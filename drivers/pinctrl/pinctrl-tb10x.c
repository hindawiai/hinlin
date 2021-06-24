<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Abilis Systems TB10x pin control driver
 *
 * Copyright (C) Abilis Systems 2012
 *
 * Author: Christian Ruppert <christian.ruppert@abilis.com>
 */

#समावेश <linux/stringअगरy.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश "pinctrl-utils.h"

#घोषणा TB10X_PORT1 (0)
#घोषणा TB10X_PORT2 (16)
#घोषणा TB10X_PORT3 (32)
#घोषणा TB10X_PORT4 (48)
#घोषणा TB10X_PORT5 (128)
#घोषणा TB10X_PORT6 (64)
#घोषणा TB10X_PORT7 (80)
#घोषणा TB10X_PORT8 (96)
#घोषणा TB10X_PORT9 (112)
#घोषणा TB10X_GPIOS (256)

#घोषणा PCFG_PORT_BITWIDTH (2)
#घोषणा PCFG_PORT_MASK(PORT) \
	(((1 << PCFG_PORT_BITWIDTH) - 1) << (PCFG_PORT_BITWIDTH * (PORT)))

अटल स्थिर काष्ठा pinctrl_pin_desc tb10x_pins[] = अणु
	/* Port 1 */
	PINCTRL_PIN(TB10X_PORT1 +  0, "MICLK_S0"),
	PINCTRL_PIN(TB10X_PORT1 +  1, "MISTRT_S0"),
	PINCTRL_PIN(TB10X_PORT1 +  2, "MIVAL_S0"),
	PINCTRL_PIN(TB10X_PORT1 +  3, "MDI_S0"),
	PINCTRL_PIN(TB10X_PORT1 +  4, "GPIOA0"),
	PINCTRL_PIN(TB10X_PORT1 +  5, "GPIOA1"),
	PINCTRL_PIN(TB10X_PORT1 +  6, "GPIOA2"),
	PINCTRL_PIN(TB10X_PORT1 +  7, "MDI_S1"),
	PINCTRL_PIN(TB10X_PORT1 +  8, "MIVAL_S1"),
	PINCTRL_PIN(TB10X_PORT1 +  9, "MISTRT_S1"),
	PINCTRL_PIN(TB10X_PORT1 + 10, "MICLK_S1"),
	/* Port 2 */
	PINCTRL_PIN(TB10X_PORT2 +  0, "MICLK_S2"),
	PINCTRL_PIN(TB10X_PORT2 +  1, "MISTRT_S2"),
	PINCTRL_PIN(TB10X_PORT2 +  2, "MIVAL_S2"),
	PINCTRL_PIN(TB10X_PORT2 +  3, "MDI_S2"),
	PINCTRL_PIN(TB10X_PORT2 +  4, "GPIOC0"),
	PINCTRL_PIN(TB10X_PORT2 +  5, "GPIOC1"),
	PINCTRL_PIN(TB10X_PORT2 +  6, "GPIOC2"),
	PINCTRL_PIN(TB10X_PORT2 +  7, "MDI_S3"),
	PINCTRL_PIN(TB10X_PORT2 +  8, "MIVAL_S3"),
	PINCTRL_PIN(TB10X_PORT2 +  9, "MISTRT_S3"),
	PINCTRL_PIN(TB10X_PORT2 + 10, "MICLK_S3"),
	/* Port 3 */
	PINCTRL_PIN(TB10X_PORT3 +  0, "MICLK_S4"),
	PINCTRL_PIN(TB10X_PORT3 +  1, "MISTRT_S4"),
	PINCTRL_PIN(TB10X_PORT3 +  2, "MIVAL_S4"),
	PINCTRL_PIN(TB10X_PORT3 +  3, "MDI_S4"),
	PINCTRL_PIN(TB10X_PORT3 +  4, "GPIOE0"),
	PINCTRL_PIN(TB10X_PORT3 +  5, "GPIOE1"),
	PINCTRL_PIN(TB10X_PORT3 +  6, "GPIOE2"),
	PINCTRL_PIN(TB10X_PORT3 +  7, "MDI_S5"),
	PINCTRL_PIN(TB10X_PORT3 +  8, "MIVAL_S5"),
	PINCTRL_PIN(TB10X_PORT3 +  9, "MISTRT_S5"),
	PINCTRL_PIN(TB10X_PORT3 + 10, "MICLK_S5"),
	/* Port 4 */
	PINCTRL_PIN(TB10X_PORT4 +  0, "MICLK_S6"),
	PINCTRL_PIN(TB10X_PORT4 +  1, "MISTRT_S6"),
	PINCTRL_PIN(TB10X_PORT4 +  2, "MIVAL_S6"),
	PINCTRL_PIN(TB10X_PORT4 +  3, "MDI_S6"),
	PINCTRL_PIN(TB10X_PORT4 +  4, "GPIOG0"),
	PINCTRL_PIN(TB10X_PORT4 +  5, "GPIOG1"),
	PINCTRL_PIN(TB10X_PORT4 +  6, "GPIOG2"),
	PINCTRL_PIN(TB10X_PORT4 +  7, "MDI_S7"),
	PINCTRL_PIN(TB10X_PORT4 +  8, "MIVAL_S7"),
	PINCTRL_PIN(TB10X_PORT4 +  9, "MISTRT_S7"),
	PINCTRL_PIN(TB10X_PORT4 + 10, "MICLK_S7"),
	/* Port 5 */
	PINCTRL_PIN(TB10X_PORT5 +  0, "PC_CE1N"),
	PINCTRL_PIN(TB10X_PORT5 +  1, "PC_CE2N"),
	PINCTRL_PIN(TB10X_PORT5 +  2, "PC_REGN"),
	PINCTRL_PIN(TB10X_PORT5 +  3, "PC_INPACKN"),
	PINCTRL_PIN(TB10X_PORT5 +  4, "PC_OEN"),
	PINCTRL_PIN(TB10X_PORT5 +  5, "PC_WEN"),
	PINCTRL_PIN(TB10X_PORT5 +  6, "PC_IORDN"),
	PINCTRL_PIN(TB10X_PORT5 +  7, "PC_IOWRN"),
	PINCTRL_PIN(TB10X_PORT5 +  8, "PC_RDYIRQN"),
	PINCTRL_PIN(TB10X_PORT5 +  9, "PC_WAITN"),
	PINCTRL_PIN(TB10X_PORT5 + 10, "PC_A0"),
	PINCTRL_PIN(TB10X_PORT5 + 11, "PC_A1"),
	PINCTRL_PIN(TB10X_PORT5 + 12, "PC_A2"),
	PINCTRL_PIN(TB10X_PORT5 + 13, "PC_A3"),
	PINCTRL_PIN(TB10X_PORT5 + 14, "PC_A4"),
	PINCTRL_PIN(TB10X_PORT5 + 15, "PC_A5"),
	PINCTRL_PIN(TB10X_PORT5 + 16, "PC_A6"),
	PINCTRL_PIN(TB10X_PORT5 + 17, "PC_A7"),
	PINCTRL_PIN(TB10X_PORT5 + 18, "PC_A8"),
	PINCTRL_PIN(TB10X_PORT5 + 19, "PC_A9"),
	PINCTRL_PIN(TB10X_PORT5 + 20, "PC_A10"),
	PINCTRL_PIN(TB10X_PORT5 + 21, "PC_A11"),
	PINCTRL_PIN(TB10X_PORT5 + 22, "PC_A12"),
	PINCTRL_PIN(TB10X_PORT5 + 23, "PC_A13"),
	PINCTRL_PIN(TB10X_PORT5 + 24, "PC_A14"),
	PINCTRL_PIN(TB10X_PORT5 + 25, "PC_D0"),
	PINCTRL_PIN(TB10X_PORT5 + 26, "PC_D1"),
	PINCTRL_PIN(TB10X_PORT5 + 27, "PC_D2"),
	PINCTRL_PIN(TB10X_PORT5 + 28, "PC_D3"),
	PINCTRL_PIN(TB10X_PORT5 + 29, "PC_D4"),
	PINCTRL_PIN(TB10X_PORT5 + 30, "PC_D5"),
	PINCTRL_PIN(TB10X_PORT5 + 31, "PC_D6"),
	PINCTRL_PIN(TB10X_PORT5 + 32, "PC_D7"),
	PINCTRL_PIN(TB10X_PORT5 + 33, "PC_MOSTRT"),
	PINCTRL_PIN(TB10X_PORT5 + 34, "PC_MOVAL"),
	PINCTRL_PIN(TB10X_PORT5 + 35, "PC_MDO0"),
	PINCTRL_PIN(TB10X_PORT5 + 36, "PC_MDO1"),
	PINCTRL_PIN(TB10X_PORT5 + 37, "PC_MDO2"),
	PINCTRL_PIN(TB10X_PORT5 + 38, "PC_MDO3"),
	PINCTRL_PIN(TB10X_PORT5 + 39, "PC_MDO4"),
	PINCTRL_PIN(TB10X_PORT5 + 40, "PC_MDO5"),
	PINCTRL_PIN(TB10X_PORT5 + 41, "PC_MDO6"),
	PINCTRL_PIN(TB10X_PORT5 + 42, "PC_MDO7"),
	PINCTRL_PIN(TB10X_PORT5 + 43, "PC_MISTRT"),
	PINCTRL_PIN(TB10X_PORT5 + 44, "PC_MIVAL"),
	PINCTRL_PIN(TB10X_PORT5 + 45, "PC_MDI0"),
	PINCTRL_PIN(TB10X_PORT5 + 46, "PC_MDI1"),
	PINCTRL_PIN(TB10X_PORT5 + 47, "PC_MDI2"),
	PINCTRL_PIN(TB10X_PORT5 + 48, "PC_MDI3"),
	PINCTRL_PIN(TB10X_PORT5 + 49, "PC_MDI4"),
	PINCTRL_PIN(TB10X_PORT5 + 50, "PC_MDI5"),
	PINCTRL_PIN(TB10X_PORT5 + 51, "PC_MDI6"),
	PINCTRL_PIN(TB10X_PORT5 + 52, "PC_MDI7"),
	PINCTRL_PIN(TB10X_PORT5 + 53, "PC_MICLK"),
	/* Port 6 */
	PINCTRL_PIN(TB10X_PORT6 + 0, "T_MOSTRT_S0"),
	PINCTRL_PIN(TB10X_PORT6 + 1, "T_MOVAL_S0"),
	PINCTRL_PIN(TB10X_PORT6 + 2, "T_MDO_S0"),
	PINCTRL_PIN(TB10X_PORT6 + 3, "T_MOSTRT_S1"),
	PINCTRL_PIN(TB10X_PORT6 + 4, "T_MOVAL_S1"),
	PINCTRL_PIN(TB10X_PORT6 + 5, "T_MDO_S1"),
	PINCTRL_PIN(TB10X_PORT6 + 6, "T_MOSTRT_S2"),
	PINCTRL_PIN(TB10X_PORT6 + 7, "T_MOVAL_S2"),
	PINCTRL_PIN(TB10X_PORT6 + 8, "T_MDO_S2"),
	PINCTRL_PIN(TB10X_PORT6 + 9, "T_MOSTRT_S3"),
	/* Port 7 */
	PINCTRL_PIN(TB10X_PORT7 + 0, "UART0_TXD"),
	PINCTRL_PIN(TB10X_PORT7 + 1, "UART0_RXD"),
	PINCTRL_PIN(TB10X_PORT7 + 2, "UART0_CTS"),
	PINCTRL_PIN(TB10X_PORT7 + 3, "UART0_RTS"),
	PINCTRL_PIN(TB10X_PORT7 + 4, "UART1_TXD"),
	PINCTRL_PIN(TB10X_PORT7 + 5, "UART1_RXD"),
	PINCTRL_PIN(TB10X_PORT7 + 6, "UART1_CTS"),
	PINCTRL_PIN(TB10X_PORT7 + 7, "UART1_RTS"),
	/* Port 8 */
	PINCTRL_PIN(TB10X_PORT8 + 0, "SPI3_CLK"),
	PINCTRL_PIN(TB10X_PORT8 + 1, "SPI3_MISO"),
	PINCTRL_PIN(TB10X_PORT8 + 2, "SPI3_MOSI"),
	PINCTRL_PIN(TB10X_PORT8 + 3, "SPI3_SSN"),
	/* Port 9 */
	PINCTRL_PIN(TB10X_PORT9 + 0, "SPI1_CLK"),
	PINCTRL_PIN(TB10X_PORT9 + 1, "SPI1_MISO"),
	PINCTRL_PIN(TB10X_PORT9 + 2, "SPI1_MOSI"),
	PINCTRL_PIN(TB10X_PORT9 + 3, "SPI1_SSN0"),
	PINCTRL_PIN(TB10X_PORT9 + 4, "SPI1_SSN1"),
	/* Unmuxed GPIOs */
	PINCTRL_PIN(TB10X_GPIOS +  0, "GPIOB0"),
	PINCTRL_PIN(TB10X_GPIOS +  1, "GPIOB1"),

	PINCTRL_PIN(TB10X_GPIOS +  2, "GPIOD0"),
	PINCTRL_PIN(TB10X_GPIOS +  3, "GPIOD1"),

	PINCTRL_PIN(TB10X_GPIOS +  4, "GPIOF0"),
	PINCTRL_PIN(TB10X_GPIOS +  5, "GPIOF1"),

	PINCTRL_PIN(TB10X_GPIOS +  6, "GPIOH0"),
	PINCTRL_PIN(TB10X_GPIOS +  7, "GPIOH1"),

	PINCTRL_PIN(TB10X_GPIOS +  8, "GPIOI0"),
	PINCTRL_PIN(TB10X_GPIOS +  9, "GPIOI1"),
	PINCTRL_PIN(TB10X_GPIOS + 10, "GPIOI2"),
	PINCTRL_PIN(TB10X_GPIOS + 11, "GPIOI3"),
	PINCTRL_PIN(TB10X_GPIOS + 12, "GPIOI4"),
	PINCTRL_PIN(TB10X_GPIOS + 13, "GPIOI5"),
	PINCTRL_PIN(TB10X_GPIOS + 14, "GPIOI6"),
	PINCTRL_PIN(TB10X_GPIOS + 15, "GPIOI7"),
	PINCTRL_PIN(TB10X_GPIOS + 16, "GPIOI8"),
	PINCTRL_PIN(TB10X_GPIOS + 17, "GPIOI9"),
	PINCTRL_PIN(TB10X_GPIOS + 18, "GPIOI10"),
	PINCTRL_PIN(TB10X_GPIOS + 19, "GPIOI11"),

	PINCTRL_PIN(TB10X_GPIOS + 20, "GPION0"),
	PINCTRL_PIN(TB10X_GPIOS + 21, "GPION1"),
	PINCTRL_PIN(TB10X_GPIOS + 22, "GPION2"),
	PINCTRL_PIN(TB10X_GPIOS + 23, "GPION3"),
