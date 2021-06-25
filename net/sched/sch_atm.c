<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* net/sched/sch_aपंचांग.c - ATM VC selection "queueing discipline" */

/* Written 1998-2000 by Werner Almesberger, EPFL ICA */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांगclip.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/file.h>		/* क्रम fput */
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>

/*
 * The ATM queuing discipline provides a framework क्रम invoking classअगरiers
 * (aka "filters"), which in turn select classes of this queuing discipline.
 * Each class maps the flow(s) it is handling to a given VC. Multiple classes
 * may share the same VC.
 *
 * When creating a class, VCs are specअगरied by passing the number of the खोलो
 * socket descriptor by which the calling process references the VC. The kernel
 * keeps the VC खोलो at least until all classes using it are हटाओd.
 *
 * In this file, most functions are named aपंचांग_tc_* to aव्योम confusion with all
 * the aपंचांग_* in net/aपंचांग. This naming convention dअगरfers from what's used in the
 * rest of net/sched.
 *
 * Known bugs:
 *  - someबार messes up the IP stack
 *  - any manipulations besides the few operations described in the README, are
 *    untested and likely to crash the प्रणाली
 *  - should lock the flow जबतक there is data in the queue (?)
 */

#घोषणा VCC2FLOW(vcc) ((काष्ठा aपंचांग_flow_data *) ((vcc)->user_back))

काष्ठा aपंचांग_flow_data अणु
	काष्ठा Qdisc_class_common common;
	काष्ठा Qdisc		*q;	/* FIFO, TBF, etc. */
	काष्ठा tcf_proto __rcu	*filter_list;
	काष्ठा tcf_block	*block;
	काष्ठा aपंचांग_vcc		*vcc;	/* VCC; शून्य अगर VCC is बंदd */
	व्योम			(*old_pop)(काष्ठा aपंचांग_vcc *vcc,
					   काष्ठा sk_buff *skb); /* chaining */
	काष्ठा aपंचांग_qdisc_data	*parent;	/* parent qdisc */
	काष्ठा socket		*sock;		/* क्रम closing */
	पूर्णांक			ref;		/* reference count */
	काष्ठा gnet_stats_basic_packed	bstats;
	काष्ठा gnet_stats_queue	qstats;
	काष्ठा list_head	list;
	काष्ठा aपंचांग_flow_data	*excess;	/* flow क्रम excess traffic;
						   शून्य to set CLP instead */
	पूर्णांक			hdr_len;
	अचिन्हित अक्षर		hdr[];		/* header data; MUST BE LAST */
पूर्ण;

काष्ठा aपंचांग_qdisc_data अणु
	काष्ठा aपंचांग_flow_data	link;		/* unclassअगरied skbs go here */
	काष्ठा list_head	flows;		/* NB: "link" is also on this
						   list */
	काष्ठा tasklet_काष्ठा	task;		/* dequeue tasklet */
पूर्ण;

/* ------------------------- Class/flow operations ------------------------- */

