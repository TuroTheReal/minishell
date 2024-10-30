#!/bin/bash

dir=$(pwd)

valgrind --trace-children=yes --show-leak-kinds=all --show-reachable=yes --leak-check=full --track-origins=yes --track-fds=yes --child-silent-after-fork=yes --suppressions=readline.supp ./minishell
