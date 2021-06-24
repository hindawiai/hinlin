<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SEGMENT_H
#घोषणा _ASM_X86_SEGMENT_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/alternative.h>

/*
 * Conकाष्ठाor क्रम a conventional segment GDT (or LDT) entry.
 * This is a macro so it can be used in initializers.
 */
#घोषणा GDT_ENTRY(flags, base, limit)			\
	((((base)  & _AC(0xff000000,ULL)) << (56-24)) |	\
	 (((flags) & _AC(0x0000f0ff,ULL)) << 40) |	\
	 (((limit) & _AC(0x000f0000,ULL)) << (48-16)) |	\
	 (((base)  & _AC(0x00ffffff,ULL)) << 16) |	\
	 (((limit) & _AC(0x0000ffff,ULL))))

/* Simple and small GDT entries क्रम booting only: */

#घोषणा GDT_ENTRY_BOOT_CS	2
#घोषणा GDT_ENTRY_BOOT_DS	3
#घोषणा GDT_ENTRY_BOOT_TSS	4
#घोषणा __BOOT_CS		(GDT_ENTRY_BOOT_CS*8)
#घोषणा __BOOT_DS		(GDT_ENTRY_BOOT_DS*8)
#घोषणा __BOOT_TSS		(GDT_ENTRY_BOOT_TSS*8)

/*
 * Bottom two bits of selector give the ring
 * privilege level
 */
#घोषणा SEGMENT_RPL_MASK	0x3

/*
 * When running on Xen PV, the actual privilege level of the kernel is 1,
 * not 0. Testing the Requested Privilege Level in a segment selector to
 * determine whether the context is user mode or kernel mode with
 * SEGMENT_RPL_MASK is wrong because the PV kernel's privilege level
 * matches the 0x3 mask.
 *
 * Testing with USER_SEGMENT_RPL_MASK is valid क्रम both native and Xen PV
 * kernels because privilege level 2 is never used.
 */
#घोषणा USER_SEGMENT_RPL_MASK	0x2

/* User mode is privilege level 3: */
#घोषणा USER_RPL		0x3

/* Bit 2 is Table Indicator (TI): selects between LDT or GDT */
#घोषणा SEGMENT_TI_MASK		0x4
/* LDT segment has TI set ... */
#घोषणा SEGMENT_LDT		0x4
/* ... GDT has it cleared */
#घोषणा SEGMENT_GDT		0x0

#घोषणा GDT_ENTRY_INVALID_SEG	0

#अगर_घोषित CONFIG_X86_32
/*
 * The layout of the per-CPU GDT under Linux:
 *
 *   0 - null								<=== cacheline #1
 *   1 - reserved
 *   2 - reserved
 *   3 - reserved
 *
 *   4 - unused								<=== cacheline #2
 *   5 - unused
 *
 *  ------- start of TLS (Thपढ़ो-Local Storage) segments:
 *
 *   6 - TLS segment #1			[ glibc's TLS segment ]
 *   7 - TLS segment #2			[ Wine's %fs Win32 segment ]
 *   8 - TLS segment #3							<=== cacheline #3
 *   9 - reserved
 *  10 - reserved
 *  11 - reserved
 *
 *  ------- start of kernel segments:
 *
 *  12 - kernel code segment						<=== cacheline #4
 *  13 - kernel data segment
 *  14 - शेष user CS
 *  15 - शेष user DS
 *  16 - TSS								<=== cacheline #5
 *  17 - LDT
 *  18 - PNPBIOS support (16->32 gate)
 *  19 - PNPBIOS support
 *  20 - PNPBIOS support						<=== cacheline #6
 *  21 - PNPBIOS support
 *  22 - PNPBIOS support
 *  23 - APM BIOS support
 *  24 - APM BIOS support						<=== cacheline #7
 *  25 - APM BIOS support
 *
 *  26 - ESPFIX small SS
 *  27 - per-cpu			[ offset to per-cpu data area ]
 *  28 - unused
 *  29 - unused
 *  30 - unused
 *  31 - TSS क्रम द्विगुन fault handler
 */
