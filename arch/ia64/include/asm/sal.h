<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_SAL_H
#घोषणा _ASM_IA64_SAL_H

/*
 * System Abstraction Layer definitions.
 *
 * This is based on version 2.5 of the manual "IA-64 System
 * Abstraction Layer".
 *
 * Copyright (C) 2001 Intel
 * Copyright (C) 2002 Jenna Hall <jenna.s.hall@पूर्णांकel.com>
 * Copyright (C) 2001 Fred Lewis <frederick.v.lewis@पूर्णांकel.com>
 * Copyright (C) 1998, 1999, 2001, 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 Srinivasa Prasad Thirumalaअक्षर <sprasad@sprasad.engr.sgi.com>
 *
 * 02/01/04 J. Hall Updated Error Record Structures to conक्रमm to July 2001
 *		    revision of the SAL spec.
 * 01/01/03 fvlewis Updated Error Record Structures to conक्रमm with Nov. 2000
 *                  revision of the SAL spec.
 * 99/09/29 davidm	Updated क्रम SAL 2.6.
 * 00/03/29 cfleck      Updated SAL Error Logging info क्रम processor (SAL 2.6)
 *                      (plus examples of platक्रमm error info काष्ठाures from smariset @ Intel)
 */

#घोषणा IA64_SAL_PLATFORM_FEATURE_BUS_LOCK_BIT		0
#घोषणा IA64_SAL_PLATFORM_FEATURE_IRQ_REसूची_HINT_BIT	1
#घोषणा IA64_SAL_PLATFORM_FEATURE_IPI_REसूची_HINT_BIT	2
#घोषणा IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT_BIT	 	3

#घोषणा IA64_SAL_PLATFORM_FEATURE_BUS_LOCK	  (1<<IA64_SAL_PLATFORM_FEATURE_BUS_LOCK_BIT)
#घोषणा IA64_SAL_PLATFORM_FEATURE_IRQ_REसूची_HINT (1<<IA64_SAL_PLATFORM_FEATURE_IRQ_REसूची_HINT_BIT)
#घोषणा IA64_SAL_PLATFORM_FEATURE_IPI_REसूची_HINT (1<<IA64_SAL_PLATFORM_FEATURE_IPI_REसूची_HINT_BIT)
#घोषणा IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT	  (1<<IA64_SAL_PLATFORM_FEATURE_ITC_DRIFT_BIT)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/bcd.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/efi.h>

#समावेश <यंत्र/pal.h>
#समावेश <यंत्र/fpu.h>

बाह्य अचिन्हित दीर्घ sal_systab_phys;
बाह्य spinlock_t sal_lock;

/* SAL spec _requires_ eight args क्रम each call. */
#घोषणा __IA64_FW_CALL(entry,result,a0,a1,a2,a3,a4,a5,a6,a7)	\
	result = (*entry)(a0,a1,a2,a3,a4,a5,a6,a7)

# define IA64_FW_CALL(entry,result,args...) करो अणु		\
	अचिन्हित दीर्घ __ia64_sc_flags;				\
	काष्ठा ia64_fpreg __ia64_sc_fr[6];			\
	ia64_save_scratch_fpregs(__ia64_sc_fr);			\
	spin_lock_irqsave(&sal_lock, __ia64_sc_flags);		\
	__IA64_FW_CALL(entry, result, args);			\
	spin_unlock_irqrestore(&sal_lock, __ia64_sc_flags);	\
	ia64_load_scratch_fpregs(__ia64_sc_fr);			\
पूर्ण जबतक (0)

# define SAL_CALL(result,args...)			\
	IA64_FW_CALL(ia64_sal, result, args);

# define SAL_CALL_NOLOCK(result,args...) करो अणु		\
	अचिन्हित दीर्घ __ia64_scn_flags;			\
	काष्ठा ia64_fpreg __ia64_scn_fr[6];		\
	ia64_save_scratch_fpregs(__ia64_scn_fr);	\
	local_irq_save(__ia64_scn_flags);		\
	__IA64_FW_CALL(ia64_sal, result, args);		\
	local_irq_restore(__ia64_scn_flags);		\
	ia64_load_scratch_fpregs(__ia64_scn_fr);	\
पूर्ण जबतक (0)

# define SAL_CALL_REENTRANT(result,args...) करो अणु	\
	काष्ठा ia64_fpreg __ia64_scs_fr[6];		\
	ia64_save_scratch_fpregs(__ia64_scs_fr);	\
	preempt_disable();				\
	__IA64_FW_CALL(ia64_sal, result, args);		\
	preempt_enable();				\
	ia64_load_scratch_fpregs(__ia64_scs_fr);	\
पूर्ण जबतक (0)

