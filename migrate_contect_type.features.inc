<?php
/**
 * @file
 * migrate_contect_type.features.inc
 */

/**
 * Implements hook_node_info().
 */
function migrate_contect_type_node_info() {
  $items = array(
    'player' => array(
      'name' => t('Player'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'team' => array(
      'name' => t('Team'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Team Name'),
      'help' => '',
    ),
  );
  return $items;
}
