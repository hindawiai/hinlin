<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend - Handle special overlays क्रम broken devices.
 *
 * Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 * Author: Chris Bookholt <hap10@epoch.ncsc.mil>
 */

#घोषणा dev_fmt(fmt) DRV_NAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश "pciback.h"
#समावेश "conf_space.h"
#समावेश "conf_space_quirks.h"

LIST_HEAD(xen_pcibk_quirks);
अटल अंतरभूत स्थिर काष्ठा pci_device_id *
match_one_device(स्थिर काष्ठा pci_device_id *id, स्थिर काष्ठा pci_dev *dev)
अणु
	अगर ((id->venकरोr == PCI_ANY_ID || id->venकरोr == dev->venकरोr) &&
	    (id->device == PCI_ANY_ID || id->device == dev->device) &&
	    (id->subvenकरोr == PCI_ANY_ID ||
				id->subvenकरोr == dev->subप्रणाली_venकरोr) &&
	    (id->subdevice == PCI_ANY_ID ||
				id->subdevice == dev->subप्रणाली_device) &&
	    !((id->class ^ dev->class) & id->class_mask))
		वापस id;
	वापस शून्य;
पूर्ण

अटल काष्ठा xen_pcibk_config_quirk *xen_pcibk_find_quirk(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_pcibk_config_quirk *पंचांगp_quirk;

	list_क्रम_each_entry(पंचांगp_quirk, &xen_pcibk_quirks, quirks_list)
		अगर (match_one_device(&पंचांगp_quirk->devid, dev) != शून्य)
			जाओ out;
	पंचांगp_quirk = शून्य;
	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev,
		   "quirk didn't match any device known\n");
out:
	वापस पंचांगp_quirk;
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_quirk(काष्ठा xen_pcibk_config_quirk *quirk)
अणु
	list_add_tail(&quirk->quirks_list, &xen_pcibk_quirks);
पूर्ण

पूर्णांक xen_pcibk_field_is_dup(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret = 0;
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	काष्ठा config_field_entry *cfg_entry;

	list_क्रम_each_entry(cfg_entry, &dev_data->config_fields, list) अणु
		अगर (OFFSET(cfg_entry) == reg) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक xen_pcibk_config_quirks_add_field(काष्ठा pci_dev *dev, काष्ठा config_field
				    *field)
अणु
	पूर्णांक err = 0;

	चयन (field->size) अणु
	हाल 1:
		field->u.b.पढ़ो = xen_pcibk_पढ़ो_config_byte;
		field->u.b.ग_लिखो = xen_pcibk_ग_लिखो_config_byte;
		अवरोध;
	हाल 2:
		field->u.w.पढ़ो = xen_pcibk_पढ़ो_config_word;
		field->u.w.ग_लिखो = xen_pcibk_ग_लिखो_config_word;
		अवरोध;
	हाल 4:
		field->u.dw.पढ़ो = xen_pcibk_पढ़ो_config_dword;
		field->u.dw.ग_लिखो = xen_pcibk_ग_लिखो_config_dword;
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out;
	पूर्ण

	xen_pcibk_config_add_field(dev, field);

out:
	वापस err;
पूर्ण

पूर्णांक xen_pcibk_config_quirks_init(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_pcibk_config_quirk *quirk;
	पूर्णांक ret = 0;

	quirk = kzalloc(माप(*quirk), GFP_KERNEL);
	अगर (!quirk) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	quirk->devid.venकरोr = dev->venकरोr;
	quirk->devid.device = dev->device;
	quirk->devid.subvenकरोr = dev->subप्रणाली_venकरोr;
	quirk->devid.subdevice = dev->subप्रणाली_device;
	quirk->devid.class = 0;
	quirk->devid.class_mask = 0;
	quirk->devid.driver_data = 0UL;

	quirk->pdev = dev;

	रेजिस्टर_quirk(quirk);
out:
	वापस ret;
पूर्ण

व्योम xen_pcibk_config_field_मुक्त(काष्ठा config_field *field)
अणु
	kमुक्त(field);
पूर्ण

पूर्णांक xen_pcibk_config_quirk_release(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_pcibk_config_quirk *quirk;
	पूर्णांक ret = 0;

	quirk = xen_pcibk_find_quirk(dev);
	अगर (!quirk) अणु
		ret = -ENXIO;
		जाओ out;
	पूर्ण

	list_del(&quirk->quirks_list);
	kमुक्त(quirk);

out:
	वापस ret;
पूर्ण
