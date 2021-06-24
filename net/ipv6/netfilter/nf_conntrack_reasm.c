<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPv6 fragment reassembly क्रम connection tracking
 *
 * Copyright (C)2004 USAGI/WIDE Project
 *
 * Author:
 *	Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *
 * Based on: net/ipv6/reassembly.c
 */

#घोषणा pr_fmt(fmt) "IPv6-nf: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>

#समावेश <net/ipv6_frag.h>

#समावेश <net/netfilter/ipv6/nf_conntrack_ipv6.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#समावेश <net/netns/generic.h>

अटल स्थिर अक्षर nf_frags_cache_name[] = "nf-frags";

अचिन्हित पूर्णांक nf_frag_pernet_id __पढ़ो_mostly;
अटल काष्ठा inet_frags nf_frags;

अटल काष्ठा nft_ct_frag6_pernet *nf_frag_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, nf_frag_pernet_id);
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

अटल काष्ठा ctl_table nf_ct_frag6_sysctl_table[] = अणु
	अणु
		.procname	= "nf_conntrack_frag6_timeout",
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "nf_conntrack_frag6_low_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "nf_conntrack_frag6_high_thresh",
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक nf_ct_frag6_sysctl_रेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag;
	काष्ठा ctl_table *table;
	काष्ठा ctl_table_header *hdr;

	table = nf_ct_frag6_sysctl_table;
	अगर (!net_eq(net, &init_net)) अणु
		table = kmemdup(table, माप(nf_ct_frag6_sysctl_table),
				GFP_KERNEL);
		अगर (table == शून्य)
			जाओ err_alloc;
	पूर्ण

	nf_frag = nf_frag_pernet(net);

	table[0].data	= &nf_frag->fqdir->समयout;
	table[1].data	= &nf_frag->fqdir->low_thresh;
	table[1].extra2	= &nf_frag->fqdir->high_thresh;
	table[2].data	= &nf_frag->fqdir->high_thresh;
	table[2].extra1	= &nf_frag->fqdir->low_thresh;
	table[2].extra2	= &nf_frag->fqdir->high_thresh;

	hdr = रेजिस्टर_net_sysctl(net, "net/netfilter", table);
	अगर (hdr == शून्य)
		जाओ err_reg;

	nf_frag->nf_frag_frags_hdr = hdr;
	वापस 0;

err_reg:
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
err_alloc:
	वापस -ENOMEM;
पूर्ण

