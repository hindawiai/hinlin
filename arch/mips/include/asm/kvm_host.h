<शैली गुरु>
/*
* This file is subject to the terms and conditions of the GNU General Public
* License.  See the file "COPYING" in the मुख्य directory of this archive
* क्रम more details.
*
* Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
* Authors: Sanjay Lal <sanjayl@kymasys.com>
*/

#अगर_अघोषित __MIPS_KVM_HOST_H__
#घोषणा __MIPS_KVM_HOST_H__

#समावेश <linux/cpumask.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_types.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/mipsregs.h>

#समावेश <kvm/iodev.h>

/* MIPS KVM रेजिस्टर ids */
#घोषणा MIPS_CP0_32(_R, _S)					\
	(KVM_REG_MIPS_CP0 | KVM_REG_SIZE_U32 | (8 * (_R) + (_S)))

#घोषणा MIPS_CP0_64(_R, _S)					\
	(KVM_REG_MIPS_CP0 | KVM_REG_SIZE_U64 | (8 * (_R) + (_S)))

#घोषणा KVM_REG_MIPS_CP0_INDEX		MIPS_CP0_32(0, 0)
#घोषणा KVM_REG_MIPS_CP0_ENTRYLO0	MIPS_CP0_64(2, 0)
#घोषणा KVM_REG_MIPS_CP0_ENTRYLO1	MIPS_CP0_64(3, 0)
#घोषणा KVM_REG_MIPS_CP0_CONTEXT	MIPS_CP0_64(4, 0)
#घोषणा KVM_REG_MIPS_CP0_CONTEXTCONFIG	MIPS_CP0_32(4, 1)
#घोषणा KVM_REG_MIPS_CP0_USERLOCAL	MIPS_CP0_64(4, 2)
#घोषणा KVM_REG_MIPS_CP0_XCONTEXTCONFIG	MIPS_CP0_64(4, 3)
#घोषणा KVM_REG_MIPS_CP0_PAGEMASK	MIPS_CP0_32(5, 0)
#घोषणा KVM_REG_MIPS_CP0_PAGEGRAIN	MIPS_CP0_32(5, 1)
#घोषणा KVM_REG_MIPS_CP0_SEGCTL0	MIPS_CP0_64(5, 2)
#घोषणा KVM_REG_MIPS_CP0_SEGCTL1	MIPS_CP0_64(5, 3)
#घोषणा KVM_REG_MIPS_CP0_SEGCTL2	MIPS_CP0_64(5, 4)
#घोषणा KVM_REG_MIPS_CP0_PWBASE		MIPS_CP0_64(5, 5)
#घोषणा KVM_REG_MIPS_CP0_PWFIELD	MIPS_CP0_64(5, 6)
#घोषणा KVM_REG_MIPS_CP0_PWSIZE		MIPS_CP0_64(5, 7)
#घोषणा KVM_REG_MIPS_CP0_WIRED		MIPS_CP0_32(6, 0)
#घोषणा KVM_REG_MIPS_CP0_PWCTL		MIPS_CP0_32(6, 6)
#घोषणा KVM_REG_MIPS_CP0_HWRENA		MIPS_CP0_32(7, 0)
#घोषणा KVM_REG_MIPS_CP0_BADVADDR	MIPS_CP0_64(8, 0)
#घोषणा KVM_REG_MIPS_CP0_BADINSTR	MIPS_CP0_32(8, 1)
#घोषणा KVM_REG_MIPS_CP0_BADINSTRP	MIPS_CP0_32(8, 2)
#घोषणा KVM_REG_MIPS_CP0_COUNT		MIPS_CP0_32(9, 0)
#घोषणा KVM_REG_MIPS_CP0_ENTRYHI	MIPS_CP0_64(10, 0)
#घोषणा KVM_REG_MIPS_CP0_COMPARE	MIPS_CP0_32(11, 0)
#घोषणा KVM_REG_MIPS_CP0_STATUS		MIPS_CP0_32(12, 0)
#घोषणा KVM_REG_MIPS_CP0_INTCTL		MIPS_CP0_32(12, 1)
#घोषणा KVM_REG_MIPS_CP0_CAUSE		MIPS_CP0_32(13, 0)
#घोषणा KVM_REG_MIPS_CP0_EPC		MIPS_CP0_64(14, 0)
#घोषणा KVM_REG_MIPS_CP0_PRID		MIPS_CP0_32(15, 0)
#घोषणा KVM_REG_MIPS_CP0_EBASE		MIPS_CP0_64(15, 1)
#घोषणा KVM_REG_MIPS_CP0_CONFIG		MIPS_CP0_32(16, 0)
#घोषणा KVM_REG_MIPS_CP0_CONFIG1	MIPS_CP0_32(16, 1)
#घोषणा KVM_REG_MIPS_CP0_CONFIG2	MIPS_CP0_32(16, 2)
#घोषणा KVM_REG_MIPS_CP0_CONFIG3	MIPS_CP0_32(16, 3)
#घोषणा KVM_REG_MIPS_CP0_CONFIG4	MIPS_CP0_32(16, 4)
#घोषणा KVM_REG_MIPS_CP0_CONFIG5	MIPS_CP0_32(16, 5)
#घोषणा KVM_REG_MIPS_CP0_CONFIG6	MIPS_CP0_32(16, 6)
#घोषणा KVM_REG_MIPS_CP0_CONFIG7	MIPS_CP0_32(16, 7)
#घोषणा KVM_REG_MIPS_CP0_MAARI		MIPS_CP0_64(17, 2)
#घोषणा KVM_REG_MIPS_CP0_XCONTEXT	MIPS_CP0_64(20, 0)
#घोषणा KVM_REG_MIPS_CP0_DIAG		MIPS_CP0_32(22, 0)
#घोषणा KVM_REG_MIPS_CP0_ERROREPC	MIPS_CP0_64(30, 0)
#घोषणा KVM_REG_MIPS_CP0_KSCRATCH1	MIPS_CP0_64(31, 2)
#घोषणा KVM_REG_MIPS_CP0_KSCRATCH2	MIPS_CP0_64(31, 3)
#घोषणा KVM_REG_MIPS_CP0_KSCRATCH3	MIPS_CP0_64(31, 4)
#घोषणा KVM_REG_MIPS_CP0_KSCRATCH4	MIPS_CP0_64(31, 5)
#घोषणा KVM_REG_MIPS_CP0_KSCRATCH5	MIPS_CP0_64(31, 6)
#घोषणा KVM_REG_MIPS_CP0_KSCRATCH6	MIPS_CP0_64(31, 7)


