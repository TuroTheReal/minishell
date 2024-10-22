#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-fds=yes --child-silent-after-fork=yes --suppressions=readline.supp ./minishell
#--trace-children=yes