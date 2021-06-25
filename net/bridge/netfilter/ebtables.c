<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ebtables
 *
 *  Author:
 *  Bart De Schuymer		<bdschuym@panकरोra.be>
 *
 *  ebtables.c,v 2.0, July, 2002
 *
 *  This code is strongly inspired by the iptables code which is
 *  Copyright (C) 1999 Paul `Rusty' Russell & Michael J. Neuling
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/kmod.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/smp.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/audit.h>
#समावेश <net/sock.h>
#समावेश <net/netns/generic.h>
/* needed क्रम logical [in,out]-dev filtering */
#समावेश "../br_private.h"

/* Each cpu has its own set of counters, so there is no need क्रम ग_लिखो_lock in
 * the softirq
 * For पढ़ोing or updating the counters, the user context needs to
 * get a ग_लिखो_lock
 */

/* The size of each set of counters is altered to get cache alignment */
#घोषणा SMP_ALIGN(x) (((x) + SMP_CACHE_BYTES-1) & ~(SMP_CACHE_BYTES-1))
#घोषणा COUNTER_OFFSET(n) (SMP_ALIGN(n * माप(काष्ठा ebt_counter)))
#घोषणा COUNTER_BASE(c, n, cpu) ((काष्ठा ebt_counter *)(((अक्षर *)c) + \
				 COUNTER_OFFSET(n) * cpu))

काष्ठा ebt_pernet अणु
	काष्ठा list_head tables;
पूर्ण;

अटल अचिन्हित पूर्णांक ebt_pernet_id __पढ़ो_mostly;
अटल DEFINE_MUTEX(ebt_mutex);

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
अटल व्योम ebt_standard_compat_from_user(व्योम *dst, स्थिर व्योम *src)
अणु
	पूर्णांक v = *(compat_पूर्णांक_t *)src;

	अगर (v >= 0)
		v += xt_compat_calc_jump(NFPROTO_BRIDGE, v);
	स_नकल(dst, &v, माप(v));
पूर्ण

अटल पूर्णांक ebt_standard_compat_to_user(व्योम __user *dst, स्थिर व्योम *src)
अणु
	compat_पूर्णांक_t cv = *(पूर्णांक *)src;

	अगर (cv >= 0)
		cv -= xt_compat_calc_jump(NFPROTO_BRIDGE, cv);
	वापस copy_to_user(dst, &cv, माप(cv)) ? -EFAULT : 0;
पूर्ण
#पूर्ण_अगर


अटल काष्ठा xt_target ebt_standard_target = अणु
	.name       = "standard",
	.revision   = 0,
	.family     = NFPROTO_BRIDGE,
	.tarमाला_लोize = माप(पूर्णांक),
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	.compatsize = माप(compat_पूर्णांक_t),
	.compat_from_user = ebt_standard_compat_from_user,
	.compat_to_user =  ebt_standard_compat_to_user,
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत पूर्णांक
ebt_करो_watcher(स्थिर काष्ठा ebt_entry_watcher *w, काष्ठा sk_buff *skb,
	       काष्ठा xt_action_param *par)
अणु
	par->target   = w->u.watcher;
	par->targinfo = w->data;
	w->u.watcher->target(skb, par);
	/* watchers करोn't give a verdict */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ebt_करो_match(काष्ठा ebt_entry_match *m, स्थिर काष्ठा sk_buff *skb,
	     काष्ठा xt_action_param *par)
अणु
	par->match     = m->u.match;
	par->matchinfo = m->data;
	वापस !m->u.match->match(skb, par);
पूर्ण

अटल अंतरभूत पूर्णांक
ebt_dev_check(स्थिर अक्षर *entry, स्थिर काष्ठा net_device *device)
अणु
	पूर्णांक i = 0;
	स्थिर अक्षर *devname;

	अगर (*entry == '\0')
		वापस 0;
	अगर (!device)
		वापस 1;
	devname = device->name;
	/* 1 is the wildcard token */
	जबतक (entry[i] != '\0' && entry[i] != 1 && entry[i] == devname[i])
		i++;
	वापस devname[i] != entry[i] && entry[i] != 1;
पूर्ण

/* process standard matches */
अटल अंतरभूत पूर्णांक
ebt_basic_match(स्थिर काष्ठा ebt_entry *e, स्थिर काष्ठा sk_buff *skb,
		स्थिर काष्ठा net_device *in, स्थिर काष्ठा net_device *out)
अणु
	स्थिर काष्ठा ethhdr *h = eth_hdr(skb);
	स्थिर काष्ठा net_bridge_port *p;
	__be16 ethproto;

	अगर (skb_vlan_tag_present(skb))
		ethproto = htons(ETH_P_8021Q);
	अन्यथा
		ethproto = h->h_proto;

	अगर (e->biपंचांगask & EBT_802_3) अणु
		अगर (NF_INVF(e, EBT_IPROTO, eth_proto_is_802_3(ethproto)))
			वापस 1;
	पूर्ण अन्यथा अगर (!(e->biपंचांगask & EBT_NOPROTO) &&
		   NF_INVF(e, EBT_IPROTO, e->ethproto != ethproto))
		वापस 1;

	अगर (NF_INVF(e, EBT_IIN, ebt_dev_check(e->in, in)))
		वापस 1;
	अगर (NF_INVF(e, EBT_IOUT, ebt_dev_check(e->out, out)))
		वापस 1;
	/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
	अगर (in && (p = br_port_get_rcu(in)) != शून्य &&
	    NF_INVF(e, EBT_ILOGICALIN,
		    ebt_dev_check(e->logical_in, p->br->dev)))
		वापस 1;
	अगर (out && (p = br_port_get_rcu(out)) != शून्य &&
	    NF_INVF(e, EBT_ILOGICALOUT,
		    ebt_dev_check(e->logical_out, p->br->dev)))
		वापस 1;

	अगर (e->biपंचांगask & EBT_SOURCEMAC) अणु
		अगर (NF_INVF(e, EBT_ISOURCE,
			    !ether_addr_equal_masked(h->h_source, e->sourcemac,
						     e->sourcemsk)))
			वापस 1;
	पूर्ण
	अगर (e->biपंचांगask & EBT_DESTMAC) अणु
		अगर (NF_INVF(e, EBT_IDEST,
			    !ether_addr_equal_masked(h->h_dest, e->desपंचांगac,
						     e->desपंचांगsk)))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत
काष्ठा ebt_entry *ebt_next_entry(स्थिर काष्ठा ebt_entry *entry)
अणु
	वापस (व्योम *)entry + entry->next_offset;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा ebt_entry_target *
ebt_get_target_c(स्थिर काष्ठा ebt_entry *e)
अणु
	वापस ebt_get_target((काष्ठा ebt_entry *)e);
पूर्ण

/* Do some firewalling */
अचिन्हित पूर्णांक ebt_करो_table(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nf_hook_state *state,
			  काष्ठा ebt_table *table)
अणु
	अचिन्हित पूर्णांक hook = state->hook;
	पूर्णांक i, nentries;
	काष्ठा ebt_entry *poपूर्णांक;
	काष्ठा ebt_counter *counter_base, *cb_base;
	स्थिर काष्ठा ebt_entry_target *t;
	पूर्णांक verdict, sp = 0;
	काष्ठा ebt_chainstack *cs;
	काष्ठा ebt_entries *chaininfo;
	स्थिर अक्षर *base;
	स्थिर काष्ठा ebt_table_info *निजी;
	काष्ठा xt_action_param acpar;

	acpar.state   = state;
	acpar.hotdrop = false;

	पढ़ो_lock_bh(&table->lock);
	निजी = table->निजी;
	cb_base = COUNTER_BASE(निजी->counters, निजी->nentries,
	   smp_processor_id());
	अगर (निजी->chainstack)
		cs = निजी->chainstack[smp_processor_id()];
	अन्यथा
		cs = शून्य;
	chaininfo = निजी->hook_entry[hook];
	nentries = निजी->hook_entry[hook]->nentries;
	poपूर्णांक = (काष्ठा ebt_entry *)(निजी->hook_entry[hook]->data);
	counter_base = cb_base + निजी->hook_entry[hook]->counter_offset;
	/* base क्रम chain jumps */
	base = निजी->entries;
	i = 0;
	जबतक (i < nentries) अणु
		अगर (ebt_basic_match(poपूर्णांक, skb, state->in, state->out))
			जाओ letsजारी;

		अगर (EBT_MATCH_ITERATE(poपूर्णांक, ebt_करो_match, skb, &acpar) != 0)
			जाओ letsजारी;
		अगर (acpar.hotdrop) अणु
			पढ़ो_unlock_bh(&table->lock);
			वापस NF_DROP;
		पूर्ण

		ADD_COUNTER(*(counter_base + i), skb->len, 1);

		/* these should only watch: not modअगरy, nor tell us
		 * what to करो with the packet
		 */
		EBT_WATCHER_ITERATE(poपूर्णांक, ebt_करो_watcher, skb, &acpar);

		t = ebt_get_target_c(poपूर्णांक);
		/* standard target */
		अगर (!t->u.target->target)
			verdict = ((काष्ठा ebt_standard_target *)t)->verdict;
		अन्यथा अणु
			acpar.target   = t->u.target;
			acpar.targinfo = t->data;
			verdict = t->u.target->target(skb, &acpar);
		पूर्ण
		अगर (verdict == EBT_ACCEPT) अणु
			पढ़ो_unlock_bh(&table->lock);
			वापस NF_ACCEPT;
		पूर्ण
		अगर (verdict == EBT_DROP) अणु
			पढ़ो_unlock_bh(&table->lock);
			वापस NF_DROP;
		पूर्ण
		अगर (verdict == EBT_RETURN) अणु
letsवापस:
			अगर (WARN(sp == 0, "RETURN on base chain")) अणु
				/* act like this is EBT_CONTINUE */
				जाओ letsजारी;
			पूर्ण

			sp--;
			/* put all the local variables right */
			i = cs[sp].n;
			chaininfo = cs[sp].chaininfo;
			nentries = chaininfo->nentries;
			poपूर्णांक = cs[sp].e;
			counter_base = cb_base +
			   chaininfo->counter_offset;
			जारी;
		पूर्ण
		अगर (verdict == EBT_CONTINUE)
			जाओ letsजारी;

		अगर (WARN(verdict < 0, "bogus standard verdict\n")) अणु
			पढ़ो_unlock_bh(&table->lock);
			वापस NF_DROP;
		पूर्ण

		/* jump to a udc */
		cs[sp].n = i + 1;
		cs[sp].chaininfo = chaininfo;
		cs[sp].e = ebt_next_entry(poपूर्णांक);
		i = 0;
		chaininfo = (काष्ठा ebt_entries *) (base + verdict);

		अगर (WARN(chaininfo->distinguisher, "jump to non-chain\n")) अणु
			पढ़ो_unlock_bh(&table->lock);
			वापस NF_DROP;
		पूर्ण

		nentries = chaininfo->nentries;
		poपूर्णांक = (काष्ठा ebt_entry *)chaininfo->data;
		counter_base = cb_base + chaininfo->counter_offset;
		sp++;
		जारी;
letsजारी:
		poपूर्णांक = ebt_next_entry(poपूर्णांक);
		i++;
	पूर्ण

	/* I actually like this :) */
	अगर (chaininfo->policy == EBT_RETURN)
		जाओ letsवापस;
	अगर (chaininfo->policy == EBT_ACCEPT) अणु
		पढ़ो_unlock_bh(&table->lock);
		वापस NF_ACCEPT;
	पूर्ण
	पढ़ो_unlock_bh(&table->lock);
	वापस NF_DROP;
पूर्ण

/* If it succeeds, वापसs element and locks mutex */
अटल अंतरभूत व्योम *
find_inlist_lock_noload(काष्ठा list_head *head, स्थिर अक्षर *name, पूर्णांक *error,
			काष्ठा mutex *mutex)
अणु
	काष्ठा अणु
		काष्ठा list_head list;
		अक्षर name[EBT_FUNCTION_MAXNAMELEN];
	पूर्ण *e;

	mutex_lock(mutex);
	list_क्रम_each_entry(e, head, list) अणु
		अगर (म_भेद(e->name, name) == 0)
			वापस e;
	पूर्ण
	*error = -ENOENT;
	mutex_unlock(mutex);
	वापस शून्य;
पूर्ण

अटल व्योम *
find_inlist_lock(काष्ठा list_head *head, स्थिर अक्षर *name, स्थिर अक्षर *prefix,
		 पूर्णांक *error, काष्ठा mutex *mutex)
अणु
	वापस try_then_request_module(
			find_inlist_lock_noload(head, name, error, mutex),
			"%s%s", prefix, name);
पूर्ण

अटल अंतरभूत काष्ठा ebt_table *
find_table_lock(काष्ठा net *net, स्थिर अक्षर *name, पूर्णांक *error,
		काष्ठा mutex *mutex)
अणु
	काष्ठा ebt_pernet *ebt_net = net_generic(net, ebt_pernet_id);

	वापस find_inlist_lock(&ebt_net->tables, name,
				"ebtable_", error, mutex);
पूर्ण

अटल अंतरभूत व्योम ebt_मुक्त_table_info(काष्ठा ebt_table_info *info)
अणु
	पूर्णांक i;

	अगर (info->chainstack) अणु
		क्रम_each_possible_cpu(i)
			vमुक्त(info->chainstack[i]);
		vमुक्त(info->chainstack);
	पूर्ण
पूर्ण
अटल अंतरभूत पूर्णांक
ebt_check_match(काष्ठा ebt_entry_match *m, काष्ठा xt_mtchk_param *par,
		अचिन्हित पूर्णांक *cnt)
अणु
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;
	काष्ठा xt_match *match;
	माप_प्रकार left = ((अक्षर *)e + e->watchers_offset) - (अक्षर *)m;
	पूर्णांक ret;

	अगर (left < माप(काष्ठा ebt_entry_match) ||
	    left - माप(काष्ठा ebt_entry_match) < m->match_size)
		वापस -EINVAL;

	match = xt_find_match(NFPROTO_BRIDGE, m->u.name, m->u.revision);
	अगर (IS_ERR(match) || match->family != NFPROTO_BRIDGE) अणु
		अगर (!IS_ERR(match))
			module_put(match->me);
		request_module("ebt_%s", m->u.name);
		match = xt_find_match(NFPROTO_BRIDGE, m->u.name, m->u.revision);
	पूर्ण
	अगर (IS_ERR(match))
		वापस PTR_ERR(match);
	m->u.match = match;

	par->match     = match;
	par->matchinfo = m->data;
	ret = xt_check_match(par, m->match_size,
	      ntohs(e->ethproto), e->invflags & EBT_IPROTO);
	अगर (ret < 0) अणु
		module_put(match->me);
		वापस ret;
	पूर्ण

	(*cnt)++;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ebt_check_watcher(काष्ठा ebt_entry_watcher *w, काष्ठा xt_tgchk_param *par,
		  अचिन्हित पूर्णांक *cnt)
अणु
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;
	काष्ठा xt_target *watcher;
	माप_प्रकार left = ((अक्षर *)e + e->target_offset) - (अक्षर *)w;
	पूर्णांक ret;

	अगर (left < माप(काष्ठा ebt_entry_watcher) ||
	   left - माप(काष्ठा ebt_entry_watcher) < w->watcher_size)
		वापस -EINVAL;

	watcher = xt_request_find_target(NFPROTO_BRIDGE, w->u.name, 0);
	अगर (IS_ERR(watcher))
		वापस PTR_ERR(watcher);

	अगर (watcher->family != NFPROTO_BRIDGE) अणु
		module_put(watcher->me);
		वापस -ENOENT;
	पूर्ण

	w->u.watcher = watcher;

	par->target   = watcher;
	par->targinfo = w->data;
	ret = xt_check_target(par, w->watcher_size,
	      ntohs(e->ethproto), e->invflags & EBT_IPROTO);
	अगर (ret < 0) अणु
		module_put(watcher->me);
		वापस ret;
	पूर्ण

	(*cnt)++;
	वापस 0;
पूर्ण

अटल पूर्णांक ebt_verअगरy_poपूर्णांकers(स्थिर काष्ठा ebt_replace *repl,
			       काष्ठा ebt_table_info *newinfo)
अणु
	अचिन्हित पूर्णांक limit = repl->entries_size;
	अचिन्हित पूर्णांक valid_hooks = repl->valid_hooks;
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++)
		newinfo->hook_entry[i] = शून्य;

	newinfo->entries_size = repl->entries_size;
	newinfo->nentries = repl->nentries;

	जबतक (offset < limit) अणु
		माप_प्रकार left = limit - offset;
		काष्ठा ebt_entry *e = (व्योम *)newinfo->entries + offset;

		अगर (left < माप(अचिन्हित पूर्णांक))
			अवरोध;

		क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
			अगर ((valid_hooks & (1 << i)) == 0)
				जारी;
			अगर ((अक्षर __user *)repl->hook_entry[i] ==
			     repl->entries + offset)
				अवरोध;
		पूर्ण

		अगर (i != NF_BR_NUMHOOKS || !(e->biपंचांगask & EBT_ENTRY_OR_ENTRIES)) अणु
			अगर (e->biपंचांगask != 0) अणु
				/* we make userspace set this right,
				 * so there is no misunderstanding
				 */
				वापस -EINVAL;
			पूर्ण
			अगर (i != NF_BR_NUMHOOKS)
				newinfo->hook_entry[i] = (काष्ठा ebt_entries *)e;
			अगर (left < माप(काष्ठा ebt_entries))
				अवरोध;
			offset += माप(काष्ठा ebt_entries);
		पूर्ण अन्यथा अणु
			अगर (left < माप(काष्ठा ebt_entry))
				अवरोध;
			अगर (left < e->next_offset)
				अवरोध;
			अगर (e->next_offset < माप(काष्ठा ebt_entry))
				वापस -EINVAL;
			offset += e->next_offset;
		पूर्ण
	पूर्ण
	अगर (offset != limit)
		वापस -EINVAL;

	/* check अगर all valid hooks have a chain */
	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
		अगर (!newinfo->hook_entry[i] &&
		   (valid_hooks & (1 << i)))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* this one is very careful, as it is the first function
 * to parse the userspace data
 */
अटल अंतरभूत पूर्णांक
ebt_check_entry_size_and_hooks(स्थिर काष्ठा ebt_entry *e,
			       स्थिर काष्ठा ebt_table_info *newinfo,
			       अचिन्हित पूर्णांक *n, अचिन्हित पूर्णांक *cnt,
			       अचिन्हित पूर्णांक *totalcnt, अचिन्हित पूर्णांक *udc_cnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
		अगर ((व्योम *)e == (व्योम *)newinfo->hook_entry[i])
			अवरोध;
	पूर्ण
	/* beginning of a new chain
	 * अगर i == NF_BR_NUMHOOKS it must be a user defined chain
	 */
	अगर (i != NF_BR_NUMHOOKS || !e->biपंचांगask) अणु
		/* this checks अगर the previous chain has as many entries
		 * as it said it has
		 */
		अगर (*n != *cnt)
			वापस -EINVAL;

		अगर (((काष्ठा ebt_entries *)e)->policy != EBT_DROP &&
		   ((काष्ठा ebt_entries *)e)->policy != EBT_ACCEPT) अणु
			/* only RETURN from udc */
			अगर (i != NF_BR_NUMHOOKS ||
			   ((काष्ठा ebt_entries *)e)->policy != EBT_RETURN)
				वापस -EINVAL;
		पूर्ण
		अगर (i == NF_BR_NUMHOOKS) /* it's a user defined chain */
			(*udc_cnt)++;
		अगर (((काष्ठा ebt_entries *)e)->counter_offset != *totalcnt)
			वापस -EINVAL;
		*n = ((काष्ठा ebt_entries *)e)->nentries;
		*cnt = 0;
		वापस 0;
	पूर्ण
	/* a plain old entry, heh */
	अगर (माप(काष्ठा ebt_entry) > e->watchers_offset ||
	   e->watchers_offset > e->target_offset ||
	   e->target_offset >= e->next_offset)
		वापस -EINVAL;

	/* this is not checked anywhere अन्यथा */
	अगर (e->next_offset - e->target_offset < माप(काष्ठा ebt_entry_target))
		वापस -EINVAL;

	(*cnt)++;
	(*totalcnt)++;
	वापस 0;
पूर्ण

काष्ठा ebt_cl_stack अणु
	काष्ठा ebt_chainstack cs;
	पूर्णांक from;
	अचिन्हित पूर्णांक hookmask;
पूर्ण;

/* We need these positions to check that the jumps to a dअगरferent part of the
 * entries is a jump to the beginning of a new chain.
 */
अटल अंतरभूत पूर्णांक
ebt_get_udc_positions(काष्ठा ebt_entry *e, काष्ठा ebt_table_info *newinfo,
		      अचिन्हित पूर्णांक *n, काष्ठा ebt_cl_stack *udc)
अणु
	पूर्णांक i;

	/* we're only पूर्णांकerested in chain starts */
	अगर (e->biपंचांगask)
		वापस 0;
	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
		अगर (newinfo->hook_entry[i] == (काष्ठा ebt_entries *)e)
			अवरोध;
	पूर्ण
	/* only care about udc */
	अगर (i != NF_BR_NUMHOOKS)
		वापस 0;

	udc[*n].cs.chaininfo = (काष्ठा ebt_entries *)e;
	/* these initialisations are depended on later in check_chainloops() */
	udc[*n].cs.n = 0;
	udc[*n].hookmask = 0;

	(*n)++;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ebt_cleanup_match(काष्ठा ebt_entry_match *m, काष्ठा net *net, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा xt_mtdtor_param par;

	अगर (i && (*i)-- == 0)
		वापस 1;

	par.net       = net;
	par.match     = m->u.match;
	par.matchinfo = m->data;
	par.family    = NFPROTO_BRIDGE;
	अगर (par.match->destroy != शून्य)
		par.match->destroy(&par);
	module_put(par.match->me);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ebt_cleanup_watcher(काष्ठा ebt_entry_watcher *w, काष्ठा net *net, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा xt_tgdtor_param par;

	अगर (i && (*i)-- == 0)
		वापस 1;

	par.net      = net;
	par.target   = w->u.watcher;
	par.targinfo = w->data;
	par.family   = NFPROTO_BRIDGE;
	अगर (par.target->destroy != शून्य)
		par.target->destroy(&par);
	module_put(par.target->me);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ebt_cleanup_entry(काष्ठा ebt_entry *e, काष्ठा net *net, अचिन्हित पूर्णांक *cnt)
अणु
	काष्ठा xt_tgdtor_param par;
	काष्ठा ebt_entry_target *t;

	अगर (e->biपंचांगask == 0)
		वापस 0;
	/* we're करोne */
	अगर (cnt && (*cnt)-- == 0)
		वापस 1;
	EBT_WATCHER_ITERATE(e, ebt_cleanup_watcher, net, शून्य);
	EBT_MATCH_ITERATE(e, ebt_cleanup_match, net, शून्य);
	t = ebt_get_target(e);

	par.net      = net;
	par.target   = t->u.target;
	par.targinfo = t->data;
	par.family   = NFPROTO_BRIDGE;
	अगर (par.target->destroy != शून्य)
		par.target->destroy(&par);
	module_put(par.target->me);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ebt_check_entry(काष्ठा ebt_entry *e, काष्ठा net *net,
		स्थिर काष्ठा ebt_table_info *newinfo,
		स्थिर अक्षर *name, अचिन्हित पूर्णांक *cnt,
		काष्ठा ebt_cl_stack *cl_s, अचिन्हित पूर्णांक udc_cnt)
अणु
	काष्ठा ebt_entry_target *t;
	काष्ठा xt_target *target;
	अचिन्हित पूर्णांक i, j, hook = 0, hookmask = 0;
	माप_प्रकार gap;
	पूर्णांक ret;
	काष्ठा xt_mtchk_param mtpar;
	काष्ठा xt_tgchk_param tgpar;

	/* करोn't mess with the काष्ठा ebt_entries */
	अगर (e->biपंचांगask == 0)
		वापस 0;

	अगर (e->biपंचांगask & ~EBT_F_MASK)
		वापस -EINVAL;

	अगर (e->invflags & ~EBT_INV_MASK)
		वापस -EINVAL;

	अगर ((e->biपंचांगask & EBT_NOPROTO) && (e->biपंचांगask & EBT_802_3))
		वापस -EINVAL;

	/* what hook करो we beदीर्घ to? */
	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
		अगर (!newinfo->hook_entry[i])
			जारी;
		अगर ((अक्षर *)newinfo->hook_entry[i] < (अक्षर *)e)
			hook = i;
		अन्यथा
			अवरोध;
	पूर्ण
	/* (1 << NF_BR_NUMHOOKS) tells the check functions the rule is on
	 * a base chain
	 */
	अगर (i < NF_BR_NUMHOOKS)
		hookmask = (1 << hook) | (1 << NF_BR_NUMHOOKS);
	अन्यथा अणु
		क्रम (i = 0; i < udc_cnt; i++)
			अगर ((अक्षर *)(cl_s[i].cs.chaininfo) > (अक्षर *)e)
				अवरोध;
		अगर (i == 0)
			hookmask = (1 << hook) | (1 << NF_BR_NUMHOOKS);
		अन्यथा
			hookmask = cl_s[i - 1].hookmask;
	पूर्ण
	i = 0;

	स_रखो(&mtpar, 0, माप(mtpar));
	स_रखो(&tgpar, 0, माप(tgpar));
	mtpar.net	= tgpar.net       = net;
	mtpar.table     = tgpar.table     = name;
	mtpar.entryinfo = tgpar.entryinfo = e;
	mtpar.hook_mask = tgpar.hook_mask = hookmask;
	mtpar.family    = tgpar.family    = NFPROTO_BRIDGE;
	ret = EBT_MATCH_ITERATE(e, ebt_check_match, &mtpar, &i);
	अगर (ret != 0)
		जाओ cleanup_matches;
	j = 0;
	ret = EBT_WATCHER_ITERATE(e, ebt_check_watcher, &tgpar, &j);
	अगर (ret != 0)
		जाओ cleanup_watchers;
	t = ebt_get_target(e);
	gap = e->next_offset - e->target_offset;

	target = xt_request_find_target(NFPROTO_BRIDGE, t->u.name, 0);
	अगर (IS_ERR(target)) अणु
		ret = PTR_ERR(target);
		जाओ cleanup_watchers;
	पूर्ण

	/* Reject UNSPEC, xtables verdicts/वापस values are incompatible */
	अगर (target->family != NFPROTO_BRIDGE) अणु
		module_put(target->me);
		ret = -ENOENT;
		जाओ cleanup_watchers;
	पूर्ण

	t->u.target = target;
	अगर (t->u.target == &ebt_standard_target) अणु
		अगर (gap < माप(काष्ठा ebt_standard_target)) अणु
			ret = -EFAULT;
			जाओ cleanup_watchers;
		पूर्ण
		अगर (((काष्ठा ebt_standard_target *)t)->verdict <
		   -NUM_STANDARD_TARGETS) अणु
			ret = -EFAULT;
			जाओ cleanup_watchers;
		पूर्ण
	पूर्ण अन्यथा अगर (t->target_size > gap - माप(काष्ठा ebt_entry_target)) अणु
		module_put(t->u.target->me);
		ret = -EFAULT;
		जाओ cleanup_watchers;
	पूर्ण

	tgpar.target   = target;
	tgpar.targinfo = t->data;
	ret = xt_check_target(&tgpar, t->target_size,
	      ntohs(e->ethproto), e->invflags & EBT_IPROTO);
	अगर (ret < 0) अणु
		module_put(target->me);
		जाओ cleanup_watchers;
	पूर्ण
	(*cnt)++;
	वापस 0;
cleanup_watchers:
	EBT_WATCHER_ITERATE(e, ebt_cleanup_watcher, net, &j);
cleanup_matches:
	EBT_MATCH_ITERATE(e, ebt_cleanup_match, net, &i);
	वापस ret;
पूर्ण

/* checks क्रम loops and sets the hook mask क्रम udc
 * the hook mask क्रम udc tells us from which base chains the udc can be
 * accessed. This mask is a parameter to the check() functions of the extensions
 */
अटल पूर्णांक check_chainloops(स्थिर काष्ठा ebt_entries *chain, काष्ठा ebt_cl_stack *cl_s,
			    अचिन्हित पूर्णांक udc_cnt, अचिन्हित पूर्णांक hooknr, अक्षर *base)
अणु
	पूर्णांक i, chain_nr = -1, pos = 0, nentries = chain->nentries, verdict;
	स्थिर काष्ठा ebt_entry *e = (काष्ठा ebt_entry *)chain->data;
	स्थिर काष्ठा ebt_entry_target *t;

	जबतक (pos < nentries || chain_nr != -1) अणु
		/* end of udc, go back one 'recursion' step */
		अगर (pos == nentries) अणु
			/* put back values of the समय when this chain was called */
			e = cl_s[chain_nr].cs.e;
			अगर (cl_s[chain_nr].from != -1)
				nentries =
				cl_s[cl_s[chain_nr].from].cs.chaininfo->nentries;
			अन्यथा
				nentries = chain->nentries;
			pos = cl_s[chain_nr].cs.n;
			/* make sure we won't see a loop that isn't one */
			cl_s[chain_nr].cs.n = 0;
			chain_nr = cl_s[chain_nr].from;
			अगर (pos == nentries)
				जारी;
		पूर्ण
		t = ebt_get_target_c(e);
		अगर (म_भेद(t->u.name, EBT_STANDARD_TARGET))
			जाओ letsजारी;
		अगर (e->target_offset + माप(काष्ठा ebt_standard_target) >
		   e->next_offset)
			वापस -1;

		verdict = ((काष्ठा ebt_standard_target *)t)->verdict;
		अगर (verdict >= 0) अणु /* jump to another chain */
			काष्ठा ebt_entries *hlp2 =
			   (काष्ठा ebt_entries *)(base + verdict);
			क्रम (i = 0; i < udc_cnt; i++)
				अगर (hlp2 == cl_s[i].cs.chaininfo)
					अवरोध;
			/* bad destination or loop */
			अगर (i == udc_cnt)
				वापस -1;

			अगर (cl_s[i].cs.n)
				वापस -1;

			अगर (cl_s[i].hookmask & (1 << hooknr))
				जाओ letsजारी;
			/* this can't be 0, so the loop test is correct */
			cl_s[i].cs.n = pos + 1;
			pos = 0;
			cl_s[i].cs.e = ebt_next_entry(e);
			e = (काष्ठा ebt_entry *)(hlp2->data);
			nentries = hlp2->nentries;
			cl_s[i].from = chain_nr;
			chain_nr = i;
			/* this udc is accessible from the base chain क्रम hooknr */
			cl_s[i].hookmask |= (1 << hooknr);
			जारी;
		पूर्ण
letsजारी:
		e = ebt_next_entry(e);
		pos++;
	पूर्ण
	वापस 0;
पूर्ण

/* करो the parsing of the table/chains/entries/matches/watchers/tarमाला_लो, heh */
अटल पूर्णांक translate_table(काष्ठा net *net, स्थिर अक्षर *name,
			   काष्ठा ebt_table_info *newinfo)
अणु
	अचिन्हित पूर्णांक i, j, k, udc_cnt;
	पूर्णांक ret;
	काष्ठा ebt_cl_stack *cl_s = शून्य; /* used in the checking क्रम chain loops */

	i = 0;
	जबतक (i < NF_BR_NUMHOOKS && !newinfo->hook_entry[i])
		i++;
	अगर (i == NF_BR_NUMHOOKS)
		वापस -EINVAL;

	अगर (newinfo->hook_entry[i] != (काष्ठा ebt_entries *)newinfo->entries)
		वापस -EINVAL;

	/* make sure chains are ordered after each other in same order
	 * as their corresponding hooks
	 */
	क्रम (j = i + 1; j < NF_BR_NUMHOOKS; j++) अणु
		अगर (!newinfo->hook_entry[j])
			जारी;
		अगर (newinfo->hook_entry[j] <= newinfo->hook_entry[i])
			वापस -EINVAL;

		i = j;
	पूर्ण

	/* करो some early checkings and initialize some things */
	i = 0; /* holds the expected nr. of entries क्रम the chain */
	j = 0; /* holds the up to now counted entries क्रम the chain */
	k = 0; /* holds the total nr. of entries, should equal
		* newinfo->nentries afterwards
		*/
	udc_cnt = 0; /* will hold the nr. of user defined chains (udc) */
	ret = EBT_ENTRY_ITERATE(newinfo->entries, newinfo->entries_size,
	   ebt_check_entry_size_and_hooks, newinfo,
	   &i, &j, &k, &udc_cnt);

	अगर (ret != 0)
		वापस ret;

	अगर (i != j)
		वापस -EINVAL;

	अगर (k != newinfo->nentries)
		वापस -EINVAL;

	/* get the location of the udc, put them in an array
	 * जबतक we're at it, allocate the chainstack
	 */
	अगर (udc_cnt) अणु
		/* this will get मुक्त'd in करो_replace()/ebt_रेजिस्टर_table()
		 * अगर an error occurs
		 */
		newinfo->chainstack =
			vदो_स्मृति(array_size(nr_cpu_ids,
					   माप(*(newinfo->chainstack))));
		अगर (!newinfo->chainstack)
			वापस -ENOMEM;
		क्रम_each_possible_cpu(i) अणु
			newinfo->chainstack[i] =
			  vदो_स्मृति(array_size(udc_cnt, माप(*(newinfo->chainstack[0]))));
			अगर (!newinfo->chainstack[i]) अणु
				जबतक (i)
					vमुक्त(newinfo->chainstack[--i]);
				vमुक्त(newinfo->chainstack);
				newinfo->chainstack = शून्य;
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		cl_s = vदो_स्मृति(array_size(udc_cnt, माप(*cl_s)));
		अगर (!cl_s)
			वापस -ENOMEM;
		i = 0; /* the i'th udc */
		EBT_ENTRY_ITERATE(newinfo->entries, newinfo->entries_size,
		   ebt_get_udc_positions, newinfo, &i, cl_s);
		/* sanity check */
		अगर (i != udc_cnt) अणु
			vमुक्त(cl_s);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	/* Check क्रम loops */
	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++)
		अगर (newinfo->hook_entry[i])
			अगर (check_chainloops(newinfo->hook_entry[i],
			   cl_s, udc_cnt, i, newinfo->entries)) अणु
				vमुक्त(cl_s);
				वापस -EINVAL;
			पूर्ण

	/* we now know the following (aदीर्घ with E=mcतऑ):
	 *  - the nr of entries in each chain is right
	 *  - the size of the allocated space is right
	 *  - all valid hooks have a corresponding chain
	 *  - there are no loops
	 *  - wrong data can still be on the level of a single entry
	 *  - could be there are jumps to places that are not the
	 *    beginning of a chain. This can only occur in chains that
	 *    are not accessible from any base chains, so we करोn't care.
	 */

	/* used to know what we need to clean up अगर something goes wrong */
	i = 0;
	ret = EBT_ENTRY_ITERATE(newinfo->entries, newinfo->entries_size,
	   ebt_check_entry, net, newinfo, name, &i, cl_s, udc_cnt);
	अगर (ret != 0) अणु
		EBT_ENTRY_ITERATE(newinfo->entries, newinfo->entries_size,
				  ebt_cleanup_entry, net, &i);
	पूर्ण
	vमुक्त(cl_s);
	वापस ret;
पूर्ण

/* called under ग_लिखो_lock */
अटल व्योम get_counters(स्थिर काष्ठा ebt_counter *oldcounters,
			 काष्ठा ebt_counter *counters, अचिन्हित पूर्णांक nentries)
अणु
	पूर्णांक i, cpu;
	काष्ठा ebt_counter *counter_base;

	/* counters of cpu 0 */
	स_नकल(counters, oldcounters,
	       माप(काष्ठा ebt_counter) * nentries);

	/* add other counters to those of cpu 0 */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == 0)
			जारी;
		counter_base = COUNTER_BASE(oldcounters, nentries, cpu);
		क्रम (i = 0; i < nentries; i++)
			ADD_COUNTER(counters[i], counter_base[i].bcnt,
				    counter_base[i].pcnt);
	पूर्ण
पूर्ण

अटल पूर्णांक करो_replace_finish(काष्ठा net *net, काष्ठा ebt_replace *repl,
			      काष्ठा ebt_table_info *newinfo)
अणु
	पूर्णांक ret;
	काष्ठा ebt_counter *countersपंचांगp = शून्य;
	/* used to be able to unlock earlier */
	काष्ठा ebt_table_info *table;
	काष्ठा ebt_table *t;

	/* the user wants counters back
	 * the check on the size is करोne later, when we have the lock
	 */
	अगर (repl->num_counters) अणु
		अचिन्हित दीर्घ size = repl->num_counters * माप(*countersपंचांगp);
		countersपंचांगp = vदो_स्मृति(size);
		अगर (!countersपंचांगp)
			वापस -ENOMEM;
	पूर्ण

	newinfo->chainstack = शून्य;
	ret = ebt_verअगरy_poपूर्णांकers(repl, newinfo);
	अगर (ret != 0)
		जाओ मुक्त_countersपंचांगp;

	ret = translate_table(net, repl->name, newinfo);

	अगर (ret != 0)
		जाओ मुक्त_countersपंचांगp;

	t = find_table_lock(net, repl->name, &ret, &ebt_mutex);
	अगर (!t) अणु
		ret = -ENOENT;
		जाओ मुक्त_iterate;
	पूर्ण

	/* the table करोesn't like it */
	अगर (t->check && (ret = t->check(newinfo, repl->valid_hooks)))
		जाओ मुक्त_unlock;

	अगर (repl->num_counters && repl->num_counters != t->निजी->nentries) अणु
		ret = -EINVAL;
		जाओ मुक्त_unlock;
	पूर्ण

	/* we have the mutex lock, so no danger in पढ़ोing this poपूर्णांकer */
	table = t->निजी;
	/* make sure the table can only be rmmod'ed अगर it contains no rules */
	अगर (!table->nentries && newinfo->nentries && !try_module_get(t->me)) अणु
		ret = -ENOENT;
		जाओ मुक्त_unlock;
	पूर्ण अन्यथा अगर (table->nentries && !newinfo->nentries)
		module_put(t->me);
	/* we need an atomic snapshot of the counters */
	ग_लिखो_lock_bh(&t->lock);
	अगर (repl->num_counters)
		get_counters(t->निजी->counters, countersपंचांगp,
		   t->निजी->nentries);

	t->निजी = newinfo;
	ग_लिखो_unlock_bh(&t->lock);
	mutex_unlock(&ebt_mutex);
	/* so, a user can change the chains जबतक having messed up her counter
	 * allocation. Only reason why this is करोne is because this way the lock
	 * is held only once, जबतक this करोesn't bring the kernel पूर्णांकo a
	 * dangerous state.
	 */
	अगर (repl->num_counters &&
	   copy_to_user(repl->counters, countersपंचांगp,
	   repl->num_counters * माप(काष्ठा ebt_counter))) अणु
		/* Silent error, can't fail, new table is alपढ़ोy in place */
		net_warn_ratelimited("ebtables: counters copy to user failed while replacing table\n");
	पूर्ण

	/* decrease module count and मुक्त resources */
	EBT_ENTRY_ITERATE(table->entries, table->entries_size,
			  ebt_cleanup_entry, net, शून्य);

	vमुक्त(table->entries);
	ebt_मुक्त_table_info(table);
	vमुक्त(table);
	vमुक्त(countersपंचांगp);

	audit_log_nfcfg(repl->name, AF_BRIDGE, repl->nentries,
			AUDIT_XT_OP_REPLACE, GFP_KERNEL);
	वापस ret;

मुक्त_unlock:
	mutex_unlock(&ebt_mutex);
मुक्त_iterate:
	EBT_ENTRY_ITERATE(newinfo->entries, newinfo->entries_size,
			  ebt_cleanup_entry, net, शून्य);
मुक्त_countersपंचांगp:
	vमुक्त(countersपंचांगp);
	/* can be initialized in translate_table() */
	ebt_मुक्त_table_info(newinfo);
	वापस ret;
पूर्ण

/* replace the table */
अटल पूर्णांक करो_replace(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret, countersize;
	काष्ठा ebt_table_info *newinfo;
	काष्ठा ebt_replace पंचांगp;

	अगर (copy_from_sockptr(&पंचांगp, arg, माप(पंचांगp)) != 0)
		वापस -EFAULT;

	अगर (len != माप(पंचांगp) + पंचांगp.entries_size)
		वापस -EINVAL;

	अगर (पंचांगp.entries_size == 0)
		वापस -EINVAL;

	/* overflow check */
	अगर (पंचांगp.nentries >= ((पूर्णांक_उच्च - माप(काष्ठा ebt_table_info)) /
			NR_CPUS - SMP_CACHE_BYTES) / माप(काष्ठा ebt_counter))
		वापस -ENOMEM;
	अगर (पंचांगp.num_counters >= पूर्णांक_उच्च / माप(काष्ठा ebt_counter))
		वापस -ENOMEM;

	पंचांगp.name[माप(पंचांगp.name) - 1] = 0;

	countersize = COUNTER_OFFSET(पंचांगp.nentries) * nr_cpu_ids;
	newinfo = __vदो_स्मृति(माप(*newinfo) + countersize, GFP_KERNEL_ACCOUNT);
	अगर (!newinfo)
		वापस -ENOMEM;

	अगर (countersize)
		स_रखो(newinfo->counters, 0, countersize);

	newinfo->entries = __vदो_स्मृति(पंचांगp.entries_size, GFP_KERNEL_ACCOUNT);
	अगर (!newinfo->entries) अणु
		ret = -ENOMEM;
		जाओ मुक्त_newinfo;
	पूर्ण
	अगर (copy_from_user(
	   newinfo->entries, पंचांगp.entries, पंचांगp.entries_size) != 0) अणु
		ret = -EFAULT;
		जाओ मुक्त_entries;
	पूर्ण

	ret = करो_replace_finish(net, &पंचांगp, newinfo);
	अगर (ret == 0)
		वापस ret;
मुक्त_entries:
	vमुक्त(newinfo->entries);
मुक्त_newinfo:
	vमुक्त(newinfo);
	वापस ret;
पूर्ण

अटल व्योम __ebt_unरेजिस्टर_table(काष्ठा net *net, काष्ठा ebt_table *table)
अणु
	mutex_lock(&ebt_mutex);
	list_del(&table->list);
	mutex_unlock(&ebt_mutex);
	audit_log_nfcfg(table->name, AF_BRIDGE, table->निजी->nentries,
			AUDIT_XT_OP_UNREGISTER, GFP_KERNEL);
	EBT_ENTRY_ITERATE(table->निजी->entries, table->निजी->entries_size,
			  ebt_cleanup_entry, net, शून्य);
	अगर (table->निजी->nentries)
		module_put(table->me);
	vमुक्त(table->निजी->entries);
	ebt_मुक्त_table_info(table->निजी);
	vमुक्त(table->निजी);
	kमुक्त(table->ops);
	kमुक्त(table);
पूर्ण

पूर्णांक ebt_रेजिस्टर_table(काष्ठा net *net, स्थिर काष्ठा ebt_table *input_table,
		       स्थिर काष्ठा nf_hook_ops *ढाँचा_ops)
अणु
	काष्ठा ebt_pernet *ebt_net = net_generic(net, ebt_pernet_id);
	काष्ठा ebt_table_info *newinfo;
	काष्ठा ebt_table *t, *table;
	काष्ठा nf_hook_ops *ops;
	अचिन्हित पूर्णांक num_ops;
	काष्ठा ebt_replace_kernel *repl;
	पूर्णांक ret, i, countersize;
	व्योम *p;

	अगर (input_table == शून्य || (repl = input_table->table) == शून्य ||
	    repl->entries == शून्य || repl->entries_size == 0 ||
	    repl->counters != शून्य || input_table->निजी != शून्य)
		वापस -EINVAL;

	/* Don't add one table to multiple lists. */
	table = kmemdup(input_table, माप(काष्ठा ebt_table), GFP_KERNEL);
	अगर (!table) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	countersize = COUNTER_OFFSET(repl->nentries) * nr_cpu_ids;
	newinfo = vदो_स्मृति(माप(*newinfo) + countersize);
	ret = -ENOMEM;
	अगर (!newinfo)
		जाओ मुक्त_table;

	p = vदो_स्मृति(repl->entries_size);
	अगर (!p)
		जाओ मुक्त_newinfo;

	स_नकल(p, repl->entries, repl->entries_size);
	newinfo->entries = p;

	newinfo->entries_size = repl->entries_size;
	newinfo->nentries = repl->nentries;

	अगर (countersize)
		स_रखो(newinfo->counters, 0, countersize);

	/* fill in newinfo and parse the entries */
	newinfo->chainstack = शून्य;
	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
		अगर ((repl->valid_hooks & (1 << i)) == 0)
			newinfo->hook_entry[i] = शून्य;
		अन्यथा
			newinfo->hook_entry[i] = p +
				((अक्षर *)repl->hook_entry[i] - repl->entries);
	पूर्ण
	ret = translate_table(net, repl->name, newinfo);
	अगर (ret != 0)
		जाओ मुक्त_chainstack;

	अगर (table->check && table->check(newinfo, table->valid_hooks)) अणु
		ret = -EINVAL;
		जाओ मुक्त_chainstack;
	पूर्ण

	table->निजी = newinfo;
	rwlock_init(&table->lock);
	mutex_lock(&ebt_mutex);
	list_क्रम_each_entry(t, &ebt_net->tables, list) अणु
		अगर (म_भेद(t->name, table->name) == 0) अणु
			ret = -EEXIST;
			जाओ मुक्त_unlock;
		पूर्ण
	पूर्ण

	/* Hold a reference count अगर the chains aren't empty */
	अगर (newinfo->nentries && !try_module_get(table->me)) अणु
		ret = -ENOENT;
		जाओ मुक्त_unlock;
	पूर्ण

	num_ops = hweight32(table->valid_hooks);
	अगर (num_ops == 0) अणु
		ret = -EINVAL;
		जाओ मुक्त_unlock;
	पूर्ण

	ops = kmemdup(ढाँचा_ops, माप(*ops) * num_ops, GFP_KERNEL);
	अगर (!ops) अणु
		ret = -ENOMEM;
		अगर (newinfo->nentries)
			module_put(table->me);
		जाओ मुक्त_unlock;
	पूर्ण

	क्रम (i = 0; i < num_ops; i++)
		ops[i].priv = table;

	list_add(&table->list, &ebt_net->tables);
	mutex_unlock(&ebt_mutex);

	table->ops = ops;
	ret = nf_रेजिस्टर_net_hooks(net, ops, num_ops);
	अगर (ret)
		__ebt_unरेजिस्टर_table(net, table);

	audit_log_nfcfg(repl->name, AF_BRIDGE, repl->nentries,
			AUDIT_XT_OP_REGISTER, GFP_KERNEL);
	वापस ret;
मुक्त_unlock:
	mutex_unlock(&ebt_mutex);
मुक्त_chainstack:
	ebt_मुक्त_table_info(newinfo);
	vमुक्त(newinfo->entries);
मुक्त_newinfo:
	vमुक्त(newinfo);
मुक्त_table:
	kमुक्त(table);
out:
	वापस ret;
पूर्ण

अटल काष्ठा ebt_table *__ebt_find_table(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा ebt_pernet *ebt_net = net_generic(net, ebt_pernet_id);
	काष्ठा ebt_table *t;

	mutex_lock(&ebt_mutex);

	list_क्रम_each_entry(t, &ebt_net->tables, list) अणु
		अगर (म_भेद(t->name, name) == 0) अणु
			mutex_unlock(&ebt_mutex);
			वापस t;
		पूर्ण
	पूर्ण

	mutex_unlock(&ebt_mutex);
	वापस शून्य;
पूर्ण

व्योम ebt_unरेजिस्टर_table_pre_निकास(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा ebt_table *table = __ebt_find_table(net, name);

	अगर (table)
		nf_unरेजिस्टर_net_hooks(net, table->ops, hweight32(table->valid_hooks));
पूर्ण
EXPORT_SYMBOL(ebt_unरेजिस्टर_table_pre_निकास);

व्योम ebt_unरेजिस्टर_table(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा ebt_table *table = __ebt_find_table(net, name);

	अगर (table)
		__ebt_unरेजिस्टर_table(net, table);
पूर्ण

/* userspace just supplied us with counters */
अटल पूर्णांक करो_update_counters(काष्ठा net *net, स्थिर अक्षर *name,
			      काष्ठा ebt_counter __user *counters,
			      अचिन्हित पूर्णांक num_counters, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i, ret;
	काष्ठा ebt_counter *पंचांगp;
	काष्ठा ebt_table *t;

	अगर (num_counters == 0)
		वापस -EINVAL;

	पंचांगp = vदो_स्मृति(array_size(num_counters, माप(*पंचांगp)));
	अगर (!पंचांगp)
		वापस -ENOMEM;

	t = find_table_lock(net, name, &ret, &ebt_mutex);
	अगर (!t)
		जाओ मुक्त_पंचांगp;

	अगर (num_counters != t->निजी->nentries) अणु
		ret = -EINVAL;
		जाओ unlock_mutex;
	पूर्ण

	अगर (copy_from_user(पंचांगp, counters, num_counters * माप(*counters))) अणु
		ret = -EFAULT;
		जाओ unlock_mutex;
	पूर्ण

	/* we want an atomic add of the counters */
	ग_लिखो_lock_bh(&t->lock);

	/* we add to the counters of the first cpu */
	क्रम (i = 0; i < num_counters; i++)
		ADD_COUNTER(t->निजी->counters[i], पंचांगp[i].bcnt, पंचांगp[i].pcnt);

	ग_लिखो_unlock_bh(&t->lock);
	ret = 0;
unlock_mutex:
	mutex_unlock(&ebt_mutex);
मुक्त_पंचांगp:
	vमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक update_counters(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ebt_replace hlp;

	अगर (copy_from_sockptr(&hlp, arg, माप(hlp)))
		वापस -EFAULT;

	अगर (len != माप(hlp) + hlp.num_counters * माप(काष्ठा ebt_counter))
		वापस -EINVAL;

	वापस करो_update_counters(net, hlp.name, hlp.counters,
				  hlp.num_counters, len);
पूर्ण

अटल अंतरभूत पूर्णांक ebt_obj_to_user(अक्षर __user *um, स्थिर अक्षर *_name,
				  स्थिर अक्षर *data, पूर्णांक entrysize,
				  पूर्णांक usersize, पूर्णांक datasize, u8 revision)
अणु
	अक्षर name[EBT_EXTENSION_MAXNAMELEN] = अणु0पूर्ण;

	/* ebtables expects 31 bytes दीर्घ names but xt_match names are 29 bytes
	 * दीर्घ. Copy 29 bytes and fill reमुख्यing bytes with zeroes.
	 */
	strlcpy(name, _name, माप(name));
	अगर (copy_to_user(um, name, EBT_EXTENSION_MAXNAMELEN) ||
	    put_user(revision, (u8 __user *)(um + EBT_EXTENSION_MAXNAMELEN)) ||
	    put_user(datasize, (पूर्णांक __user *)(um + EBT_EXTENSION_MAXNAMELEN + 1)) ||
	    xt_data_to_user(um + entrysize, data, usersize, datasize,
			    XT_ALIGN(datasize)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ebt_match_to_user(स्थिर काष्ठा ebt_entry_match *m,
				    स्थिर अक्षर *base, अक्षर __user *ubase)
अणु
	वापस ebt_obj_to_user(ubase + ((अक्षर *)m - base),
			       m->u.match->name, m->data, माप(*m),
			       m->u.match->usersize, m->match_size,
			       m->u.match->revision);
पूर्ण

अटल अंतरभूत पूर्णांक ebt_watcher_to_user(स्थिर काष्ठा ebt_entry_watcher *w,
				      स्थिर अक्षर *base, अक्षर __user *ubase)
अणु
	वापस ebt_obj_to_user(ubase + ((अक्षर *)w - base),
			       w->u.watcher->name, w->data, माप(*w),
			       w->u.watcher->usersize, w->watcher_size,
			       w->u.watcher->revision);
पूर्ण

अटल अंतरभूत पूर्णांक ebt_entry_to_user(काष्ठा ebt_entry *e, स्थिर अक्षर *base,
				    अक्षर __user *ubase)
अणु
	पूर्णांक ret;
	अक्षर __user *hlp;
	स्थिर काष्ठा ebt_entry_target *t;

	अगर (e->biपंचांगask == 0) अणु
		/* special हाल !EBT_ENTRY_OR_ENTRIES */
		अगर (copy_to_user(ubase + ((अक्षर *)e - base), e,
				 माप(काष्ठा ebt_entries)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	अगर (copy_to_user(ubase + ((अक्षर *)e - base), e, माप(*e)))
		वापस -EFAULT;

	hlp = ubase + (((अक्षर *)e + e->target_offset) - base);
	t = ebt_get_target_c(e);

	ret = EBT_MATCH_ITERATE(e, ebt_match_to_user, base, ubase);
	अगर (ret != 0)
		वापस ret;
	ret = EBT_WATCHER_ITERATE(e, ebt_watcher_to_user, base, ubase);
	अगर (ret != 0)
		वापस ret;
	ret = ebt_obj_to_user(hlp, t->u.target->name, t->data, माप(*t),
			      t->u.target->usersize, t->target_size,
			      t->u.target->revision);
	अगर (ret != 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक copy_counters_to_user(काष्ठा ebt_table *t,
				 स्थिर काष्ठा ebt_counter *oldcounters,
				 व्योम __user *user, अचिन्हित पूर्णांक num_counters,
				 अचिन्हित पूर्णांक nentries)
अणु
	काष्ठा ebt_counter *countersपंचांगp;
	पूर्णांक ret = 0;

	/* userspace might not need the counters */
	अगर (num_counters == 0)
		वापस 0;

	अगर (num_counters != nentries)
		वापस -EINVAL;

	countersपंचांगp = vदो_स्मृति(array_size(nentries, माप(*countersपंचांगp)));
	अगर (!countersपंचांगp)
		वापस -ENOMEM;

	ग_लिखो_lock_bh(&t->lock);
	get_counters(oldcounters, countersपंचांगp, nentries);
	ग_लिखो_unlock_bh(&t->lock);

	अगर (copy_to_user(user, countersपंचांगp,
	   nentries * माप(काष्ठा ebt_counter)))
		ret = -EFAULT;
	vमुक्त(countersपंचांगp);
	वापस ret;
पूर्ण

/* called with ebt_mutex locked */
अटल पूर्णांक copy_everything_to_user(काष्ठा ebt_table *t, व्योम __user *user,
				   स्थिर पूर्णांक *len, पूर्णांक cmd)
अणु
	काष्ठा ebt_replace पंचांगp;
	स्थिर काष्ठा ebt_counter *oldcounters;
	अचिन्हित पूर्णांक entries_size, nentries;
	पूर्णांक ret;
	अक्षर *entries;

	अगर (cmd == EBT_SO_GET_ENTRIES) अणु
		entries_size = t->निजी->entries_size;
		nentries = t->निजी->nentries;
		entries = t->निजी->entries;
		oldcounters = t->निजी->counters;
	पूर्ण अन्यथा अणु
		entries_size = t->table->entries_size;
		nentries = t->table->nentries;
		entries = t->table->entries;
		oldcounters = t->table->counters;
	पूर्ण

	अगर (copy_from_user(&पंचांगp, user, माप(पंचांगp)))
		वापस -EFAULT;

	अगर (*len != माप(काष्ठा ebt_replace) + entries_size +
	   (पंचांगp.num_counters ? nentries * माप(काष्ठा ebt_counter) : 0))
		वापस -EINVAL;

	अगर (पंचांगp.nentries != nentries)
		वापस -EINVAL;

	अगर (पंचांगp.entries_size != entries_size)
		वापस -EINVAL;

	ret = copy_counters_to_user(t, oldcounters, पंचांगp.counters,
					पंचांगp.num_counters, nentries);
	अगर (ret)
		वापस ret;

	/* set the match/watcher/target names right */
	वापस EBT_ENTRY_ITERATE(entries, entries_size,
	   ebt_entry_to_user, entries, पंचांगp.entries);
पूर्ण

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
/* 32 bit-userspace compatibility definitions. */
काष्ठा compat_ebt_replace अणु
	अक्षर name[EBT_TABLE_MAXNAMELEN];
	compat_uपूर्णांक_t valid_hooks;
	compat_uपूर्णांक_t nentries;
	compat_uपूर्णांक_t entries_size;
	/* start of the chains */
	compat_uptr_t hook_entry[NF_BR_NUMHOOKS];
	/* nr of counters userspace expects back */
	compat_uपूर्णांक_t num_counters;
	/* where the kernel will put the old counters. */
	compat_uptr_t counters;
	compat_uptr_t entries;
पूर्ण;

/* काष्ठा ebt_entry_match, _target and _watcher have same layout */
काष्ठा compat_ebt_entry_mwt अणु
	जोड़ अणु
		काष्ठा अणु
			अक्षर name[EBT_EXTENSION_MAXNAMELEN];
			u8 revision;
		पूर्ण;
		compat_uptr_t ptr;
	पूर्ण u;
	compat_uपूर्णांक_t match_size;
	compat_uपूर्णांक_t data[] __aligned(__alignof__(काष्ठा compat_ebt_replace));
पूर्ण;

/* account क्रम possible padding between match_size and ->data */
अटल पूर्णांक ebt_compat_entry_padsize(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा ebt_entry_match) <
			माप(काष्ठा compat_ebt_entry_mwt));
	वापस (पूर्णांक) माप(काष्ठा ebt_entry_match) -
			माप(काष्ठा compat_ebt_entry_mwt);
पूर्ण

अटल पूर्णांक ebt_compat_match_offset(स्थिर काष्ठा xt_match *match,
				   अचिन्हित पूर्णांक userlen)
अणु
	/* ebt_among needs special handling. The kernel .matchsize is
	 * set to -1 at registration समय; at runसमय an EBT_ALIGN()ed
	 * value is expected.
	 * Example: userspace sends 4500, ebt_among.c wants 4504.
	 */
	अगर (unlikely(match->matchsize == -1))
		वापस XT_ALIGN(userlen) - COMPAT_XT_ALIGN(userlen);
	वापस xt_compat_match_offset(match);
पूर्ण

अटल पूर्णांक compat_match_to_user(काष्ठा ebt_entry_match *m, व्योम __user **dstptr,
				अचिन्हित पूर्णांक *size)
अणु
	स्थिर काष्ठा xt_match *match = m->u.match;
	काष्ठा compat_ebt_entry_mwt __user *cm = *dstptr;
	पूर्णांक off = ebt_compat_match_offset(match, m->match_size);
	compat_uपूर्णांक_t msize = m->match_size - off;

	अगर (WARN_ON(off >= m->match_size))
		वापस -EINVAL;

	अगर (copy_to_user(cm->u.name, match->name, म_माप(match->name) + 1) ||
	    put_user(match->revision, &cm->u.revision) ||
	    put_user(msize, &cm->match_size))
		वापस -EFAULT;

	अगर (match->compat_to_user) अणु
		अगर (match->compat_to_user(cm->data, m->data))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (xt_data_to_user(cm->data, m->data, match->usersize, msize,
				    COMPAT_XT_ALIGN(msize)))
			वापस -EFAULT;
	पूर्ण

	*size -= ebt_compat_entry_padsize() + off;
	*dstptr = cm->data;
	*dstptr += msize;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_target_to_user(काष्ठा ebt_entry_target *t,
				 व्योम __user **dstptr,
				 अचिन्हित पूर्णांक *size)
अणु
	स्थिर काष्ठा xt_target *target = t->u.target;
	काष्ठा compat_ebt_entry_mwt __user *cm = *dstptr;
	पूर्णांक off = xt_compat_target_offset(target);
	compat_uपूर्णांक_t tsize = t->target_size - off;

	अगर (WARN_ON(off >= t->target_size))
		वापस -EINVAL;

	अगर (copy_to_user(cm->u.name, target->name, म_माप(target->name) + 1) ||
	    put_user(target->revision, &cm->u.revision) ||
	    put_user(tsize, &cm->match_size))
		वापस -EFAULT;

	अगर (target->compat_to_user) अणु
		अगर (target->compat_to_user(cm->data, t->data))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (xt_data_to_user(cm->data, t->data, target->usersize, tsize,
				    COMPAT_XT_ALIGN(tsize)))
			वापस -EFAULT;
	पूर्ण

	*size -= ebt_compat_entry_padsize() + off;
	*dstptr = cm->data;
	*dstptr += tsize;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_watcher_to_user(काष्ठा ebt_entry_watcher *w,
				  व्योम __user **dstptr,
				  अचिन्हित पूर्णांक *size)
अणु
	वापस compat_target_to_user((काष्ठा ebt_entry_target *)w,
							dstptr, size);
पूर्ण

अटल पूर्णांक compat_copy_entry_to_user(काष्ठा ebt_entry *e, व्योम __user **dstptr,
				अचिन्हित पूर्णांक *size)
अणु
	काष्ठा ebt_entry_target *t;
	काष्ठा ebt_entry __user *ce;
	u32 watchers_offset, target_offset, next_offset;
	compat_uपूर्णांक_t origsize;
	पूर्णांक ret;

	अगर (e->biपंचांगask == 0) अणु
		अगर (*size < माप(काष्ठा ebt_entries))
			वापस -EINVAL;
		अगर (copy_to_user(*dstptr, e, माप(काष्ठा ebt_entries)))
			वापस -EFAULT;

		*dstptr += माप(काष्ठा ebt_entries);
		*size -= माप(काष्ठा ebt_entries);
		वापस 0;
	पूर्ण

	अगर (*size < माप(*ce))
		वापस -EINVAL;

	ce = *dstptr;
	अगर (copy_to_user(ce, e, माप(*ce)))
		वापस -EFAULT;

	origsize = *size;
	*dstptr += माप(*ce);

	ret = EBT_MATCH_ITERATE(e, compat_match_to_user, dstptr, size);
	अगर (ret)
		वापस ret;
	watchers_offset = e->watchers_offset - (origsize - *size);

	ret = EBT_WATCHER_ITERATE(e, compat_watcher_to_user, dstptr, size);
	अगर (ret)
		वापस ret;
	target_offset = e->target_offset - (origsize - *size);

	t = ebt_get_target(e);

	ret = compat_target_to_user(t, dstptr, size);
	अगर (ret)
		वापस ret;
	next_offset = e->next_offset - (origsize - *size);

	अगर (put_user(watchers_offset, &ce->watchers_offset) ||
	    put_user(target_offset, &ce->target_offset) ||
	    put_user(next_offset, &ce->next_offset))
		वापस -EFAULT;

	*size -= माप(*ce);
	वापस 0;
पूर्ण

अटल पूर्णांक compat_calc_match(काष्ठा ebt_entry_match *m, पूर्णांक *off)
अणु
	*off += ebt_compat_match_offset(m->u.match, m->match_size);
	*off += ebt_compat_entry_padsize();
	वापस 0;
पूर्ण

अटल पूर्णांक compat_calc_watcher(काष्ठा ebt_entry_watcher *w, पूर्णांक *off)
अणु
	*off += xt_compat_target_offset(w->u.watcher);
	*off += ebt_compat_entry_padsize();
	वापस 0;
पूर्ण

अटल पूर्णांक compat_calc_entry(स्थिर काष्ठा ebt_entry *e,
			     स्थिर काष्ठा ebt_table_info *info,
			     स्थिर व्योम *base,
			     काष्ठा compat_ebt_replace *newinfo)
अणु
	स्थिर काष्ठा ebt_entry_target *t;
	अचिन्हित पूर्णांक entry_offset;
	पूर्णांक off, ret, i;

	अगर (e->biपंचांगask == 0)
		वापस 0;

	off = 0;
	entry_offset = (व्योम *)e - base;

	EBT_MATCH_ITERATE(e, compat_calc_match, &off);
	EBT_WATCHER_ITERATE(e, compat_calc_watcher, &off);

	t = ebt_get_target_c(e);

	off += xt_compat_target_offset(t->u.target);
	off += ebt_compat_entry_padsize();

	newinfo->entries_size -= off;

	ret = xt_compat_add_offset(NFPROTO_BRIDGE, entry_offset, off);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
		स्थिर व्योम *hookptr = info->hook_entry[i];
		अगर (info->hook_entry[i] &&
		    (e < (काष्ठा ebt_entry *)(base - hookptr))) अणु
			newinfo->hook_entry[i] -= off;
			pr_debug("0x%08X -> 0x%08X\n",
					newinfo->hook_entry[i] + off,
					newinfo->hook_entry[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ebt_compat_init_offsets(अचिन्हित पूर्णांक number)
अणु
	अगर (number > पूर्णांक_उच्च)
		वापस -EINVAL;

	/* also count the base chain policies */
	number += NF_BR_NUMHOOKS;

	वापस xt_compat_init_offsets(NFPROTO_BRIDGE, number);
पूर्ण

अटल पूर्णांक compat_table_info(स्थिर काष्ठा ebt_table_info *info,
			     काष्ठा compat_ebt_replace *newinfo)
अणु
	अचिन्हित पूर्णांक size = info->entries_size;
	स्थिर व्योम *entries = info->entries;
	पूर्णांक ret;

	newinfo->entries_size = size;
	ret = ebt_compat_init_offsets(info->nentries);
	अगर (ret)
		वापस ret;

	वापस EBT_ENTRY_ITERATE(entries, size, compat_calc_entry, info,
							entries, newinfo);
पूर्ण

अटल पूर्णांक compat_copy_everything_to_user(काष्ठा ebt_table *t,
					  व्योम __user *user, पूर्णांक *len, पूर्णांक cmd)
अणु
	काष्ठा compat_ebt_replace repl, पंचांगp;
	काष्ठा ebt_counter *oldcounters;
	काष्ठा ebt_table_info tinfo;
	पूर्णांक ret;
	व्योम __user *pos;

	स_रखो(&tinfo, 0, माप(tinfo));

	अगर (cmd == EBT_SO_GET_ENTRIES) अणु
		tinfo.entries_size = t->निजी->entries_size;
		tinfo.nentries = t->निजी->nentries;
		tinfo.entries = t->निजी->entries;
		oldcounters = t->निजी->counters;
	पूर्ण अन्यथा अणु
		tinfo.entries_size = t->table->entries_size;
		tinfo.nentries = t->table->nentries;
		tinfo.entries = t->table->entries;
		oldcounters = t->table->counters;
	पूर्ण

	अगर (copy_from_user(&पंचांगp, user, माप(पंचांगp)))
		वापस -EFAULT;

	अगर (पंचांगp.nentries != tinfo.nentries ||
	   (पंचांगp.num_counters && पंचांगp.num_counters != tinfo.nentries))
		वापस -EINVAL;

	स_नकल(&repl, &पंचांगp, माप(repl));
	अगर (cmd == EBT_SO_GET_ENTRIES)
		ret = compat_table_info(t->निजी, &repl);
	अन्यथा
		ret = compat_table_info(&tinfo, &repl);
	अगर (ret)
		वापस ret;

	अगर (*len != माप(पंचांगp) + repl.entries_size +
	   (पंचांगp.num_counters? tinfo.nentries * माप(काष्ठा ebt_counter): 0)) अणु
		pr_err("wrong size: *len %d, entries_size %u, replsz %d\n",
				*len, tinfo.entries_size, repl.entries_size);
		वापस -EINVAL;
	पूर्ण

	/* userspace might not need the counters */
	ret = copy_counters_to_user(t, oldcounters, compat_ptr(पंचांगp.counters),
					पंचांगp.num_counters, tinfo.nentries);
	अगर (ret)
		वापस ret;

	pos = compat_ptr(पंचांगp.entries);
	वापस EBT_ENTRY_ITERATE(tinfo.entries, tinfo.entries_size,
			compat_copy_entry_to_user, &pos, &पंचांगp.entries_size);
पूर्ण

काष्ठा ebt_entries_buf_state अणु
	अक्षर *buf_kern_start;	/* kernel buffer to copy (translated) data to */
	u32 buf_kern_len;	/* total size of kernel buffer */
	u32 buf_kern_offset;	/* amount of data copied so far */
	u32 buf_user_offset;	/* पढ़ो position in userspace buffer */
पूर्ण;

अटल पूर्णांक ebt_buf_count(काष्ठा ebt_entries_buf_state *state, अचिन्हित पूर्णांक sz)
अणु
	state->buf_kern_offset += sz;
	वापस state->buf_kern_offset >= sz ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक ebt_buf_add(काष्ठा ebt_entries_buf_state *state,
		       स्थिर व्योम *data, अचिन्हित पूर्णांक sz)
अणु
	अगर (state->buf_kern_start == शून्य)
		जाओ count_only;

	अगर (WARN_ON(state->buf_kern_offset + sz > state->buf_kern_len))
		वापस -EINVAL;

	स_नकल(state->buf_kern_start + state->buf_kern_offset, data, sz);

 count_only:
	state->buf_user_offset += sz;
	वापस ebt_buf_count(state, sz);
पूर्ण

अटल पूर्णांक ebt_buf_add_pad(काष्ठा ebt_entries_buf_state *state, अचिन्हित पूर्णांक sz)
अणु
	अक्षर *b = state->buf_kern_start;

	अगर (WARN_ON(b && state->buf_kern_offset > state->buf_kern_len))
		वापस -EINVAL;

	अगर (b != शून्य && sz > 0)
		स_रखो(b + state->buf_kern_offset, 0, sz);
	/* करो not adjust ->buf_user_offset here, we added kernel-side padding */
	वापस ebt_buf_count(state, sz);
पूर्ण

क्रमागत compat_mwt अणु
	EBT_COMPAT_MATCH,
	EBT_COMPAT_WATCHER,
	EBT_COMPAT_TARGET,
पूर्ण;

अटल पूर्णांक compat_mtw_from_user(स्थिर काष्ठा compat_ebt_entry_mwt *mwt,
				क्रमागत compat_mwt compat_mwt,
				काष्ठा ebt_entries_buf_state *state,
				स्थिर अचिन्हित अक्षर *base)
अणु
	अक्षर name[EBT_EXTENSION_MAXNAMELEN];
	काष्ठा xt_match *match;
	काष्ठा xt_target *wt;
	व्योम *dst = शून्य;
	पूर्णांक off, pad = 0;
	अचिन्हित पूर्णांक size_kern, match_size = mwt->match_size;

	अगर (strscpy(name, mwt->u.name, माप(name)) < 0)
		वापस -EINVAL;

	अगर (state->buf_kern_start)
		dst = state->buf_kern_start + state->buf_kern_offset;

	चयन (compat_mwt) अणु
	हाल EBT_COMPAT_MATCH:
		match = xt_request_find_match(NFPROTO_BRIDGE, name,
					      mwt->u.revision);
		अगर (IS_ERR(match))
			वापस PTR_ERR(match);

		off = ebt_compat_match_offset(match, match_size);
		अगर (dst) अणु
			अगर (match->compat_from_user)
				match->compat_from_user(dst, mwt->data);
			अन्यथा
				स_नकल(dst, mwt->data, match_size);
		पूर्ण

		size_kern = match->matchsize;
		अगर (unlikely(size_kern == -1))
			size_kern = match_size;
		module_put(match->me);
		अवरोध;
	हाल EBT_COMPAT_WATCHER:
	हाल EBT_COMPAT_TARGET:
		wt = xt_request_find_target(NFPROTO_BRIDGE, name,
					    mwt->u.revision);
		अगर (IS_ERR(wt))
			वापस PTR_ERR(wt);
		off = xt_compat_target_offset(wt);

		अगर (dst) अणु
			अगर (wt->compat_from_user)
				wt->compat_from_user(dst, mwt->data);
			अन्यथा
				स_नकल(dst, mwt->data, match_size);
		पूर्ण

		size_kern = wt->tarमाला_लोize;
		module_put(wt->me);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	state->buf_kern_offset += match_size + off;
	state->buf_user_offset += match_size;
	pad = XT_ALIGN(size_kern) - size_kern;

	अगर (pad > 0 && dst) अणु
		अगर (WARN_ON(state->buf_kern_len <= pad))
			वापस -EINVAL;
		अगर (WARN_ON(state->buf_kern_offset - (match_size + off) + size_kern > state->buf_kern_len - pad))
			वापस -EINVAL;
		स_रखो(dst + size_kern, 0, pad);
	पूर्ण
	वापस off + match_size;
पूर्ण

/* वापस size of all matches, watchers or target, including necessary
 * alignment and padding.
 */
अटल पूर्णांक ebt_size_mwt(स्थिर काष्ठा compat_ebt_entry_mwt *match32,
			अचिन्हित पूर्णांक size_left, क्रमागत compat_mwt type,
			काष्ठा ebt_entries_buf_state *state, स्थिर व्योम *base)
अणु
	स्थिर अक्षर *buf = (स्थिर अक्षर *)match32;
	पूर्णांक growth = 0;

	अगर (size_left == 0)
		वापस 0;

	करो अणु
		काष्ठा ebt_entry_match *match_kern;
		पूर्णांक ret;

		अगर (size_left < माप(*match32))
			वापस -EINVAL;

		match_kern = (काष्ठा ebt_entry_match *) state->buf_kern_start;
		अगर (match_kern) अणु
			अक्षर *पंचांगp;
			पंचांगp = state->buf_kern_start + state->buf_kern_offset;
			match_kern = (काष्ठा ebt_entry_match *) पंचांगp;
		पूर्ण
		ret = ebt_buf_add(state, buf, माप(*match32));
		अगर (ret < 0)
			वापस ret;
		size_left -= माप(*match32);

		/* add padding beक्रमe match->data (अगर any) */
		ret = ebt_buf_add_pad(state, ebt_compat_entry_padsize());
		अगर (ret < 0)
			वापस ret;

		अगर (match32->match_size > size_left)
			वापस -EINVAL;

		size_left -= match32->match_size;

		ret = compat_mtw_from_user(match32, type, state, base);
		अगर (ret < 0)
			वापस ret;

		अगर (WARN_ON(ret < match32->match_size))
			वापस -EINVAL;
		growth += ret - match32->match_size;
		growth += ebt_compat_entry_padsize();

		buf += माप(*match32);
		buf += match32->match_size;

		अगर (match_kern)
			match_kern->match_size = ret;

		match32 = (काष्ठा compat_ebt_entry_mwt *) buf;
	पूर्ण जबतक (size_left);

	वापस growth;
पूर्ण

/* called क्रम all ebt_entry काष्ठाures. */
अटल पूर्णांक size_entry_mwt(स्थिर काष्ठा ebt_entry *entry, स्थिर अचिन्हित अक्षर *base,
			  अचिन्हित पूर्णांक *total,
			  काष्ठा ebt_entries_buf_state *state)
अणु
	अचिन्हित पूर्णांक i, j, startoff, next_expected_off, new_offset = 0;
	/* stores match/watchers/tarमाला_लो & offset of next काष्ठा ebt_entry: */
	अचिन्हित पूर्णांक offsets[4];
	अचिन्हित पूर्णांक *offsets_update = शून्य;
	पूर्णांक ret;
	अक्षर *buf_start;

	अगर (*total < माप(काष्ठा ebt_entries))
		वापस -EINVAL;

	अगर (!entry->biपंचांगask) अणु
		*total -= माप(काष्ठा ebt_entries);
		वापस ebt_buf_add(state, entry, माप(काष्ठा ebt_entries));
	पूर्ण
	अगर (*total < माप(*entry) || entry->next_offset < माप(*entry))
		वापस -EINVAL;

	startoff = state->buf_user_offset;
	/* pull in most part of ebt_entry, it करोes not need to be changed. */
	ret = ebt_buf_add(state, entry,
			दुरत्व(काष्ठा ebt_entry, watchers_offset));
	अगर (ret < 0)
		वापस ret;

	offsets[0] = माप(काष्ठा ebt_entry); /* matches come first */
	स_नकल(&offsets[1], &entry->watchers_offset,
			माप(offsets) - माप(offsets[0]));

	अगर (state->buf_kern_start) अणु
		buf_start = state->buf_kern_start + state->buf_kern_offset;
		offsets_update = (अचिन्हित पूर्णांक *) buf_start;
	पूर्ण
	ret = ebt_buf_add(state, &offsets[1],
			माप(offsets) - माप(offsets[0]));
	अगर (ret < 0)
		वापस ret;
	buf_start = (अक्षर *) entry;
	/* 0: matches offset, always follows ebt_entry.
	 * 1: watchers offset, from ebt_entry काष्ठाure
	 * 2: target offset, from ebt_entry काष्ठाure
	 * 3: next ebt_entry offset, from ebt_entry काष्ठाure
	 *
	 * offsets are relative to beginning of काष्ठा ebt_entry (i.e., 0).
	 */
	क्रम (i = 0; i < 4 ; ++i) अणु
		अगर (offsets[i] > *total)
			वापस -EINVAL;

		अगर (i < 3 && offsets[i] == *total)
			वापस -EINVAL;

		अगर (i == 0)
			जारी;
		अगर (offsets[i-1] > offsets[i])
			वापस -EINVAL;
	पूर्ण

	क्रम (i = 0, j = 1 ; j < 4 ; j++, i++) अणु
		काष्ठा compat_ebt_entry_mwt *match32;
		अचिन्हित पूर्णांक size;
		अक्षर *buf = buf_start + offsets[i];

		अगर (offsets[i] > offsets[j])
			वापस -EINVAL;

		match32 = (काष्ठा compat_ebt_entry_mwt *) buf;
		size = offsets[j] - offsets[i];
		ret = ebt_size_mwt(match32, size, i, state, base);
		अगर (ret < 0)
			वापस ret;
		new_offset += ret;
		अगर (offsets_update && new_offset) अणु
			pr_debug("change offset %d to %d\n",
				offsets_update[i], offsets[j] + new_offset);
			offsets_update[i] = offsets[j] + new_offset;
		पूर्ण
	पूर्ण

	अगर (state->buf_kern_start == शून्य) अणु
		अचिन्हित पूर्णांक offset = buf_start - (अक्षर *) base;

		ret = xt_compat_add_offset(NFPROTO_BRIDGE, offset, new_offset);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	next_expected_off = state->buf_user_offset - startoff;
	अगर (next_expected_off != entry->next_offset)
		वापस -EINVAL;

	अगर (*total < entry->next_offset)
		वापस -EINVAL;
	*total -= entry->next_offset;
	वापस 0;
पूर्ण

/* repl->entries_size is the size of the ebt_entry blob in userspace.
 * It might need more memory when copied to a 64 bit kernel in हाल
 * userspace is 32-bit. So, first task: find out how much memory is needed.
 *
 * Called beक्रमe validation is perक्रमmed.
 */
अटल पूर्णांक compat_copy_entries(अचिन्हित अक्षर *data, अचिन्हित पूर्णांक size_user,
				काष्ठा ebt_entries_buf_state *state)
अणु
	अचिन्हित पूर्णांक size_reमुख्यing = size_user;
	पूर्णांक ret;

	ret = EBT_ENTRY_ITERATE(data, size_user, size_entry_mwt, data,
					&size_reमुख्यing, state);
	अगर (ret < 0)
		वापस ret;

	अगर (size_reमुख्यing)
		वापस -EINVAL;

	वापस state->buf_kern_offset;
पूर्ण


अटल पूर्णांक compat_copy_ebt_replace_from_user(काष्ठा ebt_replace *repl,
					     sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	काष्ठा compat_ebt_replace पंचांगp;
	पूर्णांक i;

	अगर (len < माप(पंचांगp))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&पंचांगp, arg, माप(पंचांगp)))
		वापस -EFAULT;

	अगर (len != माप(पंचांगp) + पंचांगp.entries_size)
		वापस -EINVAL;

	अगर (पंचांगp.entries_size == 0)
		वापस -EINVAL;

	अगर (पंचांगp.nentries >= ((पूर्णांक_उच्च - माप(काष्ठा ebt_table_info)) /
			NR_CPUS - SMP_CACHE_BYTES) / माप(काष्ठा ebt_counter))
		वापस -ENOMEM;
	अगर (पंचांगp.num_counters >= पूर्णांक_उच्च / माप(काष्ठा ebt_counter))
		वापस -ENOMEM;

	स_नकल(repl, &पंचांगp, दुरत्व(काष्ठा ebt_replace, hook_entry));

	/* starting with hook_entry, 32 vs. 64 bit काष्ठाures are dअगरferent */
	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++)
		repl->hook_entry[i] = compat_ptr(पंचांगp.hook_entry[i]);

	repl->num_counters = पंचांगp.num_counters;
	repl->counters = compat_ptr(पंचांगp.counters);
	repl->entries = compat_ptr(पंचांगp.entries);
	वापस 0;
पूर्ण

अटल पूर्णांक compat_करो_replace(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret, i, countersize, size64;
	काष्ठा ebt_table_info *newinfo;
	काष्ठा ebt_replace पंचांगp;
	काष्ठा ebt_entries_buf_state state;
	व्योम *entries_पंचांगp;

	ret = compat_copy_ebt_replace_from_user(&पंचांगp, arg, len);
	अगर (ret) अणु
		/* try real handler in हाल userland supplied needed padding */
		अगर (ret == -EINVAL && करो_replace(net, arg, len) == 0)
			ret = 0;
		वापस ret;
	पूर्ण

	countersize = COUNTER_OFFSET(पंचांगp.nentries) * nr_cpu_ids;
	newinfo = vदो_स्मृति(माप(*newinfo) + countersize);
	अगर (!newinfo)
		वापस -ENOMEM;

	अगर (countersize)
		स_रखो(newinfo->counters, 0, countersize);

	स_रखो(&state, 0, माप(state));

	newinfo->entries = vदो_स्मृति(पंचांगp.entries_size);
	अगर (!newinfo->entries) अणु
		ret = -ENOMEM;
		जाओ मुक्त_newinfo;
	पूर्ण
	अगर (copy_from_user(
	   newinfo->entries, पंचांगp.entries, पंचांगp.entries_size) != 0) अणु
		ret = -EFAULT;
		जाओ मुक्त_entries;
	पूर्ण

	entries_पंचांगp = newinfo->entries;

	xt_compat_lock(NFPROTO_BRIDGE);

	ret = ebt_compat_init_offsets(पंचांगp.nentries);
	अगर (ret < 0)
		जाओ out_unlock;

	ret = compat_copy_entries(entries_पंचांगp, पंचांगp.entries_size, &state);
	अगर (ret < 0)
		जाओ out_unlock;

	pr_debug("tmp.entries_size %d, kern off %d, user off %d delta %d\n",
		पंचांगp.entries_size, state.buf_kern_offset, state.buf_user_offset,
		xt_compat_calc_jump(NFPROTO_BRIDGE, पंचांगp.entries_size));

	size64 = ret;
	newinfo->entries = vदो_स्मृति(size64);
	अगर (!newinfo->entries) अणु
		vमुक्त(entries_पंचांगp);
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	स_रखो(&state, 0, माप(state));
	state.buf_kern_start = newinfo->entries;
	state.buf_kern_len = size64;

	ret = compat_copy_entries(entries_पंचांगp, पंचांगp.entries_size, &state);
	अगर (WARN_ON(ret < 0)) अणु
		vमुक्त(entries_पंचांगp);
		जाओ out_unlock;
	पूर्ण

	vमुक्त(entries_पंचांगp);
	पंचांगp.entries_size = size64;

	क्रम (i = 0; i < NF_BR_NUMHOOKS; i++) अणु
		अक्षर __user *usrptr;
		अगर (पंचांगp.hook_entry[i]) अणु
			अचिन्हित पूर्णांक delta;
			usrptr = (अक्षर __user *) पंचांगp.hook_entry[i];
			delta = usrptr - पंचांगp.entries;
			usrptr += xt_compat_calc_jump(NFPROTO_BRIDGE, delta);
			पंचांगp.hook_entry[i] = (काष्ठा ebt_entries __user *)usrptr;
		पूर्ण
	पूर्ण

	xt_compat_flush_offsets(NFPROTO_BRIDGE);
	xt_compat_unlock(NFPROTO_BRIDGE);

	ret = करो_replace_finish(net, &पंचांगp, newinfo);
	अगर (ret == 0)
		वापस ret;
मुक्त_entries:
	vमुक्त(newinfo->entries);
मुक्त_newinfo:
	vमुक्त(newinfo);
	वापस ret;
out_unlock:
	xt_compat_flush_offsets(NFPROTO_BRIDGE);
	xt_compat_unlock(NFPROTO_BRIDGE);
	जाओ मुक्त_entries;
पूर्ण

अटल पूर्णांक compat_update_counters(काष्ठा net *net, sockptr_t arg,
				  अचिन्हित पूर्णांक len)
अणु
	काष्ठा compat_ebt_replace hlp;

	अगर (copy_from_sockptr(&hlp, arg, माप(hlp)))
		वापस -EFAULT;

	/* try real handler in हाल userland supplied needed padding */
	अगर (len != माप(hlp) + hlp.num_counters * माप(काष्ठा ebt_counter))
		वापस update_counters(net, arg, len);

	वापस करो_update_counters(net, hlp.name, compat_ptr(hlp.counters),
				  hlp.num_counters, len);
पूर्ण

अटल पूर्णांक compat_करो_ebt_get_ctl(काष्ठा sock *sk, पूर्णांक cmd,
		व्योम __user *user, पूर्णांक *len)
अणु
	पूर्णांक ret;
	काष्ठा compat_ebt_replace पंचांगp;
	काष्ठा ebt_table *t;
	काष्ठा net *net = sock_net(sk);

	अगर ((cmd == EBT_SO_GET_INFO || cmd == EBT_SO_GET_INIT_INFO) &&
	    *len != माप(काष्ठा compat_ebt_replace))
		वापस -EINVAL;

	अगर (copy_from_user(&पंचांगp, user, माप(पंचांगp)))
		वापस -EFAULT;

	पंचांगp.name[माप(पंचांगp.name) - 1] = '\0';

	t = find_table_lock(net, पंचांगp.name, &ret, &ebt_mutex);
	अगर (!t)
		वापस ret;

	xt_compat_lock(NFPROTO_BRIDGE);
	चयन (cmd) अणु
	हाल EBT_SO_GET_INFO:
		पंचांगp.nentries = t->निजी->nentries;
		ret = compat_table_info(t->निजी, &पंचांगp);
		अगर (ret)
			जाओ out;
		पंचांगp.valid_hooks = t->valid_hooks;

		अगर (copy_to_user(user, &पंचांगp, *len) != 0) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ret = 0;
		अवरोध;
	हाल EBT_SO_GET_INIT_INFO:
		पंचांगp.nentries = t->table->nentries;
		पंचांगp.entries_size = t->table->entries_size;
		पंचांगp.valid_hooks = t->table->valid_hooks;

		अगर (copy_to_user(user, &पंचांगp, *len) != 0) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ret = 0;
		अवरोध;
	हाल EBT_SO_GET_ENTRIES:
	हाल EBT_SO_GET_INIT_ENTRIES:
		/* try real handler first in हाल of userland-side padding.
		 * in हाल we are dealing with an 'ordinary' 32 bit binary
		 * without 64bit compatibility padding, this will fail right
		 * after copy_from_user when the *len argument is validated.
		 *
		 * the compat_ variant needs to करो one pass over the kernel
		 * data set to adjust क्रम size dअगरferences beक्रमe it the check.
		 */
		अगर (copy_everything_to_user(t, user, len, cmd) == 0)
			ret = 0;
		अन्यथा
			ret = compat_copy_everything_to_user(t, user, len, cmd);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
 out:
	xt_compat_flush_offsets(NFPROTO_BRIDGE);
	xt_compat_unlock(NFPROTO_BRIDGE);
	mutex_unlock(&ebt_mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक करो_ebt_get_ctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *user, पूर्णांक *len)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा ebt_replace पंचांगp;
	काष्ठा ebt_table *t;
	पूर्णांक ret;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	/* try real handler in हाल userland supplied needed padding */
	अगर (in_compat_syscall() &&
	    ((cmd != EBT_SO_GET_INFO && cmd != EBT_SO_GET_INIT_INFO) ||
	     *len != माप(पंचांगp)))
		वापस compat_करो_ebt_get_ctl(sk, cmd, user, len);
#पूर्ण_अगर

	अगर (copy_from_user(&पंचांगp, user, माप(पंचांगp)))
		वापस -EFAULT;

	पंचांगp.name[माप(पंचांगp.name) - 1] = '\0';

	t = find_table_lock(net, पंचांगp.name, &ret, &ebt_mutex);
	अगर (!t)
		वापस ret;

	चयन (cmd) अणु
	हाल EBT_SO_GET_INFO:
	हाल EBT_SO_GET_INIT_INFO:
		अगर (*len != माप(काष्ठा ebt_replace)) अणु
			ret = -EINVAL;
			mutex_unlock(&ebt_mutex);
			अवरोध;
		पूर्ण
		अगर (cmd == EBT_SO_GET_INFO) अणु
			पंचांगp.nentries = t->निजी->nentries;
			पंचांगp.entries_size = t->निजी->entries_size;
			पंचांगp.valid_hooks = t->valid_hooks;
		पूर्ण अन्यथा अणु
			पंचांगp.nentries = t->table->nentries;
			पंचांगp.entries_size = t->table->entries_size;
			पंचांगp.valid_hooks = t->table->valid_hooks;
		पूर्ण
		mutex_unlock(&ebt_mutex);
		अगर (copy_to_user(user, &पंचांगp, *len) != 0) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ret = 0;
		अवरोध;

	हाल EBT_SO_GET_ENTRIES:
	हाल EBT_SO_GET_INIT_ENTRIES:
		ret = copy_everything_to_user(t, user, len, cmd);
		mutex_unlock(&ebt_mutex);
		अवरोध;

	शेष:
		mutex_unlock(&ebt_mutex);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक करो_ebt_set_ctl(काष्ठा sock *sk, पूर्णांक cmd, sockptr_t arg,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा net *net = sock_net(sk);
	पूर्णांक ret;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल EBT_SO_SET_ENTRIES:
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		अगर (in_compat_syscall())
			ret = compat_करो_replace(net, arg, len);
		अन्यथा
#पूर्ण_अगर
			ret = करो_replace(net, arg, len);
		अवरोध;
	हाल EBT_SO_SET_COUNTERS:
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		अगर (in_compat_syscall())
			ret = compat_update_counters(net, arg, len);
		अन्यथा
#पूर्ण_अगर
			ret = update_counters(net, arg, len);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा nf_sockopt_ops ebt_sockopts = अणु
	.pf		= PF_INET,
	.set_opपंचांगin	= EBT_BASE_CTL,
	.set_opपंचांगax	= EBT_SO_SET_MAX + 1,
	.set		= करो_ebt_set_ctl,
	.get_opपंचांगin	= EBT_BASE_CTL,
	.get_opपंचांगax	= EBT_SO_GET_MAX + 1,
	.get		= करो_ebt_get_ctl,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init ebt_pernet_init(काष्ठा net *net)
अणु
	काष्ठा ebt_pernet *ebt_net = net_generic(net, ebt_pernet_id);

	INIT_LIST_HEAD(&ebt_net->tables);
	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations ebt_net_ops = अणु
	.init = ebt_pernet_init,
	.id   = &ebt_pernet_id,
	.size = माप(काष्ठा ebt_pernet),
पूर्ण;

अटल पूर्णांक __init ebtables_init(व्योम)
अणु
	पूर्णांक ret;

	ret = xt_रेजिस्टर_target(&ebt_standard_target);
	अगर (ret < 0)
		वापस ret;
	ret = nf_रेजिस्टर_sockopt(&ebt_sockopts);
	अगर (ret < 0) अणु
		xt_unरेजिस्टर_target(&ebt_standard_target);
		वापस ret;
	पूर्ण

	ret = रेजिस्टर_pernet_subsys(&ebt_net_ops);
	अगर (ret < 0) अणु
		nf_unरेजिस्टर_sockopt(&ebt_sockopts);
		xt_unरेजिस्टर_target(&ebt_standard_target);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ebtables_fini(व्योम)
अणु
	nf_unरेजिस्टर_sockopt(&ebt_sockopts);
	xt_unरेजिस्टर_target(&ebt_standard_target);
	unरेजिस्टर_pernet_subsys(&ebt_net_ops);
पूर्ण

EXPORT_SYMBOL(ebt_रेजिस्टर_table);
EXPORT_SYMBOL(ebt_unरेजिस्टर_table);
EXPORT_SYMBOL(ebt_करो_table);
module_init(ebtables_init);
module_निकास(ebtables_fini);
MODULE_LICENSE("GPL");
