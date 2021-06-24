<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASMNDS32_ELF_H
#घोषणा __ASMNDS32_ELF_H

/*
 * ELF रेजिस्टर definitions..
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/fpu.h>
#समावेश <linux/elf-em.h>

प्रकार अचिन्हित दीर्घ elf_greg_t;
प्रकार अचिन्हित दीर्घ elf_freg_t[3];

बाह्य अचिन्हित पूर्णांक elf_hwcap;

#घोषणा R_NDS32_NONE			0
#घोषणा R_NDS32_16_RELA			19
#घोषणा R_NDS32_32_RELA			20
#घोषणा R_NDS32_9_PCREL_RELA		22
#घोषणा R_NDS32_15_PCREL_RELA		23
#घोषणा R_NDS32_17_PCREL_RELA		24
#घोषणा R_NDS32_25_PCREL_RELA		25
#घोषणा R_NDS32_HI20_RELA		26
#घोषणा R_NDS32_LO12S3_RELA		27
#घोषणा R_NDS32_LO12S2_RELA		28
#घोषणा R_NDS32_LO12S1_RELA		29
#घोषणा R_NDS32_LO12S0_RELA		30
#घोषणा R_NDS32_SDA15S3_RELA    	31
#घोषणा R_NDS32_SDA15S2_RELA    	32
#घोषणा R_NDS32_SDA15S1_RELA    	33
#घोषणा R_NDS32_SDA15S0_RELA    	34
#घोषणा R_NDS32_GOT20			37
#घोषणा R_NDS32_25_PLTREL		38
#घोषणा R_NDS32_COPY			39
#घोषणा R_NDS32_GLOB_DAT		40
#घोषणा R_NDS32_JMP_SLOT		41
#घोषणा R_NDS32_RELATIVE		42
#घोषणा R_NDS32_GOTOFF			43
#घोषणा R_NDS32_GOTPC20			44
#घोषणा R_NDS32_GOT_HI20		45
#घोषणा R_NDS32_GOT_LO12		46
#घोषणा R_NDS32_GOTPC_HI20		47
#घोषणा R_NDS32_GOTPC_LO12		48
#घोषणा R_NDS32_GOTOFF_HI20		49
#घोषणा R_NDS32_GOTOFF_LO12		50
#घोषणा R_NDS32_INSN16			51
#घोषणा R_NDS32_LABEL			52
#घोषणा R_NDS32_LONGCALL1		53
#घोषणा R_NDS32_LONGCALL2		54
#घोषणा R_NDS32_LONGCALL3		55
#घोषणा R_NDS32_LONGJUMP1		56
#घोषणा R_NDS32_LONGJUMP2		57
#घोषणा R_NDS32_LONGJUMP3		58
#घोषणा R_NDS32_LOADSTORE		59
#घोषणा R_NDS32_9_FIXED_RELA		60
#घोषणा R_NDS32_15_FIXED_RELA		61
#घोषणा R_NDS32_17_FIXED_RELA		62
#घोषणा R_NDS32_25_FIXED_RELA		63
#घोषणा R_NDS32_PLTREL_HI20		64
#घोषणा R_NDS32_PLTREL_LO12		65
#घोषणा R_NDS32_PLT_GOTREL_HI20		66
#घोषणा R_NDS32_PLT_GOTREL_LO12		67
#घोषणा R_NDS32_LO12S0_ORI_RELA		72
#घोषणा R_NDS32_DWARF2_OP1_RELA     	77
#घोषणा R_NDS32_DWARF2_OP2_RELA     	78
#घोषणा R_NDS32_DWARF2_LEB_RELA     	79
#घोषणा R_NDS32_WORD_9_PCREL_RELA	94
#घोषणा R_NDS32_LONGCALL4 		107
#घोषणा R_NDS32_RELA_NOP_MIX		192
#घोषणा R_NDS32_RELA_NOP_MAX		255

#घोषणा ELF_NGREG (माप (काष्ठा user_pt_regs) / माप(elf_greg_t))
#घोषणा ELF_CORE_COPY_REGS(dest, regs)	\
	*(काष्ठा user_pt_regs *)&(dest) = (regs)->user_regs;

प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

/* Core file क्रमmat: The core file is written in such a way that gdb
   can understand it and provide useful inक्रमmation to the user (under
   linux we use the 'trad-core' bfd).  There are quite a number of
   obstacles to being able to view the contents of the भग्नing poपूर्णांक
   रेजिस्टरs, and until these are solved you will not be able to view the
   contents of them.  Actually, you can पढ़ो in the core file and look at
   the contents of the user काष्ठा to find out what the भग्नing poपूर्णांक
   रेजिस्टरs contain.
   The actual file contents are as follows:
   UPAGE: 1 page consisting of a user काष्ठा that tells gdb what is present
   in the file.  Directly after this is a copy of the task_काष्ठा, which
   is currently not used by gdb, but it may come in useful at some poपूर्णांक.
   All of the रेजिस्टरs are stored as part of the upage.  The upage should
   always be only one page.
   DATA: The data area is stored.  We use current->end_text to
   current->brk to pick up all of the user variables, plus any memory
   that may have been दो_स्मृतिed.  No attempt is made to determine अगर a page
   is demand-zero or अगर a page is totally unused, we just cover the entire
   range.  All of the addresses are rounded in such a way that an पूर्णांकegral
   number of pages is written.
   STACK: We need the stack inक्रमmation in order to get a meaningful
   backtrace.  We need to ग_लिखो the data from (esp) to
   current->start_stack, so we round each of these off in order to be able
   to ग_लिखो an पूर्णांकeger number of pages.
   The minimum core file size is 3 pages, or 12288 bytes.
*/

