<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * ELF रेजिस्टर definitions..
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_ASM_POWERPC_ELF_H
#घोषणा _UAPI_ASM_POWERPC_ELF_H


#समावेश <linux/types.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/auxvec.h>

/* PowerPC relocations defined by the ABIs */
#घोषणा R_PPC_NONE		0
#घोषणा R_PPC_ADDR32		1	/* 32bit असलolute address */
#घोषणा R_PPC_ADDR24		2	/* 26bit address, 2 bits ignored.  */
#घोषणा R_PPC_ADDR16		3	/* 16bit असलolute address */
#घोषणा R_PPC_ADDR16_LO		4	/* lower 16bit of असलolute address */
#घोषणा R_PPC_ADDR16_HI		5	/* high 16bit of असलolute address */
#घोषणा R_PPC_ADDR16_HA		6	/* adjusted high 16bit */
#घोषणा R_PPC_ADDR14		7	/* 16bit address, 2 bits ignored */
#घोषणा R_PPC_ADDR14_BRTAKEN	8
#घोषणा R_PPC_ADDR14_BRNTAKEN	9
#घोषणा R_PPC_REL24		10	/* PC relative 26 bit */
#घोषणा R_PPC_REL14		11	/* PC relative 16 bit */
#घोषणा R_PPC_REL14_BRTAKEN	12
#घोषणा R_PPC_REL14_BRNTAKEN	13
#घोषणा R_PPC_GOT16		14
#घोषणा R_PPC_GOT16_LO		15
#घोषणा R_PPC_GOT16_HI		16
#घोषणा R_PPC_GOT16_HA		17
#घोषणा R_PPC_PLTREL24		18
#घोषणा R_PPC_COPY		19
#घोषणा R_PPC_GLOB_DAT		20
#घोषणा R_PPC_JMP_SLOT		21
#घोषणा R_PPC_RELATIVE		22
#घोषणा R_PPC_LOCAL24PC		23
#घोषणा R_PPC_UADDR32		24
#घोषणा R_PPC_UADDR16		25
#घोषणा R_PPC_REL32		26
#घोषणा R_PPC_PLT32		27
#घोषणा R_PPC_PLTREL32		28
#घोषणा R_PPC_PLT16_LO		29
#घोषणा R_PPC_PLT16_HI		30
#घोषणा R_PPC_PLT16_HA		31
#घोषणा R_PPC_SDAREL16		32
#घोषणा R_PPC_SECTOFF		33
#घोषणा R_PPC_SECTOFF_LO	34
#घोषणा R_PPC_SECTOFF_HI	35
#घोषणा R_PPC_SECTOFF_HA	36

/* PowerPC relocations defined क्रम the TLS access ABI.  */
#घोषणा R_PPC_TLS		67 /* none	(sym+add)@tls */
#घोषणा R_PPC_DTPMOD32		68 /* word32	(sym+add)@dtpmod */
#घोषणा R_PPC_TPREL16		69 /* half16*	(sym+add)@tprel */
#घोषणा R_PPC_TPREL16_LO	70 /* half16	(sym+add)@tprel@l */
#घोषणा R_PPC_TPREL16_HI	71 /* half16	(sym+add)@tprel@h */
#घोषणा R_PPC_TPREL16_HA	72 /* half16	(sym+add)@tprel@ha */
#घोषणा R_PPC_TPREL32		73 /* word32	(sym+add)@tprel */
#घोषणा R_PPC_DTPREL16		74 /* half16*	(sym+add)@dtprel */
#घोषणा R_PPC_DTPREL16_LO	75 /* half16	(sym+add)@dtprel@l */
#घोषणा R_PPC_DTPREL16_HI	76 /* half16	(sym+add)@dtprel@h */
#घोषणा R_PPC_DTPREL16_HA	77 /* half16	(sym+add)@dtprel@ha */
#घोषणा R_PPC_DTPREL32		78 /* word32	(sym+add)@dtprel */
#घोषणा R_PPC_GOT_TLSGD16	79 /* half16*	(sym+add)@got@tlsgd */
#घोषणा R_PPC_GOT_TLSGD16_LO	80 /* half16	(sym+add)@got@tlsgd@l */
#घोषणा R_PPC_GOT_TLSGD16_HI	81 /* half16	(sym+add)@got@tlsgd@h */
#घोषणा R_PPC_GOT_TLSGD16_HA	82 /* half16	(sym+add)@got@tlsgd@ha */
#घोषणा R_PPC_GOT_TLSLD16	83 /* half16*	(sym+add)@got@tlsld */
#घोषणा R_PPC_GOT_TLSLD16_LO	84 /* half16	(sym+add)@got@tlsld@l */
#घोषणा R_PPC_GOT_TLSLD16_HI	85 /* half16	(sym+add)@got@tlsld@h */
#घोषणा R_PPC_GOT_TLSLD16_HA	86 /* half16	(sym+add)@got@tlsld@ha */
#घोषणा R_PPC_GOT_TPREL16	87 /* half16*	(sym+add)@got@tprel */
#घोषणा R_PPC_GOT_TPREL16_LO	88 /* half16	(sym+add)@got@tprel@l */
#घोषणा R_PPC_GOT_TPREL16_HI	89 /* half16	(sym+add)@got@tprel@h */
#घोषणा R_PPC_GOT_TPREL16_HA	90 /* half16	(sym+add)@got@tprel@ha */
#घोषणा R_PPC_GOT_DTPREL16	91 /* half16*	(sym+add)@got@dtprel */
#घोषणा R_PPC_GOT_DTPREL16_LO	92 /* half16*	(sym+add)@got@dtprel@l */
#घोषणा R_PPC_GOT_DTPREL16_HI	93 /* half16*	(sym+add)@got@dtprel@h */
#घोषणा R_PPC_GOT_DTPREL16_HA	94 /* half16*	(sym+add)@got@dtprel@ha */

