<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/समय.c
 *
 *  Copyright (C) 1991, 1992, 1995  Linus Torvalds
 *  Modअगरications क्रम ARM (C) 1994-2001 Russell King
 *
 *  This file contains the ARM-specअगरic समय handling details:
 *  पढ़ोing the RTC at bootup, etc...
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/profile.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/smp.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/समयr.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/thपढ़ो_info.h>

#अगर defined(CONFIG_RTC_DRV_CMOS) || defined(CONFIG_RTC_DRV_CMOS_MODULE) || \
    defined(CONFIG_NVRAM) || defined(CONFIG_NVRAM_MODULE)
/* this needs a better home */
DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);
#पूर्ण_अगर	/* pc-style 'CMOS' RTC support */

/* change this अगर you have some स्थिरant समय drअगरt */
#घोषणा USECS_PER_JIFFY	(1000000/HZ)

#अगर_घोषित CONFIG_SMP
अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	काष्ठा stackframe frame;

	अगर (!in_lock_functions(regs->ARM_pc))
		वापस regs->ARM_pc;

	arm_get_current_stackframe(regs, &frame);
	करो अणु
		पूर्णांक ret = unwind_frame(&frame);
		अगर (ret < 0)
			वापस 0;
	पूर्ण जबतक (in_lock_functions(frame.pc));

	वापस frame.pc;
पूर्ण
EXPORT_SYMBOL(profile_pc);
#पूर्ण_अगर

अटल व्योम dummy_घड़ी_access(काष्ठा बारpec64 *ts)
अणु
	ts->tv_sec = 0;
	ts->tv_nsec = 0;
पूर्ण

अटल घड़ी_access_fn __पढ़ो_persistent_घड़ी = dummy_घड़ी_access;

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	__पढ़ो_persistent_घड़ी(ts);
पूर्ण

पूर्णांक __init रेजिस्टर_persistent_घड़ी(घड़ी_access_fn पढ़ो_persistent)
अणु
	/* Only allow the घड़ीaccess functions to be रेजिस्टरed once */
	अगर (__पढ़ो_persistent_घड़ी == dummy_घड़ी_access) अणु
		अगर (पढ़ो_persistent)
			__पढ़ो_persistent_घड़ी = पढ़ो_persistent;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	अगर (machine_desc->init_समय) अणु
		machine_desc->init_समय();
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_COMMON_CLK
		of_clk_init(शून्य);
#पूर्ण_अगर
		समयr_probe();
		tick_setup_hrसमयr_broadcast();
	पूर्ण
पूर्ण
