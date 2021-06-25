<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _IPV6_FRAG_H
#घोषणा _IPV6_FRAG_H
#समावेश <linux/kernel.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6.h>
#समावेश <net/inet_frag.h>

क्रमागत ip6_defrag_users अणु
	IP6_DEFRAG_LOCAL_DELIVER,
	IP6_DEFRAG_CONNTRACK_IN,
	__IP6_DEFRAG_CONNTRACK_IN	= IP6_DEFRAG_CONNTRACK_IN + अच_लघु_उच्च,
	IP6_DEFRAG_CONNTRACK_OUT,
	__IP6_DEFRAG_CONNTRACK_OUT	= IP6_DEFRAG_CONNTRACK_OUT + अच_लघु_उच्च,
	IP6_DEFRAG_CONNTRACK_BRIDGE_IN,
	__IP6_DEFRAG_CONNTRACK_BRIDGE_IN = IP6_DEFRAG_CONNTRACK_BRIDGE_IN + अच_लघु_उच्च,
पूर्ण;

/*
 *	Equivalent of ipv4 काष्ठा ip
 */
काष्ठा frag_queue अणु
	काष्ठा inet_frag_queue	q;

	पूर्णांक			iअगर;
	__u16			nhoffset;
	u8			ecn;
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत व्योम ip6frag_init(काष्ठा inet_frag_queue *q, स्थिर व्योम *a)
अणु
	काष्ठा frag_queue *fq = container_of(q, काष्ठा frag_queue, q);
	स्थिर काष्ठा frag_v6_compare_key *key = a;

	q->key.v6 = *key;
	fq->ecn = 0;
पूर्ण

अटल अंतरभूत u32 ip6frag_key_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	वापस jhash2(data,
		      माप(काष्ठा frag_v6_compare_key) / माप(u32), seed);
पूर्ण

अटल अंतरभूत u32 ip6frag_obj_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा inet_frag_queue *fq = data;

	वापस jhash2((स्थिर u32 *)&fq->key.v6,
		      माप(काष्ठा frag_v6_compare_key) / माप(u32), seed);
पूर्ण

अटल अंतरभूत पूर्णांक
ip6frag_obj_cmpfn(काष्ठा rhashtable_compare_arg *arg, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा frag_v6_compare_key *key = arg->key;
	स्थिर काष्ठा inet_frag_queue *fq = ptr;

	वापस !!स_भेद(&fq->key, key, माप(*key));
पूर्ण

अटल अंतरभूत व्योम
ip6frag_expire_frag_queue(काष्ठा net *net, काष्ठा frag_queue *fq)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा sk_buff *head;

	rcu_पढ़ो_lock();
	अगर (fq->q.fqdir->dead)
		जाओ out_rcu_unlock;
	spin_lock(&fq->q.lock);

	अगर (fq->q.flags & INET_FRAG_COMPLETE)
		जाओ out;

	inet_frag_समाप्त(&fq->q);

	dev = dev_get_by_index_rcu(net, fq->iअगर);
	अगर (!dev)
		जाओ out;

	__IP6_INC_STATS(net, __in6_dev_get(dev), IPSTATS_MIB_REASMFAILS);
	__IP6_INC_STATS(net, __in6_dev_get(dev), IPSTATS_MIB_REASMTIMEOUT);

	/* Don't send error अगर the first segment did not arrive. */
	अगर (!(fq->q.flags & INET_FRAG_FIRST_IN))
		जाओ out;

	/* sk_buff::dev and sk_buff::rbnode are जोड़ized. So we
	 * pull the head out of the tree in order to be able to
	 * deal with head->dev.
	 */
	head = inet_frag_pull_head(&fq->q);
	अगर (!head)
		जाओ out;

	head->dev = dev;
	spin_unlock(&fq->q.lock);

	icmpv6_send(head, ICMPV6_TIME_EXCEED, ICMPV6_EXC_FRAGTIME, 0);
	kमुक्त_skb(head);
	जाओ out_rcu_unlock;

out:
	spin_unlock(&fq->q.lock);
out_rcu_unlock:
	rcu_पढ़ो_unlock();
	inet_frag_put(&fq->q);
पूर्ण

/* Check अगर the upper layer header is truncated in the first fragment. */
अटल अंतरभूत bool
ipv6frag_thdr_truncated(काष्ठा sk_buff *skb, पूर्णांक start, u8 *nexthdrp)
अणु
	u8 nexthdr = *nexthdrp;
	__be16 frag_off;
	पूर्णांक offset;

	offset = ipv6_skip_exthdr(skb, start, &nexthdr, &frag_off);
	अगर (offset < 0 || (frag_off & htons(IP6_OFFSET)))
		वापस false;
	चयन (nexthdr) अणु
	हाल NEXTHDR_TCP:
		offset += माप(काष्ठा tcphdr);
		अवरोध;
	हाल NEXTHDR_UDP:
		offset += माप(काष्ठा udphdr);
		अवरोध;
	हाल NEXTHDR_ICMP:
		offset += माप(काष्ठा icmp6hdr);
		अवरोध;
	शेष:
		offset += 1;
	पूर्ण
	अगर (offset > skb->len)
		वापस true;
	वापस false;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
