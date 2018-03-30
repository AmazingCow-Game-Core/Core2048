//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Core2048_Utils.h                                              //
//  Project   : Core2048                                                      //
//  Date      : Feb 12, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017, 2018                                       //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

//----------------------------------------------------------------------------//
// Namespace                                                                  //
//----------------------------------------------------------------------------//
#define NS_CORE2048_BEGIN namespace Core2048 {
#define NS_CORE2048_END   }
#define USING_NS_CORE2048 using namespace Core2048


//----------------------------------------------------------------------------//
// Version                                                                    //
//----------------------------------------------------------------------------//
// The core version number.
//   Do not edit manually this...
//   Instead it should be changed by update_version.sh script
//   because it'll update the Doxygen stuff as well.
#define COW_CORE2048_VERSION_MAJOR    "0"
#define COW_CORE2048_VERSION_MINOR    "1"
#define COW_CORE2048_VERSION_REVISION "0"

#define COW_CORE2048_VERSION       \
    COW_CORE2048_VERSION_MAJOR "." \
    COW_CORE2048_VERSION_MINOR "." \
    COW_CORE2048_VERSION_REVISION
