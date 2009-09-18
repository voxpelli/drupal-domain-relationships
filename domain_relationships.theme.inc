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
 * Theme individual domain listing used in display elements
 */
function theme_domain_relationships_domain_display_list($domain_sitename, $level = 0) {
  return str_repeat('&nbsp;', $level) . $domain_sitename;
}