<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   linux/arch/parisc/kernel/pa7300lc.c
 *	- PA7300LC-specअगरic functions	
 *
 *   Copyright (C) 2000 Philipp Rumpf */

#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/machdep.h>

/* CPU रेजिस्टर indices */

#घोषणा MIOC_STATUS	0xf040
#घोषणा MIOC_CONTROL	0xf080
#घोषणा MDERRADD	0xf0e0
#घोषणा DMAERR		0xf0e8
#घोषणा DIOERR		0xf0ec
#घोषणा HIDMAMEM	0xf0f4

/* this वापसs the HPA of the CPU it was called on */
अटल u32 cpu_hpa(व्योम)
अणु
	वापस 0xfffb0000;
पूर्ण

अटल व्योम pa7300lc_lpmc(पूर्णांक code, काष्ठा pt_regs *regs)
अणु
	u32 hpa;
	prपूर्णांकk(KERN_WARNING "LPMC on CPU %d\n", smp_processor_id());

	show_regs(regs);

	hpa = cpu_hpa();
	prपूर्णांकk(KERN_WARNING
		"MIOC_CONTROL %08x\n" "MIOC_STATUS  %08x\n"
		"MDERRADD     %08x\n" "DMAERR       %08x\n"
		"DIOERR       %08x\n" "HIDMAMEM     %08x\n",
		gsc_पढ़ोl(hpa+MIOC_CONTROL), gsc_पढ़ोl(hpa+MIOC_STATUS),
		gsc_पढ़ोl(hpa+MDERRADD), gsc_पढ़ोl(hpa+DMAERR),
		gsc_पढ़ोl(hpa+DIOERR), gsc_पढ़ोl(hpa+HIDMAMEM));
पूर्ण

व्योम pa7300lc_init(व्योम)
अणु
	cpu_lpmc = pa7300lc_lpmc;
पूर्ण
