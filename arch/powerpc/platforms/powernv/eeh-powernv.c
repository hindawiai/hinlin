<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV Platक्रमm dependent EEH operations
 *
 * Copyright Benjamin Herrenschmidt & Gavin Shan, IBM Corporation 2013.
 */

#समावेश <linux/atomic.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/eeh_event.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/msi_biपंचांगap.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/pnv-pci.h>

#समावेश "powernv.h"
#समावेश "pci.h"
#समावेश "../../../../drivers/pci/pci.h"

अटल पूर्णांक eeh_event_irq = -EINVAL;

अटल व्योम pnv_pcibios_bus_add_device(काष्ठा pci_dev *pdev)
अणु
	dev_dbg(&pdev->dev, "EEH: Setting up device\n");
	eeh_probe_device(pdev);
पूर्ण

अटल irqवापस_t pnv_eeh_event(पूर्णांक irq, व्योम *data)
अणु
	/*
	 * We simply send a special EEH event अगर EEH has been
	 * enabled. We करोn't care about EEH events until we've
	 * finished processing the outstanding ones. Event processing
	 * माला_लो unmasked in next_error() अगर EEH is enabled.
	 */
	disable_irq_nosync(irq);

	अगर (eeh_enabled())
		eeh_send_failure_event(शून्य);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार pnv_eeh_ei_ग_लिखो(काष्ठा file *filp,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pci_controller *hose = filp->निजी_data;
	काष्ठा eeh_pe *pe;
	पूर्णांक pe_no, type, func;
	अचिन्हित दीर्घ addr, mask;
	अक्षर buf[50];
	पूर्णांक ret;

	अगर (!eeh_ops || !eeh_ops->err_inject)
		वापस -ENXIO;

	/* Copy over argument buffer */
	ret = simple_ग_लिखो_to_buffer(buf, माप(buf), ppos, user_buf, count);
	अगर (!ret)
		वापस -EFAULT;

	/* Retrieve parameters */
	ret = माला_पूछो(buf, "%x:%x:%x:%lx:%lx",
		     &pe_no, &type, &func, &addr, &mask);
	अगर (ret != 5)
		वापस -EINVAL;

	/* Retrieve PE */
	pe = eeh_pe_get(hose, pe_no);
	अगर (!pe)
		वापस -ENODEV;

	/* Do error injection */
	ret = eeh_ops->err_inject(pe, type, func, addr, mask);
	वापस ret < 0 ? ret : count;
पूर्ण

अटल स्थिर काष्ठा file_operations pnv_eeh_ei_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek	= no_llseek,
	.ग_लिखो	= pnv_eeh_ei_ग_लिखो,
पूर्ण;

अटल पूर्णांक pnv_eeh_dbgfs_set(व्योम *data, पूर्णांक offset, u64 val)
अणु
	काष्ठा pci_controller *hose = data;
	काष्ठा pnv_phb *phb = hose->निजी_data;

	out_be64(phb->regs + offset, val);
	वापस 0;
पूर्ण

अटल पूर्णांक pnv_eeh_dbgfs_get(व्योम *data, पूर्णांक offset, u64 *val)
अणु
	काष्ठा pci_controller *hose = data;
	काष्ठा pnv_phb *phb = hose->निजी_data;

	*val = in_be64(phb->regs + offset);
	वापस 0;
पूर्ण

#घोषणा PNV_EEH_DBGFS_ENTRY(name, reg)				\
अटल पूर्णांक pnv_eeh_dbgfs_set_##name(व्योम *data, u64 val)	\
अणु								\
	वापस pnv_eeh_dbgfs_set(data, reg, val);		\
पूर्ण								\
								\
अटल पूर्णांक pnv_eeh_dbgfs_get_##name(व्योम *data, u64 *val)	\
अणु								\
	वापस pnv_eeh_dbgfs_get(data, reg, val);		\
पूर्ण								\
								\
DEFINE_SIMPLE_ATTRIBUTE(pnv_eeh_dbgfs_ops_##name,		\
			pnv_eeh_dbgfs_get_##name,		\
                        pnv_eeh_dbgfs_set_##name,		\
			"0x%llx\n")

PNV_EEH_DBGFS_ENTRY(outb, 0xD10);
PNV_EEH_DBGFS_ENTRY(inbA, 0xD90);
PNV_EEH_DBGFS_ENTRY(inbB, 0xE10);

#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल व्योम pnv_eeh_enable_phbs(व्योम)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा pnv_phb *phb;

	list_क्रम_each_entry(hose, &hose_list, list_node) अणु
		phb = hose->निजी_data;
		/*
		 * If EEH is enabled, we're going to rely on that.
		 * Otherwise, we restore to conventional mechanism
		 * to clear frozen PE during PCI config access.
		 */
		अगर (eeh_enabled())
			phb->flags |= PNV_PHB_FLAG_EEH;
		अन्यथा
			phb->flags &= ~PNV_PHB_FLAG_EEH;
	पूर्ण
पूर्ण

/**
 * pnv_eeh_post_init - EEH platक्रमm dependent post initialization
 *
 * EEH platक्रमm dependent post initialization on घातernv. When
 * the function is called, the EEH PEs and devices should have
 * been built. If the I/O cache staff has been built, EEH is
 * पढ़ोy to supply service.
 */
पूर्णांक pnv_eeh_post_init(व्योम)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा pnv_phb *phb;
	पूर्णांक ret = 0;

	eeh_show_enabled();

	/* Register OPAL event notअगरier */
	eeh_event_irq = opal_event_request(ilog2(OPAL_EVENT_PCI_ERROR));
	अगर (eeh_event_irq < 0) अणु
		pr_err("%s: Can't register OPAL event interrupt (%d)\n",
		       __func__, eeh_event_irq);
		वापस eeh_event_irq;
	पूर्ण

	ret = request_irq(eeh_event_irq, pnv_eeh_event,
			  IRQ_TYPE_LEVEL_HIGH, "opal-eeh", शून्य);
	अगर (ret < 0) अणु
		irq_dispose_mapping(eeh_event_irq);
		pr_err("%s: Can't request OPAL event interrupt (%d)\n",
		       __func__, eeh_event_irq);
		वापस ret;
	पूर्ण

	अगर (!eeh_enabled())
		disable_irq(eeh_event_irq);

	pnv_eeh_enable_phbs();

	list_क्रम_each_entry(hose, &hose_list, list_node) अणु
		phb = hose->निजी_data;

		/* Create debugfs entries */
#अगर_घोषित CONFIG_DEBUG_FS
		अगर (phb->has_dbgfs || !phb->dbgfs)
			जारी;

		phb->has_dbgfs = 1;
		debugfs_create_file("err_injct", 0200,
				    phb->dbgfs, hose,
				    &pnv_eeh_ei_fops);

		debugfs_create_file("err_injct_outbound", 0600,
				    phb->dbgfs, hose,
				    &pnv_eeh_dbgfs_ops_outb);
		debugfs_create_file("err_injct_inboundA", 0600,
				    phb->dbgfs, hose,
				    &pnv_eeh_dbgfs_ops_inbA);
		debugfs_create_file("err_injct_inboundB", 0600,
				    phb->dbgfs, hose,
				    &pnv_eeh_dbgfs_ops_inbB);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pnv_eeh_find_cap(काष्ठा pci_dn *pdn, पूर्णांक cap)
अणु
	पूर्णांक pos = PCI_CAPABILITY_LIST;
	पूर्णांक cnt = 48;   /* Maximal number of capabilities */
	u32 status, id;

	अगर (!pdn)
		वापस 0;

	/* Check अगर the device supports capabilities */
	pnv_pci_cfg_पढ़ो(pdn, PCI_STATUS, 2, &status);
	अगर (!(status & PCI_STATUS_CAP_LIST))
		वापस 0;

	जबतक (cnt--) अणु
		pnv_pci_cfg_पढ़ो(pdn, pos, 1, &pos);
		अगर (pos < 0x40)
			अवरोध;

		pos &= ~3;
		pnv_pci_cfg_पढ़ो(pdn, pos + PCI_CAP_LIST_ID, 1, &id);
		अगर (id == 0xff)
			अवरोध;

		/* Found */
		अगर (id == cap)
			वापस pos;

		/* Next one */
		pos += PCI_CAP_LIST_NEXT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_eeh_find_ecap(काष्ठा pci_dn *pdn, पूर्णांक cap)
अणु
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);
	u32 header;
	पूर्णांक pos = 256, ttl = (4096 - 256) / 8;

	अगर (!edev || !edev->pcie_cap)
		वापस 0;
	अगर (pnv_pci_cfg_पढ़ो(pdn, pos, 4, &header) != PCIBIOS_SUCCESSFUL)
		वापस 0;
	अन्यथा अगर (!header)
		वापस 0;

	जबतक (ttl-- > 0) अणु
		अगर (PCI_EXT_CAP_ID(header) == cap && pos)
			वापस pos;

		pos = PCI_EXT_CAP_NEXT(header);
		अगर (pos < 256)
			अवरोध;

		अगर (pnv_pci_cfg_पढ़ो(pdn, pos, 4, &header) != PCIBIOS_SUCCESSFUL)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा eeh_pe *pnv_eeh_get_upstream_pe(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_controller *hose = pdev->bus->sysdata;
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा pci_dev *parent = pdev->bus->self;

#अगर_घोषित CONFIG_PCI_IOV
	/* क्रम VFs we use the PF's PE as the upstream PE */
	अगर (pdev->is_virtfn)
		parent = pdev->physfn;
#पूर्ण_अगर

	/* otherwise use the PE of our parent bridge */
	अगर (parent) अणु
		काष्ठा pnv_ioda_pe *ioda_pe = pnv_ioda_get_pe(parent);

		वापस eeh_pe_get(phb->hose, ioda_pe->pe_number);
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * pnv_eeh_probe - Do probe on PCI device
 * @pdev: pci_dev to probe
 *
 * Create, or find the existing, eeh_dev क्रम this pci_dev.
 */
अटल काष्ठा eeh_dev *pnv_eeh_probe(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn *pdn = pci_get_pdn(pdev);
	काष्ठा pci_controller *hose = pdn->phb;
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);
	काष्ठा eeh_pe *upstream_pe;
	uपूर्णांक32_t pcie_flags;
	पूर्णांक ret;
	पूर्णांक config_addr = (pdn->busno << 8) | (pdn->devfn);

	/*
	 * When probing the root bridge, which करोesn't have any
	 * subordinate PCI devices. We करोn't have OF node क्रम
	 * the root bridge. So it's not reasonable to जारी
	 * the probing.
	 */
	अगर (!edev || edev->pe)
		वापस शून्य;

	/* alपढ़ोy configured? */
	अगर (edev->pdev) अणु
		pr_debug("%s: found existing edev for %04x:%02x:%02x.%01x\n",
			__func__, hose->global_number, config_addr >> 8,
			PCI_SLOT(config_addr), PCI_FUNC(config_addr));
		वापस edev;
	पूर्ण

	/* Skip क्रम PCI-ISA bridge */
	अगर ((pdev->class >> 8) == PCI_CLASS_BRIDGE_ISA)
		वापस शून्य;

	eeh_edev_dbg(edev, "Probing device\n");

	/* Initialize eeh device */
	edev->mode	&= 0xFFFFFF00;
	edev->pcix_cap = pnv_eeh_find_cap(pdn, PCI_CAP_ID_PCIX);
	edev->pcie_cap = pnv_eeh_find_cap(pdn, PCI_CAP_ID_EXP);
	edev->af_cap   = pnv_eeh_find_cap(pdn, PCI_CAP_ID_AF);
	edev->aer_cap  = pnv_eeh_find_ecap(pdn, PCI_EXT_CAP_ID_ERR);
	अगर ((pdev->class >> 8) == PCI_CLASS_BRIDGE_PCI) अणु
		edev->mode |= EEH_DEV_BRIDGE;
		अगर (edev->pcie_cap) अणु
			pnv_pci_cfg_पढ़ो(pdn, edev->pcie_cap + PCI_EXP_FLAGS,
					 2, &pcie_flags);
			pcie_flags = (pcie_flags & PCI_EXP_FLAGS_TYPE) >> 4;
			अगर (pcie_flags == PCI_EXP_TYPE_ROOT_PORT)
				edev->mode |= EEH_DEV_ROOT_PORT;
			अन्यथा अगर (pcie_flags == PCI_EXP_TYPE_DOWNSTREAM)
				edev->mode |= EEH_DEV_DS_PORT;
		पूर्ण
	पूर्ण

	edev->pe_config_addr = phb->ioda.pe_rmap[config_addr];

	upstream_pe = pnv_eeh_get_upstream_pe(pdev);

	/* Create PE */
	ret = eeh_pe_tree_insert(edev, upstream_pe);
	अगर (ret) अणु
		eeh_edev_warn(edev, "Failed to add device to PE (code %d)\n", ret);
		वापस शून्य;
	पूर्ण

	/*
	 * If the PE contains any one of following adapters, the
	 * PCI config space can't be accessed when dumping EEH log.
	 * Otherwise, we will run पूर्णांकo fenced PHB caused by लघुage
	 * of outbound credits in the adapter. The PCI config access
	 * should be blocked until PE reset. MMIO access is dropped
	 * by hardware certainly. In order to drop PCI config requests,
	 * one more flag (EEH_PE_CFG_RESTRICTED) is पूर्णांकroduced, which
	 * will be checked in the backend क्रम PE state retrival. If
	 * the PE becomes frozen क्रम the first समय and the flag has
	 * been set क्रम the PE, we will set EEH_PE_CFG_BLOCKED क्रम
	 * that PE to block its config space.
	 *
	 * Broadcom BCM5718 2-ports NICs (14e4:1656)
	 * Broadcom Austin 4-ports NICs (14e4:1657)
	 * Broadcom Shiner 4-ports 1G NICs (14e4:168a)
	 * Broadcom Shiner 2-ports 10G NICs (14e4:168e)
	 */
	अगर ((pdn->venकरोr_id == PCI_VENDOR_ID_BROADCOM &&
	     pdn->device_id == 0x1656) ||
	    (pdn->venकरोr_id == PCI_VENDOR_ID_BROADCOM &&
	     pdn->device_id == 0x1657) ||
	    (pdn->venकरोr_id == PCI_VENDOR_ID_BROADCOM &&
	     pdn->device_id == 0x168a) ||
	    (pdn->venकरोr_id == PCI_VENDOR_ID_BROADCOM &&
	     pdn->device_id == 0x168e))
		edev->pe->state |= EEH_PE_CFG_RESTRICTED;

	/*
	 * Cache the PE primary bus, which can't be fetched when
	 * full hotplug is in progress. In that हाल, all child
	 * PCI devices of the PE are expected to be हटाओd prior
	 * to PE reset.
	 */
	अगर (!(edev->pe->state & EEH_PE_PRI_BUS)) अणु
		edev->pe->bus = pci_find_bus(hose->global_number,
					     pdn->busno);
		अगर (edev->pe->bus)
			edev->pe->state |= EEH_PE_PRI_BUS;
	पूर्ण

	/*
	 * Enable EEH explicitly so that we will करो EEH check
	 * जबतक accessing I/O stuff
	 */
	अगर (!eeh_has_flag(EEH_ENABLED)) अणु
		enable_irq(eeh_event_irq);
		pnv_eeh_enable_phbs();
		eeh_add_flag(EEH_ENABLED);
	पूर्ण

	/* Save memory bars */
	eeh_save_bars(edev);

	eeh_edev_dbg(edev, "EEH enabled on device\n");

	वापस edev;
पूर्ण

/**
 * pnv_eeh_set_option - Initialize EEH or MMIO/DMA reenable
 * @pe: EEH PE
 * @option: operation to be issued
 *
 * The function is used to control the EEH functionality globally.
 * Currently, following options are support according to PAPR:
 * Enable EEH, Disable EEH, Enable MMIO and Enable DMA
 */
अटल पूर्णांक pnv_eeh_set_option(काष्ठा eeh_pe *pe, पूर्णांक option)
अणु
	काष्ठा pci_controller *hose = pe->phb;
	काष्ठा pnv_phb *phb = hose->निजी_data;
	bool मुक्तze_pe = false;
	पूर्णांक opt;
	s64 rc;

	चयन (option) अणु
	हाल EEH_OPT_DISABLE:
		वापस -EPERM;
	हाल EEH_OPT_ENABLE:
		वापस 0;
	हाल EEH_OPT_THAW_MMIO:
		opt = OPAL_EEH_ACTION_CLEAR_FREEZE_MMIO;
		अवरोध;
	हाल EEH_OPT_THAW_DMA:
		opt = OPAL_EEH_ACTION_CLEAR_FREEZE_DMA;
		अवरोध;
	हाल EEH_OPT_FREEZE_PE:
		मुक्तze_pe = true;
		opt = OPAL_EEH_ACTION_SET_FREEZE_ALL;
		अवरोध;
	शेष:
		pr_warn("%s: Invalid option %d\n", __func__, option);
		वापस -EINVAL;
	पूर्ण

	/* Freeze master and slave PEs अगर PHB supports compound PEs */
	अगर (मुक्तze_pe) अणु
		अगर (phb->मुक्तze_pe) अणु
			phb->मुक्तze_pe(phb, pe->addr);
			वापस 0;
		पूर्ण

		rc = opal_pci_eeh_मुक्तze_set(phb->opal_id, pe->addr, opt);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("%s: Failure %lld freezing PHB#%x-PE#%x\n",
				__func__, rc, phb->hose->global_number,
				pe->addr);
			वापस -EIO;
		पूर्ण

		वापस 0;
	पूर्ण

	/* Unमुक्तze master and slave PEs अगर PHB supports */
	अगर (phb->unमुक्तze_pe)
		वापस phb->unमुक्तze_pe(phb, pe->addr, opt);

	rc = opal_pci_eeh_मुक्तze_clear(phb->opal_id, pe->addr, opt);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("%s: Failure %lld enable %d for PHB#%x-PE#%x\n",
			__func__, rc, option, phb->hose->global_number,
			pe->addr);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pnv_eeh_get_phb_diag(काष्ठा eeh_pe *pe)
अणु
	काष्ठा pnv_phb *phb = pe->phb->निजी_data;
	s64 rc;

	rc = opal_pci_get_phb_diag_data2(phb->opal_id, pe->data,
					 phb->diag_data_size);
	अगर (rc != OPAL_SUCCESS)
		pr_warn("%s: Failure %lld getting PHB#%x diag-data\n",
			__func__, rc, pe->phb->global_number);
पूर्ण

अटल पूर्णांक pnv_eeh_get_phb_state(काष्ठा eeh_pe *pe)
अणु
	काष्ठा pnv_phb *phb = pe->phb->निजी_data;
	u8 ख_स्थितिe = 0;
	__be16 pcierr = 0;
	s64 rc;
	पूर्णांक result = 0;

	rc = opal_pci_eeh_मुक्तze_status(phb->opal_id,
					pe->addr,
					&ख_स्थितिe,
					&pcierr,
					शून्य);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("%s: Failure %lld getting PHB#%x state\n",
			__func__, rc, phb->hose->global_number);
		वापस EEH_STATE_NOT_SUPPORT;
	पूर्ण

	/*
	 * Check PHB state. If the PHB is frozen क्रम the
	 * first समय, to dump the PHB diag-data.
	 */
	अगर (be16_to_cpu(pcierr) != OPAL_EEH_PHB_ERROR) अणु
		result = (EEH_STATE_MMIO_ACTIVE  |
			  EEH_STATE_DMA_ACTIVE   |
			  EEH_STATE_MMIO_ENABLED |
			  EEH_STATE_DMA_ENABLED);
	पूर्ण अन्यथा अगर (!(pe->state & EEH_PE_ISOLATED)) अणु
		eeh_pe_mark_isolated(pe);
		pnv_eeh_get_phb_diag(pe);

		अगर (eeh_has_flag(EEH_EARLY_DUMP_LOG))
			pnv_pci_dump_phb_diag_data(pe->phb, pe->data);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक pnv_eeh_get_pe_state(काष्ठा eeh_pe *pe)
अणु
	काष्ठा pnv_phb *phb = pe->phb->निजी_data;
	u8 ख_स्थितिe = 0;
	__be16 pcierr = 0;
	s64 rc;
	पूर्णांक result;

	/*
	 * We करोn't clobber hardware frozen state until PE
	 * reset is completed. In order to keep EEH core
	 * moving क्रमward, we have to वापस operational
	 * state during PE reset.
	 */
	अगर (pe->state & EEH_PE_RESET) अणु
		result = (EEH_STATE_MMIO_ACTIVE  |
			  EEH_STATE_DMA_ACTIVE   |
			  EEH_STATE_MMIO_ENABLED |
			  EEH_STATE_DMA_ENABLED);
		वापस result;
	पूर्ण

	/*
	 * Fetch PE state from hardware. If the PHB
	 * supports compound PE, let it handle that.
	 */
	अगर (phb->get_pe_state) अणु
		ख_स्थितिe = phb->get_pe_state(phb, pe->addr);
	पूर्ण अन्यथा अणु
		rc = opal_pci_eeh_मुक्तze_status(phb->opal_id,
						pe->addr,
						&ख_स्थितिe,
						&pcierr,
						शून्य);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("%s: Failure %lld getting PHB#%x-PE%x state\n",
				__func__, rc, phb->hose->global_number,
				pe->addr);
			वापस EEH_STATE_NOT_SUPPORT;
		पूर्ण
	पूर्ण

	/* Figure out state */
	चयन (ख_स्थितिe) अणु
	हाल OPAL_EEH_STOPPED_NOT_FROZEN:
		result = (EEH_STATE_MMIO_ACTIVE  |
			  EEH_STATE_DMA_ACTIVE   |
			  EEH_STATE_MMIO_ENABLED |
			  EEH_STATE_DMA_ENABLED);
		अवरोध;
	हाल OPAL_EEH_STOPPED_MMIO_FREEZE:
		result = (EEH_STATE_DMA_ACTIVE |
			  EEH_STATE_DMA_ENABLED);
		अवरोध;
	हाल OPAL_EEH_STOPPED_DMA_FREEZE:
		result = (EEH_STATE_MMIO_ACTIVE |
			  EEH_STATE_MMIO_ENABLED);
		अवरोध;
	हाल OPAL_EEH_STOPPED_MMIO_DMA_FREEZE:
		result = 0;
		अवरोध;
	हाल OPAL_EEH_STOPPED_RESET:
		result = EEH_STATE_RESET_ACTIVE;
		अवरोध;
	हाल OPAL_EEH_STOPPED_TEMP_UNAVAIL:
		result = EEH_STATE_UNAVAILABLE;
		अवरोध;
	हाल OPAL_EEH_STOPPED_PERM_UNAVAIL:
		result = EEH_STATE_NOT_SUPPORT;
		अवरोध;
	शेष:
		result = EEH_STATE_NOT_SUPPORT;
		pr_warn("%s: Invalid PHB#%x-PE#%x state %x\n",
			__func__, phb->hose->global_number,
			pe->addr, ख_स्थितिe);
	पूर्ण

	/*
	 * If PHB supports compound PE, to मुक्तze all
	 * slave PEs क्रम consistency.
	 *
	 * If the PE is चयनing to frozen state क्रम the
	 * first समय, to dump the PHB diag-data.
	 */
	अगर (!(result & EEH_STATE_NOT_SUPPORT) &&
	    !(result & EEH_STATE_UNAVAILABLE) &&
	    !(result & EEH_STATE_MMIO_ACTIVE) &&
	    !(result & EEH_STATE_DMA_ACTIVE)  &&
	    !(pe->state & EEH_PE_ISOLATED)) अणु
		अगर (phb->मुक्तze_pe)
			phb->मुक्तze_pe(phb, pe->addr);

		eeh_pe_mark_isolated(pe);
		pnv_eeh_get_phb_diag(pe);

		अगर (eeh_has_flag(EEH_EARLY_DUMP_LOG))
			pnv_pci_dump_phb_diag_data(pe->phb, pe->data);
	पूर्ण

	वापस result;
पूर्ण

/**
 * pnv_eeh_get_state - Retrieve PE state
 * @pe: EEH PE
 * @delay: delay जबतक PE state is temporarily unavailable
 *
 * Retrieve the state of the specअगरied PE. For IODA-compitable
 * platक्रमm, it should be retrieved from IODA table. Thereक्रमe,
 * we prefer passing करोwn to hardware implementation to handle
 * it.
 */
अटल पूर्णांक pnv_eeh_get_state(काष्ठा eeh_pe *pe, पूर्णांक *delay)
अणु
	पूर्णांक ret;

	अगर (pe->type & EEH_PE_PHB)
		ret = pnv_eeh_get_phb_state(pe);
	अन्यथा
		ret = pnv_eeh_get_pe_state(pe);

	अगर (!delay)
		वापस ret;

	/*
	 * If the PE state is temporarily unavailable,
	 * to inक्रमm the EEH core delay क्रम शेष
	 * period (1 second)
	 */
	*delay = 0;
	अगर (ret & EEH_STATE_UNAVAILABLE)
		*delay = 1000;

	वापस ret;
पूर्ण

अटल s64 pnv_eeh_poll(अचिन्हित दीर्घ id)
अणु
	s64 rc = OPAL_HARDWARE;

	जबतक (1) अणु
		rc = opal_pci_poll(id);
		अगर (rc <= 0)
			अवरोध;

		अगर (प्रणाली_state < SYSTEM_RUNNING)
			udelay(1000 * rc);
		अन्यथा
			msleep(rc);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक pnv_eeh_phb_reset(काष्ठा pci_controller *hose, पूर्णांक option)
अणु
	काष्ठा pnv_phb *phb = hose->निजी_data;
	s64 rc = OPAL_HARDWARE;

	pr_debug("%s: Reset PHB#%x, option=%d\n",
		 __func__, hose->global_number, option);

	/* Issue PHB complete reset request */
	अगर (option == EEH_RESET_FUNDAMENTAL ||
	    option == EEH_RESET_HOT)
		rc = opal_pci_reset(phb->opal_id,
				    OPAL_RESET_PHB_COMPLETE,
				    OPAL_ASSERT_RESET);
	अन्यथा अगर (option == EEH_RESET_DEACTIVATE)
		rc = opal_pci_reset(phb->opal_id,
				    OPAL_RESET_PHB_COMPLETE,
				    OPAL_DEASSERT_RESET);
	अगर (rc < 0)
		जाओ out;

	/*
	 * Poll state of the PHB until the request is करोne
	 * successfully. The PHB reset is usually PHB complete
	 * reset followed by hot reset on root bus. So we also
	 * need the PCI bus settlement delay.
	 */
	अगर (rc > 0)
		rc = pnv_eeh_poll(phb->opal_id);
	अगर (option == EEH_RESET_DEACTIVATE) अणु
		अगर (प्रणाली_state < SYSTEM_RUNNING)
			udelay(1000 * EEH_PE_RST_SETTLE_TIME);
		अन्यथा
			msleep(EEH_PE_RST_SETTLE_TIME);
	पूर्ण
out:
	अगर (rc != OPAL_SUCCESS)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_eeh_root_reset(काष्ठा pci_controller *hose, पूर्णांक option)
अणु
	काष्ठा pnv_phb *phb = hose->निजी_data;
	s64 rc = OPAL_HARDWARE;

	pr_debug("%s: Reset PHB#%x, option=%d\n",
		 __func__, hose->global_number, option);

	/*
	 * During the reset deनिश्चित समय, we needn't care
	 * the reset scope because the firmware करोes nothing
	 * क्रम fundamental or hot reset during deनिश्चित phase.
	 */
	अगर (option == EEH_RESET_FUNDAMENTAL)
		rc = opal_pci_reset(phb->opal_id,
				    OPAL_RESET_PCI_FUNDAMENTAL,
				    OPAL_ASSERT_RESET);
	अन्यथा अगर (option == EEH_RESET_HOT)
		rc = opal_pci_reset(phb->opal_id,
				    OPAL_RESET_PCI_HOT,
				    OPAL_ASSERT_RESET);
	अन्यथा अगर (option == EEH_RESET_DEACTIVATE)
		rc = opal_pci_reset(phb->opal_id,
				    OPAL_RESET_PCI_HOT,
				    OPAL_DEASSERT_RESET);
	अगर (rc < 0)
		जाओ out;

	/* Poll state of the PHB until the request is करोne */
	अगर (rc > 0)
		rc = pnv_eeh_poll(phb->opal_id);
	अगर (option == EEH_RESET_DEACTIVATE)
		msleep(EEH_PE_RST_SETTLE_TIME);
out:
	अगर (rc != OPAL_SUCCESS)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक __pnv_eeh_bridge_reset(काष्ठा pci_dev *dev, पूर्णांक option)
अणु
	काष्ठा pci_dn *pdn = pci_get_pdn_by_devfn(dev->bus, dev->devfn);
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);
	पूर्णांक aer = edev ? edev->aer_cap : 0;
	u32 ctrl;

	pr_debug("%s: Secondary Reset PCI bus %04x:%02x with option %d\n",
		 __func__, pci_करोमुख्य_nr(dev->bus),
		 dev->bus->number, option);

	चयन (option) अणु
	हाल EEH_RESET_FUNDAMENTAL:
	हाल EEH_RESET_HOT:
		/* Don't report linkDown event */
		अगर (aer) अणु
			eeh_ops->पढ़ो_config(edev, aer + PCI_ERR_UNCOR_MASK,
					     4, &ctrl);
			ctrl |= PCI_ERR_UNC_SURPDN;
			eeh_ops->ग_लिखो_config(edev, aer + PCI_ERR_UNCOR_MASK,
					      4, ctrl);
		पूर्ण

		eeh_ops->पढ़ो_config(edev, PCI_BRIDGE_CONTROL, 2, &ctrl);
		ctrl |= PCI_BRIDGE_CTL_BUS_RESET;
		eeh_ops->ग_लिखो_config(edev, PCI_BRIDGE_CONTROL, 2, ctrl);

		msleep(EEH_PE_RST_HOLD_TIME);
		अवरोध;
	हाल EEH_RESET_DEACTIVATE:
		eeh_ops->पढ़ो_config(edev, PCI_BRIDGE_CONTROL, 2, &ctrl);
		ctrl &= ~PCI_BRIDGE_CTL_BUS_RESET;
		eeh_ops->ग_लिखो_config(edev, PCI_BRIDGE_CONTROL, 2, ctrl);

		msleep(EEH_PE_RST_SETTLE_TIME);

		/* Continue reporting linkDown event */
		अगर (aer) अणु
			eeh_ops->पढ़ो_config(edev, aer + PCI_ERR_UNCOR_MASK,
					     4, &ctrl);
			ctrl &= ~PCI_ERR_UNC_SURPDN;
			eeh_ops->ग_लिखो_config(edev, aer + PCI_ERR_UNCOR_MASK,
					      4, ctrl);
		पूर्ण

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_eeh_bridge_reset(काष्ठा pci_dev *pdev, पूर्णांक option)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(pdev->bus);
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा device_node *dn = pci_device_to_OF_node(pdev);
	uपूर्णांक64_t id = PCI_SLOT_ID(phb->opal_id,
				  (pdev->bus->number << 8) | pdev->devfn);
	uपूर्णांक8_t scope;
	पूर्णांक64_t rc;

	/* Hot reset to the bus अगर firmware cannot handle */
	अगर (!dn || !of_get_property(dn, "ibm,reset-by-firmware", शून्य))
		वापस __pnv_eeh_bridge_reset(pdev, option);

	pr_debug("%s: FW reset PCI bus %04x:%02x with option %d\n",
		 __func__, pci_करोमुख्य_nr(pdev->bus),
		 pdev->bus->number, option);

	चयन (option) अणु
	हाल EEH_RESET_FUNDAMENTAL:
		scope = OPAL_RESET_PCI_FUNDAMENTAL;
		अवरोध;
	हाल EEH_RESET_HOT:
		scope = OPAL_RESET_PCI_HOT;
		अवरोध;
	हाल EEH_RESET_DEACTIVATE:
		वापस 0;
	शेष:
		dev_dbg(&pdev->dev, "%s: Unsupported reset %d\n",
			__func__, option);
		वापस -EINVAL;
	पूर्ण

	rc = opal_pci_reset(id, scope, OPAL_ASSERT_RESET);
	अगर (rc <= OPAL_SUCCESS)
		जाओ out;

	rc = pnv_eeh_poll(id);
