<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pistachio SoC pinctrl driver
 *
 * Copyright (C) 2014 Imagination Technologies Ltd.
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "pinctrl-utils.h"

#घोषणा PADS_SCHMITT_EN0		0x000
#घोषणा PADS_SCHMITT_EN_REG(pin)	(PADS_SCHMITT_EN0 + 0x4 * ((pin) / 32))
#घोषणा PADS_SCHMITT_EN_BIT(pin)	BIT((pin) % 32)

#घोषणा PADS_PU_PD0			0x040
#घोषणा PADS_PU_PD_REG(pin)		(PADS_PU_PD0 + 0x4 * ((pin) / 16))
#घोषणा PADS_PU_PD_SHIFT(pin)		(2 * ((pin) % 16))
#घोषणा PADS_PU_PD_MASK			0x3
#घोषणा PADS_PU_PD_HIGHZ		0x0
#घोषणा PADS_PU_PD_UP			0x1
#घोषणा PADS_PU_PD_DOWN			0x2
#घोषणा PADS_PU_PD_BUS			0x3

#घोषणा PADS_FUNCTION_SELECT0		0x0c0
#घोषणा PADS_FUNCTION_SELECT1		0x0c4
#घोषणा PADS_FUNCTION_SELECT2		0x0c8
#घोषणा PADS_SCENARIO_SELECT		0x0f8

#घोषणा PADS_SLEW_RATE0			0x100
#घोषणा PADS_SLEW_RATE_REG(pin)		(PADS_SLEW_RATE0 + 0x4 * ((pin) / 32))
#घोषणा PADS_SLEW_RATE_BIT(pin)		BIT((pin) % 32)

#घोषणा PADS_DRIVE_STRENGTH0		0x120
#घोषणा PADS_DRIVE_STRENGTH_REG(pin)					\
	(PADS_DRIVE_STRENGTH0 + 0x4 * ((pin) / 16))
#घोषणा PADS_DRIVE_STRENGTH_SHIFT(pin)	(2 * ((pin) % 16))
#घोषणा PADS_DRIVE_STRENGTH_MASK	0x3
#घोषणा PADS_DRIVE_STRENGTH_2MA		0x0
#घोषणा PADS_DRIVE_STRENGTH_4MA		0x1
#घोषणा PADS_DRIVE_STRENGTH_8MA		0x2
#घोषणा PADS_DRIVE_STRENGTH_12MA	0x3

#घोषणा GPIO_BANK_BASE(bank)		(0x200 + 0x24 * (bank))

#घोषणा GPIO_BIT_EN			0x00
#घोषणा GPIO_OUTPUT_EN			0x04
#घोषणा GPIO_OUTPUT			0x08
#घोषणा GPIO_INPUT			0x0c
#घोषणा GPIO_INPUT_POLARITY		0x10
#घोषणा GPIO_INTERRUPT_TYPE		0x14
#घोषणा GPIO_INTERRUPT_TYPE_LEVEL	0x0
#घोषणा GPIO_INTERRUPT_TYPE_EDGE	0x1
#घोषणा GPIO_INTERRUPT_EDGE		0x18
#घोषणा GPIO_INTERRUPT_EDGE_SINGLE	0x0
#घोषणा GPIO_INTERRUPT_EDGE_DUAL	0x1
#घोषणा GPIO_INTERRUPT_EN		0x1c
#घोषणा GPIO_INTERRUPT_STATUS		0x20

काष्ठा pistachio_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
	स्थिर पूर्णांक *scenarios;
	अचिन्हित पूर्णांक nscenarios;
	अचिन्हित पूर्णांक scenario_reg;
	अचिन्हित पूर्णांक scenario_shअगरt;
	अचिन्हित पूर्णांक scenario_mask;
पूर्ण;

काष्ठा pistachio_pin_group अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक pin;
	पूर्णांक mux_option[3];
	पूर्णांक mux_reg;
	पूर्णांक mux_shअगरt;
	पूर्णांक mux_mask;
पूर्ण;

काष्ठा pistachio_gpio_bank अणु
	काष्ठा pistachio_pinctrl *pctl;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक pin_base;
	अचिन्हित पूर्णांक npins;
	काष्ठा gpio_chip gpio_chip;
	काष्ठा irq_chip irq_chip;
पूर्ण;

काष्ठा pistachio_pinctrl अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा pinctrl_dev *pctldev;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;
	स्थिर काष्ठा pistachio_function *functions;
	अचिन्हित पूर्णांक nfunctions;
	स्थिर काष्ठा pistachio_pin_group *groups;
	अचिन्हित पूर्णांक ngroups;
	काष्ठा pistachio_gpio_bank *gpio_banks;
	अचिन्हित पूर्णांक nbanks;
पूर्ण;

#घोषणा PISTACHIO_PIN_MFIO(p)		(p)
#घोषणा PISTACHIO_PIN_TCK		90
#घोषणा PISTACHIO_PIN_TRSTN		91
#घोषणा PISTACHIO_PIN_TDI		92
#घोषणा PISTACHIO_PIN_TMS		93
#घोषणा PISTACHIO_PIN_TDO		94
#घोषणा PISTACHIO_PIN_JTAG_COMPLY	95
#घोषणा PISTACHIO_PIN_SAFE_MODE		96
#घोषणा PISTACHIO_PIN_POR_DISABLE	97
#घोषणा PISTACHIO_PIN_RESETN		98

#घोषणा MFIO_PIN_DESC(p)	PINCTRL_PIN(PISTACHIO_PIN_MFIO(p), "mfio" #p)

