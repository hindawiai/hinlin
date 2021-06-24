<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The file पूर्णांकends to implement the platक्रमm dependent EEH operations on pseries.
 * Actually, the pseries platक्रमm is built based on RTAS heavily. That means the
 * pseries platक्रमm dependent EEH operations will be built on RTAS calls. The functions
 * are derived from arch/घातerpc/platक्रमms/pseries/eeh.c and necessary cleanup has
 * been करोne.
 *
 * Copyright Benjamin Herrenschmidt & Gavin Shan, IBM Corporation 2011.
 * Copyright IBM Corporation 2001, 2005, 2006
 * Copyright Dave Engebretsen & Todd Inglett 2001
 * Copyright Linas Vepstas 2005, 2006
 */

#समावेश <linux/atomic.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/eeh_event.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/rtas.h>

/* RTAS tokens */
अटल पूर्णांक ibm_set_eeh_option;
अटल पूर्णांक ibm_set_slot_reset;
अटल पूर्णांक ibm_पढ़ो_slot_reset_state;
अटल पूर्णांक ibm_पढ़ो_slot_reset_state2;
अटल पूर्णांक ibm_slot_error_detail;
अटल पूर्णांक ibm_get_config_addr_info;
अटल पूर्णांक ibm_get_config_addr_info2;
अटल पूर्णांक ibm_configure_pe;

अटल व्योम pseries_pcibios_bus_add_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn *pdn = pci_get_pdn(pdev);

	अगर (eeh_has_flag(EEH_FORCE_DISABLED))
		वापस;

	dev_dbg(&pdev->dev, "EEH: Setting up device\n");
#अगर_घोषित CONFIG_PCI_IOV
	अगर (pdev->is_virtfn) अणु
		pdn->device_id  =  pdev->device;
		pdn->venकरोr_id  =  pdev->venकरोr;
		pdn->class_code =  pdev->class;
		/*
		 * Last allow unमुक्तze वापस code used क्रम retrieval
		 * by user space in eeh-sysfs to show the last command
		 * completion from platक्रमm.
		 */
		pdn->last_allow_rc =  0;
	पूर्ण
#पूर्ण_अगर
	pseries_eeh_init_edev(pdn);
#अगर_घोषित CONFIG_PCI_IOV
	अगर (pdev->is_virtfn) अणु
		/*
		 * FIXME: This really should be handled by choosing the right
		 *        parent PE in in pseries_eeh_init_edev().
		 */
		काष्ठा eeh_pe *physfn_pe = pci_dev_to_eeh_dev(pdev->physfn)->pe;
		काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);

		edev->pe_config_addr =  (pdn->busno << 16) | (pdn->devfn << 8);
		eeh_pe_tree_हटाओ(edev); /* Remove as it is adding to bus pe */
		eeh_pe_tree_insert(edev, physfn_pe);   /* Add as VF PE type */
	पूर्ण
#पूर्ण_अगर
	eeh_probe_device(pdev);
पूर्ण


/**
 * pseries_eeh_get_pe_config_addr - Find the pe_config_addr क्रम a device
 * @pdn: pci_dn of the input device
 *
 * The EEH RTAS calls use a tuple consisting of: (buid_hi, buid_lo,
 * pe_config_addr) as a handle to a given PE. This function finds the
 * pe_config_addr based on the device's config addr.
 *
 * Keep in mind that the pe_config_addr *might* be numerically identical to the
 * device's config addr, but the two are conceptually distinct.
 *
 * Returns the pe_config_addr, or a negative error code.
 */
