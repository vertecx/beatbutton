#!/bin/sh

### BEGIN INIT INFO
# Provides:          beatbutton
# Required-Start:    $local_fs $syslog
# Required-Stop:     $local_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:
# Short-Description: Start beatbutton daemon
### END INIT INFO

PATH=/sbin
DAEMON=/usr/local/bin/beatbutton
NAME=beatbutton
DESC="beatbutton daemon"

test -x $DAEMON || exit 0

. /lib/lsb/init-functions

case "$1" in
	start)
		log_daemon_msg "Starting $DESC" "$NAME"
		start-stop-daemon --start --quiet --background --exec $DAEMON
		log_end_msg $?
		;;
	stop)
		log_daemon_msg "Stopping $DESC" "$NAME"
		start-stop-daemon --stop --quiet --name $NAME
		log_end_msg $?
		;;
	restart)
		log_daemon_msg "Restarting $DESC" "$NAME"
		$0 stop
		$0 start
		;;
	status)
		status_of_proc "$DAEMON" "$NAME" && exit 0 || exit $?
		;;
	*)
		echo "Usage: $NAME {start|stop|restart|status}" >&2
		exit 3
		;;
esac
