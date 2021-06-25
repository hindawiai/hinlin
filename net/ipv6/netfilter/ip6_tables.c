<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Packet matching code.
 *
 * Copyright (C) 1999 Paul `Rusty' Russell & Michael J. Neuling
 * Copyright (C) 2000-2005 Netfilter Core Team <coreteam@netfilter.org>
 * Copyright (c) 2006-2010 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/capability.h>
#समावेश <linux/in.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/kmod.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/poison.h>
#समावेश <linux/icmpv6.h>
#समावेश <net/ipv6.h>
#समावेश <net/compat.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mutex.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/err.h>
#समावेश <linux/cpumask.h>

#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश "../../netfilter/xt_repldata.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("IPv6 packet filter");
MODULE_ALIAS("ip6t_icmp6");

व्योम *ip6t_alloc_initial_table(स्थिर काष्ठा xt_table *info)
अणु
	वापस xt_alloc_initial_table(ip6t, IP6T);
पूर्ण
EXPORT_SYMBOL_GPL(ip6t_alloc_initial_table);

/* Returns whether matches rule or not. */
/* Perक्रमmance critical - called क्रम every packet */
अटल अंतरभूत bool
ip6_packet_match(स्थिर काष्ठा sk_buff *skb,
		 स्थिर अक्षर *indev,
		 स्थिर अक्षर *outdev,
		 स्थिर काष्ठा ip6t_ip6 *ip6info,
		 अचिन्हित पूर्णांक *protoff,
		 पूर्णांक *fragoff, bool *hotdrop)
अणु
	अचिन्हित दीर्घ ret;
	स्थिर काष्ठा ipv6hdr *ipv6 = ipv6_hdr(skb);

	अगर (NF_INVF(ip6info, IP6T_INV_SRCIP,
		    ipv6_masked_addr_cmp(&ipv6->saddr, &ip6info->smsk,
					 &ip6info->src)) ||
	    NF_INVF(ip6info, IP6T_INV_DSTIP,
		    ipv6_masked_addr_cmp(&ipv6->daddr, &ip6info->dmsk,
					 &ip6info->dst)))
		वापस false;

	ret = अगरname_compare_aligned(indev, ip6info->inअगरace, ip6info->inअगरace_mask);

	अगर (NF_INVF(ip6info, IP6T_INV_VIA_IN, ret != 0))
		वापस false;

	ret = अगरname_compare_aligned(outdev, ip6info->outअगरace, ip6info->outअगरace_mask);

	अगर (NF_INVF(ip6info, IP6T_INV_VIA_OUT, ret != 0))
		वापस false;

/* ... might want to करो something with class and flowlabel here ... */

	/* look क्रम the desired protocol header */
	अगर (ip6info->flags & IP6T_F_PROTO) अणु
		पूर्णांक protohdr;
		अचिन्हित लघु _frag_off;

		protohdr = ipv6_find_hdr(skb, protoff, -1, &_frag_off, शून्य);
		अगर (protohdr < 0) अणु
			अगर (_frag_off == 0)
				*hotdrop = true;
			वापस false;
		पूर्ण
		*fragoff = _frag_off;

		अगर (ip6info->proto == protohdr) अणु
			अगर (ip6info->invflags & IP6T_INV_PROTO)
				वापस false;

			वापस true;
		पूर्ण

		/* We need match क्रम the '-p all', too! */
		अगर ((ip6info->proto != 0) &&
			!(ip6info->invflags & IP6T_INV_PROTO))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* should be ip6 safe */
अटल bool
ip6_checkentry(स्थिर काष्ठा ip6t_ip6 *ipv6)
अणु
	अगर (ipv6->flags & ~IP6T_F_MASK)
		वापस false;
	अगर (ipv6->invflags & ~IP6T_INV_MASK)
		वापस false;

	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक
ip6t_error(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	net_info_ratelimited("error: `%s'\n", (स्थिर अक्षर *)par->targinfo);

	वापस NF_DROP;
पूर्ण

अटल अंतरभूत काष्ठा ip6t_entry *
get_entry(स्थिर व्योम *base, अचिन्हित पूर्णांक offset)
अणु
	वापस (काष्ठा ip6t_entry *)(base + offset);
पूर्ण

/* All zeroes == unconditional rule. */
/* Mildly perf critical (only अगर packet tracing is on) */
अटल अंतरभूत bool unconditional(स्थिर काष्ठा ip6t_entry *e)
अणु
	अटल स्थिर काष्ठा ip6t_ip6 uncond;

	वापस e->target_offset == माप(काष्ठा ip6t_entry) &&
	       स_भेद(&e->ipv6, &uncond, माप(uncond)) == 0;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा xt_entry_target *
ip6t_get_target_c(स्थिर काष्ठा ip6t_entry *e)
अणु
	वापस ip6t_get_target((काष्ठा ip6t_entry *)e);
पूर्ण

#अगर IS_ENABLED(CONFIG_NETFILTER_XT_TARGET_TRACE)
/* This cries क्रम unअगरication! */
अटल स्थिर अक्षर *स्थिर hooknames[] = अणु
	[NF_INET_PRE_ROUTING]		= "PREROUTING",
	[NF_INET_LOCAL_IN]		= "INPUT",
	[NF_INET_FORWARD]		= "FORWARD",
	[NF_INET_LOCAL_OUT]		= "OUTPUT",
	[NF_INET_POST_ROUTING]		= "POSTROUTING",
पूर्ण;

क्रमागत nf_ip_trace_comments अणु
	NF_IP6_TRACE_COMMENT_RULE,
	NF_IP6_TRACE_COMMENT_RETURN,
	NF_IP6_TRACE_COMMENT_POLICY,
पूर्ण;

अटल स्थिर अक्षर *स्थिर comments[] = अणु
	[NF_IP6_TRACE_COMMENT_RULE]	= "rule",
	[NF_IP6_TRACE_COMMENT_RETURN]	= "return",
	[NF_IP6_TRACE_COMMENT_POLICY]	= "policy",
पूर्ण;

अटल स्थिर काष्ठा nf_loginfo trace_loginfo = अणु
	.type = NF_LOG_TYPE_LOG,
	.u = अणु
		.log = अणु
			.level = LOGLEVEL_WARNING,
			.logflags = NF_LOG_DEFAULT_MASK,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* Mildly perf critical (only अगर packet tracing is on) */
अटल अंतरभूत पूर्णांक
get_chainname_rulक्रमागत(स्थिर काष्ठा ip6t_entry *s, स्थिर काष्ठा ip6t_entry *e,
		      स्थिर अक्षर *hookname, स्थिर अक्षर **chainname,
		      स्थिर अक्षर **comment, अचिन्हित पूर्णांक *rulक्रमागत)
अणु
	स्थिर काष्ठा xt_standard_target *t = (व्योम *)ip6t_get_target_c(s);

	अगर (म_भेद(t->target.u.kernel.target->name, XT_ERROR_TARGET) == 0) अणु
		/* Head of user chain: ERROR target with chainname */
		*chainname = t->target.data;
		(*rulक्रमागत) = 0;
	पूर्ण अन्यथा अगर (s == e) अणु
		(*rulक्रमागत)++;

		अगर (unconditional(s) &&
		    म_भेद(t->target.u.kernel.target->name,
			   XT_STANDARD_TARGET) == 0 &&
		    t->verdict < 0) अणु
			/* Tail of chains: STANDARD target (वापस/policy) */
			*comment = *chainname == hookname
				? comments[NF_IP6_TRACE_COMMENT_POLICY]
				: comments[NF_IP6_TRACE_COMMENT_RETURN];
		पूर्ण
		वापस 1;
	पूर्ण अन्यथा
		(*rulक्रमागत)++;

	वापस 0;
पूर्ण

अटल व्योम trace_packet(काष्ठा net *net,
			 स्थिर काष्ठा sk_buff *skb,
			 अचिन्हित पूर्णांक hook,
			 स्थिर काष्ठा net_device *in,
			 स्थिर काष्ठा net_device *out,
			 स्थिर अक्षर *tablename,
			 स्थिर काष्ठा xt_table_info *निजी,
			 स्थिर काष्ठा ip6t_entry *e)
अणु
	स्थिर काष्ठा ip6t_entry *root;
	स्थिर अक्षर *hookname, *chainname, *comment;
	स्थिर काष्ठा ip6t_entry *iter;
	अचिन्हित पूर्णांक rulक्रमागत = 0;

	root = get_entry(निजी->entries, निजी->hook_entry[hook]);

	hookname = chainname = hooknames[hook];
	comment = comments[NF_IP6_TRACE_COMMENT_RULE];

	xt_entry_क्रमeach(iter, root, निजी->size - निजी->hook_entry[hook])
		अगर (get_chainname_rulक्रमागत(iter, e, hookname,
		    &chainname, &comment, &rulक्रमागत) != 0)
			अवरोध;

	nf_log_trace(net, AF_INET6, hook, skb, in, out, &trace_loginfo,
		     "TRACE: %s:%s:%s:%u ",
		     tablename, chainname, comment, rulक्रमागत);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा ip6t_entry *
