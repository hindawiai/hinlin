<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Hardware specअगरic definitions क्रम SL-Cx000 series of PDAs
 *
 * Copyright (c) 2005 Alexander Wykes
 * Copyright (c) 2005 Riअक्षरd Purdie
 *
 * Based on Sharp's 2.4 kernel patches
 */
#अगर_अघोषित __ASM_ARCH_SPITZ_H
#घोषणा __ASM_ARCH_SPITZ_H  1
#पूर्ण_अगर

#समावेश "irqs.h" /* PXA_NR_BUILTIN_GPIO, PXA_GPIO_TO_IRQ */
#समावेश <linux/fb.h>

/* Spitz/Akita GPIOs */

#घोषणा SPITZ_GPIO_KEY_INT         (0) /* Key Interrupt */
#घोषणा SPITZ_GPIO_RESET           (1)
#घोषणा SPITZ_GPIO_nSD_DETECT      (9)
#घोषणा SPITZ_GPIO_TP_INT          (11) /* Touch Panel पूर्णांकerrupt */
#घोषणा SPITZ_GPIO_AK_INT          (13) /* Remote Control */
#घोषणा SPITZ_GPIO_ADS7846_CS      (14)
#घोषणा SPITZ_GPIO_SYNC            (16)
#घोषणा SPITZ_GPIO_MAX1111_CS      (20)
#घोषणा SPITZ_GPIO_FATAL_BAT       (21)
#घोषणा SPITZ_GPIO_HSYNC           (22)
#घोषणा SPITZ_GPIO_nSD_CLK         (32)
#घोषणा SPITZ_GPIO_USB_DEVICE      (35)
#घोषणा SPITZ_GPIO_USB_HOST        (37)
#घोषणा SPITZ_GPIO_USB_CONNECT     (41)
#घोषणा SPITZ_GPIO_LCDCON_CS       (53)
#घोषणा SPITZ_GPIO_nPCE            (54)
#घोषणा SPITZ_GPIO_nSD_WP          (81)
#घोषणा SPITZ_GPIO_ON_RESET        (89)
#घोषणा SPITZ_GPIO_BAT_COVER       (90)
#घोषणा SPITZ_GPIO_CF_CD           (94)
#घोषणा SPITZ_GPIO_ON_KEY          (95)
#घोषणा SPITZ_GPIO_SWA             (97)
#घोषणा SPITZ_GPIO_SWB             (96)
#घोषणा SPITZ_GPIO_CHRG_FULL       (101)
#घोषणा SPITZ_GPIO_CO              (101)
#घोषणा SPITZ_GPIO_CF_IRQ          (105)
#घोषणा SPITZ_GPIO_AC_IN           (115)
#घोषणा SPITZ_GPIO_HP_IN           (116)

/* Spitz Only GPIOs */

#घोषणा SPITZ_GPIO_CF2_IRQ         (106) /* CF slot1 Ready */
#घोषणा SPITZ_GPIO_CF2_CD          (93)


/* Spitz/Akita Keyboard Definitions */

#घोषणा SPITZ_KEY_STROBE_NUM         (11)
#घोषणा SPITZ_KEY_SENSE_NUM          (7)
#घोषणा SPITZ_GPIO_G0_STROBE_BIT     0x0f800000
#घोषणा SPITZ_GPIO_G1_STROBE_BIT     0x00100000
#घोषणा SPITZ_GPIO_G2_STROBE_BIT     0x01000000
#घोषणा SPITZ_GPIO_G3_STROBE_BIT     0x00041880
#घोषणा SPITZ_GPIO_G0_SENSE_BIT      0x00021000
#घोषणा SPITZ_GPIO_G1_SENSE_BIT      0x000000d4
#घोषणा SPITZ_GPIO_G2_SENSE_BIT      0x08000000
#घोषणा SPITZ_GPIO_G3_SENSE_BIT      0x00000000

