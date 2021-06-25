<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  TUN - Universal TUN/TAP device driver.
 *  Copyright (C) 1999-2002 Maxim Krasnyansky <maxk@qualcomm.com>
 *
 *  $Id: tun.c,v 1.15 2002/03/01 02:44:24 maxk Exp $
 */

/*
 *  Changes:
 *
 *  Mike Kershaw <dragorn@kismetwireless.net> 2005/08/14
 *    Add TUNSETLINK ioctl to set the link encapsulation
 *
 *  Mark Smith <markzzzsmith@yahoo.com.au>
 *    Use eth_अक्रमom_addr() क्रम tap MAC address.
 *
 *  Harald Roelle <harald.roelle@अगरi.lmu.de>  2004/04/20
 *    Fixes in packet dropping, queue length setting and queue wakeup.
 *    Increased शेष tx queue length.
 *    Added ethtool API.
 *    Minor cleanups
 *
 *  Daniel Podlejski <underley@underley.eu.org>
 *    Modअगरications क्रम 2.3.99-pre5 kernel.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा DRV_NAME	"tun"
#घोषणा DRV_VERSION	"1.6"
#घोषणा DRV_DESCRIPTION	"Universal TUN/TAP device driver"
#घोषणा DRV_COPYRIGHT	"(C) 1999-2004 Max Krasnyansky <maxk@qualcomm.com>"

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/major.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/compat.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_tun.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crc32.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/virtio_net.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/sock.h>
#समावेश <net/xdp.h>
#समावेश <net/ip_tunnels.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uपन.स>
#समावेश <linux/skb_array.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ieee802154.h>
#समावेश <linux/अगर_ltalk.h>
#समावेश <uapi/linux/अगर_fddi.h>
#समावेश <uapi/linux/अगर_hippi.h>
#समावेश <uapi/linux/अगर_fc.h>
#समावेश <net/ax25.h>
#समावेश <net/rose.h>
#समावेश <net/6lowpan.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/proc_fs.h>

अटल व्योम tun_शेष_link_ksettings(काष्ठा net_device *dev,
				       काष्ठा ethtool_link_ksettings *cmd);

#घोषणा TUN_RX_PAD (NET_IP_ALIGN + NET_SKB_PAD)

/* TUN device flags */

/* IFF_ATTACH_QUEUE is never stored in device flags,
 * overload it to mean fasync when stored there.
 */
#घोषणा TUN_FASYNC	IFF_ATTACH_QUEUE
/* High bits in flags field are unused. */
#घोषणा TUN_VNET_LE     0x80000000
#घोषणा TUN_VNET_BE     0x40000000

#घोषणा TUN_FEATURES (IFF_NO_PI | IFF_ONE_QUEUE | IFF_VNET_HDR | \
		      IFF_MULTI_QUEUE | IFF_NAPI | IFF_NAPI_FRAGS)

#घोषणा GOODCOPY_LEN 128

#घोषणा FLT_EXACT_COUNT 8
काष्ठा tap_filter अणु
	अचिन्हित पूर्णांक    count;    /* Number of addrs. Zero means disabled */
	u32             mask[2];  /* Mask of the hashed addrs */
	अचिन्हित अक्षर	addr[FLT_EXACT_COUNT][ETH_ALEN];
पूर्ण;

/* MAX_TAP_QUEUES 256 is chosen to allow rx/tx queues to be equal
 * to max number of VCPUs in guest. */
#घोषणा MAX_TAP_QUEUES 256
#घोषणा MAX_TAP_FLOWS  4096

#घोषणा TUN_FLOW_EXPIRE (3 * HZ)

/* A tun_file connects an खोलो अक्षरacter device to a tuntap netdevice. It
 * also contains all socket related काष्ठाures (except sock_fprog and tap_filter)
 * to serve as one transmit queue क्रम tuntap device. The sock_fprog and
 * tap_filter were kept in tun_काष्ठा since they were used क्रम filtering क्रम the
 * netdevice not क्रम a specअगरic queue (at least I didn't see the requirement क्रम
 * this).
 *
 * RCU usage:
 * The tun_file and tun_काष्ठा are loosely coupled, the poपूर्णांकer from one to the
 * other can only be पढ़ो जबतक rcu_पढ़ो_lock or rtnl_lock is held.
 */
काष्ठा tun_file अणु
	काष्ठा sock sk;
	काष्ठा socket socket;
	काष्ठा tun_काष्ठा __rcu *tun;
	काष्ठा fasync_काष्ठा *fasync;
	/* only used क्रम fasnyc */
	अचिन्हित पूर्णांक flags;
	जोड़ अणु
		u16 queue_index;
		अचिन्हित पूर्णांक अगरindex;
	पूर्ण;
	काष्ठा napi_काष्ठा napi;
	bool napi_enabled;
	bool napi_frags_enabled;
	काष्ठा mutex napi_mutex;	/* Protects access to the above napi */
	काष्ठा list_head next;
	काष्ठा tun_काष्ठा *detached;
	काष्ठा ptr_ring tx_ring;
	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण;

काष्ठा tun_page अणु
	काष्ठा page *page;
	पूर्णांक count;
पूर्ण;

काष्ठा tun_flow_entry अणु
	काष्ठा hlist_node hash_link;
	काष्ठा rcu_head rcu;
	काष्ठा tun_काष्ठा *tun;

	u32 rxhash;
	u32 rps_rxhash;
	पूर्णांक queue_index;
	अचिन्हित दीर्घ updated ____cacheline_aligned_in_smp;
पूर्ण;

#घोषणा TUN_NUM_FLOW_ENTRIES 1024
#घोषणा TUN_MASK_FLOW_ENTRIES (TUN_NUM_FLOW_ENTRIES - 1)

काष्ठा tun_prog अणु
	काष्ठा rcu_head rcu;
	काष्ठा bpf_prog *prog;
पूर्ण;

/* Since the socket were moved to tun_file, to preserve the behavior of persist
 * device, socket filter, sndbuf and vnet header size were restore when the
 * file were attached to a persist device.
 */
काष्ठा tun_काष्ठा अणु
	काष्ठा tun_file __rcu	*tfiles[MAX_TAP_QUEUES];
	अचिन्हित पूर्णांक            numqueues;
	अचिन्हित पूर्णांक 		flags;
	kuid_t			owner;
	kgid_t			group;

	काष्ठा net_device	*dev;
	netdev_features_t	set_features;
#घोषणा TUN_USER_FEATURES (NETIF_F_HW_CSUM|NETIF_F_TSO_ECN|NETIF_F_TSO| \
			  NETIF_F_TSO6)

	पूर्णांक			align;
	पूर्णांक			vnet_hdr_sz;
	पूर्णांक			sndbuf;
	काष्ठा tap_filter	txflt;
	काष्ठा sock_fprog	fprog;
	/* रक्षित by rtnl lock */
	bool			filter_attached;
	u32			msg_enable;
	spinlock_t lock;
	काष्ठा hlist_head flows[TUN_NUM_FLOW_ENTRIES];
	काष्ठा समयr_list flow_gc_समयr;
	अचिन्हित दीर्घ ageing_समय;
	अचिन्हित पूर्णांक numdisabled;
	काष्ठा list_head disabled;
	व्योम *security;
	u32 flow_count;
	u32 rx_batched;
	atomic_दीर्घ_t rx_frame_errors;
	काष्ठा bpf_prog __rcu *xdp_prog;
	काष्ठा tun_prog __rcu *steering_prog;
	काष्ठा tun_prog __rcu *filter_prog;
	काष्ठा ethtool_link_ksettings link_ksettings;
पूर्ण;

काष्ठा veth अणु
	__be16 h_vlan_proto;
	__be16 h_vlan_TCI;
पूर्ण;

अटल पूर्णांक tun_napi_receive(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा tun_file *tfile = container_of(napi, काष्ठा tun_file, napi);
	काष्ठा sk_buff_head *queue = &tfile->sk.sk_ग_लिखो_queue;
	काष्ठा sk_buff_head process_queue;
	काष्ठा sk_buff *skb;
	पूर्णांक received = 0;

	__skb_queue_head_init(&process_queue);

	spin_lock(&queue->lock);
	skb_queue_splice_tail_init(queue, &process_queue);
	spin_unlock(&queue->lock);

	जबतक (received < budget && (skb = __skb_dequeue(&process_queue))) अणु
		napi_gro_receive(napi, skb);
		++received;
	पूर्ण

	अगर (!skb_queue_empty(&process_queue)) अणु
		spin_lock(&queue->lock);
		skb_queue_splice(&process_queue, queue);
		spin_unlock(&queue->lock);
	पूर्ण

	वापस received;
पूर्ण

अटल पूर्णांक tun_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक received;

	received = tun_napi_receive(napi, budget);

	अगर (received < budget)
		napi_complete_करोne(napi, received);

	वापस received;
पूर्ण

अटल व्योम tun_napi_init(काष्ठा tun_काष्ठा *tun, काष्ठा tun_file *tfile,
			  bool napi_en, bool napi_frags)
अणु
	tfile->napi_enabled = napi_en;
	tfile->napi_frags_enabled = napi_en && napi_frags;
	अगर (napi_en) अणु
		netअगर_tx_napi_add(tun->dev, &tfile->napi, tun_napi_poll,
				  NAPI_POLL_WEIGHT);
		napi_enable(&tfile->napi);
	पूर्ण
पूर्ण

अटल व्योम tun_napi_disable(काष्ठा tun_file *tfile)
अणु
	अगर (tfile->napi_enabled)
		napi_disable(&tfile->napi);
पूर्ण

अटल व्योम tun_napi_del(काष्ठा tun_file *tfile)
अणु
	अगर (tfile->napi_enabled)
		netअगर_napi_del(&tfile->napi);
पूर्ण

अटल bool tun_napi_frags_enabled(स्थिर काष्ठा tun_file *tfile)
अणु
	वापस tfile->napi_frags_enabled;
पूर्ण

#अगर_घोषित CONFIG_TUN_VNET_CROSS_LE
अटल अंतरभूत bool tun_legacy_is_little_endian(काष्ठा tun_काष्ठा *tun)
अणु
	वापस tun->flags & TUN_VNET_BE ? false :
		virtio_legacy_is_little_endian();
पूर्ण

अटल दीर्घ tun_get_vnet_be(काष्ठा tun_काष्ठा *tun, पूर्णांक __user *argp)
अणु
	पूर्णांक be = !!(tun->flags & TUN_VNET_BE);

	अगर (put_user(be, argp))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ tun_set_vnet_be(काष्ठा tun_काष्ठा *tun, पूर्णांक __user *argp)
अणु
	पूर्णांक be;

	अगर (get_user(be, argp))
		वापस -EFAULT;

	अगर (be)
		tun->flags |= TUN_VNET_BE;
	अन्यथा
		tun->flags &= ~TUN_VNET_BE;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत bool tun_legacy_is_little_endian(काष्ठा tun_काष्ठा *tun)
अणु
	वापस virtio_legacy_is_little_endian();
पूर्ण

अटल दीर्घ tun_get_vnet_be(काष्ठा tun_काष्ठा *tun, पूर्णांक __user *argp)
अणु
	वापस -EINVAL;
पूर्ण

अटल दीर्घ tun_set_vnet_be(काष्ठा tun_काष्ठा *tun, पूर्णांक __user *argp)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_TUN_VNET_CROSS_LE */

अटल अंतरभूत bool tun_is_little_endian(काष्ठा tun_काष्ठा *tun)
अणु
	वापस tun->flags & TUN_VNET_LE ||
		tun_legacy_is_little_endian(tun);
पूर्ण

अटल अंतरभूत u16 tun16_to_cpu(काष्ठा tun_काष्ठा *tun, __virtio16 val)
अणु
	वापस __virtio16_to_cpu(tun_is_little_endian(tun), val);
पूर्ण

अटल अंतरभूत __virtio16 cpu_to_tun16(काष्ठा tun_काष्ठा *tun, u16 val)
अणु
	वापस __cpu_to_virtio16(tun_is_little_endian(tun), val);
पूर्ण

अटल अंतरभूत u32 tun_hashfn(u32 rxhash)
अणु
	वापस rxhash & TUN_MASK_FLOW_ENTRIES;
पूर्ण

अटल काष्ठा tun_flow_entry *tun_flow_find(काष्ठा hlist_head *head, u32 rxhash)
अणु
	काष्ठा tun_flow_entry *e;

	hlist_क्रम_each_entry_rcu(e, head, hash_link) अणु
		अगर (e->rxhash == rxhash)
			वापस e;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा tun_flow_entry *tun_flow_create(काष्ठा tun_काष्ठा *tun,
					      काष्ठा hlist_head *head,
					      u32 rxhash, u16 queue_index)
अणु
	काष्ठा tun_flow_entry *e = kदो_स्मृति(माप(*e), GFP_ATOMIC);

	अगर (e) अणु
		netअगर_info(tun, tx_queued, tun->dev,
			   "create flow: hash %u index %u\n",
			   rxhash, queue_index);
		e->updated = jअगरfies;
		e->rxhash = rxhash;
		e->rps_rxhash = 0;
		e->queue_index = queue_index;
		e->tun = tun;
		hlist_add_head_rcu(&e->hash_link, head);
		++tun->flow_count;
	पूर्ण
	वापस e;
पूर्ण

अटल व्योम tun_flow_delete(काष्ठा tun_काष्ठा *tun, काष्ठा tun_flow_entry *e)
अणु
	netअगर_info(tun, tx_queued, tun->dev, "delete flow: hash %u index %u\n",
		   e->rxhash, e->queue_index);
	hlist_del_rcu(&e->hash_link);
	kमुक्त_rcu(e, rcu);
	--tun->flow_count;
पूर्ण

अटल व्योम tun_flow_flush(काष्ठा tun_काष्ठा *tun)
अणु
	पूर्णांक i;

	spin_lock_bh(&tun->lock);
	क्रम (i = 0; i < TUN_NUM_FLOW_ENTRIES; i++) अणु
		काष्ठा tun_flow_entry *e;
		काष्ठा hlist_node *n;

		hlist_क्रम_each_entry_safe(e, n, &tun->flows[i], hash_link)
			tun_flow_delete(tun, e);
	पूर्ण
	spin_unlock_bh(&tun->lock);
पूर्ण

अटल व्योम tun_flow_delete_by_queue(काष्ठा tun_काष्ठा *tun, u16 queue_index)
अणु
	पूर्णांक i;

	spin_lock_bh(&tun->lock);
	क्रम (i = 0; i < TUN_NUM_FLOW_ENTRIES; i++) अणु
		काष्ठा tun_flow_entry *e;
		काष्ठा hlist_node *n;

		hlist_क्रम_each_entry_safe(e, n, &tun->flows[i], hash_link) अणु
			अगर (e->queue_index == queue_index)
				tun_flow_delete(tun, e);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&tun->lock);
पूर्ण

