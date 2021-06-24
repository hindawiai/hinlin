<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is part of STM32 DFSDM ASoC DAI driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Authors: Arnaud Pouliquen <arnaud.pouliquen@st.com>
 *          Olivier Moysan <olivier.moysan@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/adc/sपंचांग32-dfsdm-adc.h>

#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#घोषणा STM32_ADFSDM_DRV_NAME "stm32-adfsdm"

#घोषणा DFSDM_MAX_PERIOD_SIZE	(PAGE_SIZE / 2)
#घोषणा DFSDM_MAX_PERIODS	6

काष्ठा sपंचांग32_adfsdm_priv अणु
	काष्ठा snd_soc_dai_driver dai_drv;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा device *dev;

	/* IIO */
	काष्ठा iio_channel *iio_ch;
	काष्ठा iio_cb_buffer *iio_cb;
	bool iio_active;

	/* PCM buffer */
	अचिन्हित अक्षर *pcm_buff;
	अचिन्हित पूर्णांक pos;

	काष्ठा mutex lock; /* protect against race condition on iio state */
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware sपंचांग32_adfsdm_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_PAUSE,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,

	.channels_min = 1,
	.channels_max = 1,

	.periods_min = 2,
	.periods_max = DFSDM_MAX_PERIODS,

	.period_bytes_max = DFSDM_MAX_PERIOD_SIZE,
	.buffer_bytes_max = DFSDM_MAX_PERIODS * DFSDM_MAX_PERIOD_SIZE
पूर्ण;

अटल व्योम sपंचांग32_adfsdm_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sपंचांग32_adfsdm_priv *priv = snd_soc_dai_get_drvdata(dai);

	mutex_lock(&priv->lock);
	अगर (priv->iio_active) अणु
		iio_channel_stop_all_cb(priv->iio_cb);
		priv->iio_active = false;
	पूर्ण
	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_dai_prepare(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sपंचांग32_adfsdm_priv *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	mutex_lock(&priv->lock);
	अगर (priv->iio_active) अणु
		iio_channel_stop_all_cb(priv->iio_cb);
		priv->iio_active = false;
	पूर्ण

	ret = iio_ग_लिखो_channel_attribute(priv->iio_ch,
					  substream->runसमय->rate, 0,
					  IIO_CHAN_INFO_SAMP_FREQ);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "%s: Failed to set %d sampling rate\n",
			__func__, substream->runसमय->rate);
		जाओ out;
	पूर्ण

	अगर (!priv->iio_active) अणु
		ret = iio_channel_start_all_cb(priv->iio_cb);
		अगर (!ret)
			priv->iio_active = true;
		अन्यथा
			dev_err(dai->dev, "%s: IIO channel start failed (%d)\n",
				__func__, ret);
	पूर्ण

out:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				   अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा sपंचांग32_adfsdm_priv *priv = snd_soc_dai_get_drvdata(dai);
	sमाप_प्रकार size;
	अक्षर str_freq[10];

	dev_dbg(dai->dev, "%s: Enter for freq %d\n", __func__, freq);

	/* Set IIO frequency अगर CODEC is master as घड़ी comes from SPI_IN */

	snम_लिखो(str_freq, माप(str_freq), "%u\n", freq);
	size = iio_ग_लिखो_channel_ext_info(priv->iio_ch, "spi_clk_freq",
					  str_freq, माप(str_freq));
	अगर (size != माप(str_freq)) अणु
		dev_err(dai->dev, "%s: Failed to set SPI clock\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sपंचांग32_adfsdm_dai_ops = अणु
	.shutकरोwn = sपंचांग32_adfsdm_shutकरोwn,
	.prepare = sपंचांग32_adfsdm_dai_prepare,
	.set_sysclk = sपंचांग32_adfsdm_set_sysclk,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver sपंचांग32_adfsdm_dai = अणु
	.capture = अणु
		    .channels_min = 1,
		    .channels_max = 1,
		    .क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			       SNDRV_PCM_FMTBIT_S32_LE,
		    .rates = SNDRV_PCM_RATE_CONTINUOUS,
		    .rate_min = 8000,
		    .rate_max = 48000,
		    पूर्ण,
	.ops = &sपंचांग32_adfsdm_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sपंचांग32_adfsdm_dai_component = अणु
	.name = "stm32_dfsdm_audio",
पूर्ण;

अटल व्योम sपंचांग32_स_नकल_32to16(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	अचिन्हित पूर्णांक i = 0;
	u16 *d = (u16 *)dest, *s = (u16 *)src;

	s++;
	क्रम (i = n >> 1; i > 0; i--) अणु
		*d++ = *s++;
		s++;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_afsdm_pcm_cb(स्थिर व्योम *data, माप_प्रकार size, व्योम *निजी)
अणु
	काष्ठा sपंचांग32_adfsdm_priv *priv = निजी;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(priv->substream);
	u8 *pcm_buff = priv->pcm_buff;
	u8 *src_buff = (u8 *)data;
	अचिन्हित पूर्णांक old_pos = priv->pos;
	माप_प्रकार buff_size = snd_pcm_lib_buffer_bytes(priv->substream);
	माप_प्रकार period_size = snd_pcm_lib_period_bytes(priv->substream);
	माप_प्रकार cur_size, src_size = size;
	snd_pcm_क्रमmat_t क्रमmat = priv->substream->runसमय->क्रमmat;

	अगर (क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
		src_size >>= 1;
	cur_size = src_size;

	dev_dbg(rtd->dev, "%s: buff_add :%pK, pos = %d, size = %zu\n",
		__func__, &pcm_buff[priv->pos], priv->pos, src_size);

	अगर ((priv->pos + src_size) > buff_size) अणु
		अगर (क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
			sपंचांग32_स_नकल_32to16(&pcm_buff[priv->pos], src_buff,
					    buff_size - priv->pos);
		अन्यथा
			स_नकल(&pcm_buff[priv->pos], src_buff,
			       buff_size - priv->pos);
		cur_size -= buff_size - priv->pos;
		priv->pos = 0;
	पूर्ण

	अगर (क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
		sपंचांग32_स_नकल_32to16(&pcm_buff[priv->pos],
				    &src_buff[src_size - cur_size], cur_size);
	अन्यथा
		स_नकल(&pcm_buff[priv->pos], &src_buff[src_size - cur_size],
		       cur_size);

	priv->pos = (priv->pos + cur_size) % buff_size;

	अगर (cur_size != src_size || (old_pos && (old_pos % period_size < size)))
		snd_pcm_period_elapsed(priv->substream);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_trigger(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sपंचांग32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		priv->pos = 0;
		वापस sपंचांग32_dfsdm_get_buff_cb(priv->iio_ch->indio_dev,
					       sपंचांग32_afsdm_pcm_cb, priv);
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		वापस sपंचांग32_dfsdm_release_buff_cb(priv->iio_ch->indio_dev);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_pcm_खोलो(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sपंचांग32_adfsdm_priv *priv = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	पूर्णांक ret;

	ret =  snd_soc_set_runसमय_hwparams(substream, &sपंचांग32_adfsdm_pcm_hw);
	अगर (!ret)
		priv->substream = substream;

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_pcm_बंद(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sपंचांग32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	priv->substream = शून्य;

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t sपंचांग32_adfsdm_pcm_poपूर्णांकer(
					    काष्ठा snd_soc_component *component,
					    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sपंचांग32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	वापस bytes_to_frames(substream->runसमय, priv->pos);
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_pcm_hw_params(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sपंचांग32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	priv->pcm_buff = substream->runसमय->dma_area;

	वापस iio_channel_cb_set_buffer_watermark(priv->iio_cb,
						   params_period_size(params));
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_pcm_new(काष्ठा snd_soc_component *component,
				काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा sपंचांग32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	अचिन्हित पूर्णांक size = DFSDM_MAX_PERIODS * DFSDM_MAX_PERIOD_SIZE;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       priv->dev, size, size);
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_dummy_cb(स्थिर व्योम *data, व्योम *निजी)
अणु
	/*
	 * This dummmy callback is requested by iio_channel_get_all_cb() API,
	 * but the sपंचांग32_dfsdm_get_buff_cb() API is used instead, to optimize
	 * DMA transfers.
	 */
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_component_driver sपंचांग32_adfsdm_soc_platक्रमm = अणु
	.खोलो		= sपंचांग32_adfsdm_pcm_खोलो,
	.बंद		= sपंचांग32_adfsdm_pcm_बंद,
	.hw_params	= sपंचांग32_adfsdm_pcm_hw_params,
	.trigger	= sपंचांग32_adfsdm_trigger,
	.poपूर्णांकer	= sपंचांग32_adfsdm_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= sपंचांग32_adfsdm_pcm_new,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_adfsdm_of_match[] = अणु
	अणु.compatible = "st,stm32h7-dfsdm-dai"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_adfsdm_of_match);

अटल पूर्णांक sपंचांग32_adfsdm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_adfsdm_priv *priv;
	काष्ठा snd_soc_component *component;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->dai_drv = sपंचांग32_adfsdm_dai;
	mutex_init(&priv->lock);

	dev_set_drvdata(&pdev->dev, priv);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &sपंचांग32_adfsdm_dai_component,
					      &priv->dai_drv, 1);
	अगर (ret < 0)
		वापस ret;

	/* Associate iio channel */
	priv->iio_ch  = devm_iio_channel_get_all(&pdev->dev);
	अगर (IS_ERR(priv->iio_ch))
		वापस PTR_ERR(priv->iio_ch);

	priv->iio_cb = iio_channel_get_all_cb(&pdev->dev, &sपंचांग32_adfsdm_dummy_cb, शून्य);
	अगर (IS_ERR(priv->iio_cb))
		वापस PTR_ERR(priv->iio_cb);

	component = devm_kzalloc(&pdev->dev, माप(*component), GFP_KERNEL);
	अगर (!component)
		वापस -ENOMEM;

	ret = snd_soc_component_initialize(component,
					   &sपंचांग32_adfsdm_soc_platक्रमm,
					   &pdev->dev);
	अगर (ret < 0)
		वापस ret;
#अगर_घोषित CONFIG_DEBUG_FS
	component->debugfs_prefix = "pcm";
#पूर्ण_अगर

	ret = snd_soc_add_component(component, शून्य, 0);
	अगर (ret < 0)
		dev_err(&pdev->dev, "%s: Failed to register PCM platform\n",
			__func__);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adfsdm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	snd_soc_unरेजिस्टर_component(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांग32_adfsdm_driver = अणु
	.driver = अणु
		   .name = STM32_ADFSDM_DRV_NAME,
		   .of_match_table = sपंचांग32_adfsdm_of_match,
		   पूर्ण,
	.probe = sपंचांग32_adfsdm_probe,
	.हटाओ = sपंचांग32_adfsdm_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_adfsdm_driver);

MODULE_DESCRIPTION("stm32 DFSDM DAI driver");
MODULE_AUTHOR("Arnaud Pouliquen <arnaud.pouliquen@st.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" STM32_ADFSDM_DRV_NAME);