out:
	वापस (rc == OPAL_SUCCESS) ? 0 : -EIO;
पूर्ण

व्योम pnv_pci_reset_secondary_bus(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose;

	अगर (pci_is_root_bus(dev->bus)) अणु
		hose = pci_bus_to_host(dev->bus);
		pnv_eeh_root_reset(hose, EEH_RESET_HOT);
		pnv_eeh_root_reset(hose, EEH_RESET_DEACTIVATE);
	पूर्ण अन्यथा अणु
		pnv_eeh_bridge_reset(dev, EEH_RESET_HOT);
		pnv_eeh_bridge_reset(dev, EEH_RESET_DEACTIVATE);
	पूर्ण
पूर्ण

अटल व्योम pnv_eeh_रुको_क्रम_pending(काष्ठा pci_dn *pdn, स्थिर अक्षर *type,
				     पूर्णांक pos, u16 mask)
अणु
	काष्ठा eeh_dev *edev = pdn->edev;
	पूर्णांक i, status = 0;

	/* Wait क्रम Transaction Pending bit to be cleared */
	क्रम (i = 0; i < 4; i++) अणु
		eeh_ops->पढ़ो_config(edev, pos, 2, &status);
		अगर (!(status & mask))
			वापस;

		msleep((1 << i) * 100);
	पूर्ण

	pr_warn("%s: Pending transaction while issuing %sFLR to %04x:%02x:%02x.%01x\n",
		__func__, type,
		pdn->phb->global_number, pdn->busno,
		PCI_SLOT(pdn->devfn), PCI_FUNC(pdn->devfn));
पूर्ण

अटल पूर्णांक pnv_eeh_करो_flr(काष्ठा pci_dn *pdn, पूर्णांक option)
अणु
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);
	u32 reg = 0;

	अगर (WARN_ON(!edev->pcie_cap))
		वापस -ENOTTY;

	eeh_ops->पढ़ो_config(edev, edev->pcie_cap + PCI_EXP_DEVCAP, 4, &reg);
	अगर (!(reg & PCI_EXP_DEVCAP_FLR))
		वापस -ENOTTY;

	चयन (option) अणु
	हाल EEH_RESET_HOT:
	हाल EEH_RESET_FUNDAMENTAL:
		pnv_eeh_रुको_क्रम_pending(pdn, "",
					 edev->pcie_cap + PCI_EXP_DEVSTA,
					 PCI_EXP_DEVSTA_TRPND);
		eeh_ops->पढ़ो_config(edev, edev->pcie_cap + PCI_EXP_DEVCTL,
				     4, &reg);
		reg |= PCI_EXP_DEVCTL_BCR_FLR;
		eeh_ops->ग_लिखो_config(edev, edev->pcie_cap + PCI_EXP_DEVCTL,
				      4, reg);
		msleep(EEH_PE_RST_HOLD_TIME);
		अवरोध;
	हाल EEH_RESET_DEACTIVATE:
		eeh_ops->पढ़ो_config(edev, edev->pcie_cap + PCI_EXP_DEVCTL,
				     4, &reg);
		reg &= ~PCI_EXP_DEVCTL_BCR_FLR;
		eeh_ops->ग_लिखो_config(edev, edev->pcie_cap + PCI_EXP_DEVCTL,
				      4, reg);
		msleep(EEH_PE_RST_SETTLE_TIME);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_eeh_करो_af_flr(काष्ठा pci_dn *pdn, पूर्णांक option)
