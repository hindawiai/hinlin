<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_ELF_H
#घोषणा __ASM_SH_ELF_H

#समावेश <linux/utsname.h>
#समावेश <यंत्र/auxvec.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/user.h>

/* ELF header e_flags defines */
#घोषणा EF_SH_PIC		0x100	/* -fpic */
#घोषणा EF_SH_FDPIC		0x8000	/* -mfdpic */

/* SH (particularly SHcompact) relocation types  */
#घोषणा	R_SH_NONE		0
#घोषणा	R_SH_सूची32		1
#घोषणा	R_SH_REL32		2
#घोषणा	R_SH_सूची8WPN		3
#घोषणा	R_SH_IND12W		4
#घोषणा	R_SH_सूची8WPL		5
#घोषणा	R_SH_सूची8WPZ		6
#घोषणा	R_SH_सूची8BP		7
#घोषणा	R_SH_सूची8W		8
#घोषणा	R_SH_सूची8L		9
#घोषणा	R_SH_SWITCH16		25
#घोषणा	R_SH_SWITCH32		26
#घोषणा	R_SH_USES		27
#घोषणा	R_SH_COUNT		28
#घोषणा	R_SH_ALIGN		29
#घोषणा	R_SH_CODE		30
#घोषणा	R_SH_DATA		31
#घोषणा	R_SH_LABEL		32
#घोषणा	R_SH_SWITCH8		33
#घोषणा	R_SH_GNU_VTINHERIT	34
#घोषणा	R_SH_GNU_VTENTRY	35
#घोषणा	R_SH_TLS_GD_32		144
#घोषणा	R_SH_TLS_LD_32		145
#घोषणा	R_SH_TLS_LDO_32		146
#घोषणा	R_SH_TLS_IE_32		147
#घोषणा	R_SH_TLS_LE_32		148
#घोषणा	R_SH_TLS_DTPMOD32	149
#घोषणा	R_SH_TLS_DTPOFF32	150
#घोषणा	R_SH_TLS_TPOFF32	151
#घोषणा	R_SH_GOT32		160
#घोषणा	R_SH_PLT32		161
#घोषणा	R_SH_COPY		162
#घोषणा	R_SH_GLOB_DAT		163
#घोषणा	R_SH_JMP_SLOT		164
#घोषणा	R_SH_RELATIVE		165
#घोषणा	R_SH_GOTOFF		166
#घोषणा	R_SH_GOTPC		167

/* FDPIC relocs */
#घोषणा R_SH_GOT20		201
#घोषणा R_SH_GOTOFF20		202
#घोषणा R_SH_GOTFUNCDESC	203
#घोषणा R_SH_GOTFUNCDESC20	204
#घोषणा R_SH_GOTOFFFUNCDESC	205
#घोषणा R_SH_GOTOFFFUNCDESC20	206
#घोषणा R_SH_FUNCDESC		207
#घोषणा R_SH_FUNCDESC_VALUE	208

/* SHmedia relocs */
#घोषणा R_SH_IMM_LOW16		246
#घोषणा R_SH_IMM_LOW16_PCREL	247
#घोषणा R_SH_IMM_MEDLOW16	248
#घोषणा R_SH_IMM_MEDLOW16_PCREL	249
/* Keep this the last entry.  */
#घोषणा	R_SH_NUM		256

/*
 * ELF रेजिस्टर definitions..
 */

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा ELF_NGREG (माप (काष्ठा pt_regs) / माप(elf_greg_t))
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा user_fpu_काष्ठा elf_fpregset_t;

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा ELF_DATA	ELFDATA2LSB
#अन्यथा
#घोषणा ELF_DATA	ELFDATA2MSB
#पूर्ण_अगर
#घोषणा ELF_ARCH	EM_SH

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x)		((x)->e_machine == EM_SH)
#घोषणा elf_check_fdpic(x)		((x)->e_flags & EF_SH_FDPIC)
#घोषणा elf_check_स्थिर_displacement(x)	((x)->e_flags & EF_SH_PIC)

/*
 * Enable dump using regset.
 * This covers all of general/DSP/FPU regs.
 */
#घोषणा CORE_DUMP_USE_REGSET

#घोषणा ELF_FDPIC_CORE_EFLAGS	EF_SH_FDPIC
#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE         (2 * TASK_SIZE / 3)

