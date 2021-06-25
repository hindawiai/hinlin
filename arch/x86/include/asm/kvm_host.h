<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * This header defines architecture specअगरic पूर्णांकerfaces, x86 version
 */

#अगर_अघोषित _ASM_X86_KVM_HOST_H
#घोषणा _ASM_X86_KVM_HOST_H

#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/irq.h>

#समावेश <linux/kvm.h>
#समावेश <linux/kvm_para.h>
#समावेश <linux/kvm_types.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/pvघड़ी_gtod.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/irqbypass.h>
#समावेश <linux/hyperv.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/pvघड़ी-abi.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/msr-index.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/kvm_page_track.h>
#समावेश <यंत्र/kvm_vcpu_regs.h>
#समावेश <यंत्र/hyperv-tlfs.h>

#घोषणा __KVM_HAVE_ARCH_VCPU_DEBUGFS

#घोषणा KVM_MAX_VCPUS 288
#घोषणा KVM_SOFT_MAX_VCPUS 240
#घोषणा KVM_MAX_VCPU_ID 1023
/* memory slots that are not exposed to userspace */
#घोषणा KVM_PRIVATE_MEM_SLOTS 3

#घोषणा KVM_HALT_POLL_NS_DEFAULT 200000

#घोषणा KVM_IRQCHIP_NUM_PINS  KVM_IOAPIC_NUM_PINS

#घोषणा KVM_सूचीTY_LOG_MANUAL_CAPS   (KVM_सूचीTY_LOG_MANUAL_PROTECT_ENABLE | \
					KVM_सूचीTY_LOG_INITIALLY_SET)

#घोषणा KVM_BUS_LOCK_DETECTION_VALID_MODE	(KVM_BUS_LOCK_DETECTION_OFF | \
						 KVM_BUS_LOCK_DETECTION_EXIT)

