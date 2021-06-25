<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * C-Media CMI8788 driver क्रम C-Media's reference design and similar models
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

/*
 * CMI8788:
 *
 *   SPI 0 -> 1st AK4396 (front)
 *   SPI 1 -> 2nd AK4396 (surround)
 *   SPI 2 -> 3rd AK4396 (center/LFE)
 *   SPI 3 -> WM8785
 *   SPI 4 -> 4th AK4396 (back)
 *
 *   GPIO 0 -> DFS0 of AK5385
 *   GPIO 1 -> DFS1 of AK5385
 *
 * X-Meridian models:
 *   GPIO 4 -> enable extension S/PDIF input
 *   GPIO 6 -> enable on-board S/PDIF input
 *
 * Claro models:
 *   GPIO 6 -> S/PDIF from optical (0) or coaxial (1) input
 *   GPIO 8 -> enable headphone amplअगरier
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   CD_IN  <- CD
 *   MIC_IN <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to ADC input
 */

#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश "oxygen.h"
#समावेश "xonar_dg.h"
#समावेश "ak4396.h"
#समावेश "wm8785.h"

MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("C-Media CMI8788 driver");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "card index");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "enable card");

क्रमागत अणु
	MODEL_CMEDIA_REF,
	MODEL_MERIDIAN,
	MODEL_MERIDIAN_2G,
	MODEL_CLARO,
	MODEL_CLARO_HALO,
	MODEL_FANTASIA,
	MODEL_SERENADE,
	MODEL_2CH_OUTPUT,
	MODEL_HG2PCI,
	MODEL_XONAR_DG,
	MODEL_XONAR_DGX,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id oxygen_ids[] = अणु
	/* C-Media's reference design */
	अणु OXYGEN_PCI_SUBID(0x10b0, 0x0216), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x10b0, 0x0217), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x10b0, 0x0218), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x10b0, 0x0219), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x13f6, 0x0001), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x13f6, 0x0010), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x13f6, 0x8788), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x147a, 0xa017), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1a58, 0x0910), .driver_data = MODEL_CMEDIA_REF पूर्ण,
	/* Asus Xonar DG */
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8467), .driver_data = MODEL_XONAR_DG पूर्ण,
	/* Asus Xonar DGX */
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8521), .driver_data = MODEL_XONAR_DGX पूर्ण,
	/* PCI 2.0 HD Audio */
	अणु OXYGEN_PCI_SUBID(0x13f6, 0x8782), .driver_data = MODEL_2CH_OUTPUT पूर्ण,
	/* Kuroutoshikou CMI8787-HG2PCI */
	अणु OXYGEN_PCI_SUBID(0x13f6, 0xffff), .driver_data = MODEL_HG2PCI पूर्ण,
	/* TempoTec HiFier Fantasia */
	अणु OXYGEN_PCI_SUBID(0x14c3, 0x1710), .driver_data = MODEL_FANTASIA पूर्ण,
	/* TempoTec HiFier Serenade */
	अणु OXYGEN_PCI_SUBID(0x14c3, 0x1711), .driver_data = MODEL_SERENADE पूर्ण,
	/* AuzenTech X-Meridian */
	अणु OXYGEN_PCI_SUBID(0x415a, 0x5431), .driver_data = MODEL_MERIDIAN पूर्ण,
	/* AuzenTech X-Meridian 2G */
	अणु OXYGEN_PCI_SUBID(0x5431, 0x017a), .driver_data = MODEL_MERIDIAN_2G पूर्ण,
	/* HT-Omega Claro */
	अणु OXYGEN_PCI_SUBID(0x7284, 0x9761), .driver_data = MODEL_CLARO पूर्ण,
	/* HT-Omega Claro halo */
	अणु OXYGEN_PCI_SUBID(0x7284, 0x9781), .driver_data = MODEL_CLARO_HALO पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, oxygen_ids);


#घोषणा GPIO_AK5385_DFS_MASK	0x0003
#घोषणा GPIO_AK5385_DFS_NORMAL	0x0000
#घोषणा GPIO_AK5385_DFS_DOUBLE	0x0001
#घोषणा GPIO_AK5385_DFS_QUAD	0x0002

