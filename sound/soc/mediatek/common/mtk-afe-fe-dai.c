<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtk-afe-fe-dais.c  --  Mediatek afe fe dai चालक
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश "mtk-afe-platform-driver.h"
#समावेश <sound/pcm_params.h>
#समावेश "mtk-afe-fe-dai.h"
#समावेश "mtk-base-afe.h"

#घोषणा AFE_BASE_END_OFFSET 8

अटल पूर्णांक mtk_regmap_update_bits(काष्ठा regmap *map, पूर्णांक reg,
			   अचिन्हित पूर्णांक mask,
			   अचिन्हित पूर्णांक val, पूर्णांक shअगरt)
अणु
	अगर (reg < 0 || WARN_ON_ONCE(shअगरt < 0))
		वापस 0;
	वापस regmap_update_bits(map, reg, mask << shअगरt, val << shअगरt);
पूर्ण

अटल पूर्णांक mtk_regmap_ग_लिखो(काष्ठा regmap *map, पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	अगर (reg < 0)
		वापस 0;
	वापस regmap_ग_लिखो(map, reg, val);
पूर्ण

पूर्णांक mtk_afe_fe_startup(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक memअगर_num = asoc_rtd_to_cpu(rtd, 0)->id;
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[memअगर_num];
	स्थिर काष्ठा snd_pcm_hardware *mtk_afe_hardware = afe->mtk_afe_hardware;
	पूर्णांक ret;

	memअगर->substream = substream;

	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 16);
	/* enable agent */
	mtk_regmap_update_bits(afe->regmap, memअगर->data->agent_disable_reg,
			       1, 0, memअगर->data->agent_disable_shअगरt);

	snd_soc_set_runसमय_hwparams(substream, mtk_afe_hardware);

	/*
	 * Capture cannot use ping-pong buffer since hw_ptr at IRQ may be
	 * smaller than period_size due to AFE's पूर्णांकernal buffer.
	 * This easily leads to overrun when avail_min is period_size.
	 * One more period can hold the possible unपढ़ो buffer.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE) अणु
		पूर्णांक periods_max = mtk_afe_hardware->periods_max;

		ret = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
						   SNDRV_PCM_HW_PARAM_PERIODS,
						   3, periods_max);
		अगर (ret < 0) अणु
			dev_err(afe->dev, "hw_constraint_minmax failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		dev_err(afe->dev, "snd_pcm_hw_constraint_integer failed\n");

	/* dynamic allocate irq to memअगर */
	अगर (memअगर->irq_usage < 0) अणु
		पूर्णांक irq_id = mtk_dynamic_irq_acquire(afe);

		अगर (irq_id != afe->irqs_size) अणु
			/* link */
			memअगर->irq_usage = irq_id;
		पूर्ण अन्यथा अणु
			dev_err(afe->dev, "%s() error: no more asys irq\n",
				__func__);
			ret = -EBUSY;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_fe_startup);

व्योम mtk_afe_fe_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[asoc_rtd_to_cpu(rtd, 0)->id];
	पूर्णांक irq_id;

	irq_id = memअगर->irq_usage;

	mtk_regmap_update_bits(afe->regmap, memअगर->data->agent_disable_reg,
			       1, 1, memअगर->data->agent_disable_shअगरt);

	अगर (!memअगर->स्थिर_irq) अणु
		mtk_dynamic_irq_release(afe, irq_id);
		memअगर->irq_usage = -1;
		memअगर->substream = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_fe_shutकरोwn);

