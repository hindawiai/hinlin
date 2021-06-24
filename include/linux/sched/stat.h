<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_STAT_H
#घोषणा _LINUX_SCHED_STAT_H

#समावेश <linux/percpu.h>

/*
 * Various counters मुख्यtained by the scheduler and विभाजन(),
 * exposed via /proc, sys.c or used by drivers via these APIs.
 *
 * ( Note that all these values are acquired without locking,
 *   so they can only be relied on in narrow circumstances. )
 */

बाह्य अचिन्हित दीर्घ total_विभाजनs;
बाह्य पूर्णांक nr_thपढ़ोs;
DECLARE_PER_CPU(अचिन्हित दीर्घ, process_counts);
बाह्य पूर्णांक nr_processes(व्योम);
बाह्य अचिन्हित दीर्घ nr_running(व्योम);
बाह्य bool single_task_running(व्योम);
बाह्य अचिन्हित दीर्घ nr_ioरुको(व्योम);
बाह्य अचिन्हित दीर्घ nr_ioरुको_cpu(पूर्णांक cpu);

अटल अंतरभूत पूर्णांक sched_info_on(व्योम)
अणु
#अगर_घोषित CONFIG_SCHEDSTATS
	वापस 1;
#या_अगर defined(CONFIG_TASK_DELAY_ACCT)
	बाह्य पूर्णांक delayacct_on;
	वापस delayacct_on;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SCHEDSTATS
व्योम क्रमce_schedstat_enabled(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_STAT_H */
