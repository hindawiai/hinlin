<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/stargate2.c
 *
 *  Author:	Ed C. Epp
 *  Created:	Nov 05, 2002
 *  Copyright:	Intel Corp.
 *
 *  Modअगरied 2009:  Jonathan Cameron <jic23@cam.ac.uk>
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/plat-ram.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/pcf857x.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/leds.h>
#समावेश <linux/property.h>

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "pxa27x.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "udc.h"
#समावेश "pxa27x-udc.h"
#समावेश <mach/smemc.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/mfd/da903x.h>

#समावेश "devices.h"
#समावेश "generic.h"

#घोषणा STARGATE_NR_IRQS	(IRQ_BOARD_START + 8)

/* Bluetooth */
#घोषणा SG2_BT_RESET		81

/* SD */
#घोषणा SG2_GPIO_nSD_DETECT	90
#घोषणा SG2_SD_POWER_ENABLE	89

अटल अचिन्हित दीर्घ sg2_im2_unअगरied_pin_config[] __initdata = अणु
	/* Device Identअगरication क्रम wakeup*/
	GPIO102_GPIO,
	/* DA9030 */
	GPIO1_GPIO,

	/* MMC */
	GPIO32_MMC_CLK,
	GPIO112_MMC_CMD,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,

	/* 802.15.4 radio - driver out of मुख्यline */
	GPIO22_GPIO,			/* CC_RSTN */
	GPIO114_GPIO,			/* CC_FIFO */
	GPIO116_GPIO,			/* CC_CCA */
	GPIO0_GPIO,			/* CC_FIFOP */
	GPIO16_GPIO,			/* CCSFD */
	GPIO115_GPIO,			/* Power enable */

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* SSP 3 - 802.15.4 radio */
	GPIO39_GPIO,			/* Chip Select */
	GPIO34_SSP3_SCLK,
	GPIO35_SSP3_TXD,
	GPIO41_SSP3_RXD,

	/* SSP 2 to daughter boards */
	GPIO11_SSP2_RXD,
	GPIO38_SSP2_TXD,
	GPIO36_SSP2_SCLK,
	GPIO37_GPIO, /* chip select */

	/* SSP 1 - to daughter boards */
	GPIO24_GPIO,			/* Chip Select */
	GPIO23_SSP1_SCLK,
	GPIO25_SSP1_TXD,
	GPIO26_SSP1_RXD,

	/* BTUART Basic Connector*/
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	/* STUART  - IM2 via debug board not sure on SG2*/
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,

	/* Basic sensor board */
	GPIO96_GPIO,	/* accelerometer पूर्णांकerrupt */
	GPIO99_GPIO,	/* ADC पूर्णांकerrupt */

	/* SHT15 */
	GPIO100_GPIO,
	GPIO98_GPIO,

	/* Basic sensor board */
	GPIO96_GPIO,	/* accelerometer पूर्णांकerrupt */
	GPIO99_GPIO,	/* ADC पूर्णांकerrupt */

	/* Connector pins specअगरied as gpios */
	GPIO94_GPIO, /* large basic connector pin 14 */
	GPIO10_GPIO, /* large basic connector pin 23 */
पूर्ण;

