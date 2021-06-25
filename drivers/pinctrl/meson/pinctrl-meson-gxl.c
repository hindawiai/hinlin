<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pin controller and GPIO driver क्रम Amlogic Meson GXL.
 *
 * Copyright (C) 2016 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 */

#समावेश <dt-bindings/gpio/meson-gxl-gpपन.स>
#समावेश "pinctrl-meson.h"
#समावेश "pinctrl-meson8-pmx.h"

अटल स्थिर काष्ठा pinctrl_pin_desc meson_gxl_periphs_pins[] = अणु
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
	MESON_PIN(GPIOZ_15),

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

	MESON_PIN(CARD_0),
	MESON_PIN(CARD_1),
	MESON_PIN(CARD_2),
	MESON_PIN(CARD_3),
	MESON_PIN(CARD_4),
	MESON_PIN(CARD_5),
	MESON_PIN(CARD_6),

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

	MESON_PIN(GPIOCLK_0),
	MESON_PIN(GPIOCLK_1),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक emmc_nand_d07_pins[] = अणु
	BOOT_0, BOOT_1, BOOT_2, BOOT_3, BOOT_4, BOOT_5, BOOT_6, BOOT_7,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक emmc_clk_pins[]	= अणु BOOT_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक emmc_cmd_pins[]	= अणु BOOT_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक emmc_ds_pins[]	= अणु BOOT_15 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nor_d_pins[]		= अणु BOOT_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_q_pins[]		= अणु BOOT_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_c_pins[]		= अणु BOOT_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nor_cs_pins[]		= अणु BOOT_15 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक spi_mosi_pins[]	= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_miso_pins[]	= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_ss0_pins[]	= अणु GPIOX_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spi_sclk_pins[]	= अणु GPIOX_11 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sdcard_d0_pins[]	= अणु CARD_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d1_pins[]	= अणु CARD_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d2_pins[]	= अणु CARD_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_d3_pins[]	= अणु CARD_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_cmd_pins[]	= अणु CARD_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdcard_clk_pins[]	= अणु CARD_2 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sdio_d0_pins[]	= अणु GPIOX_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_d1_pins[]	= अणु GPIOX_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_d2_pins[]	= अणु GPIOX_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_d3_pins[]	= अणु GPIOX_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_clk_pins[]	= अणु GPIOX_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_cmd_pins[]	= अणु GPIOX_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sdio_irq_pins[]	= अणु GPIOX_7 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक nand_ce0_pins[]	= अणु BOOT_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_ce1_pins[]	= अणु BOOT_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_rb0_pins[]	= अणु BOOT_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_ale_pins[]	= अणु BOOT_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_cle_pins[]	= अणु BOOT_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_wen_clk_pins[]	= अणु BOOT_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_ren_wr_pins[]	= अणु BOOT_14 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक nand_dqs_pins[]	= अणु BOOT_15 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_a_pins[]	= अणु GPIOX_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_a_pins[]	= अणु GPIOX_13 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_a_pins[]	= अणु GPIOX_14 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_a_pins[]	= अणु GPIOX_15 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_b_pins[]	= अणु GPIODV_24 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_b_pins[]	= अणु GPIODV_25 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_b_pins[]	= अणु GPIODV_26 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_b_pins[]	= अणु GPIODV_27 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_c_pins[]	= अणु GPIOX_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_c_pins[]	= अणु GPIOX_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_c_pins[]	= अणु GPIOX_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_c_pins[]	= अणु GPIOX_11 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sck_a_pins[]	= अणु GPIODV_25 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sda_a_pins[]	= अणु GPIODV_24 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sck_b_pins[]	= अणु GPIODV_27 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sda_b_pins[]	= अणु GPIODV_26 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sck_c_pins[]	= अणु GPIODV_29 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sda_c_pins[]	= अणु GPIODV_28 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sck_c_dv19_pins[] = अणु GPIODV_19 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sda_c_dv18_pins[] = अणु GPIODV_18 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक eth_mdio_pins[]	= अणु GPIOZ_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_mdc_pins[]	= अणु GPIOZ_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_clk_rx_clk_pins[] = अणु GPIOZ_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rx_dv_pins[]	= अणु GPIOZ_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd0_pins[]	= अणु GPIOZ_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd1_pins[]	= अणु GPIOZ_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd2_pins[]	= अणु GPIOZ_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rxd3_pins[]	= अणु GPIOZ_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_rgmii_tx_clk_pins[] = अणु GPIOZ_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_tx_en_pins[]	= अणु GPIOZ_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_txd0_pins[]	= अणु GPIOZ_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_txd1_pins[]	= अणु GPIOZ_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_txd2_pins[]	= अणु GPIOZ_12 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_txd3_pins[]	= अणु GPIOZ_13 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_a_pins[]		= अणु GPIOX_6 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_b_pins[]		= अणु GPIODV_29 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_c_pins[]		= अणु GPIOZ_15 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_d_pins[]		= अणु GPIODV_28 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_e_pins[]		= अणु GPIOX_16 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_f_clk_pins[]	= अणु GPIOCLK_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_f_x_pins[]	= अणु GPIOX_7 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hdmi_hpd_pins[]	= अणु GPIOH_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hdmi_sda_pins[]	= अणु GPIOH_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hdmi_scl_pins[]	= अणु GPIOH_2 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2s_am_clk_pins[]	= अणु GPIOH_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ao_clk_pins[] = अणु GPIOH_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_lr_clk_pins[] = अणु GPIOH_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch01_pins[]	= अणु GPIOH_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch23_z_pins[] = अणु GPIOZ_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch45_z_pins[] = अणु GPIOZ_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch67_z_pins[] = अणु GPIOZ_7 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक spdअगर_out_h_pins[]	= अणु GPIOH_4 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक eth_link_led_pins[]	= अणु GPIOZ_14 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक eth_act_led_pins[]	= अणु GPIOZ_15 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tsin_a_d0_pins[]	= अणु GPIODV_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_a_clk_pins[]	= अणु GPIODV_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_a_sop_pins[]	= अणु GPIODV_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_a_d_valid_pins[] = अणु GPIODV_10 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_a_fail_pins[]	= अणु GPIODV_11 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_a_dp_pins[] = अणु
	GPIODV_1, GPIODV_2, GPIODV_3, GPIODV_4, GPIODV_5, GPIODV_6, GPIODV_7,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tsin_b_clk_pins[]	= अणु GPIOH_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_b_d0_pins[]	= अणु GPIOH_7 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_b_sop_pins[]	= अणु GPIOH_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_b_d_valid_pins[] = अणु GPIOH_9 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tsin_b_fail_z4_pins[] = अणु GPIOZ_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_b_clk_z3_pins[]	= अणु GPIOZ_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_b_d0_z2_pins[]	= अणु GPIOZ_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_b_sop_z1_pins[]	= अणु GPIOZ_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tsin_b_d_valid_z0_pins[] = अणु GPIOZ_0 पूर्ण;

अटल स्थिर काष्ठा pinctrl_pin_desc meson_gxl_aobus_pins[] = अणु
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

	MESON_PIN(GPIO_TEST_N),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक uart_tx_ao_a_pins[]	= अणु GPIOAO_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_ao_a_pins[]	= अणु GPIOAO_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_tx_ao_b_0_pins[] = अणु GPIOAO_0 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_ao_b_1_pins[] = अणु GPIOAO_1 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_ao_a_pins[]	= अणु GPIOAO_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_ao_a_pins[]	= अणु GPIOAO_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_tx_ao_b_pins[]	= अणु GPIOAO_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rx_ao_b_pins[]	= अणु GPIOAO_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_cts_ao_b_pins[]	= अणु GPIOAO_2 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक uart_rts_ao_b_pins[]	= अणु GPIOAO_3 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2c_sck_ao_pins[]	= अणुGPIOAO_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_sda_ao_pins[]	= अणुGPIOAO_5 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sck_ao_pins[] = अणुGPIOAO_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c_slave_sda_ao_pins[] = अणुGPIOAO_5 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक remote_input_ao_pins[] = अणुGPIOAO_7 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_ao_a_3_pins[]	= अणु GPIOAO_3 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_ao_a_8_pins[]	= अणु GPIOAO_8 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pwm_ao_b_pins[]	= अणु GPIOAO_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm_ao_b_6_pins[]	= अणु GPIOAO_6 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch23_ao_pins[] = अणु GPIOAO_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch45_ao_pins[] = अणु GPIOAO_9 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2s_out_ch67_ao_pins[] = अणु GPIO_TEST_N पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक spdअगर_out_ao_6_pins[] = अणु GPIOAO_6 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक spdअगर_out_ao_9_pins[] = अणु GPIOAO_9 पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ao_cec_pins[]		= अणु GPIOAO_8 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ee_cec_pins[]		= अणु GPIOAO_8 पूर्ण;

