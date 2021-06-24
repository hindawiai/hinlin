<शैली गुरु>
/*
 * StrongARM 1100 LCD Controller Frame Buffer Device
 *
 * Copyright (C) 1999 Eric A. Thomas
 *  Based on acornfb.c Copyright (C) Russell King.
 *  
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित _VIDEO_SA1100FB_H
#घोषणा _VIDEO_SA1100FB_H

#समावेश <linux/fb.h>
#समावेश <linux/types.h>

#घोषणा RGB_4	0
#घोषणा RGB_8	1
#घोषणा RGB_16	2
#घोषणा NR_RGB	3

/* These are the bitfields क्रम each display depth that we support. */
काष्ठा sa1100fb_rgb अणु
	काष्ठा fb_bitfield	red;
	काष्ठा fb_bitfield	green;
	काष्ठा fb_bitfield	blue;
	काष्ठा fb_bitfield	transp;
पूर्ण;

/* This काष्ठाure describes the machine which we are running on. */
काष्ठा sa1100fb_mach_info अणु
	u_दीर्घ		pixघड़ी;

	u_लघु		xres;
	u_लघु		yres;

	u_अक्षर		bpp;
	u_अक्षर		hsync_len;
	u_अक्षर		left_margin;
	u_अक्षर		right_margin;

	u_अक्षर		vsync_len;
	u_अक्षर		upper_margin;
	u_अक्षर		lower_margin;
	u_अक्षर		sync;

	u_पूर्णांक		cmap_greyscale:1,
			cmap_inverse:1,
			cmap_अटल:1,
			unused:29;

	u_पूर्णांक		lccr0;
	u_पूर्णांक		lccr3;

	/* Overrides क्रम the शेष RGB maps */
	स्थिर काष्ठा sa1100fb_rgb *rgb[NR_RGB];

	व्योम (*backlight_घातer)(पूर्णांक);
	व्योम (*lcd_घातer)(पूर्णांक);
	व्योम (*set_visual)(u32);
पूर्ण;

#पूर्ण_अगर
