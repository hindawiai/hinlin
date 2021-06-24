<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		PACKET - implements raw packet sockets.
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *
 * Fixes:
 *		Alan Cox	:	verअगरy_area() now used correctly
 *		Alan Cox	:	new skbuff lists, look ma no backlogs!
 *		Alan Cox	:	tidied skbuff lists.
 *		Alan Cox	:	Now uses generic datagram routines I
 *					added. Also fixed the peek/पढ़ो crash
 *					from all old Linux datagram code.
 *		Alan Cox	:	Uses the improved datagram code.
 *		Alan Cox	:	Added शून्य's क्रम socket options.
 *		Alan Cox	:	Re-commented the code.
 *		Alan Cox	:	Use new kernel side addressing
 *		Rob Janssen	:	Correct MTU usage.
 *		Dave Platt	:	Counter leaks caused by incorrect
 *					पूर्णांकerrupt locking and some slightly
 *					dubious gcc output. Can you पढ़ो
 *					compiler: it said _VOLATILE_
 *	Riअक्षरd Kooijman	:	Timestamp fixes.
 *		Alan Cox	:	New buffers. Use sk->mac.raw.
 *		Alan Cox	:	sendmsg/recvmsg support.
 *		Alan Cox	:	Protocol setting support
 *	Alexey Kuznetsov	:	Untied from IPv4 stack.
 *	Cyrus Durgin		:	Fixed kerneld क्रम kmod.
 *	Michal Ostrowski        :       Module initialization cleanup.
 *         Ulises Alonso        :       Frame number limit removal and
 *                                      packet_set_ring memory leak.
 *		Eric Biederman	:	Allow क्रम > 8 byte hardware addresses.
 *					The convention is that दीर्घer addresses
 *					will simply extend the hardware address
 *					byte arrays at the end of sockaddr_ll
 *					and packet_mreq.
 *		Johann Baudy	:	Added TX RING.
 *		Chetan Loke	:	Implemented TPACKET_V3 block असलtraction
 *					layer.
 *					Copyright (C) 2011, <lokec@ccs.neu.edu>
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/capability.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/wireless.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/net_namespace.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <linux/skbuff.h>
#समावेश <net/sock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/virtio_net.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/percpu.h>
#अगर_घोषित CONFIG_INET
#समावेश <net/inet_common.h>
#पूर्ण_अगर
#समावेश <linux/bpf.h>
#समावेश <net/compat.h>

#समावेश "internal.h"

/*
   Assumptions:
   - If the device has no dev->header_ops->create, there is no LL header
     visible above the device. In this हाल, its hard_header_len should be 0.
     The device may prepend its own header पूर्णांकernally. In this हाल, its
     needed_headroom should be set to the space needed क्रम it to add its
     पूर्णांकernal header.
     For example, a WiFi driver pretending to be an Ethernet driver should
     set its hard_header_len to be the Ethernet header length, and set its
     needed_headroom to be (the real WiFi header length - the fake Ethernet
     header length).
   - packet socket receives packets with pulled ll header,
     so that SOCK_RAW should push it back.

On receive:
-----------

Incoming, dev_has_header(dev) == true
   mac_header -> ll header
   data       -> data

Outgoing, dev_has_header(dev) == true
   mac_header -> ll header
   data       -> ll header

Incoming, dev_has_header(dev) == false
   mac_header -> data
     However drivers often make it poपूर्णांक to the ll header.
     This is incorrect because the ll header should be invisible to us.
   data       -> data

Outgoing, dev_has_header(dev) == false
   mac_header -> data. ll header is invisible to us.
   data       -> data

Resume
  If dev_has_header(dev) == false we are unable to restore the ll header,
    because it is invisible to us.


On transmit:
------------

dev_has_header(dev) == true
   mac_header -> ll header
   data       -> ll header

dev_has_header(dev) == false (ll header is invisible to us)
   mac_header -> data
   data       -> data

   We should set network_header on output to the correct position,
   packet classअगरier depends on it.
 */

/* Private packet socket काष्ठाures. */

/* identical to काष्ठा packet_mreq except it has
 * a दीर्घer address field.
 */
काष्ठा packet_mreq_max अणु
	पूर्णांक		mr_अगरindex;
	अचिन्हित लघु	mr_type;
	अचिन्हित लघु	mr_alen;
	अचिन्हित अक्षर	mr_address[MAX_ADDR_LEN];
पूर्ण;

जोड़ tpacket_uhdr अणु
	काष्ठा tpacket_hdr  *h1;
	काष्ठा tpacket2_hdr *h2;
	काष्ठा tpacket3_hdr *h3;
	व्योम *raw;
पूर्ण;

अटल पूर्णांक packet_set_ring(काष्ठा sock *sk, जोड़ tpacket_req_u *req_u,
		पूर्णांक closing, पूर्णांक tx_ring);

#घोषणा V3_ALIGNMENT	(8)

#घोषणा BLK_HDR_LEN	(ALIGN(माप(काष्ठा tpacket_block_desc), V3_ALIGNMENT))

#घोषणा BLK_PLUS_PRIV(sz_of_priv) \
	(BLK_HDR_LEN + ALIGN((sz_of_priv), V3_ALIGNMENT))

#घोषणा BLOCK_STATUS(x)	((x)->hdr.bh1.block_status)
#घोषणा BLOCK_NUM_PKTS(x)	((x)->hdr.bh1.num_pkts)
#घोषणा BLOCK_O2FP(x)		((x)->hdr.bh1.offset_to_first_pkt)
#घोषणा BLOCK_LEN(x)		((x)->hdr.bh1.blk_len)
#घोषणा BLOCK_SNUM(x)		((x)->hdr.bh1.seq_num)
#घोषणा BLOCK_O2PRIV(x)	((x)->offset_to_priv)

काष्ठा packet_sock;
अटल पूर्णांक tpacket_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       काष्ठा packet_type *pt, काष्ठा net_device *orig_dev);

अटल व्योम *packet_previous_frame(काष्ठा packet_sock *po,
		काष्ठा packet_ring_buffer *rb,
		पूर्णांक status);
अटल व्योम packet_increment_head(काष्ठा packet_ring_buffer *buff);
अटल पूर्णांक prb_curr_blk_in_use(काष्ठा tpacket_block_desc *);
अटल व्योम *prb_dispatch_next_block(काष्ठा tpacket_kbdq_core *,
			काष्ठा packet_sock *);
अटल व्योम prb_retire_current_block(काष्ठा tpacket_kbdq_core *,
		काष्ठा packet_sock *, अचिन्हित पूर्णांक status);
अटल पूर्णांक prb_queue_frozen(काष्ठा tpacket_kbdq_core *);
अटल व्योम prb_खोलो_block(काष्ठा tpacket_kbdq_core *,
		काष्ठा tpacket_block_desc *);
अटल व्योम prb_retire_rx_blk_समयr_expired(काष्ठा समयr_list *);
अटल व्योम _prb_refresh_rx_retire_blk_समयr(काष्ठा tpacket_kbdq_core *);
अटल व्योम prb_fill_rxhash(काष्ठा tpacket_kbdq_core *, काष्ठा tpacket3_hdr *);
अटल व्योम prb_clear_rxhash(काष्ठा tpacket_kbdq_core *,
		काष्ठा tpacket3_hdr *);
अटल व्योम prb_fill_vlan_info(काष्ठा tpacket_kbdq_core *,
		काष्ठा tpacket3_hdr *);
अटल व्योम packet_flush_mclist(काष्ठा sock *sk);
अटल u16 packet_pick_tx_queue(काष्ठा sk_buff *skb);

काष्ठा packet_skb_cb अणु
	जोड़ अणु
		काष्ठा sockaddr_pkt pkt;
		जोड़ अणु
			/* Trick: alias skb original length with
			 * ll.sll_family and ll.protocol in order
			 * to save room.
			 */
			अचिन्हित पूर्णांक origlen;
			काष्ठा sockaddr_ll ll;
		पूर्ण;
	पूर्ण sa;
पूर्ण;

#घोषणा vio_le() virtio_legacy_is_little_endian()

#घोषणा PACKET_SKB_CB(__skb)	((काष्ठा packet_skb_cb *)((__skb)->cb))

#घोषणा GET_PBDQC_FROM_RB(x)	((काष्ठा tpacket_kbdq_core *)(&(x)->prb_bdqc))
#घोषणा GET_PBLOCK_DESC(x, bid)	\
	((काष्ठा tpacket_block_desc *)((x)->pkbdq[(bid)].buffer))
#घोषणा GET_CURR_PBLOCK_DESC_FROM_CORE(x)	\
	((काष्ठा tpacket_block_desc *)((x)->pkbdq[(x)->kactive_blk_num].buffer))
#घोषणा GET_NEXT_PRB_BLK_NUM(x) \
	(((x)->kactive_blk_num < ((x)->knum_blocks-1)) ? \
	((x)->kactive_blk_num+1) : 0)

अटल व्योम __fanout_unlink(काष्ठा sock *sk, काष्ठा packet_sock *po);
अटल व्योम __fanout_link(काष्ठा sock *sk, काष्ठा packet_sock *po);

अटल पूर्णांक packet_direct_xmit(काष्ठा sk_buff *skb)
अणु
	वापस dev_direct_xmit(skb, packet_pick_tx_queue(skb));
पूर्ण

अटल काष्ठा net_device *packet_cached_dev_get(काष्ठा packet_sock *po)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(po->cached_dev);
	अगर (likely(dev))
		dev_hold(dev);
	rcu_पढ़ो_unlock();

	वापस dev;
पूर्ण

अटल व्योम packet_cached_dev_assign(काष्ठा packet_sock *po,
				     काष्ठा net_device *dev)
अणु
	rcu_assign_poपूर्णांकer(po->cached_dev, dev);
पूर्ण

अटल व्योम packet_cached_dev_reset(काष्ठा packet_sock *po)
अणु
	RCU_INIT_POINTER(po->cached_dev, शून्य);
पूर्ण

अटल bool packet_use_direct_xmit(स्थिर काष्ठा packet_sock *po)
अणु
	वापस po->xmit == packet_direct_xmit;
पूर्ण

