<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Hardware specअगरic definitions क्रम SL-C7xx series of PDAs
 *
 * Copyright (c) 2004-2005 Riअक्षरd Purdie
 *
 * Based on Sharp's 2.4 kernel patches
 */
#अगर_अघोषित __ASM_ARCH_CORGI_H
#घोषणा __ASM_ARCH_CORGI_H  1

#समावेश "irqs.h" /* PXA_NR_BUILTIN_GPIO */

/*
 * Corgi (Non Standard) GPIO Definitions
 */
#घोषणा CORGI_GPIO_KEY_INT			(0)	/* Keyboard Interrupt */
#घोषणा CORGI_GPIO_AC_IN			(1) /* Charger Detection */
#घोषणा CORGI_GPIO_WAKEUP			(3) /* System wakeup notअगरication? */
#घोषणा CORGI_GPIO_AK_INT			(4)	/* Headphone Jack Control Interrupt */
#घोषणा CORGI_GPIO_TP_INT			(5)	/* Touch Panel Interrupt */
#घोषणा CORGI_GPIO_nSD_WP			(7) /* SD Write Protect? */
#घोषणा CORGI_GPIO_nSD_DETECT		(9) /* MMC/SD Card Detect */
#घोषणा CORGI_GPIO_nSD_INT			(10) /* SD Interrupt क्रम SDIO? */
#घोषणा CORGI_GPIO_MAIN_BAT_LOW		(11) /* Main Battery Low Notअगरication */
#घोषणा CORGI_GPIO_BAT_COVER		(11) /* Battery Cover Detect */
#घोषणा CORGI_GPIO_LED_ORANGE		(13) /* Orange LED Control */
#घोषणा CORGI_GPIO_CF_CD			(14) /* Compact Flash Card Detect */
#घोषणा CORGI_GPIO_CHRG_FULL		(16) /* Charging Complete Notअगरication */
#घोषणा CORGI_GPIO_CF_IRQ			(17) /* Compact Flash Interrupt */
#घोषणा CORGI_GPIO_LCDCON_CS		(19) /* LCD Control Chip Select */
#घोषणा CORGI_GPIO_MAX1111_CS		(20) /* MAX1111 Chip Select */
#घोषणा CORGI_GPIO_ADC_TEMP_ON		(21) /* Select battery voltage or temperature */
#घोषणा CORGI_GPIO_IR_ON			(22) /* Enable IR Transceiver */
#घोषणा CORGI_GPIO_ADS7846_CS		(24) /* ADS7846 Chip Select */
#घोषणा CORGI_GPIO_SD_PWR			(33) /* MMC/SD Power */
#घोषणा CORGI_GPIO_CHRG_ON			(38) /* Enable battery Charging */
#घोषणा CORGI_GPIO_DISCHARGE_ON		(42) /* Enable battery Disअक्षरge */
#घोषणा CORGI_GPIO_CHRG_UKN			(43) /* Unknown Charging (Bypass Control?) */
#घोषणा CORGI_GPIO_HSYNC			(44) /* LCD HSync Pulse */
#घोषणा CORGI_GPIO_USB_PULLUP		(45) /* USB show presence to host */


/*
 * Corgi Keyboard Definitions
 */
#घोषणा CORGI_KEY_STROBE_NUM		(12)
#घोषणा CORGI_KEY_SENSE_NUM			(8)
#घोषणा CORGI_GPIO_ALL_STROBE_BIT	(0x00003ffc)
#घोषणा CORGI_GPIO_HIGH_SENSE_BIT	(0xfc000000)
#घोषणा CORGI_GPIO_HIGH_SENSE_RSHIFT	(26)
#घोषणा CORGI_GPIO_LOW_SENSE_BIT	(0x00000003)
#घोषणा CORGI_GPIO_LOW_SENSE_LSHIFT	(6)
#घोषणा CORGI_GPIO_STROBE_BIT(a)	GPIO_bit(66+(a))
#घोषणा CORGI_GPIO_SENSE_BIT(a)		GPIO_bit(58+(a))
#घोषणा CORGI_GAFR_ALL_STROBE_BIT	(0x0ffffff0)
#घोषणा CORGI_GAFR_HIGH_SENSE_BIT	(0xfff00000)
#घोषणा CORGI_GAFR_LOW_SENSE_BIT	(0x0000000f)
#घोषणा CORGI_GPIO_KEY_SENSE(a)		(58+(a))
#घोषणा CORGI_GPIO_KEY_STROBE(a)	(66+(a))


/*
 * Corgi Interrupts
 */
#घोषणा CORGI_IRQ_GPIO_KEY_INT		PXA_GPIO_TO_IRQ(0)
#घोषणा CORGI_IRQ_GPIO_AC_IN		PXA_GPIO_TO_IRQ(1)
#घोषणा CORGI_IRQ_GPIO_WAKEUP		PXA_GPIO_TO_IRQ(3)
#घोषणा CORGI_IRQ_GPIO_AK_INT		PXA_GPIO_TO_IRQ(4)
#घोषणा CORGI_IRQ_GPIO_TP_INT		PXA_GPIO_TO_IRQ(5)
#घोषणा CORGI_IRQ_GPIO_nSD_DETECT	PXA_GPIO_TO_IRQ(9)
#घोषणा CORGI_IRQ_GPIO_nSD_INT		PXA_GPIO_TO_IRQ(10)
#घोषणा CORGI_IRQ_GPIO_MAIN_BAT_LOW	PXA_GPIO_TO_IRQ(11)
#घोषणा CORGI_IRQ_GPIO_CF_CD		PXA_GPIO_TO_IRQ(14)
#घोषणा CORGI_IRQ_GPIO_CHRG_FULL	PXA_GPIO_TO_IRQ(16)	/* Battery fully अक्षरged */
#घोषणा CORGI_IRQ_GPIO_CF_IRQ		PXA_GPIO_TO_IRQ(17)
#घोषणा CORGI_IRQ_GPIO_KEY_SENSE(a)	PXA_GPIO_TO_IRQ(58+(a))	/* Keyboard Sense lines */


/*
 * Corgi SCOOP GPIOs and Config
 */
#घोषणा CORGI_SCP_LED_GREEN		SCOOP_GPCR_PA11
#घोषणा CORGI_SCP_SWA			SCOOP_GPCR_PA12  /* Hinge Switch A */
#घोषणा CORGI_SCP_SWB			SCOOP_GPCR_PA13  /* Hinge Switch B */
#घोषणा CORGI_SCP_MUTE_L		SCOOP_GPCR_PA14
#घोषणा CORGI_SCP_MUTE_R		SCOOP_GPCR_PA15
#घोषणा CORGI_SCP_AKIN_PULLUP	SCOOP_GPCR_PA16
#घोषणा CORGI_SCP_APM_ON		SCOOP_GPCR_PA17
#घोषणा CORGI_SCP_BACKLIGHT_CONT	SCOOP_GPCR_PA18
#घोषणा CORGI_SCP_MIC_BIAS		SCOOP_GPCR_PA19

#घोषणा CORGI_SCOOP_IO_सूची	( CORGI_SCP_LED_GREEN | CORGI_SCP_MUTE_L | CORGI_SCP_MUTE_R | \
			CORGI_SCP_AKIN_PULLUP | CORGI_SCP_APM_ON | CORGI_SCP_BACKLIGHT_CONT | \
			CORGI_SCP_MIC_BIAS )
#घोषणा CORGI_SCOOP_IO_OUT	( CORGI_SCP_MUTE_L | CORGI_SCP_MUTE_R )

#घोषणा CORGI_SCOOP_GPIO_BASE		(PXA_NR_BUILTIN_GPIO)
#घोषणा CORGI_GPIO_LED_GREEN		(CORGI_SCOOP_GPIO_BASE + 0)
#घोषणा CORGI_GPIO_SWA			(CORGI_SCOOP_GPIO_BASE + 1)  /* Hinge Switch A */
#घोषणा CORGI_GPIO_SWB			(CORGI_SCOOP_GPIO_BASE + 2)  /* Hinge Switch B */
#घोषणा CORGI_GPIO_MUTE_L		(CORGI_SCOOP_GPIO_BASE + 3)
#घोषणा CORGI_GPIO_MUTE_R		(CORGI_SCOOP_GPIO_BASE + 4)
#घोषणा CORGI_GPIO_AKIN_PULLUP		(CORGI_SCOOP_GPIO_BASE + 5)
#घोषणा CORGI_GPIO_APM_ON		(CORGI_SCOOP_GPIO_BASE + 6)
#घोषणा CORGI_GPIO_BACKLIGHT_CONT	(CORGI_SCOOP_GPIO_BASE + 7)
#घोषणा CORGI_GPIO_MIC_BIAS		(CORGI_SCOOP_GPIO_BASE + 8)

#पूर्ण_अगर /* __ASM_ARCH_CORGI_H  */

