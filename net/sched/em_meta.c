<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/em_meta.c	Metadata ematch
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 *
 * ==========================================================================
 *
 * 	The metadata ematch compares two meta objects where each object
 * 	represents either a meta value stored in the kernel or a अटल
 * 	value provided by userspace. The objects are not provided by
 * 	userspace itself but rather a definition providing the inक्रमmation
 * 	to build them. Every object is of a certain type which must be
 * 	equal to the object it is being compared to.
 *
 * 	The definition of a objects conists of the type (meta type), a
 * 	identअगरier (meta id) and additional type specअगरic inक्रमmation.
 * 	The meta id is either TCF_META_TYPE_VALUE क्रम values provided by
 * 	userspace or a index to the meta operations table consisting of
 * 	function poपूर्णांकers to type specअगरic meta data collectors वापसing
 * 	the value of the requested meta value.
 *
 * 	         lvalue                                   rvalue
 * 	      +-----------+                           +-----------+
 * 	      | type: INT |                           | type: INT |
 * 	 def  | id: DEV   |                           | id: VALUE |
 * 	      | data:     |                           | data: 3   |
 * 	      +-----------+                           +-----------+
 * 	            |                                       |
 * 	            ---> meta_ops[INT][DEV](...)            |
 *	                      |                             |
 * 	            -----------                             |
 * 	            V                                       V
 * 	      +-----------+                           +-----------+
 * 	      | type: INT |                           | type: INT |
 * 	 obj  | id: DEV |                             | id: VALUE |
 * 	      | data: 2   |<--data got filled out     | data: 3   |
 * 	      +-----------+                           +-----------+
 * 	            |                                         |
 * 	            --------------> 2  equals 3 <--------------
 *
 * 	This is a simplअगरied schema, the complनिकासy varies depending
 * 	on the meta type. Obviously, the length of the data must also
 * 	be provided क्रम non-numeric types.
 *
 * 	Additionally, type dependent modअगरiers such as shअगरt चालकs
 * 	or mask may be applied to extend the functionaliy. As of now,
 * 	the variable length type supports shअगरting the byte string to
 * 	the right, eating up any number of octets and thus supporting
 * 	wildcard पूर्णांकerface name comparisons such as "ppp%" matching
 * 	ppp0..9.
 *
 * 	NOTE: Certain meta values depend on other subप्रणालीs and are
 * 	      only available अगर that subप्रणाली is enabled in the kernel.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/tc_ematch/tc_em_meta.h>
#समावेश <net/dst.h>
#समावेश <net/route.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/sock.h>

काष्ठा meta_obj अणु
	अचिन्हित दीर्घ		value;
	अचिन्हित पूर्णांक		len;
पूर्ण;

काष्ठा meta_value अणु
	काष्ठा tcf_meta_val	hdr;
	अचिन्हित दीर्घ		val;
	अचिन्हित पूर्णांक		len;
पूर्ण;

काष्ठा meta_match अणु
	काष्ठा meta_value	lvalue;
	काष्ठा meta_value	rvalue;
पूर्ण;

अटल अंतरभूत पूर्णांक meta_id(काष्ठा meta_value *v)
अणु
	वापस TCF_META_ID(v->hdr.kind);
पूर्ण

अटल अंतरभूत पूर्णांक meta_type(काष्ठा meta_value *v)
अणु
	वापस TCF_META_TYPE(v->hdr.kind);
पूर्ण

#घोषणा META_COLLECTOR(FUNC) अटल व्योम meta_##FUNC(काष्ठा sk_buff *skb, \
	काष्ठा tcf_pkt_info *info, काष्ठा meta_value *v, \
	काष्ठा meta_obj *dst, पूर्णांक *err)

/**************************************************************************
 * System status & misc
 **************************************************************************/

META_COLLECTOR(पूर्णांक_अक्रमom)
अणु
	get_अक्रमom_bytes(&dst->value, माप(dst->value));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fixed_loadavg(पूर्णांक load)
अणु
	पूर्णांक rnd_load = load + (FIXED_1/200);
	पूर्णांक rnd_frac = ((rnd_load & (FIXED_1-1)) * 100) >> FSHIFT;

	वापस ((rnd_load >> FSHIFT) * 100) + rnd_frac;
