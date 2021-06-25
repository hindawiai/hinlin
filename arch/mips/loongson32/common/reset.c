<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 Zhang, Keguang <keguang.zhang@gmail.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/reboot.h>

#समावेश <loongson1.h>

अटल व्योम __iomem *wdt_reg_base;

अटल व्योम ls1x_halt(व्योम)
अणु
	जबतक (1) अणु
		अगर (cpu_रुको)
			cpu_रुको();
	पूर्ण
पूर्ण

अटल व्योम ls1x_restart(अक्षर *command)
अणु
	__raw_ग_लिखोl(0x1, wdt_reg_base + WDT_EN);
	__raw_ग_लिखोl(0x1, wdt_reg_base + WDT_TIMER);
	__raw_ग_लिखोl(0x1, wdt_reg_base + WDT_SET);

	ls1x_halt();
पूर्ण

अटल व्योम ls1x_घातer_off(व्योम)
अणु
	ls1x_halt();
पूर्ण

अटल पूर्णांक __init ls1x_reboot_setup(व्योम)
अणु
	wdt_reg_base = ioremap(LS1X_WDT_BASE, (SZ_4 + SZ_8));
	अगर (!wdt_reg_base)
		panic("Failed to remap watchdog registers");

	_machine_restart = ls1x_restart;
	_machine_halt = ls1x_halt;
	pm_घातer_off = ls1x_घातer_off;

	वापस 0;
पूर्ण

arch_initcall(ls1x_reboot_setup);
