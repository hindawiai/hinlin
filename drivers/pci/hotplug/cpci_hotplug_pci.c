<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * CompactPCI Hot Plug Driver PCI functions
 *
 * Copyright (C) 2002,2005 by SOMA Networks, Inc.
 *
 * All rights reserved.
 *
 * Send feedback to <scotपंचांग@somanetworks.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_hotplug.h>
#समावेश <linux/proc_fs.h>
#समावेश "../pci.h"
#समावेश "cpci_hotplug.h"

#घोषणा MY_NAME	"cpci_hotplug"

बाह्य पूर्णांक cpci_debug;

#घोषणा dbg(क्रमmat, arg...)					\
	करो अणु							\
		अगर (cpci_debug)					\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n",	\
				MY_NAME, ## arg);		\
	पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat "\n", MY_NAME, ## arg)


u8 cpci_get_attention_status(काष्ठा slot *slot)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस 0;

	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस 0;

	वापस hs_csr & 0x0008 ? 1 : 0;
पूर्ण

पूर्णांक cpci_set_attention_status(काष्ठा slot *slot, पूर्णांक status)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस 0;
	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस 0;
	अगर (status)
		hs_csr |= HS_CSR_LOO;
	अन्यथा
		hs_csr &= ~HS_CSR_LOO;
	अगर (pci_bus_ग_लिखो_config_word(slot->bus,
				      slot->devfn,
				      hs_cap + 2,
				      hs_csr))
		वापस 0;
	वापस 1;
पूर्ण

u16 cpci_get_hs_csr(काष्ठा slot *slot)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस 0xFFFF;
	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस 0xFFFF;
	वापस hs_csr;
पूर्ण

पूर्णांक cpci_check_and_clear_ins(काष्ठा slot *slot)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;
	पूर्णांक ins = 0;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस 0;
	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस 0;
	अगर (hs_csr & HS_CSR_INS) अणु
		/* Clear INS (by setting it) */
		अगर (pci_bus_ग_लिखो_config_word(slot->bus,
					      slot->devfn,
					      hs_cap + 2,
					      hs_csr))
			ins = 0;
		अन्यथा
			ins = 1;
	पूर्ण
	वापस ins;
पूर्ण

पूर्णांक cpci_check_ext(काष्ठा slot *slot)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;
	पूर्णांक ext = 0;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस 0;
	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस 0;
	अगर (hs_csr & HS_CSR_EXT)
		ext = 1;
	वापस ext;
पूर्ण

पूर्णांक cpci_clear_ext(काष्ठा slot *slot)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस -ENODEV;
	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस -ENODEV;
	अगर (hs_csr & HS_CSR_EXT) अणु
		/* Clear EXT (by setting it) */
		अगर (pci_bus_ग_लिखो_config_word(slot->bus,
					      slot->devfn,
					      hs_cap + 2,
					      hs_csr))
			वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cpci_led_on(काष्ठा slot *slot)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस -ENODEV;
	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस -ENODEV;
	अगर ((hs_csr & HS_CSR_LOO) != HS_CSR_LOO) अणु
		hs_csr |= HS_CSR_LOO;
		अगर (pci_bus_ग_लिखो_config_word(slot->bus,
					      slot->devfn,
					      hs_cap + 2,
					      hs_csr)) अणु
			err("Could not set LOO for slot %s", slot_name(slot));
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cpci_led_off(काष्ठा slot *slot)
अणु
	पूर्णांक hs_cap;
	u16 hs_csr;

	hs_cap = pci_bus_find_capability(slot->bus,
					 slot->devfn,
					 PCI_CAP_ID_CHSWP);
	अगर (!hs_cap)
		वापस -ENODEV;
	अगर (pci_bus_पढ़ो_config_word(slot->bus,
				     slot->devfn,
				     hs_cap + 2,
				     &hs_csr))
		वापस -ENODEV;
	अगर (hs_csr & HS_CSR_LOO) अणु
		hs_csr &= ~HS_CSR_LOO;
		अगर (pci_bus_ग_लिखो_config_word(slot->bus,
					      slot->devfn,
					      hs_cap + 2,
					      hs_csr)) अणु
			err("Could not clear LOO for slot %s", slot_name(slot));
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/*
 * Device configuration functions
 */

पूर्णांक cpci_configure_slot(काष्ठा slot *slot)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *parent;
	पूर्णांक ret = 0;

	dbg("%s - enter", __func__);

	pci_lock_rescan_हटाओ();

	अगर (slot->dev == शून्य) अणु
		dbg("pci_dev null, finding %02x:%02x:%x",
		    slot->bus->number, PCI_SLOT(slot->devfn), PCI_FUNC(slot->devfn));
		slot->dev = pci_get_slot(slot->bus, slot->devfn);
	पूर्ण

	/* Still शून्य? Well then scan क्रम it! */
	अगर (slot->dev == शून्य) अणु
		पूर्णांक n;
		dbg("pci_dev still null");

		/*
		 * This will generate pci_dev काष्ठाures क्रम all functions, but
		 * we will only call this हाल when lookup fails.
		 */
		n = pci_scan_slot(slot->bus, slot->devfn);
		dbg("%s: pci_scan_slot returned %d", __func__, n);
		slot->dev = pci_get_slot(slot->bus, slot->devfn);
		अगर (slot->dev == शून्य) अणु
			err("Could not find PCI device for slot %02x", slot->number);
			ret = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण
	parent = slot->dev->bus;

	क्रम_each_pci_bridge(dev, parent) अणु
		अगर (PCI_SLOT(dev->devfn) == PCI_SLOT(slot->devfn))
			pci_hp_add_bridge(dev);
	पूर्ण

	pci_assign_unasचिन्हित_bridge_resources(parent->self);

	pci_bus_add_devices(parent);

 out:
	pci_unlock_rescan_हटाओ();
	dbg("%s - exit", __func__);
	वापस ret;
पूर्ण

पूर्णांक cpci_unconfigure_slot(काष्ठा slot *slot)
अणु
	काष्ठा pci_dev *dev, *temp;

	dbg("%s - enter", __func__);
	अगर (!slot->dev) अणु
		err("No device for slot %02x\n", slot->number);
		वापस -ENODEV;
	पूर्ण

	pci_lock_rescan_हटाओ();

	list_क्रम_each_entry_safe(dev, temp, &slot->bus->devices, bus_list) अणु
		अगर (PCI_SLOT(dev->devfn) != PCI_SLOT(slot->devfn))
			जारी;
		pci_dev_get(dev);
		pci_stop_and_हटाओ_bus_device(dev);
		pci_dev_put(dev);
	पूर्ण
	pci_dev_put(slot->dev);
	slot->dev = शून्य;

	pci_unlock_rescan_हटाओ();

	dbg("%s - exit", __func__);
	वापस 0;
पूर्ण
