<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Credit simulator'),
  'description' => t('A ctools plugin to include the credit simulator.'),
  'category' => t('Angular'),
  'edit form' => 'alpha_simulator_edit_form',
  'render callback' => 'alpha_simulator_render',
  'admin info' => 'alpha_simulator_info',
  'defaults' => array(
    'default_project_type' => 'NA',
    'default_amount' => NULL,
    'default_duration' => NULL,
    'default_installment' => NULL,
    'only_show_default_project' => 'n',
    'mock' => 'n'
  )
);

/**
 * 'admin info' callback for panel pane.
 */
function alpha_simulator_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = isset($conf['override_title']) ? $conf['override_title_text'] : '';
    $block->content = t('A panel to include the credit simulator in a drupal page');
    return $block;
  }
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function alpha_simulator_render($subtype, $conf, $panel_args, $context = array(), $incoming_content = '') {

  $block = new stdClass();

  // initial content is blank
  $block->title = '';

  /*REPLACE specific libs : BEGIN*//*app:SIMULATOR*/$specific_library_array = array('bower_components' => array('angular-resource/angular-resource.js','angular-route/angular-route.js','angular-bootstrap/ui-bootstrap-tpls.js','angular-translate/angular-translate.js','angular-translate-loader-static-files/angular-translate-loader-static-files.js','angular-animate/angular-animate.js','angular-touch/angular-touch.js','angular-facebook/lib/angular-facebook.js','angular-sanitize/angular-sanitize.js','angular-local-storage/dist/angular-local-storage.js',), 'apps' => array('components/common/common.js','components/common/commonUtils-service.js','components/common/amount-utils-service.js','components/common/date-utils-service.js','components/common/defaultSettingsByDrupal-service.js','components/common/passData-service.js','components/common/trust-as-html-filter.js','components/common/user-messages-factory-service.js','components/common/loggers/event-logger-to-google-analytics-service.js','components/common/directives/formatAmount-directive.js','components/common/directives/selectOnEvent-directive.js','components/common/directives/onlyDigits-directive.js','components/common/directives/setFocusOnModelChange-directive.js','components/common/interceptors/no-cache-interceptor.js','components/simulator/simulator.js','components/simulator/simulatorConfig-service.js','components/simulator/revolving/revolvingSimulatorConfig-service.js','components/simulator/simulatorResource-service.js','components/simulator/revolving/simulator-revolving-resource-service.js','components/simulator/simulationFactory-service.js','simulator-app.js','simulator/simulator-controller.js','simulator/revolving/simulator-revolving-controller.js','simulator/simulator-animation.js',));/*END*/

  if (isset($conf['mock'])) {
    $use_mock = $conf['mock'];
    switch($use_mock) {
      case 'y':
        $block->content = theme('alpha_simulator_mock');
        array_push($specific_library_array['bower_components'], "angular-mocks/angular-mocks.js");
        array_push($specific_library_array['apps'], "simulator/simulator-mocks_e2e.js");
        break;
      case 'n':
        $block->content = theme('alpha_simulator_app');
        break;
    }
  }

  $simulatorsettings = new stdClass();
  if (isset($panel_args[0]) && is_numeric($panel_args[0]) && $node = node_load($panel_args[0])) {
    if (isset($node->field_default_project_type[LANGUAGE_NONE][0]['value'])) {
      $default_project_type_raw = $node->field_default_project_type[LANGUAGE_NONE][0]['value'];
      if (strpos($default_project_type_raw, '&') !== FALSE) {
        $project_types = explode('&',$default_project_type_raw);
        $simulatorsettings->defaultProjectType = $project_types[0];
        $simulatorsettings->defaultProjectSubType = $project_types[1];
      }
      else {
        $simulatorsettings->defaultProjectType = $default_project_type_raw;
      }
    }
    if (isset($node->field_only_show_default_project[LANGUAGE_NONE][0]['value'])) {
      $simulatorsettings->onlyShowDefaultProject = $node->field_only_show_default_project[LANGUAGE_NONE][0]['value'];
    }

    if (isset($node->field_default_duration[LANGUAGE_NONE][0]['value'])) {
      $simulatorsettings->defaultDuration = $node->field_default_duration[LANGUAGE_NONE][0]['value'];
    }

    if (isset($node->field_default_amount[LANGUAGE_NONE][0]['value'])) {
      $simulatorsettings->defaultAmount = $node->field_default_amount[LANGUAGE_NONE][0]['value'];
    }

    if (isset($node->field_default_installment[LANGUAGE_NONE][0]['value'])) {
      $simulatorsettings->defaultInstallment = $node->field_default_installment[LANGUAGE_NONE][0]['value'];
    }
  }
  else {
    if (isset($conf['default_project_type'])) {
      $default_project_type_raw = $conf['default_project_type'];
      switch($default_project_type_raw) {
        case 'NA':
          break;
        default:
          if (strpos($default_project_type_raw, '&') !== FALSE) {
            $project_types = explode('&',$default_project_type_raw);
            $simulatorsettings->defaultProjectType = $project_types[0];
            $simulatorsettings->defaultProjectSubType = $project_types[1];
          }
          else {
            $simulatorsettings->defaultProjectType = $default_project_type_raw;
          }
          break;
      }
    }

    if (isset($conf['only_show_default_project'])) {
      $simulatorsettings->onlyShowDefaultProject = $conf['only_show_default_project'];
    }

    if (isset($conf['default_duration'])) {
      $simulatorsettings->defaultDuration = $conf['default_duration'];
    }

    if (isset($conf['default_installment'])) {
      $simulatorsettings->defaultInstallment = $conf['default_installment'];
    }

    if (isset($conf['default_amount'])) {
      $simulatorsettings->defaultAmount = $conf['default_amount'];
    }

  }
  $product_details = get_product_details();
  $simulatorsettings->productDetails = $product_details;


//[
//{type: 'car', subType: 'new', text: 'Exemple représentatif...'}
//,
//{type: 'car', subType: 'usedYoungerThan3years', text: 'Exemple représentatif...'}
//,
//...
//]
//p.s. subType empty string when no subtype

  drupal_add_js(array('alpha_angular_apps' => array('simulatorConfig' => $simulatorsettings)), 'setting');

  include_angular_files('alpha_angular_apps', $specific_library_array);

  return $block;
}

