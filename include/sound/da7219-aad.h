<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * da7219-aad.h - DA7322 ASoC Codec AAD Driver Platक्रमm Data
 *
 * Copyright (c) 2015 Dialog Semiconductor Ltd.
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित __DA7219_AAD_PDATA_H
#घोषणा __DA7219_AAD_PDATA_H

क्रमागत da7219_aad_micbias_pulse_lvl अणु
	DA7219_AAD_MICBIAS_PULSE_LVL_OFF = 0,
	DA7219_AAD_MICBIAS_PULSE_LVL_2_8V = 6,
	DA7219_AAD_MICBIAS_PULSE_LVL_2_9V,
पूर्ण;

क्रमागत da7219_aad_btn_cfg अणु
	DA7219_AAD_BTN_CFG_2MS = 1,
	DA7219_AAD_BTN_CFG_5MS,
	DA7219_AAD_BTN_CFG_10MS,
	DA7219_AAD_BTN_CFG_50MS,
	DA7219_AAD_BTN_CFG_100MS,
	DA7219_AAD_BTN_CFG_200MS,
	DA7219_AAD_BTN_CFG_500MS,
पूर्ण;

क्रमागत da7219_aad_mic_det_thr अणु
	DA7219_AAD_MIC_DET_THR_200_OHMS = 0,
	DA7219_AAD_MIC_DET_THR_500_OHMS,
	DA7219_AAD_MIC_DET_THR_750_OHMS,
	DA7219_AAD_MIC_DET_THR_1000_OHMS,
पूर्ण;

क्रमागत da7219_aad_jack_ins_deb अणु
	DA7219_AAD_JACK_INS_DEB_5MS = 0,
	DA7219_AAD_JACK_INS_DEB_10MS,
	DA7219_AAD_JACK_INS_DEB_20MS,
	DA7219_AAD_JACK_INS_DEB_50MS,
	DA7219_AAD_JACK_INS_DEB_100MS,
	DA7219_AAD_JACK_INS_DEB_200MS,
	DA7219_AAD_JACK_INS_DEB_500MS,
	DA7219_AAD_JACK_INS_DEB_1S,
पूर्ण;

क्रमागत da7219_aad_jack_det_rate अणु
	DA7219_AAD_JACK_DET_RATE_32_64MS = 0,
	DA7219_AAD_JACK_DET_RATE_64_128MS,
	DA7219_AAD_JACK_DET_RATE_128_256MS,
	DA7219_AAD_JACK_DET_RATE_256_512MS,
पूर्ण;

क्रमागत da7219_aad_jack_rem_deb अणु
	DA7219_AAD_JACK_REM_DEB_1MS = 0,
	DA7219_AAD_JACK_REM_DEB_5MS,
	DA7219_AAD_JACK_REM_DEB_10MS,
	DA7219_AAD_JACK_REM_DEB_20MS,
पूर्ण;

क्रमागत da7219_aad_btn_avg अणु
	DA7219_AAD_BTN_AVG_1 = 0,
	DA7219_AAD_BTN_AVG_2,
	DA7219_AAD_BTN_AVG_4,
	DA7219_AAD_BTN_AVG_8,
पूर्ण;

क्रमागत da7219_aad_adc_1bit_rpt अणु
	DA7219_AAD_ADC_1BIT_RPT_1 = 0,
	DA7219_AAD_ADC_1BIT_RPT_2,
	DA7219_AAD_ADC_1BIT_RPT_4,
	DA7219_AAD_ADC_1BIT_RPT_8,
पूर्ण;

काष्ठा da7219_aad_pdata अणु
	पूर्णांक irq;

	क्रमागत da7219_aad_micbias_pulse_lvl micbias_pulse_lvl;
	u32 micbias_pulse_समय;
	क्रमागत da7219_aad_btn_cfg btn_cfg;
	क्रमागत da7219_aad_mic_det_thr mic_det_thr;
	क्रमागत da7219_aad_jack_ins_deb jack_ins_deb;
	क्रमागत da7219_aad_jack_det_rate jack_det_rate;
	क्रमागत da7219_aad_jack_rem_deb jack_rem_deb;

	u8 a_d_btn_thr;
	u8 d_b_btn_thr;
	u8 b_c_btn_thr;
	u8 c_mic_btn_thr;

	क्रमागत da7219_aad_btn_avg btn_avg;
	क्रमागत da7219_aad_adc_1bit_rpt adc_1bit_rpt;
पूर्ण;

#पूर्ण_अगर /* __DA7219_AAD_PDATA_H */
