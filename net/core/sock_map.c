<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017 - 2018 Covalent IO, Inc. http://covalent.io */

#समावेश <linux/bpf.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/filter.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/file.h>
#समावेश <linux/net.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/skmsg.h>
#समावेश <linux/list.h>
#समावेश <linux/jhash.h>
#समावेश <linux/sock_diag.h>
#समावेश <net/udp.h>

काष्ठा bpf_stab अणु
	काष्ठा bpf_map map;
	काष्ठा sock **sks;
	काष्ठा sk_psock_progs progs;
	raw_spinlock_t lock;
पूर्ण;

#घोषणा SOCK_CREATE_FLAG_MASK				\
	(BPF_F_NUMA_NODE | BPF_F_RDONLY | BPF_F_WRONLY)

अटल पूर्णांक sock_map_prog_update(काष्ठा bpf_map *map, काष्ठा bpf_prog *prog,
				काष्ठा bpf_prog *old, u32 which);
अटल काष्ठा sk_psock_progs *sock_map_progs(काष्ठा bpf_map *map);

अटल काष्ठा bpf_map *sock_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_stab *stab;

	अगर (!capable(CAP_NET_ADMIN))
		वापस ERR_PTR(-EPERM);
	अगर (attr->max_entries == 0 ||
	    attr->key_size    != 4 ||
	    (attr->value_size != माप(u32) &&
	     attr->value_size != माप(u64)) ||
	    attr->map_flags & ~SOCK_CREATE_FLAG_MASK)
		वापस ERR_PTR(-EINVAL);

	stab = kzalloc(माप(*stab), GFP_USER | __GFP_ACCOUNT);
	अगर (!stab)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&stab->map, attr);
	raw_spin_lock_init(&stab->lock);

	stab->sks = bpf_map_area_alloc(stab->map.max_entries *
				       माप(काष्ठा sock *),
				       stab->map.numa_node);
	अगर (!stab->sks) अणु
		kमुक्त(stab);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस &stab->map;
पूर्ण

पूर्णांक sock_map_get_from_fd(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	u32 ufd = attr->target_fd;
	काष्ठा bpf_map *map;
	काष्ठा fd f;
	पूर्णांक ret;

	अगर (attr->attach_flags || attr->replace_bpf_fd)
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);
	ret = sock_map_prog_update(map, prog, शून्य, attr->attach_type);
	fdput(f);
	वापस ret;
पूर्ण

पूर्णांक sock_map_prog_detach(स्थिर जोड़ bpf_attr *attr, क्रमागत bpf_prog_type ptype)
अणु
	u32 ufd = attr->target_fd;
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_map *map;
	काष्ठा fd f;
	पूर्णांक ret;

	अगर (attr->attach_flags || attr->replace_bpf_fd)
		वापस -EINVAL;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	prog = bpf_prog_get(attr->attach_bpf_fd);
	अगर (IS_ERR(prog)) अणु
		ret = PTR_ERR(prog);
		जाओ put_map;
	पूर्ण

	अगर (prog->type != ptype) अणु
		ret = -EINVAL;
		जाओ put_prog;
	पूर्ण

	ret = sock_map_prog_update(map, शून्य, prog, attr->attach_type);
put_prog:
	bpf_prog_put(prog);
put_map:
	fdput(f);
	वापस ret;
पूर्ण

अटल व्योम sock_map_sk_acquire(काष्ठा sock *sk)
	__acquires(&sk->sk_lock.slock)
अणु
	lock_sock(sk);
	preempt_disable();
	rcu_पढ़ो_lock();
पूर्ण

अटल व्योम sock_map_sk_release(काष्ठा sock *sk)
	__releases(&sk->sk_lock.slock)
अणु
	rcu_पढ़ो_unlock();
	preempt_enable();
	release_sock(sk);
पूर्ण

अटल व्योम sock_map_add_link(काष्ठा sk_psock *psock,
			      काष्ठा sk_psock_link *link,
			      काष्ठा bpf_map *map, व्योम *link_raw)
अणु
	link->link_raw = link_raw;
	link->map = map;
	spin_lock_bh(&psock->link_lock);
	list_add_tail(&link->list, &psock->link);
	spin_unlock_bh(&psock->link_lock);
पूर्ण

अटल व्योम sock_map_del_link(काष्ठा sock *sk,
			      काष्ठा sk_psock *psock, व्योम *link_raw)
अणु
	bool strp_stop = false, verdict_stop = false;
	काष्ठा sk_psock_link *link, *पंचांगp;

	spin_lock_bh(&psock->link_lock);
	list_क्रम_each_entry_safe(link, पंचांगp, &psock->link, list) अणु
		अगर (link->link_raw == link_raw) अणु
			काष्ठा bpf_map *map = link->map;
			काष्ठा bpf_stab *stab = container_of(map, काष्ठा bpf_stab,
							     map);
			अगर (psock->saved_data_पढ़ोy && stab->progs.stream_parser)
				strp_stop = true;
			अगर (psock->saved_data_पढ़ोy && stab->progs.stream_verdict)
				verdict_stop = true;
			अगर (psock->saved_data_पढ़ोy && stab->progs.skb_verdict)
				verdict_stop = true;
			list_del(&link->list);
			sk_psock_मुक्त_link(link);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&psock->link_lock);
	अगर (strp_stop || verdict_stop) अणु
		ग_लिखो_lock_bh(&sk->sk_callback_lock);
		अगर (strp_stop)
			sk_psock_stop_strp(sk, psock);
		अन्यथा
			sk_psock_stop_verdict(sk, psock);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण
पूर्ण

अटल व्योम sock_map_unref(काष्ठा sock *sk, व्योम *link_raw)
अणु
	काष्ठा sk_psock *psock = sk_psock(sk);

	अगर (likely(psock)) अणु
		sock_map_del_link(sk, psock, link_raw);
		sk_psock_put(sk, psock);
	पूर्ण
पूर्ण

