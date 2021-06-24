<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 *
 * lpass-platक्रमm.c -- ALSA SoC platक्रमm driver क्रम QTi LPASS
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश "lpass-lpaif-reg.h"
#समावेश "lpass.h"

#घोषणा DRV_NAME "lpass-platform"

काष्ठा lpass_pcm_data अणु
	पूर्णांक dma_ch;
	पूर्णांक i2s_port;
पूर्ण;

#घोषणा LPASS_PLATFORM_BUFFER_SIZE	(24 *  2 * 1024)
#घोषणा LPASS_PLATFORM_PERIODS		2

अटल स्थिर काष्ठा snd_pcm_hardware lpass_platक्रमm_pcm_hardware = अणु
	.info			=	SNDRV_PCM_INFO_MMAP |
					SNDRV_PCM_INFO_MMAP_VALID |
					SNDRV_PCM_INFO_INTERLEAVED |
					SNDRV_PCM_INFO_PAUSE |
					SNDRV_PCM_INFO_RESUME,
	.क्रमmats		=	SNDRV_PCM_FMTBIT_S16 |
					SNDRV_PCM_FMTBIT_S24 |
					SNDRV_PCM_FMTBIT_S32,
	.rates			=	SNDRV_PCM_RATE_8000_192000,
	.rate_min		=	8000,
	.rate_max		=	192000,
	.channels_min		=	1,
	.channels_max		=	8,
	.buffer_bytes_max	=	LPASS_PLATFORM_BUFFER_SIZE,
	.period_bytes_max	=	LPASS_PLATFORM_BUFFER_SIZE /
						LPASS_PLATFORM_PERIODS,
	.period_bytes_min	=	LPASS_PLATFORM_BUFFER_SIZE /
						LPASS_PLATFORM_PERIODS,
	.periods_min		=	LPASS_PLATFORM_PERIODS,
	.periods_max		=	LPASS_PLATFORM_PERIODS,
	.fअगरo_size		=	0,
पूर्ण;

अटल पूर्णांक lpass_platक्रमm_alloc_dmactl_fields(काष्ठा device *dev,
					 काष्ठा regmap *map)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	काष्ठा lpaअगर_dmactl *rd_dmactl, *wr_dmactl;
	पूर्णांक rval;

	drvdata->rd_dmactl = devm_kzalloc(dev, माप(काष्ठा lpaअगर_dmactl),
					  GFP_KERNEL);
	अगर (drvdata->rd_dmactl == शून्य)
		वापस -ENOMEM;

	drvdata->wr_dmactl = devm_kzalloc(dev, माप(काष्ठा lpaअगर_dmactl),
					  GFP_KERNEL);
	अगर (drvdata->wr_dmactl == शून्य)
		वापस -ENOMEM;

	rd_dmactl = drvdata->rd_dmactl;
	wr_dmactl = drvdata->wr_dmactl;

	rval = devm_regmap_field_bulk_alloc(dev, map, &rd_dmactl->पूर्णांकf,
					    &v->rdma_पूर्णांकf, 6);
	अगर (rval)
		वापस rval;

	वापस devm_regmap_field_bulk_alloc(dev, map, &wr_dmactl->पूर्णांकf,
					    &v->wrdma_पूर्णांकf, 6);
पूर्ण