काष्ठा user_fp अणु
        अचिन्हित दीर्घ दीर्घ fd_regs[32];
        अचिन्हित दीर्घ fpcsr;
पूर्ण;

प्रकार काष्ठा user_fp elf_fpregset_t;

काष्ठा elf32_hdr;
#घोषणा elf_check_arch(x)		((x)->e_machine == EM_NDS32)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#अगर_घोषित __NDS32_EB__
#घोषणा ELF_DATA	ELFDATA2MSB
#अन्यथा
#घोषणा ELF_DATA	ELFDATA2LSB
#पूर्ण_अगर
#घोषणा ELF_ARCH	EM_NDS32
#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE	(2 * TASK_SIZE / 3)

/* When the program starts, a1 contains a poपूर्णांकer to a function to be
   रेजिस्टरed with निकास_पर, as per the SVR4 ABI.  A value of 0 means we
   have no such handler.  */
#घोषणा ELF_PLAT_INIT(_r, load_addr)	(_r)->uregs[0] = 0

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports. */

#घोषणा ELF_HWCAP	(elf_hwcap)

#अगर_घोषित __KERNEL__

#घोषणा ELF_PLATFORM    (शून्य)

/* Old NetWinder binaries were compiled in such a way that the iBCS
   heuristic always trips on them.  Until these binaries become uncommon
   enough not to care, करोn't trust the `ibcs' flag here.  In any हाल
   there is no other ELF प्रणाली currently supported by iBCS.
   @@ Could prपूर्णांक a warning message to encourage users to upgrade.  */
#घोषणा SET_PERSONALITY(ex)	set_personality(PER_LINUX)

#पूर्ण_अगर


#अगर IS_ENABLED(CONFIG_FPU)
#घोषणा FPU_AUX_ENT	NEW_AUX_ENT(AT_FPUCW, FPCSR_INIT)
#अन्यथा
#घोषणा FPU_AUX_ENT	NEW_AUX_ENT(AT_IGNORE, 0)
#पूर्ण_अगर

#घोषणा ARCH_DLINFO						\
करो अणु								\
	/* Optional FPU initialization */			\
	FPU_AUX_ENT;						\
								\
	NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
		    (elf_addr_t)current->mm->context.vdso);	\
पूर्ण जबतक (0)
#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
काष्ठा linux_binprm;
पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *, पूर्णांक);

#पूर्ण_अगर
