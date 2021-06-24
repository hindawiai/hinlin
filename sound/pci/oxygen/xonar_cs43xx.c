<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * card driver क्रम models with CS4398/CS4362A DACs (Xonar D1/DX)
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

/*
 * Xonar D1/DX
 * -----------
 *
 * CMI8788:
 *
 *   IतऑC <-> CS4398 (addr 1001111) (front)
 *       <-> CS4362A (addr 0011000) (surround, center/LFE, back)
 *
 *   GPI 0 <- बाह्यal घातer present (DX only)
 *
 *   GPIO 0 -> enable output to speakers
 *   GPIO 1 -> route output to front panel
 *   GPIO 2 -> M0 of CS5361
 *   GPIO 3 -> M1 of CS5361
 *   GPIO 6 -> ?
 *   GPIO 7 -> ?
 *   GPIO 8 -> route input jack to line-in (0) or mic-in (1)
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN  <- aux
 *   MIC_IN  <- mic
 *   FMIC_IN <- front mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5361 input
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश "xonar.h"
#समावेश "cm9780.h"
#समावेश "cs4398.h"
#समावेश "cs4362a.h"

#घोषणा GPI_EXT_POWER		0x01
#घोषणा GPIO_D1_OUTPUT_ENABLE	0x0001
#घोषणा GPIO_D1_FRONT_PANEL	0x0002
#घोषणा GPIO_D1_MAGIC		0x00c0
#घोषणा GPIO_D1_INPUT_ROUTE	0x0100

#घोषणा I2C_DEVICE_CS4398	0x9e	/* 10011, AD1=1, AD0=1, /W=0 */
#घोषणा I2C_DEVICE_CS4362A	0x30	/* 001100, AD0=0, /W=0 */

काष्ठा xonar_cs43xx अणु
	काष्ठा xonar_generic generic;
	u8 cs4398_regs[8];
	u8 cs4362a_regs[15];
पूर्ण;

अटल व्योम cs4398_ग_लिखो(काष्ठा oxygen *chip, u8 reg, u8 value)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;

	oxygen_ग_लिखो_i2c(chip, I2C_DEVICE_CS4398, reg, value);
	अगर (reg < ARRAY_SIZE(data->cs4398_regs))
		data->cs4398_regs[reg] = value;
पूर्ण

अटल व्योम cs4398_ग_लिखो_cached(काष्ठा oxygen *chip, u8 reg, u8 value)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;

	अगर (value != data->cs4398_regs[reg])
		cs4398_ग_लिखो(chip, reg, value);
पूर्ण

अटल व्योम cs4362a_ग_लिखो(काष्ठा oxygen *chip, u8 reg, u8 value)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;

	oxygen_ग_लिखो_i2c(chip, I2C_DEVICE_CS4362A, reg, value);
	अगर (reg < ARRAY_SIZE(data->cs4362a_regs))
		data->cs4362a_regs[reg] = value;
पूर्ण

अटल व्योम cs4362a_ग_लिखो_cached(काष्ठा oxygen *chip, u8 reg, u8 value)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;

	अगर (value != data->cs4362a_regs[reg])
		cs4362a_ग_लिखो(chip, reg, value);
पूर्ण

अटल व्योम cs43xx_रेजिस्टरs_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	/* set CPEN (control port mode) and घातer करोwn */
	cs4398_ग_लिखो(chip, 8, CS4398_CPEN | CS4398_PDN);
	cs4362a_ग_लिखो(chip, 0x01, CS4362A_PDN | CS4362A_CPEN);
	/* configure */
	cs4398_ग_लिखो(chip, 2, data->cs4398_regs[2]);
	cs4398_ग_लिखो(chip, 3, CS4398_ATAPI_B_R | CS4398_ATAPI_A_L);
	cs4398_ग_लिखो(chip, 4, data->cs4398_regs[4]);
	cs4398_ग_लिखो(chip, 5, data->cs4398_regs[5]);
	cs4398_ग_लिखो(chip, 6, data->cs4398_regs[6]);
	cs4398_ग_लिखो(chip, 7, data->cs4398_regs[7]);
	cs4362a_ग_लिखो(chip, 0x02, CS4362A_DIF_LJUST);
	cs4362a_ग_लिखो(chip, 0x03, CS4362A_MUTEC_6 | CS4362A_AMUTE |
		      CS4362A_RMP_UP | CS4362A_ZERO_CROSS | CS4362A_SOFT_RAMP);
	cs4362a_ग_लिखो(chip, 0x04, data->cs4362a_regs[0x04]);
	cs4362a_ग_लिखो(chip, 0x05, 0);
	क्रम (i = 6; i <= 14; ++i)
		cs4362a_ग_लिखो(chip, i, data->cs4362a_regs[i]);
	/* clear घातer करोwn */
	cs4398_ग_लिखो(chip, 8, CS4398_CPEN);
	cs4362a_ग_लिखो(chip, 0x01, CS4362A_CPEN);
