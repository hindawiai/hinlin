<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) Microsoft Corporation.
 *
 * Author:
 *   Jake Oshins <jakeo@microsoft.com>
 *
 * This driver acts as a paraभव front-end क्रम PCI Express root buses.
 * When a PCI Express function (either an entire device or an SR-IOV
 * Virtual Function) is being passed through to the VM, this driver exposes
 * a new bus to the guest VM.  This is modeled as a root PCI bus because
 * no bridges are being exposed to the VM.  In fact, with a "Generation 2"
 * VM within Hyper-V, there may seem to be no PCI bus at all in the VM
 * until a device as been exposed using this driver.
 *
 * Each root PCI bus has its own PCI करोमुख्य, which is called "Segment" in
 * the PCI Firmware Specअगरications.  Thus जबतक each device passed through
 * to the VM using this front-end will appear at "device 0", the करोमुख्य will
 * be unique.  Typically, each bus will have one PCI function on it, though
 * this driver करोes support more than one.
 *
 * In order to map the पूर्णांकerrupts from the device through to the guest VM,
 * this driver also implements an IRQ Doमुख्य, which handles पूर्णांकerrupts (either
 * MSI or MSI-X) associated with the functions on the bus.  As पूर्णांकerrupts are
 * set up, torn करोwn, or reaffined, this driver communicates with the
 * underlying hypervisor to adjust the mappings in the I/O MMU so that each
 * पूर्णांकerrupt will be delivered to the correct भव processor at the right
 * vector.  This driver करोes not support level-triggered (line-based)
 * पूर्णांकerrupts, and will report that the Interrupt Line रेजिस्टर in the
 * function's configuration space is zero.
 *
 * The rest of this driver mostly maps PCI concepts onto underlying Hyper-V
 * facilities.  For instance, the configuration space of a function exposed
 * by Hyper-V is mapped पूर्णांकo a single page of memory space, and the
 * पढ़ो and ग_लिखो handlers क्रम config space must be aware of this mechanism.
 * Similarly, device setup and tearकरोwn involves messages sent to and from
 * the PCI back-end driver in Hyper-V.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/apic.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/refcount.h>
#समावेश <यंत्र/mshyperv.h>

/*
 * Protocol versions. The low word is the minor version, the high word the
 * major version.
 */

#घोषणा PCI_MAKE_VERSION(major, minor) ((u32)(((major) << 16) | (minor)))
#घोषणा PCI_MAJOR_VERSION(version) ((u32)(version) >> 16)
#घोषणा PCI_MINOR_VERSION(version) ((u32)(version) & 0xff)

क्रमागत pci_protocol_version_t अणु
	PCI_PROTOCOL_VERSION_1_1 = PCI_MAKE_VERSION(1, 1),	/* Win10 */
	PCI_PROTOCOL_VERSION_1_2 = PCI_MAKE_VERSION(1, 2),	/* RS1 */
	PCI_PROTOCOL_VERSION_1_3 = PCI_MAKE_VERSION(1, 3),	/* Vibranium */
पूर्ण;

#घोषणा CPU_AFFINITY_ALL	-1ULL

/*
 * Supported protocol versions in the order of probing - highest go
 * first.
 */
अटल क्रमागत pci_protocol_version_t pci_protocol_versions[] = अणु
	PCI_PROTOCOL_VERSION_1_3,
	PCI_PROTOCOL_VERSION_1_2,
	PCI_PROTOCOL_VERSION_1_1,
पूर्ण;

#घोषणा PCI_CONFIG_MMIO_LENGTH	0x2000
#घोषणा CFG_PAGE_OFFSET 0x1000
#घोषणा CFG_PAGE_SIZE (PCI_CONFIG_MMIO_LENGTH - CFG_PAGE_OFFSET)

#घोषणा MAX_SUPPORTED_MSI_MESSAGES 0x400

#घोषणा STATUS_REVISION_MISMATCH 0xC0000059

/* space क्रम 32bit serial number as string */
#घोषणा SLOT_NAME_SIZE 11

/*
 * Message Types
 */

क्रमागत pci_message_type अणु
	/*
	 * Version 1.1
	 */
	PCI_MESSAGE_BASE                = 0x42490000,
	PCI_BUS_RELATIONS               = PCI_MESSAGE_BASE + 0,
	PCI_QUERY_BUS_RELATIONS         = PCI_MESSAGE_BASE + 1,
	PCI_POWER_STATE_CHANGE          = PCI_MESSAGE_BASE + 4,
	PCI_QUERY_RESOURCE_REQUIREMENTS = PCI_MESSAGE_BASE + 5,
	PCI_QUERY_RESOURCE_RESOURCES    = PCI_MESSAGE_BASE + 6,
	PCI_BUS_D0ENTRY                 = PCI_MESSAGE_BASE + 7,
	PCI_BUS_D0EXIT                  = PCI_MESSAGE_BASE + 8,
	PCI_READ_BLOCK                  = PCI_MESSAGE_BASE + 9,
	PCI_WRITE_BLOCK                 = PCI_MESSAGE_BASE + 0xA,
	PCI_EJECT                       = PCI_MESSAGE_BASE + 0xB,
	PCI_QUERY_STOP                  = PCI_MESSAGE_BASE + 0xC,
	PCI_REENABLE                    = PCI_MESSAGE_BASE + 0xD,
	PCI_QUERY_STOP_FAILED           = PCI_MESSAGE_BASE + 0xE,
	PCI_EJECTION_COMPLETE           = PCI_MESSAGE_BASE + 0xF,
	PCI_RESOURCES_ASSIGNED          = PCI_MESSAGE_BASE + 0x10,
	PCI_RESOURCES_RELEASED          = PCI_MESSAGE_BASE + 0x11,
	PCI_INVALIDATE_BLOCK            = PCI_MESSAGE_BASE + 0x12,
	PCI_QUERY_PROTOCOL_VERSION      = PCI_MESSAGE_BASE + 0x13,
	PCI_CREATE_INTERRUPT_MESSAGE    = PCI_MESSAGE_BASE + 0x14,
	PCI_DELETE_INTERRUPT_MESSAGE    = PCI_MESSAGE_BASE + 0x15,
	PCI_RESOURCES_ASSIGNED2		= PCI_MESSAGE_BASE + 0x16,
	PCI_CREATE_INTERRUPT_MESSAGE2	= PCI_MESSAGE_BASE + 0x17,
	PCI_DELETE_INTERRUPT_MESSAGE2	= PCI_MESSAGE_BASE + 0x18, /* unused */
	PCI_BUS_RELATIONS2		= PCI_MESSAGE_BASE + 0x19,
	PCI_MESSAGE_MAXIMUM
पूर्ण;

/*
 * Structures defining the भव PCI Express protocol.
 */

जोड़ pci_version अणु
	काष्ठा अणु
		u16 minor_version;
		u16 major_version;
	पूर्ण parts;
	u32 version;
पूर्ण __packed;

/*
 * Function numbers are 8-bits wide on Express, as पूर्णांकerpreted through ARI,
 * which is all this driver करोes.  This representation is the one used in
 * Winकरोws, which is what is expected when sending this back and क्रमth with
 * the Hyper-V parent partition.
 */
जोड़ win_slot_encoding अणु
	काष्ठा अणु
		u32	dev:5;
		u32	func:3;
		u32	reserved:24;
	पूर्ण bits;
	u32 slot;
पूर्ण __packed;

/*
 * Pretty much as defined in the PCI Specअगरications.
 */
काष्ठा pci_function_description अणु
	u16	v_id;	/* venकरोr ID */
	u16	d_id;	/* device ID */
	u8	rev;
	u8	prog_पूर्णांकf;
	u8	subclass;
	u8	base_class;
	u32	subप्रणाली_id;
	जोड़ win_slot_encoding win_slot;
	u32	ser;	/* serial number */
पूर्ण __packed;

क्रमागत pci_device_description_flags अणु
	HV_PCI_DEVICE_FLAG_NONE			= 0x0,
	HV_PCI_DEVICE_FLAG_NUMA_AFFINITY	= 0x1,
पूर्ण;

काष्ठा pci_function_description2 अणु
	u16	v_id;	/* venकरोr ID */
	u16	d_id;	/* device ID */
	u8	rev;
	u8	prog_पूर्णांकf;
	u8	subclass;
	u8	base_class;
	u32	subप्रणाली_id;
	जोड़	win_slot_encoding win_slot;
	u32	ser;	/* serial number */
	u32	flags;
	u16	भव_numa_node;
	u16	reserved;
पूर्ण __packed;

/**
 * काष्ठा hv_msi_desc
 * @vector:		IDT entry
 * @delivery_mode:	As defined in Intel's Programmer's
 *			Reference Manual, Volume 3, Chapter 8.
 * @vector_count:	Number of contiguous entries in the
 *			Interrupt Descriptor Table that are
 *			occupied by this Message-Signaled
 *			Interrupt. For "MSI", as first defined
 *			in PCI 2.2, this can be between 1 and
 *			32. For "MSI-X," as first defined in PCI
 *			3.0, this must be 1, as each MSI-X table
 *			entry would have its own descriptor.
 * @reserved:		Empty space
 * @cpu_mask:		All the target भव processors.
 */
काष्ठा hv_msi_desc अणु
	u8	vector;
	u8	delivery_mode;
	u16	vector_count;
	u32	reserved;
	u64	cpu_mask;
पूर्ण __packed;

/**
 * काष्ठा hv_msi_desc2 - 1.2 version of hv_msi_desc
 * @vector:		IDT entry
 * @delivery_mode:	As defined in Intel's Programmer's
 *			Reference Manual, Volume 3, Chapter 8.
 * @vector_count:	Number of contiguous entries in the
 *			Interrupt Descriptor Table that are
 *			occupied by this Message-Signaled
 *			Interrupt. For "MSI", as first defined
 *			in PCI 2.2, this can be between 1 and
 *			32. For "MSI-X," as first defined in PCI
 *			3.0, this must be 1, as each MSI-X table
 *			entry would have its own descriptor.
 * @processor_count:	number of bits enabled in array.
 * @processor_array:	All the target भव processors.
 */
काष्ठा hv_msi_desc2 अणु
	u8	vector;
	u8	delivery_mode;
	u16	vector_count;
	u16	processor_count;
	u16	processor_array[32];
पूर्ण __packed;

/**
 * काष्ठा tran_पूर्णांक_desc
 * @reserved:		unused, padding
 * @vector_count:	same as in hv_msi_desc
 * @data:		This is the "data payload" value that is
 *			written by the device when it generates
 *			a message-संकेतed पूर्णांकerrupt, either MSI
 *			or MSI-X.
 * @address:		This is the address to which the data
 *			payload is written on पूर्णांकerrupt
 *			generation.
 */
काष्ठा tran_पूर्णांक_desc अणु
	u16	reserved;
	u16	vector_count;
	u32	data;
	u64	address;
पूर्ण __packed;

/*
 * A generic message क्रमmat क्रम भव PCI.
 * Specअगरic message क्रमmats are defined later in the file.
 */

काष्ठा pci_message अणु
	u32 type;
पूर्ण __packed;

काष्ठा pci_child_message अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
पूर्ण __packed;

काष्ठा pci_incoming_message अणु
	काष्ठा vmpacket_descriptor hdr;
	काष्ठा pci_message message_type;
पूर्ण __packed;

काष्ठा pci_response अणु
	काष्ठा vmpacket_descriptor hdr;
	s32 status;			/* negative values are failures */
पूर्ण __packed;

काष्ठा pci_packet अणु
	व्योम (*completion_func)(व्योम *context, काष्ठा pci_response *resp,
				पूर्णांक resp_packet_size);
	व्योम *compl_ctxt;

	काष्ठा pci_message message[];
पूर्ण;

/*
 * Specअगरic message types supporting the PCI protocol.
 */

/*
 * Version negotiation message. Sent from the guest to the host.
 * The guest is मुक्त to try dअगरferent versions until the host
 * accepts the version.
 *
 * pci_version: The protocol version requested.
 * is_last_attempt: If TRUE, this is the last version guest will request.
 * reservedz: Reserved field, set to zero.
 */

काष्ठा pci_version_request अणु
	काष्ठा pci_message message_type;
	u32 protocol_version;
पूर्ण __packed;

/*
 * Bus D0 Entry.  This is sent from the guest to the host when the भव
 * bus (PCI Express port) is पढ़ोy क्रम action.
 */

काष्ठा pci_bus_d0_entry अणु
	काष्ठा pci_message message_type;
	u32 reserved;
	u64 mmio_base;
पूर्ण __packed;

काष्ठा pci_bus_relations अणु
	काष्ठा pci_incoming_message incoming;
	u32 device_count;
	काष्ठा pci_function_description func[];
पूर्ण __packed;

काष्ठा pci_bus_relations2 अणु
	काष्ठा pci_incoming_message incoming;
	u32 device_count;
	काष्ठा pci_function_description2 func[];
पूर्ण __packed;

काष्ठा pci_q_res_req_response अणु
	काष्ठा vmpacket_descriptor hdr;
	s32 status;			/* negative values are failures */
	u32 probed_bar[PCI_STD_NUM_BARS];
पूर्ण __packed;

काष्ठा pci_set_घातer अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
	u32 घातer_state;		/* In Winकरोws terms */
	u32 reserved;
पूर्ण __packed;

काष्ठा pci_set_घातer_response अणु
	काष्ठा vmpacket_descriptor hdr;
	s32 status;			/* negative values are failures */
	जोड़ win_slot_encoding wslot;
	u32 resultant_state;		/* In Winकरोws terms */
	u32 reserved;
पूर्ण __packed;

काष्ठा pci_resources_asचिन्हित अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
	u8 memory_range[0x14][6];	/* not used here */
	u32 msi_descriptors;
	u32 reserved[4];
पूर्ण __packed;

काष्ठा pci_resources_asचिन्हित2 अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
	u8 memory_range[0x14][6];	/* not used here */
	u32 msi_descriptor_count;
	u8 reserved[70];
पूर्ण __packed;

काष्ठा pci_create_पूर्णांकerrupt अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
	काष्ठा hv_msi_desc पूर्णांक_desc;
पूर्ण __packed;

काष्ठा pci_create_पूर्णांक_response अणु
	काष्ठा pci_response response;
	u32 reserved;
	काष्ठा tran_पूर्णांक_desc पूर्णांक_desc;
पूर्ण __packed;

काष्ठा pci_create_पूर्णांकerrupt2 अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
	काष्ठा hv_msi_desc2 पूर्णांक_desc;
पूर्ण __packed;

काष्ठा pci_delete_पूर्णांकerrupt अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
	काष्ठा tran_पूर्णांक_desc पूर्णांक_desc;
पूर्ण __packed;

/*
 * Note: the VM must pass a valid block id, wslot and bytes_requested.
 */
काष्ठा pci_पढ़ो_block अणु
	काष्ठा pci_message message_type;
	u32 block_id;
	जोड़ win_slot_encoding wslot;
	u32 bytes_requested;
पूर्ण __packed;

काष्ठा pci_पढ़ो_block_response अणु
	काष्ठा vmpacket_descriptor hdr;
	u32 status;
	u8 bytes[HV_CONFIG_BLOCK_SIZE_MAX];
पूर्ण __packed;

/*
 * Note: the VM must pass a valid block id, wslot and byte_count.
 */
काष्ठा pci_ग_लिखो_block अणु
	काष्ठा pci_message message_type;
	u32 block_id;
	जोड़ win_slot_encoding wslot;
	u32 byte_count;
	u8 bytes[HV_CONFIG_BLOCK_SIZE_MAX];
पूर्ण __packed;

काष्ठा pci_dev_inval_block अणु
	काष्ठा pci_incoming_message incoming;
	जोड़ win_slot_encoding wslot;
	u64 block_mask;
पूर्ण __packed;

काष्ठा pci_dev_incoming अणु
	काष्ठा pci_incoming_message incoming;
	जोड़ win_slot_encoding wslot;
पूर्ण __packed;

काष्ठा pci_eject_response अणु
	काष्ठा pci_message message_type;
	जोड़ win_slot_encoding wslot;
	u32 status;
पूर्ण __packed;

अटल पूर्णांक pci_ring_size = (4 * PAGE_SIZE);

/*
 * Driver specअगरic state.
 */

क्रमागत hv_pcibus_state अणु
	hv_pcibus_init = 0,
	hv_pcibus_probed,
	hv_pcibus_installed,
	hv_pcibus_removing,
	hv_pcibus_हटाओd,
	hv_pcibus_maximum
पूर्ण;

