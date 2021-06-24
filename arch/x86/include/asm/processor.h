<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PROCESSOR_H
#घोषणा _ASM_X86_PROCESSOR_H

#समावेश <यंत्र/processor-flags.h>

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;
काष्ठा mm_काष्ठा;
काष्ठा io_biपंचांगap;
काष्ठा vm86;

#समावेश <यंत्र/math_emu.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/types.h>
#समावेश <uapi/यंत्र/sigcontext.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgtable_types.h>
#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/desc_defs.h>
#समावेश <यंत्र/nops.h>
#समावेश <यंत्र/special_insns.h>
#समावेश <यंत्र/fpu/types.h>
#समावेश <यंत्र/unwind_hपूर्णांकs.h>
#समावेश <यंत्र/vmxfeatures.h>
#समावेश <यंत्र/vdso/processor.h>

#समावेश <linux/personality.h>
#समावेश <linux/cache.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/math64.h>
#समावेश <linux/err.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/mem_encrypt.h>

/*
 * We handle most unaligned accesses in hardware.  On the other hand
 * unaligned DMA can be quite expensive on some Nehalem processors.
 *
 * Based on this we disable the IP header alignment in network drivers.
 */
#घोषणा NET_IP_ALIGN	0

#घोषणा HBP_NUM 4

/*
 * These alignment स्थिरraपूर्णांकs are क्रम perक्रमmance in the vSMP हाल,
 * but in the task_काष्ठा हाल we must also meet hardware imposed
 * alignment requirements of the FPU state:
 */
#अगर_घोषित CONFIG_X86_VSMP
# define ARCH_MIN_TASKALIGN		(1 << INTERNODE_CACHE_SHIFT)
# define ARCH_MIN_MMSTRUCT_ALIGN	(1 << INTERNODE_CACHE_SHIFT)
#अन्यथा
# define ARCH_MIN_TASKALIGN		__alignof__(जोड़ fpregs_state)
# define ARCH_MIN_MMSTRUCT_ALIGN	0
#पूर्ण_अगर

क्रमागत tlb_infos अणु
	ENTRIES,
	NR_INFO
पूर्ण;

बाह्य u16 __पढ़ो_mostly tlb_lli_4k[NR_INFO];
बाह्य u16 __पढ़ो_mostly tlb_lli_2m[NR_INFO];
बाह्य u16 __पढ़ो_mostly tlb_lli_4m[NR_INFO];
बाह्य u16 __पढ़ो_mostly tlb_lld_4k[NR_INFO];
बाह्य u16 __पढ़ो_mostly tlb_lld_2m[NR_INFO];
बाह्य u16 __पढ़ो_mostly tlb_lld_4m[NR_INFO];
बाह्य u16 __पढ़ो_mostly tlb_lld_1g[NR_INFO];

/*
 *  CPU type and hardware bug flags. Kept separately क्रम each CPU.
 *  Members of this काष्ठाure are referenced in head_32.S, so think twice
 *  beक्रमe touching them. [mj]
 */

काष्ठा cpuinfo_x86 अणु
	__u8			x86;		/* CPU family */
	__u8			x86_venकरोr;	/* CPU venकरोr */
	__u8			x86_model;
	__u8			x86_stepping;
#अगर_घोषित CONFIG_X86_64
	/* Number of 4K pages in DTLB/ITLB combined(in pages): */
	पूर्णांक			x86_tlbsize;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_VMX_FEATURE_NAMES
	__u32			vmx_capability[NVMXINTS];
