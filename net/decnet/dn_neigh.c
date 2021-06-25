<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Neighbour Functions (Adjacency Database and
 *                                                        On-Ethernet Cache)
 *
 * Author:      Steve Whitehouse <SteveW@ACM.org>
 *
 *
 * Changes:
 *     Steve Whitehouse     : Fixed router listing routine
 *     Steve Whitehouse     : Added error_report functions
 *     Steve Whitehouse     : Added शेष router detection
 *     Steve Whitehouse     : Hop counts in outgoing messages
 *     Steve Whitehouse     : Fixed src/dst in outgoing messages so
 *                            क्रमwarding now stands a good chance of
 *                            working.
 *     Steve Whitehouse     : Fixed neighbour states (क्रम now anyway).
 *     Steve Whitehouse     : Made error_report functions dummies. This
 *                            is not the right place to वापस skbs.
 *     Steve Whitehouse     : Convert to seq_file
 *
 */

#समावेश <linux/net.h>
#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/netfilter_decnet.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/jhash.h>
#समावेश <linux/atomic.h>
#समावेश <net/net_namespace.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/dn.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_neigh.h>
#समावेश <net/dn_route.h>

अटल पूर्णांक dn_neigh_स्थिरruct(काष्ठा neighbour *);
अटल व्योम dn_neigh_error_report(काष्ठा neighbour *, काष्ठा sk_buff *);
अटल पूर्णांक dn_neigh_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);

/*
 * Operations क्रम adding the link layer header.
 */
अटल स्थिर काष्ठा neigh_ops dn_neigh_ops = अणु
	.family =		AF_DECnet,
	.error_report =		dn_neigh_error_report,
	.output =		dn_neigh_output,
	.connected_output =	dn_neigh_output,
पूर्ण;

अटल u32 dn_neigh_hash(स्थिर व्योम *pkey,
			 स्थिर काष्ठा net_device *dev,
			 __u32 *hash_rnd)
अणु
	वापस jhash_2words(*(__u16 *)pkey, 0, hash_rnd[0]);
पूर्ण

अटल bool dn_key_eq(स्थिर काष्ठा neighbour *neigh, स्थिर व्योम *pkey)
अणु
	वापस neigh_key_eq16(neigh, pkey);
पूर्ण

काष्ठा neigh_table dn_neigh_table = अणु
	.family =			PF_DECnet,
	.entry_size =			NEIGH_ENTRY_SIZE(माप(काष्ठा dn_neigh)),
	.key_len =			माप(__le16),
	.protocol =			cpu_to_be16(ETH_P_DNA_RT),
	.hash =				dn_neigh_hash,
	.key_eq =			dn_key_eq,
	.स्थिरructor =			dn_neigh_स्थिरruct,
	.id =				"dn_neigh_cache",
	.parms =अणु
		.tbl =			&dn_neigh_table,
		.reachable_समय =	30 * HZ,
		.data = अणु
			[NEIGH_VAR_MCAST_PROBES] = 0,
			[NEIGH_VAR_UCAST_PROBES] = 0,
			[NEIGH_VAR_APP_PROBES] = 0,
			[NEIGH_VAR_RETRANS_TIME] = 1 * HZ,
			[NEIGH_VAR_BASE_REACHABLE_TIME] = 30 * HZ,
			[NEIGH_VAR_DELAY_PROBE_TIME] = 5 * HZ,
			[NEIGH_VAR_GC_STALETIME] = 60 * HZ,
			[NEIGH_VAR_QUEUE_LEN_BYTES] = SK_WMEM_MAX,
			[NEIGH_VAR_PROXY_QLEN] = 0,
			[NEIGH_VAR_ANYCAST_DELAY] = 0,
			[NEIGH_VAR_PROXY_DELAY] = 0,
			[NEIGH_VAR_LOCKTIME] = 1 * HZ,
		पूर्ण,
	पूर्ण,
	.gc_पूर्णांकerval =			30 * HZ,
	.gc_thresh1 =			128,
	.gc_thresh2 =			512,
	.gc_thresh3 =			1024,
पूर्ण;

