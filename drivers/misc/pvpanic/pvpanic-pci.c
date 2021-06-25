<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Pvpanic PCI Device Support
 *
 *  Copyright (C) 2021 Oracle.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश <uapi/misc/pvpanic.h>

#समावेश "pvpanic.h"

#घोषणा PCI_VENDOR_ID_REDHAT             0x1b36
#घोषणा PCI_DEVICE_ID_REDHAT_PVPANIC     0x0011

MODULE_AUTHOR("Mihai Carabas <mihai.carabas@oracle.com>");
MODULE_DESCRIPTION("pvpanic device driver ");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा pci_device_id pvpanic_pci_id_tbl[]  = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_REDHAT, PCI_DEVICE_ID_REDHAT_PVPANIC)पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल sमाप_प्रकार capability_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%x\n", pi->capability);
पूर्ण
अटल DEVICE_ATTR_RO(capability);

अटल sमाप_प्रकार events_show(काष्ठा device *dev,  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%x\n", pi->events);
पूर्ण

अटल sमाप_प्रकार events_store(काष्ठा device *dev,  काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 16, &पंचांगp);
	अगर (err)
		वापस err;

	अगर ((पंचांगp & pi->capability) != पंचांगp)
		वापस -EINVAL;

	pi->events = पंचांगp;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(events);

अटल काष्ठा attribute *pvpanic_pci_dev_attrs[] = अणु
	&dev_attr_capability.attr,
	&dev_attr_events.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(pvpanic_pci_dev);

अटल पूर्णांक pvpanic_pci_probe(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pvpanic_instance *pi;
	व्योम __iomem *base;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		वापस ret;

	base = pci_iomap(pdev, 0, 0);
	अगर (!base)
		वापस -ENOMEM;

	pi = kदो_स्मृति(माप(*pi), GFP_ATOMIC);
	अगर (!pi)
		वापस -ENOMEM;

	pi->base = base;
	pi->capability = PVPANIC_PANICKED | PVPANIC_CRASH_LOADED;

	/* initlize capability by RDPT */
	pi->capability &= ioपढ़ो8(base);
	pi->events = pi->capability;

	dev_set_drvdata(dev, pi);

	वापस pvpanic_probe(pi);
पूर्ण

अटल व्योम pvpanic_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pvpanic_instance *pi = dev_get_drvdata(&pdev->dev);

	pvpanic_हटाओ(pi);
	iounmap(pi->base);
	kमुक्त(pi);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver pvpanic_pci_driver = अणु
	.name =         "pvpanic-pci",
	.id_table =     pvpanic_pci_id_tbl,
	.probe =        pvpanic_pci_probe,
	.हटाओ =       pvpanic_pci_हटाओ,
	.driver = अणु
		.dev_groups = pvpanic_pci_dev_groups,
	पूर्ण,
पूर्ण;

module_pci_driver(pvpanic_pci_driver);
