<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * linux/sound/soc-dai.h -- ALSA SoC Layer
 *
 * Copyright:	2005-2008 Wolfson Microelectronics. PLC.
 *
 * Digital Audio Interface (DAI) API.
 */

#अगर_अघोषित __LINUX_SND_SOC_DAI_H
#घोषणा __LINUX_SND_SOC_DAI_H


#समावेश <linux/list.h>
#समावेश <sound/asoc.h>

काष्ठा snd_pcm_substream;
काष्ठा snd_soc_dapm_widget;
काष्ठा snd_compr_stream;

/*
 * DAI hardware audio क्रमmats.
 *
 * Describes the physical PCM data क्रमmating and घड़ीing. Add new क्रमmats
 * to the end.
 */
#घोषणा SND_SOC_DAIFMT_I2S		SND_SOC_DAI_FORMAT_I2S
#घोषणा SND_SOC_DAIFMT_RIGHT_J		SND_SOC_DAI_FORMAT_RIGHT_J
#घोषणा SND_SOC_DAIFMT_LEFT_J		SND_SOC_DAI_FORMAT_LEFT_J
#घोषणा SND_SOC_DAIFMT_DSP_A		SND_SOC_DAI_FORMAT_DSP_A
#घोषणा SND_SOC_DAIFMT_DSP_B		SND_SOC_DAI_FORMAT_DSP_B
#घोषणा SND_SOC_DAIFMT_AC97		SND_SOC_DAI_FORMAT_AC97
#घोषणा SND_SOC_DAIFMT_PDM		SND_SOC_DAI_FORMAT_PDM

/* left and right justअगरied also known as MSB and LSB respectively */
#घोषणा SND_SOC_DAIFMT_MSB		SND_SOC_DAIFMT_LEFT_J
#घोषणा SND_SOC_DAIFMT_LSB		SND_SOC_DAIFMT_RIGHT_J

/*
 * DAI Clock gating.
 *
 * DAI bit घड़ीs can be gated (disabled) when the DAI is not
 * sending or receiving PCM data in a frame. This can be used to save घातer.
 */
#घोषणा SND_SOC_DAIFMT_CONT		(1 << 4) /* continuous घड़ी */
#घोषणा SND_SOC_DAIFMT_GATED		(0 << 4) /* घड़ी is gated */

/*
 * DAI hardware संकेत polarity.
 *
 * Specअगरies whether the DAI can also support inverted घड़ीs क्रम the specअगरied
 * क्रमmat.
 *
 * BCLK:
 * - "normal" polarity means संकेत is available at rising edge of BCLK
 * - "inverted" polarity means संकेत is available at falling edge of BCLK
 *
 * FSYNC "normal" polarity depends on the frame क्रमmat:
 * - I2S: frame consists of left then right channel data. Left channel starts
 *      with falling FSYNC edge, right channel starts with rising FSYNC edge.
 * - Left/Right Justअगरied: frame consists of left then right channel data.
 *      Left channel starts with rising FSYNC edge, right channel starts with
 *      falling FSYNC edge.
 * - DSP A/B: Frame starts with rising FSYNC edge.
 * - AC97: Frame starts with rising FSYNC edge.
 *
 * "Negative" FSYNC polarity is the one opposite of "normal" polarity.
 */
#घोषणा SND_SOC_DAIFMT_NB_NF		(0 << 8) /* normal bit घड़ी + frame */
#घोषणा SND_SOC_DAIFMT_NB_IF		(2 << 8) /* normal BCLK + inv FRM */
#घोषणा SND_SOC_DAIFMT_IB_NF		(3 << 8) /* invert BCLK + nor FRM */
#घोषणा SND_SOC_DAIFMT_IB_IF		(4 << 8) /* invert BCLK + FRM */

/*
 * DAI hardware घड़ी providers/consumers
 *
 * This is wrt the codec, the inverse is true क्रम the पूर्णांकerface
 * i.e. अगर the codec is clk and FRM provider then the पूर्णांकerface is
 * clk and frame consumer.
 */
