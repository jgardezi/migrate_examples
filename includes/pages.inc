<?php
/**
 * @file
 * Import pages from a csv file.
 */

class SportsBallPageMigration extends SportsBallMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Import basic pages from a CSV file.');

    $pathCSV  = drupal_get_path('module', 'sportsball') . '/source/sample_data.csv';

    $options = array(
      'header_rows' => 1,
      'delimiter' => '|',
      );

    $this->source = new MigrateSourceCSV($pathCSV, array(), $options);

    $this->destination = new MigrateDestinationNode('page');

    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'title' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'default' => '',
          'description' => 'Title of article.',
         ),
        'date' => array(
          'type' => 'int',
          'length' => 10,
          'unsigned' => TRUE,
          'not null' => TRUE,
          'default' => 0,
          'description' => 'Publication date',
         ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('created', 'date');
    $this->addFieldMapping('status', 'public');
    $this->addFieldMapping('body', 'copy');

  }

}
