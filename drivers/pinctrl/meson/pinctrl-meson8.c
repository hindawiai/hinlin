<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pin controller and GPIO driver क्रम Amlogic Meson8 and Meson8m2.
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 */

#समावेश <dt-bindings/gpio/meson8-gpपन.स>
#समावेश "pinctrl-meson.h"
#समावेश "pinctrl-meson8-pmx.h"

अटल स्थिर काष्ठा pinctrl_pin_desc meson8_cbus_pins[] = अणु
	MESON_PIN(GPIOX_0),
	MESON_PIN(GPIOX_1),
	MESON_PIN(GPIOX_2),
	MESON_PIN(GPIOX_3),
	MESON_PIN(GPIOX_4),
	MESON_PIN(GPIOX_5),
	MESON_PIN(GPIOX_6),
	MESON_PIN(GPIOX_7),
	MESON_PIN(GPIOX_8),
	MESON_PIN(GPIOX_9),
	MESON_PIN(GPIOX_10),
	MESON_PIN(GPIOX_11),
	MESON_PIN(GPIOX_12),
	MESON_PIN(GPIOX_13),
	MESON_PIN(GPIOX_14),
	MESON_PIN(GPIOX_15),
	MESON_PIN(GPIOX_16),
	MESON_PIN(GPIOX_17),
	MESON_PIN(GPIOX_18),
	MESON_PIN(GPIOX_19),
	MESON_PIN(GPIOX_20),
	MESON_PIN(GPIOX_21),
	MESON_PIN(GPIOY_0),
	MESON_PIN(GPIOY_1),
	MESON_PIN(GPIOY_2),
	MESON_PIN(GPIOY_3),
	MESON_PIN(GPIOY_4),
	MESON_PIN(GPIOY_5),
	MESON_PIN(GPIOY_6),
	MESON_PIN(GPIOY_7),
	MESON_PIN(GPIOY_8),
	MESON_PIN(GPIOY_9),
	MESON_PIN(GPIOY_10),
	MESON_PIN(GPIOY_11),
	MESON_PIN(GPIOY_12),
	MESON_PIN(GPIOY_13),
	MESON_PIN(GPIOY_14),
	MESON_PIN(GPIOY_15),
	MESON_PIN(GPIOY_16),
	MESON_PIN(GPIODV_0),
	MESON_PIN(GPIODV_1),
	MESON_PIN(GPIODV_2),
	MESON_PIN(GPIODV_3),
	MESON_PIN(GPIODV_4),
	MESON_PIN(GPIODV_5),
	MESON_PIN(GPIODV_6),
	MESON_PIN(GPIODV_7),
	MESON_PIN(GPIODV_8),
	MESON_PIN(GPIODV_9),
	MESON_PIN(GPIODV_10),
	MESON_PIN(GPIODV_11),
	MESON_PIN(GPIODV_12),
	MESON_PIN(GPIODV_13),
	MESON_PIN(GPIODV_14),
	MESON_PIN(GPIODV_15),
	MESON_PIN(GPIODV_16),
	MESON_PIN(GPIODV_17),
	MESON_PIN(GPIODV_18),
	MESON_PIN(GPIODV_19),
	MESON_PIN(GPIODV_20),
	MESON_PIN(GPIODV_21),
	MESON_PIN(GPIODV_22),
	MESON_PIN(GPIODV_23),
	MESON_PIN(GPIODV_24),
	MESON_PIN(GPIODV_25),
	MESON_PIN(GPIODV_26),
	MESON_PIN(GPIODV_27),
	MESON_PIN(GPIODV_28),
	MESON_PIN(GPIODV_29),
	MESON_PIN(GPIOH_0),
	MESON_PIN(GPIOH_1),
	MESON_PIN(GPIOH_2),
	MESON_PIN(GPIOH_3),
	MESON_PIN(GPIOH_4),
	MESON_PIN(GPIOH_5),
	MESON_PIN(GPIOH_6),
	MESON_PIN(GPIOH_7),
	MESON_PIN(GPIOH_8),
	MESON_PIN(GPIOH_9),
	MESON_PIN(GPIOZ_0),
	MESON_PIN(GPIOZ_1),
	MESON_PIN(GPIOZ_2),
	MESON_PIN(GPIOZ_3),
	MESON_PIN(GPIOZ_4),
	MESON_PIN(GPIOZ_5),
	MESON_PIN(GPIOZ_6),
	MESON_PIN(GPIOZ_7),
	MESON_PIN(GPIOZ_8),
	MESON_PIN(GPIOZ_9),
	MESON_PIN(GPIOZ_10),
	MESON_PIN(GPIOZ_11),
	MESON_PIN(GPIOZ_12),
	MESON_PIN(GPIOZ_13),
	MESON_PIN(GPIOZ_14),
	MESON_PIN(CARD_0),
	MESON_PIN(CARD_1),
	MESON_PIN(CARD_2),
	MESON_PIN(CARD_3),
	MESON_PIN(CARD_4),
	MESON_PIN(CARD_5),
	MESON_PIN(CARD_6),
	MESON_PIN(BOOT_0),
	MESON_PIN(BOOT_1),
	MESON_PIN(BOOT_2),
	MESON_PIN(BOOT_3),
	MESON_PIN(BOOT_4),
	MESON_PIN(BOOT_5),
	MESON_PIN(BOOT_6),
	MESON_PIN(BOOT_7),
	MESON_PIN(BOOT_8),
	MESON_PIN(BOOT_9),
	MESON_PIN(BOOT_10),
	MESON_PIN(BOOT_11),
	MESON_PIN(BOOT_12),
	MESON_PIN(BOOT_13),
	MESON_PIN(BOOT_14),
	MESON_PIN(BOOT_15),
	MESON_PIN(BOOT_16),
	MESON_PIN(BOOT_17),
	MESON_PIN(BOOT_18),
पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc meson8_aobus_pins[] = अणु
	MESON_PIN(GPIOAO_0),
	MESON_PIN(GPIOAO_1),
	MESON_PIN(GPIOAO_2),
	MESON_PIN(GPIOAO_3),
	MESON_PIN(GPIOAO_4),
	MESON_PIN(GPIOAO_5),
	MESON_PIN(GPIOAO_6),
	MESON_PIN(GPIOAO_7),
	MESON_PIN(GPIOAO_8),
	MESON_PIN(GPIOAO_9),
	MESON_PIN(GPIOAO_10),
	MESON_PIN(GPIOAO_11),
	MESON_PIN(GPIOAO_12),
	MESON_PIN(GPIOAO_13),
	MESON_PIN(GPIO_BSD_EN),
	MESON_PIN(GPIO_TEST_N),
