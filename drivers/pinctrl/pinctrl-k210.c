<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Sean Anderson <seanga2@gmail.com>
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश <dt-bindings/pinctrl/k210-fpioa.h>

#समावेश "core.h"
#समावेश "pinconf.h"
#समावेश "pinctrl-utils.h"

/*
 * The K210 only implements 8 drive levels, even though
 * there is रेजिस्टर space क्रम 16
 */
#घोषणा K210_PC_DRIVE_MASK	GENMASK(11, 8)
#घोषणा K210_PC_DRIVE_SHIFT	8
#घोषणा K210_PC_DRIVE_0		(0 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_1		(1 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_2		(2 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_3		(3 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_4		(4 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_5		(5 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_6		(6 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_7		(7 << K210_PC_DRIVE_SHIFT)
#घोषणा K210_PC_DRIVE_MAX	7
#घोषणा K210_PC_MODE_MASK	GENMASK(23, 12)

/*
 * output enabled == PC_OE & (PC_OE_INV ^ FUNCTION_OE)
 * where FUNCTION_OE is a physical संकेत from the function.
 */
#घोषणा K210_PC_OE		BIT(12) /* Output Enable */
#घोषणा K210_PC_OE_INV		BIT(13) /* INVert Output Enable */
#घोषणा K210_PC_DO_OE		BIT(14) /* set Data Out to Output Enable sig */
#घोषणा K210_PC_DO_INV		BIT(15) /* INVert final Data Output */
#घोषणा K210_PC_PU		BIT(16) /* Pull Up */
#घोषणा K210_PC_PD		BIT(17) /* Pull Down */
/* Strong pull up not implemented on K210 */
#घोषणा K210_PC_SL		BIT(19) /* reduce SLew rate */
/* Same semantics as OE above */
#घोषणा K210_PC_IE		BIT(20) /* Input Enable */
#घोषणा K210_PC_IE_INV		BIT(21) /* INVert Input Enable */
#घोषणा K210_PC_DI_INV		BIT(22) /* INVert Data Input */
#घोषणा K210_PC_ST		BIT(23) /* Schmitt Trigger */
#घोषणा K210_PC_DI		BIT(31) /* raw Data Input */

#घोषणा K210_PC_BIAS_MASK	(K210_PC_PU & K210_PC_PD)

#घोषणा K210_PC_MODE_IN		(K210_PC_IE | K210_PC_ST)
#घोषणा K210_PC_MODE_OUT	(K210_PC_DRIVE_7 | K210_PC_OE)
#घोषणा K210_PC_MODE_I2C	(K210_PC_MODE_IN | K210_PC_SL | \
				 K210_PC_OE | K210_PC_PU)
#घोषणा K210_PC_MODE_SCCB	(K210_PC_MODE_I2C | \
				 K210_PC_OE_INV | K210_PC_IE_INV)
#घोषणा K210_PC_MODE_SPI	(K210_PC_MODE_IN | K210_PC_IE_INV | \
				 K210_PC_MODE_OUT | K210_PC_OE_INV)
#घोषणा K210_PC_MODE_GPIO	(K210_PC_MODE_IN | K210_PC_MODE_OUT)

#घोषणा K210_PG_FUNC		GENMASK(7, 0)
#घोषणा K210_PG_DO		BIT(8)
#घोषणा K210_PG_PIN		GENMASK(22, 16)

/*
 * काष्ठा k210_fpioa: Kendryte K210 FPIOA memory mapped रेजिस्टरs
 * @pins: 48 32-bits IO pin रेजिस्टरs
 * @tie_en: 256 (one per function) input tie enable bits
 * @tie_val: 256 (one per function) input tie value bits
 */
काष्ठा k210_fpioa अणु
	u32 pins[48];
	u32 tie_en[8];
	u32 tie_val[8];
पूर्ण;

काष्ठा k210_fpioa_data अणु

	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;

	काष्ठा k210_fpioa __iomem *fpioa;
	काष्ठा regmap *sysctl_map;
	u32 घातer_offset;
	काष्ठा clk *clk;
	काष्ठा clk *pclk;
पूर्ण;

#घोषणा K210_PIN_NAME(i)	("IO_" #i)
#घोषणा K210_PIN(i)		[(i)] = PINCTRL_PIN((i), K210_PIN_NAME(i))

अटल स्थिर काष्ठा pinctrl_pin_desc k210_pins[] = अणु
	K210_PIN(0),  K210_PIN(1),  K210_PIN(2),
	K210_PIN(3),  K210_PIN(4),  K210_PIN(5),
	K210_PIN(6),  K210_PIN(7),  K210_PIN(8),
	K210_PIN(9),  K210_PIN(10), K210_PIN(11),
	K210_PIN(12), K210_PIN(13), K210_PIN(14),
	K210_PIN(15), K210_PIN(16), K210_PIN(17),
	K210_PIN(18), K210_PIN(19), K210_PIN(20),
	K210_PIN(21), K210_PIN(22), K210_PIN(23),
	K210_PIN(24), K210_PIN(25), K210_PIN(26),
	K210_PIN(27), K210_PIN(28), K210_PIN(29),
	K210_PIN(30), K210_PIN(31), K210_PIN(32),
	K210_PIN(33), K210_PIN(34), K210_PIN(35),
	K210_PIN(36), K210_PIN(37), K210_PIN(38),
	K210_PIN(39), K210_PIN(40), K210_PIN(41),
	K210_PIN(42), K210_PIN(43), K210_PIN(44),
	K210_PIN(45), K210_PIN(46), K210_PIN(47)
