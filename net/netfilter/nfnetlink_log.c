<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is a module which is used क्रम logging packets to userspace via
 * nfetlink.
 *
 * (C) 2005 by Harald Welte <laक्रमge@netfilter.org>
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 *
 * Based on the old ipv4-only ipt_ULOG.c:
 * (C) 2000-2004 by Harald Welte <laक्रमge@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <net/netlink.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_log.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/security.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>


#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
#समावेश "../bridge/br_private.h"
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर

#घोषणा NFULNL_COPY_DISABLED	0xff
#घोषणा NFULNL_NLबफ_मान_DEFAULT	NLMSG_GOODSIZE
#घोषणा NFULNL_TIMEOUT_DEFAULT 	100	/* every second */
#घोषणा NFULNL_QTHRESH_DEFAULT 	100	/* 100 packets */
/* max packet size is limited by 16-bit काष्ठा nfattr nfa_len field */
#घोषणा NFULNL_COPY_RANGE_MAX	(0xFFFF - NLA_HDRLEN)

#घोषणा PRINTR(x, args...)	करो अणु अगर (net_ratelimit()) \
				     prपूर्णांकk(x, ## args); पूर्ण जबतक (0);

काष्ठा nfulnl_instance अणु
	काष्ठा hlist_node hlist;	/* global list of instances */
	spinlock_t lock;
	refcount_t use;			/* use count */

	अचिन्हित पूर्णांक qlen;		/* number of nlmsgs in skb */
	काष्ठा sk_buff *skb;		/* pre-allocatd skb */
	काष्ठा समयr_list समयr;
	काष्ठा net *net;
	काष्ठा user_namespace *peer_user_ns;	/* User namespace of the peer process */
	u32 peer_portid;		/* PORTID of the peer process */

	/* configurable parameters */
	अचिन्हित पूर्णांक flushसमयout;	/* समयout until queue flush */
	अचिन्हित पूर्णांक nlbufsiz;		/* netlink buffer allocation size */
	अचिन्हित पूर्णांक qthreshold;	/* threshold of the queue */
	u_पूर्णांक32_t copy_range;
	u_पूर्णांक32_t seq;			/* instance-local sequential counter */
	u_पूर्णांक16_t group_num;		/* number of this queue */
	u_पूर्णांक16_t flags;
	u_पूर्णांक8_t copy_mode;
	काष्ठा rcu_head rcu;
पूर्ण;

#घोषणा INSTANCE_BUCKETS	16

अटल अचिन्हित पूर्णांक nfnl_log_net_id __पढ़ो_mostly;

काष्ठा nfnl_log_net अणु
	spinlock_t instances_lock;
	काष्ठा hlist_head instance_table[INSTANCE_BUCKETS];
	atomic_t global_seq;
पूर्ण;

अटल काष्ठा nfnl_log_net *nfnl_log_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, nfnl_log_net_id);
पूर्ण

अटल अंतरभूत u_पूर्णांक8_t instance_hashfn(u_पूर्णांक16_t group_num)
अणु
	वापस ((group_num & 0xff) % INSTANCE_BUCKETS);
पूर्ण

अटल काष्ठा nfulnl_instance *
__instance_lookup(काष्ठा nfnl_log_net *log, u_पूर्णांक16_t group_num)
अणु
	काष्ठा hlist_head *head;
	काष्ठा nfulnl_instance *inst;

	head = &log->instance_table[instance_hashfn(group_num)];
	hlist_क्रम_each_entry_rcu(inst, head, hlist) अणु
		अगर (inst->group_num == group_num)
			वापस inst;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
instance_get(काष्ठा nfulnl_instance *inst)
अणु
	refcount_inc(&inst->use);
पूर्ण

अटल काष्ठा nfulnl_instance *
instance_lookup_get(काष्ठा nfnl_log_net *log, u_पूर्णांक16_t group_num)
अणु
	काष्ठा nfulnl_instance *inst;

	rcu_पढ़ो_lock_bh();
	inst = __instance_lookup(log, group_num);
	अगर (inst && !refcount_inc_not_zero(&inst->use))
		inst = शून्य;
	rcu_पढ़ो_unlock_bh();

	वापस inst;
पूर्ण

अटल व्योम nfulnl_instance_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा nfulnl_instance *inst =
		container_of(head, काष्ठा nfulnl_instance, rcu);

	put_net(inst->net);
	kमुक्त(inst);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम
instance_put(काष्ठा nfulnl_instance *inst)
अणु
	अगर (inst && refcount_dec_and_test(&inst->use))
		call_rcu(&inst->rcu, nfulnl_instance_मुक्त_rcu);
पूर्ण

अटल व्योम nfulnl_समयr(काष्ठा समयr_list *t);

अटल काष्ठा nfulnl_instance *
instance_create(काष्ठा net *net, u_पूर्णांक16_t group_num,
		u32 portid, काष्ठा user_namespace *user_ns)
