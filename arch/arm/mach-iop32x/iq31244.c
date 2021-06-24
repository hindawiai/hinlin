<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-iop32x/iq31244.c
 *
 * Board support code क्रम the Intel EP80219 and IQ31244 platक्रमms.
 *
 * Author: Rory Bolt <rorybolt@pacbell.net>
 * Copyright (C) 2002 Rory Bolt
 * Copyright 2003 (c) MontaVista, Software, Inc.
 * Copyright (C) 2004 Intel Corp.
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/माला.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <यंत्र/cputype.h>
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
 * Until March of 2007 iq31244 platक्रमms and ep80219 platक्रमms shared the
 * same machine id, and the processor type was used to select board type.
 * However this assumption अवरोधs क्रम an iq80219 board which is an iop219
 * processor on an iq31244 board.  The क्रमce_ep80219 flag has been added
 * क्रम old boot loaders using the iq31244 machine id क्रम an ep80219 platक्रमm.
 */
अटल पूर्णांक क्रमce_ep80219;

अटल पूर्णांक is_80219(व्योम)
अणु
	वापस !!((पढ़ो_cpuid_id() & 0xffffffe0) == 0x69052e20);
पूर्ण

अटल पूर्णांक is_ep80219(व्योम)
अणु
	अगर (machine_is_ep80219() || क्रमce_ep80219)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण


/*
 * EP80219/IQ31244 समयr tick configuration.
 */
अटल व्योम __init iq31244_समयr_init(व्योम)
अणु
	अगर (is_ep80219()) अणु
		/* 33.333 MHz crystal.  */
		iop_init_समय(200000000);
	पूर्ण अन्यथा अणु
		/* 33.000 MHz crystal.  */
		iop_init_समय(198000000);
	पूर्ण
पूर्ण


/*
 * IQ31244 I/O.
 */
अटल काष्ठा map_desc iq31244_io_desc[] __initdata = अणु
	अणु	/* on-board devices */
		.भव	= IQ31244_UART,
		.pfn		= __phys_to_pfn(IQ31244_UART),
		.length		= 0x00100000,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init iq31244_map_io(व्योम)
अणु
	iop3xx_map_io();
	iotable_init(iq31244_io_desc, ARRAY_SIZE(iq31244_io_desc));
पूर्ण


/*
 * EP80219/IQ31244 PCI.
 */
अटल पूर्णांक __init
ep80219_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	अगर (slot == 0) अणु
		/* CFlash */
		irq = IRQ_IOP32X_XINT1;
	पूर्ण अन्यथा अगर (slot == 1) अणु
		/* 82551 Pro 100 */
		irq = IRQ_IOP32X_XINT0;
	पूर्ण अन्यथा अगर (slot == 2) अणु
		/* PCI-X Slot */
		irq = IRQ_IOP32X_XINT3;
	पूर्ण अन्यथा अगर (slot == 3) अणु
		/* SATA */
		irq = IRQ_IOP32X_XINT2;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "ep80219_pci_map_irq() called for unknown "
			"device PCI:%d:%d:%d\n", dev->bus->number,
			PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn));
		irq = -1;
	पूर्ण

	वापस irq;
पूर्ण

अटल काष्ठा hw_pci ep80219_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &iop3xx_ops,
	.setup		= iop3xx_pci_setup,
	.preinit	= iop3xx_pci_preinit,
	.map_irq	= ep80219_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init
iq31244_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	अगर (slot == 0) अणु
		/* CFlash */
		irq = IRQ_IOP32X_XINT1;
	पूर्ण अन्यथा अगर (slot == 1) अणु
		/* SATA */
		irq = IRQ_IOP32X_XINT2;
	पूर्ण अन्यथा अगर (slot == 2) अणु
		/* PCI-X Slot */
		irq = IRQ_IOP32X_XINT3;
	पूर्ण अन्यथा अगर (slot == 3) अणु
		/* 82546 GigE */
		irq = IRQ_IOP32X_XINT0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "iq31244_pci_map_irq called for unknown "
			"device PCI:%d:%d:%d\n", dev->bus->number,
			PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn));
		irq = -1;
	पूर्ण

	वापस irq;
पूर्ण

अटल काष्ठा hw_pci iq31244_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &iop3xx_ops,
	.setup		= iop3xx_pci_setup,
	.preinit	= iop3xx_pci_preinit,
	.map_irq	= iq31244_pci_map_irq,
पूर्ण;

