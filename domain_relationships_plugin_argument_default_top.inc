<?php
// $Id$

/**
 * @file
 * Contains the top ancestor of current domain argument default plugin.
 */

/**
 * Default argument plugin to get the top ancestor of current domain
 */
class domain_relationships_plugin_argument_default_top extends views_plugin_argument_default {
  function argument_form(&$form, &$form_state) {
  }

  function get_argument() {
    global $_domain;
    $tree = _domain_relationships_tree();
    $top_ancestors = _domain_relationships_tree_get_ancestors($tree, $_domain['domain_id']);
    $top_ancestors[] = $_domain['domain_id'];
    return implode(',', $top_ancestors);
  }
}