अणु
	काष्ठा nfulnl_instance *inst;
	काष्ठा nfnl_log_net *log = nfnl_log_pernet(net);
	पूर्णांक err;

	spin_lock_bh(&log->instances_lock);
	अगर (__instance_lookup(log, group_num)) अणु
		err = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	inst = kzalloc(माप(*inst), GFP_ATOMIC);
	अगर (!inst) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	अगर (!try_module_get(THIS_MODULE)) अणु
		kमुक्त(inst);
		err = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	INIT_HLIST_NODE(&inst->hlist);
	spin_lock_init(&inst->lock);
	/* needs to be two, since we _put() after creation */
	refcount_set(&inst->use, 2);

	समयr_setup(&inst->समयr, nfulnl_समयr, 0);

	inst->net = get_net(net);
	inst->peer_user_ns = user_ns;
	inst->peer_portid = portid;
	inst->group_num = group_num;

	inst->qthreshold 	= NFULNL_QTHRESH_DEFAULT;
	inst->flushसमयout 	= NFULNL_TIMEOUT_DEFAULT;
	inst->nlbufsiz 		= NFULNL_NLबफ_मान_DEFAULT;
	inst->copy_mode 	= NFULNL_COPY_PACKET;
	inst->copy_range 	= NFULNL_COPY_RANGE_MAX;

	hlist_add_head_rcu(&inst->hlist,
		       &log->instance_table[instance_hashfn(group_num)]);


	spin_unlock_bh(&log->instances_lock);

	वापस inst;

out_unlock:
	spin_unlock_bh(&log->instances_lock);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम __nfulnl_flush(काष्ठा nfulnl_instance *inst);

/* called with BH disabled */
अटल व्योम
__instance_destroy(काष्ठा nfulnl_instance *inst)
अणु
	/* first pull it out of the global list */
	hlist_del_rcu(&inst->hlist);

	/* then flush all pending packets from skb */

	spin_lock(&inst->lock);

	/* lockless पढ़ोers wont be able to use us */
	inst->copy_mode = NFULNL_COPY_DISABLED;

	अगर (inst->skb)
		__nfulnl_flush(inst);
	spin_unlock(&inst->lock);

	/* and finally put the refcount */
	instance_put(inst);
पूर्ण

अटल अंतरभूत व्योम
instance_destroy(काष्ठा nfnl_log_net *log,
		 काष्ठा nfulnl_instance *inst)
अणु
	spin_lock_bh(&log->instances_lock);
	__instance_destroy(inst);
	spin_unlock_bh(&log->instances_lock);
पूर्ण

अटल पूर्णांक
nfulnl_set_mode(काष्ठा nfulnl_instance *inst, u_पूर्णांक8_t mode,
		  अचिन्हित पूर्णांक range)
अणु
	पूर्णांक status = 0;

	spin_lock_bh(&inst->lock);

	चयन (mode) अणु
	हाल NFULNL_COPY_NONE:
	हाल NFULNL_COPY_META:
		inst->copy_mode = mode;
		inst->copy_range = 0;
		अवरोध;

	हाल NFULNL_COPY_PACKET:
		inst->copy_mode = mode;
		अगर (range == 0)
			range = NFULNL_COPY_RANGE_MAX;
		inst->copy_range = min_t(अचिन्हित पूर्णांक,
					 range, NFULNL_COPY_RANGE_MAX);
		अवरोध;

	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock_bh(&inst->lock);

	वापस status;
पूर्ण

अटल पूर्णांक
nfulnl_set_nlbufsiz(काष्ठा nfulnl_instance *inst, u_पूर्णांक32_t nlbufsiz)
अणु
	पूर्णांक status;

	spin_lock_bh(&inst->lock);
	अगर (nlbufsiz < NFULNL_NLबफ_मान_DEFAULT)
		status = -दुस्फल;
	अन्यथा अगर (nlbufsiz > 131072)
		status = -दुस्फल;
	अन्यथा अणु
		inst->nlbufsiz = nlbufsiz;
		status = 0;
	पूर्ण
	spin_unlock_bh(&inst->lock);

	वापस status;
पूर्ण

अटल व्योम
nfulnl_set_समयout(काष्ठा nfulnl_instance *inst, u_पूर्णांक32_t समयout)
अणु
	spin_lock_bh(&inst->lock);
	inst->flushसमयout = समयout;
	spin_unlock_bh(&inst->lock);
पूर्ण

अटल व्योम
nfulnl_set_qthresh(काष्ठा nfulnl_instance *inst, u_पूर्णांक32_t qthresh)
अणु
	spin_lock_bh(&inst->lock);
	inst->qthreshold = qthresh;
	spin_unlock_bh(&inst->lock);
पूर्ण

अटल पूर्णांक
nfulnl_set_flags(काष्ठा nfulnl_instance *inst, u_पूर्णांक16_t flags)
अणु
	spin_lock_bh(&inst->lock);
	inst->flags = flags;
	spin_unlock_bh(&inst->lock);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
nfulnl_alloc_skb(काष्ठा net *net, u32 peer_portid, अचिन्हित पूर्णांक inst_size,
		 अचिन्हित पूर्णांक pkt_size)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक n;

	/* alloc skb which should be big enough क्रम a whole multipart
	 * message.  WARNING: has to be <= 128k due to slab restrictions */

	n = max(inst_size, pkt_size);
	skb = alloc_skb(n, GFP_ATOMIC | __GFP_NOWARN);
	अगर (!skb) अणु
		अगर (n > pkt_size) अणु
			/* try to allocate only as much as we need क्रम current
			 * packet */

			skb = alloc_skb(pkt_size, GFP_ATOMIC);
		पूर्ण
	पूर्ण

	वापस skb;
पूर्ण