अटल स्थिर काष्ठा pinctrl_pin_desc pistachio_pins[] = अणु
	MFIO_PIN_DESC(0),
	MFIO_PIN_DESC(1),
	MFIO_PIN_DESC(2),
	MFIO_PIN_DESC(3),
	MFIO_PIN_DESC(4),
	MFIO_PIN_DESC(5),
	MFIO_PIN_DESC(6),
	MFIO_PIN_DESC(7),
	MFIO_PIN_DESC(8),
	MFIO_PIN_DESC(9),
	MFIO_PIN_DESC(10),
	MFIO_PIN_DESC(11),
	MFIO_PIN_DESC(12),
	MFIO_PIN_DESC(13),
	MFIO_PIN_DESC(14),
	MFIO_PIN_DESC(15),
	MFIO_PIN_DESC(16),
	MFIO_PIN_DESC(17),
	MFIO_PIN_DESC(18),
	MFIO_PIN_DESC(19),
	MFIO_PIN_DESC(20),
	MFIO_PIN_DESC(21),
	MFIO_PIN_DESC(22),
	MFIO_PIN_DESC(23),
	MFIO_PIN_DESC(24),
	MFIO_PIN_DESC(25),
	MFIO_PIN_DESC(26),
	MFIO_PIN_DESC(27),
	MFIO_PIN_DESC(28),
	MFIO_PIN_DESC(29),
	MFIO_PIN_DESC(30),
	MFIO_PIN_DESC(31),
	MFIO_PIN_DESC(32),
	MFIO_PIN_DESC(33),
	MFIO_PIN_DESC(34),
	MFIO_PIN_DESC(35),
	MFIO_PIN_DESC(36),
	MFIO_PIN_DESC(37),
	MFIO_PIN_DESC(38),
	MFIO_PIN_DESC(39),
	MFIO_PIN_DESC(40),
	MFIO_PIN_DESC(41),
	MFIO_PIN_DESC(42),
	MFIO_PIN_DESC(43),
	MFIO_PIN_DESC(44),
	MFIO_PIN_DESC(45),
	MFIO_PIN_DESC(46),
	MFIO_PIN_DESC(47),
	MFIO_PIN_DESC(48),
	MFIO_PIN_DESC(49),
	MFIO_PIN_DESC(50),
	MFIO_PIN_DESC(51),
	MFIO_PIN_DESC(52),
	MFIO_PIN_DESC(53),
	MFIO_PIN_DESC(54),
	MFIO_PIN_DESC(55),
	MFIO_PIN_DESC(56),
	MFIO_PIN_DESC(57),
	MFIO_PIN_DESC(58),
	MFIO_PIN_DESC(59),
	MFIO_PIN_DESC(60),
	MFIO_PIN_DESC(61),
	MFIO_PIN_DESC(62),
	MFIO_PIN_DESC(63),
	MFIO_PIN_DESC(64),
	MFIO_PIN_DESC(65),
	MFIO_PIN_DESC(66),
	MFIO_PIN_DESC(67),
	MFIO_PIN_DESC(68),
	MFIO_PIN_DESC(69),
	MFIO_PIN_DESC(70),
	MFIO_PIN_DESC(71),
	MFIO_PIN_DESC(72),
	MFIO_PIN_DESC(73),
	MFIO_PIN_DESC(74),
	MFIO_PIN_DESC(75),
	MFIO_PIN_DESC(76),
	MFIO_PIN_DESC(77),
	MFIO_PIN_DESC(78),
	MFIO_PIN_DESC(79),
	MFIO_PIN_DESC(80),
	MFIO_PIN_DESC(81),
	MFIO_PIN_DESC(82),
	MFIO_PIN_DESC(83),
	MFIO_PIN_DESC(84),
	MFIO_PIN_DESC(85),
	MFIO_PIN_DESC(86),
	MFIO_PIN_DESC(87),
	MFIO_PIN_DESC(88),
	MFIO_PIN_DESC(89),
	PINCTRL_PIN(PISTACHIO_PIN_TCK, "tck"),
	PINCTRL_PIN(PISTACHIO_PIN_TRSTN, "trstn"),
	PINCTRL_PIN(PISTACHIO_PIN_TDI, "tdi"),
	PINCTRL_PIN(PISTACHIO_PIN_TMS, "tms"),
	PINCTRL_PIN(PISTACHIO_PIN_TDO, "tdo"),
	PINCTRL_PIN(PISTACHIO_PIN_JTAG_COMPLY, "jtag_comply"),
	PINCTRL_PIN(PISTACHIO_PIN_SAFE_MODE, "safe_mode"),
	PINCTRL_PIN(PISTACHIO_PIN_POR_DISABLE, "por_disable"),
	PINCTRL_PIN(PISTACHIO_PIN_RESETN, "resetn"),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_spim0_groups[] = अणु
	"mfio1", "mfio2", "mfio8", "mfio9", "mfio10", "mfio28", "mfio29",
	"mfio30", "mfio55", "mfio56", "mfio57",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_spim1_groups[] = अणु
	"mfio0", "mfio1", "mfio2", "mfio3", "mfio4", "mfio5", "mfio6",
	"mfio7", "mfio31", "mfio55", "mfio56", "mfio57", "mfio58",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_spis_groups[] = अणु
	"mfio11", "mfio12", "mfio13", "mfio14",
पूर्ण;

अटल स्थिर अक्षर *स्थिर pistachio_sdhost_groups[] = अणु
	"mfio15", "mfio16", "mfio17", "mfio18", "mfio19", "mfio20",
	"mfio21", "mfio22", "mfio23", "mfio24", "mfio25", "mfio26",
	"mfio27",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_i2c0_groups[] = अणु
	"mfio28", "mfio29",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_i2c1_groups[] = अणु
	"mfio30", "mfio31",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_i2c2_groups[] = अणु
	"mfio32", "mfio33",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_i2c3_groups[] = अणु
	"mfio34", "mfio35",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_audio_clk_in_groups[] = अणु
	"mfio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_i2s_out_groups[] = अणु
	"mfio36", "mfio37", "mfio38", "mfio39", "mfio40", "mfio41",
	"mfio42", "mfio43", "mfio44",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_debug_raw_cca_ind_groups[] = अणु
	"mfio37",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_debug_ed_sec20_cca_ind_groups[] = अणु
	"mfio38",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_debug_ed_sec40_cca_ind_groups[] = अणु
	"mfio39",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_debug_agc_करोne_0_groups[] = अणु
	"mfio40",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_debug_agc_करोne_1_groups[] = अणु
	"mfio41",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_debug_ed_cca_ind_groups[] = अणु
	"mfio42",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_debug_s2l_करोne_groups[] = अणु
	"mfio43",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_i2s_dac_clk_groups[] = अणु
	"mfio45",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_audio_sync_groups[] = अणु
	"mfio45",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_audio_trigger_groups[] = अणु
	"mfio46",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_i2s_in_groups[] = अणु
	"mfio47", "mfio48", "mfio49", "mfio50", "mfio51", "mfio52",
	"mfio53", "mfio54",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_uart0_groups[] = अणु
	"mfio55", "mfio56", "mfio57", "mfio58",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_uart1_groups[] = अणु
	"mfio59", "mfio60", "mfio1", "mfio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_spdअगर_out_groups[] = अणु
	"mfio61",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_spdअगर_in_groups[] = अणु
	"mfio62", "mfio54",
पूर्ण;
अटल स्थिर पूर्णांक pistachio_spdअगर_in_scenarios[] = अणु
	PISTACHIO_PIN_MFIO(62),
	PISTACHIO_PIN_MFIO(54),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_eth_groups[] = अणु
	"mfio63", "mfio64", "mfio65", "mfio66", "mfio67", "mfio68",
	"mfio69", "mfio70", "mfio71",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_ir_groups[] = अणु
	"mfio72",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_pwmpdm_groups[] = अणु
	"mfio73", "mfio74", "mfio75", "mfio76",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_trace_clk_groups[] = अणु
	"mfio15", "mfio63", "mfio73",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_trace_dपूर्णांक_groups[] = अणु
	"mfio16", "mfio64", "mfio74",
पूर्ण;
अटल स्थिर पूर्णांक pistachio_mips_trace_dपूर्णांक_scenarios[] = अणु
	PISTACHIO_PIN_MFIO(16),
	PISTACHIO_PIN_MFIO(64),
	PISTACHIO_PIN_MFIO(74),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_trace_trigout_groups[] = अणु
	"mfio17", "mfio65", "mfio75",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_trace_trigin_groups[] = अणु
	"mfio18", "mfio66", "mfio76",
पूर्ण;
अटल स्थिर पूर्णांक pistachio_mips_trace_trigin_scenarios[] = अणु
	PISTACHIO_PIN_MFIO(18),
	PISTACHIO_PIN_MFIO(66),
	PISTACHIO_PIN_MFIO(76),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_trace_dm_groups[] = अणु
	"mfio19", "mfio67", "mfio77",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_probe_n_groups[] = अणु
	"mfio20", "mfio68", "mfio78",