#पूर्ण_अगर
	__u8			x86_virt_bits;
	__u8			x86_phys_bits;
	/* CPUID वापसed core id bits: */
	__u8			x86_coreid_bits;
	__u8			cu_id;
	/* Max extended CPUID function supported: */
	__u32			extended_cpuid_level;
	/* Maximum supported CPUID level, -1=no CPUID: */
	पूर्णांक			cpuid_level;
	/*
	 * Align to size of अचिन्हित दीर्घ because the x86_capability array
	 * is passed to bitops which require the alignment. Use unnamed
	 * जोड़ to enक्रमce the array is aligned to size of अचिन्हित दीर्घ.
	 */
	जोड़ अणु
		__u32		x86_capability[NCAPINTS + NBUGINTS];
		अचिन्हित दीर्घ	x86_capability_alignment;
	पूर्ण;
	अक्षर			x86_venकरोr_id[16];
	अक्षर			x86_model_id[64];
	/* in KB - valid क्रम CPUS which support this call: */
	अचिन्हित पूर्णांक		x86_cache_size;
	पूर्णांक			x86_cache_alignment;	/* In bytes */
	/* Cache QoS architectural values, valid only on the BSP: */
	पूर्णांक			x86_cache_max_rmid;	/* max index */
	पूर्णांक			x86_cache_occ_scale;	/* scale to bytes */
	पूर्णांक			x86_cache_mbm_width_offset;
	पूर्णांक			x86_घातer;
	अचिन्हित दीर्घ		loops_per_jअगरfy;
	/* cpuid वापसed max cores value: */
	u16			x86_max_cores;
	u16			apicid;
	u16			initial_apicid;
	u16			x86_clflush_size;
	/* number of cores as seen by the OS: */
	u16			booted_cores;
	/* Physical processor id: */
	u16			phys_proc_id;
	/* Logical processor id: */
	u16			logical_proc_id;
	/* Core id: */
	u16			cpu_core_id;
	u16			cpu_die_id;
	u16			logical_die_id;
	/* Index पूर्णांकo per_cpu list: */
	u16			cpu_index;
	u32			microcode;
	/* Address space bits used by the cache पूर्णांकernally */
	u8			x86_cache_bits;
	अचिन्हित		initialized : 1;
पूर्ण __अक्रमomize_layout;

काष्ठा cpuid_regs अणु
	u32 eax, ebx, ecx, edx;
पूर्ण;

क्रमागत cpuid_regs_idx अणु
	CPUID_EAX = 0,
	CPUID_EBX,
	CPUID_ECX,
	CPUID_EDX,
पूर्ण;

#घोषणा X86_VENDOR_INTEL	0
#घोषणा X86_VENDOR_CYRIX	1
#घोषणा X86_VENDOR_AMD		2
#घोषणा X86_VENDOR_UMC		3
#घोषणा X86_VENDOR_CENTAUR	5
#घोषणा X86_VENDOR_TRANSMETA	7
#घोषणा X86_VENDOR_NSC		8
#घोषणा X86_VENDOR_HYGON	9
#घोषणा X86_VENDOR_ZHAOXIN	10
#घोषणा X86_VENDOR_NUM		11

#घोषणा X86_VENDOR_UNKNOWN	0xff

/*
 * capabilities of CPUs
 */
बाह्य काष्ठा cpuinfo_x86	boot_cpu_data;
बाह्य काष्ठा cpuinfo_x86	new_cpu_data;

बाह्य __u32			cpu_caps_cleared[NCAPINTS + NBUGINTS];
बाह्य __u32			cpu_caps_set[NCAPINTS + NBUGINTS];

#अगर_घोषित CONFIG_SMP
DECLARE_PER_CPU_READ_MOSTLY(काष्ठा cpuinfo_x86, cpu_info);
#घोषणा cpu_data(cpu)		per_cpu(cpu_info, cpu)
#अन्यथा
#घोषणा cpu_info		boot_cpu_data
#घोषणा cpu_data(cpu)		boot_cpu_data
#पूर्ण_अगर

बाह्य स्थिर काष्ठा seq_operations cpuinfo_op;

#घोषणा cache_line_size()	(boot_cpu_data.x86_cache_alignment)

बाह्य व्योम cpu_detect(काष्ठा cpuinfo_x86 *c);

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ l1tf_pfn_limit(व्योम)
अणु
	वापस BIT_ULL(boot_cpu_data.x86_cache_bits - 1 - PAGE_SHIFT);
पूर्ण

बाह्य व्योम early_cpu_init(व्योम);
बाह्य व्योम identअगरy_boot_cpu(व्योम);
बाह्य व्योम identअगरy_secondary_cpu(काष्ठा cpuinfo_x86 *);
बाह्य व्योम prपूर्णांक_cpu_info(काष्ठा cpuinfo_x86 *);
व्योम prपूर्णांक_cpu_msr(काष्ठा cpuinfo_x86 *);

