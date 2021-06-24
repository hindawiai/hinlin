<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TRACE_CLOCK_H
#घोषणा _LINUX_TRACE_CLOCK_H

/*
 * 3 trace घड़ी variants, with dअगरfering scalability/precision
 * tradeoffs:
 *
 *  -   local: CPU-local trace घड़ी
 *  -  medium: scalable global घड़ी with some jitter
 *  -  global: globally monotonic, serialized घड़ी
 */
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/trace_घड़ी.h>

बाह्य u64 notrace trace_घड़ी_local(व्योम);
बाह्य u64 notrace trace_घड़ी(व्योम);
बाह्य u64 notrace trace_घड़ी_jअगरfies(व्योम);
बाह्य u64 notrace trace_घड़ी_global(व्योम);
बाह्य u64 notrace trace_घड़ी_counter(व्योम);

#पूर्ण_अगर /* _LINUX_TRACE_CLOCK_H */