#घोषणा GDT_ENTRY_TLS_MIN		6
#घोषणा GDT_ENTRY_TLS_MAX 		(GDT_ENTRY_TLS_MIN + GDT_ENTRY_TLS_ENTRIES - 1)

#घोषणा GDT_ENTRY_KERNEL_CS		12
#घोषणा GDT_ENTRY_KERNEL_DS		13
#घोषणा GDT_ENTRY_DEFAULT_USER_CS	14
#घोषणा GDT_ENTRY_DEFAULT_USER_DS	15
#घोषणा GDT_ENTRY_TSS			16
#घोषणा GDT_ENTRY_LDT			17
#घोषणा GDT_ENTRY_PNPBIOS_CS32		18
#घोषणा GDT_ENTRY_PNPBIOS_CS16		19
#घोषणा GDT_ENTRY_PNPBIOS_DS		20
#घोषणा GDT_ENTRY_PNPBIOS_TS1		21
#घोषणा GDT_ENTRY_PNPBIOS_TS2		22
#घोषणा GDT_ENTRY_APMBIOS_BASE		23

#घोषणा GDT_ENTRY_ESPFIX_SS		26
#घोषणा GDT_ENTRY_PERCPU		27

#घोषणा GDT_ENTRY_DOUBLEFAULT_TSS	31

/*
 * Number of entries in the GDT table:
 */
#घोषणा GDT_ENTRIES			32

/*
 * Segment selector values corresponding to the above entries:
 */

#घोषणा __KERNEL_CS			(GDT_ENTRY_KERNEL_CS*8)
#घोषणा __KERNEL_DS			(GDT_ENTRY_KERNEL_DS*8)
#घोषणा __USER_DS			(GDT_ENTRY_DEFAULT_USER_DS*8 + 3)
#घोषणा __USER_CS			(GDT_ENTRY_DEFAULT_USER_CS*8 + 3)
#घोषणा __ESPFIX_SS			(GDT_ENTRY_ESPFIX_SS*8)

/* segment क्रम calling fn: */
#घोषणा PNP_CS32			(GDT_ENTRY_PNPBIOS_CS32*8)
/* code segment क्रम BIOS: */
#घोषणा PNP_CS16			(GDT_ENTRY_PNPBIOS_CS16*8)

/* "Is this PNP code selector (PNP_CS32 or PNP_CS16)?" */
#घोषणा SEGMENT_IS_PNP_CODE(x)		(((x) & 0xf4) == PNP_CS32)

/* data segment क्रम BIOS: */
#घोषणा PNP_DS				(GDT_ENTRY_PNPBIOS_DS*8)
/* transfer data segment: */
#घोषणा PNP_TS1				(GDT_ENTRY_PNPBIOS_TS1*8)
/* another data segment: */
#घोषणा PNP_TS2				(GDT_ENTRY_PNPBIOS_TS2*8)

#अगर_घोषित CONFIG_SMP
# define __KERNEL_PERCPU		(GDT_ENTRY_PERCPU*8)
#अन्यथा
# define __KERNEL_PERCPU		0
#पूर्ण_अगर

#अन्यथा /* 64-bit: */

#समावेश <यंत्र/cache.h>

#घोषणा GDT_ENTRY_KERNEL32_CS		1
#घोषणा GDT_ENTRY_KERNEL_CS		2
#घोषणा GDT_ENTRY_KERNEL_DS		3

/*
 * We cannot use the same code segment descriptor क्रम user and kernel mode,
 * not even in दीर्घ flat mode, because of dअगरferent DPL.
 *
 * GDT layout to get 64-bit SYSCALL/SYSRET support right. SYSRET hardcodes
 * selectors:
 *
 *   अगर वापसing to 32-bit userspace: cs = STAR.SYSRET_CS,
 *   अगर वापसing to 64-bit userspace: cs = STAR.SYSRET_CS+16,
 *
 * ss = STAR.SYSRET_CS+8 (in either हाल)
 *
 * thus USER_DS should be between 32-bit and 64-bit code selectors:
 */
#घोषणा GDT_ENTRY_DEFAULT_USER32_CS	4
#घोषणा GDT_ENTRY_DEFAULT_USER_DS	5
#घोषणा GDT_ENTRY_DEFAULT_USER_CS	6