अटल काष्ठा gpiod_lookup_table sht15_gpiod_table = अणु
	.dev_id = "sht15",
	.table = अणु
		/* FIXME: should this have |GPIO_OPEN_DRAIN set? */
		GPIO_LOOKUP("gpio-pxa", 100, "data", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", 98, "clk", GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sht15 = अणु
	.name = "sht15",
	.id = -1,
पूर्ण;

अटल काष्ठा regulator_consumer_supply stargate2_sensor_3_con[] = अणु
	REGULATOR_SUPPLY("vcc", "sht15"),
पूर्ण;

क्रमागत stargate2_lकरोsअणु
	vcc_vref,
	vcc_cc2420,
	/* a mote connector? */
	vcc_mica,
	/* the CSR bluecore chip */
	vcc_bt,
	/* The two voltages available to sensor boards */
	vcc_sensor_1_8,
	vcc_sensor_3,
	/* directly connected to the pxa27x */
	vcc_sram_ext,
	vcc_pxa_pll,
	vcc_pxa_usim, /* Reference voltage क्रम certain gpios */
	vcc_pxa_mem,
	vcc_pxa_flash,
	vcc_pxa_core, /*Dc-Dc buck not yet supported */
	vcc_lcd,
	vcc_bb,
	vcc_bbio, /*not sure!*/
	vcc_io, /* cc2420 802.15.4 radio and pxa vcc_io ?*/
पूर्ण;

/* The values of the various regulator स्थिरraपूर्णांकs are obviously dependent
 * on exactly what is wired to each lकरो.  Unक्रमtunately this inक्रमmation is
 * not generally available.  More inक्रमmation has been requested from Xbow.
 */
अटल काष्ठा regulator_init_data stargate2_lकरो_init_data[] = अणु
	[vcc_bbio] = अणु
		.स्थिरraपूर्णांकs = अणु /* board शेष 1.8V */
			.name = "vcc_bbio",
			.min_uV = 1800000,
			.max_uV = 1800000,
		पूर्ण,
	पूर्ण,
	[vcc_bb] = अणु
		.स्थिरraपूर्णांकs = अणु /* board शेष 2.8V */
			.name = "vcc_bb",
			.min_uV = 2700000,
			.max_uV = 3000000,
		पूर्ण,
	पूर्ण,
	[vcc_pxa_flash] = अणु
		.स्थिरraपूर्णांकs = अणु/* शेष is 1.8V */
			.name = "vcc_pxa_flash",
			.min_uV = 1800000,
			.max_uV = 1800000,
		पूर्ण,
	पूर्ण,
	[vcc_cc2420] = अणु /* also vcc_io */
		.स्थिरraपूर्णांकs = अणु
			/* board शेष is 2.8V */
			.name = "vcc_cc2420",
			.min_uV = 2700000,
			.max_uV = 3300000,
		पूर्ण,
	पूर्ण,
	[vcc_vref] = अणु /* Reference क्रम what? */
		.स्थिरraपूर्णांकs = अणु /* शेष 1.8V */
			.name = "vcc_vref",
			.min_uV = 1800000,
			.max_uV = 1800000,
		पूर्ण,
	पूर्ण,
	[vcc_sram_ext] = अणु
		.स्थिरraपूर्णांकs = अणु /* शेष 2.8V */
			.name = "vcc_sram_ext",
			.min_uV = 2800000,
			.max_uV = 2800000,
		पूर्ण,
	पूर्ण,
	[vcc_mica] = अणु
		.स्थिरraपूर्णांकs = अणु /* शेष 2.8V */
			.name = "vcc_mica",
			.min_uV = 2800000,
			.max_uV = 2800000,
		पूर्ण,
	पूर्ण,
	[vcc_bt] = अणु
		.स्थिरraपूर्णांकs = अणु /* शेष 2.8V */
			.name = "vcc_bt",
			.min_uV = 2800000,
			.max_uV = 2800000,
		पूर्ण,
	पूर्ण,
	[vcc_lcd] = अणु
		.स्थिरraपूर्णांकs = अणु /* शेष 2.8V */
			.name = "vcc_lcd",
			.min_uV = 2700000,
			.max_uV = 3300000,
		पूर्ण,
	पूर्ण,
	[vcc_io] = अणु /* Same or higher than everything
			  * bar vccbat and vccusb */
		.स्थिरraपूर्णांकs = अणु /* शेष 2.8V */
			.name = "vcc_io",
			.min_uV = 2692000,
			.max_uV = 3300000,
		पूर्ण,
	पूर्ण,
	[vcc_sensor_1_8] = अणु
		.स्थिरraपूर्णांकs = अणु /* शेष 1.8V */
			.name = "vcc_sensor_1_8",
			.min_uV = 1800000,
			.max_uV = 1800000,
		पूर्ण,
	पूर्ण,
	[vcc_sensor_3] = अणु /* curiously शेष 2.8V */
		.स्थिरraपूर्णांकs = अणु
			.name = "vcc_sensor_3",
			.min_uV = 2800000,
			.max_uV = 3000000,
		पूर्ण,
		.num_consumer_supplies = ARRAY_SIZE(stargate2_sensor_3_con),
		.consumer_supplies = stargate2_sensor_3_con,
	पूर्ण,
	[vcc_pxa_pll] = अणु /* 1.17V - 1.43V, शेष 1.3V*/
		.स्थिरraपूर्णांकs = अणु
			.name = "vcc_pxa_pll",
			.min_uV = 1170000,
			.max_uV = 1430000,
		पूर्ण,
	पूर्ण,
	[vcc_pxa_usim] = अणु
		.स्थिरraपूर्णांकs = अणु /* शेष 1.8V */
			.name = "vcc_pxa_usim",
			.min_uV = 1710000,
			.max_uV = 2160000,
		पूर्ण,
	पूर्ण,
	[vcc_pxa_mem] = अणु
		.स्थिरraपूर्णांकs = अणु /* शेष 1.8V */
			.name = "vcc_pxa_mem",
			.min_uV = 1800000,
			.max_uV = 1800000,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition stargate2flash_partitions[] = अणु
	अणु
		.name = "Bootloader",
		.size = 0x00040000,
		.offset = 0,
		.mask_flags = 0,
	पूर्ण, अणु
		.name = "Kernel",
		.size = 0x00200000,
		.offset = 0x00040000,
		.mask_flags = 0
	पूर्ण, अणु
		.name = "Filesystem",
		.size = 0x01DC0000,
		.offset = 0x00240000,
		.mask_flags = 0
	पूर्ण,
पूर्ण;

अटल काष्ठा resource flash_resources = अणु
	.start = PXA_CS0_PHYS,
	.end = PXA_CS0_PHYS + SZ_32M - 1,
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data stargate2_flash_data = अणु
	.map_name = "cfi_probe",
	.parts = stargate2flash_partitions,
	.nr_parts = ARRAY_SIZE(stargate2flash_partitions),
	.name = "PXA27xOnChipROM",
	.width = 2,
पूर्ण;

अटल काष्ठा platक्रमm_device stargate2_flash_device = अणु
	.name = "pxa2xx-flash",
	.id = 0,
	.dev = अणु
		.platक्रमm_data = &stargate2_flash_data,
	पूर्ण,
	.resource = &flash_resources,
	.num_resources = 1,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp_master_0_info = अणु
	.num_chipselect = 1,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp_master_1_info = अणु
	.num_chipselect = 1,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp_master_2_info = अणु
	.num_chipselect = 1,
पूर्ण;

/* An upcoming kernel change will scrap SFRM usage so these
 * drivers have been moved to use gpio's via cs_control */
अटल काष्ठा pxa2xx_spi_chip staccel_chip_info = अणु
	.tx_threshold = 8,
	.rx_threshold = 8,
	.dma_burst_size = 8,
	.समयout = 235,
	.gpio_cs = 24,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip cc2420_info = अणु
	.tx_threshold = 8,
	.rx_threshold = 8,
	.dma_burst_size = 8,
	.समयout = 235,
	.gpio_cs = 39,
पूर्ण;

अटल काष्ठा spi_board_info spi_board_info[] __initdata = अणु
	अणु
		.modalias = "lis3l02dq",
		.max_speed_hz = 8000000,/* 8MHz max spi frequency at 3V */
		.bus_num = 1,
		.chip_select = 0,
		.controller_data = &staccel_chip_info,
		.irq = PXA_GPIO_TO_IRQ(96),
	पूर्ण, अणु
		.modalias = "cc2420",
		.max_speed_hz = 6500000,
		.bus_num = 3,
		.chip_select = 0,
		.controller_data = &cc2420_info,
	पूर्ण,
पूर्ण;

अटल व्योम sg2_udc_command(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल PXA2XX_UDC_CMD_CONNECT:
		UP2OCR |=  UP2OCR_HXOE  | UP2OCR_DPPUE | UP2OCR_DPPUBE;
		अवरोध;
	हाल PXA2XX_UDC_CMD_DISCONNECT:
		UP2OCR &= ~(UP2OCR_HXOE  | UP2OCR_DPPUE | UP2OCR_DPPUBE);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा i2c_pxa_platक्रमm_data i2c_pwr_pdata = अणु
	.fast_mode = 1,
पूर्ण;

अटल काष्ठा i2c_pxa_platक्रमm_data i2c_pdata = अणु
	.fast_mode = 1,
पूर्ण;

अटल व्योम __init imote2_stargate2_init(व्योम)
अणु

	pxa2xx_mfp_config(ARRAY_AND_SIZE(sg2_im2_unअगरied_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	pxa2xx_set_spi_info(1, &pxa_ssp_master_0_info);
	pxa2xx_set_spi_info(2, &pxa_ssp_master_1_info);
	pxa2xx_set_spi_info(3, &pxa_ssp_master_2_info);
	spi_रेजिस्टर_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));


	pxa27x_set_i2c_घातer_info(&i2c_pwr_pdata);
	pxa_set_i2c_info(&i2c_pdata);
पूर्ण

#अगर_घोषित CONFIG_MACH_INTELMOTE2
/* As the the imote2 करोesn't currently have a conventional SD slot
 * there is no option to hotplug cards, making all this rather simple
 */
अटल पूर्णांक imote2_mci_get_ro(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

/* Rather simple हाल as hotplugging not possible */
अटल काष्ठा pxamci_platक्रमm_data imote2_mci_platक्रमm_data = अणु
	.ocr_mask = MMC_VDD_32_33 | MMC_VDD_33_34, /* शेष anyway */
	.get_ro = imote2_mci_get_ro,
पूर्ण;

अटल काष्ठा gpio_led imote2_led_pins[] = अणु
	अणु
		.name       =  "imote2:red",
		.gpio       = 103,
		.active_low = 1,
	पूर्ण, अणु
		.name       = "imote2:green",
		.gpio       = 104,
		.active_low = 1,
	पूर्ण, अणु
		.name       = "imote2:blue",
		.gpio       = 105,
		.active_low = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data imote2_led_data = अणु
	.num_leds = ARRAY_SIZE(imote2_led_pins),
	.leds     = imote2_led_pins,
पूर्ण;

अटल काष्ठा platक्रमm_device imote2_leds = अणु
	.name = "leds-gpio",
	.id   = -1,
	.dev = अणु
		.platक्रमm_data = &imote2_led_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा da903x_subdev_info imote2_da9030_subdevs[] = अणु
	अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO2,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_bbio],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO3,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_bb],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO4,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_flash],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO5,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_cc2420],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO6,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_vref],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO7,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_sram_ext],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO8,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_mica],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO9,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_bt],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO10,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_sensor_1_8],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO11,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_sensor_3],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO12,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_lcd],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO15,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_pll],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO17,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_usim],
	पूर्ण, अणु
		.name = "da903x-regulator", /*pxa vcc i/o and cc2420 vcc i/o */
		.id = DA9030_ID_LDO18,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_io],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO19,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_mem],
	पूर्ण,