अटल पूर्णांक sock_map_init_proto(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अगर (!sk->sk_prot->psock_update_sk_prot)
		वापस -EINVAL;
	psock->psock_update_sk_prot = sk->sk_prot->psock_update_sk_prot;
	वापस sk->sk_prot->psock_update_sk_prot(sk, psock, false);
पूर्ण

अटल काष्ठा sk_psock *sock_map_psock_get_checked(काष्ठा sock *sk)
अणु
	काष्ठा sk_psock *psock;

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (psock) अणु
		अगर (sk->sk_prot->बंद != sock_map_बंद) अणु
			psock = ERR_PTR(-EBUSY);
			जाओ out;
		पूर्ण

		अगर (!refcount_inc_not_zero(&psock->refcnt))
			psock = ERR_PTR(-EBUSY);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस psock;
पूर्ण

अटल bool sock_map_redirect_allowed(स्थिर काष्ठा sock *sk);

अटल पूर्णांक sock_map_link(काष्ठा bpf_map *map, काष्ठा sock *sk)
अणु
	काष्ठा sk_psock_progs *progs = sock_map_progs(map);
	काष्ठा bpf_prog *stream_verdict = शून्य;
	काष्ठा bpf_prog *stream_parser = शून्य;
	काष्ठा bpf_prog *skb_verdict = शून्य;
	काष्ठा bpf_prog *msg_parser = शून्य;
	काष्ठा sk_psock *psock;
	पूर्णांक ret;

	/* Only sockets we can redirect पूर्णांकo/from in BPF need to hold
	 * refs to parser/verdict progs and have their sk_data_पढ़ोy
	 * and sk_ग_लिखो_space callbacks overridden.
	 */
	अगर (!sock_map_redirect_allowed(sk))
		जाओ no_progs;

	stream_verdict = READ_ONCE(progs->stream_verdict);
	अगर (stream_verdict) अणु
		stream_verdict = bpf_prog_inc_not_zero(stream_verdict);
		अगर (IS_ERR(stream_verdict))
			वापस PTR_ERR(stream_verdict);
	पूर्ण

	stream_parser = READ_ONCE(progs->stream_parser);
	अगर (stream_parser) अणु
		stream_parser = bpf_prog_inc_not_zero(stream_parser);
		अगर (IS_ERR(stream_parser)) अणु
			ret = PTR_ERR(stream_parser);
			जाओ out_put_stream_verdict;
		पूर्ण
	पूर्ण

	msg_parser = READ_ONCE(progs->msg_parser);
	अगर (msg_parser) अणु
		msg_parser = bpf_prog_inc_not_zero(msg_parser);
		अगर (IS_ERR(msg_parser)) अणु
			ret = PTR_ERR(msg_parser);
			जाओ out_put_stream_parser;
		पूर्ण
	पूर्ण

	skb_verdict = READ_ONCE(progs->skb_verdict);
	अगर (skb_verdict) अणु
		skb_verdict = bpf_prog_inc_not_zero(skb_verdict);
		अगर (IS_ERR(skb_verdict)) अणु
			ret = PTR_ERR(skb_verdict);
			जाओ out_put_msg_parser;
		पूर्ण
	पूर्ण

no_progs:
	psock = sock_map_psock_get_checked(sk);
	अगर (IS_ERR(psock)) अणु
		ret = PTR_ERR(psock);
		जाओ out_progs;
	पूर्ण

	अगर (psock) अणु
		अगर ((msg_parser && READ_ONCE(psock->progs.msg_parser)) ||
		    (stream_parser  && READ_ONCE(psock->progs.stream_parser)) ||
		    (skb_verdict && READ_ONCE(psock->progs.skb_verdict)) ||
		    (skb_verdict && READ_ONCE(psock->progs.stream_verdict)) ||
		    (stream_verdict && READ_ONCE(psock->progs.skb_verdict)) ||
		    (stream_verdict && READ_ONCE(psock->progs.stream_verdict))) अणु
			sk_psock_put(sk, psock);
			ret = -EBUSY;
			जाओ out_progs;
		पूर्ण
	पूर्ण अन्यथा अणु
		psock = sk_psock_init(sk, map->numa_node);
		अगर (IS_ERR(psock)) अणु
			ret = PTR_ERR(psock);
			जाओ out_progs;
		पूर्ण
	पूर्ण

	अगर (msg_parser)
		psock_set_prog(&psock->progs.msg_parser, msg_parser);

	ret = sock_map_init_proto(sk, psock);
	अगर (ret < 0)
		जाओ out_drop;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	अगर (stream_parser && stream_verdict && !psock->saved_data_पढ़ोy) अणु
		ret = sk_psock_init_strp(sk, psock);
		अगर (ret)
			जाओ out_unlock_drop;
		psock_set_prog(&psock->progs.stream_verdict, stream_verdict);
		psock_set_prog(&psock->progs.stream_parser, stream_parser);
		sk_psock_start_strp(sk, psock);
	पूर्ण अन्यथा अगर (!stream_parser && stream_verdict && !psock->saved_data_पढ़ोy) अणु
		psock_set_prog(&psock->progs.stream_verdict, stream_verdict);
		sk_psock_start_verdict(sk,psock);
	पूर्ण अन्यथा अगर (!stream_verdict && skb_verdict && !psock->saved_data_पढ़ोy) अणु
		psock_set_prog(&psock->progs.skb_verdict, skb_verdict);
		sk_psock_start_verdict(sk, psock);
	पूर्ण
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	वापस 0;
out_unlock_drop:
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
out_drop:
	sk_psock_put(sk, psock);
out_progs:
	अगर (skb_verdict)
		bpf_prog_put(skb_verdict);
out_put_msg_parser:
	अगर (msg_parser)
		bpf_prog_put(msg_parser);
out_put_stream_parser:
	अगर (stream_parser)
		bpf_prog_put(stream_parser);
out_put_stream_verdict:
	अगर (stream_verdict)
		bpf_prog_put(stream_verdict);
	वापस ret;
पूर्ण

अटल व्योम sock_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_stab *stab = container_of(map, काष्ठा bpf_stab, map);
	पूर्णांक i;

	/* After the sync no updates or deletes will be in-flight so it
	 * is safe to walk map and हटाओ entries without risking a race
	 * in EEXIST update हाल.
	 */
	synchronize_rcu();
	क्रम (i = 0; i < stab->map.max_entries; i++) अणु
		काष्ठा sock **psk = &stab->sks[i];
		काष्ठा sock *sk;

		sk = xchg(psk, शून्य);
		अगर (sk) अणु
			lock_sock(sk);
			rcu_पढ़ो_lock();
			sock_map_unref(sk, psk);
			rcu_पढ़ो_unlock();
			release_sock(sk);
		पूर्ण
	पूर्ण

	/* रुको क्रम psock पढ़ोers accessing its map link */
	synchronize_rcu();

	bpf_map_area_मुक्त(stab->sks);
	kमुक्त(stab);
पूर्ण

अटल व्योम sock_map_release_progs(काष्ठा bpf_map *map)
अणु
	psock_progs_drop(&container_of(map, काष्ठा bpf_stab, map)->progs);
पूर्ण

अटल काष्ठा sock *__sock_map_lookup_elem(काष्ठा bpf_map *map, u32 key)
अणु
	काष्ठा bpf_stab *stab = container_of(map, काष्ठा bpf_stab, map);

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	अगर (unlikely(key >= map->max_entries))
		वापस शून्य;
	वापस READ_ONCE(stab->sks[key]);
पूर्ण

अटल व्योम *sock_map_lookup(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा sock *sk;

	sk = __sock_map_lookup_elem(map, *(u32 *)key);
	अगर (!sk)
		वापस शून्य;
	अगर (sk_is_refcounted(sk) && !refcount_inc_not_zero(&sk->sk_refcnt))
		वापस शून्य;
	वापस sk;
पूर्ण

अटल व्योम *sock_map_lookup_sys(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा sock *sk;

	अगर (map->value_size != माप(u64))
		वापस ERR_PTR(-ENOSPC);

	sk = __sock_map_lookup_elem(map, *(u32 *)key);
	अगर (!sk)
		वापस ERR_PTR(-ENOENT);

	__sock_gen_cookie(sk);
	वापस &sk->sk_cookie;
पूर्ण

अटल पूर्णांक __sock_map_delete(काष्ठा bpf_stab *stab, काष्ठा sock *sk_test,
			     काष्ठा sock **psk)
अणु
	काष्ठा sock *sk;
	पूर्णांक err = 0;

	raw_spin_lock_bh(&stab->lock);
	sk = *psk;
	अगर (!sk_test || sk_test == sk)
		sk = xchg(psk, शून्य);

	अगर (likely(sk))
		sock_map_unref(sk, psk);
	अन्यथा
		err = -EINVAL;

	raw_spin_unlock_bh(&stab->lock);
	वापस err;
पूर्ण

अटल व्योम sock_map_delete_from_link(काष्ठा bpf_map *map, काष्ठा sock *sk,
				      व्योम *link_raw)
अणु
	काष्ठा bpf_stab *stab = container_of(map, काष्ठा bpf_stab, map);

	__sock_map_delete(stab, sk, link_raw);
पूर्ण

अटल पूर्णांक sock_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_stab *stab = container_of(map, काष्ठा bpf_stab, map);
	u32 i = *(u32 *)key;
	काष्ठा sock **psk;

	अगर (unlikely(i >= map->max_entries))
		वापस -EINVAL;

	psk = &stab->sks[i];
	वापस __sock_map_delete(stab, शून्य, psk);
पूर्ण

अटल पूर्णांक sock_map_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next)
अणु
	काष्ठा bpf_stab *stab = container_of(map, काष्ठा bpf_stab, map);
	u32 i = key ? *(u32 *)key : U32_MAX;
	u32 *key_next = next;

	अगर (i == stab->map.max_entries - 1)
		वापस -ENOENT;
	अगर (i >= stab->map.max_entries)
		*key_next = 0;
	अन्यथा
		*key_next = i + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक sock_map_update_common(काष्ठा bpf_map *map, u32 idx,
				  काष्ठा sock *sk, u64 flags)
अणु
	काष्ठा bpf_stab *stab = container_of(map, काष्ठा bpf_stab, map);
	काष्ठा sk_psock_link *link;
	काष्ठा sk_psock *psock;
	काष्ठा sock *osk;
	पूर्णांक ret;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	अगर (unlikely(flags > BPF_EXIST))
		वापस -EINVAL;
	अगर (unlikely(idx >= map->max_entries))
		वापस -E2BIG;

	link = sk_psock_init_link();
	अगर (!link)
		वापस -ENOMEM;

	ret = sock_map_link(map, sk);
	अगर (ret < 0)
		जाओ out_मुक्त;

	psock = sk_psock(sk);
	WARN_ON_ONCE(!psock);

	raw_spin_lock_bh(&stab->lock);
	osk = stab->sks[idx];
	अगर (osk && flags == BPF_NOEXIST) अणु
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (!osk && flags == BPF_EXIST) अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	sock_map_add_link(psock, link, map, &stab->sks[idx]);
	stab->sks[idx] = sk;
	अगर (osk)
		sock_map_unref(osk, &stab->sks[idx]);
	raw_spin_unlock_bh(&stab->lock);
	वापस 0;
out_unlock:
	raw_spin_unlock_bh(&stab->lock);
	अगर (psock)
		sk_psock_put(sk, psock);
out_मुक्त:
	sk_psock_मुक्त_link(link);
	वापस ret;
पूर्ण

अटल bool sock_map_op_okay(स्थिर काष्ठा bpf_sock_ops_kern *ops)
अणु
	वापस ops->op == BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB ||
	       ops->op == BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB ||
	       ops->op == BPF_SOCK_OPS_TCP_LISTEN_CB;
पूर्ण

अटल bool sk_is_tcp(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_type == SOCK_STREAM &&
	       sk->sk_protocol == IPPROTO_TCP;
पूर्ण

अटल bool sk_is_udp(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_type == SOCK_DGRAM &&
	       sk->sk_protocol == IPPROTO_UDP;
पूर्ण

अटल bool sock_map_redirect_allowed(स्थिर काष्ठा sock *sk)
अणु
	अगर (sk_is_tcp(sk))
		वापस sk->sk_state != TCP_LISTEN;
	अन्यथा
		वापस sk->sk_state == TCP_ESTABLISHED;
पूर्ण

अटल bool sock_map_sk_is_suitable(स्थिर काष्ठा sock *sk)
अणु
	वापस !!sk->sk_prot->psock_update_sk_prot;
पूर्ण

अटल bool sock_map_sk_state_allowed(स्थिर काष्ठा sock *sk)
अणु
	अगर (sk_is_tcp(sk))
		वापस (1 << sk->sk_state) & (TCPF_ESTABLISHED | TCPF_LISTEN);
	अन्यथा अगर (sk_is_udp(sk))
		वापस sk_hashed(sk);

	वापस false;
पूर्ण

अटल पूर्णांक sock_hash_update_common(काष्ठा bpf_map *map, व्योम *key,
				   काष्ठा sock *sk, u64 flags);

पूर्णांक sock_map_update_elem_sys(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
			     u64 flags)
अणु
	काष्ठा socket *sock;
	काष्ठा sock *sk;
	पूर्णांक ret;
	u64 ufd;

	अगर (map->value_size == माप(u64))
		ufd = *(u64 *)value;
	अन्यथा
		ufd = *(u32 *)value;
	अगर (ufd > S32_MAX)
		वापस -EINVAL;

	sock = sockfd_lookup(ufd, &ret);
	अगर (!sock)
		वापस ret;
	sk = sock->sk;
	अगर (!sk) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (!sock_map_sk_is_suitable(sk)) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	sock_map_sk_acquire(sk);
	अगर (!sock_map_sk_state_allowed(sk))
		ret = -EOPNOTSUPP;
	अन्यथा अगर (map->map_type == BPF_MAP_TYPE_SOCKMAP)
		ret = sock_map_update_common(map, *(u32 *)key, sk, flags);
	अन्यथा
		ret = sock_hash_update_common(map, key, sk, flags);
	sock_map_sk_release(sk);
out:
	sockfd_put(sock);
	वापस ret;
पूर्ण

अटल पूर्णांक sock_map_update_elem(काष्ठा bpf_map *map, व्योम *key,
				व्योम *value, u64 flags)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)value;
	पूर्णांक ret;

	अगर (unlikely(!sk || !sk_fullsock(sk)))
		वापस -EINVAL;

	अगर (!sock_map_sk_is_suitable(sk))
		वापस -EOPNOTSUPP;

	local_bh_disable();
	bh_lock_sock(sk);
	अगर (!sock_map_sk_state_allowed(sk))
		ret = -EOPNOTSUPP;
	अन्यथा अगर (map->map_type == BPF_MAP_TYPE_SOCKMAP)
		ret = sock_map_update_common(map, *(u32 *)key, sk, flags);
	अन्यथा
		ret = sock_hash_update_common(map, key, sk, flags);
	bh_unlock_sock(sk);
	local_bh_enable();
	वापस ret;
पूर्ण

BPF_CALL_4(bpf_sock_map_update, काष्ठा bpf_sock_ops_kern *, sops,
	   काष्ठा bpf_map *, map, व्योम *, key, u64, flags)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	अगर (likely(sock_map_sk_is_suitable(sops->sk) &&
		   sock_map_op_okay(sops)))
		वापस sock_map_update_common(map, *(u32 *)key, sops->sk,
					      flags);
	वापस -EOPNOTSUPP;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sock_map_update_proto = अणु
	.func		= bpf_sock_map_update,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_PTR_TO_MAP_KEY,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_sk_redirect_map, काष्ठा sk_buff *, skb,
	   काष्ठा bpf_map *, map, u32, key, u64, flags)
अणु
	काष्ठा sock *sk;

	अगर (unlikely(flags & ~(BPF_F_INGRESS)))
		वापस SK_DROP;

	sk = __sock_map_lookup_elem(map, key);
	अगर (unlikely(!sk || !sock_map_redirect_allowed(sk)))
		वापस SK_DROP;

	skb_bpf_set_redir(skb, sk, flags & BPF_F_INGRESS);
	वापस SK_PASS;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sk_redirect_map_proto = अणु
	.func           = bpf_sk_redirect_map,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type      = ARG_CONST_MAP_PTR,
	.arg3_type      = ARG_ANYTHING,
	.arg4_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_msg_redirect_map, काष्ठा sk_msg *, msg,
	   काष्ठा bpf_map *, map, u32, key, u64, flags)
अणु
	काष्ठा sock *sk;

	अगर (unlikely(flags & ~(BPF_F_INGRESS)))
		वापस SK_DROP;

	sk = __sock_map_lookup_elem(map, key);
	अगर (unlikely(!sk || !sock_map_redirect_allowed(sk)))
		वापस SK_DROP;

	msg->flags = flags;
	msg->sk_redir = sk;
	वापस SK_PASS;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_msg_redirect_map_proto = अणु
	.func           = bpf_msg_redirect_map,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type      = ARG_CONST_MAP_PTR,
	.arg3_type      = ARG_ANYTHING,
	.arg4_type      = ARG_ANYTHING,
पूर्ण;

काष्ठा sock_map_seq_info अणु
	काष्ठा bpf_map *map;
	काष्ठा sock *sk;
	u32 index;
पूर्ण;

काष्ठा bpf_iter__sockmap अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा bpf_map *, map);
	__bpf_md_ptr(व्योम *, key);
	__bpf_md_ptr(काष्ठा sock *, sk);
