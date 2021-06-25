<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/lubbock.c
 *
 *  Support क्रम the Intel DBPXA250 Development Platक्रमm.
 *
 *  Author:	Nicolas Pitre
 *  Created:	Jun 15, 2001
 *  Copyright:	MontaVista Software Inc.
 */
#समावेश <linux/clkdev.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/gpio-reg.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/major.h>
#समावेश <linux/fb.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/spi/pxa2xx_spi.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश <यंत्र/hardware/sa1111.h>

#समावेश "pxa25x.h"
#समावेश <mach/audपन.स>
#समावेश <mach/lubbock.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "pm.h"
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित दीर्घ lubbock_pin_config[] __initdata = अणु
	GPIO15_nCS_1,	/* CS1 - Flash */
	GPIO78_nCS_2,	/* CS2 - Baseboard FGPA */
	GPIO79_nCS_3,	/* CS3 - SMC ethernet */
	GPIO80_nCS_4,	/* CS4 - SA1111 */

	/* SSP data pins */
	GPIO23_SSP1_SCLK,
	GPIO25_SSP1_TXD,
	GPIO26_SSP1_RXD,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* LCD - 16bpp DSTN */
	GPIOxx_LCD_DSTN_16BPP,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	/* PC Card */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO52_nPCE_1,
	GPIO53_nPCE_2,
	GPIO54_nPSKTSEL,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,

	/* MMC */
	GPIO6_MMC_CLK,
	GPIO8_MMC_CS0,

	/* SA1111 chip */
	GPIO11_3_6MHz,

	/* wakeup */
	GPIO1_GPIO | WAKEUP_ON_EDGE_RISE,
पूर्ण;

#घोषणा LUB_HEXLED		__LUB_REG(LUBBOCK_FPGA_PHYS + 0x010)

व्योम lubbock_set_hexled(uपूर्णांक32_t value)
अणु
	LUB_HEXLED = value;
पूर्ण

अटल काष्ठा gpio_chip *lubbock_misc_wr_gc;

अटल व्योम lubbock_set_misc_wr(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक set)
अणु
	अचिन्हित दीर्घ m = mask, v = set;
	lubbock_misc_wr_gc->set_multiple(lubbock_misc_wr_gc, &m, &v);
पूर्ण

अटल पूर्णांक lubbock_udc_is_connected(व्योम)
अणु
	वापस (LUB_MISC_RD & (1 << 9)) == 0;
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info udc_info __initdata = अणु
	.udc_is_connected	= lubbock_udc_is_connected,
	// no D+ pullup; lubbock can't connect/disconnect in software
पूर्ण;

/* GPIOs क्रम SA1111 PCMCIA */
अटल काष्ठा gpiod_lookup_table sa1111_pcmcia_gpio_table = अणु
	.dev_id = "1800",
	.table = अणु
		अणु "sa1111", 0, "a0vpp", GPIO_ACTIVE_HIGH पूर्ण,
		अणु "sa1111", 1, "a1vpp", GPIO_ACTIVE_HIGH पूर्ण,
		अणु "sa1111", 2, "a0vcc", GPIO_ACTIVE_HIGH पूर्ण,
		अणु "sa1111", 3, "a1vcc", GPIO_ACTIVE_HIGH पूर्ण,
		अणु "lubbock", 14, "b0vcc", GPIO_ACTIVE_HIGH पूर्ण,
		अणु "lubbock", 15, "b1vcc", GPIO_ACTIVE_HIGH पूर्ण,
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम lubbock_init_pcmcia(व्योम)
अणु
	काष्ठा clk *clk;

	gpiod_add_lookup_table(&sa1111_pcmcia_gpio_table);

	/* Add an alias क्रम the SA1111 PCMCIA घड़ी */
	clk = clk_get_sys("pxa2xx-pcmcia", शून्य);
	अगर (!IS_ERR(clk)) अणु
		clkdev_create(clk, शून्य, "1800");
		clk_put(clk);
	पूर्ण
