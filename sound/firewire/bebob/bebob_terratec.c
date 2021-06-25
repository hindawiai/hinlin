<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_terratec.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./bebob.h"

अटल स्थिर क्रमागत snd_bebob_घड़ी_प्रकारype phase88_rack_clk_src_types[] = अणु
	SND_BEBOB_CLOCK_TYPE_INTERNAL,
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* S/PDIF */
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* Word Clock */
पूर्ण;
अटल पूर्णांक
phase88_rack_clk_src_get(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *id)
अणु
	अचिन्हित पूर्णांक enable_ext, enable_word;
	पूर्णांक err;

	err = avc_audio_get_selector(bebob->unit, 0, 9, &enable_ext);
	अगर (err < 0)
		जाओ end;
	err = avc_audio_get_selector(bebob->unit, 0, 8, &enable_word);
	अगर (err < 0)
		जाओ end;

	अगर (enable_ext == 0)
		*id = 0;
	अन्यथा अगर (enable_word == 0)
		*id = 1;
	अन्यथा
		*id = 2;
end:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_bebob_rate_spec phase_series_rate_spec = अणु
	.get	= &snd_bebob_stream_get_rate,
	.set	= &snd_bebob_stream_set_rate,
पूर्ण;

/* PHASE 88 Rack FW */
अटल स्थिर काष्ठा snd_bebob_घड़ी_spec phase88_rack_clk = अणु
	.num	= ARRAY_SIZE(phase88_rack_clk_src_types),
	.types	= phase88_rack_clk_src_types,
	.get	= &phase88_rack_clk_src_get,
पूर्ण;
स्थिर काष्ठा snd_bebob_spec phase88_rack_spec = अणु
	.घड़ी	= &phase88_rack_clk,
	.rate	= &phase_series_rate_spec,
	.meter	= शून्य
पूर्ण;
