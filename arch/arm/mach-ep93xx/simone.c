<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/simone.c
 * Simplemachines Sim.One support.
 *
 * Copyright (C) 2010 Ryan Mallon
 *
 * Based on the 2.6.24.7 support:
 *   Copyright (C) 2009 Simplemachines
 *   MMC support by Peter Ivanov <ivanovp@gmail.com>, 2007
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/mmc_spi.h>
#समावेश <linux/platक्रमm_data/video-ep93xx.h>
#समावेश <linux/platक्रमm_data/spi-ep93xx.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>

#समावेश "hardware.h"
#समावेश "gpio-ep93xx.h"

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "soc.h"

अटल काष्ठा ep93xx_eth_data __initdata simone_eth_data = अणु
	.phy_id		= 1,
पूर्ण;

अटल काष्ठा ep93xxfb_mach_info __initdata simone_fb_info = अणु
	.flags		= EP93XXFB_USE_SDCSN0 | EP93XXFB_PCLK_FALLING,
पूर्ण;

अटल काष्ठा mmc_spi_platक्रमm_data simone_mmc_spi_data = अणु
	.detect_delay	= 500,
	.ocr_mask	= MMC_VDD_32_33 | MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table simone_mmc_spi_gpio_table = अणु
	.dev_id = "mmc_spi.0", /* "mmc_spi" @ CS0 */
	.table = अणु
		/* Card detect */
		GPIO_LOOKUP_IDX("A", 0, शून्य, 0, GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info simone_spi_devices[] __initdata = अणु
	अणु
		.modalias		= "mmc_spi",
		.platक्रमm_data		= &simone_mmc_spi_data,
		/*
		 * We use 10 MHz even though the maximum is 3.7 MHz. The driver
		 * will limit it स्वतःmatically to max. frequency.
		 */
		.max_speed_hz		= 10 * 1000 * 1000,
		.bus_num		= 0,
		.chip_select		= 0,
		.mode			= SPI_MODE_3,
	पूर्ण,
पूर्ण;

/*
 * Up to v1.3, the Sim.One used SFRMOUT as SD card chip select, but this goes
 * low between multi-message command blocks. From v1.4, it uses a GPIO instead.
 * v1.3 parts will still work, since the संकेत on SFRMOUT is स्वतःmatic.
 */
अटल काष्ठा gpiod_lookup_table simone_spi_cs_gpio_table = अणु
	.dev_id = "spi0",
	.table = अणु
		GPIO_LOOKUP("A", 1, "cs", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ep93xx_spi_info simone_spi_info __initdata = अणु
	.use_dma = 1,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata simone_i2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("ds1337", 0x68),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device simone_audio_device = अणु
	.name		= "simone-audio",
	.id		= -1,
पूर्ण;

अटल व्योम __init simone_रेजिस्टर_audio(व्योम)
अणु
	ep93xx_रेजिस्टर_ac97();
	platक्रमm_device_रेजिस्टर(&simone_audio_device);
पूर्ण

अटल व्योम __init simone_init_machine(व्योम)
अणु
	ep93xx_init_devices();
	ep93xx_रेजिस्टर_flash(2, EP93XX_CS6_PHYS_BASE, SZ_8M);
	ep93xx_रेजिस्टर_eth(&simone_eth_data, 1);
	ep93xx_रेजिस्टर_fb(&simone_fb_info);
	ep93xx_रेजिस्टर_i2c(simone_i2c_board_info,
			    ARRAY_SIZE(simone_i2c_board_info));
	gpiod_add_lookup_table(&simone_mmc_spi_gpio_table);
	gpiod_add_lookup_table(&simone_spi_cs_gpio_table);
	ep93xx_रेजिस्टर_spi(&simone_spi_info, simone_spi_devices,
			    ARRAY_SIZE(simone_spi_devices));
	simone_रेजिस्टर_audio();
पूर्ण

MACHINE_START(SIM_ONE, "Simplemachines Sim.One Board")
	/* Maपूर्णांकainer: Ryan Mallon */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= simone_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
