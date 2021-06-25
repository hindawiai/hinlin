<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * This file contains definitions from Hyper-V Hypervisor Top-Level Functional
 * Specअगरication (TLFS):
 * https://करोcs.microsoft.com/en-us/भवization/hyper-v-on-winकरोws/reference/tlfs
 */

#अगर_अघोषित _ASM_GENERIC_HYPERV_TLFS_H
#घोषणा _ASM_GENERIC_HYPERV_TLFS_H

#समावेश <linux/types.h>
#समावेश <linux/bits.h>
#समावेश <linux/समय64.h>

/*
 * While not explicitly listed in the TLFS, Hyper-V always runs with a page size
 * of 4096. These definitions are used when communicating with Hyper-V using
 * guest physical pages and guest physical page addresses, since the guest page
 * size may not be 4096 on all architectures.
 */
#घोषणा HV_HYP_PAGE_SHIFT      12
#घोषणा HV_HYP_PAGE_SIZE       BIT(HV_HYP_PAGE_SHIFT)
#घोषणा HV_HYP_PAGE_MASK       (~(HV_HYP_PAGE_SIZE - 1))

/*
 * Hyper-V provides two categories of flags relevant to guest VMs.  The
 * "Features" category indicates specअगरic functionality that is available
 * to guests on this particular instance of Hyper-V. The "Features"
 * are presented in four groups, each of which is 32 bits. The group A
 * and B definitions are common across architectures and are listed here.
 * However, not all flags are relevant on all architectures.
 *
 * Groups C and D vary across architectures and are listed in the
 * architecture specअगरic portion of hyperv-tlfs.h. Some of these flags exist
 * on multiple architectures, but the bit positions are dअगरferent so they
 * cannot appear in the generic portion of hyperv-tlfs.h.
 *
 * The "Enlightenments" category provides recommendations on whether to use
 * specअगरic enlightenments that are available. The Enlighenments are a single
 * group of 32 bits, but they vary across architectures and are listed in
 * the architecture specअगरic portion of hyperv-tlfs.h.
 */

/*
 * Group A Features.
 */

/* VP Runसमय रेजिस्टर available */
#घोषणा HV_MSR_VP_RUNTIME_AVAILABLE		BIT(0)
/* Partition Reference Counter available*/
#घोषणा HV_MSR_TIME_REF_COUNT_AVAILABLE		BIT(1)
/* Basic SynIC रेजिस्टर available */
#घोषणा HV_MSR_SYNIC_AVAILABLE			BIT(2)
/* Synthetic Timer रेजिस्टरs available */
#घोषणा HV_MSR_SYNTIMER_AVAILABLE		BIT(3)
/* Virtual APIC assist and VP assist page रेजिस्टरs available */
#घोषणा HV_MSR_APIC_ACCESS_AVAILABLE		BIT(4)
/* Hypercall and Guest OS ID रेजिस्टरs available*/
#घोषणा HV_MSR_HYPERCALL_AVAILABLE		BIT(5)
/* Access भव processor index रेजिस्टर available*/
#घोषणा HV_MSR_VP_INDEX_AVAILABLE		BIT(6)
/* Virtual प्रणाली reset रेजिस्टर available*/
#घोषणा HV_MSR_RESET_AVAILABLE			BIT(7)
/* Access statistics page रेजिस्टरs available */
#घोषणा HV_MSR_STAT_PAGES_AVAILABLE		BIT(8)
/* Partition reference TSC रेजिस्टर is available */
#घोषणा HV_MSR_REFERENCE_TSC_AVAILABLE		BIT(9)
/* Partition Guest IDLE रेजिस्टर is available */
#घोषणा HV_MSR_GUEST_IDLE_AVAILABLE		BIT(10)
/* Partition local APIC and TSC frequency रेजिस्टरs available */
#घोषणा HV_ACCESS_FREQUENCY_MSRS		BIT(11)
/* AccessReenlightenmentControls privilege */
#घोषणा HV_ACCESS_REENLIGHTENMENT		BIT(13)
/* AccessTscInvariantControls privilege */
#घोषणा HV_ACCESS_TSC_INVARIANT			BIT(15)

