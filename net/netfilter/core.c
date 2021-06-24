<शैली गुरु>
/* netfilter.c: look after the filters क्रम various protocols.
 * Heavily influenced by the old firewall.c by David Bonn and Alan Cox.
 *
 * Thanks to Rob `CmdrTaco' Malda क्रम not influencing this code in any
 * way.
 *
 * This code is GPL.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/netfilter.h>
#समावेश <net/protocol.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netfilter/nf_queue.h>
#समावेश <net/sock.h>

#समावेश "nf_internals.h"

स्थिर काष्ठा nf_ipv6_ops __rcu *nf_ipv6_ops __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ipv6_ops);

DEFINE_PER_CPU(bool, nf_skb_duplicated);
EXPORT_SYMBOL_GPL(nf_skb_duplicated);

#अगर_घोषित CONFIG_JUMP_LABEL
काष्ठा अटल_key nf_hooks_needed[NFPROTO_NUMPROTO][NF_MAX_HOOKS];
EXPORT_SYMBOL(nf_hooks_needed);
#पूर्ण_अगर

अटल DEFINE_MUTEX(nf_hook_mutex);

/* max hooks per family/hooknum */
#घोषणा MAX_HOOK_COUNT		1024

#घोषणा nf_entry_dereference(e) \
	rcu_dereference_रक्षित(e, lockdep_is_held(&nf_hook_mutex))

अटल काष्ठा nf_hook_entries *allocate_hook_entries_size(u16 num)
अणु
	काष्ठा nf_hook_entries *e;
	माप_प्रकार alloc = माप(*e) +
		       माप(काष्ठा nf_hook_entry) * num +
		       माप(काष्ठा nf_hook_ops *) * num +
		       माप(काष्ठा nf_hook_entries_rcu_head);

	अगर (num == 0)
		वापस शून्य;

	e = kvzalloc(alloc, GFP_KERNEL);
	अगर (e)
		e->num_hook_entries = num;
	वापस e;
पूर्ण

अटल व्योम __nf_hook_entries_मुक्त(काष्ठा rcu_head *h)
अणु
	काष्ठा nf_hook_entries_rcu_head *head;

	head = container_of(h, काष्ठा nf_hook_entries_rcu_head, head);
	kvमुक्त(head->allocation);
पूर्ण

अटल व्योम nf_hook_entries_मुक्त(काष्ठा nf_hook_entries *e)
अणु
	काष्ठा nf_hook_entries_rcu_head *head;
	काष्ठा nf_hook_ops **ops;
	अचिन्हित पूर्णांक num;

	अगर (!e)
		वापस;

	num = e->num_hook_entries;
	ops = nf_hook_entries_get_hook_ops(e);
	head = (व्योम *)&ops[num];
	head->allocation = e;
	call_rcu(&head->head, __nf_hook_entries_मुक्त);
पूर्ण

