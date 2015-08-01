#!/bin/bash
echo "start cron run"
cd /var/www/sftw/docroot
drush elysia-cron
echo "end cron"