अटल व्योम tun_flow_cleanup(काष्ठा समयr_list *t)
अणु
	काष्ठा tun_काष्ठा *tun = from_समयr(tun, t, flow_gc_समयr);
	अचिन्हित दीर्घ delay = tun->ageing_समय;
	अचिन्हित दीर्घ next_समयr = jअगरfies + delay;
	अचिन्हित दीर्घ count = 0;
	पूर्णांक i;

	spin_lock(&tun->lock);
	क्रम (i = 0; i < TUN_NUM_FLOW_ENTRIES; i++) अणु
		काष्ठा tun_flow_entry *e;
		काष्ठा hlist_node *n;

		hlist_क्रम_each_entry_safe(e, n, &tun->flows[i], hash_link) अणु
			अचिन्हित दीर्घ this_समयr;

			this_समयr = e->updated + delay;
			अगर (समय_beक्रमe_eq(this_समयr, jअगरfies)) अणु
				tun_flow_delete(tun, e);
				जारी;
			पूर्ण
			count++;
			अगर (समय_beक्रमe(this_समयr, next_समयr))
				next_समयr = this_समयr;
		पूर्ण
	पूर्ण

	अगर (count)
		mod_समयr(&tun->flow_gc_समयr, round_jअगरfies_up(next_समयr));
	spin_unlock(&tun->lock);
पूर्ण

अटल व्योम tun_flow_update(काष्ठा tun_काष्ठा *tun, u32 rxhash,
			    काष्ठा tun_file *tfile)
अणु
	काष्ठा hlist_head *head;
	काष्ठा tun_flow_entry *e;
	अचिन्हित दीर्घ delay = tun->ageing_समय;
	u16 queue_index = tfile->queue_index;

	head = &tun->flows[tun_hashfn(rxhash)];

	rcu_पढ़ो_lock();

	e = tun_flow_find(head, rxhash);
	अगर (likely(e)) अणु
		/* TODO: keep queueing to old queue until it's empty? */
		अगर (READ_ONCE(e->queue_index) != queue_index)
			WRITE_ONCE(e->queue_index, queue_index);
		अगर (e->updated != jअगरfies)
			e->updated = jअगरfies;
		sock_rps_record_flow_hash(e->rps_rxhash);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&tun->lock);
		अगर (!tun_flow_find(head, rxhash) &&
		    tun->flow_count < MAX_TAP_FLOWS)
			tun_flow_create(tun, head, rxhash, queue_index);

		अगर (!समयr_pending(&tun->flow_gc_समयr))
			mod_समयr(&tun->flow_gc_समयr,
				  round_jअगरfies_up(jअगरfies + delay));
		spin_unlock_bh(&tun->lock);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/* Save the hash received in the stack receive path and update the
 * flow_hash table accordingly.
 */
अटल अंतरभूत व्योम tun_flow_save_rps_rxhash(काष्ठा tun_flow_entry *e, u32 hash)
अणु
	अगर (unlikely(e->rps_rxhash != hash))
		e->rps_rxhash = hash;
पूर्ण

/* We try to identअगरy a flow through its rxhash. The reason that
 * we करो not check rxq no. is because some cards(e.g 82599), chooses
 * the rxq based on the txq where the last packet of the flow comes. As
 * the userspace application move between processors, we may get a
 * dअगरferent rxq no. here.
 */
अटल u16 tun_स्वतःmq_select_queue(काष्ठा tun_काष्ठा *tun, काष्ठा sk_buff *skb)
अणु
	काष्ठा tun_flow_entry *e;
	u32 txq = 0;
	u32 numqueues = 0;

	numqueues = READ_ONCE(tun->numqueues);

	txq = __skb_get_hash_symmetric(skb);
	e = tun_flow_find(&tun->flows[tun_hashfn(txq)], txq);
	अगर (e) अणु
		tun_flow_save_rps_rxhash(e, txq);
		txq = e->queue_index;
	पूर्ण अन्यथा अणु
		/* use multiply and shअगरt instead of expensive भागide */
		txq = ((u64)txq * numqueues) >> 32;
	पूर्ण

	वापस txq;
पूर्ण

अटल u16 tun_ebpf_select_queue(काष्ठा tun_काष्ठा *tun, काष्ठा sk_buff *skb)
अणु
	काष्ठा tun_prog *prog;
	u32 numqueues;
	u16 ret = 0;

	numqueues = READ_ONCE(tun->numqueues);
	अगर (!numqueues)
		वापस 0;

	prog = rcu_dereference(tun->steering_prog);
	अगर (prog)
		ret = bpf_prog_run_clear_cb(prog->prog, skb);

	वापस ret % numqueues;
पूर्ण

अटल u16 tun_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा net_device *sb_dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);
	u16 ret;

	rcu_पढ़ो_lock();
	अगर (rcu_dereference(tun->steering_prog))
		ret = tun_ebpf_select_queue(tun, skb);
	अन्यथा
		ret = tun_स्वतःmq_select_queue(tun, skb);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल अंतरभूत bool tun_not_capable(काष्ठा tun_काष्ठा *tun)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा net *net = dev_net(tun->dev);

	वापस ((uid_valid(tun->owner) && !uid_eq(cred->euid, tun->owner)) ||
		  (gid_valid(tun->group) && !in_egroup_p(tun->group))) &&
		!ns_capable(net->user_ns, CAP_NET_ADMIN);
पूर्ण

अटल व्योम tun_set_real_num_queues(काष्ठा tun_काष्ठा *tun)
अणु
	netअगर_set_real_num_tx_queues(tun->dev, tun->numqueues);
	netअगर_set_real_num_rx_queues(tun->dev, tun->numqueues);
पूर्ण

अटल व्योम tun_disable_queue(काष्ठा tun_काष्ठा *tun, काष्ठा tun_file *tfile)
अणु
	tfile->detached = tun;
	list_add_tail(&tfile->next, &tun->disabled);
	++tun->numdisabled;
पूर्ण

अटल काष्ठा tun_काष्ठा *tun_enable_queue(काष्ठा tun_file *tfile)
अणु
	काष्ठा tun_काष्ठा *tun = tfile->detached;

	tfile->detached = शून्य;
	list_del_init(&tfile->next);
	--tun->numdisabled;
	वापस tun;
पूर्ण

व्योम tun_ptr_मुक्त(व्योम *ptr)
अणु
	अगर (!ptr)
		वापस;
	अगर (tun_is_xdp_frame(ptr)) अणु
		काष्ठा xdp_frame *xdpf = tun_ptr_to_xdp(ptr);

		xdp_वापस_frame(xdpf);
	पूर्ण अन्यथा अणु
		__skb_array_destroy_skb(ptr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tun_ptr_मुक्त);

अटल व्योम tun_queue_purge(काष्ठा tun_file *tfile)
अणु
	व्योम *ptr;

	जबतक ((ptr = ptr_ring_consume(&tfile->tx_ring)) != शून्य)
		tun_ptr_मुक्त(ptr);

	skb_queue_purge(&tfile->sk.sk_ग_लिखो_queue);
	skb_queue_purge(&tfile->sk.sk_error_queue);
पूर्ण

अटल व्योम __tun_detach(काष्ठा tun_file *tfile, bool clean)
अणु
	काष्ठा tun_file *ntfile;
	काष्ठा tun_काष्ठा *tun;

	tun = rtnl_dereference(tfile->tun);

	अगर (tun && clean) अणु
		tun_napi_disable(tfile);
		tun_napi_del(tfile);
	पूर्ण

	अगर (tun && !tfile->detached) अणु
		u16 index = tfile->queue_index;
		BUG_ON(index >= tun->numqueues);

		rcu_assign_poपूर्णांकer(tun->tfiles[index],
				   tun->tfiles[tun->numqueues - 1]);
		ntfile = rtnl_dereference(tun->tfiles[index]);
		ntfile->queue_index = index;
		rcu_assign_poपूर्णांकer(tun->tfiles[tun->numqueues - 1],
				   शून्य);

		--tun->numqueues;
		अगर (clean) अणु
			RCU_INIT_POINTER(tfile->tun, शून्य);
			sock_put(&tfile->sk);
		पूर्ण अन्यथा
			tun_disable_queue(tun, tfile);

		synchronize_net();
		tun_flow_delete_by_queue(tun, tun->numqueues + 1);
		/* Drop पढ़ो queue */
		tun_queue_purge(tfile);
		tun_set_real_num_queues(tun);
	पूर्ण अन्यथा अगर (tfile->detached && clean) अणु
		tun = tun_enable_queue(tfile);
		sock_put(&tfile->sk);
	पूर्ण

	अगर (clean) अणु
		अगर (tun && tun->numqueues == 0 && tun->numdisabled == 0) अणु
			netअगर_carrier_off(tun->dev);

			अगर (!(tun->flags & IFF_PERSIST) &&
			    tun->dev->reg_state == NETREG_REGISTERED)
				unरेजिस्टर_netdevice(tun->dev);
		पूर्ण
		अगर (tun)
			xdp_rxq_info_unreg(&tfile->xdp_rxq);
		ptr_ring_cleanup(&tfile->tx_ring, tun_ptr_मुक्त);
		sock_put(&tfile->sk);
	पूर्ण
पूर्ण

अटल व्योम tun_detach(काष्ठा tun_file *tfile, bool clean)
अणु
	काष्ठा tun_काष्ठा *tun;
	काष्ठा net_device *dev;

	rtnl_lock();
	tun = rtnl_dereference(tfile->tun);
	dev = tun ? tun->dev : शून्य;
	__tun_detach(tfile, clean);
	अगर (dev)
		netdev_state_change(dev);
	rtnl_unlock();
पूर्ण

अटल व्योम tun_detach_all(काष्ठा net_device *dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);
	काष्ठा tun_file *tfile, *पंचांगp;
	पूर्णांक i, n = tun->numqueues;

	क्रम (i = 0; i < n; i++) अणु
		tfile = rtnl_dereference(tun->tfiles[i]);
		BUG_ON(!tfile);
		tun_napi_disable(tfile);
		tfile->socket.sk->sk_shutकरोwn = RCV_SHUTDOWN;
		tfile->socket.sk->sk_data_पढ़ोy(tfile->socket.sk);
		RCU_INIT_POINTER(tfile->tun, शून्य);
		--tun->numqueues;
	पूर्ण
	list_क्रम_each_entry(tfile, &tun->disabled, next) अणु
		tfile->socket.sk->sk_shutकरोwn = RCV_SHUTDOWN;
		tfile->socket.sk->sk_data_पढ़ोy(tfile->socket.sk);
		RCU_INIT_POINTER(tfile->tun, शून्य);
	पूर्ण
	BUG_ON(tun->numqueues != 0);

	synchronize_net();
	क्रम (i = 0; i < n; i++) अणु
		tfile = rtnl_dereference(tun->tfiles[i]);
		tun_napi_del(tfile);
		/* Drop पढ़ो queue */
		tun_queue_purge(tfile);
		xdp_rxq_info_unreg(&tfile->xdp_rxq);
		sock_put(&tfile->sk);
	पूर्ण
	list_क्रम_each_entry_safe(tfile, पंचांगp, &tun->disabled, next) अणु
		tun_enable_queue(tfile);
		tun_queue_purge(tfile);
		xdp_rxq_info_unreg(&tfile->xdp_rxq);
		sock_put(&tfile->sk);
	पूर्ण
	BUG_ON(tun->numdisabled != 0);

	अगर (tun->flags & IFF_PERSIST)
		module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक tun_attach(काष्ठा tun_काष्ठा *tun, काष्ठा file *file,
		      bool skip_filter, bool napi, bool napi_frags,
		      bool publish_tun)
अणु
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा net_device *dev = tun->dev;
	पूर्णांक err;

	err = security_tun_dev_attach(tfile->socket.sk, tun->security);
	अगर (err < 0)
		जाओ out;

	err = -EINVAL;
	अगर (rtnl_dereference(tfile->tun) && !tfile->detached)
		जाओ out;

	err = -EBUSY;
	अगर (!(tun->flags & IFF_MULTI_QUEUE) && tun->numqueues == 1)
		जाओ out;

	err = -E2BIG;
	अगर (!tfile->detached &&
	    tun->numqueues + tun->numdisabled == MAX_TAP_QUEUES)
		जाओ out;

	err = 0;

	/* Re-attach the filter to persist device */
	अगर (!skip_filter && (tun->filter_attached == true)) अणु
		lock_sock(tfile->socket.sk);
		err = sk_attach_filter(&tun->fprog, tfile->socket.sk);
		release_sock(tfile->socket.sk);
		अगर (!err)
			जाओ out;
	पूर्ण

	अगर (!tfile->detached &&
	    ptr_ring_resize(&tfile->tx_ring, dev->tx_queue_len,
			    GFP_KERNEL, tun_ptr_मुक्त)) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	tfile->queue_index = tun->numqueues;
	tfile->socket.sk->sk_shutकरोwn &= ~RCV_SHUTDOWN;

	अगर (tfile->detached) अणु
		/* Re-attach detached tfile, updating XDP queue_index */
		WARN_ON(!xdp_rxq_info_is_reg(&tfile->xdp_rxq));

		अगर (tfile->xdp_rxq.queue_index    != tfile->queue_index)
			tfile->xdp_rxq.queue_index = tfile->queue_index;
	पूर्ण अन्यथा अणु
		/* Setup XDP RX-queue info, क्रम new tfile getting attached */
		err = xdp_rxq_info_reg(&tfile->xdp_rxq,
				       tun->dev, tfile->queue_index, 0);
		अगर (err < 0)
			जाओ out;
		err = xdp_rxq_info_reg_mem_model(&tfile->xdp_rxq,
						 MEM_TYPE_PAGE_SHARED, शून्य);
		अगर (err < 0) अणु
			xdp_rxq_info_unreg(&tfile->xdp_rxq);
			जाओ out;
		पूर्ण
		err = 0;
	पूर्ण

	अगर (tfile->detached) अणु
		tun_enable_queue(tfile);
	पूर्ण अन्यथा अणु
		sock_hold(&tfile->sk);
		tun_napi_init(tun, tfile, napi, napi_frags);
	पूर्ण

	अगर (rtnl_dereference(tun->xdp_prog))
		sock_set_flag(&tfile->sk, SOCK_XDP);

	/* device is allowed to go away first, so no need to hold extra
	 * refcnt.
	 */

	/* Publish tfile->tun and tun->tfiles only after we've fully
	 * initialized tfile; otherwise we risk using half-initialized
	 * object.
	 */
	अगर (publish_tun)
		rcu_assign_poपूर्णांकer(tfile->tun, tun);
	rcu_assign_poपूर्णांकer(tun->tfiles[tun->numqueues], tfile);
	tun->numqueues++;
	tun_set_real_num_queues(tun);
out:
	वापस err;
पूर्ण

अटल काष्ठा tun_काष्ठा *tun_get(काष्ठा tun_file *tfile)
अणु
	काष्ठा tun_काष्ठा *tun;

	rcu_पढ़ो_lock();
	tun = rcu_dereference(tfile->tun);
	अगर (tun)
		dev_hold(tun->dev);
	rcu_पढ़ो_unlock();

	वापस tun;
पूर्ण

अटल व्योम tun_put(काष्ठा tun_काष्ठा *tun)
अणु
	dev_put(tun->dev);
पूर्ण

/* TAP filtering */
अटल व्योम addr_hash_set(u32 *mask, स्थिर u8 *addr)
अणु
	पूर्णांक n = ether_crc(ETH_ALEN, addr) >> 26;
	mask[n >> 5] |= (1 << (n & 31));
पूर्ण

अटल अचिन्हित पूर्णांक addr_hash_test(स्थिर u32 *mask, स्थिर u8 *addr)
अणु
	पूर्णांक n = ether_crc(ETH_ALEN, addr) >> 26;
	वापस mask[n >> 5] & (1 << (n & 31));
पूर्ण

