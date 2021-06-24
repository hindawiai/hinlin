<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006,2007 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2006,2007 Eugene Konev <ejka@खोलोwrt.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/vlynq.h>
#समावेश <linux/leds.h>
#समावेश <linux/माला.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/clk.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/mach-ar7/ar7.h>
#समावेश <यंत्र/mach-ar7/prom.h>

/*****************************************************************************
 * VLYNQ Bus
 ****************************************************************************/
काष्ठा plat_vlynq_data अणु
	काष्ठा plat_vlynq_ops ops;
	पूर्णांक gpio_bit;
	पूर्णांक reset_bit;
पूर्ण;

अटल पूर्णांक vlynq_on(काष्ठा vlynq_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा plat_vlynq_data *pdata = dev->dev.platक्रमm_data;

	ret = gpio_request(pdata->gpio_bit, "vlynq");
	अगर (ret)
		जाओ out;

	ar7_device_reset(pdata->reset_bit);

	ret = ar7_gpio_disable(pdata->gpio_bit);
	अगर (ret)
		जाओ out_enabled;

	ret = ar7_gpio_enable(pdata->gpio_bit);
	अगर (ret)
		जाओ out_enabled;

	ret = gpio_direction_output(pdata->gpio_bit, 0);
	अगर (ret)
		जाओ out_gpio_enabled;

	msleep(50);

	gpio_set_value(pdata->gpio_bit, 1);

	msleep(50);

	वापस 0;

out_gpio_enabled:
	ar7_gpio_disable(pdata->gpio_bit);
out_enabled:
	ar7_device_disable(pdata->reset_bit);
	gpio_मुक्त(pdata->gpio_bit);
out:
	वापस ret;
पूर्ण

अटल व्योम vlynq_off(काष्ठा vlynq_device *dev)
अणु
	काष्ठा plat_vlynq_data *pdata = dev->dev.platक्रमm_data;

	ar7_gpio_disable(pdata->gpio_bit);
	gpio_मुक्त(pdata->gpio_bit);
	ar7_device_disable(pdata->reset_bit);
पूर्ण

अटल काष्ठा resource vlynq_low_res[] = अणु
	अणु
		.name	= "regs",
		.flags	= IORESOURCE_MEM,
		.start	= AR7_REGS_VLYNQ0,
		.end	= AR7_REGS_VLYNQ0 + 0xff,
	पूर्ण,
	अणु
		.name	= "irq",
		.flags	= IORESOURCE_IRQ,
		.start	= 29,
		.end	= 29,
	पूर्ण,
	अणु
		.name	= "mem",
		.flags	= IORESOURCE_MEM,
		.start	= 0x04000000,
		.end	= 0x04ffffff,
	पूर्ण,
	अणु
		.name	= "devirq",
		.flags	= IORESOURCE_IRQ,
		.start	= 80,
		.end	= 111,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource vlynq_high_res[] = अणु
	अणु
		.name	= "regs",
		.flags	= IORESOURCE_MEM,
		.start	= AR7_REGS_VLYNQ1,
		.end	= AR7_REGS_VLYNQ1 + 0xff,
	पूर्ण,
	अणु
		.name	= "irq",
		.flags	= IORESOURCE_IRQ,
		.start	= 33,
		.end	= 33,
	पूर्ण,
	अणु
		.name	= "mem",
		.flags	= IORESOURCE_MEM,
		.start	= 0x0c000000,
		.end	= 0x0cffffff,
	पूर्ण,
	अणु
		.name	= "devirq",
		.flags	= IORESOURCE_IRQ,
		.start	= 112,
		.end	= 143,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_vlynq_data vlynq_low_data = अणु
	.ops = अणु
		.on	= vlynq_on,
		.off	= vlynq_off,
	पूर्ण,
	.reset_bit	= 20,
	.gpio_bit	= 18,
पूर्ण;

अटल काष्ठा plat_vlynq_data vlynq_high_data = अणु
	.ops = अणु
		.on	= vlynq_on,
		.off	= vlynq_off,
	पूर्ण,
	.reset_bit	= 16,
	.gpio_bit	= 19,
पूर्ण;

अटल काष्ठा platक्रमm_device vlynq_low = अणु
	.id		= 0,
	.name		= "vlynq",
	.dev = अणु
		.platक्रमm_data	= &vlynq_low_data,
	पूर्ण,
	.resource	= vlynq_low_res,
	.num_resources	= ARRAY_SIZE(vlynq_low_res),
पूर्ण;

अटल काष्ठा platक्रमm_device vlynq_high = अणु
	.id		= 1,
	.name		= "vlynq",
	.dev = अणु
		.platक्रमm_data	= &vlynq_high_data,
	पूर्ण,
	.resource	= vlynq_high_res,
	.num_resources	= ARRAY_SIZE(vlynq_high_res),
पूर्ण;

/*****************************************************************************
 * Flash
 ****************************************************************************/
अटल काष्ठा resource physmap_flash_resource = अणु
	.name	= "mem",
	.flags	= IORESOURCE_MEM,
	.start	= 0x10000000,
	.end	= 0x107fffff,
पूर्ण;

अटल स्थिर अक्षर *ar7_probe_types[] = अणु "ar7part", शून्य पूर्ण;

अटल काष्ठा physmap_flash_data physmap_flash_data = अणु
	.width	= 2,
	.part_probe_types = ar7_probe_types,
पूर्ण;

अटल काष्ठा platक्रमm_device physmap_flash = अणु
	.name		= "physmap-flash",
	.dev = अणु
		.platक्रमm_data	= &physmap_flash_data,
	पूर्ण,
	.resource	= &physmap_flash_resource,
	.num_resources	= 1,
पूर्ण;

/*****************************************************************************
 * Ethernet
 ****************************************************************************/
अटल काष्ठा resource cpmac_low_res[] = अणु
	अणु
		.name	= "regs",
		.flags	= IORESOURCE_MEM,
		.start	= AR7_REGS_MAC0,
		.end	= AR7_REGS_MAC0 + 0x7ff,
	पूर्ण,
	अणु
		.name	= "irq",
		.flags	= IORESOURCE_IRQ,
		.start	= 27,
		.end	= 27,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource cpmac_high_res[] = अणु
	अणु
		.name	= "regs",
		.flags	= IORESOURCE_MEM,
		.start	= AR7_REGS_MAC1,
		.end	= AR7_REGS_MAC1 + 0x7ff,
	पूर्ण,
	अणु
		.name	= "irq",
		.flags	= IORESOURCE_IRQ,
		.start	= 41,
		.end	= 41,
	पूर्ण,
पूर्ण;

अटल काष्ठा fixed_phy_status fixed_phy_status __initdata = अणु
	.link		= 1,
	.speed		= 100,
	.duplex		= 1,
पूर्ण;

अटल काष्ठा plat_cpmac_data cpmac_low_data = अणु
	.reset_bit	= 17,
	.घातer_bit	= 20,
	.phy_mask	= 0x80000000,
पूर्ण;

अटल काष्ठा plat_cpmac_data cpmac_high_data = अणु
	.reset_bit	= 21,
	.घातer_bit	= 22,
	.phy_mask	= 0x7fffffff,
पूर्ण;

अटल u64 cpmac_dma_mask = DMA_BIT_MASK(32);

अटल काष्ठा platक्रमm_device cpmac_low = अणु
	.id		= 0,
	.name		= "cpmac",
	.dev = अणु
		.dma_mask		= &cpmac_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &cpmac_low_data,
	पूर्ण,
	.resource	= cpmac_low_res,
	.num_resources	= ARRAY_SIZE(cpmac_low_res),
पूर्ण;

अटल काष्ठा platक्रमm_device cpmac_high = अणु
	.id		= 1,
	.name		= "cpmac",
	.dev = अणु
		.dma_mask		= &cpmac_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
		.platक्रमm_data		= &cpmac_high_data,
	पूर्ण,
	.resource	= cpmac_high_res,
	.num_resources	= ARRAY_SIZE(cpmac_high_res),
पूर्ण;

अटल व्योम __init cpmac_get_mac(पूर्णांक instance, अचिन्हित अक्षर *dev_addr)
अणु
	अक्षर name[5], *mac;

	प्र_लिखो(name, "mac%c", 'a' + instance);
	mac = prom_दो_पर्या(name);
	अगर (!mac && instance) अणु
		प्र_लिखो(name, "mac%c", 'a');
		mac = prom_दो_पर्या(name);
	पूर्ण

	अगर (mac) अणु
		अगर (!mac_pton(mac, dev_addr)) अणु
			pr_warn("cannot parse mac address, using random address\n");
			eth_अक्रमom_addr(dev_addr);
		पूर्ण
	पूर्ण अन्यथा
		eth_अक्रमom_addr(dev_addr);
पूर्ण

/*****************************************************************************
 * USB
 ****************************************************************************/
अटल काष्ठा resource usb_res[] = अणु
	अणु
		.name	= "regs",
		.flags	= IORESOURCE_MEM,
		.start	= AR7_REGS_USB,
		.end	= AR7_REGS_USB + 0xff,
	पूर्ण,
	अणु
		.name	= "irq",
		.flags	= IORESOURCE_IRQ,
		.start	= 32,
		.end	= 32,
	पूर्ण,
	अणु
		.name	= "mem",
		.flags	= IORESOURCE_MEM,
		.start	= 0x03400000,
		.end	= 0x03401fff,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ar7_udc = अणु
	.name		= "ar7_udc",
	.resource	= usb_res,
	.num_resources	= ARRAY_SIZE(usb_res),
पूर्ण;

/*****************************************************************************
 * LEDs
 ****************************************************************************/
अटल स्थिर काष्ठा gpio_led शेष_leds[] = अणु
	अणु
		.name			= "status",
		.gpio			= 8,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led titan_leds[] = अणु
	अणु .name = "status", .gpio = 8, .active_low = 1, पूर्ण,
	अणु .name = "wifi", .gpio = 13, .active_low = 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led dsl502t_leds[] = अणु
	अणु
		.name			= "status",
		.gpio			= 9,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "ethernet",
		.gpio			= 7,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "usb",
		.gpio			= 12,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led dg834g_leds[] = अणु
	अणु
		.name			= "ppp",
		.gpio			= 6,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "status",
		.gpio			= 7,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "adsl",
		.gpio			= 8,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "wifi",
		.gpio			= 12,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "power",
		.gpio			= 14,
		.active_low		= 1,
		.शेष_trigger	= "default-on",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led fb_sl_leds[] = अणु
	अणु
		.name			= "1",
		.gpio			= 7,
	पूर्ण,
	अणु
		.name			= "2",
		.gpio			= 13,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "3",
		.gpio			= 10,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "4",
		.gpio			= 12,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "5",
		.gpio			= 9,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led fb_fon_leds[] = अणु
	अणु
		.name			= "1",
		.gpio			= 8,
	पूर्ण,
	अणु
		.name			= "2",
		.gpio			= 3,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "3",
		.gpio			= 5,
	पूर्ण,
	अणु
		.name			= "4",
		.gpio			= 4,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "5",
		.gpio			= 11,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gpio_led gt701_leds[] = अणु
	अणु
		.name			= "inet:green",
		.gpio			= 13,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "usb",
		.gpio			= 12,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "inet:red",
		.gpio			= 9,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "power:red",
		.gpio			= 7,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "power:green",
		.gpio			= 8,
		.active_low		= 1,
		.शेष_trigger	= "default-on",
	पूर्ण,
	अणु
		.name			= "ethernet",
		.gpio			= 10,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data ar7_led_data;

अटल काष्ठा platक्रमm_device ar7_gpio_leds = अणु
	.name = "leds-gpio",
	.dev = अणु
		.platक्रमm_data = &ar7_led_data,
	पूर्ण
पूर्ण;

अटल व्योम __init detect_leds(व्योम)
अणु
	अक्षर *prid, *usb_prod;

	/* Default LEDs */
	ar7_led_data.num_leds = ARRAY_SIZE(शेष_leds);
	ar7_led_data.leds = शेष_leds;

	/* FIXME: the whole thing is unreliable */
	prid = prom_दो_पर्या("ProductID");
	usb_prod = prom_दो_पर्या("usb_prod");

	/* If we can't get the product id from PROM, use the शेष LEDs */
	अगर (!prid)
		वापस;

	अगर (म_माला(prid, "Fritz_Box_FON")) अणु
		ar7_led_data.num_leds = ARRAY_SIZE(fb_fon_leds);
		ar7_led_data.leds = fb_fon_leds;
	पूर्ण अन्यथा अगर (म_माला(prid, "Fritz_Box_")) अणु
		ar7_led_data.num_leds = ARRAY_SIZE(fb_sl_leds);
		ar7_led_data.leds = fb_sl_leds;
	पूर्ण अन्यथा अगर ((!म_भेद(prid, "AR7RD") || !म_भेद(prid, "AR7DB"))
		&& usb_prod != शून्य && म_माला(usb_prod, "DSL-502T")) अणु
		ar7_led_data.num_leds = ARRAY_SIZE(dsl502t_leds);
		ar7_led_data.leds = dsl502t_leds;
	पूर्ण अन्यथा अगर (म_माला(prid, "DG834")) अणु
		ar7_led_data.num_leds = ARRAY_SIZE(dg834g_leds);
		ar7_led_data.leds = dg834g_leds;
	पूर्ण अन्यथा अगर (म_माला(prid, "CYWM") || म_माला(prid, "CYWL")) अणु
		ar7_led_data.num_leds = ARRAY_SIZE(titan_leds);
		ar7_led_data.leds = titan_leds;
	पूर्ण अन्यथा अगर (म_माला(prid, "GT701")) अणु
		ar7_led_data.num_leds = ARRAY_SIZE(gt701_leds);
		ar7_led_data.leds = gt701_leds;
	पूर्ण
पूर्ण

/*****************************************************************************
 * Watchकरोg
 ****************************************************************************/
अटल काष्ठा resource ar7_wdt_res = अणु
	.name		= "regs",
	.flags		= IORESOURCE_MEM,
	.start		= -1,	/* Filled at runसमय */
	.end		= -1,	/* Filled at runसमय */
पूर्ण;

अटल काष्ठा platक्रमm_device ar7_wdt = अणु
	.name		= "ar7_wdt",
	.resource	= &ar7_wdt_res,
	.num_resources	= 1,
पूर्ण;

/*****************************************************************************
 * Init
 ****************************************************************************/
अटल पूर्णांक __init ar7_रेजिस्टर_uarts(व्योम)
अणु
#अगर_घोषित CONFIG_SERIAL_8250
	अटल काष्ठा uart_port uart_port __initdata;
	काष्ठा clk *bus_clk;
	पूर्णांक res;

	स_रखो(&uart_port, 0, माप(काष्ठा uart_port));

	bus_clk = clk_get(शून्य, "bus");
	अगर (IS_ERR(bus_clk))
		panic("unable to get bus clk");

	uart_port.type		= PORT_AR7;
	uart_port.uartclk	= clk_get_rate(bus_clk) / 2;
	uart_port.iotype	= UPIO_MEM32;
	uart_port.flags		= UPF_FIXED_TYPE | UPF_BOOT_AUTOCONF;
	uart_port.regshअगरt	= 2;

	uart_port.line		= 0;
	uart_port.irq		= AR7_IRQ_UART0;
	uart_port.mapbase	= AR7_REGS_UART0;
	uart_port.membase	= ioremap(uart_port.mapbase, 256);

	res = early_serial_setup(&uart_port);
	अगर (res)
		वापस res;

	/* Only TNETD73xx have a second serial port */
	अगर (ar7_has_second_uart()) अणु
		uart_port.line		= 1;
		uart_port.irq		= AR7_IRQ_UART1;
		uart_port.mapbase	= UR8_REGS_UART1;
		uart_port.membase	= ioremap(uart_port.mapbase, 256);

		res = early_serial_setup(&uart_port);
		अगर (res)
			वापस res;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __init titan_fixup_devices(व्योम)
अणु
	/* Set vlynq0 data */
	vlynq_low_data.reset_bit = 15;
	vlynq_low_data.gpio_bit = 14;

	/* Set vlynq1 data */
	vlynq_high_data.reset_bit = 16;
	vlynq_high_data.gpio_bit = 7;

	/* Set vlynq0 resources */
	vlynq_low_res[0].start = TITAN_REGS_VLYNQ0;
	vlynq_low_res[0].end = TITAN_REGS_VLYNQ0 + 0xff;
	vlynq_low_res[1].start = 33;
	vlynq_low_res[1].end = 33;
	vlynq_low_res[2].start = 0x0c000000;
	vlynq_low_res[2].end = 0x0fffffff;
	vlynq_low_res[3].start = 80;
	vlynq_low_res[3].end = 111;

	/* Set vlynq1 resources */
	vlynq_high_res[0].start = TITAN_REGS_VLYNQ1;
	vlynq_high_res[0].end = TITAN_REGS_VLYNQ1 + 0xff;
	vlynq_high_res[1].start = 34;
	vlynq_high_res[1].end = 34;
	vlynq_high_res[2].start = 0x40000000;
	vlynq_high_res[2].end = 0x43ffffff;
	vlynq_high_res[3].start = 112;
	vlynq_high_res[3].end = 143;

	/* Set cpmac0 data */
	cpmac_low_data.phy_mask = 0x40000000;

	/* Set cpmac1 data */
	cpmac_high_data.phy_mask = 0x80000000;

	/* Set cpmac0 resources */
	cpmac_low_res[0].start = TITAN_REGS_MAC0;
	cpmac_low_res[0].end = TITAN_REGS_MAC0 + 0x7ff;

	/* Set cpmac1 resources */
	cpmac_high_res[0].start = TITAN_REGS_MAC1;
	cpmac_high_res[0].end = TITAN_REGS_MAC1 + 0x7ff;
पूर्ण

अटल पूर्णांक __init ar7_रेजिस्टर_devices(व्योम)
अणु
	व्योम __iomem *bootcr;
	u32 val;
	पूर्णांक res;

	res = ar7_gpio_init();
	अगर (res)
		pr_warn("unable to register gpios: %d\n", res);

	res = ar7_रेजिस्टर_uarts();
	अगर (res)
		pr_err("unable to setup uart(s): %d\n", res);

	res = platक्रमm_device_रेजिस्टर(&physmap_flash);
	अगर (res)
		pr_warn("unable to register physmap-flash: %d\n", res);

	अगर (ar7_is_titan())
		titan_fixup_devices();

	ar7_device_disable(vlynq_low_data.reset_bit);
	res = platक्रमm_device_रेजिस्टर(&vlynq_low);
	अगर (res)
		pr_warn("unable to register vlynq-low: %d\n", res);

	अगर (ar7_has_high_vlynq()) अणु
		ar7_device_disable(vlynq_high_data.reset_bit);
		res = platक्रमm_device_रेजिस्टर(&vlynq_high);
		अगर (res)
			pr_warn("unable to register vlynq-high: %d\n", res);
	पूर्ण

	अगर (ar7_has_high_cpmac()) अणु
		res = fixed_phy_add(PHY_POLL, cpmac_high.id,
				    &fixed_phy_status);
		अगर (!res) अणु
			cpmac_get_mac(1, cpmac_high_data.dev_addr);

			res = platक्रमm_device_रेजिस्टर(&cpmac_high);
			अगर (res)
				pr_warn("unable to register cpmac-high: %d\n",
					res);
		पूर्ण अन्यथा
			pr_warn("unable to add cpmac-high phy: %d\n", res);
	पूर्ण अन्यथा
		cpmac_low_data.phy_mask = 0xffffffff;

	res = fixed_phy_add(PHY_POLL, cpmac_low.id, &fixed_phy_status);
	अगर (!res) अणु
		cpmac_get_mac(0, cpmac_low_data.dev_addr);
		res = platक्रमm_device_रेजिस्टर(&cpmac_low);
		अगर (res)
			pr_warn("unable to register cpmac-low: %d\n", res);
	पूर्ण अन्यथा
		pr_warn("unable to add cpmac-low phy: %d\n", res);

	detect_leds();
	res = platक्रमm_device_रेजिस्टर(&ar7_gpio_leds);
	अगर (res)
		pr_warn("unable to register leds: %d\n", res);

	res = platक्रमm_device_रेजिस्टर(&ar7_udc);
	अगर (res)
		pr_warn("unable to register usb slave: %d\n", res);

	/* Register watchकरोg only अगर enabled in hardware */
	bootcr = ioremap(AR7_REGS_DCL, 4);
	val = पढ़ोl(bootcr);
	iounmap(bootcr);
	अगर (val & AR7_WDT_HW_ENA) अणु
		अगर (ar7_has_high_vlynq())
			ar7_wdt_res.start = UR8_REGS_WDT;
		अन्यथा
			ar7_wdt_res.start = AR7_REGS_WDT;

		ar7_wdt_res.end = ar7_wdt_res.start + 0x20;
		res = platक्रमm_device_रेजिस्टर(&ar7_wdt);
		अगर (res)
			pr_warn("unable to register watchdog: %d\n", res);
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(ar7_रेजिस्टर_devices);
