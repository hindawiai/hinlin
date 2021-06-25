<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/poodle.c
 *
 *  Support क्रम the SHARP Poodle Board.
 *
 * Based on:
 *  linux/arch/arm/mach-pxa/lubbock.c Author:	Nicolas Pitre
 *
 * Change Log
 *  12-Dec-2002 Sharp Corporation क्रम Poodle
 *  John Lenz <lenz@cs.wisc.edu> updates to 2.6
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>
#समावेश <linux/pm.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/mtd/sharpsl.h>
#समावेश <linux/memblock.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "pxa25x.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <mach/poodle.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>

#समावेश <यंत्र/hardware/scoop.h>
#समावेश <यंत्र/hardware/locomo.h>
#समावेश <यंत्र/mach/sharpsl_param.h>

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित दीर्घ poodle_pin_config[] __initdata = अणु
	/* I/O */
	GPIO79_nCS_3,
	GPIO80_nCS_4,
	GPIO18_RDY,

	/* Clock */
	GPIO12_32KHz,

	/* SSP1 */
	GPIO23_SSP1_SCLK,
	GPIO25_SSP1_TXD,
	GPIO26_SSP1_RXD,
	GPIO24_GPIO,	/* POODLE_GPIO_TP_CS - SFRM as chip select */

	/* I2S */
	GPIO28_I2S_BITCLK_OUT,
	GPIO29_I2S_SDATA_IN,
	GPIO30_I2S_SDATA_OUT,
	GPIO31_I2S_SYNC,
	GPIO32_I2S_SYSCLK,

	/* Infra-Red */
	GPIO47_FICP_TXD,
	GPIO46_FICP_RXD,

	/* FFUART */
	GPIO40_FFUART_DTR,
	GPIO41_FFUART_RTS,
	GPIO39_FFUART_TXD,
	GPIO37_FFUART_DSR,
	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

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

	/* GPIO */
	GPIO9_GPIO,	/* POODLE_GPIO_nSD_DETECT */
	GPIO7_GPIO,	/* POODLE_GPIO_nSD_WP */
	GPIO3_GPIO,	/* POODLE_GPIO_SD_PWR */
	GPIO33_GPIO,	/* POODLE_GPIO_SD_PWR1 */

	GPIO20_GPIO,	/* POODLE_GPIO_USB_PULLUP */
	GPIO22_GPIO,	/* POODLE_GPIO_IR_ON */
पूर्ण;

अटल काष्ठा resource poodle_scoop_resources[] = अणु
	[0] = अणु
		.start		= 0x10800000,
		.end		= 0x10800fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_config poodle_scoop_setup = अणु
	.io_dir		= POODLE_SCOOP_IO_सूची,
	.io_out		= POODLE_SCOOP_IO_OUT,
	.gpio_base	= POODLE_SCOOP_GPIO_BASE,
पूर्ण;

काष्ठा platक्रमm_device poodle_scoop_device = अणु
	.name		= "sharp-scoop",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &poodle_scoop_setup,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(poodle_scoop_resources),
	.resource	= poodle_scoop_resources,
पूर्ण;

अटल काष्ठा scoop_pcmcia_dev poodle_pcmcia_scoop[] = अणु
अणु
	.dev        = &poodle_scoop_device.dev,
	.irq        = POODLE_IRQ_GPIO_CF_IRQ,
	.cd_irq     = POODLE_IRQ_GPIO_CF_CD,
	.cd_irq_str = "PCMCIA0 CD",
पूर्ण,
पूर्ण;

अटल काष्ठा scoop_pcmcia_config poodle_pcmcia_config = अणु
	.devs         = &poodle_pcmcia_scoop[0],
	.num_devs     = 1,
पूर्ण;

EXPORT_SYMBOL(poodle_scoop_device);


अटल काष्ठा platक्रमm_device poodle_audio_device = अणु
	.name	= "poodle-audio",
	.id	= -1,
पूर्ण;

/* LoCoMo device */
अटल काष्ठा resource locomo_resources[] = अणु
	[0] = अणु
		.start		= 0x10000000,
		.end		= 0x10001fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start		= PXA_GPIO_TO_IRQ(10),
		.end		= PXA_GPIO_TO_IRQ(10),
		.flags		= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा locomo_platक्रमm_data locomo_info = अणु
	.irq_base	= IRQ_BOARD_START,