अटल पूर्णांक update_filter(काष्ठा tap_filter *filter, व्योम __user *arg)
अणु
	काष्ठा अणु u8 u[ETH_ALEN]; पूर्ण *addr;
	काष्ठा tun_filter uf;
	पूर्णांक err, alen, n, nexact;

	अगर (copy_from_user(&uf, arg, माप(uf)))
		वापस -EFAULT;

	अगर (!uf.count) अणु
		/* Disabled */
		filter->count = 0;
		वापस 0;
	पूर्ण

	alen = ETH_ALEN * uf.count;
	addr = memdup_user(arg + माप(uf), alen);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);

	/* The filter is updated without holding any locks. Which is
	 * perfectly safe. We disable it first and in the worst
	 * हाल we'll accept a few undesired packets. */
	filter->count = 0;
	wmb();

	/* Use first set of addresses as an exact filter */
	क्रम (n = 0; n < uf.count && n < FLT_EXACT_COUNT; n++)
		स_नकल(filter->addr[n], addr[n].u, ETH_ALEN);

	nexact = n;

	/* Reमुख्यing multicast addresses are hashed,
	 * unicast will leave the filter disabled. */
	स_रखो(filter->mask, 0, माप(filter->mask));
	क्रम (; n < uf.count; n++) अणु
		अगर (!is_multicast_ether_addr(addr[n].u)) अणु
			err = 0; /* no filter */
			जाओ मुक्त_addr;
		पूर्ण
		addr_hash_set(filter->mask, addr[n].u);
	पूर्ण

	/* For ALLMULTI just set the mask to all ones.
	 * This overrides the mask populated above. */
	अगर ((uf.flags & TUN_FLT_ALLMULTI))
		स_रखो(filter->mask, ~0, माप(filter->mask));

	/* Now enable the filter */
	wmb();
	filter->count = nexact;

	/* Return the number of exact filters */
	err = nexact;
मुक्त_addr:
	kमुक्त(addr);
	वापस err;
पूर्ण

/* Returns: 0 - drop, !=0 - accept */
अटल पूर्णांक run_filter(काष्ठा tap_filter *filter, स्थिर काष्ठा sk_buff *skb)
अणु
	/* Cannot use eth_hdr(skb) here because skb_mac_hdr() is incorrect
	 * at this poपूर्णांक. */
	काष्ठा ethhdr *eh = (काष्ठा ethhdr *) skb->data;
	पूर्णांक i;

	/* Exact match */
	क्रम (i = 0; i < filter->count; i++)
		अगर (ether_addr_equal(eh->h_dest, filter->addr[i]))
			वापस 1;

	/* Inexact match (multicast only) */
	अगर (is_multicast_ether_addr(eh->h_dest))
		वापस addr_hash_test(filter->mask, eh->h_dest);

	वापस 0;
पूर्ण

/*
 * Checks whether the packet is accepted or not.
 * Returns: 0 - drop, !=0 - accept
 */
अटल पूर्णांक check_filter(काष्ठा tap_filter *filter, स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (!filter->count)
		वापस 1;

	वापस run_filter(filter, skb);
पूर्ण

/* Network device part of the driver */

अटल स्थिर काष्ठा ethtool_ops tun_ethtool_ops;

/* Net device detach from fd. */
अटल व्योम tun_net_uninit(काष्ठा net_device *dev)
अणु
	tun_detach_all(dev);
पूर्ण

/* Net device खोलो. */
अटल पूर्णांक tun_net_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_tx_start_all_queues(dev);

	वापस 0;
पूर्ण

/* Net device बंद. */
अटल पूर्णांक tun_net_बंद(काष्ठा net_device *dev)
अणु
	netअगर_tx_stop_all_queues(dev);
	वापस 0;
पूर्ण

/* Net device start xmit */
अटल व्योम tun_स्वतःmq_xmit(काष्ठा tun_काष्ठा *tun, काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_RPS
	अगर (tun->numqueues == 1 && अटल_branch_unlikely(&rps_needed)) अणु
		/* Select queue was not called क्रम the skbuff, so we extract the
		 * RPS hash and save it पूर्णांकo the flow_table here.
		 */
		काष्ठा tun_flow_entry *e;
		__u32 rxhash;

		rxhash = __skb_get_hash_symmetric(skb);
		e = tun_flow_find(&tun->flows[tun_hashfn(rxhash)], rxhash);
		अगर (e)
			tun_flow_save_rps_rxhash(e, rxhash);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित पूर्णांक run_ebpf_filter(काष्ठा tun_काष्ठा *tun,
				    काष्ठा sk_buff *skb,
				    पूर्णांक len)
अणु
	काष्ठा tun_prog *prog = rcu_dereference(tun->filter_prog);

	अगर (prog)
		len = bpf_prog_run_clear_cb(prog->prog, skb);

	वापस len;
पूर्ण

/* Net device start xmit */
अटल netdev_tx_t tun_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);
	पूर्णांक txq = skb->queue_mapping;
	काष्ठा tun_file *tfile;
	पूर्णांक len = skb->len;

	rcu_पढ़ो_lock();
	tfile = rcu_dereference(tun->tfiles[txq]);

	/* Drop packet अगर पूर्णांकerface is not attached */
	अगर (!tfile)
		जाओ drop;

	अगर (!rcu_dereference(tun->steering_prog))
		tun_स्वतःmq_xmit(tun, skb);

	netअगर_info(tun, tx_queued, tun->dev, "%s %d\n", __func__, skb->len);

	/* Drop अगर the filter करोes not like it.
	 * This is a noop अगर the filter is disabled.
	 * Filter can be enabled only क्रम the TAP devices. */
	अगर (!check_filter(&tun->txflt, skb))
		जाओ drop;

	अगर (tfile->socket.sk->sk_filter &&
	    sk_filter(tfile->socket.sk, skb))
		जाओ drop;

	len = run_ebpf_filter(tun, skb, len);
	अगर (len == 0 || pskb_trim(skb, len))
		जाओ drop;

	अगर (unlikely(skb_orphan_frags_rx(skb, GFP_ATOMIC)))
		जाओ drop;

	skb_tx_बारtamp(skb);

	/* Orphan the skb - required as we might hang on to it
	 * क्रम indefinite समय.
	 */
	skb_orphan(skb);

	nf_reset_ct(skb);

	अगर (ptr_ring_produce(&tfile->tx_ring, skb))
		जाओ drop;

	/* Notअगरy and wake up पढ़ोer process */
	अगर (tfile->flags & TUN_FASYNC)
		समाप्त_fasync(&tfile->fasync, SIGIO, POLL_IN);
	tfile->socket.sk->sk_data_पढ़ोy(tfile->socket.sk);

	rcu_पढ़ो_unlock();
	वापस NETDEV_TX_OK;

drop:
	atomic_दीर्घ_inc(&dev->tx_dropped);
	skb_tx_error(skb);
	kमुक्त_skb(skb);
	rcu_पढ़ो_unlock();
	वापस NET_XMIT_DROP;
पूर्ण

अटल व्योम tun_net_mclist(काष्ठा net_device *dev)
अणु
	/*
	 * This callback is supposed to deal with mc filter in
	 * _rx_ path and has nothing to करो with the _tx_ path.
	 * In rx path we always accept everything userspace gives us.
	 */
पूर्ण

अटल netdev_features_t tun_net_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	वापस (features & tun->set_features) | (features & ~TUN_USER_FEATURES);
पूर्ण

अटल व्योम tun_set_headroom(काष्ठा net_device *dev, पूर्णांक new_hr)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	अगर (new_hr < NET_SKB_PAD)
		new_hr = NET_SKB_PAD;

	tun->align = new_hr;
पूर्ण

अटल व्योम
tun_net_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	dev_get_tstats64(dev, stats);

	stats->rx_frame_errors +=
		(अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&tun->rx_frame_errors);
पूर्ण

अटल पूर्णांक tun_xdp_set(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);
	काष्ठा tun_file *tfile;
	काष्ठा bpf_prog *old_prog;
	पूर्णांक i;

	old_prog = rtnl_dereference(tun->xdp_prog);
	rcu_assign_poपूर्णांकer(tun->xdp_prog, prog);
	अगर (old_prog)
		bpf_prog_put(old_prog);

	क्रम (i = 0; i < tun->numqueues; i++) अणु
		tfile = rtnl_dereference(tun->tfiles[i]);
		अगर (prog)
			sock_set_flag(&tfile->sk, SOCK_XDP);
		अन्यथा
			sock_reset_flag(&tfile->sk, SOCK_XDP);
	पूर्ण
	list_क्रम_each_entry(tfile, &tun->disabled, next) अणु
		अगर (prog)
			sock_set_flag(&tfile->sk, SOCK_XDP);
		अन्यथा
			sock_reset_flag(&tfile->sk, SOCK_XDP);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tun_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस tun_xdp_set(dev, xdp->prog, xdp->extack);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tun_net_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	अगर (new_carrier) अणु
		काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

		अगर (!tun->numqueues)
			वापस -EPERM;

		netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops tun_netdev_ops = अणु
	.nकरो_uninit		= tun_net_uninit,
	.nकरो_खोलो		= tun_net_खोलो,
	.nकरो_stop		= tun_net_बंद,
	.nकरो_start_xmit		= tun_net_xmit,
	.nकरो_fix_features	= tun_net_fix_features,
	.nकरो_select_queue	= tun_select_queue,
	.nकरो_set_rx_headroom	= tun_set_headroom,
	.nकरो_get_stats64	= tun_net_get_stats64,
	.nकरो_change_carrier	= tun_net_change_carrier,
पूर्ण;

अटल व्योम __tun_xdp_flush_tfile(काष्ठा tun_file *tfile)
अणु
	/* Notअगरy and wake up पढ़ोer process */
	अगर (tfile->flags & TUN_FASYNC)
		समाप्त_fasync(&tfile->fasync, SIGIO, POLL_IN);
	tfile->socket.sk->sk_data_पढ़ोy(tfile->socket.sk);
पूर्ण

अटल पूर्णांक tun_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n,
			काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);
	काष्ठा tun_file *tfile;
	u32 numqueues;
	पूर्णांक nxmit = 0;
	पूर्णांक i;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	rcu_पढ़ो_lock();

resample:
	numqueues = READ_ONCE(tun->numqueues);
	अगर (!numqueues) अणु
		rcu_पढ़ो_unlock();
		वापस -ENXIO; /* Caller will मुक्त/वापस all frames */
	पूर्ण

	tfile = rcu_dereference(tun->tfiles[smp_processor_id() %
					    numqueues]);
	अगर (unlikely(!tfile))
		जाओ resample;

	spin_lock(&tfile->tx_ring.producer_lock);
	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdp = frames[i];
		/* Encode the XDP flag पूर्णांकo lowest bit क्रम consumer to dअगरfer
		 * XDP buffer from sk_buff.
		 */
		व्योम *frame = tun_xdp_to_ptr(xdp);

		अगर (__ptr_ring_produce(&tfile->tx_ring, frame)) अणु
			atomic_दीर्घ_inc(&dev->tx_dropped);
			अवरोध;
		पूर्ण
		nxmit++;
	पूर्ण
	spin_unlock(&tfile->tx_ring.producer_lock);

	अगर (flags & XDP_XMIT_FLUSH)
		__tun_xdp_flush_tfile(tfile);

	rcu_पढ़ो_unlock();
	वापस nxmit;
पूर्ण

अटल पूर्णांक tun_xdp_tx(काष्ठा net_device *dev, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_frame *frame = xdp_convert_buff_to_frame(xdp);
	पूर्णांक nxmit;

	अगर (unlikely(!frame))
		वापस -EOVERFLOW;

	nxmit = tun_xdp_xmit(dev, 1, &frame, XDP_XMIT_FLUSH);
	अगर (!nxmit)
		xdp_वापस_frame_rx_napi(frame);
	वापस nxmit;
पूर्ण

अटल स्थिर काष्ठा net_device_ops tap_netdev_ops = अणु
	.nकरो_uninit		= tun_net_uninit,
	.nकरो_खोलो		= tun_net_खोलो,
	.nकरो_stop		= tun_net_बंद,
	.nकरो_start_xmit		= tun_net_xmit,
	.nकरो_fix_features	= tun_net_fix_features,
	.nकरो_set_rx_mode	= tun_net_mclist,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_select_queue	= tun_select_queue,
	.nकरो_features_check	= passthru_features_check,
	.nकरो_set_rx_headroom	= tun_set_headroom,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_bpf		= tun_xdp,
	.nकरो_xdp_xmit		= tun_xdp_xmit,
	.nकरो_change_carrier	= tun_net_change_carrier,
पूर्ण;

अटल व्योम tun_flow_init(काष्ठा tun_काष्ठा *tun)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TUN_NUM_FLOW_ENTRIES; i++)
		INIT_HLIST_HEAD(&tun->flows[i]);

	tun->ageing_समय = TUN_FLOW_EXPIRE;
	समयr_setup(&tun->flow_gc_समयr, tun_flow_cleanup, 0);
	mod_समयr(&tun->flow_gc_समयr,
		  round_jअगरfies_up(jअगरfies + tun->ageing_समय));
पूर्ण

अटल व्योम tun_flow_uninit(काष्ठा tun_काष्ठा *tun)
अणु
	del_समयr_sync(&tun->flow_gc_समयr);
	tun_flow_flush(tun);
पूर्ण

#घोषणा MIN_MTU 68
#घोषणा MAX_MTU 65535

/* Initialize net device. */
अटल व्योम tun_net_init(काष्ठा net_device *dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	चयन (tun->flags & TUN_TYPE_MASK) अणु
	हाल IFF_TUN:
		dev->netdev_ops = &tun_netdev_ops;
		dev->header_ops = &ip_tunnel_header_ops;

		/* Poपूर्णांक-to-Poपूर्णांक TUN Device */
		dev->hard_header_len = 0;
		dev->addr_len = 0;
		dev->mtu = 1500;

		/* Zero header length */
		dev->type = ARPHRD_NONE;
		dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
		अवरोध;

	हाल IFF_TAP:
		dev->netdev_ops = &tap_netdev_ops;
		/* Ethernet TAP Device */
		ether_setup(dev);
		dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

		eth_hw_addr_अक्रमom(dev);

		अवरोध;
	पूर्ण

	dev->min_mtu = MIN_MTU;
	dev->max_mtu = MAX_MTU - dev->hard_header_len;
पूर्ण

अटल bool tun_sock_ग_लिखोable(काष्ठा tun_काष्ठा *tun, काष्ठा tun_file *tfile)
अणु
	काष्ठा sock *sk = tfile->socket.sk;

	वापस (tun->dev->flags & IFF_UP) && sock_ग_लिखोable(sk);
पूर्ण

/* Character device part */

/* Poll */
अटल __poll_t tun_chr_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा tun_काष्ठा *tun = tun_get(tfile);
	काष्ठा sock *sk;
	__poll_t mask = 0;

	अगर (!tun)
		वापस EPOLLERR;

	sk = tfile->socket.sk;

	poll_रुको(file, sk_sleep(sk), रुको);

	अगर (!ptr_ring_empty(&tfile->tx_ring))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* Make sure SOCKWQ_ASYNC_NOSPACE is set अगर not writable to
	 * guarantee EPOLLOUT to be उठाओd by either here or
	 * tun_sock_ग_लिखो_space(). Then process could get notअगरication
	 * after it ग_लिखोs to a करोwn device and meets -EIO.
	 */
	अगर (tun_sock_ग_लिखोable(tun, tfile) ||
	    (!test_and_set_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->flags) &&
	     tun_sock_ग_लिखोable(tun, tfile)))
		mask |= EPOLLOUT | EPOLLWRNORM;

	अगर (tun->dev->reg_state != NETREG_REGISTERED)
		mask = EPOLLERR;

	tun_put(tun);
	वापस mask;
