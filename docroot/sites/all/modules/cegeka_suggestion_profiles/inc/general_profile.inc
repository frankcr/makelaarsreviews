<?php
/**
 * @file
 */

/**
 * Callback for the general suggestions profile.
 */
function cegeka_suggestion_profiles_general_suggestions() {
  $suggestions = array();

  $suggestions['dblog_row_limit'] = new Drupal_Suggestion_Variable('dblog_row_limit', 10000, 1000);

  $suggestions['page_not_found_issue'] = new Drupal_Suggestion_Watchdog('page not found', '+1 week', 5, 'admin/config/search/redirect/404');

  $suggestions['cron_safe_treshold'] = new Drupal_Suggestion_Variable('cron_safe_threshold', 0, DRUPAL_CRON_DEFAULT_THRESHOLD);

  foreach (node_type_get_types() as $type => $node_type) {
    if ('webform' == $type) {
      continue;
    }
    $suggestions["node_options_$type"] = new Drupal_Suggestion_Node_Options($type, $node_type->name, array(
        'revision' => TRUE,
    ));
  }

  $suggestions['module_transliteration'] = new Drupal_Suggestion_Module('transliteration', 'Transliteration', 'http://drupal.org/project/transliteration');

  foreach (image_styles() as $style => $style_options) {
    $suggestions["image_style_$style"] = new Drupal_Suggestion_Image_Style($style, $style_options);
  }

  foreach (views_get_all_views() as $view_idx => $view_obj) {
    $suggestions["view_$view_idx"] = new Drupal_Suggestion_View($view_obj);
  }

  return $suggestions;
}
