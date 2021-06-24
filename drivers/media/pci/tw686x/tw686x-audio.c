<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 VanguardiaSur - www.vanguardiasur.com.ar
 *
 * Based on the audio support from the tw6869 driver:
 * Copyright 2015 www.starterkit.ru <info@starterkit.ru>
 *
 * Based on:
 * Driver क्रम Intersil|Techwell TW6869 based DVR cards
 * (c) 2011-12 liran <jli11@पूर्णांकersil.com> [Intersil|Techwell China]
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>
#समावेश "tw686x.h"
#समावेश "tw686x-regs.h"

#घोषणा AUDIO_CHANNEL_OFFSET 8

व्योम tw686x_audio_irq(काष्ठा tw686x_dev *dev, अचिन्हित दीर्घ requests,
		      अचिन्हित पूर्णांक pb_status)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ch, pb;

	क्रम_each_set_bit(ch, &requests, max_channels(dev)) अणु
		काष्ठा tw686x_audio_channel *ac = &dev->audio_channels[ch];
		काष्ठा tw686x_audio_buf *करोne = शून्य;
		काष्ठा tw686x_audio_buf *next = शून्य;
		काष्ठा tw686x_dma_desc *desc;

		pb = !!(pb_status & BIT(AUDIO_CHANNEL_OFFSET + ch));

		spin_lock_irqsave(&ac->lock, flags);

		/* Sanity check */
		अगर (!ac->ss || !ac->curr_bufs[0] || !ac->curr_bufs[1]) अणु
			spin_unlock_irqrestore(&ac->lock, flags);
			जारी;
		पूर्ण

		अगर (!list_empty(&ac->buf_list)) अणु
			next = list_first_entry(&ac->buf_list,
					काष्ठा tw686x_audio_buf, list);
			list_move_tail(&next->list, &ac->buf_list);
			करोne = ac->curr_bufs[!pb];
			ac->curr_bufs[pb] = next;
		पूर्ण
		spin_unlock_irqrestore(&ac->lock, flags);

		अगर (!करोne || !next)
			जारी;
		/*
		 * Checking क्रम a non-nil dma_desc[pb]->virt buffer is
		 * the same as checking क्रम स_नकल DMA mode.
		 */
		desc = &ac->dma_descs[pb];
		अगर (desc->virt) अणु
			स_नकल(करोne->virt, desc->virt,
			       dev->period_size);
		पूर्ण अन्यथा अणु
			u32 reg = pb ? ADMA_B_ADDR[ch] : ADMA_P_ADDR[ch];
			reg_ग_लिखो(dev, reg, next->dma);
		पूर्ण
		ac->ptr = करोne->dma - ac->buf[0].dma;
		snd_pcm_period_elapsed(ac->ss);
	पूर्ण
पूर्ण

/*
 * Audio parameters are global and shared among all
 * capture channels. The driver prevents changes to
 * the parameters अगर any audio channel is capturing.
 */
अटल स्थिर काष्ठा snd_pcm_hardware tw686x_capture_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
				   SNDRV_PCM_INFO_INTERLEAVED |
				   SNDRV_PCM_INFO_BLOCK_TRANSFER |
				   SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE,
	.rates			= SNDRV_PCM_RATE_8000_48000,
	.rate_min		= 8000,
	.rate_max		= 48000,
	.channels_min		= 1,
	.channels_max		= 1,
	.buffer_bytes_max	= TW686X_AUDIO_PAGE_MAX * AUDIO_DMA_SIZE_MAX,
	.period_bytes_min	= AUDIO_DMA_SIZE_MIN,
	.period_bytes_max	= AUDIO_DMA_SIZE_MAX,
	.periods_min		= TW686X_AUDIO_PERIODS_MIN,
	.periods_max		= TW686X_AUDIO_PERIODS_MAX,
पूर्ण;