#घोषणा MAX_PIN (TB10X_GPIOS + 24)
	PINCTRL_PIN(MAX_PIN,  "GPION4"),
पूर्ण;


/* Port 1 */
अटल स्थिर अचिन्हित mis0_pins[]  = अणु	TB10X_PORT1 + 0, TB10X_PORT1 + 1,
					TB10X_PORT1 + 2, TB10X_PORT1 + 3पूर्ण;
अटल स्थिर अचिन्हित gpioa_pins[] = अणु	TB10X_PORT1 + 4, TB10X_PORT1 + 5,
					TB10X_PORT1 + 6पूर्ण;
अटल स्थिर अचिन्हित mis1_pins[]  = अणु	TB10X_PORT1 + 7, TB10X_PORT1 + 8,
					TB10X_PORT1 + 9, TB10X_PORT1 + 10पूर्ण;
अटल स्थिर अचिन्हित mip1_pins[]  = अणु	TB10X_PORT1 + 0, TB10X_PORT1 + 1,
					TB10X_PORT1 + 2, TB10X_PORT1 + 3,
					TB10X_PORT1 + 4, TB10X_PORT1 + 5,
					TB10X_PORT1 + 6, TB10X_PORT1 + 7,
					TB10X_PORT1 + 8, TB10X_PORT1 + 9,
					TB10X_PORT1 + 10पूर्ण;

