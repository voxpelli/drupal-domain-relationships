<?php
// $Id: domain_relationships.views.inc,v 1.1.2.1 2009/09/30 22:43:50 nonsie Exp $

/**
 * @file
 *
 * Provide views data and handlers for domain_relationships.module
 */

/**
 * Implementation of hook_views_data_alter().
 */
function domain_relationships_views_data_alter(&$data) {
  $data['domain']['parent'] = array( //TODO: Do I want to skip base here as the Taxonomy does?
    'title' => t('Parent Id'),
    'help' => t('Matches with domain id.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
      'skip base' => array('node', 'node_revision'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['domain']['parent_related'] = array( //TODO: Do I want to skip base here as the Taxonomy does?
    'title' => t('Related'),
    'help' => t('Matches domains related to id - both parents and children possible.'),
    'real field' => 'domain_id',
    'argument' => array(
      'handler' => 'domain_relationships_handler_argument_related',
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function domain_relationships_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'domain_relationships') . '/includes',
    ),
    'handlers' => array(
      'domain_relationships_handler_argument_related' => array(
        'parent' => 'views_handler_argument',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function domain_relationships_views_plugins() {
  return array(
    'argument default' => array(
      'current_domain_ancestors' => array(
        'title' => t("Current domain's top ancestor ID"),
        'handler' => 'domain_relationships_plugin_argument_default_top',
        'path' => drupal_get_path('module', 'domain_relationships') . '/includes',
        'parent' => 'fixed', // so that the parent class is included
      ),
    ),
  );
}