अटल पूर्णांक pseries_eeh_get_pe_config_addr(काष्ठा pci_dn *pdn)
अणु
	पूर्णांक config_addr = rtas_config_addr(pdn->busno, pdn->devfn, 0);
	काष्ठा pci_controller *phb = pdn->phb;
	पूर्णांक ret, rets[3];

	अगर (ibm_get_config_addr_info2 != RTAS_UNKNOWN_SERVICE) अणु
		/*
		 * First of all, use function 1 to determine अगर this device is
		 * part of a PE or not. ret[0] being zero indicates it's not.
		 */
		ret = rtas_call(ibm_get_config_addr_info2, 4, 2, rets,
				config_addr, BUID_HI(phb->buid),
				BUID_LO(phb->buid), 1);
		अगर (ret || (rets[0] == 0))
			वापस -ENOENT;

		/* Retrieve the associated PE config address with function 0 */
		ret = rtas_call(ibm_get_config_addr_info2, 4, 2, rets,
				config_addr, BUID_HI(phb->buid),
				BUID_LO(phb->buid), 0);
		अगर (ret) अणु
			pr_warn("%s: Failed to get address for PHB#%x-PE#%x\n",
				__func__, phb->global_number, config_addr);
			वापस -ENXIO;
		पूर्ण

		वापस rets[0];
	पूर्ण

	अगर (ibm_get_config_addr_info != RTAS_UNKNOWN_SERVICE) अणु
		ret = rtas_call(ibm_get_config_addr_info, 4, 2, rets,
				config_addr, BUID_HI(phb->buid),
				BUID_LO(phb->buid), 0);
		अगर (ret) अणु
			pr_warn("%s: Failed to get address for PHB#%x-PE#%x\n",
				__func__, phb->global_number, config_addr);
			वापस -ENXIO;
		पूर्ण

		वापस rets[0];
	पूर्ण

	/*
	 * PAPR करोes describe a process क्रम finding the pe_config_addr that was
	 * used beक्रमe the ibm,get-config-addr-info calls were added. However,
	 * I haven't found *any* systems that don't have that RTAS call
	 * implemented. If you happen to find one that needs the old DT based
	 * process, patches are welcome!
	 */
	वापस -ENOENT;
पूर्ण

/**
 * pseries_eeh_phb_reset - Reset the specअगरied PHB
 * @phb: PCI controller
 * @config_adddr: the associated config address
 * @option: reset option
 *
 * Reset the specअगरied PHB/PE
 */
अटल पूर्णांक pseries_eeh_phb_reset(काष्ठा pci_controller *phb, पूर्णांक config_addr, पूर्णांक option)
अणु
	पूर्णांक ret;

	/* Reset PE through RTAS call */
	ret = rtas_call(ibm_set_slot_reset, 4, 1, शून्य,
			config_addr, BUID_HI(phb->buid),
			BUID_LO(phb->buid), option);

	/* If fundamental-reset not supported, try hot-reset */
	अगर (option == EEH_RESET_FUNDAMENTAL && ret == -8) अणु
		option = EEH_RESET_HOT;
		ret = rtas_call(ibm_set_slot_reset, 4, 1, शून्य,
				config_addr, BUID_HI(phb->buid),
				BUID_LO(phb->buid), option);
	पूर्ण

	/* We need reset hold or settlement delay */
	अगर (option == EEH_RESET_FUNDAMENTAL || option == EEH_RESET_HOT)
		msleep(EEH_PE_RST_HOLD_TIME);
	अन्यथा
		msleep(EEH_PE_RST_SETTLE_TIME);

	वापस ret;
पूर्ण

/**
 * pseries_eeh_phb_configure_bridge - Configure PCI bridges in the indicated PE
 * @phb: PCI controller
 * @config_adddr: the associated config address
 *
 * The function will be called to reconfigure the bridges included
 * in the specअगरied PE so that the mulfunctional PE would be recovered
 * again.
 */
अटल पूर्णांक pseries_eeh_phb_configure_bridge(काष्ठा pci_controller *phb, पूर्णांक config_addr)
अणु
	पूर्णांक ret;
	/* Waiting 0.2s maximum beक्रमe skipping configuration */
	पूर्णांक max_रुको = 200;

	जबतक (max_रुको > 0) अणु
		ret = rtas_call(ibm_configure_pe, 3, 1, शून्य,
				config_addr, BUID_HI(phb->buid),
				BUID_LO(phb->buid));

		अगर (!ret)
			वापस ret;
		अगर (ret < 0)
			अवरोध;

		/*
		 * If RTAS वापसs a delay value that's above 100ms, cut it
		 * करोwn to 100ms in हाल firmware made a mistake.  For more
		 * on how these delay values work see rtas_busy_delay_समय
		 */
		अगर (ret > RTAS_EXTENDED_DELAY_MIN+2 &&
		    ret <= RTAS_EXTENDED_DELAY_MAX)
			ret = RTAS_EXTENDED_DELAY_MIN+2;

		max_रुको -= rtas_busy_delay_समय(ret);

		अगर (max_रुको < 0)
			अवरोध;

		rtas_busy_delay(ret);
	पूर्ण

	pr_warn("%s: Unable to configure bridge PHB#%x-PE#%x (%d)\n",
		__func__, phb->global_number, config_addr, ret);
	/* PAPR defines -3 as "Parameter Error" क्रम this function: */
	अगर (ret == -3)
		वापस -EINVAL;
	अन्यथा
		वापस -EIO;
