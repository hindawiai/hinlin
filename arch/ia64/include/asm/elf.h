<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_ELF_H
#घोषणा _ASM_IA64_ELF_H

/*
 * ELF-specअगरic definitions.
 *
 * Copyright (C) 1998-1999, 2002-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */


#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/auxvec.h>

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == EM_IA_64)

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS64
#घोषणा ELF_DATA	ELFDATA2LSB
#घोषणा ELF_ARCH	EM_IA_64

#घोषणा CORE_DUMP_USE_REGSET

/* Least-signअगरicant four bits of ELF header's e_flags are OS-specअगरic.  The bits are
   पूर्णांकerpreted as follows by Linux: */
#घोषणा EF_IA_64_LINUX_EXECUTABLE_STACK	0x1	/* is stack (& heap) executable by शेष? */

#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the location that an ET_DYN program is loaded अगर exec'ed.
 * Typical use of this is to invoke "./ld.so someprog" to test out a
 * new version of the loader.  We need to make sure that it is out of
 * the way of the program that it will "exec", and that there is
 * sufficient room क्रम the brk.
 */
#घोषणा ELF_ET_DYN_BASE		(TASK_UNMAPPED_BASE + 0x800000000UL)

#घोषणा PT_IA_64_UNWIND		0x70000001