/*
 * Group B features.
 */
#घोषणा HV_CREATE_PARTITIONS			BIT(0)
#घोषणा HV_ACCESS_PARTITION_ID			BIT(1)
#घोषणा HV_ACCESS_MEMORY_POOL			BIT(2)
#घोषणा HV_ADJUST_MESSAGE_BUFFERS		BIT(3)
#घोषणा HV_POST_MESSAGES			BIT(4)
#घोषणा HV_SIGNAL_EVENTS			BIT(5)
#घोषणा HV_CREATE_PORT				BIT(6)
#घोषणा HV_CONNECT_PORT				BIT(7)
#घोषणा HV_ACCESS_STATS				BIT(8)
#घोषणा HV_DEBUGGING				BIT(11)
#घोषणा HV_CPU_MANAGEMENT			BIT(12)
#घोषणा HV_ENABLE_EXTENDED_HYPERCALLS		BIT(20)
#घोषणा HV_ISOLATION				BIT(22)

/*
 * TSC page layout.
 */
काष्ठा ms_hyperv_tsc_page अणु
	अस्थिर u32 tsc_sequence;
	u32 reserved1;
	अस्थिर u64 tsc_scale;
	अस्थिर s64 tsc_offset;
पूर्ण __packed;

/*
 * The guest OS needs to रेजिस्टर the guest ID with the hypervisor.
 * The guest ID is a 64 bit entity and the काष्ठाure of this ID is
 * specअगरied in the Hyper-V specअगरication:
 *
 * msdn.microsoft.com/en-us/library/winकरोws/hardware/ff542653%28v=vs.85%29.aspx
 *
 * While the current guideline करोes not specअगरy how Linux guest ID(s)
 * need to be generated, our plan is to publish the guidelines क्रम
 * Linux and other guest operating प्रणालीs that currently are hosted
 * on Hyper-V. The implementation here conक्रमms to this yet
 * unpublished guidelines.
 *
 *
 * Bit(s)
 * 63 - Indicates अगर the OS is Open Source or not; 1 is Open Source
 * 62:56 - Os Type; Linux is 0x100
 * 55:48 - Distro specअगरic identअगरication
 * 47:16 - Linux kernel version number
 * 15:0  - Distro specअगरic identअगरication
 *
 *
 */

#घोषणा HV_LINUX_VENDOR_ID              0x8100

/*
 * Crash notअगरication flags.
 */
#घोषणा HV_CRASH_CTL_CRASH_NOTIFY_MSG		BIT_ULL(62)
#घोषणा HV_CRASH_CTL_CRASH_NOTIFY		BIT_ULL(63)

/* Declare the various hypercall operations. */
#घोषणा HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE	0x0002
#घोषणा HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST	0x0003
#घोषणा HVCALL_NOTIFY_LONG_SPIN_WAIT		0x0008
#घोषणा HVCALL_SEND_IPI				0x000b
#घोषणा HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX	0x0013
#घोषणा HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX	0x0014
#घोषणा HVCALL_SEND_IPI_EX			0x0015
#घोषणा HVCALL_GET_PARTITION_ID			0x0046
#घोषणा HVCALL_DEPOSIT_MEMORY			0x0048
#घोषणा HVCALL_CREATE_VP			0x004e
#घोषणा HVCALL_GET_VP_REGISTERS			0x0050
#घोषणा HVCALL_SET_VP_REGISTERS			0x0051
#घोषणा HVCALL_POST_MESSAGE			0x005c
#घोषणा HVCALL_SIGNAL_EVENT			0x005d
#घोषणा HVCALL_POST_DEBUG_DATA			0x0069
#घोषणा HVCALL_RETRIEVE_DEBUG_DATA		0x006a
#घोषणा HVCALL_RESET_DEBUG_SESSION		0x006b
#घोषणा HVCALL_ADD_LOGICAL_PROCESSOR		0x0076
#घोषणा HVCALL_MAP_DEVICE_INTERRUPT		0x007c
#घोषणा HVCALL_UNMAP_DEVICE_INTERRUPT		0x007d
#घोषणा HVCALL_RETARGET_INTERRUPT		0x007e
#घोषणा HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_SPACE 0x00af
#घोषणा HVCALL_FLUSH_GUEST_PHYSICAL_ADDRESS_LIST 0x00b0

