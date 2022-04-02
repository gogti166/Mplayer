#ifndef __CDEF_H__
#define __CDEF_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>

using namespace std;
/*****************************************************************
*                             cdef                               *
******************************************************************/
#define     False     0x00
#define     True      0x01

#ifndef FALSE
#define     FALSE     0
#endif
#ifndef TRUE
#define     TRUE      1
#endif

typedef unsigned char        uint8;
typedef unsigned short       uint16;
typedef unsigned int         uint32;
typedef unsigned long long   uint64;

typedef signed char          int8_t;
typedef signed short         int16_t;
typedef signed int           int32_t;
typedef signed long long     int64_t;

typedef unsigned char        boolean;

typedef void(*CDEF_tFuncPtr) (void);
typedef CDEF_tFuncPtr tFuncPtr;

#ifdef AES_CRYPTION
typedef uint8           Esc_UINT8 ;
typedef uint16          Esc_UINT16;
typedef uint32          Esc_UINT32;
typedef Esc_UINT8       Esc_ERROR;
    /** The NULL pointer */
#define Esc_NULL_PTR    ((void*)0)
#endif

#endif