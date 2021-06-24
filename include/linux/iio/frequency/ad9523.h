<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AD9523 SPI Low Jitter Clock Generator
 *
 * Copyright 2012 Analog Devices Inc.
 */

#अगर_अघोषित IIO_FREQUENCY_AD9523_H_
#घोषणा IIO_FREQUENCY_AD9523_H_

क्रमागत outp_drv_mode अणु
	TRISTATE,
	LVPECL_8mA,
	LVDS_4mA,
	LVDS_7mA,
	HSTL0_16mA,
	HSTL1_8mA,
	CMOS_CONF1,
	CMOS_CONF2,
	CMOS_CONF3,
	CMOS_CONF4,
	CMOS_CONF5,
	CMOS_CONF6,
	CMOS_CONF7,
	CMOS_CONF8,
	CMOS_CONF9
पूर्ण;

क्रमागत ref_sel_mode अणु
	NONEREVERTIVE_STAY_ON_REFB,
	REVERT_TO_REFA,
	SELECT_REFA,
	SELECT_REFB,
	EXT_REF_SEL
पूर्ण;

/**
 * काष्ठा ad9523_channel_spec - Output channel configuration
 *
 * @channel_num: Output channel number.
 * @भागider_output_invert_en: Invert the polarity of the output घड़ी.
 * @sync_ignore_en: Ignore chip-level SYNC संकेत.
 * @low_घातer_mode_en: Reduce घातer used in the dअगरferential output modes.
 * @use_alt_घड़ी_src: Channel भागider uses alternative clk source.
 * @output_dis: Disables, घातers करोwn the entire channel.
 * @driver_mode: Output driver mode (logic level family).
 * @भागider_phase: Divider initial phase after a SYNC. Range 0..63
		   LSB = 1/2 of a period of the भागider input घड़ी.
 * @channel_भागider: 10-bit channel भागider.
 * @extended_name: Optional descriptive channel name.
 */

काष्ठा ad9523_channel_spec अणु
	अचिन्हित		channel_num;
	bool			भागider_output_invert_en;
	bool			sync_ignore_en;
	bool			low_घातer_mode_en;
				 /* CH0..CH3 VCXO, CH4..CH9 VCO2 */
	bool			use_alt_घड़ी_src;
	bool			output_dis;
	क्रमागत outp_drv_mode	driver_mode;
	अचिन्हित अक्षर		भागider_phase;
	अचिन्हित लघु		channel_भागider;
	अक्षर			extended_name[16];
पूर्ण;

क्रमागत pll1_rzero_resistor अणु
	RZERO_883_OHM,
	RZERO_677_OHM,
	RZERO_341_OHM,
	RZERO_135_OHM,
	RZERO_10_OHM,
	RZERO_USE_EXT_RES = 8,
पूर्ण;

क्रमागत rpole2_resistor अणु
	RPOLE2_900_OHM,
	RPOLE2_450_OHM,
	RPOLE2_300_OHM,
	RPOLE2_225_OHM,
पूर्ण;

क्रमागत rzero_resistor अणु
	RZERO_3250_OHM,
	RZERO_2750_OHM,
	RZERO_2250_OHM,
	RZERO_2100_OHM,
	RZERO_3000_OHM,
	RZERO_2500_OHM,
	RZERO_2000_OHM,
	RZERO_1850_OHM,
पूर्ण;

क्रमागत cpole1_capacitor अणु
	CPOLE1_0_PF,
	CPOLE1_8_PF,
	CPOLE1_16_PF,
	CPOLE1_24_PF,
	_CPOLE1_24_PF, /* place holder */
	CPOLE1_32_PF,
	CPOLE1_40_PF,
	CPOLE1_48_PF,
पूर्ण;

