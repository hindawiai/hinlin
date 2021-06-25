<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   AD1843 low level driver
 *
 *   Copyright 2003 Vivien Chappelier <vivien.chappelier@linux-mips.org>
 *   Copyright 2008 Thomas Bogenकरोerfer <tsbogend@alpha.franken.de>
 *
 *   inspired from vwsnd.c (SGI VW audio driver)
 *     Copyright 1999 Silicon Graphics, Inc.  All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ad1843.h>

/*
 * AD1843 bitfield definitions.  All are named as in the AD1843 data
 * sheet, with ad1843_ prepended and inभागidual bit numbers हटाओd.
 *
 * E.g., bits LSS0 through LSS2 become ad1843_LSS.
 *
 * Only the bitfields we need are defined.
 */

काष्ठा ad1843_bitfield अणु
	अक्षर reg;
	अक्षर lo_bit;
	अक्षर nbits;
पूर्ण;

अटल स्थिर काष्ठा ad1843_bitfield
	ad1843_PDNO   = अणु  0, 14,  1 पूर्ण,	/* Converter Power-Down Flag */
	ad1843_INIT   = अणु  0, 15,  1 पूर्ण,	/* Clock Initialization Flag */
	ad1843_RIG    = अणु  2,  0,  4 पूर्ण,	/* Right ADC Input Gain */
	ad1843_RMGE   = अणु  2,  4,  1 पूर्ण,	/* Right ADC Mic Gain Enable */
	ad1843_RSS    = अणु  2,  5,  3 पूर्ण,	/* Right ADC Source Select */
	ad1843_LIG    = अणु  2,  8,  4 पूर्ण,	/* Left ADC Input Gain */
	ad1843_LMGE   = अणु  2, 12,  1 पूर्ण,	/* Left ADC Mic Gain Enable */
	ad1843_LSS    = अणु  2, 13,  3 पूर्ण,	/* Left ADC Source Select */
	ad1843_RD2M   = अणु  3,  0,  5 पूर्ण,	/* Right DAC 2 Mix Gain/Atten */
	ad1843_RD2MM  = अणु  3,  7,  1 पूर्ण,	/* Right DAC 2 Mix Mute */
	ad1843_LD2M   = अणु  3,  8,  5 पूर्ण,	/* Left DAC 2 Mix Gain/Atten */
	ad1843_LD2MM  = अणु  3, 15,  1 पूर्ण,	/* Left DAC 2 Mix Mute */
	ad1843_RX1M   = अणु  4,  0,  5 पूर्ण,	/* Right Aux 1 Mix Gain/Atten */
	ad1843_RX1MM  = अणु  4,  7,  1 पूर्ण,	/* Right Aux 1 Mix Mute */
	ad1843_LX1M   = अणु  4,  8,  5 पूर्ण,	/* Left Aux 1 Mix Gain/Atten */
	ad1843_LX1MM  = अणु  4, 15,  1 पूर्ण,	/* Left Aux 1 Mix Mute */
	ad1843_RX2M   = अणु  5,  0,  5 पूर्ण,	/* Right Aux 2 Mix Gain/Atten */
	ad1843_RX2MM  = अणु  5,  7,  1 पूर्ण,	/* Right Aux 2 Mix Mute */
	ad1843_LX2M   = अणु  5,  8,  5 पूर्ण,	/* Left Aux 2 Mix Gain/Atten */
	ad1843_LX2MM  = अणु  5, 15,  1 पूर्ण,	/* Left Aux 2 Mix Mute */
	ad1843_RMCM   = अणु  7,  0,  5 पूर्ण,	/* Right Mic Mix Gain/Atten */
	ad1843_RMCMM  = अणु  7,  7,  1 पूर्ण,	/* Right Mic Mix Mute */
	ad1843_LMCM   = अणु  7,  8,  5 पूर्ण,	/* Left Mic Mix Gain/Atten */
	ad1843_LMCMM  = अणु  7, 15,  1 पूर्ण,	/* Left Mic Mix Mute */
	ad1843_HPOS   = अणु  8,  4,  1 पूर्ण,	/* Headphone Output Voltage Swing */
	ad1843_HPOM   = अणु  8,  5,  1 पूर्ण,	/* Headphone Output Mute */
	ad1843_MPOM   = अणु  8,  6,  1 पूर्ण,	/* Mono Output Mute */
	ad1843_RDA1G  = अणु  9,  0,  6 पूर्ण,	/* Right DAC1 Analog/Digital Gain */
	ad1843_RDA1GM = अणु  9,  7,  1 पूर्ण,	/* Right DAC1 Analog Mute */
	ad1843_LDA1G  = अणु  9,  8,  6 पूर्ण,	/* Left DAC1 Analog/Digital Gain */
	ad1843_LDA1GM = अणु  9, 15,  1 पूर्ण,	/* Left DAC1 Analog Mute */
	ad1843_RDA2G  = अणु 10,  0,  6 पूर्ण,	/* Right DAC2 Analog/Digital Gain */
	ad1843_RDA2GM = अणु 10,  7,  1 पूर्ण,	/* Right DAC2 Analog Mute */
	ad1843_LDA2G  = अणु 10,  8,  6 पूर्ण,	/* Left DAC2 Analog/Digital Gain */
	ad1843_LDA2GM = अणु 10, 15,  1 पूर्ण,	/* Left DAC2 Analog Mute */
	ad1843_RDA1AM = अणु 11,  7,  1 पूर्ण,	/* Right DAC1 Digital Mute */
	ad1843_LDA1AM = अणु 11, 15,  1 पूर्ण,	/* Left DAC1 Digital Mute */
	ad1843_RDA2AM = अणु 12,  7,  1 पूर्ण,	/* Right DAC2 Digital Mute */
	ad1843_LDA2AM = अणु 12, 15,  1 पूर्ण,	/* Left DAC2 Digital Mute */
	ad1843_ADLC   = अणु 15,  0,  2 पूर्ण,	/* ADC Left Sample Rate Source */
	ad1843_ADRC   = अणु 15,  2,  2 पूर्ण,	/* ADC Right Sample Rate Source */
	ad1843_DA1C   = अणु 15,  8,  2 पूर्ण,	/* DAC1 Sample Rate Source */
	ad1843_DA2C   = अणु 15, 10,  2 पूर्ण,	/* DAC2 Sample Rate Source */
	ad1843_C1C    = अणु 17,  0, 16 पूर्ण,	/* Clock 1 Sample Rate Select */
	ad1843_C2C    = अणु 20,  0, 16 पूर्ण,	/* Clock 2 Sample Rate Select */
	ad1843_C3C    = अणु 23,  0, 16 पूर्ण,	/* Clock 3 Sample Rate Select */
	ad1843_DAADL  = अणु 25,  4,  2 पूर्ण,	/* Digital ADC Left Source Select */
	ad1843_DAADR  = अणु 25,  6,  2 पूर्ण,	/* Digital ADC Right Source Select */
	ad1843_DAMIX  = अणु 25, 14,  1 पूर्ण,	/* DAC Digital Mix Enable */
	ad1843_DRSFLT = अणु 25, 15,  1 पूर्ण,	/* Digital Reampler Filter Mode */
	ad1843_ADLF   = अणु 26,  0,  2 पूर्ण, /* ADC Left Channel Data Format */
	ad1843_ADRF   = अणु 26,  2,  2 पूर्ण, /* ADC Right Channel Data Format */
	ad1843_ADTLK  = अणु 26,  4,  1 पूर्ण,	/* ADC Transmit Lock Mode Select */
	ad1843_SCF    = अणु 26,  7,  1 पूर्ण,	/* SCLK Frequency Select */
	ad1843_DA1F   = अणु 26,  8,  2 पूर्ण,	/* DAC1 Data Format Select */
	ad1843_DA2F   = अणु 26, 10,  2 पूर्ण,	/* DAC2 Data Format Select */
	ad1843_DA1SM  = अणु 26, 14,  1 पूर्ण,	/* DAC1 Stereo/Mono Mode Select */
	ad1843_DA2SM  = अणु 26, 15,  1 पूर्ण,	/* DAC2 Stereo/Mono Mode Select */
	ad1843_ADLEN  = अणु 27,  0,  1 पूर्ण,	/* ADC Left Channel Enable */
	ad1843_ADREN  = अणु 27,  1,  1 पूर्ण,	/* ADC Right Channel Enable */
	ad1843_AAMEN  = अणु 27,  4,  1 पूर्ण,	/* Analog to Analog Mix Enable */
	ad1843_ANAEN  = अणु 27,  7,  1 पूर्ण,	/* Analog Channel Enable */
	ad1843_DA1EN  = अणु 27,  8,  1 पूर्ण,	/* DAC1 Enable */
	ad1843_DA2EN  = अणु 27,  9,  1 पूर्ण,	/* DAC2 Enable */
	ad1843_DDMEN  = अणु 27, 12,  1 पूर्ण,	/* DAC2 to DAC1 Mix  Enable */
	ad1843_C1EN   = अणु 28, 11,  1 पूर्ण,	/* Clock Generator 1 Enable */
	ad1843_C2EN   = अणु 28, 12,  1 पूर्ण,	/* Clock Generator 2 Enable */
	ad1843_C3EN   = अणु 28, 13,  1 पूर्ण,	/* Clock Generator 3 Enable */
	ad1843_PDNI   = अणु 28, 15,  1 पूर्ण;	/* Converter Power Down */

