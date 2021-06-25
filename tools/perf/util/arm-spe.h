<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Arm Statistical Profiling Extensions (SPE) support
 * Copyright (c) 2017-2018, Arm Ltd.
 */

#अगर_अघोषित INCLUDE__PERF_ARM_SPE_H__
#घोषणा INCLUDE__PERF_ARM_SPE_H__

#घोषणा ARM_SPE_PMU_NAME "arm_spe_"

क्रमागत अणु
	ARM_SPE_PMU_TYPE,
	ARM_SPE_PER_CPU_MMAPS,
	ARM_SPE_AUXTRACE_PRIV_MAX,
पूर्ण;

#घोषणा ARM_SPE_AUXTRACE_PRIV_SIZE (ARM_SPE_AUXTRACE_PRIV_MAX * माप(u64))

जोड़ perf_event;
काष्ठा perf_session;
काष्ठा perf_pmu;

काष्ठा auxtrace_record *arm_spe_recording_init(पूर्णांक *err,
					       काष्ठा perf_pmu *arm_spe_pmu);

पूर्णांक arm_spe_process_auxtrace_info(जोड़ perf_event *event,
				  काष्ठा perf_session *session);

काष्ठा perf_event_attr *arm_spe_pmu_शेष_config(काष्ठा perf_pmu *arm_spe_pmu);
#पूर्ण_अगर
