<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Interface क्रम Dynamic Logical Partitioning of I/O Slots on
 * RPA-compliant PPC64 platक्रमm.
 *
 * John Rose <johnrose@austin.ibm.com>
 * Linda Xie <lxie@us.ibm.com>
 *
 * October 2003
 *
 * Copyright (C) 2003 IBM.
 */

#अघोषित DEBUG

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/pci-bridge.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/vपन.स>
#समावेश <linux/firmware.h>

#समावेश "../pci.h"
#समावेश "rpaphp.h"
#समावेश "rpadlpar.h"

अटल DEFINE_MUTEX(rpadlpar_mutex);

#घोषणा DLPAR_MODULE_NAME "rpadlpar_io"

#घोषणा NODE_TYPE_VIO  1
#घोषणा NODE_TYPE_SLOT 2
#घोषणा NODE_TYPE_PHB  3

अटल काष्ठा device_node *find_vio_slot_node(अक्षर *drc_name)
अणु
	काष्ठा device_node *parent = of_find_node_by_name(शून्य, "vdevice");
	काष्ठा device_node *dn;
	पूर्णांक rc;

	अगर (!parent)
		वापस शून्य;

	क्रम_each_child_of_node(parent, dn) अणु
		rc = rpaphp_check_drc_props(dn, drc_name, शून्य);
		अगर (rc == 0)
			अवरोध;
	पूर्ण
	of_node_put(parent);

	वापस dn;
पूर्ण

/* Find dlpar-capable pci node that contains the specअगरied name and type */
अटल काष्ठा device_node *find_php_slot_pci_node(अक्षर *drc_name,
						  अक्षर *drc_type)
अणु
	काष्ठा device_node *np;
	पूर्णांक rc;

	क्रम_each_node_by_name(np, "pci") अणु
		rc = rpaphp_check_drc_props(np, drc_name, drc_type);
		अगर (rc == 0)
			अवरोध;
	पूर्ण

	वापस np;
पूर्ण

/* Returns a device_node with its reference count incremented */
अटल काष्ठा device_node *find_dlpar_node(अक्षर *drc_name, पूर्णांक *node_type)
अणु
	काष्ठा device_node *dn;

	dn = find_php_slot_pci_node(drc_name, "SLOT");
	अगर (dn) अणु
		*node_type = NODE_TYPE_SLOT;
		वापस dn;
	पूर्ण

	dn = find_php_slot_pci_node(drc_name, "PHB");
	अगर (dn) अणु
		*node_type = NODE_TYPE_PHB;
		वापस dn;
	पूर्ण

	dn = find_vio_slot_node(drc_name);
	अगर (dn) अणु
		*node_type = NODE_TYPE_VIO;
		वापस dn;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * find_php_slot - वापस hotplug slot काष्ठाure क्रम device node
 * @dn: target &device_node
 *
 * This routine will वापस the hotplug slot काष्ठाure
 * क्रम a given device node. Note that built-in PCI slots
 * may be dlpar-able, but not hot-pluggable, so this routine
 * will वापस शून्य क्रम built-in PCI slots.
 */
अटल काष्ठा slot *find_php_slot(काष्ठा device_node *dn)
अणु
	काष्ठा slot *slot, *next;

	list_क्रम_each_entry_safe(slot, next, &rpaphp_slot_head,
				 rpaphp_slot_list) अणु
		अगर (slot->dn == dn)
			वापस slot;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा pci_dev *dlpar_find_new_dev(काष्ठा pci_bus *parent,
					काष्ठा device_node *dev_dn)
अणु
	काष्ठा pci_dev *पंचांगp = शून्य;
	काष्ठा device_node *child_dn;

	list_क्रम_each_entry(पंचांगp, &parent->devices, bus_list) अणु
		child_dn = pci_device_to_OF_node(पंचांगp);
		अगर (child_dn == dev_dn)
			वापस पंचांगp;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम dlpar_pci_add_bus(काष्ठा device_node *dn)
अणु
	काष्ठा pci_dn *pdn = PCI_DN(dn);
	काष्ठा pci_controller *phb = pdn->phb;
	काष्ठा pci_dev *dev = शून्य;

	pseries_eeh_init_edev_recursive(pdn);

	/* Add EADS device to PHB bus, adding new entry to bus->devices */
	dev = of_create_pci_dev(dn, phb->bus, pdn->devfn);
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to create pci dev for %pOF\n",
				__func__, dn);
		वापस;
	पूर्ण

	/* Scan below the new bridge */
	अगर (pci_is_bridge(dev))
		of_scan_pci_bridge(dev);

	/* Map IO space क्रम child bus, which may or may not succeed */
	pcibios_map_io_space(dev->subordinate);

	/* Finish adding it : resource allocation, adding devices, etc...
	 * Note that we need to perक्रमm the finish pass on the -parent-
	 * bus of the EADS bridge so the bridge device itself माला_लो
	 * properly added
	 */
	pcibios_finish_adding_to_bus(phb->bus);
