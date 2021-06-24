<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_ELF_H
#घोषणा _ASM_X86_ELF_H

/*
 * ELF रेजिस्टर definitions..
 */
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/user.h>
#समावेश <यंत्र/auxvec.h>
#समावेश <यंत्र/fsgsbase.h>

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा ELF_NGREG (माप(काष्ठा user_regs_काष्ठा) / माप(elf_greg_t))
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा user_i387_काष्ठा elf_fpregset_t;

#अगर_घोषित __i386__

#घोषणा R_386_NONE	0
#घोषणा R_386_32	1
#घोषणा R_386_PC32	2
#घोषणा R_386_GOT32	3
#घोषणा R_386_PLT32	4
#घोषणा R_386_COPY	5
#घोषणा R_386_GLOB_DAT	6
#घोषणा R_386_JMP_SLOT	7
#घोषणा R_386_RELATIVE	8
#घोषणा R_386_GOTOFF	9
#घोषणा R_386_GOTPC	10
#घोषणा R_386_NUM	11

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA	ELFDATA2LSB
#घोषणा ELF_ARCH	EM_386

#अन्यथा

/* x86-64 relocation types */
#घोषणा R_X86_64_NONE		0	/* No reloc */
#घोषणा R_X86_64_64		1	/* Direct 64 bit  */
#घोषणा R_X86_64_PC32		2	/* PC relative 32 bit चिन्हित */
#घोषणा R_X86_64_GOT32		3	/* 32 bit GOT entry */
#घोषणा R_X86_64_PLT32		4	/* 32 bit PLT address */
#घोषणा R_X86_64_COPY		5	/* Copy symbol at runसमय */
#घोषणा R_X86_64_GLOB_DAT	6	/* Create GOT entry */
#घोषणा R_X86_64_JUMP_SLOT	7	/* Create PLT entry */
#घोषणा R_X86_64_RELATIVE	8	/* Adjust by program base */
#घोषणा R_X86_64_GOTPCREL	9	/* 32 bit चिन्हित pc relative
					   offset to GOT */
#घोषणा R_X86_64_32		10	/* Direct 32 bit zero extended */
#घोषणा R_X86_64_32S		11	/* Direct 32 bit sign extended */
#घोषणा R_X86_64_16		12	/* Direct 16 bit zero extended */
#घोषणा R_X86_64_PC16		13	/* 16 bit sign extended pc relative */
#घोषणा R_X86_64_8		14	/* Direct 8 bit sign extended  */
#घोषणा R_X86_64_PC8		15	/* 8 bit sign extended pc relative */
#घोषणा R_X86_64_PC64		24	/* Place relative 64-bit चिन्हित */

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS64
#घोषणा ELF_DATA	ELFDATA2LSB
#घोषणा ELF_ARCH	EM_X86_64

#पूर्ण_अगर

#समावेश <यंत्र/vdso.h>

#अगर_घोषित CONFIG_X86_64
बाह्य अचिन्हित पूर्णांक vdso64_enabled;
#पूर्ण_अगर
#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
बाह्य अचिन्हित पूर्णांक vdso32_enabled;
#पूर्ण_अगर

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch_ia32(x) \
	(((x)->e_machine == EM_386) || ((x)->e_machine == EM_486))

#समावेश <यंत्र/processor.h>

#अगर_घोषित CONFIG_X86_32
#समावेश <यंत्र/desc.h>

#घोषणा elf_check_arch(x)	elf_check_arch_ia32(x)

/* SVR4/i386 ABI (pages 3-31, 3-32) says that when the program starts %edx
   contains a poपूर्णांकer to a function which might be रेजिस्टरed using `निकास_पर'.
   This provides a mean क्रम the dynamic linker to call DT_FINI functions क्रम
   shared libraries that have been loaded beक्रमe the code runs.

   A value of 0 tells we have no such handler.

   We might as well make sure everything अन्यथा is cleared too (except क्रम %esp),
   just to make things more deterministic.
 */
#घोषणा ELF_PLAT_INIT(_r, load_addr)		\
	करो अणु					\
	_r->bx = 0; _r->cx = 0; _r->dx = 0;	\
	_r->si = 0; _r->di = 0; _r->bp = 0;	\
	_r->ax = 0;				\
पूर्ण जबतक (0)

/*
 * regs is काष्ठा pt_regs, pr_reg is elf_gregset_t (which is
 * now काष्ठा_user_regs, they are dअगरferent)
 */

