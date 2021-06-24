<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The file पूर्णांकends to implement PE based on the inक्रमmation from
 * platक्रमms. Basically, there have 3 types of PEs: PHB/Bus/Device.
 * All the PEs should be organized as hierarchy tree. The first level
 * of the tree will be associated to existing PHBs since the particular
 * PE is only meaningful in one PHB करोमुख्य.
 *
 * Copyright Benjamin Herrenschmidt & Gavin Shan, IBM Corporation 2012.
 */

#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/ppc-pci.h>

अटल पूर्णांक eeh_pe_aux_size = 0;
अटल LIST_HEAD(eeh_phb_pe);

/**
 * eeh_set_pe_aux_size - Set PE auxillary data size
 * @size: PE auxillary data size
 *
 * Set PE auxillary data size
 */
व्योम eeh_set_pe_aux_size(पूर्णांक size)
अणु
	अगर (size < 0)
		वापस;

	eeh_pe_aux_size = size;
पूर्ण

/**
 * eeh_pe_alloc - Allocate PE
 * @phb: PCI controller
 * @type: PE type
 *
 * Allocate PE instance dynamically.
 */
अटल काष्ठा eeh_pe *eeh_pe_alloc(काष्ठा pci_controller *phb, पूर्णांक type)
अणु
	काष्ठा eeh_pe *pe;
	माप_प्रकार alloc_size;

	alloc_size = माप(काष्ठा eeh_pe);
	अगर (eeh_pe_aux_size) अणु
		alloc_size = ALIGN(alloc_size, cache_line_size());
		alloc_size += eeh_pe_aux_size;
	पूर्ण

	/* Allocate PHB PE */
	pe = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!pe) वापस शून्य;

	/* Initialize PHB PE */
	pe->type = type;
	pe->phb = phb;
	INIT_LIST_HEAD(&pe->child_list);
	INIT_LIST_HEAD(&pe->edevs);

	pe->data = (व्योम *)pe + ALIGN(माप(काष्ठा eeh_pe),
				      cache_line_size());
	वापस pe;
पूर्ण

/**
 * eeh_phb_pe_create - Create PHB PE
 * @phb: PCI controller
 *
 * The function should be called जबतक the PHB is detected during
 * प्रणाली boot or PCI hotplug in order to create PHB PE.
 */
