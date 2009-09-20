<?php
// $Id$

/**
 * @file
 * Domain Realtionships theme functions.
 */

/**
 * Theme individual domain listing used in select elements
 */
function theme_domain_relationships_domain_select($domain, $level = 0) {
  return str_repeat('-', $level) . $domain['sitename'];
}

/**
 * Theme individual checkboxes used in checkbox-lists
 */
function theme_domain_relationships_domain_checkboxes($domain, $level = 0) {
  //echo '<br>theme_domain_relationships_domain_checkboxes for ';
  //var_dump($domain);
  return str_repeat('&nbsp;', $level) . $domain['sitename'];
}

/**
 * Theme individual domain listing used in elements other than checkbox/select
 */
function theme_domain_relationships_domain_default($domain, $level = 0) {
  return str_repeat('&nbsp;', $level) . $domain['sitename'];
}