अटल अचिन्हित पूर्णांक accept_all(व्योम *priv,
			       काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस NF_ACCEPT; /* ACCEPT makes nf_hook_slow call next hook */
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops dummy_ops = अणु
	.hook = accept_all,
	.priority = पूर्णांक_न्यून,
पूर्ण;

अटल काष्ठा nf_hook_entries *
nf_hook_entries_grow(स्थिर काष्ठा nf_hook_entries *old,
		     स्थिर काष्ठा nf_hook_ops *reg)
अणु
	अचिन्हित पूर्णांक i, alloc_entries, nhooks, old_entries;
	काष्ठा nf_hook_ops **orig_ops = शून्य;
	काष्ठा nf_hook_ops **new_ops;
	काष्ठा nf_hook_entries *new;
	bool inserted = false;

	alloc_entries = 1;
	old_entries = old ? old->num_hook_entries : 0;

	अगर (old) अणु
		orig_ops = nf_hook_entries_get_hook_ops(old);

		क्रम (i = 0; i < old_entries; i++) अणु
			अगर (orig_ops[i] != &dummy_ops)
				alloc_entries++;
		पूर्ण
	पूर्ण

	अगर (alloc_entries > MAX_HOOK_COUNT)
		वापस ERR_PTR(-E2BIG);

	new = allocate_hook_entries_size(alloc_entries);
	अगर (!new)
		वापस ERR_PTR(-ENOMEM);

	new_ops = nf_hook_entries_get_hook_ops(new);

	i = 0;
	nhooks = 0;
	जबतक (i < old_entries) अणु
		अगर (orig_ops[i] == &dummy_ops) अणु
			++i;
			जारी;
		पूर्ण

		अगर (inserted || reg->priority > orig_ops[i]->priority) अणु
			new_ops[nhooks] = (व्योम *)orig_ops[i];
			new->hooks[nhooks] = old->hooks[i];
			i++;
		पूर्ण अन्यथा अणु
			new_ops[nhooks] = (व्योम *)reg;
			new->hooks[nhooks].hook = reg->hook;
			new->hooks[nhooks].priv = reg->priv;
			inserted = true;
		पूर्ण
		nhooks++;
	पूर्ण

	अगर (!inserted) अणु
		new_ops[nhooks] = (व्योम *)reg;
		new->hooks[nhooks].hook = reg->hook;
		new->hooks[nhooks].priv = reg->priv;
	पूर्ण

	वापस new;
पूर्ण

अटल व्योम hooks_validate(स्थिर काष्ठा nf_hook_entries *hooks)
अणु
#अगर_घोषित CONFIG_DEBUG_MISC
	काष्ठा nf_hook_ops **orig_ops;
	पूर्णांक prio = पूर्णांक_न्यून;
	माप_प्रकार i = 0;

	orig_ops = nf_hook_entries_get_hook_ops(hooks);

	क्रम (i = 0; i < hooks->num_hook_entries; i++) अणु
		अगर (orig_ops[i] == &dummy_ops)
			जारी;

		WARN_ON(orig_ops[i]->priority < prio);

		अगर (orig_ops[i]->priority > prio)
			prio = orig_ops[i]->priority;
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक nf_hook_entries_insert_raw(काष्ठा nf_hook_entries __rcu **pp,
				स्थिर काष्ठा nf_hook_ops *reg)
अणु
	काष्ठा nf_hook_entries *new_hooks;
	काष्ठा nf_hook_entries *p;

	p = rcu_dereference_raw(*pp);
	new_hooks = nf_hook_entries_grow(p, reg);
	अगर (IS_ERR(new_hooks))
		वापस PTR_ERR(new_hooks);

	hooks_validate(new_hooks);

	rcu_assign_poपूर्णांकer(*pp, new_hooks);

	BUG_ON(p == new_hooks);
	nf_hook_entries_मुक्त(p);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_hook_entries_insert_raw);

/*
 * __nf_hook_entries_try_shrink - try to shrink hook array
 *
 * @old -- current hook blob at @pp
 * @pp -- location of hook blob
 *
 * Hook unregistration must always succeed, so to-be-हटाओd hooks
 * are replaced by a dummy one that will just move to next hook.
 *
 * This counts the current dummy hooks, attempts to allocate new blob,
 * copies the live hooks, then replaces and discards old one.
 *
 * वापस values:
 *
 * Returns address to मुक्त, or शून्य.
 */
अटल व्योम *__nf_hook_entries_try_shrink(काष्ठा nf_hook_entries *old,
					  काष्ठा nf_hook_entries __rcu **pp)
अणु
	अचिन्हित पूर्णांक i, j, skip = 0, hook_entries;
	काष्ठा nf_hook_entries *new = शून्य;
	काष्ठा nf_hook_ops **orig_ops;
	काष्ठा nf_hook_ops **new_ops;

	अगर (WARN_ON_ONCE(!old))
		वापस शून्य;

	orig_ops = nf_hook_entries_get_hook_ops(old);
	क्रम (i = 0; i < old->num_hook_entries; i++) अणु
		अगर (orig_ops[i] == &dummy_ops)
			skip++;
	पूर्ण

	/* अगर skip == hook_entries all hooks have been हटाओd */
	hook_entries = old->num_hook_entries;
	अगर (skip == hook_entries)
		जाओ out_assign;

	अगर (skip == 0)
		वापस शून्य;

	hook_entries -= skip;
	new = allocate_hook_entries_size(hook_entries);
	अगर (!new)
		वापस शून्य;

	new_ops = nf_hook_entries_get_hook_ops(new);
	क्रम (i = 0, j = 0; i < old->num_hook_entries; i++) अणु
		अगर (orig_ops[i] == &dummy_ops)
			जारी;
		new->hooks[j] = old->hooks[i];
		new_ops[j] = (व्योम *)orig_ops[i];
		j++;
	पूर्ण
	hooks_validate(new);
out_assign:
	rcu_assign_poपूर्णांकer(*pp, new);
	वापस old;
पूर्ण

