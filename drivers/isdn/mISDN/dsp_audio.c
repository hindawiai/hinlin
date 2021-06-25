<शैली गुरु>
/*
 * Audio support data क्रम mISDN_dsp.
 *
 * Copyright 2002/2003 by Andreas Eversberg (jolly@eversberg.eu)
 * Rewritten by Peter
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/mISDNdsp.h>
#समावेश <linux/export.h>
#समावेश <linux/bitrev.h>
#समावेश "core.h"
#समावेश "dsp.h"

/* ulaw[अचिन्हित अक्षर] -> चिन्हित 16-bit */
s32 dsp_audio_ulaw_to_s32[256];
/* alaw[अचिन्हित अक्षर] -> चिन्हित 16-bit */
s32 dsp_audio_alaw_to_s32[256];

s32 *dsp_audio_law_to_s32;
EXPORT_SYMBOL(dsp_audio_law_to_s32);

/* चिन्हित 16-bit -> law */
u8 dsp_audio_s16_to_law[65536];
EXPORT_SYMBOL(dsp_audio_s16_to_law);

/* alaw -> ulaw */
u8 dsp_audio_alaw_to_ulaw[256];
/* ulaw -> alaw */
अटल u8 dsp_audio_ulaw_to_alaw[256];
u8 dsp_silence;


/*****************************************************
 * generate table क्रम conversion of s16 to alaw/ulaw *
 *****************************************************/

#घोषणा AMI_MASK 0x55

अटल अंतरभूत अचिन्हित अक्षर linear2alaw(लघु पूर्णांक linear)
अणु
	पूर्णांक mask;
	पूर्णांक seg;
	पूर्णांक pcm_val;
	अटल पूर्णांक seg_end[8] = अणु
		0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF
	पूर्ण;

	pcm_val = linear;
	अगर (pcm_val >= 0) अणु
		/* Sign (7th) bit = 1 */
		mask = AMI_MASK | 0x80;
	पूर्ण अन्यथा अणु
		/* Sign bit = 0 */
		mask = AMI_MASK;
		pcm_val = -pcm_val;
	पूर्ण

	/* Convert the scaled magnitude to segment number. */
	क्रम (seg = 0; seg < 8; seg++) अणु
		अगर (pcm_val <= seg_end[seg])
			अवरोध;
	पूर्ण
	/* Combine the sign, segment, and quantization bits. */
	वापस  ((seg << 4) |
		 ((pcm_val >> ((seg)  ?  (seg + 3)  :  4)) & 0x0F)) ^ mask;
पूर्ण


अटल अंतरभूत लघु पूर्णांक alaw2linear(अचिन्हित अक्षर alaw)
अणु
	पूर्णांक i;
	पूर्णांक seg;

	alaw ^= AMI_MASK;
	i = ((alaw & 0x0F) << 4) + 8 /* rounding error */;
	seg = (((पूर्णांक) alaw & 0x70) >> 4);
	अगर (seg)
		i = (i + 0x100) << (seg - 1);
	वापस (लघु पूर्णांक) ((alaw & 0x80)  ?  i  :  -i);
पूर्ण

अटल अंतरभूत लघु पूर्णांक ulaw2linear(अचिन्हित अक्षर ulaw)
अणु
	लघु mu, e, f, y;
	अटल लघु etab[] = अणु0, 132, 396, 924, 1980, 4092, 8316, 16764पूर्ण;

	mu = 255 - ulaw;
	e = (mu & 0x70) / 16;
	f = mu & 0x0f;
	y = f * (1 << (e + 3));
	y += etab[e];
	अगर (mu & 0x80)
		y = -y;
	वापस y;
पूर्ण

#घोषणा BIAS 0x84   /*!< define the add-in bias क्रम 16 bit samples */

अटल अचिन्हित अक्षर linear2ulaw(लघु sample)
अणु
	अटल पूर्णांक exp_lut[256] = अणु
		0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7पूर्ण;
	पूर्णांक sign, exponent, mantissa;
	अचिन्हित अक्षर ulawbyte;

	/* Get the sample पूर्णांकo sign-magnitude. */
	sign = (sample >> 8) & 0x80;	  /* set aside the sign */
	अगर (sign != 0)
		sample = -sample;	      /* get magnitude */

	/* Convert from 16 bit linear to ulaw. */
	sample = sample + BIAS;
	exponent = exp_lut[(sample >> 7) & 0xFF];
	mantissa = (sample >> (exponent + 3)) & 0x0F;
	ulawbyte = ~(sign | (exponent << 4) | mantissa);

	वापस ulawbyte;
