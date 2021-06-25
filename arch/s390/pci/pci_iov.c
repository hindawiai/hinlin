<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2020
 *
 * Author(s):
 *   Niklas Schnelle <schnelle@linux.ibm.com>
 *
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>

#समावेश "pci_iov.h"

अटल काष्ठा resource iov_res = अणु
	.name	= "PCI IOV res",
	.start	= 0,
	.end	= -1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

व्योम zpci_iov_map_resources(काष्ठा pci_dev *pdev)
अणु
	resource_माप_प्रकार len;
	पूर्णांक i;

	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		पूर्णांक bar = i + PCI_IOV_RESOURCES;

		len = pci_resource_len(pdev, bar);
		अगर (!len)
			जारी;
		pdev->resource[bar].parent = &iov_res;
	पूर्ण
पूर्ण

व्योम zpci_iov_हटाओ_virtfn(काष्ठा pci_dev *pdev, पूर्णांक vfn)
अणु
	pci_lock_rescan_हटाओ();
	/* Linux' vfid's start at 0 vfn at 1 */
	pci_iov_हटाओ_virtfn(pdev->physfn, vfn - 1);
	pci_unlock_rescan_हटाओ();
पूर्ण

अटल पूर्णांक zpci_iov_link_virtfn(काष्ठा pci_dev *pdev, काष्ठा pci_dev *virtfn, पूर्णांक vfid)
अणु
	पूर्णांक rc;

	rc = pci_iov_sysfs_link(pdev, virtfn, vfid);
	अगर (rc)
		वापस rc;

	virtfn->is_virtfn = 1;
	virtfn->multअगरunction = 0;
	virtfn->physfn = pci_dev_get(pdev);

	वापस 0;
पूर्ण

पूर्णांक zpci_iov_setup_virtfn(काष्ठा zpci_bus *zbus, काष्ठा pci_dev *virtfn, पूर्णांक vfn)
अणु
	पूर्णांक i, cand_devfn;
	काष्ठा zpci_dev *zdev;
	काष्ठा pci_dev *pdev;
	पूर्णांक vfid = vfn - 1; /* Linux' vfid's start at 0 vfn at 1*/
	पूर्णांक rc = 0;

	अगर (!zbus->multअगरunction)
		वापस 0;

	/* If the parent PF क्रम the given VF is also configured in the
	 * instance, it must be on the same zbus.
	 * We can then identअगरy the parent PF by checking what
	 * devfn the VF would have अगर it beदीर्घed to that PF using the PF's
	 * stride and offset. Only अगर this candidate devfn matches the
	 * actual devfn will we link both functions.
	 */
	क्रम (i = 0; i < ZPCI_FUNCTIONS_PER_BUS; i++) अणु
		zdev = zbus->function[i];
		अगर (zdev && zdev->is_physfn) अणु
			pdev = pci_get_slot(zbus->bus, zdev->devfn);
			अगर (!pdev)
				जारी;
			cand_devfn = pci_iov_virtfn_devfn(pdev, vfid);
			अगर (cand_devfn == virtfn->devfn) अणु
				rc = zpci_iov_link_virtfn(pdev, virtfn, vfid);
				/* balance pci_get_slot() */
				pci_dev_put(pdev);
				अवरोध;
			पूर्ण
			/* balance pci_get_slot() */
			pci_dev_put(pdev);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण
