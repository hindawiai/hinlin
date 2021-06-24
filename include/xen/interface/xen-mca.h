<शैली गुरु>
/******************************************************************************
 * arch-x86/mca.h
 * Guest OS machine check पूर्णांकerface to x86 Xen.
 *
 * Contributed by Advanced Micro Devices, Inc.
 * Author: Christoph Egger <Christoph.Egger@amd.com>
 *
 * Updated by Intel Corporation
 * Author: Liu, Jinsong <jinsong.liu@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __XEN_PUBLIC_ARCH_X86_MCA_H__
#घोषणा __XEN_PUBLIC_ARCH_X86_MCA_H__

/* Hypercall */
#घोषणा __HYPERVISOR_mca __HYPERVISOR_arch_0

#घोषणा XEN_MCA_INTERFACE_VERSION	0x01ecc003

/* IN: Dom0 calls hypercall to retrieve nonurgent error log entry */
#घोषणा XEN_MC_NONURGENT	0x1
/* IN: Dom0 calls hypercall to retrieve urgent error log entry */
#घोषणा XEN_MC_URGENT		0x2
/* IN: Dom0 acknowledges previosly-fetched error log entry */
#घोषणा XEN_MC_ACK		0x4

/* OUT: All is ok */
#घोषणा XEN_MC_OK		0x0
/* OUT: Doमुख्य could not fetch data. */
#घोषणा XEN_MC_FETCHFAILED	0x1
/* OUT: There was no machine check data to fetch. */
#घोषणा XEN_MC_NODATA		0x2

#अगर_अघोषित __ASSEMBLY__
/* vIRQ injected to Dom0 */
#घोषणा VIRQ_MCA VIRQ_ARCH_0

/*
 * mc_info entry types
 * mca machine check info are recorded in mc_info entries.
 * when fetch mca info, it can use MC_TYPE_... to distinguish
 * dअगरferent mca info.
 */
#घोषणा MC_TYPE_GLOBAL		0
#घोषणा MC_TYPE_BANK		1
#घोषणा MC_TYPE_EXTENDED	2
#घोषणा MC_TYPE_RECOVERY	3

काष्ठा mcinfo_common अणु
	uपूर्णांक16_t type; /* काष्ठाure type */
	uपूर्णांक16_t size; /* size of this काष्ठा in bytes */
पूर्ण;

#घोषणा MC_FLAG_CORRECTABLE	(1 << 0)
#घोषणा MC_FLAG_UNCORRECTABLE	(1 << 1)
#घोषणा MC_FLAG_RECOVERABLE	(1 << 2)
#घोषणा MC_FLAG_POLLED		(1 << 3)
#घोषणा MC_FLAG_RESET		(1 << 4)
#घोषणा MC_FLAG_CMCI		(1 << 5)
#घोषणा MC_FLAG_MCE		(1 << 6)

/* contains x86 global mc inक्रमmation */
काष्ठा mcinfo_global अणु
	काष्ठा mcinfo_common common;

	uपूर्णांक16_t mc_करोmid; /* running करोमुख्य at the समय in error */
	uपूर्णांक16_t mc_vcpuid; /* भव cpu scheduled क्रम mc_करोmid */
	uपूर्णांक32_t mc_socketid; /* physical socket of the physical core */
	uपूर्णांक16_t mc_coreid; /* physical impacted core */
	uपूर्णांक16_t mc_core_thपढ़ोid; /* core thपढ़ो of physical core */
	uपूर्णांक32_t mc_apicid;
	uपूर्णांक32_t mc_flags;
	uपूर्णांक64_t mc_gstatus; /* global status */
पूर्ण;

/* contains x86 bank mc inक्रमmation */
काष्ठा mcinfo_bank अणु
	काष्ठा mcinfo_common common;

	uपूर्णांक16_t mc_bank; /* bank nr */
	uपूर्णांक16_t mc_करोmid; /* करोमुख्य referenced by mc_addr अगर valid */
	uपूर्णांक64_t mc_status; /* bank status */
	uपूर्णांक64_t mc_addr; /* bank address */
	uपूर्णांक64_t mc_misc;
	uपूर्णांक64_t mc_ctrl2;
	uपूर्णांक64_t mc_tsc;