अटल काष्ठा nf_hook_entries __rcu **
nf_hook_entry_head(काष्ठा net *net, पूर्णांक pf, अचिन्हित पूर्णांक hooknum,
		   काष्ठा net_device *dev)
अणु
	चयन (pf) अणु
	हाल NFPROTO_NETDEV:
		अवरोध;
#अगर_घोषित CONFIG_NETFILTER_FAMILY_ARP
	हाल NFPROTO_ARP:
		अगर (WARN_ON_ONCE(ARRAY_SIZE(net->nf.hooks_arp) <= hooknum))
			वापस शून्य;
		वापस net->nf.hooks_arp + hooknum;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
	हाल NFPROTO_BRIDGE:
		अगर (WARN_ON_ONCE(ARRAY_SIZE(net->nf.hooks_bridge) <= hooknum))
			वापस शून्य;
		वापस net->nf.hooks_bridge + hooknum;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER_INGRESS
	हाल NFPROTO_INET:
		अगर (WARN_ON_ONCE(hooknum != NF_INET_INGRESS))
			वापस शून्य;
		अगर (!dev || dev_net(dev) != net) अणु
			WARN_ON_ONCE(1);
			वापस शून्य;
		पूर्ण
		वापस &dev->nf_hooks_ingress;
#पूर्ण_अगर
	हाल NFPROTO_IPV4:
		अगर (WARN_ON_ONCE(ARRAY_SIZE(net->nf.hooks_ipv4) <= hooknum))
			वापस शून्य;
		वापस net->nf.hooks_ipv4 + hooknum;
	हाल NFPROTO_IPV6:
		अगर (WARN_ON_ONCE(ARRAY_SIZE(net->nf.hooks_ipv6) <= hooknum))
			वापस शून्य;
		वापस net->nf.hooks_ipv6 + hooknum;
#अगर IS_ENABLED(CONFIG_DECNET)
	हाल NFPROTO_DECNET:
		अगर (WARN_ON_ONCE(ARRAY_SIZE(net->nf.hooks_decnet) <= hooknum))
			वापस शून्य;
		वापस net->nf.hooks_decnet + hooknum;
#पूर्ण_अगर
	शेष:
		WARN_ON_ONCE(1);
		वापस शून्य;
	पूर्ण

#अगर_घोषित CONFIG_NETFILTER_INGRESS
	अगर (hooknum == NF_NETDEV_INGRESS) अणु
		अगर (dev && dev_net(dev) == net)
			वापस &dev->nf_hooks_ingress;
	पूर्ण
#पूर्ण_अगर
	WARN_ON_ONCE(1);
	वापस शून्य;
पूर्ण

अटल पूर्णांक nf_ingress_check(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *reg,
			    पूर्णांक hooknum)
अणु
#अगर_अघोषित CONFIG_NETFILTER_INGRESS
	अगर (reg->hooknum == hooknum)
		वापस -EOPNOTSUPP;
#पूर्ण_अगर
	अगर (reg->hooknum != hooknum ||
	    !reg->dev || dev_net(reg->dev) != net)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत bool nf_ingress_hook(स्थिर काष्ठा nf_hook_ops *reg, पूर्णांक pf)
अणु
	अगर ((pf == NFPROTO_NETDEV && reg->hooknum == NF_NETDEV_INGRESS) ||
	    (pf == NFPROTO_INET && reg->hooknum == NF_INET_INGRESS))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम nf_अटल_key_inc(स्थिर काष्ठा nf_hook_ops *reg, पूर्णांक pf)
अणु
#अगर_घोषित CONFIG_JUMP_LABEL
	पूर्णांक hooknum;

	अगर (pf == NFPROTO_INET && reg->hooknum == NF_INET_INGRESS) अणु
		pf = NFPROTO_NETDEV;
		hooknum = NF_NETDEV_INGRESS;
	पूर्ण अन्यथा अणु
		hooknum = reg->hooknum;
	पूर्ण
	अटल_key_slow_inc(&nf_hooks_needed[pf][hooknum]);
#पूर्ण_अगर
पूर्ण

अटल व्योम nf_अटल_key_dec(स्थिर काष्ठा nf_hook_ops *reg, पूर्णांक pf)
अणु
#अगर_घोषित CONFIG_JUMP_LABEL
	पूर्णांक hooknum;

	अगर (pf == NFPROTO_INET && reg->hooknum == NF_INET_INGRESS) अणु
		pf = NFPROTO_NETDEV;
		hooknum = NF_NETDEV_INGRESS;
	पूर्ण अन्यथा अणु
		hooknum = reg->hooknum;
	पूर्ण
	अटल_key_slow_dec(&nf_hooks_needed[pf][hooknum]);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __nf_रेजिस्टर_net_hook(काष्ठा net *net, पूर्णांक pf,
				  स्थिर काष्ठा nf_hook_ops *reg)
