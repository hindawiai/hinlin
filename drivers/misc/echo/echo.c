<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SpanDSP - a series of DSP components क्रम telephony
 *
 * echo.c - A line echo canceller.  This code is being developed
 *          against and partially complies with G168.
 *
 * Written by Steve Underwood <steveu@coppice.org>
 *         and David Rowe <david_at_rowetel_करोt_com>
 *
 * Copyright (C) 2001, 2003 Steve Underwood, 2007 David Rowe
 *
 * Based on a bit from here, a bit from there, eye of toad, ear of
 * bat, 15 years of failed attempts by David and a few fried brain
 * cells.
 *
 * All rights reserved.
 */

/*! \पile */

/* Implementation Notes
   David Rowe
   April 2007

   This code started lअगरe as Steve's NLMS algorithm with a tap
   rotation algorithm to handle भागergence during द्विगुन talk.  I
   added a Geigel Double Talk Detector (DTD) [2] and perक्रमmed some
   G168 tests.  However I had trouble meeting the G168 requirements,
   especially क्रम द्विगुन talk - there were always हालs where my DTD
   failed, क्रम example where near end speech was under the 6dB
   threshold required क्रम declaring द्विगुन talk.

   So I tried a two path algorithm [1], which has so far given better
   results.  The original tap rotation/Geigel algorithm is available
   in SVN http://svn.rowetel.com/software/oslec/tags/beक्रमe_16bit.
   It's probably possible to make it work अगर some one wants to put some
   serious work पूर्णांकo it.

   At present no special treaपंचांगent is provided क्रम tones, which
   generally cause NLMS algorithms to भागerge.  Initial runs of a
   subset of the G168 tests क्रम tones (e.g ./echo_test 6) show the
   current algorithm is passing OK, which is kind of surprising.  The
   full set of tests needs to be perक्रमmed to confirm this result.

   One other पूर्णांकeresting change is that I have managed to get the NLMS
   code to work with 16 bit coefficients, rather than the original 32
   bit coefficents.  This reduces the MIPs and storage required.
   I evaulated the 16 bit port using g168_tests.sh and listening tests
   on 4 real-world samples.

   I also attempted the implementation of a block based NLMS update
   [2] but although this passes g168_tests.sh it didn't converge well
   on the real-world samples.  I have no idea why, perhaps a scaling
   problem.  The block based code is also available in SVN
   http://svn.rowetel.com/software/oslec/tags/beक्रमe_16bit.  If this
   code can be debugged, it will lead to further reduction in MIPS, as
   the block update code maps nicely onto DSP inकाष्ठाion sets (it's a
   करोt product) compared to the current sample-by-sample update.

   Steve also has some nice notes on echo cancellers in echo.h

   References:

   [1] Ochiai, Areseki, and Ogihara, "Echo Canceller with Two Echo
       Path Models", IEEE Transactions on communications, COM-25,
       No. 6, June
       1977.
       https://www.rowetel.com/images/echo/dual_path_paper.pdf

   [2] The classic, very useful paper that tells you how to
       actually build a real world echo canceller:
	 Messerschmitt, Hedberg, Cole, Haoui, Winship, "Digital Voice
	 Echo Canceller with a TMS320020,
	 https://www.rowetel.com/images/echo/spra129.pdf

   [3] I have written a series of blog posts on this work, here is
       Part 1: http://www.rowetel.com/blog/?p=18

   [4] The source code http://svn.rowetel.com/software/oslec/

   [5] A nice reference on LMS filters:
	 https://en.wikipedia.org/wiki/Least_mean_squares_filter

   Credits:

   Thanks to Steve Underwood, Jean-Marc Valin, and Ramakrishnan
   Muthukrishnan क्रम their suggestions and email discussions.  Thanks
   also to those people who collected echo samples क्रम me such as
   Mark, Pawel, and Pavel.
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "echo.h"

#घोषणा MIN_TX_POWER_FOR_ADAPTION	64
#घोषणा MIN_RX_POWER_FOR_ADAPTION	64
#घोषणा DTD_HANGOVER			600	/* 600 samples, or 75ms     */
#घोषणा DC_LOG2BETA			3	/* log2() of DC filter Beta */

