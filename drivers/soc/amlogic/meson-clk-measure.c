<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2018 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>

अटल DEFINE_MUTEX(measure_lock);

#घोषणा MSR_CLK_DUTY		0x0
#घोषणा MSR_CLK_REG0		0x4
#घोषणा MSR_CLK_REG1		0x8
#घोषणा MSR_CLK_REG2		0xc

#घोषणा MSR_DURATION		GENMASK(15, 0)
#घोषणा MSR_ENABLE		BIT(16)
#घोषणा MSR_CONT		BIT(17) /* continuous measurement */
#घोषणा MSR_INTR		BIT(18) /* पूर्णांकerrupts */
#घोषणा MSR_RUN			BIT(19)
#घोषणा MSR_CLK_SRC		GENMASK(26, 20)
#घोषणा MSR_BUSY		BIT(31)

#घोषणा MSR_VAL_MASK		GENMASK(15, 0)

#घोषणा DIV_MIN			32
#घोषणा DIV_STEP		32
#घोषणा DIV_MAX			640

#घोषणा CLK_MSR_MAX		128

काष्ठा meson_msr_id अणु
	काष्ठा meson_msr *priv;
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा meson_msr अणु
	काष्ठा regmap *regmap;
	काष्ठा meson_msr_id msr_table[CLK_MSR_MAX];
पूर्ण;

#घोषणा CLK_MSR_ID(__id, __name) \
	[__id] = अणु.id = __id, .name = __name,पूर्ण

अटल काष्ठा meson_msr_id clk_msr_m8[CLK_MSR_MAX] = अणु
	CLK_MSR_ID(0, "ring_osc_out_ee0"),
	CLK_MSR_ID(1, "ring_osc_out_ee1"),
	CLK_MSR_ID(2, "ring_osc_out_ee2"),
	CLK_MSR_ID(3, "a9_ring_osck"),
	CLK_MSR_ID(6, "vid_pll"),
	CLK_MSR_ID(7, "clk81"),
	CLK_MSR_ID(8, "encp"),
	CLK_MSR_ID(9, "encl"),
	CLK_MSR_ID(11, "eth_rmii"),
	CLK_MSR_ID(13, "amclk"),
	CLK_MSR_ID(14, "fec_clk_0"),
	CLK_MSR_ID(15, "fec_clk_1"),
	CLK_MSR_ID(16, "fec_clk_2"),
	CLK_MSR_ID(18, "a9_clk_div16"),
	CLK_MSR_ID(19, "hdmi_sys"),
	CLK_MSR_ID(20, "rtc_osc_clk_out"),
	CLK_MSR_ID(21, "i2s_clk_in_src0"),
	CLK_MSR_ID(22, "clk_rmii_from_pad"),
	CLK_MSR_ID(23, "hdmi_ch0_tmds"),
	CLK_MSR_ID(24, "lvds_fifo"),
	CLK_MSR_ID(26, "sc_clk_int"),
	CLK_MSR_ID(28, "sar_adc"),
	CLK_MSR_ID(30, "mpll_clk_test_out"),
	CLK_MSR_ID(31, "audac_clkpi"),
	CLK_MSR_ID(32, "vdac"),
	CLK_MSR_ID(33, "sdhc_rx"),
	CLK_MSR_ID(34, "sdhc_sd"),
	CLK_MSR_ID(35, "mali"),
	CLK_MSR_ID(36, "hdmi_tx_pixel"),
	CLK_MSR_ID(38, "vdin_meas"),
	CLK_MSR_ID(39, "pcm_sclk"),
	CLK_MSR_ID(40, "pcm_mclk"),
	CLK_MSR_ID(41, "eth_rx_tx"),
	CLK_MSR_ID(42, "pwm_d"),
	CLK_MSR_ID(43, "pwm_c"),
	CLK_MSR_ID(44, "pwm_b"),
	CLK_MSR_ID(45, "pwm_a"),
	CLK_MSR_ID(46, "pcm2_sclk"),
	CLK_MSR_ID(47, "ddr_dpll_pt"),
	CLK_MSR_ID(48, "pwm_f"),
	CLK_MSR_ID(49, "pwm_e"),
	CLK_MSR_ID(59, "hcodec"),
	CLK_MSR_ID(60, "usb_32k_alt"),
	CLK_MSR_ID(61, "gpio"),
	CLK_MSR_ID(62, "vid2_pll"),
	CLK_MSR_ID(63, "mipi_csi_cfg"),
