<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IP30/Octane cpu-features overrides.
 *
 * Copyright (C) 2003 Ralf Baechle <ralf@linux-mips.org>
 *		 2004-2007 Stanislaw Skowronek <skylark@unaligned.org>
 *		 2009 Johannes Dickgreber <tanzy@gmx.de>
 *		 2015 Joshua Kinard <kumba@gentoo.org>
 *
 */
#अगर_अघोषित __ASM_MACH_IP30_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_IP30_CPU_FEATURE_OVERRIDES_H

#समावेश <यंत्र/cpu.h>

/*
 * IP30 only supports R1[024]000 processors, all using the same config
 */
#घोषणा cpu_has_tlb			1
#घोषणा cpu_has_tlbinv			0
#घोषणा cpu_has_segments		0
#घोषणा cpu_has_eva			0
#घोषणा cpu_has_htw			0
#घोषणा cpu_has_rixiex			0
#घोषणा cpu_has_maar			0
#घोषणा cpu_has_rw_llb			0
#घोषणा cpu_has_3kex			0
#घोषणा cpu_has_4kex			1
#घोषणा cpu_has_3k_cache		0
#घोषणा cpu_has_4k_cache		1
#घोषणा cpu_has_tx39_cache		0
#घोषणा cpu_has_fpu			1
#घोषणा cpu_has_nofpuex			0
#घोषणा cpu_has_32fpr			1
#घोषणा cpu_has_counter			1
#घोषणा cpu_has_watch			1
#घोषणा cpu_has_64bits			1
#घोषणा cpu_has_भागec			0
#घोषणा cpu_has_vce			0
#घोषणा cpu_has_cache_cdex_p		0
#घोषणा cpu_has_cache_cdex_s		0
#घोषणा cpu_has_prefetch		1
#घोषणा cpu_has_mcheck			0
#घोषणा cpu_has_ejtag			0
#घोषणा cpu_has_llsc			1
#घोषणा cpu_has_mips16			0
#घोषणा cpu_has_mdmx			0
#घोषणा cpu_has_mips3d			0
#घोषणा cpu_has_smarपंचांगips		0
#घोषणा cpu_has_rixi			0
#घोषणा cpu_has_xpa			0
#घोषणा cpu_has_vtag_icache		0
#घोषणा cpu_has_dc_aliases		0
#घोषणा cpu_has_ic_fills_f_dc		0

#घोषणा cpu_icache_snoops_remote_store	1

#घोषणा cpu_has_mips32r1		0
#घोषणा cpu_has_mips32r2		0
#घोषणा cpu_has_mips64r1		0
#घोषणा cpu_has_mips64r2		0
#घोषणा cpu_has_mips32r6		0
#घोषणा cpu_has_mips64r6		0

#घोषणा cpu_has_dsp			0
#घोषणा cpu_has_dsp2			0
#घोषणा cpu_has_mipsmt			0
#घोषणा cpu_has_userlocal		0
#घोषणा cpu_has_inclusive_pcaches	1
#घोषणा cpu_has_perf_cntr_पूर्णांकr_bit	0
#घोषणा cpu_has_vz			0
#घोषणा cpu_has_fre			0
#घोषणा cpu_has_cdmm			0

#घोषणा cpu_dcache_line_size()		32
#घोषणा cpu_icache_line_size()		64
#घोषणा cpu_scache_line_size()		128

#पूर्ण_अगर /* __ASM_MACH_IP30_CPU_FEATURE_OVERRIDES_H */

