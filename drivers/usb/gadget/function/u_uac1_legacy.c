<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * u_uac1.c -- ALSA audio utilities क्रम Gadget stack
 *
 * Copyright (C) 2008 Bryan Wu <cooloney@kernel.org>
 * Copyright (C) 2008 Analog Devices, Inc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/syscalls.h>

#समावेश "u_uac1_legacy.h"

/*
 * This component encapsulates the ALSA devices क्रम USB audio gadget
 */

/*-------------------------------------------------------------------------*/

/*
 * Some ALSA पूर्णांकernal helper functions
 */
अटल पूर्णांक snd_पूर्णांकerval_refine_set(काष्ठा snd_पूर्णांकerval *i, अचिन्हित पूर्णांक val)
अणु
	काष्ठा snd_पूर्णांकerval t;
	t.empty = 0;
	t.min = t.max = val;
	t.खोलोmin = t.खोलोmax = 0;
	t.पूर्णांकeger = 1;
	वापस snd_पूर्णांकerval_refine(i, &t);
पूर्ण

अटल पूर्णांक _snd_pcm_hw_param_set(काष्ठा snd_pcm_hw_params *params,
				 snd_pcm_hw_param_t var, अचिन्हित पूर्णांक val,
				 पूर्णांक dir)
अणु
	पूर्णांक changed;
	अगर (hw_is_mask(var)) अणु
		काष्ठा snd_mask *m = hw_param_mask(params, var);
		अगर (val == 0 && dir < 0) अणु
			changed = -EINVAL;
			snd_mask_none(m);
		पूर्ण अन्यथा अणु
			अगर (dir > 0)
				val++;
			अन्यथा अगर (dir < 0)
				val--;
			changed = snd_mask_refine_set(
					hw_param_mask(params, var), val);
		पूर्ण
	पूर्ण अन्यथा अगर (hw_is_पूर्णांकerval(var)) अणु
		काष्ठा snd_पूर्णांकerval *i = hw_param_पूर्णांकerval(params, var);
		अगर (val == 0 && dir < 0) अणु
			changed = -EINVAL;
			snd_पूर्णांकerval_none(i);
		पूर्ण अन्यथा अगर (dir == 0)
			changed = snd_पूर्णांकerval_refine_set(i, val);
		अन्यथा अणु
			काष्ठा snd_पूर्णांकerval t;
			t.खोलोmin = 1;
			t.खोलोmax = 1;
			t.empty = 0;
			t.पूर्णांकeger = 0;
			अगर (dir < 0) अणु
				t.min = val - 1;
				t.max = val;
			पूर्ण अन्यथा अणु
				t.min = val;
				t.max = val+1;
			पूर्ण
			changed = snd_पूर्णांकerval_refine(i, &t);
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;
	अगर (changed) अणु
		params->cmask |= 1 << var;
		params->rmask |= 1 << var;
	पूर्ण
	वापस changed;
पूर्ण
/*-------------------------------------------------------------------------*/

/*
 * Set शेष hardware params
 */
अटल पूर्णांक playback_शेष_hw_params(काष्ठा gaudio_snd_dev *snd)
अणु
	काष्ठा snd_pcm_substream *substream = snd->substream;
	काष्ठा snd_pcm_hw_params *params;
	snd_pcm_sframes_t result;

       /*
	* SNDRV_PCM_ACCESS_RW_INTERLEAVED,
	* SNDRV_PCM_FORMAT_S16_LE
	* CHANNELS: 2
	* RATE: 48000
	*/
	snd->access = SNDRV_PCM_ACCESS_RW_INTERLEAVED;
	snd->क्रमmat = SNDRV_PCM_FORMAT_S16_LE;
	snd->channels = 2;
	snd->rate = 48000;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	_snd_pcm_hw_params_any(params);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_ACCESS,
			snd->access, 0);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_FORMAT,
			snd->क्रमmat, 0);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_CHANNELS,
			snd->channels, 0);
	_snd_pcm_hw_param_set(params, SNDRV_PCM_HW_PARAM_RATE,
			snd->rate, 0);

	snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_DROP, शून्य);
	snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_HW_PARAMS, params);

	result = snd_pcm_kernel_ioctl(substream, SNDRV_PCM_IOCTL_PREPARE, शून्य);
	अगर (result < 0) अणु
		ERROR(snd->card,
			"Preparing sound card failed: %d\n", (पूर्णांक)result);
		kमुक्त(params);
		वापस result;
	पूर्ण

	/* Store the hardware parameters */
	snd->access = params_access(params);
	snd->क्रमmat = params_क्रमmat(params);
	snd->channels = params_channels(params);
	snd->rate = params_rate(params);

	kमुक्त(params);

	INFO(snd->card,
		"Hardware params: access %x, format %x, channels %d, rate %d\n",
		snd->access, snd->क्रमmat, snd->channels, snd->rate);

	वापस 0;
पूर्ण

/*
 * Playback audio buffer data by ALSA PCM device
 */