/* Port 2 */
अटल स्थिर अचिन्हित mis2_pins[]  = अणु	TB10X_PORT2 + 0, TB10X_PORT2 + 1,
					TB10X_PORT2 + 2, TB10X_PORT2 + 3पूर्ण;
अटल स्थिर अचिन्हित gpioc_pins[] = अणु	TB10X_PORT2 + 4, TB10X_PORT2 + 5,
					TB10X_PORT2 + 6पूर्ण;
अटल स्थिर अचिन्हित mis3_pins[]  = अणु	TB10X_PORT2 + 7, TB10X_PORT2 + 8,
					TB10X_PORT2 + 9, TB10X_PORT2 + 10पूर्ण;
अटल स्थिर अचिन्हित mip3_pins[]  = अणु	TB10X_PORT2 + 0, TB10X_PORT2 + 1,
					TB10X_PORT2 + 2, TB10X_PORT2 + 3,
					TB10X_PORT2 + 4, TB10X_PORT2 + 5,
					TB10X_PORT2 + 6, TB10X_PORT2 + 7,
					TB10X_PORT2 + 8, TB10X_PORT2 + 9,
					TB10X_PORT2 + 10पूर्ण;

/* Port 3 */
अटल स्थिर अचिन्हित mis4_pins[]  = अणु	TB10X_PORT3 + 0, TB10X_PORT3 + 1,
					TB10X_PORT3 + 2, TB10X_PORT3 + 3पूर्ण;
