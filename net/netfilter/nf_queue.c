<शैली गुरु>
/*
 * Rusty Russell (C)2000 -- This code is GPL.
 * Patrick McHardy (c) 2006-2012
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/protocol.h>
#समावेश <net/netfilter/nf_queue.h>
#समावेश <net/dst.h>

#समावेश "nf_internals.h"

/*
 * Hook क्रम nfnetlink_queue to रेजिस्टर its queue handler.
 * We करो this so that most of the NFQUEUE code can be modular.
 *
 * Once the queue is रेजिस्टरed it must reinject all packets it
 * receives, no matter what.
 */

/* वापस EBUSY when somebody अन्यथा is रेजिस्टरed, वापस EEXIST अगर the
 * same handler is रेजिस्टरed, वापस 0 in हाल of success. */
व्योम nf_रेजिस्टर_queue_handler(काष्ठा net *net, स्थिर काष्ठा nf_queue_handler *qh)
अणु
	/* should never happen, we only have one queueing backend in kernel */
	WARN_ON(rcu_access_poपूर्णांकer(net->nf.queue_handler));
	rcu_assign_poपूर्णांकer(net->nf.queue_handler, qh);
पूर्ण
EXPORT_SYMBOL(nf_रेजिस्टर_queue_handler);

/* The caller must flush their queue beक्रमe this */
व्योम nf_unरेजिस्टर_queue_handler(काष्ठा net *net)
अणु
	RCU_INIT_POINTER(net->nf.queue_handler, शून्य);
पूर्ण
EXPORT_SYMBOL(nf_unरेजिस्टर_queue_handler);

अटल व्योम nf_queue_entry_release_refs(काष्ठा nf_queue_entry *entry)
अणु
	काष्ठा nf_hook_state *state = &entry->state;

	/* Release those devices we held, or Alexey will समाप्त me. */
	अगर (state->in)
		dev_put(state->in);
	अगर (state->out)
		dev_put(state->out);
	अगर (state->sk)
		sock_put(state->sk);

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	अगर (entry->physin)
		dev_put(entry->physin);
	अगर (entry->physout)
		dev_put(entry->physout);
#पूर्ण_अगर
पूर्ण

व्योम nf_queue_entry_मुक्त(काष्ठा nf_queue_entry *entry)
अणु
	nf_queue_entry_release_refs(entry);
	kमुक्त(entry);
पूर्ण
EXPORT_SYMBOL_GPL(nf_queue_entry_मुक्त);

अटल व्योम __nf_queue_entry_init_physdevs(काष्ठा nf_queue_entry *entry)
अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	स्थिर काष्ठा sk_buff *skb = entry->skb;
	काष्ठा nf_bridge_info *nf_bridge;

	nf_bridge = nf_bridge_info_get(skb);
	अगर (nf_bridge) अणु
		entry->physin = nf_bridge_get_physindev(skb);
		entry->physout = nf_bridge_get_physoutdev(skb);
	पूर्ण अन्यथा अणु
		entry->physin = शून्य;
		entry->physout = शून्य;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Bump dev refs so they करोn't vanish जबतक packet is out */
व्योम nf_queue_entry_get_refs(काष्ठा nf_queue_entry *entry)
अणु
	काष्ठा nf_hook_state *state = &entry->state;

	अगर (state->in)
		dev_hold(state->in);
	अगर (state->out)
		dev_hold(state->out);
	अगर (state->sk)
		sock_hold(state->sk);

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	अगर (entry->physin)
		dev_hold(entry->physin);
	अगर (entry->physout)
		dev_hold(entry->physout);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(nf_queue_entry_get_refs);

व्योम nf_queue_nf_hook_drop(काष्ठा net *net)
अणु
	स्थिर काष्ठा nf_queue_handler *qh;

	rcu_पढ़ो_lock();
	qh = rcu_dereference(net->nf.queue_handler);
	अगर (qh)
		qh->nf_hook_drop(net);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(nf_queue_nf_hook_drop);

अटल व्योम nf_ip_saveroute(स्थिर काष्ठा sk_buff *skb,
			    काष्ठा nf_queue_entry *entry)
अणु
	काष्ठा ip_rt_info *rt_info = nf_queue_entry_reroute(entry);

	अगर (entry->state.hook == NF_INET_LOCAL_OUT) अणु
		स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

		rt_info->tos = iph->tos;
		rt_info->daddr = iph->daddr;
		rt_info->saddr = iph->saddr;
		rt_info->mark = skb->mark;
	पूर्ण
पूर्ण

अटल व्योम nf_ip6_saveroute(स्थिर काष्ठा sk_buff *skb,
			     काष्ठा nf_queue_entry *entry)
अणु
	काष्ठा ip6_rt_info *rt_info = nf_queue_entry_reroute(entry);

	अगर (entry->state.hook == NF_INET_LOCAL_OUT) अणु
		स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

		rt_info->daddr = iph->daddr;
		rt_info->saddr = iph->saddr;
		rt_info->mark = skb->mark;
	पूर्ण
पूर्ण

अटल पूर्णांक __nf_queue(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_hook_state *state,
		      अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक queuक्रमागत)
