<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_ELF_EM_H
#घोषणा _LINUX_ELF_EM_H

/* These स्थिरants define the various ELF target machines */
#घोषणा EM_NONE		0
#घोषणा EM_M32		1
#घोषणा EM_SPARC	2
#घोषणा EM_386		3
#घोषणा EM_68K		4
#घोषणा EM_88K		5
#घोषणा EM_486		6	/* Perhaps disused */
#घोषणा EM_860		7
#घोषणा EM_MIPS		8	/* MIPS R3000 (officially, big-endian only) */
				/* Next two are historical and binaries and
				   modules of these types will be rejected by
				   Linux.  */
#घोषणा EM_MIPS_RS3_LE	10	/* MIPS R3000 little-endian */
#घोषणा EM_MIPS_RS4_BE	10	/* MIPS R4000 big-endian */

#घोषणा EM_PARISC	15	/* HPPA */
#घोषणा EM_SPARC32PLUS	18	/* Sun's "v8plus" */
#घोषणा EM_PPC		20	/* PowerPC */
#घोषणा EM_PPC64	21	 /* PowerPC64 */
#घोषणा EM_SPU		23	/* Cell BE SPU */
#घोषणा EM_ARM		40	/* ARM 32 bit */
#घोषणा EM_SH		42	/* SuperH */
#घोषणा EM_SPARCV9	43	/* SPARC v9 64-bit */
#घोषणा EM_H8_300	46	/* Renesas H8/300 */
#घोषणा EM_IA_64	50	/* HP/Intel IA-64 */
#घोषणा EM_X86_64	62	/* AMD x86-64 */
#घोषणा EM_S390		22	/* IBM S/390 */
#घोषणा EM_CRIS		76	/* Axis Communications 32-bit embedded processor */
#घोषणा EM_M32R		88	/* Renesas M32R */
#घोषणा EM_MN10300	89	/* Panasonic/MEI MN10300, AM33 */
#घोषणा EM_OPENRISC     92     /* OpenRISC 32-bit embedded processor */
#घोषणा EM_ARCOMPACT	93	/* ARCompact processor */
#घोषणा EM_XTENSA	94	/* Tensilica Xtensa Architecture */
#घोषणा EM_BLACKFIN     106     /* ADI Blackfin Processor */
#घोषणा EM_UNICORE	110	/* UniCore-32 */
#घोषणा EM_ALTERA_NIOS2	113	/* Altera Nios II soft-core processor */
#घोषणा EM_TI_C6000	140	/* TI C6X DSPs */
#घोषणा EM_HEXAGON	164	/* QUALCOMM Hexagon */
#घोषणा EM_NDS32	167	/* Andes Technology compact code size
				   embedded RISC processor family */
#घोषणा EM_AARCH64	183	/* ARM 64 bit */
#घोषणा EM_TILEPRO	188	/* Tilera TILEPro */
#घोषणा EM_MICROBLAZE	189	/* Xilinx MicroBlaze */
#घोषणा EM_TILEGX	191	/* Tilera TILE-Gx */
#घोषणा EM_ARCV2	195	/* ARCv2 Cores */
#घोषणा EM_RISCV	243	/* RISC-V */
#घोषणा EM_BPF		247	/* Linux BPF - in-kernel भव machine */
#घोषणा EM_CSKY		252	/* C-SKY */
#घोषणा EM_FRV		0x5441	/* Fujitsu FR-V */

/*
 * This is an पूर्णांकerim value that we will use until the committee comes
 * up with a final number.
 */
#घोषणा EM_ALPHA	0x9026

/* Bogus old m32r magic number, used by old tools. */
#घोषणा EM_CYGNUS_M32R	0x9041
/* This is the old पूर्णांकerim value क्रम S/390 architecture */
#घोषणा EM_S390_OLD	0xA390
/* Also Panasonic/MEI MN10300, AM33 */
#घोषणा EM_CYGNUS_MN10300 0xbeef


#पूर्ण_अगर /* _LINUX_ELF_EM_H */
