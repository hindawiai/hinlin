<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA driver क्रम the Aureal Vortex family of soundprocessors.
 * Author: Manuel Jander (mjander@embedded.cl)
 *
 *   This driver is the result of the OpenVortex Project from Savannah
 * (savannah.nongnu.org/projects/खोलोvortex). I would like to thank
 * the developers of OpenVortex, Jeff Muizelaar and Kester Madकरोck, from
 * whom i got plenty of help, and their codebase was invaluable.
 *   Thanks to the ALSA developers, they helped a lot working out
 * the ALSA part.
 *   Thanks also to Sourceक्रमge क्रम मुख्यtaining the old binary drivers,
 * and the क्रमum, where developers could comunicate.
 *
 * Now at least i can play Legacy DOOM with MIDI music :-)
 */

#समावेश "au88x0.h"
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/initval.h>

// module parameters (see "Module Parameters")
अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
अटल पूर्णांक pcअगरix[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 255 पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CARD_NAME " soundcard.");
module_param_array(pcअगरix, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcअगरix, "Enable VIA-workaround for " CARD_NAME " soundcard.");

MODULE_DESCRIPTION("Aureal vortex");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, snd_vortex_ids);

अटल व्योम vortex_fix_latency(काष्ठा pci_dev *vortex)
अणु
	पूर्णांक rc;
	अगर (!(rc = pci_ग_लिखो_config_byte(vortex, 0x40, 0xff))) अणु
			dev_info(&vortex->dev, "vortex latency is 0xff\n");
	पूर्ण अन्यथा अणु
		dev_warn(&vortex->dev,
			 "could not set vortex latency: pci error 0x%x\n", rc);
	पूर्ण
पूर्ण

अटल व्योम vortex_fix_agp_bridge(काष्ठा pci_dev *via)
अणु
	पूर्णांक rc;
	u8 value;

	/*
	 * only set the bit (Extend PCI#2 Internal Master क्रम
	 * Efficient Handling of Dummy Requests) अगर the can
	 * पढ़ो the config and it is not alपढ़ोy set
	 */

	अगर (!(rc = pci_पढ़ो_config_byte(via, 0x42, &value))
			&& ((value & 0x10)
				|| !(rc = pci_ग_लिखो_config_byte(via, 0x42, value | 0x10)))) अणु
		dev_info(&via->dev, "bridge config is 0x%x\n", value | 0x10);
	पूर्ण अन्यथा अणु
		dev_warn(&via->dev,
			 "could not set vortex latency: pci error 0x%x\n", rc);
	पूर्ण
पूर्ण

अटल व्योम snd_vortex_workaround(काष्ठा pci_dev *vortex, पूर्णांक fix)
अणु
	काष्ठा pci_dev *via = शून्य;

	/* स्वतःdetect अगर workarounds are required */
	अगर (fix == 255) अणु
		/* VIA KT133 */
		via = pci_get_device(PCI_VENDOR_ID_VIA,
			PCI_DEVICE_ID_VIA_8365_1, शून्य);
		/* VIA Apollo */
		अगर (via == शून्य) अणु
			via = pci_get_device(PCI_VENDOR_ID_VIA,
				PCI_DEVICE_ID_VIA_82C598_1, शून्य);
			/* AMD Irongate */
			अगर (via == शून्य)
				via = pci_get_device(PCI_VENDOR_ID_AMD,
					PCI_DEVICE_ID_AMD_FE_GATE_7007, शून्य);
		पूर्ण
		अगर (via) अणु
			dev_info(&vortex->dev,
				 "Activating latency workaround...\n");
			vortex_fix_latency(vortex);
			vortex_fix_agp_bridge(via);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (fix & 0x1)
			vortex_fix_latency(vortex);
		अगर ((fix & 0x2) && (via = pci_get_device(PCI_VENDOR_ID_VIA,
				PCI_DEVICE_ID_VIA_8365_1, शून्य)))
			vortex_fix_agp_bridge(via);
		अगर ((fix & 0x4) && (via = pci_get_device(PCI_VENDOR_ID_VIA,
				PCI_DEVICE_ID_VIA_82C598_1, शून्य)))
			vortex_fix_agp_bridge(via);
		अगर ((fix & 0x8) && (via = pci_get_device(PCI_VENDOR_ID_AMD,
				PCI_DEVICE_ID_AMD_FE_GATE_7007, शून्य)))
			vortex_fix_agp_bridge(via);
	पूर्ण
	pci_dev_put(via);
पूर्ण

// component-deकाष्ठाor
// (see "Management of Cards and Components")
अटल पूर्णांक snd_vortex_dev_मुक्त(काष्ठा snd_device *device)
अणु
	vortex_t *vortex = device->device_data;

	vortex_gameport_unरेजिस्टर(vortex);
	vortex_core_shutकरोwn(vortex);
	// Take करोwn PCI पूर्णांकerface.
	मुक्त_irq(vortex->irq, vortex);
	iounmap(vortex->mmio);
	pci_release_regions(vortex->pci_dev);
	pci_disable_device(vortex->pci_dev);
	kमुक्त(vortex);

	वापस 0;
पूर्ण

// chip-specअगरic स्थिरructor
// (see "Management of Cards and Components")
अटल पूर्णांक
snd_vortex_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci, vortex_t ** rchip)
अणु
	vortex_t *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_vortex_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;

	// check PCI availability (DMA).
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32))) अणु
		dev_err(card->dev, "error to set DMA mask\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->card = card;

	// initialize the stuff
	chip->pci_dev = pci;
	chip->io = pci_resource_start(pci, 0);
	chip->venकरोr = pci->venकरोr;
	chip->device = pci->device;
	chip->card = card;
	chip->irq = -1;

	// (1) PCI resource allocation
	// Get MMIO area
	//
	अगर ((err = pci_request_regions(pci, CARD_NAME_SHORT)) != 0)
		जाओ regions_out;

	chip->mmio = pci_ioremap_bar(pci, 0);
	अगर (!chip->mmio) अणु
		dev_err(card->dev, "MMIO area remap failed.\n");
		err = -ENOMEM;
		जाओ ioremap_out;
	पूर्ण

	/* Init audio core.
	 * This must be करोne beक्रमe we करो request_irq otherwise we can get spurious
	 * पूर्णांकerrupts that we करो not handle properly and make a mess of things */
	अगर ((err = vortex_core_init(chip)) != 0) अणु
		dev_err(card->dev, "hw core init failed\n");
		जाओ core_out;
	पूर्ण

	अगर ((err = request_irq(pci->irq, vortex_पूर्णांकerrupt,
			       IRQF_SHARED, KBUILD_MODNAME,
	                       chip)) != 0) अणु
		dev_err(card->dev, "cannot grab irq\n");
		जाओ irq_out;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	pci_set_master(pci);
	// End of PCI setup.

	// Register alsa root device.
	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		जाओ alloc_out;
	पूर्ण

	*rchip = chip;

	वापस 0;

      alloc_out:
	मुक्त_irq(chip->irq, chip);
      irq_out:
	vortex_core_shutकरोwn(chip);
      core_out:
	iounmap(chip->mmio);
      ioremap_out:
	pci_release_regions(chip->pci_dev);
      regions_out:
	pci_disable_device(chip->pci_dev);
	//FIXME: this not the right place to unरेजिस्टर the gameport
	vortex_gameport_unरेजिस्टर(chip);
	kमुक्त(chip);
	वापस err;
पूर्ण

// स्थिरructor -- see "Constructor" sub-section
अटल पूर्णांक
snd_vortex_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	vortex_t *chip;
	पूर्णांक err;

	// (1)
	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण
	// (2)
	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	// (3)
	अगर ((err = snd_vortex_create(card, pci, &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	snd_vortex_workaround(pci, pcअगरix[dev]);

	// Card details needed in snd_vortex_midi
	म_नकल(card->driver, CARD_NAME_SHORT);
	प्र_लिखो(card->लघुname, "Aureal Vortex %s", CARD_NAME_SHORT);
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx irq %i",
		card->लघुname, chip->io, chip->irq);

	// (4) Alloc components.
	err = snd_vortex_mixer(chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	// ADB pcm.
	err = snd_vortex_new_pcm(chip, VORTEX_PCM_ADB, NR_PCM);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#अगर_अघोषित CHIP_AU8820
	// ADB SPDIF
	अगर ((err = snd_vortex_new_pcm(chip, VORTEX_PCM_SPDIF, 1)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	// A3D
	अगर ((err = snd_vortex_new_pcm(chip, VORTEX_PCM_A3D, NR_A3D)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#पूर्ण_अगर
	/*
	   // ADB I2S
	   अगर ((err = snd_vortex_new_pcm(chip, VORTEX_PCM_I2S, 1)) < 0) अणु
	   snd_card_मुक्त(card);
	   वापस err;
	   पूर्ण
	 */
#अगर_अघोषित CHIP_AU8810
	// WT pcm.
	अगर ((err = snd_vortex_new_pcm(chip, VORTEX_PCM_WT, NR_WT)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#पूर्ण_अगर
	अगर ((err = snd_vortex_midi(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	vortex_gameport_रेजिस्टर(chip);

#अगर 0
	अगर (snd_seq_device_new(card, 1, SNDRV_SEQ_DEV_ID_VORTEX_SYNTH,
			       माप(snd_vortex_synth_arg_t), &wave) < 0
	    || wave == शून्य) अणु
		dev_err(card->dev, "Can't initialize Aureal wavetable synth\n");
	पूर्ण अन्यथा अणु
		snd_vortex_synth_arg_t *arg;

		arg = SNDRV_SEQ_DEVICE_ARGPTR(wave);
		म_नकल(wave->name, "Aureal Synth");
		arg->hwptr = vortex;
		arg->index = 1;
		arg->seq_ports = seq_ports[dev];
		arg->max_voices = max_synth_voices[dev];
	पूर्ण
#पूर्ण_अगर

	// (5)
	अगर ((err = pci_पढ़ो_config_word(pci, PCI_DEVICE_ID,
				  &(chip->device))) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण	
	अगर ((err = pci_पढ़ो_config_word(pci, PCI_VENDOR_ID,
				  &(chip->venकरोr))) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	chip->rev = pci->revision;
#अगर_घोषित CHIP_AU8830
	अगर ((chip->rev) != 0xfe && (chip->rev) != 0xfa) अणु
		dev_alert(card->dev,
			  "The revision (%x) of your card has not been seen before.\n",
		       chip->rev);
		dev_alert(card->dev,
			  "Please email the results of 'lspci -vv' to openvortex-dev@nongnu.org.\n");
		snd_card_मुक्त(card);
		err = -ENODEV;
		वापस err;
	पूर्ण
#पूर्ण_अगर

	// (6)
	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	// (7)
	pci_set_drvdata(pci, card);
	dev++;
	vortex_connect_शेष(chip, 1);
	vortex_enable_पूर्णांक(chip);
	वापस 0;
पूर्ण

// deकाष्ठाor -- see "Destructor" sub-section
अटल व्योम snd_vortex_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

// pci_driver definition
अटल काष्ठा pci_driver vortex_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_vortex_ids,
	.probe = snd_vortex_probe,
	.हटाओ = snd_vortex_हटाओ,
पूर्ण;

module_pci_driver(vortex_driver);