अटल अंतरभूत काष्ठा aपंचांग_flow_data *lookup_flow(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow;

	list_क्रम_each_entry(flow, &p->flows, list) अणु
		अगर (flow->common.classid == classid)
			वापस flow;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक aपंचांग_tc_graft(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			काष्ठा Qdisc *new, काष्ठा Qdisc **old,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)arg;

	pr_debug("atm_tc_graft(sch %p,[qdisc %p],flow %p,new %p,old %p)\n",
		sch, p, flow, new, old);
	अगर (list_empty(&flow->list))
		वापस -EINVAL;
	अगर (!new)
		new = &noop_qdisc;
	*old = flow->q;
	flow->q = new;
	अगर (*old)
		qdisc_reset(*old);
	वापस 0;
पूर्ण

अटल काष्ठा Qdisc *aपंचांग_tc_leaf(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)cl;

	pr_debug("atm_tc_leaf(sch %p,flow %p)\n", sch, flow);
	वापस flow ? flow->q : शून्य;
पूर्ण

अटल अचिन्हित दीर्घ aपंचांग_tc_find(काष्ठा Qdisc *sch, u32 classid)
अणु
	काष्ठा aपंचांग_qdisc_data *p __maybe_unused = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow;

	pr_debug("%s(sch %p,[qdisc %p],classid %x)\n", __func__, sch, p, classid);
	flow = lookup_flow(sch, classid);
	pr_debug("%s: flow %p\n", __func__, flow);
	वापस (अचिन्हित दीर्घ)flow;
पूर्ण

अटल अचिन्हित दीर्घ aपंचांग_tc_bind_filter(काष्ठा Qdisc *sch,
					अचिन्हित दीर्घ parent, u32 classid)
अणु
	काष्ठा aपंचांग_qdisc_data *p __maybe_unused = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow;

	pr_debug("%s(sch %p,[qdisc %p],classid %x)\n", __func__, sch, p, classid);
	flow = lookup_flow(sch, classid);
	अगर (flow)
		flow->ref++;
	pr_debug("%s: flow %p\n", __func__, flow);
	वापस (अचिन्हित दीर्घ)flow;
पूर्ण

/*
 * aपंचांग_tc_put handles all deकाष्ठाions, including the ones that are explicitly
 * requested (aपंचांग_tc_destroy, etc.). The assumption here is that we never drop
 * anything that still seems to be in use.
 */
अटल व्योम aपंचांग_tc_put(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)cl;

	pr_debug("atm_tc_put(sch %p,[qdisc %p],flow %p)\n", sch, p, flow);
	अगर (--flow->ref)
		वापस;
	pr_debug("atm_tc_put: destroying\n");
	list_del_init(&flow->list);
	pr_debug("atm_tc_put: qdisc %p\n", flow->q);
	qdisc_put(flow->q);
	tcf_block_put(flow->block);
	अगर (flow->sock) अणु
		pr_debug("atm_tc_put: f_count %ld\n",
			file_count(flow->sock->file));
		flow->vcc->pop = flow->old_pop;
		sockfd_put(flow->sock);
	पूर्ण
	अगर (flow->excess)
		aपंचांग_tc_put(sch, (अचिन्हित दीर्घ)flow->excess);
	अगर (flow != &p->link)
		kमुक्त(flow);
	/*
	 * If flow == &p->link, the qdisc no दीर्घer works at this poपूर्णांक and
	 * needs to be हटाओd. (By the caller of aपंचांग_tc_put.)
	 */
पूर्ण

अटल व्योम sch_aपंचांग_pop(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	काष्ठा aपंचांग_qdisc_data *p = VCC2FLOW(vcc)->parent;

	pr_debug("sch_atm_pop(vcc %p,skb %p,[qdisc %p])\n", vcc, skb, p);
	VCC2FLOW(vcc)->old_pop(vcc, skb);
	tasklet_schedule(&p->task);
पूर्ण

अटल स्थिर u8 llc_oui_ip[] = अणु
	0xaa,			/* DSAP: non-ISO */
	0xaa,			/* SSAP: non-ISO */
	0x03,			/* Ctrl: Unnumbered Inक्रमmation Command PDU */
	0x00,			/* OUI: EtherType */
	0x00, 0x00,
	0x08, 0x00
पूर्ण;				/* Ethertype IP (0800) */

अटल स्थिर काष्ठा nla_policy aपंचांग_policy[TCA_ATM_MAX + 1] = अणु
	[TCA_ATM_FD]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_ATM_EXCESS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक aपंचांग_tc_change(काष्ठा Qdisc *sch, u32 classid, u32 parent,
			 काष्ठा nlattr **tca, अचिन्हित दीर्घ *arg,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)*arg;
	काष्ठा aपंचांग_flow_data *excess = शून्य;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_ATM_MAX + 1];
	काष्ठा socket *sock;
	पूर्णांक fd, error, hdr_len;
	व्योम *hdr;

	pr_debug("atm_tc_change(sch %p,[qdisc %p],classid %x,parent %x,"
		"flow %p,opt %p)\n", sch, p, classid, parent, flow, opt);
	/*
	 * The concept of parents करोesn't apply क्रम this qdisc.
	 */
	अगर (parent && parent != TC_H_ROOT && parent != sch->handle)
		वापस -EINVAL;
	/*
	 * ATM classes cannot be changed. In order to change properties of the
	 * ATM connection, that socket needs to be modअगरied directly (via the
	 * native ATM API. In order to send a flow to a dअगरferent VC, the old
	 * class needs to be हटाओd and a new one added. (This may be changed
	 * later.)
	 */
	अगर (flow)
		वापस -EBUSY;
	अगर (opt == शून्य)
		वापस -EINVAL;

	error = nla_parse_nested_deprecated(tb, TCA_ATM_MAX, opt, aपंचांग_policy,
					    शून्य);
	अगर (error < 0)
		वापस error;

	अगर (!tb[TCA_ATM_FD])
		वापस -EINVAL;
	fd = nla_get_u32(tb[TCA_ATM_FD]);
	pr_debug("atm_tc_change: fd %d\n", fd);
	अगर (tb[TCA_ATM_HDR]) अणु
		hdr_len = nla_len(tb[TCA_ATM_HDR]);
		hdr = nla_data(tb[TCA_ATM_HDR]);
	पूर्ण अन्यथा अणु
		hdr_len = RFC1483LLC_LEN;
		hdr = शून्य;	/* शेष LLC/SNAP क्रम IP */
	पूर्ण
	अगर (!tb[TCA_ATM_EXCESS])
		excess = शून्य;
	अन्यथा अणु
		excess = (काष्ठा aपंचांग_flow_data *)
			aपंचांग_tc_find(sch, nla_get_u32(tb[TCA_ATM_EXCESS]));
		अगर (!excess)
			वापस -ENOENT;
	पूर्ण
	pr_debug("atm_tc_change: type %d, payload %d, hdr_len %d\n",
		 opt->nla_type, nla_len(opt), hdr_len);
	sock = sockfd_lookup(fd, &error);
	अगर (!sock)
		वापस error;	/* f_count++ */
	pr_debug("atm_tc_change: f_count %ld\n", file_count(sock->file));
	अगर (sock->ops->family != PF_ATMSVC && sock->ops->family != PF_ATMPVC) अणु
		error = -EPROTOTYPE;
		जाओ err_out;
	पूर्ण
	/* @@@ should check अगर the socket is really operational or we'll crash
	   on vcc->send */
	अगर (classid) अणु
		अगर (TC_H_MAJ(classid ^ sch->handle)) अणु
			pr_debug("atm_tc_change: classid mismatch\n");
			error = -EINVAL;
			जाओ err_out;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		अचिन्हित दीर्घ cl;

		क्रम (i = 1; i < 0x8000; i++) अणु
			classid = TC_H_MAKE(sch->handle, 0x8000 | i);
			cl = aपंचांग_tc_find(sch, classid);
			अगर (!cl)
				अवरोध;
		पूर्ण
	पूर्ण
	pr_debug("atm_tc_change: new id %x\n", classid);
	flow = kzalloc(माप(काष्ठा aपंचांग_flow_data) + hdr_len, GFP_KERNEL);
	pr_debug("atm_tc_change: flow %p\n", flow);
	अगर (!flow) अणु
		error = -ENOBUFS;
		जाओ err_out;
	पूर्ण

	error = tcf_block_get(&flow->block, &flow->filter_list, sch,
			      extack);
	अगर (error) अणु
		kमुक्त(flow);
		जाओ err_out;
	पूर्ण

	flow->q = qdisc_create_dflt(sch->dev_queue, &pfअगरo_qdisc_ops, classid,
				    extack);
	अगर (!flow->q)
		flow->q = &noop_qdisc;
	pr_debug("atm_tc_change: qdisc %p\n", flow->q);
	flow->sock = sock;
	flow->vcc = ATM_SD(sock);	/* speedup */
	flow->vcc->user_back = flow;
	pr_debug("atm_tc_change: vcc %p\n", flow->vcc);
	flow->old_pop = flow->vcc->pop;
	flow->parent = p;
	flow->vcc->pop = sch_aपंचांग_pop;
	flow->common.classid = classid;
	flow->ref = 1;
	flow->excess = excess;
	list_add(&flow->list, &p->link.list);
	flow->hdr_len = hdr_len;
	अगर (hdr)
		स_नकल(flow->hdr, hdr, hdr_len);
	अन्यथा
		स_नकल(flow->hdr, llc_oui_ip, माप(llc_oui_ip));
	*arg = (अचिन्हित दीर्घ)flow;
	वापस 0;
err_out:
	sockfd_put(sock);
	वापस error;
पूर्ण

अटल पूर्णांक aपंचांग_tc_delete(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)arg;

	pr_debug("atm_tc_delete(sch %p,[qdisc %p],flow %p)\n", sch, p, flow);
	अगर (list_empty(&flow->list))
		वापस -EINVAL;
	अगर (rcu_access_poपूर्णांकer(flow->filter_list) || flow == &p->link)
		वापस -EBUSY;
	/*
	 * Reference count must be 2: one क्रम "keepalive" (set at class
	 * creation), and one क्रम the reference held when calling delete.
	 */
	अगर (flow->ref < 2) अणु
		pr_err("atm_tc_delete: flow->ref == %d\n", flow->ref);
		वापस -EINVAL;
	पूर्ण
	अगर (flow->ref > 2)
		वापस -EBUSY;	/* catch references via excess, etc. */
	aपंचांग_tc_put(sch, arg);
	वापस 0;
पूर्ण

अटल व्योम aपंचांग_tc_walk(काष्ठा Qdisc *sch, काष्ठा qdisc_walker *walker)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow;

	pr_debug("atm_tc_walk(sch %p,[qdisc %p],walker %p)\n", sch, p, walker);
	अगर (walker->stop)
		वापस;
	list_क्रम_each_entry(flow, &p->flows, list) अणु
		अगर (walker->count >= walker->skip &&
		    walker->fn(sch, (अचिन्हित दीर्घ)flow, walker) < 0) अणु
			walker->stop = 1;
			अवरोध;
		पूर्ण
		walker->count++;
	पूर्ण
पूर्ण

अटल काष्ठा tcf_block *aपंचांग_tc_tcf_block(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
					  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)cl;

	pr_debug("atm_tc_find_tcf(sch %p,[qdisc %p],flow %p)\n", sch, p, flow);
	वापस flow ? flow->block : p->link.block;
पूर्ण

/* --------------------------- Qdisc operations ---------------------------- */

अटल पूर्णांक aपंचांग_tc_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			  काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow;
	काष्ठा tcf_result res;
	पूर्णांक result;
	पूर्णांक ret = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;

	pr_debug("atm_tc_enqueue(skb %p,sch %p,[qdisc %p])\n", skb, sch, p);
	result = TC_ACT_OK;	/* be nice to gcc */
	flow = शून्य;
	अगर (TC_H_MAJ(skb->priority) != sch->handle ||
	    !(flow = (काष्ठा aपंचांग_flow_data *)aपंचांग_tc_find(sch, skb->priority))) अणु
		काष्ठा tcf_proto *fl;

		list_क्रम_each_entry(flow, &p->flows, list) अणु
			fl = rcu_dereference_bh(flow->filter_list);
			अगर (fl) अणु
				result = tcf_classअगरy(skb, fl, &res, true);
				अगर (result < 0)
					जारी;
				flow = (काष्ठा aपंचांग_flow_data *)res.class;
				अगर (!flow)
					flow = lookup_flow(sch, res.classid);
				जाओ करोne;
			पूर्ण
		पूर्ण
		flow = शून्य;
करोne:
		;
	पूर्ण
	अगर (!flow) अणु
		flow = &p->link;
	पूर्ण अन्यथा अणु
		अगर (flow->vcc)
			ATM_SKB(skb)->aपंचांग_options = flow->vcc->aपंचांग_options;
		/*@@@ looks good ... but it's not supposed to work :-) */
#अगर_घोषित CONFIG_NET_CLS_ACT
		चयन (result) अणु
		हाल TC_ACT_QUEUED:
		हाल TC_ACT_STOLEN:
		हाल TC_ACT_TRAP:
			__qdisc_drop(skb, to_मुक्त);
			वापस NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
		हाल TC_ACT_SHOT:
			__qdisc_drop(skb, to_मुक्त);
			जाओ drop;
		हाल TC_ACT_RECLASSIFY:
			अगर (flow->excess)
				flow = flow->excess;
			अन्यथा
				ATM_SKB(skb)->aपंचांग_options |= ATM_ATMOPT_CLP;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	ret = qdisc_enqueue(skb, flow->q, to_मुक्त);
	अगर (ret != NET_XMIT_SUCCESS) अणु
drop: __maybe_unused
		अगर (net_xmit_drop_count(ret)) अणु
			qdisc_qstats_drop(sch);
			अगर (flow)
				flow->qstats.drops++;
		पूर्ण
		वापस ret;
	पूर्ण
	/*
	 * Okay, this may seem weird. We pretend we've dropped the packet अगर
	 * it goes via ATM. The reason क्रम this is that the outer qdisc
	 * expects to be able to q->dequeue the packet later on अगर we वापस
	 * success at this place. Also, sch->q.qdisc needs to reflect whether
	 * there is a packet egligible क्रम dequeuing or not. Note that the
	 * statistics of the outer qdisc are necessarily wrong because of all
	 * this. There's currently no correct solution क्रम this.
	 */
	अगर (flow == &p->link) अणु
		sch->q.qlen++;
		वापस NET_XMIT_SUCCESS;
	पूर्ण
	tasklet_schedule(&p->task);
	वापस NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
पूर्ण

/*
 * Dequeue packets and send them over ATM. Note that we quite deliberately
 * aव्योम checking net_device's flow control here, simply because sch_aपंचांग
 * uses its own channels, which have nothing to करो with any CLIP/LANE/or
 * non-ATM पूर्णांकerfaces.
 */

अटल व्योम sch_aपंचांग_dequeue(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा aपंचांग_qdisc_data *p = from_tasklet(p, t, task);
	काष्ठा Qdisc *sch = qdisc_from_priv(p);
	काष्ठा aपंचांग_flow_data *flow;
	काष्ठा sk_buff *skb;

	pr_debug("sch_atm_dequeue(sch %p,[qdisc %p])\n", sch, p);
	list_क्रम_each_entry(flow, &p->flows, list) अणु
		अगर (flow == &p->link)
			जारी;
		/*
		 * If traffic is properly shaped, this won't generate nasty
		 * little bursts. Otherwise, it may ... (but that's okay)
		 */
		जबतक ((skb = flow->q->ops->peek(flow->q))) अणु
			अगर (!aपंचांग_may_send(flow->vcc, skb->truesize))
				अवरोध;

			skb = qdisc_dequeue_peeked(flow->q);
			अगर (unlikely(!skb))
				अवरोध;

			qdisc_bstats_update(sch, skb);
			bstats_update(&flow->bstats, skb);
			pr_debug("atm_tc_dequeue: sending on class %p\n", flow);
			/* हटाओ any LL header somebody अन्यथा has attached */
			skb_pull(skb, skb_network_offset(skb));
			अगर (skb_headroom(skb) < flow->hdr_len) अणु
				काष्ठा sk_buff *new;

				new = skb_पुनः_स्मृति_headroom(skb, flow->hdr_len);
				dev_kमुक्त_skb(skb);
				अगर (!new)
					जारी;
				skb = new;
			पूर्ण
			pr_debug("sch_atm_dequeue: ip %p, data %p\n",
				 skb_network_header(skb), skb->data);
			ATM_SKB(skb)->vcc = flow->vcc;
			स_नकल(skb_push(skb, flow->hdr_len), flow->hdr,
			       flow->hdr_len);
			refcount_add(skb->truesize,
				   &sk_aपंचांग(flow->vcc)->sk_wmem_alloc);
			/* aपंचांग.aपंचांग_options are alपढ़ोy set by aपंचांग_tc_enqueue */
			flow->vcc->send(flow->vcc, skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *aपंचांग_tc_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा sk_buff *skb;

	pr_debug("atm_tc_dequeue(sch %p,[qdisc %p])\n", sch, p);
	tasklet_schedule(&p->task);
	skb = qdisc_dequeue_peeked(p->link.q);
	अगर (skb)
		sch->q.qlen--;
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *aपंचांग_tc_peek(काष्ठा Qdisc *sch)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);

	pr_debug("atm_tc_peek(sch %p,[qdisc %p])\n", sch, p);

	वापस p->link.q->ops->peek(p->link.q);
पूर्ण

अटल पूर्णांक aपंचांग_tc_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	पूर्णांक err;

	pr_debug("atm_tc_init(sch %p,[qdisc %p],opt %p)\n", sch, p, opt);
	INIT_LIST_HEAD(&p->flows);
	INIT_LIST_HEAD(&p->link.list);
	list_add(&p->link.list, &p->flows);
	p->link.q = qdisc_create_dflt(sch->dev_queue,
				      &pfअगरo_qdisc_ops, sch->handle, extack);
	अगर (!p->link.q)
		p->link.q = &noop_qdisc;
	pr_debug("atm_tc_init: link (%p) qdisc %p\n", &p->link, p->link.q);
	p->link.vcc = शून्य;
	p->link.sock = शून्य;
	p->link.common.classid = sch->handle;
	p->link.ref = 1;

	err = tcf_block_get(&p->link.block, &p->link.filter_list, sch,
			    extack);
	अगर (err)
		वापस err;

	tasklet_setup(&p->task, sch_aपंचांग_dequeue);
	वापस 0;
पूर्ण

अटल व्योम aपंचांग_tc_reset(काष्ठा Qdisc *sch)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow;

	pr_debug("atm_tc_reset(sch %p,[qdisc %p])\n", sch, p);
	list_क्रम_each_entry(flow, &p->flows, list)
		qdisc_reset(flow->q);
	sch->q.qlen = 0;
पूर्ण

अटल व्योम aपंचांग_tc_destroy(काष्ठा Qdisc *sch)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow, *पंचांगp;

	pr_debug("atm_tc_destroy(sch %p,[qdisc %p])\n", sch, p);
	list_क्रम_each_entry(flow, &p->flows, list) अणु
		tcf_block_put(flow->block);
		flow->block = शून्य;
	पूर्ण

	list_क्रम_each_entry_safe(flow, पंचांगp, &p->flows, list) अणु
		अगर (flow->ref > 1)
			pr_err("atm_destroy: %p->ref = %d\n", flow, flow->ref);
		aपंचांग_tc_put(sch, (अचिन्हित दीर्घ)flow);
	पूर्ण
	tasklet_समाप्त(&p->task);
पूर्ण

अटल पूर्णांक aपंचांग_tc_dump_class(काष्ठा Qdisc *sch, अचिन्हित दीर्घ cl,
			     काष्ठा sk_buff *skb, काष्ठा tcmsg *tcm)
अणु
	काष्ठा aपंचांग_qdisc_data *p = qdisc_priv(sch);
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)cl;
	काष्ठा nlattr *nest;

	pr_debug("atm_tc_dump_class(sch %p,[qdisc %p],flow %p,skb %p,tcm %p)\n",
		sch, p, flow, skb, tcm);
	अगर (list_empty(&flow->list))
		वापस -EINVAL;
	tcm->tcm_handle = flow->common.classid;
	tcm->tcm_info = flow->q->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put(skb, TCA_ATM_HDR, flow->hdr_len, flow->hdr))
		जाओ nla_put_failure;
	अगर (flow->vcc) अणु
		काष्ठा sockaddr_aपंचांगpvc pvc;
		पूर्णांक state;

		स_रखो(&pvc, 0, माप(pvc));
		pvc.sap_family = AF_ATMPVC;
		pvc.sap_addr.itf = flow->vcc->dev ? flow->vcc->dev->number : -1;
		pvc.sap_addr.vpi = flow->vcc->vpi;
		pvc.sap_addr.vci = flow->vcc->vci;
		अगर (nla_put(skb, TCA_ATM_ADDR, माप(pvc), &pvc))
			जाओ nla_put_failure;
		state = ATM_VF2VS(flow->vcc->flags);
		अगर (nla_put_u32(skb, TCA_ATM_STATE, state))
			जाओ nla_put_failure;
	पूर्ण
	अगर (flow->excess) अणु
		अगर (nla_put_u32(skb, TCA_ATM_EXCESS, flow->common.classid))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		अगर (nla_put_u32(skb, TCA_ATM_EXCESS, 0))
			जाओ nla_put_failure;
	पूर्ण
	वापस nla_nest_end(skb, nest);

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण
अटल पूर्णांक
aपंचांग_tc_dump_class_stats(काष्ठा Qdisc *sch, अचिन्हित दीर्घ arg,
			काष्ठा gnet_dump *d)