पूर्ण;

अटल काष्ठा da903x_platक्रमm_data imote2_da9030_pdata = अणु
	.num_subdevs = ARRAY_SIZE(imote2_da9030_subdevs),
	.subdevs = imote2_da9030_subdevs,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata imote2_pwr_i2c_board_info[] = अणु
	अणु
		.type = "da9030",
		.addr = 0x49,
		.platक्रमm_data = &imote2_da9030_pdata,
		.irq = PXA_GPIO_TO_IRQ(1),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata imote2_i2c_board_info[] = अणु
	अणु /* UCAM sensor board */
		.type = "max1239",
		.addr = 0x35,
	पूर्ण, अणु /* ITS400 Sensor board only */
		.type = "max1363",
		.addr = 0x34,
		/* Through a nand gate - Also beware, on V2 sensor board the
		 * pull up resistors are missing.
		 */
		.irq = PXA_GPIO_TO_IRQ(99),
	पूर्ण, अणु /* ITS400 Sensor board only */
		.type = "tsl2561",
		.addr = 0x49,
		/* Through a nand gate - Also beware, on V2 sensor board the
		 * pull up resistors are missing.
		 */
		.irq = PXA_GPIO_TO_IRQ(99),
	पूर्ण, अणु /* ITS400 Sensor board only */
		.type = "tmp175",
		.addr = 0x4A,
		.irq = PXA_GPIO_TO_IRQ(96),
	पूर्ण, अणु /* IMB400 Mulसमयdia board */
		.type = "wm8940",
		.addr = 0x1A,
	पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ imote2_pin_config[] __initdata = अणु

	/* Button */
	GPIO91_GPIO,

	/* LEDS */
	GPIO103_GPIO, /* red led */
	GPIO104_GPIO, /* green led */
	GPIO105_GPIO, /* blue led */
