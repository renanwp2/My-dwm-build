#!/bin/sh

#current=$(pacmd dump-volumes | awk 'NR==1{print $8}' | sed 's/\%//')

pactl set-sink-volume 0 -10%

bash xsetroot_.sh
