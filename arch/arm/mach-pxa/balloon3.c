<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/balloon3.c
 *
 *  Support क्रम Balloonboard.org Balloon3 board.
 *
 *  Author:	Nick Bane, Wookey, Jonathan McDowell
 *  Created:	June, 2006
 *  Copyright:	Toby Churchill Ltd
 *  Derived from मुख्यstone.c, by Nico Pitre
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/ucb1400.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_data/pcf857x.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/mtd/platnand.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/regulator/max1586.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "pxa27x.h"
#समावेश <mach/balloon3.h>
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "udc.h"
#समावेश "pxa27x-udc.h"
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ balloon3_pin_config[] __initdata = अणु
	/* Select BTUART 'COM1/ttyS0' as IO option क्रम pins 42/43/44/45 */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	/* Reset, configured as GPIO wakeup source */
	GPIO1_GPIO | WAKEUP_ON_EDGE_BOTH,
पूर्ण;

/******************************************************************************
 * Compatibility: Parameter parsing
 ******************************************************************************/
अटल अचिन्हित दीर्घ balloon3_irq_enabled;

अटल अचिन्हित दीर्घ balloon3_features_present =
		(1 << BALLOON3_FEATURE_OHCI) | (1 << BALLOON3_FEATURE_CF) |
		(1 << BALLOON3_FEATURE_AUDIO) |
		(1 << BALLOON3_FEATURE_TOPPOLY);

पूर्णांक balloon3_has(क्रमागत balloon3_features feature)
अणु
	वापस (balloon3_features_present & (1 << feature)) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(balloon3_has);

पूर्णांक __init parse_balloon3_features(अक्षर *arg)
अणु
	अगर (!arg)
		वापस 0;

	वापस kम_से_अदीर्घ(arg, 0, &balloon3_features_present);
पूर्ण
early_param("balloon3_features", parse_balloon3_features);

/******************************************************************************
 * Compact Flash slot
 ******************************************************************************/
#अगर	defined(CONFIG_PCMCIA_PXA2XX) || defined(CONFIG_PCMCIA_PXA2XX_MODULE)
अटल अचिन्हित दीर्घ balloon3_cf_pin_config[] __initdata = अणु
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO79_PSKTSEL,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
पूर्ण;

अटल व्योम __init balloon3_cf_init(व्योम)
अणु
	अगर (!balloon3_has(BALLOON3_FEATURE_CF))
		वापस;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(balloon3_cf_pin_config));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_cf_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा mtd_partition balloon3_nor_partitions[] = अणु
	अणु
		.name		= "Flash",
		.offset		= 0x00000000,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data balloon3_flash_data[] = अणु
	अणु
		.width		= 2,	/* bankwidth in bytes */
		.parts		= balloon3_nor_partitions,
		.nr_parts	= ARRAY_SIZE(balloon3_nor_partitions)
	पूर्ण
पूर्ण;

अटल काष्ठा resource balloon3_flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_64M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device balloon3_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.resource	= &balloon3_flash_resource,
	.num_resources	= 1,
	.dev 		= अणु
		.platक्रमm_data = balloon3_flash_data,
	पूर्ण,
पूर्ण;
अटल व्योम __init balloon3_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&balloon3_flash);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Audio and Touchscreen
 ******************************************************************************/
#अगर	defined(CONFIG_TOUCHSCREEN_UCB1400) || \
	defined(CONFIG_TOUCHSCREEN_UCB1400_MODULE)
अटल अचिन्हित दीर्घ balloon3_ac97_pin_config[] __initdata = अणु
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO113_AC97_nRESET,
	GPIO95_GPIO,
पूर्ण;

अटल काष्ठा ucb1400_pdata vpac270_ucb1400_pdata = अणु
	.irq		= PXA_GPIO_TO_IRQ(BALLOON3_GPIO_CODEC_IRQ),
पूर्ण;


अटल काष्ठा platक्रमm_device balloon3_ucb1400_device = अणु
	.name		= "ucb1400_core",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &vpac270_ucb1400_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम __init balloon3_ts_init(व्योम)
