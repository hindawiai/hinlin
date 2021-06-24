<शैली गुरु>
/*
 * DTMF decoder.
 *
 * Copyright            by Andreas Eversberg (jolly@eversberg.eu)
 *			based on dअगरferent decoders such as ISDN4Linux
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#समावेश <linux/mISDNअगर.h>
#समावेश <linux/mISDNdsp.h>
#समावेश "core.h"
#समावेश "dsp.h"

#घोषणा NCOEFF            8     /* number of frequencies to be analyzed */

/* For DTMF recognition:
 * 2 * cos(2 * PI * k / N) precalculated क्रम all k
 */
अटल u64 cos2pik[NCOEFF] =
अणु
	/* k << 15 (source: hfc-4s/8s करोcumentation (www.colognechip.de)) */
	55960, 53912, 51402, 48438, 38146, 32650, 26170, 18630
पूर्ण;

/* digit matrix */
अटल अक्षर dपंचांगf_matrix[4][4] =
अणु
	अणु'1', '2', '3', 'A'पूर्ण,
	अणु'4', '5', '6', 'B'पूर्ण,
	अणु'7', '8', '9', 'C'पूर्ण,
	अणु'*', '0', '#', 'D'पूर्ण
पूर्ण;

/* dपंचांगf detection using goertzel algorithm
 * init function
 */
व्योम dsp_dपंचांगf_goertzel_init(काष्ठा dsp *dsp)
अणु
	dsp->dपंचांगf.size = 0;
	dsp->dपंचांगf.lastwhat = '\0';
	dsp->dपंचांगf.lastdigit = '\0';
	dsp->dपंचांगf.count = 0;
पूर्ण

/* check क्रम hardware or software features
 */
व्योम dsp_dपंचांगf_hardware(काष्ठा dsp *dsp)
अणु
	पूर्णांक hardware = 1;

	अगर (!dsp->dपंचांगf.enable)
		वापस;

	अगर (!dsp->features.hfc_dपंचांगf)
		hardware = 0;

	/* check क्रम volume change */
	अगर (dsp->tx_volume) अणु
		अगर (dsp_debug & DEBUG_DSP_DTMF)
			prपूर्णांकk(KERN_DEBUG "%s dsp %s cannot do hardware DTMF, "
			       "because tx_volume is changed\n",
			       __func__, dsp->name);
		hardware = 0;
	पूर्ण
	अगर (dsp->rx_volume) अणु
		अगर (dsp_debug & DEBUG_DSP_DTMF)
			prपूर्णांकk(KERN_DEBUG "%s dsp %s cannot do hardware DTMF, "
			       "because rx_volume is changed\n",
			       __func__, dsp->name);
		hardware = 0;
	पूर्ण
	/* check अगर encryption is enabled */
	अगर (dsp->bf_enable) अणु
		अगर (dsp_debug & DEBUG_DSP_DTMF)
			prपूर्णांकk(KERN_DEBUG "%s dsp %s cannot do hardware DTMF, "
			       "because encryption is enabled\n",
			       __func__, dsp->name);
		hardware = 0;
	पूर्ण
	/* check अगर pipeline exists */
	अगर (dsp->pipeline.inuse) अणु
		अगर (dsp_debug & DEBUG_DSP_DTMF)
			prपूर्णांकk(KERN_DEBUG "%s dsp %s cannot do hardware DTMF, "
			       "because pipeline exists.\n",
			       __func__, dsp->name);
		hardware = 0;
	पूर्ण

	dsp->dपंचांगf.hardware = hardware;
	dsp->dपंचांगf.software = !hardware;
पूर्ण


/*************************************************************
 * calculate the coefficients of the given sample and decode *
 *************************************************************/

