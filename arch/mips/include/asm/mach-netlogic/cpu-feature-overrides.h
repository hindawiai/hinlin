<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011 Netlogic Microप्रणालीs
 * Copyright (C) 2003 Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_NETLOGIC_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_NETLOGIC_CPU_FEATURE_OVERRIDES_H

#घोषणा cpu_has_4kex		1
#घोषणा cpu_has_4k_cache	1
#घोषणा cpu_has_watch		1
#घोषणा cpu_has_mips16		0
#घोषणा cpu_has_mips16e2	0
#घोषणा cpu_has_counter		1
#घोषणा cpu_has_भागec		1
#घोषणा cpu_has_vce		0
#घोषणा cpu_has_cache_cdex_p	0
#घोषणा cpu_has_cache_cdex_s	0
#घोषणा cpu_has_prefetch	1
#घोषणा cpu_has_mcheck		1
#घोषणा cpu_has_ejtag		1

#घोषणा cpu_has_llsc		1
#घोषणा cpu_has_vtag_icache	0
#घोषणा cpu_has_ic_fills_f_dc	1
#घोषणा cpu_has_dsp		0
#घोषणा cpu_has_dsp2		0
#घोषणा cpu_has_mipsmt		0
#घोषणा cpu_icache_snoops_remote_store	1

#घोषणा cpu_has_64bits		1

#घोषणा cpu_has_mips32r1	1
#घोषणा cpu_has_mips64r1	1

#घोषणा cpu_has_inclusive_pcaches	0

#घोषणा cpu_dcache_line_size()	32
#घोषणा cpu_icache_line_size()	32

#अगर defined(CONFIG_CPU_XLR)
#घोषणा cpu_has_userlocal	0
#घोषणा cpu_has_dc_aliases	0
#घोषणा cpu_has_mips32r2	0
#घोषणा cpu_has_mips64r2	0
#या_अगर defined(CONFIG_CPU_XLP)
#घोषणा cpu_has_userlocal	1
#घोषणा cpu_has_mips32r2	1
#घोषणा cpu_has_mips64r2	1
#अन्यथा
#त्रुटि "Unknown Netlogic CPU"
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_NETLOGIC_CPU_FEATURE_OVERRIDES_H */
