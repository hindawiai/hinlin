<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VXpocket V2/440 soundcards
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>

 */


#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश "vxpocket.h"
#समावेश <pcmcia/ciscode.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("Digigram VXPocket");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable चयनes */
अटल पूर्णांक ibl[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for VXPocket soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for VXPocket soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable VXPocket soundcard.");
module_param_array(ibl, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ibl, "Capture IBL size for VXPocket soundcard.");
 

/*
 */

अटल अचिन्हित पूर्णांक card_alloc;


/*
 */
अटल व्योम vxpocket_release(काष्ठा pcmcia_device *link)
अणु
	मुक्त_irq(link->irq, link->priv);
	pcmcia_disable_device(link);
पूर्ण

/*
 * deकाष्ठाor, called from snd_card_मुक्त_when_बंदd()
 */
अटल पूर्णांक snd_vxpocket_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा vx_core *chip = device->device_data;

	snd_vx_मुक्त_firmware(chip);
	kमुक्त(chip);
	वापस 0;
पूर्ण


/*
 * Hardware inक्रमmation
 */

/* VX-pocket V2
 *
 * 1 DSP, 1 sync UER
 * 1 programmable घड़ी (NIY)
 * 1 stereo analog input (line/micro)
 * 1 stereo analog output
 * Only output levels can be modअगरied
 */

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_old_vol, -11350, 50, 0);

अटल स्थिर काष्ठा snd_vx_hardware vxpocket_hw = अणु
	.name = "VXPocket",
	.type = VX_TYPE_VXPOCKET,

	/* hardware specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_level_max = VX_ANALOG_OUT_LEVEL_MAX,
	.output_level_db_scale = db_scale_old_vol,
पूर्ण;	

/* VX-pocket 440
 *
 * 1 DSP, 1 sync UER, 1 sync World Clock (NIY)
 * SMPTE (NIY)
 * 2 stereo analog input (line/micro)
 * 2 stereo analog output
 * Only output levels can be modअगरied
 * UER, but only क्रम the first two inमाला_दो and outमाला_दो.
 */

अटल स्थिर काष्ठा snd_vx_hardware vxp440_hw = अणु
	.name = "VXPocket440",
	.type = VX_TYPE_VXP440,

	/* hardware specs */
	.num_codecs = 2,
	.num_ins = 2,
	.num_outs = 2,
	.output_level_max = VX_ANALOG_OUT_LEVEL_MAX,
	.output_level_db_scale = db_scale_old_vol,
पूर्ण;	


/*
 * create vxpocket instance
 */
अटल पूर्णांक snd_vxpocket_new(काष्ठा snd_card *card, पूर्णांक ibl,
			    काष्ठा pcmcia_device *link,
			    काष्ठा snd_vxpocket **chip_ret)
अणु
	काष्ठा vx_core *chip;
	काष्ठा snd_vxpocket *vxp;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_vxpocket_dev_मुक्त,
	पूर्ण;
	पूर्णांक err;

	chip = snd_vx_create(card, &vxpocket_hw, &snd_vxpocket_ops,
			     माप(काष्ठा snd_vxpocket) - माप(काष्ठा vx_core));
	अगर (!chip)
		वापस -ENOMEM;

	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (err < 0) अणु
		kमुक्त(chip);
		वापस err;
	पूर्ण
	chip->ibl.size = ibl;

	vxp = to_vxpocket(chip);

	vxp->p_dev = link;
	link->priv = chip;

	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;
	link->resource[0]->end = 16;

	link->config_flags |= CONF_ENABLE_IRQ;
	link->config_index = 1;
	link->config_regs = PRESENT_OPTION;

	*chip_ret = vxp;
	वापस 0;
पूर्ण


/**
 * snd_vxpocket_assign_resources - initialize the hardware and card instance.
 * @chip: VX core instance
 * @port: i/o port क्रम the card
 * @irq: irq number क्रम the card
 *
 * this function assigns the specअगरied port and irq, boot the card,
 * create pcm and control instances, and initialize the rest hardware.
 *
 * वापसs 0 अगर successful, or a negative error code.
 */
अटल पूर्णांक snd_vxpocket_assign_resources(काष्ठा vx_core *chip, पूर्णांक port, पूर्णांक irq)
अणु
	पूर्णांक err;
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_vxpocket *vxp = to_vxpocket(chip);

	snd_prपूर्णांकdd(KERN_DEBUG "vxpocket assign resources: port = 0x%x, irq = %d\n", port, irq);
	vxp->port = port;

	प्र_लिखो(card->लघुname, "Digigram %s", card->driver);
	प्र_लिखो(card->दीर्घname, "%s at 0x%x, irq %i",
		card->लघुname, port, irq);

	chip->irq = irq;
	card->sync_irq = chip->irq;

	अगर ((err = snd_vx_setup_firmware(chip)) < 0)
		वापस err;

	वापस 0;