/* the given sample is decoded. अगर the sample is not दीर्घ enough क्रम a
 * complete frame, the decoding is finished and जारीd with the next
 * call of this function.
 *
 * the algorithm is very good क्रम detection with a minimum of errors. i
 * tested it allot. it even works with very लघु tones (40ms). the only
 * disadvantage is, that it करोesn't work good with dअगरferent volumes of both
 * tones. this will happen, अगर accoustically coupled dialers are used.
 * it someबार detects tones during speech, which is normal क्रम decoders.
 * use sequences to given commands during calls.
 *
 * dपंचांगf - poपूर्णांकs to a काष्ठाure of the current dपंचांगf state
 * spl and len - the sample
 * fmt - 0 = alaw, 1 = ulaw, 2 = coefficients from HFC DTMF hw-decoder
 */

u8
*dsp_dपंचांगf_goertzel_decode(काष्ठा dsp *dsp, u8 *data, पूर्णांक len, पूर्णांक fmt)
अणु
	u8 what;
	पूर्णांक size;
	चिन्हित लघु *buf;
	s32 sk, sk1, sk2;
	पूर्णांक k, n, i;
	s32 *hfccoeff;
	s32 result[NCOEFF], tresh, treshl;
	पूर्णांक lowgroup, highgroup;
	s64 cos2pik_;

	dsp->dपंचांगf.digits[0] = '\0';

	/* Note: The function will loop until the buffer has not enough samples
	 * left to decode a full frame.
	 */
again:
	/* convert samples */
	size = dsp->dपंचांगf.size;
	buf = dsp->dपंचांगf.buffer;
	चयन (fmt) अणु
	हाल 0: /* alaw */
	हाल 1: /* ulaw */
		जबतक (size < DSP_DTMF_NPOINTS && len) अणु
			buf[size++] = dsp_audio_law_to_s32[*data++];
			len--;
		पूर्ण
		अवरोध;

	हाल 2: /* HFC coefficients */
	शेष:
		अगर (len < 64) अणु
			अगर (len > 0)
				prपूर्णांकk(KERN_ERR "%s: coefficients have invalid "
				       "size. (is=%d < must=%d)\n",
				       __func__, len, 64);
			वापस dsp->dपंचांगf.digits;
		पूर्ण
		hfccoeff = (s32 *)data;
		क्रम (k = 0; k < NCOEFF; k++) अणु
			sk2 = (*hfccoeff++) >> 4;
			sk = (*hfccoeff++) >> 4;
			अगर (sk > 32767 || sk < -32767 || sk2 > 32767
			    || sk2 < -32767)
				prपूर्णांकk(KERN_WARNING
				       "DTMF-Detection overflow\n");
			/* compute |X(k)|**2 */
			result[k] =
				(sk * sk) -
				(((cos2pik[k] * sk) >> 15) * sk2) +
				(sk2 * sk2);
		पूर्ण
		data += 64;
		len -= 64;
		जाओ coefficients;
		अवरोध;
	पूर्ण
	dsp->dपंचांगf.size = size;

	अगर (size < DSP_DTMF_NPOINTS)
		वापस dsp->dपंचांगf.digits;

	dsp->dपंचांगf.size = 0;

	/* now we have a full buffer of चिन्हित दीर्घ samples - we करो goertzel */
	क्रम (k = 0; k < NCOEFF; k++) अणु
		sk = 0;
		sk1 = 0;
		sk2 = 0;
		buf = dsp->dपंचांगf.buffer;
		cos2pik_ = cos2pik[k];
		क्रम (n = 0; n < DSP_DTMF_NPOINTS; n++) अणु
			sk = ((cos2pik_ * sk1) >> 15) - sk2 + (*buf++);
			sk2 = sk1;
			sk1 = sk;
		पूर्ण
		sk >>= 8;
		sk2 >>= 8;
		अगर (sk > 32767 || sk < -32767 || sk2 > 32767 || sk2 < -32767)
			prपूर्णांकk(KERN_WARNING "DTMF-Detection overflow\n");
		/* compute |X(k)|**2 */
		result[k] =
			(sk * sk) -
			(((cos2pik[k] * sk) >> 15) * sk2) +
			(sk2 * sk2);
	पूर्ण

	/* our (squared) coefficients have been calculated, we need to process
	 * them.
	 */
