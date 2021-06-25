<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh3/freq.h
 *
 * Copyright (C) 2002, 2003 Paul Mundt
 */
#अगर_अघोषित __ASM_CPU_SH3_FREQ_H
#घोषणा __ASM_CPU_SH3_FREQ_H

#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7712
#घोषणा FRQCR			0xA415FF80
#अन्यथा
#घोषणा FRQCR			0xffffff80
#पूर्ण_अगर

#घोषणा MIN_DIVISOR_NR		0
#घोषणा MAX_DIVISOR_NR		4

#घोषणा FRQCR_CKOEN	0x0100
#घोषणा FRQCR_PLLEN	0x0080
#घोषणा FRQCR_PSTBY	0x0040

#पूर्ण_अगर /* __ASM_CPU_SH3_FREQ_H */