अणु
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);
	u32 cap = 0;

	अगर (WARN_ON(!edev->af_cap))
		वापस -ENOTTY;

	eeh_ops->पढ़ो_config(edev, edev->af_cap + PCI_AF_CAP, 1, &cap);
	अगर (!(cap & PCI_AF_CAP_TP) || !(cap & PCI_AF_CAP_FLR))
		वापस -ENOTTY;

	चयन (option) अणु
	हाल EEH_RESET_HOT:
	हाल EEH_RESET_FUNDAMENTAL:
		/*
		 * Wait क्रम Transaction Pending bit to clear. A word-aligned
		 * test is used, so we use the conrol offset rather than status
		 * and shअगरt the test bit to match.
		 */
		pnv_eeh_रुको_क्रम_pending(pdn, "AF",
					 edev->af_cap + PCI_AF_CTRL,
					 PCI_AF_STATUS_TP << 8);
		eeh_ops->ग_लिखो_config(edev, edev->af_cap + PCI_AF_CTRL,
				      1, PCI_AF_CTRL_FLR);
		msleep(EEH_PE_RST_HOLD_TIME);
		अवरोध;
	हाल EEH_RESET_DEACTIVATE:
		eeh_ops->ग_लिखो_config(edev, edev->af_cap + PCI_AF_CTRL, 1, 0);
		msleep(EEH_PE_RST_SETTLE_TIME);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pnv_eeh_reset_vf_pe(काष्ठा eeh_pe *pe, पूर्णांक option)