/* adapting coeffs using the traditional stochastic descent (N)LMS algorithm */

अटल अंतरभूत व्योम lms_adapt_bg(काष्ठा oslec_state *ec, पूर्णांक clean, पूर्णांक shअगरt)
अणु
	पूर्णांक i;

	पूर्णांक offset1;
	पूर्णांक offset2;
	पूर्णांक factor;
	पूर्णांक exp;

	अगर (shअगरt > 0)
		factor = clean << shअगरt;
	अन्यथा
		factor = clean >> -shअगरt;

	/* Update the FIR taps */

	offset2 = ec->curr_pos;
	offset1 = ec->taps - offset2;

	क्रम (i = ec->taps - 1; i >= offset1; i--) अणु
		exp = (ec->fir_state_bg.history[i - offset1] * factor);
		ec->fir_taps16[1][i] += (पूर्णांक16_t) ((exp + (1 << 14)) >> 15);
	पूर्ण
	क्रम (; i >= 0; i--) अणु
		exp = (ec->fir_state_bg.history[i + offset2] * factor);
		ec->fir_taps16[1][i] += (पूर्णांक16_t) ((exp + (1 << 14)) >> 15);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक top_bit(अचिन्हित पूर्णांक bits)
अणु
	अगर (bits == 0)
		वापस -1;
	अन्यथा
		वापस (पूर्णांक)fls((पूर्णांक32_t) bits) - 1;
पूर्ण

काष्ठा oslec_state *oslec_create(पूर्णांक len, पूर्णांक adaption_mode)
अणु
	काष्ठा oslec_state *ec;
	पूर्णांक i;
	स्थिर पूर्णांक16_t *history;

	ec = kzalloc(माप(*ec), GFP_KERNEL);
	अगर (!ec)
		वापस शून्य;

	ec->taps = len;
	ec->log2taps = top_bit(len);
	ec->curr_pos = ec->taps - 1;

	ec->fir_taps16[0] =
	    kसुस्मृति(ec->taps, माप(पूर्णांक16_t), GFP_KERNEL);
	अगर (!ec->fir_taps16[0])
		जाओ error_oom_0;

	ec->fir_taps16[1] =
	    kसुस्मृति(ec->taps, माप(पूर्णांक16_t), GFP_KERNEL);
	अगर (!ec->fir_taps16[1])
		जाओ error_oom_1;

	history = fir16_create(&ec->fir_state, ec->fir_taps16[0], ec->taps);
	अगर (!history)
		जाओ error_state;
	history = fir16_create(&ec->fir_state_bg, ec->fir_taps16[1], ec->taps);
	अगर (!history)
		जाओ error_state_bg;

	क्रम (i = 0; i < 5; i++)
		ec->xvtx[i] = ec->yvtx[i] = ec->xvrx[i] = ec->yvrx[i] = 0;

	ec->cng_level = 1000;
	oslec_adaption_mode(ec, adaption_mode);

	ec->snapshot = kसुस्मृति(ec->taps, माप(पूर्णांक16_t), GFP_KERNEL);
	अगर (!ec->snapshot)
		जाओ error_snap;

	ec->cond_met = 0;
	ec->pstates = 0;
	ec->ltxacc = ec->lrxacc = ec->lcleanacc = ec->lclean_bgacc = 0;
	ec->ltx = ec->lrx = ec->lclean = ec->lclean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->rx_1 = ec->rx_2 = 0;
	ec->lbgn = ec->lbgn_acc = 0;
	ec->lbgn_upper = 200;
	ec->lbgn_upper_acc = ec->lbgn_upper << 13;

	वापस ec;

error_snap:
	fir16_मुक्त(&ec->fir_state_bg);
