<शैली गुरु>
/*
 * Pinctrl driver क्रम NXP LPC18xx/LPC43xx System Control Unit (SCU)
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "core.h"
#समावेश "pinctrl-utils.h"

/* LPC18XX SCU analog function रेजिस्टरs */
#घोषणा LPC18XX_SCU_REG_ENAIO0		0xc88
#घोषणा LPC18XX_SCU_REG_ENAIO1		0xc8c
#घोषणा LPC18XX_SCU_REG_ENAIO2		0xc90
#घोषणा LPC18XX_SCU_REG_ENAIO2_DAC	BIT(0)

/* LPC18XX SCU pin रेजिस्टर definitions */
#घोषणा LPC18XX_SCU_PIN_MODE_MASK	0x7
#घोषणा LPC18XX_SCU_PIN_EPD		BIT(3)
#घोषणा LPC18XX_SCU_PIN_EPUN		BIT(4)
#घोषणा LPC18XX_SCU_PIN_EHS		BIT(5)
#घोषणा LPC18XX_SCU_PIN_EZI		BIT(6)
#घोषणा LPC18XX_SCU_PIN_ZIF		BIT(7)
#घोषणा LPC18XX_SCU_PIN_EHD_MASK	0x300
#घोषणा LPC18XX_SCU_PIN_EHD_POS		8

#घोषणा LPC18XX_SCU_USB1_EPD		BIT(2)
#घोषणा LPC18XX_SCU_USB1_EPWR		BIT(4)

#घोषणा LPC18XX_SCU_I2C0_EFP		BIT(0)
#घोषणा LPC18XX_SCU_I2C0_EHD		BIT(2)
#घोषणा LPC18XX_SCU_I2C0_EZI		BIT(3)
#घोषणा LPC18XX_SCU_I2C0_ZIF		BIT(7)
#घोषणा LPC18XX_SCU_I2C0_SCL_SHIFT	0
#घोषणा LPC18XX_SCU_I2C0_SDA_SHIFT	8

#घोषणा LPC18XX_SCU_FUNC_PER_PIN	8

/* LPC18XX SCU pin पूर्णांकerrupt select रेजिस्टरs */
#घोषणा LPC18XX_SCU_PINTSEL0		0xe00
#घोषणा LPC18XX_SCU_PINTSEL1		0xe04
#घोषणा LPC18XX_SCU_PINTSEL_VAL_MASK	0xff
#घोषणा LPC18XX_SCU_PINTSEL_PORT_SHIFT	5
#घोषणा LPC18XX_SCU_IRQ_PER_PINTSEL	4
#घोषणा LPC18XX_GPIO_PINS_PER_PORT	32
#घोषणा LPC18XX_GPIO_PIN_पूर्णांक_उच्च	8

#घोषणा LPC18XX_SCU_PINTSEL_VAL(val, n) \
	((val) << (((n) % LPC18XX_SCU_IRQ_PER_PINTSEL) * 8))

/* LPC18xx pin types */
क्रमागत अणु
	TYPE_ND,	/* Normal-drive */
	TYPE_HD,	/* High-drive */
	TYPE_HS,	/* High-speed */
	TYPE_I2C0,
	TYPE_USB1,
पूर्ण;

/* LPC18xx pin functions */
क्रमागत अणु
	FUNC_R,		/* Reserved */
	FUNC_ADC,
	FUNC_ADCTRIG,
	FUNC_CAN0,
	FUNC_CAN1,
	FUNC_CGU_OUT,
	FUNC_CLKIN,
	FUNC_CLKOUT,
	FUNC_CTIN,
	FUNC_CTOUT,
	FUNC_DAC,
	FUNC_EMC,
	FUNC_EMC_ALT,
	FUNC_ENET,
	FUNC_ENET_ALT,
	FUNC_GPIO,
	FUNC_I2C0,
	FUNC_I2C1,
	FUNC_I2S0_RX_MCLK,
	FUNC_I2S0_RX_SCK,
	FUNC_I2S0_RX_SDA,
	FUNC_I2S0_RX_WS,
	FUNC_I2S0_TX_MCLK,
	FUNC_I2S0_TX_SCK,
	FUNC_I2S0_TX_SDA,
	FUNC_I2S0_TX_WS,
	FUNC_I2S1,
	FUNC_LCD,
	FUNC_LCD_ALT,
	FUNC_MCTRL,
	FUNC_NMI,
	FUNC_QEI,
	FUNC_SDMMC,
	FUNC_SGPIO,
	FUNC_SPI,
	FUNC_SPIFI,
	FUNC_SSP0,
	FUNC_SSP0_ALT,
	FUNC_SSP1,
	FUNC_TIMER0,
	FUNC_TIMER1,
	FUNC_TIMER2,
	FUNC_TIMER3,
	FUNC_TRACE,
	FUNC_UART0,
	FUNC_UART1,
	FUNC_UART2,
	FUNC_UART3,
	FUNC_USB0,
	FUNC_USB1,
	FUNC_MAX
पूर्ण;

अटल स्थिर अक्षर *स्थिर lpc18xx_function_names[] = अणु
	[FUNC_R]		= "reserved",
	[FUNC_ADC]		= "adc",
	[FUNC_ADCTRIG]		= "adctrig",
	[FUNC_CAN0]		= "can0",
	[FUNC_CAN1]		= "can1",
	[FUNC_CGU_OUT]		= "cgu_out",
	[FUNC_CLKIN]		= "clkin",
	[FUNC_CLKOUT]		= "clkout",
	[FUNC_CTIN]		= "ctin",
	[FUNC_CTOUT]		= "ctout",
	[FUNC_DAC]		= "dac",
	[FUNC_EMC]		= "emc",
	[FUNC_EMC_ALT]		= "emc_alt",
	[FUNC_ENET]		= "enet",
	[FUNC_ENET_ALT]		= "enet_alt",
	[FUNC_GPIO]		= "gpio",
	[FUNC_I2C0]		= "i2c0",
	[FUNC_I2C1]		= "i2c1",
	[FUNC_I2S0_RX_MCLK]	= "i2s0_rx_mclk",
	[FUNC_I2S0_RX_SCK]	= "i2s0_rx_sck",
	[FUNC_I2S0_RX_SDA]	= "i2s0_rx_sda",
	[FUNC_I2S0_RX_WS]	= "i2s0_rx_ws",
	[FUNC_I2S0_TX_MCLK]	= "i2s0_tx_mclk",
	[FUNC_I2S0_TX_SCK]	= "i2s0_tx_sck",
	[FUNC_I2S0_TX_SDA]	= "i2s0_tx_sda",
	[FUNC_I2S0_TX_WS]	= "i2s0_tx_ws",
	[FUNC_I2S1]		= "i2s1",
	[FUNC_LCD]		= "lcd",
	[FUNC_LCD_ALT]		= "lcd_alt",
	[FUNC_MCTRL]		= "mctrl",
	[FUNC_NMI]		= "nmi",
	[FUNC_QEI]		= "qei",
	[FUNC_SDMMC]		= "sdmmc",
	[FUNC_SGPIO]		= "sgpio",
	[FUNC_SPI]		= "spi",
	[FUNC_SPIFI]		= "spifi",
	[FUNC_SSP0]		= "ssp0",
	[FUNC_SSP0_ALT]		= "ssp0_alt",
	[FUNC_SSP1]		= "ssp1",
	[FUNC_TIMER0]		= "timer0",
	[FUNC_TIMER1]		= "timer1",
	[FUNC_TIMER2]		= "timer2",
	[FUNC_TIMER3]		= "timer3",
	[FUNC_TRACE]		= "trace",
	[FUNC_UART0]		= "uart0",
	[FUNC_UART1]		= "uart1",
	[FUNC_UART2]		= "uart2",
	[FUNC_UART3]		= "uart3",
	[FUNC_USB0]		= "usb0",
	[FUNC_USB1]		= "usb1",
पूर्ण;

काष्ठा lpc18xx_pmx_func अणु
	स्थिर अक्षर **groups;
	अचिन्हित ngroups;
पूर्ण;

काष्ठा lpc18xx_scu_data अणु
	काष्ठा pinctrl_dev *pctl;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा lpc18xx_pmx_func func[FUNC_MAX];