/* Extended hypercalls */
#घोषणा HV_EXT_CALL_QUERY_CAPABILITIES		0x8001
#घोषणा HV_EXT_CALL_MEMORY_HEAT_HINT		0x8003

#घोषणा HV_FLUSH_ALL_PROCESSORS			BIT(0)
#घोषणा HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES	BIT(1)
#घोषणा HV_FLUSH_NON_GLOBAL_MAPPINGS_ONLY	BIT(2)
#घोषणा HV_FLUSH_USE_EXTENDED_RANGE_FORMAT	BIT(3)

/* Extended capability bits */
#घोषणा HV_EXT_CAPABILITY_MEMORY_COLD_DISCARD_HINT BIT(8)

क्रमागत HV_GENERIC_SET_FORMAT अणु
	HV_GENERIC_SET_SPARSE_4K,
	HV_GENERIC_SET_ALL,
पूर्ण;

#घोषणा HV_PARTITION_ID_SELF		((u64)-1)
#घोषणा HV_VP_INDEX_SELF		((u32)-2)

#घोषणा HV_HYPERCALL_RESULT_MASK	GENMASK_ULL(15, 0)
#घोषणा HV_HYPERCALL_FAST_BIT		BIT(16)
#घोषणा HV_HYPERCALL_VARHEAD_OFFSET	17
#घोषणा HV_HYPERCALL_REP_COMP_OFFSET	32
#घोषणा HV_HYPERCALL_REP_COMP_1		BIT_ULL(32)
#घोषणा HV_HYPERCALL_REP_COMP_MASK	GENMASK_ULL(43, 32)
#घोषणा HV_HYPERCALL_REP_START_OFFSET	48
#घोषणा HV_HYPERCALL_REP_START_MASK	GENMASK_ULL(59, 48)

/* hypercall status code */
#घोषणा HV_STATUS_SUCCESS			0
#घोषणा HV_STATUS_INVALID_HYPERCALL_CODE	2
#घोषणा HV_STATUS_INVALID_HYPERCALL_INPUT	3
#घोषणा HV_STATUS_INVALID_ALIGNMENT		4
#घोषणा HV_STATUS_INVALID_PARAMETER		5
#घोषणा HV_STATUS_OPERATION_DENIED		8
#घोषणा HV_STATUS_INSUFFICIENT_MEMORY		11
#घोषणा HV_STATUS_INVALID_PORT_ID		17
#घोषणा HV_STATUS_INVALID_CONNECTION_ID		18
#घोषणा HV_STATUS_INSUFFICIENT_BUFFERS		19

/*
 * The Hyper-V TimeRefCount रेजिस्टर and the TSC
 * page provide a guest VM घड़ी with 100ns tick rate
 */
#घोषणा HV_CLOCK_HZ (NSEC_PER_SEC/100)

/* Define the number of synthetic पूर्णांकerrupt sources. */
#घोषणा HV_SYNIC_SINT_COUNT		(16)
/* Define the expected SynIC version. */
#घोषणा HV_SYNIC_VERSION_1		(0x1)
/* Valid SynIC vectors are 16-255. */
#घोषणा HV_SYNIC_FIRST_VALID_VECTOR	(16)

#घोषणा HV_SYNIC_CONTROL_ENABLE		(1ULL << 0)
#घोषणा HV_SYNIC_SIMP_ENABLE		(1ULL << 0)
#घोषणा HV_SYNIC_SIEFP_ENABLE		(1ULL << 0)
#घोषणा HV_SYNIC_SINT_MASKED		(1ULL << 16)
#घोषणा HV_SYNIC_SINT_AUTO_EOI		(1ULL << 17)
#घोषणा HV_SYNIC_SINT_VECTOR_MASK	(0xFF)

#घोषणा HV_SYNIC_STIMER_COUNT		(4)

/* Define synthetic पूर्णांकerrupt controller message स्थिरants. */
#घोषणा HV_MESSAGE_SIZE			(256)
#घोषणा HV_MESSAGE_PAYLOAD_BYTE_COUNT	(240)
#घोषणा HV_MESSAGE_PAYLOAD_QWORD_COUNT	(30)