error_state_bg:
	fir16_मुक्त(&ec->fir_state);
error_state:
	kमुक्त(ec->fir_taps16[1]);
error_oom_1:
	kमुक्त(ec->fir_taps16[0]);
error_oom_0:
	kमुक्त(ec);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(oslec_create);

व्योम oslec_मुक्त(काष्ठा oslec_state *ec)
अणु
	पूर्णांक i;

	fir16_मुक्त(&ec->fir_state);
	fir16_मुक्त(&ec->fir_state_bg);
	क्रम (i = 0; i < 2; i++)
		kमुक्त(ec->fir_taps16[i]);
	kमुक्त(ec->snapshot);
	kमुक्त(ec);
पूर्ण
EXPORT_SYMBOL_GPL(oslec_मुक्त);

व्योम oslec_adaption_mode(काष्ठा oslec_state *ec, पूर्णांक adaption_mode)
अणु
	ec->adaption_mode = adaption_mode;
पूर्ण
EXPORT_SYMBOL_GPL(oslec_adaption_mode);

व्योम oslec_flush(काष्ठा oslec_state *ec)
अणु
	पूर्णांक i;

	ec->ltxacc = ec->lrxacc = ec->lcleanacc = ec->lclean_bgacc = 0;
	ec->ltx = ec->lrx = ec->lclean = ec->lclean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->rx_1 = ec->rx_2 = 0;

	ec->lbgn = ec->lbgn_acc = 0;
	ec->lbgn_upper = 200;
	ec->lbgn_upper_acc = ec->lbgn_upper << 13;

	ec->nonupdate_dwell = 0;

	fir16_flush(&ec->fir_state);
	fir16_flush(&ec->fir_state_bg);
	ec->fir_state.curr_pos = ec->taps - 1;
	ec->fir_state_bg.curr_pos = ec->taps - 1;
	क्रम (i = 0; i < 2; i++)
		स_रखो(ec->fir_taps16[i], 0, ec->taps * माप(पूर्णांक16_t));

	ec->curr_pos = ec->taps - 1;
	ec->pstates = 0;
पूर्ण
EXPORT_SYMBOL_GPL(oslec_flush);

व्योम oslec_snapshot(काष्ठा oslec_state *ec)
अणु
	स_नकल(ec->snapshot, ec->fir_taps16[0], ec->taps * माप(पूर्णांक16_t));
पूर्ण
EXPORT_SYMBOL_GPL(oslec_snapshot);

/* Dual Path Echo Canceller */