#घोषणा SAL_SET_VECTORS			0x01000000
#घोषणा SAL_GET_STATE_INFO		0x01000001
#घोषणा SAL_GET_STATE_INFO_SIZE		0x01000002
#घोषणा SAL_CLEAR_STATE_INFO		0x01000003
#घोषणा SAL_MC_RENDEZ			0x01000004
#घोषणा SAL_MC_SET_PARAMS		0x01000005
#घोषणा SAL_REGISTER_PHYSICAL_ADDR	0x01000006

#घोषणा SAL_CACHE_FLUSH			0x01000008
#घोषणा SAL_CACHE_INIT			0x01000009
#घोषणा SAL_PCI_CONFIG_READ		0x01000010
#घोषणा SAL_PCI_CONFIG_WRITE		0x01000011
#घोषणा SAL_FREQ_BASE			0x01000012
#घोषणा SAL_PHYSICAL_ID_INFO		0x01000013

#घोषणा SAL_UPDATE_PAL			0x01000020

काष्ठा ia64_sal_retval अणु
	/*
	 * A zero status value indicates call completed without error.
	 * A negative status value indicates reason of call failure.
	 * A positive status value indicates success but an
	 * inक्रमmational value should be prपूर्णांकed (e.g., "reboot क्रम
	 * change to take effect").
	 */
	दीर्घ status;
	अचिन्हित दीर्घ v0;
	अचिन्हित दीर्घ v1;
	अचिन्हित दीर्घ v2;
पूर्ण;

प्रकार काष्ठा ia64_sal_retval (*ia64_sal_handler) (u64, ...);

क्रमागत अणु
	SAL_FREQ_BASE_PLATFORM = 0,
	SAL_FREQ_BASE_INTERVAL_TIMER = 1,
	SAL_FREQ_BASE_REALTIME_CLOCK = 2
पूर्ण;

/*
 * The SAL प्रणाली table is followed by a variable number of variable
 * length descriptors.  The काष्ठाure of these descriptors follows
 * below.
 * The defininition follows SAL specs from July 2000
 */
काष्ठा ia64_sal_systab अणु
	u8 signature[4];	/* should be "SST_" */
	u32 size;		/* size of this table in bytes */
	u8 sal_rev_minor;
	u8 sal_rev_major;
	u16 entry_count;	/* # of entries in variable portion */
	u8 checksum;
	u8 reserved1[7];
	u8 sal_a_rev_minor;
	u8 sal_a_rev_major;
	u8 sal_b_rev_minor;
	u8 sal_b_rev_major;
	/* oem_id & product_id: terminating NUL is missing अगर string is exactly 32 bytes दीर्घ. */
	u8 oem_id[32];
	u8 product_id[32];	/* ASCII product id  */
	u8 reserved2[8];
पूर्ण;

क्रमागत sal_systab_entry_type अणु
	SAL_DESC_ENTRY_POINT = 0,
	SAL_DESC_MEMORY = 1,
	SAL_DESC_PLATFORM_FEATURE = 2,
	SAL_DESC_TR = 3,
	SAL_DESC_PTC = 4,
	SAL_DESC_AP_WAKEUP = 5
पूर्ण;

/*
 * Entry type:	Size:
 *	0	48
 *	1	32
 *	2	16
 *	3	32
 *	4	16
 *	5	16
 */
#घोषणा SAL_DESC_SIZE(type)	"\060\040\020\040\020\020"[(अचिन्हित) type]

प्रकार काष्ठा ia64_sal_desc_entry_poपूर्णांक अणु
	u8 type;
	u8 reserved1[7];
	u64 pal_proc;
	u64 sal_proc;
	u64 gp;
	u8 reserved2[16];
पूर्णia64_sal_desc_entry_poपूर्णांक_t;

प्रकार काष्ठा ia64_sal_desc_memory अणु
	u8 type;
	u8 used_by_sal;	/* needs to be mapped क्रम SAL? */
	u8 mem_attr;		/* current memory attribute setting */
	u8 access_rights;	/* access rights set up by SAL */
	u8 mem_attr_mask;	/* mask of supported memory attributes */
	u8 reserved1;
	u8 mem_type;		/* memory type */
	u8 mem_usage;		/* memory usage */
	u64 addr;		/* physical address of memory */
	u32 length;	/* length (multiple of 4KB pages) */
	u32 reserved2;
	u8 oem_reserved[8];
पूर्ण ia64_sal_desc_memory_t;

प्रकार काष्ठा ia64_sal_desc_platक्रमm_feature अणु
	u8 type;
	u8 feature_mask;
	u8 reserved1[14];
पूर्ण ia64_sal_desc_platक्रमm_feature_t;