#घोषणा GPIO_MERIDIAN_DIG_MASK	0x0050
#घोषणा GPIO_MERIDIAN_DIG_EXT	0x0010
#घोषणा GPIO_MERIDIAN_DIG_BOARD	0x0040

#घोषणा GPIO_CLARO_DIG_COAX	0x0040
#घोषणा GPIO_CLARO_HP		0x0100

काष्ठा generic_data अणु
	अचिन्हित पूर्णांक dacs;
	u8 ak4396_regs[4][5];
	u16 wm8785_regs[3];
पूर्ण;

अटल व्योम ak4396_ग_लिखो(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
			 u8 reg, u8 value)
अणु
	/* maps ALSA channel pair number to SPI output */
	अटल स्थिर u8 codec_spi_map[4] = अणु
		0, 1, 2, 4
	पूर्ण;
	काष्ठा generic_data *data = chip->model_data;

	oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER |
			 OXYGEN_SPI_DATA_LENGTH_2 |
			 OXYGEN_SPI_CLOCK_160 |
			 (codec_spi_map[codec] << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_LATCH_CLOCK_HI,
			 AK4396_WRITE | (reg << 8) | value);
	data->ak4396_regs[codec][reg] = value;
पूर्ण

अटल व्योम ak4396_ग_लिखो_cached(काष्ठा oxygen *chip, अचिन्हित पूर्णांक codec,
				u8 reg, u8 value)
अणु
	काष्ठा generic_data *data = chip->model_data;

	अगर (value != data->ak4396_regs[codec][reg])
		ak4396_ग_लिखो(chip, codec, reg, value);
पूर्ण

अटल व्योम wm8785_ग_लिखो(काष्ठा oxygen *chip, u8 reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा generic_data *data = chip->model_data;

	oxygen_ग_लिखो_spi(chip, OXYGEN_SPI_TRIGGER |
			 OXYGEN_SPI_DATA_LENGTH_2 |
			 OXYGEN_SPI_CLOCK_160 |
			 (3 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_LATCH_CLOCK_LO,
			 (reg << 9) | value);
	अगर (reg < ARRAY_SIZE(data->wm8785_regs))
		data->wm8785_regs[reg] = value;
पूर्ण

अटल व्योम ak4396_रेजिस्टरs_init(काष्ठा oxygen *chip)
अणु
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < data->dacs; ++i) अणु
		ak4396_ग_लिखो(chip, i, AK4396_CONTROL_1,
			     AK4396_DIF_24_MSB | AK4396_RSTN);
		ak4396_ग_लिखो(chip, i, AK4396_CONTROL_2,
			     data->ak4396_regs[0][AK4396_CONTROL_2]);
		ak4396_ग_लिखो(chip, i, AK4396_CONTROL_3,
			     AK4396_PCM);
		ak4396_ग_लिखो(chip, i, AK4396_LCH_ATT,
			     chip->dac_volume[i * 2]);
		ak4396_ग_लिखो(chip, i, AK4396_RCH_ATT,
			     chip->dac_volume[i * 2 + 1]);
	पूर्ण
पूर्ण

अटल व्योम ak4396_init(काष्ठा oxygen *chip)
अणु
	काष्ठा generic_data *data = chip->model_data;

	data->dacs = chip->model.dac_channels_pcm / 2;
	data->ak4396_regs[0][AK4396_CONTROL_2] =
		AK4396_SMUTE | AK4396_DEM_OFF | AK4396_DFS_NORMAL;
	ak4396_रेजिस्टरs_init(chip);
	snd_component_add(chip->card, "AK4396");
पूर्ण

अटल व्योम ak5385_init(काष्ठा oxygen *chip)
अणु
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_AK5385_DFS_MASK);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_AK5385_DFS_MASK);
	snd_component_add(chip->card, "AK5385");
पूर्ण

अटल व्योम wm8785_रेजिस्टरs_init(काष्ठा oxygen *chip)
अणु
	काष्ठा generic_data *data = chip->model_data;

	wm8785_ग_लिखो(chip, WM8785_R7, 0);
	wm8785_ग_लिखो(chip, WM8785_R0, data->wm8785_regs[0]);
	wm8785_ग_लिखो(chip, WM8785_R2, data->wm8785_regs[2]);
