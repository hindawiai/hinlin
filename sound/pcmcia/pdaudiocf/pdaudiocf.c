<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Sound Core PDAudioCF soundcard
 *
 * Copyright (c) 2003 by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/core.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/cisreg.h>
#समावेश "pdaudiocf.h"
#समावेश <sound/initval.h>
#समावेश <linux/init.h>

/*
 */

#घोषणा CARD_NAME	"PDAudio-CF"

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Sound Core " CARD_NAME);
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable चयनes */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CARD_NAME " soundcard.");

/*
 */

अटल काष्ठा snd_card *card_list[SNDRV_CARDS];

/*
 * prototypes
 */
अटल पूर्णांक pdacf_config(काष्ठा pcmcia_device *link);
अटल व्योम snd_pdacf_detach(काष्ठा pcmcia_device *p_dev);

अटल व्योम pdacf_release(काष्ठा pcmcia_device *link)
अणु
	मुक्त_irq(link->irq, link->priv);
	pcmcia_disable_device(link);
पूर्ण

/*
 * deकाष्ठाor
 */
अटल पूर्णांक snd_pdacf_मुक्त(काष्ठा snd_pdacf *pdacf)
अणु
	काष्ठा pcmcia_device *link = pdacf->p_dev;

	pdacf_release(link);

	card_list[pdacf->index] = शून्य;
	pdacf->card = शून्य;

	kमुक्त(pdacf);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_pdacf_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_pdacf *chip = device->device_data;
	वापस snd_pdacf_मुक्त(chip);
पूर्ण

/*
 * snd_pdacf_attach - attach callback क्रम cs
 */
अटल पूर्णांक snd_pdacf_probe(काष्ठा pcmcia_device *link)
अणु
	पूर्णांक i, err;
	काष्ठा snd_pdacf *pdacf;
	काष्ठा snd_card *card;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_pdacf_dev_मुक्त,
	पूर्ण;

	snd_prपूर्णांकdd(KERN_DEBUG "pdacf_attach called\n");
	/* find an empty slot from the card list */
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (! card_list[i])
			अवरोध;
	पूर्ण
	अगर (i >= SNDRV_CARDS) अणु
		snd_prपूर्णांकk(KERN_ERR "pdacf: too many cards found\n");
		वापस -EINVAL;
	पूर्ण
	अगर (! enable[i])
		वापस -ENODEV; /* disabled explicitly */

	/* ok, create a card instance */
	err = snd_card_new(&link->dev, index[i], id[i], THIS_MODULE,
			   0, &card);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "pdacf: cannot create a card instance\n");
		वापस err;
	पूर्ण

	pdacf = snd_pdacf_create(card);
	अगर (!pdacf) अणु
		snd_card_मुक्त(card);
		वापस -ENOMEM;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, pdacf, &ops);
	अगर (err < 0) अणु
		kमुक्त(pdacf);
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pdacf->index = i;
	card_list[i] = card;

	pdacf->p_dev = link;
	link->priv = pdacf;

	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	link->resource[0]->end = 16;

	link->config_flags = CONF_ENABLE_IRQ | CONF_ENABLE_PULSE_IRQ;
	link->config_index = 1;
	link->config_regs = PRESENT_OPTION;

	वापस pdacf_config(link);
पूर्ण


/**
 * snd_pdacf_assign_resources - initialize the hardware and card instance.
 * @pdacf: context
 * @port: i/o port क्रम the card
 * @irq: irq number क्रम the card
 *
 * this function assigns the specअगरied port and irq, boot the card,
 * create pcm and control instances, and initialize the rest hardware.
 *
 * वापसs 0 अगर successful, or a negative error code.
 */
