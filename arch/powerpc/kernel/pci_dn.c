<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pci_dn.c
 *
 * Copyright (C) 2001 Todd Inglett, IBM Corporation
 *
 * PCI manipulation via device_nodes.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/eeh.h>

/*
 * The function is used to find the firmware data of one
 * specअगरic PCI device, which is attached to the indicated
 * PCI bus. For VFs, their firmware data is linked to that
 * one of PF's bridge. For other devices, their firmware
 * data is linked to that of their bridge.
 */
अटल काष्ठा pci_dn *pci_bus_to_pdn(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_bus *pbus;
	काष्ठा device_node *dn;
	काष्ठा pci_dn *pdn;

	/*
	 * We probably have भव bus which करोesn't
	 * have associated bridge.
	 */
	pbus = bus;
	जबतक (pbus) अणु
		अगर (pci_is_root_bus(pbus) || pbus->self)
			अवरोध;

		pbus = pbus->parent;
	पूर्ण

	/*
	 * Except भव bus, all PCI buses should
	 * have device nodes.
	 */
	dn = pci_bus_to_OF_node(pbus);
	pdn = dn ? PCI_DN(dn) : शून्य;

	वापस pdn;
पूर्ण

काष्ठा pci_dn *pci_get_pdn_by_devfn(काष्ठा pci_bus *bus,
				    पूर्णांक devfn)
अणु
	काष्ठा device_node *dn = शून्य;
	काष्ठा pci_dn *parent, *pdn;
	काष्ठा pci_dev *pdev = शून्य;

	/* Fast path: fetch from PCI device */
	list_क्रम_each_entry(pdev, &bus->devices, bus_list) अणु
		अगर (pdev->devfn == devfn) अणु
			अगर (pdev->dev.archdata.pci_data)
				वापस pdev->dev.archdata.pci_data;

			dn = pci_device_to_OF_node(pdev);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Fast path: fetch from device node */
	pdn = dn ? PCI_DN(dn) : शून्य;
	अगर (pdn)
		वापस pdn;

	/* Slow path: fetch from firmware data hierarchy */
	parent = pci_bus_to_pdn(bus);
	अगर (!parent)
		वापस शून्य;

	list_क्रम_each_entry(pdn, &parent->child_list, list) अणु
		अगर (pdn->busno == bus->number &&
                    pdn->devfn == devfn)
                        वापस pdn;
        पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा pci_dn *pci_get_pdn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_node *dn;
	काष्ठा pci_dn *parent, *pdn;

	/* Search device directly */
	अगर (pdev->dev.archdata.pci_data)
		वापस pdev->dev.archdata.pci_data;

	/* Check device node */
	dn = pci_device_to_OF_node(pdev);
	pdn = dn ? PCI_DN(dn) : शून्य;
	अगर (pdn)
		वापस pdn;

	/*
	 * VFs करोn't have device nodes. We hook their
	 * firmware data to PF's bridge.
	 */
	parent = pci_bus_to_pdn(pdev->bus);
	अगर (!parent)
		वापस शून्य;

	list_क्रम_each_entry(pdn, &parent->child_list, list) अणु
		अगर (pdn->busno == pdev->bus->number &&
		    pdn->devfn == pdev->devfn)
			वापस pdn;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_EEH
अटल काष्ठा eeh_dev *eeh_dev_init(काष्ठा pci_dn *pdn)
अणु
	काष्ठा eeh_dev *edev;

	/* Allocate EEH device */
	edev = kzalloc(माप(*edev), GFP_KERNEL);
	अगर (!edev)
		वापस शून्य;

	/* Associate EEH device with OF node */
	pdn->edev = edev;
	edev->pdn = pdn;
	edev->bdfn = (pdn->busno << 8) | pdn->devfn;
	edev->controller = pdn->phb;

	वापस edev;
पूर्ण
#पूर्ण_अगर /* CONFIG_EEH */

#अगर_घोषित CONFIG_PCI_IOV
अटल काष्ठा pci_dn *add_one_sriov_vf_pdn(काष्ठा pci_dn *parent,
					   पूर्णांक busno, पूर्णांक devfn)
अणु
	काष्ठा pci_dn *pdn;

	/* Except PHB, we always have the parent */
	अगर (!parent)
		वापस शून्य;

	pdn = kzalloc(माप(*pdn), GFP_KERNEL);
	अगर (!pdn)
		वापस शून्य;

	pdn->phb = parent->phb;
	pdn->parent = parent;
	pdn->busno = busno;
	pdn->devfn = devfn;
	pdn->pe_number = IODA_INVALID_PE;
	INIT_LIST_HEAD(&pdn->child_list);
	INIT_LIST_HEAD(&pdn->list);
	list_add_tail(&pdn->list, &parent->child_list);

	वापस pdn;
पूर्ण

काष्ठा pci_dn *add_sriov_vf_pdns(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn *parent, *pdn;
	पूर्णांक i;

	/* Only support IOV क्रम now */
	अगर (WARN_ON(!pdev->is_physfn))
		वापस शून्य;

	/* Check अगर VFs have been populated */
	pdn = pci_get_pdn(pdev);
	अगर (!pdn || (pdn->flags & PCI_DN_FLAG_IOV_VF))
		वापस शून्य;

	pdn->flags |= PCI_DN_FLAG_IOV_VF;
	parent = pci_bus_to_pdn(pdev->bus);
	अगर (!parent)
		वापस शून्य;

	क्रम (i = 0; i < pci_sriov_get_totalvfs(pdev); i++) अणु
		काष्ठा eeh_dev *edev __maybe_unused;

		pdn = add_one_sriov_vf_pdn(parent,
					   pci_iov_virtfn_bus(pdev, i),
					   pci_iov_virtfn_devfn(pdev, i));
		अगर (!pdn) अणु
			dev_warn(&pdev->dev, "%s: Cannot create firmware data for VF#%d\n",
				 __func__, i);
			वापस शून्य;
		पूर्ण

#अगर_घोषित CONFIG_EEH
		/* Create the EEH device क्रम the VF */
		edev = eeh_dev_init(pdn);
		BUG_ON(!edev);

		/* FIXME: these should probably be populated by the EEH probe */
		edev->physfn = pdev;
		edev->vf_index = i;
#पूर्ण_अगर /* CONFIG_EEH */
	पूर्ण
	वापस pci_get_pdn(pdev);
पूर्ण

व्योम हटाओ_sriov_vf_pdns(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn *parent;
	काष्ठा pci_dn *pdn, *पंचांगp;
	पूर्णांक i;

	/* Only support IOV PF क्रम now */
	अगर (WARN_ON(!pdev->is_physfn))
		वापस;

	/* Check अगर VFs have been populated */
	pdn = pci_get_pdn(pdev);
	अगर (!pdn || !(pdn->flags & PCI_DN_FLAG_IOV_VF))
		वापस;

	pdn->flags &= ~PCI_DN_FLAG_IOV_VF;
	parent = pci_bus_to_pdn(pdev->bus);
	अगर (!parent)
		वापस;

	/*
	 * We might पूर्णांकroduce flag to pci_dn in future
	 * so that we can release VF's firmware data in
	 * a batch mode.
	 */
	क्रम (i = 0; i < pci_sriov_get_totalvfs(pdev); i++) अणु
		काष्ठा eeh_dev *edev __maybe_unused;

		list_क्रम_each_entry_safe(pdn, पंचांगp,
			&parent->child_list, list) अणु
			अगर (pdn->busno != pci_iov_virtfn_bus(pdev, i) ||
			    pdn->devfn != pci_iov_virtfn_devfn(pdev, i))
				जारी;

#अगर_घोषित CONFIG_EEH
			/*
			 * Release EEH state क्रम this VF. The PCI core
			 * has alपढ़ोy torn करोwn the pci_dev क्रम this VF, but
			 * we're responsible to removing the eeh_dev since it
			 * has the same lअगरeसमय as the pci_dn that spawned it.
			 */
			edev = pdn_to_eeh_dev(pdn);
			अगर (edev) अणु
				/*
				 * We allocate pci_dn's क्रम the totalvfs count,
				 * but only only the vfs that were activated
				 * have a configured PE.
				 */
				अगर (edev->pe)
					eeh_pe_tree_हटाओ(edev);

				pdn->edev = शून्य;
				kमुक्त(edev);
			पूर्ण
#पूर्ण_अगर /* CONFIG_EEH */

			अगर (!list_empty(&pdn->list))
				list_del(&pdn->list);

			kमुक्त(pdn);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */

काष्ठा pci_dn *pci_add_device_node_info(काष्ठा pci_controller *hose,
					काष्ठा device_node *dn)
अणु
	स्थिर __be32 *type = of_get_property(dn, "ibm,pci-config-space-type", शून्य);
	स्थिर __be32 *regs;
	काष्ठा device_node *parent;
	काष्ठा pci_dn *pdn;
#अगर_घोषित CONFIG_EEH
	काष्ठा eeh_dev *edev;
#पूर्ण_अगर

	pdn = kzalloc(माप(*pdn), GFP_KERNEL);
	अगर (pdn == शून्य)
		वापस शून्य;
	dn->data = pdn;
	pdn->phb = hose;
	pdn->pe_number = IODA_INVALID_PE;
	regs = of_get_property(dn, "reg", शून्य);
	अगर (regs) अणु
		u32 addr = of_पढ़ो_number(regs, 1);

		/* First रेजिस्टर entry is addr (00BBSS00)  */
		pdn->busno = (addr >> 16) & 0xff;
		pdn->devfn = (addr >> 8) & 0xff;
	पूर्ण

	/* venकरोr/device IDs and class code */
	regs = of_get_property(dn, "vendor-id", शून्य);
	pdn->venकरोr_id = regs ? of_पढ़ो_number(regs, 1) : 0;
	regs = of_get_property(dn, "device-id", शून्य);
	pdn->device_id = regs ? of_पढ़ो_number(regs, 1) : 0;
	regs = of_get_property(dn, "class-code", शून्य);
	pdn->class_code = regs ? of_पढ़ो_number(regs, 1) : 0;

	/* Extended config space */
	pdn->pci_ext_config_space = (type && of_पढ़ो_number(type, 1) == 1);

	/* Create EEH device */
#अगर_घोषित CONFIG_EEH
	edev = eeh_dev_init(pdn);
	अगर (!edev) अणु
		kमुक्त(pdn);
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर

	/* Attach to parent node */
	INIT_LIST_HEAD(&pdn->child_list);
	INIT_LIST_HEAD(&pdn->list);
	parent = of_get_parent(dn);
	pdn->parent = parent ? PCI_DN(parent) : शून्य;
	अगर (pdn->parent)
		list_add_tail(&pdn->list, &pdn->parent->child_list);

	वापस pdn;
पूर्ण
EXPORT_SYMBOL_GPL(pci_add_device_node_info);

व्योम pci_हटाओ_device_node_info(काष्ठा device_node *dn)
अणु
	काष्ठा pci_dn *pdn = dn ? PCI_DN(dn) : शून्य;
	काष्ठा device_node *parent;
	काष्ठा pci_dev *pdev;
#अगर_घोषित CONFIG_EEH
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);

	अगर (edev)
		edev->pdn = शून्य;
#पूर्ण_अगर

	अगर (!pdn)
		वापस;

	WARN_ON(!list_empty(&pdn->child_list));
	list_del(&pdn->list);

	/* Drop the parent pci_dn's ref to our backing dt node */
	parent = of_get_parent(dn);
	अगर (parent)
		of_node_put(parent);

	/*
	 * At this poपूर्णांक we *might* still have a pci_dev that was
	 * instantiated from this pci_dn. So defer मुक्त()ing it until
	 * the pci_dev's release function is called.
	 */
	pdev = pci_get_करोमुख्य_bus_and_slot(pdn->phb->global_number,
			pdn->busno, pdn->devfn);
	अगर (pdev) अणु
		/* NB: pdev has a ref to dn */
		pci_dbg(pdev, "marked pdn (from %pOF) as dead\n", dn);
		pdn->flags |= PCI_DN_FLAG_DEAD;
	पूर्ण अन्यथा अणु
		dn->data = शून्य;
		kमुक्त(pdn);
	पूर्ण

	pci_dev_put(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(pci_हटाओ_device_node_info);

/*
 * Traverse a device tree stopping each PCI device in the tree.
 * This is करोne depth first.  As each node is processed, a "pre"
 * function is called and the children are processed recursively.
 *
 * The "pre" func वापसs a value.  If non-zero is वापसed from
 * the "pre" func, the traversal stops and this value is वापसed.
 * This वापस value is useful when using traverse as a method of
 * finding a device.
 *
 * NOTE: we करो not run the func क्रम devices that करो not appear to
 * be PCI except क्रम the start node which we assume (this is good
 * because the start node is often a phb which may be missing PCI
 * properties).
 * We use the class-code as an indicator. If we run पूर्णांकo
 * one of these nodes we also assume its siblings are non-pci क्रम
 * perक्रमmance.
 */
व्योम *pci_traverse_device_nodes(काष्ठा device_node *start,
				व्योम *(*fn)(काष्ठा device_node *, व्योम *),
				व्योम *data)
अणु
	काष्ठा device_node *dn, *nextdn;
	व्योम *ret;

	/* We started with a phb, iterate all childs */
	क्रम (dn = start->child; dn; dn = nextdn) अणु
		स्थिर __be32 *classp;
		u32 class = 0;

		nextdn = शून्य;
		classp = of_get_property(dn, "class-code", शून्य);
		अगर (classp)
			class = of_पढ़ो_number(classp, 1);

		अगर (fn) अणु
			ret = fn(dn, data);
			अगर (ret)
				वापस ret;
		पूर्ण

		/* If we are a PCI bridge, go करोwn */
		अगर (dn->child && ((class >> 8) == PCI_CLASS_BRIDGE_PCI ||
				  (class >> 8) == PCI_CLASS_BRIDGE_CARDBUS))
			/* Depth first...करो children */
			nextdn = dn->child;
		अन्यथा अगर (dn->sibling)
			/* ok, try next sibling instead. */
			nextdn = dn->sibling;
		अगर (!nextdn) अणु
			/* Walk up to next valid sibling. */
			करो अणु
				dn = dn->parent;
				अगर (dn == start)
					वापस शून्य;
			पूर्ण जबतक (dn->sibling == शून्य);
			nextdn = dn->sibling;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pci_traverse_device_nodes);

अटल व्योम *add_pdn(काष्ठा device_node *dn, व्योम *data)
अणु
	काष्ठा pci_controller *hose = data;
	काष्ठा pci_dn *pdn;

	pdn = pci_add_device_node_info(hose, dn);
	अगर (!pdn)
		वापस ERR_PTR(-ENOMEM);

	वापस शून्य;
पूर्ण

/** 
 * pci_devs_phb_init_dynamic - setup pci devices under this PHB
 * phb: pci-to-host bridge (top-level bridge connecting to cpu)
 *
 * This routine is called both during boot, (beक्रमe the memory
 * subप्रणाली is set up, beक्रमe kदो_स्मृति is valid) and during the 
 * dynamic lpar operation of adding a PHB to a running प्रणाली.
 */
व्योम pci_devs_phb_init_dynamic(काष्ठा pci_controller *phb)
अणु
	काष्ठा device_node *dn = phb->dn;
	काष्ठा pci_dn *pdn;

	/* PHB nodes themselves must not match */
	pdn = pci_add_device_node_info(phb, dn);
	अगर (pdn) अणु
		pdn->devfn = pdn->busno = -1;
		pdn->venकरोr_id = pdn->device_id = pdn->class_code = 0;
		pdn->phb = phb;
		phb->pci_data = pdn;
	पूर्ण

	/* Update dn->phb ptrs क्रम new phb and children devices */
	pci_traverse_device_nodes(dn, add_pdn, phb);
पूर्ण

अटल व्योम pci_dev_pdn_setup(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn *pdn;

	अगर (pdev->dev.archdata.pci_data)
		वापस;

	/* Setup the fast path */
	pdn = pci_get_pdn(pdev);
	pdev->dev.archdata.pci_data = pdn;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_ANY_ID, PCI_ANY_ID, pci_dev_pdn_setup);
