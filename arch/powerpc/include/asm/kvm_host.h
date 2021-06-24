<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright IBM Corp. 2007
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#अगर_अघोषित __POWERPC_KVM_HOST_H__
#घोषणा __POWERPC_KVM_HOST_H__

#समावेश <linux/mutex.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/kvm_types.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/list.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/mce.h>

#घोषणा KVM_MAX_VCPUS		NR_CPUS
#घोषणा KVM_MAX_VCORES		NR_CPUS

#समावेश <यंत्र/cputhपढ़ोs.h>

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
#समावेश <यंत्र/kvm_book3s_यंत्र.h>		/* क्रम MAX_SMT_THREADS */
#घोषणा KVM_MAX_VCPU_ID		(MAX_SMT_THREADS * KVM_MAX_VCORES)
#घोषणा KVM_MAX_NESTED_GUESTS	KVMPPC_NR_LPIDS

#अन्यथा
#घोषणा KVM_MAX_VCPU_ID		KVM_MAX_VCPUS
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */

#घोषणा __KVM_HAVE_ARCH_INTC_INITIALIZED

#घोषणा KVM_HALT_POLL_NS_DEFAULT 10000	/* 10 us */

/* These values are पूर्णांकernal and can be increased later */
#घोषणा KVM_NR_IRQCHIPS          1
#घोषणा KVM_IRQCHIP_NUM_PINS     256

/* PPC-specअगरic vcpu->requests bit members */
#घोषणा KVM_REQ_WATCHDOG	KVM_ARCH_REQ(0)
#घोषणा KVM_REQ_EPR_EXIT	KVM_ARCH_REQ(1)
#घोषणा KVM_REQ_PENDING_TIMER	KVM_ARCH_REQ(2)

#समावेश <linux/mmu_notअगरier.h>

#घोषणा KVM_ARCH_WANT_MMU_NOTIFIER

#घोषणा HPTEG_CACHE_NUM			(1 << 15)
#घोषणा HPTEG_HASH_BITS_PTE		13
#घोषणा HPTEG_HASH_BITS_PTE_LONG	12
#घोषणा HPTEG_HASH_BITS_VPTE		13
#घोषणा HPTEG_HASH_BITS_VPTE_LONG	5
#घोषणा HPTEG_HASH_BITS_VPTE_64K	11
#घोषणा HPTEG_HASH_NUM_PTE		(1 << HPTEG_HASH_BITS_PTE)
#घोषणा HPTEG_HASH_NUM_PTE_LONG		(1 << HPTEG_HASH_BITS_PTE_LONG)
#घोषणा HPTEG_HASH_NUM_VPTE		(1 << HPTEG_HASH_BITS_VPTE)
#घोषणा HPTEG_HASH_NUM_VPTE_LONG	(1 << HPTEG_HASH_BITS_VPTE_LONG)
#घोषणा HPTEG_HASH_NUM_VPTE_64K		(1 << HPTEG_HASH_BITS_VPTE_64K)

/* Physical Address Mask - allowed range of real mode RAM access */
#घोषणा KVM_PAM			0x0fffffffffffffffULL

काष्ठा lppaca;
काष्ठा slb_shaकरोw;
काष्ठा dtl_entry;

काष्ठा kvmppc_vcpu_book3s;
काष्ठा kvmppc_book3s_shaकरोw_vcpu;
काष्ठा kvm_nested_guest;

काष्ठा kvm_vm_stat अणु
	uदीर्घ remote_tlb_flush;
	uदीर्घ num_2M_pages;
	uदीर्घ num_1G_pages;
पूर्ण;

काष्ठा kvm_vcpu_stat अणु
	u64 sum_निकासs;
	u64 mmio_निकासs;
	u64 संकेत_निकासs;
	u64 light_निकासs;
	/* Account क्रम special types of light निकासs: */
	u64 itlb_real_miss_निकासs;
	u64 itlb_virt_miss_निकासs;
	u64 dtlb_real_miss_निकासs;
	u64 dtlb_virt_miss_निकासs;
	u64 syscall_निकासs;
	u64 isi_निकासs;
	u64 dsi_निकासs;
	u64 emulated_inst_निकासs;
	u64 dec_निकासs;
	u64 ext_पूर्णांकr_निकासs;
	u64 halt_poll_success_ns;
	u64 halt_poll_fail_ns;
	u64 halt_रुको_ns;
	u64 halt_successful_poll;
	u64 halt_attempted_poll;
	u64 halt_successful_रुको;
	u64 halt_poll_invalid;
	u64 halt_wakeup;
	u64 dbell_निकासs;
	u64 gdbell_निकासs;
	u64 ld;
	u64 st;