#घोषणा SND_SOC_DAIFMT_CBP_CFP		(1 << 12) /* codec clk provider & frame provider */
#घोषणा SND_SOC_DAIFMT_CBC_CFP		(2 << 12) /* codec clk consumer & frame provider */
#घोषणा SND_SOC_DAIFMT_CBP_CFC		(3 << 12) /* codec clk provider & frame consumer */
#घोषणा SND_SOC_DAIFMT_CBC_CFC		(4 << 12) /* codec clk consumer & frame consumer */

/* previous definitions kept क्रम backwards-compatibility, करो not use in new contributions */
#घोषणा SND_SOC_DAIFMT_CBM_CFM		SND_SOC_DAIFMT_CBP_CFP
#घोषणा SND_SOC_DAIFMT_CBS_CFM		SND_SOC_DAIFMT_CBC_CFP
#घोषणा SND_SOC_DAIFMT_CBM_CFS		SND_SOC_DAIFMT_CBP_CFC
#घोषणा SND_SOC_DAIFMT_CBS_CFS		SND_SOC_DAIFMT_CBC_CFC

#घोषणा SND_SOC_DAIFMT_FORMAT_MASK		0x000f
#घोषणा SND_SOC_DAIFMT_CLOCK_MASK		0x00f0
#घोषणा SND_SOC_DAIFMT_INV_MASK			0x0f00
#घोषणा SND_SOC_DAIFMT_CLOCK_PROVIDER_MASK	0xf000

#घोषणा SND_SOC_DAIFMT_MASTER_MASK	SND_SOC_DAIFMT_CLOCK_PROVIDER_MASK

/*
 * Master Clock Directions
 */
#घोषणा SND_SOC_CLOCK_IN		0
#घोषणा SND_SOC_CLOCK_OUT		1

#घोषणा SND_SOC_STD_AC97_FMTS (SNDRV_PCM_FMTBIT_S8 |\
			       SNDRV_PCM_FMTBIT_S16_LE |\
			       SNDRV_PCM_FMTBIT_S16_BE |\
			       SNDRV_PCM_FMTBIT_S20_3LE |\
			       SNDRV_PCM_FMTBIT_S20_3BE |\
			       SNDRV_PCM_FMTBIT_S20_LE |\
			       SNDRV_PCM_FMTBIT_S20_BE |\
			       SNDRV_PCM_FMTBIT_S24_3LE |\
			       SNDRV_PCM_FMTBIT_S24_3BE |\
                               SNDRV_PCM_FMTBIT_S32_LE |\
                               SNDRV_PCM_FMTBIT_S32_BE)

काष्ठा snd_soc_dai_driver;
काष्ठा snd_soc_dai;
काष्ठा snd_ac97_bus_ops;

/* Digital Audio Interface घड़ीing API.*/
पूर्णांक snd_soc_dai_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
	अचिन्हित पूर्णांक freq, पूर्णांक dir);

पूर्णांक snd_soc_dai_set_clkभाग(काष्ठा snd_soc_dai *dai,
	पूर्णांक भाग_id, पूर्णांक भाग);

पूर्णांक snd_soc_dai_set_pll(काष्ठा snd_soc_dai *dai,
	पूर्णांक pll_id, पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out);

पूर्णांक snd_soc_dai_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio);

/* Digital Audio पूर्णांकerface क्रमmatting */
पूर्णांक snd_soc_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt);

पूर्णांक snd_soc_dai_set_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width);

पूर्णांक snd_soc_dai_set_channel_map(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
	अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot);

पूर्णांक snd_soc_dai_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate);

/* Digital Audio Interface mute */
पूर्णांक snd_soc_dai_digital_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute,
			     पूर्णांक direction);


पूर्णांक snd_soc_dai_get_channel_map(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
		अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot);

पूर्णांक snd_soc_dai_is_dummy(काष्ठा snd_soc_dai *dai);

पूर्णांक snd_soc_dai_hw_params(काष्ठा snd_soc_dai *dai,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params);
व्योम snd_soc_dai_hw_मुक्त(काष्ठा snd_soc_dai *dai,
			 काष्ठा snd_pcm_substream *substream,
			 पूर्णांक rollback);