पूर्ण

अटल व्योम wm8785_init(काष्ठा oxygen *chip)
अणु
	काष्ठा generic_data *data = chip->model_data;

	data->wm8785_regs[0] =
		WM8785_MCR_SLAVE | WM8785_OSR_SINGLE | WM8785_FORMAT_LJUST;
	data->wm8785_regs[2] = WM8785_HPFR | WM8785_HPFL;
	wm8785_रेजिस्टरs_init(chip);
	snd_component_add(chip->card, "WM8785");
पूर्ण

अटल व्योम generic_init(काष्ठा oxygen *chip)
अणु
	ak4396_init(chip);
	wm8785_init(chip);
पूर्ण

अटल व्योम meridian_init(काष्ठा oxygen *chip)
अणु
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_MERIDIAN_DIG_MASK);
	oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
			      GPIO_MERIDIAN_DIG_BOARD, GPIO_MERIDIAN_DIG_MASK);
	ak4396_init(chip);
	ak5385_init(chip);
पूर्ण

अटल व्योम claro_enable_hp(काष्ठा oxygen *chip)
अणु
	msleep(300);
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_CLARO_HP);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CLARO_HP);
पूर्ण

अटल व्योम claro_init(काष्ठा oxygen *chip)
अणु
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_CLARO_DIG_COAX);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CLARO_DIG_COAX);
	ak4396_init(chip);
	wm8785_init(chip);
	claro_enable_hp(chip);
पूर्ण

अटल व्योम claro_halo_init(काष्ठा oxygen *chip)
अणु
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, GPIO_CLARO_DIG_COAX);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CLARO_DIG_COAX);
	ak4396_init(chip);
	ak5385_init(chip);
	claro_enable_hp(chip);
पूर्ण

अटल व्योम fantasia_init(काष्ठा oxygen *chip)
अणु
	ak4396_init(chip);
	snd_component_add(chip->card, "CS5340");
पूर्ण

अटल व्योम stereo_output_init(काष्ठा oxygen *chip)
अणु
	ak4396_init(chip);
पूर्ण

अटल व्योम generic_cleanup(काष्ठा oxygen *chip)
अणु
पूर्ण

अटल व्योम claro_disable_hp(काष्ठा oxygen *chip)
अणु
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA, GPIO_CLARO_HP);
पूर्ण

अटल व्योम claro_cleanup(काष्ठा oxygen *chip)
अणु
	claro_disable_hp(chip);
पूर्ण

अटल व्योम claro_suspend(काष्ठा oxygen *chip)
अणु
	claro_disable_hp(chip);
पूर्ण

अटल व्योम generic_resume(काष्ठा oxygen *chip)
अणु
	ak4396_रेजिस्टरs_init(chip);
	wm8785_रेजिस्टरs_init(chip);
पूर्ण

अटल व्योम meridian_resume(काष्ठा oxygen *chip)
अणु
	ak4396_रेजिस्टरs_init(chip);
पूर्ण

अटल व्योम claro_resume(काष्ठा oxygen *chip)
अणु
	ak4396_रेजिस्टरs_init(chip);
	claro_enable_hp(chip);
पूर्ण

अटल व्योम stereo_resume(काष्ठा oxygen *chip)
अणु
	ak4396_रेजिस्टरs_init(chip);
पूर्ण

