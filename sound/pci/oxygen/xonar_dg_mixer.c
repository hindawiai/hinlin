<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mixer controls क्रम the Xonar DG/DGX
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 * Copyright (c) Roman Volkov <v1ron@mail.ru>
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>
#समावेश "oxygen.h"
#समावेश "xonar_dg.h"
#समावेश "cs4245.h"

/* analog output select */

अटल पूर्णांक output_select_apply(काष्ठा oxygen *chip)
अणु
	काष्ठा dg *data = chip->model_data;

	data->cs4245_shaकरोw[CS4245_SIGNAL_SEL] &= ~CS4245_A_OUT_SEL_MASK;
	अगर (data->output_sel == PLAYBACK_DST_HP) अणु
		/* mute FP (aux output) amplअगरier, चयन rear jack to CS4245 */
		oxygen_set_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_REAR);
	पूर्ण अन्यथा अगर (data->output_sel == PLAYBACK_DST_HP_FP) अणु
		/*
		 * Unmute FP amplअगरier, चयन rear jack to CS4361;
		 * I2S channels 2,3,4 should be inactive.
		 */
		oxygen_clear_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_REAR);
		data->cs4245_shaकरोw[CS4245_SIGNAL_SEL] |= CS4245_A_OUT_SEL_DAC;
	पूर्ण अन्यथा अणु
		/*
		 * 2.0, 4.0, 5.1: चयन to CS4361, mute FP amp.,
		 * and change playback routing.
		 */
		oxygen_clear_bits8(chip, OXYGEN_GPIO_DATA, GPIO_HP_REAR);
	पूर्ण
	वापस cs4245_ग_लिखो_spi(chip, CS4245_SIGNAL_SEL);
पूर्ण

अटल पूर्णांक output_select_info(काष्ठा snd_kcontrol *ctl,
			      काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[3] = अणु
		"Stereo Headphones",
		"Stereo Headphones FP",
		"Multichannel",
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 3, names);
पूर्ण

