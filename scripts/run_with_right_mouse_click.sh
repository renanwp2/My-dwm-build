#!/bin/bash

eval $(xdotool getmouselocation --shell)

if (( $X>=1710 )); then
	/opt/rofi/powermenu.sh
else
	if(( $X<=500 )); then
		exit 0
	elif (( $X<=1510 )); then
		/usr/bin/rofi_network_.sh
	else
		if (( $X<=1587 )); then
			/usr/bin/pavucontrol
		fi
	fi
fi
