<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Analog Devices Inc.
 */
#अगर_अघोषित __LINUX_PLATFORM_DATA_AD5755_H__
#घोषणा __LINUX_PLATFORM_DATA_AD5755_H__

क्रमागत ad5755_mode अणु
	AD5755_MODE_VOLTAGE_0V_5V		= 0,
	AD5755_MODE_VOLTAGE_0V_10V		= 1,
	AD5755_MODE_VOLTAGE_PLUSMINUS_5V	= 2,
	AD5755_MODE_VOLTAGE_PLUSMINUS_10V	= 3,
	AD5755_MODE_CURRENT_4mA_20mA		= 4,
	AD5755_MODE_CURRENT_0mA_20mA		= 5,
	AD5755_MODE_CURRENT_0mA_24mA		= 6,
पूर्ण;

क्रमागत ad5755_dc_dc_phase अणु
	AD5755_DC_DC_PHASE_ALL_SAME_EDGE		= 0,
	AD5755_DC_DC_PHASE_A_B_SAME_EDGE_C_D_OPP_EDGE	= 1,
	AD5755_DC_DC_PHASE_A_C_SAME_EDGE_B_D_OPP_EDGE	= 2,
	AD5755_DC_DC_PHASE_90_DEGREE			= 3,
पूर्ण;

क्रमागत ad5755_dc_dc_freq अणु
	AD5755_DC_DC_FREQ_250kHZ = 0,
	AD5755_DC_DC_FREQ_410kHZ = 1,
	AD5755_DC_DC_FREQ_650kHZ = 2,
पूर्ण;

क्रमागत ad5755_dc_dc_maxv अणु
	AD5755_DC_DC_MAXV_23V	= 0,
	AD5755_DC_DC_MAXV_24V5	= 1,
	AD5755_DC_DC_MAXV_27V	= 2,
	AD5755_DC_DC_MAXV_29V5	= 3,
पूर्ण;

क्रमागत ad5755_slew_rate अणु
	AD5755_SLEW_RATE_64k	= 0,
	AD5755_SLEW_RATE_32k	= 1,
	AD5755_SLEW_RATE_16k	= 2,
	AD5755_SLEW_RATE_8k	= 3,
	AD5755_SLEW_RATE_4k	= 4,
	AD5755_SLEW_RATE_2k	= 5,
	AD5755_SLEW_RATE_1k	= 6,
	AD5755_SLEW_RATE_500	= 7,
	AD5755_SLEW_RATE_250	= 8,
	AD5755_SLEW_RATE_125	= 9,
	AD5755_SLEW_RATE_64	= 10,
	AD5755_SLEW_RATE_32	= 11,
	AD5755_SLEW_RATE_16	= 12,
	AD5755_SLEW_RATE_8	= 13,
	AD5755_SLEW_RATE_4	= 14,
	AD5755_SLEW_RATE_0_5	= 15,
पूर्ण;

क्रमागत ad5755_slew_step_size अणु
	AD5755_SLEW_STEP_SIZE_1 = 0,
	AD5755_SLEW_STEP_SIZE_2 = 1,
	AD5755_SLEW_STEP_SIZE_4 = 2,
	AD5755_SLEW_STEP_SIZE_8 = 3,
	AD5755_SLEW_STEP_SIZE_16 = 4,
	AD5755_SLEW_STEP_SIZE_32 = 5,
	AD5755_SLEW_STEP_SIZE_64 = 6,
	AD5755_SLEW_STEP_SIZE_128 = 7,
	AD5755_SLEW_STEP_SIZE_256 = 8,
पूर्ण;

/**
 * काष्ठा ad5755_platक्रमm_data - AD5755 DAC driver platक्रमm data
 * @ext_dc_dc_compenstation_resistor: Whether an बाह्यal DC-DC converter
 * compensation रेजिस्टर is used.
 * @dc_dc_phase: DC-DC converter phase.
 * @dc_dc_freq: DC-DC converter frequency.
 * @dc_dc_maxv: DC-DC maximum allowed boost voltage.
 * @dac.mode: The mode to be used क्रम the DAC output.
 * @dac.ext_current_sense_resistor: Whether an बाह्यal current sense resistor
 * is used.
 * @dac.enable_voltage_overrange: Whether to enable 20% voltage output overrange.
 * @dac.slew.enable: Whether to enable digital slew.
 * @dac.slew.rate: Slew rate of the digital slew.
 * @dac.slew.step_size: Slew step size of the digital slew.
 **/
काष्ठा ad5755_platक्रमm_data अणु
	bool ext_dc_dc_compenstation_resistor;
	क्रमागत ad5755_dc_dc_phase dc_dc_phase;
	क्रमागत ad5755_dc_dc_freq dc_dc_freq;
	क्रमागत ad5755_dc_dc_maxv dc_dc_maxv;

	काष्ठा अणु
		क्रमागत ad5755_mode mode;
		bool ext_current_sense_resistor;
		bool enable_voltage_overrange;
		काष्ठा अणु
			bool enable;
			क्रमागत ad5755_slew_rate rate;
			क्रमागत ad5755_slew_step_size step_size;
		पूर्ण slew;
	पूर्ण dac[4];
पूर्ण;

#पूर्ण_अगर
