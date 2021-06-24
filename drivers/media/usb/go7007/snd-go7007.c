<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>

#समावेश "go7007-priv.h"

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
module_param_array(id, अक्षरp, शून्य, 0444);
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the go7007 audio driver");
MODULE_PARM_DESC(id, "ID string for the go7007 audio driver");
MODULE_PARM_DESC(enable, "Enable for the go7007 audio driver");

काष्ठा go7007_snd अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *substream;
	spinlock_t lock;
	पूर्णांक w_idx;
	पूर्णांक hw_ptr;
	पूर्णांक avail;
	पूर्णांक capturing;
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware go7007_snd_capture_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
					SNDRV_PCM_INFO_INTERLEAVED |
					SNDRV_PCM_INFO_BLOCK_TRANSFER |
					SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE,
	.rates			= SNDRV_PCM_RATE_48000,
	.rate_min		= 48000,
	.rate_max		= 48000,
	.channels_min		= 2,
	.channels_max		= 2,
	.buffer_bytes_max	= (128*1024),
	.period_bytes_min	= 4096,
	.period_bytes_max	= (128*1024),
	.periods_min		= 1,
	.periods_max		= 32,
पूर्ण;

अटल व्योम parse_audio_stream_data(काष्ठा go7007 *go, u8 *buf, पूर्णांक length)
अणु
	काष्ठा go7007_snd *gosnd = go->snd_context;
	काष्ठा snd_pcm_runसमय *runसमय = gosnd->substream->runसमय;
	पूर्णांक frames = bytes_to_frames(runसमय, length);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gosnd->lock, flags);
	gosnd->hw_ptr += frames;
	अगर (gosnd->hw_ptr >= runसमय->buffer_size)
		gosnd->hw_ptr -= runसमय->buffer_size;
	gosnd->avail += frames;
	spin_unlock_irqrestore(&gosnd->lock, flags);
	अगर (gosnd->w_idx + length > runसमय->dma_bytes) अणु
		पूर्णांक cpy = runसमय->dma_bytes - gosnd->w_idx;

		स_नकल(runसमय->dma_area + gosnd->w_idx, buf, cpy);
		length -= cpy;
		buf += cpy;
		gosnd->w_idx = 0;
	पूर्ण
	स_नकल(runसमय->dma_area + gosnd->w_idx, buf, length);
	gosnd->w_idx += length;
	spin_lock_irqsave(&gosnd->lock, flags);
	अगर (gosnd->avail < runसमय->period_size) अणु
		spin_unlock_irqrestore(&gosnd->lock, flags);
		वापस;
	पूर्ण
	gosnd->avail -= runसमय->period_size;
	spin_unlock_irqrestore(&gosnd->lock, flags);
	अगर (gosnd->capturing)
		snd_pcm_period_elapsed(gosnd->substream);
पूर्ण

अटल पूर्णांक go7007_snd_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा go7007 *go = snd_pcm_substream_chip(substream);

	go->audio_deliver = parse_audio_stream_data;
	वापस 0;
पूर्ण

अटल पूर्णांक go7007_snd_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा go7007 *go = snd_pcm_substream_chip(substream);

	go->audio_deliver = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक go7007_snd_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा go7007 *go = snd_pcm_substream_chip(substream);
	काष्ठा go7007_snd *gosnd = go->snd_context;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	spin_lock_irqsave(&gosnd->lock, flags);
	अगर (gosnd->substream == शून्य) अणु
		gosnd->substream = substream;
		substream->runसमय->hw = go7007_snd_capture_hw;
		r = 0;
	पूर्ण अन्यथा
		r = -EBUSY;
	spin_unlock_irqrestore(&gosnd->lock, flags);
	वापस r;
पूर्ण

