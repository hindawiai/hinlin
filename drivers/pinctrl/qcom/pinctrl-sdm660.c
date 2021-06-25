<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016, The Linux Foundation. All rights reserved.
 * Copyright (c) 2018, Craig Tatlor.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>

#समावेश "pinctrl-msm.h"

अटल स्थिर अक्षर * स्थिर sdm660_tiles[] = अणु
	"north",
	"center",
	"south"
पूर्ण;

क्रमागत अणु
	NORTH,
	CENTER,
	SOUTH
पूर्ण;

#घोषणा REG_SIZE 0x1000

#घोषणा FUNCTION(fname)					\
	[msm_mux_##fname] = अणु		                \
		.name = #fname,				\
		.groups = fname##_groups,               \
		.ngroups = ARRAY_SIZE(fname##_groups),	\
	पूर्ण


#घोषणा PINGROUP(id, _tile, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
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
		.ctl_reg = REG_SIZE * id,		\
		.io_reg = 0x4 + REG_SIZE * id,		\
		.पूर्णांकr_cfg_reg = 0x8 + REG_SIZE * id,	\
		.पूर्णांकr_status_reg = 0xc + REG_SIZE * id,	\
		.पूर्णांकr_target_reg = 0x8 + REG_SIZE * id,	\
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
	अणु					        \
		.name = #pg_name,			\
		.pins = pg_name##_pins,			\
		.npins = (अचिन्हित)ARRAY_SIZE(pg_name##_pins),	\
		.ctl_reg = ctl,				\
		.io_reg = 0,				\
		.पूर्णांकr_cfg_reg = 0,			\
		.पूर्णांकr_status_reg = 0,			\
		.पूर्णांकr_target_reg = 0,			\
		.tile = NORTH,				\
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

अटल स्थिर काष्ठा pinctrl_pin_desc sdm660_pins[] = अणु
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
	PINCTRL_PIN(114, "SDC1_CLK"),
	PINCTRL_PIN(115, "SDC1_CMD"),
	PINCTRL_PIN(116, "SDC1_DATA"),
	PINCTRL_PIN(117, "SDC2_CLK"),
	PINCTRL_PIN(118, "SDC2_CMD"),
	PINCTRL_PIN(119, "SDC2_DATA"),
	PINCTRL_PIN(120, "SDC1_RCLK"),
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

अटल स्थिर अचिन्हित पूर्णांक sdc1_clk_pins[] = अणु 114 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_cmd_pins[] = अणु 115 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_data_pins[] = अणु 116 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc1_rclk_pins[] = अणु 120 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_clk_pins[] = अणु 117 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_cmd_pins[] = अणु 118 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdc2_data_pins[] = अणु 119 पूर्ण;

क्रमागत sdm660_functions अणु
	msm_mux_adsp_ext,
	msm_mux_agera_pll,
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
	msm_mux_blsp_i2c1,
	msm_mux_blsp_i2c2,
	msm_mux_blsp_i2c3,
	msm_mux_blsp_i2c4,
	msm_mux_blsp_i2c5,
	msm_mux_blsp_i2c6,
	msm_mux_blsp_i2c7,
	msm_mux_blsp_i2c8_a,
	msm_mux_blsp_i2c8_b,
	msm_mux_blsp_spi1,
	msm_mux_blsp_spi2,
	msm_mux_blsp_spi3,
	msm_mux_blsp_spi3_cs1,
	msm_mux_blsp_spi3_cs2,
	msm_mux_blsp_spi4,
	msm_mux_blsp_spi5,
	msm_mux_blsp_spi6,
	msm_mux_blsp_spi7,
	msm_mux_blsp_spi8_a,
	msm_mux_blsp_spi8_b,
	msm_mux_blsp_spi8_cs1,
	msm_mux_blsp_spi8_cs2,
	msm_mux_blsp_uart1,
	msm_mux_blsp_uart2,
	msm_mux_blsp_uart5,
	msm_mux_blsp_uart6_a,
	msm_mux_blsp_uart6_b,
	msm_mux_blsp_uim1,
	msm_mux_blsp_uim2,
	msm_mux_blsp_uim5,
	msm_mux_blsp_uim6,
	msm_mux_cam_mclk,
	msm_mux_cci_async,
	msm_mux_cci_i2c,
	msm_mux_cri_trng,
	msm_mux_cri_trng0,
	msm_mux_cri_trng1,
	msm_mux_dbg_out,
	msm_mux_ddr_bist,
	msm_mux_gcc_gp1,
	msm_mux_gcc_gp2,
	msm_mux_gcc_gp3,
	msm_mux_gpio,
	msm_mux_gps_tx_a,
	msm_mux_gps_tx_b,
	msm_mux_gps_tx_c,
	msm_mux_isense_dbg,
	msm_mux_jitter_bist,
	msm_mux_lकरो_en,
	msm_mux_lकरो_update,
	msm_mux_m_voc,
	msm_mux_mdp_vsync,
	msm_mux_mdss_vsync0,
	msm_mux_mdss_vsync1,
	msm_mux_mdss_vsync2,
	msm_mux_mdss_vsync3,
	msm_mux_mss_lte,
	msm_mux_nav_pps_a,
	msm_mux_nav_pps_b,
	msm_mux_nav_pps_c,
	msm_mux_pa_indicator,
	msm_mux_phase_flag0,
	msm_mux_phase_flag1,
	msm_mux_phase_flag2,
	msm_mux_phase_flag3,
	msm_mux_phase_flag4,
	msm_mux_phase_flag5,
	msm_mux_phase_flag6,
	msm_mux_phase_flag7,
	msm_mux_phase_flag8,
	msm_mux_phase_flag9,
	msm_mux_phase_flag10,
	msm_mux_phase_flag11,
	msm_mux_phase_flag12,
	msm_mux_phase_flag13,
	msm_mux_phase_flag14,
	msm_mux_phase_flag15,
	msm_mux_phase_flag16,
	msm_mux_phase_flag17,
	msm_mux_phase_flag18,
	msm_mux_phase_flag19,
	msm_mux_phase_flag20,
	msm_mux_phase_flag21,
	msm_mux_phase_flag22,
	msm_mux_phase_flag23,
	msm_mux_phase_flag24,
	msm_mux_phase_flag25,
	msm_mux_phase_flag26,
	msm_mux_phase_flag27,
	msm_mux_phase_flag28,
	msm_mux_phase_flag29,
	msm_mux_phase_flag30,
	msm_mux_phase_flag31,
	msm_mux_pll_bypassnl,
	msm_mux_pll_reset,
	msm_mux_pri_mi2s,
	msm_mux_pri_mi2s_ws,
	msm_mux_prng_rosc,
	msm_mux_pwr_crypto,
	msm_mux_pwr_modem,
	msm_mux_pwr_nav,
	msm_mux_qdss_cti0_a,
	msm_mux_qdss_cti0_b,
	msm_mux_qdss_cti1_a,
	msm_mux_qdss_cti1_b,
	msm_mux_qdss_gpio,
	msm_mux_qdss_gpio0,
	msm_mux_qdss_gpio1,
	msm_mux_qdss_gpio10,
	msm_mux_qdss_gpio11,
	msm_mux_qdss_gpio12,
	msm_mux_qdss_gpio13,
	msm_mux_qdss_gpio14,
	msm_mux_qdss_gpio15,
	msm_mux_qdss_gpio2,
	msm_mux_qdss_gpio3,
	msm_mux_qdss_gpio4,
	msm_mux_qdss_gpio5,
	msm_mux_qdss_gpio6,
	msm_mux_qdss_gpio7,
	msm_mux_qdss_gpio8,
	msm_mux_qdss_gpio9,
	msm_mux_qlink_enable,
	msm_mux_qlink_request,
	msm_mux_qspi_clk,
	msm_mux_qspi_cs,
	msm_mux_qspi_data0,
	msm_mux_qspi_data1,
	msm_mux_qspi_data2,
	msm_mux_qspi_data3,
	msm_mux_qspi_resetn,
	msm_mux_sec_mi2s,
	msm_mux_sndwire_clk,
	msm_mux_sndwire_data,
	msm_mux_sp_cmu,
	msm_mux_ssc_irq,
	msm_mux_tgu_ch0,
	msm_mux_tgu_ch1,
	msm_mux_tsense_pwm1,
	msm_mux_tsense_pwm2,
	msm_mux_uim1_clk,
	msm_mux_uim1_data,
	msm_mux_uim1_present,
	msm_mux_uim1_reset,
	msm_mux_uim2_clk,
	msm_mux_uim2_data,
	msm_mux_uim2_present,
	msm_mux_uim2_reset,
	msm_mux_uim_batt,
	msm_mux_vfr_1,
	msm_mux_vsense_clkout,
	msm_mux_vsense_data0,
	msm_mux_vsense_data1,
	msm_mux_vsense_mode,
	msm_mux_wlan1_adc0,
	msm_mux_wlan1_adc1,
	msm_mux_wlan2_adc0,
	msm_mux_wlan2_adc1,
	msm_mux__,
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
	"gpio111", "gpio112", "gpio113",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adsp_ext_groups[] = अणु
	"gpio65",
पूर्ण;
अटल स्थिर अक्षर * स्थिर agera_pll_groups[] = अणु
	"gpio34", "gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर0_groups[] = अणु
	"gpio62",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर1_groups[] = अणु
	"gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर2_groups[] = अणु
	"gpio60",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर3_groups[] = अणु
	"gpio59",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_अक्षर_groups[] = अणु
	"gpio58",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_gpsadc0_groups[] = अणु
	"gpio1",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_gpsadc1_groups[] = अणु
	"gpio0",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens2_groups[] = अणु
	"gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_tsens_groups[] = अणु
	"gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb10_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb11_groups[] = अणु
	"gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb12_groups[] = अणु
	"gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb13_groups[] = अणु
	"gpio8",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb1_groups[] = अणु
	"gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb20_groups[] = अणु
	"gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb21_groups[] = अणु
	"gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb22_groups[] = अणु
	"gpio57",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb23_groups[] = अणु
	"gpio37",
पूर्ण;
अटल स्थिर अक्षर * स्थिर atest_usb2_groups[] = अणु
	"gpio35",
पूर्ण;
अटल स्थिर अक्षर * स्थिर audio_ref_groups[] = अणु
	"gpio62",
पूर्ण;
अटल स्थिर अक्षर * स्थिर bimc_dte0_groups[] = अणु
	"gpio9", "gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर bimc_dte1_groups[] = अणु
	"gpio8", "gpio10",
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
	"gpio26", "gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c8_a_groups[] = अणु
	"gpio30", "gpio31",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_i2c8_b_groups[] = अणु
	"gpio44", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi1_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3", "gpio46",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi2_groups[] = अणु
	"gpio4", "gpio5", "gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi3_cs1_groups[] = अणु
	"gpio30",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi3_cs2_groups[] = अणु
	"gpio65",
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
	"gpio49", "gpio52", "gpio22", "gpio23",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi7_groups[] = अणु
	"gpio24", "gpio25", "gpio26", "gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi8_a_groups[] = अणु
	"gpio28", "gpio29", "gpio30", "gpio31",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi8_b_groups[] = अणु
	"gpio40", "gpio41", "gpio44", "gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi8_cs1_groups[] = अणु
	"gpio64",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_spi8_cs2_groups[] = अणु
	"gpio76",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart1_groups[] = अणु
	"gpio0", "gpio1", "gpio2", "gpio3",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart2_groups[] = अणु
	"gpio4", "gpio5", "gpio6", "gpio7",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart5_groups[] = अणु
	"gpio16", "gpio17", "gpio18", "gpio19",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart6_a_groups[] = अणु
	"gpio24", "gpio25", "gpio26", "gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uart6_b_groups[] = अणु
	"gpio28", "gpio29", "gpio30", "gpio31",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim1_groups[] = अणु
	"gpio0", "gpio1",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim2_groups[] = अणु
	"gpio4", "gpio5",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim5_groups[] = अणु
	"gpio16", "gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर blsp_uim6_groups[] = अणु
	"gpio20", "gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cam_mclk_groups[] = अणु
	"gpio32", "gpio33", "gpio34", "gpio35",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_async_groups[] = अणु
	"gpio45",
पूर्ण;
अटल स्थिर अक्षर * स्थिर cci_i2c_groups[] = अणु
	"gpio36", "gpio37", "gpio38", "gpio39",
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
अटल स्थिर अक्षर * स्थिर dbg_out_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ddr_bist_groups[] = अणु
	"gpio3", "gpio8", "gpio9", "gpio10",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp1_groups[] = अणु
	"gpio57", "gpio78",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp2_groups[] = अणु
	"gpio58", "gpio81",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gcc_gp3_groups[] = अणु
	"gpio59", "gpio82",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gps_tx_a_groups[] = अणु
	"gpio65",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gps_tx_b_groups[] = अणु
	"gpio98",
पूर्ण;
अटल स्थिर अक्षर * स्थिर gps_tx_c_groups[] = अणु
	"gpio80",
पूर्ण;
अटल स्थिर अक्षर * स्थिर isense_dbg_groups[] = अणु
	"gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर jitter_bist_groups[] = अणु
	"gpio35",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_en_groups[] = अणु
	"gpio97",
पूर्ण;
अटल स्थिर अक्षर * स्थिर lकरो_update_groups[] = अणु
	"gpio98",
पूर्ण;
अटल स्थिर अक्षर * स्थिर m_voc_groups[] = अणु
	"gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdp_vsync_groups[] = अणु
	"gpio59", "gpio74",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdss_vsync0_groups[] = अणु
	"gpio42",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdss_vsync1_groups[] = अणु
	"gpio42",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdss_vsync2_groups[] = अणु
	"gpio42",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mdss_vsync3_groups[] = अणु
	"gpio42",
पूर्ण;
अटल स्थिर अक्षर * स्थिर mss_lte_groups[] = अणु
	"gpio81", "gpio82",
पूर्ण;
अटल स्थिर अक्षर * स्थिर nav_pps_a_groups[] = अणु
	"gpio65",
पूर्ण;
अटल स्थिर अक्षर * स्थिर nav_pps_b_groups[] = अणु
	"gpio98",
पूर्ण;
अटल स्थिर अक्षर * स्थिर nav_pps_c_groups[] = अणु
	"gpio80",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pa_indicator_groups[] = अणु
	"gpio92",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag0_groups[] = अणु
	"gpio68",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag1_groups[] = अणु
	"gpio48",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag2_groups[] = अणु
	"gpio49",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag3_groups[] = अणु
	"gpio4",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag4_groups[] = अणु
	"gpio57",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag5_groups[] = अणु
	"gpio17",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag6_groups[] = अणु
	"gpio53",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag7_groups[] = अणु
	"gpio69",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag8_groups[] = अणु
	"gpio70",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag9_groups[] = अणु
	"gpio50",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag10_groups[] = अणु
	"gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag11_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag12_groups[] = अणु
	"gpio22",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag13_groups[] = अणु
	"gpio23",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag14_groups[] = अणु
	"gpio5",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag15_groups[] = अणु
	"gpio51",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag16_groups[] = अणु
	"gpio52",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag17_groups[] = अणु
	"gpio24",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag18_groups[] = अणु
	"gpio25",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag19_groups[] = अणु
	"gpio26",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag20_groups[] = अणु
	"gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag21_groups[] = अणु
	"gpio28",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag22_groups[] = अणु
	"gpio29",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag23_groups[] = अणु
	"gpio30",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag24_groups[] = अणु
	"gpio31",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag25_groups[] = अणु
	"gpio55",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag26_groups[] = अणु
	"gpio12",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag27_groups[] = अणु
	"gpio13",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag28_groups[] = अणु
	"gpio14",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag29_groups[] = अणु
	"gpio54",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag30_groups[] = अणु
	"gpio47",
पूर्ण;
अटल स्थिर अक्षर * स्थिर phase_flag31_groups[] = अणु
	"gpio6",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_bypassnl_groups[] = अणु
	"gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pll_reset_groups[] = अणु
	"gpio37",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pri_mi2s_groups[] = अणु
	"gpio12", "gpio14", "gpio15", "gpio61",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pri_mi2s_ws_groups[] = अणु
	"gpio13",
पूर्ण;
अटल स्थिर अक्षर * स्थिर prng_rosc_groups[] = अणु
	"gpio102",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pwr_crypto_groups[] = अणु
	"gpio33",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pwr_modem_groups[] = अणु
	"gpio31",
पूर्ण;
अटल स्थिर अक्षर * स्थिर pwr_nav_groups[] = अणु
	"gpio32",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti0_a_groups[] = अणु
	"gpio49", "gpio50",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti0_b_groups[] = अणु
	"gpio13", "gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti1_a_groups[] = अणु
	"gpio53", "gpio55",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_cti1_b_groups[] = अणु
	"gpio12", "gpio66",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio0_groups[] = अणु
	"gpio32", "gpio67",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio10_groups[] = अणु
	"gpio43", "gpio77",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio11_groups[] = अणु
	"gpio44", "gpio79",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio12_groups[] = अणु
	"gpio45", "gpio80",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio13_groups[] = अणु
	"gpio46", "gpio78",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio14_groups[] = अणु
	"gpio47", "gpio72",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio15_groups[] = अणु
	"gpio48", "gpio73",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio1_groups[] = अणु
	"gpio33", "gpio63",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio2_groups[] = अणु
	"gpio34", "gpio64",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio3_groups[] = अणु
	"gpio35", "gpio56",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio4_groups[] = अणु
	"gpio0", "gpio36",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio5_groups[] = अणु
	"gpio1", "gpio37",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio6_groups[] = अणु
	"gpio38", "gpio70",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio7_groups[] = अणु
	"gpio39", "gpio71",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio8_groups[] = अणु
	"gpio51", "gpio75",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio9_groups[] = अणु
	"gpio42", "gpio76",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qdss_gpio_groups[] = अणु
	"gpio31", "gpio52", "gpio68", "gpio69",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qlink_enable_groups[] = अणु
	"gpio100",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qlink_request_groups[] = अणु
	"gpio99",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_clk_groups[] = अणु
	"gpio47",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_cs_groups[] = अणु
	"gpio43", "gpio50",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_data0_groups[] = अणु
	"gpio33",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_data1_groups[] = अणु
	"gpio34",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_data2_groups[] = अणु
	"gpio35",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_data3_groups[] = अणु
	"gpio51",
पूर्ण;
अटल स्थिर अक्षर * स्थिर qspi_resetn_groups[] = अणु
	"gpio48",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sec_mi2s_groups[] = अणु
	"gpio24", "gpio25", "gpio26", "gpio27", "gpio62",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sndwire_clk_groups[] = अणु
	"gpio24",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sndwire_data_groups[] = अणु
	"gpio25",
पूर्ण;
अटल स्थिर अक्षर * स्थिर sp_cmu_groups[] = अणु
	"gpio64",
पूर्ण;
अटल स्थिर अक्षर * स्थिर ssc_irq_groups[] = अणु
	"gpio67", "gpio68", "gpio69", "gpio70", "gpio71", "gpio72", "gpio74",
	"gpio75", "gpio76",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch0_groups[] = अणु
	"gpio0",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tgu_ch1_groups[] = अणु
	"gpio1",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsense_pwm1_groups[] = अणु
	"gpio71",
पूर्ण;
अटल स्थिर अक्षर * स्थिर tsense_pwm2_groups[] = अणु
	"gpio71",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_clk_groups[] = अणु
	"gpio88",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_data_groups[] = अणु
	"gpio87",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_present_groups[] = अणु
	"gpio90",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim1_reset_groups[] = अणु
	"gpio89",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_clk_groups[] = अणु
	"gpio84",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_data_groups[] = अणु
	"gpio83",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_present_groups[] = अणु
	"gpio86",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim2_reset_groups[] = अणु
	"gpio85",
पूर्ण;
अटल स्थिर अक्षर * स्थिर uim_batt_groups[] = अणु
	"gpio91",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vfr_1_groups[] = अणु
	"gpio27",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vsense_clkout_groups[] = अणु
	"gpio24",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vsense_data0_groups[] = अणु
	"gpio21",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vsense_data1_groups[] = अणु
	"gpio22",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vsense_mode_groups[] = अणु
	"gpio23",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan1_adc0_groups[] = अणु
	"gpio9",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan1_adc1_groups[] = अणु
	"gpio8",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan2_adc0_groups[] = अणु
	"gpio11",
पूर्ण;
अटल स्थिर अक्षर * स्थिर wlan2_adc1_groups[] = अणु
	"gpio10",
पूर्ण;

अटल स्थिर काष्ठा msm_function sdm660_functions[] = अणु
	FUNCTION(adsp_ext),
	FUNCTION(agera_pll),
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
	FUNCTION(blsp_i2c1),
	FUNCTION(blsp_i2c2),
	FUNCTION(blsp_i2c3),
	FUNCTION(blsp_i2c4),
	FUNCTION(blsp_i2c5),
	FUNCTION(blsp_i2c6),
	FUNCTION(blsp_i2c7),
	FUNCTION(blsp_i2c8_a),
	FUNCTION(blsp_i2c8_b),
	FUNCTION(blsp_spi1),
	FUNCTION(blsp_spi2),
	FUNCTION(blsp_spi3),
	FUNCTION(blsp_spi3_cs1),
	FUNCTION(blsp_spi3_cs2),
	FUNCTION(blsp_spi4),
	FUNCTION(blsp_spi5),
	FUNCTION(blsp_spi6),
	FUNCTION(blsp_spi7),
	FUNCTION(blsp_spi8_a),
	FUNCTION(blsp_spi8_b),
	FUNCTION(blsp_spi8_cs1),
	FUNCTION(blsp_spi8_cs2),
	FUNCTION(blsp_uart1),
	FUNCTION(blsp_uart2),
	FUNCTION(blsp_uart5),
	FUNCTION(blsp_uart6_a),
	FUNCTION(blsp_uart6_b),
	FUNCTION(blsp_uim1),
	FUNCTION(blsp_uim2),
	FUNCTION(blsp_uim5),
	FUNCTION(blsp_uim6),
	FUNCTION(cam_mclk),
	FUNCTION(cci_async),
	FUNCTION(cci_i2c),
	FUNCTION(cri_trng),
	FUNCTION(cri_trng0),
	FUNCTION(cri_trng1),
	FUNCTION(dbg_out),
	FUNCTION(ddr_bist),
	FUNCTION(gcc_gp1),
	FUNCTION(gcc_gp2),
	FUNCTION(gcc_gp3),
	FUNCTION(gpio),
	FUNCTION(gps_tx_a),
	FUNCTION(gps_tx_b),
	FUNCTION(gps_tx_c),
	FUNCTION(isense_dbg),
	FUNCTION(jitter_bist),
	FUNCTION(lकरो_en),
	FUNCTION(lकरो_update),
	FUNCTION(m_voc),
	FUNCTION(mdp_vsync),
	FUNCTION(mdss_vsync0),
	FUNCTION(mdss_vsync1),
	FUNCTION(mdss_vsync2),
	FUNCTION(mdss_vsync3),
	FUNCTION(mss_lte),
	FUNCTION(nav_pps_a),
	FUNCTION(nav_pps_b),
	FUNCTION(nav_pps_c),
	FUNCTION(pa_indicator),
	FUNCTION(phase_flag0),
	FUNCTION(phase_flag1),
	FUNCTION(phase_flag2),
	FUNCTION(phase_flag3),
	FUNCTION(phase_flag4),
	FUNCTION(phase_flag5),
	FUNCTION(phase_flag6),
	FUNCTION(phase_flag7),
	FUNCTION(phase_flag8),
	FUNCTION(phase_flag9),
	FUNCTION(phase_flag10),
	FUNCTION(phase_flag11),
	FUNCTION(phase_flag12),
	FUNCTION(phase_flag13),
	FUNCTION(phase_flag14),
	FUNCTION(phase_flag15),
	FUNCTION(phase_flag16),
	FUNCTION(phase_flag17),
	FUNCTION(phase_flag18),
	FUNCTION(phase_flag19),
	FUNCTION(phase_flag20),
	FUNCTION(phase_flag21),
	FUNCTION(phase_flag22),
	FUNCTION(phase_flag23),
	FUNCTION(phase_flag24),
	FUNCTION(phase_flag25),
	FUNCTION(phase_flag26),
	FUNCTION(phase_flag27),
	FUNCTION(phase_flag28),
	FUNCTION(phase_flag29),
	FUNCTION(phase_flag30),
	FUNCTION(phase_flag31),
	FUNCTION(pll_bypassnl),
	FUNCTION(pll_reset),
	FUNCTION(pri_mi2s),
	FUNCTION(pri_mi2s_ws),
	FUNCTION(prng_rosc),
	FUNCTION(pwr_crypto),
	FUNCTION(pwr_modem),
	FUNCTION(pwr_nav),
	FUNCTION(qdss_cti0_a),
	FUNCTION(qdss_cti0_b),
	FUNCTION(qdss_cti1_a),
	FUNCTION(qdss_cti1_b),
	FUNCTION(qdss_gpio),
	FUNCTION(qdss_gpio0),
	FUNCTION(qdss_gpio1),
	FUNCTION(qdss_gpio10),
	FUNCTION(qdss_gpio11),
	FUNCTION(qdss_gpio12),
	FUNCTION(qdss_gpio13),
	FUNCTION(qdss_gpio14),
	FUNCTION(qdss_gpio15),
	FUNCTION(qdss_gpio2),
	FUNCTION(qdss_gpio3),
	FUNCTION(qdss_gpio4),
	FUNCTION(qdss_gpio5),
	FUNCTION(qdss_gpio6),
	FUNCTION(qdss_gpio7),
	FUNCTION(qdss_gpio8),
	FUNCTION(qdss_gpio9),
	FUNCTION(qlink_enable),
	FUNCTION(qlink_request),
	FUNCTION(qspi_clk),
	FUNCTION(qspi_cs),
	FUNCTION(qspi_data0),
	FUNCTION(qspi_data1),
	FUNCTION(qspi_data2),
	FUNCTION(qspi_data3),
	FUNCTION(qspi_resetn),
	FUNCTION(sec_mi2s),
	FUNCTION(sndwire_clk),
	FUNCTION(sndwire_data),
	FUNCTION(sp_cmu),
	FUNCTION(ssc_irq),
	FUNCTION(tgu_ch0),
	FUNCTION(tgu_ch1),
	FUNCTION(tsense_pwm1),
	FUNCTION(tsense_pwm2),
	FUNCTION(uim1_clk),
	FUNCTION(uim1_data),
	FUNCTION(uim1_present),
	FUNCTION(uim1_reset),
	FUNCTION(uim2_clk),
	FUNCTION(uim2_data),
	FUNCTION(uim2_present),
	FUNCTION(uim2_reset),
	FUNCTION(uim_batt),
	FUNCTION(vfr_1),
	FUNCTION(vsense_clkout),
	FUNCTION(vsense_data0),
	FUNCTION(vsense_data1),
	FUNCTION(vsense_mode),
	FUNCTION(wlan1_adc0),
	FUNCTION(wlan1_adc1),
	FUNCTION(wlan2_adc0),
	FUNCTION(wlan2_adc1),
पूर्ण;

अटल स्थिर काष्ठा msm_pingroup sdm660_groups[] = अणु
	PINGROUP(0, SOUTH, blsp_spi1, blsp_uart1, blsp_uim1, tgu_ch0, _, _, qdss_gpio4, atest_gpsadc1, _),
	PINGROUP(1, SOUTH, blsp_spi1, blsp_uart1, blsp_uim1, tgu_ch1, _, _, qdss_gpio5, atest_gpsadc0, _),
	PINGROUP(2, SOUTH, blsp_spi1, blsp_uart1, blsp_i2c1, _, _, _, _, _, _),
	PINGROUP(3, SOUTH, blsp_spi1, blsp_uart1, blsp_i2c1, ddr_bist, _, _, atest_tsens2, atest_usb1, _),
	PINGROUP(4, NORTH, blsp_spi2, blsp_uim2, blsp_uart2, phase_flag3, _, _, _, _, _),
	PINGROUP(5, SOUTH, blsp_spi2, blsp_uim2, blsp_uart2, phase_flag14, _, _, _, _, _),
	PINGROUP(6, SOUTH, blsp_spi2, blsp_i2c2, blsp_uart2, phase_flag31, _, _, _, _, _),
	PINGROUP(7, SOUTH, blsp_spi2, blsp_i2c2, blsp_uart2, _, _, _, _, _, _),
	PINGROUP(8, NORTH, blsp_spi3, ddr_bist, _, _, _, wlan1_adc1, atest_usb13, bimc_dte1, _),
	PINGROUP(9, NORTH, blsp_spi3, ddr_bist, _, _, _, wlan1_adc0, atest_usb12, bimc_dte0, _),
	PINGROUP(10, NORTH, blsp_spi3, blsp_i2c3, ddr_bist, _, _, wlan2_adc1, atest_usb11, bimc_dte1, _),
	PINGROUP(11, NORTH, blsp_spi3, blsp_i2c3, _, dbg_out, wlan2_adc0, atest_usb10, bimc_dte0, _, _),
	PINGROUP(12, NORTH, blsp_spi4, pri_mi2s, _, phase_flag26, qdss_cti1_b, _, _, _, _),
	PINGROUP(13, NORTH, blsp_spi4, _, pri_mi2s_ws, _, _, phase_flag27, qdss_cti0_b, _, _),
	PINGROUP(14, NORTH, blsp_spi4, blsp_i2c4, pri_mi2s, _, phase_flag28, _, _, _, _),
	PINGROUP(15, NORTH, blsp_spi4, blsp_i2c4, pri_mi2s, _, _, _, _, _, _),
	PINGROUP(16, CENTER, blsp_uart5, blsp_spi5, blsp_uim5, _, _, _, _, _, _),
	PINGROUP(17, CENTER, blsp_uart5, blsp_spi5, blsp_uim5, _, phase_flag5, _, _, _, _),
	PINGROUP(18, CENTER, blsp_uart5, blsp_spi5, blsp_i2c5, _, _, _, _, _, _),
	PINGROUP(19, CENTER, blsp_uart5, blsp_spi5, blsp_i2c5, _, _, _, _, _, _),
	PINGROUP(20, SOUTH, _, _, blsp_uim6, _, _, _, _, _, _),
	PINGROUP(21, SOUTH, _, _, blsp_uim6, _, phase_flag11, qdss_cti0_b, vsense_data0, _, _),
	PINGROUP(22, CENTER, blsp_spi6, _, blsp_i2c6, _, phase_flag12, vsense_data1, _, _, _),
	PINGROUP(23, CENTER, blsp_spi6, _, blsp_i2c6, _, phase_flag13, vsense_mode, _, _, _),
	PINGROUP(24, NORTH, blsp_spi7, blsp_uart6_a, sec_mi2s, sndwire_clk, _, _, phase_flag17, vsense_clkout, _),
	PINGROUP(25, NORTH, blsp_spi7, blsp_uart6_a, sec_mi2s, sndwire_data, _, _, phase_flag18, _, _),
	PINGROUP(26, NORTH, blsp_spi7, blsp_uart6_a, blsp_i2c7, sec_mi2s, _, phase_flag19, _, _, _),
	PINGROUP(27, NORTH, blsp_spi7, blsp_uart6_a, blsp_i2c7, vfr_1, sec_mi2s, _, phase_flag20, _, _),
	PINGROUP(28, CENTER, blsp_spi8_a, blsp_uart6_b, m_voc, _, phase_flag21, _, _, _, _),
	PINGROUP(29, CENTER, blsp_spi8_a, blsp_uart6_b, _, _, phase_flag22, _, _, _, _),
	PINGROUP(30, CENTER, blsp_spi8_a, blsp_uart6_b, blsp_i2c8_a, blsp_spi3_cs1, _, phase_flag23, _, _, _),
	PINGROUP(31, CENTER, blsp_spi8_a, blsp_uart6_b, blsp_i2c8_a, pwr_modem, _, phase_flag24, qdss_gpio, _, _),
	PINGROUP(32, SOUTH, cam_mclk, pwr_nav, _, _, qdss_gpio0, _, _, _, _),
	PINGROUP(33, SOUTH, cam_mclk, qspi_data0, pwr_crypto, _, _, qdss_gpio1, _, _, _),
	PINGROUP(34, SOUTH, cam_mclk, qspi_data1, agera_pll, _, _, qdss_gpio2, _, _, _),
	PINGROUP(35, SOUTH, cam_mclk, qspi_data2, jitter_bist, _, _, qdss_gpio3, _, atest_usb2, _),
	PINGROUP(36, SOUTH, cci_i2c, pll_bypassnl, agera_pll, _, _, qdss_gpio4, atest_tsens, atest_usb21, _),
	PINGROUP(37, SOUTH, cci_i2c, pll_reset, _, _, qdss_gpio5, atest_usb23, _, _, _),
	PINGROUP(38, SOUTH, cci_i2c, _, _, qdss_gpio6, _, _, _, _, _),
	PINGROUP(39, SOUTH, cci_i2c, _, _, qdss_gpio7, _, _, _, _, _),
	PINGROUP(40, SOUTH, _, _, blsp_spi8_b, _, _, _, _, _, _),
	PINGROUP(41, SOUTH, _, _, blsp_spi8_b, _, _, _, _, _, _),
	PINGROUP(42, SOUTH, mdss_vsync0, mdss_vsync1, mdss_vsync2, mdss_vsync3, _, _, qdss_gpio9, _, _),
	PINGROUP(43, SOUTH, _, _, qspi_cs, _, _, qdss_gpio10, _, _, _),
	PINGROUP(44, SOUTH, _, _, blsp_spi8_b, blsp_i2c8_b, _, _, qdss_gpio11, _, _),
	PINGROUP(45, SOUTH, cci_async, _, _, qdss_gpio12, _, _, _, _, _),
	PINGROUP(46, SOUTH, blsp_spi1, _, _, qdss_gpio13, _, _, _, _, _),
	PINGROUP(47, SOUTH, qspi_clk, _, phase_flag30, qdss_gpio14, _, _, _, _, _),
	PINGROUP(48, SOUTH, _, phase_flag1, qdss_gpio15, _, _, _, _, _, _),
	PINGROUP(49, SOUTH, blsp_spi6, phase_flag2, qdss_cti0_a, _, _, _, _, _, _),
	PINGROUP(50, SOUTH, qspi_cs, _, phase_flag9, qdss_cti0_a, _, _, _, _, _),
	PINGROUP(51, SOUTH, qspi_data3, _, phase_flag15, qdss_gpio8, _, _, _, _, _),
	PINGROUP(52, SOUTH, _, blsp_spi8_b, blsp_i2c8_b, blsp_spi6, phase_flag16, qdss_gpio, _, _, _),
	PINGROUP(53, NORTH, _, phase_flag6, qdss_cti1_a, _, _, _, _, _, _),
	PINGROUP(54, NORTH, _, _, phase_flag29, _, _, _, _, _, _),
	PINGROUP(55, SOUTH, _, phase_flag25, qdss_cti1_a, _, _, _, _, _, _),
	PINGROUP(56, SOUTH, _, phase_flag10, qdss_gpio3, _, atest_usb20, _, _, _, _),
	PINGROUP(57, SOUTH, gcc_gp1, _, phase_flag4, atest_usb22, _, _, _, _, _),
	PINGROUP(58, SOUTH, _, gcc_gp2, _, _, atest_अक्षर, _, _, _, _),
	PINGROUP(59, NORTH, mdp_vsync, gcc_gp3, _, _, atest_अक्षर3, _, _, _, _),
	PINGROUP(60, NORTH, cri_trng0, _, _, atest_अक्षर2, _, _, _, _, _),
	PINGROUP(61, NORTH, pri_mi2s, cri_trng1, _, _, atest_अक्षर1, _, _, _, _),
	PINGROUP(62, NORTH, sec_mi2s, audio_ref, _, cri_trng, _, _, atest_अक्षर0, _, _),
	PINGROUP(63, NORTH, _, _, _, qdss_gpio1, _, _, _, _, _),
	PINGROUP(64, SOUTH, blsp_spi8_cs1, sp_cmu, _, _, qdss_gpio2, _, _, _, _),
	PINGROUP(65, SOUTH, _, nav_pps_a, nav_pps_a, gps_tx_a, blsp_spi3_cs2, adsp_ext, _, _, _),
	PINGROUP(66, NORTH, _, _, qdss_cti1_b, _, _, _, _, _, _),
	PINGROUP(67, NORTH, _, _, qdss_gpio0, _, _, _, _, _, _),
	PINGROUP(68, NORTH, isense_dbg, _, phase_flag0, qdss_gpio, _, _, _, _, _),
	PINGROUP(69, NORTH, _, phase_flag7, qdss_gpio, _, _, _, _, _, _),
	PINGROUP(70, NORTH, _, phase_flag8, qdss_gpio6, _, _, _, _, _, _),
	PINGROUP(71, NORTH, _, _, qdss_gpio7, tsense_pwm1, tsense_pwm2, _, _, _, _),
	PINGROUP(72, NORTH, _, qdss_gpio14, _, _, _, _, _, _, _),
	PINGROUP(73, NORTH, _, _, qdss_gpio15, _, _, _, _, _, _),
	PINGROUP(74, NORTH, mdp_vsync, _, _, _, _, _, _, _, _),
	PINGROUP(75, NORTH, _, _, qdss_gpio8, _, _, _, _, _, _),
	PINGROUP(76, NORTH, blsp_spi8_cs2, _, _, _, qdss_gpio9, _, _, _, _),
	PINGROUP(77, NORTH, _, _, qdss_gpio10, _, _, _, _, _, _),
	PINGROUP(78, NORTH, gcc_gp1, _, qdss_gpio13, _, _, _, _, _, _),
	PINGROUP(79, SOUTH, _, _, qdss_gpio11, _, _, _, _, _, _),
	PINGROUP(80, SOUTH, nav_pps_b, nav_pps_b, gps_tx_c, _, _, qdss_gpio12, _, _, _),
	PINGROUP(81, CENTER, mss_lte, gcc_gp2, _, _, _, _, _, _, _),
	PINGROUP(82, CENTER, mss_lte, gcc_gp3, _, _, _, _, _, _, _),
	PINGROUP(83, SOUTH, uim2_data, _, _, _, _, _, _, _, _),
	PINGROUP(84, SOUTH, uim2_clk, _, _, _, _, _, _, _, _),
	PINGROUP(85, SOUTH, uim2_reset, _, _, _, _, _, _, _, _),
	PINGROUP(86, SOUTH, uim2_present, _, _, _, _, _, _, _, _),
	PINGROUP(87, SOUTH, uim1_data, _, _, _, _, _, _, _, _),
	PINGROUP(88, SOUTH, uim1_clk, _, _, _, _, _, _, _, _),
	PINGROUP(89, SOUTH, uim1_reset, _, _, _, _, _, _, _, _),
	PINGROUP(90, SOUTH, uim1_present, _, _, _, _, _, _, _, _),
	PINGROUP(91, SOUTH, uim_batt, _, _, _, _, _, _, _, _),
	PINGROUP(92, SOUTH, _, _, pa_indicator, _, _, _, _, _, _),
	PINGROUP(93, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(94, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(95, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(96, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(97, SOUTH, _, lकरो_en, _, _, _, _, _, _, _),
	PINGROUP(98, SOUTH, _, nav_pps_c, nav_pps_c, gps_tx_b, lकरो_update, _, _, _, _),
	PINGROUP(99, SOUTH, qlink_request, _, _, _, _, _, _, _, _),
	PINGROUP(100, SOUTH, qlink_enable, _, _, _, _, _, _, _, _),
	PINGROUP(101, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(102, SOUTH, _, prng_rosc, _, _, _, _, _, _, _),
	PINGROUP(103, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(104, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(105, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(106, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(107, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(108, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(109, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(110, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(111, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(112, SOUTH, _, _, _, _, _, _, _, _, _),
	PINGROUP(113, SOUTH, _, _, _, _, _, _, _, _, _),
	SDC_QDSD_PINGROUP(sdc1_clk, 0x9a000, 13, 6),
	SDC_QDSD_PINGROUP(sdc1_cmd, 0x9a000, 11, 3),
	SDC_QDSD_PINGROUP(sdc1_data, 0x9a000, 9, 0),
	SDC_QDSD_PINGROUP(sdc2_clk, 0x9b000, 14, 6),
	SDC_QDSD_PINGROUP(sdc2_cmd, 0x9b000, 11, 3),
	SDC_QDSD_PINGROUP(sdc2_data, 0x9b000, 9, 0),
	SDC_QDSD_PINGROUP(sdc1_rclk, 0x9a000, 15, 0),
पूर्ण;

अटल स्थिर काष्ठा msm_pinctrl_soc_data sdm660_pinctrl = अणु
	.pins = sdm660_pins,
	.npins = ARRAY_SIZE(sdm660_pins),
	.functions = sdm660_functions,
	.nfunctions = ARRAY_SIZE(sdm660_functions),
	.groups = sdm660_groups,
	.ngroups = ARRAY_SIZE(sdm660_groups),
	.ngpios = 114,
	.tiles = sdm660_tiles,
	.ntiles = ARRAY_SIZE(sdm660_tiles),
पूर्ण;

अटल पूर्णांक sdm660_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस msm_pinctrl_probe(pdev, &sdm660_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id sdm660_pinctrl_of_match[] = अणु
	अणु .compatible = "qcom,sdm660-pinctrl", पूर्ण,
	अणु .compatible = "qcom,sdm630-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sdm660_pinctrl_driver = अणु
	.driver = अणु
		.name = "sdm660-pinctrl",
		.of_match_table = sdm660_pinctrl_of_match,
	पूर्ण,
	.probe = sdm660_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init sdm660_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sdm660_pinctrl_driver);
पूर्ण
arch_initcall(sdm660_pinctrl_init);

अटल व्योम __निकास sdm660_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sdm660_pinctrl_driver);
पूर्ण
module_निकास(sdm660_pinctrl_निकास);

MODULE_DESCRIPTION("QTI sdm660 pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, sdm660_pinctrl_of_match);
