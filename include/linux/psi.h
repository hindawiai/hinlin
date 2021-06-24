<शैली गुरु>
#अगर_अघोषित _LINUX_PSI_H
#घोषणा _LINUX_PSI_H

#समावेश <linux/jump_label.h>
#समावेश <linux/psi_types.h>
#समावेश <linux/sched.h>
#समावेश <linux/poll.h>

काष्ठा seq_file;
काष्ठा css_set;

#अगर_घोषित CONFIG_PSI

बाह्य काष्ठा अटल_key_false psi_disabled;
बाह्य काष्ठा psi_group psi_प्रणाली;

व्योम psi_init(व्योम);

व्योम psi_task_change(काष्ठा task_काष्ठा *task, पूर्णांक clear, पूर्णांक set);
व्योम psi_task_चयन(काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next,
		     bool sleep);

व्योम psi_memstall_enter(अचिन्हित दीर्घ *flags);
व्योम psi_memstall_leave(अचिन्हित दीर्घ *flags);

पूर्णांक psi_show(काष्ठा seq_file *s, काष्ठा psi_group *group, क्रमागत psi_res res);

#अगर_घोषित CONFIG_CGROUPS
पूर्णांक psi_cgroup_alloc(काष्ठा cgroup *cgrp);
व्योम psi_cgroup_मुक्त(काष्ठा cgroup *cgrp);
व्योम cgroup_move_task(काष्ठा task_काष्ठा *p, काष्ठा css_set *to);

काष्ठा psi_trigger *psi_trigger_create(काष्ठा psi_group *group,
			अक्षर *buf, माप_प्रकार nbytes, क्रमागत psi_res res);
व्योम psi_trigger_replace(व्योम **trigger_ptr, काष्ठा psi_trigger *t);

__poll_t psi_trigger_poll(व्योम **trigger_ptr, काष्ठा file *file,
			poll_table *रुको);
#पूर्ण_अगर

#अन्यथा /* CONFIG_PSI */

अटल अंतरभूत व्योम psi_init(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम psi_memstall_enter(अचिन्हित दीर्घ *flags) अणुपूर्ण
अटल अंतरभूत व्योम psi_memstall_leave(अचिन्हित दीर्घ *flags) अणुपूर्ण

#अगर_घोषित CONFIG_CGROUPS
अटल अंतरभूत पूर्णांक psi_cgroup_alloc(काष्ठा cgroup *cgrp)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम psi_cgroup_मुक्त(काष्ठा cgroup *cgrp)
अणु
पूर्ण
अटल अंतरभूत व्योम cgroup_move_task(काष्ठा task_काष्ठा *p, काष्ठा css_set *to)
अणु
	rcu_assign_poपूर्णांकer(p->cgroups, to);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PSI */

#पूर्ण_अगर /* _LINUX_PSI_H */