पूर्ण;

अटल काष्ठा pxa2xx_udc_mach_info imote2_udc_info __initdata = अणु
	.udc_command		= sg2_udc_command,
पूर्ण;

अटल काष्ठा platक्रमm_device imote2_audio_device = अणु
	.name = "imote2-audio",
	.id   = -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *imote2_devices[] = अणु
	&stargate2_flash_device,
	&imote2_leds,
	&sht15,
	&imote2_audio_device,
पूर्ण;

अटल व्योम __init imote2_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(imote2_pin_config));

	imote2_stargate2_init();

	gpiod_add_lookup_table(&sht15_gpiod_table);
	platक्रमm_add_devices(imote2_devices, ARRAY_SIZE(imote2_devices));

	i2c_रेजिस्टर_board_info(0, imote2_i2c_board_info,
				ARRAY_SIZE(imote2_i2c_board_info));
	i2c_रेजिस्टर_board_info(1, imote2_pwr_i2c_board_info,
				ARRAY_SIZE(imote2_pwr_i2c_board_info));

	pxa_set_mci_info(&imote2_mci_platक्रमm_data);
	pxa_set_udc_info(&imote2_udc_info);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_STARGATE2

अटल अचिन्हित दीर्घ stargate2_pin_config[] __initdata = अणु

	GPIO15_nCS_1, /* SRAM */
	/* SMC91x */
	GPIO80_nCS_4,
	GPIO40_GPIO, /*cable detect?*/

	/* Button */
	GPIO91_GPIO | WAKEUP_ON_LEVEL_HIGH,

	/* Compact Flash */
	GPIO79_PSKTSEL,
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
	GPIO120_GPIO, /* Buff ctrl */
	GPIO108_GPIO, /* Power ctrl */
	GPIO82_GPIO, /* Reset */
	GPIO53_GPIO, /* SG2_S0_GPIO_DETECT */

	/* MMC not shared with imote2 */
	GPIO90_GPIO, /* nSD detect */
	GPIO89_GPIO, /* SD_POWER_ENABLE */

	/* Bluetooth */
	GPIO81_GPIO, /* reset */
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.name = "smc91x-regs",
		.start = (PXA_CS4_PHYS + 0x300),
		.end = (PXA_CS4_PHYS + 0xfffff),
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = PXA_GPIO_TO_IRQ(40),
		.end = PXA_GPIO_TO_IRQ(40),
		.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा smc91x_platdata stargate2_smc91x_info = अणु
	.flags = SMC91X_USE_8BIT | SMC91X_USE_16BIT | SMC91X_USE_32BIT
	| SMC91X_NOWAIT | SMC91X_USE_DMA,
	.pxa_u16_align4 = true,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name = "smc91x",
	.id = -1,
	.num_resources = ARRAY_SIZE(smc91x_resources),
	.resource = smc91x_resources,
	.dev = अणु
		.platक्रमm_data = &stargate2_smc91x_info,
	पूर्ण,