पूर्ण;

अटल काष्ठा meson_msr_id clk_msr_gx[CLK_MSR_MAX] = अणु
	CLK_MSR_ID(0, "ring_osc_out_ee_0"),
	CLK_MSR_ID(1, "ring_osc_out_ee_1"),
	CLK_MSR_ID(2, "ring_osc_out_ee_2"),
	CLK_MSR_ID(3, "a53_ring_osc"),
	CLK_MSR_ID(4, "gp0_pll"),
	CLK_MSR_ID(6, "enci"),
	CLK_MSR_ID(7, "clk81"),
	CLK_MSR_ID(8, "encp"),
	CLK_MSR_ID(9, "encl"),
	CLK_MSR_ID(10, "vdac"),
	CLK_MSR_ID(11, "rgmii_tx"),
	CLK_MSR_ID(12, "pdm"),
	CLK_MSR_ID(13, "amclk"),
	CLK_MSR_ID(14, "fec_0"),
	CLK_MSR_ID(15, "fec_1"),
	CLK_MSR_ID(16, "fec_2"),
	CLK_MSR_ID(17, "sys_pll_div16"),
	CLK_MSR_ID(18, "sys_cpu_div16"),
	CLK_MSR_ID(19, "hdmitx_sys"),
	CLK_MSR_ID(20, "rtc_osc_out"),
	CLK_MSR_ID(21, "i2s_in_src0"),
	CLK_MSR_ID(22, "eth_phy_ref"),
	CLK_MSR_ID(23, "hdmi_todig"),
	CLK_MSR_ID(26, "sc_int"),
	CLK_MSR_ID(28, "sar_adc"),
	CLK_MSR_ID(31, "mpll_test_out"),
	CLK_MSR_ID(32, "vdec"),
	CLK_MSR_ID(35, "mali"),
	CLK_MSR_ID(36, "hdmi_tx_pixel"),
	CLK_MSR_ID(37, "i958"),
	CLK_MSR_ID(38, "vdin_meas"),
	CLK_MSR_ID(39, "pcm_sclk"),
	CLK_MSR_ID(40, "pcm_mclk"),
	CLK_MSR_ID(41, "eth_rx_or_rmii"),
	CLK_MSR_ID(42, "mp0_out"),
	CLK_MSR_ID(43, "fclk_div5"),
	CLK_MSR_ID(44, "pwm_b"),
	CLK_MSR_ID(45, "pwm_a"),
	CLK_MSR_ID(46, "vpu"),
	CLK_MSR_ID(47, "ddr_dpll_pt"),
	CLK_MSR_ID(48, "mp1_out"),
	CLK_MSR_ID(49, "mp2_out"),
	CLK_MSR_ID(50, "mp3_out"),
	CLK_MSR_ID(51, "nand_core"),
	CLK_MSR_ID(52, "sd_emmc_b"),
	CLK_MSR_ID(53, "sd_emmc_a"),
	CLK_MSR_ID(55, "vid_pll_div_out"),
	CLK_MSR_ID(56, "cci"),
	CLK_MSR_ID(57, "wave420l_c"),
	CLK_MSR_ID(58, "wave420l_b"),
	CLK_MSR_ID(59, "hcodec"),
	CLK_MSR_ID(60, "alt_32k"),
	CLK_MSR_ID(61, "gpio_msr"),
	CLK_MSR_ID(62, "hevc"),
	CLK_MSR_ID(66, "vid_lock"),
	CLK_MSR_ID(70, "pwm_f"),
	CLK_MSR_ID(71, "pwm_e"),
	CLK_MSR_ID(72, "pwm_d"),
	CLK_MSR_ID(73, "pwm_c"),
	CLK_MSR_ID(75, "aoclkx2_int"),
	CLK_MSR_ID(76, "aoclk_int"),
	CLK_MSR_ID(77, "rng_ring_osc_0"),
	CLK_MSR_ID(78, "rng_ring_osc_1"),
	CLK_MSR_ID(79, "rng_ring_osc_2"),
	CLK_MSR_ID(80, "rng_ring_osc_3"),
	CLK_MSR_ID(81, "vapb"),
	CLK_MSR_ID(82, "ge2d"),
