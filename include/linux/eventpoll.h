<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  include/linux/eventpoll.h ( Efficient event polling implementation )
 *  Copyright (C) 2001,...,2006	 Davide Libenzi
 *
 *  Davide Libenzi <davidel@xmailserver.org>
 */
#अगर_अघोषित _LINUX_EVENTPOLL_H
#घोषणा _LINUX_EVENTPOLL_H

#समावेश <uapi/linux/eventpoll.h>
#समावेश <uapi/linux/kcmp.h>


/* Forward declarations to aव्योम compiler errors */
काष्ठा file;


#अगर_घोषित CONFIG_EPOLL

#अगर_घोषित CONFIG_KCMP
काष्ठा file *get_epoll_tfile_raw_ptr(काष्ठा file *file, पूर्णांक tfd, अचिन्हित दीर्घ toff);
#पूर्ण_अगर

/* Used to release the epoll bits inside the "struct file" */
व्योम eventpoll_release_file(काष्ठा file *file);

/*
 * This is called from inside fs/file_table.c:__fput() to unlink files
 * from the eventpoll पूर्णांकerface. We need to have this facility to cleanup
 * correctly files that are बंदd without being हटाओd from the eventpoll
 * पूर्णांकerface.
 */
अटल अंतरभूत व्योम eventpoll_release(काष्ठा file *file)
अणु

	/*
	 * Fast check to aव्योम the get/release of the semaphore. Since
	 * we're करोing this outside the semaphore lock, it might वापस
	 * false negatives, but we करोn't care. It'll help in 99.99% of हालs
	 * to aव्योम the semaphore lock. False positives simply cannot happen
	 * because the file in on the way to be हटाओd and nobody ( but
	 * eventpoll ) has still a reference to this file.
	 */
	अगर (likely(!file->f_ep))
		वापस;

	/*
	 * The file is being बंदd जबतक it is still linked to an epoll
	 * descriptor. We need to handle this by correctly unlinking it
	 * from its containers.
	 */
	eventpoll_release_file(file);
पूर्ण

पूर्णांक करो_epoll_ctl(पूर्णांक epfd, पूर्णांक op, पूर्णांक fd, काष्ठा epoll_event *epds,
		 bool nonblock);

/* Tells अगर the epoll_ctl(2) operation needs an event copy from userspace */
अटल अंतरभूत पूर्णांक ep_op_has_event(पूर्णांक op)
अणु
	वापस op != EPOLL_CTL_DEL;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम eventpoll_release(काष्ठा file *file) अणुपूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* #अगर_अघोषित _LINUX_EVENTPOLL_H */