अटल u16 packet_pick_tx_queue(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;
	स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;
	पूर्णांक cpu = raw_smp_processor_id();
	u16 queue_index;

#अगर_घोषित CONFIG_XPS
	skb->sender_cpu = cpu + 1;
#पूर्ण_अगर
	skb_record_rx_queue(skb, cpu % dev->real_num_tx_queues);
	अगर (ops->nकरो_select_queue) अणु
		queue_index = ops->nकरो_select_queue(dev, skb, शून्य);
		queue_index = netdev_cap_txqueue(dev, queue_index);
	पूर्ण अन्यथा अणु
		queue_index = netdev_pick_tx(dev, skb, शून्य);
	पूर्ण

	वापस queue_index;
पूर्ण

/* __रेजिस्टर_prot_hook must be invoked through रेजिस्टर_prot_hook
 * or from a context in which asynchronous accesses to the packet
 * socket is not possible (packet_create()).
 */
अटल व्योम __रेजिस्टर_prot_hook(काष्ठा sock *sk)
अणु
	काष्ठा packet_sock *po = pkt_sk(sk);

	अगर (!po->running) अणु
		अगर (po->fanout)
			__fanout_link(sk, po);
		अन्यथा
			dev_add_pack(&po->prot_hook);

		sock_hold(sk);
		po->running = 1;
	पूर्ण
पूर्ण

अटल व्योम रेजिस्टर_prot_hook(काष्ठा sock *sk)
अणु
	lockdep_निश्चित_held_once(&pkt_sk(sk)->bind_lock);
	__रेजिस्टर_prot_hook(sk);
पूर्ण

/* If the sync parameter is true, we will temporarily drop
 * the po->bind_lock and करो a synchronize_net to make sure no
 * asynchronous packet processing paths still refer to the elements
 * of po->prot_hook.  If the sync parameter is false, it is the
 * callers responsibility to take care of this.
 */
अटल व्योम __unरेजिस्टर_prot_hook(काष्ठा sock *sk, bool sync)
अणु
	काष्ठा packet_sock *po = pkt_sk(sk);

	lockdep_निश्चित_held_once(&po->bind_lock);

	po->running = 0;

	अगर (po->fanout)
		__fanout_unlink(sk, po);
	अन्यथा
		__dev_हटाओ_pack(&po->prot_hook);

	__sock_put(sk);

	अगर (sync) अणु
		spin_unlock(&po->bind_lock);
		synchronize_net();
		spin_lock(&po->bind_lock);
	पूर्ण
पूर्ण

अटल व्योम unरेजिस्टर_prot_hook(काष्ठा sock *sk, bool sync)
अणु
	काष्ठा packet_sock *po = pkt_sk(sk);

	अगर (po->running)
		__unरेजिस्टर_prot_hook(sk, sync);
पूर्ण

अटल अंतरभूत काष्ठा page * __pure pgv_to_page(व्योम *addr)
अणु
	अगर (is_vदो_स्मृति_addr(addr))
		वापस vदो_स्मृति_to_page(addr);
	वापस virt_to_page(addr);
पूर्ण

अटल व्योम __packet_set_status(काष्ठा packet_sock *po, व्योम *frame, पूर्णांक status)
अणु
	जोड़ tpacket_uhdr h;

	h.raw = frame;
	चयन (po->tp_version) अणु
	हाल TPACKET_V1:
		h.h1->tp_status = status;
		flush_dcache_page(pgv_to_page(&h.h1->tp_status));
		अवरोध;
	हाल TPACKET_V2:
		h.h2->tp_status = status;
		flush_dcache_page(pgv_to_page(&h.h2->tp_status));
		अवरोध;
	हाल TPACKET_V3:
		h.h3->tp_status = status;
		flush_dcache_page(pgv_to_page(&h.h3->tp_status));
		अवरोध;
	शेष:
		WARN(1, "TPACKET version not supported.\n");
		BUG();
	पूर्ण

	smp_wmb();
पूर्ण

अटल पूर्णांक __packet_get_status(स्थिर काष्ठा packet_sock *po, व्योम *frame)
अणु
	जोड़ tpacket_uhdr h;

	smp_rmb();

	h.raw = frame;
	चयन (po->tp_version) अणु
	हाल TPACKET_V1:
		flush_dcache_page(pgv_to_page(&h.h1->tp_status));
		वापस h.h1->tp_status;
	हाल TPACKET_V2:
		flush_dcache_page(pgv_to_page(&h.h2->tp_status));
		वापस h.h2->tp_status;
	हाल TPACKET_V3:
		flush_dcache_page(pgv_to_page(&h.h3->tp_status));
		वापस h.h3->tp_status;
	शेष:
		WARN(1, "TPACKET version not supported.\n");
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल __u32 tpacket_get_बारtamp(काष्ठा sk_buff *skb, काष्ठा बारpec64 *ts,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);

	अगर (shhwtstamps &&
	    (flags & SOF_TIMESTAMPING_RAW_HARDWARE) &&
	    kसमय_प्रकारo_बारpec64_cond(shhwtstamps->hwtstamp, ts))
		वापस TP_STATUS_TS_RAW_HARDWARE;

	अगर ((flags & SOF_TIMESTAMPING_SOFTWARE) &&
	    kसमय_प्रकारo_बारpec64_cond(skb->tstamp, ts))
		वापस TP_STATUS_TS_SOFTWARE;

	वापस 0;
पूर्ण

अटल __u32 __packet_set_बारtamp(काष्ठा packet_sock *po, व्योम *frame,
				    काष्ठा sk_buff *skb)
अणु
	जोड़ tpacket_uhdr h;
	काष्ठा बारpec64 ts;
	__u32 ts_status;

	अगर (!(ts_status = tpacket_get_बारtamp(skb, &ts, po->tp_tstamp)))
		वापस 0;

	h.raw = frame;
	/*
	 * versions 1 through 3 overflow the बारtamps in y2106, since they
	 * all store the seconds in a 32-bit अचिन्हित पूर्णांकeger.
	 * If we create a version 4, that should have a 64-bit बारtamp,
	 * either 64-bit seconds + 32-bit nanoseconds, or just 64-bit
	 * nanoseconds.
	 */
	चयन (po->tp_version) अणु
	हाल TPACKET_V1:
		h.h1->tp_sec = ts.tv_sec;
		h.h1->tp_usec = ts.tv_nsec / NSEC_PER_USEC;
		अवरोध;
	हाल TPACKET_V2:
		h.h2->tp_sec = ts.tv_sec;
		h.h2->tp_nsec = ts.tv_nsec;
		अवरोध;
	हाल TPACKET_V3:
		h.h3->tp_sec = ts.tv_sec;
		h.h3->tp_nsec = ts.tv_nsec;
		अवरोध;
	शेष:
		WARN(1, "TPACKET version not supported.\n");
		BUG();
	पूर्ण

	/* one flush is safe, as both fields always lie on the same cacheline */
	flush_dcache_page(pgv_to_page(&h.h1->tp_sec));
	smp_wmb();

	वापस ts_status;
पूर्ण

अटल व्योम *packet_lookup_frame(स्थिर काष्ठा packet_sock *po,
				 स्थिर काष्ठा packet_ring_buffer *rb,
				 अचिन्हित पूर्णांक position,
				 पूर्णांक status)
अणु
	अचिन्हित पूर्णांक pg_vec_pos, frame_offset;
	जोड़ tpacket_uhdr h;

	pg_vec_pos = position / rb->frames_per_block;
	frame_offset = position % rb->frames_per_block;

	h.raw = rb->pg_vec[pg_vec_pos].buffer +
		(frame_offset * rb->frame_size);

	अगर (status != __packet_get_status(po, h.raw))
		वापस शून्य;

	वापस h.raw;
पूर्ण

अटल व्योम *packet_current_frame(काष्ठा packet_sock *po,
		काष्ठा packet_ring_buffer *rb,
		पूर्णांक status)
अणु
	वापस packet_lookup_frame(po, rb, rb->head, status);
पूर्ण

अटल व्योम prb_del_retire_blk_समयr(काष्ठा tpacket_kbdq_core *pkc)
अणु
	del_समयr_sync(&pkc->retire_blk_समयr);
पूर्ण

अटल व्योम prb_shutकरोwn_retire_blk_समयr(काष्ठा packet_sock *po,
		काष्ठा sk_buff_head *rb_queue)
अणु
	काष्ठा tpacket_kbdq_core *pkc;

	pkc = GET_PBDQC_FROM_RB(&po->rx_ring);

	spin_lock_bh(&rb_queue->lock);
	pkc->delete_blk_समयr = 1;
	spin_unlock_bh(&rb_queue->lock);

	prb_del_retire_blk_समयr(pkc);
पूर्ण

अटल व्योम prb_setup_retire_blk_समयr(काष्ठा packet_sock *po)
अणु
	काष्ठा tpacket_kbdq_core *pkc;

	pkc = GET_PBDQC_FROM_RB(&po->rx_ring);
	समयr_setup(&pkc->retire_blk_समयr, prb_retire_rx_blk_समयr_expired,
		    0);
	pkc->retire_blk_समयr.expires = jअगरfies;
पूर्ण

अटल पूर्णांक prb_calc_retire_blk_पंचांगo(काष्ठा packet_sock *po,
				पूर्णांक blk_size_in_bytes)
अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक mbits, भाग;
	काष्ठा ethtool_link_ksettings ecmd;
	पूर्णांक err;

	rtnl_lock();
	dev = __dev_get_by_index(sock_net(&po->sk), po->अगरindex);
	अगर (unlikely(!dev)) अणु
		rtnl_unlock();
		वापस DEFAULT_PRB_RETIRE_TOV;
	पूर्ण
	err = __ethtool_get_link_ksettings(dev, &ecmd);
	rtnl_unlock();
	अगर (err)
		वापस DEFAULT_PRB_RETIRE_TOV;

	/* If the link speed is so slow you करोn't really
	 * need to worry about perf anyways
	 */
	अगर (ecmd.base.speed < SPEED_1000 ||
	    ecmd.base.speed == SPEED_UNKNOWN)
		वापस DEFAULT_PRB_RETIRE_TOV;

	भाग = ecmd.base.speed / 1000;
	mbits = (blk_size_in_bytes * 8) / (1024 * 1024);

	अगर (भाग)
		mbits /= भाग;

	अगर (भाग)
		वापस mbits + 1;
	वापस mbits;
पूर्ण

अटल व्योम prb_init_ft_ops(काष्ठा tpacket_kbdq_core *p1,
			जोड़ tpacket_req_u *req_u)
अणु
	p1->feature_req_word = req_u->req3.tp_feature_req_word;
पूर्ण

अटल व्योम init_prb_bdqc(काष्ठा packet_sock *po,
			काष्ठा packet_ring_buffer *rb,
			काष्ठा pgv *pg_vec,
			जोड़ tpacket_req_u *req_u)
अणु
	काष्ठा tpacket_kbdq_core *p1 = GET_PBDQC_FROM_RB(rb);
	काष्ठा tpacket_block_desc *pbd;

	स_रखो(p1, 0x0, माप(*p1));

	p1->knxt_seq_num = 1;
	p1->pkbdq = pg_vec;
	pbd = (काष्ठा tpacket_block_desc *)pg_vec[0].buffer;
	p1->pkblk_start	= pg_vec[0].buffer;
	p1->kblk_size = req_u->req3.tp_block_size;
	p1->knum_blocks	= req_u->req3.tp_block_nr;
	p1->hdrlen = po->tp_hdrlen;
	p1->version = po->tp_version;
	p1->last_kactive_blk_num = 0;
	po->stats.stats3.tp_मुक्तze_q_cnt = 0;
	अगर (req_u->req3.tp_retire_blk_tov)
		p1->retire_blk_tov = req_u->req3.tp_retire_blk_tov;
	अन्यथा
		p1->retire_blk_tov = prb_calc_retire_blk_पंचांगo(po,
						req_u->req3.tp_block_size);
	p1->tov_in_jअगरfies = msecs_to_jअगरfies(p1->retire_blk_tov);
	p1->blk_माप_priv = req_u->req3.tp_माप_priv;
	rwlock_init(&p1->blk_fill_in_prog_lock);

	p1->max_frame_len = p1->kblk_size - BLK_PLUS_PRIV(p1->blk_माप_priv);
	prb_init_ft_ops(p1, req_u);
	prb_setup_retire_blk_समयr(po);
	prb_खोलो_block(p1, pbd);
पूर्ण

/*  Do NOT update the last_blk_num first.
 *  Assumes sk_buff_head lock is held.
 */
अटल व्योम _prb_refresh_rx_retire_blk_समयr(काष्ठा tpacket_kbdq_core *pkc)
अणु
	mod_समयr(&pkc->retire_blk_समयr,
			jअगरfies + pkc->tov_in_jअगरfies);
	pkc->last_kactive_blk_num = pkc->kactive_blk_num;
पूर्ण

/*
 * Timer logic:
 * 1) We refresh the समयr only when we खोलो a block.
 *    By करोing this we करोn't waste cycles refreshing the समयr
 *	  on packet-by-packet basis.
 *
 * With a 1MB block-size, on a 1Gbps line, it will take
 * i) ~8 ms to fill a block + ii) स_नकल etc.
 * In this cut we are not accounting क्रम the स_नकल समय.
 *
 * So, अगर the user sets the 'tmo' to 10ms then the समयr
 * will never fire जबतक the block is still getting filled
 * (which is what we want). However, the user could choose
 * to बंद a block early and that's fine.
 *
 * But when the समयr करोes fire, we check whether or not to refresh it.
 * Since the पंचांगo granularity is in msecs, it is not too expensive
 * to refresh the समयr, lets say every '8' msecs.
 * Either the user can set the 'tmo' or we can derive it based on
 * a) line-speed and b) block-size.
 * prb_calc_retire_blk_पंचांगo() calculates the पंचांगo.
 *
 */
अटल व्योम prb_retire_rx_blk_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा packet_sock *po =
		from_समयr(po, t, rx_ring.prb_bdqc.retire_blk_समयr);
	काष्ठा tpacket_kbdq_core *pkc = GET_PBDQC_FROM_RB(&po->rx_ring);
	अचिन्हित पूर्णांक frozen;
	काष्ठा tpacket_block_desc *pbd;

	spin_lock(&po->sk.sk_receive_queue.lock);

	frozen = prb_queue_frozen(pkc);
	pbd = GET_CURR_PBLOCK_DESC_FROM_CORE(pkc);

	अगर (unlikely(pkc->delete_blk_समयr))
		जाओ out;

	/* We only need to plug the race when the block is partially filled.
	 * tpacket_rcv:
	 *		lock(); increment BLOCK_NUM_PKTS; unlock()
	 *		copy_bits() is in progress ...
	 *		समयr fires on other cpu:
	 *		we can't retire the current block because copy_bits
	 *		is in progress.
	 *
	 */
	अगर (BLOCK_NUM_PKTS(pbd)) अणु
		/* Waiting क्रम skb_copy_bits to finish... */
		ग_लिखो_lock(&pkc->blk_fill_in_prog_lock);
		ग_लिखो_unlock(&pkc->blk_fill_in_prog_lock);
	पूर्ण

	अगर (pkc->last_kactive_blk_num == pkc->kactive_blk_num) अणु
		अगर (!frozen) अणु
			अगर (!BLOCK_NUM_PKTS(pbd)) अणु
				/* An empty block. Just refresh the समयr. */
				जाओ refresh_समयr;
			पूर्ण
			prb_retire_current_block(pkc, po, TP_STATUS_BLK_TMO);
			अगर (!prb_dispatch_next_block(pkc, po))
				जाओ refresh_समयr;
			अन्यथा
				जाओ out;
		पूर्ण अन्यथा अणु
			/* Case 1. Queue was frozen because user-space was
			 *	   lagging behind.
			 */
			अगर (prb_curr_blk_in_use(pbd)) अणु
				/*
				 * Ok, user-space is still behind.
				 * So just refresh the समयr.
				 */
				जाओ refresh_समयr;
			पूर्ण अन्यथा अणु
			       /* Case 2. queue was frozen,user-space caught up,
				* now the link went idle && the समयr fired.
				* We करोn't have a block to बंद.So we खोलो this
				* block and restart the समयr.
				* खोलोing a block thaws the queue,restarts समयr
				* Thawing/समयr-refresh is a side effect.
				*/
				prb_खोलो_block(pkc, pbd);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

refresh_समयr:
	_prb_refresh_rx_retire_blk_समयr(pkc);

out:
	spin_unlock(&po->sk.sk_receive_queue.lock);
पूर्ण

अटल व्योम prb_flush_block(काष्ठा tpacket_kbdq_core *pkc1,
		काष्ठा tpacket_block_desc *pbd1, __u32 status)
अणु
	/* Flush everything minus the block header */

#अगर ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE == 1
	u8 *start, *end;

	start = (u8 *)pbd1;

	/* Skip the block header(we know header WILL fit in 4K) */
	start += PAGE_SIZE;

	end = (u8 *)PAGE_ALIGN((अचिन्हित दीर्घ)pkc1->pkblk_end);
	क्रम (; start < end; start += PAGE_SIZE)
		flush_dcache_page(pgv_to_page(start));

	smp_wmb();
#पूर्ण_अगर

	/* Now update the block status. */

	BLOCK_STATUS(pbd1) = status;

	/* Flush the block header */

#अगर ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE == 1
	start = (u8 *)pbd1;
	flush_dcache_page(pgv_to_page(start));

	smp_wmb();
#पूर्ण_अगर
पूर्ण

/*
 * Side effect:
 *
 * 1) flush the block
 * 2) Increment active_blk_num
 *
 * Note:We DONT refresh the समयr on purpose.
 *	Because almost always the next block will be खोलोed.
 */
अटल व्योम prb_बंद_block(काष्ठा tpacket_kbdq_core *pkc1,
		काष्ठा tpacket_block_desc *pbd1,
		काष्ठा packet_sock *po, अचिन्हित पूर्णांक stat)
अणु
	__u32 status = TP_STATUS_USER | stat;

	काष्ठा tpacket3_hdr *last_pkt;
	काष्ठा tpacket_hdr_v1 *h1 = &pbd1->hdr.bh1;
	काष्ठा sock *sk = &po->sk;

	अगर (atomic_पढ़ो(&po->tp_drops))
		status |= TP_STATUS_LOSING;

	last_pkt = (काष्ठा tpacket3_hdr *)pkc1->prev;
	last_pkt->tp_next_offset = 0;

	/* Get the ts of the last pkt */
	अगर (BLOCK_NUM_PKTS(pbd1)) अणु
		h1->ts_last_pkt.ts_sec = last_pkt->tp_sec;
		h1->ts_last_pkt.ts_nsec	= last_pkt->tp_nsec;
	पूर्ण अन्यथा अणु
		/* Ok, we पंचांगo'd - so get the current समय.
		 *
		 * It shouldn't really happen as we don't बंद empty
		 * blocks. See prb_retire_rx_blk_समयr_expired().
		 */
		काष्ठा बारpec64 ts;
		kसमय_get_real_ts64(&ts);
		h1->ts_last_pkt.ts_sec = ts.tv_sec;
		h1->ts_last_pkt.ts_nsec	= ts.tv_nsec;
	पूर्ण

	smp_wmb();

	/* Flush the block */
	prb_flush_block(pkc1, pbd1, status);

	sk->sk_data_पढ़ोy(sk);

	pkc1->kactive_blk_num = GET_NEXT_PRB_BLK_NUM(pkc1);
पूर्ण

अटल व्योम prb_thaw_queue(काष्ठा tpacket_kbdq_core *pkc)
अणु
	pkc->reset_pending_on_curr_blk = 0;
पूर्ण

/*
 * Side effect of खोलोing a block:
 *
 * 1) prb_queue is thawed.
 * 2) retire_blk_समयr is refreshed.
 *
 */
अटल व्योम prb_खोलो_block(काष्ठा tpacket_kbdq_core *pkc1,
	काष्ठा tpacket_block_desc *pbd1)
अणु
	काष्ठा बारpec64 ts;
	काष्ठा tpacket_hdr_v1 *h1 = &pbd1->hdr.bh1;

	smp_rmb();

	/* We could have just स_रखो this but we will lose the
	 * flexibility of making the priv area sticky
	 */

	BLOCK_SNUM(pbd1) = pkc1->knxt_seq_num++;
	BLOCK_NUM_PKTS(pbd1) = 0;
	BLOCK_LEN(pbd1) = BLK_PLUS_PRIV(pkc1->blk_माप_priv);

	kसमय_get_real_ts64(&ts);

	h1->ts_first_pkt.ts_sec = ts.tv_sec;
	h1->ts_first_pkt.ts_nsec = ts.tv_nsec;

	pkc1->pkblk_start = (अक्षर *)pbd1;
	pkc1->nxt_offset = pkc1->pkblk_start + BLK_PLUS_PRIV(pkc1->blk_माप_priv);

	BLOCK_O2FP(pbd1) = (__u32)BLK_PLUS_PRIV(pkc1->blk_माप_priv);
	BLOCK_O2PRIV(pbd1) = BLK_HDR_LEN;

	pbd1->version = pkc1->version;
	pkc1->prev = pkc1->nxt_offset;
	pkc1->pkblk_end = pkc1->pkblk_start + pkc1->kblk_size;

	prb_thaw_queue(pkc1);
	_prb_refresh_rx_retire_blk_समयr(pkc1);

	smp_wmb();
पूर्ण

/*
 * Queue मुक्तze logic:
 * 1) Assume tp_block_nr = 8 blocks.
 * 2) At समय 't0', user खोलोs Rx ring.
 * 3) Some समय past 't0', kernel starts filling blocks starting from 0 .. 7
 * 4) user-space is either sleeping or processing block '0'.
 * 5) tpacket_rcv is currently filling block '7', since there is no space left,
 *    it will बंद block-7,loop around and try to fill block '0'.
 *    call-flow:
 *    __packet_lookup_frame_in_block
 *      prb_retire_current_block()
 *      prb_dispatch_next_block()
 *        |->(BLOCK_STATUS == USER) evaluates to true
 *    5.1) Since block-0 is currently in-use, we just मुक्तze the queue.
 * 6) Now there are two हालs:
 *    6.1) Link goes idle right after the queue is frozen.
 *         But remember, the last खोलो_block() refreshed the समयr.
 *         When this समयr expires,it will refresh itself so that we can
 *         re-खोलो block-0 in near future.
 *    6.2) Link is busy and keeps on receiving packets. This is a simple
 *         हाल and __packet_lookup_frame_in_block will check अगर block-0
 *         is मुक्त and can now be re-used.
 */
अटल व्योम prb_मुक्तze_queue(काष्ठा tpacket_kbdq_core *pkc,
				  काष्ठा packet_sock *po)
अणु
	pkc->reset_pending_on_curr_blk = 1;
	po->stats.stats3.tp_मुक्तze_q_cnt++;
पूर्ण

#घोषणा TOTAL_PKT_LEN_INCL_ALIGN(length) (ALIGN((length), V3_ALIGNMENT))

/*
 * If the next block is मुक्त then we will dispatch it
 * and वापस a good offset.
 * Else, we will मुक्तze the queue.
 * So, caller must check the वापस value.
 */
अटल व्योम *prb_dispatch_next_block(काष्ठा tpacket_kbdq_core *pkc,
		काष्ठा packet_sock *po)
अणु
	काष्ठा tpacket_block_desc *pbd;

	smp_rmb();

	/* 1. Get current block num */
	pbd = GET_CURR_PBLOCK_DESC_FROM_CORE(pkc);

	/* 2. If this block is currently in_use then मुक्तze the queue */
	अगर (TP_STATUS_USER & BLOCK_STATUS(pbd)) अणु
		prb_मुक्तze_queue(pkc, po);
		वापस शून्य;
	पूर्ण

	/*
	 * 3.
	 * खोलो this block and वापस the offset where the first packet
	 * needs to get stored.
	 */
	prb_खोलो_block(pkc, pbd);
	वापस (व्योम *)pkc->nxt_offset;
पूर्ण

अटल व्योम prb_retire_current_block(काष्ठा tpacket_kbdq_core *pkc,
		काष्ठा packet_sock *po, अचिन्हित पूर्णांक status)
अणु
	काष्ठा tpacket_block_desc *pbd = GET_CURR_PBLOCK_DESC_FROM_CORE(pkc);

	/* retire/बंद the current block */
	अगर (likely(TP_STATUS_KERNEL == BLOCK_STATUS(pbd))) अणु
		/*
		 * Plug the हाल where copy_bits() is in progress on
		 * cpu-0 and tpacket_rcv() got invoked on cpu-1, didn't
		 * have space to copy the pkt in the current block and
		 * called prb_retire_current_block()
		 *
		 * We करोn't need to worry about the TMO हाल because
		 * the समयr-handler alपढ़ोy handled this हाल.
		 */
		अगर (!(status & TP_STATUS_BLK_TMO)) अणु
			/* Waiting क्रम skb_copy_bits to finish... */
			ग_लिखो_lock(&pkc->blk_fill_in_prog_lock);
			ग_लिखो_unlock(&pkc->blk_fill_in_prog_lock);
		पूर्ण
		prb_बंद_block(pkc, pbd, po, status);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक prb_curr_blk_in_use(काष्ठा tpacket_block_desc *pbd)
अणु
	वापस TP_STATUS_USER & BLOCK_STATUS(pbd);
पूर्ण

अटल पूर्णांक prb_queue_frozen(काष्ठा tpacket_kbdq_core *pkc)
अणु
	वापस pkc->reset_pending_on_curr_blk;
पूर्ण

अटल व्योम prb_clear_blk_fill_status(काष्ठा packet_ring_buffer *rb)
	__releases(&pkc->blk_fill_in_prog_lock)
अणु
	काष्ठा tpacket_kbdq_core *pkc  = GET_PBDQC_FROM_RB(rb);

	पढ़ो_unlock(&pkc->blk_fill_in_prog_lock);
पूर्ण

अटल व्योम prb_fill_rxhash(काष्ठा tpacket_kbdq_core *pkc,
			काष्ठा tpacket3_hdr *ppd)
अणु
	ppd->hv1.tp_rxhash = skb_get_hash(pkc->skb);
पूर्ण

अटल व्योम prb_clear_rxhash(काष्ठा tpacket_kbdq_core *pkc,
			काष्ठा tpacket3_hdr *ppd)
अणु
	ppd->hv1.tp_rxhash = 0;
पूर्ण

अटल व्योम prb_fill_vlan_info(काष्ठा tpacket_kbdq_core *pkc,
			काष्ठा tpacket3_hdr *ppd)
अणु
	अगर (skb_vlan_tag_present(pkc->skb)) अणु
		ppd->hv1.tp_vlan_tci = skb_vlan_tag_get(pkc->skb);
		ppd->hv1.tp_vlan_tpid = ntohs(pkc->skb->vlan_proto);
		ppd->tp_status = TP_STATUS_VLAN_VALID | TP_STATUS_VLAN_TPID_VALID;
	पूर्ण अन्यथा अणु
		ppd->hv1.tp_vlan_tci = 0;
		ppd->hv1.tp_vlan_tpid = 0;
		ppd->tp_status = TP_STATUS_AVAILABLE;
	पूर्ण
पूर्ण

अटल व्योम prb_run_all_ft_ops(काष्ठा tpacket_kbdq_core *pkc,
			काष्ठा tpacket3_hdr *ppd)
अणु
	ppd->hv1.tp_padding = 0;
	prb_fill_vlan_info(pkc, ppd);

	अगर (pkc->feature_req_word & TP_FT_REQ_FILL_RXHASH)
		prb_fill_rxhash(pkc, ppd);
	अन्यथा
		prb_clear_rxhash(pkc, ppd);
पूर्ण

अटल व्योम prb_fill_curr_block(अक्षर *curr,
				काष्ठा tpacket_kbdq_core *pkc,
				काष्ठा tpacket_block_desc *pbd,
				अचिन्हित पूर्णांक len)
	__acquires(&pkc->blk_fill_in_prog_lock)
अणु
	काष्ठा tpacket3_hdr *ppd;

	ppd  = (काष्ठा tpacket3_hdr *)curr;
	ppd->tp_next_offset = TOTAL_PKT_LEN_INCL_ALIGN(len);
	pkc->prev = curr;
	pkc->nxt_offset += TOTAL_PKT_LEN_INCL_ALIGN(len);
	BLOCK_LEN(pbd) += TOTAL_PKT_LEN_INCL_ALIGN(len);
	BLOCK_NUM_PKTS(pbd) += 1;
	पढ़ो_lock(&pkc->blk_fill_in_prog_lock);
	prb_run_all_ft_ops(pkc, ppd);
पूर्ण

/* Assumes caller has the sk->rx_queue.lock */
अटल व्योम *__packet_lookup_frame_in_block(काष्ठा packet_sock *po,
					    काष्ठा sk_buff *skb,
					    अचिन्हित पूर्णांक len
					    )
अणु
	काष्ठा tpacket_kbdq_core *pkc;
	काष्ठा tpacket_block_desc *pbd;
	अक्षर *curr, *end;

	pkc = GET_PBDQC_FROM_RB(&po->rx_ring);
	pbd = GET_CURR_PBLOCK_DESC_FROM_CORE(pkc);

	/* Queue is frozen when user space is lagging behind */
	अगर (prb_queue_frozen(pkc)) अणु
		/*
		 * Check अगर that last block which caused the queue to मुक्तze,
		 * is still in_use by user-space.
		 */
		अगर (prb_curr_blk_in_use(pbd)) अणु
			/* Can't record this packet */
			वापस शून्य;
		पूर्ण अन्यथा अणु
			/*
			 * Ok, the block was released by user-space.
			 * Now let's खोलो that block.
			 * खोलोing a block also thaws the queue.
			 * Thawing is a side effect.
			 */
			prb_खोलो_block(pkc, pbd);
		पूर्ण
	पूर्ण

	smp_mb();
	curr = pkc->nxt_offset;
	pkc->skb = skb;
	end = (अक्षर *)pbd + pkc->kblk_size;

	/* first try the current block */
	अगर (curr+TOTAL_PKT_LEN_INCL_ALIGN(len) < end) अणु
		prb_fill_curr_block(curr, pkc, pbd, len);
		वापस (व्योम *)curr;
	पूर्ण

	/* Ok, बंद the current block */
	prb_retire_current_block(pkc, po, 0);

	/* Now, try to dispatch the next block */
	curr = (अक्षर *)prb_dispatch_next_block(pkc, po);
	अगर (curr) अणु
		pbd = GET_CURR_PBLOCK_DESC_FROM_CORE(pkc);
		prb_fill_curr_block(curr, pkc, pbd, len);
		वापस (व्योम *)curr;
	पूर्ण

	/*
	 * No मुक्त blocks are available.user_space hasn't caught up yet.
	 * Queue was just frozen and now this packet will get dropped.
	 */
	वापस शून्य;
पूर्ण

अटल व्योम *packet_current_rx_frame(काष्ठा packet_sock *po,
					    काष्ठा sk_buff *skb,
					    पूर्णांक status, अचिन्हित पूर्णांक len)
अणु
	अक्षर *curr = शून्य;
	चयन (po->tp_version) अणु
	हाल TPACKET_V1:
	हाल TPACKET_V2:
		curr = packet_lookup_frame(po, &po->rx_ring,
					po->rx_ring.head, status);
		वापस curr;
	हाल TPACKET_V3:
		वापस __packet_lookup_frame_in_block(po, skb, len);
	शेष:
		WARN(1, "TPACKET version not supported\n");
		BUG();
		वापस शून्य;
	पूर्ण
पूर्ण

अटल व्योम *prb_lookup_block(स्थिर काष्ठा packet_sock *po,
			      स्थिर काष्ठा packet_ring_buffer *rb,
			      अचिन्हित पूर्णांक idx,
			      पूर्णांक status)
अणु
	काष्ठा tpacket_kbdq_core *pkc  = GET_PBDQC_FROM_RB(rb);
	काष्ठा tpacket_block_desc *pbd = GET_PBLOCK_DESC(pkc, idx);

	अगर (status != BLOCK_STATUS(pbd))
		वापस शून्य;
	वापस pbd;
पूर्ण

अटल पूर्णांक prb_previous_blk_num(काष्ठा packet_ring_buffer *rb)
अणु
	अचिन्हित पूर्णांक prev;
	अगर (rb->prb_bdqc.kactive_blk_num)
		prev = rb->prb_bdqc.kactive_blk_num-1;
	अन्यथा
		prev = rb->prb_bdqc.knum_blocks-1;
	वापस prev;
पूर्ण

/* Assumes caller has held the rx_queue.lock */
अटल व्योम *__prb_previous_block(काष्ठा packet_sock *po,
					 काष्ठा packet_ring_buffer *rb,
					 पूर्णांक status)
अणु
	अचिन्हित पूर्णांक previous = prb_previous_blk_num(rb);
	वापस prb_lookup_block(po, rb, previous, status);
पूर्ण

अटल व्योम *packet_previous_rx_frame(काष्ठा packet_sock *po,
					     काष्ठा packet_ring_buffer *rb,
					     पूर्णांक status)
अणु
	अगर (po->tp_version <= TPACKET_V2)
		वापस packet_previous_frame(po, rb, status);

	वापस __prb_previous_block(po, rb, status);
पूर्ण

अटल व्योम packet_increment_rx_head(काष्ठा packet_sock *po,
					    काष्ठा packet_ring_buffer *rb)
अणु
	चयन (po->tp_version) अणु
	हाल TPACKET_V1:
	हाल TPACKET_V2:
		वापस packet_increment_head(rb);
	हाल TPACKET_V3:
	शेष:
		WARN(1, "TPACKET version not supported.\n");
		BUG();
		वापस;
	पूर्ण
पूर्ण

अटल व्योम *packet_previous_frame(काष्ठा packet_sock *po,
		काष्ठा packet_ring_buffer *rb,
		पूर्णांक status)
अणु
	अचिन्हित पूर्णांक previous = rb->head ? rb->head - 1 : rb->frame_max;
	वापस packet_lookup_frame(po, rb, previous, status);
पूर्ण

अटल व्योम packet_increment_head(काष्ठा packet_ring_buffer *buff)
अणु
	buff->head = buff->head != buff->frame_max ? buff->head+1 : 0;
पूर्ण

अटल व्योम packet_inc_pending(काष्ठा packet_ring_buffer *rb)
अणु
	this_cpu_inc(*rb->pending_refcnt);
पूर्ण

अटल व्योम packet_dec_pending(काष्ठा packet_ring_buffer *rb)
अणु
	this_cpu_dec(*rb->pending_refcnt);
पूर्ण

अटल अचिन्हित पूर्णांक packet_पढ़ो_pending(स्थिर काष्ठा packet_ring_buffer *rb)
अणु
	अचिन्हित पूर्णांक refcnt = 0;
	पूर्णांक cpu;

	/* We करोn't use pending refcount in rx_ring. */
	अगर (rb->pending_refcnt == शून्य)
		वापस 0;

	क्रम_each_possible_cpu(cpu)
		refcnt += *per_cpu_ptr(rb->pending_refcnt, cpu);

	वापस refcnt;
पूर्ण

अटल पूर्णांक packet_alloc_pending(काष्ठा packet_sock *po)
अणु
	po->rx_ring.pending_refcnt = शून्य;

	po->tx_ring.pending_refcnt = alloc_percpu(अचिन्हित पूर्णांक);
	अगर (unlikely(po->tx_ring.pending_refcnt == शून्य))
		वापस -ENOBUFS;

	वापस 0;
पूर्ण

अटल व्योम packet_मुक्त_pending(काष्ठा packet_sock *po)
अणु
	मुक्त_percpu(po->tx_ring.pending_refcnt);
पूर्ण

#घोषणा ROOM_POW_OFF	2
#घोषणा ROOM_NONE	0x0
#घोषणा ROOM_LOW	0x1
#घोषणा ROOM_NORMAL	0x2

अटल bool __tpacket_has_room(स्थिर काष्ठा packet_sock *po, पूर्णांक घात_off)
अणु
	पूर्णांक idx, len;

	len = READ_ONCE(po->rx_ring.frame_max) + 1;
	idx = READ_ONCE(po->rx_ring.head);
	अगर (घात_off)
		idx += len >> घात_off;
	अगर (idx >= len)
		idx -= len;
	वापस packet_lookup_frame(po, &po->rx_ring, idx, TP_STATUS_KERNEL);
पूर्ण

अटल bool __tpacket_v3_has_room(स्थिर काष्ठा packet_sock *po, पूर्णांक घात_off)
अणु
	पूर्णांक idx, len;

	len = READ_ONCE(po->rx_ring.prb_bdqc.knum_blocks);
	idx = READ_ONCE(po->rx_ring.prb_bdqc.kactive_blk_num);
	अगर (घात_off)
		idx += len >> घात_off;
	अगर (idx >= len)
		idx -= len;
	वापस prb_lookup_block(po, &po->rx_ring, idx, TP_STATUS_KERNEL);
पूर्ण

अटल पूर्णांक __packet_rcv_has_room(स्थिर काष्ठा packet_sock *po,
				 स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा sock *sk = &po->sk;
	पूर्णांक ret = ROOM_NONE;

	अगर (po->prot_hook.func != tpacket_rcv) अणु
		पूर्णांक rcvbuf = READ_ONCE(sk->sk_rcvbuf);
		पूर्णांक avail = rcvbuf - atomic_पढ़ो(&sk->sk_rmem_alloc)
				   - (skb ? skb->truesize : 0);

		अगर (avail > (rcvbuf >> ROOM_POW_OFF))
			वापस ROOM_NORMAL;
		अन्यथा अगर (avail > 0)
			वापस ROOM_LOW;
		अन्यथा
			वापस ROOM_NONE;
	पूर्ण

	अगर (po->tp_version == TPACKET_V3) अणु
		अगर (__tpacket_v3_has_room(po, ROOM_POW_OFF))
			ret = ROOM_NORMAL;
		अन्यथा अगर (__tpacket_v3_has_room(po, 0))
			ret = ROOM_LOW;
	पूर्ण अन्यथा अणु
		अगर (__tpacket_has_room(po, ROOM_POW_OFF))
			ret = ROOM_NORMAL;
		अन्यथा अगर (__tpacket_has_room(po, 0))
			ret = ROOM_LOW;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक packet_rcv_has_room(काष्ठा packet_sock *po, काष्ठा sk_buff *skb)
अणु
	पूर्णांक pressure, ret;

	ret = __packet_rcv_has_room(po, skb);
	pressure = ret != ROOM_NORMAL;

	अगर (READ_ONCE(po->pressure) != pressure)
		WRITE_ONCE(po->pressure, pressure);

	वापस ret;
पूर्ण

अटल व्योम packet_rcv_try_clear_pressure(काष्ठा packet_sock *po)
अणु
	अगर (READ_ONCE(po->pressure) &&
	    __packet_rcv_has_room(po, शून्य) == ROOM_NORMAL)
		WRITE_ONCE(po->pressure,  0);
पूर्ण

अटल व्योम packet_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	skb_queue_purge(&sk->sk_error_queue);

	WARN_ON(atomic_पढ़ो(&sk->sk_rmem_alloc));
	WARN_ON(refcount_पढ़ो(&sk->sk_wmem_alloc));

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_err("Attempt to release alive packet socket: %p\n", sk);
		वापस;
	पूर्ण

	sk_refcnt_debug_dec(sk);
पूर्ण

अटल bool fanout_flow_is_huge(काष्ठा packet_sock *po, काष्ठा sk_buff *skb)
अणु
	u32 *history = po->rollover->history;
	u32 victim, rxhash;
	पूर्णांक i, count = 0;

	rxhash = skb_get_hash(skb);
	क्रम (i = 0; i < ROLLOVER_HLEN; i++)
		अगर (READ_ONCE(history[i]) == rxhash)
			count++;

	victim = pअक्रमom_u32() % ROLLOVER_HLEN;

	/* Aव्योम dirtying the cache line अगर possible */
	अगर (READ_ONCE(history[victim]) != rxhash)
		WRITE_ONCE(history[victim], rxhash);

	वापस count > (ROLLOVER_HLEN >> 1);
पूर्ण

अटल अचिन्हित पूर्णांक fanout_demux_hash(काष्ठा packet_fanout *f,
				      काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक num)
अणु
	वापस reciprocal_scale(__skb_get_hash_symmetric(skb), num);
पूर्ण

अटल अचिन्हित पूर्णांक fanout_demux_lb(काष्ठा packet_fanout *f,
				    काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक val = atomic_inc_वापस(&f->rr_cur);

	वापस val % num;
पूर्ण

अटल अचिन्हित पूर्णांक fanout_demux_cpu(काष्ठा packet_fanout *f,
				     काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक num)
अणु
	वापस smp_processor_id() % num;
पूर्ण

अटल अचिन्हित पूर्णांक fanout_demux_rnd(काष्ठा packet_fanout *f,
				     काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक num)
अणु
	वापस pअक्रमom_u32_max(num);
पूर्ण

अटल अचिन्हित पूर्णांक fanout_demux_rollover(काष्ठा packet_fanout *f,
					  काष्ठा sk_buff *skb,
					  अचिन्हित पूर्णांक idx, bool try_self,
					  अचिन्हित पूर्णांक num)
अणु
	काष्ठा packet_sock *po, *po_next, *po_skip = शून्य;
	अचिन्हित पूर्णांक i, j, room = ROOM_NONE;

	po = pkt_sk(rcu_dereference(f->arr[idx]));

	अगर (try_self) अणु
		room = packet_rcv_has_room(po, skb);
		अगर (room == ROOM_NORMAL ||
		    (room == ROOM_LOW && !fanout_flow_is_huge(po, skb)))
			वापस idx;
		po_skip = po;
	पूर्ण

	i = j = min_t(पूर्णांक, po->rollover->sock, num - 1);
	करो अणु
		po_next = pkt_sk(rcu_dereference(f->arr[i]));
		अगर (po_next != po_skip && !READ_ONCE(po_next->pressure) &&
		    packet_rcv_has_room(po_next, skb) == ROOM_NORMAL) अणु
			अगर (i != j)
				po->rollover->sock = i;
			atomic_दीर्घ_inc(&po->rollover->num);
			अगर (room == ROOM_LOW)
				atomic_दीर्घ_inc(&po->rollover->num_huge);
			वापस i;
		पूर्ण

		अगर (++i == num)
			i = 0;
	पूर्ण जबतक (i != j);

	atomic_दीर्घ_inc(&po->rollover->num_failed);
	वापस idx;
पूर्ण

अटल अचिन्हित पूर्णांक fanout_demux_qm(काष्ठा packet_fanout *f,
				    काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक num)
अणु
	वापस skb_get_queue_mapping(skb) % num;
पूर्ण

अटल अचिन्हित पूर्णांक fanout_demux_bpf(काष्ठा packet_fanout *f,
				     काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक num)
अणु
	काष्ठा bpf_prog *prog;
	अचिन्हित पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	prog = rcu_dereference(f->bpf_prog);
	अगर (prog)
		ret = bpf_prog_run_clear_cb(prog, skb) % num;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल bool fanout_has_flag(काष्ठा packet_fanout *f, u16 flag)
अणु
	वापस f->flags & (flag >> 8);
पूर्ण

अटल पूर्णांक packet_rcv_fanout(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			     काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा packet_fanout *f = pt->af_packet_priv;
	अचिन्हित पूर्णांक num = READ_ONCE(f->num_members);
	काष्ठा net *net = पढ़ो_pnet(&f->net);
	काष्ठा packet_sock *po;
	अचिन्हित पूर्णांक idx;

	अगर (!net_eq(dev_net(dev), net) || !num) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (fanout_has_flag(f, PACKET_FANOUT_FLAG_DEFRAG)) अणु
		skb = ip_check_defrag(net, skb, IP_DEFRAG_AF_PACKET);
		अगर (!skb)
			वापस 0;
	पूर्ण
	चयन (f->type) अणु
	हाल PACKET_FANOUT_HASH:
	शेष:
		idx = fanout_demux_hash(f, skb, num);
		अवरोध;
	हाल PACKET_FANOUT_LB:
		idx = fanout_demux_lb(f, skb, num);
		अवरोध;
	हाल PACKET_FANOUT_CPU:
		idx = fanout_demux_cpu(f, skb, num);
		अवरोध;
	हाल PACKET_FANOUT_RND:
		idx = fanout_demux_rnd(f, skb, num);
		अवरोध;
	हाल PACKET_FANOUT_QM:
		idx = fanout_demux_qm(f, skb, num);
		अवरोध;
	हाल PACKET_FANOUT_ROLLOVER:
		idx = fanout_demux_rollover(f, skb, 0, false, num);
		अवरोध;
	हाल PACKET_FANOUT_CBPF:
	हाल PACKET_FANOUT_EBPF:
		idx = fanout_demux_bpf(f, skb, num);
		अवरोध;
	पूर्ण

	अगर (fanout_has_flag(f, PACKET_FANOUT_FLAG_ROLLOVER))
		idx = fanout_demux_rollover(f, skb, idx, true, num);

	po = pkt_sk(rcu_dereference(f->arr[idx]));
	वापस po->prot_hook.func(skb, dev, &po->prot_hook, orig_dev);
पूर्ण

DEFINE_MUTEX(fanout_mutex);
EXPORT_SYMBOL_GPL(fanout_mutex);
अटल LIST_HEAD(fanout_list);
अटल u16 fanout_next_id;

अटल व्योम __fanout_link(काष्ठा sock *sk, काष्ठा packet_sock *po)
अणु
	काष्ठा packet_fanout *f = po->fanout;

	spin_lock(&f->lock);
	rcu_assign_poपूर्णांकer(f->arr[f->num_members], sk);
	smp_wmb();
	f->num_members++;
	अगर (f->num_members == 1)
		dev_add_pack(&f->prot_hook);
	spin_unlock(&f->lock);
पूर्ण

अटल व्योम __fanout_unlink(काष्ठा sock *sk, काष्ठा packet_sock *po)
अणु
	काष्ठा packet_fanout *f = po->fanout;
	पूर्णांक i;

	spin_lock(&f->lock);
	क्रम (i = 0; i < f->num_members; i++) अणु
		अगर (rcu_dereference_रक्षित(f->arr[i],
					      lockdep_is_held(&f->lock)) == sk)
			अवरोध;
	पूर्ण
	BUG_ON(i >= f->num_members);
	rcu_assign_poपूर्णांकer(f->arr[i],
			   rcu_dereference_रक्षित(f->arr[f->num_members - 1],
						     lockdep_is_held(&f->lock)));
	f->num_members--;
	अगर (f->num_members == 0)
		__dev_हटाओ_pack(&f->prot_hook);
	spin_unlock(&f->lock);
पूर्ण

अटल bool match_fanout_group(काष्ठा packet_type *ptype, काष्ठा sock *sk)
अणु
	अगर (sk->sk_family != PF_PACKET)
		वापस false;

	वापस ptype->af_packet_priv == pkt_sk(sk)->fanout;
पूर्ण

अटल व्योम fanout_init_data(काष्ठा packet_fanout *f)
अणु
	चयन (f->type) अणु
	हाल PACKET_FANOUT_LB:
		atomic_set(&f->rr_cur, 0);
		अवरोध;
	हाल PACKET_FANOUT_CBPF:
	हाल PACKET_FANOUT_EBPF:
		RCU_INIT_POINTER(f->bpf_prog, शून्य);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __fanout_set_data_bpf(काष्ठा packet_fanout *f, काष्ठा bpf_prog *new)
अणु
	काष्ठा bpf_prog *old;

	spin_lock(&f->lock);
	old = rcu_dereference_रक्षित(f->bpf_prog, lockdep_is_held(&f->lock));
	rcu_assign_poपूर्णांकer(f->bpf_prog, new);
	spin_unlock(&f->lock);

	अगर (old) अणु
		synchronize_net();
		bpf_prog_destroy(old);
	पूर्ण
पूर्ण

अटल पूर्णांक fanout_set_data_cbpf(काष्ठा packet_sock *po, sockptr_t data,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा bpf_prog *new;
	काष्ठा sock_fprog fprog;
	पूर्णांक ret;

	अगर (sock_flag(&po->sk, SOCK_FILTER_LOCKED))
		वापस -EPERM;

	ret = copy_bpf_fprog_from_user(&fprog, data, len);
	अगर (ret)
		वापस ret;

	ret = bpf_prog_create_from_user(&new, &fprog, शून्य, false);
	अगर (ret)
		वापस ret;

	__fanout_set_data_bpf(po->fanout, new);
	वापस 0;
पूर्ण

अटल पूर्णांक fanout_set_data_ebpf(काष्ठा packet_sock *po, sockptr_t data,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा bpf_prog *new;
	u32 fd;

	अगर (sock_flag(&po->sk, SOCK_FILTER_LOCKED))
		वापस -EPERM;
	अगर (len != माप(fd))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&fd, data, len))
		वापस -EFAULT;

	new = bpf_prog_get_type(fd, BPF_PROG_TYPE_SOCKET_FILTER);
	अगर (IS_ERR(new))
		वापस PTR_ERR(new);

	__fanout_set_data_bpf(po->fanout, new);
	वापस 0;
पूर्ण

अटल पूर्णांक fanout_set_data(काष्ठा packet_sock *po, sockptr_t data,
			   अचिन्हित पूर्णांक len)
अणु
	चयन (po->fanout->type) अणु
	हाल PACKET_FANOUT_CBPF:
		वापस fanout_set_data_cbpf(po, data, len);
	हाल PACKET_FANOUT_EBPF:
		वापस fanout_set_data_ebpf(po, data, len);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम fanout_release_data(काष्ठा packet_fanout *f)
अणु
	चयन (f->type) अणु
	हाल PACKET_FANOUT_CBPF:
	हाल PACKET_FANOUT_EBPF:
		__fanout_set_data_bpf(f, शून्य);
	पूर्ण
पूर्ण

अटल bool __fanout_id_is_मुक्त(काष्ठा sock *sk, u16 candidate_id)
अणु
	काष्ठा packet_fanout *f;

	list_क्रम_each_entry(f, &fanout_list, list) अणु
		अगर (f->id == candidate_id &&
		    पढ़ो_pnet(&f->net) == sock_net(sk)) अणु
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल bool fanout_find_new_id(काष्ठा sock *sk, u16 *new_id)
अणु
	u16 id = fanout_next_id;

	करो अणु
		अगर (__fanout_id_is_मुक्त(sk, id)) अणु
			*new_id = id;
			fanout_next_id = id + 1;
			वापस true;
		पूर्ण

		id++;
	पूर्ण जबतक (id != fanout_next_id);

	वापस false;
पूर्ण

अटल पूर्णांक fanout_add(काष्ठा sock *sk, काष्ठा fanout_args *args)
अणु
	काष्ठा packet_rollover *rollover = शून्य;
	काष्ठा packet_sock *po = pkt_sk(sk);
	u16 type_flags = args->type_flags;
	काष्ठा packet_fanout *f, *match;
	u8 type = type_flags & 0xff;
	u8 flags = type_flags >> 8;
	u16 id = args->id;
	पूर्णांक err;

	चयन (type) अणु
	हाल PACKET_FANOUT_ROLLOVER:
		अगर (type_flags & PACKET_FANOUT_FLAG_ROLLOVER)
			वापस -EINVAL;
	हाल PACKET_FANOUT_HASH:
	हाल PACKET_FANOUT_LB:
	हाल PACKET_FANOUT_CPU:
	हाल PACKET_FANOUT_RND:
	हाल PACKET_FANOUT_QM:
	हाल PACKET_FANOUT_CBPF:
	हाल PACKET_FANOUT_EBPF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&fanout_mutex);

	err = -EALREADY;
	अगर (po->fanout)
		जाओ out;

	अगर (type == PACKET_FANOUT_ROLLOVER ||
	    (type_flags & PACKET_FANOUT_FLAG_ROLLOVER)) अणु
		err = -ENOMEM;
		rollover = kzalloc(माप(*rollover), GFP_KERNEL);
		अगर (!rollover)
			जाओ out;
		atomic_दीर्घ_set(&rollover->num, 0);
		atomic_दीर्घ_set(&rollover->num_huge, 0);
		atomic_दीर्घ_set(&rollover->num_failed, 0);
	पूर्ण

	अगर (type_flags & PACKET_FANOUT_FLAG_UNIQUEID) अणु
		अगर (id != 0) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (!fanout_find_new_id(sk, &id)) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		/* ephemeral flag क्रम the first socket in the group: drop it */
		flags &= ~(PACKET_FANOUT_FLAG_UNIQUEID >> 8);
	पूर्ण

	match = शून्य;
	list_क्रम_each_entry(f, &fanout_list, list) अणु
		अगर (f->id == id &&
		    पढ़ो_pnet(&f->net) == sock_net(sk)) अणु
			match = f;
			अवरोध;
		पूर्ण
	पूर्ण
	err = -EINVAL;
	अगर (match) अणु
		अगर (match->flags != flags)
			जाओ out;
		अगर (args->max_num_members &&
		    args->max_num_members != match->max_num_members)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (args->max_num_members > PACKET_FANOUT_MAX)
			जाओ out;
		अगर (!args->max_num_members)
			/* legacy PACKET_FANOUT_MAX */
			args->max_num_members = 256;
		err = -ENOMEM;
		match = kvzalloc(काष्ठा_size(match, arr, args->max_num_members),
				 GFP_KERNEL);
		अगर (!match)
			जाओ out;
		ग_लिखो_pnet(&match->net, sock_net(sk));
		match->id = id;
		match->type = type;
		match->flags = flags;
		INIT_LIST_HEAD(&match->list);
		spin_lock_init(&match->lock);
		refcount_set(&match->sk_ref, 0);
		fanout_init_data(match);
		match->prot_hook.type = po->prot_hook.type;
		match->prot_hook.dev = po->prot_hook.dev;
		match->prot_hook.func = packet_rcv_fanout;
		match->prot_hook.af_packet_priv = match;
		match->prot_hook.id_match = match_fanout_group;
		match->max_num_members = args->max_num_members;
		list_add(&match->list, &fanout_list);
	पूर्ण
	err = -EINVAL;

	spin_lock(&po->bind_lock);
	अगर (po->running &&
	    match->type == type &&
	    match->prot_hook.type == po->prot_hook.type &&
	    match->prot_hook.dev == po->prot_hook.dev) अणु
		err = -ENOSPC;
		अगर (refcount_पढ़ो(&match->sk_ref) < match->max_num_members) अणु
			__dev_हटाओ_pack(&po->prot_hook);
			po->fanout = match;
			po->rollover = rollover;
			rollover = शून्य;
			refcount_set(&match->sk_ref, refcount_पढ़ो(&match->sk_ref) + 1);
			__fanout_link(sk, po);
			err = 0;
		पूर्ण
	पूर्ण
	spin_unlock(&po->bind_lock);

	अगर (err && !refcount_पढ़ो(&match->sk_ref)) अणु
		list_del(&match->list);
		kvमुक्त(match);
	पूर्ण

out:
	kमुक्त(rollover);
	mutex_unlock(&fanout_mutex);
	वापस err;
पूर्ण

/* If pkt_sk(sk)->fanout->sk_ref is zero, this function हटाओs
 * pkt_sk(sk)->fanout from fanout_list and वापसs pkt_sk(sk)->fanout.
 * It is the responsibility of the caller to call fanout_release_data() and
 * मुक्त the वापसed packet_fanout (after synchronize_net())
 */
अटल काष्ठा packet_fanout *fanout_release(काष्ठा sock *sk)
अणु
	काष्ठा packet_sock *po = pkt_sk(sk);
	काष्ठा packet_fanout *f;

	mutex_lock(&fanout_mutex);
	f = po->fanout;
	अगर (f) अणु
		po->fanout = शून्य;

		अगर (refcount_dec_and_test(&f->sk_ref))
			list_del(&f->list);
		अन्यथा
			f = शून्य;
	पूर्ण
	mutex_unlock(&fanout_mutex);

	वापस f;
पूर्ण

अटल bool packet_extra_vlan_len_allowed(स्थिर काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb)
अणु
	/* Earlier code assumed this would be a VLAN pkt, द्विगुन-check
	 * this now that we have the actual packet in hand. We can only
	 * करो this check on Ethernet devices.
	 */
	अगर (unlikely(dev->type != ARPHRD_ETHER))
		वापस false;

	skb_reset_mac_header(skb);
	वापस likely(eth_hdr(skb)->h_proto == htons(ETH_P_8021Q));
पूर्ण

अटल स्थिर काष्ठा proto_ops packet_ops;

अटल स्थिर काष्ठा proto_ops packet_ops_spkt;

अटल पूर्णांक packet_rcv_spkt(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा sock *sk;
	काष्ठा sockaddr_pkt *spkt;

	/*
	 *	When we रेजिस्टरed the protocol we saved the socket in the data
	 *	field क्रम just this event.
	 */

	sk = pt->af_packet_priv;

	/*
	 *	Yank back the headers [hope the device set this
	 *	right or kerboom...]
	 *
	 *	Incoming packets have ll header pulled,
	 *	push it back.
	 *
	 *	For outgoing ones skb->data == skb_mac_header(skb)
	 *	so that this procedure is noop.
	 */

	अगर (skb->pkt_type == PACKET_LOOPBACK)
		जाओ out;

	अगर (!net_eq(dev_net(dev), sock_net(sk)))
		जाओ out;

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (skb == शून्य)
		जाओ oom;

	/* drop any routing info */
	skb_dst_drop(skb);

	/* drop conntrack reference */
	nf_reset_ct(skb);

	spkt = &PACKET_SKB_CB(skb)->sa.pkt;

	skb_push(skb, skb->data - skb_mac_header(skb));

	/*
	 *	The SOCK_PACKET socket receives _all_ frames.
	 */

	spkt->spkt_family = dev->type;
	strlcpy(spkt->spkt_device, dev->name, माप(spkt->spkt_device));
	spkt->spkt_protocol = skb->protocol;

	/*
	 *	Charge the memory to the socket. This is करोne specअगरically
	 *	to prevent sockets using all the memory up.
	 */

	अगर (sock_queue_rcv_skb(sk, skb) == 0)
		वापस 0;

out:
	kमुक्त_skb(skb);
oom:
	वापस 0;
पूर्ण

अटल व्योम packet_parse_headers(काष्ठा sk_buff *skb, काष्ठा socket *sock)
अणु
	अगर ((!skb->protocol || skb->protocol == htons(ETH_P_ALL)) &&
	    sock->type == SOCK_RAW) अणु
		skb_reset_mac_header(skb);
		skb->protocol = dev_parse_header_protocol(skb);
	पूर्ण

	skb_probe_transport_header(skb);
पूर्ण

/*
 *	Output a raw packet to a device layer. This bypasses all the other
 *	protocol layers and you must thereक्रमe supply it with a complete frame
 */

अटल पूर्णांक packet_sendmsg_spkt(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	DECLARE_SOCKADDR(काष्ठा sockaddr_pkt *, saddr, msg->msg_name);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा net_device *dev;
	काष्ठा sockcm_cookie sockc;
	__be16 proto = 0;
	पूर्णांक err;
	पूर्णांक extra_len = 0;

	/*
	 *	Get and verअगरy the address.
	 */

	अगर (saddr) अणु
		अगर (msg->msg_namelen < माप(काष्ठा sockaddr))
			वापस -EINVAL;
		अगर (msg->msg_namelen == माप(काष्ठा sockaddr_pkt))
			proto = saddr->spkt_protocol;
	पूर्ण अन्यथा
		वापस -ENOTCONN;	/* SOCK_PACKET must be sent giving an address */

	/*
	 *	Find the device first to size check it
	 */

	saddr->spkt_device[माप(saddr->spkt_device) - 1] = 0;
retry:
	rcu_पढ़ो_lock();
	dev = dev_get_by_name_rcu(sock_net(sk), saddr->spkt_device);
	err = -ENODEV;
	अगर (dev == शून्य)
		जाओ out_unlock;

	err = -ENETDOWN;
	अगर (!(dev->flags & IFF_UP))
		जाओ out_unlock;

	/*
	 * You may not queue a frame bigger than the mtu. This is the lowest level
	 * raw protocol and you must करो your own fragmentation at this level.
	 */

	अगर (unlikely(sock_flag(sk, SOCK_NOFCS))) अणु
		अगर (!netअगर_supports_nofcs(dev)) अणु
			err = -EPROTONOSUPPORT;
			जाओ out_unlock;
		पूर्ण
		extra_len = 4; /* We're करोing our own CRC */
	पूर्ण

	err = -EMSGSIZE;
	अगर (len > dev->mtu + dev->hard_header_len + VLAN_HLEN + extra_len)
		जाओ out_unlock;

	अगर (!skb) अणु
		माप_प्रकार reserved = LL_RESERVED_SPACE(dev);
		पूर्णांक tlen = dev->needed_tailroom;
		अचिन्हित पूर्णांक hhlen = dev->header_ops ? dev->hard_header_len : 0;

		rcu_पढ़ो_unlock();
		skb = sock_wदो_स्मृति(sk, len + reserved + tlen, 0, GFP_KERNEL);
		अगर (skb == शून्य)
			वापस -ENOBUFS;
		/* FIXME: Save some space क्रम broken drivers that ग_लिखो a hard
		 * header at transmission समय by themselves. PPP is the notable
		 * one here. This should really be fixed at the driver level.
		 */
		skb_reserve(skb, reserved);
		skb_reset_network_header(skb);

		/* Try to align data part correctly */
		अगर (hhlen) अणु
			skb->data -= hhlen;
			skb->tail -= hhlen;
			अगर (len < hhlen)
				skb_reset_network_header(skb);
		पूर्ण
		err = स_नकल_from_msg(skb_put(skb, len), msg, len);
		अगर (err)
			जाओ out_मुक्त;
		जाओ retry;
	पूर्ण

	अगर (!dev_validate_header(dev, skb->data, len)) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (len > (dev->mtu + dev->hard_header_len + extra_len) &&
	    !packet_extra_vlan_len_allowed(dev, skb)) अणु
		err = -EMSGSIZE;
		जाओ out_unlock;
	पूर्ण

	sockcm_init(&sockc, sk);
	अगर (msg->msg_controllen) अणु
		err = sock_cmsg_send(sk, msg, &sockc);
		अगर (unlikely(err))
			जाओ out_unlock;
	पूर्ण

	skb->protocol = proto;
	skb->dev = dev;
	skb->priority = sk->sk_priority;
	skb->mark = sk->sk_mark;
	skb->tstamp = sockc.transmit_समय;

	skb_setup_tx_बारtamp(skb, sockc.tsflags);

	अगर (unlikely(extra_len == 4))
		skb->no_fcs = 1;

	packet_parse_headers(skb, sock);

	dev_queue_xmit(skb);
	rcu_पढ़ो_unlock();
	वापस len;

out_unlock:
	rcu_पढ़ो_unlock();
out_मुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक run_filter(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा sock *sk,
			       अचिन्हित पूर्णांक res)
अणु
	काष्ठा sk_filter *filter;

	rcu_पढ़ो_lock();
	filter = rcu_dereference(sk->sk_filter);
	अगर (filter != शून्य)
		res = bpf_prog_run_clear_cb(filter->prog, skb);
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण

अटल पूर्णांक packet_rcv_vnet(काष्ठा msghdr *msg, स्थिर काष्ठा sk_buff *skb,
			   माप_प्रकार *len)
अणु
	काष्ठा virtio_net_hdr vnet_hdr;

	अगर (*len < माप(vnet_hdr))
		वापस -EINVAL;
	*len -= माप(vnet_hdr);

	अगर (virtio_net_hdr_from_skb(skb, &vnet_hdr, vio_le(), true, 0))
		वापस -EINVAL;

	वापस स_नकल_to_msg(msg, (व्योम *)&vnet_hdr, माप(vnet_hdr));
पूर्ण

/*
 * This function makes lazy skb cloning in hope that most of packets
 * are discarded by BPF.
 *
 * Note tricky part: we DO mangle shared skb! skb->data, skb->len
 * and skb->cb are mangled. It works because (and until) packets
 * falling here are owned by current CPU. Output packets are cloned
 * by dev_queue_xmit_nit(), input packets are processed by net_bh
 * sequentially, so that अगर we वापस skb to original state on निकास,
 * we will not harm anyone.
 */

अटल पूर्णांक packet_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		      काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा sock *sk;
	काष्ठा sockaddr_ll *sll;
	काष्ठा packet_sock *po;
	u8 *skb_head = skb->data;
	पूर्णांक skb_len = skb->len;
	अचिन्हित पूर्णांक snaplen, res;
	bool is_drop_n_account = false;

	अगर (skb->pkt_type == PACKET_LOOPBACK)
		जाओ drop;

	sk = pt->af_packet_priv;
	po = pkt_sk(sk);

	अगर (!net_eq(dev_net(dev), sock_net(sk)))
		जाओ drop;

	skb->dev = dev;

	अगर (dev_has_header(dev)) अणु
		/* The device has an explicit notion of ll header,
		 * exported to higher levels.
		 *
		 * Otherwise, the device hides details of its frame
		 * काष्ठाure, so that corresponding packet head is
		 * never delivered to user.
		 */
		अगर (sk->sk_type != SOCK_DGRAM)
			skb_push(skb, skb->data - skb_mac_header(skb));
		अन्यथा अगर (skb->pkt_type == PACKET_OUTGOING) अणु
			/* Special हाल: outgoing packets have ll header at head */
			skb_pull(skb, skb_network_offset(skb));
		पूर्ण
	पूर्ण

	snaplen = skb->len;

	res = run_filter(skb, sk, snaplen);
	अगर (!res)
		जाओ drop_n_restore;
	अगर (snaplen > res)
		snaplen = res;

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		जाओ drop_n_acct;

	अगर (skb_shared(skb)) अणु
		काष्ठा sk_buff *nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (nskb == शून्य)
			जाओ drop_n_acct;

		अगर (skb_head != skb->data) अणु
			skb->data = skb_head;
			skb->len = skb_len;
		पूर्ण
		consume_skb(skb);
		skb = nskb;
	पूर्ण

	sock_skb_cb_check_size(माप(*PACKET_SKB_CB(skb)) + MAX_ADDR_LEN - 8);

	sll = &PACKET_SKB_CB(skb)->sa.ll;
	sll->sll_hatype = dev->type;
	sll->sll_pkttype = skb->pkt_type;
	अगर (unlikely(po->origdev))
		sll->sll_अगरindex = orig_dev->अगरindex;
	अन्यथा
		sll->sll_अगरindex = dev->अगरindex;

	sll->sll_halen = dev_parse_header(skb, sll->sll_addr);

	/* sll->sll_family and sll->sll_protocol are set in packet_recvmsg().
	 * Use their space क्रम storing the original skb length.
	 */
	PACKET_SKB_CB(skb)->sa.origlen = skb->len;

	अगर (pskb_trim(skb, snaplen))
		जाओ drop_n_acct;

	skb_set_owner_r(skb, sk);
	skb->dev = शून्य;
	skb_dst_drop(skb);

	/* drop conntrack reference */
	nf_reset_ct(skb);

	spin_lock(&sk->sk_receive_queue.lock);
	po->stats.stats1.tp_packets++;
	sock_skb_set_dropcount(sk, skb);
	__skb_queue_tail(&sk->sk_receive_queue, skb);
	spin_unlock(&sk->sk_receive_queue.lock);
	sk->sk_data_पढ़ोy(sk);
	वापस 0;

drop_n_acct:
	is_drop_n_account = true;
	atomic_inc(&po->tp_drops);
	atomic_inc(&sk->sk_drops);

drop_n_restore:
	अगर (skb_head != skb->data && skb_shared(skb)) अणु
		skb->data = skb_head;
		skb->len = skb_len;
	पूर्ण
drop:
	अगर (!is_drop_n_account)
		consume_skb(skb);
	अन्यथा
		kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक tpacket_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा sock *sk;
	काष्ठा packet_sock *po;
	काष्ठा sockaddr_ll *sll;
	जोड़ tpacket_uhdr h;
	u8 *skb_head = skb->data;
	पूर्णांक skb_len = skb->len;
	अचिन्हित पूर्णांक snaplen, res;
	अचिन्हित दीर्घ status = TP_STATUS_USER;
	अचिन्हित लघु macoff, hdrlen;
	अचिन्हित पूर्णांक netoff;
	काष्ठा sk_buff *copy_skb = शून्य;
	काष्ठा बारpec64 ts;
	__u32 ts_status;
	bool is_drop_n_account = false;
	अचिन्हित पूर्णांक slot_id = 0;
	bool करो_vnet = false;

	/* काष्ठा tpacketअणु2,3पूर्ण_hdr is aligned to a multiple of TPACKET_ALIGNMENT.
	 * We may add members to them until current aligned size without क्रमcing
	 * userspace to call माला_लोockopt(..., PACKET_HDRLEN, ...).
	 */
	BUILD_BUG_ON(TPACKET_ALIGN(माप(*h.h2)) != 32);
	BUILD_BUG_ON(TPACKET_ALIGN(माप(*h.h3)) != 48);

	अगर (skb->pkt_type == PACKET_LOOPBACK)
		जाओ drop;

	sk = pt->af_packet_priv;
	po = pkt_sk(sk);

	अगर (!net_eq(dev_net(dev), sock_net(sk)))
		जाओ drop;

	अगर (dev_has_header(dev)) अणु
		अगर (sk->sk_type != SOCK_DGRAM)
			skb_push(skb, skb->data - skb_mac_header(skb));
		अन्यथा अगर (skb->pkt_type == PACKET_OUTGOING) अणु
			/* Special हाल: outgoing packets have ll header at head */
			skb_pull(skb, skb_network_offset(skb));
		पूर्ण
	पूर्ण

	snaplen = skb->len;

	res = run_filter(skb, sk, snaplen);
	अगर (!res)
		जाओ drop_n_restore;

	/* If we are flooded, just give up */
	अगर (__packet_rcv_has_room(po, skb) == ROOM_NONE) अणु
		atomic_inc(&po->tp_drops);
		जाओ drop_n_restore;
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		status |= TP_STATUS_CSUMNOTREADY;
	अन्यथा अगर (skb->pkt_type != PACKET_OUTGOING &&
		 (skb->ip_summed == CHECKSUM_COMPLETE ||
		  skb_csum_unnecessary(skb)))
		status |= TP_STATUS_CSUM_VALID;

	अगर (snaplen > res)
		snaplen = res;

	अगर (sk->sk_type == SOCK_DGRAM) अणु
		macoff = netoff = TPACKET_ALIGN(po->tp_hdrlen) + 16 +
				  po->tp_reserve;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक maclen = skb_network_offset(skb);
		netoff = TPACKET_ALIGN(po->tp_hdrlen +
				       (maclen < 16 ? 16 : maclen)) +
				       po->tp_reserve;
		अगर (po->has_vnet_hdr) अणु
			netoff += माप(काष्ठा virtio_net_hdr);
			करो_vnet = true;
		पूर्ण
		macoff = netoff - maclen;
	पूर्ण
	अगर (netoff > अच_लघु_उच्च) अणु
		atomic_inc(&po->tp_drops);
		जाओ drop_n_restore;
	पूर्ण
	अगर (po->tp_version <= TPACKET_V2) अणु
		अगर (macoff + snaplen > po->rx_ring.frame_size) अणु
			अगर (po->copy_thresh &&
			    atomic_पढ़ो(&sk->sk_rmem_alloc) < sk->sk_rcvbuf) अणु
				अगर (skb_shared(skb)) अणु
					copy_skb = skb_clone(skb, GFP_ATOMIC);
				पूर्ण अन्यथा अणु
					copy_skb = skb_get(skb);
					skb_head = skb->data;
				पूर्ण
				अगर (copy_skb)
					skb_set_owner_r(copy_skb, sk);
			पूर्ण
			snaplen = po->rx_ring.frame_size - macoff;
			अगर ((पूर्णांक)snaplen < 0) अणु
				snaplen = 0;
				करो_vnet = false;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(macoff + snaplen >
			    GET_PBDQC_FROM_RB(&po->rx_ring)->max_frame_len)) अणु
		u32 nval;

		nval = GET_PBDQC_FROM_RB(&po->rx_ring)->max_frame_len - macoff;
		pr_err_once("tpacket_rcv: packet too big, clamped from %u to %u. macoff=%u\n",
			    snaplen, nval, macoff);
		snaplen = nval;
		अगर (unlikely((पूर्णांक)snaplen < 0)) अणु
			snaplen = 0;
			macoff = GET_PBDQC_FROM_RB(&po->rx_ring)->max_frame_len;
			करो_vnet = false;
		पूर्ण
	पूर्ण
	spin_lock(&sk->sk_receive_queue.lock);
	h.raw = packet_current_rx_frame(po, skb,
					TP_STATUS_KERNEL, (macoff+snaplen));
	अगर (!h.raw)
		जाओ drop_n_account;

	अगर (po->tp_version <= TPACKET_V2) अणु
		slot_id = po->rx_ring.head;
		अगर (test_bit(slot_id, po->rx_ring.rx_owner_map))
			जाओ drop_n_account;
		__set_bit(slot_id, po->rx_ring.rx_owner_map);
	पूर्ण

	अगर (करो_vnet &&
	    virtio_net_hdr_from_skb(skb, h.raw + macoff -
				    माप(काष्ठा virtio_net_hdr),
				    vio_le(), true, 0)) अणु
		अगर (po->tp_version == TPACKET_V3)
			prb_clear_blk_fill_status(&po->rx_ring);
		जाओ drop_n_account;
	पूर्ण

	अगर (po->tp_version <= TPACKET_V2) अणु
		packet_increment_rx_head(po, &po->rx_ring);
	/*
	 * LOSING will be reported till you पढ़ो the stats,
	 * because it's COR - Clear On Read.
	 * Anyways, moving it क्रम V1/V2 only as V3 करोesn't need this
	 * at packet level.
	 */
		अगर (atomic_पढ़ो(&po->tp_drops))
			status |= TP_STATUS_LOSING;
	पूर्ण

	po->stats.stats1.tp_packets++;
	अगर (copy_skb) अणु
		status |= TP_STATUS_COPY;
		__skb_queue_tail(&sk->sk_receive_queue, copy_skb);
	पूर्ण
	spin_unlock(&sk->sk_receive_queue.lock);

	skb_copy_bits(skb, 0, h.raw + macoff, snaplen);

	/* Always बारtamp; prefer an existing software बारtamp taken
	 * बंदr to the समय of capture.
	 */
	ts_status = tpacket_get_बारtamp(skb, &ts,
					  po->tp_tstamp | SOF_TIMESTAMPING_SOFTWARE);
	अगर (!ts_status)
		kसमय_get_real_ts64(&ts);

	status |= ts_status;

	चयन (po->tp_version) अणु
	हाल TPACKET_V1:
		h.h1->tp_len = skb->len;
		h.h1->tp_snaplen = snaplen;
		h.h1->tp_mac = macoff;
		h.h1->tp_net = netoff;
		h.h1->tp_sec = ts.tv_sec;
		h.h1->tp_usec = ts.tv_nsec / NSEC_PER_USEC;
		hdrlen = माप(*h.h1);
		अवरोध;
	हाल TPACKET_V2:
		h.h2->tp_len = skb->len;
		h.h2->tp_snaplen = snaplen;
		h.h2->tp_mac = macoff;
		h.h2->tp_net = netoff;
		h.h2->tp_sec = ts.tv_sec;
		h.h2->tp_nsec = ts.tv_nsec;
		अगर (skb_vlan_tag_present(skb)) अणु
			h.h2->tp_vlan_tci = skb_vlan_tag_get(skb);
			h.h2->tp_vlan_tpid = ntohs(skb->vlan_proto);
			status |= TP_STATUS_VLAN_VALID | TP_STATUS_VLAN_TPID_VALID;
		पूर्ण अन्यथा अणु
			h.h2->tp_vlan_tci = 0;
			h.h2->tp_vlan_tpid = 0;
		पूर्ण
		स_रखो(h.h2->tp_padding, 0, माप(h.h2->tp_padding));
		hdrlen = माप(*h.h2);
		अवरोध;
	हाल TPACKET_V3:
		/* tp_nxt_offset,vlan are alपढ़ोy populated above.
		 * So DONT clear those fields here
		 */
		h.h3->tp_status |= status;
		h.h3->tp_len = skb->len;
		h.h3->tp_snaplen = snaplen;
		h.h3->tp_mac = macoff;
		h.h3->tp_net = netoff;
		h.h3->tp_sec  = ts.tv_sec;
		h.h3->tp_nsec = ts.tv_nsec;
		स_रखो(h.h3->tp_padding, 0, माप(h.h3->tp_padding));
		hdrlen = माप(*h.h3);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	sll = h.raw + TPACKET_ALIGN(hdrlen);
	sll->sll_halen = dev_parse_header(skb, sll->sll_addr);
	sll->sll_family = AF_PACKET;
	sll->sll_hatype = dev->type;
	sll->sll_protocol = skb->protocol;
	sll->sll_pkttype = skb->pkt_type;
	अगर (unlikely(po->origdev))
		sll->sll_अगरindex = orig_dev->अगरindex;
	अन्यथा
		sll->sll_अगरindex = dev->अगरindex;

	smp_mb();

#अगर ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE == 1
	अगर (po->tp_version <= TPACKET_V2) अणु
		u8 *start, *end;

		end = (u8 *) PAGE_ALIGN((अचिन्हित दीर्घ) h.raw +
					macoff + snaplen);

		क्रम (start = h.raw; start < end; start += PAGE_SIZE)
			flush_dcache_page(pgv_to_page(start));
	पूर्ण
	smp_wmb();
#पूर्ण_अगर

	अगर (po->tp_version <= TPACKET_V2) अणु
		spin_lock(&sk->sk_receive_queue.lock);
		__packet_set_status(po, h.raw, status);
		__clear_bit(slot_id, po->rx_ring.rx_owner_map);
		spin_unlock(&sk->sk_receive_queue.lock);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण अन्यथा अगर (po->tp_version == TPACKET_V3) अणु
		prb_clear_blk_fill_status(&po->rx_ring);
	पूर्ण

drop_n_restore:
	अगर (skb_head != skb->data && skb_shared(skb)) अणु
		skb->data = skb_head;
		skb->len = skb_len;
	पूर्ण
drop:
	अगर (!is_drop_n_account)
		consume_skb(skb);
	अन्यथा
		kमुक्त_skb(skb);
	वापस 0;

drop_n_account:
	spin_unlock(&sk->sk_receive_queue.lock);
	atomic_inc(&po->tp_drops);
	is_drop_n_account = true;

	sk->sk_data_पढ़ोy(sk);
	kमुक्त_skb(copy_skb);
	जाओ drop_n_restore;
पूर्ण

अटल व्योम tpacket_deकाष्ठा_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा packet_sock *po = pkt_sk(skb->sk);

	अगर (likely(po->tx_ring.pg_vec)) अणु
		व्योम *ph;
		__u32 ts;

		ph = skb_zcopy_get_nouarg(skb);
		packet_dec_pending(&po->tx_ring);

		ts = __packet_set_बारtamp(po, ph, skb);
		__packet_set_status(po, ph, TP_STATUS_AVAILABLE | ts);

		अगर (!packet_पढ़ो_pending(&po->tx_ring))
			complete(&po->skb_completion);
	पूर्ण

	sock_wमुक्त(skb);
पूर्ण

अटल पूर्णांक __packet_snd_vnet_parse(काष्ठा virtio_net_hdr *vnet_hdr, माप_प्रकार len)
अणु
	अगर ((vnet_hdr->flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) &&
	    (__virtio16_to_cpu(vio_le(), vnet_hdr->csum_start) +
	     __virtio16_to_cpu(vio_le(), vnet_hdr->csum_offset) + 2 >
	      __virtio16_to_cpu(vio_le(), vnet_hdr->hdr_len)))
		vnet_hdr->hdr_len = __cpu_to_virtio16(vio_le(),
			 __virtio16_to_cpu(vio_le(), vnet_hdr->csum_start) +
			__virtio16_to_cpu(vio_le(), vnet_hdr->csum_offset) + 2);

	अगर (__virtio16_to_cpu(vio_le(), vnet_hdr->hdr_len) > len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक packet_snd_vnet_parse(काष्ठा msghdr *msg, माप_प्रकार *len,
				 काष्ठा virtio_net_hdr *vnet_hdr)
अणु
	अगर (*len < माप(*vnet_hdr))
		वापस -EINVAL;
	*len -= माप(*vnet_hdr);

	अगर (!copy_from_iter_full(vnet_hdr, माप(*vnet_hdr), &msg->msg_iter))
		वापस -EFAULT;

	वापस __packet_snd_vnet_parse(vnet_hdr, *len);
पूर्ण

अटल पूर्णांक tpacket_fill_skb(काष्ठा packet_sock *po, काष्ठा sk_buff *skb,
		व्योम *frame, काष्ठा net_device *dev, व्योम *data, पूर्णांक tp_len,
		__be16 proto, अचिन्हित अक्षर *addr, पूर्णांक hlen, पूर्णांक copylen,
		स्थिर काष्ठा sockcm_cookie *sockc)
अणु
	जोड़ tpacket_uhdr ph;
	पूर्णांक to_ग_लिखो, offset, len, nr_frags, len_max;
	काष्ठा socket *sock = po->sk.sk_socket;
	काष्ठा page *page;
	पूर्णांक err;

	ph.raw = frame;

	skb->protocol = proto;
	skb->dev = dev;
	skb->priority = po->sk.sk_priority;
	skb->mark = po->sk.sk_mark;
	skb->tstamp = sockc->transmit_समय;
	skb_setup_tx_बारtamp(skb, sockc->tsflags);
	skb_zcopy_set_nouarg(skb, ph.raw);

	skb_reserve(skb, hlen);
	skb_reset_network_header(skb);

	to_ग_लिखो = tp_len;

	अगर (sock->type == SOCK_DGRAM) अणु
		err = dev_hard_header(skb, dev, ntohs(proto), addr,
				शून्य, tp_len);
		अगर (unlikely(err < 0))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (copylen) अणु
		पूर्णांक hdrlen = min_t(पूर्णांक, copylen, tp_len);

		skb_push(skb, dev->hard_header_len);
		skb_put(skb, copylen - dev->hard_header_len);
		err = skb_store_bits(skb, 0, data, hdrlen);
		अगर (unlikely(err))
			वापस err;
		अगर (!dev_validate_header(dev, skb->data, hdrlen))
			वापस -EINVAL;

		data += hdrlen;
		to_ग_लिखो -= hdrlen;
	पूर्ण

	offset = offset_in_page(data);
	len_max = PAGE_SIZE - offset;
	len = ((to_ग_लिखो > len_max) ? len_max : to_ग_लिखो);

	skb->data_len = to_ग_लिखो;
	skb->len += to_ग_लिखो;
	skb->truesize += to_ग_लिखो;
	refcount_add(to_ग_लिखो, &po->sk.sk_wmem_alloc);

	जबतक (likely(to_ग_लिखो)) अणु
		nr_frags = skb_shinfo(skb)->nr_frags;

		अगर (unlikely(nr_frags >= MAX_SKB_FRAGS)) अणु
			pr_err("Packet exceed the number of skb frags(%lu)\n",
			       MAX_SKB_FRAGS);
			वापस -EFAULT;
		पूर्ण

		page = pgv_to_page(data);
		data += len;
		flush_dcache_page(page);
		get_page(page);
		skb_fill_page_desc(skb, nr_frags, page, offset, len);
		to_ग_लिखो -= len;
		offset = 0;
		len_max = PAGE_SIZE;
		len = ((to_ग_लिखो > len_max) ? len_max : to_ग_लिखो);
	पूर्ण

	packet_parse_headers(skb, sock);

	वापस tp_len;
पूर्ण

अटल पूर्णांक tpacket_parse_header(काष्ठा packet_sock *po, व्योम *frame,
				पूर्णांक size_max, व्योम **data)
अणु
	जोड़ tpacket_uhdr ph;
	पूर्णांक tp_len, off;

	ph.raw = frame;

	चयन (po->tp_version) अणु
	हाल TPACKET_V3:
		अगर (ph.h3->tp_next_offset != 0) अणु
			pr_warn_once("variable sized slot not supported");
			वापस -EINVAL;
		पूर्ण
		tp_len = ph.h3->tp_len;
		अवरोध;
	हाल TPACKET_V2:
		tp_len = ph.h2->tp_len;
		अवरोध;
	शेष:
		tp_len = ph.h1->tp_len;
		अवरोध;
	पूर्ण
	अगर (unlikely(tp_len > size_max)) अणु
		pr_err("packet size is too long (%d > %d)\n", tp_len, size_max);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (unlikely(po->tp_tx_has_off)) अणु
		पूर्णांक off_min, off_max;

		off_min = po->tp_hdrlen - माप(काष्ठा sockaddr_ll);
		off_max = po->tx_ring.frame_size - tp_len;
		अगर (po->sk.sk_type == SOCK_DGRAM) अणु
			चयन (po->tp_version) अणु
			हाल TPACKET_V3:
				off = ph.h3->tp_net;
				अवरोध;
			हाल TPACKET_V2:
				off = ph.h2->tp_net;
				अवरोध;
			शेष:
				off = ph.h1->tp_net;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (po->tp_version) अणु
			हाल TPACKET_V3:
				off = ph.h3->tp_mac;
				अवरोध;
			हाल TPACKET_V2:
				off = ph.h2->tp_mac;
				अवरोध;
			शेष:
				off = ph.h1->tp_mac;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (unlikely((off < off_min) || (off_max < off)))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		off = po->tp_hdrlen - माप(काष्ठा sockaddr_ll);
	पूर्ण

	*data = frame + off;
	वापस tp_len;
पूर्ण

अटल पूर्णांक tpacket_snd(काष्ठा packet_sock *po, काष्ठा msghdr *msg)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा net_device *dev;
	काष्ठा virtio_net_hdr *vnet_hdr = शून्य;
	काष्ठा sockcm_cookie sockc;
	__be16 proto;
	पूर्णांक err, reserve = 0;
	व्योम *ph;
	DECLARE_SOCKADDR(काष्ठा sockaddr_ll *, saddr, msg->msg_name);
	bool need_रुको = !(msg->msg_flags & MSG_DONTWAIT);
	अचिन्हित अक्षर *addr = शून्य;
	पूर्णांक tp_len, size_max;
	व्योम *data;
	पूर्णांक len_sum = 0;
	पूर्णांक status = TP_STATUS_AVAILABLE;
	पूर्णांक hlen, tlen, copylen = 0;
	दीर्घ समयo = 0;

	mutex_lock(&po->pg_vec_lock);

	/* packet_sendmsg() check on tx_ring.pg_vec was lockless,
	 * we need to confirm it under protection of pg_vec_lock.
	 */
	अगर (unlikely(!po->tx_ring.pg_vec)) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (likely(saddr == शून्य)) अणु
		dev	= packet_cached_dev_get(po);
		proto	= READ_ONCE(po->num);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		अगर (msg->msg_namelen < माप(काष्ठा sockaddr_ll))
			जाओ out;
		अगर (msg->msg_namelen < (saddr->sll_halen
					+ दुरत्व(काष्ठा sockaddr_ll,
						sll_addr)))
			जाओ out;
		proto	= saddr->sll_protocol;
		dev = dev_get_by_index(sock_net(&po->sk), saddr->sll_अगरindex);
		अगर (po->sk.sk_socket->type == SOCK_DGRAM) अणु
			अगर (dev && msg->msg_namelen < dev->addr_len +
				   दुरत्व(काष्ठा sockaddr_ll, sll_addr))
				जाओ out_put;
			addr = saddr->sll_addr;
		पूर्ण
	पूर्ण

	err = -ENXIO;
	अगर (unlikely(dev == शून्य))
		जाओ out;
	err = -ENETDOWN;
	अगर (unlikely(!(dev->flags & IFF_UP)))
		जाओ out_put;

	sockcm_init(&sockc, &po->sk);
	अगर (msg->msg_controllen) अणु
		err = sock_cmsg_send(&po->sk, msg, &sockc);
		अगर (unlikely(err))
			जाओ out_put;
	पूर्ण

	अगर (po->sk.sk_socket->type == SOCK_RAW)
		reserve = dev->hard_header_len;
	size_max = po->tx_ring.frame_size
		- (po->tp_hdrlen - माप(काष्ठा sockaddr_ll));

	अगर ((size_max > dev->mtu + reserve + VLAN_HLEN) && !po->has_vnet_hdr)
		size_max = dev->mtu + reserve + VLAN_HLEN;

	reinit_completion(&po->skb_completion);

	करो अणु
		ph = packet_current_frame(po, &po->tx_ring,
					  TP_STATUS_SEND_REQUEST);
		अगर (unlikely(ph == शून्य)) अणु
			अगर (need_रुको && skb) अणु
				समयo = sock_sndसमयo(&po->sk, msg->msg_flags & MSG_DONTWAIT);
				समयo = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&po->skb_completion, समयo);
				अगर (समयo <= 0) अणु
					err = !समयo ? -ETIMEDOUT : -ERESTARTSYS;
					जाओ out_put;
				पूर्ण
			पूर्ण
			/* check क्रम additional frames */
			जारी;
		पूर्ण

		skb = शून्य;
		tp_len = tpacket_parse_header(po, ph, size_max, &data);
		अगर (tp_len < 0)
			जाओ tpacket_error;

		status = TP_STATUS_SEND_REQUEST;
		hlen = LL_RESERVED_SPACE(dev);
		tlen = dev->needed_tailroom;
		अगर (po->has_vnet_hdr) अणु
			vnet_hdr = data;
			data += माप(*vnet_hdr);
			tp_len -= माप(*vnet_hdr);
			अगर (tp_len < 0 ||
			    __packet_snd_vnet_parse(vnet_hdr, tp_len)) अणु
				tp_len = -EINVAL;
				जाओ tpacket_error;
			पूर्ण
			copylen = __virtio16_to_cpu(vio_le(),
						    vnet_hdr->hdr_len);
		पूर्ण
		copylen = max_t(पूर्णांक, copylen, dev->hard_header_len);
		skb = sock_alloc_send_skb(&po->sk,
				hlen + tlen + माप(काष्ठा sockaddr_ll) +
				(copylen - dev->hard_header_len),
				!need_रुको, &err);

		अगर (unlikely(skb == शून्य)) अणु
			/* we assume the socket was initially ग_लिखोable ... */
			अगर (likely(len_sum > 0))
				err = len_sum;
			जाओ out_status;
		पूर्ण
		tp_len = tpacket_fill_skb(po, skb, ph, dev, data, tp_len, proto,
					  addr, hlen, copylen, &sockc);
		अगर (likely(tp_len >= 0) &&
		    tp_len > dev->mtu + reserve &&
		    !po->has_vnet_hdr &&
		    !packet_extra_vlan_len_allowed(dev, skb))
			tp_len = -EMSGSIZE;

		अगर (unlikely(tp_len < 0)) अणु
tpacket_error:
			अगर (po->tp_loss) अणु
				__packet_set_status(po, ph,
						TP_STATUS_AVAILABLE);
				packet_increment_head(&po->tx_ring);
				kमुक्त_skb(skb);
				जारी;
			पूर्ण अन्यथा अणु
				status = TP_STATUS_WRONG_FORMAT;
				err = tp_len;
				जाओ out_status;
			पूर्ण
		पूर्ण

		अगर (po->has_vnet_hdr) अणु
			अगर (virtio_net_hdr_to_skb(skb, vnet_hdr, vio_le())) अणु
				tp_len = -EINVAL;
				जाओ tpacket_error;
			पूर्ण
			virtio_net_hdr_set_proto(skb, vnet_hdr);
		पूर्ण

		skb->deकाष्ठाor = tpacket_deकाष्ठा_skb;
		__packet_set_status(po, ph, TP_STATUS_SENDING);
		packet_inc_pending(&po->tx_ring);

		status = TP_STATUS_SEND_REQUEST;
		err = po->xmit(skb);
		अगर (unlikely(err > 0)) अणु
			err = net_xmit_त्रुटि_सं(err);
			अगर (err && __packet_get_status(po, ph) ==
				   TP_STATUS_AVAILABLE) अणु
				/* skb was deकाष्ठाed alपढ़ोy */
				skb = शून्य;
				जाओ out_status;
			पूर्ण
			/*
			 * skb was dropped but not deकाष्ठाed yet;
			 * let's treat it like congestion or err < 0
			 */
			err = 0;
		पूर्ण
		packet_increment_head(&po->tx_ring);
		len_sum += tp_len;
	पूर्ण जबतक (likely((ph != शून्य) ||
		/* Note: packet_पढ़ो_pending() might be slow अगर we have
		 * to call it as it's per_cpu variable, but in fast-path
		 * we alपढ़ोy लघु-circuit the loop with the first
		 * condition, and luckily करोn't have to go that path
		 * anyway.
		 */
		 (need_रुको && packet_पढ़ो_pending(&po->tx_ring))));

	err = len_sum;
	जाओ out_put;

out_status:
	__packet_set_status(po, ph, status);
	kमुक्त_skb(skb);
out_put:
	dev_put(dev);
out:
	mutex_unlock(&po->pg_vec_lock);
	वापस err;
पूर्ण

अटल काष्ठा sk_buff *packet_alloc_skb(काष्ठा sock *sk, माप_प्रकार prepad,
				        माप_प्रकार reserve, माप_प्रकार len,
				        माप_प्रकार linear, पूर्णांक noblock,
				        पूर्णांक *err)
अणु
	काष्ठा sk_buff *skb;

	/* Under a page?  Don't bother with paged skb. */
	अगर (prepad + len < PAGE_SIZE || !linear)
		linear = len;

	skb = sock_alloc_send_pskb(sk, prepad + linear, len - linear, noblock,
				   err, 0);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, reserve);
	skb_put(skb, linear);
	skb->data_len = len - linear;
	skb->len += len - linear;

	वापस skb;
पूर्ण

अटल पूर्णांक packet_snd(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	DECLARE_SOCKADDR(काष्ठा sockaddr_ll *, saddr, msg->msg_name);
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	__be16 proto;
	अचिन्हित अक्षर *addr = शून्य;
	पूर्णांक err, reserve = 0;
	काष्ठा sockcm_cookie sockc;
	काष्ठा virtio_net_hdr vnet_hdr = अणु 0 पूर्ण;
	पूर्णांक offset = 0;
	काष्ठा packet_sock *po = pkt_sk(sk);
	bool has_vnet_hdr = false;
	पूर्णांक hlen, tlen, linear;
	पूर्णांक extra_len = 0;

	/*
	 *	Get and verअगरy the address.
	 */

	अगर (likely(saddr == शून्य)) अणु
		dev	= packet_cached_dev_get(po);
		proto	= READ_ONCE(po->num);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		अगर (msg->msg_namelen < माप(काष्ठा sockaddr_ll))
			जाओ out;
		अगर (msg->msg_namelen < (saddr->sll_halen + दुरत्व(काष्ठा sockaddr_ll, sll_addr)))
			जाओ out;
		proto	= saddr->sll_protocol;
		dev = dev_get_by_index(sock_net(sk), saddr->sll_अगरindex);
		अगर (sock->type == SOCK_DGRAM) अणु
			अगर (dev && msg->msg_namelen < dev->addr_len +
				   दुरत्व(काष्ठा sockaddr_ll, sll_addr))
				जाओ out_unlock;
			addr = saddr->sll_addr;
		पूर्ण
	पूर्ण

	err = -ENXIO;
	अगर (unlikely(dev == शून्य))
		जाओ out_unlock;
	err = -ENETDOWN;
	अगर (unlikely(!(dev->flags & IFF_UP)))
		जाओ out_unlock;

	sockcm_init(&sockc, sk);
	sockc.mark = sk->sk_mark;
	अगर (msg->msg_controllen) अणु
		err = sock_cmsg_send(sk, msg, &sockc);
		अगर (unlikely(err))
			जाओ out_unlock;
	पूर्ण

	अगर (sock->type == SOCK_RAW)
		reserve = dev->hard_header_len;
	अगर (po->has_vnet_hdr) अणु
		err = packet_snd_vnet_parse(msg, &len, &vnet_hdr);
		अगर (err)
			जाओ out_unlock;
		has_vnet_hdr = true;
	पूर्ण

	अगर (unlikely(sock_flag(sk, SOCK_NOFCS))) अणु
		अगर (!netअगर_supports_nofcs(dev)) अणु
			err = -EPROTONOSUPPORT;
			जाओ out_unlock;
		पूर्ण
		extra_len = 4; /* We're करोing our own CRC */
	पूर्ण

	err = -EMSGSIZE;
	अगर (!vnet_hdr.gso_type &&
	    (len > dev->mtu + reserve + VLAN_HLEN + extra_len))
		जाओ out_unlock;

	err = -ENOBUFS;
	hlen = LL_RESERVED_SPACE(dev);
	tlen = dev->needed_tailroom;
	linear = __virtio16_to_cpu(vio_le(), vnet_hdr.hdr_len);
	linear = max(linear, min_t(पूर्णांक, len, dev->hard_header_len));
	skb = packet_alloc_skb(sk, hlen + tlen, hlen, len, linear,
			       msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (skb == शून्य)
		जाओ out_unlock;

	skb_reset_network_header(skb);

	err = -EINVAL;
	अगर (sock->type == SOCK_DGRAM) अणु
		offset = dev_hard_header(skb, dev, ntohs(proto), addr, शून्य, len);
		अगर (unlikely(offset < 0))
			जाओ out_मुक्त;
	पूर्ण अन्यथा अगर (reserve) अणु
		skb_reserve(skb, -reserve);
		अगर (len < reserve + माप(काष्ठा ipv6hdr) &&
		    dev->min_header_len != dev->hard_header_len)
			skb_reset_network_header(skb);
	पूर्ण

	/* Returns -EFAULT on error */
	err = skb_copy_datagram_from_iter(skb, offset, &msg->msg_iter, len);
	अगर (err)
		जाओ out_मुक्त;

	अगर (sock->type == SOCK_RAW &&
	    !dev_validate_header(dev, skb->data, len)) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	skb_setup_tx_बारtamp(skb, sockc.tsflags);

	अगर (!vnet_hdr.gso_type && (len > dev->mtu + reserve + extra_len) &&
	    !packet_extra_vlan_len_allowed(dev, skb)) अणु
		err = -EMSGSIZE;
		जाओ out_मुक्त;
	पूर्ण

	skb->protocol = proto;
	skb->dev = dev;
	skb->priority = sk->sk_priority;
	skb->mark = sockc.mark;
	skb->tstamp = sockc.transmit_समय;

	अगर (has_vnet_hdr) अणु
		err = virtio_net_hdr_to_skb(skb, &vnet_hdr, vio_le());
		अगर (err)
			जाओ out_मुक्त;
		len += माप(vnet_hdr);
		virtio_net_hdr_set_proto(skb, &vnet_hdr);
	पूर्ण

	packet_parse_headers(skb, sock);

	अगर (unlikely(extra_len == 4))
		skb->no_fcs = 1;

	err = po->xmit(skb);
	अगर (err > 0 && (err = net_xmit_त्रुटि_सं(err)) != 0)
		जाओ out_unlock;

	dev_put(dev);

	वापस len;

out_मुक्त:
	kमुक्त_skb(skb);
out_unlock:
	अगर (dev)
		dev_put(dev);
out:
	वापस err;
पूर्ण

अटल पूर्णांक packet_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा packet_sock *po = pkt_sk(sk);

	/* Reading tx_ring.pg_vec without holding pg_vec_lock is racy.
	 * tpacket_snd() will reकरो the check safely.
	 */
	अगर (data_race(po->tx_ring.pg_vec))
		वापस tpacket_snd(po, msg);

	वापस packet_snd(sock, msg, len);
पूर्ण

/*
 *	Close a PACKET socket. This is fairly simple. We immediately go
 *	to 'closed' state and हटाओ our protocol entry in the device list.
 */

अटल पूर्णांक packet_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा packet_sock *po;
	काष्ठा packet_fanout *f;
	काष्ठा net *net;
	जोड़ tpacket_req_u req_u;

	अगर (!sk)
		वापस 0;

	net = sock_net(sk);
	po = pkt_sk(sk);

	mutex_lock(&net->packet.sklist_lock);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&net->packet.sklist_lock);

	preempt_disable();
	sock_prot_inuse_add(net, sk->sk_prot, -1);
	preempt_enable();

	spin_lock(&po->bind_lock);
	unरेजिस्टर_prot_hook(sk, false);
	packet_cached_dev_reset(po);

	अगर (po->prot_hook.dev) अणु
		dev_put(po->prot_hook.dev);
		po->prot_hook.dev = शून्य;
	पूर्ण
	spin_unlock(&po->bind_lock);

	packet_flush_mclist(sk);

	lock_sock(sk);
	अगर (po->rx_ring.pg_vec) अणु
		स_रखो(&req_u, 0, माप(req_u));
		packet_set_ring(sk, &req_u, 1, 0);
	पूर्ण

	अगर (po->tx_ring.pg_vec) अणु
		स_रखो(&req_u, 0, माप(req_u));
		packet_set_ring(sk, &req_u, 1, 1);
	पूर्ण
	release_sock(sk);

	f = fanout_release(sk);

	synchronize_net();

	kमुक्त(po->rollover);
	अगर (f) अणु
		fanout_release_data(f);
		kvमुक्त(f);
	पूर्ण
	/*
	 *	Now the socket is dead. No more input will appear.
	 */
	sock_orphan(sk);
	sock->sk = शून्य;

	/* Purge queues */

	skb_queue_purge(&sk->sk_receive_queue);
	packet_मुक्त_pending(po);
	sk_refcnt_debug_release(sk);

	sock_put(sk);
	वापस 0;
पूर्ण

/*
 *	Attach a packet hook.
 */

अटल पूर्णांक packet_करो_bind(काष्ठा sock *sk, स्थिर अक्षर *name, पूर्णांक अगरindex,
			  __be16 proto)
अणु
	काष्ठा packet_sock *po = pkt_sk(sk);
	काष्ठा net_device *dev_curr;
	__be16 proto_curr;
	bool need_rehook;
	काष्ठा net_device *dev = शून्य;
	पूर्णांक ret = 0;
	bool unlisted = false;

	lock_sock(sk);
	spin_lock(&po->bind_lock);
	rcu_पढ़ो_lock();

	अगर (po->fanout) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (name) अणु
		dev = dev_get_by_name_rcu(sock_net(sk), name);
		अगर (!dev) अणु
			ret = -ENODEV;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अगर (अगरindex) अणु
		dev = dev_get_by_index_rcu(sock_net(sk), अगरindex);
		अगर (!dev) अणु
			ret = -ENODEV;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर (dev)
		dev_hold(dev);

	proto_curr = po->prot_hook.type;
	dev_curr = po->prot_hook.dev;

	need_rehook = proto_curr != proto || dev_curr != dev;

	अगर (need_rehook) अणु
		अगर (po->running) अणु
			rcu_पढ़ो_unlock();
			/* prevents packet_notअगरier() from calling
			 * रेजिस्टर_prot_hook()
			 */
			WRITE_ONCE(po->num, 0);
			__unरेजिस्टर_prot_hook(sk, true);
			rcu_पढ़ो_lock();
			dev_curr = po->prot_hook.dev;
			अगर (dev)
				unlisted = !dev_get_by_index_rcu(sock_net(sk),
								 dev->अगरindex);
		पूर्ण

		BUG_ON(po->running);
		WRITE_ONCE(po->num, proto);
		po->prot_hook.type = proto;

		अगर (unlikely(unlisted)) अणु
			dev_put(dev);
			po->prot_hook.dev = शून्य;
			WRITE_ONCE(po->अगरindex, -1);
			packet_cached_dev_reset(po);
		पूर्ण अन्यथा अणु
			po->prot_hook.dev = dev;
			WRITE_ONCE(po->अगरindex, dev ? dev->अगरindex : 0);
			packet_cached_dev_assign(po, dev);
		पूर्ण
	पूर्ण
	अगर (dev_curr)
		dev_put(dev_curr);

	अगर (proto == 0 || !need_rehook)
		जाओ out_unlock;

	अगर (!unlisted && (!dev || (dev->flags & IFF_UP))) अणु
		रेजिस्टर_prot_hook(sk);
	पूर्ण अन्यथा अणु
		sk->sk_err = ENETDOWN;
		अगर (!sock_flag(sk, SOCK_DEAD))
			sk->sk_error_report(sk);
	पूर्ण

out_unlock:
	rcu_पढ़ो_unlock();
	spin_unlock(&po->bind_lock);
	release_sock(sk);
	वापस ret;
पूर्ण

/*
 *	Bind a packet socket to a device
 */

अटल पूर्णांक packet_bind_spkt(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			    पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	अक्षर name[माप(uaddr->sa_data) + 1];

	/*
	 *	Check legality
	 */

	अगर (addr_len != माप(काष्ठा sockaddr))
		वापस -EINVAL;
	/* uaddr->sa_data comes from the userspace, it's not guaranteed to be
	 * zero-terminated.
	 */
	स_नकल(name, uaddr->sa_data, माप(uaddr->sa_data));
	name[माप(uaddr->sa_data)] = 0;

	वापस packet_करो_bind(sk, name, 0, pkt_sk(sk)->num);
पूर्ण

अटल पूर्णांक packet_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_ll *sll = (काष्ठा sockaddr_ll *)uaddr;
	काष्ठा sock *sk = sock->sk;

	/*
	 *	Check legality
	 */

	अगर (addr_len < माप(काष्ठा sockaddr_ll))
		वापस -EINVAL;
	अगर (sll->sll_family != AF_PACKET)
		वापस -EINVAL;

	वापस packet_करो_bind(sk, शून्य, sll->sll_अगरindex,
			      sll->sll_protocol ? : pkt_sk(sk)->num);
पूर्ण

अटल काष्ठा proto packet_proto = अणु
	.name	  = "PACKET",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा packet_sock),
पूर्ण;

/*
 *	Create a packet of type SOCK_PACKET.
 */

अटल पूर्णांक packet_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			 पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा packet_sock *po;
	__be16 proto = (__क्रमce __be16)protocol; /* weird, but करोcumented */
	पूर्णांक err;

	अगर (!ns_capable(net->user_ns, CAP_NET_RAW))
		वापस -EPERM;
	अगर (sock->type != SOCK_DGRAM && sock->type != SOCK_RAW &&
	    sock->type != SOCK_PACKET)
		वापस -ESOCKTNOSUPPORT;

	sock->state = SS_UNCONNECTED;

	err = -ENOBUFS;
	sk = sk_alloc(net, PF_PACKET, GFP_KERNEL, &packet_proto, kern);
	अगर (sk == शून्य)
		जाओ out;

	sock->ops = &packet_ops;
	अगर (sock->type == SOCK_PACKET)
		sock->ops = &packet_ops_spkt;

	sock_init_data(sock, sk);

	po = pkt_sk(sk);
	init_completion(&po->skb_completion);
	sk->sk_family = PF_PACKET;
	po->num = proto;
	po->xmit = dev_queue_xmit;

	err = packet_alloc_pending(po);
	अगर (err)
		जाओ out2;

	packet_cached_dev_reset(po);

	sk->sk_deकाष्ठा = packet_sock_deकाष्ठा;
	sk_refcnt_debug_inc(sk);

	/*
	 *	Attach a protocol block
	 */

	spin_lock_init(&po->bind_lock);
	mutex_init(&po->pg_vec_lock);
	po->rollover = शून्य;
	po->prot_hook.func = packet_rcv;

	अगर (sock->type == SOCK_PACKET)
		po->prot_hook.func = packet_rcv_spkt;

	po->prot_hook.af_packet_priv = sk;

	अगर (proto) अणु
		po->prot_hook.type = proto;
		__रेजिस्टर_prot_hook(sk);
	पूर्ण

	mutex_lock(&net->packet.sklist_lock);
	sk_add_node_tail_rcu(sk, &net->packet.sklist);
	mutex_unlock(&net->packet.sklist_lock);

	preempt_disable();
	sock_prot_inuse_add(net, &packet_proto, 1);
	preempt_enable();

	वापस 0;
out2:
	sk_मुक्त(sk);
out:
	वापस err;
पूर्ण

/*
 *	Pull a packet from our receive queue and hand it to the user.
 *	If necessary we block.
 */

अटल पूर्णांक packet_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
			  पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक copied, err;
	पूर्णांक vnet_hdr_len = 0;
	अचिन्हित पूर्णांक origlen = 0;

	err = -EINVAL;
	अगर (flags & ~(MSG_PEEK|MSG_DONTWAIT|MSG_TRUNC|MSG_CMSG_COMPAT|MSG_ERRQUEUE))
		जाओ out;

#अगर 0
	/* What error should we वापस now? EUNATTACH? */
	अगर (pkt_sk(sk)->अगरindex < 0)
		वापस -ENODEV;
#पूर्ण_अगर

	अगर (flags & MSG_ERRQUEUE) अणु
		err = sock_recv_errqueue(sk, msg, len,
					 SOL_PACKET, PACKET_TX_TIMESTAMP);
		जाओ out;
	पूर्ण

	/*
	 *	Call the generic datagram receiver. This handles all sorts
	 *	of horrible races and re-entrancy so we can क्रमget about it
	 *	in the protocol layers.
	 *
	 *	Now it will वापस ENETDOWN, अगर device have just gone करोwn,
	 *	but then it will block.
	 */

	skb = skb_recv_datagram(sk, flags, flags & MSG_DONTWAIT, &err);

	/*
	 *	An error occurred so वापस it. Because skb_recv_datagram()
	 *	handles the blocking we करोn't see and worry about blocking
	 *	retries.
	 */

	अगर (skb == शून्य)
		जाओ out;

	packet_rcv_try_clear_pressure(pkt_sk(sk));

	अगर (pkt_sk(sk)->has_vnet_hdr) अणु
		err = packet_rcv_vnet(msg, skb, &len);
		अगर (err)
			जाओ out_मुक्त;
		vnet_hdr_len = माप(काष्ठा virtio_net_hdr);
	पूर्ण

	/* You lose any data beyond the buffer you gave. If it worries
	 * a user program they can ask the device क्रम its MTU
	 * anyway.
	 */
	copied = skb->len;
	अगर (copied > len) अणु
		copied = len;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ out_मुक्त;

	अगर (sock->type != SOCK_PACKET) अणु
		काष्ठा sockaddr_ll *sll = &PACKET_SKB_CB(skb)->sa.ll;

		/* Original length was stored in sockaddr_ll fields */
		origlen = PACKET_SKB_CB(skb)->sa.origlen;
		sll->sll_family = AF_PACKET;
		sll->sll_protocol = skb->protocol;
	पूर्ण

	sock_recv_ts_and_drops(msg, sk, skb);

	अगर (msg->msg_name) अणु
		पूर्णांक copy_len;

		/* If the address length field is there to be filled
		 * in, we fill it in now.
		 */
		अगर (sock->type == SOCK_PACKET) अणु
			__sockaddr_check_size(माप(काष्ठा sockaddr_pkt));
			msg->msg_namelen = माप(काष्ठा sockaddr_pkt);
			copy_len = msg->msg_namelen;
		पूर्ण अन्यथा अणु
			काष्ठा sockaddr_ll *sll = &PACKET_SKB_CB(skb)->sa.ll;

			msg->msg_namelen = sll->sll_halen +
				दुरत्व(काष्ठा sockaddr_ll, sll_addr);
			copy_len = msg->msg_namelen;
			अगर (msg->msg_namelen < माप(काष्ठा sockaddr_ll)) अणु
				स_रखो(msg->msg_name +
				       दुरत्व(काष्ठा sockaddr_ll, sll_addr),
				       0, माप(sll->sll_addr));
				msg->msg_namelen = माप(काष्ठा sockaddr_ll);
			पूर्ण
		पूर्ण
		स_नकल(msg->msg_name, &PACKET_SKB_CB(skb)->sa, copy_len);
	पूर्ण

	अगर (pkt_sk(sk)->auxdata) अणु
		काष्ठा tpacket_auxdata aux;

		aux.tp_status = TP_STATUS_USER;
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			aux.tp_status |= TP_STATUS_CSUMNOTREADY;
		अन्यथा अगर (skb->pkt_type != PACKET_OUTGOING &&
			 (skb->ip_summed == CHECKSUM_COMPLETE ||
			  skb_csum_unnecessary(skb)))
			aux.tp_status |= TP_STATUS_CSUM_VALID;

		aux.tp_len = origlen;
		aux.tp_snaplen = skb->len;
		aux.tp_mac = 0;
		aux.tp_net = skb_network_offset(skb);
		अगर (skb_vlan_tag_present(skb)) अणु
			aux.tp_vlan_tci = skb_vlan_tag_get(skb);
			aux.tp_vlan_tpid = ntohs(skb->vlan_proto);
			aux.tp_status |= TP_STATUS_VLAN_VALID | TP_STATUS_VLAN_TPID_VALID;
		पूर्ण अन्यथा अणु
			aux.tp_vlan_tci = 0;
			aux.tp_vlan_tpid = 0;
		पूर्ण
		put_cmsg(msg, SOL_PACKET, PACKET_AUXDATA, माप(aux), &aux);
	पूर्ण

	/*
	 *	Free or वापस the buffer as appropriate. Again this
	 *	hides all the races and re-entrancy issues from us.
	 */
	err = vnet_hdr_len + ((flags&MSG_TRUNC) ? skb->len : copied);

out_मुक्त:
	skb_मुक्त_datagram(sk, skb);
out:
	वापस err;
पूर्ण

अटल पूर्णांक packet_getname_spkt(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			       पूर्णांक peer)
अणु
	काष्ठा net_device *dev;
	काष्ठा sock *sk	= sock->sk;

	अगर (peer)
		वापस -EOPNOTSUPP;

	uaddr->sa_family = AF_PACKET;
	स_रखो(uaddr->sa_data, 0, माप(uaddr->sa_data));
	rcu_पढ़ो_lock();
	dev = dev_get_by_index_rcu(sock_net(sk), READ_ONCE(pkt_sk(sk)->अगरindex));
	अगर (dev)
		strlcpy(uaddr->sa_data, dev->name, माप(uaddr->sa_data));
	rcu_पढ़ो_unlock();

	वापस माप(*uaddr);
पूर्ण

अटल पूर्णांक packet_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			  पूर्णांक peer)
अणु
	काष्ठा net_device *dev;
	काष्ठा sock *sk = sock->sk;
	काष्ठा packet_sock *po = pkt_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_ll *, sll, uaddr);
	पूर्णांक अगरindex;

	अगर (peer)
		वापस -EOPNOTSUPP;

	अगरindex = READ_ONCE(po->अगरindex);
	sll->sll_family = AF_PACKET;
	sll->sll_अगरindex = अगरindex;
	sll->sll_protocol = READ_ONCE(po->num);
	sll->sll_pkttype = 0;
	rcu_पढ़ो_lock();
	dev = dev_get_by_index_rcu(sock_net(sk), अगरindex);
	अगर (dev) अणु
		sll->sll_hatype = dev->type;
		sll->sll_halen = dev->addr_len;
		स_नकल(sll->sll_addr, dev->dev_addr, dev->addr_len);
	पूर्ण अन्यथा अणु
		sll->sll_hatype = 0;	/* Bad: we have no ARPHRD_UNSPEC */
		sll->sll_halen = 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस दुरत्व(काष्ठा sockaddr_ll, sll_addr) + sll->sll_halen;
पूर्ण

अटल पूर्णांक packet_dev_mc(काष्ठा net_device *dev, काष्ठा packet_mclist *i,
			 पूर्णांक what)
अणु
	चयन (i->type) अणु
	हाल PACKET_MR_MULTICAST:
		अगर (i->alen != dev->addr_len)
			वापस -EINVAL;
		अगर (what > 0)
			वापस dev_mc_add(dev, i->addr);
		अन्यथा
			वापस dev_mc_del(dev, i->addr);
		अवरोध;
	हाल PACKET_MR_PROMISC:
		वापस dev_set_promiscuity(dev, what);
	हाल PACKET_MR_ALLMULTI:
		वापस dev_set_allmulti(dev, what);
	हाल PACKET_MR_UNICAST:
		अगर (i->alen != dev->addr_len)
			वापस -EINVAL;
		अगर (what > 0)
			वापस dev_uc_add(dev, i->addr);
		अन्यथा
			वापस dev_uc_del(dev, i->addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम packet_dev_mclist_delete(काष्ठा net_device *dev,
				     काष्ठा packet_mclist **mlp)
अणु
	काष्ठा packet_mclist *ml;

	जबतक ((ml = *mlp) != शून्य) अणु
		अगर (ml->अगरindex == dev->अगरindex) अणु
			packet_dev_mc(dev, ml, -1);
			*mlp = ml->next;
			kमुक्त(ml);
		पूर्ण अन्यथा
			mlp = &ml->next;
	पूर्ण
पूर्ण

अटल पूर्णांक packet_mc_add(काष्ठा sock *sk, काष्ठा packet_mreq_max *mreq)
अणु
	काष्ठा packet_sock *po = pkt_sk(sk);
	काष्ठा packet_mclist *ml, *i;
	काष्ठा net_device *dev;
	पूर्णांक err;

	rtnl_lock();

	err = -ENODEV;
	dev = __dev_get_by_index(sock_net(sk), mreq->mr_अगरindex);
	अगर (!dev)
		जाओ करोne;

	err = -EINVAL;
	अगर (mreq->mr_alen > dev->addr_len)
		जाओ करोne;

	err = -ENOBUFS;
	i = kदो_स्मृति(माप(*i), GFP_KERNEL);
	अगर (i == शून्य)
		जाओ करोne;

	err = 0;
	क्रम (ml = po->mclist; ml; ml = ml->next) अणु
		अगर (ml->अगरindex == mreq->mr_अगरindex &&
		    ml->type == mreq->mr_type &&
		    ml->alen == mreq->mr_alen &&
		    स_भेद(ml->addr, mreq->mr_address, ml->alen) == 0) अणु
			ml->count++;
			/* Free the new element ... */
			kमुक्त(i);
			जाओ करोne;
		पूर्ण
	पूर्ण

	i->type = mreq->mr_type;
	i->अगरindex = mreq->mr_अगरindex;
	i->alen = mreq->mr_alen;
	स_नकल(i->addr, mreq->mr_address, i->alen);
	स_रखो(i->addr + i->alen, 0, माप(i->addr) - i->alen);
	i->count = 1;
	i->next = po->mclist;
	po->mclist = i;
	err = packet_dev_mc(dev, i, 1);
	अगर (err) अणु
		po->mclist = i->next;
		kमुक्त(i);
	पूर्ण

करोne:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक packet_mc_drop(काष्ठा sock *sk, काष्ठा packet_mreq_max *mreq)
अणु
	काष्ठा packet_mclist *ml, **mlp;

	rtnl_lock();

	क्रम (mlp = &pkt_sk(sk)->mclist; (ml = *mlp) != शून्य; mlp = &ml->next) अणु
		अगर (ml->अगरindex == mreq->mr_अगरindex &&
		    ml->type == mreq->mr_type &&
		    ml->alen == mreq->mr_alen &&
		    स_भेद(ml->addr, mreq->mr_address, ml->alen) == 0) अणु
			अगर (--ml->count == 0) अणु
				काष्ठा net_device *dev;
				*mlp = ml->next;
				dev = __dev_get_by_index(sock_net(sk), ml->अगरindex);
				अगर (dev)
					packet_dev_mc(dev, ml, -1);
				kमुक्त(ml);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल व्योम packet_flush_mclist(काष्ठा sock *sk)
अणु
	काष्ठा packet_sock *po = pkt_sk(sk);
	काष्ठा packet_mclist *ml;

	अगर (!po->mclist)
		वापस;

	rtnl_lock();
	जबतक ((ml = po->mclist) != शून्य) अणु
		काष्ठा net_device *dev;

		po->mclist = ml->next;
		dev = __dev_get_by_index(sock_net(sk), ml->अगरindex);
		अगर (dev != शून्य)
			packet_dev_mc(dev, ml, -1);
		kमुक्त(ml);
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल पूर्णांक
packet_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		  अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा packet_sock *po = pkt_sk(sk);
	पूर्णांक ret;

	अगर (level != SOL_PACKET)
		वापस -ENOPROTOOPT;

	चयन (optname) अणु
	हाल PACKET_ADD_MEMBERSHIP:
	हाल PACKET_DROP_MEMBERSHIP:
	अणु
		काष्ठा packet_mreq_max mreq;
		पूर्णांक len = optlen;
		स_रखो(&mreq, 0, माप(mreq));
		अगर (len < माप(काष्ठा packet_mreq))
			वापस -EINVAL;
		अगर (len > माप(mreq))
			len = माप(mreq);
		अगर (copy_from_sockptr(&mreq, optval, len))
			वापस -EFAULT;
		अगर (len < (mreq.mr_alen + दुरत्व(काष्ठा packet_mreq, mr_address)))
			वापस -EINVAL;
		अगर (optname == PACKET_ADD_MEMBERSHIP)
			ret = packet_mc_add(sk, &mreq);
		अन्यथा
			ret = packet_mc_drop(sk, &mreq);
		वापस ret;
	पूर्ण

	हाल PACKET_RX_RING:
	हाल PACKET_TX_RING:
	अणु
		जोड़ tpacket_req_u req_u;
		पूर्णांक len;

		lock_sock(sk);
		चयन (po->tp_version) अणु
		हाल TPACKET_V1:
		हाल TPACKET_V2:
			len = माप(req_u.req);
			अवरोध;
		हाल TPACKET_V3:
		शेष:
			len = माप(req_u.req3);
			अवरोध;
		पूर्ण
		अगर (optlen < len) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (copy_from_sockptr(&req_u.req, optval, len))
				ret = -EFAULT;
			अन्यथा
				ret = packet_set_ring(sk, &req_u, 0,
						    optname == PACKET_TX_RING);
		पूर्ण
		release_sock(sk);
		वापस ret;
	पूर्ण
	हाल PACKET_COPY_THRESH:
	अणु
		पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		pkt_sk(sk)->copy_thresh = val;
		वापस 0;
	पूर्ण
	हाल PACKET_VERSION:
	अणु
		पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;
		चयन (val) अणु
		हाल TPACKET_V1:
		हाल TPACKET_V2:
		हाल TPACKET_V3:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		lock_sock(sk);
		अगर (po->rx_ring.pg_vec || po->tx_ring.pg_vec) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			po->tp_version = val;
			ret = 0;
		पूर्ण
		release_sock(sk);
		वापस ret;
	पूर्ण
	हाल PACKET_RESERVE:
	अणु
		अचिन्हित पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;
		अगर (val > पूर्णांक_उच्च)
			वापस -EINVAL;
		lock_sock(sk);
		अगर (po->rx_ring.pg_vec || po->tx_ring.pg_vec) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			po->tp_reserve = val;
			ret = 0;
		पूर्ण
		release_sock(sk);
		वापस ret;
	पूर्ण
	हाल PACKET_LOSS:
	अणु
		अचिन्हित पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		lock_sock(sk);
		अगर (po->rx_ring.pg_vec || po->tx_ring.pg_vec) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			po->tp_loss = !!val;
			ret = 0;
		पूर्ण
		release_sock(sk);
		वापस ret;
	पूर्ण
	हाल PACKET_AUXDATA:
	अणु
		पूर्णांक val;

		अगर (optlen < माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		lock_sock(sk);
		po->auxdata = !!val;
		release_sock(sk);
		वापस 0;
	पूर्ण
	हाल PACKET_ORIGDEV:
	अणु
		पूर्णांक val;

		अगर (optlen < माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		lock_sock(sk);
		po->origdev = !!val;
		release_sock(sk);
		वापस 0;
	पूर्ण
	हाल PACKET_VNET_HDR:
	अणु
		पूर्णांक val;

		अगर (sock->type != SOCK_RAW)
			वापस -EINVAL;
		अगर (optlen < माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		lock_sock(sk);
		अगर (po->rx_ring.pg_vec || po->tx_ring.pg_vec) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			po->has_vnet_hdr = !!val;
			ret = 0;
		पूर्ण
		release_sock(sk);
		वापस ret;
	पूर्ण
	हाल PACKET_TIMESTAMP:
	अणु
		पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		po->tp_tstamp = val;
		वापस 0;
	पूर्ण
	हाल PACKET_FANOUT:
	अणु
		काष्ठा fanout_args args = अणु 0 पूर्ण;

		अगर (optlen != माप(पूर्णांक) && optlen != माप(args))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&args, optval, optlen))
			वापस -EFAULT;

		वापस fanout_add(sk, &args);
	पूर्ण
	हाल PACKET_FANOUT_DATA:
	अणु
		अगर (!po->fanout)
			वापस -EINVAL;

		वापस fanout_set_data(po, optval, optlen);
	पूर्ण
	हाल PACKET_IGNORE_OUTGOING:
	अणु
		पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;
		अगर (val < 0 || val > 1)
			वापस -EINVAL;

		po->prot_hook.ignore_outgoing = !!val;
		वापस 0;
	पूर्ण
	हाल PACKET_TX_HAS_OFF:
	अणु
		अचिन्हित पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		lock_sock(sk);
		अगर (po->rx_ring.pg_vec || po->tx_ring.pg_vec) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			po->tp_tx_has_off = !!val;
			ret = 0;
		पूर्ण
		release_sock(sk);
		वापस 0;
	पूर्ण
	हाल PACKET_QDISC_BYPASS:
	अणु
		पूर्णांक val;

		अगर (optlen != माप(val))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&val, optval, माप(val)))
			वापस -EFAULT;

		po->xmit = val ? packet_direct_xmit : dev_queue_xmit;
		वापस 0;
	पूर्ण
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
पूर्ण

अटल पूर्णांक packet_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			     अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक len;
	पूर्णांक val, lv = माप(val);
	काष्ठा sock *sk = sock->sk;
	काष्ठा packet_sock *po = pkt_sk(sk);
	व्योम *data = &val;
	जोड़ tpacket_stats_u st;
	काष्ठा tpacket_rollover_stats rstats;
	पूर्णांक drops;

	अगर (level != SOL_PACKET)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल PACKET_STATISTICS:
		spin_lock_bh(&sk->sk_receive_queue.lock);
		स_नकल(&st, &po->stats, माप(st));
		स_रखो(&po->stats, 0, माप(po->stats));
		spin_unlock_bh(&sk->sk_receive_queue.lock);
		drops = atomic_xchg(&po->tp_drops, 0);

		अगर (po->tp_version == TPACKET_V3) अणु
			lv = माप(काष्ठा tpacket_stats_v3);
			st.stats3.tp_drops = drops;
			st.stats3.tp_packets += drops;
			data = &st.stats3;
		पूर्ण अन्यथा अणु
			lv = माप(काष्ठा tpacket_stats);
			st.stats1.tp_drops = drops;
			st.stats1.tp_packets += drops;
			data = &st.stats1;
		पूर्ण

		अवरोध;
	हाल PACKET_AUXDATA:
		val = po->auxdata;
		अवरोध;
	हाल PACKET_ORIGDEV:
		val = po->origdev;
		अवरोध;
	हाल PACKET_VNET_HDR:
		val = po->has_vnet_hdr;
		अवरोध;
	हाल PACKET_VERSION:
		val = po->tp_version;
		अवरोध;
	हाल PACKET_HDRLEN:
		अगर (len > माप(पूर्णांक))
			len = माप(पूर्णांक);
		अगर (len < माप(पूर्णांक))
			वापस -EINVAL;
		अगर (copy_from_user(&val, optval, len))
			वापस -EFAULT;
		चयन (val) अणु
		हाल TPACKET_V1:
			val = माप(काष्ठा tpacket_hdr);
			अवरोध;
		हाल TPACKET_V2:
			val = माप(काष्ठा tpacket2_hdr);
			अवरोध;
		हाल TPACKET_V3:
			val = माप(काष्ठा tpacket3_hdr);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PACKET_RESERVE:
		val = po->tp_reserve;
		अवरोध;
	हाल PACKET_LOSS:
		val = po->tp_loss;
		अवरोध;
	हाल PACKET_TIMESTAMP:
		val = po->tp_tstamp;
		अवरोध;
	हाल PACKET_FANOUT:
		val = (po->fanout ?
		       ((u32)po->fanout->id |
			((u32)po->fanout->type << 16) |
			((u32)po->fanout->flags << 24)) :
		       0);
		अवरोध;
	हाल PACKET_IGNORE_OUTGOING:
		val = po->prot_hook.ignore_outgoing;
		अवरोध;
	हाल PACKET_ROLLOVER_STATS:
		अगर (!po->rollover)
			वापस -EINVAL;
		rstats.tp_all = atomic_दीर्घ_पढ़ो(&po->rollover->num);
		rstats.tp_huge = atomic_दीर्घ_पढ़ो(&po->rollover->num_huge);
		rstats.tp_failed = atomic_दीर्घ_पढ़ो(&po->rollover->num_failed);
		data = &rstats;
		lv = माप(rstats);
		अवरोध;
	हाल PACKET_TX_HAS_OFF:
		val = po->tp_tx_has_off;
		अवरोध;
	हाल PACKET_QDISC_BYPASS:
		val = packet_use_direct_xmit(po);
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (len > lv)
		len = lv;
	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, data, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक packet_notअगरier(काष्ठा notअगरier_block *this,
			   अचिन्हित दीर्घ msg, व्योम *ptr)
अणु
	काष्ठा sock *sk;
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);

	rcu_पढ़ो_lock();
	sk_क्रम_each_rcu(sk, &net->packet.sklist) अणु
		काष्ठा packet_sock *po = pkt_sk(sk);

		चयन (msg) अणु
		हाल NETDEV_UNREGISTER:
			अगर (po->mclist)
				packet_dev_mclist_delete(dev, &po->mclist);
			fallthrough;

		हाल NETDEV_DOWN:
			अगर (dev->अगरindex == po->अगरindex) अणु
				spin_lock(&po->bind_lock);
				अगर (po->running) अणु
					__unरेजिस्टर_prot_hook(sk, false);
					sk->sk_err = ENETDOWN;
					अगर (!sock_flag(sk, SOCK_DEAD))
						sk->sk_error_report(sk);
				पूर्ण
				अगर (msg == NETDEV_UNREGISTER) अणु
					packet_cached_dev_reset(po);
					WRITE_ONCE(po->अगरindex, -1);
					अगर (po->prot_hook.dev)
						dev_put(po->prot_hook.dev);
					po->prot_hook.dev = शून्य;
				पूर्ण
				spin_unlock(&po->bind_lock);
			पूर्ण
			अवरोध;
		हाल NETDEV_UP:
			अगर (dev->अगरindex == po->अगरindex) अणु
				spin_lock(&po->bind_lock);
				अगर (po->num)
					रेजिस्टर_prot_hook(sk);
				spin_unlock(&po->bind_lock);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस NOTIFY_DONE;
पूर्ण


अटल पूर्णांक packet_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;

	चयन (cmd) अणु
	हाल SIOCOUTQ:
	अणु
		पूर्णांक amount = sk_wmem_alloc_get(sk);

		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण
	हाल SIOCINQ:
	अणु
		काष्ठा sk_buff *skb;
		पूर्णांक amount = 0;

		spin_lock_bh(&sk->sk_receive_queue.lock);
		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb)
			amount = skb->len;
		spin_unlock_bh(&sk->sk_receive_queue.lock);
		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण
#अगर_घोषित CONFIG_INET
	हाल SIOCADDRT:
	हाल SIOCDELRT:
	हाल SIOCDARP:
	हाल SIOCGARP:
	हाल SIOCSARP:
	हाल SIOCGIFADDR:
	हाल SIOCSIFADDR:
	हाल SIOCGIFBRDADDR:
	हाल SIOCSIFBRDADDR:
	हाल SIOCGIFNETMASK:
	हाल SIOCSIFNETMASK:
	हाल SIOCGIFDSTADDR:
	हाल SIOCSIFDSTADDR:
	हाल SIOCSIFFLAGS:
		वापस inet_dgram_ops.ioctl(sock, cmd, arg);
#पूर्ण_अगर

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

अटल __poll_t packet_poll(काष्ठा file *file, काष्ठा socket *sock,
				poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा packet_sock *po = pkt_sk(sk);
	__poll_t mask = datagram_poll(file, sock, रुको);

	spin_lock_bh(&sk->sk_receive_queue.lock);
	अगर (po->rx_ring.pg_vec) अणु
		अगर (!packet_previous_rx_frame(po, &po->rx_ring,
			TP_STATUS_KERNEL))
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण
	packet_rcv_try_clear_pressure(po);
	spin_unlock_bh(&sk->sk_receive_queue.lock);
	spin_lock_bh(&sk->sk_ग_लिखो_queue.lock);
	अगर (po->tx_ring.pg_vec) अणु
		अगर (packet_current_frame(po, &po->tx_ring, TP_STATUS_AVAILABLE))
			mask |= EPOLLOUT | EPOLLWRNORM;
	पूर्ण
	spin_unlock_bh(&sk->sk_ग_लिखो_queue.lock);
	वापस mask;
पूर्ण


/* Dirty? Well, I still did not learn better way to account
 * क्रम user mmaps.
 */

अटल व्योम packet_mm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा socket *sock = file->निजी_data;
	काष्ठा sock *sk = sock->sk;

	अगर (sk)
		atomic_inc(&pkt_sk(sk)->mapped);
पूर्ण

अटल व्योम packet_mm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा file *file = vma->vm_file;
	काष्ठा socket *sock = file->निजी_data;
	काष्ठा sock *sk = sock->sk;

	अगर (sk)
		atomic_dec(&pkt_sk(sk)->mapped);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा packet_mmap_ops = अणु
	.खोलो	=	packet_mm_खोलो,
	.बंद	=	packet_mm_बंद,
पूर्ण;

अटल व्योम मुक्त_pg_vec(काष्ठा pgv *pg_vec, अचिन्हित पूर्णांक order,
			अचिन्हित पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (likely(pg_vec[i].buffer)) अणु
			अगर (is_vदो_स्मृति_addr(pg_vec[i].buffer))
				vमुक्त(pg_vec[i].buffer);
			अन्यथा
				मुक्त_pages((अचिन्हित दीर्घ)pg_vec[i].buffer,
					   order);
			pg_vec[i].buffer = शून्य;
		पूर्ण
	पूर्ण
	kमुक्त(pg_vec);
पूर्ण

अटल अक्षर *alloc_one_pg_vec_page(अचिन्हित दीर्घ order)
अणु
	अक्षर *buffer;
	gfp_t gfp_flags = GFP_KERNEL | __GFP_COMP |
			  __GFP_ZERO | __GFP_NOWARN | __GFP_NORETRY;

	buffer = (अक्षर *) __get_मुक्त_pages(gfp_flags, order);
	अगर (buffer)
		वापस buffer;

	/* __get_मुक्त_pages failed, fall back to vदो_स्मृति */
	buffer = vzalloc(array_size((1 << order), PAGE_SIZE));
	अगर (buffer)
		वापस buffer;

	/* vदो_स्मृति failed, lets dig पूर्णांकo swap here */
	gfp_flags &= ~__GFP_NORETRY;
	buffer = (अक्षर *) __get_मुक्त_pages(gfp_flags, order);
	अगर (buffer)
		वापस buffer;

	/* complete and utter failure */
	वापस शून्य;
पूर्ण

अटल काष्ठा pgv *alloc_pg_vec(काष्ठा tpacket_req *req, पूर्णांक order)
अणु
	अचिन्हित पूर्णांक block_nr = req->tp_block_nr;
	काष्ठा pgv *pg_vec;
	पूर्णांक i;

	pg_vec = kसुस्मृति(block_nr, माप(काष्ठा pgv), GFP_KERNEL | __GFP_NOWARN);
	अगर (unlikely(!pg_vec))
		जाओ out;

	क्रम (i = 0; i < block_nr; i++) अणु
		pg_vec[i].buffer = alloc_one_pg_vec_page(order);
		अगर (unlikely(!pg_vec[i].buffer))
			जाओ out_मुक्त_pgvec;
	पूर्ण

out:
	वापस pg_vec;

out_मुक्त_pgvec:
	मुक्त_pg_vec(pg_vec, order, block_nr);
	pg_vec = शून्य;
	जाओ out;
पूर्ण

अटल पूर्णांक packet_set_ring(काष्ठा sock *sk, जोड़ tpacket_req_u *req_u,
		पूर्णांक closing, पूर्णांक tx_ring)
अणु
	काष्ठा pgv *pg_vec = शून्य;
	काष्ठा packet_sock *po = pkt_sk(sk);
	अचिन्हित दीर्घ *rx_owner_map = शून्य;
	पूर्णांक was_running, order = 0;
	काष्ठा packet_ring_buffer *rb;
	काष्ठा sk_buff_head *rb_queue;
	__be16 num;
	पूर्णांक err;
	/* Added to aव्योम minimal code churn */
	काष्ठा tpacket_req *req = &req_u->req;

	rb = tx_ring ? &po->tx_ring : &po->rx_ring;
	rb_queue = tx_ring ? &sk->sk_ग_लिखो_queue : &sk->sk_receive_queue;

	err = -EBUSY;
	अगर (!closing) अणु
		अगर (atomic_पढ़ो(&po->mapped))
			जाओ out;
		अगर (packet_पढ़ो_pending(rb))
			जाओ out;
	पूर्ण

	अगर (req->tp_block_nr) अणु
		अचिन्हित पूर्णांक min_frame_size;

		/* Sanity tests and some calculations */
		err = -EBUSY;
		अगर (unlikely(rb->pg_vec))
			जाओ out;

		चयन (po->tp_version) अणु
		हाल TPACKET_V1:
			po->tp_hdrlen = TPACKET_HDRLEN;
			अवरोध;
		हाल TPACKET_V2:
			po->tp_hdrlen = TPACKET2_HDRLEN;
			अवरोध;
		हाल TPACKET_V3:
			po->tp_hdrlen = TPACKET3_HDRLEN;
			अवरोध;
		पूर्ण

		err = -EINVAL;
		अगर (unlikely((पूर्णांक)req->tp_block_size <= 0))
			जाओ out;
		अगर (unlikely(!PAGE_ALIGNED(req->tp_block_size)))
			जाओ out;
		min_frame_size = po->tp_hdrlen + po->tp_reserve;
		अगर (po->tp_version >= TPACKET_V3 &&
		    req->tp_block_size <
		    BLK_PLUS_PRIV((u64)req_u->req3.tp_माप_priv) + min_frame_size)
			जाओ out;
		अगर (unlikely(req->tp_frame_size < min_frame_size))
			जाओ out;
		अगर (unlikely(req->tp_frame_size & (TPACKET_ALIGNMENT - 1)))
			जाओ out;

		rb->frames_per_block = req->tp_block_size / req->tp_frame_size;
		अगर (unlikely(rb->frames_per_block == 0))
			जाओ out;
		अगर (unlikely(rb->frames_per_block > अच_पूर्णांक_उच्च / req->tp_block_nr))
			जाओ out;
		अगर (unlikely((rb->frames_per_block * req->tp_block_nr) !=
					req->tp_frame_nr))
			जाओ out;

		err = -ENOMEM;
		order = get_order(req->tp_block_size);
		pg_vec = alloc_pg_vec(req, order);
		अगर (unlikely(!pg_vec))
			जाओ out;
		चयन (po->tp_version) अणु
		हाल TPACKET_V3:
			/* Block transmit is not supported yet */
			अगर (!tx_ring) अणु
				init_prb_bdqc(po, rb, pg_vec, req_u);
			पूर्ण अन्यथा अणु
				काष्ठा tpacket_req3 *req3 = &req_u->req3;

				अगर (req3->tp_retire_blk_tov ||
				    req3->tp_माप_priv ||
				    req3->tp_feature_req_word) अणु
					err = -EINVAL;
					जाओ out_मुक्त_pg_vec;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अगर (!tx_ring) अणु
				rx_owner_map = biपंचांगap_alloc(req->tp_frame_nr,
					GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO);
				अगर (!rx_owner_map)
					जाओ out_मुक्त_pg_vec;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	/* Done */
	अन्यथा अणु
		err = -EINVAL;
		अगर (unlikely(req->tp_frame_nr))
			जाओ out;
	पूर्ण


	/* Detach socket from network */
	spin_lock(&po->bind_lock);
	was_running = po->running;
	num = po->num;
	अगर (was_running) अणु
		WRITE_ONCE(po->num, 0);
		__unरेजिस्टर_prot_hook(sk, false);
	पूर्ण
	spin_unlock(&po->bind_lock);

	synchronize_net();

	err = -EBUSY;
	mutex_lock(&po->pg_vec_lock);
	अगर (closing || atomic_पढ़ो(&po->mapped) == 0) अणु
		err = 0;
		spin_lock_bh(&rb_queue->lock);
		swap(rb->pg_vec, pg_vec);
		अगर (po->tp_version <= TPACKET_V2)
			swap(rb->rx_owner_map, rx_owner_map);
		rb->frame_max = (req->tp_frame_nr - 1);
		rb->head = 0;
		rb->frame_size = req->tp_frame_size;
		spin_unlock_bh(&rb_queue->lock);

		swap(rb->pg_vec_order, order);
		swap(rb->pg_vec_len, req->tp_block_nr);

		rb->pg_vec_pages = req->tp_block_size/PAGE_SIZE;
		po->prot_hook.func = (po->rx_ring.pg_vec) ?
						tpacket_rcv : packet_rcv;
		skb_queue_purge(rb_queue);
		अगर (atomic_पढ़ो(&po->mapped))
			pr_err("packet_mmap: vma is busy: %d\n",
			       atomic_पढ़ो(&po->mapped));
	पूर्ण
	mutex_unlock(&po->pg_vec_lock);

	spin_lock(&po->bind_lock);
	अगर (was_running) अणु
		WRITE_ONCE(po->num, num);
		रेजिस्टर_prot_hook(sk);
	पूर्ण
	spin_unlock(&po->bind_lock);
	अगर (pg_vec && (po->tp_version > TPACKET_V2)) अणु
		/* Because we करोn't support block-based V3 on tx-ring */
		अगर (!tx_ring)
			prb_shutकरोwn_retire_blk_समयr(po, rb_queue);
	पूर्ण

out_मुक्त_pg_vec:
	biपंचांगap_मुक्त(rx_owner_map);
	अगर (pg_vec)
		मुक्त_pg_vec(pg_vec, order, req->tp_block_nr);
out:
	वापस err;
पूर्ण

अटल पूर्णांक packet_mmap(काष्ठा file *file, काष्ठा socket *sock,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा packet_sock *po = pkt_sk(sk);
	अचिन्हित दीर्घ size, expected_size;
	काष्ठा packet_ring_buffer *rb;
	अचिन्हित दीर्घ start;
	पूर्णांक err = -EINVAL;
	पूर्णांक i;

	अगर (vma->vm_pgoff)
		वापस -EINVAL;

	mutex_lock(&po->pg_vec_lock);

	expected_size = 0;
	क्रम (rb = &po->rx_ring; rb <= &po->tx_ring; rb++) अणु
		अगर (rb->pg_vec) अणु
			expected_size += rb->pg_vec_len
						* rb->pg_vec_pages
						* PAGE_SIZE;
		पूर्ण
	पूर्ण

	अगर (expected_size == 0)
		जाओ out;

	size = vma->vm_end - vma->vm_start;
	अगर (size != expected_size)
		जाओ out;

	start = vma->vm_start;
	क्रम (rb = &po->rx_ring; rb <= &po->tx_ring; rb++) अणु
		अगर (rb->pg_vec == शून्य)
			जारी;

		क्रम (i = 0; i < rb->pg_vec_len; i++) अणु
			काष्ठा page *page;
			व्योम *kaddr = rb->pg_vec[i].buffer;
			पूर्णांक pg_num;

			क्रम (pg_num = 0; pg_num < rb->pg_vec_pages; pg_num++) अणु
				page = pgv_to_page(kaddr);
				err = vm_insert_page(vma, start, page);
				अगर (unlikely(err))
					जाओ out;
				start += PAGE_SIZE;
				kaddr += PAGE_SIZE;
			पूर्ण
		पूर्ण
	पूर्ण

	atomic_inc(&po->mapped);
	vma->vm_ops = &packet_mmap_ops;
	err = 0;

out:
	mutex_unlock(&po->pg_vec_lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proto_ops packet_ops_spkt = अणु
	.family =	PF_PACKET,
	.owner =	THIS_MODULE,
	.release =	packet_release,
	.bind =		packet_bind_spkt,
	.connect =	sock_no_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	packet_getname_spkt,
	.poll =		datagram_poll,
	.ioctl =	packet_ioctl,
	.gettstamp =	sock_gettstamp,
	.listen =	sock_no_listen,
	.shutकरोwn =	sock_no_shutकरोwn,
	.sendmsg =	packet_sendmsg_spkt,
	.recvmsg =	packet_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;

अटल स्थिर काष्ठा proto_ops packet_ops = अणु
	.family =	PF_PACKET,
	.owner =	THIS_MODULE,
	.release =	packet_release,
	.bind =		packet_bind,
	.connect =	sock_no_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	packet_getname,
	.poll =		packet_poll,
	.ioctl =	packet_ioctl,
	.gettstamp =	sock_gettstamp,
	.listen =	sock_no_listen,
	.shutकरोwn =	sock_no_shutकरोwn,
	.setsockopt =	packet_setsockopt,
	.माला_लोockopt =	packet_माला_लोockopt,
	.sendmsg =	packet_sendmsg,
	.recvmsg =	packet_recvmsg,
	.mmap =		packet_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;

अटल स्थिर काष्ठा net_proto_family packet_family_ops = अणु
	.family =	PF_PACKET,
	.create =	packet_create,
	.owner	=	THIS_MODULE,
पूर्ण;

अटल काष्ठा notअगरier_block packet_netdev_notअगरier = अणु
	.notअगरier_call =	packet_notअगरier,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS

अटल व्योम *packet_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा net *net = seq_file_net(seq);

	rcu_पढ़ो_lock();
	वापस seq_hlist_start_head_rcu(&net->packet.sklist, *pos);
पूर्ण

अटल व्योम *packet_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	वापस seq_hlist_next_rcu(v, &net->packet.sklist, pos);
पूर्ण

अटल व्योम packet_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक packet_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_म_लिखो(seq,
			   "%*sRefCnt Type Proto  Iface R Rmem   User   Inode\n",
			   IS_ENABLED(CONFIG_64BIT) ? -17 : -9, "sk");
	अन्यथा अणु
		काष्ठा sock *s = sk_entry(v);
		स्थिर काष्ठा packet_sock *po = pkt_sk(s);

		seq_म_लिखो(seq,
			   "%pK %-6d %-4d %04x   %-5d %1d %-6u %-6u %-6lu\n",
			   s,
			   refcount_पढ़ो(&s->sk_refcnt),
			   s->sk_type,
			   ntohs(READ_ONCE(po->num)),
			   READ_ONCE(po->अगरindex),
			   po->running,
			   atomic_पढ़ो(&s->sk_rmem_alloc),
			   from_kuid_munged(seq_user_ns(seq), sock_i_uid(s)),
			   sock_i_ino(s));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations packet_seq_ops = अणु
	.start	= packet_seq_start,
	.next	= packet_seq_next,
	.stop	= packet_seq_stop,
	.show	= packet_seq_show,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __net_init packet_net_init(काष्ठा net *net)
अणु
	mutex_init(&net->packet.sklist_lock);
	INIT_HLIST_HEAD(&net->packet.sklist);

#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_net("packet", 0, net->proc_net, &packet_seq_ops,
			माप(काष्ठा seq_net_निजी)))
		वापस -ENOMEM;
#पूर्ण_अगर /* CONFIG_PROC_FS */

	वापस 0;
पूर्ण

अटल व्योम __net_निकास packet_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("packet", net->proc_net);
	WARN_ON_ONCE(!hlist_empty(&net->packet.sklist));
पूर्ण

अटल काष्ठा pernet_operations packet_net_ops = अणु
	.init = packet_net_init,
	.निकास = packet_net_निकास,
पूर्ण;


अटल व्योम __निकास packet_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&packet_netdev_notअगरier);
	unरेजिस्टर_pernet_subsys(&packet_net_ops);
	sock_unरेजिस्टर(PF_PACKET);
	proto_unरेजिस्टर(&packet_proto);
पूर्ण

अटल पूर्णांक __init packet_init(व्योम)
अणु
	पूर्णांक rc;

	rc = proto_रेजिस्टर(&packet_proto, 0);
	अगर (rc)
		जाओ out;
	rc = sock_रेजिस्टर(&packet_family_ops);
	अगर (rc)
		जाओ out_proto;
	rc = रेजिस्टर_pernet_subsys(&packet_net_ops);
	अगर (rc)
		जाओ out_sock;
	rc = रेजिस्टर_netdevice_notअगरier(&packet_netdev_notअगरier);
	अगर (rc)
		जाओ out_pernet;

	वापस 0;

out_pernet:
	unरेजिस्टर_pernet_subsys(&packet_net_ops);
out_sock:
	sock_unरेजिस्टर(PF_PACKET);
out_proto:
	proto_unरेजिस्टर(&packet_proto);
out:
	वापस rc;
पूर्ण

module_init(packet_init);
module_निकास(packet_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_PACKET);
