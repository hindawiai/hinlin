<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* net/sched/sch_dsmark.c - Dअगरferentiated Services field marker */

/* Written 1998-2000 by Werner Almesberger, EPFL ICA */


#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/bitops.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/dsfield.h>
#समावेश <net/inet_ecn.h>
#समावेश <यंत्र/byteorder.h>

/*
 * classid	class		marking
 * -------	-----		-------
 *   n/a	  0		n/a
 *   x:0	  1		use entry [0]
 *   ...	 ...		...
 *   x:y y>0	 y+1		use entry [y]
 *   ...	 ...		...
 * x:indices-1	indices		use entry [indices-1]
 *   ...	 ...		...
 *   x:y	 y+1		use entry [y & (indices-1)]
 *   ...	 ...		...
 * 0xffff	0x10000		use entry [indices-1]
 */


#घोषणा NO_DEFAULT_INDEX	(1 << 16)

काष्ठा mask_value अणु
	u8			mask;
	u8			value;
पूर्ण;

काष्ठा dsmark_qdisc_data अणु
	काष्ठा Qdisc		*q;
	काष्ठा tcf_proto __rcu	*filter_list;
	काष्ठा tcf_block	*block;
	काष्ठा mask_value	*mv;
	u16			indices;
	u8			set_tc_index;
	u32			शेष_index;	/* index range is 0...0xffff */
#घोषणा DSMARK_EMBEDDED_SZ	16
	काष्ठा mask_value	embedded[DSMARK_EMBEDDED_SZ];
पूर्ण;

अटल अंतरभूत पूर्णांक dsmark_valid_index(काष्ठा dsmark_qdisc_data *p, u16 index)
अणु
	वापस index <= p->indices && index > 0;
पूर्ण

/* ------------------------- Class/flow operations ------------------------- */

अटल पूर्णांक dsmark_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			काष्ठा Qdisc *new, काष्ठा Qdisc **old,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);

	pr_debug("%s(sch %p,[qdisc %p],new %p,old %p)\n",
		 __func__, sch, p, new, old);

	अगर (new == शून्य) अणु
		new = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops,
					sch->handle, शून्य);
		अगर (new == शून्य)
			new = &noop_qdisc;
	पूर्ण

	*old = qdisc_replace(sch, new, &p->q);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *dsmark_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	वापस p->q;
पूर्ण

अटल अचिन्हित दीर्घ dsmark_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	वापस TC_H_MIN(classid) + 1;
पूर्ण

अटल अचिन्हित दीर्घ dsmark_bind_filter(काष्ठा Qdisc *sch,
					अचिन्हित दीर्घ parent, u32 classid)
अणु
	pr_debug("%s(sch %p,[qdisc %p],classid %x)\n",
		 __func__, sch, qdisc_priv(sch), classid);

	वापस dsmark_find(sch, classid);
पूर्ण

