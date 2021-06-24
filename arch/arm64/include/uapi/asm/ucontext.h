<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#अगर_अघोषित _UAPI__ASM_UCONTEXT_H
#घोषणा _UAPI__ASM_UCONTEXT_H

#समावेश <linux/types.h>

काष्ठा ucontext अणु
	अचिन्हित दीर्घ	  uc_flags;
	काष्ठा ucontext	 *uc_link;
	stack_t		  uc_stack;
	sigset_t	  uc_sigmask;
	/* glibc uses a 1024-bit sigset_t */
	__u8		  __unused[1024 / 8 - माप(sigset_t)];
	/* last क्रम future expansion */
	काष्ठा sigcontext uc_mcontext;
पूर्ण;

#पूर्ण_अगर /* _UAPI__ASM_UCONTEXT_H */
