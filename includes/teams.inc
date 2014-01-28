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