#अगर_घोषित CONFIG_X86_32
बाह्य पूर्णांक have_cpuid_p(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक have_cpuid_p(व्योम)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत व्योम native_cpuid(अचिन्हित पूर्णांक *eax, अचिन्हित पूर्णांक *ebx,
				अचिन्हित पूर्णांक *ecx, अचिन्हित पूर्णांक *edx)
अणु
	/* ecx is often an input as well as an output. */
	यंत्र अस्थिर("cpuid"
	    : "=a" (*eax),
	      "=b" (*ebx),
	      "=c" (*ecx),
	      "=d" (*edx)
	    : "0" (*eax), "2" (*ecx)
	    : "memory");
पूर्ण

#घोषणा native_cpuid_reg(reg)					\
अटल अंतरभूत अचिन्हित पूर्णांक native_cpuid_##reg(अचिन्हित पूर्णांक op)	\
अणु								\
	अचिन्हित पूर्णांक eax = op, ebx, ecx = 0, edx;		\
								\
	native_cpuid(&eax, &ebx, &ecx, &edx);			\
								\
	वापस reg;						\
पूर्ण

/*
 * Native CPUID functions वापसing a single datum.
 */
native_cpuid_reg(eax)
native_cpuid_reg(ebx)
native_cpuid_reg(ecx)
native_cpuid_reg(edx)

/*
 * Friendlier CR3 helpers.
 */
अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_cr3_pa(व्योम)
अणु
	वापस __पढ़ो_cr3() & CR3_ADDR_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ native_पढ़ो_cr3_pa(व्योम)
अणु
	वापस __native_पढ़ो_cr3() & CR3_ADDR_MASK;
पूर्ण

अटल अंतरभूत व्योम load_cr3(pgd_t *pgdir)
अणु
	ग_लिखो_cr3(__sme_pa(pgdir));
पूर्ण

/*
 * Note that जबतक the legacy 'TSS' name comes from 'Task State Segment',
 * on modern x86 CPUs the TSS also holds inक्रमmation important to 64-bit mode,
 * unrelated to the task-चयन mechanism:
 */
#अगर_घोषित CONFIG_X86_32
/* This is the TSS defined by the hardware. */
काष्ठा x86_hw_tss अणु
	अचिन्हित लघु		back_link, __blh;
	अचिन्हित दीर्घ		sp0;
	अचिन्हित लघु		ss0, __ss0h;
	अचिन्हित दीर्घ		sp1;

	/*
	 * We करोn't use ring 1, so ss1 is a convenient scratch space in
	 * the same cacheline as sp0.  We use ss1 to cache the value in
	 * MSR_IA32_SYSENTER_CS.  When we context चयन
	 * MSR_IA32_SYSENTER_CS, we first check अगर the new value being
	 * written matches ss1, and, अगर it's not, then we wrmsr the new
	 * value and update ss1.
	 *
	 * The only reason we context चयन MSR_IA32_SYSENTER_CS is
	 * that we set it to zero in vm86 tasks to aव्योम corrupting the
	 * stack अगर we were to go through the sysenter path from vm86
	 * mode.
	 */
	अचिन्हित लघु		ss1;	/* MSR_IA32_SYSENTER_CS */

	अचिन्हित लघु		__ss1h;
	अचिन्हित दीर्घ		sp2;
	अचिन्हित लघु		ss2, __ss2h;
	अचिन्हित दीर्घ		__cr3;
	अचिन्हित दीर्घ		ip;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		ax;
	अचिन्हित दीर्घ		cx;
	अचिन्हित दीर्घ		dx;
	अचिन्हित दीर्घ		bx;
	अचिन्हित दीर्घ		sp;
	अचिन्हित दीर्घ		bp;
	अचिन्हित दीर्घ		si;
	अचिन्हित दीर्घ		di;
	अचिन्हित लघु		es, __esh;
	अचिन्हित लघु		cs, __csh;
	अचिन्हित लघु		ss, __ssh;
	अचिन्हित लघु		ds, __dsh;
	अचिन्हित लघु		fs, __fsh;
	अचिन्हित लघु		gs, __gsh;
	अचिन्हित लघु		ldt, __ldth;
	अचिन्हित लघु		trace;
	अचिन्हित लघु		io_biपंचांगap_base;

पूर्ण __attribute__((packed));
#अन्यथा
काष्ठा x86_hw_tss अणु
	u32			reserved1;
	u64			sp0;
	u64			sp1;

	/*
	 * Since Linux करोes not use ring 2, the 'sp2' slot is unused by
	 * hardware.  entry_SYSCALL_64 uses it as scratch space to stash
	 * the user RSP value.
	 */
	u64			sp2;

	u64			reserved2;
	u64			ist[7];
	u32			reserved3;
	u32			reserved4;
	u16			reserved5;
	u16			io_biपंचांगap_base;

पूर्ण __attribute__((packed));
#पूर्ण_अगर

/*
 * IO-biपंचांगap sizes:
 */
#घोषणा IO_BITMAP_BITS			65536
#घोषणा IO_BITMAP_BYTES			(IO_BITMAP_BITS / BITS_PER_BYTE)
#घोषणा IO_BITMAP_LONGS			(IO_BITMAP_BYTES / माप(दीर्घ))

#घोषणा IO_BITMAP_OFFSET_VALID_MAP				\
	(दुरत्व(काष्ठा tss_काष्ठा, io_biपंचांगap.biपंचांगap) -	\
	 दुरत्व(काष्ठा tss_काष्ठा, x86_tss))

#घोषणा IO_BITMAP_OFFSET_VALID_ALL				\
	(दुरत्व(काष्ठा tss_काष्ठा, io_biपंचांगap.mapall) -	\
	 दुरत्व(काष्ठा tss_काष्ठा, x86_tss))

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
/*
 * माप(अचिन्हित दीर्घ) coming from an extra "long" at the end of the
 * iobiपंचांगap. The limit is inclusive, i.e. the last valid byte.
 */
# define __KERNEL_TSS_LIMIT	\
	(IO_BITMAP_OFFSET_VALID_ALL + IO_BITMAP_BYTES + \
	 माप(अचिन्हित दीर्घ) - 1)
#अन्यथा
# define __KERNEL_TSS_LIMIT	\
	(दुरत्व(काष्ठा tss_काष्ठा, x86_tss) + माप(काष्ठा x86_hw_tss) - 1)
#पूर्ण_अगर

/* Base offset outside of TSS_LIMIT so unpriviledged IO causes #GP */
#घोषणा IO_BITMAP_OFFSET_INVALID	(__KERNEL_TSS_LIMIT + 1)

काष्ठा entry_stack अणु
	अक्षर	stack[PAGE_SIZE];
पूर्ण;

काष्ठा entry_stack_page अणु
	काष्ठा entry_stack stack;
पूर्ण __aligned(PAGE_SIZE);

/*
 * All IO biपंचांगap related data stored in the TSS:
 */
काष्ठा x86_io_biपंचांगap अणु
	/* The sequence number of the last active biपंचांगap. */
	u64			prev_sequence;

	/*
	 * Store the dirty size of the last io biपंचांगap offender. The next
	 * one will have to करो the cleanup as the चयन out to a non io
	 * biपंचांगap user will just set x86_tss.io_biपंचांगap_base to a value
	 * outside of the TSS limit. So क्रम sane tasks there is no need to
	 * actually touch the io_biपंचांगap at all.
	 */
	अचिन्हित पूर्णांक		prev_max;

	/*
	 * The extra 1 is there because the CPU will access an
	 * additional byte beyond the end of the IO permission
	 * biपंचांगap. The extra byte must be all 1 bits, and must
	 * be within the limit.
	 */
	अचिन्हित दीर्घ		biपंचांगap[IO_BITMAP_LONGS + 1];

	/*
	 * Special I/O biपंचांगap to emulate IOPL(3). All bytes zero,
	 * except the additional byte at the end.
	 */
	अचिन्हित दीर्घ		mapall[IO_BITMAP_LONGS + 1];
पूर्ण;

काष्ठा tss_काष्ठा अणु
	/*
	 * The fixed hardware portion.  This must not cross a page boundary
	 * at risk of violating the SDM's advice and potentially triggering
	 * errata.
	 */
	काष्ठा x86_hw_tss	x86_tss;

	काष्ठा x86_io_biपंचांगap	io_biपंचांगap;
पूर्ण __aligned(PAGE_SIZE);

DECLARE_PER_CPU_PAGE_ALIGNED(काष्ठा tss_काष्ठा, cpu_tss_rw);

/* Per CPU पूर्णांकerrupt stacks */
काष्ठा irq_stack अणु
	अक्षर		stack[IRQ_STACK_SIZE];
पूर्ण __aligned(IRQ_STACK_SIZE);

DECLARE_PER_CPU(अचिन्हित दीर्घ, cpu_current_top_of_stack);

#अगर_घोषित CONFIG_X86_64
काष्ठा fixed_percpu_data अणु
	/*
	 * GCC hardcodes the stack canary as %gs:40.  Since the
	 * irq_stack is the object at %gs:0, we reserve the bottom
	 * 48 bytes of the irq stack क्रम the canary.
	 *
	 * Once we are willing to require -mstack-protector-guard-symbol=
	 * support क्रम x86_64 stackprotector, we can get rid of this.
	 */
	अक्षर		gs_base[40];
	अचिन्हित दीर्घ	stack_canary;
पूर्ण;

DECLARE_PER_CPU_FIRST(काष्ठा fixed_percpu_data, fixed_percpu_data) __visible;
DECLARE_INIT_PER_CPU(fixed_percpu_data);

अटल अंतरभूत अचिन्हित दीर्घ cpu_kernelmode_gs_base(पूर्णांक cpu)
अणु
	वापस (अचिन्हित दीर्घ)per_cpu(fixed_percpu_data.gs_base, cpu);
पूर्ण

DECLARE_PER_CPU(व्योम *, hardirq_stack_ptr);
DECLARE_PER_CPU(bool, hardirq_stack_inuse);
बाह्य यंत्रlinkage व्योम ignore_sysret(व्योम);

/* Save actual FS/GS selectors and bases to current->thपढ़ो */
व्योम current_save_fsgs(व्योम);
#अन्यथा	/* X86_64 */
#अगर_घोषित CONFIG_STACKPROTECTOR
DECLARE_PER_CPU(अचिन्हित दीर्घ, __stack_chk_guard);
#पूर्ण_अगर
DECLARE_PER_CPU(काष्ठा irq_stack *, hardirq_stack_ptr);
DECLARE_PER_CPU(काष्ठा irq_stack *, softirq_stack_ptr);
#पूर्ण_अगर	/* !X86_64 */

बाह्य अचिन्हित पूर्णांक fpu_kernel_xstate_size;
बाह्य अचिन्हित पूर्णांक fpu_user_xstate_size;

काष्ठा perf_event;

काष्ठा thपढ़ो_काष्ठा अणु
	/* Cached TLS descriptors: */
	काष्ठा desc_काष्ठा	tls_array[GDT_ENTRY_TLS_ENTRIES];
#अगर_घोषित CONFIG_X86_32
	अचिन्हित दीर्घ		sp0;
#पूर्ण_अगर
	अचिन्हित दीर्घ		sp;
#अगर_घोषित CONFIG_X86_32
	अचिन्हित दीर्घ		sysenter_cs;
#अन्यथा
	अचिन्हित लघु		es;
	अचिन्हित लघु		ds;
	अचिन्हित लघु		fsindex;
	अचिन्हित लघु		gsindex;
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
	अचिन्हित दीर्घ		fsbase;
	अचिन्हित दीर्घ		gsbase;
#अन्यथा
	/*
	 * XXX: this could presumably be अचिन्हित लघु.  Alternatively,
	 * 32-bit kernels could be taught to use fsindex instead.
	 */
	अचिन्हित दीर्घ fs;
	अचिन्हित दीर्घ gs;
#पूर्ण_अगर

	/* Save middle states of ptrace अवरोधpoपूर्णांकs */
	काष्ठा perf_event	*ptrace_bps[HBP_NUM];
	/* Debug status used क्रम traps, single steps, etc... */
	अचिन्हित दीर्घ           भव_dr6;
	/* Keep track of the exact dr7 value set by the user */
	अचिन्हित दीर्घ           ptrace_dr7;
	/* Fault info: */
	अचिन्हित दीर्घ		cr2;
	अचिन्हित दीर्घ		trap_nr;
	अचिन्हित दीर्घ		error_code;
#अगर_घोषित CONFIG_VM86
	/* Virtual 86 mode info */
	काष्ठा vm86		*vm86;
#पूर्ण_अगर
	/* IO permissions: */
	काष्ठा io_biपंचांगap	*io_biपंचांगap;

	/*
	 * IOPL. Privilege level dependent I/O permission which is
	 * emulated via the I/O biपंचांगap to prevent user space from disabling
	 * पूर्णांकerrupts.
	 */
	अचिन्हित दीर्घ		iopl_emul;

	अचिन्हित पूर्णांक		sig_on_uaccess_err:1;

	/* Floating poपूर्णांक and extended processor state */
	काष्ठा fpu		fpu;
	/*
	 * WARNING: 'fpu' is dynamically-sized.  It *MUST* be at
	 * the end.
	 */
पूर्ण;

/* Whitelist the FPU state from the task_काष्ठा क्रम hardened usercopy. */
अटल अंतरभूत व्योम arch_thपढ़ो_काष्ठा_whitelist(अचिन्हित दीर्घ *offset,
						अचिन्हित दीर्घ *size)
अणु
	*offset = दुरत्व(काष्ठा thपढ़ो_काष्ठा, fpu.state);
	*size = fpu_kernel_xstate_size;
पूर्ण

अटल अंतरभूत व्योम
native_load_sp0(अचिन्हित दीर्घ sp0)
अणु
	this_cpu_ग_लिखो(cpu_tss_rw.x86_tss.sp0, sp0);
पूर्ण

अटल __always_अंतरभूत व्योम native_swapgs(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	यंत्र अस्थिर("swapgs" ::: "memory");
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ current_top_of_stack(व्योम)
अणु
	/*
	 *  We can't पढ़ो directly from tss.sp0: sp0 on x86_32 is special in
	 *  and around vm86 mode and sp0 on x86_64 is special because of the
	 *  entry trampoline.
	 */
	वापस this_cpu_पढ़ो_stable(cpu_current_top_of_stack);
पूर्ण

अटल अंतरभूत bool on_thपढ़ो_stack(व्योम)
अणु
	वापस (अचिन्हित दीर्घ)(current_top_of_stack() -
			       current_stack_poपूर्णांकer) < THREAD_SIZE;
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा
#घोषणा __cpuid			native_cpuid

अटल अंतरभूत व्योम load_sp0(अचिन्हित दीर्घ sp0)
अणु
	native_load_sp0(sp0);
पूर्ण

#पूर्ण_अगर /* CONFIG_PARAVIRT_XXL */

/* Free all resources held by a thपढ़ो. */
बाह्य व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

/*
 * Generic CPUID function
 * clear %ecx since some cpus (Cyrix MII) करो not set or clear %ecx
 * resulting in stale रेजिस्टर contents being वापसed.
 */
अटल अंतरभूत व्योम cpuid(अचिन्हित पूर्णांक op,
			 अचिन्हित पूर्णांक *eax, अचिन्हित पूर्णांक *ebx,
			 अचिन्हित पूर्णांक *ecx, अचिन्हित पूर्णांक *edx)
अणु
	*eax = op;
	*ecx = 0;
	__cpuid(eax, ebx, ecx, edx);
पूर्ण

/* Some CPUID calls want 'count' to be placed in ecx */
अटल अंतरभूत व्योम cpuid_count(अचिन्हित पूर्णांक op, पूर्णांक count,
			       अचिन्हित पूर्णांक *eax, अचिन्हित पूर्णांक *ebx,
			       अचिन्हित पूर्णांक *ecx, अचिन्हित पूर्णांक *edx)
अणु
	*eax = op;
	*ecx = count;
	__cpuid(eax, ebx, ecx, edx);
पूर्ण

/*
 * CPUID functions वापसing a single datum
 */
अटल अंतरभूत अचिन्हित पूर्णांक cpuid_eax(अचिन्हित पूर्णांक op)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	वापस eax;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpuid_ebx(अचिन्हित पूर्णांक op)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	वापस ebx;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpuid_ecx(अचिन्हित पूर्णांक op)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	वापस ecx;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpuid_edx(अचिन्हित पूर्णांक op)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;

	cpuid(op, &eax, &ebx, &ecx, &edx);

	वापस edx;
पूर्ण

बाह्य व्योम select_idle_routine(स्थिर काष्ठा cpuinfo_x86 *c);
बाह्य व्योम amd_e400_c1e_apic_setup(व्योम);

बाह्य अचिन्हित दीर्घ		boot_option_idle_override;

क्रमागत idle_boot_override अणुIDLE_NO_OVERRIDE=0, IDLE_HALT, IDLE_NOMWAIT,
			 IDLE_POLLपूर्ण;

बाह्य व्योम enable_sep_cpu(व्योम);
बाह्य पूर्णांक sysenter_setup(व्योम);


/* Defined in head.S */
बाह्य काष्ठा desc_ptr		early_gdt_descr;

बाह्य व्योम चयन_to_new_gdt(पूर्णांक);
बाह्य व्योम load_direct_gdt(पूर्णांक);
बाह्य व्योम load_fixmap_gdt(पूर्णांक);
बाह्य व्योम load_percpu_segment(पूर्णांक);
बाह्य व्योम cpu_init(व्योम);
बाह्य व्योम cpu_init_exception_handling(व्योम);
बाह्य व्योम cr4_init(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ get_debugctlmsr(व्योम)
अणु
	अचिन्हित दीर्घ debugctlmsr = 0;

#अगर_अघोषित CONFIG_X86_DEBUGCTLMSR
	अगर (boot_cpu_data.x86 < 6)
		वापस 0;
#पूर्ण_अगर
	rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctlmsr);

	वापस debugctlmsr;
पूर्ण

अटल अंतरभूत व्योम update_debugctlmsr(अचिन्हित दीर्घ debugctlmsr)
अणु
#अगर_अघोषित CONFIG_X86_DEBUGCTLMSR
	अगर (boot_cpu_data.x86 < 6)
		वापस;
#पूर्ण_अगर
	wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctlmsr);
पूर्ण

बाह्य व्योम set_task_blockstep(काष्ठा task_काष्ठा *task, bool on);

/* Boot loader type from the setup header: */
बाह्य पूर्णांक			bootloader_type;
बाह्य पूर्णांक			bootloader_version;

बाह्य अक्षर			ignore_fpu_irq;

#घोषणा HAVE_ARCH_PICK_MMAP_LAYOUT 1
#घोषणा ARCH_HAS_PREFETCHW
#घोषणा ARCH_HAS_SPINLOCK_PREFETCH

#अगर_घोषित CONFIG_X86_32
# define BASE_PREFETCH		""
# define ARCH_HAS_PREFETCH
#अन्यथा
# define BASE_PREFETCH		"prefetcht0 %P1"
#पूर्ण_अगर

/*
 * Prefetch inकाष्ठाions क्रम Pentium III (+) and AMD Athlon (+)
 *
 * It's not worth to care about 3dnow prefetches क्रम the K6
 * because they are microcoded there and very slow.
 */
अटल अंतरभूत व्योम prefetch(स्थिर व्योम *x)
अणु
	alternative_input(BASE_PREFETCH, "prefetchnta %P1",
			  X86_FEATURE_XMM,
			  "m" (*(स्थिर अक्षर *)x));
पूर्ण

/*
 * 3dnow prefetch to get an exclusive cache line.
 * Useful क्रम spinlocks to aव्योम one state transition in the
 * cache coherency protocol:
 */
अटल __always_अंतरभूत व्योम prefetchw(स्थिर व्योम *x)
अणु
	alternative_input(BASE_PREFETCH, "prefetchw %P1",
			  X86_FEATURE_3DNOWPREFETCH,
			  "m" (*(स्थिर अक्षर *)x));
पूर्ण

अटल अंतरभूत व्योम spin_lock_prefetch(स्थिर व्योम *x)
अणु
	prefetchw(x);
पूर्ण

#घोषणा TOP_OF_INIT_STACK ((अचिन्हित दीर्घ)&init_stack + माप(init_stack) - \
			   TOP_OF_KERNEL_STACK_PADDING)