#अगर_घोषित CONFIG_PPC_BOOK3S
	u64 pf_storage;
	u64 pf_instruc;
	u64 sp_storage;
	u64 sp_instruc;
	u64 queue_पूर्णांकr;
	u64 ld_slow;
	u64 st_slow;
#पूर्ण_अगर
	u64 pthru_all;
	u64 pthru_host;
	u64 pthru_bad_aff;
पूर्ण;

क्रमागत kvm_निकास_types अणु
	MMIO_EXITS,
	SIGNAL_EXITS,
	ITLB_REAL_MISS_EXITS,
	ITLB_VIRT_MISS_EXITS,
	DTLB_REAL_MISS_EXITS,
	DTLB_VIRT_MISS_EXITS,
	SYSCALL_EXITS,
	ISI_EXITS,
	DSI_EXITS,
	EMULATED_INST_EXITS,
	EMULATED_MTMSRWE_EXITS,
	EMULATED_WRTEE_EXITS,
	EMULATED_MTSPR_EXITS,
	EMULATED_MFSPR_EXITS,
	EMULATED_MTMSR_EXITS,
	EMULATED_MFMSR_EXITS,
	EMULATED_TLBSX_EXITS,
	EMULATED_TLBWE_EXITS,
	EMULATED_RFI_EXITS,
	EMULATED_RFCI_EXITS,
	EMULATED_RFDI_EXITS,
	DEC_EXITS,
	EXT_INTR_EXITS,
	HALT_WAKEUP,
	USR_PR_INST,
	FP_UNAVAIL,
	DEBUG_EXITS,
	TIMEINGUEST,
	DBELL_EXITS,
	GDBELL_EXITS,
	__NUMBER_OF_KVM_EXIT_TYPES
पूर्ण;

/* allow access to big endian 32bit upper/lower parts and 64bit var */
काष्ठा kvmppc_निकास_timing अणु
	जोड़ अणु
		u64 tv64;
		काष्ठा अणु
			u32 tbu, tbl;
		पूर्ण tv32;
	पूर्ण;
पूर्ण;

काष्ठा kvmppc_pginfo अणु
	अचिन्हित दीर्घ pfn;
	atomic_t refcnt;
पूर्ण;

काष्ठा kvmppc_spapr_tce_iommu_table अणु
	काष्ठा rcu_head rcu;
	काष्ठा list_head next;
	काष्ठा iommu_table *tbl;
	काष्ठा kref kref;
पूर्ण;

#घोषणा TCES_PER_PAGE	(PAGE_SIZE / माप(u64))

काष्ठा kvmppc_spapr_tce_table अणु
	काष्ठा list_head list;
	काष्ठा kvm *kvm;
	u64 liobn;
	काष्ठा rcu_head rcu;
	u32 page_shअगरt;
	u64 offset;		/* in pages */
	u64 size;		/* winकरोw size in pages */
	काष्ठा list_head iommu_tables;
	काष्ठा mutex alloc_lock;
	काष्ठा page *pages[0];
पूर्ण;

/* XICS components, defined in book3s_xics.c */
काष्ठा kvmppc_xics;
काष्ठा kvmppc_icp;
बाह्य काष्ठा kvm_device_ops kvm_xics_ops;

/* XIVE components, defined in book3s_xive.c */
काष्ठा kvmppc_xive;
काष्ठा kvmppc_xive_vcpu;
बाह्य काष्ठा kvm_device_ops kvm_xive_ops;
बाह्य काष्ठा kvm_device_ops kvm_xive_native_ops;

काष्ठा kvmppc_passthru_irqmap;

/*
 * The reverse mapping array has one entry क्रम each HPTE,
 * which stores the guest's view of the second word of the HPTE
 * (including the guest physical address of the mapping),
 * plus क्रमward and backward poपूर्णांकers in a करोubly-linked ring
 * of HPTEs that map the same host page.  The poपूर्णांकers in this
 * ring are 32-bit HPTE indexes, to save space.
 */
काष्ठा revmap_entry अणु
	अचिन्हित दीर्घ guest_rpte;
	अचिन्हित पूर्णांक क्रमw, back;
पूर्ण;

/*
 * The rmap array of size number of guest pages is allocated क्रम each memslot.
 * This array is used to store usage specअगरic inक्रमmation about the guest page.
 * Below are the encodings of the various possible usage types.
 */
