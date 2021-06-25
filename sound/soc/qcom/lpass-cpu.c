<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 *
 * lpass-cpu.c -- ALSA SoC CPU DAI driver क्रम QTi LPASS
 */

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश "lpass-lpaif-reg.h"
#समावेश "lpass.h"

#घोषणा LPASS_CPU_MAX_MI2S_LINES	4
#घोषणा LPASS_CPU_I2S_SD0_MASK		BIT(0)
#घोषणा LPASS_CPU_I2S_SD1_MASK		BIT(1)
#घोषणा LPASS_CPU_I2S_SD2_MASK		BIT(2)
#घोषणा LPASS_CPU_I2S_SD3_MASK		BIT(3)
#घोषणा LPASS_CPU_I2S_SD0_1_MASK	GENMASK(1, 0)
#घोषणा LPASS_CPU_I2S_SD2_3_MASK	GENMASK(3, 2)
#घोषणा LPASS_CPU_I2S_SD0_1_2_MASK	GENMASK(2, 0)
#घोषणा LPASS_CPU_I2S_SD0_1_2_3_MASK	GENMASK(3, 0)

अटल पूर्णांक lpass_cpu_init_i2sctl_bitfields(काष्ठा device *dev,
			काष्ठा lpaअगर_i2sctl *i2sctl, काष्ठा regmap *map)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;

	i2sctl->loopback = devm_regmap_field_alloc(dev, map, v->loopback);
	i2sctl->spken = devm_regmap_field_alloc(dev, map, v->spken);
	i2sctl->spkmode = devm_regmap_field_alloc(dev, map, v->spkmode);
	i2sctl->spkmono = devm_regmap_field_alloc(dev, map, v->spkmono);
	i2sctl->micen = devm_regmap_field_alloc(dev, map, v->micen);
	i2sctl->micmode = devm_regmap_field_alloc(dev, map, v->micmode);
	i2sctl->micmono = devm_regmap_field_alloc(dev, map, v->micmono);
	i2sctl->wssrc = devm_regmap_field_alloc(dev, map, v->wssrc);
	i2sctl->bitwidth = devm_regmap_field_alloc(dev, map, v->bitwidth);

	अगर (IS_ERR(i2sctl->loopback) || IS_ERR(i2sctl->spken) ||
	    IS_ERR(i2sctl->spkmode) || IS_ERR(i2sctl->spkmono) ||
	    IS_ERR(i2sctl->micen) || IS_ERR(i2sctl->micmode) ||
	    IS_ERR(i2sctl->micmono) || IS_ERR(i2sctl->wssrc) ||
	    IS_ERR(i2sctl->bitwidth))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक lpass_cpu_daiops_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
		अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = clk_set_rate(drvdata->mi2s_osr_clk[dai->driver->id], freq);
	अगर (ret)
		dev_err(dai->dev, "error setting mi2s osrclk to %u: %d\n",
			freq, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक lpass_cpu_daiops_startup(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = clk_prepare_enable(drvdata->mi2s_osr_clk[dai->driver->id]);
	अगर (ret) अणु
		dev_err(dai->dev, "error in enabling mi2s osr clk: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare(drvdata->mi2s_bit_clk[dai->driver->id]);
	अगर (ret) अणु
		dev_err(dai->dev, "error in enabling mi2s bit clk: %d\n", ret);
		clk_disable_unprepare(drvdata->mi2s_osr_clk[dai->driver->id]);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम lpass_cpu_daiops_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	काष्ठा lpaअगर_i2sctl *i2sctl = drvdata->i2sctl;
	अचिन्हित पूर्णांक id = dai->driver->id;

	clk_disable_unprepare(drvdata->mi2s_osr_clk[dai->driver->id]);
	/*
	 * Ensure LRCLK is disabled even in device node validation.
	 * Will not impact अगर disabled in lpass_cpu_daiops_trigger()
	 * suspend.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		regmap_fields_ग_लिखो(i2sctl->spken, id, LPAIF_I2SCTL_SPKEN_DISABLE);
	अन्यथा
		regmap_fields_ग_लिखो(i2sctl->micen, id, LPAIF_I2SCTL_MICEN_DISABLE);

	/*
	 * BCLK may not be enabled अगर lpass_cpu_daiops_prepare is called beक्रमe
	 * lpass_cpu_daiops_shutकरोwn. It's paired with the clk_enable in
	 * lpass_cpu_daiops_prepare.
	 */
	अगर (drvdata->mi2s_was_prepared[dai->driver->id]) अणु
		drvdata->mi2s_was_prepared[dai->driver->id] = false;
		clk_disable(drvdata->mi2s_bit_clk[dai->driver->id]);
	पूर्ण

	clk_unprepare(drvdata->mi2s_bit_clk[dai->driver->id]);
पूर्ण

अटल पूर्णांक lpass_cpu_daiops_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	काष्ठा lpaअगर_i2sctl *i2sctl = drvdata->i2sctl;
	अचिन्हित पूर्णांक id = dai->driver->id;
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक regval;
	पूर्णांक bitwidth, ret;

	bitwidth = snd_pcm_क्रमmat_width(क्रमmat);
	अगर (bitwidth < 0) अणु
		dev_err(dai->dev, "invalid bit width given: %d\n", bitwidth);
		वापस bitwidth;
	पूर्ण

	ret = regmap_fields_ग_लिखो(i2sctl->loopback, id,
				 LPAIF_I2SCTL_LOOPBACK_DISABLE);
	अगर (ret) अणु
		dev_err(dai->dev, "error updating loopback field: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_fields_ग_लिखो(i2sctl->wssrc, id,
				 LPAIF_I2SCTL_WSSRC_INTERNAL);
	अगर (ret) अणु
		dev_err(dai->dev, "error updating wssrc field: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (bitwidth) अणु
	हाल 16:
		regval = LPAIF_I2SCTL_BITWIDTH_16;
		अवरोध;
	हाल 24:
		regval = LPAIF_I2SCTL_BITWIDTH_24;
		अवरोध;
	हाल 32:
		regval = LPAIF_I2SCTL_BITWIDTH_32;
		अवरोध;
	शेष:
		dev_err(dai->dev, "invalid bitwidth given: %d\n", bitwidth);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_fields_ग_लिखो(i2sctl->bitwidth, id, regval);
	अगर (ret) अणु
		dev_err(dai->dev, "error updating bitwidth field: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		mode = drvdata->mi2s_playback_sd_mode[id];
	अन्यथा
		mode = drvdata->mi2s_capture_sd_mode[id];

	अगर (!mode) अणु
		dev_err(dai->dev, "no line is assigned\n");
		वापस -EINVAL;
	पूर्ण

	चयन (channels) अणु
	हाल 1:
	हाल 2:
		चयन (mode) अणु
		हाल LPAIF_I2SCTL_MODE_QUAD01:
		हाल LPAIF_I2SCTL_MODE_6CH:
		हाल LPAIF_I2SCTL_MODE_8CH:
			mode = LPAIF_I2SCTL_MODE_SD0;
			अवरोध;
		हाल LPAIF_I2SCTL_MODE_QUAD23:
			mode = LPAIF_I2SCTL_MODE_SD2;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल 4:
		अगर (mode < LPAIF_I2SCTL_MODE_QUAD01) अणु
			dev_err(dai->dev, "cannot configure 4 channels with mode %d\n",
				mode);
			वापस -EINVAL;
		पूर्ण

		चयन (mode) अणु
		हाल LPAIF_I2SCTL_MODE_6CH:
		हाल LPAIF_I2SCTL_MODE_8CH:
			mode = LPAIF_I2SCTL_MODE_QUAD01;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 6:
		अगर (mode < LPAIF_I2SCTL_MODE_6CH) अणु
			dev_err(dai->dev, "cannot configure 6 channels with mode %d\n",
				mode);
			वापस -EINVAL;
		पूर्ण

		चयन (mode) अणु
		हाल LPAIF_I2SCTL_MODE_8CH:
			mode = LPAIF_I2SCTL_MODE_6CH;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 8:
		अगर (mode < LPAIF_I2SCTL_MODE_8CH) अणु
			dev_err(dai->dev, "cannot configure 8 channels with mode %d\n",
				mode);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dai->dev, "invalid channels given: %u\n", channels);
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = regmap_fields_ग_लिखो(i2sctl->spkmode, id,
					 LPAIF_I2SCTL_SPKMODE(mode));
		अगर (ret) अणु
			dev_err(dai->dev, "error writing to i2sctl spkr mode: %d\n",
				ret);
			वापस ret;
		पूर्ण
		अगर (channels >= 2)
			ret = regmap_fields_ग_लिखो(i2sctl->spkmono, id,
						 LPAIF_I2SCTL_SPKMONO_STEREO);
		अन्यथा
			ret = regmap_fields_ग_लिखो(i2sctl->spkmono, id,
						 LPAIF_I2SCTL_SPKMONO_MONO);
	पूर्ण अन्यथा अणु
		ret = regmap_fields_ग_लिखो(i2sctl->micmode, id,
					 LPAIF_I2SCTL_MICMODE(mode));
		अगर (ret) अणु
			dev_err(dai->dev, "error writing to i2sctl mic mode: %d\n",
				ret);
			वापस ret;
		पूर्ण
		अगर (channels >= 2)
			ret = regmap_fields_ग_लिखो(i2sctl->micmono, id,
						 LPAIF_I2SCTL_MICMONO_STEREO);
		अन्यथा
			ret = regmap_fields_ग_लिखो(i2sctl->micmono, id,
						 LPAIF_I2SCTL_MICMONO_MONO);
	पूर्ण

	अगर (ret) अणु
		dev_err(dai->dev, "error writing to i2sctl channels mode: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = clk_set_rate(drvdata->mi2s_bit_clk[id],
			   rate * bitwidth * 2);
	अगर (ret) अणु
		dev_err(dai->dev, "error setting mi2s bitclk to %u: %d\n",
			rate * bitwidth * 2, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpass_cpu_daiops_trigger(काष्ठा snd_pcm_substream *substream,
		पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	काष्ठा lpaअगर_i2sctl *i2sctl = drvdata->i2sctl;
	अचिन्हित पूर्णांक id = dai->driver->id;
	पूर्णांक ret = -EINVAL;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/*
		 * Ensure lpass BCLK/LRCLK is enabled during
		 * device resume as lpass_cpu_daiops_prepare() is not called
		 * after the device resumes. We करोn't check mi2s_was_prepared beक्रमe
		 * enable/disable BCLK in trigger events because:
		 *  1. These trigger events are paired, so the BCLK
		 *     enable_count is balanced.
		 *  2. the BCLK can be shared (ex: headset and headset mic),
		 *     we need to increase the enable_count so that we करोn't
		 *     turn off the shared BCLK जबतक other devices are using
		 *     it.
		 */
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			ret = regmap_fields_ग_लिखो(i2sctl->spken, id,
						 LPAIF_I2SCTL_SPKEN_ENABLE);
		पूर्ण अन्यथा  अणु
			ret = regmap_fields_ग_लिखो(i2sctl->micen, id,
						 LPAIF_I2SCTL_MICEN_ENABLE);
		पूर्ण
		अगर (ret)
			dev_err(dai->dev, "error writing to i2sctl reg: %d\n",
				ret);

		ret = clk_enable(drvdata->mi2s_bit_clk[id]);
		अगर (ret) अणु
			dev_err(dai->dev, "error in enabling mi2s bit clk: %d\n", ret);
			clk_disable(drvdata->mi2s_osr_clk[id]);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/*
		 * To ensure lpass BCLK/LRCLK is disabled during
		 * device suspend.
		 */
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			ret = regmap_fields_ग_लिखो(i2sctl->spken, id,
						 LPAIF_I2SCTL_SPKEN_DISABLE);
		पूर्ण अन्यथा  अणु
			ret = regmap_fields_ग_लिखो(i2sctl->micen, id,
						 LPAIF_I2SCTL_MICEN_DISABLE);
		पूर्ण
		अगर (ret)
			dev_err(dai->dev, "error writing to i2sctl reg: %d\n",
				ret);

		clk_disable(drvdata->mi2s_bit_clk[dai->driver->id]);

		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lpass_cpu_daiops_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	काष्ठा lpaअगर_i2sctl *i2sctl = drvdata->i2sctl;
	अचिन्हित पूर्णांक id = dai->driver->id;
	पूर्णांक ret;

	/*
	 * Ensure lpass BCLK/LRCLK is enabled bit beक्रमe playback/capture
	 * data flow starts. This allows other codec to have some delay beक्रमe
	 * the data flow.
	 * (ex: to drop start up pop noise beक्रमe capture starts).
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ret = regmap_fields_ग_लिखो(i2sctl->spken, id, LPAIF_I2SCTL_SPKEN_ENABLE);
	अन्यथा
		ret = regmap_fields_ग_लिखो(i2sctl->micen, id, LPAIF_I2SCTL_MICEN_ENABLE);

	अगर (ret) अणु
		dev_err(dai->dev, "error writing to i2sctl reg: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Check mi2s_was_prepared beक्रमe enabling BCLK as lpass_cpu_daiops_prepare can
	 * be called multiple बार. It's paired with the clk_disable in
	 * lpass_cpu_daiops_shutकरोwn.
	 */
	अगर (!drvdata->mi2s_was_prepared[dai->driver->id]) अणु
		ret = clk_enable(drvdata->mi2s_bit_clk[id]);
		अगर (ret) अणु
			dev_err(dai->dev, "error in enabling mi2s bit clk: %d\n", ret);
			वापस ret;
		पूर्ण
		drvdata->mi2s_was_prepared[dai->driver->id] = true;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops asoc_qcom_lpass_cpu_dai_ops = अणु
	.set_sysclk	= lpass_cpu_daiops_set_sysclk,
	.startup	= lpass_cpu_daiops_startup,
	.shutकरोwn	= lpass_cpu_daiops_shutकरोwn,
	.hw_params	= lpass_cpu_daiops_hw_params,
	.trigger	= lpass_cpu_daiops_trigger,
	.prepare	= lpass_cpu_daiops_prepare,
पूर्ण;
EXPORT_SYMBOL_GPL(asoc_qcom_lpass_cpu_dai_ops);

पूर्णांक asoc_qcom_lpass_cpu_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	/* ensure audio hardware is disabled */
	ret = regmap_ग_लिखो(drvdata->lpaअगर_map,
			LPAIF_I2SCTL_REG(drvdata->variant, dai->driver->id), 0);
	अगर (ret)
		dev_err(dai->dev, "error writing to i2sctl reg: %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_qcom_lpass_cpu_dai_probe);

अटल पूर्णांक asoc_qcom_of_xlate_dai_name(काष्ठा snd_soc_component *component,
				   स्थिर काष्ठा of_phandle_args *args,
				   स्थिर अक्षर **dai_name)
अणु
	काष्ठा lpass_data *drvdata = snd_soc_component_get_drvdata(component);
	काष्ठा lpass_variant *variant = drvdata->variant;
	पूर्णांक id = args->args[0];
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i  < variant->num_dai; i++) अणु
		अगर (variant->dai_driver[i].id == id) अणु
			*dai_name = variant->dai_driver[i].name;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver lpass_cpu_comp_driver = अणु
	.name = "lpass-cpu",
	.of_xlate_dai_name = asoc_qcom_of_xlate_dai_name,
पूर्ण;

अटल bool lpass_cpu_regmap_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक i;

	क्रम (i = 0; i < v->i2s_ports; ++i)
		अगर (reg == LPAIF_I2SCTL_REG(v, i))
			वापस true;

	क्रम (i = 0; i < v->irq_ports; ++i) अणु
		अगर (reg == LPAIF_IRQEN_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_IRQCLEAR_REG(v, i))
			वापस true;
	पूर्ण

	क्रम (i = 0; i < v->rdma_channels; ++i) अणु
		अगर (reg == LPAIF_RDMACTL_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_RDMABASE_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_RDMABUFF_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_RDMAPER_REG(v, i))
			वापस true;
	पूर्ण

	क्रम (i = 0; i < v->wrdma_channels; ++i) अणु
		अगर (reg == LPAIF_WRDMACTL_REG(v, i + v->wrdma_channel_start))
			वापस true;
		अगर (reg == LPAIF_WRDMABASE_REG(v, i + v->wrdma_channel_start))
			वापस true;
		अगर (reg == LPAIF_WRDMABUFF_REG(v, i + v->wrdma_channel_start))
			वापस true;
		अगर (reg == LPAIF_WRDMAPER_REG(v, i + v->wrdma_channel_start))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool lpass_cpu_regmap_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक i;

	क्रम (i = 0; i < v->i2s_ports; ++i)
		अगर (reg == LPAIF_I2SCTL_REG(v, i))
			वापस true;

	क्रम (i = 0; i < v->irq_ports; ++i) अणु
		अगर (reg == LPAIF_IRQEN_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_IRQSTAT_REG(v, i))
			वापस true;
	पूर्ण

	क्रम (i = 0; i < v->rdma_channels; ++i) अणु
		अगर (reg == LPAIF_RDMACTL_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_RDMABASE_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_RDMABUFF_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_RDMACURR_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_RDMAPER_REG(v, i))
			वापस true;
	पूर्ण

	क्रम (i = 0; i < v->wrdma_channels; ++i) अणु
		अगर (reg == LPAIF_WRDMACTL_REG(v, i + v->wrdma_channel_start))
			वापस true;
		अगर (reg == LPAIF_WRDMABASE_REG(v, i + v->wrdma_channel_start))
			वापस true;
		अगर (reg == LPAIF_WRDMABUFF_REG(v, i + v->wrdma_channel_start))
			वापस true;
		अगर (reg == LPAIF_WRDMACURR_REG(v, i + v->wrdma_channel_start))
			वापस true;
		अगर (reg == LPAIF_WRDMAPER_REG(v, i + v->wrdma_channel_start))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool lpass_cpu_regmap_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक i;

	क्रम (i = 0; i < v->irq_ports; ++i)
		अगर (reg == LPAIF_IRQSTAT_REG(v, i))
			वापस true;

	क्रम (i = 0; i < v->rdma_channels; ++i)
		अगर (reg == LPAIF_RDMACURR_REG(v, i))
			वापस true;

	क्रम (i = 0; i < v->wrdma_channels; ++i)
		अगर (reg == LPAIF_WRDMACURR_REG(v, i + v->wrdma_channel_start))
			वापस true;

	वापस false;
पूर्ण

अटल काष्ठा regmap_config lpass_cpu_regmap_config = अणु
	.name = "lpass_cpu",
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.ग_लिखोable_reg = lpass_cpu_regmap_ग_लिखोable,
	.पढ़ोable_reg = lpass_cpu_regmap_पढ़ोable,
	.अस्थिर_reg = lpass_cpu_regmap_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक lpass_hdmi_init_bitfields(काष्ठा device *dev, काष्ठा regmap *map)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	अचिन्हित पूर्णांक i;
	काष्ठा lpass_hdmi_tx_ctl *tx_ctl;
	काष्ठा regmap_field *legacy_en;
	काष्ठा lpass_vbit_ctrl *vbit_ctl;
	काष्ठा regmap_field *tx_parity;
	काष्ठा lpass_dp_metadata_ctl *meta_ctl;
	काष्ठा lpass_sstream_ctl *sstream_ctl;
	काष्ठा regmap_field *ch_msb;
	काष्ठा regmap_field *ch_lsb;
	काष्ठा lpass_hdmitx_dmactl *tx_dmactl;
	पूर्णांक rval;

	tx_ctl = devm_kzalloc(dev, माप(*tx_ctl), GFP_KERNEL);
	अगर (!tx_ctl)
		वापस -ENOMEM;

	QCOM_REGMAP_FIELD_ALLOC(dev, map, v->soft_reset, tx_ctl->soft_reset);
	QCOM_REGMAP_FIELD_ALLOC(dev, map, v->क्रमce_reset, tx_ctl->क्रमce_reset);
	drvdata->tx_ctl = tx_ctl;

	QCOM_REGMAP_FIELD_ALLOC(dev, map, v->legacy_en, legacy_en);
	drvdata->hdmitx_legacy_en = legacy_en;

	vbit_ctl = devm_kzalloc(dev, माप(*vbit_ctl), GFP_KERNEL);
	अगर (!vbit_ctl)
		वापस -ENOMEM;

	QCOM_REGMAP_FIELD_ALLOC(dev, map, v->replace_vbit, vbit_ctl->replace_vbit);
	QCOM_REGMAP_FIELD_ALLOC(dev, map, v->vbit_stream, vbit_ctl->vbit_stream);
	drvdata->vbit_ctl = vbit_ctl;


	QCOM_REGMAP_FIELD_ALLOC(dev, map, v->calc_en, tx_parity);
	drvdata->hdmitx_parity_calc_en = tx_parity;

	meta_ctl = devm_kzalloc(dev, माप(*meta_ctl), GFP_KERNEL);
	अगर (!meta_ctl)
		वापस -ENOMEM;

	rval = devm_regmap_field_bulk_alloc(dev, map, &meta_ctl->mute, &v->mute, 7);
	अगर (rval)
		वापस rval;
	drvdata->meta_ctl = meta_ctl;

	sstream_ctl = devm_kzalloc(dev, माप(*sstream_ctl), GFP_KERNEL);
	अगर (!sstream_ctl)
		वापस -ENOMEM;

	rval = devm_regmap_field_bulk_alloc(dev, map, &sstream_ctl->sstream_en, &v->sstream_en, 9);
	अगर (rval)
		वापस rval;

	drvdata->sstream_ctl = sstream_ctl;

	क्रम (i = 0; i < LPASS_MAX_HDMI_DMA_CHANNELS; i++) अणु
		QCOM_REGMAP_FIELD_ALLOC(dev, map, v->msb_bits, ch_msb);
		drvdata->hdmitx_ch_msb[i] = ch_msb;

		QCOM_REGMAP_FIELD_ALLOC(dev, map, v->lsb_bits, ch_lsb);
		drvdata->hdmitx_ch_lsb[i] = ch_lsb;

		tx_dmactl = devm_kzalloc(dev, माप(*tx_dmactl), GFP_KERNEL);
		अगर (!tx_dmactl)
			वापस -ENOMEM;

		QCOM_REGMAP_FIELD_ALLOC(dev, map, v->use_hw_chs, tx_dmactl->use_hw_chs);
		QCOM_REGMAP_FIELD_ALLOC(dev, map, v->use_hw_usr, tx_dmactl->use_hw_usr);
		QCOM_REGMAP_FIELD_ALLOC(dev, map, v->hw_chs_sel, tx_dmactl->hw_chs_sel);
		QCOM_REGMAP_FIELD_ALLOC(dev, map, v->hw_usr_sel, tx_dmactl->hw_usr_sel);
		drvdata->hdmi_tx_dmactl[i] = tx_dmactl;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool lpass_hdmi_regmap_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक i;

	अगर (reg == LPASS_HDMI_TX_CTL_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_LEGACY_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_VBIT_CTL_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_PARITY_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_DP_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_SSTREAM_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMITX_APP_IRQEN_REG(v))
		वापस true;
	अगर (reg == LPASS_HDMITX_APP_IRQCLEAR_REG(v))
		वापस true;

	क्रम (i = 0; i < v->hdmi_rdma_channels; i++) अणु
		अगर (reg == LPASS_HDMI_TX_CH_LSB_ADDR(v, i))
			वापस true;
		अगर (reg == LPASS_HDMI_TX_CH_MSB_ADDR(v, i))
			वापस true;
		अगर (reg == LPASS_HDMI_TX_DMA_ADDR(v, i))
			वापस true;
	पूर्ण

	क्रम (i = 0; i < v->hdmi_rdma_channels; ++i) अणु
		अगर (reg == LPAIF_HDMI_RDMACTL_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_HDMI_RDMABASE_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_HDMI_RDMABUFF_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_HDMI_RDMAPER_REG(v, i))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool lpass_hdmi_regmap_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक i;

	अगर (reg == LPASS_HDMI_TX_CTL_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_LEGACY_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_VBIT_CTL_ADDR(v))
		वापस true;

	क्रम (i = 0; i < v->hdmi_rdma_channels; i++) अणु
		अगर (reg == LPASS_HDMI_TX_CH_LSB_ADDR(v, i))
			वापस true;
		अगर (reg == LPASS_HDMI_TX_CH_MSB_ADDR(v, i))
			वापस true;
		अगर (reg == LPASS_HDMI_TX_DMA_ADDR(v, i))
			वापस true;
	पूर्ण

	अगर (reg == LPASS_HDMI_TX_PARITY_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_DP_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_SSTREAM_ADDR(v))
		वापस true;
	अगर (reg == LPASS_HDMITX_APP_IRQEN_REG(v))
		वापस true;
	अगर (reg == LPASS_HDMITX_APP_IRQSTAT_REG(v))
		वापस true;

	क्रम (i = 0; i < v->hdmi_rdma_channels; ++i) अणु
		अगर (reg == LPAIF_HDMI_RDMACTL_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_HDMI_RDMABASE_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_HDMI_RDMABUFF_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_HDMI_RDMAPER_REG(v, i))
			वापस true;
		अगर (reg == LPAIF_HDMI_RDMACURR_REG(v, i))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool lpass_hdmi_regmap_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा lpass_data *drvdata = dev_get_drvdata(dev);
	काष्ठा lpass_variant *v = drvdata->variant;
	पूर्णांक i;

	अगर (reg == LPASS_HDMITX_APP_IRQSTAT_REG(v))
		वापस true;
	अगर (reg == LPASS_HDMI_TX_LEGACY_ADDR(v))
		वापस true;

	क्रम (i = 0; i < v->hdmi_rdma_channels; ++i) अणु
		अगर (reg == LPAIF_HDMI_RDMACURR_REG(v, i))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा regmap_config lpass_hdmi_regmap_config = अणु
	.name = "lpass_hdmi",
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.ग_लिखोable_reg = lpass_hdmi_regmap_ग_लिखोable,
	.पढ़ोable_reg = lpass_hdmi_regmap_पढ़ोable,
	.अस्थिर_reg = lpass_hdmi_regmap_अस्थिर,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल अचिन्हित पूर्णांक of_lpass_cpu_parse_sd_lines(काष्ठा device *dev,
						काष्ठा device_node *node,
						स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक lines[LPASS_CPU_MAX_MI2S_LINES];
	अचिन्हित पूर्णांक sd_line_mask = 0;
	पूर्णांक num_lines, i;

	num_lines = of_property_पढ़ो_variable_u32_array(node, name, lines, 0,
							LPASS_CPU_MAX_MI2S_LINES);
	अगर (num_lines < 0)
		वापस LPAIF_I2SCTL_MODE_NONE;

	क्रम (i = 0; i < num_lines; i++)
		sd_line_mask |= BIT(lines[i]);

	चयन (sd_line_mask) अणु
	हाल LPASS_CPU_I2S_SD0_MASK:
		वापस LPAIF_I2SCTL_MODE_SD0;
	हाल LPASS_CPU_I2S_SD1_MASK:
		वापस LPAIF_I2SCTL_MODE_SD1;
	हाल LPASS_CPU_I2S_SD2_MASK:
		वापस LPAIF_I2SCTL_MODE_SD2;
	हाल LPASS_CPU_I2S_SD3_MASK:
		वापस LPAIF_I2SCTL_MODE_SD3;
	हाल LPASS_CPU_I2S_SD0_1_MASK:
		वापस LPAIF_I2SCTL_MODE_QUAD01;
	हाल LPASS_CPU_I2S_SD2_3_MASK:
		वापस LPAIF_I2SCTL_MODE_QUAD23;
	हाल LPASS_CPU_I2S_SD0_1_2_MASK:
		वापस LPAIF_I2SCTL_MODE_6CH;
	हाल LPASS_CPU_I2S_SD0_1_2_3_MASK:
		वापस LPAIF_I2SCTL_MODE_8CH;
	शेष:
		dev_err(dev, "Unsupported SD line mask: %#x\n", sd_line_mask);
		वापस LPAIF_I2SCTL_MODE_NONE;
	पूर्ण
पूर्ण

अटल व्योम of_lpass_cpu_parse_dai_data(काष्ठा device *dev,
					काष्ठा lpass_data *data)
अणु
	काष्ठा device_node *node;
	पूर्णांक ret, id;

	/* Allow all channels by शेष क्रम backwards compatibility */
	क्रम (id = 0; id < data->variant->num_dai; id++) अणु
		data->mi2s_playback_sd_mode[id] = LPAIF_I2SCTL_MODE_8CH;
		data->mi2s_capture_sd_mode[id] = LPAIF_I2SCTL_MODE_8CH;
	पूर्ण

	क्रम_each_child_of_node(dev->of_node, node) अणु
		ret = of_property_पढ़ो_u32(node, "reg", &id);
		अगर (ret || id < 0) अणु
			dev_err(dev, "valid dai id not found: %d\n", ret);
			जारी;
		पूर्ण
		अगर (id == LPASS_DP_RX) अणु
			data->hdmi_port_enable = 1;
		पूर्ण अन्यथा अणु
			data->mi2s_playback_sd_mode[id] =
				of_lpass_cpu_parse_sd_lines(dev, node,
							    "qcom,playback-sd-lines");
			data->mi2s_capture_sd_mode[id] =
				of_lpass_cpu_parse_sd_lines(dev, node,
						    "qcom,capture-sd-lines");
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक asoc_qcom_lpass_cpu_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata;
	काष्ठा device_node *dsp_of_node;
	काष्ठा resource *res;
	काष्ठा lpass_variant *variant;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret, i, dai_id;

	dsp_of_node = of_parse_phandle(pdev->dev.of_node, "qcom,adsp", 0);
	अगर (dsp_of_node) अणु
		dev_err(dev, "DSP exists and holds audio resources\n");
		वापस -EBUSY;
	पूर्ण

	drvdata = devm_kzalloc(dev, माप(काष्ठा lpass_data), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, drvdata);

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data)
		वापस -EINVAL;

	drvdata->variant = (काष्ठा lpass_variant *)match->data;
	variant = drvdata->variant;

	of_lpass_cpu_parse_dai_data(dev, drvdata);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "lpass-lpaif");

	drvdata->lpaअगर = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(drvdata->lpaअगर))
		वापस PTR_ERR(drvdata->lpaअगर);

	lpass_cpu_regmap_config.max_रेजिस्टर = LPAIF_WRDMAPER_REG(variant,
						variant->wrdma_channels +
						variant->wrdma_channel_start);

	drvdata->lpaअगर_map = devm_regmap_init_mmio(dev, drvdata->lpaअगर,
			&lpass_cpu_regmap_config);
	अगर (IS_ERR(drvdata->lpaअगर_map)) अणु
		dev_err(dev, "error initializing regmap: %ld\n",
			PTR_ERR(drvdata->lpaअगर_map));
		वापस PTR_ERR(drvdata->lpaअगर_map);
	पूर्ण

	अगर (drvdata->hdmi_port_enable) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "lpass-hdmiif");

		drvdata->hdmiअगर = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(drvdata->hdmiअगर))
			वापस PTR_ERR(drvdata->hdmiअगर);

		lpass_hdmi_regmap_config.max_रेजिस्टर = LPAIF_HDMI_RDMAPER_REG(variant,
					variant->hdmi_rdma_channels - 1);
		drvdata->hdmiअगर_map = devm_regmap_init_mmio(dev, drvdata->hdmiअगर,
					&lpass_hdmi_regmap_config);
		अगर (IS_ERR(drvdata->hdmiअगर_map)) अणु
			dev_err(dev, "error initializing regmap: %ld\n",
			PTR_ERR(drvdata->hdmiअगर_map));
			वापस PTR_ERR(drvdata->hdmiअगर_map);
		पूर्ण
	पूर्ण

	अगर (variant->init) अणु
		ret = variant->init(pdev);
		अगर (ret) अणु
			dev_err(dev, "error initializing variant: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < variant->num_dai; i++) अणु
		dai_id = variant->dai_driver[i].id;
		अगर (dai_id == LPASS_DP_RX)
			जारी;

		drvdata->mi2s_osr_clk[dai_id] = devm_clk_get_optional(dev,
					     variant->dai_osr_clk_names[i]);
		drvdata->mi2s_bit_clk[dai_id] = devm_clk_get(dev,
						variant->dai_bit_clk_names[i]);
		अगर (IS_ERR(drvdata->mi2s_bit_clk[dai_id])) अणु
			dev_err(dev,
				"error getting %s: %ld\n",
				variant->dai_bit_clk_names[i],
				PTR_ERR(drvdata->mi2s_bit_clk[dai_id]));
			वापस PTR_ERR(drvdata->mi2s_bit_clk[dai_id]);
		पूर्ण
	पूर्ण

	/* Allocation क्रम i2sctl regmap fields */
	drvdata->i2sctl = devm_kzalloc(&pdev->dev, माप(काष्ठा lpaअगर_i2sctl),
					GFP_KERNEL);

	/* Initialize bitfields क्रम dai I2SCTL रेजिस्टर */
	ret = lpass_cpu_init_i2sctl_bitfields(dev, drvdata->i2sctl,
						drvdata->lpaअगर_map);
	अगर (ret) अणु
		dev_err(dev, "error init i2sctl field: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (drvdata->hdmi_port_enable) अणु
		ret = lpass_hdmi_init_bitfields(dev, drvdata->hdmiअगर_map);
		अगर (ret) अणु
			dev_err(dev, "%s error  hdmi init failed\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण
	ret = devm_snd_soc_रेजिस्टर_component(dev,
					      &lpass_cpu_comp_driver,
					      variant->dai_driver,
					      variant->num_dai);
	अगर (ret) अणु
		dev_err(dev, "error registering cpu driver: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = asoc_qcom_lpass_platक्रमm_रेजिस्टर(pdev);
	अगर (ret) अणु
		dev_err(dev, "error registering platform driver: %d\n", ret);
		जाओ err;
	पूर्ण

err:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_qcom_lpass_cpu_platक्रमm_probe);

पूर्णांक asoc_qcom_lpass_cpu_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);

	अगर (drvdata->variant->निकास)
		drvdata->variant->निकास(pdev);


	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(asoc_qcom_lpass_cpu_platक्रमm_हटाओ);

व्योम asoc_qcom_lpass_cpu_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpass_data *drvdata = platक्रमm_get_drvdata(pdev);

	अगर (drvdata->variant->निकास)
		drvdata->variant->निकास(pdev);

पूर्ण
EXPORT_SYMBOL_GPL(asoc_qcom_lpass_cpu_platक्रमm_shutकरोwn);

MODULE_DESCRIPTION("QTi LPASS CPU Driver");
MODULE_LICENSE("GPL v2");