/* keep this the last entry. */
#घोषणा R_PPC_NUM		95


#घोषणा ELF_NGREG	48	/* includes nip, msr, lr, etc. */
#घोषणा ELF_NFPREG	33	/* includes fpscr */
#घोषणा ELF_NVMX	34	/* includes all vector रेजिस्टरs */
#घोषणा ELF_NVSX	32	/* includes all VSX रेजिस्टरs */
#घोषणा ELF_NTMSPRREG	3	/* include tfhar, tfiar, texasr */
#घोषणा ELF_NEBB	3	/* includes ebbrr, ebbhr, bescr */
#घोषणा ELF_NPMU	5	/* includes siar, sdar, sier, mmcr2, mmcr0 */
#घोषणा ELF_NPKEY	3	/* includes amr, iamr, uamor */

प्रकार अचिन्हित दीर्घ elf_greg_t64;
प्रकार elf_greg_t64 elf_gregset_t64[ELF_NGREG];

प्रकार अचिन्हित पूर्णांक elf_greg_t32;
प्रकार elf_greg_t32 elf_gregset_t32[ELF_NGREG];
प्रकार elf_gregset_t32 compat_elf_gregset_t;

/*
 * ELF_ARCH, CLASS, and DATA are used to set parameters in the core dumps.
 */
#अगर_घोषित __घातerpc64__
# define ELF_NVRREG32	33	/* includes vscr & vrsave stuffed together */
# define ELF_NVRREG	34	/* includes vscr & vrsave in split vectors */
# define ELF_NVSRHALFREG 32	/* Half the vsx रेजिस्टरs */
# define ELF_GREG_TYPE	elf_greg_t64
# define ELF_ARCH	EM_PPC64
# define ELF_CLASS	ELFCLASS64
प्रकार elf_greg_t64 elf_greg_t;
प्रकार elf_gregset_t64 elf_gregset_t;
#अन्यथा
# define ELF_NEVRREG	34	/* includes acc (as 2) */
# define ELF_NVRREG	33	/* includes vscr */
# define ELF_GREG_TYPE	elf_greg_t32
# define ELF_ARCH	EM_PPC
# define ELF_CLASS	ELFCLASS32
प्रकार elf_greg_t32 elf_greg_t;
प्रकार elf_gregset_t32 elf_gregset_t;
#पूर्ण_अगर /* __घातerpc64__ */

#अगर_घोषित __BIG_ENDIAN__
#घोषणा ELF_DATA	ELFDATA2MSB
#अन्यथा
#घोषणा ELF_DATA	ELFDATA2LSB
#पूर्ण_अगर

/* Floating poपूर्णांक रेजिस्टरs */
प्रकार द्विगुन elf_fpreg_t;
प्रकार elf_fpreg_t elf_fpregset_t[ELF_NFPREG];

