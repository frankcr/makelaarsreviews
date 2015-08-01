<?php
/**
 * @file
 * module_settings.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function module_settings_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['menu-content-management'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'content-management',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'rubik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'rubik',
        'weight' => 0,
      ),
      'rubik_left' => array(
        'region' => 'sidebar_first',
        'status' => 1,
        'theme' => 'rubik_left',
        'weight' => -12,
      ),
      'sftw' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'sftw',
        'weight' => 0,
      ),
      'tao' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'tao',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