अटल व्योम
__nfulnl_send(काष्ठा nfulnl_instance *inst)
अणु
	अगर (inst->qlen > 1) अणु
		काष्ठा nlmsghdr *nlh = nlmsg_put(inst->skb, 0, 0,
						 NLMSG_DONE,
						 माप(काष्ठा nfgenmsg),
						 0);
		अगर (WARN_ONCE(!nlh, "bad nlskb size: %u, tailroom %d\n",
			      inst->skb->len, skb_tailroom(inst->skb))) अणु
			kमुक्त_skb(inst->skb);
			जाओ out;
		पूर्ण
	पूर्ण
	nfnetlink_unicast(inst->skb, inst->net, inst->peer_portid);
out:
	inst->qlen = 0;
	inst->skb = शून्य;
पूर्ण

अटल व्योम
__nfulnl_flush(काष्ठा nfulnl_instance *inst)
अणु
	/* समयr holds a reference */
	अगर (del_समयr(&inst->समयr))
		instance_put(inst);
	अगर (inst->skb)
		__nfulnl_send(inst);
पूर्ण

अटल व्योम
nfulnl_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा nfulnl_instance *inst = from_समयr(inst, t, समयr);

	spin_lock_bh(&inst->lock);
	अगर (inst->skb)
		__nfulnl_send(inst);
	spin_unlock_bh(&inst->lock);
	instance_put(inst);
पूर्ण

अटल u32 nfulnl_get_bridge_size(स्थिर काष्ठा sk_buff *skb)
अणु
	u32 size = 0;

	अगर (!skb_mac_header_was_set(skb))
		वापस 0;

	अगर (skb_vlan_tag_present(skb)) अणु
		size += nla_total_size(0); /* nested */
		size += nla_total_size(माप(u16)); /* id */
		size += nla_total_size(माप(u16)); /* tag */
	पूर्ण

	अगर (skb->network_header > skb->mac_header)
		size += nla_total_size(skb->network_header - skb->mac_header);

	वापस size;
पूर्ण

अटल पूर्णांक nfulnl_put_bridge(काष्ठा nfulnl_instance *inst, स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (!skb_mac_header_was_set(skb))
		वापस 0;

	अगर (skb_vlan_tag_present(skb)) अणु
		काष्ठा nlattr *nest;

		nest = nla_nest_start(inst->skb, NFULA_VLAN);
		अगर (!nest)
			जाओ nla_put_failure;

		अगर (nla_put_be16(inst->skb, NFULA_VLAN_TCI, htons(skb->vlan_tci)) ||
		    nla_put_be16(inst->skb, NFULA_VLAN_PROTO, skb->vlan_proto))
			जाओ nla_put_failure;

		nla_nest_end(inst->skb, nest);
	पूर्ण

	अगर (skb->mac_header < skb->network_header) अणु
		पूर्णांक len = (पूर्णांक)(skb->network_header - skb->mac_header);

		अगर (nla_put(inst->skb, NFULA_L2HDR, len, skb_mac_header(skb)))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

/* This is an अंतरभूत function, we करोn't really care about a दीर्घ
 * list of arguments */
अटल अंतरभूत पूर्णांक
__build_packet_message(काष्ठा nfnl_log_net *log,
			काष्ठा nfulnl_instance *inst,
			स्थिर काष्ठा sk_buff *skb,
			अचिन्हित पूर्णांक data_len,
			u_पूर्णांक8_t pf,
			अचिन्हित पूर्णांक hooknum,
			स्थिर काष्ठा net_device *indev,
			स्थिर काष्ठा net_device *outdev,
			स्थिर अक्षर *prefix, अचिन्हित पूर्णांक plen,
			स्थिर काष्ठा nfnl_ct_hook *nfnl_ct,
			काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	काष्ठा nfulnl_msg_packet_hdr pmsg;
	काष्ठा nlmsghdr *nlh;
	sk_buff_data_t old_tail = inst->skb->tail;
	काष्ठा sock *sk;
	स्थिर अचिन्हित अक्षर *hwhdrp;

	nlh = nfnl_msg_put(inst->skb, 0, 0,
			   nfnl_msg_type(NFNL_SUBSYS_ULOG, NFULNL_MSG_PACKET),
			   0, pf, NFNETLINK_V0, htons(inst->group_num));
	अगर (!nlh)
		वापस -1;

	स_रखो(&pmsg, 0, माप(pmsg));
	pmsg.hw_protocol	= skb->protocol;
	pmsg.hook		= hooknum;

	अगर (nla_put(inst->skb, NFULA_PACKET_HDR, माप(pmsg), &pmsg))
		जाओ nla_put_failure;

	अगर (prefix &&
	    nla_put(inst->skb, NFULA_PREFIX, plen, prefix))
		जाओ nla_put_failure;

	अगर (indev) अणु
#अगर !IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		अगर (nla_put_be32(inst->skb, NFULA_IFINDEX_INDEV,
				 htonl(indev->अगरindex)))
			जाओ nla_put_failure;