अटल व्योम set_ak4396_params(काष्ठा oxygen *chip,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	u8 value;

	value = data->ak4396_regs[0][AK4396_CONTROL_2] & ~AK4396_DFS_MASK;
	अगर (params_rate(params) <= 54000)
		value |= AK4396_DFS_NORMAL;
	अन्यथा अगर (params_rate(params) <= 108000)
		value |= AK4396_DFS_DOUBLE;
	अन्यथा
		value |= AK4396_DFS_QUAD;

	msleep(1); /* रुको क्रम the new MCLK to become stable */

	अगर (value != data->ak4396_regs[0][AK4396_CONTROL_2]) अणु
		क्रम (i = 0; i < data->dacs; ++i) अणु
			ak4396_ग_लिखो(chip, i, AK4396_CONTROL_1,
				     AK4396_DIF_24_MSB);
			ak4396_ग_लिखो(chip, i, AK4396_CONTROL_2, value);
			ak4396_ग_लिखो(chip, i, AK4396_CONTROL_1,
				     AK4396_DIF_24_MSB | AK4396_RSTN);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम update_ak4396_volume(काष्ठा oxygen *chip)
अणु
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < data->dacs; ++i) अणु
		ak4396_ग_लिखो_cached(chip, i, AK4396_LCH_ATT,
				    chip->dac_volume[i * 2]);
		ak4396_ग_लिखो_cached(chip, i, AK4396_RCH_ATT,
				    chip->dac_volume[i * 2 + 1]);
	पूर्ण
पूर्ण

अटल व्योम update_ak4396_mute(काष्ठा oxygen *chip)
अणु
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	u8 value;

	value = data->ak4396_regs[0][AK4396_CONTROL_2] & ~AK4396_SMUTE;
	अगर (chip->dac_mute)
		value |= AK4396_SMUTE;
	क्रम (i = 0; i < data->dacs; ++i)
		ak4396_ग_लिखो_cached(chip, i, AK4396_CONTROL_2, value);
पूर्ण