पूर्ण;

काष्ठा mcinfo_msr अणु
	uपूर्णांक64_t reg; /* MSR */
	uपूर्णांक64_t value; /* MSR value */
पूर्ण;

/* contains mc inक्रमmation from other or additional mc MSRs */
काष्ठा mcinfo_extended अणु
	काष्ठा mcinfo_common common;
	uपूर्णांक32_t mc_msrs; /* Number of msr with valid values. */
	/*
	 * Currently Intel extended MSR (32/64) include all gp रेजिस्टरs
	 * and E(R)FLAGS, E(R)IP, E(R)MISC, up to 11/19 of them might be
	 * useful at present. So expand this array to 16/32 to leave room.
	 */
	काष्ठा mcinfo_msr mc_msr[माप(व्योम *) * 4];
पूर्ण;

/* Recovery Action flags. Giving recovery result inक्रमmation to DOM0 */

/* Xen takes successful recovery action, the error is recovered */
#घोषणा REC_ACTION_RECOVERED (0x1 << 0)
/* No action is perक्रमmed by XEN */
#घोषणा REC_ACTION_NONE (0x1 << 1)
/* It's possible DOM0 might take action ownership in some हाल */
#घोषणा REC_ACTION_NEED_RESET (0x1 << 2)

/*
 * Dअगरferent Recovery Action types, अगर the action is perक्रमmed successfully,
 * REC_ACTION_RECOVERED flag will be वापसed.
 */

/* Page Offline Action */
#घोषणा MC_ACTION_PAGE_OFFLINE (0x1 << 0)
/* CPU offline Action */
#घोषणा MC_ACTION_CPU_OFFLINE (0x1 << 1)
/* L3 cache disable Action */
#घोषणा MC_ACTION_CACHE_SHRINK (0x1 << 2)

/*
 * Below पूर्णांकerface used between XEN/DOM0 क्रम passing XEN's recovery action
 * inक्रमmation to DOM0.
 */
काष्ठा page_offline_action अणु
	/* Params क्रम passing the offlined page number to DOM0 */
	uपूर्णांक64_t mfn;
	uपूर्णांक64_t status;
पूर्ण;

काष्ठा cpu_offline_action अणु
	/* Params क्रम passing the identity of the offlined CPU to DOM0 */
	uपूर्णांक32_t mc_socketid;
	uपूर्णांक16_t mc_coreid;
	uपूर्णांक16_t mc_core_thपढ़ोid;
पूर्ण;

#घोषणा MAX_UNION_SIZE 16
काष्ठा mcinfo_recovery अणु
	काष्ठा mcinfo_common common;
	uपूर्णांक16_t mc_bank; /* bank nr */
	uपूर्णांक8_t action_flags;
	uपूर्णांक8_t action_types;
	जोड़ अणु
		काष्ठा page_offline_action page_retire;
		काष्ठा cpu_offline_action cpu_offline;
		uपूर्णांक8_t pad[MAX_UNION_SIZE];
	पूर्ण action_info;
पूर्ण;


#घोषणा MCINFO_MAXSIZE 768
काष्ठा mc_info अणु
	/* Number of mcinfo_* entries in mi_data */
	uपूर्णांक32_t mi_nentries;
	uपूर्णांक32_t flags;
	uपूर्णांक64_t mi_data[(MCINFO_MAXSIZE - 1) / 8];
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(mc_info);

#घोषणा __MC_MSR_ARRAYSIZE 8
#घोषणा __MC_NMSRS 1
#घोषणा MC_NCAPS 7
काष्ठा mcinfo_logical_cpu अणु
	uपूर्णांक32_t mc_cpunr;
	uपूर्णांक32_t mc_chipid;
	uपूर्णांक16_t mc_coreid;
	uपूर्णांक16_t mc_thपढ़ोid;
	uपूर्णांक32_t mc_apicid;
	uपूर्णांक32_t mc_clusterid;
	uपूर्णांक32_t mc_ncores;
	uपूर्णांक32_t mc_ncores_active;
	uपूर्णांक32_t mc_nthपढ़ोs;
	uपूर्णांक32_t mc_cpuid_level;
	uपूर्णांक32_t mc_family;
	uपूर्णांक32_t mc_venकरोr;
	uपूर्णांक32_t mc_model;
	uपूर्णांक32_t mc_step;
	अक्षर mc_venकरोrid[16];
	अक्षर mc_bअक्रमid[64];
	uपूर्णांक32_t mc_cpu_caps[MC_NCAPS];
	uपूर्णांक32_t mc_cache_size;
	uपूर्णांक32_t mc_cache_alignment;
	uपूर्णांक32_t mc_nmsrvals;
	काष्ठा mcinfo_msr mc_msrvalues[__MC_MSR_ARRAYSIZE];
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(mcinfo_logical_cpu);

