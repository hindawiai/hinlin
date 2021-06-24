<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// linux/sound/bcm/bcm63xx-pcm-whistler.c
// BCM63xx whistler pcm पूर्णांकerface
// Copyright (c) 2020 Broadcom Corporation
// Author: Kevin-Ke Li <kevin-ke.li@broadcom.com>

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_device.h>
#समावेश <sound/soc.h>
#समावेश "bcm63xx-i2s.h"


काष्ठा i2s_dma_desc अणु
	अचिन्हित अक्षर *dma_area;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक dma_len;
पूर्ण;

काष्ठा bcm63xx_runसमय_data अणु
	पूर्णांक dma_len;
	dma_addr_t dma_addr;
	dma_addr_t dma_addr_next;
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware bcm63xx_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE, /* support S32 only */
	.period_bytes_max = 8192 - 32,
	.periods_min = 1,
	.periods_max = PAGE_SIZE/माप(काष्ठा i2s_dma_desc),
	.buffer_bytes_max = 128 * 1024,
	.fअगरo_size = 32,
पूर्ण;

अटल पूर्णांक bcm63xx_pcm_hw_params(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा i2s_dma_desc *dma_desc;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);
	runसमय->dma_bytes = params_buffer_bytes(params);

	dma_desc = kzalloc(माप(*dma_desc), GFP_NOWAIT);
	अगर (!dma_desc)
		वापस -ENOMEM;

	snd_soc_dai_set_dma_data(asoc_rtd_to_cpu(rtd, 0), substream, dma_desc);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2s_dma_desc	*dma_desc;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	dma_desc = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	kमुक्त(dma_desc);
	snd_pcm_set_runसमय_buffer(substream, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_pcm_trigger(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा bcm_i2s_priv *i2s_priv;
	काष्ठा regmap   *regmap_i2s;

	rtd = asoc_substream_to_rtd(substream);
	i2s_priv = dev_get_drvdata(asoc_rtd_to_cpu(rtd, 0)->dev);
	regmap_i2s = i2s_priv->regmap_i2s;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
			regmap_update_bits(regmap_i2s,
					   I2S_TX_IRQ_EN,
					   I2S_TX_DESC_OFF_INTR_EN,
					   I2S_TX_DESC_OFF_INTR_EN);
			regmap_update_bits(regmap_i2s,
					   I2S_TX_CFG,
					   I2S_TX_ENABLE_MASK,
					   I2S_TX_ENABLE);
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			regmap_ग_लिखो(regmap_i2s,
				     I2S_TX_IRQ_EN,
				     0);
			regmap_update_bits(regmap_i2s,
					   I2S_TX_CFG,
					   I2S_TX_ENABLE_MASK,
					   0);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
			regmap_update_bits(regmap_i2s,
					   I2S_RX_IRQ_EN,
					   I2S_RX_DESC_OFF_INTR_EN_MSK,
					   I2S_RX_DESC_OFF_INTR_EN);
			regmap_update_bits(regmap_i2s,
					   I2S_RX_CFG,
					   I2S_RX_ENABLE_MASK,
					   I2S_RX_ENABLE);
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			regmap_update_bits(regmap_i2s,
					   I2S_RX_IRQ_EN,
					   I2S_RX_DESC_OFF_INTR_EN_MSK,
					   0);
			regmap_update_bits(regmap_i2s,
					   I2S_RX_CFG,
					   I2S_RX_ENABLE_MASK,
					   0);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_pcm_prepare(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा i2s_dma_desc	*dma_desc;
	काष्ठा regmap		*regmap_i2s;
	काष्ठा bcm_i2s_priv	*i2s_priv;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	uपूर्णांक32_t regaddr_desclen, regaddr_descaddr;

	dma_desc = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	dma_desc->dma_len  = snd_pcm_lib_period_bytes(substream);
	dma_desc->dma_addr = runसमय->dma_addr;
	dma_desc->dma_area = runसमय->dma_area;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		regaddr_desclen = I2S_TX_DESC_IFF_LEN;
		regaddr_descaddr = I2S_TX_DESC_IFF_ADDR;
	पूर्ण अन्यथा अणु
		regaddr_desclen = I2S_RX_DESC_IFF_LEN;
		regaddr_descaddr = I2S_RX_DESC_IFF_ADDR;
	पूर्ण

	i2s_priv = dev_get_drvdata(asoc_rtd_to_cpu(rtd, 0)->dev);
	regmap_i2s = i2s_priv->regmap_i2s;

	regmap_ग_लिखो(regmap_i2s, regaddr_desclen, dma_desc->dma_len);
	regmap_ग_लिखो(regmap_i2s, regaddr_descaddr, dma_desc->dma_addr);

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
bcm63xx_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_uframes_t x;
	काष्ठा bcm63xx_runसमय_data *prtd = substream->runसमय->निजी_data;

	अगर (!prtd->dma_addr_next)
		prtd->dma_addr_next = substream->runसमय->dma_addr;

	x = bytes_to_frames(substream->runसमय,
		prtd->dma_addr_next - substream->runसमय->dma_addr);

	वापस x == substream->runसमय->buffer_size ? 0 : x;
पूर्ण

अटल पूर्णांक bcm63xx_pcm_mmap(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream,
				काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	वापस  dma_mmap_wc(substream->pcm->card->dev, vma,
			    runसमय->dma_area,
			    runसमय->dma_addr,
			    runसमय->dma_bytes);

पूर्ण

अटल पूर्णांक bcm63xx_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm63xx_runसमय_data *prtd;

	runसमय->hw = bcm63xx_pcm_hardware;
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 32);
	अगर (ret)
		जाओ out;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 32);
	अगर (ret)
		जाओ out;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		जाओ out;

	ret = -ENOMEM;
	prtd = kzalloc(माप(*prtd), GFP_KERNEL);
	अगर (!prtd)
		जाओ out;

	runसमय->निजी_data = prtd;
	वापस 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_pcm_बंद(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm63xx_runसमय_data *prtd = runसमय->निजी_data;

	kमुक्त(prtd);
	वापस 0;
पूर्ण

अटल irqवापस_t i2s_dma_isr(पूर्णांक irq, व्योम *bcm_i2s_priv)
अणु
	अचिन्हित पूर्णांक availdepth, अगरflevel, offlevel, पूर्णांक_status, val_1, val_2;
	काष्ठा bcm63xx_runसमय_data *prtd;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा regmap *regmap_i2s;
	काष्ठा i2s_dma_desc *dma_desc;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा bcm_i2s_priv *i2s_priv;

	i2s_priv = (काष्ठा bcm_i2s_priv *)bcm_i2s_priv;
	regmap_i2s = i2s_priv->regmap_i2s;

	/* rx */
	regmap_पढ़ो(regmap_i2s, I2S_RX_IRQ_CTL, &पूर्णांक_status);

	अगर (पूर्णांक_status & I2S_RX_DESC_OFF_INTR_EN_MSK) अणु
		substream = i2s_priv->capture_substream;
		runसमय = substream->runसमय;
		rtd = asoc_substream_to_rtd(substream);
		prtd = runसमय->निजी_data;
		dma_desc = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);

		offlevel = (पूर्णांक_status & I2S_RX_DESC_OFF_LEVEL_MASK) >>
			   I2S_RX_DESC_OFF_LEVEL_SHIFT;
		जबतक (offlevel) अणु
			regmap_पढ़ो(regmap_i2s, I2S_RX_DESC_OFF_ADDR, &val_1);
			regmap_पढ़ो(regmap_i2s, I2S_RX_DESC_OFF_LEN, &val_2);
			offlevel--;
		पूर्ण
		prtd->dma_addr_next = val_1 + val_2;
		अगरflevel = (पूर्णांक_status & I2S_RX_DESC_IFF_LEVEL_MASK) >>
			   I2S_RX_DESC_IFF_LEVEL_SHIFT;

		availdepth = I2S_DESC_FIFO_DEPTH - अगरflevel;
		जबतक (availdepth) अणु
			dma_desc->dma_addr +=
					snd_pcm_lib_period_bytes(substream);
			dma_desc->dma_area +=
					snd_pcm_lib_period_bytes(substream);
			अगर (dma_desc->dma_addr - runसमय->dma_addr >=
						runसमय->dma_bytes) अणु
				dma_desc->dma_addr = runसमय->dma_addr;
				dma_desc->dma_area = runसमय->dma_area;
			पूर्ण

			prtd->dma_addr = dma_desc->dma_addr;
			regmap_ग_लिखो(regmap_i2s, I2S_RX_DESC_IFF_LEN,
				     snd_pcm_lib_period_bytes(substream));
			regmap_ग_लिखो(regmap_i2s, I2S_RX_DESC_IFF_ADDR,
				     dma_desc->dma_addr);
			availdepth--;
		पूर्ण

		snd_pcm_period_elapsed(substream);

		/* Clear पूर्णांकerrupt by writing 0 */
		regmap_update_bits(regmap_i2s, I2S_RX_IRQ_CTL,
				   I2S_RX_INTR_MASK, 0);
	पूर्ण

	/* tx */
	regmap_पढ़ो(regmap_i2s, I2S_TX_IRQ_CTL, &पूर्णांक_status);

	अगर (पूर्णांक_status & I2S_TX_DESC_OFF_INTR_EN_MSK) अणु
		substream = i2s_priv->play_substream;
		runसमय = substream->runसमय;
		rtd = asoc_substream_to_rtd(substream);
		prtd = runसमय->निजी_data;
		dma_desc = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);

		offlevel = (पूर्णांक_status & I2S_TX_DESC_OFF_LEVEL_MASK) >>
			   I2S_TX_DESC_OFF_LEVEL_SHIFT;
		जबतक (offlevel) अणु
			regmap_पढ़ो(regmap_i2s, I2S_TX_DESC_OFF_ADDR, &val_1);
			regmap_पढ़ो(regmap_i2s, I2S_TX_DESC_OFF_LEN,  &val_2);
			prtd->dma_addr_next = val_1 + val_2;
			offlevel--;
		पूर्ण

		अगरflevel = (पूर्णांक_status & I2S_TX_DESC_IFF_LEVEL_MASK) >>
			I2S_TX_DESC_IFF_LEVEL_SHIFT;
		availdepth = I2S_DESC_FIFO_DEPTH - अगरflevel;

		जबतक (availdepth) अणु
			dma_desc->dma_addr +=
					snd_pcm_lib_period_bytes(substream);
			dma_desc->dma_area +=
					snd_pcm_lib_period_bytes(substream);

			अगर (dma_desc->dma_addr - runसमय->dma_addr >=
							runसमय->dma_bytes) अणु
				dma_desc->dma_addr = runसमय->dma_addr;
				dma_desc->dma_area = runसमय->dma_area;
			पूर्ण

			prtd->dma_addr = dma_desc->dma_addr;
			regmap_ग_लिखो(regmap_i2s, I2S_TX_DESC_IFF_LEN,
				snd_pcm_lib_period_bytes(substream));
			regmap_ग_लिखो(regmap_i2s, I2S_TX_DESC_IFF_ADDR,
					dma_desc->dma_addr);
			availdepth--;
		पूर्ण

		snd_pcm_period_elapsed(substream);

		/* Clear पूर्णांकerrupt by writing 0 */
		regmap_update_bits(regmap_i2s, I2S_TX_IRQ_CTL,
				   I2S_TX_INTR_MASK, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm63xx_pcm_pपुनः_स्मृतिate_dma_buffer(काष्ठा snd_pcm *pcm, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_substream *substream = pcm->streams[stream].substream;
	काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;
	माप_प्रकार size = bcm63xx_pcm_hardware.buffer_bytes_max;

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->निजी_data = शून्य;

	buf->area = dma_alloc_wc(pcm->card->dev,
				 size, &buf->addr,
				 GFP_KERNEL);
	अगर (!buf->area)
		वापस -ENOMEM;
	buf->bytes = size;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_soc_pcm_new(काष्ठा snd_soc_component *component,
		काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा bcm_i2s_priv *i2s_priv;
	पूर्णांक ret;

	i2s_priv = dev_get_drvdata(asoc_rtd_to_cpu(rtd, 0)->dev);

	of_dma_configure(pcm->card->dev, pcm->card->dev->of_node, 1);

	ret = dma_coerce_mask_and_coherent(pcm->card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ out;

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		ret = bcm63xx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
						 SNDRV_PCM_STREAM_PLAYBACK);
		अगर (ret)
			जाओ out;

		i2s_priv->play_substream =
			pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	पूर्ण

	अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) अणु
		ret = bcm63xx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
					SNDRV_PCM_STREAM_CAPTURE);
		अगर (ret)
			जाओ out;
		i2s_priv->capture_substream =
			pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम bcm63xx_pcm_मुक्त_dma_buffers(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm *pcm)
अणु
	पूर्णांक stream;
	काष्ठा snd_dma_buffer *buf;
	काष्ठा snd_pcm_substream *substream;

	क्रम (stream = 0; stream < 2; stream++) अणु
		substream = pcm->streams[stream].substream;
		अगर (!substream)
			जारी;
		buf = &substream->dma_buffer;
		अगर (!buf->area)
			जारी;
		dma_मुक्त_wc(pcm->card->dev, buf->bytes,
					buf->area, buf->addr);
		buf->area = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver bcm63xx_soc_platक्रमm = अणु
	.खोलो = bcm63xx_pcm_खोलो,
	.बंद = bcm63xx_pcm_बंद,
	.hw_params = bcm63xx_pcm_hw_params,
	.hw_मुक्त = bcm63xx_pcm_hw_मुक्त,
	.prepare = bcm63xx_pcm_prepare,
	.trigger = bcm63xx_pcm_trigger,
	.poपूर्णांकer = bcm63xx_pcm_poपूर्णांकer,
	.mmap = bcm63xx_pcm_mmap,
	.pcm_स्थिरruct = bcm63xx_soc_pcm_new,
	.pcm_deकाष्ठा = bcm63xx_pcm_मुक्त_dma_buffers,
पूर्ण;

पूर्णांक bcm63xx_soc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev,
			       काष्ठा bcm_i2s_priv *i2s_priv)
अणु
	पूर्णांक ret;

	i2s_priv->r_irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!i2s_priv->r_irq) अणु
		dev_err(&pdev->dev, "Unable to get register irq resource.\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, i2s_priv->r_irq->start, i2s_dma_isr,
			i2s_priv->r_irq->flags, "i2s_dma", (व्योम *)i2s_priv);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"i2s_init: failed to request interrupt.ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					&bcm63xx_soc_platक्रमm, शून्य, 0);
पूर्ण

पूर्णांक bcm63xx_soc_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

MODULE_AUTHOR("Kevin,Li <kevin-ke.li@broadcom.com>");
MODULE_DESCRIPTION("Broadcom DSL XPON ASOC PCM Interface");
MODULE_LICENSE("GPL v2");