पूर्ण;
अटल स्थिर पूर्णांक pistachio_mips_probe_n_scenarios[] = अणु
	PISTACHIO_PIN_MFIO(20),
	PISTACHIO_PIN_MFIO(68),
	PISTACHIO_PIN_MFIO(78),
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_trace_data_groups[] = अणु
	"mfio15", "mfio16", "mfio17", "mfio18", "mfio19", "mfio20",
	"mfio21", "mfio22", "mfio63", "mfio64", "mfio65", "mfio66",
	"mfio67", "mfio68", "mfio69", "mfio70", "mfio79", "mfio80",
	"mfio81", "mfio82", "mfio83", "mfio84", "mfio85", "mfio86",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_sram_debug_groups[] = अणु
	"mfio73", "mfio74",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_rom_debug_groups[] = अणु
	"mfio75", "mfio76",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_rpu_debug_groups[] = अणु
	"mfio77", "mfio78",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_debug_groups[] = अणु
	"mfio79", "mfio80",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_eth_debug_groups[] = अणु
	"mfio81", "mfio82",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_usb_debug_groups[] = अणु
	"mfio83", "mfio84",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_sdhost_debug_groups[] = अणु
	"mfio85", "mfio86",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_socअगर_debug_groups[] = अणु
	"mfio87", "mfio88",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mdc_debug_groups[] = अणु
	"mfio77", "mfio78",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_ddr_debug_groups[] = अणु
	"mfio79", "mfio80",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_dreq0_groups[] = अणु
	"mfio81",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_dreq1_groups[] = अणु
	"mfio82",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_dreq2_groups[] = अणु
	"mfio87",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_dreq3_groups[] = अणु
	"mfio88",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_dreq4_groups[] = अणु
	"mfio89",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_dreq5_groups[] = अणु
	"mfio89",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_mips_pll_lock_groups[] = अणु
	"mfio83",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_audio_pll_lock_groups[] = अणु
	"mfio84",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_rpu_v_pll_lock_groups[] = अणु
	"mfio85",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_rpu_l_pll_lock_groups[] = अणु
	"mfio86",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_sys_pll_lock_groups[] = अणु
	"mfio87",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_wअगरi_pll_lock_groups[] = अणु
	"mfio88",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pistachio_bt_pll_lock_groups[] = अणु
	"mfio89",
पूर्ण;