अणु
	काष्ठा nf_hook_entries *p, *new_hooks;
	काष्ठा nf_hook_entries __rcu **pp;
	पूर्णांक err;

	चयन (pf) अणु
	हाल NFPROTO_NETDEV:
		err = nf_ingress_check(net, reg, NF_NETDEV_INGRESS);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल NFPROTO_INET:
		अगर (reg->hooknum != NF_INET_INGRESS)
			अवरोध;

		err = nf_ingress_check(net, reg, NF_INET_INGRESS);
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	pp = nf_hook_entry_head(net, pf, reg->hooknum, reg->dev);
	अगर (!pp)
		वापस -EINVAL;

	mutex_lock(&nf_hook_mutex);

	p = nf_entry_dereference(*pp);
	new_hooks = nf_hook_entries_grow(p, reg);

	अगर (!IS_ERR(new_hooks))
		rcu_assign_poपूर्णांकer(*pp, new_hooks);

	mutex_unlock(&nf_hook_mutex);
	अगर (IS_ERR(new_hooks))
		वापस PTR_ERR(new_hooks);

	hooks_validate(new_hooks);
#अगर_घोषित CONFIG_NETFILTER_INGRESS
	अगर (nf_ingress_hook(reg, pf))
		net_inc_ingress_queue();
#पूर्ण_अगर
	nf_अटल_key_inc(reg, pf);

	BUG_ON(p == new_hooks);
	nf_hook_entries_मुक्त(p);
	वापस 0;
पूर्ण

/*
 * nf_हटाओ_net_hook - हटाओ a hook from blob
 *
 * @oldp: current address of hook blob
 * @unreg: hook to unरेजिस्टर
 *
 * This cannot fail, hook unregistration must always succeed.
 * Thereक्रमe replace the to-be-हटाओd hook with a dummy hook.
 */
अटल bool nf_हटाओ_net_hook(काष्ठा nf_hook_entries *old,
			       स्थिर काष्ठा nf_hook_ops *unreg)
अणु
	काष्ठा nf_hook_ops **orig_ops;
	अचिन्हित पूर्णांक i;

	orig_ops = nf_hook_entries_get_hook_ops(old);
	क्रम (i = 0; i < old->num_hook_entries; i++) अणु
		अगर (orig_ops[i] != unreg)
			जारी;
		WRITE_ONCE(old->hooks[i].hook, accept_all);
		WRITE_ONCE(orig_ops[i], (व्योम *)&dummy_ops);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम __nf_unरेजिस्टर_net_hook(काष्ठा net *net, पूर्णांक pf,
				     स्थिर काष्ठा nf_hook_ops *reg)
अणु
	काष्ठा nf_hook_entries __rcu **pp;
	काष्ठा nf_hook_entries *p;

	pp = nf_hook_entry_head(net, pf, reg->hooknum, reg->dev);
	अगर (!pp)
		वापस;

	mutex_lock(&nf_hook_mutex);

	p = nf_entry_dereference(*pp);
	अगर (WARN_ON_ONCE(!p)) अणु
		mutex_unlock(&nf_hook_mutex);
		वापस;
	पूर्ण

	अगर (nf_हटाओ_net_hook(p, reg)) अणु
#अगर_घोषित CONFIG_NETFILTER_INGRESS
		अगर (nf_ingress_hook(reg, pf))
			net_dec_ingress_queue();
#पूर्ण_अगर
		nf_अटल_key_dec(reg, pf);
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "hook not found, pf %d num %d", pf, reg->hooknum);
	पूर्ण

	p = __nf_hook_entries_try_shrink(p, pp);
	mutex_unlock(&nf_hook_mutex);
	अगर (!p)
		वापस;

	nf_queue_nf_hook_drop(net);
	nf_hook_entries_मुक्त(p);
पूर्ण

