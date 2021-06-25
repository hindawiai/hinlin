<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ep93xx/edb93xx.c
 * Cirrus Logic EDB93xx Development Board support.
 *
 * EDB93XX, EDB9301, EDB9307A
 * Copyright (C) 2008-2009 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * EDB9302
 * Copyright (C) 2006 George Kashperko <george@chas.com.ua>
 *
 * EDB9302A, EDB9315, EDB9315A
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 *
 * EDB9307
 * Copyright (C) 2007 Herbert Valerio Riedel <hvr@gnu.org>
 *
 * EDB9312
 * Copyright (C) 2006 Infosys Technologies Limited
 *                    Toufeeq Hussain <toufeeq_hussain@infosys.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpio/machine.h>

#समावेश <sound/cs4271.h>

#समावेश "hardware.h"
#समावेश <linux/platक्रमm_data/video-ep93xx.h>
#समावेश <linux/platक्रमm_data/spi-ep93xx.h>
#समावेश "gpio-ep93xx.h"

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "soc.h"

अटल व्योम __init edb93xx_रेजिस्टर_flash(व्योम)
अणु
	अगर (machine_is_edb9307() || machine_is_edb9312() ||
	    machine_is_edb9315()) अणु
		ep93xx_रेजिस्टर_flash(4, EP93XX_CS6_PHYS_BASE, SZ_32M);
	पूर्ण अन्यथा अणु
		ep93xx_रेजिस्टर_flash(2, EP93XX_CS6_PHYS_BASE, SZ_16M);
	पूर्ण
पूर्ण

अटल काष्ठा ep93xx_eth_data __initdata edb93xx_eth_data = अणु
	.phy_id		= 1,
पूर्ण;


/*************************************************************************
 * EDB93xx i2c peripheral handling
 *************************************************************************/

अटल काष्ठा i2c_board_info __initdata edb93xxa_i2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("isl1208", 0x6f),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata edb93xx_i2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("ds1337", 0x68),
	पूर्ण,
पूर्ण;

अटल व्योम __init edb93xx_रेजिस्टर_i2c(व्योम)
अणु
	अगर (machine_is_edb9302a() || machine_is_edb9307a() ||
	    machine_is_edb9315a()) अणु
		ep93xx_रेजिस्टर_i2c(edb93xxa_i2c_board_info,
				    ARRAY_SIZE(edb93xxa_i2c_board_info));
	पूर्ण अन्यथा अगर (machine_is_edb9302() || machine_is_edb9307()
		|| machine_is_edb9312() || machine_is_edb9315()) अणु
		ep93xx_रेजिस्टर_i2c(edb93xx_i2c_board_info,
				    ARRAY_SIZE(edb93xx_i2c_board_info));
	पूर्ण
पूर्ण


/*************************************************************************
 * EDB93xx SPI peripheral handling
 *************************************************************************/
अटल काष्ठा cs4271_platक्रमm_data edb93xx_cs4271_data = अणु
	.gpio_nreset	= -EINVAL,	/* filled in later */
पूर्ण;

अटल काष्ठा spi_board_info edb93xx_spi_board_info[] __initdata = अणु
	अणु
		.modalias		= "cs4271",
		.platक्रमm_data		= &edb93xx_cs4271_data,
		.max_speed_hz		= 6000000,
		.bus_num		= 0,
		.chip_select		= 0,
		.mode			= SPI_MODE_3,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table edb93xx_spi_cs_gpio_table = अणु
	.dev_id = "spi0",
	.table = अणु
		GPIO_LOOKUP("A", 6, "cs", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ep93xx_spi_info edb93xx_spi_info __initdata = अणु
	/* Intentionally left blank */
पूर्ण;

अटल व्योम __init edb93xx_रेजिस्टर_spi(व्योम)
अणु
	अगर (machine_is_edb9301() || machine_is_edb9302())
		edb93xx_cs4271_data.gpio_nreset = EP93XX_GPIO_LINE_EGPIO1;
	अन्यथा अगर (machine_is_edb9302a() || machine_is_edb9307a())
		edb93xx_cs4271_data.gpio_nreset = EP93XX_GPIO_LINE_H(2);
	अन्यथा अगर (machine_is_edb9315a())
		edb93xx_cs4271_data.gpio_nreset = EP93XX_GPIO_LINE_EGPIO14;

	gpiod_add_lookup_table(&edb93xx_spi_cs_gpio_table);
	ep93xx_रेजिस्टर_spi(&edb93xx_spi_info, edb93xx_spi_board_info,
			    ARRAY_SIZE(edb93xx_spi_board_info));
पूर्ण


/*************************************************************************
 * EDB93xx I2S
 *************************************************************************/
अटल काष्ठा platक्रमm_device edb93xx_audio_device = अणु
	.name		= "edb93xx-audio",
	.id		= -1,
पूर्ण;

अटल पूर्णांक __init edb93xx_has_audio(व्योम)
अणु
	वापस (machine_is_edb9301() || machine_is_edb9302() ||
		machine_is_edb9302a() || machine_is_edb9307a() ||
		machine_is_edb9315a());
पूर्ण

अटल व्योम __init edb93xx_रेजिस्टर_i2s(व्योम)
अणु
	अगर (edb93xx_has_audio()) अणु
		ep93xx_रेजिस्टर_i2s();
		platक्रमm_device_रेजिस्टर(&edb93xx_audio_device);
	पूर्ण
पूर्ण


/*************************************************************************
 * EDB93xx pwm
 *************************************************************************/
अटल व्योम __init edb93xx_रेजिस्टर_pwm(व्योम)
अणु
	अगर (machine_is_edb9301() ||
	    machine_is_edb9302() || machine_is_edb9302a()) अणु
		/* EP9301 and EP9302 only have pwm.1 (EGPIO14) */
		ep93xx_रेजिस्टर_pwm(0, 1);
	पूर्ण अन्यथा अगर (machine_is_edb9307() || machine_is_edb9307a()) अणु
		/* EP9307 only has pwm.0 (PWMOUT) */
		ep93xx_रेजिस्टर_pwm(1, 0);
	पूर्ण अन्यथा अणु
		/* EP9312 and EP9315 have both */
		ep93xx_रेजिस्टर_pwm(1, 1);
	पूर्ण
पूर्ण


/*************************************************************************
 * EDB93xx framebuffer
 *************************************************************************/
अटल काष्ठा ep93xxfb_mach_info __initdata edb93xxfb_info = अणु
	.flags		= 0,
पूर्ण;

अटल पूर्णांक __init edb93xx_has_fb(व्योम)
अणु
	/* These platक्रमms have an ep93xx with video capability */
	वापस machine_is_edb9307() || machine_is_edb9307a() ||
	       machine_is_edb9312() || machine_is_edb9315() ||
	       machine_is_edb9315a();
पूर्ण

अटल व्योम __init edb93xx_रेजिस्टर_fb(व्योम)
अणु
	अगर (!edb93xx_has_fb())
		वापस;

	अगर (machine_is_edb9307a() || machine_is_edb9315a())
		edb93xxfb_info.flags |= EP93XXFB_USE_SDCSN0;
	अन्यथा
		edb93xxfb_info.flags |= EP93XXFB_USE_SDCSN3;

	ep93xx_रेजिस्टर_fb(&edb93xxfb_info);
पूर्ण


/*************************************************************************
 * EDB93xx IDE
 *************************************************************************/
अटल पूर्णांक __init edb93xx_has_ide(व्योम)
अणु
	/*
	 * Although EDB9312 and EDB9315 करो have IDE capability, they have
	 * INTRQ line wired as pull-up, which makes using IDE पूर्णांकerface
	 * problematic.
	 */
	वापस machine_is_edb9312() || machine_is_edb9315() ||
	       machine_is_edb9315a();
पूर्ण

अटल व्योम __init edb93xx_रेजिस्टर_ide(व्योम)
अणु
	अगर (!edb93xx_has_ide())
		वापस;

	ep93xx_रेजिस्टर_ide();
पूर्ण


अटल व्योम __init edb93xx_init_machine(व्योम)
अणु
	ep93xx_init_devices();
	edb93xx_रेजिस्टर_flash();
	ep93xx_रेजिस्टर_eth(&edb93xx_eth_data, 1);
	edb93xx_रेजिस्टर_i2c();
	edb93xx_रेजिस्टर_spi();
	edb93xx_रेजिस्टर_i2s();
	edb93xx_रेजिस्टर_pwm();
	edb93xx_रेजिस्टर_fb();
	edb93xx_रेजिस्टर_ide();
	ep93xx_रेजिस्टर_adc();
पूर्ण


#अगर_घोषित CONFIG_MACH_EDB9301
MACHINE_START(EDB9301, "Cirrus Logic EDB9301 Evaluation Board")
	/* Maपूर्णांकainer: H Hartley Sweeten <hsweeten@visionengravers.com> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_EDB9302
MACHINE_START(EDB9302, "Cirrus Logic EDB9302 Evaluation Board")
	/* Maपूर्णांकainer: George Kashperko <george@chas.com.ua> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_EDB9302A
MACHINE_START(EDB9302A, "Cirrus Logic EDB9302A Evaluation Board")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_EDB9307
MACHINE_START(EDB9307, "Cirrus Logic EDB9307 Evaluation Board")
	/* Maपूर्णांकainer: Herbert Valerio Riedel <hvr@gnu.org> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_EDB9307A
MACHINE_START(EDB9307A, "Cirrus Logic EDB9307A Evaluation Board")
	/* Maपूर्णांकainer: H Hartley Sweeten <hsweeten@visionengravers.com> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_EDB9312
MACHINE_START(EDB9312, "Cirrus Logic EDB9312 Evaluation Board")
	/* Maपूर्णांकainer: Toufeeq Hussain <toufeeq_hussain@infosys.com> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_EDB9315
MACHINE_START(EDB9315, "Cirrus Logic EDB9315 Evaluation Board")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_EDB9315A
MACHINE_START(EDB9315A, "Cirrus Logic EDB9315A Evaluation Board")
	/* Maपूर्णांकainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.init_समय	= ep93xx_समयr_init,
	.init_machine	= edb93xx_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
#पूर्ण_अगर