अणु
	काष्ठा eeh_dev *edev;
	काष्ठा pci_dn *pdn;
	पूर्णांक ret;

	/* The VF PE should have only one child device */
	edev = list_first_entry_or_null(&pe->edevs, काष्ठा eeh_dev, entry);
	pdn = eeh_dev_to_pdn(edev);
	अगर (!pdn)
		वापस -ENXIO;

	ret = pnv_eeh_करो_flr(pdn, option);
	अगर (!ret)
		वापस ret;

	वापस pnv_eeh_करो_af_flr(pdn, option);
पूर्ण

/**
 * pnv_eeh_reset - Reset the specअगरied PE
 * @pe: EEH PE
 * @option: reset option
 *
 * Do reset on the indicated PE. For PCI bus sensitive PE,
 * we need to reset the parent p2p bridge. The PHB has to
 * be reinitialized अगर the p2p bridge is root bridge. For
 * PCI device sensitive PE, we will try to reset the device
 * through FLR. For now, we करोn't have OPAL APIs to करो HARD
 * reset yet, so all reset would be SOFT (HOT) reset.
 */
अटल पूर्णांक pnv_eeh_reset(काष्ठा eeh_pe *pe, पूर्णांक option)
अणु
	काष्ठा pci_controller *hose = pe->phb;
	काष्ठा pnv_phb *phb;
	काष्ठा pci_bus *bus;
	पूर्णांक64_t rc;

	/*
	 * For PHB reset, we always have complete reset. For those PEs whose
	 * primary bus derived from root complex (root bus) or root port
	 * (usually bus#1), we apply hot or fundamental reset on the root port.
	 * For other PEs, we always have hot reset on the PE primary bus.
	 *
	 * Here, we have dअगरferent design to pHyp, which always clear the
	 * frozen state during PE reset. However, the good idea here from
	 * benh is to keep frozen state beक्रमe we get PE reset करोne completely
	 * (until BAR restore). With the frozen state, HW drops illegal IO
	 * or MMIO access, which can incur recrusive frozen PE during PE
	 * reset. The side effect is that EEH core has to clear the frozen
	 * state explicitly after BAR restore.
	 */
	अगर (pe->type & EEH_PE_PHB)
		वापस pnv_eeh_phb_reset(hose, option);

	/*
	 * The frozen PE might be caused by PAPR error injection
	 * रेजिस्टरs, which are expected to be cleared after hitting
	 * frozen PE as stated in the hardware spec. Unक्रमtunately,
	 * that's not true on P7IOC. So we have to clear it manually
	 * to aव्योम recursive EEH errors during recovery.
	 */
	phb = hose->निजी_data;
	अगर (phb->model == PNV_PHB_MODEL_P7IOC &&
	    (option == EEH_RESET_HOT ||
	     option == EEH_RESET_FUNDAMENTAL)) अणु
		rc = opal_pci_reset(phb->opal_id,
				    OPAL_RESET_PHB_ERROR,
				    OPAL_ASSERT_RESET);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_warn("%s: Failure %lld clearing error injection registers\n",
				__func__, rc);
			वापस -EIO;
		पूर्ण
	पूर्ण

	अगर (pe->type & EEH_PE_VF)
		वापस pnv_eeh_reset_vf_pe(pe, option);

	bus = eeh_pe_bus_get(pe);
	अगर (!bus) अणु
		pr_err("%s: Cannot find PCI bus for PHB#%x-PE#%x\n",
			__func__, pe->phb->global_number, pe->addr);
		वापस -EIO;
	पूर्ण

	अगर (pci_is_root_bus(bus))
		वापस pnv_eeh_root_reset(hose, option);

	/*
	 * For hot resets try use the generic PCI error recovery reset
	 * functions. These correctly handles the हाल where the secondary
	 * bus is behind a hotplug slot and it will use the slot provided
	 * reset methods to prevent spurious hotplug events during the reset.
	 *
	 * Fundemental resets need to be handled पूर्णांकernally to EEH since the
	 * PCI core करोesn't really have a concept of a fundemental reset,
	 * मुख्यly because there's no standard way to generate one. Only a
	 * few devices require an FRESET so it should be fine.
	 */
	अगर (option != EEH_RESET_FUNDAMENTAL) अणु
		/*
		 * NB: Skiboot and pnv_eeh_bridge_reset() also no-op the
		 *     de-निश्चित step. It's like the OPAL reset API was
		 *     poorly deचिन्हित or something...
		 */
		अगर (option == EEH_RESET_DEACTIVATE)
			वापस 0;

		rc = pci_bus_error_reset(bus->self);
		अगर (!rc)
			वापस 0;
	पूर्ण

	/* otherwise, use the generic bridge reset. this might call पूर्णांकo FW */
	अगर (pci_is_root_bus(bus->parent))
		वापस pnv_eeh_root_reset(hose, option);
	वापस pnv_eeh_bridge_reset(bus->self, option);
