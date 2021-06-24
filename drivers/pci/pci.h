<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DRIVERS_PCI_H
#घोषणा DRIVERS_PCI_H

#समावेश <linux/pci.h>

/* Number of possible devfns: 0.0 to 1f.7 inclusive */
#घोषणा MAX_NR_DEVFNS 256

#घोषणा PCI_FIND_CAP_TTL	48

#घोषणा PCI_VSEC_ID_INTEL_TBT	0x1234	/* Thunderbolt */

बाह्य स्थिर अचिन्हित अक्षर pcie_link_speed[];
बाह्य bool pci_early_dump;

bool pcie_cap_has_lnkctl(स्थिर काष्ठा pci_dev *dev);
bool pcie_cap_has_rtctl(स्थिर काष्ठा pci_dev *dev);

/* Functions पूर्णांकernal to the PCI core code */

पूर्णांक pci_create_sysfs_dev_files(काष्ठा pci_dev *pdev);
व्योम pci_हटाओ_sysfs_dev_files(काष्ठा pci_dev *pdev);
व्योम pci_cleanup_rom(काष्ठा pci_dev *dev);
#अगर_घोषित CONFIG_DMI
बाह्य स्थिर काष्ठा attribute_group pci_dev_smbios_attr_group;
#पूर्ण_अगर

क्रमागत pci_mmap_api अणु
	PCI_MMAP_SYSFS,	/* mmap on /sys/bus/pci/devices/<BDF>/resource<N> */
	PCI_MMAP_PROCFS	/* mmap on /proc/bus/pci/<BDF> */
पूर्ण;
पूर्णांक pci_mmap_fits(काष्ठा pci_dev *pdev, पूर्णांक resno, काष्ठा vm_area_काष्ठा *vmai,
		  क्रमागत pci_mmap_api mmap_api);

पूर्णांक pci_probe_reset_function(काष्ठा pci_dev *dev);
पूर्णांक pci_bridge_secondary_bus_reset(काष्ठा pci_dev *dev);
पूर्णांक pci_bus_error_reset(काष्ठा pci_dev *dev);

#घोषणा PCI_PM_D2_DELAY         200	/* usec; see PCIe r4.0, sec 5.9.1 */
#घोषणा PCI_PM_D3HOT_WAIT       10	/* msec */
#घोषणा PCI_PM_D3COLD_WAIT      100	/* msec */

/**
 * काष्ठा pci_platक्रमm_pm_ops - Firmware PM callbacks
 *
 * @bridge_d3: Does the bridge allow entering पूर्णांकo D3
 *
 * @is_manageable: वापसs 'true' अगर given device is घातer manageable by the
 *		   platक्रमm firmware
 *
 * @set_state: invokes the platक्रमm firmware to set the device's घातer state
 *
 * @get_state: queries the platक्रमm firmware क्रम a device's current घातer state
 *
 * @refresh_state: asks the platक्रमm to refresh the device's घातer state data
 *
 * @choose_state: वापसs PCI घातer state of given device preferred by the
 *		  platक्रमm; to be used during प्रणाली-wide transitions from a
 *		  sleeping state to the working state and vice versa
 *
 * @set_wakeup: enables/disables wakeup capability क्रम the device
 *
 * @need_resume: वापसs 'true' अगर the given device (which is currently
 *		 suspended) needs to be resumed to be configured क्रम प्रणाली
 *		 wakeup.
 *
 * If given platक्रमm is generally capable of घातer managing PCI devices, all of
 * these callbacks are mandatory.
 */
काष्ठा pci_platक्रमm_pm_ops अणु
	bool (*bridge_d3)(काष्ठा pci_dev *dev);
	bool (*is_manageable)(काष्ठा pci_dev *dev);
	पूर्णांक (*set_state)(काष्ठा pci_dev *dev, pci_घातer_t state);
	pci_घातer_t (*get_state)(काष्ठा pci_dev *dev);
	व्योम (*refresh_state)(काष्ठा pci_dev *dev);
	pci_घातer_t (*choose_state)(काष्ठा pci_dev *dev);
	पूर्णांक (*set_wakeup)(काष्ठा pci_dev *dev, bool enable);
	bool (*need_resume)(काष्ठा pci_dev *dev);
पूर्ण;

