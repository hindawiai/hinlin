<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// soc-dai.c
//
// Copyright (C) 2019 Renesas Electronics Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//

#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc-link.h>

#घोषणा soc_dai_ret(dai, ret) _soc_dai_ret(dai, __func__, ret)
अटल अंतरभूत पूर्णांक _soc_dai_ret(काष्ठा snd_soc_dai *dai,
			       स्थिर अक्षर *func, पूर्णांक ret)
अणु
	/* Positive, Zero values are not errors */
	अगर (ret >= 0)
		वापस ret;

	/* Negative values might be errors */
	चयन (ret) अणु
	हाल -EPROBE_DEFER:
	हाल -ENOTSUPP:
		अवरोध;
	शेष:
		dev_err(dai->dev,
			"ASoC: error at %s on %s: %d\n",
			func, dai->name, ret);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * We might want to check substream by using list.
 * In such हाल, we can update these macros.
 */
#घोषणा soc_dai_mark_push(dai, substream, tgt)	((dai)->mark_##tgt = substream)
#घोषणा soc_dai_mark_pop(dai, substream, tgt)	((dai)->mark_##tgt = शून्य)
#घोषणा soc_dai_mark_match(dai, substream, tgt)	((dai)->mark_##tgt == substream)

/**
 * snd_soc_dai_set_sysclk - configure DAI प्रणाली or master घड़ी.
 * @dai: DAI
 * @clk_id: DAI specअगरic घड़ी ID
 * @freq: new घड़ी frequency in Hz
 * @dir: new घड़ी direction - input/output.
 *
 * Configures the DAI master (MCLK) or प्रणाली (SYSCLK) घड़ीing.
 */
पूर्णांक snd_soc_dai_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			   अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	पूर्णांक ret;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_sysclk)
		ret = dai->driver->ops->set_sysclk(dai, clk_id, freq, dir);
	अन्यथा
		ret = snd_soc_component_set_sysclk(dai->component, clk_id, 0,
						   freq, dir);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_sysclk);

/**
 * snd_soc_dai_set_clkभाग - configure DAI घड़ी भागiders.
 * @dai: DAI
 * @भाग_id: DAI specअगरic घड़ी भागider ID
 * @भाग: new घड़ी भागisor.
 *
 * Configures the घड़ी भागiders. This is used to derive the best DAI bit and
 * frame घड़ीs from the प्रणाली or master घड़ी. It's best to set the DAI bit
 * and frame घड़ीs as low as possible to save प्रणाली घातer.
 */
पूर्णांक snd_soc_dai_set_clkभाग(काष्ठा snd_soc_dai *dai,
			   पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_clkभाग)
		ret = dai->driver->ops->set_clkभाग(dai, भाग_id, भाग);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_clkभाग);

/**
 * snd_soc_dai_set_pll - configure DAI PLL.
 * @dai: DAI
 * @pll_id: DAI specअगरic PLL ID
 * @source: DAI specअगरic source क्रम the PLL
 * @freq_in: PLL input घड़ी frequency in Hz
 * @freq_out: requested PLL output घड़ी frequency in Hz
 *
 * Configures and enables PLL to generate output घड़ी based on input घड़ी.
 */
पूर्णांक snd_soc_dai_set_pll(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
			अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक ret;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_pll)
		ret = dai->driver->ops->set_pll(dai, pll_id, source,
						freq_in, freq_out);
	अन्यथा
		ret = snd_soc_component_set_pll(dai->component, pll_id, source,
						freq_in, freq_out);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_pll);

/**
 * snd_soc_dai_set_bclk_ratio - configure BCLK to sample rate ratio.
 * @dai: DAI
 * @ratio: Ratio of BCLK to Sample rate.
 *
 * Configures the DAI क्रम a preset BCLK to sample rate ratio.
 */
पूर्णांक snd_soc_dai_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_bclk_ratio)
		ret = dai->driver->ops->set_bclk_ratio(dai, ratio);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_bclk_ratio);

/**
 * snd_soc_dai_set_fmt - configure DAI hardware audio क्रमmat.
 * @dai: DAI
 * @fmt: SND_SOC_DAIFMT_* क्रमmat value.
 *
 * Configures the DAI hardware क्रमmat and घड़ीing.
 */
पूर्णांक snd_soc_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_fmt)
		ret = dai->driver->ops->set_fmt(dai, fmt);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_fmt);

