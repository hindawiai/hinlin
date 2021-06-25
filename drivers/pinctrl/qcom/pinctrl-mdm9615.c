<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, Sony Mobile Communications AB.
 * Copyright (c) 2016 BayLibre, SAS.
 * Author : Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>

#समावेश "pinctrl-msm.h"

अटल स्थिर काष्ठा pinctrl_pin_desc mdm9615_pins[] = अणु
	PINCTRL_PIN(0, "GPIO_0"),
	PINCTRL_PIN(1, "GPIO_1"),
	PINCTRL_PIN(2, "GPIO_2"),
	PINCTRL_PIN(3, "GPIO_3"),
	PINCTRL_PIN(4, "GPIO_4"),
	PINCTRL_PIN(5, "GPIO_5"),
	PINCTRL_PIN(6, "GPIO_6"),
	PINCTRL_PIN(7, "GPIO_7"),
	PINCTRL_PIN(8, "GPIO_8"),
	PINCTRL_PIN(9, "GPIO_9"),
	PINCTRL_PIN(10, "GPIO_10"),
	PINCTRL_PIN(11, "GPIO_11"),
	PINCTRL_PIN(12, "GPIO_12"),
	PINCTRL_PIN(13, "GPIO_13"),
	PINCTRL_PIN(14, "GPIO_14"),
	PINCTRL_PIN(15, "GPIO_15"),
	PINCTRL_PIN(16, "GPIO_16"),
	PINCTRL_PIN(17, "GPIO_17"),
	PINCTRL_PIN(18, "GPIO_18"),
	PINCTRL_PIN(19, "GPIO_19"),
	PINCTRL_PIN(20, "GPIO_20"),
	PINCTRL_PIN(21, "GPIO_21"),
	PINCTRL_PIN(22, "GPIO_22"),
	PINCTRL_PIN(23, "GPIO_23"),
	PINCTRL_PIN(24, "GPIO_24"),
	PINCTRL_PIN(25, "GPIO_25"),
	PINCTRL_PIN(26, "GPIO_26"),
	PINCTRL_PIN(27, "GPIO_27"),
	PINCTRL_PIN(28, "GPIO_28"),
	PINCTRL_PIN(29, "GPIO_29"),
	PINCTRL_PIN(30, "GPIO_30"),
	PINCTRL_PIN(31, "GPIO_31"),
	PINCTRL_PIN(32, "GPIO_32"),
	PINCTRL_PIN(33, "GPIO_33"),
	PINCTRL_PIN(34, "GPIO_34"),
	PINCTRL_PIN(35, "GPIO_35"),
	PINCTRL_PIN(36, "GPIO_36"),
	PINCTRL_PIN(37, "GPIO_37"),
	PINCTRL_PIN(38, "GPIO_38"),
	PINCTRL_PIN(39, "GPIO_39"),
	PINCTRL_PIN(40, "GPIO_40"),
	PINCTRL_PIN(41, "GPIO_41"),
	PINCTRL_PIN(42, "GPIO_42"),
	PINCTRL_PIN(43, "GPIO_43"),
	PINCTRL_PIN(44, "GPIO_44"),
	PINCTRL_PIN(45, "GPIO_45"),
	PINCTRL_PIN(46, "GPIO_46"),
	PINCTRL_PIN(47, "GPIO_47"),
	PINCTRL_PIN(48, "GPIO_48"),
	PINCTRL_PIN(49, "GPIO_49"),
	PINCTRL_PIN(50, "GPIO_50"),
	PINCTRL_PIN(51, "GPIO_51"),
	PINCTRL_PIN(52, "GPIO_52"),
	PINCTRL_PIN(53, "GPIO_53"),
	PINCTRL_PIN(54, "GPIO_54"),
	PINCTRL_PIN(55, "GPIO_55"),
	PINCTRL_PIN(56, "GPIO_56"),
	PINCTRL_PIN(57, "GPIO_57"),
	PINCTRL_PIN(58, "GPIO_58"),
	PINCTRL_PIN(59, "GPIO_59"),
	PINCTRL_PIN(60, "GPIO_60"),
	PINCTRL_PIN(61, "GPIO_61"),
	PINCTRL_PIN(62, "GPIO_62"),
	PINCTRL_PIN(63, "GPIO_63"),
	PINCTRL_PIN(64, "GPIO_64"),
	PINCTRL_PIN(65, "GPIO_65"),
	PINCTRL_PIN(66, "GPIO_66"),
	PINCTRL_PIN(67, "GPIO_67"),
	PINCTRL_PIN(68, "GPIO_68"),
	PINCTRL_PIN(69, "GPIO_69"),
	PINCTRL_PIN(70, "GPIO_70"),
	PINCTRL_PIN(71, "GPIO_71"),
	PINCTRL_PIN(72, "GPIO_72"),
	PINCTRL_PIN(73, "GPIO_73"),
	PINCTRL_PIN(74, "GPIO_74"),
	PINCTRL_PIN(75, "GPIO_75"),
	PINCTRL_PIN(76, "GPIO_76"),
	PINCTRL_PIN(77, "GPIO_77"),
	PINCTRL_PIN(78, "GPIO_78"),
	PINCTRL_PIN(79, "GPIO_79"),
	PINCTRL_PIN(80, "GPIO_80"),
	PINCTRL_PIN(81, "GPIO_81"),
	PINCTRL_PIN(82, "GPIO_82"),
	PINCTRL_PIN(83, "GPIO_83"),
	PINCTRL_PIN(84, "GPIO_84"),
	PINCTRL_PIN(85, "GPIO_85"),
	PINCTRL_PIN(86, "GPIO_86"),
	PINCTRL_PIN(87, "GPIO_87"),
