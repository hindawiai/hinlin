<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xfi linux driver.
 *
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश "ctatc.h"
#समावेश "cthardware.h"

MODULE_AUTHOR("Creative Technology Ltd");
MODULE_DESCRIPTION("X-Fi driver version 1.03");
MODULE_LICENSE("GPL v2");

अटल अचिन्हित पूर्णांक reference_rate = 48000;
अटल अचिन्हित पूर्णांक multiple = 2;
MODULE_PARM_DESC(reference_rate, "Reference rate (default=48000)");
module_param(reference_rate, uपूर्णांक, 0444);
MODULE_PARM_DESC(multiple, "Rate multiplier (default=2)");
module_param(multiple, uपूर्णांक, 0444);

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;
अटल अचिन्हित पूर्णांक subप्रणाली[SNDRV_CARDS];

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Creative X-Fi driver");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Creative X-Fi driver");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Creative X-Fi driver");
module_param_array(subप्रणाली, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(subप्रणाली, "Override subsystem ID for Creative X-Fi driver");

अटल स्थिर काष्ठा pci_device_id ct_pci_dev_ids[] = अणु
	/* only X-Fi is supported, so... */
	अणु PCI_DEVICE(PCI_VENDOR_ID_CREATIVE, PCI_DEVICE_ID_CREATIVE_20K1),
	  .driver_data = ATC20K1,
	पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_CREATIVE, PCI_DEVICE_ID_CREATIVE_20K2),
	  .driver_data = ATC20K2,
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ct_pci_dev_ids);

अटल पूर्णांक
ct_card_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा ct_atc *atc;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण
	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err)
		वापस err;
	अगर ((reference_rate != 48000) && (reference_rate != 44100)) अणु
		dev_err(card->dev,
			"Invalid reference_rate value %u!!!\n",
			reference_rate);
		dev_err(card->dev,
			"The valid values for reference_rate are 48000 and 44100, Value 48000 is assumed.\n");
		reference_rate = 48000;
	पूर्ण
	अगर ((multiple != 1) && (multiple != 2) && (multiple != 4)) अणु
		dev_err(card->dev, "Invalid multiple value %u!!!\n",
			multiple);
		dev_err(card->dev,
			"The valid values for multiple are 1, 2 and 4, Value 2 is assumed.\n");
		multiple = 2;
	पूर्ण
	err = ct_atc_create(card, pci, reference_rate, multiple,
			    pci_id->driver_data, subप्रणाली[dev], &atc);
	अगर (err < 0)
		जाओ error;

	card->निजी_data = atc;

	/* Create alsa devices supported by this card */
	err = ct_atc_create_alsa_devs(atc);
	अगर (err < 0)
		जाओ error;

	म_नकल(card->driver, "SB-XFi");
	म_नकल(card->लघुname, "Creative X-Fi");
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname), "%s %s %s",
		 card->लघुname, atc->chip_name, atc->model_name);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;

	pci_set_drvdata(pci, card);
	dev++;

	वापस 0;

error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम ct_card_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ct_card_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा ct_atc *atc = card->निजी_data;

	वापस atc->suspend(atc);
पूर्ण

अटल पूर्णांक ct_card_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा ct_atc *atc = card->निजी_data;

	वापस atc->resume(atc);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ct_card_pm, ct_card_suspend, ct_card_resume);
#घोषणा CT_CARD_PM_OPS	&ct_card_pm
#अन्यथा
#घोषणा CT_CARD_PM_OPS	शून्य
#पूर्ण_अगर

अटल काष्ठा pci_driver ct_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = ct_pci_dev_ids,
	.probe = ct_card_probe,
	.हटाओ = ct_card_हटाओ,
	.driver = अणु
		.pm = CT_CARD_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(ct_driver);
