#!/usr/bin/env sh
##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : download-dependencies.sh                                      ##
##  Project   : Core2048                                                      ##
##  Date      : Mar 30, 2018                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2018                                             ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/acow_shellscript_utils.sh


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
cd $(get_script_dir)/..;

github_clone_repos                     \
    ./libs                             \
    AmazingCow-Libs/acow_c_goodies     \
    AmazingCow-Libs/acow_cpp_goodies   \
    AmazingCow-Libs/acow_math_goodies  \
    AmazingCow-Libs/CoreAssert         \
    AmazingCow-Libs/CoreGame           \
    AmazingCow-Libs/CoreRandom         \
    AmazingCow-Libs/libtermcolor       \
    AmazingCow-Libs/acow_posix_goodies \