/* Needs two entries */
#घोषणा GDT_ENTRY_TSS			8
/* Needs two entries */
#घोषणा GDT_ENTRY_LDT			10

#घोषणा GDT_ENTRY_TLS_MIN		12
#घोषणा GDT_ENTRY_TLS_MAX		14

#घोषणा GDT_ENTRY_CPUNODE		15

/*
 * Number of entries in the GDT table:
 */
#घोषणा GDT_ENTRIES			16

/*
 * Segment selector values corresponding to the above entries:
 *
 * Note, selectors also need to have a correct RPL,
 * expressed with the +3 value क्रम user-space selectors:
 */
#घोषणा __KERNEL32_CS			(GDT_ENTRY_KERNEL32_CS*8)
#घोषणा __KERNEL_CS			(GDT_ENTRY_KERNEL_CS*8)
#घोषणा __KERNEL_DS			(GDT_ENTRY_KERNEL_DS*8)
#घोषणा __USER32_CS			(GDT_ENTRY_DEFAULT_USER32_CS*8 + 3)
#घोषणा __USER_DS			(GDT_ENTRY_DEFAULT_USER_DS*8 + 3)
#घोषणा __USER32_DS			__USER_DS
#घोषणा __USER_CS			(GDT_ENTRY_DEFAULT_USER_CS*8 + 3)
#घोषणा __CPUNODE_SEG			(GDT_ENTRY_CPUNODE*8 + 3)

#पूर्ण_अगर

#घोषणा IDT_ENTRIES			256
#घोषणा NUM_EXCEPTION_VECTORS		32

/* Biपंचांगask of exception vectors which push an error code on the stack: */
#घोषणा EXCEPTION_ERRCODE_MASK		0x20027d00

#घोषणा GDT_SIZE			(GDT_ENTRIES*8)
#घोषणा GDT_ENTRY_TLS_ENTRIES		3
#घोषणा TLS_SIZE			(GDT_ENTRY_TLS_ENTRIES* 8)

#अगर_घोषित CONFIG_X86_64

/* Bit size and mask of CPU number stored in the per CPU data (and TSC_AUX) */
#घोषणा VDSO_CPUNODE_BITS		12
#घोषणा VDSO_CPUNODE_MASK		0xfff

#अगर_अघोषित __ASSEMBLY__

/* Helper functions to store/load CPU and node numbers */

अटल अंतरभूत अचिन्हित दीर्घ vdso_encode_cpunode(पूर्णांक cpu, अचिन्हित दीर्घ node)
अणु
	वापस (node << VDSO_CPUNODE_BITS) | cpu;
पूर्ण

अटल अंतरभूत व्योम vdso_पढ़ो_cpunode(अचिन्हित *cpu, अचिन्हित *node)
अणु
	अचिन्हित पूर्णांक p;

	/*
	 * Load CPU and node number from the GDT.  LSL is faster than RDTSCP
	 * and works on all CPUs.  This is अस्थिर so that it orders
	 * correctly with respect to barrier() and to keep GCC from cleverly
	 * hoisting it out of the calling function.
	 *
	 * If RDPID is available, use it.
	 */
	alternative_io ("lsl %[seg],%[p]",
			".byte 0xf3,0x0f,0xc7,0xf8", /* RDPID %eax/rax */
			X86_FEATURE_RDPID,
			[p] "=a" (p), [seg] "r" (__CPUNODE_SEG));

	अगर (cpu)
		*cpu = (p & VDSO_CPUNODE_MASK);
	अगर (node)
		*node = (p >> VDSO_CPUNODE_BITS);
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_X86_64 */

#अगर_घोषित __KERNEL__

/*
 * early_idt_handler_array is an array of entry poपूर्णांकs referenced in the
 * early IDT.  For simplicity, it's a real array with one entry poपूर्णांक
 * every nine bytes.  That leaves room क्रम an optional 'push $0' अगर the
 * vector has no error code (two bytes), a 'push $vector_number' (two
 * bytes), and a jump to the common entry code (up to five bytes).
 */
