<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Pin controller and GPIO driver क्रम Amlogic Meson A1 SoC.
 *
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 * Author: Qianggui Song <qianggui.song@amlogic.com>
 */

#समावेश <dt-bindings/gpio/meson-a1-gpपन.स>
#समावेश "pinctrl-meson.h"
#समावेश "pinctrl-meson-axg-pmx.h"

अटल स्थिर काष्ठा pinctrl_pin_desc meson_a1_periphs_pins[] = अणु
	MESON_PIN(GPIOP_0),
	MESON_PIN(GPIOP_1),
	MESON_PIN(GPIOP_2),
	MESON_PIN(GPIOP_3),
	MESON_PIN(GPIOP_4),
	MESON_PIN(GPIOP_5),
	MESON_PIN(GPIOP_6),
	MESON_PIN(GPIOP_7),
	MESON_PIN(GPIOP_8),
	MESON_PIN(GPIOP_9),
	MESON_PIN(GPIOP_10),
	MESON_PIN(GPIOP_11),
	MESON_PIN(GPIOP_12),
	MESON_PIN(GPIOB_0),
	MESON_PIN(GPIOB_1),
	MESON_PIN(GPIOB_2),
	MESON_PIN(GPIOB_3),
	MESON_PIN(GPIOB_4),
	MESON_PIN(GPIOB_5),
	MESON_PIN(GPIOB_6),
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
	MESON_PIN(GPIOF_0),
	MESON_PIN(GPIOF_1),
	MESON_PIN(GPIOF_2),
	MESON_PIN(GPIOF_3),
	MESON_PIN(GPIOF_4),
	MESON_PIN(GPIOF_5),
	MESON_PIN(GPIOF_6),
	MESON_PIN(GPIOF_7),
	MESON_PIN(GPIOF_8),
	MESON_PIN(GPIOF_9),
	MESON_PIN(GPIOF_10),
	MESON_PIN(GPIOF_11),
	MESON_PIN(GPIOF_12),
	MESON_PIN(GPIOA_0),
	MESON_PIN(GPIOA_1),
	MESON_PIN(GPIOA_2),
	MESON_PIN(GPIOA_3),
	MESON_PIN(GPIOA_4),
	MESON_PIN(GPIOA_5),
	MESON_PIN(GPIOA_6),
	MESON_PIN(GPIOA_7),
	MESON_PIN(GPIOA_8),
	MESON_PIN(GPIOA_9),
	MESON_PIN(GPIOA_10),
	MESON_PIN(GPIOA_11),
पूर्ण;

/* psram */
अटल स्थिर अचिन्हित पूर्णांक psram_clkn_pins[]		= अणु GPIOP_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_clkp_pins[]		= अणु GPIOP_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_ce_n_pins[]		= अणु GPIOP_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_rst_n_pins[]		= अणु GPIOP_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq0_pins[]		= अणु GPIOP_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq1_pins[]		= अणु GPIOP_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq2_pins[]		= अणु GPIOP_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq3_pins[]		= अणु GPIOP_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq4_pins[]		= अणु GPIOP_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq5_pins[]		= अणु GPIOP_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq6_pins[]		= अणु GPIOP_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_adq7_pins[]		= अणु GPIOP_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक psram_dqs_dm_pins[]		= अणु GPIOP_12 पूर्ण;

/* sdcard */
अटल स्थिर अचिन्हित पूर्णांक sdcard_d0_b_pins[]		= अणु GPIOB_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d1_b_pins[]		= अणु GPIOB_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d2_b_pins[]		= अणु GPIOB_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d3_b_pins[]		= अणु GPIOB_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_clk_b_pins[]		= अणु GPIOB_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_cmd_b_pins[]		= अणु GPIOB_5 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sdcard_d0_x_pins[]		= अणु GPIOX_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d1_x_pins[]		= अणु GPIOX_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d2_x_pins[]		= अणु GPIOX_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d3_x_pins[]		= अणु GPIOX_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_clk_x_pins[]		= अणु GPIOX_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_cmd_x_pins[]		= अणु GPIOX_5 पूर्ण;

/* spअगर */
अटल स्थिर अचिन्हित पूर्णांक spअगर_mo_pins[]		= अणु GPIOB_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spअगर_mi_pins[]		= अणु GPIOB_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spअगर_wp_n_pins[]		= अणु GPIOB_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spअगर_hold_n_pins[]		= अणु GPIOB_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spअगर_clk_pins[]		= अणु GPIOB_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spअगर_cs_pins[]		= अणु GPIOB_5 पूर्ण;

/* i2c0 */
अटल स्थिर अचिन्हित पूर्णांक i2c0_sck_f9_pins[]		= अणु GPIOF_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_sda_f10_pins[]		= अणु GPIOF_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_sck_f11_pins[]		= अणु GPIOF_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_sda_f12_pins[]		= अणु GPIOF_12 पूर्ण;

/* i2c1 */
अटल स्थिर अचिन्हित पूर्णांक i2c1_sda_x_pins[]		= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_sck_x_pins[]		= अणु GPIOX_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_sda_a_pins[]		= अणु GPIOA_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_sck_a_pins[]		= अणु GPIOA_11 पूर्ण;