अटल पूर्णांक lpass_platक्रमm_alloc_hdmidmactl_fields(काष्ठा device *dev,
					 काष्ठा regmap *map)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	काष्ठा lpaअगर_dmactl *rd_dmactl;

	rd_dmactl = devm_kzalloc(dev, माप(काष्ठा lpaअगर_dmactl), GFP_KERNEL);
	अगर (rd_dmactl == शून्य)
		वापस -ENOMEM;

	drvdata->hdmi_rd_dmactl = rd_dmactl;

	वापस devm_regmap_field_bulk_alloc(dev, map, &rd_dmactl->bursten,
					    &v->hdmi_rdma_bursten, 8);
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_खोलो(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक ret, dma_ch, dir = substream->stream;
	काष्ठा lpass_pcm_data *data;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;

	component->id = dai_id;
	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->i2s_port = cpu_dai->driver->id;
	runसमय->निजी_data = data;

	अगर (v->alloc_dma_channel)
		dma_ch = v->alloc_dma_channel(drvdata, dir, dai_id);
	अन्यथा
		dma_ch = 0;

	अगर (dma_ch < 0) अणु
		kमुक्त(data);
		वापस dma_ch;
	पूर्ण

	अगर (cpu_dai->driver->id == LPASS_DP_RX) अणु
		map = drvdata->hdmiअगर_map;
		drvdata->hdmi_substream[dma_ch] = substream;
	पूर्ण अन्यथा अणु
		map = drvdata->lpaअगर_map;
		drvdata->substream[dma_ch] = substream;
	पूर्ण
	data->dma_ch = dma_ch;
	ret = regmap_ग_लिखो(map,
			LPAIF_DMACTL_REG(v, dma_ch, dir, data->i2s_port), 0);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev,
			"error writing to rdmactl reg: %d\n", ret);
		वापस ret;
	पूर्ण
	snd_soc_set_runसमय_hwparams(substream, &lpass_platक्रमm_pcm_hardware);

	runसमय->dma_bytes = lpass_platक्रमm_pcm_hardware.buffer_bytes_max;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
			SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0) अणु
		kमुक्त(data);
		dev_err(soc_runसमय->dev, "setting constraints failed: %d\n",
			ret);
		वापस -EINVAL;
	पूर्ण

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_बंद(काष्ठा snd_soc_component *component,
				       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा lpass_variant *v = drvdata->variant;
	काष्ठा lpass_pcm_data *data;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;

	data = runसमय->निजी_data;
	अगर (dai_id == LPASS_DP_RX)
		drvdata->hdmi_substream[data->dma_ch] = शून्य;
	अन्यथा
		drvdata->substream[data->dma_ch] = शून्य;
	अगर (v->मुक्त_dma_channel)
		v->मुक्त_dma_channel(drvdata, data->dma_ch, dai_id);

	kमुक्त(data);
	वापस 0;
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_hw_params(काष्ठा snd_soc_component *component,
					   काष्ठा snd_pcm_substream *substream,
					   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा lpass_pcm_data *pcm_data = rt->निजी_data;
	काष्ठा lpass_variant *v = drvdata->variant;
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक regval;
	काष्ठा lpaअगर_dmactl *dmactl;
	पूर्णांक id, dir = substream->stream;
	पूर्णांक bitwidth;
	पूर्णांक ret, dma_port = pcm_data->i2s_port + v->dmactl_audअगर_start;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;

	अगर (dir ==  SNDRV_PCM_STREAM_PLAYBACK) अणु
		id = pcm_data->dma_ch;
		अगर (dai_id == LPASS_DP_RX)
			dmactl = drvdata->hdmi_rd_dmactl;
		अन्यथा
			dmactl = drvdata->rd_dmactl;

	पूर्ण अन्यथा अणु
		dmactl = drvdata->wr_dmactl;
		id = pcm_data->dma_ch - v->wrdma_channel_start;
	पूर्ण

	bitwidth = snd_pcm_क्रमmat_width(क्रमmat);
	अगर (bitwidth < 0) अणु
		dev_err(soc_runसमय->dev, "invalid bit width given: %d\n",
				bitwidth);
		वापस bitwidth;
	पूर्ण

	ret = regmap_fields_ग_लिखो(dmactl->bursten, id, LPAIF_DMACTL_BURSTEN_INCR4);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev, "error updating bursten field: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_fields_ग_लिखो(dmactl->fअगरowm, id, LPAIF_DMACTL_FIFOWM_8);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev, "error updating fifowm field: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (dai_id) अणु
	हाल LPASS_DP_RX:
		ret = regmap_fields_ग_लिखो(dmactl->burst8, id,
							LPAIF_DMACTL_BURSTEN_INCR4);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "error updating burst8en field: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = regmap_fields_ग_लिखो(dmactl->burst16, id,
							LPAIF_DMACTL_BURSTEN_INCR4);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "error updating burst16en field: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = regmap_fields_ग_लिखो(dmactl->dynburst, id,
							LPAIF_DMACTL_BURSTEN_INCR4);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "error updating dynbursten field: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल MI2S_PRIMARY:
	हाल MI2S_SECONDARY:
	हाल MI2S_TERTIARY:
	हाल MI2S_QUATERNARY:
	हाल MI2S_QUINARY:
		ret = regmap_fields_ग_लिखो(dmactl->पूर्णांकf, id,
						LPAIF_DMACTL_AUDINTF(dma_port));
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "error updating audio interface field: %d\n",
					ret);
			वापस ret;
		पूर्ण

		अवरोध;
	शेष:
		dev_err(soc_runसमय->dev, "%s: invalid  interface: %d\n", __func__, dai_id);
		अवरोध;
	पूर्ण
	चयन (bitwidth) अणु
	हाल 16:
		चयन (channels) अणु
		हाल 1:
		हाल 2:
			regval = LPAIF_DMACTL_WPSCNT_ONE;
			अवरोध;
		हाल 4:
			regval = LPAIF_DMACTL_WPSCNT_TWO;
			अवरोध;
		हाल 6:
			regval = LPAIF_DMACTL_WPSCNT_THREE;
			अवरोध;
		हाल 8:
			regval = LPAIF_DMACTL_WPSCNT_FOUR;
			अवरोध;
		शेष:
			dev_err(soc_runसमय->dev, "invalid PCM config given: bw=%d, ch=%u\n",
				bitwidth, channels);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 24:
	हाल 32:
		चयन (channels) अणु
		हाल 1:
			regval = LPAIF_DMACTL_WPSCNT_ONE;
			अवरोध;
		हाल 2:
			regval = (dai_id == LPASS_DP_RX ?
			LPAIF_DMACTL_WPSCNT_ONE :
			LPAIF_DMACTL_WPSCNT_TWO);
			अवरोध;
		हाल 4:
			regval = (dai_id == LPASS_DP_RX ?
			LPAIF_DMACTL_WPSCNT_TWO :
			LPAIF_DMACTL_WPSCNT_FOUR);
			अवरोध;
		हाल 6:
			regval = (dai_id == LPASS_DP_RX ?
			LPAIF_DMACTL_WPSCNT_THREE :
			LPAIF_DMACTL_WPSCNT_SIX);
			अवरोध;
		हाल 8:
			regval = (dai_id == LPASS_DP_RX ?
			LPAIF_DMACTL_WPSCNT_FOUR :
			LPAIF_DMACTL_WPSCNT_EIGHT);
			अवरोध;
		शेष:
			dev_err(soc_runसमय->dev, "invalid PCM config given: bw=%d, ch=%u\n",
				bitwidth, channels);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(soc_runसमय->dev, "invalid PCM config given: bw=%d, ch=%u\n",
			bitwidth, channels);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_fields_ग_लिखो(dmactl->wpscnt, id, regval);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev, "error writing to dmactl reg: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_hw_मुक्त(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा lpass_pcm_data *pcm_data = rt->निजी_data;
	काष्ठा lpass_variant *v = drvdata->variant;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;

	अगर (dai_id == LPASS_DP_RX)
		map = drvdata->hdmiअगर_map;
	अन्यथा
		map = drvdata->lpaअगर_map;

	reg = LPAIF_DMACTL_REG(v, pcm_data->dma_ch, substream->stream, dai_id);
	ret = regmap_ग_लिखो(map, reg, 0);
	अगर (ret)
		dev_err(soc_runसमय->dev, "error writing to rdmactl reg: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_prepare(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा lpass_pcm_data *pcm_data = rt->निजी_data;
	काष्ठा lpass_variant *v = drvdata->variant;
	काष्ठा lpaअगर_dmactl *dmactl;
	काष्ठा regmap *map;
	पूर्णांक ret, id, ch, dir = substream->stream;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;


	ch = pcm_data->dma_ch;
	अगर (dir ==  SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (dai_id == LPASS_DP_RX) अणु
			dmactl = drvdata->hdmi_rd_dmactl;
			map = drvdata->hdmiअगर_map;
		पूर्ण अन्यथा अणु
			dmactl = drvdata->rd_dmactl;
			map = drvdata->lpaअगर_map;
		पूर्ण

		id = pcm_data->dma_ch;
	पूर्ण अन्यथा अणु
		dmactl = drvdata->wr_dmactl;
		id = pcm_data->dma_ch - v->wrdma_channel_start;
		map = drvdata->lpaअगर_map;
	पूर्ण

	ret = regmap_ग_लिखो(map, LPAIF_DMABASE_REG(v, ch, dir, dai_id),
				runसमय->dma_addr);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev, "error writing to rdmabase reg: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(map, LPAIF_DMABUFF_REG(v, ch, dir, dai_id),
			(snd_pcm_lib_buffer_bytes(substream) >> 2) - 1);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev, "error writing to rdmabuff reg: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(map, LPAIF_DMAPER_REG(v, ch, dir, dai_id),
			(snd_pcm_lib_period_bytes(substream) >> 2) - 1);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev, "error writing to rdmaper reg: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_fields_ग_लिखो(dmactl->enable, id, LPAIF_DMACTL_ENABLE_ON);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev, "error writing to rdmactl reg: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_trigger(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream,
					 पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा lpass_pcm_data *pcm_data = rt->निजी_data;
	काष्ठा lpass_variant *v = drvdata->variant;
	काष्ठा lpaअगर_dmactl *dmactl;
	काष्ठा regmap *map;
	पूर्णांक ret, ch, id;
	पूर्णांक dir = substream->stream;
	अचिन्हित पूर्णांक reg_irqclr = 0, val_irqclr = 0;
	अचिन्हित पूर्णांक  reg_irqen = 0, val_irqen = 0, val_mask = 0;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;

	ch = pcm_data->dma_ch;
	अगर (dir ==  SNDRV_PCM_STREAM_PLAYBACK) अणु
		id = pcm_data->dma_ch;
		अगर (dai_id == LPASS_DP_RX) अणु
			dmactl = drvdata->hdmi_rd_dmactl;
			map = drvdata->hdmiअगर_map;
		पूर्ण अन्यथा अणु
			dmactl = drvdata->rd_dmactl;
			map = drvdata->lpaअगर_map;
		पूर्ण
	पूर्ण अन्यथा अणु
		dmactl = drvdata->wr_dmactl;
		id = pcm_data->dma_ch - v->wrdma_channel_start;
		map = drvdata->lpaअगर_map;
	पूर्ण

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = regmap_fields_ग_लिखो(dmactl->enable, id,
						 LPAIF_DMACTL_ENABLE_ON);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev,
				"error writing to rdmactl reg: %d\n", ret);
			वापस ret;
		पूर्ण
		चयन (dai_id) अणु
		हाल LPASS_DP_RX:
			ret = regmap_fields_ग_लिखो(dmactl->dyncclk, id,
					 LPAIF_DMACTL_DYNCLK_ON);
			अगर (ret) अणु
				dev_err(soc_runसमय->dev,
					"error writing to rdmactl reg: %d\n", ret);
				वापस ret;
			पूर्ण
			reg_irqclr = LPASS_HDMITX_APP_IRQCLEAR_REG(v);
			val_irqclr = (LPAIF_IRQ_ALL(ch) |
					LPAIF_IRQ_HDMI_REQ_ON_PRELOAD(ch) |
					LPAIF_IRQ_HDMI_METADONE |
					LPAIF_IRQ_HDMI_SDEEP_AUD_DIS(ch));

			reg_irqen = LPASS_HDMITX_APP_IRQEN_REG(v);
			val_mask = (LPAIF_IRQ_ALL(ch) |
					LPAIF_IRQ_HDMI_REQ_ON_PRELOAD(ch) |
					LPAIF_IRQ_HDMI_METADONE |
					LPAIF_IRQ_HDMI_SDEEP_AUD_DIS(ch));
			val_irqen = (LPAIF_IRQ_ALL(ch) |
					LPAIF_IRQ_HDMI_REQ_ON_PRELOAD(ch) |
					LPAIF_IRQ_HDMI_METADONE |
					LPAIF_IRQ_HDMI_SDEEP_AUD_DIS(ch));
			अवरोध;
		हाल MI2S_PRIMARY:
		हाल MI2S_SECONDARY:
		हाल MI2S_TERTIARY:
		हाल MI2S_QUATERNARY:
		हाल MI2S_QUINARY:
			reg_irqclr = LPAIF_IRQCLEAR_REG(v, LPAIF_IRQ_PORT_HOST);
			val_irqclr = LPAIF_IRQ_ALL(ch);


			reg_irqen = LPAIF_IRQEN_REG(v, LPAIF_IRQ_PORT_HOST);
			val_mask = LPAIF_IRQ_ALL(ch);
			val_irqen = LPAIF_IRQ_ALL(ch);
			अवरोध;
		शेष:
			dev_err(soc_runसमय->dev, "%s: invalid %d interface\n", __func__, dai_id);
			वापस -EINVAL;
		पूर्ण

		ret = regmap_ग_लिखो(map, reg_irqclr, val_irqclr);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "error writing to irqclear reg: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = regmap_update_bits(map, reg_irqen, val_mask, val_irqen);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "error writing to irqen reg: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = regmap_fields_ग_लिखो(dmactl->enable, id,
					 LPAIF_DMACTL_ENABLE_OFF);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev,
				"error writing to rdmactl reg: %d\n", ret);
			वापस ret;
		पूर्ण
		चयन (dai_id) अणु
		हाल LPASS_DP_RX:
			ret = regmap_fields_ग_लिखो(dmactl->dyncclk, id,
					 LPAIF_DMACTL_DYNCLK_OFF);
			अगर (ret) अणु
				dev_err(soc_runसमय->dev,
					"error writing to rdmactl reg: %d\n", ret);
				वापस ret;
			पूर्ण
			reg_irqen = LPASS_HDMITX_APP_IRQEN_REG(v);
			val_mask = (LPAIF_IRQ_ALL(ch) |
					LPAIF_IRQ_HDMI_REQ_ON_PRELOAD(ch) |
					LPAIF_IRQ_HDMI_METADONE |
					LPAIF_IRQ_HDMI_SDEEP_AUD_DIS(ch));
			val_irqen = 0;
			अवरोध;
		हाल MI2S_PRIMARY:
		हाल MI2S_SECONDARY:
		हाल MI2S_TERTIARY:
		हाल MI2S_QUATERNARY:
		हाल MI2S_QUINARY:
			reg_irqen = LPAIF_IRQEN_REG(v, LPAIF_IRQ_PORT_HOST);
			val_mask = LPAIF_IRQ_ALL(ch);
			val_irqen = 0;
			अवरोध;
		शेष:
			dev_err(soc_runसमय->dev, "%s: invalid %d interface\n", __func__, dai_id);
			वापस -EINVAL;
		पूर्ण

		ret = regmap_update_bits(map, reg_irqen, val_mask, val_irqen);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev,
				"error writing to irqen reg: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t lpass_platक्रमm_pcmops_poपूर्णांकer(
		काष्ठा snd_soc_component *component,
		काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा lpass_pcm_data *pcm_data = rt->निजी_data;
	काष्ठा lpass_variant *v = drvdata->variant;
	अचिन्हित पूर्णांक base_addr, curr_addr;
	पूर्णांक ret, ch, dir = substream->stream;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;

	अगर (dai_id == LPASS_DP_RX)
		map = drvdata->hdmiअगर_map;
	अन्यथा
		map = drvdata->lpaअगर_map;

	ch = pcm_data->dma_ch;

	ret = regmap_पढ़ो(map,
			LPAIF_DMABASE_REG(v, ch, dir, dai_id), &base_addr);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev,
			"error reading from rdmabase reg: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(map,
			LPAIF_DMACURR_REG(v, ch, dir, dai_id), &curr_addr);
	अगर (ret) अणु
		dev_err(soc_runसमय->dev,
			"error reading from rdmacurr reg: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस bytes_to_frames(substream->runसमय, curr_addr - base_addr);
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_mmap(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_substream *substream,
				      काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	वापस dma_mmap_coherent(component->dev, vma, runसमय->dma_area,
				 runसमय->dma_addr, runसमय->dma_bytes);
पूर्ण

अटल irqवापस_t lpass_dma_पूर्णांकerrupt_handler(
			काष्ठा snd_pcm_substream *substream,
			काष्ठा lpass_data *drvdata,
			पूर्णांक chan, u32 पूर्णांकerrupts)
अणु
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(soc_runसमय, 0);
	काष्ठा lpass_variant *v = drvdata->variant;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक rv;
	अचिन्हित पूर्णांक reg = 0, val = 0;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक dai_id = cpu_dai->driver->id;

	चयन (dai_id) अणु
	हाल LPASS_DP_RX:
		map = drvdata->hdmiअगर_map;
		reg = LPASS_HDMITX_APP_IRQCLEAR_REG(v);
		val = (LPAIF_IRQ_HDMI_REQ_ON_PRELOAD(chan) |
		LPAIF_IRQ_HDMI_METADONE |
		LPAIF_IRQ_HDMI_SDEEP_AUD_DIS(chan));
	अवरोध;
	हाल MI2S_PRIMARY:
	हाल MI2S_SECONDARY:
	हाल MI2S_TERTIARY:
	हाल MI2S_QUATERNARY:
	हाल MI2S_QUINARY:
		map = drvdata->lpaअगर_map;
		reg = LPAIF_IRQCLEAR_REG(v, LPAIF_IRQ_PORT_HOST);
		val = 0;
	अवरोध;
	शेष:
	dev_err(soc_runसमय->dev, "%s: invalid  %d interface\n", __func__, dai_id);
	वापस -EINVAL;
	पूर्ण
	अगर (पूर्णांकerrupts & LPAIF_IRQ_PER(chan)) अणु

		rv = regmap_ग_लिखो(map, reg, LPAIF_IRQ_PER(chan) | val);
		अगर (rv) अणु
			dev_err(soc_runसमय->dev,
				"error writing to irqclear reg: %d\n", rv);
			वापस IRQ_NONE;
		पूर्ण
		snd_pcm_period_elapsed(substream);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकerrupts & LPAIF_IRQ_XRUN(chan)) अणु
		rv = regmap_ग_लिखो(map, reg, LPAIF_IRQ_XRUN(chan) | val);
		अगर (rv) अणु
			dev_err(soc_runसमय->dev,
				"error writing to irqclear reg: %d\n", rv);
			वापस IRQ_NONE;
		पूर्ण
		dev_warn(soc_runसमय->dev, "xrun warning\n");
		snd_pcm_stop_xrun(substream);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकerrupts & LPAIF_IRQ_ERR(chan)) अणु
		rv = regmap_ग_लिखो(map, reg, LPAIF_IRQ_ERR(chan) | val);
		अगर (rv) अणु
			dev_err(soc_runसमय->dev,
				"error writing to irqclear reg: %d\n", rv);
			वापस IRQ_NONE;
		पूर्ण
		dev_err(soc_runसमय->dev, "bus access error\n");
		snd_pcm_stop(substream, SNDRV_PCM_STATE_DISCONNECTED);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकerrupts & val) अणु
		rv = regmap_ग_लिखो(map, reg, val);
		अगर (rv) अणु
			dev_err(soc_runसमय->dev,
			"error writing to irqclear reg: %d\n", rv);
			वापस IRQ_NONE;
		पूर्ण
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t lpass_platक्रमm_lpaअगर_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lpass_data *drvdata = data;
	काष्ठा lpass_variant *v = drvdata->variant;
	अचिन्हित पूर्णांक irqs;
	पूर्णांक rv, chan;

	rv = regmap_पढ़ो(drvdata->lpaअगर_map,
			LPAIF_IRQSTAT_REG(v, LPAIF_IRQ_PORT_HOST), &irqs);
	अगर (rv) अणु
		pr_err("error reading from irqstat reg: %d\n", rv);
		वापस IRQ_NONE;
	पूर्ण

	/* Handle per channel पूर्णांकerrupts */
	क्रम (chan = 0; chan < LPASS_MAX_DMA_CHANNELS; chan++) अणु
		अगर (irqs & LPAIF_IRQ_ALL(chan) && drvdata->substream[chan]) अणु
			rv = lpass_dma_पूर्णांकerrupt_handler(
						drvdata->substream[chan],
						drvdata, chan, irqs);
			अगर (rv != IRQ_HANDLED)
				वापस rv;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lpass_platक्रमm_hdmiअगर_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lpass_data *drvdata = data;
	काष्ठा lpass_variant *v = drvdata->variant;
	अचिन्हित पूर्णांक irqs;
	पूर्णांक rv, chan;

	rv = regmap_पढ़ो(drvdata->hdmiअगर_map,
			LPASS_HDMITX_APP_IRQSTAT_REG(v), &irqs);
	अगर (rv) अणु
		pr_err("error reading from irqstat reg: %d\n", rv);
		वापस IRQ_NONE;
	पूर्ण

	/* Handle per channel पूर्णांकerrupts */
	क्रम (chan = 0; chan < LPASS_MAX_HDMI_DMA_CHANNELS; chan++) अणु
		अगर (irqs & (LPAIF_IRQ_ALL(chan) | LPAIF_IRQ_HDMI_REQ_ON_PRELOAD(chan) |
				LPAIF_IRQ_HDMI_METADONE |
				LPAIF_IRQ_HDMI_SDEEP_AUD_DIS(chan))
			&& drvdata->hdmi_substream[chan]) अणु
			rv = lpass_dma_पूर्णांकerrupt_handler(
						drvdata->hdmi_substream[chan],
						drvdata, chan, irqs);
			अगर (rv != IRQ_HANDLED)
				वापस rv;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcm_new(काष्ठा snd_soc_component *component,
				  काष्ठा snd_soc_pcm_runसमय *soc_runसमय)
