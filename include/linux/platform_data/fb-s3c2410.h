<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2004 Arnaud Patard <arnaud.patard@rtp-net.org>
 *
 * Inspired by pxafb.h
*/

#अगर_अघोषित __ASM_PLAT_FB_S3C2410_H
#घोषणा __ASM_PLAT_FB_S3C2410_H __खाता__

#समावेश <linux/compiler_types.h>

काष्ठा s3c2410fb_hw अणु
	अचिन्हित दीर्घ	lcdcon1;
	अचिन्हित दीर्घ	lcdcon2;
	अचिन्हित दीर्घ	lcdcon3;
	अचिन्हित दीर्घ	lcdcon4;
	अचिन्हित दीर्घ	lcdcon5;
पूर्ण;

/* LCD description */
काष्ठा s3c2410fb_display अणु
	/* LCD type */
	अचिन्हित type;
#घोषणा S3C2410_LCDCON1_DSCAN4	   (0<<5)
#घोषणा S3C2410_LCDCON1_STN4	   (1<<5)
#घोषणा S3C2410_LCDCON1_STN8	   (2<<5)
#घोषणा S3C2410_LCDCON1_TFT	   (3<<5)

#घोषणा S3C2410_LCDCON1_TFT1BPP	   (8<<1)
#घोषणा S3C2410_LCDCON1_TFT2BPP	   (9<<1)
#घोषणा S3C2410_LCDCON1_TFT4BPP	   (10<<1)
#घोषणा S3C2410_LCDCON1_TFT8BPP	   (11<<1)
#घोषणा S3C2410_LCDCON1_TFT16BPP   (12<<1)
#घोषणा S3C2410_LCDCON1_TFT24BPP   (13<<1)

	/* Screen size */
	अचिन्हित लघु width;
	अचिन्हित लघु height;

	/* Screen info */
	अचिन्हित लघु xres;
	अचिन्हित लघु yres;
	अचिन्हित लघु bpp;

	अचिन्हित pixघड़ी;		/* pixघड़ी in picoseconds */
	अचिन्हित लघु left_margin;  /* value in pixels (TFT) or HCLKs (STN) */
	अचिन्हित लघु right_margin; /* value in pixels (TFT) or HCLKs (STN) */
	अचिन्हित लघु hsync_len;    /* value in pixels (TFT) or HCLKs (STN) */
	अचिन्हित लघु upper_margin;	/* value in lines (TFT) or 0 (STN) */
	अचिन्हित लघु lower_margin;	/* value in lines (TFT) or 0 (STN) */
	अचिन्हित लघु vsync_len;	/* value in lines (TFT) or 0 (STN) */

	/* lcd configuration रेजिस्टरs */
	अचिन्हित दीर्घ	lcdcon5;
#घोषणा S3C2410_LCDCON5_BPP24BL	    (1<<12)
#घोषणा S3C2410_LCDCON5_FRM565	    (1<<11)
#घोषणा S3C2410_LCDCON5_INVVCLK	    (1<<10)
#घोषणा S3C2410_LCDCON5_INVVLINE    (1<<9)
#घोषणा S3C2410_LCDCON5_INVVFRAME   (1<<8)
#घोषणा S3C2410_LCDCON5_INVVD	    (1<<7)
#घोषणा S3C2410_LCDCON5_INVVDEN	    (1<<6)
#घोषणा S3C2410_LCDCON5_INVPWREN    (1<<5)
#घोषणा S3C2410_LCDCON5_INVLEND	    (1<<4)
#घोषणा S3C2410_LCDCON5_PWREN	    (1<<3)
#घोषणा S3C2410_LCDCON5_ENLEND	    (1<<2)
#घोषणा S3C2410_LCDCON5_BSWP	    (1<<1)
#घोषणा S3C2410_LCDCON5_HWSWP	    (1<<0)
पूर्ण;

काष्ठा s3c2410fb_mach_info अणु

	काष्ठा s3c2410fb_display *displays;	/* attached displays info */
	अचिन्हित num_displays;			/* number of defined displays */
	अचिन्हित शेष_display;

	/* GPIOs */

	अचिन्हित दीर्घ	gpcup;
	अचिन्हित दीर्घ	gpcup_mask;
	अचिन्हित दीर्घ	gpccon;
	अचिन्हित दीर्घ	gpccon_mask;
	अचिन्हित दीर्घ	gpdup;
	अचिन्हित दीर्घ	gpdup_mask;
	अचिन्हित दीर्घ	gpdcon;
	अचिन्हित दीर्घ	gpdcon_mask;

	व्योम __iomem *  gpccon_reg;
	व्योम __iomem *  gpcup_reg;
	व्योम __iomem *  gpdcon_reg;
	व्योम __iomem *  gpdup_reg;

	/* lpc3600 control रेजिस्टर */
	अचिन्हित दीर्घ	lpcsel;
पूर्ण;

बाह्य व्योम s3c24xx_fb_set_platdata(काष्ठा s3c2410fb_mach_info *);

#पूर्ण_अगर /* __ASM_PLAT_FB_S3C2410_H */