अटल स्थिर अचिन्हित gpioe_pins[] = अणु	TB10X_PORT3 + 4, TB10X_PORT3 + 5,
					TB10X_PORT3 + 6पूर्ण;
अटल स्थिर अचिन्हित mis5_pins[]  = अणु	TB10X_PORT3 + 7, TB10X_PORT3 + 8,
					TB10X_PORT3 + 9, TB10X_PORT3 + 10पूर्ण;
अटल स्थिर अचिन्हित mip5_pins[]  = अणु	TB10X_PORT3 + 0, TB10X_PORT3 + 1,
					TB10X_PORT3 + 2, TB10X_PORT3 + 3,
					TB10X_PORT3 + 4, TB10X_PORT3 + 5,
					TB10X_PORT3 + 6, TB10X_PORT3 + 7,
					TB10X_PORT3 + 8, TB10X_PORT3 + 9,
					TB10X_PORT3 + 10पूर्ण;

/* Port 4 */
अटल स्थिर अचिन्हित mis6_pins[]  = अणु	TB10X_PORT4 + 0, TB10X_PORT4 + 1,
					TB10X_PORT4 + 2, TB10X_PORT4 + 3पूर्ण;
अटल स्थिर अचिन्हित gpiog_pins[] = अणु	TB10X_PORT4 + 4, TB10X_PORT4 + 5,
					TB10X_PORT4 + 6पूर्ण;
अटल स्थिर अचिन्हित mis7_pins[]  = अणु	TB10X_PORT4 + 7, TB10X_PORT4 + 8,
					TB10X_PORT4 + 9, TB10X_PORT4 + 10पूर्ण;
अटल स्थिर अचिन्हित mip7_pins[]  = अणु	TB10X_PORT4 + 0, TB10X_PORT4 + 1,
					TB10X_PORT4 + 2, TB10X_PORT4 + 3,
					TB10X_PORT4 + 4, TB10X_PORT4 + 5,
					TB10X_PORT4 + 6, TB10X_PORT4 + 7,
					TB10X_PORT4 + 8, TB10X_PORT4 + 9,
					TB10X_PORT4 + 10पूर्ण;

/* Port 6 */
अटल स्थिर अचिन्हित mop_pins[] = अणु	TB10X_PORT6 + 0, TB10X_PORT6 + 1,
					TB10X_PORT6 + 2, TB10X_PORT6 + 3,
					TB10X_PORT6 + 4, TB10X_PORT6 + 5,
					TB10X_PORT6 + 6, TB10X_PORT6 + 7,
					TB10X_PORT6 + 8, TB10X_PORT6 + 9पूर्ण;
अटल स्थिर अचिन्हित mos0_pins[] = अणु	TB10X_PORT6 + 0, TB10X_PORT6 + 1,
					TB10X_PORT6 + 2पूर्ण;
अटल स्थिर अचिन्हित mos1_pins[] = अणु	TB10X_PORT6 + 3, TB10X_PORT6 + 4,
					TB10X_PORT6 + 5पूर्ण;
अटल स्थिर अचिन्हित mos2_pins[] = अणु	TB10X_PORT6 + 6, TB10X_PORT6 + 7,
					TB10X_PORT6 + 8पूर्ण;
अटल स्थिर अचिन्हित mos3_pins[] = अणु	TB10X_PORT6 + 9पूर्ण;

/* Port 7 */
अटल स्थिर अचिन्हित uart0_pins[] = अणु	TB10X_PORT7 + 0, TB10X_PORT7 + 1,
					TB10X_PORT7 + 2, TB10X_PORT7 + 3पूर्ण;
अटल स्थिर अचिन्हित uart1_pins[] = अणु	TB10X_PORT7 + 4, TB10X_PORT7 + 5,
					TB10X_PORT7 + 6, TB10X_PORT7 + 7पूर्ण;
अटल स्थिर अचिन्हित gpiol_pins[] = अणु	TB10X_PORT7 + 0, TB10X_PORT7 + 1,
					TB10X_PORT7 + 2, TB10X_PORT7 + 3पूर्ण;
अटल स्थिर अचिन्हित gpiom_pins[] = अणु	TB10X_PORT7 + 4, TB10X_PORT7 + 5,
					TB10X_PORT7 + 6, TB10X_PORT7 + 7पूर्ण;

/* Port 8 */
अटल स्थिर अचिन्हित spi3_pins[] = अणु	TB10X_PORT8 + 0, TB10X_PORT8 + 1,
					TB10X_PORT8 + 2, TB10X_PORT8 + 3पूर्ण;
अटल स्थिर अचिन्हित jtag_pins[] = अणु	TB10X_PORT8 + 0, TB10X_PORT8 + 1,
					TB10X_PORT8 + 2, TB10X_PORT8 + 3पूर्ण;

/* Port 9 */
अटल स्थिर अचिन्हित spi1_pins[] = अणु	TB10X_PORT9 + 0, TB10X_PORT9 + 1,
					TB10X_PORT9 + 2, TB10X_PORT9 + 3,
					TB10X_PORT9 + 4पूर्ण;
अटल स्थिर अचिन्हित gpion_pins[] = अणु	TB10X_PORT9 + 0, TB10X_PORT9 + 1,
					TB10X_PORT9 + 2, TB10X_PORT9 + 3,
					TB10X_PORT9 + 4पूर्ण;

