<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_ASM_POWERPC_MMAN_H
#घोषणा _UAPI_ASM_POWERPC_MMAN_H

#समावेश <यंत्र-generic/mman-common.h>


#घोषणा PROT_SAO	0x10		/* Strong Access Ordering */

#घोषणा MAP_RENAME      MAP_ANONYMOUS   /* In SunOS terminology */
#घोषणा MAP_NORESERVE   0x40            /* करोn't reserve swap pages */
#घोषणा MAP_LOCKED	0x80

#घोषणा MAP_GROWSDOWN	0x0100		/* stack-like segment */
#घोषणा MAP_DENYWRITE	0x0800		/* ETXTBSY */
#घोषणा MAP_EXECUTABLE	0x1000		/* mark it as an executable */


#घोषणा MCL_CURRENT     0x2000          /* lock all currently mapped pages */
#घोषणा MCL_FUTURE      0x4000          /* lock all additions to address space */
#घोषणा MCL_ONFAULT	0x8000		/* lock all pages that are faulted in */

/* Override any generic PKEY permission defines */
#घोषणा PKEY_DISABLE_EXECUTE   0x4
#अघोषित PKEY_ACCESS_MASK
#घोषणा PKEY_ACCESS_MASK       (PKEY_DISABLE_ACCESS |\
				PKEY_DISABLE_WRITE  |\
				PKEY_DISABLE_EXECUTE)
#पूर्ण_अगर /* _UAPI_ASM_POWERPC_MMAN_H */
