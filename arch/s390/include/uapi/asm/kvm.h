<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_KVM_S390_H
#घोषणा __LINUX_KVM_S390_H
/*
 * KVM s390 specअगरic काष्ठाures and definitions
 *
 * Copyright IBM Corp. 2008, 2018
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 *               Christian Borntraeger <borntraeger@de.ibm.com>
 */
#समावेश <linux/types.h>

#घोषणा __KVM_S390
#घोषणा __KVM_HAVE_GUEST_DEBUG

/* Device control API: s390-specअगरic devices */
#घोषणा KVM_DEV_FLIC_GET_ALL_IRQS	1
#घोषणा KVM_DEV_FLIC_ENQUEUE		2
#घोषणा KVM_DEV_FLIC_CLEAR_IRQS		3
#घोषणा KVM_DEV_FLIC_APF_ENABLE		4
#घोषणा KVM_DEV_FLIC_APF_DISABLE_WAIT	5
#घोषणा KVM_DEV_FLIC_ADAPTER_REGISTER	6
#घोषणा KVM_DEV_FLIC_ADAPTER_MODIFY	7
#घोषणा KVM_DEV_FLIC_CLEAR_IO_IRQ	8
#घोषणा KVM_DEV_FLIC_AISM		9
#घोषणा KVM_DEV_FLIC_AIRQ_INJECT	10
#घोषणा KVM_DEV_FLIC_AISM_ALL		11
/*
 * We can have up to 4*64k pending subchannels + 8 adapter पूर्णांकerrupts,
 * as well as up  to ASYNC_PF_PER_VCPU*KVM_MAX_VCPUS pfault करोne पूर्णांकerrupts.
 * There are also sclp and machine checks. This gives us
 * माप(kvm_s390_irq)*(4*65536+8+64*64+1+1) = 72 * 266250 = 19170000
 * Lets round up to 8192 pages.
 */
#घोषणा KVM_S390_MAX_FLOAT_IRQS	266250
#घोषणा KVM_S390_FLIC_MAX_BUFFER	0x2000000

काष्ठा kvm_s390_io_adapter अणु
	__u32 id;
	__u8 isc;
	__u8 maskable;
	__u8 swap;
	__u8 flags;
पूर्ण;

#घोषणा KVM_S390_ADAPTER_SUPPRESSIBLE 0x01

काष्ठा kvm_s390_ais_req अणु
	__u8 isc;
	__u16 mode;
पूर्ण;

काष्ठा kvm_s390_ais_all अणु
	__u8 simm;
	__u8 nimm;
पूर्ण;

#घोषणा KVM_S390_IO_ADAPTER_MASK 1
#घोषणा KVM_S390_IO_ADAPTER_MAP 2
#घोषणा KVM_S390_IO_ADAPTER_UNMAP 3

काष्ठा kvm_s390_io_adapter_req अणु
	__u32 id;
	__u8 type;
	__u8 mask;
	__u16 pad0;
	__u64 addr;
पूर्ण;

/* kvm attr_group  on vm fd */
#घोषणा KVM_S390_VM_MEM_CTRL		0
#घोषणा KVM_S390_VM_TOD			1
#घोषणा KVM_S390_VM_CRYPTO		2
#घोषणा KVM_S390_VM_CPU_MODEL		3
#घोषणा KVM_S390_VM_MIGRATION		4

/* kvm attributes क्रम mem_ctrl */
#घोषणा KVM_S390_VM_MEM_ENABLE_CMMA	0
#घोषणा KVM_S390_VM_MEM_CLR_CMMA	1
#घोषणा KVM_S390_VM_MEM_LIMIT_SIZE	2

#घोषणा KVM_S390_NO_MEM_LIMIT		U64_MAX

/* kvm attributes क्रम KVM_S390_VM_TOD */
#घोषणा KVM_S390_VM_TOD_LOW		0
#घोषणा KVM_S390_VM_TOD_HIGH		1
#घोषणा KVM_S390_VM_TOD_EXT		2

काष्ठा kvm_s390_vm_tod_घड़ी अणु
	__u8  epoch_idx;
	__u64 tod;
पूर्ण;

/* kvm attributes क्रम KVM_S390_VM_CPU_MODEL */
/* processor related attributes are r/w */
#घोषणा KVM_S390_VM_CPU_PROCESSOR	0
काष्ठा kvm_s390_vm_cpu_processor अणु
	__u64 cpuid;
	__u16 ibc;
	__u8  pad[6];
	__u64 fac_list[256];
पूर्ण;

/* machine related attributes are r/o */
#घोषणा KVM_S390_VM_CPU_MACHINE		1
काष्ठा kvm_s390_vm_cpu_machine अणु
	__u64 cpuid;
	__u32 ibc;
	__u8  pad[4];
	__u64 fac_mask[256];
	__u64 fac_list[256];
पूर्ण;

#घोषणा KVM_S390_VM_CPU_PROCESSOR_FEAT	2
#घोषणा KVM_S390_VM_CPU_MACHINE_FEAT	3

