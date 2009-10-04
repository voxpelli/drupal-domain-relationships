<?php
// $Id: domain_relationships.theme.inc,v 1.1.2.1 2009/09/28 18:43:44 nonsie Exp $

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
  return str_repeat('&nbsp;', $level) . $domain['sitename'];
}

/**
 * Theme individual domain listing used in elements other than checkbox/select
 */
function theme_domain_relationships_domain_default($domain, $level = 0) {
  return str_repeat('&nbsp;', $level) . $domain['sitename'];
}