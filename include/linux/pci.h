<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	pci.h
 *
 *	PCI defines and function prototypes
 *	Copyright 1994, Drew Eckhardt
 *	Copyright 1997--1999 Martin Mares <mj@ucw.cz>
 *
 *	PCI Express ASPM defines and function prototypes
 *	Copyright (c) 2007 Intel Corp.
 *		Zhang Yanmin (yanmin.zhang@पूर्णांकel.com)
 *		Shaohua Li (shaohua.li@पूर्णांकel.com)
 *
 *	For more inक्रमmation, please consult the following manuals (look at
 *	http://www.pcisig.com/ क्रम how to get them):
 *
 *	PCI BIOS Specअगरication
 *	PCI Local Bus Specअगरication
 *	PCI to PCI Bridge Specअगरication
 *	PCI Express Specअगरication
 *	PCI System Design Guide
 */
#अगर_अघोषित LINUX_PCI_H
#घोषणा LINUX_PCI_H


#समावेश <linux/mod_devicetable.h>

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kobject.h>
#समावेश <linux/atomic.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/resource_ext.h>
#समावेश <uapi/linux/pci.h>

#समावेश <linux/pci_ids.h>

#घोषणा PCI_STATUS_ERROR_BITS (PCI_STATUS_DETECTED_PARITY  | \
			       PCI_STATUS_SIG_SYSTEM_ERROR | \
			       PCI_STATUS_REC_MASTER_ABORT | \
			       PCI_STATUS_REC_TARGET_ABORT | \
			       PCI_STATUS_SIG_TARGET_ABORT | \
			       PCI_STATUS_PARITY)

/*
 * The PCI पूर्णांकerface treats multi-function devices as independent
 * devices.  The slot/function address of each device is encoded
 * in a single byte as follows:
 *
 *	7:3 = slot
 *	2:0 = function
 *
 * PCI_DEVFN(), PCI_SLOT(), and PCI_FUNC() are defined in uapi/linux/pci.h.
 * In the पूर्णांकerest of not exposing पूर्णांकerfaces to user-space unnecessarily,
 * the following kernel-only defines are being added here.
 */
#घोषणा PCI_DEVID(bus, devfn)	((((u16)(bus)) << 8) | (devfn))
/* वापस bus from PCI devid = ((u16)bus_number) << 8) | devfn */
#घोषणा PCI_BUS_NUM(x) (((x) >> 8) & 0xff)

/* pci_slot represents a physical slot */
काष्ठा pci_slot अणु
	काष्ठा pci_bus		*bus;		/* Bus this slot is on */
	काष्ठा list_head	list;		/* Node in list of slots */
	काष्ठा hotplug_slot	*hotplug;	/* Hotplug info (move here) */
	अचिन्हित अक्षर		number;		/* PCI_SLOT(pci_dev->devfn) */
	काष्ठा kobject		kobj;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *pci_slot_name(स्थिर काष्ठा pci_slot *slot)
अणु
	वापस kobject_name(&slot->kobj);
पूर्ण

/* File state क्रम mmap()s on /proc/bus/pci/X/Y */
क्रमागत pci_mmap_state अणु
	pci_mmap_io,
	pci_mmap_mem
पूर्ण;

/* For PCI devices, the region numbers are asचिन्हित this way: */
क्रमागत अणु
	/* #0-5: standard PCI resources */
	PCI_STD_RESOURCES,
	PCI_STD_RESOURCE_END = PCI_STD_RESOURCES + PCI_STD_NUM_BARS - 1,

	/* #6: expansion ROM resource */
	PCI_ROM_RESOURCE,

	/* Device-specअगरic resources */
#अगर_घोषित CONFIG_PCI_IOV
	PCI_IOV_RESOURCES,
	PCI_IOV_RESOURCE_END = PCI_IOV_RESOURCES + PCI_SRIOV_NUM_BARS - 1,
#पूर्ण_अगर

/* PCI-to-PCI (P2P) bridge winकरोws */
#घोषणा PCI_BRIDGE_IO_WINDOW		(PCI_BRIDGE_RESOURCES + 0)
#घोषणा PCI_BRIDGE_MEM_WINDOW		(PCI_BRIDGE_RESOURCES + 1)
#घोषणा PCI_BRIDGE_PREF_MEM_WINDOW	(PCI_BRIDGE_RESOURCES + 2)

/* CardBus bridge winकरोws */
#घोषणा PCI_CB_BRIDGE_IO_0_WINDOW	(PCI_BRIDGE_RESOURCES + 0)
#घोषणा PCI_CB_BRIDGE_IO_1_WINDOW	(PCI_BRIDGE_RESOURCES + 1)
#घोषणा PCI_CB_BRIDGE_MEM_0_WINDOW	(PCI_BRIDGE_RESOURCES + 2)
#घोषणा PCI_CB_BRIDGE_MEM_1_WINDOW	(PCI_BRIDGE_RESOURCES + 3)

/* Total number of bridge resources क्रम P2P and CardBus */
#घोषणा PCI_BRIDGE_RESOURCE_NUM 4

	/* Resources asचिन्हित to buses behind the bridge */
	PCI_BRIDGE_RESOURCES,
	PCI_BRIDGE_RESOURCE_END = PCI_BRIDGE_RESOURCES +
				  PCI_BRIDGE_RESOURCE_NUM - 1,

	/* Total resources associated with a PCI device */
	PCI_NUM_RESOURCES,

	/* Preserve this क्रम compatibility */
	DEVICE_COUNT_RESOURCE = PCI_NUM_RESOURCES,
पूर्ण;

/**
 * क्रमागत pci_पूर्णांकerrupt_pin - PCI INTx पूर्णांकerrupt values
 * @PCI_INTERRUPT_UNKNOWN: Unknown or unasचिन्हित पूर्णांकerrupt
 * @PCI_INTERRUPT_INTA: PCI INTA pin
 * @PCI_INTERRUPT_INTB: PCI INTB pin
 * @PCI_INTERRUPT_INTC: PCI INTC pin
 * @PCI_INTERRUPT_INTD: PCI INTD pin
 *
 * Corresponds to values क्रम legacy PCI INTx पूर्णांकerrupts, as can be found in the
 * PCI_INTERRUPT_PIN रेजिस्टर.
 */
क्रमागत pci_पूर्णांकerrupt_pin अणु
	PCI_INTERRUPT_UNKNOWN,
	PCI_INTERRUPT_INTA,
	PCI_INTERRUPT_INTB,
	PCI_INTERRUPT_INTC,
	PCI_INTERRUPT_INTD,
पूर्ण;

/* The number of legacy PCI INTx पूर्णांकerrupts */
#घोषणा PCI_NUM_INTX	4

/*
 * pci_घातer_t values must match the bits in the Capabilities PME_Support
 * and Control/Status PowerState fields in the Power Management capability.
 */
प्रकार पूर्णांक __bitwise pci_घातer_t;

#घोषणा PCI_D0		((pci_घातer_t __क्रमce) 0)
#घोषणा PCI_D1		((pci_घातer_t __क्रमce) 1)
#घोषणा PCI_D2		((pci_घातer_t __क्रमce) 2)
#घोषणा PCI_D3hot	((pci_घातer_t __क्रमce) 3)
#घोषणा PCI_D3cold	((pci_घातer_t __क्रमce) 4)
#घोषणा PCI_UNKNOWN	((pci_घातer_t __क्रमce) 5)
#घोषणा PCI_POWER_ERROR	((pci_घातer_t __क्रमce) -1)

/* Remember to update this when the list above changes! */
बाह्य स्थिर अक्षर *pci_घातer_names[];

अटल अंतरभूत स्थिर अक्षर *pci_घातer_name(pci_घातer_t state)
अणु
	वापस pci_घातer_names[1 + (__क्रमce पूर्णांक) state];
पूर्ण

/**
 * प्रकार pci_channel_state_t
 *
 * The pci_channel state describes connectivity between the CPU and
 * the PCI device.  If some PCI bus between here and the PCI device
 * has crashed or locked up, this info is reflected here.
 */
प्रकार अचिन्हित पूर्णांक __bitwise pci_channel_state_t;

क्रमागत अणु
	/* I/O channel is in normal state */
	pci_channel_io_normal = (__क्रमce pci_channel_state_t) 1,

	/* I/O to channel is blocked */
	pci_channel_io_frozen = (__क्रमce pci_channel_state_t) 2,

	/* PCI card is dead */
	pci_channel_io_perm_failure = (__क्रमce pci_channel_state_t) 3,
पूर्ण;

प्रकार अचिन्हित पूर्णांक __bitwise pcie_reset_state_t;

क्रमागत pcie_reset_state अणु
	/* Reset is NOT निश्चितed (Use to deनिश्चित reset) */
	pcie_deनिश्चित_reset = (__क्रमce pcie_reset_state_t) 1,

	/* Use #PERST to reset PCIe device */
	pcie_warm_reset = (__क्रमce pcie_reset_state_t) 2,

	/* Use PCIe Hot Reset to reset device */
	pcie_hot_reset = (__क्रमce pcie_reset_state_t) 3
पूर्ण;

प्रकार अचिन्हित लघु __bitwise pci_dev_flags_t;
क्रमागत pci_dev_flags अणु
	/* INTX_DISABLE in PCI_COMMAND रेजिस्टर disables MSI too */
	PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG = (__क्रमce pci_dev_flags_t) (1 << 0),
	/* Device configuration is irrevocably lost अगर disabled पूर्णांकo D3 */
	PCI_DEV_FLAGS_NO_D3 = (__क्रमce pci_dev_flags_t) (1 << 1),
	/* Provide indication device is asचिन्हित by a Virtual Machine Manager */
	PCI_DEV_FLAGS_ASSIGNED = (__क्रमce pci_dev_flags_t) (1 << 2),
	/* Flag क्रम quirk use to store अगर quirk-specअगरic ACS is enabled */
	PCI_DEV_FLAGS_ACS_ENABLED_QUIRK = (__क्रमce pci_dev_flags_t) (1 << 3),
	/* Use a PCIe-to-PCI bridge alias even अगर !pci_is_pcie */
	PCI_DEV_FLAG_PCIE_BRIDGE_ALIAS = (__क्रमce pci_dev_flags_t) (1 << 5),
	/* Do not use bus resets क्रम device */
	PCI_DEV_FLAGS_NO_BUS_RESET = (__क्रमce pci_dev_flags_t) (1 << 6),
	/* Do not use PM reset even अगर device advertises NoSoftRst- */
	PCI_DEV_FLAGS_NO_PM_RESET = (__क्रमce pci_dev_flags_t) (1 << 7),
	/* Get VPD from function 0 VPD */
	PCI_DEV_FLAGS_VPD_REF_F0 = (__क्रमce pci_dev_flags_t) (1 << 8),
	/* A non-root bridge where translation occurs, stop alias search here */
	PCI_DEV_FLAGS_BRIDGE_XLATE_ROOT = (__क्रमce pci_dev_flags_t) (1 << 9),
	/* Do not use FLR even अगर device advertises PCI_AF_CAP */
	PCI_DEV_FLAGS_NO_FLR_RESET = (__क्रमce pci_dev_flags_t) (1 << 10),
	/* Don't use Relaxed Ordering क्रम TLPs directed at this device */
	PCI_DEV_FLAGS_NO_RELAXED_ORDERING = (__क्रमce pci_dev_flags_t) (1 << 11),
पूर्ण;

क्रमागत pci_irq_reroute_variant अणु
	INTEL_IRQ_REROUTE_VARIANT = 1,
	MAX_IRQ_REROUTE_VARIANTS = 3
पूर्ण;

प्रकार अचिन्हित लघु __bitwise pci_bus_flags_t;
क्रमागत pci_bus_flags अणु
	PCI_BUS_FLAGS_NO_MSI	= (__क्रमce pci_bus_flags_t) 1,
	PCI_BUS_FLAGS_NO_MMRBC	= (__क्रमce pci_bus_flags_t) 2,
	PCI_BUS_FLAGS_NO_AERSID	= (__क्रमce pci_bus_flags_t) 4,
	PCI_BUS_FLAGS_NO_EXTCFG	= (__क्रमce pci_bus_flags_t) 8,
पूर्ण;

/* Values from Link Status रेजिस्टर, PCIe r3.1, sec 7.8.8 */
क्रमागत pcie_link_width अणु
	PCIE_LNK_WIDTH_RESRV	= 0x00,
	PCIE_LNK_X1		= 0x01,
	PCIE_LNK_X2		= 0x02,
	PCIE_LNK_X4		= 0x04,
	PCIE_LNK_X8		= 0x08,
	PCIE_LNK_X12		= 0x0c,
	PCIE_LNK_X16		= 0x10,
	PCIE_LNK_X32		= 0x20,
	PCIE_LNK_WIDTH_UNKNOWN	= 0xff,
पूर्ण;

/* See matching string table in pci_speed_string() */
क्रमागत pci_bus_speed अणु
	PCI_SPEED_33MHz			= 0x00,
	PCI_SPEED_66MHz			= 0x01,
	PCI_SPEED_66MHz_PCIX		= 0x02,
	PCI_SPEED_100MHz_PCIX		= 0x03,
	PCI_SPEED_133MHz_PCIX		= 0x04,
	PCI_SPEED_66MHz_PCIX_ECC	= 0x05,
	PCI_SPEED_100MHz_PCIX_ECC	= 0x06,
	PCI_SPEED_133MHz_PCIX_ECC	= 0x07,
	PCI_SPEED_66MHz_PCIX_266	= 0x09,
	PCI_SPEED_100MHz_PCIX_266	= 0x0a,
	PCI_SPEED_133MHz_PCIX_266	= 0x0b,
	AGP_UNKNOWN			= 0x0c,
	AGP_1X				= 0x0d,
	AGP_2X				= 0x0e,
	AGP_4X				= 0x0f,
	AGP_8X				= 0x10,
	PCI_SPEED_66MHz_PCIX_533	= 0x11,
	PCI_SPEED_100MHz_PCIX_533	= 0x12,
	PCI_SPEED_133MHz_PCIX_533	= 0x13,
	PCIE_SPEED_2_5GT		= 0x14,
	PCIE_SPEED_5_0GT		= 0x15,
	PCIE_SPEED_8_0GT		= 0x16,
	PCIE_SPEED_16_0GT		= 0x17,
	PCIE_SPEED_32_0GT		= 0x18,
	PCIE_SPEED_64_0GT		= 0x19,
	PCI_SPEED_UNKNOWN		= 0xff,
पूर्ण;

क्रमागत pci_bus_speed pcie_get_speed_cap(काष्ठा pci_dev *dev);
क्रमागत pcie_link_width pcie_get_width_cap(काष्ठा pci_dev *dev);

काष्ठा pci_cap_saved_data अणु
	u16		cap_nr;
	bool		cap_extended;
	अचिन्हित पूर्णांक	size;
	u32		data[];
पूर्ण;

काष्ठा pci_cap_saved_state अणु
	काष्ठा hlist_node		next;
	काष्ठा pci_cap_saved_data	cap;
पूर्ण;

काष्ठा irq_affinity;
काष्ठा pcie_link_state;
काष्ठा pci_vpd;
काष्ठा pci_sriov;
काष्ठा pci_p2pdma;
काष्ठा rcec_ea;

/* The pci_dev काष्ठाure describes PCI devices */
काष्ठा pci_dev अणु
	काष्ठा list_head bus_list;	/* Node in per-bus list */
	काष्ठा pci_bus	*bus;		/* Bus this device is on */
	काष्ठा pci_bus	*subordinate;	/* Bus this device bridges to */

	व्योम		*sysdata;	/* Hook क्रम sys-specअगरic extension */
	काष्ठा proc_dir_entry *procent;	/* Device entry in /proc/bus/pci */
	काष्ठा pci_slot	*slot;		/* Physical slot this device is in */

	अचिन्हित पूर्णांक	devfn;		/* Encoded device & function index */
	अचिन्हित लघु	venकरोr;
	अचिन्हित लघु	device;
	अचिन्हित लघु	subप्रणाली_venकरोr;
	अचिन्हित लघु	subप्रणाली_device;
	अचिन्हित पूर्णांक	class;		/* 3 bytes: (base,sub,prog-अगर) */
	u8		revision;	/* PCI revision, low byte of class word */
	u8		hdr_type;	/* PCI header type (`multi' flag masked out) */
#अगर_घोषित CONFIG_PCIEAER
	u16		aer_cap;	/* AER capability offset */
	काष्ठा aer_stats *aer_stats;	/* AER stats क्रम this device */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCIEPORTBUS
	काष्ठा rcec_ea	*rcec_ea;	/* RCEC cached endpoपूर्णांक association */
	काष्ठा pci_dev  *rcec;          /* Associated RCEC device */
