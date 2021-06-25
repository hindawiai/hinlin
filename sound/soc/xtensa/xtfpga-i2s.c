<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xtfpga I2S controller driver
 *
 * Copyright (c) 2014 Cadence Design Systems Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा DRV_NAME	"xtfpga-i2s"

#घोषणा XTFPGA_I2S_VERSION	0x00
#घोषणा XTFPGA_I2S_CONFIG	0x04
#घोषणा XTFPGA_I2S_INT_MASK	0x08
#घोषणा XTFPGA_I2S_INT_STATUS	0x0c
#घोषणा XTFPGA_I2S_CHAN0_DATA	0x10
#घोषणा XTFPGA_I2S_CHAN1_DATA	0x14
#घोषणा XTFPGA_I2S_CHAN2_DATA	0x18
#घोषणा XTFPGA_I2S_CHAN3_DATA	0x1c

#घोषणा XTFPGA_I2S_CONFIG_TX_ENABLE	0x1
#घोषणा XTFPGA_I2S_CONFIG_INT_ENABLE	0x2
#घोषणा XTFPGA_I2S_CONFIG_LEFT		0x4
#घोषणा XTFPGA_I2S_CONFIG_RATIO_BASE	8
#घोषणा XTFPGA_I2S_CONFIG_RATIO_MASK	0x0000ff00
#घोषणा XTFPGA_I2S_CONFIG_RES_BASE	16
#घोषणा XTFPGA_I2S_CONFIG_RES_MASK	0x003f0000
#घोषणा XTFPGA_I2S_CONFIG_LEVEL_BASE	24
#घोषणा XTFPGA_I2S_CONFIG_LEVEL_MASK	0x0f000000
#घोषणा XTFPGA_I2S_CONFIG_CHANNEL_BASE	28

#घोषणा XTFPGA_I2S_INT_UNDERRUN		0x1
#घोषणा XTFPGA_I2S_INT_LEVEL		0x2
#घोषणा XTFPGA_I2S_INT_VALID		0x3

#घोषणा XTFPGA_I2S_FIFO_SIZE		8192

/*
 * I2S controller operation:
 *
 * Enabling TX: output 1 period of zeros (starting with left channel)
 * and then queued data.
 *
 * Level status and पूर्णांकerrupt: whenever FIFO level is below FIFO trigger,
 * level status is 1 and an IRQ is निश्चितed (अगर enabled).
 *
 * Underrun status and पूर्णांकerrupt: whenever FIFO is empty, underrun status
 * is 1 and an IRQ is निश्चितed (अगर enabled).
 */
काष्ठा xtfpga_i2s अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	व्योम __iomem *regs;

	/* current playback substream. शून्य अगर not playing.
	 *
	 * Access to that field is synchronized between the पूर्णांकerrupt handler
	 * and userspace through RCU.
	 *
	 * Interrupt handler (thपढ़ोed part) करोes PIO on substream data in RCU
	 * पढ़ो-side critical section. Trigger callback sets and clears the
	 * poपूर्णांकer when the playback is started and stopped with
	 * rcu_assign_poपूर्णांकer. When userspace is about to मुक्त the playback
	 * stream in the pcm_बंद callback it synchronizes with the पूर्णांकerrupt
	 * handler by means of synchronize_rcu call.
	 */
	काष्ठा snd_pcm_substream __rcu *tx_substream;
	अचिन्हित (*tx_fn)(काष्ठा xtfpga_i2s *i2s,
			  काष्ठा snd_pcm_runसमय *runसमय,
			  अचिन्हित tx_ptr);
	अचिन्हित tx_ptr; /* next frame index in the sample buffer */

	/* current fअगरo level estimate.
	 * Doesn't have to be perfectly accurate, but must be not less than
	 * the actual FIFO level in order to aव्योम stall on push attempt.
	 */
	अचिन्हित tx_fअगरo_level;

	/* FIFO level at which level पूर्णांकerrupt occurs */
	अचिन्हित tx_fअगरo_low;

	/* maximal FIFO level */
	अचिन्हित tx_fअगरo_high;
पूर्ण;

अटल bool xtfpga_i2s_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg >= XTFPGA_I2S_CONFIG;
पूर्ण

