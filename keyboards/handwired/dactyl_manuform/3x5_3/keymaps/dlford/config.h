/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2021 @dlford
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define EE_HANDS // ./util/docker_build.sh crkbd:dlford:dfu-split-[left|right] (or avrdude-split[left|right])

// Features I don't want, remove to save space
// #define NO_ACTION_ONESHOT // Used by caps word
#define NO_ACTION_FUNCTION
#define NO_ACTION_MACRO
#define NO_USB_STARTUP_CHECK
#ifdef NKRO_ENABLE
#    undef NKRO_ENABLE
#endif

#ifndef NO_DEBUG
#    define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#    define NO_PRINT
#endif // !NO_PRINT
