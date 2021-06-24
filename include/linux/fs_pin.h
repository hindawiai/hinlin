<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/रुको.h>

काष्ठा fs_pin अणु
	रुको_queue_head_t	रुको;
	पूर्णांक			करोne;
	काष्ठा hlist_node	s_list;
	काष्ठा hlist_node	m_list;
	व्योम (*समाप्त)(काष्ठा fs_pin *);
पूर्ण;

काष्ठा vfsmount;

अटल अंतरभूत व्योम init_fs_pin(काष्ठा fs_pin *p, व्योम (*समाप्त)(काष्ठा fs_pin *))
अणु
	init_रुकोqueue_head(&p->रुको);
	INIT_HLIST_NODE(&p->s_list);
	INIT_HLIST_NODE(&p->m_list);
	p->समाप्त = समाप्त;
पूर्ण

व्योम pin_हटाओ(काष्ठा fs_pin *);
व्योम pin_insert(काष्ठा fs_pin *, काष्ठा vfsmount *);
व्योम pin_समाप्त(काष्ठा fs_pin *);
