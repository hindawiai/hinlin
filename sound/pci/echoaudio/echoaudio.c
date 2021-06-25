<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ALSA driver क्रम Echoaudio soundcards.
 *  Copyright (C) 2003-2004 Giuliano Pochini <pochini@shiny.it>
 *  Copyright (C) 2020 Mark Hills <mark@xwax.org>
 */

#समावेश <linux/module.h>

MODULE_AUTHOR("Giuliano Pochini <pochini@shiny.it>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Echoaudio " ECHOCARD_NAME " soundcards driver");
MODULE_DEVICE_TABLE(pci, snd_echo_ids);

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " ECHOCARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " ECHOCARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " ECHOCARD_NAME " soundcard.");

अटल स्थिर अचिन्हित पूर्णांक channels_list[10] = अणु1, 2, 4, 6, 8, 10, 12, 14, 16, 999999पूर्ण;
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_output_gain, -12800, 100, 1);



अटल पूर्णांक get_firmware(स्थिर काष्ठा firmware **fw_entry,
			काष्ठा echoaudio *chip, स्थिर लघु fw_index)
अणु
	पूर्णांक err;
	अक्षर name[30];

#अगर_घोषित CONFIG_PM_SLEEP
	अगर (chip->fw_cache[fw_index]) अणु
		dev_dbg(chip->card->dev,
			"firmware requested: %s is cached\n",
			card_fw[fw_index].data);
		*fw_entry = chip->fw_cache[fw_index];
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	dev_dbg(chip->card->dev,
		"firmware requested: %s\n", card_fw[fw_index].data);
	snम_लिखो(name, माप(name), "ea/%s", card_fw[fw_index].data);
	err = request_firmware(fw_entry, name, &chip->pci->dev);
	अगर (err < 0)
		dev_err(chip->card->dev,
			"get_firmware(): Firmware not available (%d)\n", err);
#अगर_घोषित CONFIG_PM_SLEEP
	अन्यथा
		chip->fw_cache[fw_index] = *fw_entry;
#पूर्ण_अगर
	वापस err;
पूर्ण



अटल व्योम मुक्त_firmware(स्थिर काष्ठा firmware *fw_entry,
			  काष्ठा echoaudio *chip)
अणु
#अगर_घोषित CONFIG_PM_SLEEP
	dev_dbg(chip->card->dev, "firmware not released (kept in cache)\n");
#अन्यथा
	release_firmware(fw_entry);
#पूर्ण_अगर
पूर्ण



अटल व्योम मुक्त_firmware_cache(काष्ठा echoaudio *chip)
अणु
#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक i;

	क्रम (i = 0; i < 8 ; i++)
		अगर (chip->fw_cache[i]) अणु
			release_firmware(chip->fw_cache[i]);
			dev_dbg(chip->card->dev, "release_firmware(%d)\n", i);
		पूर्ण

#पूर्ण_अगर
पूर्ण



/******************************************************************************
	PCM पूर्णांकerface
******************************************************************************/

अटल व्योम audiopipe_मुक्त(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा audiopipe *pipe = runसमय->निजी_data;

	अगर (pipe->sgpage.area)
		snd_dma_मुक्त_pages(&pipe->sgpage);
	kमुक्त(pipe);
पूर्ण



अटल पूर्णांक hw_rule_capture_क्रमmat_by_channels(काष्ठा snd_pcm_hw_params *params,
					      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
						   SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *f = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_mask fmt;

	snd_mask_any(&fmt);

#अगर_अघोषित ECHOCARD_HAS_STEREO_BIG_ENDIAN32
	/* >=2 channels cannot be S32_BE */
	अगर (c->min == 2) अणु
		fmt.bits[0] &= ~SNDRV_PCM_FMTBIT_S32_BE;
		वापस snd_mask_refine(f, &fmt);
	पूर्ण
#पूर्ण_अगर
	/* > 2 channels cannot be U8 and S32_BE */
	अगर (c->min > 2) अणु
		fmt.bits[0] &= ~(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S32_BE);
		वापस snd_mask_refine(f, &fmt);
	पूर्ण
	/* Mono is ok with any क्रमmat */
	वापस 0;
पूर्ण



अटल पूर्णांक hw_rule_capture_channels_by_क्रमmat(काष्ठा snd_pcm_hw_params *params,
					      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
						   SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *f = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_पूर्णांकerval ch;

	snd_पूर्णांकerval_any(&ch);

	/* S32_BE is mono (and stereo) only */
	अगर (f->bits[0] == SNDRV_PCM_FMTBIT_S32_BE) अणु
		ch.min = 1;
#अगर_घोषित ECHOCARD_HAS_STEREO_BIG_ENDIAN32
		ch.max = 2;
#अन्यथा
		ch.max = 1;
#पूर्ण_अगर
		ch.पूर्णांकeger = 1;
		वापस snd_पूर्णांकerval_refine(c, &ch);
	पूर्ण
	/* U8 can be only mono or stereo */
	अगर (f->bits[0] == SNDRV_PCM_FMTBIT_U8) अणु
		ch.min = 1;
		ch.max = 2;
		ch.पूर्णांकeger = 1;
		वापस snd_पूर्णांकerval_refine(c, &ch);
	पूर्ण
	/* S16_LE, S24_3LE and S32_LE support any number of channels. */
	वापस 0;
पूर्ण



अटल पूर्णांक hw_rule_playback_क्रमmat_by_channels(काष्ठा snd_pcm_hw_params *params,
					       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
						   SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *f = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_mask fmt;
	u64 fmask;
	snd_mask_any(&fmt);

	fmask = fmt.bits[0] + ((u64)fmt.bits[1] << 32);

	/* >2 channels must be S16_LE, S24_3LE or S32_LE */
	अगर (c->min > 2) अणु
		fmask &= SNDRV_PCM_FMTBIT_S16_LE |
			 SNDRV_PCM_FMTBIT_S24_3LE |
			 SNDRV_PCM_FMTBIT_S32_LE;
	/* 1 channel must be S32_BE or S32_LE */
	पूर्ण अन्यथा अगर (c->max == 1)
		fmask &= SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE;
#अगर_अघोषित ECHOCARD_HAS_STEREO_BIG_ENDIAN32
	/* 2 channels cannot be S32_BE */
	अन्यथा अगर (c->min == 2 && c->max == 2)
		fmask &= ~SNDRV_PCM_FMTBIT_S32_BE;
#पूर्ण_अगर
	अन्यथा
		वापस 0;

	fmt.bits[0] &= (u32)fmask;
	fmt.bits[1] &= (u32)(fmask >> 32);
	वापस snd_mask_refine(f, &fmt);
पूर्ण



अटल पूर्णांक hw_rule_playback_channels_by_क्रमmat(काष्ठा snd_pcm_hw_params *params,
					       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
						   SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *f = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_पूर्णांकerval ch;
	u64 fmask;

	snd_पूर्णांकerval_any(&ch);
	ch.पूर्णांकeger = 1;
	fmask = f->bits[0] + ((u64)f->bits[1] << 32);

	/* S32_BE is mono (and stereo) only */
	अगर (fmask == SNDRV_PCM_FMTBIT_S32_BE) अणु
		ch.min = 1;
#अगर_घोषित ECHOCARD_HAS_STEREO_BIG_ENDIAN32
		ch.max = 2;
#अन्यथा
		ch.max = 1;
#पूर्ण_अगर
	/* U8 is stereo only */
	पूर्ण अन्यथा अगर (fmask == SNDRV_PCM_FMTBIT_U8)
		ch.min = ch.max = 2;
	/* S16_LE and S24_3LE must be at least stereo */
	अन्यथा अगर (!(fmask & ~(SNDRV_PCM_FMTBIT_S16_LE |
			       SNDRV_PCM_FMTBIT_S24_3LE)))
		ch.min = 2;
	अन्यथा
		वापस 0;

	वापस snd_पूर्णांकerval_refine(c, &ch);
पूर्ण



/* Since the sample rate is a global setting, करो allow the user to change the
sample rate only अगर there is only one pcm device खोलो. */
अटल पूर्णांक hw_rule_sample_rate(काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
						      SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा echoaudio *chip = rule->निजी;
	काष्ठा snd_पूर्णांकerval fixed;
	पूर्णांक err;

	mutex_lock(&chip->mode_mutex);

	अगर (chip->can_set_rate) अणु
		err = 0;
	पूर्ण अन्यथा अणु
		snd_पूर्णांकerval_any(&fixed);
		fixed.min = fixed.max = chip->sample_rate;
		err = snd_पूर्णांकerval_refine(rate, &fixed);
	पूर्ण

	mutex_unlock(&chip->mode_mutex);
	वापस err;
पूर्ण


अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream,
		    चिन्हित अक्षर max_channels)
अणु
	काष्ठा echoaudio *chip;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा audiopipe *pipe;
	पूर्णांक err, i;

	अगर (max_channels <= 0)
		वापस -EAGAIN;

	chip = snd_pcm_substream_chip(substream);
	runसमय = substream->runसमय;

	pipe = kzalloc(माप(काष्ठा audiopipe), GFP_KERNEL);
	अगर (!pipe)
		वापस -ENOMEM;
	pipe->index = -1;		/* Not configured yet */

	/* Set up hw capabilities and contraपूर्णांकs */
	स_नकल(&pipe->hw, &pcm_hardware_skel, माप(काष्ठा snd_pcm_hardware));
	dev_dbg(chip->card->dev, "max_channels=%d\n", max_channels);
	pipe->स्थिरr.list = channels_list;
	pipe->स्थिरr.mask = 0;
	क्रम (i = 0; channels_list[i] <= max_channels; i++);
	pipe->स्थिरr.count = i;
	अगर (pipe->hw.channels_max > max_channels)
		pipe->hw.channels_max = max_channels;
	अगर (chip->digital_mode == DIGITAL_MODE_ADAT) अणु
		pipe->hw.rate_max = 48000;
		pipe->hw.rates &= SNDRV_PCM_RATE_8000_48000;
	पूर्ण

	runसमय->hw = pipe->hw;
	runसमय->निजी_data = pipe;
	runसमय->निजी_मुक्त = audiopipe_मुक्त;
	snd_pcm_set_sync(substream);

	/* Only mono and any even number of channels are allowed */
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					      SNDRV_PCM_HW_PARAM_CHANNELS,
					      &pipe->स्थिरr)) < 0)
		वापस err;

	/* All periods should have the same size */
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
						 SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;

	/* The hw accesses memory in chunks 32 frames दीर्घ and they should be
	32-bytes-aligned. It's not a requirement, but it seems that IRQs are
	generated with a resolution of 32 frames. Thus we need the following */
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					      SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					      32)) < 0)
		वापस err;
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					      SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					      32)) < 0)
		वापस err;

	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_RATE,
					hw_rule_sample_rate, chip,
				       SNDRV_PCM_HW_PARAM_RATE, -1)) < 0)
		वापस err;

	/* Allocate a page क्रम the scatter-gather list */
	अगर ((err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev,
				       PAGE_SIZE, &pipe->sgpage)) < 0) अणु
		dev_err(chip->card->dev, "s-g list allocation failed\n");
		वापस err;
	पूर्ण

	/*
	 * Sole ownership required to set the rate
	 */

	dev_dbg(chip->card->dev, "pcm_open opencount=%d can_set_rate=%d, rate_set=%d",
		chip->खोलोcount, chip->can_set_rate, chip->rate_set);

	chip->खोलोcount++;
	अगर (chip->खोलोcount > 1 && chip->rate_set)
		chip->can_set_rate = 0;

	वापस 0;