पूर्ण

/*
 * Buffer क्रम reporting slot-error-detail rtas calls. Its here
 * in BSS, and not dynamically alloced, so that it ends up in
 * RMO where RTAS can access it.
 */
अटल अचिन्हित अक्षर slot_errbuf[RTAS_ERROR_LOG_MAX];
अटल DEFINE_SPINLOCK(slot_errbuf_lock);
अटल पूर्णांक eeh_error_buf_size;

अटल पूर्णांक pseries_eeh_cap_start(काष्ठा pci_dn *pdn)
अणु
	u32 status;

	अगर (!pdn)
		वापस 0;

	rtas_पढ़ो_config(pdn, PCI_STATUS, 2, &status);
	अगर (!(status & PCI_STATUS_CAP_LIST))
		वापस 0;

	वापस PCI_CAPABILITY_LIST;
पूर्ण


अटल पूर्णांक pseries_eeh_find_cap(काष्ठा pci_dn *pdn, पूर्णांक cap)
अणु
	पूर्णांक pos = pseries_eeh_cap_start(pdn);
	पूर्णांक cnt = 48;	/* Maximal number of capabilities */
	u32 id;

	अगर (!pos)
		वापस 0;

        जबतक (cnt--) अणु
		rtas_पढ़ो_config(pdn, pos, 1, &pos);
		अगर (pos < 0x40)
			अवरोध;
		pos &= ~3;
		rtas_पढ़ो_config(pdn, pos + PCI_CAP_LIST_ID, 1, &id);
		अगर (id == 0xff)
			अवरोध;
		अगर (id == cap)
			वापस pos;
		pos += PCI_CAP_LIST_NEXT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pseries_eeh_find_ecap(काष्ठा pci_dn *pdn, पूर्णांक cap)
अणु
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);
	u32 header;
	पूर्णांक pos = 256;
	पूर्णांक ttl = (4096 - 256) / 8;

	अगर (!edev || !edev->pcie_cap)
		वापस 0;
	अगर (rtas_पढ़ो_config(pdn, pos, 4, &header) != PCIBIOS_SUCCESSFUL)
		वापस 0;
	अन्यथा अगर (!header)
		वापस 0;

	जबतक (ttl-- > 0) अणु
		अगर (PCI_EXT_CAP_ID(header) == cap && pos)
			वापस pos;

		pos = PCI_EXT_CAP_NEXT(header);
		अगर (pos < 256)
			अवरोध;

		अगर (rtas_पढ़ो_config(pdn, pos, 4, &header) != PCIBIOS_SUCCESSFUL)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pseries_eeh_pe_get_parent - Retrieve the parent PE
 * @edev: EEH device
 *
 * The whole PEs existing in the प्रणाली are organized as hierarchy
 * tree. The function is used to retrieve the parent PE according
 * to the parent EEH device.
 */
अटल काष्ठा eeh_pe *pseries_eeh_pe_get_parent(काष्ठा eeh_dev *edev)
अणु
	काष्ठा eeh_dev *parent;
	काष्ठा pci_dn *pdn = eeh_dev_to_pdn(edev);

	/*
	 * It might have the हाल क्रम the indirect parent
	 * EEH device alपढ़ोy having associated PE, but
	 * the direct parent EEH device करोesn't have yet.
	 */
	अगर (edev->physfn)
		pdn = pci_get_pdn(edev->physfn);
	अन्यथा
		pdn = pdn ? pdn->parent : शून्य;
	जबतक (pdn) अणु
		/* We're poking out of PCI territory */
		parent = pdn_to_eeh_dev(pdn);
		अगर (!parent)
			वापस शून्य;

		अगर (parent->pe)
			वापस parent->pe;

		pdn = pdn->parent;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * pseries_eeh_init_edev - initialise the eeh_dev and eeh_pe क्रम a pci_dn
 *
 * @pdn: PCI device node
 *
 * When we discover a new PCI device via the device-tree we create a
 * corresponding pci_dn and we allocate, but करोn't initialise, an eeh_dev.
 * This function takes care of the initialisation and inserts the eeh_dev
 * पूर्णांकo the correct eeh_pe. If no eeh_pe exists we'll allocate one.
 */
