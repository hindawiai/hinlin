<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mostly IRQ support क्रम Hexagon
 *
 * Copyright (c) 2010-2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/debug.h>
#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <linux/irq.h>
#समावेश <linux/hardirq.h>

/*
 * show_regs - prपूर्णांक pt_regs काष्ठाure
 * @regs: poपूर्णांकer to pt_regs
 *
 * To-करो:  add all the accessor definitions to रेजिस्टरs.h
 *
 * Will make this routine a lot easier to ग_लिखो.
 */
व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_EMERG);

	prपूर्णांकk(KERN_EMERG "restart_r0: \t0x%08lx   syscall_nr: %ld\n",
	       regs->restart_r0, regs->syscall_nr);
	prपूर्णांकk(KERN_EMERG "preds: \t\t0x%08lx\n", regs->preds);
	prपूर्णांकk(KERN_EMERG "lc0: \t0x%08lx   sa0: 0x%08lx   m0:  0x%08lx\n",
	       regs->lc0, regs->sa0, regs->m0);
	prपूर्णांकk(KERN_EMERG "lc1: \t0x%08lx   sa1: 0x%08lx   m1:  0x%08lx\n",
	       regs->lc1, regs->sa1, regs->m1);
	prपूर्णांकk(KERN_EMERG "gp: \t0x%08lx   ugp: 0x%08lx   usr: 0x%08lx\n",
	       regs->gp, regs->ugp, regs->usr);
	prपूर्णांकk(KERN_EMERG "cs0: \t0x%08lx   cs1: 0x%08lx\n",
	       regs->cs0, regs->cs1);
	prपूर्णांकk(KERN_EMERG "r0: \t0x%08lx %08lx %08lx %08lx\n", regs->r00,
		regs->r01,
		regs->r02,
		regs->r03);
	prपूर्णांकk(KERN_EMERG "r4:  \t0x%08lx %08lx %08lx %08lx\n", regs->r04,
		regs->r05,
		regs->r06,
		regs->r07);
	prपूर्णांकk(KERN_EMERG "r8:  \t0x%08lx %08lx %08lx %08lx\n", regs->r08,
		regs->r09,
		regs->r10,
		regs->r11);
	prपूर्णांकk(KERN_EMERG "r12: \t0x%08lx %08lx %08lx %08lx\n", regs->r12,
		regs->r13,
		regs->r14,
		regs->r15);
	prपूर्णांकk(KERN_EMERG "r16: \t0x%08lx %08lx %08lx %08lx\n", regs->r16,
		regs->r17,
		regs->r18,
		regs->r19);
	prपूर्णांकk(KERN_EMERG "r20: \t0x%08lx %08lx %08lx %08lx\n", regs->r20,
		regs->r21,
		regs->r22,
		regs->r23);
	prपूर्णांकk(KERN_EMERG "r24: \t0x%08lx %08lx %08lx %08lx\n", regs->r24,
		regs->r25,
		regs->r26,
		regs->r27);
	prपूर्णांकk(KERN_EMERG "r28: \t0x%08lx %08lx %08lx %08lx\n", regs->r28,
		regs->r29,
		regs->r30,
		regs->r31);

	prपूर्णांकk(KERN_EMERG "elr: \t0x%08lx   cause: 0x%08lx   user_mode: %d\n",
		pt_elr(regs), pt_cause(regs), user_mode(regs));
	prपूर्णांकk(KERN_EMERG "psp: \t0x%08lx   badva: 0x%08lx   int_enabled: %d\n",
		pt_psp(regs), pt_badva(regs), पूर्णांकs_enabled(regs));
पूर्ण

व्योम dummy_handler(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक elr = pt_elr(regs);
	prपूर्णांकk(KERN_ERR "Unimplemented handler; ELR=0x%08x\n", elr);
पूर्ण


व्योम arch_करो_IRQ(काष्ठा pt_regs *regs)
अणु
	पूर्णांक irq = pt_cause(regs);
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	irq_enter();
	generic_handle_irq(irq);
	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण
