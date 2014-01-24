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
}