पूर्ण

अटल पूर्णांक dlpar_add_pci_slot(अक्षर *drc_name, काष्ठा device_node *dn)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_controller *phb;

	अगर (pci_find_bus_by_node(dn))
		वापस -EINVAL;

	/* Add pci bus */
	dlpar_pci_add_bus(dn);

	/* Confirm new bridge dev was created */
	phb = PCI_DN(dn)->phb;
	dev = dlpar_find_new_dev(phb->bus, dn);

	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to add bus %s\n", __func__,
			drc_name);
		वापस -EIO;
	पूर्ण

	अगर (dev->hdr_type != PCI_HEADER_TYPE_BRIDGE) अणु
		prपूर्णांकk(KERN_ERR "%s: unexpected header type %d, unable to add bus %s\n",
			__func__, dev->hdr_type, drc_name);
		वापस -EIO;
	पूर्ण

	/* Add hotplug slot */
	अगर (rpaphp_add_slot(dn)) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to add hotplug slot %s\n",
			__func__, drc_name);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dlpar_हटाओ_phb(अक्षर *drc_name, काष्ठा device_node *dn)
अणु
	काष्ठा slot *slot;
	काष्ठा pci_dn *pdn;
	पूर्णांक rc = 0;

	अगर (!pci_find_bus_by_node(dn))
		वापस -EINVAL;

	/* If pci slot is hotpluggable, use hotplug to हटाओ it */
	slot = find_php_slot(dn);
	अगर (slot && rpaphp_deरेजिस्टर_slot(slot)) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to remove hotplug slot %s\n",
		       __func__, drc_name);
		वापस -EIO;
	पूर्ण

	pdn = dn->data;
	BUG_ON(!pdn || !pdn->phb);
	rc = हटाओ_phb_dynamic(pdn->phb);
	अगर (rc < 0)
		वापस rc;

	pdn->phb = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक dlpar_add_phb(अक्षर *drc_name, काष्ठा device_node *dn)
अणु
	काष्ठा pci_controller *phb;

	अगर (PCI_DN(dn) && PCI_DN(dn)->phb) अणु
		/* PHB alपढ़ोy exists */
		वापस -EINVAL;
	पूर्ण

	phb = init_phb_dynamic(dn);
	अगर (!phb)
		वापस -EIO;

	अगर (rpaphp_add_slot(dn)) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to add hotplug slot %s\n",
			__func__, drc_name);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dlpar_add_vio_slot(अक्षर *drc_name, काष्ठा device_node *dn)
अणु
	काष्ठा vio_dev *vio_dev;

	vio_dev = vio_find_node(dn);
	अगर (vio_dev) अणु
		put_device(&vio_dev->dev);
		वापस -EINVAL;
	पूर्ण

	अगर (!vio_रेजिस्टर_device_node(dn)) अणु
		prपूर्णांकk(KERN_ERR
			"%s: failed to register vio node %s\n",
			__func__, drc_name);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dlpar_add_slot - DLPAR add an I/O Slot
 * @drc_name: drc-name of newly added slot
 *
 * Make the hotplug module and the kernel aware of a newly added I/O Slot.
 * Return Codes:
 * 0			Success
 * -ENODEV		Not a valid drc_name
 * -EINVAL		Slot alपढ़ोy added
 * -ERESTARTSYS		Signalled beक्रमe obtaining lock
 * -EIO			Internal PCI Error
 */
पूर्णांक dlpar_add_slot(अक्षर *drc_name)
अणु
	काष्ठा device_node *dn = शून्य;
	पूर्णांक node_type;
	पूर्णांक rc = -EIO;

	अगर (mutex_lock_पूर्णांकerruptible(&rpadlpar_mutex))
		वापस -ERESTARTSYS;

	/* Find newly added node */
	dn = find_dlpar_node(drc_name, &node_type);
	अगर (!dn) अणु
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	चयन (node_type) अणु
		हाल NODE_TYPE_VIO:
			rc = dlpar_add_vio_slot(drc_name, dn);
			अवरोध;
		हाल NODE_TYPE_SLOT:
			rc = dlpar_add_pci_slot(drc_name, dn);
			अवरोध;
		हाल NODE_TYPE_PHB:
			rc = dlpar_add_phb(drc_name, dn);
			अवरोध;
	पूर्ण
	of_node_put(dn);

	prपूर्णांकk(KERN_INFO "%s: slot %s added\n", DLPAR_MODULE_NAME, drc_name);
निकास:
	mutex_unlock(&rpadlpar_mutex);
	वापस rc;
पूर्ण

/**
 * dlpar_हटाओ_vio_slot - DLPAR हटाओ a भव I/O Slot
 * @drc_name: drc-name of newly added slot
 * @dn: &device_node
 *
 * Remove the kernel and hotplug representations of an I/O Slot.
 * Return Codes:
 * 0			Success
 * -EINVAL		Vio dev करोesn't exist
 */
