<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 Wu Zhangjin <wuzhangjin@gmail.com>
 * Copyright (C) 2009 Philippe Vachon <philippe@cowpig.ca>
 * Copyright (C) 2009 Zhang Le <r0bertz@gentoo.org>
 *
 * reference: /proc/cpuinfo,
 *	arch/mips/kernel/cpu-probe.c(cpu_probe_legacy),
 *	arch/mips/kernel/proc.c(show_cpuinfo),
 *	loongson2f user manual.
 */

#अगर_अघोषित __ASM_MACH_LOONGSON2EF_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_LOONGSON2EF_CPU_FEATURE_OVERRIDES_H

#घोषणा cpu_has_32fpr		1
#घोषणा cpu_has_3k_cache	0
#घोषणा cpu_has_4k_cache	1
#घोषणा cpu_has_4kex		1
#घोषणा cpu_has_64bits		1
#घोषणा cpu_has_cache_cdex_p	0
#घोषणा cpu_has_cache_cdex_s	0
#घोषणा cpu_has_counter		1
#घोषणा cpu_has_dc_aliases	(PAGE_SIZE < 0x4000)
#घोषणा cpu_has_भागec		0
#घोषणा cpu_has_ejtag		0
#घोषणा cpu_has_inclusive_pcaches	1
#घोषणा cpu_has_llsc		1
#घोषणा cpu_has_mcheck		0
#घोषणा cpu_has_mdmx		0
#घोषणा cpu_has_mips16		0
#घोषणा cpu_has_mips16e2	0
#घोषणा cpu_has_mips3d		0
#घोषणा cpu_has_mipsmt		0
#घोषणा cpu_has_smarपंचांगips	0
#घोषणा cpu_has_tlb		1
#घोषणा cpu_has_tx39_cache	0
#घोषणा cpu_has_vce		0
#घोषणा cpu_has_veic		0
#घोषणा cpu_has_vपूर्णांक		0
#घोषणा cpu_has_vtag_icache	0
#घोषणा cpu_has_watch		1

#पूर्ण_अगर /* __ASM_MACH_LOONGSON64_CPU_FEATURE_OVERRIDES_H */
