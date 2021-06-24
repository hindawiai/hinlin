<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Arnaud Pouliquen <arnaud.pouliquen@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <sound/soc.h>

#समावेश "uniperif.h"

#घोषणा UNIPERIF_READER_I2S_IN 0 /* पढ़ोer id connected to I2S/TDM TX bus */
/*
 * Note: snd_pcm_hardware is linked to DMA controller but is declared here to
 * पूर्णांकegrate uniपढ़ोer capability in term of rate and supported channels
 */
अटल स्थिर काष्ठा snd_pcm_hardware uni_पढ़ोer_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE,

	.rates = SNDRV_PCM_RATE_CONTINUOUS,
	.rate_min = 8000,
	.rate_max = 96000,

	.channels_min = 2,
	.channels_max = 8,

	.periods_min = 2,
	.periods_max = 48,

	.period_bytes_min = 128,
	.period_bytes_max = 64 * PAGE_SIZE,
	.buffer_bytes_max = 256 * PAGE_SIZE
पूर्ण;

/*
 * uni_पढ़ोer_irq_handler
 * In हाल of error audio stream is stopped; stop action is रक्षित via PCM
 * stream lock  to aव्योम race condition with trigger callback.
 */
अटल irqवापस_t uni_पढ़ोer_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t ret = IRQ_NONE;
	काष्ठा uniperअगर *पढ़ोer = dev_id;
	अचिन्हित पूर्णांक status;

	spin_lock(&पढ़ोer->irq_lock);
	अगर (!पढ़ोer->substream)
		जाओ irq_spin_unlock;

	snd_pcm_stream_lock(पढ़ोer->substream);
	अगर (पढ़ोer->state == UNIPERIF_STATE_STOPPED) अणु
		/* Unexpected IRQ: करो nothing */
		dev_warn(पढ़ोer->dev, "unexpected IRQ\n");
		जाओ stream_unlock;
	पूर्ण

	/* Get पूर्णांकerrupt status & clear them immediately */
	status = GET_UNIPERIF_ITS(पढ़ोer);
	SET_UNIPERIF_ITS_BCLR(पढ़ोer, status);

	/* Check क्रम fअगरo overflow error */
	अगर (unlikely(status & UNIPERIF_ITS_FIFO_ERROR_MASK(पढ़ोer))) अणु
		dev_err(पढ़ोer->dev, "FIFO error detected\n");

		snd_pcm_stop_xrun(पढ़ोer->substream);

		ret = IRQ_HANDLED;
	पूर्ण

stream_unlock:
	snd_pcm_stream_unlock(पढ़ोer->substream);
