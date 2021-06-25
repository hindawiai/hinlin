<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * To speed up listener socket lookup, create an array to store all sockets
 * listening on the same port.  This allows a decision to be made after finding
 * the first socket.  An optional BPF program can also be configured क्रम
 * selecting the socket index from the array of available sockets.
 */

#समावेश <net/sock_reuseport.h>
#समावेश <linux/bpf.h>
#समावेश <linux/idr.h>
#समावेश <linux/filter.h>
#समावेश <linux/rcupdate.h>

#घोषणा INIT_SOCKS 128

DEFINE_SPINLOCK(reuseport_lock);

अटल DEFINE_IDA(reuseport_ida);

अटल काष्ठा sock_reuseport *__reuseport_alloc(अचिन्हित पूर्णांक max_socks)
अणु
	अचिन्हित पूर्णांक size = माप(काष्ठा sock_reuseport) +
		      माप(काष्ठा sock *) * max_socks;
	काष्ठा sock_reuseport *reuse = kzalloc(size, GFP_ATOMIC);

	अगर (!reuse)
		वापस शून्य;

	reuse->max_socks = max_socks;

	RCU_INIT_POINTER(reuse->prog, शून्य);
	वापस reuse;
पूर्ण

पूर्णांक reuseport_alloc(काष्ठा sock *sk, bool bind_inany)
अणु
	काष्ठा sock_reuseport *reuse;
	पूर्णांक id, ret = 0;

	/* bh lock used since this function call may precede hlist lock in
	 * soft irq of receive path or setsockopt from process context
	 */
	spin_lock_bh(&reuseport_lock);

	/* Allocation attempts can occur concurrently via the setsockopt path
	 * and the bind/hash path.  Nothing to करो when we lose the race.
	 */
	reuse = rcu_dereference_रक्षित(sk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	अगर (reuse) अणु
		/* Only set reuse->bind_inany अगर the bind_inany is true.
		 * Otherwise, it will overग_लिखो the reuse->bind_inany
		 * which was set by the bind/hash path.
		 */
		अगर (bind_inany)
			reuse->bind_inany = bind_inany;
		जाओ out;
	पूर्ण

	reuse = __reuseport_alloc(INIT_SOCKS);
	अगर (!reuse) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	id = ida_alloc(&reuseport_ida, GFP_ATOMIC);
	अगर (id < 0) अणु
		kमुक्त(reuse);
		ret = id;
		जाओ out;
	पूर्ण

	reuse->reuseport_id = id;
	reuse->socks[0] = sk;
	reuse->num_socks = 1;
	reuse->bind_inany = bind_inany;
	rcu_assign_poपूर्णांकer(sk->sk_reuseport_cb, reuse);

out:
	spin_unlock_bh(&reuseport_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(reuseport_alloc);

अटल काष्ठा sock_reuseport *reuseport_grow(काष्ठा sock_reuseport *reuse)
अणु
	काष्ठा sock_reuseport *more_reuse;
	u32 more_socks_size, i;

	more_socks_size = reuse->max_socks * 2U;
	अगर (more_socks_size > U16_MAX)
		वापस शून्य;

	more_reuse = __reuseport_alloc(more_socks_size);
	अगर (!more_reuse)
		वापस शून्य;

	more_reuse->num_socks = reuse->num_socks;
	more_reuse->prog = reuse->prog;
	more_reuse->reuseport_id = reuse->reuseport_id;
	more_reuse->bind_inany = reuse->bind_inany;
	more_reuse->has_conns = reuse->has_conns;

	स_नकल(more_reuse->socks, reuse->socks,
	       reuse->num_socks * माप(काष्ठा sock *));
	more_reuse->synq_overflow_ts = READ_ONCE(reuse->synq_overflow_ts);

	क्रम (i = 0; i < reuse->num_socks; ++i)
		rcu_assign_poपूर्णांकer(reuse->socks[i]->sk_reuseport_cb,
				   more_reuse);

	/* Note: we use kमुक्त_rcu here instead of reuseport_मुक्त_rcu so
	 * that reuse and more_reuse can temporarily share a reference
	 * to prog.
	 */
	kमुक्त_rcu(reuse, rcu);
	वापस more_reuse;
पूर्ण

अटल व्योम reuseport_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा sock_reuseport *reuse;

	reuse = container_of(head, काष्ठा sock_reuseport, rcu);
	sk_reuseport_prog_मुक्त(rcu_dereference_रक्षित(reuse->prog, 1));
	ida_मुक्त(&reuseport_ida, reuse->reuseport_id);
	kमुक्त(reuse);
पूर्ण

/**
 *  reuseport_add_sock - Add a socket to the reuseport group of another.
 *  @sk:  New socket to add to the group.
 *  @sk2: Socket beदीर्घing to the existing reuseport group.
 *  @bind_inany: Whether or not the group is bound to a local Iन_अंकY address.
 *
 *  May वापस ENOMEM and not add socket to group under memory pressure.
 */
पूर्णांक reuseport_add_sock(काष्ठा sock *sk, काष्ठा sock *sk2, bool bind_inany)
अणु
	काष्ठा sock_reuseport *old_reuse, *reuse;

	अगर (!rcu_access_poपूर्णांकer(sk2->sk_reuseport_cb)) अणु
		पूर्णांक err = reuseport_alloc(sk2, bind_inany);

		अगर (err)
			वापस err;
	पूर्ण

	spin_lock_bh(&reuseport_lock);
	reuse = rcu_dereference_रक्षित(sk2->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	old_reuse = rcu_dereference_रक्षित(sk->sk_reuseport_cb,
					     lockdep_is_held(&reuseport_lock));
	अगर (old_reuse && old_reuse->num_socks != 1) अणु
		spin_unlock_bh(&reuseport_lock);
		वापस -EBUSY;
	पूर्ण

	अगर (reuse->num_socks == reuse->max_socks) अणु
		reuse = reuseport_grow(reuse);
		अगर (!reuse) अणु
			spin_unlock_bh(&reuseport_lock);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	reuse->socks[reuse->num_socks] = sk;
	/* paired with smp_rmb() in reuseport_select_sock() */
	smp_wmb();
	reuse->num_socks++;
	rcu_assign_poपूर्णांकer(sk->sk_reuseport_cb, reuse);

	spin_unlock_bh(&reuseport_lock);

	अगर (old_reuse)
		call_rcu(&old_reuse->rcu, reuseport_मुक्त_rcu);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(reuseport_add_sock);

व्योम reuseport_detach_sock(काष्ठा sock *sk)
अणु
	काष्ठा sock_reuseport *reuse;
	पूर्णांक i;

	spin_lock_bh(&reuseport_lock);
	reuse = rcu_dereference_रक्षित(sk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));

	/* Notअगरy the bpf side. The sk may be added to a sockarray
	 * map. If so, sockarray logic will हटाओ it from the map.
	 *
	 * Other bpf map types that work with reuseport, like sockmap,
	 * करोn't need an explicit callback from here. They override sk
	 * unhash/बंद ops to हटाओ the sk from the map beक्रमe we
	 * get to this poपूर्णांक.
	 */
	bpf_sk_reuseport_detach(sk);

	rcu_assign_poपूर्णांकer(sk->sk_reuseport_cb, शून्य);

	क्रम (i = 0; i < reuse->num_socks; i++) अणु
		अगर (reuse->socks[i] == sk) अणु
			reuse->socks[i] = reuse->socks[reuse->num_socks - 1];
			reuse->num_socks--;
			अगर (reuse->num_socks == 0)
				call_rcu(&reuse->rcu, reuseport_मुक्त_rcu);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&reuseport_lock);
पूर्ण
EXPORT_SYMBOL(reuseport_detach_sock);

अटल काष्ठा sock *run_bpf_filter(काष्ठा sock_reuseport *reuse, u16 socks,
				   काष्ठा bpf_prog *prog, काष्ठा sk_buff *skb,
				   पूर्णांक hdr_len)
अणु
	काष्ठा sk_buff *nskb = शून्य;
	u32 index;

	अगर (skb_shared(skb)) अणु
		nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (!nskb)
			वापस शून्य;
		skb = nskb;
	पूर्ण

	/* temporarily advance data past protocol header */
	अगर (!pskb_pull(skb, hdr_len)) अणु
		kमुक्त_skb(nskb);
		वापस शून्य;
	पूर्ण
	index = bpf_prog_run_save_cb(prog, skb);
	__skb_push(skb, hdr_len);

	consume_skb(nskb);

	अगर (index >= socks)
		वापस शून्य;

	वापस reuse->socks[index];
पूर्ण

/**
 *  reuseport_select_sock - Select a socket from an SO_REUSEPORT group.
 *  @sk: First socket in the group.
 *  @hash: When no BPF filter is available, use this hash to select.
 *  @skb: skb to run through BPF filter.
 *  @hdr_len: BPF filter expects skb data poपूर्णांकer at payload data.  If
 *    the skb करोes not yet poपूर्णांक at the payload, this parameter represents
 *    how far the poपूर्णांकer needs to advance to reach the payload.
 *  Returns a socket that should receive the packet (or शून्य on error).
 */
काष्ठा sock *reuseport_select_sock(काष्ठा sock *sk,
				   u32 hash,
				   काष्ठा sk_buff *skb,
				   पूर्णांक hdr_len)
अणु
	काष्ठा sock_reuseport *reuse;
	काष्ठा bpf_prog *prog;
	काष्ठा sock *sk2 = शून्य;
	u16 socks;

	rcu_पढ़ो_lock();
	reuse = rcu_dereference(sk->sk_reuseport_cb);

	/* अगर memory allocation failed or add call is not yet complete */
	अगर (!reuse)
		जाओ out;

	prog = rcu_dereference(reuse->prog);
	socks = READ_ONCE(reuse->num_socks);
	अगर (likely(socks)) अणु
		/* paired with smp_wmb() in reuseport_add_sock() */
		smp_rmb();

		अगर (!prog || !skb)
			जाओ select_by_hash;

		अगर (prog->type == BPF_PROG_TYPE_SK_REUSEPORT)
			sk2 = bpf_run_sk_reuseport(reuse, sk, prog, skb, hash);
		अन्यथा
			sk2 = run_bpf_filter(reuse, socks, prog, skb, hdr_len);

select_by_hash:
		/* no bpf or invalid bpf result: fall back to hash usage */
		अगर (!sk2) अणु
			पूर्णांक i, j;

			i = j = reciprocal_scale(hash, socks);
			जबतक (reuse->socks[i]->sk_state == TCP_ESTABLISHED) अणु
				i++;
				अगर (i >= socks)
					i = 0;
				अगर (i == j)
					जाओ out;
			पूर्ण
			sk2 = reuse->socks[i];
		पूर्ण
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस sk2;
पूर्ण
EXPORT_SYMBOL(reuseport_select_sock);

पूर्णांक reuseport_attach_prog(काष्ठा sock *sk, काष्ठा bpf_prog *prog)
अणु
	काष्ठा sock_reuseport *reuse;
	काष्ठा bpf_prog *old_prog;

	अगर (sk_unhashed(sk) && sk->sk_reuseport) अणु
		पूर्णांक err = reuseport_alloc(sk, false);

		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (!rcu_access_poपूर्णांकer(sk->sk_reuseport_cb)) अणु
		/* The socket wasn't bound with SO_REUSEPORT */
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&reuseport_lock);
	reuse = rcu_dereference_रक्षित(sk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	old_prog = rcu_dereference_रक्षित(reuse->prog,
					     lockdep_is_held(&reuseport_lock));
	rcu_assign_poपूर्णांकer(reuse->prog, prog);
	spin_unlock_bh(&reuseport_lock);

	sk_reuseport_prog_मुक्त(old_prog);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(reuseport_attach_prog);

पूर्णांक reuseport_detach_prog(काष्ठा sock *sk)
अणु
	काष्ठा sock_reuseport *reuse;
	काष्ठा bpf_prog *old_prog;

	अगर (!rcu_access_poपूर्णांकer(sk->sk_reuseport_cb))
		वापस sk->sk_reuseport ? -ENOENT : -EINVAL;

	old_prog = शून्य;
	spin_lock_bh(&reuseport_lock);
	reuse = rcu_dereference_रक्षित(sk->sk_reuseport_cb,
					  lockdep_is_held(&reuseport_lock));
	old_prog = rcu_replace_poपूर्णांकer(reuse->prog, old_prog,
				       lockdep_is_held(&reuseport_lock));
	spin_unlock_bh(&reuseport_lock);

	अगर (!old_prog)
		वापस -ENOENT;

	sk_reuseport_prog_मुक्त(old_prog);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(reuseport_detach_prog);
