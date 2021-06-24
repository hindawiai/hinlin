<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * card driver क्रम models with WM8776/WM8766 DACs (Xonar DS/HDAV1.3 Slim)
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

/*
 * Xonar DS
 * --------
 *
 * CMI8788:
 *
 *   SPI 0 -> WM8766 (surround, center/LFE, back)
 *   SPI 1 -> WM8776 (front, input)
 *
 *   GPIO 4 <- headphone detect, 0 = plugged
 *   GPIO 6 -> route input jack to mic-in (0) or line-in (1)
 *   GPIO 7 -> enable output to front L/R speaker channels
 *   GPIO 8 -> enable output to other speaker channels and front panel headphone
 *
 * WM8776:
 *
 *   input 1 <- line
 *   input 2 <- mic
 *   input 3 <- front mic
 *   input 4 <- aux
 */

/*
 * Xonar HDAV1.3 Slim
 * ------------------
 *
 * CMI8788:
 *
 *   IतऑC <-> WM8776 (addr 0011010)
 *
 *   GPIO 0  -> disable HDMI output
 *   GPIO 1  -> enable HP output
 *   GPIO 6  -> firmware EEPROM IतऑC घड़ी
 *   GPIO 7 <-> firmware EEPROM IतऑC data
 *
 *   UART <-> HDMI controller
 *
 * WM8776:
 *
 *   input 1 <- mic
 *   input 2 <- aux
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश "xonar.h"
#समावेश "wm8776.h"
#समावेश "wm8766.h"

#घोषणा GPIO_DS_HP_DETECT	0x0010
#घोषणा GPIO_DS_INPUT_ROUTE	0x0040
#घोषणा GPIO_DS_OUTPUT_FRONTLR	0x0080
#घोषणा GPIO_DS_OUTPUT_ENABLE	0x0100

#घोषणा GPIO_SLIM_HDMI_DISABLE	0x0001
#घोषणा GPIO_SLIM_OUTPUT_ENABLE	0x0002
#घोषणा GPIO_SLIM_FIRMWARE_CLK	0x0040
#घोषणा GPIO_SLIM_FIRMWARE_DATA	0x0080

#घोषणा I2C_DEVICE_WM8776	0x34	/* 001101, 0, /W=0 */

#घोषणा LC_CONTROL_LIMITER	0x40000000
#घोषणा LC_CONTROL_ALC		0x20000000

काष्ठा xonar_wm87x6 अणु
	काष्ठा xonar_generic generic;
	u16 wm8776_regs[0x17];
	u16 wm8766_regs[0x10];
	काष्ठा snd_kcontrol *line_adcmux_control;
	काष्ठा snd_kcontrol *mic_adcmux_control;
	काष्ठा snd_kcontrol *lc_controls[13];
	काष्ठा snd_jack *hp_jack;
	काष्ठा xonar_hdmi hdmi;
पूर्ण;

अटल व्योम wm8776_ग_लिखो_spi(काष्ठा oxygen *chip,
			     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER |
			 OXYGEN_SPI_DATA_LENGTH_2 |
			 OXYGEN_SPI_CLOCK_160 |
			 (1 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_LATCH_CLOCK_LO,
			 (reg << 9) | value);
पूर्ण

अटल व्योम wm8776_ग_लिखो_i2c(काष्ठा oxygen *chip,
			     अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	oxygen_ग_लिखो_i2c(chip, I2C_DEVICE_WM8776,
			 (reg << 1) | (value >> 8), value);
पूर्ण

अटल व्योम wm8776_ग_लिखो(काष्ठा oxygen *chip,
			 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	अगर ((chip->model.function_flags & OXYGEN_FUNCTION_2WIRE_SPI_MASK) ==
	    OXYGEN_FUNCTION_SPI)
		wm8776_ग_लिखो_spi(chip, reg, value);
	अन्यथा
		wm8776_ग_लिखो_i2c(chip, reg, value);
	अगर (reg < ARRAY_SIZE(data->wm8776_regs)) अणु
		/* reg >= WM8776_HPLVOL is always true */
		अगर (reg <= WM8776_DACMASTER)
			value &= ~WM8776_UPDATE;
		data->wm8776_regs[reg] = value;
	पूर्ण
पूर्ण

अटल व्योम wm8776_ग_लिखो_cached(काष्ठा oxygen *chip,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	अगर (reg >= ARRAY_SIZE(data->wm8776_regs) ||
	    value != data->wm8776_regs[reg])
		wm8776_ग_लिखो(chip, reg, value);
पूर्ण

अटल व्योम wm8766_ग_लिखो(काष्ठा oxygen *chip,
			 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER |
			 OXYGEN_SPI_DATA_LENGTH_2 |
			 OXYGEN_SPI_CLOCK_160 |
			 (0 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_LATCH_CLOCK_LO,
			 (reg << 9) | value);
	अगर (reg < ARRAY_SIZE(data->wm8766_regs)) अणु
		/* reg >= WM8766_LDA1 is always true */
		अगर (reg <= WM8766_RDA1 ||
		    (reg >= WM8766_LDA2 && reg <= WM8766_MASTDA))
			value &= ~WM8766_UPDATE;
		data->wm8766_regs[reg] = value;
	पूर्ण
पूर्ण

अटल व्योम wm8766_ग_लिखो_cached(काष्ठा oxygen *chip,
				अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	अगर (reg >= ARRAY_SIZE(data->wm8766_regs) ||
	    value != data->wm8766_regs[reg])
		wm8766_ग_लिखो(chip, reg, value);
पूर्ण

अटल व्योम wm8776_रेजिस्टरs_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	wm8776_ग_लिखो(chip, WM8776_RESET, 0);
	wm8776_ग_लिखो(chip, WM8776_PHASESWAP, WM8776_PH_MASK);
	wm8776_ग_लिखो(chip, WM8776_DACCTRL1, WM8776_DZCEN |
		     WM8776_PL_LEFT_LEFT | WM8776_PL_RIGHT_RIGHT);
	wm8776_ग_लिखो(chip, WM8776_DACMUTE, chip->dac_mute ? WM8776_DMUTE : 0);
	wm8776_ग_लिखो(chip, WM8776_DACIFCTRL,
		     WM8776_DACFMT_LJUST | WM8776_DACWL_24);
	wm8776_ग_लिखो(chip, WM8776_ADCIFCTRL,
		     data->wm8776_regs[WM8776_ADCIFCTRL]);
	wm8776_ग_लिखो(chip, WM8776_MSTRCTRL, data->wm8776_regs[WM8776_MSTRCTRL]);
	wm8776_ग_लिखो(chip, WM8776_PWRDOWN, data->wm8776_regs[WM8776_PWRDOWN]);
	wm8776_ग_लिखो(chip, WM8776_HPLVOL, data->wm8776_regs[WM8776_HPLVOL]);
	wm8776_ग_लिखो(chip, WM8776_HPRVOL, data->wm8776_regs[WM8776_HPRVOL] |
		     WM8776_UPDATE);
	wm8776_ग_लिखो(chip, WM8776_ADCLVOL, data->wm8776_regs[WM8776_ADCLVOL]);
	wm8776_ग_लिखो(chip, WM8776_ADCRVOL, data->wm8776_regs[WM8776_ADCRVOL]);
	wm8776_ग_लिखो(chip, WM8776_ADCMUX, data->wm8776_regs[WM8776_ADCMUX]);
	wm8776_ग_लिखो(chip, WM8776_DACLVOL, chip->dac_volume[0]);
	wm8776_ग_लिखो(chip, WM8776_DACRVOL, chip->dac_volume[1] | WM8776_UPDATE);
पूर्ण

अटल व्योम wm8766_रेजिस्टरs_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	wm8766_ग_लिखो(chip, WM8766_RESET, 0);
	wm8766_ग_लिखो(chip, WM8766_DAC_CTRL, data->wm8766_regs[WM8766_DAC_CTRL]);
	wm8766_ग_लिखो(chip, WM8766_INT_CTRL, WM8766_FMT_LJUST | WM8766_IWL_24);
	wm8766_ग_लिखो(chip, WM8766_DAC_CTRL2,
		     WM8766_ZCD | (chip->dac_mute ? WM8766_DMUTE_MASK : 0));
	wm8766_ग_लिखो(chip, WM8766_LDA1, chip->dac_volume[2]);
	wm8766_ग_लिखो(chip, WM8766_RDA1, chip->dac_volume[3]);
	wm8766_ग_लिखो(chip, WM8766_LDA2, chip->dac_volume[4]);
	wm8766_ग_लिखो(chip, WM8766_RDA2, chip->dac_volume[5]);
	wm8766_ग_लिखो(chip, WM8766_LDA3, chip->dac_volume[6]);
	wm8766_ग_लिखो(chip, WM8766_RDA3, chip->dac_volume[7] | WM8766_UPDATE);
पूर्ण

अटल व्योम wm8776_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	data->wm8776_regs[WM8776_HPLVOL] = (0x79 - 60) | WM8776_HPZCEN;
	data->wm8776_regs[WM8776_HPRVOL] = (0x79 - 60) | WM8776_HPZCEN;
	data->wm8776_regs[WM8776_ADCIFCTRL] =
		WM8776_ADCFMT_LJUST | WM8776_ADCWL_24 | WM8776_ADCMCLK;
	data->wm8776_regs[WM8776_MSTRCTRL] =
		WM8776_ADCRATE_256 | WM8776_DACRATE_256;
	data->wm8776_regs[WM8776_PWRDOWN] = WM8776_HPPD;
	data->wm8776_regs[WM8776_ADCLVOL] = 0xa5 | WM8776_ZCA;
	data->wm8776_regs[WM8776_ADCRVOL] = 0xa5 | WM8776_ZCA;
	data->wm8776_regs[WM8776_ADCMUX] = 0x001;
	wm8776_रेजिस्टरs_init(chip);
पूर्ण

अटल व्योम wm8766_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	data->wm8766_regs[WM8766_DAC_CTRL] =
		WM8766_PL_LEFT_LEFT | WM8766_PL_RIGHT_RIGHT;
	wm8766_रेजिस्टरs_init(chip);
पूर्ण

अटल व्योम xonar_ds_handle_hp_jack(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	bool hp_plugged;
	अचिन्हित पूर्णांक reg;

	mutex_lock(&chip->mutex);

	hp_plugged = !(oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA) &
		       GPIO_DS_HP_DETECT);

	oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
			      hp_plugged ? 0 : GPIO_DS_OUTPUT_FRONTLR,
			      GPIO_DS_OUTPUT_FRONTLR);

	reg = data->wm8766_regs[WM8766_DAC_CTRL] & ~WM8766_MUTEALL;
	अगर (hp_plugged)
		reg |= WM8766_MUTEALL;
	wm8766_ग_लिखो_cached(chip, WM8766_DAC_CTRL, reg);

	snd_jack_report(data->hp_jack, hp_plugged ? SND_JACK_HEADPHONE : 0);

	mutex_unlock(&chip->mutex);
पूर्ण

अटल व्योम xonar_ds_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	data->generic.anti_pop_delay = 300;
	data->generic.output_enable_bit = GPIO_DS_OUTPUT_ENABLE;

	wm8776_init(chip);
	wm8766_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_DS_INPUT_ROUTE | GPIO_DS_OUTPUT_FRONTLR);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL,
			    GPIO_DS_HP_DETECT);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, GPIO_DS_INPUT_ROUTE);
	oxygen_set_bits16(chip, OXYGEN_GPIO_INTERRUPT_MASK, GPIO_DS_HP_DETECT);
	chip->पूर्णांकerrupt_mask |= OXYGEN_INT_GPIO;

	xonar_enable_output(chip);

	snd_jack_new(chip->card, "Headphone",
		     SND_JACK_HEADPHONE, &data->hp_jack, false, false);
	xonar_ds_handle_hp_jack(chip);

	snd_component_add(chip->card, "WM8776");
	snd_component_add(chip->card, "WM8766");
पूर्ण

अटल व्योम xonar_hdav_slim_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	data->generic.anti_pop_delay = 300;
	data->generic.output_enable_bit = GPIO_SLIM_OUTPUT_ENABLE;

	wm8776_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_SLIM_HDMI_DISABLE |
			  GPIO_SLIM_FIRMWARE_CLK |
			  GPIO_SLIM_FIRMWARE_DATA);

	xonar_hdmi_init(chip, &data->hdmi);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "WM8776");
पूर्ण