पूर्ण;


/*
 * The card detect पूर्णांकerrupt isn't debounced so we delay it by 250ms
 * to give the card a chance to fully insert / eject.
 */
अटल पूर्णांक stargate2_mci_init(काष्ठा device *dev,
			      irq_handler_t stargate2_detect_पूर्णांक,
			      व्योम *data)
अणु
	पूर्णांक err;

	err = gpio_request(SG2_SD_POWER_ENABLE, "SG2_sd_power_enable");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Can't get the gpio for SD power control");
		जाओ वापस_err;
	पूर्ण
	gpio_direction_output(SG2_SD_POWER_ENABLE, 0);

	err = gpio_request(SG2_GPIO_nSD_DETECT, "SG2_sd_detect");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Can't get the sd detect gpio");
		जाओ मुक्त_घातer_en;
	पूर्ण
	gpio_direction_input(SG2_GPIO_nSD_DETECT);

	err = request_irq(PXA_GPIO_TO_IRQ(SG2_GPIO_nSD_DETECT),
			  stargate2_detect_पूर्णांक,
			  IRQ_TYPE_EDGE_BOTH,
			  "MMC card detect",
			  data);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "can't request MMC card detect IRQ\n");
		जाओ मुक्त_nsd_detect;
	पूर्ण
	वापस 0;

 मुक्त_nsd_detect:
	gpio_मुक्त(SG2_GPIO_nSD_DETECT);
 मुक्त_घातer_en:
	gpio_मुक्त(SG2_SD_POWER_ENABLE);
 वापस_err:
	वापस err;
