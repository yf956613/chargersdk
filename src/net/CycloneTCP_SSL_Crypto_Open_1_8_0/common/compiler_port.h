/**
 * @file compiler_port.h
 * @brief Compiler specific definitions
 *
 * @section License
 *
 * Copyright (C) 2010-2017 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.8.0
 **/

#ifndef _COMPILER_PORT_H
#define _COMPILER_PORT_H

//Dependencies
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

//C++ guard
#ifdef __cplusplus
   extern "C" {
#endif

//Types
typedef char char_t;
typedef signed int int_t;
typedef unsigned int uint_t;
typedef uint32_t systime_t;

#if !defined(R_TYPEDEFS_H) && !defined(USE_CHIBIOS_2)
   typedef int bool_t;
#endif

#if defined(__linux__)
   #define PRIuSIZE "zu"
   #define PRIuTIME "lu"
#elif defined(_WIN32)
   #define PRIuSIZE "Iu"
   #define PRIuTIME "lu"
#elif defined(__XC32)
   #define PRIuSIZE "u"
   #define PRIuTIME "u"
#elif defined(__CWCC__)
   #define PRIu8 "u"
   #define PRIu16 "u"
   #define PRIu32 "u"
   #define PRIx8 "x"
   #define PRIx16 "x"
   #define PRIx32 "x"
   #define PRIX8 "X"
   #define PRIX16 "X"
   #define PRIX32 "X"
   #define PRIuSIZE "u"
   #define PRIuTIME "u" 
#else
    #undef PRIu8
    #undef PRIu16
    #undef PRIu32
    #undef PRIx8
    #undef PRIx16
    #undef PRIx32
    #undef PRIX8
    #undef PRIX16
    #undef PRIX32
       
    #define PRIu8 "u"
    #define PRIu16 "u"
    #define PRIu32 "u"
    #define PRIx8 "x"
    #define PRIx16 "x"
    #define PRIx32 "x"
    #define PRIX8 "X"
    #define PRIX16 "X"
    #define PRIX32 "X"
    #define PRIuSIZE "u"
    //#define PRIuTIME "u"
   #define PRIuSIZE "u"
   #define PRIuTIME "lu"
#endif

#if defined(__CC_ARM)
   #undef PRIu8
   #define PRIu8 "u"
   #undef PRIu16
   #define PRIu16 "u"
#endif

//CodeWarrior compiler?
#if defined(__CWCC__)
   typedef uint32_t time_t;
   int strcasecmp(const char *s1, const char *s2);
   int strncasecmp(const char *s1, const char *s2, size_t n);
   char *strtok_r(char *s, const char *delim, char **last);
//TI ARM C compiler?
#elif defined(__TI_ARM__)
   int strcasecmp(const char *s1, const char *s2);
   int strncasecmp(const char *s1, const char *s2, size_t n);
   char *strtok_r(char *s, const char *delim, char **last);
#endif

//Microchip XC32 compiler?
#if defined(__XC32)
   #define sprintf _sprintf
   int sprintf(char * str, const char * format, ...);
   int strcasecmp(const char *s1, const char *s2);
   int strncasecmp(const char *s1, const char *s2, size_t n);
   char *strtok_r(char *s, const char *delim, char **last);
#endif

//GCC compiler?
#if defined(__GNUC__)
   #undef __start_packed
   #define __start_packed
   #undef __end_packed
   #define __end_packed __attribute__((__packed__))
//Keil MDK-ARM compiler?
#elif defined(__CC_ARM)
   #pragma anon_unions
   #undef __start_packed
   #define __start_packed __packed
   #undef __end_packed
   #define __end_packed
//IAR C compiler?
#elif defined(__IAR_SYSTEMS_ICC__)
   #undef __start_packed
   #define __start_packed __packed
   #undef __end_packed
   #define __end_packed
//CodeWarrior compiler?
#elif defined(__CWCC__)
   #undef __start_packed
   #define __start_packed
   #undef __end_packed
   #define __end_packed
//TI ARM C compiler?
#elif defined(__TI_ARM__)
   #undef __start_packed
   #define __start_packed
   #undef __end_packed
   #define __end_packed __attribute__((__packed__))
//Win32 compiler?
#elif defined(_WIN32)
   #undef interface
   #undef __start_packed
   #define __start_packed
   #undef __end_packed
   #define __end_packed
#endif

//C++ guard
#ifdef __cplusplus
   }
#endif

#endif