अटल पूर्णांक dlpar_हटाओ_vio_slot(अक्षर *drc_name, काष्ठा device_node *dn)
अणु
	काष्ठा vio_dev *vio_dev;

	vio_dev = vio_find_node(dn);
	अगर (!vio_dev)
		वापस -EINVAL;

	vio_unरेजिस्टर_device(vio_dev);

	put_device(&vio_dev->dev);

	वापस 0;
पूर्ण

/**
 * dlpar_हटाओ_pci_slot - DLPAR हटाओ a PCI I/O Slot
 * @drc_name: drc-name of newly added slot
 * @dn: &device_node
 *
 * Remove the kernel and hotplug representations of a PCI I/O Slot.
 * Return Codes:
 * 0			Success
 * -ENODEV		Not a valid drc_name
 * -EIO			Internal PCI Error
 */
अटल पूर्णांक dlpar_हटाओ_pci_slot(अक्षर *drc_name, काष्ठा device_node *dn)
अणु
	काष्ठा pci_bus *bus;
	काष्ठा slot *slot;
	पूर्णांक ret = 0;

	pci_lock_rescan_हटाओ();

	bus = pci_find_bus_by_node(dn);
	अगर (!bus) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	pr_debug("PCI: Removing PCI slot below EADS bridge %s\n",
		 bus->self ? pci_name(bus->self) : "<!PHB!>");

	slot = find_php_slot(dn);
	अगर (slot) अणु
		pr_debug("PCI: Removing hotplug slot for %04x:%02x...\n",
			 pci_करोमुख्य_nr(bus), bus->number);

		अगर (rpaphp_deरेजिस्टर_slot(slot)) अणु
			prपूर्णांकk(KERN_ERR
				"%s: unable to remove hotplug slot %s\n",
				__func__, drc_name);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Remove all devices below slot */
	pci_hp_हटाओ_devices(bus);

	/* Unmap PCI IO space */
	अगर (pcibios_unmap_io_space(bus)) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to unmap bus range\n",
			__func__);
		ret = -दुस्फल;
		जाओ out;
	पूर्ण

	/* Remove the EADS bridge device itself */
	BUG_ON(!bus->self);
	pr_debug("PCI: Now removing bridge device %s\n", pci_name(bus->self));
	pci_stop_and_हटाओ_bus_device(bus->self);

 out:
	pci_unlock_rescan_हटाओ();
	वापस ret;
पूर्ण

/**
 * dlpar_हटाओ_slot - DLPAR हटाओ an I/O Slot
 * @drc_name: drc-name of newly added slot
 *
 * Remove the kernel and hotplug representations of an I/O Slot.
 * Return Codes:
 * 0			Success
 * -ENODEV		Not a valid drc_name
 * -EINVAL		Slot alपढ़ोy हटाओd
 * -ERESTARTSYS		Signalled beक्रमe obtaining lock
 * -EIO			Internal Error
 */
पूर्णांक dlpar_हटाओ_slot(अक्षर *drc_name)
अणु
	काष्ठा device_node *dn;
	पूर्णांक node_type;
	पूर्णांक rc = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&rpadlpar_mutex))
		वापस -ERESTARTSYS;

	dn = find_dlpar_node(drc_name, &node_type);
	अगर (!dn) अणु
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	चयन (node_type) अणु
		हाल NODE_TYPE_VIO:
			rc = dlpar_हटाओ_vio_slot(drc_name, dn);
			अवरोध;
		हाल NODE_TYPE_PHB:
			rc = dlpar_हटाओ_phb(drc_name, dn);
			अवरोध;
		हाल NODE_TYPE_SLOT:
			rc = dlpar_हटाओ_pci_slot(drc_name, dn);
			अवरोध;
	पूर्ण
	of_node_put(dn);
	vm_unmap_aliases();

	prपूर्णांकk(KERN_INFO "%s: slot %s removed\n", DLPAR_MODULE_NAME, drc_name);
निकास:
	mutex_unlock(&rpadlpar_mutex);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक is_dlpar_capable(व्योम)
अणु
	पूर्णांक rc = rtas_token("ibm,configure-connector");

	वापस (पूर्णांक) (rc != RTAS_UNKNOWN_SERVICE);
पूर्ण

अटल पूर्णांक __init rpadlpar_io_init(व्योम)
अणु

	अगर (!is_dlpar_capable()) अणु
		prपूर्णांकk(KERN_WARNING "%s: partition not DLPAR capable\n",
			__func__);
		वापस -EPERM;
	पूर्ण

	वापस dlpar_sysfs_init();
पूर्ण

अटल व्योम __निकास rpadlpar_io_निकास(व्योम)
अणु
	dlpar_sysfs_निकास();
पूर्ण

module_init(rpadlpar_io_init);
module_निकास(rpadlpar_io_निकास);
MODULE_LICENSE("GPL");