/*
 * The various रेजिस्टरs of the AD1843 use three dअगरferent क्रमmats क्रम
 * specअगरying gain.  The ad1843_gain काष्ठाure parameterizes the
 * क्रमmats.
 */

काष्ठा ad1843_gain अणु
	पूर्णांक	negative;		/* nonzero अगर gain is negative. */
	स्थिर काष्ठा ad1843_bitfield *lfield;
	स्थिर काष्ठा ad1843_bitfield *rfield;
	स्थिर काष्ठा ad1843_bitfield *lmute;
	स्थिर काष्ठा ad1843_bitfield *rmute;
पूर्ण;

अटल स्थिर काष्ठा ad1843_gain ad1843_gain_RECLEV = अणु
	.negative = 0,
	.lfield   = &ad1843_LIG,
	.rfield   = &ad1843_RIG
पूर्ण;
अटल स्थिर काष्ठा ad1843_gain ad1843_gain_LINE = अणु
	.negative = 1,
	.lfield   = &ad1843_LX1M,
	.rfield   = &ad1843_RX1M,
	.lmute    = &ad1843_LX1MM,
	.rmute    = &ad1843_RX1MM
पूर्ण;
अटल स्थिर काष्ठा ad1843_gain ad1843_gain_LINE_2 = अणु
	.negative = 1,
	.lfield   = &ad1843_LDA2G,
	.rfield   = &ad1843_RDA2G,
	.lmute    = &ad1843_LDA2GM,
	.rmute    = &ad1843_RDA2GM
