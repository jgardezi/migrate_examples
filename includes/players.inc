<?php
/**
 * @file
 * Migration for players data.
 */

class SportsBallPlayerMigration extends SportsBallMigration {

  public function __construct($argumnets){
    parent::__construct($argumnets);

    $this->description = t('Import player data from the Lahman database.');

    // create a source object
    $query = $this->getConnection()->select('master', 'm')
      ->fields('m', array('playerID', 'nameFirst', 'nameLast', 'birthDay', 'birthMonth', 'birthYear', 'deathDay', 'deathMonth', 'deathYear',
        'nameNick', 'nameNote', 'weight', 'height', 'bats', 'throws'))
      ->isNotNull('m.playerID');

    $this->source = new MigrateSourceSQL($query);

    // create a destination object
    $this->destination = new MigrateDestinationNode('player');

    // map
    $this->map = new MigrateSQLMap($this->machineName,
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

    // individual or additional field mapping
    $this->addFieldMapping('title', 'nameFirst');
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

    //example of setting the value of a subfield.
    $this->addFieldMapping('field_player_notes:format')
          ->defaultValue('plain_text');

    //example of setting a default value for a field
    $this->addFieldMapping('log')
          ->defaultValue('Imported by player migration.')
          ->description('We are prepending data to any field that had data.');

    // Date fields.
    $this->addFieldMapping('field_player_birthday', 'birthday');
    $this->addFieldMapping('field_player_death', 'death');

    $this->addFieldMapping('created')
      ->issueGroup(t('DNM'));

    // drupal default values will be inserted field not in use, thought about these fields but considering to use it
    // just nice pratice. team work
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

  /**
   * Perform operations on rows in order to be suitable for destination
   */
  function prepareRow($row){
    //drush_print_r($row);
    $row->nameFirst = $row->nameFirst . ' ' . $row->nameLast;

    if(isset($row->birthYear)) {
      $row->birthday = $row->birthYear . '/' . $row->birthMonth . '/' . $row->birthDay;
    }
    if(isset($row->deathYear)) {
      $row->death = $row->deathYear . '/' . $row->deathMonth . '/' . $row->deathDay;
    }
  }

/**
 * Calling a custom function using call back and do some changes on the field.
 */
  public function prependTextNotes($row) {
    return 'Imported notes: ' . $row;
  }

}