अटल पूर्णांक go7007_snd_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा go7007 *go = snd_pcm_substream_chip(substream);
	काष्ठा go7007_snd *gosnd = go->snd_context;

	gosnd->substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक go7007_snd_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक go7007_snd_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा go7007 *go = snd_pcm_substream_chip(substream);
	काष्ठा go7007_snd *gosnd = go->snd_context;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* Just set a flag to indicate we should संकेत ALSA when
		 * sound comes in */
		gosnd->capturing = 1;
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
		gosnd->hw_ptr = gosnd->w_idx = gosnd->avail = 0;
		gosnd->capturing = 0;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t go7007_snd_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा go7007 *go = snd_pcm_substream_chip(substream);
	काष्ठा go7007_snd *gosnd = go->snd_context;

	वापस gosnd->hw_ptr;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops go7007_snd_capture_ops = अणु
	.खोलो		= go7007_snd_capture_खोलो,
	.बंद		= go7007_snd_capture_बंद,
	.hw_params	= go7007_snd_hw_params,
	.hw_मुक्त	= go7007_snd_hw_मुक्त,
	.prepare	= go7007_snd_pcm_prepare,
	.trigger	= go7007_snd_pcm_trigger,
	.poपूर्णांकer	= go7007_snd_pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक go7007_snd_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा go7007 *go = device->device_data;

	kमुक्त(go->snd_context);
	go->snd_context = शून्य;
	वापस 0;
पूर्ण

अटल काष्ठा snd_device_ops go7007_snd_device_ops = अणु
	.dev_मुक्त	= go7007_snd_मुक्त,
पूर्ण;

पूर्णांक go7007_snd_init(काष्ठा go7007 *go)
अणु
	अटल पूर्णांक dev;
	काष्ठा go7007_snd *gosnd;
	पूर्णांक ret;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण
	gosnd = kदो_स्मृति(माप(काष्ठा go7007_snd), GFP_KERNEL);
	अगर (gosnd == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&gosnd->lock);
	gosnd->hw_ptr = gosnd->w_idx = gosnd->avail = 0;
	gosnd->capturing = 0;
	ret = snd_card_new(go->dev, index[dev], id[dev], THIS_MODULE, 0,
			   &gosnd->card);
	अगर (ret < 0)
		जाओ मुक्त_snd;

	ret = snd_device_new(gosnd->card, SNDRV_DEV_LOWLEVEL, go,
			&go7007_snd_device_ops);
	अगर (ret < 0)
		जाओ मुक्त_card;

	ret = snd_pcm_new(gosnd->card, "go7007", 0, 0, 1, &gosnd->pcm);
	अगर (ret < 0)
		जाओ मुक्त_card;

	strscpy(gosnd->card->driver, "go7007", माप(gosnd->card->driver));
	strscpy(gosnd->card->लघुname, go->name, माप(gosnd->card->लघुname));
	strscpy(gosnd->card->दीर्घname, gosnd->card->लघुname,
		माप(gosnd->card->दीर्घname));

	gosnd->pcm->निजी_data = go;
	snd_pcm_set_ops(gosnd->pcm, SNDRV_PCM_STREAM_CAPTURE,
			&go7007_snd_capture_ops);
	snd_pcm_set_managed_buffer_all(gosnd->pcm, SNDRV_DMA_TYPE_VMALLOC,
				       शून्य, 0, 0);

	ret = snd_card_रेजिस्टर(gosnd->card);
	अगर (ret < 0)
		जाओ मुक्त_card;

	gosnd->substream = शून्य;
	go->snd_context = gosnd;
	v4l2_device_get(&go->v4l2_dev);
	++dev;

	वापस 0;

मुक्त_card:
	snd_card_मुक्त(gosnd->card);
मुक्त_snd:
	kमुक्त(gosnd);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(go7007_snd_init);

पूर्णांक go7007_snd_हटाओ(काष्ठा go7007 *go)
अणु
	काष्ठा go7007_snd *gosnd = go->snd_context;

	snd_card_disconnect(gosnd->card);
	snd_card_मुक्त_when_बंदd(gosnd->card);
	v4l2_device_put(&go->v4l2_dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(go7007_snd_हटाओ);

MODULE_LICENSE("GPL v2");
