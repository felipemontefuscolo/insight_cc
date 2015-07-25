#!/bin/sh

CC=g++

SOURCE=`ls src/*.cpp`
EXEC=`ls src/*.cpp | sed 's/\.cpp//g'`

for i in ${SOURCE}; do
  echo compiling $i
  ${CC} -O3 $i -o ${i/.cpp}
done

echo ""

./src/count  ./tweet_input/tweets.txt

echo "\ndone"
