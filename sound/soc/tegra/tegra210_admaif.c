<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// tegra210_admaअगर.c - Tegra ADMAIF driver
//
// Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "tegra210_admaif.h"
#समावेश "tegra_cif.h"
#समावेश "tegra_pcm.h"

#घोषणा CH_REG(offset, reg, id)						       \
	((offset) + (reg) + (TEGRA_ADMAIF_CHANNEL_REG_STRIDE * (id)))

#घोषणा CH_TX_REG(reg, id) CH_REG(admaअगर->soc_data->tx_base, reg, id)

#घोषणा CH_RX_REG(reg, id) CH_REG(admaअगर->soc_data->rx_base, reg, id)

#घोषणा REG_DEFAULTS(id, rx_ctrl, tx_ctrl, tx_base, rx_base)		       \
	अणु CH_REG(rx_base, TEGRA_ADMAIF_RX_INT_MASK, id), 0x00000001 पूर्ण,	       \
	अणु CH_REG(rx_base, TEGRA_ADMAIF_CH_ACIF_RX_CTRL, id), 0x00007700 पूर्ण,     \
	अणु CH_REG(rx_base, TEGRA_ADMAIF_RX_FIFO_CTRL, id), rx_ctrl पूर्ण,	       \
	अणु CH_REG(tx_base, TEGRA_ADMAIF_TX_INT_MASK, id), 0x00000001 पूर्ण,	       \
	अणु CH_REG(tx_base, TEGRA_ADMAIF_CH_ACIF_TX_CTRL, id), 0x00007700 पूर्ण,     \
	अणु CH_REG(tx_base, TEGRA_ADMAIF_TX_FIFO_CTRL, id), tx_ctrl पूर्ण

#घोषणा ADMAIF_REG_DEFAULTS(id, chip)					       \
	REG_DEFAULTS((id) - 1,						       \
		chip ## _ADMAIF_RX ## id ## _FIFO_CTRL_REG_DEFAULT,	       \
		chip ## _ADMAIF_TX ## id ## _FIFO_CTRL_REG_DEFAULT,	       \
		chip ## _ADMAIF_TX_BASE,				       \
		chip ## _ADMAIF_RX_BASE)

अटल स्थिर काष्ठा reg_शेष tegra186_admaअगर_reg_शेषs[] = अणु
	अणु(TEGRA_ADMAIF_GLOBAL_CG_0 + TEGRA186_ADMAIF_GLOBAL_BASE), 0x00000003पूर्ण,
	ADMAIF_REG_DEFAULTS(1, TEGRA186),
	ADMAIF_REG_DEFAULTS(2, TEGRA186),
	ADMAIF_REG_DEFAULTS(3, TEGRA186),
	ADMAIF_REG_DEFAULTS(4, TEGRA186),
	ADMAIF_REG_DEFAULTS(5, TEGRA186),
	ADMAIF_REG_DEFAULTS(6, TEGRA186),
	ADMAIF_REG_DEFAULTS(7, TEGRA186),
	ADMAIF_REG_DEFAULTS(8, TEGRA186),
	ADMAIF_REG_DEFAULTS(9, TEGRA186),
	ADMAIF_REG_DEFAULTS(10, TEGRA186),
	ADMAIF_REG_DEFAULTS(11, TEGRA186),
	ADMAIF_REG_DEFAULTS(12, TEGRA186),
	ADMAIF_REG_DEFAULTS(13, TEGRA186),
	ADMAIF_REG_DEFAULTS(14, TEGRA186),
	ADMAIF_REG_DEFAULTS(15, TEGRA186),
	ADMAIF_REG_DEFAULTS(16, TEGRA186),
	ADMAIF_REG_DEFAULTS(17, TEGRA186),
	ADMAIF_REG_DEFAULTS(18, TEGRA186),
	ADMAIF_REG_DEFAULTS(19, TEGRA186),
	ADMAIF_REG_DEFAULTS(20, TEGRA186)
पूर्ण;

अटल स्थिर काष्ठा reg_शेष tegra210_admaअगर_reg_शेषs[] = अणु
	अणु(TEGRA_ADMAIF_GLOBAL_CG_0 + TEGRA210_ADMAIF_GLOBAL_BASE), 0x00000003पूर्ण,
	ADMAIF_REG_DEFAULTS(1, TEGRA210),
	ADMAIF_REG_DEFAULTS(2, TEGRA210),
	ADMAIF_REG_DEFAULTS(3, TEGRA210),
	ADMAIF_REG_DEFAULTS(4, TEGRA210),
	ADMAIF_REG_DEFAULTS(5, TEGRA210),
	ADMAIF_REG_DEFAULTS(6, TEGRA210),
	ADMAIF_REG_DEFAULTS(7, TEGRA210),
	ADMAIF_REG_DEFAULTS(8, TEGRA210),
	ADMAIF_REG_DEFAULTS(9, TEGRA210),
	ADMAIF_REG_DEFAULTS(10, TEGRA210)
पूर्ण;

अटल bool tegra_admaअगर_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा tegra_admaअगर *admaअगर = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ch_stride = TEGRA_ADMAIF_CHANNEL_REG_STRIDE;
	अचिन्हित पूर्णांक num_ch = admaअगर->soc_data->num_ch;
	अचिन्हित पूर्णांक rx_base = admaअगर->soc_data->rx_base;
	अचिन्हित पूर्णांक tx_base = admaअगर->soc_data->tx_base;
	अचिन्हित पूर्णांक global_base = admaअगर->soc_data->global_base;
	अचिन्हित पूर्णांक reg_max = admaअगर->soc_data->regmap_conf->max_रेजिस्टर;
	अचिन्हित पूर्णांक rx_max = rx_base + (num_ch * ch_stride);
	अचिन्हित पूर्णांक tx_max = tx_base + (num_ch * ch_stride);

	अगर ((reg >= rx_base) && (reg < rx_max)) अणु
		reg = (reg - rx_base) % ch_stride;
		अगर ((reg == TEGRA_ADMAIF_RX_ENABLE) ||
		    (reg == TEGRA_ADMAIF_RX_FIFO_CTRL) ||
		    (reg == TEGRA_ADMAIF_RX_SOFT_RESET) ||
		    (reg == TEGRA_ADMAIF_CH_ACIF_RX_CTRL))
			वापस true;
	पूर्ण अन्यथा अगर ((reg >= tx_base) && (reg < tx_max)) अणु
		reg = (reg - tx_base) % ch_stride;
		अगर ((reg == TEGRA_ADMAIF_TX_ENABLE) ||
		    (reg == TEGRA_ADMAIF_TX_FIFO_CTRL) ||
		    (reg == TEGRA_ADMAIF_TX_SOFT_RESET) ||
		    (reg == TEGRA_ADMAIF_CH_ACIF_TX_CTRL))
			वापस true;
	पूर्ण अन्यथा अगर ((reg >= global_base) && (reg < reg_max)) अणु
		अगर (reg == (global_base + TEGRA_ADMAIF_GLOBAL_ENABLE))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tegra_admaअगर_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा tegra_admaअगर *admaअगर = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ch_stride = TEGRA_ADMAIF_CHANNEL_REG_STRIDE;
	अचिन्हित पूर्णांक num_ch = admaअगर->soc_data->num_ch;
	अचिन्हित पूर्णांक rx_base = admaअगर->soc_data->rx_base;
	अचिन्हित पूर्णांक tx_base = admaअगर->soc_data->tx_base;
	अचिन्हित पूर्णांक global_base = admaअगर->soc_data->global_base;
	अचिन्हित पूर्णांक reg_max = admaअगर->soc_data->regmap_conf->max_रेजिस्टर;
	अचिन्हित पूर्णांक rx_max = rx_base + (num_ch * ch_stride);
	अचिन्हित पूर्णांक tx_max = tx_base + (num_ch * ch_stride);

	अगर ((reg >= rx_base) && (reg < rx_max)) अणु
		reg = (reg - rx_base) % ch_stride;
		अगर ((reg == TEGRA_ADMAIF_RX_ENABLE) ||
		    (reg == TEGRA_ADMAIF_RX_STATUS) ||
		    (reg == TEGRA_ADMAIF_RX_INT_STATUS) ||
		    (reg == TEGRA_ADMAIF_RX_FIFO_CTRL) ||
		    (reg == TEGRA_ADMAIF_RX_SOFT_RESET) ||
		    (reg == TEGRA_ADMAIF_CH_ACIF_RX_CTRL))
			वापस true;
	पूर्ण अन्यथा अगर ((reg >= tx_base) && (reg < tx_max)) अणु
		reg = (reg - tx_base) % ch_stride;
		अगर ((reg == TEGRA_ADMAIF_TX_ENABLE) ||
		    (reg == TEGRA_ADMAIF_TX_STATUS) ||
		    (reg == TEGRA_ADMAIF_TX_INT_STATUS) ||
		    (reg == TEGRA_ADMAIF_TX_FIFO_CTRL) ||
		    (reg == TEGRA_ADMAIF_TX_SOFT_RESET) ||
		    (reg == TEGRA_ADMAIF_CH_ACIF_TX_CTRL))
			वापस true;
	पूर्ण अन्यथा अगर ((reg >= global_base) && (reg < reg_max)) अणु
		अगर ((reg == (global_base + TEGRA_ADMAIF_GLOBAL_ENABLE)) ||
		    (reg == (global_base + TEGRA_ADMAIF_GLOBAL_CG_0)) ||
		    (reg == (global_base + TEGRA_ADMAIF_GLOBAL_STATUS)) ||
		    (reg == (global_base +
				TEGRA_ADMAIF_GLOBAL_RX_ENABLE_STATUS)) ||
		    (reg == (global_base +
				TEGRA_ADMAIF_GLOBAL_TX_ENABLE_STATUS)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tegra_admaअगर_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा tegra_admaअगर *admaअगर = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ch_stride = TEGRA_ADMAIF_CHANNEL_REG_STRIDE;
	अचिन्हित पूर्णांक num_ch = admaअगर->soc_data->num_ch;
	अचिन्हित पूर्णांक rx_base = admaअगर->soc_data->rx_base;
	अचिन्हित पूर्णांक tx_base = admaअगर->soc_data->tx_base;
	अचिन्हित पूर्णांक global_base = admaअगर->soc_data->global_base;
	अचिन्हित पूर्णांक reg_max = admaअगर->soc_data->regmap_conf->max_रेजिस्टर;
	अचिन्हित पूर्णांक rx_max = rx_base + (num_ch * ch_stride);
	अचिन्हित पूर्णांक tx_max = tx_base + (num_ch * ch_stride);

	अगर ((reg >= rx_base) && (reg < rx_max)) अणु
		reg = (reg - rx_base) % ch_stride;
		अगर ((reg == TEGRA_ADMAIF_RX_ENABLE) ||
		    (reg == TEGRA_ADMAIF_RX_STATUS) ||
		    (reg == TEGRA_ADMAIF_RX_INT_STATUS) ||
		    (reg == TEGRA_ADMAIF_RX_SOFT_RESET))
			वापस true;
	पूर्ण अन्यथा अगर ((reg >= tx_base) && (reg < tx_max)) अणु
		reg = (reg - tx_base) % ch_stride;
		अगर ((reg == TEGRA_ADMAIF_TX_ENABLE) ||
		    (reg == TEGRA_ADMAIF_TX_STATUS) ||
		    (reg == TEGRA_ADMAIF_TX_INT_STATUS) ||
		    (reg == TEGRA_ADMAIF_TX_SOFT_RESET))
			वापस true;
	पूर्ण अन्यथा अगर ((reg >= global_base) && (reg < reg_max)) अणु
		अगर ((reg == (global_base + TEGRA_ADMAIF_GLOBAL_STATUS)) ||
		    (reg == (global_base +
				TEGRA_ADMAIF_GLOBAL_RX_ENABLE_STATUS)) ||
		    (reg == (global_base +
				TEGRA_ADMAIF_GLOBAL_TX_ENABLE_STATUS)))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra210_admaअगर_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= TEGRA210_ADMAIF_LAST_REG,
	.ग_लिखोable_reg		= tegra_admaअगर_wr_reg,
	.पढ़ोable_reg		= tegra_admaअगर_rd_reg,
	.अस्थिर_reg		= tegra_admaअगर_अस्थिर_reg,
	.reg_शेषs		= tegra210_admaअगर_reg_शेषs,
	.num_reg_शेषs	= TEGRA210_ADMAIF_CHANNEL_COUNT * 6 + 1,
	.cache_type		= REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tegra186_admaअगर_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= TEGRA186_ADMAIF_LAST_REG,
	.ग_लिखोable_reg		= tegra_admaअगर_wr_reg,
	.पढ़ोable_reg		= tegra_admaअगर_rd_reg,
	.अस्थिर_reg		= tegra_admaअगर_अस्थिर_reg,
	.reg_शेषs		= tegra186_admaअगर_reg_शेषs,
	.num_reg_शेषs	= TEGRA186_ADMAIF_CHANNEL_COUNT * 6 + 1,
	.cache_type		= REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक __maybe_unused tegra_admaअगर_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_admaअगर *admaअगर = dev_get_drvdata(dev);

	regcache_cache_only(admaअगर->regmap, true);
	regcache_mark_dirty(admaअगर->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_admaअगर_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_admaअगर *admaअगर = dev_get_drvdata(dev);

	regcache_cache_only(admaअगर->regmap, false);
	regcache_sync(admaअगर->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_set_pack_mode(काष्ठा regmap *map, अचिन्हित पूर्णांक reg,
				      पूर्णांक valid_bit)
अणु
	चयन (valid_bit) अणु
	हाल DATA_8BIT:
		regmap_update_bits(map, reg, PACK8_EN_MASK, PACK8_EN);
		regmap_update_bits(map, reg, PACK16_EN_MASK, 0);
		अवरोध;
	हाल DATA_16BIT:
		regmap_update_bits(map, reg, PACK16_EN_MASK, PACK16_EN);
		regmap_update_bits(map, reg, PACK8_EN_MASK, 0);
		अवरोध;
	हाल DATA_32BIT:
		regmap_update_bits(map, reg, PACK16_EN_MASK, 0);
		regmap_update_bits(map, reg, PACK8_EN_MASK, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा tegra_admaअगर *admaअगर = snd_soc_dai_get_drvdata(dai);
	काष्ठा tegra_cअगर_conf cअगर_conf;
	अचिन्हित पूर्णांक reg, path;
	पूर्णांक valid_bit, channels;

	स_रखो(&cअगर_conf, 0, माप(काष्ठा tegra_cअगर_conf));

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_8;
		cअगर_conf.client_bits = TEGRA_ACIF_BITS_8;
		valid_bit = DATA_8BIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_16;
		cअगर_conf.client_bits = TEGRA_ACIF_BITS_16;
		valid_bit = DATA_16BIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_32;
		cअगर_conf.client_bits = TEGRA_ACIF_BITS_32;
		valid_bit  = DATA_32BIT;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported format!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	channels = params_channels(params);
	cअगर_conf.client_ch = channels;
	cअगर_conf.audio_ch = channels;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		path = ADMAIF_TX_PATH;
		reg = CH_TX_REG(TEGRA_ADMAIF_CH_ACIF_TX_CTRL, dai->id);
	पूर्ण अन्यथा अणु
		path = ADMAIF_RX_PATH;
		reg = CH_RX_REG(TEGRA_ADMAIF_CH_ACIF_RX_CTRL, dai->id);
	पूर्ण

	cअगर_conf.mono_conv = admaअगर->mono_to_stereo[path][dai->id];
	cअगर_conf.stereo_conv = admaअगर->stereo_to_mono[path][dai->id];

	tegra_admaअगर_set_pack_mode(admaअगर->regmap, reg, valid_bit);

	tegra_set_cअगर(admaअगर->regmap, reg, &cअगर_conf);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_start(काष्ठा snd_soc_dai *dai, पूर्णांक direction)
अणु
	काष्ठा tegra_admaअगर *admaअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक reg, mask, val;

	चयन (direction) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		mask = TX_ENABLE_MASK;
		val = TX_ENABLE;
		reg = CH_TX_REG(TEGRA_ADMAIF_TX_ENABLE, dai->id);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		mask = RX_ENABLE_MASK;
		val = RX_ENABLE;
		reg = CH_RX_REG(TEGRA_ADMAIF_RX_ENABLE, dai->id);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(admaअगर->regmap, reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_stop(काष्ठा snd_soc_dai *dai, पूर्णांक direction)
अणु
	काष्ठा tegra_admaअगर *admaअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक enable_reg, status_reg, reset_reg, mask, val;
	अक्षर *dir_name;
	पूर्णांक err, enable;

	चयन (direction) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		mask = TX_ENABLE_MASK;
		enable = TX_ENABLE;
		dir_name = "TX";
		enable_reg = CH_TX_REG(TEGRA_ADMAIF_TX_ENABLE, dai->id);
		status_reg = CH_TX_REG(TEGRA_ADMAIF_TX_STATUS, dai->id);
		reset_reg = CH_TX_REG(TEGRA_ADMAIF_TX_SOFT_RESET, dai->id);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		mask = RX_ENABLE_MASK;
		enable = RX_ENABLE;
		dir_name = "RX";
		enable_reg = CH_RX_REG(TEGRA_ADMAIF_RX_ENABLE, dai->id);
		status_reg = CH_RX_REG(TEGRA_ADMAIF_RX_STATUS, dai->id);
		reset_reg = CH_RX_REG(TEGRA_ADMAIF_RX_SOFT_RESET, dai->id);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Disable TX/RX channel */
	regmap_update_bits(admaअगर->regmap, enable_reg, mask, ~enable);

	/* Wait until ADMAIF TX/RX status is disabled */
	err = regmap_पढ़ो_poll_समयout_atomic(admaअगर->regmap, status_reg, val,
					      !(val & enable), 10, 10000);
	अगर (err < 0)
		dev_warn(dai->dev, "timeout: failed to disable ADMAIF%d_%s\n",
			 dai->id + 1, dir_name);

	/* SW reset */
	regmap_update_bits(admaअगर->regmap, reset_reg, SW_RESET_MASK, SW_RESET);

	/* Wait till SW reset is complete */
	err = regmap_पढ़ो_poll_समयout_atomic(admaअगर->regmap, reset_reg, val,
					      !(val & SW_RESET_MASK & SW_RESET),
					      10, 10000);
	अगर (err) अणु
		dev_err(dai->dev, "timeout: SW reset failed for ADMAIF%d_%s\n",
			dai->id + 1, dir_name);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक err;

	err = snd_dmaengine_pcm_trigger(substream, cmd);
	अगर (err)
		वापस err;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		वापस tegra_admaअगर_start(dai, substream->stream);
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		वापस tegra_admaअगर_stop(dai, substream->stream);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra_admaअगर_dai_ops = अणु
	.hw_params	= tegra_admaअगर_hw_params,
	.trigger	= tegra_admaअगर_trigger,
पूर्ण;

अटल पूर्णांक tegra_admaअगर_get_control(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_क्रमागत *ec = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा tegra_admaअगर *admaअगर = snd_soc_component_get_drvdata(cmpnt);
	दीर्घ *uctl_val = &ucontrol->value.पूर्णांकeger.value[0];

	अगर (म_माला(kcontrol->id.name, "Playback Mono To Stereo"))
		*uctl_val = admaअगर->mono_to_stereo[ADMAIF_TX_PATH][ec->reg];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Mono To Stereo"))
		*uctl_val = admaअगर->mono_to_stereo[ADMAIF_RX_PATH][ec->reg];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Playback Stereo To Mono"))
		*uctl_val = admaअगर->stereo_to_mono[ADMAIF_TX_PATH][ec->reg];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Stereo To Mono"))
		*uctl_val = admaअगर->stereo_to_mono[ADMAIF_RX_PATH][ec->reg];

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_put_control(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_क्रमागत *ec = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा tegra_admaअगर *admaअगर = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];

	अगर (म_माला(kcontrol->id.name, "Playback Mono To Stereo"))
		admaअगर->mono_to_stereo[ADMAIF_TX_PATH][ec->reg] = value;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Mono To Stereo"))
		admaअगर->mono_to_stereo[ADMAIF_RX_PATH][ec->reg] = value;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Playback Stereo To Mono"))
		admaअगर->stereo_to_mono[ADMAIF_TX_PATH][ec->reg] = value;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Capture Stereo To Mono"))
		admaअगर->stereo_to_mono[ADMAIF_RX_PATH][ec->reg] = value;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra_admaअगर *admaअगर = snd_soc_dai_get_drvdata(dai);

	dai->capture_dma_data = &admaअगर->capture_dma_data[dai->id];
	dai->playback_dma_data = &admaअगर->playback_dma_data[dai->id];

	वापस 0;
पूर्ण

#घोषणा DAI(dai_name)					\
	अणु							\
		.name = dai_name,				\
		.probe = tegra_admaअगर_dai_probe,		\
		.playback = अणु					\
			.stream_name = dai_name " Playback",	\
			.channels_min = 1,			\
			.channels_max = 16,			\
			.rates = SNDRV_PCM_RATE_8000_192000,	\
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |	\
				SNDRV_PCM_FMTBIT_S16_LE |	\
				SNDRV_PCM_FMTBIT_S32_LE,	\
		पूर्ण,						\
		.capture = अणु					\
			.stream_name = dai_name " Capture",	\
			.channels_min = 1,			\
			.channels_max = 16,			\
			.rates = SNDRV_PCM_RATE_8000_192000,	\
			.क्रमmats = SNDRV_PCM_FMTBIT_S8 |	\
				SNDRV_PCM_FMTBIT_S16_LE |	\
				SNDRV_PCM_FMTBIT_S32_LE,	\
		पूर्ण,						\
		.ops = &tegra_admaअगर_dai_ops,			\
	पूर्ण

अटल काष्ठा snd_soc_dai_driver tegra210_admaअगर_cmpnt_dais[] = अणु
	DAI("ADMAIF1"),
	DAI("ADMAIF2"),
	DAI("ADMAIF3"),
	DAI("ADMAIF4"),
	DAI("ADMAIF5"),
	DAI("ADMAIF6"),
	DAI("ADMAIF7"),
	DAI("ADMAIF8"),
	DAI("ADMAIF9"),
	DAI("ADMAIF10"),
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tegra186_admaअगर_cmpnt_dais[] = अणु
	DAI("ADMAIF1"),
	DAI("ADMAIF2"),
	DAI("ADMAIF3"),
	DAI("ADMAIF4"),
	DAI("ADMAIF5"),
	DAI("ADMAIF6"),
	DAI("ADMAIF7"),
	DAI("ADMAIF8"),
	DAI("ADMAIF9"),
	DAI("ADMAIF10"),
	DAI("ADMAIF11"),
	DAI("ADMAIF12"),
	DAI("ADMAIF13"),
	DAI("ADMAIF14"),
	DAI("ADMAIF15"),
	DAI("ADMAIF16"),
	DAI("ADMAIF17"),
	DAI("ADMAIF18"),
	DAI("ADMAIF19"),
	DAI("ADMAIF20"),
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra_admaअगर_stereo_conv_text[] = अणु
	"CH0", "CH1", "AVG",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra_admaअगर_mono_conv_text[] = अणु
	"Zero", "Copy",
पूर्ण;

/*
 * Below macro is added to aव्योम looping over all ADMAIFx controls related
 * to mono/stereo conversions in get()/put() callbacks.
 */
#घोषणा NV_SOC_ENUM_EXT(xname, xreg, xhandler_get, xhandler_put, xक्रमागत_text)   \
अणु									       \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,				       \
	.info = snd_soc_info_क्रमागत_द्विगुन,				       \
	.name = xname,							       \
	.get = xhandler_get,						       \
	.put = xhandler_put,						       \
	.निजी_value = (अचिन्हित दीर्घ)&(काष्ठा soc_क्रमागत)		       \
		SOC_ENUM_SINGLE(xreg, 0, ARRAY_SIZE(xक्रमागत_text), xक्रमागत_text)   \
पूर्ण

#घोषणा TEGRA_ADMAIF_CIF_CTRL(reg)					       \
	NV_SOC_ENUM_EXT("ADMAIF" #reg " Playback Mono To Stereo", reg - 1,\
			tegra_admaअगर_get_control, tegra_admaअगर_put_control,    \
			tegra_admaअगर_mono_conv_text),			       \
	NV_SOC_ENUM_EXT("ADMAIF" #reg " Playback Stereo To Mono", reg - 1,\
			tegra_admaअगर_get_control, tegra_admaअगर_put_control,    \
			tegra_admaअगर_stereo_conv_text),			       \
	NV_SOC_ENUM_EXT("ADMAIF" #reg " Capture Mono To Stereo", reg - 1, \
			tegra_admaअगर_get_control, tegra_admaअगर_put_control,    \
			tegra_admaअगर_mono_conv_text),			       \
	NV_SOC_ENUM_EXT("ADMAIF" #reg " Capture Stereo To Mono", reg - 1, \
			tegra_admaअगर_get_control, tegra_admaअगर_put_control,    \
			tegra_admaअगर_stereo_conv_text)

अटल काष्ठा snd_kcontrol_new tegra210_admaअगर_controls[] = अणु
	TEGRA_ADMAIF_CIF_CTRL(1),
	TEGRA_ADMAIF_CIF_CTRL(2),
	TEGRA_ADMAIF_CIF_CTRL(3),
	TEGRA_ADMAIF_CIF_CTRL(4),
	TEGRA_ADMAIF_CIF_CTRL(5),
	TEGRA_ADMAIF_CIF_CTRL(6),
	TEGRA_ADMAIF_CIF_CTRL(7),
	TEGRA_ADMAIF_CIF_CTRL(8),
	TEGRA_ADMAIF_CIF_CTRL(9),
	TEGRA_ADMAIF_CIF_CTRL(10),
पूर्ण;

अटल काष्ठा snd_kcontrol_new tegra186_admaअगर_controls[] = अणु
	TEGRA_ADMAIF_CIF_CTRL(1),
	TEGRA_ADMAIF_CIF_CTRL(2),
	TEGRA_ADMAIF_CIF_CTRL(3),
	TEGRA_ADMAIF_CIF_CTRL(4),
	TEGRA_ADMAIF_CIF_CTRL(5),
	TEGRA_ADMAIF_CIF_CTRL(6),
	TEGRA_ADMAIF_CIF_CTRL(7),
	TEGRA_ADMAIF_CIF_CTRL(8),
	TEGRA_ADMAIF_CIF_CTRL(9),
	TEGRA_ADMAIF_CIF_CTRL(10),
	TEGRA_ADMAIF_CIF_CTRL(11),
	TEGRA_ADMAIF_CIF_CTRL(12),
	TEGRA_ADMAIF_CIF_CTRL(13),
	TEGRA_ADMAIF_CIF_CTRL(14),
	TEGRA_ADMAIF_CIF_CTRL(15),
	TEGRA_ADMAIF_CIF_CTRL(16),
	TEGRA_ADMAIF_CIF_CTRL(17),
	TEGRA_ADMAIF_CIF_CTRL(18),
	TEGRA_ADMAIF_CIF_CTRL(19),
	TEGRA_ADMAIF_CIF_CTRL(20),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra210_admaअगर_cmpnt = अणु
	.controls		= tegra210_admaअगर_controls,
	.num_controls		= ARRAY_SIZE(tegra210_admaअगर_controls),
	.pcm_स्थिरruct		= tegra_pcm_स्थिरruct,
	.pcm_deकाष्ठा		= tegra_pcm_deकाष्ठा,
	.खोलो			= tegra_pcm_खोलो,
	.बंद			= tegra_pcm_बंद,
	.hw_params		= tegra_pcm_hw_params,
	.hw_मुक्त		= tegra_pcm_hw_मुक्त,
	.mmap			= tegra_pcm_mmap,
	.poपूर्णांकer		= tegra_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra186_admaअगर_cmpnt = अणु
	.controls		= tegra186_admaअगर_controls,
	.num_controls		= ARRAY_SIZE(tegra186_admaअगर_controls),
	.pcm_स्थिरruct		= tegra_pcm_स्थिरruct,
	.pcm_deकाष्ठा		= tegra_pcm_deकाष्ठा,
	.खोलो			= tegra_pcm_खोलो,
	.बंद			= tegra_pcm_बंद,
	.hw_params		= tegra_pcm_hw_params,
	.hw_मुक्त		= tegra_pcm_hw_मुक्त,
	.mmap			= tegra_pcm_mmap,
	.poपूर्णांकer		= tegra_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा tegra_admaअगर_soc_data soc_data_tegra210 = अणु
	.num_ch		= TEGRA210_ADMAIF_CHANNEL_COUNT,
	.cmpnt		= &tegra210_admaअगर_cmpnt,
	.dais		= tegra210_admaअगर_cmpnt_dais,
	.regmap_conf	= &tegra210_admaअगर_regmap_config,
	.global_base	= TEGRA210_ADMAIF_GLOBAL_BASE,
	.tx_base	= TEGRA210_ADMAIF_TX_BASE,
	.rx_base	= TEGRA210_ADMAIF_RX_BASE,
पूर्ण;

अटल स्थिर काष्ठा tegra_admaअगर_soc_data soc_data_tegra186 = अणु
	.num_ch		= TEGRA186_ADMAIF_CHANNEL_COUNT,
	.cmpnt		= &tegra186_admaअगर_cmpnt,
	.dais		= tegra186_admaअगर_cmpnt_dais,
	.regmap_conf	= &tegra186_admaअगर_regmap_config,
	.global_base	= TEGRA186_ADMAIF_GLOBAL_BASE,
	.tx_base	= TEGRA186_ADMAIF_TX_BASE,
	.rx_base	= TEGRA186_ADMAIF_RX_BASE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_admaअगर_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-admaif", .data = &soc_data_tegra210 पूर्ण,
	अणु .compatible = "nvidia,tegra186-admaif", .data = &soc_data_tegra186 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_admaअगर_of_match);

अटल पूर्णांक tegra_admaअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_admaअगर *admaअगर;
	व्योम __iomem *regs;
	काष्ठा resource *res;
	पूर्णांक err, i;

	admaअगर = devm_kzalloc(&pdev->dev, माप(*admaअगर), GFP_KERNEL);
	अगर (!admaअगर)
		वापस -ENOMEM;

	admaअगर->soc_data = of_device_get_match_data(&pdev->dev);

	dev_set_drvdata(&pdev->dev, admaअगर);

	admaअगर->capture_dma_data =
		devm_kसुस्मृति(&pdev->dev,
			     admaअगर->soc_data->num_ch,
			     माप(काष्ठा snd_dmaengine_dai_dma_data),
			     GFP_KERNEL);
	अगर (!admaअगर->capture_dma_data)
		वापस -ENOMEM;

	admaअगर->playback_dma_data =
		devm_kसुस्मृति(&pdev->dev,
			     admaअगर->soc_data->num_ch,
			     माप(काष्ठा snd_dmaengine_dai_dma_data),
			     GFP_KERNEL);
	अगर (!admaअगर->playback_dma_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < ADMAIF_PATHS; i++) अणु
		admaअगर->mono_to_stereo[i] =
			devm_kसुस्मृति(&pdev->dev, admaअगर->soc_data->num_ch,
				     माप(अचिन्हित पूर्णांक), GFP_KERNEL);
		अगर (!admaअगर->mono_to_stereo[i])
			वापस -ENOMEM;

		admaअगर->stereo_to_mono[i] =
			devm_kसुस्मृति(&pdev->dev, admaअगर->soc_data->num_ch,
				     माप(अचिन्हित पूर्णांक), GFP_KERNEL);
		अगर (!admaअगर->stereo_to_mono[i])
			वापस -ENOMEM;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	admaअगर->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					       admaअगर->soc_data->regmap_conf);
	अगर (IS_ERR(admaअगर->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		वापस PTR_ERR(admaअगर->regmap);
	पूर्ण

	regcache_cache_only(admaअगर->regmap, true);

	regmap_update_bits(admaअगर->regmap, admaअगर->soc_data->global_base +
			   TEGRA_ADMAIF_GLOBAL_ENABLE, 1, 1);

	क्रम (i = 0; i < admaअगर->soc_data->num_ch; i++) अणु
		admaअगर->playback_dma_data[i].addr = res->start +
			CH_TX_REG(TEGRA_ADMAIF_TX_FIFO_WRITE, i);

		admaअगर->capture_dma_data[i].addr = res->start +
			CH_RX_REG(TEGRA_ADMAIF_RX_FIFO_READ, i);

		admaअगर->playback_dma_data[i].addr_width = 32;

		अगर (of_property_पढ़ो_string_index(pdev->dev.of_node,
				"dma-names", (i * 2) + 1,
				&admaअगर->playback_dma_data[i].chan_name) < 0) अणु
			dev_err(&pdev->dev,
				"missing property nvidia,dma-names\n");

			वापस -ENODEV;
		पूर्ण

		admaअगर->capture_dma_data[i].addr_width = 32;

		अगर (of_property_पढ़ो_string_index(pdev->dev.of_node,
				"dma-names",
				(i * 2),
				&admaअगर->capture_dma_data[i].chan_name) < 0) अणु
			dev_err(&pdev->dev,
				"missing property nvidia,dma-names\n");

			वापस -ENODEV;
		पूर्ण
	पूर्ण

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      admaअगर->soc_data->cmpnt,
					      admaअगर->soc_data->dais,
					      admaअगर->soc_data->num_ch);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"can't register ADMAIF component, err: %d\n", err);
		वापस err;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_admaअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_admaअगर_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_admaअगर_runसमय_suspend,
			   tegra_admaअगर_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_admaअगर_driver = अणु
	.probe = tegra_admaअगर_probe,
	.हटाओ = tegra_admaअगर_हटाओ,
	.driver = अणु
		.name = "tegra210-admaif",
		.of_match_table = tegra_admaअगर_of_match,
		.pm = &tegra_admaअगर_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_admaअगर_driver);

MODULE_AUTHOR("Songhee Baek <sbaek@nvidia.com>");
MODULE_DESCRIPTION("Tegra210 ASoC ADMAIF driver");
MODULE_LICENSE("GPL v2");
