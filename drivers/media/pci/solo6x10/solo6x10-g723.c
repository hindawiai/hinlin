<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mempool.h>
#समावेश <linux/poll.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>

#समावेश "solo6x10.h"
#समावेश "solo6x10-tw28.h"

#घोषणा G723_FDMA_PAGES		32
#घोषणा G723_PERIOD_BYTES	48
#घोषणा G723_PERIOD_BLOCK	1024
#घोषणा G723_FRAMES_PER_PAGE	48

/* Sets up channels 16-19 क्रम decoding and 0-15 क्रम encoding */
#घोषणा OUTMODE_MASK		0x300

#घोषणा SAMPLERATE		8000
#घोषणा BITRATE			25

/* The solo ग_लिखोs to 1k byte pages, 32 pages, in the dma. Each 1k page
 * is broken करोwn to 20 * 48 byte regions (one क्रम each channel possible)
 * with the rest of the page being dummy data. */
#घोषणा PERIODS			G723_FDMA_PAGES
#घोषणा G723_INTR_ORDER		4 /* 0 - 4 */

काष्ठा solo_snd_pcm अणु
	पूर्णांक				on;
	spinlock_t			lock;
	काष्ठा solo_dev			*solo_dev;
	u8				*g723_buf;
	dma_addr_t			g723_dma;
पूर्ण;