अणु
	काष्ठा aपंचांग_flow_data *flow = (काष्ठा aपंचांग_flow_data *)arg;

	अगर (gnet_stats_copy_basic(qdisc_root_sleeping_running(sch),
				  d, शून्य, &flow->bstats) < 0 ||
	    gnet_stats_copy_queue(d, शून्य, &flow->qstats, flow->q->q.qlen) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांग_tc_dump(काष्ठा Qdisc *sch, काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा Qdisc_class_ops aपंचांग_class_ops = अणु
	.graft		= aपंचांग_tc_graft,
	.leaf		= aपंचांग_tc_leaf,
	.find		= aपंचांग_tc_find,
	.change		= aपंचांग_tc_change,
	.delete		= aपंचांग_tc_delete,
	.walk		= aपंचांग_tc_walk,
	.tcf_block	= aपंचांग_tc_tcf_block,
	.bind_tcf	= aपंचांग_tc_bind_filter,
	.unbind_tcf	= aपंचांग_tc_put,
	.dump		= aपंचांग_tc_dump_class,
	.dump_stats	= aपंचांग_tc_dump_class_stats,
पूर्ण;

अटल काष्ठा Qdisc_ops aपंचांग_qdisc_ops __पढ़ो_mostly = अणु
	.cl_ops		= &aपंचांग_class_ops,
	.id		= "atm",
	.priv_size	= माप(काष्ठा aपंचांग_qdisc_data),
	.enqueue	= aपंचांग_tc_enqueue,
	.dequeue	= aपंचांग_tc_dequeue,
	.peek		= aपंचांग_tc_peek,
	.init		= aपंचांग_tc_init,
	.reset		= aपंचांग_tc_reset,
	.destroy	= aपंचांग_tc_destroy,
	.dump		= aपंचांग_tc_dump,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init aपंचांग_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&aपंचांग_qdisc_ops);
पूर्ण

अटल व्योम __निकास aपंचांग_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&aपंचांग_qdisc_ops);
पूर्ण

module_init(aपंचांग_init)
module_निकास(aपंचांग_निकास)
MODULE_LICENSE("GPL");