/*
 * Define hypervisor message types. Some of the message types
 * are x86/x64 specअगरic, but there's no good way to separate
 * them out पूर्णांकo the arch-specअगरic version of hyperv-tlfs.h
 * because C करोesn't provide a way to extend क्रमागत types.
 * Keeping them all in the arch neutral hyperv-tlfs.h seems
 * the least messy compromise.
 */
क्रमागत hv_message_type अणु
	HVMSG_NONE			= 0x00000000,

	/* Memory access messages. */
	HVMSG_UNMAPPED_GPA		= 0x80000000,
	HVMSG_GPA_INTERCEPT		= 0x80000001,

	/* Timer notअगरication messages. */
	HVMSG_TIMER_EXPIRED		= 0x80000010,

	/* Error messages. */
	HVMSG_INVALID_VP_REGISTER_VALUE	= 0x80000020,
	HVMSG_UNRECOVERABLE_EXCEPTION	= 0x80000021,
	HVMSG_UNSUPPORTED_FEATURE	= 0x80000022,

	/* Trace buffer complete messages. */
	HVMSG_EVENTLOG_BUFFERCOMPLETE	= 0x80000040,

	/* Platक्रमm-specअगरic processor पूर्णांकercept messages. */
	HVMSG_X64_IOPORT_INTERCEPT	= 0x80010000,
	HVMSG_X64_MSR_INTERCEPT		= 0x80010001,
	HVMSG_X64_CPUID_INTERCEPT	= 0x80010002,
	HVMSG_X64_EXCEPTION_INTERCEPT	= 0x80010003,
	HVMSG_X64_APIC_EOI		= 0x80010004,
	HVMSG_X64_LEGACY_FP_ERROR	= 0x80010005
पूर्ण;

/* Define synthetic पूर्णांकerrupt controller message flags. */
जोड़ hv_message_flags अणु
	__u8 asu8;
	काष्ठा अणु
		__u8 msg_pending:1;
		__u8 reserved:7;
	पूर्ण __packed;
पूर्ण;

/* Define port identअगरier type. */
जोड़ hv_port_id अणु
	__u32 asu32;
	काष्ठा अणु
		__u32 id:24;
		__u32 reserved:8;
	पूर्ण __packed u;
पूर्ण;

/* Define synthetic पूर्णांकerrupt controller message header. */
काष्ठा hv_message_header अणु
	__u32 message_type;
	__u8 payload_size;
	जोड़ hv_message_flags message_flags;
	__u8 reserved[2];
	जोड़ अणु
		__u64 sender;
		जोड़ hv_port_id port;
	पूर्ण;
पूर्ण __packed;

/* Define synthetic पूर्णांकerrupt controller message क्रमmat. */
काष्ठा hv_message अणु
	काष्ठा hv_message_header header;
	जोड़ अणु
		__u64 payload[HV_MESSAGE_PAYLOAD_QWORD_COUNT];
	पूर्ण u;
पूर्ण __packed;

/* Define the synthetic पूर्णांकerrupt message page layout. */
काष्ठा hv_message_page अणु
	काष्ठा hv_message sपूर्णांक_message[HV_SYNIC_SINT_COUNT];
पूर्ण __packed;

/* Define समयr message payload काष्ठाure. */
काष्ठा hv_समयr_message_payload अणु
	__u32 समयr_index;
	__u32 reserved;
	__u64 expiration_समय;	/* When the समयr expired */
	__u64 delivery_समय;	/* When the message was delivered */
पूर्ण __packed;


/* Define synthetic पूर्णांकerrupt controller flag स्थिरants. */
#घोषणा HV_EVENT_FLAGS_COUNT		(256 * 8)
#घोषणा HV_EVENT_FLAGS_LONG_COUNT	(256 / माप(अचिन्हित दीर्घ))

/*
 * Synthetic समयr configuration.
 */
