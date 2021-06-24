<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_PMU_EBB_EBB_H
#घोषणा _SELFTESTS_POWERPC_PMU_EBB_EBB_H

#समावेश "../event.h"
#समावेश "../lib.h"
#समावेश "trace.h"
#समावेश "reg.h"

#घोषणा PMC_INDEX(pmc)	((pmc)-1)

#घोषणा NUM_PMC_VALUES	128

काष्ठा ebb_state
अणु
	काष्ठा अणु
		u64 pmc_count[6];
		अस्थिर पूर्णांक ebb_count;
		पूर्णांक spurious;
		पूर्णांक negative;
		पूर्णांक no_overflow;
	पूर्ण stats;

	bool pmc_enable[6];
	काष्ठा trace_buffer *trace;
पूर्ण;

बाह्य काष्ठा ebb_state ebb_state;

#घोषणा COUNTER_OVERFLOW 0x80000000ull

अटल अंतरभूत uपूर्णांक32_t pmc_sample_period(uपूर्णांक32_t value)
अणु
	वापस COUNTER_OVERFLOW - value;
पूर्ण

अटल अंतरभूत व्योम ebb_enable_pmc_counting(पूर्णांक pmc)
अणु
	ebb_state.pmc_enable[PMC_INDEX(pmc)] = true;
पूर्ण

bool ebb_check_count(पूर्णांक pmc, u64 sample_period, पूर्णांक fudge);
व्योम event_leader_ebb_init(काष्ठा event *e);
व्योम event_ebb_init(काष्ठा event *e);
व्योम event_bhrb_init(काष्ठा event *e, अचिन्हित अगरm);
व्योम setup_ebb_handler(व्योम (*callee)(व्योम));
व्योम standard_ebb_callee(व्योम);
पूर्णांक ebb_event_enable(काष्ठा event *e);
व्योम ebb_global_enable(व्योम);
व्योम ebb_global_disable(व्योम);
bool ebb_is_supported(व्योम);
व्योम ebb_मुक्तze_pmcs(व्योम);
व्योम ebb_unमुक्तze_pmcs(व्योम);
व्योम event_ebb_init(काष्ठा event *e);
व्योम event_leader_ebb_init(काष्ठा event *e);
पूर्णांक count_pmc(पूर्णांक pmc, uपूर्णांक32_t sample_period);
व्योम dump_ebb_state(व्योम);
व्योम dump_summary_ebb_state(व्योम);
व्योम dump_ebb_hw_state(व्योम);
व्योम clear_ebb_stats(व्योम);
व्योम ग_लिखो_pmc(पूर्णांक pmc, u64 value);
u64 पढ़ो_pmc(पूर्णांक pmc);
व्योम reset_ebb_with_clear_mask(अचिन्हित दीर्घ mmcr0_clear_mask);
व्योम reset_ebb(व्योम);
पूर्णांक ebb_check_mmcr0(व्योम);

बाह्य u64 sample_period;

पूर्णांक core_busy_loop(व्योम);
पूर्णांक ebb_child(जोड़ pipe पढ़ो_pipe, जोड़ pipe ग_लिखो_pipe);
पूर्णांक catch_sigill(व्योम (*func)(व्योम));
व्योम ग_लिखो_pmc1(व्योम);

#पूर्ण_अगर /* _SELFTESTS_POWERPC_PMU_EBB_EBB_H */
