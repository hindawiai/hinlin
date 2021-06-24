<शैली गुरु>
/*	BSDI osd_defs.h,v 1.4 1998/06/03 19:14:58 karels Exp	*/
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

#अगर_अघोषित		_OSD_DEFS_H
#घोषणा		_OSD_DEFS_H

/*File - OSD_DEFS.H
 ****************************************************************************
 *
 *Description:
 *
 *	This file contains the OS dependent defines.  This file is included
 *in osd_util.h and provides the OS specअगरic defines क्रम that file.
 *
 *Copyright Distributed Processing Technology, Corp.
 *	  140 Candace Dr.
 *	  Maitland, Fl.	32751   USA
 *	  Phone: (407) 830-5522  Fax: (407) 260-5366
 *	  All Rights Reserved
 *
 *Author:	Doug Anderson
 *Date:		1/31/94
 *
 *Editors:
 *
 *Remarks:
 *
 *
 *****************************************************************************/


/*Definitions - Defines & Constants ----------------------------------------- */

  /* Define the operating प्रणाली */
#अगर (defined(__linux__))
# define _DPT_LINUX
#या_अगर (defined(__bsdi__))
# define _DPT_BSDI
#या_अगर (defined(__FreeBSD__))
# define _DPT_FREE_BSD
#अन्यथा
# define _DPT_SCO
#पूर्ण_अगर

#अगर defined (ZIL_CURSES)
#घोषणा		_DPT_CURSES
#अन्यथा
#घोषणा         _DPT_MOTIF
#पूर्ण_अगर

  /* Redefine 'far' to nothing - no far poपूर्णांकer type required in UNIX */
#घोषणा		far

  /* Define the mutually exclusive semaphore type */
#घोषणा		SEMAPHORE_T	अचिन्हित पूर्णांक *
  /* Define a handle to a DLL */
#घोषणा		DLL_HANDLE_T	अचिन्हित पूर्णांक *

#पूर्ण_अगर