अटल व्योम set_wm8785_params(काष्ठा oxygen *chip,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक value;

	value = WM8785_MCR_SLAVE | WM8785_FORMAT_LJUST;
	अगर (params_rate(params) <= 48000)
		value |= WM8785_OSR_SINGLE;
	अन्यथा अगर (params_rate(params) <= 96000)
		value |= WM8785_OSR_DOUBLE;
	अन्यथा
		value |= WM8785_OSR_QUAD;
	अगर (value != data->wm8785_regs[0]) अणु
		wm8785_ग_लिखो(chip, WM8785_R7, 0);
		wm8785_ग_लिखो(chip, WM8785_R0, value);
		wm8785_ग_लिखो(chip, WM8785_R2, data->wm8785_regs[2]);
	पूर्ण
पूर्ण

अटल व्योम set_ak5385_params(काष्ठा oxygen *chip,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	अचिन्हित पूर्णांक value;

	अगर (params_rate(params) <= 54000)
		value = GPIO_AK5385_DFS_NORMAL;
	अन्यथा अगर (params_rate(params) <= 108000)
		value = GPIO_AK5385_DFS_DOUBLE;
	अन्यथा
		value = GPIO_AK5385_DFS_QUAD;
	oxygen_ग_लिखो16_masked(chip, OXYGEN_GPIO_DATA,
			      value, GPIO_AK5385_DFS_MASK);
पूर्ण

अटल व्योम set_no_params(काष्ठा oxygen *chip, काष्ठा snd_pcm_hw_params *params)
अणु
पूर्ण

अटल पूर्णांक rolloff_info(काष्ठा snd_kcontrol *ctl,
			काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[2] = अणु
		"Sharp Roll-off", "Slow Roll-off"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक rolloff_get(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा generic_data *data = chip->model_data;

	value->value.क्रमागतerated.item[0] =
		(data->ak4396_regs[0][AK4396_CONTROL_2] & AK4396_SLOW) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक rolloff_put(काष्ठा snd_kcontrol *ctl,
		       काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक changed;
	u8 reg;

	mutex_lock(&chip->mutex);
	reg = data->ak4396_regs[0][AK4396_CONTROL_2];
	अगर (value->value.क्रमागतerated.item[0])
		reg |= AK4396_SLOW;
	अन्यथा
		reg &= ~AK4396_SLOW;
	changed = reg != data->ak4396_regs[0][AK4396_CONTROL_2];
	अगर (changed) अणु
		क्रम (i = 0; i < data->dacs; ++i)
			ak4396_ग_लिखो(chip, i, AK4396_CONTROL_2, reg);
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
	काष्ठा generic_data *data = chip->model_data;

	value->value.क्रमागतerated.item[0] =
		(data->wm8785_regs[WM8785_R2] & WM8785_HPFR) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक hpf_put(काष्ठा snd_kcontrol *ctl, काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक reg;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	reg = data->wm8785_regs[WM8785_R2] & ~(WM8785_HPFR | WM8785_HPFL);
	अगर (value->value.क्रमागतerated.item[0])
		reg |= WM8785_HPFR | WM8785_HPFL;
	changed = reg != data->wm8785_regs[WM8785_R2];
	अगर (changed)
		wm8785_ग_लिखो(chip, WM8785_R2, reg);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new hpf_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "ADC Filter Capture Enum",
	.info = hpf_info,
	.get = hpf_get,
	.put = hpf_put,
पूर्ण;

अटल पूर्णांक meridian_dig_source_info(काष्ठा snd_kcontrol *ctl,
				    काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[2] = अणु "On-board", "Extension" पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक claro_dig_source_info(काष्ठा snd_kcontrol *ctl,
				 काष्ठा snd_ctl_elem_info *info)
अणु
	अटल स्थिर अक्षर *स्थिर names[2] = अणु "Optical", "Coaxial" पूर्ण;

	वापस snd_ctl_क्रमागत_info(info, 1, 2, names);
पूर्ण

अटल पूर्णांक meridian_dig_source_get(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	value->value.क्रमागतerated.item[0] =
		!!(oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA) &
		   GPIO_MERIDIAN_DIG_EXT);
	वापस 0;
पूर्ण

अटल पूर्णांक claro_dig_source_get(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;

	value->value.क्रमागतerated.item[0] =
		!!(oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA) &
		   GPIO_CLARO_DIG_COAX);
	वापस 0;
पूर्ण

अटल पूर्णांक meridian_dig_source_put(काष्ठा snd_kcontrol *ctl,
				   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 old_reg, new_reg;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	old_reg = oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA);
	new_reg = old_reg & ~GPIO_MERIDIAN_DIG_MASK;
	अगर (value->value.क्रमागतerated.item[0] == 0)
		new_reg |= GPIO_MERIDIAN_DIG_BOARD;
	अन्यथा
		new_reg |= GPIO_MERIDIAN_DIG_EXT;
	changed = new_reg != old_reg;
	अगर (changed)
		oxygen_ग_लिखो16(chip, OXYGEN_GPIO_DATA, new_reg);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक claro_dig_source_put(काष्ठा snd_kcontrol *ctl,
				काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा oxygen *chip = ctl->निजी_data;
	u16 old_reg, new_reg;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	old_reg = oxygen_पढ़ो16(chip, OXYGEN_GPIO_DATA);
	new_reg = old_reg & ~GPIO_CLARO_DIG_COAX;
	अगर (value->value.क्रमागतerated.item[0])
		new_reg |= GPIO_CLARO_DIG_COAX;
	changed = new_reg != old_reg;
	अगर (changed)
		oxygen_ग_लिखो16(chip, OXYGEN_GPIO_DATA, new_reg);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new meridian_dig_source_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "IEC958 Source Capture Enum",
	.info = meridian_dig_source_info,
	.get = meridian_dig_source_get,
	.put = meridian_dig_source_put,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new claro_dig_source_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "IEC958 Source Capture Enum",
	.info = claro_dig_source_info,
	.get = claro_dig_source_get,
	.put = claro_dig_source_put,
पूर्ण;

अटल पूर्णांक generic_mixer_init(काष्ठा oxygen *chip)
अणु
	वापस snd_ctl_add(chip->card, snd_ctl_new1(&rolloff_control, chip));
पूर्ण

अटल पूर्णांक generic_wm8785_mixer_init(काष्ठा oxygen *chip)
अणु
	पूर्णांक err;

	err = generic_mixer_init(chip);
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(chip->card, snd_ctl_new1(&hpf_control, chip));
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक meridian_mixer_init(काष्ठा oxygen *chip)
अणु
	पूर्णांक err;

	err = generic_mixer_init(chip);
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&meridian_dig_source_control, chip));
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक claro_mixer_init(काष्ठा oxygen *chip)
अणु
	पूर्णांक err;

	err = generic_wm8785_mixer_init(chip);
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&claro_dig_source_control, chip));
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल पूर्णांक claro_halo_mixer_init(काष्ठा oxygen *chip)
अणु
	पूर्णांक err;

	err = generic_mixer_init(chip);
	अगर (err < 0)
		वापस err;
	err = snd_ctl_add(chip->card,
			  snd_ctl_new1(&claro_dig_source_control, chip));
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल व्योम dump_ak4396_रेजिस्टरs(काष्ठा oxygen *chip,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक dac, i;

	क्रम (dac = 0; dac < data->dacs; ++dac) अणु
		snd_iम_लिखो(buffer, "\nAK4396 %u:", dac + 1);
		क्रम (i = 0; i < 5; ++i)
			snd_iम_लिखो(buffer, " %02x", data->ak4396_regs[dac][i]);
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम dump_wm8785_रेजिस्टरs(काष्ठा oxygen *chip,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा generic_data *data = chip->model_data;
	अचिन्हित पूर्णांक i;

	snd_iम_लिखो(buffer, "\nWM8785:");
	क्रम (i = 0; i < 3; ++i)
		snd_iम_लिखो(buffer, " %03x", data->wm8785_regs[i]);
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम dump_oxygen_रेजिस्टरs(काष्ठा oxygen *chip,
				  काष्ठा snd_info_buffer *buffer)
अणु
	dump_ak4396_रेजिस्टरs(chip, buffer);
	dump_wm8785_रेजिस्टरs(chip, buffer);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_LINEAR(ak4396_db_scale, TLV_DB_GAIN_MUTE, 0);

अटल स्थिर काष्ठा oxygen_model model_generic = अणु
	.लघुname = "C-Media CMI8788",
	.दीर्घname = "C-Media Oxygen HD Audio",
	.chip = "CMI8788",
	.init = generic_init,
	.mixer_init = generic_wm8785_mixer_init,
	.cleanup = generic_cleanup,
	.resume = generic_resume,
	.set_dac_params = set_ak4396_params,
	.set_adc_params = set_wm8785_params,
	.update_dac_volume = update_ak4396_volume,
	.update_dac_mute = update_ak4396_mute,
	.dump_रेजिस्टरs = dump_oxygen_रेजिस्टरs,
	.dac_tlv = ak4396_db_scale,
	.model_data_size = माप(काष्ठा generic_data),
	.device_config = PLAYBACK_0_TO_I2S |
			 PLAYBACK_1_TO_SPDIF |
			 PLAYBACK_2_TO_AC97_1 |
			 CAPTURE_0_FROM_I2S_1 |
			 CAPTURE_1_FROM_SPDIF |
			 CAPTURE_2_FROM_AC97_1 |
			 AC97_CD_INPUT,
	.dac_channels_pcm = 8,
	.dac_channels_mixer = 8,
	.dac_volume_min = 0,
	.dac_volume_max = 255,
	.function_flags = OXYGEN_FUNCTION_SPI |
			  OXYGEN_FUNCTION_ENABLE_SPI_4_5,
	.dac_mclks = OXYGEN_MCLKS(256, 128, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 256, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
पूर्ण;

अटल पूर्णांक get_oxygen_model(काष्ठा oxygen *chip,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[MODEL_MERIDIAN]	= "AuzenTech X-Meridian",
		[MODEL_MERIDIAN_2G]	= "AuzenTech X-Meridian 2G",
		[MODEL_CLARO]		= "HT-Omega Claro",
		[MODEL_CLARO_HALO]	= "HT-Omega Claro halo",
		[MODEL_FANTASIA]	= "TempoTec HiFier Fantasia",
		[MODEL_SERENADE]	= "TempoTec HiFier Serenade",
		[MODEL_HG2PCI]		= "CMI8787-HG2PCI",
		[MODEL_XONAR_DG]        = "Xonar DG",
		[MODEL_XONAR_DGX]       = "Xonar DGX",
	पूर्ण;

	chip->model = model_generic;
	चयन (id->driver_data) अणु
	हाल MODEL_MERIDIAN:
	हाल MODEL_MERIDIAN_2G:
		chip->model.init = meridian_init;
		chip->model.mixer_init = meridian_mixer_init;
		chip->model.resume = meridian_resume;
		chip->model.set_adc_params = set_ak5385_params;
		chip->model.dump_रेजिस्टरs = dump_ak4396_रेजिस्टरs;
		chip->model.device_config = PLAYBACK_0_TO_I2S |
					    PLAYBACK_1_TO_SPDIF |
					    CAPTURE_0_FROM_I2S_2 |
					    CAPTURE_1_FROM_SPDIF;
		अगर (id->driver_data == MODEL_MERIDIAN)
			chip->model.device_config |= AC97_CD_INPUT;
		अवरोध;
	हाल MODEL_CLARO:
		chip->model.init = claro_init;
		chip->model.mixer_init = claro_mixer_init;
		chip->model.cleanup = claro_cleanup;
		chip->model.suspend = claro_suspend;
		chip->model.resume = claro_resume;
		अवरोध;
	हाल MODEL_CLARO_HALO:
		chip->model.init = claro_halo_init;
		chip->model.mixer_init = claro_halo_mixer_init;
		chip->model.cleanup = claro_cleanup;
		chip->model.suspend = claro_suspend;
		chip->model.resume = claro_resume;
		chip->model.set_adc_params = set_ak5385_params;
		chip->model.dump_रेजिस्टरs = dump_ak4396_रेजिस्टरs;
		chip->model.device_config = PLAYBACK_0_TO_I2S |
					    PLAYBACK_1_TO_SPDIF |
					    CAPTURE_0_FROM_I2S_2 |
					    CAPTURE_1_FROM_SPDIF;
		अवरोध;
	हाल MODEL_FANTASIA:
	हाल MODEL_SERENADE:
	हाल MODEL_2CH_OUTPUT:
	हाल MODEL_HG2PCI:
		chip->model.लघुname = "C-Media CMI8787";
		chip->model.chip = "CMI8787";
		अगर (id->driver_data == MODEL_FANTASIA)
			chip->model.init = fantasia_init;
		अन्यथा
			chip->model.init = stereo_output_init;
		chip->model.resume = stereo_resume;
		chip->model.mixer_init = generic_mixer_init;
		chip->model.set_adc_params = set_no_params;
		chip->model.dump_रेजिस्टरs = dump_ak4396_रेजिस्टरs;
		chip->model.device_config = PLAYBACK_0_TO_I2S |
					    PLAYBACK_1_TO_SPDIF;
		अगर (id->driver_data == MODEL_FANTASIA) अणु
			chip->model.device_config |= CAPTURE_0_FROM_I2S_1;
			chip->model.adc_mclks = OXYGEN_MCLKS(256, 128, 128);
		पूर्ण
		chip->model.dac_channels_pcm = 2;
		chip->model.dac_channels_mixer = 2;
		अवरोध;
	हाल MODEL_XONAR_DG:
	हाल MODEL_XONAR_DGX:
		chip->model = model_xonar_dg;
		अवरोध;
	पूर्ण
	अगर (id->driver_data == MODEL_MERIDIAN ||
	    id->driver_data == MODEL_MERIDIAN_2G ||
	    id->driver_data == MODEL_CLARO_HALO) अणु
		chip->model.misc_flags = OXYGEN_MISC_MIDI;
		chip->model.device_config |= MIDI_OUTPUT | MIDI_INPUT;
	पूर्ण
	अगर (id->driver_data < ARRAY_SIZE(names) && names[id->driver_data])
		chip->model.लघुname = names[id->driver_data];
	वापस 0;
पूर्ण

अटल पूर्णांक generic_oxygen_probe(काष्ठा pci_dev *pci,
				स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		++dev;
		वापस -ENOENT;
	पूर्ण
	err = oxygen_pci_probe(pci, index[dev], id[dev], THIS_MODULE,
			       oxygen_ids, get_oxygen_model);
	अगर (err >= 0)
		++dev;
	वापस err;
पूर्ण

अटल काष्ठा pci_driver oxygen_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = oxygen_ids,
	.probe = generic_oxygen_probe,
	.हटाओ = oxygen_pci_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &oxygen_pci_pm,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(oxygen_driver);