पूर्ण

META_COLLECTOR(पूर्णांक_loadavg_0)
अणु
	dst->value = fixed_loadavg(avenrun[0]);
पूर्ण

META_COLLECTOR(पूर्णांक_loadavg_1)
अणु
	dst->value = fixed_loadavg(avenrun[1]);
पूर्ण

META_COLLECTOR(पूर्णांक_loadavg_2)
अणु
	dst->value = fixed_loadavg(avenrun[2]);
पूर्ण

/**************************************************************************
 * Device names & indices
 **************************************************************************/

अटल अंतरभूत पूर्णांक पूर्णांक_dev(काष्ठा net_device *dev, काष्ठा meta_obj *dst)
अणु
	अगर (unlikely(dev == शून्य))
		वापस -1;

	dst->value = dev->अगरindex;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक var_dev(काष्ठा net_device *dev, काष्ठा meta_obj *dst)
अणु
	अगर (unlikely(dev == शून्य))
		वापस -1;

	dst->value = (अचिन्हित दीर्घ) dev->name;
	dst->len = म_माप(dev->name);
	वापस 0;
पूर्ण

META_COLLECTOR(पूर्णांक_dev)
अणु
	*err = पूर्णांक_dev(skb->dev, dst);
पूर्ण

META_COLLECTOR(var_dev)
अणु
	*err = var_dev(skb->dev, dst);
पूर्ण

/**************************************************************************
 * vlan tag
 **************************************************************************/

META_COLLECTOR(पूर्णांक_vlan_tag)
अणु
	अचिन्हित लघु tag;

	अगर (skb_vlan_tag_present(skb))
		dst->value = skb_vlan_tag_get(skb);
	अन्यथा अगर (!__vlan_get_tag(skb, &tag))
		dst->value = tag;
	अन्यथा
		*err = -1;
पूर्ण



/**************************************************************************
 * skb attributes
 **************************************************************************/

META_COLLECTOR(पूर्णांक_priority)
अणु
	dst->value = skb->priority;
पूर्ण

META_COLLECTOR(पूर्णांक_protocol)
अणु
	/* Let userspace take care of the byte ordering */
	dst->value = skb_protocol(skb, false);
पूर्ण

META_COLLECTOR(पूर्णांक_pkttype)
अणु
	dst->value = skb->pkt_type;
पूर्ण

META_COLLECTOR(पूर्णांक_pktlen)
अणु
	dst->value = skb->len;
पूर्ण

META_COLLECTOR(पूर्णांक_datalen)
अणु
	dst->value = skb->data_len;
पूर्ण

META_COLLECTOR(पूर्णांक_maclen)
अणु
	dst->value = skb->mac_len;
पूर्ण

META_COLLECTOR(पूर्णांक_rxhash)
अणु
	dst->value = skb_get_hash(skb);
पूर्ण

/**************************************************************************
 * Netfilter
 **************************************************************************/

META_COLLECTOR(पूर्णांक_mark)
अणु
	dst->value = skb->mark;
पूर्ण

/**************************************************************************
 * Traffic Control
 **************************************************************************/

META_COLLECTOR(पूर्णांक_tcindex)
अणु
	dst->value = skb->tc_index;
पूर्ण

/**************************************************************************
 * Routing
 **************************************************************************/

META_COLLECTOR(पूर्णांक_rtclassid)
अणु
	अगर (unlikely(skb_dst(skb) == शून्य))
		*err = -1;
	अन्यथा
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
		dst->value = skb_dst(skb)->tclassid;
#अन्यथा
		dst->value = 0;
#पूर्ण_अगर
पूर्ण

META_COLLECTOR(पूर्णांक_rtiअगर)
अणु
	अगर (unlikely(skb_rtable(skb) == शून्य))
		*err = -1;
	अन्यथा
		dst->value = inet_iअगर(skb);
पूर्ण

/**************************************************************************
 * Socket Attributes
 **************************************************************************/

#घोषणा skip_nonlocal(skb) \
	(unlikely(skb->sk == शून्य))

META_COLLECTOR(पूर्णांक_sk_family)
अणु
	अगर (skip_nonlocal(skb)) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = skb->sk->sk_family;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_state)