पूर्ण;

अटल काष्ठा meson_msr_id clk_msr_axg[CLK_MSR_MAX] = अणु
	CLK_MSR_ID(0, "ring_osc_out_ee_0"),
	CLK_MSR_ID(1, "ring_osc_out_ee_1"),
	CLK_MSR_ID(2, "ring_osc_out_ee_2"),
	CLK_MSR_ID(3, "a53_ring_osc"),
	CLK_MSR_ID(4, "gp0_pll"),
	CLK_MSR_ID(5, "gp1_pll"),
	CLK_MSR_ID(7, "clk81"),
	CLK_MSR_ID(9, "encl"),
	CLK_MSR_ID(17, "sys_pll_div16"),
	CLK_MSR_ID(18, "sys_cpu_div16"),
	CLK_MSR_ID(20, "rtc_osc_out"),
	CLK_MSR_ID(23, "mmc_clk"),
	CLK_MSR_ID(28, "sar_adc"),
	CLK_MSR_ID(31, "mpll_test_out"),
	CLK_MSR_ID(40, "mod_eth_tx_clk"),
	CLK_MSR_ID(41, "mod_eth_rx_clk_rmii"),
	CLK_MSR_ID(42, "mp0_out"),
	CLK_MSR_ID(43, "fclk_div5"),
	CLK_MSR_ID(44, "pwm_b"),
	CLK_MSR_ID(45, "pwm_a"),
	CLK_MSR_ID(46, "vpu"),
	CLK_MSR_ID(47, "ddr_dpll_pt"),
	CLK_MSR_ID(48, "mp1_out"),
	CLK_MSR_ID(49, "mp2_out"),
	CLK_MSR_ID(50, "mp3_out"),
	CLK_MSR_ID(51, "sd_emmm_c"),
	CLK_MSR_ID(52, "sd_emmc_b"),
	CLK_MSR_ID(61, "gpio_msr"),
	CLK_MSR_ID(66, "audio_slv_lrclk_c"),
	CLK_MSR_ID(67, "audio_slv_lrclk_b"),
	CLK_MSR_ID(68, "audio_slv_lrclk_a"),
	CLK_MSR_ID(69, "audio_slv_sclk_c"),
	CLK_MSR_ID(70, "audio_slv_sclk_b"),
	CLK_MSR_ID(71, "audio_slv_sclk_a"),
	CLK_MSR_ID(72, "pwm_d"),
	CLK_MSR_ID(73, "pwm_c"),
	CLK_MSR_ID(74, "wifi_beacon"),
	CLK_MSR_ID(75, "tdmin_lb_lrcl"),
	CLK_MSR_ID(76, "tdmin_lb_sclk"),
	CLK_MSR_ID(77, "rng_ring_osc_0"),
	CLK_MSR_ID(78, "rng_ring_osc_1"),
	CLK_MSR_ID(79, "rng_ring_osc_2"),
	CLK_MSR_ID(80, "rng_ring_osc_3"),
	CLK_MSR_ID(81, "vapb"),
	CLK_MSR_ID(82, "ge2d"),
	CLK_MSR_ID(84, "audio_resample"),
	CLK_MSR_ID(85, "audio_pdm_sys"),
	CLK_MSR_ID(86, "audio_spdifout"),
	CLK_MSR_ID(87, "audio_spdifin"),
	CLK_MSR_ID(88, "audio_lrclk_f"),
	CLK_MSR_ID(89, "audio_lrclk_e"),
	CLK_MSR_ID(90, "audio_lrclk_d"),
	CLK_MSR_ID(91, "audio_lrclk_c"),
	CLK_MSR_ID(92, "audio_lrclk_b"),
	CLK_MSR_ID(93, "audio_lrclk_a"),
	CLK_MSR_ID(94, "audio_sclk_f"),
	CLK_MSR_ID(95, "audio_sclk_e"),
	CLK_MSR_ID(96, "audio_sclk_d"),
	CLK_MSR_ID(97, "audio_sclk_c"),
	CLK_MSR_ID(98, "audio_sclk_b"),
	CLK_MSR_ID(99, "audio_sclk_a"),
	CLK_MSR_ID(100, "audio_mclk_f"),
	CLK_MSR_ID(101, "audio_mclk_e"),
	CLK_MSR_ID(102, "audio_mclk_d"),
	CLK_MSR_ID(103, "audio_mclk_c"),
	CLK_MSR_ID(104, "audio_mclk_b"),
	CLK_MSR_ID(105, "audio_mclk_a"),
	CLK_MSR_ID(106, "pcie_refclk_n"),
	CLK_MSR_ID(107, "pcie_refclk_p"),
	CLK_MSR_ID(108, "audio_locker_out"),
	CLK_MSR_ID(109, "audio_locker_in"),
