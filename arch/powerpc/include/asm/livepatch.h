<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * livepatch.h - घातerpc-specअगरic Kernel Live Patching Core
 *
 * Copyright (C) 2015-2016, SUSE, IBM Corp.
 */
#अगर_अघोषित _ASM_POWERPC_LIVEPATCH_H
#घोषणा _ASM_POWERPC_LIVEPATCH_H

#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/sched/task_stack.h>

#अगर_घोषित CONFIG_LIVEPATCH
अटल अंतरभूत व्योम klp_arch_set_pc(काष्ठा ftrace_regs *fregs, अचिन्हित दीर्घ ip)
अणु
	काष्ठा pt_regs *regs = ftrace_get_regs(fregs);

	regs->nip = ip;
पूर्ण

#घोषणा klp_get_ftrace_location klp_get_ftrace_location
अटल अंतरभूत अचिन्हित दीर्घ klp_get_ftrace_location(अचिन्हित दीर्घ faddr)
अणु
	/*
	 * Live patch works only with -mprofile-kernel on PPC. In this हाल,
	 * the ftrace location is always within the first 16 bytes.
	 */
	वापस ftrace_location_range(faddr, faddr + 16);
पूर्ण

अटल अंतरभूत व्योम klp_init_thपढ़ो_info(काष्ठा task_काष्ठा *p)
अणु
	/* + 1 to account क्रम STACK_END_MAGIC */
	task_thपढ़ो_info(p)->livepatch_sp = end_of_stack(p) + 1;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम klp_init_thपढ़ो_info(काष्ठा task_काष्ठा *p) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_LIVEPATCH */

#पूर्ण_अगर /* _ASM_POWERPC_LIVEPATCH_H */
