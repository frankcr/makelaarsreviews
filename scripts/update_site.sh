#!/bin/bash
sudo chmod -R 775 ../docroot
sudo chown -R root:root ../docroot
cd ../docroot
git pull origin master
drush updb -y
drush fra -y
drush cc all
cd ../scripts
sudo bash perms.sh --drupal_path=/var/www/mr/docroot --drupal_user=www-data --httpd_group=www-data
sudo service varnish restart