/* Free bits which can be used to define a new usage */
#घोषणा KVMPPC_RMAP_TYPE_MASK	0xff00000000000000
#घोषणा KVMPPC_RMAP_NESTED	0xc000000000000000	/* Nested rmap array */
#घोषणा KVMPPC_RMAP_HPT		0x0100000000000000	/* HPT guest */

/*
 * rmap usage definition क्रम a hash page table (hpt) guest:
 * 0x0000080000000000	Lock bit
 * 0x0000018000000000	RC bits
 * 0x0000000100000000	Present bit
 * 0x00000000ffffffff	HPT index bits
 * The bottom 32 bits are the index in the guest HPT of a HPTE that poपूर्णांकs to
 * the page.
 */
#घोषणा KVMPPC_RMAP_LOCK_BIT	43
#घोषणा KVMPPC_RMAP_RC_SHIFT	32
#घोषणा KVMPPC_RMAP_REFERENCED	(HPTE_R_R << KVMPPC_RMAP_RC_SHIFT)
#घोषणा KVMPPC_RMAP_PRESENT	0x100000000ul
#घोषणा KVMPPC_RMAP_INDEX	0xfffffffful

काष्ठा kvm_arch_memory_slot अणु
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	अचिन्हित दीर्घ *rmap;
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */
पूर्ण;

काष्ठा kvm_hpt_info अणु
	/* Host भव (linear mapping) address of guest HPT */
	अचिन्हित दीर्घ virt;
	/* Array of reverse mapping entries क्रम each guest HPTE */
	काष्ठा revmap_entry *rev;
	/* Guest HPT size is 2**(order) bytes */
	u32 order;
	/* 1 अगर HPT allocated with CMA, 0 otherwise */
	पूर्णांक cma;
पूर्ण;

काष्ठा kvm_resize_hpt;

/* Flag values क्रम kvm_arch.secure_guest */
#घोषणा KVMPPC_SECURE_INIT_START 0x1 /* H_SVM_INIT_START has been called */
#घोषणा KVMPPC_SECURE_INIT_DONE  0x2 /* H_SVM_INIT_DONE completed */
#घोषणा KVMPPC_SECURE_INIT_ABORT 0x4 /* H_SVM_INIT_ABORT issued */

काष्ठा kvm_arch अणु
	अचिन्हित पूर्णांक lpid;
	अचिन्हित पूर्णांक smt_mode;		/* # vcpus per भव core */
	अचिन्हित पूर्णांक emul_smt_mode;	/* emualted SMT mode, on P9 */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	अचिन्हित पूर्णांक tlb_sets;
	काष्ठा kvm_hpt_info hpt;
	atomic64_t mmio_update;
	अचिन्हित पूर्णांक host_lpid;
	अचिन्हित दीर्घ host_lpcr;
	अचिन्हित दीर्घ sdr1;
	अचिन्हित दीर्घ host_sdr1;
	अचिन्हित दीर्घ lpcr;
	अचिन्हित दीर्घ vrma_slb_v;
	पूर्णांक mmu_पढ़ोy;
	atomic_t vcpus_running;
	u32 online_vcores;
	atomic_t hpte_mod_पूर्णांकerest;
	cpumask_t need_tlb_flush;
	cpumask_t cpu_in_guest;
	u8 radix;
	u8 fwnmi_enabled;
	u8 secure_guest;
	u8 svm_enabled;
	bool thपढ़ोs_indep;
	bool nested_enable;
	bool dawr1_enabled;
	pgd_t *pgtable;
	u64 process_table;
	काष्ठा dentry *debugfs_dir;
	काष्ठा kvm_resize_hpt *resize_hpt; /* रक्षित by kvm->lock */
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */
#अगर_घोषित CONFIG_KVM_BOOK3S_PR_POSSIBLE
	काष्ठा mutex hpt_mutex;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा list_head spapr_tce_tables;
	काष्ठा list_head rtas_tokens;
	काष्ठा mutex rtas_token_lock;
	DECLARE_BITMAP(enabled_hcalls, MAX_HCALL_OPCODE/4 + 1);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_MPIC
	काष्ठा खोलोpic *mpic;
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_XICS
	काष्ठा kvmppc_xics *xics;
	काष्ठा kvmppc_xics *xics_device;
	काष्ठा kvmppc_xive *xive;    /* Current XIVE device in use */
	काष्ठा अणु
		काष्ठा kvmppc_xive *native;
		काष्ठा kvmppc_xive *xics_on_xive;
	पूर्ण xive_devices;
	काष्ठा kvmppc_passthru_irqmap *pimap;