पूर्ण

अटल काष्ठा sk_buff *tun_napi_alloc_frags(काष्ठा tun_file *tfile,
					    माप_प्रकार len,
					    स्थिर काष्ठा iov_iter *it)
अणु
	काष्ठा sk_buff *skb;
	माप_प्रकार linear;
	पूर्णांक err;
	पूर्णांक i;

	अगर (it->nr_segs > MAX_SKB_FRAGS + 1)
		वापस ERR_PTR(-EMSGSIZE);

	local_bh_disable();
	skb = napi_get_frags(&tfile->napi);
	local_bh_enable();
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	linear = iov_iter_single_seg_count(it);
	err = __skb_grow(skb, linear);
	अगर (err)
		जाओ मुक्त;

	skb->len = len;
	skb->data_len = len - linear;
	skb->truesize += skb->data_len;

	क्रम (i = 1; i < it->nr_segs; i++) अणु
		माप_प्रकार fragsz = it->iov[i].iov_len;
		काष्ठा page *page;
		व्योम *frag;

		अगर (fragsz == 0 || fragsz > PAGE_SIZE) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण
		frag = netdev_alloc_frag(fragsz);
		अगर (!frag) अणु
			err = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
		page = virt_to_head_page(frag);
		skb_fill_page_desc(skb, i - 1, page,
				   frag - page_address(page), fragsz);
	पूर्ण

	वापस skb;
मुक्त:
	/* मुक्तs skb and all frags allocated with napi_alloc_frag() */
	napi_मुक्त_frags(&tfile->napi);
	वापस ERR_PTR(err);
पूर्ण

/* prepad is the amount to reserve at front.  len is length after that.
 * linear is a hपूर्णांक as to how much to copy (usually headers). */
अटल काष्ठा sk_buff *tun_alloc_skb(काष्ठा tun_file *tfile,
				     माप_प्रकार prepad, माप_प्रकार len,
				     माप_प्रकार linear, पूर्णांक noblock)
अणु
	काष्ठा sock *sk = tfile->socket.sk;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	/* Under a page?  Don't bother with paged skb. */
	अगर (prepad + len < PAGE_SIZE || !linear)
		linear = len;

	skb = sock_alloc_send_pskb(sk, prepad + linear, len - linear, noblock,
				   &err, 0);
	अगर (!skb)
		वापस ERR_PTR(err);

	skb_reserve(skb, prepad);
	skb_put(skb, linear);
	skb->data_len = len - linear;
	skb->len += len - linear;

	वापस skb;
पूर्ण

अटल व्योम tun_rx_batched(काष्ठा tun_काष्ठा *tun, काष्ठा tun_file *tfile,
			   काष्ठा sk_buff *skb, पूर्णांक more)
अणु
	काष्ठा sk_buff_head *queue = &tfile->sk.sk_ग_लिखो_queue;
	काष्ठा sk_buff_head process_queue;
	u32 rx_batched = tun->rx_batched;
	bool rcv = false;

	अगर (!rx_batched || (!more && skb_queue_empty(queue))) अणु
		local_bh_disable();
		skb_record_rx_queue(skb, tfile->queue_index);
		netअगर_receive_skb(skb);
		local_bh_enable();
		वापस;
	पूर्ण

	spin_lock(&queue->lock);
	अगर (!more || skb_queue_len(queue) == rx_batched) अणु
		__skb_queue_head_init(&process_queue);
		skb_queue_splice_tail_init(queue, &process_queue);
		rcv = true;
	पूर्ण अन्यथा अणु
		__skb_queue_tail(queue, skb);
	पूर्ण
	spin_unlock(&queue->lock);

	अगर (rcv) अणु
		काष्ठा sk_buff *nskb;

		local_bh_disable();
		जबतक ((nskb = __skb_dequeue(&process_queue))) अणु
			skb_record_rx_queue(nskb, tfile->queue_index);
			netअगर_receive_skb(nskb);
		पूर्ण
		skb_record_rx_queue(skb, tfile->queue_index);
		netअगर_receive_skb(skb);
		local_bh_enable();
	पूर्ण
पूर्ण

अटल bool tun_can_build_skb(काष्ठा tun_काष्ठा *tun, काष्ठा tun_file *tfile,
			      पूर्णांक len, पूर्णांक noblock, bool zerocopy)
अणु
	अगर ((tun->flags & TUN_TYPE_MASK) != IFF_TAP)
		वापस false;

	अगर (tfile->socket.sk->sk_sndbuf != पूर्णांक_उच्च)
		वापस false;

	अगर (!noblock)
		वापस false;

	अगर (zerocopy)
		वापस false;

	अगर (SKB_DATA_ALIGN(len + TUN_RX_PAD) +
	    SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) > PAGE_SIZE)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा sk_buff *__tun_build_skb(काष्ठा tun_file *tfile,
				       काष्ठा page_frag *alloc_frag, अक्षर *buf,
				       पूर्णांक buflen, पूर्णांक len, पूर्णांक pad)
अणु
	काष्ठा sk_buff *skb = build_skb(buf, buflen);

	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	skb_reserve(skb, pad);
	skb_put(skb, len);
	skb_set_owner_w(skb, tfile->socket.sk);

	get_page(alloc_frag->page);
	alloc_frag->offset += buflen;

	वापस skb;
पूर्ण

अटल पूर्णांक tun_xdp_act(काष्ठा tun_काष्ठा *tun, काष्ठा bpf_prog *xdp_prog,
		       काष्ठा xdp_buff *xdp, u32 act)
अणु
	पूर्णांक err;

	चयन (act) अणु
	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(tun->dev, xdp, xdp_prog);
		अगर (err)
			वापस err;
		अवरोध;
	हाल XDP_TX:
		err = tun_xdp_tx(tun->dev, xdp);
		अगर (err < 0)
			वापस err;
		अवरोध;
	हाल XDP_PASS:
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(tun->dev, xdp_prog, act);
		fallthrough;
	हाल XDP_DROP:
		atomic_दीर्घ_inc(&tun->dev->rx_dropped);
		अवरोध;
	पूर्ण

	वापस act;
पूर्ण

अटल काष्ठा sk_buff *tun_build_skb(काष्ठा tun_काष्ठा *tun,
				     काष्ठा tun_file *tfile,
				     काष्ठा iov_iter *from,
				     काष्ठा virtio_net_hdr *hdr,
				     पूर्णांक len, पूर्णांक *skb_xdp)
अणु
	काष्ठा page_frag *alloc_frag = &current->task_frag;
	काष्ठा bpf_prog *xdp_prog;
	पूर्णांक buflen = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	अक्षर *buf;
	माप_प्रकार copied;
	पूर्णांक pad = TUN_RX_PAD;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(tun->xdp_prog);
	अगर (xdp_prog)
		pad += XDP_PACKET_HEADROOM;
	buflen += SKB_DATA_ALIGN(len + pad);
	rcu_पढ़ो_unlock();

	alloc_frag->offset = ALIGN((u64)alloc_frag->offset, SMP_CACHE_BYTES);
	अगर (unlikely(!skb_page_frag_refill(buflen, alloc_frag, GFP_KERNEL)))
		वापस ERR_PTR(-ENOMEM);

	buf = (अक्षर *)page_address(alloc_frag->page) + alloc_frag->offset;
	copied = copy_page_from_iter(alloc_frag->page,
				     alloc_frag->offset + pad,
				     len, from);
	अगर (copied != len)
		वापस ERR_PTR(-EFAULT);

	/* There's a small winकरोw that XDP may be set after the check
	 * of xdp_prog above, this should be rare and क्रम simplicity
	 * we करो XDP on skb in हाल the headroom is not enough.
	 */
	अगर (hdr->gso_type || !xdp_prog) अणु
		*skb_xdp = 1;
		वापस __tun_build_skb(tfile, alloc_frag, buf, buflen, len,
				       pad);
	पूर्ण

	*skb_xdp = 0;

	local_bh_disable();
	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(tun->xdp_prog);
	अगर (xdp_prog) अणु
		काष्ठा xdp_buff xdp;
		u32 act;

		xdp_init_buff(&xdp, buflen, &tfile->xdp_rxq);
		xdp_prepare_buff(&xdp, buf, pad, len, false);

		act = bpf_prog_run_xdp(xdp_prog, &xdp);
		अगर (act == XDP_REसूचीECT || act == XDP_TX) अणु
			get_page(alloc_frag->page);
			alloc_frag->offset += buflen;
		पूर्ण
		err = tun_xdp_act(tun, xdp_prog, &xdp, act);
		अगर (err < 0) अणु
			अगर (act == XDP_REसूचीECT || act == XDP_TX)
				put_page(alloc_frag->page);
			जाओ out;
		पूर्ण

		अगर (err == XDP_REसूचीECT)
			xdp_करो_flush();
		अगर (err != XDP_PASS)
			जाओ out;

		pad = xdp.data - xdp.data_hard_start;
		len = xdp.data_end - xdp.data;
	पूर्ण
	rcu_पढ़ो_unlock();
	local_bh_enable();

	वापस __tun_build_skb(tfile, alloc_frag, buf, buflen, len, pad);

out:
	rcu_पढ़ो_unlock();
	local_bh_enable();
	वापस शून्य;
पूर्ण

/* Get packet from user space buffer */
अटल sमाप_प्रकार tun_get_user(काष्ठा tun_काष्ठा *tun, काष्ठा tun_file *tfile,
			    व्योम *msg_control, काष्ठा iov_iter *from,
			    पूर्णांक noblock, bool more)
अणु
	काष्ठा tun_pi pi = अणु 0, cpu_to_be16(ETH_P_IP) पूर्ण;
	काष्ठा sk_buff *skb;
	माप_प्रकार total_len = iov_iter_count(from);
	माप_प्रकार len = total_len, align = tun->align, linear;
	काष्ठा virtio_net_hdr gso = अणु 0 पूर्ण;
	पूर्णांक good_linear;
	पूर्णांक copylen;
	bool zerocopy = false;
	पूर्णांक err;
	u32 rxhash = 0;
	पूर्णांक skb_xdp = 1;
	bool frags = tun_napi_frags_enabled(tfile);

	अगर (!(tun->flags & IFF_NO_PI)) अणु
		अगर (len < माप(pi))
			वापस -EINVAL;
		len -= माप(pi);

		अगर (!copy_from_iter_full(&pi, माप(pi), from))
			वापस -EFAULT;
	पूर्ण

	अगर (tun->flags & IFF_VNET_HDR) अणु
		पूर्णांक vnet_hdr_sz = READ_ONCE(tun->vnet_hdr_sz);

		अगर (len < vnet_hdr_sz)
			वापस -EINVAL;
		len -= vnet_hdr_sz;

		अगर (!copy_from_iter_full(&gso, माप(gso), from))
			वापस -EFAULT;

		अगर ((gso.flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) &&
		    tun16_to_cpu(tun, gso.csum_start) + tun16_to_cpu(tun, gso.csum_offset) + 2 > tun16_to_cpu(tun, gso.hdr_len))
			gso.hdr_len = cpu_to_tun16(tun, tun16_to_cpu(tun, gso.csum_start) + tun16_to_cpu(tun, gso.csum_offset) + 2);

		अगर (tun16_to_cpu(tun, gso.hdr_len) > len)
			वापस -EINVAL;
		iov_iter_advance(from, vnet_hdr_sz - माप(gso));
	पूर्ण

	अगर ((tun->flags & TUN_TYPE_MASK) == IFF_TAP) अणु
		align += NET_IP_ALIGN;
		अगर (unlikely(len < ETH_HLEN ||
			     (gso.hdr_len && tun16_to_cpu(tun, gso.hdr_len) < ETH_HLEN)))
			वापस -EINVAL;
	पूर्ण

	good_linear = SKB_MAX_HEAD(align);

	अगर (msg_control) अणु
		काष्ठा iov_iter i = *from;

		/* There are 256 bytes to be copied in skb, so there is
		 * enough room क्रम skb expand head in हाल it is used.
		 * The rest of the buffer is mapped from userspace.
		 */
		copylen = gso.hdr_len ? tun16_to_cpu(tun, gso.hdr_len) : GOODCOPY_LEN;
		अगर (copylen > good_linear)
			copylen = good_linear;
		linear = copylen;
		iov_iter_advance(&i, copylen);
		अगर (iov_iter_npages(&i, पूर्णांक_उच्च) <= MAX_SKB_FRAGS)
			zerocopy = true;
	पूर्ण

	अगर (!frags && tun_can_build_skb(tun, tfile, len, noblock, zerocopy)) अणु
		/* For the packet that is not easy to be processed
		 * (e.g gso or jumbo packet), we will करो it at after
		 * skb was created with generic XDP routine.
		 */
		skb = tun_build_skb(tun, tfile, from, &gso, len, &skb_xdp);
		अगर (IS_ERR(skb)) अणु
			atomic_दीर्घ_inc(&tun->dev->rx_dropped);
			वापस PTR_ERR(skb);
		पूर्ण
		अगर (!skb)
			वापस total_len;
	पूर्ण अन्यथा अणु
		अगर (!zerocopy) अणु
			copylen = len;
			अगर (tun16_to_cpu(tun, gso.hdr_len) > good_linear)
				linear = good_linear;
			अन्यथा
				linear = tun16_to_cpu(tun, gso.hdr_len);
		पूर्ण

		अगर (frags) अणु
			mutex_lock(&tfile->napi_mutex);
			skb = tun_napi_alloc_frags(tfile, copylen, from);
			/* tun_napi_alloc_frags() enक्रमces a layout क्रम the skb.
			 * If zerocopy is enabled, then this layout will be
			 * overwritten by zerocopy_sg_from_iter().
			 */
			zerocopy = false;
		पूर्ण अन्यथा अणु
			skb = tun_alloc_skb(tfile, align, copylen, linear,
					    noblock);
		पूर्ण

		अगर (IS_ERR(skb)) अणु
			अगर (PTR_ERR(skb) != -EAGAIN)
				atomic_दीर्घ_inc(&tun->dev->rx_dropped);
			अगर (frags)
				mutex_unlock(&tfile->napi_mutex);
			वापस PTR_ERR(skb);
		पूर्ण

		अगर (zerocopy)
			err = zerocopy_sg_from_iter(skb, from);
		अन्यथा
			err = skb_copy_datagram_from_iter(skb, 0, from, len);

		अगर (err) अणु
			err = -EFAULT;
