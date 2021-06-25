<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-sa1100/include/mach/assabet.h
 *
 * Created 2000/06/05 by Nicolas Pitre <nico@fluxnic.net>
 *
 * This file contains the hardware specअगरic definitions क्रम Assabet
 * Only include this file from SA1100-specअगरic files.
 *
 * 2000/05/23 John Dorsey <john+@cs.cmu.edu>
 *      Definitions क्रम Neponset added.
 */
#अगर_अघोषित __ASM_ARCH_ASSABET_H
#घोषणा __ASM_ARCH_ASSABET_H


/* System Configuration Register flags */

#घोषणा ASSABET_SCR_SDRAM_LOW	(1<<2)	/* SDRAM size (low bit) */
#घोषणा ASSABET_SCR_SDRAM_HIGH	(1<<3)	/* SDRAM size (high bit) */
#घोषणा ASSABET_SCR_FLASH_LOW	(1<<4)	/* Flash size (low bit) */
#घोषणा ASSABET_SCR_FLASH_HIGH	(1<<5)	/* Flash size (high bit) */
#घोषणा ASSABET_SCR_GFX		(1<<8)	/* Graphics Accelerator (0 = present) */
#घोषणा ASSABET_SCR_SA1111	(1<<9)	/* Neponset (0 = present) */

#घोषणा ASSABET_SCR_INIT	-1

बाह्य अचिन्हित दीर्घ SCR_value;

#अगर_घोषित CONFIG_ASSABET_NEPONSET
#घोषणा machine_has_neponset()  ((SCR_value & ASSABET_SCR_SA1111) == 0)
#अन्यथा
#घोषणा machine_has_neponset()	(0)
#पूर्ण_अगर

/* Board Control Register */

#घोषणा ASSABET_BCR_BASE  0xf1000000
#घोषणा ASSABET_BCR (*(अस्थिर अचिन्हित पूर्णांक *)(ASSABET_BCR_BASE))

#घोषणा ASSABET_BCR_CF_PWR	(1<<0)	/* Compact Flash Power (1 = 3.3v, 0 = off) */
#घोषणा ASSABET_BCR_CF_RST	(1<<1)	/* Compact Flash Reset (1 = घातer up reset) */
#घोषणा ASSABET_BCR_NGFX_RST	(1<<1)	/* Graphics Accelerator Reset (0 = hold reset) */
#घोषणा ASSABET_BCR_NCODEC_RST	(1<<2)	/* 0 = Holds UCB1300, ADI7171, and UDA1341 in reset */
#घोषणा ASSABET_BCR_IRDA_FSEL	(1<<3)	/* IRDA Frequency select (0 = SIR, 1 = MIR/ FIR) */
#घोषणा ASSABET_BCR_IRDA_MD0	(1<<4)	/* Range/Power select */
#घोषणा ASSABET_BCR_IRDA_MD1	(1<<5)	/* Range/Power select */
#घोषणा ASSABET_BCR_STEREO_LB	(1<<6)	/* Stereo Loopback */
#घोषणा ASSABET_BCR_CF_BUS_OFF	(1<<7)	/* Compact Flash bus (0 = on, 1 = off (भग्न)) */
#घोषणा ASSABET_BCR_AUDIO_ON	(1<<8)	/* Audio घातer on */
#घोषणा ASSABET_BCR_LIGHT_ON	(1<<9)	/* Backlight */
#घोषणा ASSABET_BCR_LCD_12RGB	(1<<10)	/* 0 = 16RGB, 1 = 12RGB */
#घोषणा ASSABET_BCR_LCD_ON	(1<<11)	/* LCD घातer on */
#घोषणा ASSABET_BCR_RS232EN	(1<<12)	/* RS232 transceiver enable */
#घोषणा ASSABET_BCR_LED_RED	(1<<13)	/* D9 (0 = on, 1 = off) */
#घोषणा ASSABET_BCR_LED_GREEN	(1<<14)	/* D8 (0 = on, 1 = off) */
#घोषणा ASSABET_BCR_VIB_ON	(1<<15)	/* Vibration motor (quiet alert) */
#घोषणा ASSABET_BCR_COM_DTR	(1<<16)	/* COMport Data Terminal Ready */
#घोषणा ASSABET_BCR_COM_RTS	(1<<17)	/* COMport Request To Send */
#घोषणा ASSABET_BCR_RAD_WU	(1<<18)	/* Radio wake up पूर्णांकerrupt */
#घोषणा ASSABET_BCR_SMB_EN	(1<<19)	/* System management bus enable */
#घोषणा ASSABET_BCR_TV_IR_DEC	(1<<20)	/* TV IR Decode Enable (not implemented) */
#घोषणा ASSABET_BCR_QMUTE	(1<<21)	/* Quick Mute */
#घोषणा ASSABET_BCR_RAD_ON	(1<<22)	/* Radio Power On */
#घोषणा ASSABET_BCR_SPK_OFF	(1<<23)	/* 1 = Speaker amplअगरier घातer off */

#अगर_घोषित CONFIG_SA1100_ASSABET
बाह्य व्योम ASSABET_BCR_frob(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक set);
#अन्यथा
#घोषणा ASSABET_BCR_frob(x,y)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य व्योम assabet_uda1341_reset(पूर्णांक set);

#घोषणा ASSABET_BCR_set(x)	ASSABET_BCR_frob((x), (x))
#घोषणा ASSABET_BCR_clear(x)	ASSABET_BCR_frob((x), 0)

#घोषणा ASSABET_BSR_BASE	0xf1000000
#घोषणा ASSABET_BSR (*(अस्थिर अचिन्हित पूर्णांक*)(ASSABET_BSR_BASE))

#घोषणा ASSABET_BSR_RS232_VALID	(1 << 24)
#घोषणा ASSABET_BSR_COM_DCD	(1 << 25)
#घोषणा ASSABET_BSR_COM_CTS	(1 << 26)
#घोषणा ASSABET_BSR_COM_DSR	(1 << 27)
#घोषणा ASSABET_BSR_RAD_CTS	(1 << 28)
#घोषणा ASSABET_BSR_RAD_DSR	(1 << 29)
#घोषणा ASSABET_BSR_RAD_DCD	(1 << 30)
#घोषणा ASSABET_BSR_RAD_RI	(1 << 31)


/* GPIOs (biपंचांगasks) क्रम which the generic definition करोesn't say much */
#घोषणा ASSABET_GPIO_RADIO_IRQ		GPIO_GPIO (14)	/* Radio पूर्णांकerrupt request  */
#घोषणा ASSABET_GPIO_PS_MODE_SYNC	GPIO_GPIO (16)	/* Power supply mode/sync   */
#घोषणा ASSABET_GPIO_STEREO_64FS_CLK	GPIO_GPIO (19)	/* SSP UDA1341 घड़ी input  */
#घोषणा ASSABET_GPIO_GFX_IRQ		GPIO_GPIO (24)	/* Graphics IRQ */
#घोषणा ASSABET_GPIO_BATT_LOW		GPIO_GPIO (26)	/* Low battery */
#घोषणा ASSABET_GPIO_RCLK		GPIO_GPIO (26)	/* CCLK/2  */

#पूर्ण_अगर
