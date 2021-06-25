<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित _UAPI__ASM_OPENRISC_PTRACE_H
#घोषणा _UAPI__ASM_OPENRISC_PTRACE_H

#अगर_अघोषित __ASSEMBLY__
/*
 * This is the layout of the regset वापसed by the GETREGSET ptrace call
 */
काष्ठा user_regs_काष्ठा अणु
	/* GPR R0-R31... */
	अचिन्हित दीर्घ gpr[32];
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ sr;
पूर्ण;
#पूर्ण_अगर


#पूर्ण_अगर /* _UAPI__ASM_OPENRISC_PTRACE_H */
