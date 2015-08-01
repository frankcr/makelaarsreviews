<?php

/**
 * @file
 * Provides default theme functions for the views_languages_field module.
 */

/**
 * Wraps a link.
 */
function theme_views_languages_field_link($vars) {
  $classes = array();
  $title = '';
  if ($vars['translated']) {
    $classes[] = 'locale-translated';
    $title = t('View');
  }
  else {
    $classes[] = 'locale-untranslated';
    $title = t('Add translation');
  }
  
  if ($vars['published']) {
    $classes[] = 'locale-published';
  }
  else {
    $classes[] = 'locale-unpublished';
  }
  
  return '<em class="' . implode(' ', $classes) . '" title="' . $title . '">' . $vars['link'] . '</em>';
}