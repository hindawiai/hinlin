<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is a module which is used क्रम queueing packets and communicating with
 * userspace via nfnetlink.
 *
 * (C) 2005 by Harald Welte <laक्रमge@netfilter.org>
 * (C) 2007 by Patrick McHardy <kaber@trash.net>
 *
 * Based on the old ipv4-only ip_queue.c:
 * (C) 2000-2002 James Morris <jmorris@पूर्णांकercode.com.au>
 * (C) 2003-2005 Netfilter Core Team <coreteam@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_queue.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/list.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/netfilter/nf_queue.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/atomic.h>

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
#समावेश "../bridge/br_private.h"
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर

#घोषणा NFQNL_QMAX_DEFAULT 1024

/* We're using काष्ठा nlattr which has 16bit nla_len. Note that nla_len
 * includes the header length. Thus, the maximum packet length that we
 * support is 65531 bytes. We send truncated packets अगर the specअगरied length
 * is larger than that.  Userspace can check क्रम presence of NFQA_CAP_LEN
 * attribute to detect truncation.
 */
#घोषणा NFQNL_MAX_COPY_RANGE (0xffff - NLA_HDRLEN)

काष्ठा nfqnl_instance अणु
	काष्ठा hlist_node hlist;		/* global list of queues */
	काष्ठा rcu_head rcu;

	u32 peer_portid;
	अचिन्हित पूर्णांक queue_maxlen;
	अचिन्हित पूर्णांक copy_range;
	अचिन्हित पूर्णांक queue_dropped;
	अचिन्हित पूर्णांक queue_user_dropped;


	u_पूर्णांक16_t queue_num;			/* number of this queue */
	u_पूर्णांक8_t copy_mode;
	u_पूर्णांक32_t flags;			/* Set using NFQA_CFG_FLAGS */
/*
 * Following fields are dirtied क्रम each queued packet,
 * keep them in same cache line अगर possible.
 */
	spinlock_t	lock	____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक	queue_total;
	अचिन्हित पूर्णांक	id_sequence;		/* 'sequence' of pkt ids */
	काष्ठा list_head queue_list;		/* packets in queue */
पूर्ण;

प्रकार पूर्णांक (*nfqnl_cmpfn)(काष्ठा nf_queue_entry *, अचिन्हित दीर्घ);

अटल अचिन्हित पूर्णांक nfnl_queue_net_id __पढ़ो_mostly;

#घोषणा INSTANCE_BUCKETS	16
काष्ठा nfnl_queue_net अणु
	spinlock_t instances_lock;
	काष्ठा hlist_head instance_table[INSTANCE_BUCKETS];
पूर्ण;

अटल काष्ठा nfnl_queue_net *nfnl_queue_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, nfnl_queue_net_id);
पूर्ण

अटल अंतरभूत u_पूर्णांक8_t instance_hashfn(u_पूर्णांक16_t queue_num)
अणु
	वापस ((queue_num >> 8) ^ queue_num) % INSTANCE_BUCKETS;
पूर्ण

अटल काष्ठा nfqnl_instance *
instance_lookup(काष्ठा nfnl_queue_net *q, u_पूर्णांक16_t queue_num)
अणु
	काष्ठा hlist_head *head;
	काष्ठा nfqnl_instance *inst;

	head = &q->instance_table[instance_hashfn(queue_num)];
	hlist_क्रम_each_entry_rcu(inst, head, hlist) अणु
		अगर (inst->queue_num == queue_num)
			वापस inst;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nfqnl_instance *
instance_create(काष्ठा nfnl_queue_net *q, u_पूर्णांक16_t queue_num, u32 portid)
अणु
	काष्ठा nfqnl_instance *inst;
	अचिन्हित पूर्णांक h;
	पूर्णांक err;

	spin_lock(&q->instances_lock);
	अगर (instance_lookup(q, queue_num)) अणु
		err = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	inst = kzalloc(माप(*inst), GFP_ATOMIC);
	अगर (!inst) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	inst->queue_num = queue_num;
	inst->peer_portid = portid;
	inst->queue_maxlen = NFQNL_QMAX_DEFAULT;
	inst->copy_range = NFQNL_MAX_COPY_RANGE;
	inst->copy_mode = NFQNL_COPY_NONE;
	spin_lock_init(&inst->lock);
	INIT_LIST_HEAD(&inst->queue_list);

	अगर (!try_module_get(THIS_MODULE)) अणु
		err = -EAGAIN;
		जाओ out_मुक्त;
	पूर्ण

	h = instance_hashfn(queue_num);
	hlist_add_head_rcu(&inst->hlist, &q->instance_table[h]);

	spin_unlock(&q->instances_lock);

	वापस inst;

out_मुक्त:
	kमुक्त(inst);
out_unlock:
	spin_unlock(&q->instances_lock);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम nfqnl_flush(काष्ठा nfqnl_instance *queue, nfqnl_cmpfn cmpfn,
			अचिन्हित दीर्घ data);

अटल व्योम
instance_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा nfqnl_instance *inst = container_of(head, काष्ठा nfqnl_instance,
						   rcu);

	nfqnl_flush(inst, शून्य, 0);
	kमुक्त(inst);
	module_put(THIS_MODULE);
पूर्ण

अटल व्योम
__instance_destroy(काष्ठा nfqnl_instance *inst)
अणु
	hlist_del_rcu(&inst->hlist);
	call_rcu(&inst->rcu, instance_destroy_rcu);
पूर्ण

अटल व्योम
instance_destroy(काष्ठा nfnl_queue_net *q, काष्ठा nfqnl_instance *inst)
अणु
	spin_lock(&q->instances_lock);
	__instance_destroy(inst);
	spin_unlock(&q->instances_lock);
पूर्ण

अटल अंतरभूत व्योम
__enqueue_entry(काष्ठा nfqnl_instance *queue, काष्ठा nf_queue_entry *entry)
अणु
       list_add_tail(&entry->list, &queue->queue_list);
       queue->queue_total++;
पूर्ण

अटल व्योम
__dequeue_entry(काष्ठा nfqnl_instance *queue, काष्ठा nf_queue_entry *entry)
अणु
	list_del(&entry->list);
	queue->queue_total--;
पूर्ण

अटल काष्ठा nf_queue_entry *
find_dequeue_entry(काष्ठा nfqnl_instance *queue, अचिन्हित पूर्णांक id)
अणु
	काष्ठा nf_queue_entry *entry = शून्य, *i;

	spin_lock_bh(&queue->lock);

	list_क्रम_each_entry(i, &queue->queue_list, list) अणु
		अगर (i->id == id) अणु
			entry = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (entry)
		__dequeue_entry(queue, entry);

	spin_unlock_bh(&queue->lock);

	वापस entry;
पूर्ण

