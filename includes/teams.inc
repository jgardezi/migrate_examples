<?php

class SportsBallTeamMigration extends SportsBallMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Migration for team data.');

    $query = $this->getConnection()->select('teams', 't')
      ->fields('t', array('teamID', 'park', 'name'))
      ->groupBy('t.teamID')
      ->orderBy('t.yearID', 'DESC');

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('team');

    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'teamID' => array(
          'type' => 'varchar',
          'length' => 3,
          'not null' => TRUE,
          'default' => '',
          'description' => 'Team ID.',
          'alias' => 't',
         ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->addFieldMapping('title', 'name');
    $this->addFieldMapping('field_team_park', 'park');
  }

/**
 * Players migration executes it will only create stub team ids for mapping purpose
 * and when teams migaration will execute it will update existing stubs
 * @param  Migration $migration this miragtion
 * @param  array     $source_id team ids
 * @return node               team id
 */
  protected function createStub(Migration $migration, array $source_id) {
    $node = new stdClass();
    $node->title = t('Stub for team @id', array('@id' => $source_id[0]));
    $node->type = 'team';
    node_save($node);
    if (isset($node->nid)) {
      return array($node->nid);
    }
    else {
      return FALSE;
    }
  }

}