ip6t_next_entry(स्थिर काष्ठा ip6t_entry *entry)
अणु
	वापस (व्योम *)entry + entry->next_offset;
पूर्ण

/* Returns one of the generic firewall policies, like NF_ACCEPT. */
अचिन्हित पूर्णांक
ip6t_करो_table(काष्ठा sk_buff *skb,
	      स्थिर काष्ठा nf_hook_state *state,
	      काष्ठा xt_table *table)
अणु
	अचिन्हित पूर्णांक hook = state->hook;
	अटल स्थिर अक्षर nulldevname[IFNAMSIZ] __attribute__((aligned(माप(दीर्घ))));
	/* Initializing verdict to NF_DROP keeps gcc happy. */
	अचिन्हित पूर्णांक verdict = NF_DROP;
	स्थिर अक्षर *indev, *outdev;
	स्थिर व्योम *table_base;
	काष्ठा ip6t_entry *e, **jumpstack;
	अचिन्हित पूर्णांक stackidx, cpu;
	स्थिर काष्ठा xt_table_info *निजी;
	काष्ठा xt_action_param acpar;
	अचिन्हित पूर्णांक addend;

	/* Initialization */
	stackidx = 0;
	indev = state->in ? state->in->name : nulldevname;
	outdev = state->out ? state->out->name : nulldevname;
	/* We handle fragments by dealing with the first fragment as
	 * अगर it was a normal packet.  All other fragments are treated
	 * normally, except that they will NEVER match rules that ask
	 * things we करोn't know, ie. tcp syn flag or ports).  If the
	 * rule is also a fragment-specअगरic rule, non-fragments won't
	 * match it. */
	acpar.hotdrop = false;
	acpar.state   = state;

	WARN_ON(!(table->valid_hooks & (1 << hook)));

	local_bh_disable();
	addend = xt_ग_लिखो_recseq_begin();
	निजी = READ_ONCE(table->निजी); /* Address dependency. */
	cpu        = smp_processor_id();
	table_base = निजी->entries;
	jumpstack  = (काष्ठा ip6t_entry **)निजी->jumpstack[cpu];

	/* Switch to alternate jumpstack अगर we're being invoked via TEE.
	 * TEE issues XT_CONTINUE verdict on original skb so we must not
	 * clobber the jumpstack.
	 *
	 * For recursion via REJECT or SYNPROXY the stack will be clobbered
	 * but it is no problem since असलolute verdict is issued by these.
	 */
	अगर (अटल_key_false(&xt_tee_enabled))
		jumpstack += निजी->stacksize * __this_cpu_पढ़ो(nf_skb_duplicated);

	e = get_entry(table_base, निजी->hook_entry[hook]);

	करो अणु
		स्थिर काष्ठा xt_entry_target *t;
		स्थिर काष्ठा xt_entry_match *ematch;
		काष्ठा xt_counters *counter;

		WARN_ON(!e);
		acpar.thoff = 0;
		अगर (!ip6_packet_match(skb, indev, outdev, &e->ipv6,
		    &acpar.thoff, &acpar.fragoff, &acpar.hotdrop)) अणु
 no_match:
			e = ip6t_next_entry(e);
			जारी;
		पूर्ण

		xt_ematch_क्रमeach(ematch, e) अणु
			acpar.match     = ematch->u.kernel.match;
			acpar.matchinfo = ematch->data;
			अगर (!acpar.match->match(skb, &acpar))
				जाओ no_match;
		पूर्ण

		counter = xt_get_this_cpu_counter(&e->counters);
		ADD_COUNTER(*counter, skb->len, 1);

		t = ip6t_get_target_c(e);
		WARN_ON(!t->u.kernel.target);

#अगर IS_ENABLED(CONFIG_NETFILTER_XT_TARGET_TRACE)
		/* The packet is traced: log it */
		अगर (unlikely(skb->nf_trace))
			trace_packet(state->net, skb, hook, state->in,
				     state->out, table->name, निजी, e);
#पूर्ण_अगर
		/* Standard target? */
		अगर (!t->u.kernel.target->target) अणु
			पूर्णांक v;

			v = ((काष्ठा xt_standard_target *)t)->verdict;
			अगर (v < 0) अणु
				/* Pop from stack? */
				अगर (v != XT_RETURN) अणु
					verdict = (अचिन्हित पूर्णांक)(-v) - 1;
					अवरोध;
				पूर्ण
				अगर (stackidx == 0)
					e = get_entry(table_base,
					    निजी->underflow[hook]);
				अन्यथा
					e = ip6t_next_entry(jumpstack[--stackidx]);
				जारी;
			पूर्ण
			अगर (table_base + v != ip6t_next_entry(e) &&
			    !(e->ipv6.flags & IP6T_F_GOTO)) अणु
				अगर (unlikely(stackidx >= निजी->stacksize)) अणु
					verdict = NF_DROP;
					अवरोध;
				पूर्ण
				jumpstack[stackidx++] = e;
			पूर्ण

			e = get_entry(table_base, v);
			जारी;
		पूर्ण

		acpar.target   = t->u.kernel.target;
		acpar.targinfo = t->data;

		verdict = t->u.kernel.target->target(skb, &acpar);
		अगर (verdict == XT_CONTINUE)
			e = ip6t_next_entry(e);
		अन्यथा
			/* Verdict */
			अवरोध;
	पूर्ण जबतक (!acpar.hotdrop);

	xt_ग_लिखो_recseq_end(addend);
	local_bh_enable();

	अगर (acpar.hotdrop)
		वापस NF_DROP;
	अन्यथा वापस verdict;
पूर्ण

/* Figures out from what hook each rule can be called: वापसs 0 अगर
   there are loops.  Puts hook biपंचांगask in comefrom. */
अटल पूर्णांक
mark_source_chains(स्थिर काष्ठा xt_table_info *newinfo,
		   अचिन्हित पूर्णांक valid_hooks, व्योम *entry0,
		   अचिन्हित पूर्णांक *offsets)
अणु
	अचिन्हित पूर्णांक hook;

	/* No recursion; use packet counter to save back ptrs (reset
	   to 0 as we leave), and comefrom to save source hook biपंचांगask */
	क्रम (hook = 0; hook < NF_INET_NUMHOOKS; hook++) अणु
		अचिन्हित पूर्णांक pos = newinfo->hook_entry[hook];
		काष्ठा ip6t_entry *e = entry0 + pos;

		अगर (!(valid_hooks & (1 << hook)))
			जारी;

		/* Set initial back poपूर्णांकer. */
		e->counters.pcnt = pos;

		क्रम (;;) अणु
			स्थिर काष्ठा xt_standard_target *t
				= (व्योम *)ip6t_get_target_c(e);
			पूर्णांक visited = e->comefrom & (1 << hook);

			अगर (e->comefrom & (1 << NF_INET_NUMHOOKS))
				वापस 0;

			e->comefrom |= ((1 << hook) | (1 << NF_INET_NUMHOOKS));

			/* Unconditional वापस/END. */
			अगर ((unconditional(e) &&
			     (म_भेद(t->target.u.user.name,
				     XT_STANDARD_TARGET) == 0) &&
			     t->verdict < 0) || visited) अणु
				अचिन्हित पूर्णांक oldpos, size;

				/* Return: backtrack through the last
				   big jump. */
				करो अणु
					e->comefrom ^= (1<<NF_INET_NUMHOOKS);
					oldpos = pos;
					pos = e->counters.pcnt;
					e->counters.pcnt = 0;

					/* We're at the start. */
					अगर (pos == oldpos)
						जाओ next;

					e = entry0 + pos;
				पूर्ण जबतक (oldpos == pos + e->next_offset);

				/* Move aदीर्घ one */
				size = e->next_offset;
				e = entry0 + pos + size;
				अगर (pos + size >= newinfo->size)
					वापस 0;
				e->counters.pcnt = pos;
				pos += size;
			पूर्ण अन्यथा अणु
				पूर्णांक newpos = t->verdict;

				अगर (म_भेद(t->target.u.user.name,
					   XT_STANDARD_TARGET) == 0 &&
				    newpos >= 0) अणु
					/* This a jump; chase it. */
					अगर (!xt_find_jump_offset(offsets, newpos,
								 newinfo->number))
						वापस 0;
				पूर्ण अन्यथा अणु
					/* ... this is a fallthru */
					newpos = pos + e->next_offset;
					अगर (newpos >= newinfo->size)
						वापस 0;
				पूर्ण
				e = entry0 + newpos;
				e->counters.pcnt = pos;
				pos = newpos;
			पूर्ण
		पूर्ण