#घोषणा KVM_MAX_VCPUS		16
/* memory slots that करोes not exposed to userspace */
#घोषणा KVM_PRIVATE_MEM_SLOTS	0

#घोषणा KVM_HALT_POLL_NS_DEFAULT 500000

बाह्य अचिन्हित दीर्घ GUESTID_MASK;
बाह्य अचिन्हित दीर्घ GUESTID_FIRST_VERSION;
बाह्य अचिन्हित दीर्घ GUESTID_VERSION_MASK;

#घोषणा KVM_INVALID_ADDR		0xdeadbeef

/*
 * EVA has overlapping user & kernel address spaces, so user VAs may be >
 * PAGE_OFFSET. For this reason we can't use the शेष KVM_HVA_ERR_BAD of
 * PAGE_OFFSET.
 */

#घोषणा KVM_HVA_ERR_BAD			(-1UL)
#घोषणा KVM_HVA_ERR_RO_BAD		(-2UL)

अटल अंतरभूत bool kvm_is_error_hva(अचिन्हित दीर्घ addr)
अणु
	वापस IS_ERR_VALUE(addr);
पूर्ण

काष्ठा kvm_vm_stat अणु
	uदीर्घ remote_tlb_flush;
पूर्ण;

काष्ठा kvm_vcpu_stat अणु
	u64 रुको_निकासs;
	u64 cache_निकासs;
	u64 संकेत_निकासs;
	u64 पूर्णांक_निकासs;
	u64 cop_unusable_निकासs;
	u64 tlbmod_निकासs;
	u64 tlbmiss_ld_निकासs;
	u64 tlbmiss_st_निकासs;
	u64 addrerr_st_निकासs;
	u64 addrerr_ld_निकासs;
	u64 syscall_निकासs;
	u64 resvd_inst_निकासs;
	u64 अवरोध_inst_निकासs;
	u64 trap_inst_निकासs;
	u64 msa_fpe_निकासs;
	u64 fpe_निकासs;
	u64 msa_disabled_निकासs;
	u64 flush_dcache_निकासs;
	u64 vz_gpsi_निकासs;
	u64 vz_gsfc_निकासs;
	u64 vz_hc_निकासs;
	u64 vz_grr_निकासs;
	u64 vz_gva_निकासs;
	u64 vz_ghfc_निकासs;
	u64 vz_gpa_निकासs;
	u64 vz_resvd_निकासs;
#अगर_घोषित CONFIG_CPU_LOONGSON64
	u64 vz_cpucfg_निकासs;
#पूर्ण_अगर
	u64 halt_successful_poll;
	u64 halt_attempted_poll;
	u64 halt_poll_success_ns;
	u64 halt_poll_fail_ns;
	u64 halt_poll_invalid;
	u64 halt_wakeup;
पूर्ण;

काष्ठा kvm_arch_memory_slot अणु
पूर्ण;

#अगर_घोषित CONFIG_CPU_LOONGSON64
काष्ठा ipi_state अणु
	uपूर्णांक32_t status;
	uपूर्णांक32_t en;
	uपूर्णांक32_t set;
	uपूर्णांक32_t clear;
	uपूर्णांक64_t buf[4];
पूर्ण;

काष्ठा loongson_kvm_ipi;

काष्ठा ipi_io_device अणु
	पूर्णांक node_id;
	काष्ठा loongson_kvm_ipi *ipi;
	काष्ठा kvm_io_device device;
पूर्ण;

काष्ठा loongson_kvm_ipi अणु
	spinlock_t lock;
	काष्ठा kvm *kvm;
	काष्ठा ipi_state ipistate[16];
	काष्ठा ipi_io_device dev_ipi[4];
पूर्ण;
#पूर्ण_अगर

काष्ठा kvm_arch अणु
	/* Guest physical mm */
	काष्ठा mm_काष्ठा gpa_mm;
	/* Mask of CPUs needing GPA ASID flush */
	cpumask_t asid_flush_mask;
#अगर_घोषित CONFIG_CPU_LOONGSON64
	काष्ठा loongson_kvm_ipi ipi;
#पूर्ण_अगर
पूर्ण;

#घोषणा N_MIPS_COPROC_REGS	32
#घोषणा N_MIPS_COPROC_SEL	8

काष्ठा mips_coproc अणु
	अचिन्हित दीर्घ reg[N_MIPS_COPROC_REGS][N_MIPS_COPROC_SEL];
#अगर_घोषित CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
	अचिन्हित दीर्घ stat[N_MIPS_COPROC_REGS][N_MIPS_COPROC_SEL];
#पूर्ण_अगर
पूर्ण;

/*
 * Coprocessor 0 रेजिस्टर names
 */
#घोषणा MIPS_CP0_TLB_INDEX	0
#घोषणा MIPS_CP0_TLB_RANDOM	1
#घोषणा MIPS_CP0_TLB_LOW	2
#घोषणा MIPS_CP0_TLB_LO0	2
#घोषणा MIPS_CP0_TLB_LO1	3
#घोषणा MIPS_CP0_TLB_CONTEXT	4
#घोषणा MIPS_CP0_TLB_PG_MASK	5
#घोषणा MIPS_CP0_TLB_WIRED	6
#घोषणा MIPS_CP0_HWRENA		7
#घोषणा MIPS_CP0_BAD_VADDR	8
#घोषणा MIPS_CP0_COUNT		9
#घोषणा MIPS_CP0_TLB_HI		10
#घोषणा MIPS_CP0_COMPARE	11
#घोषणा MIPS_CP0_STATUS		12
#घोषणा MIPS_CP0_CAUSE		13
#घोषणा MIPS_CP0_EXC_PC		14
#घोषणा MIPS_CP0_PRID		15
#घोषणा MIPS_CP0_CONFIG		16
#घोषणा MIPS_CP0_LLADDR		17
#घोषणा MIPS_CP0_WATCH_LO	18
#घोषणा MIPS_CP0_WATCH_HI	19
#घोषणा MIPS_CP0_TLB_XCONTEXT	20
#घोषणा MIPS_CP0_DIAG		22
#घोषणा MIPS_CP0_ECC		26
#घोषणा MIPS_CP0_CACHE_ERR	27
#घोषणा MIPS_CP0_TAG_LO		28
#घोषणा MIPS_CP0_TAG_HI		29
#घोषणा MIPS_CP0_ERROR_PC	30
#घोषणा MIPS_CP0_DEBUG		23
#घोषणा MIPS_CP0_DEPC		24
#घोषणा MIPS_CP0_PERFCNT	25
#घोषणा MIPS_CP0_ERRCTL		26
#घोषणा MIPS_CP0_DATA_LO	28
#घोषणा MIPS_CP0_DATA_HI	29
#घोषणा MIPS_CP0_DESAVE		31