#घोषणा SPITZ_GPIO_KEY_STROBE0       88
#घोषणा SPITZ_GPIO_KEY_STROBE1       23
#घोषणा SPITZ_GPIO_KEY_STROBE2       24
#घोषणा SPITZ_GPIO_KEY_STROBE3       25
#घोषणा SPITZ_GPIO_KEY_STROBE4       26
#घोषणा SPITZ_GPIO_KEY_STROBE5       27
#घोषणा SPITZ_GPIO_KEY_STROBE6       52
#घोषणा SPITZ_GPIO_KEY_STROBE7       103
#घोषणा SPITZ_GPIO_KEY_STROBE8       107
#घोषणा SPITZ_GPIO_KEY_STROBE9       108
#घोषणा SPITZ_GPIO_KEY_STROBE10      114

#घोषणा SPITZ_GPIO_KEY_SENSE0        12
#घोषणा SPITZ_GPIO_KEY_SENSE1        17
#घोषणा SPITZ_GPIO_KEY_SENSE2        91
#घोषणा SPITZ_GPIO_KEY_SENSE3        34
#घोषणा SPITZ_GPIO_KEY_SENSE4        36
#घोषणा SPITZ_GPIO_KEY_SENSE5        38
#घोषणा SPITZ_GPIO_KEY_SENSE6        39


/* Spitz Scoop Device (No. 1) GPIOs */
/* Suspend States in comments */
#घोषणा SPITZ_SCP_LED_GREEN     SCOOP_GPCR_PA11  /* Keep */
#घोषणा SPITZ_SCP_JK_B          SCOOP_GPCR_PA12  /* Keep */
#घोषणा SPITZ_SCP_CHRG_ON       SCOOP_GPCR_PA13  /* Keep */
#घोषणा SPITZ_SCP_MUTE_L        SCOOP_GPCR_PA14  /* Low */
#घोषणा SPITZ_SCP_MUTE_R        SCOOP_GPCR_PA15  /* Low */
#घोषणा SPITZ_SCP_CF_POWER      SCOOP_GPCR_PA16  /* Keep */
#घोषणा SPITZ_SCP_LED_ORANGE    SCOOP_GPCR_PA17  /* Keep */
#घोषणा SPITZ_SCP_JK_A          SCOOP_GPCR_PA18  /* Low */
#घोषणा SPITZ_SCP_ADC_TEMP_ON   SCOOP_GPCR_PA19  /* Low */

#घोषणा SPITZ_SCP_IO_सूची      (SPITZ_SCP_JK_B | SPITZ_SCP_CHRG_ON | \
                               SPITZ_SCP_MUTE_L | SPITZ_SCP_MUTE_R | \
                               SPITZ_SCP_CF_POWER | SPITZ_SCP_JK_A | SPITZ_SCP_ADC_TEMP_ON)
#घोषणा SPITZ_SCP_IO_OUT      (SPITZ_SCP_CHRG_ON | SPITZ_SCP_MUTE_L | SPITZ_SCP_MUTE_R)
#घोषणा SPITZ_SCP_SUS_CLR     (SPITZ_SCP_MUTE_L | SPITZ_SCP_MUTE_R | SPITZ_SCP_JK_A | SPITZ_SCP_ADC_TEMP_ON)
#घोषणा SPITZ_SCP_SUS_SET     0

#घोषणा SPITZ_SCP_GPIO_BASE	(PXA_NR_BUILTIN_GPIO)
#घोषणा SPITZ_GPIO_LED_GREEN	(SPITZ_SCP_GPIO_BASE + 0)
#घोषणा SPITZ_GPIO_JK_B		(SPITZ_SCP_GPIO_BASE + 1)
#घोषणा SPITZ_GPIO_CHRG_ON	(SPITZ_SCP_GPIO_BASE + 2)
#घोषणा SPITZ_GPIO_MUTE_L	(SPITZ_SCP_GPIO_BASE + 3)
#घोषणा SPITZ_GPIO_MUTE_R	(SPITZ_SCP_GPIO_BASE + 4)
#घोषणा SPITZ_GPIO_CF_POWER	(SPITZ_SCP_GPIO_BASE + 5)
#घोषणा SPITZ_GPIO_LED_ORANGE	(SPITZ_SCP_GPIO_BASE + 6)
#घोषणा SPITZ_GPIO_JK_A		(SPITZ_SCP_GPIO_BASE + 7)
#घोषणा SPITZ_GPIO_ADC_TEMP_ON	(SPITZ_SCP_GPIO_BASE + 8)

