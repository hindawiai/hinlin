<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Packet matching code क्रम ARP packets.
 *
 * Based heavily, अगर not almost entirely, upon ip_tables.c framework.
 *
 * Some ARP specअगरic bits are:
 *
 * Copyright (C) 2002 David S. Miller (davem@redhat.com)
 * Copyright (C) 2006-2009 Patrick McHardy <kaber@trash.net>
 *
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/capability.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/kmod.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <net/compat.h>
#समावेश <net/sock.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_arp/arp_tables.h>
#समावेश "../../netfilter/xt_repldata.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David S. Miller <davem@redhat.com>");
MODULE_DESCRIPTION("arptables core");

व्योम *arpt_alloc_initial_table(स्थिर काष्ठा xt_table *info)
अणु
	वापस xt_alloc_initial_table(arpt, ARPT);
पूर्ण
EXPORT_SYMBOL_GPL(arpt_alloc_initial_table);

अटल अंतरभूत पूर्णांक arp_devaddr_compare(स्थिर काष्ठा arpt_devaddr_info *ap,
				      स्थिर अक्षर *hdr_addr, पूर्णांक len)
अणु
	पूर्णांक i, ret;

	अगर (len > ARPT_DEV_ADDR_LEN_MAX)
		len = ARPT_DEV_ADDR_LEN_MAX;

	ret = 0;
	क्रम (i = 0; i < len; i++)
		ret |= (hdr_addr[i] ^ ap->addr[i]) & ap->mask[i];

	वापस ret != 0;
पूर्ण

/*
 * Unक्रमtunately, _b and _mask are not aligned to an पूर्णांक (or दीर्घ पूर्णांक)
 * Some arches करोnt care, unrolling the loop is a win on them.
 * For other arches, we only have a 16bit alignement.
 */
अटल अचिन्हित दीर्घ अगरname_compare(स्थिर अक्षर *_a, स्थिर अक्षर *_b, स्थिर अक्षर *_mask)
अणु
#अगर_घोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अचिन्हित दीर्घ ret = अगरname_compare_aligned(_a, _b, _mask);
#अन्यथा
	अचिन्हित दीर्घ ret = 0;
	स्थिर u16 *a = (स्थिर u16 *)_a;
	स्थिर u16 *b = (स्थिर u16 *)_b;
	स्थिर u16 *mask = (स्थिर u16 *)_mask;
	पूर्णांक i;

	क्रम (i = 0; i < IFNAMSIZ/माप(u16); i++)
		ret |= (a[i] ^ b[i]) & mask[i];
#पूर्ण_अगर
	वापस ret;
पूर्ण

/* Returns whether packet matches rule or not. */
अटल अंतरभूत पूर्णांक arp_packet_match(स्थिर काष्ठा arphdr *arphdr,
				   काष्ठा net_device *dev,
				   स्थिर अक्षर *indev,
				   स्थिर अक्षर *outdev,
				   स्थिर काष्ठा arpt_arp *arpinfo)
अणु
	स्थिर अक्षर *arpptr = (अक्षर *)(arphdr + 1);
	स्थिर अक्षर *src_devaddr, *tgt_devaddr;
	__be32 src_ipaddr, tgt_ipaddr;
	दीर्घ ret;

	अगर (NF_INVF(arpinfo, ARPT_INV_ARPOP,
		    (arphdr->ar_op & arpinfo->arpop_mask) != arpinfo->arpop))
		वापस 0;

	अगर (NF_INVF(arpinfo, ARPT_INV_ARPHRD,
		    (arphdr->ar_hrd & arpinfo->arhrd_mask) != arpinfo->arhrd))
		वापस 0;

	अगर (NF_INVF(arpinfo, ARPT_INV_ARPPRO,
		    (arphdr->ar_pro & arpinfo->arpro_mask) != arpinfo->arpro))
		वापस 0;

	अगर (NF_INVF(arpinfo, ARPT_INV_ARPHLN,
		    (arphdr->ar_hln & arpinfo->arhln_mask) != arpinfo->arhln))
		वापस 0;

	src_devaddr = arpptr;
	arpptr += dev->addr_len;
	स_नकल(&src_ipaddr, arpptr, माप(u32));
	arpptr += माप(u32);
	tgt_devaddr = arpptr;
	arpptr += dev->addr_len;
	स_नकल(&tgt_ipaddr, arpptr, माप(u32));

	अगर (NF_INVF(arpinfo, ARPT_INV_SRCDEVADDR,
		    arp_devaddr_compare(&arpinfo->src_devaddr, src_devaddr,
					dev->addr_len)) ||
	    NF_INVF(arpinfo, ARPT_INV_TGTDEVADDR,
		    arp_devaddr_compare(&arpinfo->tgt_devaddr, tgt_devaddr,
					dev->addr_len)))
		वापस 0;

	अगर (NF_INVF(arpinfo, ARPT_INV_SRCIP,
		    (src_ipaddr & arpinfo->smsk.s_addr) != arpinfo->src.s_addr) ||
	    NF_INVF(arpinfo, ARPT_INV_TGTIP,
		    (tgt_ipaddr & arpinfo->पंचांगsk.s_addr) != arpinfo->tgt.s_addr))
		वापस 0;

	/* Look क्रम अगरname matches.  */
	ret = अगरname_compare(indev, arpinfo->inअगरace, arpinfo->inअगरace_mask);

	अगर (NF_INVF(arpinfo, ARPT_INV_VIA_IN, ret != 0))
		वापस 0;

	ret = अगरname_compare(outdev, arpinfo->outअगरace, arpinfo->outअगरace_mask);

	अगर (NF_INVF(arpinfo, ARPT_INV_VIA_OUT, ret != 0))
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक arp_checkentry(स्थिर काष्ठा arpt_arp *arp)
अणु
	अगर (arp->flags & ~ARPT_F_MASK)
		वापस 0;
	अगर (arp->invflags & ~ARPT_INV_MASK)
		वापस 0;

	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक
arpt_error(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	net_err_ratelimited("arp_tables: error: '%s'\n",
			    (स्थिर अक्षर *)par->targinfo);

	वापस NF_DROP;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा xt_entry_target *
arpt_get_target_c(स्थिर काष्ठा arpt_entry *e)
अणु
	वापस arpt_get_target((काष्ठा arpt_entry *)e);
पूर्ण

अटल अंतरभूत काष्ठा arpt_entry *
get_entry(स्थिर व्योम *base, अचिन्हित पूर्णांक offset)
अणु
	वापस (काष्ठा arpt_entry *)(base + offset);
पूर्ण

अटल अंतरभूत
काष्ठा arpt_entry *arpt_next_entry(स्थिर काष्ठा arpt_entry *entry)
अणु
	वापस (व्योम *)entry + entry->next_offset;
पूर्ण

अचिन्हित पूर्णांक arpt_करो_table(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा nf_hook_state *state,
			   काष्ठा xt_table *table)
अणु
	अचिन्हित पूर्णांक hook = state->hook;
	अटल स्थिर अक्षर nulldevname[IFNAMSIZ] __attribute__((aligned(माप(दीर्घ))));
	अचिन्हित पूर्णांक verdict = NF_DROP;
	स्थिर काष्ठा arphdr *arp;
	काष्ठा arpt_entry *e, **jumpstack;
	स्थिर अक्षर *indev, *outdev;
	स्थिर व्योम *table_base;
	अचिन्हित पूर्णांक cpu, stackidx = 0;
	स्थिर काष्ठा xt_table_info *निजी;
	काष्ठा xt_action_param acpar;
	अचिन्हित पूर्णांक addend;

	अगर (!pskb_may_pull(skb, arp_hdr_len(skb->dev)))
		वापस NF_DROP;

	indev = state->in ? state->in->name : nulldevname;
	outdev = state->out ? state->out->name : nulldevname;

	local_bh_disable();
	addend = xt_ग_लिखो_recseq_begin();
	निजी = READ_ONCE(table->निजी); /* Address dependency. */
	cpu     = smp_processor_id();
	table_base = निजी->entries;
	jumpstack  = (काष्ठा arpt_entry **)निजी->jumpstack[cpu];

	/* No TEE support क्रम arptables, so no need to चयन to alternate
	 * stack.  All tarमाला_लो that reenter must वापस असलolute verdicts.
	 */
	e = get_entry(table_base, निजी->hook_entry[hook]);

	acpar.state   = state;
	acpar.hotdrop = false;

	arp = arp_hdr(skb);
	करो अणु
		स्थिर काष्ठा xt_entry_target *t;
		काष्ठा xt_counters *counter;

		अगर (!arp_packet_match(arp, skb->dev, indev, outdev, &e->arp)) अणु
			e = arpt_next_entry(e);
			जारी;
		पूर्ण

		counter = xt_get_this_cpu_counter(&e->counters);
		ADD_COUNTER(*counter, arp_hdr_len(skb->dev), 1);

		t = arpt_get_target_c(e);

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
				अगर (stackidx == 0) अणु
					e = get_entry(table_base,
						      निजी->underflow[hook]);
				पूर्ण अन्यथा अणु
					e = jumpstack[--stackidx];
					e = arpt_next_entry(e);
				पूर्ण
				जारी;
			पूर्ण
			अगर (table_base + v
			    != arpt_next_entry(e)) अणु
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

		अगर (verdict == XT_CONTINUE) अणु
			/* Target might have changed stuff. */
			arp = arp_hdr(skb);
			e = arpt_next_entry(e);
		पूर्ण अन्यथा अणु
			/* Verdict */
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!acpar.hotdrop);
	xt_ग_लिखो_recseq_end(addend);
	local_bh_enable();

	अगर (acpar.hotdrop)
		वापस NF_DROP;
	अन्यथा
		वापस verdict;
पूर्ण

/* All zeroes == unconditional rule. */
अटल अंतरभूत bool unconditional(स्थिर काष्ठा arpt_entry *e)
अणु
	अटल स्थिर काष्ठा arpt_arp uncond;

	वापस e->target_offset == माप(काष्ठा arpt_entry) &&
	       स_भेद(&e->arp, &uncond, माप(uncond)) == 0;
पूर्ण

/* Figures out from what hook each rule can be called: वापसs 0 अगर
 * there are loops.  Puts hook biपंचांगask in comefrom.
 */