अणु
	काष्ठा nf_queue_entry *entry = शून्य;
	स्थिर काष्ठा nf_queue_handler *qh;
	काष्ठा net *net = state->net;
	अचिन्हित पूर्णांक route_key_size;
	पूर्णांक status;

	/* QUEUE == DROP अगर no one is रुकोing, to be safe. */
	qh = rcu_dereference(net->nf.queue_handler);
	अगर (!qh)
		वापस -ESRCH;

	चयन (state->pf) अणु
	हाल AF_INET:
		route_key_size = माप(काष्ठा ip_rt_info);
		अवरोध;
	हाल AF_INET6:
		route_key_size = माप(काष्ठा ip6_rt_info);
		अवरोध;
	शेष:
		route_key_size = 0;
		अवरोध;
	पूर्ण

	entry = kदो_स्मृति(माप(*entry) + route_key_size, GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;

	अगर (skb_dst(skb) && !skb_dst_क्रमce(skb)) अणु
		kमुक्त(entry);
		वापस -ENETDOWN;
	पूर्ण

	*entry = (काष्ठा nf_queue_entry) अणु
		.skb	= skb,
		.state	= *state,
		.hook_index = index,
		.size	= माप(*entry) + route_key_size,
	पूर्ण;

	__nf_queue_entry_init_physdevs(entry);

	nf_queue_entry_get_refs(entry);

	चयन (entry->state.pf) अणु
	हाल AF_INET:
		nf_ip_saveroute(skb, entry);
		अवरोध;
	हाल AF_INET6:
		nf_ip6_saveroute(skb, entry);
		अवरोध;
	पूर्ण

	status = qh->outfn(entry, queuक्रमागत);
	अगर (status < 0) अणु
		nf_queue_entry_मुक्त(entry);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

/* Packets leaving via this function must come back through nf_reinject(). */
पूर्णांक nf_queue(काष्ठा sk_buff *skb, काष्ठा nf_hook_state *state,
	     अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक verdict)
अणु
	पूर्णांक ret;

	ret = __nf_queue(skb, state, index, verdict >> NF_VERDICT_QBITS);
	अगर (ret < 0) अणु
		अगर (ret == -ESRCH &&
		    (verdict & NF_VERDICT_FLAG_QUEUE_BYPASS))
			वापस 1;
		kमुक्त_skb(skb);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_queue);

अटल अचिन्हित पूर्णांक nf_iterate(काष्ठा sk_buff *skb,
			       काष्ठा nf_hook_state *state,
			       स्थिर काष्ठा nf_hook_entries *hooks,
			       अचिन्हित पूर्णांक *index)
अणु
	स्थिर काष्ठा nf_hook_entry *hook;
	अचिन्हित पूर्णांक verdict, i = *index;

	जबतक (i < hooks->num_hook_entries) अणु
		hook = &hooks->hooks[i];
repeat:
		verdict = nf_hook_entry_hookfn(hook, skb, state);
		अगर (verdict != NF_ACCEPT) अणु
			*index = i;
			अगर (verdict != NF_REPEAT)
				वापस verdict;
			जाओ repeat;
		पूर्ण
		i++;
	पूर्ण

	*index = i;
	वापस NF_ACCEPT;
पूर्ण

अटल काष्ठा nf_hook_entries *nf_hook_entries_head(स्थिर काष्ठा net *net, u8 pf, u8 hooknum)
अणु
	चयन (pf) अणु
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
	हाल NFPROTO_BRIDGE:
		वापस rcu_dereference(net->nf.hooks_bridge[hooknum]);
#पूर्ण_अगर
	हाल NFPROTO_IPV4:
		वापस rcu_dereference(net->nf.hooks_ipv4[hooknum]);
	हाल NFPROTO_IPV6:
		वापस rcu_dereference(net->nf.hooks_ipv6[hooknum]);
	शेष:
		WARN_ON_ONCE(1);
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Caller must hold rcu पढ़ो-side lock */
व्योम nf_reinject(काष्ठा nf_queue_entry *entry, अचिन्हित पूर्णांक verdict)
अणु
	स्थिर काष्ठा nf_hook_entry *hook_entry;
	स्थिर काष्ठा nf_hook_entries *hooks;
	काष्ठा sk_buff *skb = entry->skb;
	स्थिर काष्ठा net *net;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	u8 pf;

	net = entry->state.net;
	pf = entry->state.pf;

	hooks = nf_hook_entries_head(net, pf, entry->state.hook);

	i = entry->hook_index;
	अगर (WARN_ON_ONCE(!hooks || i >= hooks->num_hook_entries)) अणु
		kमुक्त_skb(skb);
		nf_queue_entry_मुक्त(entry);
		वापस;
	पूर्ण

	hook_entry = &hooks->hooks[i];

	/* Continue traversal अगरf userspace said ok... */
	अगर (verdict == NF_REPEAT)
		verdict = nf_hook_entry_hookfn(hook_entry, skb, &entry->state);

	अगर (verdict == NF_ACCEPT) अणु
		अगर (nf_reroute(skb, entry) < 0)
			verdict = NF_DROP;
	पूर्ण

	अगर (verdict == NF_ACCEPT) अणु
next_hook:
		++i;
		verdict = nf_iterate(skb, &entry->state, hooks, &i);
	पूर्ण

	चयन (verdict & NF_VERDICT_MASK) अणु
	हाल NF_ACCEPT:
	हाल NF_STOP:
		local_bh_disable();
		entry->state.okfn(entry->state.net, entry->state.sk, skb);
		local_bh_enable();
		अवरोध;
	हाल NF_QUEUE:
		err = nf_queue(skb, &entry->state, i, verdict);
		अगर (err == 1)
			जाओ next_hook;
		अवरोध;
	हाल NF_STOLEN:
		अवरोध;
	शेष:
		kमुक्त_skb(skb);
	पूर्ण

	nf_queue_entry_मुक्त(entry);
पूर्ण
EXPORT_SYMBOL(nf_reinject);
