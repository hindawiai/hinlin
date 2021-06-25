<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_TSC_H
#घोषणा __PERF_TSC_H

#समावेश <linux/types.h>

#समावेश "event.h"

काष्ठा perf_tsc_conversion अणु
	u16 समय_shअगरt;
	u32 समय_mult;
	u64 समय_zero;
	u64 समय_cycles;
	u64 समय_mask;

	bool cap_user_समय_zero;
	bool cap_user_समय_लघु;
पूर्ण;

काष्ठा perf_event_mmap_page;

पूर्णांक perf_पढ़ो_tsc_conversion(स्थिर काष्ठा perf_event_mmap_page *pc,
			     काष्ठा perf_tsc_conversion *tc);

u64 perf_समय_प्रकारo_tsc(u64 ns, काष्ठा perf_tsc_conversion *tc);
u64 tsc_to_perf_समय(u64 cyc, काष्ठा perf_tsc_conversion *tc);
u64 rdtsc(व्योम);

माप_प्रकार perf_event__ख_लिखो_समय_conv(जोड़ perf_event *event, खाता *fp);

#पूर्ण_अगर // __PERF_TSC_H