पूर्णांक eeh_phb_pe_create(काष्ठा pci_controller *phb)
अणु
	काष्ठा eeh_pe *pe;

	/* Allocate PHB PE */
	pe = eeh_pe_alloc(phb, EEH_PE_PHB);
	अगर (!pe) अणु
		pr_err("%s: out of memory!\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	/* Put it पूर्णांकo the list */
	list_add_tail(&pe->child, &eeh_phb_pe);

	pr_debug("EEH: Add PE for PHB#%x\n", phb->global_number);

	वापस 0;
पूर्ण

/**
 * eeh_रुको_state - Wait क्रम PE state
 * @pe: EEH PE
 * @max_रुको: maximal period in millisecond
 *
 * Wait क्रम the state of associated PE. It might take some समय
 * to retrieve the PE's state.
 */
पूर्णांक eeh_रुको_state(काष्ठा eeh_pe *pe, पूर्णांक max_रुको)
अणु
	पूर्णांक ret;
	पूर्णांक mरुको;

	/*
	 * According to PAPR, the state of PE might be temporarily
	 * unavailable. Under the circumstance, we have to रुको
	 * क्रम indicated समय determined by firmware. The maximal
	 * रुको समय is 5 minutes, which is acquired from the original
	 * EEH implementation. Also, the original implementation
	 * also defined the minimal रुको समय as 1 second.
	 */
#घोषणा EEH_STATE_MIN_WAIT_TIME	(1000)
#घोषणा EEH_STATE_MAX_WAIT_TIME	(300 * 1000)

	जबतक (1) अणु
		ret = eeh_ops->get_state(pe, &mरुको);

		अगर (ret != EEH_STATE_UNAVAILABLE)
			वापस ret;

		अगर (max_रुको <= 0) अणु
			pr_warn("%s: Timeout when getting PE's state (%d)\n",
				__func__, max_रुको);
			वापस EEH_STATE_NOT_SUPPORT;
		पूर्ण

		अगर (mरुको < EEH_STATE_MIN_WAIT_TIME) अणु
			pr_warn("%s: Firmware returned bad wait value %d\n",
				__func__, mरुको);
			mरुको = EEH_STATE_MIN_WAIT_TIME;
		पूर्ण अन्यथा अगर (mरुको > EEH_STATE_MAX_WAIT_TIME) अणु
			pr_warn("%s: Firmware returned too long wait value %d\n",
				__func__, mरुको);
			mरुको = EEH_STATE_MAX_WAIT_TIME;
		पूर्ण

		msleep(min(mरुको, max_रुको));
		max_रुको -= mरुको;
	पूर्ण
पूर्ण

/**
 * eeh_phb_pe_get - Retrieve PHB PE based on the given PHB
 * @phb: PCI controller
 *
 * The overall PEs क्रमm hierarchy tree. The first layer of the
 * hierarchy tree is composed of PHB PEs. The function is used
 * to retrieve the corresponding PHB PE according to the given PHB.
 */
काष्ठा eeh_pe *eeh_phb_pe_get(काष्ठा pci_controller *phb)
अणु
	काष्ठा eeh_pe *pe;

	list_क्रम_each_entry(pe, &eeh_phb_pe, child) अणु
		/*
		 * Actually, we needn't check the type since
		 * the PE क्रम PHB has been determined when that
		 * was created.
		 */
		अगर ((pe->type & EEH_PE_PHB) && pe->phb == phb)
			वापस pe;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * eeh_pe_next - Retrieve the next PE in the tree
 * @pe: current PE
 * @root: root PE
 *
 * The function is used to retrieve the next PE in the
 * hierarchy PE tree.
 */
काष्ठा eeh_pe *eeh_pe_next(काष्ठा eeh_pe *pe, काष्ठा eeh_pe *root)
अणु
	काष्ठा list_head *next = pe->child_list.next;

	अगर (next == &pe->child_list) अणु
		जबतक (1) अणु
			अगर (pe == root)
				वापस शून्य;
			next = pe->child.next;
			अगर (next != &pe->parent->child_list)
				अवरोध;
			pe = pe->parent;
		पूर्ण
	पूर्ण

	वापस list_entry(next, काष्ठा eeh_pe, child);
पूर्ण

/**
 * eeh_pe_traverse - Traverse PEs in the specअगरied PHB
 * @root: root PE
 * @fn: callback
 * @flag: extra parameter to callback
 *
 * The function is used to traverse the specअगरied PE and its
 * child PEs. The traversing is to be terminated once the
 * callback वापसs something other than शून्य, or no more PEs
 * to be traversed.
 */
व्योम *eeh_pe_traverse(काष्ठा eeh_pe *root,
		      eeh_pe_traverse_func fn, व्योम *flag)
अणु
	काष्ठा eeh_pe *pe;
	व्योम *ret;

	eeh_क्रम_each_pe(root, pe) अणु
		ret = fn(pe, flag);
		अगर (ret) वापस ret;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * eeh_pe_dev_traverse - Traverse the devices from the PE
 * @root: EEH PE
 * @fn: function callback
 * @flag: extra parameter to callback
 *
 * The function is used to traverse the devices of the specअगरied
 * PE and its child PEs.
 */
व्योम eeh_pe_dev_traverse(काष्ठा eeh_pe *root,
			  eeh_edev_traverse_func fn, व्योम *flag)
अणु
	काष्ठा eeh_pe *pe;
	काष्ठा eeh_dev *edev, *पंचांगp;

	अगर (!root) अणु
		pr_warn("%s: Invalid PE %p\n",
			__func__, root);
		वापस;
	पूर्ण

	/* Traverse root PE */
	eeh_क्रम_each_pe(root, pe)
		eeh_pe_क्रम_each_dev(pe, edev, पंचांगp)
			fn(edev, flag);
पूर्ण

/**
 * __eeh_pe_get - Check the PE address
 *
 * For one particular PE, it can be identअगरied by PE address
 * or tअक्रमitional BDF address. BDF address is composed of
 * Bus/Device/Function number. The extra data referred by flag
 * indicates which type of address should be used.
 */
अटल व्योम *__eeh_pe_get(काष्ठा eeh_pe *pe, व्योम *flag)
अणु
	पूर्णांक *target_pe = flag;

	/* PHB PEs are special and should be ignored */
	अगर (pe->type & EEH_PE_PHB)
		वापस शून्य;

	अगर (*target_pe == pe->addr)
		वापस pe;

	वापस शून्य;
पूर्ण

/**
 * eeh_pe_get - Search PE based on the given address
 * @phb: PCI controller
 * @pe_no: PE number
 *
 * Search the corresponding PE based on the specअगरied address which
 * is included in the eeh device. The function is used to check अगर
 * the associated PE has been created against the PE address. It's
 * notable that the PE address has 2 क्रमmat: traditional PE address
 * which is composed of PCI bus/device/function number, or unअगरied
 * PE address.
 */
काष्ठा eeh_pe *eeh_pe_get(काष्ठा pci_controller *phb, पूर्णांक pe_no)
अणु
	काष्ठा eeh_pe *root = eeh_phb_pe_get(phb);

	वापस eeh_pe_traverse(root, __eeh_pe_get, &pe_no);
पूर्ण

/**
 * eeh_pe_tree_insert - Add EEH device to parent PE
 * @edev: EEH device
 * @new_pe_parent: PE to create additional PEs under
 *
 * Add EEH device to the PE in edev->pe_config_addr. If a PE alपढ़ोy
 * exists with that address then @edev is added to that PE. Otherwise
 * a new PE is created and inserted पूर्णांकo the PE tree as a child of
 * @new_pe_parent.
 *
 * If @new_pe_parent is शून्य then the new PE will be inserted under
 * directly under the the PHB.
 */
पूर्णांक eeh_pe_tree_insert(काष्ठा eeh_dev *edev, काष्ठा eeh_pe *new_pe_parent)
अणु
	काष्ठा pci_controller *hose = edev->controller;
	काष्ठा eeh_pe *pe, *parent;

	/*
	 * Search the PE has been existing or not according
	 * to the PE address. If that has been existing, the
	 * PE should be composed of PCI bus and its subordinate
	 * components.
	 */
	pe = eeh_pe_get(hose, edev->pe_config_addr);
	अगर (pe) अणु
		अगर (pe->type & EEH_PE_INVALID) अणु
			list_add_tail(&edev->entry, &pe->edevs);
			edev->pe = pe;
			/*
			 * We're running to here because of PCI hotplug caused by
			 * EEH recovery. We need clear EEH_PE_INVALID until the top.
			 */
			parent = pe;
			जबतक (parent) अणु
				अगर (!(parent->type & EEH_PE_INVALID))
					अवरोध;
				parent->type &= ~EEH_PE_INVALID;
				parent = parent->parent;
			पूर्ण

			eeh_edev_dbg(edev, "Added to existing PE (parent: PE#%x)\n",
				     pe->parent->addr);
		पूर्ण अन्यथा अणु
			/* Mark the PE as type of PCI bus */
			pe->type = EEH_PE_BUS;
			edev->pe = pe;

			/* Put the edev to PE */
			list_add_tail(&edev->entry, &pe->edevs);
			eeh_edev_dbg(edev, "Added to bus PE\n");
		पूर्ण
		वापस 0;
	पूर्ण

	/* Create a new EEH PE */
	अगर (edev->physfn)
		pe = eeh_pe_alloc(hose, EEH_PE_VF);
	अन्यथा
		pe = eeh_pe_alloc(hose, EEH_PE_DEVICE);
	अगर (!pe) अणु
		pr_err("%s: out of memory!\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	pe->addr = edev->pe_config_addr;

	/*
	 * Put the new EEH PE पूर्णांकo hierarchy tree. If the parent
	 * can't be found, the newly created PE will be attached
	 * to PHB directly. Otherwise, we have to associate the
	 * PE with its parent.
	 */
	अगर (!new_pe_parent) अणु
		new_pe_parent = eeh_phb_pe_get(hose);
		अगर (!new_pe_parent) अणु
			pr_err("%s: No PHB PE is found (PHB Domain=%d)\n",
				__func__, hose->global_number);
			edev->pe = शून्य;
			kमुक्त(pe);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	/* link new PE पूर्णांकo the tree */
	pe->parent = new_pe_parent;
	list_add_tail(&pe->child, &new_pe_parent->child_list);

	/*
	 * Put the newly created PE पूर्णांकo the child list and
	 * link the EEH device accordingly.
	 */
	list_add_tail(&edev->entry, &pe->edevs);
	edev->pe = pe;
	eeh_edev_dbg(edev, "Added to new (parent: PE#%x)\n",
		     new_pe_parent->addr);

	वापस 0;
पूर्ण

/**
 * eeh_pe_tree_हटाओ - Remove one EEH device from the associated PE
 * @edev: EEH device
 *
 * The PE hierarchy tree might be changed when करोing PCI hotplug.
 * Also, the PCI devices or buses could be हटाओd from the प्रणाली
 * during EEH recovery. So we have to call the function हटाओ the
 * corresponding PE accordingly अगर necessary.
 */
पूर्णांक eeh_pe_tree_हटाओ(काष्ठा eeh_dev *edev)
अणु
	काष्ठा eeh_pe *pe, *parent, *child;
	bool keep, recover;
	पूर्णांक cnt;

	pe = eeh_dev_to_pe(edev);
	अगर (!pe) अणु
		eeh_edev_dbg(edev, "No PE found for device.\n");
		वापस -EEXIST;
	पूर्ण

	/* Remove the EEH device */
	edev->pe = शून्य;
	list_del(&edev->entry);

	/*
	 * Check अगर the parent PE includes any EEH devices.
	 * If not, we should delete that. Also, we should
	 * delete the parent PE अगर it करोesn't have associated
	 * child PEs and EEH devices.
	 */
	जबतक (1) अणु
		parent = pe->parent;

		/* PHB PEs should never be हटाओd */
		अगर (pe->type & EEH_PE_PHB)
			अवरोध;

		/*
		 * XXX: KEEP is set जबतक resetting a PE. I करोn't think it's
		 * ever set without RECOVERING also being set. I could
		 * be wrong though so catch that with a WARN.
		 */
		keep = !!(pe->state & EEH_PE_KEEP);
		recover = !!(pe->state & EEH_PE_RECOVERING);
		WARN_ON(keep && !recover);

		अगर (!keep && !recover) अणु
			अगर (list_empty(&pe->edevs) &&
			    list_empty(&pe->child_list)) अणु
				list_del(&pe->child);
				kमुक्त(pe);
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Mark the PE as invalid. At the end of the recovery
			 * process any invalid PEs will be garbage collected.
			 *
			 * We need to delay the मुक्त()ing of them since we can
			 * हटाओ edev's जबतक traversing the PE tree which
			 * might trigger the removal of a PE and we can't
			 * deal with that (yet).
			 */
			अगर (list_empty(&pe->edevs)) अणु
				cnt = 0;
				list_क्रम_each_entry(child, &pe->child_list, child) अणु
					अगर (!(child->type & EEH_PE_INVALID)) अणु
						cnt++;
						अवरोध;
					पूर्ण
				पूर्ण

				अगर (!cnt)
					pe->type |= EEH_PE_INVALID;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण

		pe = parent;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * eeh_pe_update_समय_stamp - Update PE's frozen समय stamp
 * @pe: EEH PE
 *
 * We have समय stamp क्रम each PE to trace its समय of getting
 * frozen in last hour. The function should be called to update
 * the समय stamp on first error of the specअगरic PE. On the other
 * handle, we needn't account क्रम errors happened in last hour.
 */
व्योम eeh_pe_update_समय_stamp(काष्ठा eeh_pe *pe)
अणु
	समय64_t tstamp;

	अगर (!pe) वापस;

	अगर (pe->मुक्तze_count <= 0) अणु
		pe->मुक्तze_count = 0;
		pe->tstamp = kसमय_get_seconds();
	पूर्ण अन्यथा अणु
		tstamp = kसमय_get_seconds();
		अगर (tstamp - pe->tstamp > 3600) अणु
			pe->tstamp = tstamp;
			pe->मुक्तze_count = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * eeh_pe_state_mark - Mark specअगरied state क्रम PE and its associated device
 * @pe: EEH PE
 *
 * EEH error affects the current PE and its child PEs. The function
 * is used to mark appropriate state क्रम the affected PEs and the
 * associated devices.
 */
व्योम eeh_pe_state_mark(काष्ठा eeh_pe *root, पूर्णांक state)
अणु
	काष्ठा eeh_pe *pe;

	eeh_क्रम_each_pe(root, pe)
		अगर (!(pe->state & EEH_PE_REMOVED))
			pe->state |= state;
पूर्ण
EXPORT_SYMBOL_GPL(eeh_pe_state_mark);

/**
 * eeh_pe_mark_isolated
 * @pe: EEH PE
 *
 * Record that a PE has been isolated by marking the PE and it's children as
 * EEH_PE_ISOLATED (and EEH_PE_CFG_BLOCKED, अगर required) and their PCI devices
 * as pci_channel_io_frozen.
 */
व्योम eeh_pe_mark_isolated(काष्ठा eeh_pe *root)
अणु
	काष्ठा eeh_pe *pe;
	काष्ठा eeh_dev *edev;
	काष्ठा pci_dev *pdev;

	eeh_pe_state_mark(root, EEH_PE_ISOLATED);
	eeh_क्रम_each_pe(root, pe) अणु
		list_क्रम_each_entry(edev, &pe->edevs, entry) अणु
			pdev = eeh_dev_to_pci_dev(edev);
			अगर (pdev)
				pdev->error_state = pci_channel_io_frozen;
		पूर्ण
		/* Block PCI config access अगर required */
		अगर (pe->state & EEH_PE_CFG_RESTRICTED)
			pe->state |= EEH_PE_CFG_BLOCKED;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(eeh_pe_mark_isolated);

अटल व्योम __eeh_pe_dev_mode_mark(काष्ठा eeh_dev *edev, व्योम *flag)
अणु
	पूर्णांक mode = *((पूर्णांक *)flag);

	edev->mode |= mode;
पूर्ण

/**
 * eeh_pe_dev_state_mark - Mark state क्रम all device under the PE
 * @pe: EEH PE
 *
 * Mark specअगरic state क्रम all child devices of the PE.
 */
व्योम eeh_pe_dev_mode_mark(काष्ठा eeh_pe *pe, पूर्णांक mode)
अणु
	eeh_pe_dev_traverse(pe, __eeh_pe_dev_mode_mark, &mode);
पूर्ण

/**
 * eeh_pe_state_clear - Clear state क्रम the PE
 * @data: EEH PE
 * @state: state
 * @include_passed: include passed-through devices?
 *
 * The function is used to clear the indicated state from the
 * given PE. Besides, we also clear the check count of the PE
 * as well.
 */
व्योम eeh_pe_state_clear(काष्ठा eeh_pe *root, पूर्णांक state, bool include_passed)
अणु
	काष्ठा eeh_pe *pe;
	काष्ठा eeh_dev *edev, *पंचांगp;
	काष्ठा pci_dev *pdev;

	eeh_क्रम_each_pe(root, pe) अणु
		/* Keep the state of permanently हटाओd PE पूर्णांकact */
		अगर (pe->state & EEH_PE_REMOVED)
			जारी;

		अगर (!include_passed && eeh_pe_passed(pe))
			जारी;

		pe->state &= ~state;

		/*
		 * Special treaपंचांगent on clearing isolated state. Clear
		 * check count since last isolation and put all affected
		 * devices to normal state.
		 */
		अगर (!(state & EEH_PE_ISOLATED))
			जारी;

		pe->check_count = 0;
		eeh_pe_क्रम_each_dev(pe, edev, पंचांगp) अणु
			pdev = eeh_dev_to_pci_dev(edev);
			अगर (!pdev)
				जारी;

			pdev->error_state = pci_channel_io_normal;
		पूर्ण

		/* Unblock PCI config access अगर required */
		अगर (pe->state & EEH_PE_CFG_RESTRICTED)
			pe->state &= ~EEH_PE_CFG_BLOCKED;
	पूर्ण
पूर्ण

/*
 * Some PCI bridges (e.g. PLX bridges) have primary/secondary
 * buses asचिन्हित explicitly by firmware, and we probably have
 * lost that after reset. So we have to delay the check until
 * the PCI-CFG रेजिस्टरs have been restored क्रम the parent
 * bridge.
 *
 * Don't use normal PCI-CFG accessors, which probably has been
 * blocked on normal path during the stage. So we need utilize
 * eeh operations, which is always permitted.
 */
अटल व्योम eeh_bridge_check_link(काष्ठा eeh_dev *edev)
अणु
	पूर्णांक cap;
	uपूर्णांक32_t val;
	पूर्णांक समयout = 0;

	/*
	 * We only check root port and करोwnstream ports of
	 * PCIe चयनes
	 */
	अगर (!(edev->mode & (EEH_DEV_ROOT_PORT | EEH_DEV_DS_PORT)))
		वापस;

	eeh_edev_dbg(edev, "Checking PCIe link...\n");

	/* Check slot status */
	cap = edev->pcie_cap;
	eeh_ops->पढ़ो_config(edev, cap + PCI_EXP_SLTSTA, 2, &val);
	अगर (!(val & PCI_EXP_SLTSTA_PDS)) अणु
		eeh_edev_dbg(edev, "No card in the slot (0x%04x) !\n", val);
		वापस;
	पूर्ण

	/* Check घातer status अगर we have the capability */
	eeh_ops->पढ़ो_config(edev, cap + PCI_EXP_SLTCAP, 2, &val);
	अगर (val & PCI_EXP_SLTCAP_PCP) अणु
		eeh_ops->पढ़ो_config(edev, cap + PCI_EXP_SLTCTL, 2, &val);
		अगर (val & PCI_EXP_SLTCTL_PCC) अणु
			eeh_edev_dbg(edev, "In power-off state, power it on ...\n");
			val &= ~(PCI_EXP_SLTCTL_PCC | PCI_EXP_SLTCTL_PIC);
			val |= (0x0100 & PCI_EXP_SLTCTL_PIC);
			eeh_ops->ग_लिखो_config(edev, cap + PCI_EXP_SLTCTL, 2, val);
			msleep(2 * 1000);
		पूर्ण
	पूर्ण

	/* Enable link */
	eeh_ops->पढ़ो_config(edev, cap + PCI_EXP_LNKCTL, 2, &val);
	val &= ~PCI_EXP_LNKCTL_LD;
	eeh_ops->ग_लिखो_config(edev, cap + PCI_EXP_LNKCTL, 2, val);

	/* Check link */
	eeh_ops->पढ़ो_config(edev, cap + PCI_EXP_LNKCAP, 4, &val);
	अगर (!(val & PCI_EXP_LNKCAP_DLLLARC)) अणु
		eeh_edev_dbg(edev, "No link reporting capability (0x%08x) \n", val);
		msleep(1000);
		वापस;
	पूर्ण

	/* Wait the link is up until समयout (5s) */
	समयout = 0;
	जबतक (समयout < 5000) अणु
		msleep(20);
		समयout += 20;

		eeh_ops->पढ़ो_config(edev, cap + PCI_EXP_LNKSTA, 2, &val);
		अगर (val & PCI_EXP_LNKSTA_DLLLA)
			अवरोध;
	पूर्ण

	अगर (val & PCI_EXP_LNKSTA_DLLLA)
		eeh_edev_dbg(edev, "Link up (%s)\n",
			 (val & PCI_EXP_LNKSTA_CLS_2_5GB) ? "2.5GB" : "5GB");
	अन्यथा
		eeh_edev_dbg(edev, "Link not ready (0x%04x)\n", val);
पूर्ण

#घोषणा BYTE_SWAP(OFF)	(8*((OFF)/4)+3-(OFF))
#घोषणा SAVED_BYTE(OFF)	(((u8 *)(edev->config_space))[BYTE_SWAP(OFF)])

अटल व्योम eeh_restore_bridge_bars(काष्ठा eeh_dev *edev)
अणु
	पूर्णांक i;

	/*
	 * Device BARs: 0x10 - 0x18
	 * Bus numbers and winकरोws: 0x18 - 0x30
	 */
	क्रम (i = 4; i < 13; i++)
		eeh_ops->ग_लिखो_config(edev, i*4, 4, edev->config_space[i]);
	/* Rom: 0x38 */
	eeh_ops->ग_लिखो_config(edev, 14*4, 4, edev->config_space[14]);

	/* Cache line & Latency समयr: 0xC 0xD */
	eeh_ops->ग_लिखो_config(edev, PCI_CACHE_LINE_SIZE, 1,
                SAVED_BYTE(PCI_CACHE_LINE_SIZE));
	eeh_ops->ग_लिखो_config(edev, PCI_LATENCY_TIMER, 1,
		SAVED_BYTE(PCI_LATENCY_TIMER));
	/* Max latency, min grant, पूर्णांकerrupt ping and line: 0x3C */
	eeh_ops->ग_लिखो_config(edev, 15*4, 4, edev->config_space[15]);

	/* PCI Command: 0x4 */
	eeh_ops->ग_लिखो_config(edev, PCI_COMMAND, 4, edev->config_space[1] |
			      PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);

	/* Check the PCIe link is पढ़ोy */
	eeh_bridge_check_link(edev);
पूर्ण

अटल व्योम eeh_restore_device_bars(काष्ठा eeh_dev *edev)
अणु
	पूर्णांक i;
	u32 cmd;

	क्रम (i = 4; i < 10; i++)
		eeh_ops->ग_लिखो_config(edev, i*4, 4, edev->config_space[i]);
	/* 12 == Expansion ROM Address */
	eeh_ops->ग_लिखो_config(edev, 12*4, 4, edev->config_space[12]);

	eeh_ops->ग_लिखो_config(edev, PCI_CACHE_LINE_SIZE, 1,
		SAVED_BYTE(PCI_CACHE_LINE_SIZE));
	eeh_ops->ग_लिखो_config(edev, PCI_LATENCY_TIMER, 1,
		SAVED_BYTE(PCI_LATENCY_TIMER));

	/* max latency, min grant, पूर्णांकerrupt pin and line */
	eeh_ops->ग_लिखो_config(edev, 15*4, 4, edev->config_space[15]);

	/*
	 * Restore PERR & SERR bits, some devices require it,
	 * करोn't touch the other command bits
	 */
	eeh_ops->पढ़ो_config(edev, PCI_COMMAND, 4, &cmd);
	अगर (edev->config_space[1] & PCI_COMMAND_PARITY)
		cmd |= PCI_COMMAND_PARITY;
	अन्यथा
		cmd &= ~PCI_COMMAND_PARITY;
	अगर (edev->config_space[1] & PCI_COMMAND_SERR)
		cmd |= PCI_COMMAND_SERR;
	अन्यथा
		cmd &= ~PCI_COMMAND_SERR;
	eeh_ops->ग_लिखो_config(edev, PCI_COMMAND, 4, cmd);
पूर्ण

/**
 * eeh_restore_one_device_bars - Restore the Base Address Registers क्रम one device
 * @data: EEH device
 * @flag: Unused
 *
 * Loads the PCI configuration space base address रेजिस्टरs,
 * the expansion ROM base address, the latency समयr, and etc.
 * from the saved values in the device node.
 */
अटल व्योम eeh_restore_one_device_bars(काष्ठा eeh_dev *edev, व्योम *flag)
अणु
	/* Do special restore क्रम bridges */
	अगर (edev->mode & EEH_DEV_BRIDGE)
		eeh_restore_bridge_bars(edev);
	अन्यथा
		eeh_restore_device_bars(edev);

	अगर (eeh_ops->restore_config)
		eeh_ops->restore_config(edev);
पूर्ण

/**
 * eeh_pe_restore_bars - Restore the PCI config space info
 * @pe: EEH PE
 *
 * This routine perक्रमms a recursive walk to the children
 * of this device as well.
 */
व्योम eeh_pe_restore_bars(काष्ठा eeh_pe *pe)
अणु
	/*
	 * We needn't take the EEH lock since eeh_pe_dev_traverse()
	 * will take that.
	 */
	eeh_pe_dev_traverse(pe, eeh_restore_one_device_bars, शून्य);
पूर्ण

/**
 * eeh_pe_loc_get - Retrieve location code binding to the given PE
 * @pe: EEH PE
 *
 * Retrieve the location code of the given PE. If the primary PE bus
 * is root bus, we will grab location code from PHB device tree node
 * or root port. Otherwise, the upstream bridge's device tree node
 * of the primary PE bus will be checked क्रम the location code.
 */
स्थिर अक्षर *eeh_pe_loc_get(काष्ठा eeh_pe *pe)
अणु
	काष्ठा pci_bus *bus = eeh_pe_bus_get(pe);
	काष्ठा device_node *dn;
	स्थिर अक्षर *loc = शून्य;

	जबतक (bus) अणु
		dn = pci_bus_to_OF_node(bus);
		अगर (!dn) अणु
			bus = bus->parent;
			जारी;
		पूर्ण

		अगर (pci_is_root_bus(bus))
			loc = of_get_property(dn, "ibm,io-base-loc-code", शून्य);
		अन्यथा
			loc = of_get_property(dn, "ibm,slot-location-code",
					      शून्य);

		अगर (loc)
			वापस loc;

		bus = bus->parent;
	पूर्ण

	वापस "N/A";
पूर्ण

/**
 * eeh_pe_bus_get - Retrieve PCI bus according to the given PE
 * @pe: EEH PE
 *
 * Retrieve the PCI bus according to the given PE. Basically,
 * there're 3 types of PEs: PHB/Bus/Device. For PHB PE, the
 * primary PCI bus will be retrieved. The parent bus will be
 * वापसed क्रम BUS PE. However, we करोn't have associated PCI
 * bus क्रम DEVICE PE.
 */
काष्ठा pci_bus *eeh_pe_bus_get(काष्ठा eeh_pe *pe)
अणु
	काष्ठा eeh_dev *edev;
	काष्ठा pci_dev *pdev;

	अगर (pe->type & EEH_PE_PHB)
		वापस pe->phb->bus;

	/* The primary bus might be cached during probe समय */
	अगर (pe->state & EEH_PE_PRI_BUS)
		वापस pe->bus;

	/* Retrieve the parent PCI bus of first (top) PCI device */
	edev = list_first_entry_or_null(&pe->edevs, काष्ठा eeh_dev, entry);
	pdev = eeh_dev_to_pci_dev(edev);
	अगर (pdev)
		वापस pdev->bus;

	वापस शून्य;
पूर्ण
