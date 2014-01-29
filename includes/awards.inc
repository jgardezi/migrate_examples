<?php

class SportsBallAwardsMigration extends SportsBallMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Import award names as vocabulary terms.');

    $query = $this->getConnection()->select('awardsplayers', 'a')
      ->fields('a', array('awardID'))
      ->groupBy('a.awardID')
      ->orderBy('a.awardID');

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationTerm('awards');

    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'awardID' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'default' => '',
          'description' => 'Award ID/Name',
         ),
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $this->addFieldMapping('name', 'awardID');
  }
}
