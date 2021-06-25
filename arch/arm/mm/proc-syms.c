<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/proc-syms.c
 *
 *  Copyright (C) 2000-2002 Russell King
 */
#समावेश <linux/module.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/page.h>

#अगर_अघोषित MULTI_CPU
EXPORT_SYMBOL(cpu_dcache_clean_area);
#अगर_घोषित CONFIG_MMU
EXPORT_SYMBOL(cpu_set_pte_ext);
#पूर्ण_अगर
#अन्यथा
EXPORT_SYMBOL(processor);
#पूर्ण_अगर

#अगर_अघोषित MULTI_CACHE
EXPORT_SYMBOL(__cpuc_flush_kern_all);
EXPORT_SYMBOL(__cpuc_flush_user_all);
EXPORT_SYMBOL(__cpuc_flush_user_range);
EXPORT_SYMBOL(__cpuc_coherent_kern_range);
EXPORT_SYMBOL(__cpuc_flush_dcache_area);
#अन्यथा
EXPORT_SYMBOL(cpu_cache);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
#अगर_अघोषित MULTI_USER
EXPORT_SYMBOL(__cpu_clear_user_highpage);
EXPORT_SYMBOL(__cpu_copy_user_highpage);
#अन्यथा
EXPORT_SYMBOL(cpu_user);
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * No module should need to touch the TLB (and currently
 * no modules करो.  We export this क्रम "loadkernel" support
 * (booting a new kernel from within a running kernel.)
 */
#अगर_घोषित MULTI_TLB
EXPORT_SYMBOL(cpu_tlb);
#पूर्ण_अगर
