<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_PROCESSOR_GENERIC_H
#घोषणा __UM_PROCESSOR_GENERIC_H

काष्ठा pt_regs;

काष्ठा task_काष्ठा;

#समावेश <यंत्र/ptrace.h>
#समावेश <रेजिस्टरs.h>
#समावेश <sysdep/archसमलाँघ.स>

#समावेश <linux/prefetch.h>

काष्ठा mm_काष्ठा;

काष्ठा thपढ़ो_काष्ठा अणु
	काष्ठा pt_regs regs;
	काष्ठा pt_regs *segv_regs;
	पूर्णांक singlestep_syscall;
	व्योम *fault_addr;
	लाँघ_बफ *fault_catcher;
	काष्ठा task_काष्ठा *prev_sched;
	काष्ठा arch_thपढ़ो arch;
	लाँघ_बफ चयन_buf;
	काष्ठा अणु
		पूर्णांक op;
		जोड़ अणु
			काष्ठा अणु
				पूर्णांक pid;
			पूर्ण विभाजन, exec;
			काष्ठा अणु
				पूर्णांक (*proc)(व्योम *);
				व्योम *arg;
			पूर्ण thपढ़ो;
			काष्ठा अणु
				व्योम (*proc)(व्योम *);
				व्योम *arg;
			पूर्ण cb;
		पूर्ण u;
	पूर्ण request;
पूर्ण;

#घोषणा INIT_THREAD \
अणु \
	.regs		   	= EMPTY_REGS,	\
	.fault_addr		= शून्य, \
	.prev_sched		= शून्य, \
	.arch			= INIT_ARCH_THREAD, \
	.request		= अणु 0 पूर्ण \
पूर्ण

अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत व्योम mm_copy_segments(काष्ठा mm_काष्ठा *from_mm,
				    काष्ठा mm_काष्ठा *new_mm)
अणु
पूर्ण

/*
 * User space process size: 3GB (शेष).
 */
बाह्य अचिन्हित दीर्घ task_size;

#घोषणा TASK_SIZE (task_size)

#अघोषित STACK_TOP
#अघोषित STACK_TOP_MAX

बाह्य अचिन्हित दीर्घ stacksizelim;

#घोषणा STACK_ROOM	(stacksizelim)
#घोषणा STACK_TOP	(TASK_SIZE - 2 * PAGE_SIZE)
#घोषणा STACK_TOP_MAX	STACK_TOP

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE	(0x40000000)

बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ entry, 
			 अचिन्हित दीर्घ stack);

काष्ठा cpuinfo_um अणु
	अचिन्हित दीर्घ loops_per_jअगरfy;
	पूर्णांक ipi_pipe[2];
पूर्ण;

बाह्य काष्ठा cpuinfo_um boot_cpu_data;

#घोषणा cpu_data (&boot_cpu_data)
#घोषणा current_cpu_data boot_cpu_data

#घोषणा KSTK_REG(tsk, reg) get_thपढ़ो_reg(reg, &tsk->thपढ़ो.चयन_buf)
बाह्य अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#पूर्ण_अगर