माप_प्रकार u_audio_playback(काष्ठा gaudio *card, व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा gaudio_snd_dev	*snd = &card->playback;
	काष्ठा snd_pcm_substream *substream = snd->substream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	sमाप_प्रकार result;
	snd_pcm_sframes_t frames;

try_again:
	अगर (runसमय->status->state == SNDRV_PCM_STATE_XRUN ||
		runसमय->status->state == SNDRV_PCM_STATE_SUSPENDED) अणु
		result = snd_pcm_kernel_ioctl(substream,
				SNDRV_PCM_IOCTL_PREPARE, शून्य);
		अगर (result < 0) अणु
			ERROR(card, "Preparing sound card failed: %d\n",
					(पूर्णांक)result);
			वापस result;
		पूर्ण
	पूर्ण

	frames = bytes_to_frames(runसमय, count);
	result = snd_pcm_kernel_ग_लिखो(snd->substream, buf, frames);
	अगर (result != frames) अणु
		ERROR(card, "Playback error: %d\n", (पूर्णांक)result);
		जाओ try_again;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक u_audio_get_playback_channels(काष्ठा gaudio *card)
अणु
	वापस card->playback.channels;
पूर्ण

पूर्णांक u_audio_get_playback_rate(काष्ठा gaudio *card)
अणु
	वापस card->playback.rate;
पूर्ण

/*
 * Open ALSA PCM and control device files
 * Initial the PCM or control device
 */
अटल पूर्णांक gaudio_खोलो_snd_dev(काष्ठा gaudio *card)
अणु
	काष्ठा snd_pcm_file *pcm_file;
	काष्ठा gaudio_snd_dev *snd;
	काष्ठा f_uac1_legacy_opts *opts;
	अक्षर *fn_play, *fn_cap, *fn_cntl;

	opts = container_of(card->func.fi, काष्ठा f_uac1_legacy_opts,
			    func_inst);
	fn_play = opts->fn_play;
	fn_cap = opts->fn_cap;
	fn_cntl = opts->fn_cntl;

	/* Open control device */
	snd = &card->control;
	snd->filp = filp_खोलो(fn_cntl, O_RDWR, 0);
	अगर (IS_ERR(snd->filp)) अणु
		पूर्णांक ret = PTR_ERR(snd->filp);
		ERROR(card, "unable to open sound control device file: %s\n",
				fn_cntl);
		snd->filp = शून्य;
		वापस ret;
	पूर्ण
	snd->card = card;

	/* Open PCM playback device and setup substream */
	snd = &card->playback;
	snd->filp = filp_खोलो(fn_play, O_WRONLY, 0);
	अगर (IS_ERR(snd->filp)) अणु
		पूर्णांक ret = PTR_ERR(snd->filp);

		ERROR(card, "No such PCM playback device: %s\n", fn_play);
		snd->filp = शून्य;
		वापस ret;
	पूर्ण
	pcm_file = snd->filp->निजी_data;
	snd->substream = pcm_file->substream;
	snd->card = card;
	playback_शेष_hw_params(snd);

	/* Open PCM capture device and setup substream */
	snd = &card->capture;
	snd->filp = filp_खोलो(fn_cap, O_RDONLY, 0);
	अगर (IS_ERR(snd->filp)) अणु
		ERROR(card, "No such PCM capture device: %s\n", fn_cap);
		snd->substream = शून्य;
		snd->card = शून्य;
		snd->filp = शून्य;
	पूर्ण अन्यथा अणु
		pcm_file = snd->filp->निजी_data;
		snd->substream = pcm_file->substream;
		snd->card = card;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Close ALSA PCM and control device files
 */
अटल पूर्णांक gaudio_बंद_snd_dev(काष्ठा gaudio *gau)
अणु
	काष्ठा gaudio_snd_dev	*snd;

	/* Close control device */
	snd = &gau->control;
	अगर (snd->filp)
		filp_बंद(snd->filp, शून्य);

	/* Close PCM playback device and setup substream */
	snd = &gau->playback;
	अगर (snd->filp)
		filp_बंद(snd->filp, शून्य);

	/* Close PCM capture device and setup substream */
	snd = &gau->capture;
	अगर (snd->filp)
		filp_बंद(snd->filp, शून्य);

	वापस 0;
पूर्ण

/*
 * gaudio_setup - setup ALSA पूर्णांकerface and preparing क्रम USB transfer
 *
 * This sets up PCM, mixer or MIDI ALSA devices क्रमe USB gadget using.
 *
 * Returns negative त्रुटि_सं, or zero on success
 */
पूर्णांक gaudio_setup(काष्ठा gaudio *card)
अणु
	पूर्णांक	ret;

	ret = gaudio_खोलो_snd_dev(card);
	अगर (ret)
		ERROR(card, "we need at least one control device\n");

	वापस ret;

पूर्ण

/*
 * gaudio_cleanup - हटाओ ALSA device पूर्णांकerface
 *
 * This is called to मुक्त all resources allocated by @gaudio_setup().
 */
व्योम gaudio_cleanup(काष्ठा gaudio *the_card)
अणु
	अगर (the_card)
		gaudio_बंद_snd_dev(the_card);
पूर्ण