पूर्ण



अटल पूर्णांक pcm_analog_in_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	अगर ((err = pcm_खोलो(substream, num_analog_busses_in(chip) -
			    substream->number)) < 0)
		वापस err;
	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_CHANNELS,
				       hw_rule_capture_channels_by_क्रमmat, शून्य,
				       SNDRV_PCM_HW_PARAM_FORMAT, -1)) < 0)
		वापस err;
	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_FORMAT,
				       hw_rule_capture_क्रमmat_by_channels, शून्य,
				       SNDRV_PCM_HW_PARAM_CHANNELS, -1)) < 0)
		वापस err;

	वापस 0;
पूर्ण



अटल पूर्णांक pcm_analog_out_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);
	पूर्णांक max_channels, err;

#अगर_घोषित ECHOCARD_HAS_VMIXER
	max_channels = num_pipes_out(chip);
#अन्यथा
	max_channels = num_analog_busses_out(chip);
#पूर्ण_अगर
	अगर ((err = pcm_खोलो(substream, max_channels - substream->number)) < 0)
		वापस err;
	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_CHANNELS,
				       hw_rule_playback_channels_by_क्रमmat,
				       शून्य,
				       SNDRV_PCM_HW_PARAM_FORMAT, -1)) < 0)
		वापस err;
	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_FORMAT,
				       hw_rule_playback_क्रमmat_by_channels,
				       शून्य,
				       SNDRV_PCM_HW_PARAM_CHANNELS, -1)) < 0)
		वापस err;

	वापस 0;
पूर्ण



#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO

अटल पूर्णांक pcm_digital_in_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err, max_channels;

	max_channels = num_digital_busses_in(chip) - substream->number;
	mutex_lock(&chip->mode_mutex);
	अगर (chip->digital_mode == DIGITAL_MODE_ADAT)
		err = pcm_खोलो(substream, max_channels);
	अन्यथा	/* If the card has ADAT, subtract the 6 channels
		 * that S/PDIF करोesn't have
		 */
		err = pcm_खोलो(substream, max_channels - ECHOCARD_HAS_ADAT);

	अगर (err < 0)
		जाओ din_निकास;

	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_CHANNELS,
				       hw_rule_capture_channels_by_क्रमmat, शून्य,
				       SNDRV_PCM_HW_PARAM_FORMAT, -1)) < 0)
		जाओ din_निकास;
	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_FORMAT,
				       hw_rule_capture_क्रमmat_by_channels, शून्य,
				       SNDRV_PCM_HW_PARAM_CHANNELS, -1)) < 0)
		जाओ din_निकास;

din_निकास:
	mutex_unlock(&chip->mode_mutex);
	वापस err;
पूर्ण



#अगर_अघोषित ECHOCARD_HAS_VMIXER	/* See the note in snd_echo_new_pcm() */

अटल पूर्णांक pcm_digital_out_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err, max_channels;

	max_channels = num_digital_busses_out(chip) - substream->number;
	mutex_lock(&chip->mode_mutex);
	अगर (chip->digital_mode == DIGITAL_MODE_ADAT)
		err = pcm_खोलो(substream, max_channels);
	अन्यथा	/* If the card has ADAT, subtract the 6 channels
		 * that S/PDIF करोesn't have
		 */
		err = pcm_खोलो(substream, max_channels - ECHOCARD_HAS_ADAT);

	अगर (err < 0)
		जाओ करोut_निकास;

	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_CHANNELS,
				       hw_rule_playback_channels_by_क्रमmat,
				       शून्य, SNDRV_PCM_HW_PARAM_FORMAT,
				       -1)) < 0)
		जाओ करोut_निकास;
	अगर ((err = snd_pcm_hw_rule_add(substream->runसमय, 0,
				       SNDRV_PCM_HW_PARAM_FORMAT,
				       hw_rule_playback_क्रमmat_by_channels,
				       शून्य, SNDRV_PCM_HW_PARAM_CHANNELS,
				       -1)) < 0)
		जाओ करोut_निकास;

करोut_निकास:
	mutex_unlock(&chip->mode_mutex);
	वापस err;
पूर्ण

#पूर्ण_अगर /* !ECHOCARD_HAS_VMIXER */

#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_IO */



अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);

	/* Nothing to करो here. Audio is alपढ़ोy off and pipe will be
	 * मुक्तd by its callback
	 */

	mutex_lock(&chip->mode_mutex);

	dev_dbg(chip->card->dev, "pcm_open opencount=%d can_set_rate=%d, rate_set=%d",
		chip->खोलोcount, chip->can_set_rate, chip->rate_set);

	chip->खोलोcount--;

	चयन (chip->खोलोcount) अणु
	हाल 1:
		chip->can_set_rate = 1;
		अवरोध;

	हाल 0:
		chip->rate_set = 0;
		अवरोध;
	पूर्ण

	mutex_unlock(&chip->mode_mutex);
	वापस 0;
पूर्ण



