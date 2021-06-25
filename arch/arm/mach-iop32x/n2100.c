<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-iop32x/n2100.c
 *
 * Board support code क्रम the Thecus N2100 platक्रमm.
 *
 * Author: Rory Bolt <rorybolt@pacbell.net>
 * Copyright (C) 2002 Rory Bolt
 * Copyright 2003 (c) MontaVista, Software, Inc.
 * Copyright (C) 2004 Intel Corp.
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/f75375s.h>
#समावेश <linux/leds-pca9532.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/माला.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
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
 * N2100 समयr tick configuration.
 */
अटल व्योम __init n2100_समयr_init(व्योम)
अणु
	/* 33.000 MHz crystal.  */
	iop_init_समय(198000000);
पूर्ण


/*
 * N2100 I/O.
 */
अटल काष्ठा map_desc n2100_io_desc[] __initdata = अणु
	अणु	/* on-board devices */
		.भव	= N2100_UART,
		.pfn		= __phys_to_pfn(N2100_UART),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण,
पूर्ण;

व्योम __init n2100_map_io(व्योम)
अणु
	iop3xx_map_io();
	iotable_init(n2100_io_desc, ARRAY_SIZE(n2100_io_desc));
पूर्ण


/*
 * N2100 PCI.
 */
अटल पूर्णांक n2100_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq;

	अगर (PCI_SLOT(dev->devfn) == 1) अणु
		/* RTL8110SB #1 */
		irq = IRQ_IOP32X_XINT0;
	पूर्ण अन्यथा अगर (PCI_SLOT(dev->devfn) == 2) अणु
		/* RTL8110SB #2 */
		irq = IRQ_IOP32X_XINT3;
	पूर्ण अन्यथा अगर (PCI_SLOT(dev->devfn) == 3) अणु
		/* Sil3512 */
		irq = IRQ_IOP32X_XINT2;
	पूर्ण अन्यथा अगर (PCI_SLOT(dev->devfn) == 4 && pin == 1) अणु
		/* VT6212 INTA */
		irq = IRQ_IOP32X_XINT1;
	पूर्ण अन्यथा अगर (PCI_SLOT(dev->devfn) == 4 && pin == 2) अणु
		/* VT6212 INTB */
		irq = IRQ_IOP32X_XINT0;
	पूर्ण अन्यथा अगर (PCI_SLOT(dev->devfn) == 4 && pin == 3) अणु
		/* VT6212 INTC */
		irq = IRQ_IOP32X_XINT2;
	पूर्ण अन्यथा अगर (PCI_SLOT(dev->devfn) == 5) अणु
		/* Mini-PCI slot */
		irq = IRQ_IOP32X_XINT3;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "n2100_pci_map_irq() called for unknown "
			"device PCI:%d:%d:%d\n", dev->bus->number,
			PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn));
		irq = -1;
	पूर्ण

	वापस irq;
पूर्ण

अटल काष्ठा hw_pci n2100_pci __initdata = अणु
	.nr_controllers = 1,
	.ops		= &iop3xx_ops,
	.setup		= iop3xx_pci_setup,
	.preinit	= iop3xx_pci_preinit,
	.map_irq	= n2100_pci_map_irq,
पूर्ण;

/*
 * Both r8169 chips on the n2100 exhibit PCI parity problems.  Turn
 * off parity reporting क्रम both ports so we करोn't get error पूर्णांकerrupts
 * क्रम them.
 */
अटल व्योम n2100_fixup_r8169(काष्ठा pci_dev *dev)
अणु
	अगर (dev->bus->number == 0 &&
	    (dev->devfn == PCI_DEVFN(1, 0) ||
	     dev->devfn == PCI_DEVFN(2, 0)))
		pci_disable_parity(dev);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_REALTEK, PCI_ANY_ID, n2100_fixup_r8169);

अटल पूर्णांक __init n2100_pci_init(व्योम)
अणु
	अगर (machine_is_n2100())
		pci_common_init(&n2100_pci);

	वापस 0;
पूर्ण

subsys_initcall(n2100_pci_init);


/*
 * N2100 machine initialisation.
 */
अटल काष्ठा physmap_flash_data n2100_flash_data = अणु
	.width		= 2,
पूर्ण;

अटल काष्ठा resource n2100_flash_resource = अणु
	.start		= 0xf0000000,
	.end		= 0xf0ffffff,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device n2100_flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &n2100_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &n2100_flash_resource,
पूर्ण;


अटल काष्ठा plat_serial8250_port n2100_serial_port[] = अणु
	अणु
		.mapbase	= N2100_UART,
		.membase	= (अक्षर *)N2100_UART,
		.irq		= 0,
		.flags		= UPF_SKIP_TEST | UPF_AUTO_IRQ | UPF_SHARE_IRQ,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 0,
		.uartclk	= 1843200,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा resource n2100_uart_resource = अणु
	.start		= N2100_UART,
	.end		= N2100_UART + 7,
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device n2100_serial_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev		= अणु
		.platक्रमm_data		= n2100_serial_port,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &n2100_uart_resource,
पूर्ण;