जोड़ hv_sसमयr_config अणु
	u64 as_uपूर्णांक64;
	काष्ठा अणु
		u64 enable:1;
		u64 periodic:1;
		u64 lazy:1;
		u64 स्वतः_enable:1;
		u64 apic_vector:8;
		u64 direct_mode:1;
		u64 reserved_z0:3;
		u64 sपूर्णांकx:4;
		u64 reserved_z1:44;
	पूर्ण __packed;
पूर्ण;


/* Define the synthetic पूर्णांकerrupt controller event flags क्रमmat. */
जोड़ hv_synic_event_flags अणु
	अचिन्हित दीर्घ flags[HV_EVENT_FLAGS_LONG_COUNT];
पूर्ण;

/* Define SynIC control रेजिस्टर. */
जोड़ hv_synic_scontrol अणु
	u64 as_uपूर्णांक64;
	काष्ठा अणु
		u64 enable:1;
		u64 reserved:63;
	पूर्ण __packed;
पूर्ण;

/* Define synthetic पूर्णांकerrupt source. */
जोड़ hv_synic_sपूर्णांक अणु
	u64 as_uपूर्णांक64;
	काष्ठा अणु
		u64 vector:8;
		u64 reserved1:8;
		u64 masked:1;
		u64 स्वतः_eoi:1;
		u64 polling:1;
		u64 reserved2:45;
	पूर्ण __packed;
पूर्ण;

/* Define the क्रमmat of the SIMP रेजिस्टर */
जोड़ hv_synic_simp अणु
	u64 as_uपूर्णांक64;
	काष्ठा अणु
		u64 simp_enabled:1;
		u64 preserved:11;
		u64 base_simp_gpa:52;
	पूर्ण __packed;
पूर्ण;

/* Define the क्रमmat of the SIEFP रेजिस्टर */
जोड़ hv_synic_siefp अणु
	u64 as_uपूर्णांक64;
	काष्ठा अणु
		u64 siefp_enabled:1;
		u64 preserved:11;
		u64 base_siefp_gpa:52;
	पूर्ण __packed;
पूर्ण;

काष्ठा hv_vpset अणु
	u64 क्रमmat;
	u64 valid_bank_mask;
	u64 bank_contents[];
पूर्ण __packed;

/* HvCallSendSyntheticClusterIpi hypercall */
काष्ठा hv_send_ipi अणु
	u32 vector;
	u32 reserved;
	u64 cpu_mask;
पूर्ण __packed;

/* HvCallSendSyntheticClusterIpiEx hypercall */
काष्ठा hv_send_ipi_ex अणु
	u32 vector;
	u32 reserved;
	काष्ठा hv_vpset vp_set;
पूर्ण __packed;

/* HvFlushGuestPhysicalAddressSpace hypercalls */
काष्ठा hv_guest_mapping_flush अणु
	u64 address_space;
	u64 flags;
पूर्ण __packed;

/*
 *  HV_MAX_FLUSH_PAGES = "additional_pages" + 1. It's limited
 *  by the bitwidth of "additional_pages" in जोड़ hv_gpa_page_range.
 */
#घोषणा HV_MAX_FLUSH_PAGES (2048)
#घोषणा HV_GPA_PAGE_RANGE_PAGE_SIZE_2MB		0
#घोषणा HV_GPA_PAGE_RANGE_PAGE_SIZE_1GB		1

/* HvFlushGuestPhysicalAddressList, HvExtCallMemoryHeatHपूर्णांक hypercall */
जोड़ hv_gpa_page_range अणु
	u64 address_space;
	काष्ठा अणु
		u64 additional_pages:11;
		u64 largepage:1;
		u64 basepfn:52;
	पूर्ण page;
	काष्ठा अणु
		u64 reserved:12;
		u64 page_size:1;
		u64 reserved1:8;
		u64 base_large_pfn:43;
	पूर्ण;
पूर्ण;

/*
 * All input flush parameters should be in single page. The max flush
 * count is equal with how many entries of जोड़ hv_gpa_page_range can
 * be populated पूर्णांकo the input parameter page.
 */
#घोषणा HV_MAX_FLUSH_REP_COUNT ((HV_HYP_PAGE_SIZE - 2 * माप(u64)) /	\
				माप(जोड़ hv_gpa_page_range))

काष्ठा hv_guest_mapping_flush_list अणु
	u64 address_space;
	u64 flags;
	जोड़ hv_gpa_page_range gpa_list[HV_MAX_FLUSH_REP_COUNT];
पूर्ण;

/* HvFlushVirtualAddressSpace, HvFlushVirtualAddressList hypercalls */
काष्ठा hv_tlb_flush अणु
	u64 address_space;
	u64 flags;
	u64 processor_mask;
	u64 gबहु_सूची[];
पूर्ण __packed;

/* HvFlushVirtualAddressSpaceEx, HvFlushVirtualAddressListEx hypercalls */
काष्ठा hv_tlb_flush_ex अणु
	u64 address_space;
	u64 flags;
	काष्ठा hv_vpset hv_vp_set;
	u64 gबहु_सूची[];
पूर्ण __packed;

/* HvGetPartitionId hypercall (output only) */
काष्ठा hv_get_partition_id अणु
	u64 partition_id;
पूर्ण __packed;

/* HvDepositMemory hypercall */
काष्ठा hv_deposit_memory अणु
	u64 partition_id;
	u64 gpa_page_list[];
पूर्ण __packed;

काष्ठा hv_proximity_करोमुख्य_flags अणु
	u32 proximity_preferred : 1;
	u32 reserved : 30;
	u32 proximity_info_valid : 1;
पूर्ण __packed;

/* Not a जोड़ in winकरोws but useful क्रम zeroing */
जोड़ hv_proximity_करोमुख्य_info अणु
	काष्ठा अणु
		u32 करोमुख्य_id;
		काष्ठा hv_proximity_करोमुख्य_flags flags;
	पूर्ण;
	u64 as_uपूर्णांक64;
पूर्ण __packed;

काष्ठा hv_lp_startup_status अणु
	u64 hv_status;
	u64 substatus1;
	u64 substatus2;
	u64 substatus3;
	u64 substatus4;
	u64 substatus5;
	u64 substatus6;
पूर्ण __packed;

/* HvAddLogicalProcessor hypercall */
काष्ठा hv_add_logical_processor_in अणु
	u32 lp_index;
	u32 apic_id;
	जोड़ hv_proximity_करोमुख्य_info proximity_करोमुख्य_info;
	u64 flags;
पूर्ण __packed;

काष्ठा hv_add_logical_processor_out अणु
	काष्ठा hv_lp_startup_status startup_status;
पूर्ण __packed;

क्रमागत HV_SUBNODE_TYPE
अणु
    HvSubnodeAny = 0,
    HvSubnodeSocket = 1,
    HvSubnodeAmdNode = 2,
    HvSubnodeL3 = 3,
    HvSubnodeCount = 4,
    HvSubnodeInvalid = -1
पूर्ण;

/* HvCreateVp hypercall */
काष्ठा hv_create_vp अणु
	u64 partition_id;
	u32 vp_index;
	u8 padding[3];
	u8 subnode_type;
	u64 subnode_id;
	जोड़ hv_proximity_करोमुख्य_info proximity_करोमुख्य_info;
	u64 flags;
पूर्ण __packed;

क्रमागत hv_पूर्णांकerrupt_source अणु
	HV_INTERRUPT_SOURCE_MSI = 1, /* MSI and MSI-X */
	HV_INTERRUPT_SOURCE_IOAPIC,
पूर्ण;

जोड़ hv_msi_address_रेजिस्टर अणु
	u32 as_uपूर्णांक32;
	काष्ठा अणु
		u32 reserved1:2;
		u32 destination_mode:1;
		u32 redirection_hपूर्णांक:1;
		u32 reserved2:8;
		u32 destination_id:8;
		u32 msi_base:12;
	पूर्ण;
पूर्ण __packed;

जोड़ hv_msi_data_रेजिस्टर अणु
	u32 as_uपूर्णांक32;
	काष्ठा अणु
		u32 vector:8;
		u32 delivery_mode:3;
		u32 reserved1:3;
		u32 level_निश्चित:1;
		u32 trigger_mode:1;
		u32 reserved2:16;
	पूर्ण;
पूर्ण __packed;