पूर्ण;

/* bank X */
अटल स्थिर अचिन्हित पूर्णांक sd_d0_a_pins[]	= अणु GPIOX_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d1_a_pins[]	= अणु GPIOX_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d2_a_pins[]	= अणु GPIOX_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d3_a_pins[]	= अणु GPIOX_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_clk_a_pins[]	= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_cmd_a_pins[]	= अणु GPIOX_9 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sdxc_d0_a_pins[]	= अणु GPIOX_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_d13_a_pins[]	= अणु GPIOX_1, GPIOX_2, GPIOX_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_d47_a_pins[]	= अणु GPIOX_4, GPIOX_5, GPIOX_6,
						    GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_clk_a_pins[]	= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_cmd_a_pins[]	= अणु GPIOX_9 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pcm_out_a_pins[]	= अणु GPIOX_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcm_in_a_pins[]	= अणु GPIOX_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcm_fs_a_pins[]	= अणु GPIOX_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcm_clk_a_pins[]	= अणु GPIOX_7 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_a0_pins[]	= अणु GPIOX_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_a0_pins[]	= अणु GPIOX_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_a0_pins[]	= अणु GPIOX_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_a0_pins[]	= अणु GPIOX_7 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_a1_pins[]	= अणु GPIOX_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_a1_pins[]	= अणु GPIOX_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_a1_pins[]	= अणु GPIOX_14 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_a1_pins[]	= अणु GPIOX_15 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_b0_pins[]	= अणु GPIOX_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_b0_pins[]	= अणु GPIOX_17 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_b0_pins[]	= अणु GPIOX_18 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_b0_pins[]	= अणु GPIOX_19 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक iso7816_det_pins[]	= अणु GPIOX_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक iso7816_reset_pins[]	= अणु GPIOX_17 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक iso7816_clk_pins[]	= अणु GPIOX_18 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक iso7816_data_pins[]	= अणु GPIOX_19 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_d0_pins[]	= अणु GPIOX_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_d0_pins[]	= अणु GPIOX_17 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक xtal_32k_out_pins[]	= अणु GPIOX_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक xtal_24m_out_pins[]	= अणु GPIOX_11 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_e_pins[]		= अणु GPIOX_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_b_x_pins[]	= अणु GPIOX_11 पूर्ण;

/* bank Y */
अटल स्थिर अचिन्हित पूर्णांक uart_tx_c_pins[]	= अणु GPIOY_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_c_pins[]	= अणु GPIOY_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_c_pins[]	= अणु GPIOY_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_c_pins[]	= अणु GPIOY_3 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pcm_out_b_pins[]	= अणु GPIOY_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcm_in_b_pins[]	= अणु GPIOY_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcm_fs_b_pins[]	= अणु GPIOY_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pcm_clk_b_pins[]	= अणु GPIOY_7 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_c0_pins[]	= अणु GPIOY_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_c0_pins[]	= अणु GPIOY_1 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_a_y_pins[]	= अणु GPIOY_16 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch45_pins[]	= अणु GPIOY_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch23_pins[]	= अणु GPIOY_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch01_pins[]	= अणु GPIOY_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_in_ch01_pins[]	= अणु GPIOY_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_lr_clk_in_pins[]	= अणु GPIOY_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_ao_clk_in_pins[]	= अणु GPIOY_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_am_clk_pins[]	= अणु GPIOY_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch78_pins[]	= अणु GPIOY_9 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक spdअगर_in_pins[]	= अणु GPIOY_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spdअगर_out_pins[]	= अणु GPIOY_3 पूर्ण;

/* bank DV */
अटल स्थिर अचिन्हित पूर्णांक dvin_rgb_pins[] = अणु
	GPIODV_0, GPIODV_1, GPIODV_2, GPIODV_3, GPIODV_4, GPIODV_5,
	GPIODV_6, GPIODV_7, GPIODV_8, GPIODV_9, GPIODV_10, GPIODV_11,
	GPIODV_12, GPIODV_13, GPIODV_14, GPIODV_15, GPIODV_16, GPIODV_17,
	GPIODV_18, GPIODV_19, GPIODV_20, GPIODV_21, GPIODV_22, GPIODV_23
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक dvin_vs_pins[]	= अणु GPIODV_24 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक dvin_hs_pins[]	= अणु GPIODV_25 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक dvin_clk_pins[]	= अणु GPIODV_26 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक dvin_de_pins[]	= अणु GPIODV_27 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक enc_0_pins[]		= अणु GPIODV_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_1_pins[]		= अणु GPIODV_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_2_pins[]		= अणु GPIODV_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_3_pins[]		= अणु GPIODV_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_4_pins[]		= अणु GPIODV_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_5_pins[]		= अणु GPIODV_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_6_pins[]		= अणु GPIODV_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_7_pins[]		= अणु GPIODV_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_8_pins[]		= अणु GPIODV_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_9_pins[]		= अणु GPIODV_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_10_pins[]		= अणु GPIODV_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_11_pins[]		= अणु GPIODV_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_12_pins[]		= अणु GPIODV_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_13_pins[]		= अणु GPIODV_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_14_pins[]		= अणु GPIODV_14 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_15_pins[]		= अणु GPIODV_15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_16_pins[]		= अणु GPIODV_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक enc_17_pins[]		= अणु GPIODV_17 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_b1_pins[]	= अणु GPIODV_24 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_b1_pins[]	= अणु GPIODV_25 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_b1_pins[]	= अणु GPIODV_26 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_b1_pins[]	= अणु GPIODV_27 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक vga_vs_pins[]		= अणु GPIODV_24 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक vga_hs_pins[]		= अणु GPIODV_25 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_c_dv9_pins[]	= अणु GPIODV_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_c_dv29_pins[]	= अणु GPIODV_29 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_d_pins[]		= अणु GPIODV_28 पूर्ण;

