<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX222 V2/Mic PCI soundcards
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश "vx222.h"

#घोषणा CARD_NAME "VX222"

MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("Digigram VX222 V2/Mic");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल bool mic[SNDRV_CARDS]; /* microphone */
अटल पूर्णांक ibl[SNDRV_CARDS]; /* microphone */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Digigram " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Digigram " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Digigram " CARD_NAME " soundcard.");
module_param_array(mic, bool, शून्य, 0444);
MODULE_PARM_DESC(mic, "Enable Microphone.");
module_param_array(ibl, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ibl, "Capture IBL size.");

/*
 */

क्रमागत अणु
	VX_PCI_VX222_OLD,
	VX_PCI_VX222_NEW
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_vx222_ids[] = अणु
	अणु 0x10b5, 0x9050, 0x1369, PCI_ANY_ID, 0, 0, VX_PCI_VX222_OLD, पूर्ण,   /* PLX */
	अणु 0x10b5, 0x9030, 0x1369, PCI_ANY_ID, 0, 0, VX_PCI_VX222_NEW, पूर्ण,   /* PLX */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_vx222_ids);


/*
 */

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_old_vol, -11350, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_akm, -7350, 50, 0);

अटल स्थिर काष्ठा snd_vx_hardware vx222_old_hw = अणु

	.name = "VX222/Old",
	.type = VX_TYPE_BOARD,
	/* hw specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_level_max = VX_ANALOG_OUT_LEVEL_MAX,
	.output_level_db_scale = db_scale_old_vol,
पूर्ण;

अटल स्थिर काष्ठा snd_vx_hardware vx222_v2_hw = अणु

	.name = "VX222/v2",
	.type = VX_TYPE_V2,
	/* hw specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_level_max = VX2_AKM_LEVEL_MAX,
	.output_level_db_scale = db_scale_akm,
पूर्ण;

अटल स्थिर काष्ठा snd_vx_hardware vx222_mic_hw = अणु

	.name = "VX222/Mic",
	.type = VX_TYPE_MIC,
	/* hw specs */
	.num_codecs = 1,
	.num_ins = 1,
	.num_outs = 1,
	.output_level_max = VX2_AKM_LEVEL_MAX,
	.output_level_db_scale = db_scale_akm,
पूर्ण;


/*
 */
अटल पूर्णांक snd_vx222_मुक्त(काष्ठा vx_core *chip)
अणु
	काष्ठा snd_vx222 *vx = to_vx222(chip);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम*)chip);
	अगर (vx->port[0])
		pci_release_regions(vx->pci);
	pci_disable_device(vx->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vx222_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा vx_core *chip = device->device_data;
	वापस snd_vx222_मुक्त(chip);
पूर्ण


अटल पूर्णांक snd_vx222_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
			    स्थिर काष्ठा snd_vx_hardware *hw,
			    काष्ठा snd_vx222 **rchip)
अणु
	काष्ठा vx_core *chip;
	काष्ठा snd_vx222 *vx;
	पूर्णांक i, err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_vx222_dev_मुक्त,
	पूर्ण;
	स्थिर काष्ठा snd_vx_ops *vx_ops;

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	pci_set_master(pci);

	vx_ops = hw->type == VX_TYPE_BOARD ? &vx222_old_ops : &vx222_ops;
	chip = snd_vx_create(card, hw, vx_ops,
			     माप(काष्ठा snd_vx222) - माप(काष्ठा vx_core));
	अगर (! chip) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	vx = to_vx222(chip);
	vx->pci = pci;

	अगर ((err = pci_request_regions(pci, CARD_NAME)) < 0) अणु
		snd_vx222_मुक्त(chip);
		वापस err;
	पूर्ण
	क्रम (i = 0; i < 2; i++)
		vx->port[i] = pci_resource_start(pci, i + 1);

	अगर (request_thपढ़ोed_irq(pci->irq, snd_vx_irq_handler,
				 snd_vx_thपढ़ोed_irq_handler, IRQF_SHARED,
				 KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_vx222_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_vx222_मुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = vx;
	वापस 0;
पूर्ण


अटल पूर्णांक snd_vx222_probe(काष्ठा pci_dev *pci,
			   स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	स्थिर काष्ठा snd_vx_hardware *hw;
	काष्ठा snd_vx222 *vx;
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

	चयन ((पूर्णांक)pci_id->driver_data) अणु
	हाल VX_PCI_VX222_OLD:
		hw = &vx222_old_hw;
		अवरोध;
	हाल VX_PCI_VX222_NEW:
	शेष:
		अगर (mic[dev])
			hw = &vx222_mic_hw;
		अन्यथा
			hw = &vx222_v2_hw;
		अवरोध;
	पूर्ण
	अगर ((err = snd_vx222_create(card, pci, hw, &vx)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = vx;
	vx->core.ibl.size = ibl[dev];

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx & 0x%lx, irq %i",
		card->लघुname, vx->port[0], vx->port[1], vx->core.irq);
	dev_dbg(card->dev, "%s at 0x%lx & 0x%lx, irq %i\n",
		    card->लघुname, vx->port[0], vx->port[1], vx->core.irq);

#अगर_घोषित SND_VX_FW_LOADER
	vx->core.dev = &pci->dev;
#पूर्ण_अगर

	अगर ((err = snd_vx_setup_firmware(&vx->core)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_vx222_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_vx222_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_vx222 *vx = card->निजी_data;

	वापस snd_vx_suspend(&vx->core);
पूर्ण

अटल पूर्णांक snd_vx222_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_vx222 *vx = card->निजी_data;

	वापस snd_vx_resume(&vx->core);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_vx222_pm, snd_vx222_suspend, snd_vx222_resume);
#घोषणा SND_VX222_PM_OPS	&snd_vx222_pm
#अन्यथा
#घोषणा SND_VX222_PM_OPS	शून्य
#पूर्ण_अगर

अटल काष्ठा pci_driver vx222_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_vx222_ids,
	.probe = snd_vx222_probe,
	.हटाओ = snd_vx222_हटाओ,
	.driver = अणु
		.pm = SND_VX222_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(vx222_driver);