पूर्ण;

काष्ठा platक्रमm_device poodle_locomo_device = अणु
	.name		= "locomo",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(locomo_resources),
	.resource	= locomo_resources,
	.dev		= अणु
		.platक्रमm_data	= &locomo_info,
	पूर्ण,
पूर्ण;

EXPORT_SYMBOL(poodle_locomo_device);

#अगर defined(CONFIG_SPI_PXA2XX) || defined(CONFIG_SPI_PXA2XX_MODULE)
अटल काष्ठा pxa2xx_spi_controller poodle_spi_info = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा ads7846_platक्रमm_data poodle_ads7846_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,
	.x_plate_ohms		= 419,
	.y_plate_ohms		= 486,
	.gpio_penकरोwn		= POODLE_GPIO_TP_INT,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip poodle_ads7846_chip = अणु
	.gpio_cs		= POODLE_GPIO_TP_CS,
पूर्ण;

अटल काष्ठा spi_board_info poodle_spi_devices[] = अणु
	अणु
		.modalias	= "ads7846",
		.max_speed_hz	= 10000,
		.bus_num	= 1,
		.platक्रमm_data	= &poodle_ads7846_info,
		.controller_data= &poodle_ads7846_chip,
		.irq		= PXA_GPIO_TO_IRQ(POODLE_GPIO_TP_INT),
	पूर्ण,
पूर्ण;

