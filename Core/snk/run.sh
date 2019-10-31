#!/bin/bash

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./snk_build/snk "$@"
#./snk_build/irl