drop:
			atomic_दीर्घ_inc(&tun->dev->rx_dropped);
			kमुक्त_skb(skb);
			अगर (frags) अणु
				tfile->napi.skb = शून्य;
				mutex_unlock(&tfile->napi_mutex);
			पूर्ण

			वापस err;
		पूर्ण
	पूर्ण

	अगर (virtio_net_hdr_to_skb(skb, &gso, tun_is_little_endian(tun))) अणु
		atomic_दीर्घ_inc(&tun->rx_frame_errors);
		kमुक्त_skb(skb);
		अगर (frags) अणु
			tfile->napi.skb = शून्य;
			mutex_unlock(&tfile->napi_mutex);
		पूर्ण

		वापस -EINVAL;
	पूर्ण

	चयन (tun->flags & TUN_TYPE_MASK) अणु
	हाल IFF_TUN:
		अगर (tun->flags & IFF_NO_PI) अणु
			u8 ip_version = skb->len ? (skb->data[0] >> 4) : 0;

			चयन (ip_version) अणु
			हाल 4:
				pi.proto = htons(ETH_P_IP);
				अवरोध;
			हाल 6:
				pi.proto = htons(ETH_P_IPV6);
				अवरोध;
			शेष:
				atomic_दीर्घ_inc(&tun->dev->rx_dropped);
				kमुक्त_skb(skb);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		skb_reset_mac_header(skb);
		skb->protocol = pi.proto;
		skb->dev = tun->dev;
		अवरोध;
	हाल IFF_TAP:
		अगर (frags && !pskb_may_pull(skb, ETH_HLEN)) अणु
			err = -ENOMEM;
			जाओ drop;
		पूर्ण
		skb->protocol = eth_type_trans(skb, tun->dev);
		अवरोध;
	पूर्ण

	/* copy skb_ubuf_info क्रम callback when skb has no error */
	अगर (zerocopy) अणु
		skb_zcopy_init(skb, msg_control);
	पूर्ण अन्यथा अगर (msg_control) अणु
		काष्ठा ubuf_info *uarg = msg_control;
		uarg->callback(शून्य, uarg, false);
	पूर्ण

	skb_reset_network_header(skb);
	skb_probe_transport_header(skb);
	skb_record_rx_queue(skb, tfile->queue_index);

	अगर (skb_xdp) अणु
		काष्ठा bpf_prog *xdp_prog;
		पूर्णांक ret;

		local_bh_disable();
		rcu_पढ़ो_lock();
		xdp_prog = rcu_dereference(tun->xdp_prog);
		अगर (xdp_prog) अणु
			ret = करो_xdp_generic(xdp_prog, skb);
			अगर (ret != XDP_PASS) अणु
				rcu_पढ़ो_unlock();
				local_bh_enable();
				अगर (frags) अणु
					tfile->napi.skb = शून्य;
					mutex_unlock(&tfile->napi_mutex);
				पूर्ण
				वापस total_len;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		local_bh_enable();
	पूर्ण

	/* Compute the costly rx hash only अगर needed क्रम flow updates.
	 * We may get a very small possibility of OOO during चयनing, not
	 * worth to optimize.
	 */
	अगर (!rcu_access_poपूर्णांकer(tun->steering_prog) && tun->numqueues > 1 &&
	    !tfile->detached)
		rxhash = __skb_get_hash_symmetric(skb);

	rcu_पढ़ो_lock();
	अगर (unlikely(!(tun->dev->flags & IFF_UP))) अणु
		err = -EIO;
		rcu_पढ़ो_unlock();
		जाओ drop;
	पूर्ण

	अगर (frags) अणु
		u32 headlen;

		/* Exercise flow dissector code path. */
		skb_push(skb, ETH_HLEN);
		headlen = eth_get_headlen(tun->dev, skb->data,
					  skb_headlen(skb));

		अगर (unlikely(headlen > skb_headlen(skb))) अणु
			atomic_दीर्घ_inc(&tun->dev->rx_dropped);
			napi_मुक्त_frags(&tfile->napi);
			rcu_पढ़ो_unlock();
			mutex_unlock(&tfile->napi_mutex);
			WARN_ON(1);
			वापस -ENOMEM;
		पूर्ण

		local_bh_disable();
		napi_gro_frags(&tfile->napi);
		local_bh_enable();
		mutex_unlock(&tfile->napi_mutex);
	पूर्ण अन्यथा अगर (tfile->napi_enabled) अणु
		काष्ठा sk_buff_head *queue = &tfile->sk.sk_ग_लिखो_queue;
		पूर्णांक queue_len;

		spin_lock_bh(&queue->lock);
		__skb_queue_tail(queue, skb);
		queue_len = skb_queue_len(queue);
		spin_unlock(&queue->lock);

		अगर (!more || queue_len > NAPI_POLL_WEIGHT)
			napi_schedule(&tfile->napi);

		local_bh_enable();
	पूर्ण अन्यथा अगर (!IS_ENABLED(CONFIG_4KSTACKS)) अणु
		tun_rx_batched(tun, tfile, skb, more);
	पूर्ण अन्यथा अणु
		netअगर_rx_ni(skb);
	पूर्ण
	rcu_पढ़ो_unlock();

	preempt_disable();
	dev_sw_netstats_rx_add(tun->dev, len);
	preempt_enable();

	अगर (rxhash)
		tun_flow_update(tun, rxhash, tfile);

	वापस total_len;
पूर्ण

अटल sमाप_प्रकार tun_chr_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा tun_काष्ठा *tun = tun_get(tfile);
	sमाप_प्रकार result;
	पूर्णांक noblock = 0;

	अगर (!tun)
		वापस -EBADFD;

	अगर ((file->f_flags & O_NONBLOCK) || (iocb->ki_flags & IOCB_NOWAIT))
		noblock = 1;

	result = tun_get_user(tun, tfile, शून्य, from, noblock, false);

	tun_put(tun);
	वापस result;
पूर्ण

अटल sमाप_प्रकार tun_put_user_xdp(काष्ठा tun_काष्ठा *tun,
				काष्ठा tun_file *tfile,
				काष्ठा xdp_frame *xdp_frame,
				काष्ठा iov_iter *iter)
अणु
	पूर्णांक vnet_hdr_sz = 0;
	माप_प्रकार size = xdp_frame->len;
	माप_प्रकार ret;

	अगर (tun->flags & IFF_VNET_HDR) अणु
		काष्ठा virtio_net_hdr gso = अणु 0 पूर्ण;

		vnet_hdr_sz = READ_ONCE(tun->vnet_hdr_sz);
		अगर (unlikely(iov_iter_count(iter) < vnet_hdr_sz))
			वापस -EINVAL;
		अगर (unlikely(copy_to_iter(&gso, माप(gso), iter) !=
			     माप(gso)))
			वापस -EFAULT;
		iov_iter_advance(iter, vnet_hdr_sz - माप(gso));
	पूर्ण

	ret = copy_to_iter(xdp_frame->data, size, iter) + vnet_hdr_sz;

	preempt_disable();
	dev_sw_netstats_tx_add(tun->dev, 1, ret);
	preempt_enable();

	वापस ret;
पूर्ण

/* Put packet to the user space buffer */
अटल sमाप_प्रकार tun_put_user(काष्ठा tun_काष्ठा *tun,
			    काष्ठा tun_file *tfile,
			    काष्ठा sk_buff *skb,
			    काष्ठा iov_iter *iter)
अणु
	काष्ठा tun_pi pi = अणु 0, skb->protocol पूर्ण;
	sमाप_प्रकार total;
	पूर्णांक vlan_offset = 0;
	पूर्णांक vlan_hlen = 0;
	पूर्णांक vnet_hdr_sz = 0;

	अगर (skb_vlan_tag_present(skb))
		vlan_hlen = VLAN_HLEN;

	अगर (tun->flags & IFF_VNET_HDR)
		vnet_hdr_sz = READ_ONCE(tun->vnet_hdr_sz);

	total = skb->len + vlan_hlen + vnet_hdr_sz;

	अगर (!(tun->flags & IFF_NO_PI)) अणु
		अगर (iov_iter_count(iter) < माप(pi))
			वापस -EINVAL;

		total += माप(pi);
		अगर (iov_iter_count(iter) < total) अणु
			/* Packet will be striped */
			pi.flags |= TUN_PKT_STRIP;
		पूर्ण

		अगर (copy_to_iter(&pi, माप(pi), iter) != माप(pi))
			वापस -EFAULT;
	पूर्ण

	अगर (vnet_hdr_sz) अणु
		काष्ठा virtio_net_hdr gso;

		अगर (iov_iter_count(iter) < vnet_hdr_sz)
			वापस -EINVAL;

		अगर (virtio_net_hdr_from_skb(skb, &gso,
					    tun_is_little_endian(tun), true,
					    vlan_hlen)) अणु
			काष्ठा skb_shared_info *sinfo = skb_shinfo(skb);
			pr_err("unexpected GSO type: "
			       "0x%x, gso_size %d, hdr_len %d\n",
			       sinfo->gso_type, tun16_to_cpu(tun, gso.gso_size),
			       tun16_to_cpu(tun, gso.hdr_len));
			prपूर्णांक_hex_dump(KERN_ERR, "tun: ",
				       DUMP_PREFIX_NONE,
				       16, 1, skb->head,
				       min((पूर्णांक)tun16_to_cpu(tun, gso.hdr_len), 64), true);
			WARN_ON_ONCE(1);
			वापस -EINVAL;
		पूर्ण

		अगर (copy_to_iter(&gso, माप(gso), iter) != माप(gso))
			वापस -EFAULT;

		iov_iter_advance(iter, vnet_hdr_sz - माप(gso));
	पूर्ण

	अगर (vlan_hlen) अणु
		पूर्णांक ret;
		काष्ठा veth veth;

		veth.h_vlan_proto = skb->vlan_proto;
		veth.h_vlan_TCI = htons(skb_vlan_tag_get(skb));

		vlan_offset = दुरत्व(काष्ठा vlan_ethhdr, h_vlan_proto);

		ret = skb_copy_datagram_iter(skb, 0, iter, vlan_offset);
		अगर (ret || !iov_iter_count(iter))
			जाओ करोne;

		ret = copy_to_iter(&veth, माप(veth), iter);
		अगर (ret != माप(veth) || !iov_iter_count(iter))
			जाओ करोne;
	पूर्ण

	skb_copy_datagram_iter(skb, vlan_offset, iter, skb->len - vlan_offset);

करोne:
	/* caller is in process context, */
	preempt_disable();
	dev_sw_netstats_tx_add(tun->dev, 1, skb->len + vlan_hlen);
	preempt_enable();

	वापस total;
पूर्ण

अटल व्योम *tun_ring_recv(काष्ठा tun_file *tfile, पूर्णांक noblock, पूर्णांक *err)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	व्योम *ptr = शून्य;
	पूर्णांक error = 0;

	ptr = ptr_ring_consume(&tfile->tx_ring);
	अगर (ptr)
		जाओ out;
	अगर (noblock) अणु
		error = -EAGAIN;
		जाओ out;
	पूर्ण

	add_रुको_queue(&tfile->socket.wq.रुको, &रुको);

	जबतक (1) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		ptr = ptr_ring_consume(&tfile->tx_ring);
		अगर (ptr)
			अवरोध;
		अगर (संकेत_pending(current)) अणु
			error = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (tfile->socket.sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
			error = -EFAULT;
			अवरोध;
		पूर्ण

		schedule();
	पूर्ण

	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&tfile->socket.wq.रुको, &रुको);

out:
	*err = error;
	वापस ptr;
पूर्ण

अटल sमाप_प्रकार tun_करो_पढ़ो(काष्ठा tun_काष्ठा *tun, काष्ठा tun_file *tfile,
			   काष्ठा iov_iter *to,
			   पूर्णांक noblock, व्योम *ptr)
अणु
	sमाप_प्रकार ret;
	पूर्णांक err;

	अगर (!iov_iter_count(to)) अणु
		tun_ptr_मुक्त(ptr);
		वापस 0;
	पूर्ण

	अगर (!ptr) अणु
		/* Read frames from ring */
		ptr = tun_ring_recv(tfile, noblock, &err);
		अगर (!ptr)
			वापस err;
	पूर्ण

	अगर (tun_is_xdp_frame(ptr)) अणु
		काष्ठा xdp_frame *xdpf = tun_ptr_to_xdp(ptr);

		ret = tun_put_user_xdp(tun, tfile, xdpf, to);
		xdp_वापस_frame(xdpf);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *skb = ptr;

		ret = tun_put_user(tun, tfile, skb, to);
		अगर (unlikely(ret < 0))
			kमुक्त_skb(skb);
		अन्यथा
			consume_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार tun_chr_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा tun_काष्ठा *tun = tun_get(tfile);
	sमाप_प्रकार len = iov_iter_count(to), ret;
	पूर्णांक noblock = 0;

	अगर (!tun)
		वापस -EBADFD;

	अगर ((file->f_flags & O_NONBLOCK) || (iocb->ki_flags & IOCB_NOWAIT))
		noblock = 1;

	ret = tun_करो_पढ़ो(tun, tfile, to, noblock, शून्य);
	ret = min_t(sमाप_प्रकार, ret, len);
	अगर (ret > 0)
		iocb->ki_pos = ret;
	tun_put(tun);
	वापस ret;
पूर्ण

अटल व्योम tun_prog_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा tun_prog *prog = container_of(rcu, काष्ठा tun_prog, rcu);

	bpf_prog_destroy(prog->prog);
	kमुक्त(prog);
पूर्ण

अटल पूर्णांक __tun_set_ebpf(काष्ठा tun_काष्ठा *tun,
			  काष्ठा tun_prog __rcu **prog_p,
			  काष्ठा bpf_prog *prog)
अणु
	काष्ठा tun_prog *old, *new = शून्य;

	अगर (prog) अणु
		new = kदो_स्मृति(माप(*new), GFP_KERNEL);
		अगर (!new)
			वापस -ENOMEM;
		new->prog = prog;
	पूर्ण

	spin_lock_bh(&tun->lock);
	old = rcu_dereference_रक्षित(*prog_p,
					lockdep_is_held(&tun->lock));
	rcu_assign_poपूर्णांकer(*prog_p, new);
	spin_unlock_bh(&tun->lock);

	अगर (old)
		call_rcu(&old->rcu, tun_prog_मुक्त);

	वापस 0;
पूर्ण