#अन्यथा
		अगर (pf == PF_BRIDGE) अणु
			/* Case 1: outdev is physical input device, we need to
			 * look क्रम bridge group (when called from
			 * netfilter_bridge) */
			अगर (nla_put_be32(inst->skb, NFULA_IFINDEX_PHYSINDEV,
					 htonl(indev->अगरindex)) ||
			/* this is the bridge group "brX" */
			/* rcu_पढ़ो_lock()ed by nf_hook_thresh or
			 * nf_log_packet.
			 */
			    nla_put_be32(inst->skb, NFULA_IFINDEX_INDEV,
					 htonl(br_port_get_rcu(indev)->br->dev->अगरindex)))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अणु
			काष्ठा net_device *physindev;

			/* Case 2: indev is bridge group, we need to look क्रम
			 * physical device (when called from ipv4) */
			अगर (nla_put_be32(inst->skb, NFULA_IFINDEX_INDEV,
					 htonl(indev->अगरindex)))
				जाओ nla_put_failure;

			physindev = nf_bridge_get_physindev(skb);
			अगर (physindev &&
			    nla_put_be32(inst->skb, NFULA_IFINDEX_PHYSINDEV,
					 htonl(physindev->अगरindex)))
				जाओ nla_put_failure;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (outdev) अणु
#अगर !IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		अगर (nla_put_be32(inst->skb, NFULA_IFINDEX_OUTDEV,
				 htonl(outdev->अगरindex)))
			जाओ nla_put_failure;
#अन्यथा
		अगर (pf == PF_BRIDGE) अणु
			/* Case 1: outdev is physical output device, we need to
			 * look क्रम bridge group (when called from
			 * netfilter_bridge) */
			अगर (nla_put_be32(inst->skb, NFULA_IFINDEX_PHYSOUTDEV,
					 htonl(outdev->अगरindex)) ||
			/* this is the bridge group "brX" */
			/* rcu_पढ़ो_lock()ed by nf_hook_thresh or
			 * nf_log_packet.
			 */
			    nla_put_be32(inst->skb, NFULA_IFINDEX_OUTDEV,
					 htonl(br_port_get_rcu(outdev)->br->dev->अगरindex)))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अणु
			काष्ठा net_device *physoutdev;

			/* Case 2: indev is a bridge group, we need to look
			 * क्रम physical device (when called from ipv4) */
			अगर (nla_put_be32(inst->skb, NFULA_IFINDEX_OUTDEV,
					 htonl(outdev->अगरindex)))
				जाओ nla_put_failure;

			physoutdev = nf_bridge_get_physoutdev(skb);
			अगर (physoutdev &&
			    nla_put_be32(inst->skb, NFULA_IFINDEX_PHYSOUTDEV,
					 htonl(physoutdev->अगरindex)))
				जाओ nla_put_failure;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (skb->mark &&
	    nla_put_be32(inst->skb, NFULA_MARK, htonl(skb->mark)))
		जाओ nla_put_failure;

	अगर (indev && skb->dev &&
	    skb->mac_header != skb->network_header) अणु
		काष्ठा nfulnl_msg_packet_hw phw;
		पूर्णांक len;

		स_रखो(&phw, 0, माप(phw));
		len = dev_parse_header(skb, phw.hw_addr);
		अगर (len > 0) अणु
			phw.hw_addrlen = htons(len);
			अगर (nla_put(inst->skb, NFULA_HWADDR, माप(phw), &phw))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (indev && skb_mac_header_was_set(skb)) अणु
		अगर (nla_put_be16(inst->skb, NFULA_HWTYPE, htons(skb->dev->type)) ||
		    nla_put_be16(inst->skb, NFULA_HWLEN,
				 htons(skb->dev->hard_header_len)))
			जाओ nla_put_failure;

		hwhdrp = skb_mac_header(skb);

		अगर (skb->dev->type == ARPHRD_SIT)
			hwhdrp -= ETH_HLEN;

		अगर (hwhdrp >= skb->head &&
		    nla_put(inst->skb, NFULA_HWHEADER,
			    skb->dev->hard_header_len, hwhdrp))
			जाओ nla_put_failure;
	पूर्ण

	अगर (hooknum <= NF_INET_FORWARD && skb->tstamp) अणु
		काष्ठा nfulnl_msg_packet_बारtamp ts;
		काष्ठा बारpec64 kts = kसमय_प्रकारo_बारpec64(skb->tstamp);
		ts.sec = cpu_to_be64(kts.tv_sec);
		ts.usec = cpu_to_be64(kts.tv_nsec / NSEC_PER_USEC);

		अगर (nla_put(inst->skb, NFULA_TIMESTAMP, माप(ts), &ts))
			जाओ nla_put_failure;
	पूर्ण

	/* UID */
	sk = skb->sk;
	अगर (sk && sk_fullsock(sk)) अणु
		पढ़ो_lock_bh(&sk->sk_callback_lock);
		अगर (sk->sk_socket && sk->sk_socket->file) अणु
			काष्ठा file *file = sk->sk_socket->file;
			स्थिर काष्ठा cred *cred = file->f_cred;
			काष्ठा user_namespace *user_ns = inst->peer_user_ns;
			__be32 uid = htonl(from_kuid_munged(user_ns, cred->fsuid));
			__be32 gid = htonl(from_kgid_munged(user_ns, cred->fsgid));
			पढ़ो_unlock_bh(&sk->sk_callback_lock);
			अगर (nla_put_be32(inst->skb, NFULA_UID, uid) ||
			    nla_put_be32(inst->skb, NFULA_GID, gid))
				जाओ nla_put_failure;
		पूर्ण अन्यथा
			पढ़ो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण

	/* local sequence number */
	अगर ((inst->flags & NFULNL_CFG_F_SEQ) &&
	    nla_put_be32(inst->skb, NFULA_SEQ, htonl(inst->seq++)))
		जाओ nla_put_failure;

	/* global sequence number */
	अगर ((inst->flags & NFULNL_CFG_F_SEQ_GLOBAL) &&
	    nla_put_be32(inst->skb, NFULA_SEQ_GLOBAL,
			 htonl(atomic_inc_वापस(&log->global_seq))))
		जाओ nla_put_failure;

	अगर (ct && nfnl_ct->build(inst->skb, ct, ctinfo,
				 NFULA_CT, NFULA_CT_INFO) < 0)
		जाओ nla_put_failure;

	अगर ((pf == NFPROTO_NETDEV || pf == NFPROTO_BRIDGE) &&
	    nfulnl_put_bridge(inst, skb) < 0)
		जाओ nla_put_failure;

	अगर (data_len) अणु
		काष्ठा nlattr *nla;
		पूर्णांक size = nla_attr_size(data_len);

		अगर (skb_tailroom(inst->skb) < nla_total_size(data_len))
			जाओ nla_put_failure;

		nla = skb_put(inst->skb, nla_total_size(data_len));
		nla->nla_type = NFULA_PAYLOAD;
		nla->nla_len = size;

		अगर (skb_copy_bits(skb, 0, nla_data(nla), data_len))
			BUG();
	पूर्ण

	nlh->nlmsg_len = inst->skb->tail - old_tail;
	वापस 0;

