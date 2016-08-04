#!/bin/sh
cd /home/pi/share

pwd

ffmpeg -framerate 9 -pattern_type glob -i './video_files/*.bmp' -vcodec mpeg4 -y test.avi

rm ./video_files/*.bmp

echo "Script done"

exit 0