/* bank H */
अटल स्थिर अचिन्हित पूर्णांक hdmi_hpd_pins[]	= अणु GPIOH_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hdmi_sda_pins[]	= अणु GPIOH_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hdmi_scl_pins[]	= अणु GPIOH_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hdmi_cec_pins[]	= अणु GPIOH_3 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक spi_ss0_0_pins[]	= अणु GPIOH_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_miso_0_pins[]	= अणु GPIOH_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_mosi_0_pins[]	= अणु GPIOH_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_sclk_0_pins[]	= अणु GPIOH_6 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_d1_pins[]	= अणु GPIOH_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_d1_pins[]	= अणु GPIOH_8 पूर्ण;

/* bank Z */
अटल स्थिर अचिन्हित पूर्णांक spi_ss0_1_pins[]	= अणु GPIOZ_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_ss1_1_pins[]	= अणु GPIOZ_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_sclk_1_pins[]	= अणु GPIOZ_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_mosi_1_pins[]	= अणु GPIOZ_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_miso_1_pins[]	= अणु GPIOZ_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_ss2_1_pins[]	= अणु GPIOZ_14 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक eth_txd3_pins[]	= अणु GPIOZ_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_txd2_pins[]	= अणु GPIOZ_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd3_pins[]	= अणु GPIOZ_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd2_pins[]	= अणु GPIOZ_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_tx_clk_50m_pins[]	= अणु GPIOZ_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_tx_en_pins[]	= अणु GPIOZ_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_txd1_pins[]	= अणु GPIOZ_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_txd0_pins[]	= अणु GPIOZ_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rx_clk_in_pins[]	= अणु GPIOZ_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rx_dv_pins[]	= अणु GPIOZ_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd1_pins[]	= अणु GPIOZ_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd0_pins[]	= अणु GPIOZ_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_mdio_pins[]	= अणु GPIOZ_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_mdc_pins[]	= अणु GPIOZ_13 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_a0_pins[]	= अणु GPIOZ_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_a0_pins[]	= अणु GPIOZ_1 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_b_pins[]	= अणु GPIOZ_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_b_pins[]	= अणु GPIOZ_3 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_c1_pins[]	= अणु GPIOZ_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_c1_pins[]	= अणु GPIOZ_5 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_a1_pins[]	= अणु GPIOZ_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_a1_pins[]	= अणु GPIOZ_1 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sda_a2_pins[]	= अणु GPIOZ_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sck_a2_pins[]	= अणु GPIOZ_1 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_a_z0_pins[]	= अणु GPIOZ_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_a_z7_pins[]	= अणु GPIOZ_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_b_z_pins[]	= अणु GPIOZ_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_c_z_pins[]	= अणु GPIOZ_8 पूर्ण;

/* bank BOOT */
अटल स्थिर अचिन्हित पूर्णांक sd_d0_c_pins[]	= अणु BOOT_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d1_c_pins[]	= अणु BOOT_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d2_c_pins[]	= अणु BOOT_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d3_c_pins[]	= अणु BOOT_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_cmd_c_pins[]	= अणु BOOT_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_clk_c_pins[]	= अणु BOOT_17 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sdxc_d0_c_pins[]	= अणु BOOT_0पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_d13_c_pins[]	= अणु BOOT_1, BOOT_2, BOOT_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_d47_c_pins[]	= अणु BOOT_4, BOOT_5, BOOT_6,
						    BOOT_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_cmd_c_pins[]	= अणु BOOT_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_clk_c_pins[]	= अणु BOOT_17 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nand_io_pins[] = अणु
	BOOT_0, BOOT_1, BOOT_2, BOOT_3, BOOT_4, BOOT_5, BOOT_6, BOOT_7
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_io_ce0_pins[]	= अणु BOOT_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_io_ce1_pins[]	= अणु BOOT_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_io_rb0_pins[]	= अणु BOOT_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_ale_pins[]	= अणु BOOT_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_cle_pins[]	= अणु BOOT_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_wen_clk_pins[]	= अणु BOOT_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_ren_clk_pins[]	= अणु BOOT_14 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_dqs_pins[]	= अणु BOOT_15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_ce2_pins[]	= अणु BOOT_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_ce3_pins[]	= अणु BOOT_17 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nor_d_pins[]		= अणु BOOT_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_q_pins[]		= अणु BOOT_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_c_pins[]		= अणु BOOT_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_cs_pins[]		= अणु BOOT_18 पूर्ण;

/* bank CARD */
अटल स्थिर अचिन्हित पूर्णांक sd_d1_b_pins[]	= अणु CARD_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d0_b_pins[]	= अणु CARD_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_clk_b_pins[]	= अणु CARD_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_cmd_b_pins[]	= अणु CARD_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d3_b_pins[]	= अणु CARD_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sd_d2_b_pins[]	= अणु CARD_5 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sdxc_d13_b_pins[]	= अणु CARD_0, CARD_4, CARD_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_d0_b_pins[]	= अणु CARD_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_clk_b_pins[]	= अणु CARD_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdxc_cmd_b_pins[]	= अणु CARD_3 पूर्ण;

/* bank AO */
अटल स्थिर अचिन्हित पूर्णांक uart_tx_ao_a_pins[]	= अणु GPIOAO_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_ao_a_pins[]	= अणु GPIOAO_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_ao_a_pins[]	= अणु GPIOAO_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_ao_a_pins[]	= अणु GPIOAO_3 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक remote_input_pins[]	= अणु GPIOAO_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक remote_output_ao_pins[] = अणु GPIOAO_13 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sck_ao_pins[] = अणु GPIOAO_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sda_ao_pins[] = अणु GPIOAO_5 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_ao_b0_pins[]	= अणु GPIOAO_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_ao_b0_pins[]	= अणु GPIOAO_1 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_ao_b1_pins[]	= अणु GPIOAO_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_ao_b1_pins[]	= अणु GPIOAO_5 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_mst_sck_ao_pins[]	= अणु GPIOAO_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_mst_sda_ao_pins[]	= अणु GPIOAO_5 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_f_ao_pins[]	= अणु GPIO_TEST_N पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2s_am_clk_out_ao_pins[] = अणु GPIOAO_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_ao_clk_out_ao_pins[] = अणु GPIOAO_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_lr_clk_out_ao_pins[] = अणु GPIOAO_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch01_ao_pins[] = अणु GPIOAO_11 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hdmi_cec_ao_pins[]	= अणु GPIOAO_12 पूर्ण;

अटल काष्ठा meson_pmx_group meson8_cbus_groups[] = अणु
	GPIO_GROUP(GPIOX_0),
	GPIO_GROUP(GPIOX_1),
	GPIO_GROUP(GPIOX_2),
	GPIO_GROUP(GPIOX_3),
	GPIO_GROUP(GPIOX_4),
	GPIO_GROUP(GPIOX_5),
	GPIO_GROUP(GPIOX_6),
	GPIO_GROUP(GPIOX_7),
	GPIO_GROUP(GPIOX_8),
	GPIO_GROUP(GPIOX_9),
	GPIO_GROUP(GPIOX_10),
	GPIO_GROUP(GPIOX_11),
	GPIO_GROUP(GPIOX_12),
	GPIO_GROUP(GPIOX_13),
	GPIO_GROUP(GPIOX_14),
	GPIO_GROUP(GPIOX_15),
	GPIO_GROUP(GPIOX_16),
	GPIO_GROUP(GPIOX_17),
	GPIO_GROUP(GPIOX_18),
	GPIO_GROUP(GPIOX_19),
	GPIO_GROUP(GPIOX_20),
	GPIO_GROUP(GPIOX_21),
	GPIO_GROUP(GPIOY_0),
	GPIO_GROUP(GPIOY_1),
	GPIO_GROUP(GPIOY_2),
	GPIO_GROUP(GPIOY_3),
	GPIO_GROUP(GPIOY_4),
	GPIO_GROUP(GPIOY_5),
	GPIO_GROUP(GPIOY_6),
	GPIO_GROUP(GPIOY_7),
	GPIO_GROUP(GPIOY_8),
	GPIO_GROUP(GPIOY_9),
	GPIO_GROUP(GPIOY_10),
	GPIO_GROUP(GPIOY_11),
	GPIO_GROUP(GPIOY_12),
	GPIO_GROUP(GPIOY_13),
	GPIO_GROUP(GPIOY_14),
	GPIO_GROUP(GPIOY_15),
	GPIO_GROUP(GPIOY_16),
	GPIO_GROUP(GPIODV_0),
	GPIO_GROUP(GPIODV_1),
	GPIO_GROUP(GPIODV_2),
	GPIO_GROUP(GPIODV_3),
	GPIO_GROUP(GPIODV_4),
	GPIO_GROUP(GPIODV_5),
	GPIO_GROUP(GPIODV_6),
	GPIO_GROUP(GPIODV_7),
	GPIO_GROUP(GPIODV_8),
	GPIO_GROUP(GPIODV_9),
	GPIO_GROUP(GPIODV_10),
	GPIO_GROUP(GPIODV_11),
	GPIO_GROUP(GPIODV_12),
	GPIO_GROUP(GPIODV_13),
	GPIO_GROUP(GPIODV_14),
	GPIO_GROUP(GPIODV_15),
	GPIO_GROUP(GPIODV_16),
	GPIO_GROUP(GPIODV_17),
	GPIO_GROUP(GPIODV_18),
	GPIO_GROUP(GPIODV_19),
	GPIO_GROUP(GPIODV_20),
	GPIO_GROUP(GPIODV_21),
	GPIO_GROUP(GPIODV_22),
	GPIO_GROUP(GPIODV_23),
	GPIO_GROUP(GPIODV_24),
	GPIO_GROUP(GPIODV_25),
	GPIO_GROUP(GPIODV_26),
	GPIO_GROUP(GPIODV_27),
	GPIO_GROUP(GPIODV_28),
	GPIO_GROUP(GPIODV_29),
	GPIO_GROUP(GPIOH_0),
	GPIO_GROUP(GPIOH_1),
	GPIO_GROUP(GPIOH_2),
	GPIO_GROUP(GPIOH_3),
	GPIO_GROUP(GPIOH_4),
	GPIO_GROUP(GPIOH_5),
	GPIO_GROUP(GPIOH_6),
	GPIO_GROUP(GPIOH_7),
	GPIO_GROUP(GPIOH_8),
	GPIO_GROUP(GPIOH_9),
	GPIO_GROUP(GPIOZ_0),
	GPIO_GROUP(GPIOZ_1),
	GPIO_GROUP(GPIOZ_2),
	GPIO_GROUP(GPIOZ_3),
	GPIO_GROUP(GPIOZ_4),
	GPIO_GROUP(GPIOZ_5),
	GPIO_GROUP(GPIOZ_6),
	GPIO_GROUP(GPIOZ_7),
	GPIO_GROUP(GPIOZ_8),
	GPIO_GROUP(GPIOZ_9),
	GPIO_GROUP(GPIOZ_10),
	GPIO_GROUP(GPIOZ_11),
	GPIO_GROUP(GPIOZ_12),
	GPIO_GROUP(GPIOZ_13),
	GPIO_GROUP(GPIOZ_14),
	GPIO_GROUP(CARD_0),
	GPIO_GROUP(CARD_1),
	GPIO_GROUP(CARD_2),
	GPIO_GROUP(CARD_3),
	GPIO_GROUP(CARD_4),
	GPIO_GROUP(CARD_5),
	GPIO_GROUP(CARD_6),
	GPIO_GROUP(BOOT_0),
	GPIO_GROUP(BOOT_1),
	GPIO_GROUP(BOOT_2),
	GPIO_GROUP(BOOT_3),
	GPIO_GROUP(BOOT_4),
	GPIO_GROUP(BOOT_5),
	GPIO_GROUP(BOOT_6),
	GPIO_GROUP(BOOT_7),
	GPIO_GROUP(BOOT_8),
	GPIO_GROUP(BOOT_9),
	GPIO_GROUP(BOOT_10),
	GPIO_GROUP(BOOT_11),
	GPIO_GROUP(BOOT_12),
	GPIO_GROUP(BOOT_13),
	GPIO_GROUP(BOOT_14),
	GPIO_GROUP(BOOT_15),
	GPIO_GROUP(BOOT_16),
	GPIO_GROUP(BOOT_17),
	GPIO_GROUP(BOOT_18),

	/* bank X */
	GROUP(sd_d0_a,		8,	5),
	GROUP(sd_d1_a,		8,	4),
	GROUP(sd_d2_a,		8,	3),
	GROUP(sd_d3_a,		8,	2),
	GROUP(sd_clk_a,		8,	1),
	GROUP(sd_cmd_a,		8,	0),

	GROUP(sdxc_d0_a,	5,	14),
	GROUP(sdxc_d13_a,	5,	13),
	GROUP(sdxc_d47_a,	5,	12),
	GROUP(sdxc_clk_a,	5,	11),
	GROUP(sdxc_cmd_a,	5,	10),

	GROUP(pcm_out_a,	3,	30),
	GROUP(pcm_in_a,		3,	29),
	GROUP(pcm_fs_a,		3,	28),
	GROUP(pcm_clk_a,	3,	27),

	GROUP(uart_tx_a0,	4,	17),
	GROUP(uart_rx_a0,	4,	16),
	GROUP(uart_cts_a0,	4,	15),
	GROUP(uart_rts_a0,	4,	14),

	GROUP(uart_tx_a1,	4,	13),
	GROUP(uart_rx_a1,	4,	12),
	GROUP(uart_cts_a1,	4,	11),
	GROUP(uart_rts_a1,	4,	10),

	GROUP(uart_tx_b0,	4,	9),
	GROUP(uart_rx_b0,	4,	8),
	GROUP(uart_cts_b0,	4,	7),
	GROUP(uart_rts_b0,	4,	6),

	GROUP(iso7816_det,	4,	21),
	GROUP(iso7816_reset,	4,	20),
	GROUP(iso7816_clk,	4,	19),
	GROUP(iso7816_data,	4,	18),

	GROUP(i2c_sda_d0,	4,	5),
	GROUP(i2c_sck_d0,	4,	4),

	GROUP(xtal_32k_out,	3,	22),
	GROUP(xtal_24m_out,	3,	23),

	GROUP(pwm_e,		9,	19),
	GROUP(pwm_b_x,		2,	3),

	/* bank Y */
	GROUP(uart_tx_c,	1,	19),
	GROUP(uart_rx_c,	1,	18),
	GROUP(uart_cts_c,	1,	17),
	GROUP(uart_rts_c,	1,	16),

	GROUP(pcm_out_b,	4,	25),
	GROUP(pcm_in_b,		4,	24),
	GROUP(pcm_fs_b,		4,	23),
	GROUP(pcm_clk_b,	4,	22),

	GROUP(i2c_sda_c0,	1,	15),
	GROUP(i2c_sck_c0,	1,	14),

	GROUP(pwm_a_y,		9,	14),

	GROUP(i2s_out_ch45,	1,	10),
	GROUP(i2s_out_ch23,	1,	19),
	GROUP(i2s_out_ch01,	1,	6),
	GROUP(i2s_in_ch01,	1,	5),
	GROUP(i2s_lr_clk_in,	1,	4),
	GROUP(i2s_ao_clk_in,	1,	2),
	GROUP(i2s_am_clk,	1,	0),
	GROUP(i2s_out_ch78,	1,	11),

	GROUP(spdअगर_in,		1,	8),
	GROUP(spdअगर_out,	1,	7),

	/* bank DV */
	GROUP(dvin_rgb,		0,	6),
	GROUP(dvin_vs,		0,	9),
	GROUP(dvin_hs,		0,	8),
	GROUP(dvin_clk,		0,	7),
	GROUP(dvin_de,		0,	10),

	GROUP(enc_0,		7,	0),
	GROUP(enc_1,		7,	1),
	GROUP(enc_2,		7,	2),
	GROUP(enc_3,		7,	3),
	GROUP(enc_4,		7,	4),
	GROUP(enc_5,		7,	5),
	GROUP(enc_6,		7,	6),
	GROUP(enc_7,		7,	7),
	GROUP(enc_8,		7,	8),
	GROUP(enc_9,		7,	9),
	GROUP(enc_10,		7,	10),
	GROUP(enc_11,		7,	11),
	GROUP(enc_12,		7,	12),
	GROUP(enc_13,		7,	13),
	GROUP(enc_14,		7,	14),
	GROUP(enc_15,		7,	15),
	GROUP(enc_16,		7,	16),
	GROUP(enc_17,		7,	17),

	GROUP(uart_tx_b1,	6,	23),
	GROUP(uart_rx_b1,	6,	22),
	GROUP(uart_cts_b1,	6,	21),
	GROUP(uart_rts_b1,	6,	20),

	GROUP(vga_vs,		0,	21),
	GROUP(vga_hs,		0,	20),

	GROUP(pwm_c_dv9,	3,	24),
	GROUP(pwm_c_dv29,	3,	25),
	GROUP(pwm_d,		3,	26),

	/* bank H */
	GROUP(hdmi_hpd,		1,	26),
	GROUP(hdmi_sda,		1,	25),
	GROUP(hdmi_scl,		1,	24),
	GROUP(hdmi_cec,		1,	23),

	GROUP(spi_ss0_0,	9,	13),
	GROUP(spi_miso_0,	9,	12),
	GROUP(spi_mosi_0,	9,	11),
	GROUP(spi_sclk_0,	9,	10),

	GROUP(i2c_sda_d1,	4,	3),
	GROUP(i2c_sck_d1,	4,	2),

	/* bank Z */
	GROUP(spi_ss0_1,	8,	16),
	GROUP(spi_ss1_1,	8,	12),
	GROUP(spi_sclk_1,	8,	15),
	GROUP(spi_mosi_1,	8,	14),
	GROUP(spi_miso_1,	8,	13),
	GROUP(spi_ss2_1,	8,	17),

	GROUP(eth_tx_clk_50m,	6,	15),
	GROUP(eth_tx_en,	6,	14),
	GROUP(eth_txd1,		6,	13),
	GROUP(eth_txd0,		6,	12),
	GROUP(eth_rx_clk_in,	6,	10),
	GROUP(eth_rx_dv,	6,	11),
	GROUP(eth_rxd1,		6,	8),
	GROUP(eth_rxd0,		6,	7),
	GROUP(eth_mdio,		6,	6),
	GROUP(eth_mdc,		6,	5),

	/* NOTE: the following four groups are only available on Meson8m2: */
	GROUP(eth_rxd2,		6,	3),
	GROUP(eth_rxd3,		6,	2),
	GROUP(eth_txd2,		6,	1),
	GROUP(eth_txd3,		6,	0),

	GROUP(i2c_sda_a0,	5,	31),
	GROUP(i2c_sck_a0,	5,	30),

	GROUP(i2c_sda_b,	5,	27),
	GROUP(i2c_sck_b,	5,	26),

	GROUP(i2c_sda_c1,	5,	25),
	GROUP(i2c_sck_c1,	5,	24),

	GROUP(i2c_sda_a1,	5,	9),
	GROUP(i2c_sck_a1,	5,	8),

	GROUP(i2c_sda_a2,	5,	7),
	GROUP(i2c_sck_a2,	5,	6),

	GROUP(pwm_a_z0,		9,	16),
	GROUP(pwm_a_z7,		2,	0),
	GROUP(pwm_b_z,		9,	15),
	GROUP(pwm_c_z,		2,	1),

	/* bank BOOT */
	GROUP(sd_d0_c,		6,	29),
	GROUP(sd_d1_c,		6,	28),
	GROUP(sd_d2_c,		6,	27),
	GROUP(sd_d3_c,		6,	26),
	GROUP(sd_cmd_c,		6,	25),
	GROUP(sd_clk_c,		6,	24),

	GROUP(sdxc_d0_c,	4,	30),
	GROUP(sdxc_d13_c,	4,	29),
	GROUP(sdxc_d47_c,	4,	28),
	GROUP(sdxc_cmd_c,	4,	27),
	GROUP(sdxc_clk_c,	4,	26),

	GROUP(nand_io,		2,	26),
	GROUP(nand_io_ce0,	2,	25),
	GROUP(nand_io_ce1,	2,	24),
	GROUP(nand_io_rb0,	2,	17),
	GROUP(nand_ale,		2,	21),
	GROUP(nand_cle,		2,	20),
	GROUP(nand_wen_clk,	2,	19),
	GROUP(nand_ren_clk,	2,	18),
	GROUP(nand_dqs,		2,	27),
	GROUP(nand_ce2,		2,	23),
	GROUP(nand_ce3,		2,	22),

	GROUP(nor_d,		5,	1),
	GROUP(nor_q,		5,	3),
	GROUP(nor_c,		5,	2),
	GROUP(nor_cs,		5,	0),

	/* bank CARD */
	GROUP(sd_d1_b,		2,	14),
	GROUP(sd_d0_b,		2,	15),
	GROUP(sd_clk_b,		2,	11),
	GROUP(sd_cmd_b,		2,	10),
	GROUP(sd_d3_b,		2,	12),
	GROUP(sd_d2_b,		2,	13),

	GROUP(sdxc_d13_b,	2,	6),
	GROUP(sdxc_d0_b,	2,	7),
	GROUP(sdxc_clk_b,	2,	5),
	GROUP(sdxc_cmd_b,	2,	4),
