<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * NVRAM definitions and access functions.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_ASM_POWERPC_NVRAM_H
#घोषणा _UAPI_ASM_POWERPC_NVRAM_H

/* Signatures क्रम nvram partitions */
#घोषणा NVRAM_SIG_SP	0x02	/* support processor */
#घोषणा NVRAM_SIG_OF	0x50	/* खोलो firmware config */
#घोषणा NVRAM_SIG_FW	0x51	/* general firmware */
#घोषणा NVRAM_SIG_HW	0x52	/* hardware (VPD) */
#घोषणा NVRAM_SIG_FLIP	0x5a	/* Apple flip/flop header */
#घोषणा NVRAM_SIG_APPL	0x5f	/* Apple "system" (???) */
#घोषणा NVRAM_SIG_SYS	0x70	/* प्रणाली env vars */
#घोषणा NVRAM_SIG_CFG	0x71	/* config data */
#घोषणा NVRAM_SIG_ELOG	0x72	/* error log */
#घोषणा NVRAM_SIG_VEND	0x7e	/* venकरोr defined */
#घोषणा NVRAM_SIG_FREE	0x7f	/* Free space */
#घोषणा NVRAM_SIG_OS	0xa0	/* OS defined */
#घोषणा NVRAM_SIG_PANIC	0xa1	/* Apple OSX "panic" */


/* PowerMac specअगरic nvram stuffs */

क्रमागत अणु
	pmac_nvram_OF,		/* Open Firmware partition */
	pmac_nvram_XPRAM,	/* MacOS XPRAM partition */
	pmac_nvram_NR		/* MacOS Name Registry partition */
पूर्ण;


/* Some offsets in XPRAM */
#घोषणा PMAC_XPRAM_MACHINE_LOC	0xe4
#घोषणा PMAC_XPRAM_SOUND_VOLUME	0x08

/* Machine location काष्ठाure in PowerMac XPRAM */
काष्ठा pmac_machine_location अणु
	अचिन्हित पूर्णांक	latitude;	/* 2+30 bit Fractional number */
	अचिन्हित पूर्णांक	दीर्घitude;	/* 2+30 bit Fractional number */
	अचिन्हित पूर्णांक	delta;		/* mix of GMT delta and DLS */
पूर्ण;

/*
 * /dev/nvram ioctls
 *
 * Note that PMAC_NVRAM_GET_OFFSET is still supported, but is
 * definitely obsolete. Do not use it अगर you can aव्योम it
 */

#घोषणा OBSOLETE_PMAC_NVRAM_GET_OFFSET \
				_IOWR('p', 0x40, पूर्णांक)

#घोषणा IOC_NVRAM_GET_OFFSET	_IOWR('p', 0x42, पूर्णांक)	/* Get NVRAM partition offset */
#घोषणा IOC_NVRAM_SYNC		_IO('p', 0x43)		/* Sync NVRAM image */

#पूर्ण_अगर /* _UAPI_ASM_POWERPC_NVRAM_H */
