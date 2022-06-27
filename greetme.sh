#!/bin/bash

read NAME

sleep 2

VAR="hi"
export VAR2="hello"

echo "hello $(whoami)"
echo "Test done $NAME"

sleep 1

echo "trying the vars VAR = $VAR VAR2 = $VAR2"