#पूर्ण_अगर
	u8		pcie_cap;	/* PCIe capability offset */
	u8		msi_cap;	/* MSI capability offset */
	u8		msix_cap;	/* MSI-X capability offset */
	u8		pcie_mpss:3;	/* PCIe Max Payload Size Supported */
	u8		rom_base_reg;	/* Config रेजिस्टर controlling ROM */
	u8		pin;		/* Interrupt pin this device uses */
	u16		pcie_flags_reg;	/* Cached PCIe Capabilities Register */
	अचिन्हित दीर्घ	*dma_alias_mask;/* Mask of enabled devfn aliases */

	काष्ठा pci_driver *driver;	/* Driver bound to this device */
	u64		dma_mask;	/* Mask of the bits of bus address this
					   device implements.  Normally this is
					   0xffffffff.  You only need to change
					   this अगर your device has broken DMA
					   or supports 64-bit transfers.  */

	काष्ठा device_dma_parameters dma_parms;

	pci_घातer_t	current_state;	/* Current operating state. In ACPI,
					   this is D0-D3, D0 being fully
					   functional, and D3 being off. */
	अचिन्हित पूर्णांक	imm_पढ़ोy:1;	/* Supports Immediate Readiness */
	u8		pm_cap;		/* PM capability offset */
	अचिन्हित पूर्णांक	pme_support:5;	/* Biपंचांगask of states from which PME#
					   can be generated */
	अचिन्हित पूर्णांक	pme_poll:1;	/* Poll device's PME status bit */
	अचिन्हित पूर्णांक	d1_support:1;	/* Low घातer state D1 is supported */
	अचिन्हित पूर्णांक	d2_support:1;	/* Low घातer state D2 is supported */
	अचिन्हित पूर्णांक	no_d1d2:1;	/* D1 and D2 are क्रमbidden */
	अचिन्हित पूर्णांक	no_d3cold:1;	/* D3cold is क्रमbidden */
	अचिन्हित पूर्णांक	bridge_d3:1;	/* Allow D3 क्रम bridge */
	अचिन्हित पूर्णांक	d3cold_allowed:1;	/* D3cold is allowed by user */
	अचिन्हित पूर्णांक	mmio_always_on:1;	/* Disallow turning off io/mem
						   decoding during BAR sizing */
	अचिन्हित पूर्णांक	wakeup_prepared:1;
	अचिन्हित पूर्णांक	runसमय_d3cold:1;	/* Whether go through runसमय
						   D3cold, not set क्रम devices
						   घातered on/off by the
						   corresponding bridge */
	अचिन्हित पूर्णांक	skip_bus_pm:1;	/* Internal: Skip bus-level PM */
	अचिन्हित पूर्णांक	ignore_hotplug:1;	/* Ignore hotplug events */
	अचिन्हित पूर्णांक	hotplug_user_indicators:1; /* SlotCtl indicators
						      controlled exclusively by
						      user sysfs */
	अचिन्हित पूर्णांक	clear_retrain_link:1;	/* Need to clear Retrain Link
						   bit manually */
	अचिन्हित पूर्णांक	d3hot_delay;	/* D3hot->D0 transition समय in ms */
	अचिन्हित पूर्णांक	d3cold_delay;	/* D3cold->D0 transition समय in ms */

#अगर_घोषित CONFIG_PCIEASPM
	काष्ठा pcie_link_state	*link_state;	/* ASPM link state */
	अचिन्हित पूर्णांक	ltr_path:1;	/* Latency Tolerance Reporting
					   supported from root to here */
	u16		l1ss;		/* L1SS Capability poपूर्णांकer */
#पूर्ण_अगर
	अचिन्हित पूर्णांक	eetlp_prefix_path:1;	/* End-to-End TLP Prefix */

	pci_channel_state_t error_state;	/* Current connectivity state */
	काष्ठा device	dev;			/* Generic device पूर्णांकerface */

	पूर्णांक		cfg_size;		/* Size of config space */

	/*
	 * Instead of touching पूर्णांकerrupt line and base address रेजिस्टरs
	 * directly, use the values stored here. They might be dअगरferent!
	 */
	अचिन्हित पूर्णांक	irq;
	काष्ठा resource resource[DEVICE_COUNT_RESOURCE]; /* I/O and memory regions + expansion ROMs */

	bool		match_driver;		/* Skip attaching driver */

	अचिन्हित पूर्णांक	transparent:1;		/* Subtractive decode bridge */
	अचिन्हित पूर्णांक	io_winकरोw:1;		/* Bridge has I/O winकरोw */
	अचिन्हित पूर्णांक	pref_winकरोw:1;		/* Bridge has pref mem winकरोw */
	अचिन्हित पूर्णांक	pref_64_winकरोw:1;	/* Pref mem winकरोw is 64-bit */
	अचिन्हित पूर्णांक	multअगरunction:1;	/* Multi-function device */

	अचिन्हित पूर्णांक	is_busmaster:1;		/* Is busmaster */
	अचिन्हित पूर्णांक	no_msi:1;		/* May not use MSI */
	अचिन्हित पूर्णांक	no_64bit_msi:1;		/* May only use 32-bit MSIs */
	अचिन्हित पूर्णांक	block_cfg_access:1;	/* Config space access blocked */
	अचिन्हित पूर्णांक	broken_parity_status:1;	/* Generates false positive parity */
	अचिन्हित पूर्णांक	irq_reroute_variant:2;	/* Needs IRQ rerouting variant */
	अचिन्हित पूर्णांक	msi_enabled:1;
	अचिन्हित पूर्णांक	msix_enabled:1;
	अचिन्हित पूर्णांक	ari_enabled:1;		/* ARI क्रमwarding */
	अचिन्हित पूर्णांक	ats_enabled:1;		/* Address Translation Svc */
	अचिन्हित पूर्णांक	pasid_enabled:1;	/* Process Address Space ID */
	अचिन्हित पूर्णांक	pri_enabled:1;		/* Page Request Interface */
	अचिन्हित पूर्णांक	is_managed:1;
	अचिन्हित पूर्णांक	needs_freset:1;		/* Requires fundamental reset */
	अचिन्हित पूर्णांक	state_saved:1;
	अचिन्हित पूर्णांक	is_physfn:1;
	अचिन्हित पूर्णांक	is_virtfn:1;
	अचिन्हित पूर्णांक	reset_fn:1;
	अचिन्हित पूर्णांक	is_hotplug_bridge:1;
	अचिन्हित पूर्णांक	shpc_managed:1;		/* SHPC owned by shpchp */
	अचिन्हित पूर्णांक	is_thunderbolt:1;	/* Thunderbolt controller */
	/*
	 * Devices marked being untrusted are the ones that can potentially
	 * execute DMA attacks and similar. They are typically connected
	 * through बाह्यal ports such as Thunderbolt but not limited to
	 * that. When an IOMMU is enabled they should be getting full
	 * mappings to make sure they cannot access arbitrary memory.
	 */
	अचिन्हित पूर्णांक	untrusted:1;
	/*
	 * Info from the platक्रमm, e.g., ACPI or device tree, may mark a
	 * device as "external-facing".  An बाह्यal-facing device is
	 * itself पूर्णांकernal but devices करोwnstream from it are बाह्यal.
	 */
	अचिन्हित पूर्णांक	बाह्यal_facing:1;
	अचिन्हित पूर्णांक	broken_पूर्णांकx_masking:1;	/* INTx masking can't be used */
	अचिन्हित पूर्णांक	io_winकरोw_1k:1;		/* Intel bridge 1K I/O winकरोws */
	अचिन्हित पूर्णांक	irq_managed:1;
	अचिन्हित पूर्णांक	non_compliant_bars:1;	/* Broken BARs; ignore them */
	अचिन्हित पूर्णांक	is_probed:1;		/* Device probing in progress */
	अचिन्हित पूर्णांक	link_active_reporting:1;/* Device capable of reporting link active */
	अचिन्हित पूर्णांक	no_vf_scan:1;		/* Don't scan क्रम VFs after IOV enablement */
	अचिन्हित पूर्णांक	no_command_memory:1;	/* No PCI_COMMAND_MEMORY */
	pci_dev_flags_t dev_flags;
	atomic_t	enable_cnt;	/* pci_enable_device has been called */

	u32		saved_config_space[16]; /* Config space saved at suspend समय */
	काष्ठा hlist_head saved_cap_space;
	पूर्णांक		rom_attr_enabled;	/* Display of ROM attribute enabled? */
	काष्ठा bin_attribute *res_attr[DEVICE_COUNT_RESOURCE]; /* sysfs file क्रम resources */
	काष्ठा bin_attribute *res_attr_wc[DEVICE_COUNT_RESOURCE]; /* sysfs file क्रम WC mapping of resources */

#अगर_घोषित CONFIG_HOTPLUG_PCI_PCIE
	अचिन्हित पूर्णांक	broken_cmd_compl:1;	/* No compl क्रम some cmds */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCIE_PTM
	अचिन्हित पूर्णांक	pपंचांग_root:1;
	अचिन्हित पूर्णांक	pपंचांग_enabled:1;
	u8		pपंचांग_granularity;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_MSI
	स्थिर काष्ठा attribute_group **msi_irq_groups;
#पूर्ण_अगर
	काष्ठा pci_vpd *vpd;
#अगर_घोषित CONFIG_PCIE_DPC
	u16		dpc_cap;
	अचिन्हित पूर्णांक	dpc_rp_extensions:1;
	u8		dpc_rp_log_size;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_ATS
	जोड़ अणु
		काष्ठा pci_sriov	*sriov;		/* PF: SR-IOV info */
		काष्ठा pci_dev		*physfn;	/* VF: related PF */
	पूर्ण;
	u16		ats_cap;	/* ATS Capability offset */
	u8		ats_stu;	/* ATS Smallest Translation Unit */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_PRI
	u16		pri_cap;	/* PRI Capability offset */
	u32		pri_reqs_alloc; /* Number of PRI requests allocated */
	अचिन्हित पूर्णांक	pasid_required:1; /* PRG Response PASID Required */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_PASID
	u16		pasid_cap;	/* PASID Capability offset */
	u16		pasid_features;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_P2PDMA
	काष्ठा pci_p2pdma *p2pdma;
#पूर्ण_अगर
	u16		acs_cap;	/* ACS Capability offset */
	phys_addr_t	rom;		/* Physical address अगर not from BAR */
	माप_प्रकार		romlen;		/* Length अगर not from BAR */
	अक्षर		*driver_override; /* Driver name to क्रमce a match */

	अचिन्हित दीर्घ	priv_flags;	/* Private flags क्रम the PCI driver */
पूर्ण;