पूर्णांक pci_set_platक्रमm_pm(स्थिर काष्ठा pci_platक्रमm_pm_ops *ops);
व्योम pci_update_current_state(काष्ठा pci_dev *dev, pci_घातer_t state);
व्योम pci_refresh_घातer_state(काष्ठा pci_dev *dev);
पूर्णांक pci_घातer_up(काष्ठा pci_dev *dev);
व्योम pci_disable_enabled_device(काष्ठा pci_dev *dev);
पूर्णांक pci_finish_runसमय_suspend(काष्ठा pci_dev *dev);
व्योम pcie_clear_device_status(काष्ठा pci_dev *dev);
व्योम pcie_clear_root_pme_status(काष्ठा pci_dev *dev);
bool pci_check_pme_status(काष्ठा pci_dev *dev);
व्योम pci_pme_wakeup_bus(काष्ठा pci_bus *bus);
पूर्णांक __pci_pme_wakeup(काष्ठा pci_dev *dev, व्योम *ign);
व्योम pci_pme_restore(काष्ठा pci_dev *dev);
bool pci_dev_need_resume(काष्ठा pci_dev *dev);
व्योम pci_dev_adjust_pme(काष्ठा pci_dev *dev);
व्योम pci_dev_complete_resume(काष्ठा pci_dev *pci_dev);
व्योम pci_config_pm_runसमय_get(काष्ठा pci_dev *dev);
व्योम pci_config_pm_runसमय_put(काष्ठा pci_dev *dev);
व्योम pci_pm_init(काष्ठा pci_dev *dev);
व्योम pci_ea_init(काष्ठा pci_dev *dev);
व्योम pci_msi_init(काष्ठा pci_dev *dev);
व्योम pci_msix_init(काष्ठा pci_dev *dev);
व्योम pci_allocate_cap_save_buffers(काष्ठा pci_dev *dev);
व्योम pci_मुक्त_cap_save_buffers(काष्ठा pci_dev *dev);
bool pci_bridge_d3_possible(काष्ठा pci_dev *dev);
व्योम pci_bridge_d3_update(काष्ठा pci_dev *dev);
व्योम pci_bridge_रुको_क्रम_secondary_bus(काष्ठा pci_dev *dev);

अटल अंतरभूत व्योम pci_wakeup_event(काष्ठा pci_dev *dev)
अणु
	/* Wait 100 ms beक्रमe the प्रणाली can be put पूर्णांकo a sleep state. */
	pm_wakeup_event(&dev->dev, 100);
पूर्ण

अटल अंतरभूत bool pci_has_subordinate(काष्ठा pci_dev *pci_dev)
अणु
	वापस !!(pci_dev->subordinate);
पूर्ण

अटल अंतरभूत bool pci_घातer_manageable(काष्ठा pci_dev *pci_dev)
अणु
	/*
	 * Currently we allow normal PCI devices and PCI bridges transition
	 * पूर्णांकo D3 अगर their bridge_d3 is set.
	 */
	वापस !pci_has_subordinate(pci_dev) || pci_dev->bridge_d3;
पूर्ण

अटल अंतरभूत bool pcie_करोwnstream_port(स्थिर काष्ठा pci_dev *dev)
अणु
	पूर्णांक type = pci_pcie_type(dev);

	वापस type == PCI_EXP_TYPE_ROOT_PORT ||
	       type == PCI_EXP_TYPE_DOWNSTREAM ||
	       type == PCI_EXP_TYPE_PCIE_BRIDGE;
पूर्ण

व्योम pci_vpd_init(काष्ठा pci_dev *dev);
व्योम pci_vpd_release(काष्ठा pci_dev *dev);
बाह्य स्थिर काष्ठा attribute_group pci_dev_vpd_attr_group;

/* PCI Virtual Channel */
पूर्णांक pci_save_vc_state(काष्ठा pci_dev *dev);
व्योम pci_restore_vc_state(काष्ठा pci_dev *dev);
व्योम pci_allocate_vc_save_buffers(काष्ठा pci_dev *dev);

