<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/mfd/asic3.h
 *
 * Compaq ASIC3 headers.
 *
 * Copyright 2001 Compaq Computer Corporation.
 * Copyright 2007-2008 OpenedHand Ltd.
 */

#अगर_अघोषित __ASIC3_H__
#घोषणा __ASIC3_H__

#समावेश <linux/types.h>

काष्ठा led_classdev;
काष्ठा asic3_led अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*शेष_trigger;
	काष्ठा led_classdev *cdev;
पूर्ण;

काष्ठा asic3_platक्रमm_data अणु
	u16 *gpio_config;
	अचिन्हित पूर्णांक gpio_config_num;

	अचिन्हित पूर्णांक irq_base;

	अचिन्हित पूर्णांक gpio_base;

	अचिन्हित पूर्णांक घड़ी_rate;

	काष्ठा asic3_led *leds;
पूर्ण;

#घोषणा ASIC3_NUM_GPIO_BANKS	4
#घोषणा ASIC3_GPIOS_PER_BANK	16
#घोषणा ASIC3_NUM_GPIOS		64
#घोषणा ASIC3_NR_IRQS		ASIC3_NUM_GPIOS + 6

#घोषणा ASIC3_IRQ_LED0		64
#घोषणा ASIC3_IRQ_LED1		65
#घोषणा ASIC3_IRQ_LED2		66
#घोषणा ASIC3_IRQ_SPI		67
#घोषणा ASIC3_IRQ_SMBUS		68
#घोषणा ASIC3_IRQ_OWM		69

#घोषणा ASIC3_TO_GPIO(gpio) (NR_BUILTIN_GPIO + (gpio))

#घोषणा ASIC3_GPIO_BANK_A	0
#घोषणा ASIC3_GPIO_BANK_B	1
#घोषणा ASIC3_GPIO_BANK_C	2
#घोषणा ASIC3_GPIO_BANK_D	3