/**
 * snd_soc_xlate_tdm_slot_mask - generate tx/rx slot mask.
 * @slots: Number of slots in use.
 * @tx_mask: biपंचांगask representing active TX slots.
 * @rx_mask: biपंचांगask representing active RX slots.
 *
 * Generates the TDM tx and rx slot शेष masks क्रम DAI.
 */
अटल पूर्णांक snd_soc_xlate_tdm_slot_mask(अचिन्हित पूर्णांक slots,
				       अचिन्हित पूर्णांक *tx_mask,
				       अचिन्हित पूर्णांक *rx_mask)
अणु
	अगर (*tx_mask || *rx_mask)
		वापस 0;

	अगर (!slots)
		वापस -EINVAL;

	*tx_mask = (1 << slots) - 1;
	*rx_mask = (1 << slots) - 1;

	वापस 0;
पूर्ण

/**
 * snd_soc_dai_set_tdm_slot() - Configures a DAI क्रम TDM operation
 * @dai: The DAI to configure
 * @tx_mask: biपंचांगask representing active TX slots.
 * @rx_mask: biपंचांगask representing active RX slots.
 * @slots: Number of slots in use.
 * @slot_width: Width in bits क्रम each slot.
 *
 * This function configures the specअगरied DAI क्रम TDM operation. @slot contains
 * the total number of slots of the TDM stream and @slot_with the width of each
 * slot in bit घड़ी cycles. @tx_mask and @rx_mask are biपंचांगasks specअगरying the
 * active slots of the TDM stream क्रम the specअगरied DAI, i.e. which slots the
 * DAI should ग_लिखो to or पढ़ो from. If a bit is set the corresponding slot is
 * active, अगर a bit is cleared the corresponding slot is inactive. Bit 0 maps to
 * the first slot, bit 1 to the second slot and so on. The first active slot
 * maps to the first channel of the DAI, the second active slot to the second
 * channel and so on.
 *
 * TDM mode can be disabled by passing 0 क्रम @slots. In this हाल @tx_mask,
 * @rx_mask and @slot_width will be ignored.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
पूर्णांक snd_soc_dai_set_tdm_slot(काष्ठा snd_soc_dai *dai,
			     अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
			     पूर्णांक slots, पूर्णांक slot_width)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (dai->driver->ops &&
	    dai->driver->ops->xlate_tdm_slot_mask)
		dai->driver->ops->xlate_tdm_slot_mask(slots,
						      &tx_mask, &rx_mask);
	अन्यथा
		snd_soc_xlate_tdm_slot_mask(slots, &tx_mask, &rx_mask);

	dai->tx_mask = tx_mask;
	dai->rx_mask = rx_mask;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_tdm_slot)
		ret = dai->driver->ops->set_tdm_slot(dai, tx_mask, rx_mask,
						      slots, slot_width);
	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_tdm_slot);

/**
 * snd_soc_dai_set_channel_map - configure DAI audio channel map
 * @dai: DAI
 * @tx_num: how many TX channels
 * @tx_slot: poपूर्णांकer to an array which imply the TX slot number channel
 *           0~num-1 uses
 * @rx_num: how many RX channels
 * @rx_slot: poपूर्णांकer to an array which imply the RX slot number channel
 *           0~num-1 uses
 *
 * configure the relationship between channel number and TDM slot number.
 */
पूर्णांक snd_soc_dai_set_channel_map(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
				अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_channel_map)
		ret = dai->driver->ops->set_channel_map(dai, tx_num, tx_slot,
							rx_num, rx_slot);
	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_channel_map);

/**
 * snd_soc_dai_get_channel_map - Get DAI audio channel map
 * @dai: DAI
 * @tx_num: how many TX channels
 * @tx_slot: poपूर्णांकer to an array which imply the TX slot number channel
 *           0~num-1 uses
 * @rx_num: how many RX channels
 * @rx_slot: poपूर्णांकer to an array which imply the RX slot number channel
 *           0~num-1 uses
 */
पूर्णांक snd_soc_dai_get_channel_map(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
				अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	पूर्णांक ret = -ENOTSUPP;

	अगर (dai->driver->ops &&
	    dai->driver->ops->get_channel_map)
		ret = dai->driver->ops->get_channel_map(dai, tx_num, tx_slot,
							rx_num, rx_slot);
	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_get_channel_map);

