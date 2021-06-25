<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASM_NDS32_PROCESSOR_H
#घोषणा __ASM_NDS32_PROCESSOR_H

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/sigcontext.h>

#घोषणा KERNEL_STACK_SIZE	PAGE_SIZE
#घोषणा STACK_TOP	TASK_SIZE
#घोषणा STACK_TOP_MAX   TASK_SIZE

काष्ठा cpu_context अणु
	अचिन्हित दीर्घ r6;
	अचिन्हित दीर्घ r7;
	अचिन्हित दीर्घ r8;
	अचिन्हित दीर्घ r9;
	अचिन्हित दीर्घ r10;
	अचिन्हित दीर्घ r11;
	अचिन्हित दीर्घ r12;
	अचिन्हित दीर्घ r13;
	अचिन्हित दीर्घ r14;
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ sp;
पूर्ण;

काष्ठा thपढ़ो_काष्ठा अणु
	काष्ठा cpu_context cpu_context;	/* cpu context */
	/* fault info     */
	अचिन्हित दीर्घ address;
	अचिन्हित दीर्घ trap_no;
	अचिन्हित दीर्घ error_code;

	काष्ठा fpu_काष्ठा fpu;
पूर्ण;

#घोषणा INIT_THREAD  अणु	पूर्ण

#अगर_घोषित __NDS32_EB__
#घोषणा PSW_DE	PSW_mskBE
#अन्यथा
#घोषणा PSW_DE	0x0
#पूर्ण_अगर

#अगर_घोषित CONFIG_WBNA
#घोषणा PSW_valWBNA	PSW_mskWBNA
#अन्यथा
#घोषणा PSW_valWBNA	0x0
#पूर्ण_अगर

#अगर_घोषित CONFIG_HWZOL
#घोषणा	PSW_valINIT (PSW_CPL_ANY | PSW_mskAEN | PSW_valWBNA | PSW_mskDT | PSW_mskIT | PSW_DE | PSW_mskGIE)
#अन्यथा
#घोषणा	PSW_valINIT (PSW_CPL_ANY | PSW_valWBNA | PSW_mskDT | PSW_mskIT | PSW_DE | PSW_mskGIE)
#पूर्ण_अगर

#घोषणा start_thपढ़ो(regs,pc,stack)			\
(अणु							\
	memzero(regs, माप(काष्ठा pt_regs));		\
	क्रमget_syscall(regs);				\
	regs->ipsw = PSW_valINIT;			\
	regs->ir0 = (PSW_CPL_ANY | PSW_valWBNA | PSW_mskDT | PSW_mskIT | PSW_DE | PSW_SYSTEM | PSW_INTL_1);	\
	regs->ipc = pc;					\
	regs->sp = stack;				\
पूर्ण)

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
#घोषणा release_thपढ़ो(thपढ़ो) करो अणु पूर्ण जबतक(0)
#अगर IS_ENABLED(CONFIG_FPU)
#अगर !IS_ENABLED(CONFIG_UNLAZU_FPU)
बाह्य काष्ठा task_काष्ठा *last_task_used_math;
#पूर्ण_अगर
#पूर्ण_अगर

/* Prepare to copy thपढ़ो state - unlazy all lazy status */
#घोषणा prepare_to_copy(tsk)	करो अणु पूर्ण जबतक (0)

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा cpu_relax()			barrier()

#घोषणा task_pt_regs(task) \
	((काष्ठा pt_regs *) (task_stack_page(task) + THREAD_SIZE \
		- 8) - 1)

/*
 * Create a new kernel thपढ़ो
 */
बाह्य पूर्णांक kernel_thपढ़ो(पूर्णांक (*fn) (व्योम *), व्योम *arg, अचिन्हित दीर्घ flags);

#घोषणा KSTK_EIP(tsk)	inकाष्ठाion_poपूर्णांकer(task_pt_regs(tsk))
#घोषणा KSTK_ESP(tsk)	user_stack_poपूर्णांकer(task_pt_regs(tsk))

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_NDS32_PROCESSOR_H */