/* Port 5 */
अटल स्थिर अचिन्हित gpioj_pins[] = अणु	TB10X_PORT5 + 0, TB10X_PORT5 + 1,
					TB10X_PORT5 + 2, TB10X_PORT5 + 3,
					TB10X_PORT5 + 4, TB10X_PORT5 + 5,
					TB10X_PORT5 + 6, TB10X_PORT5 + 7,
					TB10X_PORT5 + 8, TB10X_PORT5 + 9,
					TB10X_PORT5 + 10, TB10X_PORT5 + 11,
					TB10X_PORT5 + 12, TB10X_PORT5 + 13,
					TB10X_PORT5 + 14, TB10X_PORT5 + 15,
					TB10X_PORT5 + 16, TB10X_PORT5 + 17,
					TB10X_PORT5 + 18, TB10X_PORT5 + 19,
					TB10X_PORT5 + 20, TB10X_PORT5 + 21,
					TB10X_PORT5 + 22, TB10X_PORT5 + 23,
					TB10X_PORT5 + 24, TB10X_PORT5 + 25,
					TB10X_PORT5 + 26, TB10X_PORT5 + 27,
					TB10X_PORT5 + 28, TB10X_PORT5 + 29,
					TB10X_PORT5 + 30, TB10X_PORT5 + 31पूर्ण;
अटल स्थिर अचिन्हित gpiok_pins[] = अणु	TB10X_PORT5 + 32, TB10X_PORT5 + 33,
					TB10X_PORT5 + 34, TB10X_PORT5 + 35,
					TB10X_PORT5 + 36, TB10X_PORT5 + 37,
					TB10X_PORT5 + 38, TB10X_PORT5 + 39,
					TB10X_PORT5 + 40, TB10X_PORT5 + 41,
					TB10X_PORT5 + 42, TB10X_PORT5 + 43,
					TB10X_PORT5 + 44, TB10X_PORT5 + 45,
					TB10X_PORT5 + 46, TB10X_PORT5 + 47,
					TB10X_PORT5 + 48, TB10X_PORT5 + 49,
					TB10X_PORT5 + 50, TB10X_PORT5 + 51,
					TB10X_PORT5 + 52, TB10X_PORT5 + 53पूर्ण;
अटल स्थिर अचिन्हित ciplus_pins[] = अणु	TB10X_PORT5 + 0, TB10X_PORT5 + 1,
					TB10X_PORT5 + 2, TB10X_PORT5 + 3,
					TB10X_PORT5 + 4, TB10X_PORT5 + 5,
					TB10X_PORT5 + 6, TB10X_PORT5 + 7,
					TB10X_PORT5 + 8, TB10X_PORT5 + 9,
					TB10X_PORT5 + 10, TB10X_PORT5 + 11,
					TB10X_PORT5 + 12, TB10X_PORT5 + 13,
					TB10X_PORT5 + 14, TB10X_PORT5 + 15,
					TB10X_PORT5 + 16, TB10X_PORT5 + 17,
					TB10X_PORT5 + 18, TB10X_PORT5 + 19,
					TB10X_PORT5 + 20, TB10X_PORT5 + 21,
					TB10X_PORT5 + 22, TB10X_PORT5 + 23,
					TB10X_PORT5 + 24, TB10X_PORT5 + 25,
					TB10X_PORT5 + 26, TB10X_PORT5 + 27,
					TB10X_PORT5 + 28, TB10X_PORT5 + 29,
					TB10X_PORT5 + 30, TB10X_PORT5 + 31,
					TB10X_PORT5 + 32, TB10X_PORT5 + 33,
					TB10X_PORT5 + 34, TB10X_PORT5 + 35,
					TB10X_PORT5 + 36, TB10X_PORT5 + 37,
					TB10X_PORT5 + 38, TB10X_PORT5 + 39,
					TB10X_PORT5 + 40, TB10X_PORT5 + 41,
					TB10X_PORT5 + 42, TB10X_PORT5 + 43,
					TB10X_PORT5 + 44, TB10X_PORT5 + 45,
					TB10X_PORT5 + 46, TB10X_PORT5 + 47,
					TB10X_PORT5 + 48, TB10X_PORT5 + 49,
					TB10X_PORT5 + 50, TB10X_PORT5 + 51,
					TB10X_PORT5 + 52, TB10X_PORT5 + 53पूर्ण;
अटल स्थिर अचिन्हित mcard_pins[] = अणु	TB10X_PORT5 + 3, TB10X_PORT5 + 10,
					TB10X_PORT5 + 11, TB10X_PORT5 + 12,
					TB10X_PORT5 + 22, TB10X_PORT5 + 23,
					TB10X_PORT5 + 33, TB10X_PORT5 + 35,
					TB10X_PORT5 + 36, TB10X_PORT5 + 37,
					TB10X_PORT5 + 38, TB10X_PORT5 + 39,
					TB10X_PORT5 + 40, TB10X_PORT5 + 41,
					TB10X_PORT5 + 42, TB10X_PORT5 + 43,
					TB10X_PORT5 + 45, TB10X_PORT5 + 46,
					TB10X_PORT5 + 47, TB10X_PORT5 + 48,
					TB10X_PORT5 + 49, TB10X_PORT5 + 50,
					TB10X_PORT5 + 51, TB10X_PORT5 + 52,
					TB10X_PORT5 + 53पूर्ण;
अटल स्थिर अचिन्हित stc0_pins[] = अणु	TB10X_PORT5 + 34, TB10X_PORT5 + 35,
					TB10X_PORT5 + 36, TB10X_PORT5 + 37,
					TB10X_PORT5 + 38, TB10X_PORT5 + 39,
					TB10X_PORT5 + 40पूर्ण;