अटल अंतरभूत काष्ठा pci_dev *pci_physfn(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PCI_IOV
	अगर (dev->is_virtfn)
		dev = dev->physfn;
#पूर्ण_अगर
	वापस dev;
पूर्ण

काष्ठा pci_dev *pci_alloc_dev(काष्ठा pci_bus *bus);

#घोषणा	to_pci_dev(n) container_of(n, काष्ठा pci_dev, dev)
#घोषणा क्रम_each_pci_dev(d) जबतक ((d = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, d)) != शून्य)

अटल अंतरभूत पूर्णांक pci_channel_offline(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->error_state != pci_channel_io_normal);
पूर्ण

काष्ठा pci_host_bridge अणु
	काष्ठा device	dev;
	काष्ठा pci_bus	*bus;		/* Root bus */
	काष्ठा pci_ops	*ops;
	काष्ठा pci_ops	*child_ops;
	व्योम		*sysdata;
	पूर्णांक		busnr;
	काष्ठा list_head winकरोws;	/* resource_entry */
	काष्ठा list_head dma_ranges;	/* dma ranges resource list */
	u8 (*swizzle_irq)(काष्ठा pci_dev *, u8 *); /* Platक्रमm IRQ swizzler */
	पूर्णांक (*map_irq)(स्थिर काष्ठा pci_dev *, u8, u8);
	व्योम (*release_fn)(काष्ठा pci_host_bridge *);
	व्योम		*release_data;
	अचिन्हित पूर्णांक	ignore_reset_delay:1;	/* For entire hierarchy */
	अचिन्हित पूर्णांक	no_ext_tags:1;		/* No Extended Tags */
	अचिन्हित पूर्णांक	native_aer:1;		/* OS may use PCIe AER */
	अचिन्हित पूर्णांक	native_pcie_hotplug:1;	/* OS may use PCIe hotplug */
	अचिन्हित पूर्णांक	native_shpc_hotplug:1;	/* OS may use SHPC hotplug */
	अचिन्हित पूर्णांक	native_pme:1;		/* OS may use PCIe PME */
	अचिन्हित पूर्णांक	native_ltr:1;		/* OS may use PCIe LTR */
	अचिन्हित पूर्णांक	native_dpc:1;		/* OS may use PCIe DPC */
	अचिन्हित पूर्णांक	preserve_config:1;	/* Preserve FW resource setup */
	अचिन्हित पूर्णांक	size_winकरोws:1;		/* Enable root bus sizing */
	अचिन्हित पूर्णांक	msi_करोमुख्य:1;		/* Bridge wants MSI करोमुख्य */

	/* Resource alignment requirements */
	resource_माप_प्रकार (*align_resource)(काष्ठा pci_dev *dev,
			स्थिर काष्ठा resource *res,
			resource_माप_प्रकार start,
			resource_माप_प्रकार size,
			resource_माप_प्रकार align);
	अचिन्हित दीर्घ	निजी[] ____cacheline_aligned;
पूर्ण;

#घोषणा	to_pci_host_bridge(n) container_of(n, काष्ठा pci_host_bridge, dev)

अटल अंतरभूत व्योम *pci_host_bridge_priv(काष्ठा pci_host_bridge *bridge)
अणु
	वापस (व्योम *)bridge->निजी;
पूर्ण

अटल अंतरभूत काष्ठा pci_host_bridge *pci_host_bridge_from_priv(व्योम *priv)
अणु
	वापस container_of(priv, काष्ठा pci_host_bridge, निजी);
पूर्ण

काष्ठा pci_host_bridge *pci_alloc_host_bridge(माप_प्रकार priv);
काष्ठा pci_host_bridge *devm_pci_alloc_host_bridge(काष्ठा device *dev,
						   माप_प्रकार priv);
व्योम pci_मुक्त_host_bridge(काष्ठा pci_host_bridge *bridge);
काष्ठा pci_host_bridge *pci_find_host_bridge(काष्ठा pci_bus *bus);

व्योम pci_set_host_bridge_release(काष्ठा pci_host_bridge *bridge,
				 व्योम (*release_fn)(काष्ठा pci_host_bridge *),
				 व्योम *release_data);

पूर्णांक pcibios_root_bridge_prepare(काष्ठा pci_host_bridge *bridge);

/*
 * The first PCI_BRIDGE_RESOURCE_NUM PCI bus resources (those that correspond
 * to P2P or CardBus bridge winकरोws) go in a table.  Additional ones (क्रम
 * buses below host bridges or subtractive decode bridges) go in the list.
 * Use pci_bus_क्रम_each_resource() to iterate through all the resources.
 */

/*
 * PCI_SUBTRACTIVE_DECODE means the bridge क्रमwards the winकरोw implicitly
 * and there's no way to program the bridge with the details of the winकरोw.
 * This करोes not apply to ACPI _CRS winकरोws, even with the _DEC subtractive-
 * decode bit set, because they are explicit and can be programmed with _SRS.
 */
#घोषणा PCI_SUBTRACTIVE_DECODE	0x1

काष्ठा pci_bus_resource अणु
	काष्ठा list_head	list;
	काष्ठा resource		*res;
	अचिन्हित पूर्णांक		flags;
पूर्ण;

#घोषणा PCI_REGION_FLAG_MASK	0x0fU	/* These bits of resource flags tell us the PCI region flags */

काष्ठा pci_bus अणु
	काष्ठा list_head node;		/* Node in list of buses */
	काष्ठा pci_bus	*parent;	/* Parent bus this bridge is on */
	काष्ठा list_head children;	/* List of child buses */
	काष्ठा list_head devices;	/* List of devices on this bus */
	काष्ठा pci_dev	*self;		/* Bridge device as seen by parent */
	काष्ठा list_head slots;		/* List of slots on this bus;
					   रक्षित by pci_slot_mutex */
	काष्ठा resource *resource[PCI_BRIDGE_RESOURCE_NUM];
	काष्ठा list_head resources;	/* Address space routed to this bus */
	काष्ठा resource busn_res;	/* Bus numbers routed to this bus */

	काष्ठा pci_ops	*ops;		/* Configuration access functions */
	व्योम		*sysdata;	/* Hook क्रम sys-specअगरic extension */
	काष्ठा proc_dir_entry *procdir;	/* Directory entry in /proc/bus/pci */

	अचिन्हित अक्षर	number;		/* Bus number */
	अचिन्हित अक्षर	primary;	/* Number of primary bridge */
	अचिन्हित अक्षर	max_bus_speed;	/* क्रमागत pci_bus_speed */
	अचिन्हित अक्षर	cur_bus_speed;	/* क्रमागत pci_bus_speed */
#अगर_घोषित CONFIG_PCI_DOMAINS_GENERIC
	पूर्णांक		करोमुख्य_nr;
#पूर्ण_अगर

	अक्षर		name[48];

	अचिन्हित लघु	bridge_ctl;	/* Manage NO_ISA/FBB/et al behaviors */
	pci_bus_flags_t bus_flags;	/* Inherited by child buses */
	काष्ठा device		*bridge;
	काष्ठा device		dev;
	काष्ठा bin_attribute	*legacy_io;	/* Legacy I/O क्रम this bus */
	काष्ठा bin_attribute	*legacy_mem;	/* Legacy mem */
	अचिन्हित पूर्णांक		is_added:1;
पूर्ण;

#घोषणा to_pci_bus(n)	container_of(n, काष्ठा pci_bus, dev)

अटल अंतरभूत u16 pci_dev_id(काष्ठा pci_dev *dev)
अणु
	वापस PCI_DEVID(dev->bus->number, dev->devfn);
पूर्ण

/*
 * Returns true अगर the PCI bus is root (behind host-PCI bridge),
 * false otherwise
 *
 * Some code assumes that "bus->self == NULL" means that bus is a root bus.
 * This is incorrect because "virtual" buses added क्रम SR-IOV (via
 * virtfn_add_bus()) have "bus->self == NULL" but are not root buses.
 */
अटल अंतरभूत bool pci_is_root_bus(काष्ठा pci_bus *pbus)
अणु
	वापस !(pbus->parent);
पूर्ण

/**
 * pci_is_bridge - check अगर the PCI device is a bridge
 * @dev: PCI device
 *
 * Return true अगर the PCI device is bridge whether it has subordinate
 * or not.
 */
अटल अंतरभूत bool pci_is_bridge(काष्ठा pci_dev *dev)
अणु
	वापस dev->hdr_type == PCI_HEADER_TYPE_BRIDGE ||
		dev->hdr_type == PCI_HEADER_TYPE_CARDBUS;
पूर्ण

#घोषणा क्रम_each_pci_bridge(dev, bus)				\
	list_क्रम_each_entry(dev, &bus->devices, bus_list)	\
		अगर (!pci_is_bridge(dev)) अणुपूर्ण अन्यथा

अटल अंतरभूत काष्ठा pci_dev *pci_upstream_bridge(काष्ठा pci_dev *dev)
अणु
	dev = pci_physfn(dev);
	अगर (pci_is_root_bus(dev->bus))
		वापस शून्य;

	वापस dev->bus->self;
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
अटल अंतरभूत bool pci_dev_msi_enabled(काष्ठा pci_dev *pci_dev)
अणु
	वापस pci_dev->msi_enabled || pci_dev->msix_enabled;
पूर्ण
#अन्यथा
अटल अंतरभूत bool pci_dev_msi_enabled(काष्ठा pci_dev *pci_dev) अणु वापस false; पूर्ण
#पूर्ण_अगर

/* Error values that may be वापसed by PCI functions */
#घोषणा PCIBIOS_SUCCESSFUL		0x00
#घोषणा PCIBIOS_FUNC_NOT_SUPPORTED	0x81
#घोषणा PCIBIOS_BAD_VENDOR_ID		0x83
#घोषणा PCIBIOS_DEVICE_NOT_FOUND	0x86
#घोषणा PCIBIOS_BAD_REGISTER_NUMBER	0x87
#घोषणा PCIBIOS_SET_FAILED		0x88
#घोषणा PCIBIOS_BUFFER_TOO_SMALL	0x89

/* Translate above to generic त्रुटि_सं क्रम passing back through non-PCI code */
अटल अंतरभूत पूर्णांक pcibios_err_to_त्रुटि_सं(पूर्णांक err)
अणु
	अगर (err <= PCIBIOS_SUCCESSFUL)
		वापस err; /* Assume alपढ़ोy त्रुटि_सं */

	चयन (err) अणु
	हाल PCIBIOS_FUNC_NOT_SUPPORTED:
		वापस -ENOENT;
	हाल PCIBIOS_BAD_VENDOR_ID:
		वापस -ENOTTY;
	हाल PCIBIOS_DEVICE_NOT_FOUND:
		वापस -ENODEV;
	हाल PCIBIOS_BAD_REGISTER_NUMBER:
		वापस -EFAULT;
	हाल PCIBIOS_SET_FAILED:
		वापस -EIO;
	हाल PCIBIOS_BUFFER_TOO_SMALL:
		वापस -ENOSPC;
	पूर्ण

	वापस -दुस्फल;
पूर्ण

/* Low-level architecture-dependent routines */

काष्ठा pci_ops अणु
	पूर्णांक (*add_bus)(काष्ठा pci_bus *bus);
	व्योम (*हटाओ_bus)(काष्ठा pci_bus *bus);
	व्योम __iomem *(*map_bus)(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where);
	पूर्णांक (*पढ़ो)(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 *val);
	पूर्णांक (*ग_लिखो)(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size, u32 val);
पूर्ण;

/*
 * ACPI needs to be able to access PCI config space beक्रमe we've करोne a
 * PCI bus scan and created pci_bus काष्ठाures.
 */
पूर्णांक raw_pci_पढ़ो(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
		 पूर्णांक reg, पूर्णांक len, u32 *val);
पूर्णांक raw_pci_ग_लिखो(अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn,
		  पूर्णांक reg, पूर्णांक len, u32 val);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
प्रकार u64 pci_bus_addr_t;
#अन्यथा
प्रकार u32 pci_bus_addr_t;
#पूर्ण_अगर

काष्ठा pci_bus_region अणु
	pci_bus_addr_t	start;
	pci_bus_addr_t	end;
पूर्ण;

काष्ठा pci_dynids अणु
	spinlock_t		lock;	/* Protects list, index */
	काष्ठा list_head	list;	/* For IDs added at runसमय */
पूर्ण;


/*
 * PCI Error Recovery System (PCI-ERS).  If a PCI device driver provides
 * a set of callbacks in काष्ठा pci_error_handlers, that device driver
 * will be notअगरied of PCI bus errors, and will be driven to recovery
 * when an error occurs.
 */

प्रकार अचिन्हित पूर्णांक __bitwise pci_ers_result_t;

क्रमागत pci_ers_result अणु
	/* No result/none/not supported in device driver */
	PCI_ERS_RESULT_NONE = (__क्रमce pci_ers_result_t) 1,

	/* Device driver can recover without slot reset */
	PCI_ERS_RESULT_CAN_RECOVER = (__क्रमce pci_ers_result_t) 2,

	/* Device driver wants slot to be reset */
	PCI_ERS_RESULT_NEED_RESET = (__क्रमce pci_ers_result_t) 3,

	/* Device has completely failed, is unrecoverable */
	PCI_ERS_RESULT_DISCONNECT = (__क्रमce pci_ers_result_t) 4,

	/* Device driver is fully recovered and operational */
	PCI_ERS_RESULT_RECOVERED = (__क्रमce pci_ers_result_t) 5,

	/* No AER capabilities रेजिस्टरed क्रम the driver */
	PCI_ERS_RESULT_NO_AER_DRIVER = (__क्रमce pci_ers_result_t) 6,
पूर्ण;

/* PCI bus error event callbacks */
काष्ठा pci_error_handlers अणु
	/* PCI bus error detected on this device */
	pci_ers_result_t (*error_detected)(काष्ठा pci_dev *dev,
					   pci_channel_state_t error);

	/* MMIO has been re-enabled, but not DMA */
	pci_ers_result_t (*mmio_enabled)(काष्ठा pci_dev *dev);

	/* PCI slot has been reset */
	pci_ers_result_t (*slot_reset)(काष्ठा pci_dev *dev);

	/* PCI function reset prepare or completed */
	व्योम (*reset_prepare)(काष्ठा pci_dev *dev);
	व्योम (*reset_करोne)(काष्ठा pci_dev *dev);

	/* Device driver may resume normal operations */
	व्योम (*resume)(काष्ठा pci_dev *dev);
पूर्ण;


काष्ठा module;

/**
 * काष्ठा pci_driver - PCI driver काष्ठाure
 * @node:	List of driver काष्ठाures.
 * @name:	Driver name.
 * @id_table:	Poपूर्णांकer to table of device IDs the driver is
 *		पूर्णांकerested in.  Most drivers should export this
 *		table using MODULE_DEVICE_TABLE(pci,...).
 * @probe:	This probing function माला_लो called (during execution
 *		of pci_रेजिस्टर_driver() क्रम alपढ़ोy existing
 *		devices or later अगर a new device माला_लो inserted) क्रम
 *		all PCI devices which match the ID table and are not
 *		"owned" by the other drivers yet. This function माला_लो
 *		passed a "struct pci_dev \*" क्रम each device whose
 *		entry in the ID table matches the device. The probe
 *		function वापसs zero when the driver chooses to
 *		take "ownership" of the device or an error code
 *		(negative number) otherwise.
 *		The probe function always माला_लो called from process
 *		context, so it can sleep.
 * @हटाओ:	The हटाओ() function माला_लो called whenever a device
 *		being handled by this driver is हटाओd (either during
 *		deregistration of the driver or when it's manually
 *		pulled out of a hot-pluggable slot).
 *		The हटाओ function always माला_लो called from process
 *		context, so it can sleep.
 * @suspend:	Put device पूर्णांकo low घातer state.
 * @resume:	Wake device from low घातer state.
 *		(Please see Documentation/घातer/pci.rst क्रम descriptions
 *		of PCI Power Management and the related functions.)
 * @shutकरोwn:	Hook पूर्णांकo reboot_notअगरier_list (kernel/sys.c).
 *		Intended to stop any idling DMA operations.
 *		Useful क्रम enabling wake-on-lan (NIC) or changing
 *		the घातer state of a device beक्रमe reboot.
 *		e.g. drivers/net/e100.c.
 * @sriov_configure: Optional driver callback to allow configuration of
 *		number of VFs to enable via sysfs "sriov_numvfs" file.
 * @sriov_set_msix_vec_count: PF Driver callback to change number of MSI-X
 *              vectors on a VF. Triggered via sysfs "sriov_vf_msix_count".
 *              This will change MSI-X Table Size in the VF Message Control
 *              रेजिस्टरs.
 * @sriov_get_vf_total_msix: PF driver callback to get the total number of
 *              MSI-X vectors available क्रम distribution to the VFs.
 * @err_handler: See Documentation/PCI/pci-error-recovery.rst
 * @groups:	Sysfs attribute groups.
 * @driver:	Driver model काष्ठाure.
 * @dynids:	List of dynamically added device IDs.
 */
काष्ठा pci_driver अणु
	काष्ठा list_head	node;
	स्थिर अक्षर		*name;
	स्थिर काष्ठा pci_device_id *id_table;	/* Must be non-शून्य क्रम probe to be called */
	पूर्णांक  (*probe)(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id);	/* New device inserted */
	व्योम (*हटाओ)(काष्ठा pci_dev *dev);	/* Device हटाओd (शून्य अगर not a hot-plug capable driver) */
	पूर्णांक  (*suspend)(काष्ठा pci_dev *dev, pm_message_t state);	/* Device suspended */
	पूर्णांक  (*resume)(काष्ठा pci_dev *dev);	/* Device woken up */
	व्योम (*shutकरोwn)(काष्ठा pci_dev *dev);
	पूर्णांक  (*sriov_configure)(काष्ठा pci_dev *dev, पूर्णांक num_vfs); /* On PF */
	पूर्णांक  (*sriov_set_msix_vec_count)(काष्ठा pci_dev *vf, पूर्णांक msix_vec_count); /* On PF */
	u32  (*sriov_get_vf_total_msix)(काष्ठा pci_dev *pf);
	स्थिर काष्ठा pci_error_handlers *err_handler;
	स्थिर काष्ठा attribute_group **groups;
	काष्ठा device_driver	driver;
	काष्ठा pci_dynids	dynids;
पूर्ण;

#घोषणा	to_pci_driver(drv) container_of(drv, काष्ठा pci_driver, driver)

/**
 * PCI_DEVICE - macro used to describe a specअगरic PCI device
 * @vend: the 16 bit PCI Venकरोr ID
 * @dev: the 16 bit PCI Device ID
 *
 * This macro is used to create a काष्ठा pci_device_id that matches a
 * specअगरic device.  The subvenकरोr and subdevice fields will be set to
 * PCI_ANY_ID.
 */
#घोषणा PCI_DEVICE(vend,dev) \
	.venकरोr = (vend), .device = (dev), \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID

/**
 * PCI_DEVICE_SUB - macro used to describe a specअगरic PCI device with subप्रणाली
 * @vend: the 16 bit PCI Venकरोr ID
 * @dev: the 16 bit PCI Device ID
 * @subvend: the 16 bit PCI Subvenकरोr ID
 * @subdev: the 16 bit PCI Subdevice ID
 *
 * This macro is used to create a काष्ठा pci_device_id that matches a
 * specअगरic device with subप्रणाली inक्रमmation.
 */
#घोषणा PCI_DEVICE_SUB(vend, dev, subvend, subdev) \
	.venकरोr = (vend), .device = (dev), \
	.subvenकरोr = (subvend), .subdevice = (subdev)

/**
 * PCI_DEVICE_CLASS - macro used to describe a specअगरic PCI device class
 * @dev_class: the class, subclass, prog-अगर triple क्रम this device
 * @dev_class_mask: the class mask क्रम this device
 *
 * This macro is used to create a काष्ठा pci_device_id that matches a
 * specअगरic PCI class.  The venकरोr, device, subvenकरोr, and subdevice
 * fields will be set to PCI_ANY_ID.
 */
#घोषणा PCI_DEVICE_CLASS(dev_class,dev_class_mask) \
	.class = (dev_class), .class_mask = (dev_class_mask), \
	.venकरोr = PCI_ANY_ID, .device = PCI_ANY_ID, \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID

/**
 * PCI_VDEVICE - macro used to describe a specअगरic PCI device in लघु क्रमm
 * @vend: the venकरोr name
 * @dev: the 16 bit PCI Device ID
 *
 * This macro is used to create a काष्ठा pci_device_id that matches a
 * specअगरic PCI device.  The subvenकरोr, and subdevice fields will be set
 * to PCI_ANY_ID. The macro allows the next field to follow as the device
 * निजी data.
 */
#घोषणा PCI_VDEVICE(vend, dev) \
	.venकरोr = PCI_VENDOR_ID_##vend, .device = (dev), \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID, 0, 0

/**
 * PCI_DEVICE_DATA - macro used to describe a specअगरic PCI device in very लघु क्रमm
 * @vend: the venकरोr name (without PCI_VENDOR_ID_ prefix)
 * @dev: the device name (without PCI_DEVICE_ID_<vend>_ prefix)
 * @data: the driver data to be filled
 *
 * This macro is used to create a काष्ठा pci_device_id that matches a
 * specअगरic PCI device.  The subvenकरोr, and subdevice fields will be set
 * to PCI_ANY_ID.
 */
#घोषणा PCI_DEVICE_DATA(vend, dev, data) \
	.venकरोr = PCI_VENDOR_ID_##vend, .device = PCI_DEVICE_ID_##vend##_##dev, \
	.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID, 0, 0, \
	.driver_data = (kernel_uदीर्घ_t)(data)

क्रमागत अणु
	PCI_REASSIGN_ALL_RSRC	= 0x00000001,	/* Ignore firmware setup */
	PCI_REASSIGN_ALL_BUS	= 0x00000002,	/* Reassign all bus numbers */
	PCI_PROBE_ONLY		= 0x00000004,	/* Use existing setup */
	PCI_CAN_SKIP_ISA_ALIGN	= 0x00000008,	/* Don't करो ISA alignment */
	PCI_ENABLE_PROC_DOMAINS	= 0x00000010,	/* Enable करोमुख्यs in /proc */
	PCI_COMPAT_DOMAIN_0	= 0x00000020,	/* ... except करोमुख्य 0 */
	PCI_SCAN_ALL_PCIE_DEVS	= 0x00000040,	/* Scan all, not just dev 0 */
पूर्ण;

#घोषणा PCI_IRQ_LEGACY		(1 << 0) /* Allow legacy पूर्णांकerrupts */
#घोषणा PCI_IRQ_MSI		(1 << 1) /* Allow MSI पूर्णांकerrupts */
#घोषणा PCI_IRQ_MSIX		(1 << 2) /* Allow MSI-X पूर्णांकerrupts */
#घोषणा PCI_IRQ_AFFINITY	(1 << 3) /* Auto-assign affinity */

/* These बाह्यal functions are only available when PCI support is enabled */
#अगर_घोषित CONFIG_PCI

बाह्य अचिन्हित पूर्णांक pci_flags;

अटल अंतरभूत व्योम pci_set_flags(पूर्णांक flags) अणु pci_flags = flags; पूर्ण
अटल अंतरभूत व्योम pci_add_flags(पूर्णांक flags) अणु pci_flags |= flags; पूर्ण
अटल अंतरभूत व्योम pci_clear_flags(पूर्णांक flags) अणु pci_flags &= ~flags; पूर्ण
अटल अंतरभूत पूर्णांक pci_has_flag(पूर्णांक flag) अणु वापस pci_flags & flag; पूर्ण

व्योम pcie_bus_configure_settings(काष्ठा pci_bus *bus);

क्रमागत pcie_bus_config_types अणु
	PCIE_BUS_TUNE_OFF,	/* Don't touch MPS at all */
	PCIE_BUS_DEFAULT,	/* Ensure MPS matches upstream bridge */
	PCIE_BUS_SAFE,		/* Use largest MPS boot-समय devices support */
	PCIE_BUS_PERFORMANCE,	/* Use MPS and MRRS क्रम best perक्रमmance */
	PCIE_BUS_PEER2PEER,	/* Set MPS = 128 क्रम all devices */
पूर्ण;

बाह्य क्रमागत pcie_bus_config_types pcie_bus_config;

बाह्य काष्ठा bus_type pci_bus_type;

/* Do NOT directly access these two variables, unless you are arch-specअगरic PCI
 * code, or PCI core code. */
बाह्य काष्ठा list_head pci_root_buses;	/* List of all known PCI buses */
/* Some device drivers need know अगर PCI is initiated */
पूर्णांक no_pci_devices(व्योम);

व्योम pcibios_resource_survey_bus(काष्ठा pci_bus *bus);
व्योम pcibios_bus_add_device(काष्ठा pci_dev *pdev);
व्योम pcibios_add_bus(काष्ठा pci_bus *bus);
व्योम pcibios_हटाओ_bus(काष्ठा pci_bus *bus);
व्योम pcibios_fixup_bus(काष्ठा pci_bus *);
पूर्णांक __must_check pcibios_enable_device(काष्ठा pci_dev *, पूर्णांक mask);
/* Architecture-specअगरic versions may override this (weak) */
अक्षर *pcibios_setup(अक्षर *str);

/* Used only when drivers/pci/setup.c is used */
resource_माप_प्रकार pcibios_align_resource(व्योम *, स्थिर काष्ठा resource *,
				resource_माप_प्रकार,
				resource_माप_प्रकार);

/* Weak but can be overridden by arch */
व्योम pci_fixup_cardbus(काष्ठा pci_bus *);

/* Generic PCI functions used पूर्णांकernally */

व्योम pcibios_resource_to_bus(काष्ठा pci_bus *bus, काष्ठा pci_bus_region *region,
			     काष्ठा resource *res);
व्योम pcibios_bus_to_resource(काष्ठा pci_bus *bus, काष्ठा resource *res,
			     काष्ठा pci_bus_region *region);
व्योम pcibios_scan_specअगरic_bus(पूर्णांक busn);
काष्ठा pci_bus *pci_find_bus(पूर्णांक करोमुख्य, पूर्णांक busnr);
व्योम pci_bus_add_devices(स्थिर काष्ठा pci_bus *bus);
काष्ठा pci_bus *pci_scan_bus(पूर्णांक bus, काष्ठा pci_ops *ops, व्योम *sysdata);
काष्ठा pci_bus *pci_create_root_bus(काष्ठा device *parent, पूर्णांक bus,
				    काष्ठा pci_ops *ops, व्योम *sysdata,
				    काष्ठा list_head *resources);
पूर्णांक pci_host_probe(काष्ठा pci_host_bridge *bridge);
पूर्णांक pci_bus_insert_busn_res(काष्ठा pci_bus *b, पूर्णांक bus, पूर्णांक busmax);
पूर्णांक pci_bus_update_busn_res_end(काष्ठा pci_bus *b, पूर्णांक busmax);
व्योम pci_bus_release_busn_res(काष्ठा pci_bus *b);
काष्ठा pci_bus *pci_scan_root_bus(काष्ठा device *parent, पूर्णांक bus,
				  काष्ठा pci_ops *ops, व्योम *sysdata,
				  काष्ठा list_head *resources);
पूर्णांक pci_scan_root_bus_bridge(काष्ठा pci_host_bridge *bridge);
काष्ठा pci_bus *pci_add_new_bus(काष्ठा pci_bus *parent, काष्ठा pci_dev *dev,
				पूर्णांक busnr);
काष्ठा pci_slot *pci_create_slot(काष्ठा pci_bus *parent, पूर्णांक slot_nr,
				 स्थिर अक्षर *name,
				 काष्ठा hotplug_slot *hotplug);
व्योम pci_destroy_slot(काष्ठा pci_slot *slot);
#अगर_घोषित CONFIG_SYSFS
व्योम pci_dev_assign_slot(काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत व्योम pci_dev_assign_slot(काष्ठा pci_dev *dev) अणु पूर्ण
#पूर्ण_अगर
पूर्णांक pci_scan_slot(काष्ठा pci_bus *bus, पूर्णांक devfn);
काष्ठा pci_dev *pci_scan_single_device(काष्ठा pci_bus *bus, पूर्णांक devfn);
व्योम pci_device_add(काष्ठा pci_dev *dev, काष्ठा pci_bus *bus);
अचिन्हित पूर्णांक pci_scan_child_bus(काष्ठा pci_bus *bus);
व्योम pci_bus_add_device(काष्ठा pci_dev *dev);
व्योम pci_पढ़ो_bridge_bases(काष्ठा pci_bus *child);
काष्ठा resource *pci_find_parent_resource(स्थिर काष्ठा pci_dev *dev,
					  काष्ठा resource *res);
u8 pci_swizzle_पूर्णांकerrupt_pin(स्थिर काष्ठा pci_dev *dev, u8 pin);
पूर्णांक pci_get_पूर्णांकerrupt_pin(काष्ठा pci_dev *dev, काष्ठा pci_dev **bridge);
u8 pci_common_swizzle(काष्ठा pci_dev *dev, u8 *pinp);
काष्ठा pci_dev *pci_dev_get(काष्ठा pci_dev *dev);
व्योम pci_dev_put(काष्ठा pci_dev *dev);
व्योम pci_हटाओ_bus(काष्ठा pci_bus *b);
व्योम pci_stop_and_हटाओ_bus_device(काष्ठा pci_dev *dev);
व्योम pci_stop_and_हटाओ_bus_device_locked(काष्ठा pci_dev *dev);
व्योम pci_stop_root_bus(काष्ठा pci_bus *bus);
व्योम pci_हटाओ_root_bus(काष्ठा pci_bus *bus);
व्योम pci_setup_cardbus(काष्ठा pci_bus *bus);
व्योम pcibios_setup_bridge(काष्ठा pci_bus *bus, अचिन्हित दीर्घ type);
व्योम pci_sort_bपढ़ोthfirst(व्योम);
#घोषणा dev_is_pci(d) ((d)->bus == &pci_bus_type)
#घोषणा dev_is_pf(d) ((dev_is_pci(d) ? to_pci_dev(d)->is_physfn : false))

/* Generic PCI functions exported to card drivers */

u8 pci_bus_find_capability(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक cap);
u8 pci_find_capability(काष्ठा pci_dev *dev, पूर्णांक cap);
u8 pci_find_next_capability(काष्ठा pci_dev *dev, u8 pos, पूर्णांक cap);
u8 pci_find_ht_capability(काष्ठा pci_dev *dev, पूर्णांक ht_cap);
u8 pci_find_next_ht_capability(काष्ठा pci_dev *dev, u8 pos, पूर्णांक ht_cap);
u16 pci_find_ext_capability(काष्ठा pci_dev *dev, पूर्णांक cap);
u16 pci_find_next_ext_capability(काष्ठा pci_dev *dev, u16 pos, पूर्णांक cap);
काष्ठा pci_bus *pci_find_next_bus(स्थिर काष्ठा pci_bus *from);
u16 pci_find_vsec_capability(काष्ठा pci_dev *dev, u16 venकरोr, पूर्णांक cap);

u64 pci_get_dsn(काष्ठा pci_dev *dev);

काष्ठा pci_dev *pci_get_device(अचिन्हित पूर्णांक venकरोr, अचिन्हित पूर्णांक device,
			       काष्ठा pci_dev *from);
काष्ठा pci_dev *pci_get_subsys(अचिन्हित पूर्णांक venकरोr, अचिन्हित पूर्णांक device,
			       अचिन्हित पूर्णांक ss_venकरोr, अचिन्हित पूर्णांक ss_device,
			       काष्ठा pci_dev *from);
काष्ठा pci_dev *pci_get_slot(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn);
काष्ठा pci_dev *pci_get_करोमुख्य_bus_and_slot(पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
					    अचिन्हित पूर्णांक devfn);
काष्ठा pci_dev *pci_get_class(अचिन्हित पूर्णांक class, काष्ठा pci_dev *from);
पूर्णांक pci_dev_present(स्थिर काष्ठा pci_device_id *ids);

पूर्णांक pci_bus_पढ़ो_config_byte(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, u8 *val);
पूर्णांक pci_bus_पढ़ो_config_word(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, u16 *val);
पूर्णांक pci_bus_पढ़ो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, u32 *val);
पूर्णांक pci_bus_ग_लिखो_config_byte(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, u8 val);
पूर्णांक pci_bus_ग_लिखो_config_word(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, u16 val);
पूर्णांक pci_bus_ग_लिखो_config_dword(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, u32 val);

पूर्णांक pci_generic_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, पूर्णांक size, u32 *val);
पूर्णांक pci_generic_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, पूर्णांक size, u32 val);
पूर्णांक pci_generic_config_पढ़ो32(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 *val);
पूर्णांक pci_generic_config_ग_लिखो32(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 val);

काष्ठा pci_ops *pci_bus_set_ops(काष्ठा pci_bus *bus, काष्ठा pci_ops *ops);

पूर्णांक pci_पढ़ो_config_byte(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u8 *val);
पूर्णांक pci_पढ़ो_config_word(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u16 *val);
पूर्णांक pci_पढ़ो_config_dword(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u32 *val);
पूर्णांक pci_ग_लिखो_config_byte(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u8 val);
पूर्णांक pci_ग_लिखो_config_word(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u16 val);
पूर्णांक pci_ग_लिखो_config_dword(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u32 val);

पूर्णांक pcie_capability_पढ़ो_word(काष्ठा pci_dev *dev, पूर्णांक pos, u16 *val);
पूर्णांक pcie_capability_पढ़ो_dword(काष्ठा pci_dev *dev, पूर्णांक pos, u32 *val);
पूर्णांक pcie_capability_ग_लिखो_word(काष्ठा pci_dev *dev, पूर्णांक pos, u16 val);
पूर्णांक pcie_capability_ग_लिखो_dword(काष्ठा pci_dev *dev, पूर्णांक pos, u32 val);
पूर्णांक pcie_capability_clear_and_set_word(काष्ठा pci_dev *dev, पूर्णांक pos,
				       u16 clear, u16 set);
पूर्णांक pcie_capability_clear_and_set_dword(काष्ठा pci_dev *dev, पूर्णांक pos,
					u32 clear, u32 set);

अटल अंतरभूत पूर्णांक pcie_capability_set_word(काष्ठा pci_dev *dev, पूर्णांक pos,
					   u16 set)
अणु
	वापस pcie_capability_clear_and_set_word(dev, pos, 0, set);
पूर्ण

अटल अंतरभूत पूर्णांक pcie_capability_set_dword(काष्ठा pci_dev *dev, पूर्णांक pos,
					    u32 set)
अणु
	वापस pcie_capability_clear_and_set_dword(dev, pos, 0, set);
पूर्ण

अटल अंतरभूत पूर्णांक pcie_capability_clear_word(काष्ठा pci_dev *dev, पूर्णांक pos,
					     u16 clear)
अणु
	वापस pcie_capability_clear_and_set_word(dev, pos, clear, 0);
पूर्ण

अटल अंतरभूत पूर्णांक pcie_capability_clear_dword(काष्ठा pci_dev *dev, पूर्णांक pos,
					      u32 clear)
अणु
	वापस pcie_capability_clear_and_set_dword(dev, pos, clear, 0);
पूर्ण

/* User-space driven config access */
पूर्णांक pci_user_पढ़ो_config_byte(काष्ठा pci_dev *dev, पूर्णांक where, u8 *val);
पूर्णांक pci_user_पढ़ो_config_word(काष्ठा pci_dev *dev, पूर्णांक where, u16 *val);
पूर्णांक pci_user_पढ़ो_config_dword(काष्ठा pci_dev *dev, पूर्णांक where, u32 *val);
पूर्णांक pci_user_ग_लिखो_config_byte(काष्ठा pci_dev *dev, पूर्णांक where, u8 val);
पूर्णांक pci_user_ग_लिखो_config_word(काष्ठा pci_dev *dev, पूर्णांक where, u16 val);
पूर्णांक pci_user_ग_लिखो_config_dword(काष्ठा pci_dev *dev, पूर्णांक where, u32 val);

पूर्णांक __must_check pci_enable_device(काष्ठा pci_dev *dev);
पूर्णांक __must_check pci_enable_device_io(काष्ठा pci_dev *dev);
पूर्णांक __must_check pci_enable_device_mem(काष्ठा pci_dev *dev);
पूर्णांक __must_check pci_reenable_device(काष्ठा pci_dev *);
पूर्णांक __must_check pcim_enable_device(काष्ठा pci_dev *pdev);
व्योम pcim_pin_device(काष्ठा pci_dev *pdev);

अटल अंतरभूत bool pci_पूर्णांकx_mask_supported(काष्ठा pci_dev *pdev)
अणु
	/*
	 * INTx masking is supported अगर PCI_COMMAND_INTX_DISABLE is
	 * writable and no quirk has marked the feature broken.
	 */
	वापस !pdev->broken_पूर्णांकx_masking;
पूर्ण

अटल अंतरभूत पूर्णांक pci_is_enabled(काष्ठा pci_dev *pdev)
अणु
	वापस (atomic_पढ़ो(&pdev->enable_cnt) > 0);
पूर्ण