अटल काष्ठा meson_pmx_group meson_gxl_periphs_groups[] = अणु
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
	GPIO_GROUP(GPIOZ_15),

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

	GPIO_GROUP(CARD_0),
	GPIO_GROUP(CARD_1),
	GPIO_GROUP(CARD_2),
	GPIO_GROUP(CARD_3),
	GPIO_GROUP(CARD_4),
	GPIO_GROUP(CARD_5),
	GPIO_GROUP(CARD_6),

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

	GPIO_GROUP(GPIOCLK_0),
	GPIO_GROUP(GPIOCLK_1),

	GPIO_GROUP(GPIO_TEST_N),

	/* Bank X */
	GROUP(sdio_d0,		5,	31),
	GROUP(sdio_d1,		5,	30),
	GROUP(sdio_d2,		5,	29),
	GROUP(sdio_d3,		5,	28),
	GROUP(sdio_clk,		5,	27),
	GROUP(sdio_cmd,		5,	26),
	GROUP(sdio_irq,		5,	24),
	GROUP(uart_tx_a,	5,	19),
	GROUP(uart_rx_a,	5,	18),
	GROUP(uart_cts_a,	5,	17),
	GROUP(uart_rts_a,	5,	16),
	GROUP(uart_tx_c,	5,	13),
	GROUP(uart_rx_c,	5,	12),
	GROUP(uart_cts_c,	5,	11),
	GROUP(uart_rts_c,	5,	10),
	GROUP(pwm_a,		5,	25),
	GROUP(pwm_e,		5,	15),
	GROUP(pwm_f_x,		5,	14),
	GROUP(spi_mosi,		5,	3),
	GROUP(spi_miso,		5,	2),
	GROUP(spi_ss0,		5,	1),
	GROUP(spi_sclk,		5,	0),

	/* Bank Z */
	GROUP(eth_mdio,		4,	23),
	GROUP(eth_mdc,		4,	22),
	GROUP(eth_clk_rx_clk,	4,	21),
	GROUP(eth_rx_dv,	4,	20),
	GROUP(eth_rxd0,		4,	19),
	GROUP(eth_rxd1,		4,	18),
	GROUP(eth_rxd2,		4,	17),
	GROUP(eth_rxd3,		4,	16),
	GROUP(eth_rgmii_tx_clk,	4,	15),
	GROUP(eth_tx_en,	4,	14),
	GROUP(eth_txd0,		4,	13),
	GROUP(eth_txd1,		4,	12),
	GROUP(eth_txd2,		4,	11),
	GROUP(eth_txd3,		4,	10),
	GROUP(tsin_b_fail_z4,	3,	15),
	GROUP(tsin_b_clk_z3,	3,	16),
	GROUP(tsin_b_d0_z2,	3,	17),
	GROUP(tsin_b_sop_z1,	3,	18),
	GROUP(tsin_b_d_valid_z0, 3,	19),
	GROUP(pwm_c,		3,	20),
	GROUP(i2s_out_ch23_z,	3,	26),
	GROUP(i2s_out_ch45_z,	3,	25),
	GROUP(i2s_out_ch67_z,	3,	24),
	GROUP(eth_link_led,	4,	25),
	GROUP(eth_act_led,	4,	24),

	/* Bank H */
	GROUP(hdmi_hpd,		6,	31),
	GROUP(hdmi_sda,		6,	30),
	GROUP(hdmi_scl,		6,	29),
	GROUP(i2s_am_clk,	6,	26),
	GROUP(i2s_out_ao_clk,	6,	25),
	GROUP(i2s_out_lr_clk,	6,	24),
	GROUP(i2s_out_ch01,	6,	23),
	GROUP(spdअगर_out_h,	6,	28),
	GROUP(tsin_b_d0,	6,	17),
	GROUP(tsin_b_sop,	6,	18),
	GROUP(tsin_b_d_valid,	6,	19),
	GROUP(tsin_b_clk,	6,	20),

	/* Bank DV */
	GROUP(uart_tx_b,	2,	16),
	GROUP(uart_rx_b,	2,	15),
	GROUP(uart_cts_b,	2,	14),
	GROUP(uart_rts_b,	2,	13),
	GROUP(i2c_sda_c_dv18,	1,	17),
	GROUP(i2c_sck_c_dv19,	1,	16),
	GROUP(i2c_sda_a,	1,	15),
	GROUP(i2c_sck_a,	1,	14),
	GROUP(i2c_sda_b,	1,	13),
	GROUP(i2c_sck_b,	1,	12),
	GROUP(i2c_sda_c,	1,	11),
	GROUP(i2c_sck_c,	1,	10),
	GROUP(pwm_b,		2,	11),
	GROUP(pwm_d,		2,	12),
	GROUP(tsin_a_d0,	2,	4),
	GROUP(tsin_a_dp,	2,	3),
	GROUP(tsin_a_clk,	2,	2),
	GROUP(tsin_a_sop,	2,	1),
	GROUP(tsin_a_d_valid,	2,	0),
	GROUP(tsin_a_fail,	1,	31),

	/* Bank BOOT */
	GROUP(emmc_nand_d07,	7,	31),
	GROUP(emmc_clk,		7,	30),
	GROUP(emmc_cmd,		7,	29),
	GROUP(emmc_ds,		7,	28),
	GROUP(nor_d,		7,	13),
	GROUP(nor_q,		7,	12),
	GROUP(nor_c,		7,	11),
	GROUP(nor_cs,		7,	10),
	GROUP(nand_ce0,		7,	7),
	GROUP(nand_ce1,		7,	6),
	GROUP(nand_rb0,		7,	5),
	GROUP(nand_ale,		7,	4),
	GROUP(nand_cle,		7,	3),
	GROUP(nand_wen_clk,	7,	2),
	GROUP(nand_ren_wr,	7,	1),
	GROUP(nand_dqs,		7,	0),

	/* Bank CARD */
	GROUP(sdcard_d1,	6,	5),
	GROUP(sdcard_d0,	6,	4),
	GROUP(sdcard_d3,	6,	1),
	GROUP(sdcard_d2,	6,	0),
	GROUP(sdcard_cmd,	6,	2),
	GROUP(sdcard_clk,	6,	3),

	/* Bank CLK */
	GROUP(pwm_f_clk,	8,	30),
