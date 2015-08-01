<?php
/**
 * @file
 * Includes views_operations_field integration for the webform module.
 */

/**
 * Implements hook_views_operations_field_operations().
 */
function webform_views_operations_field_operations($node) {
  // @todo Permission check.
  // @todo return disabled link when the user has no permission.
  if (isset($node->webform)) {
    return array(
      'webform' => array(
        '#type' => 'link',
        '#title' => t('components'),
        '#href' => 'node/' . $node->nid .  '/webform',
        '#attributes' => array('class' => 'cm-operation-link cm-view-webform'),
        '#weight' => 3,
        '#suffix' => ' ',
      ),
      'webform-results' => array(
        '#type' => 'link',
        '#title' => t('results'),
        '#href' => 'node/' . $node->nid .  '/webform-results',
        '#attributes' => array('class' => 'cm-operation-link cm-view-webform-results'),
        '#weight' => 4,
        '#suffix' => ' ',
      ),
    );
  }
}
