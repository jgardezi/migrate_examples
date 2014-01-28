<?php

abstract class SportsBallMigration extends Migration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->issuePattern = 'https://github.com/jgardezi/migrate_examples/issues/:id:';

    $this->team = array(
      new MigrateTeamMember('Javed Gardezi', 'javed@example.com',
                            t('Product Owner and Developer')),
      new MigrateTeamMember('Rob Dev', 'rob@example.com',
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
