<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित CONFIG_SCHED_AUTOGROUP

काष्ठा स्वतःgroup अणु
	/*
	 * Reference करोesn't mean how many thपढ़ोs attach to this
	 * स्वतःgroup now. It just stands क्रम the number of tasks
	 * which could use this स्वतःgroup.
	 */
	काष्ठा kref		kref;
	काष्ठा task_group	*tg;
	काष्ठा rw_semaphore	lock;
	अचिन्हित दीर्घ		id;
	पूर्णांक			nice;
पूर्ण;

बाह्य व्योम स्वतःgroup_init(काष्ठा task_काष्ठा *init_task);
बाह्य व्योम स्वतःgroup_मुक्त(काष्ठा task_group *tg);

अटल अंतरभूत bool task_group_is_स्वतःgroup(काष्ठा task_group *tg)
अणु
	वापस !!tg->स्वतःgroup;
पूर्ण

बाह्य bool task_wants_स्वतःgroup(काष्ठा task_काष्ठा *p, काष्ठा task_group *tg);

अटल अंतरभूत काष्ठा task_group *
स्वतःgroup_task_group(काष्ठा task_काष्ठा *p, काष्ठा task_group *tg)
अणु
	पूर्णांक enabled = READ_ONCE(sysctl_sched_स्वतःgroup_enabled);

	अगर (enabled && task_wants_स्वतःgroup(p, tg))
		वापस p->संकेत->स्वतःgroup->tg;

	वापस tg;
पूर्ण

बाह्य पूर्णांक स्वतःgroup_path(काष्ठा task_group *tg, अक्षर *buf, पूर्णांक buflen);

#अन्यथा /* !CONFIG_SCHED_AUTOGROUP */

अटल अंतरभूत व्योम स्वतःgroup_init(काष्ठा task_काष्ठा *init_task) अणु  पूर्ण
अटल अंतरभूत व्योम स्वतःgroup_मुक्त(काष्ठा task_group *tg) अणु पूर्ण
अटल अंतरभूत bool task_group_is_स्वतःgroup(काष्ठा task_group *tg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा task_group *
स्वतःgroup_task_group(काष्ठा task_काष्ठा *p, काष्ठा task_group *tg)
अणु
	वापस tg;
पूर्ण

अटल अंतरभूत पूर्णांक स्वतःgroup_path(काष्ठा task_group *tg, अक्षर *buf, पूर्णांक buflen)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SCHED_AUTOGROUP */