#घोषणा MIPS_CP0_CONFIG_SEL	0
#घोषणा MIPS_CP0_CONFIG1_SEL	1
#घोषणा MIPS_CP0_CONFIG2_SEL	2
#घोषणा MIPS_CP0_CONFIG3_SEL	3
#घोषणा MIPS_CP0_CONFIG4_SEL	4
#घोषणा MIPS_CP0_CONFIG5_SEL	5

#घोषणा MIPS_CP0_GUESTCTL2	10
#घोषणा MIPS_CP0_GUESTCTL2_SEL	5
#घोषणा MIPS_CP0_GTOFFSET	12
#घोषणा MIPS_CP0_GTOFFSET_SEL	7

/* Resume Flags */
#घोषणा RESUME_FLAG_DR		(1<<0)	/* Reload guest nonअस्थिर state? */
#घोषणा RESUME_FLAG_HOST	(1<<1)	/* Resume host? */

#घोषणा RESUME_GUEST		0
#घोषणा RESUME_GUEST_DR		RESUME_FLAG_DR
#घोषणा RESUME_HOST		RESUME_FLAG_HOST

क्रमागत emulation_result अणु
	EMULATE_DONE,		/* no further processing */
	EMULATE_DO_MMIO,	/* kvm_run filled with MMIO request */
	EMULATE_FAIL,		/* can't emulate this inकाष्ठाion */
	EMULATE_WAIT,		/* WAIT inकाष्ठाion */
	EMULATE_PRIV_FAIL,
	EMULATE_EXCEPT,		/* A guest exception has been generated */
	EMULATE_HYPERCALL,	/* HYPCALL inकाष्ठाion */
पूर्ण;

#अगर defined(CONFIG_64BIT)
#घोषणा VPN2_MASK		GENMASK(cpu_vmbits - 1, 13)
#अन्यथा
#घोषणा VPN2_MASK		0xffffe000
#पूर्ण_अगर
#घोषणा KVM_ENTRYHI_ASID	cpu_asid_mask(&boot_cpu_data)
#घोषणा TLB_IS_GLOBAL(x)	((x).tlb_lo[0] & (x).tlb_lo[1] & ENTRYLO_G)
#घोषणा TLB_VPN2(x)		((x).tlb_hi & VPN2_MASK)
#घोषणा TLB_ASID(x)		((x).tlb_hi & KVM_ENTRYHI_ASID)
#घोषणा TLB_LO_IDX(x, va)	(((va) >> PAGE_SHIFT) & 1)
#घोषणा TLB_IS_VALID(x, va)	((x).tlb_lo[TLB_LO_IDX(x, va)] & ENTRYLO_V)
#घोषणा TLB_IS_सूचीTY(x, va)	((x).tlb_lo[TLB_LO_IDX(x, va)] & ENTRYLO_D)
#घोषणा TLB_HI_VPN2_HIT(x, y)	((TLB_VPN2(x) & ~(x).tlb_mask) ==	\
				 ((y) & VPN2_MASK & ~(x).tlb_mask))
#घोषणा TLB_HI_ASID_HIT(x, y)	(TLB_IS_GLOBAL(x) ||			\
				 TLB_ASID(x) == ((y) & KVM_ENTRYHI_ASID))

काष्ठा kvm_mips_tlb अणु
	दीर्घ tlb_mask;
	दीर्घ tlb_hi;
	दीर्घ tlb_lo[2];
पूर्ण;

#घोषणा KVM_MIPS_AUX_FPU	0x1
#घोषणा KVM_MIPS_AUX_MSA	0x2

काष्ठा kvm_vcpu_arch अणु
	व्योम *guest_ebase;
	पूर्णांक (*vcpu_run)(काष्ठा kvm_vcpu *vcpu);

	/* Host रेजिस्टरs preserved across guest mode execution */
	अचिन्हित दीर्घ host_stack;
	अचिन्हित दीर्घ host_gp;
	अचिन्हित दीर्घ host_pgd;
	अचिन्हित दीर्घ host_entryhi;

	/* Host CP0 रेजिस्टरs used when handling निकासs from guest */
	अचिन्हित दीर्घ host_cp0_badvaddr;
	अचिन्हित दीर्घ host_cp0_epc;
	u32 host_cp0_cause;
	u32 host_cp0_guestctl0;
	u32 host_cp0_badinstr;
	u32 host_cp0_badinstrp;

	/* GPRS */
	अचिन्हित दीर्घ gprs[32];
	अचिन्हित दीर्घ hi;
	अचिन्हित दीर्घ lo;
	अचिन्हित दीर्घ pc;

	/* FPU State */
	काष्ठा mips_fpu_काष्ठा fpu;
	/* Which auxiliary state is loaded (KVM_MIPS_AUX_*) */
	अचिन्हित पूर्णांक aux_inuse;

	/* COP0 State */
	काष्ठा mips_coproc *cop0;

	/* Resume PC after MMIO completion */
	अचिन्हित दीर्घ io_pc;
	/* GPR used as IO source/target */
	u32 io_gpr;

	काष्ठा hrसमयr comparecount_समयr;
	/* Count समयr control KVM रेजिस्टर */
	u32 count_ctl;
	/* Count bias from the raw समय */
	u32 count_bias;
	/* Frequency of समयr in Hz */
	u32 count_hz;
	/* Dynamic nanosecond bias (multiple of count_period) to aव्योम overflow */
	s64 count_dyn_bias;
	/* Resume समय */
	kसमय_प्रकार count_resume;
	/* Period of समयr tick in ns */
	u64 count_period;

	/* Biपंचांगask of exceptions that are pending */
	अचिन्हित दीर्घ pending_exceptions;

	/* Biपंचांगask of pending exceptions to be cleared */
	अचिन्हित दीर्घ pending_exceptions_clr;

	/* Cache some mmu pages needed inside spinlock regions */
	काष्ठा kvm_mmu_memory_cache mmu_page_cache;

	/* vcpu's vzguestid is dअगरferent on each host cpu in an smp प्रणाली */
	u32 vzguestid[NR_CPUS];

	/* wired guest TLB entries */
	काष्ठा kvm_mips_tlb *wired_tlb;
	अचिन्हित पूर्णांक wired_tlb_limit;
	अचिन्हित पूर्णांक wired_tlb_used;

	/* emulated guest MAAR रेजिस्टरs */
	अचिन्हित दीर्घ maar[6];

	/* Last CPU the VCPU state was loaded on */
	पूर्णांक last_sched_cpu;
	/* Last CPU the VCPU actually executed guest code on */
	पूर्णांक last_exec_cpu;

	/* WAIT executed */
	पूर्णांक रुको;

	u8 fpu_enabled;
	u8 msa_enabled;
