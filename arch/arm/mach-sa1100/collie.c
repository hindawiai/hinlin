<शैली गुरु>
/*
 * linux/arch/arm/mach-sa1100/collie.c
 *
 * May be copied or modअगरied under the terms of the GNU General Public
 * License.  See linux/COPYING क्रम more inक्रमmation.
 *
 * This file contains all Collie-specअगरic tweaks.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * ChangeLog:
 *  2006 Pavel Machek <pavel@ucw.cz>
 *  03-06-2004 John Lenz <lenz@cs.wisc.edu>
 *  06-04-2002 Chris Larson <kergoth@digitalnemesis.net>
 *  04-16-2001 Lineo Japan,Inc. ...
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_data/sa11x0-serial.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/ucb1x00.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/समयr.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/घातer/gpio-अक्षरger.h>

#समावेश <video/sa1100fb.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <mach/collie.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <linux/platक्रमm_data/irda-sa11x0.h>

#समावेश <यंत्र/hardware/scoop.h>
#समावेश <यंत्र/mach/sharpsl_param.h>
#समावेश <यंत्र/hardware/locomo.h>
#समावेश <linux/platक्रमm_data/mfd-mcp-sa11x0.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

अटल काष्ठा resource collie_scoop_resources[] = अणु
	[0] = DEFINE_RES_MEM(0x40800000, SZ_4K),
पूर्ण;

अटल काष्ठा scoop_config collie_scoop_setup = अणु
	.io_dir 	= COLLIE_SCOOP_IO_सूची,
	.io_out		= COLLIE_SCOOP_IO_OUT,
	.gpio_base	= COLLIE_SCOOP_GPIO_BASE,
पूर्ण;

काष्ठा platक्रमm_device colliescoop_device = अणु
	.name		= "sharp-scoop",
	.id		= -1,
	.dev		= अणु
 		.platक्रमm_data	= &collie_scoop_setup,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(collie_scoop_resources),
	.resource	= collie_scoop_resources,
पूर्ण;

अटल काष्ठा scoop_pcmcia_dev collie_pcmcia_scoop[] = अणु
	अणु
	.dev		= &colliescoop_device.dev,
	.irq		= COLLIE_IRQ_GPIO_CF_IRQ,
	.cd_irq		= COLLIE_IRQ_GPIO_CF_CD,
	.cd_irq_str	= "PCMCIA0 CD",
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_pcmcia_config collie_pcmcia_config = अणु
	.devs		= &collie_pcmcia_scoop[0],
	.num_devs	= 1,
पूर्ण;

अटल काष्ठा ucb1x00_plat_data collie_ucb1x00_data = अणु
	.gpio_base	= COLLIE_TC35143_GPIO_BASE,
पूर्ण;

अटल काष्ठा mcp_plat_data collie_mcp_data = अणु
	.mccr0		= MCCR0_ADM | MCCR0_ExtClk,
	.sclk_rate	= 9216000,
	.codec_pdata	= &collie_ucb1x00_data,
पूर्ण;

/* Battery management GPIOs */
अटल काष्ठा gpiod_lookup_table collie_battery_gpiod_table = अणु
	/* the MCP codec mcp0 has the ucb1x00 as attached device */
	.dev_id = "ucb1x00",
	.table = अणु
		/* This is found on the मुख्य GPIO on the SA1100 */
		GPIO_LOOKUP("gpio", COLLIE_GPIO_CO,
			    "main battery full", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio", COLLIE_GPIO_MAIN_BAT_LOW,
			    "main battery low", GPIO_ACTIVE_HIGH),
		/*
		 * This is GPIO 0 on the Scoop expander, which is रेजिस्टरed
		 * from common/scoop.c with this gpio chip label.
		 */
		GPIO_LOOKUP("sharp-scoop", 0,
			    "main charge on", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक collie_ir_startup(काष्ठा device *dev)
अणु
	पूर्णांक rc = gpio_request(COLLIE_GPIO_IR_ON, "IrDA");
	अगर (rc)
		वापस rc;
	rc = gpio_direction_output(COLLIE_GPIO_IR_ON, 1);

	अगर (!rc)
		वापस 0;

	gpio_मुक्त(COLLIE_GPIO_IR_ON);
	वापस rc;
पूर्ण

अटल व्योम collie_ir_shutकरोwn(काष्ठा device *dev)
अणु
	gpio_मुक्त(COLLIE_GPIO_IR_ON);
पूर्ण

अटल पूर्णांक collie_ir_set_घातer(काष्ठा device *dev, अचिन्हित पूर्णांक state)
अणु
	gpio_set_value(COLLIE_GPIO_IR_ON, !state);
	वापस 0;
पूर्ण

अटल काष्ठा irda_platक्रमm_data collie_ir_data = अणु
	.startup = collie_ir_startup,
	.shutकरोwn = collie_ir_shutकरोwn,
	.set_घातer = collie_ir_set_घातer,
पूर्ण;

/*
 * Collie AC IN
 */
अटल काष्ठा gpiod_lookup_table collie_घातer_gpiod_table = अणु
	.dev_id = "gpio-charger",
	.table = अणु
		GPIO_LOOKUP("gpio", COLLIE_GPIO_AC_IN,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल अक्षर *collie_ac_supplied_to[] = अणु
	"main-battery",
	"backup-battery",
पूर्ण;

अटल काष्ठा gpio_अक्षरger_platक्रमm_data collie_घातer_data = अणु
	.name			= "charger",
	.type			= POWER_SUPPLY_TYPE_MAINS,
	.supplied_to		= collie_ac_supplied_to,
	.num_supplicants	= ARRAY_SIZE(collie_ac_supplied_to),
पूर्ण;

अटल काष्ठा platक्रमm_device collie_घातer_device = अणु
	.name			= "gpio-charger",
	.id			= -1,
	.dev.platक्रमm_data	= &collie_घातer_data,
पूर्ण;

#अगर_घोषित CONFIG_SHARP_LOCOMO
/*
 * low-level UART features.
 */
काष्ठा platक्रमm_device collie_locomo_device;

अटल व्योम collie_uart_set_mctrl(काष्ठा uart_port *port, u_पूर्णांक mctrl)
अणु
	अगर (mctrl & TIOCM_RTS)
		locomo_gpio_ग_लिखो(&collie_locomo_device.dev, LOCOMO_GPIO_RTS, 0);
	अन्यथा
		locomo_gpio_ग_लिखो(&collie_locomo_device.dev, LOCOMO_GPIO_RTS, 1);

	अगर (mctrl & TIOCM_DTR)
		locomo_gpio_ग_लिखो(&collie_locomo_device.dev, LOCOMO_GPIO_DTR, 0);
	अन्यथा
		locomo_gpio_ग_लिखो(&collie_locomo_device.dev, LOCOMO_GPIO_DTR, 1);
पूर्ण

अटल u_पूर्णांक collie_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	पूर्णांक ret = TIOCM_CD;
	अचिन्हित पूर्णांक r;

	r = locomo_gpio_पढ़ो_output(&collie_locomo_device.dev, LOCOMO_GPIO_CTS & LOCOMO_GPIO_DSR);
	अगर (r == -ENODEV)
		वापस ret;
	अगर (r & LOCOMO_GPIO_CTS)
		ret |= TIOCM_CTS;
	अगर (r & LOCOMO_GPIO_DSR)
		ret |= TIOCM_DSR;

	वापस ret;
पूर्ण

अटल काष्ठा sa1100_port_fns collie_port_fns __initdata = अणु
	.set_mctrl	= collie_uart_set_mctrl,
	.get_mctrl	= collie_uart_get_mctrl,
पूर्ण;

अटल पूर्णांक collie_uart_probe(काष्ठा locomo_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा locomo_driver collie_uart_driver = अणु
	.drv = अणु
		.name = "collie_uart",
	पूर्ण,
	.devid	= LOCOMO_DEVID_UART,
	.probe	= collie_uart_probe,
पूर्ण;

अटल पूर्णांक __init collie_uart_init(व्योम)
अणु
	वापस locomo_driver_रेजिस्टर(&collie_uart_driver);
पूर्ण
device_initcall(collie_uart_init);

#पूर्ण_अगर


अटल काष्ठा resource locomo_resources[] = अणु
	[0] = DEFINE_RES_MEM(0x40000000, SZ_8K),
	[1] = DEFINE_RES_IRQ(IRQ_GPIO25),
पूर्ण;

अटल काष्ठा locomo_platक्रमm_data locomo_info = अणु
	.irq_base	= IRQ_BOARD_START,
पूर्ण;

काष्ठा platक्रमm_device collie_locomo_device = अणु
	.name		= "locomo",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &locomo_info,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(locomo_resources),
	.resource	= locomo_resources,
पूर्ण;

अटल काष्ठा gpio_keys_button collie_gpio_keys[] = अणु
	अणु
		.type	= EV_PWR,
		.code	= KEY_RESERVED,
		.gpio	= COLLIE_GPIO_ON_KEY,
		.desc	= "On key",
		.wakeup	= 1,
		.active_low = 1,
	पूर्ण,
	अणु
		.type	= EV_PWR,
		.code	= KEY_WAKEUP,
		.gpio	= COLLIE_GPIO_WAKEUP,
		.desc	= "Sync",
		.wakeup = 1,
		.active_low = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data collie_gpio_keys_data = अणु
	.buttons	= collie_gpio_keys,
	.nbuttons	= ARRAY_SIZE(collie_gpio_keys),
पूर्ण;

अटल काष्ठा platक्रमm_device collie_gpio_keys_device = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &collie_gpio_keys_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&collie_locomo_device,
	&colliescoop_device,
	&collie_घातer_device,
	&collie_gpio_keys_device,
पूर्ण;

अटल काष्ठा mtd_partition collie_partitions[] = अणु
	अणु
		.name		= "bootloader",
		.offset 	= 0,
		.size		= 0x000C0000,
		.mask_flags	= MTD_WRITEABLE
	पूर्ण, अणु
		.name		= "kernel",
		.offset 	= MTDPART_OFS_APPEND,
		.size		= 0x00100000,
	पूर्ण, अणु
		.name		= "rootfs",
		.offset 	= MTDPART_OFS_APPEND,
		.size		= 0x00e20000,
	पूर्ण, अणु
		.name		= "bootblock",
		.offset		= MTDPART_OFS_APPEND,
		.size		= 0x00020000,
		.mask_flags	= MTD_WRITEABLE
	पूर्ण
पूर्ण;

अटल पूर्णांक collie_flash_init(व्योम)
अणु
	पूर्णांक rc = gpio_request(COLLIE_GPIO_VPEN, "flash Vpp enable");
	अगर (rc)
		वापस rc;

	rc = gpio_direction_output(COLLIE_GPIO_VPEN, 1);
	अगर (rc)
		gpio_मुक्त(COLLIE_GPIO_VPEN);

	वापस rc;
पूर्ण

अटल व्योम collie_set_vpp(पूर्णांक vpp)
अणु
	gpio_set_value(COLLIE_GPIO_VPEN, vpp);
पूर्ण

अटल व्योम collie_flash_निकास(व्योम)
अणु
	gpio_मुक्त(COLLIE_GPIO_VPEN);
पूर्ण

अटल काष्ठा flash_platक्रमm_data collie_flash_data = अणु
	.map_name	= "cfi_probe",
	.init		= collie_flash_init,
	.set_vpp	= collie_set_vpp,
	.निकास		= collie_flash_निकास,
	.parts		= collie_partitions,
	.nr_parts	= ARRAY_SIZE(collie_partitions),
पूर्ण;

अटल काष्ठा resource collie_flash_resources[] = अणु
	DEFINE_RES_MEM(SA1100_CS0_PHYS, SZ_32M),
पूर्ण;

अटल काष्ठा sa1100fb_mach_info collie_lcd_info = अणु
	.pixघड़ी	= 171521,	.bpp		= 16,
	.xres		= 320,		.yres		= 240,

	.hsync_len	= 5,		.vsync_len	= 1,
	.left_margin	= 11,		.upper_margin	= 2,
	.right_margin	= 30,		.lower_margin	= 0,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,

	.lccr0		= LCCR0_Color | LCCR0_Sngl | LCCR0_Act,
	.lccr3		= LCCR3_OutEnH | LCCR3_PixRsEdg | LCCR3_ACBsDiv(2),

#अगर_घोषित CONFIG_BACKLIGHT_LOCOMO
	.lcd_घातer	= locomolcd_घातer
#पूर्ण_अगर
पूर्ण;

अटल व्योम __init collie_init(व्योम)
अणु
	पूर्णांक ret = 0;

	/* cpu initialize */
	GAFR = GPIO_SSP_TXD | GPIO_SSP_SCLK | GPIO_SSP_SFRM | GPIO_SSP_CLK |
		GPIO_MCP_CLK | GPIO_32_768kHz;

	GPDR = GPIO_LDD8 | GPIO_LDD9 | GPIO_LDD10 | GPIO_LDD11 | GPIO_LDD12 |
		GPIO_LDD13 | GPIO_LDD14 | GPIO_LDD15 | GPIO_SSP_TXD |
		GPIO_SSP_SCLK | GPIO_SSP_SFRM | GPIO_SDLC_SCLK |
		_COLLIE_GPIO_UCB1x00_RESET | _COLLIE_GPIO_nMIC_ON |
		_COLLIE_GPIO_nREMOCON_ON | GPIO_32_768kHz;

	PPDR = PPC_LDD0 | PPC_LDD1 | PPC_LDD2 | PPC_LDD3 | PPC_LDD4 | PPC_LDD5 |
		PPC_LDD6 | PPC_LDD7 | PPC_L_PCLK | PPC_L_LCLK | PPC_L_FCLK | PPC_L_BIAS |
		PPC_TXD1 | PPC_TXD2 | PPC_TXD3 | PPC_TXD4 | PPC_SCLK | PPC_SFRM;

	PWER = 0;

	PGSR = _COLLIE_GPIO_nREMOCON_ON;

	PSDR = PPC_RXD1 | PPC_RXD2 | PPC_RXD3 | PPC_RXD4;

	PCFR = PCFR_OPDE;

	GPSR |= _COLLIE_GPIO_UCB1x00_RESET;

	sa11x0_ppc_configure_mcp();


	platक्रमm_scoop_config = &collie_pcmcia_config;

	gpiod_add_lookup_table(&collie_घातer_gpiod_table);
	gpiod_add_lookup_table(&collie_battery_gpiod_table);

	ret = platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "collie: Unable to register LoCoMo device\n");
	पूर्ण

	sa11x0_रेजिस्टर_lcd(&collie_lcd_info);
	sa11x0_रेजिस्टर_mtd(&collie_flash_data, collie_flash_resources,
			    ARRAY_SIZE(collie_flash_resources));
	sa11x0_रेजिस्टर_mcp(&collie_mcp_data);
	sa11x0_रेजिस्टर_irda(&collie_ir_data);

	sharpsl_save_param();
पूर्ण

अटल काष्ठा map_desc collie_io_desc[] __initdata = अणु
	अणु	/* 32M मुख्य flash (cs0) */
		.भव	= 0xe8000000,
		.pfn		= __phys_to_pfn(0x00000000),
		.length		= 0x02000000,
		.type		= MT_DEVICE
	पूर्ण, अणु	/* 32M boot flash (cs1) */
		.भव	= 0xea000000,
		.pfn		= __phys_to_pfn(0x08000000),
		.length		= 0x02000000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init collie_map_io(व्योम)
अणु
	sa1100_map_io();
	iotable_init(collie_io_desc, ARRAY_SIZE(collie_io_desc));

#अगर_घोषित CONFIG_SHARP_LOCOMO
	sa1100_रेजिस्टर_uart_fns(&collie_port_fns);
#पूर्ण_अगर
	sa1100_रेजिस्टर_uart(0, 3);
	sa1100_रेजिस्टर_uart(1, 1);
पूर्ण

MACHINE_START(COLLIE, "Sharp-Collie")
	.map_io		= collie_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= collie_init,
	.init_late	= sa11x0_init_late,
	.restart	= sa11x0_restart,
MACHINE_END