व्योम nf_unरेजिस्टर_net_hook(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *reg)
अणु
	अगर (reg->pf == NFPROTO_INET) अणु
		अगर (reg->hooknum == NF_INET_INGRESS) अणु
			__nf_unरेजिस्टर_net_hook(net, NFPROTO_INET, reg);
		पूर्ण अन्यथा अणु
			__nf_unरेजिस्टर_net_hook(net, NFPROTO_IPV4, reg);
			__nf_unरेजिस्टर_net_hook(net, NFPROTO_IPV6, reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		__nf_unरेजिस्टर_net_hook(net, reg->pf, reg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nf_unरेजिस्टर_net_hook);

व्योम nf_hook_entries_delete_raw(काष्ठा nf_hook_entries __rcu **pp,
				स्थिर काष्ठा nf_hook_ops *reg)
अणु
	काष्ठा nf_hook_entries *p;

	p = rcu_dereference_raw(*pp);
	अगर (nf_हटाओ_net_hook(p, reg)) अणु
		p = __nf_hook_entries_try_shrink(p, pp);
		nf_hook_entries_मुक्त(p);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_hook_entries_delete_raw);

पूर्णांक nf_रेजिस्टर_net_hook(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *reg)
अणु
	पूर्णांक err;

	अगर (reg->pf == NFPROTO_INET) अणु
		अगर (reg->hooknum == NF_INET_INGRESS) अणु
			err = __nf_रेजिस्टर_net_hook(net, NFPROTO_INET, reg);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			err = __nf_रेजिस्टर_net_hook(net, NFPROTO_IPV4, reg);
			अगर (err < 0)
				वापस err;

			err = __nf_रेजिस्टर_net_hook(net, NFPROTO_IPV6, reg);
			अगर (err < 0) अणु
				__nf_unरेजिस्टर_net_hook(net, NFPROTO_IPV4, reg);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		err = __nf_रेजिस्टर_net_hook(net, reg->pf, reg);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nf_रेजिस्टर_net_hook);

पूर्णांक nf_रेजिस्टर_net_hooks(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *reg,
			  अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < n; i++) अणु
		err = nf_रेजिस्टर_net_hook(net, &reg[i]);
		अगर (err)
			जाओ err;
	पूर्ण
	वापस err;

err:
	अगर (i > 0)
		nf_unरेजिस्टर_net_hooks(net, reg, i);
	वापस err;
पूर्ण
EXPORT_SYMBOL(nf_रेजिस्टर_net_hooks);

व्योम nf_unरेजिस्टर_net_hooks(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *reg,
			     अचिन्हित पूर्णांक hookcount)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < hookcount; i++)
		nf_unरेजिस्टर_net_hook(net, &reg[i]);
पूर्ण
EXPORT_SYMBOL(nf_unरेजिस्टर_net_hooks);

/* Returns 1 अगर okfn() needs to be executed by the caller,
 * -EPERM क्रम NF_DROP, 0 otherwise.  Caller must hold rcu_पढ़ो_lock. */
पूर्णांक nf_hook_slow(काष्ठा sk_buff *skb, काष्ठा nf_hook_state *state,
		 स्थिर काष्ठा nf_hook_entries *e, अचिन्हित पूर्णांक s)
अणु
	अचिन्हित पूर्णांक verdict;
	पूर्णांक ret;

	क्रम (; s < e->num_hook_entries; s++) अणु
		verdict = nf_hook_entry_hookfn(&e->hooks[s], skb, state);
		चयन (verdict & NF_VERDICT_MASK) अणु
		हाल NF_ACCEPT:
			अवरोध;
		हाल NF_DROP:
			kमुक्त_skb(skb);
			ret = NF_DROP_GETERR(verdict);
			अगर (ret == 0)
				ret = -EPERM;
			वापस ret;
		हाल NF_QUEUE:
			ret = nf_queue(skb, state, s, verdict);
			अगर (ret == 1)
				जारी;
			वापस ret;
		शेष:
			/* Implicit handling क्रम NF_STOLEN, as well as any other
			 * non conventional verdicts.
			 */
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(nf_hook_slow);

व्योम nf_hook_slow_list(काष्ठा list_head *head, काष्ठा nf_hook_state *state,
		       स्थिर काष्ठा nf_hook_entries *e)
अणु
	काष्ठा sk_buff *skb, *next;
	काष्ठा list_head sublist;
	पूर्णांक ret;

	INIT_LIST_HEAD(&sublist);

	list_क्रम_each_entry_safe(skb, next, head, list) अणु
		skb_list_del_init(skb);
		ret = nf_hook_slow(skb, state, e, 0);
		अगर (ret == 1)
			list_add_tail(&skb->list, &sublist);
	पूर्ण
	/* Put passed packets back on मुख्य list */
	list_splice(&sublist, head);
पूर्ण
EXPORT_SYMBOL(nf_hook_slow_list);

