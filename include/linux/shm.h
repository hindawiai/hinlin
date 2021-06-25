<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SHM_H_
#घोषणा _LINUX_SHM_H_

#समावेश <linux/list.h>
#समावेश <यंत्र/page.h>
#समावेश <uapi/linux/shm.h>
#समावेश <यंत्र/shmparam.h>

काष्ठा file;

#अगर_घोषित CONFIG_SYSVIPC
काष्ठा sysv_shm अणु
	काष्ठा list_head shm_clist;
पूर्ण;

दीर्घ करो_shmat(पूर्णांक shmid, अक्षर __user *shmaddr, पूर्णांक shmflg, अचिन्हित दीर्घ *addr,
	      अचिन्हित दीर्घ shmlba);
bool is_file_shm_hugepages(काष्ठा file *file);
व्योम निकास_shm(काष्ठा task_काष्ठा *task);
#घोषणा shm_init_task(task) INIT_LIST_HEAD(&(task)->sysvshm.shm_clist)
#अन्यथा
काष्ठा sysv_shm अणु
	/* empty */
पूर्ण;

अटल अंतरभूत दीर्घ करो_shmat(पूर्णांक shmid, अक्षर __user *shmaddr,
			    पूर्णांक shmflg, अचिन्हित दीर्घ *addr,
			    अचिन्हित दीर्घ shmlba)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत bool is_file_shm_hugepages(काष्ठा file *file)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम निकास_shm(काष्ठा task_काष्ठा *task)
अणु
पूर्ण
अटल अंतरभूत व्योम shm_init_task(काष्ठा task_काष्ठा *task)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SHM_H_ */
