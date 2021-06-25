<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2006 Ben Dooks <ben-linux@fluff.org>
 *
 * Copyright (c) 2005 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * iPAQ H1940 series definitions
 */

#अगर_अघोषित __MACH_S3C24XX_H1940_H
#घोषणा __MACH_S3C24XX_H1940_H __खाता__

#घोषणा H1940_SUSPEND_CHECKSUM		(0x30003ff8)
#घोषणा H1940_SUSPEND_RESUMEAT		(0x30081000)
#घोषणा H1940_SUSPEND_CHECK		(0x30080000)

काष्ठा gpio_desc;

बाह्य व्योम h1940_pm_वापस(व्योम);
बाह्य पूर्णांक h1940_led_blink_set(काष्ठा gpio_desc *desc, पूर्णांक state,
			       अचिन्हित दीर्घ *delay_on,
			       अचिन्हित दीर्घ *delay_off);

#समावेश <linux/gpपन.स>

#घोषणा H1940_LATCH_GPIO(x)		(S3C_GPIO_END + (x))

/* SD layer latch */

#घोषणा H1940_LATCH_LCD_P0		H1940_LATCH_GPIO(0)
#घोषणा H1940_LATCH_LCD_P1		H1940_LATCH_GPIO(1)
#घोषणा H1940_LATCH_LCD_P2		H1940_LATCH_GPIO(2)
#घोषणा H1940_LATCH_LCD_P3		H1940_LATCH_GPIO(3)
#घोषणा H1940_LATCH_MAX1698_nSHUTDOWN	H1940_LATCH_GPIO(4)
#घोषणा H1940_LATCH_LED_RED		H1940_LATCH_GPIO(5)
#घोषणा H1940_LATCH_SDQ7		H1940_LATCH_GPIO(6)
#घोषणा H1940_LATCH_USB_DP		H1940_LATCH_GPIO(7)

/* CPU layer latch */

#घोषणा H1940_LATCH_UDA_POWER		H1940_LATCH_GPIO(8)
#घोषणा H1940_LATCH_AUDIO_POWER		H1940_LATCH_GPIO(9)
#घोषणा H1940_LATCH_SM803_ENABLE	H1940_LATCH_GPIO(10)
#घोषणा H1940_LATCH_LCD_P4		H1940_LATCH_GPIO(11)
#घोषणा H1940_LATCH_SD_POWER		H1940_LATCH_GPIO(12)
#घोषणा H1940_LATCH_BLUETOOTH_POWER	H1940_LATCH_GPIO(13)
#घोषणा H1940_LATCH_LED_GREEN		H1940_LATCH_GPIO(14)
#घोषणा H1940_LATCH_LED_FLASH		H1940_LATCH_GPIO(15)

#पूर्ण_अगर /* __MACH_S3C24XX_H1940_H */