/* IA-64 relocations: */
#घोषणा R_IA64_NONE		0x00	/* none */
#घोषणा R_IA64_IMM14		0x21	/* symbol + addend, add imm14 */
#घोषणा R_IA64_IMM22		0x22	/* symbol + addend, add imm22 */
#घोषणा R_IA64_IMM64		0x23	/* symbol + addend, mov imm64 */
#घोषणा R_IA64_सूची32MSB		0x24	/* symbol + addend, data4 MSB */
#घोषणा R_IA64_सूची32LSB		0x25	/* symbol + addend, data4 LSB */
#घोषणा R_IA64_सूची64MSB		0x26	/* symbol + addend, data8 MSB */
#घोषणा R_IA64_सूची64LSB		0x27	/* symbol + addend, data8 LSB */
#घोषणा R_IA64_GPREL22		0x2a	/* @gprel(sym+add), add imm22 */
#घोषणा R_IA64_GPREL64I		0x2b	/* @gprel(sym+add), mov imm64 */
#घोषणा R_IA64_GPREL32MSB	0x2c	/* @gprel(sym+add), data4 MSB */
#घोषणा R_IA64_GPREL32LSB	0x2d	/* @gprel(sym+add), data4 LSB */
#घोषणा R_IA64_GPREL64MSB	0x2e	/* @gprel(sym+add), data8 MSB */
#घोषणा R_IA64_GPREL64LSB	0x2f	/* @gprel(sym+add), data8 LSB */
#घोषणा R_IA64_LTOFF22		0x32	/* @ltoff(sym+add), add imm22 */
#घोषणा R_IA64_LTOFF64I		0x33	/* @ltoff(sym+add), mov imm64 */
#घोषणा R_IA64_PLTOFF22		0x3a	/* @pltoff(sym+add), add imm22 */
#घोषणा R_IA64_PLTOFF64I	0x3b	/* @pltoff(sym+add), mov imm64 */
#घोषणा R_IA64_PLTOFF64MSB	0x3e	/* @pltoff(sym+add), data8 MSB */
#घोषणा R_IA64_PLTOFF64LSB	0x3f	/* @pltoff(sym+add), data8 LSB */
#घोषणा R_IA64_FPTR64I		0x43	/* @fptr(sym+add), mov imm64 */
#घोषणा R_IA64_FPTR32MSB	0x44	/* @fptr(sym+add), data4 MSB */
#घोषणा R_IA64_FPTR32LSB	0x45	/* @fptr(sym+add), data4 LSB */
#घोषणा R_IA64_FPTR64MSB	0x46	/* @fptr(sym+add), data8 MSB */
#घोषणा R_IA64_FPTR64LSB	0x47	/* @fptr(sym+add), data8 LSB */
#घोषणा R_IA64_PCREL60B		0x48	/* @pcrel(sym+add), brl */
#घोषणा R_IA64_PCREL21B		0x49	/* @pcrel(sym+add), ptb, call */
#घोषणा R_IA64_PCREL21M		0x4a	/* @pcrel(sym+add), chk.s */
#घोषणा R_IA64_PCREL21F		0x4b	/* @pcrel(sym+add), fchkf */
#घोषणा R_IA64_PCREL32MSB	0x4c	/* @pcrel(sym+add), data4 MSB */
#घोषणा R_IA64_PCREL32LSB	0x4d	/* @pcrel(sym+add), data4 LSB */
#घोषणा R_IA64_PCREL64MSB	0x4e	/* @pcrel(sym+add), data8 MSB */
#घोषणा R_IA64_PCREL64LSB	0x4f	/* @pcrel(sym+add), data8 LSB */
#घोषणा R_IA64_LTOFF_FPTR22	0x52	/* @ltoff(@fptr(s+a)), imm22 */
#घोषणा R_IA64_LTOFF_FPTR64I	0x53	/* @ltoff(@fptr(s+a)), imm64 */
#घोषणा R_IA64_LTOFF_FPTR32MSB	0x54	/* @ltoff(@fptr(s+a)), 4 MSB */
#घोषणा R_IA64_LTOFF_FPTR32LSB	0x55	/* @ltoff(@fptr(s+a)), 4 LSB */
#घोषणा R_IA64_LTOFF_FPTR64MSB	0x56	/* @ltoff(@fptr(s+a)), 8 MSB */
#घोषणा R_IA64_LTOFF_FPTR64LSB	0x57	/* @ltoff(@fptr(s+a)), 8 LSB */
#घोषणा R_IA64_SEGREL32MSB	0x5c	/* @segrel(sym+add), data4 MSB */
#घोषणा R_IA64_SEGREL32LSB	0x5d	/* @segrel(sym+add), data4 LSB */
#घोषणा R_IA64_SEGREL64MSB	0x5e	/* @segrel(sym+add), data8 MSB */
#घोषणा R_IA64_SEGREL64LSB	0x5f	/* @segrel(sym+add), data8 LSB */
#घोषणा R_IA64_SECREL32MSB	0x64	/* @secrel(sym+add), data4 MSB */
#घोषणा R_IA64_SECREL32LSB	0x65	/* @secrel(sym+add), data4 LSB */
#घोषणा R_IA64_SECREL64MSB	0x66	/* @secrel(sym+add), data8 MSB */
#घोषणा R_IA64_SECREL64LSB	0x67	/* @secrel(sym+add), data8 LSB */
#घोषणा R_IA64_REL32MSB		0x6c	/* data 4 + REL */
#घोषणा R_IA64_REL32LSB		0x6d	/* data 4 + REL */
#घोषणा R_IA64_REL64MSB		0x6e	/* data 8 + REL */
#घोषणा R_IA64_REL64LSB		0x6f	/* data 8 + REL */
#घोषणा R_IA64_LTV32MSB		0x74	/* symbol + addend, data4 MSB */
#घोषणा R_IA64_LTV32LSB		0x75	/* symbol + addend, data4 LSB */
#घोषणा R_IA64_LTV64MSB		0x76	/* symbol + addend, data8 MSB */
#घोषणा R_IA64_LTV64LSB		0x77	/* symbol + addend, data8 LSB */
#घोषणा R_IA64_PCREL21BI	0x79	/* @pcrel(sym+add), ptb, call */
#घोषणा R_IA64_PCREL22		0x7a	/* @pcrel(sym+add), imm22 */
#घोषणा R_IA64_PCREL64I		0x7b	/* @pcrel(sym+add), imm64 */
#घोषणा R_IA64_IPLTMSB		0x80	/* dynamic reloc, imported PLT, MSB */
#घोषणा R_IA64_IPLTLSB		0x81	/* dynamic reloc, imported PLT, LSB */
#घोषणा R_IA64_COPY		0x84	/* dynamic reloc, data copy */
#घोषणा R_IA64_SUB		0x85	/* -symbol + addend, add imm22 */
#घोषणा R_IA64_LTOFF22X		0x86	/* LTOFF22, relaxable.  */
#घोषणा R_IA64_LDXMOV		0x87	/* Use of LTOFF22X.  */
#घोषणा R_IA64_TPREL14		0x91	/* @tprel(sym+add), add imm14 */
#घोषणा R_IA64_TPREL22		0x92	/* @tprel(sym+add), add imm22 */
#घोषणा R_IA64_TPREL64I		0x93	/* @tprel(sym+add), add imm64 */
#घोषणा R_IA64_TPREL64MSB	0x96	/* @tprel(sym+add), data8 MSB */
#घोषणा R_IA64_TPREL64LSB	0x97	/* @tprel(sym+add), data8 LSB */
#घोषणा R_IA64_LTOFF_TPREL22	0x9a	/* @ltoff(@tprel(s+a)), add imm22 */
#घोषणा R_IA64_DTPMOD64MSB	0xa6	/* @dtpmod(sym+add), data8 MSB */
#घोषणा R_IA64_DTPMOD64LSB	0xa7	/* @dtpmod(sym+add), data8 LSB */
#घोषणा R_IA64_LTOFF_DTPMOD22	0xaa	/* @ltoff(@dtpmod(s+a)), imm22 */
#घोषणा R_IA64_DTPREL14		0xb1	/* @dtprel(sym+add), imm14 */
#घोषणा R_IA64_DTPREL22		0xb2	/* @dtprel(sym+add), imm22 */
#घोषणा R_IA64_DTPREL64I	0xb3	/* @dtprel(sym+add), imm64 */
#घोषणा R_IA64_DTPREL32MSB	0xb4	/* @dtprel(sym+add), data4 MSB */
#घोषणा R_IA64_DTPREL32LSB	0xb5	/* @dtprel(sym+add), data4 LSB */
#घोषणा R_IA64_DTPREL64MSB	0xb6	/* @dtprel(sym+add), data8 MSB */
#घोषणा R_IA64_DTPREL64LSB	0xb7	/* @dtprel(sym+add), data8 LSB */
#घोषणा R_IA64_LTOFF_DTPREL22	0xba	/* @ltoff(@dtprel(s+a)), imm22 */

