<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-msm.h"

#घोषणा FUNCTION(fname)					\
	[msm_mux_##fname] = अणु				\
		.name = #fname,				\
		.groups = fname##_groups,               \
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

#घोषणा PINGROUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	अणु							\
		.name = "gpio" #id,				\
		.pins = gpio##id##_pins,			\
		.npins = ARRAY_SIZE(gpio##id##_pins),		\
		.funcs = (पूर्णांक[])अणु				\
			msm_mux_gpio, /* gpio mode */		\
			msm_mux_##f1,				\
			msm_mux_##f2,				\
			msm_mux_##f3,				\
			msm_mux_##f4,				\
			msm_mux_##f5,				\
			msm_mux_##f6,				\
			msm_mux_##f7,				\
			msm_mux_##f8,				\
			msm_mux_##f9				\
		पूर्ण,						\
		.nfuncs = 10,					\
		.ctl_reg = 0x1000 * id,				\
		.io_reg = 0x4 + 0x1000 * id,			\
		.पूर्णांकr_cfg_reg = 0x8 + 0x1000 * id,		\
		.पूर्णांकr_status_reg = 0xc + 0x1000 * id,		\
		.पूर्णांकr_target_reg = 0x8 + 0x1000 * id,		\
		.mux_bit = 2,					\
		.pull_bit = 0,					\
		.drv_bit = 6,					\
		.oe_bit = 9,					\
		.in_bit = 0,					\
		.out_bit = 1,					\
		.पूर्णांकr_enable_bit = 0,				\
		.पूर्णांकr_status_bit = 0,				\
		.पूर्णांकr_target_bit = 5,				\
		.पूर्णांकr_target_kpss_val = 4,			\
		.पूर्णांकr_raw_status_bit = 4,			\
		.पूर्णांकr_polarity_bit = 1,				\
		.पूर्णांकr_detection_bit = 2,			\
		.पूर्णांकr_detection_width = 2,			\
	पूर्ण

#घोषणा SDC_QDSD_PINGROUP(pg_name, ctl, pull, drv)	\
	अणु					        \
		.name = #pg_name,			\
		.pins = pg_name##_pins,			\
		.npins = ARRAY_SIZE(pg_name##_pins),	\
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

अटल स्थिर काष्ठा pinctrl_pin_desc msm8953_pins[] = अणु
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
	PINCTRL_PIN(142, "SDC1_CLK"),
	PINCTRL_PIN(143, "SDC1_CMD"),
	PINCTRL_PIN(144, "SDC1_DATA"),
	PINCTRL_PIN(145, "SDC1_RCLK"),
	PINCTRL_PIN(146, "SDC2_CLK"),
	PINCTRL_PIN(147, "SDC2_CMD"),
	PINCTRL_PIN(148, "SDC2_DATA"),
	PINCTRL_PIN(149, "QDSD_CLK"),
	PINCTRL_PIN(150, "QDSD_CMD"),
	PINCTRL_PIN(151, "QDSD_DATA0"),
	PINCTRL_PIN(152, "QDSD_DATA1"),
	PINCTRL_PIN(153, "QDSD_DATA2"),
	PINCTRL_PIN(154, "QDSD_DATA3"),
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

अटल स्थिर अचिन्हित पूर्णांक qdsd_clk_pins[] = अणु 142 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qdsd_cmd_pins[] = अणु 143 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qdsd_data0_pins[] = अणु 144 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qdsd_data1_pins[] = अणु 145 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qdsd_data2_pins[] = अणु 146 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qdsd_data3_pins[] = अणु 147 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_clk_pins[] = अणु 148 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_cmd_pins[] = अणु 149 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_data_pins[] = अणु 150 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_rclk_pins[] = अणु 151 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_clk_pins[] = अणु 152 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_cmd_pins[] = अणु 153 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_data_pins[] = अणु 154 पूर्ण;

क्रमागत msm8953_functions अणु
	msm_mux_accel_पूर्णांक,
	msm_mux_adsp_ext,
	msm_mux_alsp_पूर्णांक,
	msm_mux_atest_bbrx0,
	msm_mux_atest_bbrx1,
	msm_mux_atest_अक्षर,
	msm_mux_atest_अक्षर0,
	msm_mux_atest_अक्षर1,
	msm_mux_atest_अक्षर2,
	msm_mux_atest_अक्षर3,
	msm_mux_atest_gpsadc_dtest0_native,
	msm_mux_atest_gpsadc_dtest1_native,
	msm_mux_atest_tsens,
	msm_mux_atest_wlan0,
	msm_mux_atest_wlan1,
	msm_mux_bimc_dte0,
	msm_mux_bimc_dte1,
	msm_mux_blsp1_spi,
	msm_mux_blsp3_spi,
	msm_mux_blsp6_spi,
	msm_mux_blsp7_spi,
	msm_mux_blsp_i2c1,
	msm_mux_blsp_i2c2,
	msm_mux_blsp_i2c3,
	msm_mux_blsp_i2c4,
	msm_mux_blsp_i2c5,
	msm_mux_blsp_i2c6,
	msm_mux_blsp_i2c7,
	msm_mux_blsp_i2c8,
	msm_mux_blsp_spi1,
	msm_mux_blsp_spi2,
	msm_mux_blsp_spi3,
	msm_mux_blsp_spi4,
	msm_mux_blsp_spi5,
	msm_mux_blsp_spi6,
	msm_mux_blsp_spi7,
	msm_mux_blsp_spi8,
	msm_mux_blsp_uart2,
	msm_mux_blsp_uart4,
	msm_mux_blsp_uart5,
	msm_mux_blsp_uart6,
	msm_mux_cam0_lकरो,
	msm_mux_cam1_lकरो,
	msm_mux_cam1_rst,
	msm_mux_cam1_standby,
	msm_mux_cam2_rst,
	msm_mux_cam2_standby,
	msm_mux_cam3_rst,
	msm_mux_cam3_standby,
	msm_mux_cam_irq,
	msm_mux_cam_mclk,
	msm_mux_cap_पूर्णांक,
	msm_mux_cci_async,
	msm_mux_cci_i2c,
	msm_mux_cci_समयr0,
	msm_mux_cci_समयr1,
	msm_mux_cci_समयr2,
	msm_mux_cci_समयr3,
	msm_mux_cci_समयr4,
	msm_mux_cdc_pdm0,
	msm_mux_codec_पूर्णांक1,
	msm_mux_codec_पूर्णांक2,
	msm_mux_codec_reset,
	msm_mux_cri_trng,
	msm_mux_cri_trng0,
	msm_mux_cri_trng1,
	msm_mux_dac_calib0,
	msm_mux_dac_calib1,
	msm_mux_dac_calib2,
	msm_mux_dac_calib3,
	msm_mux_dac_calib4,
	msm_mux_dac_calib5,
	msm_mux_dac_calib6,
	msm_mux_dac_calib7,
	msm_mux_dac_calib8,
	msm_mux_dac_calib9,
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
	msm_mux_dac_calib20,
	msm_mux_dac_calib21,
	msm_mux_dac_calib22,
	msm_mux_dac_calib23,
	msm_mux_dac_calib24,
	msm_mux_dac_calib25,
	msm_mux_dbg_out,
	msm_mux_ddr_bist,
	msm_mux_dmic0_clk,
	msm_mux_dmic0_data,
	msm_mux_ebi_cdc,
	msm_mux_ebi_ch0,
	msm_mux_ext_lpass,
	msm_mux_flash_strobe,
	msm_mux_fp_पूर्णांक,
	msm_mux_gcc_gp1_clk_a,
	msm_mux_gcc_gp1_clk_b,
	msm_mux_gcc_gp2_clk_a,
	msm_mux_gcc_gp2_clk_b,
	msm_mux_gcc_gp3_clk_a,
	msm_mux_gcc_gp3_clk_b,
	msm_mux_gcc_plltest,
	msm_mux_gcc_tlmm,
	msm_mux_gpio,
	msm_mux_gsm0_tx,
	msm_mux_gsm1_tx,
	msm_mux_gyro_पूर्णांक,
	msm_mux_hall_पूर्णांक,
	msm_mux_hdmi_पूर्णांक,
	msm_mux_key_focus,
	msm_mux_key_home,
	msm_mux_key_snapshot,
	msm_mux_key_volp,
	msm_mux_lकरो_en,
	msm_mux_lकरो_update,
	msm_mux_lpass_slimbus,
	msm_mux_lpass_slimbus0,
	msm_mux_lpass_slimbus1,
	msm_mux_m_voc,
	msm_mux_mag_पूर्णांक,
	msm_mux_mdp_vsync,
	msm_mux_mipi_dsi0,
	msm_mux_modem_tsync,
	msm_mux_mss_lte,
	msm_mux_nav_pps,
	msm_mux_nav_pps_in_a,
	msm_mux_nav_pps_in_b,
	msm_mux_nav_tsync,
	msm_mux_nfc_disable,
	msm_mux_nfc_dwl,
	msm_mux_nfc_irq,
	msm_mux_ois_sync,
	msm_mux_pa_indicator,
	msm_mux_pbs0,
	msm_mux_pbs1,
	msm_mux_pbs2,
	msm_mux_pressure_पूर्णांक,
	msm_mux_pri_mi2s,
	msm_mux_pri_mi2s_mclk_a,
	msm_mux_pri_mi2s_mclk_b,
	msm_mux_pri_mi2s_ws,
	msm_mux_prng_rosc,
	msm_mux_pwr_crypto_enabled_a,
	msm_mux_pwr_crypto_enabled_b,
	msm_mux_pwr_करोwn,
	msm_mux_pwr_modem_enabled_a,
	msm_mux_pwr_modem_enabled_b,
	msm_mux_pwr_nav_enabled_a,
	msm_mux_pwr_nav_enabled_b,
	msm_mux_qdss_cti_trig_in_a0,
	msm_mux_qdss_cti_trig_in_a1,
	msm_mux_qdss_cti_trig_in_b0,
	msm_mux_qdss_cti_trig_in_b1,
	msm_mux_qdss_cti_trig_out_a0,
	msm_mux_qdss_cti_trig_out_a1,
	msm_mux_qdss_cti_trig_out_b0,
	msm_mux_qdss_cti_trig_out_b1,
	msm_mux_qdss_traceclk_a,
	msm_mux_qdss_traceclk_b,
	msm_mux_qdss_tracectl_a,
	msm_mux_qdss_tracectl_b,
	msm_mux_qdss_tracedata_a,
	msm_mux_qdss_tracedata_b,
	msm_mux_sd_ग_लिखो,
	msm_mux_sdcard_det,
	msm_mux_sec_mi2s,
	msm_mux_sec_mi2s_mclk_a,
	msm_mux_sec_mi2s_mclk_b,
	msm_mux_smb_पूर्णांक,
	msm_mux_ss_चयन,
	msm_mux_ssbi_wtr1,
	msm_mux_ts_resout,
	msm_mux_ts_sample,
	msm_mux_ts_xvdd,
	msm_mux_tsens_max,
	msm_mux_uim1_clk,
	msm_mux_uim1_data,
	msm_mux_uim1_present,
	msm_mux_uim1_reset,
	msm_mux_uim2_clk,
	msm_mux_uim2_data,
	msm_mux_uim2_present,
	msm_mux_uim2_reset,
	msm_mux_uim_batt,
	msm_mux_us_emitter,
	msm_mux_us_euro,
	msm_mux_wcss_bt,
	msm_mux_wcss_fm,
	msm_mux_wcss_wlan,
	msm_mux_wcss_wlan0,
	msm_mux_wcss_wlan1,
	msm_mux_wcss_wlan2,
	msm_mux_wsa_en,
	msm_mux_wsa_io,
	msm_mux_wsa_irq,
	msm_mux__,
पूर्ण;

अटल स्थिर अक्षर * स्थिर accel_पूर्णांक_groups[] = अणु
	"gpio42",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsp_ext_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर alsp_पूर्णांक_groups[] = अणु
	"gpio43",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_bbrx0_groups[] = अणु
	"gpio17",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_bbrx1_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर0_groups[] = अणु
	"gpio68",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर1_groups[] = अणु
	"gpio67",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर2_groups[] = अणु
	"gpio75",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर3_groups[] = अणु
	"gpio63",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर_groups[] = अणु
	"gpio120",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_gpsadc_dtest0_native_groups[] = अणु
	"gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_gpsadc_dtest1_native_groups[] = अणु
	"gpio18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_tsens_groups[] = अणु
	"gpio120",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_wlan0_groups[] = अणु
	"gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_wlan1_groups[] = अणु
	"gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bimc_dte0_groups[] = अणु
	"gpio63", "gpio65",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bimc_dte1_groups[] = अणु
	"gpio121", "gpio122",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp1_spi_groups[] = अणु
	"gpio35", "gpio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_spi_groups[] = अणु
	"gpio41", "gpio50",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp6_spi_groups[] = अणु
	"gpio47", "gpio48",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp7_spi_groups[] = अणु
	"gpio89", "gpio90",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c1_groups[] = अणु
	"gpio2", "gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c2_groups[] = अणु
	"gpio6", "gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c3_groups[] = अणु
	"gpio10", "gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c4_groups[] = अणु
	"gpio14", "gpio15",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c5_groups[] = अणु
	"gpio18", "gpio19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c6_groups[] = अणु
	"gpio22", "gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c7_groups[] = अणु
	"gpio135", "gpio136",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_i2c8_groups[] = अणु
	"gpio98", "gpio99",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi1_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi2_groups[] = अणु
	"gpio4", "gpio5", "gpio6", "gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi3_groups[] = अणु
	"gpio8", "gpio9", "gpio10", "gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi4_groups[] = अणु
	"gpio12", "gpio13", "gpio14", "gpio15",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi5_groups[] = अणु
	"gpio16", "gpio17", "gpio18", "gpio19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi6_groups[] = अणु
	"gpio20", "gpio21", "gpio22", "gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi7_groups[] = अणु
	"gpio135", "gpio136", "gpio137", "gpio138",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_spi8_groups[] = अणु
	"gpio96", "gpio97", "gpio98", "gpio99",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_uart2_groups[] = अणु
	"gpio4", "gpio5", "gpio6", "gpio7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_uart4_groups[] = अणु
	"gpio12", "gpio13", "gpio14", "gpio15",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_uart5_groups[] = अणु
	"gpio16", "gpio17", "gpio18", "gpio19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp_uart6_groups[] = अणु
	"gpio20", "gpio21", "gpio22", "gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam0_lकरो_groups[] = अणु
	"gpio50",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam1_lकरो_groups[] = अणु
	"gpio134",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam1_rst_groups[] = अणु
	"gpio40",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam1_standby_groups[] = अणु
	"gpio39",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam2_rst_groups[] = अणु
	"gpio129",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam2_standby_groups[] = अणु
	"gpio130",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam3_rst_groups[] = अणु
	"gpio131",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam3_standby_groups[] = अणु
	"gpio132",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam_irq_groups[] = अणु
	"gpio35",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cam_mclk_groups[] = अणु
	"gpio26", "gpio27", "gpio28", "gpio128",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cap_पूर्णांक_groups[] = अणु
	"gpio13",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cci_async_groups[] = अणु
	"gpio38",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cci_i2c_groups[] = अणु
	"gpio29", "gpio30", "gpio31", "gpio32",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cci_समयr0_groups[] = अणु
	"gpio33",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cci_समयr1_groups[] = अणु
	"gpio34",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cci_समयr2_groups[] = अणु
	"gpio35",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cci_समयr3_groups[] = अणु
	"gpio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cci_समयr4_groups[] = अणु
	"gpio41",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cdc_pdm0_groups[] = अणु
	"gpio67", "gpio68", "gpio69", "gpio70", "gpio71", "gpio72", "gpio73",
	"gpio74",
पूर्ण;

अटल स्थिर अक्षर * स्थिर codec_पूर्णांक1_groups[] = अणु
	"gpio73",
पूर्ण;

अटल स्थिर अक्षर * स्थिर codec_पूर्णांक2_groups[] = अणु
	"gpio74",
पूर्ण;

अटल स्थिर अक्षर * स्थिर codec_reset_groups[] = अणु
	"gpio67",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cri_trng0_groups[] = अणु
	"gpio85",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cri_trng1_groups[] = अणु
	"gpio86",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cri_trng_groups[] = अणु
	"gpio87",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib0_groups[] = अणु
	"gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib1_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib2_groups[] = अणु
	"gpio13",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib3_groups[] = अणु
	"gpio28",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib4_groups[] = अणु
	"gpio29",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib5_groups[] = अणु
	"gpio39",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib6_groups[] = अणु
	"gpio40",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib7_groups[] = अणु
	"gpio41",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib8_groups[] = अणु
	"gpio42",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib9_groups[] = अणु
	"gpio43",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib10_groups[] = अणु
	"gpio44",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib11_groups[] = अणु
	"gpio45",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib12_groups[] = अणु
	"gpio46",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib13_groups[] = अणु
	"gpio47",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib14_groups[] = अणु
	"gpio48",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib15_groups[] = अणु
	"gpio20",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib16_groups[] = अणु
	"gpio21",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib17_groups[] = अणु
	"gpio67",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib18_groups[] = अणु
	"gpio115",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib19_groups[] = अणु
	"gpio30",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib20_groups[] = अणु
	"gpio128",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib21_groups[] = अणु
	"gpio129",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib22_groups[] = अणु
	"gpio130",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib23_groups[] = अणु
	"gpio131",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib24_groups[] = अणु
	"gpio132",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dac_calib25_groups[] = अणु
	"gpio133",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dbg_out_groups[] = अणु
	"gpio63",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ddr_bist_groups[] = अणु
	"gpio129", "gpio130", "gpio131", "gpio132",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmic0_clk_groups[] = अणु
	"gpio89",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dmic0_data_groups[] = अणु
	"gpio90",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ebi_cdc_groups[] = अणु
	"gpio67", "gpio69", "gpio118", "gpio119", "gpio120", "gpio123",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ebi_ch0_groups[] = अणु
	"gpio75",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ext_lpass_groups[] = अणु
	"gpio81",
पूर्ण;

अटल स्थिर अक्षर * स्थिर flash_strobe_groups[] = अणु
	"gpio33", "gpio34",
पूर्ण;

अटल स्थिर अक्षर * स्थिर fp_पूर्णांक_groups[] = अणु
	"gpio48",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_gp1_clk_a_groups[] = अणु
	"gpio42",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_gp1_clk_b_groups[] = अणु
	"gpio6", "gpio41",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_gp2_clk_a_groups[] = अणु
	"gpio43",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_gp2_clk_b_groups[] = अणु
	"gpio10",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_gp3_clk_a_groups[] = अणु
	"gpio44",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_gp3_clk_b_groups[] = अणु
	"gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_plltest_groups[] = अणु
	"gpio98", "gpio99",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_tlmm_groups[] = अणु
	"gpio87",
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
	"gpio141",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gsm0_tx_groups[] = अणु
	"gpio117",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gsm1_tx_groups[] = अणु
	"gpio115",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gyro_पूर्णांक_groups[] = अणु
	"gpio45",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hall_पूर्णांक_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_पूर्णांक_groups[] = अणु
	"gpio90",
पूर्ण;

अटल स्थिर अक्षर * स्थिर key_focus_groups[] = अणु
	"gpio87",
पूर्ण;

अटल स्थिर अक्षर * स्थिर key_home_groups[] = अणु
	"gpio88",
पूर्ण;

अटल स्थिर अक्षर * स्थिर key_snapshot_groups[] = अणु
	"gpio86",
पूर्ण;

अटल स्थिर अक्षर * स्थिर key_volp_groups[] = अणु
	"gpio85",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lकरो_en_groups[] = अणु
	"gpio5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lकरो_update_groups[] = अणु
	"gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lpass_slimbus0_groups[] = अणु
	"gpio71",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lpass_slimbus1_groups[] = अणु
	"gpio72",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lpass_slimbus_groups[] = अणु
	"gpio70",
पूर्ण;

अटल स्थिर अक्षर * स्थिर m_voc_groups[] = अणु
	"gpio17", "gpio21",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mag_पूर्णांक_groups[] = अणु
	"gpio44",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mdp_vsync_groups[] = अणु
	"gpio24", "gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mipi_dsi0_groups[] = अणु
	"gpio61",
पूर्ण;

अटल स्थिर अक्षर * स्थिर modem_tsync_groups[] = अणु
	"gpio113",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mss_lte_groups[] = अणु
	"gpio82", "gpio83",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nav_pps_groups[] = अणु
	"gpio113",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nav_pps_in_a_groups[] = अणु
	"gpio111",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nav_pps_in_b_groups[] = अणु
	"gpio113",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nav_tsync_groups[] = अणु
	"gpio113",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nfc_disable_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nfc_dwl_groups[] = अणु
	"gpio62",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nfc_irq_groups[] = अणु
	"gpio17",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ois_sync_groups[] = अणु
	"gpio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pa_indicator_groups[] = अणु
	"gpio112",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pbs0_groups[] = अणु
	"gpio85",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pbs1_groups[] = अणु
	"gpio86",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pbs2_groups[] = अणु
	"gpio87",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pressure_पूर्णांक_groups[] = अणु
	"gpio46",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pri_mi2s_groups[] = अणु
	"gpio66", "gpio88", "gpio91", "gpio93", "gpio94", "gpio95",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pri_mi2s_mclk_a_groups[] = अणु
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pri_mi2s_mclk_b_groups[] = अणु
	"gpio69",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pri_mi2s_ws_groups[] = अणु
	"gpio92",
पूर्ण;

अटल स्थिर अक्षर * स्थिर prng_rosc_groups[] = अणु
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwr_crypto_enabled_a_groups[] = अणु
	"gpio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwr_crypto_enabled_b_groups[] = अणु
	"gpio13",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwr_करोwn_groups[] = अणु
	"gpio89",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwr_modem_enabled_a_groups[] = अणु
	"gpio29",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwr_modem_enabled_b_groups[] = अणु
	"gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwr_nav_enabled_a_groups[] = अणु
	"gpio35",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwr_nav_enabled_b_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_a0_groups[] = अणु
	"gpio17",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_a1_groups[] = अणु
	"gpio91",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_b0_groups[] = अणु
	"gpio21",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_b1_groups[] = अणु
	"gpio48",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_a0_groups[] = अणु
	"gpio41",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_a1_groups[] = अणु
	"gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_b0_groups[] = अणु
	"gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_b1_groups[] = अणु
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_traceclk_a_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_traceclk_b_groups[] = अणु
	"gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracectl_a_groups[] = अणु
	"gpio18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracectl_b_groups[] = अणु
	"gpio20",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracedata_a_groups[] = अणु
	"gpio19", "gpio26", "gpio27", "gpio28", "gpio29", "gpio30", "gpio31",
	"gpio32", "gpio33", "gpio34", "gpio35", "gpio36", "gpio38", "gpio39",
	"gpio40", "gpio50",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracedata_b_groups[] = अणु
	"gpio8", "gpio9", "gpio12", "gpio13", "gpio23", "gpio42", "gpio43",
	"gpio44", "gpio45", "gpio46", "gpio47", "gpio66", "gpio86", "gpio87",
	"gpio88", "gpio92",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd_ग_लिखो_groups[] = अणु
	"gpio50",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdcard_det_groups[] = अणु
	"gpio133",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sec_mi2s_groups[] = अणु
	"gpio135", "gpio136", "gpio137", "gpio138",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sec_mi2s_mclk_a_groups[] = अणु
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sec_mi2s_mclk_b_groups[] = अणु
	"gpio66",
पूर्ण;

अटल स्थिर अक्षर * स्थिर smb_पूर्णांक_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ss_चयन_groups[] = अणु
	"gpio139",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ssbi_wtr1_groups[] = अणु
	"gpio114", "gpio123",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ts_resout_groups[] = अणु
	"gpio64",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ts_sample_groups[] = अणु
	"gpio65",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ts_xvdd_groups[] = अणु
	"gpio60",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tsens_max_groups[] = अणु
	"gpio139",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim1_clk_groups[] = अणु
	"gpio52",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim1_data_groups[] = अणु
	"gpio51",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim1_present_groups[] = अणु
	"gpio54",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim1_reset_groups[] = अणु
	"gpio53",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim2_clk_groups[] = अणु
	"gpio56",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim2_data_groups[] = अणु
	"gpio55",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim2_present_groups[] = अणु
	"gpio58",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim2_reset_groups[] = अणु
	"gpio57",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uim_batt_groups[] = अणु
	"gpio49",
पूर्ण;

अटल स्थिर अक्षर * स्थिर us_emitter_groups[] = अणु
	"gpio68",
पूर्ण;

अटल स्थिर अक्षर * स्थिर us_euro_groups[] = अणु
	"gpio63",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wcss_bt_groups[] = अणु
	"gpio75", "gpio83", "gpio84",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wcss_fm_groups[] = अणु
	"gpio81", "gpio82",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wcss_wlan0_groups[] = अणु
	"gpio78",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wcss_wlan1_groups[] = अणु
	"gpio77",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wcss_wlan2_groups[] = अणु
	"gpio76",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wcss_wlan_groups[] = अणु
	"gpio79", "gpio80",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wsa_en_groups[] = अणु
	"gpio96",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wsa_io_groups[] = अणु
	"gpio94", "gpio95",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wsa_irq_groups[] = अणु
	"gpio97",
पूर्ण;

अटल स्थिर काष्ठा msm_function msm8953_functions[] = अणु
	FUNCTION(accel_पूर्णांक),
	FUNCTION(adsp_ext),
	FUNCTION(alsp_पूर्णांक),
	FUNCTION(atest_bbrx0),
	FUNCTION(atest_bbrx1),
	FUNCTION(atest_अक्षर),
	FUNCTION(atest_अक्षर0),
	FUNCTION(atest_अक्षर1),
	FUNCTION(atest_अक्षर2),
	FUNCTION(atest_अक्षर3),
	FUNCTION(atest_gpsadc_dtest0_native),
	FUNCTION(atest_gpsadc_dtest1_native),
	FUNCTION(atest_tsens),
	FUNCTION(atest_wlan0),
	FUNCTION(atest_wlan1),
	FUNCTION(bimc_dte0),
	FUNCTION(bimc_dte1),
	FUNCTION(blsp1_spi),
	FUNCTION(blsp3_spi),
	FUNCTION(blsp6_spi),
	FUNCTION(blsp7_spi),
	FUNCTION(blsp_i2c1),
	FUNCTION(blsp_i2c2),
	FUNCTION(blsp_i2c3),
	FUNCTION(blsp_i2c4),
	FUNCTION(blsp_i2c5),
	FUNCTION(blsp_i2c6),
	FUNCTION(blsp_i2c7),
	FUNCTION(blsp_i2c8),
	FUNCTION(blsp_spi1),
	FUNCTION(blsp_spi2),
	FUNCTION(blsp_spi3),
	FUNCTION(blsp_spi4),
	FUNCTION(blsp_spi5),
	FUNCTION(blsp_spi6),
	FUNCTION(blsp_spi7),
	FUNCTION(blsp_spi8),
	FUNCTION(blsp_uart2),
	FUNCTION(blsp_uart4),
	FUNCTION(blsp_uart5),
	FUNCTION(blsp_uart6),
	FUNCTION(cam0_lकरो),
	FUNCTION(cam1_lकरो),
	FUNCTION(cam1_rst),
	FUNCTION(cam1_standby),
	FUNCTION(cam2_rst),
	FUNCTION(cam2_standby),
	FUNCTION(cam3_rst),
	FUNCTION(cam3_standby),
	FUNCTION(cam_irq),
	FUNCTION(cam_mclk),
	FUNCTION(cap_पूर्णांक),
	FUNCTION(cci_async),
	FUNCTION(cci_i2c),
	FUNCTION(cci_समयr0),
	FUNCTION(cci_समयr1),
	FUNCTION(cci_समयr2),
	FUNCTION(cci_समयr3),
	FUNCTION(cci_समयr4),
	FUNCTION(cdc_pdm0),
	FUNCTION(codec_पूर्णांक1),
	FUNCTION(codec_पूर्णांक2),
	FUNCTION(codec_reset),
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
	FUNCTION(dac_calib3),
	FUNCTION(dac_calib4),
	FUNCTION(dac_calib5),
	FUNCTION(dac_calib6),
	FUNCTION(dac_calib7),
	FUNCTION(dac_calib8),
	FUNCTION(dac_calib9),
	FUNCTION(dbg_out),
	FUNCTION(ddr_bist),
	FUNCTION(dmic0_clk),
	FUNCTION(dmic0_data),
	FUNCTION(ebi_cdc),
	FUNCTION(ebi_ch0),
	FUNCTION(ext_lpass),
	FUNCTION(flash_strobe),
	FUNCTION(fp_पूर्णांक),
	FUNCTION(gcc_gp1_clk_a),
	FUNCTION(gcc_gp1_clk_b),
	FUNCTION(gcc_gp2_clk_a),
	FUNCTION(gcc_gp2_clk_b),
	FUNCTION(gcc_gp3_clk_a),
	FUNCTION(gcc_gp3_clk_b),
	FUNCTION(gcc_plltest),
	FUNCTION(gcc_tlmm),
	FUNCTION(gpio),
	FUNCTION(gsm0_tx),
	FUNCTION(gsm1_tx),
	FUNCTION(gyro_पूर्णांक),
	FUNCTION(hall_पूर्णांक),
	FUNCTION(hdmi_पूर्णांक),
	FUNCTION(key_focus),
	FUNCTION(key_home),
	FUNCTION(key_snapshot),
	FUNCTION(key_volp),
	FUNCTION(lकरो_en),
	FUNCTION(lकरो_update),
	FUNCTION(lpass_slimbus),
	FUNCTION(lpass_slimbus0),
	FUNCTION(lpass_slimbus1),
	FUNCTION(m_voc),
	FUNCTION(mag_पूर्णांक),
	FUNCTION(mdp_vsync),
	FUNCTION(mipi_dsi0),
	FUNCTION(modem_tsync),
	FUNCTION(mss_lte),
	FUNCTION(nav_pps),
	FUNCTION(nav_pps_in_a),
	FUNCTION(nav_pps_in_b),
	FUNCTION(nav_tsync),
	FUNCTION(nfc_disable),
	FUNCTION(nfc_dwl),
	FUNCTION(nfc_irq),
	FUNCTION(ois_sync),
	FUNCTION(pa_indicator),
	FUNCTION(pbs0),
	FUNCTION(pbs1),
	FUNCTION(pbs2),
	FUNCTION(pressure_पूर्णांक),
	FUNCTION(pri_mi2s),
	FUNCTION(pri_mi2s_mclk_a),
	FUNCTION(pri_mi2s_mclk_b),
	FUNCTION(pri_mi2s_ws),
	FUNCTION(prng_rosc),
	FUNCTION(pwr_crypto_enabled_a),
	FUNCTION(pwr_crypto_enabled_b),
	FUNCTION(pwr_करोwn),
	FUNCTION(pwr_modem_enabled_a),
	FUNCTION(pwr_modem_enabled_b),
	FUNCTION(pwr_nav_enabled_a),
	FUNCTION(pwr_nav_enabled_b),
	FUNCTION(qdss_cti_trig_in_a0),
	FUNCTION(qdss_cti_trig_in_a1),
	FUNCTION(qdss_cti_trig_in_b0),
	FUNCTION(qdss_cti_trig_in_b1),
	FUNCTION(qdss_cti_trig_out_a0),
	FUNCTION(qdss_cti_trig_out_a1),
	FUNCTION(qdss_cti_trig_out_b0),
	FUNCTION(qdss_cti_trig_out_b1),
	FUNCTION(qdss_traceclk_a),
	FUNCTION(qdss_traceclk_b),
	FUNCTION(qdss_tracectl_a),
	FUNCTION(qdss_tracectl_b),
	FUNCTION(qdss_tracedata_a),
	FUNCTION(qdss_tracedata_b),
	FUNCTION(sd_ग_लिखो),
	FUNCTION(sdcard_det),
	FUNCTION(sec_mi2s),
	FUNCTION(sec_mi2s_mclk_a),
	FUNCTION(sec_mi2s_mclk_b),
	FUNCTION(smb_पूर्णांक),
	FUNCTION(ss_चयन),
	FUNCTION(ssbi_wtr1),
	FUNCTION(ts_resout),
	FUNCTION(ts_sample),
	FUNCTION(ts_xvdd),
	FUNCTION(tsens_max),
	FUNCTION(uim1_clk),
	FUNCTION(uim1_data),
	FUNCTION(uim1_present),
	FUNCTION(uim1_reset),
	FUNCTION(uim2_clk),
	FUNCTION(uim2_data),
	FUNCTION(uim2_present),
	FUNCTION(uim2_reset),
	FUNCTION(uim_batt),
	FUNCTION(us_emitter),
	FUNCTION(us_euro),
	FUNCTION(wcss_bt),
	FUNCTION(wcss_fm),
	FUNCTION(wcss_wlan),
	FUNCTION(wcss_wlan0),
	FUNCTION(wcss_wlan1),
	FUNCTION(wcss_wlan2),
	FUNCTION(wsa_en),
	FUNCTION(wsa_io),
	FUNCTION(wsa_irq),
पूर्ण;

अटल स्थिर काष्ठा msm_pingroup msm8953_groups[] = अणु
	PINGROUP(0, blsp_spi1, _, _, _, _, _, _, _, _),
	PINGROUP(1, blsp_spi1, adsp_ext, _, _, _, _, _, _, _),
	PINGROUP(2, blsp_spi1, blsp_i2c1, prng_rosc, _, _, _, qdss_cti_trig_out_b0, _, _),
	PINGROUP(3, blsp_spi1, blsp_i2c1, _, _, _, qdss_cti_trig_out_a1, _, _, _),
	PINGROUP(4, blsp_spi2, blsp_uart2, lकरो_update, _, dac_calib0, _, _, _, _),
	PINGROUP(5, blsp_spi2, blsp_uart2, lकरो_en, _, _, _, _, _, _),
	PINGROUP(6, blsp_spi2, blsp_uart2, blsp_i2c2, gcc_gp1_clk_b, _, _, _, _, _),
	PINGROUP(7, blsp_spi2, blsp_uart2, blsp_i2c2, _, atest_gpsadc_dtest0_native, _, _, _, _),
	PINGROUP(8, blsp_spi3, _, _, qdss_tracedata_b, _, _, _, _, _),
	PINGROUP(9, blsp_spi3, pwr_modem_enabled_b, _, _, qdss_tracedata_b, _, _, _, _),
	PINGROUP(10, blsp_spi3, blsp_i2c3, gcc_gp2_clk_b, _, _, _, _, _, _),
	PINGROUP(11, blsp_spi3, blsp_i2c3, gcc_gp3_clk_b, _, _, _, _, _, _),
	PINGROUP(12, blsp_spi4, blsp_uart4, pwr_nav_enabled_b, _, _,
		 qdss_tracedata_b, _, dac_calib1, _),
	PINGROUP(13, blsp_spi4, blsp_uart4, pwr_crypto_enabled_b, _, _, _,
		 qdss_tracedata_b, _, dac_calib2),
	PINGROUP(14, blsp_spi4, blsp_uart4, blsp_i2c4, _, _, _, _, _, _),
	PINGROUP(15, blsp_spi4, blsp_uart4, blsp_i2c4, _, _, _, _, _, _),
	PINGROUP(16, blsp_spi5, blsp_uart5, _, _, qdss_traceclk_a, _, atest_bbrx1, _, _),
	PINGROUP(17, blsp_spi5, blsp_uart5, m_voc, qdss_cti_trig_in_a0, _, atest_bbrx0, _, _, _),
	PINGROUP(18, blsp_spi5, blsp_uart5, blsp_i2c5,
		 qdss_tracectl_a, _, atest_gpsadc_dtest1_native, _, _, _),
	PINGROUP(19, blsp_spi5, blsp_uart5, blsp_i2c5, qdss_tracedata_a, _, _, _, _, _),
	PINGROUP(20, blsp_spi6, blsp_uart6, _, _, _, qdss_tracectl_b, _, dac_calib15, _),
	PINGROUP(21, blsp_spi6, blsp_uart6, m_voc, _, _, _, qdss_cti_trig_in_b0, _, dac_calib16),
	PINGROUP(22, blsp_spi6, blsp_uart6, blsp_i2c6, qdss_traceclk_b, _, atest_wlan0, _, _, _),
	PINGROUP(23, blsp_spi6, blsp_uart6, blsp_i2c6, qdss_tracedata_b, _, atest_wlan1, _, _, _),
	PINGROUP(24, mdp_vsync, _, _, _, _, _, _, _, _),
	PINGROUP(25, mdp_vsync, pri_mi2s_mclk_a, sec_mi2s_mclk_a,
		 qdss_cti_trig_out_b1, _, _, _, _, _),
	PINGROUP(26, cam_mclk, _, _, _, qdss_tracedata_a, _, _, _, _),
	PINGROUP(27, cam_mclk, _, _, _, qdss_tracedata_a, _, _, _, _),
	PINGROUP(28, cam_mclk, _, _, _, qdss_tracedata_a, _, dac_calib3, _, _),
	PINGROUP(29, cci_i2c, pwr_modem_enabled_a, _, _, _, qdss_tracedata_a, _, dac_calib4, _),
	PINGROUP(30, cci_i2c, _, _, _, qdss_tracedata_a, _, dac_calib19, _, _),
	PINGROUP(31, cci_i2c, _, _, _, qdss_tracedata_a, _, _, _, _),
	PINGROUP(32, cci_i2c, _, _, _, qdss_tracedata_a, _, _, _, _),
	PINGROUP(33, cci_समयr0, _, _, _, _, qdss_tracedata_a, _, _, _),
	PINGROUP(34, cci_समयr1, _, _, _, _, qdss_tracedata_a, _, _, _),
	PINGROUP(35, cci_समयr2, blsp1_spi, pwr_nav_enabled_a, _, _, _, qdss_tracedata_a, _, _),
	PINGROUP(36, cci_समयr3, blsp1_spi, _, pwr_crypto_enabled_a, _, _, _, qdss_tracedata_a, _),
	PINGROUP(37, _, _, _, _, _, _, _, _, _),
	PINGROUP(38, cci_async, _, qdss_tracedata_a, _, _, _, _, _, _),
	PINGROUP(39, _, _, _, qdss_tracedata_a, _, dac_calib5, _, _, _),
	PINGROUP(40, _, _, qdss_tracedata_a, _, dac_calib6, _, _, _, _),
	PINGROUP(41, cci_समयr4, blsp3_spi, gcc_gp1_clk_b, _, _,
		 qdss_cti_trig_out_a0, _, dac_calib7, _),
	PINGROUP(42, gcc_gp1_clk_a, qdss_tracedata_b, _, dac_calib8, _, _, _, _, _),
	PINGROUP(43, gcc_gp2_clk_a, qdss_tracedata_b, _, dac_calib9, _, _, _, _, _),
	PINGROUP(44, gcc_gp3_clk_a, qdss_tracedata_b, _, dac_calib10, _, _, _, _, _),
	PINGROUP(45, _, qdss_tracedata_b, _, dac_calib11, _, _, _, _, _),
	PINGROUP(46, qdss_tracedata_b, _, dac_calib12, _, _, _, _, _, _),
	PINGROUP(47, blsp6_spi, qdss_tracedata_b, _, dac_calib13, _, _, _, _, _),
	PINGROUP(48, blsp6_spi, _, qdss_cti_trig_in_b1, _, dac_calib14, _, _, _, _),
	PINGROUP(49, uim_batt, _, _, _, _, _, _, _, _),
	PINGROUP(50, blsp3_spi, sd_ग_लिखो, _, _, _, qdss_tracedata_a, _, _, _),
	PINGROUP(51, uim1_data, _, _, _, _, _, _, _, _),
	PINGROUP(52, uim1_clk, _, _, _, _, _, _, _, _),
	PINGROUP(53, uim1_reset, _, _, _, _, _, _, _, _),
	PINGROUP(54, uim1_present, _, _, _, _, _, _, _, _),
	PINGROUP(55, uim2_data, _, _, _, _, _, _, _, _),
	PINGROUP(56, uim2_clk, _, _, _, _, _, _, _, _),
	PINGROUP(57, uim2_reset, _, _, _, _, _, _, _, _),
	PINGROUP(58, uim2_present, _, _, _, _, _, _, _, _),
	PINGROUP(59, _, _, _, _, _, _, _, _, _),
	PINGROUP(60, _, _, _, _, _, _, _, _, _),
	PINGROUP(61, _, _, _, _, _, _, _, _, _),
	PINGROUP(62, _, _, _, _, _, _, _, _, _),
	PINGROUP(63, atest_अक्षर3, dbg_out, bimc_dte0, _, _, _, _, _, _),
	PINGROUP(64, _, _, _, _, _, _, _, _, _),
	PINGROUP(65, bimc_dte0, _, _, _, _, _, _, _, _),
	PINGROUP(66, sec_mi2s_mclk_b, pri_mi2s, _, qdss_tracedata_b, _, _, _, _, _),
	PINGROUP(67, cdc_pdm0, atest_अक्षर1, ebi_cdc, _, dac_calib17, _, _, _, _),
	PINGROUP(68, cdc_pdm0, atest_अक्षर0, _, _, _, _, _, _, _),
	PINGROUP(69, cdc_pdm0, pri_mi2s_mclk_b, ebi_cdc, _, _, _, _, _, _),
	PINGROUP(70, lpass_slimbus, cdc_pdm0, _, _, _, _, _, _, _),
	PINGROUP(71, lpass_slimbus0, cdc_pdm0, _, _, _, _, _, _, _),
	PINGROUP(72, lpass_slimbus1, cdc_pdm0, _, _, _, _, _, _, _),
	PINGROUP(73, cdc_pdm0, _, _, _, _, _, _, _, _),
	PINGROUP(74, cdc_pdm0, _, _, _, _, _, _, _, _),
	PINGROUP(75, wcss_bt, atest_अक्षर2, _, ebi_ch0, _, _, _, _, _),
	PINGROUP(76, wcss_wlan2, _, _, _, _, _, _, _, _),
	PINGROUP(77, wcss_wlan1, _, _, _, _, _, _, _, _),
	PINGROUP(78, wcss_wlan0, _, _, _, _, _, _, _, _),
	PINGROUP(79, wcss_wlan, _, _, _, _, _, _, _, _),
	PINGROUP(80, wcss_wlan, _, _, _, _, _, _, _, _),
	PINGROUP(81, wcss_fm, ext_lpass, _, _, _, _, _, _, _),
	PINGROUP(82, wcss_fm, mss_lte, _, _, _, _, _, _, _),
	PINGROUP(83, wcss_bt, mss_lte, _, _, _, _, _, _, _),
	PINGROUP(84, wcss_bt, _, _, _, _, _, _, _, _),
	PINGROUP(85, pbs0, cri_trng0, _, _, _, _, _, _, _),
	PINGROUP(86, pbs1, cri_trng1, qdss_tracedata_b, _, _, _, _, _, _),
	PINGROUP(87, pbs2, cri_trng, qdss_tracedata_b, gcc_tlmm, _, _, _, _, _),
	PINGROUP(88, pri_mi2s, _, _, _, qdss_tracedata_b, _, _, _, _),
	PINGROUP(89, dmic0_clk, blsp7_spi, _, _, _, _, _, _, _),
	PINGROUP(90, dmic0_data, blsp7_spi, _, _, _, _, _, _, _),
	PINGROUP(91, pri_mi2s, _, _, _, qdss_cti_trig_in_a1, _, _, _, _),
	PINGROUP(92, pri_mi2s_ws, _, _, _, qdss_tracedata_b, _, _, _, _),
	PINGROUP(93, pri_mi2s, _, _, _, _, _, _, _, _),
	PINGROUP(94, wsa_io, pri_mi2s, _, _, _, _, _, _, _),
	PINGROUP(95, wsa_io, pri_mi2s, _, _, _, _, _, _, _),
	PINGROUP(96, blsp_spi8, _, _, _, _, _, _, _, _),
	PINGROUP(97, blsp_spi8, _, _, _, _, _, _, _, _),
	PINGROUP(98, blsp_i2c8, blsp_spi8, gcc_plltest, _, _, _, _, _, _),
	PINGROUP(99, blsp_i2c8, blsp_spi8, gcc_plltest, _, _, _, _, _, _),
	PINGROUP(100, _, _, _, _, _, _, _, _, _),
	PINGROUP(101, _, _, _, _, _, _, _, _, _),
	PINGROUP(102, _, _, _, _, _, _, _, _, _),
	PINGROUP(103, _, _, _, _, _, _, _, _, _),
	PINGROUP(104, _, _, _, _, _, _, _, _, _),
	PINGROUP(105, _, _, _, _, _, _, _, _, _),
	PINGROUP(106, _, _, _, _, _, _, _, _, _),
	PINGROUP(107, _, _, _, _, _, _, _, _, _),
	PINGROUP(108, _, _, _, _, _, _, _, _, _),
	PINGROUP(109, _, _, _, _, _, _, _, _, _),
	PINGROUP(110, _, _, _, _, _, _, _, _, _),
	PINGROUP(111, _, _, nav_pps_in_a, _, _, _, _, _, _),
	PINGROUP(112, _, pa_indicator, _, _, _, _, _, _, _),
	PINGROUP(113, _, nav_pps_in_b, nav_pps, modem_tsync, nav_tsync, _, _, _, _),
	PINGROUP(114, _, ssbi_wtr1, _, _, _, _, _, _, _),
	PINGROUP(115, _, gsm1_tx, _, dac_calib18, _, _, _, _, _),
	PINGROUP(116, _, _, _, _, _, _, _, _, _),
	PINGROUP(117, gsm0_tx, _, _, _, _, _, _, _, _),
	PINGROUP(118, _, ebi_cdc, _, _, _, _, _, _, _),
	PINGROUP(119, _, ebi_cdc, _, _, _, _, _, _, _),
	PINGROUP(120, _, atest_अक्षर, ebi_cdc, _, atest_tsens, _, _, _, _),
	PINGROUP(121, _, _, _, bimc_dte1, _, _, _, _, _),
	PINGROUP(122, _, _, _, bimc_dte1, _, _, _, _, _),
	PINGROUP(123, _, ssbi_wtr1, ebi_cdc, _, _, _, _, _, _),
	PINGROUP(124, _, _, _, _, _, _, _, _, _),
	PINGROUP(125, _, _, _, _, _, _, _, _, _),
	PINGROUP(126, _, _, _, _, _, _, _, _, _),
	PINGROUP(127, _, _, _, _, _, _, _, _, _),
	PINGROUP(128, cam_mclk, _, dac_calib20, _, _, _, _, _, _),
	PINGROUP(129, ddr_bist, _, dac_calib21, _, _, _, _, _, _),
	PINGROUP(130, ddr_bist, _, dac_calib22, _, _, _, _, _, _),
	PINGROUP(131, ddr_bist, _, dac_calib23, _, _, _, _, _, _),
	PINGROUP(132, ddr_bist, _, dac_calib24, _, _, _, _, _, _),
	PINGROUP(133, _, dac_calib25, _, _, _, _, _, _, _),
	PINGROUP(134, _, _, _, _, _, _, _, _, _),
	PINGROUP(135, sec_mi2s, blsp_spi7, blsp_i2c7, _, _, _, _, _, _),
	PINGROUP(136, sec_mi2s, blsp_spi7, blsp_i2c7, _, _, _, _, _, _),
	PINGROUP(137, sec_mi2s, blsp_spi7, _, _, _, _, _, _, _),
	PINGROUP(138, sec_mi2s, blsp_spi7, _, _, _, _, _, _, _),
	PINGROUP(139, tsens_max, _, _, _, _, _, _, _, _),
	PINGROUP(140, _, _, _, _, _, _, _, _, _),
	PINGROUP(141, _, _, _, _, _, _, _, _, _),
	SDC_QDSD_PINGROUP(qdsd_clk, 0x19c000, 3, 0),
	SDC_QDSD_PINGROUP(qdsd_cmd, 0x19c000, 8, 5),
	SDC_QDSD_PINGROUP(qdsd_data0, 0x19c000, 13, 10),
	SDC_QDSD_PINGROUP(qdsd_data1, 0x19c000, 18, 15),
	SDC_QDSD_PINGROUP(qdsd_data2, 0x19c000, 23, 20),
	SDC_QDSD_PINGROUP(qdsd_data3, 0x19c000, 28, 25),
	SDC_QDSD_PINGROUP(sdc1_clk, 0x10a000, 13, 6),
	SDC_QDSD_PINGROUP(sdc1_cmd, 0x10a000, 11, 3),
	SDC_QDSD_PINGROUP(sdc1_data, 0x10a000, 9, 0),
	SDC_QDSD_PINGROUP(sdc1_rclk, 0x10a000, 15, 0),
	SDC_QDSD_PINGROUP(sdc2_clk, 0x109000, 14, 6),
	SDC_QDSD_PINGROUP(sdc2_cmd, 0x109000, 11, 3),
	SDC_QDSD_PINGROUP(sdc2_data, 0x109000, 9, 0),
पूर्ण;

अटल स्थिर काष्ठा msm_pinctrl_soc_data msm8953_pinctrl = अणु
	.pins = msm8953_pins,
	.npins = ARRAY_SIZE(msm8953_pins),
	.functions = msm8953_functions,
	.nfunctions = ARRAY_SIZE(msm8953_functions),
	.groups = msm8953_groups,
	.ngroups = ARRAY_SIZE(msm8953_groups),
	.ngpios = 142,
पूर्ण;

अटल पूर्णांक msm8953_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस msm_pinctrl_probe(pdev, &msm8953_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id msm8953_pinctrl_of_match[] = अणु
	अणु .compatible = "qcom,msm8953-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver msm8953_pinctrl_driver = अणु
	.driver = अणु
		.name = "msm8953-pinctrl",
		.of_match_table = msm8953_pinctrl_of_match,
	पूर्ण,
	.probe = msm8953_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init msm8953_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&msm8953_pinctrl_driver);
पूर्ण
arch_initcall(msm8953_pinctrl_init);

अटल व्योम __निकास msm8953_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&msm8953_pinctrl_driver);
पूर्ण
module_निकास(msm8953_pinctrl_निकास);

MODULE_DESCRIPTION("QTI msm8953 pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, msm8953_pinctrl_of_match);
