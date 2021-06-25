<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * RCU-based infraकाष्ठाure क्रम lightweight पढ़ोer-ग_लिखोr locking
 *
 * Copyright (c) 2015, Red Hat, Inc.
 *
 * Author: Oleg Nesterov <oleg@redhat.com>
 */

#अगर_अघोषित _LINUX_RCU_SYNC_H_
#घोषणा _LINUX_RCU_SYNC_H_

#समावेश <linux/रुको.h>
#समावेश <linux/rcupdate.h>

/* Structure to mediate between updaters and fastpath-using पढ़ोers.  */
काष्ठा rcu_sync अणु
	पूर्णांक			gp_state;
	पूर्णांक			gp_count;
	रुको_queue_head_t	gp_रुको;

	काष्ठा rcu_head		cb_head;
पूर्ण;

/**
 * rcu_sync_is_idle() - Are पढ़ोers permitted to use their fastpaths?
 * @rsp: Poपूर्णांकer to rcu_sync काष्ठाure to use क्रम synchronization
 *
 * Returns true अगर पढ़ोers are permitted to use their fastpaths.  Must be
 * invoked within some flavor of RCU पढ़ो-side critical section.
 */
अटल अंतरभूत bool rcu_sync_is_idle(काष्ठा rcu_sync *rsp)
अणु
	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_any_held(),
			 "suspicious rcu_sync_is_idle() usage");
	वापस !READ_ONCE(rsp->gp_state); /* GP_IDLE */
पूर्ण

बाह्य व्योम rcu_sync_init(काष्ठा rcu_sync *);
बाह्य व्योम rcu_sync_enter_start(काष्ठा rcu_sync *);
बाह्य व्योम rcu_sync_enter(काष्ठा rcu_sync *);
बाह्य व्योम rcu_sync_निकास(काष्ठा rcu_sync *);
बाह्य व्योम rcu_sync_dtor(काष्ठा rcu_sync *);

#घोषणा __RCU_SYNC_INITIALIZER(name) अणु					\
		.gp_state = 0,						\
		.gp_count = 0,						\
		.gp_रुको = __WAIT_QUEUE_HEAD_INITIALIZER(name.gp_रुको),	\
	पूर्ण

#घोषणा	DEFINE_RCU_SYNC(name)	\
	काष्ठा rcu_sync name = __RCU_SYNC_INITIALIZER(name)

#पूर्ण_अगर /* _LINUX_RCU_SYNC_H_ */