/* Channel allocation and scatter-gather list setup */
अटल पूर्णांक init_engine(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_pcm_hw_params *hw_params,
		       पूर्णांक pipe_index, पूर्णांक पूर्णांकerleave)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक err, per, rest, page, edge, offs;
	काष्ठा audiopipe *pipe;

	chip = snd_pcm_substream_chip(substream);
	pipe = (काष्ठा audiopipe *) substream->runसमय->निजी_data;

	/* Sets up che hardware. If it's alपढ़ोy initialized, reset and
	 * reकरो with the new parameters
	 */
	spin_lock_irq(&chip->lock);
	अगर (pipe->index >= 0) अणु
		dev_dbg(chip->card->dev, "hwp_ie free(%d)\n", pipe->index);
		err = मुक्त_pipes(chip, pipe);
		snd_BUG_ON(err);
		chip->substream[pipe->index] = शून्य;
	पूर्ण

	err = allocate_pipes(chip, pipe, pipe_index, पूर्णांकerleave);
	अगर (err < 0) अणु
		spin_unlock_irq(&chip->lock);
		dev_err(chip->card->dev, "allocate_pipes(%d) err=%d\n",
			pipe_index, err);
		वापस err;
	पूर्ण
	spin_unlock_irq(&chip->lock);
	dev_dbg(chip->card->dev, "allocate_pipes()=%d\n", pipe_index);

	dev_dbg(chip->card->dev,
		"pcm_hw_params (bufsize=%dB periods=%d persize=%dB)\n",
		params_buffer_bytes(hw_params), params_periods(hw_params),
		params_period_bytes(hw_params));

	sglist_init(chip, pipe);
	edge = PAGE_SIZE;
	क्रम (offs = page = per = 0; offs < params_buffer_bytes(hw_params);
	     per++) अणु
		rest = params_period_bytes(hw_params);
		अगर (offs + rest > params_buffer_bytes(hw_params))
			rest = params_buffer_bytes(hw_params) - offs;
		जबतक (rest) अणु
			dma_addr_t addr;
			addr = snd_pcm_sgbuf_get_addr(substream, offs);
			अगर (rest <= edge - offs) अणु
				sglist_add_mapping(chip, pipe, addr, rest);
				sglist_add_irq(chip, pipe);
				offs += rest;
				rest = 0;
			पूर्ण अन्यथा अणु
				sglist_add_mapping(chip, pipe, addr,
						   edge - offs);
				rest -= edge - offs;
				offs = edge;
			पूर्ण
			अगर (offs == edge) अणु
				edge += PAGE_SIZE;
				page++;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Close the ring buffer */
	sglist_wrap(chip, pipe);

	/* This stuff is used by the irq handler, so it must be
	 * initialized beक्रमe chip->substream
	 */
	pipe->last_period = 0;
	pipe->last_counter = 0;
	pipe->position = 0;
	smp_wmb();
	chip->substream[pipe_index] = substream;
	chip->rate_set = 1;
	spin_lock_irq(&chip->lock);
	set_sample_rate(chip, hw_params->rate_num / hw_params->rate_den);
	spin_unlock_irq(&chip->lock);
	वापस 0;
पूर्ण



अटल पूर्णांक pcm_analog_in_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);

	वापस init_engine(substream, hw_params, px_analog_in(chip) +
			substream->number, params_channels(hw_params));
पूर्ण



अटल पूर्णांक pcm_analog_out_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	वापस init_engine(substream, hw_params, substream->number,
			   params_channels(hw_params));
पूर्ण



#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO

अटल पूर्णांक pcm_digital_in_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);

	वापस init_engine(substream, hw_params, px_digital_in(chip) +
			substream->number, params_channels(hw_params));
पूर्ण



#अगर_अघोषित ECHOCARD_HAS_VMIXER	/* See the note in snd_echo_new_pcm() */
अटल पूर्णांक pcm_digital_out_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);

	वापस init_engine(substream, hw_params, px_digital_out(chip) +
			substream->number, params_channels(hw_params));
पूर्ण
#पूर्ण_अगर /* !ECHOCARD_HAS_VMIXER */

#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_IO */



अटल पूर्णांक pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा echoaudio *chip;
	काष्ठा audiopipe *pipe;

	chip = snd_pcm_substream_chip(substream);
	pipe = (काष्ठा audiopipe *) substream->runसमय->निजी_data;

	spin_lock_irq(&chip->lock);
	अगर (pipe->index >= 0) अणु
		dev_dbg(chip->card->dev, "pcm_hw_free(%d)\n", pipe->index);
		मुक्त_pipes(chip, pipe);
		chip->substream[pipe->index] = शून्य;
		pipe->index = -1;
	पूर्ण
	spin_unlock_irq(&chip->lock);

	वापस 0;
पूर्ण