पूर्ण;

#घोषणा K210_NPINS ARRAY_SIZE(k210_pins)

/*
 * Pin groups: each of the 48 programmable pins is a group.
 * To this are added 8 घातer करोमुख्य groups, which क्रम the purposes of
 * the pin subप्रणाली, contain no pins. The घातer करोमुख्य groups only exist
 * to set the घातer level. The id should never be used (since there are
 * no pins 48-55).
 */
अटल स्थिर अक्षर *स्थिर k210_group_names[] = अणु
	/* The first 48 groups are क्रम pins, one each */
	K210_PIN_NAME(0),  K210_PIN_NAME(1),  K210_PIN_NAME(2),
	K210_PIN_NAME(3),  K210_PIN_NAME(4),  K210_PIN_NAME(5),
	K210_PIN_NAME(6),  K210_PIN_NAME(7),  K210_PIN_NAME(8),
	K210_PIN_NAME(9),  K210_PIN_NAME(10), K210_PIN_NAME(11),
	K210_PIN_NAME(12), K210_PIN_NAME(13), K210_PIN_NAME(14),
	K210_PIN_NAME(15), K210_PIN_NAME(16), K210_PIN_NAME(17),
	K210_PIN_NAME(18), K210_PIN_NAME(19), K210_PIN_NAME(20),
	K210_PIN_NAME(21), K210_PIN_NAME(22), K210_PIN_NAME(23),
	K210_PIN_NAME(24), K210_PIN_NAME(25), K210_PIN_NAME(26),
	K210_PIN_NAME(27), K210_PIN_NAME(28), K210_PIN_NAME(29),
	K210_PIN_NAME(30), K210_PIN_NAME(31), K210_PIN_NAME(32),
	K210_PIN_NAME(33), K210_PIN_NAME(34), K210_PIN_NAME(35),
	K210_PIN_NAME(36), K210_PIN_NAME(37), K210_PIN_NAME(38),
	K210_PIN_NAME(39), K210_PIN_NAME(40), K210_PIN_NAME(41),
	K210_PIN_NAME(42), K210_PIN_NAME(43), K210_PIN_NAME(44),
	K210_PIN_NAME(45), K210_PIN_NAME(46), K210_PIN_NAME(47),
	[48] = "A0", [49] = "A1", [50] = "A2",
	[51] = "B3", [52] = "B4", [53] = "B5",
	[54] = "C6", [55] = "C7"
पूर्ण;

#घोषणा K210_NGROUPS	ARRAY_SIZE(k210_group_names)

क्रमागत k210_pinctrl_mode_id अणु
	K210_PC_DEFAULT_DISABLED,
	K210_PC_DEFAULT_IN,
	K210_PC_DEFAULT_IN_TIE,
	K210_PC_DEFAULT_OUT,
	K210_PC_DEFAULT_I2C,
	K210_PC_DEFAULT_SCCB,
	K210_PC_DEFAULT_SPI,
	K210_PC_DEFAULT_GPIO,
	K210_PC_DEFAULT_INT13,
पूर्ण;

