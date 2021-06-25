<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_NET_AFUNIX_H
#घोषणा __LINUX_NET_AFUNIX_H

#समावेश <linux/socket.h>
#समावेश <linux/un.h>
#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>
#समावेश <net/sock.h>

व्योम unix_inflight(काष्ठा user_काष्ठा *user, काष्ठा file *fp);
व्योम unix_notinflight(काष्ठा user_काष्ठा *user, काष्ठा file *fp);
व्योम unix_deकाष्ठा_scm(काष्ठा sk_buff *skb);
व्योम unix_gc(व्योम);
व्योम रुको_क्रम_unix_gc(व्योम);
काष्ठा sock *unix_get_socket(काष्ठा file *filp);
काष्ठा sock *unix_peer_get(काष्ठा sock *sk);

#घोषणा UNIX_HASH_SIZE	256
#घोषणा UNIX_HASH_BITS	8

बाह्य अचिन्हित पूर्णांक unix_tot_inflight;
बाह्य spinlock_t unix_table_lock;
बाह्य काष्ठा hlist_head unix_socket_table[2 * UNIX_HASH_SIZE];

काष्ठा unix_address अणु
	refcount_t	refcnt;
	पूर्णांक		len;
	अचिन्हित पूर्णांक	hash;
	काष्ठा sockaddr_un name[];
पूर्ण;

काष्ठा unix_skb_parms अणु
	काष्ठा pid		*pid;		/* Skb credentials	*/
	kuid_t			uid;
	kgid_t			gid;
	काष्ठा scm_fp_list	*fp;		/* Passed files		*/
#अगर_घोषित CONFIG_SECURITY_NETWORK
	u32			secid;		/* Security ID		*/
#पूर्ण_अगर
	u32			consumed;
पूर्ण __अक्रमomize_layout;

काष्ठा scm_stat अणु
	atomic_t nr_fds;
पूर्ण;

#घोषणा UNIXCB(skb)	(*(काष्ठा unix_skb_parms *)&((skb)->cb))

#घोषणा unix_state_lock(s)	spin_lock(&unix_sk(s)->lock)
#घोषणा unix_state_unlock(s)	spin_unlock(&unix_sk(s)->lock)
#घोषणा unix_state_lock_nested(s) \
				spin_lock_nested(&unix_sk(s)->lock, \
				SINGLE_DEPTH_NESTING)

/* The AF_UNIX socket */
काष्ठा unix_sock अणु
	/* WARNING: sk has to be the first member */
	काष्ठा sock		sk;
	काष्ठा unix_address	*addr;
	काष्ठा path		path;
	काष्ठा mutex		iolock, bindlock;
	काष्ठा sock		*peer;
	काष्ठा list_head	link;
	atomic_दीर्घ_t		inflight;
	spinlock_t		lock;
	अचिन्हित दीर्घ		gc_flags;
#घोषणा UNIX_GC_CANDIDATE	0
#घोषणा UNIX_GC_MAYBE_CYCLE	1
	काष्ठा socket_wq	peer_wq;
	रुको_queue_entry_t	peer_wake;
	काष्ठा scm_stat		scm_stat;
पूर्ण;

अटल अंतरभूत काष्ठा unix_sock *unix_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा unix_sock *)sk;
पूर्ण

#घोषणा peer_रुको peer_wq.रुको

दीर्घ unix_inq_len(काष्ठा sock *sk);
दीर्घ unix_outq_len(काष्ठा sock *sk);

#अगर_घोषित CONFIG_SYSCTL
पूर्णांक unix_sysctl_रेजिस्टर(काष्ठा net *net);
व्योम unix_sysctl_unरेजिस्टर(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत पूर्णांक unix_sysctl_रेजिस्टर(काष्ठा net *net) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम unix_sysctl_unरेजिस्टर(काष्ठा net *net) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
