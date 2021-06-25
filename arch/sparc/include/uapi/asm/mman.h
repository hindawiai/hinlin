<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__SPARC_MMAN_H__
#घोषणा _UAPI__SPARC_MMAN_H__

#समावेश <यंत्र-generic/mman-common.h>

/* SunOS'अगरied... */

#घोषणा PROT_ADI	0x10		/* ADI enabled */

#घोषणा MAP_RENAME      MAP_ANONYMOUS   /* In SunOS terminology */
#घोषणा MAP_NORESERVE   0x40            /* करोn't reserve swap pages */
#घोषणा MAP_INHERIT     0x80            /* SunOS करोesn't करो this, but... */
#घोषणा MAP_LOCKED      0x100           /* lock the mapping */
#घोषणा _MAP_NEW        0x80000000      /* Binary compatibility is fun... */

#घोषणा MAP_GROWSDOWN	0x0200		/* stack-like segment */
#घोषणा MAP_DENYWRITE	0x0800		/* ETXTBSY */
#घोषणा MAP_EXECUTABLE	0x1000		/* mark it as an executable */

#घोषणा MCL_CURRENT     0x2000          /* lock all currently mapped pages */
#घोषणा MCL_FUTURE      0x4000          /* lock all additions to address space */
#घोषणा MCL_ONFAULT	0x8000		/* lock all pages that are faulted in */

#पूर्ण_अगर /* _UAPI__SPARC_MMAN_H__ */