पूर्ण

/**
 * pnv_eeh_get_log - Retrieve error log
 * @pe: EEH PE
 * @severity: temporary or permanent error log
 * @drv_log: driver log to be combined with retrieved error log
 * @len: length of driver log
 *
 * Retrieve the temporary or permanent error from the PE.
 */
अटल पूर्णांक pnv_eeh_get_log(काष्ठा eeh_pe *pe, पूर्णांक severity,
			   अक्षर *drv_log, अचिन्हित दीर्घ len)
अणु
	अगर (!eeh_has_flag(EEH_EARLY_DUMP_LOG))
		pnv_pci_dump_phb_diag_data(pe->phb, pe->data);

	वापस 0;
पूर्ण

/**
 * pnv_eeh_configure_bridge - Configure PCI bridges in the indicated PE
 * @pe: EEH PE
 *
 * The function will be called to reconfigure the bridges included
 * in the specअगरied PE so that the mulfunctional PE would be recovered
 * again.
 */
अटल पूर्णांक pnv_eeh_configure_bridge(काष्ठा eeh_pe *pe)
अणु
	वापस 0;
पूर्ण

/**
 * pnv_pe_err_inject - Inject specअगरied error to the indicated PE
 * @pe: the indicated PE
 * @type: error type
 * @func: specअगरic error type
 * @addr: address
 * @mask: address mask
 *
 * The routine is called to inject specअगरied error, which is
 * determined by @type and @func, to the indicated PE क्रम
 * testing purpose.
 */