#घोषणा FUNCTION(_name)							\
	अणु								\
		.name = #_name,						\
		.groups = pistachio_##_name##_groups,			\
		.ngroups = ARRAY_SIZE(pistachio_##_name##_groups),	\
	पूर्ण

#घोषणा FUNCTION_SCENARIO(_name, _reg, _shअगरt, _mask)			\
	अणु								\
		.name = #_name,						\
		.groups = pistachio_##_name##_groups,			\
		.ngroups = ARRAY_SIZE(pistachio_##_name##_groups),	\
		.scenarios = pistachio_##_name##_scenarios,		\
		.nscenarios = ARRAY_SIZE(pistachio_##_name##_scenarios),\
		.scenario_reg = _reg,					\
		.scenario_shअगरt = _shअगरt,				\
		.scenario_mask = _mask,					\
	पूर्ण

क्रमागत pistachio_mux_option अणु
	PISTACHIO_FUNCTION_NONE = -1,
	PISTACHIO_FUNCTION_SPIM0,
	PISTACHIO_FUNCTION_SPIM1,
	PISTACHIO_FUNCTION_SPIS,
	PISTACHIO_FUNCTION_SDHOST,
	PISTACHIO_FUNCTION_I2C0,
	PISTACHIO_FUNCTION_I2C1,
	PISTACHIO_FUNCTION_I2C2,
	PISTACHIO_FUNCTION_I2C3,
	PISTACHIO_FUNCTION_AUDIO_CLK_IN,
	PISTACHIO_FUNCTION_I2S_OUT,
	PISTACHIO_FUNCTION_I2S_DAC_CLK,
	PISTACHIO_FUNCTION_AUDIO_SYNC,
	PISTACHIO_FUNCTION_AUDIO_TRIGGER,
	PISTACHIO_FUNCTION_I2S_IN,
	PISTACHIO_FUNCTION_UART0,
	PISTACHIO_FUNCTION_UART1,
	PISTACHIO_FUNCTION_SPDIF_OUT,
	PISTACHIO_FUNCTION_SPDIF_IN,
	PISTACHIO_FUNCTION_ETH,
	PISTACHIO_FUNCTION_IR,
	PISTACHIO_FUNCTION_PWMPDM,
	PISTACHIO_FUNCTION_MIPS_TRACE_CLK,
	PISTACHIO_FUNCTION_MIPS_TRACE_DINT,
	PISTACHIO_FUNCTION_MIPS_TRACE_TRIGOUT,
	PISTACHIO_FUNCTION_MIPS_TRACE_TRIGIN,
	PISTACHIO_FUNCTION_MIPS_TRACE_DM,
	PISTACHIO_FUNCTION_MIPS_TRACE_PROBE_N,
	PISTACHIO_FUNCTION_MIPS_TRACE_DATA,
	PISTACHIO_FUNCTION_SRAM_DEBUG,
	PISTACHIO_FUNCTION_ROM_DEBUG,
	PISTACHIO_FUNCTION_RPU_DEBUG,
	PISTACHIO_FUNCTION_MIPS_DEBUG,
	PISTACHIO_FUNCTION_ETH_DEBUG,
	PISTACHIO_FUNCTION_USB_DEBUG,
	PISTACHIO_FUNCTION_SDHOST_DEBUG,
	PISTACHIO_FUNCTION_SOCIF_DEBUG,
	PISTACHIO_FUNCTION_MDC_DEBUG,
	PISTACHIO_FUNCTION_DDR_DEBUG,
	PISTACHIO_FUNCTION_DREQ0,
	PISTACHIO_FUNCTION_DREQ1,
	PISTACHIO_FUNCTION_DREQ2,
	PISTACHIO_FUNCTION_DREQ3,
	PISTACHIO_FUNCTION_DREQ4,
	PISTACHIO_FUNCTION_DREQ5,
	PISTACHIO_FUNCTION_MIPS_PLL_LOCK,
	PISTACHIO_FUNCTION_AUDIO_PLL_LOCK,
	PISTACHIO_FUNCTION_RPU_V_PLL_LOCK,
	PISTACHIO_FUNCTION_RPU_L_PLL_LOCK,
	PISTACHIO_FUNCTION_SYS_PLL_LOCK,
	PISTACHIO_FUNCTION_WIFI_PLL_LOCK,
	PISTACHIO_FUNCTION_BT_PLL_LOCK,
	PISTACHIO_FUNCTION_DEBUG_RAW_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_ED_SEC20_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_ED_SEC40_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_AGC_DONE_0,
	PISTACHIO_FUNCTION_DEBUG_AGC_DONE_1,
	PISTACHIO_FUNCTION_DEBUG_ED_CCA_IND,
	PISTACHIO_FUNCTION_DEBUG_S2L_DONE,
पूर्ण;

अटल स्थिर काष्ठा pistachio_function pistachio_functions[] = अणु
	FUNCTION(spim0),
	FUNCTION(spim1),
	FUNCTION(spis),
	FUNCTION(sdhost),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(audio_clk_in),
	FUNCTION(i2s_out),
	FUNCTION(i2s_dac_clk),
	FUNCTION(audio_sync),
	FUNCTION(audio_trigger),
	FUNCTION(i2s_in),
	FUNCTION(uart0),
	FUNCTION(uart1),
	FUNCTION(spdअगर_out),
	FUNCTION_SCENARIO(spdअगर_in, PADS_SCENARIO_SELECT, 0, 0x1),
	FUNCTION(eth),
	FUNCTION(ir),
	FUNCTION(pwmpdm),
	FUNCTION(mips_trace_clk),
	FUNCTION_SCENARIO(mips_trace_dपूर्णांक, PADS_SCENARIO_SELECT, 1, 0x3),
	FUNCTION(mips_trace_trigout),
	FUNCTION_SCENARIO(mips_trace_trigin, PADS_SCENARIO_SELECT, 3, 0x3),
	FUNCTION(mips_trace_dm),
	FUNCTION_SCENARIO(mips_probe_n, PADS_SCENARIO_SELECT, 5, 0x3),
	FUNCTION(mips_trace_data),
	FUNCTION(sram_debug),
	FUNCTION(rom_debug),
	FUNCTION(rpu_debug),
	FUNCTION(mips_debug),
	FUNCTION(eth_debug),
	FUNCTION(usb_debug),
	FUNCTION(sdhost_debug),
	FUNCTION(socअगर_debug),
	FUNCTION(mdc_debug),
	FUNCTION(ddr_debug),
	FUNCTION(dreq0),
	FUNCTION(dreq1),
	FUNCTION(dreq2),
	FUNCTION(dreq3),
	FUNCTION(dreq4),
	FUNCTION(dreq5),
	FUNCTION(mips_pll_lock),
	FUNCTION(audio_pll_lock),
	FUNCTION(rpu_v_pll_lock),
	FUNCTION(rpu_l_pll_lock),
	FUNCTION(sys_pll_lock),
	FUNCTION(wअगरi_pll_lock),
	FUNCTION(bt_pll_lock),
	FUNCTION(debug_raw_cca_ind),
	FUNCTION(debug_ed_sec20_cca_ind),
	FUNCTION(debug_ed_sec40_cca_ind),
	FUNCTION(debug_agc_करोne_0),
	FUNCTION(debug_agc_करोne_1),
	FUNCTION(debug_ed_cca_ind),
	FUNCTION(debug_s2l_करोne),
पूर्ण;

#घोषणा PIN_GROUP(_pin, _name)					\
	अणु							\
		.name = #_name,					\
		.pin = PISTACHIO_PIN_##_pin,			\
		.mux_option = अणु					\
			PISTACHIO_FUNCTION_NONE,		\
			PISTACHIO_FUNCTION_NONE,		\
			PISTACHIO_FUNCTION_NONE,		\
		पूर्ण,						\
		.mux_reg = -1,					\
		.mux_shअगरt = -1,				\
		.mux_mask = -1,					\
	पूर्ण

#घोषणा MFIO_PIN_GROUP(_pin, _func)				\
	अणु							\
		.name = "mfio" #_pin,				\
		.pin = PISTACHIO_PIN_MFIO(_pin),		\
		.mux_option = अणु					\
			PISTACHIO_FUNCTION_##_func,		\
			PISTACHIO_FUNCTION_NONE,		\
			PISTACHIO_FUNCTION_NONE,		\
		पूर्ण,						\
		.mux_reg = -1,					\
		.mux_shअगरt = -1,				\
		.mux_mask = -1,					\
	पूर्ण

#घोषणा MFIO_MUX_PIN_GROUP(_pin, _f0, _f1, _f2, _reg, _shअगरt, _mask)	\
	अणु								\
		.name = "mfio" #_pin,					\
		.pin = PISTACHIO_PIN_MFIO(_pin),			\
		.mux_option = अणु						\
			PISTACHIO_FUNCTION_##_f0,			\
			PISTACHIO_FUNCTION_##_f1,			\
			PISTACHIO_FUNCTION_##_f2,			\
		पूर्ण,							\
		.mux_reg = _reg,					\
		.mux_shअगरt = _shअगरt,					\
		.mux_mask = _mask,					\
	पूर्ण

अटल स्थिर काष्ठा pistachio_pin_group pistachio_groups[] = अणु
	MFIO_PIN_GROUP(0, SPIM1),
	MFIO_MUX_PIN_GROUP(1, SPIM1, SPIM0, UART1,
			   PADS_FUNCTION_SELECT0, 0, 0x3),
	MFIO_MUX_PIN_GROUP(2, SPIM1, SPIM0, UART1,
			   PADS_FUNCTION_SELECT0, 2, 0x3),
	MFIO_PIN_GROUP(3, SPIM1),
	MFIO_PIN_GROUP(4, SPIM1),
	MFIO_PIN_GROUP(5, SPIM1),
	MFIO_PIN_GROUP(6, SPIM1),
	MFIO_PIN_GROUP(7, SPIM1),
	MFIO_PIN_GROUP(8, SPIM0),
	MFIO_PIN_GROUP(9, SPIM0),
	MFIO_PIN_GROUP(10, SPIM0),
	MFIO_PIN_GROUP(11, SPIS),
	MFIO_PIN_GROUP(12, SPIS),
	MFIO_PIN_GROUP(13, SPIS),
	MFIO_PIN_GROUP(14, SPIS),
	MFIO_MUX_PIN_GROUP(15, SDHOST, MIPS_TRACE_CLK, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 4, 0x3),
	MFIO_MUX_PIN_GROUP(16, SDHOST, MIPS_TRACE_DINT, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 6, 0x3),
	MFIO_MUX_PIN_GROUP(17, SDHOST, MIPS_TRACE_TRIGOUT, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 8, 0x3),
	MFIO_MUX_PIN_GROUP(18, SDHOST, MIPS_TRACE_TRIGIN, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 10, 0x3),
	MFIO_MUX_PIN_GROUP(19, SDHOST, MIPS_TRACE_DM, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 12, 0x3),
	MFIO_MUX_PIN_GROUP(20, SDHOST, MIPS_TRACE_PROBE_N, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 14, 0x3),
	MFIO_MUX_PIN_GROUP(21, SDHOST, NONE, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 16, 0x3),
	MFIO_MUX_PIN_GROUP(22, SDHOST, NONE, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT0, 18, 0x3),
	MFIO_PIN_GROUP(23, SDHOST),
	MFIO_PIN_GROUP(24, SDHOST),
	MFIO_PIN_GROUP(25, SDHOST),
	MFIO_PIN_GROUP(26, SDHOST),
	MFIO_PIN_GROUP(27, SDHOST),
	MFIO_MUX_PIN_GROUP(28, I2C0, SPIM0, NONE,
			   PADS_FUNCTION_SELECT0, 20, 0x1),
	MFIO_MUX_PIN_GROUP(29, I2C0, SPIM0, NONE,
			   PADS_FUNCTION_SELECT0, 21, 0x1),
	MFIO_MUX_PIN_GROUP(30, I2C1, SPIM0, NONE,
			   PADS_FUNCTION_SELECT0, 22, 0x1),
	MFIO_MUX_PIN_GROUP(31, I2C1, SPIM1, NONE,
			   PADS_FUNCTION_SELECT0, 23, 0x1),
	MFIO_PIN_GROUP(32, I2C2),
	MFIO_PIN_GROUP(33, I2C2),
	MFIO_PIN_GROUP(34, I2C3),
	MFIO_PIN_GROUP(35, I2C3),
	MFIO_MUX_PIN_GROUP(36, I2S_OUT, AUDIO_CLK_IN, NONE,
			   PADS_FUNCTION_SELECT0, 24, 0x1),
	MFIO_MUX_PIN_GROUP(37, I2S_OUT, DEBUG_RAW_CCA_IND, NONE,
			   PADS_FUNCTION_SELECT0, 25, 0x1),
	MFIO_MUX_PIN_GROUP(38, I2S_OUT, DEBUG_ED_SEC20_CCA_IND, NONE,
			   PADS_FUNCTION_SELECT0, 26, 0x1),
	MFIO_MUX_PIN_GROUP(39, I2S_OUT, DEBUG_ED_SEC40_CCA_IND, NONE,
			   PADS_FUNCTION_SELECT0, 27, 0x1),
	MFIO_MUX_PIN_GROUP(40, I2S_OUT, DEBUG_AGC_DONE_0, NONE,
			   PADS_FUNCTION_SELECT0, 28, 0x1),
	MFIO_MUX_PIN_GROUP(41, I2S_OUT, DEBUG_AGC_DONE_1, NONE,
			   PADS_FUNCTION_SELECT0, 29, 0x1),
	MFIO_MUX_PIN_GROUP(42, I2S_OUT, DEBUG_ED_CCA_IND, NONE,
			   PADS_FUNCTION_SELECT0, 30, 0x1),
	MFIO_MUX_PIN_GROUP(43, I2S_OUT, DEBUG_S2L_DONE, NONE,
			   PADS_FUNCTION_SELECT0, 31, 0x1),
	MFIO_PIN_GROUP(44, I2S_OUT),
	MFIO_MUX_PIN_GROUP(45, I2S_DAC_CLK, AUDIO_SYNC, NONE,
			   PADS_FUNCTION_SELECT1, 0, 0x1),
	MFIO_PIN_GROUP(46, AUDIO_TRIGGER),
	MFIO_PIN_GROUP(47, I2S_IN),
	MFIO_PIN_GROUP(48, I2S_IN),
	MFIO_PIN_GROUP(49, I2S_IN),
	MFIO_PIN_GROUP(50, I2S_IN),
	MFIO_PIN_GROUP(51, I2S_IN),
	MFIO_PIN_GROUP(52, I2S_IN),
	MFIO_PIN_GROUP(53, I2S_IN),
	MFIO_MUX_PIN_GROUP(54, I2S_IN, NONE, SPDIF_IN,
			   PADS_FUNCTION_SELECT1, 1, 0x3),
	MFIO_MUX_PIN_GROUP(55, UART0, SPIM0, SPIM1,
			   PADS_FUNCTION_SELECT1, 3, 0x3),
	MFIO_MUX_PIN_GROUP(56, UART0, SPIM0, SPIM1,
			   PADS_FUNCTION_SELECT1, 5, 0x3),
	MFIO_MUX_PIN_GROUP(57, UART0, SPIM0, SPIM1,
			   PADS_FUNCTION_SELECT1, 7, 0x3),
	MFIO_MUX_PIN_GROUP(58, UART0, SPIM1, NONE,
			   PADS_FUNCTION_SELECT1, 9, 0x1),
	MFIO_PIN_GROUP(59, UART1),
	MFIO_PIN_GROUP(60, UART1),
	MFIO_PIN_GROUP(61, SPDIF_OUT),
	MFIO_PIN_GROUP(62, SPDIF_IN),
	MFIO_MUX_PIN_GROUP(63, ETH, MIPS_TRACE_CLK, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 10, 0x3),
	MFIO_MUX_PIN_GROUP(64, ETH, MIPS_TRACE_DINT, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 12, 0x3),
	MFIO_MUX_PIN_GROUP(65, ETH, MIPS_TRACE_TRIGOUT, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 14, 0x3),
	MFIO_MUX_PIN_GROUP(66, ETH, MIPS_TRACE_TRIGIN, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 16, 0x3),
	MFIO_MUX_PIN_GROUP(67, ETH, MIPS_TRACE_DM, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 18, 0x3),
	MFIO_MUX_PIN_GROUP(68, ETH, MIPS_TRACE_PROBE_N, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 20, 0x3),
	MFIO_MUX_PIN_GROUP(69, ETH, NONE, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 22, 0x3),
	MFIO_MUX_PIN_GROUP(70, ETH, NONE, MIPS_TRACE_DATA,
			   PADS_FUNCTION_SELECT1, 24, 0x3),
	MFIO_PIN_GROUP(71, ETH),
	MFIO_PIN_GROUP(72, IR),
	MFIO_MUX_PIN_GROUP(73, PWMPDM, MIPS_TRACE_CLK, SRAM_DEBUG,
			   PADS_FUNCTION_SELECT1, 26, 0x3),
	MFIO_MUX_PIN_GROUP(74, PWMPDM, MIPS_TRACE_DINT, SRAM_DEBUG,
			   PADS_FUNCTION_SELECT1, 28, 0x3),
	MFIO_MUX_PIN_GROUP(75, PWMPDM, MIPS_TRACE_TRIGOUT, ROM_DEBUG,
			   PADS_FUNCTION_SELECT1, 30, 0x3),
	MFIO_MUX_PIN_GROUP(76, PWMPDM, MIPS_TRACE_TRIGIN, ROM_DEBUG,
			   PADS_FUNCTION_SELECT2, 0, 0x3),
	MFIO_MUX_PIN_GROUP(77, MDC_DEBUG, MIPS_TRACE_DM, RPU_DEBUG,
			   PADS_FUNCTION_SELECT2, 2, 0x3),
	MFIO_MUX_PIN_GROUP(78, MDC_DEBUG, MIPS_TRACE_PROBE_N, RPU_DEBUG,
			   PADS_FUNCTION_SELECT2, 4, 0x3),
	MFIO_MUX_PIN_GROUP(79, DDR_DEBUG, MIPS_TRACE_DATA, MIPS_DEBUG,
			   PADS_FUNCTION_SELECT2, 6, 0x3),
	MFIO_MUX_PIN_GROUP(80, DDR_DEBUG, MIPS_TRACE_DATA, MIPS_DEBUG,
			   PADS_FUNCTION_SELECT2, 8, 0x3),
	MFIO_MUX_PIN_GROUP(81, DREQ0, MIPS_TRACE_DATA, ETH_DEBUG,
			   PADS_FUNCTION_SELECT2, 10, 0x3),
	MFIO_MUX_PIN_GROUP(82, DREQ1, MIPS_TRACE_DATA, ETH_DEBUG,
			   PADS_FUNCTION_SELECT2, 12, 0x3),
	MFIO_MUX_PIN_GROUP(83, MIPS_PLL_LOCK, MIPS_TRACE_DATA, USB_DEBUG,
			   PADS_FUNCTION_SELECT2, 14, 0x3),
	MFIO_MUX_PIN_GROUP(84, AUDIO_PLL_LOCK, MIPS_TRACE_DATA, USB_DEBUG,
			   PADS_FUNCTION_SELECT2, 16, 0x3),
	MFIO_MUX_PIN_GROUP(85, RPU_V_PLL_LOCK, MIPS_TRACE_DATA, SDHOST_DEBUG,
			   PADS_FUNCTION_SELECT2, 18, 0x3),
	MFIO_MUX_PIN_GROUP(86, RPU_L_PLL_LOCK, MIPS_TRACE_DATA, SDHOST_DEBUG,
			   PADS_FUNCTION_SELECT2, 20, 0x3),
	MFIO_MUX_PIN_GROUP(87, SYS_PLL_LOCK, DREQ2, SOCIF_DEBUG,
			   PADS_FUNCTION_SELECT2, 22, 0x3),
	MFIO_MUX_PIN_GROUP(88, WIFI_PLL_LOCK, DREQ3, SOCIF_DEBUG,
			   PADS_FUNCTION_SELECT2, 24, 0x3),
	MFIO_MUX_PIN_GROUP(89, BT_PLL_LOCK, DREQ4, DREQ5,
			   PADS_FUNCTION_SELECT2, 26, 0x3),
	PIN_GROUP(TCK, "tck"),
	PIN_GROUP(TRSTN, "trstn"),
	PIN_GROUP(TDI, "tdi"),
	PIN_GROUP(TMS, "tms"),
	PIN_GROUP(TDO, "tdo"),
	PIN_GROUP(JTAG_COMPLY, "jtag_comply"),
	PIN_GROUP(SAFE_MODE, "safe_mode"),
	PIN_GROUP(POR_DISABLE, "por_disable"),
	PIN_GROUP(RESETN, "resetn"),
पूर्ण;

अटल अंतरभूत u32 pctl_पढ़ोl(काष्ठा pistachio_pinctrl *pctl, u32 reg)
अणु
	वापस पढ़ोl(pctl->base + reg);
पूर्ण

अटल अंतरभूत व्योम pctl_ग_लिखोl(काष्ठा pistachio_pinctrl *pctl, u32 val, u32 reg)
अणु
	ग_लिखोl(val, pctl->base + reg);
पूर्ण

अटल अंतरभूत काष्ठा pistachio_gpio_bank *irqd_to_bank(काष्ठा irq_data *d)
अणु
	वापस gpiochip_get_data(irq_data_get_irq_chip_data(d));
पूर्ण

अटल अंतरभूत u32 gpio_पढ़ोl(काष्ठा pistachio_gpio_bank *bank, u32 reg)
अणु
	वापस पढ़ोl(bank->base + reg);
पूर्ण

अटल अंतरभूत व्योम gpio_ग_लिखोl(काष्ठा pistachio_gpio_bank *bank, u32 val,
			       u32 reg)
अणु
	ग_लिखोl(val, bank->base + reg);
पूर्ण

अटल अंतरभूत व्योम gpio_mask_ग_लिखोl(काष्ठा pistachio_gpio_bank *bank,
				    u32 reg, अचिन्हित पूर्णांक bit, u32 val)
अणु
	/*
	 * For most of the GPIO रेजिस्टरs, bit 16 + X must be set in order to
	 * ग_लिखो bit X.
	 */
	gpio_ग_लिखोl(bank, (0x10000 | val) << bit, reg);
पूर्ण

अटल अंतरभूत व्योम gpio_enable(काष्ठा pistachio_gpio_bank *bank,
			       अचिन्हित offset)
अणु
	gpio_mask_ग_लिखोl(bank, GPIO_BIT_EN, offset, 1);
पूर्ण

अटल अंतरभूत व्योम gpio_disable(काष्ठा pistachio_gpio_bank *bank,
				अचिन्हित offset)
अणु
	gpio_mask_ग_लिखोl(bank, GPIO_BIT_EN, offset, 0);
पूर्ण

अटल पूर्णांक pistachio_pinctrl_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->ngroups;
पूर्ण

अटल स्थिर अक्षर *pistachio_pinctrl_get_group_name(काष्ठा pinctrl_dev *pctldev,
						    अचिन्हित group)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->groups[group].name;
पूर्ण

अटल पूर्णांक pistachio_pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित group,
					    स्थिर अचिन्हित **pins,
					    अचिन्हित *num_pins)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*pins = &pctl->groups[group].pin;
	*num_pins = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops pistachio_pinctrl_ops = अणु
	.get_groups_count = pistachio_pinctrl_get_groups_count,
	.get_group_name = pistachio_pinctrl_get_group_name,
	.get_group_pins = pistachio_pinctrl_get_group_pins,
	.dt_node_to_map = pinconf_generic_dt_node_to_map_pin,
	.dt_मुक्त_map = pinctrl_utils_मुक्त_map,
पूर्ण;

अटल पूर्णांक pistachio_pinmux_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->nfunctions;
पूर्ण

अटल स्थिर अक्षर *
pistachio_pinmux_get_function_name(काष्ठा pinctrl_dev *pctldev, अचिन्हित func)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctl->functions[func].name;
पूर्ण

अटल पूर्णांक pistachio_pinmux_get_function_groups(काष्ठा pinctrl_dev *pctldev,
						अचिन्हित func,
						स्थिर अक्षर * स्थिर **groups,
						अचिन्हित * स्थिर num_groups)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctl->functions[func].groups;
	*num_groups = pctl->functions[func].ngroups;

	वापस 0;
पूर्ण

अटल पूर्णांक pistachio_pinmux_enable(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित func, अचिन्हित group)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा pistachio_pin_group *pg = &pctl->groups[group];
	स्थिर काष्ठा pistachio_function *pf = &pctl->functions[func];
	काष्ठा pinctrl_gpio_range *range;
	अचिन्हित पूर्णांक i;
	u32 val;

	अगर (pg->mux_reg > 0) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pg->mux_option); i++) अणु
			अगर (pg->mux_option[i] == func)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(pg->mux_option)) अणु
			dev_err(pctl->dev, "Cannot mux pin %u to function %u\n",
				group, func);
			वापस -EINVAL;
		पूर्ण

		val = pctl_पढ़ोl(pctl, pg->mux_reg);
		val &= ~(pg->mux_mask << pg->mux_shअगरt);
		val |= i << pg->mux_shअगरt;
		pctl_ग_लिखोl(pctl, val, pg->mux_reg);

		अगर (pf->scenarios) अणु
			क्रम (i = 0; i < pf->nscenarios; i++) अणु
				अगर (pf->scenarios[i] == group)
					अवरोध;
			पूर्ण
			अगर (WARN_ON(i == pf->nscenarios))
				वापस -EINVAL;

			val = pctl_पढ़ोl(pctl, pf->scenario_reg);
			val &= ~(pf->scenario_mask << pf->scenario_shअगरt);
			val |= i << pf->scenario_shअगरt;
			pctl_ग_लिखोl(pctl, val, pf->scenario_reg);
		पूर्ण
	पूर्ण

	range = pinctrl_find_gpio_range_from_pin(pctl->pctldev, pg->pin);
	अगर (range)
		gpio_disable(gpiochip_get_data(range->gc), pg->pin - range->pin_base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops pistachio_pinmux_ops = अणु
	.get_functions_count = pistachio_pinmux_get_functions_count,
	.get_function_name = pistachio_pinmux_get_function_name,
	.get_function_groups = pistachio_pinmux_get_function_groups,
	.set_mux = pistachio_pinmux_enable,
पूर्ण;

अटल पूर्णांक pistachio_pinconf_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
				 अचिन्हित दीर्घ *config)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u32 val, arg;

	चयन (param) अणु
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		val = pctl_पढ़ोl(pctl, PADS_SCHMITT_EN_REG(pin));
		arg = !!(val & PADS_SCHMITT_EN_BIT(pin));
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_HIGHZ;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_UP;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_DOWN;
		अवरोध;
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
		val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin)) >>
			PADS_PU_PD_SHIFT(pin);
		arg = (val & PADS_PU_PD_MASK) == PADS_PU_PD_BUS;
		अवरोध;
	हाल PIN_CONFIG_SLEW_RATE:
		val = pctl_पढ़ोl(pctl, PADS_SLEW_RATE_REG(pin));
		arg = !!(val & PADS_SLEW_RATE_BIT(pin));
		अवरोध;
	हाल PIN_CONFIG_DRIVE_STRENGTH:
		val = pctl_पढ़ोl(pctl, PADS_DRIVE_STRENGTH_REG(pin)) >>
			PADS_DRIVE_STRENGTH_SHIFT(pin);
		चयन (val & PADS_DRIVE_STRENGTH_MASK) अणु
		हाल PADS_DRIVE_STRENGTH_2MA:
			arg = 2;
			अवरोध;
		हाल PADS_DRIVE_STRENGTH_4MA:
			arg = 4;
			अवरोध;
		हाल PADS_DRIVE_STRENGTH_8MA:
			arg = 8;
			अवरोध;
		हाल PADS_DRIVE_STRENGTH_12MA:
		शेष:
			arg = 12;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		dev_dbg(pctl->dev, "Property %u not supported\n", param);
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);

	वापस 0;
पूर्ण

अटल पूर्णांक pistachio_pinconf_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
				 अचिन्हित दीर्घ *configs, अचिन्हित num_configs)
अणु
	काष्ठा pistachio_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param;
	u32 drv, val, arg;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_configs; i++) अणु
		param = pinconf_to_config_param(configs[i]);
		arg = pinconf_to_config_argument(configs[i]);

		चयन (param) अणु
		हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
			val = pctl_पढ़ोl(pctl, PADS_SCHMITT_EN_REG(pin));
			अगर (arg)
				val |= PADS_SCHMITT_EN_BIT(pin);
			अन्यथा
				val &= ~PADS_SCHMITT_EN_BIT(pin);
			pctl_ग_लिखोl(pctl, val, PADS_SCHMITT_EN_REG(pin));
			अवरोध;
		हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
			val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin));
			val &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			val |= PADS_PU_PD_HIGHZ << PADS_PU_PD_SHIFT(pin);
			pctl_ग_लिखोl(pctl, val, PADS_PU_PD_REG(pin));
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_UP:
			val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin));
			val &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			val |= PADS_PU_PD_UP << PADS_PU_PD_SHIFT(pin);
			pctl_ग_लिखोl(pctl, val, PADS_PU_PD_REG(pin));
			अवरोध;
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin));
			val &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			val |= PADS_PU_PD_DOWN << PADS_PU_PD_SHIFT(pin);
			pctl_ग_लिखोl(pctl, val, PADS_PU_PD_REG(pin));
			अवरोध;
		हाल PIN_CONFIG_BIAS_BUS_HOLD:
			val = pctl_पढ़ोl(pctl, PADS_PU_PD_REG(pin));
			val &= ~(PADS_PU_PD_MASK << PADS_PU_PD_SHIFT(pin));
			val |= PADS_PU_PD_BUS << PADS_PU_PD_SHIFT(pin);
			pctl_ग_लिखोl(pctl, val, PADS_PU_PD_REG(pin));
			अवरोध;
		हाल PIN_CONFIG_SLEW_RATE:
			val = pctl_पढ़ोl(pctl, PADS_SLEW_RATE_REG(pin));
			अगर (arg)
				val |= PADS_SLEW_RATE_BIT(pin);
			अन्यथा
				val &= ~PADS_SLEW_RATE_BIT(pin);
			pctl_ग_लिखोl(pctl, val, PADS_SLEW_RATE_REG(pin));
			अवरोध;
		हाल PIN_CONFIG_DRIVE_STRENGTH:
			val = pctl_पढ़ोl(pctl, PADS_DRIVE_STRENGTH_REG(pin));
			val &= ~(PADS_DRIVE_STRENGTH_MASK <<
				 PADS_DRIVE_STRENGTH_SHIFT(pin));
			चयन (arg) अणु
			हाल 2:
				drv = PADS_DRIVE_STRENGTH_2MA;
				अवरोध;
			हाल 4:
				drv = PADS_DRIVE_STRENGTH_4MA;
				अवरोध;
			हाल 8:
				drv = PADS_DRIVE_STRENGTH_8MA;
				अवरोध;
			हाल 12:
				drv = PADS_DRIVE_STRENGTH_12MA;
				अवरोध;
			शेष:
				dev_err(pctl->dev,
					"Drive strength %umA not supported\n",
					arg);
				वापस -EINVAL;
			पूर्ण
			val |= drv << PADS_DRIVE_STRENGTH_SHIFT(pin);
			pctl_ग_लिखोl(pctl, val, PADS_DRIVE_STRENGTH_REG(pin));
			अवरोध;
		शेष:
			dev_err(pctl->dev, "Property %u not supported\n",
				param);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops pistachio_pinconf_ops = अणु
	.pin_config_get = pistachio_pinconf_get,
	.pin_config_set = pistachio_pinconf_set,
	.is_generic = true,
पूर्ण;

अटल काष्ठा pinctrl_desc pistachio_pinctrl_desc = अणु
	.name = "pistachio-pinctrl",
	.pctlops = &pistachio_pinctrl_ops,
	.pmxops = &pistachio_pinmux_ops,
	.confops = &pistachio_pinconf_ops,
पूर्ण;

अटल पूर्णांक pistachio_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	अगर (gpio_पढ़ोl(bank, GPIO_OUTPUT_EN) & BIT(offset))
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक pistachio_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा pistachio_gpio_bank *bank = gpiochip_get_data(chip);
	u32 reg;

	अगर (gpio_पढ़ोl(bank, GPIO_OUTPUT_EN) & BIT(offset))
		reg = GPIO_OUTPUT;
	अन्यथा
		reg = GPIO_INPUT;

	वापस !!(gpio_पढ़ोl(bank, reg) & BIT(offset));
पूर्ण

अटल व्योम pistachio_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset,
			       पूर्णांक value)
अणु
	काष्ठा pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	gpio_mask_ग_लिखोl(bank, GPIO_OUTPUT, offset, !!value);
पूर्ण

अटल पूर्णांक pistachio_gpio_direction_input(काष्ठा gpio_chip *chip,
					  अचिन्हित offset)
अणु
	काष्ठा pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	gpio_mask_ग_लिखोl(bank, GPIO_OUTPUT_EN, offset, 0);
	gpio_enable(bank, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक pistachio_gpio_direction_output(काष्ठा gpio_chip *chip,
					   अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा pistachio_gpio_bank *bank = gpiochip_get_data(chip);

	pistachio_gpio_set(chip, offset, value);
	gpio_mask_ग_लिखोl(bank, GPIO_OUTPUT_EN, offset, 1);
	gpio_enable(bank, offset);

	वापस 0;
पूर्ण

अटल व्योम pistachio_gpio_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा pistachio_gpio_bank *bank = irqd_to_bank(data);

	gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_STATUS, data->hwirq, 0);
पूर्ण

अटल व्योम pistachio_gpio_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा pistachio_gpio_bank *bank = irqd_to_bank(data);

	gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_EN, data->hwirq, 0);
पूर्ण

अटल व्योम pistachio_gpio_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा pistachio_gpio_bank *bank = irqd_to_bank(data);

	gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_EN, data->hwirq, 1);
पूर्ण

अटल अचिन्हित पूर्णांक pistachio_gpio_irq_startup(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);

	pistachio_gpio_direction_input(chip, data->hwirq);
	pistachio_gpio_irq_unmask(data);

	वापस 0;
पूर्ण

अटल पूर्णांक pistachio_gpio_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा pistachio_gpio_bank *bank = irqd_to_bank(data);

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		gpio_mask_ग_लिखोl(bank, GPIO_INPUT_POLARITY, data->hwirq, 1);
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_EDGE);
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_EDGE, data->hwirq,
				 GPIO_INTERRUPT_EDGE_SINGLE);
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		gpio_mask_ग_लिखोl(bank, GPIO_INPUT_POLARITY, data->hwirq, 0);
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_EDGE);
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_EDGE, data->hwirq,
				 GPIO_INTERRUPT_EDGE_SINGLE);
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_EDGE);
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_EDGE, data->hwirq,
				 GPIO_INTERRUPT_EDGE_DUAL);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		gpio_mask_ग_लिखोl(bank, GPIO_INPUT_POLARITY, data->hwirq, 1);
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_LEVEL);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		gpio_mask_ग_लिखोl(bank, GPIO_INPUT_POLARITY, data->hwirq, 0);
		gpio_mask_ग_लिखोl(bank, GPIO_INTERRUPT_TYPE, data->hwirq,
				 GPIO_INTERRUPT_TYPE_LEVEL);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(data, handle_level_irq);
	अन्यथा
		irq_set_handler_locked(data, handle_edge_irq);

	वापस 0;