#पूर्ण_अगर
	काष्ठा kvmppc_ops *kvm_ops;
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	काष्ठा mutex uvmem_lock;
	काष्ठा list_head uvmem_pfns;
	काष्ठा mutex mmu_setup_lock;	/* nests inside vcpu mutexes */
	u64 l1_ptcr;
	पूर्णांक max_nested_lpid;
	काष्ठा kvm_nested_guest *nested_guests[KVM_MAX_NESTED_GUESTS];
	/* This array can grow quite large, keep it at the end */
	काष्ठा kvmppc_vcore *vcores[KVM_MAX_VCORES];
#पूर्ण_अगर
पूर्ण;

#घोषणा VCORE_ENTRY_MAP(vc)	((vc)->entry_निकास_map & 0xff)
#घोषणा VCORE_EXIT_MAP(vc)	((vc)->entry_निकास_map >> 8)
#घोषणा VCORE_IS_EXITING(vc)	(VCORE_EXIT_MAP(vc) != 0)

/* This bit is used when a vcore निकास is triggered from outside the vcore */
#घोषणा VCORE_EXIT_REQ		0x10000

/*
 * Values क्रम vcore_state.
 * Note that these are arranged such that lower values
 * (< VCORE_SLEEPING) करोn't require stolen समय accounting
 * on load/unload, and higher values करो.
 */
#घोषणा VCORE_INACTIVE	0
#घोषणा VCORE_PREEMPT	1
#घोषणा VCORE_PIGGYBACK	2
#घोषणा VCORE_SLEEPING	3
#घोषणा VCORE_RUNNING	4
#घोषणा VCORE_EXITING	5
#घोषणा VCORE_POLLING	6

/*
 * Struct used to manage memory क्रम a भव processor area
 * रेजिस्टरed by a PAPR guest.  There are three types of area
 * that a guest can रेजिस्टर.
 */
काष्ठा kvmppc_vpa अणु
	अचिन्हित दीर्घ gpa;	/* Current guest phys addr */
	व्योम *pinned_addr;	/* Address in kernel linear mapping */
	व्योम *pinned_end;	/* End of region */
	अचिन्हित दीर्घ next_gpa;	/* Guest phys addr क्रम update */
	अचिन्हित दीर्घ len;	/* Number of bytes required */
	u8 update_pending;	/* 1 => update pinned_addr from next_gpa */
	bool dirty;		/* true => area has been modअगरied by kernel */
पूर्ण;

काष्ठा kvmppc_pte अणु
	uदीर्घ eaddr;
	u64 vpage;
	uदीर्घ raddr;
	bool may_पढ़ो		: 1;
	bool may_ग_लिखो		: 1;
	bool may_execute	: 1;
	अचिन्हित दीर्घ wimg;
	अचिन्हित दीर्घ rc;
	u8 page_size;		/* MMU_PAGE_xxx */
	u8 page_shअगरt;
पूर्ण;

काष्ठा kvmppc_mmu अणु
	/* book3s_64 only */
	व्योम (*slbmte)(काष्ठा kvm_vcpu *vcpu, u64 rb, u64 rs);
	u64  (*slbmfee)(काष्ठा kvm_vcpu *vcpu, u64 slb_nr);
	u64  (*slbmfev)(काष्ठा kvm_vcpu *vcpu, u64 slb_nr);
	पूर्णांक  (*slbfee)(काष्ठा kvm_vcpu *vcpu, gva_t eaddr, uदीर्घ *ret_slb);
	व्योम (*slbie)(काष्ठा kvm_vcpu *vcpu, u64 slb_nr);
	व्योम (*slbia)(काष्ठा kvm_vcpu *vcpu);
	/* book3s */
	व्योम (*mtsrin)(काष्ठा kvm_vcpu *vcpu, u32 srnum, uदीर्घ value);
	u32  (*mfsrin)(काष्ठा kvm_vcpu *vcpu, u32 srnum);
	पूर्णांक  (*xlate)(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
		      काष्ठा kvmppc_pte *pte, bool data, bool isग_लिखो);
	व्योम (*tlbie)(काष्ठा kvm_vcpu *vcpu, uदीर्घ addr, bool large);
	पूर्णांक  (*esid_to_vsid)(काष्ठा kvm_vcpu *vcpu, uदीर्घ esid, u64 *vsid);
	u64  (*ea_to_vp)(काष्ठा kvm_vcpu *vcpu, gva_t eaddr, bool data);
	bool (*is_dcbz32)(काष्ठा kvm_vcpu *vcpu);
पूर्ण;

