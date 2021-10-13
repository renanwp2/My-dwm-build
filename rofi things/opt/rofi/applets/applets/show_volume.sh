#!/usr/bin/env sh

## Author  : Aditya Shakya
## Mail    : adi1090x@gmail.com
## Github  : @adi1090x
## Twitter : @adi1090x

style="$(/opt/rofi/applets/applets/style.sh)"

dir="/opt/rofi/applets/applets/configs/$style"
rofi_command="rofi -theme $dir/show_volume.rasi"

## Get data
BATTERY_PERCENT=$(pacmd dump-volumes | awk 'NR==1{print $8}' | sed 's/\%//')
BATTERY=$(pacmd dump-volumes | awk 'NR==1{print $8}' | sed 's/\%//')
BATTERY=$((BATTERY*100/153))
BATTERY_PERCENT=$((BATTERY_PERCENT*100/153))

active=""
urgent=""

if (( 0<=$BATTERY && $BATTERY<=5 ))
then
    BATTERY="◻◻◻◻◻◻◻◻◻◻"
elif (( 5<$BATTERY && $BATTERY<=10 ))
then
    BATTERY="◼◻◻◻◻◻◻◻◻◻"
elif (( 10<$BATTERY && $BATTERY<=20 ))
then
    BATTERY="◼◼◻◻◻◻◻◻◻◻"
elif (( 20<$BATTERY && $BATTERY<=30 ))
then
    BATTERY="◼◼◼◻◻◻◻◻◻◻"
elif (( 30<$BATTERY && $BATTERY<=40 ))
then
    BATTERY="◼◼◼◼◻◻◻◻◻◻"
elif (( 40<$BATTERY && $BATTERY<=50 ))
then
    BATTERY="◼◼◼◼◼◻◻◻◻◻"
elif (( 50<$BATTERY && $BATTERY<=60 ))
then
    BATTERY="◼◼◼◼◼◼◻◻◻◻"
elif (( 60<$BATTERY && $BATTERY<=70 ))
then
    BATTERY="◼◼◼◼◼◼◼◻◻◻"
elif (( 70<$BATTERY && $BATTERY<=80 ))
then
    BATTERY="◼◼◼◼◼◼◼◼◻◻"
elif (( 80<$BATTERY && $BATTERY<=90 ))
then
    BATTERY="◼◼◼◼◼◼◼◼◼◻"
else
    BATTERY="◼◼◼◼◼◼◼◼◼◼"
fi

## Main
chosen="$(echo -e "$BATTERY" | $rofi_command -p "$BATTERY_PERCENT%"  -dmenu $active $urgent -selected-row 0)"