अटल bool xtfpga_i2s_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg < XTFPGA_I2S_CHAN0_DATA;
पूर्ण

अटल bool xtfpga_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == XTFPGA_I2S_INT_STATUS;
पूर्ण

अटल स्थिर काष्ठा regmap_config xtfpga_i2s_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = XTFPGA_I2S_CHAN3_DATA,
	.ग_लिखोable_reg = xtfpga_i2s_wr_reg,
	.पढ़ोable_reg = xtfpga_i2s_rd_reg,
	.अस्थिर_reg = xtfpga_i2s_अस्थिर_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

/* Generate functions that करो PIO from TX DMA area to FIFO क्रम all supported
 * stream क्रमmats.
 * Functions will be called xtfpga_pcm_tx_<channels>x<sample bits>, e.g.
 * xtfpga_pcm_tx_2x16 क्रम 16-bit stereo.
 *
 * FIFO consists of 32-bit words, one word per channel, always 2 channels.
 * If I2S पूर्णांकerface is configured with smaller sample resolution, only
 * the LSB of each word is used.
 */
#घोषणा xtfpga_pcm_tx_fn(channels, sample_bits) \
अटल अचिन्हित xtfpga_pcm_tx_##channels##x##sample_bits( \
	काष्ठा xtfpga_i2s *i2s, काष्ठा snd_pcm_runसमय *runसमय, \
	अचिन्हित tx_ptr) \
अणु \
	स्थिर u##sample_bits (*p)[channels] = \
		(व्योम *)runसमय->dma_area; \
\
	क्रम (; i2s->tx_fअगरo_level < i2s->tx_fअगरo_high; \
	     i2s->tx_fअगरo_level += 2) अणु \
		ioग_लिखो32(p[tx_ptr][0], \
			  i2s->regs + XTFPGA_I2S_CHAN0_DATA); \
		ioग_लिखो32(p[tx_ptr][channels - 1], \
			  i2s->regs + XTFPGA_I2S_CHAN0_DATA); \
		अगर (++tx_ptr >= runसमय->buffer_size) \
			tx_ptr = 0; \
	पूर्ण \
	वापस tx_ptr; \
पूर्ण

xtfpga_pcm_tx_fn(1, 16)
xtfpga_pcm_tx_fn(2, 16)
xtfpga_pcm_tx_fn(1, 32)
xtfpga_pcm_tx_fn(2, 32)

#अघोषित xtfpga_pcm_tx_fn

अटल bool xtfpga_pcm_push_tx(काष्ठा xtfpga_i2s *i2s)
अणु
	काष्ठा snd_pcm_substream *tx_substream;
	bool tx_active;

	rcu_पढ़ो_lock();
	tx_substream = rcu_dereference(i2s->tx_substream);
	tx_active = tx_substream && snd_pcm_running(tx_substream);
	अगर (tx_active) अणु
		अचिन्हित tx_ptr = READ_ONCE(i2s->tx_ptr);
		अचिन्हित new_tx_ptr = i2s->tx_fn(i2s, tx_substream->runसमय,
						 tx_ptr);

		cmpxchg(&i2s->tx_ptr, tx_ptr, new_tx_ptr);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस tx_active;
पूर्ण

अटल व्योम xtfpga_pcm_refill_fअगरo(काष्ठा xtfpga_i2s *i2s)
अणु
	अचिन्हित पूर्णांक_status;
	अचिन्हित i;

	regmap_पढ़ो(i2s->regmap, XTFPGA_I2S_INT_STATUS,
		    &पूर्णांक_status);

	क्रम (i = 0; i < 2; ++i) अणु
		bool tx_active = xtfpga_pcm_push_tx(i2s);

		regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_INT_STATUS,
			     XTFPGA_I2S_INT_VALID);
		अगर (tx_active)
			regmap_पढ़ो(i2s->regmap, XTFPGA_I2S_INT_STATUS,
				    &पूर्णांक_status);

		अगर (!tx_active ||
		    !(पूर्णांक_status & XTFPGA_I2S_INT_LEVEL))
			अवरोध;

		/* After the push the level IRQ is still निश्चितed,
		 * means FIFO level is below tx_fअगरo_low. Estimate
		 * it as tx_fअगरo_low.
		 */
		i2s->tx_fअगरo_level = i2s->tx_fअगरo_low;
	पूर्ण

	अगर (!(पूर्णांक_status & XTFPGA_I2S_INT_LEVEL))
		regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_INT_MASK,
			     XTFPGA_I2S_INT_VALID);
	अन्यथा अगर (!(पूर्णांक_status & XTFPGA_I2S_INT_UNDERRUN))
		regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_INT_MASK,
			     XTFPGA_I2S_INT_UNDERRUN);

	अगर (!(पूर्णांक_status & XTFPGA_I2S_INT_UNDERRUN))
		regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE);
	अन्यथा
		regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
				   XTFPGA_I2S_CONFIG_INT_ENABLE |
				   XTFPGA_I2S_CONFIG_TX_ENABLE, 0);