#घोषणा K210_PC_DEFAULT(mode) \
	[K210_PC_DEFAULT_##mode] = K210_PC_MODE_##mode

अटल स्थिर u32 k210_pinconf_mode_id_to_mode[] = अणु
	[K210_PC_DEFAULT_DISABLED] = 0,
	K210_PC_DEFAULT(IN),
	[K210_PC_DEFAULT_IN_TIE] = K210_PC_MODE_IN,
	K210_PC_DEFAULT(OUT),
	K210_PC_DEFAULT(I2C),
	K210_PC_DEFAULT(SCCB),
	K210_PC_DEFAULT(SPI),
	K210_PC_DEFAULT(GPIO),
	[K210_PC_DEFAULT_INT13] = K210_PC_MODE_IN | K210_PC_PU,
पूर्ण;

#अघोषित DEFAULT

/*
 * Pin functions configuration inक्रमmation.
 */
काष्ठा k210_pcf_info अणु
	अक्षर name[15];
	u8 mode_id;
पूर्ण;

#घोषणा K210_FUNC(id, mode)				\
	[K210_PCF_##id] = अणु				\
		.name = #id,				\
		.mode_id = K210_PC_DEFAULT_##mode	\
	पूर्ण

अटल स्थिर काष्ठा k210_pcf_info k210_pcf_infos[] = अणु
	K210_FUNC(JTAG_TCLK,		IN),
	K210_FUNC(JTAG_TDI,		IN),
	K210_FUNC(JTAG_TMS,		IN),
	K210_FUNC(JTAG_TDO,		OUT),
	K210_FUNC(SPI0_D0,		SPI),
	K210_FUNC(SPI0_D1,		SPI),
	K210_FUNC(SPI0_D2,		SPI),
	K210_FUNC(SPI0_D3,		SPI),
	K210_FUNC(SPI0_D4,		SPI),
	K210_FUNC(SPI0_D5,		SPI),
	K210_FUNC(SPI0_D6,		SPI),
	K210_FUNC(SPI0_D7,		SPI),
	K210_FUNC(SPI0_SS0,		OUT),
	K210_FUNC(SPI0_SS1,		OUT),
	K210_FUNC(SPI0_SS2,		OUT),
	K210_FUNC(SPI0_SS3,		OUT),
	K210_FUNC(SPI0_ARB,		IN_TIE),
	K210_FUNC(SPI0_SCLK,		OUT),
	K210_FUNC(UARTHS_RX,		IN),
	K210_FUNC(UARTHS_TX,		OUT),
	K210_FUNC(RESV6,		IN),
	K210_FUNC(RESV7,		IN),
	K210_FUNC(CLK_SPI1,		OUT),
	K210_FUNC(CLK_I2C1,		OUT),
	K210_FUNC(GPIOHS0,		GPIO),
	K210_FUNC(GPIOHS1,		GPIO),
	K210_FUNC(GPIOHS2,		GPIO),
	K210_FUNC(GPIOHS3,		GPIO),
	K210_FUNC(GPIOHS4,		GPIO),
	K210_FUNC(GPIOHS5,		GPIO),
	K210_FUNC(GPIOHS6,		GPIO),
	K210_FUNC(GPIOHS7,		GPIO),
	K210_FUNC(GPIOHS8,		GPIO),
	K210_FUNC(GPIOHS9,		GPIO),
	K210_FUNC(GPIOHS10,		GPIO),
	K210_FUNC(GPIOHS11,		GPIO),
	K210_FUNC(GPIOHS12,		GPIO),
	K210_FUNC(GPIOHS13,		GPIO),
	K210_FUNC(GPIOHS14,		GPIO),
	K210_FUNC(GPIOHS15,		GPIO),
	K210_FUNC(GPIOHS16,		GPIO),
	K210_FUNC(GPIOHS17,		GPIO),
	K210_FUNC(GPIOHS18,		GPIO),
	K210_FUNC(GPIOHS19,		GPIO),
	K210_FUNC(GPIOHS20,		GPIO),
	K210_FUNC(GPIOHS21,		GPIO),
	K210_FUNC(GPIOHS22,		GPIO),
	K210_FUNC(GPIOHS23,		GPIO),
	K210_FUNC(GPIOHS24,		GPIO),
	K210_FUNC(GPIOHS25,		GPIO),
	K210_FUNC(GPIOHS26,		GPIO),
	K210_FUNC(GPIOHS27,		GPIO),
	K210_FUNC(GPIOHS28,		GPIO),
	K210_FUNC(GPIOHS29,		GPIO),
	K210_FUNC(GPIOHS30,		GPIO),
	K210_FUNC(GPIOHS31,		GPIO),
	K210_FUNC(GPIO0,		GPIO),
	K210_FUNC(GPIO1,		GPIO),
	K210_FUNC(GPIO2,		GPIO),
	K210_FUNC(GPIO3,		GPIO),
	K210_FUNC(GPIO4,		GPIO),
	K210_FUNC(GPIO5,		GPIO),
	K210_FUNC(GPIO6,		GPIO),
	K210_FUNC(GPIO7,		GPIO),
	K210_FUNC(UART1_RX,		IN),
	K210_FUNC(UART1_TX,		OUT),
	K210_FUNC(UART2_RX,		IN),
	K210_FUNC(UART2_TX,		OUT),
	K210_FUNC(UART3_RX,		IN),
	K210_FUNC(UART3_TX,		OUT),
	K210_FUNC(SPI1_D0,		SPI),
	K210_FUNC(SPI1_D1,		SPI),
	K210_FUNC(SPI1_D2,		SPI),
	K210_FUNC(SPI1_D3,		SPI),
	K210_FUNC(SPI1_D4,		SPI),
	K210_FUNC(SPI1_D5,		SPI),
	K210_FUNC(SPI1_D6,		SPI),
	K210_FUNC(SPI1_D7,		SPI),
	K210_FUNC(SPI1_SS0,		OUT),
	K210_FUNC(SPI1_SS1,		OUT),
	K210_FUNC(SPI1_SS2,		OUT),
	K210_FUNC(SPI1_SS3,		OUT),
	K210_FUNC(SPI1_ARB,		IN_TIE),
	K210_FUNC(SPI1_SCLK,		OUT),
	K210_FUNC(SPI2_D0,		SPI),
	K210_FUNC(SPI2_SS,		IN),
	K210_FUNC(SPI2_SCLK,		IN),
	K210_FUNC(I2S0_MCLK,		OUT),
	K210_FUNC(I2S0_SCLK,		OUT),
	K210_FUNC(I2S0_WS,		OUT),
	K210_FUNC(I2S0_IN_D0,		IN),
	K210_FUNC(I2S0_IN_D1,		IN),
	K210_FUNC(I2S0_IN_D2,		IN),
	K210_FUNC(I2S0_IN_D3,		IN),
	K210_FUNC(I2S0_OUT_D0,		OUT),
	K210_FUNC(I2S0_OUT_D1,		OUT),
	K210_FUNC(I2S0_OUT_D2,		OUT),
	K210_FUNC(I2S0_OUT_D3,		OUT),
	K210_FUNC(I2S1_MCLK,		OUT),
	K210_FUNC(I2S1_SCLK,		OUT),
	K210_FUNC(I2S1_WS,		OUT),
	K210_FUNC(I2S1_IN_D0,		IN),
	K210_FUNC(I2S1_IN_D1,		IN),
	K210_FUNC(I2S1_IN_D2,		IN),
	K210_FUNC(I2S1_IN_D3,		IN),
	K210_FUNC(I2S1_OUT_D0,		OUT),
	K210_FUNC(I2S1_OUT_D1,		OUT),
	K210_FUNC(I2S1_OUT_D2,		OUT),
	K210_FUNC(I2S1_OUT_D3,		OUT),
	K210_FUNC(I2S2_MCLK,		OUT),
	K210_FUNC(I2S2_SCLK,		OUT),
	K210_FUNC(I2S2_WS,		OUT),
	K210_FUNC(I2S2_IN_D0,		IN),
	K210_FUNC(I2S2_IN_D1,		IN),
	K210_FUNC(I2S2_IN_D2,		IN),
	K210_FUNC(I2S2_IN_D3,		IN),
	K210_FUNC(I2S2_OUT_D0,		OUT),
	K210_FUNC(I2S2_OUT_D1,		OUT),
	K210_FUNC(I2S2_OUT_D2,		OUT),
	K210_FUNC(I2S2_OUT_D3,		OUT),
	K210_FUNC(RESV0,		DISABLED),
	K210_FUNC(RESV1,		DISABLED),
	K210_FUNC(RESV2,		DISABLED),
	K210_FUNC(RESV3,		DISABLED),
	K210_FUNC(RESV4,		DISABLED),
	K210_FUNC(RESV5,		DISABLED),
	K210_FUNC(I2C0_SCLK,		I2C),
	K210_FUNC(I2C0_SDA,		I2C),
	K210_FUNC(I2C1_SCLK,		I2C),
	K210_FUNC(I2C1_SDA,		I2C),
	K210_FUNC(I2C2_SCLK,		I2C),
	K210_FUNC(I2C2_SDA,		I2C),
	K210_FUNC(DVP_XCLK,		OUT),
	K210_FUNC(DVP_RST,		OUT),
	K210_FUNC(DVP_PWDN,		OUT),
	K210_FUNC(DVP_VSYNC,		IN),
	K210_FUNC(DVP_HSYNC,		IN),
	K210_FUNC(DVP_PCLK,		IN),
	K210_FUNC(DVP_D0,		IN),
	K210_FUNC(DVP_D1,		IN),
	K210_FUNC(DVP_D2,		IN),
	K210_FUNC(DVP_D3,		IN),
	K210_FUNC(DVP_D4,		IN),
	K210_FUNC(DVP_D5,		IN),
	K210_FUNC(DVP_D6,		IN),
	K210_FUNC(DVP_D7,		IN),
	K210_FUNC(SCCB_SCLK,		SCCB),
	K210_FUNC(SCCB_SDA,		SCCB),
	K210_FUNC(UART1_CTS,		IN),
	K210_FUNC(UART1_DSR,		IN),
	K210_FUNC(UART1_DCD,		IN),
	K210_FUNC(UART1_RI,		IN),
	K210_FUNC(UART1_SIR_IN,		IN),
	K210_FUNC(UART1_DTR,		OUT),
	K210_FUNC(UART1_RTS,		OUT),
	K210_FUNC(UART1_OUT2,		OUT),
	K210_FUNC(UART1_OUT1,		OUT),
	K210_FUNC(UART1_SIR_OUT,	OUT),
	K210_FUNC(UART1_BAUD,		OUT),
	K210_FUNC(UART1_RE,		OUT),
	K210_FUNC(UART1_DE,		OUT),
	K210_FUNC(UART1_RS485_EN,	OUT),
	K210_FUNC(UART2_CTS,		IN),
	K210_FUNC(UART2_DSR,		IN),
	K210_FUNC(UART2_DCD,		IN),
	K210_FUNC(UART2_RI,		IN),
	K210_FUNC(UART2_SIR_IN,		IN),
	K210_FUNC(UART2_DTR,		OUT),
	K210_FUNC(UART2_RTS,		OUT),
	K210_FUNC(UART2_OUT2,		OUT),
	K210_FUNC(UART2_OUT1,		OUT),
	K210_FUNC(UART2_SIR_OUT,	OUT),
	K210_FUNC(UART2_BAUD,		OUT),
	K210_FUNC(UART2_RE,		OUT),
	K210_FUNC(UART2_DE,		OUT),
	K210_FUNC(UART2_RS485_EN,	OUT),
	K210_FUNC(UART3_CTS,		IN),
	K210_FUNC(UART3_DSR,		IN),
	K210_FUNC(UART3_DCD,		IN),
	K210_FUNC(UART3_RI,		IN),
	K210_FUNC(UART3_SIR_IN,		IN),
	K210_FUNC(UART3_DTR,		OUT),
	K210_FUNC(UART3_RTS,		OUT),
	K210_FUNC(UART3_OUT2,		OUT),
	K210_FUNC(UART3_OUT1,		OUT),
	K210_FUNC(UART3_SIR_OUT,	OUT),
	K210_FUNC(UART3_BAUD,		OUT),
	K210_FUNC(UART3_RE,		OUT),
	K210_FUNC(UART3_DE,		OUT),
	K210_FUNC(UART3_RS485_EN,	OUT),
	K210_FUNC(TIMER0_TOGGLE1,	OUT),
	K210_FUNC(TIMER0_TOGGLE2,	OUT),
	K210_FUNC(TIMER0_TOGGLE3,	OUT),
	K210_FUNC(TIMER0_TOGGLE4,	OUT),
	K210_FUNC(TIMER1_TOGGLE1,	OUT),
	K210_FUNC(TIMER1_TOGGLE2,	OUT),
	K210_FUNC(TIMER1_TOGGLE3,	OUT),
	K210_FUNC(TIMER1_TOGGLE4,	OUT),
	K210_FUNC(TIMER2_TOGGLE1,	OUT),
	K210_FUNC(TIMER2_TOGGLE2,	OUT),
	K210_FUNC(TIMER2_TOGGLE3,	OUT),
	K210_FUNC(TIMER2_TOGGLE4,	OUT),
	K210_FUNC(CLK_SPI2,		OUT),
	K210_FUNC(CLK_I2C2,		OUT),
	K210_FUNC(INTERNAL0,		OUT),
	K210_FUNC(INTERNAL1,		OUT),
	K210_FUNC(INTERNAL2,		OUT),
	K210_FUNC(INTERNAL3,		OUT),
	K210_FUNC(INTERNAL4,		OUT),
	K210_FUNC(INTERNAL5,		OUT),
	K210_FUNC(INTERNAL6,		OUT),
	K210_FUNC(INTERNAL7,		OUT),
	K210_FUNC(INTERNAL8,		OUT),
	K210_FUNC(INTERNAL9,		IN),
	K210_FUNC(INTERNAL10,		IN),
	K210_FUNC(INTERNAL11,		IN),
	K210_FUNC(INTERNAL12,		IN),
	K210_FUNC(INTERNAL13,		INT13),
	K210_FUNC(INTERNAL14,		I2C),
	K210_FUNC(INTERNAL15,		IN),
	K210_FUNC(INTERNAL16,		IN),
	K210_FUNC(INTERNAL17,		IN),
	K210_FUNC(CONSTANT,		DISABLED),
	K210_FUNC(INTERNAL18,		IN),
	K210_FUNC(DEBUG0,		OUT),
	K210_FUNC(DEBUG1,		OUT),
	K210_FUNC(DEBUG2,		OUT),
	K210_FUNC(DEBUG3,		OUT),
	K210_FUNC(DEBUG4,		OUT),
	K210_FUNC(DEBUG5,		OUT),
	K210_FUNC(DEBUG6,		OUT),
	K210_FUNC(DEBUG7,		OUT),
	K210_FUNC(DEBUG8,		OUT),
	K210_FUNC(DEBUG9,		OUT),
	K210_FUNC(DEBUG10,		OUT),
	K210_FUNC(DEBUG11,		OUT),
	K210_FUNC(DEBUG12,		OUT),
	K210_FUNC(DEBUG13,		OUT),
	K210_FUNC(DEBUG14,		OUT),
	K210_FUNC(DEBUG15,		OUT),
	K210_FUNC(DEBUG16,		OUT),
	K210_FUNC(DEBUG17,		OUT),
	K210_FUNC(DEBUG18,		OUT),
	K210_FUNC(DEBUG19,		OUT),
	K210_FUNC(DEBUG20,		OUT),
	K210_FUNC(DEBUG21,		OUT),
	K210_FUNC(DEBUG22,		OUT),
	K210_FUNC(DEBUG23,		OUT),
	K210_FUNC(DEBUG24,		OUT),
	K210_FUNC(DEBUG25,		OUT),
	K210_FUNC(DEBUG26,		OUT),
	K210_FUNC(DEBUG27,		OUT),
	K210_FUNC(DEBUG28,		OUT),
	K210_FUNC(DEBUG29,		OUT),
	K210_FUNC(DEBUG30,		OUT),
	K210_FUNC(DEBUG31,		OUT),
पूर्ण;

#घोषणा PIN_CONFIG_OUTPUT_INVERT	(PIN_CONFIG_END + 1)
#घोषणा PIN_CONFIG_INPUT_INVERT		(PIN_CONFIG_END + 2)

अटल स्थिर काष्ठा pinconf_generic_params k210_pinconf_custom_params[] = अणु
	अणु "output-polarity-invert", PIN_CONFIG_OUTPUT_INVERT, 1 पूर्ण,
	अणु "input-polarity-invert",  PIN_CONFIG_INPUT_INVERT, 1 पूर्ण,
पूर्ण;

/*
 * Max drive strength in uA.
 */
अटल स्थिर पूर्णांक k210_pinconf_drive_strength[] = अणु
	[0] = 11200,
	[1] = 16800,
	[2] = 22300,
	[3] = 27800,
	[4] = 33300,
	[5] = 38700,
	[6] = 44100,
	[7] = 49500,
पूर्ण;

अटल पूर्णांक k210_pinconf_get_drive(अचिन्हित पूर्णांक max_strength_ua)
अणु
	पूर्णांक i;

	क्रम (i = K210_PC_DRIVE_MAX; i; i--) अणु
		अगर (k210_pinconf_drive_strength[i] <= max_strength_ua)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम k210_pinmux_set_pin_function(काष्ठा pinctrl_dev *pctldev,
					 u32 pin, u32 func)
अणु
	काष्ठा k210_fpioa_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा k210_pcf_info *info = &k210_pcf_infos[func];
	u32 mode = k210_pinconf_mode_id_to_mode[info->mode_id];
	u32 val = func | mode;

	dev_dbg(pdata->dev, "set pin %u function %s (%u) -> 0x%08x\n",
		pin, info->name, func, val);

	ग_लिखोl(val, &pdata->fpioa->pins[pin]);
पूर्ण

अटल पूर्णांक k210_pinconf_set_param(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक pin,
				  अचिन्हित पूर्णांक param, अचिन्हित पूर्णांक arg)
अणु
	काष्ठा k210_fpioa_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	u32 val = पढ़ोl(&pdata->fpioa->pins[pin]);
	पूर्णांक drive;

	dev_dbg(pdata->dev, "set pin %u param %u, arg 0x%x\n",
		pin, param, arg);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		val &= ~K210_PC_BIAS_MASK;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (!arg)
			वापस -EINVAL;
		val |= K210_PC_PD;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (!arg)
			वापस -EINVAL;
		val |= K210_PC_PD;
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		arg *= 1000;
		fallthrough;
	हाल PIN_CONFIG_DRIVE_STRENGTH_UA:
		drive = k210_pinconf_get_drive(arg);
		अगर (drive < 0)
			वापस drive;
		val &= ~K210_PC_DRIVE_MASK;
		val |= FIELD_PREP(K210_PC_DRIVE_MASK, drive);
		अवरोध;
	हाल PIN_CONFIG_INPUT_ENABLE:
		अगर (arg)
			val |= K210_PC_IE;
		अन्यथा
			val &= ~K210_PC_IE;
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		अगर (arg)
			val |= K210_PC_ST;
		अन्यथा
			val &= ~K210_PC_ST;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT:
		k210_pinmux_set_pin_function(pctldev, pin, K210_PCF_CONSTANT);
		val = पढ़ोl(&pdata->fpioa->pins[pin]);
		val |= K210_PC_MODE_OUT;
		अगर (!arg)
			val |= K210_PC_DO_INV;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT_ENABLE:
		अगर (arg)
			val |= K210_PC_OE;
		अन्यथा
			val &= ~K210_PC_OE;
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		अगर (arg)
			val |= K210_PC_SL;
		अन्यथा
			val &= ~K210_PC_SL;
		अवरोध;
	हाल PIN_CONFIG_OUTPUT_INVERT:
		अगर (arg)
			val |= K210_PC_DO_INV;
		अन्यथा
			val &= ~K210_PC_DO_INV;
		अवरोध;
	हाल PIN_CONFIG_INPUT_INVERT:
		अगर (arg)
			val |= K210_PC_DI_INV;
		अन्यथा
			val &= ~K210_PC_DI_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(val, &pdata->fpioa->pins[pin]);

	वापस 0;
पूर्ण

अटल पूर्णांक k210_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक num_configs)
अणु
	अचिन्हित पूर्णांक param, arg;
	पूर्णांक i, ret;

	अगर (WARN_ON(pin >= K210_NPINS))
		वापस -EINVAL;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);
		ret = k210_pinconf_set_param(pctldev, pin, param, arg);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम k210_pinconf_dbg_show(काष्ठा pinctrl_dev *pctldev,
				  काष्ठा seq_file *s, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा k210_fpioa_data *pdata = pinctrl_dev_get_drvdata(pctldev);

	seq_म_लिखो(s, "%#x", पढ़ोl(&pdata->fpioa->pins[pin]));
पूर्ण

अटल पूर्णांक k210_pinconf_group_set(काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित पूर्णांक selector, अचिन्हित दीर्घ *configs,
				  अचिन्हित पूर्णांक num_configs)
अणु
	काष्ठा k210_fpioa_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	अचिन्हित पूर्णांक param, arg;
	u32 bit;
	पूर्णांक i;

	/* Pins should be configured with pinmux, not groups*/
	अगर (selector < K210_NPINS)
		वापस -EINVAL;

	/* Otherwise it's a घातer करोमुख्य */
	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		अगर (param != PIN_CONFIG_POWER_SOURCE)
			वापस -EINVAL;

		arg = pinconf_to_config_argument(configs[i]);
		bit = BIT(selector - K210_NPINS);
		regmap_update_bits(pdata->sysctl_map,
				   pdata->घातer_offset,
				   bit, arg ? bit : 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम k210_pinconf_group_dbg_show(काष्ठा pinctrl_dev *pctldev,
					काष्ठा seq_file *s,
					अचिन्हित पूर्णांक selector)
अणु
	काष्ठा k210_fpioa_data *pdata = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक ret;
	u32 val;

	अगर (selector < K210_NPINS)
		वापस k210_pinconf_dbg_show(pctldev, s, selector);

	ret = regmap_पढ़ो(pdata->sysctl_map, pdata->घातer_offset, &val);
	अगर (ret) अणु
		dev_err(pdata->dev, "Failed to read power reg\n");
		वापस;
	पूर्ण

	seq_म_लिखो(s, "%s: %s V", k210_group_names[selector],
		   val & BIT(selector - K210_NPINS) ? "1.8" : "3.3");
पूर्ण

अटल स्थिर काष्ठा pinconf_ops k210_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_set = k210_pinconf_set,
	.pin_config_group_set = k210_pinconf_group_set,
	.pin_config_dbg_show = k210_pinconf_dbg_show,
	.pin_config_group_dbg_show = k210_pinconf_group_dbg_show,
पूर्ण;

अटल पूर्णांक k210_pinmux_get_function_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस ARRAY_SIZE(k210_pcf_infos);
पूर्ण

अटल स्थिर अक्षर *k210_pinmux_get_function_name(काष्ठा pinctrl_dev *pctldev,
						 अचिन्हित पूर्णांक selector)
अणु
	वापस k210_pcf_infos[selector].name;
पूर्ण

अटल पूर्णांक k210_pinmux_get_function_groups(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक selector,
					   स्थिर अक्षर * स्थिर **groups,
					   अचिन्हित पूर्णांक * स्थिर num_groups)
अणु
	/* Any function can be mapped to any pin */
	*groups = k210_group_names;
	*num_groups = K210_NPINS;

	वापस 0;
पूर्ण

अटल पूर्णांक k210_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित पूर्णांक function,
			       अचिन्हित पूर्णांक group)
अणु
	/* Can't mux घातer करोमुख्यs */
	अगर (group >= K210_NPINS)
		वापस -EINVAL;

	k210_pinmux_set_pin_function(pctldev, group, function);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops k210_pinmux_ops = अणु
	.get_functions_count = k210_pinmux_get_function_count,
	.get_function_name = k210_pinmux_get_function_name,
	.get_function_groups = k210_pinmux_get_function_groups,
	.set_mux = k210_pinmux_set_mux,
	.strict = true,
पूर्ण;

अटल पूर्णांक k210_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस K210_NGROUPS;
पूर्ण

अटल स्थिर अक्षर *k210_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित पूर्णांक group)
अणु
	वापस k210_group_names[group];
