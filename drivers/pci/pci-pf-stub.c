<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci-pf-stub - simple stub driver क्रम PCI SR-IOV PF device
 *
 * This driver is meant to act as a "whitelist" क्रम devices that provide
 * SR-IOV functionality जबतक at the same समय not actually needing a
 * driver of their own.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

/*
 * pci_pf_stub_whitelist - White list of devices to bind pci-pf-stub onto
 *
 * This table provides the list of IDs this driver is supposed to bind
 * onto.  You could think of this as a list of "quirked" devices where we
 * are adding support क्रम SR-IOV here since there are no other drivers
 * that they would be running under.
 */
अटल स्थिर काष्ठा pci_device_id pci_pf_stub_whitelist[] = अणु
	अणु PCI_VDEVICE(AMAZON, 0x0053) पूर्ण,
	/* required last entry */
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_pf_stub_whitelist);

अटल पूर्णांक pci_pf_stub_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	pci_info(dev, "claimed by pci-pf-stub\n");
	वापस 0;
पूर्ण

अटल काष्ठा pci_driver pf_stub_driver = अणु
	.name			= "pci-pf-stub",
	.id_table		= pci_pf_stub_whitelist,
	.probe			= pci_pf_stub_probe,
	.sriov_configure	= pci_sriov_configure_simple,
पूर्ण;
module_pci_driver(pf_stub_driver);

MODULE_LICENSE("GPL");