/* This needs to be compiled in any हाल to aव्योम dependencies between the
 * nfnetlink_queue code and nf_conntrack.
 */
काष्ठा nfnl_ct_hook __rcu *nfnl_ct_hook __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nfnl_ct_hook);

काष्ठा nf_ct_hook __rcu *nf_ct_hook __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_ct_hook);

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
/* This करोes not beदीर्घ here, but locally generated errors need it अगर connection
   tracking in use: without this, connection may not be in hash table, and hence
   manufactured ICMP or RST packets will not be associated with it. */
व्योम (*ip_ct_attach)(काष्ठा sk_buff *, स्थिर काष्ठा sk_buff *)
		__rcu __पढ़ो_mostly;
EXPORT_SYMBOL(ip_ct_attach);

काष्ठा nf_nat_hook __rcu *nf_nat_hook __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_hook);

व्योम nf_ct_attach(काष्ठा sk_buff *new, स्थिर काष्ठा sk_buff *skb)
अणु
	व्योम (*attach)(काष्ठा sk_buff *, स्थिर काष्ठा sk_buff *);

	अगर (skb->_nfct) अणु
		rcu_पढ़ो_lock();
		attach = rcu_dereference(ip_ct_attach);
		अगर (attach)
			attach(new, skb);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nf_ct_attach);

व्योम nf_conntrack_destroy(काष्ठा nf_conntrack *nfct)
अणु
	काष्ठा nf_ct_hook *ct_hook;

	rcu_पढ़ो_lock();
	ct_hook = rcu_dereference(nf_ct_hook);
	BUG_ON(ct_hook == शून्य);
	ct_hook->destroy(nfct);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(nf_conntrack_destroy);

bool nf_ct_get_tuple_skb(काष्ठा nf_conntrack_tuple *dst_tuple,
			 स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा nf_ct_hook *ct_hook;
	bool ret = false;

	rcu_पढ़ो_lock();
	ct_hook = rcu_dereference(nf_ct_hook);
	अगर (ct_hook)
		ret = ct_hook->get_tuple_skb(dst_tuple, skb);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(nf_ct_get_tuple_skb);

/* Built-in शेष zone used e.g. by modules. */
स्थिर काष्ठा nf_conntrack_zone nf_ct_zone_dflt = अणु
	.id	= NF_CT_DEFAULT_ZONE_ID,
	.dir	= NF_CT_DEFAULT_ZONE_सूची,
पूर्ण;
EXPORT_SYMBOL_GPL(nf_ct_zone_dflt);
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK */

अटल व्योम __net_init
__netfilter_net_init(काष्ठा nf_hook_entries __rcu **e, पूर्णांक max)
अणु
	पूर्णांक h;

	क्रम (h = 0; h < max; h++)
		RCU_INIT_POINTER(e[h], शून्य);
पूर्ण

अटल पूर्णांक __net_init netfilter_net_init(काष्ठा net *net)
अणु
	__netfilter_net_init(net->nf.hooks_ipv4, ARRAY_SIZE(net->nf.hooks_ipv4));
	__netfilter_net_init(net->nf.hooks_ipv6, ARRAY_SIZE(net->nf.hooks_ipv6));
#अगर_घोषित CONFIG_NETFILTER_FAMILY_ARP
	__netfilter_net_init(net->nf.hooks_arp, ARRAY_SIZE(net->nf.hooks_arp));
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
	__netfilter_net_init(net->nf.hooks_bridge, ARRAY_SIZE(net->nf.hooks_bridge));
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_DECNET)
	__netfilter_net_init(net->nf.hooks_decnet, ARRAY_SIZE(net->nf.hooks_decnet));
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_FS
	net->nf.proc_netfilter = proc_net_सूची_गढ़ो(net, "netfilter",
						net->proc_net);
	अगर (!net->nf.proc_netfilter) अणु
		अगर (!net_eq(net, &init_net))
			pr_err("cannot create netfilter proc entry");

		वापस -ENOMEM;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __net_निकास netfilter_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("netfilter", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations netfilter_net_ops = अणु
	.init = netfilter_net_init,
	.निकास = netfilter_net_निकास,
पूर्ण;

पूर्णांक __init netfilter_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&netfilter_net_ops);
	अगर (ret < 0)
		जाओ err;

	ret = netfilter_log_init();
	अगर (ret < 0)
		जाओ err_pernet;

	वापस 0;
err_pernet:
	unरेजिस्टर_pernet_subsys(&netfilter_net_ops);
err:
	वापस ret;
पूर्ण
