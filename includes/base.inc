<?php

abstract class SportsBallMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->issuePattern = '';

    $this->team = array(
      new MigrateTeamMember('Rob Taster', 'robtaster@example.com',
                            t('Product Owner')),
      new MigrateTeamMember('Javed Gardezi', 'javed@example.com',
                            t('Implementor')),
    );
  }

/**
 * Drupal conneciton
 * @param  string $connection database connection name
 * @return database connection
 */
  public function getConnection($connection  = 'baseball') {
    return Database::getConnection('default', $connection);
  }
}