अटल पूर्णांक pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audioक्रमmat क्रमmat;
	पूर्णांक pipe_index = ((काष्ठा audiopipe *)runसमय->निजी_data)->index;

	dev_dbg(chip->card->dev, "Prepare rate=%d format=%d channels=%d\n",
		runसमय->rate, runसमय->क्रमmat, runसमय->channels);
	क्रमmat.पूर्णांकerleave = runसमय->channels;
	क्रमmat.data_are_bigendian = 0;
	क्रमmat.mono_to_stereo = 0;
	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_U8:
		क्रमmat.bits_per_sample = 8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		क्रमmat.bits_per_sample = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		क्रमmat.bits_per_sample = 24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_BE:
		क्रमmat.data_are_bigendian = 1;
		fallthrough;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		क्रमmat.bits_per_sample = 32;
		अवरोध;
	शेष:
		dev_err(chip->card->dev,
			"Prepare error: unsupported format %d\n",
			runसमय->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (snd_BUG_ON(pipe_index >= px_num(chip)))
		वापस -EINVAL;

	/*
	 * We passed checks we can करो independently; now take
	 * exclusive control
	 */

	spin_lock_irq(&chip->lock);

	अगर (snd_BUG_ON(!is_pipe_allocated(chip, pipe_index))) अणु
		spin_unlock_irq(&chip->lock);
		वापस -EINVAL;
	पूर्ण

	set_audio_क्रमmat(chip, pipe_index, &क्रमmat);
	spin_unlock_irq(&chip->lock);

	वापस 0;
पूर्ण



अटल पूर्णांक pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा echoaudio *chip = snd_pcm_substream_chip(substream);
	काष्ठा audiopipe *pipe;
	पूर्णांक i, err;
	u32 channelmask = 0;
	काष्ठा snd_pcm_substream *s;

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		क्रम (i = 0; i < DSP_MAXPIPES; i++) अणु
			अगर (s == chip->substream[i]) अणु
				channelmask |= 1 << i;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock(&chip->lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		क्रम (i = 0; i < DSP_MAXPIPES; i++) अणु
			अगर (channelmask & (1 << i)) अणु
				pipe = chip->substream[i]->runसमय->निजी_data;
				चयन (pipe->state) अणु
				हाल PIPE_STATE_STOPPED:
					pipe->last_period = 0;
					pipe->last_counter = 0;
					pipe->position = 0;
					*pipe->dma_counter = 0;
					fallthrough;
				हाल PIPE_STATE_PAUSED:
					pipe->state = PIPE_STATE_STARTED;
					अवरोध;
				हाल PIPE_STATE_STARTED:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		err = start_transport(chip, channelmask,
				      chip->pipe_cyclic_mask);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		क्रम (i = 0; i < DSP_MAXPIPES; i++) अणु
			अगर (channelmask & (1 << i)) अणु
				pipe = chip->substream[i]->runसमय->निजी_data;
				pipe->state = PIPE_STATE_STOPPED;
			पूर्ण
		पूर्ण
		err = stop_transport(chip, channelmask);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		क्रम (i = 0; i < DSP_MAXPIPES; i++) अणु
			अगर (channelmask & (1 << i)) अणु
				pipe = chip->substream[i]->runसमय->निजी_data;
				pipe->state = PIPE_STATE_PAUSED;
			पूर्ण
		पूर्ण
		err = छोड़ो_transport(chip, channelmask);
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण
	spin_unlock(&chip->lock);
	वापस err;
पूर्ण



अटल snd_pcm_uframes_t pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audiopipe *pipe = runसमय->निजी_data;
	u32 counter, step;

	/*
	 * IRQ handling runs concurrently. Do not share tracking of
	 * counter with it, which would race or require locking
	 */

	counter = le32_to_cpu(*pipe->dma_counter);  /* presumed atomic */

	step = counter - pipe->last_counter;  /* handles wrapping */
	pipe->last_counter = counter;

	/* counter करोesn't neccessarily wrap on a multiple of
	 * buffer_size, so can't derive the position; must
	 * accumulate */

	pipe->position += step;
	pipe->position %= frames_to_bytes(runसमय, runसमय->buffer_size); /* wrap */

	वापस bytes_to_frames(runसमय, pipe->position);
पूर्ण



/* pcm *_ops काष्ठाures */
अटल स्थिर काष्ठा snd_pcm_ops analog_playback_ops = अणु
	.खोलो = pcm_analog_out_खोलो,
	.बंद = pcm_बंद,
	.hw_params = pcm_analog_out_hw_params,
	.hw_मुक्त = pcm_hw_मुक्त,
	.prepare = pcm_prepare,
	.trigger = pcm_trigger,
	.poपूर्णांकer = pcm_poपूर्णांकer,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_ops analog_capture_ops = अणु
	.खोलो = pcm_analog_in_खोलो,
	.बंद = pcm_बंद,
	.hw_params = pcm_analog_in_hw_params,
	.hw_मुक्त = pcm_hw_मुक्त,
	.prepare = pcm_prepare,
	.trigger = pcm_trigger,
	.poपूर्णांकer = pcm_poपूर्णांकer,
पूर्ण;
#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO
#अगर_अघोषित ECHOCARD_HAS_VMIXER
अटल स्थिर काष्ठा snd_pcm_ops digital_playback_ops = अणु
	.खोलो = pcm_digital_out_खोलो,
	.बंद = pcm_बंद,
	.hw_params = pcm_digital_out_hw_params,
	.hw_मुक्त = pcm_hw_मुक्त,
	.prepare = pcm_prepare,
	.trigger = pcm_trigger,
	.poपूर्णांकer = pcm_poपूर्णांकer,
पूर्ण;
#पूर्ण_अगर /* !ECHOCARD_HAS_VMIXER */
अटल स्थिर काष्ठा snd_pcm_ops digital_capture_ops = अणु
	.खोलो = pcm_digital_in_खोलो,
	.बंद = pcm_बंद,
	.hw_params = pcm_digital_in_hw_params,
	.hw_मुक्त = pcm_hw_मुक्त,
	.prepare = pcm_prepare,
	.trigger = pcm_trigger,
	.poपूर्णांकer = pcm_poपूर्णांकer,
पूर्ण;
#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_IO */



/* Pपुनः_स्मृतिate memory only क्रम the first substream because it's the most
 * used one
 */
अटल व्योम snd_echo_pपुनः_स्मृतिate_pages(काष्ठा snd_pcm *pcm, काष्ठा device *dev)
अणु
	काष्ठा snd_pcm_substream *ss;
	पूर्णांक stream;

	क्रम (stream = 0; stream < 2; stream++)
		क्रम (ss = pcm->streams[stream].substream; ss; ss = ss->next)
			snd_pcm_set_managed_buffer(ss, SNDRV_DMA_TYPE_DEV_SG,
						   dev,
						   ss->number ? 0 : 128<<10,
						   256<<10);
पूर्ण



/*<--snd_echo_probe() */
अटल पूर्णांक snd_echo_new_pcm(काष्ठा echoaudio *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

#अगर_घोषित ECHOCARD_HAS_VMIXER
	/* This card has a Vmixer, that is there is no direct mapping from PCM
	streams to physical outमाला_दो. The user can mix the streams as he wishes
	via control पूर्णांकerface and it's possible to send any stream to any
	output, thus it makes no sense to keep analog and digital outमाला_दो
	separated */

	/* PCM#0 Virtual outमाला_दो and analog inमाला_दो */
	अगर ((err = snd_pcm_new(chip->card, "PCM", 0, num_pipes_out(chip),
				num_analog_busses_in(chip), &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;
	chip->analog_pcm = pcm;
	म_नकल(pcm->name, chip->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &analog_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &analog_capture_ops);
	snd_echo_pपुनः_स्मृतिate_pages(pcm, &chip->pci->dev);

#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO
	/* PCM#1 Digital inमाला_दो, no outमाला_दो */
	अगर ((err = snd_pcm_new(chip->card, "Digital PCM", 1, 0,
			       num_digital_busses_in(chip), &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;
	chip->digital_pcm = pcm;
	म_नकल(pcm->name, chip->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &digital_capture_ops);
	snd_echo_pपुनः_स्मृतिate_pages(pcm, &chip->pci->dev);
#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_IO */

#अन्यथा /* ECHOCARD_HAS_VMIXER */

	/* The card can manage substreams क्रमmed by analog and digital channels
	at the same समय, but I prefer to keep analog and digital channels
	separated, because that mixed thing is confusing and useless. So we
	रेजिस्टर two PCM devices: */

	/* PCM#0 Analog i/o */
	अगर ((err = snd_pcm_new(chip->card, "Analog PCM", 0,
			       num_analog_busses_out(chip),
			       num_analog_busses_in(chip), &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;
	chip->analog_pcm = pcm;
	म_नकल(pcm->name, chip->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &analog_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &analog_capture_ops);
	snd_echo_pपुनः_स्मृतिate_pages(pcm, &chip->pci->dev);

#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO
	/* PCM#1 Digital i/o */
	अगर ((err = snd_pcm_new(chip->card, "Digital PCM", 1,
			       num_digital_busses_out(chip),
			       num_digital_busses_in(chip), &pcm)) < 0)
		वापस err;
	pcm->निजी_data = chip;
	chip->digital_pcm = pcm;
	म_नकल(pcm->name, chip->card->लघुname);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &digital_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &digital_capture_ops);
	snd_echo_pपुनः_स्मृतिate_pages(pcm, &chip->pci->dev);
#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_IO */

#पूर्ण_अगर /* ECHOCARD_HAS_VMIXER */

	वापस 0;
पूर्ण




/******************************************************************************
	Control पूर्णांकerface
******************************************************************************/

#अगर !defined(ECHOCARD_HAS_VMIXER) || defined(ECHOCARD_HAS_LINE_OUT_GAIN)

/******************* PCM output volume *******************/
अटल पूर्णांक snd_echo_output_gain_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = num_busses_out(chip);
	uinfo->value.पूर्णांकeger.min = ECHOGAIN_MINOUT;
	uinfo->value.पूर्णांकeger.max = ECHOGAIN_MAXOUT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_output_gain_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c;

	chip = snd_kcontrol_chip(kcontrol);
	क्रम (c = 0; c < num_busses_out(chip); c++)
		ucontrol->value.पूर्णांकeger.value[c] = chip->output_gain[c];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_output_gain_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c, changed, gain;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	spin_lock_irq(&chip->lock);
	क्रम (c = 0; c < num_busses_out(chip); c++) अणु
		gain = ucontrol->value.पूर्णांकeger.value[c];
		/* Ignore out of range values */
		अगर (gain < ECHOGAIN_MINOUT || gain > ECHOGAIN_MAXOUT)
			जारी;
		अगर (chip->output_gain[c] != gain) अणु
			set_output_gain(chip, c, gain);
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed)
		update_output_line_level(chip);
	spin_unlock_irq(&chip->lock);
	वापस changed;
पूर्ण

#अगर_घोषित ECHOCARD_HAS_LINE_OUT_GAIN
/* On the Mia this one controls the line-out volume */
अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_line_output_gain = अणु
	.name = "Line Playback Volume",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
		  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.info = snd_echo_output_gain_info,
	.get = snd_echo_output_gain_get,
	.put = snd_echo_output_gain_put,
	.tlv = अणु.p = db_scale_output_gainपूर्ण,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_pcm_output_gain = अणु
	.name = "PCM Playback Volume",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.info = snd_echo_output_gain_info,
	.get = snd_echo_output_gain_get,
	.put = snd_echo_output_gain_put,
	.tlv = अणु.p = db_scale_output_gainपूर्ण,
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* !ECHOCARD_HAS_VMIXER || ECHOCARD_HAS_LINE_OUT_GAIN */



#अगर_घोषित ECHOCARD_HAS_INPUT_GAIN

/******************* Analog input volume *******************/
अटल पूर्णांक snd_echo_input_gain_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = num_analog_busses_in(chip);
	uinfo->value.पूर्णांकeger.min = ECHOGAIN_MININP;
	uinfo->value.पूर्णांकeger.max = ECHOGAIN_MAXINP;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_input_gain_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c;

	chip = snd_kcontrol_chip(kcontrol);
	क्रम (c = 0; c < num_analog_busses_in(chip); c++)
		ucontrol->value.पूर्णांकeger.value[c] = chip->input_gain[c];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_input_gain_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c, gain, changed;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	spin_lock_irq(&chip->lock);
	क्रम (c = 0; c < num_analog_busses_in(chip); c++) अणु
		gain = ucontrol->value.पूर्णांकeger.value[c];
		/* Ignore out of range values */
		अगर (gain < ECHOGAIN_MININP || gain > ECHOGAIN_MAXINP)
			जारी;
		अगर (chip->input_gain[c] != gain) अणु
			set_input_gain(chip, c, gain);
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed)
		update_input_line_level(chip);
	spin_unlock_irq(&chip->lock);
	वापस changed;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_input_gain, -2500, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_line_input_gain = अणु
	.name = "Line Capture Volume",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.info = snd_echo_input_gain_info,
	.get = snd_echo_input_gain_get,
	.put = snd_echo_input_gain_put,
	.tlv = अणु.p = db_scale_input_gainपूर्ण,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_INPUT_GAIN */



#अगर_घोषित ECHOCARD_HAS_OUTPUT_NOMINAL_LEVEL

/************ Analog output nominal level (+4dBu / -10dBV) ***************/
अटल पूर्णांक snd_echo_output_nominal_info (काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = num_analog_busses_out(chip);
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_output_nominal_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c;

	chip = snd_kcontrol_chip(kcontrol);
	क्रम (c = 0; c < num_analog_busses_out(chip); c++)
		ucontrol->value.पूर्णांकeger.value[c] = chip->nominal_level[c];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_output_nominal_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c, changed;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	spin_lock_irq(&chip->lock);
	क्रम (c = 0; c < num_analog_busses_out(chip); c++) अणु
		अगर (chip->nominal_level[c] != ucontrol->value.पूर्णांकeger.value[c]) अणु
			set_nominal_level(chip, c,
					  ucontrol->value.पूर्णांकeger.value[c]);
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed)
		update_output_line_level(chip);
	spin_unlock_irq(&chip->lock);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_output_nominal_level = अणु
	.name = "Line Playback Switch (-10dBV)",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = snd_echo_output_nominal_info,
	.get = snd_echo_output_nominal_get,
	.put = snd_echo_output_nominal_put,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_OUTPUT_NOMINAL_LEVEL */



#अगर_घोषित ECHOCARD_HAS_INPUT_NOMINAL_LEVEL

/*************** Analog input nominal level (+4dBu / -10dBV) ***************/
अटल पूर्णांक snd_echo_input_nominal_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = num_analog_busses_in(chip);
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_input_nominal_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c;

	chip = snd_kcontrol_chip(kcontrol);
	क्रम (c = 0; c < num_analog_busses_in(chip); c++)
		ucontrol->value.पूर्णांकeger.value[c] =
			chip->nominal_level[bx_analog_in(chip) + c];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_input_nominal_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक c, changed;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	spin_lock_irq(&chip->lock);
	क्रम (c = 0; c < num_analog_busses_in(chip); c++) अणु
		अगर (chip->nominal_level[bx_analog_in(chip) + c] !=
		    ucontrol->value.पूर्णांकeger.value[c]) अणु
			set_nominal_level(chip, bx_analog_in(chip) + c,
					  ucontrol->value.पूर्णांकeger.value[c]);
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed)
		update_output_line_level(chip);	/* "Output" is not a mistake
						 * here.
						 */
	spin_unlock_irq(&chip->lock);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_पूर्णांकput_nominal_level = अणु
	.name = "Line Capture Switch (-10dBV)",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = snd_echo_input_nominal_info,
	.get = snd_echo_input_nominal_get,
	.put = snd_echo_input_nominal_put,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_INPUT_NOMINAL_LEVEL */



#अगर_घोषित ECHOCARD_HAS_MONITOR

/******************* Monitor mixer *******************/
अटल पूर्णांक snd_echo_mixer_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = ECHOGAIN_MINOUT;
	uinfo->value.पूर्णांकeger.max = ECHOGAIN_MAXOUT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_mixer_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक out = ucontrol->id.index / num_busses_in(chip);
	अचिन्हित पूर्णांक in = ucontrol->id.index % num_busses_in(chip);

	अगर (out >= ECHO_MAXAUDIOOUTPUTS || in >= ECHO_MAXAUDIOINPUTS)
		वापस -EINVAL;

	ucontrol->value.पूर्णांकeger.value[0] = chip->monitor_gain[out][in];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_mixer_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक changed,  gain;
	अचिन्हित पूर्णांक out, in;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	out = ucontrol->id.index / num_busses_in(chip);
	in = ucontrol->id.index % num_busses_in(chip);
	अगर (out >= ECHO_MAXAUDIOOUTPUTS || in >= ECHO_MAXAUDIOINPUTS)
		वापस -EINVAL;
	gain = ucontrol->value.पूर्णांकeger.value[0];
	अगर (gain < ECHOGAIN_MINOUT || gain > ECHOGAIN_MAXOUT)
		वापस -EINVAL;
	अगर (chip->monitor_gain[out][in] != gain) अणु
		spin_lock_irq(&chip->lock);
		set_monitor_gain(chip, out, in, gain);
		update_output_line_level(chip);
		spin_unlock_irq(&chip->lock);
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल काष्ठा snd_kcontrol_new snd_echo_monitor_mixer = अणु
	.name = "Monitor Mixer Volume",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.info = snd_echo_mixer_info,
	.get = snd_echo_mixer_get,
	.put = snd_echo_mixer_put,
	.tlv = अणु.p = db_scale_output_gainपूर्ण,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_MONITOR */



#अगर_घोषित ECHOCARD_HAS_VMIXER

/******************* Vmixer *******************/
अटल पूर्णांक snd_echo_vmixer_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = ECHOGAIN_MINOUT;
	uinfo->value.पूर्णांकeger.max = ECHOGAIN_MAXOUT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_vmixer_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] =
		chip->vmixer_gain[ucontrol->id.index / num_pipes_out(chip)]
			[ucontrol->id.index % num_pipes_out(chip)];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_vmixer_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक gain, changed;
	लघु vch, out;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	out = ucontrol->id.index / num_pipes_out(chip);
	vch = ucontrol->id.index % num_pipes_out(chip);
	gain = ucontrol->value.पूर्णांकeger.value[0];
	अगर (gain < ECHOGAIN_MINOUT || gain > ECHOGAIN_MAXOUT)
		वापस -EINVAL;
	अगर (chip->vmixer_gain[out][vch] != ucontrol->value.पूर्णांकeger.value[0]) अणु
		spin_lock_irq(&chip->lock);
		set_vmixer_gain(chip, out, vch, ucontrol->value.पूर्णांकeger.value[0]);
		update_vmixer_level(chip);
		spin_unlock_irq(&chip->lock);
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल काष्ठा snd_kcontrol_new snd_echo_vmixer = अणु
	.name = "VMixer Volume",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.info = snd_echo_vmixer_info,
	.get = snd_echo_vmixer_get,
	.put = snd_echo_vmixer_put,
	.tlv = अणु.p = db_scale_output_gainपूर्ण,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_VMIXER */



#अगर_घोषित ECHOCARD_HAS_DIGITAL_MODE_SWITCH

/******************* Digital mode चयन *******************/
अटल पूर्णांक snd_echo_digital_mode_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर names[4] = अणु
		"S/PDIF Coaxial", "S/PDIF Optical", "ADAT Optical",
		"S/PDIF Cdrom"
	पूर्ण;
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	वापस snd_ctl_क्रमागत_info(uinfo, 1, chip->num_digital_modes, names);
पूर्ण

अटल पूर्णांक snd_echo_digital_mode_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक i, mode;

	chip = snd_kcontrol_chip(kcontrol);
	mode = chip->digital_mode;
	क्रम (i = chip->num_digital_modes - 1; i >= 0; i--)
		अगर (mode == chip->digital_mode_list[i]) अणु
			ucontrol->value.क्रमागतerated.item[0] = i;
			अवरोध;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_digital_mode_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक changed;
	अचिन्हित लघु emode, dmode;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);

	emode = ucontrol->value.क्रमागतerated.item[0];
	अगर (emode >= chip->num_digital_modes)
		वापस -EINVAL;
	dmode = chip->digital_mode_list[emode];

	अगर (dmode != chip->digital_mode) अणु
		/* mode_mutex is required to make this operation atomic wrt
		pcm_digital_*_खोलो() and set_input_घड़ी() functions. */
		mutex_lock(&chip->mode_mutex);

		/* Do not allow the user to change the digital mode when a pcm
		device is खोलो because it also changes the number of channels
		and the allowed sample rates */
		अगर (chip->खोलोcount) अणु
			changed = -EAGAIN;
		पूर्ण अन्यथा अणु
			changed = set_digital_mode(chip, dmode);
			/* If we had to change the घड़ी source, report it */
			अगर (changed > 0 && chip->घड़ी_src_ctl) अणु
				snd_ctl_notअगरy(chip->card,
					       SNDRV_CTL_EVENT_MASK_VALUE,
					       &chip->घड़ी_src_ctl->id);
				dev_dbg(chip->card->dev,
					"SDM() =%d\n", changed);
			पूर्ण
			अगर (changed >= 0)
				changed = 1;	/* No errors */
		पूर्ण
		mutex_unlock(&chip->mode_mutex);
	पूर्ण
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_digital_mode_चयन = अणु
	.name = "Digital mode Switch",
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.info = snd_echo_digital_mode_info,
	.get = snd_echo_digital_mode_get,
	.put = snd_echo_digital_mode_put,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_MODE_SWITCH */



#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO

/******************* S/PDIF mode चयन *******************/
अटल पूर्णांक snd_echo_spdअगर_mode_info(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर names[2] = अणु"Consumer", "Professional"पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, names);
पूर्ण

अटल पूर्णांक snd_echo_spdअगर_mode_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = !!chip->professional_spdअगर;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_spdअगर_mode_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक mode;

	chip = snd_kcontrol_chip(kcontrol);
	mode = !!ucontrol->value.क्रमागतerated.item[0];
	अगर (mode != chip->professional_spdअगर) अणु
		spin_lock_irq(&chip->lock);
		set_professional_spdअगर(chip, mode);
		spin_unlock_irq(&chip->lock);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_spdअगर_mode_चयन = अणु
	.name = "S/PDIF mode Switch",
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.info = snd_echo_spdअगर_mode_info,
	.get = snd_echo_spdअगर_mode_get,
	.put = snd_echo_spdअगर_mode_put,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_IO */



#अगर_घोषित ECHOCARD_HAS_EXTERNAL_CLOCK

/******************* Select input घड़ी source *******************/
अटल पूर्णांक snd_echo_घड़ी_source_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर names[8] = अणु
		"Internal", "Word", "Super", "S/PDIF", "ADAT", "ESync",
		"ESync96", "MTC"
	पूर्ण;
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	वापस snd_ctl_क्रमागत_info(uinfo, 1, chip->num_घड़ी_sources, names);
पूर्ण

अटल पूर्णांक snd_echo_घड़ी_source_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक i, घड़ी;

	chip = snd_kcontrol_chip(kcontrol);
	घड़ी = chip->input_घड़ी;

	क्रम (i = 0; i < chip->num_घड़ी_sources; i++)
		अगर (घड़ी == chip->घड़ी_source_list[i])
			ucontrol->value.क्रमागतerated.item[0] = i;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_घड़ी_source_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक changed;
	अचिन्हित पूर्णांक eघड़ी, dघड़ी;

	changed = 0;
	chip = snd_kcontrol_chip(kcontrol);
	eघड़ी = ucontrol->value.क्रमागतerated.item[0];
	अगर (eघड़ी >= chip->input_घड़ी_प्रकारypes)
		वापस -EINVAL;
	dघड़ी = chip->घड़ी_source_list[eघड़ी];
	अगर (chip->input_घड़ी != dघड़ी) अणु
		mutex_lock(&chip->mode_mutex);
		spin_lock_irq(&chip->lock);
		अगर ((changed = set_input_घड़ी(chip, dघड़ी)) == 0)
			changed = 1;	/* no errors */
		spin_unlock_irq(&chip->lock);
		mutex_unlock(&chip->mode_mutex);
	पूर्ण

	अगर (changed < 0)
		dev_dbg(chip->card->dev,
			"seticlk val%d err 0x%x\n", dघड़ी, changed);

	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_घड़ी_source_चयन = अणु
	.name = "Sample Clock Source",
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.info = snd_echo_घड़ी_source_info,
	.get = snd_echo_घड़ी_source_get,
	.put = snd_echo_घड़ी_source_put,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_EXTERNAL_CLOCK */



#अगर_घोषित ECHOCARD_HAS_PHANTOM_POWER

/******************* Phantom घातer चयन *******************/
#घोषणा snd_echo_phantom_घातer_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_echo_phantom_घातer_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = chip->phantom_घातer;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_phantom_घातer_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक घातer, changed = 0;

	घातer = !!ucontrol->value.पूर्णांकeger.value[0];
	अगर (chip->phantom_घातer != घातer) अणु
		spin_lock_irq(&chip->lock);
		changed = set_phantom_घातer(chip, घातer);
		spin_unlock_irq(&chip->lock);
		अगर (changed == 0)
			changed = 1;	/* no errors */
	पूर्ण
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_phantom_घातer_चयन = अणु
	.name = "Phantom power Switch",
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.info = snd_echo_phantom_घातer_info,
	.get = snd_echo_phantom_घातer_get,
	.put = snd_echo_phantom_घातer_put,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_PHANTOM_POWER */



#अगर_घोषित ECHOCARD_HAS_DIGITAL_IN_AUTOMUTE

/******************* Digital input स्वतःmute चयन *******************/
#घोषणा snd_echo_स्वतःmute_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_echo_स्वतःmute_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = chip->digital_in_स्वतःmute;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_स्वतःmute_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक स्वतःmute, changed = 0;

	स्वतःmute = !!ucontrol->value.पूर्णांकeger.value[0];
	अगर (chip->digital_in_स्वतःmute != स्वतःmute) अणु
		spin_lock_irq(&chip->lock);
		changed = set_input_स्वतः_mute(chip, स्वतःmute);
		spin_unlock_irq(&chip->lock);
		अगर (changed == 0)
			changed = 1;	/* no errors */
	पूर्ण
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_स्वतःmute_चयन = अणु
	.name = "Digital Capture Switch (automute)",
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.info = snd_echo_स्वतःmute_info,
	.get = snd_echo_स्वतःmute_get,
	.put = snd_echo_स्वतःmute_put,
पूर्ण;

#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_IN_AUTOMUTE */



/******************* VU-meters चयन *******************/
#घोषणा snd_echo_vumeters_चयन_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_echo_vumeters_चयन_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	spin_lock_irq(&chip->lock);
	set_meters_on(chip, ucontrol->value.पूर्णांकeger.value[0]);
	spin_unlock_irq(&chip->lock);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_vumeters_चयन = अणु
	.name = "VU-meters Switch",
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.access = SNDRV_CTL_ELEM_ACCESS_WRITE,
	.info = snd_echo_vumeters_चयन_info,
	.put = snd_echo_vumeters_चयन_put,
पूर्ण;



/***** Read VU-meters (input, output, analog and digital together) *****/
अटल पूर्णांक snd_echo_vumeters_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 96;
	uinfo->value.पूर्णांकeger.min = ECHOGAIN_MINOUT;
	uinfo->value.पूर्णांकeger.max = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_vumeters_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	get_audio_meters(chip, ucontrol->value.पूर्णांकeger.value);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_vumeters = अणु
	.name = "VU-meters",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READ |
		  SNDRV_CTL_ELEM_ACCESS_VOLATILE |
		  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
	.info = snd_echo_vumeters_info,
	.get = snd_echo_vumeters_get,
	.tlv = अणु.p = db_scale_output_gainपूर्ण,
पूर्ण;



/*** Channels info - it exports inक्रमmations about the number of channels ***/
अटल पूर्णांक snd_echo_channels_info_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 6;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1 << ECHO_CLOCK_NUMBER;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_echo_channels_info_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक detected, घड़ीs, bit, src;

	chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = num_busses_in(chip);
	ucontrol->value.पूर्णांकeger.value[1] = num_analog_busses_in(chip);
	ucontrol->value.पूर्णांकeger.value[2] = num_busses_out(chip);
	ucontrol->value.पूर्णांकeger.value[3] = num_analog_busses_out(chip);
	ucontrol->value.पूर्णांकeger.value[4] = num_pipes_out(chip);

	/* Compute the biपंचांगask of the currently valid input घड़ीs */
	detected = detect_input_घड़ीs(chip);
	घड़ीs = 0;
	src = chip->num_घड़ी_sources - 1;
	क्रम (bit = ECHO_CLOCK_NUMBER - 1; bit >= 0; bit--)
		अगर (detected & (1 << bit))
			क्रम (; src >= 0; src--)
				अगर (bit == chip->घड़ी_source_list[src]) अणु
					घड़ीs |= 1 << src;
					अवरोध;
				पूर्ण
	ucontrol->value.पूर्णांकeger.value[5] = घड़ीs;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_echo_channels_info = अणु
	.name = "Channels info",
	.अगरace = SNDRV_CTL_ELEM_IFACE_HWDEP,
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info = snd_echo_channels_info_info,
	.get = snd_echo_channels_info_get,
पूर्ण;




/******************************************************************************
	IRQ Handling
******************************************************************************/
/* Check अगर a period has elapsed since last पूर्णांकerrupt
 *
 * Don't make any updates to state; PCM core handles this with the
 * correct locks.
 *
 * \लeturn true अगर a period has elapsed, otherwise false
 */
अटल bool period_has_elapsed(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा audiopipe *pipe = runसमय->निजी_data;
	u32 counter, step;
	माप_प्रकार period_bytes;

	अगर (pipe->state != PIPE_STATE_STARTED)
		वापस false;

	period_bytes = frames_to_bytes(runसमय, runसमय->period_size);

	counter = le32_to_cpu(*pipe->dma_counter);  /* presumed atomic */

	step = counter - pipe->last_period;  /* handles wrapping */
	step -= step % period_bytes;  /* acknowledge whole periods only */

	अगर (step == 0)
		वापस false;  /* haven't advanced a whole period yet */

	pipe->last_period += step;  /* used exclusively by us */
	वापस true;
पूर्ण

अटल irqवापस_t snd_echo_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा echoaudio *chip = dev_id;
	पूर्णांक ss, st;

	spin_lock(&chip->lock);
	st = service_irq(chip);
	अगर (st < 0) अणु
		spin_unlock(&chip->lock);
		वापस IRQ_NONE;
	पूर्ण
	/* The hardware करोesn't tell us which substream caused the irq,
	thus we have to check all running substreams. */
	क्रम (ss = 0; ss < DSP_MAXPIPES; ss++) अणु
		काष्ठा snd_pcm_substream *substream;

		substream = chip->substream[ss];
		अगर (substream && period_has_elapsed(substream)) अणु
			spin_unlock(&chip->lock);
			snd_pcm_period_elapsed(substream);
			spin_lock(&chip->lock);
		पूर्ण
	पूर्ण
	spin_unlock(&chip->lock);

#अगर_घोषित ECHOCARD_HAS_MIDI
	अगर (st > 0 && chip->midi_in) अणु
		snd_rawmidi_receive(chip->midi_in, chip->midi_buffer, st);
		dev_dbg(chip->card->dev, "rawmidi_iread=%d\n", st);
	पूर्ण
#पूर्ण_अगर
	वापस IRQ_HANDLED;
पूर्ण




/******************************************************************************
	Module स्थिरruction / deकाष्ठाion
******************************************************************************/

अटल पूर्णांक snd_echo_मुक्त(काष्ठा echoaudio *chip)
अणु
	अगर (chip->comm_page)
		rest_in_peace(chip);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);

	अगर (chip->comm_page)
		snd_dma_मुक्त_pages(&chip->commpage_dma_buf);

	iounmap(chip->dsp_रेजिस्टरs);
	release_and_मुक्त_resource(chip->iores);
	pci_disable_device(chip->pci);

	/* release chip data */
	मुक्त_firmware_cache(chip);
	kमुक्त(chip);
	वापस 0;
पूर्ण



अटल पूर्णांक snd_echo_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा echoaudio *chip = device->device_data;

	वापस snd_echo_मुक्त(chip);
पूर्ण



/* <--snd_echo_probe() */
अटल पूर्णांक snd_echo_create(काष्ठा snd_card *card,
			   काष्ठा pci_dev *pci,
			   काष्ठा echoaudio **rchip)
अणु
	काष्ठा echoaudio *chip;
	पूर्णांक err;
	माप_प्रकार sz;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_echo_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	pci_ग_लिखो_config_byte(pci, PCI_LATENCY_TIMER, 0xC0);

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	pci_set_master(pci);

	/* Allocate chip अगर needed */
	अगर (!*rchip) अणु
		chip = kzalloc(माप(*chip), GFP_KERNEL);
		अगर (!chip) अणु
			pci_disable_device(pci);
			वापस -ENOMEM;
		पूर्ण
		dev_dbg(card->dev, "chip=%p\n", chip);
		spin_lock_init(&chip->lock);
		chip->card = card;
		chip->pci = pci;
		chip->irq = -1;
		chip->खोलोcount = 0;
		mutex_init(&chip->mode_mutex);
		chip->can_set_rate = 1;
	पूर्ण अन्यथा अणु
		/* If this was called from the resume function, chip is
		 * alपढ़ोy allocated and it contains current card settings.
		 */
		chip = *rchip;
	पूर्ण

	/* PCI resource allocation */
	chip->dsp_रेजिस्टरs_phys = pci_resource_start(pci, 0);
	sz = pci_resource_len(pci, 0);
	अगर (sz > PAGE_SIZE)
		sz = PAGE_SIZE;		/* We map only the required part */

	अगर ((chip->iores = request_mem_region(chip->dsp_रेजिस्टरs_phys, sz,
					      ECHOCARD_NAME)) == शून्य) अणु
		dev_err(chip->card->dev, "cannot get memory region\n");
		snd_echo_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->dsp_रेजिस्टरs = ioremap(chip->dsp_रेजिस्टरs_phys, sz);
	अगर (!chip->dsp_रेजिस्टरs) अणु
		dev_err(chip->card->dev, "ioremap failed\n");
		snd_echo_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण

	अगर (request_irq(pci->irq, snd_echo_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(chip->card->dev, "cannot grab irq\n");
		snd_echo_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	dev_dbg(card->dev, "pci=%p irq=%d subdev=%04x Init hardware...\n",
		chip->pci, chip->irq, chip->pci->subप्रणाली_device);

	/* Create the DSP comm page - this is the area of memory used क्रम most
	of the communication with the DSP, which accesses it via bus mastering */
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				माप(काष्ठा comm_page),
				&chip->commpage_dma_buf) < 0) अणु
		dev_err(chip->card->dev, "cannot allocate the comm page\n");
		snd_echo_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण
	chip->comm_page_phys = chip->commpage_dma_buf.addr;
	chip->comm_page = (काष्ठा comm_page *)chip->commpage_dma_buf.area;

	err = init_hw(chip, chip->pci->device, chip->pci->subप्रणाली_device);
	अगर (err >= 0)
		err = set_mixer_शेषs(chip);
	अगर (err < 0) अणु
		dev_err(card->dev, "init_hw err=%d\n", err);
		snd_echo_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_echo_मुक्त(chip);
		वापस err;
	पूर्ण
	*rchip = chip;
	/* Init करोne ! */
	वापस 0;
पूर्ण



/* स्थिरructor */
अटल पूर्णांक snd_echo_probe(काष्ठा pci_dev *pci,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा echoaudio *chip;
	अक्षर *dsp;
	__maybe_unused पूर्णांक i;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	i = 0;
	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	chip = शून्य;	/* Tells snd_echo_create to allocate chip */
	अगर ((err = snd_echo_create(card, pci, &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	म_नकल(card->driver, "Echo_" ECHOCARD_NAME);
	म_नकल(card->लघुname, chip->card_name);

	dsp = "56301";
	अगर (pci_id->device == 0x3410)
		dsp = "56361";

	प्र_लिखो(card->दीर्घname, "%s rev.%d (DSP%s) at 0x%lx irq %i",
		card->लघुname, pci_id->subdevice & 0x000f, dsp,
		chip->dsp_रेजिस्टरs_phys, chip->irq);

	अगर ((err = snd_echo_new_pcm(chip)) < 0) अणु
		dev_err(chip->card->dev, "new pcm error %d\n", err);
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

#अगर_घोषित ECHOCARD_HAS_MIDI
	अगर (chip->has_midi) अणु	/* Some Mia's करो not have midi */
		अगर ((err = snd_echo_midi_create(card, chip)) < 0) अणु
			dev_err(chip->card->dev, "new midi error %d\n", err);
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_VMIXER
	snd_echo_vmixer.count = num_pipes_out(chip) * num_busses_out(chip);
	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_vmixer, chip))) < 0)
		जाओ ctl_error;
#अगर_घोषित ECHOCARD_HAS_LINE_OUT_GAIN
	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&snd_echo_line_output_gain, chip));
	अगर (err < 0)
		जाओ ctl_error;
#पूर्ण_अगर
#अन्यथा /* ECHOCARD_HAS_VMIXER */
	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&snd_echo_pcm_output_gain, chip));
	अगर (err < 0)
		जाओ ctl_error;
#पूर्ण_अगर /* ECHOCARD_HAS_VMIXER */

#अगर_घोषित ECHOCARD_HAS_INPUT_GAIN
	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_line_input_gain, chip))) < 0)
		जाओ ctl_error;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_INPUT_NOMINAL_LEVEL
	अगर (!chip->hasnt_input_nominal_level)
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_पूर्णांकput_nominal_level, chip))) < 0)
			जाओ ctl_error;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_OUTPUT_NOMINAL_LEVEL
	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_output_nominal_level, chip))) < 0)
		जाओ ctl_error;
