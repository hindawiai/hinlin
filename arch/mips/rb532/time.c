<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.
 *
 *  Setting up the घड़ी on the MIPS boards.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/irq.h>
#समावेश <linux/समयx.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mach-rc32434/rc32434.h>

बाह्य अचिन्हित पूर्णांक idt_cpu_freq;

/*
 * Figure out the r4k offset, the amount to increment the compare
 * रेजिस्टर क्रम each समय tick. There is no RTC available.
 *
 * The RC32434 counts at half the CPU *core* speed.
 */
अटल अचिन्हित दीर्घ __init cal_r4koff(व्योम)
अणु
	mips_hpt_frequency = idt_cpu_freq * IDT_CLOCK_MULT / 2;

	वापस mips_hpt_frequency / HZ;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	अचिन्हित पूर्णांक est_freq;
	अचिन्हित दीर्घ flags, r4k_offset;

	local_irq_save(flags);

	prपूर्णांकk(KERN_INFO "calculating r4koff... ");
	r4k_offset = cal_r4koff();
	prपूर्णांकk("%08lx(%d)\n", r4k_offset, (पूर्णांक) r4k_offset);

	est_freq = 2 * r4k_offset * HZ;
	est_freq += 5000;	/* round */
	est_freq -= est_freq % 10000;
	prपूर्णांकk(KERN_INFO "CPU frequency %d.%02d MHz\n", est_freq / 1000000,
	       (est_freq % 1000000) * 100 / 1000000);
	local_irq_restore(flags);
पूर्ण