पूर्ण;

DEFINE_BPF_ITER_FUNC(sockmap, काष्ठा bpf_iter_meta *meta,
		     काष्ठा bpf_map *map, व्योम *key,
		     काष्ठा sock *sk)

अटल व्योम *sock_map_seq_lookup_elem(काष्ठा sock_map_seq_info *info)
अणु
	अगर (unlikely(info->index >= info->map->max_entries))
		वापस शून्य;

	info->sk = __sock_map_lookup_elem(info->map, info->index);

	/* can't वापस sk directly, since that might be शून्य */
	वापस info;
पूर्ण

अटल व्योम *sock_map_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	काष्ठा sock_map_seq_info *info = seq->निजी;

	अगर (*pos == 0)
		++*pos;

	/* pairs with sock_map_seq_stop */
	rcu_पढ़ो_lock();
	वापस sock_map_seq_lookup_elem(info);
पूर्ण

अटल व्योम *sock_map_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
	__must_hold(rcu)
अणु
	काष्ठा sock_map_seq_info *info = seq->निजी;

	++*pos;
	++info->index;

	वापस sock_map_seq_lookup_elem(info);
पूर्ण

अटल पूर्णांक sock_map_seq_show(काष्ठा seq_file *seq, व्योम *v)
	__must_hold(rcu)
