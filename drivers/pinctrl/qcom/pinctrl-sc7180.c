<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-msm.h"

अटल स्थिर अक्षर * स्थिर sc7180_tiles[] = अणु
	"north",
	"south",
	"west",
पूर्ण;

क्रमागत अणु
	NORTH,
	SOUTH,
	WEST
पूर्ण;

#घोषणा FUNCTION(fname)					\
	[msm_mux_##fname] = अणु				\
		.name = #fname,				\
		.groups = fname##_groups,		\
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण

#घोषणा PINGROUP(id, _tile, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
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
			msm_mux_##f9			\
		पूर्ण,					\
		.nfuncs = 10,				\
		.ctl_reg = 0x1000 * id,		\
		.io_reg = 0x1000 * id + 0x4,		\
		.पूर्णांकr_cfg_reg = 0x1000 * id + 0x8,	\
		.पूर्णांकr_status_reg = 0x1000 * id + 0xc,	\
		.पूर्णांकr_target_reg = 0x1000 * id + 0x8,	\
		.tile = _tile,			\
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
		.tile = SOUTH,				\
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
		.tile = SOUTH,				\
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
अटल स्थिर काष्ठा pinctrl_pin_desc sc7180_pins[] = अणु
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
	PINCTRL_PIN(119, "UFS_RESET"),
	PINCTRL_PIN(120, "SDC1_RCLK"),
	PINCTRL_PIN(121, "SDC1_CLK"),
	PINCTRL_PIN(122, "SDC1_CMD"),
	PINCTRL_PIN(123, "SDC1_DATA"),
	PINCTRL_PIN(124, "SDC2_CLK"),
	PINCTRL_PIN(125, "SDC2_CMD"),
	PINCTRL_PIN(126, "SDC2_DATA"),
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

अटल स्थिर अचिन्हित पूर्णांक ufs_reset_pins[] = अणु 119 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_rclk_pins[] = अणु 120 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_clk_pins[] = अणु 121 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_cmd_pins[] = अणु 122 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_data_pins[] = अणु 123 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_clk_pins[] = अणु 124 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_cmd_pins[] = अणु 125 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_data_pins[] = अणु 126 पूर्ण;

क्रमागत sc7180_functions अणु
	msm_mux_adsp_ext,
	msm_mux_agera_pll,
	msm_mux_aoss_cti,
	msm_mux_atest_अक्षर,
	msm_mux_atest_अक्षर0,
	msm_mux_atest_अक्षर1,
	msm_mux_atest_अक्षर2,
	msm_mux_atest_अक्षर3,
	msm_mux_atest_tsens,
	msm_mux_atest_tsens2,
	msm_mux_atest_usb1,
	msm_mux_atest_usb2,
	msm_mux_atest_usb10,
	msm_mux_atest_usb11,
	msm_mux_atest_usb12,
	msm_mux_atest_usb13,
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
	msm_mux_dbg_out,
	msm_mux_ddr_bist,
	msm_mux_ddr_pxi0,
	msm_mux_ddr_pxi1,
	msm_mux_ddr_pxi2,
	msm_mux_ddr_pxi3,
	msm_mux_dp_hot,
	msm_mux_edp_lcd,
	msm_mux_gcc_gp1,
	msm_mux_gcc_gp2,
	msm_mux_gcc_gp3,
	msm_mux_gpio,
	msm_mux_gp_pdm0,
	msm_mux_gp_pdm1,
	msm_mux_gp_pdm2,
	msm_mux_gps_tx,
	msm_mux_jitter_bist,
	msm_mux_lकरो_en,
	msm_mux_lकरो_update,
	msm_mux_lpass_ext,
	msm_mux_mdp_vsync,
	msm_mux_mdp_vsync0,
	msm_mux_mdp_vsync1,
	msm_mux_mdp_vsync2,
	msm_mux_mdp_vsync3,
	msm_mux_mi2s_1,
	msm_mux_mi2s_0,
	msm_mux_mi2s_2,
	msm_mux_mss_lte,
	msm_mux_m_voc,
	msm_mux_pa_indicator,
	msm_mux_phase_flag,
	msm_mux_PLL_BIST,
	msm_mux_pll_bypassnl,
	msm_mux_pll_reset,
	msm_mux_prng_rosc,
	msm_mux_qdss,
	msm_mux_qdss_cti,
	msm_mux_qlink_enable,
	msm_mux_qlink_request,
	msm_mux_qspi_clk,
	msm_mux_qspi_cs,
	msm_mux_qspi_data,
	msm_mux_qup00,
	msm_mux_qup01,
	msm_mux_qup02_i2c,
	msm_mux_qup02_uart,
	msm_mux_qup03,
	msm_mux_qup04_i2c,
	msm_mux_qup04_uart,
	msm_mux_qup05,
	msm_mux_qup10,
	msm_mux_qup11_i2c,
	msm_mux_qup11_uart,
	msm_mux_qup12,
	msm_mux_qup13_i2c,
	msm_mux_qup13_uart,
	msm_mux_qup14,
	msm_mux_qup15,
	msm_mux_sdc1_tb,
	msm_mux_sdc2_tb,
	msm_mux_sd_ग_लिखो,
	msm_mux_sp_cmu,
	msm_mux_tgu_ch0,
	msm_mux_tgu_ch1,
	msm_mux_tgu_ch2,
	msm_mux_tgu_ch3,
	msm_mux_tsense_pwm1,
	msm_mux_tsense_pwm2,
	msm_mux_uim1,
	msm_mux_uim2,
	msm_mux_uim_batt,
	msm_mux_usb_phy,
	msm_mux_vfr_1,
	msm_mux__V_GPIO,
	msm_mux__V_PPS_IN,
	msm_mux__V_PPS_OUT,
	msm_mux_vsense_trigger,
	msm_mux_wlan1_adc0,
	msm_mux_wlan1_adc1,
	msm_mux_wlan2_adc0,
	msm_mux_wlan2_adc1,
	msm_mux__,
पूर्ण;

अटल स्थिर अक्षर * स्थिर qup01_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio12", "gpio94",
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
	"gpio117", "gpio118",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio8", "gpio9",
	"gpio11", "gpio12", "gpio17", "gpio18", "gpio19",
	"gpio20", "gpio25", "gpio26", "gpio27", "gpio28",
	"gpio32", "gpio33", "gpio34", "gpio35", "gpio36",
	"gpio37", "gpio38", "gpio39", "gpio42", "gpio44",
	"gpio56", "gpio57", "gpio58", "gpio63", "gpio64",
	"gpio108", "gpio109",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cri_trng_groups[] = अणु
	"gpio0", "gpio1", "gpio2",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sp_cmu_groups[] = अणु
	"gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dbg_out_groups[] = अणु
	"gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti_groups[] = अणु
	"gpio3", "gpio4", "gpio8", "gpio9", "gpio33", "gpio44", "gpio45",
	"gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc1_tb_groups[] = अणु
	"gpio4",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sdc2_tb_groups[] = अणु
	"gpio5",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup11_i2c_groups[] = अणु
	"gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup11_uart_groups[] = अणु
	"gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_bist_groups[] = अणु
	"gpio7", "gpio8", "gpio9", "gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gp_pdm1_groups[] = अणु
	"gpio8", "gpio50",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync_groups[] = अणु
	"gpio10", "gpio11", "gpio12", "gpio70", "gpio71",
पूर्ण;
अटल स्थिर अक्षर * स्थिर edp_lcd_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_pxi2_groups[] = अणु
	"gpio11", "gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर m_voc_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan2_adc0_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb10_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_pxi3_groups[] = अणु
	"gpio12", "gpio108",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cam_mclk_groups[] = अणु
	"gpio13", "gpio14", "gpio15", "gpio16", "gpio23",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_bypassnl_groups[] = अणु
	"gpio13",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_groups[] = अणु
	"gpio13", "gpio86", "gpio14", "gpio87",
	"gpio15", "gpio88", "gpio16", "gpio89",
	"gpio17", "gpio90", "gpio18", "gpio91",
	"gpio19", "gpio21", "gpio20", "gpio22",
	"gpio23", "gpio54", "gpio24", "gpio36",
	"gpio25", "gpio57", "gpio26", "gpio31",
	"gpio27", "gpio56", "gpio28", "gpio29",
	"gpio30", "gpio35", "gpio93", "gpio104",
	"gpio34", "gpio53", "gpio37", "gpio55",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_reset_groups[] = अणु
	"gpio14",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup02_i2c_groups[] = अणु
	"gpio15", "gpio16",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup02_uart_groups[] = अणु
	"gpio15", "gpio16",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_i2c_groups[] = अणु
	"gpio17", "gpio18", "gpio19", "gpio20", "gpio27", "gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan1_adc0_groups[] = अणु
	"gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb12_groups[] = अणु
	"gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_pxi1_groups[] = अणु
	"gpio17", "gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर_groups[] = अणु
	"gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर agera_pll_groups[] = अणु
	"gpio18",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vsense_trigger_groups[] = अणु
	"gpio18",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_pxi0_groups[] = अणु
	"gpio18", "gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर3_groups[] = अणु
	"gpio18",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर2_groups[] = अणु
	"gpio19",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर1_groups[] = अणु
	"gpio20",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr0_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp2_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर0_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_समयr1_groups[] = अणु
	"gpio22",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp3_groups[] = अणु
	"gpio22",
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
अटल स्थिर अक्षर * स्थिर qup05_groups[] = अणु
	"gpio25", "gpio26", "gpio27", "gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens_groups[] = अणु
	"gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb11_groups[] = अणु
	"gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर PLL_BIST_groups[] = अणु
	"gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sd_ग_लिखो_groups[] = अणु
	"gpio33",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup00_groups[] = अणु
	"gpio34", "gpio35", "gpio36", "gpio37",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gp_pdm0_groups[] = अणु
	"gpio37", "gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup03_groups[] = अणु
	"gpio38", "gpio39", "gpio40", "gpio41",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens2_groups[] = अणु
	"gpio39",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan2_adc1_groups[] = अणु
	"gpio39",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb1_groups[] = अणु
	"gpio39",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup12_groups[] = अणु
	"gpio42", "gpio43", "gpio44", "gpio45",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan1_adc1_groups[] = अणु
	"gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb13_groups[] = अणु
	"gpio44",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup13_i2c_groups[] = अणु
	"gpio46", "gpio47",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup13_uart_groups[] = अणु
	"gpio46", "gpio47",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp1_groups[] = अणु
	"gpio48", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mi2s_1_groups[] = अणु
	"gpio49", "gpio50", "gpio51", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर btfm_slimbus_groups[] = अणु
	"gpio49", "gpio50", "gpio51", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb2_groups[] = अणु
	"gpio51",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb23_groups[] = अणु
	"gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mi2s_0_groups[] = अणु
	"gpio53", "gpio54", "gpio55", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup15_groups[] = अणु
	"gpio53", "gpio54", "gpio55", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb22_groups[] = अणु
	"gpio53",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb21_groups[] = अणु
	"gpio54",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb20_groups[] = अणु
	"gpio55",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lpass_ext_groups[] = अणु
	"gpio57", "gpio58",
पूर्ण;
अटल स्थिर अक्षर * स्थिर audio_ref_groups[] = अणु
	"gpio57",
पूर्ण;
अटल स्थिर अक्षर * स्थिर jitter_bist_groups[] = अणु
	"gpio57",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gp_pdm2_groups[] = अणु
	"gpio57",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup10_groups[] = अणु
	"gpio59", "gpio60", "gpio61", "gpio62", "gpio68", "gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch3_groups[] = अणु
	"gpio62",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_clk_groups[] = अणु
	"gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync0_groups[] = अणु
	"gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mi2s_2_groups[] = अणु
	"gpio63", "gpio64", "gpio65", "gpio66",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync1_groups[] = अणु
	"gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync2_groups[] = अणु
	"gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync3_groups[] = अणु
	"gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch0_groups[] = अणु
	"gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_data_groups[] = अणु
	"gpio64", "gpio65", "gpio66", "gpio67",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch1_groups[] = अणु
	"gpio64",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vfr_1_groups[] = अणु
	"gpio65",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch2_groups[] = अणु
	"gpio65",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_cs_groups[] = अणु
	"gpio68", "gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_en_groups[] = अणु
	"gpio70",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_update_groups[] = अणु
	"gpio71",
पूर्ण;
अटल स्थिर अक्षर * स्थिर prng_rosc_groups[] = अणु
	"gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_groups[] = अणु
	"gpio75", "gpio76", "gpio77", "gpio78",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_groups[] = अणु
	"gpio79", "gpio80", "gpio81", "gpio82",
पूर्ण;
अटल स्थिर अक्षर * स्थिर _V_GPIO_groups[] = अणु
	"gpio83", "gpio84", "gpio107",
पूर्ण;
अटल स्थिर अक्षर * स्थिर _V_PPS_IN_groups[] = अणु
	"gpio83", "gpio84", "gpio107",
पूर्ण;
अटल स्थिर अक्षर * स्थिर _V_PPS_OUT_groups[] = अणु
	"gpio83", "gpio84", "gpio107",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gps_tx_groups[] = अणु
	"gpio83", "gpio84", "gpio107", "gpio109",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim_batt_groups[] = अणु
	"gpio85",
पूर्ण;
अटल स्थिर अक्षर * स्थिर dp_hot_groups[] = अणु
	"gpio85", "gpio117",
पूर्ण;
अटल स्थिर अक्षर * स्थिर aoss_cti_groups[] = अणु
	"gpio85",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup14_groups[] = अणु
	"gpio86", "gpio87", "gpio88", "gpio89", "gpio90", "gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर adsp_ext_groups[] = अणु
	"gpio87",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsense_pwm1_groups[] = अणु
	"gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsense_pwm2_groups[] = अणु
	"gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qlink_request_groups[] = अणु
	"gpio96",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qlink_enable_groups[] = अणु
	"gpio97",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pa_indicator_groups[] = अणु
	"gpio99",
पूर्ण;
अटल स्थिर अक्षर * स्थिर usb_phy_groups[] = अणु
	"gpio104",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mss_lte_groups[] = अणु
	"gpio108", "gpio109",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup04_i2c_groups[] = अणु
	"gpio115", "gpio116",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qup04_uart_groups[] = अणु
	"gpio115", "gpio116",
पूर्ण;

अटल स्थिर काष्ठा msm_function sc7180_functions[] = अणु
	FUNCTION(adsp_ext),
	FUNCTION(agera_pll),
	FUNCTION(aoss_cti),
	FUNCTION(atest_अक्षर),
	FUNCTION(atest_अक्षर0),
	FUNCTION(atest_अक्षर1),
	FUNCTION(atest_अक्षर2),
	FUNCTION(atest_अक्षर3),
	FUNCTION(atest_tsens),
	FUNCTION(atest_tsens2),
	FUNCTION(atest_usb1),
	FUNCTION(atest_usb2),
	FUNCTION(atest_usb10),
	FUNCTION(atest_usb11),
	FUNCTION(atest_usb12),
	FUNCTION(atest_usb13),
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
	FUNCTION(dbg_out),
	FUNCTION(ddr_bist),
	FUNCTION(ddr_pxi0),
	FUNCTION(ddr_pxi1),
	FUNCTION(ddr_pxi2),
	FUNCTION(ddr_pxi3),
	FUNCTION(dp_hot),
	FUNCTION(edp_lcd),
	FUNCTION(gcc_gp1),
	FUNCTION(gcc_gp2),
	FUNCTION(gcc_gp3),
	FUNCTION(gpio),
	FUNCTION(gp_pdm0),
	FUNCTION(gp_pdm1),
	FUNCTION(gp_pdm2),
	FUNCTION(gps_tx),
	FUNCTION(jitter_bist),
	FUNCTION(lकरो_en),
	FUNCTION(lकरो_update),
	FUNCTION(lpass_ext),
	FUNCTION(mdp_vsync),
	FUNCTION(mdp_vsync0),
	FUNCTION(mdp_vsync1),
	FUNCTION(mdp_vsync2),
	FUNCTION(mdp_vsync3),
	FUNCTION(mi2s_0),
	FUNCTION(mi2s_1),
	FUNCTION(mi2s_2),
	FUNCTION(mss_lte),
	FUNCTION(m_voc),
	FUNCTION(pa_indicator),
	FUNCTION(phase_flag),
	FUNCTION(PLL_BIST),
	FUNCTION(pll_bypassnl),
	FUNCTION(pll_reset),
	FUNCTION(prng_rosc),
	FUNCTION(qdss),
	FUNCTION(qdss_cti),
	FUNCTION(qlink_enable),
	FUNCTION(qlink_request),
	FUNCTION(qspi_clk),
	FUNCTION(qspi_cs),
	FUNCTION(qspi_data),
	FUNCTION(qup00),
	FUNCTION(qup01),
	FUNCTION(qup02_i2c),
	FUNCTION(qup02_uart),
	FUNCTION(qup03),
	FUNCTION(qup04_i2c),
	FUNCTION(qup04_uart),
	FUNCTION(qup05),
	FUNCTION(qup10),
	FUNCTION(qup11_i2c),
	FUNCTION(qup11_uart),
	FUNCTION(qup12),
	FUNCTION(qup13_i2c),
	FUNCTION(qup13_uart),
	FUNCTION(qup14),
	FUNCTION(qup15),
	FUNCTION(sdc1_tb),
	FUNCTION(sdc2_tb),
	FUNCTION(sd_ग_लिखो),
	FUNCTION(sp_cmu),
	FUNCTION(tgu_ch0),
	FUNCTION(tgu_ch1),
	FUNCTION(tgu_ch2),
	FUNCTION(tgu_ch3),
	FUNCTION(tsense_pwm1),
	FUNCTION(tsense_pwm2),
	FUNCTION(uim1),
	FUNCTION(uim2),
	FUNCTION(uim_batt),
	FUNCTION(usb_phy),
	FUNCTION(vfr_1),
	FUNCTION(_V_GPIO),
	FUNCTION(_V_PPS_IN),
	FUNCTION(_V_PPS_OUT),
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
अटल स्थिर काष्ठा msm_pingroup sc7180_groups[] = अणु
	[0] = PINGROUP(0, SOUTH, qup01, cri_trng, _, phase_flag, _, _, _, _, _),
	[1] = PINGROUP(1, SOUTH, qup01, cri_trng, _, phase_flag, _, _, _, _, _),
	[2] = PINGROUP(2, SOUTH, qup01, cri_trng, _, phase_flag, _, _, _, _, _),
	[3] = PINGROUP(3, SOUTH, qup01, sp_cmu, dbg_out, qdss_cti, _, _, _, _, _),
	[4] = PINGROUP(4, NORTH, sdc1_tb, _, qdss_cti, _, _, _, _, _, _),
	[5] = PINGROUP(5, NORTH, sdc2_tb, _, _, _, _, _, _, _, _),
	[6] = PINGROUP(6, NORTH, qup11_i2c, qup11_uart, _, _, _, _, _, _, _),
	[7] = PINGROUP(7, NORTH, qup11_i2c, qup11_uart, ddr_bist, _, _, _, _, _, _),
	[8] = PINGROUP(8, NORTH, gp_pdm1, ddr_bist, _, phase_flag, qdss_cti, _, _, _, _),
	[9] = PINGROUP(9, NORTH, ddr_bist, _, phase_flag, qdss_cti, _, _, _, _, _),
	[10] = PINGROUP(10, NORTH, mdp_vsync, ddr_bist, _, _, _, _, _, _, _),
	[11] = PINGROUP(11, NORTH, mdp_vsync, edp_lcd, _, phase_flag, ddr_pxi2, _, _, _, _),
	[12] = PINGROUP(12, SOUTH, mdp_vsync, m_voc, qup01, _, phase_flag, wlan2_adc0, atest_usb10, ddr_pxi3, _),
	[13] = PINGROUP(13, SOUTH, cam_mclk, pll_bypassnl, qdss, _, _, _, _, _, _),
	[14] = PINGROUP(14, SOUTH, cam_mclk, pll_reset, qdss, _, _, _, _, _, _),
	[15] = PINGROUP(15, SOUTH, cam_mclk, qup02_i2c, qup02_uart, qdss, _, _, _, _, _),
	[16] = PINGROUP(16, SOUTH, cam_mclk, qup02_i2c, qup02_uart, qdss, _, _, _, _, _),
	[17] = PINGROUP(17, SOUTH, cci_i2c, _, phase_flag, qdss, _, wlan1_adc0, atest_usb12, ddr_pxi1, atest_अक्षर),
	[18] = PINGROUP(18, SOUTH, cci_i2c, agera_pll, _, phase_flag, qdss, vsense_trigger, ddr_pxi0, atest_अक्षर3, _),
	[19] = PINGROUP(19, SOUTH, cci_i2c, _, phase_flag, qdss, atest_अक्षर2, _, _, _, _),
	[20] = PINGROUP(20, SOUTH, cci_i2c, _, phase_flag, qdss, atest_अक्षर1, _, _, _, _),
	[21] = PINGROUP(21, NORTH, cci_समयr0, gcc_gp2, _, qdss, atest_अक्षर0, _, _, _, _),
	[22] = PINGROUP(22, NORTH, cci_समयr1, gcc_gp3, _, qdss, _, _, _, _, _),
	[23] = PINGROUP(23, SOUTH, cci_समयr2, cam_mclk, qdss, _, _, _, _, _, _),
	[24] = PINGROUP(24, SOUTH, cci_समयr3, cci_async, qdss, _, _, _, _, _, _),
	[25] = PINGROUP(25, SOUTH, cci_समयr4, cci_async, qup05, _, phase_flag, qdss, _, _, _),
	[26] = PINGROUP(26, SOUTH, cci_async, qup05, _, phase_flag, qdss, atest_tsens, atest_usb11, ddr_pxi2, _),
	[27] = PINGROUP(27, SOUTH, cci_i2c, qup05, PLL_BIST, _, phase_flag, qdss, ddr_pxi0, _, _),
	[28] = PINGROUP(28, SOUTH, cci_i2c, qup05, _, phase_flag, qdss, _, _, _, _),
	[29] = PINGROUP(29, NORTH, _, qdss, _, _, _, _, _, _, _),
	[30] = PINGROUP(30, SOUTH, qdss, _, _, _, _, _, _, _, _),
	[31] = PINGROUP(31, NORTH, _, qdss, _, _, _, _, _, _, _),
	[32] = PINGROUP(32, NORTH, _, phase_flag, _, _, _, _, _, _, _),
	[33] = PINGROUP(33, NORTH, sd_ग_लिखो, _, phase_flag, qdss_cti, _, _, _, _, _),
	[34] = PINGROUP(34, SOUTH, qup00, _, phase_flag, qdss, _, _, _, _, _),
	[35] = PINGROUP(35, SOUTH, qup00, _, phase_flag, qdss, _, _, _, _, _),
	[36] = PINGROUP(36, SOUTH, qup00, _, phase_flag, qdss, _, _, _, _, _),
	[37] = PINGROUP(37, SOUTH, qup00, gp_pdm0, _, phase_flag, qdss, _, _, _, _),
	[38] = PINGROUP(38, SOUTH, qup03, _, phase_flag, _, _, _, _, _, _),
	[39] = PINGROUP(39, SOUTH, qup03, _, phase_flag, atest_tsens2, wlan2_adc1, atest_usb1, _, _, _),
	[40] = PINGROUP(40, SOUTH, qup03, _, _, _, _, _, _, _, _),
	[41] = PINGROUP(41, SOUTH, qup03, _, _, _, _, _, _, _, _),
	[42] = PINGROUP(42, NORTH, qup12, _, phase_flag, _, _, _, _, _, _),
	[43] = PINGROUP(43, NORTH, qup12, _, _, _, _, _, _, _, _),
	[44] = PINGROUP(44, NORTH, qup12, _, phase_flag, qdss_cti, wlan1_adc1, atest_usb13, ddr_pxi1, _, _),
	[45] = PINGROUP(45, NORTH, qup12, qdss_cti, _, _, _, _, _, _, _),
	[46] = PINGROUP(46, NORTH, qup13_i2c, qup13_uart, _, _, _, _, _, _, _),
	[47] = PINGROUP(47, NORTH, qup13_i2c, qup13_uart, _, _, _, _, _, _, _),
	[48] = PINGROUP(48, NORTH, gcc_gp1, _, _, _, _, _, _, _, _),
	[49] = PINGROUP(49, WEST, mi2s_1, btfm_slimbus, _, _, _, _, _, _, _),
	[50] = PINGROUP(50, WEST, mi2s_1, btfm_slimbus, gp_pdm1, _, _, _, _, _, _),
	[51] = PINGROUP(51, WEST, mi2s_1, btfm_slimbus, atest_usb2, _, _, _, _, _, _),
	[52] = PINGROUP(52, WEST, mi2s_1, btfm_slimbus, atest_usb23, _, _, _, _, _, _),
	[53] = PINGROUP(53, WEST, mi2s_0, qup15, qdss, atest_usb22, _, _, _, _, _),
	[54] = PINGROUP(54, WEST, mi2s_0, qup15, qdss, atest_usb21, _, _, _, _, _),
	[55] = PINGROUP(55, WEST, mi2s_0, qup15, qdss, atest_usb20, _, _, _, _, _),
	[56] = PINGROUP(56, WEST, mi2s_0, qup15, gcc_gp1, _, phase_flag, qdss, _, _, _),
	[57] = PINGROUP(57, WEST, lpass_ext, audio_ref, jitter_bist, gp_pdm2, _, phase_flag, qdss, _, _),
	[58] = PINGROUP(58, WEST, lpass_ext, _, phase_flag, _, _, _, _, _, _),
	[59] = PINGROUP(59, NORTH, qup10, _, _, _, _, _, _, _, _),
	[60] = PINGROUP(60, NORTH, qup10, _, _, _, _, _, _, _, _),
	[61] = PINGROUP(61, NORTH, qup10, _, _, _, _, _, _, _, _),
	[62] = PINGROUP(62, NORTH, qup10, tgu_ch3, _, _, _, _, _, _, _),
	[63] = PINGROUP(63, NORTH, qspi_clk, mdp_vsync0, mi2s_2, mdp_vsync1, mdp_vsync2, mdp_vsync3, tgu_ch0, _, phase_flag),
	[64] = PINGROUP(64, NORTH, qspi_data, mi2s_2, tgu_ch1, _, phase_flag, _, _, _, _),
	[65] = PINGROUP(65, NORTH, qspi_data, mi2s_2, vfr_1, tgu_ch2, _, _, _, _, _),
	[66] = PINGROUP(66, NORTH, qspi_data, mi2s_2, _, _, _, _, _, _, _),
	[67] = PINGROUP(67, NORTH, qspi_data, _, _, _, _, _, _, _, _),
	[68] = PINGROUP(68, NORTH, qspi_cs, qup10, gp_pdm0, _, _, _, _, _, _),
	[69] = PINGROUP(69, WEST, _, _, _, _, _, _, _, _, _),
	[70] = PINGROUP(70, NORTH, _, _, mdp_vsync, lकरो_en, _, _, _, _, _),
	[71] = PINGROUP(71, NORTH, _, mdp_vsync, lकरो_update, _, _, _, _, _, _),
	[72] = PINGROUP(72, NORTH, qspi_cs, qup10, prng_rosc, _, qdss_cti, _, _, _, _),
	[73] = PINGROUP(73, WEST, _, _, _, _, _, _, _, _, _),
	[74] = PINGROUP(74, WEST, _, _, _, _, _, _, _, _, _),
	[75] = PINGROUP(75, WEST, uim2, _, _, _, _, _, _, _, _),
	[76] = PINGROUP(76, WEST, uim2, _, _, _, _, _, _, _, _),
	[77] = PINGROUP(77, WEST, uim2, _, _, _, _, _, _, _, _),
	[78] = PINGROUP(78, WEST, uim2, _, _, _, _, _, _, _, _),
	[79] = PINGROUP(79, WEST, uim1, _, _, _, _, _, _, _, _),
	[80] = PINGROUP(80, WEST, uim1, _, _, _, _, _, _, _, _),
	[81] = PINGROUP(81, WEST, uim1, _, _, _, _, _, _, _, _),
	[82] = PINGROUP(82, WEST, uim1, _, _, _, _, _, _, _, _),
	[83] = PINGROUP(83, WEST, _, _V_GPIO, _V_PPS_IN, _V_PPS_OUT, gps_tx, _, _, _, _),
	[84] = PINGROUP(84, WEST, _, _V_GPIO, _V_PPS_IN, _V_PPS_OUT, gps_tx, _, _, _, _),
	[85] = PINGROUP(85, WEST, uim_batt, dp_hot, aoss_cti, _, _, _, _, _, _),
	[86] = PINGROUP(86, NORTH, qup14, qdss, _, _, _, _, _, _, _),
	[87] = PINGROUP(87, NORTH, qup14, adsp_ext, qdss, _, _, _, _, _, _),
	[88] = PINGROUP(88, NORTH, qup14, qdss, tsense_pwm1, tsense_pwm2, _, _, _, _, _),
	[89] = PINGROUP(89, NORTH, qup14, qdss, _, _, _, _, _, _, _),
	[90] = PINGROUP(90, NORTH, qup14, qdss, _, _, _, _, _, _, _),
	[91] = PINGROUP(91, NORTH, qup14, qdss, _, _, _, _, _, _, _),
	[92] = PINGROUP(92, NORTH, _, _, _, _, _, _, _, _, _),
	[93] = PINGROUP(93, NORTH, qdss, _, _, _, _, _, _, _, _),
	[94] = PINGROUP(94, SOUTH, qup01, _, _, _, _, _, _, _, _),
	[95] = PINGROUP(95, WEST, _, _, _, _, _, _, _, _, _),
	[96] = PINGROUP(96, WEST, qlink_request, _, _, _, _, _, _, _, _),
	[97] = PINGROUP(97, WEST, qlink_enable, _, _, _, _, _, _, _, _),
	[98] = PINGROUP(98, WEST, _, _, _, _, _, _, _, _, _),
	[99] = PINGROUP(99, WEST, _, pa_indicator, _, _, _, _, _, _, _),
	[100] = PINGROUP(100, WEST, _, _, _, _, _, _, _, _, _),
	[101] = PINGROUP(101, NORTH, _, _, _, _, _, _, _, _, _),
	[102] = PINGROUP(102, NORTH, _, _, _, _, _, _, _, _, _),
	[103] = PINGROUP(103, NORTH, _, _, _, _, _, _, _, _, _),
	[104] = PINGROUP(104, WEST, usb_phy, _, qdss, _, _, _, _, _, _),
	[105] = PINGROUP(105, NORTH, _, _, _, _, _, _, _, _, _),
	[106] = PINGROUP(106, NORTH, _, _, _, _, _, _, _, _, _),
	[107] = PINGROUP(107, WEST, _, _V_GPIO, _V_PPS_IN, _V_PPS_OUT, gps_tx, _, _, _, _),
	[108] = PINGROUP(108, SOUTH, mss_lte, _, phase_flag, ddr_pxi3, _, _, _, _, _),
	[109] = PINGROUP(109, SOUTH, mss_lte, gps_tx, _, phase_flag, _, _, _, _, _),
	[110] = PINGROUP(110, NORTH, _, _, _, _, _, _, _, _, _),
	[111] = PINGROUP(111, NORTH, _, _, _, _, _, _, _, _, _),
	[112] = PINGROUP(112, NORTH, _, _, _, _, _, _, _, _, _),
	[113] = PINGROUP(113, NORTH, _, _, _, _, _, _, _, _, _),
	[114] = PINGROUP(114, NORTH, _, _, _, _, _, _, _, _, _),
	[115] = PINGROUP(115, WEST, qup04_i2c, qup04_uart, _, _, _, _, _, _, _),
	[116] = PINGROUP(116, WEST, qup04_i2c, qup04_uart, _, _, _, _, _, _, _),
	[117] = PINGROUP(117, WEST, dp_hot, _, _, _, _, _, _, _, _),
	[118] = PINGROUP(118, WEST, _, _, _, _, _, _, _, _, _),
	[119] = UFS_RESET(ufs_reset, 0x7f000),
	[120] = SDC_QDSD_PINGROUP(sdc1_rclk, 0x7a000, 15, 0),
	[121] = SDC_QDSD_PINGROUP(sdc1_clk, 0x7a000, 13, 6),
	[122] = SDC_QDSD_PINGROUP(sdc1_cmd, 0x7a000, 11, 3),
	[123] = SDC_QDSD_PINGROUP(sdc1_data, 0x7a000, 9, 0),
	[124] = SDC_QDSD_PINGROUP(sdc2_clk, 0x7b000, 14, 6),
	[125] = SDC_QDSD_PINGROUP(sdc2_cmd, 0x7b000, 11, 3),
	[126] = SDC_QDSD_PINGROUP(sdc2_data, 0x7b000, 9, 0),
पूर्ण;

अटल स्थिर काष्ठा msm_gpio_wakeirq_map sc7180_pdc_map[] = अणु
	अणु0, 40पूर्ण, अणु3, 50पूर्ण, अणु4, 42पूर्ण, अणु5, 70पूर्ण, अणु6, 41पूर्ण, अणु9, 35पूर्ण,
	अणु10, 80पूर्ण, अणु11, 51पूर्ण, अणु16, 20पूर्ण, अणु21, 55पूर्ण, अणु22, 90पूर्ण, अणु23, 21पूर्ण,
	अणु24, 61पूर्ण, अणु26, 52पूर्ण, अणु28, 36पूर्ण, अणु30, 100पूर्ण, अणु31, 33पूर्ण, अणु32, 81पूर्ण,
	अणु33, 62पूर्ण, अणु34, 43पूर्ण, अणु36, 91पूर्ण, अणु37, 53पूर्ण, अणु38, 63पूर्ण, अणु39, 72पूर्ण,
	अणु41, 101पूर्ण, अणु42, 7पूर्ण, अणु43, 34पूर्ण, अणु45, 73पूर्ण, अणु47, 82पूर्ण, अणु49, 17पूर्ण,
	अणु52, 109पूर्ण, अणु53, 102पूर्ण, अणु55, 92पूर्ण, अणु56, 56पूर्ण, अणु57, 57पूर्ण, अणु58, 83पूर्ण,
	अणु59, 37पूर्ण, अणु62, 110पूर्ण, अणु63, 111पूर्ण, अणु64, 74पूर्ण, अणु65, 44पूर्ण, अणु66, 93पूर्ण,
	अणु67, 58पूर्ण, अणु68, 112पूर्ण, अणु69, 32पूर्ण, अणु70, 54पूर्ण, अणु72, 59पूर्ण, अणु73, 64पूर्ण,
	अणु74, 71पूर्ण, अणु78, 31पूर्ण, अणु82, 30पूर्ण, अणु85, 103पूर्ण, अणु86, 38पूर्ण, अणु87, 39पूर्ण,
	अणु88, 45पूर्ण, अणु89, 46पूर्ण, अणु90, 47पूर्ण, अणु91, 48पूर्ण, अणु92, 60पूर्ण, अणु93, 49पूर्ण,
	अणु94, 84पूर्ण, अणु95, 94पूर्ण, अणु98, 65पूर्ण, अणु101, 66पूर्ण, अणु104, 67पूर्ण, अणु109, 104पूर्ण,
	अणु110, 68पूर्ण, अणु113, 69पूर्ण, अणु114, 113पूर्ण, अणु115, 108पूर्ण, अणु116, 121पूर्ण,
	अणु117, 114पूर्ण, अणु118, 119पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा msm_pinctrl_soc_data sc7180_pinctrl = अणु
	.pins = sc7180_pins,
	.npins = ARRAY_SIZE(sc7180_pins),
	.functions = sc7180_functions,
	.nfunctions = ARRAY_SIZE(sc7180_functions),
	.groups = sc7180_groups,
	.ngroups = ARRAY_SIZE(sc7180_groups),
	.ngpios = 120,
	.tiles = sc7180_tiles,
	.ntiles = ARRAY_SIZE(sc7180_tiles),
	.wakeirq_map = sc7180_pdc_map,
	.nwakeirq_map = ARRAY_SIZE(sc7180_pdc_map),
	.wakeirq_dual_edge_errata = true,
पूर्ण;

अटल पूर्णांक sc7180_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस msm_pinctrl_probe(pdev, &sc7180_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id sc7180_pinctrl_of_match[] = अणु
	अणु .compatible = "qcom,sc7180-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sc7180_pinctrl_driver = अणु
	.driver = अणु
		.name = "sc7180-pinctrl",
		.pm = &msm_pinctrl_dev_pm_ops,
		.of_match_table = sc7180_pinctrl_of_match,
	पूर्ण,
	.probe = sc7180_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init sc7180_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sc7180_pinctrl_driver);
पूर्ण
arch_initcall(sc7180_pinctrl_init);

अटल व्योम __निकास sc7180_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sc7180_pinctrl_driver);
पूर्ण
module_निकास(sc7180_pinctrl_निकास);

MODULE_DESCRIPTION("QTI sc7180 pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, sc7180_pinctrl_of_match);