#घोषणा ELF_CORE_COPY_REGS_COMMON(pr_reg, regs)	\
करो अणु						\
	pr_reg[0] = regs->bx;			\
	pr_reg[1] = regs->cx;			\
	pr_reg[2] = regs->dx;			\
	pr_reg[3] = regs->si;			\
	pr_reg[4] = regs->di;			\
	pr_reg[5] = regs->bp;			\
	pr_reg[6] = regs->ax;			\
	pr_reg[7] = regs->ds;			\
	pr_reg[8] = regs->es;			\
	pr_reg[9] = regs->fs;			\
	pr_reg[11] = regs->orig_ax;		\
	pr_reg[12] = regs->ip;			\
	pr_reg[13] = regs->cs;			\
	pr_reg[14] = regs->flags;		\
	pr_reg[15] = regs->sp;			\
	pr_reg[16] = regs->ss;			\
पूर्ण जबतक (0);

#घोषणा ELF_CORE_COPY_REGS(pr_reg, regs)	\
करो अणु						\
	ELF_CORE_COPY_REGS_COMMON(pr_reg, regs);\
	pr_reg[10] = get_user_gs(regs);		\
पूर्ण जबतक (0);

#घोषणा ELF_CORE_COPY_KERNEL_REGS(pr_reg, regs)	\
करो अणु						\
	ELF_CORE_COPY_REGS_COMMON(pr_reg, regs);\
	savesegment(gs, pr_reg[10]);		\
पूर्ण जबतक (0);

#घोषणा ELF_PLATFORM	(utsname()->machine)
#घोषणा set_personality_64bit()	करो अणु पूर्ण जबतक (0)

#अन्यथा /* CONFIG_X86_32 */

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x)			\
	((x)->e_machine == EM_X86_64)

#घोषणा compat_elf_check_arch(x)					\
	(elf_check_arch_ia32(x) ||					\
	 (IS_ENABLED(CONFIG_X86_X32_ABI) && (x)->e_machine == EM_X86_64))

#अगर __USER32_DS != __USER_DS
# error "The following code assumes __USER32_DS == __USER_DS"
#पूर्ण_अगर

अटल अंतरभूत व्योम elf_common_init(काष्ठा thपढ़ो_काष्ठा *t,
				   काष्ठा pt_regs *regs, स्थिर u16 ds)
अणु
	/* ax माला_लो execve's वापस value. */
	/*regs->ax = */ regs->bx = regs->cx = regs->dx = 0;
	regs->si = regs->di = regs->bp = 0;
	regs->r8 = regs->r9 = regs->r10 = regs->r11 = 0;
	regs->r12 = regs->r13 = regs->r14 = regs->r15 = 0;
	t->fsbase = t->gsbase = 0;
	t->fsindex = t->gsindex = 0;
	t->ds = t->es = ds;
पूर्ण

#घोषणा ELF_PLAT_INIT(_r, load_addr)			\
	elf_common_init(&current->thपढ़ो, _r, 0)

#घोषणा	COMPAT_ELF_PLAT_INIT(regs, load_addr)		\
	elf_common_init(&current->thपढ़ो, regs, __USER_DS)

व्योम compat_start_thपढ़ो(काष्ठा pt_regs *regs, u32 new_ip, u32 new_sp, bool x32);
#घोषणा COMPAT_START_THREAD(ex, regs, new_ip, new_sp)	\
	compat_start_thपढ़ो(regs, new_ip, new_sp, ex->e_machine == EM_X86_64)

व्योम set_personality_ia32(bool);
#घोषणा COMPAT_SET_PERSONALITY(ex)			\
	set_personality_ia32((ex).e_machine == EM_X86_64)

#घोषणा COMPAT_ELF_PLATFORM			("i686")

/*
 * regs is काष्ठा pt_regs, pr_reg is elf_gregset_t (which is
 * now काष्ठा_user_regs, they are dअगरferent). Assumes current is the process
 * getting dumped.
 */

