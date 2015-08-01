<?php
/**
 * @file
 */

/**
 * Callback for the production suggestions profile.
 */
function cegeka_suggestion_profiles_production_suggestions() {
  $suggestions = array();

  $devel = new Drupal_Suggestion_Module('devel', 'Devel');
  $suggestions['module_devel'] = $devel->disable();

  $suggestions['var_reroute_email_enable'] = new Drupal_Suggestion_Variable('reroute_email_enable', 0, 0);

  if (module_exists('less')) {
    $suggestions['var_less_devel'] = new Drupal_Suggestion_Variable('less_devel', FALSE, FALSE);
  }

  $page_cache_invoke_hooks = new Drupal_Suggestion_Variable('page_cache_invoke_hooks', FALSE, TRUE);
  $reverse_proxy = new Drupal_Suggestion_Variable('reverse_proxy', TRUE, FALSE);

  $suggestions['page_cache_invoke_hooks'] = $page_cache_invoke_hooks->inSettingsFile();
  $suggestions['reverse_proxy'] = $reverse_proxy->inSettingsFile();

  $suggestions['module_varnish'] = new Drupal_Suggestion_Module('varnish', 'Varnish', 'http://drupal.org/project/varnish');

  $suggestions['module_droptor'] = new Drupal_Suggestion_Module('droptor', 'Droptor', 'http://drupal.org/project/droptor');

  $suggestions['module_google_analytics'] = new Drupal_Suggestion_Module('googleanalytics', 'Google Analytics', 'http://drupal.org/project/google_analytics');

  $views_ui = new Drupal_Suggestion_Module('views_ui', 'Views UI');
  $suggestions['views_ui'] = $views_ui->disable();

  $suggestions['error_level'] = new Drupal_Suggestion_Variable('error_level', ERROR_REPORTING_HIDE, ERROR_REPORTING_DISPLAY_ALL);

  $suggestions['cache'] = new Drupal_Suggestion_Variable('cache', 1, 0);

  $suggestions['cache_lifetime'] = new Drupal_Suggestion_Variable('cache_lifetime', 60, 0);

  $suggestions['page_cache_maximum_age'] = new Drupal_Suggestion_Variable('page_cache_maximum_age', 3600, 0);

  if (module_exists('varnish')) {
    $cache_backends = new Drupal_Suggestion_Variable('cache_backends', array(drupal_get_path('module', 'varnish') . '/varnish.cache.inc'), array());

    $suggestions['cache_backends'] = $cache_backends->inSettingsFile();

    $cache_class_cache_page = new Drupal_Suggestion_Variable('cache_class_cache_page', 'VarnishCache');
    $suggestions['cache_class_cache_page'] = $cache_class_cache_page->inSettingsFile();

    $suggestions['varnish_version'] = new Drupal_Suggestion_Variable('varnish_version', '3', 2.1);
    $suggestions['varnish_control_terminal'] = new Drupal_Suggestion_Variable('varnish_control_terminal', '127.0.0.1:6082', '127.0.0.1:6082');
    $suggestions['varnish_socket_timeout'] = new Drupal_Suggestion_Variable('varnish_socket_timeout', 1000, 100);

    // @todo add check for non-empty control key.
  }

  // Outcommented for now until our hosting environment is suitable for it
  // (cgi vs. mod_php Apache handler).
  /*
  $suggestions['php_extension_apc'] = new Drupal_Suggestion_PHP_Extension('apc');
  $suggestions['php_config_apc_enabled'] = new Drupal_Suggestion_PHP_ConfigurationOption('apc.enabled', '1');
  */

  return $suggestions;
}