अटल व्योम __net_निकास nf_ct_frags6_sysctl_unरेजिस्टर(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag = nf_frag_pernet(net);
	काष्ठा ctl_table *table;

	table = nf_frag->nf_frag_frags_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(nf_frag->nf_frag_frags_hdr);
	अगर (!net_eq(net, &init_net))
		kमुक्त(table);
पूर्ण

#अन्यथा
अटल पूर्णांक nf_ct_frag6_sysctl_रेजिस्टर(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल व्योम __net_निकास nf_ct_frags6_sysctl_unरेजिस्टर(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nf_ct_frag6_reयंत्र(काष्ठा frag_queue *fq, काष्ठा sk_buff *skb,
			     काष्ठा sk_buff *prev_tail, काष्ठा net_device *dev);

अटल अंतरभूत u8 ip6_frag_ecn(स्थिर काष्ठा ipv6hdr *ipv6h)
अणु
	वापस 1 << (ipv6_get_dsfield(ipv6h) & INET_ECN_MASK);
पूर्ण

अटल व्योम nf_ct_frag6_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_frag_queue *frag = from_समयr(frag, t, समयr);
	काष्ठा frag_queue *fq;

	fq = container_of(frag, काष्ठा frag_queue, q);

	ip6frag_expire_frag_queue(fq->q.fqdir->net, fq);
पूर्ण

/* Creation primitives. */
अटल काष्ठा frag_queue *fq_find(काष्ठा net *net, __be32 id, u32 user,
				  स्थिर काष्ठा ipv6hdr *hdr, पूर्णांक iअगर)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag = nf_frag_pernet(net);
	काष्ठा frag_v6_compare_key key = अणु
		.id = id,
		.saddr = hdr->saddr,
		.daddr = hdr->daddr,
		.user = user,
		.iअगर = iअगर,
	पूर्ण;
	काष्ठा inet_frag_queue *q;

	q = inet_frag_find(nf_frag->fqdir, &key);
	अगर (!q)
		वापस शून्य;

	वापस container_of(q, काष्ठा frag_queue, q);
पूर्ण


अटल पूर्णांक nf_ct_frag6_queue(काष्ठा frag_queue *fq, काष्ठा sk_buff *skb,
			     स्थिर काष्ठा frag_hdr *fhdr, पूर्णांक nhoff)
अणु
	अचिन्हित पूर्णांक payload_len;
	काष्ठा net_device *dev;
	काष्ठा sk_buff *prev;
	पूर्णांक offset, end, err;
	u8 ecn;

	अगर (fq->q.flags & INET_FRAG_COMPLETE) अणु
		pr_debug("Already completed\n");
		जाओ err;
	पूर्ण

	payload_len = ntohs(ipv6_hdr(skb)->payload_len);

	offset = ntohs(fhdr->frag_off) & ~0x7;
	end = offset + (payload_len -
			((u8 *)(fhdr + 1) - (u8 *)(ipv6_hdr(skb) + 1)));

	अगर ((अचिन्हित पूर्णांक)end > IPV6_MAXPLEN) अणु
		pr_debug("offset is too large.\n");
		वापस -EINVAL;
	पूर्ण

	ecn = ip6_frag_ecn(ipv6_hdr(skb));

	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
		skb->csum = csum_sub(skb->csum,
				     csum_partial(nh, (u8 *)(fhdr + 1) - nh,
						  0));
	पूर्ण

	/* Is this the final fragment? */
	अगर (!(fhdr->frag_off & htons(IP6_MF))) अणु
		/* If we alपढ़ोy have some bits beyond end
		 * or have dअगरferent end, the segment is corrupted.
		 */
		अगर (end < fq->q.len ||
		    ((fq->q.flags & INET_FRAG_LAST_IN) && end != fq->q.len)) अणु
			pr_debug("already received last fragment\n");
			जाओ err;
		पूर्ण
		fq->q.flags |= INET_FRAG_LAST_IN;
		fq->q.len = end;
	पूर्ण अन्यथा अणु
		/* Check अगर the fragment is rounded to 8 bytes.
		 * Required by the RFC.
		 */
		अगर (end & 0x7) अणु
			/* RFC2460 says always send parameter problem in
			 * this हाल. -DaveM
			 */
			pr_debug("end of fragment not rounded to 8 bytes.\n");
			inet_frag_समाप्त(&fq->q);
			वापस -EPROTO;
		पूर्ण
		अगर (end > fq->q.len) अणु
			/* Some bits beyond end -> corruption. */
			अगर (fq->q.flags & INET_FRAG_LAST_IN) अणु
				pr_debug("last packet already reached.\n");
				जाओ err;
			पूर्ण
			fq->q.len = end;
		पूर्ण
	पूर्ण

	अगर (end == offset)
		जाओ err;

	/* Poपूर्णांक पूर्णांकo the IP datagram 'data' part. */
	अगर (!pskb_pull(skb, (u8 *) (fhdr + 1) - skb->data)) अणु
		pr_debug("queue: message is too short.\n");
		जाओ err;
	पूर्ण
	अगर (pskb_trim_rcsum(skb, end - offset)) अणु
		pr_debug("Can't trim\n");
		जाओ err;
	पूर्ण

	/* Note : skb->rbnode and skb->dev share the same location. */
	dev = skb->dev;
	/* Makes sure compiler wont करो silly aliasing games */
	barrier();

	prev = fq->q.fragments_tail;
	err = inet_frag_queue_insert(&fq->q, skb, offset, end);
	अगर (err) अणु
		अगर (err == IPFRAG_DUP) अणु
			/* No error क्रम duplicates, pretend they got queued. */
			kमुक्त_skb(skb);
			वापस -EINPROGRESS;
		पूर्ण
		जाओ insert_error;
	पूर्ण

	अगर (dev)
		fq->iअगर = dev->अगरindex;

	fq->q.stamp = skb->tstamp;
	fq->q.meat += skb->len;
	fq->ecn |= ecn;
	अगर (payload_len > fq->q.max_size)
		fq->q.max_size = payload_len;
	add_frag_mem_limit(fq->q.fqdir, skb->truesize);

	/* The first fragment.
	 * nhoffset is obtained from the first fragment, of course.
	 */
	अगर (offset == 0) अणु
		fq->nhoffset = nhoff;
		fq->q.flags |= INET_FRAG_FIRST_IN;
	पूर्ण

	अगर (fq->q.flags == (INET_FRAG_FIRST_IN | INET_FRAG_LAST_IN) &&
	    fq->q.meat == fq->q.len) अणु
		अचिन्हित दीर्घ orefdst = skb->_skb_refdst;

		skb->_skb_refdst = 0UL;
		err = nf_ct_frag6_reयंत्र(fq, skb, prev, dev);
		skb->_skb_refdst = orefdst;

		/* After queue has assumed skb ownership, only 0 or
		 * -EINPROGRESS must be वापसed.
		 */
		वापस err ? -EINPROGRESS : 0;
	पूर्ण

	skb_dst_drop(skb);
	वापस -EINPROGRESS;

insert_error:
	inet_frag_समाप्त(&fq->q);
err:
	skb_dst_drop(skb);
	वापस -EINVAL;
पूर्ण

/*
 *	Check अगर this packet is complete.
 *
 *	It is called with locked fq, and caller must check that
 *	queue is eligible क्रम reassembly i.e. it is not COMPLETE,
 *	the last and the first frames arrived and all the bits are here.
 */
अटल पूर्णांक nf_ct_frag6_reयंत्र(काष्ठा frag_queue *fq, काष्ठा sk_buff *skb,
			     काष्ठा sk_buff *prev_tail, काष्ठा net_device *dev)
अणु
	व्योम *reयंत्र_data;
	पूर्णांक payload_len;
	u8 ecn;

	inet_frag_समाप्त(&fq->q);

	ecn = ip_frag_ecn_table[fq->ecn];
	अगर (unlikely(ecn == 0xff))
		जाओ err;

	reयंत्र_data = inet_frag_reयंत्र_prepare(&fq->q, skb, prev_tail);
	अगर (!reयंत्र_data)
		जाओ err;

	payload_len = ((skb->data - skb_network_header(skb)) -
		       माप(काष्ठा ipv6hdr) + fq->q.len -
		       माप(काष्ठा frag_hdr));
	अगर (payload_len > IPV6_MAXPLEN) अणु
		net_dbg_ratelimited("nf_ct_frag6_reasm: payload len = %d\n",
				    payload_len);
		जाओ err;
	पूर्ण

	/* We have to हटाओ fragment header from datagram and to relocate
	 * header in order to calculate ICV correctly. */
	skb_network_header(skb)[fq->nhoffset] = skb_transport_header(skb)[0];
	स_हटाओ(skb->head + माप(काष्ठा frag_hdr), skb->head,
		(skb->data - skb->head) - माप(काष्ठा frag_hdr));
	skb->mac_header += माप(काष्ठा frag_hdr);
	skb->network_header += माप(काष्ठा frag_hdr);

	skb_reset_transport_header(skb);

	inet_frag_reयंत्र_finish(&fq->q, skb, reयंत्र_data, false);

	skb->ignore_df = 1;
	skb->dev = dev;
	ipv6_hdr(skb)->payload_len = htons(payload_len);
	ipv6_change_dsfield(ipv6_hdr(skb), 0xff, ecn);
	IP6CB(skb)->frag_max_size = माप(काष्ठा ipv6hdr) + fq->q.max_size;
	IP6CB(skb)->flags |= IP6SKB_FRAGMENTED;

	/* Yes, and fold redundant checksum back. 8) */
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->csum = csum_partial(skb_network_header(skb),
					 skb_network_header_len(skb),
					 skb->csum);

	fq->q.rb_fragments = RB_ROOT;
	fq->q.fragments_tail = शून्य;
	fq->q.last_run_head = शून्य;

	वापस 0;

err:
	inet_frag_समाप्त(&fq->q);
	वापस -EINVAL;
पूर्ण

/*
 * find the header just beक्रमe Fragment Header.
 *
 * अगर success वापस 0 and set ...
 * (*prevhdrp): the value of "Next Header Field" in the header
 *		just beक्रमe Fragment Header.
 * (*prevhoff): the offset of "Next Header Field" in the header
 *		just beक्रमe Fragment Header.
 * (*fhoff)   : the offset of Fragment Header.
 *
 * Based on ipv6_skip_hdr() in net/ipv6/exthdr.c
 *
 */
अटल पूर्णांक
find_prev_fhdr(काष्ठा sk_buff *skb, u8 *prevhdrp, पूर्णांक *prevhoff, पूर्णांक *fhoff)
अणु
	u8 nexthdr = ipv6_hdr(skb)->nexthdr;
	स्थिर पूर्णांक netoff = skb_network_offset(skb);
	u8 prev_nhoff = netoff + दुरत्व(काष्ठा ipv6hdr, nexthdr);
	पूर्णांक start = netoff + माप(काष्ठा ipv6hdr);
	पूर्णांक len = skb->len - start;
	u8 prevhdr = NEXTHDR_IPV6;

	जबतक (nexthdr != NEXTHDR_FRAGMENT) अणु
		काष्ठा ipv6_opt_hdr hdr;
		पूर्णांक hdrlen;

		अगर (!ipv6_ext_hdr(nexthdr)) अणु
			वापस -1;
		पूर्ण
		अगर (nexthdr == NEXTHDR_NONE) अणु
			pr_debug("next header is none\n");
			वापस -1;
		पूर्ण
		अगर (len < (पूर्णांक)माप(काष्ठा ipv6_opt_hdr)) अणु
			pr_debug("too short\n");
			वापस -1;
		पूर्ण
		अगर (skb_copy_bits(skb, start, &hdr, माप(hdr)))
			BUG();
		अगर (nexthdr == NEXTHDR_AUTH)
			hdrlen = ipv6_authlen(&hdr);
		अन्यथा
			hdrlen = ipv6_optlen(&hdr);

		prevhdr = nexthdr;
		prev_nhoff = start;

		nexthdr = hdr.nexthdr;
		len -= hdrlen;
		start += hdrlen;
	पूर्ण

	अगर (len < 0)
		वापस -1;

	*prevhdrp = prevhdr;
	*prevhoff = prev_nhoff;
	*fhoff = start;

	वापस 0;
पूर्ण

पूर्णांक nf_ct_frag6_gather(काष्ठा net *net, काष्ठा sk_buff *skb, u32 user)
अणु
	u16 savethdr = skb->transport_header;
	u8 nexthdr = NEXTHDR_FRAGMENT;
	पूर्णांक fhoff, nhoff, ret;
	काष्ठा frag_hdr *fhdr;
	काष्ठा frag_queue *fq;
	काष्ठा ipv6hdr *hdr;
	u8 prevhdr;

	/* Jumbo payload inhibits frag. header */
	अगर (ipv6_hdr(skb)->payload_len == 0) अणु
		pr_debug("payload len = 0\n");
		वापस 0;
	पूर्ण

	अगर (find_prev_fhdr(skb, &prevhdr, &nhoff, &fhoff) < 0)
		वापस 0;

	/* Discard the first fragment अगर it करोes not include all headers
	 * RFC 8200, Section 4.5
	 */
	अगर (ipv6frag_thdr_truncated(skb, fhoff, &nexthdr)) अणु
		pr_debug("Drop incomplete fragment\n");
		वापस 0;
	पूर्ण

	अगर (!pskb_may_pull(skb, fhoff + माप(*fhdr)))
		वापस -ENOMEM;

	skb_set_transport_header(skb, fhoff);
	hdr = ipv6_hdr(skb);
	fhdr = (काष्ठा frag_hdr *)skb_transport_header(skb);

	skb_orphan(skb);
	fq = fq_find(net, fhdr->identअगरication, user, hdr,
		     skb->dev ? skb->dev->अगरindex : 0);
	अगर (fq == शून्य) अणु
		pr_debug("Can't find and can't create new queue\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_bh(&fq->q.lock);

	ret = nf_ct_frag6_queue(fq, skb, fhdr, nhoff);
	अगर (ret == -EPROTO) अणु
		skb->transport_header = savethdr;
		ret = 0;
	पूर्ण

	spin_unlock_bh(&fq->q.lock);
	inet_frag_put(&fq->q);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_frag6_gather);

अटल पूर्णांक nf_ct_net_init(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag  = nf_frag_pernet(net);
	पूर्णांक res;

	res = fqdir_init(&nf_frag->fqdir, &nf_frags, net);
	अगर (res < 0)
		वापस res;

	nf_frag->fqdir->high_thresh = IPV6_FRAG_HIGH_THRESH;
	nf_frag->fqdir->low_thresh = IPV6_FRAG_LOW_THRESH;
	nf_frag->fqdir->समयout = IPV6_FRAG_TIMEOUT;

	res = nf_ct_frag6_sysctl_रेजिस्टर(net);
	अगर (res < 0)
		fqdir_निकास(nf_frag->fqdir);
	वापस res;
पूर्ण

अटल व्योम nf_ct_net_pre_निकास(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag  = nf_frag_pernet(net);

	fqdir_pre_निकास(nf_frag->fqdir);
पूर्ण

अटल व्योम nf_ct_net_निकास(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag  = nf_frag_pernet(net);

	nf_ct_frags6_sysctl_unरेजिस्टर(net);
	fqdir_निकास(nf_frag->fqdir);
पूर्ण

अटल काष्ठा pernet_operations nf_ct_net_ops = अणु
	.init		= nf_ct_net_init,
	.pre_निकास	= nf_ct_net_pre_निकास,
	.निकास		= nf_ct_net_निकास,
	.id		= &nf_frag_pernet_id,
	.size		= माप(काष्ठा nft_ct_frag6_pernet),
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params nfct_rhash_params = अणु
	.head_offset		= दुरत्व(काष्ठा inet_frag_queue, node),
	.hashfn			= ip6frag_key_hashfn,
	.obj_hashfn		= ip6frag_obj_hashfn,
	.obj_cmpfn		= ip6frag_obj_cmpfn,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

पूर्णांक nf_ct_frag6_init(व्योम)
अणु
	पूर्णांक ret = 0;

	nf_frags.स्थिरructor = ip6frag_init;
	nf_frags.deकाष्ठाor = शून्य;
	nf_frags.qsize = माप(काष्ठा frag_queue);
	nf_frags.frag_expire = nf_ct_frag6_expire;
	nf_frags.frags_cache_name = nf_frags_cache_name;
	nf_frags.rhash_params = nfct_rhash_params;
	ret = inet_frags_init(&nf_frags);
	अगर (ret)
		जाओ out;
	ret = रेजिस्टर_pernet_subsys(&nf_ct_net_ops);
	अगर (ret)
		inet_frags_fini(&nf_frags);

out:
	वापस ret;
पूर्ण

व्योम nf_ct_frag6_cleanup(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&nf_ct_net_ops);
	inet_frags_fini(&nf_frags);
पूर्ण
