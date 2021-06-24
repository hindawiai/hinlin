<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - FB platक्रमm data definitions
 */

#अगर_अघोषित __PLAT_S3C_FB_H
#घोषणा __PLAT_S3C_FB_H __खाता__

#समावेश <linux/platक्रमm_data/video_s3c.h>

/**
 * s3c_fb_set_platdata() - Setup the FB device with platक्रमm data.
 * @pd: The platक्रमm data to set. The data is copied from the passed काष्ठाure
 *      so the machine data can mark the data __initdata so that any unused
 *      machines will end up dumping their data at runसमय.
 */
बाह्य व्योम s3c_fb_set_platdata(काष्ठा s3c_fb_platdata *pd);

/**
 * s3c64xx_fb_gpio_setup_24bpp() - S3C64XX setup function क्रम 24bpp LCD
 *
 * Initialise the GPIO क्रम an 24bpp LCD display on the RGB पूर्णांकerface.
 */
बाह्य व्योम s3c64xx_fb_gpio_setup_24bpp(व्योम);

#पूर्ण_अगर /* __PLAT_S3C_FB_H */