अणु
	काष्ठा sock_map_seq_info *info = seq->निजी;
	काष्ठा bpf_iter__sockmap ctx = अणुपूर्ण;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, !v);
	अगर (!prog)
		वापस 0;

	ctx.meta = &meta;
	ctx.map = info->map;
	अगर (v) अणु
		ctx.key = &info->index;
		ctx.sk = info->sk;
	पूर्ण

	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल व्योम sock_map_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	अगर (!v)
		(व्योम)sock_map_seq_show(seq, शून्य);

	/* pairs with sock_map_seq_start */
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations sock_map_seq_ops = अणु
	.start	= sock_map_seq_start,
	.next	= sock_map_seq_next,
	.stop	= sock_map_seq_stop,
	.show	= sock_map_seq_show,
पूर्ण;

अटल पूर्णांक sock_map_init_seq_निजी(व्योम *priv_data,
				     काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा sock_map_seq_info *info = priv_data;

	info->map = aux->map;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_iter_seq_info sock_map_iter_seq_info = अणु
	.seq_ops		= &sock_map_seq_ops,
	.init_seq_निजी	= sock_map_init_seq_निजी,
	.seq_priv_size		= माप(काष्ठा sock_map_seq_info),
पूर्ण;

अटल पूर्णांक sock_map_btf_id;
स्थिर काष्ठा bpf_map_ops sock_map_ops = अणु
	.map_meta_equal		= bpf_map_meta_equal,
	.map_alloc		= sock_map_alloc,
	.map_मुक्त		= sock_map_मुक्त,
	.map_get_next_key	= sock_map_get_next_key,
	.map_lookup_elem_sys_only = sock_map_lookup_sys,
	.map_update_elem	= sock_map_update_elem,
	.map_delete_elem	= sock_map_delete_elem,
	.map_lookup_elem	= sock_map_lookup,
	.map_release_uref	= sock_map_release_progs,
	.map_check_btf		= map_check_no_btf,
	.map_btf_name		= "bpf_stab",
	.map_btf_id		= &sock_map_btf_id,
	.iter_seq_info		= &sock_map_iter_seq_info,
पूर्ण;

काष्ठा bpf_shtab_elem अणु
	काष्ठा rcu_head rcu;
	u32 hash;
	काष्ठा sock *sk;
	काष्ठा hlist_node node;
	u8 key[];
पूर्ण;

काष्ठा bpf_shtab_bucket अणु
	काष्ठा hlist_head head;
	raw_spinlock_t lock;
पूर्ण;

काष्ठा bpf_shtab अणु
	काष्ठा bpf_map map;
	काष्ठा bpf_shtab_bucket *buckets;
	u32 buckets_num;
	u32 elem_size;
	काष्ठा sk_psock_progs progs;
	atomic_t count;
पूर्ण;

अटल अंतरभूत u32 sock_hash_bucket_hash(स्थिर व्योम *key, u32 len)
अणु
	वापस jhash(key, len, 0);
पूर्ण

अटल काष्ठा bpf_shtab_bucket *sock_hash_select_bucket(काष्ठा bpf_shtab *htab,
							u32 hash)
अणु
	वापस &htab->buckets[hash & (htab->buckets_num - 1)];
पूर्ण

अटल काष्ठा bpf_shtab_elem *
sock_hash_lookup_elem_raw(काष्ठा hlist_head *head, u32 hash, व्योम *key,
			  u32 key_size)
अणु
	काष्ठा bpf_shtab_elem *elem;

	hlist_क्रम_each_entry_rcu(elem, head, node) अणु
		अगर (elem->hash == hash &&
		    !स_भेद(&elem->key, key, key_size))
			वापस elem;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sock *__sock_hash_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_shtab *htab = container_of(map, काष्ठा bpf_shtab, map);
	u32 key_size = map->key_size, hash;
	काष्ठा bpf_shtab_bucket *bucket;
	काष्ठा bpf_shtab_elem *elem;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	hash = sock_hash_bucket_hash(key, key_size);
	bucket = sock_hash_select_bucket(htab, hash);
	elem = sock_hash_lookup_elem_raw(&bucket->head, hash, key, key_size);

	वापस elem ? elem->sk : शून्य;
पूर्ण

अटल व्योम sock_hash_मुक्त_elem(काष्ठा bpf_shtab *htab,
				काष्ठा bpf_shtab_elem *elem)
अणु
	atomic_dec(&htab->count);
	kमुक्त_rcu(elem, rcu);
पूर्ण

अटल व्योम sock_hash_delete_from_link(काष्ठा bpf_map *map, काष्ठा sock *sk,
				       व्योम *link_raw)
अणु
	काष्ठा bpf_shtab *htab = container_of(map, काष्ठा bpf_shtab, map);
	काष्ठा bpf_shtab_elem *elem_probe, *elem = link_raw;
	काष्ठा bpf_shtab_bucket *bucket;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	bucket = sock_hash_select_bucket(htab, elem->hash);

	/* elem may be deleted in parallel from the map, but access here
	 * is okay since it's going away only after RCU grace period.
	 * However, we need to check whether it's still present.
	 */
	raw_spin_lock_bh(&bucket->lock);
	elem_probe = sock_hash_lookup_elem_raw(&bucket->head, elem->hash,
					       elem->key, map->key_size);
	अगर (elem_probe && elem_probe == elem) अणु
		hlist_del_rcu(&elem->node);
		sock_map_unref(elem->sk, elem);
		sock_hash_मुक्त_elem(htab, elem);
	पूर्ण
	raw_spin_unlock_bh(&bucket->lock);
पूर्ण

अटल पूर्णांक sock_hash_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_shtab *htab = container_of(map, काष्ठा bpf_shtab, map);
	u32 hash, key_size = map->key_size;
	काष्ठा bpf_shtab_bucket *bucket;
	काष्ठा bpf_shtab_elem *elem;
	पूर्णांक ret = -ENOENT;

	hash = sock_hash_bucket_hash(key, key_size);
	bucket = sock_hash_select_bucket(htab, hash);

	raw_spin_lock_bh(&bucket->lock);
	elem = sock_hash_lookup_elem_raw(&bucket->head, hash, key, key_size);
	अगर (elem) अणु
		hlist_del_rcu(&elem->node);
		sock_map_unref(elem->sk, elem);
		sock_hash_मुक्त_elem(htab, elem);
		ret = 0;
	पूर्ण
	raw_spin_unlock_bh(&bucket->lock);
	वापस ret;
पूर्ण

अटल काष्ठा bpf_shtab_elem *sock_hash_alloc_elem(काष्ठा bpf_shtab *htab,
						   व्योम *key, u32 key_size,
						   u32 hash, काष्ठा sock *sk,
						   काष्ठा bpf_shtab_elem *old)
अणु
	काष्ठा bpf_shtab_elem *new;

	अगर (atomic_inc_वापस(&htab->count) > htab->map.max_entries) अणु
		अगर (!old) अणु
			atomic_dec(&htab->count);
			वापस ERR_PTR(-E2BIG);
		पूर्ण
	पूर्ण

	new = bpf_map_kदो_स्मृति_node(&htab->map, htab->elem_size,
				   GFP_ATOMIC | __GFP_NOWARN,
				   htab->map.numa_node);
	अगर (!new) अणु
		atomic_dec(&htab->count);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	स_नकल(new->key, key, key_size);
	new->sk = sk;
	new->hash = hash;
	वापस new;
पूर्ण

अटल पूर्णांक sock_hash_update_common(काष्ठा bpf_map *map, व्योम *key,
				   काष्ठा sock *sk, u64 flags)
अणु
	काष्ठा bpf_shtab *htab = container_of(map, काष्ठा bpf_shtab, map);
	u32 key_size = map->key_size, hash;
	काष्ठा bpf_shtab_elem *elem, *elem_new;
	काष्ठा bpf_shtab_bucket *bucket;
	काष्ठा sk_psock_link *link;
	काष्ठा sk_psock *psock;
	पूर्णांक ret;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	अगर (unlikely(flags > BPF_EXIST))
		वापस -EINVAL;

	link = sk_psock_init_link();
	अगर (!link)
		वापस -ENOMEM;

	ret = sock_map_link(map, sk);
	अगर (ret < 0)
		जाओ out_मुक्त;

	psock = sk_psock(sk);
	WARN_ON_ONCE(!psock);

	hash = sock_hash_bucket_hash(key, key_size);
	bucket = sock_hash_select_bucket(htab, hash);

	raw_spin_lock_bh(&bucket->lock);
	elem = sock_hash_lookup_elem_raw(&bucket->head, hash, key, key_size);
	अगर (elem && flags == BPF_NOEXIST) अणु
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (!elem && flags == BPF_EXIST) अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	elem_new = sock_hash_alloc_elem(htab, key, key_size, hash, sk, elem);
	अगर (IS_ERR(elem_new)) अणु
		ret = PTR_ERR(elem_new);
		जाओ out_unlock;
	पूर्ण

	sock_map_add_link(psock, link, map, elem_new);
	/* Add new element to the head of the list, so that
	 * concurrent search will find it beक्रमe old elem.
	 */
	hlist_add_head_rcu(&elem_new->node, &bucket->head);
	अगर (elem) अणु
		hlist_del_rcu(&elem->node);
		sock_map_unref(elem->sk, elem);
		sock_hash_मुक्त_elem(htab, elem);
	पूर्ण
	raw_spin_unlock_bh(&bucket->lock);
	वापस 0;
out_unlock:
	raw_spin_unlock_bh(&bucket->lock);
	sk_psock_put(sk, psock);
out_मुक्त:
	sk_psock_मुक्त_link(link);
	वापस ret;
पूर्ण

अटल पूर्णांक sock_hash_get_next_key(काष्ठा bpf_map *map, व्योम *key,
				  व्योम *key_next)
अणु
	काष्ठा bpf_shtab *htab = container_of(map, काष्ठा bpf_shtab, map);
	काष्ठा bpf_shtab_elem *elem, *elem_next;
	u32 hash, key_size = map->key_size;
	काष्ठा hlist_head *head;
	पूर्णांक i = 0;

	अगर (!key)
		जाओ find_first_elem;
	hash = sock_hash_bucket_hash(key, key_size);
	head = &sock_hash_select_bucket(htab, hash)->head;
	elem = sock_hash_lookup_elem_raw(head, hash, key, key_size);
	अगर (!elem)
		जाओ find_first_elem;

	elem_next = hlist_entry_safe(rcu_dereference(hlist_next_rcu(&elem->node)),
				     काष्ठा bpf_shtab_elem, node);
	अगर (elem_next) अणु
		स_नकल(key_next, elem_next->key, key_size);
		वापस 0;
	पूर्ण

	i = hash & (htab->buckets_num - 1);
	i++;
find_first_elem:
	क्रम (; i < htab->buckets_num; i++) अणु
		head = &sock_hash_select_bucket(htab, i)->head;
		elem_next = hlist_entry_safe(rcu_dereference(hlist_first_rcu(head)),
					     काष्ठा bpf_shtab_elem, node);
		अगर (elem_next) अणु
			स_नकल(key_next, elem_next->key, key_size);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल काष्ठा bpf_map *sock_hash_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_shtab *htab;
	पूर्णांक i, err;

	अगर (!capable(CAP_NET_ADMIN))
		वापस ERR_PTR(-EPERM);
	अगर (attr->max_entries == 0 ||
	    attr->key_size    == 0 ||
	    (attr->value_size != माप(u32) &&
	     attr->value_size != माप(u64)) ||
	    attr->map_flags & ~SOCK_CREATE_FLAG_MASK)
		वापस ERR_PTR(-EINVAL);
	अगर (attr->key_size > MAX_BPF_STACK)
		वापस ERR_PTR(-E2BIG);

	htab = kzalloc(माप(*htab), GFP_USER | __GFP_ACCOUNT);
	अगर (!htab)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&htab->map, attr);

	htab->buckets_num = roundup_घात_of_two(htab->map.max_entries);
	htab->elem_size = माप(काष्ठा bpf_shtab_elem) +
			  round_up(htab->map.key_size, 8);
	अगर (htab->buckets_num == 0 ||
	    htab->buckets_num > U32_MAX / माप(काष्ठा bpf_shtab_bucket)) अणु
		err = -EINVAL;
		जाओ मुक्त_htab;
	पूर्ण

	htab->buckets = bpf_map_area_alloc(htab->buckets_num *
					   माप(काष्ठा bpf_shtab_bucket),
					   htab->map.numa_node);
	अगर (!htab->buckets) अणु
		err = -ENOMEM;
		जाओ मुक्त_htab;
	पूर्ण

	क्रम (i = 0; i < htab->buckets_num; i++) अणु
		INIT_HLIST_HEAD(&htab->buckets[i].head);
		raw_spin_lock_init(&htab->buckets[i].lock);
	पूर्ण

	वापस &htab->map;
