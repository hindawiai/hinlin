<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BRIEF MODULE DESCRIPTION
 *	MyCable XXS1500 board support
 *
 * Copyright 2003, 2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1000.h>
#समावेश <prom.h>

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "XXS1500";
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	alchemy_uart_अक्षर_दो(AU1000_UART0_PHYS_ADDR, c);
पूर्ण

अटल व्योम xxs1500_reset(अक्षर *c)
अणु
	/* Jump to the reset vector */
	__यंत्र__ __अस्थिर__("jr\t%0" : : "r"(0xbfc00000));
पूर्ण

अटल व्योम xxs1500_घातer_off(व्योम)
अणु
	जबतक (1)
		यंत्र अस्थिर (
		"	.set	mips32					\n"
		"	wait						\n"
		"	.set	mips0					\n");
पूर्ण

व्योम __init board_setup(व्योम)
अणु
	u32 pin_func;

	pm_घातer_off = xxs1500_घातer_off;
	_machine_halt = xxs1500_घातer_off;
	_machine_restart = xxs1500_reset;

	alchemy_gpio1_input_enable();
	alchemy_gpio2_enable();

	/* Set multiple use pins (UART3/GPIO) to UART (it's used as UART too) */
	pin_func  = alchemy_rdsys(AU1000_SYS_PINFUNC) & ~SYS_PF_UR3;
	pin_func |= SYS_PF_UR3;
	alchemy_wrsys(pin_func, AU1000_SYS_PINFUNC);

	/* Enable UART */
	alchemy_uart_enable(AU1000_UART3_PHYS_ADDR);
	/* Enable DTR (MCR bit 0) = USB घातer up */
	__raw_ग_लिखोl(1, (व्योम __iomem *)KSEG1ADDR(AU1000_UART3_PHYS_ADDR + 0x18));
	wmb();
पूर्ण

/******************************************************************************/

अटल काष्ठा resource xxs1500_pcmcia_res[] = अणु
	अणु
		.name	= "pcmcia-io",
		.flags	= IORESOURCE_MEM,
		.start	= AU1000_PCMCIA_IO_PHYS_ADDR,
		.end	= AU1000_PCMCIA_IO_PHYS_ADDR + 0x000400000 - 1,
	पूर्ण,
	अणु
		.name	= "pcmcia-attr",
		.flags	= IORESOURCE_MEM,
		.start	= AU1000_PCMCIA_ATTR_PHYS_ADDR,
		.end	= AU1000_PCMCIA_ATTR_PHYS_ADDR + 0x000400000 - 1,
	पूर्ण,
	अणु
		.name	= "pcmcia-mem",
		.flags	= IORESOURCE_MEM,
		.start	= AU1000_PCMCIA_MEM_PHYS_ADDR,
		.end	= AU1000_PCMCIA_MEM_PHYS_ADDR + 0x000400000 - 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device xxs1500_pcmcia_dev = अणु
	.name		= "xxs1500_pcmcia",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(xxs1500_pcmcia_res),
	.resource	= xxs1500_pcmcia_res,
पूर्ण;

अटल काष्ठा platक्रमm_device *xxs1500_devs[] __initdata = अणु
	&xxs1500_pcmcia_dev,
पूर्ण;

अटल पूर्णांक __init xxs1500_dev_init(व्योम)
अणु
	irq_set_irq_type(AU1500_GPIO204_INT, IRQ_TYPE_LEVEL_HIGH);
	irq_set_irq_type(AU1500_GPIO201_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO202_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO203_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO205_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO207_INT, IRQ_TYPE_LEVEL_LOW);

	irq_set_irq_type(AU1500_GPIO0_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO1_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO2_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO3_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO4_INT, IRQ_TYPE_LEVEL_LOW); /* CF irq */
	irq_set_irq_type(AU1500_GPIO5_INT, IRQ_TYPE_LEVEL_LOW);

	वापस platक्रमm_add_devices(xxs1500_devs,
				    ARRAY_SIZE(xxs1500_devs));
पूर्ण
device_initcall(xxs1500_dev_init);
