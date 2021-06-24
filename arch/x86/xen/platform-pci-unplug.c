<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/******************************************************************************
 * platक्रमm-pci-unplug.c
 *
 * Xen platक्रमm PCI device driver
 * Copyright (c) 2010, Citrix
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>

#समावेश <xen/xen.h>
#समावेश <xen/platक्रमm_pci.h>
#समावेश "xen-ops.h"

#घोषणा XEN_PLATFORM_ERR_MAGIC -1
#घोषणा XEN_PLATFORM_ERR_PROTOCOL -2
#घोषणा XEN_PLATFORM_ERR_BLACKLIST -3

/* store the value of xen_emul_unplug after the unplug is करोne */
अटल पूर्णांक xen_platक्रमm_pci_unplug;
अटल पूर्णांक xen_emul_unplug;

अटल पूर्णांक check_platक्रमm_magic(व्योम)
अणु
	लघु magic;
	अक्षर protocol;

	magic = inw(XEN_IOPORT_MAGIC);
	अगर (magic != XEN_IOPORT_MAGIC_VAL) अणु
		prपूर्णांकk(KERN_ERR "Xen Platform PCI: unrecognised magic value\n");
		वापस XEN_PLATFORM_ERR_MAGIC;
	पूर्ण

	protocol = inb(XEN_IOPORT_PROTOVER);

	prपूर्णांकk(KERN_DEBUG "Xen Platform PCI: I/O protocol version %d\n",
			protocol);

	चयन (protocol) अणु
	हाल 1:
		outw(XEN_IOPORT_LINUX_PRODNUM, XEN_IOPORT_PRODNUM);
		outl(XEN_IOPORT_LINUX_DRVVER, XEN_IOPORT_DRVVER);
		अगर (inw(XEN_IOPORT_MAGIC) != XEN_IOPORT_MAGIC_VAL) अणु
			prपूर्णांकk(KERN_ERR "Xen Platform: blacklisted by host\n");
			वापस XEN_PLATFORM_ERR_BLACKLIST;
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "Xen Platform PCI: unknown I/O protocol version\n");
		वापस XEN_PLATFORM_ERR_PROTOCOL;
	पूर्ण

	वापस 0;
पूर्ण