काष्ठा hv_pcibus_device अणु
	काष्ठा pci_sysdata sysdata;
	/* Protocol version negotiated with the host */
	क्रमागत pci_protocol_version_t protocol_version;
	क्रमागत hv_pcibus_state state;
	refcount_t हटाओ_lock;
	काष्ठा hv_device *hdev;
	resource_माप_प्रकार low_mmio_space;
	resource_माप_प्रकार high_mmio_space;
	काष्ठा resource *mem_config;
	काष्ठा resource *low_mmio_res;
	काष्ठा resource *high_mmio_res;
	काष्ठा completion *survey_event;
	काष्ठा completion हटाओ_event;
	काष्ठा pci_bus *pci_bus;
	spinlock_t config_lock;	/* Aव्योम two thपढ़ोs writing index page */
	spinlock_t device_list_lock;	/* Protect lists below */
	व्योम __iomem *cfg_addr;

	काष्ठा list_head resources_क्रम_children;

	काष्ठा list_head children;
	काष्ठा list_head dr_list;

	काष्ठा msi_करोमुख्य_info msi_info;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;

	spinlock_t retarget_msi_पूर्णांकerrupt_lock;

	काष्ठा workqueue_काष्ठा *wq;

	/* Highest slot of child device with resources allocated */
	पूर्णांक wslot_res_allocated;

	/* hypercall arg, must not cross page boundary */
	काष्ठा hv_retarget_device_पूर्णांकerrupt retarget_msi_पूर्णांकerrupt_params;

	/*
	 * Don't put anything here: retarget_msi_पूर्णांकerrupt_params must be last
	 */
पूर्ण;

/*
 * Tracks "Device Relations" messages from the host, which must be both
 * processed in order and deferred so that they करोn't run in the context
 * of the incoming packet callback.
 */
काष्ठा hv_dr_work अणु
	काष्ठा work_काष्ठा wrk;
	काष्ठा hv_pcibus_device *bus;
पूर्ण;

काष्ठा hv_pcidev_description अणु
	u16	v_id;	/* venकरोr ID */
	u16	d_id;	/* device ID */
	u8	rev;
	u8	prog_पूर्णांकf;
	u8	subclass;
	u8	base_class;
	u32	subप्रणाली_id;
	जोड़	win_slot_encoding win_slot;
	u32	ser;	/* serial number */
	u32	flags;
	u16	भव_numa_node;
पूर्ण;

काष्ठा hv_dr_state अणु
	काष्ठा list_head list_entry;
	u32 device_count;
	काष्ठा hv_pcidev_description func[];
पूर्ण;

क्रमागत hv_pcichild_state अणु
	hv_pcichild_init = 0,
	hv_pcichild_requirements,
	hv_pcichild_resourced,
	hv_pcichild_ejecting,
	hv_pcichild_maximum
पूर्ण;

काष्ठा hv_pci_dev अणु
	/* List रक्षित by pci_rescan_हटाओ_lock */
	काष्ठा list_head list_entry;
	refcount_t refs;
	क्रमागत hv_pcichild_state state;
	काष्ठा pci_slot *pci_slot;
	काष्ठा hv_pcidev_description desc;
	bool reported_missing;
	काष्ठा hv_pcibus_device *hbus;
	काष्ठा work_काष्ठा wrk;

	व्योम (*block_invalidate)(व्योम *context, u64 block_mask);
	व्योम *invalidate_context;

	/*
	 * What would be observed अगर one wrote 0xFFFFFFFF to a BAR and then
	 * पढ़ो it back, क्रम each of the BAR offsets within config space.
	 */
	u32 probed_bar[PCI_STD_NUM_BARS];
पूर्ण;

काष्ठा hv_pci_compl अणु
	काष्ठा completion host_event;
	s32 completion_status;
पूर्ण;

अटल व्योम hv_pci_onchannelcallback(व्योम *context);

/**
 * hv_pci_generic_compl() - Invoked क्रम a completion packet
 * @context:		Set up by the sender of the packet.
 * @resp:		The response packet
 * @resp_packet_size:	Size in bytes of the packet
 *
 * This function is used to trigger an event and report status
 * क्रम any message क्रम which the completion packet contains a
 * status and nothing अन्यथा.
 */
अटल व्योम hv_pci_generic_compl(व्योम *context, काष्ठा pci_response *resp,
				 पूर्णांक resp_packet_size)
अणु
	काष्ठा hv_pci_compl *comp_pkt = context;

	अगर (resp_packet_size >= दुरत्वend(काष्ठा pci_response, status))
		comp_pkt->completion_status = resp->status;
	अन्यथा
		comp_pkt->completion_status = -1;

	complete(&comp_pkt->host_event);
पूर्ण

अटल काष्ठा hv_pci_dev *get_pcichild_wslot(काष्ठा hv_pcibus_device *hbus,
						u32 wslot);

अटल व्योम get_pcichild(काष्ठा hv_pci_dev *hpdev)
अणु
	refcount_inc(&hpdev->refs);
पूर्ण

अटल व्योम put_pcichild(काष्ठा hv_pci_dev *hpdev)
अणु
	अगर (refcount_dec_and_test(&hpdev->refs))
		kमुक्त(hpdev);
पूर्ण

अटल व्योम get_hvpcibus(काष्ठा hv_pcibus_device *hv_pcibus);
अटल व्योम put_hvpcibus(काष्ठा hv_pcibus_device *hv_pcibus);

/*
 * There is no good way to get notअगरied from vmbus_onoffer_rescind(),
 * so let's use polling here, since this is not a hot path.
 */
अटल पूर्णांक रुको_क्रम_response(काष्ठा hv_device *hdev,
			     काष्ठा completion *comp)
अणु
	जबतक (true) अणु
		अगर (hdev->channel->rescind) अणु
			dev_warn_once(&hdev->device, "The device is gone.\n");
			वापस -ENODEV;
		पूर्ण

		अगर (रुको_क्रम_completion_समयout(comp, HZ / 10))
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * devfn_to_wslot() - Convert from Linux PCI slot to Winकरोws
 * @devfn:	The Linux representation of PCI slot
 *
 * Winकरोws uses a slightly dअगरferent representation of PCI slot.
 *
 * Return: The Winकरोws representation
 */
अटल u32 devfn_to_wslot(पूर्णांक devfn)
अणु
	जोड़ win_slot_encoding wslot;

	wslot.slot = 0;
	wslot.bits.dev = PCI_SLOT(devfn);
	wslot.bits.func = PCI_FUNC(devfn);

	वापस wslot.slot;
पूर्ण

/**
 * wslot_to_devfn() - Convert from Winकरोws PCI slot to Linux
 * @wslot:	The Winकरोws representation of PCI slot
 *
 * Winकरोws uses a slightly dअगरferent representation of PCI slot.
 *
 * Return: The Linux representation
 */
अटल पूर्णांक wslot_to_devfn(u32 wslot)
अणु
	जोड़ win_slot_encoding slot_no;

	slot_no.slot = wslot;
	वापस PCI_DEVFN(slot_no.bits.dev, slot_no.bits.func);
पूर्ण

/*
 * PCI Configuration Space क्रम these root PCI buses is implemented as a pair
 * of pages in memory-mapped I/O space.  Writing to the first page chooses
 * the PCI function being written or पढ़ो.  Once the first page has been
 * written to, the following page maps in the entire configuration space of
 * the function.
 */

/**
 * _hv_pcअगरront_पढ़ो_config() - Internal PCI config पढ़ो
 * @hpdev:	The PCI driver's representation of the device
 * @where:	Offset within config space
 * @size:	Size of the transfer
 * @val:	Poपूर्णांकer to the buffer receiving the data
 */
अटल व्योम _hv_pcअगरront_पढ़ो_config(काष्ठा hv_pci_dev *hpdev, पूर्णांक where,
				     पूर्णांक size, u32 *val)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr = hpdev->hbus->cfg_addr + CFG_PAGE_OFFSET + where;

	/*
	 * If the attempt is to पढ़ो the IDs or the ROM BAR, simulate that.
	 */
	अगर (where + size <= PCI_COMMAND) अणु
		स_नकल(val, ((u8 *)&hpdev->desc.v_id) + where, size);
	पूर्ण अन्यथा अगर (where >= PCI_CLASS_REVISION && where + size <=
		   PCI_CACHE_LINE_SIZE) अणु
		स_नकल(val, ((u8 *)&hpdev->desc.rev) + where -
		       PCI_CLASS_REVISION, size);
	पूर्ण अन्यथा अगर (where >= PCI_SUBSYSTEM_VENDOR_ID && where + size <=
		   PCI_ROM_ADDRESS) अणु
		स_नकल(val, (u8 *)&hpdev->desc.subप्रणाली_id + where -
		       PCI_SUBSYSTEM_VENDOR_ID, size);
	पूर्ण अन्यथा अगर (where >= PCI_ROM_ADDRESS && where + size <=
		   PCI_CAPABILITY_LIST) अणु
		/* ROM BARs are unimplemented */
		*val = 0;
	पूर्ण अन्यथा अगर (where >= PCI_INTERRUPT_LINE && where + size <=
		   PCI_INTERRUPT_PIN) अणु
		/*
		 * Interrupt Line and Interrupt PIN are hard-wired to zero
		 * because this front-end only supports message-संकेतed
		 * पूर्णांकerrupts.
		 */
		*val = 0;
	पूर्ण अन्यथा अगर (where + size <= CFG_PAGE_SIZE) अणु
		spin_lock_irqsave(&hpdev->hbus->config_lock, flags);
		/* Choose the function to be पढ़ो. (See comment above) */
		ग_लिखोl(hpdev->desc.win_slot.slot, hpdev->hbus->cfg_addr);
		/* Make sure the function was chosen beक्रमe we start पढ़ोing. */
		mb();
		/* Read from that function's config space. */
		चयन (size) अणु
		हाल 1:
			*val = पढ़ोb(addr);
			अवरोध;
		हाल 2:
			*val = पढ़ोw(addr);
			अवरोध;
		शेष:
			*val = पढ़ोl(addr);
			अवरोध;
		पूर्ण
		/*
		 * Make sure the पढ़ो was करोne beक्रमe we release the spinlock
		 * allowing consecutive पढ़ोs/ग_लिखोs.
		 */
		mb();
		spin_unlock_irqrestore(&hpdev->hbus->config_lock, flags);
	पूर्ण अन्यथा अणु
		dev_err(&hpdev->hbus->hdev->device,
			"Attempt to read beyond a function's config space.\n");
	पूर्ण
पूर्ण

अटल u16 hv_pcअगरront_get_venकरोr_id(काष्ठा hv_pci_dev *hpdev)
अणु
	u16 ret;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr = hpdev->hbus->cfg_addr + CFG_PAGE_OFFSET +
			     PCI_VENDOR_ID;

	spin_lock_irqsave(&hpdev->hbus->config_lock, flags);

	/* Choose the function to be पढ़ो. (See comment above) */
	ग_लिखोl(hpdev->desc.win_slot.slot, hpdev->hbus->cfg_addr);
	/* Make sure the function was chosen beक्रमe we start पढ़ोing. */
	mb();
	/* Read from that function's config space. */
	ret = पढ़ोw(addr);
	/*
	 * mb() is not required here, because the spin_unlock_irqrestore()
	 * is a barrier.
	 */

	spin_unlock_irqrestore(&hpdev->hbus->config_lock, flags);

	वापस ret;
पूर्ण

/**
 * _hv_pcअगरront_ग_लिखो_config() - Internal PCI config ग_लिखो
 * @hpdev:	The PCI driver's representation of the device
 * @where:	Offset within config space
 * @size:	Size of the transfer
 * @val:	The data being transferred
 */
अटल व्योम _hv_pcअगरront_ग_लिखो_config(काष्ठा hv_pci_dev *hpdev, पूर्णांक where,
				      पूर्णांक size, u32 val)
अणु
	अचिन्हित दीर्घ flags;
	व्योम __iomem *addr = hpdev->hbus->cfg_addr + CFG_PAGE_OFFSET + where;

	अगर (where >= PCI_SUBSYSTEM_VENDOR_ID &&
	    where + size <= PCI_CAPABILITY_LIST) अणु
		/* SSIDs and ROM BARs are पढ़ो-only */
	पूर्ण अन्यथा अगर (where >= PCI_COMMAND && where + size <= CFG_PAGE_SIZE) अणु
		spin_lock_irqsave(&hpdev->hbus->config_lock, flags);
		/* Choose the function to be written. (See comment above) */
		ग_लिखोl(hpdev->desc.win_slot.slot, hpdev->hbus->cfg_addr);
		/* Make sure the function was chosen beक्रमe we start writing. */
		wmb();
		/* Write to that function's config space. */
		चयन (size) अणु
		हाल 1:
			ग_लिखोb(val, addr);
			अवरोध;
		हाल 2:
			ग_लिखोw(val, addr);
			अवरोध;
		शेष:
			ग_लिखोl(val, addr);
			अवरोध;
		पूर्ण
		/*
		 * Make sure the ग_लिखो was करोne beक्रमe we release the spinlock
		 * allowing consecutive पढ़ोs/ग_लिखोs.
		 */
		mb();
		spin_unlock_irqrestore(&hpdev->hbus->config_lock, flags);
	पूर्ण अन्यथा अणु
		dev_err(&hpdev->hbus->hdev->device,
			"Attempt to write beyond a function's config space.\n");
	पूर्ण
पूर्ण

/**
 * hv_pcअगरront_पढ़ो_config() - Read configuration space
 * @bus: PCI Bus काष्ठाure
 * @devfn: Device/function
 * @where: Offset from base
 * @size: Byte/word/dword
 * @val: Value to be पढ़ो
 *
 * Return: PCIBIOS_SUCCESSFUL on success
 *	   PCIBIOS_DEVICE_NOT_FOUND on failure
 */
अटल पूर्णांक hv_pcअगरront_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा hv_pcibus_device *hbus =
		container_of(bus->sysdata, काष्ठा hv_pcibus_device, sysdata);
	काष्ठा hv_pci_dev *hpdev;

	hpdev = get_pcichild_wslot(hbus, devfn_to_wslot(devfn));
	अगर (!hpdev)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	_hv_pcअगरront_पढ़ो_config(hpdev, where, size, val);

	put_pcichild(hpdev);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

/**
 * hv_pcअगरront_ग_लिखो_config() - Write configuration space
 * @bus: PCI Bus काष्ठाure
 * @devfn: Device/function
 * @where: Offset from base
 * @size: Byte/word/dword
 * @val: Value to be written to device
 *
 * Return: PCIBIOS_SUCCESSFUL on success
 *	   PCIBIOS_DEVICE_NOT_FOUND on failure
 */
अटल पूर्णांक hv_pcअगरront_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा hv_pcibus_device *hbus =
	    container_of(bus->sysdata, काष्ठा hv_pcibus_device, sysdata);
	काष्ठा hv_pci_dev *hpdev;

	hpdev = get_pcichild_wslot(hbus, devfn_to_wslot(devfn));
	अगर (!hpdev)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	_hv_pcअगरront_ग_लिखो_config(hpdev, where, size, val);

	put_pcichild(hpdev);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

/* PCIe operations */
अटल काष्ठा pci_ops hv_pcअगरront_ops = अणु
	.पढ़ो  = hv_pcअगरront_पढ़ो_config,
	.ग_लिखो = hv_pcअगरront_ग_लिखो_config,
पूर्ण;

/*
 * Paraभव backchannel
 *
 * Hyper-V SR-IOV provides a backchannel mechanism in software क्रम
 * communication between a VF driver and a PF driver.  These
 * "configuration blocks" are similar in concept to PCI configuration space,
 * but instead of करोing पढ़ोs and ग_लिखोs in 32-bit chunks through a very slow
 * path, packets of up to 128 bytes can be sent or received asynchronously.
 *
 * Nearly every SR-IOV device contains just such a communications channel in
 * hardware, so using this one in software is usually optional.  Using the
 * software channel, however, allows driver implementers to leverage software
 * tools that fuzz the communications channel looking क्रम vulnerabilities.
 *
 * The usage model क्रम these packets माला_दो the responsibility क्रम पढ़ोing or
 * writing on the VF driver.  The VF driver sends a पढ़ो or a ग_लिखो packet,
 * indicating which "block" is being referred to by number.
 *
 * If the PF driver wishes to initiate communication, it can "invalidate" one or
 * more of the first 64 blocks.  This invalidation is delivered via a callback
 * supplied by the VF driver by this driver.
 *
 * No protocol is implied, except that supplied by the PF and VF drivers.
 */