अटल पूर्णांक output_select_get(काष्ठा snd_kcontrol *ctl,
			     काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;

	mutex_lock(&chip->mutex);
	value->value.क्रमागतerated.item[0] = data->output_sel;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक output_select_put(काष्ठा snd_kcontrol *ctl,
			     काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	अचिन्हित पूर्णांक new = value->value.क्रमागतerated.item[0];
	पूर्णांक changed = 0;
	पूर्णांक ret;

	mutex_lock(&chip->mutex);
	अगर (data->output_sel != new) अणु
		data->output_sel = new;
		ret = output_select_apply(chip);
		changed = ret >= 0 ? 1 : ret;
		oxygen_update_dac_routing(chip);
	पूर्ण
	mutex_unlock(&chip->mutex);

	वापस changed;
पूर्ण

/* CS4245 Headphone Channels A&B Volume Control */

अटल पूर्णांक hp_stereo_volume_info(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 2;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 255;
	वापस 0;
पूर्ण

अटल पूर्णांक hp_stereo_volume_get(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *val)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	अचिन्हित पूर्णांक पंचांगp;

	mutex_lock(&chip->mutex);
	पंचांगp = (~data->cs4245_shaकरोw[CS4245_DAC_A_CTRL]) & 255;
	val->value.पूर्णांकeger.value[0] = पंचांगp;
	पंचांगp = (~data->cs4245_shaकरोw[CS4245_DAC_B_CTRL]) & 255;
	val->value.पूर्णांकeger.value[1] = पंचांगp;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hp_stereo_volume_put(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *val)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	पूर्णांक ret;
	पूर्णांक changed = 0;
	दीर्घ new1 = val->value.पूर्णांकeger.value[0];
	दीर्घ new2 = val->value.पूर्णांकeger.value[1];

	अगर ((new1 > 255) || (new1 < 0) || (new2 > 255) || (new2 < 0))
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	अगर ((data->cs4245_shaकरोw[CS4245_DAC_A_CTRL] != ~new1) ||
	    (data->cs4245_shaकरोw[CS4245_DAC_B_CTRL] != ~new2)) अणु
		data->cs4245_shaकरोw[CS4245_DAC_A_CTRL] = ~new1;
		data->cs4245_shaकरोw[CS4245_DAC_B_CTRL] = ~new2;
		ret = cs4245_ग_लिखो_spi(chip, CS4245_DAC_A_CTRL);
		अगर (ret >= 0)
			ret = cs4245_ग_लिखो_spi(chip, CS4245_DAC_B_CTRL);
		changed = ret >= 0 ? 1 : ret;
	पूर्ण
	mutex_unlock(&chip->mutex);

	वापस changed;
पूर्ण

/* Headphone Mute */

अटल पूर्णांक hp_mute_get(काष्ठा snd_kcontrol *ctl,
			काष्ठा snd_ctl_elem_value *val)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;

	mutex_lock(&chip->mutex);
	val->value.पूर्णांकeger.value[0] =
		!(data->cs4245_shaकरोw[CS4245_DAC_CTRL_1] & CS4245_MUTE_DAC);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक hp_mute_put(काष्ठा snd_kcontrol *ctl,
			काष्ठा snd_ctl_elem_value *val)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	पूर्णांक ret;
	पूर्णांक changed;

	अगर (val->value.पूर्णांकeger.value[0] > 1)
		वापस -EINVAL;
	mutex_lock(&chip->mutex);
	data->cs4245_shaकरोw[CS4245_DAC_CTRL_1] &= ~CS4245_MUTE_DAC;
	data->cs4245_shaकरोw[CS4245_DAC_CTRL_1] |=
		(~val->value.पूर्णांकeger.value[0] << 2) & CS4245_MUTE_DAC;
	ret = cs4245_ग_लिखो_spi(chip, CS4245_DAC_CTRL_1);
	changed = ret >= 0 ? 1 : ret;
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

/* capture volume क्रम all sources */

अटल पूर्णांक input_volume_apply(काष्ठा oxygen *chip, अक्षर left, अक्षर right)
अणु
	काष्ठा dg *data = chip->model_data;
	पूर्णांक ret;

	data->cs4245_shaकरोw[CS4245_PGA_A_CTRL] = left;
	data->cs4245_shaकरोw[CS4245_PGA_B_CTRL] = right;
	ret = cs4245_ग_लिखो_spi(chip, CS4245_PGA_A_CTRL);
	अगर (ret < 0)
		वापस ret;
	वापस cs4245_ग_लिखो_spi(chip, CS4245_PGA_B_CTRL);
पूर्ण

अटल पूर्णांक input_vol_info(काष्ठा snd_kcontrol *ctl,
			  काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 2;
	info->value.पूर्णांकeger.min = 2 * -12;
	info->value.पूर्णांकeger.max = 2 * 12;
	वापस 0;
पूर्ण

अटल पूर्णांक input_vol_get(काष्ठा snd_kcontrol *ctl,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	अचिन्हित पूर्णांक idx = ctl->निजी_value;

	mutex_lock(&chip->mutex);
	value->value.पूर्णांकeger.value[0] = data->input_vol[idx][0];
	value->value.पूर्णांकeger.value[1] = data->input_vol[idx][1];
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक input_vol_put(काष्ठा snd_kcontrol *ctl,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	अचिन्हित पूर्णांक idx = ctl->निजी_value;
	पूर्णांक changed = 0;
	पूर्णांक ret = 0;

	अगर (value->value.पूर्णांकeger.value[0] < 2 * -12 ||
	    value->value.पूर्णांकeger.value[0] > 2 * 12 ||
	    value->value.पूर्णांकeger.value[1] < 2 * -12 ||
	    value->value.पूर्णांकeger.value[1] > 2 * 12)
		वापस -EINVAL;
	mutex_lock(&chip->mutex);
	changed = data->input_vol[idx][0] != value->value.पूर्णांकeger.value[0] ||
		  data->input_vol[idx][1] != value->value.पूर्णांकeger.value[1];
	अगर (changed) अणु
		data->input_vol[idx][0] = value->value.पूर्णांकeger.value[0];
		data->input_vol[idx][1] = value->value.पूर्णांकeger.value[1];
		अगर (idx == data->input_sel) अणु
			ret = input_volume_apply(chip,
				data->input_vol[idx][0],
				data->input_vol[idx][1]);
		पूर्ण
		changed = ret >= 0 ? 1 : ret;
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

/* Capture Source */

अटल पूर्णांक input_source_apply(काष्ठा oxygen *chip)
अणु
	काष्ठा dg *data = chip->model_data;

	data->cs4245_shaकरोw[CS4245_ANALOG_IN] &= ~CS4245_SEL_MASK;
	अगर (data->input_sel == CAPTURE_SRC_FP_MIC)
		data->cs4245_shaकरोw[CS4245_ANALOG_IN] |= CS4245_SEL_INPUT_2;
	अन्यथा अगर (data->input_sel == CAPTURE_SRC_LINE)
		data->cs4245_shaकरोw[CS4245_ANALOG_IN] |= CS4245_SEL_INPUT_4;
	अन्यथा अगर (data->input_sel != CAPTURE_SRC_MIC)
		data->cs4245_shaकरोw[CS4245_ANALOG_IN] |= CS4245_SEL_INPUT_1;
	वापस cs4245_ग_लिखो_spi(chip, CS4245_ANALOG_IN);
पूर्ण

अटल पूर्णांक input_sel_info(काष्ठा snd_kcontrol *ctl,
			  काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[4] = अणु
		"Mic", "Front Mic", "Line", "Aux"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 4, names);
पूर्ण

अटल पूर्णांक input_sel_get(काष्ठा snd_kcontrol *ctl,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;

	mutex_lock(&chip->mutex);
	value->value.क्रमागतerated.item[0] = data->input_sel;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक input_sel_put(काष्ठा snd_kcontrol *ctl,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	पूर्णांक changed;
	पूर्णांक ret;

	अगर (value->value.क्रमागतerated.item[0] > 3)
		वापस -EINVAL;

	mutex_lock(&chip->mutex);
	changed = value->value.क्रमागतerated.item[0] != data->input_sel;
	अगर (changed) अणु
		data->input_sel = value->value.क्रमागतerated.item[0];

		ret = input_source_apply(chip);
		अगर (ret >= 0)
			ret = input_volume_apply(chip,
				data->input_vol[data->input_sel][0],
				data->input_vol[data->input_sel][1]);
		changed = ret >= 0 ? 1 : ret;
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

/* ADC high-pass filter */

अटल पूर्णांक hpf_info(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[2] = अणु "Active", "Frozen" पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक hpf_get(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;

	value->value.क्रमागतerated.item[0] =
		!!(data->cs4245_shaकरोw[CS4245_ADC_CTRL] & CS4245_HPF_FREEZE);
	वापस 0;
पूर्ण

अटल पूर्णांक hpf_put(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा dg *data = chip->model_data;
	u8 reg;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	reg = data->cs4245_shaकरोw[CS4245_ADC_CTRL] & ~CS4245_HPF_FREEZE;
	अगर (value->value.क्रमागतerated.item[0])
		reg |= CS4245_HPF_FREEZE;
	changed = reg != data->cs4245_shaकरोw[CS4245_ADC_CTRL];
	अगर (changed) अणु
		data->cs4245_shaकरोw[CS4245_ADC_CTRL] = reg;
		cs4245_ग_लिखो_spi(chip, CS4245_ADC_CTRL);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

#घोषणा INPUT_VOLUME(xname, index) अणु \
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
		  SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
	.info = input_vol_info, \
	.get = input_vol_get, \
	.put = input_vol_put, \
	.tlv = अणु .p = pga_db_scale पूर्ण, \
	.निजी_value = index, \
पूर्ण
अटल स्थिर DECLARE_TLV_DB_MINMAX(hp_db_scale, -12550, 0);
अटल स्थिर DECLARE_TLV_DB_MINMAX(pga_db_scale, -1200, 1200);
अटल स्थिर काष्ठा snd_kcontrol_new dg_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Output Playback Enum",
		.info = output_select_info,
		.get = output_select_get,
		.put = output_select_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphone Playback Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = hp_stereo_volume_info,
		.get = hp_stereo_volume_get,
		.put = hp_stereo_volume_put,
		.tlv = अणु .p = hp_db_scale, पूर्ण,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphone Playback Switch",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = snd_ctl_boolean_mono_info,
		.get = hp_mute_get,
		.put = hp_mute_put,
	पूर्ण,
	INPUT_VOLUME("Mic Capture Volume", CAPTURE_SRC_MIC),
	INPUT_VOLUME("Front Mic Capture Volume", CAPTURE_SRC_FP_MIC),
	INPUT_VOLUME("Line Capture Volume", CAPTURE_SRC_LINE),
	INPUT_VOLUME("Aux Capture Volume", CAPTURE_SRC_AUX),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Capture Source",
		.info = input_sel_info,
		.get = input_sel_get,
		.put = input_sel_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "ADC High-pass Filter Capture Enum",
		.info = hpf_info,
		.get = hpf_get,
		.put = hpf_put,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dg_control_filter(काष्ठा snd_kcontrol_new *ढाँचा)
अणु
	अगर (!म_भेदन(ढाँचा->name, "Master Playback ", 16))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक dg_mixer_init(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	output_select_apply(chip);
	input_source_apply(chip);
	oxygen_update_dac_routing(chip);

	क्रम (i = 0; i < ARRAY_SIZE(dg_controls); ++i) अणु
		err = snd_ctl_add(chip->card,
				  snd_ctl_new1(&dg_controls[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा oxygen_model model_xonar_dg = अणु
	.दीर्घname = "C-Media Oxygen HD Audio",
	.chip = "CMI8786",
	.init = dg_init,
	.control_filter = dg_control_filter,
	.mixer_init = dg_mixer_init,
	.cleanup = dg_cleanup,
	.suspend = dg_suspend,
	.resume = dg_resume,
	.set_dac_params = set_cs4245_dac_params,
	.set_adc_params = set_cs4245_adc_params,
	.adjust_dac_routing = adjust_dg_dac_routing,
	.dump_रेजिस्टरs = dump_cs4245_रेजिस्टरs,
	.model_data_size = माप(काष्ठा dg),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 CAPTURE_0_FROM_I2S_1 |
			 CAPTURE_1_FROM_SPDIF,
	.dac_channels_pcm = 6,
	.dac_channels_mixer = 0,
	.function_flags = OXYGEN_FUNCTION_SPI,
	.dac_mclks = OXYGEN_MCLKS(256, 128, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 128, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;