प्रकार काष्ठा ia64_sal_desc_tr अणु
	u8 type;
	u8 tr_type;		/* 0 == inकाष्ठाion, 1 == data */
	u8 regnum;		/* translation रेजिस्टर number */
	u8 reserved1[5];
	u64 addr;		/* भव address of area covered */
	u64 page_size;		/* encoded page size */
	u8 reserved2[8];
पूर्ण ia64_sal_desc_tr_t;

प्रकार काष्ठा ia64_sal_desc_ptc अणु
	u8 type;
	u8 reserved1[3];
	u32 num_करोमुख्यs;	/* # of coherence करोमुख्यs */
	u64 करोमुख्य_info;	/* physical address of करोमुख्य info table */
पूर्ण ia64_sal_desc_ptc_t;

प्रकार काष्ठा ia64_sal_ptc_करोमुख्य_info अणु
	u64 proc_count;		/* number of processors in करोमुख्य */
	u64 proc_list;		/* physical address of LID array */
पूर्ण ia64_sal_ptc_करोमुख्य_info_t;

प्रकार काष्ठा ia64_sal_ptc_करोमुख्य_proc_entry अणु
	u64 id  : 8;		/* id of processor */
	u64 eid : 8;		/* eid of processor */
पूर्ण ia64_sal_ptc_करोमुख्य_proc_entry_t;


#घोषणा IA64_SAL_AP_EXTERNAL_INT 0

प्रकार काष्ठा ia64_sal_desc_ap_wakeup अणु
	u8 type;
	u8 mechanism;		/* 0 == बाह्यal पूर्णांकerrupt */
	u8 reserved1[6];
	u64 vector;		/* पूर्णांकerrupt vector in range 0x10-0xff */
पूर्ण ia64_sal_desc_ap_wakeup_t ;

बाह्य ia64_sal_handler ia64_sal;
बाह्य काष्ठा ia64_sal_desc_ptc *ia64_ptc_करोमुख्य_info;

बाह्य अचिन्हित लघु sal_revision;	/* supported SAL spec revision */
बाह्य अचिन्हित लघु sal_version;	/* SAL version; OEM dependent */
#घोषणा SAL_VERSION_CODE(major, minor) ((bin2bcd(major) << 8) | bin2bcd(minor))

बाह्य स्थिर अक्षर *ia64_sal_म_त्रुटि (दीर्घ status);
बाह्य व्योम ia64_sal_init (काष्ठा ia64_sal_systab *sal_systab);

/* SAL inक्रमmation type encodings */
क्रमागत अणु
	SAL_INFO_TYPE_MCA  = 0,		/* Machine check पात inक्रमmation */
        SAL_INFO_TYPE_INIT = 1,		/* Init inक्रमmation */
        SAL_INFO_TYPE_CMC  = 2,		/* Corrected machine check inक्रमmation */
        SAL_INFO_TYPE_CPE  = 3		/* Corrected platक्रमm error inक्रमmation */
पूर्ण;

/* Encodings क्रम machine check parameter types */
क्रमागत अणु
	SAL_MC_PARAM_RENDEZ_INT    = 1,	/* Rendezvous पूर्णांकerrupt */
	SAL_MC_PARAM_RENDEZ_WAKEUP = 2,	/* Wakeup */
	SAL_MC_PARAM_CPE_INT	   = 3	/* Corrected Platक्रमm Error Int */
पूर्ण;

/* Encodings क्रम rendezvous mechanisms */
क्रमागत अणु
	SAL_MC_PARAM_MECHANISM_INT = 1,	/* Use पूर्णांकerrupt */
	SAL_MC_PARAM_MECHANISM_MEM = 2	/* Use memory synchronization variable*/
पूर्ण;

/* Encodings क्रम vectors which can be रेजिस्टरed by the OS with SAL */
क्रमागत अणु
	SAL_VECTOR_OS_MCA	  = 0,
	SAL_VECTOR_OS_INIT	  = 1,
	SAL_VECTOR_OS_BOOT_RENDEZ = 2
पूर्ण;

/* Encodings क्रम mca_opt parameter sent to SAL_MC_SET_PARAMS */
#घोषणा	SAL_MC_PARAM_RZ_ALWAYS		0x1
#घोषणा	SAL_MC_PARAM_BINIT_ESCALATE	0x10

/*
 * Definition of the SAL Error Log from the SAL spec
 */

/* SAL Error Record Section GUID Definitions */
#घोषणा SAL_PROC_DEV_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf1, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_MEM_DEV_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf2, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_SEL_DEV_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf3, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_PCI_BUS_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf4, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_SMBIOS_DEV_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf5, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_PCI_COMP_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf6, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_SPECIFIC_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf7, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_HOST_CTLR_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf8, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा SAL_PLAT_BUS_ERR_SECT_GUID  \
    EFI_GUID(0xe429faf9, 0x3cb7, 0x11d4, 0xbc, 0xa7, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81)