काष्ठा hv_पढ़ो_config_compl अणु
	काष्ठा hv_pci_compl comp_pkt;
	व्योम *buf;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक bytes_वापसed;
पूर्ण;

/**
 * hv_pci_पढ़ो_config_compl() - Invoked when a response packet
 * क्रम a पढ़ो config block operation arrives.
 * @context:		Identअगरies the पढ़ो config operation
 * @resp:		The response packet itself
 * @resp_packet_size:	Size in bytes of the response packet
 */
अटल व्योम hv_pci_पढ़ो_config_compl(व्योम *context, काष्ठा pci_response *resp,
				     पूर्णांक resp_packet_size)
अणु
	काष्ठा hv_पढ़ो_config_compl *comp = context;
	काष्ठा pci_पढ़ो_block_response *पढ़ो_resp =
		(काष्ठा pci_पढ़ो_block_response *)resp;
	अचिन्हित पूर्णांक data_len, hdr_len;

	hdr_len = दुरत्व(काष्ठा pci_पढ़ो_block_response, bytes);
	अगर (resp_packet_size < hdr_len) अणु
		comp->comp_pkt.completion_status = -1;
		जाओ out;
	पूर्ण

	data_len = resp_packet_size - hdr_len;
	अगर (data_len > 0 && पढ़ो_resp->status == 0) अणु
		comp->bytes_वापसed = min(comp->len, data_len);
		स_नकल(comp->buf, पढ़ो_resp->bytes, comp->bytes_वापसed);
	पूर्ण अन्यथा अणु
		comp->bytes_वापसed = 0;
	पूर्ण

	comp->comp_pkt.completion_status = पढ़ो_resp->status;
out:
	complete(&comp->comp_pkt.host_event);
पूर्ण

/**
 * hv_पढ़ो_config_block() - Sends a पढ़ो config block request to
 * the back-end driver running in the Hyper-V parent partition.
 * @pdev:		The PCI driver's representation क्रम this device.
 * @buf:		Buffer पूर्णांकo which the config block will be copied.
 * @len:		Size in bytes of buf.
 * @block_id:		Identअगरies the config block which has been requested.
 * @bytes_वापसed:	Size which came back from the back-end driver.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_पढ़ो_config_block(काष्ठा pci_dev *pdev, व्योम *buf,
				अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक block_id,
				अचिन्हित पूर्णांक *bytes_वापसed)
अणु
	काष्ठा hv_pcibus_device *hbus =
		container_of(pdev->bus->sysdata, काष्ठा hv_pcibus_device,
			     sysdata);
	काष्ठा अणु
		काष्ठा pci_packet pkt;
		अक्षर buf[माप(काष्ठा pci_पढ़ो_block)];
	पूर्ण pkt;
	काष्ठा hv_पढ़ो_config_compl comp_pkt;
	काष्ठा pci_पढ़ो_block *पढ़ो_blk;
	पूर्णांक ret;

	अगर (len == 0 || len > HV_CONFIG_BLOCK_SIZE_MAX)
		वापस -EINVAL;

	init_completion(&comp_pkt.comp_pkt.host_event);
	comp_pkt.buf = buf;
	comp_pkt.len = len;

	स_रखो(&pkt, 0, माप(pkt));
	pkt.pkt.completion_func = hv_pci_पढ़ो_config_compl;
	pkt.pkt.compl_ctxt = &comp_pkt;
	पढ़ो_blk = (काष्ठा pci_पढ़ो_block *)&pkt.pkt.message;
	पढ़ो_blk->message_type.type = PCI_READ_BLOCK;
	पढ़ो_blk->wslot.slot = devfn_to_wslot(pdev->devfn);
	पढ़ो_blk->block_id = block_id;
	पढ़ो_blk->bytes_requested = len;

	ret = vmbus_sendpacket(hbus->hdev->channel, पढ़ो_blk,
			       माप(*पढ़ो_blk), (अचिन्हित दीर्घ)&pkt.pkt,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_response(hbus->hdev, &comp_pkt.comp_pkt.host_event);
	अगर (ret)
		वापस ret;

	अगर (comp_pkt.comp_pkt.completion_status != 0 ||
	    comp_pkt.bytes_वापसed == 0) अणु
		dev_err(&hbus->hdev->device,
			"Read Config Block failed: 0x%x, bytes_returned=%d\n",
			comp_pkt.comp_pkt.completion_status,
			comp_pkt.bytes_वापसed);
		वापस -EIO;
	पूर्ण

	*bytes_वापसed = comp_pkt.bytes_वापसed;
	वापस 0;
पूर्ण

/**
 * hv_pci_ग_लिखो_config_compl() - Invoked when a response packet क्रम a ग_लिखो
 * config block operation arrives.
 * @context:		Identअगरies the ग_लिखो config operation
 * @resp:		The response packet itself
 * @resp_packet_size:	Size in bytes of the response packet
 */
अटल व्योम hv_pci_ग_लिखो_config_compl(व्योम *context, काष्ठा pci_response *resp,
				      पूर्णांक resp_packet_size)
अणु
	काष्ठा hv_pci_compl *comp_pkt = context;

	comp_pkt->completion_status = resp->status;
	complete(&comp_pkt->host_event);
पूर्ण

/**
 * hv_ग_लिखो_config_block() - Sends a ग_लिखो config block request to the
 * back-end driver running in the Hyper-V parent partition.
 * @pdev:		The PCI driver's representation क्रम this device.
 * @buf:		Buffer from which the config block will	be copied.
 * @len:		Size in bytes of buf.
 * @block_id:		Identअगरies the config block which is being written.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_ग_लिखो_config_block(काष्ठा pci_dev *pdev, व्योम *buf,
				अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक block_id)
अणु
	काष्ठा hv_pcibus_device *hbus =
		container_of(pdev->bus->sysdata, काष्ठा hv_pcibus_device,
			     sysdata);
	काष्ठा अणु
		काष्ठा pci_packet pkt;
		अक्षर buf[माप(काष्ठा pci_ग_लिखो_block)];
		u32 reserved;
	पूर्ण pkt;
	काष्ठा hv_pci_compl comp_pkt;
	काष्ठा pci_ग_लिखो_block *ग_लिखो_blk;
	u32 pkt_size;
	पूर्णांक ret;

	अगर (len == 0 || len > HV_CONFIG_BLOCK_SIZE_MAX)
		वापस -EINVAL;

	init_completion(&comp_pkt.host_event);

	स_रखो(&pkt, 0, माप(pkt));
	pkt.pkt.completion_func = hv_pci_ग_लिखो_config_compl;
	pkt.pkt.compl_ctxt = &comp_pkt;
	ग_लिखो_blk = (काष्ठा pci_ग_लिखो_block *)&pkt.pkt.message;
	ग_लिखो_blk->message_type.type = PCI_WRITE_BLOCK;
	ग_लिखो_blk->wslot.slot = devfn_to_wslot(pdev->devfn);
	ग_लिखो_blk->block_id = block_id;
	ग_लिखो_blk->byte_count = len;
	स_नकल(ग_लिखो_blk->bytes, buf, len);
	pkt_size = दुरत्व(काष्ठा pci_ग_लिखो_block, bytes) + len;
	/*
	 * This quirk is required on some hosts shipped around 2018, because
	 * these hosts करोn't check the pkt_size correctly (new hosts have been
	 * fixed since early 2019). The quirk is also safe on very old hosts
	 * and new hosts, because, on them, what really matters is the length
	 * specअगरied in ग_लिखो_blk->byte_count.
	 */
	pkt_size += माप(pkt.reserved);

	ret = vmbus_sendpacket(hbus->hdev->channel, ग_लिखो_blk, pkt_size,
			       (अचिन्हित दीर्घ)&pkt.pkt, VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_response(hbus->hdev, &comp_pkt.host_event);
	अगर (ret)
		वापस ret;

	अगर (comp_pkt.completion_status != 0) अणु
		dev_err(&hbus->hdev->device,
			"Write Config Block failed: 0x%x\n",
			comp_pkt.completion_status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hv_रेजिस्टर_block_invalidate() - Invoked when a config block invalidation
 * arrives from the back-end driver.
 * @pdev:		The PCI driver's representation क्रम this device.
 * @context:		Identअगरies the device.
 * @block_invalidate:	Identअगरies all of the blocks being invalidated.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_रेजिस्टर_block_invalidate(काष्ठा pci_dev *pdev, व्योम *context,
					व्योम (*block_invalidate)(व्योम *context,
								 u64 block_mask))
अणु
	काष्ठा hv_pcibus_device *hbus =
		container_of(pdev->bus->sysdata, काष्ठा hv_pcibus_device,
			     sysdata);
	काष्ठा hv_pci_dev *hpdev;

	hpdev = get_pcichild_wslot(hbus, devfn_to_wslot(pdev->devfn));
	अगर (!hpdev)
		वापस -ENODEV;

	hpdev->block_invalidate = block_invalidate;
	hpdev->invalidate_context = context;

	put_pcichild(hpdev);
	वापस 0;

पूर्ण

/* Interrupt management hooks */
अटल व्योम hv_पूर्णांक_desc_मुक्त(काष्ठा hv_pci_dev *hpdev,
			     काष्ठा tran_पूर्णांक_desc *पूर्णांक_desc)
अणु
	काष्ठा pci_delete_पूर्णांकerrupt *पूर्णांक_pkt;
	काष्ठा अणु
		काष्ठा pci_packet pkt;
		u8 buffer[माप(काष्ठा pci_delete_पूर्णांकerrupt)];
	पूर्ण ctxt;

	स_रखो(&ctxt, 0, माप(ctxt));
	पूर्णांक_pkt = (काष्ठा pci_delete_पूर्णांकerrupt *)&ctxt.pkt.message;
	पूर्णांक_pkt->message_type.type =
		PCI_DELETE_INTERRUPT_MESSAGE;
	पूर्णांक_pkt->wslot.slot = hpdev->desc.win_slot.slot;
	पूर्णांक_pkt->पूर्णांक_desc = *पूर्णांक_desc;
	vmbus_sendpacket(hpdev->hbus->hdev->channel, पूर्णांक_pkt, माप(*पूर्णांक_pkt),
			 (अचिन्हित दीर्घ)&ctxt.pkt, VM_PKT_DATA_INBAND, 0);
	kमुक्त(पूर्णांक_desc);
पूर्ण

/**
 * hv_msi_मुक्त() - Free the MSI.
 * @करोमुख्य:	The पूर्णांकerrupt करोमुख्य poपूर्णांकer
 * @info:	Extra MSI-related context
 * @irq:	Identअगरies the IRQ.
 *
 * The Hyper-V parent partition and hypervisor are tracking the
 * messages that are in use, keeping the पूर्णांकerrupt redirection
 * table up to date.  This callback sends a message that मुक्तs
 * the IRT entry and related tracking nonsense.
 */
अटल व्योम hv_msi_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, काष्ठा msi_करोमुख्य_info *info,
			अचिन्हित पूर्णांक irq)
अणु
	काष्ठा hv_pcibus_device *hbus;
	काष्ठा hv_pci_dev *hpdev;
	काष्ठा pci_dev *pdev;
	काष्ठा tran_पूर्णांक_desc *पूर्णांक_desc;
	काष्ठा irq_data *irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, irq);
	काष्ठा msi_desc *msi = irq_data_get_msi_desc(irq_data);

	pdev = msi_desc_to_pci_dev(msi);
	hbus = info->data;
	पूर्णांक_desc = irq_data_get_irq_chip_data(irq_data);
	अगर (!पूर्णांक_desc)
		वापस;

	irq_data->chip_data = शून्य;
	hpdev = get_pcichild_wslot(hbus, devfn_to_wslot(pdev->devfn));
	अगर (!hpdev) अणु
		kमुक्त(पूर्णांक_desc);
		वापस;
	पूर्ण

	hv_पूर्णांक_desc_मुक्त(hpdev, पूर्णांक_desc);
	put_pcichild(hpdev);
पूर्ण

अटल पूर्णांक hv_set_affinity(काष्ठा irq_data *data, स्थिर काष्ठा cpumask *dest,
			   bool क्रमce)
अणु
	काष्ठा irq_data *parent = data->parent_data;

	वापस parent->chip->irq_set_affinity(parent, dest, क्रमce);
पूर्ण

अटल व्योम hv_irq_mask(काष्ठा irq_data *data)
अणु
	pci_msi_mask_irq(data);
पूर्ण

/**
 * hv_irq_unmask() - "Unmask" the IRQ by setting its current
 * affinity.
 * @data:	Describes the IRQ
 *
 * Build new a destination क्रम the MSI and make a hypercall to
 * update the Interrupt Redirection Table. "Device Logical ID"
 * is built out of this PCI bus's instance GUID and the function
 * number of the device.
 */
अटल व्योम hv_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा msi_desc *msi_desc = irq_data_get_msi_desc(data);
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	काष्ठा hv_retarget_device_पूर्णांकerrupt *params;
	काष्ठा hv_pcibus_device *hbus;
	काष्ठा cpumask *dest;
	cpumask_var_t पंचांगp;
	काष्ठा pci_bus *pbus;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ flags;
	u32 var_size = 0;
	पूर्णांक cpu, nr_bank;
	u64 res;

	dest = irq_data_get_effective_affinity_mask(data);
	pdev = msi_desc_to_pci_dev(msi_desc);
	pbus = pdev->bus;
	hbus = container_of(pbus->sysdata, काष्ठा hv_pcibus_device, sysdata);

	spin_lock_irqsave(&hbus->retarget_msi_पूर्णांकerrupt_lock, flags);

	params = &hbus->retarget_msi_पूर्णांकerrupt_params;
	स_रखो(params, 0, माप(*params));
	params->partition_id = HV_PARTITION_ID_SELF;
	params->पूर्णांक_entry.source = HV_INTERRUPT_SOURCE_MSI;
	hv_set_msi_entry_from_desc(&params->पूर्णांक_entry.msi_entry, msi_desc);
	params->device_id = (hbus->hdev->dev_instance.b[5] << 24) |
			   (hbus->hdev->dev_instance.b[4] << 16) |
			   (hbus->hdev->dev_instance.b[7] << 8) |
			   (hbus->hdev->dev_instance.b[6] & 0xf8) |
			   PCI_FUNC(pdev->devfn);
	params->पूर्णांक_target.vector = cfg->vector;

	/*
	 * Honoring apic->delivery_mode set to APIC_DELIVERY_MODE_FIXED by
	 * setting the HV_DEVICE_INTERRUPT_TARGET_MULTICAST flag results in a
	 * spurious पूर्णांकerrupt storm. Not करोing so करोes not seem to have a
	 * negative effect (yet?).
	 */

	अगर (hbus->protocol_version >= PCI_PROTOCOL_VERSION_1_2) अणु
		/*
		 * PCI_PROTOCOL_VERSION_1_2 supports the VP_SET version of the
		 * HVCALL_RETARGET_INTERRUPT hypercall, which also coincides
		 * with >64 VP support.
		 * ms_hyperv.hपूर्णांकs & HV_X64_EX_PROCESSOR_MASKS_RECOMMENDED
		 * is not sufficient क्रम this hypercall.
		 */
		params->पूर्णांक_target.flags |=
			HV_DEVICE_INTERRUPT_TARGET_PROCESSOR_SET;

		अगर (!alloc_cpumask_var(&पंचांगp, GFP_ATOMIC)) अणु
			res = 1;
			जाओ निकास_unlock;
		पूर्ण

		cpumask_and(पंचांगp, dest, cpu_online_mask);
		nr_bank = cpumask_to_vpset(&params->पूर्णांक_target.vp_set, पंचांगp);
		मुक्त_cpumask_var(पंचांगp);

		अगर (nr_bank <= 0) अणु
			res = 1;
			जाओ निकास_unlock;
		पूर्ण

		/*
		 * var-sized hypercall, var-size starts after vp_mask (thus
		 * vp_set.क्रमmat करोes not count, but vp_set.valid_bank_mask
		 * करोes).
		 */
		var_size = 1 + nr_bank;
	पूर्ण अन्यथा अणु
		क्रम_each_cpu_and(cpu, dest, cpu_online_mask) अणु
			params->पूर्णांक_target.vp_mask |=
				(1ULL << hv_cpu_number_to_vp_number(cpu));
		पूर्ण
	पूर्ण

	res = hv_करो_hypercall(HVCALL_RETARGET_INTERRUPT | (var_size << 17),
			      params, शून्य);