पूर्ण;

अटल काष्ठा meson_msr_id clk_msr_g12a[CLK_MSR_MAX] = अणु
	CLK_MSR_ID(0, "ring_osc_out_ee_0"),
	CLK_MSR_ID(1, "ring_osc_out_ee_1"),
	CLK_MSR_ID(2, "ring_osc_out_ee_2"),
	CLK_MSR_ID(3, "sys_cpu_ring_osc"),
	CLK_MSR_ID(4, "gp0_pll"),
	CLK_MSR_ID(6, "enci"),
	CLK_MSR_ID(7, "clk81"),
	CLK_MSR_ID(8, "encp"),
	CLK_MSR_ID(9, "encl"),
	CLK_MSR_ID(10, "vdac"),
	CLK_MSR_ID(11, "eth_tx"),
	CLK_MSR_ID(12, "hifi_pll"),
	CLK_MSR_ID(13, "mod_tcon"),
	CLK_MSR_ID(14, "fec_0"),
	CLK_MSR_ID(15, "fec_1"),
	CLK_MSR_ID(16, "fec_2"),
	CLK_MSR_ID(17, "sys_pll_div16"),
	CLK_MSR_ID(18, "sys_cpu_div16"),
	CLK_MSR_ID(19, "lcd_an_ph2"),
	CLK_MSR_ID(20, "rtc_osc_out"),
	CLK_MSR_ID(21, "lcd_an_ph3"),
	CLK_MSR_ID(22, "eth_phy_ref"),
	CLK_MSR_ID(23, "mpll_50m"),
	CLK_MSR_ID(24, "eth_125m"),
	CLK_MSR_ID(25, "eth_rmii"),
	CLK_MSR_ID(26, "sc_int"),
	CLK_MSR_ID(27, "in_mac"),
	CLK_MSR_ID(28, "sar_adc"),
	CLK_MSR_ID(29, "pcie_inp"),
	CLK_MSR_ID(30, "pcie_inn"),
	CLK_MSR_ID(31, "mpll_test_out"),
	CLK_MSR_ID(32, "vdec"),
	CLK_MSR_ID(33, "sys_cpu_ring_osc_1"),
	CLK_MSR_ID(34, "eth_mpll_50m"),
	CLK_MSR_ID(35, "mali"),
	CLK_MSR_ID(36, "hdmi_tx_pixel"),
	CLK_MSR_ID(37, "cdac"),
	CLK_MSR_ID(38, "vdin_meas"),
	CLK_MSR_ID(39, "bt656"),
	CLK_MSR_ID(41, "eth_rx_or_rmii"),
	CLK_MSR_ID(42, "mp0_out"),
	CLK_MSR_ID(43, "fclk_div5"),
	CLK_MSR_ID(44, "pwm_b"),
	CLK_MSR_ID(45, "pwm_a"),
	CLK_MSR_ID(46, "vpu"),
	CLK_MSR_ID(47, "ddr_dpll_pt"),
	CLK_MSR_ID(48, "mp1_out"),
	CLK_MSR_ID(49, "mp2_out"),
	CLK_MSR_ID(50, "mp3_out"),
	CLK_MSR_ID(51, "sd_emmc_c"),
	CLK_MSR_ID(52, "sd_emmc_b"),
	CLK_MSR_ID(53, "sd_emmc_a"),
	CLK_MSR_ID(54, "vpu_clkc"),
	CLK_MSR_ID(55, "vid_pll_div_out"),
	CLK_MSR_ID(56, "wave420l_a"),
	CLK_MSR_ID(57, "wave420l_c"),
	CLK_MSR_ID(58, "wave420l_b"),
	CLK_MSR_ID(59, "hcodec"),
	CLK_MSR_ID(61, "gpio_msr"),
	CLK_MSR_ID(62, "hevcb"),
	CLK_MSR_ID(63, "dsi_meas"),
	CLK_MSR_ID(64, "spicc_1"),
	CLK_MSR_ID(65, "spicc_0"),
	CLK_MSR_ID(66, "vid_lock"),
	CLK_MSR_ID(67, "dsi_phy"),
	CLK_MSR_ID(68, "hdcp22_esm"),
	CLK_MSR_ID(69, "hdcp22_skp"),
	CLK_MSR_ID(70, "pwm_f"),
	CLK_MSR_ID(71, "pwm_e"),
	CLK_MSR_ID(72, "pwm_d"),
	CLK_MSR_ID(73, "pwm_c"),
	CLK_MSR_ID(75, "hevcf"),
	CLK_MSR_ID(77, "rng_ring_osc_0"),
	CLK_MSR_ID(78, "rng_ring_osc_1"),
	CLK_MSR_ID(79, "rng_ring_osc_2"),
	CLK_MSR_ID(80, "rng_ring_osc_3"),
	CLK_MSR_ID(81, "vapb"),
	CLK_MSR_ID(82, "ge2d"),
	CLK_MSR_ID(83, "co_rx"),
	CLK_MSR_ID(84, "co_tx"),
	CLK_MSR_ID(89, "hdmi_todig"),
	CLK_MSR_ID(90, "hdmitx_sys"),
	CLK_MSR_ID(91, "sys_cpub_div16"),
	CLK_MSR_ID(92, "sys_pll_cpub_div16"),
	CLK_MSR_ID(94, "eth_phy_rx"),
	CLK_MSR_ID(95, "eth_phy_pll"),
	CLK_MSR_ID(96, "vpu_b"),
	CLK_MSR_ID(97, "cpu_b_tmp"),
	CLK_MSR_ID(98, "ts"),
	CLK_MSR_ID(99, "ring_osc_out_ee_3"),
	CLK_MSR_ID(100, "ring_osc_out_ee_4"),
	CLK_MSR_ID(101, "ring_osc_out_ee_5"),
	CLK_MSR_ID(102, "ring_osc_out_ee_6"),
	CLK_MSR_ID(103, "ring_osc_out_ee_7"),
	CLK_MSR_ID(104, "ring_osc_out_ee_8"),
	CLK_MSR_ID(105, "ring_osc_out_ee_9"),
	CLK_MSR_ID(106, "ephy_test"),
	CLK_MSR_ID(107, "au_dac_g128x"),
	CLK_MSR_ID(108, "audio_locker_out"),
	CLK_MSR_ID(109, "audio_locker_in"),
	CLK_MSR_ID(110, "audio_tdmout_c_sclk"),
	CLK_MSR_ID(111, "audio_tdmout_b_sclk"),
	CLK_MSR_ID(112, "audio_tdmout_a_sclk"),
	CLK_MSR_ID(113, "audio_tdmin_lb_sclk"),
	CLK_MSR_ID(114, "audio_tdmin_c_sclk"),
	CLK_MSR_ID(115, "audio_tdmin_b_sclk"),
	CLK_MSR_ID(116, "audio_tdmin_a_sclk"),
	CLK_MSR_ID(117, "audio_resample"),
	CLK_MSR_ID(118, "audio_pdm_sys"),
	CLK_MSR_ID(119, "audio_spdifout_b"),
	CLK_MSR_ID(120, "audio_spdifout"),
	CLK_MSR_ID(121, "audio_spdifin"),
	CLK_MSR_ID(122, "audio_pdm_dclk"),
