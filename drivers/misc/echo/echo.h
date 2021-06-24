<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * SpanDSP - a series of DSP components क्रम telephony
 *
 * echo.c - A line echo canceller.  This code is being developed
 *          against and partially complies with G168.
 *
 * Written by Steve Underwood <steveu@coppice.org>
 *         and David Rowe <david_at_rowetel_करोt_com>
 *
 * Copyright (C) 2001 Steve Underwood and 2007 David Rowe
 *
 * All rights reserved.
 */

#अगर_अघोषित __ECHO_H
#घोषणा __ECHO_H

/*
Line echo cancellation क्रम voice

What करोes it करो?

This module aims to provide G.168-2002 compliant echo cancellation, to हटाओ
electrical echoes (e.g. from 2-4 wire hybrids) from voice calls.

How करोes it work?

The heart of the echo cancellor is FIR filter. This is adapted to match the
echo impulse response of the telephone line. It must be दीर्घ enough to
adequately cover the duration of that impulse response. The संकेत transmitted
to the telephone line is passed through the FIR filter. Once the FIR is
properly adapted, the resulting output is an estimate of the echo संकेत
received from the line. This is subtracted from the received संकेत. The result
is an estimate of the संकेत which originated at the far end of the line, मुक्त
from echos of our own transmitted संकेत.

The least mean squares (LMS) algorithm is attributed to Widrow and Hoff, and
was पूर्णांकroduced in 1960. It is the commonest क्रमm of filter adaption used in
things like modem line equalisers and line echo cancellers. There it works very
well.  However, it only works well क्रम संकेतs of स्थिरant amplitude. It works
very poorly क्रम things like speech echo cancellation, where the संकेत level
varies widely.  This is quite easy to fix. If the संकेत level is normalised -
similar to applying AGC - LMS can work as well क्रम a संकेत of varying
amplitude as it करोes क्रम a modem संकेत. This normalised least mean squares
(NLMS) algorithm is the commonest one used क्रम speech echo cancellation. Many
other algorithms exist - e.g. RLS (essentially the same as Kalman filtering),
FAP, etc. Some perक्रमm signअगरicantly better than NLMS.  However, factors such
as computational complनिकासy and patents favour the use of NLMS.

A simple refinement to NLMS can improve its perक्रमmance with speech. NLMS tends
to adapt best to the strongest parts of a संकेत. If the संकेत is white noise,
the NLMS algorithm works very well. However, speech has more low frequency than
high frequency content. Pre-whitening (i.e. filtering the संकेत to flatten its
spectrum) the echo संकेत improves the adapt rate क्रम speech, and ensures the
final residual संकेत is not heavily biased towards high frequencies. A very
low complनिकासy filter is adequate क्रम this, so pre-whitening adds little to the
compute requirements of the echo canceller.

An FIR filter adapted using pre-whitened NLMS perक्रमms well, provided certain
conditions are met:

    - The transmitted संकेत has poor self-correlation.
    - There is no संकेत being generated within the environment being
      cancelled.

The dअगरficulty is that neither of these can be guaranteed.

If the adaption is perक्रमmed जबतक transmitting noise (or something fairly
noise like, such as voice) the adaption works very well. If the adaption is
perक्रमmed जबतक transmitting something highly correlative (typically narrow
band energy such as संकेतling tones or DTMF), the adaption can go seriously
wrong. The reason is there is only one solution क्रम the adaption on a near
अक्रमom संकेत - the impulse response of the line. For a repetitive संकेत,
there are any number of solutions which converge the adaption, and nothing
guides the adaption to choose the generalised one. Allowing an untrained
canceller to converge on this kind of narrowband energy probably a good thing,
since at least it cancels the tones. Allowing a well converged canceller to
जारी converging on such energy is just a way to ruin its generalised
adaption. A narrowband detector is needed, so adapation can be suspended at
appropriate बार.

The adaption process is based on trying to eliminate the received संकेत. When
there is any संकेत from within the environment being cancelled it may upset
the adaption process. Similarly, अगर the संकेत we are transmitting is small,
noise may करोminate and disturb the adaption process. If we can ensure that the
adaption is only perक्रमmed when we are transmitting a signअगरicant संकेत level,
and the environment is not, things will be OK. Clearly, it is easy to tell when
we are sending a signअगरicant संकेत. Telling, अगर the environment is generating
a signअगरicant संकेत, and करोing it with sufficient speed that the adaption will
not have भागerged too much more we stop it, is a little harder.

The key problem in detecting when the environment is sourcing signअगरicant
energy is that we must करो this very quickly. Given a reasonably दीर्घ sample of
the received संकेत, there are a number of strategies which may be used to
assess whether that संकेत contains a strong far end component. However, by the
समय that assessment is complete the far end संकेत will have alपढ़ोy caused
major mis-convergence in the adaption process. An assessment algorithm is
needed which produces a fairly accurate result from a very लघु burst of far
end energy.

How करो I use it?

The echo cancellor processes both the transmit and receive streams sample by
sample. The processing function is not declared अंतरभूत. Unक्रमtunately,
cancellation requires many operations per sample, so the call overhead is only
a minor burden.
*/

#समावेश "fir.h"
#समावेश "oslec.h"

/*
    G.168 echo canceller descriptor. This defines the working state क्रम a line
    echo canceller.
*/
काष्ठा oslec_state अणु
	पूर्णांक16_t tx;
	पूर्णांक16_t rx;
	पूर्णांक16_t clean;
	पूर्णांक16_t clean_nlp;

	पूर्णांक nonupdate_dwell;
	पूर्णांक curr_pos;
	पूर्णांक taps;
	पूर्णांक log2taps;
	पूर्णांक adaption_mode;

	पूर्णांक cond_met;
	पूर्णांक32_t pstates;
	पूर्णांक16_t adapt;
	पूर्णांक32_t factor;
	पूर्णांक16_t shअगरt;

	/* Average levels and averaging filter states */
	पूर्णांक ltxacc;
	पूर्णांक lrxacc;
	पूर्णांक lcleanacc;
	पूर्णांक lclean_bgacc;
	पूर्णांक ltx;
	पूर्णांक lrx;
	पूर्णांक lclean;
	पूर्णांक lclean_bg;
	पूर्णांक lbgn;
	पूर्णांक lbgn_acc;
	पूर्णांक lbgn_upper;
	पूर्णांक lbgn_upper_acc;

	/* क्रमeground and background filter states */
	काष्ठा fir16_state_t fir_state;
	काष्ठा fir16_state_t fir_state_bg;
	पूर्णांक16_t *fir_taps16[2];

	/* DC blocking filter states */
	पूर्णांक tx_1;
	पूर्णांक tx_2;
	पूर्णांक rx_1;
	पूर्णांक rx_2;

	/* optional High Pass Filter states */
	पूर्णांक32_t xvtx[5];
	पूर्णांक32_t yvtx[5];
	पूर्णांक32_t xvrx[5];
	पूर्णांक32_t yvrx[5];

	/* Parameters क्रम the optional Hoth noise generator */
	पूर्णांक cng_level;
	पूर्णांक cng_rndnum;
	पूर्णांक cng_filter;

	/* snapshot sample of coeffs used क्रम development */
	पूर्णांक16_t *snapshot;
पूर्ण;

#पूर्ण_अगर /* __ECHO_H */
