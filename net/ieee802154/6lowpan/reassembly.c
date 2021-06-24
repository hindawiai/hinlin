<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*	6LoWPAN fragment reassembly
 *
 *	Authors:
 *	Alexander Aring		<aar@pengutronix.de>
 *
 *	Based on: net/ipv6/reassembly.c
 */

#घोषणा pr_fmt(fmt) "6LoWPAN: " fmt

#समावेश <linux/net.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jhash.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश <net/ieee802154_netdev.h>
#समावेश <net/6lowpan.h>
#समावेश <net/ipv6_frag.h>
#समावेश <net/inet_frag.h>
#समावेश <net/ip.h>

#समावेश "6lowpan_i.h"

अटल स्थिर अक्षर lowpan_frags_cache_name[] = "lowpan-frags";

अटल काष्ठा inet_frags lowpan_frags;

अटल पूर्णांक lowpan_frag_reयंत्र(काष्ठा lowpan_frag_queue *fq, काष्ठा sk_buff *skb,
			     काष्ठा sk_buff *prev,  काष्ठा net_device *ldev);

अटल व्योम lowpan_frag_init(काष्ठा inet_frag_queue *q, स्थिर व्योम *a)
अणु
	स्थिर काष्ठा frag_lowpan_compare_key *key = a;

	BUILD_BUG_ON(माप(*key) > माप(q->key));
	स_नकल(&q->key, key, माप(*key));
पूर्ण

अटल व्योम lowpan_frag_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_frag_queue *frag = from_समयr(frag, t, समयr);
	काष्ठा frag_queue *fq;

	fq = container_of(frag, काष्ठा frag_queue, q);

	spin_lock(&fq->q.lock);

	अगर (fq->q.flags & INET_FRAG_COMPLETE)
		जाओ out;

	inet_frag_समाप्त(&fq->q);
out:
	spin_unlock(&fq->q.lock);
	inet_frag_put(&fq->q);
पूर्ण

अटल अंतरभूत काष्ठा lowpan_frag_queue *
fq_find(काष्ठा net *net, स्थिर काष्ठा lowpan_802154_cb *cb,
	स्थिर काष्ठा ieee802154_addr *src,
	स्थिर काष्ठा ieee802154_addr *dst)
अणु
	काष्ठा netns_ieee802154_lowpan *ieee802154_lowpan =
		net_ieee802154_lowpan(net);
	काष्ठा frag_lowpan_compare_key key = अणुपूर्ण;
	काष्ठा inet_frag_queue *q;

	key.tag = cb->d_tag;
	key.d_size = cb->d_size;
	key.src = *src;
	key.dst = *dst;

	q = inet_frag_find(ieee802154_lowpan->fqdir, &key);
	अगर (!q)
		वापस शून्य;

	वापस container_of(q, काष्ठा lowpan_frag_queue, q);
पूर्ण

अटल पूर्णांक lowpan_frag_queue(काष्ठा lowpan_frag_queue *fq,
			     काष्ठा sk_buff *skb, u8 frag_type)
अणु
	काष्ठा sk_buff *prev_tail;
	काष्ठा net_device *ldev;
	पूर्णांक end, offset, err;

	/* inet_frag_queue_* functions use skb->cb; see काष्ठा ipfrag_skb_cb
	 * in inet_fragment.c
	 */
	BUILD_BUG_ON(माप(काष्ठा lowpan_802154_cb) > माप(काष्ठा inet_skb_parm));
	BUILD_BUG_ON(माप(काष्ठा lowpan_802154_cb) > माप(काष्ठा inet6_skb_parm));

	अगर (fq->q.flags & INET_FRAG_COMPLETE)
		जाओ err;

	offset = lowpan_802154_cb(skb)->d_offset << 3;
	end = lowpan_802154_cb(skb)->d_size;

	/* Is this the final fragment? */
	अगर (offset + skb->len == end) अणु
		/* If we alपढ़ोy have some bits beyond end
		 * or have dअगरferent end, the segment is corrupted.
		 */
		अगर (end < fq->q.len ||
		    ((fq->q.flags & INET_FRAG_LAST_IN) && end != fq->q.len))
			जाओ err;
		fq->q.flags |= INET_FRAG_LAST_IN;
		fq->q.len = end;
	पूर्ण अन्यथा अणु
		अगर (end > fq->q.len) अणु
			/* Some bits beyond end -> corruption. */
			अगर (fq->q.flags & INET_FRAG_LAST_IN)
				जाओ err;
			fq->q.len = end;
		पूर्ण
	पूर्ण

	ldev = skb->dev;
	अगर (ldev)
		skb->dev = शून्य;
	barrier();

	prev_tail = fq->q.fragments_tail;
	err = inet_frag_queue_insert(&fq->q, skb, offset, end);
	अगर (err)
		जाओ err;

	fq->q.stamp = skb->tstamp;
	अगर (frag_type == LOWPAN_DISPATCH_FRAG1)
		fq->q.flags |= INET_FRAG_FIRST_IN;

	fq->q.meat += skb->len;
	add_frag_mem_limit(fq->q.fqdir, skb->truesize);

	अगर (fq->q.flags == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    fq->q.meat == fq->q.len) अणु
		पूर्णांक res;
		अचिन्हित दीर्घ orefdst = skb->_skb_refdst;

		skb->_skb_refdst = 0UL;
		res = lowpan_frag_reयंत्र(fq, skb, prev_tail, ldev);
		skb->_skb_refdst = orefdst;
		वापस res;
	पूर्ण
	skb_dst_drop(skb);

	वापस -1;
