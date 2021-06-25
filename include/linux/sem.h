<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SEM_H
#घोषणा _LINUX_SEM_H

#समावेश <uapi/linux/sem.h>

काष्ठा task_काष्ठा;
काष्ठा sem_unकरो_list;

#अगर_घोषित CONFIG_SYSVIPC

काष्ठा sysv_sem अणु
	काष्ठा sem_unकरो_list *unकरो_list;
पूर्ण;

बाह्य पूर्णांक copy_semunकरो(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk);
बाह्य व्योम निकास_sem(काष्ठा task_काष्ठा *tsk);

#अन्यथा

काष्ठा sysv_sem अणु
	/* empty */
पूर्ण;

अटल अंतरभूत पूर्णांक copy_semunकरो(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम निकास_sem(काष्ठा task_काष्ठा *tsk)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SEM_H */
