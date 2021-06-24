<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * C-Media CMI8788 driver - PCM code
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/pci.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "oxygen.h"

/* most DMA channels have a 16-bit counter क्रम 32-bit words */
#घोषणा BUFFER_BYTES_MAX		((1 << 16) * 4)
/* the multichannel DMA channel has a 24-bit counter */
#घोषणा BUFFER_BYTES_MAX_MULTICH	((1 << 24) * 4)

#घोषणा FIFO_BYTES			256
#घोषणा FIFO_BYTES_MULTICH		1024

#घोषणा PERIOD_BYTES_MIN		64

#घोषणा DEFAULT_BUFFER_BYTES		(BUFFER_BYTES_MAX / 2)
#घोषणा DEFAULT_BUFFER_BYTES_MULTICH	(1024 * 1024)

अटल स्थिर काष्ठा snd_pcm_hardware oxygen_stereo_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_SYNC_START |
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		   SNDRV_PCM_FMTBIT_S32_LE,
	.rates = SNDRV_PCM_RATE_32000 |
		 SNDRV_PCM_RATE_44100 |
		 SNDRV_PCM_RATE_48000 |
		 SNDRV_PCM_RATE_64000 |
		 SNDRV_PCM_RATE_88200 |
		 SNDRV_PCM_RATE_96000 |
		 SNDRV_PCM_RATE_176400 |
		 SNDRV_PCM_RATE_192000,
	.rate_min = 32000,
	.rate_max = 192000,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = BUFFER_BYTES_MAX,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = BUFFER_BYTES_MAX,
	.periods_min = 1,
	.periods_max = BUFFER_BYTES_MAX / PERIOD_BYTES_MIN,
	.fअगरo_size = FIFO_BYTES,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hardware oxygen_multichannel_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_SYNC_START |
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
		   SNDRV_PCM_FMTBIT_S32_LE,
	.rates = SNDRV_PCM_RATE_32000 |
		 SNDRV_PCM_RATE_44100 |
		 SNDRV_PCM_RATE_48000 |
		 SNDRV_PCM_RATE_64000 |
		 SNDRV_PCM_RATE_88200 |
		 SNDRV_PCM_RATE_96000 |
		 SNDRV_PCM_RATE_176400 |
		 SNDRV_PCM_RATE_192000,
	.rate_min = 32000,
	.rate_max = 192000,
	.channels_min = 2,
	.channels_max = 8,
	.buffer_bytes_max = BUFFER_BYTES_MAX_MULTICH,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = BUFFER_BYTES_MAX_MULTICH,
	.periods_min = 1,
	.periods_max = BUFFER_BYTES_MAX_MULTICH / PERIOD_BYTES_MIN,
	.fअगरo_size = FIFO_BYTES_MULTICH,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hardware oxygen_ac97_hardware = अणु
	.info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_SYNC_START |
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_48000,
	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = BUFFER_BYTES_MAX,
	.period_bytes_min = PERIOD_BYTES_MIN,
	.period_bytes_max = BUFFER_BYTES_MAX,
	.periods_min = 1,
	.periods_max = BUFFER_BYTES_MAX / PERIOD_BYTES_MIN,
	.fअगरo_size = FIFO_BYTES,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware *स्थिर oxygen_hardware[PCM_COUNT] = अणु
	[PCM_A] = &oxygen_stereo_hardware,
	[PCM_B] = &oxygen_stereo_hardware,
	[PCM_C] = &oxygen_stereo_hardware,
	[PCM_SPDIF] = &oxygen_stereo_hardware,
	[PCM_MULTICH] = &oxygen_multichannel_hardware,
	[PCM_AC97] = &oxygen_ac97_hardware,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक
oxygen_substream_channel(काष्ठा snd_pcm_substream *substream)
अणु
	वापस (अचिन्हित पूर्णांक)(uपूर्णांकptr_t)substream->runसमय->निजी_data;
पूर्ण

अटल पूर्णांक oxygen_खोलो(काष्ठा snd_pcm_substream *substream,
		       अचिन्हित पूर्णांक channel)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	runसमय->निजी_data = (व्योम *)(uपूर्णांकptr_t)channel;
	अगर (channel == PCM_B && chip->has_ac97_1 &&
	    (chip->model.device_config & CAPTURE_2_FROM_AC97_1))
		runसमय->hw = oxygen_ac97_hardware;
	अन्यथा
		runसमय->hw = *oxygen_hardware[channel];
	चयन (channel) अणु
	हाल PCM_C:
		अगर (chip->model.device_config & CAPTURE_1_FROM_SPDIF) अणु
			runसमय->hw.rates &= ~(SNDRV_PCM_RATE_32000 |
					       SNDRV_PCM_RATE_64000);
			runसमय->hw.rate_min = 44100;
		पूर्ण
		fallthrough;
	हाल PCM_A:
	हाल PCM_B:
		runसमय->hw.fअगरo_size = 0;
		अवरोध;
	हाल PCM_MULTICH:
		runसमय->hw.channels_max = chip->model.dac_channels_pcm;
		अवरोध;
	पूर्ण
	अगर (chip->model.pcm_hardware_filter)
		chip->model.pcm_hardware_filter(channel, &runसमय->hw);
	err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 32);
	अगर (err < 0)
		वापस err;
	err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 32);
	अगर (err < 0)
		वापस err;
	अगर (runसमय->hw.क्रमmats & SNDRV_PCM_FMTBIT_S32_LE) अणु
		err = snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (runसमय->hw.channels_max > 2) अणु
		err = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
						 SNDRV_PCM_HW_PARAM_CHANNELS,
						 2);
		अगर (err < 0)
			वापस err;
	पूर्ण
	snd_pcm_set_sync(substream);
	chip->streams[channel] = substream;

	mutex_lock(&chip->mutex);
	chip->pcm_active |= 1 << channel;
	अगर (channel == PCM_SPDIF) अणु
		chip->spdअगर_pcm_bits = chip->spdअगर_bits;
		chip->controls[CONTROL_SPDIF_PCM]->vd[0].access &=
			~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO,
			       &chip->controls[CONTROL_SPDIF_PCM]->id);
	पूर्ण
	mutex_unlock(&chip->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_rec_a_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस oxygen_खोलो(substream, PCM_A);
पूर्ण

अटल पूर्णांक oxygen_rec_b_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस oxygen_खोलो(substream, PCM_B);
पूर्ण

अटल पूर्णांक oxygen_rec_c_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस oxygen_खोलो(substream, PCM_C);
पूर्ण

अटल पूर्णांक oxygen_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस oxygen_खोलो(substream, PCM_SPDIF);
पूर्ण

अटल पूर्णांक oxygen_multich_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस oxygen_खोलो(substream, PCM_MULTICH);
पूर्ण

अटल पूर्णांक oxygen_ac97_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस oxygen_खोलो(substream, PCM_AC97);
पूर्ण

अटल पूर्णांक oxygen_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक channel = oxygen_substream_channel(substream);

	mutex_lock(&chip->mutex);
	chip->pcm_active &= ~(1 << channel);
	अगर (channel == PCM_SPDIF) अणु
		chip->controls[CONTROL_SPDIF_PCM]->vd[0].access |=
			SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO,
			       &chip->controls[CONTROL_SPDIF_PCM]->id);
	पूर्ण
	अगर (channel == PCM_SPDIF || channel == PCM_MULTICH)
		oxygen_update_spdअगर_source(chip);
	mutex_unlock(&chip->mutex);

	chip->streams[channel] = शून्य;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक oxygen_क्रमmat(काष्ठा snd_pcm_hw_params *hw_params)
अणु
	अगर (params_क्रमmat(hw_params) == SNDRV_PCM_FORMAT_S32_LE)
		वापस OXYGEN_FORMAT_24;
	अन्यथा
		वापस OXYGEN_FORMAT_16;
पूर्ण

