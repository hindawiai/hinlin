<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_NETFILTER_H
#घोषणा __LINUX_NETFILTER_H

#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/net.h>
#समावेश <linux/अगर.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/netfilter_defs.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sockptr.h>
#समावेश <net/net_namespace.h>

अटल अंतरभूत पूर्णांक NF_DROP_GETERR(पूर्णांक verdict)
अणु
	वापस -(verdict >> NF_VERDICT_QBITS);
पूर्ण

अटल अंतरभूत पूर्णांक nf_inet_addr_cmp(स्थिर जोड़ nf_inet_addr *a1,
				   स्थिर जोड़ nf_inet_addr *a2)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर अचिन्हित दीर्घ *ul1 = (स्थिर अचिन्हित दीर्घ *)a1;
	स्थिर अचिन्हित दीर्घ *ul2 = (स्थिर अचिन्हित दीर्घ *)a2;

	वापस ((ul1[0] ^ ul2[0]) | (ul1[1] ^ ul2[1])) == 0UL;
#अन्यथा
	वापस a1->all[0] == a2->all[0] &&
	       a1->all[1] == a2->all[1] &&
	       a1->all[2] == a2->all[2] &&
	       a1->all[3] == a2->all[3];
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम nf_inet_addr_mask(स्थिर जोड़ nf_inet_addr *a1,
				     जोड़ nf_inet_addr *result,
				     स्थिर जोड़ nf_inet_addr *mask)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर अचिन्हित दीर्घ *ua = (स्थिर अचिन्हित दीर्घ *)a1;
	अचिन्हित दीर्घ *ur = (अचिन्हित दीर्घ *)result;
	स्थिर अचिन्हित दीर्घ *um = (स्थिर अचिन्हित दीर्घ *)mask;

	ur[0] = ua[0] & um[0];
	ur[1] = ua[1] & um[1];
#अन्यथा
	result->all[0] = a1->all[0] & mask->all[0];
	result->all[1] = a1->all[1] & mask->all[1];
	result->all[2] = a1->all[2] & mask->all[2];
	result->all[3] = a1->all[3] & mask->all[3];
#पूर्ण_अगर
पूर्ण

पूर्णांक netfilter_init(व्योम);

काष्ठा sk_buff;

काष्ठा nf_hook_ops;

काष्ठा sock;

काष्ठा nf_hook_state अणु
	अचिन्हित पूर्णांक hook;
	u_पूर्णांक8_t pf;
	काष्ठा net_device *in;
	काष्ठा net_device *out;
	काष्ठा sock *sk;
	काष्ठा net *net;
	पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *);
पूर्ण;

प्रकार अचिन्हित पूर्णांक nf_hookfn(व्योम *priv,
			       काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nf_hook_state *state);
काष्ठा nf_hook_ops अणु
	/* User fills in from here करोwn. */
	nf_hookfn		*hook;
	काष्ठा net_device	*dev;
	व्योम			*priv;
	u_पूर्णांक8_t		pf;
	अचिन्हित पूर्णांक		hooknum;
	/* Hooks are ordered in ascending priority. */
	पूर्णांक			priority;
पूर्ण;

काष्ठा nf_hook_entry अणु
	nf_hookfn			*hook;
	व्योम				*priv;
पूर्ण;

काष्ठा nf_hook_entries_rcu_head अणु
	काष्ठा rcu_head head;
	व्योम	*allocation;
पूर्ण;

काष्ठा nf_hook_entries अणु
	u16				num_hook_entries;
	/* padding */
	काष्ठा nf_hook_entry		hooks[];

	/* trailer: poपूर्णांकers to original orig_ops of each hook,
	 * followed by rcu_head and scratch space used क्रम मुक्तing
	 * the काष्ठाure via call_rcu.
	 *
	 *   This is not part of काष्ठा nf_hook_entry since its only
	 *   needed in slow path (hook रेजिस्टर/unरेजिस्टर):
	 * स्थिर काष्ठा nf_hook_ops     *orig_ops[]
	 *
	 *   For the same reason, we store this at end -- its
	 *   only needed when a hook is deleted, not during
	 *   packet path processing:
	 * काष्ठा nf_hook_entries_rcu_head     head
	 */