/* x86-specअगरic vcpu->requests bit members */
#घोषणा KVM_REQ_MIGRATE_TIMER		KVM_ARCH_REQ(0)
#घोषणा KVM_REQ_REPORT_TPR_ACCESS	KVM_ARCH_REQ(1)
#घोषणा KVM_REQ_TRIPLE_FAULT		KVM_ARCH_REQ(2)
#घोषणा KVM_REQ_MMU_SYNC		KVM_ARCH_REQ(3)
#घोषणा KVM_REQ_CLOCK_UPDATE		KVM_ARCH_REQ(4)
#घोषणा KVM_REQ_LOAD_MMU_PGD		KVM_ARCH_REQ(5)
#घोषणा KVM_REQ_EVENT			KVM_ARCH_REQ(6)
#घोषणा KVM_REQ_APF_HALT		KVM_ARCH_REQ(7)
#घोषणा KVM_REQ_STEAL_UPDATE		KVM_ARCH_REQ(8)
#घोषणा KVM_REQ_NMI			KVM_ARCH_REQ(9)
#घोषणा KVM_REQ_PMU			KVM_ARCH_REQ(10)
#घोषणा KVM_REQ_PMI			KVM_ARCH_REQ(11)
#घोषणा KVM_REQ_SMI			KVM_ARCH_REQ(12)
#घोषणा KVM_REQ_MASTERCLOCK_UPDATE	KVM_ARCH_REQ(13)
#घोषणा KVM_REQ_MCLOCK_INPROGRESS \
	KVM_ARCH_REQ_FLAGS(14, KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_SCAN_IOAPIC \
	KVM_ARCH_REQ_FLAGS(15, KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_GLOBAL_CLOCK_UPDATE	KVM_ARCH_REQ(16)
#घोषणा KVM_REQ_APIC_PAGE_RELOAD \
	KVM_ARCH_REQ_FLAGS(17, KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_HV_CRASH		KVM_ARCH_REQ(18)
#घोषणा KVM_REQ_IOAPIC_EOI_EXIT		KVM_ARCH_REQ(19)
#घोषणा KVM_REQ_HV_RESET		KVM_ARCH_REQ(20)
#घोषणा KVM_REQ_HV_EXIT			KVM_ARCH_REQ(21)
#घोषणा KVM_REQ_HV_STIMER		KVM_ARCH_REQ(22)
#घोषणा KVM_REQ_LOAD_EOI_EXITMAP	KVM_ARCH_REQ(23)
#घोषणा KVM_REQ_GET_NESTED_STATE_PAGES	KVM_ARCH_REQ(24)
#घोषणा KVM_REQ_APICV_UPDATE \
	KVM_ARCH_REQ_FLAGS(25, KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_TLB_FLUSH_CURRENT	KVM_ARCH_REQ(26)
#घोषणा KVM_REQ_HV_TLB_FLUSH \
	KVM_ARCH_REQ_FLAGS(27, KVM_REQUEST_NO_WAKEUP)
#घोषणा KVM_REQ_APF_READY		KVM_ARCH_REQ(28)
#घोषणा KVM_REQ_MSR_FILTER_CHANGED	KVM_ARCH_REQ(29)
#घोषणा KVM_REQ_UPDATE_CPU_सूचीTY_LOGGING \
	KVM_ARCH_REQ_FLAGS(30, KVM_REQUEST_WAIT | KVM_REQUEST_NO_WAKEUP)

#घोषणा CR0_RESERVED_BITS                                               \
	(~(अचिन्हित दीर्घ)(X86_CR0_PE | X86_CR0_MP | X86_CR0_EM | X86_CR0_TS \
			  | X86_CR0_ET | X86_CR0_NE | X86_CR0_WP | X86_CR0_AM \
			  | X86_CR0_NW | X86_CR0_CD | X86_CR0_PG))

#घोषणा CR4_RESERVED_BITS                                               \
	(~(अचिन्हित दीर्घ)(X86_CR4_VME | X86_CR4_PVI | X86_CR4_TSD | X86_CR4_DE\
			  | X86_CR4_PSE | X86_CR4_PAE | X86_CR4_MCE     \
			  | X86_CR4_PGE | X86_CR4_PCE | X86_CR4_OSFXSR | X86_CR4_PCIDE \
			  | X86_CR4_OSXSAVE | X86_CR4_SMEP | X86_CR4_FSGSBASE \
			  | X86_CR4_OSXMMEXCPT | X86_CR4_LA57 | X86_CR4_VMXE \
			  | X86_CR4_SMAP | X86_CR4_PKE | X86_CR4_UMIP))

#घोषणा CR8_RESERVED_BITS (~(अचिन्हित दीर्घ)X86_CR8_TPR)



#घोषणा INVALID_PAGE (~(hpa_t)0)
#घोषणा VALID_PAGE(x) ((x) != INVALID_PAGE)

#घोषणा UNMAPPED_GVA (~(gpa_t)0)
#घोषणा INVALID_GPA (~(gpa_t)0)

/* KVM Hugepage definitions क्रम x86 */
#घोषणा KVM_MAX_HUGEPAGE_LEVEL	PG_LEVEL_1G
#घोषणा KVM_NR_PAGE_SIZES	(KVM_MAX_HUGEPAGE_LEVEL - PG_LEVEL_4K + 1)
#घोषणा KVM_HPAGE_GFN_SHIFT(x)	(((x) - 1) * 9)
#घोषणा KVM_HPAGE_SHIFT(x)	(PAGE_SHIFT + KVM_HPAGE_GFN_SHIFT(x))
#घोषणा KVM_HPAGE_SIZE(x)	(1UL << KVM_HPAGE_SHIFT(x))
#घोषणा KVM_HPAGE_MASK(x)	(~(KVM_HPAGE_SIZE(x) - 1))
#घोषणा KVM_PAGES_PER_HPAGE(x)	(KVM_HPAGE_SIZE(x) / PAGE_SIZE)

अटल अंतरभूत gfn_t gfn_to_index(gfn_t gfn, gfn_t base_gfn, पूर्णांक level)
अणु
	/* KVM_HPAGE_GFN_SHIFT(PG_LEVEL_4K) must be 0. */
	वापस (gfn >> KVM_HPAGE_GFN_SHIFT(level)) -
		(base_gfn >> KVM_HPAGE_GFN_SHIFT(level));
पूर्ण

#घोषणा KVM_PERMILLE_MMU_PAGES 20
#घोषणा KVM_MIN_ALLOC_MMU_PAGES 64UL
#घोषणा KVM_MMU_HASH_SHIFT 12
#घोषणा KVM_NUM_MMU_PAGES (1 << KVM_MMU_HASH_SHIFT)
#घोषणा KVM_MIN_FREE_MMU_PAGES 5
#घोषणा KVM_REFILL_PAGES 25
#घोषणा KVM_MAX_CPUID_ENTRIES 256
#घोषणा KVM_NR_FIXED_MTRR_REGION 88
#घोषणा KVM_NR_VAR_MTRR 8

#घोषणा ASYNC_PF_PER_VCPU 64

क्रमागत kvm_reg अणु
	VCPU_REGS_RAX = __VCPU_REGS_RAX,
	VCPU_REGS_RCX = __VCPU_REGS_RCX,
	VCPU_REGS_RDX = __VCPU_REGS_RDX,
	VCPU_REGS_RBX = __VCPU_REGS_RBX,
	VCPU_REGS_RSP = __VCPU_REGS_RSP,
	VCPU_REGS_RBP = __VCPU_REGS_RBP,
	VCPU_REGS_RSI = __VCPU_REGS_RSI,
	VCPU_REGS_RDI = __VCPU_REGS_RDI,
#अगर_घोषित CONFIG_X86_64
	VCPU_REGS_R8  = __VCPU_REGS_R8,
	VCPU_REGS_R9  = __VCPU_REGS_R9,
	VCPU_REGS_R10 = __VCPU_REGS_R10,
	VCPU_REGS_R11 = __VCPU_REGS_R11,
	VCPU_REGS_R12 = __VCPU_REGS_R12,
	VCPU_REGS_R13 = __VCPU_REGS_R13,
	VCPU_REGS_R14 = __VCPU_REGS_R14,
	VCPU_REGS_R15 = __VCPU_REGS_R15,
#पूर्ण_अगर
	VCPU_REGS_RIP,
	NR_VCPU_REGS,

	VCPU_EXREG_PDPTR = NR_VCPU_REGS,
	VCPU_EXREG_CR0,
	VCPU_EXREG_CR3,
	VCPU_EXREG_CR4,
	VCPU_EXREG_RFLAGS,
	VCPU_EXREG_SEGMENTS,
	VCPU_EXREG_EXIT_INFO_1,
	VCPU_EXREG_EXIT_INFO_2,
पूर्ण;

क्रमागत अणु
	VCPU_SREG_ES,
	VCPU_SREG_CS,
	VCPU_SREG_SS,
	VCPU_SREG_DS,
	VCPU_SREG_FS,
	VCPU_SREG_GS,
	VCPU_SREG_TR,
	VCPU_SREG_LDTR,
पूर्ण;

क्रमागत निकास_fastpath_completion अणु
	EXIT_FASTPATH_NONE,
	EXIT_FASTPATH_REENTER_GUEST,
	EXIT_FASTPATH_EXIT_HANDLED,
पूर्ण;
प्रकार क्रमागत निकास_fastpath_completion fastpath_t;

काष्ठा x86_emulate_ctxt;
काष्ठा x86_exception;
क्रमागत x86_पूर्णांकercept;
क्रमागत x86_पूर्णांकercept_stage;

#घोषणा KVM_NR_DB_REGS	4

#घोषणा DR6_BUS_LOCK   (1 << 11)
#घोषणा DR6_BD		(1 << 13)
#घोषणा DR6_BS		(1 << 14)
#घोषणा DR6_BT		(1 << 15)
#घोषणा DR6_RTM		(1 << 16)
/*
 * DR6_ACTIVE_LOW combines fixed-1 and active-low bits.
 * We can regard all the bits in DR6_FIXED_1 as active_low bits;
 * they will never be 0 क्रम now, but when they are defined
 * in the future it will require no code change.
 *
 * DR6_ACTIVE_LOW is also used as the init/reset value क्रम DR6.
 */
#घोषणा DR6_ACTIVE_LOW	0xffff0ff0
#घोषणा DR6_VOLATILE	0x0001e80f
#घोषणा DR6_FIXED_1	(DR6_ACTIVE_LOW & ~DR6_VOLATILE)

#घोषणा DR7_BP_EN_MASK	0x000000ff
#घोषणा DR7_GE		(1 << 9)
#घोषणा DR7_GD		(1 << 13)
#घोषणा DR7_FIXED_1	0x00000400
#घोषणा DR7_VOLATILE	0xffff2bff

#घोषणा KVM_GUESTDBG_VALID_MASK \
	(KVM_GUESTDBG_ENABLE | \
	KVM_GUESTDBG_SINGLESTEP | \
	KVM_GUESTDBG_USE_HW_BP | \
	KVM_GUESTDBG_USE_SW_BP | \
	KVM_GUESTDBG_INJECT_BP | \
	KVM_GUESTDBG_INJECT_DB)


#घोषणा PFERR_PRESENT_BIT 0
#घोषणा PFERR_WRITE_BIT 1
#घोषणा PFERR_USER_BIT 2
#घोषणा PFERR_RSVD_BIT 3
#घोषणा PFERR_FETCH_BIT 4
#घोषणा PFERR_PK_BIT 5
#घोषणा PFERR_SGX_BIT 15
#घोषणा PFERR_GUEST_FINAL_BIT 32
#घोषणा PFERR_GUEST_PAGE_BIT 33

#घोषणा PFERR_PRESENT_MASK (1U << PFERR_PRESENT_BIT)
#घोषणा PFERR_WRITE_MASK (1U << PFERR_WRITE_BIT)
#घोषणा PFERR_USER_MASK (1U << PFERR_USER_BIT)
#घोषणा PFERR_RSVD_MASK (1U << PFERR_RSVD_BIT)
#घोषणा PFERR_FETCH_MASK (1U << PFERR_FETCH_BIT)
#घोषणा PFERR_PK_MASK (1U << PFERR_PK_BIT)
#घोषणा PFERR_SGX_MASK (1U << PFERR_SGX_BIT)
#घोषणा PFERR_GUEST_FINAL_MASK (1ULL << PFERR_GUEST_FINAL_BIT)
#घोषणा PFERR_GUEST_PAGE_MASK (1ULL << PFERR_GUEST_PAGE_BIT)

#घोषणा PFERR_NESTED_GUEST_PAGE (PFERR_GUEST_PAGE_MASK |	\
				 PFERR_WRITE_MASK |		\
				 PFERR_PRESENT_MASK)

/* apic attention bits */
#घोषणा KVM_APIC_CHECK_VAPIC	0
/*
 * The following bit is set with PV-EOI, unset on EOI.
 * We detect PV-EOI changes by guest by comparing
 * this bit with PV-EOI in guest memory.
 * See the implementation in apic_update_pv_eoi.
 */
#घोषणा KVM_APIC_PV_EOI_PENDING	1

काष्ठा kvm_kernel_irq_routing_entry;

/*
 * the pages used as guest page table on soft mmu are tracked by
 * kvm_memory_slot.arch.gfn_track which is 16 bits, so the role bits used
 * by indirect shaकरोw page can not be more than 15 bits.
 *
 * Currently, we used 14 bits that are @level, @gpte_is_8_bytes, @quadrant, @access,
 * @nxe, @cr0_wp, @smep_andnot_wp and @smap_andnot_wp.
 */
जोड़ kvm_mmu_page_role अणु
	u32 word;
	काष्ठा अणु
		अचिन्हित level:4;
		अचिन्हित gpte_is_8_bytes:1;
		अचिन्हित quadrant:2;
		अचिन्हित direct:1;
		अचिन्हित access:3;
		अचिन्हित invalid:1;
		अचिन्हित nxe:1;
		अचिन्हित cr0_wp:1;
		अचिन्हित smep_andnot_wp:1;
		अचिन्हित smap_andnot_wp:1;
		अचिन्हित ad_disabled:1;
		अचिन्हित guest_mode:1;
		अचिन्हित :6;

		/*
		 * This is left at the top of the word so that
		 * kvm_memslots_क्रम_spte_role can extract it with a
		 * simple shअगरt.  While there is room, give it a whole
		 * byte so it is also faster to load it from memory.
		 */
		अचिन्हित smm:8;
	पूर्ण;
पूर्ण;

जोड़ kvm_mmu_extended_role अणु
/*
 * This काष्ठाure complements kvm_mmu_page_role caching everything needed क्रम
 * MMU configuration. If nothing in both these काष्ठाures changed, MMU
 * re-configuration can be skipped. @valid bit is set on first usage so we करोn't
 * treat all-zero काष्ठाure as valid data.
 */
	u32 word;
	काष्ठा अणु
		अचिन्हित पूर्णांक valid:1;
		अचिन्हित पूर्णांक execonly:1;
		अचिन्हित पूर्णांक cr0_pg:1;
		अचिन्हित पूर्णांक cr4_pae:1;
		अचिन्हित पूर्णांक cr4_pse:1;
		अचिन्हित पूर्णांक cr4_pke:1;
		अचिन्हित पूर्णांक cr4_smap:1;
		अचिन्हित पूर्णांक cr4_smep:1;
		अचिन्हित पूर्णांक maxphyaddr:6;
	पूर्ण;
पूर्ण;

जोड़ kvm_mmu_role अणु
	u64 as_u64;
	काष्ठा अणु
		जोड़ kvm_mmu_page_role base;
		जोड़ kvm_mmu_extended_role ext;
	पूर्ण;
पूर्ण;

काष्ठा kvm_rmap_head अणु
	अचिन्हित दीर्घ val;
पूर्ण;

काष्ठा kvm_pio_request अणु
	अचिन्हित दीर्घ linear_rip;
	अचिन्हित दीर्घ count;
	पूर्णांक in;
	पूर्णांक port;
	पूर्णांक size;
पूर्ण;

#घोषणा PT64_ROOT_MAX_LEVEL 5

काष्ठा rsvd_bits_validate अणु
	u64 rsvd_bits_mask[2][PT64_ROOT_MAX_LEVEL];
	u64 bad_mt_xwr;
पूर्ण;

काष्ठा kvm_mmu_root_info अणु
	gpa_t pgd;
	hpa_t hpa;
पूर्ण;

#घोषणा KVM_MMU_ROOT_INFO_INVALID \
	((काष्ठा kvm_mmu_root_info) अणु .pgd = INVALID_PAGE, .hpa = INVALID_PAGE पूर्ण)

#घोषणा KVM_MMU_NUM_PREV_ROOTS 3

#घोषणा KVM_HAVE_MMU_RWLOCK

काष्ठा kvm_mmu_page;

/*
 * x86 supports 4 paging modes (5-level 64-bit, 4-level 64-bit, 3-level 32-bit,
 * and 2-level 32-bit).  The kvm_mmu काष्ठाure असलtracts the details of the
 * current mmu mode.
 */
काष्ठा kvm_mmu अणु
	अचिन्हित दीर्घ (*get_guest_pgd)(काष्ठा kvm_vcpu *vcpu);
	u64 (*get_pdptr)(काष्ठा kvm_vcpu *vcpu, पूर्णांक index);
	पूर्णांक (*page_fault)(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa, u32 err,
			  bool prefault);
	व्योम (*inject_page_fault)(काष्ठा kvm_vcpu *vcpu,
				  काष्ठा x86_exception *fault);
	gpa_t (*gva_to_gpa)(काष्ठा kvm_vcpu *vcpu, gpa_t gva_or_gpa,
			    u32 access, काष्ठा x86_exception *exception);
	gpa_t (*translate_gpa)(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, u32 access,
			       काष्ठा x86_exception *exception);
	पूर्णांक (*sync_page)(काष्ठा kvm_vcpu *vcpu,
			 काष्ठा kvm_mmu_page *sp);
	व्योम (*invlpg)(काष्ठा kvm_vcpu *vcpu, gva_t gva, hpa_t root_hpa);
	hpa_t root_hpa;
	gpa_t root_pgd;
	जोड़ kvm_mmu_role mmu_role;
	u8 root_level;
	u8 shaकरोw_root_level;
	u8 ept_ad;
	bool direct_map;
	काष्ठा kvm_mmu_root_info prev_roots[KVM_MMU_NUM_PREV_ROOTS];

	/*
	 * Biपंचांगap; bit set = permission fault
	 * Byte index: page fault error code [4:1]
	 * Bit index: pte permissions in ACC_* क्रमmat
	 */
	u8 permissions[16];

	/*
	* The pkru_mask indicates अगर protection key checks are needed.  It
	* consists of 16 करोमुख्यs indexed by page fault error code bits [4:1],
	* with PFEC.RSVD replaced by ACC_USER_MASK from the page tables.
	* Each करोमुख्य has 2 bits which are ANDed with AD and WD from PKRU.
	*/
	u32 pkru_mask;

	u64 *pae_root;
	u64 *pml4_root;

	/*
	 * check zero bits on shaकरोw page table entries, these
	 * bits include not only hardware reserved bits but also
	 * the bits spte never used.
	 */
	काष्ठा rsvd_bits_validate shaकरोw_zero_check;

	काष्ठा rsvd_bits_validate guest_rsvd_check;

	/* Can have large pages at levels 2..last_nonleaf_level-1. */
	u8 last_nonleaf_level;

	bool nx;

	u64 pdptrs[4]; /* pae */
पूर्ण;

काष्ठा kvm_tlb_range अणु
	u64 start_gfn;
	u64 pages;
पूर्ण;

क्रमागत pmc_type अणु
	KVM_PMC_GP = 0,
	KVM_PMC_FIXED,
पूर्ण;

काष्ठा kvm_pmc अणु
	क्रमागत pmc_type type;
	u8 idx;
	u64 counter;
	u64 eventsel;
	काष्ठा perf_event *perf_event;
	काष्ठा kvm_vcpu *vcpu;
	/*
	 * eventsel value क्रम general purpose counters,
	 * ctrl value क्रम fixed counters.
	 */
	u64 current_config;
पूर्ण;

काष्ठा kvm_pmu अणु
	अचिन्हित nr_arch_gp_counters;
	अचिन्हित nr_arch_fixed_counters;
	अचिन्हित available_event_types;
	u64 fixed_ctr_ctrl;
	u64 global_ctrl;
	u64 global_status;
	u64 global_ovf_ctrl;
	u64 counter_biपंचांगask[2];
	u64 global_ctrl_mask;
	u64 global_ovf_ctrl_mask;
	u64 reserved_bits;
	u8 version;
	काष्ठा kvm_pmc gp_counters[INTEL_PMC_MAX_GENERIC];
	काष्ठा kvm_pmc fixed_counters[INTEL_PMC_MAX_FIXED];
	काष्ठा irq_work irq_work;
	DECLARE_BITMAP(reprogram_pmi, X86_PMC_IDX_MAX);
	DECLARE_BITMAP(all_valid_pmc_idx, X86_PMC_IDX_MAX);
	DECLARE_BITMAP(pmc_in_use, X86_PMC_IDX_MAX);

	/*
	 * The gate to release perf_events not marked in
	 * pmc_in_use only once in a vcpu समय slice.
	 */
	bool need_cleanup;

	/*
	 * The total number of programmed perf_events and it helps to aव्योम
	 * redundant check beक्रमe cleanup अगर guest करोn't use vPMU at all.
	 */
	u8 event_count;
पूर्ण;

काष्ठा kvm_pmu_ops;

क्रमागत अणु
	KVM_DEBUGREG_BP_ENABLED = 1,
	KVM_DEBUGREG_WONT_EXIT = 2,
	KVM_DEBUGREG_RELOAD = 4,
पूर्ण;

काष्ठा kvm_mtrr_range अणु
	u64 base;
	u64 mask;
	काष्ठा list_head node;
पूर्ण;

काष्ठा kvm_mtrr अणु
	काष्ठा kvm_mtrr_range var_ranges[KVM_NR_VAR_MTRR];
	mtrr_type fixed_ranges[KVM_NR_FIXED_MTRR_REGION];
	u64 deftype;

	काष्ठा list_head head;
पूर्ण;

/* Hyper-V SynIC समयr */
काष्ठा kvm_vcpu_hv_sसमयr अणु
	काष्ठा hrसमयr समयr;
	पूर्णांक index;
	जोड़ hv_sसमयr_config config;
	u64 count;
	u64 exp_समय;
	काष्ठा hv_message msg;
	bool msg_pending;
पूर्ण;

/* Hyper-V synthetic पूर्णांकerrupt controller (SynIC)*/
काष्ठा kvm_vcpu_hv_synic अणु
	u64 version;
	u64 control;
	u64 msg_page;
	u64 evt_page;
	atomic64_t sपूर्णांक[HV_SYNIC_SINT_COUNT];
	atomic_t sपूर्णांक_to_gsi[HV_SYNIC_SINT_COUNT];
	DECLARE_BITMAP(स्वतः_eoi_biपंचांगap, 256);
	DECLARE_BITMAP(vec_biपंचांगap, 256);
	bool active;
	bool करोnt_zero_synic_pages;
पूर्ण;

/* Hyper-V per vcpu emulation context */
काष्ठा kvm_vcpu_hv अणु
	काष्ठा kvm_vcpu *vcpu;
	u32 vp_index;
	u64 hv_vapic;
	s64 runसमय_offset;
	काष्ठा kvm_vcpu_hv_synic synic;
	काष्ठा kvm_hyperv_निकास निकास;
	काष्ठा kvm_vcpu_hv_sसमयr sसमयr[HV_SYNIC_STIMER_COUNT];
	DECLARE_BITMAP(sसमयr_pending_biपंचांगap, HV_SYNIC_STIMER_COUNT);
	cpumask_t tlb_flush;
पूर्ण;

/* Xen HVM per vcpu emulation context */
काष्ठा kvm_vcpu_xen अणु
	u64 hypercall_rip;
	u32 current_runstate;
	bool vcpu_info_set;
	bool vcpu_समय_info_set;
	bool runstate_set;
	काष्ठा gfn_to_hva_cache vcpu_info_cache;
	काष्ठा gfn_to_hva_cache vcpu_समय_info_cache;
	काष्ठा gfn_to_hva_cache runstate_cache;
	u64 last_steal;
	u64 runstate_entry_समय;
	u64 runstate_बार[4];
पूर्ण;

काष्ठा kvm_vcpu_arch अणु
	/*
	 * rip and regs accesses must go through
	 * kvm_अणुरेजिस्टर,ripपूर्ण_अणुपढ़ो,ग_लिखोपूर्ण functions.
	 */
	अचिन्हित दीर्घ regs[NR_VCPU_REGS];
	u32 regs_avail;
	u32 regs_dirty;

	अचिन्हित दीर्घ cr0;
	अचिन्हित दीर्घ cr0_guest_owned_bits;
	अचिन्हित दीर्घ cr2;
	अचिन्हित दीर्घ cr3;
	अचिन्हित दीर्घ cr4;
	अचिन्हित दीर्घ cr4_guest_owned_bits;
	अचिन्हित दीर्घ cr4_guest_rsvd_bits;
	अचिन्हित दीर्घ cr8;
	u32 host_pkru;
	u32 pkru;
	u32 hflags;
	u64 efer;
	u64 apic_base;
	काष्ठा kvm_lapic *apic;    /* kernel irqchip context */
	bool apicv_active;
	bool load_eoi_निकासmap_pending;
	DECLARE_BITMAP(ioapic_handled_vectors, 256);
	अचिन्हित दीर्घ apic_attention;
	पूर्णांक32_t apic_arb_prio;
	पूर्णांक mp_state;
	u64 ia32_misc_enable_msr;
	u64 smbase;
	u64 smi_count;
	bool tpr_access_reporting;
	bool xsaves_enabled;
	u64 ia32_xss;
	u64 microcode_version;
	u64 arch_capabilities;
	u64 perf_capabilities;

	/*
	 * Paging state of the vcpu
	 *
	 * If the vcpu runs in guest mode with two level paging this still saves
	 * the paging mode of the l1 guest. This context is always used to
	 * handle faults.
	 */
	काष्ठा kvm_mmu *mmu;

	/* Non-nested MMU क्रम L1 */
	काष्ठा kvm_mmu root_mmu;

	/* L1 MMU when running nested */
	काष्ठा kvm_mmu guest_mmu;

	/*
	 * Paging state of an L2 guest (used क्रम nested npt)
	 *
	 * This context will save all necessary inक्रमmation to walk page tables
	 * of an L2 guest. This context is only initialized क्रम page table
	 * walking and not क्रम faulting since we never handle l2 page faults on
	 * the host.
	 */
	काष्ठा kvm_mmu nested_mmu;

	/*
	 * Poपूर्णांकer to the mmu context currently used क्रम
	 * gva_to_gpa translations.
	 */
	काष्ठा kvm_mmu *walk_mmu;

	काष्ठा kvm_mmu_memory_cache mmu_pte_list_desc_cache;
	काष्ठा kvm_mmu_memory_cache mmu_shaकरोw_page_cache;
	काष्ठा kvm_mmu_memory_cache mmu_gfn_array_cache;
	काष्ठा kvm_mmu_memory_cache mmu_page_header_cache;

	/*
	 * QEMU userspace and the guest each have their own FPU state.
	 * In vcpu_run, we चयन between the user and guest FPU contexts.
	 * While running a VCPU, the VCPU thपढ़ो will have the guest FPU
	 * context.
	 *
	 * Note that जबतक the PKRU state lives inside the fpu रेजिस्टरs,
	 * it is चयनed out separately at VMENTER and VMEXIT समय. The
	 * "guest_fpu" state here contains the guest FPU context, with the
	 * host PRKU bits.
	 */
	काष्ठा fpu *user_fpu;
	काष्ठा fpu *guest_fpu;

	u64 xcr0;
	u64 guest_supported_xcr0;

	काष्ठा kvm_pio_request pio;
	व्योम *pio_data;
	व्योम *guest_ins_data;

	u8 event_निकास_inst_len;

	काष्ठा kvm_queued_exception अणु
		bool pending;
		bool injected;
		bool has_error_code;
		u8 nr;
		u32 error_code;
		अचिन्हित दीर्घ payload;
		bool has_payload;
		u8 nested_apf;
	पूर्ण exception;

	काष्ठा kvm_queued_पूर्णांकerrupt अणु
		bool injected;
		bool soft;
		u8 nr;
	पूर्ण पूर्णांकerrupt;

	पूर्णांक halt_request; /* real mode on Intel only */

	पूर्णांक cpuid_nent;
	काष्ठा kvm_cpuid_entry2 *cpuid_entries;

	u64 reserved_gpa_bits;
	पूर्णांक maxphyaddr;
	पूर्णांक max_tdp_level;

	/* emulate context */

	काष्ठा x86_emulate_ctxt *emulate_ctxt;
	bool emulate_regs_need_sync_to_vcpu;
	bool emulate_regs_need_sync_from_vcpu;
	पूर्णांक (*complete_userspace_io)(काष्ठा kvm_vcpu *vcpu);

	gpa_t समय;
	काष्ठा pvघड़ी_vcpu_समय_info hv_घड़ी;
	अचिन्हित पूर्णांक hw_tsc_khz;
	काष्ठा gfn_to_hva_cache pv_समय;
	bool pv_समय_enabled;
	/* set guest stopped flag in pvघड़ी flags field */
	bool pvघड़ी_set_guest_stopped_request;

	काष्ठा अणु
		u8 preempted;
		u64 msr_val;
		u64 last_steal;
		काष्ठा gfn_to_pfn_cache cache;
	पूर्ण st;

	u64 l1_tsc_offset;
	u64 tsc_offset;
	u64 last_guest_tsc;
	u64 last_host_tsc;
	u64 tsc_offset_adjusपंचांगent;
	u64 this_tsc_nsec;
	u64 this_tsc_ग_लिखो;
	u64 this_tsc_generation;
	bool tsc_catchup;
	bool tsc_always_catchup;
	s8 भव_tsc_shअगरt;
	u32 भव_tsc_mult;
	u32 भव_tsc_khz;
	s64 ia32_tsc_adjust_msr;
	u64 msr_ia32_घातer_ctl;
	u64 tsc_scaling_ratio;

	atomic_t nmi_queued;  /* unprocessed asynchronous NMIs */
	अचिन्हित nmi_pending; /* NMI queued after currently running handler */
	bool nmi_injected;    /* Trying to inject an NMI this entry */
	bool smi_pending;    /* SMI queued after currently running handler */

	काष्ठा kvm_mtrr mtrr_state;
	u64 pat;

	अचिन्हित चयन_db_regs;
	अचिन्हित दीर्घ db[KVM_NR_DB_REGS];
	अचिन्हित दीर्घ dr6;
	अचिन्हित दीर्घ dr7;
	अचिन्हित दीर्घ eff_db[KVM_NR_DB_REGS];
	अचिन्हित दीर्घ guest_debug_dr7;
	u64 msr_platक्रमm_info;
	u64 msr_misc_features_enables;

	u64 mcg_cap;
	u64 mcg_status;
	u64 mcg_ctl;
	u64 mcg_ext_ctl;
	u64 *mce_banks;

	/* Cache MMIO info */
	u64 mmio_gva;
	अचिन्हित mmio_access;
	gfn_t mmio_gfn;
	u64 mmio_gen;

	काष्ठा kvm_pmu pmu;

	/* used क्रम guest single stepping over the given code position */
	अचिन्हित दीर्घ singlestep_rip;

	bool hyperv_enabled;
	काष्ठा kvm_vcpu_hv *hyperv;
	काष्ठा kvm_vcpu_xen xen;

	cpumask_var_t wbinvd_dirty_mask;

	अचिन्हित दीर्घ last_retry_eip;
	अचिन्हित दीर्घ last_retry_addr;

	काष्ठा अणु
		bool halted;
		gfn_t gfns[ASYNC_PF_PER_VCPU];
		काष्ठा gfn_to_hva_cache data;
		u64 msr_en_val; /* MSR_KVM_ASYNC_PF_EN */
		u64 msr_पूर्णांक_val; /* MSR_KVM_ASYNC_PF_INT */
		u16 vec;
		u32 id;
		bool send_user_only;
		u32 host_apf_flags;
		अचिन्हित दीर्घ nested_apf_token;
		bool delivery_as_pf_vmनिकास;
		bool pageपढ़ोy_pending;
	पूर्ण apf;

	/* OSVW MSRs (AMD only) */
	काष्ठा अणु
		u64 length;
		u64 status;
	पूर्ण osvw;

	काष्ठा अणु
		u64 msr_val;
		काष्ठा gfn_to_hva_cache data;
	पूर्ण pv_eoi;

	u64 msr_kvm_poll_control;

	/*
	 * Indicates the guest is trying to ग_लिखो a gfn that contains one or
	 * more of the PTEs used to translate the ग_लिखो itself, i.e. the access
	 * is changing its own translation in the guest page tables.  KVM निकासs
	 * to userspace अगर emulation of the faulting inकाष्ठाion fails and this
	 * flag is set, as KVM cannot make क्रमward progress.
	 *
	 * If emulation fails क्रम a ग_लिखो to guest page tables, KVM unprotects
	 * (zaps) the shaकरोw page क्रम the target gfn and resumes the guest to
	 * retry the non-emulatable inकाष्ठाion (on hardware).  Unprotecting the
	 * gfn करोesn't allow क्रमward progress क्रम a self-changing access because
	 * करोing so also zaps the translation क्रम the gfn, i.e. retrying the
	 * inकाष्ठाion will hit a !PRESENT fault, which results in a new shaकरोw
	 * page and sends KVM back to square one.
	 */
	bool ग_लिखो_fault_to_shaकरोw_pgtable;

	/* set at EPT violation at this poपूर्णांक */
	अचिन्हित दीर्घ निकास_qualअगरication;

	/* pv related host specअगरic info */
	काष्ठा अणु
		bool pv_unhalted;
	पूर्ण pv;

	पूर्णांक pending_ioapic_eoi;
	पूर्णांक pending_बाह्यal_vector;

	/* be preempted when it's in kernel-mode(cpl=0) */
	bool preempted_in_kernel;

	/* Flush the L1 Data cache क्रम L1TF mitigation on VMENTER */
	bool l1tf_flush_l1d;

	/* Host CPU on which VM-entry was most recently attempted */
	अचिन्हित पूर्णांक last_vmentry_cpu;

	/* AMD MSRC001_0015 Hardware Configuration */
	u64 msr_hwcr;

	/* pv related cpuid info */
	काष्ठा अणु
		/*
		 * value of the eax रेजिस्टर in the KVM_CPUID_FEATURES CPUID
		 * leaf.
		 */
		u32 features;

		/*
		 * indicates whether pv emulation should be disabled अगर features
		 * are not present in the guest's cpuid
		 */
		bool enक्रमce;
	पूर्ण pv_cpuid;

	/* Protected Guests */
	bool guest_state_रक्षित;
पूर्ण;

काष्ठा kvm_lpage_info अणु
	पूर्णांक disallow_lpage;
पूर्ण;

काष्ठा kvm_arch_memory_slot अणु
	काष्ठा kvm_rmap_head *rmap[KVM_NR_PAGE_SIZES];
	काष्ठा kvm_lpage_info *lpage_info[KVM_NR_PAGE_SIZES - 1];
	अचिन्हित लघु *gfn_track[KVM_PAGE_TRACK_MAX];
पूर्ण;

/*
 * We use as the mode the number of bits allocated in the LDR क्रम the
 * logical processor ID.  It happens that these are all घातers of two.
 * This makes it is very easy to detect हालs where the APICs are
 * configured क्रम multiple modes; in that हाल, we cannot use the map and
 * hence cannot use kvm_irq_delivery_to_apic_fast either.
 */
#घोषणा KVM_APIC_MODE_XAPIC_CLUSTER          4
#घोषणा KVM_APIC_MODE_XAPIC_FLAT             8
#घोषणा KVM_APIC_MODE_X2APIC                16

काष्ठा kvm_apic_map अणु
	काष्ठा rcu_head rcu;
	u8 mode;
	u32 max_apic_id;
	जोड़ अणु
		काष्ठा kvm_lapic *xapic_flat_map[8];
		काष्ठा kvm_lapic *xapic_cluster_map[16][4];
	पूर्ण;
	काष्ठा kvm_lapic *phys_map[];
पूर्ण;

/* Hyper-V synthetic debugger (SynDbg)*/
काष्ठा kvm_hv_syndbg अणु
	काष्ठा अणु
		u64 control;
		u64 status;
		u64 send_page;
		u64 recv_page;
		u64 pending_page;
	पूर्ण control;
	u64 options;
पूर्ण;

/* Current state of Hyper-V TSC page घड़ीsource */
क्रमागत hv_tsc_page_status अणु
	/* TSC page was not set up or disabled */
	HV_TSC_PAGE_UNSET = 0,
	/* TSC page MSR was written by the guest, update pending */
	HV_TSC_PAGE_GUEST_CHANGED,
	/* TSC page MSR was written by KVM userspace, update pending */
	HV_TSC_PAGE_HOST_CHANGED,
	/* TSC page was properly set up and is currently active  */
	HV_TSC_PAGE_SET,
	/* TSC page is currently being updated and thereक्रमe is inactive */
	HV_TSC_PAGE_UPDATING,
	/* TSC page was set up with an inaccessible GPA */
	HV_TSC_PAGE_BROKEN,
पूर्ण;

/* Hyper-V emulation context */
काष्ठा kvm_hv अणु
	काष्ठा mutex hv_lock;
	u64 hv_guest_os_id;
	u64 hv_hypercall;
	u64 hv_tsc_page;
	क्रमागत hv_tsc_page_status hv_tsc_page_status;

	/* Hyper-v based guest crash (NT kernel bugcheck) parameters */
	u64 hv_crash_param[HV_X64_MSR_CRASH_PARAMS];
	u64 hv_crash_ctl;

	काष्ठा ms_hyperv_tsc_page tsc_ref;

	काष्ठा idr conn_to_evt;

	u64 hv_reenlightenment_control;
	u64 hv_tsc_emulation_control;
	u64 hv_tsc_emulation_status;

	/* How many vCPUs have VP index != vCPU index */
	atomic_t num_mismatched_vp_indexes;

	काष्ठा hv_partition_assist_pg *hv_pa_pg;
	काष्ठा kvm_hv_syndbg hv_syndbg;
पूर्ण;

काष्ठा msr_biपंचांगap_range अणु
	u32 flags;
	u32 nmsrs;
	u32 base;
	अचिन्हित दीर्घ *biपंचांगap;
पूर्ण;

/* Xen emulation context */
काष्ठा kvm_xen अणु
	bool दीर्घ_mode;
	bool shinfo_set;
	u8 upcall_vector;
	काष्ठा gfn_to_hva_cache shinfo_cache;
पूर्ण;

क्रमागत kvm_irqchip_mode अणु
	KVM_IRQCHIP_NONE,
	KVM_IRQCHIP_KERNEL,       /* created with KVM_CREATE_IRQCHIP */
	KVM_IRQCHIP_SPLIT,        /* created with KVM_CAP_SPLIT_IRQCHIP */
पूर्ण;

काष्ठा kvm_x86_msr_filter अणु
	u8 count;
	bool शेष_allow:1;
	काष्ठा msr_biपंचांगap_range ranges[16];
पूर्ण;

#घोषणा APICV_INHIBIT_REASON_DISABLE    0
#घोषणा APICV_INHIBIT_REASON_HYPERV     1
#घोषणा APICV_INHIBIT_REASON_NESTED     2
#घोषणा APICV_INHIBIT_REASON_IRQWIN     3
#घोषणा APICV_INHIBIT_REASON_PIT_REINJ  4
#घोषणा APICV_INHIBIT_REASON_X2APIC	5

काष्ठा kvm_arch अणु
	अचिन्हित दीर्घ n_used_mmu_pages;
	अचिन्हित दीर्घ n_requested_mmu_pages;
	अचिन्हित दीर्घ n_max_mmu_pages;
	अचिन्हित पूर्णांक indirect_shaकरोw_pages;
	u8 mmu_valid_gen;
	काष्ठा hlist_head mmu_page_hash[KVM_NUM_MMU_PAGES];
	काष्ठा list_head active_mmu_pages;
	काष्ठा list_head zapped_obsolete_pages;
	काष्ठा list_head lpage_disallowed_mmu_pages;
	काष्ठा kvm_page_track_notअगरier_node mmu_sp_tracker;
	काष्ठा kvm_page_track_notअगरier_head track_notअगरier_head;

	काष्ठा list_head asचिन्हित_dev_head;
	काष्ठा iommu_करोमुख्य *iommu_करोमुख्य;
	bool iommu_noncoherent;
#घोषणा __KVM_HAVE_ARCH_NONCOHERENT_DMA
	atomic_t noncoherent_dma_count;
#घोषणा __KVM_HAVE_ARCH_ASSIGNED_DEVICE
	atomic_t asचिन्हित_device_count;
	काष्ठा kvm_pic *vpic;
	काष्ठा kvm_ioapic *vioapic;
	काष्ठा kvm_pit *vpit;
	atomic_t vapics_in_nmi_mode;
	काष्ठा mutex apic_map_lock;
	काष्ठा kvm_apic_map __rcu *apic_map;
	atomic_t apic_map_dirty;

	bool apic_access_page_करोne;
	अचिन्हित दीर्घ apicv_inhibit_reasons;

	gpa_t wall_घड़ी;

	bool mरुको_in_guest;
	bool hlt_in_guest;
	bool छोड़ो_in_guest;
	bool cstate_in_guest;

	अचिन्हित दीर्घ irq_sources_biपंचांगap;
	s64 kvmघड़ी_offset;
	raw_spinlock_t tsc_ग_लिखो_lock;
	u64 last_tsc_nsec;
	u64 last_tsc_ग_लिखो;
	u32 last_tsc_khz;
	u64 cur_tsc_nsec;
	u64 cur_tsc_ग_लिखो;
	u64 cur_tsc_offset;
	u64 cur_tsc_generation;
	पूर्णांक nr_vcpus_matched_tsc;

	spinlock_t pvघड़ी_gtod_sync_lock;
	bool use_master_घड़ी;
	u64 master_kernel_ns;
	u64 master_cycle_now;
	काष्ठा delayed_work kvmघड़ी_update_work;
	काष्ठा delayed_work kvmघड़ी_sync_work;

	काष्ठा kvm_xen_hvm_config xen_hvm_config;

	/* पढ़ोs रक्षित by irq_srcu, ग_लिखोs by irq_lock */
	काष्ठा hlist_head mask_notअगरier_list;

	काष्ठा kvm_hv hyperv;
	काष्ठा kvm_xen xen;

	#अगर_घोषित CONFIG_KVM_MMU_AUDIT
	पूर्णांक audit_poपूर्णांक;
	#पूर्ण_अगर

	bool backwards_tsc_observed;
	bool boot_vcpu_runs_old_kvmघड़ी;
	u32 bsp_vcpu_id;

	u64 disabled_quirks;
	पूर्णांक cpu_dirty_logging_count;

	क्रमागत kvm_irqchip_mode irqchip_mode;
	u8 nr_reserved_ioapic_pins;

	bool disabled_lapic_found;

	bool x2apic_क्रमmat;
	bool x2apic_broadcast_quirk_disabled;

	bool guest_can_पढ़ो_msr_platक्रमm_info;
	bool exception_payload_enabled;

	bool bus_lock_detection_enabled;

	/* Deflect RDMSR and WRMSR to user space when they trigger a #GP */
	u32 user_space_msr_mask;
	काष्ठा kvm_x86_msr_filter __rcu *msr_filter;

	/* Guest can access the SGX PROVISIONKEY. */
	bool sgx_provisioning_allowed;

	काष्ठा kvm_pmu_event_filter __rcu *pmu_event_filter;
	काष्ठा task_काष्ठा *nx_lpage_recovery_thपढ़ो;

#अगर_घोषित CONFIG_X86_64
	/*
	 * Whether the TDP MMU is enabled क्रम this VM. This contains a
	 * snapshot of the TDP MMU module parameter from when the VM was
	 * created and reमुख्यs unchanged क्रम the lअगरe of the VM. If this is
	 * true, TDP MMU handler functions will run क्रम various MMU
	 * operations.
	 */
	bool tdp_mmu_enabled;

	/*
	 * List of काष्ठा kvm_mmu_pages being used as roots.
	 * All काष्ठा kvm_mmu_pages in the list should have
	 * tdp_mmu_page set.
	 *
	 * For पढ़ोs, this list is रक्षित by:
	 *	the MMU lock in पढ़ो mode + RCU or
	 *	the MMU lock in ग_लिखो mode
	 *
	 * For ग_लिखोs, this list is रक्षित by:
	 *	the MMU lock in पढ़ो mode + the tdp_mmu_pages_lock or
	 *	the MMU lock in ग_लिखो mode
	 *
	 * Roots will reमुख्य in the list until their tdp_mmu_root_count
	 * drops to zero, at which poपूर्णांक the thपढ़ो that decremented the
	 * count to zero should हटाओd the root from the list and clean
	 * it up, मुक्तing the root after an RCU grace period.
	 */
	काष्ठा list_head tdp_mmu_roots;

	/*
	 * List of काष्ठा kvmp_mmu_pages not being used as roots.
	 * All काष्ठा kvm_mmu_pages in the list should have
	 * tdp_mmu_page set and a tdp_mmu_root_count of 0.
	 */
	काष्ठा list_head tdp_mmu_pages;

	/*
	 * Protects accesses to the following fields when the MMU lock
	 * is held in पढ़ो mode:
	 *  - tdp_mmu_roots (above)
	 *  - tdp_mmu_pages (above)
	 *  - the link field of काष्ठा kvm_mmu_pages used by the TDP MMU
	 *  - lpage_disallowed_mmu_pages
	 *  - the lpage_disallowed_link field of काष्ठा kvm_mmu_pages used
	 *    by the TDP MMU
	 * It is acceptable, but not necessary, to acquire this lock when
	 * the thपढ़ो holds the MMU lock in ग_लिखो mode.
	 */
	spinlock_t tdp_mmu_pages_lock;
#पूर्ण_अगर /* CONFIG_X86_64 */
पूर्ण;

काष्ठा kvm_vm_stat अणु
	uदीर्घ mmu_shaकरोw_zapped;
	uदीर्घ mmu_pte_ग_लिखो;
	uदीर्घ mmu_pde_zapped;
	uदीर्घ mmu_flooded;
	uदीर्घ mmu_recycled;
	uदीर्घ mmu_cache_miss;
	uदीर्घ mmu_unsync;
	uदीर्घ remote_tlb_flush;
	uदीर्घ lpages;
	uदीर्घ nx_lpage_splits;
	uदीर्घ max_mmu_page_hash_collisions;
पूर्ण;

काष्ठा kvm_vcpu_stat अणु
	u64 pf_fixed;
	u64 pf_guest;
	u64 tlb_flush;
	u64 invlpg;

	u64 निकासs;
	u64 io_निकासs;
	u64 mmio_निकासs;
	u64 संकेत_निकासs;
	u64 irq_winकरोw_निकासs;
	u64 nmi_winकरोw_निकासs;
	u64 l1d_flush;
	u64 halt_निकासs;
	u64 halt_successful_poll;
	u64 halt_attempted_poll;
	u64 halt_poll_invalid;
	u64 halt_wakeup;
	u64 request_irq_निकासs;
	u64 irq_निकासs;
	u64 host_state_reload;
	u64 fpu_reload;
	u64 insn_emulation;
	u64 insn_emulation_fail;
	u64 hypercalls;
	u64 irq_injections;
	u64 nmi_injections;
	u64 req_event;
	u64 halt_poll_success_ns;
	u64 halt_poll_fail_ns;
	u64 nested_run;
	u64 directed_yield_attempted;
	u64 directed_yield_successful;
पूर्ण;

काष्ठा x86_inकाष्ठाion_info;

काष्ठा msr_data अणु
	bool host_initiated;
	u32 index;
	u64 data;
पूर्ण;

काष्ठा kvm_lapic_irq अणु
	u32 vector;
	u16 delivery_mode;
	u16 dest_mode;
	bool level;
	u16 trig_mode;
	u32 लघुhand;
	u32 dest_id;
	bool msi_redir_hपूर्णांक;
पूर्ण;

अटल अंतरभूत u16 kvm_lapic_irq_dest_mode(bool dest_mode_logical)
अणु
	वापस dest_mode_logical ? APIC_DEST_LOGICAL : APIC_DEST_PHYSICAL;
पूर्ण

काष्ठा kvm_x86_ops अणु
	पूर्णांक (*hardware_enable)(व्योम);
	व्योम (*hardware_disable)(व्योम);
	व्योम (*hardware_unsetup)(व्योम);
	bool (*cpu_has_accelerated_tpr)(व्योम);
	bool (*has_emulated_msr)(काष्ठा kvm *kvm, u32 index);
	व्योम (*vcpu_after_set_cpuid)(काष्ठा kvm_vcpu *vcpu);

	अचिन्हित पूर्णांक vm_size;
	पूर्णांक (*vm_init)(काष्ठा kvm *kvm);
	व्योम (*vm_destroy)(काष्ठा kvm *kvm);

	/* Create, but करो not attach this VCPU */
	पूर्णांक (*vcpu_create)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*vcpu_मुक्त)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*vcpu_reset)(काष्ठा kvm_vcpu *vcpu, bool init_event);

	व्योम (*prepare_guest_चयन)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*vcpu_load)(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
	व्योम (*vcpu_put)(काष्ठा kvm_vcpu *vcpu);

	व्योम (*update_exception_biपंचांगap)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*get_msr)(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr);
	पूर्णांक (*set_msr)(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr);
	u64 (*get_segment_base)(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg);
	व्योम (*get_segment)(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_segment *var, पूर्णांक seg);
	पूर्णांक (*get_cpl)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*set_segment)(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_segment *var, पूर्णांक seg);
	व्योम (*get_cs_db_l_bits)(काष्ठा kvm_vcpu *vcpu, पूर्णांक *db, पूर्णांक *l);
	व्योम (*set_cr0)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0);
	bool (*is_valid_cr4)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0);
	व्योम (*set_cr4)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4);
	पूर्णांक (*set_efer)(काष्ठा kvm_vcpu *vcpu, u64 efer);
	व्योम (*get_idt)(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt);
	व्योम (*set_idt)(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt);
	व्योम (*get_gdt)(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt);
	व्योम (*set_gdt)(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt);
	व्योम (*sync_dirty_debug_regs)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*set_dr7)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ value);
	व्योम (*cache_reg)(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_reg reg);
	अचिन्हित दीर्घ (*get_rflags)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*set_rflags)(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags);

	व्योम (*tlb_flush_all)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*tlb_flush_current)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक  (*tlb_remote_flush)(काष्ठा kvm *kvm);
	पूर्णांक  (*tlb_remote_flush_with_range)(काष्ठा kvm *kvm,
			काष्ठा kvm_tlb_range *range);

	/*
	 * Flush any TLB entries associated with the given GVA.
	 * Does not need to flush GPA->HPA mappings.
	 * Can potentially get non-canonical addresses through INVLPGs, which
	 * the implementation may choose to ignore अगर appropriate.
	 */
	व्योम (*tlb_flush_gva)(काष्ठा kvm_vcpu *vcpu, gva_t addr);

	/*
	 * Flush any TLB entries created by the guest.  Like tlb_flush_gva(),
	 * करोes not need to flush GPA->HPA mappings.
	 */
	व्योम (*tlb_flush_guest)(काष्ठा kvm_vcpu *vcpu);

	क्रमागत निकास_fastpath_completion (*run)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_निकास)(काष्ठा kvm_vcpu *vcpu,
		क्रमागत निकास_fastpath_completion निकास_fastpath);
	पूर्णांक (*skip_emulated_inकाष्ठाion)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*update_emulated_inकाष्ठाion)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*set_पूर्णांकerrupt_shaकरोw)(काष्ठा kvm_vcpu *vcpu, पूर्णांक mask);
	u32 (*get_पूर्णांकerrupt_shaकरोw)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*patch_hypercall)(काष्ठा kvm_vcpu *vcpu,
				अचिन्हित अक्षर *hypercall_addr);
	व्योम (*set_irq)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*set_nmi)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*queue_exception)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*cancel_injection)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*पूर्णांकerrupt_allowed)(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection);
	पूर्णांक (*nmi_allowed)(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection);
	bool (*get_nmi_mask)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*set_nmi_mask)(काष्ठा kvm_vcpu *vcpu, bool masked);
	व्योम (*enable_nmi_winकरोw)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*enable_irq_winकरोw)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*update_cr8_पूर्णांकercept)(काष्ठा kvm_vcpu *vcpu, पूर्णांक tpr, पूर्णांक irr);
	bool (*check_apicv_inhibit_reasons)(uदीर्घ bit);
	व्योम (*pre_update_apicv_exec_ctrl)(काष्ठा kvm *kvm, bool activate);
	व्योम (*refresh_apicv_exec_ctrl)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*hwapic_irr_update)(काष्ठा kvm_vcpu *vcpu, पूर्णांक max_irr);
	व्योम (*hwapic_isr_update)(काष्ठा kvm_vcpu *vcpu, पूर्णांक isr);
	bool (*guest_apic_has_पूर्णांकerrupt)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*load_eoi_निकासmap)(काष्ठा kvm_vcpu *vcpu, u64 *eoi_निकास_biपंचांगap);
	व्योम (*set_भव_apic_mode)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*set_apic_access_page_addr)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*deliver_posted_पूर्णांकerrupt)(काष्ठा kvm_vcpu *vcpu, पूर्णांक vector);
	पूर्णांक (*sync_pir_to_irr)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*set_tss_addr)(काष्ठा kvm *kvm, अचिन्हित पूर्णांक addr);
	पूर्णांक (*set_identity_map_addr)(काष्ठा kvm *kvm, u64 ident_addr);
	u64 (*get_mt_mask)(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, bool is_mmio);

	व्योम (*load_mmu_pgd)(काष्ठा kvm_vcpu *vcpu, hpa_t root_hpa,
			     पूर्णांक root_level);

	bool (*has_wbinvd_निकास)(व्योम);

	/* Returns actual tsc_offset set in active VMCS */
	u64 (*ग_लिखो_l1_tsc_offset)(काष्ठा kvm_vcpu *vcpu, u64 offset);

	/*
	 * Retrieve somewhat arbitrary निकास inक्रमmation.  Intended to be used
	 * only from within tracepoपूर्णांकs to aव्योम VMREADs when tracing is off.
	 */
	व्योम (*get_निकास_info)(काष्ठा kvm_vcpu *vcpu, u64 *info1, u64 *info2,
			      u32 *निकास_पूर्णांक_info, u32 *निकास_पूर्णांक_info_err_code);

	पूर्णांक (*check_पूर्णांकercept)(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा x86_inकाष्ठाion_info *info,
			       क्रमागत x86_पूर्णांकercept_stage stage,
			       काष्ठा x86_exception *exception);
	व्योम (*handle_निकास_irqoff)(काष्ठा kvm_vcpu *vcpu);

	व्योम (*request_immediate_निकास)(काष्ठा kvm_vcpu *vcpu);

	व्योम (*sched_in)(काष्ठा kvm_vcpu *kvm, पूर्णांक cpu);

	/*
	 * Size of the CPU's dirty log buffer, i.e. VMX's PML buffer.  A zero
	 * value indicates CPU dirty logging is unsupported or disabled.
	 */
	पूर्णांक cpu_dirty_log_size;
	व्योम (*update_cpu_dirty_logging)(काष्ठा kvm_vcpu *vcpu);

	/* pmu operations of sub-arch */
	स्थिर काष्ठा kvm_pmu_ops *pmu_ops;
	स्थिर काष्ठा kvm_x86_nested_ops *nested_ops;

	/*
	 * Architecture specअगरic hooks क्रम vCPU blocking due to
	 * HLT inकाष्ठाion.
	 * Returns क्रम .pre_block():
	 *    - 0 means जारी to block the vCPU.
	 *    - 1 means we cannot block the vCPU since some event
	 *        happens during this period, such as, 'ON' bit in
	 *        posted-पूर्णांकerrupts descriptor is set.
	 */
	पूर्णांक (*pre_block)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*post_block)(काष्ठा kvm_vcpu *vcpu);

	व्योम (*vcpu_blocking)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*vcpu_unblocking)(काष्ठा kvm_vcpu *vcpu);

	पूर्णांक (*update_pi_irte)(काष्ठा kvm *kvm, अचिन्हित पूर्णांक host_irq,
			      uपूर्णांक32_t guest_irq, bool set);
	व्योम (*start_assignment)(काष्ठा kvm *kvm);
	व्योम (*apicv_post_state_restore)(काष्ठा kvm_vcpu *vcpu);
	bool (*dy_apicv_has_pending_पूर्णांकerrupt)(काष्ठा kvm_vcpu *vcpu);

	पूर्णांक (*set_hv_समयr)(काष्ठा kvm_vcpu *vcpu, u64 guest_deadline_tsc,
			    bool *expired);
	व्योम (*cancel_hv_समयr)(काष्ठा kvm_vcpu *vcpu);

	व्योम (*setup_mce)(काष्ठा kvm_vcpu *vcpu);

	पूर्णांक (*smi_allowed)(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection);
	पूर्णांक (*pre_enter_smm)(काष्ठा kvm_vcpu *vcpu, अक्षर *smstate);
	पूर्णांक (*pre_leave_smm)(काष्ठा kvm_vcpu *vcpu, स्थिर अक्षर *smstate);
	व्योम (*enable_smi_winकरोw)(काष्ठा kvm_vcpu *vcpu);

	पूर्णांक (*mem_enc_op)(काष्ठा kvm *kvm, व्योम __user *argp);
	पूर्णांक (*mem_enc_reg_region)(काष्ठा kvm *kvm, काष्ठा kvm_enc_region *argp);
	पूर्णांक (*mem_enc_unreg_region)(काष्ठा kvm *kvm, काष्ठा kvm_enc_region *argp);
	पूर्णांक (*vm_copy_enc_context_from)(काष्ठा kvm *kvm, अचिन्हित पूर्णांक source_fd);

	पूर्णांक (*get_msr_feature)(काष्ठा kvm_msr_entry *entry);

	bool (*can_emulate_inकाष्ठाion)(काष्ठा kvm_vcpu *vcpu, व्योम *insn, पूर्णांक insn_len);

	bool (*apic_init_संकेत_blocked)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*enable_direct_tlbflush)(काष्ठा kvm_vcpu *vcpu);

	व्योम (*migrate_समयrs)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*msr_filter_changed)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*complete_emulated_msr)(काष्ठा kvm_vcpu *vcpu, पूर्णांक err);

	व्योम (*vcpu_deliver_sipi_vector)(काष्ठा kvm_vcpu *vcpu, u8 vector);