irq_spin_unlock:
	spin_unlock(&पढ़ोer->irq_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक uni_पढ़ोer_prepare_pcm(काष्ठा snd_pcm_runसमय *runसमय,
				  काष्ठा uniperअगर *पढ़ोer)
अणु
	पूर्णांक slot_width;

	/* Force slot width to 32 in I2S mode */
	अगर ((पढ़ोer->daअगरmt & SND_SOC_DAIFMT_FORMAT_MASK)
		== SND_SOC_DAIFMT_I2S) अणु
		slot_width = 32;
	पूर्ण अन्यथा अणु
		चयन (runसमय->क्रमmat) अणु
		हाल SNDRV_PCM_FORMAT_S16_LE:
			slot_width = 16;
			अवरोध;
		शेष:
			slot_width = 32;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Number of bits per subframe (i.e one channel sample) on input. */
	चयन (slot_width) अणु
	हाल 32:
		SET_UNIPERIF_I2S_FMT_NBIT_32(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_DATA_SIZE_32(पढ़ोer);
		अवरोध;
	हाल 16:
		SET_UNIPERIF_I2S_FMT_NBIT_16(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_DATA_SIZE_16(पढ़ोer);
		अवरोध;
	शेष:
		dev_err(पढ़ोer->dev, "subframe format not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Configure data memory क्रमmat */
	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		/* One data word contains two samples */
		SET_UNIPERIF_CONFIG_MEM_FMT_16_16(पढ़ोer);
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S32_LE:
		/*
		 * Actually "16 bits/0 bits" means "32/28/24/20/18/16 bits
		 * on the MSB then zeros (अगर less than 32 bytes)"...
		 */
		SET_UNIPERIF_CONFIG_MEM_FMT_16_0(पढ़ोer);
		अवरोध;

	शेष:
		dev_err(पढ़ोer->dev, "format not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Number of channels must be even */
	अगर ((runसमय->channels % 2) || (runसमय->channels < 2) ||
	    (runसमय->channels > 10)) अणु
		dev_err(पढ़ोer->dev, "%s: invalid nb of channels\n", __func__);
		वापस -EINVAL;
	पूर्ण

	SET_UNIPERIF_I2S_FMT_NUM_CH(पढ़ोer, runसमय->channels / 2);
	SET_UNIPERIF_I2S_FMT_ORDER_MSB(पढ़ोer);

	वापस 0;
पूर्ण

अटल पूर्णांक uni_पढ़ोer_prepare_tdm(काष्ठा snd_pcm_runसमय *runसमय,
				  काष्ठा uniperअगर *पढ़ोer)
अणु
	पूर्णांक frame_size; /* user tdm frame size in bytes */
	/* शेष unip TDM_WORD_POS_X_Y */
	अचिन्हित पूर्णांक word_pos[4] = अणु
		0x04060002, 0x0C0E080A, 0x14161012, 0x1C1E181Aपूर्ण;

	frame_size = sti_uniperiph_get_user_frame_size(runसमय);

	/* fix 16/0 क्रमmat */
	SET_UNIPERIF_CONFIG_MEM_FMT_16_0(पढ़ोer);
	SET_UNIPERIF_I2S_FMT_DATA_SIZE_32(पढ़ोer);

	/* number of words inserted on the TDM line */
	SET_UNIPERIF_I2S_FMT_NUM_CH(पढ़ोer, frame_size / 4 / 2);

	SET_UNIPERIF_I2S_FMT_ORDER_MSB(पढ़ोer);
	SET_UNIPERIF_I2S_FMT_ALIGN_LEFT(पढ़ोer);
	SET_UNIPERIF_TDM_ENABLE_TDM_ENABLE(पढ़ोer);

	/*
	 * set the बारlots allocation क्रम words in FIFO
	 *
	 * HW bug: (LSB word < MSB word) => this config is not possible
	 *         So अगर we want (LSB word < MSB) word, then it shall be
	 *         handled by user
	 */
	sti_uniperiph_get_tdm_word_pos(पढ़ोer, word_pos);
	SET_UNIPERIF_TDM_WORD_POS(पढ़ोer, 1_2, word_pos[WORD_1_2]);
	SET_UNIPERIF_TDM_WORD_POS(पढ़ोer, 3_4, word_pos[WORD_3_4]);
	SET_UNIPERIF_TDM_WORD_POS(पढ़ोer, 5_6, word_pos[WORD_5_6]);
	SET_UNIPERIF_TDM_WORD_POS(पढ़ोer, 7_8, word_pos[WORD_7_8]);

	वापस 0;
पूर्ण

अटल पूर्णांक uni_पढ़ोer_prepare(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *पढ़ोer = priv->dai_data.uni;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक transfer_size, trigger_limit, ret;

	/* The पढ़ोer should be stopped */
	अगर (पढ़ोer->state != UNIPERIF_STATE_STOPPED) अणु
		dev_err(पढ़ोer->dev, "%s: invalid reader state %d\n", __func__,
			पढ़ोer->state);
		वापस -EINVAL;
	पूर्ण

	/* Calculate transfer size (in fअगरo cells and bytes) क्रम frame count */
	अगर (पढ़ोer->type == SND_ST_UNIPERIF_TYPE_TDM) अणु
		/* transfer size = unip frame size (in 32 bits FIFO cell) */
		transfer_size =
			sti_uniperiph_get_user_frame_size(runसमय) / 4;
	पूर्ण अन्यथा अणु
		transfer_size = runसमय->channels * UNIPERIF_FIFO_FRAMES;
	पूर्ण

	/* Calculate number of empty cells available beक्रमe निश्चितing DREQ */
	अगर (पढ़ोer->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0)
		trigger_limit = UNIPERIF_FIFO_SIZE - transfer_size;
	अन्यथा
		/*
		 * Since SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0
		 * FDMA_TRIGGER_LIMIT also controls when the state चयनes
		 * from OFF or STANDBY to AUDIO DATA.
		 */
		trigger_limit = transfer_size;

	/* Trigger limit must be an even number */
	अगर ((!trigger_limit % 2) ||
	    (trigger_limit != 1 && transfer_size % 2) ||
	    (trigger_limit > UNIPERIF_CONFIG_DMA_TRIG_LIMIT_MASK(पढ़ोer))) अणु
		dev_err(पढ़ोer->dev, "invalid trigger limit %d\n",
			trigger_limit);
		वापस -EINVAL;
	पूर्ण

	SET_UNIPERIF_CONFIG_DMA_TRIG_LIMIT(पढ़ोer, trigger_limit);

	अगर (UNIPERIF_TYPE_IS_TDM(पढ़ोer))
		ret = uni_पढ़ोer_prepare_tdm(runसमय, पढ़ोer);
	अन्यथा
		ret = uni_पढ़ोer_prepare_pcm(runसमय, पढ़ोer);
	अगर (ret)
		वापस ret;

	चयन (पढ़ोer->daअगरmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		SET_UNIPERIF_I2S_FMT_ALIGN_LEFT(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_PADDING_I2S_MODE(पढ़ोer);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		SET_UNIPERIF_I2S_FMT_ALIGN_LEFT(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_PADDING_SONY_MODE(पढ़ोer);
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		SET_UNIPERIF_I2S_FMT_ALIGN_RIGHT(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_PADDING_SONY_MODE(पढ़ोer);
		अवरोध;
	शेष:
		dev_err(पढ़ोer->dev, "format not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Data घड़ीing (changing) on the rising/falling edge */
	चयन (पढ़ोer->daअगरmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		SET_UNIPERIF_I2S_FMT_LR_POL_LOW(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_RISING(पढ़ोer);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		SET_UNIPERIF_I2S_FMT_LR_POL_HIG(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_RISING(पढ़ोer);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		SET_UNIPERIF_I2S_FMT_LR_POL_LOW(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_FALLING(पढ़ोer);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		SET_UNIPERIF_I2S_FMT_LR_POL_HIG(पढ़ोer);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_FALLING(पढ़ोer);
		अवरोध;
	पूर्ण

	/* Clear any pending पूर्णांकerrupts */
	SET_UNIPERIF_ITS_BCLR(पढ़ोer, GET_UNIPERIF_ITS(पढ़ोer));

	SET_UNIPERIF_I2S_FMT_NO_OF_SAMPLES_TO_READ(पढ़ोer, 0);

	/* Set the पूर्णांकerrupt mask */
	SET_UNIPERIF_ITM_BSET_DMA_ERROR(पढ़ोer);
	SET_UNIPERIF_ITM_BSET_FIFO_ERROR(पढ़ोer);
	SET_UNIPERIF_ITM_BSET_MEM_BLK_READ(पढ़ोer);

	/* Enable underflow recovery पूर्णांकerrupts */
	अगर (पढ़ोer->underflow_enabled) अणु
		SET_UNIPERIF_ITM_BSET_UNDERFLOW_REC_DONE(पढ़ोer);
		SET_UNIPERIF_ITM_BSET_UNDERFLOW_REC_FAILED(पढ़ोer);
	पूर्ण

	/* Reset uniperipheral पढ़ोer */
	वापस sti_uniperiph_reset(पढ़ोer);
पूर्ण

अटल पूर्णांक uni_पढ़ोer_start(काष्ठा uniperअगर *पढ़ोer)
अणु
	/* The पढ़ोer should be stopped */
	अगर (पढ़ोer->state != UNIPERIF_STATE_STOPPED) अणु
		dev_err(पढ़ोer->dev, "%s: invalid reader state\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Enable पढ़ोer पूर्णांकerrupts (and clear possible stalled ones) */
	SET_UNIPERIF_ITS_BCLR_FIFO_ERROR(पढ़ोer);
	SET_UNIPERIF_ITM_BSET_FIFO_ERROR(पढ़ोer);

	/* Launch the पढ़ोer */
	SET_UNIPERIF_CTRL_OPERATION_PCM_DATA(पढ़ोer);

	/* Update state to started */
	पढ़ोer->state = UNIPERIF_STATE_STARTED;
	वापस 0;
पूर्ण

अटल पूर्णांक uni_पढ़ोer_stop(काष्ठा uniperअगर *पढ़ोer)
अणु
	/* The पढ़ोer should not be in stopped state */
	अगर (पढ़ोer->state == UNIPERIF_STATE_STOPPED) अणु
		dev_err(पढ़ोer->dev, "%s: invalid reader state\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Turn the पढ़ोer off */
	SET_UNIPERIF_CTRL_OPERATION_OFF(पढ़ोer);

	/* Disable पूर्णांकerrupts */
	SET_UNIPERIF_ITM_BCLR(पढ़ोer, GET_UNIPERIF_ITM(पढ़ोer));

	/* Update state to stopped and वापस */
	पढ़ोer->state = UNIPERIF_STATE_STOPPED;

	वापस 0;
पूर्ण

अटल पूर्णांक  uni_पढ़ोer_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *पढ़ोer = priv->dai_data.uni;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		वापस  uni_पढ़ोer_start(पढ़ोer);
	हाल SNDRV_PCM_TRIGGER_STOP:
		वापस  uni_पढ़ोer_stop(पढ़ोer);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक uni_पढ़ोer_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *पढ़ोer = priv->dai_data.uni;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&पढ़ोer->irq_lock, flags);
	पढ़ोer->substream = substream;
	spin_unlock_irqrestore(&पढ़ोer->irq_lock, flags);

	अगर (!UNIPERIF_TYPE_IS_TDM(पढ़ोer))
		वापस 0;

	/* refine hw स्थिरraपूर्णांक in tdm mode */
	ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  sti_uniperiph_fix_tdm_chan,
				  पढ़ोer, SNDRV_PCM_HW_PARAM_CHANNELS,
				  -1);
	अगर (ret < 0)
		वापस ret;

	वापस snd_pcm_hw_rule_add(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_FORMAT,
				   sti_uniperiph_fix_tdm_क्रमmat,
				   पढ़ोer, SNDRV_PCM_HW_PARAM_FORMAT,
				   -1);
पूर्ण

अटल व्योम uni_पढ़ोer_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *पढ़ोer = priv->dai_data.uni;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पढ़ोer->irq_lock, flags);
	अगर (पढ़ोer->state != UNIPERIF_STATE_STOPPED) अणु
		/* Stop the पढ़ोer */
		uni_पढ़ोer_stop(पढ़ोer);
	पूर्ण
	पढ़ोer->substream = शून्य;
	spin_unlock_irqrestore(&पढ़ोer->irq_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops uni_पढ़ोer_dai_ops = अणु
		.startup = uni_पढ़ोer_startup,
		.shutकरोwn = uni_पढ़ोer_shutकरोwn,
		.prepare = uni_पढ़ोer_prepare,
		.trigger = uni_पढ़ोer_trigger,
		.hw_params = sti_uniperiph_dai_hw_params,
		.set_fmt = sti_uniperiph_dai_set_fmt,
		.set_tdm_slot = sti_uniperiph_set_tdm_slot
पूर्ण;

पूर्णांक uni_पढ़ोer_init(काष्ठा platक्रमm_device *pdev,
		    काष्ठा uniperअगर *पढ़ोer)
अणु
	पूर्णांक ret = 0;

	पढ़ोer->dev = &pdev->dev;
	पढ़ोer->state = UNIPERIF_STATE_STOPPED;
	पढ़ोer->dai_ops = &uni_पढ़ोer_dai_ops;

	अगर (UNIPERIF_TYPE_IS_TDM(पढ़ोer))
		पढ़ोer->hw = &uni_tdm_hw;
	अन्यथा
		पढ़ोer->hw = &uni_पढ़ोer_pcm_hw;

	ret = devm_request_irq(&pdev->dev, पढ़ोer->irq,
			       uni_पढ़ोer_irq_handler, IRQF_SHARED,
			       dev_name(&pdev->dev), पढ़ोer);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		वापस -EBUSY;
	पूर्ण

	spin_lock_init(&पढ़ोer->irq_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uni_पढ़ोer_init);
