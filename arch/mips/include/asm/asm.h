<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 1997, 1999, 2001 by Ralf Baechle
 * Copyright (C) 1999 by Silicon Graphics, Inc.
 * Copyright (C) 2001 MIPS Technologies, Inc.
 * Copyright (C) 2002  Maciej W. Rozycki
 *
 * Some useful macros क्रम MIPS assembler code
 *
 * Some of the routines below contain useless nops that will be optimized
 * away by gas in -O mode. These nops are however required to fill delay
 * slots in noreorder mode.
 */
#अगर_अघोषित __ASM_ASM_H
#घोषणा __ASM_ASM_H

#समावेश <यंत्र/sgidefs.h>
#समावेश <यंत्र/यंत्र-eva.h>

#अगर_अघोषित __VDSO__
/*
 * Emit CFI data in .debug_frame sections, not .eh_frame sections.
 * We करोn't करो DWARF unwinding at runसमय, so only the offline DWARF
 * inक्रमmation is useful to anyone. Note we should change this अगर we
 * ever decide to enable DWARF unwinding at runसमय.
 */
#घोषणा CFI_SECTIONS	.cfi_sections .debug_frame
#अन्यथा
 /*
  * For the vDSO, emit both runसमय unwind inक्रमmation and debug
  * symbols क्रम the .dbg file.
  */
#घोषणा CFI_SECTIONS
#पूर्ण_अगर

/*
 * LEAF - declare leaf routine
 */
#घोषणा LEAF(symbol)					\
		CFI_SECTIONS;				\
		.globl	symbol;				\
		.align	2;				\
		.type	symbol, @function;		\
		.ent	symbol, 0;			\
symbol:		.frame	sp, 0, ra;			\
		.cfi_startproc;				\
		.insn

/*
 * NESTED - declare nested routine entry poपूर्णांक
 */
#घोषणा NESTED(symbol, framesize, rpc)			\
		CFI_SECTIONS;				\
		.globl	symbol;				\
		.align	2;				\
		.type	symbol, @function;		\
		.ent	symbol, 0;			\
symbol:		.frame	sp, framesize, rpc;		\
		.cfi_startproc;				\
		.insn

/*
 * END - mark end of function
 */
#घोषणा END(function)					\
		.cfi_endproc;				\
		.end	function;			\
		.size	function, .-function

/*
 * EXPORT - export definition of symbol
 */
#घोषणा EXPORT(symbol)					\
		.globl	symbol;				\
symbol:

/*
 * FEXPORT - export definition of a function symbol
 */
#घोषणा FEXPORT(symbol)					\
		.globl	symbol;				\
		.type	symbol, @function;		\
symbol:		.insn

/*
 * ABS - export असलolute symbol
 */
#घोषणा ABS(symbol,value)				\
		.globl	symbol;				\
symbol		=	value

#घोषणा TEXT(msg)					\
		.pushsection .data;			\
8:		.asciiz msg;				\
		.popsection;

#घोषणा ASM_PANIC(msg)					\
		.set	push;				\
		.set	reorder;			\
		PTR_LA	a0, 8f;				\
		jal	panic;				\
9:		b	9b;				\
		.set	pop;				\
		TEXT(msg)

/*
 * Prपूर्णांक क्रमmatted string
 */
#अगर_घोषित CONFIG_PRINTK
#घोषणा ASM_PRINT(string)				\
		.set	push;				\
		.set	reorder;			\
		PTR_LA	a0, 8f;				\
		jal	prपूर्णांकk;				\
		.set	pop;				\
		TEXT(string)
#अन्यथा
#घोषणा ASM_PRINT(string)
#पूर्ण_अगर

/*
 * Stack alignment
 */
#अगर (_MIPS_SIM == _MIPS_SIM_ABI32)
#घोषणा ALSZ	7
#घोषणा ALMASK	~7
#पूर्ण_अगर
#अगर (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64)
#घोषणा ALSZ	15
#घोषणा ALMASK	~15
#पूर्ण_अगर

/*
 * Macros to handle dअगरferent poपूर्णांकer/रेजिस्टर sizes क्रम 32/64-bit code
 */

/*
 * Size of a रेजिस्टर
 */
#अगर_घोषित __mips64
#घोषणा SZREG	8
#अन्यथा
#घोषणा SZREG	4
#पूर्ण_अगर

/*
 * Use the following macros in assemblercode to load/store रेजिस्टरs,
 * poपूर्णांकers etc.
 */
#अगर (_MIPS_SIM == _MIPS_SIM_ABI32)
#घोषणा REG_S		sw
#घोषणा REG_L		lw
#घोषणा REG_SUBU	subu
#घोषणा REG_ADDU	addu
#पूर्ण_अगर
#अगर (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64)
#घोषणा REG_S		sd
#घोषणा REG_L		ld
#घोषणा REG_SUBU	dsubu
#घोषणा REG_ADDU	daddu
#पूर्ण_अगर

/*
 * How to add/sub/load/store/shअगरt C पूर्णांक variables.
 */
#अगर (_MIPS_SZINT == 32)
#घोषणा INT_ADD		add
#घोषणा INT_ADDU	addu
#घोषणा INT_ADDI	addi
#घोषणा INT_ADDIU	addiu
#घोषणा INT_SUB		sub
#घोषणा INT_SUBU	subu
#घोषणा INT_L		lw
#घोषणा INT_S		sw
#घोषणा INT_SLL		sll
#घोषणा INT_SLLV	sllv
#घोषणा INT_SRL		srl
#घोषणा INT_SRLV	srlv
#घोषणा INT_SRA		sra
#घोषणा INT_SRAV	srav
#पूर्ण_अगर

