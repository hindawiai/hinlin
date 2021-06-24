<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Generic driver क्रम AD1848/AD1847/CS4248 chips (0.1 Alpha)
 *  Copyright (c) by Tugrul Galatali <galatalt@stuy.edu>,
 *                   Jaroslav Kysela <perex@perex.cz>
 *  Based on card-4232.c by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/wss.h>
#समावेश <sound/initval.h>

#घोषणा CRD_NAME "Generic AD1848/AD1847/CS4248"
#घोषणा DEV_NAME "ad1848"

MODULE_DESCRIPTION(CRD_NAME);
MODULE_AUTHOR("Tugrul Galatali <galatalt@stuy.edu>, Jaroslav Kysela <perex@perex.cz>");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* PnP setup */
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,11,12,15 */
अटल पूर्णांक dma1[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3,5,6,7 */
अटल bool thinkpad[SNDRV_CARDS];			/* Thinkpad special हाल */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CRD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CRD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CRD_NAME " soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for " CRD_NAME " driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(irq, "IRQ # for " CRD_NAME " driver.");
module_param_hw_array(dma1, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma1, "DMA1 # for " CRD_NAME " driver.");
module_param_array(thinkpad, bool, शून्य, 0444);
MODULE_PARM_DESC(thinkpad, "Enable only for the onboard CS4248 of IBM Thinkpad 360/750/755 series.");

अटल पूर्णांक snd_ad1848_match(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	अगर (!enable[n])
		वापस 0;

	अगर (port[n] == SNDRV_AUTO_PORT) अणु
		dev_err(dev, "please specify port\n");
		वापस 0;
	पूर्ण
	अगर (irq[n] == SNDRV_AUTO_IRQ) अणु
		dev_err(dev, "please specify irq\n");
		वापस 0;	
	पूर्ण
	अगर (dma1[n] == SNDRV_AUTO_DMA) अणु
		dev_err(dev, "please specify dma1\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक snd_ad1848_probe(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_wss *chip;
	पूर्णांक error;

	error = snd_card_new(dev, index[n], id[n], THIS_MODULE, 0, &card);
	अगर (error < 0)
		वापस error;

	error = snd_wss_create(card, port[n], -1, irq[n], dma1[n], -1,
			thinkpad[n] ? WSS_HW_THINKPAD : WSS_HW_DETECT,
			0, &chip);
	अगर (error < 0)
		जाओ out;

	card->निजी_data = chip;

	error = snd_wss_pcm(chip, 0);
	अगर (error < 0)
		जाओ out;

	error = snd_wss_mixer(chip);
	अगर (error < 0)
		जाओ out;

	strscpy(card->driver, "AD1848", माप(card->driver));
	strscpy(card->लघुname, chip->pcm->name, माप(card->लघुname));

	अगर (!thinkpad[n])
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "%s at 0x%lx, irq %d, dma %d",
			 chip->pcm->name, chip->port, irq[n], dma1[n]);
	अन्यथा
		snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
			 "%s at 0x%lx, irq %d, dma %d [Thinkpad]",
			 chip->pcm->name, chip->port, irq[n], dma1[n]);

	error = snd_card_रेजिस्टर(card);
	अगर (error < 0)
		जाओ out;

	dev_set_drvdata(dev, card);
	वापस 0;

out:	snd_card_मुक्त(card);
	वापस error;
पूर्ण

अटल व्योम snd_ad1848_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	snd_card_मुक्त(dev_get_drvdata(dev));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_ad1848_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक n, pm_message_t state)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_wss *chip = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	chip->suspend(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1848_resume(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_wss *chip = card->निजी_data;

	chip->resume(chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा isa_driver snd_ad1848_driver = अणु
	.match		= snd_ad1848_match,
	.probe		= snd_ad1848_probe,
	.हटाओ		= snd_ad1848_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_ad1848_suspend,
	.resume		= snd_ad1848_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण
पूर्ण;

module_isa_driver(snd_ad1848_driver, SNDRV_CARDS);