पूर्ण

अटल व्योम pistachio_gpio_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा gpio_chip *gc = irq_desc_get_handler_data(desc);
	काष्ठा pistachio_gpio_bank *bank = gpiochip_get_data(gc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ pending;
	अचिन्हित पूर्णांक pin;

	chained_irq_enter(chip, desc);
	pending = gpio_पढ़ोl(bank, GPIO_INTERRUPT_STATUS) &
		gpio_पढ़ोl(bank, GPIO_INTERRUPT_EN);
	क्रम_each_set_bit(pin, &pending, 16)
		generic_handle_irq(irq_linear_revmap(gc->irq.करोमुख्य, pin));
	chained_irq_निकास(chip, desc);
पूर्ण

#घोषणा GPIO_BANK(_bank, _pin_base, _npins)				\
	अणु								\
		.pin_base = _pin_base,					\
		.npins = _npins,					\
		.gpio_chip = अणु						\
			.label = "GPIO" #_bank,				\
			.request = gpiochip_generic_request,		\
			.मुक्त = gpiochip_generic_मुक्त,			\
			.get_direction = pistachio_gpio_get_direction,	\
			.direction_input = pistachio_gpio_direction_input, \
			.direction_output = pistachio_gpio_direction_output, \
			.get = pistachio_gpio_get,			\
			.set = pistachio_gpio_set,			\
			.base = _pin_base,				\
			.ngpio = _npins,				\
		पूर्ण,							\
		.irq_chip = अणु						\
			.name = "GPIO" #_bank,				\
			.irq_startup = pistachio_gpio_irq_startup,	\
			.irq_ack = pistachio_gpio_irq_ack,		\
			.irq_mask = pistachio_gpio_irq_mask,		\
			.irq_unmask = pistachio_gpio_irq_unmask,	\
			.irq_set_type = pistachio_gpio_irq_set_type,	\
		पूर्ण,							\
	पूर्ण

अटल काष्ठा pistachio_gpio_bank pistachio_gpio_banks[] = अणु
	GPIO_BANK(0, PISTACHIO_PIN_MFIO(0), 16),
	GPIO_BANK(1, PISTACHIO_PIN_MFIO(16), 16),
	GPIO_BANK(2, PISTACHIO_PIN_MFIO(32), 16),
	GPIO_BANK(3, PISTACHIO_PIN_MFIO(48), 16),
	GPIO_BANK(4, PISTACHIO_PIN_MFIO(64), 16),
	GPIO_BANK(5, PISTACHIO_PIN_MFIO(80), 10),
पूर्ण;

अटल पूर्णांक pistachio_gpio_रेजिस्टर(काष्ठा pistachio_pinctrl *pctl)
अणु
	काष्ठा device_node *node = pctl->dev->of_node;
	काष्ठा pistachio_gpio_bank *bank;
	अचिन्हित पूर्णांक i;
	पूर्णांक irq, ret = 0;

	क्रम (i = 0; i < pctl->nbanks; i++) अणु
		अक्षर child_name[माप("gpioXX")];
		काष्ठा device_node *child;
		काष्ठा gpio_irq_chip *girq;

		snम_लिखो(child_name, माप(child_name), "gpio%d", i);
		child = of_get_child_by_name(node, child_name);
		अगर (!child) अणु
			dev_err(pctl->dev, "No node for bank %u\n", i);
			ret = -ENODEV;
			जाओ err;
		पूर्ण

		अगर (!of_find_property(child, "gpio-controller", शून्य)) अणु
			dev_err(pctl->dev,
				"No gpio-controller property for bank %u\n", i);
			of_node_put(child);
			ret = -ENODEV;
			जाओ err;
		पूर्ण

		irq = irq_of_parse_and_map(child, 0);
		अगर (irq < 0) अणु
			dev_err(pctl->dev, "No IRQ for bank %u: %d\n", i, irq);
			of_node_put(child);
			ret = irq;
			जाओ err;
		पूर्ण

		bank = &pctl->gpio_banks[i];
		bank->pctl = pctl;
		bank->base = pctl->base + GPIO_BANK_BASE(i);

		bank->gpio_chip.parent = pctl->dev;
		bank->gpio_chip.of_node = child;

		girq = &bank->gpio_chip.irq;
		girq->chip = &bank->irq_chip;
		girq->parent_handler = pistachio_gpio_irq_handler;
		girq->num_parents = 1;
		girq->parents = devm_kसुस्मृति(pctl->dev, 1,
					     माप(*girq->parents),
					     GFP_KERNEL);
		अगर (!girq->parents) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		girq->parents[0] = irq;
		girq->शेष_type = IRQ_TYPE_NONE;
		girq->handler = handle_level_irq;

		ret = gpiochip_add_data(&bank->gpio_chip, bank);
		अगर (ret < 0) अणु
			dev_err(pctl->dev, "Failed to add GPIO chip %u: %d\n",
				i, ret);
			जाओ err;
		पूर्ण

		ret = gpiochip_add_pin_range(&bank->gpio_chip,
					     dev_name(pctl->dev), 0,
					     bank->pin_base, bank->npins);
		अगर (ret < 0) अणु
			dev_err(pctl->dev, "Failed to add GPIO range %u: %d\n",
				i, ret);
			gpiochip_हटाओ(&bank->gpio_chip);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	क्रम (; i > 0; i--) अणु
		bank = &pctl->gpio_banks[i - 1];
		gpiochip_हटाओ(&bank->gpio_chip);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id pistachio_pinctrl_of_match[] = अणु
	अणु .compatible = "img,pistachio-system-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक pistachio_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pistachio_pinctrl *pctl;

	pctl = devm_kzalloc(&pdev->dev, माप(*pctl), GFP_KERNEL);
	अगर (!pctl)
		वापस -ENOMEM;
	pctl->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, pctl);

	pctl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pctl->base))
		वापस PTR_ERR(pctl->base);

	pctl->pins = pistachio_pins;
	pctl->npins = ARRAY_SIZE(pistachio_pins);
	pctl->functions = pistachio_functions;
	pctl->nfunctions = ARRAY_SIZE(pistachio_functions);
	pctl->groups = pistachio_groups;
	pctl->ngroups = ARRAY_SIZE(pistachio_groups);
	pctl->gpio_banks = pistachio_gpio_banks;
	pctl->nbanks = ARRAY_SIZE(pistachio_gpio_banks);

	pistachio_pinctrl_desc.pins = pctl->pins;
	pistachio_pinctrl_desc.npins = pctl->npins;

	pctl->pctldev = devm_pinctrl_रेजिस्टर(&pdev->dev, &pistachio_pinctrl_desc,
					      pctl);
	अगर (IS_ERR(pctl->pctldev)) अणु
		dev_err(&pdev->dev, "Failed to register pinctrl device\n");
		वापस PTR_ERR(pctl->pctldev);
	पूर्ण

	वापस pistachio_gpio_रेजिस्टर(pctl);
पूर्ण

अटल काष्ठा platक्रमm_driver pistachio_pinctrl_driver = अणु
	.driver = अणु
		.name = "pistachio-pinctrl",
		.of_match_table = pistachio_pinctrl_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = pistachio_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init pistachio_pinctrl_रेजिस्टर(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pistachio_pinctrl_driver);
पूर्ण
arch_initcall(pistachio_pinctrl_रेजिस्टर);
