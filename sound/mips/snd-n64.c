<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   Sound driver क्रम Nपूर्णांकenकरो 64.
 *
 *   Copyright 2021 Lauri Kasanen
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

MODULE_AUTHOR("Lauri Kasanen <cand@gmx.com>");
MODULE_DESCRIPTION("N64 Audio");
MODULE_LICENSE("GPL");

#घोषणा AI_NTSC_DACRATE 48681812
#घोषणा AI_STATUS_BUSY  (1 << 30)
#घोषणा AI_STATUS_FULL  (1 << 31)

#घोषणा AI_ADDR_REG 0
#घोषणा AI_LEN_REG 1
#घोषणा AI_CONTROL_REG 2
#घोषणा AI_STATUS_REG 3
#घोषणा AI_RATE_REG 4
#घोषणा AI_BITCLOCK_REG 5

#घोषणा MI_INTR_REG 2
#घोषणा MI_MASK_REG 3

#घोषणा MI_INTR_AI 0x04

#घोषणा MI_MASK_CLR_AI 0x0010
#घोषणा MI_MASK_SET_AI 0x0020


काष्ठा n64audio अणु
	u32 __iomem *ai_reg_base;
	u32 __iomem *mi_reg_base;

	व्योम *ring_base;
	dma_addr_t ring_base_dma;

	काष्ठा snd_card *card;

	काष्ठा अणु
		काष्ठा snd_pcm_substream *substream;
		पूर्णांक pos, nextpos;
		u32 ग_लिखोsize;
		u32 bufsize;
		spinlock_t lock;
	पूर्ण chan;
पूर्ण;

अटल व्योम n64audio_ग_लिखो_reg(काष्ठा n64audio *priv, स्थिर u8 reg, स्थिर u32 value)
अणु
	ग_लिखोl(value, priv->ai_reg_base + reg);
पूर्ण

अटल व्योम n64mi_ग_लिखो_reg(काष्ठा n64audio *priv, स्थिर u8 reg, स्थिर u32 value)
अणु
	ग_लिखोl(value, priv->mi_reg_base + reg);
पूर्ण

अटल u32 n64mi_पढ़ो_reg(काष्ठा n64audio *priv, स्थिर u8 reg)
अणु
	वापस पढ़ोl(priv->mi_reg_base + reg);
पूर्ण

अटल व्योम n64audio_push(काष्ठा n64audio *priv)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = priv->chan.substream->runसमय;
	अचिन्हित दीर्घ flags;
	u32 count;

	spin_lock_irqsave(&priv->chan.lock, flags);

	count = priv->chan.ग_लिखोsize;

	स_नकल(priv->ring_base + priv->chan.nextpos,
	       runसमय->dma_area + priv->chan.nextpos, count);

	/*
	 * The hw रेजिस्टरs are द्विगुन-buffered, and the IRQ fires essentially
	 * one period behind. The core only allows one period's distance, so we
	 * keep a निजी DMA buffer to afक्रमd two.
	 */
	n64audio_ग_लिखो_reg(priv, AI_ADDR_REG, priv->ring_base_dma + priv->chan.nextpos);
	barrier();
	n64audio_ग_लिखो_reg(priv, AI_LEN_REG, count);

	priv->chan.nextpos += count;
	priv->chan.nextpos %= priv->chan.bufsize;

	runसमय->delay = runसमय->period_size;

	spin_unlock_irqrestore(&priv->chan.lock, flags);
पूर्ण

अटल irqवापस_t n64audio_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा n64audio *priv = dev_id;
	स्थिर u32 पूर्णांकrs = n64mi_पढ़ो_reg(priv, MI_INTR_REG);
	अचिन्हित दीर्घ flags;

	// Check it's ours
	अगर (!(पूर्णांकrs & MI_INTR_AI))
		वापस IRQ_NONE;

	n64audio_ग_लिखो_reg(priv, AI_STATUS_REG, 1);

	अगर (priv->chan.substream && snd_pcm_running(priv->chan.substream)) अणु
		spin_lock_irqsave(&priv->chan.lock, flags);

		priv->chan.pos = priv->chan.nextpos;

		spin_unlock_irqrestore(&priv->chan.lock, flags);

		snd_pcm_period_elapsed(priv->chan.substream);
		अगर (priv->chan.substream && snd_pcm_running(priv->chan.substream))
			n64audio_push(priv);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware n64audio_pcm_hw = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER),
	.क्रमmats =          SNDRV_PCM_FMTBIT_S16_BE,
	.rates =            SNDRV_PCM_RATE_8000_48000,
	.rate_min =         8000,
	.rate_max =         48000,
	.channels_min =     2,
	.channels_max =     2,
	.buffer_bytes_max = 32768,
	.period_bytes_min = 1024,
	.period_bytes_max = 32768,
	.periods_min =      3,
	// 3 periods lets the द्विगुन-buffering hw पढ़ो one buffer behind safely
	.periods_max =      128,
पूर्ण;

