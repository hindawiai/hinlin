<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_PROCESSOR_H
#घोषणा __ASM_OPENRISC_PROCESSOR_H

#समावेश <यंत्र/spr_defs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा STACK_TOP       TASK_SIZE
#घोषणा STACK_TOP_MAX	STACK_TOP
/* Kernel and user SR रेजिस्टर setting */
#घोषणा KERNEL_SR (SPR_SR_DME | SPR_SR_IME | SPR_SR_ICE \
		   | SPR_SR_DCE | SPR_SR_SM)
#घोषणा USER_SR   (SPR_SR_DME | SPR_SR_IME | SPR_SR_ICE \
		   | SPR_SR_DCE | SPR_SR_IEE | SPR_SR_TEE)

/*
 * User space process size. This is hardcoded पूर्णांकo a few places,
 * so करोn't change it unless you know what you are करोing.
 */

#घोषणा TASK_SIZE       (0x80000000UL)

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE      (TASK_SIZE / 8 * 3)

#अगर_अघोषित __ASSEMBLY__

काष्ठा task_काष्ठा;

काष्ठा thपढ़ो_काष्ठा अणु
पूर्ण;

/*
 * At user->kernel entry, the pt_regs काष्ठा is stacked on the top of the
 * kernel-stack.  This macro allows us to find those regs क्रम a task.
 * Notice that subsequent pt_regs stackings, like recursive पूर्णांकerrupts
 * occurring जबतक we're in the kernel, won't affect this - only the first
 * user->kernel transition रेजिस्टरs are reached by this (i.e. not regs
 * क्रम running संकेत handler)
 */
#घोषणा user_regs(thपढ़ो_info)  (((काष्ठा pt_regs *)((अचिन्हित दीर्घ)(thपढ़ो_info) + THREAD_SIZE - STACK_FRAME_OVERHEAD)) - 1)

/*
 * Dito but क्रम the currently running task
 */

#घोषणा task_pt_regs(task) user_regs(task_thपढ़ो_info(task))

#घोषणा INIT_SP         (माप(init_stack) + (अचिन्हित दीर्घ) &init_stack)

#घोषणा INIT_THREAD  अणु पूर्ण


#घोषणा KSTK_EIP(tsk)   (task_pt_regs(tsk)->pc)
#घोषणा KSTK_ESP(tsk)   (task_pt_regs(tsk)->sp)


व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ nip, अचिन्हित दीर्घ sp);
व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);
अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा cpu_relax()     barrier()

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_OPENRISC_PROCESSOR_H */
