<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * C-Media CMI8787 driver क्रम the Studio Evolution SE6X
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

/*
 * CMI8787:
 *
 *   SPI    -> microcontroller (not actually used)
 *   GPIO 0 -> करो.
 *   GPIO 2 -> करो.
 *
 *   DAC0   -> both PCM1792A (L+R, each in mono mode)
 *   ADC1  <-  1st PCM1804
 *   ADC2  <-  2nd PCM1804
 *   ADC3  <-  3rd PCM1804
 */

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश "oxygen.h"

MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("Studio Evolution SE6X driver");
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

अटल स्थिर काष्ठा pci_device_id se6x_ids[] = अणु
	अणु OXYGEN_PCI_SUBID(0x13f6, 0x8788) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, se6x_ids);

अटल व्योम se6x_init(काष्ठा oxygen *chip)
अणु
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL, 0x005);

	snd_component_add(chip->card, "PCM1792A");
	snd_component_add(chip->card, "PCM1804");
पूर्ण

अटल पूर्णांक se6x_control_filter(काष्ठा snd_kcontrol_new *ढाँचा)
अणु
	/* no DAC volume/mute */
	अगर (!म_भेदन(ढाँचा->name, "Master Playback ", 16))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम se6x_cleanup(काष्ठा oxygen *chip)
अणु
पूर्ण

अटल व्योम set_pcm1792a_params(काष्ठा oxygen *chip,
				काष्ठा snd_pcm_hw_params *params)
अणु
	/* nothing to करो (the microcontroller monitors DAC_LRCK) */
पूर्ण

अटल व्योम set_pcm1804_params(काष्ठा oxygen *chip,
			       काष्ठा snd_pcm_hw_params *params)
अणु
पूर्ण

अटल अचिन्हित पूर्णांक se6x_adjust_dac_routing(काष्ठा oxygen *chip,
					    अचिन्हित पूर्णांक play_routing)
अणु
	/* route the same stereo pair to DAC0 and DAC1 */
	वापस ( play_routing       & OXYGEN_PLAY_DAC0_SOURCE_MASK) |
	       ((play_routing << 2) & OXYGEN_PLAY_DAC1_SOURCE_MASK);
पूर्ण

अटल स्थिर काष्ठा oxygen_model model_se6x = अणु
	.लघुname = "Studio Evolution SE6X",
	.दीर्घname = "C-Media Oxygen HD Audio",
	.chip = "CMI8787",
	.init = se6x_init,
	.control_filter = se6x_control_filter,
	.cleanup = se6x_cleanup,
	.set_dac_params = set_pcm1792a_params,
	.set_adc_params = set_pcm1804_params,
	.adjust_dac_routing = se6x_adjust_dac_routing,
	.device_config = PLAYBACK_0_TO_I2S |
			 CAPTURE_0_FROM_I2S_1 |
			 CAPTURE_2_FROM_I2S_2 |
			 CAPTURE_3_FROM_I2S_3,
	.dac_channels_pcm = 2,
	.function_flags = OXYGEN_FUNCTION_SPI,
	.dac_mclks = OXYGEN_MCLKS(256, 128, 128),
	.adc_mclks = OXYGEN_MCLKS(256, 256, 128),
	.dac_i2s_क्रमmat = OXYGEN_I2S_FORMAT_LJUST,
	.adc_i2s_क्रमmat = OXYGEN_I2S_FORMAT_I2S,
पूर्ण;

अटल पूर्णांक se6x_get_model(काष्ठा oxygen *chip,
			  स्थिर काष्ठा pci_device_id *pci_id)
अणु
	chip->model = model_se6x;
	वापस 0;
पूर्ण

अटल पूर्णांक se6x_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
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
			       se6x_ids, se6x_get_model);
	अगर (err >= 0)
		++dev;
	वापस err;
पूर्ण

अटल काष्ठा pci_driver se6x_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = se6x_ids,
	.probe = se6x_probe,
	.हटाओ = oxygen_pci_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &oxygen_pci_pm,
	पूर्ण,
#पूर्ण_अगर
	.shutकरोwn = oxygen_pci_shutकरोwn,
पूर्ण;

module_pci_driver(se6x_driver);