/* i2c2 */
अटल स्थिर अचिन्हित पूर्णांक i2c2_sck_x0_pins[]		= अणु GPIOX_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_sda_x1_pins[]		= अणु GPIOX_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_sck_x15_pins[]		= अणु GPIOX_15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_sda_x16_pins[]		= अणु GPIOX_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_sck_a4_pins[]		= अणु GPIOA_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_sda_a5_pins[]		= अणु GPIOA_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_sck_a8_pins[]		= अणु GPIOA_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_sda_a9_pins[]		= अणु GPIOA_9 पूर्ण;

/* i2c3 */
अटल स्थिर अचिन्हित पूर्णांक i2c3_sck_f_pins[]		= अणु GPIOF_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c3_sda_f_pins[]		= अणु GPIOF_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c3_sck_x_pins[]		= अणु GPIOX_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c3_sda_x_pins[]		= अणु GPIOX_12 पूर्ण;

/* i2c slave */
अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sck_a_pins[]	= अणु GPIOA_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sda_a_pins[]	= अणु GPIOA_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sck_f_pins[]	= अणु GPIOF_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sda_f_pins[]	= अणु GPIOF_12 पूर्ण;

/* uart_a */
अटल स्थिर अचिन्हित पूर्णांक uart_a_tx_pins[]		= अणु GPIOX_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_a_rx_pins[]		= अणु GPIOX_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_a_cts_pins[]		= अणु GPIOX_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_a_rts_pins[]		= अणु GPIOX_14 पूर्ण;

/* uart_b */
अटल स्थिर अचिन्हित पूर्णांक uart_b_tx_x_pins[]		= अणु GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_b_rx_x_pins[]		= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_b_tx_f_pins[]		= अणु GPIOF_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_b_rx_f_pins[]		= अणु GPIOF_1 पूर्ण;

/* uart_c */
अटल स्थिर अचिन्हित पूर्णांक uart_c_tx_x0_pins[]		= अणु GPIOX_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_c_rx_x1_pins[]		= अणु GPIOX_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_c_cts_pins[]		= अणु GPIOX_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_c_rts_pins[]		= अणु GPIOX_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_c_tx_x15_pins[]		= अणु GPIOX_15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_c_rx_x16_pins[]		= अणु GPIOX_16 पूर्ण;

/* pmw_a */
अटल स्थिर अचिन्हित पूर्णांक pwm_a_x6_pins[]		= अणु GPIOX_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_a_x7_pins[]		= अणु GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_a_f6_pins[]		= अणु GPIOF_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_a_f10_pins[]		= अणु GPIOF_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_a_a_pins[]		= अणु GPIOA_5 पूर्ण;

/* pmw_b */
अटल स्थिर अचिन्हित पूर्णांक pwm_b_x_pins[]		= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_b_f_pins[]		= अणु GPIOF_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_b_a_pins[]		= अणु GPIOA_11 पूर्ण;

/* pmw_c */
अटल स्थिर अचिन्हित पूर्णांक pwm_c_x_pins[]		= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_c_f3_pins[]		= अणु GPIOF_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_c_f8_pins[]		= अणु GPIOF_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_c_a_pins[]		= अणु GPIOA_10 पूर्ण;

/* pwm_d */
अटल स्थिर अचिन्हित पूर्णांक pwm_d_x10_pins[]		= अणु GPIOX_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_d_x13_pins[]		= अणु GPIOX_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_d_x15_pins[]		= अणु GPIOX_15 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_d_f_pins[]		= अणु GPIOF_11 पूर्ण;

/* pwm_e */
अटल स्थिर अचिन्हित पूर्णांक pwm_e_p_pins[]		= अणु GPIOP_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_e_x2_pins[]		= अणु GPIOX_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_e_x14_pins[]		= अणु GPIOX_14 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_e_x16_pins[]		= अणु GPIOX_16 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_e_f_pins[]		= अणु GPIOF_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_e_a_pins[]		= अणु GPIOA_0 पूर्ण;

/* pwm_f */
अटल स्थिर अचिन्हित पूर्णांक pwm_f_b_pins[]		= अणु GPIOB_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_f_x_pins[]		= अणु GPIOX_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_f_f4_pins[]		= अणु GPIOF_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_f_f12_pins[]		= अणु GPIOF_12 पूर्ण;

/* pwm_a_hiz */
अटल स्थिर अचिन्हित पूर्णांक pwm_a_hiz_f8_pins[]		= अणु GPIOF_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_a_hiz_f10_pins[]		= अणु GPIOF_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pmw_a_hiz_f6_pins[]		= अणु GPIOF_6 पूर्ण;

/* pwm_b_hiz */
अटल स्थिर अचिन्हित पूर्णांक pwm_b_hiz_pins[]		= अणु GPIOF_7 पूर्ण;

/* pmw_c_hiz */
अटल स्थिर अचिन्हित पूर्णांक pwm_c_hiz_pins[]		= अणु GPIOF_8 पूर्ण;

/* tdm_a */
अटल स्थिर अचिन्हित पूर्णांक tdm_a_करोut1_pins[]		= अणु GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_a_करोut0_pins[]		= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_a_fs_pins[]		= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_a_sclk_pins[]		= अणु GPIOX_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_a_din1_pins[]		= अणु GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_a_din0_pins[]		= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_a_slv_fs_pins[]		= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_a_slv_sclk_pins[]		= अणु GPIOX_10 पूर्ण;

/* spi_a */
अटल स्थिर अचिन्हित पूर्णांक spi_a_mosi_x2_pins[]		= अणु GPIOX_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_ss0_x3_pins[]		= अणु GPIOX_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_sclk_x4_pins[]		= अणु GPIOX_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_miso_x5_pins[]		= अणु GPIOX_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_mosi_x7_pins[]		= अणु GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_miso_x8_pins[]		= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_ss0_x9_pins[]		= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_sclk_x10_pins[]		= अणु GPIOX_10 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक spi_a_mosi_a_pins[]		= अणु GPIOA_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_miso_a_pins[]		= अणु GPIOA_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_ss0_a_pins[]		= अणु GPIOA_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_a_sclk_a_pins[]		= अणु GPIOA_9 पूर्ण;

/* pdm */
अटल स्थिर अचिन्हित पूर्णांक pdm_din0_x_pins[]		= अणु GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pdm_din1_x_pins[]		= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pdm_din2_x_pins[]		= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pdm_dclk_x_pins[]		= अणु GPIOX_10 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pdm_din2_a_pins[]		= अणु GPIOA_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pdm_din1_a_pins[]		= अणु GPIOA_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pdm_din0_a_pins[]		= अणु GPIOA_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pdm_dclk_pins[]		= अणु GPIOA_9 पूर्ण;

/* gen_clk */
अटल स्थिर अचिन्हित पूर्णांक gen_clk_x_pins[]		= अणु GPIOX_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gen_clk_f8_pins[]		= अणु GPIOF_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gen_clk_f10_pins[]		= अणु GPIOF_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक gen_clk_a_pins[]		= अणु GPIOA_11 पूर्ण;

/* jtag_a */
अटल स्थिर अचिन्हित पूर्णांक jtag_a_clk_pins[]		= अणु GPIOF_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक jtag_a_पंचांगs_pins[]		= अणु GPIOF_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक jtag_a_tdi_pins[]		= अणु GPIOF_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक jtag_a_tकरो_pins[]		= अणु GPIOF_7 पूर्ण;

/* clk_32_in */
अटल स्थिर अचिन्हित पूर्णांक clk_32k_in_pins[]		= अणु GPIOF_2 पूर्ण;

/* ir in */
अटल स्थिर अचिन्हित पूर्णांक remote_input_f_pins[]		= अणु GPIOF_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक remote_input_a_pins[]		= अणु GPIOA_11 पूर्ण;

/* ir out */
अटल स्थिर अचिन्हित पूर्णांक remote_out_pins[]		= अणु GPIOF_5 पूर्ण;

/* spdअगर */
अटल स्थिर अचिन्हित पूर्णांक spdअगर_in_f6_pins[]		= अणु GPIOF_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spdअगर_in_f7_pins[]		= अणु GPIOF_7 पूर्ण;

/* sw */
अटल स्थिर अचिन्हित पूर्णांक swclk_pins[]			= अणु GPIOF_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक swdio_pins[]			= अणु GPIOF_5 पूर्ण;

/* clk_25 */
अटल स्थिर अचिन्हित पूर्णांक clk25_pins[]			= अणु GPIOF_10 पूर्ण;

/* cec_a */
अटल स्थिर अचिन्हित पूर्णांक cec_a_pins[]			= अणु GPIOF_2 पूर्ण;

/* cec_b */
अटल स्थिर अचिन्हित पूर्णांक cec_b_pins[]			= अणु GPIOF_2 पूर्ण;

/* clk12_24 */
अटल स्थिर अचिन्हित पूर्णांक clk12_24_pins[]		= अणु GPIOF_10 पूर्ण;

/* mclk_0 */
अटल स्थिर अचिन्हित पूर्णांक mclk_0_pins[]			= अणु GPIOA_0 पूर्ण;

/* tdm_b */
अटल स्थिर अचिन्हित पूर्णांक tdm_b_sclk_pins[]		= अणु GPIOA_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_fs_pins[]		= अणु GPIOA_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_करोut0_pins[]		= अणु GPIOA_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_करोut1_pins[]		= अणु GPIOA_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_करोut2_pins[]		= अणु GPIOA_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_करोut3_pins[]		= अणु GPIOA_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_करोut4_pins[]		= अणु GPIOA_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_करोut5_pins[]		= अणु GPIOA_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_slv_sclk_pins[]		= अणु GPIOA_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_slv_fs_pins[]		= अणु GPIOA_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_din0_pins[]		= अणु GPIOA_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_din1_pins[]		= अणु GPIOA_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_b_din2_pins[]		= अणु GPIOA_9 पूर्ण;