पूर्ण;

अटल काष्ठा meson_pmx_group meson_gxl_aobus_groups[] = अणु
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

	/* bank AO */
	GROUP(uart_tx_ao_b_0,	0,	26),
	GROUP(uart_rx_ao_b_1,	0,	25),
	GROUP(uart_tx_ao_b,	0,	24),
	GROUP(uart_rx_ao_b,	0,	23),
	GROUP(uart_tx_ao_a,	0,	12),
	GROUP(uart_rx_ao_a,	0,	11),
	GROUP(uart_cts_ao_a,	0,	10),
	GROUP(uart_rts_ao_a,	0,	9),
	GROUP(uart_cts_ao_b,	0,	8),
	GROUP(uart_rts_ao_b,	0,	7),
	GROUP(i2c_sck_ao,	0,	6),
	GROUP(i2c_sda_ao,	0,	5),
	GROUP(i2c_slave_sck_ao, 0,	2),
	GROUP(i2c_slave_sda_ao, 0,	1),
	GROUP(remote_input_ao,	0,	0),
	GROUP(pwm_ao_a_3,	0,	22),
	GROUP(pwm_ao_b_6,	0,	18),
	GROUP(pwm_ao_a_8,	0,	17),
	GROUP(pwm_ao_b,		0,	3),
	GROUP(i2s_out_ch23_ao,	1,	0),
	GROUP(i2s_out_ch45_ao,	1,	1),
	GROUP(spdअगर_out_ao_6,	0,	16),
	GROUP(spdअगर_out_ao_9,	0,	4),
	GROUP(ao_cec,		0,	15),
	GROUP(ee_cec,		0,	14),

	/* test n pin */
	GROUP(i2s_out_ch67_ao,	1,	2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_periphs_groups[] = अणु
	"GPIOZ_0", "GPIOZ_1", "GPIOZ_2", "GPIOZ_3", "GPIOZ_4",
	"GPIOZ_5", "GPIOZ_6", "GPIOZ_7", "GPIOZ_8", "GPIOZ_9",
	"GPIOZ_10", "GPIOZ_11", "GPIOZ_12", "GPIOZ_13", "GPIOZ_14",
	"GPIOZ_15",

	"GPIOH_0", "GPIOH_1", "GPIOH_2", "GPIOH_3", "GPIOH_4",
	"GPIOH_5", "GPIOH_6", "GPIOH_7", "GPIOH_8", "GPIOH_9",

	"BOOT_0", "BOOT_1", "BOOT_2", "BOOT_3", "BOOT_4",
	"BOOT_5", "BOOT_6", "BOOT_7", "BOOT_8", "BOOT_9",
	"BOOT_10", "BOOT_11", "BOOT_12", "BOOT_13", "BOOT_14",
	"BOOT_15",

	"CARD_0", "CARD_1", "CARD_2", "CARD_3", "CARD_4",
	"CARD_5", "CARD_6",

	"GPIODV_0", "GPIODV_1", "GPIODV_2", "GPIODV_3", "GPIODV_4",
	"GPIODV_5", "GPIODV_6", "GPIODV_7", "GPIODV_8", "GPIODV_9",
	"GPIODV_10", "GPIODV_11", "GPIODV_12", "GPIODV_13", "GPIODV_14",
	"GPIODV_15", "GPIODV_16", "GPIODV_17", "GPIODV_18", "GPIODV_19",
	"GPIODV_20", "GPIODV_21", "GPIODV_22", "GPIODV_23", "GPIODV_24",
	"GPIODV_25", "GPIODV_26", "GPIODV_27", "GPIODV_28", "GPIODV_29",

	"GPIOX_0", "GPIOX_1", "GPIOX_2", "GPIOX_3", "GPIOX_4",
	"GPIOX_5", "GPIOX_6", "GPIOX_7", "GPIOX_8", "GPIOX_9",
	"GPIOX_10", "GPIOX_11", "GPIOX_12", "GPIOX_13", "GPIOX_14",
	"GPIOX_15", "GPIOX_16", "GPIOX_17", "GPIOX_18",
पूर्ण;

अटल स्थिर अक्षर * स्थिर emmc_groups[] = अणु
	"emmc_nand_d07", "emmc_clk", "emmc_cmd", "emmc_ds",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nor_groups[] = अणु
	"nor_d", "nor_q", "nor_c", "nor_cs",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi_groups[] = अणु
	"spi_mosi", "spi_miso", "spi_ss0", "spi_sclk",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdcard_groups[] = अणु
	"sdcard_d0", "sdcard_d1", "sdcard_d2", "sdcard_d3",
	"sdcard_cmd", "sdcard_clk",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sdio_groups[] = अणु
	"sdio_d0", "sdio_d1", "sdio_d2", "sdio_d3",
	"sdio_cmd", "sdio_clk", "sdio_irq",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand_groups[] = अणु
	"emmc_nand_d07", "nand_ce0", "nand_ce1", "nand_rb0", "nand_ale",
	"nand_cle", "nand_wen_clk", "nand_ren_wr", "nand_dqs",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_a_groups[] = अणु
	"uart_tx_a", "uart_rx_a", "uart_cts_a", "uart_rts_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_b_groups[] = अणु
	"uart_tx_b", "uart_rx_b", "uart_cts_b", "uart_rts_b",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_c_groups[] = अणु
	"uart_tx_c", "uart_rx_c", "uart_cts_c", "uart_rts_c",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_a_groups[] = अणु
	"i2c_sck_a", "i2c_sda_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_b_groups[] = अणु
	"i2c_sck_b", "i2c_sda_b",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_c_groups[] = अणु
	"i2c_sck_c", "i2c_sda_c", "i2c_sda_c_dv18", "i2c_sck_c_dv19",
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_groups[] = अणु
	"eth_mdio", "eth_mdc", "eth_clk_rx_clk", "eth_rx_dv",
	"eth_rxd0", "eth_rxd1", "eth_rxd2", "eth_rxd3",
	"eth_rgmii_tx_clk", "eth_tx_en",
	"eth_txd0", "eth_txd1", "eth_txd2", "eth_txd3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_a_groups[] = अणु
	"pwm_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_b_groups[] = अणु
	"pwm_b",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_c_groups[] = अणु
	"pwm_c",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_d_groups[] = अणु
	"pwm_d",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_e_groups[] = अणु
	"pwm_e",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_f_groups[] = अणु
	"pwm_f_clk", "pwm_f_x",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_hpd_groups[] = अणु
	"hdmi_hpd",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hdmi_i2c_groups[] = अणु
	"hdmi_sda", "hdmi_scl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s_out_groups[] = अणु
	"i2s_am_clk", "i2s_out_ao_clk", "i2s_out_lr_clk",
	"i2s_out_ch01", "i2s_out_ch23_z", "i2s_out_ch45_z", "i2s_out_ch67_z",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगर_out_groups[] = अणु
	"spdif_out_h",
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_led_groups[] = अणु
	"eth_link_led", "eth_act_led",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tsin_a_groups[] = अणु
	"tsin_a_clk", "tsin_a_sop",
	"tsin_a_d_valid", "tsin_a_d0",
	"tsin_a_dp", "tsin_a_fail",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tsin_b_groups[] = अणु
	"tsin_b_clk", "tsin_b_sop", "tsin_b_d_valid", "tsin_b_d0",
	"tsin_b_clk_z3", "tsin_b_sop_z1", "tsin_b_d_valid_z0", "tsin_b_d0_z2",
	"tsin_b_fail_z4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpio_aobus_groups[] = अणु
	"GPIOAO_0", "GPIOAO_1", "GPIOAO_2", "GPIOAO_3", "GPIOAO_4",
	"GPIOAO_5", "GPIOAO_6", "GPIOAO_7", "GPIOAO_8", "GPIOAO_9",

	"GPIO_TEST_N",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_ao_groups[] = अणु
	"uart_tx_ao_a", "uart_rx_ao_a", "uart_cts_ao_a", "uart_rts_ao_a",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart_ao_b_groups[] = अणु
	"uart_tx_ao_b", "uart_rx_ao_b", "uart_cts_ao_b", "uart_rts_ao_b",
	"uart_tx_ao_b_0", "uart_rx_ao_b_1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_ao_groups[] = अणु
	"i2c_sck_ao", "i2c_sda_ao",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c_slave_ao_groups[] = अणु
	"i2c_slave_sck_ao", "i2c_slave_sda_ao",
पूर्ण;

अटल स्थिर अक्षर * स्थिर remote_input_ao_groups[] = अणु
	"remote_input_ao",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_ao_a_groups[] = अणु
	"pwm_ao_a_3", "pwm_ao_a_8",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm_ao_b_groups[] = अणु
	"pwm_ao_b", "pwm_ao_b_6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s_out_ao_groups[] = अणु
	"i2s_out_ch23_ao", "i2s_out_ch45_ao", "i2s_out_ch67_ao",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगर_out_ao_groups[] = अणु
	"spdif_out_ao_6", "spdif_out_ao_9",
पूर्ण;

अटल स्थिर अक्षर * स्थिर cec_ao_groups[] = अणु
	"ao_cec", "ee_cec",
पूर्ण;

अटल काष्ठा meson_pmx_func meson_gxl_periphs_functions[] = अणु
	FUNCTION(gpio_periphs),
	FUNCTION(emmc),
	FUNCTION(nor),
	FUNCTION(spi),
	FUNCTION(sdcard),
	FUNCTION(sdio),
	FUNCTION(nand),
	FUNCTION(uart_a),
	FUNCTION(uart_b),
	FUNCTION(uart_c),
	FUNCTION(i2c_a),
	FUNCTION(i2c_b),
	FUNCTION(i2c_c),
	FUNCTION(eth),
	FUNCTION(pwm_a),
	FUNCTION(pwm_b),
	FUNCTION(pwm_c),
	FUNCTION(pwm_d),
	FUNCTION(pwm_e),
	FUNCTION(pwm_f),
	FUNCTION(hdmi_hpd),
	FUNCTION(hdmi_i2c),
	FUNCTION(i2s_out),
	FUNCTION(spdअगर_out),
	FUNCTION(eth_led),
	FUNCTION(tsin_a),
	FUNCTION(tsin_b),
पूर्ण;

अटल काष्ठा meson_pmx_func meson_gxl_aobus_functions[] = अणु
	FUNCTION(gpio_aobus),
	FUNCTION(uart_ao),
	FUNCTION(uart_ao_b),
	FUNCTION(i2c_ao),
	FUNCTION(i2c_slave_ao),
	FUNCTION(remote_input_ao),
	FUNCTION(pwm_ao_a),
	FUNCTION(pwm_ao_b),
	FUNCTION(i2s_out_ao),
	FUNCTION(spdअगर_out_ao),
	FUNCTION(cec_ao),
पूर्ण;

अटल काष्ठा meson_bank meson_gxl_periphs_banks[] = अणु
	/*   name    first      last       irq	     pullen  pull    dir     out     in  */
	BANK("X",    GPIOX_0,	GPIOX_18,   89, 107, 4,  0,  4,  0,  12, 0,  13, 0,  14, 0),
	BANK("DV",   GPIODV_0,	GPIODV_29,  83,  88, 0,  0,  0,  0,  0,  0,  1,  0,  2,  0),
	BANK("H",    GPIOH_0,	GPIOH_9,    26,  35, 1, 20,  1, 20,  3, 20,  4, 20,  5, 20),
	BANK("Z",    GPIOZ_0,	GPIOZ_15,   10,  25, 3,  0,  3,  0,  9,  0,  10, 0, 11,  0),
	BANK("CARD", CARD_0,	CARD_6,     52,  58, 2, 20,  2, 20,  6, 20,  7, 20,  8, 20),
	BANK("BOOT", BOOT_0,	BOOT_15,    36,  51, 2,  0,  2,  0,  6,  0,  7,  0,  8,  0),
	BANK("CLK",  GPIOCLK_0,	GPIOCLK_1, 108, 109, 3, 28,  3, 28,  9, 28, 10, 28, 11, 28),
पूर्ण;

अटल काष्ठा meson_bank meson_gxl_aobus_banks[] = अणु
	/*   name    first      last      irq	pullen  pull    dir     out     in  */
	BANK("AO",   GPIOAO_0,  GPIOAO_9, 0, 9, 0,  16, 0, 0,   0,  0,  0, 16,  1,  0),
पूर्ण;

अटल काष्ठा meson_pinctrl_data meson_gxl_periphs_pinctrl_data = अणु
	.name		= "periphs-banks",
	.pins		= meson_gxl_periphs_pins,
	.groups		= meson_gxl_periphs_groups,
	.funcs		= meson_gxl_periphs_functions,
	.banks		= meson_gxl_periphs_banks,
	.num_pins	= ARRAY_SIZE(meson_gxl_periphs_pins),
	.num_groups	= ARRAY_SIZE(meson_gxl_periphs_groups),
	.num_funcs	= ARRAY_SIZE(meson_gxl_periphs_functions),
	.num_banks	= ARRAY_SIZE(meson_gxl_periphs_banks),
	.pmx_ops	= &meson8_pmx_ops,
पूर्ण;

अटल काष्ठा meson_pinctrl_data meson_gxl_aobus_pinctrl_data = अणु
	.name		= "aobus-banks",
	.pins		= meson_gxl_aobus_pins,
	.groups		= meson_gxl_aobus_groups,
	.funcs		= meson_gxl_aobus_functions,
	.banks		= meson_gxl_aobus_banks,
	.num_pins	= ARRAY_SIZE(meson_gxl_aobus_pins),
	.num_groups	= ARRAY_SIZE(meson_gxl_aobus_groups),
	.num_funcs	= ARRAY_SIZE(meson_gxl_aobus_functions),
	.num_banks	= ARRAY_SIZE(meson_gxl_aobus_banks),
	.pmx_ops	= &meson8_pmx_ops,
	.parse_dt	= meson8_aobus_parse_dt_extra,
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_gxl_pinctrl_dt_match[] = अणु
	अणु
		.compatible = "amlogic,meson-gxl-periphs-pinctrl",
		.data = &meson_gxl_periphs_pinctrl_data,
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-gxl-aobus-pinctrl",
		.data = &meson_gxl_aobus_pinctrl_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_gxl_pinctrl_dt_match);

अटल काष्ठा platक्रमm_driver meson_gxl_pinctrl_driver = अणु
	.probe		= meson_pinctrl_probe,
	.driver = अणु
		.name	= "meson-gxl-pinctrl",
		.of_match_table = meson_gxl_pinctrl_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_gxl_pinctrl_driver);
MODULE_LICENSE("GPL v2");