#घोषणा task_top_of_stack(task) ((अचिन्हित दीर्घ)(task_pt_regs(task) + 1))

#घोषणा task_pt_regs(task) \
(अणु									\
	अचिन्हित दीर्घ __ptr = (अचिन्हित दीर्घ)task_stack_page(task);	\
	__ptr += THREAD_SIZE - TOP_OF_KERNEL_STACK_PADDING;		\
	((काष्ठा pt_regs *)__ptr) - 1;					\
पूर्ण)

#अगर_घोषित CONFIG_X86_32
#घोषणा INIT_THREAD  अणु							  \
	.sp0			= TOP_OF_INIT_STACK,			  \
	.sysenter_cs		= __KERNEL_CS,				  \
पूर्ण

#घोषणा KSTK_ESP(task)		(task_pt_regs(task)->sp)

#अन्यथा
#घोषणा INIT_THREAD अणु पूर्ण

बाह्य अचिन्हित दीर्घ KSTK_ESP(काष्ठा task_काष्ठा *task);

#पूर्ण_अगर /* CONFIG_X86_64 */

बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ new_ip,
					       अचिन्हित दीर्घ new_sp);

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा __TASK_UNMAPPED_BASE(task_size)	(PAGE_ALIGN(task_size / 3))
#घोषणा TASK_UNMAPPED_BASE		__TASK_UNMAPPED_BASE(TASK_SIZE_LOW)

