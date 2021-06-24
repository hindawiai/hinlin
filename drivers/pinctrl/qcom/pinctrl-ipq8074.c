<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, The Linux Foundation. All rights reserved.
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

#घोषणा REG_SIZE 0x1000
#घोषणा PINGROUP(id, f1, f2, f3, f4, f5, f6, f7, f8, f9)	\
	अणु					        \
		.name = "gpio" #id,			\
		.pins = gpio##id##_pins,		\
		.npins = (अचिन्हित पूर्णांक)ARRAY_SIZE(gpio##id##_pins),	\
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
		.पूर्णांकr_cfg_reg = 0x8 + REG_SIZE * id,		\
		.पूर्णांकr_status_reg = 0xc + REG_SIZE * id,	\
		.पूर्णांकr_target_reg = 0x8 + REG_SIZE * id,	\
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

अटल स्थिर काष्ठा pinctrl_pin_desc ipq8074_pins[] = अणु
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

क्रमागत ipq8074_functions अणु
	msm_mux_atest_अक्षर,
	msm_mux_atest_अक्षर0,
	msm_mux_atest_अक्षर1,
	msm_mux_atest_अक्षर2,
	msm_mux_atest_अक्षर3,
	msm_mux_audio_rxbclk,
	msm_mux_audio_rxd,
	msm_mux_audio_rxfsync,
	msm_mux_audio_rxmclk,
	msm_mux_audio_txbclk,
	msm_mux_audio_txd,
	msm_mux_audio_txfsync,
	msm_mux_audio_txmclk,
	msm_mux_blsp0_i2c,
	msm_mux_blsp0_spi,
	msm_mux_blsp0_uart,
	msm_mux_blsp1_i2c,
	msm_mux_blsp1_spi,
	msm_mux_blsp1_uart,
	msm_mux_blsp2_i2c,
	msm_mux_blsp2_spi,
	msm_mux_blsp2_uart,
	msm_mux_blsp3_i2c,
	msm_mux_blsp3_spi,
	msm_mux_blsp3_spi0,
	msm_mux_blsp3_spi1,
	msm_mux_blsp3_spi2,
	msm_mux_blsp3_spi3,
	msm_mux_blsp3_uart,
	msm_mux_blsp4_i2c0,
	msm_mux_blsp4_i2c1,
	msm_mux_blsp4_spi0,
	msm_mux_blsp4_spi1,
	msm_mux_blsp4_uart0,
	msm_mux_blsp4_uart1,
	msm_mux_blsp5_i2c,
	msm_mux_blsp5_spi,
	msm_mux_blsp5_uart,
	msm_mux_burn0,
	msm_mux_burn1,
	msm_mux_cri_trng,
	msm_mux_cri_trng0,
	msm_mux_cri_trng1,
	msm_mux_cxc0,
	msm_mux_cxc1,
	msm_mux_dbg_out,
	msm_mux_gcc_plltest,
	msm_mux_gcc_tlmm,
	msm_mux_gpio,
	msm_mux_lकरो_en,
	msm_mux_lकरो_update,
	msm_mux_led0,
	msm_mux_led1,
	msm_mux_led2,
	msm_mux_mac0_sa0,
	msm_mux_mac0_sa1,
	msm_mux_mac1_sa0,
	msm_mux_mac1_sa1,
	msm_mux_mac1_sa2,
	msm_mux_mac1_sa3,
	msm_mux_mac2_sa0,
	msm_mux_mac2_sa1,
	msm_mux_mdc,
	msm_mux_mdio,
	msm_mux_pcie0_clk,
	msm_mux_pcie0_rst,
	msm_mux_pcie0_wake,
	msm_mux_pcie1_clk,
	msm_mux_pcie1_rst,
	msm_mux_pcie1_wake,
	msm_mux_pcm_drx,
	msm_mux_pcm_dtx,
	msm_mux_pcm_fsync,
	msm_mux_pcm_pclk,
	msm_mux_pcm_zsi0,
	msm_mux_pcm_zsi1,
	msm_mux_prng_rosc,
	msm_mux_pta1_0,
	msm_mux_pta1_1,
	msm_mux_pta1_2,
	msm_mux_pta2_0,
	msm_mux_pta2_1,
	msm_mux_pta2_2,
	msm_mux_pwm0,
	msm_mux_pwm1,
	msm_mux_pwm2,
	msm_mux_pwm3,
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
	msm_mux_qpic,
	msm_mux_rx0,
	msm_mux_rx1,
	msm_mux_rx2,
	msm_mux_sd_card,
	msm_mux_sd_ग_लिखो,
	msm_mux_tsens_max,
	msm_mux_wci2a,
	msm_mux_wci2b,
	msm_mux_wci2c,
	msm_mux_wci2d,
	msm_mux_NA,
पूर्ण;

अटल स्थिर अक्षर * स्थिर qpic_groups[] = अणु
	"gpio0",	/* LCD_TE */
	"gpio1",	/* BUSY_N */
	"gpio2",	/* LCD_RS_N */
	"gpio3",	/* WE_N */
	"gpio4",	/* OE_N */
	"gpio5",	/* DATA[0] */
	"gpio6",	/* DATA[1] */
	"gpio7",	/* DATA[2] */
	"gpio8",	/* DATA[3] */
	"gpio9",	/* CS_CSR_LCD */
	"gpio10",	/* CLE */
	"gpio11",	/* न_अंकD_CS_N */
	"gpio12",	/* DATA[4] */
	"gpio13",	/* DATA[5] */
	"gpio14",	/* DATA[6] */
	"gpio15",	/* DATA[7] */
	"gpio16",	/* DATA[8] */
	"gpio17",	/* ALE */
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp5_i2c_groups[] = अणु
	"gpio0", "gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp5_spi_groups[] = अणु
	"gpio0", "gpio2", "gpio9", "gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wci2a_groups[] = अणु
	"gpio0", "gpio2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_spi3_groups[] = अणु
	"gpio0", "gpio2", "gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर burn0_groups[] = अणु
	"gpio0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_zsi0_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp5_uart_groups[] = अणु
	"gpio0", "gpio2", "gpio9", "gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac1_sa2_groups[] = अणु
	"gpio1", "gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_spi0_groups[] = अणु
	"gpio1", "gpio3", "gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर burn1_groups[] = अणु
	"gpio1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac0_sa1_groups[] = अणु
	"gpio3", "gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_b0_groups[] = अणु
	"gpio3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_b0_groups[] = अणु
	"gpio4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp4_uart0_groups[] = अणु
	"gpio5", "gpio6", "gpio7", "gpio8",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp4_i2c0_groups[] = अणु
	"gpio5", "gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp4_spi0_groups[] = अणु
	"gpio5", "gpio6", "gpio7", "gpio8",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac2_sa1_groups[] = अणु
	"gpio5", "gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_b1_groups[] = अणु
	"gpio5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_b1_groups[] = अणु
	"gpio6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cxc0_groups[] = अणु
	"gpio9", "gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac1_sa3_groups[] = अणु
	"gpio9", "gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_a1_groups[] = अणु
	"gpio9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_a1_groups[] = अणु
	"gpio10",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wci2c_groups[] = अणु
	"gpio11", "gpio17",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_in_a0_groups[] = अणु
	"gpio11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_cti_trig_out_a0_groups[] = अणु
	"gpio12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_traceclk_b_groups[] = अणु
	"gpio14",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracectl_b_groups[] = अणु
	"gpio15",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_zsi1_groups[] = अणु
	"gpio16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracedata_b_groups[] = अणु
	"gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21", "gpio22",
	"gpio23", "gpio24", "gpio25", "gpio26", "gpio27", "gpio28", "gpio29",
	"gpio30", "gpio31",
पूर्ण;

अटल स्थिर अक्षर * स्थिर led0_groups[] = अणु
	"gpio18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm0_groups[] = अणु
	"gpio18", "gpio21", "gpio25", "gpio29", "gpio63",
पूर्ण;

अटल स्थिर अक्षर * स्थिर led1_groups[] = अणु
	"gpio19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm1_groups[] = अणु
	"gpio19", "gpio22", "gpio26", "gpio30", "gpio64",
पूर्ण;

अटल स्थिर अक्षर * स्थिर led2_groups[] = अणु
	"gpio20",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm2_groups[] = अणु
	"gpio20", "gpio23", "gpio27", "gpio31", "gpio66",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp4_uart1_groups[] = अणु
	"gpio21", "gpio22", "gpio23", "gpio24",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp4_i2c1_groups[] = अणु
	"gpio21", "gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp4_spi1_groups[] = अणु
	"gpio21", "gpio22", "gpio23", "gpio24",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wci2d_groups[] = अणु
	"gpio21", "gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac1_sa1_groups[] = अणु
	"gpio21", "gpio22",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_spi2_groups[] = अणु
	"gpio21", "gpio22", "gpio23",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm3_groups[] = अणु
	"gpio24", "gpio28", "gpio32", "gpio67",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_txmclk_groups[] = अणु
	"gpio25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_txbclk_groups[] = अणु
	"gpio26",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_txfsync_groups[] = अणु
	"gpio27",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_txd_groups[] = अणु
	"gpio28",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_rxmclk_groups[] = अणु
	"gpio29",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर0_groups[] = अणु
	"gpio29",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_rxbclk_groups[] = अणु
	"gpio30",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर1_groups[] = अणु
	"gpio30",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_rxfsync_groups[] = अणु
	"gpio31",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर2_groups[] = अणु
	"gpio31",
पूर्ण;

अटल स्थिर अक्षर * स्थिर audio_rxd_groups[] = अणु
	"gpio32",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर3_groups[] = अणु
	"gpio32",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_drx_groups[] = अणु
	"gpio33",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac1_sa0_groups[] = अणु
	"gpio33", "gpio34",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac0_sa0_groups[] = अणु
	"gpio33", "gpio34",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_dtx_groups[] = अणु
	"gpio34",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_fsync_groups[] = अणु
	"gpio35",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mac2_sa0_groups[] = अणु
	"gpio35", "gpio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_traceclk_a_groups[] = अणु
	"gpio35",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_pclk_groups[] = अणु
	"gpio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracectl_a_groups[] = अणु
	"gpio36",
पूर्ण;

अटल स्थिर अक्षर * स्थिर atest_अक्षर_groups[] = अणु
	"gpio37",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qdss_tracedata_a_groups[] = अणु
	"gpio37", "gpio38", "gpio39", "gpio40", "gpio41", "gpio42", "gpio43",
	"gpio44", "gpio45", "gpio46", "gpio47", "gpio48", "gpio49", "gpio50",
	"gpio51", "gpio52",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp0_uart_groups[] = अणु
	"gpio38", "gpio39", "gpio40", "gpio41",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp0_i2c_groups[] = अणु
	"gpio38", "gpio39",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp0_spi_groups[] = अणु
	"gpio38", "gpio39", "gpio40", "gpio41",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp1_uart_groups[] = अणु
	"gpio42", "gpio43", "gpio44", "gpio45",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp1_i2c_groups[] = अणु
	"gpio42", "gpio43",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp1_spi_groups[] = अणु
	"gpio42", "gpio43", "gpio44", "gpio45",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp2_uart_groups[] = अणु
	"gpio46", "gpio47", "gpio48", "gpio49",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp2_i2c_groups[] = अणु
	"gpio46", "gpio47",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp2_spi_groups[] = अणु
	"gpio46", "gpio47", "gpio48", "gpio49",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_uart_groups[] = अणु
	"gpio50", "gpio51", "gpio52", "gpio53",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_i2c_groups[] = अणु
	"gpio50", "gpio51",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_spi_groups[] = अणु
	"gpio50", "gpio51", "gpio52", "gpio53",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pta2_0_groups[] = अणु
	"gpio54",
पूर्ण;

अटल स्थिर अक्षर * स्थिर wci2b_groups[] = अणु
	"gpio54", "gpio56",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cxc1_groups[] = अणु
	"gpio54", "gpio56",
पूर्ण;

अटल स्थिर अक्षर * स्थिर blsp3_spi1_groups[] = अणु
	"gpio54", "gpio55", "gpio56",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pta2_1_groups[] = अणु
	"gpio55",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pta2_2_groups[] = अणु
	"gpio56",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie0_clk_groups[] = अणु
	"gpio57",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dbg_out_groups[] = अणु
	"gpio57",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cri_trng0_groups[] = अणु
	"gpio57",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie0_rst_groups[] = अणु
	"gpio58",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cri_trng1_groups[] = अणु
	"gpio58",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie0_wake_groups[] = अणु
	"gpio59",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cri_trng_groups[] = अणु
	"gpio59",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie1_clk_groups[] = अणु
	"gpio60",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx2_groups[] = अणु
	"gpio60",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lकरो_update_groups[] = अणु
	"gpio60",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie1_rst_groups[] = अणु
	"gpio61",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lकरो_en_groups[] = अणु
	"gpio61",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcie1_wake_groups[] = अणु
	"gpio62",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_plltest_groups[] = अणु
	"gpio62", "gpio63",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd_card_groups[] = अणु
	"gpio63",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pta1_1_groups[] = अणु
	"gpio64",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx1_groups[] = अणु
	"gpio64",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pta1_2_groups[] = अणु
	"gpio65",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gcc_tlmm_groups[] = अणु
	"gpio65",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pta1_0_groups[] = अणु
	"gpio66",
पूर्ण;

अटल स्थिर अक्षर * स्थिर prng_rosc_groups[] = अणु
	"gpio66",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd_ग_लिखो_groups[] = अणु
	"gpio67",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rx0_groups[] = अणु
	"gpio67",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tsens_max_groups[] = अणु
	"gpio67",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mdc_groups[] = अणु
	"gpio68",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mdio_groups[] = अणु
	"gpio69",
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
	"gpio64", "gpio65", "gpio66", "gpio67", "gpio68", "gpio69",
पूर्ण;

अटल स्थिर काष्ठा msm_function ipq8074_functions[] = अणु
	FUNCTION(atest_अक्षर),
	FUNCTION(atest_अक्षर0),
	FUNCTION(atest_अक्षर1),
	FUNCTION(atest_अक्षर2),
	FUNCTION(atest_अक्षर3),
	FUNCTION(audio_rxbclk),
	FUNCTION(audio_rxd),
	FUNCTION(audio_rxfsync),
	FUNCTION(audio_rxmclk),
	FUNCTION(audio_txbclk),
	FUNCTION(audio_txd),
	FUNCTION(audio_txfsync),
	FUNCTION(audio_txmclk),
	FUNCTION(blsp0_i2c),
	FUNCTION(blsp0_spi),
	FUNCTION(blsp0_uart),
	FUNCTION(blsp1_i2c),
	FUNCTION(blsp1_spi),
	FUNCTION(blsp1_uart),
	FUNCTION(blsp2_i2c),
	FUNCTION(blsp2_spi),
	FUNCTION(blsp2_uart),
	FUNCTION(blsp3_i2c),
	FUNCTION(blsp3_spi),
	FUNCTION(blsp3_spi0),
	FUNCTION(blsp3_spi1),
	FUNCTION(blsp3_spi2),
	FUNCTION(blsp3_spi3),
	FUNCTION(blsp3_uart),
	FUNCTION(blsp4_i2c0),
	FUNCTION(blsp4_i2c1),
	FUNCTION(blsp4_spi0),
	FUNCTION(blsp4_spi1),
	FUNCTION(blsp4_uart0),
	FUNCTION(blsp4_uart1),
	FUNCTION(blsp5_i2c),
	FUNCTION(blsp5_spi),
	FUNCTION(blsp5_uart),
	FUNCTION(burn0),
	FUNCTION(burn1),
	FUNCTION(cri_trng),
	FUNCTION(cri_trng0),
	FUNCTION(cri_trng1),
	FUNCTION(cxc0),
	FUNCTION(cxc1),
	FUNCTION(dbg_out),
	FUNCTION(gcc_plltest),
	FUNCTION(gcc_tlmm),
	FUNCTION(gpio),
	FUNCTION(lकरो_en),
	FUNCTION(lकरो_update),
	FUNCTION(led0),
	FUNCTION(led1),
	FUNCTION(led2),
	FUNCTION(mac0_sa0),
	FUNCTION(mac0_sa1),
	FUNCTION(mac1_sa0),
	FUNCTION(mac1_sa1),
	FUNCTION(mac1_sa2),
	FUNCTION(mac1_sa3),
	FUNCTION(mac2_sa0),
	FUNCTION(mac2_sa1),
	FUNCTION(mdc),
	FUNCTION(mdio),
	FUNCTION(pcie0_clk),
	FUNCTION(pcie0_rst),
	FUNCTION(pcie0_wake),
	FUNCTION(pcie1_clk),
	FUNCTION(pcie1_rst),
	FUNCTION(pcie1_wake),
	FUNCTION(pcm_drx),
	FUNCTION(pcm_dtx),
	FUNCTION(pcm_fsync),
	FUNCTION(pcm_pclk),
	FUNCTION(pcm_zsi0),
	FUNCTION(pcm_zsi1),
	FUNCTION(prng_rosc),
	FUNCTION(pta1_0),
	FUNCTION(pta1_1),
	FUNCTION(pta1_2),
	FUNCTION(pta2_0),
	FUNCTION(pta2_1),
	FUNCTION(pta2_2),
	FUNCTION(pwm0),
	FUNCTION(pwm1),
	FUNCTION(pwm2),
	FUNCTION(pwm3),
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
	FUNCTION(qpic),
	FUNCTION(rx0),
	FUNCTION(rx1),
	FUNCTION(rx2),
	FUNCTION(sd_card),
	FUNCTION(sd_ग_लिखो),
	FUNCTION(tsens_max),
	FUNCTION(wci2a),
	FUNCTION(wci2b),
	FUNCTION(wci2c),
	FUNCTION(wci2d),
पूर्ण;

अटल स्थिर काष्ठा msm_pingroup ipq8074_groups[] = अणु
	PINGROUP(0, qpic, blsp5_uart, blsp5_i2c, blsp5_spi, wci2a,
		 blsp3_spi3, NA, burn0, NA),
	PINGROUP(1, qpic, pcm_zsi0, mac1_sa2, blsp3_spi0, NA, burn1, NA, NA,
		 NA),
	PINGROUP(2, qpic, blsp5_uart, blsp5_i2c, blsp5_spi, wci2a,
		 blsp3_spi3, NA, NA, NA),
	PINGROUP(3, qpic, mac0_sa1, blsp3_spi0, qdss_cti_trig_out_b0, NA, NA,
		 NA, NA, NA),
	PINGROUP(4, qpic, mac0_sa1, blsp3_spi0, qdss_cti_trig_in_b0, NA, NA,
		 NA, NA, NA),
	PINGROUP(5, qpic, blsp4_uart0, blsp4_i2c0, blsp4_spi0, mac2_sa1,
		 qdss_cti_trig_out_b1, NA, NA, NA),
	PINGROUP(6, qpic, blsp4_uart0, blsp4_i2c0, blsp4_spi0, mac2_sa1,
		 qdss_cti_trig_in_b1, NA, NA, NA),
	PINGROUP(7, qpic, blsp4_uart0, blsp4_spi0, NA, NA, NA, NA, NA, NA),
	PINGROUP(8, qpic, blsp4_uart0, blsp4_spi0, NA, NA, NA, NA, NA, NA),
	PINGROUP(9, qpic, blsp5_uart, blsp5_spi, cxc0, mac1_sa3, blsp3_spi3,
		 qdss_cti_trig_in_a1, NA, NA),
	PINGROUP(10, qpic, qdss_cti_trig_out_a1, NA, NA, NA, NA, NA, NA,
		 NA),
	PINGROUP(11, qpic, wci2c, mac1_sa2, qdss_cti_trig_in_a0, NA, NA, NA,
		 NA, NA),
	PINGROUP(12, qpic, qdss_cti_trig_out_a0, NA, NA, NA, NA, NA, NA,
		 NA),
	PINGROUP(13, qpic, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(14, qpic, qdss_traceclk_b, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(15, qpic, qdss_tracectl_b, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(16, qpic, blsp5_uart, pcm_zsi1, blsp5_spi, cxc0, mac1_sa3,
		 qdss_tracedata_b, NA, NA),
	PINGROUP(17, qpic, wci2c, qdss_tracedata_b, NA, NA, NA, NA, NA, NA),
	PINGROUP(18, led0, pwm0, qdss_tracedata_b, NA, NA, NA, NA, NA, NA),
	PINGROUP(19, led1, pwm1, NA, qdss_tracedata_b, NA, NA, NA, NA, NA),
	PINGROUP(20, led2, pwm2, NA, qdss_tracedata_b, NA, NA, NA, NA, NA),
	PINGROUP(21, pwm0, blsp4_uart1, blsp4_i2c1, blsp4_spi1, wci2d, mac1_sa1,
		 blsp3_spi2, NA, qdss_tracedata_b),
	PINGROUP(22, pwm1, blsp4_uart1, blsp4_i2c1, blsp4_spi1, wci2d, mac1_sa1,
		 blsp3_spi2, NA, qdss_tracedata_b),
	PINGROUP(23, pwm2, blsp4_uart1, blsp4_spi1, blsp3_spi2, NA,
		 qdss_tracedata_b, NA, NA, NA),
	PINGROUP(24, pwm3, blsp4_uart1, blsp4_spi1, NA, qdss_tracedata_b, NA,
		 NA, NA, NA),
	PINGROUP(25, audio_txmclk, pwm0, NA, qdss_tracedata_b, NA, NA, NA, NA,
		 NA),
	PINGROUP(26, audio_txbclk, pwm1, NA, qdss_tracedata_b, NA, NA, NA, NA,
		 NA),
	PINGROUP(27, audio_txfsync, pwm2, NA, qdss_tracedata_b, NA, NA, NA,
		 NA, NA),
	PINGROUP(28, audio_txd, pwm3, NA, qdss_tracedata_b, NA, NA, NA, NA,
		 NA),
	PINGROUP(29, audio_rxmclk, pwm0, atest_अक्षर0, NA, qdss_tracedata_b,
		 NA, NA, NA, NA),
	PINGROUP(30, audio_rxbclk, pwm1, atest_अक्षर1, NA, qdss_tracedata_b,
		 NA, NA, NA, NA),
	PINGROUP(31, audio_rxfsync, pwm2, atest_अक्षर2, NA, qdss_tracedata_b,
		 NA, NA, NA, NA),
	PINGROUP(32, audio_rxd, pwm3, atest_अक्षर3, NA, NA, NA, NA, NA, NA),
	PINGROUP(33, pcm_drx, mac1_sa0, mac0_sa0, NA, NA, NA, NA, NA, NA),
	PINGROUP(34, pcm_dtx, mac1_sa0, mac0_sa0, NA, NA, NA, NA, NA, NA),
	PINGROUP(35, pcm_fsync, mac2_sa0, qdss_traceclk_a, NA, NA, NA, NA, NA, NA),
	PINGROUP(36, pcm_pclk, mac2_sa0, NA, qdss_tracectl_a, NA, NA, NA, NA, NA),
	PINGROUP(37, atest_अक्षर, NA, qdss_tracedata_a, NA, NA, NA, NA, NA, NA),
	PINGROUP(38, blsp0_uart, blsp0_i2c, blsp0_spi, NA, qdss_tracedata_a,
		 NA, NA, NA, NA),
	PINGROUP(39, blsp0_uart, blsp0_i2c, blsp0_spi, NA, qdss_tracedata_a,
		 NA, NA, NA, NA),
	PINGROUP(40, blsp0_uart, blsp0_spi, NA, qdss_tracedata_a, NA, NA, NA,
		 NA, NA),
	PINGROUP(41, blsp0_uart, blsp0_spi, NA, qdss_tracedata_a, NA, NA, NA,
		 NA, NA),
	PINGROUP(42, blsp1_uart, blsp1_i2c, blsp1_spi, NA, qdss_tracedata_a,
		 NA, NA, NA, NA),
	PINGROUP(43, blsp1_uart, blsp1_i2c, blsp1_spi, NA, qdss_tracedata_a,
		 NA, NA, NA, NA),
	PINGROUP(44, blsp1_uart, blsp1_spi, NA, qdss_tracedata_a, NA, NA, NA,
		 NA, NA),
	PINGROUP(45, blsp1_uart, blsp1_spi, qdss_tracedata_a, NA, NA, NA, NA,
		 NA, NA),
	PINGROUP(46, blsp2_uart, blsp2_i2c, blsp2_spi, qdss_tracedata_a, NA,
		 NA, NA, NA, NA),
	PINGROUP(47, blsp2_uart, blsp2_i2c, blsp2_spi, NA, qdss_tracedata_a,
		 NA, NA, NA, NA),
	PINGROUP(48, blsp2_uart, blsp2_spi, NA, qdss_tracedata_a, NA, NA, NA,
		 NA, NA),
	PINGROUP(49, blsp2_uart, blsp2_spi, NA, qdss_tracedata_a, NA, NA, NA,
		 NA, NA),
	PINGROUP(50, blsp3_uart, blsp3_i2c, blsp3_spi, NA, qdss_tracedata_a,
		 NA, NA, NA, NA),
	PINGROUP(51, blsp3_uart, blsp3_i2c, blsp3_spi, NA, qdss_tracedata_a,
		 NA, NA, NA, NA),
	PINGROUP(52, blsp3_uart, blsp3_spi, NA, qdss_tracedata_a, NA, NA, NA,
		 NA, NA),
	PINGROUP(53, blsp3_uart, blsp3_spi, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(54, pta2_0, wci2b, cxc1, blsp3_spi1, NA, NA, NA, NA, NA),
	PINGROUP(55, pta2_1, blsp3_spi1, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(56, pta2_2, wci2b, cxc1, blsp3_spi1, NA, NA, NA, NA, NA),
	PINGROUP(57, pcie0_clk, NA, dbg_out, cri_trng0, NA, NA, NA, NA, NA),
	PINGROUP(58, pcie0_rst, NA, cri_trng1, NA, NA, NA, NA, NA, NA),
	PINGROUP(59, pcie0_wake, NA, cri_trng, NA, NA, NA, NA, NA, NA),
	PINGROUP(60, pcie1_clk, rx2, lकरो_update, NA, NA, NA, NA, NA, NA),
	PINGROUP(61, pcie1_rst, lकरो_en, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(62, pcie1_wake, gcc_plltest, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(63, sd_card, pwm0, NA, gcc_plltest, NA, NA, NA, NA, NA),
	PINGROUP(64, pta1_1, pwm1, NA, rx1, NA, NA, NA, NA, NA),
	PINGROUP(65, pta1_2, NA, gcc_tlmm, NA, NA, NA, NA, NA, NA),
	PINGROUP(66, pta1_0, pwm2, prng_rosc, NA, NA, NA, NA, NA, NA),
	PINGROUP(67, sd_ग_लिखो, pwm3, rx0, tsens_max, NA, NA, NA, NA, NA),
	PINGROUP(68, mdc, NA, NA, NA, NA, NA, NA, NA, NA),
	PINGROUP(69, mdio, NA, NA, NA, NA, NA, NA, NA, NA),
पूर्ण;

अटल स्थिर काष्ठा msm_pinctrl_soc_data ipq8074_pinctrl = अणु
	.pins = ipq8074_pins,
	.npins = ARRAY_SIZE(ipq8074_pins),
	.functions = ipq8074_functions,
	.nfunctions = ARRAY_SIZE(ipq8074_functions),
	.groups = ipq8074_groups,
	.ngroups = ARRAY_SIZE(ipq8074_groups),
	.ngpios = 70,
पूर्ण;

अटल पूर्णांक ipq8074_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस msm_pinctrl_probe(pdev, &ipq8074_pinctrl);
पूर्ण

अटल स्थिर काष्ठा of_device_id ipq8074_pinctrl_of_match[] = अणु
	अणु .compatible = "qcom,ipq8074-pinctrl", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ipq8074_pinctrl_driver = अणु
	.driver = अणु
		.name = "ipq8074-pinctrl",
		.of_match_table = ipq8074_pinctrl_of_match,
	पूर्ण,
	.probe = ipq8074_pinctrl_probe,
	.हटाओ = msm_pinctrl_हटाओ,
पूर्ण;

अटल पूर्णांक __init ipq8074_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&ipq8074_pinctrl_driver);
पूर्ण
arch_initcall(ipq8074_pinctrl_init);

अटल व्योम __निकास ipq8074_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ipq8074_pinctrl_driver);
पूर्ण
module_निकास(ipq8074_pinctrl_निकास);

MODULE_DESCRIPTION("Qualcomm ipq8074 pinctrl driver");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, ipq8074_pinctrl_of_match);