मुक्त_htab:
	kमुक्त(htab);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम sock_hash_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_shtab *htab = container_of(map, काष्ठा bpf_shtab, map);
	काष्ठा bpf_shtab_bucket *bucket;
	काष्ठा hlist_head unlink_list;
	काष्ठा bpf_shtab_elem *elem;
	काष्ठा hlist_node *node;
	पूर्णांक i;

	/* After the sync no updates or deletes will be in-flight so it
	 * is safe to walk map and हटाओ entries without risking a race
	 * in EEXIST update हाल.
	 */
	synchronize_rcu();
	क्रम (i = 0; i < htab->buckets_num; i++) अणु
		bucket = sock_hash_select_bucket(htab, i);

		/* We are racing with sock_hash_delete_from_link to
		 * enter the spin-lock critical section. Every socket on
		 * the list is still linked to sockhash. Since link
		 * exists, psock exists and holds a ref to socket. That
		 * lets us to grab a socket ref too.
		 */
		raw_spin_lock_bh(&bucket->lock);
		hlist_क्रम_each_entry(elem, &bucket->head, node)
			sock_hold(elem->sk);
		hlist_move_list(&bucket->head, &unlink_list);
		raw_spin_unlock_bh(&bucket->lock);

		/* Process हटाओd entries out of atomic context to
		 * block क्रम socket lock beक्रमe deleting the psock's
		 * link to sockhash.
		 */
		hlist_क्रम_each_entry_safe(elem, node, &unlink_list, node) अणु
			hlist_del(&elem->node);
			lock_sock(elem->sk);
			rcu_पढ़ो_lock();
			sock_map_unref(elem->sk, elem);
			rcu_पढ़ो_unlock();
			release_sock(elem->sk);
			sock_put(elem->sk);
			sock_hash_मुक्त_elem(htab, elem);
		पूर्ण
	पूर्ण

	/* रुको क्रम psock पढ़ोers accessing its map link */
	synchronize_rcu();

	bpf_map_area_मुक्त(htab->buckets);
	kमुक्त(htab);