पूर्ण

अटल व्योम xonar_d1_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;

	data->generic.anti_pop_delay = 800;
	data->generic.output_enable_bit = GPIO_D1_OUTPUT_ENABLE;
	data->cs4398_regs[2] =
		CS4398_FM_SINGLE | CS4398_DEM_NONE | CS4398_DIF_LJUST;
	data->cs4398_regs[4] = CS4398_MUTEP_LOW |
		CS4398_MUTE_B | CS4398_MUTE_A | CS4398_PAMUTE;
	data->cs4398_regs[5] = 60 * 2;
	data->cs4398_regs[6] = 60 * 2;
	data->cs4398_regs[7] = CS4398_RMP_DN | CS4398_RMP_UP |
		CS4398_ZERO_CROSS | CS4398_SOFT_RAMP;
	data->cs4362a_regs[4] = CS4362A_RMP_DN | CS4362A_DEM_NONE;
	data->cs4362a_regs[6] = CS4362A_FM_SINGLE |
		CS4362A_ATAPI_B_R | CS4362A_ATAPI_A_L;
	data->cs4362a_regs[7] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[8] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[9] = data->cs4362a_regs[6];
	data->cs4362a_regs[10] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[11] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[12] = data->cs4362a_regs[6];
	data->cs4362a_regs[13] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[14] = 60 | CS4362A_MUTE;

	oxygen_ग_लिखो16(chip, OXYGEN_2WIRE_BUS_STATUS,
		       OXYGEN_2WIRE_LENGTH_8 |
		       OXYGEN_2WIRE_INTERRUPT_MASK |
		       OXYGEN_2WIRE_SPEED_FAST);

	cs43xx_रेजिस्टरs_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_D1_FRONT_PANEL |
			  GPIO_D1_MAGIC |
			  GPIO_D1_INPUT_ROUTE);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA,
			    GPIO_D1_FRONT_PANEL | GPIO_D1_INPUT_ROUTE);

	xonar_init_cs53x1(chip);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "CS4398");
	snd_component_add(chip->card, "CS4362A");
	snd_component_add(chip->card, "CS5361");
पूर्ण

अटल व्योम xonar_dx_init(काष्ठा oxygen *chip)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;

	data->generic.ext_घातer_reg = OXYGEN_GPI_DATA;
	data->generic.ext_घातer_पूर्णांक_reg = OXYGEN_GPI_INTERRUPT_MASK;
	data->generic.ext_घातer_bit = GPI_EXT_POWER;
	xonar_init_ext_घातer(chip);
	xonar_d1_init(chip);
पूर्ण

अटल व्योम xonar_d1_cleanup(काष्ठा oxygen *chip)
अणु
	xonar_disable_output(chip);
	cs4362a_ग_लिखो(chip, 0x01, CS4362A_PDN | CS4362A_CPEN);
	oxygen_clear_bits8(chip, OXYGEN_FUNCTION, OXYGEN_FUNCTION_RESET_CODEC);
पूर्ण

अटल व्योम xonar_d1_suspend(काष्ठा oxygen *chip)
अणु
	xonar_d1_cleanup(chip);
पूर्ण

अटल व्योम xonar_d1_resume(काष्ठा oxygen *chip)
अणु
	oxygen_set_bits8(chip, OXYGEN_FUNCTION, OXYGEN_FUNCTION_RESET_CODEC);
	msleep(1);
	cs43xx_रेजिस्टरs_init(chip);
	xonar_enable_output(chip);
पूर्ण

