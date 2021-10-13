#!/bin/bash
cur=$(</sys/class/backlight/intel_backlight/brightness)
max=$(</sys/class/backlight/intel_backlight/max_brightness)
inpfile=/sys/class/backlight/intel_backlight/brightness
step=10000
case "$1" in
	down) lower=$(($cur-$step));[ $lower -lt 0 ] && lower=0;sel=$lower;;
	up)   higher=$(($cur+$step));[ $higher -gt $max ] && higher=$max;sel=$higher;;
esac
echo $sel > $inpfile
