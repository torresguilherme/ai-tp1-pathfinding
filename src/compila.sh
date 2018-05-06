#!/bin/bash

CC="g++"
CFLAGS="-no-pie -Wall -std=c++17"
SRCS="main.cpp common.cpp ids.cpp bestFirst.cpp"
HDRS="common.h ids.h bestFirst.h"
BIN=" exec"
DB="gdb"

if [ "$1" ] && [ $1 == "clean" ]
then
	echo "Deleting objects..."
	for SRC in $SRCS
	do
		OBJ=${SRC/%.cpp/.o}
		rm -f $OBJ
	done
	echo "Done!"
	exit
fi

build_obj()
{
	echo "Compiling objects..."
	for SRC in $SRCS
	do
		OBJ=${SRC/%.cpp/.o}
		OBJS="$OBJ $OBJS"
		for HDR in $HDRS
		do
			if [ $HDR -nt $OBJ ] || [ $SRC -nt $OBJ ]
			then
				echo "Compiling $SRC"
				$CC $CFLAGS -c $SRC -o $OBJ
			fi
		done
	done
	echo "Done compiling the objects!"
}

link()
{
	for OBJ in $OBJS
	do
		if [ $OBJ -nt $BIN ]
		then
			echo "Linking objects..."
			$CC $CFLAGS $OBJS -o $BIN
			break
		fi
	done
}

build_obj
link
echo "Done!"
