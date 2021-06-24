<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 Ilya A. Volynets-Evenbakh
 * Copyright (C) 2005, 07 Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित __ASM_MACH_IP32_CPU_FEATURE_OVERRIDES_H
#घोषणा __ASM_MACH_IP32_CPU_FEATURE_OVERRIDES_H


/*
 * R5000 has an पूर्णांकeresting "restriction":  ll(d)/sc(d)
 * inकाष्ठाions to XKPHYS region simply करो uncached bus
 * requests. This अवरोधs all the atomic bitops functions.
 * so, क्रम 64bit IP32 kernel we just करोn't use ll/sc.
 * This करोes not affect luserland.
 */
#अगर (defined(CONFIG_CPU_R5000) || defined(CONFIG_CPU_NEVADA)) && defined(CONFIG_64BIT)
#घोषणा cpu_has_llsc		0
#अन्यथा
#घोषणा cpu_has_llsc		1
#पूर्ण_अगर

/* Settings which are common क्रम all ip32 CPUs */
#घोषणा cpu_has_tlb		1
#घोषणा cpu_has_4kex		1
#घोषणा cpu_has_32fpr		1
#घोषणा cpu_has_counter		1
#घोषणा cpu_has_mips16		0
#घोषणा cpu_has_mips16e2	0
#घोषणा cpu_has_vce		0
#घोषणा cpu_has_cache_cdex_s	0
#घोषणा cpu_has_mcheck		0
#घोषणा cpu_has_ejtag		0
#घोषणा cpu_has_vtag_icache	0
#घोषणा cpu_has_ic_fills_f_dc	0
#घोषणा cpu_has_dsp		0
#घोषणा cpu_has_dsp2		0
#घोषणा cpu_has_4k_cache	1
#घोषणा cpu_has_mipsmt		0
#घोषणा cpu_has_userlocal	0


#घोषणा cpu_has_mips32r1	0
#घोषणा cpu_has_mips32r2	0
#घोषणा cpu_has_mips64r1	0
#घोषणा cpu_has_mips64r2	0

#पूर्ण_अगर /* __ASM_MACH_IP32_CPU_FEATURE_OVERRIDES_H */
