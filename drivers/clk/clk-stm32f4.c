<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Author: Daniel Thompson <daniel.thompson@linaro.org>
 *
 * Inspired by clk-यंत्र9260.c .
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

/*
 * Include list of घड़ीs wich are not derived from प्रणाली घड़ी (SYSCLOCK)
 * The index of these घड़ीs is the secondary index of DT bindings
 *
 */
#समावेश <dt-bindings/घड़ी/sपंचांग32fx-घड़ी.h>

#घोषणा STM32F4_RCC_CR			0x00
#घोषणा STM32F4_RCC_PLLCFGR		0x04
#घोषणा STM32F4_RCC_CFGR		0x08
#घोषणा STM32F4_RCC_AHB1ENR		0x30
#घोषणा STM32F4_RCC_AHB2ENR		0x34
#घोषणा STM32F4_RCC_AHB3ENR		0x38
#घोषणा STM32F4_RCC_APB1ENR		0x40
#घोषणा STM32F4_RCC_APB2ENR		0x44
#घोषणा STM32F4_RCC_BDCR		0x70
#घोषणा STM32F4_RCC_CSR			0x74
#घोषणा STM32F4_RCC_PLLI2SCFGR		0x84
#घोषणा STM32F4_RCC_PLLSAICFGR		0x88
#घोषणा STM32F4_RCC_DCKCFGR		0x8c
#घोषणा STM32F7_RCC_DCKCFGR2		0x90

#घोषणा NONE -1
#घोषणा NO_IDX  NONE
#घोषणा NO_MUX  NONE
#घोषणा NO_GATE NONE

काष्ठा sपंचांग32f4_gate_data अणु
	u8	offset;
	u8	bit_idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_gate_data sपंचांग32f429_gates[] __initस्थिर = अणु
	अणु STM32F4_RCC_AHB1ENR,  0,	"gpioa",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  1,	"gpiob",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  2,	"gpioc",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  3,	"gpiod",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  4,	"gpioe",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  5,	"gpiof",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  6,	"gpiog",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  7,	"gpioh",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  8,	"gpioi",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  9,	"gpioj",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 10,	"gpiok",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 12,	"crc",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 18,	"bkpsra",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 20,	"ccmdatam",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 21,	"dma1",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 22,	"dma2",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 23,	"dma2d",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 25,	"ethmac",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 26,	"ethmactx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 27,	"ethmacrx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 28,	"ethmacptp",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 29,	"otghs",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 30,	"otghsulpi",	"ahb_div" पूर्ण,

	अणु STM32F4_RCC_AHB2ENR,  0,	"dcmi",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  4,	"cryp",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  5,	"hash",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  6,	"rng",		"pll48" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  7,	"otgfs",	"pll48" पूर्ण,

	अणु STM32F4_RCC_AHB3ENR,  0,	"fmc",		"ahb_div",
		CLK_IGNORE_UNUSED पूर्ण,

	अणु STM32F4_RCC_APB1ENR,  0,	"tim2",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  1,	"tim3",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  2,	"tim4",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  3,	"tim5",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  4,	"tim6",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  5,	"tim7",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  6,	"tim12",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  7,	"tim13",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  8,	"tim14",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 11,	"wwdg",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 14,	"spi2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 15,	"spi3",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 17,	"uart2",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 18,	"uart3",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 19,	"uart4",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 20,	"uart5",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 21,	"i2c1",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 22,	"i2c2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 23,	"i2c3",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 25,	"can1",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 26,	"can2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 28,	"pwr",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 29,	"dac",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 30,	"uart7",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 31,	"uart8",	"apb1_div" पूर्ण,

	अणु STM32F4_RCC_APB2ENR,  0,	"tim1",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  1,	"tim8",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  4,	"usart1",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  5,	"usart6",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  8,	"adc1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  9,	"adc2",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 10,	"adc3",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 11,	"sdio",		"pll48" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 12,	"spi1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 13,	"spi4",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 14,	"syscfg",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 16,	"tim9",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 17,	"tim10",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 18,	"tim11",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 20,	"spi5",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 21,	"spi6",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 22,	"sai1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 26,	"ltdc",		"apb2_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_gate_data sपंचांग32f469_gates[] __initस्थिर = अणु
	अणु STM32F4_RCC_AHB1ENR,  0,	"gpioa",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  1,	"gpiob",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  2,	"gpioc",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  3,	"gpiod",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  4,	"gpioe",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  5,	"gpiof",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  6,	"gpiog",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  7,	"gpioh",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  8,	"gpioi",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  9,	"gpioj",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 10,	"gpiok",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 12,	"crc",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 18,	"bkpsra",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 20,	"ccmdatam",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 21,	"dma1",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 22,	"dma2",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 23,	"dma2d",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 25,	"ethmac",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 26,	"ethmactx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 27,	"ethmacrx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 28,	"ethmacptp",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 29,	"otghs",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 30,	"otghsulpi",	"ahb_div" पूर्ण,

	अणु STM32F4_RCC_AHB2ENR,  0,	"dcmi",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  4,	"cryp",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  5,	"hash",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  6,	"rng",		"pll48" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  7,	"otgfs",	"pll48" पूर्ण,

	अणु STM32F4_RCC_AHB3ENR,  0,	"fmc",		"ahb_div",
		CLK_IGNORE_UNUSED पूर्ण,
	अणु STM32F4_RCC_AHB3ENR,  1,	"qspi",		"ahb_div",
		CLK_IGNORE_UNUSED पूर्ण,

	अणु STM32F4_RCC_APB1ENR,  0,	"tim2",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  1,	"tim3",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  2,	"tim4",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  3,	"tim5",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  4,	"tim6",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  5,	"tim7",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  6,	"tim12",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  7,	"tim13",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  8,	"tim14",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 11,	"wwdg",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 14,	"spi2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 15,	"spi3",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 17,	"uart2",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 18,	"uart3",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 19,	"uart4",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 20,	"uart5",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 21,	"i2c1",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 22,	"i2c2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 23,	"i2c3",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 25,	"can1",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 26,	"can2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 28,	"pwr",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 29,	"dac",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 30,	"uart7",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 31,	"uart8",	"apb1_div" पूर्ण,

	अणु STM32F4_RCC_APB2ENR,  0,	"tim1",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  1,	"tim8",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  4,	"usart1",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  5,	"usart6",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  8,	"adc1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  9,	"adc2",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 10,	"adc3",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 11,	"sdio",		"sdmux" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 12,	"spi1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 13,	"spi4",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 14,	"syscfg",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 16,	"tim9",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 17,	"tim10",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 18,	"tim11",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 20,	"spi5",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 21,	"spi6",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 22,	"sai1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 26,	"ltdc",		"apb2_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_gate_data sपंचांग32f746_gates[] __initस्थिर = अणु
	अणु STM32F4_RCC_AHB1ENR,  0,	"gpioa",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  1,	"gpiob",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  2,	"gpioc",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  3,	"gpiod",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  4,	"gpioe",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  5,	"gpiof",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  6,	"gpiog",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  7,	"gpioh",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  8,	"gpioi",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  9,	"gpioj",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 10,	"gpiok",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 12,	"crc",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 18,	"bkpsra",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 20,	"dtcmram",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 21,	"dma1",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 22,	"dma2",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 23,	"dma2d",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 25,	"ethmac",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 26,	"ethmactx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 27,	"ethmacrx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 28,	"ethmacptp",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 29,	"otghs",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 30,	"otghsulpi",	"ahb_div" पूर्ण,

	अणु STM32F4_RCC_AHB2ENR,  0,	"dcmi",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  4,	"cryp",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  5,	"hash",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  6,	"rng",		"pll48"   पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  7,	"otgfs",	"pll48"   पूर्ण,

	अणु STM32F4_RCC_AHB3ENR,  0,	"fmc",		"ahb_div",
		CLK_IGNORE_UNUSED पूर्ण,
	अणु STM32F4_RCC_AHB3ENR,  1,	"qspi",		"ahb_div",
		CLK_IGNORE_UNUSED पूर्ण,

	अणु STM32F4_RCC_APB1ENR,  0,	"tim2",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  1,	"tim3",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  2,	"tim4",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  3,	"tim5",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  4,	"tim6",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  5,	"tim7",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  6,	"tim12",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  7,	"tim13",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  8,	"tim14",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 11,	"wwdg",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 14,	"spi2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 15,	"spi3",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 16,	"spdifrx",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 25,	"can1",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 26,	"can2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 27,	"cec",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 28,	"pwr",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 29,	"dac",		"apb1_div" पूर्ण,

	अणु STM32F4_RCC_APB2ENR,  0,	"tim1",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  1,	"tim8",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  7,	"sdmmc2",	"sdmux"    पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  8,	"adc1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  9,	"adc2",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 10,	"adc3",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 11,	"sdmmc",	"sdmux"    पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 12,	"spi1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 13,	"spi4",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 14,	"syscfg",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 16,	"tim9",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 17,	"tim10",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 18,	"tim11",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 20,	"spi5",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 21,	"spi6",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 22,	"sai1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 23,	"sai2",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 26,	"ltdc",		"apb2_div" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_gate_data sपंचांग32f769_gates[] __initस्थिर = अणु
	अणु STM32F4_RCC_AHB1ENR,  0,	"gpioa",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  1,	"gpiob",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  2,	"gpioc",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  3,	"gpiod",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  4,	"gpioe",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  5,	"gpiof",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  6,	"gpiog",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  7,	"gpioh",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  8,	"gpioi",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR,  9,	"gpioj",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 10,	"gpiok",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 12,	"crc",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 18,	"bkpsra",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 20,	"dtcmram",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 21,	"dma1",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 22,	"dma2",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 23,	"dma2d",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 25,	"ethmac",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 26,	"ethmactx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 27,	"ethmacrx",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 28,	"ethmacptp",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 29,	"otghs",	"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB1ENR, 30,	"otghsulpi",	"ahb_div" पूर्ण,

	अणु STM32F4_RCC_AHB2ENR,  0,	"dcmi",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  1,	"jpeg",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  4,	"cryp",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  5,	"hash",		"ahb_div" पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  6,	"rng",		"pll48"   पूर्ण,
	अणु STM32F4_RCC_AHB2ENR,  7,	"otgfs",	"pll48"   पूर्ण,

	अणु STM32F4_RCC_AHB3ENR,  0,	"fmc",		"ahb_div",
		CLK_IGNORE_UNUSED पूर्ण,
	अणु STM32F4_RCC_AHB3ENR,  1,	"qspi",		"ahb_div",
		CLK_IGNORE_UNUSED पूर्ण,

	अणु STM32F4_RCC_APB1ENR,  0,	"tim2",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  1,	"tim3",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  2,	"tim4",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  3,	"tim5",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  4,	"tim6",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  5,	"tim7",		"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  6,	"tim12",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  7,	"tim13",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR,  8,	"tim14",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 10,	"rtcapb",	"apb1_mul" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 11,	"wwdg",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 13,	"can3",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 14,	"spi2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 15,	"spi3",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 16,	"spdifrx",	"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 25,	"can1",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 26,	"can2",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 27,	"cec",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 28,	"pwr",		"apb1_div" पूर्ण,
	अणु STM32F4_RCC_APB1ENR, 29,	"dac",		"apb1_div" पूर्ण,

	अणु STM32F4_RCC_APB2ENR,  0,	"tim1",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  1,	"tim8",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  7,	"sdmmc2",	"sdmux2" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  8,	"adc1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR,  9,	"adc2",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 10,	"adc3",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 11,	"sdmmc1",	"sdmux1" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 12,	"spi1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 13,	"spi4",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 14,	"syscfg",	"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 16,	"tim9",		"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 17,	"tim10",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 18,	"tim11",	"apb2_mul" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 20,	"spi5",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 21,	"spi6",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 22,	"sai1",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 23,	"sai2",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 26,	"ltdc",		"apb2_div" पूर्ण,
	अणु STM32F4_RCC_APB2ENR, 30,	"mdio",		"apb2_div" पूर्ण,