function get_product_details() {
  global $language;
  $query = db_select('node', 'n');
  $query->join('field_data_field_default_project_type', 'pt', 'n.nid = pt.entity_id');
  $query->join('field_data_body', 'b', 'n.nid = b.entity_id');
  $query->join('field_data_field_default_amount', 'a', 'n.nid = a.entity_id');

  $result = $query->fields('n', array('nid', 'type', 'language'))
    ->fields('b', array('body_value'))
    ->fields('pt', array('field_default_project_type_value'))
    ->fields('a', array())
    ->condition('n.status', 1, '=')
    ->condition('n.language', $language->language, '=')
    ->condition('n.type', 'alpha_representative_example', '=')
    ->execute();

  $examples = array();
  foreach ($result as $database_details) {
    $example = new stdClass();
    $database_type = $database_details->field_default_project_type_value;
    $type_parts = explode('&', $database_type);
    $example->type = $type_parts[0];
    $example->subType = isset($type_parts[1]) ? $type_parts[1] : '';
    $example->text = $database_details->body_value;
    $example->amount = $database_details->field_default_amount_value;
    $examples[] = $example;
  }

  return $examples;
}

/**
* 'Edit form' callback for the content type.
*/

function alpha_simulator_edit_form($form, &$form_state) {

  $conf = $form_state['conf'];

  //TODO info text;
  if (!isset($form_state['contexts']['argument_entity_id:node_1'])) {
    $form['default_project_type'] = array(
      '#title' => t('Default product type'),
      '#description' => t('The default product type of the simulator'),
      '#type' => 'select',
      '#options' => array(
        'NA' => t('None'),
        'car' => t('Car'),
        'car&new' => t('New car'),
        'car&usedYoungerThan3years' => t('Used car < 3 years'),
        'car&usedOlderThan3years' => t('Used car > 3 years'),
        'moto' => t('Moto'),
        'moto&new' => t('New moto'),
        'moto&usedYoungerThan3years' => t('Used moto < 3 years'),
        'moto&usedOlderThan3years' => t('Used moto > 3 years'),
        'homeImprovement' => t('Home improvement'),
        'homeImprovement&eco' => t('Home improvement eco'),
        'homeImprovement&classic' => t('Home improvement classic'),
        'other' => t('Other'),
        'other&allPurposes' => t('All purposes'),
        'other&holiday' => t('Holiday'),
        'revolving' => t('Revolving'),
      ),
      '#required' => FALSE,
      '#default_value' => $conf['default_project_type'],
    );

    $form['only_show_default_project'] = array(
      '#title' => t('Only show default project'),
      '#type' => 'select',
      '#options' => array(
        'n' => t('No'),
        'y' => t('Yes'),
      ),
      '#required' => FALSE,
      '#default_value' => $conf['only_show_default_project'],
    );

    $form['default_amount'] = array(
      '#type' => 'textfield',
      '#title' => t('Default amount'),
      '#size' => 60,
      '#maxlength' => 10,
      '#default_value' => $conf['default_amount'],
    );

    $form['default_duration'] = array(
      '#type' => 'textfield',
      '#title' => t('Default duration'),
      '#size' => 60,
      '#maxlength' => 10,
      '#default_value' => $conf['default_duration'],
    );

    $form['default_installment'] = array(
      '#type' => 'textfield',
      '#title' => t('Default installment'),
      '#size' => 60,
      '#maxlength' => 10,
      '#default_value' => $conf['default_installment'],
    );
  }

  $form['mock'] = array(
    '#title' => t('Use mock server'),
    '#type' => 'select',
    '#options' => array(
      'n' => t('No'),
      'y' => t('Yes'),
    ),
    '#required' => FALSE,
    '#default_value' => $conf['mock'],
  );

  if (isset($form_state['contexts']['argument_entity_id:node_1'])) {
    $nid = $form_state['contexts']['argument_entity_id:node_1']->argument;
    if (isset($nid) && is_numeric($nid)) {
      $message = t('Other simulator settings can be changed <a href="/node/@nid/edit" target="_blank">here</a>.',
        array('@nid' => $nid));
      $form['description'] = array(
        '#markup' => '<h4>'.$message.'</h4>',
      );
    }
  }
  return $form;
}

/**
* The submit form stores the data in $conf.
*/
function alpha_simulator_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}