अटल व्योम solo_g723_config(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक clk_भाग;

	clk_भाग = (solo_dev->घड़ी_mhz * 1000000)
		/ (SAMPLERATE * (BITRATE * 2) * 2);

	solo_reg_ग_लिखो(solo_dev, SOLO_AUDIO_SAMPLE,
		       SOLO_AUDIO_BITRATE(BITRATE)
		       | SOLO_AUDIO_CLK_DIV(clk_भाग));

	solo_reg_ग_लिखो(solo_dev, SOLO_AUDIO_FDMA_INTR,
		       SOLO_AUDIO_FDMA_INTERVAL(1)
		       | SOLO_AUDIO_INTR_ORDER(G723_INTR_ORDER)
		       | SOLO_AUDIO_FDMA_BASE(SOLO_G723_EXT_ADDR(solo_dev) >> 16));

	solo_reg_ग_लिखो(solo_dev, SOLO_AUDIO_CONTROL,
		       SOLO_AUDIO_ENABLE
		       | SOLO_AUDIO_I2S_MODE
		       | SOLO_AUDIO_I2S_MULTI(3)
		       | SOLO_AUDIO_MODE(OUTMODE_MASK));
पूर्ण

व्योम solo_g723_isr(काष्ठा solo_dev *solo_dev)
अणु
	काष्ठा snd_pcm_str *pstr =
		&solo_dev->snd_pcm->streams[SNDRV_PCM_STREAM_CAPTURE];
	काष्ठा snd_pcm_substream *ss;
	काष्ठा solo_snd_pcm *solo_pcm;

	क्रम (ss = pstr->substream; ss != शून्य; ss = ss->next) अणु
		अगर (snd_pcm_substream_chip(ss) == शून्य)
			जारी;

		/* This means खोलो() hasn't been called on this one */
		अगर (snd_pcm_substream_chip(ss) == solo_dev)
			जारी;

		/* Haven't triggered a start yet */
		solo_pcm = snd_pcm_substream_chip(ss);
		अगर (!solo_pcm->on)
			जारी;

		snd_pcm_period_elapsed(ss);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_solo_pcm_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
				   SNDRV_PCM_INFO_INTERLEAVED |
				   SNDRV_PCM_INFO_BLOCK_TRANSFER |
				   SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats		= SNDRV_PCM_FMTBIT_U8,
	.rates			= SNDRV_PCM_RATE_8000,
	.rate_min		= SAMPLERATE,
	.rate_max		= SAMPLERATE,
	.channels_min		= 1,
	.channels_max		= 1,
	.buffer_bytes_max	= G723_PERIOD_BYTES * PERIODS,
	.period_bytes_min	= G723_PERIOD_BYTES,
	.period_bytes_max	= G723_PERIOD_BYTES,
	.periods_min		= PERIODS,
	.periods_max		= PERIODS,
पूर्ण;

अटल पूर्णांक snd_solo_pcm_खोलो(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा solo_dev *solo_dev = snd_pcm_substream_chip(ss);
	काष्ठा solo_snd_pcm *solo_pcm;

	solo_pcm = kzalloc(माप(*solo_pcm), GFP_KERNEL);
	अगर (solo_pcm == शून्य)
		जाओ oom;

	solo_pcm->g723_buf = dma_alloc_coherent(&solo_dev->pdev->dev,
						G723_PERIOD_BYTES,
						&solo_pcm->g723_dma,
						GFP_KERNEL);
	अगर (solo_pcm->g723_buf == शून्य)
		जाओ oom;

	spin_lock_init(&solo_pcm->lock);
	solo_pcm->solo_dev = solo_dev;
	ss->runसमय->hw = snd_solo_pcm_hw;

	snd_pcm_substream_chip(ss) = solo_pcm;

	वापस 0;

oom:
	kमुक्त(solo_pcm);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक snd_solo_pcm_बंद(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा solo_snd_pcm *solo_pcm = snd_pcm_substream_chip(ss);

	snd_pcm_substream_chip(ss) = solo_pcm->solo_dev;
	dma_मुक्त_coherent(&solo_pcm->solo_dev->pdev->dev, G723_PERIOD_BYTES,
			  solo_pcm->g723_buf, solo_pcm->g723_dma);
	kमुक्त(solo_pcm);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_solo_pcm_trigger(काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
	काष्ठा solo_snd_pcm *solo_pcm = snd_pcm_substream_chip(ss);
	काष्ठा solo_dev *solo_dev = solo_pcm->solo_dev;
	पूर्णांक ret = 0;

	spin_lock(&solo_pcm->lock);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (solo_pcm->on == 0) अणु
			/* If this is the first user, चयन on पूर्णांकerrupts */
			अगर (atomic_inc_वापस(&solo_dev->snd_users) == 1)
				solo_irq_on(solo_dev, SOLO_IRQ_G723);
			solo_pcm->on = 1;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (solo_pcm->on) अणु
			/* If this was our last user, चयन them off */
			अगर (atomic_dec_वापस(&solo_dev->snd_users) == 0)
				solo_irq_off(solo_dev, SOLO_IRQ_G723);
			solo_pcm->on = 0;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	spin_unlock(&solo_pcm->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_solo_pcm_prepare(काष्ठा snd_pcm_substream *ss)
अणु
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_solo_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा solo_snd_pcm *solo_pcm = snd_pcm_substream_chip(ss);
	काष्ठा solo_dev *solo_dev = solo_pcm->solo_dev;
	snd_pcm_uframes_t idx = solo_reg_पढ़ो(solo_dev, SOLO_AUDIO_STA) & 0x1f;

	वापस idx * G723_FRAMES_PER_PAGE;
पूर्ण

अटल पूर्णांक snd_solo_pcm_copy_user(काष्ठा snd_pcm_substream *ss, पूर्णांक channel,
				  अचिन्हित दीर्घ pos, व्योम __user *dst,
				  अचिन्हित दीर्घ count)
अणु
	काष्ठा solo_snd_pcm *solo_pcm = snd_pcm_substream_chip(ss);
	काष्ठा solo_dev *solo_dev = solo_pcm->solo_dev;
	पूर्णांक err, i;

	क्रम (i = 0; i < (count / G723_FRAMES_PER_PAGE); i++) अणु
		पूर्णांक page = (pos / G723_FRAMES_PER_PAGE) + i;

		err = solo_p2m_dma_t(solo_dev, 0, solo_pcm->g723_dma,
				     SOLO_G723_EXT_ADDR(solo_dev) +
				     (page * G723_PERIOD_BLOCK) +
				     (ss->number * G723_PERIOD_BYTES),
				     G723_PERIOD_BYTES, 0, 0);
		अगर (err)
			वापस err;

		अगर (copy_to_user(dst, solo_pcm->g723_buf, G723_PERIOD_BYTES))
			वापस -EFAULT;
		dst += G723_PERIOD_BYTES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_solo_pcm_copy_kernel(काष्ठा snd_pcm_substream *ss, पूर्णांक channel,
				    अचिन्हित दीर्घ pos, व्योम *dst,
				    अचिन्हित दीर्घ count)
अणु
	काष्ठा solo_snd_pcm *solo_pcm = snd_pcm_substream_chip(ss);
	काष्ठा solo_dev *solo_dev = solo_pcm->solo_dev;
	पूर्णांक err, i;

	क्रम (i = 0; i < (count / G723_FRAMES_PER_PAGE); i++) अणु
		पूर्णांक page = (pos / G723_FRAMES_PER_PAGE) + i;

		err = solo_p2m_dma_t(solo_dev, 0, solo_pcm->g723_dma,
				     SOLO_G723_EXT_ADDR(solo_dev) +
				     (page * G723_PERIOD_BLOCK) +
				     (ss->number * G723_PERIOD_BYTES),
				     G723_PERIOD_BYTES, 0, 0);
		अगर (err)
			वापस err;

		स_नकल(dst, solo_pcm->g723_buf, G723_PERIOD_BYTES);
		dst += G723_PERIOD_BYTES;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_solo_pcm_ops = अणु
	.खोलो = snd_solo_pcm_खोलो,
	.बंद = snd_solo_pcm_बंद,
	.prepare = snd_solo_pcm_prepare,
	.trigger = snd_solo_pcm_trigger,
	.poपूर्णांकer = snd_solo_pcm_poपूर्णांकer,
	.copy_user = snd_solo_pcm_copy_user,
	.copy_kernel = snd_solo_pcm_copy_kernel,
पूर्ण;

अटल पूर्णांक snd_solo_capture_volume_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 1;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 15;
	info->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_solo_capture_volume_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा solo_dev *solo_dev = snd_kcontrol_chip(kcontrol);
	u8 ch = value->id.numid - 1;

	value->value.पूर्णांकeger.value[0] = tw28_get_audio_gain(solo_dev, ch);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_solo_capture_volume_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा solo_dev *solo_dev = snd_kcontrol_chip(kcontrol);
	u8 ch = value->id.numid - 1;
	u8 old_val;

	old_val = tw28_get_audio_gain(solo_dev, ch);
	अगर (old_val == value->value.पूर्णांकeger.value[0])
		वापस 0;

	tw28_set_audio_gain(solo_dev, ch, value->value.पूर्णांकeger.value[0]);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_solo_capture_volume = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Volume",
	.info = snd_solo_capture_volume_info,
	.get = snd_solo_capture_volume_get,
	.put = snd_solo_capture_volume_put,
पूर्ण;

अटल पूर्णांक solo_snd_pcm_init(काष्ठा solo_dev *solo_dev)
अणु
	काष्ठा snd_card *card = solo_dev->snd_card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *ss;
	पूर्णांक ret;
	पूर्णांक i;

	ret = snd_pcm_new(card, card->driver, 0, 0, solo_dev->nr_chans,
			  &pcm);
	अगर (ret < 0)
		वापस ret;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_solo_pcm_ops);

	snd_pcm_chip(pcm) = solo_dev;
	pcm->info_flags = 0;
	strscpy(pcm->name, card->लघुname, माप(pcm->name));

	क्रम (i = 0, ss = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	     ss; ss = ss->next, i++)
		प्र_लिखो(ss->name, "Camera #%d Audio", i);

	snd_pcm_set_managed_buffer_all(pcm,
				       SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य,
				       G723_PERIOD_BYTES * PERIODS,
				       G723_PERIOD_BYTES * PERIODS);

	solo_dev->snd_pcm = pcm;

	वापस 0;
पूर्ण

पूर्णांक solo_g723_init(काष्ठा solo_dev *solo_dev)
अणु
	अटल काष्ठा snd_device_ops ops = अणु पूर्ण;
	काष्ठा snd_card *card;
	काष्ठा snd_kcontrol_new kctl;
	अक्षर name[32];
	पूर्णांक ret;

	atomic_set(&solo_dev->snd_users, 0);

	/* Allows क्रम easier mapping between video and audio */
	प्र_लिखो(name, "Softlogic%d", solo_dev->vfd->num);

	ret = snd_card_new(&solo_dev->pdev->dev,
			   SNDRV_DEFAULT_IDX1, name, THIS_MODULE, 0,
			   &solo_dev->snd_card);
	अगर (ret < 0)
		वापस ret;

	card = solo_dev->snd_card;

	strscpy(card->driver, SOLO6X10_NAME, माप(card->driver));
	strscpy(card->लघुname, "SOLO-6x10 Audio", माप(card->लघुname));
	प्र_लिखो(card->दीर्घname, "%s on %s IRQ %d", card->लघुname,
		pci_name(solo_dev->pdev), solo_dev->pdev->irq);

	ret = snd_device_new(card, SNDRV_DEV_LOWLEVEL, solo_dev, &ops);
	अगर (ret < 0)
		जाओ snd_error;

	/* Mixer controls */
	strscpy(card->mixername, "SOLO-6x10", माप(card->mixername));
	kctl = snd_solo_capture_volume;
	kctl.count = solo_dev->nr_chans;

	ret = snd_ctl_add(card, snd_ctl_new1(&kctl, solo_dev));
	अगर (ret < 0)
		जाओ snd_error;

	ret = solo_snd_pcm_init(solo_dev);
	अगर (ret < 0)
		जाओ snd_error;

	ret = snd_card_रेजिस्टर(card);
	अगर (ret < 0)
		जाओ snd_error;

	solo_g723_config(solo_dev);

	dev_info(&solo_dev->pdev->dev, "Alsa sound card as %s\n", name);

	वापस 0;

snd_error:
	snd_card_मुक्त(card);
	वापस ret;
पूर्ण

व्योम solo_g723_निकास(काष्ठा solo_dev *solo_dev)
अणु
	अगर (!solo_dev->snd_card)
		वापस;

	solo_reg_ग_लिखो(solo_dev, SOLO_AUDIO_CONTROL, 0);
	solo_irq_off(solo_dev, SOLO_IRQ_G723);

	snd_card_मुक्त(solo_dev->snd_card);
	solo_dev->snd_card = शून्य;
पूर्ण
