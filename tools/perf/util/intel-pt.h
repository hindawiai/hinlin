<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांकel_pt.h: Intel Processor Trace support
 * Copyright (c) 2013-2015, Intel Corporation.
 */

#अगर_अघोषित INCLUDE__PERF_INTEL_PT_H__
#घोषणा INCLUDE__PERF_INTEL_PT_H__

#घोषणा INTEL_PT_PMU_NAME "intel_pt"

क्रमागत अणु
	INTEL_PT_PMU_TYPE,
	INTEL_PT_TIME_SHIFT,
	INTEL_PT_TIME_MULT,
	INTEL_PT_TIME_ZERO,
	INTEL_PT_CAP_USER_TIME_ZERO,
	INTEL_PT_TSC_BIT,
	INTEL_PT_NORETCOMP_BIT,
	INTEL_PT_HAVE_SCHED_SWITCH,
	INTEL_PT_SNAPSHOT_MODE,
	INTEL_PT_PER_CPU_MMAPS,
	INTEL_PT_MTC_BIT,
	INTEL_PT_MTC_FREQ_BITS,
	INTEL_PT_TSC_CTC_N,
	INTEL_PT_TSC_CTC_D,
	INTEL_PT_CYC_BIT,
	INTEL_PT_MAX_NONTURBO_RATIO,
	INTEL_PT_FILTER_STR_LEN,
	INTEL_PT_AUXTRACE_PRIV_MAX,
पूर्ण;

काष्ठा auxtrace_record;
काष्ठा perf_tool;
जोड़ perf_event;
काष्ठा perf_session;
काष्ठा perf_event_attr;
काष्ठा perf_pmu;

काष्ठा auxtrace_record *पूर्णांकel_pt_recording_init(पूर्णांक *err);

पूर्णांक पूर्णांकel_pt_process_auxtrace_info(जोड़ perf_event *event,
				   काष्ठा perf_session *session);

काष्ठा perf_event_attr *पूर्णांकel_pt_pmu_शेष_config(काष्ठा perf_pmu *pmu);

#पूर्ण_अगर