/* HvRetargetDeviceInterrupt hypercall */
जोड़ hv_msi_entry अणु
	u64 as_uपूर्णांक64;
	काष्ठा अणु
		जोड़ hv_msi_address_रेजिस्टर address;
		जोड़ hv_msi_data_रेजिस्टर data;
	पूर्ण __packed;
पूर्ण;

जोड़ hv_ioapic_rte अणु
	u64 as_uपूर्णांक64;

	काष्ठा अणु
		u32 vector:8;
		u32 delivery_mode:3;
		u32 destination_mode:1;
		u32 delivery_status:1;
		u32 पूर्णांकerrupt_polarity:1;
		u32 remote_irr:1;
		u32 trigger_mode:1;
		u32 पूर्णांकerrupt_mask:1;
		u32 reserved1:15;

		u32 reserved2:24;
		u32 destination_id:8;
	पूर्ण;

	काष्ठा अणु
		u32 low_uपूर्णांक32;
		u32 high_uपूर्णांक32;
	पूर्ण;
पूर्ण __packed;

काष्ठा hv_पूर्णांकerrupt_entry अणु
	u32 source;
	u32 reserved1;
	जोड़ अणु
		जोड़ hv_msi_entry msi_entry;
		जोड़ hv_ioapic_rte ioapic_rte;
	पूर्ण;
पूर्ण __packed;

/*
 * flags क्रम hv_device_पूर्णांकerrupt_target.flags
 */
#घोषणा HV_DEVICE_INTERRUPT_TARGET_MULTICAST		1
#घोषणा HV_DEVICE_INTERRUPT_TARGET_PROCESSOR_SET	2

काष्ठा hv_device_पूर्णांकerrupt_target अणु
	u32 vector;
	u32 flags;
	जोड़ अणु
		u64 vp_mask;
		काष्ठा hv_vpset vp_set;
	पूर्ण;
पूर्ण __packed;

काष्ठा hv_retarget_device_पूर्णांकerrupt अणु
	u64 partition_id;		/* use "self" */
	u64 device_id;
	काष्ठा hv_पूर्णांकerrupt_entry पूर्णांक_entry;
	u64 reserved2;
	काष्ठा hv_device_पूर्णांकerrupt_target पूर्णांक_target;
पूर्ण __packed __aligned(8);


/* HvGetVpRegisters hypercall input with variable size reg name list*/
काष्ठा hv_get_vp_रेजिस्टरs_input अणु
	काष्ठा अणु
		u64 partitionid;
		u32 vpindex;
		u8  inputvtl;
		u8  padding[3];
	पूर्ण header;
	काष्ठा input अणु
		u32 name0;
		u32 name1;
	पूर्ण element[];
पूर्ण __packed;


/* HvGetVpRegisters वापसs an array of these output elements */
काष्ठा hv_get_vp_रेजिस्टरs_output अणु
	जोड़ अणु
		काष्ठा अणु
			u32 a;
			u32 b;
			u32 c;
			u32 d;
		पूर्ण as32 __packed;
		काष्ठा अणु
			u64 low;
			u64 high;
		पूर्ण as64 __packed;
	पूर्ण;
पूर्ण;

/* HvSetVpRegisters hypercall with variable size reg name/value list*/
काष्ठा hv_set_vp_रेजिस्टरs_input अणु
	काष्ठा अणु
		u64 partitionid;
		u32 vpindex;
		u8  inputvtl;
		u8  padding[3];
	पूर्ण header;
	काष्ठा अणु
		u32 name;
		u32 padding1;
		u64 padding2;
		u64 valuelow;
		u64 valuehigh;
	पूर्ण element[];
पूर्ण __packed;

क्रमागत hv_device_type अणु
	HV_DEVICE_TYPE_LOGICAL = 0,
	HV_DEVICE_TYPE_PCI = 1,
	HV_DEVICE_TYPE_IOAPIC = 2,
	HV_DEVICE_TYPE_ACPI = 3,
पूर्ण;

प्रकार u16 hv_pci_rid;
प्रकार u16 hv_pci_segment;
प्रकार u64 hv_logical_device_id;
जोड़ hv_pci_bdf अणु
	u16 as_uपूर्णांक16;

	काष्ठा अणु
		u8 function:3;
		u8 device:5;
		u8 bus;
	पूर्ण;