/* Spitz Scoop Device (No. 2) GPIOs */
/* Suspend States in comments */
#घोषणा SPITZ_SCP2_IR_ON           SCOOP_GPCR_PA11  /* High */
#घोषणा SPITZ_SCP2_AKIN_PULLUP     SCOOP_GPCR_PA12  /* Keep */
#घोषणा SPITZ_SCP2_RESERVED_1      SCOOP_GPCR_PA13  /* High */
#घोषणा SPITZ_SCP2_RESERVED_2      SCOOP_GPCR_PA14  /* Low */
#घोषणा SPITZ_SCP2_RESERVED_3      SCOOP_GPCR_PA15  /* Low */
#घोषणा SPITZ_SCP2_RESERVED_4      SCOOP_GPCR_PA16  /* Low */
#घोषणा SPITZ_SCP2_BACKLIGHT_CONT  SCOOP_GPCR_PA17  /* Low */
#घोषणा SPITZ_SCP2_BACKLIGHT_ON    SCOOP_GPCR_PA18  /* Low */
#घोषणा SPITZ_SCP2_MIC_BIAS        SCOOP_GPCR_PA19  /* Low */

#घोषणा SPITZ_SCP2_IO_सूची (SPITZ_SCP2_AKIN_PULLUP | SPITZ_SCP2_RESERVED_1 | \
                           SPITZ_SCP2_RESERVED_2 | SPITZ_SCP2_RESERVED_3 | SPITZ_SCP2_RESERVED_4 | \
                           SPITZ_SCP2_BACKLIGHT_CONT | SPITZ_SCP2_BACKLIGHT_ON | SPITZ_SCP2_MIC_BIAS)

#घोषणा SPITZ_SCP2_IO_OUT   (SPITZ_SCP2_AKIN_PULLUP | SPITZ_SCP2_RESERVED_1)
#घोषणा SPITZ_SCP2_SUS_CLR  (SPITZ_SCP2_RESERVED_2 | SPITZ_SCP2_RESERVED_3 | SPITZ_SCP2_RESERVED_4 | \
                             SPITZ_SCP2_BACKLIGHT_CONT | SPITZ_SCP2_BACKLIGHT_ON | SPITZ_SCP2_MIC_BIAS)
#घोषणा SPITZ_SCP2_SUS_SET  (SPITZ_SCP2_IR_ON | SPITZ_SCP2_RESERVED_1)

#घोषणा SPITZ_SCP2_GPIO_BASE		(PXA_NR_BUILTIN_GPIO + 12)
#घोषणा SPITZ_GPIO_IR_ON		(SPITZ_SCP2_GPIO_BASE + 0)
#घोषणा SPITZ_GPIO_AKIN_PULLUP		(SPITZ_SCP2_GPIO_BASE + 1)
#घोषणा SPITZ_GPIO_RESERVED_1		(SPITZ_SCP2_GPIO_BASE + 2)
#घोषणा SPITZ_GPIO_RESERVED_2		(SPITZ_SCP2_GPIO_BASE + 3)
#घोषणा SPITZ_GPIO_RESERVED_3		(SPITZ_SCP2_GPIO_BASE + 4)
#घोषणा SPITZ_GPIO_RESERVED_4		(SPITZ_SCP2_GPIO_BASE + 5)
#घोषणा SPITZ_GPIO_BACKLIGHT_CONT	(SPITZ_SCP2_GPIO_BASE + 6)
#घोषणा SPITZ_GPIO_BACKLIGHT_ON		(SPITZ_SCP2_GPIO_BASE + 7)
#घोषणा SPITZ_GPIO_MIC_BIAS		(SPITZ_SCP2_GPIO_BASE + 8)

