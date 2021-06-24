<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/personality.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/elf.h>
#समावेश <linux/elf-fdpic.h>
#समावेश <यंत्र/प्रणाली_info.h>

पूर्णांक elf_check_arch(स्थिर काष्ठा elf32_hdr *x)
अणु
	अचिन्हित पूर्णांक eflags;

	/* Make sure it's an ARM executable */
	अगर (x->e_machine != EM_ARM)
		वापस 0;

	/* Make sure the entry address is reasonable */
	अगर (x->e_entry & 1) अणु
		अगर (!(elf_hwcap & HWCAP_THUMB))
			वापस 0;
	पूर्ण अन्यथा अगर (x->e_entry & 3)
		वापस 0;

	eflags = x->e_flags;
	अगर ((eflags & EF_ARM_EABI_MASK) == EF_ARM_EABI_UNKNOWN) अणु
		अचिन्हित पूर्णांक flt_fmt;

		/* APCS26 is only allowed अगर the CPU supports it */
		अगर ((eflags & EF_ARM_APCS_26) && !(elf_hwcap & HWCAP_26BIT))
			वापस 0;

		flt_fmt = eflags & (EF_ARM_VFP_FLOAT | EF_ARM_SOFT_FLOAT);

		/* VFP requires the supporting code */
		अगर (flt_fmt == EF_ARM_VFP_FLOAT && !(elf_hwcap & HWCAP_VFP))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण
EXPORT_SYMBOL(elf_check_arch);

व्योम elf_set_personality(स्थिर काष्ठा elf32_hdr *x)
अणु
	अचिन्हित पूर्णांक eflags = x->e_flags;
	अचिन्हित पूर्णांक personality = current->personality & ~PER_MASK;

	/*
	 * We only support Linux ELF executables, so always set the
	 * personality to LINUX.
	 */
	personality |= PER_LINUX;

	/*
	 * APCS-26 is only valid क्रम OABI executables
	 */
	अगर ((eflags & EF_ARM_EABI_MASK) == EF_ARM_EABI_UNKNOWN &&
	    (eflags & EF_ARM_APCS_26))
		personality &= ~ADDR_LIMIT_32BIT;
	अन्यथा
		personality |= ADDR_LIMIT_32BIT;

	set_personality(personality);

	/*
	 * Since the FPA coprocessor uses CP1 and CP2, and iWMMXt uses CP0
	 * and CP1, we only enable access to the iWMMXt coprocessor अगर the
	 * binary is EABI or softभग्न (and thus, guaranteed not to use
	 * FPA inकाष्ठाions.)
	 */
	अगर (elf_hwcap & HWCAP_IWMMXT &&
	    eflags & (EF_ARM_EABI_MASK | EF_ARM_SOFT_FLOAT)) अणु
		set_thपढ़ो_flag(TIF_USING_IWMMXT);
	पूर्ण अन्यथा अणु
		clear_thपढ़ो_flag(TIF_USING_IWMMXT);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(elf_set_personality);

/*
 * An executable क्रम which elf_पढ़ो_implies_exec() वापसs TRUE will
 * have the READ_IMPLIES_EXEC personality flag set स्वतःmatically.
 *
 * The decision process क्रम determining the results are:
 *
 * त  त  त  त  त  त     त CPU: | lacks NX* त | has NX     |
 * ELF: त  त  त  त     त  त  त | त  त  त  त  त  त | त  त  त  त  त   |
 * ---------------------|------------|------------|
 * missing PT_GNU_STACK | exec-all त  | exec-all  त |
 * PT_GNU_STACK == RWX त | exec-all त  | exec-stackत |
 * PT_GNU_STACK == RW त  | exec-all  त | exec-none  |
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
पूर्णांक arm_elf_पढ़ो_implies_exec(पूर्णांक executable_stack)
अणु
	अगर (executable_stack == EXSTACK_DEFAULT)
		वापस 1;
	अगर (cpu_architecture() < CPU_ARCH_ARMv6)
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(arm_elf_पढ़ो_implies_exec);

#अगर defined(CONFIG_MMU) && defined(CONFIG_BINFMT_ELF_FDPIC)

व्योम elf_fdpic_arch_lay_out_mm(काष्ठा elf_fdpic_params *exec_params,
			       काष्ठा elf_fdpic_params *पूर्णांकerp_params,
			       अचिन्हित दीर्घ *start_stack,
			       अचिन्हित दीर्घ *start_brk)
अणु
	elf_set_personality(&exec_params->hdr);

	exec_params->load_addr = 0x8000;
	पूर्णांकerp_params->load_addr = ELF_ET_DYN_BASE;
	*start_stack = TASK_SIZE - SZ_16M;

	अगर ((exec_params->flags & ELF_FDPIC_FLAG_ARRANGEMENT) == ELF_FDPIC_FLAG_INDEPENDENT) अणु
		exec_params->flags &= ~ELF_FDPIC_FLAG_ARRANGEMENT;
		exec_params->flags |= ELF_FDPIC_FLAG_CONSTDISP;
	पूर्ण
पूर्ण

#पूर्ण_अगर
