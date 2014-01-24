<?php

/**
 * Implements hook_migrate_api().
 */
function sportsball_migrate_api() {
  return array(
    'api' => 2,
    'groups' => array(
      'baseball' => array(
        'title' => t('Baseball'),
        ),
      ),
    'migrations' => array(
      'SportsBallPlayers' => array(
        'class_name' => 'SportsBallPlayerMigration',
        'group_name' => 'baseball',
        ),
      'SportsBallTeams' => array(
        'class_name' => 'SportsBallTeamMigration',
        'group_name' => 'baseball',
      ),
      ),
    );
}