अटल व्योम dsmark_unbind_filter(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
पूर्ण

अटल स्थिर काष्ठा nla_policy dsmark_policy[TCA_DSMARK_MAX + 1] = अणु
	[TCA_DSMARK_INDICES]		= अणु .type = NLA_U16 पूर्ण,
	[TCA_DSMARK_DEFAULT_INDEX]	= अणु .type = NLA_U16 पूर्ण,
	[TCA_DSMARK_SET_TC_INDEX]	= अणु .type = NLA_FLAG पूर्ण,
	[TCA_DSMARK_MASK]		= अणु .type = NLA_U8 पूर्ण,
	[TCA_DSMARK_VALUE]		= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक dsmark_change(काष्ठा Qdisc *sch, u32 classid, u32 parent,
			 काष्ठा nlattr **tca, अचिन्हित दीर्घ *arg,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_DSMARK_MAX + 1];
	पूर्णांक err = -EINVAL;

	pr_debug("%s(sch %p,[qdisc %p],classid %x,parent %x), arg 0x%lx\n",
		 __func__, sch, p, classid, parent, *arg);

	अगर (!dsmark_valid_index(p, *arg)) अणु
		err = -ENOENT;
		जाओ errout;
	पूर्ण

	अगर (!opt)
		जाओ errout;

	err = nla_parse_nested_deprecated(tb, TCA_DSMARK_MAX, opt,
					  dsmark_policy, शून्य);
	अगर (err < 0)
		जाओ errout;

	अगर (tb[TCA_DSMARK_VALUE])
		p->mv[*arg - 1].value = nla_get_u8(tb[TCA_DSMARK_VALUE]);

	अगर (tb[TCA_DSMARK_MASK])
		p->mv[*arg - 1].mask = nla_get_u8(tb[TCA_DSMARK_MASK]);

	err = 0;

errout:
	वापस err;
पूर्ण

अटल पूर्णांक dsmark_delete(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);

	अगर (!dsmark_valid_index(p, arg))
		वापस -EINVAL;

	p->mv[arg - 1].mask = 0xff;
	p->mv[arg - 1].value = 0;

	वापस 0;
पूर्ण

अटल व्योम dsmark_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	पूर्णांक i;

	pr_debug("%s(sch %p,[qdisc %p],walker %p)\n",
		 __func__, sch, p, walker);

	अगर (walker->stop)
		वापस;

	क्रम (i = 0; i < p->indices; i++) अणु
		अगर (p->mv[i].mask == 0xff && !p->mv[i].value)
			जाओ ignore;
		अगर (walker->count >= walker->skip) अणु
			अगर (walker->fn(sch, i + 1, walker) < 0) अणु
				walker->stop = 1;
				अवरोध;
			पूर्ण
		पूर्ण
ignore:
		walker->count++;
	पूर्ण
पूर्ण

अटल काष्ठा tcf_block *dsmark_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);

	वापस p->block;
पूर्ण

/* --------------------------- Qdisc operations ---------------------------- */

अटल पूर्णांक dsmark_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			  काष्ठा sk_buff **to_मुक्त)
अणु
	अचिन्हित पूर्णांक len = qdisc_pkt_len(skb);
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	पूर्णांक err;

	pr_debug("%s(skb %p,sch %p,[qdisc %p])\n", __func__, skb, sch, p);

	अगर (p->set_tc_index) अणु
		पूर्णांक wlen = skb_network_offset(skb);

		चयन (skb_protocol(skb, true)) अणु
		हाल htons(ETH_P_IP):
			wlen += माप(काष्ठा iphdr);
			अगर (!pskb_may_pull(skb, wlen) ||
			    skb_try_make_writable(skb, wlen))
				जाओ drop;

			skb->tc_index = ipv4_get_dsfield(ip_hdr(skb))
				& ~INET_ECN_MASK;
			अवरोध;

		हाल htons(ETH_P_IPV6):
			wlen += माप(काष्ठा ipv6hdr);
			अगर (!pskb_may_pull(skb, wlen) ||
			    skb_try_make_writable(skb, wlen))
				जाओ drop;

			skb->tc_index = ipv6_get_dsfield(ipv6_hdr(skb))
				& ~INET_ECN_MASK;
			अवरोध;
		शेष:
			skb->tc_index = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (TC_H_MAJ(skb->priority) == sch->handle)
		skb->tc_index = TC_H_MIN(skb->priority);
	अन्यथा अणु
		काष्ठा tcf_result res;
		काष्ठा tcf_proto *fl = rcu_dereference_bh(p->filter_list);
		पूर्णांक result = tcf_classअगरy(skb, fl, &res, false);

		pr_debug("result %d class 0x%04x\n", result, res.classid);

		चयन (result) अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_TRAP:
			__qdisc_drop(skb, to_मुक्त);
			वापस NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;

		हाल TC_ACT_SHOT:
			जाओ drop;
#पूर्ण_अगर
		हाल TC_ACT_OK:
			skb->tc_index = TC_H_MIN(res.classid);
			अवरोध;

		शेष:
			अगर (p->शेष_index != NO_DEFAULT_INDEX)
				skb->tc_index = p->शेष_index;
			अवरोध;
		पूर्ण
	पूर्ण

	err = qdisc_enqueue(skb, p->q, to_मुक्त);
	अगर (err != NET_XMIT_SUCCESS) अणु
		अगर (net_xmit_drop_count(err))
			qdisc_qstats_drop(sch);
		वापस err;
	पूर्ण

	sch->qstats.backlog += len;
	sch->q.qlen++;

	वापस NET_XMIT_SUCCESS;

drop:
	qdisc_drop(skb, sch, to_मुक्त);
	वापस NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
पूर्ण

अटल काष्ठा sk_buff *dsmark_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	काष्ठा sk_buff *skb;
	u32 index;

	pr_debug("%s(sch %p,[qdisc %p])\n", __func__, sch, p);

	skb = qdisc_dequeue_peeked(p->q);
	अगर (skb == शून्य)
		वापस शून्य;

	qdisc_bstats_update(sch, skb);
	qdisc_qstats_backlog_dec(sch, skb);
	sch->q.qlen--;

	index = skb->tc_index & (p->indices - 1);
	pr_debug("index %d->%d\n", skb->tc_index, index);

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		ipv4_change_dsfield(ip_hdr(skb), p->mv[index].mask,
				    p->mv[index].value);
			अवरोध;
	हाल htons(ETH_P_IPV6):
		ipv6_change_dsfield(ipv6_hdr(skb), p->mv[index].mask,
				    p->mv[index].value);
			अवरोध;
	शेष:
		/*
		 * Only complain अगर a change was actually attempted.
		 * This way, we can send non-IP traffic through dsmark
		 * and करोn't need yet another qdisc as a bypass.
		 */
		अगर (p->mv[index].mask != 0xff || p->mv[index].value)
			pr_warn("%s: unsupported protocol %d\n",
				__func__, ntohs(skb_protocol(skb, true)));
		अवरोध;
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *dsmark_peek(काष्ठा Qdisc *sch)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);

	pr_debug("%s(sch %p,[qdisc %p])\n", __func__, sch, p);

	वापस p->q->ops->peek(p->q);
पूर्ण

अटल पूर्णांक dsmark_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	काष्ठा nlattr *tb[TCA_DSMARK_MAX + 1];
	पूर्णांक err = -EINVAL;
	u32 शेष_index = NO_DEFAULT_INDEX;
	u16 indices;
	पूर्णांक i;

	pr_debug("%s(sch %p,[qdisc %p],opt %p)\n", __func__, sch, p, opt);

	अगर (!opt)
		जाओ errout;

	err = tcf_block_get(&p->block, &p->filter_list, sch, extack);
	अगर (err)
		वापस err;

	err = nla_parse_nested_deprecated(tb, TCA_DSMARK_MAX, opt,
					  dsmark_policy, शून्य);
	अगर (err < 0)
		जाओ errout;

	err = -EINVAL;
	अगर (!tb[TCA_DSMARK_INDICES])
		जाओ errout;
	indices = nla_get_u16(tb[TCA_DSMARK_INDICES]);

	अगर (hweight32(indices) != 1)
		जाओ errout;

	अगर (tb[TCA_DSMARK_DEFAULT_INDEX])
		शेष_index = nla_get_u16(tb[TCA_DSMARK_DEFAULT_INDEX]);

	अगर (indices <= DSMARK_EMBEDDED_SZ)
		p->mv = p->embedded;
	अन्यथा
		p->mv = kदो_स्मृति_array(indices, माप(*p->mv), GFP_KERNEL);
	अगर (!p->mv) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण
	क्रम (i = 0; i < indices; i++) अणु
		p->mv[i].mask = 0xff;
		p->mv[i].value = 0;
	पूर्ण
	p->indices = indices;
	p->शेष_index = शेष_index;
	p->set_tc_index = nla_get_flag(tb[TCA_DSMARK_SET_TC_INDEX]);

	p->q = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops, sch->handle,
				 शून्य);
	अगर (p->q == शून्य)
		p->q = &noop_qdisc;
	अन्यथा
		qdisc_hash_add(p->q, true);

	pr_debug("%s: qdisc %p\n", __func__, p->q);

	err = 0;