पूर्ण

अटल काष्ठा resource sa1111_resources[] = अणु
	[0] = अणु
		.start	= 0x10000000,
		.end	= 0x10001fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= LUBBOCK_SA1111_IRQ,
		.end	= LUBBOCK_SA1111_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा sa1111_platक्रमm_data sa1111_info = अणु
	.irq_base	= LUBBOCK_SA1111_IRQ_BASE,
	.disable_devs	= SA1111_DEVID_SAC,
पूर्ण;

अटल काष्ठा platक्रमm_device sa1111_device = अणु
	.name		= "sa1111",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(sa1111_resources),
	.resource	= sa1111_resources,
	.dev		= अणु
		.platक्रमm_data	= &sa1111_info,
	पूर्ण,
पूर्ण;

/* ADS7846 is connected through SSP ... and अगर your board has J5 populated,
 * you can select it to replace the ucb1400 by चयनing the touchscreen cable
 * (to J5) and poking board रेजिस्टरs (as करोne below).  Else it's only useful
 * क्रम the temperature sensors.
 */
अटल काष्ठा pxa2xx_spi_controller pxa_ssp_master_info = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल पूर्णांक lubbock_ads7846_penकरोwn_state(व्योम)
अणु
	/* TS_BUSY is bit 8 in LUB_MISC_RD, but penकरोwn is irq-only */
	वापस 0;
पूर्ण

अटल काष्ठा ads7846_platक्रमm_data ads_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,		/* पूर्णांकernal, no cap */
	.get_penकरोwn_state	= lubbock_ads7846_penकरोwn_state,
	// .x_plate_ohms		= 500,	/* GUESS! */
	// .y_plate_ohms		= 500,	/* GUESS! */
पूर्ण;

अटल व्योम ads7846_cs(u32 command)
अणु
	अटल स्थिर अचिन्हित	TS_nCS = 1 << 11;
	lubbock_set_misc_wr(TS_nCS, (command == PXA2XX_CS_ASSERT) ? 0 : TS_nCS);
पूर्ण

अटल काष्ठा pxa2xx_spi_chip ads_hw = अणु
	.tx_threshold		= 1,
	.rx_threshold		= 2,
	.cs_control		= ads7846_cs,
पूर्ण;

अटल काष्ठा spi_board_info spi_board_info[] __initdata = अणु अणु
	.modalias	= "ads7846",
	.platक्रमm_data	= &ads_info,
	.controller_data = &ads_hw,
	.irq		= LUBBOCK_BB_IRQ,
	.max_speed_hz	= 120000 /* max sample rate at 3V */
				* 26 /* command + data + overhead */,
	.bus_num	= 1,
	.chip_select	= 0,
पूर्ण,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.name	= "smc91x-regs",
		.start	= 0x0c000c00,
		.end	= 0x0c0fffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= LUBBOCK_ETH_IRQ,
		.end	= LUBBOCK_ETH_IRQ,
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
	[2] = अणु
		.name	= "smc91x-attrib",
		.start	= 0x0e000000,
		.end	= 0x0e0fffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा smc91x_platdata lubbock_smc91x_info = अणु
	.flags	= SMC91X_USE_16BIT | SMC91X_NOWAIT | SMC91X_IO_SHIFT_2,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev		= अणु
		.platक्रमm_data = &lubbock_smc91x_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource flash_resources[] = अणु
	[0] = अणु
		.start	= 0x00000000,
		.end	= SZ_64M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= 0x04000000,
		.end	= 0x04000000 + SZ_64M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition lubbock_partitions[] = अणु
	अणु
		.name =		"Bootloader",
		.size =		0x00040000,
		.offset =	0,
		.mask_flags =	MTD_WRITEABLE  /* क्रमce पढ़ो-only */
	पूर्ण,अणु
		.name =		"Kernel",
		.size =		0x00100000,
		.offset =	0x00040000,
	पूर्ण,अणु
		.name =		"Filesystem",
		.size =		MTDPART_SIZ_FULL,
		.offset =	0x00140000
	पूर्ण