#पूर्ण_अगर

	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_vumeters_चयन, chip))) < 0)
		जाओ ctl_error;

	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_vumeters, chip))) < 0)
		जाओ ctl_error;

#अगर_घोषित ECHOCARD_HAS_MONITOR
	snd_echo_monitor_mixer.count = num_busses_in(chip) * num_busses_out(chip);
	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_monitor_mixer, chip))) < 0)
		जाओ ctl_error;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_DIGITAL_IN_AUTOMUTE
	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_स्वतःmute_चयन, chip))) < 0)
		जाओ ctl_error;
#पूर्ण_अगर

	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_channels_info, chip))) < 0)
		जाओ ctl_error;

#अगर_घोषित ECHOCARD_HAS_DIGITAL_MODE_SWITCH
	/* Creates a list of available digital modes */
	chip->num_digital_modes = 0;
	क्रम (i = 0; i < 6; i++)
		अगर (chip->digital_modes & (1 << i))
			chip->digital_mode_list[chip->num_digital_modes++] = i;

	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_digital_mode_चयन, chip))) < 0)
		जाओ ctl_error;
#पूर्ण_अगर /* ECHOCARD_HAS_DIGITAL_MODE_SWITCH */

#अगर_घोषित ECHOCARD_HAS_EXTERNAL_CLOCK
	/* Creates a list of available घड़ी sources */
	chip->num_घड़ी_sources = 0;
	क्रम (i = 0; i < 10; i++)
		अगर (chip->input_घड़ी_प्रकारypes & (1 << i))
			chip->घड़ी_source_list[chip->num_घड़ी_sources++] = i;

	अगर (chip->num_घड़ी_sources > 1) अणु
		chip->घड़ी_src_ctl = snd_ctl_new1(&snd_echo_घड़ी_source_चयन, chip);
		अगर ((err = snd_ctl_add(chip->card, chip->घड़ी_src_ctl)) < 0)
			जाओ ctl_error;
	पूर्ण