पूर्ण

अटल पूर्णांक k210_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक group,
				       स्थिर अचिन्हित पूर्णांक **pins,
				       अचिन्हित पूर्णांक *npins)
अणु
	अगर (group >= K210_NPINS) अणु
		*pins = शून्य;
		*npins = 0;
		वापस 0;
	पूर्ण

	*pins = &k210_pins[group].number;
	*npins = 1;

	वापस 0;
पूर्ण

अटल व्योम k210_pinctrl_pin_dbg_show(काष्ठा pinctrl_dev *pctldev,
				      काष्ठा seq_file *s, अचिन्हित पूर्णांक offset)
अणु
	seq_म_लिखो(s, "%s", dev_name(pctldev->dev));
पूर्ण

अटल पूर्णांक k210_pinctrl_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
					  काष्ठा device_node *np,
					  काष्ठा pinctrl_map **map,
					  अचिन्हित पूर्णांक *reserved_maps,
					  अचिन्हित पूर्णांक *num_maps)
अणु
	काष्ठा property *prop;
	स्थिर __be32 *p;
	पूर्णांक ret, pinmux_groups;
	u32 pinmux_group;
	अचिन्हित दीर्घ *configs = शून्य;
	अचिन्हित पूर्णांक num_configs = 0;
	अचिन्हित पूर्णांक reserve = 0;

	ret = of_property_count_strings(np, "groups");
	अगर (!ret)
		वापस pinconf_generic_dt_subnode_to_map(pctldev, np, map,
						reserved_maps, num_maps,
						PIN_MAP_TYPE_CONFIGS_GROUP);

	pinmux_groups = of_property_count_u32_elems(np, "pinmux");
	अगर (pinmux_groups <= 0) अणु
		/* Ignore this node */
		वापस 0;
	पूर्ण

	ret = pinconf_generic_parse_dt_config(np, pctldev, &configs,
					      &num_configs);
	अगर (ret < 0) अणु
		dev_err(pctldev->dev, "%pOF: could not parse node property\n",
			np);
		वापस ret;
	पूर्ण

	reserve = pinmux_groups * (1 + num_configs);
	ret = pinctrl_utils_reserve_map(pctldev, map, reserved_maps, num_maps,
					reserve);
	अगर (ret < 0)
		जाओ निकास;

	of_property_क्रम_each_u32(np, "pinmux", prop, p, pinmux_group) अणु
		स्थिर अक्षर *group_name, *func_name;
		u32 pin = FIELD_GET(K210_PG_PIN, pinmux_group);
		u32 func = FIELD_GET(K210_PG_FUNC, pinmux_group);

		अगर (pin >= K210_NPINS) अणु
			ret = -EINVAL;
			जाओ निकास;
		पूर्ण

		group_name = k210_group_names[pin];
		func_name = k210_pcf_infos[func].name;

		dev_dbg(pctldev->dev, "Pinmux %s: pin %u func %s\n",
			np->name, pin, func_name);

		ret = pinctrl_utils_add_map_mux(pctldev, map, reserved_maps,
						num_maps, group_name,
						func_name);
		अगर (ret < 0) अणु
			dev_err(pctldev->dev, "%pOF add mux map failed %d\n",
				np, ret);
			जाओ निकास;
		पूर्ण

		अगर (num_configs) अणु
			ret = pinctrl_utils_add_map_configs(pctldev, map,
					reserved_maps, num_maps, group_name,
					configs, num_configs,
					PIN_MAP_TYPE_CONFIGS_PIN);
			अगर (ret < 0) अणु
				dev_err(pctldev->dev,
					"%pOF add configs map failed %d\n",
					np, ret);
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = 0;

