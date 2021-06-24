<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2001  Dave Engebretsen & Todd Inglett IBM Corporation.
 * Copyright 2001-2012 IBM Corporation.
 */

#अगर_अघोषित _POWERPC_EEH_H
#घोषणा _POWERPC_EEH_H
#अगर_घोषित __KERNEL__

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/atomic.h>

#समावेश <uapi/यंत्र/eeh.h>

काष्ठा pci_dev;
काष्ठा pci_bus;
काष्ठा pci_dn;

#अगर_घोषित CONFIG_EEH

/* EEH subप्रणाली flags */
#घोषणा EEH_ENABLED		0x01	/* EEH enabled			     */
#घोषणा EEH_FORCE_DISABLED	0x02	/* EEH disabled			     */
#घोषणा EEH_PROBE_MODE_DEV	0x04	/* From PCI device		     */
#घोषणा EEH_PROBE_MODE_DEVTREE	0x08	/* From device tree		     */
#घोषणा EEH_ENABLE_IO_FOR_LOG	0x20	/* Enable IO क्रम log		     */
#घोषणा EEH_EARLY_DUMP_LOG	0x40	/* Dump log immediately		     */

/*
 * Delay क्रम PE reset, all in ms
 *
 * PCI specअगरication has reset hold समय of 100 milliseconds.
 * We have 250 milliseconds here. The PCI bus settlement समय
 * is specअगरied as 1.5 seconds and we have 1.8 seconds.
 */
#घोषणा EEH_PE_RST_HOLD_TIME		250
#घोषणा EEH_PE_RST_SETTLE_TIME		1800

/*
 * The काष्ठा is used to trace PE related EEH functionality.
 * In theory, there will have one instance of the काष्ठा to
 * be created against particular PE. In nature, PEs correlate
 * to each other. the काष्ठा has to reflect that hierarchy in
 * order to easily pick up those affected PEs when one particular
 * PE has EEH errors.
 *
 * Also, one particular PE might be composed of PCI device, PCI
 * bus and its subordinate components. The काष्ठा also need ship
 * the inक्रमmation. Further more, one particular PE is only meaingful
 * in the corresponding PHB. Thereक्रमe, the root PEs should be created
 * against existing PHBs in on-to-one fashion.
 */
#घोषणा EEH_PE_INVALID	(1 << 0)	/* Invalid   */
#घोषणा EEH_PE_PHB	(1 << 1)	/* PHB PE    */
#घोषणा EEH_PE_DEVICE 	(1 << 2)	/* Device PE */
#घोषणा EEH_PE_BUS	(1 << 3)	/* Bus PE    */
#घोषणा EEH_PE_VF	(1 << 4)	/* VF PE     */

#घोषणा EEH_PE_ISOLATED		(1 << 0)	/* Isolated PE		*/
#घोषणा EEH_PE_RECOVERING	(1 << 1)	/* Recovering PE	*/
#घोषणा EEH_PE_CFG_BLOCKED	(1 << 2)	/* Block config access	*/
#घोषणा EEH_PE_RESET		(1 << 3)	/* PE reset in progress */

#घोषणा EEH_PE_KEEP		(1 << 8)	/* Keep PE on hotplug	*/
#घोषणा EEH_PE_CFG_RESTRICTED	(1 << 9)	/* Block config on error */
#घोषणा EEH_PE_REMOVED		(1 << 10)	/* Removed permanently	*/
#घोषणा EEH_PE_PRI_BUS		(1 << 11)	/* Cached primary bus   */

काष्ठा eeh_pe अणु
	पूर्णांक type;			/* PE type: PHB/Bus/Device	*/
	पूर्णांक state;			/* PE EEH dependent mode	*/
	पूर्णांक addr;			/* PE configuration address	*/
	काष्ठा pci_controller *phb;	/* Associated PHB		*/
	काष्ठा pci_bus *bus;		/* Top PCI bus क्रम bus PE	*/
	पूर्णांक check_count;		/* Times of ignored error	*/
	पूर्णांक मुक्तze_count;		/* Times of froze up		*/
	समय64_t tstamp;		/* Time on first-समय मुक्तze	*/
	पूर्णांक false_positives;		/* Times of reported #ff's	*/
	atomic_t pass_dev_cnt;		/* Count of passed through devs	*/
	काष्ठा eeh_pe *parent;		/* Parent PE			*/
	व्योम *data;			/* PE auxillary data		*/
	काष्ठा list_head child_list;	/* List of PEs below this PE	*/
	काष्ठा list_head child;		/* Memb. child_list/eeh_phb_pe	*/
	काष्ठा list_head edevs;		/* List of eeh_dev in this PE	*/

#अगर_घोषित CONFIG_STACKTRACE
	/*
	 * Saved stack trace. When we find a PE मुक्तze in eeh_dev_check_failure
	 * the stack trace is saved here so we can prपूर्णांक it in the recovery
	 * thपढ़ो अगर it turns out to due to a real problem rather than
	 * a hot-हटाओ.
	 *
	 * A max of 64 entries might be overसमाप्त, but it also might not be.
	 */
	अचिन्हित दीर्घ stack_trace[64];
	पूर्णांक trace_entries;
#पूर्ण_अगर /* CONFIG_STACKTRACE */
पूर्ण;

#घोषणा eeh_pe_क्रम_each_dev(pe, edev, पंचांगp) \
		list_क्रम_each_entry_safe(edev, पंचांगp, &pe->edevs, entry)

#घोषणा eeh_क्रम_each_pe(root, pe) \
	क्रम (pe = root; pe; pe = eeh_pe_next(pe, root))

अटल अंतरभूत bool eeh_pe_passed(काष्ठा eeh_pe *pe)
अणु
	वापस pe ? !!atomic_पढ़ो(&pe->pass_dev_cnt) : false;
पूर्ण

/*
 * The काष्ठा is used to trace EEH state क्रम the associated
 * PCI device node or PCI device. In future, it might
 * represent PE as well so that the EEH device to क्रमm
 * another tree except the currently existing tree of PCI
 * buses and PCI devices
 */
#घोषणा EEH_DEV_BRIDGE		(1 << 0)	/* PCI bridge		*/
#घोषणा EEH_DEV_ROOT_PORT	(1 << 1)	/* PCIe root port	*/
#घोषणा EEH_DEV_DS_PORT		(1 << 2)	/* Downstream port	*/
#घोषणा EEH_DEV_IRQ_DISABLED	(1 << 3)	/* Interrupt disabled	*/
#घोषणा EEH_DEV_DISCONNECTED	(1 << 4)	/* Removing from PE	*/

#घोषणा EEH_DEV_NO_HANDLER	(1 << 8)	/* No error handler	*/
#घोषणा EEH_DEV_SYSFS		(1 << 9)	/* Sysfs created	*/
#घोषणा EEH_DEV_REMOVED		(1 << 10)	/* Removed permanently	*/

काष्ठा eeh_dev अणु
	पूर्णांक mode;			/* EEH mode			*/
	पूर्णांक bdfn;			/* bdfn of device (क्रम cfg ops) */
	काष्ठा pci_controller *controller;
	पूर्णांक pe_config_addr;		/* PE config address		*/
	u32 config_space[16];		/* Saved PCI config space	*/
	पूर्णांक pcix_cap;			/* Saved PCIx capability	*/
	पूर्णांक pcie_cap;			/* Saved PCIe capability	*/
	पूर्णांक aer_cap;			/* Saved AER capability		*/
	पूर्णांक af_cap;			/* Saved AF capability		*/
	काष्ठा eeh_pe *pe;		/* Associated PE		*/
	काष्ठा list_head entry;		/* Membership in eeh_pe.edevs	*/
	काष्ठा list_head rmv_entry;	/* Membership in rmv_list	*/
	काष्ठा pci_dn *pdn;		/* Associated PCI device node	*/
	काष्ठा pci_dev *pdev;		/* Associated PCI device	*/
	bool in_error;			/* Error flag क्रम edev		*/

	/* VF specअगरic properties */
	काष्ठा pci_dev *physfn;		/* Associated SRIOV PF		*/
	पूर्णांक vf_index;			/* Index of this VF 		*/
पूर्ण;