पूर्ण;

#अगर_घोषित CONFIG_NETFILTER
अटल अंतरभूत काष्ठा nf_hook_ops **nf_hook_entries_get_hook_ops(स्थिर काष्ठा nf_hook_entries *e)
अणु
	अचिन्हित पूर्णांक n = e->num_hook_entries;
	स्थिर व्योम *hook_end;

	hook_end = &e->hooks[n]; /* this is *past* ->hooks[]! */

	वापस (काष्ठा nf_hook_ops **)hook_end;
पूर्ण

अटल अंतरभूत पूर्णांक
nf_hook_entry_hookfn(स्थिर काष्ठा nf_hook_entry *entry, काष्ठा sk_buff *skb,
		     काष्ठा nf_hook_state *state)
अणु
	वापस entry->hook(entry->priv, skb, state);
पूर्ण

अटल अंतरभूत व्योम nf_hook_state_init(काष्ठा nf_hook_state *p,
				      अचिन्हित पूर्णांक hook,
				      u_पूर्णांक8_t pf,
				      काष्ठा net_device *indev,
				      काष्ठा net_device *outdev,
				      काष्ठा sock *sk,
				      काष्ठा net *net,
				      पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	p->hook = hook;
	p->pf = pf;
	p->in = indev;
	p->out = outdev;
	p->sk = sk;
	p->net = net;
	p->okfn = okfn;
पूर्ण



काष्ठा nf_sockopt_ops अणु
	काष्ठा list_head list;

	u_पूर्णांक8_t pf;

	/* Non-inclusive ranges: use 0/0/शून्य to never get called. */
	पूर्णांक set_opपंचांगin;
	पूर्णांक set_opपंचांगax;
	पूर्णांक (*set)(काष्ठा sock *sk, पूर्णांक optval, sockptr_t arg,
		   अचिन्हित पूर्णांक len);
	पूर्णांक get_opपंचांगin;
	पूर्णांक get_opपंचांगax;
	पूर्णांक (*get)(काष्ठा sock *sk, पूर्णांक optval, व्योम __user *user, पूर्णांक *len);
	/* Use the module काष्ठा to lock set/get code in place */
	काष्ठा module *owner;
पूर्ण;

/* Function to रेजिस्टर/unरेजिस्टर hook poपूर्णांकs. */
पूर्णांक nf_रेजिस्टर_net_hook(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);
व्योम nf_unरेजिस्टर_net_hook(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *ops);
पूर्णांक nf_रेजिस्टर_net_hooks(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *reg,
			  अचिन्हित पूर्णांक n);
व्योम nf_unरेजिस्टर_net_hooks(काष्ठा net *net, स्थिर काष्ठा nf_hook_ops *reg,
			     अचिन्हित पूर्णांक n);

/* Functions to रेजिस्टर get/setsockopt ranges (non-inclusive).  You
   need to check permissions yourself! */
पूर्णांक nf_रेजिस्टर_sockopt(काष्ठा nf_sockopt_ops *reg);
व्योम nf_unरेजिस्टर_sockopt(काष्ठा nf_sockopt_ops *reg);

#अगर_घोषित CONFIG_JUMP_LABEL
बाह्य काष्ठा अटल_key nf_hooks_needed[NFPROTO_NUMPROTO][NF_MAX_HOOKS];
#पूर्ण_अगर

पूर्णांक nf_hook_slow(काष्ठा sk_buff *skb, काष्ठा nf_hook_state *state,
		 स्थिर काष्ठा nf_hook_entries *e, अचिन्हित पूर्णांक i);

व्योम nf_hook_slow_list(काष्ठा list_head *head, काष्ठा nf_hook_state *state,
		       स्थिर काष्ठा nf_hook_entries *e);
/**
 *	nf_hook - call a netfilter hook
 *
 *	Returns 1 अगर the hook has allowed the packet to pass.  The function
 *	okfn must be invoked by the caller in this हाल.  Any other वापस
 *	value indicates the packet has been consumed by the hook.
 */
अटल अंतरभूत पूर्णांक nf_hook(u_पूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net,
			  काष्ठा sock *sk, काष्ठा sk_buff *skb,
			  काष्ठा net_device *indev, काष्ठा net_device *outdev,
			  पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	काष्ठा nf_hook_entries *hook_head = शून्य;
	पूर्णांक ret = 1;

#अगर_घोषित CONFIG_JUMP_LABEL
	अगर (__builtin_स्थिरant_p(pf) &&
	    __builtin_स्थिरant_p(hook) &&
	    !अटल_key_false(&nf_hooks_needed[pf][hook]))
		वापस 1;
#पूर्ण_अगर

	rcu_पढ़ो_lock();
	चयन (pf) अणु
	हाल NFPROTO_IPV4:
		hook_head = rcu_dereference(net->nf.hooks_ipv4[hook]);
		अवरोध;
	हाल NFPROTO_IPV6:
		hook_head = rcu_dereference(net->nf.hooks_ipv6[hook]);
		अवरोध;
	हाल NFPROTO_ARP:
#अगर_घोषित CONFIG_NETFILTER_FAMILY_ARP
		अगर (WARN_ON_ONCE(hook >= ARRAY_SIZE(net->nf.hooks_arp)))
			अवरोध;
		hook_head = rcu_dereference(net->nf.hooks_arp[hook]);
#पूर्ण_अगर
		अवरोध;
	हाल NFPROTO_BRIDGE:
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
		hook_head = rcu_dereference(net->nf.hooks_bridge[hook]);
#पूर्ण_अगर
		अवरोध;
#अगर IS_ENABLED(CONFIG_DECNET)
	हाल NFPROTO_DECNET:
		hook_head = rcu_dereference(net->nf.hooks_decnet[hook]);
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	अगर (hook_head) अणु
		काष्ठा nf_hook_state state;

		nf_hook_state_init(&state, hook, pf, indev, outdev,
				   sk, net, okfn);

		ret = nf_hook_slow(skb, &state, hook_head, 0);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/* Activate hook; either okfn or kमुक्त_skb called, unless a hook
   वापसs NF_STOLEN (in which हाल, it's up to the hook to deal with
   the consequences).

   Returns -ERRNO अगर packet dropped.  Zero means queued, stolen or
   accepted.
*/

/* RR:
   > I करोn't want nf_hook to वापस anything because people might क्रमget
   > about async and trust the वापस value to mean "packet was ok".

   AK:
   Just करोcument it clearly, then you can expect some sense from kernel
   coders :)
*/

अटल अंतरभूत पूर्णांक
NF_HOOK_COND(uपूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net, काष्ठा sock *sk,
	     काष्ठा sk_buff *skb, काष्ठा net_device *in, काष्ठा net_device *out,
	     पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *),
	     bool cond)
अणु
	पूर्णांक ret;

	अगर (!cond ||
	    ((ret = nf_hook(pf, hook, net, sk, skb, in, out, okfn)) == 1))
		ret = okfn(net, sk, skb);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
NF_HOOK(uपूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
	काष्ठा net_device *in, काष्ठा net_device *out,
	पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	पूर्णांक ret = nf_hook(pf, hook, net, sk, skb, in, out, okfn);
	अगर (ret == 1)
		ret = okfn(net, sk, skb);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
NF_HOOK_LIST(uपूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net, काष्ठा sock *sk,
	     काष्ठा list_head *head, काष्ठा net_device *in, काष्ठा net_device *out,
	     पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	काष्ठा nf_hook_entries *hook_head = शून्य;

#अगर_घोषित CONFIG_JUMP_LABEL
	अगर (__builtin_स्थिरant_p(pf) &&
	    __builtin_स्थिरant_p(hook) &&
	    !अटल_key_false(&nf_hooks_needed[pf][hook]))
		वापस;
#पूर्ण_अगर

	rcu_पढ़ो_lock();
	चयन (pf) अणु
	हाल NFPROTO_IPV4:
		hook_head = rcu_dereference(net->nf.hooks_ipv4[hook]);
		अवरोध;
	हाल NFPROTO_IPV6:
		hook_head = rcu_dereference(net->nf.hooks_ipv6[hook]);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	अगर (hook_head) अणु
		काष्ठा nf_hook_state state;

		nf_hook_state_init(&state, hook, pf, in, out, sk, net, okfn);

		nf_hook_slow_list(head, &state, hook_head);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Call setsockopt() */
पूर्णांक nf_setsockopt(काष्ठा sock *sk, u_पूर्णांक8_t pf, पूर्णांक optval, sockptr_t opt,
		  अचिन्हित पूर्णांक len);
पूर्णांक nf_माला_लोockopt(काष्ठा sock *sk, u_पूर्णांक8_t pf, पूर्णांक optval, अक्षर __user *opt,
		  पूर्णांक *len);

काष्ठा flowi;
काष्ठा nf_queue_entry;

__sum16 nf_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
		    अचिन्हित पूर्णांक dataoff, u_पूर्णांक8_t protocol,
		    अचिन्हित लघु family);

__sum16 nf_checksum_partial(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
			    अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक len,
			    u_पूर्णांक8_t protocol, अचिन्हित लघु family);
पूर्णांक nf_route(काष्ठा net *net, काष्ठा dst_entry **dst, काष्ठा flowi *fl,
	     bool strict, अचिन्हित लघु family);
पूर्णांक nf_reroute(काष्ठा sk_buff *skb, काष्ठा nf_queue_entry *entry);

#समावेश <net/flow.h>

काष्ठा nf_conn;
क्रमागत nf_nat_manip_type;
काष्ठा nlattr;
क्रमागत ip_conntrack_dir;

काष्ठा nf_nat_hook अणु
	पूर्णांक (*parse_nat_setup)(काष्ठा nf_conn *ct, क्रमागत nf_nat_manip_type manip,
			       स्थिर काष्ठा nlattr *attr);
	व्योम (*decode_session)(काष्ठा sk_buff *skb, काष्ठा flowi *fl);
	अचिन्हित पूर्णांक (*manip_pkt)(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
				  क्रमागत nf_nat_manip_type mtype,
				  क्रमागत ip_conntrack_dir dir);
पूर्ण;

बाह्य काष्ठा nf_nat_hook __rcu *nf_nat_hook;

अटल अंतरभूत व्योम
nf_nat_decode_session(काष्ठा sk_buff *skb, काष्ठा flowi *fl, u_पूर्णांक8_t family)
अणु
#अगर IS_ENABLED(CONFIG_NF_NAT)
	काष्ठा nf_nat_hook *nat_hook;

	rcu_पढ़ो_lock();
	nat_hook = rcu_dereference(nf_nat_hook);
	अगर (nat_hook && nat_hook->decode_session)
		nat_hook->decode_session(skb, fl);
	rcu_पढ़ो_unlock();
#पूर्ण_अगर
पूर्ण

#अन्यथा /* !CONFIG_NETFILTER */
अटल अंतरभूत पूर्णांक
NF_HOOK_COND(uपूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net, काष्ठा sock *sk,
	     काष्ठा sk_buff *skb, काष्ठा net_device *in, काष्ठा net_device *out,
	     पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *),
	     bool cond)
अणु
	वापस okfn(net, sk, skb);
पूर्ण

अटल अंतरभूत पूर्णांक
NF_HOOK(uपूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net, काष्ठा sock *sk,
	काष्ठा sk_buff *skb, काष्ठा net_device *in, काष्ठा net_device *out,
	पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	वापस okfn(net, sk, skb);
पूर्ण

अटल अंतरभूत व्योम
NF_HOOK_LIST(uपूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net, काष्ठा sock *sk,
	     काष्ठा list_head *head, काष्ठा net_device *in, काष्ठा net_device *out,
	     पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	/* nothing to करो */
पूर्ण

अटल अंतरभूत पूर्णांक nf_hook(u_पूर्णांक8_t pf, अचिन्हित पूर्णांक hook, काष्ठा net *net,
			  काष्ठा sock *sk, काष्ठा sk_buff *skb,
			  काष्ठा net_device *indev, काष्ठा net_device *outdev,
			  पूर्णांक (*okfn)(काष्ठा net *, काष्ठा sock *, काष्ठा sk_buff *))
अणु
	वापस 1;
पूर्ण
काष्ठा flowi;
अटल अंतरभूत व्योम
nf_nat_decode_session(काष्ठा sk_buff *skb, काष्ठा flowi *fl, u_पूर्णांक8_t family)
अणु
पूर्ण
#पूर्ण_अगर /*CONFIG_NETFILTER*/

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <linux/netfilter/nf_conntrack_zones_common.h>

बाह्य व्योम (*ip_ct_attach)(काष्ठा sk_buff *, स्थिर काष्ठा sk_buff *) __rcu;
व्योम nf_ct_attach(काष्ठा sk_buff *, स्थिर काष्ठा sk_buff *);
काष्ठा nf_conntrack_tuple;
bool nf_ct_get_tuple_skb(काष्ठा nf_conntrack_tuple *dst_tuple,
			 स्थिर काष्ठा sk_buff *skb);
#अन्यथा
अटल अंतरभूत व्योम nf_ct_attach(काष्ठा sk_buff *new, काष्ठा sk_buff *skb) अणुपूर्ण
काष्ठा nf_conntrack_tuple;
अटल अंतरभूत bool nf_ct_get_tuple_skb(काष्ठा nf_conntrack_tuple *dst_tuple,
				       स्थिर काष्ठा sk_buff *skb)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

काष्ठा nf_conn;
क्रमागत ip_conntrack_info;

काष्ठा nf_ct_hook अणु
	पूर्णांक (*update)(काष्ठा net *net, काष्ठा sk_buff *skb);
	व्योम (*destroy)(काष्ठा nf_conntrack *);
	bool (*get_tuple_skb)(काष्ठा nf_conntrack_tuple *,
			      स्थिर काष्ठा sk_buff *);
पूर्ण;
बाह्य काष्ठा nf_ct_hook __rcu *nf_ct_hook;

काष्ठा nlattr;

काष्ठा nfnl_ct_hook अणु
	माप_प्रकार (*build_size)(स्थिर काष्ठा nf_conn *ct);
	पूर्णांक (*build)(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
		     क्रमागत ip_conntrack_info ctinfo,
		     u_पूर्णांक16_t ct_attr, u_पूर्णांक16_t ct_info_attr);
	पूर्णांक (*parse)(स्थिर काष्ठा nlattr *attr, काष्ठा nf_conn *ct);
	पूर्णांक (*attach_expect)(स्थिर काष्ठा nlattr *attr, काष्ठा nf_conn *ct,
			     u32 portid, u32 report);
	व्योम (*seq_adjust)(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			   क्रमागत ip_conntrack_info ctinfo, s32 off);
पूर्ण;
बाह्य काष्ठा nfnl_ct_hook __rcu *nfnl_ct_hook;

/**
 * nf_skb_duplicated - TEE target has sent a packet
 *
 * When a xtables target sends a packet, the OUTPUT and POSTROUTING
 * hooks are traversed again, i.e. nft and xtables are invoked recursively.
 *
 * This is used by xtables TEE target to prevent the duplicated skb from
 * being duplicated again.
 */
DECLARE_PER_CPU(bool, nf_skb_duplicated);

#पूर्ण_अगर /*__LINUX_NETFILTER_H*/
