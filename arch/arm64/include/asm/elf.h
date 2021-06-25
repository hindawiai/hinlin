<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_ELF_H
#घोषणा __ASM_ELF_H

#समावेश <यंत्र/hwcap.h>

/*
 * ELF रेजिस्टर definitions..
 */
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/user.h>

/*
 * AArch64 अटल relocation types.
 */

/* Miscellaneous. */
#घोषणा R_ARM_NONE			0
#घोषणा R_AARCH64_NONE			256

/* Data. */
#घोषणा R_AARCH64_ABS64			257
#घोषणा R_AARCH64_ABS32			258
#घोषणा R_AARCH64_ABS16			259
#घोषणा R_AARCH64_PREL64		260
#घोषणा R_AARCH64_PREL32		261
#घोषणा R_AARCH64_PREL16		262

/* Inकाष्ठाions. */
#घोषणा R_AARCH64_MOVW_UABS_G0		263
#घोषणा R_AARCH64_MOVW_UABS_G0_NC	264
#घोषणा R_AARCH64_MOVW_UABS_G1		265
#घोषणा R_AARCH64_MOVW_UABS_G1_NC	266
#घोषणा R_AARCH64_MOVW_UABS_G2		267
#घोषणा R_AARCH64_MOVW_UABS_G2_NC	268
#घोषणा R_AARCH64_MOVW_UABS_G3		269

#घोषणा R_AARCH64_MOVW_SABS_G0		270
#घोषणा R_AARCH64_MOVW_SABS_G1		271
#घोषणा R_AARCH64_MOVW_SABS_G2		272

#घोषणा R_AARCH64_LD_PREL_LO19		273
#घोषणा R_AARCH64_ADR_PREL_LO21		274
#घोषणा R_AARCH64_ADR_PREL_PG_HI21	275
#घोषणा R_AARCH64_ADR_PREL_PG_HI21_NC	276
#घोषणा R_AARCH64_ADD_ABS_LO12_NC	277
#घोषणा R_AARCH64_LDST8_ABS_LO12_NC	278

#घोषणा R_AARCH64_TSTBR14		279
#घोषणा R_AARCH64_CONDBR19		280
#घोषणा R_AARCH64_JUMP26		282
#घोषणा R_AARCH64_CALL26		283
#घोषणा R_AARCH64_LDST16_ABS_LO12_NC	284
#घोषणा R_AARCH64_LDST32_ABS_LO12_NC	285
#घोषणा R_AARCH64_LDST64_ABS_LO12_NC	286
#घोषणा R_AARCH64_LDST128_ABS_LO12_NC	299

#घोषणा R_AARCH64_MOVW_PREL_G0		287
#घोषणा R_AARCH64_MOVW_PREL_G0_NC	288
#घोषणा R_AARCH64_MOVW_PREL_G1		289
#घोषणा R_AARCH64_MOVW_PREL_G1_NC	290
#घोषणा R_AARCH64_MOVW_PREL_G2		291
#घोषणा R_AARCH64_MOVW_PREL_G2_NC	292
#घोषणा R_AARCH64_MOVW_PREL_G3		293

#घोषणा R_AARCH64_RELATIVE		1027

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS64
#अगर_घोषित __AARCH64EB__
#घोषणा ELF_DATA	ELFDATA2MSB
#अन्यथा
#घोषणा ELF_DATA	ELFDATA2LSB
#पूर्ण_अगर
#घोषणा ELF_ARCH	EM_AARCH64

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 */
#घोषणा ELF_PLATFORM_SIZE	16
#अगर_घोषित __AARCH64EB__
#घोषणा ELF_PLATFORM		("aarch64_be")
#अन्यथा
#घोषणा ELF_PLATFORM		("aarch64")
#पूर्ण_अगर

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x)		((x)->e_machine == EM_AARCH64)

