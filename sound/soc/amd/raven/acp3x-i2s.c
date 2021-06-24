<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// AMD ALSA SoC PCM Driver
//
//Copyright 2016 Advanced Micro Devices, Inc.

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <linux/dma-mapping.h>

#समावेश "acp3x.h"

#घोषणा DRV_NAME "acp3x_i2s_playcap"

अटल पूर्णांक acp3x_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
					अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा i2s_dev_data *adata;
	पूर्णांक mode;

	adata = snd_soc_dai_get_drvdata(cpu_dai);
	mode = fmt & SND_SOC_DAIFMT_FORMAT_MASK;
	चयन (mode) अणु
	हाल SND_SOC_DAIFMT_I2S:
		adata->tdm_mode = TDM_DISABLE;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		adata->tdm_mode = TDM_ENABLE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_i2s_set_tdm_slot(काष्ठा snd_soc_dai *cpu_dai,
		u32 tx_mask, u32 rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा i2s_dev_data *adata;
	u32 frm_len;
	u16 slot_len;

	adata = snd_soc_dai_get_drvdata(cpu_dai);

	/* These values are as per Hardware Spec */
	चयन (slot_width) अणु
	हाल SLOT_WIDTH_8:
		slot_len = 8;
		अवरोध;
	हाल SLOT_WIDTH_16:
		slot_len = 16;
		अवरोध;
	हाल SLOT_WIDTH_24:
		slot_len = 24;
		अवरोध;
	हाल SLOT_WIDTH_32:
		slot_len = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	frm_len = FRM_LEN | (slots << 15) | (slot_len << 18);
	adata->tdm_fmt = frm_len;
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_i2s_hwparams(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा i2s_stream_instance *rtd;
	काष्ठा snd_soc_pcm_runसमय *prtd;
	काष्ठा snd_soc_card *card;
	काष्ठा acp3x_platक्रमm_info *pinfo;
	काष्ठा i2s_dev_data *adata;
	u32 val;
	u32 reg_val, frmt_reg;

	prtd = asoc_substream_to_rtd(substream);
	rtd = substream->runसमय->निजी_data;
	card = prtd->card;
	adata = snd_soc_dai_get_drvdata(dai);
	pinfo = snd_soc_card_get_drvdata(card);
	अगर (pinfo) अणु
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			rtd->i2s_instance = pinfo->play_i2s_instance;
		अन्यथा
			rtd->i2s_instance = pinfo->cap_i2s_instance;
	पूर्ण

	/* These values are as per Hardware Spec */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_U8:
	हाल SNDRV_PCM_FORMAT_S8:
		rtd->xfer_resolution = 0x0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		rtd->xfer_resolution = 0x02;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		rtd->xfer_resolution = 0x04;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		rtd->xfer_resolution = 0x05;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			reg_val = mmACP_BTTDM_ITER;
			frmt_reg = mmACP_BTTDM_TXFRMT;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			reg_val = mmACP_I2STDM_ITER;
			frmt_reg = mmACP_I2STDM_TXFRMT;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (rtd->i2s_instance) अणु
		हाल I2S_BT_INSTANCE:
			reg_val = mmACP_BTTDM_IRER;
			frmt_reg = mmACP_BTTDM_RXFRMT;
			अवरोध;
		हाल I2S_SP_INSTANCE:
		शेष:
			reg_val = mmACP_I2STDM_IRER;
			frmt_reg = mmACP_I2STDM_RXFRMT;
		पूर्ण
	पूर्ण
	अगर (adata->tdm_mode) अणु
		val = rv_पढ़ोl(rtd->acp3x_base + reg_val);
		rv_ग_लिखोl(val | 0x2, rtd->acp3x_base + reg_val);
		rv_ग_लिखोl(adata->tdm_fmt, rtd->acp3x_base + frmt_reg);
	पूर्ण
	val = rv_पढ़ोl(rtd->acp3x_base + reg_val);
	val &= ~ACP3x_ITER_IRER_SAMP_LEN_MASK;
	val = val | (rtd->xfer_resolution  << 3);
	rv_ग_लिखोl(val, rtd->acp3x_base + reg_val);
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_i2s_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा i2s_stream_instance *rtd;
	u32 ret, val, period_bytes, reg_val, ier_val, water_val;
	u32 buf_size, buf_reg;

	rtd = substream->runसमय->निजी_data;
	period_bytes = frames_to_bytes(substream->runसमय,
			substream->runसमय->period_size);
	buf_size = frames_to_bytes(substream->runसमय,
			substream->runसमय->buffer_size);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		rtd->bytescount = acp_get_byte_count(rtd,
						substream->stream);
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				water_val =
					mmACP_BT_TX_INTR_WATERMARK_SIZE;
				reg_val = mmACP_BTTDM_ITER;
				ier_val = mmACP_BTTDM_IER;
				buf_reg = mmACP_BT_TX_RINGबफ_मानE;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				water_val =
					mmACP_I2S_TX_INTR_WATERMARK_SIZE;
				reg_val = mmACP_I2STDM_ITER;
				ier_val = mmACP_I2STDM_IER;
				buf_reg = mmACP_I2S_TX_RINGबफ_मानE;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				water_val =
					mmACP_BT_RX_INTR_WATERMARK_SIZE;
				reg_val = mmACP_BTTDM_IRER;
				ier_val = mmACP_BTTDM_IER;
				buf_reg = mmACP_BT_RX_RINGबफ_मानE;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				water_val =
					mmACP_I2S_RX_INTR_WATERMARK_SIZE;
				reg_val = mmACP_I2STDM_IRER;
				ier_val = mmACP_I2STDM_IER;
				buf_reg = mmACP_I2S_RX_RINGबफ_मानE;
			पूर्ण
		पूर्ण
		rv_ग_लिखोl(period_bytes, rtd->acp3x_base + water_val);
		rv_ग_लिखोl(buf_size, rtd->acp3x_base + buf_reg);
		val = rv_पढ़ोl(rtd->acp3x_base + reg_val);
		val = val | BIT(0);
		rv_ग_लिखोl(val, rtd->acp3x_base + reg_val);
		rv_ग_लिखोl(1, rtd->acp3x_base + ier_val);
		ret = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				reg_val = mmACP_BTTDM_ITER;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				reg_val = mmACP_I2STDM_ITER;
			पूर्ण

		पूर्ण अन्यथा अणु
			चयन (rtd->i2s_instance) अणु
			हाल I2S_BT_INSTANCE:
				reg_val = mmACP_BTTDM_IRER;
				अवरोध;
			हाल I2S_SP_INSTANCE:
			शेष:
				reg_val = mmACP_I2STDM_IRER;
			पूर्ण
		पूर्ण
		val = rv_पढ़ोl(rtd->acp3x_base + reg_val);
		val = val & ~BIT(0);
		rv_ग_लिखोl(val, rtd->acp3x_base + reg_val);

		अगर (!(rv_पढ़ोl(rtd->acp3x_base + mmACP_BTTDM_ITER) & BIT(0)) &&
		     !(rv_पढ़ोl(rtd->acp3x_base + mmACP_BTTDM_IRER) & BIT(0)))
			rv_ग_लिखोl(0, rtd->acp3x_base + mmACP_BTTDM_IER);
		अगर (!(rv_पढ़ोl(rtd->acp3x_base + mmACP_I2STDM_ITER) & BIT(0)) &&
		     !(rv_पढ़ोl(rtd->acp3x_base + mmACP_I2STDM_IRER) & BIT(0)))
			rv_ग_लिखोl(0, rtd->acp3x_base + mmACP_I2STDM_IER);
		ret = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops acp3x_i2s_dai_ops = अणु
	.hw_params = acp3x_i2s_hwparams,
	.trigger = acp3x_i2s_trigger,
	.set_fmt = acp3x_i2s_set_fmt,
	.set_tdm_slot = acp3x_i2s_set_tdm_slot,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver acp3x_dai_component = अणु
	.name           = DRV_NAME,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver acp3x_i2s_dai = अणु
	.playback = अणु
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8 |
			SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S32_LE,
		.channels_min = 2,
		.channels_max = 8,
		.rate_min = 8000,
		.rate_max = 96000,
	पूर्ण,
	.capture = अणु
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8 |
			SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S32_LE,
		.channels_min = 2,
		.channels_max = 2,
		.rate_min = 8000,
		.rate_max = 48000,
	पूर्ण,
	.ops = &acp3x_i2s_dai_ops,
पूर्ण;

अटल पूर्णांक acp3x_dai_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा i2s_dev_data *adata;
	पूर्णांक ret;

	adata = devm_kzalloc(&pdev->dev, माप(काष्ठा i2s_dev_data),
			GFP_KERNEL);
	अगर (!adata)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "IORESOURCE_MEM FAILED\n");
		वापस -ENOMEM;
	पूर्ण
	adata->acp3x_base = devm_ioremap(&pdev->dev, res->start,
						resource_size(res));
	अगर (!adata->acp3x_base)
		वापस -ENOMEM;

	adata->i2s_irq = res->start;
	dev_set_drvdata(&pdev->dev, adata);
	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&acp3x_dai_component, &acp3x_i2s_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Fail to register acp i2s dai\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acp3x_dai_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* As we use devm_ memory alloc there is nothing TBD here */

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver acp3x_dai_driver = अणु
	.probe = acp3x_dai_probe,
	.हटाओ = acp3x_dai_हटाओ,
	.driver = अणु
		.name = "acp3x_i2s_playcap",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(acp3x_dai_driver);

MODULE_AUTHOR("Vishnuvardhanrao.Ravulapati@amd.com");
MODULE_DESCRIPTION("AMD ACP 3.x PCM Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:"DRV_NAME);
