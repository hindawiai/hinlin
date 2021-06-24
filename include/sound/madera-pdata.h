<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Platक्रमm data क्रम Madera codec driver
 *
 * Copyright (C) 2016-2019 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 */

#अगर_अघोषित MADERA_CODEC_PDATA_H
#घोषणा MADERA_CODEC_PDATA_H

#समावेश <linux/kernel.h>

#घोषणा MADERA_MAX_INPUT		6
#घोषणा MADERA_MAX_MUXED_CHANNELS	4
#घोषणा MADERA_MAX_OUTPUT		6
#घोषणा MADERA_MAX_AIF			4
#घोषणा MADERA_MAX_PDM_SPK		2
#घोषणा MADERA_MAX_DSP			7

/**
 * काष्ठा madera_codec_pdata
 *
 * @max_channels_घड़ीed: Maximum number of channels that I2S घड़ीs will be
 *			  generated क्रम. Useful when घड़ी master क्रम प्रणालीs
 *			  where the I2S bus has multiple data lines.
 * @dmic_ref:		  Indicates how the MICBIAS pins have been बाह्यally
 *			  connected to DMICs on each input. A value of 0
 *			  indicates MICVDD and is the शेष. Other values are:
 *			  For CS47L35 one of the CS47L35_DMIC_REF_xxx values
 *			  For all other codecs one of the MADERA_DMIC_REF_xxx
 *			  Also see the datasheet क्रम a description of the
 *			  INn_DMIC_SUP field.
 * @inmode:		  Mode क्रम the ADC inमाला_दो. One of the MADERA_INMODE_xxx
 *			  values. Two-dimensional array
 *			  [input_number][channel number], with four slots per
 *			  input in the order
 *			  [n][0]=INnAL [n][1]=INnAR [n][2]=INnBL [n][3]=INnBR
 * @out_mono:		  For each output set the value to TRUE to indicate that
 *			  the output is mono. [0]=OUT1, [1]=OUT2, ...
 * @pdm_fmt:		  PDM speaker data क्रमmat. See the PDM_SPKn_FMT field in
 *			  the datasheet क्रम a description of this value.
 * @pdm_mute:		  PDM mute क्रमmat. See the PDM_SPKn_CTRL_1 रेजिस्टर
 *			  in the datasheet क्रम a description of this value.
 */
काष्ठा madera_codec_pdata अणु
	u32 max_channels_घड़ीed[MADERA_MAX_AIF];

	u32 dmic_ref[MADERA_MAX_INPUT];

	u32 inmode[MADERA_MAX_INPUT][MADERA_MAX_MUXED_CHANNELS];

	bool out_mono[MADERA_MAX_OUTPUT];

	u32 pdm_fmt[MADERA_MAX_PDM_SPK];
	u32 pdm_mute[MADERA_MAX_PDM_SPK];
पूर्ण;

#पूर्ण_अगर
