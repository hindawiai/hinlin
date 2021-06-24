<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SOCK_REUSEPORT_H
#घोषणा _SOCK_REUSEPORT_H

#समावेश <linux/filter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <net/sock.h>

बाह्य spinlock_t reuseport_lock;

काष्ठा sock_reuseport अणु
	काष्ठा rcu_head		rcu;

	u16			max_socks;	/* length of socks */
	u16			num_socks;	/* elements in socks */
	/* The last synq overflow event बारtamp of this
	 * reuse->socks[] group.
	 */
	अचिन्हित पूर्णांक		synq_overflow_ts;
	/* ID stays the same even after the size of socks[] grows. */
	अचिन्हित पूर्णांक		reuseport_id;
	अचिन्हित पूर्णांक		bind_inany:1;
	अचिन्हित पूर्णांक		has_conns:1;
	काष्ठा bpf_prog __rcu	*prog;		/* optional BPF sock selector */
	काष्ठा sock		*socks[];	/* array of sock poपूर्णांकers */
पूर्ण;

बाह्य पूर्णांक reuseport_alloc(काष्ठा sock *sk, bool bind_inany);
बाह्य पूर्णांक reuseport_add_sock(काष्ठा sock *sk, काष्ठा sock *sk2,
			      bool bind_inany);
बाह्य व्योम reuseport_detach_sock(काष्ठा sock *sk);
बाह्य काष्ठा sock *reuseport_select_sock(काष्ठा sock *sk,
					  u32 hash,
					  काष्ठा sk_buff *skb,
					  पूर्णांक hdr_len);
बाह्य पूर्णांक reuseport_attach_prog(काष्ठा sock *sk, काष्ठा bpf_prog *prog);
बाह्य पूर्णांक reuseport_detach_prog(काष्ठा sock *sk);

अटल अंतरभूत bool reuseport_has_conns(काष्ठा sock *sk, bool set)
अणु
	काष्ठा sock_reuseport *reuse;
	bool ret = false;

	rcu_पढ़ो_lock();
	reuse = rcu_dereference(sk->sk_reuseport_cb);
	अगर (reuse) अणु
		अगर (set)
			reuse->has_conns = 1;
		ret = reuse->has_conns;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

#पूर्ण_अगर  /* _SOCK_REUSEPORT_H */