अणु
	अगर (skip_nonlocal(skb)) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = skb->sk->sk_state;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_reuse)
अणु
	अगर (skip_nonlocal(skb)) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = skb->sk->sk_reuse;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_bound_अगर)
अणु
	अगर (skip_nonlocal(skb)) अणु
		*err = -1;
		वापस;
	पूर्ण
	/* No error अगर bound_dev_अगर is 0, legal userspace check */
	dst->value = skb->sk->sk_bound_dev_अगर;
पूर्ण

META_COLLECTOR(var_sk_bound_अगर)
अणु
	अगर (skip_nonlocal(skb)) अणु
		*err = -1;
		वापस;
	पूर्ण

	अगर (skb->sk->sk_bound_dev_अगर == 0) अणु
		dst->value = (अचिन्हित दीर्घ) "any";
		dst->len = 3;
	पूर्ण अन्यथा अणु
		काष्ठा net_device *dev;

		rcu_पढ़ो_lock();
		dev = dev_get_by_index_rcu(sock_net(skb->sk),
					   skb->sk->sk_bound_dev_अगर);
		*err = var_dev(dev, dst);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

META_COLLECTOR(पूर्णांक_sk_refcnt)
अणु
	अगर (skip_nonlocal(skb)) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = refcount_पढ़ो(&skb->sk->sk_refcnt);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_rcvbuf)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_rcvbuf;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_shutकरोwn)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_shutकरोwn;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_proto)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_protocol;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_type)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_type;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_rmem_alloc)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk_rmem_alloc_get(sk);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_wmem_alloc)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk_wmem_alloc_get(sk);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_omem_alloc)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = atomic_पढ़ो(&sk->sk_omem_alloc);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_rcv_qlen)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_receive_queue.qlen;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_snd_qlen)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_ग_लिखो_queue.qlen;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_wmem_queued)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = READ_ONCE(sk->sk_wmem_queued);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_fwd_alloc)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_क्रमward_alloc;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_sndbuf)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_sndbuf;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_alloc)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = (__क्रमce पूर्णांक) sk->sk_allocation;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_hash)
अणु
	अगर (skip_nonlocal(skb)) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = skb->sk->sk_hash;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_lingerसमय)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_lingerसमय / HZ;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_err_qlen)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_error_queue.qlen;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_ack_bl)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = READ_ONCE(sk->sk_ack_backlog);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_max_ack_bl)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = READ_ONCE(sk->sk_max_ack_backlog);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_prio)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_priority;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_rcvlowat)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = READ_ONCE(sk->sk_rcvlowat);
पूर्ण

META_COLLECTOR(पूर्णांक_sk_rcvसमयo)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_rcvसमयo / HZ;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_sndसमयo)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_sndसमयo / HZ;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_sendmsg_off)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_frag.offset;
पूर्ण

META_COLLECTOR(पूर्णांक_sk_ग_लिखो_pend)
अणु
	स्थिर काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk) अणु
		*err = -1;
		वापस;
	पूर्ण
	dst->value = sk->sk_ग_लिखो_pending;
पूर्ण

/**************************************************************************
 * Meta value collectors assignment table
 **************************************************************************/

काष्ठा meta_ops अणु
	व्योम		(*get)(काष्ठा sk_buff *, काष्ठा tcf_pkt_info *,
			       काष्ठा meta_value *, काष्ठा meta_obj *, पूर्णांक *);
पूर्ण;

#घोषणा META_ID(name) TCF_META_ID_##name
#घोषणा META_FUNC(name) अणु .get = meta_##name पूर्ण

/* Meta value operations table listing all meta value collectors and
 * assigns them to a type and meta id. */