पूर्ण;

#घोषणा DECLARE_MSM_GPIO_PINS(pin) \
	अटल स्थिर अचिन्हित पूर्णांक gpio##pin##_pins[] = अणु pin पूर्ण
DECLARE_MSM_GPIO_PINS(0);
DECLARE_MSM_GPIO_PINS(1);
DECLARE_MSM_GPIO_PINS(2);
DECLARE_MSM_GPIO_PINS(3);
DECLARE_MSM_GPIO_PINS(4);
DECLARE_MSM_GPIO_PINS(5);
DECLARE_MSM_GPIO_PINS(6);
DECLARE_MSM_GPIO_PINS(7);
DECLARE_MSM_GPIO_PINS(8);
DECLARE_MSM_GPIO_PINS(9);
DECLARE_MSM_GPIO_PINS(10);
DECLARE_MSM_GPIO_PINS(11);
DECLARE_MSM_GPIO_PINS(12);
DECLARE_MSM_GPIO_PINS(13);
DECLARE_MSM_GPIO_PINS(14);
DECLARE_MSM_GPIO_PINS(15);
DECLARE_MSM_GPIO_PINS(16);
DECLARE_MSM_GPIO_PINS(17);
DECLARE_MSM_GPIO_PINS(18);
DECLARE_MSM_GPIO_PINS(19);
DECLARE_MSM_GPIO_PINS(20);
DECLARE_MSM_GPIO_PINS(21);
DECLARE_MSM_GPIO_PINS(22);
DECLARE_MSM_GPIO_PINS(23);
DECLARE_MSM_GPIO_PINS(24);
DECLARE_MSM_GPIO_PINS(25);
DECLARE_MSM_GPIO_PINS(26);
DECLARE_MSM_GPIO_PINS(27);
DECLARE_MSM_GPIO_PINS(28);
DECLARE_MSM_GPIO_PINS(29);
DECLARE_MSM_GPIO_PINS(30);
DECLARE_MSM_GPIO_PINS(31);
DECLARE_MSM_GPIO_PINS(32);
DECLARE_MSM_GPIO_PINS(33);
DECLARE_MSM_GPIO_PINS(34);
DECLARE_MSM_GPIO_PINS(35);
DECLARE_MSM_GPIO_PINS(36);
DECLARE_MSM_GPIO_PINS(37);
DECLARE_MSM_GPIO_PINS(38);
DECLARE_MSM_GPIO_PINS(39);
DECLARE_MSM_GPIO_PINS(40);
DECLARE_MSM_GPIO_PINS(41);
DECLARE_MSM_GPIO_PINS(42);
DECLARE_MSM_GPIO_PINS(43);
DECLARE_MSM_GPIO_PINS(44);
DECLARE_MSM_GPIO_PINS(45);
DECLARE_MSM_GPIO_PINS(46);
DECLARE_MSM_GPIO_PINS(47);
DECLARE_MSM_GPIO_PINS(48);
DECLARE_MSM_GPIO_PINS(49);
DECLARE_MSM_GPIO_PINS(50);
DECLARE_MSM_GPIO_PINS(51);
DECLARE_MSM_GPIO_PINS(52);
DECLARE_MSM_GPIO_PINS(53);
DECLARE_MSM_GPIO_PINS(54);
DECLARE_MSM_GPIO_PINS(55);
DECLARE_MSM_GPIO_PINS(56);
DECLARE_MSM_GPIO_PINS(57);
DECLARE_MSM_GPIO_PINS(58);
DECLARE_MSM_GPIO_PINS(59);
DECLARE_MSM_GPIO_PINS(60);
DECLARE_MSM_GPIO_PINS(61);
DECLARE_MSM_GPIO_PINS(62);
DECLARE_MSM_GPIO_PINS(63);
DECLARE_MSM_GPIO_PINS(64);
DECLARE_MSM_GPIO_PINS(65);
DECLARE_MSM_GPIO_PINS(66);
DECLARE_MSM_GPIO_PINS(67);
DECLARE_MSM_GPIO_PINS(68);
DECLARE_MSM_GPIO_PINS(69);
DECLARE_MSM_GPIO_PINS(70);
DECLARE_MSM_GPIO_PINS(71);
DECLARE_MSM_GPIO_PINS(72);
DECLARE_MSM_GPIO_PINS(73);
DECLARE_MSM_GPIO_PINS(74);
DECLARE_MSM_GPIO_PINS(75);
DECLARE_MSM_GPIO_PINS(76);
DECLARE_MSM_GPIO_PINS(77);
DECLARE_MSM_GPIO_PINS(78);
DECLARE_MSM_GPIO_PINS(79);
DECLARE_MSM_GPIO_PINS(80);
DECLARE_MSM_GPIO_PINS(81);
DECLARE_MSM_GPIO_PINS(82);
DECLARE_MSM_GPIO_PINS(83);
DECLARE_MSM_GPIO_PINS(84);
DECLARE_MSM_GPIO_PINS(85);
DECLARE_MSM_GPIO_PINS(86);
DECLARE_MSM_GPIO_PINS(87);

