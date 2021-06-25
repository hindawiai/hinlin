<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-msm.h"

#घोषणा FUNCTION(fname)					\
	[msm_mux_##fname] = अणु				\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

#घोषणा NORTH	0x00500000
#घोषणा SOUTH	0x00900000
#घोषणा EAST	0x00100000
#घोषणा REG_SIZE 0x1000
#घोषणा PINGROUP(id, base, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10)	\
	अणु						\
		.name = "gpio" #id,			\
		.pins = gpio##id##_pins,		\
		.npins = ARRAY_SIZE(gpio##id##_pins),	\
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
			msm_mux_##f9,			\
			msm_mux_##f10			\
		पूर्ण,					\
		.nfuncs = 11,				\
		.ctl_reg = base + REG_SIZE * id,		\
		.io_reg = base + 0x4 + REG_SIZE * id,		\
		.पूर्णांकr_cfg_reg = base + 0x8 + REG_SIZE * id,	\
		.पूर्णांकr_status_reg = base + 0xc + REG_SIZE * id,	\
		.पूर्णांकr_target_reg = base + 0x8 + REG_SIZE * id,	\
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
	अणु						\
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

#घोषणा UFS_RESET(pg_name, offset)				\
	अणु						\
		.name = #pg_name,			\
		.pins = pg_name##_pins,			\
		.npins = ARRAY_SIZE(pg_name##_pins),	\
		.ctl_reg = offset,			\
		.io_reg = offset + 0x4,			\
		.पूर्णांकr_cfg_reg = 0,			\
		.पूर्णांकr_status_reg = 0,			\
		.पूर्णांकr_target_reg = 0,			\
		.mux_bit = -1,				\
		.pull_bit = 3,				\
		.drv_bit = 0,				\
		.oe_bit = -1,				\
		.in_bit = -1,				\
		.out_bit = 0,				\
		.पूर्णांकr_enable_bit = -1,			\
		.पूर्णांकr_status_bit = -1,			\
		.पूर्णांकr_target_bit = -1,			\
		.पूर्णांकr_raw_status_bit = -1,		\
		.पूर्णांकr_polarity_bit = -1,		\
		.पूर्णांकr_detection_bit = -1,		\
		.पूर्णांकr_detection_width = -1,		\
	पूर्ण
अटल स्थिर काष्ठा pinctrl_pin_desc sdm845_pins[] = अणु
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
	PINCTRL_PIN(150, "UFS_RESET"),
	PINCTRL_PIN(151, "SDC2_CLK"),
	PINCTRL_PIN(152, "SDC2_CMD"),
	PINCTRL_PIN(153, "SDC2_DATA"),
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

अटल स्थिर अचिन्हित पूर्णांक ufs_reset_pins[] = अणु 150 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_clk_pins[] = अणु 151 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_cmd_pins[] = अणु 152 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_data_pins[] = अणु 153 पूर्ण;

क्रमागत sdm845_functions अणु
	msm_mux_gpio,
	msm_mux_adsp_ext,
	msm_mux_agera_pll,
	msm_mux_atest_अक्षर,
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
	msm_mux_dbg_out,
	msm_mux_ddr_bist,
	msm_mux_ddr_pxi0,
	msm_mux_ddr_pxi1,
	msm_mux_ddr_pxi2,
	msm_mux_ddr_pxi3,
	msm_mux_edp_hot,
	msm_mux_edp_lcd,
	msm_mux_gcc_gp1,
	msm_mux_gcc_gp2,
	msm_mux_gcc_gp3,
	msm_mux_jitter_bist,
	msm_mux_lकरो_en,
	msm_mux_lकरो_update,
	msm_mux_lpass_slimbus,
	msm_mux_m_voc,
	msm_mux_mdp_vsync,
	msm_mux_mdp_vsync0,
	msm_mux_mdp_vsync1,
	msm_mux_mdp_vsync2,
	msm_mux_mdp_vsync3,
	msm_mux_mss_lte,
	msm_mux_nav_pps,
	msm_mux_pa_indicator,
	msm_mux_pci_e0,
	msm_mux_pci_e1,
	msm_mux_phase_flag,
	msm_mux_pll_bist,
	msm_mux_pll_bypassnl,
	msm_mux_pll_reset,
	msm_mux_pri_mi2s,
	msm_mux_pri_mi2s_ws,
	msm_mux_prng_rosc,
	msm_mux_qdss_cti,
	msm_mux_qdss,
	msm_mux_qlink_enable,
	msm_mux_qlink_request,
	msm_mux_qspi_clk,
	msm_mux_qspi_cs,
	msm_mux_qspi_data,
	msm_mux_qua_mi2s,
	msm_mux_qup0,
	msm_mux_qup1,
	msm_mux_qup10,
	msm_mux_qup11,
	msm_mux_qup12,
	msm_mux_qup13,
	msm_mux_qup14,
	msm_mux_qup15,
	msm_mux_qup2,
	msm_mux_qup3,
	msm_mux_qup4,
	msm_mux_qup5,
	msm_mux_qup6,
	msm_mux_qup7,
	msm_mux_qup8,
	msm_mux_qup9,
	msm_mux_qup_l4,
	msm_mux_qup_l5,
	msm_mux_qup_l6,
	msm_mux_sd_ग_लिखो,
	msm_mux_sdc4_clk,
	msm_mux_sdc4_cmd,
	msm_mux_sdc4_data,
	msm_mux_sec_mi2s,
	msm_mux_sp_cmu,
	msm_mux_spkr_i2s,
	msm_mux_ter_mi2s,
	msm_mux_tgu_ch0,
	msm_mux_tgu_ch1,
	msm_mux_tgu_ch2,
	msm_mux_tgu_ch3,
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
	msm_mux_uim1_clk,
	msm_mux_uim1_data,
	msm_mux_uim1_present,
	msm_mux_uim1_reset,
	msm_mux_uim2_clk,
	msm_mux_uim2_data,
	msm_mux_uim2_present,
	msm_mux_uim2_reset,
	msm_mux_uim_batt,
	msm_mux_usb_phy,
	msm_mux_vfr_1,
	msm_mux_vsense_trigger,
	msm_mux_wlan1_adc0,
	msm_mux_wlan1_adc1,
	msm_mux_wlan2_adc0,
	msm_mux_wlan2_adc1,
	msm_mux__,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ddr_pxi3_groups[] = अणु
	"gpio12", "gpio13",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cam_mclk_groups[] = अणु
	"gpio13", "gpio14", "gpio15", "gpio16",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_bypassnl_groups[] = अणु
	"gpio13",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_groups[] = अणु
	"gpio13", "gpio14", "gpio15", "gpio16", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio21", "gpio22", "gpio23", "gpio24", "gpio25", "gpio26",
	"gpio27", "gpio28", "gpio29", "gpio30", "gpio41", "gpio42", "gpio43",
	"gpio44", "gpio75", "gpio76", "gpio77", "gpio79", "gpio80", "gpio93",
	"gpio117", "gpio118", "gpio119", "gpio120", "gpio121", "gpio122",
	"gpio123", "gpio124",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_reset_groups[] = अणु
	"gpio14",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_i2c_groups[] = अणु
	"gpio17", "gpio18", "gpio19", "gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup1_groups[] = अणु
	"gpio17", "gpio18", "gpio19", "gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr0_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp2_groups[] = अणु
	"gpio21", "gpio58",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr1_groups[] = अणु
	"gpio22",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp3_groups[] = अणु
	"gpio22", "gpio59",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr2_groups[] = अणु
	"gpio23",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr3_groups[] = अणु
	"gpio24",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_async_groups[] = अणु
	"gpio24", "gpio25", "gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr4_groups[] = अणु
	"gpio25",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup2_groups[] = अणु
	"gpio27", "gpio28", "gpio29", "gpio30",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag_groups[] = अणु
	"gpio29", "gpio30", "gpio52", "gpio53", "gpio54", "gpio55", "gpio56",
	"gpio57", "gpio58", "gpio59", "gpio60", "gpio61", "gpio62", "gpio63",
	"gpio64", "gpio74", "gpio75", "gpio76", "gpio77", "gpio89", "gpio90",
	"gpio96", "gpio99", "gpio100", "gpio103", "gpio137", "gpio138",
	"gpio139", "gpio140", "gpio141", "gpio142", "gpio143",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup11_groups[] = अणु
	"gpio31", "gpio32", "gpio33", "gpio34",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup14_groups[] = अणु
	"gpio31", "gpio32", "gpio33", "gpio34",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pci_e0_groups[] = अणु
	"gpio35", "gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर jitter_bist_groups[] = अणु
	"gpio35",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_bist_groups[] = अणु
	"gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens_groups[] = अणु
	"gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर agera_pll_groups[] = अणु
	"gpio37",
पूर्ण;
अटल स्थिर अक्षर * स्थिर usb_phy_groups[] = अणु
	"gpio38",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lpass_slimbus_groups[] = अणु
	"gpio39", "gpio70", "gpio71", "gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sd_ग_लिखो_groups[] = अणु
	"gpio40",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_error_groups[] = अणु
	"gpio40",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup3_groups[] = अणु
	"gpio41", "gpio42", "gpio43", "gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup6_groups[] = अणु
	"gpio45", "gpio46", "gpio47", "gpio48",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup12_groups[] = अणु
	"gpio49", "gpio50", "gpio51", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup10_groups[] = अणु
	"gpio53", "gpio54", "gpio55", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qua_mi2s_groups[] = अणु
	"gpio57", "gpio58", "gpio59", "gpio60", "gpio61", "gpio62", "gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp1_groups[] = अणु
	"gpio57", "gpio78",
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
अटल स्थिर अक्षर * स्थिर pri_mi2s_groups[] = अणु
	"gpio64", "gpio65", "gpio67", "gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sp_cmu_groups[] = अणु
	"gpio64",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup8_groups[] = अणु
	"gpio65", "gpio66", "gpio67", "gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pri_mi2s_ws_groups[] = अणु
	"gpio66",
पूर्ण;
अटल स्थिर अक्षर * स्थिर spkr_i2s_groups[] = अणु
	"gpio69", "gpio70", "gpio71", "gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर audio_ref_groups[] = अणु
	"gpio69",
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
अटल स्थिर अक्षर * स्थिर atest_usb2_groups[] = अणु
	"gpio73",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ter_mi2s_groups[] = अणु
	"gpio74", "gpio75", "gpio76", "gpio77", "gpio78",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb23_groups[] = अणु
	"gpio74",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb22_groups[] = अणु
	"gpio75",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb21_groups[] = अणु
	"gpio76",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb20_groups[] = अणु
	"gpio77",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sec_mi2s_groups[] = अणु
	"gpio79", "gpio80", "gpio81", "gpio82", "gpio83",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup15_groups[] = अणु
	"gpio81", "gpio82", "gpio83", "gpio84",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup5_groups[] = अणु
	"gpio85", "gpio86", "gpio87", "gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_clk_groups[] = अणु
	"gpio89",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup4_groups[] = अणु
	"gpio89", "gpio90", "gpio91", "gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_cs_groups[] = अणु
	"gpio89", "gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch3_groups[] = अणु
	"gpio89",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_en_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync0_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync1_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync2_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync3_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch0_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_data_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc4_cmd_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_data_groups[] = अणु
	"gpio91", "gpio92", "gpio93", "gpio94",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch1_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_error_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc4_data_groups[] = अणु
	"gpio92",
	"gpio94",
	"gpio95",
	"gpio96",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vfr_1_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch2_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_clk_groups[] = अणु
	"gpio93",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc4_clk_groups[] = अणु
	"gpio93",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup7_groups[] = अणु
	"gpio93", "gpio94", "gpio95", "gpio96",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_en_groups[] = अणु
	"gpio94",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_data_groups[] = अणु
	"gpio95",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_clk_groups[] = अणु
	"gpio95",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर2_sync_groups[] = अणु
	"gpio96",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_en_groups[] = अणु
	"gpio97",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_update_groups[] = अणु
	"gpio98",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pci_e1_groups[] = अणु
	"gpio102", "gpio103",
पूर्ण;
अटल स्थिर अक्षर * स्थिर prng_rosc_groups[] = अणु
	"gpio102",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_data_groups[] = अणु
	"gpio105",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup13_groups[] = अणु
	"gpio105", "gpio106", "gpio107", "gpio108",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_clk_groups[] = अणु
	"gpio106",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_reset_groups[] = अणु
	"gpio107",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_present_groups[] = अणु
	"gpio108",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_data_groups[] = अणु
	"gpio109",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_clk_groups[] = अणु
	"gpio110",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_reset_groups[] = अणु
	"gpio111",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_present_groups[] = अणु
	"gpio112",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim_batt_groups[] = अणु
	"gpio113",
पूर्ण;
अटल स्थिर अक्षर * स्थिर edp_hot_groups[] = अणु
	"gpio113",
पूर्ण;
अटल स्थिर अक्षर * स्थिर nav_pps_groups[] = अणु
	"gpio114", "gpio114", "gpio115", "gpio115", "gpio128", "gpio128",
	"gpio129", "gpio129", "gpio143", "gpio143",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर_groups[] = अणु
	"gpio117", "gpio118", "gpio119", "gpio120", "gpio121",
पूर्ण;
अटल स्थिर अक्षर * स्थिर adsp_ext_groups[] = अणु
	"gpio118",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qlink_request_groups[] = अणु
	"gpio130",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qlink_enable_groups[] = अणु
	"gpio131",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pa_indicator_groups[] = अणु
	"gpio135",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mss_lte_groups[] = अणु
	"gpio144", "gpio145",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup0_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3",
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
	"gpio147", "gpio148", "gpio149",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup9_groups[] = अणु
	"gpio4", "gpio5", "gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti_groups[] = अणु
	"gpio4", "gpio5", "gpio51", "gpio52", "gpio62", "gpio63", "gpio90",
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_pxi0_groups[] = अणु
	"gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_bist_groups[] = अणु
	"gpio7", "gpio8", "gpio9", "gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens2_groups[] = अणु
	"gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vsense_trigger_groups[] = अणु
	"gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb1_groups[] = अणु
	"gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup_l4_groups[] = अणु
	"gpio8", "gpio35", "gpio105", "gpio123",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan1_adc1_groups[] = अणु
	"gpio8",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb13_groups[] = अणु
	"gpio8",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_pxi1_groups[] = अणु
	"gpio8", "gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup_l5_groups[] = अणु
	"gpio9", "gpio36", "gpio106", "gpio124",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan1_adc0_groups[] = अणु
	"gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb12_groups[] = अणु
	"gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync_groups[] = अणु
	"gpio10", "gpio11", "gpio12", "gpio97", "gpio98",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup_l6_groups[] = अणु
	"gpio10", "gpio37", "gpio107", "gpio125",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan2_adc1_groups[] = अणु
	"gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb11_groups[] = अणु
	"gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_pxi2_groups[] = अणु
	"gpio10", "gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर edp_lcd_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dbg_out_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan2_adc0_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb10_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर m_voc_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsअगर1_sync_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर काष्ठा msm_function sdm845_functions[] = अणु
	FUNCTION(gpio),
	FUNCTION(adsp_ext),
	FUNCTION(agera_pll),
	FUNCTION(atest_अक्षर),
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
	FUNCTION(dbg_out),
	FUNCTION(ddr_bist),
	FUNCTION(ddr_pxi0),
	FUNCTION(ddr_pxi1),
	FUNCTION(ddr_pxi2),
	FUNCTION(ddr_pxi3),
	FUNCTION(edp_hot),
	FUNCTION(edp_lcd),
	FUNCTION(gcc_gp1),
	FUNCTION(gcc_gp2),
	FUNCTION(gcc_gp3),
	FUNCTION(jitter_bist),
	FUNCTION(lकरो_en),
	FUNCTION(lकरो_update),
	FUNCTION(lpass_slimbus),
	FUNCTION(m_voc),
	FUNCTION(mdp_vsync),
	FUNCTION(mdp_vsync0),
	FUNCTION(mdp_vsync1),
	FUNCTION(mdp_vsync2),
	FUNCTION(mdp_vsync3),
	FUNCTION(mss_lte),
	FUNCTION(nav_pps),
	FUNCTION(pa_indicator),
	FUNCTION(pci_e0),
	FUNCTION(pci_e1),
	FUNCTION(phase_flag),
	FUNCTION(pll_bist),
	FUNCTION(pll_bypassnl),
	FUNCTION(pll_reset),
	FUNCTION(pri_mi2s),
	FUNCTION(pri_mi2s_ws),
	FUNCTION(prng_rosc),
	FUNCTION(qdss_cti),
	FUNCTION(qdss),
	FUNCTION(qlink_enable),
	FUNCTION(qlink_request),
	FUNCTION(qspi_clk),
	FUNCTION(qspi_cs),
	FUNCTION(qspi_data),
	FUNCTION(qua_mi2s),
	FUNCTION(qup0),
	FUNCTION(qup1),
	FUNCTION(qup10),
	FUNCTION(qup11),
	FUNCTION(qup12),
	FUNCTION(qup13),
	FUNCTION(qup14),
	FUNCTION(qup15),
	FUNCTION(qup2),
	FUNCTION(qup3),
	FUNCTION(qup4),
	FUNCTION(qup5),
	FUNCTION(qup6),
	FUNCTION(qup7),
	FUNCTION(qup8),
	FUNCTION(qup9),
	FUNCTION(qup_l4),
	FUNCTION(qup_l5),
	FUNCTION(qup_l6),
	FUNCTION(sd_ग_लिखो),
	FUNCTION(sdc4_clk),
	FUNCTION(sdc4_cmd),
	FUNCTION(sdc4_data),
	FUNCTION(sec_mi2s),
	FUNCTION(sp_cmu),
	FUNCTION(spkr_i2s),
	FUNCTION(ter_mi2s),
	FUNCTION(tgu_ch0),
	FUNCTION(tgu_ch1),
	FUNCTION(tgu_ch2),
	FUNCTION(tgu_ch3),
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
	FUNCTION(uim1_clk),
	FUNCTION(uim1_data),
	FUNCTION(uim1_present),
	FUNCTION(uim1_reset),
	FUNCTION(uim2_clk),
	FUNCTION(uim2_data),
	FUNCTION(uim2_present),
	FUNCTION(uim2_reset),
	FUNCTION(uim_batt),
	FUNCTION(usb_phy),
	FUNCTION(vfr_1),
	FUNCTION(vsense_trigger),
	FUNCTION(wlan1_adc0),
	FUNCTION(wlan1_adc1),
	FUNCTION(wlan2_adc0),
	FUNCTION(wlan2_adc1),
पूर्ण;

/* Every pin is मुख्यtained as a single group, and missing or non-existing pin
 * would be मुख्यtained as dummy group to synchronize pin group index with
 * pin descriptor रेजिस्टरed with pinctrl core.
 * Clients would not be able to request these dummy pin groups.
 */
अटल स्थिर काष्ठा msm_pingroup sdm845_groups[] = अणु
	PINGROUP(0, EAST, qup0, _, _, _, _, _, _, _, _, _),
	PINGROUP(1, EAST, qup0, _, _, _, _, _, _, _, _, _),
	PINGROUP(2, EAST, qup0, _, _, _, _, _, _, _, _, _),
	PINGROUP(3, EAST, qup0, _, _, _, _, _, _, _, _, _),
	PINGROUP(4, NORTH, qup9, qdss_cti, _, _, _, _, _, _, _, _),
	PINGROUP(5, NORTH, qup9, qdss_cti, _, _, _, _, _, _, _, _),
	PINGROUP(6, NORTH, qup9, _, ddr_pxi0, _, _, _, _, _, _, _),
	PINGROUP(7, NORTH, qup9, ddr_bist, _, atest_tsens2, vsense_trigger, atest_usb1, ddr_pxi0, _, _, _),
	PINGROUP(8, EAST, qup_l4, _, ddr_bist, _, _, wlan1_adc1, atest_usb13, ddr_pxi1, _, _),
	PINGROUP(9, EAST, qup_l5, ddr_bist, _, wlan1_adc0, atest_usb12, ddr_pxi1, _, _, _, _),
	PINGROUP(10, EAST, mdp_vsync, qup_l6, ddr_bist, wlan2_adc1, atest_usb11, ddr_pxi2, _, _, _, _),
	PINGROUP(11, EAST, mdp_vsync, edp_lcd, dbg_out, wlan2_adc0, atest_usb10, ddr_pxi2, _, _, _, _),
	PINGROUP(12, SOUTH, mdp_vsync, m_voc, tsअगर1_sync, ddr_pxi3, _, _, _, _, _, _),
	PINGROUP(13, SOUTH, cam_mclk, pll_bypassnl, qdss, ddr_pxi3, _, _, _, _, _, _),
	PINGROUP(14, SOUTH, cam_mclk, pll_reset, qdss, _, _, _, _, _, _, _),
	PINGROUP(15, SOUTH, cam_mclk, qdss, _, _, _, _, _, _, _, _),
	PINGROUP(16, SOUTH, cam_mclk, qdss, _, _, _, _, _, _, _, _),
	PINGROUP(17, SOUTH, cci_i2c, qup1, qdss, _, _, _, _, _, _, _),
	PINGROUP(18, SOUTH, cci_i2c, qup1, _, qdss, _, _, _, _, _, _),
	PINGROUP(19, SOUTH, cci_i2c, qup1, _, qdss, _, _, _, _, _, _),
	PINGROUP(20, SOUTH, cci_i2c, qup1, _, qdss, _, _, _, _, _, _),
	PINGROUP(21, SOUTH, cci_समयr0, gcc_gp2, qdss, _, _, _, _, _, _, _),
	PINGROUP(22, SOUTH, cci_समयr1, gcc_gp3, qdss, _, _, _, _, _, _, _),
	PINGROUP(23, SOUTH, cci_समयr2, qdss, _, _, _, _, _, _, _, _),
	PINGROUP(24, SOUTH, cci_समयr3, cci_async, qdss, _, _, _, _, _, _, _),
	PINGROUP(25, SOUTH, cci_समयr4, cci_async, qdss, _, _, _, _, _, _, _),
	PINGROUP(26, SOUTH, cci_async, qdss, _, _, _, _, _, _, _, _),
	PINGROUP(27, EAST, qup2, qdss, _, _, _, _, _, _, _, _),
	PINGROUP(28, EAST, qup2, qdss, _, _, _, _, _, _, _, _),
	PINGROUP(29, EAST, qup2, _, phase_flag, qdss, _, _, _, _, _, _),
	PINGROUP(30, EAST, qup2, phase_flag, qdss, _, _, _, _, _, _, _),
	PINGROUP(31, NORTH, qup11, qup14, _, _, _, _, _, _, _, _),
	PINGROUP(32, NORTH, qup11, qup14, _, _, _, _, _, _, _, _),
	PINGROUP(33, NORTH, qup11, qup14, _, _, _, _, _, _, _, _),
	PINGROUP(34, NORTH, qup11, qup14, _, _, _, _, _, _, _, _),
	PINGROUP(35, SOUTH, pci_e0, qup_l4, jitter_bist, _, _, _, _, _, _, _),
	PINGROUP(36, SOUTH, pci_e0, qup_l5, pll_bist, _, atest_tsens, _, _, _, _, _),
	PINGROUP(37, SOUTH, qup_l6, agera_pll, _, _, _, _, _, _, _, _),
	PINGROUP(38, NORTH, usb_phy, _, _, _, _, _, _, _, _, _),
	PINGROUP(39, EAST, lpass_slimbus, _, _, _, _, _, _, _, _, _),
	PINGROUP(40, SOUTH, sd_ग_लिखो, tsअगर1_error, _, _, _, _, _, _, _, _),
	PINGROUP(41, EAST, qup3, _, qdss, _, _, _, _, _, _, _),
	PINGROUP(42, EAST, qup3, _, qdss, _, _, _, _, _, _, _),
	PINGROUP(43, EAST, qup3, _, qdss, _, _, _, _, _, _, _),
	PINGROUP(44, EAST, qup3, _, qdss, _, _, _, _, _, _, _),
	PINGROUP(45, EAST, qup6, _, _, _, _, _, _, _, _, _),
	PINGROUP(46, EAST, qup6, _, _, _, _, _, _, _, _, _),
	PINGROUP(47, EAST, qup6, _, _, _, _, _, _, _, _, _),
	PINGROUP(48, EAST, qup6, _, _, _, _, _, _, _, _, _),
	PINGROUP(49, NORTH, qup12, _, _, _, _, _, _, _, _, _),
	PINGROUP(50, NORTH, qup12, _, _, _, _, _, _, _, _, _),
	PINGROUP(51, NORTH, qup12, qdss_cti, _, _, _, _, _, _, _, _),
	PINGROUP(52, NORTH, qup12, phase_flag, qdss_cti, _, _, _, _, _, _, _),
	PINGROUP(53, NORTH, qup10, phase_flag, _, _, _, _, _, _, _, _),
	PINGROUP(54, NORTH, qup10, _, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(55, NORTH, qup10, phase_flag, _, _, _, _, _, _, _, _),
	PINGROUP(56, NORTH, qup10, phase_flag, _, _, _, _, _, _, _, _),
	PINGROUP(57, NORTH, qua_mi2s, gcc_gp1, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(58, NORTH, qua_mi2s, gcc_gp2, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(59, NORTH, qua_mi2s, gcc_gp3, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(60, NORTH, qua_mi2s, cri_trng0, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(61, NORTH, qua_mi2s, cri_trng1, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(62, NORTH, qua_mi2s, cri_trng, phase_flag, qdss_cti, _, _, _, _, _, _),
	PINGROUP(63, NORTH, qua_mi2s, _, phase_flag, qdss_cti, _, _, _, _, _, _),
	PINGROUP(64, NORTH, pri_mi2s, sp_cmu, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(65, NORTH, pri_mi2s, qup8, _, _, _, _, _, _, _, _),
	PINGROUP(66, NORTH, pri_mi2s_ws, qup8, _, _, _, _, _, _, _, _),
	PINGROUP(67, NORTH, pri_mi2s, qup8, _, _, _, _, _, _, _, _),
	PINGROUP(68, NORTH, pri_mi2s, qup8, _, _, _, _, _, _, _, _),
	PINGROUP(69, EAST, spkr_i2s, audio_ref, _, _, _, _, _, _, _, _),
	PINGROUP(70, EAST, lpass_slimbus, spkr_i2s, _, _, _, _, _, _, _, _),
	PINGROUP(71, EAST, lpass_slimbus, spkr_i2s, tsense_pwm1, tsense_pwm2, _, _, _, _, _, _),
	PINGROUP(72, EAST, lpass_slimbus, spkr_i2s, _, _, _, _, _, _, _, _),
	PINGROUP(73, EAST, btfm_slimbus, atest_usb2, _, _, _, _, _, _, _, _),
	PINGROUP(74, EAST, btfm_slimbus, ter_mi2s, phase_flag, atest_usb23, _, _, _, _, _, _),
	PINGROUP(75, EAST, ter_mi2s, phase_flag, qdss, atest_usb22, _, _, _, _, _, _),
	PINGROUP(76, EAST, ter_mi2s, phase_flag, qdss, atest_usb21, _, _, _, _, _, _),
	PINGROUP(77, EAST, ter_mi2s, phase_flag, qdss, atest_usb20, _, _, _, _, _, _),
	PINGROUP(78, EAST, ter_mi2s, gcc_gp1, _, _, _, _, _, _, _, _),
	PINGROUP(79, NORTH, sec_mi2s, _, _, qdss, _, _, _, _, _, _),
	PINGROUP(80, NORTH, sec_mi2s, _, qdss, _, _, _, _, _, _, _),
	PINGROUP(81, NORTH, sec_mi2s, qup15, _, _, _, _, _, _, _, _),
	PINGROUP(82, NORTH, sec_mi2s, qup15, _, _, _, _, _, _, _, _),
	PINGROUP(83, NORTH, sec_mi2s, qup15, _, _, _, _, _, _, _, _),
	PINGROUP(84, NORTH, qup15, _, _, _, _, _, _, _, _, _),
	PINGROUP(85, EAST, qup5, _, _, _, _, _, _, _, _, _),
	PINGROUP(86, EAST, qup5, _, _, _, _, _, _, _, _, _),
	PINGROUP(87, EAST, qup5, _, _, _, _, _, _, _, _, _),
	PINGROUP(88, EAST, qup5, _, _, _, _, _, _, _, _, _),
	PINGROUP(89, SOUTH, tsअगर1_clk, qup4, qspi_cs, tgu_ch3, phase_flag, _, _, _, _, _),
	PINGROUP(90, SOUTH, tsअगर1_en, mdp_vsync0, qup4, qspi_cs, mdp_vsync1,
			    mdp_vsync2, mdp_vsync3, tgu_ch0, phase_flag, qdss_cti),
	PINGROUP(91, SOUTH, tsअगर1_data, sdc4_cmd, qup4, qspi_data, tgu_ch1, _, qdss_cti, _, _, _),
	PINGROUP(92, SOUTH, tsअगर2_error, sdc4_data, qup4, qspi_data, vfr_1, tgu_ch2, _, _, _, _),
	PINGROUP(93, SOUTH, tsअगर2_clk, sdc4_clk, qup7, qspi_data, _, qdss, _, _, _, _),
	PINGROUP(94, SOUTH, tsअगर2_en, sdc4_data, qup7, qspi_data, _, _, _, _, _, _),
	PINGROUP(95, SOUTH, tsअगर2_data, sdc4_data, qup7, qspi_clk, _, _, _, _, _, _),
	PINGROUP(96, SOUTH, tsअगर2_sync, sdc4_data, qup7, phase_flag, _, _, _, _, _, _),
	PINGROUP(97, NORTH, _, _, mdp_vsync, lकरो_en, _, _, _, _, _, _),
	PINGROUP(98, NORTH, _, mdp_vsync, lकरो_update, _, _, _, _, _, _, _),
	PINGROUP(99, NORTH, phase_flag, _, _, _, _, _, _, _, _, _),
	PINGROUP(100, NORTH, phase_flag, _, _, _, _, _, _, _, _, _),
	PINGROUP(101, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(102, NORTH, pci_e1, prng_rosc, _, _, _, _, _, _, _, _),
	PINGROUP(103, NORTH, pci_e1, phase_flag, _, _, _, _, _, _, _, _),
	PINGROUP(104, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(105, NORTH, uim2_data, qup13, qup_l4, _, _, _, _, _, _, _),
	PINGROUP(106, NORTH, uim2_clk, qup13, qup_l5, _, _, _, _, _, _, _),
	PINGROUP(107, NORTH, uim2_reset, qup13, qup_l6, _, _, _, _, _, _, _),
	PINGROUP(108, NORTH, uim2_present, qup13, _, _, _, _, _, _, _, _),
	PINGROUP(109, NORTH, uim1_data, _, _, _, _, _, _, _, _, _),
	PINGROUP(110, NORTH, uim1_clk, _, _, _, _, _, _, _, _, _),
	PINGROUP(111, NORTH, uim1_reset, _, _, _, _, _, _, _, _, _),
	PINGROUP(112, NORTH, uim1_present, _, _, _, _, _, _, _, _, _),
	PINGROUP(113, NORTH, uim_batt, edp_hot, _, _, _, _, _, _, _, _),
	PINGROUP(114, NORTH, _, nav_pps, nav_pps, _, _, _, _, _, _, _),
	PINGROUP(115, NORTH, _, nav_pps, nav_pps, _, _, _, _, _, _, _),
	PINGROUP(116, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(117, NORTH, _, qdss, atest_अक्षर, _, _, _, _, _, _, _),
	PINGROUP(118, NORTH, adsp_ext, _, qdss, atest_अक्षर, _, _, _, _, _, _),
	PINGROUP(119, NORTH, _, qdss, atest_अक्षर, _, _, _, _, _, _, _),
	PINGROUP(120, NORTH, _, qdss, atest_अक्षर, _, _, _, _, _, _, _),
	PINGROUP(121, NORTH, _, qdss, atest_अक्षर, _, _, _, _, _, _, _),
	PINGROUP(122, EAST, _, qdss, _, _, _, _, _, _, _, _),
	PINGROUP(123, EAST, qup_l4, _, qdss, _, _, _, _, _, _, _),
	PINGROUP(124, EAST, qup_l5, _, qdss, _, _, _, _, _, _, _),
	PINGROUP(125, EAST, qup_l6, _, _, _, _, _, _, _, _, _),
	PINGROUP(126, EAST, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(127, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(128, NORTH, nav_pps, nav_pps, _, _, _, _, _, _, _, _),
	PINGROUP(129, NORTH, nav_pps, nav_pps, _, _, _, _, _, _, _, _),
	PINGROUP(130, NORTH, qlink_request, _, _, _, _, _, _, _, _, _),
	PINGROUP(131, NORTH, qlink_enable, _, _, _, _, _, _, _, _, _),
	PINGROUP(132, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(133, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(134, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(135, NORTH, _, pa_indicator, _, _, _, _, _, _, _, _),
	PINGROUP(136, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(137, NORTH, _, _, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(138, NORTH, _, _, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(139, NORTH, _, phase_flag, _, _, _, _, _, _, _, _),
	PINGROUP(140, NORTH, _, _, phase_flag, _, _, _, _, _, _, _),
	PINGROUP(141, NORTH, _, phase_flag, _, _, _, _, _, _, _, _),
	PINGROUP(142, NORTH, _, phase_flag, _, _, _, _, _, _, _, _),
	PINGROUP(143, NORTH, _, nav_pps, nav_pps, _, phase_flag, _, _, _, _, _),
	PINGROUP(144, NORTH, mss_lte, _, _, _, _, _, _, _, _, _),
	PINGROUP(145, NORTH, mss_lte, _, _, _, _, _, _, _, _, _),
	PINGROUP(146, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(147, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(148, NORTH, _, _, _, _, _, _, _, _, _, _),
	PINGROUP(149, NORTH, _, _, _, _, _, _, _, _, _, _),
	UFS_RESET(ufs_reset, 0x99f000),
	SDC_QDSD_PINGROUP(sdc2_clk, 0x99a000, 14, 6),
	SDC_QDSD_PINGROUP(sdc2_cmd, 0x99a000, 11, 3),
	SDC_QDSD_PINGROUP(sdc2_data, 0x99a000, 9, 0),
पूर्ण;

अटल स्थिर पूर्णांक sdm845_acpi_reserved_gpios[] = अणु
	0, 1, 2, 3, 81, 82, 83, 84, -1
पूर्ण;

अटल स्थिर काष्ठा msm_gpio_wakeirq_map sdm845_pdc_map[] = अणु
	अणु 1, 30 पूर्ण, अणु 3, 31 पूर्ण, अणु 5, 32 पूर्ण, अणु 10, 33 पूर्ण, अणु 11, 34 पूर्ण,
	अणु 20, 35 पूर्ण, अणु 22, 36 पूर्ण, अणु 24, 37 पूर्ण, अणु 26, 38 पूर्ण, अणु 30, 39 पूर्ण,
	अणु 31, 117 पूर्ण, अणु 32, 41 पूर्ण, अणु 34, 42 पूर्ण, अणु 36, 43 पूर्ण, अणु 37, 44 पूर्ण,
	अणु 38, 45 पूर्ण, अणु 39, 46 पूर्ण, अणु 40, 47 पूर्ण, अणु 41, 115 पूर्ण, अणु 43, 49 पूर्ण,
	अणु 44, 50 पूर्ण, अणु 46, 51 पूर्ण, अणु 48, 52 पूर्ण, अणु 49, 118 पूर्ण, अणु 52, 54 पूर्ण,
	अणु 53, 55 पूर्ण, अणु 54, 56 पूर्ण, अणु 56, 57 पूर्ण, अणु 57, 58 पूर्ण, अणु 58, 59 पूर्ण,
	अणु 59, 60 पूर्ण, अणु 60, 61 पूर्ण, अणु 61, 62 पूर्ण, अणु 62, 63 पूर्ण, अणु 63, 64 पूर्ण,
	अणु 64, 65 पूर्ण, अणु 66, 66 पूर्ण, अणु 68, 67 पूर्ण, अणु 71, 68 पूर्ण, अणु 73, 69 पूर्ण,
	अणु 77, 70 पूर्ण, अणु 78, 71 पूर्ण, अणु 79, 72 पूर्ण, अणु 80, 73 पूर्ण, अणु 84, 74 पूर्ण,
	अणु 85, 75 पूर्ण, अणु 86, 76 पूर्ण, अणु 88, 77 पूर्ण, अणु 89, 116 पूर्ण, अणु 91, 79 पूर्ण,
	अणु 92, 80 पूर्ण, अणु 95, 81 पूर्ण, अणु 96, 82 पूर्ण, अणु 97, 83 पूर्ण, अणु 101, 84 पूर्ण,
	अणु 103, 85 पूर्ण, अणु 104, 86 पूर्ण, अणु 115, 90 पूर्ण, अणु 116, 91 पूर्ण, अणु 117, 92 पूर्ण,
	अणु 118, 93 पूर्ण, अणु 119, 94 पूर्ण, अणु 120, 95 पूर्ण, अणु 121, 96 पूर्ण, अणु 122, 97 पूर्ण,
	अणु 123, 98 पूर्ण, अणु 124, 99 पूर्ण, अणु 125, 100 पूर्ण, अणु 127, 102 पूर्ण, अणु 128, 103 पूर्ण,
	अणु 129, 104 पूर्ण, अणु 130, 105 पूर्ण, अणु 132, 106 पूर्ण, अणु 133, 107 पूर्ण, अणु 145, 108 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा msm_pinctrl_soc_data sdm845_pinctrl = अणु
	.pins = sdm845_pins,
	.npins = ARRAY_SIZE(sdm845_pins),
	.functions = sdm845_functions,
	.nfunctions = ARRAY_SIZE(sdm845_functions),
	.groups = sdm845_groups,
	.ngroups = ARRAY_SIZE(sdm845_groups),
	.ngpios = 151,
	.wakeirq_map = sdm845_pdc_map,
	.nwakeirq_map = ARRAY_SIZE(sdm845_pdc_map),
पूर्ण;

अटल स्थिर काष्ठा msm_pinctrl_soc_data sdm845_acpi_pinctrl = अणु
	.pins = sdm845_pins,
	.npins = ARRAY_SIZE(sdm845_pins),
	.groups = sdm845_groups,
	.ngroups = ARRAY_SIZE(sdm845_groups),
	.reserved_gpios = sdm845_acpi_reserved_gpios,
	.ngpios = 150,
पूर्ण;

अटल पूर्णांक sdm845_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	अगर (pdev->dev.of_node) अणु
		ret = msm_pinctrl_probe(pdev, &sdm845_pinctrl);
	पूर्ण अन्यथा अगर (has_acpi_companion(&pdev->dev)) अणु
		ret = msm_pinctrl_probe(pdev, &sdm845_acpi_pinctrl);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "DT and ACPI disabled\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id sdm845_pinctrl_acpi_match[] = अणु
	अणु "QCOM0217"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sdm845_pinctrl_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id sdm845_pinctrl_of_match[] = अणु
	अणु .compatible = "qcom,sdm845-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sdm845_pinctrl_driver = अणु
	.driver = अणु
		.name = "sdm845-pinctrl",
		.pm = &msm_pinctrl_dev_pm_ops,
		.of_match_table = sdm845_pinctrl_of_match,
		.acpi_match_table = ACPI_PTR(sdm845_pinctrl_acpi_match),
	पूर्ण,
	.probe = sdm845_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init sdm845_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sdm845_pinctrl_driver);
पूर्ण
arch_initcall(sdm845_pinctrl_init);

अटल व्योम __निकास sdm845_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sdm845_pinctrl_driver);
पूर्ण
module_निकास(sdm845_pinctrl_निकास);

MODULE_DESCRIPTION("QTI sdm845 pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, sdm845_pinctrl_of_match);
