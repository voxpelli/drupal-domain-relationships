<?php
// $Id$
/**
 * Argument handler for related domains.
 */
class domain_relationships_handler_argument_related extends views_handler_argument {
  function option_definition() {
    $options = parent::option_definition();

    $options['negative_depth'] = array('default' => 0);
    $options['positive_depth'] = array('default' => 0);
    $options['break_phrase'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['negative_depth'] = array(
      '#type' => 'textfield',
      '#title' => t('Negative Depth'),
      '#size' => 5,
      '#default_value' => $this->options['negative_depth'],
      '#description' => t('The negative depth will determine how far above the domain in the hierarchy domains should be matched.'),
    );

    $form['positive_depth'] = array(
      '#type' => 'textfield',
      '#title' => t('Positive Depth'),
      '#size' => 5,
      '#default_value' => $this->options['positive_depth'],
      '#description' => t('The positive depth will determine how far below the domain in the hierarchy domains should be matched.'),
    );

    $form['break_phrase'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow multiple terms per argument'),
      '#description' => t('If selected, users can enter multiple arguments in the form of 1+2+3. Due to the number of JOINs it would require, AND will be treated as OR with this argument.'),
      '#default_value' => !empty($this->options['break_phrase']),
    );
  }

  function options_validate($form, &$form_state) {
    parent::options_validate($form, $form_state);

    $depths = array('negative_depth', 'positive_depth');

    foreach ($depths as $depth) {
      $value = $form_state['values']['options'][$depth];
      if (!$value) {
        form_set_value($form[$depth], 0, $form_state);
      }
      elseif (!is_numeric($value)) {
        form_error($form[$depth], t('The depth must be a number.'));
      }
      elseif ($value < 0) {
        form_error($form[$depth], t('The depth can not be a negative number.'));
      }
    }
  }

  /**
   * Override default_actions() to remove summary actions.
   */
  function default_actions($which = NULL) {
    if ($which) {
      if (in_array($which, array('ignore', 'not found', 'empty', 'default'))) {
        return parent::default_actions($which);
      }
      return;
    }
    $actions = parent::default_actions();
    unset($actions['summary asc']);
    unset($actions['summary desc']);
    return $actions;
  }

  function query() {
    $this->ensure_my_table();

    $multiple = FALSE;

    if (!empty($this->options['break_phrase'])) {
      $tids = new stdClass();
      $tids->value = $this->argument;
      $tids = views_break_phrase($this->argument, $tids);
      if ($tids->value == -1) {
        return FALSE;
      }

      if (count($tids->value) > 1) {
        $multiple = TRUE;
        $placeholder = " IN (" . implode(', ', array_fill(0, sizeof($tids->value), '%d')) . ")";
      }
      else {
        $placeholder = " = %d";
      }

      $tids = $tids->value;
    }
    else {
      $placeholder = "= %d";
      $tids = array($this->argument);
    }
    $subquery = '';
    $where = "  WHERE d.domain_id $placeholder\n";
    $args = $tids;
    $last = 'd';

    if ($this->options['negative_depth'] > 0) {
      for ($count = 1; $count <= $this->options['negative_depth']; $count++) {
        $current = "nd$count";
        $subquery .= "    LEFT JOIN {domain} $current ON $last.domain_id = $current.parent\n";
        $where .= "    OR $current.domain_id $placeholder\n";
        $args = array_merge($args, $tids);
        $last = $current;
      }
    }
    if ($this->options['positive_depth'] > 0) {
      if ($multiple || !empty($subquery) || $this->options['positive_depth'] != 1) {
        $last = 'd';
        for ($count = 1; $count <= $this->options['positive_depth']; $count++) {
          $current = "pd$count";
          $subquery .= "    LEFT JOIN {domain} $current ON $last.parent = $current.domain_id\n";
          $where .= "    OR $current.domain_id $placeholder\n";
          $args = array_merge($args, $tids);
          $last = $current;
        }
      }
    }

    if (empty($subquery)) {
      $group_id = $this->query->set_where_group('OR');
      $this->query->add_where($group_id , "$this->table_alias.$this->real_field = %d", $this->argument);
      $this->query->add_where($group_id , "$this->table_alias.parent = %d", $this->argument);
    }
    else {
      $subquery = "\n  SELECT d.domain_id FROM {domain} d\n" . $subquery;
      $this->query->add_where(0, "$this->table_alias.$this->real_field IN ($subquery$where  )", $args);
    }

  }
}