<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <as-layout.h>
#समावेश <mem_user.h>
#समावेश <skas.h>
#समावेश <os.h>

व्योम flush_thपढ़ो(व्योम)
अणु
	व्योम *data = शून्य;
	पूर्णांक ret;

	arch_flush_thपढ़ो(&current->thपढ़ो.arch);

	ret = unmap(&current->mm->context.id, 0, TASK_SIZE, 1, &data);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "flush_thread - clearing address space failed, "
		       "err = %d\n", ret);
		क्रमce_sig(SIGKILL);
	पूर्ण
	get_safe_रेजिस्टरs(current_pt_regs()->regs.gp,
			   current_pt_regs()->regs.fp);

	__चयन_mm(&current->mm->context.id);
पूर्ण

व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ eip, अचिन्हित दीर्घ esp)
अणु
	PT_REGS_IP(regs) = eip;
	PT_REGS_SP(regs) = esp;
	current->ptrace &= ~PT_DTRACE;
#अगर_घोषित SUBARCH_EXECVE1
	SUBARCH_EXECVE1(regs->regs);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(start_thपढ़ो);
