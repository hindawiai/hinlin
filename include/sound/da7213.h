<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * da7213.h - DA7213 ASoC Codec Driver Platक्रमm Data
 *
 * Copyright (c) 2013 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित _DA7213_PDATA_H
#घोषणा _DA7213_PDATA_H

क्रमागत da7213_micbias_voltage अणु
	DA7213_MICBIAS_1_6V = 0,
	DA7213_MICBIAS_2_2V = 1,
	DA7213_MICBIAS_2_5V = 2,
	DA7213_MICBIAS_3_0V = 3,
पूर्ण;

क्रमागत da7213_dmic_data_sel अणु
	DA7213_DMIC_DATA_LRISE_RFALL = 0,
	DA7213_DMIC_DATA_LFALL_RRISE = 1,
पूर्ण;

क्रमागत da7213_dmic_samplephase अणु
	DA7213_DMIC_SAMPLE_ON_CLKEDGE = 0,
	DA7213_DMIC_SAMPLE_BETWEEN_CLKEDGE = 1,
पूर्ण;

क्रमागत da7213_dmic_clk_rate अणु
	DA7213_DMIC_CLK_3_0MHZ = 0,
	DA7213_DMIC_CLK_1_5MHZ = 1,
पूर्ण;

काष्ठा da7213_platक्रमm_data अणु
	/* Mic Bias voltage */
	क्रमागत da7213_micbias_voltage micbias1_lvl;
	क्रमागत da7213_micbias_voltage micbias2_lvl;

	/* DMIC config */
	क्रमागत da7213_dmic_data_sel dmic_data_sel;
	क्रमागत da7213_dmic_samplephase dmic_samplephase;
	क्रमागत da7213_dmic_clk_rate dmic_clk_rate;
पूर्ण;

#पूर्ण_अगर /* _DA7213_PDATA_H */