पूर्ण

अटल irqवापस_t xtfpga_i2s_thपढ़ोed_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xtfpga_i2s *i2s = dev_id;
	काष्ठा snd_pcm_substream *tx_substream;
	अचिन्हित config, पूर्णांक_status, पूर्णांक_mask;

	regmap_पढ़ो(i2s->regmap, XTFPGA_I2S_CONFIG, &config);
	regmap_पढ़ो(i2s->regmap, XTFPGA_I2S_INT_MASK, &पूर्णांक_mask);
	regmap_पढ़ो(i2s->regmap, XTFPGA_I2S_INT_STATUS, &पूर्णांक_status);

	अगर (!(config & XTFPGA_I2S_CONFIG_INT_ENABLE) ||
	    !(पूर्णांक_status & पूर्णांक_mask & XTFPGA_I2S_INT_VALID))
		वापस IRQ_NONE;

	/* Update FIFO level estimate in accordance with पूर्णांकerrupt status
	 * रेजिस्टर.
	 */
	अगर (पूर्णांक_status & XTFPGA_I2S_INT_UNDERRUN) अणु
		i2s->tx_fअगरo_level = 0;
		regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
				   XTFPGA_I2S_CONFIG_TX_ENABLE, 0);
	पूर्ण अन्यथा अणु
		/* The FIFO isn't empty, but is below tx_fअगरo_low. Estimate
		 * it as tx_fअगरo_low.
		 */
		i2s->tx_fअगरo_level = i2s->tx_fअगरo_low;
	पूर्ण

	rcu_पढ़ो_lock();
	tx_substream = rcu_dereference(i2s->tx_substream);

	अगर (tx_substream && snd_pcm_running(tx_substream)) अणु
		snd_pcm_period_elapsed(tx_substream);
		अगर (पूर्णांक_status & XTFPGA_I2S_INT_UNDERRUN)
			dev_dbg_ratelimited(i2s->dev, "%s: underrun\n",
					    __func__);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Refill FIFO, update allowed IRQ reasons, enable IRQ अगर FIFO is
	 * not empty.
	 */
	xtfpga_pcm_refill_fअगरo(i2s);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xtfpga_i2s_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा xtfpga_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_set_dma_data(dai, substream, i2s);
	वापस 0;
पूर्ण

अटल पूर्णांक xtfpga_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा xtfpga_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित srate = params_rate(params);
	अचिन्हित channels = params_channels(params);
	अचिन्हित period_size = params_period_size(params);
	अचिन्हित sample_size = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	अचिन्हित freq, ratio, level;
	पूर्णांक err;

	regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
			   XTFPGA_I2S_CONFIG_RES_MASK,
			   sample_size << XTFPGA_I2S_CONFIG_RES_BASE);

	freq = 256 * srate;
	err = clk_set_rate(i2s->clk, freq);
	अगर (err < 0)
		वापस err;

	/* ratio field of the config रेजिस्टर controls MCLK->I2S घड़ी
	 * derivation: I2S घड़ी = MCLK / (2 * (ratio + 2)).
	 *
	 * So with MCLK = 256 * sample rate ratio is 0 क्रम 32 bit stereo
	 * and 2 क्रम 16 bit stereo.
	 */
	ratio = (freq - (srate * sample_size * 8)) /
		(srate * sample_size * 4);

	regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
			   XTFPGA_I2S_CONFIG_RATIO_MASK,
			   ratio << XTFPGA_I2S_CONFIG_RATIO_BASE);

	i2s->tx_fअगरo_low = XTFPGA_I2S_FIFO_SIZE / 2;

	/* period_size * 2: FIFO always माला_लो 2 samples per frame */
	क्रम (level = 1;
	     i2s->tx_fअगरo_low / 2 >= period_size * 2 &&
	     level < (XTFPGA_I2S_CONFIG_LEVEL_MASK >>
		      XTFPGA_I2S_CONFIG_LEVEL_BASE); ++level)
		i2s->tx_fअगरo_low /= 2;

	i2s->tx_fअगरo_high = 2 * i2s->tx_fअगरo_low;

	regmap_update_bits(i2s->regmap, XTFPGA_I2S_CONFIG,
			   XTFPGA_I2S_CONFIG_LEVEL_MASK,
			   level << XTFPGA_I2S_CONFIG_LEVEL_BASE);

	dev_dbg(i2s->dev,
		"%s srate: %u, channels: %u, sample_size: %u, period_size: %u\n",
		__func__, srate, channels, sample_size, period_size);
	dev_dbg(i2s->dev, "%s freq: %u, ratio: %u, level: %u\n",
		__func__, freq, ratio, level);

	वापस 0;
