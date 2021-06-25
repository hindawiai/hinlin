<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_ELF_H
#घोषणा __ASM_CSKY_ELF_H

#समावेश <यंत्र/ptrace.h>
#समावेश <abi/regdef.h>

#घोषणा ELF_ARCH EM_CSKY
#घोषणा EM_CSKY_OLD 39

/* CSKY Relocations */
#घोषणा R_CSKY_NONE               0
#घोषणा R_CSKY_32                 1
#घोषणा R_CSKY_PCIMM8BY4          2
#घोषणा R_CSKY_PCIMM11BY2         3
#घोषणा R_CSKY_PCIMM4BY2          4
#घोषणा R_CSKY_PC32               5
#घोषणा R_CSKY_PCRELJSR_IMM11BY2  6
#घोषणा R_CSKY_GNU_VTINHERIT      7
#घोषणा R_CSKY_GNU_VTENTRY        8
#घोषणा R_CSKY_RELATIVE           9
#घोषणा R_CSKY_COPY               10
#घोषणा R_CSKY_GLOB_DAT           11
#घोषणा R_CSKY_JUMP_SLOT          12
#घोषणा R_CSKY_ADDR_HI16          24
#घोषणा R_CSKY_ADDR_LO16          25
#घोषणा R_CSKY_PCRELJSR_IMM26BY2  40

प्रकार अचिन्हित दीर्घ elf_greg_t;

प्रकार काष्ठा user_fp elf_fpregset_t;

/*
 * In gdb/bfd elf32-csky.c, csky_elf_grok_prstatus() use fixed size of
 * elf_prstatus. It's 148 क्रम abiv1 and 220 क्रम abiv2, the size is enough
 * क्रम coredump and no need full माप(काष्ठा pt_regs).
 */
#घोषणा ELF_NGREG ((माप(काष्ठा pt_regs) / माप(elf_greg_t)) - 2)

प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) (((x)->e_machine == ELF_ARCH) || \
			   ((x)->e_machine == EM_CSKY_OLD))

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_EXEC_PAGESIZE		4096
#घोषणा ELF_CLASS			ELFCLASS32
#घोषणा ELF_PLAT_INIT(_r, load_addr)	अणु _r->a0 = 0; पूर्ण

#अगर_घोषित __cskyBE__
#घोषणा ELF_DATA	ELFDATA2MSB
#अन्यथा
#घोषणा ELF_DATA	ELFDATA2LSB
#पूर्ण_अगर

/*
 * This is the location that an ET_DYN program is loaded अगर exec'ed. Typical
 * use of this is to invoke "./ld.so someprog" to test out a new version of
 * the loader.  We need to make sure that it is out of the way of the program
 * that it will "exec", and that there is sufficient room क्रम the brk.
 */
#घोषणा ELF_ET_DYN_BASE	0x0UL
#समावेश <abi/elf.h>

/* Similar, but क्रम a thपढ़ो other than current. */
काष्ठा task_काष्ठा;
बाह्य पूर्णांक dump_task_regs(काष्ठा task_काष्ठा *tsk, elf_gregset_t *elf_regs);
#घोषणा ELF_CORE_COPY_TASK_REGS(tsk, elf_regs) dump_task_regs(tsk, elf_regs)

#घोषणा ELF_HWCAP	(0)

/*
 * This yields a string that ld.so will use to load implementation specअगरic
 * libraries क्रम optimization. This is more specअगरic in पूर्णांकent than poking
 * at uname or /proc/cpuinfo.
 */
#घोषणा ELF_PLATFORM		(शून्य)
#घोषणा SET_PERSONALITY(ex)	set_personality(PER_LINUX)

#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp);
#पूर्ण_अगर /* __ASM_CSKY_ELF_H */
