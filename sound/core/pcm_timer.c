<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Digital Audio (PCM) असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/समय.स>
#समावेश <linux/gcd.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/समयr.h>

#समावेश "pcm_local.h"

/*
 *  Timer functions
 */

व्योम snd_pcm_समयr_resolution_change(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ rate, mult, fsize, l, post;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	mult = 1000000000;
	rate = runसमय->rate;
	अगर (snd_BUG_ON(!rate))
		वापस;
	l = gcd(mult, rate);
	mult /= l;
	rate /= l;
	fsize = runसमय->period_size;
	अगर (snd_BUG_ON(!fsize))
		वापस;
	l = gcd(rate, fsize);
	rate /= l;
	fsize /= l;
	post = 1;
	जबतक ((mult * fsize) / fsize != mult) अणु
		mult /= 2;
		post *= 2;
	पूर्ण
	अगर (rate == 0) अणु
		pcm_err(substream->pcm,
			"pcm timer resolution out of range (rate = %u, period_size = %lu)\n",
			runसमय->rate, runसमय->period_size);
		runसमय->समयr_resolution = -1;
		वापस;
	पूर्ण
	runसमय->समयr_resolution = (mult * fsize / rate) * post;
पूर्ण

अटल अचिन्हित दीर्घ snd_pcm_समयr_resolution(काष्ठा snd_समयr * समयr)
अणु
	काष्ठा snd_pcm_substream *substream;

	substream = समयr->निजी_data;
	वापस substream->runसमय ? substream->runसमय->समयr_resolution : 0;
पूर्ण

अटल पूर्णांक snd_pcm_समयr_start(काष्ठा snd_समयr * समयr)
अणु
	काष्ठा snd_pcm_substream *substream;

	substream = snd_समयr_chip(समयr);
	substream->समयr_running = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pcm_समयr_stop(काष्ठा snd_समयr * समयr)
अणु
	काष्ठा snd_pcm_substream *substream;

	substream = snd_समयr_chip(समयr);
	substream->समयr_running = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware snd_pcm_समयr =
अणु
	.flags =	SNDRV_TIMER_HW_AUTO | SNDRV_TIMER_HW_SLAVE,
	.resolution =	0,
	.ticks =	1,
	.c_resolution =	snd_pcm_समयr_resolution,
	.start =	snd_pcm_समयr_start,
	.stop =		snd_pcm_समयr_stop,
पूर्ण;

/*
 *  Init functions
 */

अटल व्योम snd_pcm_समयr_मुक्त(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_pcm_substream *substream = समयr->निजी_data;
	substream->समयr = शून्य;
पूर्ण

व्योम snd_pcm_समयr_init(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_समयr_id tid;
	काष्ठा snd_समयr *समयr;

	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.dev_class = SNDRV_TIMER_CLASS_PCM;
	tid.card = substream->pcm->card->number;
	tid.device = substream->pcm->device;
	tid.subdevice = (substream->number << 1) | (substream->stream & 1);
	अगर (snd_समयr_new(substream->pcm->card, "PCM", &tid, &समयr) < 0)
		वापस;
	प्र_लिखो(समयr->name, "PCM %s %i-%i-%i",
			substream->stream == SNDRV_PCM_STREAM_CAPTURE ?
				"capture" : "playback",
			tid.card, tid.device, tid.subdevice);
	समयr->hw = snd_pcm_समयr;
	अगर (snd_device_रेजिस्टर(समयr->card, समयr) < 0) अणु
		snd_device_मुक्त(समयr->card, समयr);
		वापस;
	पूर्ण
	समयr->निजी_data = substream;
	समयr->निजी_मुक्त = snd_pcm_समयr_मुक्त;
	substream->समयr = समयr;
पूर्ण

व्योम snd_pcm_समयr_करोne(काष्ठा snd_pcm_substream *substream)
अणु
	अगर (substream->समयr) अणु
		snd_device_मुक्त(substream->pcm->card, substream->समयr);
		substream->समयr = शून्य;
	पूर्ण
पूर्ण
