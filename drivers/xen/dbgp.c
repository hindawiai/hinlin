<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/pci.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ehci_def.h>
#समावेश <linux/usb/hcd.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश <xen/xen.h>

अटल पूर्णांक xen_dbgp_op(काष्ठा usb_hcd *hcd, पूर्णांक op)
अणु
#अगर_घोषित CONFIG_PCI
	स्थिर काष्ठा device *ctrlr = hcd_to_bus(hcd)->controller;
#पूर्ण_अगर
	काष्ठा physdev_dbgp_op dbgp;

	अगर (!xen_initial_करोमुख्य())
		वापस 0;

	dbgp.op = op;

#अगर_घोषित CONFIG_PCI
	अगर (dev_is_pci(ctrlr)) अणु
		स्थिर काष्ठा pci_dev *pdev = to_pci_dev(ctrlr);

		dbgp.u.pci.seg = pci_करोमुख्य_nr(pdev->bus);
		dbgp.u.pci.bus = pdev->bus->number;
		dbgp.u.pci.devfn = pdev->devfn;
		dbgp.bus = PHYSDEVOP_DBGP_BUS_PCI;
	पूर्ण अन्यथा
#पूर्ण_अगर
		dbgp.bus = PHYSDEVOP_DBGP_BUS_UNKNOWN;

	वापस HYPERVISOR_physdev_op(PHYSDEVOP_dbgp_op, &dbgp);
पूर्ण

पूर्णांक xen_dbgp_reset_prep(काष्ठा usb_hcd *hcd)
अणु
	वापस xen_dbgp_op(hcd, PHYSDEVOP_DBGP_RESET_PREPARE);
पूर्ण

पूर्णांक xen_dbgp_बाह्यal_startup(काष्ठा usb_hcd *hcd)
अणु
	वापस xen_dbgp_op(hcd, PHYSDEVOP_DBGP_RESET_DONE);
पूर्ण

#अगर_अघोषित CONFIG_EARLY_PRINTK_DBGP
#समावेश <linux/export.h>
EXPORT_SYMBOL_GPL(xen_dbgp_reset_prep);
EXPORT_SYMBOL_GPL(xen_dbgp_बाह्यal_startup);
#पूर्ण_अगर