पूर्णांक16_t oslec_update(काष्ठा oslec_state *ec, पूर्णांक16_t tx, पूर्णांक16_t rx)
अणु
	पूर्णांक32_t echo_value;
	पूर्णांक clean_bg;
	पूर्णांक पंचांगp;
	पूर्णांक पंचांगp1;

	/*
	 * Input scaling was found be required to prevent problems when tx
	 * starts clipping.  Another possible way to handle this would be the
	 * filter coefficent scaling.
	 */

	ec->tx = tx;
	ec->rx = rx;
	tx >>= 1;
	rx >>= 1;

	/*
	 * Filter DC, 3dB poपूर्णांक is 160Hz (I think), note 32 bit precision
	 * required otherwise values करो not track करोwn to 0. Zero at DC, Pole
	 * at (1-Beta) on real axis.  Some chip sets (like Si द_असल) करोn't
	 * need this, but something like a $10 X100P card करोes.  Any DC really
	 * slows करोwn convergence.
	 *
	 * Note: हटाओs some low frequency from the संकेत, this reduces the
	 * speech quality when listening to samples through headphones but may
	 * not be obvious through a telephone handset.
	 *
	 * Note that the 3dB frequency in radians is approx Beta, e.g. क्रम Beta
	 * = 2^(-3) = 0.125, 3dB freq is 0.125 rads = 159Hz.
	 */

	अगर (ec->adaption_mode & ECHO_CAN_USE_RX_HPF) अणु
		पंचांगp = rx << 15;

		/*
		 * Make sure the gain of the HPF is 1.0. This can still
		 * saturate a little under impulse conditions, and it might
		 * roll to 32768 and need clipping on sustained peak level
		 * संकेतs. However, the scale of such clipping is small, and
		 * the error due to any saturation should not markedly affect
		 * the करोwnstream processing.
		 */
		पंचांगp -= (पंचांगp >> 4);

		ec->rx_1 += -(ec->rx_1 >> DC_LOG2BETA) + पंचांगp - ec->rx_2;

		/*
		 * hard limit filter to prevent clipping.  Note that at this
		 * stage rx should be limited to +/- 16383 due to right shअगरt
		 * above
		 */
		पंचांगp1 = ec->rx_1 >> 15;
		अगर (पंचांगp1 > 16383)
			पंचांगp1 = 16383;
		अगर (पंचांगp1 < -16383)
			पंचांगp1 = -16383;
		rx = पंचांगp1;
		ec->rx_2 = पंचांगp;
	पूर्ण

	/* Block average of घातer in the filter states.  Used क्रम
	   adaption घातer calculation. */

	अणु
		पूर्णांक new, old;

		/* efficient "out with the old and in with the new" algorithm so
		   we करोn't have to recalculate over the whole block of
		   samples. */
		new = (पूर्णांक)tx * (पूर्णांक)tx;
		old = (पूर्णांक)ec->fir_state.history[ec->fir_state.curr_pos] *
		    (पूर्णांक)ec->fir_state.history[ec->fir_state.curr_pos];
		ec->pstates +=
		    ((new - old) + (1 << (ec->log2taps - 1))) >> ec->log2taps;
		अगर (ec->pstates < 0)
			ec->pstates = 0;
	पूर्ण

	/* Calculate लघु term average levels using simple single pole IIRs */

	ec->ltxacc += असल(tx) - ec->ltx;
	ec->ltx = (ec->ltxacc + (1 << 4)) >> 5;
	ec->lrxacc += असल(rx) - ec->lrx;
	ec->lrx = (ec->lrxacc + (1 << 4)) >> 5;

	/* Foreground filter */

	ec->fir_state.coeffs = ec->fir_taps16[0];
	echo_value = fir16(&ec->fir_state, tx);
	ec->clean = rx - echo_value;
	ec->lcleanacc += असल(ec->clean) - ec->lclean;
	ec->lclean = (ec->lcleanacc + (1 << 4)) >> 5;

	/* Background filter */

	echo_value = fir16(&ec->fir_state_bg, tx);
	clean_bg = rx - echo_value;
	ec->lclean_bgacc += असल(clean_bg) - ec->lclean_bg;
	ec->lclean_bg = (ec->lclean_bgacc + (1 << 4)) >> 5;

	/* Background Filter adaption */

	/* Almost always adap bg filter, just simple DT and energy
	   detection to minimise adaption in हालs of strong द्विगुन talk.
	   However this is not critical क्रम the dual path algorithm.
	 */
	ec->factor = 0;
	ec->shअगरt = 0;
	अगर (!ec->nonupdate_dwell) अणु
		पूर्णांक p, logp, shअगरt;

		/* Determine:

		   f = Beta * clean_bg_rx/P ------ (1)

		   where P is the total घातer in the filter states.

		   The Boffins have shown that अगर we obey (1) we converge
		   quickly and aव्योम instability.

		   The correct factor f must be in Q30, as this is the fixed
		   poपूर्णांक क्रमmat required by the lms_adapt_bg() function,
		   thereक्रमe the scaled version of (1) is:

		   (2^30) * f  = (2^30) * Beta * clean_bg_rx/P
		   factor      = (2^30) * Beta * clean_bg_rx/P     ----- (2)

		   We have chosen Beta = 0.25 by experiment, so:

		   factor      = (2^30) * (2^-2) * clean_bg_rx/P

		   (30 - 2 - log2(P))
		   factor      = clean_bg_rx 2                     ----- (3)

		   To aव्योम a भागide we approximate log2(P) as top_bit(P),
		   which वापसs the position of the highest non-zero bit in
		   P.  This approximation पूर्णांकroduces an error as large as a
		   factor of 2, but the algorithm seems to handle it OK.

		   Come to think of it a भागide may not be a big deal on a
		   modern DSP, so its probably worth checking out the cycles
		   क्रम a भागide versus a top_bit() implementation.
		 */

		p = MIN_TX_POWER_FOR_ADAPTION + ec->pstates;
		logp = top_bit(p) + ec->log2taps;
		shअगरt = 30 - 2 - logp;
		ec->shअगरt = shअगरt;

		lms_adapt_bg(ec, clean_bg, shअगरt);
	पूर्ण

	/* very simple DTD to make sure we करोnt try and adapt with strong
	   near end speech */

	ec->adapt = 0;
	अगर ((ec->lrx > MIN_RX_POWER_FOR_ADAPTION) && (ec->lrx > ec->ltx))
		ec->nonupdate_dwell = DTD_HANGOVER;
	अगर (ec->nonupdate_dwell)
		ec->nonupdate_dwell--;

	/* Transfer logic */

	/* These conditions are from the dual path paper [1], I messed with
	   them a bit to improve perक्रमmance. */

	अगर ((ec->adaption_mode & ECHO_CAN_USE_ADAPTION) &&
	    (ec->nonupdate_dwell == 0) &&
	    /* (ec->Lclean_bg < 0.875*ec->Lclean) */
	    (8 * ec->lclean_bg < 7 * ec->lclean) &&
	    /* (ec->Lclean_bg < 0.125*ec->Ltx) */
	    (8 * ec->lclean_bg < ec->ltx)) अणु
		अगर (ec->cond_met == 6) अणु
			/*
			 * BG filter has had better results क्रम 6 consecutive
			 * samples
			 */
			ec->adapt = 1;
			स_नकल(ec->fir_taps16[0], ec->fir_taps16[1],
			       ec->taps * माप(पूर्णांक16_t));
		पूर्ण अन्यथा
			ec->cond_met++;
	पूर्ण अन्यथा
		ec->cond_met = 0;

	/* Non-Linear Processing */

	ec->clean_nlp = ec->clean;
	अगर (ec->adaption_mode & ECHO_CAN_USE_NLP) अणु
		/*
		 * Non-linear processor - a fancy way to say "zap small
		 * संकेतs, to aव्योम residual echo due to (uLaw/ALaw)
		 * non-linearity in the channel.".
		 */

		अगर ((16 * ec->lclean < ec->ltx)) अणु
			/*
			 * Our e/c has improved echo by at least 24 dB (each
			 * factor of 2 is 6dB, so 2*2*2*2=16 is the same as
			 * 6+6+6+6=24dB)
			 */
			अगर (ec->adaption_mode & ECHO_CAN_USE_CNG) अणु
				ec->cng_level = ec->lbgn;

				/*
				 * Very elementary comक्रमt noise generation.
				 * Just अक्रमom numbers rolled off very vaguely
				 * Hoth-like.  DR: This noise करोesn't sound
				 * quite right to me - I suspect there are some
				 * overflow issues in the filtering as it's too
				 * "crackly".
				 * TODO: debug this, maybe just play noise at
				 * high level or look at spectrum.
				 */

				ec->cng_rndnum =
				    1664525U * ec->cng_rndnum + 1013904223U;
				ec->cng_filter =
				    ((ec->cng_rndnum & 0xFFFF) - 32768 +
				     5 * ec->cng_filter) >> 3;
				ec->clean_nlp =
				    (ec->cng_filter * ec->cng_level * 8) >> 14;

			पूर्ण अन्यथा अगर (ec->adaption_mode & ECHO_CAN_USE_CLIP) अणु
				/* This sounds much better than CNG */
				अगर (ec->clean_nlp > ec->lbgn)
					ec->clean_nlp = ec->lbgn;
				अगर (ec->clean_nlp < -ec->lbgn)
					ec->clean_nlp = -ec->lbgn;
			पूर्ण अन्यथा अणु
				/*
				 * just mute the residual, करोesn't sound very
				 * good, used मुख्यly in G168 tests
				 */
				ec->clean_nlp = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Background noise estimator.  I tried a few
			 * algorithms here without much luck.  This very simple
			 * one seems to work best, we just average the level
			 * using a slow (1 sec समय स्थिर) filter अगर the
			 * current level is less than a (experimentally
			 * derived) स्थिरant.  This means we करोnt include high
			 * level संकेतs like near end speech.  When combined
			 * with CNG or especially CLIP seems to work OK.
			 */
			अगर (ec->lclean < 40) अणु
				ec->lbgn_acc += असल(ec->clean) - ec->lbgn;
				ec->lbgn = (ec->lbgn_acc + (1 << 11)) >> 12;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Roll around the taps buffer */
	अगर (ec->curr_pos <= 0)
		ec->curr_pos = ec->taps;
	ec->curr_pos--;

	अगर (ec->adaption_mode & ECHO_CAN_DISABLE)
		ec->clean_nlp = rx;

	/* Output scaled back up again to match input scaling */

	वापस (पूर्णांक16_t) ec->clean_nlp << 1;
