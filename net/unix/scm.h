<शैली गुरु>
#अगर_अघोषित NET_UNIX_SCM_H
#घोषणा NET_UNIX_SCM_H

बाह्य काष्ठा list_head gc_inflight_list;
बाह्य spinlock_t unix_gc_lock;

पूर्णांक unix_attach_fds(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb);
व्योम unix_detach_fds(काष्ठा scm_cookie *scm, काष्ठा sk_buff *skb);

#पूर्ण_अगर