निकास_unlock:
	spin_unlock_irqrestore(&hbus->retarget_msi_पूर्णांकerrupt_lock, flags);

	/*
	 * During hibernation, when a CPU is offlined, the kernel tries
	 * to move the पूर्णांकerrupt to the reमुख्यing CPUs that haven't
	 * been offlined yet. In this हाल, the below hv_करो_hypercall()
	 * always fails since the vmbus channel has been बंदd:
	 * refer to cpu_disable_common() -> fixup_irqs() ->
	 * irq_migrate_all_off_this_cpu() -> migrate_one_irq().
	 *
	 * Suppress the error message क्रम hibernation because the failure
	 * during hibernation करोes not matter (at this समय all the devices
	 * have been frozen). Note: the correct affinity info is still updated
	 * पूर्णांकo the irqdata data काष्ठाure in migrate_one_irq() ->
	 * irq_करो_set_affinity() -> hv_set_affinity(), so later when the VM
	 * resumes, hv_pci_restore_msi_state() is able to correctly restore
	 * the पूर्णांकerrupt with the correct affinity.
	 */
	अगर (!hv_result_success(res) && hbus->state != hv_pcibus_removing)
		dev_err(&hbus->hdev->device,
			"%s() failed: %#llx", __func__, res);

	pci_msi_unmask_irq(data);
पूर्ण

काष्ठा compose_comp_ctxt अणु
	काष्ठा hv_pci_compl comp_pkt;
	काष्ठा tran_पूर्णांक_desc पूर्णांक_desc;
पूर्ण;

अटल व्योम hv_pci_compose_compl(व्योम *context, काष्ठा pci_response *resp,
				 पूर्णांक resp_packet_size)
अणु
	काष्ठा compose_comp_ctxt *comp_pkt = context;
	काष्ठा pci_create_पूर्णांक_response *पूर्णांक_resp =
		(काष्ठा pci_create_पूर्णांक_response *)resp;

	comp_pkt->comp_pkt.completion_status = resp->status;
	comp_pkt->पूर्णांक_desc = पूर्णांक_resp->पूर्णांक_desc;
	complete(&comp_pkt->comp_pkt.host_event);
पूर्ण

अटल u32 hv_compose_msi_req_v1(
	काष्ठा pci_create_पूर्णांकerrupt *पूर्णांक_pkt, काष्ठा cpumask *affinity,
	u32 slot, u8 vector)
अणु
	पूर्णांक_pkt->message_type.type = PCI_CREATE_INTERRUPT_MESSAGE;
	पूर्णांक_pkt->wslot.slot = slot;
	पूर्णांक_pkt->पूर्णांक_desc.vector = vector;
	पूर्णांक_pkt->पूर्णांक_desc.vector_count = 1;
	पूर्णांक_pkt->पूर्णांक_desc.delivery_mode = APIC_DELIVERY_MODE_FIXED;

	/*
	 * Create MSI w/ dummy vCPU set, overwritten by subsequent retarget in
	 * hv_irq_unmask().
	 */
	पूर्णांक_pkt->पूर्णांक_desc.cpu_mask = CPU_AFFINITY_ALL;

	वापस माप(*पूर्णांक_pkt);
पूर्ण

अटल u32 hv_compose_msi_req_v2(
	काष्ठा pci_create_पूर्णांकerrupt2 *पूर्णांक_pkt, काष्ठा cpumask *affinity,
	u32 slot, u8 vector)
अणु
	पूर्णांक cpu;

	पूर्णांक_pkt->message_type.type = PCI_CREATE_INTERRUPT_MESSAGE2;
	पूर्णांक_pkt->wslot.slot = slot;
	पूर्णांक_pkt->पूर्णांक_desc.vector = vector;
	पूर्णांक_pkt->पूर्णांक_desc.vector_count = 1;
	पूर्णांक_pkt->पूर्णांक_desc.delivery_mode = APIC_DELIVERY_MODE_FIXED;

	/*
	 * Create MSI w/ dummy vCPU set targeting just one vCPU, overwritten
	 * by subsequent retarget in hv_irq_unmask().
	 */
	cpu = cpumask_first_and(affinity, cpu_online_mask);
	पूर्णांक_pkt->पूर्णांक_desc.processor_array[0] =
		hv_cpu_number_to_vp_number(cpu);
	पूर्णांक_pkt->पूर्णांक_desc.processor_count = 1;

	वापस माप(*पूर्णांक_pkt);
पूर्ण

/**
 * hv_compose_msi_msg() - Supplies a valid MSI address/data
 * @data:	Everything about this MSI
 * @msg:	Buffer that is filled in by this function
 *
 * This function unpacks the IRQ looking क्रम target CPU set, IDT
 * vector and mode and sends a message to the parent partition
 * asking क्रम a mapping क्रम that tuple in this partition.  The
 * response supplies a data value and address to which that data
 * should be written to trigger that पूर्णांकerrupt.
 */
अटल व्योम hv_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा irq_cfg *cfg = irqd_cfg(data);
	काष्ठा hv_pcibus_device *hbus;
	काष्ठा vmbus_channel *channel;
	काष्ठा hv_pci_dev *hpdev;
	काष्ठा pci_bus *pbus;
	काष्ठा pci_dev *pdev;
	काष्ठा cpumask *dest;
	काष्ठा compose_comp_ctxt comp;
	काष्ठा tran_पूर्णांक_desc *पूर्णांक_desc;
	काष्ठा अणु
		काष्ठा pci_packet pci_pkt;
		जोड़ अणु
			काष्ठा pci_create_पूर्णांकerrupt v1;
			काष्ठा pci_create_पूर्णांकerrupt2 v2;
		पूर्ण पूर्णांक_pkts;
	पूर्ण __packed ctxt;

	u32 size;
	पूर्णांक ret;

	pdev = msi_desc_to_pci_dev(irq_data_get_msi_desc(data));
	dest = irq_data_get_effective_affinity_mask(data);
	pbus = pdev->bus;
	hbus = container_of(pbus->sysdata, काष्ठा hv_pcibus_device, sysdata);
	channel = hbus->hdev->channel;
	hpdev = get_pcichild_wslot(hbus, devfn_to_wslot(pdev->devfn));
	अगर (!hpdev)
		जाओ वापस_null_message;

	/* Free any previous message that might have alपढ़ोy been composed. */
	अगर (data->chip_data) अणु
		पूर्णांक_desc = data->chip_data;
		data->chip_data = शून्य;
		hv_पूर्णांक_desc_मुक्त(hpdev, पूर्णांक_desc);
	पूर्ण

	पूर्णांक_desc = kzalloc(माप(*पूर्णांक_desc), GFP_ATOMIC);
	अगर (!पूर्णांक_desc)
		जाओ drop_reference;

	स_रखो(&ctxt, 0, माप(ctxt));
	init_completion(&comp.comp_pkt.host_event);
	ctxt.pci_pkt.completion_func = hv_pci_compose_compl;
	ctxt.pci_pkt.compl_ctxt = &comp;

	चयन (hbus->protocol_version) अणु
	हाल PCI_PROTOCOL_VERSION_1_1:
		size = hv_compose_msi_req_v1(&ctxt.पूर्णांक_pkts.v1,
					dest,
					hpdev->desc.win_slot.slot,
					cfg->vector);
		अवरोध;

	हाल PCI_PROTOCOL_VERSION_1_2:
	हाल PCI_PROTOCOL_VERSION_1_3:
		size = hv_compose_msi_req_v2(&ctxt.पूर्णांक_pkts.v2,
					dest,
					hpdev->desc.win_slot.slot,
					cfg->vector);
		अवरोध;

	शेष:
		/* As we only negotiate protocol versions known to this driver,
		 * this path should never hit. However, this is it not a hot
		 * path so we prपूर्णांक a message to aid future updates.
		 */
		dev_err(&hbus->hdev->device,
			"Unexpected vPCI protocol, update driver.");
		जाओ मुक्त_पूर्णांक_desc;
	पूर्ण

	ret = vmbus_sendpacket(hpdev->hbus->hdev->channel, &ctxt.पूर्णांक_pkts,
			       size, (अचिन्हित दीर्घ)&ctxt.pci_pkt,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret) अणु
		dev_err(&hbus->hdev->device,
			"Sending request for interrupt failed: 0x%x",
			comp.comp_pkt.completion_status);
		जाओ मुक्त_पूर्णांक_desc;
	पूर्ण

	/*
	 * Prevents hv_pci_onchannelcallback() from running concurrently
	 * in the tasklet.
	 */
	tasklet_disable_in_atomic(&channel->callback_event);

	/*
	 * Since this function is called with IRQ locks held, can't
	 * करो normal रुको क्रम completion; instead poll.
	 */
	जबतक (!try_रुको_क्रम_completion(&comp.comp_pkt.host_event)) अणु
		अचिन्हित दीर्घ flags;

		/* 0xFFFF means an invalid PCI VENDOR ID. */
		अगर (hv_pcअगरront_get_venकरोr_id(hpdev) == 0xFFFF) अणु
			dev_err_once(&hbus->hdev->device,
				     "the device has gone\n");
			जाओ enable_tasklet;
		पूर्ण

		/*
		 * Make sure that the ring buffer data काष्ठाure करोesn't get
		 * मुक्तd जबतक we dereference the ring buffer poपूर्णांकer.  Test
		 * क्रम the channel's onchannel_callback being शून्य within a
		 * sched_lock critical section.  See also the अंतरभूत comments
		 * in vmbus_reset_channel_cb().
		 */
		spin_lock_irqsave(&channel->sched_lock, flags);
		अगर (unlikely(channel->onchannel_callback == शून्य)) अणु
			spin_unlock_irqrestore(&channel->sched_lock, flags);
			जाओ enable_tasklet;
		पूर्ण
		hv_pci_onchannelcallback(hbus);
		spin_unlock_irqrestore(&channel->sched_lock, flags);

		अगर (hpdev->state == hv_pcichild_ejecting) अणु
			dev_err_once(&hbus->hdev->device,
				     "the device is being ejected\n");
			जाओ enable_tasklet;
		पूर्ण

		udelay(100);
	पूर्ण

	tasklet_enable(&channel->callback_event);

	अगर (comp.comp_pkt.completion_status < 0) अणु
		dev_err(&hbus->hdev->device,
			"Request for interrupt failed: 0x%x",
			comp.comp_pkt.completion_status);
		जाओ मुक्त_पूर्णांक_desc;
	पूर्ण

	/*
	 * Record the assignment so that this can be unwound later. Using
	 * irq_set_chip_data() here would be appropriate, but the lock it takes
	 * is alपढ़ोy held.
	 */
	*पूर्णांक_desc = comp.पूर्णांक_desc;
	data->chip_data = पूर्णांक_desc;

	/* Pass up the result. */
	msg->address_hi = comp.पूर्णांक_desc.address >> 32;
	msg->address_lo = comp.पूर्णांक_desc.address & 0xffffffff;
	msg->data = comp.पूर्णांक_desc.data;

	put_pcichild(hpdev);
	वापस;

enable_tasklet:
	tasklet_enable(&channel->callback_event);
मुक्त_पूर्णांक_desc:
	kमुक्त(पूर्णांक_desc);
drop_reference:
	put_pcichild(hpdev);
वापस_null_message:
	msg->address_hi = 0;
	msg->address_lo = 0;
	msg->data = 0;
पूर्ण

/* HW Interrupt Chip Descriptor */
अटल काष्ठा irq_chip hv_msi_irq_chip = अणु
	.name			= "Hyper-V PCIe MSI",
	.irq_compose_msi_msg	= hv_compose_msi_msg,
	.irq_set_affinity	= hv_set_affinity,
	.irq_ack		= irq_chip_ack_parent,
	.irq_mask		= hv_irq_mask,
	.irq_unmask		= hv_irq_unmask,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_ops hv_msi_ops = अणु
	.msi_prepare	= pci_msi_prepare,
	.msi_मुक्त	= hv_msi_मुक्त,
पूर्ण;

/**
 * hv_pcie_init_irq_करोमुख्य() - Initialize IRQ करोमुख्य
 * @hbus:	The root PCI bus
 *
 * This function creates an IRQ करोमुख्य which will be used क्रम
 * पूर्णांकerrupts from devices that have been passed through.  These
 * devices only support MSI and MSI-X, not line-based पूर्णांकerrupts
 * or simulations of line-based पूर्णांकerrupts through PCIe's
 * fabric-layer messages.  Because पूर्णांकerrupts are remapped, we
 * can support multi-message MSI here.
 *
 * Return: '0' on success and error value on failure
 */
अटल पूर्णांक hv_pcie_init_irq_करोमुख्य(काष्ठा hv_pcibus_device *hbus)
अणु
	hbus->msi_info.chip = &hv_msi_irq_chip;
	hbus->msi_info.ops = &hv_msi_ops;
	hbus->msi_info.flags = (MSI_FLAG_USE_DEF_DOM_OPS |
		MSI_FLAG_USE_DEF_CHIP_OPS | MSI_FLAG_MULTI_PCI_MSI |
		MSI_FLAG_PCI_MSIX);
	hbus->msi_info.handler = handle_edge_irq;
	hbus->msi_info.handler_name = "edge";
	hbus->msi_info.data = hbus;
	hbus->irq_करोमुख्य = pci_msi_create_irq_करोमुख्य(hbus->sysdata.fwnode,
						     &hbus->msi_info,
						     x86_vector_करोमुख्य);
	अगर (!hbus->irq_करोमुख्य) अणु
		dev_err(&hbus->hdev->device,
			"Failed to build an MSI IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_bar_size() - Get the address space consumed by a BAR
 * @bar_val:	Value that a BAR वापसed after -1 was written
 *              to it.
 *
 * This function वापसs the size of the BAR, rounded up to 1
 * page.  It has to be rounded up because the hypervisor's page
 * table entry that maps the BAR पूर्णांकo the VM can't specअगरy an
 * offset within a page.  The invariant is that the hypervisor
 * must place any BARs of smaller than page length at the
 * beginning of a page.
 *
 * Return:	Size in bytes of the consumed MMIO space.
 */
अटल u64 get_bar_size(u64 bar_val)
अणु
	वापस round_up((1 + ~(bar_val & PCI_BASE_ADDRESS_MEM_MASK)),
			PAGE_SIZE);
पूर्ण

/**
 * survey_child_resources() - Total all MMIO requirements
 * @hbus:	Root PCI bus, as understood by this driver
 */
अटल व्योम survey_child_resources(काष्ठा hv_pcibus_device *hbus)
अणु
	काष्ठा hv_pci_dev *hpdev;
	resource_माप_प्रकार bar_size = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा completion *event;
	u64 bar_val;
	पूर्णांक i;

	/* If nobody is रुकोing on the answer, करोn't compute it. */
	event = xchg(&hbus->survey_event, शून्य);
	अगर (!event)
		वापस;

	/* If the answer has alपढ़ोy been computed, go with it. */
	अगर (hbus->low_mmio_space || hbus->high_mmio_space) अणु
		complete(event);
		वापस;
	पूर्ण

	spin_lock_irqsave(&hbus->device_list_lock, flags);

	/*
	 * Due to an पूर्णांकeresting quirk of the PCI spec, all memory regions
	 * क्रम a child device are a घातer of 2 in size and aligned in memory,
	 * so it's sufficient to just add them up without tracking alignment.
	 */
	list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
		क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
			अगर (hpdev->probed_bar[i] & PCI_BASE_ADDRESS_SPACE_IO)
				dev_err(&hbus->hdev->device,
					"There's an I/O BAR in this list!\n");

			अगर (hpdev->probed_bar[i] != 0) अणु
				/*
				 * A probed BAR has all the upper bits set that
				 * can be changed.
				 */

				bar_val = hpdev->probed_bar[i];
				अगर (bar_val & PCI_BASE_ADDRESS_MEM_TYPE_64)
					bar_val |=
					((u64)hpdev->probed_bar[++i] << 32);
				अन्यथा
					bar_val |= 0xffffffff00000000ULL;

				bar_size = get_bar_size(bar_val);

				अगर (bar_val & PCI_BASE_ADDRESS_MEM_TYPE_64)
					hbus->high_mmio_space += bar_size;
				अन्यथा
					hbus->low_mmio_space += bar_size;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&hbus->device_list_lock, flags);
	complete(event);
पूर्ण

/**
 * prepopulate_bars() - Fill in BARs with शेषs
 * @hbus:	Root PCI bus, as understood by this driver
 *
 * The core PCI driver code seems much, much happier अगर the BARs
 * क्रम a device have values upon first scan. So fill them in.
 * The algorithm below works करोwn from large sizes to small,
 * attempting to pack the assignments optimally. The assumption,
 * enक्रमced in other parts of the code, is that the beginning of
 * the memory-mapped I/O space will be aligned on the largest
 * BAR size.
 */
