<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* elf-fdpic.h: FDPIC ELF load map
 *
 * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_ELF_FDPIC_H
#घोषणा _UAPI_LINUX_ELF_FDPIC_H

#समावेश <linux/elf.h>

#घोषणा PT_GNU_STACK    (PT_LOOS + 0x474e551)

/* segment mappings क्रम ELF FDPIC libraries/executables/पूर्णांकerpreters */
काष्ठा elf32_fdpic_loadseg अणु
	Elf32_Addr	addr;		/* core address to which mapped */
	Elf32_Addr	p_vaddr;	/* VMA recorded in file */
	Elf32_Word	p_memsz;	/* allocation size recorded in file */
पूर्ण;

काष्ठा elf32_fdpic_loadmap अणु
	Elf32_Half	version;	/* version of these काष्ठाures, just in हाल... */
	Elf32_Half	nsegs;		/* number of segments */
	काष्ठा elf32_fdpic_loadseg segs[];
पूर्ण;

#घोषणा ELF32_FDPIC_LOADMAP_VERSION	0x0000

#पूर्ण_अगर /* _UAPI_LINUX_ELF_FDPIC_H */