पूर्ण;

अटल काष्ठा meson_msr_id clk_msr_sm1[CLK_MSR_MAX] = अणु
	CLK_MSR_ID(0, "ring_osc_out_ee_0"),
	CLK_MSR_ID(1, "ring_osc_out_ee_1"),
	CLK_MSR_ID(2, "ring_osc_out_ee_2"),
	CLK_MSR_ID(3, "ring_osc_out_ee_3"),
	CLK_MSR_ID(4, "gp0_pll"),
	CLK_MSR_ID(5, "gp1_pll"),
	CLK_MSR_ID(6, "enci"),
	CLK_MSR_ID(7, "clk81"),
	CLK_MSR_ID(8, "encp"),
	CLK_MSR_ID(9, "encl"),
	CLK_MSR_ID(10, "vdac"),
	CLK_MSR_ID(11, "eth_tx"),
	CLK_MSR_ID(12, "hifi_pll"),
	CLK_MSR_ID(13, "mod_tcon"),
	CLK_MSR_ID(14, "fec_0"),
	CLK_MSR_ID(15, "fec_1"),
	CLK_MSR_ID(16, "fec_2"),
	CLK_MSR_ID(17, "sys_pll_div16"),
	CLK_MSR_ID(18, "sys_cpu_div16"),
	CLK_MSR_ID(19, "lcd_an_ph2"),
	CLK_MSR_ID(20, "rtc_osc_out"),
	CLK_MSR_ID(21, "lcd_an_ph3"),
	CLK_MSR_ID(22, "eth_phy_ref"),
	CLK_MSR_ID(23, "mpll_50m"),
	CLK_MSR_ID(24, "eth_125m"),
	CLK_MSR_ID(25, "eth_rmii"),
	CLK_MSR_ID(26, "sc_int"),
	CLK_MSR_ID(27, "in_mac"),
	CLK_MSR_ID(28, "sar_adc"),
	CLK_MSR_ID(29, "pcie_inp"),
	CLK_MSR_ID(30, "pcie_inn"),
	CLK_MSR_ID(31, "mpll_test_out"),
	CLK_MSR_ID(32, "vdec"),
	CLK_MSR_ID(34, "eth_mpll_50m"),
	CLK_MSR_ID(35, "mali"),
	CLK_MSR_ID(36, "hdmi_tx_pixel"),
	CLK_MSR_ID(37, "cdac"),
	CLK_MSR_ID(38, "vdin_meas"),
	CLK_MSR_ID(39, "bt656"),
	CLK_MSR_ID(40, "arm_ring_osc_out_4"),
	CLK_MSR_ID(41, "eth_rx_or_rmii"),
	CLK_MSR_ID(42, "mp0_out"),
	CLK_MSR_ID(43, "fclk_div5"),
	CLK_MSR_ID(44, "pwm_b"),
	CLK_MSR_ID(45, "pwm_a"),
	CLK_MSR_ID(46, "vpu"),
	CLK_MSR_ID(47, "ddr_dpll_pt"),
	CLK_MSR_ID(48, "mp1_out"),
	CLK_MSR_ID(49, "mp2_out"),
	CLK_MSR_ID(50, "mp3_out"),
	CLK_MSR_ID(51, "sd_emmc_c"),
	CLK_MSR_ID(52, "sd_emmc_b"),
	CLK_MSR_ID(53, "sd_emmc_a"),
	CLK_MSR_ID(54, "vpu_clkc"),
	CLK_MSR_ID(55, "vid_pll_div_out"),
	CLK_MSR_ID(56, "wave420l_a"),
	CLK_MSR_ID(57, "wave420l_c"),
	CLK_MSR_ID(58, "wave420l_b"),
	CLK_MSR_ID(59, "hcodec"),
	CLK_MSR_ID(60, "arm_ring_osc_out_5"),
	CLK_MSR_ID(61, "gpio_msr"),
	CLK_MSR_ID(62, "hevcb"),
	CLK_MSR_ID(63, "dsi_meas"),
	CLK_MSR_ID(64, "spicc_1"),
	CLK_MSR_ID(65, "spicc_0"),
	CLK_MSR_ID(66, "vid_lock"),
	CLK_MSR_ID(67, "dsi_phy"),
	CLK_MSR_ID(68, "hdcp22_esm"),
	CLK_MSR_ID(69, "hdcp22_skp"),
	CLK_MSR_ID(70, "pwm_f"),
	CLK_MSR_ID(71, "pwm_e"),
	CLK_MSR_ID(72, "pwm_d"),
	CLK_MSR_ID(73, "pwm_c"),
	CLK_MSR_ID(74, "arm_ring_osc_out_6"),
	CLK_MSR_ID(75, "hevcf"),
	CLK_MSR_ID(76, "arm_ring_osc_out_7"),
	CLK_MSR_ID(77, "rng_ring_osc_0"),
	CLK_MSR_ID(78, "rng_ring_osc_1"),
	CLK_MSR_ID(79, "rng_ring_osc_2"),
	CLK_MSR_ID(80, "rng_ring_osc_3"),
	CLK_MSR_ID(81, "vapb"),
	CLK_MSR_ID(82, "ge2d"),
	CLK_MSR_ID(83, "co_rx"),
	CLK_MSR_ID(84, "co_tx"),
	CLK_MSR_ID(85, "arm_ring_osc_out_8"),
	CLK_MSR_ID(86, "arm_ring_osc_out_9"),
	CLK_MSR_ID(87, "mipi_dsi_phy"),
	CLK_MSR_ID(88, "cis2_adapt"),
	CLK_MSR_ID(89, "hdmi_todig"),
	CLK_MSR_ID(90, "hdmitx_sys"),
	CLK_MSR_ID(91, "nna_core"),
	CLK_MSR_ID(92, "nna_axi"),
	CLK_MSR_ID(93, "vad"),
	CLK_MSR_ID(94, "eth_phy_rx"),
	CLK_MSR_ID(95, "eth_phy_pll"),
	CLK_MSR_ID(96, "vpu_b"),
	CLK_MSR_ID(97, "cpu_b_tmp"),
	CLK_MSR_ID(98, "ts"),
	CLK_MSR_ID(99, "arm_ring_osc_out_10"),
	CLK_MSR_ID(100, "arm_ring_osc_out_11"),
	CLK_MSR_ID(101, "arm_ring_osc_out_12"),
	CLK_MSR_ID(102, "arm_ring_osc_out_13"),
	CLK_MSR_ID(103, "arm_ring_osc_out_14"),
	CLK_MSR_ID(104, "arm_ring_osc_out_15"),
	CLK_MSR_ID(105, "arm_ring_osc_out_16"),
	CLK_MSR_ID(106, "ephy_test"),
	CLK_MSR_ID(107, "au_dac_g128x"),
	CLK_MSR_ID(108, "audio_locker_out"),
	CLK_MSR_ID(109, "audio_locker_in"),
	CLK_MSR_ID(110, "audio_tdmout_c_sclk"),
	CLK_MSR_ID(111, "audio_tdmout_b_sclk"),
	CLK_MSR_ID(112, "audio_tdmout_a_sclk"),
	CLK_MSR_ID(113, "audio_tdmin_lb_sclk"),
	CLK_MSR_ID(114, "audio_tdmin_c_sclk"),
	CLK_MSR_ID(115, "audio_tdmin_b_sclk"),
	CLK_MSR_ID(116, "audio_tdmin_a_sclk"),
	CLK_MSR_ID(117, "audio_resample"),
	CLK_MSR_ID(118, "audio_pdm_sys"),
	CLK_MSR_ID(119, "audio_spdifout_b"),
	CLK_MSR_ID(120, "audio_spdifout"),
	CLK_MSR_ID(121, "audio_spdifin"),
	CLK_MSR_ID(122, "audio_pdm_dclk"),
	CLK_MSR_ID(123, "audio_resampled"),
	CLK_MSR_ID(124, "earcrx_pll"),
	CLK_MSR_ID(125, "earcrx_pll_test"),
	CLK_MSR_ID(126, "csi_phy0"),
	CLK_MSR_ID(127, "csi2_data"),