/* Altivec रेजिस्टरs */
/*
 * The entries with indexes 0-31 contain the corresponding vector रेजिस्टरs. 
 * The entry with index 32 contains the vscr as the last word (offset 12) 
 * within the quadword.  This allows the vscr to be stored as either a 
 * quadword (since it must be copied via a vector रेजिस्टर to/from storage) 
 * or as a word.  
 *
 * 64-bit kernel notes: The entry at index 33 contains the vrsave as the first  
 * word (offset 0) within the quadword.
 *
 * This definition of the VMX state is compatible with the current PPC32 
 * ptrace पूर्णांकerface.  This allows संकेत handling and ptrace to use the same 
 * काष्ठाures.  This also simplअगरies the implementation of a bi-arch 
 * (combined (32- and 64-bit) gdb.
 *
 * Note that it's _not_ compatible with 32 bits ucontext which stuffs the
 * vrsave aदीर्घ with vscr and so only uses 33 vectors क्रम the रेजिस्टर set
 */
प्रकार __vector128 elf_vrreg_t;
प्रकार elf_vrreg_t elf_vrregset_t[ELF_NVRREG];
#अगर_घोषित __घातerpc64__
प्रकार elf_vrreg_t elf_vrregset_t32[ELF_NVRREG32];
प्रकार elf_fpreg_t elf_vsrreghalf_t32[ELF_NVSRHALFREG];
#पूर्ण_अगर

/* PowerPC64 relocations defined by the ABIs */
#घोषणा R_PPC64_NONE    R_PPC_NONE
#घोषणा R_PPC64_ADDR32  R_PPC_ADDR32  /* 32bit असलolute address.  */
#घोषणा R_PPC64_ADDR24  R_PPC_ADDR24  /* 26bit address, word aligned.  */
#घोषणा R_PPC64_ADDR16  R_PPC_ADDR16  /* 16bit असलolute address. */
#घोषणा R_PPC64_ADDR16_LO R_PPC_ADDR16_LO /* lower 16bits of असल. address.  */
#घोषणा R_PPC64_ADDR16_HI R_PPC_ADDR16_HI /* high 16bits of असल. address. */
#घोषणा R_PPC64_ADDR16_HA R_PPC_ADDR16_HA /* adjusted high 16bits.  */
#घोषणा R_PPC64_ADDR14 R_PPC_ADDR14   /* 16bit address, word aligned.  */
#घोषणा R_PPC64_ADDR14_BRTAKEN  R_PPC_ADDR14_BRTAKEN
#घोषणा R_PPC64_ADDR14_BRNTAKEN R_PPC_ADDR14_BRNTAKEN
#घोषणा R_PPC64_REL24   R_PPC_REL24 /* PC relative 26 bit, word aligned.  */
#घोषणा R_PPC64_REL14   R_PPC_REL14 /* PC relative 16 bit. */
#घोषणा R_PPC64_REL14_BRTAKEN   R_PPC_REL14_BRTAKEN
#घोषणा R_PPC64_REL14_BRNTAKEN  R_PPC_REL14_BRNTAKEN
#घोषणा R_PPC64_GOT16     R_PPC_GOT16
#घोषणा R_PPC64_GOT16_LO  R_PPC_GOT16_LO
#घोषणा R_PPC64_GOT16_HI  R_PPC_GOT16_HI
#घोषणा R_PPC64_GOT16_HA  R_PPC_GOT16_HA

#घोषणा R_PPC64_COPY      R_PPC_COPY
#घोषणा R_PPC64_GLOB_DAT  R_PPC_GLOB_DAT
#घोषणा R_PPC64_JMP_SLOT  R_PPC_JMP_SLOT
#घोषणा R_PPC64_RELATIVE  R_PPC_RELATIVE

#घोषणा R_PPC64_UADDR32   R_PPC_UADDR32
#घोषणा R_PPC64_UADDR16   R_PPC_UADDR16
#घोषणा R_PPC64_REL32     R_PPC_REL32
#घोषणा R_PPC64_PLT32     R_PPC_PLT32
#घोषणा R_PPC64_PLTREL32  R_PPC_PLTREL32
#घोषणा R_PPC64_PLT16_LO  R_PPC_PLT16_LO
#घोषणा R_PPC64_PLT16_HI  R_PPC_PLT16_HI
#घोषणा R_PPC64_PLT16_HA  R_PPC_PLT16_HA

