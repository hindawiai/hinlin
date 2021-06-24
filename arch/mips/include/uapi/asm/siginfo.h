<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998, 1999, 2001, 2003 Ralf Baechle
 * Copyright (C) 2000, 2001 Silicon Graphics, Inc.
 */
#अगर_अघोषित _UAPI_ASM_SIGINFO_H
#घोषणा _UAPI_ASM_SIGINFO_H


#घोषणा __ARCH_SIGEV_PREAMBLE_SIZE (माप(दीर्घ) + 2*माप(पूर्णांक))
#अघोषित __ARCH_SI_TRAPNO /* exception code needs to fill this ...  */

#घोषणा __ARCH_HAS_SWAPPED_SIGINFO

#समावेश <यंत्र-generic/siginfo.h>

/*
 * si_code values
 * Again these have been chosen to be IRIX compatible.
 */
#अघोषित SI_ASYNCIO
#अघोषित SI_TIMER
#अघोषित SI_MESGQ
#घोषणा SI_ASYNCIO	-2	/* sent by AIO completion */
#घोषणा SI_TIMER	-3	/* sent by समयr expiration */
#घोषणा SI_MESGQ	-4	/* sent by real समय mesq state change */

#पूर्ण_अगर /* _UAPI_ASM_SIGINFO_H */