#घोषणा KSTK_EIP(task)		(task_pt_regs(task)->ip)

/* Get/set a process' ability to use the बारtamp counter inकाष्ठाion */
#घोषणा GET_TSC_CTL(adr)	get_tsc_mode((adr))
#घोषणा SET_TSC_CTL(val)	set_tsc_mode((val))

बाह्य पूर्णांक get_tsc_mode(अचिन्हित दीर्घ adr);
बाह्य पूर्णांक set_tsc_mode(अचिन्हित पूर्णांक val);

DECLARE_PER_CPU(u64, msr_misc_features_shaकरोw);

#अगर_घोषित CONFIG_CPU_SUP_AMD
बाह्य u32 amd_get_nodes_per_socket(व्योम);
बाह्य u32 amd_get_highest_perf(व्योम);
#अन्यथा
अटल अंतरभूत u32 amd_get_nodes_per_socket(व्योम)	अणु वापस 0; पूर्ण
अटल अंतरभूत u32 amd_get_highest_perf(व्योम)		अणु वापस 0; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत uपूर्णांक32_t hypervisor_cpuid_base(स्थिर अक्षर *sig, uपूर्णांक32_t leaves)
अणु
	uपूर्णांक32_t base, eax, signature[3];

	क्रम (base = 0x40000000; base < 0x40010000; base += 0x100) अणु
		cpuid(base, &eax, &signature[0], &signature[1], &signature[2]);

		अगर (!स_भेद(sig, signature, 12) &&
		    (leaves == 0 || ((eax - base) >= leaves)))
			वापस base;
	पूर्ण

	वापस 0;