nla_put_failure:
	PRINTR(KERN_ERR "nfnetlink_log: error creating log nlmsg\n");
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nf_loginfo शेष_loginfo = अणु
	.type =		NF_LOG_TYPE_ULOG,
	.u = अणु
		.ulog = अणु
			.copy_len	= 0xffff,
			.group		= 0,
			.qthreshold	= 1,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* log handler क्रम पूर्णांकernal netfilter logging api */
अटल व्योम
nfulnl_log_packet(काष्ठा net *net,
		  u_पूर्णांक8_t pf,
		  अचिन्हित पूर्णांक hooknum,
		  स्थिर काष्ठा sk_buff *skb,
		  स्थिर काष्ठा net_device *in,
		  स्थिर काष्ठा net_device *out,
		  स्थिर काष्ठा nf_loginfo *li_user,
		  स्थिर अक्षर *prefix)
अणु
	माप_प्रकार size;
	अचिन्हित पूर्णांक data_len;
	काष्ठा nfulnl_instance *inst;
	स्थिर काष्ठा nf_loginfo *li;
	अचिन्हित पूर्णांक qthreshold;
	अचिन्हित पूर्णांक plen = 0;
	काष्ठा nfnl_log_net *log = nfnl_log_pernet(net);
	स्थिर काष्ठा nfnl_ct_hook *nfnl_ct = शून्य;
	काष्ठा nf_conn *ct = शून्य;
	क्रमागत ip_conntrack_info ctinfo;

	अगर (li_user && li_user->type == NF_LOG_TYPE_ULOG)
		li = li_user;
	अन्यथा
		li = &शेष_loginfo;

	inst = instance_lookup_get(log, li->u.ulog.group);
	अगर (!inst)
		वापस;

	अगर (prefix)
		plen = म_माप(prefix) + 1;

	/* FIXME: करो we want to make the size calculation conditional based on
	 * what is actually present?  way more branches and checks, but more
	 * memory efficient... */
	size = nlmsg_total_size(माप(काष्ठा nfgenmsg))
		+ nla_total_size(माप(काष्ठा nfulnl_msg_packet_hdr))
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
#पूर्ण_अगर
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* mark */
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* uid */
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* gid */
		+ nla_total_size(plen)			/* prefix */
		+ nla_total_size(माप(काष्ठा nfulnl_msg_packet_hw))
		+ nla_total_size(माप(काष्ठा nfulnl_msg_packet_बारtamp))
		+ nla_total_size(माप(काष्ठा nfgenmsg));	/* NLMSG_DONE */

	अगर (in && skb_mac_header_was_set(skb)) अणु
		size += nla_total_size(skb->dev->hard_header_len)
			+ nla_total_size(माप(u_पूर्णांक16_t))	/* hwtype */
			+ nla_total_size(माप(u_पूर्णांक16_t));	/* hwlen */
	पूर्ण

	spin_lock_bh(&inst->lock);

	अगर (inst->flags & NFULNL_CFG_F_SEQ)
		size += nla_total_size(माप(u_पूर्णांक32_t));
	अगर (inst->flags & NFULNL_CFG_F_SEQ_GLOBAL)
		size += nla_total_size(माप(u_पूर्णांक32_t));
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (inst->flags & NFULNL_CFG_F_CONNTRACK) अणु
		nfnl_ct = rcu_dereference(nfnl_ct_hook);
		अगर (nfnl_ct != शून्य) अणु
			ct = nf_ct_get(skb, &ctinfo);
			अगर (ct != शून्य)
				size += nfnl_ct->build_size(ct);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (pf == NFPROTO_NETDEV || pf == NFPROTO_BRIDGE)
		size += nfulnl_get_bridge_size(skb);

	qthreshold = inst->qthreshold;
	/* per-rule qthreshold overrides per-instance */
	अगर (li->u.ulog.qthreshold)
		अगर (qthreshold > li->u.ulog.qthreshold)
			qthreshold = li->u.ulog.qthreshold;


	चयन (inst->copy_mode) अणु
	हाल NFULNL_COPY_META:
	हाल NFULNL_COPY_NONE:
		data_len = 0;
		अवरोध;

	हाल NFULNL_COPY_PACKET:
		data_len = inst->copy_range;
		अगर ((li->u.ulog.flags & NF_LOG_F_COPY_LEN) &&
		    (li->u.ulog.copy_len < data_len))
			data_len = li->u.ulog.copy_len;

		अगर (data_len > skb->len)
			data_len = skb->len;

		size += nla_total_size(data_len);
		अवरोध;

	हाल NFULNL_COPY_DISABLED:
	शेष:
		जाओ unlock_and_release;
	पूर्ण

	अगर (inst->skb && size > skb_tailroom(inst->skb)) अणु
		/* either the queue len is too high or we करोn't have
		 * enough room in the skb left. flush to userspace. */
		__nfulnl_flush(inst);
	पूर्ण

	अगर (!inst->skb) अणु
		inst->skb = nfulnl_alloc_skb(net, inst->peer_portid,
					     inst->nlbufsiz, size);
		अगर (!inst->skb)
			जाओ alloc_failure;
	पूर्ण

	inst->qlen++;

	__build_packet_message(log, inst, skb, data_len, pf,
				hooknum, in, out, prefix, plen,
				nfnl_ct, ct, ctinfo);

	अगर (inst->qlen >= qthreshold)
		__nfulnl_flush(inst);
	/* समयr_pending always called within inst->lock, so there
	 * is no chance of a race here */
	अन्यथा अगर (!समयr_pending(&inst->समयr)) अणु
		instance_get(inst);
		inst->समयr.expires = jअगरfies + (inst->flushसमयout*HZ/100);
		add_समयr(&inst->समयr);
	पूर्ण

