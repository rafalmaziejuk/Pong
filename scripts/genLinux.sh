#!/bin/sh

if [ $# -ne 1 ]
then
	echo "You need to pass 1 argument!"
	exit
fi

cd ..

if [ "$1" = "clean" ]
then
	make clean
	exit	
elif [ "$1" = "build" ]
then
	./premake5 gmake
	make			
elif [ "$1" = "run" ]
then
	./bin/Debug-linux-x86_64/Pong/Pong		
fi