/*
 * An executable क्रम which elf_पढ़ो_implies_exec() वापसs TRUE will
 * have the READ_IMPLIES_EXEC personality flag set स्वतःmatically.
 *
 * The decision process क्रम determining the results are:
 *
 * त  त  त  त  त  त    त CPU*: | arm32त  त    | arm64      |
 * ELF: त  त  त     त  त  त  त | त  त  त  त  त  त | त  त  त  त  त  त |
 * ---------------------|------------|------------|
 * missing PT_GNU_STACK | exec-all त  | exec-noneत  |
 * PT_GNU_STACK == RWX त | exec-stack | exec-stack |
 * PT_GNU_STACK == RW त  | exec-none  | exec-none  |
 *
 *  exec-all  : all PROT_READ user mappings are executable, except when
 *              backed by files on a noexec-fileप्रणाली.
 *  exec-none : only PROT_EXEC user mappings are executable.
 *  exec-stack: only the stack and PROT_EXEC user mappings are executable.
 *
 *  *all arm64 CPUs support NX, so there is no "lacks NX" column.
 *
 */
#घोषणा compat_elf_पढ़ो_implies_exec(ex, stk)	(stk == EXSTACK_DEFAULT)

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the base location क्रम PIE (ET_DYN with INTERP) loads. On
 * 64-bit, this is above 4GB to leave the entire 32-bit address
 * space खोलो क्रम things that want to use the area क्रम 32-bit poपूर्णांकers.
 */
#अगर_घोषित CONFIG_ARM64_FORCE_52BIT
#घोषणा ELF_ET_DYN_BASE		(2 * TASK_SIZE_64 / 3)
#अन्यथा
#घोषणा ELF_ET_DYN_BASE		(2 * DEFAULT_MAP_WINDOW_64 / 3)
#पूर्ण_अगर /* CONFIG_ARM64_FORCE_52BIT */

#अगर_अघोषित __ASSEMBLY__

#समावेश <uapi/linux/elf.h>
#समावेश <linux/bug.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/processor.h> /* क्रम संकेत_minsigstksz, used by ARCH_DLINFO */

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा ELF_NGREG (माप(काष्ठा user_pt_regs) / माप(elf_greg_t))
#घोषणा ELF_CORE_COPY_REGS(dest, regs)	\
	*(काष्ठा user_pt_regs *)&(dest) = (regs)->user_regs;

प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];
प्रकार काष्ठा user_fpsimd_state elf_fpregset_t;

/*
 * When the program starts, a1 contains a poपूर्णांकer to a function to be
 * रेजिस्टरed with निकास_पर, as per the SVR4 ABI.  A value of 0 means we have no
 * such handler.
 */
#घोषणा ELF_PLAT_INIT(_r, load_addr)	(_r)->regs[0] = 0

#घोषणा SET_PERSONALITY(ex)						\
(अणु									\
	clear_thपढ़ो_flag(TIF_32BIT);					\
	current->personality &= ~READ_IMPLIES_EXEC;			\
पूर्ण)

/* update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes */
#घोषणा ARCH_DLINFO							\
करो अणु									\
	NEW_AUX_ENT(AT_SYSINFO_EHDR,					\
		    (elf_addr_t)current->mm->context.vdso);		\
									\
	/*								\
	 * Should always be nonzero unless there's a kernel bug.	\
	 * If we haven't determined a sensible value to give to		\
	 * userspace, omit the entry:					\
	 */								\
	अगर (likely(संकेत_minsigstksz))					\
		NEW_AUX_ENT(AT_MINSIGSTKSZ, संकेत_minsigstksz);	\
	अन्यथा								\
		NEW_AUX_ENT(AT_IGNORE, 0);				\
पूर्ण जबतक (0)

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp);

/* 1GB of VA */
#अगर_घोषित CONFIG_COMPAT
#घोषणा STACK_RND_MASK			(test_thपढ़ो_flag(TIF_32BIT) ? \
						0x7ff >> (PAGE_SHIFT - 12) : \
						0x3ffff >> (PAGE_SHIFT - 12))
#अन्यथा
#घोषणा STACK_RND_MASK			(0x3ffff >> (PAGE_SHIFT - 12))
#पूर्ण_अगर

