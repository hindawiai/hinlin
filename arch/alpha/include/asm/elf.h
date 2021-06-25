<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ALPHA_ELF_H
#घोषणा __ASM_ALPHA_ELF_H

#समावेश <यंत्र/auxvec.h>
#समावेश <यंत्र/special_insns.h>

/* Special values क्रम the st_other field in the symbol table.  */

#घोषणा STO_ALPHA_NOPV		0x80
#घोषणा STO_ALPHA_STD_GPLOAD	0x88

/*
 * Alpha ELF relocation types
 */
#घोषणा R_ALPHA_NONE            0       /* No reloc */
#घोषणा R_ALPHA_REFLONG         1       /* Direct 32 bit */
#घोषणा R_ALPHA_REFQUAD         2       /* Direct 64 bit */
#घोषणा R_ALPHA_GPREL32         3       /* GP relative 32 bit */
#घोषणा R_ALPHA_LITERAL         4       /* GP relative 16 bit w/optimization */
#घोषणा R_ALPHA_LITUSE          5       /* Optimization hपूर्णांक क्रम LITERAL */
#घोषणा R_ALPHA_GPDISP          6       /* Add displacement to GP */
#घोषणा R_ALPHA_BRADDR          7       /* PC+4 relative 23 bit shअगरted */
#घोषणा R_ALPHA_HINT            8       /* PC+4 relative 16 bit shअगरted */
#घोषणा R_ALPHA_SREL16          9       /* PC relative 16 bit */
#घोषणा R_ALPHA_SREL32          10      /* PC relative 32 bit */
#घोषणा R_ALPHA_SREL64          11      /* PC relative 64 bit */
#घोषणा R_ALPHA_GPRELHIGH       17      /* GP relative 32 bit, high 16 bits */
#घोषणा R_ALPHA_GPRELLOW        18      /* GP relative 32 bit, low 16 bits */
#घोषणा R_ALPHA_GPREL16         19      /* GP relative 16 bit */
#घोषणा R_ALPHA_COPY            24      /* Copy symbol at runसमय */
#घोषणा R_ALPHA_GLOB_DAT        25      /* Create GOT entry */
#घोषणा R_ALPHA_JMP_SLOT        26      /* Create PLT entry */
#घोषणा R_ALPHA_RELATIVE        27      /* Adjust by program base */
#घोषणा R_ALPHA_BRSGP		28
#घोषणा R_ALPHA_TLSGD           29
#घोषणा R_ALPHA_TLS_LDM         30
#घोषणा R_ALPHA_DTPMOD64        31
#घोषणा R_ALPHA_GOTDTPREL       32
#घोषणा R_ALPHA_DTPREL64        33
#घोषणा R_ALPHA_DTPRELHI        34
#घोषणा R_ALPHA_DTPRELLO        35
#घोषणा R_ALPHA_DTPREL16        36
#घोषणा R_ALPHA_GOTTPREL        37
#घोषणा R_ALPHA_TPREL64         38
#घोषणा R_ALPHA_TPRELHI         39
#घोषणा R_ALPHA_TPRELLO         40
#घोषणा R_ALPHA_TPREL16         41

#घोषणा SHF_ALPHA_GPREL		0x10000000

/* Legal values क्रम e_flags field of Elf64_Ehdr.  */

#घोषणा EF_ALPHA_32BIT		1	/* All addresses are below 2GB */

/*
 * ELF रेजिस्टर definitions..
 */

/*
 * The OSF/1 version of <sys/procfs.h> makes gregset_t 46 entries दीर्घ.
 * I have no idea why that is so.  For now, we just leave it at 33
 * (32 general regs + processor status word). 
 */
#घोषणा ELF_NGREG	33
#घोषणा ELF_NFPREG	32

प्रकार अचिन्हित दीर्घ elf_greg_t;
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार द्विगुन elf_fpreg_t;
प्रकार elf_fpreg_t elf_fpregset_t[ELF_NFPREG];

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == EM_ALPHA)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS64
#घोषणा ELF_DATA	ELFDATA2LSB
#घोषणा ELF_ARCH	EM_ALPHA

#घोषणा ELF_EXEC_PAGESIZE	8192

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE		(TASK_UNMAPPED_BASE + 0x1000000)

/* $0 is set by ld.so to a poपूर्णांकer to a function which might be 
   रेजिस्टरed using निकास_पर.  This provides a mean क्रम the dynamic
   linker to call DT_FINI functions क्रम shared libraries that have
   been loaded beक्रमe the code runs.

   So that we can use the same startup file with अटल executables,
   we start programs with a value of 0 to indicate that there is no
   such function.  */

#घोषणा ELF_PLAT_INIT(_r, load_addr)	_r->r0 = 0

/* The रेजिस्टरs are laid out in pt_regs क्रम PAL and syscall
   convenience.  Re-order them क्रम the linear elf_gregset_t.  */

काष्ठा pt_regs;
काष्ठा thपढ़ो_info;
काष्ठा task_काष्ठा;
बाह्य व्योम dump_elf_thपढ़ो(elf_greg_t *dest, काष्ठा pt_regs *pt,
			    काष्ठा thपढ़ो_info *ti);
#घोषणा ELF_CORE_COPY_REGS(DEST, REGS) \
	dump_elf_thपढ़ो(DEST, REGS, current_thपढ़ो_info());

/* Similar, but क्रम a thपढ़ो other than current.  */

बाह्य पूर्णांक dump_elf_task(elf_greg_t *dest, काष्ठा task_काष्ठा *task);
#घोषणा ELF_CORE_COPY_TASK_REGS(TASK, DEST) \
	dump_elf_task(*(DEST), TASK)

/* Similar, but क्रम the FP रेजिस्टरs.  */

बाह्य पूर्णांक dump_elf_task_fp(elf_fpreg_t *dest, काष्ठा task_काष्ठा *task);
#घोषणा ELF_CORE_COPY_FPREGS(TASK, DEST) \
	dump_elf_task_fp(*(DEST), TASK)

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this CPU supports.  This is trivial on Alpha, 
   but not so on other machines. */

#घोषणा ELF_HWCAP  (~amask(-1))

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.  */

#घोषणा ELF_PLATFORM				\
(अणु						\
	क्रमागत implver_क्रमागत i_ = implver();	\
	( i_ == IMPLVER_EV4 ? "ev4"		\
	: i_ == IMPLVER_EV5			\
	  ? (amask(AMASK_BWX) ? "ev5" : "ev56")	\
	: amask (AMASK_CIX) ? "ev6" : "ev67");	\
पूर्ण)

#घोषणा SET_PERSONALITY(EX)					\
	set_personality(((EX).e_flags & EF_ALPHA_32BIT)		\
	   ? PER_LINUX_32BIT : PER_LINUX)

बाह्य पूर्णांक alpha_l1i_cacheshape;
बाह्य पूर्णांक alpha_l1d_cacheshape;
बाह्य पूर्णांक alpha_l2_cacheshape;
बाह्य पूर्णांक alpha_l3_cacheshape;

/* update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes */
#घोषणा ARCH_DLINFO						\
  करो अणु								\
    NEW_AUX_ENT(AT_L1I_CACHESHAPE, alpha_l1i_cacheshape);	\
    NEW_AUX_ENT(AT_L1D_CACHESHAPE, alpha_l1d_cacheshape);	\
    NEW_AUX_ENT(AT_L2_CACHESHAPE, alpha_l2_cacheshape);		\
    NEW_AUX_ENT(AT_L3_CACHESHAPE, alpha_l3_cacheshape);		\
  पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_ALPHA_ELF_H */
