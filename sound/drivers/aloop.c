<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Loopback soundcard
 *
 *  Original code:
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
 *  More accurate positioning and full-duplex support:
 *  Copyright (c) Ahmet दओnan <ainan at mathematik.uni-freiburg.de>
 *
 *  Major (almost complete) reग_लिखो:
 *  Copyright (c) by Takashi Iwai <tiwai@suse.de>
 *
 *  A next major update in 2010 (separate समयrs क्रम playback and capture):
 *  Copyright (c) Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>
#समावेश <sound/समयr.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("A loopback soundcard");
MODULE_LICENSE("GPL");

#घोषणा MAX_PCM_SUBSTREAMS	8

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = अणु1, [1 ... (SNDRV_CARDS - 1)] = 0पूर्ण;
अटल पूर्णांक pcm_substreams[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 8पूर्ण;
अटल पूर्णांक pcm_notअगरy[SNDRV_CARDS];
अटल अक्षर *समयr_source[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for loopback soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for loopback soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable this loopback soundcard.");
module_param_array(pcm_substreams, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_substreams, "PCM substreams # (1-8) for loopback driver.");
module_param_array(pcm_notअगरy, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_notअगरy, "Break capture when PCM format/rate/channels changes.");
module_param_array(समयr_source, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(समयr_source, "Sound card name or number and device/subdevice number of timer to be used. Empty string for jiffies timer [default].");

#घोषणा NO_PITCH 100000

#घोषणा CABLE_VALID_PLAYBACK	BIT(SNDRV_PCM_STREAM_PLAYBACK)
#घोषणा CABLE_VALID_CAPTURE	BIT(SNDRV_PCM_STREAM_CAPTURE)
#घोषणा CABLE_VALID_BOTH	(CABLE_VALID_PLAYBACK | CABLE_VALID_CAPTURE)

काष्ठा loopback_cable;
काष्ठा loopback_pcm;

काष्ठा loopback_ops अणु
	/* optional
	 * call in loopback->cable_lock
	 */
	पूर्णांक (*खोलो)(काष्ठा loopback_pcm *dpcm);
	/* required
	 * call in cable->lock
	 */
	पूर्णांक (*start)(काष्ठा loopback_pcm *dpcm);
	/* required
	 * call in cable->lock
	 */
	पूर्णांक (*stop)(काष्ठा loopback_pcm *dpcm);
	/* optional */
	पूर्णांक (*stop_sync)(काष्ठा loopback_pcm *dpcm);
	/* optional */
	पूर्णांक (*बंद_substream)(काष्ठा loopback_pcm *dpcm);
	/* optional
	 * call in loopback->cable_lock
	 */
	पूर्णांक (*बंद_cable)(काष्ठा loopback_pcm *dpcm);
	/* optional
	 * call in cable->lock
	 */
	अचिन्हित पूर्णांक (*pos_update)(काष्ठा loopback_cable *cable);
	/* optional */
	व्योम (*dpcm_info)(काष्ठा loopback_pcm *dpcm,
			  काष्ठा snd_info_buffer *buffer);
पूर्ण;

काष्ठा loopback_cable अणु
	spinlock_t lock;
	काष्ठा loopback_pcm *streams[2];
	काष्ठा snd_pcm_hardware hw;
	/* flags */
	अचिन्हित पूर्णांक valid;
	अचिन्हित पूर्णांक running;
	अचिन्हित पूर्णांक छोड़ो;
	/* समयr specअगरic */
	स्थिर काष्ठा loopback_ops *ops;
	/* If sound समयr is used */
	काष्ठा अणु
		पूर्णांक stream;
		काष्ठा snd_समयr_id id;
		काष्ठा work_काष्ठा event_work;
		काष्ठा snd_समयr_instance *instance;
	पूर्ण snd_समयr;
पूर्ण;

काष्ठा loopback_setup अणु
	अचिन्हित पूर्णांक notअगरy: 1;
	अचिन्हित पूर्णांक rate_shअगरt;
	snd_pcm_क्रमmat_t क्रमmat;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक channels;
	काष्ठा snd_ctl_elem_id active_id;
	काष्ठा snd_ctl_elem_id क्रमmat_id;
	काष्ठा snd_ctl_elem_id rate_id;
	काष्ठा snd_ctl_elem_id channels_id;
पूर्ण;

काष्ठा loopback अणु
	काष्ठा snd_card *card;
	काष्ठा mutex cable_lock;
	काष्ठा loopback_cable *cables[MAX_PCM_SUBSTREAMS][2];
	काष्ठा snd_pcm *pcm[2];
	काष्ठा loopback_setup setup[MAX_PCM_SUBSTREAMS][2];
	स्थिर अक्षर *समयr_source;
पूर्ण;

काष्ठा loopback_pcm अणु
	काष्ठा loopback *loopback;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा loopback_cable *cable;
	अचिन्हित पूर्णांक pcm_buffer_size;
	अचिन्हित पूर्णांक buf_pos;	/* position in buffer */
	अचिन्हित पूर्णांक silent_size;
	/* PCM parameters */
	अचिन्हित पूर्णांक pcm_period_size;
	अचिन्हित पूर्णांक pcm_bps;		/* bytes per second */
	अचिन्हित पूर्णांक pcm_salign;	/* bytes per sample * channels */
	अचिन्हित पूर्णांक pcm_rate_shअगरt;	/* rate shअगरt value */
	/* flags */
	अचिन्हित पूर्णांक period_update_pending :1;
	/* समयr stuff */
	अचिन्हित पूर्णांक irq_pos;		/* fractional IRQ position in jअगरfies
					 * ticks
					 */
	अचिन्हित पूर्णांक period_size_frac;	/* period size in jअगरfies ticks */
	अचिन्हित पूर्णांक last_drअगरt;
	अचिन्हित दीर्घ last_jअगरfies;
	/* If jअगरfies समयr is used */
	काष्ठा समयr_list समयr;
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[SNDRV_CARDS];

अटल अंतरभूत अचिन्हित पूर्णांक byte_pos(काष्ठा loopback_pcm *dpcm, अचिन्हित पूर्णांक x)
अणु
	अगर (dpcm->pcm_rate_shअगरt == NO_PITCH) अणु
		x /= HZ;
	पूर्ण अन्यथा अणु
		x = भाग_u64(NO_PITCH * (अचिन्हित दीर्घ दीर्घ)x,
			    HZ * (अचिन्हित दीर्घ दीर्घ)dpcm->pcm_rate_shअगरt);
	पूर्ण
	वापस x - (x % dpcm->pcm_salign);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक frac_pos(काष्ठा loopback_pcm *dpcm, अचिन्हित पूर्णांक x)
अणु
	अगर (dpcm->pcm_rate_shअगरt == NO_PITCH) अणु	/* no pitch */
		वापस x * HZ;
	पूर्ण अन्यथा अणु
		x = भाग_u64(dpcm->pcm_rate_shअगरt * (अचिन्हित दीर्घ दीर्घ)x * HZ,
			    NO_PITCH);
	पूर्ण
	वापस x;
पूर्ण

अटल अंतरभूत काष्ठा loopback_setup *get_setup(काष्ठा loopback_pcm *dpcm)
अणु
	पूर्णांक device = dpcm->substream->pstr->pcm->device;
	
	अगर (dpcm->substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		device ^= 1;
	वापस &dpcm->loopback->setup[dpcm->substream->number][device];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_notअगरy(काष्ठा loopback_pcm *dpcm)
अणु
	वापस get_setup(dpcm)->notअगरy;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_rate_shअगरt(काष्ठा loopback_pcm *dpcm)
अणु
	वापस get_setup(dpcm)->rate_shअगरt;
पूर्ण

/* call in cable->lock */
अटल पूर्णांक loopback_jअगरfies_समयr_start(काष्ठा loopback_pcm *dpcm)
अणु
	अचिन्हित दीर्घ tick;
	अचिन्हित पूर्णांक rate_shअगरt = get_rate_shअगरt(dpcm);

	अगर (rate_shअगरt != dpcm->pcm_rate_shअगरt) अणु
		dpcm->pcm_rate_shअगरt = rate_shअगरt;
		dpcm->period_size_frac = frac_pos(dpcm, dpcm->pcm_period_size);
	पूर्ण
	अगर (dpcm->period_size_frac <= dpcm->irq_pos) अणु
		dpcm->irq_pos %= dpcm->period_size_frac;
		dpcm->period_update_pending = 1;
	पूर्ण
	tick = dpcm->period_size_frac - dpcm->irq_pos;
	tick = DIV_ROUND_UP(tick, dpcm->pcm_bps);
	mod_समयr(&dpcm->समयr, jअगरfies + tick);

	वापस 0;
पूर्ण

/* call in cable->lock */
अटल पूर्णांक loopback_snd_समयr_start(काष्ठा loopback_pcm *dpcm)
अणु
	काष्ठा loopback_cable *cable = dpcm->cable;
	पूर्णांक err;

	/* Loopback device has to use same period as समयr card. Thereक्रमe
	 * wake up क्रम each snd_pcm_period_elapsed() call of समयr card.
	 */
	err = snd_समयr_start(cable->snd_समयr.instance, 1);
	अगर (err < 0) अणु
		/* करो not report error अगर trying to start but alपढ़ोy
		 * running. For example called by opposite substream
		 * of the same cable
		 */
		अगर (err == -EBUSY)
			वापस 0;

		pcm_err(dpcm->substream->pcm,
			"snd_timer_start(%d,%d,%d) failed with %d",
			cable->snd_समयr.id.card,
			cable->snd_समयr.id.device,
			cable->snd_समयr.id.subdevice,
			err);
	पूर्ण

	वापस err;
पूर्ण

/* call in cable->lock */
अटल अंतरभूत पूर्णांक loopback_jअगरfies_समयr_stop(काष्ठा loopback_pcm *dpcm)
अणु
	del_समयr(&dpcm->समयr);
	dpcm->समयr.expires = 0;

	वापस 0;
पूर्ण

/* call in cable->lock */
अटल पूर्णांक loopback_snd_समयr_stop(काष्ठा loopback_pcm *dpcm)
अणु
	काष्ठा loopback_cable *cable = dpcm->cable;
	पूर्णांक err;

	/* only stop अगर both devices (playback and capture) are not running */
	अगर (cable->running ^ cable->छोड़ो)
		वापस 0;

	err = snd_समयr_stop(cable->snd_समयr.instance);
	अगर (err < 0) अणु
		pcm_err(dpcm->substream->pcm,
			"snd_timer_stop(%d,%d,%d) failed with %d",
			cable->snd_समयr.id.card,
			cable->snd_समयr.id.device,
			cable->snd_समयr.id.subdevice,
			err);
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक loopback_jअगरfies_समयr_stop_sync(काष्ठा loopback_pcm *dpcm)
अणु
	del_समयr_sync(&dpcm->समयr);

	वापस 0;
पूर्ण

/* call in loopback->cable_lock */
अटल पूर्णांक loopback_snd_समयr_बंद_cable(काष्ठा loopback_pcm *dpcm)
अणु
	काष्ठा loopback_cable *cable = dpcm->cable;

	/* snd_समयr was not खोलोed */
	अगर (!cable->snd_समयr.instance)
		वापस 0;

	/* will only be called from मुक्त_cable() when other stream was
	 * alपढ़ोy बंदd. Other stream cannot be reखोलोed as दीर्घ as
	 * loopback->cable_lock is locked. Thereक्रमe no need to lock
	 * cable->lock;
	 */
	snd_समयr_बंद(cable->snd_समयr.instance);

	/* रुको till drain work has finished अगर requested */
	cancel_work_sync(&cable->snd_समयr.event_work);

	snd_समयr_instance_मुक्त(cable->snd_समयr.instance);
	स_रखो(&cable->snd_समयr, 0, माप(cable->snd_समयr));

	वापस 0;
पूर्ण

अटल पूर्णांक loopback_check_क्रमmat(काष्ठा loopback_cable *cable, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय, *crunसमय;
	काष्ठा loopback_setup *setup;
	काष्ठा snd_card *card;
	पूर्णांक check;

	अगर (cable->valid != CABLE_VALID_BOTH) अणु
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
			जाओ __notअगरy;
		वापस 0;
	पूर्ण
	runसमय = cable->streams[SNDRV_PCM_STREAM_PLAYBACK]->
							substream->runसमय;
	crunसमय = cable->streams[SNDRV_PCM_STREAM_CAPTURE]->
							substream->runसमय;
	check = runसमय->क्रमmat != crunसमय->क्रमmat ||
		runसमय->rate != crunसमय->rate ||
		runसमय->channels != crunसमय->channels;
	अगर (!check)
		वापस 0;
	अगर (stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		वापस -EIO;
	पूर्ण अन्यथा अणु
		snd_pcm_stop(cable->streams[SNDRV_PCM_STREAM_CAPTURE]->
					substream, SNDRV_PCM_STATE_DRAINING);
	      __notअगरy:
		runसमय = cable->streams[SNDRV_PCM_STREAM_PLAYBACK]->
							substream->runसमय;
		setup = get_setup(cable->streams[SNDRV_PCM_STREAM_PLAYBACK]);
		card = cable->streams[SNDRV_PCM_STREAM_PLAYBACK]->loopback->card;
		अगर (setup->क्रमmat != runसमय->क्रमmat) अणु
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
							&setup->क्रमmat_id);
			setup->क्रमmat = runसमय->क्रमmat;
		पूर्ण
		अगर (setup->rate != runसमय->rate) अणु
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
							&setup->rate_id);
			setup->rate = runसमय->rate;
		पूर्ण
		अगर (setup->channels != runसमय->channels) अणु
			snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE,
							&setup->channels_id);
			setup->channels = runसमय->channels;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम loopback_active_notअगरy(काष्ठा loopback_pcm *dpcm)
अणु
	snd_ctl_notअगरy(dpcm->loopback->card,
		       SNDRV_CTL_EVENT_MASK_VALUE,
		       &get_setup(dpcm)->active_id);
पूर्ण

अटल पूर्णांक loopback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा loopback_pcm *dpcm = runसमय->निजी_data;
	काष्ठा loopback_cable *cable = dpcm->cable;
	पूर्णांक err = 0, stream = 1 << substream->stream;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		err = loopback_check_क्रमmat(cable, substream->stream);
		अगर (err < 0)
			वापस err;
		dpcm->last_jअगरfies = jअगरfies;
		dpcm->pcm_rate_shअगरt = 0;
		dpcm->last_drअगरt = 0;
		spin_lock(&cable->lock);	
		cable->running |= stream;
		cable->छोड़ो &= ~stream;
		err = cable->ops->start(dpcm);
		spin_unlock(&cable->lock);
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notअगरy(dpcm);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		spin_lock(&cable->lock);	
		cable->running &= ~stream;
		cable->छोड़ो &= ~stream;
		err = cable->ops->stop(dpcm);
		spin_unlock(&cable->lock);
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notअगरy(dpcm);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		spin_lock(&cable->lock);	
		cable->छोड़ो |= stream;
		err = cable->ops->stop(dpcm);
		spin_unlock(&cable->lock);
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notअगरy(dpcm);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		spin_lock(&cable->lock);
		dpcm->last_jअगरfies = jअगरfies;
		cable->छोड़ो &= ~stream;
		err = cable->ops->start(dpcm);
		spin_unlock(&cable->lock);
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			loopback_active_notअगरy(dpcm);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम params_change(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा loopback_pcm *dpcm = runसमय->निजी_data;
	काष्ठा loopback_cable *cable = dpcm->cable;

	cable->hw.क्रमmats = pcm_क्रमmat_to_bits(runसमय->क्रमmat);
	cable->hw.rate_min = runसमय->rate;
	cable->hw.rate_max = runसमय->rate;
	cable->hw.channels_min = runसमय->channels;
	cable->hw.channels_max = runसमय->channels;

	अगर (cable->snd_समयr.instance) अणु
		cable->hw.period_bytes_min =
				frames_to_bytes(runसमय, runसमय->period_size);
		cable->hw.period_bytes_max = cable->hw.period_bytes_min;
	पूर्ण

पूर्ण

अटल पूर्णांक loopback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा loopback_pcm *dpcm = runसमय->निजी_data;
	काष्ठा loopback_cable *cable = dpcm->cable;
	पूर्णांक err, bps, salign;

	अगर (cable->ops->stop_sync) अणु
		err = cable->ops->stop_sync(dpcm);
		अगर (err < 0)
			वापस err;
	पूर्ण

	salign = (snd_pcm_क्रमmat_physical_width(runसमय->क्रमmat) *
						runसमय->channels) / 8;
	bps = salign * runसमय->rate;
	अगर (bps <= 0 || salign <= 0)
		वापस -EINVAL;

	dpcm->buf_pos = 0;
	dpcm->pcm_buffer_size = frames_to_bytes(runसमय, runसमय->buffer_size);
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		/* clear capture buffer */
		dpcm->silent_size = dpcm->pcm_buffer_size;
		snd_pcm_क्रमmat_set_silence(runसमय->क्रमmat, runसमय->dma_area,
					   runसमय->buffer_size * runसमय->channels);
	पूर्ण

	dpcm->irq_pos = 0;
	dpcm->period_update_pending = 0;
	dpcm->pcm_bps = bps;
	dpcm->pcm_salign = salign;
	dpcm->pcm_period_size = frames_to_bytes(runसमय, runसमय->period_size);

	mutex_lock(&dpcm->loopback->cable_lock);
	अगर (!(cable->valid & ~(1 << substream->stream)) ||
            (get_setup(dpcm)->notअगरy &&
	     substream->stream == SNDRV_PCM_STREAM_PLAYBACK))
		params_change(substream);
	cable->valid |= 1 << substream->stream;
	mutex_unlock(&dpcm->loopback->cable_lock);

	वापस 0;
पूर्ण

अटल व्योम clear_capture_buf(काष्ठा loopback_pcm *dpcm, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = dpcm->substream->runसमय;
	अक्षर *dst = runसमय->dma_area;
	अचिन्हित पूर्णांक dst_off = dpcm->buf_pos;

	अगर (dpcm->silent_size >= dpcm->pcm_buffer_size)
		वापस;
	अगर (dpcm->silent_size + bytes > dpcm->pcm_buffer_size)
		bytes = dpcm->pcm_buffer_size - dpcm->silent_size;

	क्रम (;;) अणु
		अचिन्हित पूर्णांक size = bytes;
		अगर (dst_off + size > dpcm->pcm_buffer_size)
			size = dpcm->pcm_buffer_size - dst_off;
		snd_pcm_क्रमmat_set_silence(runसमय->क्रमmat, dst + dst_off,
					   bytes_to_frames(runसमय, size) *
					   	runसमय->channels);
		dpcm->silent_size += size;
		bytes -= size;
		अगर (!bytes)
			अवरोध;
		dst_off = 0;
	पूर्ण
पूर्ण

अटल व्योम copy_play_buf(काष्ठा loopback_pcm *play,
			  काष्ठा loopback_pcm *capt,
			  अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = play->substream->runसमय;
	अक्षर *src = runसमय->dma_area;
	अक्षर *dst = capt->substream->runसमय->dma_area;
	अचिन्हित पूर्णांक src_off = play->buf_pos;
	अचिन्हित पूर्णांक dst_off = capt->buf_pos;
	अचिन्हित पूर्णांक clear_bytes = 0;

	/* check अगर playback is draining, trim the capture copy size
	 * when our poपूर्णांकer is at the end of playback ring buffer */
	अगर (runसमय->status->state == SNDRV_PCM_STATE_DRAINING &&
	    snd_pcm_playback_hw_avail(runसमय) < runसमय->buffer_size) अणु 
	    	snd_pcm_uframes_t appl_ptr, appl_ptr1, dअगरf;
		appl_ptr = appl_ptr1 = runसमय->control->appl_ptr;
		appl_ptr1 -= appl_ptr1 % runसमय->buffer_size;
		appl_ptr1 += play->buf_pos / play->pcm_salign;
		अगर (appl_ptr < appl_ptr1)
			appl_ptr1 -= runसमय->buffer_size;
		dअगरf = (appl_ptr - appl_ptr1) * play->pcm_salign;
		अगर (dअगरf < bytes) अणु
			clear_bytes = bytes - dअगरf;
			bytes = dअगरf;
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		अचिन्हित पूर्णांक size = bytes;
		अगर (src_off + size > play->pcm_buffer_size)
			size = play->pcm_buffer_size - src_off;
		अगर (dst_off + size > capt->pcm_buffer_size)
			size = capt->pcm_buffer_size - dst_off;
		स_नकल(dst + dst_off, src + src_off, size);
		capt->silent_size = 0;
		bytes -= size;
		अगर (!bytes)
			अवरोध;
		src_off = (src_off + size) % play->pcm_buffer_size;
		dst_off = (dst_off + size) % capt->pcm_buffer_size;
	पूर्ण

	अगर (clear_bytes > 0) अणु
		clear_capture_buf(capt, clear_bytes);
		capt->silent_size = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bytepos_delta(काष्ठा loopback_pcm *dpcm,
					 अचिन्हित पूर्णांक jअगरfies_delta)
अणु
	अचिन्हित दीर्घ last_pos;
	अचिन्हित पूर्णांक delta;

	last_pos = byte_pos(dpcm, dpcm->irq_pos);
	dpcm->irq_pos += jअगरfies_delta * dpcm->pcm_bps;
	delta = byte_pos(dpcm, dpcm->irq_pos) - last_pos;
	अगर (delta >= dpcm->last_drअगरt)
		delta -= dpcm->last_drअगरt;
	dpcm->last_drअगरt = 0;
	अगर (dpcm->irq_pos >= dpcm->period_size_frac) अणु
		dpcm->irq_pos %= dpcm->period_size_frac;
		dpcm->period_update_pending = 1;
	पूर्ण
	वापस delta;
पूर्ण

अटल अंतरभूत व्योम bytepos_finish(काष्ठा loopback_pcm *dpcm,
				  अचिन्हित पूर्णांक delta)
अणु
	dpcm->buf_pos += delta;
	dpcm->buf_pos %= dpcm->pcm_buffer_size;
पूर्ण

/* call in cable->lock */
अटल अचिन्हित पूर्णांक loopback_jअगरfies_समयr_pos_update
		(काष्ठा loopback_cable *cable)
अणु
	काष्ठा loopback_pcm *dpcm_play =
			cable->streams[SNDRV_PCM_STREAM_PLAYBACK];
	काष्ठा loopback_pcm *dpcm_capt =
			cable->streams[SNDRV_PCM_STREAM_CAPTURE];
	अचिन्हित दीर्घ delta_play = 0, delta_capt = 0;
	अचिन्हित पूर्णांक running, count1, count2;

	running = cable->running ^ cable->छोड़ो;
	अगर (running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) अणु
		delta_play = jअगरfies - dpcm_play->last_jअगरfies;
		dpcm_play->last_jअगरfies += delta_play;
	पूर्ण

	अगर (running & (1 << SNDRV_PCM_STREAM_CAPTURE)) अणु
		delta_capt = jअगरfies - dpcm_capt->last_jअगरfies;
		dpcm_capt->last_jअगरfies += delta_capt;
	पूर्ण

	अगर (delta_play == 0 && delta_capt == 0)
		जाओ unlock;
		
	अगर (delta_play > delta_capt) अणु
		count1 = bytepos_delta(dpcm_play, delta_play - delta_capt);
		bytepos_finish(dpcm_play, count1);
		delta_play = delta_capt;
	पूर्ण अन्यथा अगर (delta_play < delta_capt) अणु
		count1 = bytepos_delta(dpcm_capt, delta_capt - delta_play);
		clear_capture_buf(dpcm_capt, count1);
		bytepos_finish(dpcm_capt, count1);
		delta_capt = delta_play;
	पूर्ण

	अगर (delta_play == 0 && delta_capt == 0)
		जाओ unlock;

	/* note delta_capt == delta_play at this moment */
	count1 = bytepos_delta(dpcm_play, delta_play);
	count2 = bytepos_delta(dpcm_capt, delta_capt);
	अगर (count1 < count2) अणु
		dpcm_capt->last_drअगरt = count2 - count1;
		count1 = count2;
	पूर्ण अन्यथा अगर (count1 > count2) अणु
		dpcm_play->last_drअगरt = count1 - count2;
	पूर्ण
	copy_play_buf(dpcm_play, dpcm_capt, count1);
	bytepos_finish(dpcm_play, count1);
	bytepos_finish(dpcm_capt, count1);
 unlock:
	वापस running;
पूर्ण

अटल व्योम loopback_jअगरfies_समयr_function(काष्ठा समयr_list *t)
अणु
	काष्ठा loopback_pcm *dpcm = from_समयr(dpcm, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dpcm->cable->lock, flags);
	अगर (loopback_jअगरfies_समयr_pos_update(dpcm->cable) &
			(1 << dpcm->substream->stream)) अणु
		loopback_jअगरfies_समयr_start(dpcm);
		अगर (dpcm->period_update_pending) अणु
			dpcm->period_update_pending = 0;
			spin_unlock_irqrestore(&dpcm->cable->lock, flags);
			/* need to unlock beक्रमe calling below */
			snd_pcm_period_elapsed(dpcm->substream);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dpcm->cable->lock, flags);
पूर्ण

/* call in cable->lock */
अटल पूर्णांक loopback_snd_समयr_check_resolution(काष्ठा snd_pcm_runसमय *runसमय,
					       अचिन्हित दीर्घ resolution)
अणु
	अगर (resolution != runसमय->समयr_resolution) अणु
		काष्ठा loopback_pcm *dpcm = runसमय->निजी_data;
		काष्ठा loopback_cable *cable = dpcm->cable;
		/* Worst हाल estimation of possible values क्रम resolution
		 * resolution <= (512 * 1024) frames / 8kHz in nsec
		 * resolution <= 65.536.000.000 nsec
		 *
		 * period_size <= 65.536.000.000 nsec / 1000nsec/usec * 192kHz +
		 *  500.000
		 * period_size <= 12.582.912.000.000  <64bit
		 *  / 1.000.000 usec/sec
		 */
		snd_pcm_uframes_t period_size_usec =
				resolution / 1000 * runसमय->rate;
		/* round to nearest sample rate */
		snd_pcm_uframes_t period_size =
				(period_size_usec + 500 * 1000) / (1000 * 1000);

		pcm_err(dpcm->substream->pcm,
			"Period size (%lu frames) of loopback device is not corresponding to timer resolution (%lu nsec = %lu frames) of card timer %d,%d,%d. Use period size of %lu frames for loopback device.",
			runसमय->period_size, resolution, period_size,
			cable->snd_समयr.id.card,
			cable->snd_समयr.id.device,
			cable->snd_समयr.id.subdevice,
			period_size);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम loopback_snd_समयr_period_elapsed(काष्ठा loopback_cable *cable,
					      पूर्णांक event,
					      अचिन्हित दीर्घ resolution)
अणु
	काष्ठा loopback_pcm *dpcm_play, *dpcm_capt;
	काष्ठा snd_pcm_substream *substream_play, *substream_capt;
	काष्ठा snd_pcm_runसमय *valid_runसमय;
	अचिन्हित पूर्णांक running, elapsed_bytes;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cable->lock, flags);
	running = cable->running ^ cable->छोड़ो;
	/* no need to करो anything अगर no stream is running */
	अगर (!running) अणु
		spin_unlock_irqrestore(&cable->lock, flags);
		वापस;
	पूर्ण

	dpcm_play = cable->streams[SNDRV_PCM_STREAM_PLAYBACK];
	dpcm_capt = cable->streams[SNDRV_PCM_STREAM_CAPTURE];

	अगर (event == SNDRV_TIMER_EVENT_MSTOP) अणु
		अगर (!dpcm_play ||
		    dpcm_play->substream->runसमय->status->state !=
				SNDRV_PCM_STATE_DRAINING) अणु
			spin_unlock_irqrestore(&cable->lock, flags);
			वापस;
		पूर्ण
	पूर्ण

	substream_play = (running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) ?
			dpcm_play->substream : शून्य;
	substream_capt = (running & (1 << SNDRV_PCM_STREAM_CAPTURE)) ?
			dpcm_capt->substream : शून्य;
	valid_runसमय = (running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) ?
				dpcm_play->substream->runसमय :
				dpcm_capt->substream->runसमय;

	/* resolution is only valid क्रम SNDRV_TIMER_EVENT_TICK events */
	अगर (event == SNDRV_TIMER_EVENT_TICK) अणु
		/* The hardware rules guarantee that playback and capture period
		 * are the same. Thereक्रमe only one device has to be checked
		 * here.
		 */
		अगर (loopback_snd_समयr_check_resolution(valid_runसमय,
							resolution) < 0) अणु
			spin_unlock_irqrestore(&cable->lock, flags);
			अगर (substream_play)
				snd_pcm_stop_xrun(substream_play);
			अगर (substream_capt)
				snd_pcm_stop_xrun(substream_capt);
			वापस;
		पूर्ण
	पूर्ण

	elapsed_bytes = frames_to_bytes(valid_runसमय,
					valid_runसमय->period_size);
	/* The same समयr पूर्णांकerrupt is used क्रम playback and capture device */
	अगर ((running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) &&
	    (running & (1 << SNDRV_PCM_STREAM_CAPTURE))) अणु
		copy_play_buf(dpcm_play, dpcm_capt, elapsed_bytes);
		bytepos_finish(dpcm_play, elapsed_bytes);
		bytepos_finish(dpcm_capt, elapsed_bytes);
	पूर्ण अन्यथा अगर (running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) अणु
		bytepos_finish(dpcm_play, elapsed_bytes);
	पूर्ण अन्यथा अगर (running & (1 << SNDRV_PCM_STREAM_CAPTURE)) अणु
		clear_capture_buf(dpcm_capt, elapsed_bytes);
		bytepos_finish(dpcm_capt, elapsed_bytes);
	पूर्ण
	spin_unlock_irqrestore(&cable->lock, flags);

	अगर (substream_play)
		snd_pcm_period_elapsed(substream_play);
	अगर (substream_capt)
		snd_pcm_period_elapsed(substream_capt);
पूर्ण

अटल व्योम loopback_snd_समयr_function(काष्ठा snd_समयr_instance *समयri,
					अचिन्हित दीर्घ resolution,
					अचिन्हित दीर्घ ticks)
अणु
	काष्ठा loopback_cable *cable = समयri->callback_data;

	loopback_snd_समयr_period_elapsed(cable, SNDRV_TIMER_EVENT_TICK,
					  resolution);
पूर्ण

अटल व्योम loopback_snd_समयr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा loopback_cable *cable;

	cable = container_of(work, काष्ठा loopback_cable, snd_समयr.event_work);
	loopback_snd_समयr_period_elapsed(cable, SNDRV_TIMER_EVENT_MSTOP, 0);
पूर्ण

अटल व्योम loopback_snd_समयr_event(काष्ठा snd_समयr_instance *समयri,
				     पूर्णांक event,
				     काष्ठा बारpec64 *tstamp,
				     अचिन्हित दीर्घ resolution)
अणु
	/* Do not lock cable->lock here because समयr->lock is alपढ़ोy hold.
	 * There are other functions which first lock cable->lock and than
	 * समयr->lock e.g.
	 * loopback_trigger()
	 * spin_lock(&cable->lock)
	 * loopback_snd_समयr_start()
	 * snd_समयr_start()
	 * spin_lock(&समयr->lock)
	 * Thereक्रमe when using the oposit order of locks here it could result
	 * in a deadlock.
	 */

	अगर (event == SNDRV_TIMER_EVENT_MSTOP) अणु
		काष्ठा loopback_cable *cable = समयri->callback_data;

		/* sound card of the समयr was stopped. Thereक्रमe there will not
		 * be any further समयr callbacks. Due to this क्रमward audio
		 * data from here अगर in draining state. When still in running
		 * state the streaming will be पातed by the usual समयout. It
		 * should not be पातed here because may be the समयr sound
		 * card करोes only a recovery and the समयr is back soon.
		 * This work triggers loopback_snd_समयr_work()
		 */
		schedule_work(&cable->snd_समयr.event_work);
	पूर्ण
पूर्ण

अटल व्योम loopback_jअगरfies_समयr_dpcm_info(काष्ठा loopback_pcm *dpcm,
					     काष्ठा snd_info_buffer *buffer)
अणु
	snd_iम_लिखो(buffer, "    update_pending:\t%u\n",
		    dpcm->period_update_pending);
	snd_iम_लिखो(buffer, "    irq_pos:\t\t%u\n", dpcm->irq_pos);
	snd_iम_लिखो(buffer, "    period_frac:\t%u\n", dpcm->period_size_frac);
	snd_iम_लिखो(buffer, "    last_jiffies:\t%lu (%lu)\n",
		    dpcm->last_jअगरfies, jअगरfies);
	snd_iम_लिखो(buffer, "    timer_expires:\t%lu\n", dpcm->समयr.expires);
पूर्ण

अटल व्योम loopback_snd_समयr_dpcm_info(काष्ठा loopback_pcm *dpcm,
					 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा loopback_cable *cable = dpcm->cable;

	snd_iम_लिखो(buffer, "    sound timer:\thw:%d,%d,%d\n",
		    cable->snd_समयr.id.card,
		    cable->snd_समयr.id.device,
		    cable->snd_समयr.id.subdevice);
	snd_iम_लिखो(buffer, "    timer open:\t\t%s\n",
		    (cable->snd_समयr.stream == SNDRV_PCM_STREAM_CAPTURE) ?
			    "capture" : "playback");
पूर्ण

अटल snd_pcm_uframes_t loopback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा loopback_pcm *dpcm = runसमय->निजी_data;
	snd_pcm_uframes_t pos;

	spin_lock(&dpcm->cable->lock);
	अगर (dpcm->cable->ops->pos_update)
		dpcm->cable->ops->pos_update(dpcm->cable);
	pos = dpcm->buf_pos;
	spin_unlock(&dpcm->cable->lock);
	वापस bytes_to_frames(runसमय, pos);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware loopback_pcm_hardware =
अणु
	.info =		(SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_MMAP |
			 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_PAUSE |
			 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
			 SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE |
			 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE |
			 SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE |
			 SNDRV_PCM_FMTBIT_FLOAT_LE | SNDRV_PCM_FMTBIT_FLOAT_BE),
	.rates =	SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_192000,
	.rate_min =		8000,
	.rate_max =		192000,
	.channels_min =		1,
	.channels_max =		32,
	.buffer_bytes_max =	2 * 1024 * 1024,
	.period_bytes_min =	64,
	/* note check overflow in frac_pos() using pcm_rate_shअगरt beक्रमe
	   changing period_bytes_max value */
	.period_bytes_max =	1024 * 1024,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल व्योम loopback_runसमय_मुक्त(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा loopback_pcm *dpcm = runसमय->निजी_data;
	kमुक्त(dpcm);
पूर्ण

अटल पूर्णांक loopback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा loopback_pcm *dpcm = runसमय->निजी_data;
	काष्ठा loopback_cable *cable = dpcm->cable;

	mutex_lock(&dpcm->loopback->cable_lock);
	cable->valid &= ~(1 << substream->stream);
	mutex_unlock(&dpcm->loopback->cable_lock);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक get_cable_index(काष्ठा snd_pcm_substream *substream)
अणु
	अगर (!substream->pcm->device)
		वापस substream->stream;
	अन्यथा
		वापस !substream->stream;
पूर्ण

अटल पूर्णांक rule_क्रमmat(काष्ठा snd_pcm_hw_params *params,
		       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा loopback_pcm *dpcm = rule->निजी;
	काष्ठा loopback_cable *cable = dpcm->cable;
	काष्ठा snd_mask m;

	snd_mask_none(&m);
	mutex_lock(&dpcm->loopback->cable_lock);
	m.bits[0] = (u_पूर्णांक32_t)cable->hw.क्रमmats;
	m.bits[1] = (u_पूर्णांक32_t)(cable->hw.क्रमmats >> 32);
	mutex_unlock(&dpcm->loopback->cable_lock);
	वापस snd_mask_refine(hw_param_mask(params, rule->var), &m);
पूर्ण

अटल पूर्णांक rule_rate(काष्ठा snd_pcm_hw_params *params,
		     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा loopback_pcm *dpcm = rule->निजी;
	काष्ठा loopback_cable *cable = dpcm->cable;
	काष्ठा snd_पूर्णांकerval t;

	mutex_lock(&dpcm->loopback->cable_lock);
	t.min = cable->hw.rate_min;
	t.max = cable->hw.rate_max;
	mutex_unlock(&dpcm->loopback->cable_lock);
        t.खोलोmin = t.खोलोmax = 0;
        t.पूर्णांकeger = 0;
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

अटल पूर्णांक rule_channels(काष्ठा snd_pcm_hw_params *params,
			 काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा loopback_pcm *dpcm = rule->निजी;
	काष्ठा loopback_cable *cable = dpcm->cable;
	काष्ठा snd_पूर्णांकerval t;

	mutex_lock(&dpcm->loopback->cable_lock);
	t.min = cable->hw.channels_min;
	t.max = cable->hw.channels_max;
	mutex_unlock(&dpcm->loopback->cable_lock);
        t.खोलोmin = t.खोलोmax = 0;
        t.पूर्णांकeger = 0;
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

अटल पूर्णांक rule_period_bytes(काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा loopback_pcm *dpcm = rule->निजी;
	काष्ठा loopback_cable *cable = dpcm->cable;
	काष्ठा snd_पूर्णांकerval t;

	mutex_lock(&dpcm->loopback->cable_lock);
	t.min = cable->hw.period_bytes_min;
	t.max = cable->hw.period_bytes_max;
	mutex_unlock(&dpcm->loopback->cable_lock);
	t.खोलोmin = 0;
	t.खोलोmax = 0;
	t.पूर्णांकeger = 0;
	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), &t);
पूर्ण

अटल व्योम मुक्त_cable(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा loopback *loopback = substream->निजी_data;
	पूर्णांक dev = get_cable_index(substream);
	काष्ठा loopback_cable *cable;

	cable = loopback->cables[substream->number][dev];
	अगर (!cable)
		वापस;
	अगर (cable->streams[!substream->stream]) अणु
		/* other stream is still alive */
		spin_lock_irq(&cable->lock);
		cable->streams[substream->stream] = शून्य;
		spin_unlock_irq(&cable->lock);
	पूर्ण अन्यथा अणु
		काष्ठा loopback_pcm *dpcm = substream->runसमय->निजी_data;

		अगर (cable->ops && cable->ops->बंद_cable && dpcm)
			cable->ops->बंद_cable(dpcm);
		/* मुक्त the cable */
		loopback->cables[substream->number][dev] = शून्य;
		kमुक्त(cable);
	पूर्ण
पूर्ण

अटल पूर्णांक loopback_jअगरfies_समयr_खोलो(काष्ठा loopback_pcm *dpcm)
अणु
	समयr_setup(&dpcm->समयr, loopback_jअगरfies_समयr_function, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा loopback_ops loopback_jअगरfies_समयr_ops = अणु
	.खोलो = loopback_jअगरfies_समयr_खोलो,
	.start = loopback_jअगरfies_समयr_start,
	.stop = loopback_jअगरfies_समयr_stop,
	.stop_sync = loopback_jअगरfies_समयr_stop_sync,
	.बंद_substream = loopback_jअगरfies_समयr_stop_sync,
	.pos_update = loopback_jअगरfies_समयr_pos_update,
	.dpcm_info = loopback_jअगरfies_समयr_dpcm_info,
पूर्ण;

अटल पूर्णांक loopback_parse_समयr_id(स्थिर अक्षर *str,
				   काष्ठा snd_समयr_id *tid)
अणु
	/* [<pref>:](<card name>|<card idx>)[अणु.,पूर्ण<dev idx>[अणु.,पूर्ण<subdev idx>]] */
	स्थिर अक्षर * स्थिर sep_dev = ".,";
	स्थिर अक्षर * स्थिर sep_pref = ":";
	स्थिर अक्षर *name = str;
	अक्षर *sep, save = '\0';
	पूर्णांक card_idx = 0, dev = 0, subdev = 0;
	पूर्णांक err;

	sep = strpbrk(str, sep_pref);
	अगर (sep)
		name = sep + 1;
	sep = strpbrk(name, sep_dev);
	अगर (sep) अणु
		save = *sep;
		*sep = '\0';
	पूर्ण
	err = kstrtoपूर्णांक(name, 0, &card_idx);
	अगर (err == -EINVAL) अणु
		/* Must be the name, not number */
		क्रम (card_idx = 0; card_idx < snd_ecards_limit; card_idx++) अणु
			काष्ठा snd_card *card = snd_card_ref(card_idx);

			अगर (card) अणु
				अगर (!म_भेद(card->id, name))
					err = 0;
				snd_card_unref(card);
			पूर्ण
			अगर (!err)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (sep) अणु
		*sep = save;
		अगर (!err) अणु
			अक्षर *sep2, save2 = '\0';

			sep2 = strpbrk(sep + 1, sep_dev);
			अगर (sep2) अणु
				save2 = *sep2;
				*sep2 = '\0';
			पूर्ण
			err = kstrtoपूर्णांक(sep + 1, 0, &dev);
			अगर (sep2) अणु
				*sep2 = save2;
				अगर (!err)
					err = kstrtoपूर्णांक(sep2 + 1, 0, &subdev);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!err && tid) अणु
		tid->card = card_idx;
		tid->device = dev;
		tid->subdevice = subdev;
	पूर्ण
	वापस err;
पूर्ण

/* call in loopback->cable_lock */
अटल पूर्णांक loopback_snd_समयr_खोलो(काष्ठा loopback_pcm *dpcm)
अणु
	पूर्णांक err = 0;
	काष्ठा snd_समयr_id tid = अणु
		.dev_class = SNDRV_TIMER_CLASS_PCM,
		.dev_sclass = SNDRV_TIMER_SCLASS_APPLICATION,
	पूर्ण;
	काष्ठा snd_समयr_instance *समयri;
	काष्ठा loopback_cable *cable = dpcm->cable;

	/* check अगर समयr was alपढ़ोy खोलोed. It is only खोलोed once
	 * per playback and capture subdevice (aka cable).
	 */
	अगर (cable->snd_समयr.instance)
		जाओ निकास;

	err = loopback_parse_समयr_id(dpcm->loopback->समयr_source, &tid);
	अगर (err < 0) अणु
		pcm_err(dpcm->substream->pcm,
			"Parsing timer source \'%s\' failed with %d",
			dpcm->loopback->समयr_source, err);
		जाओ निकास;
	पूर्ण

	cable->snd_समयr.stream = dpcm->substream->stream;
	cable->snd_समयr.id = tid;

	समयri = snd_समयr_instance_new(dpcm->loopback->card->id);
	अगर (!समयri) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	/* The callback has to be called from another work. If
	 * SNDRV_TIMER_IFLG_FAST is specअगरied it will be called from the
	 * snd_pcm_period_elapsed() call of the selected sound card.
	 * snd_pcm_period_elapsed() helds snd_pcm_stream_lock_irqsave().
	 * Due to our callback loopback_snd_समयr_function() also calls
	 * snd_pcm_period_elapsed() which calls snd_pcm_stream_lock_irqsave().
	 * This would end up in a dead lock.
	 */
	समयri->flags |= SNDRV_TIMER_IFLG_AUTO;
	समयri->callback = loopback_snd_समयr_function;
	समयri->callback_data = (व्योम *)cable;
	समयri->ccallback = loopback_snd_समयr_event;

	/* initialise a work used क्रम draining */
	INIT_WORK(&cable->snd_समयr.event_work, loopback_snd_समयr_work);

	/* The mutex loopback->cable_lock is kept locked.
	 * Thereक्रमe snd_समयr_खोलो() cannot be called a second समय
	 * by the other device of the same cable.
	 * Thereक्रमe the following issue cannot happen:
	 * [proc1] Call loopback_समयr_खोलो() ->
	 *	   Unlock cable->lock क्रम snd_समयr_बंद/खोलो() call
	 * [proc2] Call loopback_समयr_खोलो() -> snd_समयr_खोलो(),
	 *	   snd_समयr_start()
	 * [proc1] Call snd_समयr_खोलो() and overग_लिखो running समयr
	 *	   instance
	 */
	err = snd_समयr_खोलो(समयri, &cable->snd_समयr.id, current->pid);
	अगर (err < 0) अणु
		pcm_err(dpcm->substream->pcm,
			"snd_timer_open (%d,%d,%d) failed with %d",
			cable->snd_समयr.id.card,
			cable->snd_समयr.id.device,
			cable->snd_समयr.id.subdevice,
			err);
		snd_समयr_instance_मुक्त(समयri);
		जाओ निकास;
	पूर्ण

	cable->snd_समयr.instance = समयri;

निकास:
	वापस err;
पूर्ण

/* stop_sync() is not required क्रम sound समयr because it करोes not need to be
 * restarted in loopback_prepare() on Xrun recovery
 */
अटल स्थिर काष्ठा loopback_ops loopback_snd_समयr_ops = अणु
	.खोलो = loopback_snd_समयr_खोलो,
	.start = loopback_snd_समयr_start,
	.stop = loopback_snd_समयr_stop,
	.बंद_cable = loopback_snd_समयr_बंद_cable,
	.dpcm_info = loopback_snd_समयr_dpcm_info,
पूर्ण;

अटल पूर्णांक loopback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा loopback *loopback = substream->निजी_data;
	काष्ठा loopback_pcm *dpcm;
	काष्ठा loopback_cable *cable = शून्य;
	पूर्णांक err = 0;
	पूर्णांक dev = get_cable_index(substream);

	mutex_lock(&loopback->cable_lock);
	dpcm = kzalloc(माप(*dpcm), GFP_KERNEL);
	अगर (!dpcm) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण
	dpcm->loopback = loopback;
	dpcm->substream = substream;

	cable = loopback->cables[substream->number][dev];
	अगर (!cable) अणु
		cable = kzalloc(माप(*cable), GFP_KERNEL);
		अगर (!cable) अणु
			err = -ENOMEM;
			जाओ unlock;
		पूर्ण
		spin_lock_init(&cable->lock);
		cable->hw = loopback_pcm_hardware;
		अगर (loopback->समयr_source)
			cable->ops = &loopback_snd_समयr_ops;
		अन्यथा
			cable->ops = &loopback_jअगरfies_समयr_ops;
		loopback->cables[substream->number][dev] = cable;
	पूर्ण
	dpcm->cable = cable;
	runसमय->निजी_data = dpcm;

	अगर (cable->ops->खोलो) अणु
		err = cable->ops->खोलो(dpcm);
		अगर (err < 0)
			जाओ unlock;
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);

	/* use dynamic rules based on actual runसमय->hw values */
	/* note that the शेष rules created in the PCM midlevel code */
	/* are cached -> they करो not reflect the actual state */
	err = snd_pcm_hw_rule_add(runसमय, 0,
				  SNDRV_PCM_HW_PARAM_FORMAT,
				  rule_क्रमmat, dpcm,
				  SNDRV_PCM_HW_PARAM_FORMAT, -1);
	अगर (err < 0)
		जाओ unlock;
	err = snd_pcm_hw_rule_add(runसमय, 0,
				  SNDRV_PCM_HW_PARAM_RATE,
				  rule_rate, dpcm,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (err < 0)
		जाओ unlock;
	err = snd_pcm_hw_rule_add(runसमय, 0,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  rule_channels, dpcm,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (err < 0)
		जाओ unlock;

	/* In हाल of sound समयr the period समय of both devices of the same
	 * loop has to be the same.
	 * This rule only takes effect अगर a sound समयr was chosen
	 */
	अगर (cable->snd_समयr.instance) अणु
		err = snd_pcm_hw_rule_add(runसमय, 0,
					  SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					  rule_period_bytes, dpcm,
					  SNDRV_PCM_HW_PARAM_PERIOD_BYTES, -1);
		अगर (err < 0)
			जाओ unlock;
	पूर्ण

	/* loopback_runसमय_मुक्त() has not to be called अगर kमुक्त(dpcm) was
	 * alपढ़ोy called here. Otherwise it will end up with a द्विगुन मुक्त.
	 */
	runसमय->निजी_मुक्त = loopback_runसमय_मुक्त;
	अगर (get_notअगरy(dpcm))
		runसमय->hw = loopback_pcm_hardware;
	अन्यथा
		runसमय->hw = cable->hw;

	spin_lock_irq(&cable->lock);
	cable->streams[substream->stream] = dpcm;
	spin_unlock_irq(&cable->lock);

 unlock:
	अगर (err < 0) अणु
		मुक्त_cable(substream);
		kमुक्त(dpcm);
	पूर्ण
	mutex_unlock(&loopback->cable_lock);
	वापस err;
पूर्ण

अटल पूर्णांक loopback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा loopback *loopback = substream->निजी_data;
	काष्ठा loopback_pcm *dpcm = substream->runसमय->निजी_data;
	पूर्णांक err = 0;

	अगर (dpcm->cable->ops->बंद_substream)
		err = dpcm->cable->ops->बंद_substream(dpcm);
	mutex_lock(&loopback->cable_lock);
	मुक्त_cable(substream);
	mutex_unlock(&loopback->cable_lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops loopback_pcm_ops = अणु
	.खोलो =		loopback_खोलो,
	.बंद =	loopback_बंद,
	.hw_मुक्त =	loopback_hw_मुक्त,
	.prepare =	loopback_prepare,
	.trigger =	loopback_trigger,
	.poपूर्णांकer =	loopback_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक loopback_pcm_new(काष्ठा loopback *loopback,
			    पूर्णांक device, पूर्णांक substreams)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(loopback->card, "Loopback PCM", device,
			  substreams, substreams, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &loopback_pcm_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &loopback_pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);

	pcm->निजी_data = loopback;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "Loopback PCM");

	loopback->pcm[device] = pcm;
	वापस 0;
पूर्ण

अटल पूर्णांक loopback_rate_shअगरt_info(काष्ठा snd_kcontrol *kcontrol,   
				    काष्ठा snd_ctl_elem_info *uinfo) 
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 80000;
	uinfo->value.पूर्णांकeger.max = 120000;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण                                  

अटल पूर्णांक loopback_rate_shअगरt_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	
	mutex_lock(&loopback->cable_lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		loopback->setup[kcontrol->id.subdevice]
			       [kcontrol->id.device].rate_shअगरt;
	mutex_unlock(&loopback->cable_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक loopback_rate_shअगरt_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val < 80000)
		val = 80000;
	अगर (val > 120000)
		val = 120000;	
	mutex_lock(&loopback->cable_lock);
	अगर (val != loopback->setup[kcontrol->id.subdevice]
				  [kcontrol->id.device].rate_shअगरt) अणु
		loopback->setup[kcontrol->id.subdevice]
			       [kcontrol->id.device].rate_shअगरt = val;
		change = 1;
	पूर्ण
	mutex_unlock(&loopback->cable_lock);
	वापस change;
पूर्ण

अटल पूर्णांक loopback_notअगरy_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	
	mutex_lock(&loopback->cable_lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		loopback->setup[kcontrol->id.subdevice]
			       [kcontrol->id.device].notअगरy;
	mutex_unlock(&loopback->cable_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक loopback_notअगरy_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change = 0;

	val = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;
	mutex_lock(&loopback->cable_lock);
	अगर (val != loopback->setup[kcontrol->id.subdevice]
				[kcontrol->id.device].notअगरy) अणु
		loopback->setup[kcontrol->id.subdevice]
			[kcontrol->id.device].notअगरy = val;
		change = 1;
	पूर्ण
	mutex_unlock(&loopback->cable_lock);
	वापस change;
पूर्ण

अटल पूर्णांक loopback_active_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	काष्ठा loopback_cable *cable;

	अचिन्हित पूर्णांक val = 0;

	mutex_lock(&loopback->cable_lock);
	cable = loopback->cables[kcontrol->id.subdevice][kcontrol->id.device ^ 1];
	अगर (cable != शून्य) अणु
		अचिन्हित पूर्णांक running = cable->running ^ cable->छोड़ो;

		val = (running & (1 << SNDRV_PCM_STREAM_PLAYBACK)) ? 1 : 0;
	पूर्ण
	mutex_unlock(&loopback->cable_lock);
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक loopback_क्रमmat_info(काष्ठा snd_kcontrol *kcontrol,   
				काष्ठा snd_ctl_elem_info *uinfo) 
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = (__क्रमce पूर्णांक)SNDRV_PCM_FORMAT_LAST;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण                                  

अटल पूर्णांक loopback_क्रमmat_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] =
		(__क्रमce पूर्णांक)loopback->setup[kcontrol->id.subdevice]
			       [kcontrol->id.device].क्रमmat;
	वापस 0;
पूर्ण

अटल पूर्णांक loopback_rate_info(काष्ठा snd_kcontrol *kcontrol,   
			      काष्ठा snd_ctl_elem_info *uinfo) 
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 192000;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण                                  

अटल पूर्णांक loopback_rate_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	
	mutex_lock(&loopback->cable_lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		loopback->setup[kcontrol->id.subdevice]
			       [kcontrol->id.device].rate;
	mutex_unlock(&loopback->cable_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक loopback_channels_info(काष्ठा snd_kcontrol *kcontrol,   
				  काष्ठा snd_ctl_elem_info *uinfo) 
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 1;
	uinfo->value.पूर्णांकeger.max = 1024;
	uinfo->value.पूर्णांकeger.step = 1;
	वापस 0;
पूर्ण                                  

अटल पूर्णांक loopback_channels_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा loopback *loopback = snd_kcontrol_chip(kcontrol);
	
	mutex_lock(&loopback->cable_lock);
	ucontrol->value.पूर्णांकeger.value[0] =
		loopback->setup[kcontrol->id.subdevice]
			       [kcontrol->id.device].channels;
	mutex_unlock(&loopback->cable_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new loopback_controls[]  = अणु
अणु
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "PCM Rate Shift 100000",
	.info =         loopback_rate_shअगरt_info,
	.get =          loopback_rate_shअगरt_get,
	.put =          loopback_rate_shअगरt_put,
पूर्ण,
अणु
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "PCM Notify",
	.info =         snd_ctl_boolean_mono_info,
	.get =          loopback_notअगरy_get,
	.put =          loopback_notअगरy_put,
पूर्ण,
#घोषणा ACTIVE_IDX 2
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "PCM Slave Active",
	.info =         snd_ctl_boolean_mono_info,
	.get =          loopback_active_get,
पूर्ण,
#घोषणा FORMAT_IDX 3
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "PCM Slave Format",
	.info =         loopback_क्रमmat_info,
	.get =          loopback_क्रमmat_get
पूर्ण,
#घोषणा RATE_IDX 4
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "PCM Slave Rate",
	.info =         loopback_rate_info,
	.get =          loopback_rate_get
पूर्ण,
#घोषणा CHANNELS_IDX 5
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =        SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         "PCM Slave Channels",
	.info =         loopback_channels_info,
	.get =          loopback_channels_get
पूर्ण
पूर्ण;

अटल पूर्णांक loopback_mixer_new(काष्ठा loopback *loopback, पूर्णांक notअगरy)
अणु
	काष्ठा snd_card *card = loopback->card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा loopback_setup *setup;
	पूर्णांक err, dev, substr, substr_count, idx;

	म_नकल(card->mixername, "Loopback Mixer");
	क्रम (dev = 0; dev < 2; dev++) अणु
		pcm = loopback->pcm[dev];
		substr_count =
		    pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream_count;
		क्रम (substr = 0; substr < substr_count; substr++) अणु
			setup = &loopback->setup[substr][dev];
			setup->notअगरy = notअगरy;
			setup->rate_shअगरt = NO_PITCH;
			setup->क्रमmat = SNDRV_PCM_FORMAT_S16_LE;
			setup->rate = 48000;
			setup->channels = 2;
			क्रम (idx = 0; idx < ARRAY_SIZE(loopback_controls);
									idx++) अणु
				kctl = snd_ctl_new1(&loopback_controls[idx],
						    loopback);
				अगर (!kctl)
					वापस -ENOMEM;
				kctl->id.device = dev;
				kctl->id.subdevice = substr;

				/* Add the control beक्रमe copying the id so that
				 * the numid field of the id is set in the copy.
				 */
				err = snd_ctl_add(card, kctl);
				अगर (err < 0)
					वापस err;

				चयन (idx) अणु
				हाल ACTIVE_IDX:
					setup->active_id = kctl->id;
					अवरोध;
				हाल FORMAT_IDX:
					setup->क्रमmat_id = kctl->id;
					अवरोध;
				हाल RATE_IDX:
					setup->rate_id = kctl->id;
					अवरोध;
				हाल CHANNELS_IDX:
					setup->channels_id = kctl->id;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_dpcm_info(काष्ठा snd_info_buffer *buffer,
			    काष्ठा loopback_pcm *dpcm,
			    स्थिर अक्षर *id)
अणु
	snd_iम_लिखो(buffer, "  %s\n", id);
	अगर (dpcm == शून्य) अणु
		snd_iम_लिखो(buffer, "    inactive\n");
		वापस;
	पूर्ण
	snd_iम_लिखो(buffer, "    buffer_size:\t%u\n", dpcm->pcm_buffer_size);
	snd_iम_लिखो(buffer, "    buffer_pos:\t\t%u\n", dpcm->buf_pos);
	snd_iम_लिखो(buffer, "    silent_size:\t%u\n", dpcm->silent_size);
	snd_iम_लिखो(buffer, "    period_size:\t%u\n", dpcm->pcm_period_size);
	snd_iम_लिखो(buffer, "    bytes_per_sec:\t%u\n", dpcm->pcm_bps);
	snd_iम_लिखो(buffer, "    sample_align:\t%u\n", dpcm->pcm_salign);
	snd_iम_लिखो(buffer, "    rate_shift:\t\t%u\n", dpcm->pcm_rate_shअगरt);
	अगर (dpcm->cable->ops->dpcm_info)
		dpcm->cable->ops->dpcm_info(dpcm, buffer);
पूर्ण

अटल व्योम prपूर्णांक_substream_info(काष्ठा snd_info_buffer *buffer,
				 काष्ठा loopback *loopback,
				 पूर्णांक sub,
				 पूर्णांक num)
अणु
	काष्ठा loopback_cable *cable = loopback->cables[sub][num];

	snd_iम_लिखो(buffer, "Cable %i substream %i:\n", num, sub);
	अगर (cable == शून्य) अणु
		snd_iम_लिखो(buffer, "  inactive\n");
		वापस;
	पूर्ण
	snd_iम_लिखो(buffer, "  valid: %u\n", cable->valid);
	snd_iम_लिखो(buffer, "  running: %u\n", cable->running);
	snd_iम_लिखो(buffer, "  pause: %u\n", cable->छोड़ो);
	prपूर्णांक_dpcm_info(buffer, cable->streams[0], "Playback");
	prपूर्णांक_dpcm_info(buffer, cable->streams[1], "Capture");
पूर्ण

अटल व्योम prपूर्णांक_cable_info(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा loopback *loopback = entry->निजी_data;
	पूर्णांक sub, num;

	mutex_lock(&loopback->cable_lock);
	num = entry->name[म_माप(entry->name)-1];
	num = num == '0' ? 0 : 1;
	क्रम (sub = 0; sub < MAX_PCM_SUBSTREAMS; sub++)
		prपूर्णांक_substream_info(buffer, loopback, sub, num);
	mutex_unlock(&loopback->cable_lock);
पूर्ण

अटल पूर्णांक loopback_cable_proc_new(काष्ठा loopback *loopback, पूर्णांक cidx)
अणु
	अक्षर name[32];

	snम_लिखो(name, माप(name), "cable#%d", cidx);
	वापस snd_card_ro_proc_new(loopback->card, name, loopback,
				    prपूर्णांक_cable_info);
पूर्ण

अटल व्योम loopback_set_समयr_source(काष्ठा loopback *loopback,
				      स्थिर अक्षर *value)
अणु
	अगर (loopback->समयr_source) अणु
		devm_kमुक्त(loopback->card->dev, loopback->समयr_source);
		loopback->समयr_source = शून्य;
	पूर्ण
	अगर (value && *value)
		loopback->समयr_source = devm_kstrdup(loopback->card->dev,
						      value, GFP_KERNEL);
पूर्ण

अटल व्योम prपूर्णांक_समयr_source_info(काष्ठा snd_info_entry *entry,
				    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा loopback *loopback = entry->निजी_data;

	mutex_lock(&loopback->cable_lock);
	snd_iम_लिखो(buffer, "%s\n",
		    loopback->समयr_source ? loopback->समयr_source : "");
	mutex_unlock(&loopback->cable_lock);
पूर्ण

अटल व्योम change_समयr_source_info(काष्ठा snd_info_entry *entry,
				     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा loopback *loopback = entry->निजी_data;
	अक्षर line[64];

	mutex_lock(&loopback->cable_lock);
	अगर (!snd_info_get_line(buffer, line, माप(line)))
		loopback_set_समयr_source(loopback, strim(line));
	mutex_unlock(&loopback->cable_lock);
पूर्ण

अटल पूर्णांक loopback_समयr_source_proc_new(काष्ठा loopback *loopback)
अणु
	वापस snd_card_rw_proc_new(loopback->card, "timer_source", loopback,
				    prपूर्णांक_समयr_source_info,
				    change_समयr_source_info);
पूर्ण

अटल पूर्णांक loopback_probe(काष्ठा platक्रमm_device *devptr)
अणु
	काष्ठा snd_card *card;
	काष्ठा loopback *loopback;
	पूर्णांक dev = devptr->id;
	पूर्णांक err;

	err = snd_card_new(&devptr->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा loopback), &card);
	अगर (err < 0)
		वापस err;
	loopback = card->निजी_data;

	अगर (pcm_substreams[dev] < 1)
		pcm_substreams[dev] = 1;
	अगर (pcm_substreams[dev] > MAX_PCM_SUBSTREAMS)
		pcm_substreams[dev] = MAX_PCM_SUBSTREAMS;
	
	loopback->card = card;
	loopback_set_समयr_source(loopback, समयr_source[dev]);

	mutex_init(&loopback->cable_lock);

	err = loopback_pcm_new(loopback, 0, pcm_substreams[dev]);
	अगर (err < 0)
		जाओ __nodev;
	err = loopback_pcm_new(loopback, 1, pcm_substreams[dev]);
	अगर (err < 0)
		जाओ __nodev;
	err = loopback_mixer_new(loopback, pcm_notअगरy[dev] ? 1 : 0);
	अगर (err < 0)
		जाओ __nodev;
	loopback_cable_proc_new(loopback, 0);
	loopback_cable_proc_new(loopback, 1);
	loopback_समयr_source_proc_new(loopback);
	म_नकल(card->driver, "Loopback");
	म_नकल(card->लघुname, "Loopback");
	प्र_लिखो(card->दीर्घname, "Loopback %i", dev + 1);
	err = snd_card_रेजिस्टर(card);
	अगर (!err) अणु
		platक्रमm_set_drvdata(devptr, card);
		वापस 0;
	पूर्ण
      __nodev:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक loopback_हटाओ(काष्ठा platक्रमm_device *devptr)
अणु
	snd_card_मुक्त(platक्रमm_get_drvdata(devptr));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक loopback_suspend(काष्ठा device *pdev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	वापस 0;
पूर्ण
	
अटल पूर्णांक loopback_resume(काष्ठा device *pdev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(loopback_pm, loopback_suspend, loopback_resume);
#घोषणा LOOPBACK_PM_OPS	&loopback_pm
#अन्यथा
#घोषणा LOOPBACK_PM_OPS	शून्य
#पूर्ण_अगर

#घोषणा SND_LOOPBACK_DRIVER	"snd_aloop"

अटल काष्ठा platक्रमm_driver loopback_driver = अणु
	.probe		= loopback_probe,
	.हटाओ		= loopback_हटाओ,
	.driver		= अणु
		.name	= SND_LOOPBACK_DRIVER,
		.pm	= LOOPBACK_PM_OPS,
	पूर्ण,
पूर्ण;

अटल व्योम loopback_unरेजिस्टर_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(devices); ++i)
		platक्रमm_device_unरेजिस्टर(devices[i]);
	platक्रमm_driver_unरेजिस्टर(&loopback_driver);
पूर्ण

अटल पूर्णांक __init alsa_card_loopback_init(व्योम)
अणु
	पूर्णांक i, err, cards;

	err = platक्रमm_driver_रेजिस्टर(&loopback_driver);
	अगर (err < 0)
		वापस err;


	cards = 0;
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		काष्ठा platक्रमm_device *device;
		अगर (!enable[i])
			जारी;
		device = platक्रमm_device_रेजिस्टर_simple(SND_LOOPBACK_DRIVER,
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
		prपूर्णांकk(KERN_ERR "aloop: No loopback enabled\n");
#पूर्ण_अगर
		loopback_unरेजिस्टर_all();
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास alsa_card_loopback_निकास(व्योम)
अणु
	loopback_unरेजिस्टर_all();
पूर्ण

module_init(alsa_card_loopback_init)
module_निकास(alsa_card_loopback_निकास)