#घोषणा KVM_S390_VM_CPU_FEAT_NR_BITS	1024
#घोषणा KVM_S390_VM_CPU_FEAT_ESOP	0
#घोषणा KVM_S390_VM_CPU_FEAT_SIEF2	1
#घोषणा KVM_S390_VM_CPU_FEAT_64BSCAO	2
#घोषणा KVM_S390_VM_CPU_FEAT_SIIF	3
#घोषणा KVM_S390_VM_CPU_FEAT_GPERE	4
#घोषणा KVM_S390_VM_CPU_FEAT_GSLS	5
#घोषणा KVM_S390_VM_CPU_FEAT_IB		6
#घोषणा KVM_S390_VM_CPU_FEAT_CEI	7
#घोषणा KVM_S390_VM_CPU_FEAT_IBS	8
#घोषणा KVM_S390_VM_CPU_FEAT_SKEY	9
#घोषणा KVM_S390_VM_CPU_FEAT_CMMA	10
#घोषणा KVM_S390_VM_CPU_FEAT_PFMFI	11
#घोषणा KVM_S390_VM_CPU_FEAT_SIGPIF	12
#घोषणा KVM_S390_VM_CPU_FEAT_KSS	13
काष्ठा kvm_s390_vm_cpu_feat अणु
	__u64 feat[16];
पूर्ण;

#घोषणा KVM_S390_VM_CPU_PROCESSOR_SUBFUNC	4
#घोषणा KVM_S390_VM_CPU_MACHINE_SUBFUNC		5
/* क्रम "test bit" inकाष्ठाions MSB 0 bit ordering, क्रम "query" raw blocks */
काष्ठा kvm_s390_vm_cpu_subfunc अणु
	__u8 plo[32];		/* always */
	__u8 ptff[16];		/* with TOD-घड़ी steering */
	__u8 kmac[16];		/* with MSA */
	__u8 kmc[16];		/* with MSA */
	__u8 km[16];		/* with MSA */
	__u8 kimd[16];		/* with MSA */
	__u8 klmd[16];		/* with MSA */
	__u8 pckmo[16];		/* with MSA3 */
	__u8 kmctr[16];		/* with MSA4 */
	__u8 kmf[16];		/* with MSA4 */
	__u8 kmo[16];		/* with MSA4 */
	__u8 pcc[16];		/* with MSA4 */
	__u8 ppno[16];		/* with MSA5 */
	__u8 kma[16];		/* with MSA8 */
	__u8 kdsa[16];		/* with MSA9 */
	__u8 sortl[32];		/* with STFLE.150 */
	__u8 dfltcc[32];	/* with STFLE.151 */
	__u8 reserved[1728];
पूर्ण;

/* kvm attributes क्रम crypto */
#घोषणा KVM_S390_VM_CRYPTO_ENABLE_AES_KW	0
#घोषणा KVM_S390_VM_CRYPTO_ENABLE_DEA_KW	1
#घोषणा KVM_S390_VM_CRYPTO_DISABLE_AES_KW	2
#घोषणा KVM_S390_VM_CRYPTO_DISABLE_DEA_KW	3
#घोषणा KVM_S390_VM_CRYPTO_ENABLE_APIE		4
#घोषणा KVM_S390_VM_CRYPTO_DISABLE_APIE		5

/* kvm attributes क्रम migration mode */
#घोषणा KVM_S390_VM_MIGRATION_STOP	0
#घोषणा KVM_S390_VM_MIGRATION_START	1
#घोषणा KVM_S390_VM_MIGRATION_STATUS	2

/* क्रम KVM_GET_REGS and KVM_SET_REGS */
काष्ठा kvm_regs अणु
	/* general purpose regs क्रम s390 */
	__u64 gprs[16];
पूर्ण;

/* क्रम KVM_GET_SREGS and KVM_SET_SREGS */
काष्ठा kvm_sregs अणु
	__u32 acrs[16];
	__u64 crs[16];
पूर्ण;

/* क्रम KVM_GET_FPU and KVM_SET_FPU */
काष्ठा kvm_fpu अणु
	__u32 fpc;
	__u64 fprs[16];
पूर्ण;

#घोषणा KVM_GUESTDBG_USE_HW_BP		0x00010000

#घोषणा KVM_HW_BP			1
#घोषणा KVM_HW_WP_WRITE			2
#घोषणा KVM_SINGLESTEP			4

काष्ठा kvm_debug_निकास_arch अणु
	__u64 addr;
	__u8 type;
	__u8 pad[7]; /* Should be set to 0 */
पूर्ण;

काष्ठा kvm_hw_अवरोधpoपूर्णांक अणु
	__u64 addr;
	__u64 phys_addr;
	__u64 len;
	__u8 type;
	__u8 pad[7]; /* Should be set to 0 */
पूर्ण;

