<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-iop32x/em7210.c
 *
 * Board support code क्रम the Lanner EM7210 platक्रमms.
 *
 * Based on arch/arm/mach-iop32x/iq31244.c file.
 *
 * Copyright (C) 2007 Arnaud Patard <arnaud.patard@rtp-net.org>
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/mach-types.h>

#समावेश "hardware.h"
#समावेश "gpio-iop32x.h"
#समावेश "irqs.h"

अटल व्योम __init em7210_समयr_init(व्योम)
अणु
	/* http://www.kwaak.net/fotos/fotos-nas/slide_24.hपंचांगl */
	/* 33.333 MHz crystal.                                */
	iop_init_समय(200000000);
पूर्ण

/*
 * EM7210 RTC
 */
अटल काष्ठा i2c_board_info __initdata em7210_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("rs5c372a", 0x32),
	पूर्ण,
पूर्ण;

/*
 * EM7210 I/O
 */
अटल काष्ठा map_desc em7210_io_desc[] __initdata = अणु
	अणु	/* on-board devices */
		.भव	= IQ31244_UART,
		.pfn		= __phys_to_pfn(IQ31244_UART),
		.length		= 0x00100000,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init em7210_map_io(व्योम)
अणु
	iop3xx_map_io();
	iotable_init(em7210_io_desc, ARRAY_SIZE(em7210_io_desc));
पूर्ण


/*
 * EM7210 PCI
 */
#घोषणा INTA	IRQ_IOP32X_XINT0
#घोषणा INTB	IRQ_IOP32X_XINT1
#घोषणा INTC	IRQ_IOP32X_XINT2
#घोषणा INTD	IRQ_IOP32X_XINT3

अटल पूर्णांक __init
em7210_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अटल पूर्णांक pci_irq_table[][4] = अणु
		/*
		 * PCI IDSEL/INTPIN->INTLINE
		 * A       B       C       D
		 */
		अणुINTB, INTB, INTB, INTBपूर्ण, /* console / uart */
		अणुINTA, INTA, INTA, INTAपूर्ण, /* 1st 82541      */
		अणुINTD, INTD, INTD, INTDपूर्ण, /* 2nd 82541      */
		अणुINTC, INTC, INTC, INTCपूर्ण, /* GD31244        */
		अणुINTD, INTA, INTA, INTAपूर्ण, /* mini-PCI       */
		अणुINTD, INTC, INTA, INTAपूर्ण, /* NEC USB        */
	पूर्ण;

	अगर (pin < 1 || pin > 4)
		वापस -1;

	वापस pci_irq_table[slot % 6][pin - 1];
पूर्ण

अटल काष्ठा hw_pci em7210_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &iop3xx_ops,
	.setup		= iop3xx_pci_setup,
	.preinit	= iop3xx_pci_preinit,
	.map_irq	= em7210_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init em7210_pci_init(व्योम)
अणु
	अगर (machine_is_em7210())
		pci_common_init(&em7210_pci);

	वापस 0;
पूर्ण

subsys_initcall(em7210_pci_init);


/*
 * EM7210 Flash
 */
अटल काष्ठा physmap_flash_data em7210_flash_data = अणु
	.width		= 2,
पूर्ण;

अटल काष्ठा resource em7210_flash_resource = अणु
	.start		= 0xf0000000,
	.end		= 0xf1ffffff,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device em7210_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &em7210_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &em7210_flash_resource,
पूर्ण;


/*
 * EM7210 UART
 * The physical address of the serial port is 0xfe800000,
 * so it can be used क्रम physical and भव address.
 */
अटल काष्ठा plat_serial8250_port em7210_serial_port[] = अणु
	अणु
		.mapbase	= IQ31244_UART,
		.membase	= (अक्षर *)IQ31244_UART,
		.irq		= IRQ_IOP32X_XINT1,
		.flags		= UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= 1843200,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा resource em7210_uart_resource = अणु
	.start		= IQ31244_UART,
	.end		= IQ31244_UART + 7,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device em7210_serial_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
		.platक्रमm_data		= em7210_serial_port,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &em7210_uart_resource,
पूर्ण;

#घोषणा EM7210_HARDWARE_POWER 0

व्योम em7210_घातer_off(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_direction_output(EM7210_HARDWARE_POWER, 1);
	अगर (ret)
		pr_crit("could not drive power off GPIO high\n");
पूर्ण

अटल पूर्णांक __init em7210_request_gpios(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_em7210())
		वापस 0;

	ret = gpio_request(EM7210_HARDWARE_POWER, "power");
	अगर (ret) अणु
		pr_err("could not request power off GPIO\n");
		वापस 0;
	पूर्ण

	pm_घातer_off = em7210_घातer_off;

	वापस 0;
पूर्ण
device_initcall(em7210_request_gpios);

अटल व्योम __init em7210_init_machine(व्योम)
अणु
	रेजिस्टर_iop32x_gpio();
	platक्रमm_device_रेजिस्टर(&em7210_serial_device);
	gpiod_add_lookup_table(&iop3xx_i2c0_gpio_lookup);
	gpiod_add_lookup_table(&iop3xx_i2c1_gpio_lookup);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c0_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c1_device);
	platक्रमm_device_रेजिस्टर(&em7210_flash_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_0_channel);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_1_channel);

	i2c_रेजिस्टर_board_info(0, em7210_i2c_devices,
		ARRAY_SIZE(em7210_i2c_devices));
पूर्ण

MACHINE_START(EM7210, "Lanner EM7210")
	.atag_offset	= 0x100,
	.map_io		= em7210_map_io,
	.init_irq	= iop32x_init_irq,
	.init_समय	= em7210_समयr_init,
	.init_machine	= em7210_init_machine,
	.restart	= iop3xx_restart,
MACHINE_END