err:
	kमुक्त_skb(skb);
	वापस -1;
पूर्ण

/*	Check अगर this packet is complete.
 *
 *	It is called with locked fq, and caller must check that
 *	queue is eligible क्रम reassembly i.e. it is not COMPLETE,
 *	the last and the first frames arrived and all the bits are here.
 */
अटल पूर्णांक lowpan_frag_reयंत्र(काष्ठा lowpan_frag_queue *fq, काष्ठा sk_buff *skb,
			     काष्ठा sk_buff *prev_tail, काष्ठा net_device *ldev)
अणु
	व्योम *reयंत्र_data;

	inet_frag_समाप्त(&fq->q);

	reयंत्र_data = inet_frag_reयंत्र_prepare(&fq->q, skb, prev_tail);
	अगर (!reयंत्र_data)
		जाओ out_oom;
	inet_frag_reयंत्र_finish(&fq->q, skb, reयंत्र_data, false);

	skb->dev = ldev;
	skb->tstamp = fq->q.stamp;
	fq->q.rb_fragments = RB_ROOT;
	fq->q.fragments_tail = शून्य;
	fq->q.last_run_head = शून्य;

	वापस 1;
out_oom:
	net_dbg_ratelimited("lowpan_frag_reasm: no memory for reassembly\n");
	वापस -1;
पूर्ण

अटल पूर्णांक lowpan_frag_rx_handlers_result(काष्ठा sk_buff *skb,
					  lowpan_rx_result res)
अणु
	चयन (res) अणु
	हाल RX_QUEUED:
		वापस NET_RX_SUCCESS;
	हाल RX_CONTINUE:
		/* nobody cared about this packet */
		net_warn_ratelimited("%s: received unknown dispatch\n",
				     __func__);

		fallthrough;
	शेष:
		/* all others failure */
		वापस NET_RX_DROP;
	पूर्ण
पूर्ण