पूर्ण;
अटल स्थिर काष्ठा ad1843_gain ad1843_gain_MIC = अणु
	.negative = 1,
	.lfield   = &ad1843_LMCM,
	.rfield   = &ad1843_RMCM,
	.lmute    = &ad1843_LMCMM,
	.rmute    = &ad1843_RMCMM
पूर्ण;
अटल स्थिर काष्ठा ad1843_gain ad1843_gain_PCM_0 = अणु
	.negative = 1,
	.lfield   = &ad1843_LDA1G,
	.rfield   = &ad1843_RDA1G,
	.lmute    = &ad1843_LDA1GM,
	.rmute    = &ad1843_RDA1GM
पूर्ण;
अटल स्थिर काष्ठा ad1843_gain ad1843_gain_PCM_1 = अणु
	.negative = 1,
	.lfield   = &ad1843_LD2M,
	.rfield   = &ad1843_RD2M,
	.lmute    = &ad1843_LD2MM,
	.rmute    = &ad1843_RD2MM
पूर्ण;

अटल स्थिर काष्ठा ad1843_gain *ad1843_gain[AD1843_GAIN_SIZE] =
अणु
	&ad1843_gain_RECLEV,
	&ad1843_gain_LINE,
	&ad1843_gain_LINE_2,
	&ad1843_gain_MIC,
	&ad1843_gain_PCM_0,
	&ad1843_gain_PCM_1,