पूर्णांक mtk_afe_fe_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	पूर्णांक id = asoc_rtd_to_cpu(rtd, 0)->id;
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];
	पूर्णांक ret;
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);

	अगर (afe->request_dram_resource)
		afe->request_dram_resource(afe->dev);

	dev_dbg(afe->dev, "%s(), %s, ch %d, rate %d, fmt %d, dma_addr %pad, dma_area %p, dma_bytes 0x%zx\n",
		__func__, memअगर->data->name,
		channels, rate, क्रमmat,
		&substream->runसमय->dma_addr,
		substream->runसमय->dma_area,
		substream->runसमय->dma_bytes);

	स_रखो_io(substream->runसमय->dma_area, 0,
		  substream->runसमय->dma_bytes);

	/* set addr */
	ret = mtk_memअगर_set_addr(afe, id,
				 substream->runसमय->dma_area,
				 substream->runसमय->dma_addr,
				 substream->runसमय->dma_bytes);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), error, id %d, set addr, ret %d\n",
			__func__, id, ret);
		वापस ret;
	पूर्ण

	/* set channel */
	ret = mtk_memअगर_set_channel(afe, id, channels);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), error, id %d, set channel %d, ret %d\n",
			__func__, id, channels, ret);
		वापस ret;
	पूर्ण

	/* set rate */
	ret = mtk_memअगर_set_rate_substream(substream, id, rate);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), error, id %d, set rate %d, ret %d\n",
			__func__, id, rate, ret);
		वापस ret;
	पूर्ण

	/* set क्रमmat */
	ret = mtk_memअगर_set_क्रमmat(afe, id, क्रमmat);
	अगर (ret) अणु
		dev_err(afe->dev, "%s(), error, id %d, set format %d, ret %d\n",
			__func__, id, क्रमmat, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_fe_hw_params);

पूर्णांक mtk_afe_fe_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);

	अगर (afe->release_dram_resource)
		afe->release_dram_resource(afe->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_fe_hw_मुक्त);

पूर्णांक mtk_afe_fe_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय * स्थिर runसमय = substream->runसमय;
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	पूर्णांक id = asoc_rtd_to_cpu(rtd, 0)->id;
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];
	काष्ठा mtk_base_afe_irq *irqs = &afe->irqs[memअगर->irq_usage];
	स्थिर काष्ठा mtk_base_irq_data *irq_data = irqs->irq_data;
	अचिन्हित पूर्णांक counter = runसमय->period_size;
	पूर्णांक fs;
	पूर्णांक ret;

	dev_dbg(afe->dev, "%s %s cmd=%d\n", __func__, memअगर->data->name, cmd);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		ret = mtk_memअगर_set_enable(afe, id);
		अगर (ret) अणु
			dev_err(afe->dev, "%s(), error, id %d, memif enable, ret %d\n",
				__func__, id, ret);
			वापस ret;
		पूर्ण

		/* set irq counter */
		mtk_regmap_update_bits(afe->regmap, irq_data->irq_cnt_reg,
				       irq_data->irq_cnt_maskbit, counter,
				       irq_data->irq_cnt_shअगरt);

		/* set irq fs */
		fs = afe->irq_fs(substream, runसमय->rate);

		अगर (fs < 0)
			वापस -EINVAL;

		mtk_regmap_update_bits(afe->regmap, irq_data->irq_fs_reg,
				       irq_data->irq_fs_maskbit, fs,
				       irq_data->irq_fs_shअगरt);

		/* enable पूर्णांकerrupt */
		mtk_regmap_update_bits(afe->regmap, irq_data->irq_en_reg,
				       1, 1, irq_data->irq_en_shअगरt);

		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		ret = mtk_memअगर_set_disable(afe, id);
		अगर (ret) अणु
			dev_err(afe->dev, "%s(), error, id %d, memif enable, ret %d\n",
				__func__, id, ret);
		पूर्ण

		/* disable पूर्णांकerrupt */
		mtk_regmap_update_bits(afe->regmap, irq_data->irq_en_reg,
				       1, 0, irq_data->irq_en_shअगरt);
		/* and clear pending IRQ */
		mtk_regmap_ग_लिखो(afe->regmap, irq_data->irq_clr_reg,
				 1 << irq_data->irq_clr_shअगरt);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_fe_trigger);