#अगर (_MIPS_SZINT == 64)
#घोषणा INT_ADD		dadd
#घोषणा INT_ADDU	daddu
#घोषणा INT_ADDI	daddi
#घोषणा INT_ADDIU	daddiu
#घोषणा INT_SUB		dsub
#घोषणा INT_SUBU	dsubu
#घोषणा INT_L		ld
#घोषणा INT_S		sd
#घोषणा INT_SLL		dsll
#घोषणा INT_SLLV	dsllv
#घोषणा INT_SRL		dsrl
#घोषणा INT_SRLV	dsrlv
#घोषणा INT_SRA		dsra
#घोषणा INT_SRAV	dsrav
#पूर्ण_अगर

/*
 * How to add/sub/load/store/shअगरt C दीर्घ variables.
 */
#अगर (_MIPS_SZLONG == 32)
#घोषणा LONG_ADD	add
#घोषणा LONG_ADDU	addu
#घोषणा LONG_ADDI	addi
#घोषणा LONG_ADDIU	addiu
#घोषणा LONG_SUB	sub
#घोषणा LONG_SUBU	subu
#घोषणा LONG_L		lw
#घोषणा LONG_S		sw
#घोषणा LONG_SP		swp
#घोषणा LONG_SLL	sll
#घोषणा LONG_SLLV	sllv
#घोषणा LONG_SRL	srl
#घोषणा LONG_SRLV	srlv
#घोषणा LONG_SRA	sra
#घोषणा LONG_SRAV	srav

#अगर_घोषित __ASSEMBLY__
#घोषणा LONG		.word
#पूर्ण_अगर
#घोषणा LONGSIZE	4
#घोषणा LONGMASK	3
#घोषणा LONGLOG		2
#पूर्ण_अगर

#अगर (_MIPS_SZLONG == 64)
#घोषणा LONG_ADD	dadd
#घोषणा LONG_ADDU	daddu
#घोषणा LONG_ADDI	daddi
#घोषणा LONG_ADDIU	daddiu
#घोषणा LONG_SUB	dsub
#घोषणा LONG_SUBU	dsubu
#घोषणा LONG_L		ld
#घोषणा LONG_S		sd
#घोषणा LONG_SP		sdp
#घोषणा LONG_SLL	dsll
#घोषणा LONG_SLLV	dsllv
#घोषणा LONG_SRL	dsrl
#घोषणा LONG_SRLV	dsrlv
#घोषणा LONG_SRA	dsra
#घोषणा LONG_SRAV	dsrav

#अगर_घोषित __ASSEMBLY__
#घोषणा LONG		.dword
#पूर्ण_अगर
#घोषणा LONGSIZE	8
#घोषणा LONGMASK	7
#घोषणा LONGLOG		3
#पूर्ण_अगर

/*
 * How to add/sub/load/store/shअगरt poपूर्णांकers.
 */
#अगर (_MIPS_SZPTR == 32)
#घोषणा PTR_ADD		add
#घोषणा PTR_ADDU	addu
#घोषणा PTR_ADDI	addi
#घोषणा PTR_ADDIU	addiu
#घोषणा PTR_SUB		sub
#घोषणा PTR_SUBU	subu
#घोषणा PTR_L		lw
#घोषणा PTR_S		sw
#घोषणा PTR_LA		la
#घोषणा PTR_LI		li
#घोषणा PTR_SLL		sll
#घोषणा PTR_SLLV	sllv
#घोषणा PTR_SRL		srl
#घोषणा PTR_SRLV	srlv
#घोषणा PTR_SRA		sra
#घोषणा PTR_SRAV	srav

#घोषणा PTR_SCALESHIFT	2

#घोषणा PTR		.word
#घोषणा PTRSIZE		4
#घोषणा PTRLOG		2
#पूर्ण_अगर

#अगर (_MIPS_SZPTR == 64)
#घोषणा PTR_ADD		dadd
#घोषणा PTR_ADDU	daddu
#घोषणा PTR_ADDI	daddi
#घोषणा PTR_ADDIU	daddiu
#घोषणा PTR_SUB		dsub
#घोषणा PTR_SUBU	dsubu
#घोषणा PTR_L		ld
#घोषणा PTR_S		sd
#घोषणा PTR_LA		dla
#घोषणा PTR_LI		dli
#घोषणा PTR_SLL		dsll
#घोषणा PTR_SLLV	dsllv
#घोषणा PTR_SRL		dsrl
#घोषणा PTR_SRLV	dsrlv
#घोषणा PTR_SRA		dsra
#घोषणा PTR_SRAV	dsrav

#घोषणा PTR_SCALESHIFT	3

#घोषणा PTR		.dword
#घोषणा PTRSIZE		8
#घोषणा PTRLOG		3
#पूर्ण_अगर

/*
 * Some cp0 रेजिस्टरs were extended to 64bit क्रम MIPS III.
 */
#अगर (_MIPS_SIM == _MIPS_SIM_ABI32)
#घोषणा MFC0		mfc0
#घोषणा MTC0		mtc0
#पूर्ण_अगर
#अगर (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64)
#घोषणा MFC0		dmfc0
#घोषणा MTC0		dmtc0
#पूर्ण_अगर

#घोषणा SSNOP		sll zero, zero, 1

#अगर_घोषित CONFIG_SGI_IP28
/* Inhibit speculative stores to अस्थिर (e.g.DMA) or invalid addresses. */
#समावेश <यंत्र/cacheops.h>
#घोषणा R10KCBARRIER(addr)  cache   Cache_Barrier, addr;
#अन्यथा
#घोषणा R10KCBARRIER(addr)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ASM_H */
