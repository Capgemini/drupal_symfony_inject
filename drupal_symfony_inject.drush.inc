<?php
/**
 * @file
 * Drush commands to clear off/rebuild the container.
 */

/**
 * Implements hook_drush_command().
 * @see drush_drupal_symfony_inject_rebuild_symfony_container()
 */
function drupal_symfony_inject_drush_command() {
  $items['rebuild-symfony-container'] = array(
    'description' => dt('Rebuild the Symfony container, compile and set cache.'),
    'examples' => array(
      'rebuild-symfony-container' => 'drush rebuild-symfony-container',
    ),
    'aliases' => array('rsc'),
  );

  return $items;
}

/**
 * Drush command - drush_drupal_symfony_inject_rebuild_symfony_container.
 */
function drush_drupal_symfony_inject_rebuild_symfony_container() {
  require_once drupal_get_path('module', 'drupal_symfony_inject') . '/drupal_symfony_inject.module';

  drush_print('Rebuild and Registering class loader.');
  drupal_symfony_inject_register_class_loader(TRUE);
  drush_print('Loading Yaml config with custom params.');
  $container_builder = drupal_symfony_inject_load_yaml_config();

  if (
    !empty($container_builder) &&
    $container_builder instanceof Symfony\Component\DependencyInjection\ContainerBuilder
  ) {
    cache_set(SYMFONY_DI_CONTAINER_CACHE_KEY, $container_builder);
    drush_print('Symfony DI container compiled and cached successfully !!!');
  }
  else {
    drush_print('Failed to compile and save the Symfont Container Builder.');
  }
}

