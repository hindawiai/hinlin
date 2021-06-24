<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * da7218.h - DA7218 ASoC Codec Driver Platक्रमm Data
 *
 * Copyright (c) 2015 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित _DA7218_PDATA_H
#घोषणा _DA7218_PDATA_H

/* Mic Bias */
क्रमागत da7218_micbias_voltage अणु
	DA7218_MICBIAS_1_2V = -1,
	DA7218_MICBIAS_1_6V,
	DA7218_MICBIAS_1_8V,
	DA7218_MICBIAS_2_0V,
	DA7218_MICBIAS_2_2V,
	DA7218_MICBIAS_2_4V,
	DA7218_MICBIAS_2_6V,
	DA7218_MICBIAS_2_8V,
	DA7218_MICBIAS_3_0V,
पूर्ण;

क्रमागत da7218_mic_amp_in_sel अणु
	DA7218_MIC_AMP_IN_SEL_DIFF = 0,
	DA7218_MIC_AMP_IN_SEL_SE_P,
	DA7218_MIC_AMP_IN_SEL_SE_N,
पूर्ण;

/* DMIC */
क्रमागत da7218_dmic_data_sel अणु
	DA7218_DMIC_DATA_LRISE_RFALL = 0,
	DA7218_DMIC_DATA_LFALL_RRISE,
पूर्ण;

क्रमागत da7218_dmic_samplephase अणु
	DA7218_DMIC_SAMPLE_ON_CLKEDGE = 0,
	DA7218_DMIC_SAMPLE_BETWEEN_CLKEDGE,
पूर्ण;

क्रमागत da7218_dmic_clk_rate अणु
	DA7218_DMIC_CLK_3_0MHZ = 0,
	DA7218_DMIC_CLK_1_5MHZ,
पूर्ण;

/* Headphone Detect */
क्रमागत da7218_hpldet_jack_rate अणु
	DA7218_HPLDET_JACK_RATE_5US = 0,
	DA7218_HPLDET_JACK_RATE_10US,
	DA7218_HPLDET_JACK_RATE_20US,
	DA7218_HPLDET_JACK_RATE_40US,
	DA7218_HPLDET_JACK_RATE_80US,
	DA7218_HPLDET_JACK_RATE_160US,
	DA7218_HPLDET_JACK_RATE_320US,
	DA7218_HPLDET_JACK_RATE_640US,
पूर्ण;

क्रमागत da7218_hpldet_jack_debounce अणु
	DA7218_HPLDET_JACK_DEBOUNCE_OFF = 0,
	DA7218_HPLDET_JACK_DEBOUNCE_2,
	DA7218_HPLDET_JACK_DEBOUNCE_3,
	DA7218_HPLDET_JACK_DEBOUNCE_4,
पूर्ण;

क्रमागत da7218_hpldet_jack_thr अणु
	DA7218_HPLDET_JACK_THR_84PCT = 0,
	DA7218_HPLDET_JACK_THR_88PCT,
	DA7218_HPLDET_JACK_THR_92PCT,
	DA7218_HPLDET_JACK_THR_96PCT,
पूर्ण;

काष्ठा da7218_hpldet_pdata अणु
	क्रमागत da7218_hpldet_jack_rate jack_rate;
	क्रमागत da7218_hpldet_jack_debounce jack_debounce;
	क्रमागत da7218_hpldet_jack_thr jack_thr;
	bool comp_inv;
	bool hyst;
	bool disअक्षरge;
पूर्ण;

काष्ठा da7218_pdata अणु
	/* Mic */
	क्रमागत da7218_micbias_voltage micbias1_lvl;
	क्रमागत da7218_micbias_voltage micbias2_lvl;
	क्रमागत da7218_mic_amp_in_sel mic1_amp_in_sel;
	क्रमागत da7218_mic_amp_in_sel mic2_amp_in_sel;

	/* DMIC */
	क्रमागत da7218_dmic_data_sel dmic1_data_sel;
	क्रमागत da7218_dmic_data_sel dmic2_data_sel;
	क्रमागत da7218_dmic_samplephase dmic1_samplephase;
	क्रमागत da7218_dmic_samplephase dmic2_samplephase;
	क्रमागत da7218_dmic_clk_rate dmic1_clk_rate;
	क्रमागत da7218_dmic_clk_rate dmic2_clk_rate;

	/* HP Dअगरf Supply - DA7217 only */
	bool hp_dअगरf_single_supply;

	/* HP Detect - DA7218 only */
	काष्ठा da7218_hpldet_pdata *hpldet_pdata;
पूर्ण;

#पूर्ण_अगर /* _DA7218_PDATA_H */