पूर्ण;

अटल पूर्णांक meson_measure_id(काष्ठा meson_msr_id *clk_msr_id,
			       अचिन्हित पूर्णांक duration)
अणु
	काष्ठा meson_msr *priv = clk_msr_id->priv;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&measure_lock);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, MSR_CLK_REG0, 0);

	/* Set measurement duration */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0, MSR_DURATION,
			   FIELD_PREP(MSR_DURATION, duration - 1));

	/* Set ID */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0, MSR_CLK_SRC,
			   FIELD_PREP(MSR_CLK_SRC, clk_msr_id->id));

	/* Enable & Start */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0,
			   MSR_RUN | MSR_ENABLE,
			   MSR_RUN | MSR_ENABLE);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, MSR_CLK_REG0,
				       val, !(val & MSR_BUSY), 10, 10000);
	अगर (ret) अणु
		mutex_unlock(&measure_lock);
		वापस ret;
	पूर्ण

	/* Disable */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0, MSR_ENABLE, 0);

	/* Get the value in multiple of gate समय counts */
	regmap_पढ़ो(priv->regmap, MSR_CLK_REG2, &val);

	mutex_unlock(&measure_lock);

	अगर (val >= MSR_VAL_MASK)
		वापस -EINVAL;

	वापस DIV_ROUND_CLOSEST_ULL((val & MSR_VAL_MASK) * 1000000ULL,
				     duration);