/*
 * Prototype:
 *    uपूर्णांक32_t x86_mcinfo_nentries(काष्ठा mc_info *mi);
 */
#घोषणा x86_mcinfo_nentries(_mi)    \
	((_mi)->mi_nentries)
/*
 * Prototype:
 *    काष्ठा mcinfo_common *x86_mcinfo_first(काष्ठा mc_info *mi);
 */
#घोषणा x86_mcinfo_first(_mi)       \
	((काष्ठा mcinfo_common *)(_mi)->mi_data)
/*
 * Prototype:
 *    काष्ठा mcinfo_common *x86_mcinfo_next(काष्ठा mcinfo_common *mic);
 */
#घोषणा x86_mcinfo_next(_mic)       \
	((काष्ठा mcinfo_common *)((uपूर्णांक8_t *)(_mic) + (_mic)->size))

/*
 * Prototype:
 *    व्योम x86_mcinfo_lookup(व्योम *ret, काष्ठा mc_info *mi, uपूर्णांक16_t type);
 */
अटल अंतरभूत व्योम x86_mcinfo_lookup(काष्ठा mcinfo_common **ret,
				     काष्ठा mc_info *mi, uपूर्णांक16_t type)
अणु
	uपूर्णांक32_t i;
	काष्ठा mcinfo_common *mic;
	bool found = 0;

	अगर (!ret || !mi)
		वापस;

	mic = x86_mcinfo_first(mi);
	क्रम (i = 0; i < x86_mcinfo_nentries(mi); i++) अणु
		अगर (mic->type == type) अणु
			found = 1;
			अवरोध;
		पूर्ण
		mic = x86_mcinfo_next(mic);
	पूर्ण

	*ret = found ? mic : शून्य;
पूर्ण

/*
 * Fetch machine check data from hypervisor.
 */
#घोषणा XEN_MC_fetch		1
काष्ठा xen_mc_fetch अणु
	/*
	 * IN: XEN_MC_NONURGENT, XEN_MC_URGENT,
	 * XEN_MC_ACK अगर ack'king an earlier fetch
	 * OUT: XEN_MC_OK, XEN_MC_FETCHAILED, XEN_MC_NODATA
	 */
	uपूर्णांक32_t flags;
	uपूर्णांक32_t _pad0;
	/* OUT: id क्रम ack, IN: id we are ack'ing */
	uपूर्णांक64_t fetch_id;

	/* OUT variables. */
	GUEST_HANDLE(mc_info) data;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_mc_fetch);


/*
 * This tells the hypervisor to notअगरy a DomU about the machine check error
 */
#घोषणा XEN_MC_notअगरyकरोमुख्य	2
काष्ठा xen_mc_notअगरyकरोमुख्य अणु
	/* IN variables */
	uपूर्णांक16_t mc_करोmid; /* The unprivileged करोमुख्य to notअगरy */
	uपूर्णांक16_t mc_vcpuid; /* The vcpu in mc_करोmid to notअगरy */

	/* IN/OUT variables */
	uपूर्णांक32_t flags;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_mc_notअगरyकरोमुख्य);

#घोषणा XEN_MC_physcpuinfo	3
काष्ठा xen_mc_physcpuinfo अणु
	/* IN/OUT */
	uपूर्णांक32_t ncpus;
	uपूर्णांक32_t _pad0;
	/* OUT */
	GUEST_HANDLE(mcinfo_logical_cpu) info;
पूर्ण;