/* mclk_vad */
अटल स्थिर अचिन्हित पूर्णांक mclk_vad_pins[]		= अणु GPIOA_0 पूर्ण;

/* tdm_vad */
अटल स्थिर अचिन्हित पूर्णांक tdm_vad_sclk_a1_pins[]	= अणु GPIOA_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_vad_fs_a2_pins[]		= अणु GPIOA_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_vad_sclk_a5_pins[]	= अणु GPIOA_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tdm_vad_fs_a6_pins[]		= अणु GPIOA_6 पूर्ण;

/* tst_out */
अटल स्थिर अचिन्हित पूर्णांक tst_out0_pins[]		= अणु GPIOA_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out1_pins[]		= अणु GPIOA_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out2_pins[]		= अणु GPIOA_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out3_pins[]		= अणु GPIOA_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out4_pins[]		= अणु GPIOA_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out5_pins[]		= अणु GPIOA_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out6_pins[]		= अणु GPIOA_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out7_pins[]		= अणु GPIOA_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out8_pins[]		= अणु GPIOA_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out9_pins[]		= अणु GPIOA_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out10_pins[]		= अणु GPIOA_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tst_out11_pins[]		= अणु GPIOA_11 पूर्ण;

/* mute */
अटल स्थिर अचिन्हित पूर्णांक mute_key_pins[]		= अणु GPIOA_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mute_en_pins[]		= अणु GPIOA_5 पूर्ण;