पूर्ण;

/*
 * This biपंचांगask tells us which bit offsets (0..192) on STM32F4[23]xxx
 * have gate bits associated with them. Its combined hweight is 71.
 */
#घोषणा MAX_GATE_MAP 3

अटल स्थिर u64 sपंचांग32f42xx_gate_map[MAX_GATE_MAP] = अणु 0x000000f17ef417ffull,
						       0x0000000000000001ull,
						       0x04777f33f6fec9ffull पूर्ण;

अटल स्थिर u64 sपंचांग32f46xx_gate_map[MAX_GATE_MAP] = अणु 0x000000f17ef417ffull,
						       0x0000000000000003ull,
						       0x0c777f33f6fec9ffull पूर्ण;

अटल स्थिर u64 sपंचांग32f746_gate_map[MAX_GATE_MAP] = अणु 0x000000f17ef417ffull,
						      0x0000000000000003ull,
						      0x04f77f833e01c9ffull पूर्ण;

अटल स्थिर u64 sपंचांग32f769_gate_map[MAX_GATE_MAP] = अणु 0x000000f37ef417ffull,
						      0x0000000000000003ull,
						      0x44F77F833E01EDFFull पूर्ण;

अटल स्थिर u64 *sपंचांग32f4_gate_map;

अटल काष्ठा clk_hw **clks;

अटल DEFINE_SPINLOCK(sपंचांग32f4_clk_lock);
अटल व्योम __iomem *base;

अटल काष्ठा regmap *pdrm;

अटल पूर्णांक sपंचांग32fx_end_primary_clk;

/*
 * "Multiplier" device क्रम APBx घड़ीs.
 *
 * The APBx भागiders are घातer-of-two भागiders and, अगर *not* running in 1:1
 * mode, they also tap out the one of the low order state bits to run the
 * समयrs. ST datasheets represent this feature as a (conditional) घड़ी
 * multiplier.
 */
काष्ठा clk_apb_mul अणु
	काष्ठा clk_hw hw;
	u8 bit_idx;
पूर्ण;

#घोषणा to_clk_apb_mul(_hw) container_of(_hw, काष्ठा clk_apb_mul, hw)

अटल अचिन्हित दीर्घ clk_apb_mul_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_apb_mul *am = to_clk_apb_mul(hw);

	अगर (पढ़ोl(base + STM32F4_RCC_CFGR) & BIT(am->bit_idx))
		वापस parent_rate * 2;

	वापस parent_rate;
पूर्ण

अटल दीर्घ clk_apb_mul_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_apb_mul *am = to_clk_apb_mul(hw);
	अचिन्हित दीर्घ mult = 1;

	अगर (पढ़ोl(base + STM32F4_RCC_CFGR) & BIT(am->bit_idx))
		mult = 2;

	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		अचिन्हित दीर्घ best_parent = rate / mult;

		*prate = clk_hw_round_rate(clk_hw_get_parent(hw), best_parent);
	पूर्ण

	वापस *prate * mult;
पूर्ण

अटल पूर्णांक clk_apb_mul_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	/*
	 * We must report success but we can करो so unconditionally because
	 * clk_apb_mul_round_rate वापसs values that ensure this call is a
	 * nop.
	 */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_apb_mul_factor_ops = अणु
	.round_rate = clk_apb_mul_round_rate,
	.set_rate = clk_apb_mul_set_rate,
	.recalc_rate = clk_apb_mul_recalc_rate,
पूर्ण;

अटल काष्ठा clk *clk_रेजिस्टर_apb_mul(काष्ठा device *dev, स्थिर अक्षर *name,
					स्थिर अक्षर *parent_name,
					अचिन्हित दीर्घ flags, u8 bit_idx)
अणु
	काष्ठा clk_apb_mul *am;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	am = kzalloc(माप(*am), GFP_KERNEL);
	अगर (!am)
		वापस ERR_PTR(-ENOMEM);

	am->bit_idx = bit_idx;
	am->hw.init = &init;

	init.name = name;
	init.ops = &clk_apb_mul_factor_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	clk = clk_रेजिस्टर(dev, &am->hw);

	अगर (IS_ERR(clk))
		kमुक्त(am);

	वापस clk;
पूर्ण