पूर्ण __packed;

जोड़ hv_pci_bus_range अणु
	u16 as_uपूर्णांक16;

	काष्ठा अणु
		u8 subordinate_bus;
		u8 secondary_bus;
	पूर्ण;
पूर्ण __packed;

जोड़ hv_device_id अणु
	u64 as_uपूर्णांक64;

	काष्ठा अणु
		u64 reserved0:62;
		u64 device_type:2;
	पूर्ण;

	/* HV_DEVICE_TYPE_LOGICAL */
	काष्ठा अणु
		u64 id:62;
		u64 device_type:2;
	पूर्ण logical;

	/* HV_DEVICE_TYPE_PCI */
	काष्ठा अणु
		जोड़ अणु
			hv_pci_rid rid;
			जोड़ hv_pci_bdf bdf;
		पूर्ण;

		hv_pci_segment segment;
		जोड़ hv_pci_bus_range shaकरोw_bus_range;

		u16 phantom_function_bits:2;
		u16 source_shaकरोw:1;

		u16 rsvdz0:11;
		u16 device_type:2;
	पूर्ण pci;

	/* HV_DEVICE_TYPE_IOAPIC */
	काष्ठा अणु
		u8 ioapic_id;
		u8 rsvdz0;
		u16 rsvdz1;
		u16 rsvdz2;

		u16 rsvdz3:14;
		u16 device_type:2;
	पूर्ण ioapic;

	/* HV_DEVICE_TYPE_ACPI */
	काष्ठा अणु
		u32 input_mapping_base;
		u32 input_mapping_count:30;
		u32 device_type:2;
	पूर्ण acpi;
पूर्ण __packed;

क्रमागत hv_पूर्णांकerrupt_trigger_mode अणु
	HV_INTERRUPT_TRIGGER_MODE_EDGE = 0,
	HV_INTERRUPT_TRIGGER_MODE_LEVEL = 1,
पूर्ण;

काष्ठा hv_device_पूर्णांकerrupt_descriptor अणु
	u32 पूर्णांकerrupt_type;
	u32 trigger_mode;
	u32 vector_count;
	u32 reserved;
	काष्ठा hv_device_पूर्णांकerrupt_target target;
पूर्ण __packed;

काष्ठा hv_input_map_device_पूर्णांकerrupt अणु
	u64 partition_id;
	u64 device_id;
	u64 flags;
	काष्ठा hv_पूर्णांकerrupt_entry logical_पूर्णांकerrupt_entry;
	काष्ठा hv_device_पूर्णांकerrupt_descriptor पूर्णांकerrupt_descriptor;
पूर्ण __packed;

काष्ठा hv_output_map_device_पूर्णांकerrupt अणु
	काष्ठा hv_पूर्णांकerrupt_entry पूर्णांकerrupt_entry;
पूर्ण __packed;

काष्ठा hv_input_unmap_device_पूर्णांकerrupt अणु
	u64 partition_id;
	u64 device_id;
	काष्ठा hv_पूर्णांकerrupt_entry पूर्णांकerrupt_entry;
पूर्ण __packed;

#घोषणा HV_SOURCE_SHADOW_NONE               0x0
#घोषणा HV_SOURCE_SHADOW_BRIDGE_BUS_RANGE   0x1

/*
 * The whole argument should fit in a page to be able to pass to the hypervisor
 * in one hypercall.
 */
#घोषणा HV_MEMORY_Hपूर्णांक_उच्च_GPA_PAGE_RANGES  \
	((HV_HYP_PAGE_SIZE - माप(काष्ठा hv_memory_hपूर्णांक)) / \
		माप(जोड़ hv_gpa_page_range))

/* HvExtCallMemoryHeatHपूर्णांक hypercall */
#घोषणा HV_EXT_MEMORY_HEAT_HINT_TYPE_COLD_DISCARD	2
काष्ठा hv_memory_hपूर्णांक अणु
	u64 type:2;
	u64 reserved:62;
	जोड़ hv_gpa_page_range ranges[];
पूर्ण __packed;

#पूर्ण_अगर
