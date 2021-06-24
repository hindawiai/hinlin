<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003 Simtec Electronics <linux@simtec.co.uk>
 *		      http://www.simtec.co.uk/products/SWLINUX/
 */

#अगर_अघोषित ___ASM_ARCH_REGS_LCD_H
#घोषणा ___ASM_ARCH_REGS_LCD_H

/*
 * a couple of values are used as platक्रमm data in
 * include/linux/platक्रमm_data/fb-s3c2410.h and not
 * duplicated here.
 */
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>

#घोषणा S3C2410_LCDREG(x)	(x)

/* LCD control रेजिस्टरs */
#घोषणा S3C2410_LCDCON1	    S3C2410_LCDREG(0x00)
#घोषणा S3C2410_LCDCON2	    S3C2410_LCDREG(0x04)
#घोषणा S3C2410_LCDCON3	    S3C2410_LCDREG(0x08)
#घोषणा S3C2410_LCDCON4	    S3C2410_LCDREG(0x0C)
#घोषणा S3C2410_LCDCON5	    S3C2410_LCDREG(0x10)

#घोषणा S3C2410_LCDCON1_CLKVAL(x)  ((x) << 8)
#घोषणा S3C2410_LCDCON1_MMODE	   (1<<7)
#घोषणा S3C2410_LCDCON1_DSCAN4	   (0<<5)
#घोषणा S3C2410_LCDCON1_STN4	   (1<<5)
#घोषणा S3C2410_LCDCON1_STN8	   (2<<5)
#घोषणा S3C2410_LCDCON1_TFT	   (3<<5)

#घोषणा S3C2410_LCDCON1_STN1BPP	   (0<<1)
#घोषणा S3C2410_LCDCON1_STN2GREY   (1<<1)
#घोषणा S3C2410_LCDCON1_STN4GREY   (2<<1)
#घोषणा S3C2410_LCDCON1_STN8BPP	   (3<<1)
#घोषणा S3C2410_LCDCON1_STN12BPP   (4<<1)

#घोषणा S3C2410_LCDCON1_ENVID	   (1)

#घोषणा S3C2410_LCDCON1_MODEMASK    0x1E

#घोषणा S3C2410_LCDCON2_VBPD(x)	    ((x) << 24)
#घोषणा S3C2410_LCDCON2_LINEVAL(x)  ((x) << 14)
#घोषणा S3C2410_LCDCON2_VFPD(x)	    ((x) << 6)
#घोषणा S3C2410_LCDCON2_VSPW(x)	    ((x) << 0)

#घोषणा S3C2410_LCDCON2_GET_VBPD(x) ( ((x) >> 24) & 0xFF)
#घोषणा S3C2410_LCDCON2_GET_VFPD(x) ( ((x) >>  6) & 0xFF)
#घोषणा S3C2410_LCDCON2_GET_VSPW(x) ( ((x) >>  0) & 0x3F)

#घोषणा S3C2410_LCDCON3_HBPD(x)	    ((x) << 19)
#घोषणा S3C2410_LCDCON3_WDLY(x)	    ((x) << 19)
#घोषणा S3C2410_LCDCON3_HOZVAL(x)   ((x) << 8)
#घोषणा S3C2410_LCDCON3_HFPD(x)	    ((x) << 0)
#घोषणा S3C2410_LCDCON3_LINEBLANK(x)((x) << 0)

#घोषणा S3C2410_LCDCON3_GET_HBPD(x) ( ((x) >> 19) & 0x7F)
#घोषणा S3C2410_LCDCON3_GET_HFPD(x) ( ((x) >>  0) & 0xFF)

/* LDCCON4 changes क्रम STN mode on the S3C2412 */

#घोषणा S3C2410_LCDCON4_MVAL(x)	    ((x) << 8)
#घोषणा S3C2410_LCDCON4_HSPW(x)	    ((x) << 0)
#घोषणा S3C2410_LCDCON4_WLH(x)	    ((x) << 0)

#घोषणा S3C2410_LCDCON4_GET_HSPW(x) ( ((x) >>  0) & 0xFF)

