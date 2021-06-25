<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * C-Media CMI8788 driver क्रम Asus Xonar cards
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश "xonar.h"

MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("Asus Virtuoso driver");
MODULE_LICENSE("GPL v2");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "card index");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "enable card");

अटल स्थिर काष्ठा pci_device_id xonar_ids[] = अणु
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8269) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8275) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x82b7) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8314) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8327) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x834f) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x835c) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x835d) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x835e) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x838e) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8428) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x8522) पूर्ण,
	अणु OXYGEN_PCI_SUBID(0x1043, 0x85f4) पूर्ण,
	अणु OXYGEN_PCI_SUBID_BROKEN_EEPROM पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, xonar_ids);

अटल पूर्णांक get_xonar_model(काष्ठा oxygen *chip,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	अगर (get_xonar_pcm179x_model(chip, id) >= 0)
		वापस 0;
	अगर (get_xonar_cs43xx_model(chip, id) >= 0)
		वापस 0;
	अगर (get_xonar_wm87x6_model(chip, id) >= 0)
		वापस 0;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक xonar_probe(काष्ठा pci_dev *pci,
		       स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		++dev;
		वापस -ENOENT;
	पूर्ण
	err = oxygen_pci_probe(pci, index[dev], id[dev], THIS_MODULE,
			       xonar_ids, get_xonar_model);
	अगर (err >= 0)
		++dev;
	वापस err;
पूर्ण

अटल काष्ठा pci_driver xonar_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = xonar_ids,
	.probe = xonar_probe,
	.हटाओ = oxygen_pci_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &oxygen_pci_pm,
	पूर्ण,
#पूर्ण_अगर
	.shutकरोwn = oxygen_pci_shutकरोwn,
पूर्ण;

module_pci_driver(xonar_driver);
