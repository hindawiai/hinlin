<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_USER_RETURN_NOTIFIER_H
#घोषणा _LINUX_USER_RETURN_NOTIFIER_H

#अगर_घोषित CONFIG_USER_RETURN_NOTIFIER

#समावेश <linux/list.h>
#समावेश <linux/sched.h>

काष्ठा user_वापस_notअगरier अणु
	व्योम (*on_user_वापस)(काष्ठा user_वापस_notअगरier *urn);
	काष्ठा hlist_node link;
पूर्ण;


व्योम user_वापस_notअगरier_रेजिस्टर(काष्ठा user_वापस_notअगरier *urn);
व्योम user_वापस_notअगरier_unरेजिस्टर(काष्ठा user_वापस_notअगरier *urn);

अटल अंतरभूत व्योम propagate_user_वापस_notअगरy(काष्ठा task_काष्ठा *prev,
						काष्ठा task_काष्ठा *next)
अणु
	अगर (test_tsk_thपढ़ो_flag(prev, TIF_USER_RETURN_NOTIFY)) अणु
		clear_tsk_thपढ़ो_flag(prev, TIF_USER_RETURN_NOTIFY);
		set_tsk_thपढ़ो_flag(next, TIF_USER_RETURN_NOTIFY);
	पूर्ण
पूर्ण

व्योम fire_user_वापस_notअगरiers(व्योम);

अटल अंतरभूत व्योम clear_user_वापस_notअगरier(काष्ठा task_काष्ठा *p)
अणु
	clear_tsk_thपढ़ो_flag(p, TIF_USER_RETURN_NOTIFY);
पूर्ण

#अन्यथा

काष्ठा user_वापस_notअगरier अणुपूर्ण;

अटल अंतरभूत व्योम propagate_user_वापस_notअगरy(काष्ठा task_काष्ठा *prev,
						काष्ठा task_काष्ठा *next)
अणु
पूर्ण

अटल अंतरभूत व्योम fire_user_वापस_notअगरiers(व्योम) अणुपूर्ण

अटल अंतरभूत व्योम clear_user_वापस_notअगरier(काष्ठा task_काष्ठा *p) अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