पूर्णांक mtk_afe_fe_prepare(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd  = asoc_substream_to_rtd(substream);
	काष्ठा mtk_base_afe *afe = snd_soc_dai_get_drvdata(dai);
	पूर्णांक id = asoc_rtd_to_cpu(rtd, 0)->id;
	पूर्णांक pbuf_size;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (afe->get_memअगर_pbuf_size) अणु
			pbuf_size = afe->get_memअगर_pbuf_size(substream);
			mtk_memअगर_set_pbuf_size(afe, id, pbuf_size);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_fe_prepare);

स्थिर काष्ठा snd_soc_dai_ops mtk_afe_fe_ops = अणु
	.startup	= mtk_afe_fe_startup,
	.shutकरोwn	= mtk_afe_fe_shutकरोwn,
	.hw_params	= mtk_afe_fe_hw_params,
	.hw_मुक्त	= mtk_afe_fe_hw_मुक्त,
	.prepare	= mtk_afe_fe_prepare,
	.trigger	= mtk_afe_fe_trigger,
पूर्ण;
EXPORT_SYMBOL_GPL(mtk_afe_fe_ops);

अटल DEFINE_MUTEX(irqs_lock);
पूर्णांक mtk_dynamic_irq_acquire(काष्ठा mtk_base_afe *afe)
अणु
	पूर्णांक i;

	mutex_lock(&afe->irq_alloc_lock);
	क्रम (i = 0; i < afe->irqs_size; ++i) अणु
		अगर (afe->irqs[i].irq_occupyed == 0) अणु
			afe->irqs[i].irq_occupyed = 1;
			mutex_unlock(&afe->irq_alloc_lock);
			वापस i;
		पूर्ण
	पूर्ण
	mutex_unlock(&afe->irq_alloc_lock);
	वापस afe->irqs_size;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_dynamic_irq_acquire);

पूर्णांक mtk_dynamic_irq_release(काष्ठा mtk_base_afe *afe, पूर्णांक irq_id)
अणु
	mutex_lock(&afe->irq_alloc_lock);
	अगर (irq_id >= 0 && irq_id < afe->irqs_size) अणु
		afe->irqs[irq_id].irq_occupyed = 0;
		mutex_unlock(&afe->irq_alloc_lock);
		वापस 0;
	पूर्ण
	mutex_unlock(&afe->irq_alloc_lock);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_dynamic_irq_release);

पूर्णांक mtk_afe_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = afe->dev;
	काष्ठा regmap *regmap = afe->regmap;
	पूर्णांक i;

	अगर (pm_runसमय_status_suspended(dev) || afe->suspended)
		वापस 0;

	अगर (!afe->reg_back_up)
		afe->reg_back_up =
			devm_kसुस्मृति(dev, afe->reg_back_up_list_num,
				     माप(अचिन्हित पूर्णांक), GFP_KERNEL);

	क्रम (i = 0; i < afe->reg_back_up_list_num; i++)
		regmap_पढ़ो(regmap, afe->reg_back_up_list[i],
			    &afe->reg_back_up[i]);

	afe->suspended = true;
	afe->runसमय_suspend(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_suspend);

पूर्णांक mtk_afe_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = afe->dev;
	काष्ठा regmap *regmap = afe->regmap;
	पूर्णांक i = 0;

	अगर (pm_runसमय_status_suspended(dev) || !afe->suspended)
		वापस 0;

	afe->runसमय_resume(dev);

	अगर (!afe->reg_back_up)
		dev_dbg(dev, "%s no reg_backup\n", __func__);

	क्रम (i = 0; i < afe->reg_back_up_list_num; i++)
		mtk_regmap_ग_लिखो(regmap, afe->reg_back_up_list[i],
				 afe->reg_back_up[i]);

	afe->suspended = false;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_resume);

पूर्णांक mtk_memअगर_set_enable(काष्ठा mtk_base_afe *afe, पूर्णांक id)
अणु
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];

	अगर (memअगर->data->enable_shअगरt < 0) अणु
		dev_warn(afe->dev, "%s(), error, id %d, enable_shift < 0\n",
			 __func__, id);
		वापस 0;
	पूर्ण
	वापस mtk_regmap_update_bits(afe->regmap, memअगर->data->enable_reg,
				      1, 1, memअगर->data->enable_shअगरt);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_enable);

पूर्णांक mtk_memअगर_set_disable(काष्ठा mtk_base_afe *afe, पूर्णांक id)
अणु
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];

	अगर (memअगर->data->enable_shअगरt < 0) अणु
		dev_warn(afe->dev, "%s(), error, id %d, enable_shift < 0\n",
			 __func__, id);
		वापस 0;
	पूर्ण
	वापस mtk_regmap_update_bits(afe->regmap, memअगर->data->enable_reg,
				      1, 0, memअगर->data->enable_shअगरt);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_disable);

पूर्णांक mtk_memअगर_set_addr(काष्ठा mtk_base_afe *afe, पूर्णांक id,
		       अचिन्हित अक्षर *dma_area,
		       dma_addr_t dma_addr,
		       माप_प्रकार dma_bytes)
अणु
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];
	पूर्णांक msb_at_bit33 = upper_32_bits(dma_addr) ? 1 : 0;
	अचिन्हित पूर्णांक phys_buf_addr = lower_32_bits(dma_addr);
	अचिन्हित पूर्णांक phys_buf_addr_upper_32 = upper_32_bits(dma_addr);

	memअगर->dma_area = dma_area;
	memअगर->dma_addr = dma_addr;
	memअगर->dma_bytes = dma_bytes;

	/* start */
	mtk_regmap_ग_लिखो(afe->regmap, memअगर->data->reg_ofs_base,
			 phys_buf_addr);
	/* end */
	अगर (memअगर->data->reg_ofs_end)
		mtk_regmap_ग_लिखो(afe->regmap,
				 memअगर->data->reg_ofs_end,
				 phys_buf_addr + dma_bytes - 1);
	अन्यथा
		mtk_regmap_ग_लिखो(afe->regmap,
				 memअगर->data->reg_ofs_base +
				 AFE_BASE_END_OFFSET,
				 phys_buf_addr + dma_bytes - 1);

	/* set start, end, upper 32 bits */
	अगर (memअगर->data->reg_ofs_base_msb) अणु
		mtk_regmap_ग_लिखो(afe->regmap, memअगर->data->reg_ofs_base_msb,
				 phys_buf_addr_upper_32);
		mtk_regmap_ग_लिखो(afe->regmap,
				 memअगर->data->reg_ofs_end_msb,
				 phys_buf_addr_upper_32);
	पूर्ण

	/* set MSB to 33-bit */
	अगर (memअगर->data->msb_reg >= 0)
		mtk_regmap_update_bits(afe->regmap, memअगर->data->msb_reg,
				       1, msb_at_bit33, memअगर->data->msb_shअगरt);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_addr);

पूर्णांक mtk_memअगर_set_channel(काष्ठा mtk_base_afe *afe,
			  पूर्णांक id, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];
	अचिन्हित पूर्णांक mono;

	अगर (memअगर->data->mono_shअगरt < 0)
		वापस 0;

	अगर (memअगर->data->quad_ch_mask) अणु
		अचिन्हित पूर्णांक quad_ch = (channel == 4) ? 1 : 0;

		mtk_regmap_update_bits(afe->regmap, memअगर->data->quad_ch_reg,
				       memअगर->data->quad_ch_mask,
				       quad_ch, memअगर->data->quad_ch_shअगरt);
	पूर्ण

	अगर (memअगर->data->mono_invert)
		mono = (channel == 1) ? 0 : 1;
	अन्यथा
		mono = (channel == 1) ? 1 : 0;

	वापस mtk_regmap_update_bits(afe->regmap, memअगर->data->mono_reg,
				      1, mono, memअगर->data->mono_shअगरt);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_channel);

