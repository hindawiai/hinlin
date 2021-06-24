<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ADF4350/ADF4351 SPI PLL driver
 *
 * Copyright 2012-2013 Analog Devices Inc.
 */

#अगर_अघोषित IIO_PLL_ADF4350_H_
#घोषणा IIO_PLL_ADF4350_H_

/* Registers */
#घोषणा ADF4350_REG0	0
#घोषणा ADF4350_REG1	1
#घोषणा ADF4350_REG2	2
#घोषणा ADF4350_REG3	3
#घोषणा ADF4350_REG4	4
#घोषणा ADF4350_REG5	5

/* REG0 Bit Definitions */
#घोषणा ADF4350_REG0_FRACT(x)			(((x) & 0xFFF) << 3)
#घोषणा ADF4350_REG0_INT(x)			(((x) & 0xFFFF) << 15)

/* REG1 Bit Definitions */
#घोषणा ADF4350_REG1_MOD(x)			(((x) & 0xFFF) << 3)
#घोषणा ADF4350_REG1_PHASE(x)			(((x) & 0xFFF) << 15)
#घोषणा ADF4350_REG1_PRESCALER			(1 << 27)

/* REG2 Bit Definitions */
#घोषणा ADF4350_REG2_COUNTER_RESET_EN		(1 << 3)
#घोषणा ADF4350_REG2_CP_THREESTATE_EN		(1 << 4)
#घोषणा ADF4350_REG2_POWER_DOWN_EN		(1 << 5)
#घोषणा ADF4350_REG2_PD_POLARITY_POS		(1 << 6)
#घोषणा ADF4350_REG2_LDP_6ns			(1 << 7)
#घोषणा ADF4350_REG2_LDP_10ns			(0 << 7)
#घोषणा ADF4350_REG2_LDF_FRACT_N		(0 << 8)
#घोषणा ADF4350_REG2_LDF_INT_N			(1 << 8)
#घोषणा ADF4350_REG2_CHARGE_PUMP_CURR_uA(x)	(((((x)-312) / 312) & 0xF) << 9)
#घोषणा ADF4350_REG2_DOUBLE_BUFF_EN		(1 << 13)
#घोषणा ADF4350_REG2_10BIT_R_CNT(x)		((x) << 14)
#घोषणा ADF4350_REG2_RDIV2_EN			(1 << 24)
#घोषणा ADF4350_REG2_RMULT2_EN			(1 << 25)
#घोषणा ADF4350_REG2_MUXOUT(x)			((x) << 26)
#घोषणा ADF4350_REG2_NOISE_MODE(x)		(((अचिन्हित)(x)) << 29)
#घोषणा ADF4350_MUXOUT_THREESTATE		0
#घोषणा ADF4350_MUXOUT_DVDD			1
#घोषणा ADF4350_MUXOUT_GND			2
#घोषणा ADF4350_MUXOUT_R_DIV_OUT		3
#घोषणा ADF4350_MUXOUT_N_DIV_OUT		4
#घोषणा ADF4350_MUXOUT_ANALOG_LOCK_DETECT	5
#घोषणा ADF4350_MUXOUT_DIGITAL_LOCK_DETECT	6

/* REG3 Bit Definitions */
#घोषणा ADF4350_REG3_12BIT_CLKDIV(x)		((x) << 3)
#घोषणा ADF4350_REG3_12BIT_CLKDIV_MODE(x)	((x) << 16)
#घोषणा ADF4350_REG3_12BIT_CSR_EN		(1 << 18)
#घोषणा ADF4351_REG3_CHARGE_CANCELLATION_EN	(1 << 21)
#घोषणा ADF4351_REG3_ANTI_BACKLASH_3ns_EN	(1 << 22)
#घोषणा ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH	(1 << 23)

