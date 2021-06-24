<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2006, 07 Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित __ASM_COBALT_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_COBALT_CPU_FEATURE_OVERRIDES_H


#घोषणा cpu_has_tlb		1
#घोषणा cpu_has_4kex		1
#घोषणा cpu_has_3k_cache	0
#घोषणा cpu_has_4k_cache	1
#घोषणा cpu_has_tx39_cache	0
#घोषणा cpu_has_32fpr		1
#घोषणा cpu_has_counter		1
#घोषणा cpu_has_watch		0
#घोषणा cpu_has_भागec		1
#घोषणा cpu_has_vce		0
#घोषणा cpu_has_cache_cdex_p	0
#घोषणा cpu_has_cache_cdex_s	0
#घोषणा cpu_has_prefetch	0
#घोषणा cpu_has_mcheck		0
#घोषणा cpu_has_ejtag		0

#घोषणा cpu_has_inclusive_pcaches	0
#घोषणा cpu_dcache_line_size()	32
#घोषणा cpu_icache_line_size()	32
#घोषणा cpu_scache_line_size()	0

#अगर_घोषित CONFIG_64BIT
#घोषणा cpu_has_llsc		0
#अन्यथा
#घोषणा cpu_has_llsc		1
#पूर्ण_अगर

#घोषणा cpu_has_mips16		0
#घोषणा cpu_has_mips16e2	0
#घोषणा cpu_has_mdmx		0
#घोषणा cpu_has_mips3d		0
#घोषणा cpu_has_smarपंचांगips	0
#घोषणा cpu_has_vtag_icache	0
#घोषणा cpu_has_ic_fills_f_dc	0
#घोषणा cpu_icache_snoops_remote_store	0
#घोषणा cpu_has_dsp		0
#घोषणा cpu_has_dsp2		0
#घोषणा cpu_has_mipsmt		0
#घोषणा cpu_has_userlocal	0

#घोषणा cpu_has_mips32r1	0
#घोषणा cpu_has_mips32r2	0
#घोषणा cpu_has_mips64r1	0
#घोषणा cpu_has_mips64r2	0

#पूर्ण_अगर /* __ASM_COBALT_CPU_FEATURE_OVERRIDES_H */
