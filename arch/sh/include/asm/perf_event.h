<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PERF_EVENT_H
#घोषणा __ASM_SH_PERF_EVENT_H

काष्ठा hw_perf_event;

#घोषणा MAX_HWEVENTS	2

काष्ठा sh_pmu अणु
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	num_events;
	व्योम		(*disable_all)(व्योम);
	व्योम		(*enable_all)(व्योम);
	व्योम		(*enable)(काष्ठा hw_perf_event *, पूर्णांक);
	व्योम		(*disable)(काष्ठा hw_perf_event *, पूर्णांक);
	u64		(*पढ़ो)(पूर्णांक);
	पूर्णांक		(*event_map)(पूर्णांक);
	अचिन्हित पूर्णांक	max_events;
	अचिन्हित दीर्घ	raw_event_mask;
	स्थिर पूर्णांक	(*cache_events)[PERF_COUNT_HW_CACHE_MAX]
				       [PERF_COUNT_HW_CACHE_OP_MAX]
				       [PERF_COUNT_HW_CACHE_RESULT_MAX];
पूर्ण;

/* arch/sh/kernel/perf_event.c */
बाह्य पूर्णांक रेजिस्टर_sh_pmu(काष्ठा sh_pmu *);
बाह्य पूर्णांक reserve_pmc_hardware(व्योम);
बाह्य व्योम release_pmc_hardware(व्योम);

#पूर्ण_अगर /* __ASM_SH_PERF_EVENT_H */
