#!/bin/sh

current=$(pacmd dump-volumes | awk 'NR==1{print $8}' | sed 's/\%//')

higher=$((10+$current))

[ $higher -gt 153 ] && higher="153"

pactl set-sink-volume 0 "$higher%"

bash xsetroot_.sh