#घोषणा XEN_MC_msrinject	4
#घोषणा MC_MSRINJ_MAXMSRS	8
काष्ठा xen_mc_msrinject अणु
	/* IN */
	uपूर्णांक32_t mcinj_cpunr; /* target processor id */
	uपूर्णांक32_t mcinj_flags; /* see MC_MSRINJ_F_* below */
	uपूर्णांक32_t mcinj_count; /* 0 .. count-1 in array are valid */
	uपूर्णांक32_t _pad0;
	काष्ठा mcinfo_msr mcinj_msr[MC_MSRINJ_MAXMSRS];
पूर्ण;

/* Flags क्रम mcinj_flags above; bits 16-31 are reserved */
#घोषणा MC_MSRINJ_F_INTERPOSE	0x1

#घोषणा XEN_MC_mceinject	5
काष्ठा xen_mc_mceinject अणु
	अचिन्हित पूर्णांक mceinj_cpunr; /* target processor id */
पूर्ण;

काष्ठा xen_mc अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t पूर्णांकerface_version; /* XEN_MCA_INTERFACE_VERSION */
	जोड़ अणु
		काष्ठा xen_mc_fetch        mc_fetch;
		काष्ठा xen_mc_notअगरyकरोमुख्य mc_notअगरyकरोमुख्य;
		काष्ठा xen_mc_physcpuinfo  mc_physcpuinfo;
		काष्ठा xen_mc_msrinject    mc_msrinject;
		काष्ठा xen_mc_mceinject    mc_mceinject;
	पूर्ण u;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_mc);

/*
 * Fields are zero when not available. Also, this काष्ठा is shared with
 * userspace mcelog and thus must keep existing fields at current offsets.
 * Only add new fields to the end of the काष्ठाure
 */
काष्ठा xen_mce अणु
	__u64 status;
	__u64 misc;
	__u64 addr;
	__u64 mcgstatus;
	__u64 ip;
	__u64 tsc;	/* cpu समय stamp counter */
	__u64 समय;	/* wall समय_प्रकार when error was detected */
	__u8  cpuvenकरोr;	/* cpu venकरोr as encoded in प्रणाली.h */
	__u8  inject_flags;	/* software inject flags */
	__u16  pad;
	__u32 cpuid;	/* CPUID 1 EAX */
	__u8  cs;		/* code segment */
	__u8  bank;	/* machine check bank */
	__u8  cpu;	/* cpu number; obsolete; use extcpu now */
	__u8  finished;   /* entry is valid */
	__u32 extcpu;	/* linux cpu number that detected the error */
	__u32 socketid;	/* CPU socket ID */
	__u32 apicid;	/* CPU initial apic ID */
	__u64 mcgcap;	/* MCGCAP MSR: machine check capabilities of CPU */
	__u64 synd;	/* MCA_SYND MSR: only valid on SMCA प्रणालीs */
	__u64 ipid;	/* MCA_IPID MSR: only valid on SMCA प्रणालीs */
	__u64 ppin;	/* Protected Processor Inventory Number */
पूर्ण;

/*
 * This काष्ठाure contains all data related to the MCE log.  Also
 * carries a signature to make it easier to find from बाह्यal
 * debugging tools.  Each entry is only valid when its finished flag
 * is set.
 */

#घोषणा XEN_MCE_LOG_LEN 32

काष्ठा xen_mce_log अणु
	अक्षर signature[12]; /* "MACHINECHECK" */
	अचिन्हित len;	    /* = XEN_MCE_LOG_LEN */
	अचिन्हित next;
	अचिन्हित flags;
	अचिन्हित recordlen;	/* length of काष्ठा xen_mce */
	काष्ठा xen_mce entry[XEN_MCE_LOG_LEN];
पूर्ण;

#घोषणा XEN_MCE_OVERFLOW 0		/* bit 0 in flags means overflow */

#घोषणा XEN_MCE_LOG_SIGNATURE	"MACHINECHECK"

#घोषणा MCE_GET_RECORD_LEN   _IOR('M', 1, पूर्णांक)
#घोषणा MCE_GET_LOG_LEN      _IOR('M', 2, पूर्णांक)
#घोषणा MCE_GETCLEAR_FLAGS   _IOR('M', 3, पूर्णांक)

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __XEN_PUBLIC_ARCH_X86_MCA_H__ */
