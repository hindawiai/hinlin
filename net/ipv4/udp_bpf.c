<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Cloudflare Ltd https://cloudflare.com */

#समावेश <linux/skmsg.h>
#समावेश <net/sock.h>
#समावेश <net/udp.h>
#समावेश <net/inet_common.h>

#समावेश "udp_impl.h"

अटल काष्ठा proto *udpv6_prot_saved __पढ़ो_mostly;

अटल पूर्णांक sk_udp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			  पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		वापस udpv6_prot_saved->recvmsg(sk, msg, len, noblock, flags,
						 addr_len);
#पूर्ण_अगर
	वापस udp_prot.recvmsg(sk, msg, len, noblock, flags, addr_len);
पूर्ण

अटल पूर्णांक udp_bpf_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			   पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा sk_psock *psock;
	पूर्णांक copied, ret;

	अगर (unlikely(flags & MSG_ERRQUEUE))
		वापस inet_recv_error(sk, msg, len, addr_len);

	psock = sk_psock_get(sk);
	अगर (unlikely(!psock))
		वापस sk_udp_recvmsg(sk, msg, len, nonblock, flags, addr_len);

	lock_sock(sk);
	अगर (sk_psock_queue_empty(psock)) अणु
		ret = sk_udp_recvmsg(sk, msg, len, nonblock, flags, addr_len);
		जाओ out;
	पूर्ण

msg_bytes_पढ़ोy:
	copied = sk_msg_recvmsg(sk, psock, msg, len, flags);
	अगर (!copied) अणु
		पूर्णांक data, err = 0;
		दीर्घ समयo;

		समयo = sock_rcvसमयo(sk, nonblock);
		data = sk_msg_रुको_data(sk, psock, flags, समयo, &err);
		अगर (data) अणु
			अगर (!sk_psock_queue_empty(psock))
				जाओ msg_bytes_पढ़ोy;
			ret = sk_udp_recvmsg(sk, msg, len, nonblock, flags, addr_len);
			जाओ out;
		पूर्ण
		अगर (err) अणु
			ret = err;
			जाओ out;
		पूर्ण
		copied = -EAGAIN;
	पूर्ण
	ret = copied;
out:
	release_sock(sk);
	sk_psock_put(sk, psock);
	वापस ret;
पूर्ण

क्रमागत अणु
	UDP_BPF_IPV4,
	UDP_BPF_IPV6,
	UDP_BPF_NUM_PROTS,
पूर्ण;

अटल DEFINE_SPINLOCK(udpv6_prot_lock);
अटल काष्ठा proto udp_bpf_prots[UDP_BPF_NUM_PROTS];

अटल व्योम udp_bpf_rebuild_protos(काष्ठा proto *prot, स्थिर काष्ठा proto *base)
अणु
	*prot        = *base;
	prot->unhash = sock_map_unhash;
	prot->बंद  = sock_map_बंद;
	prot->recvmsg = udp_bpf_recvmsg;
पूर्ण

अटल व्योम udp_bpf_check_v6_needs_rebuild(काष्ठा proto *ops)
अणु
	अगर (unlikely(ops != smp_load_acquire(&udpv6_prot_saved))) अणु
		spin_lock_bh(&udpv6_prot_lock);
		अगर (likely(ops != udpv6_prot_saved)) अणु
			udp_bpf_rebuild_protos(&udp_bpf_prots[UDP_BPF_IPV6], ops);
			smp_store_release(&udpv6_prot_saved, ops);
		पूर्ण
		spin_unlock_bh(&udpv6_prot_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक __init udp_bpf_v4_build_proto(व्योम)
अणु
	udp_bpf_rebuild_protos(&udp_bpf_prots[UDP_BPF_IPV4], &udp_prot);
	वापस 0;
पूर्ण
core_initcall(udp_bpf_v4_build_proto);

पूर्णांक udp_bpf_update_proto(काष्ठा sock *sk, काष्ठा sk_psock *psock, bool restore)
अणु
	पूर्णांक family = sk->sk_family == AF_INET ? UDP_BPF_IPV4 : UDP_BPF_IPV6;

	अगर (restore) अणु
		sk->sk_ग_लिखो_space = psock->saved_ग_लिखो_space;
		WRITE_ONCE(sk->sk_prot, psock->sk_proto);
		वापस 0;
	पूर्ण

	अगर (sk->sk_family == AF_INET6)
		udp_bpf_check_v6_needs_rebuild(psock->sk_proto);

	WRITE_ONCE(sk->sk_prot, &udp_bpf_prots[family]);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(udp_bpf_update_proto);
