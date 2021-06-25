<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_REG_H
#घोषणा _SELFTESTS_POWERPC_REG_H

#घोषणा __stringअगरy_1(x)        #x
#घोषणा __stringअगरy(x)          __stringअगरy_1(x)

#घोषणा mfspr(rn)	(अणुअचिन्हित दीर्घ rval; \
			 यंत्र अस्थिर("mfspr %0," _str(rn) \
				    : "=r" (rval)); rval; पूर्ण)
#घोषणा mtspr(rn, v)	यंत्र अस्थिर("mtspr " _str(rn) ",%0" : \
				    : "r" ((अचिन्हित दीर्घ)(v)) \
				    : "memory")

#घोषणा mb()		यंत्र अस्थिर("sync" : : : "memory");
#घोषणा barrier()	यंत्र अस्थिर("" : : : "memory");

#घोषणा SPRN_MMCR2     769
#घोषणा SPRN_MMCRA     770
#घोषणा SPRN_MMCR0     779
#घोषणा   MMCR0_PMAO   0x00000080
#घोषणा   MMCR0_PMAE   0x04000000
#घोषणा   MMCR0_FC     0x80000000
#घोषणा SPRN_EBBHR     804
#घोषणा SPRN_EBBRR     805
#घोषणा SPRN_BESCR     806     /* Branch event status & control रेजिस्टर */
#घोषणा SPRN_BESCRS    800     /* Branch event status & control set (1 bits set to 1) */
#घोषणा SPRN_BESCRSU   801     /* Branch event status & control set upper */
#घोषणा SPRN_BESCRR    802     /* Branch event status & control REset (1 bits set to 0) */
#घोषणा SPRN_BESCRRU   803     /* Branch event status & control REset upper */

#घोषणा BESCR_PMEO     0x1     /* PMU Event-based exception Occurred */
#घोषणा BESCR_PME      (0x1ul << 32) /* PMU Event-based exception Enable */

#घोषणा SPRN_PMC1      771
#घोषणा SPRN_PMC2      772
#घोषणा SPRN_PMC3      773
#घोषणा SPRN_PMC4      774
#घोषणा SPRN_PMC5      775
#घोषणा SPRN_PMC6      776

#घोषणा SPRN_SIAR      780
#घोषणा SPRN_SDAR      781
#घोषणा SPRN_SIER      768

#घोषणा SPRN_TEXASR     0x82    /* Transaction Exception and Status Register */
#घोषणा SPRN_TFIAR      0x81    /* Transaction Failure Inst Addr    */
#घोषणा SPRN_TFHAR      0x80    /* Transaction Failure Handler Addr */
#घोषणा SPRN_TAR        0x32f	/* Target Address Register */

#घोषणा SPRN_DSCR_PRIV 0x11	/* Privilege State DSCR */
#घोषणा SPRN_DSCR      0x03	/* Data Stream Control Register */
#घोषणा SPRN_PPR       896	/* Program Priority Register */
#घोषणा SPRN_AMR       13	/* Authority Mask Register - problem state */

#घोषणा set_amr(v)	यंत्र अस्थिर("isync;" \
				     "mtspr " __stringअगरy(SPRN_AMR) ",%0;" \
				     "isync" : \
				    : "r" ((अचिन्हित दीर्घ)(v)) \
				    : "memory")

/* TEXASR रेजिस्टर bits */
#घोषणा TEXASR_FC	0xFE00000000000000
#घोषणा TEXASR_FP	0x0100000000000000
#घोषणा TEXASR_DA	0x0080000000000000
#घोषणा TEXASR_NO	0x0040000000000000
#घोषणा TEXASR_FO	0x0020000000000000
#घोषणा TEXASR_SIC	0x0010000000000000
#घोषणा TEXASR_NTC	0x0008000000000000
#घोषणा TEXASR_TC	0x0004000000000000
#घोषणा TEXASR_TIC	0x0002000000000000
#घोषणा TEXASR_IC	0x0001000000000000
#घोषणा TEXASR_IFC	0x0000800000000000
#घोषणा TEXASR_ABT	0x0000000100000000
#घोषणा TEXASR_SPD	0x0000000080000000
#घोषणा TEXASR_HV	0x0000000020000000
#घोषणा TEXASR_PR	0x0000000010000000
#घोषणा TEXASR_FS	0x0000000008000000
#घोषणा TEXASR_TE	0x0000000004000000
#घोषणा TEXASR_ROT	0x0000000002000000