क्रमागत अणु
	PLL,
	PLL_I2S,
	PLL_SAI,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable pll_भागp_table[] = अणु
	अणु 0, 2 पूर्ण, अणु 1, 4 पूर्ण, अणु 2, 6 पूर्ण, अणु 3, 8 पूर्ण, अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable pll_भागq_table[] = अणु
	अणु 2, 2 पूर्ण, अणु 3, 3 पूर्ण, अणु 4, 4 पूर्ण, अणु 5, 5 पूर्ण, अणु 6, 6 पूर्ण, अणु 7, 7 पूर्ण,
	अणु 8, 8 पूर्ण, अणु 9, 9 पूर्ण, अणु 10, 10 पूर्ण, अणु 11, 11 पूर्ण, अणु 12, 12 पूर्ण, अणु 13, 13 पूर्ण,
	अणु 14, 14 पूर्ण, अणु 15, 15 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable pll_भागr_table[] = अणु
	अणु 2, 2 पूर्ण, अणु 3, 3 पूर्ण, अणु 4, 4 पूर्ण, अणु 5, 5 पूर्ण, अणु 6, 6 पूर्ण, अणु 7, 7 पूर्ण, अणु 0 पूर्ण
पूर्ण;

काष्ठा sपंचांग32f4_pll अणु
	spinlock_t *lock;
	काष्ठा	clk_gate gate;
	u8 offset;
	u8 bit_rdy_idx;
	u8 status;
	u8 n_start;
पूर्ण;

#घोषणा to_sपंचांग32f4_pll(_gate) container_of(_gate, काष्ठा sपंचांग32f4_pll, gate)

काष्ठा sपंचांग32f4_pll_post_भाग_data अणु
	पूर्णांक idx;
	u8 pll_num;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
	u8 flag;
	u8 offset;
	u8 shअगरt;
	u8 width;
	u8 flag_भाग;
	स्थिर काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable;
पूर्ण;

काष्ठा sपंचांग32f4_vco_data अणु
	स्थिर अक्षर *vco_name;
	u8 offset;
	u8 bit_idx;
	u8 bit_rdy_idx;
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_vco_data  vco_data[] = अणु
	अणु "vco",     STM32F4_RCC_PLLCFGR,    24, 25 पूर्ण,
	अणु "vco-i2s", STM32F4_RCC_PLLI2SCFGR, 26, 27 पूर्ण,
	अणु "vco-sai", STM32F4_RCC_PLLSAICFGR, 28, 29 पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा clk_भाग_प्रकारable post_भागr_table[] = अणु
	अणु 0, 2 पूर्ण, अणु 1, 4 पूर्ण, अणु 2, 8 पूर्ण, अणु 3, 16 पूर्ण, अणु 0 पूर्ण
पूर्ण;

#घोषणा MAX_POST_DIV 3
अटल स्थिर काष्ठा sपंचांग32f4_pll_post_भाग_data  post_भाग_data[MAX_POST_DIV] = अणु
	अणु CLK_I2SQ_PDIV, PLL_I2S, "plli2s-q-div", "plli2s-q",
		CLK_SET_RATE_PARENT, STM32F4_RCC_DCKCFGR, 0, 5, 0, शून्यपूर्ण,

	अणु CLK_SAIQ_PDIV, PLL_SAI, "pllsai-q-div", "pllsai-q",
		CLK_SET_RATE_PARENT, STM32F4_RCC_DCKCFGR, 8, 5, 0, शून्य पूर्ण,

	अणु NO_IDX, PLL_SAI, "pllsai-r-div", "pllsai-r", CLK_SET_RATE_PARENT,
		STM32F4_RCC_DCKCFGR, 16, 2, 0, post_भागr_table पूर्ण,
पूर्ण;

काष्ठा sपंचांग32f4_भाग_data अणु
	u8 shअगरt;
	u8 width;
	u8 flag_भाग;
	स्थिर काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable;
पूर्ण;

#घोषणा MAX_PLL_DIV 3
अटल स्थिर काष्ठा sपंचांग32f4_भाग_data  भाग_data[MAX_PLL_DIV] = अणु
	अणु 16, 2, 0, pll_भागp_table पूर्ण,
	अणु 24, 4, 0, pll_भागq_table पूर्ण,
	अणु 28, 3, 0, pll_भागr_table पूर्ण,
पूर्ण;

काष्ठा sपंचांग32f4_pll_data अणु
	u8 pll_num;
	u8 n_start;
	स्थिर अक्षर *भाग_name[MAX_PLL_DIV];
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_pll_data sपंचांग32f429_pll[MAX_PLL_DIV] = अणु
	अणु PLL,	   192, अणु "pll", "pll48",    शून्य	पूर्ण पूर्ण,
	अणु PLL_I2S, 192, अणु शून्य,  "plli2s-q", "plli2s-r" पूर्ण पूर्ण,
	अणु PLL_SAI,  49, अणु शून्य,  "pllsai-q", "pllsai-r" पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_pll_data sपंचांग32f469_pll[MAX_PLL_DIV] = अणु
	अणु PLL,	   50, अणु "pll",	     "pll-q",    "pll-r"    पूर्ण पूर्ण,
	अणु PLL_I2S, 50, अणु "plli2s-p", "plli2s-q", "plli2s-r" पूर्ण पूर्ण,
	अणु PLL_SAI, 50, अणु "pllsai-p", "pllsai-q", "pllsai-r" पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32f4_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	वापस clk_gate_ops.is_enabled(hw);
पूर्ण

#घोषणा PLL_TIMEOUT 10000

अटल पूर्णांक sपंचांग32f4_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32f4_pll *pll = to_sपंचांग32f4_pll(gate);
	पूर्णांक bit_status;
	अचिन्हित पूर्णांक समयout = PLL_TIMEOUT;

	अगर (clk_gate_ops.is_enabled(hw))
		वापस 0;

	clk_gate_ops.enable(hw);

	करो अणु
		bit_status = !(पढ़ोl(gate->reg) & BIT(pll->bit_rdy_idx));

	पूर्ण जबतक (bit_status && --समयout);

	वापस bit_status;
पूर्ण

अटल व्योम sपंचांग32f4_pll_disable(काष्ठा clk_hw *hw)
अणु
	clk_gate_ops.disable(hw);
पूर्ण