पूर्ण

अटल व्योम *sock_hash_lookup_sys(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा sock *sk;

	अगर (map->value_size != माप(u64))
		वापस ERR_PTR(-ENOSPC);

	sk = __sock_hash_lookup_elem(map, key);
	अगर (!sk)
		वापस ERR_PTR(-ENOENT);

	__sock_gen_cookie(sk);
	वापस &sk->sk_cookie;
पूर्ण

अटल व्योम *sock_hash_lookup(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा sock *sk;

	sk = __sock_hash_lookup_elem(map, key);
	अगर (!sk)
		वापस शून्य;
	अगर (sk_is_refcounted(sk) && !refcount_inc_not_zero(&sk->sk_refcnt))
		वापस शून्य;
	वापस sk;
पूर्ण

अटल व्योम sock_hash_release_progs(काष्ठा bpf_map *map)
अणु
	psock_progs_drop(&container_of(map, काष्ठा bpf_shtab, map)->progs);
पूर्ण

BPF_CALL_4(bpf_sock_hash_update, काष्ठा bpf_sock_ops_kern *, sops,
	   काष्ठा bpf_map *, map, व्योम *, key, u64, flags)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	अगर (likely(sock_map_sk_is_suitable(sops->sk) &&
		   sock_map_op_okay(sops)))
		वापस sock_hash_update_common(map, key, sops->sk, flags);
	वापस -EOPNOTSUPP;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sock_hash_update_proto = अणु
	.func		= bpf_sock_hash_update,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_PTR_TO_MAP_KEY,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_sk_redirect_hash, काष्ठा sk_buff *, skb,
	   काष्ठा bpf_map *, map, व्योम *, key, u64, flags)
अणु
	काष्ठा sock *sk;

	अगर (unlikely(flags & ~(BPF_F_INGRESS)))
		वापस SK_DROP;

	sk = __sock_hash_lookup_elem(map, key);
	अगर (unlikely(!sk || !sock_map_redirect_allowed(sk)))
		वापस SK_DROP;

	skb_bpf_set_redir(skb, sk, flags & BPF_F_INGRESS);
	वापस SK_PASS;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sk_redirect_hash_proto = अणु
	.func           = bpf_sk_redirect_hash,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type      = ARG_CONST_MAP_PTR,
	.arg3_type      = ARG_PTR_TO_MAP_KEY,
	.arg4_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_msg_redirect_hash, काष्ठा sk_msg *, msg,
	   काष्ठा bpf_map *, map, व्योम *, key, u64, flags)