अटल व्योम nfqnl_reinject(काष्ठा nf_queue_entry *entry, अचिन्हित पूर्णांक verdict)
अणु
	काष्ठा nf_ct_hook *ct_hook;
	पूर्णांक err;

	अगर (verdict == NF_ACCEPT ||
	    verdict == NF_REPEAT ||
	    verdict == NF_STOP) अणु
		rcu_पढ़ो_lock();
		ct_hook = rcu_dereference(nf_ct_hook);
		अगर (ct_hook) अणु
			err = ct_hook->update(entry->state.net, entry->skb);
			अगर (err < 0)
				verdict = NF_DROP;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	nf_reinject(entry, verdict);
पूर्ण

अटल व्योम
nfqnl_flush(काष्ठा nfqnl_instance *queue, nfqnl_cmpfn cmpfn, अचिन्हित दीर्घ data)
अणु
	काष्ठा nf_queue_entry *entry, *next;

	spin_lock_bh(&queue->lock);
	list_क्रम_each_entry_safe(entry, next, &queue->queue_list, list) अणु
		अगर (!cmpfn || cmpfn(entry, data)) अणु
			list_del(&entry->list);
			queue->queue_total--;
			nfqnl_reinject(entry, NF_DROP);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&queue->lock);
पूर्ण

अटल पूर्णांक
nfqnl_put_packet_info(काष्ठा sk_buff *nlskb, काष्ठा sk_buff *packet,
		      bool csum_verअगरy)
अणु
	__u32 flags = 0;

	अगर (packet->ip_summed == CHECKSUM_PARTIAL)
		flags = NFQA_SKB_CSUMNOTREADY;
	अन्यथा अगर (csum_verअगरy)
		flags = NFQA_SKB_CSUM_NOTVERIFIED;

	अगर (skb_is_gso(packet))
		flags |= NFQA_SKB_GSO;

	वापस flags ? nla_put_be32(nlskb, NFQA_SKB_INFO, htonl(flags)) : 0;
पूर्ण