पूर्ण;

/* पढ़ो the current value of an AD1843 bitfield. */

अटल पूर्णांक ad1843_पढ़ो_bits(काष्ठा snd_ad1843 *ad1843,
			    स्थिर काष्ठा ad1843_bitfield *field)
अणु
	पूर्णांक w;

	w = ad1843->पढ़ो(ad1843->chip, field->reg);
	वापस w >> field->lo_bit & ((1 << field->nbits) - 1);
पूर्ण

/*
 * ग_लिखो a new value to an AD1843 bitfield and वापस the old value.
 */

अटल पूर्णांक ad1843_ग_लिखो_bits(काष्ठा snd_ad1843 *ad1843,
			     स्थिर काष्ठा ad1843_bitfield *field,
			     पूर्णांक newval)
अणु
	पूर्णांक w, mask, oldval, newbits;

	w = ad1843->पढ़ो(ad1843->chip, field->reg);
	mask = ((1 << field->nbits) - 1) << field->lo_bit;
	oldval = (w & mask) >> field->lo_bit;
	newbits = (newval << field->lo_bit) & mask;
	w = (w & ~mask) | newbits;
	ad1843->ग_लिखो(ad1843->chip, field->reg, w);

	वापस oldval;
पूर्ण

/*
 * ad1843_पढ़ो_multi पढ़ोs multiple bitfields from the same AD1843
 * रेजिस्टर.  It uses a single पढ़ो cycle to करो it.  (Reading the
 * ad1843 requires 256 bit बार at 12.288 MHz, or nearly 20
 * microseconds.)
 *
 * Called like this.
 *
 *  ad1843_पढ़ो_multi(ad1843, nfields,
 *		      &ad1843_FIELD1, &val1,
 *		      &ad1843_FIELD2, &val2, ...);
 */

अटल व्योम ad1843_पढ़ो_multi(काष्ठा snd_ad1843 *ad1843, पूर्णांक argcount, ...)
अणु
	बहु_सूची ap;
	स्थिर काष्ठा ad1843_bitfield *fp;
	पूर्णांक w = 0, mask, *value, reg = -1;

	बहु_शुरू(ap, argcount);
	जबतक (--argcount >= 0) अणु
		fp = बहु_तर्क(ap, स्थिर काष्ठा ad1843_bitfield *);
		value = बहु_तर्क(ap, पूर्णांक *);
		अगर (reg == -1) अणु
			reg = fp->reg;
			w = ad1843->पढ़ो(ad1843->chip, reg);
		पूर्ण

		mask = (1 << fp->nbits) - 1;
		*value = w >> fp->lo_bit & mask;
	पूर्ण
	बहु_पूर्ण(ap);
पूर्ण

/*
 * ad1843_ग_लिखो_multi stores multiple bitfields पूर्णांकo the same AD1843
 * रेजिस्टर.  It uses one पढ़ो and one ग_लिखो cycle to करो it.
 *
 * Called like this.
 *
 *  ad1843_ग_लिखो_multi(ad1843, nfields,
 *		       &ad1843_FIELD1, val1,
 *		       &ad1843_FIELF2, val2, ...);
 */