पूर्ण

अटल पूर्णांक xtfpga_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	अगर ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF)
		वापस -EINVAL;
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		वापस -EINVAL;
	अगर ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_I2S)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* PCM */

अटल स्थिर काष्ठा snd_pcm_hardware xtfpga_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BLOCK_TRANSFER,
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min		= 1,
	.channels_max		= 2,
	.period_bytes_min	= 2,
	.period_bytes_max	= XTFPGA_I2S_FIFO_SIZE / 2 * 8,
	.periods_min		= 2,
	.periods_max		= XTFPGA_I2S_FIFO_SIZE * 8 / 2,
	.buffer_bytes_max	= XTFPGA_I2S_FIFO_SIZE * 8,
	.fअगरo_size		= 16,
पूर्ण;

अटल पूर्णांक xtfpga_pcm_खोलो(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	व्योम *p;

	snd_soc_set_runसमय_hwparams(substream, &xtfpga_pcm_hardware);
	p = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	runसमय->निजी_data = p;

	वापस 0;
पूर्ण

अटल पूर्णांक xtfpga_pcm_बंद(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream)
अणु
	synchronize_rcu();
	वापस 0;
पूर्ण

अटल पूर्णांक xtfpga_pcm_hw_params(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा xtfpga_i2s *i2s = runसमय->निजी_data;
	अचिन्हित channels = params_channels(hw_params);

	चयन (channels) अणु
	हाल 1:
	हाल 2:
		अवरोध;

	शेष:
		वापस -EINVAL;

	पूर्ण

	चयन (params_क्रमmat(hw_params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		i2s->tx_fn = (channels == 1) ?
			xtfpga_pcm_tx_1x16 :
			xtfpga_pcm_tx_2x16;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S32_LE:
		i2s->tx_fn = (channels == 1) ?
			xtfpga_pcm_tx_1x32 :
			xtfpga_pcm_tx_2x32;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xtfpga_pcm_trigger(काष्ठा snd_soc_component *component,
			      काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा xtfpga_i2s *i2s = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		WRITE_ONCE(i2s->tx_ptr, 0);
		rcu_assign_poपूर्णांकer(i2s->tx_substream, substream);
		xtfpga_pcm_refill_fअगरo(i2s);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		rcu_assign_poपूर्णांकer(i2s->tx_substream, शून्य);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t xtfpga_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा xtfpga_i2s *i2s = runसमय->निजी_data;
	snd_pcm_uframes_t pos = READ_ONCE(i2s->tx_ptr);

	वापस pos < runसमय->buffer_size ? pos : 0;
पूर्ण

अटल पूर्णांक xtfpga_pcm_new(काष्ठा snd_soc_component *component,
			  काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	माप_प्रकार size = xtfpga_pcm_hardware.buffer_bytes_max;

	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_DEV,
				       card->dev, size, size);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver xtfpga_i2s_component = अणु
	.name		= DRV_NAME,
	.खोलो		= xtfpga_pcm_खोलो,
	.बंद		= xtfpga_pcm_बंद,
	.hw_params	= xtfpga_pcm_hw_params,
	.trigger	= xtfpga_pcm_trigger,
	.poपूर्णांकer	= xtfpga_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= xtfpga_pcm_new,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops xtfpga_i2s_dai_ops = अणु
	.startup	= xtfpga_i2s_startup,
	.hw_params      = xtfpga_i2s_hw_params,
	.set_fmt        = xtfpga_i2s_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver xtfpga_i2s_dai[] = अणु
	अणु
		.name = "xtfpga-i2s",
		.id = 0,
		.playback = अणु
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &xtfpga_i2s_dai_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक xtfpga_i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा xtfpga_i2s *i2s = dev_get_drvdata(dev);

	clk_disable_unprepare(i2s->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक xtfpga_i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा xtfpga_i2s *i2s = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->clk);
	अगर (ret) अणु
		dev_err(dev, "clk_prepare_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xtfpga_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xtfpga_i2s *i2s;
	पूर्णांक err, irq;

	i2s = devm_kzalloc(&pdev->dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण
	platक्रमm_set_drvdata(pdev, i2s);
	i2s->dev = &pdev->dev;
	dev_dbg(&pdev->dev, "dev: %p, i2s: %p\n", &pdev->dev, i2s);

	i2s->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2s->regs)) अणु
		err = PTR_ERR(i2s->regs);
		जाओ err;
	पूर्ण

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, i2s->regs,
					    &xtfpga_i2s_regmap_config);
	अगर (IS_ERR(i2s->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		err = PTR_ERR(i2s->regmap);
		जाओ err;
	पूर्ण

	i2s->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2s->clk)) अणु
		dev_err(&pdev->dev, "couldn't get clock\n");
		err = PTR_ERR(i2s->clk);
		जाओ err;
	पूर्ण

	regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_CONFIG,
		     (0x1 << XTFPGA_I2S_CONFIG_CHANNEL_BASE));
	regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_INT_STATUS, XTFPGA_I2S_INT_VALID);
	regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_INT_MASK, XTFPGA_I2S_INT_UNDERRUN);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ err;
	पूर्ण
	err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
					xtfpga_i2s_thपढ़ोed_irq_handler,
					IRQF_SHARED | IRQF_ONESHOT,
					pdev->name, i2s);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ err;
	पूर्ण

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &xtfpga_i2s_component,
					      xtfpga_i2s_dai,
					      ARRAY_SIZE(xtfpga_i2s_dai));
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "couldn't register component\n");
		जाओ err;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		err = xtfpga_i2s_runसमय_resume(&pdev->dev);
		अगर (err)
			जाओ err_pm_disable;
	पूर्ण
	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
