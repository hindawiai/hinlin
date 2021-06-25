<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2012 Thomas Langer <thomas.langer@lantiq.com>
 * Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm.h>
#समावेश <यंत्र/reboot.h>
#समावेश <linux/export.h>

#समावेश <lantiq_soc.h>

/*
 * Dummy implementation.  Used to allow platक्रमm code to find out what
 * source was booted from
 */
अचिन्हित अक्षर ltq_boot_select(व्योम)
अणु
	वापस BS_SPI;
पूर्ण

#घोषणा BOOT_REG_BASE	(KSEG1 | 0x1F200000)
#घोषणा BOOT_PW1_REG	(BOOT_REG_BASE | 0x20)
#घोषणा BOOT_PW2_REG	(BOOT_REG_BASE | 0x24)
#घोषणा BOOT_PW1	0x4C545100
#घोषणा BOOT_PW2	0x0051544C

#घोषणा WDT_REG_BASE	(KSEG1 | 0x1F8803F0)
#घोषणा WDT_PW1		0x00BE0000
#घोषणा WDT_PW2		0x00DC0000

अटल व्योम machine_restart(अक्षर *command)
अणु
	local_irq_disable();

	/* reboot magic */
	ltq_w32(BOOT_PW1, (व्योम *)BOOT_PW1_REG); /* 'LTQ\0' */
	ltq_w32(BOOT_PW2, (व्योम *)BOOT_PW2_REG); /* '\0QTL' */
	ltq_w32(0, (व्योम *)BOOT_REG_BASE); /* reset Bootreg RVEC */

	/* watchकरोg magic */
	ltq_w32(WDT_PW1, (व्योम *)WDT_REG_BASE);
	ltq_w32(WDT_PW2 |
		(0x3 << 26) | /* PWL */
		(0x2 << 24) | /* CLKDIV */
		(0x1 << 31) | /* enable */
		(1), /* reload */
		(व्योम *)WDT_REG_BASE);
	unreachable();
पूर्ण

अटल व्योम machine_halt(व्योम)
अणु
	local_irq_disable();
	unreachable();
पूर्ण

अटल व्योम machine_घातer_off(व्योम)
अणु
	local_irq_disable();
	unreachable();
पूर्ण

अटल पूर्णांक __init mips_reboot_setup(व्योम)
अणु
	_machine_restart = machine_restart;
	_machine_halt = machine_halt;
	pm_घातer_off = machine_घातer_off;
	वापस 0;
पूर्ण

arch_initcall(mips_reboot_setup);
