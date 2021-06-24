<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMARM_ELF_H
#घोषणा __ASMARM_ELF_H

#समावेश <यंत्र/auxvec.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/vdso_datapage.h>

/*
 * ELF रेजिस्टर definitions..
 */
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/user.h>

काष्ठा task_काष्ठा;

प्रकार अचिन्हित दीर्घ elf_greg_t;
प्रकार अचिन्हित दीर्घ elf_freg_t[3];

#घोषणा ELF_NGREG (माप (काष्ठा pt_regs) / माप(elf_greg_t))
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा user_fp elf_fpregset_t;

#घोषणा EF_ARM_EABI_MASK	0xff000000
#घोषणा EF_ARM_EABI_UNKNOWN	0x00000000
#घोषणा EF_ARM_EABI_VER1	0x01000000
#घोषणा EF_ARM_EABI_VER2	0x02000000
#घोषणा EF_ARM_EABI_VER3	0x03000000
#घोषणा EF_ARM_EABI_VER4	0x04000000
#घोषणा EF_ARM_EABI_VER5	0x05000000

#घोषणा EF_ARM_BE8		0x00800000	/* ABI 4,5 */
#घोषणा EF_ARM_LE8		0x00400000	/* ABI 4,5 */
#घोषणा EF_ARM_MAVERICK_FLOAT	0x00000800	/* ABI 0 */
#घोषणा EF_ARM_VFP_FLOAT	0x00000400	/* ABI 0 */
#घोषणा EF_ARM_SOFT_FLOAT	0x00000200	/* ABI 0 */
#घोषणा EF_ARM_OLD_ABI		0x00000100	/* ABI 0 */
#घोषणा EF_ARM_NEW_ABI		0x00000080	/* ABI 0 */
#घोषणा EF_ARM_ALIGN8		0x00000040	/* ABI 0 */
#घोषणा EF_ARM_PIC		0x00000020	/* ABI 0 */
#घोषणा EF_ARM_MAPSYMSFIRST	0x00000010	/* ABI 2 */
#घोषणा EF_ARM_APCS_FLOAT	0x00000010	/* ABI 0, भग्नs in fp regs */
#घोषणा EF_ARM_DYNSYMSUSESEGIDX	0x00000008	/* ABI 2 */
#घोषणा EF_ARM_APCS_26		0x00000008	/* ABI 0 */
#घोषणा EF_ARM_SYMSARESORTED	0x00000004	/* ABI 1,2 */
#घोषणा EF_ARM_INTERWORK	0x00000004	/* ABI 0 */
#घोषणा EF_ARM_HASENTRY		0x00000002	/* All */
#घोषणा EF_ARM_RELEXEC		0x00000001	/* All */

#घोषणा R_ARM_NONE		0
#घोषणा R_ARM_PC24		1
#घोषणा R_ARM_ABS32		2
#घोषणा R_ARM_REL32		3
#घोषणा R_ARM_CALL		28
#घोषणा R_ARM_JUMP24		29
#घोषणा R_ARM_TARGET1		38
#घोषणा R_ARM_V4BX		40
#घोषणा R_ARM_PREL31		42
#घोषणा R_ARM_MOVW_ABS_NC	43
#घोषणा R_ARM_MOVT_ABS		44
#घोषणा R_ARM_MOVW_PREL_NC	45
#घोषणा R_ARM_MOVT_PREL		46

#घोषणा R_ARM_THM_CALL		10
#घोषणा R_ARM_THM_JUMP24	30
#घोषणा R_ARM_THM_MOVW_ABS_NC	47
#घोषणा R_ARM_THM_MOVT_ABS	48
#घोषणा R_ARM_THM_MOVW_PREL_NC	49
#घोषणा R_ARM_THM_MOVT_PREL	50

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#अगर_घोषित __ARMEB__
#घोषणा ELF_DATA	ELFDATA2MSB
#अन्यथा
#घोषणा ELF_DATA	ELFDATA2LSB
#पूर्ण_अगर
#घोषणा ELF_ARCH	EM_ARM

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 *
 * For now we just provide a fairly general string that describes the
 * processor family.  This could be made more specअगरic later अगर someone
 * implemented optimisations that require it.  26-bit CPUs give you
 * "v1l" क्रम ARM2 (no SWP) and "v2l" क्रम anything अन्यथा (ARM1 isn't
 * supported).  32-bit CPUs give you "v3[lb]" क्रम anything based on an
 * ARM6 or ARM7 core and "armv4[lb]" क्रम anything based on a StrongARM-1
 * core.
 */
#घोषणा ELF_PLATFORM_SIZE 8
#घोषणा ELF_PLATFORM	(elf_platक्रमm)

बाह्य अक्षर elf_platक्रमm[];

काष्ठा elf32_hdr;

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
बाह्य पूर्णांक elf_check_arch(स्थिर काष्ठा elf32_hdr *);
#घोषणा elf_check_arch elf_check_arch

#घोषणा ELFOSABI_ARM_FDPIC  65	/* ARM FDPIC platक्रमm */
#घोषणा elf_check_fdpic(x)  ((x)->e_ident[EI_OSABI] == ELFOSABI_ARM_FDPIC)
#घोषणा elf_check_स्थिर_displacement(x)  ((x)->e_flags & EF_ARM_PIC)
#घोषणा ELF_FDPIC_CORE_EFLAGS  0

#घोषणा vmcore_elf64_check_arch(x) (0)

बाह्य पूर्णांक arm_elf_पढ़ो_implies_exec(पूर्णांक);
#घोषणा elf_पढ़ो_implies_exec(ex,stk) arm_elf_पढ़ो_implies_exec(stk)

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	4096

/* This is the base location क्रम PIE (ET_DYN with INTERP) loads. */
#घोषणा ELF_ET_DYN_BASE		0x400000UL

/* When the program starts, a1 contains a poपूर्णांकer to a function to be 
   रेजिस्टरed with निकास_पर, as per the SVR4 ABI.  A value of 0 means we 
   have no such handler.  */
#घोषणा ELF_PLAT_INIT(_r, load_addr)	(_r)->ARM_r0 = 0

#घोषणा ELF_FDPIC_PLAT_INIT(_r, _exec_map_addr, _पूर्णांकerp_map_addr, dynamic_addr) \
	करो अणु \
		(_r)->ARM_r7 = _exec_map_addr; \
		(_r)->ARM_r8 = _पूर्णांकerp_map_addr; \
		(_r)->ARM_r9 = dynamic_addr; \
	पूर्ण जबतक(0)

बाह्य व्योम elf_set_personality(स्थिर काष्ठा elf32_hdr *);
#घोषणा SET_PERSONALITY(ex)	elf_set_personality(&(ex))

#अगर_घोषित CONFIG_MMU
#अगर_घोषित CONFIG_VDSO
#घोषणा ARCH_DLINFO						\
करो अणु								\
	NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
		    (elf_addr_t)current->mm->context.vdso);	\
पूर्ण जबतक (0)
#पूर्ण_अगर
#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
काष्ठा linux_binprm;
पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *, पूर्णांक);
#पूर्ण_अगर

#पूर्ण_अगर