/**
 * काष्ठा ad9523_platक्रमm_data - platक्रमm specअगरic inक्रमmation
 *
 * @vcxo_freq: External VCXO frequency in Hz
 * @refa_dअगरf_rcv_en: REFA dअगरferential/single-ended input selection.
 * @refb_dअगरf_rcv_en: REFB dअगरferential/single-ended input selection.
 * @zd_in_dअगरf_en: Zero Delay dअगरferential/single-ended input selection.
 * @osc_in_dअगरf_en: OSC dअगरferential/ single-ended input selection.
 * @refa_cmos_neg_inp_en: REFA single-ended neg./pos. input enable.
 * @refb_cmos_neg_inp_en: REFB single-ended neg./pos. input enable.
 * @zd_in_cmos_neg_inp_en: Zero Delay single-ended neg./pos. input enable.
 * @osc_in_cmos_neg_inp_en: OSC single-ended neg./pos. input enable.
 * @refa_r_भाग: PLL1 10-bit REFA R भागider.
 * @refb_r_भाग: PLL1 10-bit REFB R भागider.
 * @pll1_feedback_भाग: PLL1 10-bit Feedback N भागider.
 * @pll1_अक्षरge_pump_current_nA: Magnitude of PLL1 अक्षरge pump current (nA).
 * @zero_delay_mode_पूर्णांकernal_en: Internal, बाह्यal Zero Delay mode selection.
 * @osc_in_feedback_en: PLL1 feedback path, local feedback from
 *			the OSC_IN receiver or zero delay mode
 * @pll1_loop_filter_rzero: PLL1 Loop Filter Zero Resistor selection.
 * @ref_mode: Reference selection mode.
 * @pll2_अक्षरge_pump_current_nA: Magnitude of PLL2 अक्षरge pump current (nA).
 * @pll2_nभाग_a_cnt: PLL2 Feedback N-भागider, A Counter, range 0..4.
 * @pll2_nभाग_b_cnt: PLL2 Feedback N-भागider, B Counter, range 0..63.
 * @pll2_freq_द्विगुनr_en: PLL2 frequency द्विगुनr enable.
 * @pll2_r2_भाग: PLL2 R2 भागider, range 0..31.
 * @pll2_vco_भाग_m1: VCO1 भागider, range 3..5.
 * @pll2_vco_भाग_m2: VCO2 भागider, range 3..5.
 * @rpole2: PLL2 loop filter Rpole resistor value.
 * @rzero: PLL2 loop filter Rzero resistor value.
 * @cpole1: PLL2 loop filter Cpole capacitor value.
 * @rzero_bypass_en: PLL2 loop filter Rzero bypass enable.
 * @num_channels: Array size of काष्ठा ad9523_channel_spec.
 * @channels: Poपूर्णांकer to channel array.
 * @name: Optional alternative iio device name.
 */

काष्ठा ad9523_platक्रमm_data अणु
	अचिन्हित दीर्घ vcxo_freq;

	/* Dअगरferential/ Single-Ended Input Configuration */
	bool				refa_dअगरf_rcv_en;
	bool				refb_dअगरf_rcv_en;
	bool				zd_in_dअगरf_en;
	bool				osc_in_dअगरf_en;

	/*
	 * Valid अगर dअगरferential input disabled
	 * अगर false शेषs to pos input
	 */
	bool				refa_cmos_neg_inp_en;
	bool				refb_cmos_neg_inp_en;
	bool				zd_in_cmos_neg_inp_en;
	bool				osc_in_cmos_neg_inp_en;

	/* PLL1 Setting */
	अचिन्हित लघु			refa_r_भाग;
	अचिन्हित लघु			refb_r_भाग;
	अचिन्हित लघु			pll1_feedback_भाग;
	अचिन्हित लघु			pll1_अक्षरge_pump_current_nA;
	bool				zero_delay_mode_पूर्णांकernal_en;
	bool				osc_in_feedback_en;
	क्रमागत pll1_rzero_resistor	pll1_loop_filter_rzero;

	/* Reference */
	क्रमागत ref_sel_mode		ref_mode;

	/* PLL2 Setting */
	अचिन्हित पूर्णांक			pll2_अक्षरge_pump_current_nA;
	अचिन्हित अक्षर			pll2_nभाग_a_cnt;
	अचिन्हित अक्षर			pll2_nभाग_b_cnt;
	bool				pll2_freq_द्विगुनr_en;
	अचिन्हित अक्षर			pll2_r2_भाग;
	अचिन्हित अक्षर			pll2_vco_भाग_m1; /* 3..5 */
	अचिन्हित अक्षर			pll2_vco_भाग_m2; /* 3..5 */

	/* Loop Filter PLL2 */
	क्रमागत rpole2_resistor		rpole2;
	क्रमागत rzero_resistor		rzero;
	क्रमागत cpole1_capacitor		cpole1;
	bool				rzero_bypass_en;

	/* Output Channel Configuration */
	पूर्णांक				num_channels;
	काष्ठा ad9523_channel_spec	*channels;

	अक्षर				name[SPI_NAME_SIZE];
पूर्ण;

#पूर्ण_अगर /* IIO_FREQUENCY_AD9523_H_ */
