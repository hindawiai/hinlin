<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Definitions क्रम the घड़ीsource provided by the Hyper-V
 * hypervisor to guest VMs, as described in the Hyper-V Top
 * Level Functional Spec (TLFS).
 *
 * Copyright (C) 2019, Microsoft, Inc.
 *
 * Author:  Michael Kelley <mikelley@microsoft.com>
 */

#अगर_अघोषित __CLKSOURCE_HYPERV_TIMER_H
#घोषणा __CLKSOURCE_HYPERV_TIMER_H

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/math64.h>
#समावेश <यंत्र/mshyperv.h>

#घोषणा HV_MAX_MAX_DELTA_TICKS 0xffffffff
#घोषणा HV_MIN_DELTA_TICKS 1

/* Routines called by the VMbus driver */
बाह्य पूर्णांक hv_sसमयr_alloc(bool have_percpu_irqs);
बाह्य पूर्णांक hv_sसमयr_cleanup(अचिन्हित पूर्णांक cpu);
बाह्य व्योम hv_sसमयr_legacy_init(अचिन्हित पूर्णांक cpu, पूर्णांक sपूर्णांक);
बाह्य व्योम hv_sसमयr_legacy_cleanup(अचिन्हित पूर्णांक cpu);
बाह्य व्योम hv_sसमयr_global_cleanup(व्योम);
बाह्य व्योम hv_sसमयr0_isr(व्योम);

#अगर_घोषित CONFIG_HYPERV_TIMER
बाह्य u64 (*hv_पढ़ो_reference_counter)(व्योम);
बाह्य व्योम hv_init_घड़ीsource(व्योम);

बाह्य काष्ठा ms_hyperv_tsc_page *hv_get_tsc_page(व्योम);

अटल अंतरभूत notrace u64
hv_पढ़ो_tsc_page_tsc(स्थिर काष्ठा ms_hyperv_tsc_page *tsc_pg, u64 *cur_tsc)
अणु
	u64 scale, offset;
	u32 sequence;

	/*
	 * The protocol क्रम पढ़ोing Hyper-V TSC page is specअगरied in Hypervisor
	 * Top-Level Functional Specअगरication ver. 3.0 and above. To get the
	 * reference समय we must करो the following:
	 * - READ ReferenceTscSequence
	 *   A special '0' value indicates the समय source is unreliable and we
	 *   need to use something अन्यथा. The currently published specअगरication
	 *   versions (up to 4.0b) contain a mistake and wrongly claim '-1'
	 *   instead of '0' as the special value, see commit c35b82ef0294.
	 * - ReferenceTime =
	 *        ((RDTSC() * ReferenceTscScale) >> 64) + ReferenceTscOffset
	 * - READ ReferenceTscSequence again. In हाल its value has changed
	 *   since our first पढ़ोing we need to discard ReferenceTime and repeat
	 *   the whole sequence as the hypervisor was updating the page in
	 *   between.
	 */
	करो अणु
		sequence = READ_ONCE(tsc_pg->tsc_sequence);
		अगर (!sequence)
			वापस U64_MAX;
		/*
		 * Make sure we पढ़ो sequence beक्रमe we पढ़ो other values from
		 * TSC page.
		 */
		smp_rmb();

		scale = READ_ONCE(tsc_pg->tsc_scale);
		offset = READ_ONCE(tsc_pg->tsc_offset);
		*cur_tsc = hv_get_raw_समयr();

		/*
		 * Make sure we पढ़ो sequence after we पढ़ो all other values
		 * from TSC page.
		 */
		smp_rmb();

	पूर्ण जबतक (READ_ONCE(tsc_pg->tsc_sequence) != sequence);

	वापस mul_u64_u64_shr(*cur_tsc, scale, 64) + offset;
पूर्ण

अटल अंतरभूत notrace u64
hv_पढ़ो_tsc_page(स्थिर काष्ठा ms_hyperv_tsc_page *tsc_pg)
अणु
	u64 cur_tsc;

	वापस hv_पढ़ो_tsc_page_tsc(tsc_pg, &cur_tsc);
पूर्ण

#अन्यथा /* CONFIG_HYPERV_TIMER */
अटल अंतरभूत काष्ठा ms_hyperv_tsc_page *hv_get_tsc_page(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत u64 hv_पढ़ो_tsc_page_tsc(स्थिर काष्ठा ms_hyperv_tsc_page *tsc_pg,
				       u64 *cur_tsc)
अणु
	वापस U64_MAX;
पूर्ण
#पूर्ण_अगर /* CONFIG_HYPERV_TIMER */

#पूर्ण_अगर