/**
 * snd_soc_dai_set_tristate - configure DAI प्रणाली or master घड़ी.
 * @dai: DAI
 * @tristate: tristate enable
 *
 * Tristates the DAI so that others can use it.
 */
पूर्णांक snd_soc_dai_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (dai->driver->ops &&
	    dai->driver->ops->set_tristate)
		ret = dai->driver->ops->set_tristate(dai, tristate);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_set_tristate);

/**
 * snd_soc_dai_digital_mute - configure DAI प्रणाली or master घड़ी.
 * @dai: DAI
 * @mute: mute enable
 * @direction: stream to mute
 *
 * Mutes the DAI DAC.
 */
पूर्णांक snd_soc_dai_digital_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute,
			     पूर्णांक direction)
अणु
	पूर्णांक ret = -ENOTSUPP;

	/*
	 * ignore अगर direction was CAPTURE
	 * and it had .no_capture_mute flag
	 */
	अगर (dai->driver->ops &&
	    dai->driver->ops->mute_stream &&
	    (direction == SNDRV_PCM_STREAM_PLAYBACK ||
	     !dai->driver->ops->no_capture_mute))
		ret = dai->driver->ops->mute_stream(dai, mute, direction);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_digital_mute);

पूर्णांक snd_soc_dai_hw_params(काष्ठा snd_soc_dai *dai,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret = 0;

	/* perक्रमm any topology hw_params fixups beक्रमe DAI  */
	ret = snd_soc_link_be_hw_params_fixup(rtd, params);
	अगर (ret < 0)
		जाओ end;

	अगर (dai->driver->ops &&
	    dai->driver->ops->hw_params)
		ret = dai->driver->ops->hw_params(substream, params, dai);

	/* mark substream अगर succeeded */
	अगर (ret == 0)
		soc_dai_mark_push(dai, substream, hw_params);
end:
	वापस soc_dai_ret(dai, ret);
पूर्ण

व्योम snd_soc_dai_hw_मुक्त(काष्ठा snd_soc_dai *dai,
			 काष्ठा snd_pcm_substream *substream,
			 पूर्णांक rollback)
अणु
	अगर (rollback && !soc_dai_mark_match(dai, substream, hw_params))
		वापस;

	अगर (dai->driver->ops &&
	    dai->driver->ops->hw_मुक्त)
		dai->driver->ops->hw_मुक्त(substream, dai);

	/* हटाओ marked substream */
	soc_dai_mark_pop(dai, substream, hw_params);
पूर्ण

पूर्णांक snd_soc_dai_startup(काष्ठा snd_soc_dai *dai,
			काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->ops &&
	    dai->driver->ops->startup)
		ret = dai->driver->ops->startup(substream, dai);

	/* mark substream अगर succeeded */
	अगर (ret == 0)
		soc_dai_mark_push(dai, substream, startup);

	वापस soc_dai_ret(dai, ret);
पूर्ण

व्योम snd_soc_dai_shutकरोwn(काष्ठा snd_soc_dai *dai,
			  काष्ठा snd_pcm_substream *substream,
			  पूर्णांक rollback)
अणु
	अगर (rollback && !soc_dai_mark_match(dai, substream, startup))
		वापस;

	अगर (dai->driver->ops &&
	    dai->driver->ops->shutकरोwn)
		dai->driver->ops->shutकरोwn(substream, dai);

	/* हटाओ marked substream */
	soc_dai_mark_pop(dai, substream, startup);
पूर्ण

snd_pcm_sframes_t snd_soc_dai_delay(काष्ठा snd_soc_dai *dai,
				    काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक delay = 0;

	अगर (dai->driver->ops &&
	    dai->driver->ops->delay)
		delay = dai->driver->ops->delay(substream, dai);

	वापस delay;
पूर्ण

पूर्णांक snd_soc_dai_compress_new(काष्ठा snd_soc_dai *dai,
			     काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num)
अणु
	पूर्णांक ret = -ENOTSUPP;
	अगर (dai->driver->compress_new)
		ret = dai->driver->compress_new(rtd, num);
	वापस soc_dai_ret(dai, ret);
पूर्ण

/*
 * snd_soc_dai_stream_valid() - check अगर a DAI supports the given stream
 *
 * Returns true अगर the DAI supports the indicated stream type.
 */
bool snd_soc_dai_stream_valid(काष्ठा snd_soc_dai *dai, पूर्णांक dir)
अणु
	काष्ठा snd_soc_pcm_stream *stream = snd_soc_dai_get_pcm_stream(dai, dir);

	/* If the codec specअगरies any channels at all, it supports the stream */
	वापस stream->channels_min;
पूर्ण

/*
 * snd_soc_dai_link_set_capabilities() - set dai_link properties based on its DAIs
 */
व्योम snd_soc_dai_link_set_capabilities(काष्ठा snd_soc_dai_link *dai_link)
अणु
	काष्ठा snd_soc_dai_link_component *cpu;
	काष्ठा snd_soc_dai_link_component *codec;
	काष्ठा snd_soc_dai *dai;
	bool supported[SNDRV_PCM_STREAM_LAST + 1];
	bool supported_cpu;
	bool supported_codec;
	पूर्णांक direction;
	पूर्णांक i;

	क्रम_each_pcm_streams(direction) अणु
		supported_cpu = false;
		supported_codec = false;

		क्रम_each_link_cpus(dai_link, i, cpu) अणु
			dai = snd_soc_find_dai_with_mutex(cpu);
			अगर (dai && snd_soc_dai_stream_valid(dai, direction)) अणु
				supported_cpu = true;
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम_each_link_codecs(dai_link, i, codec) अणु
			dai = snd_soc_find_dai_with_mutex(codec);
			अगर (dai && snd_soc_dai_stream_valid(dai, direction)) अणु
				supported_codec = true;
				अवरोध;
			पूर्ण
		पूर्ण
		supported[direction] = supported_cpu && supported_codec;
	पूर्ण

	dai_link->dpcm_playback = supported[SNDRV_PCM_STREAM_PLAYBACK];
	dai_link->dpcm_capture  = supported[SNDRV_PCM_STREAM_CAPTURE];
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_link_set_capabilities);

व्योम snd_soc_dai_action(काष्ठा snd_soc_dai *dai,
			पूर्णांक stream, पूर्णांक action)
अणु
	/* see snd_soc_dai_stream_active() */
	dai->stream_active[stream]	+= action;

	/* see snd_soc_component_active() */
	dai->component->active		+= action;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_action);

