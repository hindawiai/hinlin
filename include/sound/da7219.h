<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * da7219.h - DA7219 ASoC Codec Driver Platक्रमm Data
 *
 * Copyright (c) 2015 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित __DA7219_PDATA_H
#घोषणा __DA7219_PDATA_H

/* Mic Bias */
क्रमागत da7219_micbias_voltage अणु
	DA7219_MICBIAS_1_6V = 0,
	DA7219_MICBIAS_1_8V,
	DA7219_MICBIAS_2_0V,
	DA7219_MICBIAS_2_2V,
	DA7219_MICBIAS_2_4V,
	DA7219_MICBIAS_2_6V,
पूर्ण;

/* Mic input type */
क्रमागत da7219_mic_amp_in_sel अणु
	DA7219_MIC_AMP_IN_SEL_DIFF = 0,
	DA7219_MIC_AMP_IN_SEL_SE_P,
	DA7219_MIC_AMP_IN_SEL_SE_N,
पूर्ण;

काष्ठा da7219_aad_pdata;

क्रमागत da7219_dai_clks अणु
	DA7219_DAI_WCLK_IDX = 0,
	DA7219_DAI_BCLK_IDX,
	DA7219_DAI_NUM_CLKS,
पूर्ण;

काष्ठा da7219_pdata अणु
	bool wakeup_source;

	स्थिर अक्षर *dai_clk_names[DA7219_DAI_NUM_CLKS];

	/* Mic */
	क्रमागत da7219_micbias_voltage micbias_lvl;
	क्रमागत da7219_mic_amp_in_sel mic_amp_in_sel;

	/* AAD */
	काष्ठा da7219_aad_pdata *aad_pdata;
पूर्ण;

#पूर्ण_अगर /* __DA7219_PDATA_H */
