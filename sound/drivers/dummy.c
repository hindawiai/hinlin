<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Dummy soundcard
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Dummy soundcard (/dev/null)");
MODULE_LICENSE("GPL");

#घोषणा MAX_PCM_DEVICES		4
#घोषणा MAX_PCM_SUBSTREAMS	128
#घोषणा MAX_MIDI_DEVICES	2

/* शेषs */
#घोषणा MAX_BUFFER_SIZE		(64*1024)
#घोषणा MIN_PERIOD_SIZE		64
#घोषणा MAX_PERIOD_SIZE		MAX_BUFFER_SIZE
#घोषणा USE_FORMATS 		(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE)
#घोषणा USE_RATE		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000
#घोषणा USE_RATE_MIN		5500
#घोषणा USE_RATE_MAX		48000
#घोषणा USE_CHANNELS_MIN 	1
#घोषणा USE_CHANNELS_MAX 	2
#घोषणा USE_PERIODS_MIN 	1
#घोषणा USE_PERIODS_MAX 	1024

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = अणु1, [1 ... (SNDRV_CARDS - 1)] = 0पूर्ण;
अटल अक्षर *model[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = शून्यपूर्ण;
अटल पूर्णांक pcm_devs[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;
अटल पूर्णांक pcm_substreams[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 8पूर्ण;
//अटल पूर्णांक midi_devs[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 2पूर्ण;
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
अटल bool hrसमयr = 1;
#पूर्ण_अगर
अटल bool fake_buffer = 1;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for dummy soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for dummy soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable this dummy soundcard.");
module_param_array(model, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(model, "Soundcard model.");
module_param_array(pcm_devs, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_devs, "PCM devices # (0-4) for dummy driver.");
module_param_array(pcm_substreams, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_substreams, "PCM substreams # (1-128) for dummy driver.");
//module_param_array(midi_devs, पूर्णांक, शून्य, 0444);
//MODULE_PARM_DESC(midi_devs, "MIDI devices # (0-2) for dummy driver.");
module_param(fake_buffer, bool, 0444);
MODULE_PARM_DESC(fake_buffer, "Fake buffer allocations.");
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
module_param(hrसमयr, bool, 0644);
MODULE_PARM_DESC(hrसमयr, "Use hrtimer as the timer source.");
#पूर्ण_अगर

अटल काष्ठा platक्रमm_device *devices[SNDRV_CARDS];

#घोषणा MIXER_ADDR_MASTER	0
#घोषणा MIXER_ADDR_LINE		1
#घोषणा MIXER_ADDR_MIC		2
#घोषणा MIXER_ADDR_SYNTH	3
#घोषणा MIXER_ADDR_CD		4
#घोषणा MIXER_ADDR_LAST		4

काष्ठा dummy_समयr_ops अणु
	पूर्णांक (*create)(काष्ठा snd_pcm_substream *);
	व्योम (*मुक्त)(काष्ठा snd_pcm_substream *);
	पूर्णांक (*prepare)(काष्ठा snd_pcm_substream *);
	पूर्णांक (*start)(काष्ठा snd_pcm_substream *);
	पूर्णांक (*stop)(काष्ठा snd_pcm_substream *);
	snd_pcm_uframes_t (*poपूर्णांकer)(काष्ठा snd_pcm_substream *);
पूर्ण;

#घोषणा get_dummy_ops(substream) \
	(*(स्थिर काष्ठा dummy_समयr_ops **)(substream)->runसमय->निजी_data)

काष्ठा dummy_model अणु
	स्थिर अक्षर *name;
	पूर्णांक (*playback_स्थिरraपूर्णांकs)(काष्ठा snd_pcm_runसमय *runसमय);
	पूर्णांक (*capture_स्थिरraपूर्णांकs)(काष्ठा snd_pcm_runसमय *runसमय);
	u64 क्रमmats;
	माप_प्रकार buffer_bytes_max;
	माप_प्रकार period_bytes_min;
	माप_प्रकार period_bytes_max;
	अचिन्हित पूर्णांक periods_min;
	अचिन्हित पूर्णांक periods_max;
	अचिन्हित पूर्णांक rates;
	अचिन्हित पूर्णांक rate_min;
	अचिन्हित पूर्णांक rate_max;
	अचिन्हित पूर्णांक channels_min;
	अचिन्हित पूर्णांक channels_max;
पूर्ण;

काष्ठा snd_dummy अणु
	काष्ठा snd_card *card;
	स्थिर काष्ठा dummy_model *model;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_hardware pcm_hw;
	spinlock_t mixer_lock;
	पूर्णांक mixer_volume[MIXER_ADDR_LAST+1][2];
	पूर्णांक capture_source[MIXER_ADDR_LAST+1][2];
	पूर्णांक iobox;
	काष्ठा snd_kcontrol *cd_volume_ctl;
	काष्ठा snd_kcontrol *cd_चयन_ctl;
पूर्ण;

/*
 * card models
 */

अटल पूर्णांक emu10k1_playback_स्थिरraपूर्णांकs(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक err;
	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 256, अच_पूर्णांक_उच्च);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dummy_model model_emu10k1 = अणु
	.name = "emu10k1",
	.playback_स्थिरraपूर्णांकs = emu10k1_playback_स्थिरraपूर्णांकs,
	.buffer_bytes_max = 128 * 1024,
पूर्ण;

अटल स्थिर काष्ठा dummy_model model_rme9652 = अणु
	.name = "rme9652",
	.buffer_bytes_max = 26 * 64 * 1024,
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 26,
	.channels_max = 26,
	.periods_min = 2,
	.periods_max = 2,
पूर्ण;

अटल स्थिर काष्ठा dummy_model model_ice1712 = अणु
	.name = "ice1712",
	.buffer_bytes_max = 256 * 1024,
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 10,
	.channels_max = 10,
	.periods_min = 1,
	.periods_max = 1024,
पूर्ण;

अटल स्थिर काष्ठा dummy_model model_uda1341 = अणु
	.name = "uda1341",
	.buffer_bytes_max = 16380,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.channels_min = 2,
	.channels_max = 2,
	.periods_min = 2,
	.periods_max = 255,
पूर्ण;

अटल स्थिर काष्ठा dummy_model model_ac97 = अणु
	.name = "ac97",
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.channels_min = 2,
	.channels_max = 2,
	.rates = SNDRV_PCM_RATE_48000,
	.rate_min = 48000,
	.rate_max = 48000,
पूर्ण;

अटल स्थिर काष्ठा dummy_model model_ca0106 = अणु
	.name = "ca0106",
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.buffer_bytes_max = ((65536-64)*8),
	.period_bytes_max = (65536-64),
	.periods_min = 2,
	.periods_max = 8,
	.channels_min = 2,
	.channels_max = 2,
	.rates = SNDRV_PCM_RATE_48000|SNDRV_PCM_RATE_96000|SNDRV_PCM_RATE_192000,
	.rate_min = 48000,
	.rate_max = 192000,
पूर्ण;

अटल स्थिर काष्ठा dummy_model *dummy_models[] = अणु
	&model_emu10k1,
	&model_rme9652,
	&model_ice1712,
	&model_uda1341,
	&model_ac97,
	&model_ca0106,
	शून्य
पूर्ण;

/*
 * प्रणाली समयr पूर्णांकerface
 */

काष्ठा dummy_sysसमयr_pcm अणु
	/* ops must be the first item */
	स्थिर काष्ठा dummy_समयr_ops *समयr_ops;
	spinlock_t lock;
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ base_समय;
	अचिन्हित पूर्णांक frac_pos;	/* fractional sample position (based HZ) */
	अचिन्हित पूर्णांक frac_period_rest;
	अचिन्हित पूर्णांक frac_buffer_size;	/* buffer_size * HZ */
	अचिन्हित पूर्णांक frac_period_size;	/* period_size * HZ */
	अचिन्हित पूर्णांक rate;
	पूर्णांक elapsed;
	काष्ठा snd_pcm_substream *substream;
पूर्ण;

अटल व्योम dummy_sysसमयr_rearm(काष्ठा dummy_sysसमयr_pcm *dpcm)
अणु
	mod_समयr(&dpcm->समयr, jअगरfies +
		DIV_ROUND_UP(dpcm->frac_period_rest, dpcm->rate));
पूर्ण

अटल व्योम dummy_sysसमयr_update(काष्ठा dummy_sysसमयr_pcm *dpcm)
अणु
	अचिन्हित दीर्घ delta;

	delta = jअगरfies - dpcm->base_समय;
	अगर (!delta)
		वापस;
	dpcm->base_समय += delta;
	delta *= dpcm->rate;
	dpcm->frac_pos += delta;
	जबतक (dpcm->frac_pos >= dpcm->frac_buffer_size)
		dpcm->frac_pos -= dpcm->frac_buffer_size;
	जबतक (dpcm->frac_period_rest <= delta) अणु
		dpcm->elapsed++;
		dpcm->frac_period_rest += dpcm->frac_period_size;
	पूर्ण
	dpcm->frac_period_rest -= delta;
पूर्ण

अटल पूर्णांक dummy_sysसमयr_start(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_sysसमयr_pcm *dpcm = substream->runसमय->निजी_data;
	spin_lock(&dpcm->lock);
	dpcm->base_समय = jअगरfies;
	dummy_sysसमयr_rearm(dpcm);
	spin_unlock(&dpcm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_sysसमयr_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_sysसमयr_pcm *dpcm = substream->runसमय->निजी_data;
	spin_lock(&dpcm->lock);
	del_समयr(&dpcm->समयr);
	spin_unlock(&dpcm->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_sysसमयr_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dummy_sysसमयr_pcm *dpcm = runसमय->निजी_data;

	dpcm->frac_pos = 0;
	dpcm->rate = runसमय->rate;
	dpcm->frac_buffer_size = runसमय->buffer_size * HZ;
	dpcm->frac_period_size = runसमय->period_size * HZ;
	dpcm->frac_period_rest = dpcm->frac_period_size;
	dpcm->elapsed = 0;

	वापस 0;
पूर्ण

अटल व्योम dummy_sysसमयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा dummy_sysसमयr_pcm *dpcm = from_समयr(dpcm, t, समयr);
	अचिन्हित दीर्घ flags;
	पूर्णांक elapsed = 0;
	
	spin_lock_irqsave(&dpcm->lock, flags);
	dummy_sysसमयr_update(dpcm);
	dummy_sysसमयr_rearm(dpcm);
	elapsed = dpcm->elapsed;
	dpcm->elapsed = 0;
	spin_unlock_irqrestore(&dpcm->lock, flags);
	अगर (elapsed)
		snd_pcm_period_elapsed(dpcm->substream);
पूर्ण

अटल snd_pcm_uframes_t
dummy_sysसमयr_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_sysसमयr_pcm *dpcm = substream->runसमय->निजी_data;
	snd_pcm_uframes_t pos;

	spin_lock(&dpcm->lock);
	dummy_sysसमयr_update(dpcm);
	pos = dpcm->frac_pos / HZ;
	spin_unlock(&dpcm->lock);
	वापस pos;
पूर्ण

अटल पूर्णांक dummy_sysसमयr_create(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_sysसमयr_pcm *dpcm;

	dpcm = kzalloc(माप(*dpcm), GFP_KERNEL);
	अगर (!dpcm)
		वापस -ENOMEM;
	substream->runसमय->निजी_data = dpcm;
	समयr_setup(&dpcm->समयr, dummy_sysसमयr_callback, 0);
	spin_lock_init(&dpcm->lock);
	dpcm->substream = substream;
	वापस 0;
पूर्ण

अटल व्योम dummy_sysसमयr_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	kमुक्त(substream->runसमय->निजी_data);
पूर्ण

अटल स्थिर काष्ठा dummy_समयr_ops dummy_sysसमयr_ops = अणु
	.create =	dummy_sysसमयr_create,
	.मुक्त =		dummy_sysसमयr_मुक्त,
	.prepare =	dummy_sysसमयr_prepare,
	.start =	dummy_sysसमयr_start,
	.stop =		dummy_sysसमयr_stop,
	.poपूर्णांकer =	dummy_sysसमयr_poपूर्णांकer,
पूर्ण;

#अगर_घोषित CONFIG_HIGH_RES_TIMERS
/*
 * hrसमयr पूर्णांकerface
 */

काष्ठा dummy_hrसमयr_pcm अणु
	/* ops must be the first item */
	स्थिर काष्ठा dummy_समयr_ops *समयr_ops;
	kसमय_प्रकार base_समय;
	kसमय_प्रकार period_समय;
	atomic_t running;
	काष्ठा hrसमयr समयr;
	काष्ठा snd_pcm_substream *substream;
पूर्ण;

अटल क्रमागत hrसमयr_restart dummy_hrसमयr_callback(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा dummy_hrसमयr_pcm *dpcm;

	dpcm = container_of(समयr, काष्ठा dummy_hrसमयr_pcm, समयr);
	अगर (!atomic_पढ़ो(&dpcm->running))
		वापस HRTIMER_NORESTART;
	/*
	 * In हालs of XRUN and draining, this calls .trigger to stop PCM
	 * substream.
	 */
	snd_pcm_period_elapsed(dpcm->substream);
	अगर (!atomic_पढ़ो(&dpcm->running))
		वापस HRTIMER_NORESTART;

	hrसमयr_क्रमward_now(समयr, dpcm->period_समय);
	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक dummy_hrसमयr_start(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_hrसमयr_pcm *dpcm = substream->runसमय->निजी_data;

	dpcm->base_समय = hrसमयr_cb_get_समय(&dpcm->समयr);
	hrसमयr_start(&dpcm->समयr, dpcm->period_समय, HRTIMER_MODE_REL_SOFT);
	atomic_set(&dpcm->running, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_hrसमयr_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_hrसमयr_pcm *dpcm = substream->runसमय->निजी_data;

	atomic_set(&dpcm->running, 0);
	अगर (!hrसमयr_callback_running(&dpcm->समयr))
		hrसमयr_cancel(&dpcm->समयr);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dummy_hrसमयr_sync(काष्ठा dummy_hrसमयr_pcm *dpcm)
अणु
	hrसमयr_cancel(&dpcm->समयr);
पूर्ण

अटल snd_pcm_uframes_t
dummy_hrसमयr_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dummy_hrसमयr_pcm *dpcm = runसमय->निजी_data;
	u64 delta;
	u32 pos;

	delta = kसमय_us_delta(hrसमयr_cb_get_समय(&dpcm->समयr),
			       dpcm->base_समय);
	delta = भाग_u64(delta * runसमय->rate + 999999, 1000000);
	भाग_u64_rem(delta, runसमय->buffer_size, &pos);
	वापस pos;
पूर्ण

अटल पूर्णांक dummy_hrसमयr_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dummy_hrसमयr_pcm *dpcm = runसमय->निजी_data;
	अचिन्हित पूर्णांक period, rate;
	दीर्घ sec;
	अचिन्हित दीर्घ nsecs;

	dummy_hrसमयr_sync(dpcm);
	period = runसमय->period_size;
	rate = runसमय->rate;
	sec = period / rate;
	period %= rate;
	nsecs = भाग_u64((u64)period * 1000000000UL + rate - 1, rate);
	dpcm->period_समय = kसमय_set(sec, nsecs);

	वापस 0;
पूर्ण

अटल पूर्णांक dummy_hrसमयr_create(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_hrसमयr_pcm *dpcm;

	dpcm = kzalloc(माप(*dpcm), GFP_KERNEL);
	अगर (!dpcm)
		वापस -ENOMEM;
	substream->runसमय->निजी_data = dpcm;
	hrसमयr_init(&dpcm->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_SOFT);
	dpcm->समयr.function = dummy_hrसमयr_callback;
	dpcm->substream = substream;
	atomic_set(&dpcm->running, 0);
	वापस 0;
पूर्ण

अटल व्योम dummy_hrसमयr_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा dummy_hrसमयr_pcm *dpcm = substream->runसमय->निजी_data;
	dummy_hrसमयr_sync(dpcm);
	kमुक्त(dpcm);
पूर्ण

अटल स्थिर काष्ठा dummy_समयr_ops dummy_hrसमयr_ops = अणु
	.create =	dummy_hrसमयr_create,
	.मुक्त =		dummy_hrसमयr_मुक्त,
	.prepare =	dummy_hrसमयr_prepare,
	.start =	dummy_hrसमयr_start,
	.stop =		dummy_hrसमयr_stop,
	.poपूर्णांकer =	dummy_hrसमयr_poपूर्णांकer,
पूर्ण;

#पूर्ण_अगर /* CONFIG_HIGH_RES_TIMERS */

/*
 * PCM पूर्णांकerface
 */

अटल पूर्णांक dummy_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		वापस get_dummy_ops(substream)->start(substream);
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		वापस get_dummy_ops(substream)->stop(substream);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dummy_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस get_dummy_ops(substream)->prepare(substream);
पूर्ण

अटल snd_pcm_uframes_t dummy_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	वापस get_dummy_ops(substream)->poपूर्णांकer(substream);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware dummy_pcm_hardware = अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		USE_FORMATS,
	.rates =		USE_RATE,
	.rate_min =		USE_RATE_MIN,
	.rate_max =		USE_RATE_MAX,
	.channels_min =		USE_CHANNELS_MIN,
	.channels_max =		USE_CHANNELS_MAX,
	.buffer_bytes_max =	MAX_BUFFER_SIZE,
	.period_bytes_min =	MIN_PERIOD_SIZE,
	.period_bytes_max =	MAX_PERIOD_SIZE,
	.periods_min =		USE_PERIODS_MIN,
	.periods_max =		USE_PERIODS_MAX,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक dummy_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *hw_params)
अणु
	अगर (fake_buffer) अणु
		/* runसमय->dma_bytes has to be set manually to allow mmap */
		substream->runसमय->dma_bytes = params_buffer_bytes(hw_params);
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dummy *dummy = snd_pcm_substream_chip(substream);
	स्थिर काष्ठा dummy_model *model = dummy->model;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	स्थिर काष्ठा dummy_समयr_ops *ops;
	पूर्णांक err;

	ops = &dummy_sysसमयr_ops;
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
	अगर (hrसमयr)
		ops = &dummy_hrसमयr_ops;
#पूर्ण_अगर

	err = ops->create(substream);
	अगर (err < 0)
		वापस err;
	get_dummy_ops(substream) = ops;

	runसमय->hw = dummy->pcm_hw;
	अगर (substream->pcm->device & 1) अणु
		runसमय->hw.info &= ~SNDRV_PCM_INFO_INTERLEAVED;
		runसमय->hw.info |= SNDRV_PCM_INFO_NONINTERLEAVED;
	पूर्ण
	अगर (substream->pcm->device & 2)
		runसमय->hw.info &= ~(SNDRV_PCM_INFO_MMAP |
				      SNDRV_PCM_INFO_MMAP_VALID);

	अगर (model == शून्य)
		वापस 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (model->playback_स्थिरraपूर्णांकs)
			err = model->playback_स्थिरraपूर्णांकs(substream->runसमय);
	पूर्ण अन्यथा अणु
		अगर (model->capture_स्थिरraपूर्णांकs)
			err = model->capture_स्थिरraपूर्णांकs(substream->runसमय);
	पूर्ण
	अगर (err < 0) अणु
		get_dummy_ops(substream)->मुक्त(substream);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	get_dummy_ops(substream)->मुक्त(substream);
	वापस 0;
पूर्ण

/*
 * dummy buffer handling
 */

अटल व्योम *dummy_page[2];

अटल व्योम मुक्त_fake_buffer(व्योम)
अणु
	अगर (fake_buffer) अणु
		पूर्णांक i;
		क्रम (i = 0; i < 2; i++)
			अगर (dummy_page[i]) अणु
				मुक्त_page((अचिन्हित दीर्घ)dummy_page[i]);
				dummy_page[i] = शून्य;
			पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_fake_buffer(व्योम)
अणु
	पूर्णांक i;

	अगर (!fake_buffer)
		वापस 0;
	क्रम (i = 0; i < 2; i++) अणु
		dummy_page[i] = (व्योम *)get_zeroed_page(GFP_KERNEL);
		अगर (!dummy_page[i]) अणु
			मुक्त_fake_buffer();
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dummy_pcm_copy(काष्ठा snd_pcm_substream *substream,
			  पूर्णांक channel, अचिन्हित दीर्घ pos,
			  व्योम __user *dst, अचिन्हित दीर्घ bytes)
अणु
	वापस 0; /* करो nothing */
पूर्ण

अटल पूर्णांक dummy_pcm_copy_kernel(काष्ठा snd_pcm_substream *substream,
				 पूर्णांक channel, अचिन्हित दीर्घ pos,
				 व्योम *dst, अचिन्हित दीर्घ bytes)
अणु
	वापस 0; /* करो nothing */
पूर्ण

अटल पूर्णांक dummy_pcm_silence(काष्ठा snd_pcm_substream *substream,
			     पूर्णांक channel, अचिन्हित दीर्घ pos,
			     अचिन्हित दीर्घ bytes)
अणु
	वापस 0; /* करो nothing */
पूर्ण

अटल काष्ठा page *dummy_pcm_page(काष्ठा snd_pcm_substream *substream,
				   अचिन्हित दीर्घ offset)
अणु
	वापस virt_to_page(dummy_page[substream->stream]); /* the same page */
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops dummy_pcm_ops = अणु
	.खोलो =		dummy_pcm_खोलो,
	.बंद =	dummy_pcm_बंद,
	.hw_params =	dummy_pcm_hw_params,
	.prepare =	dummy_pcm_prepare,
	.trigger =	dummy_pcm_trigger,
	.poपूर्णांकer =	dummy_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops dummy_pcm_ops_no_buf = अणु
	.खोलो =		dummy_pcm_खोलो,
	.बंद =	dummy_pcm_बंद,
	.hw_params =	dummy_pcm_hw_params,
	.prepare =	dummy_pcm_prepare,
	.trigger =	dummy_pcm_trigger,
	.poपूर्णांकer =	dummy_pcm_poपूर्णांकer,
	.copy_user =	dummy_pcm_copy,
	.copy_kernel =	dummy_pcm_copy_kernel,
	.fill_silence =	dummy_pcm_silence,
	.page =		dummy_pcm_page,
पूर्ण;

अटल पूर्णांक snd_card_dummy_pcm(काष्ठा snd_dummy *dummy, पूर्णांक device,
			      पूर्णांक substreams)
अणु
	काष्ठा snd_pcm *pcm;
	स्थिर काष्ठा snd_pcm_ops *ops;
	पूर्णांक err;

	err = snd_pcm_new(dummy->card, "Dummy PCM", device,
			       substreams, substreams, &pcm);
	अगर (err < 0)
		वापस err;
	dummy->pcm = pcm;
	अगर (fake_buffer)
		ops = &dummy_pcm_ops_no_buf;
	अन्यथा
		ops = &dummy_pcm_ops;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, ops);
	pcm->निजी_data = dummy;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "Dummy PCM");
	अगर (!fake_buffer) अणु
		snd_pcm_set_managed_buffer_all(pcm,
			SNDRV_DMA_TYPE_CONTINUOUS,
			शून्य,
			0, 64*1024);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * mixer पूर्णांकerface
 */

#घोषणा DUMMY_VOLUME(xname, xindex, addr) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .index = xindex, \
  .info = snd_dummy_volume_info, \
  .get = snd_dummy_volume_get, .put = snd_dummy_volume_put, \
  .निजी_value = addr, \
  .tlv = अणु .p = db_scale_dummy पूर्ण पूर्ण

अटल पूर्णांक snd_dummy_volume_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = -50;
	uinfo->value.पूर्णांकeger.max = 100;
	वापस 0;
पूर्ण
 
अटल पूर्णांक snd_dummy_volume_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dummy *dummy = snd_kcontrol_chip(kcontrol);
	पूर्णांक addr = kcontrol->निजी_value;

	spin_lock_irq(&dummy->mixer_lock);
	ucontrol->value.पूर्णांकeger.value[0] = dummy->mixer_volume[addr][0];
	ucontrol->value.पूर्णांकeger.value[1] = dummy->mixer_volume[addr][1];
	spin_unlock_irq(&dummy->mixer_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_dummy_volume_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dummy *dummy = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, addr = kcontrol->निजी_value;
	पूर्णांक left, right;

	left = ucontrol->value.पूर्णांकeger.value[0];
	अगर (left < -50)
		left = -50;
	अगर (left > 100)
		left = 100;
	right = ucontrol->value.पूर्णांकeger.value[1];
	अगर (right < -50)
		right = -50;
	अगर (right > 100)
		right = 100;
	spin_lock_irq(&dummy->mixer_lock);
	change = dummy->mixer_volume[addr][0] != left ||
	         dummy->mixer_volume[addr][1] != right;
	dummy->mixer_volume[addr][0] = left;
	dummy->mixer_volume[addr][1] = right;
	spin_unlock_irq(&dummy->mixer_lock);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_dummy, -4500, 30, 0);

#घोषणा DUMMY_CAPSRC(xname, xindex, addr) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_dummy_capsrc_info, \
  .get = snd_dummy_capsrc_get, .put = snd_dummy_capsrc_put, \
  .निजी_value = addr पूर्ण

#घोषणा snd_dummy_capsrc_info	snd_ctl_boolean_stereo_info
 
अटल पूर्णांक snd_dummy_capsrc_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dummy *dummy = snd_kcontrol_chip(kcontrol);
	पूर्णांक addr = kcontrol->निजी_value;

	spin_lock_irq(&dummy->mixer_lock);
	ucontrol->value.पूर्णांकeger.value[0] = dummy->capture_source[addr][0];
	ucontrol->value.पूर्णांकeger.value[1] = dummy->capture_source[addr][1];
	spin_unlock_irq(&dummy->mixer_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_dummy_capsrc_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dummy *dummy = snd_kcontrol_chip(kcontrol);
	पूर्णांक change, addr = kcontrol->निजी_value;
	पूर्णांक left, right;

	left = ucontrol->value.पूर्णांकeger.value[0] & 1;
	right = ucontrol->value.पूर्णांकeger.value[1] & 1;
	spin_lock_irq(&dummy->mixer_lock);
	change = dummy->capture_source[addr][0] != left &&
	         dummy->capture_source[addr][1] != right;
	dummy->capture_source[addr][0] = left;
	dummy->capture_source[addr][1] = right;
	spin_unlock_irq(&dummy->mixer_lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_dummy_iobox_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु "None", "CD Player" पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक snd_dummy_iobox_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_dummy *dummy = snd_kcontrol_chip(kcontrol);

	value->value.क्रमागतerated.item[0] = dummy->iobox;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_dummy_iobox_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_dummy *dummy = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed;

	अगर (value->value.क्रमागतerated.item[0] > 1)
		वापस -EINVAL;

	changed = value->value.क्रमागतerated.item[0] != dummy->iobox;
	अगर (changed) अणु
		dummy->iobox = value->value.क्रमागतerated.item[0];

		अगर (dummy->iobox) अणु
			dummy->cd_volume_ctl->vd[0].access &=
				~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
			dummy->cd_चयन_ctl->vd[0].access &=
				~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		पूर्ण अन्यथा अणु
			dummy->cd_volume_ctl->vd[0].access |=
				SNDRV_CTL_ELEM_ACCESS_INACTIVE;
			dummy->cd_चयन_ctl->vd[0].access |=
				SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		पूर्ण

		snd_ctl_notअगरy(dummy->card, SNDRV_CTL_EVENT_MASK_INFO,
			       &dummy->cd_volume_ctl->id);
		snd_ctl_notअगरy(dummy->card, SNDRV_CTL_EVENT_MASK_INFO,
			       &dummy->cd_चयन_ctl->id);
	पूर्ण

	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_dummy_controls[] = अणु
DUMMY_VOLUME("Master Volume", 0, MIXER_ADDR_MASTER),
DUMMY_CAPSRC("Master Capture Switch", 0, MIXER_ADDR_MASTER),
DUMMY_VOLUME("Synth Volume", 0, MIXER_ADDR_SYNTH),
DUMMY_CAPSRC("Synth Capture Switch", 0, MIXER_ADDR_SYNTH),
DUMMY_VOLUME("Line Volume", 0, MIXER_ADDR_LINE),
DUMMY_CAPSRC("Line Capture Switch", 0, MIXER_ADDR_LINE),
DUMMY_VOLUME("Mic Volume", 0, MIXER_ADDR_MIC),
DUMMY_CAPSRC("Mic Capture Switch", 0, MIXER_ADDR_MIC),
DUMMY_VOLUME("CD Volume", 0, MIXER_ADDR_CD),
DUMMY_CAPSRC("CD Capture Switch", 0, MIXER_ADDR_CD),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name  = "External I/O Box",
	.info  = snd_dummy_iobox_info,
	.get   = snd_dummy_iobox_get,
	.put   = snd_dummy_iobox_put,
पूर्ण,
पूर्ण;

अटल पूर्णांक snd_card_dummy_new_mixer(काष्ठा snd_dummy *dummy)
अणु
	काष्ठा snd_card *card = dummy->card;
	काष्ठा snd_kcontrol *kcontrol;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	spin_lock_init(&dummy->mixer_lock);
	म_नकल(card->mixername, "Dummy Mixer");
	dummy->iobox = 1;

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_dummy_controls); idx++) अणु
		kcontrol = snd_ctl_new1(&snd_dummy_controls[idx], dummy);
		err = snd_ctl_add(card, kcontrol);
		अगर (err < 0)
			वापस err;
		अगर (!म_भेद(kcontrol->id.name, "CD Volume"))
			dummy->cd_volume_ctl = kcontrol;
		अन्यथा अगर (!म_भेद(kcontrol->id.name, "CD Capture Switch"))
			dummy->cd_चयन_ctl = kcontrol;

	पूर्ण
	वापस 0;
पूर्ण

#अगर defined(CONFIG_SND_DEBUG) && defined(CONFIG_SND_PROC_FS)
/*
 * proc पूर्णांकerface
 */
अटल व्योम prपूर्णांक_क्रमmats(काष्ठा snd_dummy *dummy,
			  काष्ठा snd_info_buffer *buffer)
अणु
	snd_pcm_क्रमmat_t i;

	pcm_क्रम_each_क्रमmat(i) अणु
		अगर (dummy->pcm_hw.क्रमmats & pcm_क्रमmat_to_bits(i))
			snd_iम_लिखो(buffer, " %s", snd_pcm_क्रमmat_name(i));
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_rates(काष्ठा snd_dummy *dummy,
			काष्ठा snd_info_buffer *buffer)
अणु
	अटल स्थिर पूर्णांक rates[] = अणु
		5512, 8000, 11025, 16000, 22050, 32000, 44100, 48000,
		64000, 88200, 96000, 176400, 192000,
	पूर्ण;
	पूर्णांक i;

	अगर (dummy->pcm_hw.rates & SNDRV_PCM_RATE_CONTINUOUS)
		snd_iम_लिखो(buffer, " continuous");
	अगर (dummy->pcm_hw.rates & SNDRV_PCM_RATE_KNOT)
		snd_iम_लिखो(buffer, " knot");
	क्रम (i = 0; i < ARRAY_SIZE(rates); i++)
		अगर (dummy->pcm_hw.rates & (1 << i))
			snd_iम_लिखो(buffer, " %d", rates[i]);
पूर्ण

#घोषणा get_dummy_पूर्णांक_ptr(dummy, ofs) \
	(अचिन्हित पूर्णांक *)((अक्षर *)&((dummy)->pcm_hw) + (ofs))
#घोषणा get_dummy_ll_ptr(dummy, ofs) \
	(अचिन्हित दीर्घ दीर्घ *)((अक्षर *)&((dummy)->pcm_hw) + (ofs))

काष्ठा dummy_hw_field अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *क्रमmat;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
पूर्ण;
#घोषणा FIELD_ENTRY(item, fmt) अणु		   \
	.name = #item,				   \
	.क्रमmat = fmt,				   \
	.offset = दुरत्व(काष्ठा snd_pcm_hardware, item), \
	.size = माप(dummy_pcm_hardware.item) पूर्ण

अटल स्थिर काष्ठा dummy_hw_field fields[] = अणु
	FIELD_ENTRY(क्रमmats, "%#llx"),
	FIELD_ENTRY(rates, "%#x"),
	FIELD_ENTRY(rate_min, "%d"),
	FIELD_ENTRY(rate_max, "%d"),
	FIELD_ENTRY(channels_min, "%d"),
	FIELD_ENTRY(channels_max, "%d"),
	FIELD_ENTRY(buffer_bytes_max, "%ld"),
	FIELD_ENTRY(period_bytes_min, "%ld"),
	FIELD_ENTRY(period_bytes_max, "%ld"),
	FIELD_ENTRY(periods_min, "%d"),
	FIELD_ENTRY(periods_max, "%d"),
पूर्ण;

अटल व्योम dummy_proc_पढ़ो(काष्ठा snd_info_entry *entry,
			    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_dummy *dummy = entry->निजी_data;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fields); i++) अणु
		snd_iम_लिखो(buffer, "%s ", fields[i].name);
		अगर (fields[i].size == माप(पूर्णांक))
			snd_iम_लिखो(buffer, fields[i].क्रमmat,
				*get_dummy_पूर्णांक_ptr(dummy, fields[i].offset));
		अन्यथा
			snd_iम_लिखो(buffer, fields[i].क्रमmat,
				*get_dummy_ll_ptr(dummy, fields[i].offset));
		अगर (!म_भेद(fields[i].name, "formats"))
			prपूर्णांक_क्रमmats(dummy, buffer);
		अन्यथा अगर (!म_भेद(fields[i].name, "rates"))
			prपूर्णांक_rates(dummy, buffer);
		snd_iम_लिखो(buffer, "\n");
	पूर्ण
पूर्ण

अटल व्योम dummy_proc_ग_लिखो(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_dummy *dummy = entry->निजी_data;
	अक्षर line[64];

	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अक्षर item[20];
		स्थिर अक्षर *ptr;
		अचिन्हित दीर्घ दीर्घ val;
		पूर्णांक i;

		ptr = snd_info_get_str(item, line, माप(item));
		क्रम (i = 0; i < ARRAY_SIZE(fields); i++) अणु
			अगर (!म_भेद(item, fields[i].name))
				अवरोध;
		पूर्ण
		अगर (i >= ARRAY_SIZE(fields))
			जारी;
		snd_info_get_str(item, ptr, माप(item));
		अगर (kम_से_अदीर्घl(item, 0, &val))
			जारी;
		अगर (fields[i].size == माप(पूर्णांक))
			*get_dummy_पूर्णांक_ptr(dummy, fields[i].offset) = val;
		अन्यथा
			*get_dummy_ll_ptr(dummy, fields[i].offset) = val;
	पूर्ण
पूर्ण

अटल व्योम dummy_proc_init(काष्ठा snd_dummy *chip)
अणु
	snd_card_rw_proc_new(chip->card, "dummy_pcm", chip,
			     dummy_proc_पढ़ो, dummy_proc_ग_लिखो);
पूर्ण
#अन्यथा
#घोषणा dummy_proc_init(x)
#पूर्ण_अगर /* CONFIG_SND_DEBUG && CONFIG_SND_PROC_FS */

अटल पूर्णांक snd_dummy_probe(काष्ठा platक्रमm_device *devptr)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_dummy *dummy;
	स्थिर काष्ठा dummy_model *m = शून्य, **mdl;
	पूर्णांक idx, err;
	पूर्णांक dev = devptr->id;

	err = snd_card_new(&devptr->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_dummy), &card);
	अगर (err < 0)
		वापस err;
	dummy = card->निजी_data;
	dummy->card = card;
	क्रम (mdl = dummy_models; *mdl && model[dev]; mdl++) अणु
		अगर (म_भेद(model[dev], (*mdl)->name) == 0) अणु
			prपूर्णांकk(KERN_INFO
				"snd-dummy: Using model '%s' for card %i\n",
				(*mdl)->name, card->number);
			m = dummy->model = *mdl;
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (idx = 0; idx < MAX_PCM_DEVICES && idx < pcm_devs[dev]; idx++) अणु
		अगर (pcm_substreams[dev] < 1)
			pcm_substreams[dev] = 1;
		अगर (pcm_substreams[dev] > MAX_PCM_SUBSTREAMS)
			pcm_substreams[dev] = MAX_PCM_SUBSTREAMS;
		err = snd_card_dummy_pcm(dummy, idx, pcm_substreams[dev]);
		अगर (err < 0)
			जाओ __nodev;
	पूर्ण

	dummy->pcm_hw = dummy_pcm_hardware;
	अगर (m) अणु
		अगर (m->क्रमmats)
			dummy->pcm_hw.क्रमmats = m->क्रमmats;
		अगर (m->buffer_bytes_max)
			dummy->pcm_hw.buffer_bytes_max = m->buffer_bytes_max;
		अगर (m->period_bytes_min)
			dummy->pcm_hw.period_bytes_min = m->period_bytes_min;
		अगर (m->period_bytes_max)
			dummy->pcm_hw.period_bytes_max = m->period_bytes_max;
		अगर (m->periods_min)
			dummy->pcm_hw.periods_min = m->periods_min;
		अगर (m->periods_max)
			dummy->pcm_hw.periods_max = m->periods_max;
		अगर (m->rates)
			dummy->pcm_hw.rates = m->rates;
		अगर (m->rate_min)
			dummy->pcm_hw.rate_min = m->rate_min;
		अगर (m->rate_max)
			dummy->pcm_hw.rate_max = m->rate_max;
		अगर (m->channels_min)
			dummy->pcm_hw.channels_min = m->channels_min;
		अगर (m->channels_max)
			dummy->pcm_hw.channels_max = m->channels_max;
	पूर्ण

	err = snd_card_dummy_new_mixer(dummy);
	अगर (err < 0)
		जाओ __nodev;
	म_नकल(card->driver, "Dummy");
	म_नकल(card->लघुname, "Dummy");
	प्र_लिखो(card->दीर्घname, "Dummy %i", dev + 1);

	dummy_proc_init(dummy);

	err = snd_card_रेजिस्टर(card);
	अगर (err == 0) अणु
		platक्रमm_set_drvdata(devptr, card);
		वापस 0;
	पूर्ण
      __nodev:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक snd_dummy_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_dummy_suspend(काष्ठा device *pdev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	वापस 0;
पूर्ण
	
अटल पूर्णांक snd_dummy_resume(काष्ठा device *pdev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_dummy_pm, snd_dummy_suspend, snd_dummy_resume);
#घोषणा SND_DUMMY_PM_OPS	&snd_dummy_pm
#अन्यथा
#घोषणा SND_DUMMY_PM_OPS	शून्य
#पूर्ण_अगर

#घोषणा SND_DUMMY_DRIVER	"snd_dummy"

अटल काष्ठा platक्रमm_driver snd_dummy_driver = अणु
	.probe		= snd_dummy_probe,
	.हटाओ		= snd_dummy_हटाओ,
	.driver		= अणु
		.name	= SND_DUMMY_DRIVER,
		.pm	= SND_DUMMY_PM_OPS,
	पूर्ण,
पूर्ण;

अटल व्योम snd_dummy_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(devices); ++i)
		platक्रमm_device_unरेजिस्टर(devices[i]);
	platक्रमm_driver_unरेजिस्टर(&snd_dummy_driver);
	मुक्त_fake_buffer();
पूर्ण

अटल पूर्णांक __init alsa_card_dummy_init(व्योम)
अणु
	पूर्णांक i, cards, err;

	err = platक्रमm_driver_रेजिस्टर(&snd_dummy_driver);
	अगर (err < 0)
		वापस err;

	err = alloc_fake_buffer();
	अगर (err < 0) अणु
		platक्रमm_driver_unरेजिस्टर(&snd_dummy_driver);
		वापस err;
	पूर्ण

	cards = 0;
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		काष्ठा platक्रमm_device *device;
		अगर (! enable[i])
			जारी;
		device = platक्रमm_device_रेजिस्टर_simple(SND_DUMMY_DRIVER,
							 i, शून्य, 0);
		अगर (IS_ERR(device))
			जारी;
		अगर (!platक्रमm_get_drvdata(device)) अणु
			platक्रमm_device_unरेजिस्टर(device);
			जारी;
		पूर्ण
		devices[i] = device;
		cards++;
	पूर्ण
	अगर (!cards) अणु
#अगर_घोषित MODULE
		prपूर्णांकk(KERN_ERR "Dummy soundcard not found or device busy\n");
#पूर्ण_अगर
		snd_dummy_unरेजिस्टर_all();
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_dummy_निकास(व्योम)
अणु
	snd_dummy_unरेजिस्टर_all();
पूर्ण

module_init(alsa_card_dummy_init)
module_निकास(alsa_card_dummy_निकास)