अटल काष्ठा f75375s_platक्रमm_data n2100_f75375s = अणु
	.pwm		= अणु 255, 255 पूर्ण,
	.pwm_enable = अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा pca9532_platक्रमm_data n2100_leds = अणु
	.leds = अणु
	अणु	.name = "n2100:red:satafail0",
		.state = PCA9532_OFF,
		.type = PCA9532_TYPE_LED,
	पूर्ण,
	अणु	.name = "n2100:red:satafail1",
		.state = PCA9532_OFF,
		.type = PCA9532_TYPE_LED,
	पूर्ण,
	अणु	.name = "n2100:blue:usb",
		.state = PCA9532_OFF,
		.type = PCA9532_TYPE_LED,
	पूर्ण,
	अणु 	.type = PCA9532_TYPE_NONE पूर्ण,

	अणु 	.type = PCA9532_TYPE_NONE पूर्ण,
	अणु 	.type = PCA9532_TYPE_NONE पूर्ण,
	अणु 	.type = PCA9532_TYPE_NONE पूर्ण,
	अणु	.name = "n2100:red:usb",
		.state = PCA9532_OFF,
		.type = PCA9532_TYPE_LED,
	पूर्ण,

	अणु	.type = PCA9532_TYPE_NONE पूर्ण, /* घातer OFF gpio */
	अणु	.type = PCA9532_TYPE_NONE पूर्ण, /* reset gpio */
	अणु	.type = PCA9532_TYPE_NONE पूर्ण,
	अणु	.type = PCA9532_TYPE_NONE पूर्ण,

	अणु	.type = PCA9532_TYPE_NONE पूर्ण,
	अणु	.name = "n2100:orange:system",
		.state = PCA9532_OFF,
		.type = PCA9532_TYPE_LED,
	पूर्ण,
	अणु	.name = "n2100:red:system",
		.state = PCA9532_OFF,
		.type = PCA9532_TYPE_LED,
	पूर्ण,
	अणु	.name = "N2100 beeper"  ,
		.state =  PCA9532_OFF,
		.type = PCA9532_TYPE_N2100_BEEP,
	पूर्ण,
	पूर्ण,
	.psc = अणु 0, 0 पूर्ण,
	.pwm = अणु 0, 0 पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata n2100_i2c_devices[] = अणु
	अणु
		I2C_BOARD_INFO("rs5c372b", 0x32),
	पूर्ण,
	अणु
		I2C_BOARD_INFO("f75375", 0x2e),
		.platक्रमm_data = &n2100_f75375s,
	पूर्ण,
	अणु
		I2C_BOARD_INFO("pca9532", 0x60),
		.platक्रमm_data = &n2100_leds,
	पूर्ण,
पूर्ण;

/*
 * Pull PCA9532 GPIO #8 low to घातer off the machine.
 */
अटल व्योम n2100_घातer_off(व्योम)
अणु
	local_irq_disable();

	/* Start condition, I2C address of PCA9532, ग_लिखो transaction.  */
	*IOP3XX_IDBR0 = 0xc0;
	*IOP3XX_ICR0 = 0xe9;
	mdelay(1);

	/* Write address 0x08.  */
	*IOP3XX_IDBR0 = 0x08;
	*IOP3XX_ICR0 = 0xe8;
	mdelay(1);

	/* Write data 0x01, stop condition.  */
	*IOP3XX_IDBR0 = 0x01;
	*IOP3XX_ICR0 = 0xea;

	जबतक (1)
		;
पूर्ण

अटल व्योम n2100_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	पूर्णांक ret;

	ret = gpio_direction_output(N2100_HARDWARE_RESET, 0);
	अगर (ret) अणु
		pr_crit("could not drive reset GPIO low\n");
		वापस;
	पूर्ण
	/* Wait क्रम reset to happen */
	जबतक (1)
		;
पूर्ण


अटल काष्ठा समयr_list घातer_button_poll_समयr;

अटल व्योम घातer_button_poll(काष्ठा समयr_list *unused)
अणु
	अगर (gpio_get_value(N2100_POWER_BUTTON) == 0) अणु
		ctrl_alt_del();
		वापस;
	पूर्ण

	घातer_button_poll_समयr.expires = jअगरfies + (HZ / 10);
	add_समयr(&घातer_button_poll_समयr);
पूर्ण

अटल पूर्णांक __init n2100_request_gpios(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_n2100())
		वापस 0;

	ret = gpio_request(N2100_HARDWARE_RESET, "reset");
	अगर (ret)
		pr_err("could not request reset GPIO\n");

	ret = gpio_request(N2100_POWER_BUTTON, "power");
	अगर (ret)
		pr_err("could not request power GPIO\n");
	अन्यथा अणु
		ret = gpio_direction_input(N2100_POWER_BUTTON);
		अगर (ret)
			pr_err("could not set power GPIO as input\n");
	पूर्ण
	/* Set up घातer button poll समयr */
	समयr_setup(&घातer_button_poll_समयr, घातer_button_poll, 0);
	घातer_button_poll_समयr.expires = jअगरfies + (HZ / 10);
	add_समयr(&घातer_button_poll_समयr);
	वापस 0;
पूर्ण
device_initcall(n2100_request_gpios);

अटल व्योम __init n2100_init_machine(व्योम)
अणु
	रेजिस्टर_iop32x_gpio();
	gpiod_add_lookup_table(&iop3xx_i2c0_gpio_lookup);
	platक्रमm_device_रेजिस्टर(&iop3xx_i2c0_device);
	platक्रमm_device_रेजिस्टर(&n2100_flash_device);
	platक्रमm_device_रेजिस्टर(&n2100_serial_device);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_0_channel);
	platक्रमm_device_रेजिस्टर(&iop3xx_dma_1_channel);

	i2c_रेजिस्टर_board_info(0, n2100_i2c_devices,
		ARRAY_SIZE(n2100_i2c_devices));

	pm_घातer_off = n2100_घातer_off;
पूर्ण

MACHINE_START(N2100, "Thecus N2100")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= n2100_map_io,
	.init_irq	= iop32x_init_irq,
	.init_समय	= n2100_समयr_init,
	.init_machine	= n2100_init_machine,
	.restart	= n2100_restart,
MACHINE_END