पूर्ण


/*
 * configuration callback
 */

अटल पूर्णांक vxpocket_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा vx_core *chip = link->priv;
	पूर्णांक ret;

	snd_prपूर्णांकdd(KERN_DEBUG "vxpocket_config called\n");

	/* redefine hardware record according to the VERSION1 string */
	अगर (!म_भेद(link->prod_id[1], "VX-POCKET")) अणु
		snd_prपूर्णांकdd("VX-pocket is detected\n");
	पूर्ण अन्यथा अणु
		snd_prपूर्णांकdd("VX-pocket 440 is detected\n");
		/* overग_लिखो the hardware inक्रमmation */
		chip->hw = &vxp440_hw;
		chip->type = vxp440_hw.type;
		म_नकल(chip->card->driver, vxp440_hw.name);
	पूर्ण

	ret = pcmcia_request_io(link);
	अगर (ret)
		जाओ failed_preirq;

	ret = request_thपढ़ोed_irq(link->irq, snd_vx_irq_handler,
				   snd_vx_thपढ़ोed_irq_handler,
				   IRQF_SHARED, link->devname, link->priv);
	अगर (ret)
		जाओ failed_preirq;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	chip->dev = &link->dev;

	अगर (snd_vxpocket_assign_resources(chip, link->resource[0]->start,
						link->irq) < 0)
		जाओ failed;

	वापस 0;

 failed:
	मुक्त_irq(link->irq, link->priv);
failed_preirq:
	pcmcia_disable_device(link);
	वापस -ENODEV;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक vxp_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा vx_core *chip = link->priv;

	snd_prपूर्णांकdd(KERN_DEBUG "SUSPEND\n");
	अगर (chip) अणु
		snd_prपूर्णांकdd(KERN_DEBUG "snd_vx_suspend calling\n");
		snd_vx_suspend(chip);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vxp_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा vx_core *chip = link->priv;

	snd_prपूर्णांकdd(KERN_DEBUG "RESUME\n");
	अगर (pcmcia_dev_present(link)) अणु
		//काष्ठा snd_vxpocket *vxp = (काष्ठा snd_vxpocket *)chip;
		अगर (chip) अणु
			snd_prपूर्णांकdd(KERN_DEBUG "calling snd_vx_resume\n");
			snd_vx_resume(chip);
		पूर्ण
	पूर्ण
	snd_prपूर्णांकdd(KERN_DEBUG "resume done!\n");

	वापस 0;
पूर्ण

#पूर्ण_अगर


/*
 */
अटल पूर्णांक vxpocket_probe(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_vxpocket *vxp;
	पूर्णांक i, err;

	/* find an empty slot from the card list */
	क्रम (i = 0; i < SNDRV_CARDS; i++) अणु
		अगर (!(card_alloc & (1 << i)))
			अवरोध;
	पूर्ण
	अगर (i >= SNDRV_CARDS) अणु
		snd_prपूर्णांकk(KERN_ERR "vxpocket: too many cards found\n");
		वापस -EINVAL;
	पूर्ण
	अगर (! enable[i])
		वापस -ENODEV; /* disabled explicitly */

	/* ok, create a card instance */
	err = snd_card_new(&p_dev->dev, index[i], id[i], THIS_MODULE,
			   0, &card);
	अगर (err < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "vxpocket: cannot create a card instance\n");
		वापस err;
	पूर्ण

	err = snd_vxpocket_new(card, ibl[i], p_dev, &vxp);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = vxp;

	vxp->index = i;
	card_alloc |= 1 << i;

	vxp->p_dev = p_dev;

	वापस vxpocket_config(p_dev);
पूर्ण

अटल व्योम vxpocket_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा snd_vxpocket *vxp;
	काष्ठा vx_core *chip;

	अगर (! link)
		वापस;

	vxp = link->priv;
	chip = (काष्ठा vx_core *)vxp;
	card_alloc &= ~(1 << vxp->index);

	chip->chip_status |= VX_STAT_IS_STALE; /* to be sure */
	snd_card_disconnect(chip->card);
	vxpocket_release(link);
	snd_card_मुक्त_when_बंदd(chip->card);
पूर्ण

/*
 * Module entry poपूर्णांकs
 */

अटल स्थिर काष्ठा pcmcia_device_id vxp_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x01f1, 0x0100),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, vxp_ids);

अटल काष्ठा pcmcia_driver vxp_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "snd-vxpocket",
	.probe		= vxpocket_probe,
	.हटाओ		= vxpocket_detach,
	.id_table	= vxp_ids,
#अगर_घोषित CONFIG_PM
	.suspend	= vxp_suspend,
	.resume		= vxp_resume,
#पूर्ण_अगर
पूर्ण;
module_pcmcia_driver(vxp_cs_driver);