अटल पूर्णांक mark_source_chains(स्थिर काष्ठा xt_table_info *newinfo,
			      अचिन्हित पूर्णांक valid_hooks, व्योम *entry0,
			      अचिन्हित पूर्णांक *offsets)
अणु
	अचिन्हित पूर्णांक hook;

	/* No recursion; use packet counter to save back ptrs (reset
	 * to 0 as we leave), and comefrom to save source hook biपंचांगask.
	 */
	क्रम (hook = 0; hook < NF_ARP_NUMHOOKS; hook++) अणु
		अचिन्हित पूर्णांक pos = newinfo->hook_entry[hook];
		काष्ठा arpt_entry *e = entry0 + pos;

		अगर (!(valid_hooks & (1 << hook)))
			जारी;

		/* Set initial back poपूर्णांकer. */
		e->counters.pcnt = pos;

		क्रम (;;) अणु
			स्थिर काष्ठा xt_standard_target *t
				= (व्योम *)arpt_get_target_c(e);
			पूर्णांक visited = e->comefrom & (1 << hook);

			अगर (e->comefrom & (1 << NF_ARP_NUMHOOKS))
				वापस 0;

			e->comefrom
				|= ((1 << hook) | (1 << NF_ARP_NUMHOOKS));

			/* Unconditional वापस/END. */
			अगर ((unconditional(e) &&
			     (म_भेद(t->target.u.user.name,
				     XT_STANDARD_TARGET) == 0) &&
			     t->verdict < 0) || visited) अणु
				अचिन्हित पूर्णांक oldpos, size;

				/* Return: backtrack through the last
				 * big jump.
				 */
				करो अणु
					e->comefrom ^= (1<<NF_ARP_NUMHOOKS);
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

