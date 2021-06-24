<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम Compaq iPAQ H3100 handheld computer
 *
 * Copyright (c) 2000,1 Compaq Computer Corporation. (Author: Jamey Hicks)
 * Copyright (c) 2009 Dmitry Artamonow <mad_soft@inbox.ru>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gpपन.स>

#समावेश <video/sa1100fb.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <linux/platक्रमm_data/irda-sa11x0.h>

#समावेश <mach/h3xxx.h>
#समावेश <mach/irqs.h>

#समावेश "generic.h"

/*
 * helper क्रम sa1100fb
 */
अटल काष्ठा gpio h3100_lcd_gpio[] = अणु
	अणु H3100_GPIO_LCD_3V_ON, GPIOF_OUT_INIT_LOW, "LCD 3V" पूर्ण,
	अणु H3XXX_EGPIO_LCD_ON, GPIOF_OUT_INIT_LOW, "LCD ON" पूर्ण,
पूर्ण;

अटल bool h3100_lcd_request(व्योम)
अणु
	अटल bool h3100_lcd_ok;
	पूर्णांक rc;

	अगर (h3100_lcd_ok)
		वापस true;

	rc = gpio_request_array(h3100_lcd_gpio, ARRAY_SIZE(h3100_lcd_gpio));
	अगर (rc)
		pr_err("%s: can't request GPIOs\n", __func__);
	अन्यथा
		h3100_lcd_ok = true;

	वापस h3100_lcd_ok;
पूर्ण

अटल व्योम h3100_lcd_घातer(पूर्णांक enable)
अणु
	अगर (!h3100_lcd_request())
		वापस;

	gpio_set_value(H3100_GPIO_LCD_3V_ON, enable);
	gpio_set_value(H3XXX_EGPIO_LCD_ON, enable);
पूर्ण

अटल काष्ठा sa1100fb_mach_info h3100_lcd_info = अणु
	.pixघड़ी	= 406977, 	.bpp		= 4,
	.xres		= 320,		.yres		= 240,

	.hsync_len	= 26,		.vsync_len	= 41,
	.left_margin	= 4,		.upper_margin	= 0,
	.right_margin	= 4,		.lower_margin	= 0,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.cmap_greyscale	= 1,
	.cmap_inverse	= 1,

	.lccr0		= LCCR0_Mono | LCCR0_4PixMono | LCCR0_Sngl | LCCR0_Pas,
	.lccr3		= LCCR3_OutEnH | LCCR3_PixRsEdg | LCCR3_ACBsDiv(2),

	.lcd_घातer = h3100_lcd_घातer,
पूर्ण;

अटल व्योम __init h3100_map_io(व्योम)
अणु
	h3xxx_map_io();

	/* Older bootldrs put GPIO2-9 in alternate mode on the
	   assumption that they are used क्रम video */
	GAFR &= ~0x000001fb;
पूर्ण

/*
 * This turns the IRDA घातer on or off on the Compaq H3100
 */
अटल काष्ठा gpio h3100_irda_gpio[] = अणु
	अणु H3100_GPIO_IR_ON,	GPIOF_OUT_INIT_LOW, "IrDA power" पूर्ण,
	अणु H3100_GPIO_IR_FSEL,	GPIOF_OUT_INIT_LOW, "IrDA fsel" पूर्ण,
पूर्ण;

अटल पूर्णांक h3100_irda_set_घातer(काष्ठा device *dev, अचिन्हित पूर्णांक state)
अणु
	gpio_set_value(H3100_GPIO_IR_ON, state);
	वापस 0;
पूर्ण

अटल व्योम h3100_irda_set_speed(काष्ठा device *dev, अचिन्हित पूर्णांक speed)
अणु
	gpio_set_value(H3100_GPIO_IR_FSEL, !(speed < 4000000));
पूर्ण

अटल पूर्णांक h3100_irda_startup(काष्ठा device *dev)
अणु
	वापस gpio_request_array(h3100_irda_gpio, माप(h3100_irda_gpio));
पूर्ण

अटल व्योम h3100_irda_shutकरोwn(काष्ठा device *dev)
अणु
	वापस gpio_मुक्त_array(h3100_irda_gpio, माप(h3100_irda_gpio));
पूर्ण

अटल काष्ठा irda_platक्रमm_data h3100_irda_data = अणु
	.set_घातer	= h3100_irda_set_घातer,
	.set_speed	= h3100_irda_set_speed,
	.startup	= h3100_irda_startup,
	.shutकरोwn	= h3100_irda_shutकरोwn,
पूर्ण;

अटल व्योम __init h3100_mach_init(व्योम)
अणु
	h3xxx_mach_init();

	sa11x0_रेजिस्टर_pcmcia(-1, शून्य);
	sa11x0_रेजिस्टर_lcd(&h3100_lcd_info);
	sa11x0_रेजिस्टर_irda(&h3100_irda_data);
पूर्ण

MACHINE_START(H3100, "Compaq iPAQ H3100")
	.atag_offset	= 0x100,
	.map_io		= h3100_map_io,
	.nr_irqs	= SA1100_NR_IRQS,
	.init_irq	= sa1100_init_irq,
	.init_समय	= sa1100_समयr_init,
	.init_machine	= h3100_mach_init,
	.init_late	= sa11x0_init_late,
	.restart	= sa11x0_restart,
MACHINE_END