पूर्ण

/**
 * stargate2_mci_setघातer() - set state of mmc घातer supply
 *
 * Very simple control. Either it is on or off and is controlled by
 * a gpio pin */
अटल पूर्णांक stargate2_mci_setघातer(काष्ठा device *dev, अचिन्हित पूर्णांक vdd)
अणु
	gpio_set_value(SG2_SD_POWER_ENABLE, !!vdd);
	वापस 0;
पूर्ण

अटल व्योम stargate2_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	मुक्त_irq(PXA_GPIO_TO_IRQ(SG2_GPIO_nSD_DETECT), data);
	gpio_मुक्त(SG2_SD_POWER_ENABLE);
	gpio_मुक्त(SG2_GPIO_nSD_DETECT);
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data stargate2_mci_platक्रमm_data = अणु
	.detect_delay_ms = 250,
	.ocr_mask = MMC_VDD_32_33 | MMC_VDD_33_34,
	.init = stargate2_mci_init,
	.setघातer = stargate2_mci_setघातer,
	.निकास = stargate2_mci_निकास,
पूर्ण;


/*
 * SRAM - The Stargate 2 has 32MB of SRAM.
 *
 * Here it is made available as an MTD. This will then
 * typically have a cअगरs fileप्रणाली created on it to provide
 * fast temporary storage.
 */
अटल काष्ठा resource sram_resources = अणु
	.start = PXA_CS1_PHYS,
	.end = PXA_CS1_PHYS + SZ_32M-1,
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platdata_mtd_ram stargate2_sram_pdata = अणु
	.mapname = "Stargate2 SRAM",
	.bankwidth = 2,
पूर्ण;

अटल काष्ठा platक्रमm_device stargate2_sram = अणु
	.name = "mtd-ram",
	.id = 0,
	.resource = &sram_resources,
	.num_resources = 1,
	.dev = अणु
		.platक्रमm_data = &stargate2_sram_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा pcf857x_platक्रमm_data platक्रमm_data_pcf857x = अणु
	.gpio_base = 128,
	.n_latch = 0,
	.setup = शून्य,
	.tearकरोwn = शून्य,
	.context = शून्य,
पूर्ण;

अटल स्थिर काष्ठा property_entry pca9500_eeprom_properties[] = अणु
	PROPERTY_ENTRY_U32("pagesize", 4),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा software_node pca9500_eeprom_node = अणु
	.properties = pca9500_eeprom_properties,
पूर्ण;

/**
 * stargate2_reset_bluetooth() reset the bluecore to ensure consistent state
 **/
अटल पूर्णांक stargate2_reset_bluetooth(व्योम)
अणु
	पूर्णांक err;
	err = gpio_request(SG2_BT_RESET, "SG2_BT_RESET");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Could not get gpio for bluetooth reset\n");
		वापस err;
	पूर्ण
	gpio_direction_output(SG2_BT_RESET, 1);
	mdelay(5);
	/* now reset it - 5 msec minimum */
	gpio_set_value(SG2_BT_RESET, 0);
	mdelay(10);
	gpio_set_value(SG2_BT_RESET, 1);
	gpio_मुक्त(SG2_BT_RESET);
	वापस 0;
पूर्ण

अटल काष्ठा led_info stargate2_leds[] = अणु
	अणु
		.name = "sg2:red",
		.flags = DA9030_LED_RATE_ON,
	पूर्ण, अणु
		.name = "sg2:blue",
		.flags = DA9030_LED_RATE_ON,
	पूर्ण, अणु
		.name = "sg2:green",
		.flags = DA9030_LED_RATE_ON,
	पूर्ण,
पूर्ण;

अटल काष्ठा da903x_subdev_info stargate2_da9030_subdevs[] = अणु
	अणु
		.name = "da903x-led",
		.id = DA9030_ID_LED_2,
		.platक्रमm_data = &stargate2_leds[0],
	पूर्ण, अणु
		.name = "da903x-led",
		.id = DA9030_ID_LED_3,
		.platक्रमm_data = &stargate2_leds[2],
	पूर्ण, अणु
		.name = "da903x-led",
		.id = DA9030_ID_LED_4,
		.platक्रमm_data = &stargate2_leds[1],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO2,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_bbio],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO3,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_bb],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO4,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_flash],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO5,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_cc2420],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO6,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_vref],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO7,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_sram_ext],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO8,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_mica],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO9,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_bt],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO10,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_sensor_1_8],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO11,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_sensor_3],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO12,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_lcd],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO15,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_pll],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO17,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_usim],
	पूर्ण, अणु
		.name = "da903x-regulator", /*pxa vcc i/o and cc2420 vcc i/o */
		.id = DA9030_ID_LDO18,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_io],
	पूर्ण, अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_LDO19,
		.platक्रमm_data = &stargate2_lकरो_init_data[vcc_pxa_mem],
	पूर्ण,