#पूर्ण_अगर /* ECHOCARD_HAS_EXTERNAL_CLOCK */

#अगर_घोषित ECHOCARD_HAS_DIGITAL_IO
	अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_spdअगर_mode_चयन, chip))) < 0)
		जाओ ctl_error;
#पूर्ण_अगर

#अगर_घोषित ECHOCARD_HAS_PHANTOM_POWER
	अगर (chip->has_phantom_घातer)
		अगर ((err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_echo_phantom_घातer_चयन, chip))) < 0)
			जाओ ctl_error;
#पूर्ण_अगर

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ ctl_error;
	dev_info(card->dev, "Card registered: %s\n", card->दीर्घname);

	pci_set_drvdata(pci, chip);
	dev++;
	वापस 0;

ctl_error:
	dev_err(card->dev, "new control error %d\n", err);
	snd_card_मुक्त(card);
	वापस err;
पूर्ण



#अगर defined(CONFIG_PM_SLEEP)

अटल पूर्णांक snd_echo_suspend(काष्ठा device *dev)
अणु
	काष्ठा echoaudio *chip = dev_get_drvdata(dev);

#अगर_घोषित ECHOCARD_HAS_MIDI
	/* This call can sleep */
	अगर (chip->midi_out)
		snd_echo_midi_output_trigger(chip->midi_out, 0);