काष्ठा kvmppc_slb अणु
	u64 esid;
	u64 vsid;
	u64 orige;
	u64 origv;
	bool valid	: 1;
	bool Ks		: 1;
	bool Kp		: 1;
	bool nx		: 1;
	bool large	: 1;	/* PTEs are 16MB */
	bool tb		: 1;	/* 1TB segment */
	bool class	: 1;
	u8 base_page_size;	/* MMU_PAGE_xxx */
पूर्ण;

/* Struct used to accumulate timing inक्रमmation in HV real mode code */
काष्ठा kvmhv_tb_accumulator अणु
	u64	seqcount;	/* used to synchronize access, also count * 2 */
	u64	tb_total;	/* total समय in समयbase ticks */
	u64	tb_min;		/* min समय */
	u64	tb_max;		/* max समय */
पूर्ण;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
काष्ठा kvmppc_irq_map अणु
	u32	r_hwirq;
	u32	v_hwirq;
	काष्ठा irq_desc *desc;
पूर्ण;

#घोषणा	KVMPPC_PIRQ_MAPPED	1024
काष्ठा kvmppc_passthru_irqmap अणु
	पूर्णांक n_mapped;
	काष्ठा kvmppc_irq_map mapped[KVMPPC_PIRQ_MAPPED];
पूर्ण;
#पूर्ण_अगर

# अगरdef CONFIG_PPC_FSL_BOOK3E
#घोषणा KVMPPC_BOOKE_IAC_NUM	2
#घोषणा KVMPPC_BOOKE_DAC_NUM	2
# अन्यथा
#घोषणा KVMPPC_BOOKE_IAC_NUM	4
#घोषणा KVMPPC_BOOKE_DAC_NUM	2
# endअगर
#घोषणा KVMPPC_BOOKE_MAX_IAC	4
#घोषणा KVMPPC_BOOKE_MAX_DAC	2

/* KVMPPC_EPR_USER takes precedence over KVMPPC_EPR_KERNEL */
#घोषणा KVMPPC_EPR_NONE		0 /* EPR not supported */
#घोषणा KVMPPC_EPR_USER		1 /* निकास to userspace to fill EPR */
#घोषणा KVMPPC_EPR_KERNEL	2 /* in-kernel irqchip */

#घोषणा KVMPPC_IRQ_DEFAULT	0
#घोषणा KVMPPC_IRQ_MPIC		1
#घोषणा KVMPPC_IRQ_XICS		2 /* Includes a XIVE option */
#घोषणा KVMPPC_IRQ_XIVE		3 /* XIVE native exploitation mode */

#घोषणा MMIO_HPTE_CACHE_SIZE	4

काष्ठा mmio_hpte_cache_entry अणु
	अचिन्हित दीर्घ hpte_v;
	अचिन्हित दीर्घ hpte_r;
	अचिन्हित दीर्घ rpte;
	अचिन्हित दीर्घ pte_index;
	अचिन्हित दीर्घ eaddr;
	अचिन्हित दीर्घ slb_v;
	दीर्घ mmio_update;
	अचिन्हित पूर्णांक slb_base_pshअगरt;
पूर्ण;

काष्ठा mmio_hpte_cache अणु
	काष्ठा mmio_hpte_cache_entry entry[MMIO_HPTE_CACHE_SIZE];
	अचिन्हित पूर्णांक index;
पूर्ण;

#घोषणा KVMPPC_VSX_COPY_NONE		0
#घोषणा KVMPPC_VSX_COPY_WORD		1
#घोषणा KVMPPC_VSX_COPY_DWORD		2
#घोषणा KVMPPC_VSX_COPY_DWORD_LOAD_DUMP	3
#घोषणा KVMPPC_VSX_COPY_WORD_LOAD_DUMP	4

#घोषणा KVMPPC_VMX_COPY_BYTE		8
#घोषणा KVMPPC_VMX_COPY_HWORD		9
#घोषणा KVMPPC_VMX_COPY_WORD		10
#घोषणा KVMPPC_VMX_COPY_DWORD		11

काष्ठा खोलोpic;

/* W0 and W1 of a XIVE thपढ़ो management context */
जोड़ xive_पंचांगa_w01 अणु
	काष्ठा अणु
		u8	nsr;
		u8	cppr;
		u8	ipb;
		u8	lsmfb;
		u8	ack;
		u8	inc;
		u8	age;
		u8	pipr;
	पूर्ण;
	__be64 w01;
पूर्ण;

काष्ठा kvm_vcpu_arch अणु
	uदीर्घ host_stack;
	u32 host_pid;
