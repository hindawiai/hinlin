<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम audio on multअगरunction CS5535/6 companion device
 * Copyright (C) Jaya Kumar
 *
 * Based on Jaroslav Kysela and Takashi Iwai's examples.
 * This work was sponsored by CIS(M) Sdn Bhd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/asoundef.h>
#समावेश "cs5535audio.h"

#घोषणा DRIVER_NAME "cs5535audio"

अटल अक्षर *ac97_quirk;
module_param(ac97_quirk, अक्षरp, 0444);
MODULE_PARM_DESC(ac97_quirk, "AC'97 board specific workarounds.");

अटल स्थिर काष्ठा ac97_quirk ac97_quirks[] = अणु
#अगर 0 /* Not yet confirmed अगर all 5536 boards are HP only */
	अणु
		.subvenकरोr = PCI_VENDOR_ID_AMD, 
		.subdevice = PCI_DEVICE_ID_AMD_CS5536_AUDIO, 
		.name = "AMD RDK",     
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " DRIVER_NAME);
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " DRIVER_NAME);
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " DRIVER_NAME);

अटल स्थिर काष्ठा pci_device_id snd_cs5535audio_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_CS5535_AUDIO) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_AUDIO) पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_cs5535audio_ids);

अटल व्योम रुको_till_cmd_acked(काष्ठा cs5535audio *cs5535au, अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	करो अणु
		पंचांगp = cs_पढ़ोl(cs5535au, ACC_CODEC_CNTL);
		अगर (!(पंचांगp & CMD_NEW))
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--समयout);
	अगर (!समयout)
		dev_err(cs5535au->card->dev,
			"Failure writing to cs5535 codec\n");
पूर्ण

अटल अचिन्हित लघु snd_cs5535audio_codec_पढ़ो(काष्ठा cs5535audio *cs5535au,
						 अचिन्हित लघु reg)
अणु
	अचिन्हित पूर्णांक regdata;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक val;

	regdata = ((अचिन्हित पूर्णांक) reg) << 24;
	regdata |= ACC_CODEC_CNTL_RD_CMD;
	regdata |= CMD_NEW;

	cs_ग_लिखोl(cs5535au, ACC_CODEC_CNTL, regdata);
	रुको_till_cmd_acked(cs5535au, 50);

	समयout = 50;
	करो अणु
		val = cs_पढ़ोl(cs5535au, ACC_CODEC_STATUS);
		अगर ((val & STS_NEW) && reg == (val >> 24))
			अवरोध;
		udelay(1);
	पूर्ण जबतक (--समयout);
	अगर (!समयout)
		dev_err(cs5535au->card->dev,
			"Failure reading codec reg 0x%x, Last value=0x%x\n",
			reg, val);

	वापस (अचिन्हित लघु) val;
पूर्ण

