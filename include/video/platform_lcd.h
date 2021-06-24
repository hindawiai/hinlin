<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/video/platक्रमm_lcd.h
 *
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Generic platक्रमm-device LCD घातer control पूर्णांकerface.
*/

काष्ठा plat_lcd_data;
काष्ठा fb_info;

काष्ठा plat_lcd_data अणु
	पूर्णांक	(*probe)(काष्ठा plat_lcd_data *);
	व्योम	(*set_घातer)(काष्ठा plat_lcd_data *, अचिन्हित पूर्णांक घातer);
	पूर्णांक	(*match_fb)(काष्ठा plat_lcd_data *, काष्ठा fb_info *);
पूर्ण;