पूर्ण

व्योम dsp_audio_generate_law_tables(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 256; i++)
		dsp_audio_alaw_to_s32[i] = alaw2linear(bitrev8((u8)i));

	क्रम (i = 0; i < 256; i++)
		dsp_audio_ulaw_to_s32[i] = ulaw2linear(bitrev8((u8)i));

	क्रम (i = 0; i < 256; i++) अणु
		dsp_audio_alaw_to_ulaw[i] =
			linear2ulaw(dsp_audio_alaw_to_s32[i]);
		dsp_audio_ulaw_to_alaw[i] =
			linear2alaw(dsp_audio_ulaw_to_s32[i]);
	पूर्ण
पूर्ण

व्योम
dsp_audio_generate_s2law_table(व्योम)
अणु
	पूर्णांक i;

	अगर (dsp_options & DSP_OPT_ULAW) अणु
		/* generating ulaw-table */
		क्रम (i = -32768; i < 32768; i++) अणु
			dsp_audio_s16_to_law[i & 0xffff] =
				bitrev8(linear2ulaw(i));
		पूर्ण
	पूर्ण अन्यथा अणु
		/* generating alaw-table */
		क्रम (i = -32768; i < 32768; i++) अणु
			dsp_audio_s16_to_law[i & 0xffff] =
				bitrev8(linear2alaw(i));
		पूर्ण
	पूर्ण
पूर्ण


/*
 * the seven bit sample is the number of every second alaw-sample ordered by
 * aplitude. 0x00 is negative, 0x7f is positive amplitude.
 */
u8 dsp_audio_seven2law[128];
u8 dsp_audio_law2seven[256];

/********************************************************************
 * generate table क्रम conversion law from/to 7-bit alaw-like sample *
 ********************************************************************/

व्योम
dsp_audio_generate_seven(व्योम)
अणु
	पूर्णांक i, j, k;
	u8 spl;
	u8 sorted_alaw[256];

	/* generate alaw table, sorted by the linear value */
	क्रम (i = 0; i < 256; i++) अणु
		j = 0;
		क्रम (k = 0; k < 256; k++) अणु
			अगर (dsp_audio_alaw_to_s32[k]
			    < dsp_audio_alaw_to_s32[i])
				j++;
		पूर्ण
		sorted_alaw[j] = i;
	पूर्ण

	/* generate tabels */
	क्रम (i = 0; i < 256; i++) अणु
		/* spl is the source: the law-sample (converted to alaw) */
		spl = i;
		अगर (dsp_options & DSP_OPT_ULAW)
			spl = dsp_audio_ulaw_to_alaw[i];
		/* find the 7-bit-sample */
		क्रम (j = 0; j < 256; j++) अणु
			अगर (sorted_alaw[j] == spl)
				अवरोध;
		पूर्ण
		/* ग_लिखो 7-bit audio value */
		dsp_audio_law2seven[i] = j >> 1;
	पूर्ण
	क्रम (i = 0; i < 128; i++) अणु
		spl = sorted_alaw[i << 1];
		अगर (dsp_options & DSP_OPT_ULAW)
			spl = dsp_audio_alaw_to_ulaw[spl];
		dsp_audio_seven2law[i] = spl;
	पूर्ण
पूर्ण


/* mix 2*law -> law */
u8 dsp_audio_mix_law[65536];

/******************************************************
 * generate mix table to mix two law samples पूर्णांकo one *
 ******************************************************/

व्योम
dsp_audio_generate_mix_table(व्योम)
अणु
	पूर्णांक i, j;
	s32 sample;

	i = 0;
	जबतक (i < 256) अणु
		j = 0;
		जबतक (j < 256) अणु
			sample = dsp_audio_law_to_s32[i];
			sample += dsp_audio_law_to_s32[j];
			अगर (sample > 32767)
				sample = 32767;
			अगर (sample < -32768)
				sample = -32768;
			dsp_audio_mix_law[(i << 8) | j] =
				dsp_audio_s16_to_law[sample & 0xffff];
			j++;
		पूर्ण
		i++;
	पूर्ण
पूर्ण


/*************************************
 * generate dअगरferent volume changes *
 *************************************/

अटल u8 dsp_audio_reduce8[256];
अटल u8 dsp_audio_reduce7[256];
अटल u8 dsp_audio_reduce6[256];
अटल u8 dsp_audio_reduce5[256];
अटल u8 dsp_audio_reduce4[256];
अटल u8 dsp_audio_reduce3[256];
अटल u8 dsp_audio_reduce2[256];
अटल u8 dsp_audio_reduce1[256];
अटल u8 dsp_audio_increase1[256];
अटल u8 dsp_audio_increase2[256];
अटल u8 dsp_audio_increase3[256];
अटल u8 dsp_audio_increase4[256];
अटल u8 dsp_audio_increase5[256];
अटल u8 dsp_audio_increase6[256];
अटल u8 dsp_audio_increase7[256];
अटल u8 dsp_audio_increase8[256];

अटल u8 *dsp_audio_volume_change[16] = अणु
	dsp_audio_reduce8,
	dsp_audio_reduce7,
	dsp_audio_reduce6,
	dsp_audio_reduce5,
	dsp_audio_reduce4,
	dsp_audio_reduce3,
	dsp_audio_reduce2,
	dsp_audio_reduce1,
	dsp_audio_increase1,
	dsp_audio_increase2,
	dsp_audio_increase3,
	dsp_audio_increase4,
	dsp_audio_increase5,
	dsp_audio_increase6,
	dsp_audio_increase7,
	dsp_audio_increase8,
पूर्ण;

व्योम
dsp_audio_generate_volume_changes(व्योम)
अणु
	रेजिस्टर s32 sample;
	पूर्णांक i;
	पूर्णांक num[]   = अणु 110, 125, 150, 175, 200, 300, 400, 500 पूर्ण;
	पूर्णांक dक्रमागत[] = अणु 100, 100, 100, 100, 100, 100, 100, 100 पूर्ण;

	i = 0;
	जबतक (i < 256) अणु
		dsp_audio_reduce8[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[7] / num[7]) & 0xffff];
		dsp_audio_reduce7[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[6] / num[6]) & 0xffff];
		dsp_audio_reduce6[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[5] / num[5]) & 0xffff];
		dsp_audio_reduce5[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[4] / num[4]) & 0xffff];
		dsp_audio_reduce4[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[3] / num[3]) & 0xffff];
		dsp_audio_reduce3[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[2] / num[2]) & 0xffff];
		dsp_audio_reduce2[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[1] / num[1]) & 0xffff];
		dsp_audio_reduce1[i] = dsp_audio_s16_to_law[
			(dsp_audio_law_to_s32[i] * dक्रमागत[0] / num[0]) & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[0] / dक्रमागत[0];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase1[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[1] / dक्रमागत[1];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase2[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[2] / dक्रमागत[2];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase3[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[3] / dक्रमागत[3];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase4[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[4] / dक्रमागत[4];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase5[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[5] / dक्रमागत[5];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase6[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[6] / dक्रमागत[6];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase7[i] = dsp_audio_s16_to_law[sample & 0xffff];
		sample = dsp_audio_law_to_s32[i] * num[7] / dक्रमागत[7];
		अगर (sample < -32768)
			sample = -32768;
		अन्यथा अगर (sample > 32767)
			sample = 32767;
		dsp_audio_increase8[i] = dsp_audio_s16_to_law[sample & 0xffff];

		i++;
	पूर्ण
पूर्ण


/**************************************
 * change the volume of the given skb *
 **************************************/

/* this is a helper function क्रम changing volume of skb. the range may be
 * -8 to 8, which is a shअगरt to the घातer of 2. 0 == no volume, 3 == volume*8
 */
व्योम
dsp_change_volume(काष्ठा sk_buff *skb, पूर्णांक volume)
अणु
	u8 *volume_change;
	पूर्णांक i, ii;
	u8 *p;
	पूर्णांक shअगरt;

	अगर (volume == 0)
		वापस;

	/* get correct conversion table */
	अगर (volume < 0) अणु
		shअगरt = volume + 8;
		अगर (shअगरt < 0)
			shअगरt = 0;
	पूर्ण अन्यथा अणु
		shअगरt = volume + 7;
		अगर (shअगरt > 15)
			shअगरt = 15;
	पूर्ण
	volume_change = dsp_audio_volume_change[shअगरt];
	i = 0;
	ii = skb->len;
	p = skb->data;
	/* change volume */
	जबतक (i < ii) अणु
		*p = volume_change[*p];
		p++;
		i++;
	पूर्ण
पूर्ण
