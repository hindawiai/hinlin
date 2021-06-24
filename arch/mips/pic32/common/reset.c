<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <linux/init.h>
#समावेश <linux/pm.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/mach-pic32/pic32.h>

#घोषणा PIC32_RSWRST		0x10

अटल व्योम pic32_halt(व्योम)
अणु
	जबतक (1) अणु
		__यंत्र__(".set push;\n"
			".set arch=r4000;\n"
			"wait;\n"
			".set pop;\n"
		);
	पूर्ण
पूर्ण

अटल व्योम pic32_machine_restart(अक्षर *command)
अणु
	व्योम __iomem *reg =
		ioremap(PIC32_BASE_RESET + PIC32_RSWRST, माप(u32));

	pic32_syskey_unlock();

	/* magic ग_लिखो/पढ़ो */
	__raw_ग_लिखोl(1, reg);
	(व्योम)__raw_पढ़ोl(reg);

	pic32_halt();
पूर्ण

अटल व्योम pic32_machine_halt(व्योम)
अणु
	local_irq_disable();

	pic32_halt();
पूर्ण

अटल पूर्णांक __init mips_reboot_setup(व्योम)
अणु
	_machine_restart = pic32_machine_restart;
	_machine_halt = pic32_machine_halt;
	pm_घातer_off = pic32_machine_halt;

	वापस 0;
पूर्ण

arch_initcall(mips_reboot_setup);