/* framebuffer start addressed */
#घोषणा S3C2410_LCDSADDR1   S3C2410_LCDREG(0x14)
#घोषणा S3C2410_LCDSADDR2   S3C2410_LCDREG(0x18)
#घोषणा S3C2410_LCDSADDR3   S3C2410_LCDREG(0x1C)

#घोषणा S3C2410_LCDBANK(x)	((x) << 21)
#घोषणा S3C2410_LCDBASEU(x)	(x)

#घोषणा S3C2410_OFFSIZE(x)	((x) << 11)
#घोषणा S3C2410_PAGEWIDTH(x)	(x)

/* colour lookup and miscellaneous controls */

#घोषणा S3C2410_REDLUT	   S3C2410_LCDREG(0x20)
#घोषणा S3C2410_GREENLUT   S3C2410_LCDREG(0x24)
#घोषणा S3C2410_BLUELUT	   S3C2410_LCDREG(0x28)

#घोषणा S3C2410_DITHMODE   S3C2410_LCDREG(0x4C)
#घोषणा S3C2410_TPAL	   S3C2410_LCDREG(0x50)

#घोषणा S3C2410_TPAL_EN		(1<<24)

/* पूर्णांकerrupt info */
#घोषणा S3C2410_LCDINTPND  S3C2410_LCDREG(0x54)
#घोषणा S3C2410_LCDSRCPND  S3C2410_LCDREG(0x58)
#घोषणा S3C2410_LCDINTMSK  S3C2410_LCDREG(0x5C)
#घोषणा S3C2410_LCDINT_FIWSEL	(1<<2)
#घोषणा	S3C2410_LCDINT_FRSYNC	(1<<1)
#घोषणा S3C2410_LCDINT_FICNT	(1<<0)

/* s3c2442 extra stn रेजिस्टरs */

#घोषणा S3C2442_REDLUT		S3C2410_LCDREG(0x20)
#घोषणा S3C2442_GREENLUT	S3C2410_LCDREG(0x24)
#घोषणा S3C2442_BLUELUT		S3C2410_LCDREG(0x28)
#घोषणा S3C2442_DITHMODE	S3C2410_LCDREG(0x20)

#घोषणा S3C2410_LPCSEL	   S3C2410_LCDREG(0x60)

#घोषणा S3C2410_TFTPAL(x)  S3C2410_LCDREG((0x400 + (x)*4))

/* S3C2412 रेजिस्टरs */

#घोषणा S3C2412_TPAL		S3C2410_LCDREG(0x20)

#घोषणा S3C2412_LCDINTPND	S3C2410_LCDREG(0x24)
#घोषणा S3C2412_LCDSRCPND	S3C2410_LCDREG(0x28)
#घोषणा S3C2412_LCDINTMSK	S3C2410_LCDREG(0x2C)

#घोषणा S3C2412_TCONSEL		S3C2410_LCDREG(0x30)

#घोषणा S3C2412_LCDCON6		S3C2410_LCDREG(0x34)
#घोषणा S3C2412_LCDCON7		S3C2410_LCDREG(0x38)
#घोषणा S3C2412_LCDCON8		S3C2410_LCDREG(0x3C)
#घोषणा S3C2412_LCDCON9		S3C2410_LCDREG(0x40)

#घोषणा S3C2412_REDLUT(x)	S3C2410_LCDREG(0x44 + ((x)*4))
#घोषणा S3C2412_GREENLUT(x)	S3C2410_LCDREG(0x60 + ((x)*4))
#घोषणा S3C2412_BLUELUT(x)	S3C2410_LCDREG(0x98 + ((x)*4))

#घोषणा S3C2412_FRCPAT(x)	S3C2410_LCDREG(0xB4 + ((x)*4))

/* general रेजिस्टरs */

/* base of the LCD रेजिस्टरs, where INTPND, INTSRC and then INTMSK
 * are available. */

#घोषणा S3C2410_LCDINTBASE	S3C2410_LCDREG(0x54)
#घोषणा S3C2412_LCDINTBASE	S3C2410_LCDREG(0x24)

#घोषणा S3C24XX_LCDINTPND	(0x00)
#घोषणा S3C24XX_LCDSRCPND	(0x04)
#घोषणा S3C24XX_LCDINTMSK	(0x08)

#पूर्ण_अगर /* ___ASM_ARCH_REGS_LCD_H */
