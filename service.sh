#!/bin/bash

TIMEOUT_MS=60000
SCREENSAVER_EXE=/home/woz/screensaver/screensaver
GDBUS=/usr/bin/gdbus
GSETTINGS=/usr/bin/gsettings
SED=/usr/bin/sed

function get_idle_time() {
	$GDBUS call --session \
    --dest org.gnome.Mutter.IdleMonitor \
    --object-path /org/gnome/Mutter/IdleMonitor/Core \
    --method org.gnome.Mutter.IdleMonitor.GetIdletime \
    | $SED -E 's/\(uint64 (.*?),\)/\1/'
}

function is_inhibited() {
	result=$($GDBUS call --session \
    --dest org.gnome.SessionManager \
    --object-path /org/gnome/SessionManager \
    --method org.gnome.SessionManager.GetInhibitors)
    
    echo $result >> /tmp/screensaver.log
    if [ "$result" = "(@ao [],)" ]; then echo 0
    	else echo 1
    fi
}

function check_and_run() {
	idletime_ms=$(get_idle_time)
	
	if [ "$idletime_ms" -gt "$TIMEOUT_MS" ]; then
		inh=$(is_inhibited)
		echo $inh >> /tmp/screensaver.log
		if [ "$inh" -eq 0 ]; then
			$GSETTINGS set org.gnome.desktop.interface cursor-theme "hidden_cursor"
			$SCREENSAVER_EXE
			$GSETTINGS reset org.gnome.desktop.interface cursor-theme
		fi
	fi
}


while true
do
	sleep 1
	check_and_run	
done