अटल व्योम prepopulate_bars(काष्ठा hv_pcibus_device *hbus)
अणु
	resource_माप_प्रकार high_size = 0;
	resource_माप_प्रकार low_size = 0;
	resource_माप_प्रकार high_base = 0;
	resource_माप_प्रकार low_base = 0;
	resource_माप_प्रकार bar_size;
	काष्ठा hv_pci_dev *hpdev;
	अचिन्हित दीर्घ flags;
	u64 bar_val;
	u32 command;
	bool high;
	पूर्णांक i;

	अगर (hbus->low_mmio_space) अणु
		low_size = 1ULL << (63 - __builtin_clzll(hbus->low_mmio_space));
		low_base = hbus->low_mmio_res->start;
	पूर्ण

	अगर (hbus->high_mmio_space) अणु
		high_size = 1ULL <<
			(63 - __builtin_clzll(hbus->high_mmio_space));
		high_base = hbus->high_mmio_res->start;
	पूर्ण

	spin_lock_irqsave(&hbus->device_list_lock, flags);

	/*
	 * Clear the memory enable bit, in हाल it's alपढ़ोy set. This occurs
	 * in the suspend path of hibernation, where the device is suspended,
	 * resumed and suspended again: see hibernation_snapshot() and
	 * hibernation_platक्रमm_enter().
	 *
	 * If the memory enable bit is alपढ़ोy set, Hyper-V silently ignores
	 * the below BAR updates, and the related PCI device driver can not
	 * work, because पढ़ोing from the device रेजिस्टर(s) always वापसs
	 * 0xFFFFFFFF.
	 */
	list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
		_hv_pcअगरront_पढ़ो_config(hpdev, PCI_COMMAND, 2, &command);
		command &= ~PCI_COMMAND_MEMORY;
		_hv_pcअगरront_ग_लिखो_config(hpdev, PCI_COMMAND, 2, command);
	पूर्ण

	/* Pick addresses क्रम the BARs. */
	करो अणु
		list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
			क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
				bar_val = hpdev->probed_bar[i];
				अगर (bar_val == 0)
					जारी;
				high = bar_val & PCI_BASE_ADDRESS_MEM_TYPE_64;
				अगर (high) अणु
					bar_val |=
						((u64)hpdev->probed_bar[i + 1]
						 << 32);
				पूर्ण अन्यथा अणु
					bar_val |= 0xffffffffULL << 32;
				पूर्ण
				bar_size = get_bar_size(bar_val);
				अगर (high) अणु
					अगर (high_size != bar_size) अणु
						i++;
						जारी;
					पूर्ण
					_hv_pcअगरront_ग_लिखो_config(hpdev,
						PCI_BASE_ADDRESS_0 + (4 * i),
						4,
						(u32)(high_base & 0xffffff00));
					i++;
					_hv_pcअगरront_ग_लिखो_config(hpdev,
						PCI_BASE_ADDRESS_0 + (4 * i),
						4, (u32)(high_base >> 32));
					high_base += bar_size;
				पूर्ण अन्यथा अणु
					अगर (low_size != bar_size)
						जारी;
					_hv_pcअगरront_ग_लिखो_config(hpdev,
						PCI_BASE_ADDRESS_0 + (4 * i),
						4,
						(u32)(low_base & 0xffffff00));
					low_base += bar_size;
				पूर्ण
			पूर्ण
			अगर (high_size <= 1 && low_size <= 1) अणु
				/* Set the memory enable bit. */
				_hv_pcअगरront_पढ़ो_config(hpdev, PCI_COMMAND, 2,
							 &command);
				command |= PCI_COMMAND_MEMORY;
				_hv_pcअगरront_ग_लिखो_config(hpdev, PCI_COMMAND, 2,
							  command);
				अवरोध;
			पूर्ण
		पूर्ण

		high_size >>= 1;
		low_size >>= 1;
	पूर्ण  जबतक (high_size || low_size);

	spin_unlock_irqrestore(&hbus->device_list_lock, flags);
पूर्ण

/*
 * Assign entries in sysfs pci slot directory.
 *
 * Note that this function करोes not need to lock the children list
 * because it is called from pci_devices_present_work which
 * is serialized with hv_eject_device_work because they are on the
 * same ordered workqueue. Thereक्रमe hbus->children list will not change
 * even when pci_create_slot sleeps.
 */
अटल व्योम hv_pci_assign_slots(काष्ठा hv_pcibus_device *hbus)
अणु
	काष्ठा hv_pci_dev *hpdev;
	अक्षर name[SLOT_NAME_SIZE];
	पूर्णांक slot_nr;

	list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
		अगर (hpdev->pci_slot)
			जारी;

		slot_nr = PCI_SLOT(wslot_to_devfn(hpdev->desc.win_slot.slot));
		snम_लिखो(name, SLOT_NAME_SIZE, "%u", hpdev->desc.ser);
		hpdev->pci_slot = pci_create_slot(hbus->pci_bus, slot_nr,
					  name, शून्य);
		अगर (IS_ERR(hpdev->pci_slot)) अणु
			pr_warn("pci_create slot %s failed\n", name);
			hpdev->pci_slot = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Remove entries in sysfs pci slot directory.
 */
अटल व्योम hv_pci_हटाओ_slots(काष्ठा hv_pcibus_device *hbus)
अणु
	काष्ठा hv_pci_dev *hpdev;

	list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
		अगर (!hpdev->pci_slot)
			जारी;
		pci_destroy_slot(hpdev->pci_slot);
		hpdev->pci_slot = शून्य;
	पूर्ण
पूर्ण

/*
 * Set NUMA node क्रम the devices on the bus
 */
अटल व्योम hv_pci_assign_numa_node(काष्ठा hv_pcibus_device *hbus)
अणु
	काष्ठा pci_dev *dev;
	काष्ठा pci_bus *bus = hbus->pci_bus;
	काष्ठा hv_pci_dev *hv_dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		hv_dev = get_pcichild_wslot(hbus, devfn_to_wslot(dev->devfn));
		अगर (!hv_dev)
			जारी;

		अगर (hv_dev->desc.flags & HV_PCI_DEVICE_FLAG_NUMA_AFFINITY)
			set_dev_node(&dev->dev, hv_dev->desc.भव_numa_node);

		put_pcichild(hv_dev);
	पूर्ण
पूर्ण

/**
 * create_root_hv_pci_bus() - Expose a new root PCI bus
 * @hbus:	Root PCI bus, as understood by this driver
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक create_root_hv_pci_bus(काष्ठा hv_pcibus_device *hbus)
अणु
	/* Register the device */
	hbus->pci_bus = pci_create_root_bus(&hbus->hdev->device,
					    0, /* bus number is always zero */
					    &hv_pcअगरront_ops,
					    &hbus->sysdata,
					    &hbus->resources_क्रम_children);
	अगर (!hbus->pci_bus)
		वापस -ENODEV;

	pci_lock_rescan_हटाओ();
	pci_scan_child_bus(hbus->pci_bus);
	hv_pci_assign_numa_node(hbus);
	pci_bus_assign_resources(hbus->pci_bus);
	hv_pci_assign_slots(hbus);
	pci_bus_add_devices(hbus->pci_bus);
	pci_unlock_rescan_हटाओ();
	hbus->state = hv_pcibus_installed;
	वापस 0;
पूर्ण

काष्ठा q_res_req_compl अणु
	काष्ठा completion host_event;
	काष्ठा hv_pci_dev *hpdev;
पूर्ण;

/**
 * q_resource_requirements() - Query Resource Requirements
 * @context:		The completion context.
 * @resp:		The response that came from the host.
 * @resp_packet_size:	The size in bytes of resp.
 *
 * This function is invoked on completion of a Query Resource
 * Requirements packet.
 */
अटल व्योम q_resource_requirements(व्योम *context, काष्ठा pci_response *resp,
				    पूर्णांक resp_packet_size)
अणु
	काष्ठा q_res_req_compl *completion = context;
	काष्ठा pci_q_res_req_response *q_res_req =
		(काष्ठा pci_q_res_req_response *)resp;
	पूर्णांक i;

	अगर (resp->status < 0) अणु
		dev_err(&completion->hpdev->hbus->hdev->device,
			"query resource requirements failed: %x\n",
			resp->status);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
			completion->hpdev->probed_bar[i] =
				q_res_req->probed_bar[i];
		पूर्ण
	पूर्ण

	complete(&completion->host_event);
पूर्ण

/**
 * new_pcichild_device() - Create a new child device
 * @hbus:	The पूर्णांकernal काष्ठा tracking this root PCI bus.
 * @desc:	The inक्रमmation supplied so far from the host
 *              about the device.
 *
 * This function creates the tracking काष्ठाure क्रम a new child
 * device and kicks off the process of figuring out what it is.
 *
 * Return: Poपूर्णांकer to the new tracking काष्ठा
 */
अटल काष्ठा hv_pci_dev *new_pcichild_device(काष्ठा hv_pcibus_device *hbus,
		काष्ठा hv_pcidev_description *desc)
अणु
	काष्ठा hv_pci_dev *hpdev;
	काष्ठा pci_child_message *res_req;
	काष्ठा q_res_req_compl comp_pkt;
	काष्ठा अणु
		काष्ठा pci_packet init_packet;
		u8 buffer[माप(काष्ठा pci_child_message)];
	पूर्ण pkt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	hpdev = kzalloc(माप(*hpdev), GFP_KERNEL);
	अगर (!hpdev)
		वापस शून्य;

	hpdev->hbus = hbus;

	स_रखो(&pkt, 0, माप(pkt));
	init_completion(&comp_pkt.host_event);
	comp_pkt.hpdev = hpdev;
	pkt.init_packet.compl_ctxt = &comp_pkt;
	pkt.init_packet.completion_func = q_resource_requirements;
	res_req = (काष्ठा pci_child_message *)&pkt.init_packet.message;
	res_req->message_type.type = PCI_QUERY_RESOURCE_REQUIREMENTS;
	res_req->wslot.slot = desc->win_slot.slot;

	ret = vmbus_sendpacket(hbus->hdev->channel, res_req,
			       माप(काष्ठा pci_child_message),
			       (अचिन्हित दीर्घ)&pkt.init_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret)
		जाओ error;

	अगर (रुको_क्रम_response(hbus->hdev, &comp_pkt.host_event))
		जाओ error;

	hpdev->desc = *desc;
	refcount_set(&hpdev->refs, 1);
	get_pcichild(hpdev);
	spin_lock_irqsave(&hbus->device_list_lock, flags);

	list_add_tail(&hpdev->list_entry, &hbus->children);
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);
	वापस hpdev;

error:
	kमुक्त(hpdev);
	वापस शून्य;
पूर्ण

/**
 * get_pcichild_wslot() - Find device from slot
 * @hbus:	Root PCI bus, as understood by this driver
 * @wslot:	Location on the bus
 *
 * This function looks up a PCI device and वापसs the पूर्णांकernal
 * representation of it.  It acquires a reference on it, so that
 * the device won't be deleted जबतक somebody is using it.  The
 * caller is responsible क्रम calling put_pcichild() to release
 * this reference.
 *
 * Return:	Internal representation of a PCI device
 */
अटल काष्ठा hv_pci_dev *get_pcichild_wslot(काष्ठा hv_pcibus_device *hbus,
					     u32 wslot)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hv_pci_dev *iter, *hpdev = शून्य;

	spin_lock_irqsave(&hbus->device_list_lock, flags);
	list_क्रम_each_entry(iter, &hbus->children, list_entry) अणु
		अगर (iter->desc.win_slot.slot == wslot) अणु
			hpdev = iter;
			get_pcichild(hpdev);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);

	वापस hpdev;
पूर्ण

/**
 * pci_devices_present_work() - Handle new list of child devices
 * @work:	Work काष्ठा embedded in काष्ठा hv_dr_work
 *
 * "Bus Relations" is the Winकरोws term क्रम "children of this
 * bus."  The terminology is preserved here क्रम people trying to
 * debug the पूर्णांकeraction between Hyper-V and Linux.  This
 * function is called when the parent partition reports a list
 * of functions that should be observed under this PCI Express
 * port (bus).
 *
 * This function updates the list, and must tolerate being
 * called multiple बार with the same inक्रमmation.  The typical
 * number of child devices is one, with very atypical हालs
 * involving three or four, so the algorithms used here can be
 * simple and inefficient.
 *
 * It must also treat the omission of a previously observed device as
 * notअगरication that the device no दीर्घer exists.
 *
 * Note that this function is serialized with hv_eject_device_work(),
 * because both are pushed to the ordered workqueue hbus->wq.
 */
अटल व्योम pci_devices_present_work(काष्ठा work_काष्ठा *work)
अणु
	u32 child_no;
	bool found;
	काष्ठा hv_pcidev_description *new_desc;
	काष्ठा hv_pci_dev *hpdev;
	काष्ठा hv_pcibus_device *hbus;
	काष्ठा list_head हटाओd;
	काष्ठा hv_dr_work *dr_wrk;
	काष्ठा hv_dr_state *dr = शून्य;
	अचिन्हित दीर्घ flags;

	dr_wrk = container_of(work, काष्ठा hv_dr_work, wrk);
	hbus = dr_wrk->bus;
	kमुक्त(dr_wrk);

	INIT_LIST_HEAD(&हटाओd);

	/* Pull this off the queue and process it अगर it was the last one. */
	spin_lock_irqsave(&hbus->device_list_lock, flags);
	जबतक (!list_empty(&hbus->dr_list)) अणु
		dr = list_first_entry(&hbus->dr_list, काष्ठा hv_dr_state,
				      list_entry);
		list_del(&dr->list_entry);

		/* Throw this away अगर the list still has stuff in it. */
		अगर (!list_empty(&hbus->dr_list)) अणु
			kमुक्त(dr);
			जारी;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);

	अगर (!dr) अणु
		put_hvpcibus(hbus);
		वापस;
	पूर्ण

	/* First, mark all existing children as reported missing. */
	spin_lock_irqsave(&hbus->device_list_lock, flags);
	list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
		hpdev->reported_missing = true;
	पूर्ण
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);

	/* Next, add back any reported devices. */
	क्रम (child_no = 0; child_no < dr->device_count; child_no++) अणु
		found = false;
		new_desc = &dr->func[child_no];

		spin_lock_irqsave(&hbus->device_list_lock, flags);
		list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
			अगर ((hpdev->desc.win_slot.slot == new_desc->win_slot.slot) &&
			    (hpdev->desc.v_id == new_desc->v_id) &&
			    (hpdev->desc.d_id == new_desc->d_id) &&
			    (hpdev->desc.ser == new_desc->ser)) अणु
				hpdev->reported_missing = false;
				found = true;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&hbus->device_list_lock, flags);

		अगर (!found) अणु
			hpdev = new_pcichild_device(hbus, new_desc);
			अगर (!hpdev)
				dev_err(&hbus->hdev->device,
					"couldn't record a child device.\n");
		पूर्ण
	पूर्ण

	/* Move missing children to a list on the stack. */
	spin_lock_irqsave(&hbus->device_list_lock, flags);
	करो अणु
		found = false;
		list_क्रम_each_entry(hpdev, &hbus->children, list_entry) अणु
			अगर (hpdev->reported_missing) अणु
				found = true;
				put_pcichild(hpdev);
				list_move_tail(&hpdev->list_entry, &हटाओd);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (found);
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);

	/* Delete everything that should no दीर्घer exist. */
	जबतक (!list_empty(&हटाओd)) अणु
		hpdev = list_first_entry(&हटाओd, काष्ठा hv_pci_dev,
					 list_entry);
		list_del(&hpdev->list_entry);

		अगर (hpdev->pci_slot)
			pci_destroy_slot(hpdev->pci_slot);

		put_pcichild(hpdev);
	पूर्ण

	चयन (hbus->state) अणु
	हाल hv_pcibus_installed:
		/*
		 * Tell the core to rescan bus
		 * because there may have been changes.
		 */
		pci_lock_rescan_हटाओ();
		pci_scan_child_bus(hbus->pci_bus);
		hv_pci_assign_numa_node(hbus);
		hv_pci_assign_slots(hbus);
		pci_unlock_rescan_हटाओ();
		अवरोध;

	हाल hv_pcibus_init:
	हाल hv_pcibus_probed:
		survey_child_resources(hbus);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	put_hvpcibus(hbus);
	kमुक्त(dr);
पूर्ण