पूर्णांक snd_soc_dai_startup(काष्ठा snd_soc_dai *dai,
			काष्ठा snd_pcm_substream *substream);
व्योम snd_soc_dai_shutकरोwn(काष्ठा snd_soc_dai *dai,
			  काष्ठा snd_pcm_substream *substream, पूर्णांक rollback);
snd_pcm_sframes_t snd_soc_dai_delay(काष्ठा snd_soc_dai *dai,
				    काष्ठा snd_pcm_substream *substream);
व्योम snd_soc_dai_suspend(काष्ठा snd_soc_dai *dai);
व्योम snd_soc_dai_resume(काष्ठा snd_soc_dai *dai);
पूर्णांक snd_soc_dai_compress_new(काष्ठा snd_soc_dai *dai,
			     काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num);
bool snd_soc_dai_stream_valid(काष्ठा snd_soc_dai *dai, पूर्णांक stream);
व्योम snd_soc_dai_link_set_capabilities(काष्ठा snd_soc_dai_link *dai_link);
व्योम snd_soc_dai_action(काष्ठा snd_soc_dai *dai,
			पूर्णांक stream, पूर्णांक action);
अटल अंतरभूत व्योम snd_soc_dai_activate(काष्ठा snd_soc_dai *dai,
					पूर्णांक stream)
अणु
	snd_soc_dai_action(dai, stream,  1);
पूर्ण
अटल अंतरभूत व्योम snd_soc_dai_deactivate(काष्ठा snd_soc_dai *dai,
					  पूर्णांक stream)
अणु
	snd_soc_dai_action(dai, stream, -1);
पूर्ण
पूर्णांक snd_soc_dai_active(काष्ठा snd_soc_dai *dai);

पूर्णांक snd_soc_pcm_dai_probe(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक order);
पूर्णांक snd_soc_pcm_dai_हटाओ(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक order);
पूर्णांक snd_soc_pcm_dai_new(काष्ठा snd_soc_pcm_runसमय *rtd);
पूर्णांक snd_soc_pcm_dai_prepare(काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_soc_pcm_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			    पूर्णांक rollback);
पूर्णांक snd_soc_pcm_dai_bespoke_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd);

पूर्णांक snd_soc_dai_compr_startup(काष्ठा snd_soc_dai *dai,
			      काष्ठा snd_compr_stream *cstream);
व्योम snd_soc_dai_compr_shutकरोwn(काष्ठा snd_soc_dai *dai,
				काष्ठा snd_compr_stream *cstream,
				पूर्णांक rollback);
पूर्णांक snd_soc_dai_compr_trigger(काष्ठा snd_soc_dai *dai,
			      काष्ठा snd_compr_stream *cstream, पूर्णांक cmd);
पूर्णांक snd_soc_dai_compr_set_params(काष्ठा snd_soc_dai *dai,
				 काष्ठा snd_compr_stream *cstream,
				 काष्ठा snd_compr_params *params);
पूर्णांक snd_soc_dai_compr_get_params(काष्ठा snd_soc_dai *dai,
				 काष्ठा snd_compr_stream *cstream,
				 काष्ठा snd_codec *params);
पूर्णांक snd_soc_dai_compr_ack(काष्ठा snd_soc_dai *dai,
			  काष्ठा snd_compr_stream *cstream,
			  माप_प्रकार bytes);
पूर्णांक snd_soc_dai_compr_poपूर्णांकer(काष्ठा snd_soc_dai *dai,
			      काष्ठा snd_compr_stream *cstream,
			      काष्ठा snd_compr_tstamp *tstamp);
पूर्णांक snd_soc_dai_compr_set_metadata(काष्ठा snd_soc_dai *dai,
				   काष्ठा snd_compr_stream *cstream,
				   काष्ठा snd_compr_metadata *metadata);
पूर्णांक snd_soc_dai_compr_get_metadata(काष्ठा snd_soc_dai *dai,
				   काष्ठा snd_compr_stream *cstream,
				   काष्ठा snd_compr_metadata *metadata);