पूर्ण;

अटल काष्ठा meson_pmx_group meson8_aobus_groups[] = अणु
	GPIO_GROUP(GPIOAO_0),
	GPIO_GROUP(GPIOAO_1),
	GPIO_GROUP(GPIOAO_2),
	GPIO_GROUP(GPIOAO_3),
	GPIO_GROUP(GPIOAO_4),
	GPIO_GROUP(GPIOAO_5),
	GPIO_GROUP(GPIOAO_6),
	GPIO_GROUP(GPIOAO_7),
	GPIO_GROUP(GPIOAO_8),
	GPIO_GROUP(GPIOAO_9),
	GPIO_GROUP(GPIOAO_10),
	GPIO_GROUP(GPIOAO_11),
	GPIO_GROUP(GPIOAO_12),
	GPIO_GROUP(GPIOAO_13),
	GPIO_GROUP(GPIO_BSD_EN),
	GPIO_GROUP(GPIO_TEST_N),

	/* bank AO */
	GROUP(uart_tx_ao_a,		0,	12),
	GROUP(uart_rx_ao_a,		0,	11),
	GROUP(uart_cts_ao_a,		0,	10),
	GROUP(uart_rts_ao_a,		0,	9),

	GROUP(remote_input,		0,	0),
	GROUP(remote_output_ao,		0,	31),

	GROUP(i2c_slave_sck_ao,		0,	2),
	GROUP(i2c_slave_sda_ao,		0,	1),

	GROUP(uart_tx_ao_b0,		0,	26),
	GROUP(uart_rx_ao_b0,		0,	25),

	GROUP(uart_tx_ao_b1,		0,	24),
	GROUP(uart_rx_ao_b1,		0,	23),

	GROUP(i2c_mst_sck_ao,		0,	6),
	GROUP(i2c_mst_sda_ao,		0,	5),

	GROUP(pwm_f_ao,			0,	19),

	GROUP(i2s_am_clk_out_ao,	0,	30),
	GROUP(i2s_ao_clk_out_ao,	0,	29),
	GROUP(i2s_lr_clk_out_ao,	0,	28),
	GROUP(i2s_out_ch01_ao,		0,	27),

	GROUP(hdmi_cec_ao,		0,	17),
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_periphs_groups[] = अणु
	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13", "GPIOX_14",
	"GPIOX_15", "GPIOX_16", "GPIOX_17", "GPIOX_18", "GPIOX_19",
	"GPIOX_20", "GPIOX_21",

	"GPIOY_0", "GPIOY_1", "GPIOY_2", "GPIOY_3", "GPIOY_4",
	"GPIOY_5", "GPIOY_6", "GPIOY_7", "GPIOY_8", "GPIOY_9",
	"GPIOY_10", "GPIOY_11", "GPIOY_12", "GPIOY_13", "GPIOY_14",
	"GPIOY_15", "GPIOY_16",

	"GPIODV_0", "GPIODV_1", "GPIODV_2", "GPIODV_3", "GPIODV_4",
	"GPIODV_5", "GPIODV_6", "GPIODV_7", "GPIODV_8", "GPIODV_9",
	"GPIODV_10", "GPIODV_11", "GPIODV_12", "GPIODV_13", "GPIODV_14",
	"GPIODV_15", "GPIODV_16", "GPIODV_17", "GPIODV_18", "GPIODV_19",
	"GPIODV_20", "GPIODV_21", "GPIODV_22", "GPIODV_23", "GPIODV_24",
	"GPIODV_25", "GPIODV_26", "GPIODV_27", "GPIODV_28", "GPIODV_29",

	"GPIOH_0", "GPIOH_1", "GPIOH_2", "GPIOH_3", "GPIOH_4",
	"GPIOH_5", "GPIOH_6", "GPIOH_7", "GPIOH_8", "GPIOH_9",

	"GPIOZ_0", "GPIOZ_1", "GPIOZ_2", "GPIOZ_3", "GPIOZ_4",
	"GPIOZ_5", "GPIOZ_6", "GPIOZ_7", "GPIOZ_8", "GPIOZ_9",
	"GPIOZ_10", "GPIOZ_11", "GPIOZ_12", "GPIOZ_13", "GPIOZ_14",

	"CARD_0", "CARD_1", "CARD_2", "CARD_3", "CARD_4",
	"CARD_5", "CARD_6",

	"BOOT_0", "BOOT_1", "BOOT_2", "BOOT_3", "BOOT_4",
	"BOOT_5", "BOOT_6", "BOOT_7", "BOOT_8", "BOOT_9",
	"BOOT_10", "BOOT_11", "BOOT_12", "BOOT_13", "BOOT_14",
	"BOOT_15", "BOOT_16", "BOOT_17", "BOOT_18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_aobus_groups[] = अणु
	"GPIOAO_0", "GPIOAO_1", "GPIOAO_2", "GPIOAO_3",
	"GPIOAO_4", "GPIOAO_5", "GPIOAO_6", "GPIOAO_7",
	"GPIOAO_8", "GPIOAO_9", "GPIOAO_10", "GPIOAO_11",
	"GPIOAO_12", "GPIOAO_13", "GPIO_BSD_EN", "GPIO_TEST_N"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd_a_groups[] = अणु
	"sd_d0_a", "sd_d1_a", "sd_d2_a", "sd_d3_a", "sd_clk_a", "sd_cmd_a"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdxc_a_groups[] = अणु
	"sdxc_d0_a", "sdxc_d13_a", "sdxc_d47_a", "sdxc_clk_a", "sdxc_cmd_a"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_a_groups[] = अणु
	"pcm_out_a", "pcm_in_a", "pcm_fs_a", "pcm_clk_a"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_a_groups[] = अणु
	"uart_tx_a0", "uart_rx_a0", "uart_cts_a0", "uart_rts_a0",
	"uart_tx_a1", "uart_rx_a1", "uart_cts_a1", "uart_rts_a1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_b_groups[] = अणु
	"uart_tx_b0", "uart_rx_b0", "uart_cts_b0", "uart_rts_b0",
	"uart_tx_b1", "uart_rx_b1", "uart_cts_b1", "uart_rts_b1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर iso7816_groups[] = अणु
	"iso7816_det", "iso7816_reset", "iso7816_clk", "iso7816_data"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_d_groups[] = अणु
	"i2c_sda_d0", "i2c_sck_d0", "i2c_sda_d1", "i2c_sck_d1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर xtal_groups[] = अणु
	"xtal_32k_out", "xtal_24m_out"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_c_groups[] = अणु
	"uart_tx_c", "uart_rx_c", "uart_cts_c", "uart_rts_c"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm_b_groups[] = अणु
	"pcm_out_b", "pcm_in_b", "pcm_fs_b", "pcm_clk_b"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_c_groups[] = अणु
	"i2c_sda_c0", "i2c_sck_c0", "i2c_sda_c1", "i2c_sck_c1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर dvin_groups[] = अणु
	"dvin_rgb", "dvin_vs", "dvin_hs", "dvin_clk", "dvin_de"