अटल अचिन्हित पूर्णांक oxygen_rate(काष्ठा snd_pcm_hw_params *hw_params)
अणु
	चयन (params_rate(hw_params)) अणु
	हाल 32000:
		वापस OXYGEN_RATE_32000;
	हाल 44100:
		वापस OXYGEN_RATE_44100;
	शेष: /* 48000 */
		वापस OXYGEN_RATE_48000;
	हाल 64000:
		वापस OXYGEN_RATE_64000;
	हाल 88200:
		वापस OXYGEN_RATE_88200;
	हाल 96000:
		वापस OXYGEN_RATE_96000;
	हाल 176400:
		वापस OXYGEN_RATE_176400;
	हाल 192000:
		वापस OXYGEN_RATE_192000;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक oxygen_i2s_bits(काष्ठा snd_pcm_hw_params *hw_params)
अणु
	अगर (params_क्रमmat(hw_params) == SNDRV_PCM_FORMAT_S32_LE)
		वापस OXYGEN_I2S_BITS_24;
	अन्यथा
		वापस OXYGEN_I2S_BITS_16;
पूर्ण

अटल अचिन्हित पूर्णांक oxygen_play_channels(काष्ठा snd_pcm_hw_params *hw_params)
अणु
	चयन (params_channels(hw_params)) अणु
	शेष: /* 2 */
		वापस OXYGEN_PLAY_CHANNELS_2;
	हाल 4:
		वापस OXYGEN_PLAY_CHANNELS_4;
	हाल 6:
		वापस OXYGEN_PLAY_CHANNELS_6;
	हाल 8:
		वापस OXYGEN_PLAY_CHANNELS_8;
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक channel_base_रेजिस्टरs[PCM_COUNT] = अणु
	[PCM_A] = OXYGEN_DMA_A_ADDRESS,
	[PCM_B] = OXYGEN_DMA_B_ADDRESS,
	[PCM_C] = OXYGEN_DMA_C_ADDRESS,
	[PCM_SPDIF] = OXYGEN_DMA_SPDIF_ADDRESS,
	[PCM_MULTICH] = OXYGEN_DMA_MULTICH_ADDRESS,
	[PCM_AC97] = OXYGEN_DMA_AC97_ADDRESS,
पूर्ण;