काष्ठा snd_soc_dai_ops अणु
	/*
	 * DAI घड़ीing configuration, all optional.
	 * Called by soc_card drivers, normally in their hw_params.
	 */
	पूर्णांक (*set_sysclk)(काष्ठा snd_soc_dai *dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir);
	पूर्णांक (*set_pll)(काष्ठा snd_soc_dai *dai, पूर्णांक pll_id, पूर्णांक source,
		अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out);
	पूर्णांक (*set_clkभाग)(काष्ठा snd_soc_dai *dai, पूर्णांक भाग_id, पूर्णांक भाग);
	पूर्णांक (*set_bclk_ratio)(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio);

	/*
	 * DAI क्रमmat configuration
	 * Called by soc_card drivers, normally in their hw_params.
	 */
	पूर्णांक (*set_fmt)(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt);
	पूर्णांक (*xlate_tdm_slot_mask)(अचिन्हित पूर्णांक slots,
		अचिन्हित पूर्णांक *tx_mask, अचिन्हित पूर्णांक *rx_mask);
	पूर्णांक (*set_tdm_slot)(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
		पूर्णांक slots, पूर्णांक slot_width);
	पूर्णांक (*set_channel_map)(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
		अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot);
	पूर्णांक (*get_channel_map)(काष्ठा snd_soc_dai *dai,
			अचिन्हित पूर्णांक *tx_num, अचिन्हित पूर्णांक *tx_slot,
			अचिन्हित पूर्णांक *rx_num, अचिन्हित पूर्णांक *rx_slot);
	पूर्णांक (*set_tristate)(काष्ठा snd_soc_dai *dai, पूर्णांक tristate);

	पूर्णांक (*set_sdw_stream)(काष्ठा snd_soc_dai *dai,
			व्योम *stream, पूर्णांक direction);
	व्योम *(*get_sdw_stream)(काष्ठा snd_soc_dai *dai, पूर्णांक direction);

	/*
	 * DAI digital mute - optional.
	 * Called by soc-core to minimise any pops.
	 */
	पूर्णांक (*mute_stream)(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream);

	/*
	 * ALSA PCM audio operations - all optional.
	 * Called by soc-core during audio PCM operations.
	 */
	पूर्णांक (*startup)(काष्ठा snd_pcm_substream *,
		काष्ठा snd_soc_dai *);
	व्योम (*shutकरोwn)(काष्ठा snd_pcm_substream *,
		काष्ठा snd_soc_dai *);
	पूर्णांक (*hw_params)(काष्ठा snd_pcm_substream *,
		काष्ठा snd_pcm_hw_params *, काष्ठा snd_soc_dai *);
	पूर्णांक (*hw_मुक्त)(काष्ठा snd_pcm_substream *,
		काष्ठा snd_soc_dai *);
	पूर्णांक (*prepare)(काष्ठा snd_pcm_substream *,
		काष्ठा snd_soc_dai *);
	/*
	 * NOTE: Commands passed to the trigger function are not necessarily
	 * compatible with the current state of the dai. For example this
	 * sequence of commands is possible: START STOP STOP.
	 * So करो not unconditionally use refcounting functions in the trigger
	 * function, e.g. clk_enable/disable.
	 */
	पूर्णांक (*trigger)(काष्ठा snd_pcm_substream *, पूर्णांक,
		काष्ठा snd_soc_dai *);
	पूर्णांक (*bespoke_trigger)(काष्ठा snd_pcm_substream *, पूर्णांक,
		काष्ठा snd_soc_dai *);
	/*
	 * For hardware based FIFO caused delay reporting.
	 * Optional.
	 */
	snd_pcm_sframes_t (*delay)(काष्ठा snd_pcm_substream *,
		काष्ठा snd_soc_dai *);

	/* bit field */
	अचिन्हित पूर्णांक no_capture_mute:1;
पूर्ण;