अटल काष्ठा meta_ops __meta_ops[TCF_META_TYPE_MAX + 1][TCF_META_ID_MAX + 1] = अणु
	[TCF_META_TYPE_VAR] = अणु
		[META_ID(DEV)]			= META_FUNC(var_dev),
		[META_ID(SK_BOUND_IF)] 		= META_FUNC(var_sk_bound_अगर),
	पूर्ण,
	[TCF_META_TYPE_INT] = अणु
		[META_ID(RANDOM)]		= META_FUNC(पूर्णांक_अक्रमom),
		[META_ID(LOADAVG_0)]		= META_FUNC(पूर्णांक_loadavg_0),
		[META_ID(LOADAVG_1)]		= META_FUNC(पूर्णांक_loadavg_1),
		[META_ID(LOADAVG_2)]		= META_FUNC(पूर्णांक_loadavg_2),
		[META_ID(DEV)]			= META_FUNC(पूर्णांक_dev),
		[META_ID(PRIORITY)]		= META_FUNC(पूर्णांक_priority),
		[META_ID(PROTOCOL)]		= META_FUNC(पूर्णांक_protocol),
		[META_ID(PKTTYPE)]		= META_FUNC(पूर्णांक_pkttype),
		[META_ID(PKTLEN)]		= META_FUNC(पूर्णांक_pktlen),
		[META_ID(DATALEN)]		= META_FUNC(पूर्णांक_datalen),
		[META_ID(MACLEN)]		= META_FUNC(पूर्णांक_maclen),
		[META_ID(NFMARK)]		= META_FUNC(पूर्णांक_mark),
		[META_ID(TCINDEX)]		= META_FUNC(पूर्णांक_tcindex),
		[META_ID(RTCLASSID)]		= META_FUNC(पूर्णांक_rtclassid),
		[META_ID(RTIIF)]		= META_FUNC(पूर्णांक_rtiअगर),
		[META_ID(SK_FAMILY)]		= META_FUNC(पूर्णांक_sk_family),
		[META_ID(SK_STATE)]		= META_FUNC(पूर्णांक_sk_state),
		[META_ID(SK_REUSE)]		= META_FUNC(पूर्णांक_sk_reuse),
		[META_ID(SK_BOUND_IF)]		= META_FUNC(पूर्णांक_sk_bound_अगर),
		[META_ID(SK_REFCNT)]		= META_FUNC(पूर्णांक_sk_refcnt),
		[META_ID(SK_RCVBUF)]		= META_FUNC(पूर्णांक_sk_rcvbuf),
		[META_ID(SK_SNDBUF)]		= META_FUNC(पूर्णांक_sk_sndbuf),
		[META_ID(SK_SHUTDOWN)]		= META_FUNC(पूर्णांक_sk_shutकरोwn),
		[META_ID(SK_PROTO)]		= META_FUNC(पूर्णांक_sk_proto),
		[META_ID(SK_TYPE)]		= META_FUNC(पूर्णांक_sk_type),
		[META_ID(SK_RMEM_ALLOC)]	= META_FUNC(पूर्णांक_sk_rmem_alloc),
		[META_ID(SK_WMEM_ALLOC)]	= META_FUNC(पूर्णांक_sk_wmem_alloc),
		[META_ID(SK_OMEM_ALLOC)]	= META_FUNC(पूर्णांक_sk_omem_alloc),
		[META_ID(SK_WMEM_QUEUED)]	= META_FUNC(पूर्णांक_sk_wmem_queued),
		[META_ID(SK_RCV_QLEN)]		= META_FUNC(पूर्णांक_sk_rcv_qlen),
		[META_ID(SK_SND_QLEN)]		= META_FUNC(पूर्णांक_sk_snd_qlen),
		[META_ID(SK_ERR_QLEN)]		= META_FUNC(पूर्णांक_sk_err_qlen),
		[META_ID(SK_FORWARD_ALLOCS)]	= META_FUNC(पूर्णांक_sk_fwd_alloc),
		[META_ID(SK_ALLOCS)]		= META_FUNC(पूर्णांक_sk_alloc),
		[META_ID(SK_HASH)]		= META_FUNC(पूर्णांक_sk_hash),
		[META_ID(SK_LINGERTIME)]	= META_FUNC(पूर्णांक_sk_lingerसमय),
		[META_ID(SK_ACK_BACKLOG)]	= META_FUNC(पूर्णांक_sk_ack_bl),
		[META_ID(SK_MAX_ACK_BACKLOG)]	= META_FUNC(पूर्णांक_sk_max_ack_bl),
		[META_ID(SK_PRIO)]		= META_FUNC(पूर्णांक_sk_prio),
		[META_ID(SK_RCVLOWAT)]		= META_FUNC(पूर्णांक_sk_rcvlowat),
		[META_ID(SK_RCVTIMEO)]		= META_FUNC(पूर्णांक_sk_rcvसमयo),
		[META_ID(SK_SNDTIMEO)]		= META_FUNC(पूर्णांक_sk_sndसमयo),
		[META_ID(SK_SENDMSG_OFF)]	= META_FUNC(पूर्णांक_sk_sendmsg_off),
		[META_ID(SK_WRITE_PENDING)]	= META_FUNC(पूर्णांक_sk_ग_लिखो_pend),
		[META_ID(VLAN_TAG)]		= META_FUNC(पूर्णांक_vlan_tag),
		[META_ID(RXHASH)]		= META_FUNC(पूर्णांक_rxhash),
	पूर्ण
