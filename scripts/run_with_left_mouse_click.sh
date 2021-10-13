#!/bin/bash

eval $(xdotool getmouselocation --shell)

if (( $X>=1710 )); then
/opt/rofi_calendar/naivecalendar-master/src/naivecalendar.sh -t nordic_blackout
else
	if(( $X<=500 )); then
	/opt/rofi/launcher.sh
	elif (( $X<=1510 )); then
		/usr/bin/rofi_internet_.sh
	else
		if (( $X<=1587 )); then
                /home/renan/.local/bin/eww open volume
		bash /home/renan/Scripts/killeww_.sh
		else
		/home/renan/.local/bin/eww open bright
		bash /home/renan/Scripts/killeww_.sh
		fi
	fi
fi