अणु
	अगर (!balloon3_has(BALLOON3_FEATURE_AUDIO))
		वापस;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(balloon3_ac97_pin_config));
	pxa_set_ac97_info(शून्य);
	platक्रमm_device_रेजिस्टर(&balloon3_ucb1400_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_ts_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल अचिन्हित दीर्घ balloon3_lcd_pin_config[] __initdata = अणु
	GPIOxx_LCD_TFT_16BPP,
	GPIO99_GPIO,
पूर्ण;

अटल काष्ठा pxafb_mode_info balloon3_lcd_modes[] = अणु
	अणु
		.pixघड़ी		= 38000,
		.xres			= 480,
		.yres			= 640,
		.bpp			= 16,
		.hsync_len		= 8,
		.left_margin		= 8,
		.right_margin		= 8,
		.vsync_len		= 2,
		.upper_margin		= 4,
		.lower_margin		= 5,
		.sync			= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info balloon3_lcd_screen = अणु
	.modes			= balloon3_lcd_modes,
	.num_modes		= ARRAY_SIZE(balloon3_lcd_modes),
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल व्योम balloon3_backlight_घातer(पूर्णांक on)
अणु
	gpio_set_value(BALLOON3_GPIO_RUN_BACKLIGHT, on);
पूर्ण

अटल व्योम __init balloon3_lcd_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!balloon3_has(BALLOON3_FEATURE_TOPPOLY))
		वापस;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(balloon3_lcd_pin_config));

	ret = gpio_request(BALLOON3_GPIO_RUN_BACKLIGHT, "BKL-ON");
	अगर (ret) अणु
		pr_err("Requesting BKL-ON GPIO failed!\n");
		जाओ err;
	पूर्ण

	ret = gpio_direction_output(BALLOON3_GPIO_RUN_BACKLIGHT, 1);
	अगर (ret) अणु
		pr_err("Setting BKL-ON GPIO direction failed!\n");
		जाओ err2;
	पूर्ण

	balloon3_lcd_screen.pxafb_backlight_घातer = balloon3_backlight_घातer;
	pxa_set_fb_info(शून्य, &balloon3_lcd_screen);
	वापस;

err2:
	gpio_मुक्त(BALLOON3_GPIO_RUN_BACKLIGHT);
err:
	वापस;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_lcd_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल अचिन्हित दीर्घ balloon3_mmc_pin_config[] __initdata = अणु
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
पूर्ण;

अटल काष्ठा pxamci_platक्रमm_data balloon3_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms	= 200,
पूर्ण;