पूर्ण;

काष्ठा kvm_x86_nested_ops अणु
	पूर्णांक (*check_events)(काष्ठा kvm_vcpu *vcpu);
	bool (*hv_समयr_pending)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*triple_fault)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*get_state)(काष्ठा kvm_vcpu *vcpu,
			 काष्ठा kvm_nested_state __user *user_kvm_nested_state,
			 अचिन्हित user_data_size);
	पूर्णांक (*set_state)(काष्ठा kvm_vcpu *vcpu,
			 काष्ठा kvm_nested_state __user *user_kvm_nested_state,
			 काष्ठा kvm_nested_state *kvm_state);
	bool (*get_nested_state_pages)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*ग_लिखो_log_dirty)(काष्ठा kvm_vcpu *vcpu, gpa_t l2_gpa);

	पूर्णांक (*enable_evmcs)(काष्ठा kvm_vcpu *vcpu,
			    uपूर्णांक16_t *vmcs_version);
	uपूर्णांक16_t (*get_evmcs_version)(काष्ठा kvm_vcpu *vcpu);
पूर्ण;

काष्ठा kvm_x86_init_ops अणु
	पूर्णांक (*cpu_has_kvm_support)(व्योम);
	पूर्णांक (*disabled_by_bios)(व्योम);
	पूर्णांक (*check_processor_compatibility)(व्योम);
	पूर्णांक (*hardware_setup)(व्योम);

	काष्ठा kvm_x86_ops *runसमय_ops;