#अगर_घोषित CONFIG_PPC_BOOK3S
	काष्ठा kvmppc_slb slb[64];
	पूर्णांक slb_max;		/* 1 + index of last valid entry in slb[] */
	पूर्णांक slb_nr;		/* total number of entries in SLB */
	काष्ठा kvmppc_mmu mmu;
	काष्ठा kvmppc_vcpu_book3s *book3s;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	काष्ठा kvmppc_book3s_shaकरोw_vcpu *shaकरोw_vcpu;
#पूर्ण_अगर

	काष्ठा pt_regs regs;

	काष्ठा thपढ़ो_fp_state fp;

#अगर_घोषित CONFIG_SPE
	uदीर्घ evr[32];
	uदीर्घ spefscr;
	uदीर्घ host_spefscr;
	u64 acc;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	काष्ठा thपढ़ो_vr_state vr;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	u32 host_mas4;
	u32 host_mas6;
	u32 shaकरोw_epcr;
	u32 shaकरोw_msrp;
	u32 eplc;
	u32 epsc;
	u32 oldpir;
#पूर्ण_अगर

#अगर defined(CONFIG_BOOKE)
#अगर defined(CONFIG_KVM_BOOKE_HV) || defined(CONFIG_64BIT)
	u32 epcr;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S
	/* For Gekko paired singles */
	u32 qpr[32];
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S
	uदीर्घ tar;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S
	uदीर्घ hflags;
	uदीर्घ guest_owned_ext;
	uदीर्घ purr;
	uदीर्घ spurr;
	uदीर्घ ic;
	uदीर्घ dscr;
	uदीर्घ amr;
	uदीर्घ uamor;
	uदीर्घ iamr;
	u32 ctrl;
	u32 dabrx;
	uदीर्घ dabr;
	uदीर्घ dawr0;
	uदीर्घ dawrx0;
	uदीर्घ dawr1;
	uदीर्घ dawrx1;
	uदीर्घ ciabr;
	uदीर्घ cfar;
	uदीर्घ ppr;
	u32 pspb;
	uदीर्घ fscr;
	uदीर्घ shaकरोw_fscr;
	uदीर्घ ebbhr;
	uदीर्घ ebbrr;
	uदीर्घ bescr;
	uदीर्घ csigr;
	uदीर्घ tacr;
	uदीर्घ tcscr;
	uदीर्घ acop;
	uदीर्घ wort;
	uदीर्घ tid;
	uदीर्घ psscr;
	uदीर्घ hfscr;
	uदीर्घ shaकरोw_srr1;
#पूर्ण_अगर
	u32 vrsave; /* also USPRG0 */
	u32 mmucr;
	/* shaकरोw_msr is unused क्रम BookE HV */
	uदीर्घ shaकरोw_msr;
	uदीर्घ csrr0;
	uदीर्घ csrr1;
	uदीर्घ dsrr0;
	uदीर्घ dsrr1;
	uदीर्घ mcsrr0;
	uदीर्घ mcsrr1;
	uदीर्घ mcsr;
	uदीर्घ dec;
#अगर_घोषित CONFIG_BOOKE
	u32 decar;
#पूर्ण_अगर
	/* Time base value when we entered the guest */
	u64 entry_tb;
	u64 entry_vtb;
	u64 entry_ic;
	u32 tcr;
	uदीर्घ tsr; /* we need to perक्रमm set/clr_bits() which requires uदीर्घ */
	u32 ivor[64];
	uदीर्घ ivpr;
	u32 pvr;

	u32 shaकरोw_pid;
	u32 shaकरोw_pid1;
	u32 pid;
	u32 swap_pid;

	u32 ccr0;
	u32 ccr1;
	u32 dbsr;

	u64 mmcr[4];	/* MMCR0, MMCR1, MMCR2, MMCR3 */
	u64 mmcra;
	u64 mmcrs;
	u32 pmc[8];
	u32 spmc[2];
	u64 siar;
	u64 sdar;
	u64 sier[3];
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	u64 tfhar;
	u64 texasr;
	u64 tfiar;
	u64 orig_texasr;

	u32 cr_पंचांग;
	u64 xer_पंचांग;
	u64 lr_पंचांग;
	u64 ctr_पंचांग;
	u64 amr_पंचांग;
	u64 ppr_पंचांग;
	u64 dscr_पंचांग;
	u64 tar_पंचांग;

	uदीर्घ gpr_पंचांग[32];

	काष्ठा thपढ़ो_fp_state fp_पंचांग;

	काष्ठा thपढ़ो_vr_state vr_पंचांग;
	u32 vrsave_पंचांग; /* also USPRG0 */
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_EXIT_TIMING
	काष्ठा mutex निकास_timing_lock;
	काष्ठा kvmppc_निकास_timing timing_निकास;
	काष्ठा kvmppc_निकास_timing timing_last_enter;
	u32 last_निकास_type;
	u32 timing_count_type[__NUMBER_OF_KVM_EXIT_TYPES];
	u64 timing_sum_duration[__NUMBER_OF_KVM_EXIT_TYPES];
	u64 timing_sum_quad_duration[__NUMBER_OF_KVM_EXIT_TYPES];
	u64 timing_min_duration[__NUMBER_OF_KVM_EXIT_TYPES];
	u64 timing_max_duration[__NUMBER_OF_KVM_EXIT_TYPES];
	u64 timing_last_निकास;
	काष्ठा dentry *debugfs_निकास_timing;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S
	uदीर्घ fault_dar;
	u32 fault_dsisr;
	अचिन्हित दीर्घ पूर्णांकr_msr;
	uदीर्घ fault_gpa;	/* guest real address of page fault (POWER9) */
