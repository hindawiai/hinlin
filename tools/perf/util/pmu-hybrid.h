<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PMU_HYBRID_H
#घोषणा __PMU_HYBRID_H

#समावेश <linux/perf_event.h>
#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <stdbool.h>
#समावेश "pmu.h"

बाह्य काष्ठा list_head perf_pmu__hybrid_pmus;

#घोषणा perf_pmu__क्रम_each_hybrid_pmu(pmu)	\
	list_क्रम_each_entry(pmu, &perf_pmu__hybrid_pmus, hybrid_list)

bool perf_pmu__hybrid_mounted(स्थिर अक्षर *name);

काष्ठा perf_pmu *perf_pmu__find_hybrid_pmu(स्थिर अक्षर *name);
bool perf_pmu__is_hybrid(स्थिर अक्षर *name);
अक्षर *perf_pmu__hybrid_type_to_pmu(स्थिर अक्षर *type);

#पूर्ण_अगर /* __PMU_HYBRID_H */
