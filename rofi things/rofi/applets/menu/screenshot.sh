#!/usr/bin/env sh

## Author  : Aditya Shakya
## Mail    : adi1090x@gmail.com
## Github  : @adi1090x
## Twitter : @adi1090x

style="$(/opt/rofi/applets/menu/style.sh)"

dir="/opt/rofi/applets/menu/configs/$style"
rofi_command="rofi -theme $dir/screenshot.rasi"

# Error msg
msg() {
	rofi -theme "/opt/rofi/applets/styles/message.rasi" -e "Please install 'scrot' first."
}

# Options
screen=""
area=""
window=""

# Variable passed to rofi
options="$screen\n$area\n$window"

chosen="$(echo -e "$options" | $rofi_command -p 'App : scrot' -dmenu -selected-row 1)"
case $chosen in
    $screen)
		if [[ -f /usr/bin/scrot ]]; then
			sleep 1; scrot 'Scree.shot_%Y-%m-%d-%S_$wx$h.png' -e 'mv $f $$(xdg-user-dir PICTURES) ; viewnior $$(xdg-user-dir PICTURES)/$f'
		else
			msg
		fi
        ;;
    $area)
		if [[ -f /usr/bin/scrot ]]; then
			scrot -s 'Scree.shot_%Y-%m-%d-%S_$wx$h.png' -e 'mv $f $$(xdg-user-dir PICTURES) ; viewnior $$(xdg-user-dir PICTURES)/$f'
		else
			msg
		fi
        ;;
    $window)
		if [[ -f /usr/bin/scrot ]]; then
			sleep 1; scrot -u 'Scree.shot_%Y-%m-%d-%S_$wx$h.png' -e 'mv $f $$(xdg-user-dir PICTURES) ; viewnior $$(xdg-user-dir PICTURES)/$f'
		else
			msg
		fi
        ;;
esac

