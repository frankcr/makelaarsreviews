<?php
/**
 * @file
 * Includes views_operations_field integration for the webform module.
 */

/**
 * Implements hook_views_operations_field_operations().
 */
function node_views_operations_field_operations($node) {
  $operations = array();

  // View operation.
  $text = t('view');
  if (node_access('view', $node)) {
    $operations['view'] = array(
      '#type' => 'link',
      '#title' => $text,
      '#href' => "node/{$node->nid}",
      '#attributes' => array(
        'class' => 'cm-operation-link cm-view-view',
      ),
      // @todo: Find a better way to add spaces (probably a #theme property).
      '#suffix' => ' ',
      '#weight' => 0,
    );
  }
  else {
    $operations['view'] = array(
      '#type' => 'html_tag',
      '#tag' => 'span',
      '#value' => $text,
      '#attributes' => array(
        'class' => "link-disabled",
      ),
      // @todo: find a better way to add spaces (probably a #theme property).
      '#suffix' => ' ',
      '#weight' => 0,
    );
  }

  // Edit operation.
  $text = t('edit');
  if (node_access('update', $node)) {
    $options = array('query' => drupal_get_destination());
    $href = "node/{$node->nid}/edit";

    // Add language options to the url.
    if (!empty($node->language)) {
      $options = views_operations_field_i18n_node_translation_options("node/{$node->nid}/edit", $node->language, $options);
      $href = views_operations_field_i18n_node_translation_path("node/{$node->nid}/edit", $node->language);
    }

    $operations['edit'] = array(
      '#type' => 'link',
      '#title' => $text,
      '#href' => $href,
      '#options' => $options,
      '#attributes' => array(
        'class' => 'cm-operation-link cm-view-edit',
      ),
      // @todo: find a better way to add spaces (probably a #theme property).
      '#suffix' => ' ',
      '#weight' => 1,
    );
  }
  else {
    $operations['edit'] = array(
      '#type' => 'html_tag',
      '#tag' => 'span',
      '#value' => $text,
      '#attributes' => array(
        'class' => "link-disabled",
      ),
      // @todo: find a better way to add spaces (probably a #theme property).
      '#suffix' => ' ',
      '#weight' => 1,
    );
  }

  // Delete operation.
  $text = t('delete');
  if (node_access('delete', $node)) {
    $operations['delete'] = array(
      '#type' => 'link',
      '#title' => $text,
      '#href' => "node/{$node->nid}/delete",
      '#options' => array(
        'query' => drupal_get_destination(),
      ),
      '#attributes' => array(
        'class' => 'cm-operation-link cm-view-delete',
      ),
      // @todo: find a better way to add spaces (probably a #theme property).
      '#suffix' => ' ',
      '#weight' => 3,
    );
  }
  else {
    $operations['delete'] = array(
      '#type' => 'html_tag',
      '#tag' => 'span',
      '#value' => $text,
      '#attributes' => array(
        'class' => "link-disabled",
      ),
      // @todo: find a better way to add spaces (probably a #theme property).
      '#suffix' => ' ',
      '#weight' => 3,
    );
  }

  // View revisions operation.
  if (module_exists('revisioning')) {
    $text = t('revisions');
    if (user_access('view revisions')) {
      $operations['revisions'] = array(
        '#type' => 'link',
        '#title' => $text,
        '#href' => "node/{$node->nid}/revisions/{$node->vid}/list",
        '#options' => array(
          'query' => drupal_get_destination(),
        ),
        '#attributes' => array(
          'class' => 'cm-operation-link cm-view-revisions',
        ),
        // @todo: find a better way to add spaces (probably a #theme property).
        '#suffix' => ' ',
        '#weight' => 4,
      );
    }
    else {
      $operations['revisions'] = array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#value' => $text,
        '#attributes' => array(
          'class' => "link-disabled",
        ),
        // @todo: find a better way to add spaces (probably a #theme property).
        '#suffix' => ' ',
        '#weight' => 4,
      );
    }
  }
  return $operations;
}

