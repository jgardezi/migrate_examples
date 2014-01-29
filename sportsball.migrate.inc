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
      'content' => array(
        'title' => t('Content'),
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
        'SportsBallPages' => array(
          'class_name' => 'SportsBallPageMigration',
          'group_name' => 'content',
        ),
        'SportsBallAwards' => array(
          'class_name' => 'SportsBallAwardsMigration',
          'group_name' => 'content',
        ),
      ),
    );
}
