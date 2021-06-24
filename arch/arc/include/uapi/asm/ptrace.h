<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Amit Bhor, Sameer Dhavale: Codito Technologies 2004
 */

#अगर_अघोषित _UAPI__ASM_ARC_PTRACE_H
#घोषणा _UAPI__ASM_ARC_PTRACE_H

#घोषणा PTRACE_GET_THREAD_AREA	25

#अगर_अघोषित __ASSEMBLY__
/*
 * Userspace ABI: Register state needed by
 *  -ptrace (gdbserver)
 *  -sigcontext (SA_SIGNINFO संकेत frame)
 *
 * This is to decouple pt_regs from user-space ABI, to be able to change it
 * w/o affecting the ABI.
 *
 * The पूर्णांकermediate pad,pad2 are relics of initial layout based on pt_regs
 * क्रम optimizations when copying pt_regs to/from user_regs_काष्ठा.
 * We no दीर्घer need them, but can't be changed as they are part of ABI now.
 *
 * Also, sigcontext only care about the scratch regs as that is what we really
 * save/restore क्रम संकेत handling. However gdb also uses the same काष्ठा
 * hence callee regs need to be in there too.
*/
काष्ठा user_regs_काष्ठा अणु

	अचिन्हित दीर्घ pad;
	काष्ठा अणु
		अचिन्हित दीर्घ bta, lp_start, lp_end, lp_count;
		अचिन्हित दीर्घ status32, ret, blink, fp, gp;
		अचिन्हित दीर्घ r12, r11, r10, r9, r8, r7, r6, r5, r4, r3, r2, r1, r0;
		अचिन्हित दीर्घ sp;
	पूर्ण scratch;
	अचिन्हित दीर्घ pad2;
	काष्ठा अणु
		अचिन्हित दीर्घ r25, r24, r23, r22, r21, r20;
		अचिन्हित दीर्घ r19, r18, r17, r16, r15, r14, r13;
	पूर्ण callee;
	अचिन्हित दीर्घ efa;	/* अवरोध pt addr, क्रम अवरोध poपूर्णांकs in delay slots */
	अचिन्हित दीर्घ stop_pc;	/* give dbg stop_pc after ensuring brkpt trap */
पूर्ण;

काष्ठा user_regs_arcv2 अणु
	अचिन्हित दीर्घ r30, r58, r59;
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI__ASM_ARC_PTRACE_H */
