<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/vision_ep9307.c
 * Vision Engraving Systems EP9307 SoM support.
 *
 * Copyright (C) 2008-2011 Vision Engraving Systems
 * H Hartley Sweeten <hsweeten@visionengravers.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/fb.h>
#समावेश <linux/पन.स>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/flash.h>
#समावेश <linux/spi/mmc_spi.h>
#समावेश <linux/mmc/host.h>

#समावेश <sound/cs4271.h>

#समावेश "hardware.h"
#समावेश <linux/platक्रमm_data/video-ep93xx.h>
#समावेश <linux/platक्रमm_data/spi-ep93xx.h>
#समावेश "gpio-ep93xx.h"

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "soc.h"

/*************************************************************************
 * Static I/O mappings क्रम the FPGA
 *************************************************************************/
#घोषणा VISION_PHYS_BASE	EP93XX_CS7_PHYS_BASE
#घोषणा VISION_VIRT_BASE	0xfebff000

अटल काष्ठा map_desc vision_io_desc[] __initdata = अणु
	अणु
		.भव	= VISION_VIRT_BASE,
		.pfn		= __phys_to_pfn(VISION_PHYS_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init vision_map_io(व्योम)
अणु
	ep93xx_map_io();

	iotable_init(vision_io_desc, ARRAY_SIZE(vision_io_desc));
पूर्ण

/*************************************************************************
 * Ethernet
 *************************************************************************/
अटल काष्ठा ep93xx_eth_data vision_eth_data __initdata = अणु
	.phy_id		= 1,
पूर्ण;

/*************************************************************************
 * Framebuffer
 *************************************************************************/
#घोषणा VISION_LCD_ENABLE	EP93XX_GPIO_LINE_EGPIO1

अटल पूर्णांक vision_lcd_setup(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;

	err = gpio_request_one(VISION_LCD_ENABLE, GPIOF_INIT_HIGH,
				dev_name(&pdev->dev));
	अगर (err)
		वापस err;

	ep93xx_devcfg_clear_bits(EP93XX_SYSCON_DEVCFG_RAS |
				 EP93XX_SYSCON_DEVCFG_RASONP3 |
				 EP93XX_SYSCON_DEVCFG_EXVC);

	वापस 0;
पूर्ण

अटल व्योम vision_lcd_tearकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	gpio_मुक्त(VISION_LCD_ENABLE);
पूर्ण

अटल व्योम vision_lcd_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	अगर (blank_mode)
		gpio_set_value(VISION_LCD_ENABLE, 0);
	अन्यथा
		gpio_set_value(VISION_LCD_ENABLE, 1);
पूर्ण

अटल काष्ठा ep93xxfb_mach_info ep93xxfb_info __initdata = अणु
	.flags		= EP93XXFB_USE_SDCSN0 | EP93XXFB_PCLK_FALLING,
	.setup		= vision_lcd_setup,
	.tearकरोwn	= vision_lcd_tearकरोwn,
	.blank		= vision_lcd_blank,
पूर्ण;


/*************************************************************************
 * GPIO Expanders
 *************************************************************************/
#घोषणा PCA9539_74_GPIO_BASE	(EP93XX_GPIO_LINE_MAX + 1)
#घोषणा PCA9539_75_GPIO_BASE	(PCA9539_74_GPIO_BASE + 16)
#घोषणा PCA9539_76_GPIO_BASE	(PCA9539_75_GPIO_BASE + 16)
#घोषणा PCA9539_77_GPIO_BASE	(PCA9539_76_GPIO_BASE + 16)

अटल काष्ठा pca953x_platक्रमm_data pca953x_74_gpio_data = अणु
	.gpio_base	= PCA9539_74_GPIO_BASE,
	.irq_base	= EP93XX_BOARD_IRQ(0),
पूर्ण;

अटल काष्ठा pca953x_platक्रमm_data pca953x_75_gpio_data = अणु
	.gpio_base	= PCA9539_75_GPIO_BASE,
	.irq_base	= -1,
पूर्ण;

अटल काष्ठा pca953x_platक्रमm_data pca953x_76_gpio_data = अणु
	.gpio_base	= PCA9539_76_GPIO_BASE,
	.irq_base	= -1,
पूर्ण;

अटल काष्ठा pca953x_platक्रमm_data pca953x_77_gpio_data = अणु
	.gpio_base	= PCA9539_77_GPIO_BASE,
	.irq_base	= -1,
पूर्ण;

/*************************************************************************
 * I2C Bus
 *************************************************************************/

अटल काष्ठा i2c_board_info vision_i2c_info[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("isl1208", 0x6f),
		.irq		= IRQ_EP93XX_EXT1,
	पूर्ण, अणु
		I2C_BOARD_INFO("pca9539", 0x74),
		.platक्रमm_data	= &pca953x_74_gpio_data,
	पूर्ण, अणु
		I2C_BOARD_INFO("pca9539", 0x75),
		.platक्रमm_data	= &pca953x_75_gpio_data,
	पूर्ण, अणु
		I2C_BOARD_INFO("pca9539", 0x76),
		.platक्रमm_data	= &pca953x_76_gpio_data,
	पूर्ण, अणु
		I2C_BOARD_INFO("pca9539", 0x77),
		.platक्रमm_data	= &pca953x_77_gpio_data,
	पूर्ण,
पूर्ण;

/*************************************************************************
 * SPI CS4271 Audio Codec
 *************************************************************************/
अटल काष्ठा cs4271_platक्रमm_data vision_cs4271_data = अणु
	.gpio_nreset	= EP93XX_GPIO_LINE_H(2),
पूर्ण;

/*************************************************************************
 * SPI Flash
 *************************************************************************/
अटल काष्ठा mtd_partition vision_spi_flash_partitions[] = अणु
	अणु
		.name	= "SPI bootstrap",
		.offset	= 0,
		.size	= SZ_4K,
	पूर्ण, अणु
		.name	= "Bootstrap config",
		.offset	= MTDPART_OFS_APPEND,
		.size	= SZ_4K,
	पूर्ण, अणु
		.name	= "System config",
		.offset	= MTDPART_OFS_APPEND,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data vision_spi_flash_data = अणु
	.name		= "SPI Flash",
	.parts		= vision_spi_flash_partitions,
	.nr_parts	= ARRAY_SIZE(vision_spi_flash_partitions),
पूर्ण;

/*************************************************************************
 * SPI SD/MMC host
 *************************************************************************/
अटल काष्ठा mmc_spi_platक्रमm_data vision_spi_mmc_data = अणु
	.detect_delay	= 100,
	.घातerup_msecs	= 100,
	.ocr_mask	= MMC_VDD_32_33 | MMC_VDD_33_34,
	.caps2		= MMC_CAP2_RO_ACTIVE_HIGH,
पूर्ण;

अटल काष्ठा gpiod_lookup_table vision_spi_mmc_gpio_table = अणु
	.dev_id = "mmc_spi.2", /* "mmc_spi @ CS2 */
	.table = अणु
		/* Card detect */
		GPIO_LOOKUP_IDX("B", 7, शून्य, 0, GPIO_ACTIVE_LOW),
		/* Write protect */
		GPIO_LOOKUP_IDX("F", 0, शून्य, 1, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*************************************************************************
 * SPI Bus
 *************************************************************************/
अटल काष्ठा spi_board_info vision_spi_board_info[] __initdata = अणु
	अणु
		.modalias		= "cs4271",
		.platक्रमm_data		= &vision_cs4271_data,
		.max_speed_hz		= 6000000,
		.bus_num		= 0,
		.chip_select		= 0,
		.mode			= SPI_MODE_3,
	पूर्ण, अणु
		.modalias		= "sst25l",
		.platक्रमm_data		= &vision_spi_flash_data,
		.max_speed_hz		= 20000000,
		.bus_num		= 0,
		.chip_select		= 1,
		.mode			= SPI_MODE_3,
	पूर्ण, अणु
		.modalias		= "mmc_spi",
		.platक्रमm_data		= &vision_spi_mmc_data,
		.max_speed_hz		= 20000000,
		.bus_num		= 0,
		.chip_select		= 2,
		.mode			= SPI_MODE_3,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table vision_spi_cs_gpio_table = अणु
	.dev_id = "spi0",
	.table = अणु
		GPIO_LOOKUP_IDX("A", 6, "cs", 0, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("A", 7, "cs", 1, GPIO_ACTIVE_LOW),
		GPIO_LOOKUP_IDX("G", 2, "cs", 2, GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ep93xx_spi_info vision_spi_master __initdata = अणु
	.use_dma	= 1,
पूर्ण;

/*************************************************************************
 * I2S Audio
 *************************************************************************/
अटल काष्ठा platक्रमm_device vision_audio_device = अणु
	.name		= "edb93xx-audio",
	.id		= -1,
पूर्ण;

अटल व्योम __init vision_रेजिस्टर_i2s(व्योम)
अणु
	ep93xx_रेजिस्टर_i2s();
	platक्रमm_device_रेजिस्टर(&vision_audio_device);
पूर्ण

/*************************************************************************
 * Machine Initialization
 *************************************************************************/
अटल व्योम __init vision_init_machine(व्योम)
अणु
	ep93xx_init_devices();
	ep93xx_रेजिस्टर_flash(2, EP93XX_CS6_PHYS_BASE, SZ_64M);
	ep93xx_रेजिस्टर_eth(&vision_eth_data, 1);
	ep93xx_रेजिस्टर_fb(&ep93xxfb_info);
	ep93xx_रेजिस्टर_pwm(1, 0);

	/*
	 * Request the gpio expander's पूर्णांकerrupt gpio line now to prevent
	 * the kernel from करोing a WARN in gpiolib:gpio_ensure_requested().
	 */
	अगर (gpio_request_one(EP93XX_GPIO_LINE_F(7), GPIOF_सूची_IN,
				"pca9539:74"))
		pr_warn("cannot request interrupt gpio for pca9539:74\n");

	vision_i2c_info[1].irq = gpio_to_irq(EP93XX_GPIO_LINE_F(7));

	ep93xx_रेजिस्टर_i2c(vision_i2c_info,
				ARRAY_SIZE(vision_i2c_info));
	gpiod_add_lookup_table(&vision_spi_mmc_gpio_table);
	gpiod_add_lookup_table(&vision_spi_cs_gpio_table);
	ep93xx_रेजिस्टर_spi(&vision_spi_master, vision_spi_board_info,
				ARRAY_SIZE(vision_spi_board_info));
	vision_रेजिस्टर_i2s();
पूर्ण

MACHINE_START(VISION_EP9307, "Vision Engraving Systems EP9307")
	/* Maपूर्णांकainer: H Hartley Sweeten <hsweeten@visionengravers.com> */
	.atag_offset	= 0x100,
	.map_io		= vision_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= vision_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