पूर्णांक snd_soc_dai_active(काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक stream, active;

	active = 0;
	क्रम_each_pcm_streams(stream)
		active += dai->stream_active[stream];

	वापस active;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_active);

पूर्णांक snd_soc_pcm_dai_probe(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक order)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i;

	क्रम_each_rtd_dais(rtd, i, dai) अणु
		अगर (dai->driver->probe_order != order)
			जारी;

		अगर (dai->driver->probe) अणु
			पूर्णांक ret = dai->driver->probe(dai);

			अगर (ret < 0)
				वापस soc_dai_ret(dai, ret);
		पूर्ण

		dai->probed = 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_pcm_dai_हटाओ(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक order)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i, r, ret = 0;

	क्रम_each_rtd_dais(rtd, i, dai) अणु
		अगर (dai->driver->हटाओ_order != order)
			जारी;

		अगर (dai->probed &&
		    dai->driver->हटाओ) अणु
			r = dai->driver->हटाओ(dai);
			अगर (r < 0)
				ret = r; /* use last error */
		पूर्ण

		dai->probed = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक snd_soc_pcm_dai_new(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i, ret = 0;

	क्रम_each_rtd_dais(rtd, i, dai) अणु
		अगर (dai->driver->pcm_new) अणु
			ret = dai->driver->pcm_new(rtd, dai);
			अगर (ret < 0)
				वापस soc_dai_ret(dai, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_pcm_dai_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i, ret;

	क्रम_each_rtd_dais(rtd, i, dai) अणु
		अगर (dai->driver->ops &&
		    dai->driver->ops->prepare) अणु
			ret = dai->driver->ops->prepare(substream, dai);
			अगर (ret < 0)
				वापस soc_dai_ret(dai, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक soc_dai_trigger(काष्ठा snd_soc_dai *dai,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->ops &&
	    dai->driver->ops->trigger)
		ret = dai->driver->ops->trigger(substream, cmd, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण

पूर्णांक snd_soc_pcm_dai_trigger(काष्ठा snd_pcm_substream *substream,
			    पूर्णांक cmd, पूर्णांक rollback)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i, r, ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		क्रम_each_rtd_dais(rtd, i, dai) अणु
			ret = soc_dai_trigger(dai, substream, cmd);
			अगर (ret < 0)
				अवरोध;
			soc_dai_mark_push(dai, substream, trigger);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		क्रम_each_rtd_dais(rtd, i, dai) अणु
			अगर (rollback && !soc_dai_mark_match(dai, substream, trigger))
				जारी;

			r = soc_dai_trigger(dai, substream, cmd);
			अगर (r < 0)
				ret = r; /* use last ret */
			soc_dai_mark_pop(dai, substream, trigger);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक snd_soc_pcm_dai_bespoke_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i, ret;

	क्रम_each_rtd_dais(rtd, i, dai) अणु
		अगर (dai->driver->ops &&
		    dai->driver->ops->bespoke_trigger) अणु
			ret = dai->driver->ops->bespoke_trigger(substream,
								cmd, dai);
			अगर (ret < 0)
				वापस soc_dai_ret(dai, ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_dai_compr_startup(काष्ठा snd_soc_dai *dai,
			      काष्ठा snd_compr_stream *cstream)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->startup)
		ret = dai->driver->cops->startup(cstream, dai);

	/* mark cstream अगर succeeded */
	अगर (ret == 0)
		soc_dai_mark_push(dai, cstream, compr_startup);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_startup);

व्योम snd_soc_dai_compr_shutकरोwn(काष्ठा snd_soc_dai *dai,
				काष्ठा snd_compr_stream *cstream,
				पूर्णांक rollback)
अणु
	अगर (rollback && !soc_dai_mark_match(dai, cstream, compr_startup))
		वापस;

	अगर (dai->driver->cops &&
	    dai->driver->cops->shutकरोwn)
		dai->driver->cops->shutकरोwn(cstream, dai);

	/* हटाओ marked cstream */
	soc_dai_mark_pop(dai, cstream, compr_startup);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_shutकरोwn);

पूर्णांक snd_soc_dai_compr_trigger(काष्ठा snd_soc_dai *dai,
			      काष्ठा snd_compr_stream *cstream, पूर्णांक cmd)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->trigger)
		ret = dai->driver->cops->trigger(cstream, cmd, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_trigger);

पूर्णांक snd_soc_dai_compr_set_params(काष्ठा snd_soc_dai *dai,
				 काष्ठा snd_compr_stream *cstream,
				 काष्ठा snd_compr_params *params)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->set_params)
		ret = dai->driver->cops->set_params(cstream, params, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_set_params);