/* PCI /proc functions */
#अगर_घोषित CONFIG_PROC_FS
पूर्णांक pci_proc_attach_device(काष्ठा pci_dev *dev);
पूर्णांक pci_proc_detach_device(काष्ठा pci_dev *dev);
पूर्णांक pci_proc_detach_bus(काष्ठा pci_bus *bus);
#अन्यथा
अटल अंतरभूत पूर्णांक pci_proc_attach_device(काष्ठा pci_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_proc_detach_device(काष्ठा pci_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_proc_detach_bus(काष्ठा pci_bus *bus) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* Functions क्रम PCI Hotplug drivers to use */
पूर्णांक pci_hp_add_bridge(काष्ठा pci_dev *dev);

#अगर_घोषित HAVE_PCI_LEGACY
व्योम pci_create_legacy_files(काष्ठा pci_bus *bus);
व्योम pci_हटाओ_legacy_files(काष्ठा pci_bus *bus);
#अन्यथा
अटल अंतरभूत व्योम pci_create_legacy_files(काष्ठा pci_bus *bus) अणु वापस; पूर्ण
अटल अंतरभूत व्योम pci_हटाओ_legacy_files(काष्ठा pci_bus *bus) अणु वापस; पूर्ण
#पूर्ण_अगर

/* Lock क्रम पढ़ो/ग_लिखो access to pci device and bus lists */
बाह्य काष्ठा rw_semaphore pci_bus_sem;
बाह्य काष्ठा mutex pci_slot_mutex;

बाह्य raw_spinlock_t pci_lock;

बाह्य अचिन्हित पूर्णांक pci_pm_d3hot_delay;

#अगर_घोषित CONFIG_PCI_MSI
व्योम pci_no_msi(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pci_no_msi(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम pci_पुनः_स्मृति_get_opt(अक्षर *);

अटल अंतरभूत पूर्णांक pci_no_d1d2(काष्ठा pci_dev *dev)
अणु
	अचिन्हित पूर्णांक parent_dstates = 0;

	अगर (dev->bus->self)
		parent_dstates = dev->bus->self->no_d1d2;
	वापस (dev->no_d1d2 || parent_dstates);

पूर्ण
बाह्य स्थिर काष्ठा attribute_group *pci_dev_groups[];
बाह्य स्थिर काष्ठा attribute_group *pcibus_groups[];
बाह्य स्थिर काष्ठा device_type pci_dev_type;
बाह्य स्थिर काष्ठा attribute_group *pci_bus_groups[];

बाह्य अचिन्हित दीर्घ pci_hotplug_io_size;
बाह्य अचिन्हित दीर्घ pci_hotplug_mmio_size;
बाह्य अचिन्हित दीर्घ pci_hotplug_mmio_pref_size;
बाह्य अचिन्हित दीर्घ pci_hotplug_bus_size;

/**
 * pci_match_one_device - Tell अगर a PCI device काष्ठाure has a matching
 *			  PCI device id काष्ठाure
 * @id: single PCI device id काष्ठाure to match
 * @dev: the PCI device काष्ठाure to match against
 *
 * Returns the matching pci_device_id काष्ठाure or %शून्य अगर there is no match.
 */
अटल अंतरभूत स्थिर काष्ठा pci_device_id *
pci_match_one_device(स्थिर काष्ठा pci_device_id *id, स्थिर काष्ठा pci_dev *dev)
अणु
	अगर ((id->venकरोr == PCI_ANY_ID || id->venकरोr == dev->venकरोr) &&
	    (id->device == PCI_ANY_ID || id->device == dev->device) &&
	    (id->subvenकरोr == PCI_ANY_ID || id->subvenकरोr == dev->subप्रणाली_venकरोr) &&
	    (id->subdevice == PCI_ANY_ID || id->subdevice == dev->subप्रणाली_device) &&
	    !((id->class ^ dev->class) & id->class_mask))
		वापस id;
	वापस शून्य;
पूर्ण

/* PCI slot sysfs helper code */
#घोषणा to_pci_slot(s) container_of(s, काष्ठा pci_slot, kobj)

बाह्य काष्ठा kset *pci_slots_kset;

काष्ठा pci_slot_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा pci_slot *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा pci_slot *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;
#घोषणा to_pci_slot_attr(s) container_of(s, काष्ठा pci_slot_attribute, attr)

क्रमागत pci_bar_type अणु
	pci_bar_unknown,	/* Standard PCI BAR probe */
	pci_bar_io,		/* An I/O port BAR */
	pci_bar_mem32,		/* A 32-bit memory BAR */
	pci_bar_mem64,		/* A 64-bit memory BAR */
पूर्ण;

काष्ठा device *pci_get_host_bridge_device(काष्ठा pci_dev *dev);
व्योम pci_put_host_bridge_device(काष्ठा device *dev);

पूर्णांक pci_configure_extended_tags(काष्ठा pci_dev *dev, व्योम *ign);
bool pci_bus_पढ़ो_dev_venकरोr_id(काष्ठा pci_bus *bus, पूर्णांक devfn, u32 *pl,
				पूर्णांक crs_समयout);
bool pci_bus_generic_पढ़ो_dev_venकरोr_id(काष्ठा pci_bus *bus, पूर्णांक devfn, u32 *pl,
					पूर्णांक crs_समयout);
पूर्णांक pci_idt_bus_quirk(काष्ठा pci_bus *bus, पूर्णांक devfn, u32 *pl, पूर्णांक crs_समयout);

पूर्णांक pci_setup_device(काष्ठा pci_dev *dev);
पूर्णांक __pci_पढ़ो_base(काष्ठा pci_dev *dev, क्रमागत pci_bar_type type,
		    काष्ठा resource *res, अचिन्हित पूर्णांक reg);
व्योम pci_configure_ari(काष्ठा pci_dev *dev);
व्योम __pci_bus_size_bridges(काष्ठा pci_bus *bus,
			काष्ठा list_head *पुनः_स्मृति_head);
व्योम __pci_bus_assign_resources(स्थिर काष्ठा pci_bus *bus,
				काष्ठा list_head *पुनः_स्मृति_head,
				काष्ठा list_head *fail_head);
bool pci_bus_clip_resource(काष्ठा pci_dev *dev, पूर्णांक idx);

व्योम pci_reassigndev_resource_alignment(काष्ठा pci_dev *dev);
व्योम pci_disable_bridge_winकरोw(काष्ठा pci_dev *dev);
काष्ठा pci_bus *pci_bus_get(काष्ठा pci_bus *bus);
व्योम pci_bus_put(काष्ठा pci_bus *bus);

/* PCIe link inक्रमmation from Link Capabilities 2 */
#घोषणा PCIE_LNKCAP2_SLS2SPEED(lnkcap2) \
	((lnkcap2) & PCI_EXP_LNKCAP2_SLS_64_0GB ? PCIE_SPEED_64_0GT : \
	 (lnkcap2) & PCI_EXP_LNKCAP2_SLS_32_0GB ? PCIE_SPEED_32_0GT : \
	 (lnkcap2) & PCI_EXP_LNKCAP2_SLS_16_0GB ? PCIE_SPEED_16_0GT : \
	 (lnkcap2) & PCI_EXP_LNKCAP2_SLS_8_0GB ? PCIE_SPEED_8_0GT : \
	 (lnkcap2) & PCI_EXP_LNKCAP2_SLS_5_0GB ? PCIE_SPEED_5_0GT : \
	 (lnkcap2) & PCI_EXP_LNKCAP2_SLS_2_5GB ? PCIE_SPEED_2_5GT : \
	 PCI_SPEED_UNKNOWN)

/* PCIe speed to Mb/s reduced by encoding overhead */
#घोषणा PCIE_SPEED2MBS_ENC(speed) \
	((speed) == PCIE_SPEED_64_0GT ? 64000*128/130 : \
	 (speed) == PCIE_SPEED_32_0GT ? 32000*128/130 : \
	 (speed) == PCIE_SPEED_16_0GT ? 16000*128/130 : \
	 (speed) == PCIE_SPEED_8_0GT  ?  8000*128/130 : \
	 (speed) == PCIE_SPEED_5_0GT  ?  5000*8/10 : \
	 (speed) == PCIE_SPEED_2_5GT  ?  2500*8/10 : \
	 0)

स्थिर अक्षर *pci_speed_string(क्रमागत pci_bus_speed speed);
क्रमागत pci_bus_speed pcie_get_speed_cap(काष्ठा pci_dev *dev);
क्रमागत pcie_link_width pcie_get_width_cap(काष्ठा pci_dev *dev);
u32 pcie_bandwidth_capable(काष्ठा pci_dev *dev, क्रमागत pci_bus_speed *speed,
			   क्रमागत pcie_link_width *width);
व्योम __pcie_prपूर्णांक_link_status(काष्ठा pci_dev *dev, bool verbose);
व्योम pcie_report_करोwntraining(काष्ठा pci_dev *dev);
व्योम pcie_update_link_speed(काष्ठा pci_bus *bus, u16 link_status);

/* Single Root I/O Virtualization */
काष्ठा pci_sriov अणु
	पूर्णांक		pos;		/* Capability position */
	पूर्णांक		nres;		/* Number of resources */
	u32		cap;		/* SR-IOV Capabilities */
	u16		ctrl;		/* SR-IOV Control */
	u16		total_VFs;	/* Total VFs associated with the PF */
	u16		initial_VFs;	/* Initial VFs associated with the PF */
	u16		num_VFs;	/* Number of VFs available */
	u16		offset;		/* First VF Routing ID offset */
	u16		stride;		/* Following VF stride */
	u16		vf_device;	/* VF device ID */
	u32		pgsz;		/* Page size क्रम BAR alignment */
	u8		link;		/* Function Dependency Link */
	u8		max_VF_buses;	/* Max buses consumed by VFs */
	u16		driver_max_VFs;	/* Max num VFs driver supports */
	काष्ठा pci_dev	*dev;		/* Lowest numbered PF */
	काष्ठा pci_dev	*self;		/* This PF */
	u32		class;		/* VF device */
	u8		hdr_type;	/* VF header type */
	u16		subप्रणाली_venकरोr; /* VF subप्रणाली venकरोr */
	u16		subप्रणाली_device; /* VF subप्रणाली device */
	resource_माप_प्रकार	barsz[PCI_SRIOV_NUM_BARS];	/* VF BAR size */
	bool		drivers_स्वतःprobe; /* Auto probing of VFs by driver */
पूर्ण;

/**
 * pci_dev_set_io_state - Set the new error state अगर possible.
 *
 * @dev - pci device to set new error_state
 * @new - the state we want dev to be in
 *
 * Must be called with device_lock held.
 *
 * Returns true अगर state has been changed to the requested state.
 */
अटल अंतरभूत bool pci_dev_set_io_state(काष्ठा pci_dev *dev,
					pci_channel_state_t new)
अणु
	bool changed = false;

	device_lock_निश्चित(&dev->dev);
	चयन (new) अणु
	हाल pci_channel_io_perm_failure:
		चयन (dev->error_state) अणु
		हाल pci_channel_io_frozen:
		हाल pci_channel_io_normal:
		हाल pci_channel_io_perm_failure:
			changed = true;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल pci_channel_io_frozen:
		चयन (dev->error_state) अणु
		हाल pci_channel_io_frozen:
		हाल pci_channel_io_normal:
			changed = true;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल pci_channel_io_normal:
		चयन (dev->error_state) अणु
		हाल pci_channel_io_frozen:
		हाल pci_channel_io_normal:
			changed = true;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (changed)
		dev->error_state = new;
	वापस changed;
पूर्ण

अटल अंतरभूत पूर्णांक pci_dev_set_disconnected(काष्ठा pci_dev *dev, व्योम *unused)
अणु
	device_lock(&dev->dev);
	pci_dev_set_io_state(dev, pci_channel_io_perm_failure);
	device_unlock(&dev->dev);

	वापस 0;
पूर्ण

अटल अंतरभूत bool pci_dev_is_disconnected(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस dev->error_state == pci_channel_io_perm_failure;
पूर्ण

/* pci_dev priv_flags */
#घोषणा PCI_DEV_ADDED 0

अटल अंतरभूत व्योम pci_dev_assign_added(काष्ठा pci_dev *dev, bool added)
अणु
	assign_bit(PCI_DEV_ADDED, &dev->priv_flags, added);
पूर्ण

अटल अंतरभूत bool pci_dev_is_added(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस test_bit(PCI_DEV_ADDED, &dev->priv_flags);
पूर्ण

#अगर_घोषित CONFIG_PCIEAER
#समावेश <linux/aer.h>

#घोषणा AER_MAX_MULTI_ERR_DEVICES	5	/* Not likely to have more */

काष्ठा aer_err_info अणु
	काष्ठा pci_dev *dev[AER_MAX_MULTI_ERR_DEVICES];
	पूर्णांक error_dev_num;

	अचिन्हित पूर्णांक id:16;

	अचिन्हित पूर्णांक severity:2;	/* 0:NONFATAL | 1:FATAL | 2:COR */
	अचिन्हित पूर्णांक __pad1:5;
	अचिन्हित पूर्णांक multi_error_valid:1;

	अचिन्हित पूर्णांक first_error:5;
	अचिन्हित पूर्णांक __pad2:2;
	अचिन्हित पूर्णांक tlp_header_valid:1;

	अचिन्हित पूर्णांक status;		/* COR/UNCOR Error Status */
	अचिन्हित पूर्णांक mask;		/* COR/UNCOR Error Mask */
	काष्ठा aer_header_log_regs tlp;	/* TLP Header */
पूर्ण;

पूर्णांक aer_get_device_error_info(काष्ठा pci_dev *dev, काष्ठा aer_err_info *info);
व्योम aer_prपूर्णांक_error(काष्ठा pci_dev *dev, काष्ठा aer_err_info *info);
#पूर्ण_अगर	/* CONFIG_PCIEAER */

#अगर_घोषित CONFIG_PCIEPORTBUS
/* Cached RCEC Endpoपूर्णांक Association */
काष्ठा rcec_ea अणु
	u8		nextbusn;
	u8		lastbusn;
	u32		biपंचांगap;
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIE_DPC
व्योम pci_save_dpc_state(काष्ठा pci_dev *dev);
व्योम pci_restore_dpc_state(काष्ठा pci_dev *dev);
व्योम pci_dpc_init(काष्ठा pci_dev *pdev);
व्योम dpc_process_error(काष्ठा pci_dev *pdev);
pci_ers_result_t dpc_reset_link(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत व्योम pci_save_dpc_state(काष्ठा pci_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम pci_restore_dpc_state(काष्ठा pci_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम pci_dpc_init(काष्ठा pci_dev *pdev) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIEPORTBUS
व्योम pci_rcec_init(काष्ठा pci_dev *dev);
व्योम pci_rcec_निकास(काष्ठा pci_dev *dev);
व्योम pcie_link_rcec(काष्ठा pci_dev *rcec);
व्योम pcie_walk_rcec(काष्ठा pci_dev *rcec,
		    पूर्णांक (*cb)(काष्ठा pci_dev *, व्योम *),
		    व्योम *userdata);
#अन्यथा
अटल अंतरभूत व्योम pci_rcec_init(काष्ठा pci_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम pci_rcec_निकास(काष्ठा pci_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम pcie_link_rcec(काष्ठा pci_dev *rcec) अणुपूर्ण
अटल अंतरभूत व्योम pcie_walk_rcec(काष्ठा pci_dev *rcec,
				  पूर्णांक (*cb)(काष्ठा pci_dev *, व्योम *),
				  व्योम *userdata) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_ATS
/* Address Translation Service */
व्योम pci_ats_init(काष्ठा pci_dev *dev);
व्योम pci_restore_ats_state(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत व्योम pci_ats_init(काष्ठा pci_dev *d) अणु पूर्ण
अटल अंतरभूत व्योम pci_restore_ats_state(काष्ठा pci_dev *dev) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_ATS */

#अगर_घोषित CONFIG_PCI_PRI
व्योम pci_pri_init(काष्ठा pci_dev *dev);
व्योम pci_restore_pri_state(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत व्योम pci_pri_init(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pci_restore_pri_state(काष्ठा pci_dev *pdev) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_PASID
व्योम pci_pasid_init(काष्ठा pci_dev *dev);
व्योम pci_restore_pasid_state(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत व्योम pci_pasid_init(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pci_restore_pasid_state(काष्ठा pci_dev *pdev) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_IOV
पूर्णांक pci_iov_init(काष्ठा pci_dev *dev);
व्योम pci_iov_release(काष्ठा pci_dev *dev);
व्योम pci_iov_हटाओ(काष्ठा pci_dev *dev);
व्योम pci_iov_update_resource(काष्ठा pci_dev *dev, पूर्णांक resno);
resource_माप_प्रकार pci_sriov_resource_alignment(काष्ठा pci_dev *dev, पूर्णांक resno);
व्योम pci_restore_iov_state(काष्ठा pci_dev *dev);
पूर्णांक pci_iov_bus_range(काष्ठा pci_bus *bus);
बाह्य स्थिर काष्ठा attribute_group sriov_pf_dev_attr_group;
बाह्य स्थिर काष्ठा attribute_group sriov_vf_dev_attr_group;
#अन्यथा
अटल अंतरभूत पूर्णांक pci_iov_init(काष्ठा pci_dev *dev)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम pci_iov_release(काष्ठा pci_dev *dev)

अणु
पूर्ण
अटल अंतरभूत व्योम pci_iov_हटाओ(काष्ठा pci_dev *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम pci_restore_iov_state(काष्ठा pci_dev *dev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक pci_iov_bus_range(काष्ठा pci_bus *bus)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI_IOV */

#अगर_घोषित CONFIG_PCIE_PTM
व्योम pci_save_pपंचांग_state(काष्ठा pci_dev *dev);
व्योम pci_restore_pपंचांग_state(काष्ठा pci_dev *dev);
व्योम pci_disable_pपंचांग(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत व्योम pci_save_pपंचांग_state(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pci_restore_pपंचांग_state(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pci_disable_pपंचांग(काष्ठा pci_dev *dev) अणु पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ pci_cardbus_resource_alignment(काष्ठा resource *);

अटल अंतरभूत resource_माप_प्रकार pci_resource_alignment(काष्ठा pci_dev *dev,
						     काष्ठा resource *res)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	पूर्णांक resno = res - dev->resource;

	अगर (resno >= PCI_IOV_RESOURCES && resno <= PCI_IOV_RESOURCE_END)
		वापस pci_sriov_resource_alignment(dev, resno);
#पूर्ण_अगर
	अगर (dev->class >> 8 == PCI_CLASS_BRIDGE_CARDBUS)
		वापस pci_cardbus_resource_alignment(res);
	वापस resource_alignment(res);
पूर्ण

व्योम pci_acs_init(काष्ठा pci_dev *dev);
#अगर_घोषित CONFIG_PCI_QUIRKS
पूर्णांक pci_dev_specअगरic_acs_enabled(काष्ठा pci_dev *dev, u16 acs_flags);
पूर्णांक pci_dev_specअगरic_enable_acs(काष्ठा pci_dev *dev);
पूर्णांक pci_dev_specअगरic_disable_acs_redir(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक pci_dev_specअगरic_acs_enabled(काष्ठा pci_dev *dev,
					       u16 acs_flags)
अणु
	वापस -ENOTTY;
पूर्ण
अटल अंतरभूत पूर्णांक pci_dev_specअगरic_enable_acs(काष्ठा pci_dev *dev)
अणु
	वापस -ENOTTY;
पूर्ण
अटल अंतरभूत पूर्णांक pci_dev_specअगरic_disable_acs_redir(काष्ठा pci_dev *dev)
अणु
	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर

/* PCI error reporting and recovery */
pci_ers_result_t pcie_करो_recovery(काष्ठा pci_dev *dev,
		pci_channel_state_t state,
		pci_ers_result_t (*reset_subordinates)(काष्ठा pci_dev *pdev));

bool pcie_रुको_क्रम_link(काष्ठा pci_dev *pdev, bool active);
#अगर_घोषित CONFIG_PCIEASPM
व्योम pcie_aspm_init_link_state(काष्ठा pci_dev *pdev);
व्योम pcie_aspm_निकास_link_state(काष्ठा pci_dev *pdev);
व्योम pcie_aspm_pm_state_change(काष्ठा pci_dev *pdev);
व्योम pcie_aspm_घातersave_config_link(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत व्योम pcie_aspm_init_link_state(काष्ठा pci_dev *pdev) अणु पूर्ण
अटल अंतरभूत व्योम pcie_aspm_निकास_link_state(काष्ठा pci_dev *pdev) अणु पूर्ण
अटल अंतरभूत व्योम pcie_aspm_pm_state_change(काष्ठा pci_dev *pdev) अणु पूर्ण
अटल अंतरभूत व्योम pcie_aspm_घातersave_config_link(काष्ठा pci_dev *pdev) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIE_ECRC
व्योम pcie_set_ecrc_checking(काष्ठा pci_dev *dev);
व्योम pcie_ecrc_get_policy(अक्षर *str);
#अन्यथा
अटल अंतरभूत व्योम pcie_set_ecrc_checking(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pcie_ecrc_get_policy(अक्षर *str) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIE_PTM
व्योम pci_pपंचांग_init(काष्ठा pci_dev *dev);
पूर्णांक pci_enable_pपंचांग(काष्ठा pci_dev *dev, u8 *granularity);
#अन्यथा
अटल अंतरभूत व्योम pci_pपंचांग_init(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_pपंचांग(काष्ठा pci_dev *dev, u8 *granularity)
अणु वापस -EINVAL; पूर्ण
#पूर्ण_अगर

काष्ठा pci_dev_reset_methods अणु
	u16 venकरोr;
	u16 device;
	पूर्णांक (*reset)(काष्ठा pci_dev *dev, पूर्णांक probe);
पूर्ण;

#अगर_घोषित CONFIG_PCI_QUIRKS
पूर्णांक pci_dev_specअगरic_reset(काष्ठा pci_dev *dev, पूर्णांक probe);
#अन्यथा
अटल अंतरभूत पूर्णांक pci_dev_specअगरic_reset(काष्ठा pci_dev *dev, पूर्णांक probe)
अणु
	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PCI_QUIRKS) && defined(CONFIG_ARM64)
पूर्णांक acpi_get_rc_resources(काष्ठा device *dev, स्थिर अक्षर *hid, u16 segment,
			  काष्ठा resource *res);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_get_rc_resources(काष्ठा device *dev, स्थिर अक्षर *hid,
					u16 segment, काष्ठा resource *res)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

पूर्णांक pci_rebar_get_current_size(काष्ठा pci_dev *pdev, पूर्णांक bar);
पूर्णांक pci_rebar_set_size(काष्ठा pci_dev *pdev, पूर्णांक bar, पूर्णांक size);
अटल अंतरभूत u64 pci_rebar_माप_प्रकारo_bytes(पूर्णांक size)
अणु
	वापस 1ULL << (size + 20);
पूर्ण

काष्ठा device_node;

#अगर_घोषित CONFIG_OF
पूर्णांक of_pci_parse_bus_range(काष्ठा device_node *node, काष्ठा resource *res);
पूर्णांक of_get_pci_करोमुख्य_nr(काष्ठा device_node *node);
पूर्णांक of_pci_get_max_link_speed(काष्ठा device_node *node);
व्योम pci_set_of_node(काष्ठा pci_dev *dev);
व्योम pci_release_of_node(काष्ठा pci_dev *dev);
व्योम pci_set_bus_of_node(काष्ठा pci_bus *bus);
व्योम pci_release_bus_of_node(काष्ठा pci_bus *bus);

पूर्णांक devm_of_pci_bridge_init(काष्ठा device *dev, काष्ठा pci_host_bridge *bridge);

#अन्यथा
अटल अंतरभूत पूर्णांक
of_pci_parse_bus_range(काष्ठा device_node *node, काष्ठा resource *res)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
of_get_pci_करोमुख्य_nr(काष्ठा device_node *node)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक
of_pci_get_max_link_speed(काष्ठा device_node *node)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम pci_set_of_node(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pci_release_of_node(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pci_set_bus_of_node(काष्ठा pci_bus *bus) अणु पूर्ण
अटल अंतरभूत व्योम pci_release_bus_of_node(काष्ठा pci_bus *bus) अणु पूर्ण

अटल अंतरभूत पूर्णांक devm_of_pci_bridge_init(काष्ठा device *dev, काष्ठा pci_host_bridge *bridge)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF */

#अगर_घोषित CONFIG_PCIEAER
व्योम pci_no_aer(व्योम);
व्योम pci_aer_init(काष्ठा pci_dev *dev);
व्योम pci_aer_निकास(काष्ठा pci_dev *dev);
बाह्य स्थिर काष्ठा attribute_group aer_stats_attr_group;
व्योम pci_aer_clear_fatal_status(काष्ठा pci_dev *dev);
पूर्णांक pci_aer_clear_status(काष्ठा pci_dev *dev);
पूर्णांक pci_aer_raw_clear_status(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत व्योम pci_no_aer(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम pci_aer_init(काष्ठा pci_dev *d) अणु पूर्ण
अटल अंतरभूत व्योम pci_aer_निकास(काष्ठा pci_dev *d) अणु पूर्ण
अटल अंतरभूत व्योम pci_aer_clear_fatal_status(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_aer_clear_status(काष्ठा pci_dev *dev) अणु वापस -EINVAL; पूर्ण
अटल अंतरभूत पूर्णांक pci_aer_raw_clear_status(काष्ठा pci_dev *dev) अणु वापस -EINVAL; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
पूर्णांक pci_acpi_program_hp_params(काष्ठा pci_dev *dev);
बाह्य स्थिर काष्ठा attribute_group pci_dev_acpi_attr_group;
#अन्यथा
अटल अंतरभूत पूर्णांक pci_acpi_program_hp_params(काष्ठा pci_dev *dev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIEASPM
बाह्य स्थिर काष्ठा attribute_group aspm_ctrl_attr_group;
#पूर्ण_अगर

#पूर्ण_अगर /* DRIVERS_PCI_H */
