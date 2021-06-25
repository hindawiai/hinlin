<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_TIMER_H
#घोषणा _ASM_X86_TIMER_H
#समावेश <linux/pm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/math64.h>

#घोषणा TICK_SIZE (tick_nsec / 1000)

अचिन्हित दीर्घ दीर्घ native_sched_घड़ी(व्योम);
बाह्य व्योम recalibrate_cpu_khz(व्योम);

बाह्य पूर्णांक no_समयr_check;

बाह्य bool using_native_sched_घड़ी(व्योम);

/*
 * We use the full linear equation: f(x) = a + b*x, in order to allow
 * a continuous function in the face of dynamic freq changes.
 *
 * Continuity means that when our frequency changes our slope (b); we want to
 * ensure that: f(t) == f'(t), which gives: a + b*t == a' + b'*t.
 *
 * Without an offset (a) the above would not be possible.
 *
 * See the comment near cycles_2_ns() क्रम details on how we compute (b).
 */
काष्ठा cyc2ns_data अणु
	u32 cyc2ns_mul;
	u32 cyc2ns_shअगरt;
	u64 cyc2ns_offset;
पूर्ण; /* 16 bytes */

बाह्य व्योम cyc2ns_पढ़ो_begin(काष्ठा cyc2ns_data *);
बाह्य व्योम cyc2ns_पढ़ो_end(व्योम);

#पूर्ण_अगर /* _ASM_X86_TIMER_H */