#घोषणा EARLY_IDT_HANDLER_SIZE 9

/*
 * xen_early_idt_handler_array is क्रम Xen pv guests: क्रम each entry in
 * early_idt_handler_array it contains a prequel in the क्रमm of
 * pop %rcx; pop %r11; jmp early_idt_handler_array[i]; summing up to
 * max 8 bytes.
 */
#घोषणा XEN_EARLY_IDT_HANDLER_SIZE 8

#अगर_अघोषित __ASSEMBLY__

बाह्य स्थिर अक्षर early_idt_handler_array[NUM_EXCEPTION_VECTORS][EARLY_IDT_HANDLER_SIZE];
बाह्य व्योम early_ignore_irq(व्योम);

#अगर_घोषित CONFIG_XEN_PV
बाह्य स्थिर अक्षर xen_early_idt_handler_array[NUM_EXCEPTION_VECTORS][XEN_EARLY_IDT_HANDLER_SIZE];
#पूर्ण_अगर

/*
 * Load a segment. Fall back on loading the zero segment अगर something goes
 * wrong.  This variant assumes that loading zero fully clears the segment.
 * This is always the हाल on Intel CPUs and, even on 64-bit AMD CPUs, any
 * failure to fully clear the cached descriptor is only observable क्रम
 * FS and GS.
 */
#घोषणा __loadsegment_simple(seg, value)				\
करो अणु									\
	अचिन्हित लघु __val = (value);					\
									\
	यंत्र अस्थिर("						\n"	\
		     "1:	movl %k0,%%" #seg "		\n"	\
									\
		     ".section .fixup,\"ax\"			\n"	\
		     "2:	xorl %k0,%k0			\n"	\
		     "		jmp 1b				\n"	\
		     ".previous					\n"	\
									\
		     _ASM_EXTABLE(1b, 2b)				\
									\
		     : "+r" (__val) : : "memory");			\
पूर्ण जबतक (0)

#घोषणा __loadsegment_ss(value) __loadsegment_simple(ss, (value))
#घोषणा __loadsegment_ds(value) __loadsegment_simple(ds, (value))
#घोषणा __loadsegment_es(value) __loadsegment_simple(es, (value))

#अगर_घोषित CONFIG_X86_32

/*
 * On 32-bit प्रणालीs, the hidden parts of FS and GS are unobservable अगर
 * the selector is शून्य, so there's no funny business here.
 */
#घोषणा __loadsegment_fs(value) __loadsegment_simple(fs, (value))
#घोषणा __loadsegment_gs(value) __loadsegment_simple(gs, (value))

#अन्यथा

अटल अंतरभूत व्योम __loadsegment_fs(अचिन्हित लघु value)
अणु
	यंत्र अस्थिर("						\n"
		     "1:	movw %0, %%fs			\n"
		     "2:					\n"

		     _ASM_EXTABLE_HANDLE(1b, 2b, ex_handler_clear_fs)

		     : : "rm" (value) : "memory");
पूर्ण

/* __loadsegment_gs is पूर्णांकentionally undefined.  Use load_gs_index instead. */

#पूर्ण_अगर

#घोषणा loadsegment(seg, value) __loadsegment_ ## seg (value)

/*
 * Save a segment रेजिस्टर away:
 */
#घोषणा savesegment(seg, value)				\
	यंत्र("mov %%" #seg ",%0":"=r" (value) : : "memory")

/*
 * x86-32 user GS accessors.  This is ugly and could करो with some cleaning up.
 */
#अगर_घोषित CONFIG_X86_32
# define get_user_gs(regs)		(u16)(अणु अचिन्हित दीर्घ v; savesegment(gs, v); v; पूर्ण)
# define set_user_gs(regs, v)		loadsegment(gs, (अचिन्हित दीर्घ)(v))
# define task_user_gs(tsk)		((tsk)->thपढ़ो.gs)
# define lazy_save_gs(v)		savesegment(gs, (v))
# define lazy_load_gs(v)		loadsegment(gs, (v))
# define load_gs_index(v)		loadsegment(gs, (v))
#पूर्ण_अगर	/* X86_32 */

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_X86_SEGMENT_H */