पूर्ण

अटल पूर्णांक meson_measure_best_id(काष्ठा meson_msr_id *clk_msr_id,
				    अचिन्हित पूर्णांक *precision)
अणु
	अचिन्हित पूर्णांक duration = DIV_MAX;
	पूर्णांक ret;

	/* Start from max duration and करोwn to min duration */
	करो अणु
		ret = meson_measure_id(clk_msr_id, duration);
		अगर (ret >= 0)
			*precision = (2 * 1000000) / duration;
		अन्यथा
			duration -= DIV_STEP;
	पूर्ण जबतक (duration >= DIV_MIN && ret == -EINVAL);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_msr_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा meson_msr_id *clk_msr_id = s->निजी;
	अचिन्हित पूर्णांक precision = 0;
	पूर्णांक val;

	val = meson_measure_best_id(clk_msr_id, &precision);
	अगर (val < 0)
		वापस val;

	seq_म_लिखो(s, "%d\t+/-%dHz\n", val, precision);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_msr);

अटल पूर्णांक clk_msr_summary_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा meson_msr_id *msr_table = s->निजी;
	अचिन्हित पूर्णांक precision = 0;
	पूर्णांक val, i;

	seq_माला_दो(s, "  clock                     rate    precision\n");
	seq_माला_दो(s, "---------------------------------------------\n");

	क्रम (i = 0 ; i < CLK_MSR_MAX ; ++i) अणु
		अगर (!msr_table[i].name)
			जारी;

		val = meson_measure_best_id(&msr_table[i], &precision);
		अगर (val < 0)
			वापस val;

		seq_म_लिखो(s, " %-20s %10d    +/-%dHz\n",
			   msr_table[i].name, val, precision);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk_msr_summary);