/**
 * hv_pci_start_relations_work() - Queue work to start device discovery
 * @hbus:	Root PCI bus, as understood by this driver
 * @dr:		The list of children वापसed from host
 *
 * Return:  0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_pci_start_relations_work(काष्ठा hv_pcibus_device *hbus,
				       काष्ठा hv_dr_state *dr)
अणु
	काष्ठा hv_dr_work *dr_wrk;
	अचिन्हित दीर्घ flags;
	bool pending_dr;

	अगर (hbus->state == hv_pcibus_removing) अणु
		dev_info(&hbus->hdev->device,
			 "PCI VMBus BUS_RELATIONS: ignored\n");
		वापस -ENOENT;
	पूर्ण

	dr_wrk = kzalloc(माप(*dr_wrk), GFP_NOWAIT);
	अगर (!dr_wrk)
		वापस -ENOMEM;

	INIT_WORK(&dr_wrk->wrk, pci_devices_present_work);
	dr_wrk->bus = hbus;

	spin_lock_irqsave(&hbus->device_list_lock, flags);
	/*
	 * If pending_dr is true, we have alपढ़ोy queued a work,
	 * which will see the new dr. Otherwise, we need to
	 * queue a new work.
	 */
	pending_dr = !list_empty(&hbus->dr_list);
	list_add_tail(&dr->list_entry, &hbus->dr_list);
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);

	अगर (pending_dr) अणु
		kमुक्त(dr_wrk);
	पूर्ण अन्यथा अणु
		get_hvpcibus(hbus);
		queue_work(hbus->wq, &dr_wrk->wrk);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hv_pci_devices_present() - Handle list of new children
 * @hbus:      Root PCI bus, as understood by this driver
 * @relations: Packet from host listing children
 *
 * Process a new list of devices on the bus. The list of devices is
 * discovered by VSP and sent to us via VSP message PCI_BUS_RELATIONS,
 * whenever a new list of devices क्रम this bus appears.
 */
अटल व्योम hv_pci_devices_present(काष्ठा hv_pcibus_device *hbus,
				   काष्ठा pci_bus_relations *relations)
अणु
	काष्ठा hv_dr_state *dr;
	पूर्णांक i;

	dr = kzalloc(काष्ठा_size(dr, func, relations->device_count),
		     GFP_NOWAIT);
	अगर (!dr)
		वापस;

	dr->device_count = relations->device_count;
	क्रम (i = 0; i < dr->device_count; i++) अणु
		dr->func[i].v_id = relations->func[i].v_id;
		dr->func[i].d_id = relations->func[i].d_id;
		dr->func[i].rev = relations->func[i].rev;
		dr->func[i].prog_पूर्णांकf = relations->func[i].prog_पूर्णांकf;
		dr->func[i].subclass = relations->func[i].subclass;
		dr->func[i].base_class = relations->func[i].base_class;
		dr->func[i].subप्रणाली_id = relations->func[i].subप्रणाली_id;
		dr->func[i].win_slot = relations->func[i].win_slot;
		dr->func[i].ser = relations->func[i].ser;
	पूर्ण

	अगर (hv_pci_start_relations_work(hbus, dr))
		kमुक्त(dr);
पूर्ण

/**
 * hv_pci_devices_present2() - Handle list of new children
 * @hbus:	Root PCI bus, as understood by this driver
 * @relations:	Packet from host listing children
 *
 * This function is the v2 version of hv_pci_devices_present()
 */
अटल व्योम hv_pci_devices_present2(काष्ठा hv_pcibus_device *hbus,
				    काष्ठा pci_bus_relations2 *relations)
अणु
	काष्ठा hv_dr_state *dr;
	पूर्णांक i;

	dr = kzalloc(काष्ठा_size(dr, func, relations->device_count),
		     GFP_NOWAIT);
	अगर (!dr)
		वापस;

	dr->device_count = relations->device_count;
	क्रम (i = 0; i < dr->device_count; i++) अणु
		dr->func[i].v_id = relations->func[i].v_id;
		dr->func[i].d_id = relations->func[i].d_id;
		dr->func[i].rev = relations->func[i].rev;
		dr->func[i].prog_पूर्णांकf = relations->func[i].prog_पूर्णांकf;
		dr->func[i].subclass = relations->func[i].subclass;
		dr->func[i].base_class = relations->func[i].base_class;
		dr->func[i].subप्रणाली_id = relations->func[i].subप्रणाली_id;
		dr->func[i].win_slot = relations->func[i].win_slot;
		dr->func[i].ser = relations->func[i].ser;
		dr->func[i].flags = relations->func[i].flags;
		dr->func[i].भव_numa_node =
			relations->func[i].भव_numa_node;
	पूर्ण

	अगर (hv_pci_start_relations_work(hbus, dr))
		kमुक्त(dr);
पूर्ण

/**
 * hv_eject_device_work() - Asynchronously handles ejection
 * @work:	Work काष्ठा embedded in पूर्णांकernal device काष्ठा
 *
 * This function handles ejecting a device.  Winकरोws will
 * attempt to gracefully eject a device, रुकोing 60 seconds to
 * hear back from the guest OS that this completed successfully.
 * If this समयr expires, the device will be क्रमcibly हटाओd.
 */
अटल व्योम hv_eject_device_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pci_eject_response *ejct_pkt;
	काष्ठा hv_pcibus_device *hbus;
	काष्ठा hv_pci_dev *hpdev;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक wslot;
	काष्ठा अणु
		काष्ठा pci_packet pkt;
		u8 buffer[माप(काष्ठा pci_eject_response)];
	पूर्ण ctxt;

	hpdev = container_of(work, काष्ठा hv_pci_dev, wrk);
	hbus = hpdev->hbus;

	WARN_ON(hpdev->state != hv_pcichild_ejecting);

	/*
	 * Ejection can come beक्रमe or after the PCI bus has been set up, so
	 * attempt to find it and tear करोwn the bus state, अगर it exists.  This
	 * must be करोne without स्थिरructs like pci_करोमुख्य_nr(hbus->pci_bus)
	 * because hbus->pci_bus may not exist yet.
	 */
	wslot = wslot_to_devfn(hpdev->desc.win_slot.slot);
	pdev = pci_get_करोमुख्य_bus_and_slot(hbus->sysdata.करोमुख्य, 0, wslot);
	अगर (pdev) अणु
		pci_lock_rescan_हटाओ();
		pci_stop_and_हटाओ_bus_device(pdev);
		pci_dev_put(pdev);
		pci_unlock_rescan_हटाओ();
	पूर्ण

	spin_lock_irqsave(&hbus->device_list_lock, flags);
	list_del(&hpdev->list_entry);
	spin_unlock_irqrestore(&hbus->device_list_lock, flags);

	अगर (hpdev->pci_slot)
		pci_destroy_slot(hpdev->pci_slot);

	स_रखो(&ctxt, 0, माप(ctxt));
	ejct_pkt = (काष्ठा pci_eject_response *)&ctxt.pkt.message;
	ejct_pkt->message_type.type = PCI_EJECTION_COMPLETE;
	ejct_pkt->wslot.slot = hpdev->desc.win_slot.slot;
	vmbus_sendpacket(hbus->hdev->channel, ejct_pkt,
			 माप(*ejct_pkt), (अचिन्हित दीर्घ)&ctxt.pkt,
			 VM_PKT_DATA_INBAND, 0);

	/* For the get_pcichild() in hv_pci_eject_device() */
	put_pcichild(hpdev);
	/* For the two refs got in new_pcichild_device() */
	put_pcichild(hpdev);
	put_pcichild(hpdev);
	/* hpdev has been मुक्तd. Do not use it any more. */

	put_hvpcibus(hbus);
पूर्ण

/**
 * hv_pci_eject_device() - Handles device ejection
 * @hpdev:	Internal device tracking काष्ठा
 *
 * This function is invoked when an ejection packet arrives.  It
 * just schedules work so that we करोn't re-enter the packet
 * delivery code handling the ejection.
 */
अटल व्योम hv_pci_eject_device(काष्ठा hv_pci_dev *hpdev)
अणु
	काष्ठा hv_pcibus_device *hbus = hpdev->hbus;
	काष्ठा hv_device *hdev = hbus->hdev;

	अगर (hbus->state == hv_pcibus_removing) अणु
		dev_info(&hdev->device, "PCI VMBus EJECT: ignored\n");
		वापस;
	पूर्ण

	hpdev->state = hv_pcichild_ejecting;
	get_pcichild(hpdev);
	INIT_WORK(&hpdev->wrk, hv_eject_device_work);
	get_hvpcibus(hbus);
	queue_work(hbus->wq, &hpdev->wrk);
पूर्ण

/**
 * hv_pci_onchannelcallback() - Handles incoming packets
 * @context:	Internal bus tracking काष्ठा
 *
 * This function is invoked whenever the host sends a packet to
 * this channel (which is निजी to this root PCI bus).
 */
अटल व्योम hv_pci_onchannelcallback(व्योम *context)
अणु
	स्थिर पूर्णांक packet_size = 0x100;
	पूर्णांक ret;
	काष्ठा hv_pcibus_device *hbus = context;
	u32 bytes_recvd;
	u64 req_id;
	काष्ठा vmpacket_descriptor *desc;
	अचिन्हित अक्षर *buffer;
	पूर्णांक bufferlen = packet_size;
	काष्ठा pci_packet *comp_packet;
	काष्ठा pci_response *response;
	काष्ठा pci_incoming_message *new_message;
	काष्ठा pci_bus_relations *bus_rel;
	काष्ठा pci_bus_relations2 *bus_rel2;
	काष्ठा pci_dev_inval_block *inval;
	काष्ठा pci_dev_incoming *dev_message;
	काष्ठा hv_pci_dev *hpdev;

	buffer = kदो_स्मृति(bufferlen, GFP_ATOMIC);
	अगर (!buffer)
		वापस;

	जबतक (1) अणु
		ret = vmbus_recvpacket_raw(hbus->hdev->channel, buffer,
					   bufferlen, &bytes_recvd, &req_id);

		अगर (ret == -ENOBUFS) अणु
			kमुक्त(buffer);
			/* Handle large packet */
			bufferlen = bytes_recvd;
			buffer = kदो_स्मृति(bytes_recvd, GFP_ATOMIC);
			अगर (!buffer)
				वापस;
			जारी;
		पूर्ण

		/* Zero length indicates there are no more packets. */
		अगर (ret || !bytes_recvd)
			अवरोध;

		/*
		 * All incoming packets must be at least as large as a
		 * response.
		 */
		अगर (bytes_recvd <= माप(काष्ठा pci_response))
			जारी;
		desc = (काष्ठा vmpacket_descriptor *)buffer;

		चयन (desc->type) अणु
		हाल VM_PKT_COMP:

			/*
			 * The host is trusted, and thus it's safe to पूर्णांकerpret
			 * this transaction ID as a poपूर्णांकer.
			 */
			comp_packet = (काष्ठा pci_packet *)req_id;
			response = (काष्ठा pci_response *)buffer;
			comp_packet->completion_func(comp_packet->compl_ctxt,
						     response,
						     bytes_recvd);
			अवरोध;

		हाल VM_PKT_DATA_INBAND:

			new_message = (काष्ठा pci_incoming_message *)buffer;
			चयन (new_message->message_type.type) अणु
			हाल PCI_BUS_RELATIONS:

				bus_rel = (काष्ठा pci_bus_relations *)buffer;
				अगर (bytes_recvd <
					काष्ठा_size(bus_rel, func,
						    bus_rel->device_count)) अणु
					dev_err(&hbus->hdev->device,
						"bus relations too small\n");
					अवरोध;
				पूर्ण

				hv_pci_devices_present(hbus, bus_rel);
				अवरोध;

			हाल PCI_BUS_RELATIONS2:

				bus_rel2 = (काष्ठा pci_bus_relations2 *)buffer;
				अगर (bytes_recvd <
					काष्ठा_size(bus_rel2, func,
						    bus_rel2->device_count)) अणु
					dev_err(&hbus->hdev->device,
						"bus relations v2 too small\n");
					अवरोध;
				पूर्ण

				hv_pci_devices_present2(hbus, bus_rel2);
				अवरोध;

			हाल PCI_EJECT:

				dev_message = (काष्ठा pci_dev_incoming *)buffer;
				hpdev = get_pcichild_wslot(hbus,
						      dev_message->wslot.slot);
				अगर (hpdev) अणु
					hv_pci_eject_device(hpdev);
					put_pcichild(hpdev);
				पूर्ण
				अवरोध;

			हाल PCI_INVALIDATE_BLOCK:

				inval = (काष्ठा pci_dev_inval_block *)buffer;
				hpdev = get_pcichild_wslot(hbus,
							   inval->wslot.slot);
				अगर (hpdev) अणु
					अगर (hpdev->block_invalidate) अणु
						hpdev->block_invalidate(
						    hpdev->invalidate_context,
						    inval->block_mask);
					पूर्ण
					put_pcichild(hpdev);
				पूर्ण
				अवरोध;

			शेष:
				dev_warn(&hbus->hdev->device,
					"Unimplemented protocol message %x\n",
					new_message->message_type.type);
				अवरोध;
			पूर्ण
			अवरोध;

		शेष:
			dev_err(&hbus->hdev->device,
				"unhandled packet type %d, tid %llx len %d\n",
				desc->type, req_id, bytes_recvd);
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(buffer);
पूर्ण

/**
 * hv_pci_protocol_negotiation() - Set up protocol
 * @hdev:		VMBus's tracking काष्ठा क्रम this root PCI bus.
 * @version:		Array of supported channel protocol versions in
 *			the order of probing - highest go first.
 * @num_version:	Number of elements in the version array.
 *
 * This driver is पूर्णांकended to support running on Winकरोws 10
 * (server) and later versions. It will not run on earlier
 * versions, as they assume that many of the operations which
 * Linux needs accomplished with a spinlock held were करोne via
 * asynchronous messaging via VMBus.  Winकरोws 10 increases the
 * surface area of PCI emulation so that these actions can take
 * place by suspending a भव processor क्रम their duration.
 *
 * This function negotiates the channel protocol version,
 * failing अगर the host करोesn't support the necessary protocol
 * level.
 */
