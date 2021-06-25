<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCI Hot Plug Controller Driver क्रम System z
 *
 * Copyright 2012 IBM Corp.
 *
 * Author(s):
 *   Jan Glauber <jang@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <यंत्र/pci_debug.h>
#समावेश <यंत्र/sclp.h>

#घोषणा SLOT_NAME_SIZE	10

अटल पूर्णांक enable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा zpci_dev *zdev = container_of(hotplug_slot, काष्ठा zpci_dev,
					     hotplug_slot);
	पूर्णांक rc;

	अगर (zdev->state != ZPCI_FN_STATE_STANDBY)
		वापस -EIO;

	rc = sclp_pci_configure(zdev->fid);
	zpci_dbg(3, "conf fid:%x, rc:%d\n", zdev->fid, rc);
	अगर (rc)
		वापस rc;
	zdev->state = ZPCI_FN_STATE_CONFIGURED;

	वापस zpci_scan_configured_device(zdev, zdev->fh);
पूर्ण

अटल पूर्णांक disable_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	काष्ठा zpci_dev *zdev = container_of(hotplug_slot, काष्ठा zpci_dev,
					     hotplug_slot);
	काष्ठा pci_dev *pdev;

	अगर (zdev->state != ZPCI_FN_STATE_CONFIGURED)
		वापस -EIO;

	pdev = pci_get_slot(zdev->zbus->bus, zdev->devfn);
	अगर (pdev && pci_num_vf(pdev)) अणु
		pci_dev_put(pdev);
		वापस -EBUSY;
	पूर्ण
	pci_dev_put(pdev);

	वापस zpci_deconfigure_device(zdev);
पूर्ण

अटल पूर्णांक get_घातer_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	काष्ठा zpci_dev *zdev = container_of(hotplug_slot, काष्ठा zpci_dev,
					     hotplug_slot);

	चयन (zdev->state) अणु
	हाल ZPCI_FN_STATE_STANDBY:
		*value = 0;
		अवरोध;
	शेष:
		*value = 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_adapter_status(काष्ठा hotplug_slot *hotplug_slot, u8 *value)
अणु
	/* अगर the slot निकासs it always contains a function */
	*value = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hotplug_slot_ops s390_hotplug_slot_ops = अणु
	.enable_slot =		enable_slot,
	.disable_slot =		disable_slot,
	.get_घातer_status =	get_घातer_status,
	.get_adapter_status =	get_adapter_status,
पूर्ण;

पूर्णांक zpci_init_slot(काष्ठा zpci_dev *zdev)
अणु
	अक्षर name[SLOT_NAME_SIZE];
	काष्ठा zpci_bus *zbus = zdev->zbus;

	zdev->hotplug_slot.ops = &s390_hotplug_slot_ops;

	snम_लिखो(name, SLOT_NAME_SIZE, "%08x", zdev->fid);
	वापस pci_hp_रेजिस्टर(&zdev->hotplug_slot, zbus->bus,
			       zdev->devfn, name);
पूर्ण

व्योम zpci_निकास_slot(काष्ठा zpci_dev *zdev)
अणु
	pci_hp_deरेजिस्टर(&zdev->hotplug_slot);
पूर्ण
