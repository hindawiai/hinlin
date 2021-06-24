<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/समय.c
 *
 * Copyright (C) 1991, 1992, 1995  Linus Torvalds
 * Modअगरications क्रम ARM (C) 1994-2001 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/घड़ीchips.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/समयx.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/profile.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/समयr.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/acpi.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/paravirt.h>

अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	काष्ठा stackframe frame;

	अगर (!in_lock_functions(regs->pc))
		वापस regs->pc;

	start_backtrace(&frame, regs->regs[29], regs->pc);

	करो अणु
		पूर्णांक ret = unwind_frame(शून्य, &frame);
		अगर (ret < 0)
			वापस 0;
	पूर्ण जबतक (in_lock_functions(frame.pc));

	वापस frame.pc;
पूर्ण
EXPORT_SYMBOL(profile_pc);

व्योम __init समय_init(व्योम)
अणु
	u32 arch_समयr_rate;

	of_clk_init(शून्य);
	समयr_probe();

	tick_setup_hrसमयr_broadcast();

	arch_समयr_rate = arch_समयr_get_rate();
	अगर (!arch_समयr_rate)
		panic("Unable to initialise architected timer.\n");

	/* Calibrate the delay loop directly */
	lpj_fine = arch_समयr_rate / HZ;

	pv_समय_init();
पूर्ण