पूर्ण;

अटल अंतरभूत काष्ठा meta_ops *meta_ops(काष्ठा meta_value *val)
अणु
	वापस &__meta_ops[meta_type(val)][meta_id(val)];
पूर्ण

/**************************************************************************
 * Type specअगरic operations क्रम TCF_META_TYPE_VAR
 **************************************************************************/

अटल पूर्णांक meta_var_compare(काष्ठा meta_obj *a, काष्ठा meta_obj *b)
अणु
	पूर्णांक r = a->len - b->len;

	अगर (r == 0)
		r = स_भेद((व्योम *) a->value, (व्योम *) b->value, a->len);

	वापस r;
पूर्ण

अटल पूर्णांक meta_var_change(काष्ठा meta_value *dst, काष्ठा nlattr *nla)
अणु
	पूर्णांक len = nla_len(nla);

	dst->val = (अचिन्हित दीर्घ)kmemdup(nla_data(nla), len, GFP_KERNEL);
	अगर (dst->val == 0UL)
		वापस -ENOMEM;
	dst->len = len;
	वापस 0;
पूर्ण

अटल व्योम meta_var_destroy(काष्ठा meta_value *v)
अणु
	kमुक्त((व्योम *) v->val);
पूर्ण

अटल व्योम meta_var_apply_extras(काष्ठा meta_value *v,
				  काष्ठा meta_obj *dst)
अणु
	पूर्णांक shअगरt = v->hdr.shअगरt;

	अगर (shअगरt && shअगरt < dst->len)
		dst->len -= shअगरt;
पूर्ण

अटल पूर्णांक meta_var_dump(काष्ठा sk_buff *skb, काष्ठा meta_value *v, पूर्णांक tlv)
अणु
	अगर (v->val && v->len &&
	    nla_put(skb, tlv, v->len, (व्योम *) v->val))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

/**************************************************************************
 * Type specअगरic operations क्रम TCF_META_TYPE_INT
 **************************************************************************/

अटल पूर्णांक meta_पूर्णांक_compare(काष्ठा meta_obj *a, काष्ठा meta_obj *b)
अणु
	/* Let gcc optimize it, the unlikely is not really based on
	 * some numbers but jump मुक्त code क्रम mismatches seems
	 * more logical. */
	अगर (unlikely(a->value == b->value))
		वापस 0;
	अन्यथा अगर (a->value < b->value)
		वापस -1;
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक meta_पूर्णांक_change(काष्ठा meta_value *dst, काष्ठा nlattr *nla)
अणु
	अगर (nla_len(nla) >= माप(अचिन्हित दीर्घ)) अणु
		dst->val = *(अचिन्हित दीर्घ *) nla_data(nla);
		dst->len = माप(अचिन्हित दीर्घ);
	पूर्ण अन्यथा अगर (nla_len(nla) == माप(u32)) अणु
		dst->val = nla_get_u32(nla);
		dst->len = माप(u32);
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम meta_पूर्णांक_apply_extras(काष्ठा meta_value *v,
				  काष्ठा meta_obj *dst)
अणु
	अगर (v->hdr.shअगरt)
		dst->value >>= v->hdr.shअगरt;

	अगर (v->val)
		dst->value &= v->val;
पूर्ण

