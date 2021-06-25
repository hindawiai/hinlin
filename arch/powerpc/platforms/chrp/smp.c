<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Smp support क्रम CHRP machines.
 *
 * Written by Cort Dougan (cort@cs.nmt.edu) borrowing a great
 * deal of code from the sparc and पूर्णांकel versions.
 *
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/rtas.h>

अटल पूर्णांक smp_chrp_kick_cpu(पूर्णांक nr)
अणु
	*(अचिन्हित दीर्घ *)KERNELBASE = nr;
	यंत्र अस्थिर("dcbf 0,%0"::"r"(KERNELBASE):"memory");

	वापस 0;
पूर्ण

अटल व्योम smp_chrp_setup_cpu(पूर्णांक cpu_nr)
अणु
	mpic_setup_this_cpu();
पूर्ण

/* CHRP with खोलोpic */
काष्ठा smp_ops_t chrp_smp_ops = अणु
	.cause_nmi_ipi = शून्य,
	.message_pass = smp_mpic_message_pass,
	.probe = smp_mpic_probe,
	.kick_cpu = smp_chrp_kick_cpu,
	.setup_cpu = smp_chrp_setup_cpu,
	.give_समयbase = rtas_give_समयbase,
	.take_समयbase = rtas_take_समयbase,
पूर्ण;
