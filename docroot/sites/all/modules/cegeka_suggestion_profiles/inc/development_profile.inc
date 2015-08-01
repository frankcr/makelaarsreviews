<?php
/**
 * @file
 */

/**
 * Callback for the development suggestions profile.
 */
function cegeka_suggestion_profiles_development_suggestions() {
  $suggestions = array();

  $suggestions['module_devel'] = new Drupal_Suggestion_Module('devel', 'Devel');

  if (module_exists('less')) {
    $suggestions['var_less_devel'] = new Drupal_Suggestion_Variable('less_devel', TRUE, FALSE);
  }

  $suggestions['module_views_ui'] = new Drupal_Suggestion_Module('views_ui', 'Views UI');

  $suggestions['module_reroute_email'] = new Drupal_Suggestion_Module('reroute_email', 'reroute email');
  $suggestions['reroute_to'] = new Drupal_Suggestion_Variable('reroute_email_address', 'noreply@example.com');

  $droptor = new Drupal_Suggestion_Module('droptor', 'Droptor');
  $suggestions['module_droptor'] = $droptor->disable();

  $google_analytics = new Drupal_Suggestion_Module('google_analytics', 'Google analytics');
  $suggestions['module_google_analytics'] = $google_analytics->disable();

  $suggestions['error_level'] = new Drupal_Suggestion_Variable('error_level', ERROR_REPORTING_DISPLAY_ALL, ERROR_REPORTING_DISPLAY_ALL);

  return $suggestions;
}