अटल पूर्णांक pnv_eeh_err_inject(काष्ठा eeh_pe *pe, पूर्णांक type, पूर्णांक func,
			      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ mask)
अणु
	काष्ठा pci_controller *hose = pe->phb;
	काष्ठा pnv_phb *phb = hose->निजी_data;
	s64 rc;

	अगर (type != OPAL_ERR_INJECT_TYPE_IOA_BUS_ERR &&
	    type != OPAL_ERR_INJECT_TYPE_IOA_BUS_ERR64) अणु
		pr_warn("%s: Invalid error type %d\n",
			__func__, type);
		वापस -दुस्फल;
	पूर्ण

	अगर (func < OPAL_ERR_INJECT_FUNC_IOA_LD_MEM_ADDR ||
	    func > OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_TARGET) अणु
		pr_warn("%s: Invalid error function %d\n",
			__func__, func);
		वापस -दुस्फल;
	पूर्ण

	/* Firmware supports error injection ? */
	अगर (!opal_check_token(OPAL_PCI_ERR_INJECT)) अणु
		pr_warn("%s: Firmware doesn't support error injection\n",
			__func__);
		वापस -ENXIO;
	पूर्ण

	/* Do error injection */
	rc = opal_pci_err_inject(phb->opal_id, pe->addr,
				 type, func, addr, mask);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("%s: Failure %lld injecting error "
			"%d-%d to PHB#%x-PE#%x\n",
			__func__, rc, type, func,
			hose->global_number, pe->addr);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool pnv_eeh_cfg_blocked(काष्ठा pci_dn *pdn)