अटल व्योम ad1843_ग_लिखो_multi(काष्ठा snd_ad1843 *ad1843, पूर्णांक argcount, ...)
अणु
	बहु_सूची ap;
	पूर्णांक reg;
	स्थिर काष्ठा ad1843_bitfield *fp;
	पूर्णांक value;
	पूर्णांक w, m, mask, bits;

	mask = 0;
	bits = 0;
	reg = -1;

	बहु_शुरू(ap, argcount);
	जबतक (--argcount >= 0) अणु
		fp = बहु_तर्क(ap, स्थिर काष्ठा ad1843_bitfield *);
		value = बहु_तर्क(ap, पूर्णांक);
		अगर (reg == -1)
			reg = fp->reg;
		अन्यथा
			WARN_ON(reg != fp->reg);
		m = ((1 << fp->nbits) - 1) << fp->lo_bit;
		mask |= m;
		bits |= (value << fp->lo_bit) & m;
	पूर्ण
	बहु_पूर्ण(ap);

	अगर (~mask & 0xFFFF)
		w = ad1843->पढ़ो(ad1843->chip, reg);
	अन्यथा
		w = 0;
	w = (w & ~mask) | bits;
	ad1843->ग_लिखो(ad1843->chip, reg, w);
पूर्ण

पूर्णांक ad1843_get_gain_max(काष्ठा snd_ad1843 *ad1843, पूर्णांक id)
अणु
	स्थिर काष्ठा ad1843_gain *gp = ad1843_gain[id];
	पूर्णांक ret;

	ret = (1 << gp->lfield->nbits);
	अगर (!gp->lmute)
		ret -= 1;
	वापस ret;
पूर्ण

/*
 * ad1843_get_gain पढ़ोs the specअगरied रेजिस्टर and extracts the gain value
 * using the supplied gain type.
 */

पूर्णांक ad1843_get_gain(काष्ठा snd_ad1843 *ad1843, पूर्णांक id)
अणु
	पूर्णांक lg, rg, lm, rm;
	स्थिर काष्ठा ad1843_gain *gp = ad1843_gain[id];
	अचिन्हित लघु mask = (1 << gp->lfield->nbits) - 1;

	ad1843_पढ़ो_multi(ad1843, 2, gp->lfield, &lg, gp->rfield, &rg);
	अगर (gp->negative) अणु
		lg = mask - lg;
		rg = mask - rg;
	पूर्ण
	अगर (gp->lmute) अणु
		ad1843_पढ़ो_multi(ad1843, 2, gp->lmute, &lm, gp->rmute, &rm);
		अगर (lm)
			lg = 0;
		अगर (rm)
			rg = 0;
	पूर्ण
	वापस lg << 0 | rg << 8;
पूर्ण

/*
 * Set an audio channel's gain.
 *
 * Returns the new gain, which may be lower than the old gain.
 */

पूर्णांक ad1843_set_gain(काष्ठा snd_ad1843 *ad1843, पूर्णांक id, पूर्णांक newval)
अणु
	स्थिर काष्ठा ad1843_gain *gp = ad1843_gain[id];
	अचिन्हित लघु mask = (1 << gp->lfield->nbits) - 1;

	पूर्णांक lg = (newval >> 0) & mask;
	पूर्णांक rg = (newval >> 8) & mask;
	पूर्णांक lm = (lg == 0) ? 1 : 0;
	पूर्णांक rm = (rg == 0) ? 1 : 0;

	अगर (gp->negative) अणु
		lg = mask - lg;
		rg = mask - rg;
	पूर्ण
	अगर (gp->lmute)
		ad1843_ग_लिखो_multi(ad1843, 2, gp->lmute, lm, gp->rmute, rm);
	ad1843_ग_लिखो_multi(ad1843, 2, gp->lfield, lg, gp->rfield, rg);
	वापस ad1843_get_gain(ad1843, id);
पूर्ण

/* Returns the current recording source */

