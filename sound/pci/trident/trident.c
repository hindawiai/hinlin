<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Trident 4DWave DX/NX & SiS SI7018 Audio PCI soundcard
 *
 *  Driver was originated by Trident <audio@tridenपंचांगicro.com>
 *  			     Fri Feb 19 15:55:28 MST 1999
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश "trident.h"
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, <audio@tridentmicro.com>");
MODULE_DESCRIPTION("Trident 4D-WaveDX/NX & SiS SI7018");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल पूर्णांक pcm_channels[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 32पूर्ण;
अटल पूर्णांक wavetable_size[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 8192पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Trident 4DWave PCI soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Trident 4DWave PCI soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Trident 4DWave PCI soundcard.");
module_param_array(pcm_channels, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_channels, "Number of hardware channels assigned for PCM.");
module_param_array(wavetable_size, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(wavetable_size, "Maximum memory size in kB for wavetable synth.");

अटल स्थिर काष्ठा pci_device_id snd_trident_ids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_TRIDENT, PCI_DEVICE_ID_TRIDENT_4DWAVE_DX), 
		PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, 0पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TRIDENT, PCI_DEVICE_ID_TRIDENT_4DWAVE_NX), 
		0, 0, 0पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_7018), 0, 0, 0पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_trident_ids);

अटल पूर्णांक snd_trident_probe(काष्ठा pci_dev *pci,
			     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_trident *trident;
	स्थिर अक्षर *str;
	पूर्णांक err, pcm_dev = 0;

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

	अगर ((err = snd_trident_create(card, pci,
				      pcm_channels[dev],
				      ((pci->venकरोr << 16) | pci->device) == TRIDENT_DEVICE_ID_SI7018 ? 1 : 2,
				      wavetable_size[dev],
				      &trident)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = trident;

	चयन (trident->device) अणु
	हाल TRIDENT_DEVICE_ID_DX:
		str = "TRID4DWAVEDX";
		अवरोध;
	हाल TRIDENT_DEVICE_ID_NX:
		str = "TRID4DWAVENX";
		अवरोध;
	हाल TRIDENT_DEVICE_ID_SI7018:
		str = "SI7018";
		अवरोध;
	शेष:
		str = "Unknown";
	पूर्ण
	म_नकल(card->driver, str);
	अगर (trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		म_नकल(card->लघुname, "SiS ");
	पूर्ण अन्यथा अणु
		म_नकल(card->लघुname, "Trident ");
	पूर्ण
	म_जोड़ो(card->लघुname, str);
	प्र_लिखो(card->दीर्घname, "%s PCI Audio at 0x%lx, irq %d",
		card->लघुname, trident->port, trident->irq);

	अगर ((err = snd_trident_pcm(trident, pcm_dev++)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	चयन (trident->device) अणु
	हाल TRIDENT_DEVICE_ID_DX:
	हाल TRIDENT_DEVICE_ID_NX:
		अगर ((err = snd_trident_foldback_pcm(trident, pcm_dev++)) < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (trident->device == TRIDENT_DEVICE_ID_NX || trident->device == TRIDENT_DEVICE_ID_SI7018) अणु
		अगर ((err = snd_trident_spdअगर_pcm(trident, pcm_dev++)) < 0) अणु
			snd_card_मुक्त(card);
			वापस err;
		पूर्ण
	पूर्ण
	अगर (trident->device != TRIDENT_DEVICE_ID_SI7018 &&
	    (err = snd_mpu401_uart_new(card, 0, MPU401_HW_TRID4DWAVE,
				       trident->midi_port,
				       MPU401_INFO_INTEGRATED |
				       MPU401_INFO_IRQ_HOOK,
				       -1, &trident->rmidi)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	snd_trident_create_gameport(trident);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_trident_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver trident_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_trident_ids,
	.probe = snd_trident_probe,
	.हटाओ = snd_trident_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &snd_trident_pm,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(trident_driver);
