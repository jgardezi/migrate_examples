<?php
/**
 * @file
 * Migration for player data.
 */

class SportsBallPlayerMigration extends SportsBallMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Import player data from the Lahman database.');

    //dependencies
    $this->dependencies = array('SportsBallTeams');

    // create a source object
    // use mysql special function Group_conact() so that we don't have to run query
    $query = $this->getConnection()->select('master', 'm')
      ->fields('m', array('playerID', 'nameFirst', 'nameLast', 'birthDay', 'birthMonth', 'birthYear', 'deathDay', 'deathMonth', 'deathYear', 'nameNick', 'nameNote', 'weight', 'height', 'bats', 'throws'))
      ->isNotNull('m.playerID');
    $query->leftJoin('appearances', 'a', 'a.playerID = m.playerID');
    $query->fields('a', array('teamID'))
      ->groupBy('m.playerID')
      ->orderBy('a.yearID', 'DESC')
      ->orderBy('m.playerID');

    $query->addExpression('GROUP_CONCAT(a.teamID)', 'teams');

    $this->source = new MigrateSourceSQL($query);

    // create a destination object
    $this->destination = new MigrateDestinationNode('player');

    // map
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'playerID' => array(
          'type' => 'varchar',
          'length' => 10,
          'not null' => TRUE,
          'default' => '',
          'description' => 'Player ID.',
          'alias' => 'm',
         ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->addFieldMapping('title', 'nameFirst');

    // Additional field mappings.
    $this->addFieldMapping('field_player_nick_name', 'nameNick');
    $this->addFieldMapping('field_player_height', 'height');
    $this->addFieldMapping('field_player_weight', 'weight');

    $this->addFieldMapping('field_player_bats', 'bats')
      ->description(t('What about batters who can hit switch?'))
      ->issueGroup(t('Questions'))
      ->issuePriority(MigrateFieldMapping::ISSUE_PRIORITY_BLOCKER)
      ->issueNumber(1);

    $this->addFieldMapping('field_player_throws', 'throws');

    //complex subfields  ->callbacks('strtoupper');
    $this->addFieldMapping('field_player_notes', 'nameNote')
      ->callbacks(array($this, 'prependTextNotes'));

    // Example of setting the value of a subfield.
    $this->addFieldMapping('field_player_notes:format')
      ->defaultValue('plain_text');

    // Example of setting a default value for a field.
    $this->addFieldMapping('log')
      ->defaultValue('Imported by player migration.')
      ->description(t('We are prepending data to any field that has data.'));

    // Date fields.
    $this->addFieldMapping('field_player_birthday', 'birthday');
    $this->addFieldMapping('field_player_death', 'death');

    //Field mapping for the join or entity reference
    $this->addFieldMapping('field_player_teams', 'teams')
      ->separator(',')
      ->sourceMigration(array('SportsBallTeams'));

    //showing warning error messages.
    $this->addFieldMapping('created')
      ->issueGroup(t('DNM'));

    // List of destination fields that we have no intention of migrating.
    $this->addUnmigratedDestinations(array(
      'field_player_notes:language',
      'uid',
      'changed',
      'status',
      'promote',
      'sticky',
      'revision',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'field_player_nick_name:language',
      'comment',
    ));
  }

  function prepareRow($row) {
    $row->nameFirst = $row->nameFirst . ' ' . $row->nameLast;

    if (isset($row->birthYear)) {
      $row->birthday = $row->birthYear . '/' . $row->birthMonth . '/' . $row->birthDay;
    }
    if (isset($row->deathYear)) {
      $row->death = $row->deathYear . '/' . $row->deathMonth . '/' . $row->deathDay;
    }

    //Complex way and it will run for every single query.
    //There has to be better way.
    /*$teams = array();
    $results = $this->getConnection()->select('appearances', 'a')
        ->fields('a', array('teamID'))
        ->condition('playerID', $row->playerID)
        ->execute();

    foreach ($results as $res) {
      $teams[] = $res->teamID;
    }

    $row->teamID = count($teams) ? $teams : NULL;*/
    //drush_print_r($row);

  }


  public function prependTextNotes($row) {
    return 'Imported notes: ' . $row;
  }


}
