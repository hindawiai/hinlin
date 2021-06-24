<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MTX-1 platक्रमm devices registration (Au1500)
 *
 * Copyright (C) 2007-2009, Florian Fainelli <florian@खोलोwrt.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <mtd/mtd-abi.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_eth.h>
#समावेश <prom.h>

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "MTX-1";
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	alchemy_uart_अक्षर_दो(AU1000_UART0_PHYS_ADDR, c);
पूर्ण

अटल व्योम mtx1_reset(अक्षर *c)
अणु
	/* Jump to the reset vector */
	__यंत्र__ __अस्थिर__("jr\t%0" : : "r"(0xbfc00000));
पूर्ण

अटल व्योम mtx1_घातer_off(व्योम)
अणु
	जबतक (1)
		यंत्र अस्थिर (
		"	.set	mips32					\n"
		"	wait						\n"
		"	.set	mips0					\n");
पूर्ण

व्योम __init board_setup(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_USB_OHCI_HCD)
	/* Enable USB घातer चयन */
	alchemy_gpio_direction_output(204, 0);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_USB_OHCI_HCD) */

	/* Initialize sys_pinfunc */
	alchemy_wrsys(SYS_PF_NI2, AU1000_SYS_PINFUNC);

	/* Initialize GPIO */
	alchemy_wrsys(~0, AU1000_SYS_TRIOUTCLR);
	alchemy_gpio_direction_output(0, 0);	/* Disable M66EN (PCI 66MHz) */
	alchemy_gpio_direction_output(3, 1);	/* Disable PCI CLKRUN# */
	alchemy_gpio_direction_output(1, 1);	/* Enable EXT_IO3 */
	alchemy_gpio_direction_output(5, 0);	/* Disable eth PHY TX_ER */

	/* Enable LED and set it to green */
	alchemy_gpio_direction_output(211, 1);	/* green on */
	alchemy_gpio_direction_output(212, 0);	/* red off */

	pm_घातer_off = mtx1_घातer_off;
	_machine_halt = mtx1_घातer_off;
	_machine_restart = mtx1_reset;

	prपूर्णांकk(KERN_INFO "4G Systems MTX-1 Board\n");
पूर्ण

/******************************************************************************/

अटल काष्ठा gpio_keys_button mtx1_gpio_button[] = अणु
	अणु
		.gpio = 207,
		.code = BTN_0,
		.desc = "System button",
	पूर्ण
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data mtx1_buttons_data = अणु
	.buttons = mtx1_gpio_button,
	.nbuttons = ARRAY_SIZE(mtx1_gpio_button),
पूर्ण;

अटल काष्ठा platक्रमm_device mtx1_button = अणु
	.name = "gpio-keys",
	.id = -1,
	.dev = अणु
		.platक्रमm_data = &mtx1_buttons_data,
	पूर्ण
पूर्ण;