अटल काष्ठा meson_pmx_group meson_a1_periphs_groups[] = अणु
	GPIO_GROUP(GPIOP_0),
	GPIO_GROUP(GPIOP_1),
	GPIO_GROUP(GPIOP_2),
	GPIO_GROUP(GPIOP_3),
	GPIO_GROUP(GPIOP_4),
	GPIO_GROUP(GPIOP_5),
	GPIO_GROUP(GPIOP_6),
	GPIO_GROUP(GPIOP_7),
	GPIO_GROUP(GPIOP_8),
	GPIO_GROUP(GPIOP_9),
	GPIO_GROUP(GPIOP_10),
	GPIO_GROUP(GPIOP_11),
	GPIO_GROUP(GPIOP_12),
	GPIO_GROUP(GPIOB_0),
	GPIO_GROUP(GPIOB_1),
	GPIO_GROUP(GPIOB_2),
	GPIO_GROUP(GPIOB_3),
	GPIO_GROUP(GPIOB_4),
	GPIO_GROUP(GPIOB_5),
	GPIO_GROUP(GPIOB_6),
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
	GPIO_GROUP(GPIOF_0),
	GPIO_GROUP(GPIOF_1),
	GPIO_GROUP(GPIOF_2),
	GPIO_GROUP(GPIOF_3),
	GPIO_GROUP(GPIOF_4),
	GPIO_GROUP(GPIOF_5),
	GPIO_GROUP(GPIOF_6),
	GPIO_GROUP(GPIOF_7),
	GPIO_GROUP(GPIOF_8),
	GPIO_GROUP(GPIOF_9),
	GPIO_GROUP(GPIOF_10),
	GPIO_GROUP(GPIOF_11),
	GPIO_GROUP(GPIOF_12),
	GPIO_GROUP(GPIOA_0),
	GPIO_GROUP(GPIOA_1),
	GPIO_GROUP(GPIOA_2),
	GPIO_GROUP(GPIOA_3),
	GPIO_GROUP(GPIOA_4),
	GPIO_GROUP(GPIOA_5),
	GPIO_GROUP(GPIOA_6),
	GPIO_GROUP(GPIOA_7),
	GPIO_GROUP(GPIOA_8),
	GPIO_GROUP(GPIOA_9),
	GPIO_GROUP(GPIOA_10),
	GPIO_GROUP(GPIOA_11),

	/* bank P func1 */
	GROUP(psram_clkn,		1),
	GROUP(psram_clkp,		1),
	GROUP(psram_ce_n,		1),
	GROUP(psram_rst_n,		1),
	GROUP(psram_adq0,		1),
	GROUP(psram_adq1,		1),
	GROUP(psram_adq2,		1),
	GROUP(psram_adq3,		1),
	GROUP(psram_adq4,		1),
	GROUP(psram_adq5,		1),
	GROUP(psram_adq6,		1),
	GROUP(psram_adq7,		1),
	GROUP(psram_dqs_dm,		1),

	/*bank P func2 */
	GROUP(pwm_e_p,			2),

	/*bank B func1 */
	GROUP(spअगर_mo,			1),
	GROUP(spअगर_mi,			1),
	GROUP(spअगर_wp_n,		1),
	GROUP(spअगर_hold_n,		1),
	GROUP(spअगर_clk,			1),
	GROUP(spअगर_cs,			1),
	GROUP(pwm_f_b,			1),

	/*bank B func2 */
	GROUP(sdcard_d0_b,		2),
	GROUP(sdcard_d1_b,		2),
	GROUP(sdcard_d2_b,		2),
	GROUP(sdcard_d3_b,		2),
	GROUP(sdcard_clk_b,		2),
	GROUP(sdcard_cmd_b,		2),

	/*bank X func1 */
	GROUP(sdcard_d0_x,		1),
	GROUP(sdcard_d1_x,		1),
	GROUP(sdcard_d2_x,		1),
	GROUP(sdcard_d3_x,		1),
	GROUP(sdcard_clk_x,		1),
	GROUP(sdcard_cmd_x,		1),
	GROUP(pwm_a_x6,			1),
	GROUP(tdm_a_करोut1,		1),
	GROUP(tdm_a_करोut0,		1),
	GROUP(tdm_a_fs,			1),
	GROUP(tdm_a_sclk,		1),
	GROUP(uart_a_tx,		1),
	GROUP(uart_a_rx,		1),
	GROUP(uart_a_cts,		1),
	GROUP(uart_a_rts,		1),
	GROUP(pwm_d_x15,		1),
	GROUP(pwm_e_x16,		1),

	/*bank X func2 */
	GROUP(i2c2_sck_x0,		2),
	GROUP(i2c2_sda_x1,		2),
	GROUP(spi_a_mosi_x2,		2),
	GROUP(spi_a_ss0_x3,		2),
	GROUP(spi_a_sclk_x4,		2),
	GROUP(spi_a_miso_x5,		2),
	GROUP(tdm_a_din1,		2),
	GROUP(tdm_a_din0,		2),
	GROUP(tdm_a_slv_fs,		2),
	GROUP(tdm_a_slv_sclk,		2),
	GROUP(i2c3_sck_x,		2),
	GROUP(i2c3_sda_x,		2),
	GROUP(pwm_d_x13,		2),
	GROUP(pwm_e_x14,		2),
	GROUP(i2c2_sck_x15,		2),
	GROUP(i2c2_sda_x16,		2),

	/*bank X func3 */
	GROUP(uart_c_tx_x0,		3),
	GROUP(uart_c_rx_x1,		3),
	GROUP(uart_c_cts,		3),
	GROUP(uart_c_rts,		3),
	GROUP(pdm_din0_x,		3),
	GROUP(pdm_din1_x,		3),
	GROUP(pdm_din2_x,		3),
	GROUP(pdm_dclk_x,		3),
	GROUP(uart_c_tx_x15,		3),
	GROUP(uart_c_rx_x16,		3),

	/*bank X func4 */
	GROUP(pwm_e_x2,			4),
	GROUP(pwm_f_x,			4),
	GROUP(spi_a_mosi_x7,		4),
	GROUP(spi_a_miso_x8,		4),
	GROUP(spi_a_ss0_x9,		4),
	GROUP(spi_a_sclk_x10,		4),

	/*bank X func5 */
	GROUP(uart_b_tx_x,		5),
	GROUP(uart_b_rx_x,		5),
	GROUP(i2c1_sda_x,		5),
	GROUP(i2c1_sck_x,		5),

	/*bank X func6 */
	GROUP(pwm_a_x7,			6),
	GROUP(pwm_b_x,			6),
	GROUP(pwm_c_x,			6),
	GROUP(pwm_d_x10,		6),

	/*bank X func7 */
	GROUP(gen_clk_x,		7),

	/*bank F func1 */
	GROUP(uart_b_tx_f,		1),
	GROUP(uart_b_rx_f,		1),
	GROUP(remote_input_f,		1),
	GROUP(jtag_a_clk,		1),
	GROUP(jtag_a_पंचांगs,		1),
	GROUP(jtag_a_tdi,		1),
	GROUP(jtag_a_tकरो,		1),
	GROUP(gen_clk_f8,		1),
	GROUP(pwm_a_f10,		1),
	GROUP(i2c0_sck_f11,		1),
	GROUP(i2c0_sda_f12,		1),

	/*bank F func2 */
	GROUP(clk_32k_in,		2),
	GROUP(pwm_e_f,			2),
	GROUP(pwm_f_f4,			2),
	GROUP(remote_out,		2),
	GROUP(spdअगर_in_f6,		2),
	GROUP(spdअगर_in_f7,		2),
	GROUP(pwm_a_hiz_f8,		2),
	GROUP(pwm_a_hiz_f10,		2),
	GROUP(pwm_d_f,			2),
	GROUP(pwm_f_f12,		2),

	/*bank F func3 */
	GROUP(pwm_c_f3,			3),
	GROUP(swclk,			3),
	GROUP(swdio,			3),
	GROUP(pwm_a_f6,			3),
	GROUP(pwm_b_f,			3),
	GROUP(pwm_c_f8,			3),
	GROUP(clk25,			3),
	GROUP(i2c_slave_sck_f,		3),
	GROUP(i2c_slave_sda_f,		3),

	/*bank F func4 */
	GROUP(cec_a,			4),
	GROUP(i2c3_sck_f,		4),
	GROUP(i2c3_sda_f,		4),
	GROUP(pmw_a_hiz_f6,		4),
	GROUP(pwm_b_hiz,		4),
	GROUP(pwm_c_hiz,		4),
	GROUP(i2c0_sck_f9,		4),
	GROUP(i2c0_sda_f10,		4),

	/*bank F func5 */
	GROUP(cec_b,			5),
	GROUP(clk12_24,			5),

	/*bank F func7 */
	GROUP(gen_clk_f10,		7),

	/*bank A func1 */
	GROUP(mclk_0,			1),
	GROUP(tdm_b_sclk,		1),
	GROUP(tdm_b_fs,			1),
	GROUP(tdm_b_करोut0,		1),
	GROUP(tdm_b_करोut1,		1),
	GROUP(tdm_b_करोut2,		1),
	GROUP(tdm_b_करोut3,		1),
	GROUP(tdm_b_करोut4,		1),
	GROUP(tdm_b_करोut5,		1),
	GROUP(remote_input_a,		1),

	/*bank A func2 */
	GROUP(pwm_e_a,			2),
	GROUP(tdm_b_slv_sclk,		2),
	GROUP(tdm_b_slv_fs,		2),
	GROUP(tdm_b_din0,		2),
	GROUP(tdm_b_din1,		2),
	GROUP(tdm_b_din2,		2),
	GROUP(i2c1_sda_a,		2),
	GROUP(i2c1_sck_a,		2),

	/*bank A func3 */
	GROUP(i2c2_sck_a4,		3),
	GROUP(i2c2_sda_a5,		3),
	GROUP(pdm_din2_a,		3),
	GROUP(pdm_din1_a,		3),
	GROUP(pdm_din0_a,		3),
	GROUP(pdm_dclk,			3),
	GROUP(pwm_c_a,			3),
	GROUP(pwm_b_a,			3),

	/*bank A func4 */
	GROUP(pwm_a_a,			4),
	GROUP(spi_a_mosi_a,		4),
	GROUP(spi_a_miso_a,		4),
	GROUP(spi_a_ss0_a,		4),
	GROUP(spi_a_sclk_a,		4),
	GROUP(i2c_slave_sck_a,		4),
	GROUP(i2c_slave_sda_a,		4),

	/*bank A func5 */
	GROUP(mclk_vad,			5),
	GROUP(tdm_vad_sclk_a1,		5),
	GROUP(tdm_vad_fs_a2,		5),
	GROUP(tdm_vad_sclk_a5,		5),
	GROUP(tdm_vad_fs_a6,		5),
	GROUP(i2c2_sck_a8,		5),
	GROUP(i2c2_sda_a9,		5),

	/*bank A func6 */
	GROUP(tst_out0,			6),
	GROUP(tst_out1,			6),
	GROUP(tst_out2,			6),
	GROUP(tst_out3,			6),
	GROUP(tst_out4,			6),
	GROUP(tst_out5,			6),
	GROUP(tst_out6,			6),
	GROUP(tst_out7,			6),
	GROUP(tst_out8,			6),
	GROUP(tst_out9,			6),
	GROUP(tst_out10,		6),
	GROUP(tst_out11,		6),

	/*bank A func7 */
	GROUP(mute_key,			7),
	GROUP(mute_en,			7),
	GROUP(gen_clk_a,		7),
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_periphs_groups[] = अणु
	"GPIOP_0", "GPIOP_1", "GPIOP_2", "GPIOP_3", "GPIOP_4",
	"GPIOP_5", "GPIOP_6", "GPIOP_7", "GPIOP_8", "GPIOP_9",
	"GPIOP_10", "GPIOP_11", "GPIOP_12",

	"GPIOB_0", "GPIOB_1", "GPIOB_2", "GPIOB_3", "GPIOB_4",
	"GPIOB_5", "GPIOB_6",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13", "GPIOX_14",
	"GPIOX_15", "GPIOX_16",

	"GPIOF_0", "GPIOF_1", "GPIOF_2", "GPIOF_3", "GPIOF_4",
	"GPIOF_5", "GPIOF_6", "GPIOF_7", "GPIOF_8", "GPIOF_9",
	"GPIOF_10", "GPIOF_11", "GPIOF_12",

	"GPIOA_0", "GPIOA_1", "GPIOA_2", "GPIOA_3", "GPIOA_4",
	"GPIOA_5", "GPIOA_6", "GPIOA_7", "GPIOA_8", "GPIOA_9",
	"GPIOA_10", "GPIOA_11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर psram_groups[] = अणु
	"psram_clkn", "psram_clkp", "psram_ce_n", "psram_rst_n", "psram_adq0",
	"psram_adq1", "psram_adq2", "psram_adq3", "psram_adq4", "psram_adq5",
	"psram_adq6", "psram_adq7", "psram_dqs_dm",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_a_groups[] = अणु
	"pwm_a_x6", "pwm_a_x7", "pwm_a_f10", "pwm_a_f6", "pwm_a_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_b_groups[] = अणु
	"pwm_b_x", "pwm_b_f", "pwm_b_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_c_groups[] = अणु
	"pwm_c_x", "pwm_c_f3", "pwm_c_f8", "pwm_c_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_d_groups[] = अणु
	"pwm_d_x15", "pwm_d_x13", "pwm_d_x10", "pwm_d_f",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_e_groups[] = अणु
	"pwm_e_p", "pwm_e_x16", "pwm_e_x14", "pwm_e_x2", "pwm_e_f",
	"pwm_e_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_f_groups[] = अणु
	"pwm_f_b", "pwm_f_x", "pwm_f_f4", "pwm_f_f12",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_a_hiz_groups[] = अणु
	"pwm_a_hiz_f8", "pwm_a_hiz_f10", "pwm_a_hiz_f6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_b_hiz_groups[] = अणु
	"pwm_b_hiz",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_c_hiz_groups[] = अणु
	"pwm_c_hiz",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spअगर_groups[] = अणु
	"spif_mo", "spif_mi", "spif_wp_n", "spif_hold_n", "spif_clk",
	"spif_cs",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdcard_groups[] = अणु
	"sdcard_d0_b", "sdcard_d1_b", "sdcard_d2_b", "sdcard_d3_b",
	"sdcard_clk_b", "sdcard_cmd_b",

	"sdcard_d0_x", "sdcard_d1_x", "sdcard_d2_x", "sdcard_d3_x",
	"sdcard_clk_x", "sdcard_cmd_x",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tdm_a_groups[] = अणु
	"tdm_a_din0", "tdm_a_din1",  "tdm_a_fs", "tdm_a_sclk",
	"tdm_a_slv_fs", "tdm_a_slv_sclk", "tdm_a_dout0", "tdm_a_dout1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_a_groups[] = अणु
	"uart_a_tx", "uart_a_rx", "uart_a_cts", "uart_a_rts",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_b_groups[] = अणु
	"uart_b_tx_x", "uart_b_rx_x", "uart_b_tx_f", "uart_b_rx_f",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_c_groups[] = अणु
	"uart_c_tx_x0", "uart_c_rx_x1", "uart_c_cts", "uart_c_rts",
	"uart_c_tx_x15", "uart_c_rx_x16",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c0_groups[] = अणु
	"i2c0_sck_f11", "i2c0_sda_f12", "i2c0_sck_f9", "i2c0_sda_f10",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c1_groups[] = अणु
	"i2c1_sda_x", "i2c1_sck_x", "i2c1_sda_a", "i2c1_sck_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c2_groups[] = अणु
	"i2c2_sck_x0", "i2c2_sda_x1", "i2c2_sck_x15", "i2c2_sda_x16",
	"i2c2_sck_a4", "i2c2_sda_a5", "i2c2_sck_a8", "i2c2_sda_a9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c3_groups[] = अणु
	"i2c3_sck_x", "i2c3_sda_x", "i2c3_sck_f", "i2c3_sda_f",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_a_groups[] = अणु
	"spi_a_mosi_x2", "spi_a_ss0_x3", "spi_a_sclk_x4", "spi_a_miso_x5",
	"spi_a_mosi_x7", "spi_a_miso_x8", "spi_a_ss0_x9", "spi_a_sclk_x10",

	"spi_a_mosi_a", "spi_a_miso_a", "spi_a_ss0_a", "spi_a_sclk_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pdm_groups[] = अणु
	"pdm_din0_x", "pdm_din1_x", "pdm_din2_x", "pdm_dclk_x", "pdm_din2_a",
	"pdm_din1_a", "pdm_din0_a", "pdm_dclk",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gen_clk_groups[] = अणु
	"gen_clk_x", "gen_clk_f8", "gen_clk_f10", "gen_clk_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर remote_input_groups[] = अणु
	"remote_input_f",
	"remote_input_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर jtag_a_groups[] = अणु
	"jtag_a_clk", "jtag_a_tms", "jtag_a_tdi", "jtag_a_tdo",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk_32k_in_groups[] = अणु
	"clk_32k_in",