अटल अंतरभूत पूर्णांक pci_is_managed(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->is_managed;
पूर्ण

व्योम pci_disable_device(काष्ठा pci_dev *dev);

बाह्य अचिन्हित पूर्णांक pcibios_max_latency;
व्योम pci_set_master(काष्ठा pci_dev *dev);
व्योम pci_clear_master(काष्ठा pci_dev *dev);

पूर्णांक pci_set_pcie_reset_state(काष्ठा pci_dev *dev, क्रमागत pcie_reset_state state);
पूर्णांक pci_set_cacheline_size(काष्ठा pci_dev *dev);
पूर्णांक __must_check pci_set_mwi(काष्ठा pci_dev *dev);
पूर्णांक __must_check pcim_set_mwi(काष्ठा pci_dev *dev);
पूर्णांक pci_try_set_mwi(काष्ठा pci_dev *dev);
व्योम pci_clear_mwi(काष्ठा pci_dev *dev);
व्योम pci_disable_parity(काष्ठा pci_dev *dev);
व्योम pci_पूर्णांकx(काष्ठा pci_dev *dev, पूर्णांक enable);
bool pci_check_and_mask_पूर्णांकx(काष्ठा pci_dev *dev);
bool pci_check_and_unmask_पूर्णांकx(काष्ठा pci_dev *dev);
पूर्णांक pci_रुको_क्रम_pending(काष्ठा pci_dev *dev, पूर्णांक pos, u16 mask);
पूर्णांक pci_रुको_क्रम_pending_transaction(काष्ठा pci_dev *dev);
पूर्णांक pcix_get_max_mmrbc(काष्ठा pci_dev *dev);
पूर्णांक pcix_get_mmrbc(काष्ठा pci_dev *dev);
पूर्णांक pcix_set_mmrbc(काष्ठा pci_dev *dev, पूर्णांक mmrbc);
पूर्णांक pcie_get_पढ़ोrq(काष्ठा pci_dev *dev);
पूर्णांक pcie_set_पढ़ोrq(काष्ठा pci_dev *dev, पूर्णांक rq);
पूर्णांक pcie_get_mps(काष्ठा pci_dev *dev);
पूर्णांक pcie_set_mps(काष्ठा pci_dev *dev, पूर्णांक mps);
u32 pcie_bandwidth_available(काष्ठा pci_dev *dev, काष्ठा pci_dev **limiting_dev,
			     क्रमागत pci_bus_speed *speed,
			     क्रमागत pcie_link_width *width);
व्योम pcie_prपूर्णांक_link_status(काष्ठा pci_dev *dev);
bool pcie_has_flr(काष्ठा pci_dev *dev);
पूर्णांक pcie_flr(काष्ठा pci_dev *dev);
पूर्णांक __pci_reset_function_locked(काष्ठा pci_dev *dev);
पूर्णांक pci_reset_function(काष्ठा pci_dev *dev);
पूर्णांक pci_reset_function_locked(काष्ठा pci_dev *dev);
पूर्णांक pci_try_reset_function(काष्ठा pci_dev *dev);
पूर्णांक pci_probe_reset_slot(काष्ठा pci_slot *slot);
पूर्णांक pci_probe_reset_bus(काष्ठा pci_bus *bus);
पूर्णांक pci_reset_bus(काष्ठा pci_dev *dev);
व्योम pci_reset_secondary_bus(काष्ठा pci_dev *dev);
व्योम pcibios_reset_secondary_bus(काष्ठा pci_dev *dev);
व्योम pci_update_resource(काष्ठा pci_dev *dev, पूर्णांक resno);
पूर्णांक __must_check pci_assign_resource(काष्ठा pci_dev *dev, पूर्णांक i);
पूर्णांक __must_check pci_reassign_resource(काष्ठा pci_dev *dev, पूर्णांक i, resource_माप_प्रकार add_size, resource_माप_प्रकार align);
व्योम pci_release_resource(काष्ठा pci_dev *dev, पूर्णांक resno);
अटल अंतरभूत पूर्णांक pci_rebar_bytes_to_size(u64 bytes)
अणु
	bytes = roundup_घात_of_two(bytes);

	/* Return BAR size as defined in the resizable BAR specअगरication */
	वापस max(ilog2(bytes), 20) - 20;
पूर्ण

u32 pci_rebar_get_possible_sizes(काष्ठा pci_dev *pdev, पूर्णांक bar);
पूर्णांक __must_check pci_resize_resource(काष्ठा pci_dev *dev, पूर्णांक i, पूर्णांक size);
पूर्णांक pci_select_bars(काष्ठा pci_dev *dev, अचिन्हित दीर्घ flags);
bool pci_device_is_present(काष्ठा pci_dev *pdev);
व्योम pci_ignore_hotplug(काष्ठा pci_dev *dev);
काष्ठा pci_dev *pci_real_dma_dev(काष्ठा pci_dev *dev);
पूर्णांक pci_status_get_and_clear_errors(काष्ठा pci_dev *pdev);

पूर्णांक __म_लिखो(6, 7) pci_request_irq(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr,
		irq_handler_t handler, irq_handler_t thपढ़ो_fn, व्योम *dev_id,
		स्थिर अक्षर *fmt, ...);
व्योम pci_मुक्त_irq(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr, व्योम *dev_id);

/* ROM control related routines */
पूर्णांक pci_enable_rom(काष्ठा pci_dev *pdev);
व्योम pci_disable_rom(काष्ठा pci_dev *pdev);
व्योम __iomem __must_check *pci_map_rom(काष्ठा pci_dev *pdev, माप_प्रकार *size);
व्योम pci_unmap_rom(काष्ठा pci_dev *pdev, व्योम __iomem *rom);

/* Power management related routines */
पूर्णांक pci_save_state(काष्ठा pci_dev *dev);
व्योम pci_restore_state(काष्ठा pci_dev *dev);
काष्ठा pci_saved_state *pci_store_saved_state(काष्ठा pci_dev *dev);
पूर्णांक pci_load_saved_state(काष्ठा pci_dev *dev,
			 काष्ठा pci_saved_state *state);
पूर्णांक pci_load_and_मुक्त_saved_state(काष्ठा pci_dev *dev,
				  काष्ठा pci_saved_state **state);
काष्ठा pci_cap_saved_state *pci_find_saved_cap(काष्ठा pci_dev *dev, अक्षर cap);
काष्ठा pci_cap_saved_state *pci_find_saved_ext_cap(काष्ठा pci_dev *dev,
						   u16 cap);
पूर्णांक pci_add_cap_save_buffer(काष्ठा pci_dev *dev, अक्षर cap, अचिन्हित पूर्णांक size);
पूर्णांक pci_add_ext_cap_save_buffer(काष्ठा pci_dev *dev,
				u16 cap, अचिन्हित पूर्णांक size);
पूर्णांक pci_platक्रमm_घातer_transition(काष्ठा pci_dev *dev, pci_घातer_t state);
पूर्णांक pci_set_घातer_state(काष्ठा pci_dev *dev, pci_घातer_t state);
pci_घातer_t pci_choose_state(काष्ठा pci_dev *dev, pm_message_t state);
bool pci_pme_capable(काष्ठा pci_dev *dev, pci_घातer_t state);
व्योम pci_pme_active(काष्ठा pci_dev *dev, bool enable);
पूर्णांक pci_enable_wake(काष्ठा pci_dev *dev, pci_घातer_t state, bool enable);
पूर्णांक pci_wake_from_d3(काष्ठा pci_dev *dev, bool enable);
पूर्णांक pci_prepare_to_sleep(काष्ठा pci_dev *dev);
पूर्णांक pci_back_from_sleep(काष्ठा pci_dev *dev);
bool pci_dev_run_wake(काष्ठा pci_dev *dev);
व्योम pci_d3cold_enable(काष्ठा pci_dev *dev);
व्योम pci_d3cold_disable(काष्ठा pci_dev *dev);
bool pcie_relaxed_ordering_enabled(काष्ठा pci_dev *dev);
व्योम pci_resume_bus(काष्ठा pci_bus *bus);
व्योम pci_bus_set_current_state(काष्ठा pci_bus *bus, pci_घातer_t state);

/* For use by arch with custom probe code */
व्योम set_pcie_port_type(काष्ठा pci_dev *pdev);
व्योम set_pcie_hotplug_bridge(काष्ठा pci_dev *pdev);

/* Functions क्रम PCI Hotplug drivers to use */
अचिन्हित पूर्णांक pci_rescan_bus_bridge_resize(काष्ठा pci_dev *bridge);
अचिन्हित पूर्णांक pci_rescan_bus(काष्ठा pci_bus *bus);
व्योम pci_lock_rescan_हटाओ(व्योम);
व्योम pci_unlock_rescan_हटाओ(व्योम);

/* Vital Product Data routines */
sमाप_प्रकार pci_पढ़ो_vpd(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count, व्योम *buf);
sमाप_प्रकार pci_ग_लिखो_vpd(काष्ठा pci_dev *dev, loff_t pos, माप_प्रकार count, स्थिर व्योम *buf);

/* Helper functions क्रम low-level code (drivers/pci/setup-[bus,res].c) */
resource_माप_प्रकार pcibios_retrieve_fw_addr(काष्ठा pci_dev *dev, पूर्णांक idx);
व्योम pci_bus_assign_resources(स्थिर काष्ठा pci_bus *bus);
व्योम pci_bus_claim_resources(काष्ठा pci_bus *bus);
व्योम pci_bus_size_bridges(काष्ठा pci_bus *bus);
पूर्णांक pci_claim_resource(काष्ठा pci_dev *, पूर्णांक);
पूर्णांक pci_claim_bridge_resource(काष्ठा pci_dev *bridge, पूर्णांक i);
व्योम pci_assign_unasचिन्हित_resources(व्योम);
व्योम pci_assign_unasचिन्हित_bridge_resources(काष्ठा pci_dev *bridge);
व्योम pci_assign_unasचिन्हित_bus_resources(काष्ठा pci_bus *bus);
व्योम pci_assign_unasचिन्हित_root_bus_resources(काष्ठा pci_bus *bus);
पूर्णांक pci_reassign_bridge_resources(काष्ठा pci_dev *bridge, अचिन्हित दीर्घ type);
व्योम pdev_enable_device(काष्ठा pci_dev *);
पूर्णांक pci_enable_resources(काष्ठा pci_dev *, पूर्णांक mask);
व्योम pci_assign_irq(काष्ठा pci_dev *dev);
काष्ठा resource *pci_find_resource(काष्ठा pci_dev *dev, काष्ठा resource *res);
#घोषणा HAVE_PCI_REQ_REGIONS	2
पूर्णांक __must_check pci_request_regions(काष्ठा pci_dev *, स्थिर अक्षर *);
पूर्णांक __must_check pci_request_regions_exclusive(काष्ठा pci_dev *, स्थिर अक्षर *);
व्योम pci_release_regions(काष्ठा pci_dev *);
पूर्णांक __must_check pci_request_region(काष्ठा pci_dev *, पूर्णांक, स्थिर अक्षर *);
व्योम pci_release_region(काष्ठा pci_dev *, पूर्णांक);
पूर्णांक pci_request_selected_regions(काष्ठा pci_dev *, पूर्णांक, स्थिर अक्षर *);
पूर्णांक pci_request_selected_regions_exclusive(काष्ठा pci_dev *, पूर्णांक, स्थिर अक्षर *);
व्योम pci_release_selected_regions(काष्ठा pci_dev *, पूर्णांक);

/* drivers/pci/bus.c */
व्योम pci_add_resource(काष्ठा list_head *resources, काष्ठा resource *res);
व्योम pci_add_resource_offset(काष्ठा list_head *resources, काष्ठा resource *res,
			     resource_माप_प्रकार offset);
व्योम pci_मुक्त_resource_list(काष्ठा list_head *resources);
व्योम pci_bus_add_resource(काष्ठा pci_bus *bus, काष्ठा resource *res,
			  अचिन्हित पूर्णांक flags);
काष्ठा resource *pci_bus_resource_n(स्थिर काष्ठा pci_bus *bus, पूर्णांक n);
व्योम pci_bus_हटाओ_resources(काष्ठा pci_bus *bus);
पूर्णांक devm_request_pci_bus_resources(काष्ठा device *dev,
				   काष्ठा list_head *resources);

/* Temporary until new and working PCI SBR API in place */
पूर्णांक pci_bridge_secondary_bus_reset(काष्ठा pci_dev *dev);

#घोषणा pci_bus_क्रम_each_resource(bus, res, i)				\
	क्रम (i = 0;							\
	    (res = pci_bus_resource_n(bus, i)) || i < PCI_BRIDGE_RESOURCE_NUM; \
	     i++)

पूर्णांक __must_check pci_bus_alloc_resource(काष्ठा pci_bus *bus,
			काष्ठा resource *res, resource_माप_प्रकार size,
			resource_माप_प्रकार align, resource_माप_प्रकार min,
			अचिन्हित दीर्घ type_mask,
			resource_माप_प्रकार (*alignf)(व्योम *,
						  स्थिर काष्ठा resource *,
						  resource_माप_प्रकार,
						  resource_माप_प्रकार),
			व्योम *alignf_data);


पूर्णांक pci_रेजिस्टर_io_range(काष्ठा fwnode_handle *fwnode, phys_addr_t addr,
			resource_माप_प्रकार size);
अचिन्हित दीर्घ pci_address_to_pio(phys_addr_t addr);
phys_addr_t pci_pio_to_address(अचिन्हित दीर्घ pio);
पूर्णांक pci_remap_iospace(स्थिर काष्ठा resource *res, phys_addr_t phys_addr);
पूर्णांक devm_pci_remap_iospace(काष्ठा device *dev, स्थिर काष्ठा resource *res,
			   phys_addr_t phys_addr);
व्योम pci_unmap_iospace(काष्ठा resource *res);
व्योम __iomem *devm_pci_remap_cfgspace(काष्ठा device *dev,
				      resource_माप_प्रकार offset,
				      resource_माप_प्रकार size);
व्योम __iomem *devm_pci_remap_cfg_resource(काष्ठा device *dev,
					  काष्ठा resource *res);

अटल अंतरभूत pci_bus_addr_t pci_bus_address(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	काष्ठा pci_bus_region region;

	pcibios_resource_to_bus(pdev->bus, &region, &pdev->resource[bar]);
	वापस region.start;
पूर्ण

/* Proper probing supporting hot-pluggable devices */
पूर्णांक __must_check __pci_रेजिस्टर_driver(काष्ठा pci_driver *, काष्ठा module *,
				       स्थिर अक्षर *mod_name);

/* pci_रेजिस्टर_driver() must be a macro so KBUILD_MODNAME can be expanded */
#घोषणा pci_रेजिस्टर_driver(driver)		\
	__pci_रेजिस्टर_driver(driver, THIS_MODULE, KBUILD_MODNAME)

व्योम pci_unरेजिस्टर_driver(काष्ठा pci_driver *dev);

/**
 * module_pci_driver() - Helper macro क्रम रेजिस्टरing a PCI driver
 * @__pci_driver: pci_driver काष्ठा
 *
 * Helper macro क्रम PCI drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_pci_driver(__pci_driver) \
	module_driver(__pci_driver, pci_रेजिस्टर_driver, pci_unरेजिस्टर_driver)

/**
 * builtin_pci_driver() - Helper macro क्रम रेजिस्टरing a PCI driver
 * @__pci_driver: pci_driver काष्ठा
 *
 * Helper macro क्रम PCI drivers which करो not करो anything special in their
 * init code. This eliminates a lot of boilerplate. Each driver may only
 * use this macro once, and calling it replaces device_initcall(...)
 */
#घोषणा builtin_pci_driver(__pci_driver) \
	builtin_driver(__pci_driver, pci_रेजिस्टर_driver)

काष्ठा pci_driver *pci_dev_driver(स्थिर काष्ठा pci_dev *dev);
पूर्णांक pci_add_dynid(काष्ठा pci_driver *drv,
		  अचिन्हित पूर्णांक venकरोr, अचिन्हित पूर्णांक device,
		  अचिन्हित पूर्णांक subvenकरोr, अचिन्हित पूर्णांक subdevice,
		  अचिन्हित पूर्णांक class, अचिन्हित पूर्णांक class_mask,
		  अचिन्हित दीर्घ driver_data);
स्थिर काष्ठा pci_device_id *pci_match_id(स्थिर काष्ठा pci_device_id *ids,
					 काष्ठा pci_dev *dev);
पूर्णांक pci_scan_bridge(काष्ठा pci_bus *bus, काष्ठा pci_dev *dev, पूर्णांक max,
		    पूर्णांक pass);

व्योम pci_walk_bus(काष्ठा pci_bus *top, पूर्णांक (*cb)(काष्ठा pci_dev *, व्योम *),
		  व्योम *userdata);
पूर्णांक pci_cfg_space_size(काष्ठा pci_dev *dev);
अचिन्हित अक्षर pci_bus_max_busnr(काष्ठा pci_bus *bus);
व्योम pci_setup_bridge(काष्ठा pci_bus *bus);
resource_माप_प्रकार pcibios_winकरोw_alignment(काष्ठा pci_bus *bus,
					 अचिन्हित दीर्घ type);

#घोषणा PCI_VGA_STATE_CHANGE_BRIDGE (1 << 0)
#घोषणा PCI_VGA_STATE_CHANGE_DECODES (1 << 1)

पूर्णांक pci_set_vga_state(काष्ठा pci_dev *pdev, bool decode,
		      अचिन्हित पूर्णांक command_bits, u32 flags);

/*
 * Virtual पूर्णांकerrupts allow क्रम more पूर्णांकerrupts to be allocated
 * than the device has पूर्णांकerrupts क्रम. These are not programmed
 * पूर्णांकo the device's MSI-X table and must be handled by some
 * other driver means.
 */
#घोषणा PCI_IRQ_VIRTUAL		(1 << 4)

#घोषणा PCI_IRQ_ALL_TYPES \
	(PCI_IRQ_LEGACY | PCI_IRQ_MSI | PCI_IRQ_MSIX)

/* kmem_cache style wrapper around pci_alloc_consistent() */

#समावेश <linux/dmapool.h>

#घोषणा	pci_pool dma_pool
#घोषणा pci_pool_create(name, pdev, size, align, allocation) \
		dma_pool_create(name, &pdev->dev, size, align, allocation)
#घोषणा	pci_pool_destroy(pool) dma_pool_destroy(pool)
#घोषणा	pci_pool_alloc(pool, flags, handle) dma_pool_alloc(pool, flags, handle)
#घोषणा	pci_pool_zalloc(pool, flags, handle) \
		dma_pool_zalloc(pool, flags, handle)
#घोषणा	pci_pool_मुक्त(pool, vaddr, addr) dma_pool_मुक्त(pool, vaddr, addr)

काष्ठा msix_entry अणु
	u32	vector;	/* Kernel uses to ग_लिखो allocated vector */
	u16	entry;	/* Driver uses to specअगरy entry, OS ग_लिखोs */
पूर्ण;

#अगर_घोषित CONFIG_PCI_MSI
पूर्णांक pci_msi_vec_count(काष्ठा pci_dev *dev);
व्योम pci_disable_msi(काष्ठा pci_dev *dev);
पूर्णांक pci_msix_vec_count(काष्ठा pci_dev *dev);
व्योम pci_disable_msix(काष्ठा pci_dev *dev);
व्योम pci_restore_msi_state(काष्ठा pci_dev *dev);
पूर्णांक pci_msi_enabled(व्योम);
पूर्णांक pci_enable_msi(काष्ठा pci_dev *dev);
पूर्णांक pci_enable_msix_range(काष्ठा pci_dev *dev, काष्ठा msix_entry *entries,
			  पूर्णांक minvec, पूर्णांक maxvec);
अटल अंतरभूत पूर्णांक pci_enable_msix_exact(काष्ठा pci_dev *dev,
					काष्ठा msix_entry *entries, पूर्णांक nvec)
अणु
	पूर्णांक rc = pci_enable_msix_range(dev, entries, nvec, nvec);
	अगर (rc < 0)
		वापस rc;
	वापस 0;
पूर्ण
पूर्णांक pci_alloc_irq_vectors_affinity(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक min_vecs,
				   अचिन्हित पूर्णांक max_vecs, अचिन्हित पूर्णांक flags,
				   काष्ठा irq_affinity *affd);

व्योम pci_मुक्त_irq_vectors(काष्ठा pci_dev *dev);
पूर्णांक pci_irq_vector(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr);
स्थिर काष्ठा cpumask *pci_irq_get_affinity(काष्ठा pci_dev *pdev, पूर्णांक vec);

#अन्यथा
अटल अंतरभूत पूर्णांक pci_msi_vec_count(काष्ठा pci_dev *dev) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम pci_disable_msi(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_msix_vec_count(काष्ठा pci_dev *dev) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम pci_disable_msix(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम pci_restore_msi_state(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_msi_enabled(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_msi(काष्ठा pci_dev *dev)
अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_msix_range(काष्ठा pci_dev *dev,
			काष्ठा msix_entry *entries, पूर्णांक minvec, पूर्णांक maxvec)
अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_msix_exact(काष्ठा pci_dev *dev,
			काष्ठा msix_entry *entries, पूर्णांक nvec)
अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत पूर्णांक
pci_alloc_irq_vectors_affinity(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक min_vecs,
			       अचिन्हित पूर्णांक max_vecs, अचिन्हित पूर्णांक flags,
			       काष्ठा irq_affinity *aff_desc)
अणु
	अगर ((flags & PCI_IRQ_LEGACY) && min_vecs == 1 && dev->irq)
		वापस 1;
	वापस -ENOSPC;
पूर्ण

अटल अंतरभूत व्योम pci_मुक्त_irq_vectors(काष्ठा pci_dev *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pci_irq_vector(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr)
अणु
	अगर (WARN_ON_ONCE(nr > 0))
		वापस -EINVAL;
	वापस dev->irq;
पूर्ण
अटल अंतरभूत स्थिर काष्ठा cpumask *pci_irq_get_affinity(काष्ठा pci_dev *pdev,
		पूर्णांक vec)
अणु
	वापस cpu_possible_mask;
पूर्ण
#पूर्ण_अगर

/**
 * pci_irqd_पूर्णांकx_xlate() - Translate PCI INTx value to an IRQ करोमुख्य hwirq
 * @d: the INTx IRQ करोमुख्य
 * @node: the DT node क्रम the device whose पूर्णांकerrupt we're translating
 * @पूर्णांकspec: the पूर्णांकerrupt specअगरier data from the DT
 * @पूर्णांकsize: the number of entries in @पूर्णांकspec
 * @out_hwirq: poपूर्णांकer at which to ग_लिखो the hwirq number
 * @out_type: poपूर्णांकer at which to ग_लिखो the पूर्णांकerrupt type
 *
 * Translate a PCI INTx पूर्णांकerrupt number from device tree in the range 1-4, as
 * stored in the standard PCI_INTERRUPT_PIN रेजिस्टर, to a value in the range
 * 0-3 suitable क्रम use in a 4 entry IRQ करोमुख्य. That is, subtract one from the
 * INTx value to obtain the hwirq number.
 *
 * Returns 0 on success, or -EINVAL अगर the पूर्णांकerrupt specअगरier is out of range.
 */
अटल अंतरभूत पूर्णांक pci_irqd_पूर्णांकx_xlate(काष्ठा irq_करोमुख्य *d,
				      काष्ठा device_node *node,
				      स्थिर u32 *पूर्णांकspec,
				      अचिन्हित पूर्णांक पूर्णांकsize,
				      अचिन्हित दीर्घ *out_hwirq,
				      अचिन्हित पूर्णांक *out_type)
अणु
	स्थिर u32 पूर्णांकx = पूर्णांकspec[0];

	अगर (पूर्णांकx < PCI_INTERRUPT_INTA || पूर्णांकx > PCI_INTERRUPT_INTD)
		वापस -EINVAL;

	*out_hwirq = पूर्णांकx - PCI_INTERRUPT_INTA;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCIEPORTBUS
बाह्य bool pcie_ports_disabled;
बाह्य bool pcie_ports_native;
#अन्यथा
#घोषणा pcie_ports_disabled	true
#घोषणा pcie_ports_native	false
#पूर्ण_अगर

#घोषणा PCIE_LINK_STATE_L0S		BIT(0)
#घोषणा PCIE_LINK_STATE_L1		BIT(1)
#घोषणा PCIE_LINK_STATE_CLKPM		BIT(2)
#घोषणा PCIE_LINK_STATE_L1_1		BIT(3)
#घोषणा PCIE_LINK_STATE_L1_2		BIT(4)
#घोषणा PCIE_LINK_STATE_L1_1_PCIPM	BIT(5)
#घोषणा PCIE_LINK_STATE_L1_2_PCIPM	BIT(6)

#अगर_घोषित CONFIG_PCIEASPM
पूर्णांक pci_disable_link_state(काष्ठा pci_dev *pdev, पूर्णांक state);
पूर्णांक pci_disable_link_state_locked(काष्ठा pci_dev *pdev, पूर्णांक state);
व्योम pcie_no_aspm(व्योम);
bool pcie_aspm_support_enabled(व्योम);
bool pcie_aspm_enabled(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत पूर्णांक pci_disable_link_state(काष्ठा pci_dev *pdev, पूर्णांक state)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_disable_link_state_locked(काष्ठा pci_dev *pdev, पूर्णांक state)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pcie_no_aspm(व्योम) अणु पूर्ण
अटल अंतरभूत bool pcie_aspm_support_enabled(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool pcie_aspm_enabled(काष्ठा pci_dev *pdev) अणु वापस false; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIEAER
bool pci_aer_available(व्योम);
#अन्यथा
अटल अंतरभूत bool pci_aer_available(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

bool pci_ats_disabled(व्योम);

व्योम pci_cfg_access_lock(काष्ठा pci_dev *dev);
bool pci_cfg_access_trylock(काष्ठा pci_dev *dev);
व्योम pci_cfg_access_unlock(काष्ठा pci_dev *dev);

/*
 * PCI करोमुख्य support.  Someबार called PCI segment (eg by ACPI),
 * a PCI करोमुख्य is defined to be a set of PCI buses which share
 * configuration space.
 */
#अगर_घोषित CONFIG_PCI_DOMAINS
बाह्य पूर्णांक pci_करोमुख्यs_supported;
#अन्यथा
क्रमागत अणु pci_करोमुख्यs_supported = 0 पूर्ण;
अटल अंतरभूत पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_proc_करोमुख्य(काष्ठा pci_bus *bus) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_DOMAINS */

/*
 * Generic implementation क्रम PCI करोमुख्य support. If your
 * architecture करोes not need custom management of PCI
 * करोमुख्यs then this implementation will be used
 */
#अगर_घोषित CONFIG_PCI_DOMAINS_GENERIC
अटल अंतरभूत पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus)
अणु
	वापस bus->करोमुख्य_nr;
पूर्ण
#अगर_घोषित CONFIG_ACPI
पूर्णांक acpi_pci_bus_find_करोमुख्य_nr(काष्ठा pci_bus *bus);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_pci_bus_find_करोमुख्य_nr(काष्ठा pci_bus *bus)
अणु वापस 0; पूर्ण
#पूर्ण_अगर
पूर्णांक pci_bus_find_करोमुख्य_nr(काष्ठा pci_bus *bus, काष्ठा device *parent);
#पूर्ण_अगर

/* Some architectures require additional setup to direct VGA traffic */
प्रकार पूर्णांक (*arch_set_vga_state_t)(काष्ठा pci_dev *pdev, bool decode,
				    अचिन्हित पूर्णांक command_bits, u32 flags);
व्योम pci_रेजिस्टर_set_vga_state(arch_set_vga_state_t func);

अटल अंतरभूत पूर्णांक
pci_request_io_regions(काष्ठा pci_dev *pdev, स्थिर अक्षर *name)
अणु
	वापस pci_request_selected_regions(pdev,
			    pci_select_bars(pdev, IORESOURCE_IO), name);
पूर्ण

अटल अंतरभूत व्योम
pci_release_io_regions(काष्ठा pci_dev *pdev)
अणु
	वापस pci_release_selected_regions(pdev,
			    pci_select_bars(pdev, IORESOURCE_IO));
पूर्ण

अटल अंतरभूत पूर्णांक
pci_request_mem_regions(काष्ठा pci_dev *pdev, स्थिर अक्षर *name)
अणु
	वापस pci_request_selected_regions(pdev,
			    pci_select_bars(pdev, IORESOURCE_MEM), name);
पूर्ण

अटल अंतरभूत व्योम
pci_release_mem_regions(काष्ठा pci_dev *pdev)
अणु
	वापस pci_release_selected_regions(pdev,
			    pci_select_bars(pdev, IORESOURCE_MEM));
पूर्ण

#अन्यथा /* CONFIG_PCI is not enabled */

अटल अंतरभूत व्योम pci_set_flags(पूर्णांक flags) अणु पूर्ण
अटल अंतरभूत व्योम pci_add_flags(पूर्णांक flags) अणु पूर्ण
अटल अंतरभूत व्योम pci_clear_flags(पूर्णांक flags) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_has_flag(पूर्णांक flag) अणु वापस 0; पूर्ण

/*
 * If the प्रणाली करोes not have PCI, clearly these वापस errors.  Define
 * these as simple अंतरभूत functions to aव्योम hair in drivers.
 */
#घोषणा _PCI_NOP(o, s, t) \
	अटल अंतरभूत पूर्णांक pci_##o##_config_##s(काष्ठा pci_dev *dev, \
						पूर्णांक where, t val) \
		अणु वापस PCIBIOS_FUNC_NOT_SUPPORTED; पूर्ण

#घोषणा _PCI_NOP_ALL(o, x)	_PCI_NOP(o, byte, u8 x) \
				_PCI_NOP(o, word, u16 x) \
				_PCI_NOP(o, dword, u32 x)
_PCI_NOP_ALL(पढ़ो, *)
_PCI_NOP_ALL(ग_लिखो,)

अटल अंतरभूत काष्ठा pci_dev *pci_get_device(अचिन्हित पूर्णांक venकरोr,
					     अचिन्हित पूर्णांक device,
					     काष्ठा pci_dev *from)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत काष्ठा pci_dev *pci_get_subsys(अचिन्हित पूर्णांक venकरोr,
					     अचिन्हित पूर्णांक device,
					     अचिन्हित पूर्णांक ss_venकरोr,
					     अचिन्हित पूर्णांक ss_device,
					     काष्ठा pci_dev *from)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत काष्ठा pci_dev *pci_get_class(अचिन्हित पूर्णांक class,
					    काष्ठा pci_dev *from)
अणु वापस शून्य; पूर्ण

#घोषणा pci_dev_present(ids)	(0)
#घोषणा no_pci_devices()	(1)
#घोषणा pci_dev_put(dev)	करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम pci_set_master(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_device(काष्ठा pci_dev *dev) अणु वापस -EIO; पूर्ण
अटल अंतरभूत व्योम pci_disable_device(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pcim_enable_device(काष्ठा pci_dev *pdev) अणु वापस -EIO; पूर्ण
अटल अंतरभूत पूर्णांक pci_assign_resource(काष्ठा pci_dev *dev, पूर्णांक i)
अणु वापस -EBUSY; पूर्ण
अटल अंतरभूत पूर्णांक __pci_रेजिस्टर_driver(काष्ठा pci_driver *drv,
					काष्ठा module *owner)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_रेजिस्टर_driver(काष्ठा pci_driver *drv)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pci_unरेजिस्टर_driver(काष्ठा pci_driver *drv) अणु पूर्ण
अटल अंतरभूत u8 pci_find_capability(काष्ठा pci_dev *dev, पूर्णांक cap)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_find_next_capability(काष्ठा pci_dev *dev, u8 post,
					   पूर्णांक cap)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_find_ext_capability(काष्ठा pci_dev *dev, पूर्णांक cap)
अणु वापस 0; पूर्ण

अटल अंतरभूत u64 pci_get_dsn(काष्ठा pci_dev *dev)
अणु वापस 0; पूर्ण

/* Power management related routines */
अटल अंतरभूत पूर्णांक pci_save_state(काष्ठा pci_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pci_restore_state(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_set_घातer_state(काष्ठा pci_dev *dev, pci_घातer_t state)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_wake_from_d3(काष्ठा pci_dev *dev, bool enable)
अणु वापस 0; पूर्ण
अटल अंतरभूत pci_घातer_t pci_choose_state(काष्ठा pci_dev *dev,
					   pm_message_t state)
अणु वापस PCI_D0; पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_wake(काष्ठा pci_dev *dev, pci_घातer_t state,
				  पूर्णांक enable)
अणु वापस 0; पूर्ण

अटल अंतरभूत काष्ठा resource *pci_find_resource(काष्ठा pci_dev *dev,
						 काष्ठा resource *res)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक pci_request_regions(काष्ठा pci_dev *dev, स्थिर अक्षर *res_name)
अणु वापस -EIO; पूर्ण
अटल अंतरभूत व्योम pci_release_regions(काष्ठा pci_dev *dev) अणु पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pci_address_to_pio(phys_addr_t addr) अणु वापस -1; पूर्ण

अटल अंतरभूत काष्ठा pci_bus *pci_find_next_bus(स्थिर काष्ठा pci_bus *from)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा pci_dev *pci_get_slot(काष्ठा pci_bus *bus,
						अचिन्हित पूर्णांक devfn)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा pci_dev *pci_get_करोमुख्य_bus_and_slot(पूर्णांक करोमुख्य,
					अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn)
अणु वापस शून्य; पूर्ण

अटल अंतरभूत पूर्णांक pci_करोमुख्य_nr(काष्ठा pci_bus *bus) अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा pci_dev *pci_dev_get(काष्ठा pci_dev *dev) अणु वापस शून्य; पूर्ण

#घोषणा dev_is_pci(d) (false)
#घोषणा dev_is_pf(d) (false)
अटल अंतरभूत bool pci_acs_enabled(काष्ठा pci_dev *pdev, u16 acs_flags)
अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक pci_irqd_पूर्णांकx_xlate(काष्ठा irq_करोमुख्य *d,
				      काष्ठा device_node *node,
				      स्थिर u32 *पूर्णांकspec,
				      अचिन्हित पूर्णांक पूर्णांकsize,
				      अचिन्हित दीर्घ *out_hwirq,
				      अचिन्हित पूर्णांक *out_type)
अणु वापस -EINVAL; पूर्ण

अटल अंतरभूत स्थिर काष्ठा pci_device_id *pci_match_id(स्थिर काष्ठा pci_device_id *ids,
							 काष्ठा pci_dev *dev)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत bool pci_ats_disabled(व्योम) अणु वापस true; पूर्ण

अटल अंतरभूत पूर्णांक pci_irq_vector(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक nr)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
pci_alloc_irq_vectors_affinity(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक min_vecs,
			       अचिन्हित पूर्णांक max_vecs, अचिन्हित पूर्णांक flags,
			       काष्ठा irq_affinity *aff_desc)
अणु
	वापस -ENOSPC;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

अटल अंतरभूत पूर्णांक
pci_alloc_irq_vectors(काष्ठा pci_dev *dev, अचिन्हित पूर्णांक min_vecs,
		      अचिन्हित पूर्णांक max_vecs, अचिन्हित पूर्णांक flags)
अणु
	वापस pci_alloc_irq_vectors_affinity(dev, min_vecs, max_vecs, flags,
					      शून्य);
पूर्ण

/* Include architecture-dependent settings and functions */

#समावेश <यंत्र/pci.h>

/* These two functions provide almost identical functionality. Depending
 * on the architecture, one will be implemented as a wrapper around the
 * other (in drivers/pci/mmap.c).
 *
 * pci_mmap_resource_range() maps a specअगरic BAR, and vm->vm_pgoff
 * is expected to be an offset within that region.
 *
 * pci_mmap_page_range() is the legacy architecture-specअगरic पूर्णांकerface,
 * which accepts a "user visible" resource address converted by
 * pci_resource_to_user(), as used in the legacy mmap() पूर्णांकerface in
 * /proc/bus/pci/.
 */
पूर्णांक pci_mmap_resource_range(काष्ठा pci_dev *dev, पूर्णांक bar,
			    काष्ठा vm_area_काष्ठा *vma,
			    क्रमागत pci_mmap_state mmap_state, पूर्णांक ग_लिखो_combine);
पूर्णांक pci_mmap_page_range(काष्ठा pci_dev *pdev, पूर्णांक bar,
			काष्ठा vm_area_काष्ठा *vma,
			क्रमागत pci_mmap_state mmap_state, पूर्णांक ग_लिखो_combine);

#अगर_अघोषित arch_can_pci_mmap_wc
#घोषणा arch_can_pci_mmap_wc()		0
#पूर्ण_अगर

#अगर_अघोषित arch_can_pci_mmap_io
#घोषणा arch_can_pci_mmap_io()		0
#घोषणा pci_iobar_pfn(pdev, bar, vma) (-EINVAL)
#अन्यथा
पूर्णांक pci_iobar_pfn(काष्ठा pci_dev *pdev, पूर्णांक bar, काष्ठा vm_area_काष्ठा *vma);
#पूर्ण_अगर

#अगर_अघोषित pci_root_bus_fwnode
#घोषणा pci_root_bus_fwnode(bus)	शून्य
#पूर्ण_अगर

/*
 * These helpers provide future and backwards compatibility
 * क्रम accessing popular PCI BAR info
 */
#घोषणा pci_resource_start(dev, bar)	((dev)->resource[(bar)].start)
#घोषणा pci_resource_end(dev, bar)	((dev)->resource[(bar)].end)
#घोषणा pci_resource_flags(dev, bar)	((dev)->resource[(bar)].flags)
#घोषणा pci_resource_len(dev,bar) \
	((pci_resource_start((dev), (bar)) == 0 &&	\
	  pci_resource_end((dev), (bar)) ==		\
	  pci_resource_start((dev), (bar))) ? 0 :	\
							\
	 (pci_resource_end((dev), (bar)) -		\
	  pci_resource_start((dev), (bar)) + 1))

/*
 * Similar to the helpers above, these manipulate per-pci_dev
 * driver-specअगरic data.  They are really just a wrapper around
 * the generic device काष्ठाure functions of these calls.
 */
अटल अंतरभूत व्योम *pci_get_drvdata(काष्ठा pci_dev *pdev)
अणु
	वापस dev_get_drvdata(&pdev->dev);
पूर्ण

अटल अंतरभूत व्योम pci_set_drvdata(काष्ठा pci_dev *pdev, व्योम *data)
अणु
	dev_set_drvdata(&pdev->dev, data);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *pci_name(स्थिर काष्ठा pci_dev *pdev)
अणु
	वापस dev_name(&pdev->dev);
पूर्ण

व्योम pci_resource_to_user(स्थिर काष्ठा pci_dev *dev, पूर्णांक bar,
			  स्थिर काष्ठा resource *rsrc,
			  resource_माप_प्रकार *start, resource_माप_प्रकार *end);

/*
 * The world is not perfect and supplies us with broken PCI devices.
 * For at least a part of these bugs we need a work-around, so both
 * generic (drivers/pci/quirks.c) and per-architecture code can define
 * fixup hooks to be called क्रम particular buggy devices.
 */

काष्ठा pci_fixup अणु
	u16 venकरोr;			/* Or PCI_ANY_ID */
	u16 device;			/* Or PCI_ANY_ID */
	u32 class;			/* Or PCI_ANY_ID */
	अचिन्हित पूर्णांक class_shअगरt;	/* should be 0, 8, 16 */
#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
	पूर्णांक hook_offset;
#अन्यथा
	व्योम (*hook)(काष्ठा pci_dev *dev);
#पूर्ण_अगर
पूर्ण;

क्रमागत pci_fixup_pass अणु
	pci_fixup_early,	/* Beक्रमe probing BARs */
	pci_fixup_header,	/* After पढ़ोing configuration header */
	pci_fixup_final,	/* Final phase of device fixups */
	pci_fixup_enable,	/* pci_enable_device() समय */
	pci_fixup_resume,	/* pci_device_resume() */
	pci_fixup_suspend,	/* pci_device_suspend() */
	pci_fixup_resume_early, /* pci_device_resume_early() */
	pci_fixup_suspend_late,	/* pci_device_suspend_late() */
पूर्ण;

#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
#घोषणा ___DECLARE_PCI_FIXUP_SECTION(sec, name, venकरोr, device, class,	\
				    class_shअगरt, hook)			\
	__ADDRESSABLE(hook)						\
	यंत्र(".section "	#sec ", \"a\"				\n"	\
	    ".balign	16					\n"	\
	    ".short "	#venकरोr ", " #device "			\n"	\
	    ".long "	#class ", " #class_shअगरt "		\n"	\
	    ".long "	#hook " - .				\n"	\
	    ".previous						\n");

/*
 * Clang's LTO may नाम अटल functions in C, but has no way to
 * handle such renamings when referenced from अंतरभूत यंत्र. To work
 * around this, create global C stubs क्रम these हालs.
 */
#अगर_घोषित CONFIG_LTO_CLANG
#घोषणा __DECLARE_PCI_FIXUP_SECTION(sec, name, venकरोr, device, class,	\
				  class_shअगरt, hook, stub)		\
	व्योम __cficanonical stub(काष्ठा pci_dev *dev);			\
	व्योम __cficanonical stub(काष्ठा pci_dev *dev)			\
	अणु 								\
		hook(dev); 						\
	पूर्ण								\
	___DECLARE_PCI_FIXUP_SECTION(sec, name, venकरोr, device, class,	\
				  class_shअगरt, stub)
#अन्यथा
#घोषणा __DECLARE_PCI_FIXUP_SECTION(sec, name, venकरोr, device, class,	\
				  class_shअगरt, hook, stub)		\
	___DECLARE_PCI_FIXUP_SECTION(sec, name, venकरोr, device, class,	\
				  class_shअगरt, hook)
#पूर्ण_अगर

#घोषणा DECLARE_PCI_FIXUP_SECTION(sec, name, venकरोr, device, class,	\
				  class_shअगरt, hook)			\
	__DECLARE_PCI_FIXUP_SECTION(sec, name, venकरोr, device, class,	\
				  class_shअगरt, hook, __UNIQUE_ID(hook))
#अन्यथा
/* Anonymous variables would be nice... */
#घोषणा DECLARE_PCI_FIXUP_SECTION(section, name, venकरोr, device, class,	\
				  class_shअगरt, hook)			\
	अटल स्थिर काष्ठा pci_fixup __PASTE(__pci_fixup_##name,__LINE__) __used	\
	__attribute__((__section__(#section), aligned((माप(व्योम *)))))    \
		= अणु venकरोr, device, class, class_shअगरt, hook पूर्ण;
#पूर्ण_अगर

#घोषणा DECLARE_PCI_FIXUP_CLASS_EARLY(venकरोr, device, class,		\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_early,			\
		hook, venकरोr, device, class, class_shअगरt, hook)
#घोषणा DECLARE_PCI_FIXUP_CLASS_HEADER(venकरोr, device, class,		\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_header,			\
		hook, venकरोr, device, class, class_shअगरt, hook)
#घोषणा DECLARE_PCI_FIXUP_CLASS_FINAL(venकरोr, device, class,		\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_final,			\
		hook, venकरोr, device, class, class_shअगरt, hook)
#घोषणा DECLARE_PCI_FIXUP_CLASS_ENABLE(venकरोr, device, class,		\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_enable,			\
		hook, venकरोr, device, class, class_shअगरt, hook)
#घोषणा DECLARE_PCI_FIXUP_CLASS_RESUME(venकरोr, device, class,		\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_resume,			\
		resume##hook, venकरोr, device, class, class_shअगरt, hook)
#घोषणा DECLARE_PCI_FIXUP_CLASS_RESUME_EARLY(venकरोr, device, class,	\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_resume_early,		\
		resume_early##hook, venकरोr, device, class, class_shअगरt, hook)
#घोषणा DECLARE_PCI_FIXUP_CLASS_SUSPEND(venकरोr, device, class,		\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_suspend,			\
		suspend##hook, venकरोr, device, class, class_shअगरt, hook)
#घोषणा DECLARE_PCI_FIXUP_CLASS_SUSPEND_LATE(venकरोr, device, class,	\
					 class_shअगरt, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_suspend_late,		\
		suspend_late##hook, venकरोr, device, class, class_shअगरt, hook)

#घोषणा DECLARE_PCI_FIXUP_EARLY(venकरोr, device, hook)			\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_early,			\
		hook, venकरोr, device, PCI_ANY_ID, 0, hook)
#घोषणा DECLARE_PCI_FIXUP_HEADER(venकरोr, device, hook)			\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_header,			\
		hook, venकरोr, device, PCI_ANY_ID, 0, hook)
#घोषणा DECLARE_PCI_FIXUP_FINAL(venकरोr, device, hook)			\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_final,			\
		hook, venकरोr, device, PCI_ANY_ID, 0, hook)
#घोषणा DECLARE_PCI_FIXUP_ENABLE(venकरोr, device, hook)			\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_enable,			\
		hook, venकरोr, device, PCI_ANY_ID, 0, hook)
#घोषणा DECLARE_PCI_FIXUP_RESUME(venकरोr, device, hook)			\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_resume,			\
		resume##hook, venकरोr, device, PCI_ANY_ID, 0, hook)
#घोषणा DECLARE_PCI_FIXUP_RESUME_EARLY(venकरोr, device, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_resume_early,		\
		resume_early##hook, venकरोr, device, PCI_ANY_ID, 0, hook)
#घोषणा DECLARE_PCI_FIXUP_SUSPEND(venकरोr, device, hook)			\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_suspend,			\
		suspend##hook, venकरोr, device, PCI_ANY_ID, 0, hook)
#घोषणा DECLARE_PCI_FIXUP_SUSPEND_LATE(venकरोr, device, hook)		\
	DECLARE_PCI_FIXUP_SECTION(.pci_fixup_suspend_late,		\
		suspend_late##hook, venकरोr, device, PCI_ANY_ID, 0, hook)

#अगर_घोषित CONFIG_PCI_QUIRKS
व्योम pci_fixup_device(क्रमागत pci_fixup_pass pass, काष्ठा pci_dev *dev);
#अन्यथा
अटल अंतरभूत व्योम pci_fixup_device(क्रमागत pci_fixup_pass pass,
				    काष्ठा pci_dev *dev) अणु पूर्ण
#पूर्ण_अगर

व्योम __iomem *pcim_iomap(काष्ठा pci_dev *pdev, पूर्णांक bar, अचिन्हित दीर्घ maxlen);
व्योम pcim_iounmap(काष्ठा pci_dev *pdev, व्योम __iomem *addr);
व्योम __iomem * स्थिर *pcim_iomap_table(काष्ठा pci_dev *pdev);
पूर्णांक pcim_iomap_regions(काष्ठा pci_dev *pdev, पूर्णांक mask, स्थिर अक्षर *name);
पूर्णांक pcim_iomap_regions_request_all(काष्ठा pci_dev *pdev, पूर्णांक mask,
				   स्थिर अक्षर *name);
व्योम pcim_iounmap_regions(काष्ठा pci_dev *pdev, पूर्णांक mask);

बाह्य पूर्णांक pci_pci_problems;
#घोषणा PCIPCI_FAIL		1	/* No PCI PCI DMA */
#घोषणा PCIPCI_TRITON		2
#घोषणा PCIPCI_NATOMA		4
#घोषणा PCIPCI_VIAETBF		8
#घोषणा PCIPCI_VSFX		16
#घोषणा PCIPCI_ALIMAGIK		32	/* Need low latency setting */
#घोषणा PCIAGP_FAIL		64	/* No PCI to AGP DMA */

बाह्य अचिन्हित दीर्घ pci_cardbus_io_size;
बाह्य अचिन्हित दीर्घ pci_cardbus_mem_size;
बाह्य u8 pci_dfl_cache_line_size;
बाह्य u8 pci_cache_line_size;

/* Architecture-specअगरic versions may override these (weak) */
व्योम pcibios_disable_device(काष्ठा pci_dev *dev);
व्योम pcibios_set_master(काष्ठा pci_dev *dev);
पूर्णांक pcibios_set_pcie_reset_state(काष्ठा pci_dev *dev,
				 क्रमागत pcie_reset_state state);
पूर्णांक pcibios_add_device(काष्ठा pci_dev *dev);
व्योम pcibios_release_device(काष्ठा pci_dev *dev);
#अगर_घोषित CONFIG_PCI
व्योम pcibios_penalize_isa_irq(पूर्णांक irq, पूर्णांक active);
#अन्यथा
अटल अंतरभूत व्योम pcibios_penalize_isa_irq(पूर्णांक irq, पूर्णांक active) अणुपूर्ण
#पूर्ण_अगर
पूर्णांक pcibios_alloc_irq(काष्ठा pci_dev *dev);
व्योम pcibios_मुक्त_irq(काष्ठा pci_dev *dev);
resource_माप_प्रकार pcibios_शेष_alignment(व्योम);

#अगर defined(CONFIG_PCI_MMCONFIG) || defined(CONFIG_ACPI_MCFG)
व्योम __init pci_mmcfg_early_init(व्योम);
व्योम __init pci_mmcfg_late_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pci_mmcfg_early_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम pci_mmcfg_late_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक pci_ext_cfg_avail(व्योम);

व्योम __iomem *pci_ioremap_bar(काष्ठा pci_dev *pdev, पूर्णांक bar);
व्योम __iomem *pci_ioremap_wc_bar(काष्ठा pci_dev *pdev, पूर्णांक bar);

#अगर_घोषित CONFIG_PCI_IOV
पूर्णांक pci_iov_virtfn_bus(काष्ठा pci_dev *dev, पूर्णांक id);
पूर्णांक pci_iov_virtfn_devfn(काष्ठा pci_dev *dev, पूर्णांक id);

पूर्णांक pci_enable_sriov(काष्ठा pci_dev *dev, पूर्णांक nr_virtfn);
व्योम pci_disable_sriov(काष्ठा pci_dev *dev);

पूर्णांक pci_iov_sysfs_link(काष्ठा pci_dev *dev, काष्ठा pci_dev *virtfn, पूर्णांक id);
पूर्णांक pci_iov_add_virtfn(काष्ठा pci_dev *dev, पूर्णांक id);
व्योम pci_iov_हटाओ_virtfn(काष्ठा pci_dev *dev, पूर्णांक id);
पूर्णांक pci_num_vf(काष्ठा pci_dev *dev);
पूर्णांक pci_vfs_asचिन्हित(काष्ठा pci_dev *dev);
पूर्णांक pci_sriov_set_totalvfs(काष्ठा pci_dev *dev, u16 numvfs);
पूर्णांक pci_sriov_get_totalvfs(काष्ठा pci_dev *dev);
पूर्णांक pci_sriov_configure_simple(काष्ठा pci_dev *dev, पूर्णांक nr_virtfn);
resource_माप_प्रकार pci_iov_resource_size(काष्ठा pci_dev *dev, पूर्णांक resno);
व्योम pci_vf_drivers_स्वतःprobe(काष्ठा pci_dev *dev, bool probe);

/* Arch may override these (weak) */
पूर्णांक pcibios_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs);
पूर्णांक pcibios_sriov_disable(काष्ठा pci_dev *pdev);
resource_माप_प्रकार pcibios_iov_resource_alignment(काष्ठा pci_dev *dev, पूर्णांक resno);
#अन्यथा
अटल अंतरभूत पूर्णांक pci_iov_virtfn_bus(काष्ठा pci_dev *dev, पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pci_iov_virtfn_devfn(काष्ठा pci_dev *dev, पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pci_enable_sriov(काष्ठा pci_dev *dev, पूर्णांक nr_virtfn)
अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक pci_iov_sysfs_link(काष्ठा pci_dev *dev,
				     काष्ठा pci_dev *virtfn, पूर्णांक id)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक pci_iov_add_virtfn(काष्ठा pci_dev *dev, पूर्णांक id)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम pci_iov_हटाओ_virtfn(काष्ठा pci_dev *dev,
					 पूर्णांक id) अणु पूर्ण
अटल अंतरभूत व्योम pci_disable_sriov(काष्ठा pci_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pci_num_vf(काष्ठा pci_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_vfs_asचिन्हित(काष्ठा pci_dev *dev)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_sriov_set_totalvfs(काष्ठा pci_dev *dev, u16 numvfs)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pci_sriov_get_totalvfs(काष्ठा pci_dev *dev)
अणु वापस 0; पूर्ण
#घोषणा pci_sriov_configure_simple	शून्य
अटल अंतरभूत resource_माप_प्रकार pci_iov_resource_size(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pci_vf_drivers_स्वतःprobe(काष्ठा pci_dev *dev, bool probe) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_HOTPLUG_PCI) || defined(CONFIG_HOTPLUG_PCI_MODULE)
व्योम pci_hp_create_module_link(काष्ठा pci_slot *pci_slot);
व्योम pci_hp_हटाओ_module_link(काष्ठा pci_slot *pci_slot);
#पूर्ण_अगर

/**
 * pci_pcie_cap - get the saved PCIe capability offset
 * @dev: PCI device
 *
 * PCIe capability offset is calculated at PCI device initialization
 * समय and saved in the data काष्ठाure. This function वापसs saved
 * PCIe capability offset. Using this instead of pci_find_capability()
 * reduces unnecessary search in the PCI configuration space. If you
 * need to calculate PCIe capability offset from raw device क्रम some
 * reasons, please use pci_find_capability() instead.
 */
अटल अंतरभूत पूर्णांक pci_pcie_cap(काष्ठा pci_dev *dev)
अणु
	वापस dev->pcie_cap;
पूर्ण

/**
 * pci_is_pcie - check अगर the PCI device is PCI Express capable
 * @dev: PCI device
 *
 * Returns: true अगर the PCI device is PCI Express capable, false otherwise.
 */
अटल अंतरभूत bool pci_is_pcie(काष्ठा pci_dev *dev)
अणु
	वापस pci_pcie_cap(dev);
पूर्ण

/**
 * pcie_caps_reg - get the PCIe Capabilities Register
 * @dev: PCI device
 */
अटल अंतरभूत u16 pcie_caps_reg(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस dev->pcie_flags_reg;
पूर्ण

/**
 * pci_pcie_type - get the PCIe device/port type
 * @dev: PCI device
 */
अटल अंतरभूत पूर्णांक pci_pcie_type(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस (pcie_caps_reg(dev) & PCI_EXP_FLAGS_TYPE) >> 4;
पूर्ण

/**
 * pcie_find_root_port - Get the PCIe root port device
 * @dev: PCI device
 *
 * Traverse up the parent chain and वापस the PCIe Root Port PCI Device
 * क्रम a given PCI/PCIe Device.
 */
अटल अंतरभूत काष्ठा pci_dev *pcie_find_root_port(काष्ठा pci_dev *dev)
अणु
	जबतक (dev) अणु
		अगर (pci_is_pcie(dev) &&
		    pci_pcie_type(dev) == PCI_EXP_TYPE_ROOT_PORT)
			वापस dev;
		dev = pci_upstream_bridge(dev);
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम pci_request_acs(व्योम);
bool pci_acs_enabled(काष्ठा pci_dev *pdev, u16 acs_flags);
bool pci_acs_path_enabled(काष्ठा pci_dev *start,
			  काष्ठा pci_dev *end, u16 acs_flags);
पूर्णांक pci_enable_atomic_ops_to_root(काष्ठा pci_dev *dev, u32 cap_mask);

#घोषणा PCI_VPD_LRDT			0x80	/* Large Resource Data Type */
#घोषणा PCI_VPD_LRDT_ID(x)		((x) | PCI_VPD_LRDT)

/* Large Resource Data Type Tag Item Names */
#घोषणा PCI_VPD_LTIN_ID_STRING		0x02	/* Identअगरier String */
#घोषणा PCI_VPD_LTIN_RO_DATA		0x10	/* Read-Only Data */
#घोषणा PCI_VPD_LTIN_RW_DATA		0x11	/* Read-Write Data */

#घोषणा PCI_VPD_LRDT_ID_STRING		PCI_VPD_LRDT_ID(PCI_VPD_LTIN_ID_STRING)
#घोषणा PCI_VPD_LRDT_RO_DATA		PCI_VPD_LRDT_ID(PCI_VPD_LTIN_RO_DATA)
#घोषणा PCI_VPD_LRDT_RW_DATA		PCI_VPD_LRDT_ID(PCI_VPD_LTIN_RW_DATA)

/* Small Resource Data Type Tag Item Names */
#घोषणा PCI_VPD_STIN_END		0x0f	/* End */

#घोषणा PCI_VPD_SRDT_END		(PCI_VPD_STIN_END << 3)

#घोषणा PCI_VPD_SRDT_TIN_MASK		0x78
#घोषणा PCI_VPD_SRDT_LEN_MASK		0x07
#घोषणा PCI_VPD_LRDT_TIN_MASK		0x7f

#घोषणा PCI_VPD_LRDT_TAG_SIZE		3
#घोषणा PCI_VPD_SRDT_TAG_SIZE		1

#घोषणा PCI_VPD_INFO_FLD_HDR_SIZE	3

#घोषणा PCI_VPD_RO_KEYWORD_PARTNO	"PN"
#घोषणा PCI_VPD_RO_KEYWORD_SERIALNO	"SN"
#घोषणा PCI_VPD_RO_KEYWORD_MFR_ID	"MN"
#घोषणा PCI_VPD_RO_KEYWORD_VENDOR0	"V0"
#घोषणा PCI_VPD_RO_KEYWORD_CHKSUM	"RV"

/**
 * pci_vpd_lrdt_size - Extracts the Large Resource Data Type length
 * @lrdt: Poपूर्णांकer to the beginning of the Large Resource Data Type tag
 *
 * Returns the extracted Large Resource Data Type length.
 */
अटल अंतरभूत u16 pci_vpd_lrdt_size(स्थिर u8 *lrdt)
अणु
	वापस (u16)lrdt[1] + ((u16)lrdt[2] << 8);
पूर्ण

/**
 * pci_vpd_lrdt_tag - Extracts the Large Resource Data Type Tag Item
 * @lrdt: Poपूर्णांकer to the beginning of the Large Resource Data Type tag
 *
 * Returns the extracted Large Resource Data Type Tag item.
 */
अटल अंतरभूत u16 pci_vpd_lrdt_tag(स्थिर u8 *lrdt)
अणु
	वापस (u16)(lrdt[0] & PCI_VPD_LRDT_TIN_MASK);
पूर्ण

/**
 * pci_vpd_srdt_size - Extracts the Small Resource Data Type length
 * @srdt: Poपूर्णांकer to the beginning of the Small Resource Data Type tag
 *
 * Returns the extracted Small Resource Data Type length.
 */
अटल अंतरभूत u8 pci_vpd_srdt_size(स्थिर u8 *srdt)
अणु
	वापस (*srdt) & PCI_VPD_SRDT_LEN_MASK;
पूर्ण

/**
 * pci_vpd_srdt_tag - Extracts the Small Resource Data Type Tag Item
 * @srdt: Poपूर्णांकer to the beginning of the Small Resource Data Type tag
 *
 * Returns the extracted Small Resource Data Type Tag Item.
 */
अटल अंतरभूत u8 pci_vpd_srdt_tag(स्थिर u8 *srdt)
अणु
	वापस ((*srdt) & PCI_VPD_SRDT_TIN_MASK) >> 3;
पूर्ण

/**
 * pci_vpd_info_field_size - Extracts the inक्रमmation field length
 * @info_field: Poपूर्णांकer to the beginning of an inक्रमmation field header
 *
 * Returns the extracted inक्रमmation field length.
 */
अटल अंतरभूत u8 pci_vpd_info_field_size(स्थिर u8 *info_field)
अणु
	वापस info_field[2];
पूर्ण

/**
 * pci_vpd_find_tag - Locates the Resource Data Type tag provided
 * @buf: Poपूर्णांकer to buffered vpd data
 * @len: The length of the vpd buffer
 * @rdt: The Resource Data Type to search क्रम
 *
 * Returns the index where the Resource Data Type was found or
 * -ENOENT otherwise.
 */
पूर्णांक pci_vpd_find_tag(स्थिर u8 *buf, अचिन्हित पूर्णांक len, u8 rdt);

/**
 * pci_vpd_find_info_keyword - Locates an inक्रमmation field keyword in the VPD
 * @buf: Poपूर्णांकer to buffered vpd data
 * @off: The offset पूर्णांकo the buffer at which to begin the search
 * @len: The length of the buffer area, relative to off, in which to search
 * @kw: The keyword to search क्रम
 *
 * Returns the index where the inक्रमmation field keyword was found or
 * -ENOENT otherwise.
 */
पूर्णांक pci_vpd_find_info_keyword(स्थिर u8 *buf, अचिन्हित पूर्णांक off,
			      अचिन्हित पूर्णांक len, स्थिर अक्षर *kw);

/* PCI <-> OF binding helpers */
#अगर_घोषित CONFIG_OF
काष्ठा device_node;
काष्ठा irq_करोमुख्य;
काष्ठा irq_करोमुख्य *pci_host_bridge_of_msi_करोमुख्य(काष्ठा pci_bus *bus);
bool pci_host_of_has_msi_map(काष्ठा device *dev);

/* Arch may override this (weak) */
काष्ठा device_node *pcibios_get_phb_of_node(काष्ठा pci_bus *bus);

#अन्यथा	/* CONFIG_OF */
अटल अंतरभूत काष्ठा irq_करोमुख्य *
pci_host_bridge_of_msi_करोमुख्य(काष्ठा pci_bus *bus) अणु वापस शून्य; पूर्ण
अटल अंतरभूत bool pci_host_of_has_msi_map(काष्ठा device *dev) अणु वापस false; पूर्ण
#पूर्ण_अगर  /* CONFIG_OF */

अटल अंतरभूत काष्ठा device_node *
pci_device_to_OF_node(स्थिर काष्ठा pci_dev *pdev)
अणु
	वापस pdev ? pdev->dev.of_node : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device_node *pci_bus_to_OF_node(काष्ठा pci_bus *bus)
अणु
	वापस bus ? bus->dev.of_node : शून्य;
पूर्ण

#अगर_घोषित CONFIG_ACPI
काष्ठा irq_करोमुख्य *pci_host_bridge_acpi_msi_करोमुख्य(काष्ठा pci_bus *bus);

व्योम
pci_msi_रेजिस्टर_fwnode_provider(काष्ठा fwnode_handle *(*fn)(काष्ठा device *));
bool pci_pr3_present(काष्ठा pci_dev *pdev);
#अन्यथा
अटल अंतरभूत काष्ठा irq_करोमुख्य *
pci_host_bridge_acpi_msi_करोमुख्य(काष्ठा pci_bus *bus) अणु वापस शून्य; पूर्ण
अटल अंतरभूत bool pci_pr3_present(काष्ठा pci_dev *pdev) अणु वापस false; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_EEH
अटल अंतरभूत काष्ठा eeh_dev *pci_dev_to_eeh_dev(काष्ठा pci_dev *pdev)
अणु
	वापस pdev->dev.archdata.edev;
पूर्ण
#पूर्ण_अगर

व्योम pci_add_dma_alias(काष्ठा pci_dev *dev, u8 devfn_from, अचिन्हित nr_devfns);
bool pci_devs_are_dma_aliases(काष्ठा pci_dev *dev1, काष्ठा pci_dev *dev2);
पूर्णांक pci_क्रम_each_dma_alias(काष्ठा pci_dev *pdev,
			   पूर्णांक (*fn)(काष्ठा pci_dev *pdev,
				     u16 alias, व्योम *data), व्योम *data);

/* Helper functions क्रम operation of device flag */
अटल अंतरभूत व्योम pci_set_dev_asचिन्हित(काष्ठा pci_dev *pdev)
अणु
	pdev->dev_flags |= PCI_DEV_FLAGS_ASSIGNED;
पूर्ण
अटल अंतरभूत व्योम pci_clear_dev_asचिन्हित(काष्ठा pci_dev *pdev)
अणु
	pdev->dev_flags &= ~PCI_DEV_FLAGS_ASSIGNED;
पूर्ण
अटल अंतरभूत bool pci_is_dev_asचिन्हित(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->dev_flags & PCI_DEV_FLAGS_ASSIGNED) == PCI_DEV_FLAGS_ASSIGNED;
पूर्ण

/**
 * pci_ari_enabled - query ARI क्रमwarding status
 * @bus: the PCI bus
 *
 * Returns true अगर ARI क्रमwarding is enabled.
 */
अटल अंतरभूत bool pci_ari_enabled(काष्ठा pci_bus *bus)
अणु
	वापस bus->self && bus->self->ari_enabled;
पूर्ण

/**
 * pci_is_thunderbolt_attached - whether device is on a Thunderbolt daisy chain
 * @pdev: PCI device to check
 *
 * Walk upwards from @pdev and check क्रम each encountered bridge अगर it's part
 * of a Thunderbolt controller.  Reaching the host bridge means @pdev is not
 * Thunderbolt-attached.  (But rather soldered to the मुख्यboard usually.)
 */
अटल अंतरभूत bool pci_is_thunderbolt_attached(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *parent = pdev;

	अगर (pdev->is_thunderbolt)
		वापस true;

	जबतक ((parent = pci_upstream_bridge(parent)))
		अगर (parent->is_thunderbolt)
			वापस true;

	वापस false;
पूर्ण

#अगर defined(CONFIG_PCIEPORTBUS) || defined(CONFIG_EEH)
व्योम pci_uevent_ers(काष्ठा pci_dev *pdev, क्रमागत  pci_ers_result err_type);
#पूर्ण_अगर

/* Provide the legacy pci_dma_* API */
#समावेश <linux/pci-dma-compat.h>

#घोषणा pci_prपूर्णांकk(level, pdev, fmt, arg...) \
	dev_prपूर्णांकk(level, &(pdev)->dev, fmt, ##arg)

#घोषणा pci_emerg(pdev, fmt, arg...)	dev_emerg(&(pdev)->dev, fmt, ##arg)
#घोषणा pci_alert(pdev, fmt, arg...)	dev_alert(&(pdev)->dev, fmt, ##arg)
#घोषणा pci_crit(pdev, fmt, arg...)	dev_crit(&(pdev)->dev, fmt, ##arg)
#घोषणा pci_err(pdev, fmt, arg...)	dev_err(&(pdev)->dev, fmt, ##arg)
#घोषणा pci_warn(pdev, fmt, arg...)	dev_warn(&(pdev)->dev, fmt, ##arg)
#घोषणा pci_notice(pdev, fmt, arg...)	dev_notice(&(pdev)->dev, fmt, ##arg)
#घोषणा pci_info(pdev, fmt, arg...)	dev_info(&(pdev)->dev, fmt, ##arg)
#घोषणा pci_dbg(pdev, fmt, arg...)	dev_dbg(&(pdev)->dev, fmt, ##arg)

#घोषणा pci_notice_ratelimited(pdev, fmt, arg...) \
	dev_notice_ratelimited(&(pdev)->dev, fmt, ##arg)

#घोषणा pci_info_ratelimited(pdev, fmt, arg...) \
	dev_info_ratelimited(&(pdev)->dev, fmt, ##arg)

#घोषणा pci_WARN(pdev, condition, fmt, arg...) \
	WARN(condition, "%s %s: " fmt, \
	     dev_driver_string(&(pdev)->dev), pci_name(pdev), ##arg)

#घोषणा pci_WARN_ONCE(pdev, condition, fmt, arg...) \
	WARN_ONCE(condition, "%s %s: " fmt, \
		  dev_driver_string(&(pdev)->dev), pci_name(pdev), ##arg)

#पूर्ण_अगर /* LINUX_PCI_H */
