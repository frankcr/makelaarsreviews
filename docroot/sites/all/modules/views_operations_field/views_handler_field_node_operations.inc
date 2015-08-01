<?php
/**
 * @file
 */

/**
 * Views field handler for node operations.
 *
 */
class views_handler_field_node_operations extends views_handler_field {

  /**
   * Constructor.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['type'] = 'type';
  }

  /**
   * Query.
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Render the field.
   */
  function render($values) {

    $node = new stdClass();
    $node = node_load($values->{$this->aliases['nid']});
    // Unpublished nodes ignore access control.
    $node->status = 1;

    // Invoke hook implementations.
    $operations = module_invoke_all('views_operations_field_operations', $node);

    // Let other modules alter the operations.
    drupal_alter('views_operations_field_operations', $operations, $node);

    return drupal_render($operations);
  }
}

// Link helpers for correct modification context.

/**
 * @todo Document this function.
 */
function views_operations_field_i18n_node_translation_path($path, $langcode) {
  if (variable_get_value('i18n_node_translation_switch')) {
    $type = variable_get('translation_language_type', LANGUAGE_TYPE_INTERFACE);
    $links = language_negotiation_get_switch_links($type, $path);

    if (!empty($links->links[$langcode]) && !empty($links->links[$langcode]['href'])) {
      $path = $links->links[$langcode]['href'];
    }
  }
  return $path;
}

/**
 * @todo Document this function.
 */
function views_operations_field_i18n_node_translation_options($path, $langcode, $options) {
  if (variable_get_value('i18n_node_translation_switch')) {
    // @link http://drupal.org/node/1008628#comment-3881380
    include_once DRUPAL_ROOT . '/includes/language.inc';

    $type = variable_get('translation_language_type', LANGUAGE_TYPE_INTERFACE);
    $links = language_negotiation_get_switch_links($type, $path);
    if (!empty($links->links[$langcode]) && !empty($links->links[$langcode]['href'])) {
      $options = array_merge_recursive($links->links[$langcode], $options);
    }
  }
  // Remove the language url class to avoid layout breaking.
  unset($options['attributes']);

  return $options;
}
