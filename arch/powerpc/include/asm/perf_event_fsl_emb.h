<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Perक्रमmance event support - Freescale embedded specअगरic definitions.
 *
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 * Copyright 2010 Freescale Semiconductor, Inc.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/hw_irq.h>

#घोषणा MAX_HWEVENTS 6

/* event flags */
#घोषणा FSL_EMB_EVENT_VALID      1
#घोषणा FSL_EMB_EVENT_RESTRICTED 2

/* upper half of event flags is PMLCb */
#घोषणा FSL_EMB_EVENT_THRESHMUL  0x0000070000000000ULL
#घोषणा FSL_EMB_EVENT_THRESH     0x0000003f00000000ULL

काष्ठा fsl_emb_pmu अणु
	स्थिर अक्षर	*name;
	पूर्णांक		n_counter; /* total number of counters */

	/*
	 * The number of contiguous counters starting at zero that
	 * can hold restricted events, or zero अगर there are no
	 * restricted events.
	 *
	 * This isn't a very flexible method of expressing स्थिरraपूर्णांकs,
	 * but it's very simple and is adequate क्रम existing chips.
	 */
	पूर्णांक		n_restricted;

	/* Returns event flags and PMLCb (FSL_EMB_EVENT_*) */
	u64		(*xlate_event)(u64 event_id);

	पूर्णांक		n_generic;
	पूर्णांक		*generic_events;
	पूर्णांक		(*cache_events)[PERF_COUNT_HW_CACHE_MAX]
			       [PERF_COUNT_HW_CACHE_OP_MAX]
			       [PERF_COUNT_HW_CACHE_RESULT_MAX];
पूर्ण;

पूर्णांक रेजिस्टर_fsl_emb_pmu(काष्ठा fsl_emb_pmu *);