अटल अचिन्हित दीर्घ sपंचांग32f4_pll_recalc(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32f4_pll *pll = to_sपंचांग32f4_pll(gate);
	अचिन्हित दीर्घ n;

	n = (पढ़ोl(base + pll->offset) >> 6) & 0x1ff;

	वापस parent_rate * n;
पूर्ण

अटल दीर्घ sपंचांग32f4_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32f4_pll *pll = to_sपंचांग32f4_pll(gate);
	अचिन्हित दीर्घ n;

	n = rate / *prate;

	अगर (n < pll->n_start)
		n = pll->n_start;
	अन्यथा अगर (n > 432)
		n = 432;

	वापस *prate * n;
पूर्ण

अटल पूर्णांक sपंचांग32f4_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32f4_pll *pll = to_sपंचांग32f4_pll(gate);

	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ val;
	पूर्णांक pll_state;

	pll_state = sपंचांग32f4_pll_is_enabled(hw);

	अगर (pll_state)
		sपंचांग32f4_pll_disable(hw);

	n = rate  / parent_rate;

	val = पढ़ोl(base + pll->offset) & ~(0x1ff << 6);

	ग_लिखोl(val | ((n & 0x1ff) <<  6), base + pll->offset);

	अगर (pll_state)
		sपंचांग32f4_pll_enable(hw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sपंचांग32f4_pll_gate_ops = अणु
	.enable		= sपंचांग32f4_pll_enable,
	.disable	= sपंचांग32f4_pll_disable,
	.is_enabled	= sपंचांग32f4_pll_is_enabled,
	.recalc_rate	= sपंचांग32f4_pll_recalc,
	.round_rate	= sपंचांग32f4_pll_round_rate,
	.set_rate	= sपंचांग32f4_pll_set_rate,
पूर्ण;

काष्ठा sपंचांग32f4_pll_भाग अणु
	काष्ठा clk_भागider भाग;
	काष्ठा clk_hw *hw_pll;
पूर्ण;

#घोषणा to_pll_भाग_clk(_भाग) container_of(_भाग, काष्ठा sपंचांग32f4_pll_भाग, भाग)

अटल अचिन्हित दीर्घ sपंचांग32f4_pll_भाग_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	वापस clk_भागider_ops.recalc_rate(hw, parent_rate);
पूर्ण

अटल दीर्घ sपंचांग32f4_pll_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	वापस clk_भागider_ops.round_rate(hw, rate, prate);
पूर्ण

अटल पूर्णांक sपंचांग32f4_pll_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक pll_state, ret;

	काष्ठा clk_भागider *भाग = to_clk_भागider(hw);
	काष्ठा sपंचांग32f4_pll_भाग *pll_भाग = to_pll_भाग_clk(भाग);

	pll_state = sपंचांग32f4_pll_is_enabled(pll_भाग->hw_pll);

	अगर (pll_state)
		sपंचांग32f4_pll_disable(pll_भाग->hw_pll);

	ret = clk_भागider_ops.set_rate(hw, rate, parent_rate);

	अगर (pll_state)
		sपंचांग32f4_pll_enable(pll_भाग->hw_pll);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops sपंचांग32f4_pll_भाग_ops = अणु
	.recalc_rate = sपंचांग32f4_pll_भाग_recalc_rate,
	.round_rate = sपंचांग32f4_pll_भाग_round_rate,
	.set_rate = sपंचांग32f4_pll_भाग_set_rate,
पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_pll_भाग(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 shअगरt, u8 width,
		u8 clk_भागider_flags, स्थिर काष्ठा clk_भाग_प्रकारable *table,
		काष्ठा clk_hw *pll_hw, spinlock_t *lock)
अणु
	काष्ठा sपंचांग32f4_pll_भाग *pll_भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	/* allocate the भागider */
	pll_भाग = kzalloc(माप(*pll_भाग), GFP_KERNEL);
	अगर (!pll_भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &sपंचांग32f4_pll_भाग_ops;
	init.flags = flags;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	/* काष्ठा clk_भागider assignments */
	pll_भाग->भाग.reg = reg;
	pll_भाग->भाग.shअगरt = shअगरt;
	pll_भाग->भाग.width = width;
	pll_भाग->भाग.flags = clk_भागider_flags;
	pll_भाग->भाग.lock = lock;
	pll_भाग->भाग.table = table;
	pll_भाग->भाग.hw.init = &init;

	pll_भाग->hw_pll = pll_hw;

	/* रेजिस्टर the घड़ी */
	hw = &pll_भाग->भाग.hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(pll_भाग);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल काष्ठा clk_hw *sपंचांग32f4_rcc_रेजिस्टर_pll(स्थिर अक्षर *pllsrc,
		स्थिर काष्ठा sपंचांग32f4_pll_data *data,  spinlock_t *lock)
अणु
	काष्ठा sपंचांग32f4_pll *pll;
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	व्योम __iomem *reg;
	काष्ठा clk_hw *pll_hw;
	पूर्णांक ret;
	पूर्णांक i;
	स्थिर काष्ठा sपंचांग32f4_vco_data *vco;


	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	vco = &vco_data[data->pll_num];

	init.name = vco->vco_name;
	init.ops = &sपंचांग32f4_pll_gate_ops;
	init.flags = CLK_SET_RATE_GATE;
	init.parent_names = &pllsrc;
	init.num_parents = 1;

	pll->gate.lock = lock;
	pll->gate.reg = base + STM32F4_RCC_CR;
	pll->gate.bit_idx = vco->bit_idx;
	pll->gate.hw.init = &init;

	pll->offset = vco->offset;
	pll->n_start = data->n_start;
	pll->bit_rdy_idx = vco->bit_rdy_idx;
	pll->status = (पढ़ोl(base + STM32F4_RCC_CR) >> vco->bit_idx) & 0x1;

	reg = base + pll->offset;

	pll_hw = &pll->gate.hw;
	ret = clk_hw_रेजिस्टर(शून्य, pll_hw);
	अगर (ret) अणु
		kमुक्त(pll);
		वापस ERR_PTR(ret);
	पूर्ण

	क्रम (i = 0; i < MAX_PLL_DIV; i++)
		अगर (data->भाग_name[i])
			clk_रेजिस्टर_pll_भाग(data->भाग_name[i],
					vco->vco_name,
					0,
					reg,
					भाग_data[i].shअगरt,
					भाग_data[i].width,
					भाग_data[i].flag_भाग,
					भाग_data[i].भाग_प्रकारable,
					pll_hw,
					lock);
	वापस pll_hw;
पूर्ण

/*
 * Converts the primary and secondary indices (as they appear in DT) to an
 * offset पूर्णांकo our काष्ठा घड़ी array.
 */
अटल पूर्णांक sपंचांग32f4_rcc_lookup_clk_idx(u8 primary, u8 secondary)
अणु
	u64 table[MAX_GATE_MAP];

	अगर (primary == 1) अणु
		अगर (WARN_ON(secondary >= sपंचांग32fx_end_primary_clk))
			वापस -EINVAL;
		वापस secondary;
	पूर्ण

	स_नकल(table, sपंचांग32f4_gate_map, माप(table));

	/* only bits set in table can be used as indices */
	अगर (WARN_ON(secondary >= BITS_PER_BYTE * माप(table) ||
		    0 == (table[BIT_ULL_WORD(secondary)] &
			  BIT_ULL_MASK(secondary))))
		वापस -EINVAL;

	/* mask out bits above our current index */
	table[BIT_ULL_WORD(secondary)] &=
	    GENMASK_ULL(secondary % BITS_PER_LONG_LONG, 0);

	वापस sपंचांग32fx_end_primary_clk - 1 + hweight64(table[0]) +
	       (BIT_ULL_WORD(secondary) >= 1 ? hweight64(table[1]) : 0) +
	       (BIT_ULL_WORD(secondary) >= 2 ? hweight64(table[2]) : 0);
पूर्ण

अटल काष्ठा clk_hw *
sपंचांग32f4_rcc_lookup_clk(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	पूर्णांक i = sपंचांग32f4_rcc_lookup_clk_idx(clkspec->args[0], clkspec->args[1]);

	अगर (i < 0)
		वापस ERR_PTR(-EINVAL);

	वापस clks[i];
पूर्ण

#घोषणा to_rgclk(_rgate) container_of(_rgate, काष्ठा sपंचांग32_rgate, gate)

अटल अंतरभूत व्योम disable_घातer_करोमुख्य_ग_लिखो_protection(व्योम)
अणु
	अगर (pdrm)
		regmap_update_bits(pdrm, 0x00, (1 << 8), (1 << 8));
पूर्ण

अटल अंतरभूत व्योम enable_घातer_करोमुख्य_ग_लिखो_protection(व्योम)
अणु
	अगर (pdrm)
		regmap_update_bits(pdrm, 0x00, (1 << 8), (0 << 8));
पूर्ण

अटल अंतरभूत व्योम sofware_reset_backup_करोमुख्य(व्योम)
अणु
	अचिन्हित दीर्घ val;

	val = पढ़ोl(base + STM32F4_RCC_BDCR);
	ग_लिखोl(val | BIT(16), base + STM32F4_RCC_BDCR);
	ग_लिखोl(val & ~BIT(16), base + STM32F4_RCC_BDCR);
पूर्ण

काष्ठा sपंचांग32_rgate अणु
	काष्ठा	clk_gate gate;
	u8	bit_rdy_idx;
पूर्ण;

#घोषणा RGATE_TIMEOUT 50000

अटल पूर्णांक rgclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gate *gate = to_clk_gate(hw);
	काष्ठा sपंचांग32_rgate *rgate = to_rgclk(gate);
	पूर्णांक bit_status;
	अचिन्हित पूर्णांक समयout = RGATE_TIMEOUT;

	अगर (clk_gate_ops.is_enabled(hw))
		वापस 0;

	disable_घातer_करोमुख्य_ग_लिखो_protection();

	clk_gate_ops.enable(hw);

	करो अणु
		bit_status = !(पढ़ोl(gate->reg) & BIT(rgate->bit_rdy_idx));
		अगर (bit_status)
			udelay(100);

	पूर्ण जबतक (bit_status && --समयout);

	enable_घातer_करोमुख्य_ग_लिखो_protection();

	वापस bit_status;
पूर्ण

अटल व्योम rgclk_disable(काष्ठा clk_hw *hw)
अणु
	clk_gate_ops.disable(hw);
पूर्ण

अटल पूर्णांक rgclk_is_enabled(काष्ठा clk_hw *hw)
अणु
	वापस clk_gate_ops.is_enabled(hw);
पूर्ण

अटल स्थिर काष्ठा clk_ops rgclk_ops = अणु
	.enable = rgclk_enable,
	.disable = rgclk_disable,
	.is_enabled = rgclk_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_rgate(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 bit_idx, u8 bit_rdy_idx,
		u8 clk_gate_flags, spinlock_t *lock)
अणु
	काष्ठा sपंचांग32_rgate *rgate;
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	rgate = kzalloc(माप(*rgate), GFP_KERNEL);
	अगर (!rgate)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &rgclk_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	rgate->bit_rdy_idx = bit_rdy_idx;

	rgate->gate.lock = lock;
	rgate->gate.reg = reg;
	rgate->gate.bit_idx = bit_idx;
	rgate->gate.hw.init = &init;

	hw = &rgate->gate.hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(rgate);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल पूर्णांक cclk_gate_enable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;

	disable_घातer_करोमुख्य_ग_लिखो_protection();

	ret = clk_gate_ops.enable(hw);

	enable_घातer_करोमुख्य_ग_लिखो_protection();

	वापस ret;
पूर्ण

अटल व्योम cclk_gate_disable(काष्ठा clk_hw *hw)
अणु
	disable_घातer_करोमुख्य_ग_लिखो_protection();

	clk_gate_ops.disable(hw);

	enable_घातer_करोमुख्य_ग_लिखो_protection();
पूर्ण

अटल पूर्णांक cclk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	वापस clk_gate_ops.is_enabled(hw);
पूर्ण

अटल स्थिर काष्ठा clk_ops cclk_gate_ops = अणु
	.enable		= cclk_gate_enable,
	.disable	= cclk_gate_disable,
	.is_enabled	= cclk_gate_is_enabled,
पूर्ण;

अटल u8 cclk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	वापस clk_mux_ops.get_parent(hw);
पूर्ण

अटल पूर्णांक cclk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	पूर्णांक ret;

	disable_घातer_करोमुख्य_ग_लिखो_protection();

	sofware_reset_backup_करोमुख्य();

	ret = clk_mux_ops.set_parent(hw, index);

	enable_घातer_करोमुख्य_ग_लिखो_protection();

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops cclk_mux_ops = अणु
	.get_parent = cclk_mux_get_parent,
	.set_parent = cclk_mux_set_parent,
पूर्ण;

अटल काष्ठा clk_hw *sपंचांग32_रेजिस्टर_cclk(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		व्योम __iomem *reg, u8 bit_idx, u8 shअगरt, अचिन्हित दीर्घ flags,
		spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_gate *gate;
	काष्ठा clk_mux *mux;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate) अणु
		hw = ERR_PTR(-EINVAL);
		जाओ fail;
	पूर्ण

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux) अणु
		kमुक्त(gate);
		hw = ERR_PTR(-EINVAL);
		जाओ fail;
	पूर्ण

	gate->reg = reg;
	gate->bit_idx = bit_idx;
	gate->flags = 0;
	gate->lock = lock;

	mux->reg = reg;
	mux->shअगरt = shअगरt;
	mux->mask = 3;
	mux->flags = 0;

	hw = clk_hw_रेजिस्टर_composite(dev, name, parent_names, num_parents,
			&mux->hw, &cclk_mux_ops,
			शून्य, शून्य,
			&gate->hw, &cclk_gate_ops,
			flags);

	अगर (IS_ERR(hw)) अणु
		kमुक्त(gate);
		kमुक्त(mux);
	पूर्ण

fail:
	वापस hw;
पूर्ण

अटल स्थिर अक्षर *sys_parents[] __initdata =   अणु "hsi", शून्य, "pll" पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable ahb_भाग_प्रकारable[] = अणु
	अणु 0x0,   1 पूर्ण, अणु 0x1,   1 पूर्ण, अणु 0x2,   1 पूर्ण, अणु 0x3,   1 पूर्ण,
	अणु 0x4,   1 पूर्ण, अणु 0x5,   1 पूर्ण, अणु 0x6,   1 पूर्ण, अणु 0x7,   1 पूर्ण,
	अणु 0x8,   2 पूर्ण, अणु 0x9,   4 पूर्ण, अणु 0xa,   8 पूर्ण, अणु 0xb,  16 पूर्ण,
	अणु 0xc,  64 पूर्ण, अणु 0xd, 128 पूर्ण, अणु 0xe, 256 पूर्ण, अणु 0xf, 512 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable apb_भाग_प्रकारable[] = अणु
	अणु 0,  1 पूर्ण, अणु 0,  1 पूर्ण, अणु 0,  1 पूर्ण, अणु 0,  1 पूर्ण,
	अणु 4,  2 पूर्ण, अणु 5,  4 पूर्ण, अणु 6,  8 पूर्ण, अणु 7, 16 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *rtc_parents[4] = अणु
	"no-clock", "lse", "lsi", "hse-rtc"
पूर्ण;

अटल स्थिर अक्षर *pll_src = "pll-src";

अटल स्थिर अक्षर *pllsrc_parent[2] = अणु "hsi", शून्य पूर्ण;

अटल स्थिर अक्षर *dsi_parent[2] = अणु शून्य, "pll-r" पूर्ण;

अटल स्थिर अक्षर *lcd_parent[1] = अणु "pllsai-r-div" पूर्ण;

अटल स्थिर अक्षर *i2s_parents[2] = अणु "plli2s-r", शून्य पूर्ण;

अटल स्थिर अक्षर *sai_parents[4] = अणु "pllsai-q-div", "plli2s-q-div", शून्य,
	"no-clock" पूर्ण;

अटल स्थिर अक्षर *pll48_parents[2] = अणु "pll-q", "pllsai-p" पूर्ण;

अटल स्थिर अक्षर *sdmux_parents[2] = अणु "pll48", "sys" पूर्ण;

अटल स्थिर अक्षर *hdmi_parents[2] = अणु "lse", "hsi_div488" पूर्ण;

अटल स्थिर अक्षर *spdअगर_parent[1] = अणु "plli2s-p" पूर्ण;

अटल स्थिर अक्षर *lptim_parent[4] = अणु "apb1_mul", "lsi", "hsi", "lse" पूर्ण;

अटल स्थिर अक्षर *uart_parents1[4] = अणु "apb2_div", "sys", "hsi", "lse" पूर्ण;
अटल स्थिर अक्षर *uart_parents2[4] = अणु "apb1_div", "sys", "hsi", "lse" पूर्ण;

अटल स्थिर अक्षर *i2c_parents[4] = अणु "apb1_div", "sys", "hsi", "no-clock" पूर्ण;

अटल स्थिर अक्षर * स्थिर dfsdm1_src[] = अणु "apb2_div", "sys" पूर्ण;
अटल स्थिर अक्षर * स्थिर adsfdm1_parent[] = अणु "sai1_clk", "sai2_clk" पूर्ण;

काष्ठा sपंचांग32_aux_clk अणु
	पूर्णांक idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_names;
	पूर्णांक num_parents;
	पूर्णांक offset_mux;
	u8 shअगरt;
	u8 mask;
	पूर्णांक offset_gate;
	u8 bit_idx;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा sपंचांग32f4_clk_data अणु
	स्थिर काष्ठा sपंचांग32f4_gate_data *gates_data;
	स्थिर u64 *gates_map;
	पूर्णांक gates_num;
	स्थिर काष्ठा sपंचांग32f4_pll_data *pll_data;
	स्थिर काष्ठा sपंचांग32_aux_clk *aux_clk;
	पूर्णांक aux_clk_num;
	पूर्णांक end_primary;
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_aux_clk sपंचांग32f429_aux_clk[] = अणु
	अणु
		CLK_LCD, "lcd-tft", lcd_parent, ARRAY_SIZE(lcd_parent),
		NO_MUX, 0, 0,
		STM32F4_RCC_APB2ENR, 26,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_I2S, "i2s", i2s_parents, ARRAY_SIZE(i2s_parents),
		STM32F4_RCC_CFGR, 23, 1,
		NO_GATE, 0,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI1, "sai1-a", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 20, 3,
		STM32F4_RCC_APB2ENR, 22,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI2, "sai1-b", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 22, 3,
		STM32F4_RCC_APB2ENR, 22,
		CLK_SET_RATE_PARENT
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_aux_clk sपंचांग32f469_aux_clk[] = अणु
	अणु
		CLK_LCD, "lcd-tft", lcd_parent, ARRAY_SIZE(lcd_parent),
		NO_MUX, 0, 0,
		STM32F4_RCC_APB2ENR, 26,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_I2S, "i2s", i2s_parents, ARRAY_SIZE(i2s_parents),
		STM32F4_RCC_CFGR, 23, 1,
		NO_GATE, 0,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI1, "sai1-a", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 20, 3,
		STM32F4_RCC_APB2ENR, 22,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI2, "sai1-b", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 22, 3,
		STM32F4_RCC_APB2ENR, 22,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		NO_IDX, "pll48", pll48_parents, ARRAY_SIZE(pll48_parents),
		STM32F4_RCC_DCKCFGR, 27, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		NO_IDX, "sdmux", sdmux_parents, ARRAY_SIZE(sdmux_parents),
		STM32F4_RCC_DCKCFGR, 28, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		CLK_F469_DSI, "dsi", dsi_parent, ARRAY_SIZE(dsi_parent),
		STM32F4_RCC_DCKCFGR, 29, 1,
		STM32F4_RCC_APB2ENR, 27,
		CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_aux_clk sपंचांग32f746_aux_clk[] = अणु
	अणु
		CLK_LCD, "lcd-tft", lcd_parent, ARRAY_SIZE(lcd_parent),
		NO_MUX, 0, 0,
		STM32F4_RCC_APB2ENR, 26,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_I2S, "i2s", i2s_parents, ARRAY_SIZE(i2s_parents),
		STM32F4_RCC_CFGR, 23, 1,
		NO_GATE, 0,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI1, "sai1_clk", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 20, 3,
		STM32F4_RCC_APB2ENR, 22,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI2, "sai2_clk", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 22, 3,
		STM32F4_RCC_APB2ENR, 23,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		NO_IDX, "pll48", pll48_parents, ARRAY_SIZE(pll48_parents),
		STM32F7_RCC_DCKCFGR2, 27, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		NO_IDX, "sdmux", sdmux_parents, ARRAY_SIZE(sdmux_parents),
		STM32F7_RCC_DCKCFGR2, 28, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		CLK_HDMI_CEC, "hdmi-cec",
		hdmi_parents, ARRAY_SIZE(hdmi_parents),
		STM32F7_RCC_DCKCFGR2, 26, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		CLK_SPDIF, "spdif-rx",
		spdअगर_parent, ARRAY_SIZE(spdअगर_parent),
		STM32F7_RCC_DCKCFGR2, 22, 3,
		STM32F4_RCC_APB2ENR, 23,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_USART1, "usart1",
		uart_parents1, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 0, 3,
		STM32F4_RCC_APB2ENR, 4,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_USART2, "usart2",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 2, 3,
		STM32F4_RCC_APB1ENR, 17,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_USART3, "usart3",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 4, 3,
		STM32F4_RCC_APB1ENR, 18,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_UART4, "uart4",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 6, 3,
		STM32F4_RCC_APB1ENR, 19,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_UART5, "uart5",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 8, 3,
		STM32F4_RCC_APB1ENR, 20,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_USART6, "usart6",
		uart_parents1, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 10, 3,
		STM32F4_RCC_APB2ENR, 5,
		CLK_SET_RATE_PARENT,
	पूर्ण,

	अणु
		CLK_UART7, "uart7",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 12, 3,
		STM32F4_RCC_APB1ENR, 30,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_UART8, "uart8",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 14, 3,
		STM32F4_RCC_APB1ENR, 31,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C1, "i2c1",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 16, 3,
		STM32F4_RCC_APB1ENR, 21,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C2, "i2c2",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 18, 3,
		STM32F4_RCC_APB1ENR, 22,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C3, "i2c3",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 20, 3,
		STM32F4_RCC_APB1ENR, 23,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C4, "i2c4",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 22, 3,
		STM32F4_RCC_APB1ENR, 24,
		CLK_SET_RATE_PARENT,
	पूर्ण,

	अणु
		CLK_LPTIMER, "lptim1",
		lptim_parent, ARRAY_SIZE(lptim_parent),
		STM32F7_RCC_DCKCFGR2, 24, 3,
		STM32F4_RCC_APB1ENR, 9,
		CLK_SET_RATE_PARENT
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_aux_clk sपंचांग32f769_aux_clk[] = अणु
	अणु
		CLK_LCD, "lcd-tft", lcd_parent, ARRAY_SIZE(lcd_parent),
		NO_MUX, 0, 0,
		STM32F4_RCC_APB2ENR, 26,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_I2S, "i2s", i2s_parents, ARRAY_SIZE(i2s_parents),
		STM32F4_RCC_CFGR, 23, 1,
		NO_GATE, 0,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI1, "sai1_clk", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 20, 3,
		STM32F4_RCC_APB2ENR, 22,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_SAI2, "sai2_clk", sai_parents, ARRAY_SIZE(sai_parents),
		STM32F4_RCC_DCKCFGR, 22, 3,
		STM32F4_RCC_APB2ENR, 23,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		NO_IDX, "pll48", pll48_parents, ARRAY_SIZE(pll48_parents),
		STM32F7_RCC_DCKCFGR2, 27, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		NO_IDX, "sdmux1", sdmux_parents, ARRAY_SIZE(sdmux_parents),
		STM32F7_RCC_DCKCFGR2, 28, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		NO_IDX, "sdmux2", sdmux_parents, ARRAY_SIZE(sdmux_parents),
		STM32F7_RCC_DCKCFGR2, 29, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		CLK_HDMI_CEC, "hdmi-cec",
		hdmi_parents, ARRAY_SIZE(hdmi_parents),
		STM32F7_RCC_DCKCFGR2, 26, 1,
		NO_GATE, 0,
		0
	पूर्ण,
	अणु
		CLK_SPDIF, "spdif-rx",
		spdअगर_parent, ARRAY_SIZE(spdअगर_parent),
		STM32F7_RCC_DCKCFGR2, 22, 3,
		STM32F4_RCC_APB2ENR, 23,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_USART1, "usart1",
		uart_parents1, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 0, 3,
		STM32F4_RCC_APB2ENR, 4,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_USART2, "usart2",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 2, 3,
		STM32F4_RCC_APB1ENR, 17,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_USART3, "usart3",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 4, 3,
		STM32F4_RCC_APB1ENR, 18,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_UART4, "uart4",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 6, 3,
		STM32F4_RCC_APB1ENR, 19,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_UART5, "uart5",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 8, 3,
		STM32F4_RCC_APB1ENR, 20,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_USART6, "usart6",
		uart_parents1, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 10, 3,
		STM32F4_RCC_APB2ENR, 5,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_UART7, "uart7",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 12, 3,
		STM32F4_RCC_APB1ENR, 30,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_UART8, "uart8",
		uart_parents2, ARRAY_SIZE(uart_parents1),
		STM32F7_RCC_DCKCFGR2, 14, 3,
		STM32F4_RCC_APB1ENR, 31,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C1, "i2c1",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 16, 3,
		STM32F4_RCC_APB1ENR, 21,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C2, "i2c2",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 18, 3,
		STM32F4_RCC_APB1ENR, 22,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C3, "i2c3",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 20, 3,
		STM32F4_RCC_APB1ENR, 23,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_I2C4, "i2c4",
		i2c_parents, ARRAY_SIZE(i2c_parents),
		STM32F7_RCC_DCKCFGR2, 22, 3,
		STM32F4_RCC_APB1ENR, 24,
		CLK_SET_RATE_PARENT,
	पूर्ण,
	अणु
		CLK_LPTIMER, "lptim1",
		lptim_parent, ARRAY_SIZE(lptim_parent),
		STM32F7_RCC_DCKCFGR2, 24, 3,
		STM32F4_RCC_APB1ENR, 9,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_F769_DSI, "dsi",
		dsi_parent, ARRAY_SIZE(dsi_parent),
		STM32F7_RCC_DCKCFGR2, 0, 1,
		STM32F4_RCC_APB2ENR, 27,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_DFSDM1, "dfsdm1",
		dfsdm1_src, ARRAY_SIZE(dfsdm1_src),
		STM32F4_RCC_DCKCFGR, 25, 1,
		STM32F4_RCC_APB2ENR, 29,
		CLK_SET_RATE_PARENT
	पूर्ण,
	अणु
		CLK_ADFSDM1, "adfsdm1",
		adsfdm1_parent, ARRAY_SIZE(adsfdm1_parent),
		STM32F4_RCC_DCKCFGR, 26, 1,
		STM32F4_RCC_APB2ENR, 29,
		CLK_SET_RATE_PARENT
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_clk_data sपंचांग32f429_clk_data = अणु
	.end_primary	= END_PRIMARY_CLK,
	.gates_data	= sपंचांग32f429_gates,
	.gates_map	= sपंचांग32f42xx_gate_map,
	.gates_num	= ARRAY_SIZE(sपंचांग32f429_gates),
	.pll_data	= sपंचांग32f429_pll,
	.aux_clk	= sपंचांग32f429_aux_clk,
	.aux_clk_num	= ARRAY_SIZE(sपंचांग32f429_aux_clk),
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_clk_data sपंचांग32f469_clk_data = अणु
	.end_primary	= END_PRIMARY_CLK,
	.gates_data	= sपंचांग32f469_gates,
	.gates_map	= sपंचांग32f46xx_gate_map,
	.gates_num	= ARRAY_SIZE(sपंचांग32f469_gates),
	.pll_data	= sपंचांग32f469_pll,
	.aux_clk	= sपंचांग32f469_aux_clk,
	.aux_clk_num	= ARRAY_SIZE(sपंचांग32f469_aux_clk),
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_clk_data sपंचांग32f746_clk_data = अणु
	.end_primary	= END_PRIMARY_CLK_F7,
	.gates_data	= sपंचांग32f746_gates,
	.gates_map	= sपंचांग32f746_gate_map,
	.gates_num	= ARRAY_SIZE(sपंचांग32f746_gates),
	.pll_data	= sपंचांग32f469_pll,
	.aux_clk	= sपंचांग32f746_aux_clk,
	.aux_clk_num	= ARRAY_SIZE(sपंचांग32f746_aux_clk),
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32f4_clk_data sपंचांग32f769_clk_data = अणु
	.end_primary	= END_PRIMARY_CLK_F7,
	.gates_data	= sपंचांग32f769_gates,
	.gates_map	= sपंचांग32f769_gate_map,
	.gates_num	= ARRAY_SIZE(sपंचांग32f769_gates),
	.pll_data	= sपंचांग32f469_pll,
	.aux_clk	= sपंचांग32f769_aux_clk,
	.aux_clk_num	= ARRAY_SIZE(sपंचांग32f769_aux_clk),
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32f4_of_match[] = अणु
	अणु
		.compatible = "st,stm32f42xx-rcc",
		.data = &sपंचांग32f429_clk_data
	पूर्ण,
	अणु
		.compatible = "st,stm32f469-rcc",
		.data = &sपंचांग32f469_clk_data
	पूर्ण,
	अणु
		.compatible = "st,stm32f746-rcc",
		.data = &sपंचांग32f746_clk_data
	पूर्ण,
	अणु
		.compatible = "st,stm32f769-rcc",
		.data = &sपंचांग32f769_clk_data
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा clk_hw *sपंचांग32_रेजिस्टर_aux_clk(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		पूर्णांक offset_mux, u8 shअगरt, u8 mask,
		पूर्णांक offset_gate, u8 bit_idx,
		अचिन्हित दीर्घ flags, spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_mux *mux = शून्य;
	काष्ठा clk_hw *mux_hw = शून्य, *gate_hw = शून्य;
	स्थिर काष्ठा clk_ops *mux_ops = शून्य, *gate_ops = शून्य;

	अगर (offset_gate != NO_GATE) अणु
		gate = kzalloc(माप(*gate), GFP_KERNEL);
		अगर (!gate) अणु
			hw = ERR_PTR(-EINVAL);
			जाओ fail;
		पूर्ण

		gate->reg = base + offset_gate;
		gate->bit_idx = bit_idx;
		gate->flags = 0;
		gate->lock = lock;
		gate_hw = &gate->hw;
		gate_ops = &clk_gate_ops;
	पूर्ण

	अगर (offset_mux != NO_MUX) अणु
		mux = kzalloc(माप(*mux), GFP_KERNEL);
		अगर (!mux) अणु
			hw = ERR_PTR(-EINVAL);
			जाओ fail;
		पूर्ण

		mux->reg = base + offset_mux;
		mux->shअगरt = shअगरt;
		mux->mask = mask;
		mux->flags = 0;
		mux_hw = &mux->hw;
		mux_ops = &clk_mux_ops;
	पूर्ण

	अगर (mux_hw == शून्य && gate_hw == शून्य) अणु
		hw = ERR_PTR(-EINVAL);
		जाओ fail;
	पूर्ण

	hw = clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
			mux_hw, mux_ops,
			शून्य, शून्य,
			gate_hw, gate_ops,
			flags);

fail:
	अगर (IS_ERR(hw)) अणु
		kमुक्त(gate);
		kमुक्त(mux);
	पूर्ण

	वापस hw;
पूर्ण

अटल व्योम __init sपंचांग32f4_rcc_init(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *hse_clk, *i2s_in_clk;
	पूर्णांक n;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा sपंचांग32f4_clk_data *data;
	अचिन्हित दीर्घ pllm;
	काष्ठा clk_hw *pll_src_hw;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("%pOFn: unable to map resource\n", np);
		वापस;
	पूर्ण

	pdrm = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(pdrm)) अणु
		pdrm = शून्य;
		pr_warn("%s: Unable to get syscfg\n", __func__);
	पूर्ण

	match = of_match_node(sपंचांग32f4_of_match, np);
	अगर (WARN_ON(!match))
		वापस;

	data = match->data;

	sपंचांग32fx_end_primary_clk = data->end_primary;

	clks = kदो_स्मृति_array(data->gates_num + sपंचांग32fx_end_primary_clk,
			माप(*clks), GFP_KERNEL);
	अगर (!clks)
		जाओ fail;

	sपंचांग32f4_gate_map = data->gates_map;

	hse_clk = of_clk_get_parent_name(np, 0);
	dsi_parent[0] = hse_clk;
	pllsrc_parent[1] = hse_clk;

	i2s_in_clk = of_clk_get_parent_name(np, 1);

	i2s_parents[1] = i2s_in_clk;
	sai_parents[2] = i2s_in_clk;

	अगर (of_device_is_compatible(np, "st,stm32f769-rcc")) अणु
		clk_hw_रेजिस्टर_gate(शून्य, "dfsdm1_apb", "apb2_div", 0,
				     base + STM32F4_RCC_APB2ENR, 29,
				     CLK_IGNORE_UNUSED, &sपंचांग32f4_clk_lock);
		dsi_parent[0] = pll_src;
		sai_parents[3] = pll_src;
	पूर्ण

	clks[CLK_HSI] = clk_hw_रेजिस्टर_fixed_rate_with_accuracy(शून्य, "hsi",
			शून्य, 0, 16000000, 160000);

	pll_src_hw = clk_hw_रेजिस्टर_mux(शून्य, pll_src, pllsrc_parent,
					 ARRAY_SIZE(pllsrc_parent), 0,
					 base + STM32F4_RCC_PLLCFGR, 22, 1, 0,
					 &sपंचांग32f4_clk_lock);

	pllm = पढ़ोl(base + STM32F4_RCC_PLLCFGR) & 0x3f;

	clk_hw_रेजिस्टर_fixed_factor(शून्य, "vco_in", pll_src,
				     0, 1, pllm);

	sपंचांग32f4_rcc_रेजिस्टर_pll("vco_in", &data->pll_data[0],
			&sपंचांग32f4_clk_lock);

	clks[PLL_VCO_I2S] = sपंचांग32f4_rcc_रेजिस्टर_pll("vco_in",
			&data->pll_data[1], &sपंचांग32f4_clk_lock);

	clks[PLL_VCO_SAI] = sपंचांग32f4_rcc_रेजिस्टर_pll("vco_in",
			&data->pll_data[2], &sपंचांग32f4_clk_lock);

	क्रम (n = 0; n < MAX_POST_DIV; n++) अणु
		स्थिर काष्ठा sपंचांग32f4_pll_post_भाग_data *post_भाग;
		काष्ठा clk_hw *hw;

		post_भाग = &post_भाग_data[n];

		hw = clk_रेजिस्टर_pll_भाग(post_भाग->name,
				post_भाग->parent,
				post_भाग->flag,
				base + post_भाग->offset,
				post_भाग->shअगरt,
				post_भाग->width,
				post_भाग->flag_भाग,
				post_भाग->भाग_प्रकारable,
				clks[post_भाग->pll_num],
				&sपंचांग32f4_clk_lock);

		अगर (post_भाग->idx != NO_IDX)
			clks[post_भाग->idx] = hw;
	पूर्ण

	sys_parents[1] = hse_clk;

	clks[CLK_SYSCLK] = clk_hw_रेजिस्टर_mux_table(
	    शून्य, "sys", sys_parents, ARRAY_SIZE(sys_parents), 0,
	    base + STM32F4_RCC_CFGR, 0, 3, 0, शून्य, &sपंचांग32f4_clk_lock);

	clk_रेजिस्टर_भागider_table(शून्य, "ahb_div", "sys",
				   CLK_SET_RATE_PARENT, base + STM32F4_RCC_CFGR,
				   4, 4, 0, ahb_भाग_प्रकारable, &sपंचांग32f4_clk_lock);

	clk_रेजिस्टर_भागider_table(शून्य, "apb1_div", "ahb_div",
				   CLK_SET_RATE_PARENT, base + STM32F4_RCC_CFGR,
				   10, 3, 0, apb_भाग_प्रकारable, &sपंचांग32f4_clk_lock);
	clk_रेजिस्टर_apb_mul(शून्य, "apb1_mul", "apb1_div",
			     CLK_SET_RATE_PARENT, 12);

	clk_रेजिस्टर_भागider_table(शून्य, "apb2_div", "ahb_div",
				   CLK_SET_RATE_PARENT, base + STM32F4_RCC_CFGR,
				   13, 3, 0, apb_भाग_प्रकारable, &sपंचांग32f4_clk_lock);
	clk_रेजिस्टर_apb_mul(शून्य, "apb2_mul", "apb2_div",
			     CLK_SET_RATE_PARENT, 15);

	clks[SYSTICK] = clk_hw_रेजिस्टर_fixed_factor(शून्य, "systick", "ahb_div",
						  0, 1, 8);
	clks[FCLK] = clk_hw_रेजिस्टर_fixed_factor(शून्य, "fclk", "ahb_div",
					       0, 1, 1);

	क्रम (n = 0; n < data->gates_num; n++) अणु
		स्थिर काष्ठा sपंचांग32f4_gate_data *gd;
		अचिन्हित पूर्णांक secondary;
		पूर्णांक idx;

		gd = &data->gates_data[n];
		secondary = 8 * (gd->offset - STM32F4_RCC_AHB1ENR) +
			gd->bit_idx;
		idx = sपंचांग32f4_rcc_lookup_clk_idx(0, secondary);

		अगर (idx < 0)
			जाओ fail;

		clks[idx] = clk_hw_रेजिस्टर_gate(
		    शून्य, gd->name, gd->parent_name, gd->flags,
		    base + gd->offset, gd->bit_idx, 0, &sपंचांग32f4_clk_lock);

		अगर (IS_ERR(clks[idx])) अणु
			pr_err("%pOF: Unable to register leaf clock %s\n",
			       np, gd->name);
			जाओ fail;
		पूर्ण
	पूर्ण

	clks[CLK_LSI] = clk_रेजिस्टर_rgate(शून्य, "lsi", "clk-lsi", 0,
			base + STM32F4_RCC_CSR, 0, 1, 0, &sपंचांग32f4_clk_lock);

	अगर (IS_ERR(clks[CLK_LSI])) अणु
		pr_err("Unable to register lsi clock\n");
		जाओ fail;
	पूर्ण

	clks[CLK_LSE] = clk_रेजिस्टर_rgate(शून्य, "lse", "clk-lse", 0,
			base + STM32F4_RCC_BDCR, 0, 1, 0, &sपंचांग32f4_clk_lock);

	अगर (IS_ERR(clks[CLK_LSE])) अणु
		pr_err("Unable to register lse clock\n");
		जाओ fail;
	पूर्ण

	clks[CLK_HSE_RTC] = clk_hw_रेजिस्टर_भागider(शून्य, "hse-rtc", "clk-hse",
			0, base + STM32F4_RCC_CFGR, 16, 5, 0,
			&sपंचांग32f4_clk_lock);

	अगर (IS_ERR(clks[CLK_HSE_RTC])) अणु
		pr_err("Unable to register hse-rtc clock\n");
		जाओ fail;
	पूर्ण

	clks[CLK_RTC] = sपंचांग32_रेजिस्टर_cclk(शून्य, "rtc", rtc_parents, 4,
			base + STM32F4_RCC_BDCR, 15, 8, 0, &sपंचांग32f4_clk_lock);

	अगर (IS_ERR(clks[CLK_RTC])) अणु
		pr_err("Unable to register rtc clock\n");
		जाओ fail;
	पूर्ण

	क्रम (n = 0; n < data->aux_clk_num; n++) अणु
		स्थिर काष्ठा sपंचांग32_aux_clk *aux_clk;
		काष्ठा clk_hw *hw;

		aux_clk = &data->aux_clk[n];

		hw = sपंचांग32_रेजिस्टर_aux_clk(aux_clk->name,
				aux_clk->parent_names, aux_clk->num_parents,
				aux_clk->offset_mux, aux_clk->shअगरt,
				aux_clk->mask, aux_clk->offset_gate,
				aux_clk->bit_idx, aux_clk->flags,
				&sपंचांग32f4_clk_lock);

		अगर (IS_ERR(hw)) अणु
			pr_warn("Unable to register %s clk\n", aux_clk->name);
			जारी;
		पूर्ण

		अगर (aux_clk->idx != NO_IDX)
			clks[aux_clk->idx] = hw;
	पूर्ण

	अगर (of_device_is_compatible(np, "st,stm32f746-rcc")) अणु

		clk_hw_रेजिस्टर_fixed_factor(शून्य, "hsi_div488", "hsi", 0,
				1, 488);

		clks[CLK_PLL_SRC] = pll_src_hw;
	पूर्ण

	of_clk_add_hw_provider(np, sपंचांग32f4_rcc_lookup_clk, शून्य);

	वापस;
fail:
	kमुक्त(clks);
	iounmap(base);
पूर्ण
CLK_OF_DECLARE_DRIVER(sपंचांग32f42xx_rcc, "st,stm32f42xx-rcc", sपंचांग32f4_rcc_init);
CLK_OF_DECLARE_DRIVER(sपंचांग32f46xx_rcc, "st,stm32f469-rcc", sपंचांग32f4_rcc_init);
CLK_OF_DECLARE_DRIVER(sपंचांग32f746_rcc, "st,stm32f746-rcc", sपंचांग32f4_rcc_init);
CLK_OF_DECLARE_DRIVER(sपंचांग32f769_rcc, "st,stm32f769-rcc", sपंचांग32f4_rcc_init);