अटल स्थिर अचिन्हित stc1_pins[] = अणु	TB10X_PORT5 + 25, TB10X_PORT5 + 26,
					TB10X_PORT5 + 27, TB10X_PORT5 + 28,
					TB10X_PORT5 + 29, TB10X_PORT5 + 30,
					TB10X_PORT5 + 44पूर्ण;

/* Unmuxed GPIOs */
अटल स्थिर अचिन्हित gpiob_pins[] = अणु	TB10X_GPIOS + 0, TB10X_GPIOS + 1पूर्ण;
अटल स्थिर अचिन्हित gpiod_pins[] = अणु	TB10X_GPIOS + 2, TB10X_GPIOS + 3पूर्ण;
अटल स्थिर अचिन्हित gpiof_pins[] = अणु	TB10X_GPIOS + 4, TB10X_GPIOS + 5पूर्ण;
अटल स्थिर अचिन्हित gpioh_pins[] = अणु	TB10X_GPIOS + 6, TB10X_GPIOS + 7पूर्ण;
अटल स्थिर अचिन्हित gpioi_pins[] = अणु	TB10X_GPIOS + 8, TB10X_GPIOS + 9,
					TB10X_GPIOS + 10, TB10X_GPIOS + 11,
					TB10X_GPIOS + 12, TB10X_GPIOS + 13,
					TB10X_GPIOS + 14, TB10X_GPIOS + 15,
					TB10X_GPIOS + 16, TB10X_GPIOS + 17,
					TB10X_GPIOS + 18, TB10X_GPIOS + 19पूर्ण;

काष्ठा tb10x_pinfuncgrp अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक pincnt;
	स्थिर पूर्णांक port;
	स्थिर अचिन्हित पूर्णांक mode;
	स्थिर पूर्णांक isgpio;
पूर्ण;
#घोषणा DEFPINFUNCGRP(NAME, PORT, MODE, ISGPIO) अणु \
		.name = __stringअगरy(NAME), \
		.pins = NAME##_pins, .pincnt = ARRAY_SIZE(NAME##_pins), \
		.port = (PORT), .mode = (MODE), \
		.isgpio = (ISGPIO), \
	पूर्ण
अटल स्थिर काष्ठा tb10x_pinfuncgrp tb10x_pingroups[] = अणु
	DEFPINFUNCGRP(mis0,   0, 0, 0),
	DEFPINFUNCGRP(gpioa,  0, 0, 1),
	DEFPINFUNCGRP(mis1,   0, 0, 0),
	DEFPINFUNCGRP(mip1,   0, 1, 0),
	DEFPINFUNCGRP(mis2,   1, 0, 0),
	DEFPINFUNCGRP(gpioc,  1, 0, 1),
	DEFPINFUNCGRP(mis3,   1, 0, 0),
	DEFPINFUNCGRP(mip3,   1, 1, 0),
	DEFPINFUNCGRP(mis4,   2, 0, 0),
	DEFPINFUNCGRP(gpioe,  2, 0, 1),
	DEFPINFUNCGRP(mis5,   2, 0, 0),
	DEFPINFUNCGRP(mip5,   2, 1, 0),
	DEFPINFUNCGRP(mis6,   3, 0, 0),
	DEFPINFUNCGRP(gpiog,  3, 0, 1),
	DEFPINFUNCGRP(mis7,   3, 0, 0),
	DEFPINFUNCGRP(mip7,   3, 1, 0),
	DEFPINFUNCGRP(gpioj,  4, 0, 1),
	DEFPINFUNCGRP(gpiok,  4, 0, 1),
	DEFPINFUNCGRP(ciplus, 4, 1, 0),
	DEFPINFUNCGRP(mcard,  4, 2, 0),
	DEFPINFUNCGRP(stc0,   4, 3, 0),
	DEFPINFUNCGRP(stc1,   4, 3, 0),
	DEFPINFUNCGRP(mop,    5, 0, 0),
	DEFPINFUNCGRP(mos0,   5, 1, 0),
	DEFPINFUNCGRP(mos1,   5, 1, 0),
	DEFPINFUNCGRP(mos2,   5, 1, 0),
	DEFPINFUNCGRP(mos3,   5, 1, 0),
	DEFPINFUNCGRP(uart0,  6, 0, 0),
	DEFPINFUNCGRP(uart1,  6, 0, 0),
	DEFPINFUNCGRP(gpiol,  6, 1, 1),
	DEFPINFUNCGRP(gpiom,  6, 1, 1),
	DEFPINFUNCGRP(spi3,   7, 0, 0),
	DEFPINFUNCGRP(jtag,   7, 1, 0),
	DEFPINFUNCGRP(spi1,   8, 0, 0),
	DEFPINFUNCGRP(gpion,  8, 1, 1),
	DEFPINFUNCGRP(gpiob, -1, 0, 1),
	DEFPINFUNCGRP(gpiod, -1, 0, 1),
	DEFPINFUNCGRP(gpiof, -1, 0, 1),
	DEFPINFUNCGRP(gpioh, -1, 0, 1),
	DEFPINFUNCGRP(gpioi, -1, 0, 1),
पूर्ण;
#अघोषित DEFPINFUNCGRP

काष्ठा tb10x_of_pinfunc अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *group;
पूर्ण;

#घोषणा TB10X_PORTS (9)

/**
 * काष्ठा tb10x_port - state of an I/O port
 * @mode: Node this port is currently in.
 * @count: Number of enabled functions which require this port to be
 *         configured in @mode.
 */
काष्ठा tb10x_port अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक count;
पूर्ण;

