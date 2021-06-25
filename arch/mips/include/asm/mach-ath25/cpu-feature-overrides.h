<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Atheros AR231x/AR531x SoC specअगरic CPU feature overrides
 *
 *  Copyright (C) 2008 Gabor Juhos <juhosg@खोलोwrt.org>
 *
 *  This file was derived from: include/यंत्र-mips/cpu-features.h
 *	Copyright (C) 2003, 2004 Ralf Baechle
 *	Copyright (C) 2004 Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MACH_ATH25_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_ATH25_CPU_FEATURE_OVERRIDES_H

/*
 * The Atheros AR531x/AR231x SoCs have MIPS 4Kc/4KEc core.
 */
#घोषणा cpu_has_tlb			1
#घोषणा cpu_has_4kex			1
#घोषणा cpu_has_3k_cache		0
#घोषणा cpu_has_4k_cache		1
#घोषणा cpu_has_tx39_cache		0
#घोषणा cpu_has_sb1_cache		0
#घोषणा cpu_has_fpu			0
#घोषणा cpu_has_32fpr			0
#घोषणा cpu_has_counter			1
#घोषणा cpu_has_ejtag			1

#अगर !defined(CONFIG_SOC_AR5312)
#  define cpu_has_llsc			1
#अन्यथा
/*
 * The MIPS 4Kc V0.9 core in the AR5312/AR2312 have problems with the
 * ll/sc inकाष्ठाions.
 */
#  define cpu_has_llsc			0
#पूर्ण_अगर

#घोषणा cpu_has_mips16			0
#घोषणा cpu_has_mips16e2		0
#घोषणा cpu_has_mdmx			0
#घोषणा cpu_has_mips3d			0
#घोषणा cpu_has_smarपंचांगips		0

#घोषणा cpu_has_mips32r1		1

#अगर !defined(CONFIG_SOC_AR5312)
#  define cpu_has_mips32r2		1
#पूर्ण_अगर

#घोषणा cpu_has_mips64r1		0
#घोषणा cpu_has_mips64r2		0

#घोषणा cpu_has_dsp			0
#घोषणा cpu_has_mipsmt			0

#घोषणा cpu_has_64bits			0
#घोषणा cpu_has_64bit_zero_reg		0
#घोषणा cpu_has_64bit_gp_regs		0

#पूर्ण_अगर /* __ASM_MACH_ATH25_CPU_FEATURE_OVERRIDES_H */
