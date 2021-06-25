<शैली गुरु>
/*
 * ALSA SoC Synopsys PIO PCM क्रम I2S driver
 *
 * sound/soc/dwc/designware_pcm.c
 *
 * Copyright (C) 2016 Synopsys
 * Jose Abreu <joabreu@synopsys.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/पन.स>
#समावेश <linux/rcupdate.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "local.h"

#घोषणा BUFFER_BYTES_MAX	(3 * 2 * 8 * PERIOD_BYTES_MIN)
#घोषणा PERIOD_BYTES_MIN	4096
#घोषणा PERIODS_MIN		2

#घोषणा dw_pcm_tx_fn(sample_bits) \
अटल अचिन्हित पूर्णांक dw_pcm_tx_##sample_bits(काष्ठा dw_i2s_dev *dev, \
		काष्ठा snd_pcm_runसमय *runसमय, अचिन्हित पूर्णांक tx_ptr, \
		bool *period_elapsed) \
अणु \
	स्थिर u##sample_bits (*p)[2] = (व्योम *)runसमय->dma_area; \
	अचिन्हित पूर्णांक period_pos = tx_ptr % runसमय->period_size; \
	पूर्णांक i; \
\
	क्रम (i = 0; i < dev->fअगरo_th; i++) अणु \
		ioग_लिखो32(p[tx_ptr][0], dev->i2s_base + LRBR_LTHR(0)); \
		ioग_लिखो32(p[tx_ptr][1], dev->i2s_base + RRBR_RTHR(0)); \
		period_pos++; \
		अगर (++tx_ptr >= runसमय->buffer_size) \
			tx_ptr = 0; \
	पूर्ण \
	*period_elapsed = period_pos >= runसमय->period_size; \
	वापस tx_ptr; \
पूर्ण

#घोषणा dw_pcm_rx_fn(sample_bits) \
अटल अचिन्हित पूर्णांक dw_pcm_rx_##sample_bits(काष्ठा dw_i2s_dev *dev, \
		काष्ठा snd_pcm_runसमय *runसमय, अचिन्हित पूर्णांक rx_ptr, \
		bool *period_elapsed) \
अणु \
	u##sample_bits (*p)[2] = (व्योम *)runसमय->dma_area; \
	अचिन्हित पूर्णांक period_pos = rx_ptr % runसमय->period_size; \
	पूर्णांक i; \
\
	क्रम (i = 0; i < dev->fअगरo_th; i++) अणु \
		p[rx_ptr][0] = ioपढ़ो32(dev->i2s_base + LRBR_LTHR(0)); \
		p[rx_ptr][1] = ioपढ़ो32(dev->i2s_base + RRBR_RTHR(0)); \
		period_pos++; \
		अगर (++rx_ptr >= runसमय->buffer_size) \
			rx_ptr = 0; \
	पूर्ण \
	*period_elapsed = period_pos >= runसमय->period_size; \
	वापस rx_ptr; \
पूर्ण

dw_pcm_tx_fn(16);
dw_pcm_tx_fn(32);
dw_pcm_rx_fn(16);
dw_pcm_rx_fn(32);

#अघोषित dw_pcm_tx_fn
#अघोषित dw_pcm_rx_fn

अटल स्थिर काष्ठा snd_pcm_hardware dw_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BLOCK_TRANSFER,
	.rates = SNDRV_PCM_RATE_32000 |
		SNDRV_PCM_RATE_44100 |
		SNDRV_PCM_RATE_48000,
	.rate_min = 32000,
	.rate_max = 48000,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		SNDRV_PCM_FMTBIT_S24_LE |
		SNDRV_PCM_FMTBIT_S32_LE,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = BUFFER_BYTES_MAX,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = BUFFER_BYTES_MAX / PERIODS_MIN,
	.periods_min = PERIODS_MIN,
	.periods_max = BUFFER_BYTES_MAX / PERIOD_BYTES_MIN,
	.fअगरo_size = 16,
पूर्ण;

अटल व्योम dw_pcm_transfer(काष्ठा dw_i2s_dev *dev, bool push)
अणु
	काष्ठा snd_pcm_substream *substream;
	bool active, period_elapsed;

	rcu_पढ़ो_lock();
	अगर (push)
		substream = rcu_dereference(dev->tx_substream);
	अन्यथा
		substream = rcu_dereference(dev->rx_substream);
	active = substream && snd_pcm_running(substream);
	अगर (active) अणु
		अचिन्हित पूर्णांक ptr;
		अचिन्हित पूर्णांक new_ptr;

		अगर (push) अणु
			ptr = READ_ONCE(dev->tx_ptr);
			new_ptr = dev->tx_fn(dev, substream->runसमय, ptr,
					&period_elapsed);
			cmpxchg(&dev->tx_ptr, ptr, new_ptr);
		पूर्ण अन्यथा अणु
			ptr = READ_ONCE(dev->rx_ptr);
			new_ptr = dev->rx_fn(dev, substream->runसमय, ptr,
					&period_elapsed);
			cmpxchg(&dev->rx_ptr, ptr, new_ptr);
		पूर्ण

		अगर (period_elapsed)
			snd_pcm_period_elapsed(substream);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम dw_pcm_push_tx(काष्ठा dw_i2s_dev *dev)
अणु
	dw_pcm_transfer(dev, true);
पूर्ण

व्योम dw_pcm_pop_rx(काष्ठा dw_i2s_dev *dev)
अणु
	dw_pcm_transfer(dev, false);
पूर्ण

अटल पूर्णांक dw_pcm_खोलो(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा dw_i2s_dev *dev = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	snd_soc_set_runसमय_hwparams(substream, &dw_pcm_hardware);
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	runसमय->निजी_data = dev;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcm_बंद(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	synchronize_rcu();
	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcm_hw_params(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dw_i2s_dev *dev = runसमय->निजी_data;

	चयन (params_channels(hw_params)) अणु
	हाल 2:
		अवरोध;
	शेष:
		dev_err(dev->dev, "invalid channels number\n");
		वापस -EINVAL;
	पूर्ण

	चयन (params_क्रमmat(hw_params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		dev->tx_fn = dw_pcm_tx_16;
		dev->rx_fn = dw_pcm_rx_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
	हाल SNDRV_PCM_FORMAT_S32_LE:
		dev->tx_fn = dw_pcm_tx_32;
		dev->rx_fn = dw_pcm_rx_32;
		अवरोध;
	शेष:
		dev_err(dev->dev, "invalid format\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcm_trigger(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dw_i2s_dev *dev = runसमय->निजी_data;
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			WRITE_ONCE(dev->tx_ptr, 0);
			rcu_assign_poपूर्णांकer(dev->tx_substream, substream);
		पूर्ण अन्यथा अणु
			WRITE_ONCE(dev->rx_ptr, 0);
			rcu_assign_poपूर्णांकer(dev->rx_substream, substream);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			rcu_assign_poपूर्णांकer(dev->tx_substream, शून्य);
		अन्यथा
			rcu_assign_poपूर्णांकer(dev->rx_substream, शून्य);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t dw_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dw_i2s_dev *dev = runसमय->निजी_data;
	snd_pcm_uframes_t pos;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		pos = READ_ONCE(dev->tx_ptr);
	अन्यथा
		pos = READ_ONCE(dev->rx_ptr);

	वापस pos < runसमय->buffer_size ? pos : 0;
पूर्ण

अटल पूर्णांक dw_pcm_new(काष्ठा snd_soc_component *component,
		      काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	माप_प्रकार size = dw_pcm_hardware.buffer_bytes_max;

	snd_pcm_set_managed_buffer_all(rtd->pcm,
			SNDRV_DMA_TYPE_CONTINUOUS,
			शून्य, size, size);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver dw_pcm_component = अणु
	.खोलो		= dw_pcm_खोलो,
	.बंद		= dw_pcm_बंद,
	.hw_params	= dw_pcm_hw_params,
	.trigger	= dw_pcm_trigger,
	.poपूर्णांकer	= dw_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= dw_pcm_new,
पूर्ण;

पूर्णांक dw_pcm_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &dw_pcm_component,
					       शून्य, 0);
पूर्ण