#घोषणा PROCESSOR_ABSTRACTION_LAYER_OVERWRITE_GUID \
    EFI_GUID(0x6cb0a200, 0x893a, 0x11da, 0x96, 0xd2, 0x0, 0x10, 0x83, 0xff, \
		0xca, 0x4d)

#घोषणा MAX_CACHE_ERRORS	6
#घोषणा MAX_TLB_ERRORS		6
#घोषणा MAX_BUS_ERRORS		1

/* Definition of version  according to SAL spec क्रम logging purposes */
प्रकार काष्ठा sal_log_revision अणु
	u8 minor;		/* BCD (0..99) */
	u8 major;		/* BCD (0..99) */
पूर्ण sal_log_revision_t;

/* Definition of बारtamp according to SAL spec क्रम logging purposes */
प्रकार काष्ठा sal_log_बारtamp अणु
	u8 slh_second;		/* Second (0..59) */
	u8 slh_minute;		/* Minute (0..59) */
	u8 slh_hour;		/* Hour (0..23) */
	u8 slh_reserved;
	u8 slh_day;		/* Day (1..31) */
	u8 slh_month;		/* Month (1..12) */
	u8 slh_year;		/* Year (00..99) */
	u8 slh_century;		/* Century (19, 20, 21, ...) */
पूर्ण sal_log_बारtamp_t;

/* Definition of log record  header काष्ठाures */
प्रकार काष्ठा sal_log_record_header अणु
	u64 id;				/* Unique monotonically increasing ID */
	sal_log_revision_t revision;	/* Major and Minor revision of header */
	u8 severity;			/* Error Severity */
	u8 validation_bits;		/* 0: platक्रमm_guid, 1: !बारtamp */
	u32 len;			/* Length of this error log in bytes */
	sal_log_बारtamp_t बारtamp;	/* Timestamp */
	efi_guid_t platक्रमm_guid;	/* Unique OEM Platक्रमm ID */
पूर्ण sal_log_record_header_t;

#घोषणा sal_log_severity_recoverable	0
#घोषणा sal_log_severity_fatal		1
#घोषणा sal_log_severity_corrected	2

/*
 * Error Recovery Info (ERI) bit decode.  From SAL Spec section B.2.2 Table B-3
 * Error Section Error_Recovery_Info Field Definition.
 */
#घोषणा ERI_NOT_VALID		0x0	/* Error Recovery Field is not valid */
#घोषणा ERI_NOT_ACCESSIBLE	0x30	/* Resource not accessible */
#घोषणा ERI_CONTAINMENT_WARN	0x22	/* Corrupt data propagated */
#घोषणा ERI_UNCORRECTED_ERROR	0x20	/* Uncorrected error */
#घोषणा ERI_COMPONENT_RESET	0x24	/* Component must be reset */
#घोषणा ERI_CORR_ERROR_LOG	0x21	/* Corrected error, needs logging */
#घोषणा ERI_CORR_ERROR_THRESH	0x29	/* Corrected error threshold exceeded */

/* Definition of log section header काष्ठाures */
प्रकार काष्ठा sal_log_sec_header अणु
    efi_guid_t guid;			/* Unique Section ID */
    sal_log_revision_t revision;	/* Major and Minor revision of Section */
    u8 error_recovery_info;		/* Platक्रमm error recovery status */
    u8 reserved;
    u32 len;				/* Section length */
पूर्ण sal_log_section_hdr_t;

प्रकार काष्ठा sal_log_mod_error_info अणु
	काष्ठा अणु
		u64 check_info              : 1,
		    requestor_identअगरier    : 1,
		    responder_identअगरier    : 1,
		    target_identअगरier       : 1,
		    precise_ip              : 1,
		    reserved                : 59;
	पूर्ण valid;
	u64 check_info;
	u64 requestor_identअगरier;
	u64 responder_identअगरier;
	u64 target_identअगरier;
	u64 precise_ip;
पूर्ण sal_log_mod_error_info_t;

प्रकार काष्ठा sal_processor_अटल_info अणु
	काष्ठा अणु
		u64 minstate        : 1,
		    br              : 1,
		    cr              : 1,
		    ar              : 1,
		    rr              : 1,
		    fr              : 1,
		    reserved        : 58;
	पूर्ण valid;
	काष्ठा pal_min_state_area min_state_area;
	u64 br[8];
	u64 cr[128];
	u64 ar[128];
	u64 rr[8];
	काष्ठा ia64_fpreg __attribute__ ((packed)) fr[128];
पूर्ण sal_processor_अटल_info_t;

काष्ठा sal_cpuid_info अणु
	u64 regs[5];
	u64 reserved;
पूर्ण;