अटल lowpan_rx_result lowpan_frag_rx_h_iphc(काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (!lowpan_is_iphc(*skb_network_header(skb)))
		वापस RX_CONTINUE;

	ret = lowpan_iphc_decompress(skb);
	अगर (ret < 0)
		वापस RX_DROP;

	वापस RX_QUEUED;
पूर्ण

अटल पूर्णांक lowpan_invoke_frag_rx_handlers(काष्ठा sk_buff *skb)
अणु
	lowpan_rx_result res;

#घोषणा CALL_RXH(rxh)			\
	करो अणु				\
		res = rxh(skb);	\
		अगर (res != RX_CONTINUE)	\
			जाओ rxh_next;	\
	पूर्ण जबतक (0)

	/* likely at first */
	CALL_RXH(lowpan_frag_rx_h_iphc);
	CALL_RXH(lowpan_rx_h_ipv6);

rxh_next:
	वापस lowpan_frag_rx_handlers_result(skb, res);
#अघोषित CALL_RXH
पूर्ण

#घोषणा LOWPAN_FRAG_DGRAM_SIZE_HIGH_MASK	0x07
#घोषणा LOWPAN_FRAG_DGRAM_SIZE_HIGH_SHIFT	8

अटल पूर्णांक lowpan_get_cb(काष्ठा sk_buff *skb, u8 frag_type,
			 काष्ठा lowpan_802154_cb *cb)
अणु
	bool fail;
	u8 high = 0, low = 0;
	__be16 d_tag = 0;

	fail = lowpan_fetch_skb(skb, &high, 1);
	fail |= lowpan_fetch_skb(skb, &low, 1);
	/* हटाओ the dispatch value and use first three bits as high value
	 * क्रम the datagram size
	 */
	cb->d_size = (high & LOWPAN_FRAG_DGRAM_SIZE_HIGH_MASK) <<
		LOWPAN_FRAG_DGRAM_SIZE_HIGH_SHIFT | low;
	fail |= lowpan_fetch_skb(skb, &d_tag, 2);
	cb->d_tag = ntohs(d_tag);

	अगर (frag_type == LOWPAN_DISPATCH_FRAGN) अणु
		fail |= lowpan_fetch_skb(skb, &cb->d_offset, 1);
	पूर्ण अन्यथा अणु
		skb_reset_network_header(skb);
		cb->d_offset = 0;
		/* check अगर datagram_size has ipv6hdr on FRAG1 */
		fail |= cb->d_size < माप(काष्ठा ipv6hdr);
		/* check अगर we can dereference the dispatch value */
		fail |= !skb->len;
	पूर्ण

	अगर (unlikely(fail))
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक lowpan_frag_rcv(काष्ठा sk_buff *skb, u8 frag_type)
अणु
	काष्ठा lowpan_frag_queue *fq;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा lowpan_802154_cb *cb = lowpan_802154_cb(skb);
	काष्ठा ieee802154_hdr hdr = अणुपूर्ण;
	पूर्णांक err;

	अगर (ieee802154_hdr_peek_addrs(skb, &hdr) < 0)
		जाओ err;

	err = lowpan_get_cb(skb, frag_type, cb);
	अगर (err < 0)
		जाओ err;

	अगर (frag_type == LOWPAN_DISPATCH_FRAG1) अणु
		err = lowpan_invoke_frag_rx_handlers(skb);
		अगर (err == NET_RX_DROP)
			जाओ err;
	पूर्ण

	अगर (cb->d_size > IPV6_MIN_MTU) अणु
		net_warn_ratelimited("lowpan_frag_rcv: datagram size exceeds MTU\n");
		जाओ err;
	पूर्ण

	fq = fq_find(net, cb, &hdr.source, &hdr.dest);
	अगर (fq != शून्य) अणु
		पूर्णांक ret;

		spin_lock(&fq->q.lock);
		ret = lowpan_frag_queue(fq, skb, frag_type);
		spin_unlock(&fq->q.lock);

		inet_frag_put(&fq->q);
		वापस ret;
	पूर्ण

err:
	kमुक्त_skb(skb);
	वापस -1;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

अटल काष्ठा ctl_table lowpan_frags_ns_ctl_table[] = अणु
	अणु
		.procname	= "6lowpanfrag_high_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "6lowpanfrag_low_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "6lowpanfrag_time",
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* secret पूर्णांकerval has been deprecated */
अटल पूर्णांक lowpan_frags_secret_पूर्णांकerval_unused;
अटल काष्ठा ctl_table lowpan_frags_ctl_table[] = अणु
	अणु
		.procname	= "6lowpanfrag_secret_interval",
		.data		= &lowpan_frags_secret_पूर्णांकerval_unused,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __net_init lowpan_frags_ns_sysctl_रेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	काष्ठा ctl_table_header *hdr;
	काष्ठा netns_ieee802154_lowpan *ieee802154_lowpan =
		net_ieee802154_lowpan(net);

	table = lowpan_frags_ns_ctl_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(lowpan_frags_ns_ctl_table),
				GFP_KERNEL);
		अगर (table == शून्य)
			जाओ err_alloc;

		/* Don't export sysctls to unprivileged users */
		अगर (net->user_ns != &init_user_ns)
			table[0].procname = शून्य;
	पूर्ण

	table[0].data	= &ieee802154_lowpan->fqdir->high_thresh;
	table[0].extra1	= &ieee802154_lowpan->fqdir->low_thresh;
	table[1].data	= &ieee802154_lowpan->fqdir->low_thresh;
	table[1].extra2	= &ieee802154_lowpan->fqdir->high_thresh;
	table[2].data	= &ieee802154_lowpan->fqdir->समयout;

	hdr = रेजिस्टर_net_sysctl(net, "net/ieee802154/6lowpan", table);
	अगर (hdr == शून्य)
		जाओ err_reg;

	ieee802154_lowpan->sysctl.frags_hdr = hdr;
	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास lowpan_frags_ns_sysctl_unरेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा ctl_table *table;
	काष्ठा netns_ieee802154_lowpan *ieee802154_lowpan =
		net_ieee802154_lowpan(net);

	table = ieee802154_lowpan->sysctl.frags_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(ieee802154_lowpan->sysctl.frags_hdr);
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
पूर्ण

अटल काष्ठा ctl_table_header *lowpan_ctl_header;

अटल पूर्णांक __init lowpan_frags_sysctl_रेजिस्टर(व्योम)
अणु
	lowpan_ctl_header = रेजिस्टर_net_sysctl(&init_net,
						"net/ieee802154/6lowpan",
						lowpan_frags_ctl_table);
	वापस lowpan_ctl_header == शून्य ? -ENOMEM : 0;
