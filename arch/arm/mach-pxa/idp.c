<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/idp.c
 *
 *  Copyright (c) 2001 Clअगरf Brake, Accelent Systems Inc.
 *
 *  2001-09-13: Clअगरf Brake <cbrake@accelent.com>
 *              Initial code
 *
 *  2005-02-15: Clअगरf Brake <clअगरf.brake@gmail.com>
 *  		<http://www.vibren.com> <http://bec-प्रणालीs.com>
 *              Updated क्रम 2.6 kernel
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fb.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa25x.h"
#समावेश "idp.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <mach/bitfield.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/smc91x.h>

#समावेश "generic.h"
#समावेश "devices.h"

/* TODO:
 * - add pxa2xx_audio_ops_t device काष्ठाure
 * - Ethernet पूर्णांकerrupt
 */

अटल अचिन्हित दीर्घ idp_pin_config[] __initdata = अणु
	/* LCD */
	GPIOxx_LCD_DSTN_16BPP,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	/* STUART */
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,

	/* MMC */
	GPIO6_MMC_CLK,
	GPIO8_MMC_CS0,

	/* Ethernet */
	GPIO33_nCS_5,	/* Ethernet CS */
	GPIO4_GPIO,	/* Ethernet IRQ */
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= (IDP_ETH_PHYS + 0x300),
		.end	= (IDP_ETH_PHYS + 0xfffff),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(4),
		.end	= PXA_GPIO_TO_IRQ(4),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा smc91x_platdata smc91x_platdata = अणु
	.flags = SMC91X_USE_8BIT | SMC91X_USE_16BIT | SMC91X_USE_32BIT |
		 SMC91X_USE_DMA | SMC91X_NOWAIT,
	.pxa_u16_align4 = true,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev.platक्रमm_data = &smc91x_platdata,
पूर्ण;

अटल व्योम idp_backlight_घातer(पूर्णांक on)
अणु
	अगर (on) अणु
		IDP_CPLD_LCD |= (1<<1);
	पूर्ण अन्यथा अणु
		IDP_CPLD_LCD &= ~(1<<1);
	पूर्ण
पूर्ण

अटल व्योम idp_vlcd(पूर्णांक on)
अणु
	अगर (on) अणु
		IDP_CPLD_LCD |= (1<<2);
	पूर्ण अन्यथा अणु
		IDP_CPLD_LCD &= ~(1<<2);
	पूर्ण
पूर्ण

अटल व्योम idp_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *var)
अणु
	अगर (on) अणु
		IDP_CPLD_LCD |= (1<<0);
	पूर्ण अन्यथा अणु
		IDP_CPLD_LCD &= ~(1<<0);
	पूर्ण

	/* call idp_vlcd क्रम now as core driver करोes not support
	 * both घातer and vlcd hooks.  Note, this is not technically
	 * the correct sequence, but seems to work.  Disclaimer:
	 * this may eventually damage the display.
	 */

	idp_vlcd(on);
पूर्ण

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
	.modes          = &sharp_lm8v31_mode,
	.num_modes      = 1,
	.cmap_inverse	= 0,
	.cmap_अटल	= 0,
	.lcd_conn	= LCD_COLOR_DSTN_16BPP | LCD_PCLK_EDGE_FALL |
			  LCD_AC_BIAS_FREQ(255),
	.pxafb_backlight_घातer = &idp_backlight_घातer,
	.pxafb_lcd_घातer = &idp_lcd_घातer
पूर्ण;

अटल काष्ठा pxamci_platक्रमm_data idp_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

अटल व्योम __init idp_init(व्योम)
अणु
	prपूर्णांकk("idp_init()\n");

	pxa2xx_mfp_config(ARRAY_AND_SIZE(idp_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	platक्रमm_device_रेजिस्टर(&smc91x_device);
	//platक्रमm_device_रेजिस्टर(&mst_audio_device);
	pxa_set_fb_info(शून्य, &sharp_lm8v31);
	pxa_set_mci_info(&idp_mci_platक्रमm_data);
पूर्ण

अटल काष्ठा map_desc idp_io_desc[] __initdata = अणु
  	अणु
		.भव	=  IDP_COREVOLT_VIRT,
		.pfn		= __phys_to_pfn(IDP_COREVOLT_PHYS),
		.length		= IDP_COREVOLT_SIZE,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	=  IDP_CPLD_VIRT,
		.pfn		= __phys_to_pfn(IDP_CPLD_PHYS),
		.length		= IDP_CPLD_SIZE,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init idp_map_io(व्योम)
अणु
	pxa25x_map_io();
	iotable_init(idp_io_desc, ARRAY_SIZE(idp_io_desc));
पूर्ण

/* LEDs */
#अगर defined(CONFIG_NEW_LEDS) && defined(CONFIG_LEDS_CLASS)
काष्ठा idp_led अणु
	काष्ठा led_classdev     cdev;
	u8                      mask;
पूर्ण;

/*
 * The triggers lines up below will only be used अगर the
 * LED triggers are compiled in.
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *trigger;
पूर्ण idp_leds[] = अणु
	अणु "idp:green", "heartbeat", पूर्ण,
	अणु "idp:red", "cpu0", पूर्ण,
पूर्ण;

अटल व्योम idp_led_set(काष्ठा led_classdev *cdev,
		क्रमागत led_brightness b)
अणु
	काष्ठा idp_led *led = container_of(cdev,
			काष्ठा idp_led, cdev);
	u32 reg = IDP_CPLD_LED_CONTROL;

	अगर (b != LED_OFF)
		reg &= ~led->mask;
	अन्यथा
		reg |= led->mask;

	IDP_CPLD_LED_CONTROL = reg;
पूर्ण

अटल क्रमागत led_brightness idp_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा idp_led *led = container_of(cdev,
			काष्ठा idp_led, cdev);

	वापस (IDP_CPLD_LED_CONTROL & led->mask) ? LED_OFF : LED_FULL;
पूर्ण

अटल पूर्णांक __init idp_leds_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!machine_is_pxa_idp())
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(idp_leds); i++) अणु
		काष्ठा idp_led *led;

		led = kzalloc(माप(*led), GFP_KERNEL);
		अगर (!led)
			अवरोध;

		led->cdev.name = idp_leds[i].name;
		led->cdev.brightness_set = idp_led_set;
		led->cdev.brightness_get = idp_led_get;
		led->cdev.शेष_trigger = idp_leds[i].trigger;

		अगर (i == 0)
			led->mask = IDP_HB_LED;
		अन्यथा
			led->mask = IDP_BUSY_LED;

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
fs_initcall(idp_leds_init);
#पूर्ण_अगर

MACHINE_START(PXA_IDP, "Vibren PXA255 IDP")
	/* Maपूर्णांकainer: Vibren Technologies */
	.map_io		= idp_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= idp_init,
	.restart	= pxa_restart,
MACHINE_END