पूर्णांक ad1843_get_recsrc(काष्ठा snd_ad1843 *ad1843)
अणु
	पूर्णांक val = ad1843_पढ़ो_bits(ad1843, &ad1843_LSS);

	अगर (val < 0 || val > 2) अणु
		val = 2;
		ad1843_ग_लिखो_multi(ad1843, 2,
				   &ad1843_LSS, val, &ad1843_RSS, val);
	पूर्ण
	वापस val;
पूर्ण

/*
 * Set recording source.
 *
 * Returns newsrc on success, -त्रुटि_सं on failure.
 */

पूर्णांक ad1843_set_recsrc(काष्ठा snd_ad1843 *ad1843, पूर्णांक newsrc)
अणु
	अगर (newsrc < 0 || newsrc > 2)
		वापस -EINVAL;

	ad1843_ग_लिखो_multi(ad1843, 2, &ad1843_LSS, newsrc, &ad1843_RSS, newsrc);
	वापस newsrc;
पूर्ण

/* Setup ad1843 क्रम D/A conversion. */

व्योम ad1843_setup_dac(काष्ठा snd_ad1843 *ad1843,
		      अचिन्हित पूर्णांक id,
		      अचिन्हित पूर्णांक framerate,
		      snd_pcm_क्रमmat_t fmt,
		      अचिन्हित पूर्णांक channels)
अणु
	पूर्णांक ad_fmt = 0, ad_mode = 0;

	चयन (fmt) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		ad_fmt = 0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_U8:
		ad_fmt = 0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		ad_fmt = 1;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_MU_LAW:
		ad_fmt = 2;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:
		ad_fmt = 3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (channels) अणु
	हाल 2:
		ad_mode = 0;
		अवरोध;
	हाल 1:
		ad_mode = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (id) अणु
		ad1843_ग_लिखो_bits(ad1843, &ad1843_C2C, framerate);
		ad1843_ग_लिखो_multi(ad1843, 2,
				   &ad1843_DA2SM, ad_mode,
				   &ad1843_DA2F, ad_fmt);
	पूर्ण अन्यथा अणु
		ad1843_ग_लिखो_bits(ad1843, &ad1843_C1C, framerate);
		ad1843_ग_लिखो_multi(ad1843, 2,
				   &ad1843_DA1SM, ad_mode,
				   &ad1843_DA1F, ad_fmt);
	पूर्ण
पूर्ण

व्योम ad1843_shutकरोwn_dac(काष्ठा snd_ad1843 *ad1843, अचिन्हित पूर्णांक id)
अणु
	अगर (id)
		ad1843_ग_लिखो_bits(ad1843, &ad1843_DA2F, 1);
	अन्यथा
		ad1843_ग_लिखो_bits(ad1843, &ad1843_DA1F, 1);
पूर्ण

व्योम ad1843_setup_adc(काष्ठा snd_ad1843 *ad1843,
		      अचिन्हित पूर्णांक framerate,
		      snd_pcm_क्रमmat_t fmt,
		      अचिन्हित पूर्णांक channels)
अणु
	पूर्णांक da_fmt = 0;

	चयन (fmt) अणु
	हाल SNDRV_PCM_FORMAT_S8:	da_fmt = 0; अवरोध;
	हाल SNDRV_PCM_FORMAT_U8:	da_fmt = 0; अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:	da_fmt = 1; अवरोध;
	हाल SNDRV_PCM_FORMAT_MU_LAW:	da_fmt = 2; अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:	da_fmt = 3; अवरोध;
	शेष:		अवरोध;
	पूर्ण

	ad1843_ग_लिखो_bits(ad1843, &ad1843_C3C, framerate);
	ad1843_ग_लिखो_multi(ad1843, 2,
			   &ad1843_ADLF, da_fmt, &ad1843_ADRF, da_fmt);
पूर्ण

व्योम ad1843_shutकरोwn_adc(काष्ठा snd_ad1843 *ad1843)
अणु
	/* nothing to करो */
पूर्ण

/*
 * Fully initialize the ad1843.  As described in the AD1843 data
 * sheet, section "START-UP SEQUENCE".  The numbered comments are
 * subsection headings from the data sheet.  See the data sheet, pages
 * 52-54, क्रम more info.
 *
 * वापस 0 on success, -त्रुटि_सं on failure.  */

पूर्णांक ad1843_init(काष्ठा snd_ad1843 *ad1843)
अणु
	अचिन्हित दीर्घ later;

	अगर (ad1843_पढ़ो_bits(ad1843, &ad1843_INIT) != 0) अणु
		prपूर्णांकk(KERN_ERR "ad1843: AD1843 won't initialize\n");
		वापस -EIO;
	पूर्ण

	ad1843_ग_लिखो_bits(ad1843, &ad1843_SCF, 1);

	/* 4. Put the conversion resources पूर्णांकo standby. */
	ad1843_ग_लिखो_bits(ad1843, &ad1843_PDNI, 0);
	later = jअगरfies + msecs_to_jअगरfies(500);

	जबतक (ad1843_पढ़ो_bits(ad1843, &ad1843_PDNO)) अणु
		अगर (समय_after(jअगरfies, later)) अणु
			prपूर्णांकk(KERN_ERR
			       "ad1843: AD1843 won't power up\n");
			वापस -EIO;
		पूर्ण
		schedule_समयout_पूर्णांकerruptible(5);
	पूर्ण

	/* 5. Power up the घड़ी generators and enable घड़ी output pins. */
	ad1843_ग_लिखो_multi(ad1843, 3,
			   &ad1843_C1EN, 1,
			   &ad1843_C2EN, 1,
			   &ad1843_C3EN, 1);

	/* 6. Configure conversion resources जबतक they are in standby. */

	/* DAC1/2 use घड़ी 1/2 as source, ADC uses घड़ी 3.  Always. */
	ad1843_ग_लिखो_multi(ad1843, 4,
			   &ad1843_DA1C, 1,
			   &ad1843_DA2C, 2,
			   &ad1843_ADLC, 3,
			   &ad1843_ADRC, 3);

	/* 7. Enable conversion resources. */
	ad1843_ग_लिखो_bits(ad1843, &ad1843_ADTLK, 1);
	ad1843_ग_लिखो_multi(ad1843, 7,
			   &ad1843_ANAEN, 1,
			   &ad1843_AAMEN, 1,
			   &ad1843_DA1EN, 1,
			   &ad1843_DA2EN, 1,
			   &ad1843_DDMEN, 1,
			   &ad1843_ADLEN, 1,
			   &ad1843_ADREN, 1);

	/* 8. Configure conversion resources जबतक they are enabled. */

	/* set gain to 0 क्रम all channels */
	ad1843_set_gain(ad1843, AD1843_GAIN_RECLEV, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_LINE, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_LINE_2, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_MIC, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_PCM_0, 0);
	ad1843_set_gain(ad1843, AD1843_GAIN_PCM_1, 0);

	/* Unmute all channels. */
	/* DAC1 */
	ad1843_ग_लिखो_multi(ad1843, 2, &ad1843_LDA1GM, 0, &ad1843_RDA1GM, 0);
	/* DAC2 */
	ad1843_ग_लिखो_multi(ad1843, 2, &ad1843_LDA2GM, 0, &ad1843_RDA2GM, 0);

	/* Set शेष recording source to Line In and set
	 * mic gain to +20 dB.
	 */
	ad1843_set_recsrc(ad1843, 2);
	ad1843_ग_लिखो_multi(ad1843, 2, &ad1843_LMGE, 1, &ad1843_RMGE, 1);

	/* Set Speaker Out level to +/- 4V and unmute it. */
	ad1843_ग_लिखो_multi(ad1843, 3,
			   &ad1843_HPOS, 1,
			   &ad1843_HPOM, 0,
			   &ad1843_MPOM, 0);

	वापस 0;
पूर्ण
