<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_HOTPLUG_H
#घोषणा _LINUX_SCHED_HOTPLUG_H

/*
 * Scheduler पूर्णांकerfaces क्रम hotplug CPU support:
 */

बाह्य पूर्णांक sched_cpu_starting(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक sched_cpu_activate(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक sched_cpu_deactivate(अचिन्हित पूर्णांक cpu);

#अगर_घोषित CONFIG_HOTPLUG_CPU
बाह्य पूर्णांक sched_cpu_रुको_empty(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक sched_cpu_dying(अचिन्हित पूर्णांक cpu);
#अन्यथा
# define sched_cpu_रुको_empty	शून्य
# define sched_cpu_dying	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
बाह्य व्योम idle_task_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम idle_task_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_HOTPLUG_H */