#घोषणा ELF_CORE_COPY_REGS(pr_reg, regs)			\
करो अणु								\
	अचिन्हित v;						\
	(pr_reg)[0] = (regs)->r15;				\
	(pr_reg)[1] = (regs)->r14;				\
	(pr_reg)[2] = (regs)->r13;				\
	(pr_reg)[3] = (regs)->r12;				\
	(pr_reg)[4] = (regs)->bp;				\
	(pr_reg)[5] = (regs)->bx;				\
	(pr_reg)[6] = (regs)->r11;				\
	(pr_reg)[7] = (regs)->r10;				\
	(pr_reg)[8] = (regs)->r9;				\
	(pr_reg)[9] = (regs)->r8;				\
	(pr_reg)[10] = (regs)->ax;				\
	(pr_reg)[11] = (regs)->cx;				\
	(pr_reg)[12] = (regs)->dx;				\
	(pr_reg)[13] = (regs)->si;				\
	(pr_reg)[14] = (regs)->di;				\
	(pr_reg)[15] = (regs)->orig_ax;				\
	(pr_reg)[16] = (regs)->ip;				\
	(pr_reg)[17] = (regs)->cs;				\
	(pr_reg)[18] = (regs)->flags;				\
	(pr_reg)[19] = (regs)->sp;				\
	(pr_reg)[20] = (regs)->ss;				\
	(pr_reg)[21] = x86_fsbase_पढ़ो_cpu();			\
	(pr_reg)[22] = x86_gsbase_पढ़ो_cpu_inactive();		\
	यंत्र("movl %%ds,%0" : "=r" (v)); (pr_reg)[23] = v;	\
	यंत्र("movl %%es,%0" : "=r" (v)); (pr_reg)[24] = v;	\
	यंत्र("movl %%fs,%0" : "=r" (v)); (pr_reg)[25] = v;	\
	यंत्र("movl %%gs,%0" : "=r" (v)); (pr_reg)[26] = v;	\
पूर्ण जबतक (0);

/* I'm not sure if we can use '-' here */
#घोषणा ELF_PLATFORM       ("x86_64")
बाह्य व्योम set_personality_64bit(व्योम);
बाह्य अचिन्हित पूर्णांक sysctl_vsyscall32;
बाह्य पूर्णांक क्रमce_personality32;

#पूर्ण_अगर /* !CONFIG_X86_32 */

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	4096

/*
 * This is the base location क्रम PIE (ET_DYN with INTERP) loads. On
 * 64-bit, this is above 4GB to leave the entire 32-bit address
 * space खोलो क्रम things that want to use the area क्रम 32-bit poपूर्णांकers.
 */
#घोषणा ELF_ET_DYN_BASE		(mmap_is_ia32() ? 0x000400000UL : \
						  (DEFAULT_MAP_WINDOW / 3 * 2))

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this CPU supports.  This could be करोne in user space,
   but it's not easy, and we've alपढ़ोy करोne it here.  */

#घोषणा ELF_HWCAP		(boot_cpu_data.x86_capability[CPUID_1_EDX])

बाह्य u32 elf_hwcap2;

/*
 * HWCAP2 supplies mask with kernel enabled CPU features, so that
 * the application can discover that it can safely use them.
 * The bits are defined in uapi/यंत्र/hwcap2.h.
 */
#घोषणा ELF_HWCAP2		(elf_hwcap2)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.

   For the moment, we have only optimizations क्रम the Intel generations,
   but that could change... */

#घोषणा SET_PERSONALITY(ex) set_personality_64bit()

/*
 * An executable क्रम which elf_पढ़ो_implies_exec() वापसs TRUE will
 * have the READ_IMPLIES_EXEC personality flag set स्वतःmatically.
 *
 * The decision process क्रम determining the results are:
 *
 *                 CPU: | lacks NX*  | has NX, ia32     | has NX, x86_64 |
 * ELF:                 |            |                  |                |
 * ---------------------|------------|------------------|----------------|
 * missing PT_GNU_STACK | exec-all   | exec-all         | exec-none      |
 * PT_GNU_STACK == RWX  | exec-stack | exec-stack       | exec-stack     |
 * PT_GNU_STACK == RW   | exec-none  | exec-none        | exec-none      |
 *
 *  exec-all  : all PROT_READ user mappings are executable, except when
 *              backed by files on a noexec-fileप्रणाली.
 *  exec-none : only PROT_EXEC user mappings are executable.
 *  exec-stack: only the stack and PROT_EXEC user mappings are executable.
 *
 *  *this column has no architectural effect: NX markings are ignored by
 *   hardware, but may have behavioral effects when "wants X" collides with
 *   "cannot be X" स्थिरraपूर्णांकs in memory permission flags, as in
 *   https://lkml.kernel.org/r/20190418055759.GA3155@mellanox.com
 *
 */