पूर्ण;

अटल स्थिर अक्षर * स्थिर remote_out_groups[] = अणु
	"remote_out",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगर_in_groups[] = अणु
	"spdif_in_f6", "spdif_in_f7",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sw_groups[] = अणु
	"swclk", "swdio",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk25_groups[] = अणु
	"clk_25",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cec_a_groups[] = अणु
	"cec_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cec_b_groups[] = अणु
	"cec_b",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clk12_24_groups[] = अणु
	"clk12_24",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mclk_0_groups[] = अणु
	"mclk_0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tdm_b_groups[] = अणु
	"tdm_b_din0", "tdm_b_din1", "tdm_b_din2",
	"tdm_b_sclk", "tdm_b_fs", "tdm_b_dout0", "tdm_b_dout1",
	"tdm_b_dout2", "tdm_b_dout3", "tdm_b_dout4", "tdm_b_dout5",
	"tdm_b_slv_sclk", "tdm_b_slv_fs",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mclk_vad_groups[] = अणु
	"mclk_vad",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tdm_vad_groups[] = अणु
	"tdm_vad_sclk_a1", "tdm_vad_fs_a2", "tdm_vad_sclk_a5", "tdm_vad_fs_a6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tst_out_groups[] = अणु
	"tst_out0", "tst_out1", "tst_out2", "tst_out3",
	"tst_out4", "tst_out5", "tst_out6", "tst_out7",
	"tst_out8", "tst_out9", "tst_out10", "tst_out11",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mute_groups[] = अणु
	"mute_key", "mute_en",
