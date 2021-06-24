<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * livepatch.h - s390-specअगरic Kernel Live Patching Core
 *
 *  Copyright (c) 2013-2015 SUSE
 *   Authors: Jiri Kosina
 *	      Vojtech Pavlik
 *	      Jiri Slaby
 */

#अगर_अघोषित ASM_LIVEPATCH_H
#घोषणा ASM_LIVEPATCH_H

#समावेश <linux/ftrace.h>
#समावेश <यंत्र/ptrace.h>

अटल अंतरभूत व्योम klp_arch_set_pc(काष्ठा ftrace_regs *fregs, अचिन्हित दीर्घ ip)
अणु
	काष्ठा pt_regs *regs = ftrace_get_regs(fregs);

	regs->psw.addr = ip;
पूर्ण

#पूर्ण_अगर
