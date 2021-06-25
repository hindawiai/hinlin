<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2001, 2002, MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 * Copyright (c) 2003  Maciej W. Rozycki
 *
 * include/यंत्र-mips/समय.स
 *     header file क्रम the new style समय.c file and समय services.
 */
#अगर_अघोषित _ASM_TIME_H
#घोषणा _ASM_TIME_H

#समावेश <linux/rtc.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>

बाह्य spinlock_t rtc_lock;

/*
 * board specअगरic routines required by समय_init().
 */
बाह्य व्योम plat_समय_init(व्योम);

/*
 * mips_hpt_frequency - must be set अगर you पूर्णांकend to use an R4k-compatible
 * counter as a समयr पूर्णांकerrupt source.
 */
बाह्य अचिन्हित पूर्णांक mips_hpt_frequency;

/*
 * The perक्रमmance counter IRQ on MIPS is a बंद relative to the समयr IRQ
 * so it lives here.
 */
बाह्य पूर्णांक (*perf_irq)(व्योम);
बाह्य पूर्णांक __weak get_c0_perfcount_पूर्णांक(व्योम);

/*
 * Initialize the calling CPU's compare पूर्णांकerrupt as घड़ीevent device
 */
बाह्य अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम);
बाह्य पूर्णांक r4k_घड़ीevent_init(व्योम);

अटल अंतरभूत पूर्णांक mips_घड़ीevent_init(व्योम)
अणु
#अगर_घोषित CONFIG_CEVT_R4K
	वापस r4k_घड़ीevent_init();
#अन्यथा
	वापस -ENXIO;
#पूर्ण_अगर
पूर्ण

/*
 * Initialize the count रेजिस्टर as a घड़ीsource
 */
बाह्य पूर्णांक init_r4k_घड़ीsource(व्योम);

अटल अंतरभूत पूर्णांक init_mips_घड़ीsource(व्योम)
अणु
#अगर_घोषित CONFIG_CSRC_R4K
	वापस init_r4k_घड़ीsource();
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम घड़ीevent_set_घड़ी(काष्ठा घड़ी_event_device *cd,
					अचिन्हित पूर्णांक घड़ी)
अणु
	घड़ीevents_calc_mult_shअगरt(cd, घड़ी, 4);
पूर्ण

#पूर्ण_अगर /* _ASM_TIME_H */