bool xen_has_pv_devices(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस false;

	/* PV and PVH करोमुख्यs always have them. */
	अगर (xen_pv_करोमुख्य() || xen_pvh_करोमुख्य())
		वापस true;

	/* And user has xen_platक्रमm_pci=0 set in guest config as
	 * driver did not modअगरy the value. */
	अगर (xen_platक्रमm_pci_unplug == 0)
		वापस false;

	अगर (xen_platक्रमm_pci_unplug & XEN_UNPLUG_NEVER)
		वापस false;

	अगर (xen_platक्रमm_pci_unplug & XEN_UNPLUG_ALL)
		वापस true;

	/* This is an odd one - we are going to run legacy
	 * and PV drivers at the same समय. */
	अगर (xen_platक्रमm_pci_unplug & XEN_UNPLUG_UNNECESSARY)
		वापस true;

	/* And the caller has to follow with xen_pv_अणुdisk,nicपूर्ण_devices
	 * to be certain which driver can load. */
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(xen_has_pv_devices);

अटल bool __xen_has_pv_device(पूर्णांक state)
अणु
	/* HVM करोमुख्यs might or might not */
	अगर (xen_hvm_करोमुख्य() && (xen_platक्रमm_pci_unplug & state))
		वापस true;

	वापस xen_has_pv_devices();
पूर्ण

bool xen_has_pv_nic_devices(व्योम)
अणु
	वापस __xen_has_pv_device(XEN_UNPLUG_ALL_NICS | XEN_UNPLUG_ALL);
पूर्ण
EXPORT_SYMBOL_GPL(xen_has_pv_nic_devices);

bool xen_has_pv_disk_devices(व्योम)
अणु
	वापस __xen_has_pv_device(XEN_UNPLUG_ALL_IDE_DISKS |
				   XEN_UNPLUG_AUX_IDE_DISKS | XEN_UNPLUG_ALL);
पूर्ण
EXPORT_SYMBOL_GPL(xen_has_pv_disk_devices);

/*
 * This one is odd - it determines whether you want to run PV _and_
 * legacy (IDE) drivers together. This combination is only possible
 * under HVM.
 */
bool xen_has_pv_and_legacy_disk_devices(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस false;

	/* N.B. This is only ever used in HVM mode */
	अगर (xen_pv_करोमुख्य())
		वापस false;

	अगर (xen_platक्रमm_pci_unplug & XEN_UNPLUG_UNNECESSARY)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(xen_has_pv_and_legacy_disk_devices);

व्योम xen_unplug_emulated_devices(व्योम)
अणु
	पूर्णांक r;

	/* PVH guests करोn't have emulated devices. */
	अगर (xen_pvh_करोमुख्य())
		वापस;

	/* user explicitly requested no unplug */
	अगर (xen_emul_unplug & XEN_UNPLUG_NEVER)
		वापस;
	/* check the version of the xen platक्रमm PCI device */
	r = check_platक्रमm_magic();
	/* If the version matches enable the Xen platक्रमm PCI driver.
	 * Also enable the Xen platक्रमm PCI driver अगर the host करोes
	 * not support the unplug protocol (XEN_PLATFORM_ERR_MAGIC)
	 * but the user told us that unplugging is unnecessary. */
	अगर (r && !(r == XEN_PLATFORM_ERR_MAGIC &&
			(xen_emul_unplug & XEN_UNPLUG_UNNECESSARY)))
		वापस;
	/* Set the शेष value of xen_emul_unplug depending on whether or
	 * not the Xen PV frontends and the Xen platक्रमm PCI driver have
	 * been compiled क्रम this kernel (modules or built-in are both OK). */
	अगर (!xen_emul_unplug) अणु
		अगर (xen_must_unplug_nics()) अणु
			prपूर्णांकk(KERN_INFO "Netfront and the Xen platform PCI driver have "
					"been compiled for this kernel: unplug emulated NICs.\n");
			xen_emul_unplug |= XEN_UNPLUG_ALL_NICS;
		पूर्ण
		अगर (xen_must_unplug_disks()) अणु
			prपूर्णांकk(KERN_INFO "Blkfront and the Xen platform PCI driver have "
					"been compiled for this kernel: unplug emulated disks.\n"
					"You might have to change the root device\n"
					"from /dev/hd[a-d] to /dev/xvd[a-d]\n"
					"in your root= kernel command line option\n");
			xen_emul_unplug |= XEN_UNPLUG_ALL_IDE_DISKS;
		पूर्ण
	पूर्ण
	/* Now unplug the emulated devices */
	अगर (!(xen_emul_unplug & XEN_UNPLUG_UNNECESSARY))
		outw(xen_emul_unplug, XEN_IOPORT_UNPLUG);
	xen_platक्रमm_pci_unplug = xen_emul_unplug;
पूर्ण

अटल पूर्णांक __init parse_xen_emul_unplug(अक्षर *arg)
अणु
	अक्षर *p, *q;
	पूर्णांक l;

	क्रम (p = arg; p; p = q) अणु
		q = म_अक्षर(p, ',');
		अगर (q) अणु
			l = q - p;
			q++;
		पूर्ण अन्यथा अणु
			l = म_माप(p);
		पूर्ण
		अगर (!म_भेदन(p, "all", l))
			xen_emul_unplug |= XEN_UNPLUG_ALL;
		अन्यथा अगर (!म_भेदन(p, "ide-disks", l))
			xen_emul_unplug |= XEN_UNPLUG_ALL_IDE_DISKS;
		अन्यथा अगर (!म_भेदन(p, "aux-ide-disks", l))
			xen_emul_unplug |= XEN_UNPLUG_AUX_IDE_DISKS;
		अन्यथा अगर (!म_भेदन(p, "nics", l))
			xen_emul_unplug |= XEN_UNPLUG_ALL_NICS;
		अन्यथा अगर (!म_भेदन(p, "unnecessary", l))
			xen_emul_unplug |= XEN_UNPLUG_UNNECESSARY;
		अन्यथा अगर (!म_भेदन(p, "never", l))
			xen_emul_unplug |= XEN_UNPLUG_NEVER;
		अन्यथा
			prपूर्णांकk(KERN_WARNING "unrecognised option '%s' "
				 "in parameter 'xen_emul_unplug'\n", p);
	पूर्ण
	वापस 0;
पूर्ण
early_param("xen_emul_unplug", parse_xen_emul_unplug);