निकास:
	kमुक्त(configs);
	वापस ret;
पूर्ण

अटल पूर्णांक k210_pinctrl_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
				       काष्ठा device_node *np_config,
				       काष्ठा pinctrl_map **map,
				       अचिन्हित पूर्णांक *num_maps)
अणु
	अचिन्हित पूर्णांक reserved_maps;
	काष्ठा device_node *np;
	पूर्णांक ret;

	reserved_maps = 0;
	*map = शून्य;
	*num_maps = 0;

	ret = k210_pinctrl_dt_subnode_to_map(pctldev, np_config, map,
					     &reserved_maps, num_maps);
	अगर (ret < 0)
		जाओ err;

	क्रम_each_available_child_of_node(np_config, np) अणु
		ret = k210_pinctrl_dt_subnode_to_map(pctldev, np, map,
						     &reserved_maps, num_maps);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
	वापस 0;

err:
	pinctrl_utils_मुक्त_map(pctldev, *map, *num_maps);
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा pinctrl_ops k210_pinctrl_ops = अणु
	.get_groups_count = k210_pinctrl_get_groups_count,
	.get_group_name = k210_pinctrl_get_group_name,
	.get_group_pins = k210_pinctrl_get_group_pins,
	.pin_dbg_show = k210_pinctrl_pin_dbg_show,
	.dt_node_to_map = k210_pinctrl_dt_node_to_map,
	.dt_मुक्त_map = pinconf_generic_dt_मुक्त_map,
पूर्ण;

अटल काष्ठा pinctrl_desc k210_pinctrl_desc = अणु
	.name = "k210-pinctrl",
	.pins = k210_pins,
	.npins = K210_NPINS,
	.pctlops = &k210_pinctrl_ops,
	.pmxops = &k210_pinmux_ops,
	.confops = &k210_pinconf_ops,
	.custom_params = k210_pinconf_custom_params,
	.num_custom_params = ARRAY_SIZE(k210_pinconf_custom_params),
पूर्ण;

अटल व्योम k210_fpioa_init_ties(काष्ठा k210_fpioa_data *pdata)
अणु
	काष्ठा k210_fpioa __iomem *fpioa = pdata->fpioa;
	u32 val;
	पूर्णांक i, j;

	dev_dbg(pdata->dev, "Init pin ties\n");

	/* Init pin functions input ties */
	क्रम (i = 0; i < ARRAY_SIZE(fpioa->tie_en); i++) अणु
		val = 0;
		क्रम (j = 0; j < 32; j++) अणु
			अगर (k210_pcf_infos[i * 32 + j].mode_id ==
			    K210_PC_DEFAULT_IN_TIE) अणु
				dev_dbg(pdata->dev,
					"tie_en function %d (%s)\n",
					i * 32 + j,
					k210_pcf_infos[i * 32 + j].name);
				val |= BIT(j);
			पूर्ण
		पूर्ण

		/* Set value beक्रमe enable */
		ग_लिखोl(val, &fpioa->tie_val[i]);
		ग_लिखोl(val, &fpioa->tie_en[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक k210_fpioa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा k210_fpioa_data *pdata;
	पूर्णांक ret;

	dev_info(dev, "K210 FPIOA pin controller\n");

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->dev = dev;
	platक्रमm_set_drvdata(pdev, pdata);

	pdata->fpioa = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pdata->fpioa))
		वापस PTR_ERR(pdata->fpioa);

	pdata->clk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(pdata->clk))
		वापस PTR_ERR(pdata->clk);

	ret = clk_prepare_enable(pdata->clk);
	अगर (ret)
		वापस ret;

	pdata->pclk = devm_clk_get_optional(dev, "pclk");
	अगर (!IS_ERR(pdata->pclk))
		clk_prepare_enable(pdata->pclk);

	pdata->sysctl_map =
		syscon_regmap_lookup_by_phandle_args(np,
						"canaan,k210-sysctl-power",
						1, &pdata->घातer_offset);
	अगर (IS_ERR(pdata->sysctl_map))
		वापस PTR_ERR(pdata->sysctl_map);

	k210_fpioa_init_ties(pdata);

	pdata->pctl = pinctrl_रेजिस्टर(&k210_pinctrl_desc, dev, (व्योम *)pdata);
	अगर (IS_ERR(pdata->pctl))
		वापस PTR_ERR(pdata->pctl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id k210_fpioa_dt_ids[] = अणु
	अणु .compatible = "canaan,k210-fpioa" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver k210_fpioa_driver = अणु
	.probe	= k210_fpioa_probe,
	.driver = अणु
		.name		= "k210-fpioa",
		.of_match_table	= k210_fpioa_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(k210_fpioa_driver);