#पूर्ण_अगर

#अगर_घोषित CONFIG_BOOKE
	uदीर्घ fault_dear;
	uदीर्घ fault_esr;
	uदीर्घ queued_dear;
	uदीर्घ queued_esr;
	spinlock_t wdt_lock;
	काष्ठा समयr_list wdt_समयr;
	u32 tlbcfg[4];
	u32 tlbps[4];
	u32 mmucfg;
	u32 eptcfg;
	u32 epr;
	u64 sprg9;
	u32 pwrmgtcr0;
	u32 crit_save;
	/* guest debug रेजिस्टरs*/
	काष्ठा debug_reg dbg_reg;
#पूर्ण_अगर
	gpa_t paddr_accessed;
	gva_t vaddr_accessed;
	pgd_t *pgdir;

	u16 io_gpr; /* GPR used as IO source/target */
	u8 mmio_host_swabbed;
	u8 mmio_sign_extend;
	/* conversion between single and द्विगुन precision */
	u8 mmio_sp64_extend;
	/*
	 * Number of simulations क्रम vsx.
	 * If we use 2*8bytes to simulate 1*16bytes,
	 * then the number should be 2 and
	 * mmio_copy_type=KVMPPC_VSX_COPY_DWORD.
	 * If we use 4*4bytes to simulate 1*16bytes,
	 * the number should be 4 and
	 * mmio_vsx_copy_type=KVMPPC_VSX_COPY_WORD.
	 */
	u8 mmio_vsx_copy_nums;
	u8 mmio_vsx_offset;
	u8 mmio_vmx_copy_nums;
	u8 mmio_vmx_offset;
	u8 mmio_copy_type;
	u8 osi_needed;
	u8 osi_enabled;
	u8 papr_enabled;
	u8 watchकरोg_enabled;
	u8 sane;
	u8 cpu_type;
	u8 hcall_needed;
	u8 epr_flags; /* KVMPPC_EPR_xxx */
	u8 epr_needed;
	u8 बाह्यal_oneshot;	/* clear बाह्यal irq after delivery */

	u32 cpr0_cfgaddr; /* holds the last set cpr0_cfgaddr */

	काष्ठा hrसमयr dec_समयr;
	u64 dec_jअगरfies;
	u64 dec_expires;
	अचिन्हित दीर्घ pending_exceptions;
	u8 ceded;
	u8 prodded;
	u8 करोorbell_request;
	u8 irq_pending; /* Used by XIVE to संकेत pending guest irqs */
	u32 last_inst;

	काष्ठा rcuरुको *रुकोp;
	काष्ठा kvmppc_vcore *vcore;
	पूर्णांक ret;
	पूर्णांक trap;
	पूर्णांक state;
	पूर्णांक ptid;
	पूर्णांक thपढ़ो_cpu;
	पूर्णांक prev_cpu;
	bool समयr_running;
	रुको_queue_head_t cpu_run;
	काष्ठा machine_check_event mce_evt; /* Valid अगर trap == 0x200 */

	काष्ठा kvm_vcpu_arch_shared *shared;
#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PR_POSSIBLE)
	bool shared_big_endian;
#पूर्ण_अगर
	अचिन्हित दीर्घ magic_page_pa; /* phys addr to map the magic page to */
	अचिन्हित दीर्घ magic_page_ea; /* effect. addr to map the magic page to */
	bool disable_kernel_nx;

	पूर्णांक irq_type;		/* one of KVM_IRQ_* */
	पूर्णांक irq_cpu_id;
	काष्ठा खोलोpic *mpic;	/* KVM_IRQ_MPIC */