पूर्ण;

काष्ठा lpc18xx_pin_caps अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित अक्षर functions[LPC18XX_SCU_FUNC_PER_PIN];
	अचिन्हित अक्षर analog;
	अचिन्हित अक्षर type;
पूर्ण;

/* Analog pins are required to have both bias and input disabled */
#घोषणा LPC18XX_SCU_ANALOG_PIN_CFG	0x10

/* Macros to maniupluate analog member in lpc18xx_pin_caps */
#घोषणा LPC18XX_ANALOG_PIN		BIT(7)
#घोषणा LPC18XX_ANALOG_ADC(a)		((a >> 5) & 0x3)
#घोषणा LPC18XX_ANALOG_BIT_MASK		0x1f
#घोषणा ADC0				(LPC18XX_ANALOG_PIN | (0x00 << 5))
#घोषणा ADC1				(LPC18XX_ANALOG_PIN | (0x01 << 5))
#घोषणा DAC				LPC18XX_ANALOG_PIN

#घोषणा LPC_P(port, pin, f0, f1, f2, f3, f4, f5, f6, f7, a, t)	\
अटल काष्ठा lpc18xx_pin_caps lpc18xx_pin_p##port##_##pin = अणु	\
	.offset = 0x##port * 32 * 4 + pin * 4,			\
	.functions = अणु						\
			FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
			FUNC_##f3, FUNC_##f4, FUNC_##f5,	\
			FUNC_##f6, FUNC_##f7,			\
	पूर्ण,							\
	.analog = a,						\
	.type = TYPE_##t,					\
पूर्ण

#घोषणा LPC_N(pname, off, f0, f1, f2, f3, f4, f5, f6, f7, a, t)	\
अटल काष्ठा lpc18xx_pin_caps lpc18xx_pin_##pname = अणु		\
	.offset = off,						\
	.functions = अणु						\
			FUNC_##f0, FUNC_##f1, FUNC_##f2,	\
			FUNC_##f3, FUNC_##f4, FUNC_##f5,	\
			FUNC_##f6, FUNC_##f7,			\
	पूर्ण,							\
	.analog = a,						\
	.type = TYPE_##t,					\
पूर्ण


