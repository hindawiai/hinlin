<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R8A7740 processor support
 *
 * Copyright (C) 2011  Renesas Solutions Corp.
 * Copyright (C) 2011  Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic.h>

#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "common.h"

/*
 * r8a7740 chip has lasting errata on MERAM buffer.
 * this is work-around क्रम it.
 * see
 *	"Media RAM (MERAM)" on r8a7740 करोcumentation
 */
#घोषणा MEBUFCNTR	0xFE950098
अटल व्योम __init r8a7740_meram_workaround(व्योम)
अणु
	व्योम __iomem *reg;

	reg = ioremap(MEBUFCNTR, 4);
	अगर (reg) अणु
		ioग_लिखो32(0x01600164, reg);
		iounmap(reg);
	पूर्ण
पूर्ण

अटल व्योम __init r8a7740_init_irq_of(व्योम)
अणु
	व्योम __iomem *पूर्णांकc_prio_base = ioremap(0xe6900010, 0x10);
	व्योम __iomem *पूर्णांकc_msk_base = ioremap(0xe6900040, 0x10);
	व्योम __iomem *pfc_पूर्णांकa_ctrl = ioremap(0xe605807c, 0x4);

	irqchip_init();

	/* route संकेतs to GIC */
	ioग_लिखो32(0x0, pfc_पूर्णांकa_ctrl);

	/*
	 * To mask the shared पूर्णांकerrupt to SPI 149 we must ensure to set
	 * PRIO *and* MASK. Else we run पूर्णांकo IRQ floods when रेजिस्टरing
	 * the पूर्णांकc_irqpin devices
	 */
	ioग_लिखो32(0x0, पूर्णांकc_prio_base + 0x0);
	ioग_लिखो32(0x0, पूर्णांकc_prio_base + 0x4);
	ioग_लिखो32(0x0, पूर्णांकc_prio_base + 0x8);
	ioग_लिखो32(0x0, पूर्णांकc_prio_base + 0xc);
	ioग_लिखो8(0xff, पूर्णांकc_msk_base + 0x0);
	ioग_लिखो8(0xff, पूर्णांकc_msk_base + 0x4);
	ioग_लिखो8(0xff, पूर्णांकc_msk_base + 0x8);
	ioग_लिखो8(0xff, पूर्णांकc_msk_base + 0xc);

	iounmap(पूर्णांकc_prio_base);
	iounmap(पूर्णांकc_msk_base);
	iounmap(pfc_पूर्णांकa_ctrl);
पूर्ण

अटल व्योम __init r8a7740_generic_init(व्योम)
अणु
	r8a7740_meram_workaround();
पूर्ण

अटल स्थिर अक्षर *स्थिर r8a7740_boards_compat_dt[] __initस्थिर = अणु
	"renesas,r8a7740",
	शून्य,
पूर्ण;

DT_MACHINE_START(R8A7740_DT, "Generic R8A7740 (Flattened Device Tree)")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_early	= shmobile_init_delay,
	.init_irq	= r8a7740_init_irq_of,
	.init_machine	= r8a7740_generic_init,
	.init_late	= shmobile_init_late,
	.dt_compat	= r8a7740_boards_compat_dt,
MACHINE_END