अटल पूर्णांक mtk_memअगर_set_rate_fs(काष्ठा mtk_base_afe *afe,
				 पूर्णांक id, पूर्णांक fs)
अणु
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];

	अगर (memअगर->data->fs_shअगरt >= 0)
		mtk_regmap_update_bits(afe->regmap, memअगर->data->fs_reg,
				       memअगर->data->fs_maskbit,
				       fs, memअगर->data->fs_shअगरt);

	वापस 0;
पूर्ण

पूर्णांक mtk_memअगर_set_rate(काष्ठा mtk_base_afe *afe,
		       पूर्णांक id, अचिन्हित पूर्णांक rate)
अणु
	पूर्णांक fs = 0;

	अगर (!afe->get_dai_fs) अणु
		dev_err(afe->dev, "%s(), error, afe->get_dai_fs == NULL\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	fs = afe->get_dai_fs(afe, id, rate);

	अगर (fs < 0)
		वापस -EINVAL;

	वापस mtk_memअगर_set_rate_fs(afe, id, fs);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_rate);

पूर्णांक mtk_memअगर_set_rate_substream(काष्ठा snd_pcm_substream *substream,
				 पूर्णांक id, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);

	पूर्णांक fs = 0;

	अगर (!afe->memअगर_fs) अणु
		dev_err(afe->dev, "%s(), error, afe->memif_fs == NULL\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	fs = afe->memअगर_fs(substream, rate);

	अगर (fs < 0)
		वापस -EINVAL;

	वापस mtk_memअगर_set_rate_fs(afe, id, fs);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_rate_substream);

पूर्णांक mtk_memअगर_set_क्रमmat(काष्ठा mtk_base_afe *afe,
			 पूर्णांक id, snd_pcm_क्रमmat_t क्रमmat)
अणु
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[id];
	पूर्णांक hd_audio = 0;
	पूर्णांक hd_align = 0;

	/* set hd mode */
	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
	हाल SNDRV_PCM_FORMAT_U16_LE:
		hd_audio = 0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
	हाल SNDRV_PCM_FORMAT_U32_LE:
		अगर (afe->memअगर_32bit_supported) अणु
			hd_audio = 2;
			hd_align = 0;
		पूर्ण अन्यथा अणु
			hd_audio = 1;
			hd_align = 1;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
	हाल SNDRV_PCM_FORMAT_U24_LE:
		hd_audio = 1;
		अवरोध;
	शेष:
		dev_err(afe->dev, "%s() error: unsupported format %d\n",
			__func__, क्रमmat);
		अवरोध;
	पूर्ण

	mtk_regmap_update_bits(afe->regmap, memअगर->data->hd_reg,
			       0x3, hd_audio, memअगर->data->hd_shअगरt);

	mtk_regmap_update_bits(afe->regmap, memअगर->data->hd_align_reg,
			       0x1, hd_align, memअगर->data->hd_align_mshअगरt);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_क्रमmat);

पूर्णांक mtk_memअगर_set_pbuf_size(काष्ठा mtk_base_afe *afe,
			    पूर्णांक id, पूर्णांक pbuf_size)
अणु
	स्थिर काष्ठा mtk_base_memअगर_data *memअगर_data = afe->memअगर[id].data;

	अगर (memअगर_data->pbuf_mask == 0 || memअगर_data->minlen_mask == 0)
		वापस 0;

	mtk_regmap_update_bits(afe->regmap, memअगर_data->pbuf_reg,
			       memअगर_data->pbuf_mask,
			       pbuf_size, memअगर_data->pbuf_shअगरt);

	mtk_regmap_update_bits(afe->regmap, memअगर_data->minlen_reg,
			       memअगर_data->minlen_mask,
			       pbuf_size, memअगर_data->minlen_shअगरt);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_memअगर_set_pbuf_size);

MODULE_DESCRIPTION("Mediatek simple fe dai operator");
MODULE_AUTHOR("Garlic Tseng <garlic.tseng@mediatek.com>");
MODULE_LICENSE("GPL v2");