#घोषणा ASIC3_GPIO(bank, gpio) \
	((ASIC3_GPIOS_PER_BANK * ASIC3_GPIO_BANK_##bank) + (gpio))
#घोषणा ASIC3_GPIO_bit(gpio) (1 << (gpio & 0xf))
/* All offsets below are specअगरied with this address bus shअगरt */
#घोषणा ASIC3_DEFAULT_ADDR_SHIFT 2

#घोषणा ASIC3_OFFSET(base, reg) (ASIC3_##base##_BASE + ASIC3_##base##_##reg)
#घोषणा ASIC3_GPIO_OFFSET(base, reg) \
	(ASIC3_GPIO_##base##_BASE + ASIC3_GPIO_##reg)

#घोषणा ASIC3_GPIO_A_BASE      0x0000
#घोषणा ASIC3_GPIO_B_BASE      0x0100
#घोषणा ASIC3_GPIO_C_BASE      0x0200
#घोषणा ASIC3_GPIO_D_BASE      0x0300

#घोषणा ASIC3_GPIO_TO_BANK(gpio) ((gpio) >> 4)
#घोषणा ASIC3_GPIO_TO_BIT(gpio)  ((gpio) - \
				  (ASIC3_GPIOS_PER_BANK * ((gpio) >> 4)))
#घोषणा ASIC3_GPIO_TO_MASK(gpio) (1 << ASIC3_GPIO_TO_BIT(gpio))
#घोषणा ASIC3_GPIO_TO_BASE(gpio) (ASIC3_GPIO_A_BASE + (((gpio) >> 4) * 0x0100))
#घोषणा ASIC3_BANK_TO_BASE(bank) (ASIC3_GPIO_A_BASE + ((bank) * 0x100))

#घोषणा ASIC3_GPIO_MASK          0x00    /* R/W 0:करोn't mask */
#घोषणा ASIC3_GPIO_सूचीECTION     0x04    /* R/W 0:input */
#घोषणा ASIC3_GPIO_OUT           0x08    /* R/W 0:output low */
#घोषणा ASIC3_GPIO_TRIGGER_TYPE  0x0c    /* R/W 0:level */
#घोषणा ASIC3_GPIO_EDGE_TRIGGER  0x10    /* R/W 0:falling */
#घोषणा ASIC3_GPIO_LEVEL_TRIGGER 0x14    /* R/W 0:low level detect */
#घोषणा ASIC3_GPIO_SLEEP_MASK    0x18    /* R/W 0:करोn't mask in sleep mode */
#घोषणा ASIC3_GPIO_SLEEP_OUT     0x1c    /* R/W level 0:low in sleep mode */
#घोषणा ASIC3_GPIO_BAT_FAULT_OUT 0x20    /* R/W level 0:low in batt_fault */
#घोषणा ASIC3_GPIO_INT_STATUS    0x24    /* R/W 0:none, 1:detect */
#घोषणा ASIC3_GPIO_ALT_FUNCTION  0x28	 /* R/W 1:LED रेजिस्टर control */
#घोषणा ASIC3_GPIO_SLEEP_CONF    0x2c    /*
					  * R/W bit 1: स्वतःsleep
					  * 0: disable gposlpout in normal mode,
					  * enable gposlpout in sleep mode.
					  */
#घोषणा ASIC3_GPIO_STATUS        0x30    /* R   Pin status */

/*
 * ASIC3 GPIO config
 *
 * Bits 0..6   gpio number
 * Bits 7..13  Alternate function
 * Bit  14     Direction
 * Bit  15     Initial value
 *
 */
#घोषणा ASIC3_CONFIG_GPIO_PIN(config) ((config) & 0x7f)
#घोषणा ASIC3_CONFIG_GPIO_ALT(config)  (((config) & (0x7f << 7)) >> 7)
#घोषणा ASIC3_CONFIG_GPIO_सूची(config)  ((config & (1 << 14)) >> 14)
#घोषणा ASIC3_CONFIG_GPIO_INIT(config) ((config & (1 << 15)) >> 15)
#घोषणा ASIC3_CONFIG_GPIO(gpio, alt, dir, init) (((gpio) & 0x7f) \
	| (((alt) & 0x7f) << 7) | (((dir) & 0x1) << 14) \
	| (((init) & 0x1) << 15))
#घोषणा ASIC3_CONFIG_GPIO_DEFAULT(gpio, dir, init) \
	ASIC3_CONFIG_GPIO((gpio), 0, (dir), (init))
#घोषणा ASIC3_CONFIG_GPIO_DEFAULT_OUT(gpio, init) \
	ASIC3_CONFIG_GPIO((gpio), 0, 1, (init))

/*
 * Alternate functions
 */
#घोषणा ASIC3_GPIOA11_PWM0		ASIC3_CONFIG_GPIO(11, 1, 1, 0)
#घोषणा ASIC3_GPIOA12_PWM1		ASIC3_CONFIG_GPIO(12, 1, 1, 0)
#घोषणा ASIC3_GPIOA15_CONTROL_CX	ASIC3_CONFIG_GPIO(15, 1, 1, 0)
#घोषणा ASIC3_GPIOC0_LED0		ASIC3_CONFIG_GPIO(32, 1, 0, 0)
#घोषणा ASIC3_GPIOC1_LED1		ASIC3_CONFIG_GPIO(33, 1, 0, 0)
#घोषणा ASIC3_GPIOC2_LED2		ASIC3_CONFIG_GPIO(34, 1, 0, 0)
#घोषणा ASIC3_GPIOC3_SPI_RXD		ASIC3_CONFIG_GPIO(35, 1, 0, 0)
#घोषणा ASIC3_GPIOC4_CF_nCD		ASIC3_CONFIG_GPIO(36, 1, 0, 0)
#घोषणा ASIC3_GPIOC4_SPI_TXD		ASIC3_CONFIG_GPIO(36, 1, 1, 0)
#घोषणा ASIC3_GPIOC5_SPI_CLK		ASIC3_CONFIG_GPIO(37, 1, 1, 0)
#घोषणा ASIC3_GPIOC5_nCIOW		ASIC3_CONFIG_GPIO(37, 1, 1, 0)
#घोषणा ASIC3_GPIOC6_nCIOR		ASIC3_CONFIG_GPIO(38, 1, 1, 0)
#घोषणा ASIC3_GPIOC7_nPCE_1		ASIC3_CONFIG_GPIO(39, 1, 0, 0)
#घोषणा ASIC3_GPIOC8_nPCE_2		ASIC3_CONFIG_GPIO(40, 1, 0, 0)
#घोषणा ASIC3_GPIOC9_nPOE		ASIC3_CONFIG_GPIO(41, 1, 0, 0)
#घोषणा ASIC3_GPIOC10_nPWE		ASIC3_CONFIG_GPIO(42, 1, 0, 0)
#घोषणा ASIC3_GPIOC11_PSKTSEL		ASIC3_CONFIG_GPIO(43, 1, 0, 0)
#घोषणा ASIC3_GPIOC12_nPREG		ASIC3_CONFIG_GPIO(44, 1, 0, 0)
#घोषणा ASIC3_GPIOC13_nPWAIT		ASIC3_CONFIG_GPIO(45, 1, 1, 0)
#घोषणा ASIC3_GPIOC14_nPIOIS16		ASIC3_CONFIG_GPIO(46, 1, 1, 0)
#घोषणा ASIC3_GPIOC15_nPIOR		ASIC3_CONFIG_GPIO(47, 1, 0, 0)
#घोषणा ASIC3_GPIOD4_CF_nCD		ASIC3_CONFIG_GPIO(52, 1, 0, 0)
#घोषणा ASIC3_GPIOD11_nCIOIS16		ASIC3_CONFIG_GPIO(59, 1, 0, 0)
#घोषणा ASIC3_GPIOD12_nCWAIT		ASIC3_CONFIG_GPIO(60, 1, 0, 0)
#घोषणा ASIC3_GPIOD15_nPIOW		ASIC3_CONFIG_GPIO(63, 1, 0, 0)


#घोषणा ASIC3_SPI_Base		      0x0400
#घोषणा ASIC3_SPI_Control               0x0000
#घोषणा ASIC3_SPI_TxData                0x0004
#घोषणा ASIC3_SPI_RxData                0x0008
#घोषणा ASIC3_SPI_Int                   0x000c
#घोषणा ASIC3_SPI_Status                0x0010

#घोषणा SPI_CONTROL_SPR(clk)      ((clk) & 0x0f)  /* Clock rate */

#घोषणा ASIC3_PWM_0_Base                0x0500
#घोषणा ASIC3_PWM_1_Base                0x0600
#घोषणा ASIC3_PWM_TimeBase              0x0000
#घोषणा ASIC3_PWM_PeriodTime            0x0004
#घोषणा ASIC3_PWM_DutyTime              0x0008

#घोषणा PWM_TIMEBASE_VALUE(x)    ((x)&0xf)   /* Low 4 bits sets समय base */
#घोषणा PWM_TIMEBASE_ENABLE     (1 << 4)   /* Enable घड़ी */

#घोषणा ASIC3_NUM_LEDS                  3
#घोषणा ASIC3_LED_0_Base                0x0700
#घोषणा ASIC3_LED_1_Base                0x0800
#घोषणा ASIC3_LED_2_Base 		      0x0900
#घोषणा ASIC3_LED_TimeBase              0x0000    /* R/W  7 bits */
#घोषणा ASIC3_LED_PeriodTime            0x0004    /* R/W 12 bits */
#घोषणा ASIC3_LED_DutyTime              0x0008    /* R/W 12 bits */
#घोषणा ASIC3_LED_AutoStopCount         0x000c    /* R/W 16 bits */

/* LED TimeBase bits - match ASIC2 */
#घोषणा LED_TBS		0x0f /* Low 4 bits sets समय base, max = 13 */
			     /* Note: max = 5 on hx4700	*/
			     /* 0: maximum समय base */
			     /* 1: maximum समय base / 2 */
			     /* n: maximum समय base / 2^n */

#घोषणा LED_EN		(1 << 4) /* LED ON/OFF 0:off, 1:on */
#घोषणा LED_AUTOSTOP	(1 << 5) /* LED ON/OFF स्वतः stop 0:disable, 1:enable */
#घोषणा LED_ALWAYS	(1 << 6) /* LED Interrupt Mask 0:No mask, 1:mask */

#घोषणा ASIC3_CLOCK_BASE	   0x0A00
#घोषणा ASIC3_CLOCK_CDEX           0x00
#घोषणा ASIC3_CLOCK_SEL            0x04

#घोषणा CLOCK_CDEX_SOURCE       (1 << 0)  /* 2 bits */
#घोषणा CLOCK_CDEX_SOURCE0      (1 << 0)
#घोषणा CLOCK_CDEX_SOURCE1      (1 << 1)
#घोषणा CLOCK_CDEX_SPI          (1 << 2)
#घोषणा CLOCK_CDEX_OWM          (1 << 3)
#घोषणा CLOCK_CDEX_PWM0         (1 << 4)
#घोषणा CLOCK_CDEX_PWM1         (1 << 5)
#घोषणा CLOCK_CDEX_LED0         (1 << 6)
#घोषणा CLOCK_CDEX_LED1         (1 << 7)
#घोषणा CLOCK_CDEX_LED2         (1 << 8)

/* Clocks settings: 1 क्रम 24.576 MHz, 0 क्रम 12.288Mhz */
#घोषणा CLOCK_CDEX_SD_HOST      (1 << 9)   /* R/W: SD host घड़ी source */
#घोषणा CLOCK_CDEX_SD_BUS       (1 << 10)  /* R/W: SD bus घड़ी source ctrl */
#घोषणा CLOCK_CDEX_SMBUS        (1 << 11)
#घोषणा CLOCK_CDEX_CONTROL_CX   (1 << 12)

#घोषणा CLOCK_CDEX_EX0          (1 << 13)  /* R/W: 32.768 kHz crystal */
#घोषणा CLOCK_CDEX_EX1          (1 << 14)  /* R/W: 24.576 MHz crystal */

#घोषणा CLOCK_SEL_SD_HCLK_SEL   (1 << 0)   /* R/W: SDIO host घड़ी select */
#घोषणा CLOCK_SEL_SD_BCLK_SEL   (1 << 1)   /* R/W: SDIO bus घड़ी select */

/* R/W: INT घड़ी source control (32.768 kHz) */
#घोषणा CLOCK_SEL_CX            (1 << 2)


#घोषणा ASIC3_INTR_BASE		0x0B00

#घोषणा ASIC3_INTR_INT_MASK       0x00  /* Interrupt mask control */
#घोषणा ASIC3_INTR_P_INT_STAT     0x04  /* Peripheral पूर्णांकerrupt status */
#घोषणा ASIC3_INTR_INT_CPS        0x08  /* Interrupt समयr घड़ी pre-scale */
#घोषणा ASIC3_INTR_INT_TBS        0x0c  /* Interrupt समयr set */

#घोषणा ASIC3_INTMASK_GINTMASK    (1 << 0)  /* Global INTs mask 1:enable */
#घोषणा ASIC3_INTMASK_GINTEL      (1 << 1)  /* 1: rising edge, 0: hi level */
#घोषणा ASIC3_INTMASK_MASK0       (1 << 2)
#घोषणा ASIC3_INTMASK_MASK1       (1 << 3)
#घोषणा ASIC3_INTMASK_MASK2       (1 << 4)
#घोषणा ASIC3_INTMASK_MASK3       (1 << 5)
#घोषणा ASIC3_INTMASK_MASK4       (1 << 6)
#घोषणा ASIC3_INTMASK_MASK5       (1 << 7)

#घोषणा ASIC3_INTR_PERIPHERAL_A   (1 << 0)
#घोषणा ASIC3_INTR_PERIPHERAL_B   (1 << 1)
#घोषणा ASIC3_INTR_PERIPHERAL_C   (1 << 2)
#घोषणा ASIC3_INTR_PERIPHERAL_D   (1 << 3)
#घोषणा ASIC3_INTR_LED0           (1 << 4)
#घोषणा ASIC3_INTR_LED1           (1 << 5)
#घोषणा ASIC3_INTR_LED2           (1 << 6)
#घोषणा ASIC3_INTR_SPI            (1 << 7)
#घोषणा ASIC3_INTR_SMBUS          (1 << 8)
#घोषणा ASIC3_INTR_OWM            (1 << 9)

#घोषणा ASIC3_INTR_CPS(x)         ((x)&0x0f)    /* 4 bits, max 14 */
#घोषणा ASIC3_INTR_CPS_SET        (1 << 4)    /* Time base enable */


/* Basic control of the SD ASIC */
#घोषणा ASIC3_SDHWCTRL_BASE     0x0E00
#घोषणा ASIC3_SDHWCTRL_SDCONF     0x00

#घोषणा ASIC3_SDHWCTRL_SUSPEND    (1 << 0)  /* 1=suspend all SD operations */
#घोषणा ASIC3_SDHWCTRL_CLKSEL     (1 << 1)  /* 1=SDICK, 0=HCLK */
#घोषणा ASIC3_SDHWCTRL_PCLR       (1 << 2)  /* All रेजिस्टरs of SDIO cleared */
#घोषणा ASIC3_SDHWCTRL_LEVCD      (1 << 3)  /* SD card detection: 0:low */

/* SD card ग_लिखो protection: 0=high */
#घोषणा ASIC3_SDHWCTRL_LEVWP      (1 << 4)
#घोषणा ASIC3_SDHWCTRL_SDLED      (1 << 5)  /* SD card LED संकेत 0=disable */

/* SD card घातer supply ctrl 1=enable */
#घोषणा ASIC3_SDHWCTRL_SDPWR      (1 << 6)

#घोषणा ASIC3_EXTCF_BASE        0x1100

#घोषणा ASIC3_EXTCF_SELECT        0x00
#घोषणा ASIC3_EXTCF_RESET         0x04

#घोषणा ASIC3_EXTCF_SMOD0	         (1 << 0)  /* slot number of mode 0 */
#घोषणा ASIC3_EXTCF_SMOD1	         (1 << 1)  /* slot number of mode 1 */
#घोषणा ASIC3_EXTCF_SMOD2	         (1 << 2)  /* slot number of mode 2 */
#घोषणा ASIC3_EXTCF_OWM_EN	         (1 << 4)  /* enable onewire module */
#घोषणा ASIC3_EXTCF_OWM_SMB	         (1 << 5)  /* OWM bus selection */
#घोषणा ASIC3_EXTCF_OWM_RESET            (1 << 6)  /* ?? used by OWM and CF */
#घोषणा ASIC3_EXTCF_CF0_SLEEP_MODE       (1 << 7)  /* CF0 sleep state */
#घोषणा ASIC3_EXTCF_CF1_SLEEP_MODE       (1 << 8)  /* CF1 sleep state */
#घोषणा ASIC3_EXTCF_CF0_PWAIT_EN         (1 << 10) /* CF0 PWAIT_n control */
#घोषणा ASIC3_EXTCF_CF1_PWAIT_EN         (1 << 11) /* CF1 PWAIT_n control */
#घोषणा ASIC3_EXTCF_CF0_BUF_EN           (1 << 12) /* CF0 buffer control */
#घोषणा ASIC3_EXTCF_CF1_BUF_EN           (1 << 13) /* CF1 buffer control */
#घोषणा ASIC3_EXTCF_SD_MEM_ENABLE        (1 << 14)
#घोषणा ASIC3_EXTCF_CF_SLEEP             (1 << 15) /* CF sleep mode control */

/*********************************************
 *  The Onewire पूर्णांकerface (DS1WM) is handled
 *  by the ds1wm driver.
 *
 *********************************************/

#घोषणा ASIC3_OWM_BASE		0xC00

/*****************************************************************************
 *  The SD configuration रेजिस्टरs are at a completely dअगरferent location
 *  in memory.  They are भागided पूर्णांकo three sets of रेजिस्टरs:
 *
 *  SD_CONFIG         Core configuration रेजिस्टर
 *  SD_CTRL           Control रेजिस्टरs क्रम SD operations
 *  SDIO_CTRL         Control रेजिस्टरs क्रम SDIO operations
 *
 *****************************************************************************/
#घोषणा ASIC3_SD_CONFIG_BASE	0x0400 /* Assumes 32 bit addressing */
#घोषणा ASIC3_SD_CONFIG_SIZE	0x0200 /* Assumes 32 bit addressing */
#घोषणा ASIC3_SD_CTRL_BASE	0x1000
#घोषणा ASIC3_SDIO_CTRL_BASE	0x1200

#घोषणा ASIC3_MAP_SIZE_32BIT	0x2000
#घोषणा ASIC3_MAP_SIZE_16BIT	0x1000

/* Functions needed by leds-asic3 */

काष्ठा asic3;
बाह्य व्योम asic3_ग_लिखो_रेजिस्टर(काष्ठा asic3 *asic, अचिन्हित पूर्णांक reg, u32 val);
बाह्य u32 asic3_पढ़ो_रेजिस्टर(काष्ठा asic3 *asic, अचिन्हित पूर्णांक reg);

#पूर्ण_अगर /* __ASIC3_H__ */