/* "fmt" must be a simple literal string */
#घोषणा EEH_EDEV_PRINT(level, edev, fmt, ...) \
	pr_##level("PCI %04x:%02x:%02x.%x#%04x: EEH: " fmt, \
	(edev)->controller->global_number, PCI_BUSNO((edev)->bdfn), \
	PCI_SLOT((edev)->bdfn), PCI_FUNC((edev)->bdfn), \
	((edev)->pe ? (edev)->pe_config_addr : 0xffff), ##__VA_ARGS__)
#घोषणा eeh_edev_dbg(edev, fmt, ...) EEH_EDEV_PRINT(debug, (edev), fmt, ##__VA_ARGS__)
#घोषणा eeh_edev_info(edev, fmt, ...) EEH_EDEV_PRINT(info, (edev), fmt, ##__VA_ARGS__)
#घोषणा eeh_edev_warn(edev, fmt, ...) EEH_EDEV_PRINT(warn, (edev), fmt, ##__VA_ARGS__)
#घोषणा eeh_edev_err(edev, fmt, ...) EEH_EDEV_PRINT(err, (edev), fmt, ##__VA_ARGS__)

अटल अंतरभूत काष्ठा pci_dn *eeh_dev_to_pdn(काष्ठा eeh_dev *edev)
अणु
	वापस edev ? edev->pdn : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा pci_dev *eeh_dev_to_pci_dev(काष्ठा eeh_dev *edev)
अणु
	वापस edev ? edev->pdev : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा eeh_pe *eeh_dev_to_pe(काष्ठा eeh_dev* edev)
अणु
	वापस edev ? edev->pe : शून्य;
पूर्ण

/* Return values from eeh_ops::next_error */
क्रमागत अणु
	EEH_NEXT_ERR_NONE = 0,
	EEH_NEXT_ERR_INF,
	EEH_NEXT_ERR_FROZEN_PE,
	EEH_NEXT_ERR_FENCED_PHB,
	EEH_NEXT_ERR_DEAD_PHB,
	EEH_NEXT_ERR_DEAD_IOC
पूर्ण;

/*
 * The काष्ठा is used to trace the रेजिस्टरed EEH operation
 * callback functions. Actually, those operation callback
 * functions are heavily platक्रमm dependent. That means the
 * platक्रमm should रेजिस्टर its own EEH operation callback
 * functions beक्रमe any EEH further operations.
 */
#घोषणा EEH_OPT_DISABLE		0	/* EEH disable	*/
#घोषणा EEH_OPT_ENABLE		1	/* EEH enable	*/
#घोषणा EEH_OPT_THAW_MMIO	2	/* MMIO enable	*/
#घोषणा EEH_OPT_THAW_DMA	3	/* DMA enable	*/
#घोषणा EEH_OPT_FREEZE_PE	4	/* Freeze PE	*/
#घोषणा EEH_STATE_UNAVAILABLE	(1 << 0)	/* State unavailable	*/
#घोषणा EEH_STATE_NOT_SUPPORT	(1 << 1)	/* EEH not supported	*/
#घोषणा EEH_STATE_RESET_ACTIVE	(1 << 2)	/* Active reset		*/
#घोषणा EEH_STATE_MMIO_ACTIVE	(1 << 3)	/* Active MMIO		*/
#घोषणा EEH_STATE_DMA_ACTIVE	(1 << 4)	/* Active DMA		*/
#घोषणा EEH_STATE_MMIO_ENABLED	(1 << 5)	/* MMIO enabled		*/
#घोषणा EEH_STATE_DMA_ENABLED	(1 << 6)	/* DMA enabled		*/
#घोषणा EEH_RESET_DEACTIVATE	0	/* Deactivate the PE reset	*/
#घोषणा EEH_RESET_HOT		1	/* Hot reset			*/
#घोषणा EEH_RESET_FUNDAMENTAL	3	/* Fundamental reset		*/
#घोषणा EEH_LOG_TEMP		1	/* EEH temporary error log	*/
#घोषणा EEH_LOG_PERM		2	/* EEH permanent error log	*/

काष्ठा eeh_ops अणु
	अक्षर *name;
	काष्ठा eeh_dev *(*probe)(काष्ठा pci_dev *pdev);
	पूर्णांक (*set_option)(काष्ठा eeh_pe *pe, पूर्णांक option);
	पूर्णांक (*get_state)(काष्ठा eeh_pe *pe, पूर्णांक *delay);
	पूर्णांक (*reset)(काष्ठा eeh_pe *pe, पूर्णांक option);
	पूर्णांक (*get_log)(काष्ठा eeh_pe *pe, पूर्णांक severity, अक्षर *drv_log, अचिन्हित दीर्घ len);
	पूर्णांक (*configure_bridge)(काष्ठा eeh_pe *pe);
	पूर्णांक (*err_inject)(काष्ठा eeh_pe *pe, पूर्णांक type, पूर्णांक func,
			  अचिन्हित दीर्घ addr, अचिन्हित दीर्घ mask);
	पूर्णांक (*पढ़ो_config)(काष्ठा eeh_dev *edev, पूर्णांक where, पूर्णांक size, u32 *val);
	पूर्णांक (*ग_लिखो_config)(काष्ठा eeh_dev *edev, पूर्णांक where, पूर्णांक size, u32 val);
	पूर्णांक (*next_error)(काष्ठा eeh_pe **pe);
	पूर्णांक (*restore_config)(काष्ठा eeh_dev *edev);
	पूर्णांक (*notअगरy_resume)(काष्ठा eeh_dev *edev);
पूर्ण;

बाह्य पूर्णांक eeh_subप्रणाली_flags;
बाह्य u32 eeh_max_मुक्तzes;
बाह्य bool eeh_debugfs_no_recover;
बाह्य काष्ठा eeh_ops *eeh_ops;
बाह्य raw_spinlock_t confirm_error_lock;

अटल अंतरभूत व्योम eeh_add_flag(पूर्णांक flag)
अणु
	eeh_subप्रणाली_flags |= flag;
पूर्ण

अटल अंतरभूत व्योम eeh_clear_flag(पूर्णांक flag)
अणु
	eeh_subप्रणाली_flags &= ~flag;
पूर्ण

अटल अंतरभूत bool eeh_has_flag(पूर्णांक flag)
अणु
        वापस !!(eeh_subप्रणाली_flags & flag);
पूर्ण

अटल अंतरभूत bool eeh_enabled(व्योम)
अणु
	वापस eeh_has_flag(EEH_ENABLED) && !eeh_has_flag(EEH_FORCE_DISABLED);
पूर्ण

अटल अंतरभूत व्योम eeh_serialize_lock(अचिन्हित दीर्घ *flags)
अणु
	raw_spin_lock_irqsave(&confirm_error_lock, *flags);
पूर्ण

अटल अंतरभूत व्योम eeh_serialize_unlock(अचिन्हित दीर्घ flags)
अणु
	raw_spin_unlock_irqrestore(&confirm_error_lock, flags);
पूर्ण

अटल अंतरभूत bool eeh_state_active(पूर्णांक state)
अणु
	वापस (state & (EEH_STATE_MMIO_ACTIVE | EEH_STATE_DMA_ACTIVE))
	== (EEH_STATE_MMIO_ACTIVE | EEH_STATE_DMA_ACTIVE);
पूर्ण

प्रकार व्योम (*eeh_edev_traverse_func)(काष्ठा eeh_dev *edev, व्योम *flag);
प्रकार व्योम *(*eeh_pe_traverse_func)(काष्ठा eeh_pe *pe, व्योम *flag);
व्योम eeh_set_pe_aux_size(पूर्णांक size);
पूर्णांक eeh_phb_pe_create(काष्ठा pci_controller *phb);
पूर्णांक eeh_रुको_state(काष्ठा eeh_pe *pe, पूर्णांक max_रुको);
काष्ठा eeh_pe *eeh_phb_pe_get(काष्ठा pci_controller *phb);
काष्ठा eeh_pe *eeh_pe_next(काष्ठा eeh_pe *pe, काष्ठा eeh_pe *root);
काष्ठा eeh_pe *eeh_pe_get(काष्ठा pci_controller *phb, पूर्णांक pe_no);
पूर्णांक eeh_pe_tree_insert(काष्ठा eeh_dev *edev, काष्ठा eeh_pe *new_pe_parent);
पूर्णांक eeh_pe_tree_हटाओ(काष्ठा eeh_dev *edev);
व्योम eeh_pe_update_समय_stamp(काष्ठा eeh_pe *pe);
व्योम *eeh_pe_traverse(काष्ठा eeh_pe *root,
		      eeh_pe_traverse_func fn, व्योम *flag);
