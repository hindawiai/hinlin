<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-iop32x/iq80321.c
 *
 * Board support code क्रम the Intel IQ80321 platक्रमm.
 *
 * Author: Rory Bolt <rorybolt@pacbell.net>
 * Copyright (C) 2002 Rory Bolt
 * Copyright (C) 2004 Intel Corp.
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/mtd/physmap.h>
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
#समावेश "irqs.h"
#समावेश "gpio-iop32x.h"

/*
 * IQ80321 समयr tick configuration.
 */
अटल व्योम __init iq80321_समयr_init(व्योम)
अणु
	/* 33.333 MHz crystal.  */
	iop_init_समय(200000000);
पूर्ण


/*
 * IQ80321 I/O.
 */
अटल काष्ठा map_desc iq80321_io_desc[] __initdata = अणु
 	अणु	/* on-board devices */
		.भव	= IQ80321_UART,
		.pfn		= __phys_to_pfn(IQ80321_UART),
		.length		= 0x00100000,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init iq80321_map_io(व्योम)
अणु
	iop3xx_map_io();
	iotable_init(iq80321_io_desc, ARRAY_SIZE(iq80321_io_desc));
पूर्ण


/*
 * IQ80321 PCI.
 */
अटल पूर्णांक __init
iq80321_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	अगर ((slot == 2 || slot == 6) && pin == 1) अणु
		/* PCI-X Slot INTA */
		irq = IRQ_IOP32X_XINT2;
	पूर्ण अन्यथा अगर ((slot == 2 || slot == 6) && pin == 2) अणु
		/* PCI-X Slot INTA */
		irq = IRQ_IOP32X_XINT3;
	पूर्ण अन्यथा अगर ((slot == 2 || slot == 6) && pin == 3) अणु
		/* PCI-X Slot INTA */
		irq = IRQ_IOP32X_XINT0;
	पूर्ण अन्यथा अगर ((slot == 2 || slot == 6) && pin == 4) अणु
		/* PCI-X Slot INTA */
		irq = IRQ_IOP32X_XINT1;
	पूर्ण अन्यथा अगर (slot == 4 || slot == 8) अणु
		/* Gig-E */
		irq = IRQ_IOP32X_XINT0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "iq80321_pci_map_irq() called for unknown "
			"device PCI:%d:%d:%d\n", dev->bus->number,
			PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn));
		irq = -1;
	पूर्ण

	वापस irq;
पूर्ण

अटल काष्ठा hw_pci iq80321_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &iop3xx_ops,
	.setup		= iop3xx_pci_setup,
	.preinit	= iop3xx_pci_preinit_cond,
	.map_irq	= iq80321_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init iq80321_pci_init(व्योम)
अणु
	अगर ((iop3xx_get_init_atu() == IOP3XX_INIT_ATU_ENABLE) &&
		machine_is_iq80321())
		pci_common_init(&iq80321_pci);

	वापस 0;
पूर्ण

subsys_initcall(iq80321_pci_init);


/*
 * IQ80321 machine initialisation.
 */
अटल काष्ठा physmap_flash_data iq80321_flash_data = अणु
	.width		= 1,
पूर्ण;

अटल काष्ठा resource iq80321_flash_resource = अणु
	.start		= 0xf0000000,
	.end		= 0xf07fffff,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device iq80321_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &iq80321_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &iq80321_flash_resource,
पूर्ण;

अटल काष्ठा plat_serial8250_port iq80321_serial_port[] = अणु
	अणु
		.mapbase	= IQ80321_UART,
		.membase	= (अक्षर *)IQ80321_UART,
		.irq		= IRQ_IOP32X_XINT1,
		.flags		= UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= 1843200,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा resource iq80321_uart_resource = अणु
	.start		= IQ80321_UART,
	.end		= IQ80321_UART + 7,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device iq80321_serial_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
		.platक्रमm_data		= iq80321_serial_port,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &iq80321_uart_resource,
पूर्ण;

अटल व्योम __init iq80321_init_machine(व्योम)
अणु
	रेजिस्टर_iop32x_gpio();
	gpiod_add_lookup_table(&iop3xx_i2c0_gpio_lookup);
	gpiod_add_lookup_table(&iop3xx_i2c1_gpio_lookup);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c0_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c1_device);
	platक्रमm_device_रेजिस्टर(&iq80321_flash_device);
	platक्रमm_device_रेजिस्टर(&iq80321_serial_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_0_channel);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_1_channel);
	platक्रमm_device_रेजिस्टर(&iop3xx_aau_channel);
पूर्ण

MACHINE_START(IQ80321, "Intel IQ80321")
	/* Maपूर्णांकainer: Intel Corp. */
	.atag_offset	= 0x100,
	.map_io		= iq80321_map_io,
	.init_irq	= iop32x_init_irq,
	.init_समय	= iq80321_समयr_init,
	.init_machine	= iq80321_init_machine,
	.restart	= iop3xx_restart,
MACHINE_END
