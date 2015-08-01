<?php

function cetelembe_menu_tree__menu_block__1($variables) {
  $menu = menu_tree_all_data('main-menu');
  $dropdown = FALSE;
  foreach ($menu as $key => $value) {
    if (isset($value['below']) && $value['below']) {
      $dropdown = TRUE;
    }
  }

  if ($dropdown) {
    if (substr_count($variables['tree'], '</ul>') != 0) {
      return '<ul class="nav nav-pills text-bold">' . $variables['tree'] . '</ul>';
    }
    else {
      return '<ul class="dropdown-menu">' . $variables['tree'] . '</ul>';
    }
  }
  else {
    return '<ul class="nav nav-pills text-bold">' . $variables['tree'] . '</ul>';
  }
}

function cetelembe_menu_link__menu_block__1($variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
    $element['#attributes']['class'][] = 'dropdown';
    $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function cetelembe_links__locale_block($variables) {
  global $language;
  unset($variables['links'][$language->language]);

  return theme('links', $variables);
}

function cetelembe_preprocess_html(&$variables) {
  /**
   * Loop through to add various sizes
   */
  $apple_icon_sizes = array(60, 76, 120, 152);

  foreach ($apple_icon_sizes as $size) {
    $apple = array(
      '#tag' => 'link',
      '#attributes' => array(
        'href' => '/' . path_to_theme() . '/mobile-icon-' . $size . '.jpg',
        'rel' => 'apple-touch-icon-precomposed',
        'sizes' => $size . 'x' . $size,
      ),
    );
    drupal_add_html_head($apple, 'apple-touch-icon-' . $size);
  }
}