/* MSR रेजिस्टर bits */
#घोषणा MSR_TS_S_LG     33              /* Trans Mem state: Suspended */
#घोषणा MSR_TS_T_LG	34              /* Trans Mem state: Active */

#घोषणा __MASK(X)       (1UL<<(X))

/* macro to check TM MSR bits */
#घोषणा MSR_TS_S        __MASK(MSR_TS_S_LG)   /* Transaction Suspended */
#घोषणा MSR_TS_T	__MASK(MSR_TS_T_LG)   /* Transaction Transactional */

/* Vector Inकाष्ठाions */
#घोषणा VSX_XX1(xs, ra, rb)	(((xs) & 0x1f) << 21 | ((ra) << 16) |  \
				 ((rb) << 11) | (((xs) >> 5)))
#घोषणा STXVD2X(xs, ra, rb)	.दीर्घ (0x7c000798 | VSX_XX1((xs), (ra), (rb)))
#घोषणा LXVD2X(xs, ra, rb)	.दीर्घ (0x7c000698 | VSX_XX1((xs), (ra), (rb)))

#घोषणा ASM_LOAD_GPR_IMMED(_यंत्र_symbol_name_immed) \
		"li 14, %[" #_यंत्र_symbol_name_immed "];" \
		"li 15, %[" #_यंत्र_symbol_name_immed "];" \
		"li 16, %[" #_यंत्र_symbol_name_immed "];" \
		"li 17, %[" #_यंत्र_symbol_name_immed "];" \
		"li 18, %[" #_यंत्र_symbol_name_immed "];" \
		"li 19, %[" #_यंत्र_symbol_name_immed "];" \
		"li 20, %[" #_यंत्र_symbol_name_immed "];" \
		"li 21, %[" #_यंत्र_symbol_name_immed "];" \
		"li 22, %[" #_यंत्र_symbol_name_immed "];" \
		"li 23, %[" #_यंत्र_symbol_name_immed "];" \
		"li 24, %[" #_यंत्र_symbol_name_immed "];" \
		"li 25, %[" #_यंत्र_symbol_name_immed "];" \
		"li 26, %[" #_यंत्र_symbol_name_immed "];" \
		"li 27, %[" #_यंत्र_symbol_name_immed "];" \
		"li 28, %[" #_यंत्र_symbol_name_immed "];" \
		"li 29, %[" #_यंत्र_symbol_name_immed "];" \
		"li 30, %[" #_यंत्र_symbol_name_immed "];" \
		"li 31, %[" #_यंत्र_symbol_name_immed "];"

#घोषणा ASM_LOAD_FPR_SINGLE_PRECISION(_यंत्र_symbol_name_addr) \
		"lfs 0, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 1, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 2, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 3, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 4, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 5, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 6, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 7, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 8, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 9, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 10, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 11, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 12, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 13, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 14, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 15, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 16, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 17, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 18, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 19, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 20, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 21, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 22, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 23, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 24, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 25, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 26, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 27, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 28, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 29, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 30, 0(%[" #_यंत्र_symbol_name_addr "]);" \
		"lfs 31, 0(%[" #_यंत्र_symbol_name_addr "]);"

#अगर_अघोषित __ASSEMBLER__
व्योम store_gpr(अचिन्हित दीर्घ *addr);
व्योम load_gpr(अचिन्हित दीर्घ *addr);
व्योम load_fpr_single_precision(भग्न *addr);
व्योम store_fpr_single_precision(भग्न *addr);
#पूर्ण_अगर /* end of __ASSEMBLER__ */

#पूर्ण_अगर /* _SELFTESTS_POWERPC_REG_H */
