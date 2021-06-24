<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: March 2009
 *  -Implemented task_pt_regs( )
 *
 * Amit Bhor, Sameer Dhavale, Ashwin Chaugule: Codito Technologies 2004
 */

#अगर_अघोषित __ASM_ARC_PROCESSOR_H
#घोषणा __ASM_ARC_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/fpu.h>

/* Arch specअगरic stuff which needs to be saved per task.
 * However these items are not so important so as to earn a place in
 * काष्ठा thपढ़ो_info
 */
काष्ठा thपढ़ो_काष्ठा अणु
	अचिन्हित दीर्घ ksp;	/* kernel mode stack poपूर्णांकer */
	अचिन्हित दीर्घ callee_reg;	/* poपूर्णांकer to callee regs */
	अचिन्हित दीर्घ fault_address;	/* dbls as brkpt holder as well */
#अगर_घोषित CONFIG_ARC_DSP_SAVE_RESTORE_REGS
	काष्ठा dsp_callee_regs dsp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARC_FPU_SAVE_RESTORE
	काष्ठा arc_fpu fpu;
#पूर्ण_अगर
पूर्ण;

#घोषणा INIT_THREAD  अणु                          \
	.ksp = माप(init_stack) + (अचिन्हित दीर्घ) init_stack, \
पूर्ण

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

#घोषणा task_pt_regs(p) \
	((काष्ठा pt_regs *)(THREAD_SIZE + (व्योम *)task_stack_page(p)) - 1)

/* Free all resources held by a thपढ़ो */
#घोषणा release_thपढ़ो(thपढ़ो) करो अणु पूर्ण जबतक (0)

/*
 * A lot of busy-रुको loops in SMP are based off of non-अस्थिर data otherwise
 * get optimised away by gcc
 */
#घोषणा cpu_relax()		barrier()

#घोषणा KSTK_EIP(tsk)   (task_pt_regs(tsk)->ret)
#घोषणा KSTK_ESP(tsk)   (task_pt_regs(tsk)->sp)

/*
 * Where about of Task's sp, fp, blink when it was last seen in kernel mode.
 * Look in process.c क्रम details of kernel stack layout
 */
#घोषणा TSK_K_ESP(tsk)		(tsk->thपढ़ो.ksp)

#घोषणा TSK_K_REG(tsk, off)	(*((अचिन्हित दीर्घ *)(TSK_K_ESP(tsk) + \
					माप(काष्ठा callee_regs) + off)))

#घोषणा TSK_K_BLINK(tsk)	TSK_K_REG(tsk, 4)
#घोषणा TSK_K_FP(tsk)		TSK_K_REG(tsk, 0)

बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs * regs, अचिन्हित दीर्घ pc,
			 अचिन्हित दीर्घ usp);

बाह्य अचिन्हित पूर्णांक get_wchan(काष्ठा task_काष्ठा *p);

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * Default System Memory Map on ARC
 *
 * ---------------------------- (lower 2G, Translated) -------------------------
 * 0x0000_0000		0x5FFF_FFFF	(user vaddr: TASK_SIZE)
 * 0x6000_0000		0x6FFF_FFFF	(reserved gutter between U/K)
 * 0x7000_0000		0x7FFF_FFFF	(kvaddr: vदो_स्मृति/modules/pkmap..)
 *
 * PAGE_OFFSET ---------------- (Upper 2G, Untranslated) -----------------------
 * 0x8000_0000		0xBFFF_FFFF	(kernel direct mapped)
 * 0xC000_0000		0xFFFF_FFFF	(peripheral uncached space)
 * -----------------------------------------------------------------------------
 */

#घोषणा TASK_SIZE	0x60000000

#घोषणा VMALLOC_START	(PAGE_OFFSET - (CONFIG_ARC_KVADDR_SIZE << 20))

/* 1 PGसूची_SIZE each क्रम fixmap/pkmap, 2 PGसूची_SIZE gutter (see यंत्र/highस्मृति.स) */
#घोषणा VMALLOC_SIZE	((CONFIG_ARC_KVADDR_SIZE << 20) - PGसूची_SIZE * 4)

#घोषणा VMALLOC_END	(VMALLOC_START + VMALLOC_SIZE)

#घोषणा USER_KERNEL_GUTTER    (VMALLOC_START - TASK_SIZE)

#घोषणा STACK_TOP       TASK_SIZE
#घोषणा STACK_TOP_MAX   STACK_TOP

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE      (TASK_SIZE / 3)

#पूर्ण_अगर /* __ASM_ARC_PROCESSOR_H */
