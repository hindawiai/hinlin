<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_AUTOGROUP_H
#घोषणा _LINUX_SCHED_AUTOGROUP_H

काष्ठा संकेत_काष्ठा;
काष्ठा task_काष्ठा;
काष्ठा task_group;
काष्ठा seq_file;

#अगर_घोषित CONFIG_SCHED_AUTOGROUP
बाह्य व्योम sched_स्वतःgroup_create_attach(काष्ठा task_काष्ठा *p);
बाह्य व्योम sched_स्वतःgroup_detach(काष्ठा task_काष्ठा *p);
बाह्य व्योम sched_स्वतःgroup_विभाजन(काष्ठा संकेत_काष्ठा *sig);
बाह्य व्योम sched_स्वतःgroup_निकास(काष्ठा संकेत_काष्ठा *sig);
बाह्य व्योम sched_स्वतःgroup_निकास_task(काष्ठा task_काष्ठा *p);
#अगर_घोषित CONFIG_PROC_FS
बाह्य व्योम proc_sched_स्वतःgroup_show_task(काष्ठा task_काष्ठा *p, काष्ठा seq_file *m);
बाह्य पूर्णांक proc_sched_स्वतःgroup_set_nice(काष्ठा task_काष्ठा *p, पूर्णांक nice);
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत व्योम sched_स्वतःgroup_create_attach(काष्ठा task_काष्ठा *p) अणु पूर्ण
अटल अंतरभूत व्योम sched_स्वतःgroup_detach(काष्ठा task_काष्ठा *p) अणु पूर्ण
अटल अंतरभूत व्योम sched_स्वतःgroup_विभाजन(काष्ठा संकेत_काष्ठा *sig) अणु पूर्ण
अटल अंतरभूत व्योम sched_स्वतःgroup_निकास(काष्ठा संकेत_काष्ठा *sig) अणु पूर्ण
अटल अंतरभूत व्योम sched_स्वतःgroup_निकास_task(काष्ठा task_काष्ठा *p) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUP_SCHED
बाह्य काष्ठा task_group root_task_group;
#पूर्ण_अगर /* CONFIG_CGROUP_SCHED */

#पूर्ण_अगर /* _LINUX_SCHED_AUTOGROUP_H */
