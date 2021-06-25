<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SpanDSP - a series of DSP components क्रम telephony
 *
 * ec_disable_detector.h - A detector which should eventually meet the
 *                         G.164/G.165 requirements क्रम detecting the
 *                         2100Hz echo cancellor disable tone.
 *
 * Written by Steve Underwood <steveu@coppice.org>
 *
 * Copyright (C) 2001 Steve Underwood
 *
 * All rights reserved.
 */

#समावेश "dsp_biquad.h"

काष्ठा ec_disable_detector_state अणु
	काष्ठा biquad2_state notch;
	पूर्णांक notch_level;
	पूर्णांक channel_level;
	पूर्णांक tone_present;
	पूर्णांक tone_cycle_duration;
	पूर्णांक good_cycles;
	पूर्णांक hit;
पूर्ण;


#घोषणा FALSE 0
#घोषणा TRUE (!FALSE)

अटल अंतरभूत व्योम
echo_can_disable_detector_init(काष्ठा ec_disable_detector_state *det)
अणु
	/* Elliptic notch */
	/* This is actually centred at 2095Hz, but माला_लो the balance we want, due
	   to the asymmetric walls of the notch */
	biquad2_init(&det->notch,
		     (पूर्णांक32_t)(-0.7600000 * 32768.0),
		     (पूर्णांक32_t)(-0.1183852 * 32768.0),
		     (पूर्णांक32_t)(-0.5104039 * 32768.0),
		     (पूर्णांक32_t)(0.1567596 * 32768.0),
		     (पूर्णांक32_t)(1.0000000 * 32768.0));

	det->channel_level = 0;
	det->notch_level = 0;
	det->tone_present = FALSE;
	det->tone_cycle_duration = 0;
	det->good_cycles = 0;
	det->hit = 0;
पूर्ण
/*- End of function --------------------------------------------------------*/

अटल अंतरभूत पूर्णांक
echo_can_disable_detector_update(काष्ठा ec_disable_detector_state *det,
				 पूर्णांक16_t amp)
अणु
	पूर्णांक16_t notched;

	notched = biquad2(&det->notch, amp);
	/* Estimate the overall energy in the channel, and the energy in
	   the notch (i.e. overall channel energy - tone energy => noise).
	   Use असल instead of multiply क्रम speed (is it really faster?).
	   Damp the overall energy a little more क्रम a stable result.
	   Damp the notch energy a little less, so we करोn't damp out the
	   blip every समय the phase reverses */
	det->channel_level += ((असल(amp) - det->channel_level) >> 5);
	det->notch_level += ((असल(notched) - det->notch_level) >> 4);
	अगर (det->channel_level > 280) अणु
		/* There is adequate energy in the channel.
		   Is it mostly at 2100Hz? */
		अगर (det->notch_level * 6 < det->channel_level) अणु
			/* The notch says yes, so we have the tone. */
			अगर (!det->tone_present) अणु
				/* Do we get a kick every 450+-25ms? */
				अगर (det->tone_cycle_duration >= 425 * 8
				    && det->tone_cycle_duration <= 475 * 8) अणु
					det->good_cycles++;
					अगर (det->good_cycles > 2)
						det->hit = TRUE;
				पूर्ण
				det->tone_cycle_duration = 0;
			पूर्ण
			det->tone_present = TRUE;
		पूर्ण अन्यथा
			det->tone_present = FALSE;
		det->tone_cycle_duration++;
	पूर्ण अन्यथा अणु
		det->tone_present = FALSE;
		det->tone_cycle_duration = 0;
		det->good_cycles = 0;
	पूर्ण
	वापस det->hit;
पूर्ण
/*- End of function --------------------------------------------------------*/
/*- End of file ------------------------------------------------------------*/
