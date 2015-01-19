#!/bin/sh


sudo echo -e "if \$programname == 'judged' then /var/log/judged.log \n& ~" > /etc/rsyslog.d/30-judged.conf

sudo service rsyslog restart