अणु
	काष्ठा snd_pcm *pcm = soc_runसमय->pcm;
	काष्ठा snd_pcm_substream *psubstream, *csubstream;
	पूर्णांक ret;
	माप_प्रकार size = lpass_platक्रमm_pcm_hardware.buffer_bytes_max;

	psubstream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	अगर (psubstream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
					component->dev,
					size, &psubstream->dma_buffer);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "Cannot allocate buffer(s)\n");
			वापस ret;
		पूर्ण
	पूर्ण

	csubstream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	अगर (csubstream) अणु
		ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
					component->dev,
					size, &csubstream->dma_buffer);
		अगर (ret) अणु
			dev_err(soc_runसमय->dev, "Cannot allocate buffer(s)\n");
			अगर (psubstream)
				snd_dma_मुक्त_pages(&psubstream->dma_buffer);
			वापस ret;
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lpass_platक्रमm_pcm_मुक्त(काष्ठा snd_soc_component *component,
				    काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक i;

	क्रम_each_pcm_streams(i) अणु
		substream = pcm->streams[i].substream;
		अगर (substream) अणु
			snd_dma_मुक्त_pages(&substream->dma_buffer);
			substream->dma_buffer.area = शून्य;
			substream->dma_buffer.addr = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक dai_id = component->id;

	अगर (dai_id == LPASS_DP_RX)
		map = drvdata->hdmiअगर_map;
	अन्यथा
		map = drvdata->lpaअगर_map;

	regcache_cache_only(map, true);
	regcache_mark_dirty(map);

	वापस 0;
पूर्ण

अटल पूर्णांक lpass_platक्रमm_pcmops_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक dai_id = component->id;

	अगर (dai_id == LPASS_DP_RX)
		map = drvdata->hdmiअगर_map;
	अन्यथा
		map = drvdata->lpaअगर_map;

	regcache_cache_only(map, false);
	वापस regcache_sync(map);
पूर्ण


अटल स्थिर काष्ठा snd_soc_component_driver lpass_component_driver = अणु
	.name		= DRV_NAME,
	.खोलो		= lpass_platक्रमm_pcmops_खोलो,
	.बंद		= lpass_platक्रमm_pcmops_बंद,
	.hw_params	= lpass_platक्रमm_pcmops_hw_params,
	.hw_मुक्त	= lpass_platक्रमm_pcmops_hw_मुक्त,
	.prepare	= lpass_platक्रमm_pcmops_prepare,
	.trigger	= lpass_platक्रमm_pcmops_trigger,
	.poपूर्णांकer	= lpass_platक्रमm_pcmops_poपूर्णांकer,
	.mmap		= lpass_platक्रमm_pcmops_mmap,
	.pcm_स्थिरruct	= lpass_platक्रमm_pcm_new,
	.pcm_deकाष्ठा	= lpass_platक्रमm_pcm_मुक्त,
	.suspend		= lpass_platक्रमm_pcmops_suspend,
	.resume			= lpass_platक्रमm_pcmops_resume,

पूर्ण;

पूर्णांक asoc_qcom_lpass_platक्रमm_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक ret;

	drvdata->lpaअगर_irq = platक्रमm_get_irq_byname(pdev, "lpass-irq-lpaif");
	अगर (drvdata->lpaअगर_irq < 0)
		वापस -ENODEV;

	/* ensure audio hardware is disabled */
	ret = regmap_ग_लिखो(drvdata->lpaअगर_map,
			LPAIF_IRQEN_REG(v, LPAIF_IRQ_PORT_HOST), 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "error writing to irqen reg: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, drvdata->lpaअगर_irq,
			lpass_platक्रमm_lpaअगर_irq, IRQF_TRIGGER_RISING,
			"lpass-irq-lpaif", drvdata);
	अगर (ret) अणु
		dev_err(&pdev->dev, "irq request failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = lpass_platक्रमm_alloc_dmactl_fields(&pdev->dev,
						 drvdata->lpaअगर_map);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"error initializing dmactl fields: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (drvdata->hdmi_port_enable) अणु
		drvdata->hdmiअगर_irq = platक्रमm_get_irq_byname(pdev, "lpass-irq-hdmi");
		अगर (drvdata->hdmiअगर_irq < 0)
			वापस -ENODEV;

		ret = devm_request_irq(&pdev->dev, drvdata->hdmiअगर_irq,
				lpass_platक्रमm_hdmiअगर_irq, 0, "lpass-irq-hdmi", drvdata);
		अगर (ret) अणु
			dev_err(&pdev->dev, "irq hdmi request failed: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = regmap_ग_लिखो(drvdata->hdmiअगर_map,
				LPASS_HDMITX_APP_IRQEN_REG(v), 0);
		अगर (ret) अणु
			dev_err(&pdev->dev, "error writing to hdmi irqen reg: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = lpass_platक्रमm_alloc_hdmidmactl_fields(&pdev->dev,
							 drvdata->hdmiअगर_map);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"error initializing hdmidmactl fields: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&lpass_component_driver, शून्य, 0);
पूर्ण
EXPORT_SYMBOL_GPL(asoc_qcom_lpass_platक्रमm_रेजिस्टर);

MODULE_DESCRIPTION("QTi LPASS Platform Driver");
MODULE_LICENSE("GPL v2");
