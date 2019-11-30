#! /bin/sh
COUNT=5
while true
do
	if [ $COUNT -eq 5 ]; then
		sudo env "PATH=$PATH" python /home/odroid/tensortest/Object_detection_file_old/reset_gsm.py
		COUNT=0
	fi
	sudo env "PATH=$PATH" python /home/odroid/tensortest/Object_detection_file_old/sensors_to_gsm.py
	COUNT=$((COUNT+1))
	echo $COUNT
done
