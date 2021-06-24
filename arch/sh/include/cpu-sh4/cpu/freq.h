<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh4/freq.h
 *
 * Copyright (C) 2002, 2003 Paul Mundt
 */
#अगर_अघोषित __ASM_CPU_SH4_FREQ_H
#घोषणा __ASM_CPU_SH4_FREQ_H

#अगर defined(CONFIG_CPU_SUBTYPE_SH7722) || \
    defined(CONFIG_CPU_SUBTYPE_SH7723) || \
    defined(CONFIG_CPU_SUBTYPE_SH7343) || \
    defined(CONFIG_CPU_SUBTYPE_SH7366)
#घोषणा FRQCR		        0xa4150000
#घोषणा VCLKCR			0xa4150004
#घोषणा SCLKACR			0xa4150008
#घोषणा SCLKBCR			0xa415000c
#घोषणा IrDACLKCR		0xa4150010
#घोषणा MSTPCR0			0xa4150030
#घोषणा MSTPCR1			0xa4150034
#घोषणा MSTPCR2			0xa4150038
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7757)
#घोषणा	FRQCR			0xffc80000
#घोषणा	OSCCR			0xffc80018
#घोषणा	PLLCR			0xffc80024
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7763) || \
      defined(CONFIG_CPU_SUBTYPE_SH7780)
#घोषणा	FRQCR			0xffc80000
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7724)
#घोषणा FRQCRA			0xa4150000
#घोषणा FRQCRB			0xa4150004
#घोषणा VCLKCR			0xa4150048

#घोषणा FCLKACR			0xa4150008
#घोषणा FCLKBCR			0xa415000c
#घोषणा FRQCR			FRQCRA
#घोषणा SCLKACR			FCLKACR
#घोषणा SCLKBCR			FCLKBCR
#घोषणा FCLKACR			0xa4150008
#घोषणा FCLKBCR			0xa415000c
#घोषणा IrDACLKCR		0xa4150018

#घोषणा MSTPCR0			0xa4150030
#घोषणा MSTPCR1			0xa4150034
#घोषणा MSTPCR2			0xa4150038

#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7734)
#घोषणा FRQCR0			0xffc80000
#घोषणा FRQCR2			0xffc80008
#घोषणा FRQMR1			0xffc80014
#घोषणा FRQMR2			0xffc80018
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7785)
#घोषणा FRQCR0			0xffc80000
#घोषणा FRQCR1			0xffc80004
#घोषणा FRQMR1			0xffc80014
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7786)
#घोषणा FRQCR0			0xffc40000
#घोषणा FRQCR1			0xffc40004
#घोषणा FRQMR1			0xffc40014
#या_अगर defined(CONFIG_CPU_SUBTYPE_SHX3)
#घोषणा FRQCR0			0xffc00000
#घोषणा FRQCR1			0xffc00004
#घोषणा FRQMR1			0xffc00014
#अन्यथा
#घोषणा FRQCR			0xffc00000
#घोषणा FRQCR_PSTBY		0x0200
#घोषणा FRQCR_PLLEN		0x0400
#घोषणा FRQCR_CKOEN		0x0800
#पूर्ण_अगर
#घोषणा MIN_DIVISOR_NR		0
#घोषणा MAX_DIVISOR_NR		3

#पूर्ण_अगर /* __ASM_CPU_SH4_FREQ_H */