अणु
	काष्ठा eeh_dev *edev = pdn_to_eeh_dev(pdn);

	अगर (!edev || !edev->pe)
		वापस false;

	/*
	 * We will issue FLR or AF FLR to all VFs, which are contained
	 * in VF PE. It relies on the EEH PCI config accessors. So we
	 * can't block them during the winकरोw.
	 */
	अगर (edev->physfn && (edev->pe->state & EEH_PE_RESET))
		वापस false;

	अगर (edev->pe->state & EEH_PE_CFG_BLOCKED)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक pnv_eeh_पढ़ो_config(काष्ठा eeh_dev *edev,
			       पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_dn *pdn = eeh_dev_to_pdn(edev);

	अगर (!pdn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (pnv_eeh_cfg_blocked(pdn)) अणु
		*val = 0xFFFFFFFF;
		वापस PCIBIOS_SET_FAILED;
	पूर्ण

	वापस pnv_pci_cfg_पढ़ो(pdn, where, size, val);
पूर्ण

अटल पूर्णांक pnv_eeh_ग_लिखो_config(काष्ठा eeh_dev *edev,
				पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_dn *pdn = eeh_dev_to_pdn(edev);

	अगर (!pdn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (pnv_eeh_cfg_blocked(pdn))
		वापस PCIBIOS_SET_FAILED;

	वापस pnv_pci_cfg_ग_लिखो(pdn, where, size, val);
पूर्ण

अटल व्योम pnv_eeh_dump_hub_diag_common(काष्ठा OpalIoP7IOCErrorData *data)
अणु
	/* GEM */
	अगर (data->gemXfir || data->gemRfir ||
	    data->gemRirqfir || data->gemMask || data->gemRwof)
		pr_info("  GEM: %016llx %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->gemXfir),
			be64_to_cpu(data->gemRfir),
			be64_to_cpu(data->gemRirqfir),
			be64_to_cpu(data->gemMask),
			be64_to_cpu(data->gemRwof));

	/* LEM */
	अगर (data->lemFir || data->lemErrMask ||
	    data->lemAction0 || data->lemAction1 || data->lemWof)
		pr_info("  LEM: %016llx %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->lemFir),
			be64_to_cpu(data->lemErrMask),
			be64_to_cpu(data->lemAction0),
			be64_to_cpu(data->lemAction1),
			be64_to_cpu(data->lemWof));
पूर्ण

अटल व्योम pnv_eeh_get_and_dump_hub_diag(काष्ठा pci_controller *hose)
अणु
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा OpalIoP7IOCErrorData *data =
		(काष्ठा OpalIoP7IOCErrorData*)phb->diag_data;
	दीर्घ rc;

	rc = opal_pci_get_hub_diag_data(phb->hub_id, data, माप(*data));
	अगर (rc != OPAL_SUCCESS) अणु
		pr_warn("%s: Failed to get HUB#%llx diag-data (%ld)\n",
			__func__, phb->hub_id, rc);
		वापस;
	पूर्ण

	चयन (be16_to_cpu(data->type)) अणु
	हाल OPAL_P7IOC_DIAG_TYPE_RGC:
		pr_info("P7IOC diag-data for RGC\n\n");
		pnv_eeh_dump_hub_diag_common(data);
		अगर (data->rgc.rgcStatus || data->rgc.rgcLdcp)
			pr_info("  RGC: %016llx %016llx\n",
				be64_to_cpu(data->rgc.rgcStatus),
				be64_to_cpu(data->rgc.rgcLdcp));
		अवरोध;
	हाल OPAL_P7IOC_DIAG_TYPE_BI:
		pr_info("P7IOC diag-data for BI %s\n\n",
			data->bi.biDownbound ? "Downbound" : "Upbound");
		pnv_eeh_dump_hub_diag_common(data);
		अगर (data->bi.biLdcp0 || data->bi.biLdcp1 ||
		    data->bi.biLdcp2 || data->bi.biFenceStatus)
			pr_info("  BI:  %016llx %016llx %016llx %016llx\n",
				be64_to_cpu(data->bi.biLdcp0),
				be64_to_cpu(data->bi.biLdcp1),
				be64_to_cpu(data->bi.biLdcp2),
				be64_to_cpu(data->bi.biFenceStatus));
		अवरोध;
	हाल OPAL_P7IOC_DIAG_TYPE_CI:
		pr_info("P7IOC diag-data for CI Port %d\n\n",
			data->ci.ciPort);
		pnv_eeh_dump_hub_diag_common(data);
		अगर (data->ci.ciPortStatus || data->ci.ciPortLdcp)
			pr_info("  CI:  %016llx %016llx\n",
				be64_to_cpu(data->ci.ciPortStatus),
				be64_to_cpu(data->ci.ciPortLdcp));
		अवरोध;
	हाल OPAL_P7IOC_DIAG_TYPE_MISC:
		pr_info("P7IOC diag-data for MISC\n\n");
		pnv_eeh_dump_hub_diag_common(data);
		अवरोध;
	हाल OPAL_P7IOC_DIAG_TYPE_I2C:
		pr_info("P7IOC diag-data for I2C\n\n");
		pnv_eeh_dump_hub_diag_common(data);
		अवरोध;
	शेष:
		pr_warn("%s: Invalid type of HUB#%llx diag-data (%d)\n",
			__func__, phb->hub_id, data->type);
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_eeh_get_pe(काष्ठा pci_controller *hose,
			  u16 pe_no, काष्ठा eeh_pe **pe)
अणु
	काष्ठा pnv_phb *phb = hose->निजी_data;
	काष्ठा pnv_ioda_pe *pnv_pe;
	काष्ठा eeh_pe *dev_pe;

	/*
	 * If PHB supports compound PE, to fetch
	 * the master PE because slave PE is invisible
	 * to EEH core.
	 */
	pnv_pe = &phb->ioda.pe_array[pe_no];
	अगर (pnv_pe->flags & PNV_IODA_PE_SLAVE) अणु
		pnv_pe = pnv_pe->master;
		WARN_ON(!pnv_pe ||
			!(pnv_pe->flags & PNV_IODA_PE_MASTER));
		pe_no = pnv_pe->pe_number;
	पूर्ण

	/* Find the PE according to PE# */
	dev_pe = eeh_pe_get(hose, pe_no);
	अगर (!dev_pe)
		वापस -EEXIST;

	/* Freeze the (compound) PE */
	*pe = dev_pe;
	अगर (!(dev_pe->state & EEH_PE_ISOLATED))
		phb->मुक्तze_pe(phb, pe_no);

	/*
	 * At this poपूर्णांक, we're sure the (compound) PE should
	 * have been frozen. However, we still need poke until
	 * hitting the frozen PE on top level.
	 */
	dev_pe = dev_pe->parent;
	जबतक (dev_pe && !(dev_pe->type & EEH_PE_PHB)) अणु
		पूर्णांक ret;
		ret = eeh_ops->get_state(dev_pe, शून्य);
		अगर (ret <= 0 || eeh_state_active(ret)) अणु
			dev_pe = dev_pe->parent;
			जारी;
		पूर्ण

		/* Frozen parent PE */
		*pe = dev_pe;
		अगर (!(dev_pe->state & EEH_PE_ISOLATED))
			phb->मुक्तze_pe(phb, dev_pe->addr);

		/* Next one */
		dev_pe = dev_pe->parent;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pnv_eeh_next_error - Retrieve next EEH error to handle
 * @pe: Affected PE
 *
 * The function is expected to be called by EEH core जबतक it माला_लो
 * special EEH event (without binding PE). The function calls to
 * OPAL APIs क्रम next error to handle. The inक्रमmational error is
 * handled पूर्णांकernally by platक्रमm. However, the dead IOC, dead PHB,
 * fenced PHB and frozen PE should be handled by EEH core eventually.
 */
अटल पूर्णांक pnv_eeh_next_error(काष्ठा eeh_pe **pe)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा pnv_phb *phb;
	काष्ठा eeh_pe *phb_pe, *parent_pe;
	__be64 frozen_pe_no;
	__be16 err_type, severity;
	दीर्घ rc;
	पूर्णांक state, ret = EEH_NEXT_ERR_NONE;

	/*
	 * While running here, it's safe to purge the event queue. The
	 * event should still be masked.
	 */
	eeh_हटाओ_event(शून्य, false);

	list_क्रम_each_entry(hose, &hose_list, list_node) अणु
		/*
		 * If the subordinate PCI buses of the PHB has been
		 * हटाओd or is exactly under error recovery, we
		 * needn't take care of it any more.
		 */
		phb = hose->निजी_data;
		phb_pe = eeh_phb_pe_get(hose);
		अगर (!phb_pe || (phb_pe->state & EEH_PE_ISOLATED))
			जारी;

		rc = opal_pci_next_error(phb->opal_id,
					 &frozen_pe_no, &err_type, &severity);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_devel("%s: Invalid return value on "
				 "PHB#%x (0x%lx) from opal_pci_next_error",
				 __func__, hose->global_number, rc);
			जारी;
		पूर्ण

		/* If the PHB करोesn't have error, stop processing */
		अगर (be16_to_cpu(err_type) == OPAL_EEH_NO_ERROR ||
		    be16_to_cpu(severity) == OPAL_EEH_SEV_NO_ERROR) अणु
			pr_devel("%s: No error found on PHB#%x\n",
				 __func__, hose->global_number);
			जारी;
		पूर्ण

		/*
		 * Processing the error. We're expecting the error with
		 * highest priority reported upon multiple errors on the
		 * specअगरic PHB.
		 */
		pr_devel("%s: Error (%d, %d, %llu) on PHB#%x\n",
			__func__, be16_to_cpu(err_type),
			be16_to_cpu(severity), be64_to_cpu(frozen_pe_no),
			hose->global_number);
		चयन (be16_to_cpu(err_type)) अणु
		हाल OPAL_EEH_IOC_ERROR:
			अगर (be16_to_cpu(severity) == OPAL_EEH_SEV_IOC_DEAD) अणु
				pr_err("EEH: dead IOC detected\n");
				ret = EEH_NEXT_ERR_DEAD_IOC;
			पूर्ण अन्यथा अगर (be16_to_cpu(severity) == OPAL_EEH_SEV_INF) अणु
				pr_info("EEH: IOC informative error "
					"detected\n");
				pnv_eeh_get_and_dump_hub_diag(hose);
				ret = EEH_NEXT_ERR_NONE;
			पूर्ण

			अवरोध;
		हाल OPAL_EEH_PHB_ERROR:
			अगर (be16_to_cpu(severity) == OPAL_EEH_SEV_PHB_DEAD) अणु
				*pe = phb_pe;
				pr_err("EEH: dead PHB#%x detected, "
				       "location: %s\n",
					hose->global_number,
					eeh_pe_loc_get(phb_pe));
				ret = EEH_NEXT_ERR_DEAD_PHB;
			पूर्ण अन्यथा अगर (be16_to_cpu(severity) ==
				   OPAL_EEH_SEV_PHB_FENCED) अणु
				*pe = phb_pe;
				pr_err("EEH: Fenced PHB#%x detected, "
				       "location: %s\n",
					hose->global_number,
					eeh_pe_loc_get(phb_pe));
				ret = EEH_NEXT_ERR_FENCED_PHB;
			पूर्ण अन्यथा अगर (be16_to_cpu(severity) == OPAL_EEH_SEV_INF) अणु
				pr_info("EEH: PHB#%x informative error "
					"detected, location: %s\n",
					hose->global_number,
					eeh_pe_loc_get(phb_pe));
				pnv_eeh_get_phb_diag(phb_pe);
				pnv_pci_dump_phb_diag_data(hose, phb_pe->data);
				ret = EEH_NEXT_ERR_NONE;
			पूर्ण

			अवरोध;
		हाल OPAL_EEH_PE_ERROR:
			/*
			 * If we can't find the corresponding PE, we
			 * just try to unमुक्तze.
			 */
			अगर (pnv_eeh_get_pe(hose,
				be64_to_cpu(frozen_pe_no), pe)) अणु
				pr_info("EEH: Clear non-existing PHB#%x-PE#%llx\n",
					hose->global_number, be64_to_cpu(frozen_pe_no));
				pr_info("EEH: PHB location: %s\n",
					eeh_pe_loc_get(phb_pe));

				/* Dump PHB diag-data */
				rc = opal_pci_get_phb_diag_data2(phb->opal_id,
					phb->diag_data, phb->diag_data_size);
				अगर (rc == OPAL_SUCCESS)
					pnv_pci_dump_phb_diag_data(hose,
							phb->diag_data);

				/* Try best to clear it */
				opal_pci_eeh_मुक्तze_clear(phb->opal_id,
					be64_to_cpu(frozen_pe_no),
					OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);
				ret = EEH_NEXT_ERR_NONE;
			पूर्ण अन्यथा अगर ((*pe)->state & EEH_PE_ISOLATED ||
				   eeh_pe_passed(*pe)) अणु
				ret = EEH_NEXT_ERR_NONE;
			पूर्ण अन्यथा अणु
				pr_err("EEH: Frozen PE#%x "
				       "on PHB#%x detected\n",
				       (*pe)->addr,
					(*pe)->phb->global_number);
				pr_err("EEH: PE location: %s, "
				       "PHB location: %s\n",
				       eeh_pe_loc_get(*pe),
				       eeh_pe_loc_get(phb_pe));
				ret = EEH_NEXT_ERR_FROZEN_PE;
			पूर्ण

			अवरोध;
		शेष:
			pr_warn("%s: Unexpected error type %d\n",
				__func__, be16_to_cpu(err_type));
		पूर्ण

		/*
		 * EEH core will try recover from fenced PHB or
		 * frozen PE. In the समय क्रम frozen PE, EEH core
		 * enable IO path क्रम that beक्रमe collecting logs,
		 * but it ruins the site. So we have to dump the
		 * log in advance here.
		 */
		अगर ((ret == EEH_NEXT_ERR_FROZEN_PE  ||
		    ret == EEH_NEXT_ERR_FENCED_PHB) &&
		    !((*pe)->state & EEH_PE_ISOLATED)) अणु
			eeh_pe_mark_isolated(*pe);
			pnv_eeh_get_phb_diag(*pe);

			अगर (eeh_has_flag(EEH_EARLY_DUMP_LOG))
				pnv_pci_dump_phb_diag_data((*pe)->phb,
							   (*pe)->data);
		पूर्ण

		/*
		 * We probably have the frozen parent PE out there and
		 * we need have to handle frozen parent PE firstly.
		 */
		अगर (ret == EEH_NEXT_ERR_FROZEN_PE) अणु
			parent_pe = (*pe)->parent;
			जबतक (parent_pe) अणु
				/* Hit the उच्चमानing ? */
				अगर (parent_pe->type & EEH_PE_PHB)
					अवरोध;

				/* Frozen parent PE ? */
				state = eeh_ops->get_state(parent_pe, शून्य);
				अगर (state > 0 && !eeh_state_active(state))
					*pe = parent_pe;

				/* Next parent level */
				parent_pe = parent_pe->parent;
			पूर्ण

			/* We possibly migrate to another PE */
			eeh_pe_mark_isolated(*pe);
		पूर्ण

		/*
		 * If we have no errors on the specअगरic PHB or only
		 * inक्रमmative error there, we जारी poking it.
		 * Otherwise, we need actions to be taken by upper
		 * layer.
		 */
		अगर (ret > EEH_NEXT_ERR_INF)
			अवरोध;
	पूर्ण

	/* Unmask the event */
	अगर (ret == EEH_NEXT_ERR_NONE && eeh_enabled())
		enable_irq(eeh_event_irq);

	वापस ret;
पूर्ण

अटल पूर्णांक pnv_eeh_restore_config(काष्ठा eeh_dev *edev)
अणु
	काष्ठा pnv_phb *phb;
	s64 ret = 0;

	अगर (!edev)
		वापस -EEXIST;

	अगर (edev->physfn)
		वापस 0;

	phb = edev->controller->निजी_data;
	ret = opal_pci_reinit(phb->opal_id,
			      OPAL_REINIT_PCI_DEV, edev->bdfn);

	अगर (ret) अणु
		pr_warn("%s: Can't reinit PCI dev 0x%x (%lld)\n",
			__func__, edev->bdfn, ret);
		वापस -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा eeh_ops pnv_eeh_ops = अणु
	.name                   = "powernv",
	.probe			= pnv_eeh_probe,
	.set_option             = pnv_eeh_set_option,
	.get_state              = pnv_eeh_get_state,
	.reset                  = pnv_eeh_reset,
	.get_log                = pnv_eeh_get_log,
	.configure_bridge       = pnv_eeh_configure_bridge,
	.err_inject		= pnv_eeh_err_inject,
	.पढ़ो_config            = pnv_eeh_पढ़ो_config,
	.ग_लिखो_config           = pnv_eeh_ग_लिखो_config,
	.next_error		= pnv_eeh_next_error,
	.restore_config		= pnv_eeh_restore_config,
	.notअगरy_resume		= शून्य
पूर्ण;

#अगर_घोषित CONFIG_PCI_IOV
अटल व्योम pnv_pci_fixup_vf_mps(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dn *pdn = pci_get_pdn(pdev);
	पूर्णांक parent_mps;

	अगर (!pdev->is_virtfn)
		वापस;

	/* Synchronize MPS क्रम VF and PF */
	parent_mps = pcie_get_mps(pdev->physfn);
	अगर ((128 << pdev->pcie_mpss) >= parent_mps)
		pcie_set_mps(pdev, parent_mps);
	pdn->mps = pcie_get_mps(pdev);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, pnv_pci_fixup_vf_mps);
#पूर्ण_अगर /* CONFIG_PCI_IOV */

/**
 * eeh_घातernv_init - Register platक्रमm dependent EEH operations
 *
 * EEH initialization on घातernv platक्रमm. This function should be
 * called beक्रमe any EEH related functions.
 */
अटल पूर्णांक __init eeh_घातernv_init(व्योम)
अणु
	पूर्णांक max_diag_size = PNV_PCI_DIAG_BUF_SIZE;
	काष्ठा pci_controller *hose;
	काष्ठा pnv_phb *phb;
	पूर्णांक ret = -EINVAL;

	अगर (!firmware_has_feature(FW_FEATURE_OPAL)) अणु
		pr_warn("%s: OPAL is required !\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Set probe mode */
	eeh_add_flag(EEH_PROBE_MODE_DEV);

	/*
	 * P7IOC blocks PCI config access to frozen PE, but PHB3
	 * करोesn't करो that. So we have to selectively enable I/O
	 * prior to collecting error log.
	 */
	list_क्रम_each_entry(hose, &hose_list, list_node) अणु
		phb = hose->निजी_data;

		अगर (phb->model == PNV_PHB_MODEL_P7IOC)
			eeh_add_flag(EEH_ENABLE_IO_FOR_LOG);

		अगर (phb->diag_data_size > max_diag_size)
			max_diag_size = phb->diag_data_size;

		अवरोध;
	पूर्ण

	/*
	 * eeh_init() allocates the eeh_pe and its aux data buf so the
	 * size needs to be set beक्रमe calling eeh_init().
	 */
	eeh_set_pe_aux_size(max_diag_size);
	ppc_md.pcibios_bus_add_device = pnv_pcibios_bus_add_device;

	ret = eeh_init(&pnv_eeh_ops);
	अगर (!ret)
		pr_info("EEH: PowerNV platform initialized\n");
	अन्यथा
		pr_info("EEH: Failed to initialize PowerNV platform (%d)\n", ret);

	वापस ret;
पूर्ण
machine_arch_initcall(घातernv, eeh_घातernv_init);