पूर्ण

अटल व्योम lowpan_frags_sysctl_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(lowpan_ctl_header);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक lowpan_frags_ns_sysctl_रेजिस्टर(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम lowpan_frags_ns_sysctl_unरेजिस्टर(काष्ठा net *net)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __init lowpan_frags_sysctl_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम lowpan_frags_sysctl_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init lowpan_frags_init_net(काष्ठा net *net)
अणु
	काष्ठा netns_ieee802154_lowpan *ieee802154_lowpan =
		net_ieee802154_lowpan(net);
	पूर्णांक res;


	res = fqdir_init(&ieee802154_lowpan->fqdir, &lowpan_frags, net);
	अगर (res < 0)
		वापस res;

	ieee802154_lowpan->fqdir->high_thresh = IPV6_FRAG_HIGH_THRESH;
	ieee802154_lowpan->fqdir->low_thresh = IPV6_FRAG_LOW_THRESH;
	ieee802154_lowpan->fqdir->समयout = IPV6_FRAG_TIMEOUT;

	res = lowpan_frags_ns_sysctl_रेजिस्टर(net);
	अगर (res < 0)
		fqdir_निकास(ieee802154_lowpan->fqdir);
	वापस res;
पूर्ण

अटल व्योम __net_निकास lowpan_frags_pre_निकास_net(काष्ठा net *net)
अणु
	काष्ठा netns_ieee802154_lowpan *ieee802154_lowpan =
		net_ieee802154_lowpan(net);

	fqdir_pre_निकास(ieee802154_lowpan->fqdir);
पूर्ण

अटल व्योम __net_निकास lowpan_frags_निकास_net(काष्ठा net *net)
अणु
	काष्ठा netns_ieee802154_lowpan *ieee802154_lowpan =
		net_ieee802154_lowpan(net);

	lowpan_frags_ns_sysctl_unरेजिस्टर(net);
	fqdir_निकास(ieee802154_lowpan->fqdir);
पूर्ण

अटल काष्ठा pernet_operations lowpan_frags_ops = अणु
	.init		= lowpan_frags_init_net,
	.pre_निकास	= lowpan_frags_pre_निकास_net,
	.निकास		= lowpan_frags_निकास_net,
पूर्ण;

अटल u32 lowpan_key_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	वापस jhash2(data,
		      माप(काष्ठा frag_lowpan_compare_key) / माप(u32), seed);
पूर्ण

अटल u32 lowpan_obj_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा inet_frag_queue *fq = data;

	वापस jhash2((स्थिर u32 *)&fq->key,
		      माप(काष्ठा frag_lowpan_compare_key) / माप(u32), seed);
पूर्ण

अटल पूर्णांक lowpan_obj_cmpfn(काष्ठा rhashtable_compare_arg *arg, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा frag_lowpan_compare_key *key = arg->key;
	स्थिर काष्ठा inet_frag_queue *fq = ptr;

	वापस !!स_भेद(&fq->key, key, माप(*key));
पूर्ण

अटल स्थिर काष्ठा rhashtable_params lowpan_rhash_params = अणु
	.head_offset		= दुरत्व(काष्ठा inet_frag_queue, node),
	.hashfn			= lowpan_key_hashfn,
	.obj_hashfn		= lowpan_obj_hashfn,
	.obj_cmpfn		= lowpan_obj_cmpfn,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

पूर्णांक __init lowpan_net_frag_init(व्योम)
अणु
	पूर्णांक ret;

	lowpan_frags.स्थिरructor = lowpan_frag_init;
	lowpan_frags.deकाष्ठाor = शून्य;
	lowpan_frags.qsize = माप(काष्ठा frag_queue);
	lowpan_frags.frag_expire = lowpan_frag_expire;
	lowpan_frags.frags_cache_name = lowpan_frags_cache_name;
	lowpan_frags.rhash_params = lowpan_rhash_params;
	ret = inet_frags_init(&lowpan_frags);
	अगर (ret)
		जाओ out;

	ret = lowpan_frags_sysctl_रेजिस्टर();
	अगर (ret)
		जाओ err_sysctl;

	ret = रेजिस्टर_pernet_subsys(&lowpan_frags_ops);
	अगर (ret)
		जाओ err_pernet;
out:
	वापस ret;
err_pernet:
	lowpan_frags_sysctl_unरेजिस्टर();
err_sysctl:
	inet_frags_fini(&lowpan_frags);
	वापस ret;
पूर्ण

व्योम lowpan_net_frag_निकास(व्योम)
अणु
	lowpan_frags_sysctl_unरेजिस्टर();
	unरेजिस्टर_pernet_subsys(&lowpan_frags_ops);
	inet_frags_fini(&lowpan_frags);
पूर्ण
