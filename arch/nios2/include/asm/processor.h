<शैली गुरु>
/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd
 * Copyright (C) 2001 Ken Hill (khill@microtronix.com)
 *                    Vic Phillips (vic@microtronix.com)
 *
 * based on SPARC यंत्र/processor_32.h which is:
 *
 * Copyright (C) 1994 David S. Miller
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_PROCESSOR_H
#घोषणा _ASM_NIOS2_PROCESSOR_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <यंत्र/page.h>

#घोषणा NIOS2_FLAG_KTHREAD	0x00000001	/* task is a kernel thपढ़ो */

#घोषणा NIOS2_OP_NOP		0x1883a
#घोषणा NIOS2_OP_BREAK		0x3da03a

#अगर_घोषित __KERNEL__

#घोषणा STACK_TOP	TASK_SIZE
#घोषणा STACK_TOP_MAX	STACK_TOP

#पूर्ण_अगर /* __KERNEL__ */

/* Kuser helpers is mapped to this user space address */
#घोषणा KUSER_BASE		0x1000
#घोषणा KUSER_SIZE		(PAGE_SIZE)
#अगर_अघोषित __ASSEMBLY__

# define TASK_SIZE		0x7FFF0000UL
# define TASK_UNMAPPED_BASE	(PAGE_ALIGN(TASK_SIZE / 3))

/* The Nios processor specअगरic thपढ़ो काष्ठा. */
काष्ठा thपढ़ो_काष्ठा अणु
	काष्ठा pt_regs *kregs;

	/* Context चयन saved kernel state. */
	अचिन्हित दीर्घ ksp;
	अचिन्हित दीर्घ kpsr;
पूर्ण;

#घोषणा INIT_MMAP \
	अणु &init_mm, (0), (0), __pgprot(0x0), VM_READ | VM_WRITE | VM_EXEC पूर्ण

# define INIT_THREAD अणु			\
	.kregs	= शून्य,			\
	.ksp	= 0,			\
	.kpsr	= 0,			\
पूर्ण

बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
			अचिन्हित दीर्घ sp);

काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

बाह्य अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा task_pt_regs(p) \
	((काष्ठा pt_regs *)(THREAD_SIZE + task_stack_page(p)) - 1)

/* Used by procfs */
#घोषणा KSTK_EIP(tsk)	((tsk)->thपढ़ो.kregs->ea)
#घोषणा KSTK_ESP(tsk)	((tsk)->thपढ़ो.kregs->sp)

#घोषणा cpu_relax()	barrier()

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_NIOS2_PROCESSOR_H */