अटल व्योम snd_cs5535audio_codec_ग_लिखो(काष्ठा cs5535audio *cs5535au,
					अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	अचिन्हित पूर्णांक regdata;

	regdata = ((अचिन्हित पूर्णांक) reg) << 24;
	regdata |= val;
	regdata &= CMD_MASK;
	regdata |= CMD_NEW;
	regdata &= ACC_CODEC_CNTL_WR_CMD;

	cs_ग_लिखोl(cs5535au, ACC_CODEC_CNTL, regdata);
	रुको_till_cmd_acked(cs5535au, 50);
पूर्ण

अटल व्योम snd_cs5535audio_ac97_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
					     अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा cs5535audio *cs5535au = ac97->निजी_data;
	snd_cs5535audio_codec_ग_लिखो(cs5535au, reg, val);
पूर्ण

अटल अचिन्हित लघु snd_cs5535audio_ac97_codec_पढ़ो(काष्ठा snd_ac97 *ac97,
						      अचिन्हित लघु reg)
अणु
	काष्ठा cs5535audio *cs5535au = ac97->निजी_data;
	वापस snd_cs5535audio_codec_पढ़ो(cs5535au, reg);
पूर्ण

अटल पूर्णांक snd_cs5535audio_mixer(काष्ठा cs5535audio *cs5535au)
अणु
	काष्ठा snd_card *card = cs5535au->card;
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_cs5535audio_ac97_codec_ग_लिखो,
		.पढ़ो = snd_cs5535audio_ac97_codec_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.scaps = AC97_SCAP_AUDIO | AC97_SCAP_SKIP_MODEM
			| AC97_SCAP_POWER_SAVE;
	ac97.निजी_data = cs5535au;
	ac97.pci = cs5535au->pci;

	/* set any OLPC-specअगरic scaps */
	olpc_prequirks(card, &ac97);

	अगर ((err = snd_ac97_mixer(pbus, &ac97, &cs5535au->ac97)) < 0) अणु
		dev_err(card->dev, "mixer failed\n");
		वापस err;
	पूर्ण

	snd_ac97_tune_hardware(cs5535au->ac97, ac97_quirks, ac97_quirk);

	err = olpc_quirks(card, cs5535au->ac97);
	अगर (err < 0) अणु
		dev_err(card->dev, "olpc quirks failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम process_bm0_irq(काष्ठा cs5535audio *cs5535au)
अणु
	u8 bm_stat;
	spin_lock(&cs5535au->reg_lock);
	bm_stat = cs_पढ़ोb(cs5535au, ACC_BM0_STATUS);
	spin_unlock(&cs5535au->reg_lock);
	अगर (bm_stat & EOP) अणु
		snd_pcm_period_elapsed(cs5535au->playback_substream);
	पूर्ण अन्यथा अणु
		dev_err(cs5535au->card->dev,
			"unexpected bm0 irq src, bm_stat=%x\n",
			bm_stat);
	पूर्ण
पूर्ण

अटल व्योम process_bm1_irq(काष्ठा cs5535audio *cs5535au)
अणु
	u8 bm_stat;
	spin_lock(&cs5535au->reg_lock);
	bm_stat = cs_पढ़ोb(cs5535au, ACC_BM1_STATUS);
	spin_unlock(&cs5535au->reg_lock);
	अगर (bm_stat & EOP)
		snd_pcm_period_elapsed(cs5535au->capture_substream);
पूर्ण

अटल irqवापस_t snd_cs5535audio_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u16 acc_irq_stat;
	अचिन्हित अक्षर count;
	काष्ठा cs5535audio *cs5535au = dev_id;

	अगर (cs5535au == शून्य)
		वापस IRQ_NONE;

	acc_irq_stat = cs_पढ़ोw(cs5535au, ACC_IRQ_STATUS);

	अगर (!acc_irq_stat)
		वापस IRQ_NONE;
	क्रम (count = 0; count < 4; count++) अणु
		अगर (acc_irq_stat & (1 << count)) अणु
			चयन (count) अणु
			हाल IRQ_STS:
				cs_पढ़ोl(cs5535au, ACC_GPIO_STATUS);
				अवरोध;
			हाल WU_IRQ_STS:
				cs_पढ़ोl(cs5535au, ACC_GPIO_STATUS);
				अवरोध;
			हाल BM0_IRQ_STS:
				process_bm0_irq(cs5535au);
				अवरोध;
			हाल BM1_IRQ_STS:
				process_bm1_irq(cs5535au);
				अवरोध;
			शेष:
				dev_err(cs5535au->card->dev,
					"Unexpected irq src: 0x%x\n",
					acc_irq_stat);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक snd_cs5535audio_मुक्त(काष्ठा cs5535audio *cs5535au)
अणु
	pci_set_घातer_state(cs5535au->pci, PCI_D3hot);

	अगर (cs5535au->irq >= 0)
		मुक्त_irq(cs5535au->irq, cs5535au);

	pci_release_regions(cs5535au->pci);
	pci_disable_device(cs5535au->pci);
	kमुक्त(cs5535au);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs5535audio_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा cs5535audio *cs5535au = device->device_data;
	वापस snd_cs5535audio_मुक्त(cs5535au);
पूर्ण

अटल पूर्णांक snd_cs5535audio_create(काष्ठा snd_card *card,
				  काष्ठा pci_dev *pci,
				  काष्ठा cs5535audio **rcs5535au)
अणु
	काष्ठा cs5535audio *cs5535au;

	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_cs5535audio_dev_मुक्त,
	पूर्ण;

	*rcs5535au = शून्य;
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(32))) अणु
		dev_warn(card->dev, "unable to get 32bit dma\n");
		err = -ENXIO;
		जाओ pcअगरail;
	पूर्ण

	cs5535au = kzalloc(माप(*cs5535au), GFP_KERNEL);
	अगर (cs5535au == शून्य) अणु
		err = -ENOMEM;
		जाओ pcअगरail;
	पूर्ण

	spin_lock_init(&cs5535au->reg_lock);
	cs5535au->card = card;
	cs5535au->pci = pci;
	cs5535au->irq = -1;

	अगर ((err = pci_request_regions(pci, "CS5535 Audio")) < 0) अणु
		kमुक्त(cs5535au);
		जाओ pcअगरail;
	पूर्ण

	cs5535au->port = pci_resource_start(pci, 0);

	अगर (request_irq(pci->irq, snd_cs5535audio_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, cs5535au)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		err = -EBUSY;
		जाओ sndfail;
	पूर्ण

	cs5535au->irq = pci->irq;
	card->sync_irq = cs5535au->irq;
	pci_set_master(pci);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL,
				  cs5535au, &ops)) < 0)
		जाओ sndfail;

	*rcs5535au = cs5535au;
	वापस 0;

sndfail: /* leave the device alive, just समाप्त the snd */
	snd_cs5535audio_मुक्त(cs5535au);
	वापस err;

pcअगरail:
	pci_disable_device(pci);
	वापस err;
पूर्ण

अटल पूर्णांक snd_cs5535audio_probe(काष्ठा pci_dev *pci,
				 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा cs5535audio *cs5535au;
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

	अगर ((err = snd_cs5535audio_create(card, pci, &cs5535au)) < 0)
		जाओ probefail_out;

	card->निजी_data = cs5535au;

	अगर ((err = snd_cs5535audio_mixer(cs5535au)) < 0)
		जाओ probefail_out;

	अगर ((err = snd_cs5535audio_pcm(cs5535au)) < 0)
		जाओ probefail_out;

	म_नकल(card->driver, DRIVER_NAME);

	म_नकल(card->लघुname, "CS5535 Audio");
	प्र_लिखो(card->दीर्घname, "%s %s at 0x%lx, irq %i",
		card->लघुname, card->driver,
		cs5535au->port, cs5535au->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		जाओ probefail_out;

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

probefail_out:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_cs5535audio_हटाओ(काष्ठा pci_dev *pci)
अणु
	olpc_quirks_cleanup();
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver cs5535audio_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_cs5535audio_ids,
	.probe = snd_cs5535audio_probe,
	.हटाओ = snd_cs5535audio_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &snd_cs5535audio_pm,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cs5535audio_driver);

MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CS5535 Audio");