#घोषणा R_PPC64_SECTOFF     R_PPC_SECTOFF
#घोषणा R_PPC64_SECTOFF_LO  R_PPC_SECTOFF_LO
#घोषणा R_PPC64_SECTOFF_HI  R_PPC_SECTOFF_HI
#घोषणा R_PPC64_SECTOFF_HA  R_PPC_SECTOFF_HA
#घोषणा R_PPC64_ADDR30          37  /* word30 (S + A - P) >> 2.  */
#घोषणा R_PPC64_ADDR64          38  /* द्विगुनword64 S + A.  */
#घोषणा R_PPC64_ADDR16_HIGHER   39  /* half16 #higher(S + A).  */
#घोषणा R_PPC64_ADDR16_HIGHERA  40  /* half16 #highera(S + A).  */
#घोषणा R_PPC64_ADDR16_HIGHEST  41  /* half16 #highest(S + A).  */
#घोषणा R_PPC64_ADDR16_HIGHESTA 42  /* half16 #highesta(S + A). */
#घोषणा R_PPC64_UADDR64     43  /* द्विगुनword64 S + A.  */
#घोषणा R_PPC64_REL64       44  /* द्विगुनword64 S + A - P.  */
#घोषणा R_PPC64_PLT64       45  /* द्विगुनword64 L + A.  */
#घोषणा R_PPC64_PLTREL64    46  /* द्विगुनword64 L + A - P.  */
#घोषणा R_PPC64_TOC16       47  /* half16* S + A - .TOC.  */
#घोषणा R_PPC64_TOC16_LO    48  /* half16 #lo(S + A - .TOC.).  */
#घोषणा R_PPC64_TOC16_HI    49  /* half16 #hi(S + A - .TOC.).  */
#घोषणा R_PPC64_TOC16_HA    50  /* half16 #ha(S + A - .TOC.).  */
#घोषणा R_PPC64_TOC         51  /* द्विगुनword64 .TOC. */
#घोषणा R_PPC64_PLTGOT16    52  /* half16* M + A.  */
#घोषणा R_PPC64_PLTGOT16_LO 53  /* half16 #lo(M + A).  */
#घोषणा R_PPC64_PLTGOT16_HI 54  /* half16 #hi(M + A).  */
#घोषणा R_PPC64_PLTGOT16_HA 55  /* half16 #ha(M + A).  */

#घोषणा R_PPC64_ADDR16_DS      56 /* half16ds* (S + A) >> 2.  */
#घोषणा R_PPC64_ADDR16_LO_DS   57 /* half16ds  #lo(S + A) >> 2.  */
#घोषणा R_PPC64_GOT16_DS       58 /* half16ds* (G + A) >> 2.  */
#घोषणा R_PPC64_GOT16_LO_DS    59 /* half16ds  #lo(G + A) >> 2.  */
#घोषणा R_PPC64_PLT16_LO_DS    60 /* half16ds  #lo(L + A) >> 2.  */
#घोषणा R_PPC64_SECTOFF_DS     61 /* half16ds* (R + A) >> 2.  */
#घोषणा R_PPC64_SECTOFF_LO_DS  62 /* half16ds  #lo(R + A) >> 2.  */
#घोषणा R_PPC64_TOC16_DS       63 /* half16ds* (S + A - .TOC.) >> 2.  */
#घोषणा R_PPC64_TOC16_LO_DS    64 /* half16ds  #lo(S + A - .TOC.) >> 2.  */
#घोषणा R_PPC64_PLTGOT16_DS    65 /* half16ds* (M + A) >> 2.  */
#घोषणा R_PPC64_PLTGOT16_LO_DS 66 /* half16ds  #lo(M + A) >> 2.  */

