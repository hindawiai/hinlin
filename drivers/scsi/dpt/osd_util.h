<शैली गुरु>
/*	BSDI osd_util.h,v 1.8 1998/06/03 19:14:58 karels Exp	*/

/*
 * Copyright (c) 1996-1999 Distributed Processing Technology Corporation
 * All rights reserved.
 *
 * Redistribution and use in source क्रमm, with or without modअगरication, are
 * permitted provided that redistributions of source code must retain the
 * above copyright notice, this list of conditions and the following disclaimer.
 *
 * This software is provided `as is' by Distributed Processing Technology and
 * any express or implied warranties, including, but not limited to, the
 * implied warranties of merchantability and fitness क्रम a particular purpose,
 * are disclaimed. In no event shall Distributed Processing Technology be
 * liable क्रम any direct, indirect, incidental, special, exemplary or
 * consequential damages (including, but not limited to, procurement of
 * substitute goods or services; loss of use, data, or profits; or business
 * पूर्णांकerruptions) however caused and on any theory of liability, whether in
 * contract, strict liability, or tort (including negligence or otherwise)
 * arising in any way out of the use of this driver software, even अगर advised
 * of the possibility of such damage.
 *
 */

#अगर_अघोषित         __OSD_UTIL_H
#घोषणा         __OSD_UTIL_H

/*File - OSD_UTIL.H
 ****************************************************************************
 *
 *Description:
 *
 *      This file contains defines and function prototypes that are
 *operating प्रणाली dependent.  The resources defined in this file
 *are not specअगरic to any particular application.
 *
 *Copyright Distributed Processing Technology, Corp.
 *        140 Candace Dr.
 *        Maitland, Fl. 32751   USA
 *        Phone: (407) 830-5522  Fax: (407) 260-5366
 *        All Rights Reserved
 *
 *Author:       Doug Anderson
 *Date:         1/7/94
 *
 *Editors:
 *
 *Remarks:
 *
 *
 *****************************************************************************/


/*Definitions - Defines & Constants ----------------------------------------- */

/*----------------------------- */
/* Operating प्रणाली selections: */
/*----------------------------- */

/*#घोषणा               _DPT_MSDOS      */
/*#घोषणा               _DPT_WIN_3X     */
/*#घोषणा               _DPT_WIN_4X     */
/*#घोषणा               _DPT_WIN_NT     */
/*#घोषणा               _DPT_NETWARE    */
/*#घोषणा               _DPT_OS2        */
/*#घोषणा               _DPT_SCO        */
/*#घोषणा               _DPT_UNIXWARE   */
/*#घोषणा               _DPT_SOLARIS    */
/*#घोषणा               _DPT_NEXTSTEP   */
/*#घोषणा               _DPT_BANYAN     */

/*-------------------------------- */
/* Include the OS specअगरic defines */
/*-------------------------------- */

/*#घोषणा       OS_SELECTION    From Above List */
/*#घोषणा       SEMAPHORE_T     ??? */
/*#घोषणा       DLL_HANDLE_T    ??? */

#अगर (defined(KERNEL) && (defined(__FreeBSD__) || defined(__bsdi__)))
# include        "i386/isa/dpt_osd_defs.h"
#अन्यथा
# include        "osd_defs.h"
#पूर्ण_अगर

#अगर_अघोषित DPT_UNALIGNED
   #घोषणा      DPT_UNALIGNED
#पूर्ण_अगर

#अगर_अघोषित DPT_EXPORT
   #घोषणा      DPT_EXPORT
#पूर्ण_अगर

#अगर_अघोषित DPT_IMPORT
   #घोषणा      DPT_IMPORT
#पूर्ण_अगर

#अगर_अघोषित DPT_RUNTIME_IMPORT
   #घोषणा      DPT_RUNTIME_IMPORT  DPT_IMPORT
#पूर्ण_अगर

/*--------------------- */
/* OS dependent defines */
/*--------------------- */

#अगर defined (_DPT_MSDOS) || defined (_DPT_WIN_3X)
   #घोषणा      _DPT_16_BIT
#अन्यथा
   #घोषणा      _DPT_32_BIT
#पूर्ण_अगर

#अगर defined (_DPT_SCO) || defined (_DPT_UNIXWARE) || defined (_DPT_SOLARIS) || defined (_DPT_AIX) || defined (SNI_MIPS) || defined (_DPT_BSDI) || defined (_DPT_FREE_BSD) || defined(_DPT_LINUX)
   #घोषणा      _DPT_UNIX
#पूर्ण_अगर

#अगर defined (_DPT_WIN_3x) || defined (_DPT_WIN_4X) || defined (_DPT_WIN_NT) \
	    || defined (_DPT_OS2)
   #घोषणा      _DPT_DLL_SUPPORT
#पूर्ण_अगर

#अगर !defined (_DPT_MSDOS) && !defined (_DPT_WIN_3X) && !defined (_DPT_NETWARE)
   #घोषणा      _DPT_PREEMPTIVE
#पूर्ण_अगर

#अगर !defined (_DPT_MSDOS) && !defined (_DPT_WIN_3X)
   #घोषणा      _DPT_MULTI_THREADED
#पूर्ण_अगर

#अगर !defined (_DPT_MSDOS)
   #घोषणा      _DPT_MULTI_TASKING
#पूर्ण_अगर

  /* These exist क्रम platक्रमms that   */
  /* chunk when accessing mis-aligned */
  /* data                             */
#अगर defined (SNI_MIPS) || defined (_DPT_SOLARIS)
   #अगर defined (_DPT_BIG_ENDIAN)
	#अगर !defined (_DPT_STRICT_ALIGN)
            #घोषणा _DPT_STRICT_ALIGN
	#पूर्ण_अगर
   #पूर्ण_अगर
#पूर्ण_अगर

  /* Determine अगर in C or C++ mode */
#अगर_घोषित  __cplusplus
   #घोषणा      _DPT_CPP
#अन्यथा
   #घोषणा      _DPT_C
#पूर्ण_अगर

/*-------------------------------------------------------------------*/
/* Under Solaris the compiler refuses to accept code like:           */
/*   अणु अणु"DPT"पूर्ण, 0, शून्य .... पूर्ण,                                      */
/* and complains about the अणु"DPT"पूर्ण part by saying "cannot use अणु पूर्ण    */
/* to initialize अक्षर*".                                             */
/*                                                                   */
/* By defining these ugly macros we can get around this and also     */
/* not have to copy and #अगर_घोषित large sections of code.  I know that  */
/* these macros are *really* ugly, but they should help reduce       */
/* मुख्यtenance in the दीर्घ run.                                      */
/*                                                                   */
/*-------------------------------------------------------------------*/
#अगर !defined (DPTSQO)
   #अगर defined (_DPT_SOLARIS)
      #घोषणा DPTSQO
      #घोषणा DPTSQC
   #अन्यथा
      #घोषणा DPTSQO अणु
      #घोषणा DPTSQC पूर्ण
   #पूर्ण_अगर  /* solaris */
#पूर्ण_अगर  /* DPTSQO */


/*---------------------- */
/* OS dependent प्रकारs */
/*---------------------- */

#अगर defined (_DPT_MSDOS) || defined (_DPT_SCO)
   #घोषणा BYTE अचिन्हित अक्षर
   #घोषणा WORD अचिन्हित लघु
#पूर्ण_अगर

#अगर_अघोषित _DPT_TYPEDEFS
   #घोषणा _DPT_TYPEDEFS
   प्रकार अचिन्हित अक्षर   uCHAR;
   प्रकार अचिन्हित लघु  uSHORT;
   प्रकार अचिन्हित पूर्णांक    uINT;
   प्रकार अचिन्हित दीर्घ   uLONG;

   प्रकार जोड़ अणु
	 uCHAR        u8[4];
	 uSHORT       u16[2];
	 uLONG        u32;
   पूर्ण access_U;
#पूर्ण_अगर

#अगर !defined (शून्य)
   #घोषणा      शून्य    0
#पूर्ण_अगर


/*Prototypes - function ----------------------------------------------------- */

#अगर_घोषित  __cplusplus
   बाह्य "C" अणु         /* Declare all these functions as "C" functions */
#पूर्ण_अगर

/*------------------------ */
/* Byte reversal functions */
/*------------------------ */

  /* Reverses the byte ordering of a 2 byte variable */
#अगर (!defined(osdSwap2))
 uSHORT       osdSwap2(DPT_UNALIGNED uSHORT *);
#पूर्ण_अगर  // !osdSwap2

  /* Reverses the byte ordering of a 4 byte variable and shअगरts left 8 bits */
#अगर (!defined(osdSwap3))
 uLONG        osdSwap3(DPT_UNALIGNED uLONG *);
#पूर्ण_अगर  // !osdSwap3


#अगर_घोषित  _DPT_NETWARE
   #समावेश "novpass.h" /* For DPT_Bswapl() prototype */
	/* Inline the byte swap */
   #अगर_घोषित __cplusplus
	 अंतरभूत uLONG osdSwap4(uLONG *inLong) अणु
	 वापस *inLong = DPT_Bswapl(*inLong);
	 पूर्ण
   #अन्यथा
	 #घोषणा osdSwap4(inLong)       DPT_Bswapl(inLong)
   #पूर्ण_अगर  // cplusplus
#अन्यथा
	/* Reverses the byte ordering of a 4 byte variable */
# अगर (!defined(osdSwap4))
   uLONG        osdSwap4(DPT_UNALIGNED uLONG *);
# endअगर  // !osdSwap4

  /* The following functions ALWAYS swap regardless of the *
   * presence of DPT_BIG_ENDIAN                            */

   uSHORT       trueSwap2(DPT_UNALIGNED uSHORT *);
   uLONG        trueSwap4(DPT_UNALIGNED uLONG *);

#पूर्ण_अगर  // netware


/*-------------------------------------*
 * Network order swap functions        *
 *                                     *
 * These functions/macros will be used *
 * by the काष्ठाure insert()/extract() *
 * functions.                          *
 *
 * We will enबंद all काष्ठाure       *
 * portability modअगरications inside    *
 * #अगर_घोषितs.  When we are पढ़ोy, we     *
 * will #घोषणा DPT_PORTABLE to begin  *
 * using the modअगरications.            *
 *-------------------------------------*/
uLONG	netSwap4(uLONG val);

#अगर defined (_DPT_BIG_ENDIAN)

// क्रम big-endian we need to swap

#अगर_अघोषित NET_SWAP_2
#घोषणा NET_SWAP_2(x) (((x) >> 8) | ((x) << 8))
#पूर्ण_अगर  // NET_SWAP_2

#अगर_अघोषित NET_SWAP_4
#घोषणा NET_SWAP_4(x) netSwap4((x))
#पूर्ण_अगर  // NET_SWAP_4

#अन्यथा

// क्रम little-endian we करोn't need to करो anything

#अगर_अघोषित NET_SWAP_2
#घोषणा NET_SWAP_2(x) (x)
#पूर्ण_अगर  // NET_SWAP_2

#अगर_अघोषित NET_SWAP_4
#घोषणा NET_SWAP_4(x) (x)
#पूर्ण_अगर  // NET_SWAP_4

#पूर्ण_अगर  // big endian



/*----------------------------------- */
/* Run-समय loadable module functions */
/*----------------------------------- */

  /* Loads the specअगरied run-समय loadable DLL */
DLL_HANDLE_T    osdLoadModule(uCHAR *);
  /* Unloads the specअगरied run-समय loadable DLL */
uSHORT          osdUnloadModule(DLL_HANDLE_T);
  /* Returns a poपूर्णांकer to a function inside a run-समय loadable DLL */
व्योम *          osdGetFnAddr(DLL_HANDLE_T,uCHAR *);

/*--------------------------------------- */
/* Mutually exclusive semaphore functions */
/*--------------------------------------- */

  /* Create a named semaphore */
SEMAPHORE_T     osdCreateNamedSemaphore(अक्षर *);
  /* Create a mutually exlusive semaphore */
SEMAPHORE_T     osdCreateSemaphore(व्योम);
	/* create an event semaphore */
SEMAPHORE_T              osdCreateEventSemaphore(व्योम);
	/* create a named event semaphore */
SEMAPHORE_T             osdCreateNamedEventSemaphore(अक्षर *);

  /* Destroy the specअगरied mutually exclusive semaphore object */
uSHORT          osdDestroySemaphore(SEMAPHORE_T);
  /* Request access to the specअगरied mutually exclusive semaphore */
uLONG           osdRequestSemaphore(SEMAPHORE_T,uLONG);
  /* Release access to the specअगरied mutually exclusive semaphore */
uSHORT          osdReleaseSemaphore(SEMAPHORE_T);
	/* रुको क्रम a event to happen */
uLONG                            osdWaitForEventSemaphore(SEMAPHORE_T, uLONG);
	/* संकेत an event */
uLONG                            osdSignalEventSemaphore(SEMAPHORE_T);
	/* reset the event */
uLONG                            osdResetEventSemaphore(SEMAPHORE_T);

/*----------------- */
/* Thपढ़ो functions */
/*----------------- */

  /* Releases control to the task चयनer in non-preemptive */
  /* multitasking operating प्रणालीs. */
व्योम            osdSwitchThपढ़ोs(व्योम);

  /* Starts a thपढ़ो function */
uLONG   osdStartThपढ़ो(व्योम *,व्योम *);

/* what is my thपढ़ो id */
uLONG osdGetThपढ़ोID(व्योम);

/* wakes up the specअगरed thपढ़ो */
व्योम osdWakeThपढ़ो(uLONG);

/* osd sleep क्रम x milliseconds */
व्योम osdSleep(uLONG);

#घोषणा DPT_THREAD_PRIORITY_LOWEST 0x00
#घोषणा DPT_THREAD_PRIORITY_NORMAL 0x01
#घोषणा DPT_THREAD_PRIORITY_HIGHEST 0x02

uCHAR osdSetThपढ़ोPriority(uLONG tid, uCHAR priority);

#अगर_घोषित __cplusplus
   पूर्ण    /* end the xtern "C" declaration */
#पूर्ण_अगर

#पूर्ण_अगर  /* osd_util_h */