अटल पूर्णांक dn_neigh_स्थिरruct(काष्ठा neighbour *neigh)
अणु
	काष्ठा net_device *dev = neigh->dev;
	काष्ठा dn_neigh *dn = container_of(neigh, काष्ठा dn_neigh, n);
	काष्ठा dn_dev *dn_db;
	काष्ठा neigh_parms *parms;

	rcu_पढ़ो_lock();
	dn_db = rcu_dereference(dev->dn_ptr);
	अगर (dn_db == शून्य) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	parms = dn_db->neigh_parms;
	अगर (!parms) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	__neigh_parms_put(neigh->parms);
	neigh->parms = neigh_parms_clone(parms);
	rcu_पढ़ो_unlock();

	neigh->ops = &dn_neigh_ops;
	neigh->nud_state = NUD_NOARP;
	neigh->output = neigh->ops->connected_output;

	अगर ((dev->type == ARPHRD_IPGRE) || (dev->flags & IFF_POINTOPOINT))
		स_नकल(neigh->ha, dev->broadcast, dev->addr_len);
	अन्यथा अगर ((dev->type == ARPHRD_ETHER) || (dev->type == ARPHRD_LOOPBACK))
		dn_dn2eth(neigh->ha, dn->addr);
	अन्यथा अणु
		net_dbg_ratelimited("Trying to create neigh for hw %d\n",
				    dev->type);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Make an estimate of the remote block size by assuming that its
	 * two less then the device mtu, which it true क्रम ethernet (and
	 * other things which support दीर्घ क्रमmat headers) since there is
	 * an extra length field (of 16 bits) which isn't part of the
	 * ethernet headers and which the DECnet specs won't admit is part
	 * of the DECnet routing headers either.
	 *
	 * If we over estimate here its no big deal, the NSP negotiations
	 * will prevent us from sending packets which are too large क्रम the
	 * remote node to handle. In any हाल this figure is normally updated
	 * by a hello message in most हालs.
	 */
	dn->blksize = dev->mtu - 2;

	वापस 0;
पूर्ण

अटल व्योम dn_neigh_error_report(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	prपूर्णांकk(KERN_DEBUG "dn_neigh_error_report: called\n");
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक dn_neigh_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा dn_route *rt = (काष्ठा dn_route *)dst;
	काष्ठा net_device *dev = neigh->dev;
	अक्षर mac_addr[ETH_ALEN];
	अचिन्हित पूर्णांक seq;
	पूर्णांक err;

	dn_dn2eth(mac_addr, rt->rt_local_src);
	करो अणु
		seq = पढ़ो_seqbegin(&neigh->ha_lock);
		err = dev_hard_header(skb, dev, ntohs(skb->protocol),
				      neigh->ha, mac_addr, skb->len);
	पूर्ण जबतक (पढ़ो_seqretry(&neigh->ha_lock, seq));

	अगर (err >= 0)
		err = dev_queue_xmit(skb);
	अन्यथा अणु
		kमुक्त_skb(skb);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक dn_neigh_output_packet(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा dn_route *rt = (काष्ठा dn_route *)dst;
	काष्ठा neighbour *neigh = rt->n;

	वापस neigh->output(neigh, skb);
पूर्ण

/*
 * For talking to broadcast devices: Ethernet & PPP
 */
अटल पूर्णांक dn_दीर्घ_output(काष्ठा neighbour *neigh, काष्ठा sock *sk,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = neigh->dev;
	पूर्णांक headroom = dev->hard_header_len + माप(काष्ठा dn_दीर्घ_packet) + 3;
	अचिन्हित अक्षर *data;
	काष्ठा dn_दीर्घ_packet *lp;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);


	अगर (skb_headroom(skb) < headroom) अणु
		काष्ठा sk_buff *skb2 = skb_पुनः_स्मृति_headroom(skb, headroom);
		अगर (skb2 == शून्य) अणु
			net_crit_ratelimited("dn_long_output: no memory\n");
			kमुक्त_skb(skb);
			वापस -ENOBUFS;
		पूर्ण
		consume_skb(skb);
		skb = skb2;
		net_info_ratelimited("dn_long_output: Increasing headroom\n");
	पूर्ण

	data = skb_push(skb, माप(काष्ठा dn_दीर्घ_packet) + 3);
	lp = (काष्ठा dn_दीर्घ_packet *)(data+3);

	*((__le16 *)data) = cpu_to_le16(skb->len - 2);
	*(data + 2) = 1 | DN_RT_F_PF; /* Padding */

	lp->msgflg   = DN_RT_PKT_LONG|(cb->rt_flags&(DN_RT_F_IE|DN_RT_F_RQR|DN_RT_F_RTS));
	lp->d_area   = lp->d_subarea = 0;
	dn_dn2eth(lp->d_id, cb->dst);
	lp->s_area   = lp->s_subarea = 0;
	dn_dn2eth(lp->s_id, cb->src);
	lp->nl2      = 0;
	lp->visit_ct = cb->hops & 0x3f;
	lp->s_class  = 0;
	lp->pt       = 0;

	skb_reset_network_header(skb);

	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_POST_ROUTING,
		       &init_net, sk, skb, शून्य, neigh->dev,
		       dn_neigh_output_packet);
पूर्ण

/*
 * For talking to poपूर्णांकopoपूर्णांक and multidrop devices: DDCMP and X.25
 */
अटल पूर्णांक dn_लघु_output(काष्ठा neighbour *neigh, काष्ठा sock *sk,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = neigh->dev;
	पूर्णांक headroom = dev->hard_header_len + माप(काष्ठा dn_लघु_packet) + 2;
	काष्ठा dn_लघु_packet *sp;
	अचिन्हित अक्षर *data;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);


	अगर (skb_headroom(skb) < headroom) अणु
		काष्ठा sk_buff *skb2 = skb_पुनः_स्मृति_headroom(skb, headroom);
		अगर (skb2 == शून्य) अणु
			net_crit_ratelimited("dn_short_output: no memory\n");
			kमुक्त_skb(skb);
			वापस -ENOBUFS;
		पूर्ण
		consume_skb(skb);
		skb = skb2;
		net_info_ratelimited("dn_short_output: Increasing headroom\n");
	पूर्ण

	data = skb_push(skb, माप(काष्ठा dn_लघु_packet) + 2);
	*((__le16 *)data) = cpu_to_le16(skb->len - 2);
	sp = (काष्ठा dn_लघु_packet *)(data+2);

	sp->msgflg     = DN_RT_PKT_SHORT|(cb->rt_flags&(DN_RT_F_RQR|DN_RT_F_RTS));
	sp->dstnode    = cb->dst;
	sp->srcnode    = cb->src;
	sp->क्रमward    = cb->hops & 0x3f;

	skb_reset_network_header(skb);

	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_POST_ROUTING,
		       &init_net, sk, skb, शून्य, neigh->dev,
		       dn_neigh_output_packet);