err:
	dev_err(&pdev->dev, "%s: err = %d\n", __func__, err);
	वापस err;
पूर्ण

अटल पूर्णांक xtfpga_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xtfpga_i2s *i2s = dev_get_drvdata(&pdev->dev);

	अगर (i2s->regmap && !IS_ERR(i2s->regmap)) अणु
		regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_CONFIG, 0);
		regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_INT_MASK, 0);
		regmap_ग_लिखो(i2s->regmap, XTFPGA_I2S_INT_STATUS,
			     XTFPGA_I2S_INT_VALID);
	पूर्ण
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		xtfpga_i2s_runसमय_suspend(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id xtfpga_i2s_of_match[] = अणु
	अणु .compatible = "cdns,xtfpga-i2s", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xtfpga_i2s_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops xtfpga_i2s_pm_ops = अणु
	SET_RUNTIME_PM_OPS(xtfpga_i2s_runसमय_suspend,
			   xtfpga_i2s_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver xtfpga_i2s_driver = अणु
	.probe   = xtfpga_i2s_probe,
	.हटाओ  = xtfpga_i2s_हटाओ,
	.driver  = अणु
		.name = "xtfpga-i2s",
		.of_match_table = of_match_ptr(xtfpga_i2s_of_match),
		.pm = &xtfpga_i2s_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xtfpga_i2s_driver);

MODULE_AUTHOR("Max Filippov <jcmvbkbc@gmail.com>");
MODULE_DESCRIPTION("xtfpga I2S controller driver");
MODULE_LICENSE("GPL v2");
