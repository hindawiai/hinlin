<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtk-afe-platक्रमm-driver.c  --  Mediatek afe platक्रमm driver
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/soc.h>

#समावेश "mtk-afe-platform-driver.h"
#समावेश "mtk-base-afe.h"

पूर्णांक mtk_afe_combine_sub_dai(काष्ठा mtk_base_afe *afe)
अणु
	काष्ठा mtk_base_afe_dai *dai;
	माप_प्रकार num_dai_drivers = 0, dai_idx = 0;

	/* calcualte total dai driver size */
	list_क्रम_each_entry(dai, &afe->sub_dais, list) अणु
		num_dai_drivers += dai->num_dai_drivers;
	पूर्ण

	dev_info(afe->dev, "%s(), num of dai %zd\n", __func__, num_dai_drivers);

	/* combine sub_dais */
	afe->num_dai_drivers = num_dai_drivers;
	afe->dai_drivers = devm_kसुस्मृति(afe->dev,
					num_dai_drivers,
					माप(काष्ठा snd_soc_dai_driver),
					GFP_KERNEL);
	अगर (!afe->dai_drivers)
		वापस -ENOMEM;

	list_क्रम_each_entry(dai, &afe->sub_dais, list) अणु
		/* dai driver */
		स_नकल(&afe->dai_drivers[dai_idx],
		       dai->dai_drivers,
		       dai->num_dai_drivers *
		       माप(काष्ठा snd_soc_dai_driver));
		dai_idx += dai->num_dai_drivers;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_combine_sub_dai);

पूर्णांक mtk_afe_add_sub_dai_control(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	काष्ठा mtk_base_afe_dai *dai;

	list_क्रम_each_entry(dai, &afe->sub_dais, list) अणु
		अगर (dai->controls)
			snd_soc_add_component_controls(component,
						       dai->controls,
						       dai->num_controls);

		अगर (dai->dapm_widमाला_लो)
			snd_soc_dapm_new_controls(&component->dapm,
						  dai->dapm_widमाला_लो,
						  dai->num_dapm_widमाला_लो);
	पूर्ण
	/* add routes after all widमाला_लो are added */
	list_क्रम_each_entry(dai, &afe->sub_dais, list) अणु
		अगर (dai->dapm_routes)
			snd_soc_dapm_add_routes(&component->dapm,
						dai->dapm_routes,
						dai->num_dapm_routes);
	पूर्ण

	snd_soc_dapm_new_widमाला_लो(component->dapm.card);

	वापस 0;

पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_add_sub_dai_control);

snd_pcm_uframes_t mtk_afe_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);
	काष्ठा mtk_base_afe_memअगर *memअगर = &afe->memअगर[asoc_rtd_to_cpu(rtd, 0)->id];
	स्थिर काष्ठा mtk_base_memअगर_data *memअगर_data = memअगर->data;
	काष्ठा regmap *regmap = afe->regmap;
	काष्ठा device *dev = afe->dev;
	पूर्णांक reg_ofs_base = memअगर_data->reg_ofs_base;
	पूर्णांक reg_ofs_cur = memअगर_data->reg_ofs_cur;
	अचिन्हित पूर्णांक hw_ptr = 0, hw_base = 0;
	पूर्णांक ret, pcm_ptr_bytes;

	ret = regmap_पढ़ो(regmap, reg_ofs_cur, &hw_ptr);
	अगर (ret || hw_ptr == 0) अणु
		dev_err(dev, "%s hw_ptr err\n", __func__);
		pcm_ptr_bytes = 0;
		जाओ POINTER_RETURN_FRAMES;
	पूर्ण

	ret = regmap_पढ़ो(regmap, reg_ofs_base, &hw_base);
	अगर (ret || hw_base == 0) अणु
		dev_err(dev, "%s hw_ptr err\n", __func__);
		pcm_ptr_bytes = 0;
		जाओ POINTER_RETURN_FRAMES;
	पूर्ण

	pcm_ptr_bytes = hw_ptr - hw_base;

POINTER_RETURN_FRAMES:
	वापस bytes_to_frames(substream->runसमय, pcm_ptr_bytes);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_pcm_poपूर्णांकer);

पूर्णांक mtk_afe_pcm_new(काष्ठा snd_soc_component *component,
		    काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	माप_प्रकार size;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(component);

	size = afe->mtk_afe_hardware->buffer_bytes_max;
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       afe->dev, size, size);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_afe_pcm_new);

स्थिर काष्ठा snd_soc_component_driver mtk_afe_pcm_platक्रमm = अणु
	.name		= AFE_PCM_NAME,
	.poपूर्णांकer	= mtk_afe_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= mtk_afe_pcm_new,
पूर्ण;
EXPORT_SYMBOL_GPL(mtk_afe_pcm_platक्रमm);

MODULE_DESCRIPTION("Mediatek simple platform driver");
MODULE_AUTHOR("Garlic Tseng <garlic.tseng@mediatek.com>");
MODULE_LICENSE("GPL v2");

