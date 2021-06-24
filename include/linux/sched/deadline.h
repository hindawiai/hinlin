<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * SCHED_DEADLINE tasks has negative priorities, reflecting
 * the fact that any of them has higher prio than RT and
 * NORMAL/BATCH tasks.
 */

#घोषणा MAX_DL_PRIO		0

अटल अंतरभूत पूर्णांक dl_prio(पूर्णांक prio)
अणु
	अगर (unlikely(prio < MAX_DL_PRIO))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dl_task(काष्ठा task_काष्ठा *p)
अणु
	वापस dl_prio(p->prio);
पूर्ण

अटल अंतरभूत bool dl_समय_beक्रमe(u64 a, u64 b)
अणु
	वापस (s64)(a - b) < 0;
पूर्ण

#अगर_घोषित CONFIG_SMP

काष्ठा root_करोमुख्य;
बाह्य व्योम dl_add_task_root_करोमुख्य(काष्ठा task_काष्ठा *p);
बाह्य व्योम dl_clear_root_करोमुख्य(काष्ठा root_करोमुख्य *rd);

#पूर्ण_अगर /* CONFIG_SMP */