पूर्णांक snd_soc_dai_compr_get_params(काष्ठा snd_soc_dai *dai,
				 काष्ठा snd_compr_stream *cstream,
				 काष्ठा snd_codec *params)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->get_params)
		ret = dai->driver->cops->get_params(cstream, params, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_get_params);

पूर्णांक snd_soc_dai_compr_ack(काष्ठा snd_soc_dai *dai,
			  काष्ठा snd_compr_stream *cstream,
			  माप_प्रकार bytes)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->ack)
		ret = dai->driver->cops->ack(cstream, bytes, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_ack);

पूर्णांक snd_soc_dai_compr_poपूर्णांकer(काष्ठा snd_soc_dai *dai,
			      काष्ठा snd_compr_stream *cstream,
			      काष्ठा snd_compr_tstamp *tstamp)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->poपूर्णांकer)
		ret = dai->driver->cops->poपूर्णांकer(cstream, tstamp, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_poपूर्णांकer);

पूर्णांक snd_soc_dai_compr_set_metadata(काष्ठा snd_soc_dai *dai,
				   काष्ठा snd_compr_stream *cstream,
				   काष्ठा snd_compr_metadata *metadata)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->set_metadata)
		ret = dai->driver->cops->set_metadata(cstream, metadata, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_set_metadata);

पूर्णांक snd_soc_dai_compr_get_metadata(काष्ठा snd_soc_dai *dai,
				   काष्ठा snd_compr_stream *cstream,
				   काष्ठा snd_compr_metadata *metadata)
अणु
	पूर्णांक ret = 0;

	अगर (dai->driver->cops &&
	    dai->driver->cops->get_metadata)
		ret = dai->driver->cops->get_metadata(cstream, metadata, dai);

	वापस soc_dai_ret(dai, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dai_compr_get_metadata);
