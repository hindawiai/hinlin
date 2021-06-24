<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_NOHZ_H
#घोषणा _LINUX_SCHED_NOHZ_H

/*
 * This is the पूर्णांकerface between the scheduler and nohz/dynticks:
 */

#अगर defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
बाह्य व्योम nohz_balance_enter_idle(पूर्णांक cpu);
बाह्य पूर्णांक get_nohz_समयr_target(व्योम);
#अन्यथा
अटल अंतरभूत व्योम nohz_balance_enter_idle(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NO_HZ_COMMON
व्योम calc_load_nohz_start(व्योम);
व्योम calc_load_nohz_remote(काष्ठा rq *rq);
व्योम calc_load_nohz_stop(व्योम);
#अन्यथा
अटल अंतरभूत व्योम calc_load_nohz_start(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम calc_load_nohz_remote(काष्ठा rq *rq) अणु पूर्ण
अटल अंतरभूत व्योम calc_load_nohz_stop(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

#अगर defined(CONFIG_NO_HZ_COMMON) && defined(CONFIG_SMP)
बाह्य व्योम wake_up_nohz_cpu(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम wake_up_nohz_cpu(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_NOHZ_H */