#घोषणा ELF_CORE_COPY_REGS(_dest,_regs)				\
	स_नकल((अक्षर *) &_dest, (अक्षर *) _regs,			\
	       माप(काष्ठा pt_regs));

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this CPU supports.  This could be करोne in user space,
   but it's not easy, and we've alपढ़ोy करोne it here.  */

#घोषणा ELF_HWCAP	(boot_cpu_data.flags)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.

   For the moment, we have only optimizations क्रम the Intel generations,
   but that could change... */

#घोषणा ELF_PLATFORM	(utsname()->machine)

#घोषणा ELF_PLAT_INIT(_r, load_addr) \
  करो अणु _r->regs[0]=0; _r->regs[1]=0; _r->regs[2]=0; _r->regs[3]=0; \
       _r->regs[4]=0; _r->regs[5]=0; _r->regs[6]=0; _r->regs[7]=0; \
       _r->regs[8]=0; _r->regs[9]=0; _r->regs[10]=0; _r->regs[11]=0; \
       _r->regs[12]=0; _r->regs[13]=0; _r->regs[14]=0; \
       _r->sr = SR_FD; पूर्ण जबतक (0)

#घोषणा ELF_FDPIC_PLAT_INIT(_r, _exec_map_addr, _पूर्णांकerp_map_addr,	\
			    _dynamic_addr)				\
करो अणु									\
	_r->regs[0]	= 0;						\
	_r->regs[1]	= 0;						\
	_r->regs[2]	= 0;						\
	_r->regs[3]	= 0;						\
	_r->regs[4]	= 0;						\
	_r->regs[5]	= 0;						\
	_r->regs[6]	= 0;						\
	_r->regs[7]	= 0;						\
	_r->regs[8]	= _exec_map_addr;				\
	_r->regs[9]	= _पूर्णांकerp_map_addr;				\
	_r->regs[10]	= _dynamic_addr;				\
	_r->regs[11]	= 0;						\
	_r->regs[12]	= 0;						\
	_r->regs[13]	= 0;						\
	_r->regs[14]	= 0;						\
	_r->sr		= SR_FD;					\
पूर्ण जबतक (0)

#घोषणा SET_PERSONALITY(ex) \
	set_personality(PER_LINUX_32BIT | (current->personality & (~PER_MASK)))

#अगर_घोषित CONFIG_VSYSCALL
/* vDSO has arch_setup_additional_pages */
#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp);

बाह्य अचिन्हित पूर्णांक vdso_enabled;
बाह्य व्योम __kernel_vsyscall;

#घोषणा VDSO_BASE		((अचिन्हित दीर्घ)current->mm->context.vdso)
#घोषणा VDSO_SYM(x)		(VDSO_BASE + (अचिन्हित दीर्घ)(x))

#घोषणा VSYSCALL_AUX_ENT					\
	अगर (vdso_enabled)					\
		NEW_AUX_ENT(AT_SYSINFO_EHDR, VDSO_BASE);	\
	अन्यथा							\
		NEW_AUX_ENT(AT_IGNORE, 0)
#अन्यथा
#घोषणा VSYSCALL_AUX_ENT	NEW_AUX_ENT(AT_IGNORE, 0)
#पूर्ण_अगर /* CONFIG_VSYSCALL */

#अगर_घोषित CONFIG_SH_FPU
#घोषणा FPU_AUX_ENT	NEW_AUX_ENT(AT_FPUCW, FPSCR_INIT)
#अन्यथा
#घोषणा FPU_AUX_ENT	NEW_AUX_ENT(AT_IGNORE, 0)
#पूर्ण_अगर

बाह्य पूर्णांक l1i_cache_shape, l1d_cache_shape, l2_cache_shape;

/* update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes */
#घोषणा ARCH_DLINFO						\
करो अणु								\
	/* Optional FPU initialization */			\
	FPU_AUX_ENT;						\
								\
	/* Optional vsyscall entry */				\
	VSYSCALL_AUX_ENT;					\
								\
	/* Cache desc */					\
	NEW_AUX_ENT(AT_L1I_CACHESHAPE, l1i_cache_shape);	\
	NEW_AUX_ENT(AT_L1D_CACHESHAPE, l1d_cache_shape);	\
	NEW_AUX_ENT(AT_L2_CACHESHAPE, l2_cache_shape);		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_SH_ELF_H */