प्रकार काष्ठा sal_log_processor_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 proc_error_map      : 1,
		    proc_state_param    : 1,
		    proc_cr_lid         : 1,
		    psi_अटल_काष्ठा   : 1,
		    num_cache_check     : 4,
		    num_tlb_check       : 4,
		    num_bus_check       : 4,
		    num_reg_file_check  : 4,
		    num_ms_check        : 4,
		    cpuid_info          : 1,
		    reserved1           : 39;
	पूर्ण valid;
	u64 proc_error_map;
	u64 proc_state_parameter;
	u64 proc_cr_lid;
	/*
	 * The rest of this काष्ठाure consists of variable-length arrays, which can't be
	 * expressed in C.
	 */
	sal_log_mod_error_info_t info[0];
	/*
	 * This is what the rest looked like अगर C supported variable-length arrays:
	 *
	 * sal_log_mod_error_info_t cache_check_info[.valid.num_cache_check];
	 * sal_log_mod_error_info_t tlb_check_info[.valid.num_tlb_check];
	 * sal_log_mod_error_info_t bus_check_info[.valid.num_bus_check];
	 * sal_log_mod_error_info_t reg_file_check_info[.valid.num_reg_file_check];
	 * sal_log_mod_error_info_t ms_check_info[.valid.num_ms_check];
	 * काष्ठा sal_cpuid_info cpuid_info;
	 * sal_processor_अटल_info_t processor_अटल_info;
	 */
पूर्ण sal_log_processor_info_t;

/* Given a sal_log_processor_info_t poपूर्णांकer, वापस a poपूर्णांकer to the processor_अटल_info: */
#घोषणा SAL_LPI_PSI_INFO(l)									\
(अणु	sal_log_processor_info_t *_l = (l);							\
	((sal_processor_अटल_info_t *)							\
	 ((अक्षर *) _l->info + ((_l->valid.num_cache_check + _l->valid.num_tlb_check		\
				+ _l->valid.num_bus_check + _l->valid.num_reg_file_check	\
				+ _l->valid.num_ms_check) * माप(sal_log_mod_error_info_t)	\
			       + माप(काष्ठा sal_cpuid_info))));				\
पूर्ण)

/* platक्रमm error log काष्ठाures */

प्रकार काष्ठा sal_log_mem_dev_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 error_status    : 1,
		    physical_addr   : 1,
		    addr_mask       : 1,
		    node            : 1,
		    card            : 1,
		    module          : 1,
		    bank            : 1,
		    device          : 1,
		    row             : 1,
		    column          : 1,
		    bit_position    : 1,
		    requestor_id    : 1,
		    responder_id    : 1,
		    target_id       : 1,
		    bus_spec_data   : 1,
		    oem_id          : 1,
		    oem_data        : 1,
		    reserved        : 47;
	पूर्ण valid;
	u64 error_status;
	u64 physical_addr;
	u64 addr_mask;
	u16 node;
	u16 card;
	u16 module;
	u16 bank;
	u16 device;
	u16 row;
	u16 column;
	u16 bit_position;
	u64 requestor_id;
	u64 responder_id;
	u64 target_id;
	u64 bus_spec_data;
	u8 oem_id[16];
	u8 oem_data[1];			/* Variable length data */
पूर्ण sal_log_mem_dev_err_info_t;

प्रकार काष्ठा sal_log_sel_dev_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 record_id       : 1,
		    record_type     : 1,
		    generator_id    : 1,
		    evm_rev         : 1,
		    sensor_type     : 1,
		    sensor_num      : 1,
		    event_dir       : 1,
		    event_data1     : 1,
		    event_data2     : 1,
		    event_data3     : 1,
		    reserved        : 54;
	पूर्ण valid;
	u16 record_id;
	u8 record_type;
	u8 बारtamp[4];
	u16 generator_id;
	u8 evm_rev;
	u8 sensor_type;
	u8 sensor_num;
	u8 event_dir;
	u8 event_data1;
	u8 event_data2;
	u8 event_data3;
पूर्ण sal_log_sel_dev_err_info_t;

प्रकार काष्ठा sal_log_pci_bus_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 err_status      : 1,
		    err_type        : 1,
		    bus_id          : 1,
		    bus_address     : 1,
		    bus_data        : 1,
		    bus_cmd         : 1,
		    requestor_id    : 1,
		    responder_id    : 1,
		    target_id       : 1,
		    oem_data        : 1,
		    reserved        : 54;
	पूर्ण valid;
	u64 err_status;
	u16 err_type;
	u16 bus_id;
	u32 reserved;
	u64 bus_address;
	u64 bus_data;
	u64 bus_cmd;
	u64 requestor_id;
	u64 responder_id;
	u64 target_id;
	u8 oem_data[1];			/* Variable length data */
पूर्ण sal_log_pci_bus_err_info_t;

प्रकार काष्ठा sal_log_smbios_dev_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 event_type      : 1,
		    length          : 1,
		    समय_stamp      : 1,
		    data            : 1,
		    reserved1       : 60;
	पूर्ण valid;
	u8 event_type;
	u8 length;
	u8 समय_stamp[6];
	u8 data[1];			/* data of variable length, length == slsmb_length */
पूर्ण sal_log_smbios_dev_err_info_t;

प्रकार काष्ठा sal_log_pci_comp_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 err_status      : 1,
		    comp_info       : 1,
		    num_mem_regs    : 1,
		    num_io_regs     : 1,
		    reg_data_pairs  : 1,
		    oem_data        : 1,
		    reserved        : 58;
	पूर्ण valid;
	u64 err_status;
	काष्ठा अणु
		u16 venकरोr_id;
		u16 device_id;
		u8 class_code[3];
		u8 func_num;
		u8 dev_num;
		u8 bus_num;
		u8 seg_num;
		u8 reserved[5];
	पूर्ण comp_info;
	u32 num_mem_regs;
	u32 num_io_regs;
	u64 reg_data_pairs[1];
	/*
	 * array of address/data रेजिस्टर pairs is num_mem_regs + num_io_regs elements
	 * दीर्घ.  Each array element consists of a u64 address followed by a u64 data
	 * value.  The oem_data array immediately follows the reg_data_pairs array
	 */
	u8 oem_data[1];			/* Variable length data */
पूर्ण sal_log_pci_comp_err_info_t;

प्रकार काष्ठा sal_log_plat_specअगरic_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 err_status      : 1,
		    guid            : 1,
		    oem_data        : 1,
		    reserved        : 61;
	पूर्ण valid;
	u64 err_status;
	efi_guid_t guid;
	u8 oem_data[1];			/* platक्रमm specअगरic variable length data */
पूर्ण sal_log_plat_specअगरic_err_info_t;

प्रकार काष्ठा sal_log_host_ctlr_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 err_status      : 1,
		    requestor_id    : 1,
		    responder_id    : 1,
		    target_id       : 1,
		    bus_spec_data   : 1,
		    oem_data        : 1,
		    reserved        : 58;
	पूर्ण valid;
	u64 err_status;
	u64 requestor_id;
	u64 responder_id;
	u64 target_id;
	u64 bus_spec_data;
	u8 oem_data[1];			/* Variable length OEM data */
पूर्ण sal_log_host_ctlr_err_info_t;

प्रकार काष्ठा sal_log_plat_bus_err_info अणु
	sal_log_section_hdr_t header;
	काष्ठा अणु
		u64 err_status      : 1,
		    requestor_id    : 1,
		    responder_id    : 1,
		    target_id       : 1,
		    bus_spec_data   : 1,
		    oem_data        : 1,
		    reserved        : 58;
	पूर्ण valid;
	u64 err_status;
	u64 requestor_id;
	u64 responder_id;
	u64 target_id;
	u64 bus_spec_data;
	u8 oem_data[1];			/* Variable length OEM data */
पूर्ण sal_log_plat_bus_err_info_t;

/* Overall platक्रमm error section काष्ठाure */
प्रकार जोड़ sal_log_platक्रमm_err_info अणु
	sal_log_mem_dev_err_info_t mem_dev_err;
	sal_log_sel_dev_err_info_t sel_dev_err;
	sal_log_pci_bus_err_info_t pci_bus_err;
	sal_log_smbios_dev_err_info_t smbios_dev_err;
	sal_log_pci_comp_err_info_t pci_comp_err;
	sal_log_plat_specअगरic_err_info_t plat_specअगरic_err;
	sal_log_host_ctlr_err_info_t host_ctlr_err;
	sal_log_plat_bus_err_info_t plat_bus_err;
पूर्ण sal_log_platक्रमm_err_info_t;

/* SAL log over-all, multi-section error record काष्ठाure (processor+platक्रमm) */
प्रकार काष्ठा err_rec अणु
	sal_log_record_header_t sal_elog_header;
	sal_log_processor_info_t proc_err;
	sal_log_platक्रमm_err_info_t plat_err;
	u8 oem_data_pad[1024];
पूर्ण ia64_err_rec_t;

/*
 * Now define a couple of अंतरभूत functions क्रम improved type checking
 * and convenience.
 */

बाह्य s64 ia64_sal_cache_flush (u64 cache_type);
बाह्य व्योम __init check_sal_cache_flush (व्योम);

/* Initialize all the processor and platक्रमm level inकाष्ठाion and data caches */
अटल अंतरभूत s64
ia64_sal_cache_init (व्योम)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL(isrv, SAL_CACHE_INIT, 0, 0, 0, 0, 0, 0, 0);
	वापस isrv.status;
