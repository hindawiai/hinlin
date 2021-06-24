<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  The driver क्रम the Cirrus Logic's Sound Fusion CS46XX based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

/*
  NOTES:
  - someबार the sound is metallic and sibilant, unloading and 
    reloading the module may solve this.
*/

#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश "cs46xx.h"
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Cirrus Logic Sound Fusion CS46XX");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल bool बाह्यal_amp[SNDRV_CARDS];
अटल bool thinkpad[SNDRV_CARDS];
अटल bool mmap_valid[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for the CS46xx soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for the CS46xx soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable CS46xx soundcard.");
module_param_array(बाह्यal_amp, bool, शून्य, 0444);
MODULE_PARM_DESC(बाह्यal_amp, "Force to enable external amplifier.");
module_param_array(thinkpad, bool, शून्य, 0444);
MODULE_PARM_DESC(thinkpad, "Force to enable Thinkpad's CLKRUN control.");
module_param_array(mmap_valid, bool, शून्य, 0444);
MODULE_PARM_DESC(mmap_valid, "Support OSS mmap.");

अटल स्थिर काष्ठा pci_device_id snd_cs46xx_ids[] = अणु
	अणु PCI_VDEVICE(CIRRUS, 0x6001), 0, पूर्ण,   /* CS4280 */
	अणु PCI_VDEVICE(CIRRUS, 0x6003), 0, पूर्ण,   /* CS4612 */
	अणु PCI_VDEVICE(CIRRUS, 0x6004), 0, पूर्ण,   /* CS4615 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_cs46xx_ids);

अटल पूर्णांक snd_card_cs46xx_probe(काष्ठा pci_dev *pci,
				 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_cs46xx *chip;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;
	अगर ((err = snd_cs46xx_create(card, pci,
				     बाह्यal_amp[dev], thinkpad[dev],
				     &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;
	chip->accept_valid = mmap_valid[dev];
	अगर ((err = snd_cs46xx_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर ((err = snd_cs46xx_pcm_rear(chip, 1)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_cs46xx_pcm_iec958(chip, 2)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#पूर्ण_अगर
	अगर ((err = snd_cs46xx_mixer(chip, 2)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#अगर_घोषित CONFIG_SND_CS46XX_NEW_DSP
	अगर (chip->nr_ac97_codecs ==2) अणु
		अगर ((err = snd_cs46xx_pcm_center_lfe(chip, 3)) < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर ((err = snd_cs46xx_midi(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_cs46xx_start_dsp(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण


	snd_cs46xx_gameport(chip);

	म_नकल(card->driver, "CS46xx");
	म_नकल(card->लघुname, "Sound Fusion CS46xx");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx/0x%lx, irq %i",
		card->लघुname,
		chip->ba0_addr,
		chip->ba1_addr,
		chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_card_cs46xx_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver cs46xx_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_cs46xx_ids,
	.probe = snd_card_cs46xx_probe,
	.हटाओ = snd_card_cs46xx_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &snd_cs46xx_pm,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cs46xx_driver);