अटल पूर्णांक tw686x_pcm_खोलो(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा tw686x_dev *dev = snd_pcm_substream_chip(ss);
	काष्ठा tw686x_audio_channel *ac = &dev->audio_channels[ss->number];
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	पूर्णांक err;

	ac->ss = ss;
	rt->hw = tw686x_capture_hw;

	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(rt, SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_pcm_बंद(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा tw686x_dev *dev = snd_pcm_substream_chip(ss);
	काष्ठा tw686x_audio_channel *ac = &dev->audio_channels[ss->number];

	ac->ss = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक tw686x_pcm_prepare(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा tw686x_dev *dev = snd_pcm_substream_chip(ss);
	काष्ठा tw686x_audio_channel *ac = &dev->audio_channels[ss->number];
	काष्ठा snd_pcm_runसमय *rt = ss->runसमय;
	अचिन्हित पूर्णांक period_size = snd_pcm_lib_period_bytes(ss);
	काष्ठा tw686x_audio_buf *p_buf, *b_buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&dev->lock, flags);
	/*
	 * Given the audio parameters are global (i.e. shared across
	 * DMA channels), we need to check new params are allowed.
	 */
	अगर (((dev->audio_rate != rt->rate) ||
	     (dev->period_size != period_size)) && dev->audio_enabled)
		जाओ err_audio_busy;

	tw686x_disable_channel(dev, AUDIO_CHANNEL_OFFSET + ac->ch);
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (dev->audio_rate != rt->rate) अणु
		u32 reg;

		dev->audio_rate = rt->rate;
		reg = ((125000000 / rt->rate) << 16) +
		       ((125000000 % rt->rate) << 16) / rt->rate;

		reg_ग_लिखो(dev, AUDIO_CONTROL2, reg);
	पूर्ण

	अगर (dev->period_size != period_size) अणु
		u32 reg;

		dev->period_size = period_size;
		reg = reg_पढ़ो(dev, AUDIO_CONTROL1);
		reg &= ~(AUDIO_DMA_SIZE_MASK << AUDIO_DMA_SIZE_SHIFT);
		reg |= period_size << AUDIO_DMA_SIZE_SHIFT;

		reg_ग_लिखो(dev, AUDIO_CONTROL1, reg);
	पूर्ण

	अगर (rt->periods < TW686X_AUDIO_PERIODS_MIN ||
	    rt->periods > TW686X_AUDIO_PERIODS_MAX)
		वापस -EINVAL;

	spin_lock_irqsave(&ac->lock, flags);
	INIT_LIST_HEAD(&ac->buf_list);

	क्रम (i = 0; i < rt->periods; i++) अणु
		ac->buf[i].dma = rt->dma_addr + period_size * i;
		ac->buf[i].virt = rt->dma_area + period_size * i;
		INIT_LIST_HEAD(&ac->buf[i].list);
		list_add_tail(&ac->buf[i].list, &ac->buf_list);
	पूर्ण

	p_buf =	list_first_entry(&ac->buf_list, काष्ठा tw686x_audio_buf, list);
	list_move_tail(&p_buf->list, &ac->buf_list);

	b_buf =	list_first_entry(&ac->buf_list, काष्ठा tw686x_audio_buf, list);
	list_move_tail(&b_buf->list, &ac->buf_list);

	ac->curr_bufs[0] = p_buf;
	ac->curr_bufs[1] = b_buf;
	ac->ptr = 0;

	अगर (dev->dma_mode != TW686X_DMA_MODE_MEMCPY) अणु
		reg_ग_लिखो(dev, ADMA_P_ADDR[ac->ch], p_buf->dma);
		reg_ग_लिखो(dev, ADMA_B_ADDR[ac->ch], b_buf->dma);
	पूर्ण

	spin_unlock_irqrestore(&ac->lock, flags);

	वापस 0;

err_audio_busy:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक tw686x_pcm_trigger(काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
	काष्ठा tw686x_dev *dev = snd_pcm_substream_chip(ss);
	काष्ठा tw686x_audio_channel *ac = &dev->audio_channels[ss->number];
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (ac->curr_bufs[0] && ac->curr_bufs[1]) अणु
			spin_lock_irqsave(&dev->lock, flags);
			dev->audio_enabled = 1;
			tw686x_enable_channel(dev,
				AUDIO_CHANNEL_OFFSET + ac->ch);
			spin_unlock_irqrestore(&dev->lock, flags);

			mod_समयr(&dev->dma_delay_समयr,
				  jअगरfies + msecs_to_jअगरfies(100));
		पूर्ण अन्यथा अणु
			err = -EIO;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		spin_lock_irqsave(&dev->lock, flags);
		dev->audio_enabled = 0;
		tw686x_disable_channel(dev, AUDIO_CHANNEL_OFFSET + ac->ch);
		spin_unlock_irqrestore(&dev->lock, flags);

		spin_lock_irqsave(&ac->lock, flags);
		ac->curr_bufs[0] = शून्य;
		ac->curr_bufs[1] = शून्य;
		spin_unlock_irqrestore(&ac->lock, flags);
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल snd_pcm_uframes_t tw686x_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा tw686x_dev *dev = snd_pcm_substream_chip(ss);
	काष्ठा tw686x_audio_channel *ac = &dev->audio_channels[ss->number];

	वापस bytes_to_frames(ss->runसमय, ac->ptr);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops tw686x_pcm_ops = अणु
	.खोलो = tw686x_pcm_खोलो,
	.बंद = tw686x_pcm_बंद,
	.prepare = tw686x_pcm_prepare,
	.trigger = tw686x_pcm_trigger,
	.poपूर्णांकer = tw686x_pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक tw686x_snd_pcm_init(काष्ठा tw686x_dev *dev)
अणु
	काष्ठा snd_card *card = dev->snd_card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *ss;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = snd_pcm_new(card, card->driver, 0, 0, max_channels(dev), &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &tw686x_pcm_ops);
	snd_pcm_chip(pcm) = dev;
	pcm->info_flags = 0;
	strscpy(pcm->name, "tw686x PCM", माप(pcm->name));

	क्रम (i = 0, ss = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	     ss; ss = ss->next, i++)
		snम_लिखो(ss->name, माप(ss->name), "vch%u audio", i);

	snd_pcm_set_managed_buffer_all(pcm,
				SNDRV_DMA_TYPE_DEV,
				&dev->pci_dev->dev,
				TW686X_AUDIO_PAGE_MAX * AUDIO_DMA_SIZE_MAX,
				TW686X_AUDIO_PAGE_MAX * AUDIO_DMA_SIZE_MAX);
	वापस 0;
पूर्ण

अटल व्योम tw686x_audio_dma_मुक्त(काष्ठा tw686x_dev *dev,
				  काष्ठा tw686x_audio_channel *ac)
अणु
	पूर्णांक pb;

	क्रम (pb = 0; pb < 2; pb++) अणु
		अगर (!ac->dma_descs[pb].virt)
			जारी;
		dma_मुक्त_coherent(&dev->pci_dev->dev, ac->dma_descs[pb].size,
				  ac->dma_descs[pb].virt,
				  ac->dma_descs[pb].phys);
		ac->dma_descs[pb].virt = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tw686x_audio_dma_alloc(काष्ठा tw686x_dev *dev,
				  काष्ठा tw686x_audio_channel *ac)
अणु
	पूर्णांक pb;

	/*
	 * In the स_नकल DMA mode we allocate a coherent buffer
	 * and use it क्रम the DMA capture. Otherwise, DMA
	 * acts on the ALSA buffers as received in pcm_prepare.
	 */
	अगर (dev->dma_mode != TW686X_DMA_MODE_MEMCPY)
		वापस 0;

	क्रम (pb = 0; pb < 2; pb++) अणु
		u32 reg = pb ? ADMA_B_ADDR[ac->ch] : ADMA_P_ADDR[ac->ch];
		व्योम *virt;

		virt = dma_alloc_coherent(&dev->pci_dev->dev,
					  AUDIO_DMA_SIZE_MAX,
					  &ac->dma_descs[pb].phys, GFP_KERNEL);
		अगर (!virt) अणु
			dev_err(&dev->pci_dev->dev,
				"dma%d: unable to allocate audio DMA %s-buffer\n",
				ac->ch, pb ? "B" : "P");
			वापस -ENOMEM;
		पूर्ण
		ac->dma_descs[pb].virt = virt;
		ac->dma_descs[pb].size = AUDIO_DMA_SIZE_MAX;
		reg_ग_लिखो(dev, reg, ac->dma_descs[pb].phys);
	पूर्ण
	वापस 0;
पूर्ण

व्योम tw686x_audio_मुक्त(काष्ठा tw686x_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	u32 dma_ch_mask;
	u32 dma_cmd;

	spin_lock_irqsave(&dev->lock, flags);
	dma_cmd = reg_पढ़ो(dev, DMA_CMD);
	dma_ch_mask = reg_पढ़ो(dev, DMA_CHANNEL_ENABLE);
	reg_ग_लिखो(dev, DMA_CMD, dma_cmd & ~0xff00);
	reg_ग_लिखो(dev, DMA_CHANNEL_ENABLE, dma_ch_mask & ~0xff00);
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (!dev->snd_card)
		वापस;
	snd_card_मुक्त(dev->snd_card);
	dev->snd_card = शून्य;
पूर्ण

पूर्णांक tw686x_audio_init(काष्ठा tw686x_dev *dev)
अणु
	काष्ठा pci_dev *pci_dev = dev->pci_dev;
	काष्ठा snd_card *card;
	पूर्णांक err, ch;

	/* Enable बाह्यal audio */
	reg_ग_लिखो(dev, AUDIO_CONTROL1, BIT(0));

	err = snd_card_new(&pci_dev->dev, SNDRV_DEFAULT_IDX1,
			   SNDRV_DEFAULT_STR1,
			   THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	dev->snd_card = card;
	strscpy(card->driver, "tw686x", माप(card->driver));
	strscpy(card->लघुname, "tw686x", माप(card->लघुname));
	strscpy(card->दीर्घname, pci_name(pci_dev), माप(card->दीर्घname));
	snd_card_set_dev(card, &pci_dev->dev);

	क्रम (ch = 0; ch < max_channels(dev); ch++) अणु
		काष्ठा tw686x_audio_channel *ac;

		ac = &dev->audio_channels[ch];
		spin_lock_init(&ac->lock);
		ac->dev = dev;
		ac->ch = ch;

		err = tw686x_audio_dma_alloc(dev, ac);
		अगर (err < 0)
			जाओ err_cleanup;
	पूर्ण

	err = tw686x_snd_pcm_init(dev);
	अगर (err < 0)
		जाओ err_cleanup;

	err = snd_card_रेजिस्टर(card);
	अगर (!err)
		वापस 0;

err_cleanup:
	क्रम (ch = 0; ch < max_channels(dev); ch++) अणु
		अगर (!dev->audio_channels[ch].dev)
			जारी;
		tw686x_audio_dma_मुक्त(dev, &dev->audio_channels[ch]);
	पूर्ण
	snd_card_मुक्त(card);
	dev->snd_card = शून्य;
	वापस err;
पूर्ण
