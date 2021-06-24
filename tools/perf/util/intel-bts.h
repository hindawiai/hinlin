<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांकel-bts.h: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#अगर_अघोषित INCLUDE__PERF_INTEL_BTS_H__
#घोषणा INCLUDE__PERF_INTEL_BTS_H__

#घोषणा INTEL_BTS_PMU_NAME "intel_bts"

क्रमागत अणु
	INTEL_BTS_PMU_TYPE,
	INTEL_BTS_TIME_SHIFT,
	INTEL_BTS_TIME_MULT,
	INTEL_BTS_TIME_ZERO,
	INTEL_BTS_CAP_USER_TIME_ZERO,
	INTEL_BTS_SNAPSHOT_MODE,
	INTEL_BTS_AUXTRACE_PRIV_MAX,
पूर्ण;

#घोषणा INTEL_BTS_AUXTRACE_PRIV_SIZE (INTEL_BTS_AUXTRACE_PRIV_MAX * माप(u64))

काष्ठा auxtrace_record;
काष्ठा perf_tool;
जोड़ perf_event;
काष्ठा perf_session;

काष्ठा auxtrace_record *पूर्णांकel_bts_recording_init(पूर्णांक *err);

पूर्णांक पूर्णांकel_bts_process_auxtrace_info(जोड़ perf_event *event,
				    काष्ठा perf_session *session);

#पूर्ण_अगर
