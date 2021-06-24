<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 07 Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_IP22_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_IP22_CPU_FEATURE_OVERRIDES_H

#समावेश <यंत्र/cpu.h>

/*
 * IP22 with a variety of processors so we can't use शेषs क्रम everything.
 */
#घोषणा cpu_has_tlb		1
#घोषणा cpu_has_4kex		1
#घोषणा cpu_has_4k_cache	1
#घोषणा cpu_has_32fpr		1
#घोषणा cpu_has_counter		1
#घोषणा cpu_has_mips16		0
#घोषणा cpu_has_mips16e2	0
#घोषणा cpu_has_भागec		0
#घोषणा cpu_has_cache_cdex_p	1
#घोषणा cpu_has_prefetch	0
#घोषणा cpu_has_mcheck		0
#घोषणा cpu_has_ejtag		0

#घोषणा cpu_has_llsc		1
#घोषणा cpu_has_vtag_icache	0		/* Needs to change क्रम R8000 */
#घोषणा cpu_has_dc_aliases	(PAGE_SIZE < 0x4000)
#घोषणा cpu_has_ic_fills_f_dc	0

#घोषणा cpu_has_dsp		0
#घोषणा cpu_has_dsp2		0
#घोषणा cpu_has_mipsmt		0
#घोषणा cpu_has_userlocal	0

#घोषणा cpu_has_nofpuex		0
#घोषणा cpu_has_64bits		1

#घोषणा cpu_has_mips_2		1
#घोषणा cpu_has_mips_3		1
#घोषणा cpu_has_mips_5		0

#घोषणा cpu_has_mips32r1	0
#घोषणा cpu_has_mips32r2	0
#घोषणा cpu_has_mips64r1	0
#घोषणा cpu_has_mips64r2	0

#पूर्ण_अगर /* __ASM_MACH_IP22_CPU_FEATURE_OVERRIDES_H */