पूर्ण

/*
 * For talking to DECnet phase III nodes
 * Phase 3 output is the same as लघु output, execpt that
 * it clears the area bits beक्रमe transmission.
 */
अटल पूर्णांक dn_phase3_output(काष्ठा neighbour *neigh, काष्ठा sock *sk,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = neigh->dev;
	पूर्णांक headroom = dev->hard_header_len + माप(काष्ठा dn_लघु_packet) + 2;
	काष्ठा dn_लघु_packet *sp;
	अचिन्हित अक्षर *data;
	काष्ठा dn_skb_cb *cb = DN_SKB_CB(skb);

	अगर (skb_headroom(skb) < headroom) अणु
		काष्ठा sk_buff *skb2 = skb_पुनः_स्मृति_headroom(skb, headroom);
		अगर (skb2 == शून्य) अणु
			net_crit_ratelimited("dn_phase3_output: no memory\n");
			kमुक्त_skb(skb);
			वापस -ENOBUFS;
		पूर्ण
		consume_skb(skb);
		skb = skb2;
		net_info_ratelimited("dn_phase3_output: Increasing headroom\n");
	पूर्ण

	data = skb_push(skb, माप(काष्ठा dn_लघु_packet) + 2);
	*((__le16 *)data) = cpu_to_le16(skb->len - 2);
	sp = (काष्ठा dn_लघु_packet *)(data + 2);

	sp->msgflg   = DN_RT_PKT_SHORT|(cb->rt_flags&(DN_RT_F_RQR|DN_RT_F_RTS));
	sp->dstnode  = cb->dst & cpu_to_le16(0x03ff);
	sp->srcnode  = cb->src & cpu_to_le16(0x03ff);
	sp->क्रमward  = cb->hops & 0x3f;

	skb_reset_network_header(skb);

	वापस NF_HOOK(NFPROTO_DECNET, NF_DN_POST_ROUTING,
		       &init_net, sk, skb, शून्य, neigh->dev,
		       dn_neigh_output_packet);
पूर्ण

पूर्णांक dn_to_neigh_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा dn_route *rt = (काष्ठा dn_route *) dst;
	काष्ठा neighbour *neigh = rt->n;
	काष्ठा dn_neigh *dn = container_of(neigh, काष्ठा dn_neigh, n);
	काष्ठा dn_dev *dn_db;
	bool use_दीर्घ;

	rcu_पढ़ो_lock();
	dn_db = rcu_dereference(neigh->dev->dn_ptr);
	अगर (dn_db == शून्य) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	use_दीर्घ = dn_db->use_दीर्घ;
	rcu_पढ़ो_unlock();

	अगर (dn->flags & DN_NDFLAG_P3)
		वापस dn_phase3_output(neigh, sk, skb);
	अगर (use_दीर्घ)
		वापस dn_दीर्घ_output(neigh, sk, skb);
	अन्यथा
		वापस dn_लघु_output(neigh, sk, skb);
पूर्ण

/*
 * Unक्रमtunately, the neighbour code uses the device in its hash
 * function, so we करोn't get any advantage from it. This function
 * basically करोes a neigh_lookup(), but without comparing the device
 * field. This is required क्रम the On-Ethernet cache
 */

/*
 * Poपूर्णांकopoपूर्णांक link receives a hello message
 */
व्योम dn_neigh_poपूर्णांकopoपूर्णांक_hello(काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

/*
 * Ethernet router hello message received
 */
पूर्णांक dn_neigh_router_hello(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtnode_hello_message *msg = (काष्ठा rtnode_hello_message *)skb->data;

	काष्ठा neighbour *neigh;
	काष्ठा dn_neigh *dn;
	काष्ठा dn_dev *dn_db;
	__le16 src;

	src = dn_eth2dn(msg->id);

	neigh = __neigh_lookup(&dn_neigh_table, &src, skb->dev, 1);

	dn = container_of(neigh, काष्ठा dn_neigh, n);

	अगर (neigh) अणु
		ग_लिखो_lock(&neigh->lock);

		neigh->used = jअगरfies;
		dn_db = rcu_dereference(neigh->dev->dn_ptr);

		अगर (!(neigh->nud_state & NUD_PERMANENT)) अणु
			neigh->updated = jअगरfies;

			अगर (neigh->dev->type == ARPHRD_ETHER)
				स_नकल(neigh->ha, &eth_hdr(skb)->h_source, ETH_ALEN);

			dn->blksize  = le16_to_cpu(msg->blksize);
			dn->priority = msg->priority;

			dn->flags &= ~DN_NDFLAG_P3;

			चयन (msg->iinfo & DN_RT_INFO_TYPE) अणु
			हाल DN_RT_INFO_L1RT:
				dn->flags &=~DN_NDFLAG_R2;
				dn->flags |= DN_NDFLAG_R1;
				अवरोध;
			हाल DN_RT_INFO_L2RT:
				dn->flags |= DN_NDFLAG_R2;
			पूर्ण
		पूर्ण

		/* Only use routers in our area */
		अगर ((le16_to_cpu(src)>>10) == (le16_to_cpu((decnet_address))>>10)) अणु
			अगर (!dn_db->router) अणु
				dn_db->router = neigh_clone(neigh);
			पूर्ण अन्यथा अणु
				अगर (msg->priority > ((काष्ठा dn_neigh *)dn_db->router)->priority)
					neigh_release(xchg(&dn_db->router, neigh_clone(neigh)));
			पूर्ण
		पूर्ण
		ग_लिखो_unlock(&neigh->lock);
		neigh_release(neigh);
	पूर्ण

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Endnode hello message received
 */
पूर्णांक dn_neigh_endnode_hello(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा endnode_hello_message *msg = (काष्ठा endnode_hello_message *)skb->data;
	काष्ठा neighbour *neigh;
	काष्ठा dn_neigh *dn;
	__le16 src;

	src = dn_eth2dn(msg->id);

	neigh = __neigh_lookup(&dn_neigh_table, &src, skb->dev, 1);

	dn = container_of(neigh, काष्ठा dn_neigh, n);

	अगर (neigh) अणु
		ग_लिखो_lock(&neigh->lock);

		neigh->used = jअगरfies;

		अगर (!(neigh->nud_state & NUD_PERMANENT)) अणु
			neigh->updated = jअगरfies;

			अगर (neigh->dev->type == ARPHRD_ETHER)
				स_नकल(neigh->ha, &eth_hdr(skb)->h_source, ETH_ALEN);
			dn->flags   &= ~(DN_NDFLAG_R1 | DN_NDFLAG_R2);
			dn->blksize  = le16_to_cpu(msg->blksize);
			dn->priority = 0;
		पूर्ण

		ग_लिखो_unlock(&neigh->lock);
		neigh_release(neigh);
	पूर्ण

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल अक्षर *dn_find_slot(अक्षर *base, पूर्णांक max, पूर्णांक priority)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर *min = शून्य;

	base += 6; /* skip first id */

	क्रम(i = 0; i < max; i++) अणु
		अगर (!min || (*base < *min))
			min = base;
		base += 7; /* find next priority */
	पूर्ण

	अगर (!min)
		वापस शून्य;

	वापस (*min < priority) ? (min - 6) : शून्य;
पूर्ण

काष्ठा elist_cb_state अणु
	काष्ठा net_device *dev;
	अचिन्हित अक्षर *ptr;
	अचिन्हित अक्षर *rs;
	पूर्णांक t, n;
पूर्ण;

अटल व्योम neigh_elist_cb(काष्ठा neighbour *neigh, व्योम *_info)
अणु
	काष्ठा elist_cb_state *s = _info;
	काष्ठा dn_neigh *dn;

	अगर (neigh->dev != s->dev)
		वापस;

	dn = container_of(neigh, काष्ठा dn_neigh, n);
	अगर (!(dn->flags & (DN_NDFLAG_R1|DN_NDFLAG_R2)))
		वापस;

	अगर (s->t == s->n)
		s->rs = dn_find_slot(s->ptr, s->n, dn->priority);
	अन्यथा
		s->t++;
	अगर (s->rs == शून्य)
		वापस;

	dn_dn2eth(s->rs, dn->addr);
	s->rs += 6;
	*(s->rs) = neigh->nud_state & NUD_CONNECTED ? 0x80 : 0x0;
	*(s->rs) |= dn->priority;
	s->rs++;
पूर्ण

पूर्णांक dn_neigh_elist(काष्ठा net_device *dev, अचिन्हित अक्षर *ptr, पूर्णांक n)
अणु
	काष्ठा elist_cb_state state;

	state.dev = dev;
	state.t = 0;
	state.n = n;
	state.ptr = ptr;
	state.rs = ptr;

	neigh_क्रम_each(&dn_neigh_table, neigh_elist_cb, &state);

	वापस state.t;
पूर्ण


#अगर_घोषित CONFIG_PROC_FS

अटल अंतरभूत व्योम dn_neigh_क्रमmat_entry(काष्ठा seq_file *seq,
					 काष्ठा neighbour *n)
अणु
	काष्ठा dn_neigh *dn = container_of(n, काष्ठा dn_neigh, n);
	अक्षर buf[DN_ASCBUF_LEN];

	पढ़ो_lock(&n->lock);
	seq_म_लिखो(seq, "%-7s %s%s%s   %02x    %02d  %07ld %-8s\n",
		   dn_addr2asc(le16_to_cpu(dn->addr), buf),
		   (dn->flags&DN_NDFLAG_R1) ? "1" : "-",
		   (dn->flags&DN_NDFLAG_R2) ? "2" : "-",
		   (dn->flags&DN_NDFLAG_P3) ? "3" : "-",
		   dn->n.nud_state,
		   refcount_पढ़ो(&dn->n.refcnt),
		   dn->blksize,
		   (dn->n.dev) ? dn->n.dev->name : "?");
	पढ़ो_unlock(&n->lock);
पूर्ण

अटल पूर्णांक dn_neigh_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Addr    Flags State Use Blksize Dev\n");
	पूर्ण अन्यथा अणु
		dn_neigh_क्रमmat_entry(seq, v);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *dn_neigh_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस neigh_seq_start(seq, pos, &dn_neigh_table,
			       NEIGH_SEQ_NEIGH_ONLY);
पूर्ण

अटल स्थिर काष्ठा seq_operations dn_neigh_seq_ops = अणु
	.start = dn_neigh_seq_start,
	.next  = neigh_seq_next,
	.stop  = neigh_seq_stop,
	.show  = dn_neigh_seq_show,
पूर्ण;
#पूर्ण_अगर

व्योम __init dn_neigh_init(व्योम)
अणु
	neigh_table_init(NEIGH_DN_TABLE, &dn_neigh_table);
	proc_create_net("decnet_neigh", 0444, init_net.proc_net,
			&dn_neigh_seq_ops, माप(काष्ठा neigh_seq_state));
पूर्ण

व्योम __निकास dn_neigh_cleanup(व्योम)
अणु
	हटाओ_proc_entry("decnet_neigh", init_net.proc_net);
	neigh_table_clear(NEIGH_DN_TABLE, &dn_neigh_table);
पूर्ण
