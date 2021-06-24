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

#अगर_अघोषित __ASM_OPENRISC_SIGCONTEXT_H
#घोषणा __ASM_OPENRISC_SIGCONTEXT_H

#समावेश <यंत्र/ptrace.h>

/* This काष्ठा is saved by setup_frame in संकेत.c, to keep the current
   context जबतक a संकेत handler is executed. It's restored by sys_sigवापस.
*/

काष्ठा sigcontext अणु
	काष्ठा user_regs_काष्ठा regs;  /* needs to be first */
	अचिन्हित दीर्घ oldmask;
पूर्ण;

#पूर्ण_अगर /* __ASM_OPENRISC_SIGCONTEXT_H */
