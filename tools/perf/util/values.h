<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_VALUES_H
#घोषणा __PERF_VALUES_H

#समावेश <linux/types.h>

काष्ठा perf_पढ़ो_values अणु
	पूर्णांक thपढ़ोs;
	पूर्णांक thपढ़ोs_max;
	u32 *pid, *tid;
	पूर्णांक counters;
	पूर्णांक counters_max;
	u64 *counterrawid;
	अक्षर **countername;
	u64 **value;
पूर्ण;

पूर्णांक perf_पढ़ो_values_init(काष्ठा perf_पढ़ो_values *values);
व्योम perf_पढ़ो_values_destroy(काष्ठा perf_पढ़ो_values *values);

पूर्णांक perf_पढ़ो_values_add_value(काष्ठा perf_पढ़ो_values *values,
				u32 pid, u32 tid,
				u64 rawid, स्थिर अक्षर *name, u64 value);

व्योम perf_पढ़ो_values_display(खाता *fp, काष्ठा perf_पढ़ो_values *values,
			      पूर्णांक raw);

#पूर्ण_अगर /* __PERF_VALUES_H */
