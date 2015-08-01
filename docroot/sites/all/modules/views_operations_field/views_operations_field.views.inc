<?php
/**
 * @file
 */

/**
 * Implements hook_views_handlers().
 */
function views_operations_field_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_operations_field'),
    ),
    'handlers' => array(
      'views_handler_field_node_operations' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

/**
 * Implements hook_views_data_alter().
 */
function views_operations_field_views_data_alter(&$views_data) {
  $views_data['node']['operations'] = array(
    'field' => array(
      'title' => t('Operations'),
      'help' => t('Provide links to common node operations like edit and delete.'),
      'handler' => 'views_handler_field_node_operations',
    ),
  );
}