पूर्ण
EXPORT_SYMBOL_GPL(oslec_update);

/* This function is separated from the echo canceller is it is usually called
   as part of the tx process.  See rx HP (DC blocking) filter above, it's
   the same design.

   Some soft phones send speech संकेतs with a lot of low frequency
   energy, e.g. करोwn to 20Hz.  This can make the hybrid non-linear
   which causes the echo canceller to fall over.  This filter can help
   by removing any low frequency beक्रमe it माला_लो to the tx port of the
   hybrid.

   It can also help by removing and DC in the tx संकेत.  DC is bad
   क्रम LMS algorithms.

   This is one of the classic DC removal filters, adjusted to provide
   sufficient bass rolloff to meet the above requirement to protect hybrids
   from things that upset them. The dअगरference between successive samples
   produces a lousy HPF, and then a suitably placed pole flattens things out.
   The final result is a nicely rolled off bass end. The filtering is
   implemented with extended fractional precision, which noise shapes things,
   giving very clean DC removal.
*/

पूर्णांक16_t oslec_hpf_tx(काष्ठा oslec_state *ec, पूर्णांक16_t tx)
अणु
	पूर्णांक पंचांगp;
	पूर्णांक पंचांगp1;

	अगर (ec->adaption_mode & ECHO_CAN_USE_TX_HPF) अणु
		पंचांगp = tx << 15;

		/*
		 * Make sure the gain of the HPF is 1.0. The first can still
		 * saturate a little under impulse conditions, and it might
		 * roll to 32768 and need clipping on sustained peak level
		 * संकेतs. However, the scale of such clipping is small, and
		 * the error due to any saturation should not markedly affect
		 * the करोwnstream processing.
		 */
		पंचांगp -= (पंचांगp >> 4);

		ec->tx_1 += -(ec->tx_1 >> DC_LOG2BETA) + पंचांगp - ec->tx_2;
		पंचांगp1 = ec->tx_1 >> 15;
		अगर (पंचांगp1 > 32767)
			पंचांगp1 = 32767;
		अगर (पंचांगp1 < -32767)
			पंचांगp1 = -32767;
		tx = पंचांगp1;
		ec->tx_2 = पंचांगp;
	पूर्ण

	वापस tx;
पूर्ण
EXPORT_SYMBOL_GPL(oslec_hpf_tx);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Rowe");
MODULE_DESCRIPTION("Open Source Line Echo Canceller");
MODULE_VERSION("0.3.0");