/* REG4 Bit Definitions */
#घोषणा ADF4350_REG4_OUTPUT_PWR(x)		((x) << 3)
#घोषणा ADF4350_REG4_RF_OUT_EN			(1 << 5)
#घोषणा ADF4350_REG4_AUX_OUTPUT_PWR(x)		((x) << 6)
#घोषणा ADF4350_REG4_AUX_OUTPUT_EN		(1 << 8)
#घोषणा ADF4350_REG4_AUX_OUTPUT_FUND		(1 << 9)
#घोषणा ADF4350_REG4_AUX_OUTPUT_DIV		(0 << 9)
#घोषणा ADF4350_REG4_MUTE_TILL_LOCK_EN		(1 << 10)
#घोषणा ADF4350_REG4_VCO_PWRDOWN_EN		(1 << 11)
#घोषणा ADF4350_REG4_8BIT_BAND_SEL_CLKDIV(x)	((x) << 12)
#घोषणा ADF4350_REG4_RF_DIV_SEL(x)		((x) << 20)
#घोषणा ADF4350_REG4_FEEDBACK_DIVIDED		(0 << 23)
#घोषणा ADF4350_REG4_FEEDBACK_FUND		(1 << 23)

/* REG5 Bit Definitions */
#घोषणा ADF4350_REG5_LD_PIN_MODE_LOW		(0 << 22)
#घोषणा ADF4350_REG5_LD_PIN_MODE_DIGITAL	(1 << 22)
#घोषणा ADF4350_REG5_LD_PIN_MODE_HIGH		(3 << 22)

/* Specअगरications */
#घोषणा ADF4350_MAX_OUT_FREQ		4400000000ULL /* Hz */
#घोषणा ADF4350_MIN_OUT_FREQ		137500000 /* Hz */
#घोषणा ADF4351_MIN_OUT_FREQ		34375000 /* Hz */
#घोषणा ADF4350_MIN_VCO_FREQ		2200000000ULL /* Hz */
#घोषणा ADF4350_MAX_FREQ_45_PRESC	3000000000ULL /* Hz */
#घोषणा ADF4350_MAX_FREQ_PFD		32000000 /* Hz */
#घोषणा ADF4350_MAX_BANDSEL_CLK		125000 /* Hz */
#घोषणा ADF4350_MAX_FREQ_REFIN		250000000 /* Hz */
#घोषणा ADF4350_MAX_MODULUS		4095
#घोषणा ADF4350_MAX_R_CNT		1023


/**
 * काष्ठा adf4350_platक्रमm_data - platक्रमm specअगरic inक्रमmation
 * @name:		Optional device name.
 * @clkin:		REFin frequency in Hz.
 * @channel_spacing:	Channel spacing in Hz (influences MODULUS).
 * @घातer_up_frequency:	Optional, If set in Hz the PLL tunes to the desired
 *			frequency on probe.
 * @ref_भाग_factor:	Optional, अगर set the driver skips dynamic calculation
 *			and uses this शेष value instead.
 * @ref_द्विगुनr_en:	Enables reference द्विगुनr.
 * @ref_भाग2_en:	Enables reference भागider.
 * @r2_user_settings:	User defined settings क्रम ADF4350/1 REGISTER_2.
 * @r3_user_settings:	User defined settings क्रम ADF4350/1 REGISTER_3.
 * @r4_user_settings:	User defined settings क्रम ADF4350/1 REGISTER_4.
 */

काष्ठा adf4350_platक्रमm_data अणु
	अक्षर			name[32];
	अचिन्हित दीर्घ		clkin;
	अचिन्हित दीर्घ		channel_spacing;
	अचिन्हित दीर्घ दीर्घ	घातer_up_frequency;

	अचिन्हित लघु		ref_भाग_factor; /* 10-bit R counter */
	bool			ref_द्विगुनr_en;
	bool			ref_भाग2_en;

	अचिन्हित		r2_user_settings;
	अचिन्हित		r3_user_settings;
	अचिन्हित		r4_user_settings;
पूर्ण;

#पूर्ण_अगर /* IIO_PLL_ADF4350_H_ */