पूर्ण;

अटल काष्ठा da903x_platक्रमm_data stargate2_da9030_pdata = अणु
	.num_subdevs = ARRAY_SIZE(stargate2_da9030_subdevs),
	.subdevs = stargate2_da9030_subdevs,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata stargate2_pwr_i2c_board_info[] = अणु
	अणु
		.type = "da9030",
		.addr = 0x49,
		.platक्रमm_data = &stargate2_da9030_pdata,
		.irq = PXA_GPIO_TO_IRQ(1),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata stargate2_i2c_board_info[] = अणु
	/* Techically this a pca9500 - but it's compatible with the 8574
	 * क्रम gpio expansion and the 24c02 क्रम eeprom access.
	 */
	अणु
		.type = "pcf8574",
		.addr =  0x27,
		.platक्रमm_data = &platक्रमm_data_pcf857x,
	पूर्ण, अणु
		.type = "24c02",
		.addr = 0x57,
		.swnode = &pca9500_eeprom_node,
	पूर्ण, अणु
		.type = "max1238",
		.addr = 0x35,
	पूर्ण, अणु /* ITS400 Sensor board only */
		.type = "max1363",
		.addr = 0x34,
		/* Through a nand gate - Also beware, on V2 sensor board the
		 * pull up resistors are missing.
		 */
		.irq = PXA_GPIO_TO_IRQ(99),
	पूर्ण, अणु /* ITS400 Sensor board only */
		.type = "tsl2561",
		.addr = 0x49,
		/* Through a nand gate - Also beware, on V2 sensor board the
		 * pull up resistors are missing.
		 */
		.irq = PXA_GPIO_TO_IRQ(99),
	पूर्ण, अणु /* ITS400 Sensor board only */
		.type = "tmp175",
		.addr = 0x4A,
		.irq = PXA_GPIO_TO_IRQ(96),
	पूर्ण,
पूर्ण;

/* Board करोesn't support cable detection - so always lie and say
 * something is there.
 */
अटल पूर्णांक sg2_udc_detect(व्योम)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info stargate2_udc_info __initdata = अणु
	.udc_is_connected	= sg2_udc_detect,
	.udc_command		= sg2_udc_command,
पूर्ण;

अटल काष्ठा platक्रमm_device *stargate2_devices[] = अणु
	&stargate2_flash_device,
	&stargate2_sram,
	&smc91x_device,
	&sht15,
पूर्ण;

अटल व्योम __init stargate2_init(व्योम)
अणु
	/* This is probably a board specअगरic hack as this must be set
	   prior to connecting the MFP stuff up. */
	__raw_ग_लिखोl(__raw_पढ़ोl(MECR) & ~MECR_NOS, MECR);

	pxa2xx_mfp_config(ARRAY_AND_SIZE(stargate2_pin_config));

	imote2_stargate2_init();

	gpiod_add_lookup_table(&sht15_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(stargate2_devices));

	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(stargate2_i2c_board_info));
	i2c_रेजिस्टर_board_info(1, stargate2_pwr_i2c_board_info,
				ARRAY_SIZE(stargate2_pwr_i2c_board_info));

	pxa_set_mci_info(&stargate2_mci_platक्रमm_data);

	pxa_set_udc_info(&stargate2_udc_info);

	stargate2_reset_bluetooth();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_INTELMOTE2
MACHINE_START(INTELMOTE2, "IMOTE 2")
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= imote2_init,
	.atag_offset	= 0x100,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_STARGATE2
MACHINE_START(STARGATE2, "Stargate 2")
	.map_io = pxa27x_map_io,
	.nr_irqs = STARGATE_NR_IRQS,
	.init_irq = pxa27x_init_irq,
	.handle_irq = pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine = stargate2_init,
	.atag_offset = 0x100,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर
