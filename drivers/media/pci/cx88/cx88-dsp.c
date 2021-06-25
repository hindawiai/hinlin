<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Stereo and SAP detection क्रम cx88
 *
 *  Copyright (c) 2009 Marton Balपूर्णांक <cus@fazekas.hu>
 */

#समावेश "cx88.h"
#समावेश "cx88-reg.h"

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <यंत्र/भाग64.h>

#घोषणा INT_PI			((s32)(3.141592653589 * 32768.0))

#घोषणा compat_reमुख्यder(a, b) \
	 ((भग्न)(((s32)((a) * 100)) % ((s32)((b) * 100))) / 100.0)

#घोषणा baseband_freq(carrier, srate, tone) ((s32)( \
	 (compat_reमुख्यder(carrier + tone, srate)) / srate * 2 * INT_PI))

/*
 * We calculate the baseband frequencies of the carrier and the pilot tones
 * based on the the sampling rate of the audio rds fअगरo.
 */

#घोषणा FREQ_A2_CARRIER         baseband_freq(54687.5, 2689.36, 0.0)
#घोषणा FREQ_A2_DUAL            baseband_freq(54687.5, 2689.36, 274.1)
#घोषणा FREQ_A2_STEREO          baseband_freq(54687.5, 2689.36, 117.5)

/*
 * The frequencies below are from the reference driver. They probably need
 * further adjusपंचांगents, because they are not tested at all. You may even need
 * to play a bit with the रेजिस्टरs of the chip to select the proper संकेत
 * क्रम the input of the audio rds fअगरo, and measure it's sampling rate to
 * calculate the proper baseband frequencies...
 */

#घोषणा FREQ_A2M_CARRIER	((s32)(2.114516 * 32768.0))
#घोषणा FREQ_A2M_DUAL		((s32)(2.754916 * 32768.0))
#घोषणा FREQ_A2M_STEREO		((s32)(2.462326 * 32768.0))

#घोषणा FREQ_EIAJ_CARRIER	((s32)(1.963495 * 32768.0)) /* 5pi/8  */
#घोषणा FREQ_EIAJ_DUAL		((s32)(2.562118 * 32768.0))
#घोषणा FREQ_EIAJ_STEREO	((s32)(2.601053 * 32768.0))

#घोषणा FREQ_BTSC_DUAL		((s32)(1.963495 * 32768.0)) /* 5pi/8  */
#घोषणा FREQ_BTSC_DUAL_REF	((s32)(1.374446 * 32768.0)) /* 7pi/16 */

#घोषणा FREQ_BTSC_SAP		((s32)(2.471532 * 32768.0))
#घोषणा FREQ_BTSC_SAP_REF	((s32)(1.730072 * 32768.0))

/* The spectrum of the संकेत should be empty between these frequencies. */
#घोषणा FREQ_NOISE_START	((s32)(0.100000 * 32768.0))
#घोषणा FREQ_NOISE_END		((s32)(1.200000 * 32768.0))

अटल अचिन्हित पूर्णांक dsp_debug;
module_param(dsp_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(dsp_debug, "enable audio dsp debug messages");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (dsp_debug >= level)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: dsp:" fmt),		\
			__func__, ##arg);				\
पूर्ण जबतक (0)

अटल s32 पूर्णांक_cos(u32 x)
अणु
	u32 t2, t4, t6, t8;
	s32 ret;
	u16 period = x / INT_PI;

	अगर (period % 2)
		वापस -पूर्णांक_cos(x - INT_PI);
	x = x % INT_PI;
	अगर (x > INT_PI / 2)
		वापस -पूर्णांक_cos(INT_PI / 2 - (x % (INT_PI / 2)));
	/*
	 * Now x is between 0 and INT_PI/2.
	 * To calculate cos(x) we use it's Taylor polinom.
	 */
	t2 = x * x / 32768 / 2;
	t4 = t2 * x / 32768 * x / 32768 / 3 / 4;
	t6 = t4 * x / 32768 * x / 32768 / 5 / 6;
	t8 = t6 * x / 32768 * x / 32768 / 7 / 8;
	ret = 32768 - t2 + t4 - t6 + t8;
	वापस ret;
पूर्ण

अटल u32 पूर्णांक_goertzel(s16 x[], u32 N, u32 freq)
अणु
	/*
	 * We use the Goertzel algorithm to determine the घातer of the
	 * given frequency in the संकेत
	 */
	s32 s_prev = 0;
	s32 s_prev2 = 0;
	s32 coeff = 2 * पूर्णांक_cos(freq);
	u32 i;

	u64 पंचांगp;
	u32 भागisor;

	क्रम (i = 0; i < N; i++) अणु
		s32 s = x[i] + ((s64)coeff * s_prev / 32768) - s_prev2;

		s_prev2 = s_prev;
		s_prev = s;
	पूर्ण

	पंचांगp = (s64)s_prev2 * s_prev2 + (s64)s_prev * s_prev -
		      (s64)coeff * s_prev2 * s_prev / 32768;

	/*
	 * XXX: N must be low enough so that N*N fits in s32.
	 * Else we need two भागisions.
	 */
	भागisor = N * N;
	करो_भाग(पंचांगp, भागisor);

	वापस (u32)पंचांगp;
पूर्ण

अटल u32 freq_magnitude(s16 x[], u32 N, u32 freq)
अणु
	u32 sum = पूर्णांक_goertzel(x, N, freq);

	वापस (u32)पूर्णांक_वर्ग_मूल(sum);
पूर्ण

अटल u32 noise_magnitude(s16 x[], u32 N, u32 freq_start, u32 freq_end)
अणु
	पूर्णांक i;
	u32 sum = 0;
	u32 freq_step;
	पूर्णांक samples = 5;

	अगर (N > 192) अणु
		/* The last 192 samples are enough क्रम noise detection */
		x += (N - 192);
		N = 192;
	पूर्ण

	freq_step = (freq_end - freq_start) / (samples - 1);

	क्रम (i = 0; i < samples; i++) अणु
		sum += पूर्णांक_goertzel(x, N, freq_start);
		freq_start += freq_step;
	पूर्ण

	वापस (u32)पूर्णांक_वर्ग_मूल(sum / samples);
पूर्ण

अटल s32 detect_a2_a2m_eiaj(काष्ठा cx88_core *core, s16 x[], u32 N)
अणु
	s32 carrier, stereo, dual, noise;
	s32 carrier_freq, stereo_freq, dual_freq;
	s32 ret;

	चयन (core->tvaudio) अणु
	हाल WW_BG:
	हाल WW_DK:
		carrier_freq = FREQ_A2_CARRIER;
		stereo_freq = FREQ_A2_STEREO;
		dual_freq = FREQ_A2_DUAL;
		अवरोध;
	हाल WW_M:
		carrier_freq = FREQ_A2M_CARRIER;
		stereo_freq = FREQ_A2M_STEREO;
		dual_freq = FREQ_A2M_DUAL;
		अवरोध;
	हाल WW_EIAJ:
		carrier_freq = FREQ_EIAJ_CARRIER;
		stereo_freq = FREQ_EIAJ_STEREO;
		dual_freq = FREQ_EIAJ_DUAL;
		अवरोध;
	शेष:
		pr_warn("unsupported audio mode %d for %s\n",
			core->tvaudio, __func__);
		वापस UNSET;
	पूर्ण

	carrier = freq_magnitude(x, N, carrier_freq);
	stereo  = freq_magnitude(x, N, stereo_freq);
	dual    = freq_magnitude(x, N, dual_freq);
	noise   = noise_magnitude(x, N, FREQ_NOISE_START, FREQ_NOISE_END);

	dprपूर्णांकk(1,
		"detect a2/a2m/eiaj: carrier=%d, stereo=%d, dual=%d, noise=%d\n",
		carrier, stereo, dual, noise);

	अगर (stereo > dual)
		ret = V4L2_TUNER_SUB_STEREO;
	अन्यथा
		ret = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;

	अगर (core->tvaudio == WW_EIAJ) अणु
		/* EIAJ checks may need adjusपंचांगents */
		अगर ((carrier > max(stereo, dual) * 2) &&
		    (carrier < max(stereo, dual) * 6) &&
		    (carrier > 20 && carrier < 200) &&
		    (max(stereo, dual) > min(stereo, dual))) अणु
			/*
			 * For EIAJ the carrier is always present,
			 * so we probably करोn't need noise detection
			 */
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((carrier > max(stereo, dual) * 2) &&
		    (carrier < max(stereo, dual) * 8) &&
		    (carrier > 20 && carrier < 200) &&
		    (noise < 10) &&
		    (max(stereo, dual) > min(stereo, dual) * 2)) अणु
			वापस ret;
		पूर्ण
	पूर्ण
	वापस V4L2_TUNER_SUB_MONO;
पूर्ण

अटल s32 detect_btsc(काष्ठा cx88_core *core, s16 x[], u32 N)
अणु
	s32 sap_ref = freq_magnitude(x, N, FREQ_BTSC_SAP_REF);
	s32 sap = freq_magnitude(x, N, FREQ_BTSC_SAP);
	s32 dual_ref = freq_magnitude(x, N, FREQ_BTSC_DUAL_REF);
	s32 dual = freq_magnitude(x, N, FREQ_BTSC_DUAL);

	dprपूर्णांकk(1, "detect btsc: dual_ref=%d, dual=%d, sap_ref=%d, sap=%d\n",
		dual_ref, dual, sap_ref, sap);
	/* FIXME: Currently not supported */
	वापस UNSET;
पूर्ण

अटल s16 *पढ़ो_rds_samples(काष्ठा cx88_core *core, u32 *N)
अणु
	स्थिर काष्ठा sram_channel *srch = &cx88_sram_channels[SRAM_CH27];
	s16 *samples;

	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक bpl = srch->fअगरo_size / AUD_RDS_LINES;
	अचिन्हित पूर्णांक spl = bpl / 4;
	अचिन्हित पूर्णांक sample_count = spl * (AUD_RDS_LINES - 1);

	u32 current_address = cx_पढ़ो(srch->ptr1_reg);
	u32 offset = (current_address - srch->fअगरo_start + bpl);

	dprपूर्णांकk(1,
		"read RDS samples: current_address=%08x (offset=%08x), sample_count=%d, aud_intstat=%08x\n",
		current_address,
		current_address - srch->fअगरo_start, sample_count,
		cx_पढ़ो(MO_AUD_INTSTAT));
	samples = kदो_स्मृति_array(sample_count, माप(*samples), GFP_KERNEL);
	अगर (!samples)
		वापस शून्य;

	*N = sample_count;

	क्रम (i = 0; i < sample_count; i++)  अणु
		offset = offset % (AUD_RDS_LINES * bpl);
		samples[i] = cx_पढ़ो(srch->fअगरo_start + offset);
		offset += 4;
	पूर्ण

	dprपूर्णांकk(2, "RDS samples dump: %*ph\n", sample_count, samples);

	वापस samples;
पूर्ण

s32 cx88_dsp_detect_stereo_sap(काष्ठा cx88_core *core)
अणु
	s16 *samples;
	u32 N = 0;
	s32 ret = UNSET;

	/* If audio RDS fअगरo is disabled, we can't पढ़ो the samples */
	अगर (!(cx_पढ़ो(MO_AUD_DMACNTRL) & 0x04))
		वापस ret;
	अगर (!(cx_पढ़ो(AUD_CTL) & EN_FMRADIO_EN_RDS))
		वापस ret;

	/* Wait at least 500 ms after an audio standard change */
	अगर (समय_beक्रमe(jअगरfies, core->last_change + msecs_to_jअगरfies(500)))
		वापस ret;

	samples = पढ़ो_rds_samples(core, &N);

	अगर (!samples)
		वापस ret;

	चयन (core->tvaudio) अणु
	हाल WW_BG:
	हाल WW_DK:
	हाल WW_EIAJ:
	हाल WW_M:
		ret = detect_a2_a2m_eiaj(core, samples, N);
		अवरोध;
	हाल WW_BTSC:
		ret = detect_btsc(core, samples, N);
		अवरोध;
	हाल WW_NONE:
	हाल WW_I:
	हाल WW_L:
	हाल WW_I2SPT:
	हाल WW_FM:
	हाल WW_I2SADC:
		अवरोध;
	पूर्ण

	kमुक्त(samples);

	अगर (ret != UNSET)
		dprपूर्णांकk(1, "stereo/sap detection result:%s%s%s\n",
			(ret & V4L2_TUNER_SUB_MONO) ? " mono" : "",
			(ret & V4L2_TUNER_SUB_STEREO) ? " stereo" : "",
			(ret & V4L2_TUNER_SUB_LANG2) ? " dual" : "");

	वापस ret;
पूर्ण
EXPORT_SYMBOL(cx88_dsp_detect_stereo_sap);

