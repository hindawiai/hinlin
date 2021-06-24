<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Arnaud Pouliquen <arnaud.pouliquen@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <sound/asoundef.h>
#समावेश <sound/soc.h>

#समावेश "uniperif.h"

/*
 * Some hardware-related definitions
 */

/* sys config रेजिस्टरs definitions */
#घोषणा SYS_CFG_AUDIO_GLUE 0xA4

/*
 * Driver specअगरic types.
 */

#घोषणा UNIPERIF_PLAYER_CLK_ADJ_MIN  -999999
#घोषणा UNIPERIF_PLAYER_CLK_ADJ_MAX  1000000
#घोषणा UNIPERIF_PLAYER_I2S_OUT 1 /* player id connected to I2S/TDM TX bus */

/*
 * Note: snd_pcm_hardware is linked to DMA controller but is declared here to
 * पूर्णांकegrate  DAI_CPU capability in term of rate and supported channels
 */
अटल स्थिर काष्ठा snd_pcm_hardware uni_player_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID,
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE,

	.rates = SNDRV_PCM_RATE_CONTINUOUS,
	.rate_min = 8000,
	.rate_max = 192000,

	.channels_min = 2,
	.channels_max = 8,

	.periods_min = 2,
	.periods_max = 48,

	.period_bytes_min = 128,
	.period_bytes_max = 64 * PAGE_SIZE,
	.buffer_bytes_max = 256 * PAGE_SIZE
पूर्ण;

/*
 * uni_player_irq_handler
 * In हाल of error audio stream is stopped; stop action is रक्षित via PCM
 * stream lock to aव्योम race condition with trigger callback.
 */
अटल irqवापस_t uni_player_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t ret = IRQ_NONE;
	काष्ठा uniperअगर *player = dev_id;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक पंचांगp;

	spin_lock(&player->irq_lock);
	अगर (!player->substream)
		जाओ irq_spin_unlock;

	snd_pcm_stream_lock(player->substream);
	अगर (player->state == UNIPERIF_STATE_STOPPED)
		जाओ stream_unlock;

	/* Get पूर्णांकerrupt status & clear them immediately */
	status = GET_UNIPERIF_ITS(player);
	SET_UNIPERIF_ITS_BCLR(player, status);

	/* Check क्रम fअगरo error (underrun) */
	अगर (unlikely(status & UNIPERIF_ITS_FIFO_ERROR_MASK(player))) अणु
		dev_err(player->dev, "FIFO underflow error detected\n");

		/* Interrupt is just क्रम inक्रमmation when underflow recovery */
		अगर (player->underflow_enabled) अणु
			/* Update state to underflow */
			player->state = UNIPERIF_STATE_UNDERFLOW;

		पूर्ण अन्यथा अणु
			/* Disable पूर्णांकerrupt so करोesn't continually fire */
			SET_UNIPERIF_ITM_BCLR_FIFO_ERROR(player);

			/* Stop the player */
			snd_pcm_stop_xrun(player->substream);
		पूर्ण

		ret = IRQ_HANDLED;
	पूर्ण

	/* Check क्रम dma error (overrun) */
	अगर (unlikely(status & UNIPERIF_ITS_DMA_ERROR_MASK(player))) अणु
		dev_err(player->dev, "DMA error detected\n");

		/* Disable पूर्णांकerrupt so करोesn't continually fire */
		SET_UNIPERIF_ITM_BCLR_DMA_ERROR(player);

		/* Stop the player */
		snd_pcm_stop_xrun(player->substream);

		ret = IRQ_HANDLED;
	पूर्ण

	/* Check क्रम underflow recovery करोne */
	अगर (unlikely(status & UNIPERIF_ITM_UNDERFLOW_REC_DONE_MASK(player))) अणु
		अगर (!player->underflow_enabled) अणु
			dev_err(player->dev,
				"unexpected Underflow recovering\n");
			ret = -EPERM;
			जाओ stream_unlock;
		पूर्ण
		/* Read the underflow recovery duration */
		पंचांगp = GET_UNIPERIF_STATUS_1_UNDERFLOW_DURATION(player);
		dev_dbg(player->dev, "Underflow recovered (%d LR clocks max)\n",
			पंचांगp);

		/* Clear the underflow recovery duration */
		SET_UNIPERIF_BIT_CONTROL_CLR_UNDERFLOW_DURATION(player);

		/* Update state to started */
		player->state = UNIPERIF_STATE_STARTED;

		ret = IRQ_HANDLED;
	पूर्ण

	/* Check अगर underflow recovery failed */
	अगर (unlikely(status &
		     UNIPERIF_ITM_UNDERFLOW_REC_FAILED_MASK(player))) अणु
		dev_err(player->dev, "Underflow recovery failed\n");

		/* Stop the player */
		snd_pcm_stop_xrun(player->substream);

		ret = IRQ_HANDLED;
	पूर्ण

stream_unlock:
	snd_pcm_stream_unlock(player->substream);
irq_spin_unlock:
	spin_unlock(&player->irq_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक uni_player_clk_set_rate(काष्ठा uniperअगर *player, अचिन्हित दीर्घ rate)
अणु
	पूर्णांक rate_adjusted, rate_achieved, delta, ret;
	पूर्णांक adjusपंचांगent = player->clk_adj;

	/*
	 *             a
	 * F = f + --------- * f = f + d
	 *          1000000
	 *
	 *         a
	 * d = --------- * f
	 *      1000000
	 *
	 * where:
	 *   f - nominal rate
	 *   a - adjusपंचांगent in ppm (parts per milion)
	 *   F - rate to be set in synthesizer
	 *   d - delta (dअगरference) between f and F
	 */
	अगर (adjusपंचांगent < 0) अणु
		/* भाग64_64 operates on अचिन्हित values... */
		delta = -1;
		adjusपंचांगent = -adjusपंचांगent;
	पूर्ण अन्यथा अणु
		delta = 1;
	पूर्ण
	/* 500000 ppm is 0.5, which is used to round up values */
	delta *= (पूर्णांक)भाग64_u64((uपूर्णांक64_t)rate *
				(uपूर्णांक64_t)adjusपंचांगent + 500000, 1000000);
	rate_adjusted = rate + delta;

	/* Adjusted rate should never be == 0 */
	अगर (!rate_adjusted)
		वापस -EINVAL;

	ret = clk_set_rate(player->clk, rate_adjusted);
	अगर (ret < 0)
		वापस ret;

	rate_achieved = clk_get_rate(player->clk);
	अगर (!rate_achieved)
		/* If value is 0 means that घड़ी or parent not valid */
		वापस -EINVAL;

	/*
	 * Using ALSA's adjusपंचांगent control, we can modअगरy the rate to be up
	 * to twice as much as requested, but no more
	 */
	delta = rate_achieved - rate;
	अगर (delta < 0) अणु
		/* भाग64_64 operates on अचिन्हित values... */
		delta = -delta;
		adjusपंचांगent = -1;
	पूर्ण अन्यथा अणु
		adjusपंचांगent = 1;
	पूर्ण
	/* Frequency/2 is added to round up result */
	adjusपंचांगent *= (पूर्णांक)भाग64_u64((uपूर्णांक64_t)delta * 1000000 + rate / 2,
				     rate);
	player->clk_adj = adjusपंचांगent;
	वापस 0;
पूर्ण

अटल व्योम uni_player_set_channel_status(काष्ठा uniperअगर *player,
					  काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक n;
	अचिन्हित पूर्णांक status;

	/*
	 * Some AVRs and TVs require the channel status to contain a correct
	 * sampling frequency. If no sample rate is alपढ़ोy specअगरied, then
	 * set one.
	 */
	अगर (runसमय) अणु
		चयन (runसमय->rate) अणु
		हाल 22050:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_22050;
			अवरोध;
		हाल 44100:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_44100;
			अवरोध;
		हाल 88200:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_88200;
			अवरोध;
		हाल 176400:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_176400;
			अवरोध;
		हाल 24000:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_24000;
			अवरोध;
		हाल 48000:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_48000;
			अवरोध;
		हाल 96000:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_96000;
			अवरोध;
		हाल 192000:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_192000;
			अवरोध;
		हाल 32000:
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_32000;
			अवरोध;
		शेष:
			/* Mark as sampling frequency not indicated */
			player->stream_settings.iec958.status[3] =
						IEC958_AES3_CON_FS_NOTID;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Audio mode:
	 * Use audio mode status to select PCM or encoded mode
	 */
	अगर (player->stream_settings.iec958.status[0] & IEC958_AES0_NONAUDIO)
		player->stream_settings.encoding_mode =
			UNIPERIF_IEC958_ENCODING_MODE_ENCODED;
	अन्यथा
		player->stream_settings.encoding_mode =
			UNIPERIF_IEC958_ENCODING_MODE_PCM;

	अगर (player->stream_settings.encoding_mode ==
		UNIPERIF_IEC958_ENCODING_MODE_PCM)
		/* Clear user validity bits */
		SET_UNIPERIF_USER_VALIDITY_VALIDITY_LR(player, 0);
	अन्यथा
		/* Set user validity bits */
		SET_UNIPERIF_USER_VALIDITY_VALIDITY_LR(player, 1);

	/* Program the new channel status */
	क्रम (n = 0; n < 6; ++n) अणु
		status  =
		player->stream_settings.iec958.status[0 + (n * 4)] & 0xf;
		status |=
		player->stream_settings.iec958.status[1 + (n * 4)] << 8;
		status |=
		player->stream_settings.iec958.status[2 + (n * 4)] << 16;
		status |=
		player->stream_settings.iec958.status[3 + (n * 4)] << 24;
		SET_UNIPERIF_CHANNEL_STA_REGN(player, n, status);
	पूर्ण

	/* Update the channel status */
	अगर (player->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0)
		SET_UNIPERIF_CONFIG_CHL_STS_UPDATE(player);
	अन्यथा
		SET_UNIPERIF_BIT_CONTROL_CHL_STS_UPDATE(player);
पूर्ण

अटल पूर्णांक uni_player_prepare_iec958(काष्ठा uniperअगर *player,
				     काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक clk_भाग;

	clk_भाग = player->mclk / runसमय->rate;

	/* Oversampling must be multiple of 128 as iec958 frame is 32-bits */
	अगर ((clk_भाग % 128) || (clk_भाग <= 0)) अणु
		dev_err(player->dev, "%s: invalid clk_div %d\n",
			__func__, clk_भाग);
		वापस -EINVAL;
	पूर्ण

	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		/* 16/16 memory क्रमmat */
		SET_UNIPERIF_CONFIG_MEM_FMT_16_16(player);
		/* 16-bits per sub-frame */
		SET_UNIPERIF_I2S_FMT_NBIT_32(player);
		/* Set 16-bit sample precision */
		SET_UNIPERIF_I2S_FMT_DATA_SIZE_16(player);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		/* 16/0 memory क्रमmat */
		SET_UNIPERIF_CONFIG_MEM_FMT_16_0(player);
		/* 32-bits per sub-frame */
		SET_UNIPERIF_I2S_FMT_NBIT_32(player);
		/* Set 24-bit sample precision */
		SET_UNIPERIF_I2S_FMT_DATA_SIZE_24(player);
		अवरोध;
	शेष:
		dev_err(player->dev, "format not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Set parity to be calculated by the hardware */
	SET_UNIPERIF_CONFIG_PARITY_CNTR_BY_HW(player);

	/* Set channel status bits to be inserted by the hardware */
	SET_UNIPERIF_CONFIG_CHANNEL_STA_CNTR_BY_HW(player);

	/* Set user data bits to be inserted by the hardware */
	SET_UNIPERIF_CONFIG_USER_DAT_CNTR_BY_HW(player);

	/* Set validity bits to be inserted by the hardware */
	SET_UNIPERIF_CONFIG_VALIDITY_DAT_CNTR_BY_HW(player);

	/* Set full software control to disabled */
	SET_UNIPERIF_CONFIG_SPDIF_SW_CTRL_DISABLE(player);

	SET_UNIPERIF_CTRL_ZERO_STUFF_HW(player);

	mutex_lock(&player->ctrl_lock);
	/* Update the channel status */
	uni_player_set_channel_status(player, runसमय);
	mutex_unlock(&player->ctrl_lock);

	/* Clear the user validity user bits */
	SET_UNIPERIF_USER_VALIDITY_VALIDITY_LR(player, 0);

	/* Disable one-bit audio mode */
	SET_UNIPERIF_CONFIG_ONE_BIT_AUD_DISABLE(player);

	/* Enable consecutive frames repetition of Z preamble (not क्रम HBRA) */
	SET_UNIPERIF_CONFIG_REPEAT_CHL_STS_ENABLE(player);

	/* Change to SUF0_SUBF1 and left/right channels swap! */
	SET_UNIPERIF_CONFIG_SUBFRAME_SEL_SUBF1_SUBF0(player);

	/* Set data output as MSB first */
	SET_UNIPERIF_I2S_FMT_ORDER_MSB(player);

	अगर (player->stream_settings.encoding_mode ==
				UNIPERIF_IEC958_ENCODING_MODE_ENCODED)
		SET_UNIPERIF_CTRL_EXIT_STBY_ON_EOBLOCK_ON(player);
	अन्यथा
		SET_UNIPERIF_CTRL_EXIT_STBY_ON_EOBLOCK_OFF(player);

	SET_UNIPERIF_I2S_FMT_NUM_CH(player, runसमय->channels / 2);

	/* Set rounding to off */
	SET_UNIPERIF_CTRL_ROUNDING_OFF(player);

	/* Set घड़ी भागisor */
	SET_UNIPERIF_CTRL_DIVIDER(player, clk_भाग / 128);

	/* Set the spdअगर latency to not रुको beक्रमe starting player */
	SET_UNIPERIF_CTRL_SPDIF_LAT_OFF(player);

	/*
	 * Ensure iec958 क्रमmatting is off. It will be enabled in function
	 * uni_player_start() at the same समय as the operation
	 * mode is set to work around a silicon issue.
	 */
	अगर (player->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0)
		SET_UNIPERIF_CTRL_SPDIF_FMT_OFF(player);
	अन्यथा
		SET_UNIPERIF_CTRL_SPDIF_FMT_ON(player);

	वापस 0;
पूर्ण

अटल पूर्णांक uni_player_prepare_pcm(काष्ठा uniperअगर *player,
				  काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक output_frame_size, slot_width, clk_भाग;

	/* Force slot width to 32 in I2S mode (HW स्थिरraपूर्णांक) */
	अगर ((player->daअगरmt & SND_SOC_DAIFMT_FORMAT_MASK) ==
		SND_SOC_DAIFMT_I2S)
		slot_width = 32;
	अन्यथा
		slot_width = snd_pcm_क्रमmat_width(runसमय->क्रमmat);

	output_frame_size = slot_width * runसमय->channels;

	clk_भाग = player->mclk / runसमय->rate;
	/*
	 * For 32 bits subframe clk_भाग must be a multiple of 128,
	 * क्रम 16 bits must be a multiple of 64
	 */
	अगर ((slot_width == 32) && (clk_भाग % 128)) अणु
		dev_err(player->dev, "%s: invalid clk_div\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर ((slot_width == 16) && (clk_भाग % 64)) अणु
		dev_err(player->dev, "%s: invalid clk_div\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Number of bits per subframe (which is one channel sample)
	 * on output - Transfer 16 or 32 bits from FIFO
	 */
	चयन (slot_width) अणु
	हाल 32:
		SET_UNIPERIF_I2S_FMT_NBIT_32(player);
		SET_UNIPERIF_I2S_FMT_DATA_SIZE_32(player);
		अवरोध;
	हाल 16:
		SET_UNIPERIF_I2S_FMT_NBIT_16(player);
		SET_UNIPERIF_I2S_FMT_DATA_SIZE_16(player);
		अवरोध;
	शेष:
		dev_err(player->dev, "subframe format not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Configure data memory क्रमmat */
	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		/* One data word contains two samples */
		SET_UNIPERIF_CONFIG_MEM_FMT_16_16(player);
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S32_LE:
		/*
		 * Actually "16 bits/0 bits" means "32/28/24/20/18/16 bits
		 * on the left than zeros (अगर less than 32 bytes)"... ;-)
		 */
		SET_UNIPERIF_CONFIG_MEM_FMT_16_0(player);
		अवरोध;

	शेष:
		dev_err(player->dev, "format not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Set rounding to off */
	SET_UNIPERIF_CTRL_ROUNDING_OFF(player);

	/* Set घड़ी भागisor */
	SET_UNIPERIF_CTRL_DIVIDER(player, clk_भाग / (2 * output_frame_size));

	/* Number of channelsmust be even*/
	अगर ((runसमय->channels % 2) || (runसमय->channels < 2) ||
	    (runसमय->channels > 10)) अणु
		dev_err(player->dev, "%s: invalid nb of channels\n", __func__);
		वापस -EINVAL;
	पूर्ण

	SET_UNIPERIF_I2S_FMT_NUM_CH(player, runसमय->channels / 2);

	/* Set 1-bit audio क्रमmat to disabled */
	SET_UNIPERIF_CONFIG_ONE_BIT_AUD_DISABLE(player);

	SET_UNIPERIF_I2S_FMT_ORDER_MSB(player);

	/* No iec958 क्रमmatting as outputting to DAC  */
	SET_UNIPERIF_CTRL_SPDIF_FMT_OFF(player);

	वापस 0;
पूर्ण

अटल पूर्णांक uni_player_prepare_tdm(काष्ठा uniperअगर *player,
				  काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक tdm_frame_size; /* unip tdm frame size in bytes */
	पूर्णांक user_frame_size; /* user tdm frame size in bytes */
	/* शेष unip TDM_WORD_POS_X_Y */
	अचिन्हित पूर्णांक word_pos[4] = अणु
		0x04060002, 0x0C0E080A, 0x14161012, 0x1C1E181Aपूर्ण;
	पूर्णांक freq, ret;

	tdm_frame_size =
		sti_uniperiph_get_unip_tdm_frame_size(player);
	user_frame_size =
		sti_uniperiph_get_user_frame_size(runसमय);

	/* fix 16/0 क्रमmat */
	SET_UNIPERIF_CONFIG_MEM_FMT_16_0(player);
	SET_UNIPERIF_I2S_FMT_DATA_SIZE_32(player);

	/* number of words inserted on the TDM line */
	SET_UNIPERIF_I2S_FMT_NUM_CH(player, user_frame_size / 4 / 2);

	SET_UNIPERIF_I2S_FMT_ORDER_MSB(player);
	SET_UNIPERIF_I2S_FMT_ALIGN_LEFT(player);

	/* Enable the tdm functionality */
	SET_UNIPERIF_TDM_ENABLE_TDM_ENABLE(player);

	/* number of 8 bits बारlots avail in unip tdm frame */
	SET_UNIPERIF_TDM_FS_REF_DIV_NUM_TIMESLOT(player, tdm_frame_size);

	/* set the बारlot allocation क्रम words in FIFO */
	sti_uniperiph_get_tdm_word_pos(player, word_pos);
	SET_UNIPERIF_TDM_WORD_POS(player, 1_2, word_pos[WORD_1_2]);
	SET_UNIPERIF_TDM_WORD_POS(player, 3_4, word_pos[WORD_3_4]);
	SET_UNIPERIF_TDM_WORD_POS(player, 5_6, word_pos[WORD_5_6]);
	SET_UNIPERIF_TDM_WORD_POS(player, 7_8, word_pos[WORD_7_8]);

	/* set unip clk rate (not करोne vai set_sysclk ops) */
	freq = runसमय->rate * tdm_frame_size * 8;
	mutex_lock(&player->ctrl_lock);
	ret = uni_player_clk_set_rate(player, freq);
	अगर (!ret)
		player->mclk = freq;
	mutex_unlock(&player->ctrl_lock);

	वापस 0;
पूर्ण

/*
 * ALSA uniperipheral iec958 controls
 */
अटल पूर्णांक  uni_player_ctl_iec958_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक uni_player_ctl_iec958_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;
	काष्ठा snd_aes_iec958 *iec958 = &player->stream_settings.iec958;

	mutex_lock(&player->ctrl_lock);
	ucontrol->value.iec958.status[0] = iec958->status[0];
	ucontrol->value.iec958.status[1] = iec958->status[1];
	ucontrol->value.iec958.status[2] = iec958->status[2];
	ucontrol->value.iec958.status[3] = iec958->status[3];
	mutex_unlock(&player->ctrl_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक uni_player_ctl_iec958_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;
	काष्ठा snd_aes_iec958 *iec958 =  &player->stream_settings.iec958;
	अचिन्हित दीर्घ flags;

	mutex_lock(&player->ctrl_lock);
	iec958->status[0] = ucontrol->value.iec958.status[0];
	iec958->status[1] = ucontrol->value.iec958.status[1];
	iec958->status[2] = ucontrol->value.iec958.status[2];
	iec958->status[3] = ucontrol->value.iec958.status[3];

	spin_lock_irqsave(&player->irq_lock, flags);
	अगर (player->substream && player->substream->runसमय)
		uni_player_set_channel_status(player,
					      player->substream->runसमय);
	अन्यथा
		uni_player_set_channel_status(player, शून्य);

	spin_unlock_irqrestore(&player->irq_lock, flags);
	mutex_unlock(&player->ctrl_lock);

	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new uni_player_iec958_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
	.info = uni_player_ctl_iec958_info,
	.get = uni_player_ctl_iec958_get,
	.put = uni_player_ctl_iec958_put,
पूर्ण;

/*
 * uniperअगर rate adjustement control
 */
अटल पूर्णांक snd_sti_clk_adjusपंचांगent_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = UNIPERIF_PLAYER_CLK_ADJ_MIN;
	uinfo->value.पूर्णांकeger.max = UNIPERIF_PLAYER_CLK_ADJ_MAX;
	uinfo->value.पूर्णांकeger.step = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sti_clk_adjusपंचांगent_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;

	mutex_lock(&player->ctrl_lock);
	ucontrol->value.पूर्णांकeger.value[0] = player->clk_adj;
	mutex_unlock(&player->ctrl_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_sti_clk_adjusपंचांगent_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *dai = snd_kcontrol_chip(kcontrol);
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;
	पूर्णांक ret = 0;

	अगर ((ucontrol->value.पूर्णांकeger.value[0] < UNIPERIF_PLAYER_CLK_ADJ_MIN) ||
	    (ucontrol->value.पूर्णांकeger.value[0] > UNIPERIF_PLAYER_CLK_ADJ_MAX))
		वापस -EINVAL;

	mutex_lock(&player->ctrl_lock);
	player->clk_adj = ucontrol->value.पूर्णांकeger.value[0];

	अगर (player->mclk)
		ret = uni_player_clk_set_rate(player, player->mclk);
	mutex_unlock(&player->ctrl_lock);

	वापस ret;
पूर्ण

अटल काष्ठा snd_kcontrol_new uni_player_clk_adj_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "PCM Playback Oversampling Freq. Adjustment",
	.info = snd_sti_clk_adjusपंचांगent_info,
	.get = snd_sti_clk_adjusपंचांगent_get,
	.put = snd_sti_clk_adjusपंचांगent_put,
पूर्ण;

अटल काष्ठा snd_kcontrol_new *snd_sti_pcm_ctl[] = अणु
	&uni_player_clk_adj_ctl,
पूर्ण;

अटल काष्ठा snd_kcontrol_new *snd_sti_iec_ctl[] = अणु
	&uni_player_iec958_ctl,
	&uni_player_clk_adj_ctl,
पूर्ण;

अटल पूर्णांक uni_player_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&player->irq_lock, flags);
	player->substream = substream;
	spin_unlock_irqrestore(&player->irq_lock, flags);

	player->clk_adj = 0;

	अगर (!UNIPERIF_TYPE_IS_TDM(player))
		वापस 0;

	/* refine hw स्थिरraपूर्णांक in tdm mode */
	ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  sti_uniperiph_fix_tdm_chan,
				  player, SNDRV_PCM_HW_PARAM_CHANNELS,
				  -1);
	अगर (ret < 0)
		वापस ret;

	वापस snd_pcm_hw_rule_add(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_FORMAT,
				   sti_uniperiph_fix_tdm_क्रमmat,
				   player, SNDRV_PCM_HW_PARAM_FORMAT,
				   -1);
पूर्ण

अटल पूर्णांक uni_player_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				 अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;
	पूर्णांक ret;

	अगर (UNIPERIF_TYPE_IS_TDM(player) || (dir == SND_SOC_CLOCK_IN))
		वापस 0;

	अगर (clk_id != 0)
		वापस -EINVAL;

	mutex_lock(&player->ctrl_lock);
	ret = uni_player_clk_set_rate(player, freq);
	अगर (!ret)
		player->mclk = freq;
	mutex_unlock(&player->ctrl_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक uni_player_prepare(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक transfer_size, trigger_limit;
	पूर्णांक ret;

	/* The player should be stopped */
	अगर (player->state != UNIPERIF_STATE_STOPPED) अणु
		dev_err(player->dev, "%s: invalid player state %d\n", __func__,
			player->state);
		वापस -EINVAL;
	पूर्ण

	/* Calculate transfer size (in fअगरo cells and bytes) क्रम frame count */
	अगर (player->type == SND_ST_UNIPERIF_TYPE_TDM) अणु
		/* transfer size = user frame size (in 32 bits FIFO cell) */
		transfer_size =
			sti_uniperiph_get_user_frame_size(runसमय) / 4;
	पूर्ण अन्यथा अणु
		transfer_size = runसमय->channels * UNIPERIF_FIFO_FRAMES;
	पूर्ण

	/* Calculate number of empty cells available beक्रमe निश्चितing DREQ */
	अगर (player->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0) अणु
		trigger_limit = UNIPERIF_FIFO_SIZE - transfer_size;
	पूर्ण अन्यथा अणु
		/*
		 * Since SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0
		 * FDMA_TRIGGER_LIMIT also controls when the state चयनes
		 * from OFF or STANDBY to AUDIO DATA.
		 */
		trigger_limit = transfer_size;
	पूर्ण

	/* Trigger limit must be an even number */
	अगर ((!trigger_limit % 2) || (trigger_limit != 1 && transfer_size % 2) ||
	    (trigger_limit > UNIPERIF_CONFIG_DMA_TRIG_LIMIT_MASK(player))) अणु
		dev_err(player->dev, "invalid trigger limit %d\n",
			trigger_limit);
		वापस -EINVAL;
	पूर्ण

	SET_UNIPERIF_CONFIG_DMA_TRIG_LIMIT(player, trigger_limit);

	/* Uniperipheral setup depends on player type */
	चयन (player->type) अणु
	हाल SND_ST_UNIPERIF_TYPE_HDMI:
		ret = uni_player_prepare_iec958(player, runसमय);
		अवरोध;
	हाल SND_ST_UNIPERIF_TYPE_PCM:
		ret = uni_player_prepare_pcm(player, runसमय);
		अवरोध;
	हाल SND_ST_UNIPERIF_TYPE_SPDIF:
		ret = uni_player_prepare_iec958(player, runसमय);
		अवरोध;
	हाल SND_ST_UNIPERIF_TYPE_TDM:
		ret = uni_player_prepare_tdm(player, runसमय);
		अवरोध;
	शेष:
		dev_err(player->dev, "invalid player type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	चयन (player->daअगरmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		SET_UNIPERIF_I2S_FMT_LR_POL_LOW(player);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_RISING(player);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		SET_UNIPERIF_I2S_FMT_LR_POL_HIG(player);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_RISING(player);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		SET_UNIPERIF_I2S_FMT_LR_POL_LOW(player);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_FALLING(player);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		SET_UNIPERIF_I2S_FMT_LR_POL_HIG(player);
		SET_UNIPERIF_I2S_FMT_SCLK_EDGE_FALLING(player);
		अवरोध;
	पूर्ण

	चयन (player->daअगरmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		SET_UNIPERIF_I2S_FMT_ALIGN_LEFT(player);
		SET_UNIPERIF_I2S_FMT_PADDING_I2S_MODE(player);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		SET_UNIPERIF_I2S_FMT_ALIGN_LEFT(player);
		SET_UNIPERIF_I2S_FMT_PADDING_SONY_MODE(player);
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		SET_UNIPERIF_I2S_FMT_ALIGN_RIGHT(player);
		SET_UNIPERIF_I2S_FMT_PADDING_SONY_MODE(player);
		अवरोध;
	शेष:
		dev_err(player->dev, "format not supported\n");
		वापस -EINVAL;
	पूर्ण

	SET_UNIPERIF_I2S_FMT_NO_OF_SAMPLES_TO_READ(player, 0);


	वापस sti_uniperiph_reset(player);
पूर्ण

अटल पूर्णांक uni_player_start(काष्ठा uniperअगर *player)
अणु
	पूर्णांक ret;

	/* The player should be stopped */
	अगर (player->state != UNIPERIF_STATE_STOPPED) अणु
		dev_err(player->dev, "%s: invalid player state\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ret = clk_prepare_enable(player->clk);
	अगर (ret) अणु
		dev_err(player->dev, "%s: Failed to enable clock\n", __func__);
		वापस ret;
	पूर्ण

	/* Clear any pending पूर्णांकerrupts */
	SET_UNIPERIF_ITS_BCLR(player, GET_UNIPERIF_ITS(player));

	/* Set the पूर्णांकerrupt mask */
	SET_UNIPERIF_ITM_BSET_DMA_ERROR(player);
	SET_UNIPERIF_ITM_BSET_FIFO_ERROR(player);

	/* Enable underflow recovery पूर्णांकerrupts */
	अगर (player->underflow_enabled) अणु
		SET_UNIPERIF_ITM_BSET_UNDERFLOW_REC_DONE(player);
		SET_UNIPERIF_ITM_BSET_UNDERFLOW_REC_FAILED(player);
	पूर्ण

	ret = sti_uniperiph_reset(player);
	अगर (ret < 0) अणु
		clk_disable_unprepare(player->clk);
		वापस ret;
	पूर्ण

	/*
	 * Does not use IEC61937 features of the uniperipheral hardware.
	 * Instead it perक्रमms IEC61937 in software and inserts it directly
	 * पूर्णांकo the audio data stream. As such, when encoded mode is selected,
	 * linear pcm mode is still used, but with the dअगरferences of the
	 * channel status bits set क्रम encoded mode and the validity bits set.
	 */
	SET_UNIPERIF_CTRL_OPERATION_PCM_DATA(player);

	/*
	 * If iec958 क्रमmatting is required क्रम hdmi or spdअगर, then it must be
	 * enabled after the operation mode is set. If set prior to this, it
	 * will not take affect and hang the player.
	 */
	अगर (player->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0)
		अगर (UNIPERIF_TYPE_IS_IEC958(player))
			SET_UNIPERIF_CTRL_SPDIF_FMT_ON(player);

	/* Force channel status update (no update अगर clk disable) */
	अगर (player->ver < SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0)
		SET_UNIPERIF_CONFIG_CHL_STS_UPDATE(player);
	अन्यथा
		SET_UNIPERIF_BIT_CONTROL_CHL_STS_UPDATE(player);

	/* Update state to started */
	player->state = UNIPERIF_STATE_STARTED;

	वापस 0;
पूर्ण

अटल पूर्णांक uni_player_stop(काष्ठा uniperअगर *player)
अणु
	पूर्णांक ret;

	/* The player should not be in stopped state */
	अगर (player->state == UNIPERIF_STATE_STOPPED) अणु
		dev_err(player->dev, "%s: invalid player state\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Turn the player off */
	SET_UNIPERIF_CTRL_OPERATION_OFF(player);

	ret = sti_uniperiph_reset(player);
	अगर (ret < 0)
		वापस ret;

	/* Disable पूर्णांकerrupts */
	SET_UNIPERIF_ITM_BCLR(player, GET_UNIPERIF_ITM(player));

	/* Disable घड़ी */
	clk_disable_unprepare(player->clk);

	/* Update state to stopped and वापस */
	player->state = UNIPERIF_STATE_STOPPED;

	वापस 0;
पूर्ण

पूर्णांक uni_player_resume(काष्ठा uniperअगर *player)
अणु
	पूर्णांक ret;

	/* Select the frequency synthesizer घड़ी */
	अगर (player->clk_sel) अणु
		ret = regmap_field_ग_लिखो(player->clk_sel, 1);
		अगर (ret) अणु
			dev_err(player->dev,
				"%s: Failed to select freq synth clock\n",
				__func__);
			वापस ret;
		पूर्ण
	पूर्ण

	SET_UNIPERIF_CONFIG_BACK_STALL_REQ_DISABLE(player);
	SET_UNIPERIF_CTRL_ROUNDING_OFF(player);
	SET_UNIPERIF_CTRL_SPDIF_LAT_OFF(player);
	SET_UNIPERIF_CONFIG_IDLE_MOD_DISABLE(player);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uni_player_resume);

अटल पूर्णांक uni_player_trigger(काष्ठा snd_pcm_substream *substream,
			      पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		वापस uni_player_start(player);
	हाल SNDRV_PCM_TRIGGER_STOP:
		वापस uni_player_stop(player);
	हाल SNDRV_PCM_TRIGGER_RESUME:
		वापस uni_player_resume(player);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम uni_player_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sti_uniperiph_data *priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा uniperअगर *player = priv->dai_data.uni;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&player->irq_lock, flags);
	अगर (player->state != UNIPERIF_STATE_STOPPED)
		/* Stop the player */
		uni_player_stop(player);

	player->substream = शून्य;
	spin_unlock_irqrestore(&player->irq_lock, flags);
पूर्ण

अटल पूर्णांक uni_player_parse_dt_audio_glue(काष्ठा platक्रमm_device *pdev,
					  काष्ठा uniperअगर *player)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा regmap *regmap;
	काष्ठा reg_field regfield[2] = अणु
		/* PCM_CLK_SEL */
		REG_FIELD(SYS_CFG_AUDIO_GLUE,
			  8 + player->id,
			  8 + player->id),
		/* PCMP_VALID_SEL */
		REG_FIELD(SYS_CFG_AUDIO_GLUE, 0, 1)
	पूर्ण;

	regmap = syscon_regmap_lookup_by_phandle(node, "st,syscfg");

	अगर (IS_ERR(regmap)) अणु
		dev_err(&pdev->dev, "sti-audio-clk-glue syscf not found\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	player->clk_sel = regmap_field_alloc(regmap, regfield[0]);
	player->valid_sel = regmap_field_alloc(regmap, regfield[1]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops uni_player_dai_ops = अणु
		.startup = uni_player_startup,
		.shutकरोwn = uni_player_shutकरोwn,
		.prepare = uni_player_prepare,
		.trigger = uni_player_trigger,
		.hw_params = sti_uniperiph_dai_hw_params,
		.set_fmt = sti_uniperiph_dai_set_fmt,
		.set_sysclk = uni_player_set_sysclk,
		.set_tdm_slot = sti_uniperiph_set_tdm_slot
पूर्ण;

पूर्णांक uni_player_init(काष्ठा platक्रमm_device *pdev,
		    काष्ठा uniperअगर *player)
अणु
	पूर्णांक ret = 0;

	player->dev = &pdev->dev;
	player->state = UNIPERIF_STATE_STOPPED;
	player->dai_ops = &uni_player_dai_ops;

	/* Get PCM_CLK_SEL & PCMP_VALID_SEL from audio-glue-ctrl SoC reg */
	ret = uni_player_parse_dt_audio_glue(pdev, player);

	अगर (ret < 0) अणु
		dev_err(player->dev, "Failed to parse DeviceTree\n");
		वापस ret;
	पूर्ण

	/* Underflow recovery is only supported on later ip revisions */
	अगर (player->ver >= SND_ST_UNIPERIF_VERSION_UNI_PLR_TOP_1_0)
		player->underflow_enabled = 1;

	अगर (UNIPERIF_TYPE_IS_TDM(player))
		player->hw = &uni_tdm_hw;
	अन्यथा
		player->hw = &uni_player_pcm_hw;

	/* Get uniperअगर resource */
	player->clk = of_clk_get(pdev->dev.of_node, 0);
	अगर (IS_ERR(player->clk)) अणु
		dev_err(player->dev, "Failed to get clock\n");
		वापस PTR_ERR(player->clk);
	पूर्ण

	/* Select the frequency synthesizer घड़ी */
	अगर (player->clk_sel) अणु
		ret = regmap_field_ग_लिखो(player->clk_sel, 1);
		अगर (ret) अणु
			dev_err(player->dev,
				"%s: Failed to select freq synth clock\n",
				__func__);
			वापस ret;
		पूर्ण
	पूर्ण

	/* connect to I2S/TDM TX bus */
	अगर (player->valid_sel &&
	    (player->id == UNIPERIF_PLAYER_I2S_OUT)) अणु
		ret = regmap_field_ग_लिखो(player->valid_sel, player->id);
		अगर (ret) अणु
			dev_err(player->dev,
				"%s: unable to connect to tdm bus\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_request_irq(&pdev->dev, player->irq,
			       uni_player_irq_handler, IRQF_SHARED,
			       dev_name(&pdev->dev), player);
	अगर (ret < 0) अणु
		dev_err(player->dev, "unable to request IRQ %d\n", player->irq);
		वापस ret;
	पूर्ण

	mutex_init(&player->ctrl_lock);
	spin_lock_init(&player->irq_lock);

	/* Ensure that disabled by शेष */
	SET_UNIPERIF_CONFIG_BACK_STALL_REQ_DISABLE(player);
	SET_UNIPERIF_CTRL_ROUNDING_OFF(player);
	SET_UNIPERIF_CTRL_SPDIF_LAT_OFF(player);
	SET_UNIPERIF_CONFIG_IDLE_MOD_DISABLE(player);

	अगर (UNIPERIF_TYPE_IS_IEC958(player)) अणु
		/* Set शेष iec958 status bits  */

		/* Consumer, PCM, copyright, 2ch, mode 0 */
		player->stream_settings.iec958.status[0] = 0x00;
		/* Broadcast reception category */
		player->stream_settings.iec958.status[1] =
					IEC958_AES1_CON_GENERAL;
		/* Do not take पूर्णांकo account source or channel number */
		player->stream_settings.iec958.status[2] =
					IEC958_AES2_CON_SOURCE_UNSPEC;
		/* Sampling frequency not indicated */
		player->stream_settings.iec958.status[3] =
					IEC958_AES3_CON_FS_NOTID;
		/* Max sample word 24-bit, sample word length not indicated */
		player->stream_settings.iec958.status[4] =
					IEC958_AES4_CON_MAX_WORDLEN_24 |
					IEC958_AES4_CON_WORDLEN_24_20;

		player->num_ctrls = ARRAY_SIZE(snd_sti_iec_ctl);
		player->snd_ctrls = snd_sti_iec_ctl[0];
	पूर्ण अन्यथा अणु
		player->num_ctrls = ARRAY_SIZE(snd_sti_pcm_ctl);
		player->snd_ctrls = snd_sti_pcm_ctl[0];
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(uni_player_init);