अटल व्योम tun_मुक्त_netdev(काष्ठा net_device *dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	BUG_ON(!(list_empty(&tun->disabled)));

	मुक्त_percpu(dev->tstats);
	/* We clear tstats so that tun_set_अगरf() can tell अगर
	 * tun_मुक्त_netdev() has been called from रेजिस्टर_netdevice().
	 */
	dev->tstats = शून्य;

	tun_flow_uninit(tun);
	security_tun_dev_मुक्त_security(tun->security);
	__tun_set_ebpf(tun, &tun->steering_prog, शून्य);
	__tun_set_ebpf(tun, &tun->filter_prog, शून्य);
पूर्ण

अटल व्योम tun_setup(काष्ठा net_device *dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	tun->owner = INVALID_UID;
	tun->group = INVALID_GID;
	tun_शेष_link_ksettings(dev, &tun->link_ksettings);

	dev->ethtool_ops = &tun_ethtool_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = tun_मुक्त_netdev;
	/* We prefer our own queue length */
	dev->tx_queue_len = TUN_READQ_SIZE;
पूर्ण

/* Trivial set of netlink ops to allow deleting tun or tap
 * device with netlink.
 */
अटल पूर्णांक tun_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG(extack,
		       "tun/tap creation via rtnetlink is not supported.");
	वापस -EOPNOTSUPP;
पूर्ण

अटल माप_प्रकार tun_get_size(स्थिर काष्ठा net_device *dev)
अणु
	BUILD_BUG_ON(माप(u32) != माप(uid_t));
	BUILD_BUG_ON(माप(u32) != माप(gid_t));

	वापस nla_total_size(माप(uid_t)) + /* OWNER */
	       nla_total_size(माप(gid_t)) + /* GROUP */
	       nla_total_size(माप(u8)) + /* TYPE */
	       nla_total_size(माप(u8)) + /* PI */
	       nla_total_size(माप(u8)) + /* VNET_HDR */
	       nla_total_size(माप(u8)) + /* PERSIST */
	       nla_total_size(माप(u8)) + /* MULTI_QUEUE */
	       nla_total_size(माप(u32)) + /* NUM_QUEUES */
	       nla_total_size(माप(u32)) + /* NUM_DISABLED_QUEUES */
	       0;
पूर्ण

अटल पूर्णांक tun_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	अगर (nla_put_u8(skb, IFLA_TUN_TYPE, tun->flags & TUN_TYPE_MASK))
		जाओ nla_put_failure;
	अगर (uid_valid(tun->owner) &&
	    nla_put_u32(skb, IFLA_TUN_OWNER,
			from_kuid_munged(current_user_ns(), tun->owner)))
		जाओ nla_put_failure;
	अगर (gid_valid(tun->group) &&
	    nla_put_u32(skb, IFLA_TUN_GROUP,
			from_kgid_munged(current_user_ns(), tun->group)))
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, IFLA_TUN_PI, !(tun->flags & IFF_NO_PI)))
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, IFLA_TUN_VNET_HDR, !!(tun->flags & IFF_VNET_HDR)))
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, IFLA_TUN_PERSIST, !!(tun->flags & IFF_PERSIST)))
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, IFLA_TUN_MULTI_QUEUE,
		       !!(tun->flags & IFF_MULTI_QUEUE)))
		जाओ nla_put_failure;
	अगर (tun->flags & IFF_MULTI_QUEUE) अणु
		अगर (nla_put_u32(skb, IFLA_TUN_NUM_QUEUES, tun->numqueues))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, IFLA_TUN_NUM_DISABLED_QUEUES,
				tun->numdisabled))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा rtnl_link_ops tun_link_ops __पढ़ो_mostly = अणु
	.kind		= DRV_NAME,
	.priv_size	= माप(काष्ठा tun_काष्ठा),
	.setup		= tun_setup,
	.validate	= tun_validate,
	.get_size       = tun_get_size,
	.fill_info      = tun_fill_info,
पूर्ण;

अटल व्योम tun_sock_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा tun_file *tfile;
	रुको_queue_head_t *wqueue;

	अगर (!sock_ग_लिखोable(sk))
		वापस;

	अगर (!test_and_clear_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->flags))
		वापस;

	wqueue = sk_sleep(sk);
	अगर (wqueue && रुकोqueue_active(wqueue))
		wake_up_पूर्णांकerruptible_sync_poll(wqueue, EPOLLOUT |
						EPOLLWRNORM | EPOLLWRBAND);

	tfile = container_of(sk, काष्ठा tun_file, sk);
	समाप्त_fasync(&tfile->fasync, SIGIO, POLL_OUT);
पूर्ण

अटल व्योम tun_put_page(काष्ठा tun_page *tpage)
अणु
	अगर (tpage->page)
		__page_frag_cache_drain(tpage->page, tpage->count);
पूर्ण

अटल पूर्णांक tun_xdp_one(काष्ठा tun_काष्ठा *tun,
		       काष्ठा tun_file *tfile,
		       काष्ठा xdp_buff *xdp, पूर्णांक *flush,
		       काष्ठा tun_page *tpage)
अणु
	अचिन्हित पूर्णांक datasize = xdp->data_end - xdp->data;
	काष्ठा tun_xdp_hdr *hdr = xdp->data_hard_start;
	काष्ठा virtio_net_hdr *gso = &hdr->gso;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा sk_buff *skb = शून्य;
	u32 rxhash = 0, act;
	पूर्णांक buflen = hdr->buflen;
	पूर्णांक err = 0;
	bool skb_xdp = false;
	काष्ठा page *page;

	xdp_prog = rcu_dereference(tun->xdp_prog);
	अगर (xdp_prog) अणु
		अगर (gso->gso_type) अणु
			skb_xdp = true;
			जाओ build;
		पूर्ण

		xdp_init_buff(xdp, buflen, &tfile->xdp_rxq);
		xdp_set_data_meta_invalid(xdp);

		act = bpf_prog_run_xdp(xdp_prog, xdp);
		err = tun_xdp_act(tun, xdp_prog, xdp, act);
		अगर (err < 0) अणु
			put_page(virt_to_head_page(xdp->data));
			वापस err;
		पूर्ण

		चयन (err) अणु
		हाल XDP_REसूचीECT:
			*flush = true;
			fallthrough;
		हाल XDP_TX:
			वापस 0;
		हाल XDP_PASS:
			अवरोध;
		शेष:
			page = virt_to_head_page(xdp->data);
			अगर (tpage->page == page) अणु
				++tpage->count;
			पूर्ण अन्यथा अणु
				tun_put_page(tpage);
				tpage->page = page;
				tpage->count = 1;
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

build:
	skb = build_skb(xdp->data_hard_start, buflen);
	अगर (!skb) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	skb_put(skb, xdp->data_end - xdp->data);

	अगर (virtio_net_hdr_to_skb(skb, gso, tun_is_little_endian(tun))) अणु
		atomic_दीर्घ_inc(&tun->rx_frame_errors);
		kमुक्त_skb(skb);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	skb->protocol = eth_type_trans(skb, tun->dev);
	skb_reset_network_header(skb);
	skb_probe_transport_header(skb);
	skb_record_rx_queue(skb, tfile->queue_index);

	अगर (skb_xdp) अणु
		err = करो_xdp_generic(xdp_prog, skb);
		अगर (err != XDP_PASS)
			जाओ out;
	पूर्ण

	अगर (!rcu_dereference(tun->steering_prog) && tun->numqueues > 1 &&
	    !tfile->detached)
		rxhash = __skb_get_hash_symmetric(skb);

	netअगर_receive_skb(skb);

	/* No need to disable preemption here since this function is
	 * always called with bh disabled
	 */
	dev_sw_netstats_rx_add(tun->dev, datasize);

	अगर (rxhash)
		tun_flow_update(tun, rxhash, tfile);

out:
	वापस err;
पूर्ण

अटल पूर्णांक tun_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार total_len)
अणु
	पूर्णांक ret, i;
	काष्ठा tun_file *tfile = container_of(sock, काष्ठा tun_file, socket);
	काष्ठा tun_काष्ठा *tun = tun_get(tfile);
	काष्ठा tun_msg_ctl *ctl = m->msg_control;
	काष्ठा xdp_buff *xdp;

	अगर (!tun)
		वापस -EBADFD;

	अगर (ctl && (ctl->type == TUN_MSG_PTR)) अणु
		काष्ठा tun_page tpage;
		पूर्णांक n = ctl->num;
		पूर्णांक flush = 0;

		स_रखो(&tpage, 0, माप(tpage));

		local_bh_disable();
		rcu_पढ़ो_lock();

		क्रम (i = 0; i < n; i++) अणु
			xdp = &((काष्ठा xdp_buff *)ctl->ptr)[i];
			tun_xdp_one(tun, tfile, xdp, &flush, &tpage);
		पूर्ण

		अगर (flush)
			xdp_करो_flush();

		rcu_पढ़ो_unlock();
		local_bh_enable();

		tun_put_page(&tpage);

		ret = total_len;
		जाओ out;
	पूर्ण

	ret = tun_get_user(tun, tfile, ctl ? ctl->ptr : शून्य, &m->msg_iter,
			   m->msg_flags & MSG_DONTWAIT,
			   m->msg_flags & MSG_MORE);
out:
	tun_put(tun);
	वापस ret;
पूर्ण

अटल पूर्णांक tun_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार total_len,
		       पूर्णांक flags)
अणु
	काष्ठा tun_file *tfile = container_of(sock, काष्ठा tun_file, socket);
	काष्ठा tun_काष्ठा *tun = tun_get(tfile);
	व्योम *ptr = m->msg_control;
	पूर्णांक ret;

	अगर (!tun) अणु
		ret = -EBADFD;
		जाओ out_मुक्त;
	पूर्ण

	अगर (flags & ~(MSG_DONTWAIT|MSG_TRUNC|MSG_ERRQUEUE)) अणु
		ret = -EINVAL;
		जाओ out_put_tun;
	पूर्ण
	अगर (flags & MSG_ERRQUEUE) अणु
		ret = sock_recv_errqueue(sock->sk, m, total_len,
					 SOL_PACKET, TUN_TX_TIMESTAMP);
		जाओ out;
	पूर्ण
	ret = tun_करो_पढ़ो(tun, tfile, &m->msg_iter, flags & MSG_DONTWAIT, ptr);
	अगर (ret > (sमाप_प्रकार)total_len) अणु
		m->msg_flags |= MSG_TRUNC;
		ret = flags & MSG_TRUNC ? ret : total_len;
	पूर्ण
out:
	tun_put(tun);
	वापस ret;

out_put_tun:
	tun_put(tun);
out_मुक्त:
	tun_ptr_मुक्त(ptr);
	वापस ret;
पूर्ण

अटल पूर्णांक tun_ptr_peek_len(व्योम *ptr)
अणु
	अगर (likely(ptr)) अणु
		अगर (tun_is_xdp_frame(ptr)) अणु
			काष्ठा xdp_frame *xdpf = tun_ptr_to_xdp(ptr);

			वापस xdpf->len;
		पूर्ण
		वापस __skb_array_len_with_tag(ptr);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tun_peek_len(काष्ठा socket *sock)
अणु
	काष्ठा tun_file *tfile = container_of(sock, काष्ठा tun_file, socket);
	काष्ठा tun_काष्ठा *tun;
	पूर्णांक ret = 0;

	tun = tun_get(tfile);
	अगर (!tun)
		वापस 0;

	ret = PTR_RING_PEEK_CALL(&tfile->tx_ring, tun_ptr_peek_len);
	tun_put(tun);

	वापस ret;
पूर्ण

/* Ops काष्ठाure to mimic raw sockets with tun */
अटल स्थिर काष्ठा proto_ops tun_socket_ops = अणु
	.peek_len = tun_peek_len,
	.sendmsg = tun_sendmsg,
	.recvmsg = tun_recvmsg,
पूर्ण;

अटल काष्ठा proto tun_proto = अणु
	.name		= "tun",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा tun_file),
पूर्ण;

अटल पूर्णांक tun_flags(काष्ठा tun_काष्ठा *tun)
अणु
	वापस tun->flags & (TUN_FEATURES | IFF_PERSIST | IFF_TUN | IFF_TAP);
पूर्ण

