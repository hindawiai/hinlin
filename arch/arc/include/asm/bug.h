<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_BUG_H
#घोषणा _ASM_ARC_BUG_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/ptrace.h>

काष्ठा task_काष्ठा;

व्योम show_regs(काष्ठा pt_regs *regs);
व्योम show_stacktrace(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
		     स्थिर अक्षर *loglvl);
व्योम show_kernel_fault_diag(स्थिर अक्षर *str, काष्ठा pt_regs *regs,
			    अचिन्हित दीर्घ address);
व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, अचिन्हित दीर्घ address);

#घोषणा BUG()	करो अणु								\
	pr_warn("BUG: failure at %s:%d/%s()!\n", __खाता__, __LINE__, __func__); \
	barrier_beक्रमe_unreachable();						\
	__builtin_trap();							\
पूर्ण जबतक (0)

#घोषणा HAVE_ARCH_BUG

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर
