<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Toshiba TC6393XB SoC support
 *
 * Copyright(c) 2005-2006 Chris Humbert
 * Copyright(c) 2005 Dirk Opfer
 * Copyright(c) 2005 Ian Molton <spyro@f2s.com>
 * Copyright(c) 2007 Dmitry Baryshkov
 *
 * Based on code written by Sharp/Lineo क्रम 2.4 kernels
 * Based on locomo.c
 */

#अगर_अघोषित MFD_TC6393XB_H
#घोषणा MFD_TC6393XB_H

#समावेश <linux/fb.h>

/* Also one should provide the CK3P6MI घड़ी */
काष्ठा tc6393xb_platक्रमm_data अणु
	u16	scr_pll2cr;	/* PLL2 Control */
	u16	scr_gper;	/* GP Enable */

	पूर्णांक	(*enable)(काष्ठा platक्रमm_device *dev);
	पूर्णांक	(*disable)(काष्ठा platक्रमm_device *dev);
	पूर्णांक	(*suspend)(काष्ठा platक्रमm_device *dev);
	पूर्णांक	(*resume)(काष्ठा platक्रमm_device *dev);

	पूर्णांक	irq_base;	/* base क्रम subdevice irqs */
	पूर्णांक	gpio_base;
	पूर्णांक	(*setup)(काष्ठा platक्रमm_device *dev);
	व्योम	(*tearकरोwn)(काष्ठा platक्रमm_device *dev);

	काष्ठा पंचांगio_nand_data	*nand_data;
	काष्ठा पंचांगio_fb_data	*fb_data;

	अचिन्हित resume_restore : 1; /* make special actions
					to preserve the state
					on suspend/resume */
पूर्ण;

बाह्य पूर्णांक tc6393xb_lcd_mode(काष्ठा platक्रमm_device *fb,
			     स्थिर काष्ठा fb_videomode *mode);
बाह्य पूर्णांक tc6393xb_lcd_set_घातer(काष्ठा platक्रमm_device *fb, bool on);

/*
 * Relative to irq_base
 */
#घोषणा	IRQ_TC6393_न_अंकD		0
#घोषणा	IRQ_TC6393_MMC		1
#घोषणा	IRQ_TC6393_OHCI		2
#घोषणा	IRQ_TC6393_FB		4

#घोषणा	TC6393XB_NR_IRQS	8

#पूर्ण_अगर