/* Akita IO Expander GPIOs */
#घोषणा AKITA_IOEXP_GPIO_BASE		(PXA_NR_BUILTIN_GPIO + 12)
#घोषणा AKITA_GPIO_RESERVED_0		(AKITA_IOEXP_GPIO_BASE + 0)
#घोषणा AKITA_GPIO_RESERVED_1		(AKITA_IOEXP_GPIO_BASE + 1)
#घोषणा AKITA_GPIO_MIC_BIAS		(AKITA_IOEXP_GPIO_BASE + 2)
#घोषणा AKITA_GPIO_BACKLIGHT_ON		(AKITA_IOEXP_GPIO_BASE + 3)
#घोषणा AKITA_GPIO_BACKLIGHT_CONT	(AKITA_IOEXP_GPIO_BASE + 4)
#घोषणा AKITA_GPIO_AKIN_PULLUP		(AKITA_IOEXP_GPIO_BASE + 5)
#घोषणा AKITA_GPIO_IR_ON		(AKITA_IOEXP_GPIO_BASE + 6)
#घोषणा AKITA_GPIO_RESERVED_7		(AKITA_IOEXP_GPIO_BASE + 7)

/* Spitz IRQ Definitions */

#घोषणा SPITZ_IRQ_GPIO_KEY_INT        PXA_GPIO_TO_IRQ(SPITZ_GPIO_KEY_INT)
#घोषणा SPITZ_IRQ_GPIO_AC_IN          PXA_GPIO_TO_IRQ(SPITZ_GPIO_AC_IN)
#घोषणा SPITZ_IRQ_GPIO_AK_INT         PXA_GPIO_TO_IRQ(SPITZ_GPIO_AK_INT)
#घोषणा SPITZ_IRQ_GPIO_HP_IN          PXA_GPIO_TO_IRQ(SPITZ_GPIO_HP_IN)
#घोषणा SPITZ_IRQ_GPIO_TP_INT         PXA_GPIO_TO_IRQ(SPITZ_GPIO_TP_INT)
#घोषणा SPITZ_IRQ_GPIO_SYNC           PXA_GPIO_TO_IRQ(SPITZ_GPIO_SYNC)
#घोषणा SPITZ_IRQ_GPIO_ON_KEY         PXA_GPIO_TO_IRQ(SPITZ_GPIO_ON_KEY)
#घोषणा SPITZ_IRQ_GPIO_SWA            PXA_GPIO_TO_IRQ(SPITZ_GPIO_SWA)
#घोषणा SPITZ_IRQ_GPIO_SWB            PXA_GPIO_TO_IRQ(SPITZ_GPIO_SWB)
#घोषणा SPITZ_IRQ_GPIO_BAT_COVER      PXA_GPIO_TO_IRQ(SPITZ_GPIO_BAT_COVER)
#घोषणा SPITZ_IRQ_GPIO_FATAL_BAT      PXA_GPIO_TO_IRQ(SPITZ_GPIO_FATAL_BAT)
#घोषणा SPITZ_IRQ_GPIO_CO             PXA_GPIO_TO_IRQ(SPITZ_GPIO_CO)
#घोषणा SPITZ_IRQ_GPIO_CF_IRQ         PXA_GPIO_TO_IRQ(SPITZ_GPIO_CF_IRQ)
#घोषणा SPITZ_IRQ_GPIO_CF_CD          PXA_GPIO_TO_IRQ(SPITZ_GPIO_CF_CD)
#घोषणा SPITZ_IRQ_GPIO_CF2_IRQ        PXA_GPIO_TO_IRQ(SPITZ_GPIO_CF2_IRQ)
#घोषणा SPITZ_IRQ_GPIO_nSD_INT        PXA_GPIO_TO_IRQ(SPITZ_GPIO_nSD_INT)
#घोषणा SPITZ_IRQ_GPIO_nSD_DETECT     PXA_GPIO_TO_IRQ(SPITZ_GPIO_nSD_DETECT)

/*
 * Shared data काष्ठाures
 */
बाह्य काष्ठा platक्रमm_device spitzssp_device;
बाह्य काष्ठा sharpsl_अक्षरger_machinfo spitz_pm_machinfo;
