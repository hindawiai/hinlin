<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_PROCESSOR_H
#घोषणा _ASM_MICROBLAZE_PROCESSOR_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <यंत्र/entry.h>
#समावेश <यंत्र/current.h>

# अगरndef __ASSEMBLY__
/* from kernel/cpu/mb.c */
बाह्य स्थिर काष्ठा seq_operations cpuinfo_op;

# define cpu_relax()		barrier()

#घोषणा task_pt_regs(tsk) \
		(((काष्ठा pt_regs *)(THREAD_SIZE + task_stack_page(tsk))) - 1)

/* Do necessary setup to start up a newly executed thपढ़ो. */
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ usp);

बाह्य व्योम ret_from_विभाजन(व्योम);
बाह्य व्योम ret_from_kernel_thपढ़ो(व्योम);

# endअगर /* __ASSEMBLY__ */

/*
 * This is used to define STACK_TOP, and with MMU it must be below
 * kernel base to select the correct PGD when handling MMU exceptions.
 */
# define TASK_SIZE	(CONFIG_KERNEL_START)

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
# define TASK_UNMAPPED_BASE	(TASK_SIZE / 8 * 3)

# define THREAD_KSP	0

#  अगरndef __ASSEMBLY__

/* If you change this, you must change the associated assembly-languages
 * स्थिरants defined below, THREAD_*.
 */
काष्ठा thपढ़ो_काष्ठा अणु
	/* kernel stack poपूर्णांकer (must be first field in काष्ठाure) */
	अचिन्हित दीर्घ	ksp;
	अचिन्हित दीर्घ	ksp_limit;	/* अगर ksp <= ksp_limit stack overflow */
	व्योम		*pgdir;		/* root of page-table tree */
	काष्ठा pt_regs	*regs;		/* Poपूर्णांकer to saved रेजिस्टर state */
पूर्ण;

#  define INIT_THREAD अणु \
	.ksp   = माप init_stack + (अचिन्हित दीर्घ)init_stack, \
	.pgdir = swapper_pg_dir, \
पूर्ण

/* Free all resources held by a thपढ़ो. */
अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

/* The size allocated क्रम kernel stacks. This _must_ be a घातer of two! */
# define KERNEL_STACK_SIZE	0x2000

/* Return some info about the user process TASK.  */
#  define task_tos(task)	((अचिन्हित दीर्घ)(task) + KERNEL_STACK_SIZE)
#  define task_regs(task) ((काष्ठा pt_regs *)task_tos(task) - 1)

#  define task_pt_regs_plus_args(tsk) \
	((व्योम *)task_pt_regs(tsk))

#  define task_sp(task)	(task_regs(task)->r1)
#  define task_pc(task)	(task_regs(task)->pc)
/* Grotty old names क्रम some.  */
#  define KSTK_EIP(task)	(task_pc(task))
#  define KSTK_ESP(task)	(task_sp(task))

#  define STACK_TOP	TASK_SIZE
#  define STACK_TOP_MAX	STACK_TOP

#अगर_घोषित CONFIG_DEBUG_FS
बाह्य काष्ठा dentry *of_debugfs_root;
#पूर्ण_अगर

#  endअगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_PROCESSOR_H */