पूर्ण;

अटल काष्ठा meson_pmx_func meson_a1_periphs_functions[] = अणु
	FUNCTION(gpio_periphs),
	FUNCTION(psram),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_e),
	FUNCTION(pwm_f),
	FUNCTION(pwm_a_hiz),
	FUNCTION(pwm_b_hiz),
	FUNCTION(pwm_c_hiz),
	FUNCTION(spअगर),
	FUNCTION(sdcard),
	FUNCTION(tdm_a),
	FUNCTION(uart_a),
	FUNCTION(uart_b),
	FUNCTION(uart_c),
	FUNCTION(i2c0),
	FUNCTION(i2c1),
	FUNCTION(i2c2),
	FUNCTION(i2c3),
	FUNCTION(spi_a),
	FUNCTION(pdm),
	FUNCTION(gen_clk),
	FUNCTION(remote_input),
	FUNCTION(jtag_a),
	FUNCTION(clk_32k_in),
	FUNCTION(remote_out),
	FUNCTION(spdअगर_in),
	FUNCTION(sw),
	FUNCTION(clk25),
	FUNCTION(cec_a),
	FUNCTION(cec_b),
	FUNCTION(clk12_24),
	FUNCTION(mclk_0),
	FUNCTION(tdm_b),
	FUNCTION(mclk_vad),
	FUNCTION(tdm_vad),
	FUNCTION(tst_out),
	FUNCTION(mute),