काष्ठा snd_soc_cdai_ops अणु
	/*
	 * क्रम compress ops
	 */
	पूर्णांक (*startup)(काष्ठा snd_compr_stream *,
			काष्ठा snd_soc_dai *);
	पूर्णांक (*shutकरोwn)(काष्ठा snd_compr_stream *,
			काष्ठा snd_soc_dai *);
	पूर्णांक (*set_params)(काष्ठा snd_compr_stream *,
			काष्ठा snd_compr_params *, काष्ठा snd_soc_dai *);
	पूर्णांक (*get_params)(काष्ठा snd_compr_stream *,
			काष्ठा snd_codec *, काष्ठा snd_soc_dai *);
	पूर्णांक (*set_metadata)(काष्ठा snd_compr_stream *,
			काष्ठा snd_compr_metadata *, काष्ठा snd_soc_dai *);
	पूर्णांक (*get_metadata)(काष्ठा snd_compr_stream *,
			काष्ठा snd_compr_metadata *, काष्ठा snd_soc_dai *);
	पूर्णांक (*trigger)(काष्ठा snd_compr_stream *, पूर्णांक,
			काष्ठा snd_soc_dai *);
	पूर्णांक (*poपूर्णांकer)(काष्ठा snd_compr_stream *,
			काष्ठा snd_compr_tstamp *, काष्ठा snd_soc_dai *);
	पूर्णांक (*ack)(काष्ठा snd_compr_stream *, माप_प्रकार,
			काष्ठा snd_soc_dai *);
पूर्ण;

/*
 * Digital Audio Interface Driver.
 *
 * Describes the Digital Audio Interface in terms of its ALSA, DAI and AC97
 * operations and capabilities. Codec and platक्रमm drivers will रेजिस्टर this
 * काष्ठाure क्रम every DAI they have.
 *
 * This काष्ठाure covers the घड़ीing, क्रमmating and ALSA operations क्रम each
 * पूर्णांकerface.
 */
काष्ठा snd_soc_dai_driver अणु
	/* DAI description */
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक base;
	काष्ठा snd_soc_करोbj करोbj;

	/* DAI driver callbacks */
	पूर्णांक (*probe)(काष्ठा snd_soc_dai *dai);
	पूर्णांक (*हटाओ)(काष्ठा snd_soc_dai *dai);
	/* compress dai */
	पूर्णांक (*compress_new)(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक num);
	/* Optional Callback used at pcm creation*/
	पूर्णांक (*pcm_new)(काष्ठा snd_soc_pcm_runसमय *rtd,
		       काष्ठा snd_soc_dai *dai);

	/* ops */
	स्थिर काष्ठा snd_soc_dai_ops *ops;
	स्थिर काष्ठा snd_soc_cdai_ops *cops;

	/* DAI capabilities */
	काष्ठा snd_soc_pcm_stream capture;
	काष्ठा snd_soc_pcm_stream playback;
	अचिन्हित पूर्णांक symmetric_rate:1;
	अचिन्हित पूर्णांक symmetric_channels:1;
	अचिन्हित पूर्णांक symmetric_sample_bits:1;

	/* probe ordering - क्रम components with runसमय dependencies */
	पूर्णांक probe_order;
	पूर्णांक हटाओ_order;
पूर्ण;

/*
 * Digital Audio Interface runसमय data.
 *
 * Holds runसमय data क्रम a DAI.
 */
काष्ठा snd_soc_dai अणु
	स्थिर अक्षर *name;
	पूर्णांक id;
	काष्ठा device *dev;

	/* driver ops */
	काष्ठा snd_soc_dai_driver *driver;

	/* DAI runसमय info */
	अचिन्हित पूर्णांक stream_active[SNDRV_PCM_STREAM_LAST + 1]; /* usage count */

	काष्ठा snd_soc_dapm_widget *playback_widget;
	काष्ठा snd_soc_dapm_widget *capture_widget;

	/* DAI DMA data */
	व्योम *playback_dma_data;
	व्योम *capture_dma_data;

	/* Symmetry data - only valid अगर symmetry is being enक्रमced */
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक channels;
	अचिन्हित पूर्णांक sample_bits;

	/* parent platक्रमm/codec */
	काष्ठा snd_soc_component *component;

	/* CODEC TDM slot masks and params (क्रम fixup) */
	अचिन्हित पूर्णांक tx_mask;
	अचिन्हित पूर्णांक rx_mask;

	काष्ठा list_head list;

	/* function mark */
	काष्ठा snd_pcm_substream *mark_startup;
	काष्ठा snd_pcm_substream *mark_hw_params;
	काष्ठा snd_pcm_substream *mark_trigger;
	काष्ठा snd_compr_stream  *mark_compr_startup;

	/* bit field */
	अचिन्हित पूर्णांक probed:1;