#अगर_घोषित CONFIG_KVM_XICS
	काष्ठा kvmppc_icp *icp; /* XICS presentation controller */
	काष्ठा kvmppc_xive_vcpu *xive_vcpu; /* XIVE भव CPU data */
	__be32 xive_cam_word;    /* Cooked W2 in proper endian with valid bit */
	u8 xive_pushed;		 /* Is the VP pushed on the physical CPU ? */
	u8 xive_esc_on;		 /* Is the escalation irq enabled ? */
	जोड़ xive_पंचांगa_w01 xive_saved_state; /* W0..1 of XIVE thपढ़ो state */
	u64 xive_esc_raddr;	 /* Escalation पूर्णांकerrupt ESB real addr */
	u64 xive_esc_vaddr;	 /* Escalation पूर्णांकerrupt ESB virt addr */
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	काष्ठा kvm_vcpu_arch_shared shregs;

	काष्ठा mmio_hpte_cache mmio_cache;
	अचिन्हित दीर्घ pgfault_addr;
	दीर्घ pgfault_index;
	अचिन्हित दीर्घ pgfault_hpte[2];
	काष्ठा mmio_hpte_cache_entry *pgfault_cache;

	काष्ठा task_काष्ठा *run_task;

	spinlock_t vpa_update_lock;
	काष्ठा kvmppc_vpa vpa;
	काष्ठा kvmppc_vpa dtl;
	काष्ठा dtl_entry *dtl_ptr;
	अचिन्हित दीर्घ dtl_index;
	u64 stolen_logged;
	काष्ठा kvmppc_vpa slb_shaकरोw;

	spinlock_t tbacct_lock;
	u64 busy_stolen;
	u64 busy_preempt;

	u32 emul_inst;

	u32 online;

	/* For support of nested guests */
	काष्ठा kvm_nested_guest *nested;
	u32 nested_vcpu_id;
	gpa_t nested_io_gpr;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_EXIT_TIMING
	काष्ठा kvmhv_tb_accumulator *cur_activity;	/* What we're timing */
	u64	cur_tb_start;			/* when it started */
	काष्ठा kvmhv_tb_accumulator rm_entry;	/* real-mode entry code */
	काष्ठा kvmhv_tb_accumulator rm_पूर्णांकr;	/* real-mode पूर्णांकr handling */
	काष्ठा kvmhv_tb_accumulator rm_निकास;	/* real-mode निकास code */
	काष्ठा kvmhv_tb_accumulator guest_समय;	/* guest execution */
	काष्ठा kvmhv_tb_accumulator cede_समय;	/* समय napping inside guest */

	काष्ठा dentry *debugfs_dir;
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_EXIT_TIMING */
पूर्ण;

#घोषणा VCPU_FPR(vcpu, i)	(vcpu)->arch.fp.fpr[i][TS_FPROFFSET]
#घोषणा VCPU_VSX_FPR(vcpu, i, j)	((vcpu)->arch.fp.fpr[i][j])
#घोषणा VCPU_VSX_VR(vcpu, i)		((vcpu)->arch.vr.vr[i])

/* Values क्रम vcpu->arch.state */
#घोषणा KVMPPC_VCPU_NOTREADY		0
#घोषणा KVMPPC_VCPU_RUNNABLE		1
#घोषणा KVMPPC_VCPU_BUSY_IN_HOST	2

/* Values क्रम vcpu->arch.io_gpr */
#घोषणा KVM_MMIO_REG_MASK	0x003f
#घोषणा KVM_MMIO_REG_EXT_MASK	0xffc0
#घोषणा KVM_MMIO_REG_GPR	0x0000
#घोषणा KVM_MMIO_REG_FPR	0x0040
#घोषणा KVM_MMIO_REG_QPR	0x0080
#घोषणा KVM_MMIO_REG_FQPR	0x00c0
#घोषणा KVM_MMIO_REG_VSX	0x0100
#घोषणा KVM_MMIO_REG_VMX	0x0180
#घोषणा KVM_MMIO_REG_NESTED_GPR	0xffc0


#घोषणा __KVM_HAVE_ARCH_WQP
#घोषणा __KVM_HAVE_CREATE_DEVICE

अटल अंतरभूत व्योम kvm_arch_hardware_disable(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_hardware_unsetup(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sync_events(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_memslots_updated(काष्ठा kvm *kvm, u64 gen) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_flush_shaकरोw_all(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_निकास(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_blocking(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_block_finish(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण

#पूर्ण_अगर /* __POWERPC_KVM_HOST_H__ */
