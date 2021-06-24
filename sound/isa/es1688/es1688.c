<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम generic ESS AudioDrive ESx688 soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/isa.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/dma.h>
#समावेश <sound/core.h>
#समावेश <sound/es1688.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#घोषणा SNDRV_LEGACY_FIND_FREE_IRQ
#घोषणा SNDRV_LEGACY_FIND_FREE_DMA
#समावेश <sound/initval.h>

#घोषणा CRD_NAME "Generic ESS ES1688/ES688 AudioDrive"
#घोषणा DEV_NAME "es1688"

MODULE_DESCRIPTION(CRD_NAME);
MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("snd_es968");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
#अगर_घोषित CONFIG_PNP
अटल bool isapnp[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_ISAPNP;
#पूर्ण_अगर
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;	/* Enable this card */
अटल दीर्घ port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* 0x220,0x240,0x260 */
अटल दीर्घ fm_port[SNDRV_CARDS] = SNDRV_DEFAULT_PORT;	/* Usually 0x388 */
अटल दीर्घ mpu_port[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = -1पूर्ण;
अटल पूर्णांक irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,10 */
अटल पूर्णांक mpu_irq[SNDRV_CARDS] = SNDRV_DEFAULT_IRQ;	/* 5,7,9,10 */
अटल पूर्णांक dma8[SNDRV_CARDS] = SNDRV_DEFAULT_DMA;	/* 0,1,3 */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CRD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CRD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
#अगर_घोषित CONFIG_PNP
module_param_array(isapnp, bool, शून्य, 0444);
MODULE_PARM_DESC(isapnp, "PnP detection for specified soundcard.");
#पूर्ण_अगर
MODULE_PARM_DESC(enable, "Enable " CRD_NAME " soundcard.");
module_param_hw_array(port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(port, "Port # for " CRD_NAME " driver.");
module_param_hw_array(mpu_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port # for " CRD_NAME " driver.");
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0444);
module_param_hw_array(fm_port, दीर्घ, ioport, शून्य, 0444);
MODULE_PARM_DESC(fm_port, "FM port # for ES1688 driver.");
MODULE_PARM_DESC(irq, "IRQ # for " CRD_NAME " driver.");
module_param_hw_array(mpu_irq, पूर्णांक, irq, शून्य, 0444);
MODULE_PARM_DESC(mpu_irq, "MPU-401 IRQ # for " CRD_NAME " driver.");
module_param_hw_array(dma8, पूर्णांक, dma, शून्य, 0444);
MODULE_PARM_DESC(dma8, "8-bit DMA # for " CRD_NAME " driver.");

#अगर_घोषित CONFIG_PNP
#घोषणा is_isapnp_selected(dev)		isapnp[dev]
#अन्यथा
#घोषणा is_isapnp_selected(dev)		0
#पूर्ण_अगर

अटल पूर्णांक snd_es1688_match(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	वापस enable[n] && !is_isapnp_selected(n);
पूर्ण

अटल पूर्णांक snd_es1688_legacy_create(काष्ठा snd_card *card,
				    काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_es1688 *chip = card->निजी_data;
	अटल स्थिर दीर्घ possible_ports[] = अणु0x220, 0x240, 0x260पूर्ण;
	अटल स्थिर पूर्णांक possible_irqs[] = अणु5, 9, 10, 7, -1पूर्ण;
	अटल स्थिर पूर्णांक possible_dmas[] = अणु1, 3, 0, -1पूर्ण;

	पूर्णांक i, error;

	अगर (irq[n] == SNDRV_AUTO_IRQ) अणु
		irq[n] = snd_legacy_find_मुक्त_irq(possible_irqs);
		अगर (irq[n] < 0) अणु
			dev_err(dev, "unable to find a free IRQ\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	अगर (dma8[n] == SNDRV_AUTO_DMA) अणु
		dma8[n] = snd_legacy_find_मुक्त_dma(possible_dmas);
		अगर (dma8[n] < 0) अणु
			dev_err(dev, "unable to find a free DMA\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (port[n] != SNDRV_AUTO_PORT)
		वापस snd_es1688_create(card, chip, port[n], mpu_port[n],
				irq[n], mpu_irq[n], dma8[n], ES1688_HW_AUTO);

	i = 0;
	करो अणु
		port[n] = possible_ports[i];
		error = snd_es1688_create(card, chip, port[n], mpu_port[n],
				irq[n], mpu_irq[n], dma8[n], ES1688_HW_AUTO);
	पूर्ण जबतक (error < 0 && ++i < ARRAY_SIZE(possible_ports));

	वापस error;
पूर्ण

अटल पूर्णांक snd_es1688_probe(काष्ठा snd_card *card, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_es1688 *chip = card->निजी_data;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक error;

	error = snd_es1688_pcm(card, chip, 0);
	अगर (error < 0)
		वापस error;

	error = snd_es1688_mixer(card, chip);
	अगर (error < 0)
		वापस error;

	strscpy(card->driver, "ES1688", माप(card->driver));
	strscpy(card->लघुname, chip->pcm->name, माप(card->लघुname));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		"%s at 0x%lx, irq %i, dma %i", chip->pcm->name, chip->port,
		 chip->irq, chip->dma8);

	अगर (fm_port[n] == SNDRV_AUTO_PORT)
		fm_port[n] = port[n];	/* share the same port */

	अगर (fm_port[n] > 0) अणु
		अगर (snd_opl3_create(card, fm_port[n], fm_port[n] + 2,
				OPL3_HW_OPL3, 0, &opl3) < 0)
			dev_warn(card->dev,
				 "opl3 not detected at 0x%lx\n", fm_port[n]);
		अन्यथा अणु
			error =	snd_opl3_hwdep_new(opl3, 0, 1, शून्य);
			अगर (error < 0)
				वापस error;
		पूर्ण
	पूर्ण

	अगर (mpu_irq[n] >= 0 && mpu_irq[n] != SNDRV_AUTO_IRQ &&
			chip->mpu_port > 0) अणु
		error = snd_mpu401_uart_new(card, 0, MPU401_HW_ES1688,
				chip->mpu_port, 0,
				mpu_irq[n], शून्य);
		अगर (error < 0)
			वापस error;
	पूर्ण

	वापस snd_card_रेजिस्टर(card);
पूर्ण

अटल पूर्णांक snd_es1688_isa_probe(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	काष्ठा snd_card *card;
	पूर्णांक error;

	error = snd_card_new(dev, index[n], id[n], THIS_MODULE,
			     माप(काष्ठा snd_es1688), &card);
	अगर (error < 0)
		वापस error;

	error = snd_es1688_legacy_create(card, dev, n);
	अगर (error < 0)
		जाओ out;

	error = snd_es1688_probe(card, n);
	अगर (error < 0)
		जाओ out;

	dev_set_drvdata(dev, card);

	वापस 0;
out:
	snd_card_मुक्त(card);
	वापस error;
पूर्ण

अटल व्योम snd_es1688_isa_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक n)
अणु
	snd_card_मुक्त(dev_get_drvdata(dev));
पूर्ण

अटल काष्ठा isa_driver snd_es1688_driver = अणु
	.match		= snd_es1688_match,
	.probe		= snd_es1688_isa_probe,
	.हटाओ		= snd_es1688_isa_हटाओ,
#अगर 0	/* FIXME */
	.suspend	= snd_es1688_suspend,
	.resume		= snd_es1688_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= DEV_NAME
	पूर्ण
पूर्ण;

अटल पूर्णांक snd_es968_pnp_is_probed;

#अगर_घोषित CONFIG_PNP
अटल पूर्णांक snd_card_es968_pnp(काष्ठा snd_card *card, अचिन्हित पूर्णांक n,
			      काष्ठा pnp_card_link *pcard,
			      स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	काष्ठा snd_es1688 *chip = card->निजी_data;
	काष्ठा pnp_dev *pdev;
	पूर्णांक error;

	pdev = pnp_request_card_device(pcard, pid->devs[0].id, शून्य);
	अगर (pdev == शून्य)
		वापस -ENODEV;

	error = pnp_activate_dev(pdev);
	अगर (error < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "ES968 pnp configure failure\n");
		वापस error;
	पूर्ण
	port[n] = pnp_port_start(pdev, 0);
	dma8[n] = pnp_dma(pdev, 0);
	irq[n] = pnp_irq(pdev, 0);

	वापस snd_es1688_create(card, chip, port[n], mpu_port[n], irq[n],
				 mpu_irq[n], dma8[n], ES1688_HW_AUTO);
पूर्ण

अटल पूर्णांक snd_es968_pnp_detect(काष्ठा pnp_card_link *pcard,
				स्थिर काष्ठा pnp_card_device_id *pid)
अणु
	काष्ठा snd_card *card;
	अटल अचिन्हित पूर्णांक dev;
	पूर्णांक error;

	अगर (snd_es968_pnp_is_probed)
		वापस -EBUSY;
	क्रम ( ; dev < SNDRV_CARDS; dev++) अणु
		अगर (enable[dev] && isapnp[dev])
			अवरोध;
	पूर्ण
	अगर (dev == SNDRV_CARDS)
		वापस -ENODEV;

	error = snd_card_new(&pcard->card->dev,
			     index[dev], id[dev], THIS_MODULE,
			     माप(काष्ठा snd_es1688), &card);
	अगर (error < 0)
		वापस error;

	error = snd_card_es968_pnp(card, dev, pcard, pid);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	error = snd_es1688_probe(card, dev);
	अगर (error < 0) अणु
		snd_card_मुक्त(card);
		वापस error;
	पूर्ण
	pnp_set_card_drvdata(pcard, card);
	snd_es968_pnp_is_probed = 1;
	वापस 0;
पूर्ण

अटल व्योम snd_es968_pnp_हटाओ(काष्ठा pnp_card_link *pcard)
अणु
	snd_card_मुक्त(pnp_get_card_drvdata(pcard));
	pnp_set_card_drvdata(pcard, शून्य);
	snd_es968_pnp_is_probed = 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक snd_es968_pnp_suspend(काष्ठा pnp_card_link *pcard,
				 pm_message_t state)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es968_pnp_resume(काष्ठा pnp_card_link *pcard)
अणु
	काष्ठा snd_card *card = pnp_get_card_drvdata(pcard);
	काष्ठा snd_es1688 *chip = card->निजी_data;

	snd_es1688_reset(chip);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pnp_card_device_id snd_es968_pnpids[] = अणु
	अणु .id = "ESS0968", .devs = अणु अणु "@@@0968" पूर्ण, पूर्ण पूर्ण,
	अणु .id = "ESS0968", .devs = अणु अणु "ESS0968" पूर्ण, पूर्ण पूर्ण,
	अणु .id = "", पूर्ण /* end */
पूर्ण;

MODULE_DEVICE_TABLE(pnp_card, snd_es968_pnpids);

अटल काष्ठा pnp_card_driver es968_pnpc_driver = अणु
	.flags		= PNP_DRIVER_RES_DISABLE,
	.name		= DEV_NAME " PnP",
	.id_table	= snd_es968_pnpids,
	.probe		= snd_es968_pnp_detect,
	.हटाओ		= snd_es968_pnp_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= snd_es968_pnp_suspend,
	.resume		= snd_es968_pnp_resume,
#पूर्ण_अगर
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init alsa_card_es1688_init(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	pnp_रेजिस्टर_card_driver(&es968_pnpc_driver);
	अगर (snd_es968_pnp_is_probed)
		वापस 0;
	pnp_unरेजिस्टर_card_driver(&es968_pnpc_driver);
#पूर्ण_अगर
	वापस isa_रेजिस्टर_driver(&snd_es1688_driver, SNDRV_CARDS);
पूर्ण

अटल व्योम __निकास alsa_card_es1688_निकास(व्योम)
अणु
	अगर (!snd_es968_pnp_is_probed) अणु
		isa_unरेजिस्टर_driver(&snd_es1688_driver);
		वापस;
	पूर्ण
#अगर_घोषित CONFIG_PNP
	pnp_unरेजिस्टर_card_driver(&es968_pnpc_driver);
#पूर्ण_अगर
पूर्ण

module_init(alsa_card_es1688_init);
module_निकास(alsa_card_es1688_निकास);