पूर्ण

/*
 * Clear the processor and platक्रमm inक्रमmation logged by SAL with respect to the machine
 * state at the समय of MCA's, INITs, CMCs, or CPEs.
 */
अटल अंतरभूत s64
ia64_sal_clear_state_info (u64 sal_info_type)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL_REENTRANT(isrv, SAL_CLEAR_STATE_INFO, sal_info_type, 0,
	              0, 0, 0, 0, 0);
	वापस isrv.status;
पूर्ण


/* Get the processor and platक्रमm inक्रमmation logged by SAL with respect to the machine
 * state at the समय of the MCAs, INITs, CMCs, or CPEs.
 */
अटल अंतरभूत u64
ia64_sal_get_state_info (u64 sal_info_type, u64 *sal_info)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL_REENTRANT(isrv, SAL_GET_STATE_INFO, sal_info_type, 0,
	              sal_info, 0, 0, 0, 0);
	अगर (isrv.status)
		वापस 0;

	वापस isrv.v0;
पूर्ण

/*
 * Get the maximum size of the inक्रमmation logged by SAL with respect to the machine state
 * at the समय of MCAs, INITs, CMCs, or CPEs.
 */
अटल अंतरभूत u64
ia64_sal_get_state_info_size (u64 sal_info_type)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL_REENTRANT(isrv, SAL_GET_STATE_INFO_SIZE, sal_info_type, 0,
	              0, 0, 0, 0, 0);
	अगर (isrv.status)
		वापस 0;
	वापस isrv.v0;
पूर्ण

/*
 * Causes the processor to go पूर्णांकo a spin loop within SAL where SAL aरुकोs a wakeup from
 * the monarch processor.  Must not lock, because it will not वापस on any cpu until the
 * monarch processor sends a wake up.
 */
अटल अंतरभूत s64
ia64_sal_mc_rendez (व्योम)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL_NOLOCK(isrv, SAL_MC_RENDEZ, 0, 0, 0, 0, 0, 0, 0);
	वापस isrv.status;
पूर्ण

/*
 * Allow the OS to specअगरy the पूर्णांकerrupt number to be used by SAL to पूर्णांकerrupt OS during
 * the machine check rendezvous sequence as well as the mechanism to wake up the
 * non-monarch processor at the end of machine check processing.
 * Returns the complete ia64_sal_retval because some calls वापस more than just a status
 * value.
 */
अटल अंतरभूत काष्ठा ia64_sal_retval
ia64_sal_mc_set_params (u64 param_type, u64 i_or_m, u64 i_or_m_val, u64 समयout, u64 rz_always)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL(isrv, SAL_MC_SET_PARAMS, param_type, i_or_m, i_or_m_val,
		 समयout, rz_always, 0, 0);
	वापस isrv;
पूर्ण

/* Read from PCI configuration space */
अटल अंतरभूत s64
ia64_sal_pci_config_पढ़ो (u64 pci_config_addr, पूर्णांक type, u64 size, u64 *value)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL(isrv, SAL_PCI_CONFIG_READ, pci_config_addr, size, type, 0, 0, 0, 0);
	अगर (value)
		*value = isrv.v0;
	वापस isrv.status;
पूर्ण

/* Write to PCI configuration space */
अटल अंतरभूत s64
ia64_sal_pci_config_ग_लिखो (u64 pci_config_addr, पूर्णांक type, u64 size, u64 value)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL(isrv, SAL_PCI_CONFIG_WRITE, pci_config_addr, size, value,
	         type, 0, 0, 0);
	वापस isrv.status;
पूर्ण

/*
 * Register physical addresses of locations needed by SAL when SAL procedures are invoked
 * in भव mode.
 */
अटल अंतरभूत s64
ia64_sal_रेजिस्टर_physical_addr (u64 phys_entry, u64 phys_addr)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL(isrv, SAL_REGISTER_PHYSICAL_ADDR, phys_entry, phys_addr,
	         0, 0, 0, 0, 0);
	वापस isrv.status;
पूर्ण

/*
 * Register software dependent code locations within SAL. These locations are handlers or
 * entry poपूर्णांकs where SAL will pass control क्रम the specअगरied event. These event handlers
 * are क्रम the bott rendezvous, MCAs and INIT scenarios.
 */
अटल अंतरभूत s64
ia64_sal_set_vectors (u64 vector_type,
		      u64 handler_addr1, u64 gp1, u64 handler_len1,
		      u64 handler_addr2, u64 gp2, u64 handler_len2)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL(isrv, SAL_SET_VECTORS, vector_type,
			handler_addr1, gp1, handler_len1,
			handler_addr2, gp2, handler_len2);

	वापस isrv.status;