अटल पूर्णांक snd_pdacf_assign_resources(काष्ठा snd_pdacf *pdacf, पूर्णांक port, पूर्णांक irq)
अणु
	पूर्णांक err;
	काष्ठा snd_card *card = pdacf->card;

	snd_prपूर्णांकdd(KERN_DEBUG "pdacf assign resources: port = 0x%x, irq = %d\n", port, irq);
	pdacf->port = port;
	pdacf->irq = irq;
	pdacf->chip_status |= PDAUDIOCF_STAT_IS_CONFIGURED;

	err = snd_pdacf_ak4117_create(pdacf);
	अगर (err < 0)
		वापस err;	

	म_नकल(card->driver, "PDAudio-CF");
	प्र_लिखो(card->लघुname, "Core Sound %s", card->driver);
	प्र_लिखो(card->दीर्घname, "%s at 0x%x, irq %i",
		card->लघुname, port, irq);

	err = snd_pdacf_pcm_new(pdacf);
	अगर (err < 0)
		वापस err;

	अगर ((err = snd_card_रेजिस्टर(card)) < 0)
		वापस err;

	वापस 0;
पूर्ण


/*
 * snd_pdacf_detach - detach callback क्रम cs
 */
अटल व्योम snd_pdacf_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा snd_pdacf *chip = link->priv;

	snd_prपूर्णांकdd(KERN_DEBUG "pdacf_detach called\n");

	अगर (chip->chip_status & PDAUDIOCF_STAT_IS_CONFIGURED)
		snd_pdacf_घातerकरोwn(chip);
	chip->chip_status |= PDAUDIOCF_STAT_IS_STALE; /* to be sure */
	snd_card_disconnect(chip->card);
	snd_card_मुक्त_when_बंदd(chip->card);
पूर्ण

/*
 * configuration callback
 */

अटल पूर्णांक pdacf_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा snd_pdacf *pdacf = link->priv;
	पूर्णांक ret;

	snd_prपूर्णांकdd(KERN_DEBUG "pdacf_config called\n");
	link->config_index = 0x5;
	link->config_flags |= CONF_ENABLE_IRQ | CONF_ENABLE_PULSE_IRQ;

	ret = pcmcia_request_io(link);
	अगर (ret)
		जाओ failed_preirq;

	ret = request_thपढ़ोed_irq(link->irq, pdacf_पूर्णांकerrupt,
				   pdacf_thपढ़ोed_irq,
				   IRQF_SHARED, link->devname, link->priv);
	अगर (ret)
		जाओ failed_preirq;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	अगर (snd_pdacf_assign_resources(pdacf, link->resource[0]->start,
					link->irq) < 0)
		जाओ failed;

	pdacf->card->sync_irq = link->irq;
	वापस 0;

 failed:
	मुक्त_irq(link->irq, link->priv);
failed_preirq:
	pcmcia_disable_device(link);
	वापस -ENODEV;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक pdacf_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा snd_pdacf *chip = link->priv;

	snd_prपूर्णांकdd(KERN_DEBUG "SUSPEND\n");
	अगर (chip) अणु
		snd_prपूर्णांकdd(KERN_DEBUG "snd_pdacf_suspend calling\n");
		snd_pdacf_suspend(chip);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pdacf_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा snd_pdacf *chip = link->priv;

	snd_prपूर्णांकdd(KERN_DEBUG "RESUME\n");
	अगर (pcmcia_dev_present(link)) अणु
		अगर (chip) अणु
			snd_prपूर्णांकdd(KERN_DEBUG "calling snd_pdacf_resume\n");
			snd_pdacf_resume(chip);
		पूर्ण
	पूर्ण
	snd_prपूर्णांकdd(KERN_DEBUG "resume done!\n");

	वापस 0;
पूर्ण

#पूर्ण_अगर

/*
 * Module entry poपूर्णांकs
 */
अटल स्थिर काष्ठा pcmcia_device_id snd_pdacf_ids[] = अणु
	/* this is too general PCMCIA_DEVICE_MANF_CARD(0x015d, 0x4c45), */
	PCMCIA_DEVICE_PROD_ID12("Core Sound","PDAudio-CF",0x396d19d2,0x71717b49),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, snd_pdacf_ids);

अटल काष्ठा pcmcia_driver pdacf_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "snd-pdaudiocf",
	.probe		= snd_pdacf_probe,
	.हटाओ		= snd_pdacf_detach,
	.id_table	= snd_pdacf_ids,
#अगर_घोषित CONFIG_PM
	.suspend	= pdacf_suspend,
	.resume		= pdacf_resume,
#पूर्ण_अगर
पूर्ण;
module_pcmcia_driver(pdacf_cs_driver);
