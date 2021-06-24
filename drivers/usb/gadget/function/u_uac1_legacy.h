<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * u_uac1.h -- पूर्णांकerface to USB gadget "ALSA AUDIO" utilities
 *
 * Copyright (C) 2008 Bryan Wu <cooloney@kernel.org>
 * Copyright (C) 2008 Analog Devices, Inc
 */

#अगर_अघोषित __U_UAC1_LEGACY_H
#घोषणा __U_UAC1_LEGACY_H

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/usb/audपन.स>
#समावेश <linux/usb/composite.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#घोषणा खाता_PCM_PLAYBACK	"/dev/snd/pcmC0D0p"
#घोषणा खाता_PCM_CAPTURE	"/dev/snd/pcmC0D0c"
#घोषणा खाता_CONTROL		"/dev/snd/controlC0"

#घोषणा UAC1_OUT_EP_MAX_PACKET_SIZE	200
#घोषणा UAC1_REQ_COUNT			256
#घोषणा UAC1_AUDIO_BUF_SIZE		48000

/*
 * This represents the USB side of an audio card device, managed by a USB
 * function which provides control and stream पूर्णांकerfaces.
 */

काष्ठा gaudio_snd_dev अणु
	काष्ठा gaudio			*card;
	काष्ठा file			*filp;
	काष्ठा snd_pcm_substream	*substream;
	पूर्णांक				access;
	पूर्णांक				क्रमmat;
	पूर्णांक				channels;
	पूर्णांक				rate;
पूर्ण;

काष्ठा gaudio अणु
	काष्ठा usb_function		func;
	काष्ठा usb_gadget		*gadget;

	/* ALSA sound device पूर्णांकerfaces */
	काष्ठा gaudio_snd_dev		control;
	काष्ठा gaudio_snd_dev		playback;
	काष्ठा gaudio_snd_dev		capture;

	/* TODO */
पूर्ण;

काष्ठा f_uac1_legacy_opts अणु
	काष्ठा usb_function_instance	func_inst;
	पूर्णांक				req_buf_size;
	पूर्णांक				req_count;
	पूर्णांक				audio_buf_size;
	अक्षर				*fn_play;
	अक्षर				*fn_cap;
	अक्षर				*fn_cntl;
	अचिन्हित			bound:1;
	अचिन्हित			fn_play_alloc:1;
	अचिन्हित			fn_cap_alloc:1;
	अचिन्हित			fn_cntl_alloc:1;
	काष्ठा mutex			lock;
	पूर्णांक				refcnt;
पूर्ण;

पूर्णांक gaudio_setup(काष्ठा gaudio *card);
व्योम gaudio_cleanup(काष्ठा gaudio *the_card);

माप_प्रकार u_audio_playback(काष्ठा gaudio *card, व्योम *buf, माप_प्रकार count);
पूर्णांक u_audio_get_playback_channels(काष्ठा gaudio *card);
पूर्णांक u_audio_get_playback_rate(काष्ठा gaudio *card);

#पूर्ण_अगर /* __U_UAC1_LEGACY_H */
