<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/यंत्र-arm/arch-pxa/balloon3.h
 *
 *  Authors:	Nick Bane and Wookey
 *  Created:	Oct, 2005
 *  Copyright:	Toby Churchill Ltd
 *  Cribbed from मुख्यstone.c, by Nicholas Pitre
 */

#अगर_अघोषित ASM_ARCH_BALLOON3_H
#घोषणा ASM_ARCH_BALLOON3_H

#समावेश "irqs.h" /* PXA_NR_BUILTIN_GPIO */

क्रमागत balloon3_features अणु
	BALLOON3_FEATURE_OHCI,
	BALLOON3_FEATURE_MMC,
	BALLOON3_FEATURE_CF,
	BALLOON3_FEATURE_AUDIO,
	BALLOON3_FEATURE_TOPPOLY,
पूर्ण;

#घोषणा BALLOON3_FPGA_PHYS	PXA_CS4_PHYS
#घोषणा BALLOON3_FPGA_VIRT	IOMEM(0xf1000000)	/* as per balloon2 */
#घोषणा BALLOON3_FPGA_LENGTH	0x01000000

#घोषणा	BALLOON3_FPGA_SETnCLR		(0x1000)

/* FPGA / CPLD रेजिस्टरs क्रम CF socket */
#घोषणा	BALLOON3_CF_STATUS_REG		(BALLOON3_FPGA_VIRT + 0x00e00008)
#घोषणा	BALLOON3_CF_CONTROL_REG		(BALLOON3_FPGA_VIRT + 0x00e00008)
/* FPGA / CPLD version रेजिस्टर */
#घोषणा	BALLOON3_FPGA_VER		(BALLOON3_FPGA_VIRT + 0x00e0001c)
/* FPGA / CPLD रेजिस्टरs क्रम न_अंकD flash */
#घोषणा	BALLOON3_न_अंकD_BASE		(PXA_CS4_PHYS + 0x00e00000)
#घोषणा	BALLOON3_न_अंकD_IO_REG		(BALLOON3_FPGA_VIRT + 0x00e00000)
#घोषणा	BALLOON3_न_अंकD_CONTROL2_REG	(BALLOON3_FPGA_VIRT + 0x00e00010)
#घोषणा	BALLOON3_न_अंकD_STAT_REG		(BALLOON3_FPGA_VIRT + 0x00e00014)
#घोषणा	BALLOON3_न_अंकD_CONTROL_REG	(BALLOON3_FPGA_VIRT + 0x00e00014)

/* fpga/cpld पूर्णांकerrupt control रेजिस्टर */
#घोषणा BALLOON3_INT_CONTROL_REG	(BALLOON3_FPGA_VIRT + 0x00e0000C)
#घोषणा BALLOON3_VERSION_REG		(BALLOON3_FPGA_VIRT + 0x00e0001c)

#घोषणा BALLOON3_SAMOSA_ADDR_REG	(BALLOON3_FPGA_VIRT + 0x00c00000)
#घोषणा BALLOON3_SAMOSA_DATA_REG	(BALLOON3_FPGA_VIRT + 0x00c00004)
#घोषणा BALLOON3_SAMOSA_STATUS_REG	(BALLOON3_FPGA_VIRT + 0x00c0001c)

/* CF Status Register bits (पढ़ो-only) bits */
#घोषणा BALLOON3_CF_nIRQ		(1 << 0)
#घोषणा BALLOON3_CF_nSTSCHG_BVD1	(1 << 1)

/* CF Control Set Register bits / CF Control Clear Register bits (ग_लिखो-only) */
#घोषणा BALLOON3_CF_RESET		(1 << 0)
#घोषणा BALLOON3_CF_ENABLE		(1 << 1)
#घोषणा BALLOON3_CF_ADD_ENABLE		(1 << 2)

/* CF Interrupt sources */
#घोषणा BALLOON3_BP_CF_NRDY_IRQ		BALLOON3_IRQ(0)
#घोषणा BALLOON3_BP_NSTSCHG_IRQ		BALLOON3_IRQ(1)

/* न_अंकD Control रेजिस्टर */
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLWP	(1 << 7)
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLSE	(1 << 6)
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLCE3	(1 << 5)
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLCE2	(1 << 4)
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLCE1	(1 << 3)
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLCE0	(1 << 2)
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLALE	(1 << 1)
#घोषणा	BALLOON3_न_अंकD_CONTROL_FLCLE	(1 << 0)

/* न_अंकD Status रेजिस्टर */
#घोषणा	BALLOON3_न_अंकD_STAT_RNB		(1 << 0)

/* न_अंकD Control2 रेजिस्टर */
#घोषणा	BALLOON3_न_अंकD_CONTROL2_16BIT	(1 << 0)

/* GPIOs क्रम irqs */
#घोषणा BALLOON3_GPIO_AUX_NIRQ		(94)
#घोषणा BALLOON3_GPIO_CODEC_IRQ		(95)

/* Timer and Idle LED locations */
#घोषणा BALLOON3_GPIO_LED_न_अंकD		(9)
#घोषणा BALLOON3_GPIO_LED_IDLE		(10)

/* backlight control */
#घोषणा BALLOON3_GPIO_RUN_BACKLIGHT	(99)

#घोषणा BALLOON3_GPIO_S0_CD		(105)

/* न_अंकD */
#घोषणा BALLOON3_GPIO_RUN_न_अंकD		(102)