/* PowerPC64 relocations defined क्रम the TLS access ABI.  */
#घोषणा R_PPC64_TLS		67 /* none	(sym+add)@tls */
#घोषणा R_PPC64_DTPMOD64	68 /* द्विगुनword64 (sym+add)@dtpmod */
#घोषणा R_PPC64_TPREL16		69 /* half16*	(sym+add)@tprel */
#घोषणा R_PPC64_TPREL16_LO	70 /* half16	(sym+add)@tprel@l */
#घोषणा R_PPC64_TPREL16_HI	71 /* half16	(sym+add)@tprel@h */
#घोषणा R_PPC64_TPREL16_HA	72 /* half16	(sym+add)@tprel@ha */
#घोषणा R_PPC64_TPREL64		73 /* द्विगुनword64 (sym+add)@tprel */
#घोषणा R_PPC64_DTPREL16	74 /* half16*	(sym+add)@dtprel */
#घोषणा R_PPC64_DTPREL16_LO	75 /* half16	(sym+add)@dtprel@l */
#घोषणा R_PPC64_DTPREL16_HI	76 /* half16	(sym+add)@dtprel@h */
#घोषणा R_PPC64_DTPREL16_HA	77 /* half16	(sym+add)@dtprel@ha */
#घोषणा R_PPC64_DTPREL64	78 /* द्विगुनword64 (sym+add)@dtprel */
#घोषणा R_PPC64_GOT_TLSGD16	79 /* half16*	(sym+add)@got@tlsgd */
#घोषणा R_PPC64_GOT_TLSGD16_LO	80 /* half16	(sym+add)@got@tlsgd@l */
#घोषणा R_PPC64_GOT_TLSGD16_HI	81 /* half16	(sym+add)@got@tlsgd@h */
#घोषणा R_PPC64_GOT_TLSGD16_HA	82 /* half16	(sym+add)@got@tlsgd@ha */
#घोषणा R_PPC64_GOT_TLSLD16	83 /* half16*	(sym+add)@got@tlsld */
#घोषणा R_PPC64_GOT_TLSLD16_LO	84 /* half16	(sym+add)@got@tlsld@l */
#घोषणा R_PPC64_GOT_TLSLD16_HI	85 /* half16	(sym+add)@got@tlsld@h */
#घोषणा R_PPC64_GOT_TLSLD16_HA	86 /* half16	(sym+add)@got@tlsld@ha */
#घोषणा R_PPC64_GOT_TPREL16_DS	87 /* half16ds*	(sym+add)@got@tprel */
#घोषणा R_PPC64_GOT_TPREL16_LO_DS 88 /* half16ds (sym+add)@got@tprel@l */
#घोषणा R_PPC64_GOT_TPREL16_HI	89 /* half16	(sym+add)@got@tprel@h */
#घोषणा R_PPC64_GOT_TPREL16_HA	90 /* half16	(sym+add)@got@tprel@ha */
#घोषणा R_PPC64_GOT_DTPREL16_DS	91 /* half16ds*	(sym+add)@got@dtprel */
#घोषणा R_PPC64_GOT_DTPREL16_LO_DS 92 /* half16ds (sym+add)@got@dtprel@l */
#घोषणा R_PPC64_GOT_DTPREL16_HI	93 /* half16	(sym+add)@got@dtprel@h */
#घोषणा R_PPC64_GOT_DTPREL16_HA	94 /* half16	(sym+add)@got@dtprel@ha */
#घोषणा R_PPC64_TPREL16_DS	95 /* half16ds*	(sym+add)@tprel */
#घोषणा R_PPC64_TPREL16_LO_DS	96 /* half16ds	(sym+add)@tprel@l */
#घोषणा R_PPC64_TPREL16_HIGHER	97 /* half16	(sym+add)@tprel@higher */
#घोषणा R_PPC64_TPREL16_HIGHERA	98 /* half16	(sym+add)@tprel@highera */
#घोषणा R_PPC64_TPREL16_HIGHEST	99 /* half16	(sym+add)@tprel@highest */
#घोषणा R_PPC64_TPREL16_HIGHESTA 100 /* half16	(sym+add)@tprel@highesta */
#घोषणा R_PPC64_DTPREL16_DS	101 /* half16ds* (sym+add)@dtprel */
#घोषणा R_PPC64_DTPREL16_LO_DS	102 /* half16ds	(sym+add)@dtprel@l */
#घोषणा R_PPC64_DTPREL16_HIGHER	103 /* half16	(sym+add)@dtprel@higher */
#घोषणा R_PPC64_DTPREL16_HIGHERA 104 /* half16	(sym+add)@dtprel@highera */
#घोषणा R_PPC64_DTPREL16_HIGHEST 105 /* half16	(sym+add)@dtprel@highest */
#घोषणा R_PPC64_DTPREL16_HIGHESTA 106 /* half16	(sym+add)@dtprel@highesta */
#घोषणा R_PPC64_TLSGD		107
#घोषणा R_PPC64_TLSLD		108
#घोषणा R_PPC64_TOCSAVE		109

#घोषणा R_PPC64_ENTRY		118

#घोषणा R_PPC64_REL16		249
#घोषणा R_PPC64_REL16_LO	250
#घोषणा R_PPC64_REL16_HI	251
#घोषणा R_PPC64_REL16_HA	252

/* Keep this the last entry.  */
#घोषणा R_PPC64_NUM		253

/* There's actually a third entry here, but it's unused */
काष्ठा ppc64_opd_entry
अणु
	अचिन्हित दीर्घ funcaddr;
	अचिन्हित दीर्घ r2;
पूर्ण;


#पूर्ण_अगर /* _UAPI_ASM_POWERPC_ELF_H */