अटल पूर्णांक nfqnl_put_sk_uidgid(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	स्थिर काष्ठा cred *cred;

	अगर (!sk_fullsock(sk))
		वापस 0;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	अगर (sk->sk_socket && sk->sk_socket->file) अणु
		cred = sk->sk_socket->file->f_cred;
		अगर (nla_put_be32(skb, NFQA_UID,
		    htonl(from_kuid_munged(&init_user_ns, cred->fsuid))))
			जाओ nla_put_failure;
		अगर (nla_put_be32(skb, NFQA_GID,
		    htonl(from_kgid_munged(&init_user_ns, cred->fsgid))))
			जाओ nla_put_failure;
	पूर्ण
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	वापस 0;

nla_put_failure:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	वापस -1;
पूर्ण

अटल u32 nfqnl_get_sk_secctx(काष्ठा sk_buff *skb, अक्षर **secdata)
अणु
	u32 seclen = 0;
#अगर IS_ENABLED(CONFIG_NETWORK_SECMARK)
	अगर (!skb || !sk_fullsock(skb->sk))
		वापस 0;

	पढ़ो_lock_bh(&skb->sk->sk_callback_lock);

	अगर (skb->secmark)
		security_secid_to_secctx(skb->secmark, secdata, &seclen);

	पढ़ो_unlock_bh(&skb->sk->sk_callback_lock);
#पूर्ण_अगर
	वापस seclen;
पूर्ण

अटल u32 nfqnl_get_bridge_size(काष्ठा nf_queue_entry *entry)
अणु
	काष्ठा sk_buff *entskb = entry->skb;
	u32 nlalen = 0;

	अगर (entry->state.pf != PF_BRIDGE || !skb_mac_header_was_set(entskb))
		वापस 0;

	अगर (skb_vlan_tag_present(entskb))
		nlalen += nla_total_size(nla_total_size(माप(__be16)) +
					 nla_total_size(माप(__be16)));

	अगर (entskb->network_header > entskb->mac_header)
		nlalen += nla_total_size((entskb->network_header -
					  entskb->mac_header));

	वापस nlalen;
पूर्ण

अटल पूर्णांक nfqnl_put_bridge(काष्ठा nf_queue_entry *entry, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *entskb = entry->skb;

	अगर (entry->state.pf != PF_BRIDGE || !skb_mac_header_was_set(entskb))
		वापस 0;

	अगर (skb_vlan_tag_present(entskb)) अणु
		काष्ठा nlattr *nest;

		nest = nla_nest_start(skb, NFQA_VLAN);
		अगर (!nest)
			जाओ nla_put_failure;

		अगर (nla_put_be16(skb, NFQA_VLAN_TCI, htons(entskb->vlan_tci)) ||
		    nla_put_be16(skb, NFQA_VLAN_PROTO, entskb->vlan_proto))
			जाओ nla_put_failure;

		nla_nest_end(skb, nest);
	पूर्ण

	अगर (entskb->mac_header < entskb->network_header) अणु
		पूर्णांक len = (पूर्णांक)(entskb->network_header - entskb->mac_header);

		अगर (nla_put(skb, NFQA_L2HDR, len, skb_mac_header(entskb)))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा sk_buff *
nfqnl_build_packet_message(काष्ठा net *net, काष्ठा nfqnl_instance *queue,
			   काष्ठा nf_queue_entry *entry,
			   __be32 **packet_id_ptr)
अणु
	माप_प्रकार size;
	माप_प्रकार data_len = 0, cap_len = 0;
	अचिन्हित पूर्णांक hlen = 0;
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *nla;
	काष्ठा nfqnl_msg_packet_hdr *pmsg;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *entskb = entry->skb;
	काष्ठा net_device *indev;
	काष्ठा net_device *outdev;
	काष्ठा nf_conn *ct = शून्य;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nfnl_ct_hook *nfnl_ct;
	bool csum_verअगरy;
	अक्षर *secdata = शून्य;
	u32 seclen = 0;

	size = nlmsg_total_size(माप(काष्ठा nfgenmsg))
		+ nla_total_size(माप(काष्ठा nfqnl_msg_packet_hdr))
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* अगरindex */
#पूर्ण_अगर
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* mark */
		+ nla_total_size(माप(काष्ठा nfqnl_msg_packet_hw))
		+ nla_total_size(माप(u_पूर्णांक32_t))	/* skbinfo */
		+ nla_total_size(माप(u_पूर्णांक32_t));	/* cap_len */

	अगर (entskb->tstamp)
		size += nla_total_size(माप(काष्ठा nfqnl_msg_packet_बारtamp));

	size += nfqnl_get_bridge_size(entry);

	अगर (entry->state.hook <= NF_INET_FORWARD ||
	   (entry->state.hook == NF_INET_POST_ROUTING && entskb->sk == शून्य))
		csum_verअगरy = !skb_csum_unnecessary(entskb);
	अन्यथा
		csum_verअगरy = false;

	outdev = entry->state.out;

	चयन ((क्रमागत nfqnl_config_mode)READ_ONCE(queue->copy_mode)) अणु
	हाल NFQNL_COPY_META:
	हाल NFQNL_COPY_NONE:
		अवरोध;

	हाल NFQNL_COPY_PACKET:
		अगर (!(queue->flags & NFQA_CFG_F_GSO) &&
		    entskb->ip_summed == CHECKSUM_PARTIAL &&
		    skb_checksum_help(entskb))
			वापस शून्य;

		data_len = READ_ONCE(queue->copy_range);
		अगर (data_len > entskb->len)
			data_len = entskb->len;

		hlen = skb_zerocopy_headlen(entskb);
		hlen = min_t(अचिन्हित पूर्णांक, hlen, data_len);
		size += माप(काष्ठा nlattr) + hlen;
		cap_len = entskb->len;
		अवरोध;
	पूर्ण

	nfnl_ct = rcu_dereference(nfnl_ct_hook);

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (queue->flags & NFQA_CFG_F_CONNTRACK) अणु
		अगर (nfnl_ct != शून्य) अणु
			ct = nf_ct_get(entskb, &ctinfo);
			अगर (ct != शून्य)
				size += nfnl_ct->build_size(ct);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (queue->flags & NFQA_CFG_F_UID_GID) अणु
		size += (nla_total_size(माप(u_पूर्णांक32_t))	/* uid */
			+ nla_total_size(माप(u_पूर्णांक32_t)));	/* gid */
	पूर्ण

	अगर ((queue->flags & NFQA_CFG_F_SECCTX) && entskb->sk) अणु
		seclen = nfqnl_get_sk_secctx(entskb, &secdata);
		अगर (seclen)
			size += nla_total_size(seclen);
	पूर्ण

	skb = alloc_skb(size, GFP_ATOMIC);
	अगर (!skb) अणु
		skb_tx_error(entskb);
		जाओ nlmsg_failure;
	पूर्ण

	nlh = nfnl_msg_put(skb, 0, 0,
			   nfnl_msg_type(NFNL_SUBSYS_QUEUE, NFQNL_MSG_PACKET),
			   0, entry->state.pf, NFNETLINK_V0,
			   htons(queue->queue_num));
	अगर (!nlh) अणु
		skb_tx_error(entskb);
		kमुक्त_skb(skb);
		जाओ nlmsg_failure;
	पूर्ण

	nla = __nla_reserve(skb, NFQA_PACKET_HDR, माप(*pmsg));
	pmsg = nla_data(nla);
	pmsg->hw_protocol	= entskb->protocol;
	pmsg->hook		= entry->state.hook;
	*packet_id_ptr		= &pmsg->packet_id;

	indev = entry->state.in;
	अगर (indev) अणु
#अगर !IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		अगर (nla_put_be32(skb, NFQA_IFINDEX_INDEV, htonl(indev->अगरindex)))
			जाओ nla_put_failure;
#अन्यथा
		अगर (entry->state.pf == PF_BRIDGE) अणु
			/* Case 1: indev is physical input device, we need to
			 * look क्रम bridge group (when called from
			 * netfilter_bridge) */
			अगर (nla_put_be32(skb, NFQA_IFINDEX_PHYSINDEV,
					 htonl(indev->अगरindex)) ||
			/* this is the bridge group "brX" */
			/* rcu_पढ़ो_lock()ed by __nf_queue */
			    nla_put_be32(skb, NFQA_IFINDEX_INDEV,
					 htonl(br_port_get_rcu(indev)->br->dev->अगरindex)))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अणु
			पूर्णांक physinअगर;

			/* Case 2: indev is bridge group, we need to look क्रम
			 * physical device (when called from ipv4) */
			अगर (nla_put_be32(skb, NFQA_IFINDEX_INDEV,
					 htonl(indev->अगरindex)))
				जाओ nla_put_failure;

			physinअगर = nf_bridge_get_physinअगर(entskb);
			अगर (physinअगर &&
			    nla_put_be32(skb, NFQA_IFINDEX_PHYSINDEV,
					 htonl(physinअगर)))
				जाओ nla_put_failure;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (outdev) अणु
#अगर !IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		अगर (nla_put_be32(skb, NFQA_IFINDEX_OUTDEV, htonl(outdev->अगरindex)))
			जाओ nla_put_failure;
#अन्यथा
		अगर (entry->state.pf == PF_BRIDGE) अणु
			/* Case 1: outdev is physical output device, we need to
			 * look क्रम bridge group (when called from
			 * netfilter_bridge) */
			अगर (nla_put_be32(skb, NFQA_IFINDEX_PHYSOUTDEV,
					 htonl(outdev->अगरindex)) ||
			/* this is the bridge group "brX" */
			/* rcu_पढ़ो_lock()ed by __nf_queue */
			    nla_put_be32(skb, NFQA_IFINDEX_OUTDEV,
					 htonl(br_port_get_rcu(outdev)->br->dev->अगरindex)))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अणु
			पूर्णांक physoutअगर;

			/* Case 2: outdev is bridge group, we need to look क्रम
			 * physical output device (when called from ipv4) */
			अगर (nla_put_be32(skb, NFQA_IFINDEX_OUTDEV,
					 htonl(outdev->अगरindex)))
				जाओ nla_put_failure;

			physoutअगर = nf_bridge_get_physoutअगर(entskb);
			अगर (physoutअगर &&
			    nla_put_be32(skb, NFQA_IFINDEX_PHYSOUTDEV,
					 htonl(physoutअगर)))
				जाओ nla_put_failure;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (entskb->mark &&
	    nla_put_be32(skb, NFQA_MARK, htonl(entskb->mark)))
		जाओ nla_put_failure;

	अगर (indev && entskb->dev &&
	    entskb->mac_header != entskb->network_header) अणु
		काष्ठा nfqnl_msg_packet_hw phw;
		पूर्णांक len;

		स_रखो(&phw, 0, माप(phw));
		len = dev_parse_header(entskb, phw.hw_addr);
		अगर (len) अणु
			phw.hw_addrlen = htons(len);
			अगर (nla_put(skb, NFQA_HWADDR, माप(phw), &phw))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (nfqnl_put_bridge(entry, skb) < 0)
		जाओ nla_put_failure;

	अगर (entry->state.hook <= NF_INET_FORWARD && entskb->tstamp) अणु
		काष्ठा nfqnl_msg_packet_बारtamp ts;
		काष्ठा बारpec64 kts = kसमय_प्रकारo_बारpec64(entskb->tstamp);

		ts.sec = cpu_to_be64(kts.tv_sec);
		ts.usec = cpu_to_be64(kts.tv_nsec / NSEC_PER_USEC);

		अगर (nla_put(skb, NFQA_TIMESTAMP, माप(ts), &ts))
			जाओ nla_put_failure;
	पूर्ण

	अगर ((queue->flags & NFQA_CFG_F_UID_GID) && entskb->sk &&
	    nfqnl_put_sk_uidgid(skb, entskb->sk) < 0)
		जाओ nla_put_failure;

	अगर (seclen && nla_put(skb, NFQA_SECCTX, seclen, secdata))
		जाओ nla_put_failure;

	अगर (ct && nfnl_ct->build(skb, ct, ctinfo, NFQA_CT, NFQA_CT_INFO) < 0)
		जाओ nla_put_failure;

	अगर (cap_len > data_len &&
	    nla_put_be32(skb, NFQA_CAP_LEN, htonl(cap_len)))
		जाओ nla_put_failure;

	अगर (nfqnl_put_packet_info(skb, entskb, csum_verअगरy))
		जाओ nla_put_failure;

	अगर (data_len) अणु
		काष्ठा nlattr *nla;

		अगर (skb_tailroom(skb) < माप(*nla) + hlen)
			जाओ nla_put_failure;

		nla = skb_put(skb, माप(*nla));
		nla->nla_type = NFQA_PAYLOAD;
		nla->nla_len = nla_attr_size(data_len);

		अगर (skb_zerocopy(skb, entskb, data_len, hlen))
			जाओ nla_put_failure;
	पूर्ण

	nlh->nlmsg_len = skb->len;
	अगर (seclen)
		security_release_secctx(secdata, seclen);
	वापस skb;

nla_put_failure:
	skb_tx_error(entskb);
	kमुक्त_skb(skb);
	net_err_ratelimited("nf_queue: error creating packet message\n");
nlmsg_failure:
	अगर (seclen)
		security_release_secctx(secdata, seclen);
	वापस शून्य;
पूर्ण

अटल bool nf_ct_drop_unconfirmed(स्थिर काष्ठा nf_queue_entry *entry)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अटल स्थिर अचिन्हित दीर्घ flags = IPS_CONFIRMED | IPS_DYING;
	स्थिर काष्ठा nf_conn *ct = (व्योम *)skb_nfct(entry->skb);

	अगर (ct && ((ct->status & flags) == IPS_DYING))
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक
__nfqnl_enqueue_packet(काष्ठा net *net, काष्ठा nfqnl_instance *queue,
			काष्ठा nf_queue_entry *entry)
अणु
	काष्ठा sk_buff *nskb;
	पूर्णांक err = -ENOBUFS;
	__be32 *packet_id_ptr;
	पूर्णांक failखोलो = 0;

	nskb = nfqnl_build_packet_message(net, queue, entry, &packet_id_ptr);
	अगर (nskb == शून्य) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	spin_lock_bh(&queue->lock);

	अगर (nf_ct_drop_unconfirmed(entry))
		जाओ err_out_मुक्त_nskb;

	अगर (queue->queue_total >= queue->queue_maxlen) अणु
		अगर (queue->flags & NFQA_CFG_F_FAIL_OPEN) अणु
			failखोलो = 1;
			err = 0;
		पूर्ण अन्यथा अणु
			queue->queue_dropped++;
			net_warn_ratelimited("nf_queue: full at %d entries, dropping packets(s)\n",
					     queue->queue_total);
		पूर्ण
		जाओ err_out_मुक्त_nskb;
	पूर्ण
	entry->id = ++queue->id_sequence;
	*packet_id_ptr = htonl(entry->id);

	/* nfnetlink_unicast will either मुक्त the nskb or add it to a socket */
	err = nfnetlink_unicast(nskb, net, queue->peer_portid);
	अगर (err < 0) अणु
		अगर (queue->flags & NFQA_CFG_F_FAIL_OPEN) अणु
			failखोलो = 1;
			err = 0;
		पूर्ण अन्यथा अणु
			queue->queue_user_dropped++;
		पूर्ण
		जाओ err_out_unlock;
	पूर्ण

	__enqueue_entry(queue, entry);

	spin_unlock_bh(&queue->lock);
	वापस 0;

err_out_मुक्त_nskb:
	kमुक्त_skb(nskb);
err_out_unlock:
	spin_unlock_bh(&queue->lock);
	अगर (failखोलो)
		nfqnl_reinject(entry, NF_ACCEPT);
err_out:
	वापस err;
पूर्ण

अटल काष्ठा nf_queue_entry *
nf_queue_entry_dup(काष्ठा nf_queue_entry *e)
अणु
	काष्ठा nf_queue_entry *entry = kmemdup(e, e->size, GFP_ATOMIC);
	अगर (entry)
		nf_queue_entry_get_refs(entry);
	वापस entry;
पूर्ण

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
/* When called from bridge netfilter, skb->data must poपूर्णांक to MAC header
 * beक्रमe calling skb_gso_segment(). Else, original MAC header is lost
 * and segmented skbs will be sent to wrong destination.
 */
अटल व्योम nf_bridge_adjust_skb_data(काष्ठा sk_buff *skb)
अणु
	अगर (nf_bridge_info_get(skb))
		__skb_push(skb, skb->network_header - skb->mac_header);
पूर्ण

अटल व्योम nf_bridge_adjust_segmented_data(काष्ठा sk_buff *skb)
अणु
	अगर (nf_bridge_info_get(skb))
		__skb_pull(skb, skb->network_header - skb->mac_header);
पूर्ण
#अन्यथा
#घोषणा nf_bridge_adjust_skb_data(s) करो अणुपूर्ण जबतक (0)
#घोषणा nf_bridge_adjust_segmented_data(s) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक
__nfqnl_enqueue_packet_gso(काष्ठा net *net, काष्ठा nfqnl_instance *queue,
			   काष्ठा sk_buff *skb, काष्ठा nf_queue_entry *entry)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा nf_queue_entry *entry_seg;

	nf_bridge_adjust_segmented_data(skb);

	अगर (skb->next == शून्य) अणु /* last packet, no need to copy entry */
		काष्ठा sk_buff *gso_skb = entry->skb;
		entry->skb = skb;
		ret = __nfqnl_enqueue_packet(net, queue, entry);
		अगर (ret)
			entry->skb = gso_skb;
		वापस ret;
	पूर्ण

	skb_mark_not_on_list(skb);

	entry_seg = nf_queue_entry_dup(entry);
	अगर (entry_seg) अणु
		entry_seg->skb = skb;
		ret = __nfqnl_enqueue_packet(net, queue, entry_seg);
		अगर (ret)
			nf_queue_entry_मुक्त(entry_seg);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nfqnl_enqueue_packet(काष्ठा nf_queue_entry *entry, अचिन्हित पूर्णांक queuक्रमागत)
अणु
	अचिन्हित पूर्णांक queued;
	काष्ठा nfqnl_instance *queue;
	काष्ठा sk_buff *skb, *segs, *nskb;
	पूर्णांक err = -ENOBUFS;
	काष्ठा net *net = entry->state.net;
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(net);

	/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
	queue = instance_lookup(q, queuक्रमागत);
	अगर (!queue)
		वापस -ESRCH;

	अगर (queue->copy_mode == NFQNL_COPY_NONE)
		वापस -EINVAL;

	skb = entry->skb;

	चयन (entry->state.pf) अणु
	हाल NFPROTO_IPV4:
		skb->protocol = htons(ETH_P_IP);
		अवरोध;
	हाल NFPROTO_IPV6:
		skb->protocol = htons(ETH_P_IPV6);
		अवरोध;
	पूर्ण

	अगर ((queue->flags & NFQA_CFG_F_GSO) || !skb_is_gso(skb))
		वापस __nfqnl_enqueue_packet(net, queue, entry);

	nf_bridge_adjust_skb_data(skb);
	segs = skb_gso_segment(skb, 0);
	/* Does not use PTR_ERR to limit the number of error codes that can be
	 * वापसed by nf_queue.  For instance, callers rely on -ESRCH to
	 * mean 'ignore this hook'.
	 */
	अगर (IS_ERR_OR_शून्य(segs))
		जाओ out_err;
	queued = 0;
	err = 0;
	skb_list_walk_safe(segs, segs, nskb) अणु
		अगर (err == 0)
			err = __nfqnl_enqueue_packet_gso(net, queue,
							segs, entry);
		अगर (err == 0)
			queued++;
		अन्यथा
			kमुक्त_skb(segs);
	पूर्ण

	अगर (queued) अणु
		अगर (err) /* some segments are alपढ़ोy queued */
			nf_queue_entry_मुक्त(entry);
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
 out_err:
	nf_bridge_adjust_segmented_data(skb);
	वापस err;
पूर्ण

अटल पूर्णांक
nfqnl_mangle(व्योम *data, पूर्णांक data_len, काष्ठा nf_queue_entry *e, पूर्णांक dअगरf)
अणु
	काष्ठा sk_buff *nskb;

	अगर (dअगरf < 0) अणु
		अगर (pskb_trim(e->skb, data_len))
			वापस -ENOMEM;
	पूर्ण अन्यथा अगर (dअगरf > 0) अणु
		अगर (data_len > 0xFFFF)
			वापस -EINVAL;
		अगर (dअगरf > skb_tailroom(e->skb)) अणु
			nskb = skb_copy_expand(e->skb, skb_headroom(e->skb),
					       dअगरf, GFP_ATOMIC);
			अगर (!nskb)
				वापस -ENOMEM;
			kमुक्त_skb(e->skb);
			e->skb = nskb;
		पूर्ण
		skb_put(e->skb, dअगरf);
	पूर्ण
	अगर (skb_ensure_writable(e->skb, data_len))
		वापस -ENOMEM;
	skb_copy_to_linear_data(e->skb, data, data_len);
	e->skb->ip_summed = CHECKSUM_NONE;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfqnl_set_mode(काष्ठा nfqnl_instance *queue,
	       अचिन्हित अक्षर mode, अचिन्हित पूर्णांक range)
अणु
	पूर्णांक status = 0;

	spin_lock_bh(&queue->lock);
	चयन (mode) अणु
	हाल NFQNL_COPY_NONE:
	हाल NFQNL_COPY_META:
		queue->copy_mode = mode;
		queue->copy_range = 0;
		अवरोध;

	हाल NFQNL_COPY_PACKET:
		queue->copy_mode = mode;
		अगर (range == 0 || range > NFQNL_MAX_COPY_RANGE)
			queue->copy_range = NFQNL_MAX_COPY_RANGE;
		अन्यथा
			queue->copy_range = range;
		अवरोध;

	शेष:
		status = -EINVAL;

	पूर्ण
	spin_unlock_bh(&queue->lock);

	वापस status;
पूर्ण

अटल पूर्णांक
dev_cmp(काष्ठा nf_queue_entry *entry, अचिन्हित दीर्घ अगरindex)
अणु
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	पूर्णांक physinअगर, physoutअगर;

	physinअगर = nf_bridge_get_physinअगर(entry->skb);
	physoutअगर = nf_bridge_get_physoutअगर(entry->skb);

	अगर (physinअगर == अगरindex || physoutअगर == अगरindex)
		वापस 1;
#पूर्ण_अगर
	अगर (entry->state.in)
		अगर (entry->state.in->अगरindex == अगरindex)
			वापस 1;
	अगर (entry->state.out)
		अगर (entry->state.out->अगरindex == अगरindex)
			वापस 1;

	वापस 0;
पूर्ण

/* drop all packets with either indev or outdev == अगरindex from all queue
 * instances */
अटल व्योम
nfqnl_dev_drop(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	पूर्णांक i;
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(net);

	rcu_पढ़ो_lock();

	क्रम (i = 0; i < INSTANCE_BUCKETS; i++) अणु
		काष्ठा nfqnl_instance *inst;
		काष्ठा hlist_head *head = &q->instance_table[i];

		hlist_क्रम_each_entry_rcu(inst, head, hlist)
			nfqnl_flush(inst, dev_cmp, अगरindex);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक
nfqnl_rcv_dev_event(काष्ठा notअगरier_block *this,
		    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	/* Drop any packets associated with the करोwned device */
	अगर (event == NETDEV_DOWN)
		nfqnl_dev_drop(dev_net(dev), dev->अगरindex);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nfqnl_dev_notअगरier = अणु
	.notअगरier_call	= nfqnl_rcv_dev_event,
पूर्ण;

अटल व्योम nfqnl_nf_hook_drop(काष्ठा net *net)
अणु
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(net);
	पूर्णांक i;

	क्रम (i = 0; i < INSTANCE_BUCKETS; i++) अणु
		काष्ठा nfqnl_instance *inst;
		काष्ठा hlist_head *head = &q->instance_table[i];

		hlist_क्रम_each_entry_rcu(inst, head, hlist)
			nfqnl_flush(inst, शून्य, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक
nfqnl_rcv_nl_event(काष्ठा notअगरier_block *this,
		   अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netlink_notअगरy *n = ptr;
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(n->net);

	अगर (event == NETLINK_URELEASE && n->protocol == NETLINK_NETFILTER) अणु
		पूर्णांक i;

		/* destroy all instances क्रम this portid */
		spin_lock(&q->instances_lock);
		क्रम (i = 0; i < INSTANCE_BUCKETS; i++) अणु
			काष्ठा hlist_node *t2;
			काष्ठा nfqnl_instance *inst;
			काष्ठा hlist_head *head = &q->instance_table[i];

			hlist_क्रम_each_entry_safe(inst, t2, head, hlist) अणु
				अगर (n->portid == inst->peer_portid)
					__instance_destroy(inst);
			पूर्ण
		पूर्ण
		spin_unlock(&q->instances_lock);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nfqnl_rtnl_notअगरier = अणु
	.notअगरier_call	= nfqnl_rcv_nl_event,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nfqa_vlan_policy[NFQA_VLAN_MAX + 1] = अणु
	[NFQA_VLAN_TCI]		= अणु .type = NLA_U16पूर्ण,
	[NFQA_VLAN_PROTO]	= अणु .type = NLA_U16पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nfqa_verdict_policy[NFQA_MAX+1] = अणु
	[NFQA_VERDICT_HDR]	= अणु .len = माप(काष्ठा nfqnl_msg_verdict_hdr) पूर्ण,
	[NFQA_MARK]		= अणु .type = NLA_U32 पूर्ण,
	[NFQA_PAYLOAD]		= अणु .type = NLA_UNSPEC पूर्ण,
	[NFQA_CT]		= अणु .type = NLA_UNSPEC पूर्ण,
	[NFQA_EXP]		= अणु .type = NLA_UNSPEC पूर्ण,
	[NFQA_VLAN]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nfqa_verdict_batch_policy[NFQA_MAX+1] = अणु
	[NFQA_VERDICT_HDR]	= अणु .len = माप(काष्ठा nfqnl_msg_verdict_hdr) पूर्ण,
	[NFQA_MARK]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा nfqnl_instance *
verdict_instance_lookup(काष्ठा nfnl_queue_net *q, u16 queue_num, u32 nlportid)
अणु
	काष्ठा nfqnl_instance *queue;

	queue = instance_lookup(q, queue_num);
	अगर (!queue)
		वापस ERR_PTR(-ENODEV);

	अगर (queue->peer_portid != nlportid)
		वापस ERR_PTR(-EPERM);

	वापस queue;
पूर्ण

अटल काष्ठा nfqnl_msg_verdict_hdr*
verdicthdr_get(स्थिर काष्ठा nlattr * स्थिर nfqa[])
अणु
	काष्ठा nfqnl_msg_verdict_hdr *vhdr;
	अचिन्हित पूर्णांक verdict;

	अगर (!nfqa[NFQA_VERDICT_HDR])
		वापस शून्य;

	vhdr = nla_data(nfqa[NFQA_VERDICT_HDR]);
	verdict = ntohl(vhdr->verdict) & NF_VERDICT_MASK;
	अगर (verdict > NF_MAX_VERDICT || verdict == NF_STOLEN)
		वापस शून्य;
	वापस vhdr;
पूर्ण

अटल पूर्णांक nfq_id_after(अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक max)
अणु
	वापस (पूर्णांक)(id - max) > 0;
पूर्ण

अटल पूर्णांक nfqnl_recv_verdict_batch(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nfnl_info *info,
				    स्थिर काष्ठा nlattr * स्थिर nfqa[])
अणु
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(info->net);
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u16 queue_num = ntohs(nfmsg->res_id);
	काष्ठा nf_queue_entry *entry, *पंचांगp;
	काष्ठा nfqnl_msg_verdict_hdr *vhdr;
	काष्ठा nfqnl_instance *queue;
	अचिन्हित पूर्णांक verdict, maxid;
	LIST_HEAD(batch_list);

	queue = verdict_instance_lookup(q, queue_num,
					NETLINK_CB(skb).portid);
	अगर (IS_ERR(queue))
		वापस PTR_ERR(queue);

	vhdr = verdicthdr_get(nfqa);
	अगर (!vhdr)
		वापस -EINVAL;

	verdict = ntohl(vhdr->verdict);
	maxid = ntohl(vhdr->id);

	spin_lock_bh(&queue->lock);

	list_क्रम_each_entry_safe(entry, पंचांगp, &queue->queue_list, list) अणु
		अगर (nfq_id_after(entry->id, maxid))
			अवरोध;
		__dequeue_entry(queue, entry);
		list_add_tail(&entry->list, &batch_list);
	पूर्ण

	spin_unlock_bh(&queue->lock);

	अगर (list_empty(&batch_list))
		वापस -ENOENT;

	list_क्रम_each_entry_safe(entry, पंचांगp, &batch_list, list) अणु
		अगर (nfqa[NFQA_MARK])
			entry->skb->mark = ntohl(nla_get_be32(nfqa[NFQA_MARK]));

		nfqnl_reinject(entry, verdict);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा nf_conn *nfqnl_ct_parse(काष्ठा nfnl_ct_hook *nfnl_ct,
				      स्थिर काष्ठा nlmsghdr *nlh,
				      स्थिर काष्ठा nlattr * स्थिर nfqa[],
				      काष्ठा nf_queue_entry *entry,
				      क्रमागत ip_conntrack_info *ctinfo)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(entry->skb, ctinfo);
	अगर (ct == शून्य)
		वापस शून्य;

	अगर (nfnl_ct->parse(nfqa[NFQA_CT], ct) < 0)
		वापस शून्य;

	अगर (nfqa[NFQA_EXP])
		nfnl_ct->attach_expect(nfqa[NFQA_EXP], ct,
				      NETLINK_CB(entry->skb).portid,
				      nlmsg_report(nlh));
	वापस ct;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक nfqa_parse_bridge(काष्ठा nf_queue_entry *entry,
			     स्थिर काष्ठा nlattr * स्थिर nfqa[])
अणु
	अगर (nfqa[NFQA_VLAN]) अणु
		काष्ठा nlattr *tb[NFQA_VLAN_MAX + 1];
		पूर्णांक err;

		err = nla_parse_nested_deprecated(tb, NFQA_VLAN_MAX,
						  nfqa[NFQA_VLAN],
						  nfqa_vlan_policy, शून्य);
		अगर (err < 0)
			वापस err;

		अगर (!tb[NFQA_VLAN_TCI] || !tb[NFQA_VLAN_PROTO])
			वापस -EINVAL;

		__vlan_hwaccel_put_tag(entry->skb,
			nla_get_be16(tb[NFQA_VLAN_PROTO]),
			ntohs(nla_get_be16(tb[NFQA_VLAN_TCI])));
	पूर्ण

	अगर (nfqa[NFQA_L2HDR]) अणु
		पूर्णांक mac_header_len = entry->skb->network_header -
			entry->skb->mac_header;

		अगर (mac_header_len != nla_len(nfqa[NFQA_L2HDR]))
			वापस -EINVAL;
		अन्यथा अगर (mac_header_len > 0)
			स_नकल(skb_mac_header(entry->skb),
			       nla_data(nfqa[NFQA_L2HDR]),
			       mac_header_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nfqnl_recv_verdict(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			      स्थिर काष्ठा nlattr * स्थिर nfqa[])
अणु
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(info->net);
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u_पूर्णांक16_t queue_num = ntohs(nfmsg->res_id);
	काष्ठा nfqnl_msg_verdict_hdr *vhdr;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nfqnl_instance *queue;
	काष्ठा nf_queue_entry *entry;
	काष्ठा nfnl_ct_hook *nfnl_ct;
	काष्ठा nf_conn *ct = शून्य;
	अचिन्हित पूर्णांक verdict;
	पूर्णांक err;

	queue = verdict_instance_lookup(q, queue_num,
					NETLINK_CB(skb).portid);
	अगर (IS_ERR(queue))
		वापस PTR_ERR(queue);

	vhdr = verdicthdr_get(nfqa);
	अगर (!vhdr)
		वापस -EINVAL;

	verdict = ntohl(vhdr->verdict);

	entry = find_dequeue_entry(queue, ntohl(vhdr->id));
	अगर (entry == शून्य)
		वापस -ENOENT;

	/* rcu lock alपढ़ोy held from nfnl->call_rcu. */
	nfnl_ct = rcu_dereference(nfnl_ct_hook);

	अगर (nfqa[NFQA_CT]) अणु
		अगर (nfnl_ct != शून्य)
			ct = nfqnl_ct_parse(nfnl_ct, info->nlh, nfqa, entry,
					    &ctinfo);
	पूर्ण

	अगर (entry->state.pf == PF_BRIDGE) अणु
		err = nfqa_parse_bridge(entry, nfqa);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (nfqa[NFQA_PAYLOAD]) अणु
		u16 payload_len = nla_len(nfqa[NFQA_PAYLOAD]);
		पूर्णांक dअगरf = payload_len - entry->skb->len;

		अगर (nfqnl_mangle(nla_data(nfqa[NFQA_PAYLOAD]),
				 payload_len, entry, dअगरf) < 0)
			verdict = NF_DROP;

		अगर (ct && dअगरf)
			nfnl_ct->seq_adjust(entry->skb, ct, ctinfo, dअगरf);
	पूर्ण

	अगर (nfqa[NFQA_MARK])
		entry->skb->mark = ntohl(nla_get_be32(nfqa[NFQA_MARK]));

	nfqnl_reinject(entry, verdict);
	वापस 0;
पूर्ण

अटल पूर्णांक nfqnl_recv_unsupp(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा nla_policy nfqa_cfg_policy[NFQA_CFG_MAX+1] = अणु
	[NFQA_CFG_CMD]		= अणु .len = माप(काष्ठा nfqnl_msg_config_cmd) पूर्ण,
	[NFQA_CFG_PARAMS]	= अणु .len = माप(काष्ठा nfqnl_msg_config_params) पूर्ण,
	[NFQA_CFG_QUEUE_MAXLEN]	= अणु .type = NLA_U32 पूर्ण,
	[NFQA_CFG_MASK]		= अणु .type = NLA_U32 पूर्ण,
	[NFQA_CFG_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nf_queue_handler nfqh = अणु
	.outfn		= nfqnl_enqueue_packet,
	.nf_hook_drop	= nfqnl_nf_hook_drop,
पूर्ण;

अटल पूर्णांक nfqnl_recv_config(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर nfqa[])
अणु
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(info->net);
	काष्ठा nfgenmsg *nfmsg = nlmsg_data(info->nlh);
	u_पूर्णांक16_t queue_num = ntohs(nfmsg->res_id);
	काष्ठा nfqnl_msg_config_cmd *cmd = शून्य;
	काष्ठा nfqnl_instance *queue;
	__u32 flags = 0, mask = 0;
	पूर्णांक ret = 0;

	अगर (nfqa[NFQA_CFG_CMD]) अणु
		cmd = nla_data(nfqa[NFQA_CFG_CMD]);

		/* Obsolete commands without queue context */
		चयन (cmd->command) अणु
		हाल NFQNL_CFG_CMD_PF_BIND: वापस 0;
		हाल NFQNL_CFG_CMD_PF_UNBIND: वापस 0;
		पूर्ण
	पूर्ण

	/* Check अगर we support these flags in first place, dependencies should
	 * be there too not to अवरोध atomicity.
	 */
	अगर (nfqa[NFQA_CFG_FLAGS]) अणु
		अगर (!nfqa[NFQA_CFG_MASK]) अणु
			/* A mask is needed to specअगरy which flags are being
			 * changed.
			 */
			वापस -EINVAL;
		पूर्ण

		flags = ntohl(nla_get_be32(nfqa[NFQA_CFG_FLAGS]));
		mask = ntohl(nla_get_be32(nfqa[NFQA_CFG_MASK]));

		अगर (flags >= NFQA_CFG_F_MAX)
			वापस -EOPNOTSUPP;

#अगर !IS_ENABLED(CONFIG_NETWORK_SECMARK)
		अगर (flags & mask & NFQA_CFG_F_SECCTX)
			वापस -EOPNOTSUPP;
#पूर्ण_अगर
		अगर ((flags & mask & NFQA_CFG_F_CONNTRACK) &&
		    !rcu_access_poपूर्णांकer(nfnl_ct_hook)) अणु
#अगर_घोषित CONFIG_MODULES
			nfnl_unlock(NFNL_SUBSYS_QUEUE);
			request_module("ip_conntrack_netlink");
			nfnl_lock(NFNL_SUBSYS_QUEUE);
			अगर (rcu_access_poपूर्णांकer(nfnl_ct_hook))
				वापस -EAGAIN;
#पूर्ण_अगर
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	queue = instance_lookup(q, queue_num);
	अगर (queue && queue->peer_portid != NETLINK_CB(skb).portid) अणु
		ret = -EPERM;
		जाओ err_out_unlock;
	पूर्ण

	अगर (cmd != शून्य) अणु
		चयन (cmd->command) अणु
		हाल NFQNL_CFG_CMD_BIND:
			अगर (queue) अणु
				ret = -EBUSY;
				जाओ err_out_unlock;
			पूर्ण
			queue = instance_create(q, queue_num,
						NETLINK_CB(skb).portid);
			अगर (IS_ERR(queue)) अणु
				ret = PTR_ERR(queue);
				जाओ err_out_unlock;
			पूर्ण
			अवरोध;
		हाल NFQNL_CFG_CMD_UNBIND:
			अगर (!queue) अणु
				ret = -ENODEV;
				जाओ err_out_unlock;
			पूर्ण
			instance_destroy(q, queue);
			जाओ err_out_unlock;
		हाल NFQNL_CFG_CMD_PF_BIND:
		हाल NFQNL_CFG_CMD_PF_UNBIND:
			अवरोध;
		शेष:
			ret = -ENOTSUPP;
			जाओ err_out_unlock;
		पूर्ण
	पूर्ण

	अगर (!queue) अणु
		ret = -ENODEV;
		जाओ err_out_unlock;
	पूर्ण

	अगर (nfqa[NFQA_CFG_PARAMS]) अणु
		काष्ठा nfqnl_msg_config_params *params =
			nla_data(nfqa[NFQA_CFG_PARAMS]);

		nfqnl_set_mode(queue, params->copy_mode,
				ntohl(params->copy_range));
	पूर्ण

	अगर (nfqa[NFQA_CFG_QUEUE_MAXLEN]) अणु
		__be32 *queue_maxlen = nla_data(nfqa[NFQA_CFG_QUEUE_MAXLEN]);

		spin_lock_bh(&queue->lock);
		queue->queue_maxlen = ntohl(*queue_maxlen);
		spin_unlock_bh(&queue->lock);
	पूर्ण

	अगर (nfqa[NFQA_CFG_FLAGS]) अणु
		spin_lock_bh(&queue->lock);
		queue->flags &= ~mask;
		queue->flags |= flags & mask;
		spin_unlock_bh(&queue->lock);
	पूर्ण

err_out_unlock:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nfnl_callback nfqnl_cb[NFQNL_MSG_MAX] = अणु
	[NFQNL_MSG_PACKET]	= अणु
		.call		= nfqnl_recv_unsupp,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFQA_MAX,
	पूर्ण,
	[NFQNL_MSG_VERDICT]	= अणु
		.call		= nfqnl_recv_verdict,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFQA_MAX,
		.policy		= nfqa_verdict_policy
	पूर्ण,
	[NFQNL_MSG_CONFIG]	= अणु
		.call		= nfqnl_recv_config,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFQA_CFG_MAX,
		.policy		= nfqa_cfg_policy
	पूर्ण,
	[NFQNL_MSG_VERDICT_BATCH] = अणु
		.call		= nfqnl_recv_verdict_batch,
		.type		= NFNL_CB_RCU,
		.attr_count	= NFQA_MAX,
		.policy		= nfqa_verdict_batch_policy
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली nfqnl_subsys = अणु
	.name		= "nf_queue",
	.subsys_id	= NFNL_SUBSYS_QUEUE,
	.cb_count	= NFQNL_MSG_MAX,
	.cb		= nfqnl_cb,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
काष्ठा iter_state अणु
	काष्ठा seq_net_निजी p;
	अचिन्हित पूर्णांक bucket;
पूर्ण;

अटल काष्ठा hlist_node *get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा iter_state *st = seq->निजी;
	काष्ठा net *net;
	काष्ठा nfnl_queue_net *q;

	अगर (!st)
		वापस शून्य;

	net = seq_file_net(seq);
	q = nfnl_queue_pernet(net);
	क्रम (st->bucket = 0; st->bucket < INSTANCE_BUCKETS; st->bucket++) अणु
		अगर (!hlist_empty(&q->instance_table[st->bucket]))
			वापस q->instance_table[st->bucket].first;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा hlist_node *get_next(काष्ठा seq_file *seq, काष्ठा hlist_node *h)
अणु
	काष्ठा iter_state *st = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);

	h = h->next;
	जबतक (!h) अणु
		काष्ठा nfnl_queue_net *q;

		अगर (++st->bucket >= INSTANCE_BUCKETS)
			वापस शून्य;

		q = nfnl_queue_pernet(net);
		h = q->instance_table[st->bucket].first;
	पूर्ण
	वापस h;
पूर्ण

अटल काष्ठा hlist_node *get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा hlist_node *head;
	head = get_first(seq);

	अगर (head)
		जबतक (pos && (head = get_next(seq, head)))
			pos--;
	वापस pos ? शून्य : head;
पूर्ण

अटल व्योम *seq_start(काष्ठा seq_file *s, loff_t *pos)
	__acquires(nfnl_queue_pernet(seq_file_net(s))->instances_lock)
अणु
	spin_lock(&nfnl_queue_pernet(seq_file_net(s))->instances_lock);
	वापस get_idx(s, *pos);
पूर्ण

अटल व्योम *seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस get_next(s, v);
पूर्ण

अटल व्योम seq_stop(काष्ठा seq_file *s, व्योम *v)
	__releases(nfnl_queue_pernet(seq_file_net(s))->instances_lock)
अणु
	spin_unlock(&nfnl_queue_pernet(seq_file_net(s))->instances_lock);
पूर्ण

अटल पूर्णांक seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	स्थिर काष्ठा nfqnl_instance *inst = v;

	seq_म_लिखो(s, "%5u %6u %5u %1u %5u %5u %5u %8u %2d\n",
		   inst->queue_num,
		   inst->peer_portid, inst->queue_total,
		   inst->copy_mode, inst->copy_range,
		   inst->queue_dropped, inst->queue_user_dropped,
		   inst->id_sequence, 1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations nfqnl_seq_ops = अणु
	.start	= seq_start,
	.next	= seq_next,
	.stop	= seq_stop,
	.show	= seq_show,
पूर्ण;
#पूर्ण_अगर /* PROC_FS */

अटल पूर्णांक __net_init nfnl_queue_net_init(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(net);

	क्रम (i = 0; i < INSTANCE_BUCKETS; i++)
		INIT_HLIST_HEAD(&q->instance_table[i]);

	spin_lock_init(&q->instances_lock);

#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_net("nfnetlink_queue", 0440, net->nf.proc_netfilter,
			&nfqnl_seq_ops, माप(काष्ठा iter_state)))
		वापस -ENOMEM;
#पूर्ण_अगर
	nf_रेजिस्टर_queue_handler(net, &nfqh);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास nfnl_queue_net_निकास(काष्ठा net *net)
अणु
	काष्ठा nfnl_queue_net *q = nfnl_queue_pernet(net);
	अचिन्हित पूर्णांक i;

	nf_unरेजिस्टर_queue_handler(net);
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("nfnetlink_queue", net->nf.proc_netfilter);
#पूर्ण_अगर
	क्रम (i = 0; i < INSTANCE_BUCKETS; i++)
		WARN_ON_ONCE(!hlist_empty(&q->instance_table[i]));
पूर्ण

अटल व्योम nfnl_queue_net_निकास_batch(काष्ठा list_head *net_निकास_list)
अणु
	synchronize_rcu();
पूर्ण

अटल काष्ठा pernet_operations nfnl_queue_net_ops = अणु
	.init		= nfnl_queue_net_init,
	.निकास		= nfnl_queue_net_निकास,
	.निकास_batch	= nfnl_queue_net_निकास_batch,
	.id		= &nfnl_queue_net_id,
	.size		= माप(काष्ठा nfnl_queue_net),
पूर्ण;

अटल पूर्णांक __init nfnetlink_queue_init(व्योम)
अणु
	पूर्णांक status;

	status = रेजिस्टर_pernet_subsys(&nfnl_queue_net_ops);
	अगर (status < 0) अणु
		pr_err("failed to register pernet ops\n");
		जाओ out;
	पूर्ण

	netlink_रेजिस्टर_notअगरier(&nfqnl_rtnl_notअगरier);
	status = nfnetlink_subsys_रेजिस्टर(&nfqnl_subsys);
	अगर (status < 0) अणु
		pr_err("failed to create netlink socket\n");
		जाओ cleanup_netlink_notअगरier;
	पूर्ण

	status = रेजिस्टर_netdevice_notअगरier(&nfqnl_dev_notअगरier);
	अगर (status < 0) अणु
		pr_err("failed to register netdevice notifier\n");
		जाओ cleanup_netlink_subsys;
	पूर्ण

	वापस status;

cleanup_netlink_subsys:
	nfnetlink_subsys_unरेजिस्टर(&nfqnl_subsys);
cleanup_netlink_notअगरier:
	netlink_unरेजिस्टर_notअगरier(&nfqnl_rtnl_notअगरier);
	unरेजिस्टर_pernet_subsys(&nfnl_queue_net_ops);
out:
	वापस status;
पूर्ण

अटल व्योम __निकास nfnetlink_queue_fini(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&nfqnl_dev_notअगरier);
	nfnetlink_subsys_unरेजिस्टर(&nfqnl_subsys);
	netlink_unरेजिस्टर_notअगरier(&nfqnl_rtnl_notअगरier);
	unरेजिस्टर_pernet_subsys(&nfnl_queue_net_ops);

	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */
पूर्ण

MODULE_DESCRIPTION("netfilter packet queue handler");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_QUEUE);

module_init(nfnetlink_queue_init);
module_निकास(nfnetlink_queue_fini);
