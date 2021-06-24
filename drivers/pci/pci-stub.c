<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Simple stub driver to reserve a PCI device
 *
 * Copyright (C) 2008 Red Hat, Inc.
 * Author:
 *	Chris Wright
 *
 * Usage is simple, allocate a new id to the stub driver and bind the
 * device to it.  For example:
 *
 * # echo "8086 10f5" > /sys/bus/pci/drivers/pci-stub/new_id
 * # echo -n 0000:00:19.0 > /sys/bus/pci/drivers/e1000e/unbind
 * # echo -n 0000:00:19.0 > /sys/bus/pci/drivers/pci-stub/bind
 * # ls -l /sys/bus/pci/devices/0000:00:19.0/driver
 * .../0000:00:19.0/driver -> ../../../bus/pci/drivers/pci-stub
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

अटल अक्षर ids[1024] __initdata;

module_param_string(ids, ids, माप(ids), 0);
MODULE_PARM_DESC(ids, "Initial PCI IDs to add to the stub driver, format is "
		 "\"vendor:device[:subvendor[:subdevice[:class[:class_mask]]]]\""
		 " and multiple comma separated entries can be specified");

अटल पूर्णांक pci_stub_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	pci_info(dev, "claimed by stub\n");
	वापस 0;
पूर्ण

अटल काष्ठा pci_driver stub_driver = अणु
	.name		= "pci-stub",
	.id_table	= शून्य,	/* only dynamic id's */
	.probe		= pci_stub_probe,
पूर्ण;

अटल पूर्णांक __init pci_stub_init(व्योम)
अणु
	अक्षर *p, *id;
	पूर्णांक rc;

	rc = pci_रेजिस्टर_driver(&stub_driver);
	अगर (rc)
		वापस rc;

	/* no ids passed actually */
	अगर (ids[0] == '\0')
		वापस 0;

	/* add ids specअगरied in the module parameter */
	p = ids;
	जबतक ((id = strsep(&p, ","))) अणु
		अचिन्हित पूर्णांक venकरोr, device, subvenकरोr = PCI_ANY_ID,
			subdevice = PCI_ANY_ID, class = 0, class_mask = 0;
		पूर्णांक fields;

		अगर (!म_माप(id))
			जारी;

		fields = माला_पूछो(id, "%x:%x:%x:%x:%x:%x",
				&venकरोr, &device, &subvenकरोr, &subdevice,
				&class, &class_mask);

		अगर (fields < 2) अणु
			pr_warn("pci-stub: invalid ID string \"%s\"\n", id);
			जारी;
		पूर्ण

		pr_info("pci-stub: add %04X:%04X sub=%04X:%04X cls=%08X/%08X\n",
		       venकरोr, device, subvenकरोr, subdevice, class, class_mask);

		rc = pci_add_dynid(&stub_driver, venकरोr, device,
				   subvenकरोr, subdevice, class, class_mask, 0);
		अगर (rc)
			pr_warn("pci-stub: failed to add dynamic ID (%d)\n",
				rc);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास pci_stub_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&stub_driver);
पूर्ण

module_init(pci_stub_init);
module_निकास(pci_stub_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Wright <chrisw@sous-sol.org>");