coefficients:
	tresh = 0;
	क्रम (i = 0; i < NCOEFF; i++) अणु
		अगर (result[i] < 0)
			result[i] = 0;
		अगर (result[i] > dsp->dपंचांगf.treshold) अणु
			अगर (result[i] > tresh)
				tresh = result[i];
		पूर्ण
	पूर्ण

	अगर (tresh == 0) अणु
		what = 0;
		जाओ storedigit;
	पूर्ण

	अगर (dsp_debug & DEBUG_DSP_DTMFCOEFF) अणु
		s32 tresh_100 = tresh/100;

		अगर (tresh_100 == 0) अणु
			tresh_100 = 1;
			prपूर्णांकk(KERN_DEBUG
				"tresh(%d) too small set tresh/100 to 1\n",
				tresh);
		पूर्ण
		prपूर्णांकk(KERN_DEBUG "a %3d %3d %3d %3d %3d %3d %3d %3d"
		       " tr:%3d r %3d %3d %3d %3d %3d %3d %3d %3d\n",
		       result[0] / 10000, result[1] / 10000, result[2] / 10000,
		       result[3] / 10000, result[4] / 10000, result[5] / 10000,
		       result[6] / 10000, result[7] / 10000, tresh / 10000,
		       result[0] / (tresh_100), result[1] / (tresh_100),
		       result[2] / (tresh_100), result[3] / (tresh_100),
		       result[4] / (tresh_100), result[5] / (tresh_100),
		       result[6] / (tresh_100), result[7] / (tresh_100));
	पूर्ण

	/* calc digit (lowgroup/highgroup) */
	lowgroup = -1;
	highgroup = -1;
	treshl = tresh >> 3;  /* tones which are not on, must be below 9 dB */
	tresh = tresh >> 2;  /* touchtones must match within 6 dB */
	क्रम (i = 0; i < NCOEFF; i++) अणु
		अगर (result[i] < treshl)
			जारी;  /* ignore */
		अगर (result[i] < tresh) अणु
			lowgroup = -1;
			highgroup = -1;
			अवरोध;  /* noise in between */
		पूर्ण
		/* good level found. This is allowed only one समय per group */
		अगर (i < NCOEFF / 2) अणु
			/* lowgroup */
			अगर (lowgroup >= 0) अणु
				/* Bad. Another tone found. */
				lowgroup = -1;
				अवरोध;
			पूर्ण अन्यथा
				lowgroup = i;
		पूर्ण अन्यथा अणु
			/* higroup */
			अगर (highgroup >= 0) अणु
				/* Bad. Another tone found. */
				highgroup = -1;
				अवरोध;
			पूर्ण अन्यथा
				highgroup = i - (NCOEFF / 2);
		पूर्ण
	पूर्ण

	/* get digit or null */
	what = 0;
	अगर (lowgroup >= 0 && highgroup >= 0)
		what = dपंचांगf_matrix[lowgroup][highgroup];

storedigit:
	अगर (what && (dsp_debug & DEBUG_DSP_DTMF))
		prपूर्णांकk(KERN_DEBUG "DTMF what: %c\n", what);

	अगर (dsp->dपंचांगf.lastwhat != what)
		dsp->dपंचांगf.count = 0;

	/* the tone (or no tone) must reमुख्य 3 बार without change */
	अगर (dsp->dपंचांगf.count == 2) अणु
		अगर (dsp->dपंचांगf.lastdigit != what) अणु
			dsp->dपंचांगf.lastdigit = what;
			अगर (what) अणु
				अगर (dsp_debug & DEBUG_DSP_DTMF)
					prपूर्णांकk(KERN_DEBUG "DTMF digit: %c\n",
					       what);
				अगर ((म_माप(dsp->dपंचांगf.digits) + 1)
				    < माप(dsp->dपंचांगf.digits)) अणु
					dsp->dपंचांगf.digits[म_माप(
							dsp->dपंचांगf.digits) + 1] = '\0';
					dsp->dपंचांगf.digits[म_माप(
							dsp->dपंचांगf.digits)] = what;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		dsp->dपंचांगf.count++;

	dsp->dपंचांगf.lastwhat = what;

	जाओ again;
पूर्ण