अटल पूर्णांक oxygen_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक channel = oxygen_substream_channel(substream);

	oxygen_ग_लिखो32(chip, channel_base_रेजिस्टरs[channel],
		       (u32)substream->runसमय->dma_addr);
	अगर (channel == PCM_MULTICH) अणु
		oxygen_ग_लिखो32(chip, OXYGEN_DMA_MULTICH_COUNT,
			       params_buffer_bytes(hw_params) / 4 - 1);
		oxygen_ग_लिखो32(chip, OXYGEN_DMA_MULTICH_TCOUNT,
			       params_period_bytes(hw_params) / 4 - 1);
	पूर्ण अन्यथा अणु
		oxygen_ग_लिखो16(chip, channel_base_रेजिस्टरs[channel] + 4,
			       params_buffer_bytes(hw_params) / 4 - 1);
		oxygen_ग_लिखो16(chip, channel_base_रेजिस्टरs[channel] + 6,
			       params_period_bytes(hw_params) / 4 - 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 get_mclk(काष्ठा oxygen *chip, अचिन्हित पूर्णांक channel,
		    काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक mclks, shअगरt;

	अगर (channel == PCM_MULTICH)
		mclks = chip->model.dac_mclks;
	अन्यथा
		mclks = chip->model.adc_mclks;

	अगर (params_rate(params) <= 48000)
		shअगरt = 0;
	अन्यथा अगर (params_rate(params) <= 96000)
		shअगरt = 2;
	अन्यथा
		shअगरt = 4;

	वापस OXYGEN_I2S_MCLK(mclks >> shअगरt);
पूर्ण

अटल पूर्णांक oxygen_rec_a_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	err = oxygen_hw_params(substream, hw_params);
	अगर (err < 0)
		वापस err;

	spin_lock_irq(&chip->reg_lock);
	oxygen_ग_लिखो8_masked(chip, OXYGEN_REC_FORMAT,
			     oxygen_क्रमmat(hw_params) << OXYGEN_REC_FORMAT_A_SHIFT,
			     OXYGEN_REC_FORMAT_A_MASK);
	oxygen_ग_लिखो16_masked(chip, OXYGEN_I2S_A_FORMAT,
			      oxygen_rate(hw_params) |
			      chip->model.adc_i2s_क्रमmat |
			      get_mclk(chip, PCM_A, hw_params) |
			      oxygen_i2s_bits(hw_params),
			      OXYGEN_I2S_RATE_MASK |
			      OXYGEN_I2S_FORMAT_MASK |
			      OXYGEN_I2S_MCLK_MASK |
			      OXYGEN_I2S_BITS_MASK);
	spin_unlock_irq(&chip->reg_lock);

	mutex_lock(&chip->mutex);
	chip->model.set_adc_params(chip, hw_params);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_rec_b_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	पूर्णांक is_ac97;
	पूर्णांक err;

	err = oxygen_hw_params(substream, hw_params);
	अगर (err < 0)
		वापस err;

	is_ac97 = chip->has_ac97_1 &&
		(chip->model.device_config & CAPTURE_2_FROM_AC97_1);

	spin_lock_irq(&chip->reg_lock);
	oxygen_ग_लिखो8_masked(chip, OXYGEN_REC_FORMAT,
			     oxygen_क्रमmat(hw_params) << OXYGEN_REC_FORMAT_B_SHIFT,
			     OXYGEN_REC_FORMAT_B_MASK);
	अगर (!is_ac97)
		oxygen_ग_लिखो16_masked(chip, OXYGEN_I2S_B_FORMAT,
				      oxygen_rate(hw_params) |
				      chip->model.adc_i2s_क्रमmat |
				      get_mclk(chip, PCM_B, hw_params) |
				      oxygen_i2s_bits(hw_params),
				      OXYGEN_I2S_RATE_MASK |
				      OXYGEN_I2S_FORMAT_MASK |
				      OXYGEN_I2S_MCLK_MASK |
				      OXYGEN_I2S_BITS_MASK);
	spin_unlock_irq(&chip->reg_lock);

	अगर (!is_ac97) अणु
		mutex_lock(&chip->mutex);
		chip->model.set_adc_params(chip, hw_params);
		mutex_unlock(&chip->mutex);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_rec_c_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	bool is_spdअगर;
	पूर्णांक err;

	err = oxygen_hw_params(substream, hw_params);
	अगर (err < 0)
		वापस err;

	is_spdअगर = chip->model.device_config & CAPTURE_1_FROM_SPDIF;

	spin_lock_irq(&chip->reg_lock);
	oxygen_ग_लिखो8_masked(chip, OXYGEN_REC_FORMAT,
			     oxygen_क्रमmat(hw_params) << OXYGEN_REC_FORMAT_C_SHIFT,
			     OXYGEN_REC_FORMAT_C_MASK);
	अगर (!is_spdअगर)
		oxygen_ग_लिखो16_masked(chip, OXYGEN_I2S_C_FORMAT,
				      oxygen_rate(hw_params) |
				      chip->model.adc_i2s_क्रमmat |
				      get_mclk(chip, PCM_B, hw_params) |
				      oxygen_i2s_bits(hw_params),
				      OXYGEN_I2S_RATE_MASK |
				      OXYGEN_I2S_FORMAT_MASK |
				      OXYGEN_I2S_MCLK_MASK |
				      OXYGEN_I2S_BITS_MASK);
	spin_unlock_irq(&chip->reg_lock);

	अगर (!is_spdअगर) अणु
		mutex_lock(&chip->mutex);
		chip->model.set_adc_params(chip, hw_params);
		mutex_unlock(&chip->mutex);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	err = oxygen_hw_params(substream, hw_params);
	अगर (err < 0)
		वापस err;

	mutex_lock(&chip->mutex);
	spin_lock_irq(&chip->reg_lock);
	oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
			    OXYGEN_SPDIF_OUT_ENABLE);
	oxygen_ग_लिखो8_masked(chip, OXYGEN_PLAY_FORMAT,
			     oxygen_क्रमmat(hw_params) << OXYGEN_SPDIF_FORMAT_SHIFT,
			     OXYGEN_SPDIF_FORMAT_MASK);
	oxygen_ग_लिखो32_masked(chip, OXYGEN_SPDIF_CONTROL,
			      oxygen_rate(hw_params) << OXYGEN_SPDIF_OUT_RATE_SHIFT,
			      OXYGEN_SPDIF_OUT_RATE_MASK);
	oxygen_update_spdअगर_source(chip);
	spin_unlock_irq(&chip->reg_lock);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_multich_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	पूर्णांक err;

	err = oxygen_hw_params(substream, hw_params);
	अगर (err < 0)
		वापस err;

	mutex_lock(&chip->mutex);
	spin_lock_irq(&chip->reg_lock);
	oxygen_ग_लिखो8_masked(chip, OXYGEN_PLAY_CHANNELS,
			     oxygen_play_channels(hw_params),
			     OXYGEN_PLAY_CHANNELS_MASK);
	oxygen_ग_लिखो8_masked(chip, OXYGEN_PLAY_FORMAT,
			     oxygen_क्रमmat(hw_params) << OXYGEN_MULTICH_FORMAT_SHIFT,
			     OXYGEN_MULTICH_FORMAT_MASK);
	oxygen_ग_लिखो16_masked(chip, OXYGEN_I2S_MULTICH_FORMAT,
			      oxygen_rate(hw_params) |
			      chip->model.dac_i2s_क्रमmat |
			      get_mclk(chip, PCM_MULTICH, hw_params) |
			      oxygen_i2s_bits(hw_params),
			      OXYGEN_I2S_RATE_MASK |
			      OXYGEN_I2S_FORMAT_MASK |
			      OXYGEN_I2S_MCLK_MASK |
			      OXYGEN_I2S_BITS_MASK);
	oxygen_update_spdअगर_source(chip);
	spin_unlock_irq(&chip->reg_lock);

	chip->model.set_dac_params(chip, hw_params);
	oxygen_update_dac_routing(chip);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक channel = oxygen_substream_channel(substream);
	अचिन्हित पूर्णांक channel_mask = 1 << channel;

	spin_lock_irq(&chip->reg_lock);
	chip->पूर्णांकerrupt_mask &= ~channel_mask;
	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, chip->पूर्णांकerrupt_mask);

	oxygen_set_bits8(chip, OXYGEN_DMA_FLUSH, channel_mask);
	oxygen_clear_bits8(chip, OXYGEN_DMA_FLUSH, channel_mask);
	spin_unlock_irq(&chip->reg_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_spdअगर_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
			    OXYGEN_SPDIF_OUT_ENABLE);
	spin_unlock_irq(&chip->reg_lock);
	वापस oxygen_hw_मुक्त(substream);