व्योम eeh_pe_dev_traverse(काष्ठा eeh_pe *root,
			 eeh_edev_traverse_func fn, व्योम *flag);
व्योम eeh_pe_restore_bars(काष्ठा eeh_pe *pe);
स्थिर अक्षर *eeh_pe_loc_get(काष्ठा eeh_pe *pe);
काष्ठा pci_bus *eeh_pe_bus_get(काष्ठा eeh_pe *pe);

व्योम eeh_show_enabled(व्योम);
पूर्णांक __init eeh_init(काष्ठा eeh_ops *ops);
पूर्णांक eeh_check_failure(स्थिर अस्थिर व्योम __iomem *token);
पूर्णांक eeh_dev_check_failure(काष्ठा eeh_dev *edev);
व्योम eeh_addr_cache_init(व्योम);
व्योम eeh_probe_device(काष्ठा pci_dev *pdev);
व्योम eeh_हटाओ_device(काष्ठा pci_dev *);
पूर्णांक eeh_unमुक्तze_pe(काष्ठा eeh_pe *pe);
पूर्णांक eeh_pe_reset_and_recover(काष्ठा eeh_pe *pe);
पूर्णांक eeh_dev_खोलो(काष्ठा pci_dev *pdev);
व्योम eeh_dev_release(काष्ठा pci_dev *pdev);
काष्ठा eeh_pe *eeh_iommu_group_to_pe(काष्ठा iommu_group *group);
पूर्णांक eeh_pe_set_option(काष्ठा eeh_pe *pe, पूर्णांक option);
पूर्णांक eeh_pe_get_state(काष्ठा eeh_pe *pe);
पूर्णांक eeh_pe_reset(काष्ठा eeh_pe *pe, पूर्णांक option, bool include_passed);
पूर्णांक eeh_pe_configure(काष्ठा eeh_pe *pe);
पूर्णांक eeh_pe_inject_err(काष्ठा eeh_pe *pe, पूर्णांक type, पूर्णांक func,
		      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ mask);

/**
 * EEH_POSSIBLE_ERROR() -- test क्रम possible MMIO failure.
 *
 * If this macro yields TRUE, the caller relays to eeh_check_failure()
 * which करोes further tests out of line.
 */
#घोषणा EEH_POSSIBLE_ERROR(val, type)	((val) == (type)~0 && eeh_enabled())

/*
 * Reads from a device which has been isolated by EEH will वापस
 * all 1s.  This macro gives an all-1s value of the given size (in
 * bytes: 1, 2, or 4) क्रम comparing with the result of a पढ़ो.
 */
#घोषणा EEH_IO_ERROR_VALUE(size)	(~0U >> ((4 - (size)) * 8))

#अन्यथा /* !CONFIG_EEH */

अटल अंतरभूत bool eeh_enabled(व्योम)
अणु
        वापस false;
पूर्ण

अटल अंतरभूत व्योम eeh_show_enabled(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम eeh_dev_phb_init_dynamic(काष्ठा pci_controller *phb) अणु पूर्ण

अटल अंतरभूत पूर्णांक eeh_check_failure(स्थिर अस्थिर व्योम __iomem *token)
अणु
	वापस 0;
पूर्ण

#घोषणा eeh_dev_check_failure(x) (0)

अटल अंतरभूत व्योम eeh_addr_cache_init(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम eeh_probe_device(काष्ठा pci_dev *dev) अणु पूर्ण

अटल अंतरभूत व्योम eeh_हटाओ_device(काष्ठा pci_dev *dev) अणु पूर्ण

#घोषणा EEH_POSSIBLE_ERROR(val, type) (0)
#घोषणा EEH_IO_ERROR_VALUE(size) (-1UL)
अटल अंतरभूत पूर्णांक eeh_phb_pe_create(काष्ठा pci_controller *phb) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_EEH */

#अगर defined(CONFIG_PPC_PSERIES) && defined(CONFIG_EEH)
व्योम pseries_eeh_init_edev(काष्ठा pci_dn *pdn);
व्योम pseries_eeh_init_edev_recursive(काष्ठा pci_dn *pdn);
#अन्यथा
अटल अंतरभूत व्योम pseries_eeh_add_device_early(काष्ठा pci_dn *pdn) अणु पूर्ण
अटल अंतरभूत व्योम pseries_eeh_add_device_tree_early(काष्ठा pci_dn *pdn) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
/*
 * MMIO पढ़ो/ग_लिखो operations with EEH support.
 */
अटल अंतरभूत u8 eeh_पढ़ोb(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u8 val = in_8(addr);
	अगर (EEH_POSSIBLE_ERROR(val, u8))
		eeh_check_failure(addr);
	वापस val;
पूर्ण

अटल अंतरभूत u16 eeh_पढ़ोw(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val = in_le16(addr);
	अगर (EEH_POSSIBLE_ERROR(val, u16))
		eeh_check_failure(addr);
	वापस val;
पूर्ण

अटल अंतरभूत u32 eeh_पढ़ोl(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val = in_le32(addr);
	अगर (EEH_POSSIBLE_ERROR(val, u32))
		eeh_check_failure(addr);
	वापस val;
पूर्ण

अटल अंतरभूत u64 eeh_पढ़ोq(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 val = in_le64(addr);
	अगर (EEH_POSSIBLE_ERROR(val, u64))
		eeh_check_failure(addr);
	वापस val;
पूर्ण

अटल अंतरभूत u16 eeh_पढ़ोw_be(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u16 val = in_be16(addr);
	अगर (EEH_POSSIBLE_ERROR(val, u16))
		eeh_check_failure(addr);
	वापस val;
पूर्ण

अटल अंतरभूत u32 eeh_पढ़ोl_be(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u32 val = in_be32(addr);
	अगर (EEH_POSSIBLE_ERROR(val, u32))
		eeh_check_failure(addr);
	वापस val;
पूर्ण

अटल अंतरभूत u64 eeh_पढ़ोq_be(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	u64 val = in_be64(addr);
	अगर (EEH_POSSIBLE_ERROR(val, u64))
		eeh_check_failure(addr);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम eeh_स_नकल_fromio(व्योम *dest, स्थिर
				     अस्थिर व्योम __iomem *src,
				     अचिन्हित दीर्घ n)
अणु
	_स_नकल_fromio(dest, src, n);

	/* Look क्रम ffff's here at dest[n].  Assume that at least 4 bytes
	 * were copied. Check all four bytes.
	 */
	अगर (n >= 4 && EEH_POSSIBLE_ERROR(*((u32 *)(dest + n - 4)), u32))
		eeh_check_failure(src);
पूर्ण

/* in-string eeh macros */
अटल अंतरभूत व्योम eeh_पढ़ोsb(स्थिर अस्थिर व्योम __iomem *addr, व्योम * buf,
			      पूर्णांक ns)
अणु
	_insb(addr, buf, ns);
	अगर (EEH_POSSIBLE_ERROR((*(((u8*)buf)+ns-1)), u8))
		eeh_check_failure(addr);
पूर्ण

अटल अंतरभूत व्योम eeh_पढ़ोsw(स्थिर अस्थिर व्योम __iomem *addr, व्योम * buf,
			      पूर्णांक ns)
अणु
	_insw(addr, buf, ns);
	अगर (EEH_POSSIBLE_ERROR((*(((u16*)buf)+ns-1)), u16))
		eeh_check_failure(addr);
पूर्ण

अटल अंतरभूत व्योम eeh_पढ़ोsl(स्थिर अस्थिर व्योम __iomem *addr, व्योम * buf,
			      पूर्णांक nl)
अणु
	_insl(addr, buf, nl);
	अगर (EEH_POSSIBLE_ERROR((*(((u32*)buf)+nl-1)), u32))
		eeh_check_failure(addr);
पूर्ण


व्योम eeh_cache_debugfs_init(व्योम);

#पूर्ण_अगर /* CONFIG_PPC64 */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _POWERPC_EEH_H */