/* क्रम KVM_SET_GUEST_DEBUG */
काष्ठा kvm_guest_debug_arch अणु
	__u32 nr_hw_bp;
	__u32 pad; /* Should be set to 0 */
	काष्ठा kvm_hw_अवरोधpoपूर्णांक __user *hw_bp;
पूर्ण;

/* क्रम KVM_SYNC_PFAULT and KVM_REG_S390_PFTOKEN */
#घोषणा KVM_S390_PFAULT_TOKEN_INVALID	0xffffffffffffffffULL

#घोषणा KVM_SYNC_PREFIX (1UL << 0)
#घोषणा KVM_SYNC_GPRS   (1UL << 1)
#घोषणा KVM_SYNC_ACRS   (1UL << 2)
#घोषणा KVM_SYNC_CRS    (1UL << 3)
#घोषणा KVM_SYNC_ARCH0  (1UL << 4)
#घोषणा KVM_SYNC_PFAULT (1UL << 5)
#घोषणा KVM_SYNC_VRS    (1UL << 6)
#घोषणा KVM_SYNC_RICCB  (1UL << 7)
#घोषणा KVM_SYNC_FPRS   (1UL << 8)
#घोषणा KVM_SYNC_GSCB   (1UL << 9)
#घोषणा KVM_SYNC_BPBC   (1UL << 10)
#घोषणा KVM_SYNC_ETOKEN (1UL << 11)
#घोषणा KVM_SYNC_DIAG318 (1UL << 12)

#घोषणा KVM_SYNC_S390_VALID_FIELDS \
	(KVM_SYNC_PREFIX | KVM_SYNC_GPRS | KVM_SYNC_ACRS | KVM_SYNC_CRS | \
	 KVM_SYNC_ARCH0 | KVM_SYNC_PFAULT | KVM_SYNC_VRS | KVM_SYNC_RICCB | \
	 KVM_SYNC_FPRS | KVM_SYNC_GSCB | KVM_SYNC_BPBC | KVM_SYNC_ETOKEN | \
	 KVM_SYNC_DIAG318)

/* length and alignment of the sdnx as a घातer of two */
#घोषणा SDNXC 8
#घोषणा SDNXL (1UL << SDNXC)
/* definition of रेजिस्टरs in kvm_run */
काष्ठा kvm_sync_regs अणु
	__u64 prefix;	/* prefix रेजिस्टर */
	__u64 gprs[16];	/* general purpose रेजिस्टरs */
	__u32 acrs[16];	/* access रेजिस्टरs */
	__u64 crs[16];	/* control रेजिस्टरs */
	__u64 todpr;	/* tod programmable रेजिस्टर [ARCH0] */
	__u64 cpuपंचांग;	/* cpu समयr [ARCH0] */
	__u64 ckc;	/* घड़ी comparator [ARCH0] */
	__u64 pp;	/* program parameter [ARCH0] */
	__u64 gbea;	/* guest अवरोधing-event address [ARCH0] */
	__u64 pft;	/* pfault token [PFAULT] */
	__u64 pfs;	/* pfault select [PFAULT] */
	__u64 pfc;	/* pfault compare [PFAULT] */
	जोड़ अणु
		__u64 vrs[32][2];	/* vector रेजिस्टरs (KVM_SYNC_VRS) */
		__u64 fprs[16];		/* fp रेजिस्टरs (KVM_SYNC_FPRS) */
	पूर्ण;
	__u8  reserved[512];	/* क्रम future vector expansion */
	__u32 fpc;		/* valid on KVM_SYNC_VRS or KVM_SYNC_FPRS */
	__u8 bpbc : 1;		/* bp mode */
	__u8 reserved2 : 7;
	__u8 padding1[51];	/* riccb needs to be 64byte aligned */
	__u8 riccb[64];		/* runसमय instrumentation controls block */
	__u64 diag318;		/* diagnose 0x318 info */
	__u8 padding2[184];	/* sdnx needs to be 256byte aligned */
	जोड़ अणु
		__u8 sdnx[SDNXL];  /* state description annex */
		काष्ठा अणु
			__u64 reserved1[2];
			__u64 gscb[4];
			__u64 etoken;
			__u64 etoken_extension;
		पूर्ण;
	पूर्ण;
पूर्ण;

#घोषणा KVM_REG_S390_TODPR	(KVM_REG_S390 | KVM_REG_SIZE_U32 | 0x1)
#घोषणा KVM_REG_S390_EPOCHDIFF	(KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x2)
#घोषणा KVM_REG_S390_CPU_TIMER  (KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x3)
#घोषणा KVM_REG_S390_CLOCK_COMP (KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x4)
#घोषणा KVM_REG_S390_PFTOKEN	(KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x5)
#घोषणा KVM_REG_S390_PFCOMPARE	(KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x6)
#घोषणा KVM_REG_S390_PFSELECT	(KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x7)
#घोषणा KVM_REG_S390_PP		(KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x8)
#घोषणा KVM_REG_S390_GBEA	(KVM_REG_S390 | KVM_REG_SIZE_U64 | 0x9)
#पूर्ण_अगर