अटल पूर्णांक __init iq31244_pci_init(व्योम)
अणु
	अगर (is_ep80219())
		pci_common_init(&ep80219_pci);
	अन्यथा अगर (machine_is_iq31244()) अणु
		अगर (is_80219()) अणु
			prपूर्णांकk("note: iq31244 board type has been selected\n");
			prपूर्णांकk("note: to select ep80219 operation:\n");
			prपूर्णांकk("\t1/ specify \"force_ep80219\" on the kernel"
				" command line\n");
			prपूर्णांकk("\t2/ update boot loader to pass"
				" the ep80219 id: %d\n", MACH_TYPE_EP80219);
		पूर्ण
		pci_common_init(&iq31244_pci);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(iq31244_pci_init);


/*
 * IQ31244 machine initialisation.
 */
अटल काष्ठा physmap_flash_data iq31244_flash_data = अणु
	.width		= 2,
पूर्ण;

अटल काष्ठा resource iq31244_flash_resource = अणु
	.start		= 0xf0000000,
	.end		= 0xf07fffff,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device iq31244_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &iq31244_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &iq31244_flash_resource,
पूर्ण;

अटल काष्ठा plat_serial8250_port iq31244_serial_port[] = अणु
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

अटल काष्ठा resource iq31244_uart_resource = अणु
	.start		= IQ31244_UART,
	.end		= IQ31244_UART + 7,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device iq31244_serial_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
		.platक्रमm_data		= iq31244_serial_port,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &iq31244_uart_resource,
पूर्ण;

/*
 * This function will send a SHUTDOWN_COMPLETE message to the PIC
 * controller over I2C.  We are not using the i2c subप्रणाली since
 * we are going to घातer off and it may be हटाओd
 */
व्योम ep80219_घातer_off(व्योम)
अणु
	/*
	 * Send the Address byte w/ the start condition
	 */
	*IOP3XX_IDBR1 = 0x60;
	*IOP3XX_ICR1 = 0xE9;
	mdelay(1);

	/*
	 * Send the START_MSG byte w/ no start or stop condition
	 */
	*IOP3XX_IDBR1 = 0x0F;
	*IOP3XX_ICR1 = 0xE8;
	mdelay(1);

	/*
	 * Send the SHUTDOWN_COMPLETE Message ID byte w/ no start or
	 * stop condition
	 */
	*IOP3XX_IDBR1 = 0x03;
	*IOP3XX_ICR1 = 0xE8;
	mdelay(1);

	/*
	 * Send an ignored byte w/ stop condition
	 */
	*IOP3XX_IDBR1 = 0x00;
	*IOP3XX_ICR1 = 0xEA;

	जबतक (1)
		;
पूर्ण

अटल व्योम __init iq31244_init_machine(व्योम)
अणु
	रेजिस्टर_iop32x_gpio();
	gpiod_add_lookup_table(&iop3xx_i2c0_gpio_lookup);
	gpiod_add_lookup_table(&iop3xx_i2c1_gpio_lookup);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c0_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c1_device);
	platक्रमm_device_रेजिस्टर(&iq31244_flash_device);
	platक्रमm_device_रेजिस्टर(&iq31244_serial_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_0_channel);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_1_channel);

	अगर (is_ep80219())
		pm_घातer_off = ep80219_घातer_off;

	अगर (!is_80219())
		platक्रमm_device_रेजिस्टर(&iop3xx_aau_channel);
पूर्ण

अटल पूर्णांक __init क्रमce_ep80219_setup(अक्षर *str)
अणु
	क्रमce_ep80219 = 1;
	वापस 1;
पूर्ण

__setup("force_ep80219", क्रमce_ep80219_setup);

MACHINE_START(IQ31244, "Intel IQ31244")
	/* Maपूर्णांकainer: Intel Corp. */
	.atag_offset	= 0x100,
	.map_io		= iq31244_map_io,
	.init_irq	= iop32x_init_irq,
	.init_समय	= iq31244_समयr_init,
	.init_machine	= iq31244_init_machine,
	.restart	= iop3xx_restart,
MACHINE_END

/* There should have been an ep80219 machine identअगरier from the beginning.
 * Boot roms older than March 2007 करो not know the ep80219 machine id.  Pass
 * "force_ep80219" on the kernel command line, otherwise iq31244 operation
 * will be selected.
 */
MACHINE_START(EP80219, "Intel EP80219")
	/* Maपूर्णांकainer: Intel Corp. */
	.atag_offset	= 0x100,
	.map_io		= iq31244_map_io,
	.init_irq	= iop32x_init_irq,
	.init_समय	= iq31244_समयr_init,
	.init_machine	= iq31244_init_machine,
	.restart	= iop3xx_restart,
MACHINE_END
