<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_PROCESSOR_H
#घोषणा _ASM_RISCV_PROCESSOR_H

#समावेश <linux/स्थिर.h>

#समावेश <vdso/processor.h>

#समावेश <यंत्र/ptrace.h>

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE	PAGE_ALIGN(TASK_SIZE / 3)

#घोषणा STACK_TOP		TASK_SIZE
#घोषणा STACK_TOP_MAX		STACK_TOP
#घोषणा STACK_ALIGN		16

#अगर_अघोषित __ASSEMBLY__

काष्ठा task_काष्ठा;
काष्ठा pt_regs;

/* CPU-specअगरic state of a task */
काष्ठा thपढ़ो_काष्ठा अणु
	/* Callee-saved रेजिस्टरs */
	अचिन्हित दीर्घ ra;
	अचिन्हित दीर्घ sp;	/* Kernel mode stack */
	अचिन्हित दीर्घ s[12];	/* s[0]: frame poपूर्णांकer */
	काष्ठा __riscv_d_ext_state ख_स्थितिe;
	अचिन्हित दीर्घ bad_cause;
पूर्ण;

#घोषणा INIT_THREAD अणु					\
	.sp = माप(init_stack) + (दीर्घ)&init_stack,	\
पूर्ण

#घोषणा task_pt_regs(tsk)						\
	((काष्ठा pt_regs *)(task_stack_page(tsk) + THREAD_SIZE		\
			    - ALIGN(माप(काष्ठा pt_regs), STACK_ALIGN)))

#घोषणा KSTK_EIP(tsk)		(task_pt_regs(tsk)->epc)
#घोषणा KSTK_ESP(tsk)		(task_pt_regs(tsk)->sp)


/* Do necessary setup to start up a newly executed thपढ़ो. */
बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs *regs,
			अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp);

/* Free all resources held by a thपढ़ो. */
अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

बाह्य अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);


अटल अंतरभूत व्योम रुको_क्रम_पूर्णांकerrupt(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("wfi");
पूर्ण

काष्ठा device_node;
पूर्णांक riscv_of_processor_hartid(काष्ठा device_node *node);
पूर्णांक riscv_of_parent_hartid(काष्ठा device_node *node);

बाह्य व्योम riscv_fill_hwcap(व्योम);
बाह्य पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_RISCV_PROCESSOR_H */