अटल स्थिर काष्ठा regmap_config meson_clk_msr_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = MSR_CLK_REG2,
पूर्ण;

अटल पूर्णांक meson_msr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_msr_id *match_data;
	काष्ठा meson_msr *priv;
	काष्ठा resource *res;
	काष्ठा dentry *root, *clks;
	व्योम __iomem *base;
	पूर्णांक i;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा meson_msr),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	match_data = device_get_match_data(&pdev->dev);
	अगर (!match_data) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	स_नकल(priv->msr_table, match_data, माप(priv->msr_table));

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					     &meson_clk_msr_regmap_config);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	root = debugfs_create_dir("meson-clk-msr", शून्य);
	clks = debugfs_create_dir("clks", root);

	debugfs_create_file("measure_summary", 0444, root,
			    priv->msr_table, &clk_msr_summary_fops);

	क्रम (i = 0 ; i < CLK_MSR_MAX ; ++i) अणु
		अगर (!priv->msr_table[i].name)
			जारी;

		priv->msr_table[i].priv = priv;

		debugfs_create_file(priv->msr_table[i].name, 0444, clks,
				    &priv->msr_table[i], &clk_msr_fops);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_msr_match_table[] = अणु
	अणु
		.compatible = "amlogic,meson-gx-clk-measure",
		.data = (व्योम *)clk_msr_gx,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8-clk-measure",
		.data = (व्योम *)clk_msr_m8,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8b-clk-measure",
		.data = (व्योम *)clk_msr_m8,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-axg-clk-measure",
		.data = (व्योम *)clk_msr_axg,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-g12a-clk-measure",
		.data = (व्योम *)clk_msr_g12a,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-sm1-clk-measure",
		.data = (व्योम *)clk_msr_sm1,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_msr_match_table);

अटल काष्ठा platक्रमm_driver meson_msr_driver = अणु
	.probe	= meson_msr_probe,
	.driver = अणु
		.name		= "meson_msr",
		.of_match_table	= meson_msr_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_msr_driver);
MODULE_LICENSE("GPL v2");
