<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 audio-related functions
 *
 *  Derived from ivtv-audio.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-cards.h"
#समावेश "cx18-audio.h"

#घोषणा CX18_AUDIO_ENABLE    0xc72014
#घोषणा CX18_AI1_MUX_MASK    0x30
#घोषणा CX18_AI1_MUX_I2S1    0x00
#घोषणा CX18_AI1_MUX_I2S2    0x10
#घोषणा CX18_AI1_MUX_843_I2S 0x20

/* Selects the audio input and output according to the current
   settings. */
पूर्णांक cx18_audio_set_io(काष्ठा cx18 *cx)
अणु
	स्थिर काष्ठा cx18_card_audio_input *in;
	u32 u, v;
	पूर्णांक err;

	/* Determine which input to use */
	अगर (test_bit(CX18_F_I_RADIO_USER, &cx->i_flags))
		in = &cx->card->radio_input;
	अन्यथा
		in = &cx->card->audio_inमाला_दो[cx->audio_input];

	/* handle muxer chips */
	v4l2_subdev_call(cx->sd_exपंचांगux, audio, s_routing,
			 (u32) in->muxer_input, 0, 0);

	err = cx18_call_hw_err(cx, cx->card->hw_audio_ctrl,
			       audio, s_routing, in->audio_input, 0, 0);
	अगर (err)
		वापस err;

	/* FIXME - this पूर्णांकernal mux should be असलtracted to a subdev */
	u = cx18_पढ़ो_reg(cx, CX18_AUDIO_ENABLE);
	v = u & ~CX18_AI1_MUX_MASK;
	चयन (in->audio_input) अणु
	हाल CX18_AV_AUDIO_SERIAL1:
		v |= CX18_AI1_MUX_I2S1;
		अवरोध;
	हाल CX18_AV_AUDIO_SERIAL2:
		v |= CX18_AI1_MUX_I2S2;
		अवरोध;
	शेष:
		v |= CX18_AI1_MUX_843_I2S;
		अवरोध;
	पूर्ण
	अगर (v == u) अणु
		/* क्रमce a toggle of some AI1 MUX control bits */
		u &= ~CX18_AI1_MUX_MASK;
		चयन (in->audio_input) अणु
		हाल CX18_AV_AUDIO_SERIAL1:
			u |= CX18_AI1_MUX_843_I2S;
			अवरोध;
		हाल CX18_AV_AUDIO_SERIAL2:
			u |= CX18_AI1_MUX_843_I2S;
			अवरोध;
		शेष:
			u |= CX18_AI1_MUX_I2S1;
			अवरोध;
		पूर्ण
		cx18_ग_लिखो_reg_expect(cx, u | 0xb00, CX18_AUDIO_ENABLE,
				      u, CX18_AI1_MUX_MASK);
	पूर्ण
	cx18_ग_लिखो_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
			      v, CX18_AI1_MUX_MASK);
	वापस 0;
पूर्ण