पूर्ण

बाह्य अचिन्हित दीर्घ arch_align_stack(अचिन्हित दीर्घ sp);
व्योम मुक्त_init_pages(स्थिर अक्षर *what, अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end);
बाह्य व्योम मुक्त_kernel_image_pages(स्थिर अक्षर *what, व्योम *begin, व्योम *end);

व्योम शेष_idle(व्योम);
#अगर_घोषित	CONFIG_XEN
bool xen_set_शेष_idle(व्योम);
#अन्यथा
#घोषणा xen_set_शेष_idle 0
#पूर्ण_अगर

व्योम stop_this_cpu(व्योम *dummy);
व्योम microcode_check(व्योम);

क्रमागत l1tf_mitigations अणु
	L1TF_MITIGATION_OFF,
	L1TF_MITIGATION_FLUSH_NOWARN,
	L1TF_MITIGATION_FLUSH,
	L1TF_MITIGATION_FLUSH_NOSMT,
	L1TF_MITIGATION_FULL,
	L1TF_MITIGATION_FULL_FORCE
पूर्ण;

बाह्य क्रमागत l1tf_mitigations l1tf_mitigation;

क्रमागत mds_mitigations अणु
	MDS_MITIGATION_OFF,
	MDS_MITIGATION_FULL,
	MDS_MITIGATION_VMWERV,
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_PROCESSOR_H */
