<?php

class views_handler_field_translation_controls extends views_handler_field_prerender_list {

  public function construct() {
    parent::construct();

    // unfortunately need to use nid as well because new nodes all have their tnid set to 0
    $this->additional_fields['nid'] = array(
      'table' => 'node',
      'field' => 'nid',
    );
    $this->additional_fields['tnid'] = array(
      'table' => 'node',
      'field' => 'tnid',
    );
    $this->additional_fields['type'] = array(
      'table' => 'node',
      'field' => 'type',
    );

    drupal_add_css(
      drupal_get_path('module', 'locale') . '/locale.css',
      array('preprocess' => FALSE)
    );
    drupal_add_css(
      drupal_get_path('module', 'views_languages_field') . '/views_languages_field.css',
      array('preprocess' => FALSE)
    );
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['nid'];
  }

  function pre_render(&$values) {
    $languages = language_list('language', TRUE);

    // remove non-enabled languages
    foreach ($languages as $key => $language) {
      if (!$language->enabled) {
        unset($languages[$key]);
      }
    }

    $sets = array();
    $this->items = array();

    // TODO: search for a better way to get 'type' into render_item
    foreach ($values as $result) {
      $tnid =  $result->{$this->aliases['tnid']};
      $type = $result->{$this->aliases['type']};
      $set = array(
        'tnid' => $tnid <> 0 ? $tnid : $result->{$this->aliases['nid']},
        'type' => $type,
      );
      $sets[$set['tnid']] = $set;
    }

    if ($sets) {
      // TODO: check if we can optimize this query somehow
      // most likely it's even better for performance to get each translation set separately
      $result = db_query(
      	"SELECT n.tnid, n.nid, n.type, n.language, n.status, h.timestamp, n.created, n.changed FROM {node} n LEFT JOIN {history} h ON n.nid = h.nid WHERE n.tnid IN (:tnid) OR n.nid IN (:nid)",
        array(
          ':tnid' => array_keys($sets),
          ':nid' => array_keys($sets),
        )
      );

      foreach ($result as $translation) {
        $tnid = $translation->tnid <> 0 ? $translation->tnid : $translation->nid;
        $this->items[$tnid][$translation->language] = array(
          'language' => $translation->language,
          'nid' => $translation->nid,
          'tnid' => $tnid,
          'type' => $sets[$tnid]['type'],
          'status' => $translation->status,
          'type' => node_mark($translation->nid, $translation->changed),
        );
      }
    }

    // add missing languages
    foreach (array_keys($sets) as $tnid) {
      $set = array_key_exists($tnid, $this->items) ? $this->items[$tnid] : array();
      $language_codes = array_keys($languages);
      $current_language_codes = array_keys($set);
      $missing_langs = array_diff($language_codes, $current_language_codes);

      if (count($missing_langs) > 0) {
        foreach ($missing_langs as $missing_lang) {
          $set[$missing_lang] = array(
            'language' => $missing_lang,
            'tnid' => $tnid,
            'type' => $sets[$tnid]['type'],
          );
        }
      }

      ksort($set);
      $this->items[$tnid] = $set;
    }
  }

  function render_item($count, $item) {
    $options['query'] = drupal_get_destination();
    $vars = array();
    if (!empty($item['nid'])) {		
      $vars['translated'] = 1;
      if ($item['status']) {
        $vars['published'] = 1;
        //l($item['language'] ? $item['language'] : t('Language neutral'), 'node/' . $item['nid'] . '/edit', $options['query']);
        $vars['link'] = views_languages_field_i18n_node_translation_link(
          $item['language'] . views_languages_mark_node($item['type']),
        	'node/' . $item['nid'] . '/edit', 
          $item['language'],
          $options['query']
        );
      }
      else {
        $vars['published'] = 0;
        //l($item['language'] ? $item['language'] : t('Language neutral'), 'node/' . $item['nid'] . '/edit', $options['query']);
      	$vars['link'] = views_languages_field_i18n_node_translation_link(
        	$item['language'], 
        	'node/' . $item['nid'] . '/edit',
        	$item['language'],
        	$options['query']
      	); 
      }
    }
    elseif (user_access('translate content')) {
      $options['query']['translation'] = $item['tnid'];
      $options['query']['target'] = $item['language'];
      //l($item['language'], 'node/add/' . str_replace('_', '-', $item['type']), $options);
      $vars['link'] = views_languages_field_i18n_node_translation_link(
        $item['language'], 
        'node/add/' . str_replace('_', '-', $item['type']),
        $item['language'],
        $options
      ); 
      
      $vars['translated'] = 0;
      $vars['published'] = 0;
    }
    else {
      // If the user has no permission to translate content, we omit the link.
      $vars['link'] = $item['language'];
      $vars['translated'] = 0;
      $vars['published'] = 0;
    } 
    
    return theme('views_languages_field_link', $vars);
  }

}

/**  
 * Link helpers for correct modification context.
 * @todo: properly document this function. 
 */
function views_languages_field_i18n_node_translation_link($text, $path, $langcode, $options = array()) {
  $options['html'] = TRUE;
	if (!variable_get('i18n_hide_translation_links', FALSE)) {
		$type = variable_get('translation_language_type', LANGUAGE_TYPE_INTERFACE);
		$links = language_negotiation_get_switch_links($type, $path);

		if (!empty($links->links[$langcode]) && !empty($links->links[$langcode]['href'])) {
		  $options = array_merge_recursive($links->links[$langcode], $options);
		  $path = $links->links[$langcode]['href'];
		}
	}

  if (drupal_valid_path($path)) {
  	return l($text, $path, $options);
  }
  else {
    return $text;
  }
}

/**
 * Helper function to get the node status.
 *
 * @param $type
 *   Integer reflecting the nodes' status
 * @return string
 *   Indicating whether the node is new or recently updated.
 */
function views_languages_mark_node($type) {
  global $user;
  if ($user->uid) {
    if ($type == MARK_NEW) {
      return '<span class="marker">*</span>';
    }
    elseif ($type == MARK_UPDATED) {
      return '<span class="marker">!</span>';
    }
  }
}