अटल व्योम __init balloon3_mmc_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(balloon3_mmc_pin_config));
	pxa_set_mci_info(&balloon3_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Gadget
 ******************************************************************************/
#अगर defined(CONFIG_USB_PXA27X)||defined(CONFIG_USB_PXA27X_MODULE)
अटल व्योम balloon3_udc_command(पूर्णांक cmd)
अणु
	अगर (cmd == PXA2XX_UDC_CMD_CONNECT)
		UP2OCR |= UP2OCR_DPPUE | UP2OCR_DPPUBE;
	अन्यथा अगर (cmd == PXA2XX_UDC_CMD_DISCONNECT)
		UP2OCR &= ~UP2OCR_DPPUE;
पूर्ण

अटल पूर्णांक balloon3_udc_is_connected(व्योम)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info balloon3_udc_info __initdata = अणु
	.udc_command		= balloon3_udc_command,
	.udc_is_connected	= balloon3_udc_is_connected,
	.gpio_pullup		= -1,
पूर्ण;

अटल व्योम __init balloon3_udc_init(व्योम)
अणु
	pxa_set_udc_info(&balloon3_udc_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_udc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * IrDA
 ******************************************************************************/
#अगर defined(CONFIG_IRDA) || defined(CONFIG_IRDA_MODULE)
अटल काष्ठा pxaficp_platक्रमm_data balloon3_ficp_platक्रमm_data = अणु
	.transceiver_cap	= IR_FIRMODE | IR_SIRMODE | IR_OFF,
पूर्ण;

अटल व्योम __init balloon3_irda_init(व्योम)
अणु
	pxa_set_ficp_info(&balloon3_ficp_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_irda_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Host
 ******************************************************************************/
#अगर defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
अटल अचिन्हित दीर्घ balloon3_uhc_pin_config[] __initdata = अणु
	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,
पूर्ण;

अटल काष्ठा pxaohci_platक्रमm_data balloon3_ohci_info = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT_ALL | POWER_CONTROL_LOW | POWER_SENSE_LOW,
पूर्ण;

अटल व्योम __init balloon3_uhc_init(व्योम)
अणु
	अगर (!balloon3_has(BALLOON3_FEATURE_OHCI))
		वापस;
	pxa2xx_mfp_config(ARRAY_AND_SIZE(balloon3_uhc_pin_config));
	pxa_set_ohci_info(&balloon3_ohci_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_uhc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LEDs
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
अटल अचिन्हित दीर्घ balloon3_led_pin_config[] __initdata = अणु
	GPIO9_GPIO,	/* न_अंकD activity LED */
	GPIO10_GPIO,	/* Heartbeat LED */
पूर्ण;

काष्ठा gpio_led balloon3_gpio_leds[] = अणु
	अणु
		.name			= "balloon3:green:idle",
		.शेष_trigger	= "heartbeat",
		.gpio			= BALLOON3_GPIO_LED_IDLE,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:green:nand",
		.शेष_trigger	= "nand-disk",
		.gpio			= BALLOON3_GPIO_LED_न_अंकD,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data balloon3_gpio_led_info = अणु
	.leds		= balloon3_gpio_leds,
	.num_leds	= ARRAY_SIZE(balloon3_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device balloon3_leds = अणु
	.name	= "leds-gpio",
	.id	= 0,
	.dev	= अणु
		.platक्रमm_data	= &balloon3_gpio_led_info,
	पूर्ण
पूर्ण;

काष्ठा gpio_led balloon3_pcf_gpio_leds[] = अणु
	अणु
		.name			= "balloon3:green:led0",
		.gpio			= BALLOON3_PCF_GPIO_LED0,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:green:led1",
		.gpio			= BALLOON3_PCF_GPIO_LED1,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:orange:led2",
		.gpio			= BALLOON3_PCF_GPIO_LED2,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:orange:led3",
		.gpio			= BALLOON3_PCF_GPIO_LED3,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:orange:led4",
		.gpio			= BALLOON3_PCF_GPIO_LED4,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:orange:led5",
		.gpio			= BALLOON3_PCF_GPIO_LED5,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:red:led6",
		.gpio			= BALLOON3_PCF_GPIO_LED6,
		.active_low		= 1,
	पूर्ण, अणु
		.name			= "balloon3:red:led7",
		.gpio			= BALLOON3_PCF_GPIO_LED7,
		.active_low		= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data balloon3_pcf_gpio_led_info = अणु
	.leds		= balloon3_pcf_gpio_leds,
	.num_leds	= ARRAY_SIZE(balloon3_pcf_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device balloon3_pcf_leds = अणु
	.name	= "leds-gpio",
	.id	= 1,
	.dev	= अणु
		.platक्रमm_data	= &balloon3_pcf_gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init balloon3_leds_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(balloon3_led_pin_config));
	platक्रमm_device_रेजिस्टर(&balloon3_leds);
	platक्रमm_device_रेजिस्टर(&balloon3_pcf_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_leds_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * FPGA IRQ
 ******************************************************************************/
अटल व्योम balloon3_mask_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक balloon3_irq = (d->irq - BALLOON3_IRQ(0));
	balloon3_irq_enabled &= ~(1 << balloon3_irq);
	__raw_ग_लिखोl(~balloon3_irq_enabled, BALLOON3_INT_CONTROL_REG);
पूर्ण

अटल व्योम balloon3_unmask_irq(काष्ठा irq_data *d)
अणु
	पूर्णांक balloon3_irq = (d->irq - BALLOON3_IRQ(0));
	balloon3_irq_enabled |= (1 << balloon3_irq);
	__raw_ग_लिखोl(~balloon3_irq_enabled, BALLOON3_INT_CONTROL_REG);
पूर्ण

अटल काष्ठा irq_chip balloon3_irq_chip = अणु
	.name		= "FPGA",
	.irq_ack	= balloon3_mask_irq,
	.irq_mask	= balloon3_mask_irq,
	.irq_unmask	= balloon3_unmask_irq,
पूर्ण;

अटल व्योम balloon3_irq_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित दीर्घ pending = __raw_पढ़ोl(BALLOON3_INT_CONTROL_REG) &
					balloon3_irq_enabled;
	करो अणु
		काष्ठा irq_data *d = irq_desc_get_irq_data(desc);
		काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
		अचिन्हित पूर्णांक irq;

		/* clear useless edge notअगरication */
		अगर (chip->irq_ack)
			chip->irq_ack(d);

		जबतक (pending) अणु
			irq = BALLOON3_IRQ(0) + __ffs(pending);
			generic_handle_irq(irq);
			pending &= pending - 1;
		पूर्ण
		pending = __raw_पढ़ोl(BALLOON3_INT_CONTROL_REG) &
				balloon3_irq_enabled;
	पूर्ण जबतक (pending);
पूर्ण

अटल व्योम __init balloon3_init_irq(व्योम)
अणु
	पूर्णांक irq;

	pxa27x_init_irq();
	/* setup extra Balloon3 irqs */
	क्रम (irq = BALLOON3_IRQ(0); irq <= BALLOON3_IRQ(7); irq++) अणु
		irq_set_chip_and_handler(irq, &balloon3_irq_chip,
					 handle_level_irq);
		irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	irq_set_chained_handler(BALLOON3_AUX_NIRQ, balloon3_irq_handler);
	irq_set_irq_type(BALLOON3_AUX_NIRQ, IRQ_TYPE_EDGE_FALLING);

	pr_debug("%s: chained handler installed - irq %d automatically "
		"enabled\n", __func__, BALLOON3_AUX_NIRQ);
पूर्ण

/******************************************************************************
 * GPIO expander
 ******************************************************************************/
#अगर defined(CONFIG_GPIO_PCF857X) || defined(CONFIG_GPIO_PCF857X_MODULE)
अटल काष्ठा pcf857x_platक्रमm_data balloon3_pcf857x_pdata = अणु
	.gpio_base	= BALLOON3_PCF_GPIO_BASE,
	.n_latch	= 0,
	.setup		= शून्य,
	.tearकरोwn	= शून्य,
	.context	= शून्य,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata balloon3_i2c_devs[] = अणु
	अणु
		I2C_BOARD_INFO("pcf8574a", 0x38),
		.platक्रमm_data	= &balloon3_pcf857x_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम __init balloon3_i2c_init(व्योम)
अणु
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(balloon3_i2c_devs));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_i2c_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * न_अंकD
 ******************************************************************************/
#अगर defined(CONFIG_MTD_न_अंकD_PLATFORM)||defined(CONFIG_MTD_न_अंकD_PLATFORM_MODULE)
अटल व्योम balloon3_nand_cmd_ctl(काष्ठा nand_chip *this, पूर्णांक cmd,
				  अचिन्हित पूर्णांक ctrl)
अणु
	uपूर्णांक8_t balloon3_ctl_set = 0, balloon3_ctl_clr = 0;

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		अगर (ctrl & न_अंकD_CLE)
			balloon3_ctl_set |= BALLOON3_न_अंकD_CONTROL_FLCLE;
		अन्यथा
			balloon3_ctl_clr |= BALLOON3_न_अंकD_CONTROL_FLCLE;

		अगर (ctrl & न_अंकD_ALE)
			balloon3_ctl_set |= BALLOON3_न_अंकD_CONTROL_FLALE;
		अन्यथा
			balloon3_ctl_clr |= BALLOON3_न_अंकD_CONTROL_FLALE;

		अगर (balloon3_ctl_clr)
			__raw_ग_लिखोl(balloon3_ctl_clr,
				BALLOON3_न_अंकD_CONTROL_REG);
		अगर (balloon3_ctl_set)
			__raw_ग_लिखोl(balloon3_ctl_set,
				BALLOON3_न_अंकD_CONTROL_REG +
				BALLOON3_FPGA_SETnCLR);
	पूर्ण

	अगर (cmd != न_अंकD_CMD_NONE)
		ग_लिखोb(cmd, this->legacy.IO_ADDR_W);
पूर्ण

अटल व्योम balloon3_nand_select_chip(काष्ठा nand_chip *this, पूर्णांक chip)
अणु
	अगर (chip < 0 || chip > 3)
		वापस;

	/* Assert all nCE lines */
	__raw_ग_लिखोw(
		BALLOON3_न_अंकD_CONTROL_FLCE0 | BALLOON3_न_अंकD_CONTROL_FLCE1 |
		BALLOON3_न_अंकD_CONTROL_FLCE2 | BALLOON3_न_अंकD_CONTROL_FLCE3,
		BALLOON3_न_अंकD_CONTROL_REG + BALLOON3_FPGA_SETnCLR);

	/* Deनिश्चित correct nCE line */
	__raw_ग_लिखोw(BALLOON3_न_अंकD_CONTROL_FLCE0 << chip,
		BALLOON3_न_अंकD_CONTROL_REG);
पूर्ण

अटल पूर्णांक balloon3_nand_dev_पढ़ोy(काष्ठा nand_chip *this)
अणु
	वापस __raw_पढ़ोl(BALLOON3_न_अंकD_STAT_REG) & BALLOON3_न_अंकD_STAT_RNB;
पूर्ण

अटल पूर्णांक balloon3_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	uपूर्णांक16_t ver;
	पूर्णांक ret;

	__raw_ग_लिखोw(BALLOON3_न_अंकD_CONTROL2_16BIT,
		BALLOON3_न_अंकD_CONTROL2_REG + BALLOON3_FPGA_SETnCLR);

	ver = __raw_पढ़ोw(BALLOON3_FPGA_VER);
	अगर (ver < 0x4f08)
		pr_warn("The FPGA code, version 0x%04x, is too old. "
			"NAND support might be broken in this version!", ver);

	/* Power up the न_अंकD chips */
	ret = gpio_request(BALLOON3_GPIO_RUN_न_अंकD, "NAND");
	अगर (ret)
		जाओ err1;

	ret = gpio_direction_output(BALLOON3_GPIO_RUN_न_अंकD, 1);
	अगर (ret)
		जाओ err2;

	gpio_set_value(BALLOON3_GPIO_RUN_न_अंकD, 1);

	/* Deनिश्चित all nCE lines and ग_लिखो protect line */
	__raw_ग_लिखोl(
		BALLOON3_न_अंकD_CONTROL_FLCE0 | BALLOON3_न_अंकD_CONTROL_FLCE1 |
		BALLOON3_न_अंकD_CONTROL_FLCE2 | BALLOON3_न_अंकD_CONTROL_FLCE3 |
		BALLOON3_न_अंकD_CONTROL_FLWP,
		BALLOON3_न_अंकD_CONTROL_REG + BALLOON3_FPGA_SETnCLR);
	वापस 0;

err2:
	gpio_मुक्त(BALLOON3_GPIO_RUN_न_अंकD);
err1:
	वापस ret;
पूर्ण

अटल व्योम balloon3_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* Power करोwn the न_अंकD chips */
	gpio_set_value(BALLOON3_GPIO_RUN_न_अंकD, 0);
	gpio_मुक्त(BALLOON3_GPIO_RUN_न_अंकD);
पूर्ण

अटल काष्ठा mtd_partition balloon3_partition_info[] = अणु
	[0] = अणु
		.name	= "Boot",
		.offset	= 0,
		.size	= SZ_4M,
	पूर्ण,
	[1] = अणु
		.name	= "RootFS",
		.offset	= MTDPART_OFS_APPEND,
		.size	= MTDPART_SIZ_FULL
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_nand_data balloon3_nand_pdata = अणु
	.chip = अणु
		.nr_chips	= 4,
		.chip_offset	= 0,
		.nr_partitions	= ARRAY_SIZE(balloon3_partition_info),
		.partitions	= balloon3_partition_info,
		.chip_delay	= 50,
	पूर्ण,
	.ctrl = अणु
		.dev_पढ़ोy	= balloon3_nand_dev_पढ़ोy,
		.select_chip	= balloon3_nand_select_chip,
		.cmd_ctrl	= balloon3_nand_cmd_ctl,
		.probe		= balloon3_nand_probe,
		.हटाओ		= balloon3_nand_हटाओ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource balloon3_nand_resource[] = अणु
	[0] = अणु
		.start = BALLOON3_न_अंकD_BASE,
		.end   = BALLOON3_न_अंकD_BASE + 0x4,
		.flags = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device balloon3_nand = अणु
	.name		= "gen_nand",
	.num_resources	= ARRAY_SIZE(balloon3_nand_resource),
	.resource	= balloon3_nand_resource,
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &balloon3_nand_pdata,
	पूर्ण
पूर्ण;

अटल व्योम __init balloon3_nand_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&balloon3_nand);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_nand_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Core घातer regulator
 ******************************************************************************/
#अगर defined(CONFIG_REGULATOR_MAX1586) || \
    defined(CONFIG_REGULATOR_MAX1586_MODULE)
अटल काष्ठा regulator_consumer_supply balloon3_max1587a_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data balloon3_max1587a_v3_info = अणु
	.स्थिरraपूर्णांकs = अणु
		.name		= "vcc_core range",
		.min_uV		= 900000,
		.max_uV		= 1705000,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.consumer_supplies	= balloon3_max1587a_consumers,
	.num_consumer_supplies	= ARRAY_SIZE(balloon3_max1587a_consumers),
पूर्ण;

अटल काष्ठा max1586_subdev_data balloon3_max1587a_subdevs[] = अणु
	अणु
		.name		= "vcc_core",
		.id		= MAX1586_V3,
		.platक्रमm_data	= &balloon3_max1587a_v3_info,
	पूर्ण
पूर्ण;

अटल काष्ठा max1586_platक्रमm_data balloon3_max1587a_info = अणु
	.subdevs     = balloon3_max1587a_subdevs,
	.num_subdevs = ARRAY_SIZE(balloon3_max1587a_subdevs),
	.v3_gain     = MAX1586_GAIN_R24_3k32, /* 730..1550 mV */
पूर्ण;

अटल काष्ठा i2c_board_info __initdata balloon3_pi2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("max1586", 0x14),
		.platक्रमm_data	= &balloon3_max1587a_info,
	पूर्ण,
पूर्ण;

अटल व्योम __init balloon3_pmic_init(व्योम)
अणु
	pxa27x_set_i2c_घातer_info(शून्य);
	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(balloon3_pi2c_board_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम balloon3_pmic_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम __init balloon3_init(व्योम)
अणु
	ARB_CNTRL = ARB_CORE_PARK | 0x234;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(balloon3_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	balloon3_i2c_init();
	balloon3_irda_init();
	balloon3_lcd_init();
	balloon3_leds_init();
	balloon3_mmc_init();
	balloon3_nand_init();
	balloon3_nor_init();
	balloon3_pmic_init();
	balloon3_ts_init();
	balloon3_udc_init();
	balloon3_uhc_init();
	balloon3_cf_init();
पूर्ण

अटल काष्ठा map_desc balloon3_io_desc[] __initdata = अणु
	अणु	/* CPLD/FPGA */
		.भव	= (अचिन्हित दीर्घ)BALLOON3_FPGA_VIRT,
		.pfn		= __phys_to_pfn(BALLOON3_FPGA_PHYS),
		.length		= BALLOON3_FPGA_LENGTH,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल व्योम __init balloon3_map_io(व्योम)
अणु
	pxa27x_map_io();
	iotable_init(balloon3_io_desc, ARRAY_SIZE(balloon3_io_desc));
पूर्ण

MACHINE_START(BALLOON3, "Balloon3")
	/* Maपूर्णांकainer: Nick Bane. */
	.map_io		= balloon3_map_io,
	.nr_irqs	= BALLOON3_NR_IRQS,
	.init_irq	= balloon3_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= balloon3_init,
	.atag_offset	= 0x100,
	.restart	= pxa_restart,
MACHINE_END
