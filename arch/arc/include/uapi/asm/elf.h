<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित _UAPI__ASM_ARC_ELF_H
#घोषणा _UAPI__ASM_ARC_ELF_H

#समावेश <यंत्र/ptrace.h>		/* क्रम user_regs_काष्ठा */

/* Machine specअगरic ELF Hdr flags */
#घोषणा EF_ARC_OSABI_MSK	0x00000f00

#घोषणा EF_ARC_OSABI_V3		0x00000300   /* v3 (no legacy syscalls) */
#घोषणा EF_ARC_OSABI_V4		0x00000400   /* v4 (64bit data any reg align) */

#अगर __GNUC__ < 6
#घोषणा EF_ARC_OSABI_CURRENT	EF_ARC_OSABI_V3
#अन्यथा
#घोषणा EF_ARC_OSABI_CURRENT	EF_ARC_OSABI_V4
#पूर्ण_अगर

प्रकार अचिन्हित दीर्घ elf_greg_t;
प्रकार अचिन्हित दीर्घ elf_fpregset_t;

#घोषणा ELF_NGREG	(माप(काष्ठा user_regs_काष्ठा) / माप(elf_greg_t))
#घोषणा ELF_ARCV2REG	(माप(काष्ठा user_regs_arcv2) / माप(elf_greg_t))

प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

#पूर्ण_अगर
