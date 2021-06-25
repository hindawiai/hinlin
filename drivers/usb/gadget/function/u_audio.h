<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * u_audपन.स -- पूर्णांकerface to USB gadget "ALSA sound card" utilities
 *
 * Copyright (C) 2016
 * Author: Ruslan Bilovol <ruslan.bilovol@gmail.com>
 */

#अगर_अघोषित __U_AUDIO_H
#घोषणा __U_AUDIO_H

#समावेश <linux/usb/composite.h>

काष्ठा uac_params अणु
	/* playback */
	पूर्णांक p_chmask;	/* channel mask */
	पूर्णांक p_srate;	/* rate in Hz */
	पूर्णांक p_ssize;	/* sample size */

	/* capture */
	पूर्णांक c_chmask;	/* channel mask */
	पूर्णांक c_srate;	/* rate in Hz */
	पूर्णांक c_ssize;	/* sample size */

	पूर्णांक req_number; /* number of pपुनः_स्मृतिated requests */
पूर्ण;

काष्ठा g_audio अणु
	काष्ठा usb_function func;
	काष्ठा usb_gadget *gadget;

	काष्ठा usb_ep *in_ep;
	काष्ठा usb_ep *out_ep;

	/* Max packet size क्रम all in_ep possible speeds */
	अचिन्हित पूर्णांक in_ep_maxpsize;
	/* Max packet size क्रम all out_ep possible speeds */
	अचिन्हित पूर्णांक out_ep_maxpsize;

	/* The ALSA Sound Card it represents on the USB-Client side */
	काष्ठा snd_uac_chip *uac;

	काष्ठा uac_params params;
पूर्ण;

अटल अंतरभूत काष्ठा g_audio *func_to_g_audio(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा g_audio, func);
पूर्ण

अटल अंतरभूत uपूर्णांक num_channels(uपूर्णांक chanmask)
अणु
	uपूर्णांक num = 0;

	जबतक (chanmask) अणु
		num += (chanmask & 1);
		chanmask >>= 1;
	पूर्ण

	वापस num;
पूर्ण

/*
 * g_audio_setup - initialize one भव ALSA sound card
 * @g_audio: काष्ठा with filled params, in_ep_maxpsize, out_ep_maxpsize
 * @pcm_name: the id string क्रम a PCM instance of this sound card
 * @card_name: name of this soundcard
 *
 * This sets up the single भव ALSA sound card that may be exported by a
 * gadget driver using this framework.
 *
 * Context: may sleep
 *
 * Returns zero on success, or a negative error on failure.
 */
पूर्णांक g_audio_setup(काष्ठा g_audio *g_audio, स्थिर अक्षर *pcm_name,
					स्थिर अक्षर *card_name);
व्योम g_audio_cleanup(काष्ठा g_audio *g_audio);

पूर्णांक u_audio_start_capture(काष्ठा g_audio *g_audio);
व्योम u_audio_stop_capture(काष्ठा g_audio *g_audio);
पूर्णांक u_audio_start_playback(काष्ठा g_audio *g_audio);
व्योम u_audio_stop_playback(काष्ठा g_audio *g_audio);

#पूर्ण_अगर /* __U_AUDIO_H */
