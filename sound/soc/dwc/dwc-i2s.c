<शैली गुरु>
/*
 * ALSA SoC Synopsys I2S Audio Layer
 *
 * sound/soc/dwc/designware_i2s.c
 *
 * Copyright (C) 2010 ST Microelectronics
 * Rajeev Kumar <rajeevkumar.linux@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/designware_i2s.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश "local.h"

अटल अंतरभूत व्योम i2s_ग_लिखो_reg(व्योम __iomem *io_base, पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, io_base + reg);
पूर्ण

अटल अंतरभूत u32 i2s_पढ़ो_reg(व्योम __iomem *io_base, पूर्णांक reg)
अणु
	वापस पढ़ोl(io_base + reg);
पूर्ण

अटल अंतरभूत व्योम i2s_disable_channels(काष्ठा dw_i2s_dev *dev, u32 stream)
अणु
	u32 i = 0;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		क्रम (i = 0; i < 4; i++)
			i2s_ग_लिखो_reg(dev->i2s_base, TER(i), 0);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 4; i++)
			i2s_ग_लिखो_reg(dev->i2s_base, RER(i), 0);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम i2s_clear_irqs(काष्ठा dw_i2s_dev *dev, u32 stream)
अणु
	u32 i = 0;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		क्रम (i = 0; i < 4; i++)
			i2s_पढ़ो_reg(dev->i2s_base, TOR(i));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 4; i++)
			i2s_पढ़ो_reg(dev->i2s_base, ROR(i));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम i2s_disable_irqs(काष्ठा dw_i2s_dev *dev, u32 stream,
				    पूर्णांक chan_nr)
अणु
	u32 i, irq;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		क्रम (i = 0; i < (chan_nr / 2); i++) अणु
			irq = i2s_पढ़ो_reg(dev->i2s_base, IMR(i));
			i2s_ग_लिखो_reg(dev->i2s_base, IMR(i), irq | 0x30);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < (chan_nr / 2); i++) अणु
			irq = i2s_पढ़ो_reg(dev->i2s_base, IMR(i));
			i2s_ग_लिखो_reg(dev->i2s_base, IMR(i), irq | 0x03);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम i2s_enable_irqs(काष्ठा dw_i2s_dev *dev, u32 stream,
				   पूर्णांक chan_nr)
अणु
	u32 i, irq;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		क्रम (i = 0; i < (chan_nr / 2); i++) अणु
			irq = i2s_पढ़ो_reg(dev->i2s_base, IMR(i));
			i2s_ग_लिखो_reg(dev->i2s_base, IMR(i), irq & ~0x30);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < (chan_nr / 2); i++) अणु
			irq = i2s_पढ़ो_reg(dev->i2s_base, IMR(i));
			i2s_ग_लिखो_reg(dev->i2s_base, IMR(i), irq & ~0x03);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t i2s_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dw_i2s_dev *dev = dev_id;
	bool irq_valid = false;
	u32 isr[4];
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		isr[i] = i2s_पढ़ो_reg(dev->i2s_base, ISR(i));

	i2s_clear_irqs(dev, SNDRV_PCM_STREAM_PLAYBACK);
	i2s_clear_irqs(dev, SNDRV_PCM_STREAM_CAPTURE);

	क्रम (i = 0; i < 4; i++) अणु
		/*
		 * Check अगर TX fअगरo is empty. If empty fill FIFO with samples
		 * NOTE: Only two channels supported
		 */
		अगर ((isr[i] & ISR_TXFE) && (i == 0) && dev->use_pio) अणु
			dw_pcm_push_tx(dev);
			irq_valid = true;
		पूर्ण

		/*
		 * Data available. Retrieve samples from FIFO
		 * NOTE: Only two channels supported
		 */
		अगर ((isr[i] & ISR_RXDA) && (i == 0) && dev->use_pio) अणु
			dw_pcm_pop_rx(dev);
			irq_valid = true;
		पूर्ण

		/* Error Handling: TX */
		अगर (isr[i] & ISR_TXFO) अणु
			dev_err(dev->dev, "TX overrun (ch_id=%d)\n", i);
			irq_valid = true;
		पूर्ण

		/* Error Handling: TX */
		अगर (isr[i] & ISR_RXFO) अणु
			dev_err(dev->dev, "RX overrun (ch_id=%d)\n", i);
			irq_valid = true;
		पूर्ण
	पूर्ण

	अगर (irq_valid)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल व्योम i2s_start(काष्ठा dw_i2s_dev *dev,
		      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2s_clk_config_data *config = &dev->config;

	i2s_ग_लिखो_reg(dev->i2s_base, IER, 1);
	i2s_enable_irqs(dev, substream->stream, config->chan_nr);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		i2s_ग_लिखो_reg(dev->i2s_base, ITER, 1);
	अन्यथा
		i2s_ग_लिखो_reg(dev->i2s_base, IRER, 1);

	i2s_ग_लिखो_reg(dev->i2s_base, CER, 1);
पूर्ण

अटल व्योम i2s_stop(काष्ठा dw_i2s_dev *dev,
		काष्ठा snd_pcm_substream *substream)
अणु

	i2s_clear_irqs(dev, substream->stream);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		i2s_ग_लिखो_reg(dev->i2s_base, ITER, 0);
	अन्यथा
		i2s_ग_लिखो_reg(dev->i2s_base, IRER, 0);

	i2s_disable_irqs(dev, substream->stream, 8);

	अगर (!dev->active) अणु
		i2s_ग_लिखो_reg(dev->i2s_base, CER, 0);
		i2s_ग_लिखो_reg(dev->i2s_base, IER, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक dw_i2s_startup(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा dw_i2s_dev *dev = snd_soc_dai_get_drvdata(cpu_dai);
	जोड़ dw_i2s_snd_dma_data *dma_data = शून्य;

	अगर (!(dev->capability & DWC_I2S_RECORD) &&
			(substream->stream == SNDRV_PCM_STREAM_CAPTURE))
		वापस -EINVAL;

	अगर (!(dev->capability & DWC_I2S_PLAY) &&
			(substream->stream == SNDRV_PCM_STREAM_PLAYBACK))
		वापस -EINVAL;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = &dev->play_dma_data;
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		dma_data = &dev->capture_dma_data;

	snd_soc_dai_set_dma_data(cpu_dai, substream, (व्योम *)dma_data);

	वापस 0;
पूर्ण

अटल व्योम dw_i2s_config(काष्ठा dw_i2s_dev *dev, पूर्णांक stream)
अणु
	u32 ch_reg;
	काष्ठा i2s_clk_config_data *config = &dev->config;


	i2s_disable_channels(dev, stream);

	क्रम (ch_reg = 0; ch_reg < (config->chan_nr / 2); ch_reg++) अणु
		अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			i2s_ग_लिखो_reg(dev->i2s_base, TCR(ch_reg),
				      dev->xfer_resolution);
			i2s_ग_लिखो_reg(dev->i2s_base, TFCR(ch_reg),
				      dev->fअगरo_th - 1);
			i2s_ग_लिखो_reg(dev->i2s_base, TER(ch_reg), 1);
		पूर्ण अन्यथा अणु
			i2s_ग_लिखो_reg(dev->i2s_base, RCR(ch_reg),
				      dev->xfer_resolution);
			i2s_ग_लिखो_reg(dev->i2s_base, RFCR(ch_reg),
				      dev->fअगरo_th - 1);
			i2s_ग_लिखो_reg(dev->i2s_base, RER(ch_reg), 1);
		पूर्ण

	पूर्ण
पूर्ण

अटल पूर्णांक dw_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा dw_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा i2s_clk_config_data *config = &dev->config;
	पूर्णांक ret;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		config->data_width = 16;
		dev->ccr = 0x00;
		dev->xfer_resolution = 0x02;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S24_LE:
		config->data_width = 24;
		dev->ccr = 0x08;
		dev->xfer_resolution = 0x04;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S32_LE:
		config->data_width = 32;
		dev->ccr = 0x10;
		dev->xfer_resolution = 0x05;
		अवरोध;

	शेष:
		dev_err(dev->dev, "designware-i2s: unsupported PCM fmt");
		वापस -EINVAL;
	पूर्ण

	config->chan_nr = params_channels(params);

	चयन (config->chan_nr) अणु
	हाल EIGHT_CHANNEL_SUPPORT:
	हाल SIX_CHANNEL_SUPPORT:
	हाल FOUR_CHANNEL_SUPPORT:
	हाल TWO_CHANNEL_SUPPORT:
		अवरोध;
	शेष:
		dev_err(dev->dev, "channel not supported\n");
		वापस -EINVAL;
	पूर्ण

	dw_i2s_config(dev, substream->stream);

	i2s_ग_लिखो_reg(dev->i2s_base, CCR, dev->ccr);

	config->sample_rate = params_rate(params);

	अगर (dev->capability & DW_I2S_MASTER) अणु
		अगर (dev->i2s_clk_cfg) अणु
			ret = dev->i2s_clk_cfg(config);
			अगर (ret < 0) अणु
				dev_err(dev->dev, "runtime audio clk config fail\n");
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 bitclk = config->sample_rate *
					config->data_width * 2;

			ret = clk_set_rate(dev->clk, bitclk);
			अगर (ret) अणु
				dev_err(dev->dev, "Can't set I2S clock rate: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dw_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
पूर्ण

अटल पूर्णांक dw_i2s_prepare(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा dw_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		i2s_ग_लिखो_reg(dev->i2s_base, TXFFR, 1);
	अन्यथा
		i2s_ग_लिखो_reg(dev->i2s_base, RXFFR, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_i2s_trigger(काष्ठा snd_pcm_substream *substream,
		पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा dw_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dev->active++;
		i2s_start(dev, substream);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dev->active--;
		i2s_stop(dev, substream);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक dw_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा dw_i2s_dev *dev = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगर (dev->capability & DW_I2S_SLAVE)
			ret = 0;
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगर (dev->capability & DW_I2S_MASTER)
			ret = 0;
		अन्यथा
			ret = -EINVAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
	हाल SND_SOC_DAIFMT_CBS_CFM:
		ret = -EINVAL;
		अवरोध;
	शेष:
		dev_dbg(dev->dev, "dwc : Invalid master/slave format\n");
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops dw_i2s_dai_ops = अणु
	.startup	= dw_i2s_startup,
	.shutकरोwn	= dw_i2s_shutकरोwn,
	.hw_params	= dw_i2s_hw_params,
	.prepare	= dw_i2s_prepare,
	.trigger	= dw_i2s_trigger,
	.set_fmt	= dw_i2s_set_fmt,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dw_i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw_i2s_dev *dw_dev = dev_get_drvdata(dev);

	अगर (dw_dev->capability & DW_I2S_MASTER)
		clk_disable(dw_dev->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक dw_i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dw_i2s_dev *dw_dev = dev_get_drvdata(dev);

	अगर (dw_dev->capability & DW_I2S_MASTER)
		clk_enable(dw_dev->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक dw_i2s_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा dw_i2s_dev *dev = snd_soc_component_get_drvdata(component);

	अगर (dev->capability & DW_I2S_MASTER)
		clk_disable(dev->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक dw_i2s_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा dw_i2s_dev *dev = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dai *dai;
	पूर्णांक stream;

	अगर (dev->capability & DW_I2S_MASTER)
		clk_enable(dev->clk);

	क्रम_each_component_dais(component, dai) अणु
		क्रम_each_pcm_streams(stream)
			अगर (snd_soc_dai_stream_active(dai, stream))
				dw_i2s_config(dev, stream);
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा dw_i2s_suspend	शून्य
#घोषणा dw_i2s_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver dw_i2s_component = अणु
	.name		= "dw-i2s",
	.suspend	= dw_i2s_suspend,
	.resume		= dw_i2s_resume,
पूर्ण;

/*
 * The following tables allow a direct lookup of various parameters
 * defined in the I2S block's configuration in terms of sound प्रणाली
 * parameters.  Each table is sized to the number of entries possible
 * according to the number of configuration bits describing an I2S
 * block parameter.
 */

/* Maximum bit resolution of a channel - not unअगरormly spaced */
अटल स्थिर u32 fअगरo_width[COMP_MAX_WORDSIZE] = अणु
	12, 16, 20, 24, 32, 0, 0, 0
पूर्ण;

/* Width of (DMA) bus */
अटल स्थिर u32 bus_widths[COMP_MAX_DATA_WIDTH] = अणु
	DMA_SLAVE_BUSWIDTH_1_BYTE,
	DMA_SLAVE_BUSWIDTH_2_BYTES,
	DMA_SLAVE_BUSWIDTH_4_BYTES,
	DMA_SLAVE_BUSWIDTH_UNDEFINED
पूर्ण;

/* PCM क्रमmat to support channel resolution */
अटल स्थिर u32 क्रमmats[COMP_MAX_WORDSIZE] = अणु
	SNDRV_PCM_FMTBIT_S16_LE,
	SNDRV_PCM_FMTBIT_S16_LE,
	SNDRV_PCM_FMTBIT_S24_LE,
	SNDRV_PCM_FMTBIT_S24_LE,
	SNDRV_PCM_FMTBIT_S32_LE,
	0,
	0,
	0
पूर्ण;

अटल पूर्णांक dw_configure_dai(काष्ठा dw_i2s_dev *dev,
				   काष्ठा snd_soc_dai_driver *dw_i2s_dai,
				   अचिन्हित पूर्णांक rates)
अणु
	/*
	 * Read component parameter रेजिस्टरs to extract
	 * the I2S block's configuration.
	 */
	u32 comp1 = i2s_पढ़ो_reg(dev->i2s_base, dev->i2s_reg_comp1);
	u32 comp2 = i2s_पढ़ो_reg(dev->i2s_base, dev->i2s_reg_comp2);
	u32 fअगरo_depth = 1 << (1 + COMP1_FIFO_DEPTH_GLOBAL(comp1));
	u32 idx;

	अगर (dev->capability & DWC_I2S_RECORD &&
			dev->quirks & DW_I2S_QUIRK_COMP_PARAM1)
		comp1 = comp1 & ~BIT(5);

	अगर (dev->capability & DWC_I2S_PLAY &&
			dev->quirks & DW_I2S_QUIRK_COMP_PARAM1)
		comp1 = comp1 & ~BIT(6);

	अगर (COMP1_TX_ENABLED(comp1)) अणु
		dev_dbg(dev->dev, " designware: play supported\n");
		idx = COMP1_TX_WORDSIZE_0(comp1);
		अगर (WARN_ON(idx >= ARRAY_SIZE(क्रमmats)))
			वापस -EINVAL;
		अगर (dev->quirks & DW_I2S_QUIRK_16BIT_IDX_OVERRIDE)
			idx = 1;
		dw_i2s_dai->playback.channels_min = MIN_CHANNEL_NUM;
		dw_i2s_dai->playback.channels_max =
				1 << (COMP1_TX_CHANNELS(comp1) + 1);
		dw_i2s_dai->playback.क्रमmats = क्रमmats[idx];
		dw_i2s_dai->playback.rates = rates;
	पूर्ण

	अगर (COMP1_RX_ENABLED(comp1)) अणु
		dev_dbg(dev->dev, "designware: record supported\n");
		idx = COMP2_RX_WORDSIZE_0(comp2);
		अगर (WARN_ON(idx >= ARRAY_SIZE(क्रमmats)))
			वापस -EINVAL;
		अगर (dev->quirks & DW_I2S_QUIRK_16BIT_IDX_OVERRIDE)
			idx = 1;
		dw_i2s_dai->capture.channels_min = MIN_CHANNEL_NUM;
		dw_i2s_dai->capture.channels_max =
				1 << (COMP1_RX_CHANNELS(comp1) + 1);
		dw_i2s_dai->capture.क्रमmats = क्रमmats[idx];
		dw_i2s_dai->capture.rates = rates;
	पूर्ण

	अगर (COMP1_MODE_EN(comp1)) अणु
		dev_dbg(dev->dev, "designware: i2s master mode supported\n");
		dev->capability |= DW_I2S_MASTER;
	पूर्ण अन्यथा अणु
		dev_dbg(dev->dev, "designware: i2s slave mode supported\n");
		dev->capability |= DW_I2S_SLAVE;
	पूर्ण

	dev->fअगरo_th = fअगरo_depth / 2;
	वापस 0;
पूर्ण

अटल पूर्णांक dw_configure_dai_by_pd(काष्ठा dw_i2s_dev *dev,
				   काष्ठा snd_soc_dai_driver *dw_i2s_dai,
				   काष्ठा resource *res,
				   स्थिर काष्ठा i2s_platक्रमm_data *pdata)
अणु
	u32 comp1 = i2s_पढ़ो_reg(dev->i2s_base, dev->i2s_reg_comp1);
	u32 idx = COMP1_APB_DATA_WIDTH(comp1);
	पूर्णांक ret;

	अगर (WARN_ON(idx >= ARRAY_SIZE(bus_widths)))
		वापस -EINVAL;

	ret = dw_configure_dai(dev, dw_i2s_dai, pdata->snd_rates);
	अगर (ret < 0)
		वापस ret;

	अगर (dev->quirks & DW_I2S_QUIRK_16BIT_IDX_OVERRIDE)
		idx = 1;
	/* Set DMA slaves info */
	dev->play_dma_data.pd.data = pdata->play_dma_data;
	dev->capture_dma_data.pd.data = pdata->capture_dma_data;
	dev->play_dma_data.pd.addr = res->start + I2S_TXDMA;
	dev->capture_dma_data.pd.addr = res->start + I2S_RXDMA;
	dev->play_dma_data.pd.max_burst = 16;
	dev->capture_dma_data.pd.max_burst = 16;
	dev->play_dma_data.pd.addr_width = bus_widths[idx];
	dev->capture_dma_data.pd.addr_width = bus_widths[idx];
	dev->play_dma_data.pd.filter = pdata->filter;
	dev->capture_dma_data.pd.filter = pdata->filter;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_configure_dai_by_dt(काष्ठा dw_i2s_dev *dev,
				   काष्ठा snd_soc_dai_driver *dw_i2s_dai,
				   काष्ठा resource *res)
अणु
	u32 comp1 = i2s_पढ़ो_reg(dev->i2s_base, I2S_COMP_PARAM_1);
	u32 comp2 = i2s_पढ़ो_reg(dev->i2s_base, I2S_COMP_PARAM_2);
	u32 fअगरo_depth = 1 << (1 + COMP1_FIFO_DEPTH_GLOBAL(comp1));
	u32 idx = COMP1_APB_DATA_WIDTH(comp1);
	u32 idx2;
	पूर्णांक ret;

	अगर (WARN_ON(idx >= ARRAY_SIZE(bus_widths)))
		वापस -EINVAL;

	ret = dw_configure_dai(dev, dw_i2s_dai, SNDRV_PCM_RATE_8000_192000);
	अगर (ret < 0)
		वापस ret;

	अगर (COMP1_TX_ENABLED(comp1)) अणु
		idx2 = COMP1_TX_WORDSIZE_0(comp1);

		dev->capability |= DWC_I2S_PLAY;
		dev->play_dma_data.dt.addr = res->start + I2S_TXDMA;
		dev->play_dma_data.dt.addr_width = bus_widths[idx];
		dev->play_dma_data.dt.fअगरo_size = fअगरo_depth *
			(fअगरo_width[idx2]) >> 8;
		dev->play_dma_data.dt.maxburst = 16;
	पूर्ण
	अगर (COMP1_RX_ENABLED(comp1)) अणु
		idx2 = COMP2_RX_WORDSIZE_0(comp2);

		dev->capability |= DWC_I2S_RECORD;
		dev->capture_dma_data.dt.addr = res->start + I2S_RXDMA;
		dev->capture_dma_data.dt.addr_width = bus_widths[idx];
		dev->capture_dma_data.dt.fअगरo_size = fअगरo_depth *
			(fअगरo_width[idx2] >> 8);
		dev->capture_dma_data.dt.maxburst = 16;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक dw_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा i2s_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा dw_i2s_dev *dev;
	काष्ठा resource *res;
	पूर्णांक ret, irq;
	काष्ठा snd_soc_dai_driver *dw_i2s_dai;
	स्थिर अक्षर *clk_id;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dw_i2s_dai = devm_kzalloc(&pdev->dev, माप(*dw_i2s_dai), GFP_KERNEL);
	अगर (!dw_i2s_dai)
		वापस -ENOMEM;

	dw_i2s_dai->ops = &dw_i2s_dai_ops;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->i2s_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dev->i2s_base))
		वापस PTR_ERR(dev->i2s_base);

	dev->dev = &pdev->dev;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq >= 0) अणु
		ret = devm_request_irq(&pdev->dev, irq, i2s_irq_handler, 0,
				pdev->name, dev);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "failed to request irq\n");
			वापस ret;
		पूर्ण
	पूर्ण

	dev->i2s_reg_comp1 = I2S_COMP_PARAM_1;
	dev->i2s_reg_comp2 = I2S_COMP_PARAM_2;
	अगर (pdata) अणु
		dev->capability = pdata->cap;
		clk_id = शून्य;
		dev->quirks = pdata->quirks;
		अगर (dev->quirks & DW_I2S_QUIRK_COMP_REG_OFFSET) अणु
			dev->i2s_reg_comp1 = pdata->i2s_reg_comp1;
			dev->i2s_reg_comp2 = pdata->i2s_reg_comp2;
		पूर्ण
		ret = dw_configure_dai_by_pd(dev, dw_i2s_dai, res, pdata);
	पूर्ण अन्यथा अणु
		clk_id = "i2sclk";
		ret = dw_configure_dai_by_dt(dev, dw_i2s_dai, res);
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	अगर (dev->capability & DW_I2S_MASTER) अणु
		अगर (pdata) अणु
			dev->i2s_clk_cfg = pdata->i2s_clk_cfg;
			अगर (!dev->i2s_clk_cfg) अणु
				dev_err(&pdev->dev, "no clock configure method\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		dev->clk = devm_clk_get(&pdev->dev, clk_id);

		अगर (IS_ERR(dev->clk))
			वापस PTR_ERR(dev->clk);

		ret = clk_prepare_enable(dev->clk);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	dev_set_drvdata(&pdev->dev, dev);
	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &dw_i2s_component,
					 dw_i2s_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "not able to register dai\n");
		जाओ err_clk_disable;
	पूर्ण

	अगर (!pdata) अणु
		अगर (irq >= 0) अणु
			ret = dw_pcm_रेजिस्टर(pdev);
			dev->use_pio = true;
		पूर्ण अन्यथा अणु
			ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य,
					0);
			dev->use_pio = false;
		पूर्ण

		अगर (ret) अणु
			dev_err(&pdev->dev, "could not register pcm: %d\n",
					ret);
			जाओ err_clk_disable;
		पूर्ण
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	वापस 0;

err_clk_disable:
	अगर (dev->capability & DW_I2S_MASTER)
		clk_disable_unprepare(dev->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक dw_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_i2s_dev *dev = dev_get_drvdata(&pdev->dev);

	अगर (dev->capability & DW_I2S_MASTER)
		clk_disable_unprepare(dev->clk);

	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dw_i2s_of_match[] = अणु
	अणु .compatible = "snps,designware-i2s",	 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dw_i2s_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops dwc_pm_ops = अणु
	SET_RUNTIME_PM_OPS(dw_i2s_runसमय_suspend, dw_i2s_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver dw_i2s_driver = अणु
	.probe		= dw_i2s_probe,
	.हटाओ		= dw_i2s_हटाओ,
	.driver		= अणु
		.name	= "designware-i2s",
		.of_match_table = of_match_ptr(dw_i2s_of_match),
		.pm = &dwc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_i2s_driver);

MODULE_AUTHOR("Rajeev Kumar <rajeevkumar.linux@gmail.com>");
MODULE_DESCRIPTION("DESIGNWARE I2S SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:designware_i2s");