#अगर_घोषित __AARCH64EB__
#घोषणा COMPAT_ELF_PLATFORM		("v8b")
#अन्यथा
#घोषणा COMPAT_ELF_PLATFORM		("v8l")
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT

/* PIE load location क्रम compat arm. Must match ARM ELF_ET_DYN_BASE. */
#घोषणा COMPAT_ELF_ET_DYN_BASE		0x000400000UL

/* AArch32 रेजिस्टरs. */
#घोषणा COMPAT_ELF_NGREG		18
प्रकार अचिन्हित पूर्णांक			compat_elf_greg_t;
प्रकार compat_elf_greg_t		compat_elf_gregset_t[COMPAT_ELF_NGREG];

/* AArch32 EABI. */
#घोषणा EF_ARM_EABI_MASK		0xff000000
#घोषणा compat_elf_check_arch(x)	(प्रणाली_supports_32bit_el0() && \
					 ((x)->e_machine == EM_ARM) && \
					 ((x)->e_flags & EF_ARM_EABI_MASK))

#घोषणा compat_start_thपढ़ो		compat_start_thपढ़ो
/*
 * Unlike the native SET_PERSONALITY macro, the compat version मुख्यtains
 * READ_IMPLIES_EXEC across an execve() since this is the behaviour on
 * arch/arm/.
 */
#घोषणा COMPAT_SET_PERSONALITY(ex)					\
(अणु									\
	set_thपढ़ो_flag(TIF_32BIT);					\
 पूर्ण)
#अगर_घोषित CONFIG_COMPAT_VDSO
#घोषणा COMPAT_ARCH_DLINFO						\
करो अणु									\
	/*								\
	 * Note that we use Elf64_Off instead of elf_addr_t because	\
	 * elf_addr_t in compat is defined as Elf32_Addr and casting	\
	 * current->mm->context.vdso to it triggers a cast warning of	\
	 * cast from poपूर्णांकer to पूर्णांकeger of dअगरferent size.		\
	 */								\
	NEW_AUX_ENT(AT_SYSINFO_EHDR,					\
			(Elf64_Off)current->mm->context.vdso);		\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा COMPAT_ARCH_DLINFO
#पूर्ण_अगर
बाह्य पूर्णांक aarch32_setup_additional_pages(काष्ठा linux_binprm *bprm,
					  पूर्णांक uses_पूर्णांकerp);
#घोषणा compat_arch_setup_additional_pages \
					aarch32_setup_additional_pages

#पूर्ण_अगर /* CONFIG_COMPAT */

काष्ठा arch_elf_state अणु
	पूर्णांक flags;
पूर्ण;

#घोषणा ARM64_ELF_BTI		(1 << 0)

#घोषणा INIT_ARCH_ELF_STATE अणु			\
	.flags = 0,				\
पूर्ण

अटल अंतरभूत पूर्णांक arch_parse_elf_property(u32 type, स्थिर व्योम *data,
					  माप_प्रकार datasz, bool compat,
					  काष्ठा arch_elf_state *arch)
अणु
	/* No known properties क्रम AArch32 yet */
	अगर (IS_ENABLED(CONFIG_COMPAT) && compat)
		वापस 0;

	अगर (type == GNU_PROPERTY_AARCH64_FEATURE_1_AND) अणु
		स्थिर u32 *p = data;

		अगर (datasz != माप(*p))
			वापस -ENOEXEC;

		अगर (प्रणाली_supports_bti() &&
		    (*p & GNU_PROPERTY_AARCH64_FEATURE_1_BTI))
			arch->flags |= ARM64_ELF_BTI;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_elf_pt_proc(व्योम *ehdr, व्योम *phdr,
				   काष्ठा file *f, bool is_पूर्णांकerp,
				   काष्ठा arch_elf_state *state)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_check_elf(व्योम *ehdr, bool has_पूर्णांकerp,
				 व्योम *पूर्णांकerp_ehdr,
				 काष्ठा arch_elf_state *state)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर
