<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * C-Media CMI8788 driver - mixer code
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/mutex.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश "oxygen.h"
#समावेश "cm9780.h"

अटल पूर्णांक dac_volume_info(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_info *info)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = chip->model.dac_channels_mixer;
	info->value.पूर्णांकeger.min = chip->model.dac_volume_min;
	info->value.पूर्णांकeger.max = chip->model.dac_volume_max;
	वापस 0;
पूर्ण

अटल पूर्णांक dac_volume_get(काष्ठा snd_kcontrol *ctl,
			  काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक i;

	mutex_lock(&chip->mutex);
	क्रम (i = 0; i < chip->model.dac_channels_mixer; ++i)
		value->value.पूर्णांकeger.value[i] = chip->dac_volume[i];
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dac_volume_put(काष्ठा snd_kcontrol *ctl,
			  काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक changed;

	changed = 0;
	mutex_lock(&chip->mutex);
	क्रम (i = 0; i < chip->model.dac_channels_mixer; ++i)
		अगर (value->value.पूर्णांकeger.value[i] != chip->dac_volume[i]) अणु
			chip->dac_volume[i] = value->value.पूर्णांकeger.value[i];
			changed = 1;
		पूर्ण
	अगर (changed)
		chip->model.update_dac_volume(chip);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक dac_mute_get(काष्ठा snd_kcontrol *ctl,
			काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	mutex_lock(&chip->mutex);
	value->value.पूर्णांकeger.value[0] = !chip->dac_mute;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक dac_mute_put(काष्ठा snd_kcontrol *ctl,
			  काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	changed = (!value->value.पूर्णांकeger.value[0]) != chip->dac_mute;
	अगर (changed) अणु
		chip->dac_mute = !value->value.पूर्णांकeger.value[0];
		chip->model.update_dac_mute(chip);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल अचिन्हित पूर्णांक upmix_item_count(काष्ठा oxygen *chip)
अणु
	अगर (chip->model.dac_channels_pcm < 8)
		वापस 2;
	अन्यथा अगर (chip->model.update_center_lfe_mix)
		वापस 5;
	अन्यथा
		वापस 3;
पूर्ण

अटल पूर्णांक upmix_info(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[5] = अणु
		"Front",
		"Front+Surround",
		"Front+Surround+Back",
		"Front+Surround+Center/LFE",
		"Front+Surround+Center/LFE+Back",
	पूर्ण;
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक count = upmix_item_count(chip);

	वापस snd_ctl_क्रमागत_info(info, 1, count, names);
पूर्ण

अटल पूर्णांक upmix_get(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	mutex_lock(&chip->mutex);
	value->value.क्रमागतerated.item[0] = chip->dac_routing;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

व्योम oxygen_update_dac_routing(काष्ठा oxygen *chip)
अणु
	/* DAC 0: front, DAC 1: surround, DAC 2: center/LFE, DAC 3: back */
	अटल स्थिर अचिन्हित पूर्णांक reg_values[5] = अणु
		/* stereo -> front */
		(0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
		(1 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
		(2 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
		(3 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT),
		/* stereo -> front+surround */
		(0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
		(2 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
		(3 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT),
		/* stereo -> front+surround+back */
		(0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
		(2 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT),
		/* stereo -> front+surround+center/LFE */
		(0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
		(3 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT),
		/* stereo -> front+surround+center/LFE+back */
		(0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
		(0 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT),
	पूर्ण;
	u8 channels;
	अचिन्हित पूर्णांक reg_value;

	channels = oxygen_पढ़ो8(chip, OXYGEN_PLAY_CHANNELS) &
		OXYGEN_PLAY_CHANNELS_MASK;
	अगर (channels == OXYGEN_PLAY_CHANNELS_2)
		reg_value = reg_values[chip->dac_routing];
	अन्यथा अगर (channels == OXYGEN_PLAY_CHANNELS_8)
		/* in 7.1 mode, "rear" channels go to the "back" jack */
		reg_value = (0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
			    (3 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
			    (2 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
			    (1 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT);
	अन्यथा
		reg_value = (0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
			    (1 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
			    (2 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
			    (3 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT);
	अगर (chip->model.adjust_dac_routing)
		reg_value = chip->model.adjust_dac_routing(chip, reg_value);
	oxygen_ग_लिखो16_masked(chip, OXYGEN_PLAY_ROUTING, reg_value,
			      OXYGEN_PLAY_DAC0_SOURCE_MASK |
			      OXYGEN_PLAY_DAC1_SOURCE_MASK |
			      OXYGEN_PLAY_DAC2_SOURCE_MASK |
			      OXYGEN_PLAY_DAC3_SOURCE_MASK);
	अगर (chip->model.update_center_lfe_mix)
		chip->model.update_center_lfe_mix(chip, chip->dac_routing > 2);
पूर्ण
EXPORT_SYMBOL(oxygen_update_dac_routing);

अटल पूर्णांक upmix_put(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक count = upmix_item_count(chip);
	पूर्णांक changed;

	अगर (value->value.क्रमागतerated.item[0] >= count)
		वापस -EINVAL;
	mutex_lock(&chip->mutex);
	changed = value->value.क्रमागतerated.item[0] != chip->dac_routing;
	अगर (changed) अणु
		chip->dac_routing = value->value.क्रमागतerated.item[0];
		oxygen_update_dac_routing(chip);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक spdअगर_चयन_get(काष्ठा snd_kcontrol *ctl,
			    काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	mutex_lock(&chip->mutex);
	value->value.पूर्णांकeger.value[0] = chip->spdअगर_playback_enable;
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक oxygen_spdअगर_rate(अचिन्हित पूर्णांक oxygen_rate)
अणु
	चयन (oxygen_rate) अणु
	हाल OXYGEN_RATE_32000:
		वापस IEC958_AES3_CON_FS_32000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	हाल OXYGEN_RATE_44100:
		वापस IEC958_AES3_CON_FS_44100 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	शेष: /* OXYGEN_RATE_48000 */
		वापस IEC958_AES3_CON_FS_48000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	हाल OXYGEN_RATE_64000:
		वापस 0xb << OXYGEN_SPDIF_CS_RATE_SHIFT;
	हाल OXYGEN_RATE_88200:
		वापस IEC958_AES3_CON_FS_88200 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	हाल OXYGEN_RATE_96000:
		वापस IEC958_AES3_CON_FS_96000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	हाल OXYGEN_RATE_176400:
		वापस IEC958_AES3_CON_FS_176400 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	हाल OXYGEN_RATE_192000:
		वापस IEC958_AES3_CON_FS_192000 << OXYGEN_SPDIF_CS_RATE_SHIFT;
	पूर्ण
पूर्ण

व्योम oxygen_update_spdअगर_source(काष्ठा oxygen *chip)
अणु
	u32 old_control, new_control;
	u16 old_routing, new_routing;
	अचिन्हित पूर्णांक oxygen_rate;

	old_control = oxygen_पढ़ो32(chip, OXYGEN_SPDIF_CONTROL);
	old_routing = oxygen_पढ़ो16(chip, OXYGEN_PLAY_ROUTING);
	अगर (chip->pcm_active & (1 << PCM_SPDIF)) अणु
		new_control = old_control | OXYGEN_SPDIF_OUT_ENABLE;
		new_routing = (old_routing & ~OXYGEN_PLAY_SPDIF_MASK)
			| OXYGEN_PLAY_SPDIF_SPDIF;
		oxygen_rate = (old_control >> OXYGEN_SPDIF_OUT_RATE_SHIFT)
			& OXYGEN_I2S_RATE_MASK;
		/* S/PDIF rate was alपढ़ोy set by the caller */
	पूर्ण अन्यथा अगर ((chip->pcm_active & (1 << PCM_MULTICH)) &&
		   chip->spdअगर_playback_enable) अणु
		new_routing = (old_routing & ~OXYGEN_PLAY_SPDIF_MASK)
			| OXYGEN_PLAY_SPDIF_MULTICH_01;
		oxygen_rate = oxygen_पढ़ो16(chip, OXYGEN_I2S_MULTICH_FORMAT)
			& OXYGEN_I2S_RATE_MASK;
		new_control = (old_control & ~OXYGEN_SPDIF_OUT_RATE_MASK) |
			(oxygen_rate << OXYGEN_SPDIF_OUT_RATE_SHIFT) |
			OXYGEN_SPDIF_OUT_ENABLE;
	पूर्ण अन्यथा अणु
		new_control = old_control & ~OXYGEN_SPDIF_OUT_ENABLE;
		new_routing = old_routing;
		oxygen_rate = OXYGEN_RATE_44100;
	पूर्ण
	अगर (old_routing != new_routing) अणु
		oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_CONTROL,
			       new_control & ~OXYGEN_SPDIF_OUT_ENABLE);
		oxygen_ग_लिखो16(chip, OXYGEN_PLAY_ROUTING, new_routing);
	पूर्ण
	अगर (new_control & OXYGEN_SPDIF_OUT_ENABLE)
		oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_OUTPUT_BITS,
			       oxygen_spdअगर_rate(oxygen_rate) |
			       ((chip->pcm_active & (1 << PCM_SPDIF)) ?
				chip->spdअगर_pcm_bits : chip->spdअगर_bits));
	oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_CONTROL, new_control);
पूर्ण

अटल पूर्णांक spdअगर_चयन_put(काष्ठा snd_kcontrol *ctl,
			    काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	changed = value->value.पूर्णांकeger.value[0] != chip->spdअगर_playback_enable;
	अगर (changed) अणु
		chip->spdअगर_playback_enable = !!value->value.पूर्णांकeger.value[0];
		spin_lock_irq(&chip->reg_lock);
		oxygen_update_spdअगर_source(chip);
		spin_unlock_irq(&chip->reg_lock);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक spdअगर_info(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	info->count = 1;
	वापस 0;
पूर्ण

अटल व्योम oxygen_to_iec958(u32 bits, काष्ठा snd_ctl_elem_value *value)
अणु
	value->value.iec958.status[0] =
		bits & (OXYGEN_SPDIF_NONAUDIO | OXYGEN_SPDIF_C |
			OXYGEN_SPDIF_PREEMPHASIS);
	value->value.iec958.status[1] = /* category and original */
		bits >> OXYGEN_SPDIF_CATEGORY_SHIFT;
पूर्ण

अटल u32 iec958_to_oxygen(काष्ठा snd_ctl_elem_value *value)
अणु
	u32 bits;

	bits = value->value.iec958.status[0] &
		(OXYGEN_SPDIF_NONAUDIO | OXYGEN_SPDIF_C |
		 OXYGEN_SPDIF_PREEMPHASIS);
	bits |= value->value.iec958.status[1] << OXYGEN_SPDIF_CATEGORY_SHIFT;
	अगर (bits & OXYGEN_SPDIF_NONAUDIO)
		bits |= OXYGEN_SPDIF_V;
	वापस bits;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_spdअगर_bits(काष्ठा oxygen *chip, u32 bits)
अणु
	oxygen_ग_लिखो32_masked(chip, OXYGEN_SPDIF_OUTPUT_BITS, bits,
			      OXYGEN_SPDIF_NONAUDIO |
			      OXYGEN_SPDIF_C |
			      OXYGEN_SPDIF_PREEMPHASIS |
			      OXYGEN_SPDIF_CATEGORY_MASK |
			      OXYGEN_SPDIF_ORIGINAL |
			      OXYGEN_SPDIF_V);
पूर्ण

अटल पूर्णांक spdअगर_शेष_get(काष्ठा snd_kcontrol *ctl,
			     काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	mutex_lock(&chip->mutex);
	oxygen_to_iec958(chip->spdअगर_bits, value);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_शेष_put(काष्ठा snd_kcontrol *ctl,
			     काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u32 new_bits;
	पूर्णांक changed;

	new_bits = iec958_to_oxygen(value);
	mutex_lock(&chip->mutex);
	changed = new_bits != chip->spdअगर_bits;
	अगर (changed) अणु
		chip->spdअगर_bits = new_bits;
		अगर (!(chip->pcm_active & (1 << PCM_SPDIF)))
			ग_लिखो_spdअगर_bits(chip, new_bits);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक spdअगर_mask_get(काष्ठा snd_kcontrol *ctl,
			  काष्ठा snd_ctl_elem_value *value)
अणु
	value->value.iec958.status[0] = IEC958_AES0_NONAUDIO |
		IEC958_AES0_CON_NOT_COPYRIGHT | IEC958_AES0_CON_EMPHASIS;
	value->value.iec958.status[1] =
		IEC958_AES1_CON_CATEGORY | IEC958_AES1_CON_ORIGINAL;
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_pcm_get(काष्ठा snd_kcontrol *ctl,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	mutex_lock(&chip->mutex);
	oxygen_to_iec958(chip->spdअगर_pcm_bits, value);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_pcm_put(काष्ठा snd_kcontrol *ctl,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u32 new_bits;
	पूर्णांक changed;

	new_bits = iec958_to_oxygen(value);
	mutex_lock(&chip->mutex);
	changed = new_bits != chip->spdअगर_pcm_bits;
	अगर (changed) अणु
		chip->spdअगर_pcm_bits = new_bits;
		अगर (chip->pcm_active & (1 << PCM_SPDIF))
			ग_लिखो_spdअगर_bits(chip, new_bits);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक spdअगर_input_mask_get(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	value->value.iec958.status[0] = 0xff;
	value->value.iec958.status[1] = 0xff;
	value->value.iec958.status[2] = 0xff;
	value->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_input_शेष_get(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u32 bits;

	bits = oxygen_पढ़ो32(chip, OXYGEN_SPDIF_INPUT_BITS);
	value->value.iec958.status[0] = bits;
	value->value.iec958.status[1] = bits >> 8;
	value->value.iec958.status[2] = bits >> 16;
	value->value.iec958.status[3] = bits >> 24;
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_bit_चयन_get(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u32 bit = ctl->निजी_value;

	value->value.पूर्णांकeger.value[0] =
		!!(oxygen_पढ़ो32(chip, OXYGEN_SPDIF_CONTROL) & bit);
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_bit_चयन_put(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u32 bit = ctl->निजी_value;
	u32 oldreg, newreg;
	पूर्णांक changed;

	spin_lock_irq(&chip->reg_lock);
	oldreg = oxygen_पढ़ो32(chip, OXYGEN_SPDIF_CONTROL);
	अगर (value->value.पूर्णांकeger.value[0])
		newreg = oldreg | bit;
	अन्यथा
		newreg = oldreg & ~bit;
	changed = newreg != oldreg;
	अगर (changed)
		oxygen_ग_लिखो32(chip, OXYGEN_SPDIF_CONTROL, newreg);
	spin_unlock_irq(&chip->reg_lock);
	वापस changed;
पूर्ण

अटल पूर्णांक monitor_volume_info(काष्ठा snd_kcontrol *ctl,
			       काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 1;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक monitor_get(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u8 bit = ctl->निजी_value;
	पूर्णांक invert = ctl->निजी_value & (1 << 8);

	value->value.पूर्णांकeger.value[0] =
		!!invert ^ !!(oxygen_पढ़ो8(chip, OXYGEN_ADC_MONITOR) & bit);
	वापस 0;
पूर्ण

अटल पूर्णांक monitor_put(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u8 bit = ctl->निजी_value;
	पूर्णांक invert = ctl->निजी_value & (1 << 8);
	u8 oldreg, newreg;
	पूर्णांक changed;

	spin_lock_irq(&chip->reg_lock);
	oldreg = oxygen_पढ़ो8(chip, OXYGEN_ADC_MONITOR);
	अगर ((!!value->value.पूर्णांकeger.value[0] ^ !!invert) != 0)
		newreg = oldreg | bit;
	अन्यथा
		newreg = oldreg & ~bit;
	changed = newreg != oldreg;
	अगर (changed)
		oxygen_ग_लिखो8(chip, OXYGEN_ADC_MONITOR, newreg);
	spin_unlock_irq(&chip->reg_lock);
	वापस changed;
पूर्ण

अटल पूर्णांक ac97_चयन_get(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक codec = (ctl->निजी_value >> 24) & 1;
	अचिन्हित पूर्णांक index = ctl->निजी_value & 0xff;
	अचिन्हित पूर्णांक bitnr = (ctl->निजी_value >> 8) & 0xff;
	पूर्णांक invert = ctl->निजी_value & (1 << 16);
	u16 reg;

	mutex_lock(&chip->mutex);
	reg = oxygen_पढ़ो_ac97(chip, codec, index);
	mutex_unlock(&chip->mutex);
	अगर (!(reg & (1 << bitnr)) ^ !invert)
		value->value.पूर्णांकeger.value[0] = 1;
	अन्यथा
		value->value.पूर्णांकeger.value[0] = 0;
	वापस 0;
पूर्ण

अटल व्योम mute_ac97_ctl(काष्ठा oxygen *chip, अचिन्हित पूर्णांक control)
अणु
	अचिन्हित पूर्णांक priv_idx;
	u16 value;

	अगर (!chip->controls[control])
		वापस;
	priv_idx = chip->controls[control]->निजी_value & 0xff;
	value = oxygen_पढ़ो_ac97(chip, 0, priv_idx);
	अगर (!(value & 0x8000)) अणु
		oxygen_ग_लिखो_ac97(chip, 0, priv_idx, value | 0x8000);
		अगर (chip->model.ac97_चयन)
			chip->model.ac97_चयन(chip, priv_idx, 0x8000);
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->controls[control]->id);
	पूर्ण
पूर्ण

अटल पूर्णांक ac97_चयन_put(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक codec = (ctl->निजी_value >> 24) & 1;
	अचिन्हित पूर्णांक index = ctl->निजी_value & 0xff;
	अचिन्हित पूर्णांक bitnr = (ctl->निजी_value >> 8) & 0xff;
	पूर्णांक invert = ctl->निजी_value & (1 << 16);
	u16 oldreg, newreg;
	पूर्णांक change;

	mutex_lock(&chip->mutex);
	oldreg = oxygen_पढ़ो_ac97(chip, codec, index);
	newreg = oldreg;
	अगर (!value->value.पूर्णांकeger.value[0] ^ !invert)
		newreg |= 1 << bitnr;
	अन्यथा
		newreg &= ~(1 << bitnr);
	change = newreg != oldreg;
	अगर (change) अणु
		oxygen_ग_लिखो_ac97(chip, codec, index, newreg);
		अगर (codec == 0 && chip->model.ac97_चयन)
			chip->model.ac97_चयन(chip, index, newreg & 0x8000);
		अगर (index == AC97_LINE) अणु
			oxygen_ग_लिखो_ac97_masked(chip, 0, CM9780_GPIO_STATUS,
						 newreg & 0x8000 ?
						 CM9780_GPO0 : 0, CM9780_GPO0);
			अगर (!(newreg & 0x8000)) अणु
				mute_ac97_ctl(chip, CONTROL_MIC_CAPTURE_SWITCH);
				mute_ac97_ctl(chip, CONTROL_CD_CAPTURE_SWITCH);
				mute_ac97_ctl(chip, CONTROL_AUX_CAPTURE_SWITCH);
			पूर्ण
		पूर्ण अन्यथा अगर ((index == AC97_MIC || index == AC97_CD ||
			    index == AC97_VIDEO || index == AC97_AUX) &&
			   bitnr == 15 && !(newreg & 0x8000)) अणु
			mute_ac97_ctl(chip, CONTROL_LINE_CAPTURE_SWITCH);
			oxygen_ग_लिखो_ac97_masked(chip, 0, CM9780_GPIO_STATUS,
						 CM9780_GPO0, CM9780_GPO0);
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस change;
पूर्ण

अटल पूर्णांक ac97_volume_info(काष्ठा snd_kcontrol *ctl,
			    काष्ठा snd_ctl_elem_info *info)
अणु
	पूर्णांक stereo = (ctl->निजी_value >> 16) & 1;

	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = stereo ? 2 : 1;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 0x1f;
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_volume_get(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक codec = (ctl->निजी_value >> 24) & 1;
	पूर्णांक stereo = (ctl->निजी_value >> 16) & 1;
	अचिन्हित पूर्णांक index = ctl->निजी_value & 0xff;
	u16 reg;

	mutex_lock(&chip->mutex);
	reg = oxygen_पढ़ो_ac97(chip, codec, index);
	mutex_unlock(&chip->mutex);
	अगर (!stereo) अणु
		value->value.पूर्णांकeger.value[0] = 31 - (reg & 0x1f);
	पूर्ण अन्यथा अणु
		value->value.पूर्णांकeger.value[0] = 31 - ((reg >> 8) & 0x1f);
		value->value.पूर्णांकeger.value[1] = 31 - (reg & 0x1f);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_volume_put(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक codec = (ctl->निजी_value >> 24) & 1;
	पूर्णांक stereo = (ctl->निजी_value >> 16) & 1;
	अचिन्हित पूर्णांक index = ctl->निजी_value & 0xff;
	u16 oldreg, newreg;
	पूर्णांक change;

	mutex_lock(&chip->mutex);
	oldreg = oxygen_पढ़ो_ac97(chip, codec, index);
	अगर (!stereo) अणु
		newreg = oldreg & ~0x1f;
		newreg |= 31 - (value->value.पूर्णांकeger.value[0] & 0x1f);
	पूर्ण अन्यथा अणु
		newreg = oldreg & ~0x1f1f;
		newreg |= (31 - (value->value.पूर्णांकeger.value[0] & 0x1f)) << 8;
		newreg |= 31 - (value->value.पूर्णांकeger.value[1] & 0x1f);
	पूर्ण
	change = newreg != oldreg;
	अगर (change)
		oxygen_ग_लिखो_ac97(chip, codec, index, newreg);
	mutex_unlock(&chip->mutex);
	वापस change;
पूर्ण

अटल पूर्णांक mic_fmic_source_info(काष्ठा snd_kcontrol *ctl,
			   काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु "Mic Jack", "Front Panel" पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक mic_fmic_source_get(काष्ठा snd_kcontrol *ctl,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	mutex_lock(&chip->mutex);
	value->value.क्रमागतerated.item[0] =
		!!(oxygen_पढ़ो_ac97(chip, 0, CM9780_JACK) & CM9780_FMIC2MIC);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mic_fmic_source_put(काष्ठा snd_kcontrol *ctl,
			       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 oldreg, newreg;
	पूर्णांक change;

	mutex_lock(&chip->mutex);
	oldreg = oxygen_पढ़ो_ac97(chip, 0, CM9780_JACK);
	अगर (value->value.क्रमागतerated.item[0])
		newreg = oldreg | CM9780_FMIC2MIC;
	अन्यथा
		newreg = oldreg & ~CM9780_FMIC2MIC;
	change = newreg != oldreg;
	अगर (change)
		oxygen_ग_लिखो_ac97(chip, 0, CM9780_JACK, newreg);
	mutex_unlock(&chip->mutex);
	वापस change;
पूर्ण

अटल पूर्णांक ac97_fp_rec_volume_info(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_info *info)
अणु
	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = 2;
	info->value.पूर्णांकeger.min = 0;
	info->value.पूर्णांकeger.max = 7;
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_fp_rec_volume_get(काष्ठा snd_kcontrol *ctl,
				  काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 reg;

	mutex_lock(&chip->mutex);
	reg = oxygen_पढ़ो_ac97(chip, 1, AC97_REC_GAIN);
	mutex_unlock(&chip->mutex);
	value->value.पूर्णांकeger.value[0] = reg & 7;
	value->value.पूर्णांकeger.value[1] = (reg >> 8) & 7;
	वापस 0;
पूर्ण

अटल पूर्णांक ac97_fp_rec_volume_put(काष्ठा snd_kcontrol *ctl,
				  काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 oldreg, newreg;
	पूर्णांक change;

	mutex_lock(&chip->mutex);
	oldreg = oxygen_पढ़ो_ac97(chip, 1, AC97_REC_GAIN);
	newreg = oldreg & ~0x0707;
	newreg = newreg | (value->value.पूर्णांकeger.value[0] & 7);
	newreg = newreg | ((value->value.पूर्णांकeger.value[0] & 7) << 8);
	change = newreg != oldreg;
	अगर (change)
		oxygen_ग_लिखो_ac97(chip, 1, AC97_REC_GAIN, newreg);
	mutex_unlock(&chip->mutex);
	वापस change;
पूर्ण

#घोषणा AC97_SWITCH(xname, codec, index, bitnr, invert) अणु \
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
		.name = xname, \
		.info = snd_ctl_boolean_mono_info, \
		.get = ac97_चयन_get, \
		.put = ac97_चयन_put, \
		.निजी_value = ((codec) << 24) | ((invert) << 16) | \
				 ((bitnr) << 8) | (index), \
	पूर्ण
#घोषणा AC97_VOLUME(xname, codec, index, stereo) अणु \
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
		.name = xname, \
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
		.info = ac97_volume_info, \
		.get = ac97_volume_get, \
		.put = ac97_volume_put, \
		.tlv = अणु .p = ac97_db_scale, पूर्ण, \
		.निजी_value = ((codec) << 24) | ((stereo) << 16) | (index), \
	पूर्ण

अटल DECLARE_TLV_DB_SCALE(monitor_db_scale, -600, 600, 0);
अटल DECLARE_TLV_DB_SCALE(ac97_db_scale, -3450, 150, 0);
अटल DECLARE_TLV_DB_SCALE(ac97_rec_db_scale, 0, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = dac_volume_info,
		.get = dac_volume_get,
		.put = dac_volume_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Switch",
		.info = snd_ctl_boolean_mono_info,
		.get = dac_mute_get,
		.put = dac_mute_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Stereo Upmixing",
		.info = upmix_info,
		.get = upmix_get,
		.put = upmix_put,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new spdअगर_output_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, SWITCH),
		.info = snd_ctl_boolean_mono_info,
		.get = spdअगर_चयन_get,
		.put = spdअगर_चयन_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.device = 1,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info = spdअगर_info,
		.get = spdअगर_शेष_get,
		.put = spdअगर_शेष_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.device = 1,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, CON_MASK),
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.info = spdअगर_info,
		.get = spdअगर_mask_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.device = 1,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, PCM_STREAM),
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			  SNDRV_CTL_ELEM_ACCESS_INACTIVE,
		.info = spdअगर_info,
		.get = spdअगर_pcm_get,
		.put = spdअगर_pcm_put,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new spdअगर_input_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.device = 1,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, MASK),
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.info = spdअगर_info,
		.get = spdअगर_input_mask_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.device = 1,
		.name = SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.info = spdअगर_info,
		.get = spdअगर_input_शेष_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("Loopback ", NONE, SWITCH),
		.info = snd_ctl_boolean_mono_info,
		.get = spdअगर_bit_चयन_get,
		.put = spdअगर_bit_चयन_put,
		.निजी_value = OXYGEN_SPDIF_LOOPBACK,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = SNDRV_CTL_NAME_IEC958("Validity Check ",CAPTURE,SWITCH),
		.info = snd_ctl_boolean_mono_info,
		.get = spdअगर_bit_चयन_get,
		.put = spdअगर_bit_चयन_put,
		.निजी_value = OXYGEN_SPDIF_SPDVALID,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक pcm_dev;
	काष्ठा snd_kcontrol_new controls[2];
पूर्ण monitor_controls[] = अणु
	अणु
		.pcm_dev = CAPTURE_0_FROM_I2S_1,
		.controls = अणु
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Switch",
				.info = snd_ctl_boolean_mono_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_A,
			पूर्ण,
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Volume",
				.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
					  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
				.info = monitor_volume_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_A_HALF_VOL
						| (1 << 8),
				.tlv = अणु .p = monitor_db_scale, पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.pcm_dev = CAPTURE_0_FROM_I2S_2,
		.controls = अणु
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Switch",
				.info = snd_ctl_boolean_mono_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_B,
			पूर्ण,
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Volume",
				.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
					  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
				.info = monitor_volume_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_B_HALF_VOL
						| (1 << 8),
				.tlv = अणु .p = monitor_db_scale, पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.pcm_dev = CAPTURE_2_FROM_I2S_2,
		.controls = अणु
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Switch",
				.index = 1,
				.info = snd_ctl_boolean_mono_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_B,
			पूर्ण,
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Volume",
				.index = 1,
				.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
					  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
				.info = monitor_volume_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_B_HALF_VOL
						| (1 << 8),
				.tlv = अणु .p = monitor_db_scale, पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.pcm_dev = CAPTURE_3_FROM_I2S_3,
		.controls = अणु
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Switch",
				.index = 2,
				.info = snd_ctl_boolean_mono_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_C,
			पूर्ण,
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Analog Input Monitor Playback Volume",
				.index = 2,
				.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
					  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
				.info = monitor_volume_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_C_HALF_VOL
						| (1 << 8),
				.tlv = अणु .p = monitor_db_scale, पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.pcm_dev = CAPTURE_1_FROM_SPDIF,
		.controls = अणु
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Digital Input Monitor Playback Switch",
				.info = snd_ctl_boolean_mono_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_C,
			पूर्ण,
			अणु
				.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
				.name = "Digital Input Monitor Playback Volume",
				.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
					  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
				.info = monitor_volume_info,
				.get = monitor_get,
				.put = monitor_put,
				.निजी_value = OXYGEN_ADC_MONITOR_C_HALF_VOL
						| (1 << 8),
				.tlv = अणु .p = monitor_db_scale, पूर्ण,
			पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ac97_controls[] = अणु
	AC97_VOLUME("Mic Capture Volume", 0, AC97_MIC, 0),
	AC97_SWITCH("Mic Capture Switch", 0, AC97_MIC, 15, 1),
	AC97_SWITCH("Mic Boost (+20dB)", 0, AC97_MIC, 6, 0),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Mic Source Capture Enum",
		.info = mic_fmic_source_info,
		.get = mic_fmic_source_get,
		.put = mic_fmic_source_put,
	पूर्ण,
	AC97_SWITCH("Line Capture Switch", 0, AC97_LINE, 15, 1),
	AC97_VOLUME("CD Capture Volume", 0, AC97_CD, 1),
	AC97_SWITCH("CD Capture Switch", 0, AC97_CD, 15, 1),
	AC97_VOLUME("Aux Capture Volume", 0, AC97_AUX, 1),
	AC97_SWITCH("Aux Capture Switch", 0, AC97_AUX, 15, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ac97_fp_controls[] = अणु
	AC97_VOLUME("Front Panel Playback Volume", 1, AC97_HEADPHONE, 1),
	AC97_SWITCH("Front Panel Playback Switch", 1, AC97_HEADPHONE, 15, 1),
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Front Panel Capture Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = ac97_fp_rec_volume_info,
		.get = ac97_fp_rec_volume_get,
		.put = ac97_fp_rec_volume_put,
		.tlv = अणु .p = ac97_rec_db_scale, पूर्ण,
	पूर्ण,
	AC97_SWITCH("Front Panel Capture Switch", 1, AC97_REC_GAIN, 15, 1),
पूर्ण;

अटल व्योम oxygen_any_ctl_मुक्त(काष्ठा snd_kcontrol *ctl)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	अचिन्हित पूर्णांक i;

	/* I'm too lazy to ग_लिखो a function क्रम each control :-) */
	क्रम (i = 0; i < ARRAY_SIZE(chip->controls); ++i)
		chip->controls[i] = शून्य;
पूर्ण

अटल पूर्णांक add_controls(काष्ठा oxygen *chip,
			स्थिर काष्ठा snd_kcontrol_new controls[],
			अचिन्हित पूर्णांक count)
अणु
	अटल स्थिर अक्षर *स्थिर known_ctl_names[CONTROL_COUNT] = अणु
		[CONTROL_SPDIF_PCM] =
			SNDRV_CTL_NAME_IEC958("", PLAYBACK, PCM_STREAM),
		[CONTROL_SPDIF_INPUT_BITS] =
			SNDRV_CTL_NAME_IEC958("", CAPTURE, DEFAULT),
		[CONTROL_MIC_CAPTURE_SWITCH] = "Mic Capture Switch",
		[CONTROL_LINE_CAPTURE_SWITCH] = "Line Capture Switch",
		[CONTROL_CD_CAPTURE_SWITCH] = "CD Capture Switch",
		[CONTROL_AUX_CAPTURE_SWITCH] = "Aux Capture Switch",
	पूर्ण;
	अचिन्हित पूर्णांक i;
	काष्ठा snd_kcontrol_new ढाँचा;
	काष्ठा snd_kcontrol *ctl;
	पूर्णांक j, err;

	क्रम (i = 0; i < count; ++i) अणु
		ढाँचा = controls[i];
		अगर (chip->model.control_filter) अणु
			err = chip->model.control_filter(&ढाँचा);
			अगर (err < 0)
				वापस err;
			अगर (err == 1)
				जारी;
		पूर्ण
		अगर (!म_भेद(ढाँचा.name, "Stereo Upmixing") &&
		    chip->model.dac_channels_pcm == 2)
			जारी;
		अगर (!म_भेद(ढाँचा.name, "Mic Source Capture Enum") &&
		    !(chip->model.device_config & AC97_FMIC_SWITCH))
			जारी;
		अगर (!म_भेदन(ढाँचा.name, "CD Capture ", 11) &&
		    !(chip->model.device_config & AC97_CD_INPUT))
			जारी;
		अगर (!म_भेद(ढाँचा.name, "Master Playback Volume") &&
		    chip->model.dac_tlv) अणु
			ढाँचा.tlv.p = chip->model.dac_tlv;
			ढाँचा.access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		पूर्ण
		ctl = snd_ctl_new1(&ढाँचा, chip);
		अगर (!ctl)
			वापस -ENOMEM;
		err = snd_ctl_add(chip->card, ctl);
		अगर (err < 0)
			वापस err;
		j = match_string(known_ctl_names, CONTROL_COUNT, ctl->id.name);
		अगर (j >= 0) अणु
			chip->controls[j] = ctl;
			ctl->निजी_मुक्त = oxygen_any_ctl_मुक्त;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक oxygen_mixer_init(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = add_controls(chip, controls, ARRAY_SIZE(controls));
	अगर (err < 0)
		वापस err;
	अगर (chip->model.device_config & PLAYBACK_1_TO_SPDIF) अणु
		err = add_controls(chip, spdअगर_output_controls,
				   ARRAY_SIZE(spdअगर_output_controls));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (chip->model.device_config & CAPTURE_1_FROM_SPDIF) अणु
		err = add_controls(chip, spdअगर_input_controls,
				   ARRAY_SIZE(spdअगर_input_controls));
		अगर (err < 0)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(monitor_controls); ++i) अणु
		अगर (!(chip->model.device_config & monitor_controls[i].pcm_dev))
			जारी;
		err = add_controls(chip, monitor_controls[i].controls,
				   ARRAY_SIZE(monitor_controls[i].controls));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (chip->has_ac97_0) अणु
		err = add_controls(chip, ac97_controls,
				   ARRAY_SIZE(ac97_controls));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (chip->has_ac97_1) अणु
		err = add_controls(chip, ac97_fp_controls,
				   ARRAY_SIZE(ac97_fp_controls));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस chip->model.mixer_init ? chip->model.mixer_init(chip) : 0;
पूर्ण