/* IA-64 specअगरic section flags: */
#घोषणा SHF_IA_64_SHORT		0x10000000	/* section near gp */

/*
 * We use (abuse?) this macro to insert the (empty) vm_area that is
 * used to map the रेजिस्टर backing store.  I करोn't see any better
 * place to करो this, but we should discuss this with Linus once we can
 * talk to him...
 */
बाह्य व्योम ia64_init_addr_space (व्योम);
#घोषणा ELF_PLAT_INIT(_r, load_addr)	ia64_init_addr_space()

/* ELF रेजिस्टर definitions.  This is needed क्रम core dump support.  */

/*
 * elf_gregset_t contains the application-level state in the following order:
 *	r0-r31
 *	NaT bits (क्रम r0-r31; bit N == 1 अगरf rN is a NaT)
 *	predicate रेजिस्टरs (p0-p63)
 *	b0-b7
 *	ip cfm psr
 *	ar.rsc ar.bsp ar.bspstore ar.rnat
 *	ar.ccv ar.unat ar.fpsr ar.pfs ar.lc ar.ec ar.csd ar.ssd
 */
#घोषणा ELF_NGREG	128	/* we really need just 72 but let's leave some headroom... */
#घोषणा ELF_NFPREG	128	/* f0 and f1 could be omitted, but so what... */