अटल काष्ठा gpiod_lookup_table mtx1_wdt_gpio_table = अणु
	.dev_id = "mtx1-wdt.0",
	.table = अणु
		/* Global number 215 is offset 15 on Alchemy GPIO 2 */
		GPIO_LOOKUP("alchemy-gpio2", 15, शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device mtx1_wdt = अणु
	.name = "mtx1-wdt",
	.id = 0,
पूर्ण;

अटल स्थिर काष्ठा gpio_led शेष_leds[] = अणु
	अणु
		.name	= "mtx1:green",
		.gpio = 211,
	पूर्ण, अणु
		.name = "mtx1:red",
		.gpio = 212,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data mtx1_led_data = अणु
	.num_leds = ARRAY_SIZE(शेष_leds),
	.leds = शेष_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device mtx1_gpio_leds = अणु
	.name = "leds-gpio",
	.id = -1,
	.dev = अणु
		.platक्रमm_data = &mtx1_led_data,
	पूर्ण
पूर्ण;

अटल काष्ठा mtd_partition mtx1_mtd_partitions[] = अणु
	अणु
		.name	= "filesystem",
		.size	= 0x01C00000,
		.offset = 0,
	पूर्ण,
	अणु
		.name	= "yamon",
		.size	= 0x00100000,
		.offset = MTDPART_OFS_APPEND,
		.mask_flags = MTD_WRITEABLE,
	पूर्ण,
	अणु
		.name	= "kernel",
		.size	= 0x002c0000,
		.offset = MTDPART_OFS_APPEND,
	पूर्ण,
	अणु
		.name	= "yamon env",
		.size	= 0x00040000,
		.offset = MTDPART_OFS_APPEND,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data mtx1_flash_data = अणु
	.width		= 4,
	.nr_parts	= 4,
	.parts		= mtx1_mtd_partitions,
पूर्ण;

अटल काष्ठा resource mtx1_mtd_resource = अणु
	.start	= 0x1e000000,
	.end	= 0x1fffffff,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device mtx1_mtd = अणु
	.name		= "physmap-flash",
	.dev		= अणु
		.platक्रमm_data	= &mtx1_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &mtx1_mtd_resource,
पूर्ण;

अटल काष्ठा resource alchemy_pci_host_res[] = अणु
	[0] = अणु
		.start	= AU1500_PCI_PHYS_ADDR,
		.end	= AU1500_PCI_PHYS_ADDR + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mtx1_pci_idsel(अचिन्हित पूर्णांक devsel, पूर्णांक निश्चित)
अणु
	/* This function is only necessary to support a proprietary Cardbus
	 * adapter on the mtx-1 "singleboard" variant. It triggers a custom
	 * logic chip connected to EXT_IO3 (GPIO1) to suppress IDSEL संकेतs.
	 */
	udelay(1);

	अगर (निश्चित && devsel != 0)
		/* Suppress संकेत to Cardbus */
		alchemy_gpio_set_value(1, 0);	/* set EXT_IO3 OFF */
	अन्यथा
		alchemy_gpio_set_value(1, 1);	/* set EXT_IO3 ON */

	udelay(1);
	वापस 1;
पूर्ण

अटल स्थिर अक्षर mtx1_irqtab[][5] = अणु
	[0] = अणु -1, AU1500_PCI_INTA, AU1500_PCI_INTA, 0xff, 0xff पूर्ण, /* IDSEL 00 - AdapterA-Slot0 (top) */
	[1] = अणु -1, AU1500_PCI_INTB, AU1500_PCI_INTA, 0xff, 0xff पूर्ण, /* IDSEL 01 - AdapterA-Slot1 (bottom) */
	[2] = अणु -1, AU1500_PCI_INTC, AU1500_PCI_INTD, 0xff, 0xff पूर्ण, /* IDSEL 02 - AdapterB-Slot0 (top) */
	[3] = अणु -1, AU1500_PCI_INTD, AU1500_PCI_INTC, 0xff, 0xff पूर्ण, /* IDSEL 03 - AdapterB-Slot1 (bottom) */
	[4] = अणु -1, AU1500_PCI_INTA, AU1500_PCI_INTB, 0xff, 0xff पूर्ण, /* IDSEL 04 - AdapterC-Slot0 (top) */
	[5] = अणु -1, AU1500_PCI_INTB, AU1500_PCI_INTA, 0xff, 0xff पूर्ण, /* IDSEL 05 - AdapterC-Slot1 (bottom) */
	[6] = अणु -1, AU1500_PCI_INTC, AU1500_PCI_INTD, 0xff, 0xff पूर्ण, /* IDSEL 06 - AdapterD-Slot0 (top) */
	[7] = अणु -1, AU1500_PCI_INTD, AU1500_PCI_INTC, 0xff, 0xff पूर्ण, /* IDSEL 07 - AdapterD-Slot1 (bottom) */
पूर्ण;

अटल पूर्णांक mtx1_map_pci_irq(स्थिर काष्ठा pci_dev *d, u8 slot, u8 pin)
अणु
	वापस mtx1_irqtab[slot][pin];
पूर्ण

अटल काष्ठा alchemy_pci_platdata mtx1_pci_pd = अणु
	.board_map_irq	 = mtx1_map_pci_irq,
	.board_pci_idsel = mtx1_pci_idsel,
	.pci_cfg_set	 = PCI_CONFIG_AEN | PCI_CONFIG_R2H | PCI_CONFIG_R1H |
			   PCI_CONFIG_CH |
#अगर defined(__MIPSEB__)
			   PCI_CONFIG_SIC_HWA_DAT | PCI_CONFIG_SM,
#अन्यथा
			   0,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा platक्रमm_device mtx1_pci_host = अणु
	.dev.platक्रमm_data = &mtx1_pci_pd,
	.name		= "alchemy-pci",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(alchemy_pci_host_res),
	.resource	= alchemy_pci_host_res,
पूर्ण;

अटल काष्ठा platक्रमm_device *mtx1_devs[] __initdata = अणु
	&mtx1_pci_host,
	&mtx1_gpio_leds,
	&mtx1_wdt,
	&mtx1_button,
	&mtx1_mtd,
पूर्ण;

अटल काष्ठा au1000_eth_platक्रमm_data mtx1_au1000_eth0_pdata = अणु
	.phy_search_highest_addr	= 1,
	.phy1_search_mac0		= 1,
पूर्ण;

अटल पूर्णांक __init mtx1_रेजिस्टर_devices(व्योम)
अणु
	पूर्णांक rc;

	irq_set_irq_type(AU1500_GPIO204_INT, IRQ_TYPE_LEVEL_HIGH);
	irq_set_irq_type(AU1500_GPIO201_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO202_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO203_INT, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(AU1500_GPIO205_INT, IRQ_TYPE_LEVEL_LOW);

	au1xxx_override_eth_cfg(0, &mtx1_au1000_eth0_pdata);

	rc = gpio_request(mtx1_gpio_button[0].gpio,
					mtx1_gpio_button[0].desc);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_INFO "mtx1: failed to request %d\n",
					mtx1_gpio_button[0].gpio);
		जाओ out;
	पूर्ण
	gpio_direction_input(mtx1_gpio_button[0].gpio);
out:
	gpiod_add_lookup_table(&mtx1_wdt_gpio_table);
	वापस platक्रमm_add_devices(mtx1_devs, ARRAY_SIZE(mtx1_devs));
पूर्ण
arch_initcall(mtx1_रेजिस्टर_devices);