पूर्ण

अटल पूर्णांक oxygen_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक channel = oxygen_substream_channel(substream);
	अचिन्हित पूर्णांक channel_mask = 1 << channel;

	spin_lock_irq(&chip->reg_lock);
	oxygen_set_bits8(chip, OXYGEN_DMA_FLUSH, channel_mask);
	oxygen_clear_bits8(chip, OXYGEN_DMA_FLUSH, channel_mask);

	अगर (substream->runसमय->no_period_wakeup)
		chip->पूर्णांकerrupt_mask &= ~channel_mask;
	अन्यथा
		chip->पूर्णांकerrupt_mask |= channel_mask;
	oxygen_ग_लिखो16(chip, OXYGEN_INTERRUPT_MASK, chip->पूर्णांकerrupt_mask);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक oxygen_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;
	अचिन्हित पूर्णांक mask = 0;
	पूर्णांक pausing;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		pausing = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		pausing = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (snd_pcm_substream_chip(s) == chip) अणु
			mask |= 1 << oxygen_substream_channel(s);
			snd_pcm_trigger_करोne(s, substream);
		पूर्ण
	पूर्ण

	spin_lock(&chip->reg_lock);
	अगर (!pausing) अणु
		अगर (cmd == SNDRV_PCM_TRIGGER_START)
			chip->pcm_running |= mask;
		अन्यथा
			chip->pcm_running &= ~mask;
		oxygen_ग_लिखो8(chip, OXYGEN_DMA_STATUS, chip->pcm_running);
	पूर्ण अन्यथा अणु
		अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_PUSH)
			oxygen_set_bits8(chip, OXYGEN_DMA_PAUSE, mask);
		अन्यथा
			oxygen_clear_bits8(chip, OXYGEN_DMA_PAUSE, mask);
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t oxygen_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा oxygen *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक channel = oxygen_substream_channel(substream);
	u32 curr_addr;

	/* no spinlock, this पढ़ो should be atomic */
	curr_addr = oxygen_पढ़ो32(chip, channel_base_रेजिस्टरs[channel]);
	वापस bytes_to_frames(runसमय, curr_addr - (u32)runसमय->dma_addr);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops oxygen_rec_a_ops = अणु
	.खोलो      = oxygen_rec_a_खोलो,
	.बंद     = oxygen_बंद,
	.hw_params = oxygen_rec_a_hw_params,
	.hw_मुक्त   = oxygen_hw_मुक्त,
	.prepare   = oxygen_prepare,
	.trigger   = oxygen_trigger,
	.poपूर्णांकer   = oxygen_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops oxygen_rec_b_ops = अणु
	.खोलो      = oxygen_rec_b_खोलो,
	.बंद     = oxygen_बंद,
	.hw_params = oxygen_rec_b_hw_params,
	.hw_मुक्त   = oxygen_hw_मुक्त,
	.prepare   = oxygen_prepare,
	.trigger   = oxygen_trigger,
	.poपूर्णांकer   = oxygen_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops oxygen_rec_c_ops = अणु
	.खोलो      = oxygen_rec_c_खोलो,
	.बंद     = oxygen_बंद,
	.hw_params = oxygen_rec_c_hw_params,
	.hw_मुक्त   = oxygen_hw_मुक्त,
	.prepare   = oxygen_prepare,
	.trigger   = oxygen_trigger,
	.poपूर्णांकer   = oxygen_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops oxygen_spdअगर_ops = अणु
	.खोलो      = oxygen_spdअगर_खोलो,
	.बंद     = oxygen_बंद,
	.hw_params = oxygen_spdअगर_hw_params,
	.hw_मुक्त   = oxygen_spdअगर_hw_मुक्त,
	.prepare   = oxygen_prepare,
	.trigger   = oxygen_trigger,
	.poपूर्णांकer   = oxygen_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops oxygen_multich_ops = अणु
	.खोलो      = oxygen_multich_खोलो,
	.बंद     = oxygen_बंद,
	.hw_params = oxygen_multich_hw_params,
	.hw_मुक्त   = oxygen_hw_मुक्त,
	.prepare   = oxygen_prepare,
	.trigger   = oxygen_trigger,
	.poपूर्णांकer   = oxygen_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops oxygen_ac97_ops = अणु
	.खोलो      = oxygen_ac97_खोलो,
	.बंद     = oxygen_बंद,
	.hw_params = oxygen_hw_params,
	.hw_मुक्त   = oxygen_hw_मुक्त,
	.prepare   = oxygen_prepare,
	.trigger   = oxygen_trigger,
	.poपूर्णांकer   = oxygen_poपूर्णांकer,