unlock_and_release:
	spin_unlock_bh(&inst->lock);
	instance_put(inst);
	वापस;

alloc_failure:
	/* FIXME: statistics */
	जाओ unlock_and_release;
पूर्ण

अटल पूर्णांक
nfulnl_rcv_nl_event(काष्ठा notअगरier_block *this,
		   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netlink_notअगरy *n = ptr;
	काष्ठा nfnl_log_net *log = nfnl_log_pernet(n->net);

	अगर (event == NETLINK_URELEASE && n->protocol == NETLINK_NETFILTER) अणु
		पूर्णांक i;

		/* destroy all instances क्रम this portid */
		spin_lock_bh(&log->instances_lock);
		क्रम  (i = 0; i < INSTANCE_BUCKETS; i++) अणु
			काष्ठा hlist_node *t2;
			काष्ठा nfulnl_instance *inst;
			काष्ठा hlist_head *head = &log->instance_table[i];

			hlist_क्रम_each_entry_safe(inst, t2, head, hlist) अणु
				अगर (n->portid == inst->peer_portid)
					__instance_destroy(inst);
			पूर्ण
		पूर्ण
		spin_unlock_bh(&log->instances_lock);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nfulnl_rtnl_notअगरier = अणु
	.notअगरier_call	= nfulnl_rcv_nl_event,
पूर्ण;

अटल पूर्णांक nfulnl_recv_unsupp(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nfula[])
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल काष्ठा nf_logger nfulnl_logger __पढ़ो_mostly = अणु
	.name	= "nfnetlink_log",
	.type	= NF_LOG_TYPE_ULOG,
	.logfn	= nfulnl_log_packet,
	.me	= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nfula_cfg_policy[NFULA_CFG_MAX+1] = अणु
	[NFULA_CFG_CMD]		= अणु .len = माप(काष्ठा nfulnl_msg_config_cmd) पूर्ण,
	[NFULA_CFG_MODE]	= अणु .len = माप(काष्ठा nfulnl_msg_config_mode) पूर्ण,
	[NFULA_CFG_TIMEOUT]	= अणु .type = NLA_U32 पूर्ण,
	[NFULA_CFG_QTHRESH]	= अणु .type = NLA_U32 पूर्ण,
	[NFULA_CFG_NLबफ_मान]	= अणु .type = NLA_U32 पूर्ण,
	[NFULA_CFG_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक nfulnl_recv_config(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nfula[])
अणु
	काष्ठा nfnl_log_net *log = nfnl_log_pernet(info->net);
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u_पूर्णांक16_t group_num = ntohs(nfmsg->res_id);
	काष्ठा nfulnl_msg_config_cmd *cmd = शून्य;
	काष्ठा nfulnl_instance *inst;
	u16 flags = 0;
	पूर्णांक ret = 0;

	अगर (nfula[NFULA_CFG_CMD]) अणु
		u_पूर्णांक8_t pf = nfmsg->nfgen_family;
		cmd = nla_data(nfula[NFULA_CFG_CMD]);

		/* Commands without queue context */
		चयन (cmd->command) अणु
		हाल NFULNL_CFG_CMD_PF_BIND:
			वापस nf_log_bind_pf(info->net, pf, &nfulnl_logger);
		हाल NFULNL_CFG_CMD_PF_UNBIND:
			nf_log_unbind_pf(info->net, pf);
			वापस 0;
		पूर्ण
	पूर्ण

	inst = instance_lookup_get(log, group_num);
	अगर (inst && inst->peer_portid != NETLINK_CB(skb).portid) अणु
		ret = -EPERM;
		जाओ out_put;
	पूर्ण

	/* Check अगर we support these flags in first place, dependencies should
	 * be there too not to अवरोध atomicity.
	 */
	अगर (nfula[NFULA_CFG_FLAGS]) अणु
		flags = ntohs(nla_get_be16(nfula[NFULA_CFG_FLAGS]));

		अगर ((flags & NFULNL_CFG_F_CONNTRACK) &&
		    !rcu_access_poपूर्णांकer(nfnl_ct_hook)) अणु
#अगर_घोषित CONFIG_MODULES
			nfnl_unlock(NFNL_SUBSYS_ULOG);
			request_module("ip_conntrack_netlink");
			nfnl_lock(NFNL_SUBSYS_ULOG);
			अगर (rcu_access_poपूर्णांकer(nfnl_ct_hook)) अणु
				ret = -EAGAIN;
				जाओ out_put;
			पूर्ण
#पूर्ण_अगर
			ret = -EOPNOTSUPP;
			जाओ out_put;
		पूर्ण
	पूर्ण

	अगर (cmd != शून्य) अणु
		चयन (cmd->command) अणु
		हाल NFULNL_CFG_CMD_BIND:
			अगर (inst) अणु
				ret = -EBUSY;
				जाओ out_put;
			पूर्ण

			inst = instance_create(info->net, group_num,
					       NETLINK_CB(skb).portid,
					       sk_user_ns(NETLINK_CB(skb).sk));
			अगर (IS_ERR(inst)) अणु
				ret = PTR_ERR(inst);
				जाओ out;
			पूर्ण
			अवरोध;
		हाल NFULNL_CFG_CMD_UNBIND:
			अगर (!inst) अणु
				ret = -ENODEV;
				जाओ out;
			पूर्ण

			instance_destroy(log, inst);
			जाओ out_put;
		शेष:
			ret = -ENOTSUPP;
			जाओ out_put;
		पूर्ण
	पूर्ण अन्यथा अगर (!inst) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (nfula[NFULA_CFG_MODE]) अणु
		काष्ठा nfulnl_msg_config_mode *params =
			nla_data(nfula[NFULA_CFG_MODE]);

		nfulnl_set_mode(inst, params->copy_mode,
				ntohl(params->copy_range));
	पूर्ण

	अगर (nfula[NFULA_CFG_TIMEOUT]) अणु
		__be32 समयout = nla_get_be32(nfula[NFULA_CFG_TIMEOUT]);

		nfulnl_set_समयout(inst, ntohl(समयout));
	पूर्ण

	अगर (nfula[NFULA_CFG_NLबफ_मान]) अणु
		__be32 nlbufsiz = nla_get_be32(nfula[NFULA_CFG_NLबफ_मान]);

		nfulnl_set_nlbufsiz(inst, ntohl(nlbufsiz));
	पूर्ण

	अगर (nfula[NFULA_CFG_QTHRESH]) अणु
		__be32 qthresh = nla_get_be32(nfula[NFULA_CFG_QTHRESH]);

		nfulnl_set_qthresh(inst, ntohl(qthresh));
	पूर्ण

	अगर (nfula[NFULA_CFG_FLAGS])
		nfulnl_set_flags(inst, flags);

out_put:
	instance_put(inst);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nfnl_callback nfulnl_cb[NFULNL_MSG_MAX] = अणु
	[NFULNL_MSG_PACKET]	= अणु
		.call		= nfulnl_recv_unsupp,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFULA_MAX,
	पूर्ण,
	[NFULNL_MSG_CONFIG]	= अणु
		.call		= nfulnl_recv_config,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFULA_CFG_MAX,
		.policy		= nfula_cfg_policy
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली nfulnl_subsys = अणु
	.name		= "log",
	.subsys_id	= NFNL_SUBSYS_ULOG,
	.cb_count	= NFULNL_MSG_MAX,
	.cb		= nfulnl_cb,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
काष्ठा iter_state अणु
	काष्ठा seq_net_निजी p;
	अचिन्हित पूर्णांक bucket;
पूर्ण;

अटल काष्ठा hlist_node *get_first(काष्ठा net *net, काष्ठा iter_state *st)
अणु
	काष्ठा nfnl_log_net *log;
	अगर (!st)
		वापस शून्य;

	log = nfnl_log_pernet(net);

	क्रम (st->bucket = 0; st->bucket < INSTANCE_BUCKETS; st->bucket++) अणु
		काष्ठा hlist_head *head = &log->instance_table[st->bucket];

		अगर (!hlist_empty(head))
			वापस rcu_dereference_bh(hlist_first_rcu(head));
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा hlist_node *get_next(काष्ठा net *net, काष्ठा iter_state *st,
				   काष्ठा hlist_node *h)
अणु
	h = rcu_dereference_bh(hlist_next_rcu(h));
	जबतक (!h) अणु
		काष्ठा nfnl_log_net *log;
		काष्ठा hlist_head *head;

		अगर (++st->bucket >= INSTANCE_BUCKETS)
			वापस शून्य;

		log = nfnl_log_pernet(net);
		head = &log->instance_table[st->bucket];
		h = rcu_dereference_bh(hlist_first_rcu(head));
	पूर्ण
	वापस h;
पूर्ण

अटल काष्ठा hlist_node *get_idx(काष्ठा net *net, काष्ठा iter_state *st,
				  loff_t pos)
अणु
	काष्ठा hlist_node *head;
	head = get_first(net, st);

	अगर (head)
		जबतक (pos && (head = get_next(net, st, head)))
			pos--;
	वापस pos ? शून्य : head;
पूर्ण

अटल व्योम *seq_start(काष्ठा seq_file *s, loff_t *pos)
	__acquires(rcu_bh)
अणु
	rcu_पढ़ो_lock_bh();
	वापस get_idx(seq_file_net(s), s->निजी, *pos);
पूर्ण

अटल व्योम *seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस get_next(seq_file_net(s), s->निजी, v);
पूर्ण

अटल व्योम seq_stop(काष्ठा seq_file *s, व्योम *v)
	__releases(rcu_bh)
अणु
	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल पूर्णांक seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	स्थिर काष्ठा nfulnl_instance *inst = v;

	seq_म_लिखो(s, "%5u %6u %5u %1u %5u %6u %2u\n",
		   inst->group_num,
		   inst->peer_portid, inst->qlen,
		   inst->copy_mode, inst->copy_range,
		   inst->flushसमयout, refcount_पढ़ो(&inst->use));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations nful_seq_ops = अणु
	.start	= seq_start,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= seq_show,
पूर्ण;
#पूर्ण_अगर /* PROC_FS */

अटल पूर्णांक __net_init nfnl_log_net_init(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा nfnl_log_net *log = nfnl_log_pernet(net);
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *proc;
	kuid_t root_uid;
	kgid_t root_gid;
#पूर्ण_अगर

	क्रम (i = 0; i < INSTANCE_BUCKETS; i++)
		INIT_HLIST_HEAD(&log->instance_table[i]);
	spin_lock_init(&log->instances_lock);

#अगर_घोषित CONFIG_PROC_FS
	proc = proc_create_net("nfnetlink_log", 0440, net->nf.proc_netfilter,
			&nful_seq_ops, माप(काष्ठा iter_state));
	अगर (!proc)
		वापस -ENOMEM;

	root_uid = make_kuid(net->user_ns, 0);
	root_gid = make_kgid(net->user_ns, 0);
	अगर (uid_valid(root_uid) && gid_valid(root_gid))
		proc_set_user(proc, root_uid, root_gid);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __net_निकास nfnl_log_net_निकास(काष्ठा net *net)
अणु
	काष्ठा nfnl_log_net *log = nfnl_log_pernet(net);
	अचिन्हित पूर्णांक i;

#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("nfnetlink_log", net->nf.proc_netfilter);
#पूर्ण_अगर
	nf_log_unset(net, &nfulnl_logger);
	क्रम (i = 0; i < INSTANCE_BUCKETS; i++)
		WARN_ON_ONCE(!hlist_empty(&log->instance_table[i]));
पूर्ण

अटल काष्ठा pernet_operations nfnl_log_net_ops = अणु
	.init	= nfnl_log_net_init,
	.निकास	= nfnl_log_net_निकास,
	.id	= &nfnl_log_net_id,
	.size	= माप(काष्ठा nfnl_log_net),
पूर्ण;

अटल पूर्णांक __init nfnetlink_log_init(व्योम)
अणु
	पूर्णांक status;

	status = रेजिस्टर_pernet_subsys(&nfnl_log_net_ops);
	अगर (status < 0) अणु
		pr_err("failed to register pernet ops\n");
		जाओ out;
	पूर्ण

	netlink_रेजिस्टर_notअगरier(&nfulnl_rtnl_notअगरier);
	status = nfnetlink_subsys_रेजिस्टर(&nfulnl_subsys);
	अगर (status < 0) अणु
		pr_err("failed to create netlink socket\n");
		जाओ cleanup_netlink_notअगरier;
	पूर्ण

	status = nf_log_रेजिस्टर(NFPROTO_UNSPEC, &nfulnl_logger);
	अगर (status < 0) अणु
		pr_err("failed to register logger\n");
		जाओ cleanup_subsys;
	पूर्ण

	वापस status;

cleanup_subsys:
	nfnetlink_subsys_unरेजिस्टर(&nfulnl_subsys);
cleanup_netlink_notअगरier:
	netlink_unरेजिस्टर_notअगरier(&nfulnl_rtnl_notअगरier);
	unरेजिस्टर_pernet_subsys(&nfnl_log_net_ops);
out:
	वापस status;
पूर्ण

अटल व्योम __निकास nfnetlink_log_fini(व्योम)
अणु
	nfnetlink_subsys_unरेजिस्टर(&nfulnl_subsys);
	netlink_unरेजिस्टर_notअगरier(&nfulnl_rtnl_notअगरier);
	unरेजिस्टर_pernet_subsys(&nfnl_log_net_ops);
	nf_log_unरेजिस्टर(&nfulnl_logger);
पूर्ण

MODULE_DESCRIPTION("netfilter userspace logging");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_ULOG);
MODULE_ALIAS_NF_LOGGER(AF_INET, 1);
MODULE_ALIAS_NF_LOGGER(AF_INET6, 1);
MODULE_ALIAS_NF_LOGGER(AF_BRIDGE, 1);
MODULE_ALIAS_NF_LOGGER(3, 1); /* NFPROTO_ARP */
MODULE_ALIAS_NF_LOGGER(5, 1); /* NFPROTO_NETDEV */

module_init(nfnetlink_log_init);
module_निकास(nfnetlink_log_fini);
