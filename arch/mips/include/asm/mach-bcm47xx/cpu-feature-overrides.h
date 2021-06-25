<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_BCM47XX_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_BCM47XX_CPU_FEATURE_OVERRIDES_H

#घोषणा cpu_has_tlb			1
#घोषणा cpu_has_4kex			1
#घोषणा cpu_has_3k_cache		0
#घोषणा cpu_has_4k_cache		1
#घोषणा cpu_has_tx39_cache		0
#घोषणा cpu_has_fpu			0
#घोषणा cpu_has_32fpr			0
#घोषणा cpu_has_counter			1
#अगर defined(CONFIG_BCM47XX_BCMA) && !defined(CONFIG_BCM47XX_SSB)
#घोषणा cpu_has_watch			1
#या_अगर defined(CONFIG_BCM47XX_SSB) && !defined(CONFIG_BCM47XX_BCMA)
#घोषणा cpu_has_watch			0
#पूर्ण_अगर
#घोषणा cpu_has_भागec			1
#घोषणा cpu_has_vce			0
#घोषणा cpu_has_cache_cdex_p		0
#घोषणा cpu_has_cache_cdex_s		0
#घोषणा cpu_has_prefetch		1
#घोषणा cpu_has_mcheck			1
#घोषणा cpu_has_ejtag			1
#घोषणा cpu_has_llsc			1

/* cpu_has_mips16 */
#घोषणा cpu_has_mdmx			0
#घोषणा cpu_has_mips3d			0
#घोषणा cpu_has_rixi			0
#घोषणा cpu_has_mmips			0
#घोषणा cpu_has_smarपंचांगips		0
#घोषणा cpu_has_vtag_icache		0
/* cpu_has_dc_aliases */
#घोषणा cpu_has_ic_fills_f_dc		0
#घोषणा cpu_has_pindexed_dcache		0
#घोषणा cpu_icache_snoops_remote_store	0

#घोषणा cpu_has_mips_2			1
#घोषणा cpu_has_mips_3			0
#घोषणा cpu_has_mips32r1		1
#अगर defined(CONFIG_BCM47XX_BCMA) && !defined(CONFIG_BCM47XX_SSB)
#घोषणा cpu_has_mips32r2		1
#या_अगर defined(CONFIG_BCM47XX_SSB) && !defined(CONFIG_BCM47XX_BCMA)
#घोषणा cpu_has_mips32r2		0
#पूर्ण_अगर
#घोषणा cpu_has_mips64r1		0
#घोषणा cpu_has_mips64r2		0

#अगर defined(CONFIG_BCM47XX_BCMA) && !defined(CONFIG_BCM47XX_SSB)
#घोषणा cpu_has_dsp			1
#घोषणा cpu_has_dsp2			1
#या_अगर defined(CONFIG_BCM47XX_SSB) && !defined(CONFIG_BCM47XX_BCMA)
#घोषणा cpu_has_dsp			0
#घोषणा cpu_has_dsp2			0
#पूर्ण_अगर
#घोषणा cpu_has_mipsmt			0
/* cpu_has_userlocal */

#घोषणा cpu_has_nofpuex			0
#घोषणा cpu_has_64bits			0
#घोषणा cpu_has_64bit_zero_reg		0
#अगर defined(CONFIG_BCM47XX_BCMA) && !defined(CONFIG_BCM47XX_SSB)
#घोषणा cpu_has_vपूर्णांक			1
#या_अगर defined(CONFIG_BCM47XX_SSB) && !defined(CONFIG_BCM47XX_BCMA)
#घोषणा cpu_has_vपूर्णांक			0
#पूर्ण_अगर
#घोषणा cpu_has_veic			0
#घोषणा cpu_has_inclusive_pcaches	0

#अगर defined(CONFIG_BCM47XX_BCMA) && !defined(CONFIG_BCM47XX_SSB)
#घोषणा cpu_dcache_line_size()		32
#घोषणा cpu_icache_line_size()		32
#घोषणा cpu_has_perf_cntr_पूर्णांकr_bit	1
#या_अगर defined(CONFIG_BCM47XX_SSB) && !defined(CONFIG_BCM47XX_BCMA)
#घोषणा cpu_dcache_line_size()		16
#घोषणा cpu_icache_line_size()		16
#घोषणा cpu_has_perf_cntr_पूर्णांकr_bit	0
#पूर्ण_अगर
#घोषणा cpu_scache_line_size()		0
#घोषणा cpu_has_vz			0

#पूर्ण_अगर /* __ASM_MACH_BCM47XX_CPU_FEATURE_OVERRIDES_H */