पूर्ण;

अटल काष्ठा flash_platक्रमm_data lubbock_flash_data[2] = अणु
	अणु
		.map_name	= "cfi_probe",
		.parts		= lubbock_partitions,
		.nr_parts	= ARRAY_SIZE(lubbock_partitions),
	पूर्ण, अणु
		.map_name	= "cfi_probe",
		.parts		= शून्य,
		.nr_parts	= 0,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device lubbock_flash_device[2] = अणु
	अणु
		.name		= "pxa2xx-flash",
		.id		= 0,
		.dev = अणु
			.platक्रमm_data = &lubbock_flash_data[0],
		पूर्ण,
		.resource = &flash_resources[0],
		.num_resources = 1,
	पूर्ण,
	अणु
		.name		= "pxa2xx-flash",
		.id		= 1,
		.dev = अणु
			.platक्रमm_data = &lubbock_flash_data[1],
		पूर्ण,
		.resource = &flash_resources[1],
		.num_resources = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource lubbock_cplds_resources[] = अणु
	[0] = अणु
		.start	= LUBBOCK_FPGA_PHYS + 0xc0,
		.end	= LUBBOCK_FPGA_PHYS + 0xe0 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(0),
		.end	= PXA_GPIO_TO_IRQ(0),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
	[2] = अणु
		.start	= LUBBOCK_IRQ(0),
		.end	= LUBBOCK_IRQ(6),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device lubbock_cplds_device = अणु
	.name		= "pxa_cplds_irqs",
	.id		= -1,
	.resource	= &lubbock_cplds_resources[0],
	.num_resources	= 3,
पूर्ण;


अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&sa1111_device,
	&smc91x_device,
	&lubbock_flash_device[0],
	&lubbock_flash_device[1],
	&lubbock_cplds_device,
पूर्ण;

अटल काष्ठा pxafb_mode_info sharp_lm8v31_mode = अणु
	.pixघड़ी	= 270000,
	.xres		= 640,
	.yres		= 480,
	.bpp		= 16,
	.hsync_len	= 1,
	.left_margin	= 3,
	.right_margin	= 3,
	.vsync_len	= 1,
	.upper_margin	= 0,
	.lower_margin	= 0,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.cmap_greyscale	= 0,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lm8v31 = अणु
	.modes		= &sharp_lm8v31_mode,
	.num_modes	= 1,
	.cmap_inverse	= 0,
	.cmap_अटल	= 0,
	.lcd_conn	= LCD_COLOR_DSTN_16BPP | LCD_PCLK_EDGE_FALL |
			  LCD_AC_BIAS_FREQ(255),
पूर्ण;

#घोषणा	MMC_POLL_RATE		msecs_to_jअगरfies(1000)

अटल irq_handler_t mmc_detect_पूर्णांक;
अटल व्योम *mmc_detect_पूर्णांक_data;
अटल काष्ठा समयr_list mmc_समयr;

अटल व्योम lubbock_mmc_poll(काष्ठा समयr_list *unused)
अणु
	अचिन्हित दीर्घ flags;

	/* clear any previous irq state, then ... */
	local_irq_save(flags);
	LUB_IRQ_SET_CLR &= ~(1 << 0);
	local_irq_restore(flags);

	/* poll until mmc/sd card is हटाओd */
	अगर (LUB_IRQ_SET_CLR & (1 << 0))
		mod_समयr(&mmc_समयr, jअगरfies + MMC_POLL_RATE);
	अन्यथा अणु
		(व्योम) mmc_detect_पूर्णांक(LUBBOCK_SD_IRQ, mmc_detect_पूर्णांक_data);
		enable_irq(LUBBOCK_SD_IRQ);
	पूर्ण
पूर्ण

अटल irqवापस_t lubbock_detect_पूर्णांक(पूर्णांक irq, व्योम *data)
अणु
	/* IRQ is level triggered; disable, and poll क्रम removal */
	disable_irq(irq);
	mod_समयr(&mmc_समयr, jअगरfies + MMC_POLL_RATE);

	वापस mmc_detect_पूर्णांक(irq, data);
पूर्ण

अटल पूर्णांक lubbock_mci_init(काष्ठा device *dev,
		irq_handler_t detect_पूर्णांक,
		व्योम *data)
अणु
	/* detect card insert/eject */
	mmc_detect_पूर्णांक = detect_पूर्णांक;
	mmc_detect_पूर्णांक_data = data;
	समयr_setup(&mmc_समयr, lubbock_mmc_poll, 0);
	वापस request_irq(LUBBOCK_SD_IRQ, lubbock_detect_पूर्णांक,
			   0, "lubbock-sd-detect", data);
पूर्ण

अटल पूर्णांक lubbock_mci_get_ro(काष्ठा device *dev)
अणु
	वापस (LUB_MISC_RD & (1 << 2)) != 0;
पूर्ण

अटल व्योम lubbock_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	मुक्त_irq(LUBBOCK_SD_IRQ, data);
	del_समयr_sync(&mmc_समयr);
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data lubbock_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	.detect_delay_ms	= 10,
	.init 			= lubbock_mci_init,
	.get_ro			= lubbock_mci_get_ro,
	.निकास 			= lubbock_mci_निकास,
पूर्ण;

अटल व्योम lubbock_irda_transceiver_mode(काष्ठा device *dev, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (mode & IR_SIRMODE) अणु
		lubbock_set_misc_wr(BIT(4), 0);
	पूर्ण अन्यथा अगर (mode & IR_FIRMODE) अणु
		lubbock_set_misc_wr(BIT(4), BIT(4));
	पूर्ण
	pxa2xx_transceiver_mode(dev, mode);
	local_irq_restore(flags);
पूर्ण

अटल काष्ठा pxaficp_platक्रमm_data lubbock_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= -1,
	.transceiver_cap	= IR_SIRMODE | IR_FIRMODE,
	.transceiver_mode	= lubbock_irda_transceiver_mode,
पूर्ण;

अटल व्योम __init lubbock_init(व्योम)
अणु
	पूर्णांक flashboot = (LUB_CONF_SWITCHES & 1);

	pxa2xx_mfp_config(ARRAY_AND_SIZE(lubbock_pin_config));

	lubbock_misc_wr_gc = gpio_reg_init(शून्य, (व्योम *)&LUB_MISC_WR,
					   -1, 16, "lubbock", 0, LUB_MISC_WR,
					   शून्य, शून्य, शून्य);
	अगर (IS_ERR(lubbock_misc_wr_gc)) अणु
		pr_err("Lubbock: unable to register lubbock GPIOs: %ld\n",
		       PTR_ERR(lubbock_misc_wr_gc));
		lubbock_misc_wr_gc = शून्य;
	पूर्ण

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	lubbock_init_pcmcia();

	clk_add_alias("SA1111_CLK", शून्य, "GPIO11_CLK", शून्य);
	pxa_set_udc_info(&udc_info);
	pxa_set_fb_info(शून्य, &sharp_lm8v31);
	pxa_set_mci_info(&lubbock_mci_platक्रमm_data);
	pxa_set_ficp_info(&lubbock_ficp_platक्रमm_data);
	pxa_set_ac97_info(शून्य);

	lubbock_flash_data[0].width = lubbock_flash_data[1].width =
		(__raw_पढ़ोl(BOOT_DEF) & 1) ? 2 : 4;
	/* Compensate क्रम the nROMBT चयन which swaps the flash banks */
	prपूर्णांकk(KERN_NOTICE "Lubbock configured to boot from %s (bank %d)\n",
	       flashboot?"Flash":"ROM", flashboot);

	lubbock_flash_data[flashboot^1].name = "application-flash";
	lubbock_flash_data[flashboot].name = "boot-rom";
	(व्योम) platक्रमm_add_devices(devices, ARRAY_SIZE(devices));

	pxa2xx_set_spi_info(1, &pxa_ssp_master_info);
	spi_रेजिस्टर_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));