अटल पूर्णांक meta_पूर्णांक_dump(काष्ठा sk_buff *skb, काष्ठा meta_value *v, पूर्णांक tlv)
अणु
	अगर (v->len == माप(अचिन्हित दीर्घ)) अणु
		अगर (nla_put(skb, tlv, माप(अचिन्हित दीर्घ), &v->val))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अगर (v->len == माप(u32)) अणु
		अगर (nla_put_u32(skb, tlv, v->val))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

/**************************************************************************
 * Type specअगरic operations table
 **************************************************************************/

काष्ठा meta_type_ops अणु
	व्योम	(*destroy)(काष्ठा meta_value *);
	पूर्णांक	(*compare)(काष्ठा meta_obj *, काष्ठा meta_obj *);
	पूर्णांक	(*change)(काष्ठा meta_value *, काष्ठा nlattr *);
	व्योम	(*apply_extras)(काष्ठा meta_value *, काष्ठा meta_obj *);
	पूर्णांक	(*dump)(काष्ठा sk_buff *, काष्ठा meta_value *, पूर्णांक);
पूर्ण;

अटल स्थिर काष्ठा meta_type_ops __meta_type_ops[TCF_META_TYPE_MAX + 1] = अणु
	[TCF_META_TYPE_VAR] = अणु
		.destroy = meta_var_destroy,
		.compare = meta_var_compare,
		.change = meta_var_change,
		.apply_extras = meta_var_apply_extras,
		.dump = meta_var_dump
	पूर्ण,
	[TCF_META_TYPE_INT] = अणु
		.compare = meta_पूर्णांक_compare,
		.change = meta_पूर्णांक_change,
		.apply_extras = meta_पूर्णांक_apply_extras,
		.dump = meta_पूर्णांक_dump
	पूर्ण
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा meta_type_ops *meta_type_ops(काष्ठा meta_value *v)
अणु
	वापस &__meta_type_ops[meta_type(v)];
पूर्ण

/**************************************************************************
 * Core
 **************************************************************************/

अटल पूर्णांक meta_get(काष्ठा sk_buff *skb, काष्ठा tcf_pkt_info *info,
		    काष्ठा meta_value *v, काष्ठा meta_obj *dst)
अणु
	पूर्णांक err = 0;

	अगर (meta_id(v) == TCF_META_ID_VALUE) अणु
		dst->value = v->val;
		dst->len = v->len;
		वापस 0;
	पूर्ण

	meta_ops(v)->get(skb, info, v, dst, &err);
	अगर (err < 0)
		वापस err;

	अगर (meta_type_ops(v)->apply_extras)
		meta_type_ops(v)->apply_extras(v, dst);

	वापस 0;
पूर्ण

अटल पूर्णांक em_meta_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *m,
			 काष्ठा tcf_pkt_info *info)
अणु
	पूर्णांक r;
	काष्ठा meta_match *meta = (काष्ठा meta_match *) m->data;
	काष्ठा meta_obj l_value, r_value;

	अगर (meta_get(skb, info, &meta->lvalue, &l_value) < 0 ||
	    meta_get(skb, info, &meta->rvalue, &r_value) < 0)
		वापस 0;

	r = meta_type_ops(&meta->lvalue)->compare(&l_value, &r_value);

	चयन (meta->lvalue.hdr.op) अणु
	हाल TCF_EM_OPND_EQ:
		वापस !r;
	हाल TCF_EM_OPND_LT:
		वापस r < 0;
	हाल TCF_EM_OPND_GT:
		वापस r > 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meta_delete(काष्ठा meta_match *meta)
अणु
	अगर (meta) अणु
		स्थिर काष्ठा meta_type_ops *ops = meta_type_ops(&meta->lvalue);

		अगर (ops && ops->destroy) अणु
			ops->destroy(&meta->lvalue);
			ops->destroy(&meta->rvalue);
		पूर्ण
	पूर्ण

	kमुक्त(meta);
पूर्ण

अटल अंतरभूत पूर्णांक meta_change_data(काष्ठा meta_value *dst, काष्ठा nlattr *nla)
अणु
	अगर (nla) अणु
		अगर (nla_len(nla) == 0)
			वापस -EINVAL;

		वापस meta_type_ops(dst)->change(dst, nla);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक meta_is_supported(काष्ठा meta_value *val)
