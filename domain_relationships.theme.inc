<?php
// $Id$

/**
 * @file
 * Domain Realtionships theme functions.
 */

/**
 * Theme individual domain listing used in select elements
 */
function theme_domain_relationships_domain_select_list($domain, $level = 0, $show_subdomain = FALSE) {
  if ($show_subdomain) {
    return str_repeat('-', $level) . $domain['sitename'] .'('. $domain['subdomain'] .')';
  }
  else {
    return str_repeat('-', $level) . $domain['sitename'];
  }
}

/**
 * Theme individual checkboxes used in checkbox-lists
 */
function theme_domain_relationships_domain_checkbox($element) {
  $element['#title'] = str_repeat('&nbsp;', $element['#indent'] * 3) . $element['#title'];
  $output = theme('checkbox', $element);
  return $output;
}