पूर्ण;

अटल स्थिर अक्षर * स्थिर enc_groups[] = अणु
	"enc_0", "enc_1", "enc_2", "enc_3", "enc_4", "enc_5",
	"enc_6", "enc_7", "enc_8", "enc_9", "enc_10", "enc_11",
	"enc_12", "enc_13", "enc_14", "enc_15", "enc_16", "enc_17"
पूर्ण;

अटल स्थिर अक्षर * स्थिर vga_groups[] = अणु
	"vga_vs", "vga_hs"
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_groups[] = अणु
	"hdmi_hpd", "hdmi_sda", "hdmi_scl", "hdmi_cec"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_groups[] = अणु
	"spi_ss0_0", "spi_miso_0", "spi_mosi_0", "spi_sclk_0",
	"spi_ss0_1", "spi_ss1_1", "spi_sclk_1", "spi_mosi_1",
	"spi_miso_1", "spi_ss2_1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर ethernet_groups[] = अणु
	"eth_tx_clk_50m", "eth_tx_en", "eth_txd1",
	"eth_txd0", "eth_rx_clk_in", "eth_rx_dv",
	"eth_rxd1", "eth_rxd0", "eth_mdio", "eth_mdc", "eth_rxd2",
	"eth_rxd3", "eth_txd2", "eth_txd3"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_a_groups[] = अणु
	"i2c_sda_a0", "i2c_sck_a0", "i2c_sda_a1", "i2c_sck_a1",
	"i2c_sda_a2", "i2c_sck_a2"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_b_groups[] = अणु
	"i2c_sda_b", "i2c_sck_b"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s_groups[] = अणु
	"i2s_out_ch45", "i2s_out_ch23_pins", "i2s_out_ch01_pins",
	"i2s_in_ch01_pins", "i2s_lr_clk_in_pins", "i2s_ao_clk_in_pins",
	"i2s_am_clk_pins", "i2s_out_ch78_pins"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd_c_groups[] = अणु
	"sd_d0_c", "sd_d1_c", "sd_d2_c", "sd_d3_c",
	"sd_cmd_c", "sd_clk_c"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdxc_c_groups[] = अणु
	"sdxc_d0_c", "sdxc_d13_c", "sdxc_d47_c", "sdxc_cmd_c",
	"sdxc_clk_c"
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand_groups[] = अणु
	"nand_io", "nand_io_ce0", "nand_io_ce1",
	"nand_io_rb0", "nand_ale", "nand_cle",
	"nand_wen_clk", "nand_ren_clk", "nand_dqs",
	"nand_ce2", "nand_ce3"