पूर्ण

/* Update the contents of PAL block in the non-अस्थिर storage device */
अटल अंतरभूत s64
ia64_sal_update_pal (u64 param_buf, u64 scratch_buf, u64 scratch_buf_size,
		     u64 *error_code, u64 *scratch_buf_size_needed)
अणु
	काष्ठा ia64_sal_retval isrv;
	SAL_CALL(isrv, SAL_UPDATE_PAL, param_buf, scratch_buf, scratch_buf_size,
	         0, 0, 0, 0);
	अगर (error_code)
		*error_code = isrv.v0;
	अगर (scratch_buf_size_needed)
		*scratch_buf_size_needed = isrv.v1;
	वापस isrv.status;
पूर्ण

/* Get physical processor die mapping in the platक्रमm. */
अटल अंतरभूत s64
ia64_sal_physical_id_info(u16 *splid)
अणु
	काष्ठा ia64_sal_retval isrv;

	अगर (sal_revision < SAL_VERSION_CODE(3,2))
		वापस -1;

	SAL_CALL(isrv, SAL_PHYSICAL_ID_INFO, 0, 0, 0, 0, 0, 0, 0);
	अगर (splid)
		*splid = isrv.v0;
	वापस isrv.status;
पूर्ण

बाह्य अचिन्हित दीर्घ sal_platक्रमm_features;

बाह्य पूर्णांक (*salinfo_platक्रमm_oemdata)(स्थिर u8 *, u8 **, u64 *);

काष्ठा sal_ret_values अणु
	दीर्घ r8; दीर्घ r9; दीर्घ r10; दीर्घ r11;
पूर्ण;

#घोषणा IA64_SAL_OEMFUNC_MIN		0x02000000
#घोषणा IA64_SAL_OEMFUNC_MAX		0x03ffffff

बाह्य पूर्णांक ia64_sal_oemcall(काष्ठा ia64_sal_retval *, u64, u64, u64, u64, u64,
			    u64, u64, u64);
बाह्य पूर्णांक ia64_sal_oemcall_nolock(काष्ठा ia64_sal_retval *, u64, u64, u64,
				   u64, u64, u64, u64, u64);
बाह्य पूर्णांक ia64_sal_oemcall_reentrant(काष्ठा ia64_sal_retval *, u64, u64, u64,
				      u64, u64, u64, u64, u64);
बाह्य दीर्घ
ia64_sal_freq_base (अचिन्हित दीर्घ which, अचिन्हित दीर्घ *ticks_per_second,
		    अचिन्हित दीर्घ *drअगरt_info);
#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * System Abstraction Layer Specअगरication
 * Section 3.2.5.1: OS_BOOT_RENDEZ to SAL वापस State.
 * Note: region regs are stored first in head.S _start. Hence they must
 * stay up front.
 */
काष्ठा sal_to_os_boot अणु
	u64 rr[8];		/* Region Registers */
	u64 br[6];		/* br0:
				 * वापस addr पूर्णांकo SAL boot rendez routine */
	u64 gr1;		/* SAL:GP */
	u64 gr12;		/* SAL:SP */
	u64 gr13;		/* SAL: Task Poपूर्णांकer */
	u64 fpsr;
	u64 pfs;
	u64 rnat;
	u64 unat;
	u64 bspstore;
	u64 dcr;		/* Default Control Register */
	u64 iva;
	u64 pta;
	u64 itv;
	u64 pmv;
	u64 cmcv;
	u64 lrr[2];
	u64 gr[4];
	u64 pr;			/* Predicate रेजिस्टरs */
	u64 lc;			/* Loop Count */
	काष्ठा ia64_fpreg fp[20];
पूर्ण;

/*
 * Global array allocated क्रम NR_CPUS at boot समय
 */
बाह्य काष्ठा sal_to_os_boot sal_boot_rendez_state[NR_CPUS];

बाह्य व्योम ia64_jump_to_sal(काष्ठा sal_to_os_boot *);
#पूर्ण_अगर

बाह्य व्योम ia64_sal_handler_init(व्योम *entry_poपूर्णांक, व्योम *gpval);

#घोषणा PALO_MAX_TLB_PURGES	0xFFFF
#घोषणा PALO_SIG	"PALO"

काष्ठा palo_table अणु
	u8  signature[4];	/* Should be "PALO" */
	u32 length;
	u8  minor_revision;
	u8  major_revision;
	u8  checksum;
	u8  reserved1[5];
	u16 max_tlb_purges;
	u8  reserved2[6];
पूर्ण;

#घोषणा NPTCG_FROM_PAL			0
#घोषणा NPTCG_FROM_PALO			1
#घोषणा NPTCG_FROM_KERNEL_PARAMETER	2

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_IA64_SAL_H */