errout:
	वापस err;
पूर्ण

अटल व्योम dsmark_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);

	pr_debug("%s(sch %p,[qdisc %p])\n", __func__, sch, p);
	अगर (p->q)
		qdisc_reset(p->q);
	sch->qstats.backlog = 0;
	sch->q.qlen = 0;
पूर्ण

अटल व्योम dsmark_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);

	pr_debug("%s(sch %p,[qdisc %p])\n", __func__, sch, p);

	tcf_block_put(p->block);
	qdisc_put(p->q);
	अगर (p->mv != p->embedded)
		kमुक्त(p->mv);
पूर्ण

अटल पूर्णांक dsmark_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			     काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	काष्ठा nlattr *opts = शून्य;

	pr_debug("%s(sch %p,[qdisc %p],class %ld\n", __func__, sch, p, cl);

	अगर (!dsmark_valid_index(p, cl))
		वापस -EINVAL;

	tcm->tcm_handle = TC_H_MAKE(TC_H_MAJ(sch->handle), cl - 1);
	tcm->tcm_info = p->q->handle;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, TCA_DSMARK_MASK, p->mv[cl - 1].mask) ||
	    nla_put_u8(skb, TCA_DSMARK_VALUE, p->mv[cl - 1].value))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक dsmark_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	काष्ठा dsmark_qdisc_data *p = qdisc_priv(sch);
	काष्ठा nlattr *opts = शून्य;

	opts = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (opts == शून्य)
		जाओ nla_put_failure;
	अगर (nla_put_u16(skb, TCA_DSMARK_INDICES, p->indices))
		जाओ nla_put_failure;

	अगर (p->शेष_index != NO_DEFAULT_INDEX &&
	    nla_put_u16(skb, TCA_DSMARK_DEFAULT_INDEX, p->शेष_index))
		जाओ nla_put_failure;

	अगर (p->set_tc_index &&
	    nla_put_flag(skb, TCA_DSMARK_SET_TC_INDEX))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops dsmark_class_ops = अणु
	.graft		=	dsmark_graft,
	.leaf		=	dsmark_leaf,
	.find		=	dsmark_find,
	.change		=	dsmark_change,
	.delete		=	dsmark_delete,
	.walk		=	dsmark_walk,
	.tcf_block	=	dsmark_tcf_block,
	.bind_tcf	=	dsmark_bind_filter,
	.unbind_tcf	=	dsmark_unbind_filter,
	.dump		=	dsmark_dump_class,
पूर्ण;

अटल काष्ठा Qdisc_ops dsmark_qdisc_ops __पढ़ो_mostly = अणु
	.next		=	शून्य,
	.cl_ops		=	&dsmark_class_ops,
	.id		=	"dsmark",
	.priv_size	=	माप(काष्ठा dsmark_qdisc_data),
	.enqueue	=	dsmark_enqueue,
	.dequeue	=	dsmark_dequeue,
	.peek		=	dsmark_peek,
	.init		=	dsmark_init,
	.reset		=	dsmark_reset,
	.destroy	=	dsmark_destroy,
	.change		=	शून्य,
	.dump		=	dsmark_dump,
	.owner		=	THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init dsmark_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&dsmark_qdisc_ops);
पूर्ण

अटल व्योम __निकास dsmark_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&dsmark_qdisc_ops);
पूर्ण

module_init(dsmark_module_init)
module_निकास(dsmark_module_निकास)

MODULE_LICENSE("GPL");