अटल पूर्णांक hv_pci_protocol_negotiation(काष्ठा hv_device *hdev,
				       क्रमागत pci_protocol_version_t version[],
				       पूर्णांक num_version)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	काष्ठा pci_version_request *version_req;
	काष्ठा hv_pci_compl comp_pkt;
	काष्ठा pci_packet *pkt;
	पूर्णांक ret;
	पूर्णांक i;

	/*
	 * Initiate the handshake with the host and negotiate
	 * a version that the host can support. We start with the
	 * highest version number and go करोwn अगर the host cannot
	 * support it.
	 */
	pkt = kzalloc(माप(*pkt) + माप(*version_req), GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	init_completion(&comp_pkt.host_event);
	pkt->completion_func = hv_pci_generic_compl;
	pkt->compl_ctxt = &comp_pkt;
	version_req = (काष्ठा pci_version_request *)&pkt->message;
	version_req->message_type.type = PCI_QUERY_PROTOCOL_VERSION;

	क्रम (i = 0; i < num_version; i++) अणु
		version_req->protocol_version = version[i];
		ret = vmbus_sendpacket(hdev->channel, version_req,
				माप(काष्ठा pci_version_request),
				(अचिन्हित दीर्घ)pkt, VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
		अगर (!ret)
			ret = रुको_क्रम_response(hdev, &comp_pkt.host_event);

		अगर (ret) अणु
			dev_err(&hdev->device,
				"PCI Pass-through VSP failed to request version: %d",
				ret);
			जाओ निकास;
		पूर्ण

		अगर (comp_pkt.completion_status >= 0) अणु
			hbus->protocol_version = version[i];
			dev_info(&hdev->device,
				"PCI VMBus probing: Using version %#x\n",
				hbus->protocol_version);
			जाओ निकास;
		पूर्ण

		अगर (comp_pkt.completion_status != STATUS_REVISION_MISMATCH) अणु
			dev_err(&hdev->device,
				"PCI Pass-through VSP failed version request: %#x",
				comp_pkt.completion_status);
			ret = -EPROTO;
			जाओ निकास;
		पूर्ण

		reinit_completion(&comp_pkt.host_event);
	पूर्ण

	dev_err(&hdev->device,
		"PCI pass-through VSP failed to find supported version");
	ret = -EPROTO;

निकास:
	kमुक्त(pkt);
	वापस ret;
पूर्ण

/**
 * hv_pci_मुक्त_bridge_winकरोws() - Release memory regions क्रम the
 * bus
 * @hbus:	Root PCI bus, as understood by this driver
 */
अटल व्योम hv_pci_मुक्त_bridge_winकरोws(काष्ठा hv_pcibus_device *hbus)
अणु
	/*
	 * Set the resources back to the way they looked when they
	 * were allocated by setting IORESOURCE_BUSY again.
	 */

	अगर (hbus->low_mmio_space && hbus->low_mmio_res) अणु
		hbus->low_mmio_res->flags |= IORESOURCE_BUSY;
		vmbus_मुक्त_mmio(hbus->low_mmio_res->start,
				resource_size(hbus->low_mmio_res));
	पूर्ण

	अगर (hbus->high_mmio_space && hbus->high_mmio_res) अणु
		hbus->high_mmio_res->flags |= IORESOURCE_BUSY;
		vmbus_मुक्त_mmio(hbus->high_mmio_res->start,
				resource_size(hbus->high_mmio_res));
	पूर्ण
पूर्ण

/**
 * hv_pci_allocate_bridge_winकरोws() - Allocate memory regions
 * क्रम the bus
 * @hbus:	Root PCI bus, as understood by this driver
 *
 * This function calls vmbus_allocate_mmio(), which is itself a
 * bit of a compromise.  Ideally, we might change the pnp layer
 * in the kernel such that it comprehends either PCI devices
 * which are "grandchildren of ACPI," with some पूर्णांकermediate bus
 * node (in this हाल, VMBus) or change it such that it
 * understands VMBus.  The pnp layer, however, has been declared
 * deprecated, and not subject to change.
 *
 * The workaround, implemented here, is to ask VMBus to allocate
 * MMIO space क्रम this bus.  VMBus itself knows which ranges are
 * appropriate by looking at its own ACPI objects.  Then, after
 * these ranges are claimed, they're modअगरied to look like they
 * would have looked अगर the ACPI and pnp code had allocated
 * bridge winकरोws.  These descriptors have to exist in this क्रमm
 * in order to satisfy the code which will get invoked when the
 * endpoपूर्णांक PCI function driver calls request_mem_region() or
 * request_mem_region_exclusive().
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_pci_allocate_bridge_winकरोws(काष्ठा hv_pcibus_device *hbus)
अणु
	resource_माप_प्रकार align;
	पूर्णांक ret;

	अगर (hbus->low_mmio_space) अणु
		align = 1ULL << (63 - __builtin_clzll(hbus->low_mmio_space));
		ret = vmbus_allocate_mmio(&hbus->low_mmio_res, hbus->hdev, 0,
					  (u64)(u32)0xffffffff,
					  hbus->low_mmio_space,
					  align, false);
		अगर (ret) अणु
			dev_err(&hbus->hdev->device,
				"Need %#llx of low MMIO space. Consider reconfiguring the VM.\n",
				hbus->low_mmio_space);
			वापस ret;
		पूर्ण

		/* Modअगरy this resource to become a bridge winकरोw. */
		hbus->low_mmio_res->flags |= IORESOURCE_WINDOW;
		hbus->low_mmio_res->flags &= ~IORESOURCE_BUSY;
		pci_add_resource(&hbus->resources_क्रम_children,
				 hbus->low_mmio_res);
	पूर्ण

	अगर (hbus->high_mmio_space) अणु
		align = 1ULL << (63 - __builtin_clzll(hbus->high_mmio_space));
		ret = vmbus_allocate_mmio(&hbus->high_mmio_res, hbus->hdev,
					  0x100000000, -1,
					  hbus->high_mmio_space, align,
					  false);
		अगर (ret) अणु
			dev_err(&hbus->hdev->device,
				"Need %#llx of high MMIO space. Consider reconfiguring the VM.\n",
				hbus->high_mmio_space);
			जाओ release_low_mmio;
		पूर्ण

		/* Modअगरy this resource to become a bridge winकरोw. */
		hbus->high_mmio_res->flags |= IORESOURCE_WINDOW;
		hbus->high_mmio_res->flags &= ~IORESOURCE_BUSY;
		pci_add_resource(&hbus->resources_क्रम_children,
				 hbus->high_mmio_res);
	पूर्ण

	वापस 0;

release_low_mmio:
	अगर (hbus->low_mmio_res) अणु
		vmbus_मुक्त_mmio(hbus->low_mmio_res->start,
				resource_size(hbus->low_mmio_res));
	पूर्ण

	वापस ret;
पूर्ण

/**
 * hv_allocate_config_winकरोw() - Find MMIO space क्रम PCI Config
 * @hbus:	Root PCI bus, as understood by this driver
 *
 * This function claims memory-mapped I/O space क्रम accessing
 * configuration space क्रम the functions on this bus.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_allocate_config_winकरोw(काष्ठा hv_pcibus_device *hbus)
अणु
	पूर्णांक ret;

	/*
	 * Set up a region of MMIO space to use क्रम accessing configuration
	 * space.
	 */
	ret = vmbus_allocate_mmio(&hbus->mem_config, hbus->hdev, 0, -1,
				  PCI_CONFIG_MMIO_LENGTH, 0x1000, false);
	अगर (ret)
		वापस ret;

	/*
	 * vmbus_allocate_mmio() माला_लो used क्रम allocating both device endpoपूर्णांक
	 * resource claims (those which cannot be overlapped) and the ranges
	 * which are valid क्रम the children of this bus, which are पूर्णांकended
	 * to be overlapped by those children.  Set the flag on this claim
	 * meaning that this region can't be overlapped.
	 */

	hbus->mem_config->flags |= IORESOURCE_BUSY;

	वापस 0;
पूर्ण

अटल व्योम hv_मुक्त_config_winकरोw(काष्ठा hv_pcibus_device *hbus)
अणु
	vmbus_मुक्त_mmio(hbus->mem_config->start, PCI_CONFIG_MMIO_LENGTH);
पूर्ण

अटल पूर्णांक hv_pci_bus_निकास(काष्ठा hv_device *hdev, bool keep_devs);

/**
 * hv_pci_enter_d0() - Bring the "bus" पूर्णांकo the D0 घातer state
 * @hdev:	VMBus's tracking काष्ठा क्रम this root PCI bus
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_pci_enter_d0(काष्ठा hv_device *hdev)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	काष्ठा pci_bus_d0_entry *d0_entry;
	काष्ठा hv_pci_compl comp_pkt;
	काष्ठा pci_packet *pkt;
	पूर्णांक ret;

	/*
	 * Tell the host that the bus is पढ़ोy to use, and moved पूर्णांकo the
	 * घातered-on state.  This includes telling the host which region
	 * of memory-mapped I/O space has been chosen क्रम configuration space
	 * access.
	 */
	pkt = kzalloc(माप(*pkt) + माप(*d0_entry), GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	init_completion(&comp_pkt.host_event);
	pkt->completion_func = hv_pci_generic_compl;
	pkt->compl_ctxt = &comp_pkt;
	d0_entry = (काष्ठा pci_bus_d0_entry *)&pkt->message;
	d0_entry->message_type.type = PCI_BUS_D0ENTRY;
	d0_entry->mmio_base = hbus->mem_config->start;

	ret = vmbus_sendpacket(hdev->channel, d0_entry, माप(*d0_entry),
			       (अचिन्हित दीर्घ)pkt, VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (!ret)
		ret = रुको_क्रम_response(hdev, &comp_pkt.host_event);

	अगर (ret)
		जाओ निकास;

	अगर (comp_pkt.completion_status < 0) अणु
		dev_err(&hdev->device,
			"PCI Pass-through VSP failed D0 Entry with status %x\n",
			comp_pkt.completion_status);
		ret = -EPROTO;
		जाओ निकास;
	पूर्ण

	ret = 0;

निकास:
	kमुक्त(pkt);
	वापस ret;
पूर्ण

/**
 * hv_pci_query_relations() - Ask host to send list of child
 * devices
 * @hdev:	VMBus's tracking काष्ठा क्रम this root PCI bus
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_pci_query_relations(काष्ठा hv_device *hdev)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	काष्ठा pci_message message;
	काष्ठा completion comp;
	पूर्णांक ret;

	/* Ask the host to send aदीर्घ the list of child devices */
	init_completion(&comp);
	अगर (cmpxchg(&hbus->survey_event, शून्य, &comp))
		वापस -ENOTEMPTY;

	स_रखो(&message, 0, माप(message));
	message.type = PCI_QUERY_BUS_RELATIONS;

	ret = vmbus_sendpacket(hdev->channel, &message, माप(message),
			       0, VM_PKT_DATA_INBAND, 0);
	अगर (!ret)
		ret = रुको_क्रम_response(hdev, &comp);

	वापस ret;
पूर्ण

/**
 * hv_send_resources_allocated() - Report local resource choices
 * @hdev:	VMBus's tracking काष्ठा क्रम this root PCI bus
 *
 * The host OS is expecting to be sent a request as a message
 * which contains all the resources that the device will use.
 * The response contains those same resources, "translated"
 * which is to say, the values which should be used by the
 * hardware, when it delivers an पूर्णांकerrupt.  (MMIO resources are
 * used in local terms.)  This is nice क्रम Winकरोws, and lines up
 * with the FDO/PDO split, which करोesn't exist in Linux.  Linux
 * is deeply expecting to scan an emulated PCI configuration
 * space.  So this message is sent here only to drive the state
 * machine on the host क्रमward.
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_send_resources_allocated(काष्ठा hv_device *hdev)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	काष्ठा pci_resources_asचिन्हित *res_asचिन्हित;
	काष्ठा pci_resources_asचिन्हित2 *res_asचिन्हित2;
	काष्ठा hv_pci_compl comp_pkt;
	काष्ठा hv_pci_dev *hpdev;
	काष्ठा pci_packet *pkt;
	माप_प्रकार size_res;
	पूर्णांक wslot;
	पूर्णांक ret;

	size_res = (hbus->protocol_version < PCI_PROTOCOL_VERSION_1_2)
			? माप(*res_asचिन्हित) : माप(*res_asचिन्हित2);

	pkt = kदो_स्मृति(माप(*pkt) + size_res, GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	ret = 0;

	क्रम (wslot = 0; wslot < 256; wslot++) अणु
		hpdev = get_pcichild_wslot(hbus, wslot);
		अगर (!hpdev)
			जारी;

		स_रखो(pkt, 0, माप(*pkt) + size_res);
		init_completion(&comp_pkt.host_event);
		pkt->completion_func = hv_pci_generic_compl;
		pkt->compl_ctxt = &comp_pkt;

		अगर (hbus->protocol_version < PCI_PROTOCOL_VERSION_1_2) अणु
			res_asचिन्हित =
				(काष्ठा pci_resources_asचिन्हित *)&pkt->message;
			res_asचिन्हित->message_type.type =
				PCI_RESOURCES_ASSIGNED;
			res_asचिन्हित->wslot.slot = hpdev->desc.win_slot.slot;
		पूर्ण अन्यथा अणु
			res_asचिन्हित2 =
				(काष्ठा pci_resources_asचिन्हित2 *)&pkt->message;
			res_asचिन्हित2->message_type.type =
				PCI_RESOURCES_ASSIGNED2;
			res_asचिन्हित2->wslot.slot = hpdev->desc.win_slot.slot;
		पूर्ण
		put_pcichild(hpdev);

		ret = vmbus_sendpacket(hdev->channel, &pkt->message,
				size_res, (अचिन्हित दीर्घ)pkt,
				VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
		अगर (!ret)
			ret = रुको_क्रम_response(hdev, &comp_pkt.host_event);
		अगर (ret)
			अवरोध;

		अगर (comp_pkt.completion_status < 0) अणु
			ret = -EPROTO;
			dev_err(&hdev->device,
				"resource allocated returned 0x%x",
				comp_pkt.completion_status);
			अवरोध;
		पूर्ण

		hbus->wslot_res_allocated = wslot;
	पूर्ण

	kमुक्त(pkt);
	वापस ret;
पूर्ण

/**
 * hv_send_resources_released() - Report local resources
 * released
 * @hdev:	VMBus's tracking काष्ठा क्रम this root PCI bus
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_send_resources_released(काष्ठा hv_device *hdev)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	काष्ठा pci_child_message pkt;
	काष्ठा hv_pci_dev *hpdev;
	पूर्णांक wslot;
	पूर्णांक ret;

	क्रम (wslot = hbus->wslot_res_allocated; wslot >= 0; wslot--) अणु
		hpdev = get_pcichild_wslot(hbus, wslot);
		अगर (!hpdev)
			जारी;

		स_रखो(&pkt, 0, माप(pkt));
		pkt.message_type.type = PCI_RESOURCES_RELEASED;
		pkt.wslot.slot = hpdev->desc.win_slot.slot;

		put_pcichild(hpdev);

		ret = vmbus_sendpacket(hdev->channel, &pkt, माप(pkt), 0,
				       VM_PKT_DATA_INBAND, 0);
		अगर (ret)
			वापस ret;

		hbus->wslot_res_allocated = wslot - 1;
	पूर्ण

	hbus->wslot_res_allocated = -1;

	वापस 0;
पूर्ण

अटल व्योम get_hvpcibus(काष्ठा hv_pcibus_device *hbus)
अणु
	refcount_inc(&hbus->हटाओ_lock);
पूर्ण

अटल व्योम put_hvpcibus(काष्ठा hv_pcibus_device *hbus)
अणु
	अगर (refcount_dec_and_test(&hbus->हटाओ_lock))
		complete(&hbus->हटाओ_event);
पूर्ण

#घोषणा HVPCI_DOM_MAP_SIZE (64 * 1024)
अटल DECLARE_BITMAP(hvpci_करोm_map, HVPCI_DOM_MAP_SIZE);

/*
 * PCI करोमुख्य number 0 is used by emulated devices on Gen1 VMs, so define 0
 * as invalid क्रम passthrough PCI devices of this driver.
 */
#घोषणा HVPCI_DOM_INVALID 0

/**
 * hv_get_करोm_num() - Get a valid PCI करोमुख्य number
 * Check अगर the PCI करोमुख्य number is in use, and वापस another number अगर
 * it is in use.
 *
 * @करोm: Requested करोमुख्य number
 *
 * वापस: करोमुख्य number on success, HVPCI_DOM_INVALID on failure
 */
अटल u16 hv_get_करोm_num(u16 करोm)
अणु
	अचिन्हित पूर्णांक i;

	अगर (test_and_set_bit(करोm, hvpci_करोm_map) == 0)
		वापस करोm;

	क्रम_each_clear_bit(i, hvpci_करोm_map, HVPCI_DOM_MAP_SIZE) अणु
		अगर (test_and_set_bit(i, hvpci_करोm_map) == 0)
			वापस i;
	पूर्ण

	वापस HVPCI_DOM_INVALID;
पूर्ण

/**
 * hv_put_करोm_num() - Mark the PCI करोमुख्य number as मुक्त
 * @करोm: Doमुख्य number to be मुक्तd
 */
अटल व्योम hv_put_करोm_num(u16 करोm)
अणु
	clear_bit(करोm, hvpci_करोm_map);
पूर्ण

/**
 * hv_pci_probe() - New VMBus channel probe, क्रम a root PCI bus
 * @hdev:	VMBus's tracking काष्ठा क्रम this root PCI bus
 * @dev_id:	Identअगरies the device itself
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_pci_probe(काष्ठा hv_device *hdev,
			स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	काष्ठा hv_pcibus_device *hbus;
	u16 करोm_req, करोm;
	अक्षर *name;
	bool enter_d0_retry = true;
	पूर्णांक ret;

	/*
	 * hv_pcibus_device contains the hypercall arguments क्रम retargeting in
	 * hv_irq_unmask(). Those must not cross a page boundary.
	 */
	BUILD_BUG_ON(माप(*hbus) > HV_HYP_PAGE_SIZE);

	/*
	 * With the recent 59bb47985c1d ("mm, sl[aou]b: guarantee natural
	 * alignment क्रम kदो_स्मृति(घातer-of-two)"), kzalloc() is able to allocate
	 * a 4KB buffer that is guaranteed to be 4KB-aligned. Here the size and
	 * alignment of hbus is important because hbus's field
	 * retarget_msi_पूर्णांकerrupt_params must not cross a 4KB page boundary.
	 *
	 * Here we prefer kzalloc to get_zeroed_page(), because a buffer
	 * allocated by the latter is not tracked and scanned by kmemleak, and
	 * hence kmemleak reports the poपूर्णांकer contained in the hbus buffer
	 * (i.e. the hpdev काष्ठा, which is created in new_pcichild_device() and
	 * is tracked by hbus->children) as memory leak (false positive).
	 *
	 * If the kernel करोesn't have 59bb47985c1d, get_zeroed_page() *must* be
	 * used to allocate the hbus buffer and we can aव्योम the kmemleak false
	 * positive by using kmemleak_alloc() and kmemleak_मुक्त() to ask
	 * kmemleak to track and scan the hbus buffer.
	 */
	hbus = kzalloc(HV_HYP_PAGE_SIZE, GFP_KERNEL);
	अगर (!hbus)
		वापस -ENOMEM;
	hbus->state = hv_pcibus_init;
	hbus->wslot_res_allocated = -1;

	/*
	 * The PCI bus "domain" is what is called "segment" in ACPI and other
	 * specs. Pull it from the instance ID, to get something usually
	 * unique. In rare हालs of collision, we will find out another number
	 * not in use.
	 *
	 * Note that, since this code only runs in a Hyper-V VM, Hyper-V
	 * together with this guest driver can guarantee that (1) The only
	 * करोमुख्य used by Gen1 VMs क्रम something that looks like a physical
	 * PCI bus (which is actually emulated by the hypervisor) is करोमुख्य 0.
	 * (2) There will be no overlap between करोमुख्यs (after fixing possible
	 * collisions) in the same VM.
	 */
	करोm_req = hdev->dev_instance.b[5] << 8 | hdev->dev_instance.b[4];
	करोm = hv_get_करोm_num(करोm_req);

	अगर (करोm == HVPCI_DOM_INVALID) अणु
		dev_err(&hdev->device,
			"Unable to use dom# 0x%hx or other numbers", करोm_req);
		ret = -EINVAL;
		जाओ मुक्त_bus;
	पूर्ण

	अगर (करोm != करोm_req)
		dev_info(&hdev->device,
			 "PCI dom# 0x%hx has collision, using 0x%hx",
			 करोm_req, करोm);

	hbus->sysdata.करोमुख्य = करोm;

	hbus->hdev = hdev;
	refcount_set(&hbus->हटाओ_lock, 1);
	INIT_LIST_HEAD(&hbus->children);
	INIT_LIST_HEAD(&hbus->dr_list);
	INIT_LIST_HEAD(&hbus->resources_क्रम_children);
	spin_lock_init(&hbus->config_lock);
	spin_lock_init(&hbus->device_list_lock);
	spin_lock_init(&hbus->retarget_msi_पूर्णांकerrupt_lock);
	init_completion(&hbus->हटाओ_event);
	hbus->wq = alloc_ordered_workqueue("hv_pci_%x", 0,
					   hbus->sysdata.करोमुख्य);
	अगर (!hbus->wq) अणु
		ret = -ENOMEM;
		जाओ मुक्त_करोm;
	पूर्ण

	ret = vmbus_खोलो(hdev->channel, pci_ring_size, pci_ring_size, शून्य, 0,
			 hv_pci_onchannelcallback, hbus);
	अगर (ret)
		जाओ destroy_wq;

	hv_set_drvdata(hdev, hbus);

	ret = hv_pci_protocol_negotiation(hdev, pci_protocol_versions,
					  ARRAY_SIZE(pci_protocol_versions));
	अगर (ret)
		जाओ बंद;

	ret = hv_allocate_config_winकरोw(hbus);
	अगर (ret)
		जाओ बंद;

	hbus->cfg_addr = ioremap(hbus->mem_config->start,
				 PCI_CONFIG_MMIO_LENGTH);
	अगर (!hbus->cfg_addr) अणु
		dev_err(&hdev->device,
			"Unable to map a virtual address for config space\n");
		ret = -ENOMEM;
		जाओ मुक्त_config;
	पूर्ण

	name = kaप्र_लिखो(GFP_KERNEL, "%pUL", &hdev->dev_instance);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ unmap;
	पूर्ण

	hbus->sysdata.fwnode = irq_करोमुख्य_alloc_named_fwnode(name);
	kमुक्त(name);
	अगर (!hbus->sysdata.fwnode) अणु
		ret = -ENOMEM;
		जाओ unmap;
	पूर्ण

	ret = hv_pcie_init_irq_करोमुख्य(hbus);
	अगर (ret)
		जाओ मुक्त_fwnode;

retry:
	ret = hv_pci_query_relations(hdev);
	अगर (ret)
		जाओ मुक्त_irq_करोमुख्य;

	ret = hv_pci_enter_d0(hdev);
	/*
	 * In certain हाल (Kdump) the pci device of पूर्णांकerest was
	 * not cleanly shut करोwn and resource is still held on host
	 * side, the host could वापस invalid device status.
	 * We need to explicitly request host to release the resource
	 * and try to enter D0 again.
	 * Since the hv_pci_bus_निकास() call releases काष्ठाures
	 * of all its child devices, we need to start the retry from
	 * hv_pci_query_relations() call, requesting host to send
	 * the synchronous child device relations message beक्रमe this
	 * inक्रमmation is needed in hv_send_resources_allocated()
	 * call later.
	 */
	अगर (ret == -EPROTO && enter_d0_retry) अणु
		enter_d0_retry = false;

		dev_err(&hdev->device, "Retrying D0 Entry\n");

		/*
		 * Hv_pci_bus_निकास() calls hv_send_resources_released()
		 * to मुक्त up resources of its child devices.
		 * In the kdump kernel we need to set the
		 * wslot_res_allocated to 255 so it scans all child
		 * devices to release resources allocated in the
		 * normal kernel beक्रमe panic happened.
		 */
		hbus->wslot_res_allocated = 255;
		ret = hv_pci_bus_निकास(hdev, true);

		अगर (ret == 0)
			जाओ retry;

		dev_err(&hdev->device,
			"Retrying D0 failed with ret %d\n", ret);
	पूर्ण
	अगर (ret)
		जाओ मुक्त_irq_करोमुख्य;

	ret = hv_pci_allocate_bridge_winकरोws(hbus);
	अगर (ret)
		जाओ निकास_d0;

	ret = hv_send_resources_allocated(hdev);
	अगर (ret)
		जाओ मुक्त_winकरोws;

	prepopulate_bars(hbus);

	hbus->state = hv_pcibus_probed;

	ret = create_root_hv_pci_bus(hbus);
	अगर (ret)
		जाओ मुक्त_winकरोws;

	वापस 0;

मुक्त_winकरोws:
	hv_pci_मुक्त_bridge_winकरोws(hbus);
निकास_d0:
	(व्योम) hv_pci_bus_निकास(hdev, true);
मुक्त_irq_करोमुख्य:
	irq_करोमुख्य_हटाओ(hbus->irq_करोमुख्य);
मुक्त_fwnode:
	irq_करोमुख्य_मुक्त_fwnode(hbus->sysdata.fwnode);
unmap:
	iounmap(hbus->cfg_addr);
मुक्त_config:
	hv_मुक्त_config_winकरोw(hbus);
बंद:
	vmbus_बंद(hdev->channel);
destroy_wq:
	destroy_workqueue(hbus->wq);
मुक्त_करोm:
	hv_put_करोm_num(hbus->sysdata.करोमुख्य);
मुक्त_bus:
	kमुक्त(hbus);
	वापस ret;
पूर्ण

अटल पूर्णांक hv_pci_bus_निकास(काष्ठा hv_device *hdev, bool keep_devs)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	काष्ठा अणु
		काष्ठा pci_packet tearकरोwn_packet;
		u8 buffer[माप(काष्ठा pci_message)];
	पूर्ण pkt;
	काष्ठा hv_dr_state *dr;
	काष्ठा hv_pci_compl comp_pkt;
	पूर्णांक ret;

	/*
	 * After the host sends the RESCIND_CHANNEL message, it करोesn't
	 * access the per-channel ringbuffer any दीर्घer.
	 */
	अगर (hdev->channel->rescind)
		वापस 0;

	अगर (!keep_devs) अणु
		/* Delete any children which might still exist. */
		dr = kzalloc(माप(*dr), GFP_KERNEL);
		अगर (dr && hv_pci_start_relations_work(hbus, dr))
			kमुक्त(dr);
	पूर्ण

	ret = hv_send_resources_released(hdev);
	अगर (ret) अणु
		dev_err(&hdev->device,
			"Couldn't send resources released packet(s)\n");
		वापस ret;
	पूर्ण

	स_रखो(&pkt.tearकरोwn_packet, 0, माप(pkt.tearकरोwn_packet));
	init_completion(&comp_pkt.host_event);
	pkt.tearकरोwn_packet.completion_func = hv_pci_generic_compl;
	pkt.tearकरोwn_packet.compl_ctxt = &comp_pkt;
	pkt.tearकरोwn_packet.message[0].type = PCI_BUS_D0EXIT;

	ret = vmbus_sendpacket(hdev->channel, &pkt.tearकरोwn_packet.message,
			       माप(काष्ठा pci_message),
			       (अचिन्हित दीर्घ)&pkt.tearकरोwn_packet,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret)
		वापस ret;

	अगर (रुको_क्रम_completion_समयout(&comp_pkt.host_event, 10 * HZ) == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/**
 * hv_pci_हटाओ() - Remove routine क्रम this VMBus channel
 * @hdev:	VMBus's tracking काष्ठा क्रम this root PCI bus
 *
 * Return: 0 on success, -त्रुटि_सं on failure
 */
अटल पूर्णांक hv_pci_हटाओ(काष्ठा hv_device *hdev)
अणु
	काष्ठा hv_pcibus_device *hbus;
	पूर्णांक ret;

	hbus = hv_get_drvdata(hdev);
	अगर (hbus->state == hv_pcibus_installed) अणु
		/* Remove the bus from PCI's poपूर्णांक of view. */
		pci_lock_rescan_हटाओ();
		pci_stop_root_bus(hbus->pci_bus);
		hv_pci_हटाओ_slots(hbus);
		pci_हटाओ_root_bus(hbus->pci_bus);
		pci_unlock_rescan_हटाओ();
		hbus->state = hv_pcibus_हटाओd;
	पूर्ण

	ret = hv_pci_bus_निकास(hdev, false);

	vmbus_बंद(hdev->channel);

	iounmap(hbus->cfg_addr);
	hv_मुक्त_config_winकरोw(hbus);
	pci_मुक्त_resource_list(&hbus->resources_क्रम_children);
	hv_pci_मुक्त_bridge_winकरोws(hbus);
	irq_करोमुख्य_हटाओ(hbus->irq_करोमुख्य);
	irq_करोमुख्य_मुक्त_fwnode(hbus->sysdata.fwnode);
	put_hvpcibus(hbus);
	रुको_क्रम_completion(&hbus->हटाओ_event);
	destroy_workqueue(hbus->wq);

	hv_put_करोm_num(hbus->sysdata.करोमुख्य);

	kमुक्त(hbus);
	वापस ret;
पूर्ण

अटल पूर्णांक hv_pci_suspend(काष्ठा hv_device *hdev)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	क्रमागत hv_pcibus_state old_state;
	पूर्णांक ret;

	/*
	 * hv_pci_suspend() must make sure there are no pending work items
	 * beक्रमe calling vmbus_बंद(), since it runs in a process context
	 * as a callback in dpm_suspend().  When it starts to run, the channel
	 * callback hv_pci_onchannelcallback(), which runs in a tasklet
	 * context, can be still running concurrently and scheduling new work
	 * items onto hbus->wq in hv_pci_devices_present() and
	 * hv_pci_eject_device(), and the work item handlers can access the
	 * vmbus channel, which can be being बंदd by hv_pci_suspend(), e.g.
	 * the work item handler pci_devices_present_work() ->
	 * new_pcichild_device() ग_लिखोs to the vmbus channel.
	 *
	 * To eliminate the race, hv_pci_suspend() disables the channel
	 * callback tasklet, sets hbus->state to hv_pcibus_removing, and
	 * re-enables the tasklet. This way, when hv_pci_suspend() proceeds,
	 * it knows that no new work item can be scheduled, and then it flushes
	 * hbus->wq and safely बंदs the vmbus channel.
	 */
	tasklet_disable(&hdev->channel->callback_event);

	/* Change the hbus state to prevent new work items. */
	old_state = hbus->state;
	अगर (hbus->state == hv_pcibus_installed)
		hbus->state = hv_pcibus_removing;

	tasklet_enable(&hdev->channel->callback_event);

	अगर (old_state != hv_pcibus_installed)
		वापस -EINVAL;

	flush_workqueue(hbus->wq);

	ret = hv_pci_bus_निकास(hdev, true);
	अगर (ret)
		वापस ret;

	vmbus_बंद(hdev->channel);

	वापस 0;
पूर्ण

अटल पूर्णांक hv_pci_restore_msi_msg(काष्ठा pci_dev *pdev, व्योम *arg)
अणु
	काष्ठा msi_desc *entry;
	काष्ठा irq_data *irq_data;

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		irq_data = irq_get_irq_data(entry->irq);
		अगर (WARN_ON_ONCE(!irq_data))
			वापस -EINVAL;

		hv_compose_msi_msg(irq_data, &entry->msg);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Upon resume, pci_restore_msi_state() -> ... ->  __pci_ग_लिखो_msi_msg()
 * directly ग_लिखोs the MSI/MSI-X रेजिस्टरs via MMIO, but since Hyper-V
 * करोesn't trap and emulate the MMIO accesses, here hv_compose_msi_msg()
 * must be used to ask Hyper-V to re-create the IOMMU Interrupt Remapping
 * Table entries.
 */
अटल व्योम hv_pci_restore_msi_state(काष्ठा hv_pcibus_device *hbus)
अणु
	pci_walk_bus(hbus->pci_bus, hv_pci_restore_msi_msg, शून्य);
पूर्ण

अटल पूर्णांक hv_pci_resume(काष्ठा hv_device *hdev)
अणु
	काष्ठा hv_pcibus_device *hbus = hv_get_drvdata(hdev);
	क्रमागत pci_protocol_version_t version[1];
	पूर्णांक ret;

	hbus->state = hv_pcibus_init;

	ret = vmbus_खोलो(hdev->channel, pci_ring_size, pci_ring_size, शून्य, 0,
			 hv_pci_onchannelcallback, hbus);
	अगर (ret)
		वापस ret;

	/* Only use the version that was in use beक्रमe hibernation. */
	version[0] = hbus->protocol_version;
	ret = hv_pci_protocol_negotiation(hdev, version, 1);
	अगर (ret)
		जाओ out;

	ret = hv_pci_query_relations(hdev);
	अगर (ret)
		जाओ out;

	ret = hv_pci_enter_d0(hdev);
	अगर (ret)
		जाओ out;

	ret = hv_send_resources_allocated(hdev);
	अगर (ret)
		जाओ out;

	prepopulate_bars(hbus);

	hv_pci_restore_msi_state(hbus);

	hbus->state = hv_pcibus_installed;
	वापस 0;
out:
	vmbus_बंद(hdev->channel);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id hv_pci_id_table[] = अणु
	/* PCI Pass-through Class ID */
	/* 44C4F61D-4444-4400-9D52-802E27EDE19F */
	अणु HV_PCIE_GUID, पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vmbus, hv_pci_id_table);

अटल काष्ठा hv_driver hv_pci_drv = अणु
	.name		= "hv_pci",
	.id_table	= hv_pci_id_table,
	.probe		= hv_pci_probe,
	.हटाओ		= hv_pci_हटाओ,
	.suspend	= hv_pci_suspend,
	.resume		= hv_pci_resume,
पूर्ण;

अटल व्योम __निकास निकास_hv_pci_drv(व्योम)
अणु
	vmbus_driver_unरेजिस्टर(&hv_pci_drv);

	hvpci_block_ops.पढ़ो_block = शून्य;
	hvpci_block_ops.ग_लिखो_block = शून्य;
	hvpci_block_ops.reg_blk_invalidate = शून्य;
पूर्ण

अटल पूर्णांक __init init_hv_pci_drv(व्योम)
अणु
	/* Set the invalid करोमुख्य number's bit, so it will not be used */
	set_bit(HVPCI_DOM_INVALID, hvpci_करोm_map);

	/* Initialize PCI block r/w पूर्णांकerface */
	hvpci_block_ops.पढ़ो_block = hv_पढ़ो_config_block;
	hvpci_block_ops.ग_लिखो_block = hv_ग_लिखो_config_block;
	hvpci_block_ops.reg_blk_invalidate = hv_रेजिस्टर_block_invalidate;

	वापस vmbus_driver_रेजिस्टर(&hv_pci_drv);
पूर्ण

module_init(init_hv_pci_drv);
module_निकास(निकास_hv_pci_drv);

MODULE_DESCRIPTION("Hyper-V PCI");
MODULE_LICENSE("GPL v2");
