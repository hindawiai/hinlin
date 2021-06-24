<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-alpha/processor.h
 *
 * Copyright (C) 1994 Linus Torvalds
 */

#अगर_अघोषित __ASM_ALPHA_PROCESSOR_H
#घोषणा __ASM_ALPHA_PROCESSOR_H

#समावेश <linux/personality.h>	/* क्रम ADDR_LIMIT_32BIT */

/*
 * We have a 42-bit user address space: 4TB user VM...
 */
#घोषणा TASK_SIZE (0x40000000000UL)

#घोषणा STACK_TOP \
  (current->personality & ADDR_LIMIT_32BIT ? 0x80000000 : 0x00120000000UL)

#घोषणा STACK_TOP_MAX	0x00120000000UL

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE \
  ((current->personality & ADDR_LIMIT_32BIT) ? 0x40000000 : TASK_SIZE / 2)

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

/* This is dead.  Everything has been moved to thपढ़ो_info.  */
काष्ठा thपढ़ो_काष्ठा अणु पूर्ण;
#घोषणा INIT_THREAD  अणु पूर्ण

/* Do necessary setup to start up a newly executed thपढ़ो.  */
काष्ठा pt_regs;
बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs *, अचिन्हित दीर्घ, अचिन्हित दीर्घ);

/* Free all resources held by a thपढ़ो. */
काष्ठा task_काष्ठा;
बाह्य व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा KSTK_EIP(tsk) (task_pt_regs(tsk)->pc)

#घोषणा KSTK_ESP(tsk) \
  ((tsk) == current ? rdusp() : task_thपढ़ो_info(tsk)->pcb.usp)

#घोषणा cpu_relax()	barrier()

#घोषणा ARCH_HAS_PREFETCH
#घोषणा ARCH_HAS_PREFETCHW
#घोषणा ARCH_HAS_SPINLOCK_PREFETCH

#अगर_अघोषित CONFIG_SMP
/* Nothing to prefetch. */
#घोषणा spin_lock_prefetch(lock)  	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य अंतरभूत व्योम prefetch(स्थिर व्योम *ptr)  
अणु 
	__builtin_prefetch(ptr, 0, 3);
पूर्ण

बाह्य अंतरभूत व्योम prefetchw(स्थिर व्योम *ptr)  
अणु
	__builtin_prefetch(ptr, 1, 3);
पूर्ण

#अगर_घोषित CONFIG_SMP
बाह्य अंतरभूत व्योम spin_lock_prefetch(स्थिर व्योम *ptr)  
अणु
	__builtin_prefetch(ptr, 1, 3);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ALPHA_PROCESSOR_H */