अटल sमाप_प्रकार tun_show_flags(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(to_net_dev(dev));
	वापस प्र_लिखो(buf, "0x%x\n", tun_flags(tun));
पूर्ण

अटल sमाप_प्रकार tun_show_owner(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(to_net_dev(dev));
	वापस uid_valid(tun->owner)?
		प्र_लिखो(buf, "%u\n",
			from_kuid_munged(current_user_ns(), tun->owner)):
		प्र_लिखो(buf, "-1\n");
पूर्ण

अटल sमाप_प्रकार tun_show_group(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(to_net_dev(dev));
	वापस gid_valid(tun->group) ?
		प्र_लिखो(buf, "%u\n",
			from_kgid_munged(current_user_ns(), tun->group)):
		प्र_लिखो(buf, "-1\n");
पूर्ण

अटल DEVICE_ATTR(tun_flags, 0444, tun_show_flags, शून्य);
अटल DEVICE_ATTR(owner, 0444, tun_show_owner, शून्य);
अटल DEVICE_ATTR(group, 0444, tun_show_group, शून्य);

अटल काष्ठा attribute *tun_dev_attrs[] = अणु
	&dev_attr_tun_flags.attr,
	&dev_attr_owner.attr,
	&dev_attr_group.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tun_attr_group = अणु
	.attrs = tun_dev_attrs
पूर्ण;

अटल पूर्णांक tun_set_अगरf(काष्ठा net *net, काष्ठा file *file, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा tun_काष्ठा *tun;
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा net_device *dev;
	पूर्णांक err;

	अगर (tfile->detached)
		वापस -EINVAL;

	अगर ((अगरr->अगरr_flags & IFF_NAPI_FRAGS)) अणु
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (!(अगरr->अगरr_flags & IFF_NAPI) ||
		    (अगरr->अगरr_flags & TUN_TYPE_MASK) != IFF_TAP)
			वापस -EINVAL;
	पूर्ण

	dev = __dev_get_by_name(net, अगरr->अगरr_name);
	अगर (dev) अणु
		अगर (अगरr->अगरr_flags & IFF_TUN_EXCL)
			वापस -EBUSY;
		अगर ((अगरr->अगरr_flags & IFF_TUN) && dev->netdev_ops == &tun_netdev_ops)
			tun = netdev_priv(dev);
		अन्यथा अगर ((अगरr->अगरr_flags & IFF_TAP) && dev->netdev_ops == &tap_netdev_ops)
			tun = netdev_priv(dev);
		अन्यथा
			वापस -EINVAL;

		अगर (!!(अगरr->अगरr_flags & IFF_MULTI_QUEUE) !=
		    !!(tun->flags & IFF_MULTI_QUEUE))
			वापस -EINVAL;

		अगर (tun_not_capable(tun))
			वापस -EPERM;
		err = security_tun_dev_खोलो(tun->security);
		अगर (err < 0)
			वापस err;

		err = tun_attach(tun, file, अगरr->अगरr_flags & IFF_NOFILTER,
				 अगरr->अगरr_flags & IFF_NAPI,
				 अगरr->अगरr_flags & IFF_NAPI_FRAGS, true);
		अगर (err < 0)
			वापस err;

		अगर (tun->flags & IFF_MULTI_QUEUE &&
		    (tun->numqueues + tun->numdisabled > 1)) अणु
			/* One or more queue has alपढ़ोy been attached, no need
			 * to initialize the device again.
			 */
			netdev_state_change(dev);
			वापस 0;
		पूर्ण

		tun->flags = (tun->flags & ~TUN_FEATURES) |
			      (अगरr->अगरr_flags & TUN_FEATURES);

		netdev_state_change(dev);
	पूर्ण अन्यथा अणु
		अक्षर *name;
		अचिन्हित दीर्घ flags = 0;
		पूर्णांक queues = अगरr->अगरr_flags & IFF_MULTI_QUEUE ?
			     MAX_TAP_QUEUES : 1;

		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
		err = security_tun_dev_create();
		अगर (err < 0)
			वापस err;

		/* Set dev type */
		अगर (अगरr->अगरr_flags & IFF_TUN) अणु
			/* TUN device */
			flags |= IFF_TUN;
			name = "tun%d";
		पूर्ण अन्यथा अगर (अगरr->अगरr_flags & IFF_TAP) अणु
			/* TAP device */
			flags |= IFF_TAP;
			name = "tap%d";
		पूर्ण अन्यथा
			वापस -EINVAL;

		अगर (*अगरr->अगरr_name)
			name = अगरr->अगरr_name;

		dev = alloc_netdev_mqs(माप(काष्ठा tun_काष्ठा), name,
				       NET_NAME_UNKNOWN, tun_setup, queues,
				       queues);

		अगर (!dev)
			वापस -ENOMEM;

		dev_net_set(dev, net);
		dev->rtnl_link_ops = &tun_link_ops;
		dev->अगरindex = tfile->अगरindex;
		dev->sysfs_groups[0] = &tun_attr_group;

		tun = netdev_priv(dev);
		tun->dev = dev;
		tun->flags = flags;
		tun->txflt.count = 0;
		tun->vnet_hdr_sz = माप(काष्ठा virtio_net_hdr);

		tun->align = NET_SKB_PAD;
		tun->filter_attached = false;
		tun->sndbuf = tfile->socket.sk->sk_sndbuf;
		tun->rx_batched = 0;
		RCU_INIT_POINTER(tun->steering_prog, शून्य);

		dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
		अगर (!dev->tstats) अणु
			err = -ENOMEM;
			जाओ err_मुक्त_dev;
		पूर्ण

		spin_lock_init(&tun->lock);

		err = security_tun_dev_alloc_security(&tun->security);
		अगर (err < 0)
			जाओ err_मुक्त_stat;

		tun_net_init(dev);
		tun_flow_init(tun);

		dev->hw_features = NETIF_F_SG | NETIF_F_FRAGLIST |
				   TUN_USER_FEATURES | NETIF_F_HW_VLAN_CTAG_TX |
				   NETIF_F_HW_VLAN_STAG_TX;
		dev->features = dev->hw_features | NETIF_F_LLTX;
		dev->vlan_features = dev->features &
				     ~(NETIF_F_HW_VLAN_CTAG_TX |
				       NETIF_F_HW_VLAN_STAG_TX);

		tun->flags = (tun->flags & ~TUN_FEATURES) |
			      (अगरr->अगरr_flags & TUN_FEATURES);

		INIT_LIST_HEAD(&tun->disabled);
		err = tun_attach(tun, file, false, अगरr->अगरr_flags & IFF_NAPI,
				 अगरr->अगरr_flags & IFF_NAPI_FRAGS, false);
		अगर (err < 0)
			जाओ err_मुक्त_flow;

		err = रेजिस्टर_netdevice(tun->dev);
		अगर (err < 0)
			जाओ err_detach;
		/* मुक्त_netdev() won't check refcnt, to aव्योम race
		 * with dev_put() we need publish tun after registration.
		 */
		rcu_assign_poपूर्णांकer(tfile->tun, tun);
	पूर्ण

	netअगर_carrier_on(tun->dev);

	/* Make sure persistent devices करो not get stuck in
	 * xoff state.
	 */
	अगर (netअगर_running(tun->dev))
		netअगर_tx_wake_all_queues(tun->dev);

	म_नकल(अगरr->अगरr_name, tun->dev->name);
	वापस 0;

err_detach:
	tun_detach_all(dev);
	/* We are here because रेजिस्टर_netdevice() has failed.
	 * If रेजिस्टर_netdevice() alपढ़ोy called tun_मुक्त_netdev()
	 * जबतक dealing with the error, dev->stats has been cleared.
	 */
	अगर (!dev->tstats)
		जाओ err_मुक्त_dev;

err_मुक्त_flow:
	tun_flow_uninit(tun);
	security_tun_dev_मुक्त_security(tun->security);
err_मुक्त_stat:
	मुक्त_percpu(dev->tstats);
err_मुक्त_dev:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल व्योम tun_get_अगरf(काष्ठा tun_काष्ठा *tun, काष्ठा अगरreq *अगरr)
अणु
	म_नकल(अगरr->अगरr_name, tun->dev->name);

	अगरr->अगरr_flags = tun_flags(tun);

पूर्ण

/* This is like a cut-करोwn ethtool ops, except करोne via tun fd so no
 * privs required. */
अटल पूर्णांक set_offload(काष्ठा tun_काष्ठा *tun, अचिन्हित दीर्घ arg)
अणु
	netdev_features_t features = 0;

	अगर (arg & TUN_F_CSUM) अणु
		features |= NETIF_F_HW_CSUM;
		arg &= ~TUN_F_CSUM;

		अगर (arg & (TUN_F_TSO4|TUN_F_TSO6)) अणु
			अगर (arg & TUN_F_TSO_ECN) अणु
				features |= NETIF_F_TSO_ECN;
				arg &= ~TUN_F_TSO_ECN;
			पूर्ण
			अगर (arg & TUN_F_TSO4)
				features |= NETIF_F_TSO;
			अगर (arg & TUN_F_TSO6)
				features |= NETIF_F_TSO6;
			arg &= ~(TUN_F_TSO4|TUN_F_TSO6);
		पूर्ण

		arg &= ~TUN_F_UFO;
	पूर्ण

	/* This gives the user a way to test क्रम new features in future by
	 * trying to set them. */
	अगर (arg)
		वापस -EINVAL;

	tun->set_features = features;
	tun->dev->wanted_features &= ~TUN_USER_FEATURES;
	tun->dev->wanted_features |= features;
	netdev_update_features(tun->dev);

	वापस 0;
पूर्ण

अटल व्योम tun_detach_filter(काष्ठा tun_काष्ठा *tun, पूर्णांक n)
अणु
	पूर्णांक i;
	काष्ठा tun_file *tfile;

	क्रम (i = 0; i < n; i++) अणु
		tfile = rtnl_dereference(tun->tfiles[i]);
		lock_sock(tfile->socket.sk);
		sk_detach_filter(tfile->socket.sk);
		release_sock(tfile->socket.sk);
	पूर्ण

	tun->filter_attached = false;
पूर्ण

अटल पूर्णांक tun_attach_filter(काष्ठा tun_काष्ठा *tun)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा tun_file *tfile;

	क्रम (i = 0; i < tun->numqueues; i++) अणु
		tfile = rtnl_dereference(tun->tfiles[i]);
		lock_sock(tfile->socket.sk);
		ret = sk_attach_filter(&tun->fprog, tfile->socket.sk);
		release_sock(tfile->socket.sk);
		अगर (ret) अणु
			tun_detach_filter(tun, i);
			वापस ret;
		पूर्ण
	पूर्ण

	tun->filter_attached = true;
	वापस ret;
पूर्ण

अटल व्योम tun_set_sndbuf(काष्ठा tun_काष्ठा *tun)
अणु
	काष्ठा tun_file *tfile;
	पूर्णांक i;

	क्रम (i = 0; i < tun->numqueues; i++) अणु
		tfile = rtnl_dereference(tun->tfiles[i]);
		tfile->socket.sk->sk_sndbuf = tun->sndbuf;
	पूर्ण
पूर्ण

अटल पूर्णांक tun_set_queue(काष्ठा file *file, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा tun_काष्ठा *tun;
	पूर्णांक ret = 0;

	rtnl_lock();

	अगर (अगरr->अगरr_flags & IFF_ATTACH_QUEUE) अणु
		tun = tfile->detached;
		अगर (!tun) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
		ret = security_tun_dev_attach_queue(tun->security);
		अगर (ret < 0)
			जाओ unlock;
		ret = tun_attach(tun, file, false, tun->flags & IFF_NAPI,
				 tun->flags & IFF_NAPI_FRAGS, true);
	पूर्ण अन्यथा अगर (अगरr->अगरr_flags & IFF_DETACH_QUEUE) अणु
		tun = rtnl_dereference(tfile->tun);
		अगर (!tun || !(tun->flags & IFF_MULTI_QUEUE) || tfile->detached)
			ret = -EINVAL;
		अन्यथा
			__tun_detach(tfile, false);
	पूर्ण अन्यथा
		ret = -EINVAL;

	अगर (ret >= 0)
		netdev_state_change(tun->dev);

unlock:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक tun_set_ebpf(काष्ठा tun_काष्ठा *tun, काष्ठा tun_prog __rcu **prog_p,
			व्योम __user *data)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक fd;

	अगर (copy_from_user(&fd, data, माप(fd)))
		वापस -EFAULT;

	अगर (fd == -1) अणु
		prog = शून्य;
	पूर्ण अन्यथा अणु
		prog = bpf_prog_get_type(fd, BPF_PROG_TYPE_SOCKET_FILTER);
		अगर (IS_ERR(prog))
			वापस PTR_ERR(prog);
	पूर्ण

	वापस __tun_set_ebpf(tun, prog_p, prog);
पूर्ण

/* Return correct value क्रम tun->dev->addr_len based on tun->dev->type. */
अटल अचिन्हित अक्षर tun_get_addr_len(अचिन्हित लघु type)
अणु
	चयन (type) अणु
	हाल ARPHRD_IP6GRE:
	हाल ARPHRD_TUNNEL6:
		वापस माप(काष्ठा in6_addr);
	हाल ARPHRD_IPGRE:
	हाल ARPHRD_TUNNEL:
	हाल ARPHRD_SIT:
		वापस 4;
	हाल ARPHRD_ETHER:
		वापस ETH_ALEN;
	हाल ARPHRD_IEEE802154:
	हाल ARPHRD_IEEE802154_MONITOR:
		वापस IEEE802154_EXTENDED_ADDR_LEN;
	हाल ARPHRD_PHONET_PIPE:
	हाल ARPHRD_PPP:
	हाल ARPHRD_NONE:
		वापस 0;
	हाल ARPHRD_6LOWPAN:
		वापस EUI64_ADDR_LEN;
	हाल ARPHRD_FDDI:
		वापस FDDI_K_ALEN;
	हाल ARPHRD_HIPPI:
		वापस HIPPI_ALEN;
	हाल ARPHRD_IEEE802:
		वापस FC_ALEN;
	हाल ARPHRD_ROSE:
		वापस ROSE_ADDR_LEN;
	हाल ARPHRD_NETROM:
		वापस AX25_ADDR_LEN;
	हाल ARPHRD_LOCALTLK:
		वापस LTALK_ALEN;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल दीर्घ __tun_chr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg, पूर्णांक अगरreq_len)
अणु
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा net *net = sock_net(&tfile->sk);
	काष्ठा tun_काष्ठा *tun;
	व्योम __user* argp = (व्योम __user*)arg;
	अचिन्हित पूर्णांक अगरindex, carrier;
	काष्ठा अगरreq अगरr;
	kuid_t owner;
	kgid_t group;
	पूर्णांक sndbuf;
	पूर्णांक vnet_hdr_sz;
	पूर्णांक le;
	पूर्णांक ret;
	bool करो_notअगरy = false;

	अगर (cmd == TUNSETIFF || cmd == TUNSETQUEUE ||
	    (_IOC_TYPE(cmd) == SOCK_IOC_TYPE && cmd != SIOCGSKNS)) अणु
		अगर (copy_from_user(&अगरr, argp, अगरreq_len))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		स_रखो(&अगरr, 0, माप(अगरr));
	पूर्ण
	अगर (cmd == TUNGETFEATURES) अणु
		/* Currently this just means: "what IFF flags are valid?".
		 * This is needed because we never checked क्रम invalid flags on
		 * TUNSETIFF.
		 */
		वापस put_user(IFF_TUN | IFF_TAP | TUN_FEATURES,
				(अचिन्हित पूर्णांक __user*)argp);
	पूर्ण अन्यथा अगर (cmd == TUNSETQUEUE) अणु
		वापस tun_set_queue(file, &अगरr);
	पूर्ण अन्यथा अगर (cmd == SIOCGSKNS) अणु
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EPERM;
		वापस खोलो_related_ns(&net->ns, get_net_ns);
	पूर्ण

	rtnl_lock();

	tun = tun_get(tfile);
	अगर (cmd == TUNSETIFF) अणु
		ret = -EEXIST;
		अगर (tun)
			जाओ unlock;

		अगरr.अगरr_name[IFNAMSIZ-1] = '\0';

		ret = tun_set_अगरf(net, file, &अगरr);

		अगर (ret)
			जाओ unlock;

		अगर (copy_to_user(argp, &अगरr, अगरreq_len))
			ret = -EFAULT;
		जाओ unlock;
	पूर्ण
	अगर (cmd == TUNSETIFINDEX) अणु
		ret = -EPERM;
		अगर (tun)
			जाओ unlock;

		ret = -EFAULT;
		अगर (copy_from_user(&अगरindex, argp, माप(अगरindex)))
			जाओ unlock;

		ret = 0;
		tfile->अगरindex = अगरindex;
		जाओ unlock;
	पूर्ण

	ret = -EBADFD;
	अगर (!tun)
		जाओ unlock;

	netअगर_info(tun, drv, tun->dev, "tun_chr_ioctl cmd %u\n", cmd);

	net = dev_net(tun->dev);
	ret = 0;
	चयन (cmd) अणु
	हाल TUNGETIFF:
		tun_get_अगरf(tun, &अगरr);

		अगर (tfile->detached)
			अगरr.अगरr_flags |= IFF_DETACH_QUEUE;
		अगर (!tfile->socket.sk->sk_filter)
			अगरr.अगरr_flags |= IFF_NOFILTER;

		अगर (copy_to_user(argp, &अगरr, अगरreq_len))
			ret = -EFAULT;
		अवरोध;

	हाल TUNSETNOCSUM:
		/* Disable/Enable checksum */

		/* [unimplemented] */
		netअगर_info(tun, drv, tun->dev, "ignored: set checksum %s\n",
			   arg ? "disabled" : "enabled");
		अवरोध;

	हाल TUNSETPERSIST:
		/* Disable/Enable persist mode. Keep an extra reference to the
		 * module to prevent the module being unprobed.
		 */
		अगर (arg && !(tun->flags & IFF_PERSIST)) अणु
			tun->flags |= IFF_PERSIST;
			__module_get(THIS_MODULE);
			करो_notअगरy = true;
		पूर्ण
		अगर (!arg && (tun->flags & IFF_PERSIST)) अणु
			tun->flags &= ~IFF_PERSIST;
			module_put(THIS_MODULE);
			करो_notअगरy = true;
		पूर्ण

		netअगर_info(tun, drv, tun->dev, "persist %s\n",
			   arg ? "enabled" : "disabled");
		अवरोध;

	हाल TUNSETOWNER:
		/* Set owner of the device */
		owner = make_kuid(current_user_ns(), arg);
		अगर (!uid_valid(owner)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		tun->owner = owner;
		करो_notअगरy = true;
		netअगर_info(tun, drv, tun->dev, "owner set to %u\n",
			   from_kuid(&init_user_ns, tun->owner));
		अवरोध;

	हाल TUNSETGROUP:
		/* Set group of the device */
		group = make_kgid(current_user_ns(), arg);
		अगर (!gid_valid(group)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		tun->group = group;
		करो_notअगरy = true;
		netअगर_info(tun, drv, tun->dev, "group set to %u\n",
			   from_kgid(&init_user_ns, tun->group));
		अवरोध;

	हाल TUNSETLINK:
		/* Only allow setting the type when the पूर्णांकerface is करोwn */
		अगर (tun->dev->flags & IFF_UP) अणु
			netअगर_info(tun, drv, tun->dev,
				   "Linktype set failed because interface is up\n");
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			ret = call_netdevice_notअगरiers(NETDEV_PRE_TYPE_CHANGE,
						       tun->dev);
			ret = notअगरier_to_त्रुटि_सं(ret);
			अगर (ret) अणु
				netअगर_info(tun, drv, tun->dev,
					   "Refused to change device type\n");
				अवरोध;
			पूर्ण
			tun->dev->type = (पूर्णांक) arg;
			tun->dev->addr_len = tun_get_addr_len(tun->dev->type);
			netअगर_info(tun, drv, tun->dev, "linktype set to %d\n",
				   tun->dev->type);
			call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE,
						 tun->dev);
		पूर्ण
		अवरोध;

	हाल TUNSETDEBUG:
		tun->msg_enable = (u32)arg;
		अवरोध;

	हाल TUNSETOFFLOAD:
		ret = set_offload(tun, arg);
		अवरोध;

	हाल TUNSETTXFILTER:
		/* Can be set only क्रम TAPs */
		ret = -EINVAL;
		अगर ((tun->flags & TUN_TYPE_MASK) != IFF_TAP)
			अवरोध;
		ret = update_filter(&tun->txflt, (व्योम __user *)arg);
		अवरोध;

	हाल SIOCGIFHWADDR:
		/* Get hw address */
		dev_get_mac_address(&अगरr.अगरr_hwaddr, net, tun->dev->name);
		अगर (copy_to_user(argp, &अगरr, अगरreq_len))
			ret = -EFAULT;
		अवरोध;

	हाल SIOCSIFHWADDR:
		/* Set hw address */
		ret = dev_set_mac_address_user(tun->dev, &अगरr.अगरr_hwaddr, शून्य);
		अवरोध;

	हाल TUNGETSNDBUF:
		sndbuf = tfile->socket.sk->sk_sndbuf;
		अगर (copy_to_user(argp, &sndbuf, माप(sndbuf)))
			ret = -EFAULT;
		अवरोध;

	हाल TUNSETSNDBUF:
		अगर (copy_from_user(&sndbuf, argp, माप(sndbuf))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (sndbuf <= 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		tun->sndbuf = sndbuf;
		tun_set_sndbuf(tun);
		अवरोध;

	हाल TUNGETVNETHDRSZ:
		vnet_hdr_sz = tun->vnet_hdr_sz;
		अगर (copy_to_user(argp, &vnet_hdr_sz, माप(vnet_hdr_sz)))
			ret = -EFAULT;
		अवरोध;

	हाल TUNSETVNETHDRSZ:
		अगर (copy_from_user(&vnet_hdr_sz, argp, माप(vnet_hdr_sz))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (vnet_hdr_sz < (पूर्णांक)माप(काष्ठा virtio_net_hdr)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		tun->vnet_hdr_sz = vnet_hdr_sz;
		अवरोध;

	हाल TUNGETVNETLE:
		le = !!(tun->flags & TUN_VNET_LE);
		अगर (put_user(le, (पूर्णांक __user *)argp))
			ret = -EFAULT;
		अवरोध;

	हाल TUNSETVNETLE:
		अगर (get_user(le, (पूर्णांक __user *)argp)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (le)
			tun->flags |= TUN_VNET_LE;
		अन्यथा
			tun->flags &= ~TUN_VNET_LE;
		अवरोध;

	हाल TUNGETVNETBE:
		ret = tun_get_vnet_be(tun, argp);
		अवरोध;

	हाल TUNSETVNETBE:
		ret = tun_set_vnet_be(tun, argp);
		अवरोध;

	हाल TUNATTACHFILTER:
		/* Can be set only क्रम TAPs */
		ret = -EINVAL;
		अगर ((tun->flags & TUN_TYPE_MASK) != IFF_TAP)
			अवरोध;
		ret = -EFAULT;
		अगर (copy_from_user(&tun->fprog, argp, माप(tun->fprog)))
			अवरोध;

		ret = tun_attach_filter(tun);
		अवरोध;

	हाल TUNDETACHFILTER:
		/* Can be set only क्रम TAPs */
		ret = -EINVAL;
		अगर ((tun->flags & TUN_TYPE_MASK) != IFF_TAP)
			अवरोध;
		ret = 0;
		tun_detach_filter(tun, tun->numqueues);
		अवरोध;

	हाल TUNGETFILTER:
		ret = -EINVAL;
		अगर ((tun->flags & TUN_TYPE_MASK) != IFF_TAP)
			अवरोध;
		ret = -EFAULT;
		अगर (copy_to_user(argp, &tun->fprog, माप(tun->fprog)))
			अवरोध;
		ret = 0;
		अवरोध;

	हाल TUNSETSTEERINGEBPF:
		ret = tun_set_ebpf(tun, &tun->steering_prog, argp);
		अवरोध;

	हाल TUNSETFILTEREBPF:
		ret = tun_set_ebpf(tun, &tun->filter_prog, argp);
		अवरोध;

	हाल TUNSETCARRIER:
		ret = -EFAULT;
		अगर (copy_from_user(&carrier, argp, माप(carrier)))
			जाओ unlock;

		ret = tun_net_change_carrier(tun->dev, (bool)carrier);
		अवरोध;

	हाल TUNGETDEVNETNS:
		ret = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			जाओ unlock;
		ret = खोलो_related_ns(&net->ns, get_net_ns);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (करो_notअगरy)
		netdev_state_change(tun->dev);

unlock:
	rtnl_unlock();
	अगर (tun)
		tun_put(tun);
	वापस ret;
पूर्ण

अटल दीर्घ tun_chr_ioctl(काष्ठा file *file,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस __tun_chr_ioctl(file, cmd, arg, माप (काष्ठा अगरreq));
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ tun_chr_compat_ioctl(काष्ठा file *file,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल TUNSETIFF:
	हाल TUNGETIFF:
	हाल TUNSETTXFILTER:
	हाल TUNGETSNDBUF:
	हाल TUNSETSNDBUF:
	हाल SIOCGIFHWADDR:
	हाल SIOCSIFHWADDR:
		arg = (अचिन्हित दीर्घ)compat_ptr(arg);
		अवरोध;
	शेष:
		arg = (compat_uदीर्घ_t)arg;
		अवरोध;
	पूर्ण

	/*
	 * compat_अगरreq is लघुer than अगरreq, so we must not access beyond
	 * the end of that काष्ठाure. All fields that are used in this
	 * driver are compatible though, we करोn't need to convert the
	 * contents.
	 */
	वापस __tun_chr_ioctl(file, cmd, arg, माप(काष्ठा compat_अगरreq));
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल पूर्णांक tun_chr_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा tun_file *tfile = file->निजी_data;
	पूर्णांक ret;

	अगर ((ret = fasync_helper(fd, file, on, &tfile->fasync)) < 0)
		जाओ out;

	अगर (on) अणु
		__f_setown(file, task_pid(current), PIDTYPE_TGID, 0);
		tfile->flags |= TUN_FASYNC;
	पूर्ण अन्यथा
		tfile->flags &= ~TUN_FASYNC;
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक tun_chr_खोलो(काष्ठा inode *inode, काष्ठा file * file)
अणु
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा tun_file *tfile;

	tfile = (काष्ठा tun_file *)sk_alloc(net, AF_UNSPEC, GFP_KERNEL,
					    &tun_proto, 0);
	अगर (!tfile)
		वापस -ENOMEM;
	अगर (ptr_ring_init(&tfile->tx_ring, 0, GFP_KERNEL)) अणु
		sk_मुक्त(&tfile->sk);
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&tfile->napi_mutex);
	RCU_INIT_POINTER(tfile->tun, शून्य);
	tfile->flags = 0;
	tfile->अगरindex = 0;

	init_रुकोqueue_head(&tfile->socket.wq.रुको);

	tfile->socket.file = file;
	tfile->socket.ops = &tun_socket_ops;

	sock_init_data(&tfile->socket, &tfile->sk);

	tfile->sk.sk_ग_लिखो_space = tun_sock_ग_लिखो_space;
	tfile->sk.sk_sndbuf = पूर्णांक_उच्च;

	file->निजी_data = tfile;
	INIT_LIST_HEAD(&tfile->next);

	sock_set_flag(&tfile->sk, SOCK_ZEROCOPY);

	वापस 0;
पूर्ण

अटल पूर्णांक tun_chr_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा tun_file *tfile = file->निजी_data;

	tun_detach(tfile, true);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम tun_chr_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *file)
अणु
	काष्ठा tun_file *tfile = file->निजी_data;
	काष्ठा tun_काष्ठा *tun;
	काष्ठा अगरreq अगरr;

	स_रखो(&अगरr, 0, माप(अगरr));

	rtnl_lock();
	tun = tun_get(tfile);
	अगर (tun)
		tun_get_अगरf(tun, &अगरr);
	rtnl_unlock();

	अगर (tun)
		tun_put(tun);

	seq_म_लिखो(m, "iff:\t%s\n", अगरr.अगरr_name);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations tun_fops = अणु
	.owner	= THIS_MODULE,
	.llseek = no_llseek,
	.पढ़ो_iter  = tun_chr_पढ़ो_iter,
	.ग_लिखो_iter = tun_chr_ग_लिखो_iter,
	.poll	= tun_chr_poll,
	.unlocked_ioctl	= tun_chr_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = tun_chr_compat_ioctl,
#पूर्ण_अगर
	.खोलो	= tun_chr_खोलो,
	.release = tun_chr_बंद,
	.fasync = tun_chr_fasync,
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo = tun_chr_show_fdinfo,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा miscdevice tun_miscdev = अणु
	.minor = TUN_MINOR,
	.name = "tun",
	.nodename = "net/tun",
	.fops = &tun_fops,
पूर्ण;

/* ethtool पूर्णांकerface */

अटल व्योम tun_शेष_link_ksettings(काष्ठा net_device *dev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	cmd->base.speed		= SPEED_10;
	cmd->base.duplex	= DUPLEX_FULL;
	cmd->base.port		= PORT_TP;
	cmd->base.phy_address	= 0;
	cmd->base.स्वतःneg	= AUTONEG_DISABLE;
पूर्ण

अटल पूर्णांक tun_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	स_नकल(cmd, &tun->link_ksettings, माप(*cmd));
	वापस 0;
पूर्ण

अटल पूर्णांक tun_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	स_नकल(&tun->link_ksettings, cmd, माप(*cmd));
	वापस 0;
पूर्ण

अटल व्योम tun_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));

	चयन (tun->flags & TUN_TYPE_MASK) अणु
	हाल IFF_TUN:
		strlcpy(info->bus_info, "tun", माप(info->bus_info));
		अवरोध;
	हाल IFF_TAP:
		strlcpy(info->bus_info, "tap", माप(info->bus_info));
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 tun_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	वापस tun->msg_enable;
पूर्ण

अटल व्योम tun_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	tun->msg_enable = value;
पूर्ण

अटल पूर्णांक tun_get_coalesce(काष्ठा net_device *dev,
			    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	ec->rx_max_coalesced_frames = tun->rx_batched;

	वापस 0;
पूर्ण

अटल पूर्णांक tun_set_coalesce(काष्ठा net_device *dev,
			    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);

	अगर (ec->rx_max_coalesced_frames > NAPI_POLL_WEIGHT)
		tun->rx_batched = NAPI_POLL_WEIGHT;
	अन्यथा
		tun->rx_batched = ec->rx_max_coalesced_frames;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops tun_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_MAX_FRAMES,
	.get_drvinfo	= tun_get_drvinfo,
	.get_msglevel	= tun_get_msglevel,
	.set_msglevel	= tun_set_msglevel,
	.get_link	= ethtool_op_get_link,
	.get_ts_info	= ethtool_op_get_ts_info,
	.get_coalesce   = tun_get_coalesce,
	.set_coalesce   = tun_set_coalesce,
	.get_link_ksettings = tun_get_link_ksettings,
	.set_link_ksettings = tun_set_link_ksettings,
पूर्ण;

अटल पूर्णांक tun_queue_resize(काष्ठा tun_काष्ठा *tun)
अणु
	काष्ठा net_device *dev = tun->dev;
	काष्ठा tun_file *tfile;
	काष्ठा ptr_ring **rings;
	पूर्णांक n = tun->numqueues + tun->numdisabled;
	पूर्णांक ret, i;

	rings = kदो_स्मृति_array(n, माप(*rings), GFP_KERNEL);
	अगर (!rings)
		वापस -ENOMEM;

	क्रम (i = 0; i < tun->numqueues; i++) अणु
		tfile = rtnl_dereference(tun->tfiles[i]);
		rings[i] = &tfile->tx_ring;
	पूर्ण
	list_क्रम_each_entry(tfile, &tun->disabled, next)
		rings[i++] = &tfile->tx_ring;

	ret = ptr_ring_resize_multiple(rings, n,
				       dev->tx_queue_len, GFP_KERNEL,
				       tun_ptr_मुक्त);

	kमुक्त(rings);
	वापस ret;
पूर्ण

अटल पूर्णांक tun_device_event(काष्ठा notअगरier_block *unused,
			    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा tun_काष्ठा *tun = netdev_priv(dev);
	पूर्णांक i;

	अगर (dev->rtnl_link_ops != &tun_link_ops)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_CHANGE_TX_QUEUE_LEN:
		अगर (tun_queue_resize(tun))
			वापस NOTIFY_BAD;
		अवरोध;
	हाल NETDEV_UP:
		क्रम (i = 0; i < tun->numqueues; i++) अणु
			काष्ठा tun_file *tfile;

			tfile = rtnl_dereference(tun->tfiles[i]);
			tfile->socket.sk->sk_ग_लिखो_space(tfile->socket.sk);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block tun_notअगरier_block __पढ़ो_mostly = अणु
	.notअगरier_call	= tun_device_event,
पूर्ण;

अटल पूर्णांक __init tun_init(व्योम)
अणु
	पूर्णांक ret = 0;

	pr_info("%s, %s\n", DRV_DESCRIPTION, DRV_VERSION);

	ret = rtnl_link_रेजिस्टर(&tun_link_ops);
	अगर (ret) अणु
		pr_err("Can't register link_ops\n");
		जाओ err_linkops;
	पूर्ण

	ret = misc_रेजिस्टर(&tun_miscdev);
	अगर (ret) अणु
		pr_err("Can't register misc device %d\n", TUN_MINOR);
		जाओ err_misc;
	पूर्ण

	ret = रेजिस्टर_netdevice_notअगरier(&tun_notअगरier_block);
	अगर (ret) अणु
		pr_err("Can't register netdevice notifier\n");
		जाओ err_notअगरier;
	पूर्ण

	वापस  0;

err_notअगरier:
	misc_deरेजिस्टर(&tun_miscdev);
err_misc:
	rtnl_link_unरेजिस्टर(&tun_link_ops);
err_linkops:
	वापस ret;
पूर्ण

अटल व्योम tun_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&tun_miscdev);
	rtnl_link_unरेजिस्टर(&tun_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&tun_notअगरier_block);
पूर्ण

/* Get an underlying socket object from tun file.  Returns error unless file is
 * attached to a device.  The वापसed object works like a packet socket, it
 * can be used क्रम sock_sendmsg/sock_recvmsg.  The caller is responsible क्रम
 * holding a reference to the file क्रम as दीर्घ as the socket is in use. */
काष्ठा socket *tun_get_socket(काष्ठा file *file)
अणु
	काष्ठा tun_file *tfile;
	अगर (file->f_op != &tun_fops)
		वापस ERR_PTR(-EINVAL);
	tfile = file->निजी_data;
	अगर (!tfile)
		वापस ERR_PTR(-EBADFD);
	वापस &tfile->socket;
पूर्ण
EXPORT_SYMBOL_GPL(tun_get_socket);

काष्ठा ptr_ring *tun_get_tx_ring(काष्ठा file *file)
अणु
	काष्ठा tun_file *tfile;

	अगर (file->f_op != &tun_fops)
		वापस ERR_PTR(-EINVAL);
	tfile = file->निजी_data;
	अगर (!tfile)
		वापस ERR_PTR(-EBADFD);
	वापस &tfile->tx_ring;
पूर्ण
EXPORT_SYMBOL_GPL(tun_get_tx_ring);

module_init(tun_init);
module_निकास(tun_cleanup);
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR(DRV_COPYRIGHT);
MODULE_LICENSE("GPL");
MODULE_ALIAS_MISCDEV(TUN_MINOR);
MODULE_ALIAS("devname:net/tun");
