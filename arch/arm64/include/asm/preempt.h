<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PREEMPT_H
#घोषणा __ASM_PREEMPT_H

#समावेश <linux/thपढ़ो_info.h>

#घोषणा PREEMPT_NEED_RESCHED	BIT(32)
#घोषणा PREEMPT_ENABLED	(PREEMPT_NEED_RESCHED)

अटल अंतरभूत पूर्णांक preempt_count(व्योम)
अणु
	वापस READ_ONCE(current_thपढ़ो_info()->preempt.count);
पूर्ण

अटल अंतरभूत व्योम preempt_count_set(u64 pc)
अणु
	/* Preserve existing value of PREEMPT_NEED_RESCHED */
	WRITE_ONCE(current_thपढ़ो_info()->preempt.count, pc);
पूर्ण

#घोषणा init_task_preempt_count(p) करो अणु \
	task_thपढ़ो_info(p)->preempt_count = FORK_PREEMPT_COUNT; \
पूर्ण जबतक (0)

#घोषणा init_idle_preempt_count(p, cpu) करो अणु \
	task_thपढ़ो_info(p)->preempt_count = PREEMPT_ENABLED; \
पूर्ण जबतक (0)

अटल अंतरभूत व्योम set_preempt_need_resched(व्योम)
अणु
	current_thपढ़ो_info()->preempt.need_resched = 0;
पूर्ण

अटल अंतरभूत व्योम clear_preempt_need_resched(व्योम)
अणु
	current_thपढ़ो_info()->preempt.need_resched = 1;
पूर्ण

अटल अंतरभूत bool test_preempt_need_resched(व्योम)
अणु
	वापस !current_thपढ़ो_info()->preempt.need_resched;
पूर्ण

अटल अंतरभूत व्योम __preempt_count_add(पूर्णांक val)
अणु
	u32 pc = READ_ONCE(current_thपढ़ो_info()->preempt.count);
	pc += val;
	WRITE_ONCE(current_thपढ़ो_info()->preempt.count, pc);
पूर्ण

अटल अंतरभूत व्योम __preempt_count_sub(पूर्णांक val)
अणु
	u32 pc = READ_ONCE(current_thपढ़ो_info()->preempt.count);
	pc -= val;
	WRITE_ONCE(current_thपढ़ो_info()->preempt.count, pc);
पूर्ण

अटल अंतरभूत bool __preempt_count_dec_and_test(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	u64 pc = READ_ONCE(ti->preempt_count);

	/* Update only the count field, leaving need_resched unchanged */
	WRITE_ONCE(ti->preempt.count, --pc);

	/*
	 * If we wrote back all zeroes, then we're preemptible and in
	 * need of a reschedule. Otherwise, we need to reload the
	 * preempt_count in हाल the need_resched flag was cleared by an
	 * पूर्णांकerrupt occurring between the non-atomic READ_ONCE/WRITE_ONCE
	 * pair.
	 */
	वापस !pc || !READ_ONCE(ti->preempt_count);
पूर्ण

अटल अंतरभूत bool should_resched(पूर्णांक preempt_offset)
अणु
	u64 pc = READ_ONCE(current_thपढ़ो_info()->preempt_count);
	वापस pc == preempt_offset;
पूर्ण

#अगर_घोषित CONFIG_PREEMPTION
व्योम preempt_schedule(व्योम);
#घोषणा __preempt_schedule() preempt_schedule()
व्योम preempt_schedule_notrace(व्योम);
#घोषणा __preempt_schedule_notrace() preempt_schedule_notrace()
#पूर्ण_अगर /* CONFIG_PREEMPTION */

#पूर्ण_अगर /* __ASM_PREEMPT_H */