/* elf_gregset_t रेजिस्टर offsets */
#घोषणा ELF_GR_0_OFFSET     0
#घोषणा ELF_NAT_OFFSET     (32 * माप(elf_greg_t))
#घोषणा ELF_PR_OFFSET      (33 * माप(elf_greg_t))
#घोषणा ELF_BR_0_OFFSET    (34 * माप(elf_greg_t))
#घोषणा ELF_CR_IIP_OFFSET  (42 * माप(elf_greg_t))
#घोषणा ELF_CFM_OFFSET     (43 * माप(elf_greg_t))
#घोषणा ELF_CR_IPSR_OFFSET (44 * माप(elf_greg_t))
#घोषणा ELF_GR_OFFSET(i)   (ELF_GR_0_OFFSET + i * माप(elf_greg_t))
#घोषणा ELF_BR_OFFSET(i)   (ELF_BR_0_OFFSET + i * माप(elf_greg_t))
#घोषणा ELF_AR_RSC_OFFSET  (45 * माप(elf_greg_t))
#घोषणा ELF_AR_BSP_OFFSET  (46 * माप(elf_greg_t))
#घोषणा ELF_AR_BSPSTORE_OFFSET (47 * माप(elf_greg_t))
#घोषणा ELF_AR_RNAT_OFFSET (48 * माप(elf_greg_t))
#घोषणा ELF_AR_CCV_OFFSET  (49 * माप(elf_greg_t))
#घोषणा ELF_AR_UNAT_OFFSET (50 * माप(elf_greg_t))
#घोषणा ELF_AR_FPSR_OFFSET (51 * माप(elf_greg_t))
#घोषणा ELF_AR_PFS_OFFSET  (52 * माप(elf_greg_t))
#घोषणा ELF_AR_LC_OFFSET   (53 * माप(elf_greg_t))
#घोषणा ELF_AR_EC_OFFSET   (54 * माप(elf_greg_t))
#घोषणा ELF_AR_CSD_OFFSET  (55 * माप(elf_greg_t))
#घोषणा ELF_AR_SSD_OFFSET  (56 * माप(elf_greg_t))
#घोषणा ELF_AR_END_OFFSET  (57 * माप(elf_greg_t))

प्रकार अचिन्हित दीर्घ elf_greg_t;
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार काष्ठा ia64_fpreg elf_fpreg_t;
प्रकार elf_fpreg_t elf_fpregset_t[ELF_NFPREG];



काष्ठा pt_regs;	/* क्रमward declaration... */
बाह्य व्योम ia64_elf_core_copy_regs (काष्ठा pt_regs *src, elf_gregset_t dst);
#घोषणा ELF_CORE_COPY_REGS(_dest,_regs)	ia64_elf_core_copy_regs(_regs, _dest);

/* This macro yields a biपंचांगask that programs can use to figure out
   what inकाष्ठाion set this CPU supports.  */
#घोषणा ELF_HWCAP 	0

/* This macro yields a string that ld.so will use to load
   implementation specअगरic libraries क्रम optimization.  Not terribly
   relevant until we have real hardware to play with... */
#घोषणा ELF_PLATFORM	शून्य

#घोषणा elf_पढ़ो_implies_exec(ex, executable_stack)					\
	((executable_stack!=EXSTACK_DISABLE_X) && ((ex).e_flags & EF_IA_64_LINUX_EXECUTABLE_STACK) != 0)

काष्ठा task_काष्ठा;

#घोषणा GATE_EHDR	((स्थिर काष्ठा elfhdr *) GATE_ADDR)

/* update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT entries changes */
#घोषणा ARCH_DLINFO								\
करो अणु										\
	बाह्य अक्षर __kernel_syscall_via_epc[];					\
	NEW_AUX_ENT(AT_SYSINFO, (अचिन्हित दीर्घ) __kernel_syscall_via_epc);	\
	NEW_AUX_ENT(AT_SYSINFO_EHDR, (अचिन्हित दीर्घ) GATE_EHDR);		\
पूर्ण जबतक (0)

/*
 * क्रमmat क्रम entries in the Global Offset Table
 */
काष्ठा got_entry अणु
	uपूर्णांक64_t val;
पूर्ण;

/*
 * Layout of the Function Descriptor
 */
काष्ठा fdesc अणु
	uपूर्णांक64_t ip;
	uपूर्णांक64_t gp;
पूर्ण;

#पूर्ण_अगर /* _ASM_IA64_ELF_H */