अटल व्योम __init poodle_init_spi(व्योम)
अणु
	pxa2xx_set_spi_info(1, &poodle_spi_info);
	spi_रेजिस्टर_board_info(ARRAY_AND_SIZE(poodle_spi_devices));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम poodle_init_spi(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*
 * MMC/SD Device
 *
 * The card detect पूर्णांकerrupt isn't debounced so we delay it by 250ms
 * to give the card a chance to fully insert/eject.
 */
अटल पूर्णांक poodle_mci_init(काष्ठा device *dev, irq_handler_t poodle_detect_पूर्णांक, व्योम *data)
अणु
	पूर्णांक err;

	err = gpio_request(POODLE_GPIO_SD_PWR, "SD_PWR");
	अगर (err)
		जाओ err_मुक्त_2;

	err = gpio_request(POODLE_GPIO_SD_PWR1, "SD_PWR1");
	अगर (err)
		जाओ err_मुक्त_3;

	gpio_direction_output(POODLE_GPIO_SD_PWR, 0);
	gpio_direction_output(POODLE_GPIO_SD_PWR1, 0);

	वापस 0;

err_मुक्त_3:
	gpio_मुक्त(POODLE_GPIO_SD_PWR);
err_मुक्त_2:
	वापस err;
पूर्ण

अटल पूर्णांक poodle_mci_setघातer(काष्ठा device *dev, अचिन्हित पूर्णांक vdd)
अणु
	काष्ठा pxamci_platक्रमm_data* p_d = dev->platक्रमm_data;

	अगर ((1 << vdd) & p_d->ocr_mask) अणु
		gpio_set_value(POODLE_GPIO_SD_PWR, 1);
		mdelay(2);
		gpio_set_value(POODLE_GPIO_SD_PWR1, 1);
	पूर्ण अन्यथा अणु
		gpio_set_value(POODLE_GPIO_SD_PWR1, 0);
		gpio_set_value(POODLE_GPIO_SD_PWR, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम poodle_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	gpio_मुक्त(POODLE_GPIO_SD_PWR1);
	gpio_मुक्त(POODLE_GPIO_SD_PWR);
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data poodle_mci_platक्रमm_data = अणु
	.detect_delay_ms	= 250,
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	.init 			= poodle_mci_init,
	.setघातer 		= poodle_mci_setघातer,
	.निकास			= poodle_mci_निकास,
पूर्ण;

अटल काष्ठा gpiod_lookup_table poodle_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", POODLE_GPIO_nSD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", POODLE_GPIO_nSD_WP,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Irda
 */
अटल काष्ठा pxaficp_platक्रमm_data poodle_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= POODLE_GPIO_IR_ON,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;


/*
 * USB Device Controller
 */
अटल काष्ठा pxa2xx_udc_mach_info udc_info __initdata = अणु
	/* no connect GPIO; poodle can't tell connection status */
	.gpio_pullup	= POODLE_GPIO_USB_PULLUP,
पूर्ण;


/* PXAFB device */
अटल काष्ठा pxafb_mode_info poodle_fb_mode = अणु
	.pixघड़ी	= 144700,
	.xres		= 320,
	.yres		= 240,
	.bpp		= 16,
	.hsync_len	= 7,
	.left_margin	= 11,
	.right_margin	= 30,
	.vsync_len	= 2,
	.upper_margin	= 2,
	.lower_margin	= 0,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण;

अटल काष्ठा pxafb_mach_info poodle_fb_info = अणु
	.modes		= &poodle_fb_mode,
	.num_modes	= 1,
	.lcd_conn	= LCD_COLOR_TFT_16BPP,
पूर्ण;

अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

अटल काष्ठा nand_bbt_descr sharpsl_bbt = अणु
	.options = 0,
	.offs = 4,
	.len = 2,
	.pattern = scan_ff_pattern
पूर्ण;

अटल स्थिर अक्षर * स्थिर probes[] = अणु
	"cmdlinepart",
	"ofpart",
	"sharpslpart",
	शून्य,
पूर्ण;

अटल काष्ठा sharpsl_nand_platक्रमm_data sharpsl_nand_platक्रमm_data = अणु
	.badblock_pattern	= &sharpsl_bbt,
	.part_parsers		= probes,
पूर्ण;

अटल काष्ठा resource sharpsl_nand_resources[] = अणु
	अणु
		.start	= 0x0C000000,
		.end	= 0x0C000FFF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sharpsl_nand_device = अणु
	.name		= "sharpsl-nand",
	.id		= -1,
	.resource	= sharpsl_nand_resources,
	.num_resources	= ARRAY_SIZE(sharpsl_nand_resources),
	.dev.platक्रमm_data	= &sharpsl_nand_platक्रमm_data,
पूर्ण;

अटल काष्ठा mtd_partition sharpsl_rom_parts[] = अणु
	अणु
		.name	="Boot PROM Filesystem",
		.offset	= 0x00120000,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data sharpsl_rom_data = अणु
	.width		= 2,
	.nr_parts	= ARRAY_SIZE(sharpsl_rom_parts),
	.parts		= sharpsl_rom_parts,
पूर्ण;

अटल काष्ठा resource sharpsl_rom_resources[] = अणु
	अणु
		.start	= 0x00000000,
		.end	= 0x007fffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sharpsl_rom_device = अणु
	.name	= "physmap-flash",
	.id	= -1,
	.resource = sharpsl_rom_resources,
	.num_resources = ARRAY_SIZE(sharpsl_rom_resources),
	.dev.platक्रमm_data = &sharpsl_rom_data,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&poodle_locomo_device,
	&poodle_scoop_device,
	&poodle_audio_device,
	&sharpsl_nand_device,
	&sharpsl_rom_device,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata poodle_i2c_devices[] = अणु
	अणु I2C_BOARD_INFO("wm8731", 0x1b) पूर्ण,
पूर्ण;

अटल व्योम poodle_घातeroff(व्योम)
अणु
	pxa_restart(REBOOT_HARD, शून्य);
पूर्ण

अटल व्योम __init poodle_init(व्योम)
अणु
	पूर्णांक ret = 0;

	pm_घातer_off = poodle_घातeroff;

	PCFR |= PCFR_OPDE;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(poodle_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	platक्रमm_scoop_config = &poodle_pcmcia_config;

	ret = platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	अगर (ret)
		pr_warn("poodle: Unable to register LoCoMo device\n");

	pxa_set_fb_info(&poodle_locomo_device.dev, &poodle_fb_info);
	pxa_set_udc_info(&udc_info);
	gpiod_add_lookup_table(&poodle_mci_gpio_table);
	pxa_set_mci_info(&poodle_mci_platक्रमm_data);
	pxa_set_ficp_info(&poodle_ficp_platक्रमm_data);
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(poodle_i2c_devices));
	poodle_init_spi();
	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल व्योम __init fixup_poodle(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	sharpsl_save_param();
	memblock_add(0xa0000000, SZ_32M);
पूर्ण

MACHINE_START(POODLE, "SHARP Poodle")
	.fixup		= fixup_poodle,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= POODLE_NR_IRQS,	/* 4 क्रम LoCoMo */
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= poodle_init,
	.restart	= pxa_restart,
MACHINE_END
