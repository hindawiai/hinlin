<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Simtec Audio support.
*/

/**
 * काष्ठा s3c24xx_audio_simtec_pdata - platक्रमm data क्रम simtec audio
 * @use_mpllin: Select codec घड़ी from MPLLin
 * @output_cdclk: Need to output CDCLK to the codec
 * @have_mic: Set अगर we have a MIC socket
 * @have_lout: Set अगर we have a LineOut socket
 * @amp_gpio: GPIO pin to enable the AMP
 * @amp_gain: Option GPIO to control AMP gain
 */
काष्ठा s3c24xx_audio_simtec_pdata अणु
	अचिन्हित पूर्णांक	use_mpllin:1;
	अचिन्हित पूर्णांक	output_cdclk:1;

	अचिन्हित पूर्णांक	have_mic:1;
	अचिन्हित पूर्णांक	have_lout:1;

	पूर्णांक		amp_gpio;
	पूर्णांक		amp_gain[2];

	व्योम	(*startup)(व्योम);
पूर्ण;