व्योम pseries_eeh_init_edev(काष्ठा pci_dn *pdn)
अणु
	काष्ठा eeh_pe pe, *parent;
	काष्ठा eeh_dev *edev;
	u32 pcie_flags;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(!eeh_has_flag(EEH_PROBE_MODE_DEVTREE)))
		वापस;

	/*
	 * Find the eeh_dev क्रम this pdn. The storage क्रम the eeh_dev was
	 * allocated at the same समय as the pci_dn.
	 *
	 * XXX: We should probably re-visit that.
	 */
	edev = pdn_to_eeh_dev(pdn);
	अगर (!edev)
		वापस;

	/*
	 * If ->pe is set then we've alपढ़ोy probed this device. We hit
	 * this path when a pci_dev is हटाओd and rescanned जबतक recovering
	 * a PE (i.e. क्रम devices where the driver करोesn't support error
	 * recovery).
	 */
	अगर (edev->pe)
		वापस;

	/* Check class/venकरोr/device IDs */
	अगर (!pdn->venकरोr_id || !pdn->device_id || !pdn->class_code)
		वापस;

	/* Skip क्रम PCI-ISA bridge */
        अगर ((pdn->class_code >> 8) == PCI_CLASS_BRIDGE_ISA)
		वापस;

	eeh_edev_dbg(edev, "Probing device\n");

	/*
	 * Update class code and mode of eeh device. We need
	 * correctly reflects that current device is root port
	 * or PCIe चयन करोwnstream port.
	 */
	edev->pcix_cap = pseries_eeh_find_cap(pdn, PCI_CAP_ID_PCIX);
	edev->pcie_cap = pseries_eeh_find_cap(pdn, PCI_CAP_ID_EXP);
	edev->aer_cap = pseries_eeh_find_ecap(pdn, PCI_EXT_CAP_ID_ERR);
	edev->mode &= 0xFFFFFF00;
	अगर ((pdn->class_code >> 8) == PCI_CLASS_BRIDGE_PCI) अणु
		edev->mode |= EEH_DEV_BRIDGE;
		अगर (edev->pcie_cap) अणु
			rtas_पढ़ो_config(pdn, edev->pcie_cap + PCI_EXP_FLAGS,
					 2, &pcie_flags);
			pcie_flags = (pcie_flags & PCI_EXP_FLAGS_TYPE) >> 4;
			अगर (pcie_flags == PCI_EXP_TYPE_ROOT_PORT)
				edev->mode |= EEH_DEV_ROOT_PORT;
			अन्यथा अगर (pcie_flags == PCI_EXP_TYPE_DOWNSTREAM)
				edev->mode |= EEH_DEV_DS_PORT;
		पूर्ण
	पूर्ण

	/* first up, find the pe_config_addr क्रम the PE containing the device */
	ret = pseries_eeh_get_pe_config_addr(pdn);
	अगर (ret < 0) अणु
		eeh_edev_dbg(edev, "Unable to find pe_config_addr\n");
		जाओ err;
	पूर्ण

	/* Try enable EEH on the fake PE */
	स_रखो(&pe, 0, माप(काष्ठा eeh_pe));
	pe.phb = pdn->phb;
	pe.addr = ret;

	eeh_edev_dbg(edev, "Enabling EEH on device\n");
	ret = eeh_ops->set_option(&pe, EEH_OPT_ENABLE);
	अगर (ret) अणु
		eeh_edev_dbg(edev, "EEH failed to enable on device (code %d)\n", ret);
		जाओ err;
	पूर्ण

	edev->pe_config_addr = pe.addr;

	eeh_add_flag(EEH_ENABLED);

	parent = pseries_eeh_pe_get_parent(edev);
	eeh_pe_tree_insert(edev, parent);
	eeh_save_bars(edev);
	eeh_edev_dbg(edev, "EEH enabled for device");

	वापस;

err:
	eeh_edev_dbg(edev, "EEH is unsupported on device (code = %d)\n", ret);
पूर्ण

अटल काष्ठा eeh_dev *pseries_eeh_probe(काष्ठा pci_dev *pdev)
अणु
	काष्ठा eeh_dev *edev;
	काष्ठा pci_dn *pdn;

	pdn = pci_get_pdn_by_devfn(pdev->bus, pdev->devfn);
	अगर (!pdn)
		वापस शून्य;

	/*
	 * If the प्रणाली supports EEH on this device then the eeh_dev was
	 * configured and inserted पूर्णांकo a PE in pseries_eeh_init_edev()
	 */
	edev = pdn_to_eeh_dev(pdn);
	अगर (!edev || !edev->pe)
		वापस शून्य;

	वापस edev;