पूर्ण;

अटल अंतरभूत काष्ठा snd_soc_pcm_stream *
snd_soc_dai_get_pcm_stream(स्थिर काष्ठा snd_soc_dai *dai, पूर्णांक stream)
अणु
	वापस (stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		&dai->driver->playback : &dai->driver->capture;
पूर्ण

अटल अंतरभूत
काष्ठा snd_soc_dapm_widget *snd_soc_dai_get_widget(
	काष्ठा snd_soc_dai *dai, पूर्णांक stream)
अणु
	वापस (stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		dai->playback_widget : dai->capture_widget;
पूर्ण

अटल अंतरभूत व्योम *snd_soc_dai_get_dma_data(स्थिर काष्ठा snd_soc_dai *dai,
					     स्थिर काष्ठा snd_pcm_substream *ss)
अणु
	वापस (ss->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		dai->playback_dma_data : dai->capture_dma_data;
पूर्ण

अटल अंतरभूत व्योम snd_soc_dai_set_dma_data(काष्ठा snd_soc_dai *dai,
					    स्थिर काष्ठा snd_pcm_substream *ss,
					    व्योम *data)
अणु
	अगर (ss->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dai->playback_dma_data = data;
	अन्यथा
		dai->capture_dma_data = data;
पूर्ण

अटल अंतरभूत व्योम snd_soc_dai_init_dma_data(काष्ठा snd_soc_dai *dai,
					     व्योम *playback, व्योम *capture)
अणु
	dai->playback_dma_data = playback;
	dai->capture_dma_data = capture;
पूर्ण

अटल अंतरभूत व्योम snd_soc_dai_set_drvdata(काष्ठा snd_soc_dai *dai,
		व्योम *data)
अणु
	dev_set_drvdata(dai->dev, data);
पूर्ण

अटल अंतरभूत व्योम *snd_soc_dai_get_drvdata(काष्ठा snd_soc_dai *dai)
अणु
	वापस dev_get_drvdata(dai->dev);
पूर्ण

/**
 * snd_soc_dai_set_sdw_stream() - Configures a DAI क्रम SDW stream operation
 * @dai: DAI
 * @stream: STREAM
 * @direction: Stream direction(Playback/Capture)
 * SoundWire subप्रणाली करोesn't have a notion of direction and we reuse
 * the ASoC stream direction to configure sink/source ports.
 * Playback maps to source ports and Capture क्रम sink ports.
 *
 * This should be invoked with शून्य to clear the stream set previously.
 * Returns 0 on success, a negative error code otherwise.
 */
अटल अंतरभूत पूर्णांक snd_soc_dai_set_sdw_stream(काष्ठा snd_soc_dai *dai,
				व्योम *stream, पूर्णांक direction)
अणु
	अगर (dai->driver->ops->set_sdw_stream)
		वापस dai->driver->ops->set_sdw_stream(dai, stream, direction);
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण

/**
 * snd_soc_dai_get_sdw_stream() - Retrieves SDW stream from DAI
 * @dai: DAI
 * @direction: Stream direction(Playback/Capture)
 *
 * This routine only retrieves that was previously configured
 * with snd_soc_dai_get_sdw_stream()
 *
 * Returns poपूर्णांकer to stream or an ERR_PTR value, e.g.
 * ERR_PTR(-ENOTSUPP) अगर callback is not supported;
 */
अटल अंतरभूत व्योम *snd_soc_dai_get_sdw_stream(काष्ठा snd_soc_dai *dai,
					       पूर्णांक direction)
अणु
	अगर (dai->driver->ops->get_sdw_stream)
		वापस dai->driver->ops->get_sdw_stream(dai, direction);
	अन्यथा
		वापस ERR_PTR(-ENOTSUPP);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
snd_soc_dai_stream_active(काष्ठा snd_soc_dai *dai, पूर्णांक stream)
अणु
	वापस dai->stream_active[stream];
पूर्ण

#पूर्ण_अगर