next:		;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम cleanup_match(काष्ठा xt_entry_match *m, काष्ठा net *net)
अणु
	काष्ठा xt_mtdtor_param par;

	par.net       = net;
	par.match     = m->u.kernel.match;
	par.matchinfo = m->data;
	par.family    = NFPROTO_IPV6;
	अगर (par.match->destroy != शून्य)
		par.match->destroy(&par);
	module_put(par.match->me);
पूर्ण

अटल पूर्णांक check_match(काष्ठा xt_entry_match *m, काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_ip6 *ipv6 = par->entryinfo;

	par->match     = m->u.kernel.match;
	par->matchinfo = m->data;

	वापस xt_check_match(par, m->u.match_size - माप(*m),
			      ipv6->proto, ipv6->invflags & IP6T_INV_PROTO);
पूर्ण

अटल पूर्णांक
find_check_match(काष्ठा xt_entry_match *m, काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_match *match;
	पूर्णांक ret;

	match = xt_request_find_match(NFPROTO_IPV6, m->u.user.name,
				      m->u.user.revision);
	अगर (IS_ERR(match))
		वापस PTR_ERR(match);

	m->u.kernel.match = match;

	ret = check_match(m, par);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	module_put(m->u.kernel.match->me);
	वापस ret;
पूर्ण

अटल पूर्णांक check_target(काष्ठा ip6t_entry *e, काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा xt_entry_target *t = ip6t_get_target(e);
	काष्ठा xt_tgchk_param par = अणु
		.net       = net,
		.table     = name,
		.entryinfo = e,
		.target    = t->u.kernel.target,
		.targinfo  = t->data,
		.hook_mask = e->comefrom,
		.family    = NFPROTO_IPV6,
	पूर्ण;

	वापस xt_check_target(&par, t->u.target_size - माप(*t),
			       e->ipv6.proto,
			       e->ipv6.invflags & IP6T_INV_PROTO);
पूर्ण

अटल पूर्णांक
find_check_entry(काष्ठा ip6t_entry *e, काष्ठा net *net, स्थिर अक्षर *name,
		 अचिन्हित पूर्णांक size,
		 काष्ठा xt_percpu_counter_alloc_state *alloc_state)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा xt_target *target;
	पूर्णांक ret;
	अचिन्हित पूर्णांक j;
	काष्ठा xt_mtchk_param mtpar;
	काष्ठा xt_entry_match *ematch;

	अगर (!xt_percpu_counter_alloc(alloc_state, &e->counters))
		वापस -ENOMEM;

	j = 0;
	स_रखो(&mtpar, 0, माप(mtpar));
	mtpar.net	= net;
	mtpar.table     = name;
	mtpar.entryinfo = &e->ipv6;
	mtpar.hook_mask = e->comefrom;
	mtpar.family    = NFPROTO_IPV6;
	xt_ematch_क्रमeach(ematch, e) अणु
		ret = find_check_match(ematch, &mtpar);
		अगर (ret != 0)
			जाओ cleanup_matches;
		++j;
	पूर्ण

	t = ip6t_get_target(e);
	target = xt_request_find_target(NFPROTO_IPV6, t->u.user.name,
					t->u.user.revision);
	अगर (IS_ERR(target)) अणु
		ret = PTR_ERR(target);
		जाओ cleanup_matches;
	पूर्ण
	t->u.kernel.target = target;

	ret = check_target(e, net, name);
	अगर (ret)
		जाओ err;
	वापस 0;
 err:
	module_put(t->u.kernel.target->me);
 cleanup_matches:
	xt_ematch_क्रमeach(ematch, e) अणु
		अगर (j-- == 0)
			अवरोध;
		cleanup_match(ematch, net);
	पूर्ण

	xt_percpu_counter_मुक्त(&e->counters);

	वापस ret;
पूर्ण

अटल bool check_underflow(स्थिर काष्ठा ip6t_entry *e)
अणु
	स्थिर काष्ठा xt_entry_target *t;
	अचिन्हित पूर्णांक verdict;

	अगर (!unconditional(e))
		वापस false;
	t = ip6t_get_target_c(e);
	अगर (म_भेद(t->u.user.name, XT_STANDARD_TARGET) != 0)
		वापस false;
	verdict = ((काष्ठा xt_standard_target *)t)->verdict;
	verdict = -verdict - 1;
	वापस verdict == NF_DROP || verdict == NF_ACCEPT;
पूर्ण

अटल पूर्णांक
check_entry_size_and_hooks(काष्ठा ip6t_entry *e,
			   काष्ठा xt_table_info *newinfo,
			   स्थिर अचिन्हित अक्षर *base,
			   स्थिर अचिन्हित अक्षर *limit,
			   स्थिर अचिन्हित पूर्णांक *hook_entries,
			   स्थिर अचिन्हित पूर्णांक *underflows,
			   अचिन्हित पूर्णांक valid_hooks)
अणु
	अचिन्हित पूर्णांक h;
	पूर्णांक err;

	अगर ((अचिन्हित दीर्घ)e % __alignof__(काष्ठा ip6t_entry) != 0 ||
	    (अचिन्हित अक्षर *)e + माप(काष्ठा ip6t_entry) >= limit ||
	    (अचिन्हित अक्षर *)e + e->next_offset > limit)
		वापस -EINVAL;

	अगर (e->next_offset
	    < माप(काष्ठा ip6t_entry) + माप(काष्ठा xt_entry_target))
		वापस -EINVAL;

	अगर (!ip6_checkentry(&e->ipv6))
		वापस -EINVAL;

	err = xt_check_entry_offsets(e, e->elems, e->target_offset,
				     e->next_offset);
	अगर (err)
		वापस err;

	/* Check hooks & underflows */
	क्रम (h = 0; h < NF_INET_NUMHOOKS; h++) अणु
		अगर (!(valid_hooks & (1 << h)))
			जारी;
		अगर ((अचिन्हित अक्षर *)e - base == hook_entries[h])
			newinfo->hook_entry[h] = hook_entries[h];
		अगर ((अचिन्हित अक्षर *)e - base == underflows[h]) अणु
			अगर (!check_underflow(e))
				वापस -EINVAL;

			newinfo->underflow[h] = underflows[h];
		पूर्ण
	पूर्ण

	/* Clear counters and comefrom */
	e->counters = ((काष्ठा xt_counters) अणु 0, 0 पूर्ण);
	e->comefrom = 0;
	वापस 0;
पूर्ण

अटल व्योम cleanup_entry(काष्ठा ip6t_entry *e, काष्ठा net *net)
अणु
	काष्ठा xt_tgdtor_param par;
	काष्ठा xt_entry_target *t;
	काष्ठा xt_entry_match *ematch;

	/* Cleanup all matches */
	xt_ematch_क्रमeach(ematch, e)
		cleanup_match(ematch, net);
	t = ip6t_get_target(e);

	par.net      = net;
	par.target   = t->u.kernel.target;
	par.targinfo = t->data;
	par.family   = NFPROTO_IPV6;
	अगर (par.target->destroy != शून्य)
		par.target->destroy(&par);
	module_put(par.target->me);
	xt_percpu_counter_मुक्त(&e->counters);
पूर्ण

/* Checks and translates the user-supplied table segment (held in
   newinfo) */
अटल पूर्णांक
translate_table(काष्ठा net *net, काष्ठा xt_table_info *newinfo, व्योम *entry0,
		स्थिर काष्ठा ip6t_replace *repl)
अणु
	काष्ठा xt_percpu_counter_alloc_state alloc_state = अणु 0 पूर्ण;
	काष्ठा ip6t_entry *iter;
	अचिन्हित पूर्णांक *offsets;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	newinfo->size = repl->size;
	newinfo->number = repl->num_entries;

	/* Init all hooks to impossible value. */
	क्रम (i = 0; i < NF_INET_NUMHOOKS; i++) अणु
		newinfo->hook_entry[i] = 0xFFFFFFFF;
		newinfo->underflow[i] = 0xFFFFFFFF;
	पूर्ण

	offsets = xt_alloc_entry_offsets(newinfo->number);
	अगर (!offsets)
		वापस -ENOMEM;
	i = 0;
	/* Walk through entries, checking offsets. */
	xt_entry_क्रमeach(iter, entry0, newinfo->size) अणु
		ret = check_entry_size_and_hooks(iter, newinfo, entry0,
						 entry0 + repl->size,
						 repl->hook_entry,
						 repl->underflow,
						 repl->valid_hooks);
		अगर (ret != 0)
			जाओ out_मुक्त;
		अगर (i < repl->num_entries)
			offsets[i] = (व्योम *)iter - entry0;
		++i;
		अगर (म_भेद(ip6t_get_target(iter)->u.user.name,
		    XT_ERROR_TARGET) == 0)
			++newinfo->stacksize;
	पूर्ण

	ret = -EINVAL;
	अगर (i != repl->num_entries)
		जाओ out_मुक्त;

	ret = xt_check_table_hooks(newinfo, repl->valid_hooks);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (!mark_source_chains(newinfo, repl->valid_hooks, entry0, offsets)) अणु
		ret = -ELOOP;
		जाओ out_मुक्त;
	पूर्ण
	kvमुक्त(offsets);

	/* Finally, each sanity check must pass */
	i = 0;
	xt_entry_क्रमeach(iter, entry0, newinfo->size) अणु
		ret = find_check_entry(iter, net, repl->name, repl->size,
				       &alloc_state);
		अगर (ret != 0)
			अवरोध;
		++i;
	पूर्ण

	अगर (ret != 0) अणु
		xt_entry_क्रमeach(iter, entry0, newinfo->size) अणु
			अगर (i-- == 0)
				अवरोध;
			cleanup_entry(iter, net);
		पूर्ण
		वापस ret;
	पूर्ण

	वापस ret;
 out_मुक्त:
	kvमुक्त(offsets);
	वापस ret;
पूर्ण

अटल व्योम
get_counters(स्थिर काष्ठा xt_table_info *t,
	     काष्ठा xt_counters counters[])
अणु
	काष्ठा ip6t_entry *iter;
	अचिन्हित पूर्णांक cpu;
	अचिन्हित पूर्णांक i;

	क्रम_each_possible_cpu(cpu) अणु
		seqcount_t *s = &per_cpu(xt_recseq, cpu);

		i = 0;
		xt_entry_क्रमeach(iter, t->entries, t->size) अणु
			काष्ठा xt_counters *पंचांगp;
			u64 bcnt, pcnt;
			अचिन्हित पूर्णांक start;

			पंचांगp = xt_get_per_cpu_counter(&iter->counters, cpu);
			करो अणु
				start = पढ़ो_seqcount_begin(s);
				bcnt = पंचांगp->bcnt;
				pcnt = पंचांगp->pcnt;
			पूर्ण जबतक (पढ़ो_seqcount_retry(s, start));

			ADD_COUNTER(counters[i], bcnt, pcnt);
			++i;
			cond_resched();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_old_counters(स्थिर काष्ठा xt_table_info *t,
			     काष्ठा xt_counters counters[])
अणु
	काष्ठा ip6t_entry *iter;
	अचिन्हित पूर्णांक cpu, i;

	क्रम_each_possible_cpu(cpu) अणु
		i = 0;
		xt_entry_क्रमeach(iter, t->entries, t->size) अणु
			स्थिर काष्ठा xt_counters *पंचांगp;

			पंचांगp = xt_get_per_cpu_counter(&iter->counters, cpu);
			ADD_COUNTER(counters[i], पंचांगp->bcnt, पंचांगp->pcnt);
			++i;
		पूर्ण
		cond_resched();
	पूर्ण
पूर्ण

अटल काष्ठा xt_counters *alloc_counters(स्थिर काष्ठा xt_table *table)
अणु
	अचिन्हित पूर्णांक countersize;
	काष्ठा xt_counters *counters;
	स्थिर काष्ठा xt_table_info *निजी = table->निजी;

	/* We need atomic snapshot of counters: rest करोesn't change
	   (other than comefrom, which userspace करोesn't care
	   about). */
	countersize = माप(काष्ठा xt_counters) * निजी->number;
	counters = vzalloc(countersize);

	अगर (counters == शून्य)
		वापस ERR_PTR(-ENOMEM);

	get_counters(निजी, counters);

	वापस counters;
पूर्ण

अटल पूर्णांक
copy_entries_to_user(अचिन्हित पूर्णांक total_size,
		     स्थिर काष्ठा xt_table *table,
		     व्योम __user *userptr)
अणु
	अचिन्हित पूर्णांक off, num;
	स्थिर काष्ठा ip6t_entry *e;
	काष्ठा xt_counters *counters;
	स्थिर काष्ठा xt_table_info *निजी = table->निजी;
	पूर्णांक ret = 0;
	स्थिर व्योम *loc_cpu_entry;

	counters = alloc_counters(table);
	अगर (IS_ERR(counters))
		वापस PTR_ERR(counters);

	loc_cpu_entry = निजी->entries;

	/* FIXME: use iterator macros --RR */
	/* ... then go back and fix counters and names */
	क्रम (off = 0, num = 0; off < total_size; off += e->next_offset, num++)अणु
		अचिन्हित पूर्णांक i;
		स्थिर काष्ठा xt_entry_match *m;
		स्थिर काष्ठा xt_entry_target *t;

		e = loc_cpu_entry + off;
		अगर (copy_to_user(userptr + off, e, माप(*e))) अणु
			ret = -EFAULT;
			जाओ मुक्त_counters;
		पूर्ण
		अगर (copy_to_user(userptr + off
				 + दुरत्व(काष्ठा ip6t_entry, counters),
				 &counters[num],
				 माप(counters[num])) != 0) अणु
			ret = -EFAULT;
			जाओ मुक्त_counters;
		पूर्ण

		क्रम (i = माप(काष्ठा ip6t_entry);
		     i < e->target_offset;
		     i += m->u.match_size) अणु
			m = (व्योम *)e + i;

			अगर (xt_match_to_user(m, userptr + off + i)) अणु
				ret = -EFAULT;
				जाओ मुक्त_counters;
			पूर्ण
		पूर्ण

		t = ip6t_get_target_c(e);
		अगर (xt_target_to_user(t, userptr + off + e->target_offset)) अणु
			ret = -EFAULT;
			जाओ मुक्त_counters;
		पूर्ण
	पूर्ण

 मुक्त_counters:
	vमुक्त(counters);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
अटल व्योम compat_standard_from_user(व्योम *dst, स्थिर व्योम *src)
अणु
	पूर्णांक v = *(compat_पूर्णांक_t *)src;

	अगर (v > 0)
		v += xt_compat_calc_jump(AF_INET6, v);
	स_नकल(dst, &v, माप(v));
पूर्ण

अटल पूर्णांक compat_standard_to_user(व्योम __user *dst, स्थिर व्योम *src)
अणु
	compat_पूर्णांक_t cv = *(पूर्णांक *)src;

	अगर (cv > 0)
		cv -= xt_compat_calc_jump(AF_INET6, cv);
	वापस copy_to_user(dst, &cv, माप(cv)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक compat_calc_entry(स्थिर काष्ठा ip6t_entry *e,
			     स्थिर काष्ठा xt_table_info *info,
			     स्थिर व्योम *base, काष्ठा xt_table_info *newinfo)
अणु
	स्थिर काष्ठा xt_entry_match *ematch;
	स्थिर काष्ठा xt_entry_target *t;
	अचिन्हित पूर्णांक entry_offset;
	पूर्णांक off, i, ret;

	off = माप(काष्ठा ip6t_entry) - माप(काष्ठा compat_ip6t_entry);
	entry_offset = (व्योम *)e - base;
	xt_ematch_क्रमeach(ematch, e)
		off += xt_compat_match_offset(ematch->u.kernel.match);
	t = ip6t_get_target_c(e);
	off += xt_compat_target_offset(t->u.kernel.target);
	newinfo->size -= off;
	ret = xt_compat_add_offset(AF_INET6, entry_offset, off);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < NF_INET_NUMHOOKS; i++) अणु
		अगर (info->hook_entry[i] &&
		    (e < (काष्ठा ip6t_entry *)(base + info->hook_entry[i])))
			newinfo->hook_entry[i] -= off;
		अगर (info->underflow[i] &&
		    (e < (काष्ठा ip6t_entry *)(base + info->underflow[i])))
			newinfo->underflow[i] -= off;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compat_table_info(स्थिर काष्ठा xt_table_info *info,
			     काष्ठा xt_table_info *newinfo)
अणु
	काष्ठा ip6t_entry *iter;
	स्थिर व्योम *loc_cpu_entry;
	पूर्णांक ret;

	अगर (!newinfo || !info)
		वापस -EINVAL;

	/* we करोnt care about newinfo->entries */
	स_नकल(newinfo, info, दुरत्व(काष्ठा xt_table_info, entries));
	newinfo->initial_entries = 0;
	loc_cpu_entry = info->entries;
	ret = xt_compat_init_offsets(AF_INET6, info->number);
	अगर (ret)
		वापस ret;
	xt_entry_क्रमeach(iter, loc_cpu_entry, info->size) अणु
		ret = compat_calc_entry(iter, info, loc_cpu_entry, newinfo);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक get_info(काष्ठा net *net, व्योम __user *user, स्थिर पूर्णांक *len)
अणु
	अक्षर name[XT_TABLE_MAXNAMELEN];
	काष्ठा xt_table *t;
	पूर्णांक ret;

	अगर (*len != माप(काष्ठा ip6t_getinfo))
		वापस -EINVAL;

	अगर (copy_from_user(name, user, माप(name)) != 0)
		वापस -EFAULT;

	name[XT_TABLE_MAXNAMELEN-1] = '\0';
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	अगर (in_compat_syscall())
		xt_compat_lock(AF_INET6);
#पूर्ण_अगर
	t = xt_request_find_table_lock(net, AF_INET6, name);
	अगर (!IS_ERR(t)) अणु
		काष्ठा ip6t_getinfo info;
		स्थिर काष्ठा xt_table_info *निजी = t->निजी;
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		काष्ठा xt_table_info पंचांगp;

		अगर (in_compat_syscall()) अणु
			ret = compat_table_info(निजी, &पंचांगp);
			xt_compat_flush_offsets(AF_INET6);
			निजी = &पंचांगp;
		पूर्ण
#पूर्ण_अगर
		स_रखो(&info, 0, माप(info));
		info.valid_hooks = t->valid_hooks;
		स_नकल(info.hook_entry, निजी->hook_entry,
		       माप(info.hook_entry));
		स_नकल(info.underflow, निजी->underflow,
		       माप(info.underflow));
		info.num_entries = निजी->number;
		info.size = निजी->size;
		म_नकल(info.name, name);

		अगर (copy_to_user(user, &info, *len) != 0)
			ret = -EFAULT;
		अन्यथा
			ret = 0;

		xt_table_unlock(t);
		module_put(t->me);
	पूर्ण अन्यथा
		ret = PTR_ERR(t);
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	अगर (in_compat_syscall())
		xt_compat_unlock(AF_INET6);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक
get_entries(काष्ठा net *net, काष्ठा ip6t_get_entries __user *uptr,
	    स्थिर पूर्णांक *len)
अणु
	पूर्णांक ret;
	काष्ठा ip6t_get_entries get;
	काष्ठा xt_table *t;

	अगर (*len < माप(get))
		वापस -EINVAL;
	अगर (copy_from_user(&get, uptr, माप(get)) != 0)
		वापस -EFAULT;
	अगर (*len != माप(काष्ठा ip6t_get_entries) + get.size)
		वापस -EINVAL;

	get.name[माप(get.name) - 1] = '\0';

	t = xt_find_table_lock(net, AF_INET6, get.name);
	अगर (!IS_ERR(t)) अणु
		काष्ठा xt_table_info *निजी = t->निजी;
		अगर (get.size == निजी->size)
			ret = copy_entries_to_user(निजी->size,
						   t, uptr->entrytable);
		अन्यथा
			ret = -EAGAIN;

		module_put(t->me);
		xt_table_unlock(t);
	पूर्ण अन्यथा
		ret = PTR_ERR(t);

	वापस ret;
पूर्ण

अटल पूर्णांक
__करो_replace(काष्ठा net *net, स्थिर अक्षर *name, अचिन्हित पूर्णांक valid_hooks,
	     काष्ठा xt_table_info *newinfo, अचिन्हित पूर्णांक num_counters,
	     व्योम __user *counters_ptr)
अणु
	पूर्णांक ret;
	काष्ठा xt_table *t;
	काष्ठा xt_table_info *oldinfo;
	काष्ठा xt_counters *counters;
	काष्ठा ip6t_entry *iter;

	ret = 0;
	counters = xt_counters_alloc(num_counters);
	अगर (!counters) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	t = xt_request_find_table_lock(net, AF_INET6, name);
	अगर (IS_ERR(t)) अणु
		ret = PTR_ERR(t);
		जाओ मुक्त_newinfo_counters_untrans;
	पूर्ण

	/* You lied! */
	अगर (valid_hooks != t->valid_hooks) अणु
		ret = -EINVAL;
		जाओ put_module;
	पूर्ण

	oldinfo = xt_replace_table(t, num_counters, newinfo, &ret);
	अगर (!oldinfo)
		जाओ put_module;

	/* Update module usage count based on number of rules */
	अगर ((oldinfo->number > oldinfo->initial_entries) ||
	    (newinfo->number <= oldinfo->initial_entries))
		module_put(t->me);
	अगर ((oldinfo->number > oldinfo->initial_entries) &&
	    (newinfo->number <= oldinfo->initial_entries))
		module_put(t->me);

	xt_table_unlock(t);

	get_old_counters(oldinfo, counters);

	/* Decrease module usage counts and मुक्त resource */
	xt_entry_क्रमeach(iter, oldinfo->entries, oldinfo->size)
		cleanup_entry(iter, net);

	xt_मुक्त_table_info(oldinfo);
	अगर (copy_to_user(counters_ptr, counters,
			 माप(काष्ठा xt_counters) * num_counters) != 0) अणु
		/* Silent error, can't fail, new table is alपढ़ोy in place */
		net_warn_ratelimited("ip6tables: counters copy to user failed while replacing table\n");
	पूर्ण
	vमुक्त(counters);
	वापस ret;

 put_module:
	module_put(t->me);
	xt_table_unlock(t);
 मुक्त_newinfo_counters_untrans:
	vमुक्त(counters);
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक
करो_replace(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा ip6t_replace पंचांगp;
	काष्ठा xt_table_info *newinfo;
	व्योम *loc_cpu_entry;
	काष्ठा ip6t_entry *iter;

	अगर (copy_from_sockptr(&पंचांगp, arg, माप(पंचांगp)) != 0)
		वापस -EFAULT;

	/* overflow check */
	अगर (पंचांगp.num_counters >= पूर्णांक_उच्च / माप(काष्ठा xt_counters))
		वापस -ENOMEM;
	अगर (पंचांगp.num_counters == 0)
		वापस -EINVAL;

	पंचांगp.name[माप(पंचांगp.name)-1] = 0;

	newinfo = xt_alloc_table_info(पंचांगp.size);
	अगर (!newinfo)
		वापस -ENOMEM;

	loc_cpu_entry = newinfo->entries;
	अगर (copy_from_sockptr_offset(loc_cpu_entry, arg, माप(पंचांगp),
			पंचांगp.size) != 0) अणु
		ret = -EFAULT;
		जाओ मुक्त_newinfo;
	पूर्ण

	ret = translate_table(net, newinfo, loc_cpu_entry, &पंचांगp);
	अगर (ret != 0)
		जाओ मुक्त_newinfo;

	ret = __करो_replace(net, पंचांगp.name, पंचांगp.valid_hooks, newinfo,
			   पंचांगp.num_counters, पंचांगp.counters);
	अगर (ret)
		जाओ मुक्त_newinfo_untrans;
	वापस 0;

 मुक्त_newinfo_untrans:
	xt_entry_क्रमeach(iter, loc_cpu_entry, newinfo->size)
		cleanup_entry(iter, net);
 मुक्त_newinfo:
	xt_मुक्त_table_info(newinfo);
	वापस ret;
पूर्ण

अटल पूर्णांक
करो_add_counters(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा xt_counters_info पंचांगp;
	काष्ठा xt_counters *paddc;
	काष्ठा xt_table *t;
	स्थिर काष्ठा xt_table_info *निजी;
	पूर्णांक ret = 0;
	काष्ठा ip6t_entry *iter;
	अचिन्हित पूर्णांक addend;

	paddc = xt_copy_counters(arg, len, &पंचांगp);
	अगर (IS_ERR(paddc))
		वापस PTR_ERR(paddc);
	t = xt_find_table_lock(net, AF_INET6, पंचांगp.name);
	अगर (IS_ERR(t)) अणु
		ret = PTR_ERR(t);
		जाओ मुक्त;
	पूर्ण

	local_bh_disable();
	निजी = t->निजी;
	अगर (निजी->number != पंचांगp.num_counters) अणु
		ret = -EINVAL;
		जाओ unlock_up_मुक्त;
	पूर्ण

	i = 0;
	addend = xt_ग_लिखो_recseq_begin();
	xt_entry_क्रमeach(iter, निजी->entries, निजी->size) अणु
		काष्ठा xt_counters *पंचांगp;

		पंचांगp = xt_get_this_cpu_counter(&iter->counters);
		ADD_COUNTER(*पंचांगp, paddc[i].bcnt, paddc[i].pcnt);
		++i;
	पूर्ण
	xt_ग_लिखो_recseq_end(addend);
 unlock_up_मुक्त:
	local_bh_enable();
	xt_table_unlock(t);
	module_put(t->me);
 मुक्त:
	vमुक्त(paddc);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
काष्ठा compat_ip6t_replace अणु
	अक्षर			name[XT_TABLE_MAXNAMELEN];
	u32			valid_hooks;
	u32			num_entries;
	u32			size;
	u32			hook_entry[NF_INET_NUMHOOKS];
	u32			underflow[NF_INET_NUMHOOKS];
	u32			num_counters;
	compat_uptr_t		counters;	/* काष्ठा xt_counters * */
	काष्ठा compat_ip6t_entry entries[];
पूर्ण;

अटल पूर्णांक
compat_copy_entry_to_user(काष्ठा ip6t_entry *e, व्योम __user **dstptr,
			  अचिन्हित पूर्णांक *size, काष्ठा xt_counters *counters,
			  अचिन्हित पूर्णांक i)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा compat_ip6t_entry __user *ce;
	u_पूर्णांक16_t target_offset, next_offset;
	compat_uपूर्णांक_t origsize;
	स्थिर काष्ठा xt_entry_match *ematch;
	पूर्णांक ret = 0;

	origsize = *size;
	ce = *dstptr;
	अगर (copy_to_user(ce, e, माप(काष्ठा ip6t_entry)) != 0 ||
	    copy_to_user(&ce->counters, &counters[i],
	    माप(counters[i])) != 0)
		वापस -EFAULT;

	*dstptr += माप(काष्ठा compat_ip6t_entry);
	*size -= माप(काष्ठा ip6t_entry) - माप(काष्ठा compat_ip6t_entry);

	xt_ematch_क्रमeach(ematch, e) अणु
		ret = xt_compat_match_to_user(ematch, dstptr, size);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	target_offset = e->target_offset - (origsize - *size);
	t = ip6t_get_target(e);
	ret = xt_compat_target_to_user(t, dstptr, size);
	अगर (ret)
		वापस ret;
	next_offset = e->next_offset - (origsize - *size);
	अगर (put_user(target_offset, &ce->target_offset) != 0 ||
	    put_user(next_offset, &ce->next_offset) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक
compat_find_calc_match(काष्ठा xt_entry_match *m,
		       स्थिर काष्ठा ip6t_ip6 *ipv6,
		       पूर्णांक *size)
अणु
	काष्ठा xt_match *match;

	match = xt_request_find_match(NFPROTO_IPV6, m->u.user.name,
				      m->u.user.revision);
	अगर (IS_ERR(match))
		वापस PTR_ERR(match);

	m->u.kernel.match = match;
	*size += xt_compat_match_offset(match);
	वापस 0;
पूर्ण

अटल व्योम compat_release_entry(काष्ठा compat_ip6t_entry *e)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा xt_entry_match *ematch;

	/* Cleanup all matches */
	xt_ematch_क्रमeach(ematch, e)
		module_put(ematch->u.kernel.match->me);
	t = compat_ip6t_get_target(e);
	module_put(t->u.kernel.target->me);
पूर्ण

अटल पूर्णांक
check_compat_entry_size_and_hooks(काष्ठा compat_ip6t_entry *e,
				  काष्ठा xt_table_info *newinfo,
				  अचिन्हित पूर्णांक *size,
				  स्थिर अचिन्हित अक्षर *base,
				  स्थिर अचिन्हित अक्षर *limit)
अणु
	काष्ठा xt_entry_match *ematch;
	काष्ठा xt_entry_target *t;
	काष्ठा xt_target *target;
	अचिन्हित पूर्णांक entry_offset;
	अचिन्हित पूर्णांक j;
	पूर्णांक ret, off;

	अगर ((अचिन्हित दीर्घ)e % __alignof__(काष्ठा compat_ip6t_entry) != 0 ||
	    (अचिन्हित अक्षर *)e + माप(काष्ठा compat_ip6t_entry) >= limit ||
	    (अचिन्हित अक्षर *)e + e->next_offset > limit)
		वापस -EINVAL;

	अगर (e->next_offset < माप(काष्ठा compat_ip6t_entry) +
			     माप(काष्ठा compat_xt_entry_target))
		वापस -EINVAL;

	अगर (!ip6_checkentry(&e->ipv6))
		वापस -EINVAL;

	ret = xt_compat_check_entry_offsets(e, e->elems,
					    e->target_offset, e->next_offset);
	अगर (ret)
		वापस ret;

	off = माप(काष्ठा ip6t_entry) - माप(काष्ठा compat_ip6t_entry);
	entry_offset = (व्योम *)e - (व्योम *)base;
	j = 0;
	xt_ematch_क्रमeach(ematch, e) अणु
		ret = compat_find_calc_match(ematch, &e->ipv6, &off);
		अगर (ret != 0)
			जाओ release_matches;
		++j;
	पूर्ण

	t = compat_ip6t_get_target(e);
	target = xt_request_find_target(NFPROTO_IPV6, t->u.user.name,
					t->u.user.revision);
	अगर (IS_ERR(target)) अणु
		ret = PTR_ERR(target);
		जाओ release_matches;
	पूर्ण
	t->u.kernel.target = target;

	off += xt_compat_target_offset(target);
	*size += off;
	ret = xt_compat_add_offset(AF_INET6, entry_offset, off);
	अगर (ret)
		जाओ out;

	वापस 0;

out:
	module_put(t->u.kernel.target->me);
release_matches:
	xt_ematch_क्रमeach(ematch, e) अणु
		अगर (j-- == 0)
			अवरोध;
		module_put(ematch->u.kernel.match->me);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
compat_copy_entry_from_user(काष्ठा compat_ip6t_entry *e, व्योम **dstptr,
			    अचिन्हित पूर्णांक *size,
			    काष्ठा xt_table_info *newinfo, अचिन्हित अक्षर *base)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा ip6t_entry *de;
	अचिन्हित पूर्णांक origsize;
	पूर्णांक h;
	काष्ठा xt_entry_match *ematch;

	origsize = *size;
	de = *dstptr;
	स_नकल(de, e, माप(काष्ठा ip6t_entry));
	स_नकल(&de->counters, &e->counters, माप(e->counters));

	*dstptr += माप(काष्ठा ip6t_entry);
	*size += माप(काष्ठा ip6t_entry) - माप(काष्ठा compat_ip6t_entry);

	xt_ematch_क्रमeach(ematch, e)
		xt_compat_match_from_user(ematch, dstptr, size);

	de->target_offset = e->target_offset - (origsize - *size);
	t = compat_ip6t_get_target(e);
	xt_compat_target_from_user(t, dstptr, size);

	de->next_offset = e->next_offset - (origsize - *size);
	क्रम (h = 0; h < NF_INET_NUMHOOKS; h++) अणु
		अगर ((अचिन्हित अक्षर *)de - base < newinfo->hook_entry[h])
			newinfo->hook_entry[h] -= origsize - *size;
		अगर ((अचिन्हित अक्षर *)de - base < newinfo->underflow[h])
			newinfo->underflow[h] -= origsize - *size;
	पूर्ण
पूर्ण

अटल पूर्णांक
translate_compat_table(काष्ठा net *net,
		       काष्ठा xt_table_info **pinfo,
		       व्योम **pentry0,
		       स्थिर काष्ठा compat_ip6t_replace *compatr)
अणु
	अचिन्हित पूर्णांक i, j;
	काष्ठा xt_table_info *newinfo, *info;
	व्योम *pos, *entry0, *entry1;
	काष्ठा compat_ip6t_entry *iter0;
	काष्ठा ip6t_replace repl;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	info = *pinfo;
	entry0 = *pentry0;
	size = compatr->size;
	info->number = compatr->num_entries;

	j = 0;
	xt_compat_lock(AF_INET6);
	ret = xt_compat_init_offsets(AF_INET6, compatr->num_entries);
	अगर (ret)
		जाओ out_unlock;
	/* Walk through entries, checking offsets. */
	xt_entry_क्रमeach(iter0, entry0, compatr->size) अणु
		ret = check_compat_entry_size_and_hooks(iter0, info, &size,
							entry0,
							entry0 + compatr->size);
		अगर (ret != 0)
			जाओ out_unlock;
		++j;
	पूर्ण

	ret = -EINVAL;
	अगर (j != compatr->num_entries)
		जाओ out_unlock;

	ret = -ENOMEM;
	newinfo = xt_alloc_table_info(size);
	अगर (!newinfo)
		जाओ out_unlock;

	स_रखो(newinfo->entries, 0, size);

	newinfo->number = compatr->num_entries;
	क्रम (i = 0; i < NF_INET_NUMHOOKS; i++) अणु
		newinfo->hook_entry[i] = compatr->hook_entry[i];
		newinfo->underflow[i] = compatr->underflow[i];
	पूर्ण
	entry1 = newinfo->entries;
	pos = entry1;
	size = compatr->size;
	xt_entry_क्रमeach(iter0, entry0, compatr->size)
		compat_copy_entry_from_user(iter0, &pos, &size,
					    newinfo, entry1);

	/* all module references in entry0 are now gone. */
	xt_compat_flush_offsets(AF_INET6);
	xt_compat_unlock(AF_INET6);

	स_नकल(&repl, compatr, माप(*compatr));

	क्रम (i = 0; i < NF_INET_NUMHOOKS; i++) अणु
		repl.hook_entry[i] = newinfo->hook_entry[i];
		repl.underflow[i] = newinfo->underflow[i];
	पूर्ण

	repl.num_counters = 0;
	repl.counters = शून्य;
	repl.size = newinfo->size;
	ret = translate_table(net, newinfo, entry1, &repl);
	अगर (ret)
		जाओ मुक्त_newinfo;

	*pinfo = newinfo;
	*pentry0 = entry1;
	xt_मुक्त_table_info(info);
	वापस 0;

मुक्त_newinfo:
	xt_मुक्त_table_info(newinfo);
	वापस ret;
out_unlock:
	xt_compat_flush_offsets(AF_INET6);
	xt_compat_unlock(AF_INET6);
	xt_entry_क्रमeach(iter0, entry0, compatr->size) अणु
		अगर (j-- == 0)
			अवरोध;
		compat_release_entry(iter0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
compat_करो_replace(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा compat_ip6t_replace पंचांगp;
	काष्ठा xt_table_info *newinfo;
	व्योम *loc_cpu_entry;
	काष्ठा ip6t_entry *iter;

	अगर (copy_from_sockptr(&पंचांगp, arg, माप(पंचांगp)) != 0)
		वापस -EFAULT;

	/* overflow check */
	अगर (पंचांगp.num_counters >= पूर्णांक_उच्च / माप(काष्ठा xt_counters))
		वापस -ENOMEM;
	अगर (पंचांगp.num_counters == 0)
		वापस -EINVAL;

	पंचांगp.name[माप(पंचांगp.name)-1] = 0;

	newinfo = xt_alloc_table_info(पंचांगp.size);
	अगर (!newinfo)
		वापस -ENOMEM;

	loc_cpu_entry = newinfo->entries;
	अगर (copy_from_sockptr_offset(loc_cpu_entry, arg, माप(पंचांगp),
			पंचांगp.size) != 0) अणु
		ret = -EFAULT;
		जाओ मुक्त_newinfo;
	पूर्ण

	ret = translate_compat_table(net, &newinfo, &loc_cpu_entry, &पंचांगp);
	अगर (ret != 0)
		जाओ मुक्त_newinfo;

	ret = __करो_replace(net, पंचांगp.name, पंचांगp.valid_hooks, newinfo,
			   पंचांगp.num_counters, compat_ptr(पंचांगp.counters));
	अगर (ret)
		जाओ मुक्त_newinfo_untrans;
	वापस 0;

 मुक्त_newinfo_untrans:
	xt_entry_क्रमeach(iter, loc_cpu_entry, newinfo->size)
		cleanup_entry(iter, net);
 मुक्त_newinfo:
	xt_मुक्त_table_info(newinfo);
	वापस ret;
पूर्ण

काष्ठा compat_ip6t_get_entries अणु
	अक्षर name[XT_TABLE_MAXNAMELEN];
	compat_uपूर्णांक_t size;
	काष्ठा compat_ip6t_entry entrytable[];
पूर्ण;

अटल पूर्णांक
compat_copy_entries_to_user(अचिन्हित पूर्णांक total_size, काष्ठा xt_table *table,
			    व्योम __user *userptr)
अणु
	काष्ठा xt_counters *counters;
	स्थिर काष्ठा xt_table_info *निजी = table->निजी;
	व्योम __user *pos;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा ip6t_entry *iter;

	counters = alloc_counters(table);
	अगर (IS_ERR(counters))
		वापस PTR_ERR(counters);

	pos = userptr;
	size = total_size;
	xt_entry_क्रमeach(iter, निजी->entries, total_size) अणु
		ret = compat_copy_entry_to_user(iter, &pos,
						&size, counters, i++);
		अगर (ret != 0)
			अवरोध;
	पूर्ण

	vमुक्त(counters);
	वापस ret;
पूर्ण

अटल पूर्णांक
compat_get_entries(काष्ठा net *net, काष्ठा compat_ip6t_get_entries __user *uptr,
		   पूर्णांक *len)
अणु
	पूर्णांक ret;
	काष्ठा compat_ip6t_get_entries get;
	काष्ठा xt_table *t;

	अगर (*len < माप(get))
		वापस -EINVAL;

	अगर (copy_from_user(&get, uptr, माप(get)) != 0)
		वापस -EFAULT;

	अगर (*len != माप(काष्ठा compat_ip6t_get_entries) + get.size)
		वापस -EINVAL;

	get.name[माप(get.name) - 1] = '\0';

	xt_compat_lock(AF_INET6);
	t = xt_find_table_lock(net, AF_INET6, get.name);
	अगर (!IS_ERR(t)) अणु
		स्थिर काष्ठा xt_table_info *निजी = t->निजी;
		काष्ठा xt_table_info info;
		ret = compat_table_info(निजी, &info);
		अगर (!ret && get.size == info.size)
			ret = compat_copy_entries_to_user(निजी->size,
							  t, uptr->entrytable);
		अन्यथा अगर (!ret)
			ret = -EAGAIN;

		xt_compat_flush_offsets(AF_INET6);
		module_put(t->me);
		xt_table_unlock(t);
	पूर्ण अन्यथा
		ret = PTR_ERR(t);

	xt_compat_unlock(AF_INET6);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
करो_ip6t_set_ctl(काष्ठा sock *sk, पूर्णांक cmd, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल IP6T_SO_SET_REPLACE:
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		अगर (in_compat_syscall())
			ret = compat_करो_replace(sock_net(sk), arg, len);
		अन्यथा
#पूर्ण_अगर
			ret = करो_replace(sock_net(sk), arg, len);
		अवरोध;

	हाल IP6T_SO_SET_ADD_COUNTERS:
		ret = करो_add_counters(sock_net(sk), arg, len);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
करो_ip6t_get_ctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *user, पूर्णांक *len)
अणु
	पूर्णांक ret;

	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल IP6T_SO_GET_INFO:
		ret = get_info(sock_net(sk), user, len);
		अवरोध;

	हाल IP6T_SO_GET_ENTRIES:
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		अगर (in_compat_syscall())
			ret = compat_get_entries(sock_net(sk), user, len);
		अन्यथा
#पूर्ण_अगर
			ret = get_entries(sock_net(sk), user, len);
		अवरोध;

	हाल IP6T_SO_GET_REVISION_MATCH:
	हाल IP6T_SO_GET_REVISION_TARGET: अणु
		काष्ठा xt_get_revision rev;
		पूर्णांक target;

		अगर (*len != माप(rev)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&rev, user, माप(rev)) != 0) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		rev.name[माप(rev.name)-1] = 0;

		अगर (cmd == IP6T_SO_GET_REVISION_TARGET)
			target = 1;
		अन्यथा
			target = 0;

		try_then_request_module(xt_find_revision(AF_INET6, rev.name,
							 rev.revision,
							 target, &ret),
					"ip6t_%s", rev.name);
		अवरोध;
	पूर्ण

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __ip6t_unरेजिस्टर_table(काष्ठा net *net, काष्ठा xt_table *table)
अणु
	काष्ठा xt_table_info *निजी;
	व्योम *loc_cpu_entry;
	काष्ठा module *table_owner = table->me;
	काष्ठा ip6t_entry *iter;

	निजी = xt_unरेजिस्टर_table(table);

	/* Decrease module usage counts and मुक्त resources */
	loc_cpu_entry = निजी->entries;
	xt_entry_क्रमeach(iter, loc_cpu_entry, निजी->size)
		cleanup_entry(iter, net);
	अगर (निजी->number > निजी->initial_entries)
		module_put(table_owner);
	xt_मुक्त_table_info(निजी);
पूर्ण

पूर्णांक ip6t_रेजिस्टर_table(काष्ठा net *net, स्थिर काष्ठा xt_table *table,
			स्थिर काष्ठा ip6t_replace *repl,
			स्थिर काष्ठा nf_hook_ops *ढाँचा_ops)
अणु
	काष्ठा nf_hook_ops *ops;
	अचिन्हित पूर्णांक num_ops;
	पूर्णांक ret, i;
	काष्ठा xt_table_info *newinfo;
	काष्ठा xt_table_info bootstrap = अणु0पूर्ण;
	व्योम *loc_cpu_entry;
	काष्ठा xt_table *new_table;

	newinfo = xt_alloc_table_info(repl->size);
	अगर (!newinfo)
		वापस -ENOMEM;

	loc_cpu_entry = newinfo->entries;
	स_नकल(loc_cpu_entry, repl->entries, repl->size);

	ret = translate_table(net, newinfo, loc_cpu_entry, repl);
	अगर (ret != 0) अणु
		xt_मुक्त_table_info(newinfo);
		वापस ret;
	पूर्ण

	new_table = xt_रेजिस्टर_table(net, table, &bootstrap, newinfo);
	अगर (IS_ERR(new_table)) अणु
		xt_मुक्त_table_info(newinfo);
		वापस PTR_ERR(new_table);
	पूर्ण

	अगर (!ढाँचा_ops)
		वापस 0;

	num_ops = hweight32(table->valid_hooks);
	अगर (num_ops == 0) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	ops = kmemdup(ढाँचा_ops, माप(*ops) * num_ops, GFP_KERNEL);
	अगर (!ops) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < num_ops; i++)
		ops[i].priv = new_table;

	new_table->ops = ops;

	ret = nf_रेजिस्टर_net_hooks(net, ops, num_ops);
	अगर (ret != 0)
		जाओ out_मुक्त;

	वापस ret;

out_मुक्त:
	__ip6t_unरेजिस्टर_table(net, new_table);
	वापस ret;
पूर्ण

व्योम ip6t_unरेजिस्टर_table_pre_निकास(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा xt_table *table = xt_find_table(net, NFPROTO_IPV6, name);

	अगर (table)
		nf_unरेजिस्टर_net_hooks(net, table->ops, hweight32(table->valid_hooks));
पूर्ण

व्योम ip6t_unरेजिस्टर_table_निकास(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा xt_table *table = xt_find_table(net, NFPROTO_IPV6, name);

	अगर (table)
		__ip6t_unरेजिस्टर_table(net, table);
पूर्ण

/* Returns 1 अगर the type and code is matched by the range, 0 otherwise */
अटल अंतरभूत bool
icmp6_type_code_match(u_पूर्णांक8_t test_type, u_पूर्णांक8_t min_code, u_पूर्णांक8_t max_code,
		     u_पूर्णांक8_t type, u_पूर्णांक8_t code,
		     bool invert)
अणु
	वापस (type == test_type && code >= min_code && code <= max_code)
		^ invert;
पूर्ण

अटल bool
icmp6_match(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा icmp6hdr *ic;
	काष्ठा icmp6hdr _icmph;
	स्थिर काष्ठा ip6t_icmp *icmpinfo = par->matchinfo;

	/* Must not be a fragment. */
	अगर (par->fragoff != 0)
		वापस false;

	ic = skb_header_poपूर्णांकer(skb, par->thoff, माप(_icmph), &_icmph);
	अगर (ic == शून्य) अणु
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		par->hotdrop = true;
		वापस false;
	पूर्ण

	वापस icmp6_type_code_match(icmpinfo->type,
				     icmpinfo->code[0],
				     icmpinfo->code[1],
				     ic->icmp6_type, ic->icmp6_code,
				     !!(icmpinfo->invflags&IP6T_ICMP_INV));
पूर्ण

/* Called when user tries to insert an entry of this type. */
अटल पूर्णांक icmp6_checkentry(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ip6t_icmp *icmpinfo = par->matchinfo;

	/* Must specअगरy no unknown invflags */
	वापस (icmpinfo->invflags & ~IP6T_ICMP_INV) ? -EINVAL : 0;
पूर्ण

/* The built-in tarमाला_लो: standard (शून्य) and error. */
अटल काष्ठा xt_target ip6t_builtin_tg[] __पढ़ो_mostly = अणु
	अणु
		.name             = XT_STANDARD_TARGET,
		.tarमाला_लोize       = माप(पूर्णांक),
		.family           = NFPROTO_IPV6,
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		.compatsize       = माप(compat_पूर्णांक_t),
		.compat_from_user = compat_standard_from_user,
		.compat_to_user   = compat_standard_to_user,
#पूर्ण_अगर
	पूर्ण,
	अणु
		.name             = XT_ERROR_TARGET,
		.target           = ip6t_error,
		.tarमाला_लोize       = XT_FUNCTION_MAXNAMELEN,
		.family           = NFPROTO_IPV6,
	पूर्ण,
पूर्ण;

अटल काष्ठा nf_sockopt_ops ip6t_sockopts = अणु
	.pf		= PF_INET6,
	.set_opपंचांगin	= IP6T_BASE_CTL,
	.set_opपंचांगax	= IP6T_SO_SET_MAX+1,
	.set		= करो_ip6t_set_ctl,
	.get_opपंचांगin	= IP6T_BASE_CTL,
	.get_opपंचांगax	= IP6T_SO_GET_MAX+1,
	.get		= करो_ip6t_get_ctl,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा xt_match ip6t_builtin_mt[] __पढ़ो_mostly = अणु
	अणु
		.name       = "icmp6",
		.match      = icmp6_match,
		.matchsize  = माप(काष्ठा ip6t_icmp),
		.checkentry = icmp6_checkentry,
		.proto      = IPPROTO_ICMPV6,
		.family     = NFPROTO_IPV6,
		.me	    = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __net_init ip6_tables_net_init(काष्ठा net *net)
अणु
	वापस xt_proto_init(net, NFPROTO_IPV6);
पूर्ण

अटल व्योम __net_निकास ip6_tables_net_निकास(काष्ठा net *net)
अणु
	xt_proto_fini(net, NFPROTO_IPV6);
पूर्ण

अटल काष्ठा pernet_operations ip6_tables_net_ops = अणु
	.init = ip6_tables_net_init,
	.निकास = ip6_tables_net_निकास,
पूर्ण;

अटल पूर्णांक __init ip6_tables_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&ip6_tables_net_ops);
	अगर (ret < 0)
		जाओ err1;

	/* No one अन्यथा will be करोwning sem now, so we won't sleep */
	ret = xt_रेजिस्टर_tarमाला_लो(ip6t_builtin_tg, ARRAY_SIZE(ip6t_builtin_tg));
	अगर (ret < 0)
		जाओ err2;
	ret = xt_रेजिस्टर_matches(ip6t_builtin_mt, ARRAY_SIZE(ip6t_builtin_mt));
	अगर (ret < 0)
		जाओ err4;

	/* Register setsockopt */
	ret = nf_रेजिस्टर_sockopt(&ip6t_sockopts);
	अगर (ret < 0)
		जाओ err5;

	वापस 0;

err5:
	xt_unरेजिस्टर_matches(ip6t_builtin_mt, ARRAY_SIZE(ip6t_builtin_mt));
err4:
	xt_unरेजिस्टर_tarमाला_लो(ip6t_builtin_tg, ARRAY_SIZE(ip6t_builtin_tg));
err2:
	unरेजिस्टर_pernet_subsys(&ip6_tables_net_ops);
err1:
	वापस ret;
पूर्ण

अटल व्योम __निकास ip6_tables_fini(व्योम)
अणु
	nf_unरेजिस्टर_sockopt(&ip6t_sockopts);

	xt_unरेजिस्टर_matches(ip6t_builtin_mt, ARRAY_SIZE(ip6t_builtin_mt));
	xt_unरेजिस्टर_tarमाला_लो(ip6t_builtin_tg, ARRAY_SIZE(ip6t_builtin_tg));
	unरेजिस्टर_pernet_subsys(&ip6_tables_net_ops);
पूर्ण

EXPORT_SYMBOL(ip6t_रेजिस्टर_table);
EXPORT_SYMBOL(ip6t_unरेजिस्टर_table_pre_निकास);
EXPORT_SYMBOL(ip6t_unरेजिस्टर_table_निकास);
EXPORT_SYMBOL(ip6t_करो_table);

module_init(ip6_tables_init);
module_निकास(ip6_tables_fini);