पूर्ण

/**
 * pseries_eeh_init_edev_recursive - Enable EEH क्रम the indicated device
 * @pdn: PCI device node
 *
 * This routine must be used to perक्रमm EEH initialization क्रम the
 * indicated PCI device that was added after प्रणाली boot (e.g.
 * hotplug, dlpar).
 */
व्योम pseries_eeh_init_edev_recursive(काष्ठा pci_dn *pdn)
अणु
	काष्ठा pci_dn *n;

	अगर (!pdn)
		वापस;

	list_क्रम_each_entry(n, &pdn->child_list, list)
		pseries_eeh_init_edev_recursive(n);

	pseries_eeh_init_edev(pdn);
पूर्ण
EXPORT_SYMBOL_GPL(pseries_eeh_init_edev_recursive);

/**
 * pseries_eeh_set_option - Initialize EEH or MMIO/DMA reenable
 * @pe: EEH PE
 * @option: operation to be issued
 *
 * The function is used to control the EEH functionality globally.
 * Currently, following options are support according to PAPR:
 * Enable EEH, Disable EEH, Enable MMIO and Enable DMA
 */
अटल पूर्णांक pseries_eeh_set_option(काष्ठा eeh_pe *pe, पूर्णांक option)
अणु
	पूर्णांक ret = 0;

	/*
	 * When we're enabling or disabling EEH functioality on
	 * the particular PE, the PE config address is possibly
	 * unavailable. Thereक्रमe, we have to figure it out from
	 * the FDT node.
	 */
	चयन (option) अणु
	हाल EEH_OPT_DISABLE:
	हाल EEH_OPT_ENABLE:
	हाल EEH_OPT_THAW_MMIO:
	हाल EEH_OPT_THAW_DMA:
		अवरोध;
	हाल EEH_OPT_FREEZE_PE:
		/* Not support */
		वापस 0;
	शेष:
		pr_err("%s: Invalid option %d\n", __func__, option);
		वापस -EINVAL;
	पूर्ण

	ret = rtas_call(ibm_set_eeh_option, 4, 1, शून्य,
			pe->addr, BUID_HI(pe->phb->buid),
			BUID_LO(pe->phb->buid), option);

	वापस ret;
पूर्ण

/**
 * pseries_eeh_get_state - Retrieve PE state
 * @pe: EEH PE
 * @delay: suggested समय to रुको अगर state is unavailable
 *
 * Retrieve the state of the specअगरied PE. On RTAS compliant
 * pseries platक्रमm, there alपढ़ोy has one dedicated RTAS function
 * क्रम the purpose. It's notable that the associated PE config address
 * might be पढ़ोy when calling the function. Thereक्रमe, endeavour to
 * use the PE config address अगर possible. Further more, there're 2
 * RTAS calls क्रम the purpose, we need to try the new one and back
 * to the old one अगर the new one couldn't work properly.
 */
अटल पूर्णांक pseries_eeh_get_state(काष्ठा eeh_pe *pe, पूर्णांक *delay)
अणु
	पूर्णांक ret;
	पूर्णांक rets[4];
	पूर्णांक result;

	अगर (ibm_पढ़ो_slot_reset_state2 != RTAS_UNKNOWN_SERVICE) अणु
		ret = rtas_call(ibm_पढ़ो_slot_reset_state2, 3, 4, rets,
				pe->addr, BUID_HI(pe->phb->buid),
				BUID_LO(pe->phb->buid));
	पूर्ण अन्यथा अगर (ibm_पढ़ो_slot_reset_state != RTAS_UNKNOWN_SERVICE) अणु
		/* Fake PE unavailable info */
		rets[2] = 0;
		ret = rtas_call(ibm_पढ़ो_slot_reset_state, 3, 3, rets,
				pe->addr, BUID_HI(pe->phb->buid),
				BUID_LO(pe->phb->buid));
	पूर्ण अन्यथा अणु
		वापस EEH_STATE_NOT_SUPPORT;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* Parse the result out */
	अगर (!rets[1])
		वापस EEH_STATE_NOT_SUPPORT;

	चयन(rets[0]) अणु
	हाल 0:
		result = EEH_STATE_MMIO_ACTIVE |
			 EEH_STATE_DMA_ACTIVE;
		अवरोध;
	हाल 1:
		result = EEH_STATE_RESET_ACTIVE |
			 EEH_STATE_MMIO_ACTIVE  |
			 EEH_STATE_DMA_ACTIVE;
		अवरोध;
	हाल 2:
		result = 0;
		अवरोध;
	हाल 4:
		result = EEH_STATE_MMIO_ENABLED;
		अवरोध;
	हाल 5:
		अगर (rets[2]) अणु
			अगर (delay)
				*delay = rets[2];
			result = EEH_STATE_UNAVAILABLE;
		पूर्ण अन्यथा अणु
			result = EEH_STATE_NOT_SUPPORT;
		पूर्ण
		अवरोध;
	शेष:
		result = EEH_STATE_NOT_SUPPORT;
	पूर्ण

	वापस result;
