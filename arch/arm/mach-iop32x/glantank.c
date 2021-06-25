<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-iop32x/glantank.c
 *
 * Board support code क्रम the GLAN Tank.
 *
 * Copyright (C) 2006, 2007 Martin Michlmayr <tbm@cyrius.com>
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/f75375s.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/माला.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/page.h>

#समावेश "hardware.h"
#समावेश "gpio-iop32x.h"
#समावेश "irqs.h"

/*
 * GLAN Tank समयr tick configuration.
 */
अटल व्योम __init glantank_समयr_init(व्योम)
अणु
	/* 33.333 MHz crystal.  */
	iop_init_समय(200000000);
पूर्ण


/*
 * GLAN Tank I/O.
 */
अटल काष्ठा map_desc glantank_io_desc[] __initdata = अणु
	अणु	/* on-board devices */
		.भव	= GLANTANK_UART,
		.pfn		= __phys_to_pfn(GLANTANK_UART),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

व्योम __init glantank_map_io(व्योम)
अणु
	iop3xx_map_io();
	iotable_init(glantank_io_desc, ARRAY_SIZE(glantank_io_desc));
पूर्ण


/*
 * GLAN Tank PCI.
 */
#घोषणा INTA	IRQ_IOP32X_XINT0
#घोषणा INTB	IRQ_IOP32X_XINT1
#घोषणा INTC	IRQ_IOP32X_XINT2
#घोषणा INTD	IRQ_IOP32X_XINT3

अटल पूर्णांक __init
glantank_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल पूर्णांक pci_irq_table[][4] = अणु
		/*
		 * PCI IDSEL/INTPIN->INTLINE
		 * A       B       C       D
		 */
		अणुINTD, INTD, INTD, INTDपूर्ण, /* UART (8250) */
		अणुINTA, INTA, INTA, INTAपूर्ण, /* Ethernet (E1000) */
		अणुINTB, INTB, INTB, INTBपूर्ण, /* IDE (AEC6280R) */
		अणुINTC, INTC, INTC, INTCपूर्ण, /* USB (NEC) */
	पूर्ण;

	BUG_ON(pin < 1 || pin > 4);

	वापस pci_irq_table[slot % 4][pin - 1];
पूर्ण

अटल काष्ठा hw_pci glantank_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &iop3xx_ops,
	.setup		= iop3xx_pci_setup,
	.preinit	= iop3xx_pci_preinit,
	.map_irq	= glantank_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init glantank_pci_init(व्योम)
अणु
	अगर (machine_is_glantank())
		pci_common_init(&glantank_pci);

	वापस 0;
पूर्ण

subsys_initcall(glantank_pci_init);


/*
 * GLAN Tank machine initialization.
 */
अटल काष्ठा physmap_flash_data glantank_flash_data = अणु
	.width		= 2,
पूर्ण;

अटल काष्ठा resource glantank_flash_resource = अणु
	.start		= 0xf0000000,
	.end		= 0xf007ffff,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device glantank_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &glantank_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &glantank_flash_resource,
पूर्ण;

अटल काष्ठा plat_serial8250_port glantank_serial_port[] = अणु
	अणु
		.mapbase	= GLANTANK_UART,
		.membase	= (अक्षर *)GLANTANK_UART,
		.irq		= IRQ_IOP32X_XINT3,
		.flags		= UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= 1843200,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा resource glantank_uart_resource = अणु
	.start		= GLANTANK_UART,
	.end		= GLANTANK_UART + 7,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device glantank_serial_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
		.platक्रमm_data		= glantank_serial_port,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &glantank_uart_resource,
पूर्ण;

अटल काष्ठा f75375s_platक्रमm_data glantank_f75375s = अणु
	.pwm		= अणु 255, 255 पूर्ण,
	.pwm_enable	= अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata glantank_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("rs5c372a", 0x32),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("f75375", 0x2e),
		.platक्रमm_data = &glantank_f75375s,
	पूर्ण,
पूर्ण;

अटल व्योम glantank_घातer_off(व्योम)
अणु
	__raw_ग_लिखोb(0x01, IOMEM(0xfe8d0004));

	जबतक (1)
		;
पूर्ण

अटल व्योम __init glantank_init_machine(व्योम)
अणु
	रेजिस्टर_iop32x_gpio();
	gpiod_add_lookup_table(&iop3xx_i2c0_gpio_lookup);
	gpiod_add_lookup_table(&iop3xx_i2c1_gpio_lookup);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c0_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c1_device);
	platक्रमm_device_रेजिस्टर(&glantank_flash_device);
	platक्रमm_device_रेजिस्टर(&glantank_serial_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_0_channel);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_1_channel);

	i2c_रेजिस्टर_board_info(0, glantank_i2c_devices,
		ARRAY_SIZE(glantank_i2c_devices));

	pm_घातer_off = glantank_घातer_off;
पूर्ण

MACHINE_START(GLANTANK, "GLAN Tank")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= glantank_map_io,
	.init_irq	= iop32x_init_irq,
	.init_समय	= glantank_समयr_init,
	.init_machine	= glantank_init_machine,
	.restart	= iop3xx_restart,
MACHINE_END