पूर्ण;

अटल अंतरभूत व्योम _kvm_atomic_set_c0_guest_reg(अचिन्हित दीर्घ *reg,
						अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ temp;
	करो अणु
		__यंत्र__ __अस्थिर__(
		"	.set	push				\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"		\n"
		"	" __LL "%0, %1				\n"
		"	or	%0, %2				\n"
		"	" __SC	"%0, %1				\n"
		"	.set	pop				\n"
		: "=&r" (temp), "+m" (*reg)
		: "r" (val));
	पूर्ण जबतक (unlikely(!temp));
पूर्ण

अटल अंतरभूत व्योम _kvm_atomic_clear_c0_guest_reg(अचिन्हित दीर्घ *reg,
						  अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ temp;
	करो अणु
		__यंत्र__ __अस्थिर__(
		"	.set	push				\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"		\n"
		"	" __LL "%0, %1				\n"
		"	and	%0, %2				\n"
		"	" __SC	"%0, %1				\n"
		"	.set	pop				\n"
		: "=&r" (temp), "+m" (*reg)
		: "r" (~val));
	पूर्ण जबतक (unlikely(!temp));
पूर्ण

अटल अंतरभूत व्योम _kvm_atomic_change_c0_guest_reg(अचिन्हित दीर्घ *reg,
						   अचिन्हित दीर्घ change,
						   अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ temp;
	करो अणु
		__यंत्र__ __अस्थिर__(
		"	.set	push				\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"		\n"
		"	" __LL "%0, %1				\n"
		"	and	%0, %2				\n"
		"	or	%0, %3				\n"
		"	" __SC	"%0, %1				\n"
		"	.set	pop				\n"
		: "=&r" (temp), "+m" (*reg)
		: "r" (~change), "r" (val & change));
	पूर्ण जबतक (unlikely(!temp));
पूर्ण

/* Guest रेजिस्टर types, used in accessor build below */
#घोषणा __KVMT32	u32
#घोषणा __KVMTl	अचिन्हित दीर्घ

/*
 * __BUILD_KVM_$ops_SAVED(): kvm_$op_sw_gc0_$reg()
 * These operate on the saved guest C0 state in RAM.
 */

/* Generate saved context simple accessors */
#घोषणा __BUILD_KVM_RW_SAVED(name, type, _reg, sel)			\
अटल अंतरभूत __KVMT##type kvm_पढ़ो_sw_gc0_##name(काष्ठा mips_coproc *cop0) \
अणु									\
	वापस cop0->reg[(_reg)][(sel)];				\
पूर्ण									\
अटल अंतरभूत व्योम kvm_ग_लिखो_sw_gc0_##name(काष्ठा mips_coproc *cop0,	\
					   __KVMT##type val)		\
अणु									\
	cop0->reg[(_reg)][(sel)] = val;					\
पूर्ण

/* Generate saved context bitwise modअगरiers */
#घोषणा __BUILD_KVM_SET_SAVED(name, type, _reg, sel)			\
अटल अंतरभूत व्योम kvm_set_sw_gc0_##name(काष्ठा mips_coproc *cop0,	\
					 __KVMT##type val)		\
अणु									\
	cop0->reg[(_reg)][(sel)] |= val;				\
पूर्ण									\
अटल अंतरभूत व्योम kvm_clear_sw_gc0_##name(काष्ठा mips_coproc *cop0,	\
					   __KVMT##type val)		\
अणु									\
	cop0->reg[(_reg)][(sel)] &= ~val;				\
पूर्ण									\
अटल अंतरभूत व्योम kvm_change_sw_gc0_##name(काष्ठा mips_coproc *cop0,	\
					    __KVMT##type mask,		\
					    __KVMT##type val)		\
अणु									\
	अचिन्हित दीर्घ _mask = mask;					\
	cop0->reg[(_reg)][(sel)] &= ~_mask;				\
	cop0->reg[(_reg)][(sel)] |= val & _mask;			\
पूर्ण

/* Generate saved context atomic bitwise modअगरiers */
#घोषणा __BUILD_KVM_ATOMIC_SAVED(name, type, _reg, sel)			\
अटल अंतरभूत व्योम kvm_set_sw_gc0_##name(काष्ठा mips_coproc *cop0,	\
					 __KVMT##type val)		\
अणु									\
	_kvm_atomic_set_c0_guest_reg(&cop0->reg[(_reg)][(sel)], val);	\
पूर्ण									\
अटल अंतरभूत व्योम kvm_clear_sw_gc0_##name(काष्ठा mips_coproc *cop0,	\
					   __KVMT##type val)		\
अणु									\
	_kvm_atomic_clear_c0_guest_reg(&cop0->reg[(_reg)][(sel)], val);	\
पूर्ण									\
अटल अंतरभूत व्योम kvm_change_sw_gc0_##name(काष्ठा mips_coproc *cop0,	\
					    __KVMT##type mask,		\
					    __KVMT##type val)		\
अणु									\
	_kvm_atomic_change_c0_guest_reg(&cop0->reg[(_reg)][(sel)], mask, \
					val);				\
पूर्ण

/*
 * __BUILD_KVM_$ops_VZ(): kvm_$op_vz_gc0_$reg()
 * These operate on the VZ guest C0 context in hardware.
 */

/* Generate VZ guest context simple accessors */
#घोषणा __BUILD_KVM_RW_VZ(name, type, _reg, sel)			\
अटल अंतरभूत __KVMT##type kvm_पढ़ो_vz_gc0_##name(काष्ठा mips_coproc *cop0) \
अणु									\
	वापस पढ़ो_gc0_##name();					\
पूर्ण									\
अटल अंतरभूत व्योम kvm_ग_लिखो_vz_gc0_##name(काष्ठा mips_coproc *cop0,	\
					   __KVMT##type val)		\
अणु									\
	ग_लिखो_gc0_##name(val);						\
पूर्ण

/* Generate VZ guest context bitwise modअगरiers */
#घोषणा __BUILD_KVM_SET_VZ(name, type, _reg, sel)			\
अटल अंतरभूत व्योम kvm_set_vz_gc0_##name(काष्ठा mips_coproc *cop0,	\
					 __KVMT##type val)		\
अणु									\
	set_gc0_##name(val);						\
पूर्ण									\
अटल अंतरभूत व्योम kvm_clear_vz_gc0_##name(काष्ठा mips_coproc *cop0,	\
					   __KVMT##type val)		\
अणु									\
	clear_gc0_##name(val);						\
पूर्ण									\
अटल अंतरभूत व्योम kvm_change_vz_gc0_##name(काष्ठा mips_coproc *cop0,	\
					    __KVMT##type mask,		\
					    __KVMT##type val)		\
अणु									\
	change_gc0_##name(mask, val);					\
पूर्ण

/* Generate VZ guest context save/restore to/from saved context */
#घोषणा __BUILD_KVM_SAVE_VZ(name, _reg, sel)			\
अटल अंतरभूत व्योम kvm_restore_gc0_##name(काष्ठा mips_coproc *cop0)	\
अणु									\
	ग_लिखो_gc0_##name(cop0->reg[(_reg)][(sel)]);			\
पूर्ण									\
अटल अंतरभूत व्योम kvm_save_gc0_##name(काष्ठा mips_coproc *cop0)	\
अणु									\
	cop0->reg[(_reg)][(sel)] = पढ़ो_gc0_##name();			\
पूर्ण

/*
 * __BUILD_KVM_$ops_WRAP(): kvm_$op_$name1() -> kvm_$op_$name2()
 * These wrap a set of operations to provide them with a dअगरferent name.
 */

/* Generate simple accessor wrapper */
#घोषणा __BUILD_KVM_RW_WRAP(name1, name2, type)				\
अटल अंतरभूत __KVMT##type kvm_पढ़ो_##name1(काष्ठा mips_coproc *cop0)	\
अणु									\
	वापस kvm_पढ़ो_##name2(cop0);					\
पूर्ण									\
अटल अंतरभूत व्योम kvm_ग_लिखो_##name1(काष्ठा mips_coproc *cop0,		\
				     __KVMT##type val)			\
अणु									\
	kvm_ग_लिखो_##name2(cop0, val);					\
पूर्ण

/* Generate bitwise modअगरier wrapper */
#घोषणा __BUILD_KVM_SET_WRAP(name1, name2, type)			\
अटल अंतरभूत व्योम kvm_set_##name1(काष्ठा mips_coproc *cop0,		\
				   __KVMT##type val)			\
अणु									\
	kvm_set_##name2(cop0, val);					\
पूर्ण									\
अटल अंतरभूत व्योम kvm_clear_##name1(काष्ठा mips_coproc *cop0,		\
				     __KVMT##type val)			\
अणु									\
	kvm_clear_##name2(cop0, val);					\
पूर्ण									\
अटल अंतरभूत व्योम kvm_change_##name1(काष्ठा mips_coproc *cop0,		\
				      __KVMT##type mask,		\
				      __KVMT##type val)			\
अणु									\
	kvm_change_##name2(cop0, mask, val);				\
पूर्ण

/*
 * __BUILD_KVM_$ops_SW(): kvm_$op_c0_guest_$reg() -> kvm_$op_sw_gc0_$reg()
 * These generate accessors operating on the saved context in RAM, and wrap them
 * with the common guest C0 accessors (क्रम use by common emulation code).
 */

#घोषणा __BUILD_KVM_RW_SW(name, type, _reg, sel)			\
	__BUILD_KVM_RW_SAVED(name, type, _reg, sel)			\
	__BUILD_KVM_RW_WRAP(c0_guest_##name, sw_gc0_##name, type)

#घोषणा __BUILD_KVM_SET_SW(name, type, _reg, sel)			\
	__BUILD_KVM_SET_SAVED(name, type, _reg, sel)			\
	__BUILD_KVM_SET_WRAP(c0_guest_##name, sw_gc0_##name, type)

#घोषणा __BUILD_KVM_ATOMIC_SW(name, type, _reg, sel)			\
	__BUILD_KVM_ATOMIC_SAVED(name, type, _reg, sel)			\
	__BUILD_KVM_SET_WRAP(c0_guest_##name, sw_gc0_##name, type)

/*
 * VZ (hardware assisted भवisation)
 * These macros use the active guest state in VZ mode (hardware रेजिस्टरs),
 */

/*
 * __BUILD_KVM_$ops_HW(): kvm_$op_c0_guest_$reg() -> kvm_$op_vz_gc0_$reg()
 * These generate accessors operating on the VZ guest context in hardware, and
 * wrap them with the common guest C0 accessors (क्रम use by common emulation
 * code).
 *
 * Accessors operating on the saved context in RAM are also generated to allow
 * convenient explicit saving and restoring of the state.
 */

#घोषणा __BUILD_KVM_RW_HW(name, type, _reg, sel)			\
	__BUILD_KVM_RW_SAVED(name, type, _reg, sel)			\
	__BUILD_KVM_RW_VZ(name, type, _reg, sel)			\
	__BUILD_KVM_RW_WRAP(c0_guest_##name, vz_gc0_##name, type)	\
	__BUILD_KVM_SAVE_VZ(name, _reg, sel)

#घोषणा __BUILD_KVM_SET_HW(name, type, _reg, sel)			\
	__BUILD_KVM_SET_SAVED(name, type, _reg, sel)			\
	__BUILD_KVM_SET_VZ(name, type, _reg, sel)			\
	__BUILD_KVM_SET_WRAP(c0_guest_##name, vz_gc0_##name, type)

/*
 * We can't करो atomic modअगरications of COP0 state अगर hardware can modअगरy it.
 * Races must be handled explicitly.
 */
#घोषणा __BUILD_KVM_ATOMIC_HW	__BUILD_KVM_SET_HW

/*
 * Define accessors क्रम CP0 रेजिस्टरs that are accessible to the guest. These
 * are primarily used by common emulation code, which may need to access the
 * रेजिस्टरs dअगरferently depending on the implementation.
 *
 *    fns_hw/sw    name     type    reg num         select
 */
__BUILD_KVM_RW_HW(index,          32, MIPS_CP0_TLB_INDEX,    0)
__BUILD_KVM_RW_HW(entrylo0,       l,  MIPS_CP0_TLB_LO0,      0)
__BUILD_KVM_RW_HW(entrylo1,       l,  MIPS_CP0_TLB_LO1,      0)
__BUILD_KVM_RW_HW(context,        l,  MIPS_CP0_TLB_CONTEXT,  0)
__BUILD_KVM_RW_HW(contextconfig,  32, MIPS_CP0_TLB_CONTEXT,  1)
__BUILD_KVM_RW_HW(userlocal,      l,  MIPS_CP0_TLB_CONTEXT,  2)
__BUILD_KVM_RW_HW(xcontextconfig, l,  MIPS_CP0_TLB_CONTEXT,  3)
__BUILD_KVM_RW_HW(pagemask,       l,  MIPS_CP0_TLB_PG_MASK,  0)
__BUILD_KVM_RW_HW(pagegrain,      32, MIPS_CP0_TLB_PG_MASK,  1)
__BUILD_KVM_RW_HW(segctl0,        l,  MIPS_CP0_TLB_PG_MASK,  2)
__BUILD_KVM_RW_HW(segctl1,        l,  MIPS_CP0_TLB_PG_MASK,  3)
__BUILD_KVM_RW_HW(segctl2,        l,  MIPS_CP0_TLB_PG_MASK,  4)
__BUILD_KVM_RW_HW(pwbase,         l,  MIPS_CP0_TLB_PG_MASK,  5)
__BUILD_KVM_RW_HW(pwfield,        l,  MIPS_CP0_TLB_PG_MASK,  6)
__BUILD_KVM_RW_HW(pwsize,         l,  MIPS_CP0_TLB_PG_MASK,  7)
__BUILD_KVM_RW_HW(wired,          32, MIPS_CP0_TLB_WIRED,    0)
__BUILD_KVM_RW_HW(pwctl,          32, MIPS_CP0_TLB_WIRED,    6)
__BUILD_KVM_RW_HW(hwrena,         32, MIPS_CP0_HWRENA,       0)
__BUILD_KVM_RW_HW(badvaddr,       l,  MIPS_CP0_BAD_VADDR,    0)
__BUILD_KVM_RW_HW(badinstr,       32, MIPS_CP0_BAD_VADDR,    1)
__BUILD_KVM_RW_HW(badinstrp,      32, MIPS_CP0_BAD_VADDR,    2)
__BUILD_KVM_RW_SW(count,          32, MIPS_CP0_COUNT,        0)
__BUILD_KVM_RW_HW(entryhi,        l,  MIPS_CP0_TLB_HI,       0)
__BUILD_KVM_RW_HW(compare,        32, MIPS_CP0_COMPARE,      0)
__BUILD_KVM_RW_HW(status,         32, MIPS_CP0_STATUS,       0)
__BUILD_KVM_RW_HW(पूर्णांकctl,         32, MIPS_CP0_STATUS,       1)
__BUILD_KVM_RW_HW(cause,          32, MIPS_CP0_CAUSE,        0)
__BUILD_KVM_RW_HW(epc,            l,  MIPS_CP0_EXC_PC,       0)
__BUILD_KVM_RW_SW(prid,           32, MIPS_CP0_PRID,         0)
__BUILD_KVM_RW_HW(ebase,          l,  MIPS_CP0_PRID,         1)
__BUILD_KVM_RW_HW(config,         32, MIPS_CP0_CONFIG,       0)
__BUILD_KVM_RW_HW(config1,        32, MIPS_CP0_CONFIG,       1)
__BUILD_KVM_RW_HW(config2,        32, MIPS_CP0_CONFIG,       2)
__BUILD_KVM_RW_HW(config3,        32, MIPS_CP0_CONFIG,       3)
__BUILD_KVM_RW_HW(config4,        32, MIPS_CP0_CONFIG,       4)
__BUILD_KVM_RW_HW(config5,        32, MIPS_CP0_CONFIG,       5)
__BUILD_KVM_RW_HW(config6,        32, MIPS_CP0_CONFIG,       6)
__BUILD_KVM_RW_HW(config7,        32, MIPS_CP0_CONFIG,       7)
__BUILD_KVM_RW_SW(maari,          l,  MIPS_CP0_LLADDR,       2)
__BUILD_KVM_RW_HW(xcontext,       l,  MIPS_CP0_TLB_XCONTEXT, 0)
__BUILD_KVM_RW_HW(errorepc,       l,  MIPS_CP0_ERROR_PC,     0)
__BUILD_KVM_RW_HW(kscratch1,      l,  MIPS_CP0_DESAVE,       2)
__BUILD_KVM_RW_HW(kscratch2,      l,  MIPS_CP0_DESAVE,       3)
__BUILD_KVM_RW_HW(kscratch3,      l,  MIPS_CP0_DESAVE,       4)
__BUILD_KVM_RW_HW(kscratch4,      l,  MIPS_CP0_DESAVE,       5)
__BUILD_KVM_RW_HW(kscratch5,      l,  MIPS_CP0_DESAVE,       6)
__BUILD_KVM_RW_HW(kscratch6,      l,  MIPS_CP0_DESAVE,       7)

/* Bitwise operations (on HW state) */
__BUILD_KVM_SET_HW(status,        32, MIPS_CP0_STATUS,       0)
/* Cause can be modअगरied asynchronously from hardirq hrसमयr callback */
__BUILD_KVM_ATOMIC_HW(cause,      32, MIPS_CP0_CAUSE,        0)
__BUILD_KVM_SET_HW(ebase,         l,  MIPS_CP0_PRID,         1)

/* Bitwise operations (on saved state) */
__BUILD_KVM_SET_SAVED(config,     32, MIPS_CP0_CONFIG,       0)
__BUILD_KVM_SET_SAVED(config1,    32, MIPS_CP0_CONFIG,       1)
__BUILD_KVM_SET_SAVED(config2,    32, MIPS_CP0_CONFIG,       2)
__BUILD_KVM_SET_SAVED(config3,    32, MIPS_CP0_CONFIG,       3)
__BUILD_KVM_SET_SAVED(config4,    32, MIPS_CP0_CONFIG,       4)
__BUILD_KVM_SET_SAVED(config5,    32, MIPS_CP0_CONFIG,       5)

/* Helpers */

अटल अंतरभूत bool kvm_mips_guest_can_have_fpu(काष्ठा kvm_vcpu_arch *vcpu)
अणु
	वापस (!__builtin_स्थिरant_p(raw_cpu_has_fpu) || raw_cpu_has_fpu) &&
		vcpu->fpu_enabled;
पूर्ण

अटल अंतरभूत bool kvm_mips_guest_has_fpu(काष्ठा kvm_vcpu_arch *vcpu)
अणु
	वापस kvm_mips_guest_can_have_fpu(vcpu) &&
		kvm_पढ़ो_c0_guest_config1(vcpu->cop0) & MIPS_CONF1_FP;
पूर्ण

अटल अंतरभूत bool kvm_mips_guest_can_have_msa(काष्ठा kvm_vcpu_arch *vcpu)
अणु
	वापस (!__builtin_स्थिरant_p(cpu_has_msa) || cpu_has_msa) &&
		vcpu->msa_enabled;
पूर्ण

अटल अंतरभूत bool kvm_mips_guest_has_msa(काष्ठा kvm_vcpu_arch *vcpu)
अणु
	वापस kvm_mips_guest_can_have_msa(vcpu) &&
		kvm_पढ़ो_c0_guest_config3(vcpu->cop0) & MIPS_CONF3_MSA;
पूर्ण

काष्ठा kvm_mips_callbacks अणु
	पूर्णांक (*handle_cop_unusable)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_tlb_mod)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_tlb_ld_miss)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_tlb_st_miss)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_addr_err_st)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_addr_err_ld)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_syscall)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_res_inst)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_अवरोध)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_trap)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_msa_fpe)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_fpe)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_msa_disabled)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*handle_guest_निकास)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*hardware_enable)(व्योम);
	व्योम (*hardware_disable)(व्योम);
	पूर्णांक (*check_extension)(काष्ठा kvm *kvm, दीर्घ ext);
	पूर्णांक (*vcpu_init)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*vcpu_uninit)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*vcpu_setup)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*prepare_flush_shaकरोw)(काष्ठा kvm *kvm);
	gpa_t (*gva_to_gpa)(gva_t gva);
	व्योम (*queue_समयr_पूर्णांक)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*dequeue_समयr_पूर्णांक)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*queue_io_पूर्णांक)(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा kvm_mips_पूर्णांकerrupt *irq);
	व्योम (*dequeue_io_पूर्णांक)(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा kvm_mips_पूर्णांकerrupt *irq);
	पूर्णांक (*irq_deliver)(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority,
			   u32 cause);
	पूर्णांक (*irq_clear)(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority,
			 u32 cause);
	अचिन्हित दीर्घ (*num_regs)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*copy_reg_indices)(काष्ठा kvm_vcpu *vcpu, u64 __user *indices);
	पूर्णांक (*get_one_reg)(काष्ठा kvm_vcpu *vcpu,
			   स्थिर काष्ठा kvm_one_reg *reg, s64 *v);
	पूर्णांक (*set_one_reg)(काष्ठा kvm_vcpu *vcpu,
			   स्थिर काष्ठा kvm_one_reg *reg, s64 v);
	पूर्णांक (*vcpu_load)(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
	पूर्णांक (*vcpu_put)(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
	पूर्णांक (*vcpu_run)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*vcpu_reenter)(काष्ठा kvm_vcpu *vcpu);
पूर्ण;
बाह्य काष्ठा kvm_mips_callbacks *kvm_mips_callbacks;
पूर्णांक kvm_mips_emulation_init(काष्ठा kvm_mips_callbacks **install_callbacks);

/* Debug: dump vcpu state */
पूर्णांक kvm_arch_vcpu_dump_regs(काष्ठा kvm_vcpu *vcpu);

बाह्य पूर्णांक kvm_mips_handle_निकास(काष्ठा kvm_vcpu *vcpu);

/* Building of entry/exception code */
पूर्णांक kvm_mips_entry_setup(व्योम);
व्योम *kvm_mips_build_vcpu_run(व्योम *addr);
व्योम *kvm_mips_build_tlb_refill_exception(व्योम *addr, व्योम *handler);
व्योम *kvm_mips_build_exception(व्योम *addr, व्योम *handler);
व्योम *kvm_mips_build_निकास(व्योम *addr);

/* FPU/MSA context management */
व्योम __kvm_save_fpu(काष्ठा kvm_vcpu_arch *vcpu);
व्योम __kvm_restore_fpu(काष्ठा kvm_vcpu_arch *vcpu);
व्योम __kvm_restore_fcsr(काष्ठा kvm_vcpu_arch *vcpu);
व्योम __kvm_save_msa(काष्ठा kvm_vcpu_arch *vcpu);
व्योम __kvm_restore_msa(काष्ठा kvm_vcpu_arch *vcpu);
व्योम __kvm_restore_msa_upper(काष्ठा kvm_vcpu_arch *vcpu);
व्योम __kvm_restore_msacsr(काष्ठा kvm_vcpu_arch *vcpu);
व्योम kvm_own_fpu(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_own_msa(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_drop_fpu(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_lose_fpu(काष्ठा kvm_vcpu *vcpu);

/* TLB handling */
पूर्णांक kvm_mips_handle_vz_root_tlb_fault(अचिन्हित दीर्घ badvaddr,
				      काष्ठा kvm_vcpu *vcpu, bool ग_लिखो_fault);

पूर्णांक kvm_vz_host_tlb_inv(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ entryhi);
पूर्णांक kvm_vz_guest_tlb_lookup(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva,
			    अचिन्हित दीर्घ *gpa);
व्योम kvm_vz_local_flush_roottlb_all_guests(व्योम);
व्योम kvm_vz_local_flush_guesttlb_all(व्योम);
व्योम kvm_vz_save_guesttlb(काष्ठा kvm_mips_tlb *buf, अचिन्हित पूर्णांक index,
			  अचिन्हित पूर्णांक count);
व्योम kvm_vz_load_guesttlb(स्थिर काष्ठा kvm_mips_tlb *buf, अचिन्हित पूर्णांक index,
			  अचिन्हित पूर्णांक count);
#अगर_घोषित CONFIG_CPU_LOONGSON64
व्योम kvm_loongson_clear_guest_vtlb(व्योम);
व्योम kvm_loongson_clear_guest_ftlb(व्योम);
#पूर्ण_अगर

/* MMU handling */

bool kvm_mips_flush_gpa_pt(काष्ठा kvm *kvm, gfn_t start_gfn, gfn_t end_gfn);
पूर्णांक kvm_mips_mkclean_gpa_pt(काष्ठा kvm *kvm, gfn_t start_gfn, gfn_t end_gfn);
pgd_t *kvm_pgd_alloc(व्योम);
व्योम kvm_mmu_मुक्त_memory_caches(काष्ठा kvm_vcpu *vcpu);

#घोषणा KVM_ARCH_WANT_MMU_NOTIFIER

/* Emulation */
क्रमागत emulation_result update_pc(काष्ठा kvm_vcpu *vcpu, u32 cause);
पूर्णांक kvm_get_badinstr(u32 *opc, काष्ठा kvm_vcpu *vcpu, u32 *out);
पूर्णांक kvm_get_badinstrp(u32 *opc, काष्ठा kvm_vcpu *vcpu, u32 *out);

/**
 * kvm_is_अगरetch_fault() - Find whether a TLBL exception is due to अगरetch fault.
 * @vcpu:	Virtual CPU.
 *
 * Returns:	Whether the TLBL exception was likely due to an inकाष्ठाion
 *		fetch fault rather than a data load fault.
 */
अटल अंतरभूत bool kvm_is_अगरetch_fault(काष्ठा kvm_vcpu_arch *vcpu)
अणु
	अचिन्हित दीर्घ badvaddr = vcpu->host_cp0_badvaddr;
	अचिन्हित दीर्घ epc = msk_isa16_mode(vcpu->pc);
	u32 cause = vcpu->host_cp0_cause;

	अगर (epc == badvaddr)
		वापस true;

	/*
	 * Branches may be 32-bit or 16-bit inकाष्ठाions.
	 * This isn't exact, but we don't really support MIPS16 or microMIPS yet
	 * in KVM anyway.
	 */
	अगर ((cause & CAUSEF_BD) && badvaddr - epc <= 4)
		वापस true;

	वापस false;
पूर्ण

बाह्य क्रमागत emulation_result kvm_mips_complete_mmio_load(काष्ठा kvm_vcpu *vcpu);

u32 kvm_mips_पढ़ो_count(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_mips_ग_लिखो_count(काष्ठा kvm_vcpu *vcpu, u32 count);
व्योम kvm_mips_ग_लिखो_compare(काष्ठा kvm_vcpu *vcpu, u32 compare, bool ack);
व्योम kvm_mips_init_count(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ count_hz);
पूर्णांक kvm_mips_set_count_ctl(काष्ठा kvm_vcpu *vcpu, s64 count_ctl);
पूर्णांक kvm_mips_set_count_resume(काष्ठा kvm_vcpu *vcpu, s64 count_resume);
पूर्णांक kvm_mips_set_count_hz(काष्ठा kvm_vcpu *vcpu, s64 count_hz);
व्योम kvm_mips_count_enable_cause(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_mips_count_disable_cause(काष्ठा kvm_vcpu *vcpu);
क्रमागत hrसमयr_restart kvm_mips_count_समयout(काष्ठा kvm_vcpu *vcpu);

/* fairly पूर्णांकernal functions requiring some care to use */
पूर्णांक kvm_mips_count_disabled(काष्ठा kvm_vcpu *vcpu);
kसमय_प्रकार kvm_mips_मुक्तze_hrसमयr(काष्ठा kvm_vcpu *vcpu, u32 *count);
पूर्णांक kvm_mips_restore_hrसमयr(काष्ठा kvm_vcpu *vcpu, kसमय_प्रकार beक्रमe,
			     u32 count, पूर्णांक min_drअगरt);

व्योम kvm_vz_acquire_hसमयr(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_vz_lose_hसमयr(काष्ठा kvm_vcpu *vcpu);

क्रमागत emulation_result kvm_mips_emulate_store(जोड़ mips_inकाष्ठाion inst,
					     u32 cause,
					     काष्ठा kvm_vcpu *vcpu);
क्रमागत emulation_result kvm_mips_emulate_load(जोड़ mips_inकाष्ठाion inst,
					    u32 cause,
					    काष्ठा kvm_vcpu *vcpu);

/* COP0 */
क्रमागत emulation_result kvm_mips_emul_रुको(काष्ठा kvm_vcpu *vcpu);

/* Hypercalls (hypcall.c) */

क्रमागत emulation_result kvm_mips_emul_hypcall(काष्ठा kvm_vcpu *vcpu,
					    जोड़ mips_inकाष्ठाion inst);
पूर्णांक kvm_mips_handle_hypcall(काष्ठा kvm_vcpu *vcpu);

/* Misc */
बाह्य व्योम kvm_mips_dump_stats(काष्ठा kvm_vcpu *vcpu);
बाह्य अचिन्हित दीर्घ kvm_mips_get_ramsize(काष्ठा kvm *kvm);
बाह्य पूर्णांक kvm_vcpu_ioctl_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा kvm_mips_पूर्णांकerrupt *irq);

अटल अंतरभूत व्योम kvm_arch_hardware_unsetup(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sync_events(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_मुक्त_memslot(काष्ठा kvm *kvm,
					 काष्ठा kvm_memory_slot *slot) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_memslots_updated(काष्ठा kvm *kvm, u64 gen) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_blocking(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvm_arch_vcpu_block_finish(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण

#घोषणा __KVM_HAVE_ARCH_FLUSH_REMOTE_TLB
पूर्णांक kvm_arch_flush_remote_tlb(काष्ठा kvm *kvm);

#पूर्ण_अगर /* __MIPS_KVM_HOST_H__ */