पूर्ण

/**
 * pseries_eeh_reset - Reset the specअगरied PE
 * @pe: EEH PE
 * @option: reset option
 *
 * Reset the specअगरied PE
 */
अटल पूर्णांक pseries_eeh_reset(काष्ठा eeh_pe *pe, पूर्णांक option)
अणु
	वापस pseries_eeh_phb_reset(pe->phb, pe->addr, option);
पूर्ण

/**
 * pseries_eeh_get_log - Retrieve error log
 * @pe: EEH PE
 * @severity: temporary or permanent error log
 * @drv_log: driver log to be combined with retrieved error log
 * @len: length of driver log
 *
 * Retrieve the temporary or permanent error from the PE.
 * Actually, the error will be retrieved through the dedicated
 * RTAS call.
 */
अटल पूर्णांक pseries_eeh_get_log(काष्ठा eeh_pe *pe, पूर्णांक severity, अक्षर *drv_log, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&slot_errbuf_lock, flags);
	स_रखो(slot_errbuf, 0, eeh_error_buf_size);

	ret = rtas_call(ibm_slot_error_detail, 8, 1, शून्य, pe->addr,
			BUID_HI(pe->phb->buid), BUID_LO(pe->phb->buid),
			virt_to_phys(drv_log), len,
			virt_to_phys(slot_errbuf), eeh_error_buf_size,
			severity);
	अगर (!ret)
		log_error(slot_errbuf, ERR_TYPE_RTAS_LOG, 0);
	spin_unlock_irqrestore(&slot_errbuf_lock, flags);

	वापस ret;
पूर्ण

/**
 * pseries_eeh_configure_bridge - Configure PCI bridges in the indicated PE
 * @pe: EEH PE
 *
 */
अटल पूर्णांक pseries_eeh_configure_bridge(काष्ठा eeh_pe *pe)
अणु
	वापस pseries_eeh_phb_configure_bridge(pe->phb, pe->addr);
पूर्ण

/**
 * pseries_eeh_पढ़ो_config - Read PCI config space
 * @edev: EEH device handle
 * @where: PCI config space offset
 * @size: size to पढ़ो
 * @val: वापस value
 *
 * Read config space from the speicअगरed device
 */
