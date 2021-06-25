<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-msm.h"

#घोषणा FUNCTION(fname)			                \
	[msm_mux_##fname] = अणु		                \
		.name = #fname,				\
		.groups = fname##_groups,               \
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

#घोषणा REG_BASE 0x0
#घोषणा REG_SIZE 0x1000
#घोषणा PINGROUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	अणु					        \
		.name = "gpio" #id,			\
		.pins = gpio##id##_pins,		\
		.npins = (अचिन्हित)ARRAY_SIZE(gpio##id##_pins),	\
		.funcs = (पूर्णांक[])अणु			\
			msm_mux_gpio, /* gpio mode */	\
			msm_mux_##f1,			\
			msm_mux_##f2,			\
			msm_mux_##f3,			\
			msm_mux_##f4,			\
			msm_mux_##f5,			\
			msm_mux_##f6,			\
			msm_mux_##f7,			\
			msm_mux_##f8,			\
			msm_mux_##f9			\
		पूर्ण,				        \
		.nfuncs = 10,				\
		.ctl_reg = REG_BASE + REG_SIZE * id,	\
		.io_reg = REG_BASE + 0x4 + REG_SIZE * id,		\
		.पूर्णांकr_cfg_reg = REG_BASE + 0x8 + REG_SIZE * id,		\
		.पूर्णांकr_status_reg = REG_BASE + 0xc + REG_SIZE * id,	\
		.पूर्णांकr_target_reg = REG_BASE + 0x8 + REG_SIZE * id,	\
		.mux_bit = 2,			\
		.pull_bit = 0,			\
		.drv_bit = 6,			\
		.oe_bit = 9,			\
		.in_bit = 0,			\
		.out_bit = 1,			\
		.पूर्णांकr_enable_bit = 0,		\
		.पूर्णांकr_status_bit = 0,		\
		.पूर्णांकr_target_bit = 5,		\
		.पूर्णांकr_target_kpss_val = 3,	\
		.पूर्णांकr_raw_status_bit = 4,	\
		.पूर्णांकr_polarity_bit = 1,		\
		.पूर्णांकr_detection_bit = 2,	\
		.पूर्णांकr_detection_width = 2,	\
	पूर्ण

#घोषणा SDC_QDSD_PINGROUP(pg_name, ctl, pull, drv)	\
	अणु					        \
		.name = #pg_name,			\
		.pins = pg_name##_pins,			\
		.npins = (अचिन्हित)ARRAY_SIZE(pg_name##_pins),	\
		.ctl_reg = ctl,				\
		.io_reg = 0,				\
		.पूर्णांकr_cfg_reg = 0,			\
		.पूर्णांकr_status_reg = 0,			\
		.पूर्णांकr_target_reg = 0,			\
		.mux_bit = -1,				\
		.pull_bit = pull,			\
		.drv_bit = drv,				\
		.oe_bit = -1,				\
		.in_bit = -1,				\
		.out_bit = -1,				\
		.पूर्णांकr_enable_bit = -1,			\
		.पूर्णांकr_status_bit = -1,			\
		.पूर्णांकr_target_bit = -1,			\
		.पूर्णांकr_raw_status_bit = -1,		\
		.पूर्णांकr_polarity_bit = -1,		\
		.पूर्णांकr_detection_bit = -1,		\
		.पूर्णांकr_detection_width = -1,		\
	पूर्ण
अटल स्थिर काष्ठा pinctrl_pin_desc msm8996_pins[] = अणु
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
	PINCTRL_PIN(88, "GPIO_88"),
	PINCTRL_PIN(89, "GPIO_89"),
	PINCTRL_PIN(90, "GPIO_90"),
	PINCTRL_PIN(91, "GPIO_91"),
	PINCTRL_PIN(92, "GPIO_92"),
	PINCTRL_PIN(93, "GPIO_93"),
	PINCTRL_PIN(94, "GPIO_94"),
	PINCTRL_PIN(95, "GPIO_95"),
	PINCTRL_PIN(96, "GPIO_96"),
	PINCTRL_PIN(97, "GPIO_97"),
	PINCTRL_PIN(98, "GPIO_98"),
	PINCTRL_PIN(99, "GPIO_99"),
	PINCTRL_PIN(100, "GPIO_100"),
	PINCTRL_PIN(101, "GPIO_101"),
	PINCTRL_PIN(102, "GPIO_102"),
	PINCTRL_PIN(103, "GPIO_103"),
	PINCTRL_PIN(104, "GPIO_104"),
	PINCTRL_PIN(105, "GPIO_105"),
	PINCTRL_PIN(106, "GPIO_106"),
	PINCTRL_PIN(107, "GPIO_107"),
	PINCTRL_PIN(108, "GPIO_108"),
	PINCTRL_PIN(109, "GPIO_109"),
	PINCTRL_PIN(110, "GPIO_110"),
	PINCTRL_PIN(111, "GPIO_111"),
	PINCTRL_PIN(112, "GPIO_112"),
	PINCTRL_PIN(113, "GPIO_113"),
	PINCTRL_PIN(114, "GPIO_114"),
	PINCTRL_PIN(115, "GPIO_115"),
	PINCTRL_PIN(116, "GPIO_116"),
	PINCTRL_PIN(117, "GPIO_117"),
	PINCTRL_PIN(118, "GPIO_118"),
	PINCTRL_PIN(119, "GPIO_119"),
	PINCTRL_PIN(120, "GPIO_120"),
	PINCTRL_PIN(121, "GPIO_121"),
	PINCTRL_PIN(122, "GPIO_122"),
	PINCTRL_PIN(123, "GPIO_123"),
	PINCTRL_PIN(124, "GPIO_124"),
	PINCTRL_PIN(125, "GPIO_125"),
	PINCTRL_PIN(126, "GPIO_126"),
	PINCTRL_PIN(127, "GPIO_127"),
	PINCTRL_PIN(128, "GPIO_128"),
	PINCTRL_PIN(129, "GPIO_129"),
	PINCTRL_PIN(130, "GPIO_130"),
	PINCTRL_PIN(131, "GPIO_131"),
	PINCTRL_PIN(132, "GPIO_132"),
	PINCTRL_PIN(133, "GPIO_133"),
	PINCTRL_PIN(134, "GPIO_134"),
	PINCTRL_PIN(135, "GPIO_135"),
	PINCTRL_PIN(136, "GPIO_136"),
	PINCTRL_PIN(137, "GPIO_137"),
	PINCTRL_PIN(138, "GPIO_138"),
	PINCTRL_PIN(139, "GPIO_139"),
	PINCTRL_PIN(140, "GPIO_140"),
	PINCTRL_PIN(141, "GPIO_141"),
	PINCTRL_PIN(142, "GPIO_142"),
	PINCTRL_PIN(143, "GPIO_143"),
	PINCTRL_PIN(144, "GPIO_144"),
	PINCTRL_PIN(145, "GPIO_145"),
	PINCTRL_PIN(146, "GPIO_146"),
	PINCTRL_PIN(147, "GPIO_147"),
	PINCTRL_PIN(148, "GPIO_148"),
	PINCTRL_PIN(149, "GPIO_149"),
	PINCTRL_PIN(150, "SDC1_CLK"),
	PINCTRL_PIN(151, "SDC1_CMD"),
	PINCTRL_PIN(152, "SDC1_DATA"),
	PINCTRL_PIN(153, "SDC2_CLK"),
	PINCTRL_PIN(154, "SDC2_CMD"),
	PINCTRL_PIN(155, "SDC2_DATA"),
	PINCTRL_PIN(156, "SDC1_RCLK"),
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
DECLARE_MSM_GPIO_PINS(88);
DECLARE_MSM_GPIO_PINS(89);
DECLARE_MSM_GPIO_PINS(90);
DECLARE_MSM_GPIO_PINS(91);
DECLARE_MSM_GPIO_PINS(92);
DECLARE_MSM_GPIO_PINS(93);
DECLARE_MSM_GPIO_PINS(94);
DECLARE_MSM_GPIO_PINS(95);
DECLARE_MSM_GPIO_PINS(96);
DECLARE_MSM_GPIO_PINS(97);
DECLARE_MSM_GPIO_PINS(98);
DECLARE_MSM_GPIO_PINS(99);
DECLARE_MSM_GPIO_PINS(100);
DECLARE_MSM_GPIO_PINS(101);
DECLARE_MSM_GPIO_PINS(102);
DECLARE_MSM_GPIO_PINS(103);
DECLARE_MSM_GPIO_PINS(104);
DECLARE_MSM_GPIO_PINS(105);
DECLARE_MSM_GPIO_PINS(106);
DECLARE_MSM_GPIO_PINS(107);
DECLARE_MSM_GPIO_PINS(108);
DECLARE_MSM_GPIO_PINS(109);
DECLARE_MSM_GPIO_PINS(110);
DECLARE_MSM_GPIO_PINS(111);
DECLARE_MSM_GPIO_PINS(112);
DECLARE_MSM_GPIO_PINS(113);
DECLARE_MSM_GPIO_PINS(114);
DECLARE_MSM_GPIO_PINS(115);
DECLARE_MSM_GPIO_PINS(116);
DECLARE_MSM_GPIO_PINS(117);
DECLARE_MSM_GPIO_PINS(118);
DECLARE_MSM_GPIO_PINS(119);
DECLARE_MSM_GPIO_PINS(120);
DECLARE_MSM_GPIO_PINS(121);
DECLARE_MSM_GPIO_PINS(122);
DECLARE_MSM_GPIO_PINS(123);
DECLARE_MSM_GPIO_PINS(124);
DECLARE_MSM_GPIO_PINS(125);
DECLARE_MSM_GPIO_PINS(126);
DECLARE_MSM_GPIO_PINS(127);
DECLARE_MSM_GPIO_PINS(128);
DECLARE_MSM_GPIO_PINS(129);
DECLARE_MSM_GPIO_PINS(130);
DECLARE_MSM_GPIO_PINS(131);
DECLARE_MSM_GPIO_PINS(132);
DECLARE_MSM_GPIO_PINS(133);
DECLARE_MSM_GPIO_PINS(134);
DECLARE_MSM_GPIO_PINS(135);
DECLARE_MSM_GPIO_PINS(136);
DECLARE_MSM_GPIO_PINS(137);
DECLARE_MSM_GPIO_PINS(138);
DECLARE_MSM_GPIO_PINS(139);
DECLARE_MSM_GPIO_PINS(140);
DECLARE_MSM_GPIO_PINS(141);
DECLARE_MSM_GPIO_PINS(142);
DECLARE_MSM_GPIO_PINS(143);
DECLARE_MSM_GPIO_PINS(144);
DECLARE_MSM_GPIO_PINS(145);
DECLARE_MSM_GPIO_PINS(146);
DECLARE_MSM_GPIO_PINS(147);
DECLARE_MSM_GPIO_PINS(148);
DECLARE_MSM_GPIO_PINS(149);

अटल स्थिर अचिन्हित पूर्णांक sdc1_clk_pins[] = अणु 150 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_cmd_pins[] = अणु 151 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_data_pins[] = अणु 152 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_clk_pins[] = अणु 153 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_cmd_pins[] = अणु 154 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_data_pins[] = अणु 155 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_rclk_pins[] = अणु 156 पूर्ण;

क्रमागत msm8996_functions अणु
	msm_mux_adsp_ext,
	msm_mux_atest_bbrx0,
	msm_mux_atest_bbrx1,
	msm_mux_atest_अक्षर,
	msm_mux_atest_अक्षर0,
	msm_mux_atest_अक्षर1,
	msm_mux_atest_अक्षर2,
	msm_mux_atest_अक्षर3,
	msm_mux_atest_gpsadc0,
	msm_mux_atest_gpsadc1,
	msm_mux_atest_tsens,
	msm_mux_atest_tsens2,
	msm_mux_atest_usb1,
	msm_mux_atest_usb10,
	msm_mux_atest_usb11,
	msm_mux_atest_usb12,
	msm_mux_atest_usb13,
	msm_mux_atest_usb2,
	msm_mux_atest_usb20,
	msm_mux_atest_usb21,
	msm_mux_atest_usb22,
	msm_mux_atest_usb23,
	msm_mux_audio_ref,
	msm_mux_bimc_dte0,
	msm_mux_bimc_dte1,
	msm_mux_blsp10_spi,
	msm_mux_blsp11_i2c_scl_b,
	msm_mux_blsp11_i2c_sda_b,
	msm_mux_blsp11_uart_rx_b,
	msm_mux_blsp11_uart_tx_b,
	msm_mux_blsp1_spi,
	msm_mux_blsp2_spi,
	msm_mux_blsp_i2c1,
	msm_mux_blsp_i2c10,
	msm_mux_blsp_i2c11,
	msm_mux_blsp_i2c12,
	msm_mux_blsp_i2c2,
	msm_mux_blsp_i2c3,
	msm_mux_blsp_i2c4,
	msm_mux_blsp_i2c5,
	msm_mux_blsp_i2c6,
	msm_mux_blsp_i2c7,
	msm_mux_blsp_i2c8,
	msm_mux_blsp_i2c9,
	msm_mux_blsp_spi1,
	msm_mux_blsp_spi10,
	msm_mux_blsp_spi11,
	msm_mux_blsp_spi12,
	msm_mux_blsp_spi2,
	msm_mux_blsp_spi3,
	msm_mux_blsp_spi4,
	msm_mux_blsp_spi5,
	msm_mux_blsp_spi6,
	msm_mux_blsp_spi7,
	msm_mux_blsp_spi8,
	msm_mux_blsp_spi9,
	msm_mux_blsp_uart1,
	msm_mux_blsp_uart10,
	msm_mux_blsp_uart11,
	msm_mux_blsp_uart12,
	msm_mux_blsp_uart2,
	msm_mux_blsp_uart3,
	msm_mux_blsp_uart4,
	msm_mux_blsp_uart5,
	msm_mux_blsp_uart6,
	msm_mux_blsp_uart7,
	msm_mux_blsp_uart8,
	msm_mux_blsp_uart9,
	msm_mux_blsp_uim1,
	msm_mux_blsp_uim10,
	msm_mux_blsp_uim11,
	msm_mux_blsp_uim12,
	msm_mux_blsp_uim2,
	msm_mux_blsp_uim3,
	msm_mux_blsp_uim4,
	msm_mux_blsp_uim5,
	msm_mux_blsp_uim6,
	msm_mux_blsp_uim7,
	msm_mux_blsp_uim8,
	msm_mux_blsp_uim9,
	msm_mux_btfm_slimbus,
	msm_mux_cam_mclk,
	msm_mux_cci_async,
	msm_mux_cci_i2c,
	msm_mux_cci_समयr0,
	msm_mux_cci_समयr1,
	msm_mux_cci_समयr2,
	msm_mux_cci_समयr3,
	msm_mux_cci_समयr4,
	msm_mux_cri_trng,
	msm_mux_cri_trng0,
	msm_mux_cri_trng1,
	msm_mux_dac_calib0,
	msm_mux_dac_calib1,
	msm_mux_dac_calib10,
	msm_mux_dac_calib11,
	msm_mux_dac_calib12,
	msm_mux_dac_calib13,
	msm_mux_dac_calib14,
	msm_mux_dac_calib15,
	msm_mux_dac_calib16,
	msm_mux_dac_calib17,
	msm_mux_dac_calib18,
	msm_mux_dac_calib19,
	msm_mux_dac_calib2,
	msm_mux_dac_calib20,
	msm_mux_dac_calib21,
	msm_mux_dac_calib22,
	msm_mux_dac_calib23,
	msm_mux_dac_calib24,
	msm_mux_dac_calib25,
	msm_mux_dac_calib26,
	msm_mux_dac_calib3,
	msm_mux_dac_calib4,
	msm_mux_dac_calib5,
	msm_mux_dac_calib6,
	msm_mux_dac_calib7,
	msm_mux_dac_calib8,
	msm_mux_dac_calib9,
	msm_mux_dac_gpio,
	msm_mux_dbg_out,
	msm_mux_ddr_bist,
	msm_mux_edp_hot,
	msm_mux_edp_lcd,
	msm_mux_gcc_gp1_clk_a,
	msm_mux_gcc_gp1_clk_b,
	msm_mux_gcc_gp2_clk_a,
	msm_mux_gcc_gp2_clk_b,
	msm_mux_gcc_gp3_clk_a,
	msm_mux_gcc_gp3_clk_b,
	msm_mux_gsm_tx,
	msm_mux_hdmi_cec,
	msm_mux_hdmi_ddc,
	msm_mux_hdmi_hot,
	msm_mux_hdmi_rcv,
	msm_mux_isense_dbg,
	msm_mux_lकरो_en,
	msm_mux_lकरो_update,
	msm_mux_lpass_slimbus,
	msm_mux_m_voc,
	msm_mux_mdp_vsync,
	msm_mux_mdp_vsync_p_b,
	msm_mux_mdp_vsync_s_b,
	msm_mux_modem_tsync,
	msm_mux_mss_lte,
	msm_mux_nav_dr,
	msm_mux_nav_pps,
	msm_mux_pa_indicator,
	msm_mux_pci_e0,
	msm_mux_pci_e1,
	msm_mux_pci_e2,
	msm_mux_pll_bypassnl,
	msm_mux_pll_reset,
	msm_mux_pri_mi2s,
	msm_mux_prng_rosc,
	msm_mux_pwr_crypto,
	msm_mux_pwr_modem,
	msm_mux_pwr_nav,
	msm_mux_qdss_cti,
	msm_mux_qdss_cti_trig_in_a,
	msm_mux_qdss_cti_trig_in_b,
	msm_mux_qdss_cti_trig_out_a,
	msm_mux_qdss_cti_trig_out_b,
	msm_mux_qdss_sपंचांग0,
	msm_mux_qdss_sपंचांग1,
	msm_mux_qdss_sपंचांग10,
	msm_mux_qdss_sपंचांग11,
	msm_mux_qdss_sपंचांग12,
	msm_mux_qdss_sपंचांग13,
	msm_mux_qdss_sपंचांग14,
	msm_mux_qdss_sपंचांग15,
	msm_mux_qdss_sपंचांग16,
	msm_mux_qdss_sपंचांग17,
	msm_mux_qdss_sपंचांग18,
	msm_mux_qdss_sपंचांग19,
	msm_mux_qdss_sपंचांग2,
	msm_mux_qdss_sपंचांग20,
	msm_mux_qdss_sपंचांग21,
	msm_mux_qdss_sपंचांग22,
	msm_mux_qdss_sपंचांग23,
	msm_mux_qdss_sपंचांग24,
	msm_mux_qdss_sपंचांग25,
	msm_mux_qdss_sपंचांग26,
	msm_mux_qdss_sपंचांग27,
	msm_mux_qdss_sपंचांग28,
	msm_mux_qdss_sपंचांग29,
	msm_mux_qdss_sपंचांग3,
	msm_mux_qdss_sपंचांग30,
	msm_mux_qdss_sपंचांग31,
	msm_mux_qdss_sपंचांग4,
	msm_mux_qdss_sपंचांग5,
	msm_mux_qdss_sपंचांग6,
	msm_mux_qdss_sपंचांग7,
	msm_mux_qdss_sपंचांग8,
	msm_mux_qdss_sपंचांग9,
	msm_mux_qdss_traceclk_a,
	msm_mux_qdss_traceclk_b,
	msm_mux_qdss_tracectl_a,
	msm_mux_qdss_tracectl_b,
	msm_mux_qdss_tracedata_11,
	msm_mux_qdss_tracedata_12,
	msm_mux_qdss_tracedata_a,
	msm_mux_qdss_tracedata_b,
	msm_mux_qspi0,
	msm_mux_qspi1,
	msm_mux_qspi2,
	msm_mux_qspi3,
	msm_mux_qspi_clk,
	msm_mux_qspi_cs,
	msm_mux_qua_mi2s,
	msm_mux_sd_card,
	msm_mux_sd_ग_लिखो,
	msm_mux_sdc40,
	msm_mux_sdc41,
	msm_mux_sdc42,
	msm_mux_sdc43,
	msm_mux_sdc4_clk,
	msm_mux_sdc4_cmd,
	msm_mux_sec_mi2s,
	msm_mux_spkr_i2s,
	msm_mux_ssbi1,
	msm_mux_ssbi2,
	msm_mux_ssc_irq,
	msm_mux_ter_mi2s,
	msm_mux_tsense_pwm1,
	msm_mux_tsense_pwm2,
	msm_mux_tsअगर1_clk,
	msm_mux_tsअगर1_data,
	msm_mux_tsअगर1_en,
	msm_mux_tsअगर1_error,
	msm_mux_tsअगर1_sync,
	msm_mux_tsअगर2_clk,
	msm_mux_tsअगर2_data,
	msm_mux_tsअगर2_en,
	msm_mux_tsअगर2_error,
	msm_mux_tsअगर2_sync,
	msm_mux_uim1,
	msm_mux_uim2,
	msm_mux_uim3,
	msm_mux_uim4,
	msm_mux_uim_batt,
	msm_mux_vfr_1,
	msm_mux_gpio,
	msm_mux_NA,
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
	"gpio85", "gpio86", "gpio87", "gpio88", "gpio89", "gpio90", "gpio91",
	"gpio92", "gpio93", "gpio94", "gpio95", "gpio96", "gpio97", "gpio98",
	"gpio99", "gpio100", "gpio101", "gpio102", "gpio103", "gpio104",
	"gpio105", "gpio106", "gpio107", "gpio108", "gpio109", "gpio110",
	"gpio111", "gpio112", "gpio113", "gpio114", "gpio115", "gpio116",
	"gpio117", "gpio118", "gpio119", "gpio120", "gpio121", "gpio122",
	"gpio123", "gpio124", "gpio125", "gpio126", "gpio127", "gpio128",
	"gpio129", "gpio130", "gpio131", "gpio132", "gpio133", "gpio134",
	"gpio135", "gpio136", "gpio137", "gpio138", "gpio139", "gpio140",
	"gpio141", "gpio142", "gpio143", "gpio144", "gpio145", "gpio146",
	"gpio147", "gpio148", "gpio149"
पूर्ण;


अटल स्थिर अक्षर * स्थिर blsp_uart1_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi1_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c1_groups[] = अणु
	"gpio2", "gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim1_groups[] = अणु
	"gpio0", "gpio1",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens_groups[] = अणु
	"gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर bimc_dte1_groups[] = अणु
	"gpio3", "gpio5",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi8_groups[] = अणु
	"gpio4", "gpio5", "gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart8_groups[] = अणु
	"gpio4", "gpio5", "gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim8_groups[] = अणु
	"gpio4", "gpio5",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_b_groups[] = अणु
	"gpio4",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib0_groups[] = अणु
	"gpio4", "gpio41",
पूर्ण;
अटल स्थिर अक्षर * स्थिर bimc_dte0_groups[] = अणु
	"gpio4", "gpio6",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_b_groups[] = अणु
	"gpio5",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib1_groups[] = अणु
	"gpio5", "gpio42",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib2_groups[] = अणु
	"gpio6", "gpio43",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens2_groups[] = अणु
	"gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi10_groups[] = अणु
	"gpio8", "gpio9", "gpio10", "gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart10_groups[] = अणु
	"gpio8", "gpio9", "gpio10", "gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim10_groups[] = अणु
	"gpio8", "gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_bbrx1_groups[] = अणु
	"gpio8",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb12_groups[] = अणु
	"gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync_groups[] = अणु
	"gpio10", "gpio11", "gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर edp_lcd_groups[] = अणु
	"gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c10_groups[] = अणु
	"gpio10", "gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb11_groups[] = अणु
	"gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_gpsadc0_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर edp_hot_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb10_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर m_voc_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_gpio_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cam_mclk_groups[] = अणु
	"gpio13", "gpio14", "gpio15", "gpio16",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_bypassnl_groups[] = अणु
	"gpio13",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग7_groups[] = अणु
	"gpio13",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c8_groups[] = अणु
	"gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb1_groups[] = अणु
	"gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb13_groups[] = अणु
	"gpio8",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_bbrx0_groups[] = अणु
	"gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_gpsadc1_groups[] = अणु
	"gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_tracedata_b_groups[] = अणु
	"gpio13", "gpio14", "gpio15", "gpio16", "gpio17", "gpio18", "gpio19",
	"gpio21", "gpio22", "gpio23", "gpio26", "gpio29", "gpio57", "gpio58",
	"gpio92", "gpio93",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_reset_groups[] = अणु
	"gpio14",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग6_groups[] = अणु
	"gpio14",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग5_groups[] = अणु
	"gpio15",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग4_groups[] = अणु
	"gpio16",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb2_groups[] = अणु
	"gpio16",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib3_groups[] = अणु
	"gpio17", "gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_i2c_groups[] = अणु
	"gpio17", "gpio18", "gpio19", "gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग3_groups[] = अणु
	"gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb23_groups[] = अणु
	"gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर3_groups[] = अणु
	"gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib4_groups[] = अणु
	"gpio18", "gpio45",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग2_groups[] = अणु
	"gpio18",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb22_groups[] = अणु
	"gpio18",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर2_groups[] = अणु
	"gpio18",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib5_groups[] = अणु
	"gpio19", "gpio46",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग1_groups[] = अणु
	"gpio19",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb21_groups[] = अणु
	"gpio19",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर1_groups[] = अणु
	"gpio19",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib6_groups[] = अणु
	"gpio20", "gpio47",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dbg_out_groups[] = अणु
	"gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग0_groups[] = अणु
	"gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb20_groups[] = अणु
	"gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर0_groups[] = अणु
	"gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib7_groups[] = अणु
	"gpio21", "gpio48",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr0_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग13_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib8_groups[] = अणु
	"gpio22", "gpio49",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr1_groups[] = अणु
	"gpio22",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग12_groups[] = अणु
	"gpio22",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib9_groups[] = अणु
	"gpio23", "gpio50",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr2_groups[] = अणु
	"gpio23",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग11_groups[] = अणु
	"gpio23",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib10_groups[] = अणु
	"gpio24", "gpio51",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr3_groups[] = अणु
	"gpio24",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_async_groups[] = अणु
	"gpio24", "gpio25", "gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp1_spi_groups[] = अणु
	"gpio24", "gpio27", "gpio28", "gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग10_groups[] = अणु
	"gpio24",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_a_groups[] = अणु
	"gpio24",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib11_groups[] = अणु
	"gpio25", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr4_groups[] = अणु
	"gpio25",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi6_groups[] = अणु
	"gpio25", "gpio26", "gpio27", "gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart6_groups[] = अणु
	"gpio25", "gpio26", "gpio27", "gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim6_groups[] = अणु
	"gpio25", "gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp2_spi_groups[] = अणु
	"gpio25", "gpio29", "gpio30",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग9_groups[] = अणु
	"gpio25",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_a_groups[] = अणु
	"gpio25",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib12_groups[] = अणु
	"gpio26", "gpio53",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग8_groups[] = अणु
	"gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib13_groups[] = अणु
	"gpio27", "gpio54",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c6_groups[] = अणु
	"gpio27", "gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_tracectl_a_groups[] = अणु
	"gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib14_groups[] = अणु
	"gpio28", "gpio55",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_traceclk_a_groups[] = अणु
	"gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib15_groups[] = अणु
	"gpio29", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib16_groups[] = अणु
	"gpio30", "gpio57",
पूर्ण;
अटल स्थिर अक्षर * स्थिर hdmi_rcv_groups[] = अणु
	"gpio30",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib17_groups[] = अणु
	"gpio31", "gpio58",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pwr_modem_groups[] = अणु
	"gpio31",
पूर्ण;
अटल स्थिर अक्षर * स्थिर hdmi_cec_groups[] = अणु
	"gpio31",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pwr_nav_groups[] = अणु
	"gpio32",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib18_groups[] = अणु
	"gpio32", "gpio59",
पूर्ण;
अटल स्थिर अक्षर * स्थिर hdmi_ddc_groups[] = अणु
	"gpio32", "gpio33",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pwr_crypto_groups[] = अणु
	"gpio33",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib19_groups[] = अणु
	"gpio33", "gpio60",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib20_groups[] = अणु
	"gpio34", "gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर hdmi_hot_groups[] = अणु
	"gpio34",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib21_groups[] = अणु
	"gpio35", "gpio62",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pci_e0_groups[] = अणु
	"gpio35", "gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib22_groups[] = अणु
	"gpio36", "gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib23_groups[] = अणु
	"gpio37", "gpio64",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c2_groups[] = अणु
	"gpio43", "gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi3_groups[] = अणु
	"gpio45", "gpio46", "gpio47", "gpio48",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart3_groups[] = अणु
	"gpio45", "gpio46", "gpio47", "gpio48",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim3_groups[] = अणु
	"gpio45", "gpio46",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c3_groups[] = अणु
	"gpio47", "gpio48",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib24_groups[] = अणु
	"gpio38", "gpio65",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib25_groups[] = अणु
	"gpio39", "gpio66",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_sync_groups[] = अणु
	"gpio39",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sd_ग_लिखो_groups[] = अणु
	"gpio40",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_error_groups[] = अणु
	"gpio40",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi2_groups[] = अणु
	"gpio41", "gpio42", "gpio43", "gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart2_groups[] = अणु
	"gpio41", "gpio42", "gpio43", "gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim2_groups[] = अणु
	"gpio41", "gpio42",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti_groups[] = अणु
	"gpio41", "gpio42", "gpio100", "gpio101",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim3_groups[] = अणु
	"gpio49", "gpio50", "gpio51", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi9_groups[] = अणु
	"gpio49", "gpio50", "gpio51", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart9_groups[] = अणु
	"gpio49", "gpio50", "gpio51", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim9_groups[] = अणु
	"gpio49", "gpio50",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp10_spi_groups[] = अणु
	"gpio49", "gpio50", "gpio51", "gpio52", "gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c9_groups[] = अणु
	"gpio51", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi7_groups[] = अणु
	"gpio53", "gpio54", "gpio55", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart7_groups[] = अणु
	"gpio53", "gpio54", "gpio55", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim7_groups[] = अणु
	"gpio53", "gpio54",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_tracedata_a_groups[] = अणु
	"gpio53", "gpio54", "gpio63", "gpio64", "gpio65", "gpio66", "gpio67",
	"gpio74", "gpio75", "gpio76", "gpio77", "gpio85", "gpio86", "gpio87",
	"gpio89", "gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c7_groups[] = अणु
	"gpio55", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qua_mi2s_groups[] = अणु
	"gpio57", "gpio58", "gpio59", "gpio60", "gpio61", "gpio62", "gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp1_clk_a_groups[] = अणु
	"gpio57",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim4_groups[] = अणु
	"gpio58", "gpio59", "gpio60", "gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi11_groups[] = अणु
	"gpio58", "gpio59", "gpio60", "gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart11_groups[] = अणु
	"gpio58", "gpio59", "gpio60", "gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim11_groups[] = अणु
	"gpio58", "gpio59",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp2_clk_a_groups[] = अणु
	"gpio58",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp3_clk_a_groups[] = अणु
	"gpio59",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c11_groups[] = अणु
	"gpio60", "gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cri_trng0_groups[] = अणु
	"gpio60",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cri_trng1_groups[] = अणु
	"gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cri_trng_groups[] = अणु
	"gpio62",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग18_groups[] = अणु
	"gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pri_mi2s_groups[] = अणु
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग17_groups[] = अणु
	"gpio64",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi4_groups[] = अणु
	"gpio65", "gpio66", "gpio67", "gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart4_groups[] = अणु
	"gpio65", "gpio66", "gpio67", "gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim4_groups[] = अणु
	"gpio65", "gpio66",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग16_groups[] = अणु
	"gpio65",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग15_groups[] = अणु
	"gpio66",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dac_calib26_groups[] = अणु
	"gpio67",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c4_groups[] = अणु
	"gpio67", "gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग14_groups[] = अणु
	"gpio67",
पूर्ण;
अटल स्थिर अक्षर * स्थिर spkr_i2s_groups[] = अणु
	"gpio69", "gpio70", "gpio71", "gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर audio_ref_groups[] = अणु
	"gpio69",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lpass_slimbus_groups[] = अणु
	"gpio70", "gpio71", "gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर isense_dbg_groups[] = अणु
	"gpio70",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsense_pwm1_groups[] = अणु
	"gpio71",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsense_pwm2_groups[] = अणु
	"gpio71",
पूर्ण;
अटल स्थिर अक्षर * स्थिर btfm_slimbus_groups[] = अणु
	"gpio73", "gpio74",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ter_mi2s_groups[] = अणु
	"gpio74", "gpio75", "gpio76", "gpio77", "gpio78",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग22_groups[] = अणु
	"gpio74",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग21_groups[] = अणु
	"gpio75",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग20_groups[] = अणु
	"gpio76",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग19_groups[] = अणु
	"gpio77",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ssc_irq_groups[] = अणु
	"gpio78", "gpio79", "gpio80", "gpio117", "gpio118", "gpio119",
	"gpio120", "gpio121", "gpio122", "gpio123", "gpio124", "gpio125",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp1_clk_b_groups[] = अणु
	"gpio78",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sec_mi2s_groups[] = अणु
	"gpio79", "gpio80", "gpio81", "gpio82", "gpio83",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi5_groups[] = अणु
	"gpio81", "gpio82", "gpio83", "gpio84",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart5_groups[] = अणु
	"gpio81", "gpio82", "gpio83", "gpio84",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim5_groups[] = अणु
	"gpio81", "gpio82",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp2_clk_b_groups[] = अणु
	"gpio81",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp3_clk_b_groups[] = अणु
	"gpio82",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c5_groups[] = अणु
	"gpio83", "gpio84",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi12_groups[] = अणु
	"gpio85", "gpio86", "gpio87", "gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart12_groups[] = अणु
	"gpio85", "gpio86", "gpio87", "gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim12_groups[] = अणु
	"gpio85", "gpio86",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग25_groups[] = अणु
	"gpio85",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग31_groups[] = अणु
	"gpio86",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c12_groups[] = अणु
	"gpio87", "gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग30_groups[] = अणु
	"gpio87",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग29_groups[] = अणु
	"gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_clk_groups[] = अणु
	"gpio89",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग28_groups[] = अणु
	"gpio89",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_en_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_data_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc4_cmd_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग27_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_traceclk_b_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_error_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc43_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vfr_1_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग26_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_clk_groups[] = अणु
	"gpio93",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc4_clk_groups[] = अणु
	"gpio93",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग24_groups[] = अणु
	"gpio93",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_en_groups[] = अणु
	"gpio94",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc42_groups[] = अणु
	"gpio94",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_sपंचांग23_groups[] = अणु
	"gpio94",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_tracectl_b_groups[] = अणु
	"gpio94",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sd_card_groups[] = अणु
	"gpio95",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_data_groups[] = अणु
	"gpio95",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc41_groups[] = अणु
	"gpio95",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_sync_groups[] = अणु
	"gpio96",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc40_groups[] = अणु
	"gpio96",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync_p_b_groups[] = अणु
	"gpio97",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_en_groups[] = अणु
	"gpio97",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync_s_b_groups[] = अणु
	"gpio98",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_update_groups[] = अणु
	"gpio98",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp11_uart_tx_b_groups[] = अणु
	"gpio100",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp11_uart_rx_b_groups[] = अणु
	"gpio101",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp11_i2c_sda_b_groups[] = अणु
	"gpio102",
पूर्ण;
अटल स्थिर अक्षर * स्थिर prng_rosc_groups[] = अणु
	"gpio102",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp11_i2c_scl_b_groups[] = अणु
	"gpio103",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_groups[] = अणु
	"gpio105", "gpio106", "gpio107", "gpio108",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_groups[] = अणु
	"gpio109", "gpio110", "gpio111", "gpio112",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim_batt_groups[] = अणु
	"gpio113",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pci_e2_groups[] = अणु
	"gpio114", "gpio115", "gpio116",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pa_indicator_groups[] = अणु
	"gpio116",
पूर्ण;
अटल स्थिर अक्षर * स्थिर adsp_ext_groups[] = अणु
	"gpio118",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_bist_groups[] = अणु
	"gpio121", "gpio122", "gpio123", "gpio124",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_tracedata_11_groups[] = अणु
	"gpio123",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_tracedata_12_groups[] = अणु
	"gpio124",
पूर्ण;
अटल स्थिर अक्षर * स्थिर modem_tsync_groups[] = अणु
	"gpio128",
पूर्ण;
अटल स्थिर अक्षर * स्थिर nav_dr_groups[] = अणु
	"gpio128",
पूर्ण;
अटल स्थिर अक्षर * स्थिर nav_pps_groups[] = अणु
	"gpio128",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pci_e1_groups[] = अणु
	"gpio130", "gpio131", "gpio132",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gsm_tx_groups[] = अणु
	"gpio134", "gpio135",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_cs_groups[] = अणु
	"gpio138", "gpio141",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ssbi2_groups[] = अणु
	"gpio139",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ssbi1_groups[] = अणु
	"gpio140",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mss_lte_groups[] = अणु
	"gpio144", "gpio145",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_clk_groups[] = अणु
	"gpio145",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi0_groups[] = अणु
	"gpio146",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi1_groups[] = अणु
	"gpio147",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi2_groups[] = अणु
	"gpio148",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi3_groups[] = अणु
	"gpio149",
पूर्ण;

अटल स्थिर काष्ठा msm_function msm8996_functions[] = अणु
	FUNCTION(adsp_ext),
	FUNCTION(atest_bbrx0),
	FUNCTION(atest_bbrx1),
	FUNCTION(atest_अक्षर),
	FUNCTION(atest_अक्षर0),
	FUNCTION(atest_अक्षर1),
	FUNCTION(atest_अक्षर2),
	FUNCTION(atest_अक्षर3),
	FUNCTION(atest_gpsadc0),
	FUNCTION(atest_gpsadc1),
	FUNCTION(atest_tsens),
	FUNCTION(atest_tsens2),
	FUNCTION(atest_usb1),
	FUNCTION(atest_usb10),
	FUNCTION(atest_usb11),
	FUNCTION(atest_usb12),
	FUNCTION(atest_usb13),
	FUNCTION(atest_usb2),
	FUNCTION(atest_usb20),
	FUNCTION(atest_usb21),
	FUNCTION(atest_usb22),
	FUNCTION(atest_usb23),
	FUNCTION(audio_ref),
	FUNCTION(bimc_dte0),
	FUNCTION(bimc_dte1),
	FUNCTION(blsp10_spi),
	FUNCTION(blsp11_i2c_scl_b),
	FUNCTION(blsp11_i2c_sda_b),
	FUNCTION(blsp11_uart_rx_b),
	FUNCTION(blsp11_uart_tx_b),
	FUNCTION(blsp1_spi),
	FUNCTION(blsp2_spi),
	FUNCTION(blsp_i2c1),
	FUNCTION(blsp_i2c10),
	FUNCTION(blsp_i2c11),
	FUNCTION(blsp_i2c12),
	FUNCTION(blsp_i2c2),
	FUNCTION(blsp_i2c3),
	FUNCTION(blsp_i2c4),
	FUNCTION(blsp_i2c5),
	FUNCTION(blsp_i2c6),
	FUNCTION(blsp_i2c7),
	FUNCTION(blsp_i2c8),
	FUNCTION(blsp_i2c9),
	FUNCTION(blsp_spi1),
	FUNCTION(blsp_spi10),
	FUNCTION(blsp_spi11),
	FUNCTION(blsp_spi12),
	FUNCTION(blsp_spi2),
	FUNCTION(blsp_spi3),
	FUNCTION(blsp_spi4),
	FUNCTION(blsp_spi5),
	FUNCTION(blsp_spi6),
	FUNCTION(blsp_spi7),
	FUNCTION(blsp_spi8),
	FUNCTION(blsp_spi9),
	FUNCTION(blsp_uart1),
	FUNCTION(blsp_uart10),
	FUNCTION(blsp_uart11),
	FUNCTION(blsp_uart12),
	FUNCTION(blsp_uart2),
	FUNCTION(blsp_uart3),
	FUNCTION(blsp_uart4),
	FUNCTION(blsp_uart5),
	FUNCTION(blsp_uart6),
	FUNCTION(blsp_uart7),
	FUNCTION(blsp_uart8),
	FUNCTION(blsp_uart9),
	FUNCTION(blsp_uim1),
	FUNCTION(blsp_uim10),
	FUNCTION(blsp_uim11),
	FUNCTION(blsp_uim12),
	FUNCTION(blsp_uim2),
	FUNCTION(blsp_uim3),
	FUNCTION(blsp_uim4),
	FUNCTION(blsp_uim5),
	FUNCTION(blsp_uim6),
	FUNCTION(blsp_uim7),
	FUNCTION(blsp_uim8),
	FUNCTION(blsp_uim9),
	FUNCTION(btfm_slimbus),
	FUNCTION(cam_mclk),
	FUNCTION(cci_async),
	FUNCTION(cci_i2c),
	FUNCTION(cci_समयr0),
	FUNCTION(cci_समयr1),
	FUNCTION(cci_समयr2),
	FUNCTION(cci_समयr3),
	FUNCTION(cci_समयr4),
	FUNCTION(cri_trng),
	FUNCTION(cri_trng0),
	FUNCTION(cri_trng1),
	FUNCTION(dac_calib0),
	FUNCTION(dac_calib1),
	FUNCTION(dac_calib10),
	FUNCTION(dac_calib11),
	FUNCTION(dac_calib12),
	FUNCTION(dac_calib13),
	FUNCTION(dac_calib14),
	FUNCTION(dac_calib15),
	FUNCTION(dac_calib16),
	FUNCTION(dac_calib17),
	FUNCTION(dac_calib18),
	FUNCTION(dac_calib19),
	FUNCTION(dac_calib2),
	FUNCTION(dac_calib20),
	FUNCTION(dac_calib21),
	FUNCTION(dac_calib22),
	FUNCTION(dac_calib23),
	FUNCTION(dac_calib24),
	FUNCTION(dac_calib25),
	FUNCTION(dac_calib26),
	FUNCTION(dac_calib3),
	FUNCTION(dac_calib4),
	FUNCTION(dac_calib5),
	FUNCTION(dac_calib6),
	FUNCTION(dac_calib7),
	FUNCTION(dac_calib8),
	FUNCTION(dac_calib9),
	FUNCTION(dac_gpio),
	FUNCTION(dbg_out),
	FUNCTION(ddr_bist),
	FUNCTION(edp_hot),
	FUNCTION(edp_lcd),
	FUNCTION(gcc_gp1_clk_a),
	FUNCTION(gcc_gp1_clk_b),
	FUNCTION(gcc_gp2_clk_a),
	FUNCTION(gcc_gp2_clk_b),
	FUNCTION(gcc_gp3_clk_a),
	FUNCTION(gcc_gp3_clk_b),
	FUNCTION(gpio),
	FUNCTION(gsm_tx),
	FUNCTION(hdmi_cec),
	FUNCTION(hdmi_ddc),
	FUNCTION(hdmi_hot),
	FUNCTION(hdmi_rcv),
	FUNCTION(isense_dbg),
	FUNCTION(lकरो_en),
	FUNCTION(lकरो_update),
	FUNCTION(lpass_slimbus),
	FUNCTION(m_voc),
	FUNCTION(mdp_vsync),
	FUNCTION(mdp_vsync_p_b),
	FUNCTION(mdp_vsync_s_b),
	FUNCTION(modem_tsync),
	FUNCTION(mss_lte),
	FUNCTION(nav_dr),
	FUNCTION(nav_pps),
	FUNCTION(pa_indicator),
	FUNCTION(pci_e0),
	FUNCTION(pci_e1),
	FUNCTION(pci_e2),
	FUNCTION(pll_bypassnl),
	FUNCTION(pll_reset),
	FUNCTION(pri_mi2s),
	FUNCTION(prng_rosc),
	FUNCTION(pwr_crypto),
	FUNCTION(pwr_modem),
	FUNCTION(pwr_nav),
	FUNCTION(qdss_cti),
	FUNCTION(qdss_cti_trig_in_a),
	FUNCTION(qdss_cti_trig_in_b),
	FUNCTION(qdss_cti_trig_out_a),
	FUNCTION(qdss_cti_trig_out_b),
	FUNCTION(qdss_sपंचांग0),
	FUNCTION(qdss_sपंचांग1),
	FUNCTION(qdss_sपंचांग10),
	FUNCTION(qdss_sपंचांग11),
	FUNCTION(qdss_sपंचांग12),
	FUNCTION(qdss_sपंचांग13),
	FUNCTION(qdss_sपंचांग14),
	FUNCTION(qdss_sपंचांग15),
	FUNCTION(qdss_sपंचांग16),
	FUNCTION(qdss_sपंचांग17),
	FUNCTION(qdss_sपंचांग18),
	FUNCTION(qdss_sपंचांग19),
	FUNCTION(qdss_sपंचांग2),
	FUNCTION(qdss_sपंचांग20),
	FUNCTION(qdss_sपंचांग21),
	FUNCTION(qdss_sपंचांग22),
	FUNCTION(qdss_sपंचांग23),
	FUNCTION(qdss_sपंचांग24),
	FUNCTION(qdss_sपंचांग25),
	FUNCTION(qdss_sपंचांग26),
	FUNCTION(qdss_sपंचांग27),
	FUNCTION(qdss_sपंचांग28),
	FUNCTION(qdss_sपंचांग29),
	FUNCTION(qdss_sपंचांग3),
	FUNCTION(qdss_sपंचांग30),
	FUNCTION(qdss_sपंचांग31),
	FUNCTION(qdss_sपंचांग4),
	FUNCTION(qdss_sपंचांग5),
	FUNCTION(qdss_sपंचांग6),
	FUNCTION(qdss_sपंचांग7),
	FUNCTION(qdss_sपंचांग8),
	FUNCTION(qdss_sपंचांग9),
	FUNCTION(qdss_traceclk_a),
	FUNCTION(qdss_traceclk_b),
	FUNCTION(qdss_tracectl_a),
	FUNCTION(qdss_tracectl_b),
	FUNCTION(qdss_tracedata_11),
	FUNCTION(qdss_tracedata_12),
	FUNCTION(qdss_tracedata_a),
	FUNCTION(qdss_tracedata_b),
	FUNCTION(qspi0),
	FUNCTION(qspi1),
	FUNCTION(qspi2),
	FUNCTION(qspi3),
	FUNCTION(qspi_clk),
	FUNCTION(qspi_cs),
	FUNCTION(qua_mi2s),
	FUNCTION(sd_card),
	FUNCTION(sd_ग_लिखो),
	FUNCTION(sdc40),
	FUNCTION(sdc41),
	FUNCTION(sdc42),
	FUNCTION(sdc43),
	FUNCTION(sdc4_clk),
	FUNCTION(sdc4_cmd),
	FUNCTION(sec_mi2s),
	FUNCTION(spkr_i2s),
	FUNCTION(ssbi1),
	FUNCTION(ssbi2),
	FUNCTION(ssc_irq),
	FUNCTION(ter_mi2s),
	FUNCTION(tsense_pwm1),
	FUNCTION(tsense_pwm2),
	FUNCTION(tsअगर1_clk),
	FUNCTION(tsअगर1_data),
	FUNCTION(tsअगर1_en),
	FUNCTION(tsअगर1_error),
	FUNCTION(tsअगर1_sync),
	FUNCTION(tsअगर2_clk),
	FUNCTION(tsअगर2_data),
	FUNCTION(tsअगर2_en),
	FUNCTION(tsअगर2_error),
	FUNCTION(tsअगर2_sync),
	FUNCTION(uim1),
	FUNCTION(uim2),
	FUNCTION(uim3),
	FUNCTION(uim4),
	FUNCTION(uim_batt),
	FUNCTION(vfr_1),
पूर्ण;

अटल स्थिर काष्ठा msm_pingroup msm8996_groups[] = अणु
	PINGROUP(0, blsp_spi1, blsp_uart1, blsp_uim1, NA, NA, NA, NA, NA, NA),
	PINGROUP(1, blsp_spi1, blsp_uart1, blsp_uim1, NA, NA, NA, NA, NA, NA),
	PINGROUP(2, blsp_spi1, blsp_uart1, blsp_i2c1, NA, NA, NA, NA, NA, NA),
	PINGROUP(3, blsp_spi1, blsp_uart1, blsp_i2c1, NA, atest_tsens,
		 bimc_dte1, NA, NA, NA),
	PINGROUP(4, blsp_spi8, blsp_uart8, blsp_uim8, NA, qdss_cti_trig_out_b,
		 dac_calib0, bimc_dte0, NA, NA),
	PINGROUP(5, blsp_spi8, blsp_uart8, blsp_uim8, NA, qdss_cti_trig_in_b,
		 dac_calib1, bimc_dte1, NA, NA),
	PINGROUP(6, blsp_spi8, blsp_uart8, blsp_i2c8, NA, dac_calib2,
		 bimc_dte0, NA, NA, NA),
	PINGROUP(7, blsp_spi8, blsp_uart8, blsp_i2c8, NA, atest_tsens2,
		 atest_usb1, NA, NA, NA),
	PINGROUP(8, blsp_spi10, blsp_uart10, blsp_uim10, NA, atest_bbrx1,
		 atest_usb13, NA, NA, NA),
	PINGROUP(9, blsp_spi10, blsp_uart10, blsp_uim10, atest_bbrx0,
		 atest_usb12, NA, NA, NA, NA),
	PINGROUP(10, mdp_vsync, blsp_spi10, blsp_uart10, blsp_i2c10,
		 atest_gpsadc1, atest_usb11, NA, NA, NA),
	PINGROUP(11, mdp_vsync, blsp_spi10, blsp_uart10, blsp_i2c10,
		 atest_gpsadc0, atest_usb10, NA, NA, NA),
	PINGROUP(12, mdp_vsync, m_voc, dac_gpio, atest_अक्षर, NA, NA, NA, NA,
		 NA),
	PINGROUP(13, cam_mclk, pll_bypassnl, qdss_sपंचांग7, qdss_tracedata_b, NA,
		 NA, NA, NA, NA),
	PINGROUP(14, cam_mclk, pll_reset, qdss_sपंचांग6, qdss_tracedata_b, NA, NA,
		 NA, NA, NA),
	PINGROUP(15, cam_mclk, qdss_sपंचांग5, qdss_tracedata_b, NA, NA, NA, NA, NA,
		 NA),
	PINGROUP(16, cam_mclk, qdss_sपंचांग4, qdss_tracedata_b, NA, atest_usb2, NA,
		 NA, NA, NA),
	PINGROUP(17, cci_i2c, qdss_sपंचांग3, qdss_tracedata_b, dac_calib3,
		 atest_usb23, atest_अक्षर3, NA, NA, NA),
	PINGROUP(18, cci_i2c, qdss_sपंचांग2, qdss_tracedata_b, dac_calib4,
		 atest_usb22, atest_अक्षर2, NA, NA, NA),
	PINGROUP(19, cci_i2c, qdss_sपंचांग1, qdss_tracedata_b, dac_calib5,
		 atest_usb21, atest_अक्षर1, NA, NA, NA),
	PINGROUP(20, cci_i2c, dbg_out, qdss_sपंचांग0, dac_calib6, atest_usb20,
		 atest_अक्षर0, NA, NA, NA),
	PINGROUP(21, cci_समयr0, qdss_sपंचांग13, qdss_tracedata_b, dac_calib7, NA,
		 NA, NA, NA, NA),
	PINGROUP(22, cci_समयr1, qdss_sपंचांग12, qdss_tracedata_b, dac_calib8, NA,
		 NA, NA, NA, NA),
	PINGROUP(23, cci_समयr2, blsp1_spi, qdss_sपंचांग11, qdss_tracedata_b,
		 dac_calib9, NA, NA, NA, NA),
	PINGROUP(24, cci_समयr3, cci_async, blsp1_spi, qdss_sपंचांग10,
		 qdss_cti_trig_in_a, dac_calib10, NA, NA, NA),
	PINGROUP(25, cci_समयr4, cci_async, blsp_spi6, blsp_uart6, blsp_uim6,
		 blsp2_spi, qdss_sपंचांग9, qdss_cti_trig_out_a, dac_calib11),
	PINGROUP(26, cci_async, blsp_spi6, blsp_uart6, blsp_uim6, qdss_sपंचांग8,
		 qdss_tracedata_b, dac_calib12, NA, NA),
	PINGROUP(27, blsp_spi6, blsp_uart6, blsp_i2c6, blsp1_spi,
		 qdss_tracectl_a, dac_calib13, NA, NA, NA),
	PINGROUP(28, blsp_spi6, blsp_uart6, blsp_i2c6, blsp1_spi,
		 qdss_traceclk_a, dac_calib14, NA, NA, NA),
	PINGROUP(29, blsp2_spi, NA, qdss_tracedata_b, dac_calib15, NA, NA, NA,
		 NA, NA),
	PINGROUP(30, hdmi_rcv, blsp2_spi, dac_calib16, NA, NA, NA, NA, NA, NA),
	PINGROUP(31, hdmi_cec, pwr_modem, dac_calib17, NA, NA, NA, NA, NA, NA),
	PINGROUP(32, hdmi_ddc, pwr_nav, NA, dac_calib18, NA, NA, NA, NA, NA),
	PINGROUP(33, hdmi_ddc, pwr_crypto, NA, dac_calib19, NA, NA, NA, NA, NA),
	PINGROUP(34, hdmi_hot, NA, dac_calib20, NA, NA, NA, NA, NA, NA),
	PINGROUP(35, pci_e0, NA, dac_calib21, NA, NA, NA, NA, NA, NA),
	PINGROUP(36, pci_e0, NA, dac_calib22, NA, NA, NA, NA, NA, NA),
	PINGROUP(37, NA, dac_calib23, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(38, NA, dac_calib24, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(39, tsअगर1_sync, NA, dac_calib25, NA, NA, NA, NA, NA, NA),
	PINGROUP(40, sd_ग_लिखो, tsअगर1_error, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(41, blsp_spi2, blsp_uart2, blsp_uim2, NA, qdss_cti,
		 dac_calib0, NA, NA, NA),
	PINGROUP(42, blsp_spi2, blsp_uart2, blsp_uim2, NA, qdss_cti,
		 dac_calib1, NA, NA, NA),
	PINGROUP(43, blsp_spi2, blsp_uart2, blsp_i2c2, NA, dac_calib2, NA, NA,
		 NA, NA),
	PINGROUP(44, blsp_spi2, blsp_uart2, blsp_i2c2, NA, dac_calib3, NA, NA,
		 NA, NA),
	PINGROUP(45, blsp_spi3, blsp_uart3, blsp_uim3, NA, dac_calib4, NA, NA,
		 NA, NA),
	PINGROUP(46, blsp_spi3, blsp_uart3, blsp_uim3, NA, dac_calib5, NA, NA,
		 NA, NA),
	PINGROUP(47, blsp_spi3, blsp_uart3, blsp_i2c3, dac_calib6, NA, NA, NA,
		 NA, NA),
	PINGROUP(48, blsp_spi3, blsp_uart3, blsp_i2c3, dac_calib7, NA, NA, NA,
		 NA, NA),
	PINGROUP(49, uim3, blsp_spi9, blsp_uart9, blsp_uim9, blsp10_spi,
		 dac_calib8, NA, NA, NA),
	PINGROUP(50, uim3, blsp_spi9, blsp_uart9, blsp_uim9, blsp10_spi,
		 dac_calib9, NA, NA, NA),
	PINGROUP(51, uim3, blsp_spi9, blsp_uart9, blsp_i2c9, blsp10_spi,
		 dac_calib10, NA, NA, NA),
	PINGROUP(52, uim3, blsp_spi9, blsp_uart9, blsp_i2c9,
		 blsp10_spi, dac_calib11, NA, NA, NA),
	PINGROUP(53, blsp_spi7, blsp_uart7, blsp_uim7, NA, qdss_tracedata_a,
		 dac_calib12, NA, NA, NA),
	PINGROUP(54, blsp_spi7, blsp_uart7, blsp_uim7, NA, NA,
		 qdss_tracedata_a, dac_calib13, NA, NA),
	PINGROUP(55, blsp_spi7, blsp_uart7, blsp_i2c7, NA, dac_calib14, NA, NA,
		 NA, NA),
	PINGROUP(56, blsp_spi7, blsp_uart7, blsp_i2c7, NA, dac_calib15, NA, NA,
		 NA, NA),
	PINGROUP(57, qua_mi2s, gcc_gp1_clk_a, NA, qdss_tracedata_b,
		 dac_calib16, NA, NA, NA, NA),
	PINGROUP(58, qua_mi2s, uim4, blsp_spi11, blsp_uart11, blsp_uim11,
		 gcc_gp2_clk_a, NA, qdss_tracedata_b, dac_calib17),
	PINGROUP(59, qua_mi2s, uim4, blsp_spi11, blsp_uart11, blsp_uim11,
		 gcc_gp3_clk_a, NA, dac_calib18, NA),
	PINGROUP(60, qua_mi2s, uim4, blsp_spi11, blsp_uart11, blsp_i2c11,
		 cri_trng0, NA, dac_calib19, NA),
	PINGROUP(61, qua_mi2s, uim4, blsp_spi11, blsp_uart11,
		 blsp_i2c11, cri_trng1, NA, dac_calib20, NA),
	PINGROUP(62, qua_mi2s, cri_trng, NA, dac_calib21, NA, NA, NA, NA, NA),
	PINGROUP(63, qua_mi2s, NA, NA, qdss_sपंचांग18, qdss_tracedata_a,
		 dac_calib22, NA, NA, NA),
	PINGROUP(64, pri_mi2s, NA, qdss_sपंचांग17, qdss_tracedata_a, dac_calib23,
		 NA, NA, NA, NA),
	PINGROUP(65, pri_mi2s, blsp_spi4, blsp_uart4, blsp_uim4, NA,
		 qdss_sपंचांग16, qdss_tracedata_a, dac_calib24, NA),
	PINGROUP(66, pri_mi2s, blsp_spi4, blsp_uart4, blsp_uim4, NA,
		 qdss_sपंचांग15, qdss_tracedata_a, dac_calib25, NA),
	PINGROUP(67, pri_mi2s, blsp_spi4, blsp_uart4, blsp_i2c4, qdss_sपंचांग14,
		 qdss_tracedata_a, dac_calib26, NA, NA),
	PINGROUP(68, pri_mi2s, blsp_spi4, blsp_uart4, blsp_i2c4, NA, NA, NA,
		 NA, NA),
	PINGROUP(69, spkr_i2s, audio_ref, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(70, lpass_slimbus, spkr_i2s, isense_dbg, NA, NA, NA, NA, NA,
		 NA),
	PINGROUP(71, lpass_slimbus, spkr_i2s, tsense_pwm1, tsense_pwm2, NA, NA,
		 NA, NA, NA),
	PINGROUP(72, lpass_slimbus, spkr_i2s, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(73, btfm_slimbus, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(74, btfm_slimbus, ter_mi2s, qdss_sपंचांग22, qdss_tracedata_a, NA,
		 NA, NA, NA, NA),
	PINGROUP(75, ter_mi2s, qdss_sपंचांग21, qdss_tracedata_a, NA, NA, NA, NA,
		 NA, NA),
	PINGROUP(76, ter_mi2s, qdss_sपंचांग20, qdss_tracedata_a, NA, NA, NA, NA,
		 NA, NA),
	PINGROUP(77, ter_mi2s, qdss_sपंचांग19, qdss_tracedata_a, NA, NA, NA, NA,
		 NA, NA),
	PINGROUP(78, ter_mi2s, gcc_gp1_clk_b, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(79, sec_mi2s, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(80, sec_mi2s, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(81, sec_mi2s, blsp_spi5, blsp_uart5, blsp_uim5, gcc_gp2_clk_b,
		 NA, NA, NA, NA),
	PINGROUP(82, sec_mi2s, blsp_spi5, blsp_uart5, blsp_uim5, gcc_gp3_clk_b,
		 NA, NA, NA, NA),
	PINGROUP(83, sec_mi2s, blsp_spi5, blsp_uart5, blsp_i2c5, NA, NA, NA,
		 NA, NA),
	PINGROUP(84, blsp_spi5, blsp_uart5, blsp_i2c5, NA, NA, NA, NA, NA, NA),
	PINGROUP(85, blsp_spi12, blsp_uart12, blsp_uim12, NA, qdss_sपंचांग25,
		 qdss_tracedata_a, NA, NA, NA),
	PINGROUP(86, blsp_spi12, blsp_uart12, blsp_uim12, NA, NA, qdss_sपंचांग31,
		 qdss_tracedata_a, NA, NA),
	PINGROUP(87, blsp_spi12, blsp_uart12, blsp_i2c12, NA, qdss_sपंचांग30,
		 qdss_tracedata_a, NA, NA, NA),
	PINGROUP(88, blsp_spi12, blsp_uart12, blsp_i2c12, blsp10_spi, NA,
		 qdss_sपंचांग29, NA, NA, NA),
	PINGROUP(89, tsअगर1_clk, qdss_sपंचांग28, qdss_tracedata_a, NA, NA, NA, NA,
		 NA, NA),
	PINGROUP(90, tsअगर1_en, blsp1_spi, qdss_tracedata_a, NA, NA, NA, NA, NA,
		 NA),
	PINGROUP(91, tsअगर1_data, sdc4_cmd, qdss_sपंचांग27, qdss_traceclk_b, NA, NA,
		 NA, NA, NA),
	PINGROUP(92, tsअगर2_error, sdc43, vfr_1, qdss_sपंचांग26, qdss_tracedata_b,
		 NA, NA, NA, NA),
	PINGROUP(93, tsअगर2_clk, sdc4_clk, NA, qdss_sपंचांग24, qdss_tracedata_b, NA,
		 NA, NA, NA),
	PINGROUP(94, tsअगर2_en, sdc42, NA, qdss_sपंचांग23, qdss_tracectl_b, NA, NA,
		 NA, NA),
	PINGROUP(95, tsअगर2_data, sdc41, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(96, tsअगर2_sync, sdc40, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(97, NA, NA, mdp_vsync_p_b, lकरो_en, NA, NA, NA, NA, NA),
	PINGROUP(98, NA, NA, mdp_vsync_s_b, lकरो_update, NA, NA, NA, NA, NA),
	PINGROUP(99, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(100, NA, NA, blsp11_uart_tx_b, qdss_cti, NA, NA, NA, NA, NA),
	PINGROUP(101, NA, blsp11_uart_rx_b, qdss_cti, NA, NA, NA, NA, NA, NA),
	PINGROUP(102, NA, blsp11_i2c_sda_b, prng_rosc, NA, NA, NA, NA, NA, NA),
	PINGROUP(103, NA, blsp11_i2c_scl_b, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(104, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(105, uim2, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(106, uim2, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(107, uim2, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(108, uim2, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(109, uim1, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(110, uim1, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(111, uim1, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(112, uim1, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(113, uim_batt, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(114, NA, pci_e2, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(115, NA, pci_e2, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(116, NA, pa_indicator, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(117, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(118, adsp_ext, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(119, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(120, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(121, ddr_bist, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(122, ddr_bist, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(123, ddr_bist, qdss_tracedata_11, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(124, ddr_bist, qdss_tracedata_12, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(125, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(126, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(127, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(128, NA, modem_tsync, nav_dr, nav_pps, NA, NA, NA, NA, NA),
	PINGROUP(129, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(130, pci_e1, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(131, pci_e1, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(132, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(133, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(134, gsm_tx, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(135, gsm_tx, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(136, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(137, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(138, NA, qspi_cs, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(139, NA, ssbi2, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(140, NA, ssbi1, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(141, NA, qspi_cs, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(142, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(143, NA, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(144, mss_lte, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(145, mss_lte, qspi_clk, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(146, NA, qspi0, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(147, NA, qspi1, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(148, NA, qspi2, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(149, NA, qspi3, NA, NA, NA, NA, NA, NA, NA),
	SDC_QDSD_PINGROUP(sdc1_clk, 0x12c000, 13, 6),
	SDC_QDSD_PINGROUP(sdc1_cmd, 0x12c000, 11, 3),
	SDC_QDSD_PINGROUP(sdc1_data, 0x12c000, 9, 0),
	SDC_QDSD_PINGROUP(sdc2_clk, 0x12d000, 14, 6),
	SDC_QDSD_PINGROUP(sdc2_cmd, 0x12d000, 11, 3),
	SDC_QDSD_PINGROUP(sdc2_data, 0x12d000, 9, 0),
	SDC_QDSD_PINGROUP(sdc1_rclk, 0x12c000, 15, 0),
पूर्ण;

अटल स्थिर काष्ठा msm_pinctrl_soc_data msm8996_pinctrl = अणु
	.pins = msm8996_pins,
	.npins = ARRAY_SIZE(msm8996_pins),
	.functions = msm8996_functions,
	.nfunctions = ARRAY_SIZE(msm8996_functions),
	.groups = msm8996_groups,
	.ngroups = ARRAY_SIZE(msm8996_groups),
	.ngpios = 150,
पूर्ण;

अटल पूर्णांक msm8996_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस msm_pinctrl_probe(pdev, &msm8996_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id msm8996_pinctrl_of_match[] = अणु
	अणु .compatible = "qcom,msm8996-pinctrl", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver msm8996_pinctrl_driver = अणु
	.driver = अणु
		.name = "msm8996-pinctrl",
		.of_match_table = msm8996_pinctrl_of_match,
	पूर्ण,
	.probe = msm8996_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init msm8996_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&msm8996_pinctrl_driver);
पूर्ण
arch_initcall(msm8996_pinctrl_init);

अटल व्योम __निकास msm8996_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&msm8996_pinctrl_driver);
पूर्ण
module_निकास(msm8996_pinctrl_निकास);

MODULE_DESCRIPTION("Qualcomm msm8996 pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, msm8996_pinctrl_of_match);
