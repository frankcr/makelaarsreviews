<?php
/**
 * @file
 * Includes views_operations_field integration for the webform module.
 */

/**
 * Implements hook_views_operations_field_operations().
 */
function panels_node_views_operations_field_operations($node) {
  $operations = array();

  // Edit panel content (only for panel nodes)
  if ($node->type == 'panel') {
    $text = t('panel content');
    if (node_access('update', $node)) {
      $options = array('query' => drupal_get_destination());
      $href = "node/{$node->nid}/panel_content";

      if (!empty($node->language)) {
        $options = views_operations_field_i18n_node_translation_options("node/{$node->nid}/panel_content", $node->language, $options);
        $href = views_operations_field_i18n_node_translation_path($href, $node->language);
      }

      $operations['panel-content'] = array(
        '#type' => 'link',
        '#title' => $text,
        '#href' => $href,
        '#options' => $options,
        '#attributes' => array(
          'class' => 'cm-operation-link cm-view-edit',
        ),
        // @todo: find a better way to add spaces (probably a #theme property).
        '#suffix' => ' ',
        '#weight' => 2,
      );
    }
    else {
      $operations['panel-content'] = array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#value' => $text,
        '#attributes' => array(
          'class' => "link-disabled",
        ),
        // @todo: find a better way to add spaces (probably a #theme property).
        '#suffix' => ' ',
        '#weight' => 2,
      );
    }
  }

  return $operations;
}