#पूर्ण_अगर
	spin_lock_irq(&chip->lock);
	अगर (रुको_handshake(chip)) अणु
		spin_unlock_irq(&chip->lock);
		वापस -EIO;
	पूर्ण
	clear_handshake(chip);
	अगर (send_vector(chip, DSP_VC_GO_COMATOSE) < 0) अणु
		spin_unlock_irq(&chip->lock);
		वापस -EIO;
	पूर्ण
	spin_unlock_irq(&chip->lock);

	chip->dsp_code = शून्य;
	मुक्त_irq(chip->irq, chip);
	chip->irq = -1;
	chip->card->sync_irq = -1;
	वापस 0;
पूर्ण



अटल पूर्णांक snd_echo_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा echoaudio *chip = dev_get_drvdata(dev);
	काष्ठा comm_page *commpage, *commpage_bak;
	u32 pipe_alloc_mask;
	पूर्णांक err;

	commpage = chip->comm_page;
	commpage_bak = kmemdup(commpage, माप(*commpage), GFP_KERNEL);
	अगर (commpage_bak == शून्य)
		वापस -ENOMEM;

	err = init_hw(chip, chip->pci->device, chip->pci->subप्रणाली_device);
	अगर (err < 0) अणु
		kमुक्त(commpage_bak);
		dev_err(dev, "resume init_hw err=%d\n", err);
		वापस err;
	पूर्ण

	/* Temporarily set chip->pipe_alloc_mask=0 otherwise
	 * restore_dsp_settings() fails.
	 */
	pipe_alloc_mask = chip->pipe_alloc_mask;
	chip->pipe_alloc_mask = 0;
	err = restore_dsp_rettings(chip);
	chip->pipe_alloc_mask = pipe_alloc_mask;
	अगर (err < 0) अणु
		kमुक्त(commpage_bak);
		वापस err;
	पूर्ण

	स_नकल(&commpage->audio_क्रमmat, &commpage_bak->audio_क्रमmat,
		माप(commpage->audio_क्रमmat));
	स_नकल(&commpage->sglist_addr, &commpage_bak->sglist_addr,
		माप(commpage->sglist_addr));
	स_नकल(&commpage->midi_output, &commpage_bak->midi_output,
		माप(commpage->midi_output));
	kमुक्त(commpage_bak);

	अगर (request_irq(pci->irq, snd_echo_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(chip->card->dev, "cannot grab irq\n");
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	chip->card->sync_irq = chip->irq;
	dev_dbg(dev, "resume irq=%d\n", chip->irq);

#अगर_घोषित ECHOCARD_HAS_MIDI
	अगर (chip->midi_input_enabled)
		enable_midi_input(chip, true);
	अगर (chip->midi_out)
		snd_echo_midi_output_trigger(chip->midi_out, 1);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_echo_pm, snd_echo_suspend, snd_echo_resume);
#घोषणा SND_ECHO_PM_OPS	&snd_echo_pm
#अन्यथा
#घोषणा SND_ECHO_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */


अटल व्योम snd_echo_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा echoaudio *chip;

	chip = pci_get_drvdata(pci);
	अगर (chip)
		snd_card_मुक्त(chip->card);
पूर्ण



/******************************************************************************
	Everything starts and ends here
******************************************************************************/

/* pci_driver definition */
अटल काष्ठा pci_driver echo_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_echo_ids,
	.probe = snd_echo_probe,
	.हटाओ = snd_echo_हटाओ,
	.driver = अणु
		.pm = SND_ECHO_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(echo_driver);
