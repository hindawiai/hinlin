<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2018
 * Auxtrace support क्रम s390 CPU-Measurement Sampling Facility
 *
 * Author(s):  Thomas Richter <पंचांगricht@linux.ibm.com>
 */

#अगर_अघोषित INCLUDE__PERF_S390_CPUMSF_H
#घोषणा INCLUDE__PERF_S390_CPUMSF_H

जोड़ perf_event;
काष्ठा perf_session;
काष्ठा perf_pmu;

काष्ठा auxtrace_record *
s390_cpumsf_recording_init(पूर्णांक *err, काष्ठा perf_pmu *s390_cpumsf_pmu);

पूर्णांक s390_cpumsf_process_auxtrace_info(जोड़ perf_event *event,
				      काष्ठा perf_session *session);
#पूर्ण_अगर