अटल पूर्णांक check_target(काष्ठा arpt_entry *e, काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा xt_entry_target *t = arpt_get_target(e);
	काष्ठा xt_tgchk_param par = अणु
		.net       = net,
		.table     = name,
		.entryinfo = e,
		.target    = t->u.kernel.target,
		.targinfo  = t->data,
		.hook_mask = e->comefrom,
		.family    = NFPROTO_ARP,
	पूर्ण;

	वापस xt_check_target(&par, t->u.target_size - माप(*t), 0, false);
पूर्ण

अटल पूर्णांक
find_check_entry(काष्ठा arpt_entry *e, काष्ठा net *net, स्थिर अक्षर *name,
		 अचिन्हित पूर्णांक size,
		 काष्ठा xt_percpu_counter_alloc_state *alloc_state)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा xt_target *target;
	पूर्णांक ret;

	अगर (!xt_percpu_counter_alloc(alloc_state, &e->counters))
		वापस -ENOMEM;

	t = arpt_get_target(e);
	target = xt_request_find_target(NFPROTO_ARP, t->u.user.name,
					t->u.user.revision);
	अगर (IS_ERR(target)) अणु
		ret = PTR_ERR(target);
		जाओ out;
	पूर्ण
	t->u.kernel.target = target;

	ret = check_target(e, net, name);
	अगर (ret)
		जाओ err;
	वापस 0;
err:
	module_put(t->u.kernel.target->me);
out:
	xt_percpu_counter_मुक्त(&e->counters);

	वापस ret;
पूर्ण

अटल bool check_underflow(स्थिर काष्ठा arpt_entry *e)
अणु
	स्थिर काष्ठा xt_entry_target *t;
	अचिन्हित पूर्णांक verdict;

	अगर (!unconditional(e))
		वापस false;
	t = arpt_get_target_c(e);
	अगर (म_भेद(t->u.user.name, XT_STANDARD_TARGET) != 0)
		वापस false;
	verdict = ((काष्ठा xt_standard_target *)t)->verdict;
	verdict = -verdict - 1;
	वापस verdict == NF_DROP || verdict == NF_ACCEPT;
पूर्ण

अटल अंतरभूत पूर्णांक check_entry_size_and_hooks(काष्ठा arpt_entry *e,
					     काष्ठा xt_table_info *newinfo,
					     स्थिर अचिन्हित अक्षर *base,
					     स्थिर अचिन्हित अक्षर *limit,
					     स्थिर अचिन्हित पूर्णांक *hook_entries,
					     स्थिर अचिन्हित पूर्णांक *underflows,
					     अचिन्हित पूर्णांक valid_hooks)
अणु
	अचिन्हित पूर्णांक h;
	पूर्णांक err;

	अगर ((अचिन्हित दीर्घ)e % __alignof__(काष्ठा arpt_entry) != 0 ||
	    (अचिन्हित अक्षर *)e + माप(काष्ठा arpt_entry) >= limit ||
	    (अचिन्हित अक्षर *)e + e->next_offset > limit)
		वापस -EINVAL;

	अगर (e->next_offset
	    < माप(काष्ठा arpt_entry) + माप(काष्ठा xt_entry_target))
		वापस -EINVAL;

	अगर (!arp_checkentry(&e->arp))
		वापस -EINVAL;

	err = xt_check_entry_offsets(e, e->elems, e->target_offset,
				     e->next_offset);
	अगर (err)
		वापस err;

	/* Check hooks & underflows */
	क्रम (h = 0; h < NF_ARP_NUMHOOKS; h++) अणु
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

अटल व्योम cleanup_entry(काष्ठा arpt_entry *e, काष्ठा net *net)
अणु
	काष्ठा xt_tgdtor_param par;
	काष्ठा xt_entry_target *t;

	t = arpt_get_target(e);
	par.net      = net;
	par.target   = t->u.kernel.target;
	par.targinfo = t->data;
	par.family   = NFPROTO_ARP;
	अगर (par.target->destroy != शून्य)
		par.target->destroy(&par);
	module_put(par.target->me);
	xt_percpu_counter_मुक्त(&e->counters);
पूर्ण

/* Checks and translates the user-supplied table segment (held in
 * newinfo).
 */
अटल पूर्णांक translate_table(काष्ठा net *net,
			   काष्ठा xt_table_info *newinfo,
			   व्योम *entry0,
			   स्थिर काष्ठा arpt_replace *repl)
अणु
	काष्ठा xt_percpu_counter_alloc_state alloc_state = अणु 0 पूर्ण;
	काष्ठा arpt_entry *iter;
	अचिन्हित पूर्णांक *offsets;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	newinfo->size = repl->size;
	newinfo->number = repl->num_entries;

	/* Init all hooks to impossible value. */
	क्रम (i = 0; i < NF_ARP_NUMHOOKS; i++) अणु
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
		अगर (म_भेद(arpt_get_target(iter)->u.user.name,
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

अटल व्योम get_counters(स्थिर काष्ठा xt_table_info *t,
			 काष्ठा xt_counters counters[])
अणु
	काष्ठा arpt_entry *iter;
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
	काष्ठा arpt_entry *iter;
	अचिन्हित पूर्णांक cpu, i;

	क्रम_each_possible_cpu(cpu) अणु
		i = 0;
		xt_entry_क्रमeach(iter, t->entries, t->size) अणु
			काष्ठा xt_counters *पंचांगp;

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
	 * (other than comefrom, which userspace करोesn't care
	 * about).
	 */
	countersize = माप(काष्ठा xt_counters) * निजी->number;
	counters = vzalloc(countersize);

	अगर (counters == शून्य)
		वापस ERR_PTR(-ENOMEM);

	get_counters(निजी, counters);

	वापस counters;
पूर्ण

अटल पूर्णांक copy_entries_to_user(अचिन्हित पूर्णांक total_size,
				स्थिर काष्ठा xt_table *table,
				व्योम __user *userptr)
अणु
	अचिन्हित पूर्णांक off, num;
	स्थिर काष्ठा arpt_entry *e;
	काष्ठा xt_counters *counters;
	काष्ठा xt_table_info *निजी = table->निजी;
	पूर्णांक ret = 0;
	व्योम *loc_cpu_entry;

	counters = alloc_counters(table);
	अगर (IS_ERR(counters))
		वापस PTR_ERR(counters);

	loc_cpu_entry = निजी->entries;

	/* FIXME: use iterator macros --RR */
	/* ... then go back and fix counters and names */
	क्रम (off = 0, num = 0; off < total_size; off += e->next_offset, num++)अणु
		स्थिर काष्ठा xt_entry_target *t;

		e = loc_cpu_entry + off;
		अगर (copy_to_user(userptr + off, e, माप(*e))) अणु
			ret = -EFAULT;
			जाओ मुक्त_counters;
		पूर्ण
		अगर (copy_to_user(userptr + off
				 + दुरत्व(काष्ठा arpt_entry, counters),
				 &counters[num],
				 माप(counters[num])) != 0) अणु
			ret = -EFAULT;
			जाओ मुक्त_counters;
		पूर्ण

		t = arpt_get_target_c(e);
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
		v += xt_compat_calc_jump(NFPROTO_ARP, v);
	स_नकल(dst, &v, माप(v));
पूर्ण

अटल पूर्णांक compat_standard_to_user(व्योम __user *dst, स्थिर व्योम *src)
अणु
	compat_पूर्णांक_t cv = *(पूर्णांक *)src;

	अगर (cv > 0)
		cv -= xt_compat_calc_jump(NFPROTO_ARP, cv);
	वापस copy_to_user(dst, &cv, माप(cv)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक compat_calc_entry(स्थिर काष्ठा arpt_entry *e,
			     स्थिर काष्ठा xt_table_info *info,
			     स्थिर व्योम *base, काष्ठा xt_table_info *newinfo)
अणु
	स्थिर काष्ठा xt_entry_target *t;
	अचिन्हित पूर्णांक entry_offset;
	पूर्णांक off, i, ret;

	off = माप(काष्ठा arpt_entry) - माप(काष्ठा compat_arpt_entry);
	entry_offset = (व्योम *)e - base;

	t = arpt_get_target_c(e);
	off += xt_compat_target_offset(t->u.kernel.target);
	newinfo->size -= off;
	ret = xt_compat_add_offset(NFPROTO_ARP, entry_offset, off);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < NF_ARP_NUMHOOKS; i++) अणु
		अगर (info->hook_entry[i] &&
		    (e < (काष्ठा arpt_entry *)(base + info->hook_entry[i])))
			newinfo->hook_entry[i] -= off;
		अगर (info->underflow[i] &&
		    (e < (काष्ठा arpt_entry *)(base + info->underflow[i])))
			newinfo->underflow[i] -= off;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compat_table_info(स्थिर काष्ठा xt_table_info *info,
			     काष्ठा xt_table_info *newinfo)
अणु
	काष्ठा arpt_entry *iter;
	स्थिर व्योम *loc_cpu_entry;
	पूर्णांक ret;

	अगर (!newinfo || !info)
		वापस -EINVAL;

	/* we करोnt care about newinfo->entries */
	स_नकल(newinfo, info, दुरत्व(काष्ठा xt_table_info, entries));
	newinfo->initial_entries = 0;
	loc_cpu_entry = info->entries;
	ret = xt_compat_init_offsets(NFPROTO_ARP, info->number);
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

	अगर (*len != माप(काष्ठा arpt_getinfo))
		वापस -EINVAL;

	अगर (copy_from_user(name, user, माप(name)) != 0)
		वापस -EFAULT;

	name[XT_TABLE_MAXNAMELEN-1] = '\0';
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
	अगर (in_compat_syscall())
		xt_compat_lock(NFPROTO_ARP);
#पूर्ण_अगर
	t = xt_request_find_table_lock(net, NFPROTO_ARP, name);
	अगर (!IS_ERR(t)) अणु
		काष्ठा arpt_getinfo info;
		स्थिर काष्ठा xt_table_info *निजी = t->निजी;
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		काष्ठा xt_table_info पंचांगp;

		अगर (in_compat_syscall()) अणु
			ret = compat_table_info(निजी, &पंचांगp);
			xt_compat_flush_offsets(NFPROTO_ARP);
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
		xt_compat_unlock(NFPROTO_ARP);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक get_entries(काष्ठा net *net, काष्ठा arpt_get_entries __user *uptr,
		       स्थिर पूर्णांक *len)
अणु
	पूर्णांक ret;
	काष्ठा arpt_get_entries get;
	काष्ठा xt_table *t;

	अगर (*len < माप(get))
		वापस -EINVAL;
	अगर (copy_from_user(&get, uptr, माप(get)) != 0)
		वापस -EFAULT;
	अगर (*len != माप(काष्ठा arpt_get_entries) + get.size)
		वापस -EINVAL;

	get.name[माप(get.name) - 1] = '\0';

	t = xt_find_table_lock(net, NFPROTO_ARP, get.name);
	अगर (!IS_ERR(t)) अणु
		स्थिर काष्ठा xt_table_info *निजी = t->निजी;

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

अटल पूर्णांक __करो_replace(काष्ठा net *net, स्थिर अक्षर *name,
			अचिन्हित पूर्णांक valid_hooks,
			काष्ठा xt_table_info *newinfo,
			अचिन्हित पूर्णांक num_counters,
			व्योम __user *counters_ptr)
अणु
	पूर्णांक ret;
	काष्ठा xt_table *t;
	काष्ठा xt_table_info *oldinfo;
	काष्ठा xt_counters *counters;
	व्योम *loc_cpu_old_entry;
	काष्ठा arpt_entry *iter;

	ret = 0;
	counters = xt_counters_alloc(num_counters);
	अगर (!counters) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	t = xt_request_find_table_lock(net, NFPROTO_ARP, name);
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
	loc_cpu_old_entry = oldinfo->entries;
	xt_entry_क्रमeach(iter, loc_cpu_old_entry, oldinfo->size)
		cleanup_entry(iter, net);

	xt_मुक्त_table_info(oldinfo);
	अगर (copy_to_user(counters_ptr, counters,
			 माप(काष्ठा xt_counters) * num_counters) != 0) अणु
		/* Silent error, can't fail, new table is alपढ़ोy in place */
		net_warn_ratelimited("arptables: counters copy to user failed while replacing table\n");
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

अटल पूर्णांक करो_replace(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा arpt_replace पंचांगp;
	काष्ठा xt_table_info *newinfo;
	व्योम *loc_cpu_entry;
	काष्ठा arpt_entry *iter;

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

अटल पूर्णांक करो_add_counters(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा xt_counters_info पंचांगp;
	काष्ठा xt_counters *paddc;
	काष्ठा xt_table *t;
	स्थिर काष्ठा xt_table_info *निजी;
	पूर्णांक ret = 0;
	काष्ठा arpt_entry *iter;
	अचिन्हित पूर्णांक addend;

	paddc = xt_copy_counters(arg, len, &पंचांगp);
	अगर (IS_ERR(paddc))
		वापस PTR_ERR(paddc);

	t = xt_find_table_lock(net, NFPROTO_ARP, पंचांगp.name);
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
	xt_entry_क्रमeach(iter,  निजी->entries, निजी->size) अणु
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
काष्ठा compat_arpt_replace अणु
	अक्षर				name[XT_TABLE_MAXNAMELEN];
	u32				valid_hooks;
	u32				num_entries;
	u32				size;
	u32				hook_entry[NF_ARP_NUMHOOKS];
	u32				underflow[NF_ARP_NUMHOOKS];
	u32				num_counters;
	compat_uptr_t			counters;
	काष्ठा compat_arpt_entry	entries[];
पूर्ण;

अटल अंतरभूत व्योम compat_release_entry(काष्ठा compat_arpt_entry *e)
अणु
	काष्ठा xt_entry_target *t;

	t = compat_arpt_get_target(e);
	module_put(t->u.kernel.target->me);
पूर्ण

अटल पूर्णांक
check_compat_entry_size_and_hooks(काष्ठा compat_arpt_entry *e,
				  काष्ठा xt_table_info *newinfo,
				  अचिन्हित पूर्णांक *size,
				  स्थिर अचिन्हित अक्षर *base,
				  स्थिर अचिन्हित अक्षर *limit)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा xt_target *target;
	अचिन्हित पूर्णांक entry_offset;
	पूर्णांक ret, off;

	अगर ((अचिन्हित दीर्घ)e % __alignof__(काष्ठा compat_arpt_entry) != 0 ||
	    (अचिन्हित अक्षर *)e + माप(काष्ठा compat_arpt_entry) >= limit ||
	    (अचिन्हित अक्षर *)e + e->next_offset > limit)
		वापस -EINVAL;

	अगर (e->next_offset < माप(काष्ठा compat_arpt_entry) +
			     माप(काष्ठा compat_xt_entry_target))
		वापस -EINVAL;

	अगर (!arp_checkentry(&e->arp))
		वापस -EINVAL;

	ret = xt_compat_check_entry_offsets(e, e->elems, e->target_offset,
					    e->next_offset);
	अगर (ret)
		वापस ret;

	off = माप(काष्ठा arpt_entry) - माप(काष्ठा compat_arpt_entry);
	entry_offset = (व्योम *)e - (व्योम *)base;

	t = compat_arpt_get_target(e);
	target = xt_request_find_target(NFPROTO_ARP, t->u.user.name,
					t->u.user.revision);
	अगर (IS_ERR(target)) अणु
		ret = PTR_ERR(target);
		जाओ out;
	पूर्ण
	t->u.kernel.target = target;

	off += xt_compat_target_offset(target);
	*size += off;
	ret = xt_compat_add_offset(NFPROTO_ARP, entry_offset, off);
	अगर (ret)
		जाओ release_target;

	वापस 0;

release_target:
	module_put(t->u.kernel.target->me);
out:
	वापस ret;
पूर्ण

अटल व्योम
compat_copy_entry_from_user(काष्ठा compat_arpt_entry *e, व्योम **dstptr,
			    अचिन्हित पूर्णांक *size,
			    काष्ठा xt_table_info *newinfo, अचिन्हित अक्षर *base)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा arpt_entry *de;
	अचिन्हित पूर्णांक origsize;
	पूर्णांक h;

	origsize = *size;
	de = *dstptr;
	स_नकल(de, e, माप(काष्ठा arpt_entry));
	स_नकल(&de->counters, &e->counters, माप(e->counters));

	*dstptr += माप(काष्ठा arpt_entry);
	*size += माप(काष्ठा arpt_entry) - माप(काष्ठा compat_arpt_entry);

	de->target_offset = e->target_offset - (origsize - *size);
	t = compat_arpt_get_target(e);
	xt_compat_target_from_user(t, dstptr, size);

	de->next_offset = e->next_offset - (origsize - *size);
	क्रम (h = 0; h < NF_ARP_NUMHOOKS; h++) अणु
		अगर ((अचिन्हित अक्षर *)de - base < newinfo->hook_entry[h])
			newinfo->hook_entry[h] -= origsize - *size;
		अगर ((अचिन्हित अक्षर *)de - base < newinfo->underflow[h])
			newinfo->underflow[h] -= origsize - *size;
	पूर्ण
पूर्ण

अटल पूर्णांक translate_compat_table(काष्ठा net *net,
				  काष्ठा xt_table_info **pinfo,
				  व्योम **pentry0,
				  स्थिर काष्ठा compat_arpt_replace *compatr)
अणु
	अचिन्हित पूर्णांक i, j;
	काष्ठा xt_table_info *newinfo, *info;
	व्योम *pos, *entry0, *entry1;
	काष्ठा compat_arpt_entry *iter0;
	काष्ठा arpt_replace repl;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	info = *pinfo;
	entry0 = *pentry0;
	size = compatr->size;
	info->number = compatr->num_entries;

	j = 0;
	xt_compat_lock(NFPROTO_ARP);
	ret = xt_compat_init_offsets(NFPROTO_ARP, compatr->num_entries);
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
	क्रम (i = 0; i < NF_ARP_NUMHOOKS; i++) अणु
		newinfo->hook_entry[i] = compatr->hook_entry[i];
		newinfo->underflow[i] = compatr->underflow[i];
	पूर्ण
	entry1 = newinfo->entries;
	pos = entry1;
	size = compatr->size;
	xt_entry_क्रमeach(iter0, entry0, compatr->size)
		compat_copy_entry_from_user(iter0, &pos, &size,
					    newinfo, entry1);

	/* all module references in entry0 are now gone */

	xt_compat_flush_offsets(NFPROTO_ARP);
	xt_compat_unlock(NFPROTO_ARP);

	स_नकल(&repl, compatr, माप(*compatr));

	क्रम (i = 0; i < NF_ARP_NUMHOOKS; i++) अणु
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
	xt_compat_flush_offsets(NFPROTO_ARP);
	xt_compat_unlock(NFPROTO_ARP);
	xt_entry_क्रमeach(iter0, entry0, compatr->size) अणु
		अगर (j-- == 0)
			अवरोध;
		compat_release_entry(iter0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक compat_करो_replace(काष्ठा net *net, sockptr_t arg, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा compat_arpt_replace पंचांगp;
	काष्ठा xt_table_info *newinfo;
	व्योम *loc_cpu_entry;
	काष्ठा arpt_entry *iter;

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

अटल पूर्णांक compat_copy_entry_to_user(काष्ठा arpt_entry *e, व्योम __user **dstptr,
				     compat_uपूर्णांक_t *size,
				     काष्ठा xt_counters *counters,
				     अचिन्हित पूर्णांक i)
अणु
	काष्ठा xt_entry_target *t;
	काष्ठा compat_arpt_entry __user *ce;
	u_पूर्णांक16_t target_offset, next_offset;
	compat_uपूर्णांक_t origsize;
	पूर्णांक ret;

	origsize = *size;
	ce = *dstptr;
	अगर (copy_to_user(ce, e, माप(काष्ठा arpt_entry)) != 0 ||
	    copy_to_user(&ce->counters, &counters[i],
	    माप(counters[i])) != 0)
		वापस -EFAULT;

	*dstptr += माप(काष्ठा compat_arpt_entry);
	*size -= माप(काष्ठा arpt_entry) - माप(काष्ठा compat_arpt_entry);

	target_offset = e->target_offset - (origsize - *size);

	t = arpt_get_target(e);
	ret = xt_compat_target_to_user(t, dstptr, size);
	अगर (ret)
		वापस ret;
	next_offset = e->next_offset - (origsize - *size);
	अगर (put_user(target_offset, &ce->target_offset) != 0 ||
	    put_user(next_offset, &ce->next_offset) != 0)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_copy_entries_to_user(अचिन्हित पूर्णांक total_size,
				       काष्ठा xt_table *table,
				       व्योम __user *userptr)
अणु
	काष्ठा xt_counters *counters;
	स्थिर काष्ठा xt_table_info *निजी = table->निजी;
	व्योम __user *pos;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा arpt_entry *iter;

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

काष्ठा compat_arpt_get_entries अणु
	अक्षर name[XT_TABLE_MAXNAMELEN];
	compat_uपूर्णांक_t size;
	काष्ठा compat_arpt_entry entrytable[];
पूर्ण;

अटल पूर्णांक compat_get_entries(काष्ठा net *net,
			      काष्ठा compat_arpt_get_entries __user *uptr,
			      पूर्णांक *len)
अणु
	पूर्णांक ret;
	काष्ठा compat_arpt_get_entries get;
	काष्ठा xt_table *t;

	अगर (*len < माप(get))
		वापस -EINVAL;
	अगर (copy_from_user(&get, uptr, माप(get)) != 0)
		वापस -EFAULT;
	अगर (*len != माप(काष्ठा compat_arpt_get_entries) + get.size)
		वापस -EINVAL;

	get.name[माप(get.name) - 1] = '\0';

	xt_compat_lock(NFPROTO_ARP);
	t = xt_find_table_lock(net, NFPROTO_ARP, get.name);
	अगर (!IS_ERR(t)) अणु
		स्थिर काष्ठा xt_table_info *निजी = t->निजी;
		काष्ठा xt_table_info info;

		ret = compat_table_info(निजी, &info);
		अगर (!ret && get.size == info.size) अणु
			ret = compat_copy_entries_to_user(निजी->size,
							  t, uptr->entrytable);
		पूर्ण अन्यथा अगर (!ret)
			ret = -EAGAIN;

		xt_compat_flush_offsets(NFPROTO_ARP);
		module_put(t->me);
		xt_table_unlock(t);
	पूर्ण अन्यथा
		ret = PTR_ERR(t);

	xt_compat_unlock(NFPROTO_ARP);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक करो_arpt_set_ctl(काष्ठा sock *sk, पूर्णांक cmd, sockptr_t arg,
		अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल ARPT_SO_SET_REPLACE:
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		अगर (in_compat_syscall())
			ret = compat_करो_replace(sock_net(sk), arg, len);
		अन्यथा
#पूर्ण_अगर
			ret = करो_replace(sock_net(sk), arg, len);
		अवरोध;

	हाल ARPT_SO_SET_ADD_COUNTERS:
		ret = करो_add_counters(sock_net(sk), arg, len);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक करो_arpt_get_ctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *user, पूर्णांक *len)
अणु
	पूर्णांक ret;

	अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	चयन (cmd) अणु
	हाल ARPT_SO_GET_INFO:
		ret = get_info(sock_net(sk), user, len);
		अवरोध;

	हाल ARPT_SO_GET_ENTRIES:
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		अगर (in_compat_syscall())
			ret = compat_get_entries(sock_net(sk), user, len);
		अन्यथा
#पूर्ण_अगर
			ret = get_entries(sock_net(sk), user, len);
		अवरोध;

	हाल ARPT_SO_GET_REVISION_TARGET: अणु
		काष्ठा xt_get_revision rev;

		अगर (*len != माप(rev)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_user(&rev, user, माप(rev)) != 0) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		rev.name[माप(rev.name)-1] = 0;

		try_then_request_module(xt_find_revision(NFPROTO_ARP, rev.name,
							 rev.revision, 1, &ret),
					"arpt_%s", rev.name);
		अवरोध;
	पूर्ण

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __arpt_unरेजिस्टर_table(काष्ठा net *net, काष्ठा xt_table *table)
अणु
	काष्ठा xt_table_info *निजी;
	व्योम *loc_cpu_entry;
	काष्ठा module *table_owner = table->me;
	काष्ठा arpt_entry *iter;

	निजी = xt_unरेजिस्टर_table(table);

	/* Decrease module usage counts and मुक्त resources */
	loc_cpu_entry = निजी->entries;
	xt_entry_क्रमeach(iter, loc_cpu_entry, निजी->size)
		cleanup_entry(iter, net);
	अगर (निजी->number > निजी->initial_entries)
		module_put(table_owner);
	xt_मुक्त_table_info(निजी);
पूर्ण

पूर्णांक arpt_रेजिस्टर_table(काष्ठा net *net,
			स्थिर काष्ठा xt_table *table,
			स्थिर काष्ठा arpt_replace *repl,
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
	__arpt_unरेजिस्टर_table(net, new_table);
	वापस ret;
पूर्ण

व्योम arpt_unरेजिस्टर_table_pre_निकास(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा xt_table *table = xt_find_table(net, NFPROTO_ARP, name);

	अगर (table)
		nf_unरेजिस्टर_net_hooks(net, table->ops, hweight32(table->valid_hooks));
पूर्ण
EXPORT_SYMBOL(arpt_unरेजिस्टर_table_pre_निकास);

व्योम arpt_unरेजिस्टर_table(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा xt_table *table = xt_find_table(net, NFPROTO_ARP, name);

	अगर (table)
		__arpt_unरेजिस्टर_table(net, table);
पूर्ण

/* The built-in tarमाला_लो: standard (शून्य) and error. */
अटल काष्ठा xt_target arpt_builtin_tg[] __पढ़ो_mostly = अणु
	अणु
		.name             = XT_STANDARD_TARGET,
		.tarमाला_लोize       = माप(पूर्णांक),
		.family           = NFPROTO_ARP,
#अगर_घोषित CONFIG_NETFILTER_XTABLES_COMPAT
		.compatsize       = माप(compat_पूर्णांक_t),
		.compat_from_user = compat_standard_from_user,
		.compat_to_user   = compat_standard_to_user,
#पूर्ण_अगर
	पूर्ण,
	अणु
		.name             = XT_ERROR_TARGET,
		.target           = arpt_error,
		.tarमाला_लोize       = XT_FUNCTION_MAXNAMELEN,
		.family           = NFPROTO_ARP,
	पूर्ण,
पूर्ण;

अटल काष्ठा nf_sockopt_ops arpt_sockopts = अणु
	.pf		= PF_INET,
	.set_opपंचांगin	= ARPT_BASE_CTL,
	.set_opपंचांगax	= ARPT_SO_SET_MAX+1,
	.set		= करो_arpt_set_ctl,
	.get_opपंचांगin	= ARPT_BASE_CTL,
	.get_opपंचांगax	= ARPT_SO_GET_MAX+1,
	.get		= करो_arpt_get_ctl,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init arp_tables_net_init(काष्ठा net *net)
अणु
	वापस xt_proto_init(net, NFPROTO_ARP);
पूर्ण

अटल व्योम __net_निकास arp_tables_net_निकास(काष्ठा net *net)
अणु
	xt_proto_fini(net, NFPROTO_ARP);
पूर्ण

अटल काष्ठा pernet_operations arp_tables_net_ops = अणु
	.init = arp_tables_net_init,
	.निकास = arp_tables_net_निकास,
पूर्ण;

अटल पूर्णांक __init arp_tables_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&arp_tables_net_ops);
	अगर (ret < 0)
		जाओ err1;

	/* No one अन्यथा will be करोwning sem now, so we won't sleep */
	ret = xt_रेजिस्टर_tarमाला_लो(arpt_builtin_tg, ARRAY_SIZE(arpt_builtin_tg));
	अगर (ret < 0)
		जाओ err2;

	/* Register setsockopt */
	ret = nf_रेजिस्टर_sockopt(&arpt_sockopts);
	अगर (ret < 0)
		जाओ err4;

	वापस 0;

err4:
	xt_unरेजिस्टर_tarमाला_लो(arpt_builtin_tg, ARRAY_SIZE(arpt_builtin_tg));
err2:
	unरेजिस्टर_pernet_subsys(&arp_tables_net_ops);
err1:
	वापस ret;
पूर्ण

अटल व्योम __निकास arp_tables_fini(व्योम)
अणु
	nf_unरेजिस्टर_sockopt(&arpt_sockopts);
	xt_unरेजिस्टर_tarमाला_लो(arpt_builtin_tg, ARRAY_SIZE(arpt_builtin_tg));
	unरेजिस्टर_pernet_subsys(&arp_tables_net_ops);
पूर्ण

EXPORT_SYMBOL(arpt_रेजिस्टर_table);
EXPORT_SYMBOL(arpt_unरेजिस्टर_table);
EXPORT_SYMBOL(arpt_करो_table);

module_init(arp_tables_init);
module_निकास(arp_tables_fini);