अणु
	काष्ठा sock *sk;

	अगर (unlikely(flags & ~(BPF_F_INGRESS)))
		वापस SK_DROP;

	sk = __sock_hash_lookup_elem(map, key);
	अगर (unlikely(!sk || !sock_map_redirect_allowed(sk)))
		वापस SK_DROP;

	msg->flags = flags;
	msg->sk_redir = sk;
	वापस SK_PASS;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_msg_redirect_hash_proto = अणु
	.func           = bpf_msg_redirect_hash,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type      = ARG_CONST_MAP_PTR,
	.arg3_type      = ARG_PTR_TO_MAP_KEY,
	.arg4_type      = ARG_ANYTHING,
पूर्ण;

काष्ठा sock_hash_seq_info अणु
	काष्ठा bpf_map *map;
	काष्ठा bpf_shtab *htab;
	u32 bucket_id;
पूर्ण;

अटल व्योम *sock_hash_seq_find_next(काष्ठा sock_hash_seq_info *info,
				     काष्ठा bpf_shtab_elem *prev_elem)
अणु
	स्थिर काष्ठा bpf_shtab *htab = info->htab;
	काष्ठा bpf_shtab_bucket *bucket;
	काष्ठा bpf_shtab_elem *elem;
	काष्ठा hlist_node *node;

	/* try to find next elem in the same bucket */
	अगर (prev_elem) अणु
		node = rcu_dereference(hlist_next_rcu(&prev_elem->node));
		elem = hlist_entry_safe(node, काष्ठा bpf_shtab_elem, node);
		अगर (elem)
			वापस elem;

		/* no more elements, जारी in the next bucket */
		info->bucket_id++;
	पूर्ण

	क्रम (; info->bucket_id < htab->buckets_num; info->bucket_id++) अणु
		bucket = &htab->buckets[info->bucket_id];
		node = rcu_dereference(hlist_first_rcu(&bucket->head));
		elem = hlist_entry_safe(node, काष्ठा bpf_shtab_elem, node);
		अगर (elem)
			वापस elem;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *sock_hash_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	काष्ठा sock_hash_seq_info *info = seq->निजी;

	अगर (*pos == 0)
		++*pos;

	/* pairs with sock_hash_seq_stop */
	rcu_पढ़ो_lock();
	वापस sock_hash_seq_find_next(info, शून्य);
पूर्ण

अटल व्योम *sock_hash_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
	__must_hold(rcu)
अणु
	काष्ठा sock_hash_seq_info *info = seq->निजी;

	++*pos;
	वापस sock_hash_seq_find_next(info, v);
पूर्ण

अटल पूर्णांक sock_hash_seq_show(काष्ठा seq_file *seq, व्योम *v)
	__must_hold(rcu)
अणु
	काष्ठा sock_hash_seq_info *info = seq->निजी;
	काष्ठा bpf_iter__sockmap ctx = अणुपूर्ण;
	काष्ठा bpf_shtab_elem *elem = v;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, !elem);
	अगर (!prog)
		वापस 0;

	ctx.meta = &meta;
	ctx.map = info->map;
	अगर (elem) अणु
		ctx.key = elem->key;
		ctx.sk = elem->sk;
	पूर्ण

	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल व्योम sock_hash_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	अगर (!v)
		(व्योम)sock_hash_seq_show(seq, शून्य);

	/* pairs with sock_hash_seq_start */
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर काष्ठा seq_operations sock_hash_seq_ops = अणु
	.start	= sock_hash_seq_start,
	.next	= sock_hash_seq_next,
	.stop	= sock_hash_seq_stop,
	.show	= sock_hash_seq_show,
पूर्ण;

