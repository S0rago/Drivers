#!/bin/bash

echo "Starting sync...
src="~/Downloads/ToSync/"
dest="/media/soragomint/SP\ UFD\ U3/"
	
if mount | grep -q ' on  $dest'; then
 echo "Drive found"
 echo "Copying..."
 cp -ru "$src*" "$dest/ToSync/"
 cp -ru "$dest/ToSync/*" "$src"
fi

#else mount usb on /media/*MOUNT_POINT*/
echo "DONE"