#घोषणा elf_पढ़ो_implies_exec(ex, executable_stack)	\
	(mmap_is_ia32() && executable_stack == EXSTACK_DEFAULT)

काष्ठा task_काष्ठा;

#घोषणा	ARCH_DLINFO_IA32						\
करो अणु									\
	अगर (VDSO_CURRENT_BASE) अणु					\
		NEW_AUX_ENT(AT_SYSINFO,	VDSO_ENTRY);			\
		NEW_AUX_ENT(AT_SYSINFO_EHDR, VDSO_CURRENT_BASE);	\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * True on X86_32 or when emulating IA32 on X86_64
 */
अटल अंतरभूत पूर्णांक mmap_is_ia32(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_X86_32) ||
	       (IS_ENABLED(CONFIG_COMPAT) &&
		test_thपढ़ो_flag(TIF_ADDR32));
पूर्ण

बाह्य अचिन्हित दीर्घ task_size_32bit(व्योम);
बाह्य अचिन्हित दीर्घ task_size_64bit(पूर्णांक full_addr_space);
बाह्य अचिन्हित दीर्घ get_mmap_base(पूर्णांक is_legacy);
बाह्य bool mmap_address_hपूर्णांक_valid(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len);

#अगर_घोषित CONFIG_X86_32

#घोषणा __STACK_RND_MASK(is32bit) (0x7ff)
#घोषणा STACK_RND_MASK (0x7ff)

#घोषणा ARCH_DLINFO		ARCH_DLINFO_IA32

/* update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes */

#अन्यथा /* CONFIG_X86_32 */

/* 1GB क्रम 64bit, 8MB क्रम 32bit */
#घोषणा __STACK_RND_MASK(is32bit) ((is32bit) ? 0x7ff : 0x3fffff)
#घोषणा STACK_RND_MASK __STACK_RND_MASK(mmap_is_ia32())

#घोषणा ARCH_DLINFO							\
करो अणु									\
	अगर (vdso64_enabled)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
			    (अचिन्हित दीर्घ __क्रमce)current->mm->context.vdso); \
पूर्ण जबतक (0)

/* As a historical oddity, the x32 and x86_64 vDSOs are controlled together. */
#घोषणा ARCH_DLINFO_X32							\
करो अणु									\
	अगर (vdso64_enabled)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
			    (अचिन्हित दीर्घ __क्रमce)current->mm->context.vdso); \
पूर्ण जबतक (0)

#घोषणा AT_SYSINFO		32

#घोषणा COMPAT_ARCH_DLINFO						\
अगर (exec->e_machine == EM_X86_64)					\
	ARCH_DLINFO_X32;						\
अन्यथा अगर (IS_ENABLED(CONFIG_IA32_EMULATION))				\
	ARCH_DLINFO_IA32

#घोषणा COMPAT_ELF_ET_DYN_BASE	(TASK_UNMAPPED_BASE + 0x1000000)

#पूर्ण_अगर /* !CONFIG_X86_32 */

#घोषणा VDSO_CURRENT_BASE	((अचिन्हित दीर्घ)current->mm->context.vdso)

#घोषणा VDSO_ENTRY							\
	((अचिन्हित दीर्घ)current->mm->context.vdso +			\
	 vdso_image_32.sym___kernel_vsyscall)

काष्ठा linux_binprm;

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp);
बाह्य पूर्णांक compat_arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
					      पूर्णांक uses_पूर्णांकerp, bool x32);
#घोषणा COMPAT_ARCH_SETUP_ADDITIONAL_PAGES(bprm, ex, पूर्णांकerpreter)	\
	compat_arch_setup_additional_pages(bprm, पूर्णांकerpreter,		\
					   (ex->e_machine == EM_X86_64))

बाह्य bool arch_syscall_is_vdso_sigवापस(काष्ठा pt_regs *regs);

/* Do not change the values. See get_align_mask() */
क्रमागत align_flags अणु
	ALIGN_VA_32	= BIT(0),
	ALIGN_VA_64	= BIT(1),
पूर्ण;

काष्ठा va_alignment अणु
	पूर्णांक flags;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ bits;
पूर्ण ____cacheline_aligned;

बाह्य काष्ठा va_alignment va_align;
बाह्य अचिन्हित दीर्घ align_vdso_addr(अचिन्हित दीर्घ);
#पूर्ण_अगर /* _ASM_X86_ELF_H */