/**
 * काष्ठा tb10x_pinctrl - TB10x pin controller पूर्णांकernal state
 * @pctl: poपूर्णांकer to the pinctrl_dev काष्ठाure of this pin controller.
 * @base: रेजिस्टर set base address.
 * @pingroups: poपूर्णांकer to an array of the pin groups this driver manages.
 * @pinfuncgrpcnt: number of pingroups in @pingroups.
 * @pinfuncnt: number of pin functions in @pinfuncs.
 * @mutex: mutex क्रम exclusive access to a pin controller's state.
 * @ports: current state of each port.
 * @gpios: Indicates अगर a given pin is currently used as GPIO (1) or not (0).
 * @pinfuncs: flexible array of pin functions this driver manages.
 */
काष्ठा tb10x_pinctrl अणु
	काष्ठा pinctrl_dev *pctl;
	व्योम *base;
	स्थिर काष्ठा tb10x_pinfuncgrp *pingroups;
	अचिन्हित पूर्णांक pinfuncgrpcnt;
	अचिन्हित पूर्णांक pinfuncnt;
	काष्ठा mutex mutex;
	काष्ठा tb10x_port ports[TB10X_PORTS];
	DECLARE_BITMAP(gpios, MAX_PIN + 1);
	काष्ठा tb10x_of_pinfunc pinfuncs[];
पूर्ण;

अटल अंतरभूत व्योम tb10x_pinctrl_set_config(काष्ठा tb10x_pinctrl *state,
				अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक mode)
अणु
	u32 pcfg;

	अगर (state->ports[port].count)
		वापस;

	state->ports[port].mode = mode;

	pcfg = ioपढ़ो32(state->base) & ~(PCFG_PORT_MASK(port));
	pcfg |= (mode << (PCFG_PORT_BITWIDTH * port)) & PCFG_PORT_MASK(port);
	ioग_लिखो32(pcfg, state->base);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tb10x_pinctrl_get_config(
				काष्ठा tb10x_pinctrl *state,
				अचिन्हित पूर्णांक port)
अणु
	वापस (ioपढ़ो32(state->base) & PCFG_PORT_MASK(port))
		>> (PCFG_PORT_BITWIDTH * port);
पूर्ण

अटल पूर्णांक tb10x_get_groups_count(काष्ठा pinctrl_dev *pctl)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	वापस state->pinfuncgrpcnt;
पूर्ण

अटल स्थिर अक्षर *tb10x_get_group_name(काष्ठा pinctrl_dev *pctl, अचिन्हित n)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	वापस state->pingroups[n].name;
पूर्ण

अटल पूर्णांक tb10x_get_group_pins(काष्ठा pinctrl_dev *pctl, अचिन्हित n,
				अचिन्हित स्थिर **pins,
				अचिन्हित * स्थिर num_pins)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);

	*pins = state->pingroups[n].pins;
	*num_pins = state->pingroups[n].pincnt;

	वापस 0;
पूर्ण

अटल पूर्णांक tb10x_dt_node_to_map(काष्ठा pinctrl_dev *pctl,
				काष्ठा device_node *np_config,
				काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	स्थिर अक्षर *string;
	अचिन्हित reserved_maps = 0;
	पूर्णांक ret = 0;

	अगर (of_property_पढ़ो_string(np_config, "abilis,function", &string)) अणु
		pr_err("%pOF: No abilis,function property in device tree.\n",
			np_config);
		वापस -EINVAL;
	पूर्ण

	*map = शून्य;
	*num_maps = 0;

	ret = pinctrl_utils_reserve_map(pctl, map, &reserved_maps,
					num_maps, 1);
	अगर (ret)
		जाओ out;

	ret = pinctrl_utils_add_map_mux(pctl, map, &reserved_maps,
					num_maps, string, np_config->name);

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops tb10x_pinctrl_ops = अणु
	.get_groups_count = tb10x_get_groups_count,
	.get_group_name   = tb10x_get_group_name,
	.get_group_pins   = tb10x_get_group_pins,
	.dt_node_to_map   = tb10x_dt_node_to_map,
	.dt_मुक्त_map      = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक tb10x_get_functions_count(काष्ठा pinctrl_dev *pctl)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	वापस state->pinfuncnt;
पूर्ण

अटल स्थिर अक्षर *tb10x_get_function_name(काष्ठा pinctrl_dev *pctl,
					अचिन्हित n)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	वापस state->pinfuncs[n].name;
पूर्ण

अटल पूर्णांक tb10x_get_function_groups(काष्ठा pinctrl_dev *pctl,
				अचिन्हित n, स्थिर अक्षर * स्थिर **groups,
				अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);

	*groups = &state->pinfuncs[n].group;
	*num_groups = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक tb10x_gpio_request_enable(काष्ठा pinctrl_dev *pctl,
					काष्ठा pinctrl_gpio_range *range,
					अचिन्हित pin)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	पूर्णांक muxport = -1;
	पूर्णांक muxmode = -1;
	पूर्णांक i;

	mutex_lock(&state->mutex);

	/*
	 * Figure out to which port the requested GPIO beदीर्घs and how to
	 * configure that port.
	 * This loop also checks क्रम pin conflicts between GPIOs and other
	 * functions.
	 */
	क्रम (i = 0; i < state->pinfuncgrpcnt; i++) अणु
		स्थिर काष्ठा tb10x_pinfuncgrp *pfg = &state->pingroups[i];
		अचिन्हित पूर्णांक mode = pfg->mode;
		पूर्णांक j, port = pfg->port;

		/*
		 * Skip pin groups which are always mapped and करोn't need
		 * to be configured.
		 */
		अगर (port < 0)
			जारी;

		क्रम (j = 0; j < pfg->pincnt; j++) अणु
			अगर (pin == pfg->pins[j]) अणु
				अगर (pfg->isgpio) अणु
					/*
					 * Remember the GPIO-only setting of
					 * the port this pin beदीर्घs to.
					 */
					muxport = port;
					muxmode = mode;
				पूर्ण अन्यथा अगर (state->ports[port].count
					&& (state->ports[port].mode == mode)) अणु
					/*
					 * Error: The requested pin is alपढ़ोy
					 * used क्रम something अन्यथा.
					 */
					mutex_unlock(&state->mutex);
					वापस -EBUSY;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If we haven't वापसed an error at this poपूर्णांक, the GPIO pin is not
	 * used by another function and the GPIO request can be granted:
	 * Register pin as being used as GPIO so we करोn't allocate it to
	 * another function later.
	 */
	set_bit(pin, state->gpios);

	/*
	 * Potential conflicts between GPIOs and pin functions were caught
	 * earlier in this function and tb10x_pinctrl_set_config will करो the
	 * Right Thing, either configure the port in GPIO only mode or leave
	 * another mode compatible with this GPIO request untouched.
	 */
	अगर (muxport >= 0)
		tb10x_pinctrl_set_config(state, muxport, muxmode);

	mutex_unlock(&state->mutex);

	वापस 0;
पूर्ण

अटल व्योम tb10x_gpio_disable_मुक्त(काष्ठा pinctrl_dev *pctl,
					काष्ठा pinctrl_gpio_range *range,
					अचिन्हित pin)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);

	mutex_lock(&state->mutex);

	clear_bit(pin, state->gpios);

	mutex_unlock(&state->mutex);
