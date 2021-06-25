<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_yamaha.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./bebob.h"

/*
 * NOTE:
 * Yamaha GO44 is not deचिन्हित to be used as stand-alone mixer. So any streams
 * must be accompanied. If changing the state, a LED on the device starts to
 * blink and its sync status is false. In this state, the device sounds nothing
 * even अगर streaming. To start streaming at the current sampling rate is only
 * way to recover this state. GO46 is better क्रम stand-alone mixer.
 *
 * Both of them have a capability to change its sampling rate up to 192.0kHz.
 * At 192.0kHz, the device reports 4 PCM-in, 1 MIDI-in, 6 PCM-out, 1 MIDI-out.
 * But Yamaha's driver reduce 2 PCM-in, 1 MIDI-in, 2 PCM-out, 1 MIDI-out to use
 * 'Extended Stream Format Information Command - Single Request' in 'Additional
 * AVC commands' defined by BridgeCo.
 * This ALSA driver करोn't करो this because a bit tiresome. Then isochronous
 * streaming with many asynchronous transactions brings sounds with noises.
 * Unक्रमtunately current 'ffado-mixer' generated many asynchronous transaction
 * to observe device's state, मुख्यly check cmp connection and संकेत क्रमmat. I
 * recommend users to बंद ffaकरो-mixer at 192.0kHz अगर mixer is needless.
 *
 * Terratec PHASE 24 FW and PHASE X24 FW are पूर्णांकernally the same as
 * Yamaha GO 44 and GO 46. Yamaha and Terratec had cooperated क्रम these models.
 */

अटल स्थिर क्रमागत snd_bebob_घड़ी_प्रकारype clk_src_types[] = अणु
	SND_BEBOB_CLOCK_TYPE_INTERNAL,
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* S/PDIF */
पूर्ण;
अटल पूर्णांक
clk_src_get(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *id)
अणु
	पूर्णांक err;

	err = avc_audio_get_selector(bebob->unit, 0, 4, id);
	अगर (err < 0)
		वापस err;

	अगर (*id >= ARRAY_SIZE(clk_src_types))
		वापस -EIO;

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा snd_bebob_घड़ी_spec घड़ी_spec = अणु
	.num	= ARRAY_SIZE(clk_src_types),
	.types	= clk_src_types,
	.get	= &clk_src_get,
पूर्ण;
अटल स्थिर काष्ठा snd_bebob_rate_spec rate_spec = अणु
	.get	= &snd_bebob_stream_get_rate,
	.set	= &snd_bebob_stream_set_rate,
पूर्ण;
स्थिर काष्ठा snd_bebob_spec yamaha_terratec_spec = अणु
	.घड़ी	= &घड़ी_spec,
	.rate	= &rate_spec,
	.meter	= शून्य
पूर्ण;