पूर्ण;

पूर्णांक oxygen_pcm_init(काष्ठा oxygen *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक outs, ins;
	पूर्णांक err;

	outs = !!(chip->model.device_config & PLAYBACK_0_TO_I2S);
	ins = !!(chip->model.device_config & (CAPTURE_0_FROM_I2S_1 |
					      CAPTURE_0_FROM_I2S_2));
	अगर (outs | ins) अणु
		err = snd_pcm_new(chip->card, "Multichannel",
				  0, outs, ins, &pcm);
		अगर (err < 0)
			वापस err;
		अगर (outs)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					&oxygen_multich_ops);
		अगर (chip->model.device_config & CAPTURE_0_FROM_I2S_1)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
					&oxygen_rec_a_ops);
		अन्यथा अगर (chip->model.device_config & CAPTURE_0_FROM_I2S_2)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
					&oxygen_rec_b_ops);
		pcm->निजी_data = chip;
		म_नकल(pcm->name, "Multichannel");
		अगर (outs)
			snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream,
						   SNDRV_DMA_TYPE_DEV,
						   &chip->pci->dev,
						   DEFAULT_BUFFER_BYTES_MULTICH,
						   BUFFER_BYTES_MAX_MULTICH);
		अगर (ins)
			snd_pcm_set_managed_buffer(pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream,
						   SNDRV_DMA_TYPE_DEV,
						   &chip->pci->dev,
						   DEFAULT_BUFFER_BYTES,
						   BUFFER_BYTES_MAX);
	पूर्ण

	outs = !!(chip->model.device_config & PLAYBACK_1_TO_SPDIF);
	ins = !!(chip->model.device_config & CAPTURE_1_FROM_SPDIF);
	अगर (outs | ins) अणु
		err = snd_pcm_new(chip->card, "Digital", 1, outs, ins, &pcm);
		अगर (err < 0)
			वापस err;
		अगर (outs)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					&oxygen_spdअगर_ops);
		अगर (ins)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
					&oxygen_rec_c_ops);
		pcm->निजी_data = chip;
		म_नकल(pcm->name, "Digital");
		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
					       &chip->pci->dev,
					       DEFAULT_BUFFER_BYTES,
					       BUFFER_BYTES_MAX);
	पूर्ण

	अगर (chip->has_ac97_1) अणु
		outs = !!(chip->model.device_config & PLAYBACK_2_TO_AC97_1);
		ins = !!(chip->model.device_config & CAPTURE_2_FROM_AC97_1);
	पूर्ण अन्यथा अणु
		outs = 0;
		ins = !!(chip->model.device_config & CAPTURE_2_FROM_I2S_2);
	पूर्ण
	अगर (outs | ins) अणु
		err = snd_pcm_new(chip->card, outs ? "AC97" : "Analog2",
				  2, outs, ins, &pcm);
		अगर (err < 0)
			वापस err;
		अगर (outs) अणु
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					&oxygen_ac97_ops);
			oxygen_ग_लिखो8_masked(chip, OXYGEN_REC_ROUTING,
					     OXYGEN_REC_B_ROUTE_AC97_1,
					     OXYGEN_REC_B_ROUTE_MASK);
		पूर्ण
		अगर (ins)
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
					&oxygen_rec_b_ops);
		pcm->निजी_data = chip;
		म_नकल(pcm->name, outs ? "Front Panel" : "Analog 2");
		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
					       &chip->pci->dev,
					       DEFAULT_BUFFER_BYTES,
					       BUFFER_BYTES_MAX);
	पूर्ण

	ins = !!(chip->model.device_config & CAPTURE_3_FROM_I2S_3);
	अगर (ins) अणु
		err = snd_pcm_new(chip->card, "Analog3", 3, 0, ins, &pcm);
		अगर (err < 0)
			वापस err;
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&oxygen_rec_c_ops);
		oxygen_ग_लिखो8_masked(chip, OXYGEN_REC_ROUTING,
				     OXYGEN_REC_C_ROUTE_I2S_ADC_3,
				     OXYGEN_REC_C_ROUTE_MASK);
		pcm->निजी_data = chip;
		म_नकल(pcm->name, "Analog 3");
		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
					       &chip->pci->dev,
					       DEFAULT_BUFFER_BYTES,
					       BUFFER_BYTES_MAX);
	पूर्ण
	वापस 0;
पूर्ण
