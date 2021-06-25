<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cs5530.c - Initialisation code क्रम Cyrix/NatSemi VSA1 softaudio
 *
 * 	(C) Copyright 2007 Ash Willis <ashwillis@programmer.net>
 *	(C) Copyright 2003 Red Hat Inc <alan@lxorguk.ukuu.org.uk>
 *
 * This driver was ported (shamelessly ripped ;) from oss/kahlua.c but I did
 * mess with it a bit. The chip seems to have to have trouble with full duplex
 * mode. If we're recording in 8bit 8000kHz, say, and we then attempt to
 * simultaneously play back audio at 16bit 44100kHz, the device actually plays
 * back in the same क्रमmat in which it is capturing. By क्रमcing the chip to
 * always play/capture in 16/44100, we can let alsa-lib convert the samples and
 * that way we can hack up some full duplex audio. 
 * 
 * XpressAudio(पंचांग) is used on the Cyrix MediaGX (now NatSemi Geode) प्रणालीs.
 * The older version (VSA1) provides fairly good soundblaster emulation
 * although there are a couple of bugs: large DMA buffers अवरोध record,
 * and the MPU event handling seems suspect. VSA2 allows the native driver
 * to control the AC97 audio engine directly and requires a dअगरferent driver.
 *
 * Thanks to National Semiconductor क्रम providing the needed inक्रमmation
 * on the XpressAudio(पंचांग) पूर्णांकernals.
 *
 * TO DO:
 *	Investigate whether we can portably support Cognac (5520) in the
 *	same manner.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Ash Willis");
MODULE_DESCRIPTION("CS5530 Audio");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for CS5530 Audio driver.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for CS5530 Audio driver.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable CS5530 Audio driver.");

काष्ठा snd_cs5530 अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;
	काष्ठा snd_sb *sb;
	अचिन्हित दीर्घ pci_base;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_cs5530_ids[] = अणु
	अणुPCI_VENDOR_ID_CYRIX, PCI_DEVICE_ID_CYRIX_5530_AUDIO, PCI_ANY_ID,
							PCI_ANY_ID, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_cs5530_ids);

अटल पूर्णांक snd_cs5530_मुक्त(काष्ठा snd_cs5530 *chip)
अणु
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs5530_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_cs5530 *chip = device->device_data;
	वापस snd_cs5530_मुक्त(chip);
पूर्ण

अटल व्योम snd_cs5530_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल u8 snd_cs5530_mixer_पढ़ो(अचिन्हित दीर्घ io, u8 reg)
अणु
	outb(reg, io + 4);
	udelay(20);
	reg = inb(io + 5);
	udelay(20);
	वापस reg;
पूर्ण

अटल पूर्णांक snd_cs5530_create(काष्ठा snd_card *card,
			     काष्ठा pci_dev *pci,
			     काष्ठा snd_cs5530 **rchip)
अणु
	काष्ठा snd_cs5530 *chip;
	अचिन्हित दीर्घ sb_base;
	u8 irq, dma8, dma16 = 0;
	u16 map;
	व्योम __iomem *mem;
	पूर्णांक err;

	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_cs5530_dev_मुक्त,
	पूर्ण;
	*rchip = शून्य;

	err = pci_enable_device(pci);
 	अगर (err < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->card = card;
	chip->pci = pci;

	err = pci_request_regions(pci, "CS5530");
	अगर (err < 0) अणु
		kमुक्त(chip); 
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->pci_base = pci_resource_start(pci, 0);

	mem = pci_ioremap_bar(pci, 0);
	अगर (mem == शून्य) अणु
		snd_cs5530_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण

	map = पढ़ोw(mem + 0x18);
	iounmap(mem);

	/* Map bits
		0:1	* 0x20 + 0x200 = sb base
		2	sb enable
		3	adlib enable
		5	MPU enable 0x330
		6	MPU enable 0x300

	   The other bits may be used पूर्णांकernally so must be masked */

	sb_base = 0x220 + 0x20 * (map & 3);

	अगर (map & (1<<2))
		dev_info(card->dev, "XpressAudio at 0x%lx\n", sb_base);
	अन्यथा अणु
		dev_err(card->dev, "Could not find XpressAudio!\n");
		snd_cs5530_मुक्त(chip);
		वापस -ENODEV;
	पूर्ण

	अगर (map & (1<<5))
		dev_info(card->dev, "MPU at 0x300\n");
	अन्यथा अगर (map & (1<<6))
		dev_info(card->dev, "MPU at 0x330\n");

	irq = snd_cs5530_mixer_पढ़ो(sb_base, 0x80) & 0x0F;
	dma8 = snd_cs5530_mixer_पढ़ो(sb_base, 0x81);

	अगर (dma8 & 0x20)
		dma16 = 5;
	अन्यथा अगर (dma8 & 0x40)
		dma16 = 6;
	अन्यथा अगर (dma8 & 0x80)
		dma16 = 7;
	अन्यथा अणु
		dev_err(card->dev, "No 16bit DMA enabled\n");
		snd_cs5530_मुक्त(chip);
		वापस -ENODEV;
	पूर्ण

	अगर (dma8 & 0x01)
		dma8 = 0;
	अन्यथा अगर (dma8 & 02)
		dma8 = 1;
	अन्यथा अगर (dma8 & 0x08)
		dma8 = 3;
	अन्यथा अणु
		dev_err(card->dev, "No 8bit DMA enabled\n");
		snd_cs5530_मुक्त(chip);
		वापस -ENODEV;
	पूर्ण

	अगर (irq & 1)
		irq = 9;
	अन्यथा अगर (irq & 2)
		irq = 5;
	अन्यथा अगर (irq & 4)
		irq = 7;
	अन्यथा अगर (irq & 8)
		irq = 10;
	अन्यथा अणु
		dev_err(card->dev, "SoundBlaster IRQ not set\n");
		snd_cs5530_मुक्त(chip);
		वापस -ENODEV;
	पूर्ण

	dev_info(card->dev, "IRQ: %d DMA8: %d DMA16: %d\n", irq, dma8, dma16);

	err = snd_sbdsp_create(card, sb_base, irq, snd_sb16dsp_पूर्णांकerrupt, dma8,
						dma16, SB_HW_CS5530, &chip->sb);
	अगर (err < 0) अणु
		dev_err(card->dev, "Could not create SoundBlaster\n");
		snd_cs5530_मुक्त(chip);
		वापस err;
	पूर्ण

	err = snd_sb16dsp_pcm(chip->sb, 0);
	अगर (err < 0) अणु
		dev_err(card->dev, "Could not create PCM\n");
		snd_cs5530_मुक्त(chip);
		वापस err;
	पूर्ण

	err = snd_sbmixer_new(chip->sb);
	अगर (err < 0) अणु
		dev_err(card->dev, "Could not create Mixer\n");
		snd_cs5530_मुक्त(chip);
		वापस err;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		snd_cs5530_मुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = chip;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs5530_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_cs5530 *chip = शून्य;
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

	err = snd_cs5530_create(card, pci, &chip);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	म_नकल(card->driver, "CS5530");
	म_नकल(card->लघुname, "CS5530 Audio");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx", card->लघुname, chip->pci_base);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल काष्ठा pci_driver cs5530_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_cs5530_ids,
	.probe = snd_cs5530_probe,
	.हटाओ = snd_cs5530_हटाओ,
पूर्ण;

module_pci_driver(cs5530_driver);