अणु
	वापस !meta_id(val) || meta_ops(val)->get;
पूर्ण

अटल स्थिर काष्ठा nla_policy meta_policy[TCA_EM_META_MAX + 1] = अणु
	[TCA_EM_META_HDR]	= अणु .len = माप(काष्ठा tcf_meta_hdr) पूर्ण,
पूर्ण;

अटल पूर्णांक em_meta_change(काष्ठा net *net, व्योम *data, पूर्णांक len,
			  काष्ठा tcf_ematch *m)
अणु
	पूर्णांक err;
	काष्ठा nlattr *tb[TCA_EM_META_MAX + 1];
	काष्ठा tcf_meta_hdr *hdr;
	काष्ठा meta_match *meta = शून्य;

	err = nla_parse_deprecated(tb, TCA_EM_META_MAX, data, len,
				   meta_policy, शून्य);
	अगर (err < 0)
		जाओ errout;

	err = -EINVAL;
	अगर (tb[TCA_EM_META_HDR] == शून्य)
		जाओ errout;
	hdr = nla_data(tb[TCA_EM_META_HDR]);

	अगर (TCF_META_TYPE(hdr->left.kind) != TCF_META_TYPE(hdr->right.kind) ||
	    TCF_META_TYPE(hdr->left.kind) > TCF_META_TYPE_MAX ||
	    TCF_META_ID(hdr->left.kind) > TCF_META_ID_MAX ||
	    TCF_META_ID(hdr->right.kind) > TCF_META_ID_MAX)
		जाओ errout;

	meta = kzalloc(माप(*meta), GFP_KERNEL);
	अगर (meta == शून्य) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण

	स_नकल(&meta->lvalue.hdr, &hdr->left, माप(hdr->left));
	स_नकल(&meta->rvalue.hdr, &hdr->right, माप(hdr->right));

	अगर (!meta_is_supported(&meta->lvalue) ||
	    !meta_is_supported(&meta->rvalue)) अणु
		err = -EOPNOTSUPP;
		जाओ errout;
	पूर्ण

	अगर (meta_change_data(&meta->lvalue, tb[TCA_EM_META_LVALUE]) < 0 ||
	    meta_change_data(&meta->rvalue, tb[TCA_EM_META_RVALUE]) < 0)
		जाओ errout;

	m->datalen = माप(*meta);
	m->data = (अचिन्हित दीर्घ) meta;

	err = 0;
errout:
	अगर (err && meta)
		meta_delete(meta);
	वापस err;
पूर्ण

अटल व्योम em_meta_destroy(काष्ठा tcf_ematch *m)
अणु
	अगर (m)
		meta_delete((काष्ठा meta_match *) m->data);
पूर्ण

अटल पूर्णांक em_meta_dump(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em)
अणु
	काष्ठा meta_match *meta = (काष्ठा meta_match *) em->data;
	काष्ठा tcf_meta_hdr hdr;
	स्थिर काष्ठा meta_type_ops *ops;

	स_रखो(&hdr, 0, माप(hdr));
	स_नकल(&hdr.left, &meta->lvalue.hdr, माप(hdr.left));
	स_नकल(&hdr.right, &meta->rvalue.hdr, माप(hdr.right));

	अगर (nla_put(skb, TCA_EM_META_HDR, माप(hdr), &hdr))
		जाओ nla_put_failure;

	ops = meta_type_ops(&meta->lvalue);
	अगर (ops->dump(skb, &meta->lvalue, TCA_EM_META_LVALUE) < 0 ||
	    ops->dump(skb, &meta->rvalue, TCA_EM_META_RVALUE) < 0)
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा tcf_ematch_ops em_meta_ops = अणु
	.kind	  = TCF_EM_META,
	.change	  = em_meta_change,
	.match	  = em_meta_match,
	.destroy  = em_meta_destroy,
	.dump	  = em_meta_dump,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_meta_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_meta(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_meta_ops);
पूर्ण

अटल व्योम __निकास निकास_em_meta(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_meta_ops);
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_em_meta);
module_निकास(निकास_em_meta);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_META);
