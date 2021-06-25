<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	CPU feature overrides क्रम DECstation प्रणालीs.  Two variations
 *	are generally applicable.
 *
 *	Copyright (C) 2013  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MACH_DEC_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_DEC_CPU_FEATURE_OVERRIDES_H

/* Generic ones first.  */
#घोषणा cpu_has_tlb			1
#घोषणा cpu_has_tlbinv			0
#घोषणा cpu_has_segments		0
#घोषणा cpu_has_eva			0
#घोषणा cpu_has_htw			0
#घोषणा cpu_has_rixiex			0
#घोषणा cpu_has_maar			0
#घोषणा cpu_has_rw_llb			0
#घोषणा cpu_has_tx39_cache		0
#घोषणा cpu_has_भागec			0
#घोषणा cpu_has_prefetch		0
#घोषणा cpu_has_mcheck			0
#घोषणा cpu_has_ejtag			0
#घोषणा cpu_has_mips16			0
#घोषणा cpu_has_mips16e2		0
#घोषणा cpu_has_mdmx			0
#घोषणा cpu_has_mips3d			0
#घोषणा cpu_has_smarपंचांगips		0
#घोषणा cpu_has_rixi			0
#घोषणा cpu_has_xpa			0
#घोषणा cpu_has_vtag_icache		0
#घोषणा cpu_has_ic_fills_f_dc		0
#घोषणा cpu_has_pindexed_dcache		0
#घोषणा cpu_icache_snoops_remote_store	1
#घोषणा cpu_has_mips_4			0
#घोषणा cpu_has_mips_5			0
#घोषणा cpu_has_mips32r1		0
#घोषणा cpu_has_mips32r2		0
#घोषणा cpu_has_mips64r1		0
#घोषणा cpu_has_mips64r2		0
#घोषणा cpu_has_dsp			0
#घोषणा cpu_has_dsp2			0
#घोषणा cpu_has_mipsmt			0
#घोषणा cpu_has_userlocal		0
#घोषणा cpu_has_perf_cntr_पूर्णांकr_bit	0
#घोषणा cpu_has_vz			0
#घोषणा cpu_has_fre			0
#घोषणा cpu_has_cdmm			0

/* R3k-specअगरic ones.  */
#अगर_घोषित CONFIG_CPU_R3000
#घोषणा cpu_has_3kex			1
#घोषणा cpu_has_4kex			0
#घोषणा cpu_has_3k_cache		1
#घोषणा cpu_has_4k_cache		0
#घोषणा cpu_has_32fpr			0
#घोषणा cpu_has_counter			0
#घोषणा cpu_has_watch			0
#घोषणा cpu_has_vce			0
#घोषणा cpu_has_cache_cdex_p		0
#घोषणा cpu_has_cache_cdex_s		0
#घोषणा cpu_has_llsc			0
#घोषणा cpu_has_dc_aliases		0
#घोषणा cpu_has_mips_2			0
#घोषणा cpu_has_mips_3			0
#घोषणा cpu_has_nofpuex			1
#घोषणा cpu_has_inclusive_pcaches	0
#घोषणा cpu_dcache_line_size()		4
#घोषणा cpu_icache_line_size()		4
#घोषणा cpu_scache_line_size()		0
#पूर्ण_अगर /* CONFIG_CPU_R3000 */

/* R4k-specअगरic ones.  */
#अगर_घोषित CONFIG_CPU_R4X00
#घोषणा cpu_has_3kex			0
#घोषणा cpu_has_4kex			1
#घोषणा cpu_has_3k_cache		0
#घोषणा cpu_has_4k_cache		1
#घोषणा cpu_has_32fpr			1
#घोषणा cpu_has_counter			1
#घोषणा cpu_has_watch			1
#घोषणा cpu_has_vce			1
#घोषणा cpu_has_cache_cdex_p		1
#घोषणा cpu_has_cache_cdex_s		1
#घोषणा cpu_has_llsc			1
#घोषणा cpu_has_dc_aliases		(PAGE_SIZE < 0x4000)
#घोषणा cpu_has_mips_2			1
#घोषणा cpu_has_mips_3			1
#घोषणा cpu_has_nofpuex			0
#घोषणा cpu_has_inclusive_pcaches	1
#घोषणा cpu_dcache_line_size()		16
#घोषणा cpu_icache_line_size()		16
#घोषणा cpu_scache_line_size()		32
#पूर्ण_अगर /* CONFIG_CPU_R4X00 */

#पूर्ण_अगर /* __ASM_MACH_DEC_CPU_FEATURE_OVERRIDES_H */