/* PCF8574A Leds */
#घोषणा	BALLOON3_PCF_GPIO_BASE		160
#घोषणा	BALLOON3_PCF_GPIO_LED0		(BALLOON3_PCF_GPIO_BASE + 0)
#घोषणा	BALLOON3_PCF_GPIO_LED1		(BALLOON3_PCF_GPIO_BASE + 1)
#घोषणा	BALLOON3_PCF_GPIO_LED2		(BALLOON3_PCF_GPIO_BASE + 2)
#घोषणा	BALLOON3_PCF_GPIO_LED3		(BALLOON3_PCF_GPIO_BASE + 3)
#घोषणा	BALLOON3_PCF_GPIO_LED4		(BALLOON3_PCF_GPIO_BASE + 4)
#घोषणा	BALLOON3_PCF_GPIO_LED5		(BALLOON3_PCF_GPIO_BASE + 5)
#घोषणा	BALLOON3_PCF_GPIO_LED6		(BALLOON3_PCF_GPIO_BASE + 6)
#घोषणा	BALLOON3_PCF_GPIO_LED7		(BALLOON3_PCF_GPIO_BASE + 7)

/* FPGA Interrupt Mask/Acknowledge Register */
#घोषणा BALLOON3_INT_S0_IRQ		(1 << 0)  /* PCMCIA 0 IRQ */
#घोषणा BALLOON3_INT_S0_STSCHG		(1 << 1)  /* PCMCIA 0 status changed */

/* CPLD (and FPGA) पूर्णांकerface definitions */
#घोषणा CPLD_LCD0_DATA_SET             0x00
#घोषणा CPLD_LCD0_DATA_CLR             0x10
#घोषणा CPLD_LCD0_COMMAND_SET          0x01
#घोषणा CPLD_LCD0_COMMAND_CLR          0x11
#घोषणा CPLD_LCD1_DATA_SET             0x02
#घोषणा CPLD_LCD1_DATA_CLR             0x12
#घोषणा CPLD_LCD1_COMMAND_SET          0x03
#घोषणा CPLD_LCD1_COMMAND_CLR          0x13

#घोषणा CPLD_MISC_SET                  0x07
#घोषणा CPLD_MISC_CLR                  0x17
#घोषणा CPLD_MISC_LOON_NRESET_BIT      0
#घोषणा CPLD_MISC_LOON_UNSUSP_BIT      1
#घोषणा CPLD_MISC_RUN_5V_BIT           2
#घोषणा CPLD_MISC_CHG_D0_BIT           3
#घोषणा CPLD_MISC_CHG_D1_BIT           4
#घोषणा CPLD_MISC_DAC_NCS_BIT          5

#घोषणा CPLD_LCD_SET                   0x08
#घोषणा CPLD_LCD_CLR                   0x18
#घोषणा CPLD_LCD_BACKLIGHT_EN_0_BIT    0
#घोषणा CPLD_LCD_BACKLIGHT_EN_1_BIT    1
#घोषणा CPLD_LCD_LED_RED_BIT           4
#घोषणा CPLD_LCD_LED_GREEN_BIT         5
#घोषणा CPLD_LCD_NRESET_BIT            7

#घोषणा CPLD_LCD_RO_SET                0x09
#घोषणा CPLD_LCD_RO_CLR                0x19
#घोषणा CPLD_LCD_RO_LCD0_nWAIT_BIT     0
#घोषणा CPLD_LCD_RO_LCD1_nWAIT_BIT     1

#घोषणा CPLD_SERIAL_SET                0x0a
#घोषणा CPLD_SERIAL_CLR                0x1a
#घोषणा CPLD_SERIAL_GSM_RI_BIT         0
#घोषणा CPLD_SERIAL_GSM_CTS_BIT        1
#घोषणा CPLD_SERIAL_GSM_DTR_BIT        2
#घोषणा CPLD_SERIAL_LPR_CTS_BIT        3
#घोषणा CPLD_SERIAL_TC232_CTS_BIT      4
#घोषणा CPLD_SERIAL_TC232_DSR_BIT      5

#घोषणा CPLD_SROUTING_SET              0x0b
#घोषणा CPLD_SROUTING_CLR              0x1b
#घोषणा CPLD_SROUTING_MSP430_LPR       0
#घोषणा CPLD_SROUTING_MSP430_TC232     1
#घोषणा CPLD_SROUTING_MSP430_GSM       2
#घोषणा CPLD_SROUTING_LOON_LPR         (0 << 4)
#घोषणा CPLD_SROUTING_LOON_TC232       (1 << 4)
#घोषणा CPLD_SROUTING_LOON_GSM         (2 << 4)

#घोषणा CPLD_AROUTING_SET              0x0c
#घोषणा CPLD_AROUTING_CLR              0x1c
#घोषणा CPLD_AROUTING_MIC2PHONE_BIT    0
#घोषणा CPLD_AROUTING_PHONE2INT_BIT    1
#घोषणा CPLD_AROUTING_PHONE2EXT_BIT    2
#घोषणा CPLD_AROUTING_LOONL2INT_BIT    3
#घोषणा CPLD_AROUTING_LOONL2EXT_BIT    4
#घोषणा CPLD_AROUTING_LOONR2PHONE_BIT  5
#घोषणा CPLD_AROUTING_LOONR2INT_BIT    6
#घोषणा CPLD_AROUTING_LOONR2EXT_BIT    7

/* Balloon3 Interrupts */
#घोषणा BALLOON3_IRQ(x)		(IRQ_BOARD_START + (x))

#घोषणा BALLOON3_AUX_NIRQ	PXA_GPIO_TO_IRQ(BALLOON3_GPIO_AUX_NIRQ)
#घोषणा BALLOON3_CODEC_IRQ	PXA_GPIO_TO_IRQ(BALLOON3_GPIO_CODEC_IRQ)

#घोषणा BALLOON3_NR_IRQS	(IRQ_BOARD_START + 16)

बाह्य पूर्णांक balloon3_has(क्रमागत balloon3_features feature);

#पूर्ण_अगर
