<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PREEMPT_H
#घोषणा PREEMPT_H

#समावेश <stdbool.h>

#समावेश "bug_on.h"

/* This flag contains garbage अगर preempt_disable_count is 0. */
बाह्य __thपढ़ो पूर्णांक thपढ़ो_cpu_id;

/* Support recursive preemption disabling. */
बाह्य __thपढ़ो पूर्णांक preempt_disable_count;

व्योम preempt_disable(व्योम);
व्योम preempt_enable(व्योम);

अटल अंतरभूत व्योम preempt_disable_notrace(व्योम)
अणु
	preempt_disable();
पूर्ण

अटल अंतरभूत व्योम preempt_enable_no_resched(व्योम)
अणु
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम preempt_enable_notrace(व्योम)
अणु
	preempt_enable();
पूर्ण

अटल अंतरभूत पूर्णांक preempt_count(व्योम)
अणु
	वापस preempt_disable_count;
पूर्ण

अटल अंतरभूत bool preemptible(व्योम)
अणु
	वापस !preempt_count();
पूर्ण

अटल अंतरभूत पूर्णांक get_cpu(व्योम)
अणु
	preempt_disable();
	वापस thपढ़ो_cpu_id;
पूर्ण

अटल अंतरभूत व्योम put_cpu(व्योम)
अणु
	preempt_enable();
पूर्ण

अटल अंतरभूत व्योम might_sleep(व्योम)
अणु
	BUG_ON(preempt_disable_count);
पूर्ण

#पूर्ण_अगर
