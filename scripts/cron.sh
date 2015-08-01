#!/bin/bash
echo "start cron run"
cd /var/www/mr/docroot
drush elysia-cron
echo "end cron"