पूर्ण;

अटल स्थिर अक्षर * स्थिर nor_groups[] = अणु
	"nor_d", "nor_q", "nor_c", "nor_cs"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_a_groups[] = अणु
	"pwm_a_y", "pwm_a_z0", "pwm_a_z7"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_b_groups[] = अणु
	"pwm_b_x", "pwm_b_z"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_c_groups[] = अणु
	"pwm_c_dv9", "pwm_c_dv29", "pwm_c_z"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_d_groups[] = अणु
	"pwm_d"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_e_groups[] = अणु
	"pwm_e"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd_b_groups[] = अणु
	"sd_d1_b", "sd_d0_b", "sd_clk_b", "sd_cmd_b",
	"sd_d3_b", "sd_d2_b"
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdxc_b_groups[] = अणु
	"sdxc_d13_b", "sdxc_d0_b", "sdxc_clk_b", "sdxc_cmd_b"
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगर_groups[] = अणु
	"spdif_in", "spdif_out"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_ao_groups[] = अणु
	"uart_tx_ao_a", "uart_rx_ao_a", "uart_cts_ao_a", "uart_rts_ao_a"
पूर्ण;

अटल स्थिर अक्षर * स्थिर remote_groups[] = अणु
	"remote_input", "remote_output_ao"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_slave_ao_groups[] = अणु
	"i2c_slave_sck_ao", "i2c_slave_sda_ao"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_ao_b_groups[] = अणु
	"uart_tx_ao_b0", "uart_rx_ao_b0", "uart_tx_ao_b1", "uart_rx_ao_b1"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_mst_ao_groups[] = अणु
	"i2c_mst_sck_ao", "i2c_mst_sda_ao"
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_f_ao_groups[] = अणु
	"pwm_f_ao"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s_ao_groups[] = अणु
	"i2s_am_clk_out_ao", "i2s_ao_clk_out_ao", "i2s_lr_clk_out_ao",
	"i2s_out_ch01_ao"
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_cec_ao_groups[] = अणु
	"hdmi_cec_ao"