पूर्ण;

अटल काष्ठा meson_bank meson_a1_periphs_banks[] = अणु
	/* name  first  last  irq  pullen  pull  dir  out  in  ds*/
	BANK_DS("P",  GPIOP_0,  GPIOP_12,  0,  12, 0x3,  0,  0x4,  0,
		0x2,  0,  0x1,  0,  0x0,  0,  0x5,  0),
	BANK_DS("B",  GPIOB_0,    GPIOB_6,   13,  19,  0x13,  0,  0x14,  0,
		0x12,  0,  0x11,  0,  0x10,  0,  0x15,  0),
	BANK_DS("X",  GPIOX_0,    GPIOX_16,  20,  36,  0x23,  0,  0x24,  0,
		0x22,  0,  0x21,  0,  0x20,  0,  0x25,  0),
	BANK_DS("F",  GPIOF_0,    GPIOF_12,  37,  49,  0x33,  0,  0x34,  0,
		0x32,  0,  0x31,  0,  0x30,  0,  0x35,  0),
	BANK_DS("A",  GPIOA_0,    GPIOA_11,  50,  61,  0x43,  0,  0x44,  0,
		0x42,  0,  0x41,  0,  0x40,  0,  0x45,  0),
पूर्ण;

अटल काष्ठा meson_pmx_bank meson_a1_periphs_pmx_banks[] = अणु
	/*  name	 first	    lask    reg	offset  */
	BANK_PMX("P",    GPIOP_0, GPIOP_12, 0x0, 0),
	BANK_PMX("B",    GPIOB_0, GPIOB_6,  0x2, 0),
	BANK_PMX("X",    GPIOX_0, GPIOX_16, 0x3, 0),
	BANK_PMX("F",    GPIOF_0, GPIOF_12, 0x6, 0),
	BANK_PMX("A",    GPIOA_0, GPIOA_11, 0x8, 0),
पूर्ण;

अटल काष्ठा meson_axg_pmx_data meson_a1_periphs_pmx_banks_data = अणु
	.pmx_banks	= meson_a1_periphs_pmx_banks,
	.num_pmx_banks	= ARRAY_SIZE(meson_a1_periphs_pmx_banks),
पूर्ण;

अटल काष्ठा meson_pinctrl_data meson_a1_periphs_pinctrl_data = अणु
	.name		= "periphs-banks",
	.pins		= meson_a1_periphs_pins,
	.groups		= meson_a1_periphs_groups,
	.funcs		= meson_a1_periphs_functions,
	.banks		= meson_a1_periphs_banks,
	.num_pins	= ARRAY_SIZE(meson_a1_periphs_pins),
	.num_groups	= ARRAY_SIZE(meson_a1_periphs_groups),
	.num_funcs	= ARRAY_SIZE(meson_a1_periphs_functions),
	.num_banks	= ARRAY_SIZE(meson_a1_periphs_banks),
	.pmx_ops	= &meson_axg_pmx_ops,
	.pmx_data	= &meson_a1_periphs_pmx_banks_data,
	.parse_dt	= &meson_a1_parse_dt_extra,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_a1_pinctrl_dt_match[] = अणु
	अणु
		.compatible = "amlogic,meson-a1-periphs-pinctrl",
		.data = &meson_a1_periphs_pinctrl_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_a1_pinctrl_dt_match);

अटल काष्ठा platक्रमm_driver meson_a1_pinctrl_driver = अणु
	.probe  = meson_pinctrl_probe,
	.driver = अणु
		.name	= "meson-a1-pinctrl",
		.of_match_table = meson_a1_pinctrl_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_a1_pinctrl_driver);
MODULE_LICENSE("Dual BSD/GPL");