अटल पूर्णांक pseries_eeh_पढ़ो_config(काष्ठा eeh_dev *edev, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_dn *pdn = eeh_dev_to_pdn(edev);

	वापस rtas_पढ़ो_config(pdn, where, size, val);
पूर्ण

/**
 * pseries_eeh_ग_लिखो_config - Write PCI config space
 * @edev: EEH device handle
 * @where: PCI config space offset
 * @size: size to ग_लिखो
 * @val: value to be written
 *
 * Write config space to the specअगरied device
 */
अटल पूर्णांक pseries_eeh_ग_लिखो_config(काष्ठा eeh_dev *edev, पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_dn *pdn = eeh_dev_to_pdn(edev);

	वापस rtas_ग_लिखो_config(pdn, where, size, val);
पूर्ण

#अगर_घोषित CONFIG_PCI_IOV
अटल पूर्णांक pseries_send_allow_unमुक्तze(काष्ठा pci_dn *pdn, u16 *vf_pe_array, पूर्णांक cur_vfs)
अणु
	पूर्णांक rc;
	पूर्णांक ibm_allow_unमुक्तze = rtas_token("ibm,open-sriov-allow-unfreeze");
	अचिन्हित दीर्घ buid, addr;

	addr = rtas_config_addr(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;
	spin_lock(&rtas_data_buf_lock);
	स_नकल(rtas_data_buf, vf_pe_array, RTAS_DATA_BUF_SIZE);
	rc = rtas_call(ibm_allow_unमुक्तze, 5, 1, शून्य,
		       addr,
		       BUID_HI(buid),
		       BUID_LO(buid),
		       rtas_data_buf, cur_vfs * माप(u16));
	spin_unlock(&rtas_data_buf_lock);
	अगर (rc)
		pr_warn("%s: Failed to allow unfreeze for PHB#%x-PE#%lx, rc=%x\n",
			__func__,
			pdn->phb->global_number, addr, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक pseries_call_allow_unमुक्तze(काष्ठा eeh_dev *edev)
अणु
	पूर्णांक cur_vfs = 0, rc = 0, vf_index, bus, devfn, vf_pe_num;
	काष्ठा pci_dn *pdn, *पंचांगp, *parent, *physfn_pdn;
	u16 *vf_pe_array;

	vf_pe_array = kzalloc(RTAS_DATA_BUF_SIZE, GFP_KERNEL);
	अगर (!vf_pe_array)
		वापस -ENOMEM;
	अगर (pci_num_vf(edev->physfn ? edev->physfn : edev->pdev)) अणु
		अगर (edev->pdev->is_physfn) अणु
			cur_vfs = pci_num_vf(edev->pdev);
			pdn = eeh_dev_to_pdn(edev);
			parent = pdn->parent;
			क्रम (vf_index = 0; vf_index < cur_vfs; vf_index++)
				vf_pe_array[vf_index] =
					cpu_to_be16(pdn->pe_num_map[vf_index]);
			rc = pseries_send_allow_unमुक्तze(pdn, vf_pe_array,
							 cur_vfs);
			pdn->last_allow_rc = rc;
			क्रम (vf_index = 0; vf_index < cur_vfs; vf_index++) अणु
				list_क्रम_each_entry_safe(pdn, पंचांगp,
							 &parent->child_list,
							 list) अणु
					bus = pci_iov_virtfn_bus(edev->pdev,
								 vf_index);
					devfn = pci_iov_virtfn_devfn(edev->pdev,
								     vf_index);
					अगर (pdn->busno != bus ||
					    pdn->devfn != devfn)
						जारी;
					pdn->last_allow_rc = rc;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			pdn = pci_get_pdn(edev->pdev);
			physfn_pdn = pci_get_pdn(edev->physfn);

			vf_pe_num = physfn_pdn->pe_num_map[edev->vf_index];
			vf_pe_array[0] = cpu_to_be16(vf_pe_num);
			rc = pseries_send_allow_unमुक्तze(physfn_pdn,
							 vf_pe_array, 1);
			pdn->last_allow_rc = rc;
		पूर्ण
	पूर्ण

	kमुक्त(vf_pe_array);
	वापस rc;
पूर्ण

अटल पूर्णांक pseries_notअगरy_resume(काष्ठा eeh_dev *edev)
अणु
	अगर (!edev)
		वापस -EEXIST;

	अगर (rtas_token("ibm,open-sriov-allow-unfreeze") == RTAS_UNKNOWN_SERVICE)
		वापस -EINVAL;

	अगर (edev->pdev->is_physfn || edev->pdev->is_virtfn)
		वापस pseries_call_allow_unमुक्तze(edev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा eeh_ops pseries_eeh_ops = अणु
	.name			= "pseries",
	.probe			= pseries_eeh_probe,
	.set_option		= pseries_eeh_set_option,
	.get_state		= pseries_eeh_get_state,
	.reset			= pseries_eeh_reset,
	.get_log		= pseries_eeh_get_log,
	.configure_bridge       = pseries_eeh_configure_bridge,
	.err_inject		= शून्य,
	.पढ़ो_config		= pseries_eeh_पढ़ो_config,
	.ग_लिखो_config		= pseries_eeh_ग_लिखो_config,
	.next_error		= शून्य,
	.restore_config		= शून्य, /* NB: configure_bridge() करोes this */
#अगर_घोषित CONFIG_PCI_IOV
	.notअगरy_resume		= pseries_notअगरy_resume
#पूर्ण_अगर
पूर्ण;

/**
 * eeh_pseries_init - Register platक्रमm dependent EEH operations
 *
 * EEH initialization on pseries platक्रमm. This function should be
 * called beक्रमe any EEH related functions.
 */
अटल पूर्णांक __init eeh_pseries_init(व्योम)
अणु
	काष्ठा pci_controller *phb;
	काष्ठा pci_dn *pdn;
	पूर्णांक ret, config_addr;

	/* figure out EEH RTAS function call tokens */
	ibm_set_eeh_option		= rtas_token("ibm,set-eeh-option");
	ibm_set_slot_reset		= rtas_token("ibm,set-slot-reset");
	ibm_पढ़ो_slot_reset_state2	= rtas_token("ibm,read-slot-reset-state2");
	ibm_पढ़ो_slot_reset_state	= rtas_token("ibm,read-slot-reset-state");
	ibm_slot_error_detail		= rtas_token("ibm,slot-error-detail");
	ibm_get_config_addr_info2	= rtas_token("ibm,get-config-addr-info2");
	ibm_get_config_addr_info	= rtas_token("ibm,get-config-addr-info");
	ibm_configure_pe		= rtas_token("ibm,configure-pe");

	/*
	 * ibm,configure-pe and ibm,configure-bridge have the same semantics,
	 * however ibm,configure-pe can be faster.  If we can't find
	 * ibm,configure-pe then fall back to using ibm,configure-bridge.
	 */
	अगर (ibm_configure_pe == RTAS_UNKNOWN_SERVICE)
		ibm_configure_pe	= rtas_token("ibm,configure-bridge");

	/*
	 * Necessary sanity check. We needn't check "get-config-addr-info"
	 * and its variant since the old firmware probably support address
	 * of करोमुख्य/bus/slot/function क्रम EEH RTAS operations.
	 */
	अगर (ibm_set_eeh_option == RTAS_UNKNOWN_SERVICE		||
	    ibm_set_slot_reset == RTAS_UNKNOWN_SERVICE		||
	    (ibm_पढ़ो_slot_reset_state2 == RTAS_UNKNOWN_SERVICE &&
	     ibm_पढ़ो_slot_reset_state == RTAS_UNKNOWN_SERVICE)	||
	    ibm_slot_error_detail == RTAS_UNKNOWN_SERVICE	||
	    ibm_configure_pe == RTAS_UNKNOWN_SERVICE) अणु
		pr_info("EEH functionality not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Initialize error log lock and size */
	spin_lock_init(&slot_errbuf_lock);
	eeh_error_buf_size = rtas_token("rtas-error-log-max");
	अगर (eeh_error_buf_size == RTAS_UNKNOWN_SERVICE) अणु
		pr_info("%s: unknown EEH error log size\n",
			__func__);
		eeh_error_buf_size = 1024;
	पूर्ण अन्यथा अगर (eeh_error_buf_size > RTAS_ERROR_LOG_MAX) अणु
		pr_info("%s: EEH error log size %d exceeds the maximal %d\n",
			__func__, eeh_error_buf_size, RTAS_ERROR_LOG_MAX);
		eeh_error_buf_size = RTAS_ERROR_LOG_MAX;
	पूर्ण

	/* Set EEH probe mode */
	eeh_add_flag(EEH_PROBE_MODE_DEVTREE | EEH_ENABLE_IO_FOR_LOG);

	/* Set EEH machine dependent code */
	ppc_md.pcibios_bus_add_device = pseries_pcibios_bus_add_device;

	अगर (is_kdump_kernel() || reset_devices) अणु
		pr_info("Issue PHB reset ...\n");
		list_क्रम_each_entry(phb, &hose_list, list_node) अणु
			pdn = list_first_entry(&PCI_DN(phb->dn)->child_list, काष्ठा pci_dn, list);
			config_addr = pseries_eeh_get_pe_config_addr(pdn);

			/* invalid PE config addr */
			अगर (config_addr < 0)
				जारी;

			pseries_eeh_phb_reset(phb, config_addr, EEH_RESET_FUNDAMENTAL);
			pseries_eeh_phb_reset(phb, config_addr, EEH_RESET_DEACTIVATE);
			pseries_eeh_phb_configure_bridge(phb, config_addr);
		पूर्ण
	पूर्ण

	ret = eeh_init(&pseries_eeh_ops);
	अगर (!ret)
		pr_info("EEH: pSeries platform initialized\n");
	अन्यथा
		pr_info("EEH: pSeries platform initialization failure (%d)\n",
			ret);
	वापस ret;
पूर्ण
machine_arch_initcall(pseries, eeh_pseries_init);
