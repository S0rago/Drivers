#!/bin/bash

echo "Starting sync..."
src="/home/soragomint/Downloads/ToSync/"
dest="/media/soragomint/SP UFD U3"
	
if [ -n $(mount | grep -q ' on  $dest') ]; then
 echo "Drive found"
 echo "From $src"
 echo "to $dest"
 cp -ru "$src"* "$dest/ToSync/"
 cp -ru "$dest/ToSync/"* "$src"
fi

#else mount usb on /media/*MOUNT_POINT*/
echo "DONE"

exit 0
