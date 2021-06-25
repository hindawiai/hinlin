<शैली गुरु>
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_MACH_PIC32_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_PIC32_CPU_FEATURE_OVERRIDES_H

/*
 * CPU feature overrides क्रम PIC32 boards
 */
#अगर_घोषित CONFIG_CPU_MIPS32
#घोषणा cpu_has_vपूर्णांक		1
#घोषणा cpu_has_veic		0
#घोषणा cpu_has_tlb		1
#घोषणा cpu_has_4kex		1
#घोषणा cpu_has_4k_cache	1
#घोषणा cpu_has_fpu		0
#घोषणा cpu_has_counter		1
#घोषणा cpu_has_llsc		1
#घोषणा cpu_has_nofpuex		0
#घोषणा cpu_icache_snoops_remote_store 1
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_MIPS64
#त्रुटि This platक्रमm करोes not support 64bit.
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_PIC32_CPU_FEATURE_OVERRIDES_H */