अटल पूर्णांक sock_hash_init_seq_निजी(व्योम *priv_data,
				     काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा sock_hash_seq_info *info = priv_data;

	info->map = aux->map;
	info->htab = container_of(aux->map, काष्ठा bpf_shtab, map);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_iter_seq_info sock_hash_iter_seq_info = अणु
	.seq_ops		= &sock_hash_seq_ops,
	.init_seq_निजी	= sock_hash_init_seq_निजी,
	.seq_priv_size		= माप(काष्ठा sock_hash_seq_info),
पूर्ण;

अटल पूर्णांक sock_hash_map_btf_id;
स्थिर काष्ठा bpf_map_ops sock_hash_ops = अणु
	.map_meta_equal		= bpf_map_meta_equal,
	.map_alloc		= sock_hash_alloc,
	.map_मुक्त		= sock_hash_मुक्त,
	.map_get_next_key	= sock_hash_get_next_key,
	.map_update_elem	= sock_map_update_elem,
	.map_delete_elem	= sock_hash_delete_elem,
	.map_lookup_elem	= sock_hash_lookup,
	.map_lookup_elem_sys_only = sock_hash_lookup_sys,
	.map_release_uref	= sock_hash_release_progs,
	.map_check_btf		= map_check_no_btf,
	.map_btf_name		= "bpf_shtab",
	.map_btf_id		= &sock_hash_map_btf_id,
	.iter_seq_info		= &sock_hash_iter_seq_info,
पूर्ण;

अटल काष्ठा sk_psock_progs *sock_map_progs(काष्ठा bpf_map *map)
अणु
	चयन (map->map_type) अणु
	हाल BPF_MAP_TYPE_SOCKMAP:
		वापस &container_of(map, काष्ठा bpf_stab, map)->progs;
	हाल BPF_MAP_TYPE_SOCKHASH:
		वापस &container_of(map, काष्ठा bpf_shtab, map)->progs;
	शेष:
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sock_map_prog_update(काष्ठा bpf_map *map, काष्ठा bpf_prog *prog,
				काष्ठा bpf_prog *old, u32 which)
अणु
	काष्ठा sk_psock_progs *progs = sock_map_progs(map);
	काष्ठा bpf_prog **pprog;

	अगर (!progs)
		वापस -EOPNOTSUPP;

	चयन (which) अणु
	हाल BPF_SK_MSG_VERDICT:
		pprog = &progs->msg_parser;
		अवरोध;
#अगर IS_ENABLED(CONFIG_BPF_STREAM_PARSER)
	हाल BPF_SK_SKB_STREAM_PARSER:
		pprog = &progs->stream_parser;
		अवरोध;
#पूर्ण_अगर
	हाल BPF_SK_SKB_STREAM_VERDICT:
		अगर (progs->skb_verdict)
			वापस -EBUSY;
		pprog = &progs->stream_verdict;
		अवरोध;
	हाल BPF_SK_SKB_VERDICT:
		अगर (progs->stream_verdict)
			वापस -EBUSY;
		pprog = &progs->skb_verdict;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (old)
		वापस psock_replace_prog(pprog, prog, old);

	psock_set_prog(pprog, prog);
	वापस 0;
पूर्ण

अटल व्योम sock_map_unlink(काष्ठा sock *sk, काष्ठा sk_psock_link *link)
अणु
	चयन (link->map->map_type) अणु
	हाल BPF_MAP_TYPE_SOCKMAP:
		वापस sock_map_delete_from_link(link->map, sk,
						 link->link_raw);
	हाल BPF_MAP_TYPE_SOCKHASH:
		वापस sock_hash_delete_from_link(link->map, sk,
						  link->link_raw);
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sock_map_हटाओ_links(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	काष्ठा sk_psock_link *link;

	जबतक ((link = sk_psock_link_pop(psock))) अणु
		sock_map_unlink(sk, link);
		sk_psock_मुक्त_link(link);
	पूर्ण
पूर्ण

व्योम sock_map_unhash(काष्ठा sock *sk)
अणु
	व्योम (*saved_unhash)(काष्ठा sock *sk);
	काष्ठा sk_psock *psock;

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (unlikely(!psock)) अणु
		rcu_पढ़ो_unlock();
		अगर (sk->sk_prot->unhash)
			sk->sk_prot->unhash(sk);
		वापस;
	पूर्ण

	saved_unhash = psock->saved_unhash;
	sock_map_हटाओ_links(sk, psock);
	rcu_पढ़ो_unlock();
	saved_unhash(sk);
पूर्ण

व्योम sock_map_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	व्योम (*saved_बंद)(काष्ठा sock *sk, दीर्घ समयout);
	काष्ठा sk_psock *psock;

	lock_sock(sk);
	rcu_पढ़ो_lock();
	psock = sk_psock_get(sk);
	अगर (unlikely(!psock)) अणु
		rcu_पढ़ो_unlock();
		release_sock(sk);
		वापस sk->sk_prot->बंद(sk, समयout);
	पूर्ण

	saved_बंद = psock->saved_बंद;
	sock_map_हटाओ_links(sk, psock);
	rcu_पढ़ो_unlock();
	sk_psock_stop(psock, true);
	sk_psock_put(sk, psock);
	release_sock(sk);
	saved_बंद(sk, समयout);
पूर्ण

अटल पूर्णांक sock_map_iter_attach_target(काष्ठा bpf_prog *prog,
				       जोड़ bpf_iter_link_info *linfo,
				       काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा bpf_map *map;
	पूर्णांक err = -EINVAL;

	अगर (!linfo->map.map_fd)
		वापस -EBADF;

	map = bpf_map_get_with_uref(linfo->map.map_fd);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	अगर (map->map_type != BPF_MAP_TYPE_SOCKMAP &&
	    map->map_type != BPF_MAP_TYPE_SOCKHASH)
		जाओ put_map;

	अगर (prog->aux->max_rकरोnly_access > map->key_size) अणु
		err = -EACCES;
		जाओ put_map;
	पूर्ण

	aux->map = map;
	वापस 0;

put_map:
	bpf_map_put_with_uref(map);
	वापस err;
पूर्ण

अटल व्योम sock_map_iter_detach_target(काष्ठा bpf_iter_aux_info *aux)
अणु
	bpf_map_put_with_uref(aux->map);
पूर्ण

अटल काष्ठा bpf_iter_reg sock_map_iter_reg = अणु
	.target			= "sockmap",
	.attach_target		= sock_map_iter_attach_target,
	.detach_target		= sock_map_iter_detach_target,
	.show_fdinfo		= bpf_iter_map_show_fdinfo,
	.fill_link_info		= bpf_iter_map_fill_link_info,
	.ctx_arg_info_size	= 2,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__sockmap, key),
		  PTR_TO_RDONLY_BUF_OR_शून्य पूर्ण,
		अणु दुरत्व(काष्ठा bpf_iter__sockmap, sk),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init bpf_sockmap_iter_init(व्योम)
अणु
	sock_map_iter_reg.ctx_arg_info[1].btf_id =
		btf_sock_ids[BTF_SOCK_TYPE_SOCK];
	वापस bpf_iter_reg_target(&sock_map_iter_reg);
पूर्ण
late_initcall(bpf_sockmap_iter_init);