पूर्ण;

अटल काष्ठा meson_pmx_func meson8_cbus_functions[] = अणु
	FUNCTION(gpio_periphs),
	FUNCTION(sd_a),
	FUNCTION(sdxc_a),
	FUNCTION(pcm_a),
	FUNCTION(uart_a),
	FUNCTION(uart_b),
	FUNCTION(iso7816),
	FUNCTION(i2c_d),
	FUNCTION(xtal),
	FUNCTION(uart_c),
	FUNCTION(pcm_b),
	FUNCTION(i2c_c),
	FUNCTION(dvin),
	FUNCTION(enc),
	FUNCTION(vga),
	FUNCTION(hdmi),
	FUNCTION(spi),
	FUNCTION(ethernet),
	FUNCTION(i2c_a),
	FUNCTION(i2c_b),
	FUNCTION(sd_c),
	FUNCTION(sdxc_c),
	FUNCTION(nand),
	FUNCTION(nor),
	FUNCTION(sd_b),
	FUNCTION(sdxc_b),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_e),
	FUNCTION(i2s),
	FUNCTION(spdअगर),
पूर्ण;

अटल काष्ठा meson_pmx_func meson8_aobus_functions[] = अणु
	FUNCTION(gpio_aobus),
	FUNCTION(uart_ao),
	FUNCTION(remote),
	FUNCTION(i2c_slave_ao),
	FUNCTION(uart_ao_b),
	FUNCTION(i2c_mst_ao),
	FUNCTION(pwm_f_ao),
	FUNCTION(i2s_ao),
	FUNCTION(hdmi_cec_ao),
पूर्ण;

अटल काष्ठा meson_bank meson8_cbus_banks[] = अणु
	/*   name    first     last         irq       pullen  pull    dir     out     in  */
	BANK("X",    GPIOX_0,  GPIOX_21,    112, 133, 4,  0,  4,  0,  0,  0,  1,  0,  2,  0),
	BANK("Y",    GPIOY_0,  GPIOY_16,    95,  111, 3,  0,  3,  0,  3,  0,  4,  0,  5,  0),
	BANK("DV",   GPIODV_0, GPIODV_29,   65,   94, 0,  0,  0,  0,  7,  0,  8,  0,  9,  0),
	BANK("H",    GPIOH_0,  GPIOH_9,     29,   38, 1, 16,  1, 16,  9, 19, 10, 19, 11, 19),
	BANK("Z",    GPIOZ_0,  GPIOZ_14,    14,   28, 1,  0,  1,  0,  3, 17,  4, 17,  5, 17),
	BANK("CARD", CARD_0,   CARD_6,      58,   64, 2, 20,  2, 20,  0, 22,  1, 22,  2, 22),
	BANK("BOOT", BOOT_0,   BOOT_18,     39,   57, 2,  0,  2,  0,  9,  0, 10,  0, 11,  0),
पूर्ण;

अटल काष्ठा meson_bank meson8_aobus_banks[] = अणु
	/*   name    first     last         irq    pullen  pull    dir     out     in  */
	BANK("AO",   GPIOAO_0, GPIO_TEST_N, 0, 13, 0, 16,  0,  0,  0,  0,  0, 16,  1,  0),
पूर्ण;

अटल काष्ठा meson_pinctrl_data meson8_cbus_pinctrl_data = अणु
	.name		= "cbus-banks",
	.pins		= meson8_cbus_pins,
	.groups		= meson8_cbus_groups,
	.funcs		= meson8_cbus_functions,
	.banks		= meson8_cbus_banks,
	.num_pins	= ARRAY_SIZE(meson8_cbus_pins),
	.num_groups	= ARRAY_SIZE(meson8_cbus_groups),
	.num_funcs	= ARRAY_SIZE(meson8_cbus_functions),
	.num_banks	= ARRAY_SIZE(meson8_cbus_banks),
	.pmx_ops	= &meson8_pmx_ops,
पूर्ण;

अटल काष्ठा meson_pinctrl_data meson8_aobus_pinctrl_data = अणु
	.name		= "ao-bank",
	.pins		= meson8_aobus_pins,
	.groups		= meson8_aobus_groups,
	.funcs		= meson8_aobus_functions,
	.banks		= meson8_aobus_banks,
	.num_pins	= ARRAY_SIZE(meson8_aobus_pins),
	.num_groups	= ARRAY_SIZE(meson8_aobus_groups),
	.num_funcs	= ARRAY_SIZE(meson8_aobus_functions),
	.num_banks	= ARRAY_SIZE(meson8_aobus_banks),
	.pmx_ops	= &meson8_pmx_ops,
	.parse_dt	= &meson8_aobus_parse_dt_extra,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson8_pinctrl_dt_match[] = अणु
	अणु
		.compatible = "amlogic,meson8-cbus-pinctrl",
		.data = &meson8_cbus_pinctrl_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8-aobus-pinctrl",
		.data = &meson8_aobus_pinctrl_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8m2-cbus-pinctrl",
		.data = &meson8_cbus_pinctrl_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8m2-aobus-pinctrl",
		.data = &meson8_aobus_pinctrl_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver meson8_pinctrl_driver = अणु
	.probe		= meson_pinctrl_probe,
	.driver = अणु
		.name	= "meson8-pinctrl",
		.of_match_table = meson8_pinctrl_dt_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(meson8_pinctrl_driver);