अटल व्योम xonar_ds_cleanup(काष्ठा oxygen *chip)
अणु
	xonar_disable_output(chip);
	wm8776_ग_लिखो(chip, WM8776_RESET, 0);
पूर्ण

अटल व्योम xonar_hdav_slim_cleanup(काष्ठा oxygen *chip)
अणु
	xonar_hdmi_cleanup(chip);
	xonar_disable_output(chip);
	wm8776_ग_लिखो(chip, WM8776_RESET, 0);
	msleep(2);
पूर्ण

अटल व्योम xonar_ds_suspend(काष्ठा oxygen *chip)
अणु
	xonar_ds_cleanup(chip);
पूर्ण

अटल व्योम xonar_hdav_slim_suspend(काष्ठा oxygen *chip)
अणु
	xonar_hdav_slim_cleanup(chip);
पूर्ण

अटल व्योम xonar_ds_resume(काष्ठा oxygen *chip)
अणु
	wm8776_रेजिस्टरs_init(chip);
	wm8766_रेजिस्टरs_init(chip);
	xonar_enable_output(chip);
	xonar_ds_handle_hp_jack(chip);
पूर्ण

अटल व्योम xonar_hdav_slim_resume(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	wm8776_रेजिस्टरs_init(chip);
	xonar_hdmi_resume(chip, &data->hdmi);
	xonar_enable_output(chip);
पूर्ण

अटल व्योम wm8776_adc_hardware_filter(अचिन्हित पूर्णांक channel,
				       काष्ठा snd_pcm_hardware *hardware)
अणु
	अगर (channel == PCM_A) अणु
		hardware->rates = SNDRV_PCM_RATE_32000 |
				  SNDRV_PCM_RATE_44100 |
				  SNDRV_PCM_RATE_48000 |
				  SNDRV_PCM_RATE_64000 |
				  SNDRV_PCM_RATE_88200 |
				  SNDRV_PCM_RATE_96000;
		hardware->rate_max = 96000;
	पूर्ण
पूर्ण

अटल व्योम xonar_hdav_slim_hardware_filter(अचिन्हित पूर्णांक channel,
					    काष्ठा snd_pcm_hardware *hardware)
अणु
	wm8776_adc_hardware_filter(channel, hardware);
	xonar_hdmi_pcm_hardware_filter(channel, hardware);
पूर्ण

अटल व्योम set_wm87x6_dac_params(काष्ठा oxygen *chip,
				  काष्ठा snd_pcm_hw_params *params)
अणु
पूर्ण

अटल व्योम set_wm8776_adc_params(काष्ठा oxygen *chip,
				  काष्ठा snd_pcm_hw_params *params)
अणु
	u16 reg;

	reg = WM8776_ADCRATE_256 | WM8776_DACRATE_256;
	अगर (params_rate(params) > 48000)
		reg |= WM8776_ADCOSR;
	wm8776_ग_लिखो_cached(chip, WM8776_MSTRCTRL, reg);
पूर्ण

अटल व्योम set_hdav_slim_dac_params(काष्ठा oxygen *chip,
				     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	xonar_set_hdmi_params(chip, &data->hdmi, params);
पूर्ण

अटल व्योम update_wm8776_volume(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	u8 to_change;

	अगर (chip->dac_volume[0] == chip->dac_volume[1]) अणु
		अगर (chip->dac_volume[0] != data->wm8776_regs[WM8776_DACLVOL] ||
		    chip->dac_volume[1] != data->wm8776_regs[WM8776_DACRVOL]) अणु
			wm8776_ग_लिखो(chip, WM8776_DACMASTER,
				     chip->dac_volume[0] | WM8776_UPDATE);
			data->wm8776_regs[WM8776_DACLVOL] = chip->dac_volume[0];
			data->wm8776_regs[WM8776_DACRVOL] = chip->dac_volume[0];
		पूर्ण
	पूर्ण अन्यथा अणु
		to_change = (chip->dac_volume[0] !=
			     data->wm8776_regs[WM8776_DACLVOL]) << 0;
		to_change |= (chip->dac_volume[1] !=
			      data->wm8776_regs[WM8776_DACLVOL]) << 1;
		अगर (to_change & 1)
			wm8776_ग_लिखो(chip, WM8776_DACLVOL, chip->dac_volume[0] |
				     ((to_change & 2) ? 0 : WM8776_UPDATE));
		अगर (to_change & 2)
			wm8776_ग_लिखो(chip, WM8776_DACRVOL,
				     chip->dac_volume[1] | WM8776_UPDATE);
	पूर्ण
पूर्ण

अटल व्योम update_wm87x6_volume(काष्ठा oxygen *chip)
अणु
	अटल स्थिर u8 wm8766_regs[6] = अणु
		WM8766_LDA1, WM8766_RDA1,
		WM8766_LDA2, WM8766_RDA2,
		WM8766_LDA3, WM8766_RDA3,
	पूर्ण;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	u8 to_change;

	update_wm8776_volume(chip);
	अगर (chip->dac_volume[2] == chip->dac_volume[3] &&
	    chip->dac_volume[2] == chip->dac_volume[4] &&
	    chip->dac_volume[2] == chip->dac_volume[5] &&
	    chip->dac_volume[2] == chip->dac_volume[6] &&
	    chip->dac_volume[2] == chip->dac_volume[7]) अणु
		to_change = 0;
		क्रम (i = 0; i < 6; ++i)
			अगर (chip->dac_volume[2] !=
			    data->wm8766_regs[wm8766_regs[i]])
				to_change = 1;
		अगर (to_change) अणु
			wm8766_ग_लिखो(chip, WM8766_MASTDA,
				     chip->dac_volume[2] | WM8766_UPDATE);
			क्रम (i = 0; i < 6; ++i)
				data->wm8766_regs[wm8766_regs[i]] =
					chip->dac_volume[2];
		पूर्ण
	पूर्ण अन्यथा अणु
		to_change = 0;
		क्रम (i = 0; i < 6; ++i)
			to_change |= (chip->dac_volume[2 + i] !=
				      data->wm8766_regs[wm8766_regs[i]]) << i;
		क्रम (i = 0; i < 6; ++i)
			अगर (to_change & (1 << i))
				wm8766_ग_लिखो(chip, wm8766_regs[i],
					     chip->dac_volume[2 + i] |
					     ((to_change & (0x3e << i))
					      ? 0 : WM8766_UPDATE));
	पूर्ण
पूर्ण

अटल व्योम update_wm8776_mute(काष्ठा oxygen *chip)
अणु
	wm8776_ग_लिखो_cached(chip, WM8776_DACMUTE,
			    chip->dac_mute ? WM8776_DMUTE : 0);
पूर्ण

अटल व्योम update_wm87x6_mute(काष्ठा oxygen *chip)
अणु
	update_wm8776_mute(chip);
	wm8766_ग_लिखो_cached(chip, WM8766_DAC_CTRL2, WM8766_ZCD |
			    (chip->dac_mute ? WM8766_DMUTE_MASK : 0));
पूर्ण

अटल व्योम update_wm8766_center_lfe_mix(काष्ठा oxygen *chip, bool mixed)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक reg;

	/*
	 * The WM8766 can mix left and right channels, but this setting
	 * applies to all three stereo pairs.
	 */
	reg = data->wm8766_regs[WM8766_DAC_CTRL] &
		~(WM8766_PL_LEFT_MASK | WM8766_PL_RIGHT_MASK);
	अगर (mixed)
		reg |= WM8766_PL_LEFT_LRMIX | WM8766_PL_RIGHT_LRMIX;
	अन्यथा
		reg |= WM8766_PL_LEFT_LEFT | WM8766_PL_RIGHT_RIGHT;
	wm8766_ग_लिखो_cached(chip, WM8766_DAC_CTRL, reg);
पूर्ण

अटल व्योम xonar_ds_gpio_changed(काष्ठा oxygen *chip)
अणु
	xonar_ds_handle_hp_jack(chip);
पूर्ण

अटल पूर्णांक wm8776_bit_चयन_get(काष्ठा snd_kcontrol *ctl,
				 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	u16 bit = ctl->निजी_value & 0xffff;
	अचिन्हित पूर्णांक reg_index = (ctl->निजी_value >> 16) & 0xff;
	bool invert = (ctl->निजी_value >> 24) & 1;

	value->value.पूर्णांकeger.value[0] =
		((data->wm8776_regs[reg_index] & bit) != 0) ^ invert;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_bit_चयन_put(काष्ठा snd_kcontrol *ctl,
				 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	u16 bit = ctl->निजी_value & 0xffff;
	u16 reg_value;
	अचिन्हित पूर्णांक reg_index = (ctl->निजी_value >> 16) & 0xff;
	bool invert = (ctl->निजी_value >> 24) & 1;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	reg_value = data->wm8776_regs[reg_index] & ~bit;
	अगर (value->value.पूर्णांकeger.value[0] ^ invert)
		reg_value |= bit;
	changed = reg_value != data->wm8776_regs[reg_index];
	अगर (changed)
		wm8776_ग_लिखो(chip, reg_index, reg_value);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक wm8776_field_क्रमागत_info(काष्ठा snd_kcontrol *ctl,
				  काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर hld[16] = अणु
		"0 ms", "2.67 ms", "5.33 ms", "10.6 ms",
		"21.3 ms", "42.7 ms", "85.3 ms", "171 ms",
		"341 ms", "683 ms", "1.37 s", "2.73 s",
		"5.46 s", "10.9 s", "21.8 s", "43.7 s",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर atk_lim[11] = अणु
		"0.25 ms", "0.5 ms", "1 ms", "2 ms",
		"4 ms", "8 ms", "16 ms", "32 ms",
		"64 ms", "128 ms", "256 ms",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर atk_alc[11] = अणु
		"8.40 ms", "16.8 ms", "33.6 ms", "67.2 ms",
		"134 ms", "269 ms", "538 ms", "1.08 s",
		"2.15 s", "4.3 s", "8.6 s",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर dcy_lim[11] = अणु
		"1.2 ms", "2.4 ms", "4.8 ms", "9.6 ms",
		"19.2 ms", "38.4 ms", "76.8 ms", "154 ms",
		"307 ms", "614 ms", "1.23 s",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर dcy_alc[11] = अणु
		"33.5 ms", "67.0 ms", "134 ms", "268 ms",
		"536 ms", "1.07 s", "2.14 s", "4.29 s",
		"8.58 s", "17.2 s", "34.3 s",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर tranwin[8] = अणु
		"0 us", "62.5 us", "125 us", "250 us",
		"500 us", "1 ms", "2 ms", "4 ms",
	पूर्ण;
	u8 max;
	स्थिर अक्षर *स्थिर *names;

	max = (ctl->निजी_value >> 12) & 0xf;
	चयन ((ctl->निजी_value >> 24) & 0x1f) अणु
	हाल WM8776_ALCCTRL2:
		names = hld;
		अवरोध;
	हाल WM8776_ALCCTRL3:
		अगर (((ctl->निजी_value >> 20) & 0xf) == 0) अणु
			अगर (ctl->निजी_value & LC_CONTROL_LIMITER)
				names = atk_lim;
			अन्यथा
				names = atk_alc;
		पूर्ण अन्यथा अणु
			अगर (ctl->निजी_value & LC_CONTROL_LIMITER)
				names = dcy_lim;
			अन्यथा
				names = dcy_alc;
		पूर्ण
		अवरोध;
	हाल WM8776_LIMITER:
		names = tranwin;
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण
	वापस snd_ctl_क्रमागत_info(info, 1, max + 1, names);
पूर्ण

अटल पूर्णांक wm8776_field_volume_info(काष्ठा snd_kcontrol *ctl,
				    काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 1;
	info->value.पूर्णांकeger.min = (ctl->निजी_value >> 8) & 0xf;
	info->value.पूर्णांकeger.max = (ctl->निजी_value >> 12) & 0xf;
	वापस 0;
पूर्ण

अटल व्योम wm8776_field_set_from_ctl(काष्ठा snd_kcontrol *ctl)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक value, reg_index, mode;
	u8 min, max, shअगरt;
	u16 mask, reg_value;
	bool invert;

	अगर ((data->wm8776_regs[WM8776_ALCCTRL1] & WM8776_LCSEL_MASK) ==
	    WM8776_LCSEL_LIMITER)
		mode = LC_CONTROL_LIMITER;
	अन्यथा
		mode = LC_CONTROL_ALC;
	अगर (!(ctl->निजी_value & mode))
		वापस;

	value = ctl->निजी_value & 0xf;
	min = (ctl->निजी_value >> 8) & 0xf;
	max = (ctl->निजी_value >> 12) & 0xf;
	mask = (ctl->निजी_value >> 16) & 0xf;
	shअगरt = (ctl->निजी_value >> 20) & 0xf;
	reg_index = (ctl->निजी_value >> 24) & 0x1f;
	invert = (ctl->निजी_value >> 29) & 0x1;

	अगर (invert)
		value = max - (value - min);
	reg_value = data->wm8776_regs[reg_index];
	reg_value &= ~(mask << shअगरt);
	reg_value |= value << shअगरt;
	wm8776_ग_लिखो_cached(chip, reg_index, reg_value);
पूर्ण

अटल पूर्णांक wm8776_field_set(काष्ठा snd_kcontrol *ctl, अचिन्हित पूर्णांक value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u8 min, max;
	पूर्णांक changed;

	min = (ctl->निजी_value >> 8) & 0xf;
	max = (ctl->निजी_value >> 12) & 0xf;
	अगर (value < min || value > max)
		वापस -EINVAL;
	mutex_lock(&chip->mutex);
	changed = value != (ctl->निजी_value & 0xf);
	अगर (changed) अणु
		ctl->निजी_value = (ctl->निजी_value & ~0xf) | value;
		wm8776_field_set_from_ctl(ctl);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक wm8776_field_क्रमागत_get(काष्ठा snd_kcontrol *ctl,
				 काष्ठा snd_ctl_elem_value *value)
अणु
	value->value.क्रमागतerated.item[0] = ctl->निजी_value & 0xf;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_field_volume_get(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	value->value.पूर्णांकeger.value[0] = ctl->निजी_value & 0xf;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_field_क्रमागत_put(काष्ठा snd_kcontrol *ctl,
				 काष्ठा snd_ctl_elem_value *value)
अणु
	वापस wm8776_field_set(ctl, value->value.क्रमागतerated.item[0]);
पूर्ण

अटल पूर्णांक wm8776_field_volume_put(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	वापस wm8776_field_set(ctl, value->value.पूर्णांकeger.value[0]);
पूर्ण

अटल पूर्णांक wm8776_hp_vol_info(काष्ठा snd_kcontrol *ctl,
			      काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 2;
	info->value.पूर्णांकeger.min = 0x79 - 60;
	info->value.पूर्णांकeger.max = 0x7f;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_hp_vol_get(काष्ठा snd_kcontrol *ctl,
			     काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	mutex_lock(&chip->mutex);
	value->value.पूर्णांकeger.value[0] =
		data->wm8776_regs[WM8776_HPLVOL] & WM8776_HPATT_MASK;
	value->value.पूर्णांकeger.value[1] =
		data->wm8776_regs[WM8776_HPRVOL] & WM8776_HPATT_MASK;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_hp_vol_put(काष्ठा snd_kcontrol *ctl,
			     काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	u8 to_update;

	mutex_lock(&chip->mutex);
	to_update = (value->value.पूर्णांकeger.value[0] !=
		     (data->wm8776_regs[WM8776_HPLVOL] & WM8776_HPATT_MASK))
		<< 0;
	to_update |= (value->value.पूर्णांकeger.value[1] !=
		      (data->wm8776_regs[WM8776_HPRVOL] & WM8776_HPATT_MASK))
		<< 1;
	अगर (value->value.पूर्णांकeger.value[0] == value->value.पूर्णांकeger.value[1]) अणु
		अगर (to_update) अणु
			wm8776_ग_लिखो(chip, WM8776_HPMASTER,
				     value->value.पूर्णांकeger.value[0] |
				     WM8776_HPZCEN | WM8776_UPDATE);
			data->wm8776_regs[WM8776_HPLVOL] =
				value->value.पूर्णांकeger.value[0] | WM8776_HPZCEN;
			data->wm8776_regs[WM8776_HPRVOL] =
				value->value.पूर्णांकeger.value[0] | WM8776_HPZCEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (to_update & 1)
			wm8776_ग_लिखो(chip, WM8776_HPLVOL,
				     value->value.पूर्णांकeger.value[0] |
				     WM8776_HPZCEN |
				     ((to_update & 2) ? 0 : WM8776_UPDATE));
		अगर (to_update & 2)
			wm8776_ग_लिखो(chip, WM8776_HPRVOL,
				     value->value.पूर्णांकeger.value[1] |
				     WM8776_HPZCEN | WM8776_UPDATE);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस to_update != 0;
पूर्ण

अटल पूर्णांक wm8776_input_mux_get(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक mux_bit = ctl->निजी_value;

	value->value.पूर्णांकeger.value[0] =
		!!(data->wm8776_regs[WM8776_ADCMUX] & mux_bit);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_input_mux_put(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	काष्ठा snd_kcontrol *other_ctl;
	अचिन्हित पूर्णांक mux_bit = ctl->निजी_value;
	u16 reg;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	reg = data->wm8776_regs[WM8776_ADCMUX];
	अगर (value->value.पूर्णांकeger.value[0]) अणु
		reg |= mux_bit;
		/* line-in and mic-in are exclusive */
		mux_bit ^= 3;
		अगर (reg & mux_bit) अणु
			reg &= ~mux_bit;
			अगर (mux_bit == 1)
				other_ctl = data->line_adcmux_control;
			अन्यथा
				other_ctl = data->mic_adcmux_control;
			snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
				       &other_ctl->id);
		पूर्ण
	पूर्ण अन्यथा
		reg &= ~mux_bit;
	changed = reg != data->wm8776_regs[WM8776_ADCMUX];
	अगर (changed) अणु
		oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
				      reg & 1 ? GPIO_DS_INPUT_ROUTE : 0,
				      GPIO_DS_INPUT_ROUTE);
		wm8776_ग_लिखो(chip, WM8776_ADCMUX, reg);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक wm8776_input_vol_info(काष्ठा snd_kcontrol *ctl,
				 काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 2;
	info->value.पूर्णांकeger.min = 0xa5;
	info->value.पूर्णांकeger.max = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_input_vol_get(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	mutex_lock(&chip->mutex);
	value->value.पूर्णांकeger.value[0] =
		data->wm8776_regs[WM8776_ADCLVOL] & WM8776_AGMASK;
	value->value.पूर्णांकeger.value[1] =
		data->wm8776_regs[WM8776_ADCRVOL] & WM8776_AGMASK;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_input_vol_put(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	पूर्णांक changed = 0;

	mutex_lock(&chip->mutex);
	changed = (value->value.पूर्णांकeger.value[0] !=
		   (data->wm8776_regs[WM8776_ADCLVOL] & WM8776_AGMASK)) ||
		  (value->value.पूर्णांकeger.value[1] !=
		   (data->wm8776_regs[WM8776_ADCRVOL] & WM8776_AGMASK));
	wm8776_ग_लिखो_cached(chip, WM8776_ADCLVOL,
			    value->value.पूर्णांकeger.value[0] | WM8776_ZCA);
	wm8776_ग_लिखो_cached(chip, WM8776_ADCRVOL,
			    value->value.पूर्णांकeger.value[1] | WM8776_ZCA);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक wm8776_level_control_info(काष्ठा snd_kcontrol *ctl,
				     काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[3] = अणु
		"None", "Peak Limiter", "Automatic Level Control"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 3, names);
पूर्ण

अटल पूर्णांक wm8776_level_control_get(काष्ठा snd_kcontrol *ctl,
				    काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	अगर (!(data->wm8776_regs[WM8776_ALCCTRL2] & WM8776_LCEN))
		value->value.क्रमागतerated.item[0] = 0;
	अन्यथा अगर ((data->wm8776_regs[WM8776_ALCCTRL1] & WM8776_LCSEL_MASK) ==
		 WM8776_LCSEL_LIMITER)
		value->value.क्रमागतerated.item[0] = 1;
	अन्यथा
		value->value.क्रमागतerated.item[0] = 2;
	वापस 0;
पूर्ण

अटल व्योम activate_control(काष्ठा oxygen *chip,
			     काष्ठा snd_kcontrol *ctl, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक access;

	अगर (ctl->निजी_value & mode)
		access = 0;
	अन्यथा
		access = SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	अगर ((ctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_INACTIVE) != access) अणु
		ctl->vd[0].access ^= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_INFO, &ctl->id);
	पूर्ण
पूर्ण

अटल पूर्णांक wm8776_level_control_put(काष्ठा snd_kcontrol *ctl,
				    काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक mode = 0, i;
	u16 ctrl1, ctrl2;
	पूर्णांक changed;

	अगर (value->value.क्रमागतerated.item[0] >= 3)
		वापस -EINVAL;
	mutex_lock(&chip->mutex);
	changed = value->value.क्रमागतerated.item[0] != ctl->निजी_value;
	अगर (changed) अणु
		ctl->निजी_value = value->value.क्रमागतerated.item[0];
		ctrl1 = data->wm8776_regs[WM8776_ALCCTRL1];
		ctrl2 = data->wm8776_regs[WM8776_ALCCTRL2];
		चयन (value->value.क्रमागतerated.item[0]) अणु
		शेष:
			wm8776_ग_लिखो_cached(chip, WM8776_ALCCTRL2,
					    ctrl2 & ~WM8776_LCEN);
			अवरोध;
		हाल 1:
			wm8776_ग_लिखो_cached(chip, WM8776_ALCCTRL1,
					    (ctrl1 & ~WM8776_LCSEL_MASK) |
					    WM8776_LCSEL_LIMITER);
			wm8776_ग_लिखो_cached(chip, WM8776_ALCCTRL2,
					    ctrl2 | WM8776_LCEN);
			mode = LC_CONTROL_LIMITER;
			अवरोध;
		हाल 2:
			wm8776_ग_लिखो_cached(chip, WM8776_ALCCTRL1,
					    (ctrl1 & ~WM8776_LCSEL_MASK) |
					    WM8776_LCSEL_ALC_STEREO);
			wm8776_ग_लिखो_cached(chip, WM8776_ALCCTRL2,
					    ctrl2 | WM8776_LCEN);
			mode = LC_CONTROL_ALC;
			अवरोध;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(data->lc_controls); ++i)
			activate_control(chip, data->lc_controls[i], mode);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक hpf_info(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[2] = अणु
		"None", "High-pass Filter"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक hpf_get(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;

	value->value.क्रमागतerated.item[0] =
		!(data->wm8776_regs[WM8776_ADCIFCTRL] & WM8776_ADCHPD);
	वापस 0;
पूर्ण

अटल पूर्णांक hpf_put(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक reg;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	reg = data->wm8776_regs[WM8776_ADCIFCTRL] & ~WM8776_ADCHPD;
	अगर (!value->value.क्रमागतerated.item[0])
		reg |= WM8776_ADCHPD;
	changed = reg != data->wm8776_regs[WM8776_ADCIFCTRL];
	अगर (changed)
		wm8776_ग_लिखो(chip, WM8776_ADCIFCTRL, reg);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

#घोषणा WM8776_BIT_SWITCH(xname, reg, bit, invert, flags) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.info = snd_ctl_boolean_mono_info, \
	.get = wm8776_bit_चयन_get, \
	.put = wm8776_bit_चयन_put, \
	.निजी_value = ((reg) << 16) | (bit) | ((invert) << 24) | (flags), \
पूर्ण
#घोषणा _WM8776_FIELD_CTL(xname, reg, shअगरt, initval, min, max, mask, flags) \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.निजी_value = (initval) | ((min) << 8) | ((max) << 12) | \
	((mask) << 16) | ((shअगरt) << 20) | ((reg) << 24) | (flags)
#घोषणा WM8776_FIELD_CTL_ENUM(xname, reg, shअगरt, init, min, max, mask, flags) अणु\
	_WM8776_FIELD_CTL(xname " Capture Enum", \
			  reg, shअगरt, init, min, max, mask, flags), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
		  SNDRV_CTL_ELEM_ACCESS_INACTIVE, \
	.info = wm8776_field_क्रमागत_info, \
	.get = wm8776_field_क्रमागत_get, \
	.put = wm8776_field_क्रमागत_put, \
पूर्ण
#घोषणा WM8776_FIELD_CTL_VOLUME(a, b, c, d, e, f, g, h, tlv_p) अणु \
	_WM8776_FIELD_CTL(a " Capture Volume", b, c, d, e, f, g, h), \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
		  SNDRV_CTL_ELEM_ACCESS_INACTIVE | \
		  SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
	.info = wm8776_field_volume_info, \
	.get = wm8776_field_volume_get, \
	.put = wm8776_field_volume_put, \
	.tlv = अणु .p = tlv_p पूर्ण, \
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(wm87x6_dac_db_scale, -6000, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_adc_db_scale, -2100, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_hp_db_scale, -6000, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_lct_db_scale, -1600, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_maxgain_db_scale, 0, 400, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_ngth_db_scale, -7800, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_maxatten_lim_db_scale, -1200, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(wm8776_maxatten_alc_db_scale, -2100, 400, 0);

अटल स्थिर काष्ठा snd_kcontrol_new ds_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphone Playback Volume",
		.info = wm8776_hp_vol_info,
		.get = wm8776_hp_vol_get,
		.put = wm8776_hp_vol_put,
		.tlv = अणु .p = wm8776_hp_db_scale पूर्ण,
	पूर्ण,
	WM8776_BIT_SWITCH("Headphone Playback Switch",
			  WM8776_PWRDOWN, WM8776_HPPD, 1, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Input Capture Volume",
		.info = wm8776_input_vol_info,
		.get = wm8776_input_vol_get,
		.put = wm8776_input_vol_put,
		.tlv = अणु .p = wm8776_adc_db_scale पूर्ण,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Line Capture Switch",
		.info = snd_ctl_boolean_mono_info,
		.get = wm8776_input_mux_get,
		.put = wm8776_input_mux_put,
		.निजी_value = 1 << 0,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Capture Switch",
		.info = snd_ctl_boolean_mono_info,
		.get = wm8776_input_mux_get,
		.put = wm8776_input_mux_put,
		.निजी_value = 1 << 1,
	पूर्ण,
	WM8776_BIT_SWITCH("Front Mic Capture Switch",
			  WM8776_ADCMUX, 1 << 2, 0, 0),
	WM8776_BIT_SWITCH("Aux Capture Switch",
			  WM8776_ADCMUX, 1 << 3, 0, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "ADC Filter Capture Enum",
		.info = hpf_info,
		.get = hpf_get,
		.put = hpf_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Level Control Capture Enum",
		.info = wm8776_level_control_info,
		.get = wm8776_level_control_get,
		.put = wm8776_level_control_put,
		.निजी_value = 0,
	पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new hdav_slim_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "HDMI Playback Switch",
		.info = snd_ctl_boolean_mono_info,
		.get = xonar_gpio_bit_चयन_get,
		.put = xonar_gpio_bit_चयन_put,
		.निजी_value = GPIO_SLIM_HDMI_DISABLE | XONAR_GPIO_BIT_INVERT,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphone Playback Volume",
		.info = wm8776_hp_vol_info,
		.get = wm8776_hp_vol_get,
		.put = wm8776_hp_vol_put,
		.tlv = अणु .p = wm8776_hp_db_scale पूर्ण,
	पूर्ण,
	WM8776_BIT_SWITCH("Headphone Playback Switch",
			  WM8776_PWRDOWN, WM8776_HPPD, 1, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Input Capture Volume",
		.info = wm8776_input_vol_info,
		.get = wm8776_input_vol_get,
		.put = wm8776_input_vol_put,
		.tlv = अणु .p = wm8776_adc_db_scale पूर्ण,
	पूर्ण,
	WM8776_BIT_SWITCH("Mic Capture Switch",
			  WM8776_ADCMUX, 1 << 0, 0, 0),
	WM8776_BIT_SWITCH("Aux Capture Switch",
			  WM8776_ADCMUX, 1 << 1, 0, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "ADC Filter Capture Enum",
		.info = hpf_info,
		.get = hpf_get,
		.put = hpf_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Level Control Capture Enum",
		.info = wm8776_level_control_info,
		.get = wm8776_level_control_get,
		.put = wm8776_level_control_put,
		.निजी_value = 0,
	पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new lc_controls[] = अणु
	WM8776_FIELD_CTL_VOLUME("Limiter Threshold",
				WM8776_ALCCTRL1, 0, 11, 0, 15, 0xf,
				LC_CONTROL_LIMITER, wm8776_lct_db_scale),
	WM8776_FIELD_CTL_ENUM("Limiter Attack Time",
			      WM8776_ALCCTRL3, 0, 2, 0, 10, 0xf,
			      LC_CONTROL_LIMITER),
	WM8776_FIELD_CTL_ENUM("Limiter Decay Time",
			      WM8776_ALCCTRL3, 4, 3, 0, 10, 0xf,
			      LC_CONTROL_LIMITER),
	WM8776_FIELD_CTL_ENUM("Limiter Transient Window",
			      WM8776_LIMITER, 4, 2, 0, 7, 0x7,
			      LC_CONTROL_LIMITER),
	WM8776_FIELD_CTL_VOLUME("Limiter Maximum Attenuation",
				WM8776_LIMITER, 0, 6, 3, 12, 0xf,
				LC_CONTROL_LIMITER,
				wm8776_maxatten_lim_db_scale),
	WM8776_FIELD_CTL_VOLUME("ALC Target Level",
				WM8776_ALCCTRL1, 0, 11, 0, 15, 0xf,
				LC_CONTROL_ALC, wm8776_lct_db_scale),
	WM8776_FIELD_CTL_ENUM("ALC Attack Time",
			      WM8776_ALCCTRL3, 0, 2, 0, 10, 0xf,
			      LC_CONTROL_ALC),
	WM8776_FIELD_CTL_ENUM("ALC Decay Time",
			      WM8776_ALCCTRL3, 4, 3, 0, 10, 0xf,
			      LC_CONTROL_ALC),
	WM8776_FIELD_CTL_VOLUME("ALC Maximum Gain",
				WM8776_ALCCTRL1, 4, 7, 1, 7, 0x7,
				LC_CONTROL_ALC, wm8776_maxgain_db_scale),
	WM8776_FIELD_CTL_VOLUME("ALC Maximum Attenuation",
				WM8776_LIMITER, 0, 10, 10, 15, 0xf,
				LC_CONTROL_ALC, wm8776_maxatten_alc_db_scale),
	WM8776_FIELD_CTL_ENUM("ALC Hold Time",
			      WM8776_ALCCTRL2, 0, 0, 0, 15, 0xf,
			      LC_CONTROL_ALC),
	WM8776_BIT_SWITCH("Noise Gate Capture Switch",
			  WM8776_NOISEGATE, WM8776_NGAT, 0,
			  LC_CONTROL_ALC),
	WM8776_FIELD_CTL_VOLUME("Noise Gate Threshold",
				WM8776_NOISEGATE, 2, 0, 0, 7, 0x7,
				LC_CONTROL_ALC, wm8776_ngth_db_scale),
पूर्ण;

अटल पूर्णांक add_lc_controls(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक err;

	BUILD_BUG_ON(ARRAY_SIZE(lc_controls) != ARRAY_SIZE(data->lc_controls));
	क्रम (i = 0; i < ARRAY_SIZE(lc_controls); ++i) अणु
		ctl = snd_ctl_new1(&lc_controls[i], chip);
		अगर (!ctl)
			वापस -ENOMEM;
		err = snd_ctl_add(chip->card, ctl);
		अगर (err < 0)
			वापस err;
		data->lc_controls[i] = ctl;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xonar_ds_mixer_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(ds_controls); ++i) अणु
		ctl = snd_ctl_new1(&ds_controls[i], chip);
		अगर (!ctl)
			वापस -ENOMEM;
		err = snd_ctl_add(chip->card, ctl);
		अगर (err < 0)
			वापस err;
		अगर (!म_भेद(ctl->id.name, "Line Capture Switch"))
			data->line_adcmux_control = ctl;
		अन्यथा अगर (!म_भेद(ctl->id.name, "Mic Capture Switch"))
			data->mic_adcmux_control = ctl;
	पूर्ण
	अगर (!data->line_adcmux_control || !data->mic_adcmux_control)
		वापस -ENXIO;

	वापस add_lc_controls(chip);
पूर्ण

अटल पूर्णांक xonar_hdav_slim_mixer_init(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(hdav_slim_controls); ++i) अणु
		ctl = snd_ctl_new1(&hdav_slim_controls[i], chip);
		अगर (!ctl)
			वापस -ENOMEM;
		err = snd_ctl_add(chip->card, ctl);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस add_lc_controls(chip);
पूर्ण

अटल व्योम dump_wm8776_रेजिस्टरs(काष्ठा oxygen *chip,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	snd_iम_लिखो(buffer, "\nWM8776:\n00:");
	क्रम (i = 0; i < 0x10; ++i)
		snd_iम_लिखो(buffer, " %03x", data->wm8776_regs[i]);
	snd_iम_लिखो(buffer, "\n10:");
	क्रम (i = 0x10; i < 0x17; ++i)
		snd_iम_लिखो(buffer, " %03x", data->wm8776_regs[i]);
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम dump_wm87x6_रेजिस्टरs(काष्ठा oxygen *chip,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा xonar_wm87x6 *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	dump_wm8776_रेजिस्टरs(chip, buffer);
	snd_iम_लिखो(buffer, "\nWM8766:\n00:");
	क्रम (i = 0; i < 0x10; ++i)
		snd_iम_लिखो(buffer, " %03x", data->wm8766_regs[i]);
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल स्थिर काष्ठा oxygen_model model_xonar_ds = अणु
	.दीर्घname = "Asus Virtuoso 66",
	.chip = "AV200",
	.init = xonar_ds_init,
	.mixer_init = xonar_ds_mixer_init,
	.cleanup = xonar_ds_cleanup,
	.suspend = xonar_ds_suspend,
	.resume = xonar_ds_resume,
	.pcm_hardware_filter = wm8776_adc_hardware_filter,
	.set_dac_params = set_wm87x6_dac_params,
	.set_adc_params = set_wm8776_adc_params,
	.update_dac_volume = update_wm87x6_volume,
	.update_dac_mute = update_wm87x6_mute,
	.update_center_lfe_mix = update_wm8766_center_lfe_mix,
	.gpio_changed = xonar_ds_gpio_changed,
	.dump_रेजिस्टरs = dump_wm87x6_रेजिस्टरs,
	.dac_tlv = wm87x6_dac_db_scale,
	.model_data_size = माप(काष्ठा xonar_wm87x6),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 CAPTURE_0_FROM_I2S_1 |
			 CAPTURE_1_FROM_SPDIF,
	.dac_channels_pcm = 8,
	.dac_channels_mixer = 8,
	.dac_volume_min = 255 - 2*60,
	.dac_volume_max = 255,
	.function_flags = OXYGEN_FUNCTION_SPI,
	.dac_mclks = OXYGEN_MCLKS(256, 256, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 256, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;

अटल स्थिर काष्ठा oxygen_model model_xonar_hdav_slim = अणु
	.लघुname = "Xonar HDAV1.3 Slim",
	.दीर्घname = "Asus Virtuoso 200",
	.chip = "AV200",
	.init = xonar_hdav_slim_init,
	.mixer_init = xonar_hdav_slim_mixer_init,
	.cleanup = xonar_hdav_slim_cleanup,
	.suspend = xonar_hdav_slim_suspend,
	.resume = xonar_hdav_slim_resume,
	.pcm_hardware_filter = xonar_hdav_slim_hardware_filter,
	.set_dac_params = set_hdav_slim_dac_params,
	.set_adc_params = set_wm8776_adc_params,
	.update_dac_volume = update_wm8776_volume,
	.update_dac_mute = update_wm8776_mute,
	.uart_input = xonar_hdmi_uart_input,
	.dump_रेजिस्टरs = dump_wm8776_रेजिस्टरs,
	.dac_tlv = wm87x6_dac_db_scale,
	.model_data_size = माप(काष्ठा xonar_wm87x6),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 CAPTURE_0_FROM_I2S_1 |
			 CAPTURE_1_FROM_SPDIF,
	.dac_channels_pcm = 8,
	.dac_channels_mixer = 2,
	.dac_volume_min = 255 - 2*60,
	.dac_volume_max = 255,
	.function_flags = OXYGEN_FUNCTION_2WIRE,
	.dac_mclks = OXYGEN_MCLKS(256, 256, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 256, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;

पूर्णांक get_xonar_wm87x6_model(काष्ठा oxygen *chip,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	चयन (id->subdevice) अणु
	हाल 0x838e:
		chip->model = model_xonar_ds;
		chip->model.लघुname = "Xonar DS";
		अवरोध;
	हाल 0x8522:
		chip->model = model_xonar_ds;
		chip->model.लघुname = "Xonar DSX";
		अवरोध;
	हाल 0x835e:
		chip->model = model_xonar_hdav_slim;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