पूर्ण

अटल काष्ठा map_desc lubbock_io_desc[] __initdata = अणु
  	अणु	/* CPLD */
		.भव	=  LUBBOCK_FPGA_VIRT,
		.pfn		= __phys_to_pfn(LUBBOCK_FPGA_PHYS),
		.length		= 0x00100000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init lubbock_map_io(व्योम)
अणु
	pxa25x_map_io();
	iotable_init(lubbock_io_desc, ARRAY_SIZE(lubbock_io_desc));

	PCFR |= PCFR_OPDE;
पूर्ण

/*
 * Driver क्रम the 8 discrete LEDs available क्रम general use:
 * Note: bits [15-8] are used to enable/blank the 8 7 segment hex displays
 * so be sure to not monkey with them here.
 */

#अगर defined(CONFIG_NEW_LEDS) && defined(CONFIG_LEDS_CLASS)
काष्ठा lubbock_led अणु
	काष्ठा led_classdev	cdev;
	u8			mask;
पूर्ण;

/*
 * The triggers lines up below will only be used अगर the
 * LED triggers are compiled in.
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण lubbock_leds[] = अणु
	अणु "lubbock:D28", "default-on", पूर्ण,
	अणु "lubbock:D27", "cpu0", पूर्ण,
	अणु "lubbock:D26", "heartbeat" पूर्ण,
	अणु "lubbock:D25", पूर्ण,
	अणु "lubbock:D24", पूर्ण,
	अणु "lubbock:D23", पूर्ण,
	अणु "lubbock:D22", पूर्ण,
	अणु "lubbock:D21", पूर्ण,
पूर्ण;

अटल व्योम lubbock_led_set(काष्ठा led_classdev *cdev,
			      क्रमागत led_brightness b)
अणु
	काष्ठा lubbock_led *led = container_of(cdev,
					 काष्ठा lubbock_led, cdev);
	u32 reg = LUB_DISC_BLNK_LED;

	अगर (b != LED_OFF)
		reg |= led->mask;
	अन्यथा
		reg &= ~led->mask;

	LUB_DISC_BLNK_LED = reg;
पूर्ण

अटल क्रमागत led_brightness lubbock_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा lubbock_led *led = container_of(cdev,
					 काष्ठा lubbock_led, cdev);
	u32 reg = LUB_DISC_BLNK_LED;

	वापस (reg & led->mask) ? LED_FULL : LED_OFF;
पूर्ण

अटल पूर्णांक __init lubbock_leds_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!machine_is_lubbock())
		वापस -ENODEV;

	/* All ON */
	LUB_DISC_BLNK_LED |= 0xff;
	क्रम (i = 0; i < ARRAY_SIZE(lubbock_leds); i++) अणु
		काष्ठा lubbock_led *led;

		led = kzalloc(माप(*led), GFP_KERNEL);
		अगर (!led)
			अवरोध;

		led->cdev.name = lubbock_leds[i].name;
		led->cdev.brightness_set = lubbock_led_set;
		led->cdev.brightness_get = lubbock_led_get;
		led->cdev.शेष_trigger = lubbock_leds[i].trigger;
		led->mask = BIT(i);

		अगर (led_classdev_रेजिस्टर(शून्य, &led->cdev) < 0) अणु
			kमुक्त(led);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Since we may have triggers on any subप्रणाली, defer registration
 * until after subप्रणाली_init.
 */
fs_initcall(lubbock_leds_init);
#पूर्ण_अगर

MACHINE_START(LUBBOCK, "Intel DBPXA250 Development Platform (aka Lubbock)")
	/* Maपूर्णांकainer: MontaVista Software Inc. */
	.map_io		= lubbock_map_io,
	.nr_irqs	= LUBBOCK_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= lubbock_init,
	.restart	= pxa_restart,
MACHINE_END