अटल पूर्णांक hw_rule_period_size(काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
						   SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
	पूर्णांक changed = 0;

	/*
	 * The DMA unit has errata on (start + len) & 0x3fff == 0x2000.
	 * This स्थिरraपूर्णांक makes sure that the period size is not a घातer of two,
	 * which combined with dma_alloc_coherent aligning the buffer to the largest
	 * PoT <= size guarantees it won't be hit.
	 */

	अगर (is_घातer_of_2(c->min)) अणु
		c->min += 2;
		changed = 1;
	पूर्ण
	अगर (is_घातer_of_2(c->max)) अणु
		c->max -= 2;
		changed = 1;
	पूर्ण
	अगर (snd_पूर्णांकerval_checkempty(c)) अणु
		c->empty = 1;
		वापस -EINVAL;
	पूर्ण

	वापस changed;
पूर्ण

अटल पूर्णांक n64audio_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	runसमय->hw = n64audio_pcm_hw;
	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 2);
	अगर (err < 0)
		वापस err;

	err = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
			    hw_rule_period_size, शून्य, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक n64audio_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा n64audio *priv = substream->pcm->निजी_data;
	u32 rate;

	rate = ((2 * AI_NTSC_DACRATE / runसमय->rate) + 1) / 2 - 1;

	n64audio_ग_लिखो_reg(priv, AI_RATE_REG, rate);

	rate /= 66;
	अगर (rate > 16)
		rate = 16;
	n64audio_ग_लिखो_reg(priv, AI_BITCLOCK_REG, rate - 1);

	spin_lock_irq(&priv->chan.lock);

	/* Setup the pseuकरो-dma transfer poपूर्णांकers.  */
	priv->chan.pos = 0;
	priv->chan.nextpos = 0;
	priv->chan.substream = substream;
	priv->chan.ग_लिखोsize = snd_pcm_lib_period_bytes(substream);
	priv->chan.bufsize = snd_pcm_lib_buffer_bytes(substream);

	spin_unlock_irq(&priv->chan.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक n64audio_pcm_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd)
अणु
	काष्ठा n64audio *priv = substream->pcm->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		n64audio_push(substream->pcm->निजी_data);
		n64audio_ग_लिखो_reg(priv, AI_CONTROL_REG, 1);
		n64mi_ग_लिखो_reg(priv, MI_MASK_REG, MI_MASK_SET_AI);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		n64audio_ग_लिखो_reg(priv, AI_CONTROL_REG, 0);
		n64mi_ग_लिखो_reg(priv, MI_MASK_REG, MI_MASK_CLR_AI);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t n64audio_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा n64audio *priv = substream->pcm->निजी_data;

	वापस bytes_to_frames(substream->runसमय,
			       priv->chan.pos);
पूर्ण

अटल पूर्णांक n64audio_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा n64audio *priv = substream->pcm->निजी_data;

	priv->chan.substream = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops n64audio_pcm_ops = अणु
	.खोलो =		n64audio_pcm_खोलो,
	.prepare =	n64audio_pcm_prepare,
	.trigger =	n64audio_pcm_trigger,
	.poपूर्णांकer =	n64audio_pcm_poपूर्णांकer,
	.बंद =	n64audio_pcm_बंद,
पूर्ण;

/*
 * The target device is embedded and RAM-स्थिरrained. We save RAM
 * by initializing in __init code that माला_लो dropped late in boot.
 * For the same reason there is no module or unloading support.
 */
अटल पूर्णांक __init n64audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा n64audio *priv;
	काष्ठा resource *res;
	पूर्णांक err;

	err = snd_card_new(&pdev->dev, SNDRV_DEFAULT_IDX1,
			   SNDRV_DEFAULT_STR1,
			   THIS_MODULE, माप(*priv), &card);
	अगर (err < 0)
		वापस err;

	priv = card->निजी_data;

	spin_lock_init(&priv->chan.lock);

	priv->card = card;

	priv->ring_base = dma_alloc_coherent(card->dev, 32 * 1024, &priv->ring_base_dma,
					     GFP_DMA|GFP_KERNEL);
	अगर (!priv->ring_base) अणु
		err = -ENOMEM;
		जाओ fail_card;
	पूर्ण

	priv->mi_reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->mi_reg_base)) अणु
		err = PTR_ERR(priv->mi_reg_base);
		जाओ fail_dma_alloc;
	पूर्ण

	priv->ai_reg_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->ai_reg_base)) अणु
		err = PTR_ERR(priv->ai_reg_base);
		जाओ fail_dma_alloc;
	पूर्ण

	err = snd_pcm_new(card, "N64 Audio", 0, 1, 0, &pcm);
	अगर (err < 0)
		जाओ fail_dma_alloc;

	pcm->निजी_data = priv;
	म_नकल(pcm->name, "N64 Audio");

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &n64audio_pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, card->dev, 0, 0);

	म_नकल(card->driver, "N64 Audio");
	म_नकल(card->लघुname, "N64 Audio");
	म_नकल(card->दीर्घname, "N64 Audio");

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (devm_request_irq(&pdev->dev, res->start, n64audio_isr,
				IRQF_SHARED, "N64 Audio", priv)) अणु
		err = -EBUSY;
		जाओ fail_dma_alloc;
	पूर्ण

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ fail_dma_alloc;

	वापस 0;

fail_dma_alloc:
	dma_मुक्त_coherent(card->dev, 32 * 1024, priv->ring_base, priv->ring_base_dma);

fail_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver n64audio_driver = अणु
	.driver = अणु
		.name = "n64audio",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init n64audio_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&n64audio_driver, n64audio_probe);
पूर्ण

module_init(n64audio_init);
