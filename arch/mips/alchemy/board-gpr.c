<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GPR board platक्रमm device registration (Au1550)
 *
 * Copyright (C) 2010 Wolfgang Gअक्रमegger <wg@denx.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1000.h>
#समावेश <prom.h>

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "GPR";
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	alchemy_uart_अक्षर_दो(AU1000_UART0_PHYS_ADDR, c);
पूर्ण

अटल व्योम gpr_reset(अक्षर *c)
अणु
	/* चयन System-LED to orange (red# and green# on) */
	alchemy_gpio_direction_output(4, 0);
	alchemy_gpio_direction_output(5, 0);

	/* trigger watchकरोg to reset board in 200ms */
	prपूर्णांकk(KERN_EMERG "Triggering watchdog soft reset...\n");
	raw_local_irq_disable();
	alchemy_gpio_direction_output(1, 0);
	udelay(1);
	alchemy_gpio_set_value(1, 1);
	जबतक (1)
		cpu_रुको();
पूर्ण

अटल व्योम gpr_घातer_off(व्योम)
अणु
	जबतक (1)
		cpu_रुको();
पूर्ण

व्योम __init board_setup(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Trapeze ITS GPR board\n");

	pm_घातer_off = gpr_घातer_off;
	_machine_halt = gpr_घातer_off;
	_machine_restart = gpr_reset;

	/* Enable UART1/3 */
	alchemy_uart_enable(AU1000_UART3_PHYS_ADDR);
	alchemy_uart_enable(AU1000_UART1_PHYS_ADDR);

	/* Take away Reset of UMTS-card */
	alchemy_gpio_direction_output(215, 1);
पूर्ण

/*
 * Watchकरोg
 */
अटल काष्ठा resource gpr_wdt_resource[] = अणु
	[0] = अणु
		.start	= 1,
		.end	= 1,
		.name	= "gpr-adm6320-wdt",
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device gpr_wdt_device = अणु
	.name = "adm6320-wdt",
	.id = 0,
	.num_resources = ARRAY_SIZE(gpr_wdt_resource),
	.resource = gpr_wdt_resource,
पूर्ण;

/*
 * FLASH
 *
 * 0x00000000-0x00200000 : "kernel"
 * 0x00200000-0x00a00000 : "rootfs"
 * 0x01d00000-0x01f00000 : "config"
 * 0x01c00000-0x01d00000 : "yamon"
 * 0x01d00000-0x01d40000 : "yamon env vars"
 * 0x00000000-0x00a00000 : "kernel+rootfs"
 */
अटल काष्ठा mtd_partition gpr_mtd_partitions[] = अणु
	अणु
		.name	= "kernel",
		.size	= 0x00200000,
		.offset = 0,
	पूर्ण,
	अणु
		.name	= "rootfs",
		.size	= 0x00800000,
		.offset = MTDPART_OFS_APPEND,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name	= "config",
		.size	= 0x00200000,
		.offset = 0x01d00000,
	पूर्ण,
	अणु
		.name	= "yamon",
		.size	= 0x00100000,
		.offset = 0x01c00000,
	पूर्ण,
	अणु
		.name	= "yamon env vars",
		.size	= 0x00040000,
		.offset = MTDPART_OFS_APPEND,
	पूर्ण,
	अणु
		.name	= "kernel+rootfs",
		.size	= 0x00a00000,
		.offset = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data gpr_flash_data = अणु
	.width		= 4,
	.nr_parts	= ARRAY_SIZE(gpr_mtd_partitions),
	.parts		= gpr_mtd_partitions,
पूर्ण;

अटल काष्ठा resource gpr_mtd_resource = अणु
	.start	= 0x1e000000,
	.end	= 0x1fffffff,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device gpr_mtd_device = अणु
	.name		= "physmap-flash",
	.dev		= अणु
		.platक्रमm_data	= &gpr_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &gpr_mtd_resource,
पूर्ण;

/*
 * LEDs
 */
अटल स्थिर काष्ठा gpio_led gpr_gpio_leds[] = अणु
	अणु	/* green */
		.name			= "gpr:green",
		.gpio			= 4,
		.active_low		= 1,
	पूर्ण,
	अणु	/* red */
		.name			= "gpr:red",
		.gpio			= 5,
		.active_low		= 1,
	पूर्ण
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data gpr_led_data = अणु
	.num_leds = ARRAY_SIZE(gpr_gpio_leds),
	.leds = gpr_gpio_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device gpr_led_devices = अणु
	.name = "leds-gpio",
	.id = -1,
	.dev = अणु
		.platक्रमm_data = &gpr_led_data,
	पूर्ण
पूर्ण;

/*
 * I2C
 */
अटल काष्ठा gpiod_lookup_table gpr_i2c_gpiod_table = अणु
	.dev_id = "i2c-gpio",
	.table = अणु
		/*
		 * This should be on "GPIO2" which has base at 200 so
		 * the global numbers 209 and 210 should correspond to
		 * local offsets 9 and 10.
		 */
		GPIO_LOOKUP_IDX("alchemy-gpio2", 9, शून्य, 0,
				GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP_IDX("alchemy-gpio2", 10, शून्य, 1,
				GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_gpio_platक्रमm_data gpr_i2c_data = अणु
	/*
	 * The खोलो drain mode is hardwired somewhere or an electrical
	 * property of the alchemy GPIO controller.
	 */
	.sda_is_खोलो_drain	= 1,
	.scl_is_खोलो_drain	= 1,
	.udelay			= 2,		/* ~100 kHz */
	.समयout		= HZ,
पूर्ण;

अटल काष्ठा platक्रमm_device gpr_i2c_device = अणु
	.name			= "i2c-gpio",
	.id			= -1,
	.dev.platक्रमm_data	= &gpr_i2c_data,
पूर्ण;

अटल काष्ठा i2c_board_info gpr_i2c_info[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("lm83", 0x18),
	पूर्ण
पूर्ण;



अटल काष्ठा resource alchemy_pci_host_res[] = अणु
	[0] = अणु
		.start	= AU1500_PCI_PHYS_ADDR,
		.end	= AU1500_PCI_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक gpr_map_pci_irq(स्थिर काष्ठा pci_dev *d, u8 slot, u8 pin)
अणु
	अगर ((slot == 0) && (pin == 1))
		वापस AU1550_PCI_INTA;
	अन्यथा अगर ((slot == 0) && (pin == 2))
		वापस AU1550_PCI_INTB;

	वापस 0xff;
पूर्ण

अटल काष्ठा alchemy_pci_platdata gpr_pci_pd = अणु
	.board_map_irq	= gpr_map_pci_irq,
	.pci_cfg_set	= PCI_CONFIG_AEN | PCI_CONFIG_R2H | PCI_CONFIG_R1H |
			  PCI_CONFIG_CH |
#अगर defined(__MIPSEB__)
			  PCI_CONFIG_SIC_HWA_DAT | PCI_CONFIG_SM,
#अन्यथा
			  0,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा platक्रमm_device gpr_pci_host_dev = अणु
	.dev.platक्रमm_data = &gpr_pci_pd,
	.name		= "alchemy-pci",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(alchemy_pci_host_res),
	.resource	= alchemy_pci_host_res,
पूर्ण;

अटल काष्ठा platक्रमm_device *gpr_devices[] __initdata = अणु
	&gpr_wdt_device,
	&gpr_mtd_device,
	&gpr_i2c_device,
	&gpr_led_devices,
पूर्ण;

अटल पूर्णांक __init gpr_pci_init(व्योम)
अणु
	वापस platक्रमm_device_रेजिस्टर(&gpr_pci_host_dev);
पूर्ण
/* must be arch_initcall; MIPS PCI scans busses in a subsys_initcall */
arch_initcall(gpr_pci_init);


अटल पूर्णांक __init gpr_dev_init(व्योम)
अणु
	gpiod_add_lookup_table(&gpr_i2c_gpiod_table);
	i2c_रेजिस्टर_board_info(0, gpr_i2c_info, ARRAY_SIZE(gpr_i2c_info));

	वापस platक्रमm_add_devices(gpr_devices, ARRAY_SIZE(gpr_devices));
पूर्ण
device_initcall(gpr_dev_init);