पूर्ण

अटल पूर्णांक tb10x_pctl_set_mux(काष्ठा pinctrl_dev *pctl,
			अचिन्हित func_selector, अचिन्हित group_selector)
अणु
	काष्ठा tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	स्थिर काष्ठा tb10x_pinfuncgrp *grp = &state->pingroups[group_selector];
	पूर्णांक i;

	अगर (grp->port < 0)
		वापस 0;

	mutex_lock(&state->mutex);

	/*
	 * Check अगर the requested function is compatible with previously
	 * requested functions.
	 */
	अगर (state->ports[grp->port].count
			&& (state->ports[grp->port].mode != grp->mode)) अणु
		mutex_unlock(&state->mutex);
		वापस -EBUSY;
	पूर्ण

	/*
	 * Check अगर the requested function is compatible with previously
	 * requested GPIOs.
	 */
	क्रम (i = 0; i < grp->pincnt; i++)
		अगर (test_bit(grp->pins[i], state->gpios)) अणु
			mutex_unlock(&state->mutex);
			वापस -EBUSY;
		पूर्ण

	tb10x_pinctrl_set_config(state, grp->port, grp->mode);

	state->ports[grp->port].count++;

	mutex_unlock(&state->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops tb10x_pinmux_ops = अणु
	.get_functions_count = tb10x_get_functions_count,
	.get_function_name = tb10x_get_function_name,
	.get_function_groups = tb10x_get_function_groups,
	.gpio_request_enable = tb10x_gpio_request_enable,
	.gpio_disable_मुक्त = tb10x_gpio_disable_मुक्त,
	.set_mux = tb10x_pctl_set_mux,
पूर्ण;

अटल काष्ठा pinctrl_desc tb10x_pindesc = अणु
	.name = "TB10x",
	.pins = tb10x_pins,
	.npins = ARRAY_SIZE(tb10x_pins),
	.owner = THIS_MODULE,
	.pctlops = &tb10x_pinctrl_ops,
	.pmxops  = &tb10x_pinmux_ops,
पूर्ण;

अटल पूर्णांक tb10x_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *of_node = dev->of_node;
	काष्ठा device_node *child;
	काष्ठा tb10x_pinctrl *state;
	पूर्णांक i;

	अगर (!of_node) अणु
		dev_err(dev, "No device tree node found.\n");
		वापस -EINVAL;
	पूर्ण

	state = devm_kzalloc(dev, काष्ठा_size(state, pinfuncs,
					      of_get_child_count(of_node)),
			     GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, state);
	mutex_init(&state->mutex);

	state->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(state->base)) अणु
		ret = PTR_ERR(state->base);
		जाओ fail;
	पूर्ण

	state->pingroups = tb10x_pingroups;
	state->pinfuncgrpcnt = ARRAY_SIZE(tb10x_pingroups);

	क्रम (i = 0; i < TB10X_PORTS; i++)
		state->ports[i].mode = tb10x_pinctrl_get_config(state, i);

	क्रम_each_child_of_node(of_node, child) अणु
		स्थिर अक्षर *name;

		अगर (!of_property_पढ़ो_string(child, "abilis,function",
						&name)) अणु
			state->pinfuncs[state->pinfuncnt].name = child->name;
			state->pinfuncs[state->pinfuncnt].group = name;
			state->pinfuncnt++;
		पूर्ण
	पूर्ण

	state->pctl = devm_pinctrl_रेजिस्टर(dev, &tb10x_pindesc, state);
	अगर (IS_ERR(state->pctl)) अणु
		dev_err(dev, "could not register TB10x pin driver\n");
		ret = PTR_ERR(state->pctl);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	mutex_destroy(&state->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक tb10x_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tb10x_pinctrl *state = platक्रमm_get_drvdata(pdev);

	mutex_destroy(&state->mutex);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id tb10x_pinctrl_dt_ids[] = अणु
	अणु .compatible = "abilis,tb10x-iomux" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tb10x_pinctrl_dt_ids);

अटल काष्ठा platक्रमm_driver tb10x_pinctrl_pdrv = अणु
	.probe   = tb10x_pinctrl_probe,
	.हटाओ  = tb10x_pinctrl_हटाओ,
	.driver  = अणु
		.name  = "tb10x_pinctrl",
		.of_match_table = of_match_ptr(tb10x_pinctrl_dt_ids),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(tb10x_pinctrl_pdrv);

MODULE_AUTHOR("Christian Ruppert <christian.ruppert@abilis.com>");
MODULE_LICENSE("GPL");