/* Pinmuxing table taken from data sheet */
/*    Pin    FUNC0  FUNC1  FUNC2  FUNC3   FUNC4   FUNC5   FUNC6    FUNC7 ANALOG TYPE */
LPC_P(0,0,   GPIO,  SSP1,  ENET,  SGPIO,      R,      R, I2S0_TX_WS,I2S1,     0, ND);
LPC_P(0,1,   GPIO,  SSP1,ENET_ALT,SGPIO,      R,      R,   ENET,    I2S1,     0, ND);
LPC_P(1,0,   GPIO,  CTIN,   EMC,      R,      R,   SSP0,  SGPIO,       R,     0, ND);
LPC_P(1,1,   GPIO, CTOUT,   EMC,  SGPIO,      R,   SSP0,      R,       R,     0, ND);
LPC_P(1,2,   GPIO, CTOUT,   EMC,  SGPIO,      R,   SSP0,      R,       R,     0, ND);
LPC_P(1,3,   GPIO, CTOUT, SGPIO,    EMC,   USB0,   SSP1,      R,   SDMMC,     0, ND);
LPC_P(1,4,   GPIO, CTOUT, SGPIO,    EMC,   USB0,   SSP1,      R,   SDMMC,     0, ND);
LPC_P(1,5,   GPIO, CTOUT,     R,    EMC,   USB0,   SSP1,  SGPIO,   SDMMC,     0, ND);
LPC_P(1,6,   GPIO,  CTIN,     R,    EMC,      R,      R,  SGPIO,   SDMMC,     0, ND);
LPC_P(1,7,   GPIO, UART1, CTOUT,    EMC,   USB0,      R,      R,       R,     0, ND);
LPC_P(1,8,   GPIO, UART1, CTOUT,    EMC,      R,      R,      R,   SDMMC,     0, ND);
LPC_P(1,9,   GPIO, UART1, CTOUT,    EMC,      R,      R,      R,   SDMMC,     0, ND);
LPC_P(1,10,  GPIO, UART1, CTOUT,    EMC,      R,      R,      R,   SDMMC,     0, ND);
LPC_P(1,11,  GPIO, UART1, CTOUT,    EMC,      R,      R,      R,   SDMMC,     0, ND);
LPC_P(1,12,  GPIO, UART1,     R,    EMC, TIMER0,      R,  SGPIO,   SDMMC,     0, ND);
LPC_P(1,13,  GPIO, UART1,     R,    EMC, TIMER0,      R,  SGPIO,   SDMMC,     0, ND);
LPC_P(1,14,  GPIO, UART1,     R,    EMC, TIMER0,      R,  SGPIO,       R,     0, ND);
LPC_P(1,15,  GPIO, UART2, SGPIO,   ENET, TIMER0,      R,      R,       R,     0, ND);
LPC_P(1,16,  GPIO, UART2, SGPIO,ENET_ALT,TIMER0,      R,      R,    ENET,     0, ND);
LPC_P(1,17,  GPIO, UART2,     R,   ENET, TIMER0,   CAN1,  SGPIO,       R,     0, HD);
LPC_P(1,18,  GPIO, UART2,     R,   ENET, TIMER0,   CAN1,  SGPIO,       R,     0, ND);
LPC_P(1,19,  ENET,  SSP1,     R,      R, CLKOUT,      R, I2S0_RX_MCLK,I2S1,   0, ND);
LPC_P(1,20,  GPIO,  SSP1,     R,   ENET, TIMER0,      R,  SGPIO,       R,     0, ND);
LPC_P(2,0,  SGPIO, UART0,   EMC,   USB0,   GPIO,      R, TIMER3,    ENET,     0, ND);
LPC_P(2,1,  SGPIO, UART0,   EMC,   USB0,   GPIO,      R, TIMER3,       R,     0, ND);
LPC_P(2,2,  SGPIO, UART0,   EMC,   USB0,   GPIO,   CTIN, TIMER3,       R,     0, ND);
LPC_P(2,3,  SGPIO,  I2C1, UART3,   CTIN,   GPIO,      R, TIMER3,    USB0,     0, HD);
LPC_P(2,4,  SGPIO,  I2C1, UART3,   CTIN,   GPIO,      R, TIMER3,    USB0,     0, HD);
LPC_P(2,5,  SGPIO,  CTIN,  USB1, ADCTRIG,  GPIO,      R, TIMER3,    USB0,     0, HD);
LPC_P(2,6,  SGPIO, UART0,   EMC,   USB0,   GPIO,   CTIN, TIMER3,       R,     0, ND);
LPC_P(2,7,   GPIO, CTOUT, UART3,    EMC,      R,      R, TIMER3,       R,     0, ND);
LPC_P(2,8,  SGPIO, CTOUT, UART3,    EMC,   GPIO,      R,      R,       R,     0, ND);
LPC_P(2,9,   GPIO, CTOUT, UART3,    EMC,      R,      R,      R,       R,     0, ND);
LPC_P(2,10,  GPIO, CTOUT, UART2,    EMC,      R,      R,      R,       R,     0, ND);
LPC_P(2,11,  GPIO, CTOUT, UART2,    EMC,      R,      R,      R,       R,     0, ND);
LPC_P(2,12,  GPIO, CTOUT,     R,    EMC,      R,      R,      R,   UART2,     0, ND);
LPC_P(2,13,  GPIO,  CTIN,     R,    EMC,      R,      R,      R,   UART2,     0, ND);
LPC_P(3,0,  I2S0_RX_SCK, I2S0_RX_MCLK, I2S0_TX_SCK, I2S0_TX_MCLK,SSP0,R,R,R,  0, ND);
LPC_P(3,1,  I2S0_TX_WS, I2S0_RX_WS,CAN0,USB1,GPIO,    R,    LCD,       R,     0, ND);
LPC_P(3,2,  I2S0_TX_SDA, I2S0_RX_SDA,CAN0,USB1,GPIO,  R,    LCD,      R,      0, ND);
LPC_P(3,3,      R,   SPI,  SSP0,  SPIFI, CGU_OUT,R, I2S0_TX_MCLK,  I2S1,      0, HS);
LPC_P(3,4,   GPIO,     R,     R,  SPIFI,  UART1, I2S0_TX_WS, I2S1,  LCD,      0, ND);
LPC_P(3,5,   GPIO,     R,     R,  SPIFI,  UART1, I2S0_TX_SDA,I2S1,  LCD,      0, ND);
LPC_P(3,6,   GPIO,   SPI,  SSP0,  SPIFI,      R,  SSP0_ALT,   R,      R,      0, ND);
LPC_P(3,7,      R,   SPI,  SSP0,  SPIFI,   GPIO,  SSP0_ALT,   R,      R,      0, ND);
LPC_P(3,8,      R,   SPI,  SSP0,  SPIFI,   GPIO,  SSP0_ALT,   R,      R,      0, ND);
LPC_P(4,0,   GPIO, MCTRL,   NMI,      R,      R,    LCD,  UART3,      R,      0, ND);
LPC_P(4,1,   GPIO, CTOUT,   LCD,      R,      R, LCD_ALT, UART3,   ENET, ADC0|1, ND);
LPC_P(4,2,   GPIO, CTOUT,   LCD,      R,      R, LCD_ALT, UART3,  SGPIO,      0, ND);
LPC_P(4,3,   GPIO, CTOUT,   LCD,      R,      R, LCD_ALT, UART3,  SGPIO, ADC0|0, ND);
LPC_P(4,4,   GPIO, CTOUT,   LCD,      R,      R, LCD_ALT, UART3,  SGPIO,    DAC, ND);
LPC_P(4,5,   GPIO, CTOUT,   LCD,      R,      R,      R,      R,  SGPIO,      0, ND);
LPC_P(4,6,   GPIO, CTOUT,   LCD,      R,      R,      R,      R,  SGPIO,      0, ND);
LPC_P(4,7,    LCD, CLKIN,     R,      R,      R,      R,   I2S1,I2S0_TX_SCK,  0, ND);
LPC_P(4,8,      R,  CTIN,   LCD,      R,   GPIO, LCD_ALT,  CAN1,  SGPIO,      0, ND);
LPC_P(4,9,      R,  CTIN,   LCD,      R,   GPIO, LCD_ALT,  CAN1,  SGPIO,      0, ND);
LPC_P(4,10,     R,  CTIN,   LCD,      R,   GPIO, LCD_ALT,     R,  SGPIO,      0, ND);
LPC_P(5,0,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(5,1,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(5,2,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(5,3,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(5,4,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(5,5,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(5,6,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(5,7,   GPIO, MCTRL,   EMC,      R,  UART1, TIMER1,      R,      R,      0, ND);
LPC_P(6,0,      R, I2S0_RX_MCLK,R,    R, I2S0_RX_SCK, R,      R,      R,      0, ND);
LPC_P(6,1,   GPIO,   EMC, UART0, I2S0_RX_WS,  R, TIMER2,      R,      R,      0, ND);
LPC_P(6,2,   GPIO,   EMC, UART0, I2S0_RX_SDA, R, TIMER2,      R,      R,      0, ND);
LPC_P(6,3,   GPIO,  USB0, SGPIO,    EMC,      R, TIMER2,      R,      R,      0, ND);
LPC_P(6,4,   GPIO,  CTIN, UART0,    EMC,      R,      R,      R,      R,      0, ND);
LPC_P(6,5,   GPIO, CTOUT, UART0,    EMC,      R,      R,      R,      R,      0, ND);
LPC_P(6,6,   GPIO,   EMC, SGPIO,   USB0,      R, TIMER2,      R,      R,      0, ND);
LPC_P(6,7,      R,   EMC, SGPIO,   USB0,   GPIO, TIMER2,      R,      R,      0, ND);
LPC_P(6,8,      R,   EMC, SGPIO,   USB0,   GPIO, TIMER2,      R,      R,      0, ND);
LPC_P(6,9,   GPIO,     R,     R,    EMC,      R, TIMER2,      R,      R,      0, ND);
LPC_P(6,10,  GPIO, MCTRL,     R,    EMC,      R,      R,      R,      R,      0, ND);
LPC_P(6,11,  GPIO,     R,     R,    EMC,      R, TIMER2,      R,      R,      0, ND);
LPC_P(6,12,  GPIO, CTOUT,     R,    EMC,      R,      R,      R,      R,      0, ND);
LPC_P(7,0,   GPIO, CTOUT,     R,    LCD,      R,      R,      R,  SGPIO,      0, ND);
LPC_P(7,1,   GPIO, CTOUT,I2S0_TX_WS,LCD,LCD_ALT,      R,  UART2,  SGPIO,      0, ND);
LPC_P(7,2,   GPIO, CTIN,I2S0_TX_SDA,LCD,LCD_ALT,      R,  UART2,  SGPIO,      0, ND);
LPC_P(7,3,   GPIO, CTIN,      R,    LCD,LCD_ALT,      R,      R,      R,      0, ND);
LPC_P(7,4,   GPIO, CTOUT,     R,    LCD,LCD_ALT,  TRACE,      R,      R, ADC0|4, ND);
LPC_P(7,5,   GPIO, CTOUT,     R,    LCD,LCD_ALT,  TRACE,      R,      R, ADC0|3, ND);
LPC_P(7,6,   GPIO, CTOUT,     R,    LCD,      R,  TRACE,      R,      R,      0, ND);
LPC_P(7,7,   GPIO, CTOUT,     R,    LCD,      R,  TRACE,   ENET,  SGPIO, ADC1|6, ND);
LPC_P(8,0,   GPIO,  USB0,     R,  MCTRL,  SGPIO,      R,      R, TIMER0,      0, HD);
LPC_P(8,1,   GPIO,  USB0,     R,  MCTRL,  SGPIO,      R,      R, TIMER0,      0, HD);
LPC_P(8,2,   GPIO,  USB0,     R,  MCTRL,  SGPIO,      R,      R, TIMER0,      0, HD);
LPC_P(8,3,   GPIO,  USB1,     R,    LCD, LCD_ALT,     R,      R, TIMER0,      0, ND);
LPC_P(8,4,   GPIO,  USB1,     R,    LCD, LCD_ALT,     R,      R, TIMER0,      0, ND);
LPC_P(8,5,   GPIO,  USB1,     R,    LCD, LCD_ALT,     R,      R, TIMER0,      0, ND);
LPC_P(8,6,   GPIO,  USB1,     R,    LCD, LCD_ALT,     R,      R, TIMER0,      0, ND);
LPC_P(8,7,   GPIO,  USB1,     R,    LCD, LCD_ALT,     R,      R, TIMER0,      0, ND);
LPC_P(8,8,      R,  USB1,     R,      R,      R,      R,CGU_OUT,   I2S1,      0, ND);
LPC_P(9,0,   GPIO, MCTRL,     R,      R,      R,   ENET,  SGPIO,   SSP0,      0, ND);
LPC_P(9,1,   GPIO, MCTRL,     R,      R, I2S0_TX_WS,ENET, SGPIO,   SSP0,      0, ND);
LPC_P(9,2,   GPIO, MCTRL,     R,      R, I2S0_TX_SDA,ENET,SGPIO,   SSP0,      0, ND);
LPC_P(9,3,   GPIO, MCTRL,  USB1,      R,      R,   ENET,  SGPIO,  UART3,      0, ND);
LPC_P(9,4,      R, MCTRL,  USB1,      R,   GPIO,   ENET,  SGPIO,  UART3,      0, ND);
LPC_P(9,5,      R, MCTRL,  USB1,      R,   GPIO,   ENET,  SGPIO,  UART0,      0, ND);
LPC_P(9,6,   GPIO, MCTRL,  USB1,      R,      R,   ENET,  SGPIO,  UART0,      0, ND);
LPC_P(a,0,      R,     R,     R,      R,      R,   I2S1, CGU_OUT,     R,      0, ND);
LPC_P(a,1,   GPIO,   QEI,     R,  UART2,      R,      R,      R,      R,      0, HD);
LPC_P(a,2,   GPIO,   QEI,     R,  UART2,      R,      R,      R,      R,      0, HD);
LPC_P(a,3,   GPIO,   QEI,     R,      R,      R,      R,      R,      R,      0, HD);
LPC_P(a,4,      R, CTOUT,     R,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(b,0,      R, CTOUT,   LCD,      R,   GPIO,      R,      R,      R,      0, ND);
LPC_P(b,1,      R,  USB1,   LCD,      R,   GPIO,  CTOUT,      R,      R,      0, ND);
LPC_P(b,2,      R,  USB1,   LCD,      R,   GPIO,  CTOUT,      R,      R,      0, ND);
LPC_P(b,3,      R,  USB1,   LCD,      R,   GPIO,  CTOUT,      R,      R,      0, ND);
LPC_P(b,4,      R,  USB1,   LCD,      R,   GPIO,   CTIN,      R,      R,      0, ND);
LPC_P(b,5,      R,  USB1,   LCD,      R,   GPIO,   CTIN, LCD_ALT,     R,      0, ND);
LPC_P(b,6,      R,  USB1,   LCD,      R,   GPIO,   CTIN, LCD_ALT,     R, ADC0|6, ND);
LPC_P(c,0,      R,  USB1,     R,   ENET,    LCD,      R,      R,  SDMMC, ADC1|1, ND);
LPC_P(c,1,   USB1,     R, UART1,   ENET,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,2,   USB1,     R, UART1,   ENET,   GPIO,      R,      R,  SDMMC,      0, ND);
LPC_P(c,3,   USB1,     R, UART1,   ENET,   GPIO,      R,      R,  SDMMC, ADC1|0, ND);
LPC_P(c,4,      R,  USB1,     R,   ENET,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,5,      R,  USB1,     R,   ENET,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,6,      R,  USB1,     R,   ENET,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,7,      R,  USB1,     R,   ENET,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,8,      R,  USB1,     R,   ENET,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,9,      R,  USB1,     R,   ENET,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,10,     R,  USB1, UART1,      R,   GPIO,      R, TIMER3,  SDMMC,      0, ND);
LPC_P(c,11,     R,  USB1, UART1,      R,   GPIO,      R,      R,  SDMMC,      0, ND);
LPC_P(c,12,     R,     R, UART1,      R,   GPIO,  SGPIO, I2S0_TX_SDA,SDMMC,   0, ND);
LPC_P(c,13,     R,     R, UART1,      R,   GPIO,  SGPIO, I2S0_TX_WS, SDMMC,   0, ND);
LPC_P(c,14,     R,     R, UART1,      R,   GPIO,  SGPIO,   ENET,  SDMMC,      0, ND);
LPC_P(d,0,      R, CTOUT,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,1,      R,     R,   EMC,      R,   GPIO,  SDMMC,      R,  SGPIO,      0, ND);
LPC_P(d,2,      R, CTOUT,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,3,      R, CTOUT,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,4,      R, CTOUT,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,5,      R, CTOUT,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,6,      R, CTOUT,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,7,      R,  CTIN,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,8,      R,  CTIN,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,9,      R, CTOUT,   EMC,      R,   GPIO,      R,      R,  SGPIO,      0, ND);
LPC_P(d,10,     R,  CTIN,   EMC,      R,   GPIO,      R,      R,      R,      0, ND);
LPC_P(d,11,     R,     R,   EMC,      R,   GPIO,   USB1,  CTOUT,      R,      0, ND);
LPC_P(d,12,     R,     R,   EMC,      R,   GPIO,      R,  CTOUT,      R,      0, ND);
LPC_P(d,13,     R,  CTIN,   EMC,      R,   GPIO,      R,  CTOUT,      R,      0, ND);
LPC_P(d,14,     R,     R,   EMC,      R,   GPIO,      R,  CTOUT,      R,      0, ND);
LPC_P(d,15,     R,     R,   EMC,      R,   GPIO,  SDMMC,  CTOUT,      R,      0, ND);
LPC_P(d,16,     R,     R,   EMC,      R,   GPIO,  SDMMC,  CTOUT,      R,      0, ND);
LPC_P(e,0,      R,     R,     R,    EMC,   GPIO,   CAN1,      R,      R,      0, ND);
LPC_P(e,1,      R,     R,     R,    EMC,   GPIO,   CAN1,      R,      R,      0, ND);
LPC_P(e,2,ADCTRIG,  CAN0,     R,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,3,      R,  CAN0,ADCTRIG,   EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,4,      R,   NMI,     R,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,5,      R, CTOUT, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,6,      R, CTOUT, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,7,      R, CTOUT, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,8,      R, CTOUT, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,9,      R,  CTIN, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,10,     R,  CTIN, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,11,     R, CTOUT, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,12,     R, CTOUT, UART1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,13,     R, CTOUT,  I2C1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,14,     R,     R,     R,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(e,15,     R, CTOUT,  I2C1,    EMC,   GPIO,      R,      R,      R,      0, ND);
LPC_P(f,0,   SSP0, CLKIN,     R,      R,      R,      R,      R,   I2S1,      0, ND);
LPC_P(f,1,      R,     R,  SSP0,      R,   GPIO,      R,  SGPIO,      R,      0, ND);
LPC_P(f,2,      R, UART3,  SSP0,      R,   GPIO,      R,  SGPIO,      R,      0, ND);
LPC_P(f,3,      R, UART3,  SSP0,      R,   GPIO,      R,  SGPIO,      R,      0, ND);
LPC_P(f,4,   SSP1, CLKIN, TRACE,      R,      R, R, I2S0_TX_MCLK,I2S0_RX_SCK, 0, ND);
LPC_P(f,5,      R, UART3,  SSP1,  TRACE,   GPIO,      R,  SGPIO,      R, ADC1|4, ND);
LPC_P(f,6,      R, UART3,  SSP1,  TRACE,   GPIO,      R,  SGPIO,   I2S1, ADC1|3, ND);
LPC_P(f,7,      R, UART3,  SSP1,  TRACE,   GPIO,      R,  SGPIO,   I2S1, ADC1|7, ND);
LPC_P(f,8,      R, UART0,  CTIN,  TRACE,   GPIO,      R,  SGPIO,      R, ADC0|2, ND);
LPC_P(f,9,      R, UART0, CTOUT,      R,   GPIO,      R,  SGPIO,      R, ADC1|2, ND);
LPC_P(f,10,     R, UART0,     R,      R,   GPIO,      R,  SDMMC,      R, ADC0|5, ND);
LPC_P(f,11,     R, UART0,     R,      R,   GPIO,      R,  SDMMC,      R, ADC1|5, ND);

/*    Pin      Offset FUNC0  FUNC1  FUNC2  FUNC3  FUNC4    FUNC5   FUNC6      FUNC7 ANALOG TYPE */
LPC_N(clk0,     0xc00, EMC, CLKOUT,   R,     R,  SDMMC,   EMC_ALT,  SSP1,      ENET,  0, HS);
LPC_N(clk1,     0xc04, EMC, CLKOUT,   R,     R,      R,   CGU_OUT,   R,        I2S1,  0, HS);
LPC_N(clk2,     0xc08, EMC, CLKOUT,   R,     R,  SDMMC,   EMC_ALT,I2S0_TX_MCLK,I2S1,  0, HS);
LPC_N(clk3,     0xc0c, EMC, CLKOUT,   R,     R,      R,   CGU_OUT,   R,        I2S1,  0, HS);
LPC_N(usb1_dm,  0xc80, R,      R,     R,     R,      R,      R,      R,          R,   0, USB1);
LPC_N(usb1_dp,  0xc80, R,      R,     R,     R,      R,      R,      R,          R,   0, USB1);
LPC_N(i2c0_scl, 0xc84, R,      R,     R,     R,      R,      R,      R,          R,   0, I2C0);
LPC_N(i2c0_sda, 0xc84, R,      R,     R,     R,      R,      R,      R,          R,   0, I2C0);

#घोषणा LPC18XX_PIN_P(port, pin) अणु			\
	.number = 0x##port * 32 + pin,			\
	.name = "p"#port"_"#pin,			\
	.drv_data = &lpc18xx_pin_p##port##_##pin 	\
पूर्ण

/* Pin numbers क्रम special pins */
क्रमागत अणु
	PIN_CLK0 = 600,
	PIN_CLK1,
	PIN_CLK2,
	PIN_CLK3,
	PIN_USB1_DM,
	PIN_USB1_DP,
	PIN_I2C0_SCL,
	PIN_I2C0_SDA,
पूर्ण;

#घोषणा LPC18XX_PIN(pname, n) अणु				\
	.number = n,					\
	.name = #pname,					\
	.drv_data = &lpc18xx_pin_##pname 		\
पूर्ण

अटल स्थिर काष्ठा pinctrl_pin_desc lpc18xx_pins[] = अणु
	LPC18XX_PIN_P(0,0),
	LPC18XX_PIN_P(0,1),
	LPC18XX_PIN_P(1,0),
	LPC18XX_PIN_P(1,1),
	LPC18XX_PIN_P(1,2),
	LPC18XX_PIN_P(1,3),
	LPC18XX_PIN_P(1,4),
	LPC18XX_PIN_P(1,5),
	LPC18XX_PIN_P(1,6),
	LPC18XX_PIN_P(1,7),
	LPC18XX_PIN_P(1,8),
	LPC18XX_PIN_P(1,9),
	LPC18XX_PIN_P(1,10),
	LPC18XX_PIN_P(1,11),
	LPC18XX_PIN_P(1,12),
	LPC18XX_PIN_P(1,13),
	LPC18XX_PIN_P(1,14),
	LPC18XX_PIN_P(1,15),
	LPC18XX_PIN_P(1,16),
	LPC18XX_PIN_P(1,17),
	LPC18XX_PIN_P(1,18),
	LPC18XX_PIN_P(1,19),
	LPC18XX_PIN_P(1,20),
	LPC18XX_PIN_P(2,0),
	LPC18XX_PIN_P(2,1),
	LPC18XX_PIN_P(2,2),
	LPC18XX_PIN_P(2,3),
	LPC18XX_PIN_P(2,4),
	LPC18XX_PIN_P(2,5),
	LPC18XX_PIN_P(2,6),
	LPC18XX_PIN_P(2,7),
	LPC18XX_PIN_P(2,8),
	LPC18XX_PIN_P(2,9),
	LPC18XX_PIN_P(2,10),
	LPC18XX_PIN_P(2,11),
	LPC18XX_PIN_P(2,12),
	LPC18XX_PIN_P(2,13),
	LPC18XX_PIN_P(3,0),
	LPC18XX_PIN_P(3,1),
	LPC18XX_PIN_P(3,2),
	LPC18XX_PIN_P(3,3),
	LPC18XX_PIN_P(3,4),
	LPC18XX_PIN_P(3,5),
	LPC18XX_PIN_P(3,6),
	LPC18XX_PIN_P(3,7),
	LPC18XX_PIN_P(3,8),
	LPC18XX_PIN_P(4,0),
	LPC18XX_PIN_P(4,1),
	LPC18XX_PIN_P(4,2),
	LPC18XX_PIN_P(4,3),
	LPC18XX_PIN_P(4,4),
	LPC18XX_PIN_P(4,5),
	LPC18XX_PIN_P(4,6),
	LPC18XX_PIN_P(4,7),
	LPC18XX_PIN_P(4,8),
	LPC18XX_PIN_P(4,9),
	LPC18XX_PIN_P(4,10),
	LPC18XX_PIN_P(5,0),
	LPC18XX_PIN_P(5,1),
	LPC18XX_PIN_P(5,2),
	LPC18XX_PIN_P(5,3),
	LPC18XX_PIN_P(5,4),
	LPC18XX_PIN_P(5,5),
	LPC18XX_PIN_P(5,6),
	LPC18XX_PIN_P(5,7),
	LPC18XX_PIN_P(6,0),
	LPC18XX_PIN_P(6,1),
	LPC18XX_PIN_P(6,2),
	LPC18XX_PIN_P(6,3),
	LPC18XX_PIN_P(6,4),
	LPC18XX_PIN_P(6,5),
	LPC18XX_PIN_P(6,6),
	LPC18XX_PIN_P(6,7),
	LPC18XX_PIN_P(6,8),
	LPC18XX_PIN_P(6,9),
	LPC18XX_PIN_P(6,10),
	LPC18XX_PIN_P(6,11),
	LPC18XX_PIN_P(6,12),
	LPC18XX_PIN_P(7,0),
	LPC18XX_PIN_P(7,1),
	LPC18XX_PIN_P(7,2),
	LPC18XX_PIN_P(7,3),
	LPC18XX_PIN_P(7,4),
	LPC18XX_PIN_P(7,5),
	LPC18XX_PIN_P(7,6),
	LPC18XX_PIN_P(7,7),
	LPC18XX_PIN_P(8,0),
	LPC18XX_PIN_P(8,1),
	LPC18XX_PIN_P(8,2),
	LPC18XX_PIN_P(8,3),
	LPC18XX_PIN_P(8,4),
	LPC18XX_PIN_P(8,5),
	LPC18XX_PIN_P(8,6),
	LPC18XX_PIN_P(8,7),
	LPC18XX_PIN_P(8,8),
	LPC18XX_PIN_P(9,0),
	LPC18XX_PIN_P(9,1),
	LPC18XX_PIN_P(9,2),
	LPC18XX_PIN_P(9,3),
	LPC18XX_PIN_P(9,4),
	LPC18XX_PIN_P(9,5),
	LPC18XX_PIN_P(9,6),
	LPC18XX_PIN_P(a,0),
	LPC18XX_PIN_P(a,1),
	LPC18XX_PIN_P(a,2),
	LPC18XX_PIN_P(a,3),
	LPC18XX_PIN_P(a,4),
	LPC18XX_PIN_P(b,0),
	LPC18XX_PIN_P(b,1),
	LPC18XX_PIN_P(b,2),
	LPC18XX_PIN_P(b,3),
	LPC18XX_PIN_P(b,4),
	LPC18XX_PIN_P(b,5),
	LPC18XX_PIN_P(b,6),
	LPC18XX_PIN_P(c,0),
	LPC18XX_PIN_P(c,1),
	LPC18XX_PIN_P(c,2),
	LPC18XX_PIN_P(c,3),
	LPC18XX_PIN_P(c,4),
	LPC18XX_PIN_P(c,5),
	LPC18XX_PIN_P(c,6),
	LPC18XX_PIN_P(c,7),
	LPC18XX_PIN_P(c,8),
	LPC18XX_PIN_P(c,9),
	LPC18XX_PIN_P(c,10),
	LPC18XX_PIN_P(c,11),
	LPC18XX_PIN_P(c,12),
	LPC18XX_PIN_P(c,13),
	LPC18XX_PIN_P(c,14),
	LPC18XX_PIN_P(d,0),
	LPC18XX_PIN_P(d,1),
	LPC18XX_PIN_P(d,2),
	LPC18XX_PIN_P(d,3),
	LPC18XX_PIN_P(d,4),
	LPC18XX_PIN_P(d,5),
	LPC18XX_PIN_P(d,6),
	LPC18XX_PIN_P(d,7),
	LPC18XX_PIN_P(d,8),
	LPC18XX_PIN_P(d,9),
	LPC18XX_PIN_P(d,10),
	LPC18XX_PIN_P(d,11),
	LPC18XX_PIN_P(d,12),
	LPC18XX_PIN_P(d,13),
	LPC18XX_PIN_P(d,14),
	LPC18XX_PIN_P(d,15),
	LPC18XX_PIN_P(d,16),
	LPC18XX_PIN_P(e,0),
	LPC18XX_PIN_P(e,1),
	LPC18XX_PIN_P(e,2),
	LPC18XX_PIN_P(e,3),
	LPC18XX_PIN_P(e,4),
	LPC18XX_PIN_P(e,5),
	LPC18XX_PIN_P(e,6),
	LPC18XX_PIN_P(e,7),
	LPC18XX_PIN_P(e,8),
	LPC18XX_PIN_P(e,9),
	LPC18XX_PIN_P(e,10),
	LPC18XX_PIN_P(e,11),
	LPC18XX_PIN_P(e,12),
	LPC18XX_PIN_P(e,13),
	LPC18XX_PIN_P(e,14),
	LPC18XX_PIN_P(e,15),
	LPC18XX_PIN_P(f,0),
	LPC18XX_PIN_P(f,1),
	LPC18XX_PIN_P(f,2),
	LPC18XX_PIN_P(f,3),
	LPC18XX_PIN_P(f,4),
	LPC18XX_PIN_P(f,5),
	LPC18XX_PIN_P(f,6),
	LPC18XX_PIN_P(f,7),
	LPC18XX_PIN_P(f,8),
	LPC18XX_PIN_P(f,9),
	LPC18XX_PIN_P(f,10),
	LPC18XX_PIN_P(f,11),

	LPC18XX_PIN(clk0, PIN_CLK0),
	LPC18XX_PIN(clk1, PIN_CLK1),
	LPC18XX_PIN(clk2, PIN_CLK2),
	LPC18XX_PIN(clk3, PIN_CLK3),
	LPC18XX_PIN(usb1_dm,  PIN_USB1_DM),
	LPC18XX_PIN(usb1_dp,  PIN_USB1_DP),
	LPC18XX_PIN(i2c0_scl, PIN_I2C0_SCL),
	LPC18XX_PIN(i2c0_sda, PIN_I2C0_SDA),
पूर्ण;

/* PIN_CONFIG_GPIO_PIN_INT: route gpio to the gpio pin पूर्णांकerrupt controller */
#घोषणा PIN_CONFIG_GPIO_PIN_INT		(PIN_CONFIG_END + 1)

अटल स्थिर काष्ठा pinconf_generic_params lpc18xx_params[] = अणु
	अणु"nxp,gpio-pin-interrupt", PIN_CONFIG_GPIO_PIN_INT, 0पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर काष्ठा pin_config_item lpc18xx_conf_items[ARRAY_SIZE(lpc18xx_params)] = अणु
	PCONFDUMP(PIN_CONFIG_GPIO_PIN_INT, "gpio pin int", शून्य, true),
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक lpc18xx_pconf_get_usb1(क्रमागत pin_config_param param, पूर्णांक *arg, u32 reg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_MODE_LOW_POWER:
		अगर (reg & LPC18XX_SCU_USB1_EPWR)
			*arg = 0;
		अन्यथा
			*arg = 1;
		अवरोध;

	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (reg & LPC18XX_SCU_USB1_EPD)
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (reg & LPC18XX_SCU_USB1_EPD)
			*arg = 1;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pconf_get_i2c0(क्रमागत pin_config_param param, पूर्णांक *arg, u32 reg,
				  अचिन्हित pin)
अणु
	u8 shअगरt;

	अगर (pin == PIN_I2C0_SCL)
		shअगरt = LPC18XX_SCU_I2C0_SCL_SHIFT;
	अन्यथा
		shअगरt = LPC18XX_SCU_I2C0_SDA_SHIFT;

	चयन (param) अणु
	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (reg & (LPC18XX_SCU_I2C0_EZI << shअगरt))
			*arg = 1;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_SLEW_RATE:
		अगर (reg & (LPC18XX_SCU_I2C0_EHD << shअगरt))
			*arg = 1;
		अन्यथा
			*arg = 0;
		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT:
		अगर (reg & (LPC18XX_SCU_I2C0_EFP << shअगरt))
			*arg = 3;
		अन्यथा
			*arg = 50;
		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (reg & (LPC18XX_SCU_I2C0_ZIF << shअगरt))
			वापस -EINVAL;
		अन्यथा
			*arg = 1;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pin_to_gpio(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin)
अणु
	काष्ठा pinctrl_gpio_range *range;

	range = pinctrl_find_gpio_range_from_pin_nolock(pctldev, pin);
	अगर (!range)
		वापस -EINVAL;

	वापस pin - range->pin_base + range->base;
पूर्ण

अटल पूर्णांक lpc18xx_get_pपूर्णांकsel(व्योम __iomem *addr, u32 val, पूर्णांक *arg)
अणु
	u32 reg_val;
	पूर्णांक i;

	reg_val = पढ़ोl(addr);
	क्रम (i = 0; i < LPC18XX_SCU_IRQ_PER_PINTSEL; i++) अणु
		अगर ((reg_val & LPC18XX_SCU_PINTSEL_VAL_MASK) == val)
			वापस 0;

		reg_val >>= BITS_PER_BYTE;
		*arg += 1;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल u32 lpc18xx_gpio_to_pपूर्णांकsel_val(पूर्णांक gpio)
अणु
	अचिन्हित पूर्णांक gpio_port, gpio_pin;

	gpio_port = gpio / LPC18XX_GPIO_PINS_PER_PORT;
	gpio_pin  = gpio % LPC18XX_GPIO_PINS_PER_PORT;

	वापस gpio_pin | (gpio_port << LPC18XX_SCU_PINTSEL_PORT_SHIFT);
पूर्ण

अटल पूर्णांक lpc18xx_pconf_get_gpio_pin_पूर्णांक(काष्ठा pinctrl_dev *pctldev,
					  पूर्णांक *arg, अचिन्हित pin)
अणु
	काष्ठा lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक gpio, ret;
	u32 val;

	gpio = lpc18xx_pin_to_gpio(pctldev, pin);
	अगर (gpio < 0)
		वापस -ENOTSUPP;

	val = lpc18xx_gpio_to_pपूर्णांकsel_val(gpio);

	/*
	 * Check अगर this pin has been enabled as a पूर्णांकerrupt in any of the two
	 * PINTSEL रेजिस्टरs. *arg indicates which पूर्णांकerrupt number (0-7).
	 */
	*arg = 0;
	ret = lpc18xx_get_pपूर्णांकsel(scu->base + LPC18XX_SCU_PINTSEL0, val, arg);
	अगर (ret == 0)
		वापस ret;

	वापस lpc18xx_get_pपूर्णांकsel(scu->base + LPC18XX_SCU_PINTSEL1, val, arg);
पूर्ण

अटल पूर्णांक lpc18xx_pconf_get_pin(काष्ठा pinctrl_dev *pctldev, अचिन्हित param,
				 पूर्णांक *arg, u32 reg, अचिन्हित pin,
				 काष्ठा lpc18xx_pin_caps *pin_cap)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर ((!(reg & LPC18XX_SCU_PIN_EPD)) && (reg & LPC18XX_SCU_PIN_EPUN))
			;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (reg & LPC18XX_SCU_PIN_EPUN)
			वापस -EINVAL;
		अन्यथा
			*arg = 1;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (reg & LPC18XX_SCU_PIN_EPD)
			*arg = 1;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (reg & LPC18XX_SCU_PIN_EZI)
			*arg = 1;
		अन्यथा
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_SLEW_RATE:
		अगर (pin_cap->type == TYPE_HD)
			वापस -ENOTSUPP;

		अगर (reg & LPC18XX_SCU_PIN_EHS)
			*arg = 1;
		अन्यथा
			*arg = 0;
		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (reg & LPC18XX_SCU_PIN_ZIF)
			वापस -EINVAL;
		अन्यथा
			*arg = 1;
		अवरोध;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		अगर (pin_cap->type != TYPE_HD)
			वापस -ENOTSUPP;

		*arg = (reg & LPC18XX_SCU_PIN_EHD_MASK) >> LPC18XX_SCU_PIN_EHD_POS;
		चयन (*arg) अणु
		हाल 3: *arg += 5;
			fallthrough;
		हाल 2: *arg += 5;
			fallthrough;
		हाल 1: *arg += 3;
			fallthrough;
		हाल 0: *arg += 4;
		पूर्ण
		अवरोध;

	हाल PIN_CONFIG_GPIO_PIN_INT:
		वापस lpc18xx_pconf_get_gpio_pin_पूर्णांक(pctldev, arg, pin);

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा lpc18xx_pin_caps *lpc18xx_get_pin_caps(अचिन्हित pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lpc18xx_pins); i++) अणु
		अगर (lpc18xx_pins[i].number == pin)
			वापस lpc18xx_pins[i].drv_data;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक lpc18xx_pconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			     अचिन्हित दीर्घ *config)
अणु
	काष्ठा lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	काष्ठा lpc18xx_pin_caps *pin_cap;
	पूर्णांक ret, arg = 0;
	u32 reg;

	pin_cap = lpc18xx_get_pin_caps(pin);
	अगर (!pin_cap)
		वापस -EINVAL;

	reg = पढ़ोl(scu->base + pin_cap->offset);

	अगर (pin_cap->type == TYPE_I2C0)
		ret = lpc18xx_pconf_get_i2c0(param, &arg, reg, pin);
	अन्यथा अगर (pin_cap->type == TYPE_USB1)
		ret = lpc18xx_pconf_get_usb1(param, &arg, reg);
	अन्यथा
		ret = lpc18xx_pconf_get_pin(pctldev, param, &arg, reg, pin, pin_cap);

	अगर (ret < 0)
		वापस ret;

	*config = pinconf_to_config_packed(param, (u16)arg);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pconf_set_usb1(काष्ठा pinctrl_dev *pctldev,
				  क्रमागत pin_config_param param,
				  u32 param_val, u32 *reg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_MODE_LOW_POWER:
		अगर (param_val)
			*reg &= ~LPC18XX_SCU_USB1_EPWR;
		अन्यथा
			*reg |= LPC18XX_SCU_USB1_EPWR;
		अवरोध;

	हाल PIN_CONFIG_BIAS_DISABLE:
		*reg &= ~LPC18XX_SCU_USB1_EPD;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		*reg |= LPC18XX_SCU_USB1_EPD;
		अवरोध;

	शेष:
		dev_err(pctldev->dev, "Property not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pconf_set_i2c0(काष्ठा pinctrl_dev *pctldev,
				  क्रमागत pin_config_param param,
				  u32 param_val, u32 *reg,
				  अचिन्हित pin)
अणु
	u8 shअगरt;

	अगर (pin == PIN_I2C0_SCL)
		shअगरt = LPC18XX_SCU_I2C0_SCL_SHIFT;
	अन्यथा
		shअगरt = LPC18XX_SCU_I2C0_SDA_SHIFT;

	चयन (param) अणु
	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (param_val)
			*reg |= (LPC18XX_SCU_I2C0_EZI << shअगरt);
		अन्यथा
			*reg &= ~(LPC18XX_SCU_I2C0_EZI << shअगरt);
		अवरोध;

	हाल PIN_CONFIG_SLEW_RATE:
		अगर (param_val)
			*reg |= (LPC18XX_SCU_I2C0_EHD << shअगरt);
		अन्यथा
			*reg &= ~(LPC18XX_SCU_I2C0_EHD << shअगरt);
		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT:
		अगर (param_val == 3)
			*reg |= (LPC18XX_SCU_I2C0_EFP << shअगरt);
		अन्यथा अगर (param_val == 50)
			*reg &= ~(LPC18XX_SCU_I2C0_EFP << shअगरt);
		अन्यथा
			वापस -ENOTSUPP;
		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (param_val)
			*reg &= ~(LPC18XX_SCU_I2C0_ZIF << shअगरt);
		अन्यथा
			*reg |= (LPC18XX_SCU_I2C0_ZIF << shअगरt);
		अवरोध;

	शेष:
		dev_err(pctldev->dev, "Property not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pconf_set_gpio_pin_पूर्णांक(काष्ठा pinctrl_dev *pctldev,
					  u32 param_val, अचिन्हित pin)
अणु
	काष्ठा lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);
	u32 val, reg_val, reg_offset = LPC18XX_SCU_PINTSEL0;
	पूर्णांक gpio;

	अगर (param_val >= LPC18XX_GPIO_PIN_पूर्णांक_उच्च)
		वापस -EINVAL;

	gpio = lpc18xx_pin_to_gpio(pctldev, pin);
	अगर (gpio < 0)
		वापस -ENOTSUPP;

	val = lpc18xx_gpio_to_pपूर्णांकsel_val(gpio);

	reg_offset += (param_val / LPC18XX_SCU_IRQ_PER_PINTSEL) * माप(u32);

	reg_val = पढ़ोl(scu->base + reg_offset);
	reg_val &= ~LPC18XX_SCU_PINTSEL_VAL(LPC18XX_SCU_PINTSEL_VAL_MASK, param_val);
	reg_val |= LPC18XX_SCU_PINTSEL_VAL(val, param_val);
	ग_लिखोl(reg_val, scu->base + reg_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pconf_set_pin(काष्ठा pinctrl_dev *pctldev, अचिन्हित param,
				 u32 param_val, u32 *reg, अचिन्हित pin,
				 काष्ठा lpc18xx_pin_caps *pin_cap)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		*reg &= ~LPC18XX_SCU_PIN_EPD;
		*reg |= LPC18XX_SCU_PIN_EPUN;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		*reg &= ~LPC18XX_SCU_PIN_EPUN;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		*reg |= LPC18XX_SCU_PIN_EPD;
		अवरोध;

	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (param_val)
			*reg |= LPC18XX_SCU_PIN_EZI;
		अन्यथा
			*reg &= ~LPC18XX_SCU_PIN_EZI;
		अवरोध;

	हाल PIN_CONFIG_SLEW_RATE:
		अगर (pin_cap->type == TYPE_HD) अणु
			dev_err(pctldev->dev, "Slew rate unsupported on high-drive pins\n");
			वापस -ENOTSUPP;
		पूर्ण

		अगर (param_val == 0)
			*reg &= ~LPC18XX_SCU_PIN_EHS;
		अन्यथा
			*reg |= LPC18XX_SCU_PIN_EHS;
		अवरोध;

	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (param_val)
			*reg &= ~LPC18XX_SCU_PIN_ZIF;
		अन्यथा
			*reg |= LPC18XX_SCU_PIN_ZIF;
		अवरोध;

	हाल PIN_CONFIG_DRIVE_STRENGTH:
		अगर (pin_cap->type != TYPE_HD) अणु
			dev_err(pctldev->dev, "Drive strength available only on high-drive pins\n");
			वापस -ENOTSUPP;
		पूर्ण
		*reg &= ~LPC18XX_SCU_PIN_EHD_MASK;

		चयन (param_val) अणु
		हाल 20: param_val -= 5;
			fallthrough;
		हाल 14: param_val -= 5;
			fallthrough;
		हाल  8: param_val -= 3;
			fallthrough;
		हाल  4: param_val -= 4;
			 अवरोध;
		शेष:
			dev_err(pctldev->dev, "Drive strength %u unsupported\n", param_val);
			वापस -ENOTSUPP;
		पूर्ण
		*reg |= param_val << LPC18XX_SCU_PIN_EHD_POS;
		अवरोध;

	हाल PIN_CONFIG_GPIO_PIN_INT:
		वापस lpc18xx_pconf_set_gpio_pin_पूर्णांक(pctldev, param_val, pin);

	शेष:
		dev_err(pctldev->dev, "Property not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			     अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा lpc18xx_pin_caps *pin_cap;
	क्रमागत pin_config_param param;
	u32 param_val;
	u32 reg;
	पूर्णांक ret;
	पूर्णांक i;

	pin_cap = lpc18xx_get_pin_caps(pin);
	अगर (!pin_cap)
		वापस -EINVAL;

	reg = पढ़ोl(scu->base + pin_cap->offset);

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		param_val = pinconf_to_config_argument(configs[i]);

		अगर (pin_cap->type == TYPE_I2C0)
			ret = lpc18xx_pconf_set_i2c0(pctldev, param, param_val, &reg, pin);
		अन्यथा अगर (pin_cap->type == TYPE_USB1)
			ret = lpc18xx_pconf_set_usb1(pctldev, param, param_val, &reg);
		अन्यथा
			ret = lpc18xx_pconf_set_pin(pctldev, param, param_val, &reg, pin, pin_cap);

		अगर (ret)
			वापस ret;
	पूर्ण

	ग_लिखोl(reg, scu->base + pin_cap->offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops lpc18xx_pconf_ops = अणु
	.is_generic	= true,
	.pin_config_get	= lpc18xx_pconf_get,
	.pin_config_set	= lpc18xx_pconf_set,
पूर्ण;

अटल पूर्णांक lpc18xx_pmx_get_funcs_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(lpc18xx_function_names);
पूर्ण

अटल स्थिर अक्षर *lpc18xx_pmx_get_func_name(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित function)
अणु
	वापस lpc18xx_function_names[function];
पूर्ण

अटल पूर्णांक lpc18xx_pmx_get_func_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित function,
				       स्थिर अक्षर *स्थिर **groups,
				       अचिन्हित *स्थिर num_groups)
अणु
	काष्ठा lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);

	*groups  = scu->func[function].groups;
	*num_groups = scu->func[function].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_pmx_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित function,
			   अचिन्हित group)
अणु
	काष्ठा lpc18xx_scu_data *scu = pinctrl_dev_get_drvdata(pctldev);
	काष्ठा lpc18xx_pin_caps *pin = lpc18xx_pins[group].drv_data;
	पूर्णांक func;
	u32 reg;

	/* Dedicated USB1 and I2C0 pins करोesn't support muxing */
	अगर (pin->type == TYPE_USB1) अणु
		अगर (function == FUNC_USB1)
			वापस 0;

		जाओ fail;
	पूर्ण

	अगर (pin->type == TYPE_I2C0) अणु
		अगर (function == FUNC_I2C0)
			वापस 0;

		जाओ fail;
	पूर्ण

	अगर (function == FUNC_ADC && (pin->analog & LPC18XX_ANALOG_PIN)) अणु
		u32 offset;

		ग_लिखोl(LPC18XX_SCU_ANALOG_PIN_CFG, scu->base + pin->offset);

		अगर (LPC18XX_ANALOG_ADC(pin->analog) == 0)
			offset = LPC18XX_SCU_REG_ENAIO0;
		अन्यथा
			offset = LPC18XX_SCU_REG_ENAIO1;

		reg = पढ़ोl(scu->base + offset);
		reg |= pin->analog & LPC18XX_ANALOG_BIT_MASK;
		ग_लिखोl(reg, scu->base + offset);

		वापस 0;
	पूर्ण

	अगर (function == FUNC_DAC && (pin->analog & LPC18XX_ANALOG_PIN)) अणु
		ग_लिखोl(LPC18XX_SCU_ANALOG_PIN_CFG, scu->base + pin->offset);

		reg = पढ़ोl(scu->base + LPC18XX_SCU_REG_ENAIO2);
		reg |= LPC18XX_SCU_REG_ENAIO2_DAC;
		ग_लिखोl(reg, scu->base + LPC18XX_SCU_REG_ENAIO2);

		वापस 0;
	पूर्ण

	क्रम (func = 0; func < LPC18XX_SCU_FUNC_PER_PIN; func++) अणु
		अगर (function == pin->functions[func])
			अवरोध;
	पूर्ण

	अगर (func >= LPC18XX_SCU_FUNC_PER_PIN)
		जाओ fail;

	reg = पढ़ोl(scu->base + pin->offset);
	reg &= ~LPC18XX_SCU_PIN_MODE_MASK;
	ग_लिखोl(reg | func, scu->base + pin->offset);

	वापस 0;
fail:
	dev_err(pctldev->dev, "Pin %s can't be %s\n", lpc18xx_pins[group].name,
						      lpc18xx_function_names[function]);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops lpc18xx_pmx_ops = अणु
	.get_functions_count	= lpc18xx_pmx_get_funcs_count,
	.get_function_name	= lpc18xx_pmx_get_func_name,
	.get_function_groups	= lpc18xx_pmx_get_func_groups,
	.set_mux		= lpc18xx_pmx_set,
पूर्ण;

अटल पूर्णांक lpc18xx_pctl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(lpc18xx_pins);
पूर्ण

अटल स्थिर अक्षर *lpc18xx_pctl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित group)
अणु
	वापस lpc18xx_pins[group].name;
पूर्ण

अटल पूर्णांक lpc18xx_pctl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित group,
				       स्थिर अचिन्हित **pins,
				       अचिन्हित *num_pins)
अणु
	*pins = &lpc18xx_pins[group].number;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops lpc18xx_pctl_ops = अणु
	.get_groups_count	= lpc18xx_pctl_get_groups_count,
	.get_group_name		= lpc18xx_pctl_get_group_name,
	.get_group_pins		= lpc18xx_pctl_get_group_pins,
	.dt_node_to_map		= pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map		= pinctrl_utils_मुक्त_map,
पूर्ण;

अटल काष्ठा pinctrl_desc lpc18xx_scu_desc = अणु
	.name = "lpc18xx/43xx-scu",
	.pins = lpc18xx_pins,
	.npins = ARRAY_SIZE(lpc18xx_pins),
	.pctlops = &lpc18xx_pctl_ops,
	.pmxops = &lpc18xx_pmx_ops,
	.confops = &lpc18xx_pconf_ops,
	.num_custom_params = ARRAY_SIZE(lpc18xx_params),
	.custom_params = lpc18xx_params,
#अगर_घोषित CONFIG_DEBUG_FS
	.custom_conf_items = lpc18xx_conf_items,
#पूर्ण_अगर
	.owner = THIS_MODULE,
पूर्ण;

अटल bool lpc18xx_valid_pin_function(अचिन्हित pin, अचिन्हित function)
अणु
	काष्ठा lpc18xx_pin_caps *p = lpc18xx_pins[pin].drv_data;
	पूर्णांक i;

	अगर (function == FUNC_DAC && p->analog == DAC)
		वापस true;

	अगर (function == FUNC_ADC && p->analog)
		वापस true;

	अगर (function == FUNC_I2C0 && p->type == TYPE_I2C0)
		वापस true;

	अगर (function == FUNC_USB1 && p->type == TYPE_USB1)
		वापस true;

	क्रम (i = 0; i < LPC18XX_SCU_FUNC_PER_PIN; i++) अणु
		अगर (function == p->functions[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक lpc18xx_create_group_func_map(काष्ठा device *dev,
					 काष्ठा lpc18xx_scu_data *scu)
अणु
	u16 pins[ARRAY_SIZE(lpc18xx_pins)];
	पूर्णांक func, ngroups, i;

	क्रम (func = 0; func < FUNC_MAX; func++) अणु
		क्रम (ngroups = 0, i = 0; i < ARRAY_SIZE(lpc18xx_pins); i++) अणु
			अगर (lpc18xx_valid_pin_function(i, func))
				pins[ngroups++] = i;
		पूर्ण

		scu->func[func].ngroups = ngroups;
		scu->func[func].groups = devm_kसुस्मृति(dev,
						      ngroups, माप(अक्षर *),
						      GFP_KERNEL);
		अगर (!scu->func[func].groups)
			वापस -ENOMEM;

		क्रम (i = 0; i < ngroups; i++)
			scu->func[func].groups[i] = lpc18xx_pins[pins[i]].name;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_scu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc18xx_scu_data *scu;
	पूर्णांक ret;

	scu = devm_kzalloc(&pdev->dev, माप(*scu), GFP_KERNEL);
	अगर (!scu)
		वापस -ENOMEM;

	scu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(scu->base))
		वापस PTR_ERR(scu->base);

	scu->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(scu->clk)) अणु
		dev_err(&pdev->dev, "Input clock not found.\n");
		वापस PTR_ERR(scu->clk);
	पूर्ण

	ret = lpc18xx_create_group_func_map(&pdev->dev, scu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to create group func map.\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(scu->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to enable clock.\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, scu);

	scu->pctl = devm_pinctrl_रेजिस्टर(&pdev->dev, &lpc18xx_scu_desc, scu);
	अगर (IS_ERR(scu->pctl)) अणु
		dev_err(&pdev->dev, "Could not register pinctrl driver\n");
		clk_disable_unprepare(scu->clk);
		वापस PTR_ERR(scu->pctl);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_scu_match[] = अणु
	अणु .compatible = "nxp,lpc1850-scu" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver lpc18xx_scu_driver = अणु
	.probe		= lpc18xx_scu_probe,
	.driver = अणु
		.name		= "lpc18xx-scu",
		.of_match_table	= lpc18xx_scu_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(lpc18xx_scu_driver);
