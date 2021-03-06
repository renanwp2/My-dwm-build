#!/bin/bash

## Author  : Aditya Shakya
## Mail    : adi1090x@gmail.com
## Github  : @adi1090x
## Twitter : @adi1090x

# Available Styles
# >> Created and tested on : rofi 1.6.0-1
#
# column_circle     column_square     column_rounded     column_alt
# card_circle     card_square     card_rounded     card_alt
# dock_circle     dock_square     dock_rounded     dock_alt
# drop_circle     drop_square     drop_rounded     drop_alt
# full_circle     full_square     full_rounded     full_alt
# row_circle      row_square      row_rounded      row_alt

theme="row_square"
dir="/opt/rofi/powermenu"

# random colors
#styles=($(ls -p --hide="colors.rasi" $dir/styles))
#color="${styles[$(( $RANDOM % 8 ))]}"

# comment this line to disable random colors
#sed -i -e "s/@import .*/@import \"$color\"/g" $dir/styles/colors.rasi

# comment these lines to disable random style
#themes=($(ls -p --hide="powermenu.sh" --hide="styles" --hide="confirm.rasi" --hide="message.rasi" $dir))
#theme="${themes[$(( $RANDOM % 24 ))]}"

uptime=$(cat /proc/uptime | awk '{print $1}' | awk '{DAYS=int($1/(86400)); HOURS=int(($1%86400)/3600); MINUTES=int($1%3600/60); { print DAYS "d:" HOURS"h:"MINUTES"m"}}')

rofi_command="rofi -theme $dir/$theme"

# Options
bashutdown=""
reboot=""
lock=""
suspend=""
logout=""

# Confirmation
confirm_exit() {
	rofi -dmenu\
		-i\
		-no-fixed-num-lines\
		-p "Confirme com sim, por favor:"\
		-theme $dir/confirm.rasi
}

# Message
msg() {
	rofi -theme "$dir/message.rasi" -e "Opções disponíveis:      sim / s / não / nao / n"
}

# Variable passed to rofi
options="$bashutdown\n$reboot\n$lock\n$suspend\n$logout"

chosen="$(echo -e "$options" | $rofi_command -p "Tempo de atividade : $uptime" -dmenu -selected-row 2)"
case $chosen in
    $bashutdown)
		ans=$(confirm_exit &)
		if [[ $ans == "sim" || $ans == "SIM" || $ans == "s" || $ans == "S" ]]; then
			systemctl poweroff
		elif [[ $ans == "nao" || $ans == "NAO" || $ans == "n" || $ans == "N" || $ans == "não" || $ans == "NÃO" ]]; then
			exit 0
        	else
			msg
        	fi
        ;;
    $reboot)
		ans=$(confirm_exit &)
		if [[ $ans == "sim" || $ans == "SIM" || $ans == "s" || $ans == "S" ]]; then
			systemctl reboot
		elif [[ $ans == "nao" || $ans == "NAO" || $ans == "n" || $ans == "N" || $ans == "não" || $ans == "NÃO" ]]; then
			exit 0
        	else
			msg
        	fi
        ;;
    $lock)
		if [[ -f /usr/bin/i3lock ]]; then
			i3lock
		elif [[ -f /usr/bin/betterlockscreen ]]; then
			betterlockscreen -l
		else [[ -f /usr/bin/dm-tool ]]
			dm-tool lock
		fi
        ;;
    $suspend)
		ans=$(confirm_exit &)
		if [[ $ans == "sim" || $ans == "SIM" || $ans == "s" || $ans == "S" ]]; then
			mpc -q pause
			amixer set Master mute
			systemctl suspend
		elif [[ $ans == "nao" || $ans == "NAO" || $ans == "n" || $ans == "N" || $ans == "não" || $ans == "NÃO" ]]; then
			exit 0
        	else
			msg
        	fi
        ;;
    $logout)
		ans=$(confirm_exit &)
		if [[ $ans == "sim" || $ans == "SIM" || $ans == "s" || $ans == "S" ]]; then
			if [[ "$DESKTOP_SESSION" == "Openbox" ]]; then
				openbox --exit
			elif [[ "$DESKTOP_SESSION" == "bspwm" ]]; then
				bspc quit
			elif [[ "$DESKTOP_SESSION" == "i3" ]]; then
				i3-msg exit
			else [[ "$DESKTOP_SESSION" == "dwm" ]]
				killall dwm
			fi
		elif [[ $ans == "no" || $ans == "NO" || $ans == "n" || $ans == "N" ]]; then
			exit 0
        	else
			msg
        	fi
        ;;
esac