अटल व्योम set_cs43xx_params(काष्ठा oxygen *chip,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;
	u8 cs4398_fm, cs4362a_fm;

	अगर (params_rate(params) <= 50000) अणु
		cs4398_fm = CS4398_FM_SINGLE;
		cs4362a_fm = CS4362A_FM_SINGLE;
	पूर्ण अन्यथा अगर (params_rate(params) <= 100000) अणु
		cs4398_fm = CS4398_FM_DOUBLE;
		cs4362a_fm = CS4362A_FM_DOUBLE;
	पूर्ण अन्यथा अणु
		cs4398_fm = CS4398_FM_QUAD;
		cs4362a_fm = CS4362A_FM_QUAD;
	पूर्ण
	cs4398_fm |= CS4398_DEM_NONE | CS4398_DIF_LJUST;
	cs4398_ग_लिखो_cached(chip, 2, cs4398_fm);
	cs4362a_fm |= data->cs4362a_regs[6] & ~CS4362A_FM_MASK;
	cs4362a_ग_लिखो_cached(chip, 6, cs4362a_fm);
	cs4362a_ग_लिखो_cached(chip, 12, cs4362a_fm);
	cs4362a_fm &= CS4362A_FM_MASK;
	cs4362a_fm |= data->cs4362a_regs[9] & ~CS4362A_FM_MASK;
	cs4362a_ग_लिखो_cached(chip, 9, cs4362a_fm);
पूर्ण

अटल व्योम update_cs4362a_volumes(काष्ठा oxygen *chip)
अणु
	अचिन्हित पूर्णांक i;
	u8 mute;

	mute = chip->dac_mute ? CS4362A_MUTE : 0;
	क्रम (i = 0; i < 6; ++i)
		cs4362a_ग_लिखो_cached(chip, 7 + i + i / 2,
				     (127 - chip->dac_volume[2 + i]) | mute);
पूर्ण

अटल व्योम update_cs43xx_volume(काष्ठा oxygen *chip)
अणु
	cs4398_ग_लिखो_cached(chip, 5, (127 - chip->dac_volume[0]) * 2);
	cs4398_ग_लिखो_cached(chip, 6, (127 - chip->dac_volume[1]) * 2);
	update_cs4362a_volumes(chip);
पूर्ण

अटल व्योम update_cs43xx_mute(काष्ठा oxygen *chip)
अणु
	u8 reg;

	reg = CS4398_MUTEP_LOW | CS4398_PAMUTE;
	अगर (chip->dac_mute)
		reg |= CS4398_MUTE_B | CS4398_MUTE_A;
	cs4398_ग_लिखो_cached(chip, 4, reg);
	update_cs4362a_volumes(chip);
पूर्ण

अटल व्योम update_cs43xx_center_lfe_mix(काष्ठा oxygen *chip, bool mixed)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;
	u8 reg;

	reg = data->cs4362a_regs[9] & ~CS4362A_ATAPI_MASK;
	अगर (mixed)
		reg |= CS4362A_ATAPI_B_LR | CS4362A_ATAPI_A_LR;
	अन्यथा
		reg |= CS4362A_ATAPI_B_R | CS4362A_ATAPI_A_L;
	cs4362a_ग_लिखो_cached(chip, 9, reg);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new front_panel_चयन = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Front Panel Playback Switch",
	.info = snd_ctl_boolean_mono_info,
	.get = xonar_gpio_bit_चयन_get,
	.put = xonar_gpio_bit_चयन_put,
	.निजी_value = GPIO_D1_FRONT_PANEL,
पूर्ण;

अटल पूर्णांक rolloff_info(काष्ठा snd_kcontrol *ctl,
			काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[2] = अणु
		"Fast Roll-off", "Slow Roll-off"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक rolloff_get(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_cs43xx *data = chip->model_data;

	value->value.क्रमागतerated.item[0] =
		(data->cs4398_regs[7] & CS4398_FILT_SEL) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक rolloff_put(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा xonar_cs43xx *data = chip->model_data;
	पूर्णांक changed;
	u8 reg;

	mutex_lock(&chip->mutex);
	reg = data->cs4398_regs[7];
	अगर (value->value.क्रमागतerated.item[0])
		reg |= CS4398_FILT_SEL;
	अन्यथा
		reg &= ~CS4398_FILT_SEL;
	changed = reg != data->cs4398_regs[7];
	अगर (changed) अणु
		cs4398_ग_लिखो(chip, 7, reg);
		अगर (reg & CS4398_FILT_SEL)
			reg = data->cs4362a_regs[0x04] | CS4362A_FILT_SEL;
		अन्यथा
			reg = data->cs4362a_regs[0x04] & ~CS4362A_FILT_SEL;
		cs4362a_ग_लिखो(chip, 0x04, reg);
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rolloff_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DAC Filter Playback Enum",
	.info = rolloff_info,
	.get = rolloff_get,
	.put = rolloff_put,
पूर्ण;

अटल व्योम xonar_d1_line_mic_ac97_चयन(काष्ठा oxygen *chip,
					  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mute)
अणु
	अगर (reg == AC97_LINE) अणु
		spin_lock_irq(&chip->reg_lock);
		oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
				      mute ? GPIO_D1_INPUT_ROUTE : 0,
				      GPIO_D1_INPUT_ROUTE);
		spin_unlock_irq(&chip->reg_lock);
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(cs4362a_db_scale, -6000, 100, 0);

अटल पूर्णांक xonar_d1_mixer_init(काष्ठा oxygen *chip)
अणु
	पूर्णांक err;

	err = snd_ctl_add(chip->card, snd_ctl_new1(&front_panel_चयन, chip));
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(chip->card, snd_ctl_new1(&rolloff_control, chip));
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल व्योम dump_cs4362a_रेजिस्टरs(काष्ठा xonar_cs43xx *data,
				   काष्ठा snd_info_buffer *buffer)
अणु
	अचिन्हित पूर्णांक i;

	snd_iम_लिखो(buffer, "\nCS4362A:");
	क्रम (i = 1; i <= 14; ++i)
		snd_iम_लिखो(buffer, " %02x", data->cs4362a_regs[i]);
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम dump_d1_रेजिस्टरs(काष्ठा oxygen *chip,
			      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा xonar_cs43xx *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	snd_iम_लिखो(buffer, "\nCS4398: 7?");
	क्रम (i = 2; i < 8; ++i)
		snd_iम_लिखो(buffer, " %02x", data->cs4398_regs[i]);
	snd_iम_लिखो(buffer, "\n");
	dump_cs4362a_रेजिस्टरs(data, buffer);
पूर्ण

अटल स्थिर काष्ठा oxygen_model model_xonar_d1 = अणु
	.दीर्घname = "Asus Virtuoso 100",
	.chip = "AV200",
	.init = xonar_d1_init,
	.mixer_init = xonar_d1_mixer_init,
	.cleanup = xonar_d1_cleanup,
	.suspend = xonar_d1_suspend,
	.resume = xonar_d1_resume,
	.set_dac_params = set_cs43xx_params,
	.set_adc_params = xonar_set_cs53x1_params,
	.update_dac_volume = update_cs43xx_volume,
	.update_dac_mute = update_cs43xx_mute,
	.update_center_lfe_mix = update_cs43xx_center_lfe_mix,
	.ac97_चयन = xonar_d1_line_mic_ac97_चयन,
	.dump_रेजिस्टरs = dump_d1_रेजिस्टरs,
	.dac_tlv = cs4362a_db_scale,
	.model_data_size = माप(काष्ठा xonar_cs43xx),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 CAPTURE_0_FROM_I2S_2 |
			 CAPTURE_1_FROM_SPDIF |
			 AC97_FMIC_SWITCH,
	.dac_channels_pcm = 8,
	.dac_channels_mixer = 8,
	.dac_volume_min = 127 - 60,
	.dac_volume_max = 127,
	.function_flags = OXYGEN_FUNCTION_2WIRE,
	.dac_mclks = OXYGEN_MCLKS(256, 128, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 128, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;

पूर्णांक get_xonar_cs43xx_model(काष्ठा oxygen *chip,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	चयन (id->subdevice) अणु
	हाल 0x834f:
		chip->model = model_xonar_d1;
		chip->model.लघुname = "Xonar D1";
		अवरोध;
	हाल 0x8275:
	हाल 0x8327:
		chip->model = model_xonar_d1;
		chip->model.लघुname = "Xonar DX";
		chip->model.init = xonar_dx_init;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