पूर्ण;

काष्ठा kvm_arch_async_pf अणु
	u32 token;
	gfn_t gfn;
	अचिन्हित दीर्घ cr3;
	bool direct_map;
पूर्ण;

बाह्य u32 __पढ़ो_mostly kvm_nr_uret_msrs;
बाह्य u64 __पढ़ो_mostly host_efer;
बाह्य bool __पढ़ो_mostly allow_smaller_maxphyaddr;
बाह्य काष्ठा kvm_x86_ops kvm_x86_ops;

#घोषणा KVM_X86_OP(func) \
	DECLARE_STATIC_CALL(kvm_x86_##func, *(((काष्ठा kvm_x86_ops *)0)->func));
#घोषणा KVM_X86_OP_शून्य KVM_X86_OP
#समावेश <यंत्र/kvm-x86-ops.h>

अटल अंतरभूत व्योम kvm_ops_अटल_call_update(व्योम)
अणु
#घोषणा KVM_X86_OP(func) \
	अटल_call_update(kvm_x86_##func, kvm_x86_ops.func);
#घोषणा KVM_X86_OP_शून्य KVM_X86_OP
#समावेश <यंत्र/kvm-x86-ops.h>
पूर्ण

#घोषणा __KVM_HAVE_ARCH_VM_ALLOC
अटल अंतरभूत काष्ठा kvm *kvm_arch_alloc_vm(व्योम)
अणु
	वापस __vदो_स्मृति(kvm_x86_ops.vm_size, GFP_KERNEL_ACCOUNT | __GFP_ZERO);
पूर्ण
व्योम kvm_arch_मुक्त_vm(काष्ठा kvm *kvm);

#घोषणा __KVM_HAVE_ARCH_FLUSH_REMOTE_TLB
अटल अंतरभूत पूर्णांक kvm_arch_flush_remote_tlb(काष्ठा kvm *kvm)
अणु
	अगर (kvm_x86_ops.tlb_remote_flush &&
	    !अटल_call(kvm_x86_tlb_remote_flush)(kvm))
		वापस 0;
	अन्यथा
		वापस -ENOTSUPP;
पूर्ण

पूर्णांक kvm_mmu_module_init(व्योम);
व्योम kvm_mmu_module_निकास(व्योम);

व्योम kvm_mmu_destroy(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_mmu_create(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_mmu_init_vm(काष्ठा kvm *kvm);
व्योम kvm_mmu_uninit_vm(काष्ठा kvm *kvm);

व्योम kvm_mmu_reset_context(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_mmu_slot_हटाओ_ग_लिखो_access(काष्ठा kvm *kvm,
				      काष्ठा kvm_memory_slot *memslot,
				      पूर्णांक start_level);
व्योम kvm_mmu_zap_collapsible_sptes(काष्ठा kvm *kvm,
				   स्थिर काष्ठा kvm_memory_slot *memslot);
व्योम kvm_mmu_slot_leaf_clear_dirty(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *memslot);
व्योम kvm_mmu_zap_all(काष्ठा kvm *kvm);
व्योम kvm_mmu_invalidate_mmio_sptes(काष्ठा kvm *kvm, u64 gen);
अचिन्हित दीर्घ kvm_mmu_calculate_शेष_mmu_pages(काष्ठा kvm *kvm);
व्योम kvm_mmu_change_mmu_pages(काष्ठा kvm *kvm, अचिन्हित दीर्घ kvm_nr_mmu_pages);

पूर्णांक load_pdptrs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu, अचिन्हित दीर्घ cr3);
bool pdptrs_changed(काष्ठा kvm_vcpu *vcpu);

पूर्णांक emulator_ग_लिखो_phys(काष्ठा kvm_vcpu *vcpu, gpa_t gpa,
			  स्थिर व्योम *val, पूर्णांक bytes);

काष्ठा kvm_irq_mask_notअगरier अणु
	व्योम (*func)(काष्ठा kvm_irq_mask_notअगरier *kimn, bool masked);
	पूर्णांक irq;
	काष्ठा hlist_node link;
पूर्ण;

व्योम kvm_रेजिस्टर_irq_mask_notअगरier(काष्ठा kvm *kvm, पूर्णांक irq,
				    काष्ठा kvm_irq_mask_notअगरier *kimn);
व्योम kvm_unरेजिस्टर_irq_mask_notअगरier(काष्ठा kvm *kvm, पूर्णांक irq,
				      काष्ठा kvm_irq_mask_notअगरier *kimn);
व्योम kvm_fire_mask_notअगरiers(काष्ठा kvm *kvm, अचिन्हित irqchip, अचिन्हित pin,
			     bool mask);

बाह्य bool tdp_enabled;

u64 vcpu_tsc_khz(काष्ठा kvm_vcpu *vcpu);

/* control of guest tsc rate supported? */
बाह्य bool kvm_has_tsc_control;
/* maximum supported tsc_khz क्रम guests */
बाह्य u32  kvm_max_guest_tsc_khz;
/* number of bits of the fractional part of the TSC scaling ratio */
बाह्य u8   kvm_tsc_scaling_ratio_frac_bits;
/* maximum allowed value of TSC scaling ratio */
बाह्य u64  kvm_max_tsc_scaling_ratio;
/* 1ull << kvm_tsc_scaling_ratio_frac_bits */
बाह्य u64  kvm_शेष_tsc_scaling_ratio;
/* bus lock detection supported? */
बाह्य bool kvm_has_bus_lock_निकास;

बाह्य u64 kvm_mce_cap_supported;

/*
 * EMULTYPE_NO_DECODE - Set when re-emulating an inकाष्ठाion (after completing
 *			userspace I/O) to indicate that the emulation context
 *			should be reused as is, i.e. skip initialization of
 *			emulation context, inकाष्ठाion fetch and decode.
 *
 * EMULTYPE_TRAP_UD - Set when emulating an पूर्णांकercepted #UD from hardware.
 *		      Indicates that only select inकाष्ठाions (tagged with
 *		      EmulateOnUD) should be emulated (to minimize the emulator
 *		      attack surface).  See also EMULTYPE_TRAP_UD_FORCED.
 *
 * EMULTYPE_SKIP - Set when emulating solely to skip an inकाष्ठाion, i.e. to
 *		   decode the inकाष्ठाion length.  For use *only* by
 *		   kvm_x86_ops.skip_emulated_inकाष्ठाion() implementations.
 *
 * EMULTYPE_ALLOW_RETRY_PF - Set when the emulator should resume the guest to
 *			     retry native execution under certain conditions,
 *			     Can only be set in conjunction with EMULTYPE_PF.
 *
 * EMULTYPE_TRAP_UD_FORCED - Set when emulating an पूर्णांकercepted #UD that was
 *			     triggered by KVM's magic "force emulation" prefix,
 *			     which is opt in via module param (off by शेष).
 *			     Bypasses EmulateOnUD restriction despite emulating
 *			     due to an पूर्णांकercepted #UD (see EMULTYPE_TRAP_UD).
 *			     Used to test the full emulator from userspace.
 *
 * EMULTYPE_VMWARE_GP - Set when emulating an पूर्णांकercepted #GP क्रम VMware
 *			backकरोor emulation, which is opt in via module param.
 *			VMware backकरोor emulation handles select inकाष्ठाions
 *			and reinjects the #GP क्रम all other हालs.
 *
 * EMULTYPE_PF - Set when emulating MMIO by way of an पूर्णांकercepted #PF, in which
 *		 हाल the CR2/GPA value pass on the stack is valid.
 */
#घोषणा EMULTYPE_NO_DECODE	    (1 << 0)
#घोषणा EMULTYPE_TRAP_UD	    (1 << 1)
#घोषणा EMULTYPE_SKIP		    (1 << 2)
#घोषणा EMULTYPE_ALLOW_RETRY_PF	    (1 << 3)
#घोषणा EMULTYPE_TRAP_UD_FORCED	    (1 << 4)
#घोषणा EMULTYPE_VMWARE_GP	    (1 << 5)
#घोषणा EMULTYPE_PF		    (1 << 6)

पूर्णांक kvm_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, पूर्णांक emulation_type);
पूर्णांक kvm_emulate_inकाष्ठाion_from_buffer(काष्ठा kvm_vcpu *vcpu,
					व्योम *insn, पूर्णांक insn_len);

व्योम kvm_enable_efer_bits(u64);
bool kvm_valid_efer(काष्ठा kvm_vcpu *vcpu, u64 efer);
पूर्णांक __kvm_get_msr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 *data, bool host_initiated);
पूर्णांक kvm_get_msr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 *data);
पूर्णांक kvm_set_msr(काष्ठा kvm_vcpu *vcpu, u32 index, u64 data);
पूर्णांक kvm_emulate_rdmsr(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_wrmsr(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_as_nop(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_invd(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_mरुको(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_handle_invalid_op(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_monitor(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_fast_pio(काष्ठा kvm_vcpu *vcpu, पूर्णांक size, अचिन्हित लघु port, पूर्णांक in);
पूर्णांक kvm_emulate_cpuid(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_halt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_vcpu_halt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_ap_reset_hold(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_emulate_wbinvd(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_get_segment(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_segment *var, पूर्णांक seg);
पूर्णांक kvm_load_segment_descriptor(काष्ठा kvm_vcpu *vcpu, u16 selector, पूर्णांक seg);
व्योम kvm_vcpu_deliver_sipi_vector(काष्ठा kvm_vcpu *vcpu, u8 vector);

पूर्णांक kvm_task_चयन(काष्ठा kvm_vcpu *vcpu, u16 tss_selector, पूर्णांक idt_index,
		    पूर्णांक reason, bool has_error_code, u32 error_code);

व्योम kvm_मुक्त_guest_fpu(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_post_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ old_cr0, अचिन्हित दीर्घ cr0);
व्योम kvm_post_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ old_cr4, अचिन्हित दीर्घ cr4);
पूर्णांक kvm_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0);
पूर्णांक kvm_set_cr3(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr3);
पूर्णांक kvm_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4);
पूर्णांक kvm_set_cr8(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr8);
पूर्णांक kvm_set_dr(काष्ठा kvm_vcpu *vcpu, पूर्णांक dr, अचिन्हित दीर्घ val);
व्योम kvm_get_dr(काष्ठा kvm_vcpu *vcpu, पूर्णांक dr, अचिन्हित दीर्घ *val);
अचिन्हित दीर्घ kvm_get_cr8(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lmsw(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ msw);
व्योम kvm_get_cs_db_l_bits(काष्ठा kvm_vcpu *vcpu, पूर्णांक *db, पूर्णांक *l);
पूर्णांक kvm_emulate_xsetbv(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_get_msr_common(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr);
पूर्णांक kvm_set_msr_common(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr);

अचिन्हित दीर्घ kvm_get_rflags(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_set_rflags(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags);
पूर्णांक kvm_emulate_rdpmc(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_queue_exception(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr);
व्योम kvm_queue_exception_e(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr, u32 error_code);
व्योम kvm_queue_exception_p(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr, अचिन्हित दीर्घ payload);
व्योम kvm_requeue_exception(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr);
व्योम kvm_requeue_exception_e(काष्ठा kvm_vcpu *vcpu, अचिन्हित nr, u32 error_code);
व्योम kvm_inject_page_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा x86_exception *fault);
bool kvm_inject_emulated_page_fault(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा x86_exception *fault);
पूर्णांक kvm_पढ़ो_guest_page_mmu(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu,
			    gfn_t gfn, व्योम *data, पूर्णांक offset, पूर्णांक len,
			    u32 access);
bool kvm_require_cpl(काष्ठा kvm_vcpu *vcpu, पूर्णांक required_cpl);
bool kvm_require_dr(काष्ठा kvm_vcpu *vcpu, पूर्णांक dr);

अटल अंतरभूत पूर्णांक __kvm_irq_line_state(अचिन्हित दीर्घ *irq_state,
				       पूर्णांक irq_source_id, पूर्णांक level)
अणु
	/* Logical OR क्रम level trig पूर्णांकerrupt */
	अगर (level)
		__set_bit(irq_source_id, irq_state);
	अन्यथा
		__clear_bit(irq_source_id, irq_state);

	वापस !!(*irq_state);
पूर्ण

#घोषणा KVM_MMU_ROOT_CURRENT		BIT(0)
#घोषणा KVM_MMU_ROOT_PREVIOUS(i)	BIT(1+i)
#घोषणा KVM_MMU_ROOTS_ALL		(~0UL)

पूर्णांक kvm_pic_set_irq(काष्ठा kvm_pic *pic, पूर्णांक irq, पूर्णांक irq_source_id, पूर्णांक level);
व्योम kvm_pic_clear_all(काष्ठा kvm_pic *pic, पूर्णांक irq_source_id);

व्योम kvm_inject_nmi(काष्ठा kvm_vcpu *vcpu);

व्योम kvm_update_dr7(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_mmu_unprotect_page(काष्ठा kvm *kvm, gfn_t gfn);
व्योम __kvm_mmu_मुक्त_some_pages(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_mmu_मुक्त_roots(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu,
			uदीर्घ roots_to_मुक्त);
gpa_t translate_nested_gpa(काष्ठा kvm_vcpu *vcpu, gpa_t gpa, u32 access,
			   काष्ठा x86_exception *exception);
gpa_t kvm_mmu_gva_to_gpa_पढ़ो(काष्ठा kvm_vcpu *vcpu, gva_t gva,
			      काष्ठा x86_exception *exception);
gpa_t kvm_mmu_gva_to_gpa_fetch(काष्ठा kvm_vcpu *vcpu, gva_t gva,
			       काष्ठा x86_exception *exception);
gpa_t kvm_mmu_gva_to_gpa_ग_लिखो(काष्ठा kvm_vcpu *vcpu, gva_t gva,
			       काष्ठा x86_exception *exception);
gpa_t kvm_mmu_gva_to_gpa_प्रणाली(काष्ठा kvm_vcpu *vcpu, gva_t gva,
				काष्ठा x86_exception *exception);

bool kvm_apicv_activated(काष्ठा kvm *kvm);
व्योम kvm_apicv_init(काष्ठा kvm *kvm, bool enable);
व्योम kvm_vcpu_update_apicv(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_request_apicv_update(काष्ठा kvm *kvm, bool activate,
			      अचिन्हित दीर्घ bit);

पूर्णांक kvm_emulate_hypercall(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_mmu_page_fault(काष्ठा kvm_vcpu *vcpu, gpa_t cr2_or_gpa, u64 error_code,
		       व्योम *insn, पूर्णांक insn_len);
व्योम kvm_mmu_invlpg(काष्ठा kvm_vcpu *vcpu, gva_t gva);
व्योम kvm_mmu_invalidate_gva(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu *mmu,
			    gva_t gva, hpa_t root_hpa);
व्योम kvm_mmu_invpcid_gva(काष्ठा kvm_vcpu *vcpu, gva_t gva, अचिन्हित दीर्घ pcid);
व्योम kvm_mmu_new_pgd(काष्ठा kvm_vcpu *vcpu, gpa_t new_pgd, bool skip_tlb_flush,
		     bool skip_mmu_sync);

व्योम kvm_configure_mmu(bool enable_tdp, पूर्णांक tdp_max_root_level,
		       पूर्णांक tdp_huge_page_level);

अटल अंतरभूत u16 kvm_पढ़ो_ldt(व्योम)
अणु
	u16 ldt;
	यंत्र("sldt %0" : "=g"(ldt));
	वापस ldt;
पूर्ण

अटल अंतरभूत व्योम kvm_load_ldt(u16 sel)
अणु
	यंत्र("lldt %0" : : "rm"(sel));
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_msr(अचिन्हित दीर्घ msr)
अणु
	u64 value;

	rdmsrl(msr, value);
	वापस value;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 get_rdx_init_val(व्योम)
अणु
	वापस 0x600; /* P6 family */
पूर्ण

अटल अंतरभूत व्योम kvm_inject_gp(काष्ठा kvm_vcpu *vcpu, u32 error_code)
अणु
	kvm_queue_exception_e(vcpu, GP_VECTOR, error_code);
पूर्ण

#घोषणा TSS_IOPB_BASE_OFFSET 0x66
#घोषणा TSS_BASE_SIZE 0x68
#घोषणा TSS_IOPB_SIZE (65536 / 8)
#घोषणा TSS_REसूचीECTION_SIZE (256 / 8)
#घोषणा RMODE_TSS_SIZE							\
	(TSS_BASE_SIZE + TSS_REसूचीECTION_SIZE + TSS_IOPB_SIZE + 1)

क्रमागत अणु
	TASK_SWITCH_CALL = 0,
	TASK_SWITCH_IRET = 1,
	TASK_SWITCH_JMP = 2,
	TASK_SWITCH_GATE = 3,
पूर्ण;

#घोषणा HF_GIF_MASK		(1 << 0)
#घोषणा HF_NMI_MASK		(1 << 3)
#घोषणा HF_IRET_MASK		(1 << 4)
#घोषणा HF_GUEST_MASK		(1 << 5) /* VCPU is in guest-mode */
#घोषणा HF_SMM_MASK		(1 << 6)
#घोषणा HF_SMM_INSIDE_NMI_MASK	(1 << 7)

#घोषणा __KVM_VCPU_MULTIPLE_ADDRESS_SPACE
#घोषणा KVM_ADDRESS_SPACE_NUM 2

#घोषणा kvm_arch_vcpu_memslots_id(vcpu) ((vcpu)->arch.hflags & HF_SMM_MASK ? 1 : 0)
#घोषणा kvm_memslots_क्रम_spte_role(kvm, role) __kvm_memslots(kvm, (role).smm)

यंत्रlinkage व्योम kvm_spurious_fault(व्योम);

/*
 * Hardware भवization extension inकाष्ठाions may fault अगर a
 * reboot turns off भवization जबतक processes are running.
 * Usually after catching the fault we just panic; during reboot
 * instead the inकाष्ठाion is ignored.
 */
#घोषणा __kvm_handle_fault_on_reboot(insn)				\
	"666: \n\t"							\
	insn "\n\t"							\
	"jmp	668f \n\t"						\
	"667: \n\t"							\
	"1: \n\t"							\
	".pushsection .discard.instr_begin \n\t"			\
	".long 1b - . \n\t"						\
	".popsection \n\t"						\
	"call	kvm_spurious_fault \n\t"				\
	"1: \n\t"							\
	".pushsection .discard.instr_end \n\t"				\
	".long 1b - . \n\t"						\
	".popsection \n\t"						\
	"668: \n\t"							\
	_ASM_EXTABLE(666b, 667b)

#घोषणा KVM_ARCH_WANT_MMU_NOTIFIER

पूर्णांक kvm_cpu_has_injectable_पूर्णांकr(काष्ठा kvm_vcpu *v);
पूर्णांक kvm_cpu_has_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_cpu_has_extपूर्णांक(काष्ठा kvm_vcpu *v);
पूर्णांक kvm_arch_पूर्णांकerrupt_allowed(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_cpu_get_पूर्णांकerrupt(काष्ठा kvm_vcpu *v);
व्योम kvm_vcpu_reset(काष्ठा kvm_vcpu *vcpu, bool init_event);
व्योम kvm_vcpu_reload_apic_access_page(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_pv_send_ipi(काष्ठा kvm *kvm, अचिन्हित दीर्घ ipi_biपंचांगap_low,
		    अचिन्हित दीर्घ ipi_biपंचांगap_high, u32 min,
		    अचिन्हित दीर्घ icr, पूर्णांक op_64_bit);

पूर्णांक kvm_add_user_वापस_msr(u32 msr);
पूर्णांक kvm_find_user_वापस_msr(u32 msr);
पूर्णांक kvm_set_user_वापस_msr(अचिन्हित index, u64 val, u64 mask);

अटल अंतरभूत bool kvm_is_supported_user_वापस_msr(u32 msr)
अणु
	वापस kvm_find_user_वापस_msr(msr) >= 0;
पूर्ण

u64 kvm_scale_tsc(काष्ठा kvm_vcpu *vcpu, u64 tsc);
u64 kvm_पढ़ो_l1_tsc(काष्ठा kvm_vcpu *vcpu, u64 host_tsc);

अचिन्हित दीर्घ kvm_get_linear_rip(काष्ठा kvm_vcpu *vcpu);
bool kvm_is_linear_rip(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ linear_rip);

व्योम kvm_make_mघड़ी_inprogress_request(काष्ठा kvm *kvm);
व्योम kvm_make_scan_ioapic_request(काष्ठा kvm *kvm);
व्योम kvm_make_scan_ioapic_request_mask(काष्ठा kvm *kvm,
				       अचिन्हित दीर्घ *vcpu_biपंचांगap);

bool kvm_arch_async_page_not_present(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_async_pf *work);
व्योम kvm_arch_async_page_present(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_async_pf *work);
व्योम kvm_arch_async_page_पढ़ोy(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_async_pf *work);
व्योम kvm_arch_async_page_present_queued(काष्ठा kvm_vcpu *vcpu);
bool kvm_arch_can_dequeue_async_page_present(काष्ठा kvm_vcpu *vcpu);
बाह्य bool kvm_find_async_pf_gfn(काष्ठा kvm_vcpu *vcpu, gfn_t gfn);

पूर्णांक kvm_skip_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_complete_insn_gp(काष्ठा kvm_vcpu *vcpu, पूर्णांक err);
व्योम __kvm_request_immediate_निकास(काष्ठा kvm_vcpu *vcpu);

पूर्णांक kvm_is_in_guest(व्योम);

व्योम __user *__x86_set_memory_region(काष्ठा kvm *kvm, पूर्णांक id, gpa_t gpa,
				     u32 size);
bool kvm_vcpu_is_reset_bsp(काष्ठा kvm_vcpu *vcpu);
bool kvm_vcpu_is_bsp(काष्ठा kvm_vcpu *vcpu);

bool kvm_पूर्णांकr_is_single_vcpu(काष्ठा kvm *kvm, काष्ठा kvm_lapic_irq *irq,
			     काष्ठा kvm_vcpu **dest_vcpu);

व्योम kvm_set_msi_irq(काष्ठा kvm *kvm, काष्ठा kvm_kernel_irq_routing_entry *e,
		     काष्ठा kvm_lapic_irq *irq);

अटल अंतरभूत bool kvm_irq_is_postable(काष्ठा kvm_lapic_irq *irq)
अणु
	/* We can only post Fixed and LowPrio IRQs */
	वापस (irq->delivery_mode == APIC_DM_FIXED ||
		irq->delivery_mode == APIC_DM_LOWEST);
पूर्ण

अटल अंतरभूत व्योम kvm_arch_vcpu_blocking(काष्ठा kvm_vcpu *vcpu)
अणु
	अटल_call_cond(kvm_x86_vcpu_blocking)(vcpu);
पूर्ण

अटल अंतरभूत व्योम kvm_arch_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu)
अणु
	अटल_call_cond(kvm_x86_vcpu_unblocking)(vcpu);
पूर्ण

अटल अंतरभूत व्योम kvm_arch_vcpu_block_finish(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण

अटल अंतरभूत पूर्णांक kvm_cpu_get_apicid(पूर्णांक mps_cpu)
अणु
#अगर_घोषित CONFIG_X86_LOCAL_APIC
	वापस शेष_cpu_present_to_apicid(mps_cpu);
#अन्यथा
	WARN_ON_ONCE(1);
	वापस BAD_APICID;
#पूर्ण_अगर
पूर्ण

#घोषणा put_smstate(type, buf, offset, val)                      \
	*(type *)((buf) + (offset) - 0x7e00) = val

#घोषणा GET_SMSTATE(type, buf, offset)		\
	(*(type *)((buf) + (offset) - 0x7e00))

पूर्णांक kvm_cpu_dirty_log_size(व्योम);

#पूर्ण_अगर /* _ASM_X86_KVM_HOST_H */