#घोषणा FUNCTION(fname)					\
	[MSM_MUX_##fname] = अणु				\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

#घोषणा PINGROUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11) \
	अणु						\
		.name = "gpio" #id,			\
		.pins = gpio##id##_pins,		\
		.npins = ARRAY_SIZE(gpio##id##_pins),	\
		.funcs = (पूर्णांक[])अणु			\
			MSM_MUX_gpio,			\
			MSM_MUX_##f1,			\
			MSM_MUX_##f2,			\
			MSM_MUX_##f3,			\
			MSM_MUX_##f4,			\
			MSM_MUX_##f5,			\
			MSM_MUX_##f6,			\
			MSM_MUX_##f7,			\
			MSM_MUX_##f8,			\
			MSM_MUX_##f9,			\
			MSM_MUX_##f10,			\
			MSM_MUX_##f11			\
		पूर्ण,					\
		.nfuncs = 12,				\
		.ctl_reg = 0x1000 + 0x10 * id,		\
		.io_reg = 0x1004 + 0x10 * id,		\
		.पूर्णांकr_cfg_reg = 0x1008 + 0x10 * id,	\
		.पूर्णांकr_status_reg = 0x100c + 0x10 * id,	\
		.पूर्णांकr_target_reg = 0x400 + 0x4 * id,	\
		.mux_bit = 2,				\
		.pull_bit = 0,				\
		.drv_bit = 6,				\
		.oe_bit = 9,				\
		.in_bit = 0,				\
		.out_bit = 1,				\
		.पूर्णांकr_enable_bit = 0,			\
		.पूर्णांकr_status_bit = 0,			\
		.पूर्णांकr_ack_high = 1,			\
		.पूर्णांकr_target_bit = 0,			\
		.पूर्णांकr_target_kpss_val = 4,		\
		.पूर्णांकr_raw_status_bit = 3,		\
		.पूर्णांकr_polarity_bit = 1,			\
		.पूर्णांकr_detection_bit = 2,		\
		.पूर्णांकr_detection_width = 1,		\
	पूर्ण

क्रमागत mdm9615_functions अणु
	MSM_MUX_gpio,
	MSM_MUX_gsbi2_i2c,
	MSM_MUX_gsbi3,
	MSM_MUX_gsbi4,
	MSM_MUX_gsbi5_i2c,
	MSM_MUX_gsbi5_uart,
	MSM_MUX_sdc2,
	MSM_MUX_ebi2_lcdc,
	MSM_MUX_ps_hold,
	MSM_MUX_prim_audio,
	MSM_MUX_sec_audio,
	MSM_MUX_cdc_mclk,
	MSM_MUX_NA,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio4", "gpio5", "gpio6", "gpio7",
	"gpio8", "gpio9", "gpio10", "gpio11", "gpio12", "gpio13", "gpio14",
	"gpio15", "gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21",
	"gpio22", "gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28",
	"gpio29", "gpio30", "gpio31", "gpio32", "gpio33", "gpio34", "gpio35",
	"gpio36", "gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42",
	"gpio43", "gpio44", "gpio45", "gpio46", "gpio47", "gpio48", "gpio49",
	"gpio50", "gpio51", "gpio52", "gpio53", "gpio54", "gpio55", "gpio56",
	"gpio57", "gpio58", "gpio59", "gpio60", "gpio61", "gpio62", "gpio63",
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio68", "gpio69", "gpio70",
	"gpio71", "gpio72", "gpio73", "gpio74", "gpio75", "gpio76", "gpio77",
	"gpio78", "gpio79", "gpio80", "gpio81", "gpio82", "gpio83", "gpio84",
	"gpio85", "gpio86", "gpio87"
पूर्ण;

अटल स्थिर अक्षर * स्थिर gsbi2_i2c_groups[] = अणु
	"gpio4", "gpio5"
पूर्ण;

अटल स्थिर अक्षर * स्थिर gsbi3_groups[] = अणु
	"gpio8", "gpio9", "gpio10", "gpio11"
पूर्ण;

अटल स्थिर अक्षर * स्थिर gsbi4_groups[] = अणु
	"gpio12", "gpio13", "gpio14", "gpio15"
पूर्ण;

अटल स्थिर अक्षर * स्थिर gsbi5_i2c_groups[] = अणु
	"gpio16", "gpio17"
पूर्ण;

अटल स्थिर अक्षर * स्थिर gsbi5_uart_groups[] = अणु
	"gpio18", "gpio19"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdc2_groups[] = अणु
	"gpio25", "gpio26", "gpio27", "gpio28", "gpio29", "gpio30",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ebi2_lcdc_groups[] = अणु
	"gpio21", "gpio22", "gpio24",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ps_hold_groups[] = अणु
	"gpio83",
पूर्ण;

अटल स्थिर अक्षर * स्थिर prim_audio_groups[] = अणु
	"gpio20", "gpio21", "gpio22", "gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sec_audio_groups[] = अणु
	"gpio25", "gpio26", "gpio27", "gpio28",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_mclk_groups[] = अणु
	"gpio24",
पूर्ण;

अटल स्थिर काष्ठा msm_function mdm9615_functions[] = अणु
	FUNCTION(gpio),
	FUNCTION(gsbi2_i2c),
	FUNCTION(gsbi3),
	FUNCTION(gsbi4),
	FUNCTION(gsbi5_i2c),
	FUNCTION(gsbi5_uart),
	FUNCTION(sdc2),
	FUNCTION(ebi2_lcdc),
	FUNCTION(ps_hold),
	FUNCTION(prim_audio),
	FUNCTION(sec_audio),
	FUNCTION(cdc_mclk),
पूर्ण;

अटल स्थिर काष्ठा msm_pingroup mdm9615_groups[] = अणु
	PINGROUP(0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(1, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(2, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(4, gsbi2_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(5, gsbi2_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(6, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(7, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(8, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(9, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(10, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(11, gsbi3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(12, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(13, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(14, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(15, gsbi4, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(16, gsbi5_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(17, gsbi5_i2c, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(18, gsbi5_uart, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(19, gsbi5_uart, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(20, prim_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(21, prim_audio, ebi2_lcdc, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(22, prim_audio, ebi2_lcdc, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(23, prim_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(24, cdc_mclk, NA, ebi2_lcdc, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(25, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(26, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(27, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(28, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(29, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(30, sdc2, sec_audio, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(31, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(32, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(33, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(34, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(35, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(36, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(37, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(38, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(39, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(40, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(41, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(42, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(43, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(44, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(45, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(46, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(47, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(48, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(49, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(50, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(51, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(52, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(53, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(54, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(55, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(56, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(57, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(58, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(59, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(60, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(61, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(62, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(63, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(64, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(65, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(66, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(67, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(68, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(69, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(70, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(71, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(72, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(73, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(74, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(75, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(76, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(77, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(78, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(79, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(80, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(81, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(82, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(83, ps_hold, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(84, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(85, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(86, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(87, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA),
पूर्ण;

#घोषणा NUM_GPIO_PINGROUPS 88

अटल स्थिर काष्ठा msm_pinctrl_soc_data mdm9615_pinctrl = अणु
	.pins = mdm9615_pins,
	.npins = ARRAY_SIZE(mdm9615_pins),
	.functions = mdm9615_functions,
	.nfunctions = ARRAY_SIZE(mdm9615_functions),
	.groups = mdm9615_groups,
	.ngroups = ARRAY_SIZE(mdm9615_groups),
	.ngpios = NUM_GPIO_PINGROUPS,
पूर्ण;

अटल पूर्णांक mdm9615_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस msm_pinctrl_probe(pdev, &mdm9615_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id mdm9615_pinctrl_of_match[] = अणु
	अणु .compatible = "qcom,mdm9615-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mdm9615_pinctrl_driver = अणु
	.driver = अणु
		.name = "mdm9615-pinctrl",
		.of_match_table = mdm9615_pinctrl_of_match,
	पूर्ण,
	.probe = mdm9615_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init mdm9615_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mdm9615_pinctrl_driver);
पूर्ण
arch_initcall(mdm9615_pinctrl_init);

अटल व्योम __निकास mdm9615_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mdm9615_pinctrl_driver);
पूर्ण
module_निकास(mdm9615_pinctrl_निकास);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Qualcomm MDM9615 pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, mdm9615_pinctrl_of_match);
