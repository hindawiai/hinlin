<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2010 Cavium Networks
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/dst.h>
#अगर_घोषित CONFIG_XFRM
#समावेश <linux/xfrm.h>
#समावेश <net/xfrm.h>
#पूर्ण_अगर /* CONFIG_XFRM */

#समावेश <linux/atomic.h>
#समावेश <net/sch_generic.h>

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-defines.h"
#समावेश "ethernet-tx.h"
#समावेश "ethernet-util.h"

#घोषणा CVM_OCT_SKB_CB(skb)	((u64 *)((skb)->cb))

/*
 * You can define GET_SKBUFF_QOS() to override how the skbuff output
 * function determines which output queue is used. The शेष
 * implementation always uses the base queue क्रम the port. If, क्रम
 * example, you wanted to use the skb->priority field, define
 * GET_SKBUFF_QOS as: #घोषणा GET_SKBUFF_QOS(skb) ((skb)->priority)
 */
#अगर_अघोषित GET_SKBUFF_QOS
#घोषणा GET_SKBUFF_QOS(skb) 0
#पूर्ण_अगर

अटल व्योम cvm_oct_tx_करो_cleanup(अचिन्हित दीर्घ arg);
अटल DECLARE_TASKLET_OLD(cvm_oct_tx_cleanup_tasklet, cvm_oct_tx_करो_cleanup);

/* Maximum number of SKBs to try to मुक्त per xmit packet. */
#घोषणा MAX_SKB_TO_FREE (MAX_OUT_QUEUE_DEPTH * 2)

अटल अंतरभूत पूर्णांक cvm_oct_adjust_skb_to_मुक्त(पूर्णांक skb_to_मुक्त, पूर्णांक fau)
अणु
	पूर्णांक unकरो;

	unकरो = skb_to_मुक्त > 0 ? MAX_SKB_TO_FREE : skb_to_मुक्त +
						   MAX_SKB_TO_FREE;
	अगर (unकरो > 0)
		cvmx_fau_atomic_add32(fau, -unकरो);
	skb_to_मुक्त = -skb_to_मुक्त > MAX_SKB_TO_FREE ? MAX_SKB_TO_FREE :
						       -skb_to_मुक्त;
	वापस skb_to_मुक्त;
पूर्ण

अटल व्योम cvm_oct_kick_tx_poll_watchकरोg(व्योम)
अणु
	जोड़ cvmx_ciu_timx ciu_timx;

	ciu_timx.u64 = 0;
	ciu_timx.s.one_shot = 1;
	ciu_timx.s.len = cvm_oct_tx_poll_पूर्णांकerval;
	cvmx_ग_लिखो_csr(CVMX_CIU_TIMX(1), ciu_timx.u64);
पूर्ण

अटल व्योम cvm_oct_मुक्त_tx_skbs(काष्ठा net_device *dev)
अणु
	पूर्णांक skb_to_मुक्त;
	पूर्णांक qos, queues_per_port;
	पूर्णांक total_मुक्तd = 0;
	पूर्णांक total_reमुख्यing = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);

	queues_per_port = cvmx_pko_get_num_queues(priv->port);
	/* Drain any pending packets in the मुक्त list */
	क्रम (qos = 0; qos < queues_per_port; qos++) अणु
		अगर (skb_queue_len(&priv->tx_मुक्त_list[qos]) == 0)
			जारी;
		skb_to_मुक्त = cvmx_fau_fetch_and_add32(priv->fau + qos * 4,
						       MAX_SKB_TO_FREE);
		skb_to_मुक्त = cvm_oct_adjust_skb_to_मुक्त(skb_to_मुक्त,
							 priv->fau + qos * 4);
		total_मुक्तd += skb_to_मुक्त;
		अगर (skb_to_मुक्त > 0) अणु
			काष्ठा sk_buff *to_मुक्त_list = शून्य;

			spin_lock_irqsave(&priv->tx_मुक्त_list[qos].lock, flags);
			जबतक (skb_to_मुक्त > 0) अणु
				काष्ठा sk_buff *t;

				t = __skb_dequeue(&priv->tx_मुक्त_list[qos]);
				t->next = to_मुक्त_list;
				to_मुक्त_list = t;
				skb_to_मुक्त--;
			पूर्ण
			spin_unlock_irqrestore(&priv->tx_मुक्त_list[qos].lock,
					       flags);
			/* Do the actual मुक्तing outside of the lock. */
			जबतक (to_मुक्त_list) अणु
				काष्ठा sk_buff *t = to_मुक्त_list;

				to_मुक्त_list = to_मुक्त_list->next;
				dev_kमुक्त_skb_any(t);
			पूर्ण
		पूर्ण
		total_reमुख्यing += skb_queue_len(&priv->tx_मुक्त_list[qos]);
	पूर्ण
	अगर (total_reमुख्यing < MAX_OUT_QUEUE_DEPTH && netअगर_queue_stopped(dev))
		netअगर_wake_queue(dev);
	अगर (total_reमुख्यing)
		cvm_oct_kick_tx_poll_watchकरोg();
पूर्ण

/**
 * cvm_oct_xmit - transmit a packet
 * @skb:    Packet to send
 * @dev:    Device info काष्ठाure
 *
 * Returns Always वापसs NETDEV_TX_OK
 */
पूर्णांक cvm_oct_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	जोड़ cvmx_pko_command_word0 pko_command;
	जोड़ cvmx_buf_ptr hw_buffer;
	u64 old_scratch;
	u64 old_scratch2;
	पूर्णांक qos;
	पूर्णांक i;
	क्रमागत अणुQUEUE_CORE, QUEUE_HW, QUEUE_DROPपूर्ण queue_type;
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	काष्ठा sk_buff *to_मुक्त_list;
	पूर्णांक skb_to_मुक्त;
	पूर्णांक buffers_to_मुक्त;
	u32 total_to_clean;
	अचिन्हित दीर्घ flags;
#अगर REUSE_SKBUFFS_WITHOUT_FREE
	अचिन्हित अक्षर *fpa_head;
#पूर्ण_अगर

	/*
	 * Prefetch the निजी data काष्ठाure.  It is larger than the
	 * one cache line.
	 */
	prefetch(priv);

	/*
	 * The check on CVMX_PKO_QUEUES_PER_PORT_* is deचिन्हित to
	 * completely हटाओ "qos" in the event neither पूर्णांकerface
	 * supports multiple queues per port.
	 */
	अगर ((CVMX_PKO_QUEUES_PER_PORT_INTERFACE0 > 1) ||
	    (CVMX_PKO_QUEUES_PER_PORT_INTERFACE1 > 1)) अणु
		qos = GET_SKBUFF_QOS(skb);
		अगर (qos <= 0)
			qos = 0;
		अन्यथा अगर (qos >= cvmx_pko_get_num_queues(priv->port))
			qos = 0;
	पूर्ण अन्यथा अणु
		qos = 0;
	पूर्ण

	अगर (USE_ASYNC_IOBDMA) अणु
		/* Save scratch in हाल userspace is using it */
		CVMX_SYNCIOBDMA;
		old_scratch = cvmx_scratch_पढ़ो64(CVMX_SCR_SCRATCH);
		old_scratch2 = cvmx_scratch_पढ़ो64(CVMX_SCR_SCRATCH + 8);

		/*
		 * Fetch and increment the number of packets to be
		 * मुक्तd.
		 */
		cvmx_fau_async_fetch_and_add32(CVMX_SCR_SCRATCH + 8,
					       FAU_NUM_PACKET_BUFFERS_TO_FREE,
					       0);
		cvmx_fau_async_fetch_and_add32(CVMX_SCR_SCRATCH,
					       priv->fau + qos * 4,
					       MAX_SKB_TO_FREE);
	पूर्ण

	/*
	 * We have space क्रम 6 segment poपूर्णांकers, If there will be more
	 * than that, we must linearize.
	 */
	अगर (unlikely(skb_shinfo(skb)->nr_frags > 5)) अणु
		अगर (unlikely(__skb_linearize(skb))) अणु
			queue_type = QUEUE_DROP;
			अगर (USE_ASYNC_IOBDMA) अणु
				/*
				 * Get the number of skbuffs in use
				 * by the hardware
				 */
				CVMX_SYNCIOBDMA;
				skb_to_मुक्त =
					cvmx_scratch_पढ़ो64(CVMX_SCR_SCRATCH);
			पूर्ण अन्यथा अणु
				/*
				 * Get the number of skbuffs in use
				 * by the hardware
				 */
				skb_to_मुक्त =
				     cvmx_fau_fetch_and_add32(priv->fau +
							      qos * 4,
							      MAX_SKB_TO_FREE);
			पूर्ण
			skb_to_मुक्त = cvm_oct_adjust_skb_to_मुक्त(skb_to_मुक्त,
								 priv->fau +
								 qos * 4);
			spin_lock_irqsave(&priv->tx_मुक्त_list[qos].lock, flags);
			जाओ skip_xmit;
		पूर्ण
	पूर्ण

	/*
	 * The CN3XXX series of parts has an errata (GMX-401) which
	 * causes the GMX block to hang अगर a collision occurs towards
	 * the end of a <68 byte packet. As a workaround क्रम this, we
	 * pad packets to be 68 bytes whenever we are in half duplex
	 * mode. We करोn't handle the हाल of having a small packet but
	 * no room to add the padding.  The kernel should always give
	 * us at least a cache line
	 */
	अगर ((skb->len < 64) && OCTEON_IS_MODEL(OCTEON_CN3XXX)) अणु
		जोड़ cvmx_gmxx_prtx_cfg gmx_prt_cfg;
		पूर्णांक पूर्णांकerface = INTERFACE(priv->port);
		पूर्णांक index = INDEX(priv->port);

		अगर (पूर्णांकerface < 2) अणु
			/* We only need to pad packet in half duplex mode */
			gmx_prt_cfg.u64 =
			    cvmx_पढ़ो_csr(CVMX_GMXX_PRTX_CFG(index, पूर्णांकerface));
			अगर (gmx_prt_cfg.s.duplex == 0) अणु
				पूर्णांक add_bytes = 64 - skb->len;

				अगर ((skb_tail_poपूर्णांकer(skb) + add_bytes) <=
				    skb_end_poपूर्णांकer(skb))
					__skb_put_zero(skb, add_bytes);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Build the PKO command */
	pko_command.u64 = 0;
#अगर_घोषित __LITTLE_ENDIAN
	pko_command.s.le = 1;
#पूर्ण_अगर
	pko_command.s.n2 = 1;	/* Don't pollute L2 with the outgoing packet */
	pko_command.s.segs = 1;
	pko_command.s.total_bytes = skb->len;
	pko_command.s.size0 = CVMX_FAU_OP_SIZE_32;
	pko_command.s.subone0 = 1;

	pko_command.s.करोntमुक्त = 1;

	/* Build the PKO buffer poपूर्णांकer */
	hw_buffer.u64 = 0;
	अगर (skb_shinfo(skb)->nr_frags == 0) अणु
		hw_buffer.s.addr = XKPHYS_TO_PHYS((uपूर्णांकptr_t)skb->data);
		hw_buffer.s.pool = 0;
		hw_buffer.s.size = skb->len;
	पूर्ण अन्यथा अणु
		hw_buffer.s.addr = XKPHYS_TO_PHYS((uपूर्णांकptr_t)skb->data);
		hw_buffer.s.pool = 0;
		hw_buffer.s.size = skb_headlen(skb);
		CVM_OCT_SKB_CB(skb)[0] = hw_buffer.u64;
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			skb_frag_t *fs = skb_shinfo(skb)->frags + i;

			hw_buffer.s.addr =
				XKPHYS_TO_PHYS((uपूर्णांकptr_t)skb_frag_address(fs));
			hw_buffer.s.size = skb_frag_size(fs);
			CVM_OCT_SKB_CB(skb)[i + 1] = hw_buffer.u64;
		पूर्ण
		hw_buffer.s.addr =
			XKPHYS_TO_PHYS((uपूर्णांकptr_t)CVM_OCT_SKB_CB(skb));
		hw_buffer.s.size = skb_shinfo(skb)->nr_frags + 1;
		pko_command.s.segs = skb_shinfo(skb)->nr_frags + 1;
		pko_command.s.gather = 1;
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण

	/*
	 * See अगर we can put this skb in the FPA pool. Any strange
	 * behavior from the Linux networking stack will most likely
	 * be caused by a bug in the following code. If some field is
	 * in use by the network stack and माला_लो carried over when a
	 * buffer is reused, bad things may happen.  If in करोubt and
	 * you करोnt need the असलolute best perक्रमmance, disable the
	 * define REUSE_SKBUFFS_WITHOUT_FREE. The reuse of buffers has
	 * shown a 25% increase in perक्रमmance under some loads.
	 */
#अगर REUSE_SKBUFFS_WITHOUT_FREE
	fpa_head = skb->head + 256 - ((अचिन्हित दीर्घ)skb->head & 0x7f);
	अगर (unlikely(skb->data < fpa_head)) अणु
		/* TX buffer beginning can't meet FPA alignment स्थिरraपूर्णांकs */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण
	अगर (unlikely
	    ((skb_end_poपूर्णांकer(skb) - fpa_head) < CVMX_FPA_PACKET_POOL_SIZE)) अणु
		/* TX buffer isn't large enough क्रम the FPA */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण
	अगर (unlikely(skb_shared(skb))) अणु
		/* TX buffer sharing data with someone अन्यथा */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण
	अगर (unlikely(skb_cloned(skb))) अणु
		/* TX buffer has been cloned */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण
	अगर (unlikely(skb_header_cloned(skb))) अणु
		/* TX buffer header has been cloned */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण
	अगर (unlikely(skb->deकाष्ठाor)) अणु
		/* TX buffer has a deकाष्ठाor */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण
	अगर (unlikely(skb_shinfo(skb)->nr_frags)) अणु
		/* TX buffer has fragments */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण
	अगर (unlikely
	    (skb->truesize !=
	     माप(*skb) + skb_end_offset(skb))) अणु
		/* TX buffer truesize has been changed */
		जाओ करोnt_put_skbuff_in_hw;
	पूर्ण

	/*
	 * We can use this buffer in the FPA.  We करोn't need the FAU
	 * update anymore
	 */
	pko_command.s.करोntमुक्त = 0;

	hw_buffer.s.back = ((अचिन्हित दीर्घ)skb->data >> 7) -
			   ((अचिन्हित दीर्घ)fpa_head >> 7);

	*(काष्ठा sk_buff **)(fpa_head - माप(व्योम *)) = skb;

	/*
	 * The skbuff will be reused without ever being मुक्तd. We must
	 * cleanup a bunch of core things.
	 */
	dst_release(skb_dst(skb));
	skb_dst_set(skb, शून्य);
	skb_ext_reset(skb);
	nf_reset_ct(skb);
	skb_reset_redirect(skb);

#अगर_घोषित CONFIG_NET_SCHED
	skb->tc_index = 0;
#पूर्ण_अगर /* CONFIG_NET_SCHED */
#पूर्ण_अगर /* REUSE_SKBUFFS_WITHOUT_FREE */

करोnt_put_skbuff_in_hw:

	/* Check अगर we can use the hardware checksumming */
	अगर ((skb->protocol == htons(ETH_P_IP)) &&
	    (ip_hdr(skb)->version == 4) &&
	    (ip_hdr(skb)->ihl == 5) &&
	    ((ip_hdr(skb)->frag_off == 0) ||
	     (ip_hdr(skb)->frag_off == htons(1 << 14))) &&
	    ((ip_hdr(skb)->protocol == IPPROTO_TCP) ||
	     (ip_hdr(skb)->protocol == IPPROTO_UDP))) अणु
		/* Use hardware checksum calc */
		pko_command.s.ipoffp1 = skb_network_offset(skb) + 1;
	पूर्ण

	अगर (USE_ASYNC_IOBDMA) अणु
		/* Get the number of skbuffs in use by the hardware */
		CVMX_SYNCIOBDMA;
		skb_to_मुक्त = cvmx_scratch_पढ़ो64(CVMX_SCR_SCRATCH);
		buffers_to_मुक्त = cvmx_scratch_पढ़ो64(CVMX_SCR_SCRATCH + 8);
	पूर्ण अन्यथा अणु
		/* Get the number of skbuffs in use by the hardware */
		skb_to_मुक्त = cvmx_fau_fetch_and_add32(priv->fau + qos * 4,
						       MAX_SKB_TO_FREE);
		buffers_to_मुक्त =
		    cvmx_fau_fetch_and_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE, 0);
	पूर्ण

	skb_to_मुक्त = cvm_oct_adjust_skb_to_मुक्त(skb_to_मुक्त,
						 priv->fau + qos * 4);

	/*
	 * If we're sending faster than the receive can मुक्त them then
	 * करोn't करो the HW मुक्त.
	 */
	अगर ((buffers_to_मुक्त < -100) && !pko_command.s.करोntमुक्त)
		pko_command.s.करोntमुक्त = 1;

	अगर (pko_command.s.करोntमुक्त) अणु
		queue_type = QUEUE_CORE;
		pko_command.s.reg0 = priv->fau + qos * 4;
	पूर्ण अन्यथा अणु
		queue_type = QUEUE_HW;
	पूर्ण
	अगर (USE_ASYNC_IOBDMA)
		cvmx_fau_async_fetch_and_add32(CVMX_SCR_SCRATCH,
					       FAU_TOTAL_TX_TO_CLEAN, 1);

	spin_lock_irqsave(&priv->tx_मुक्त_list[qos].lock, flags);

	/* Drop this packet अगर we have too many alपढ़ोy queued to the HW */
	अगर (unlikely(skb_queue_len(&priv->tx_मुक्त_list[qos]) >=
		     MAX_OUT_QUEUE_DEPTH)) अणु
		अगर (dev->tx_queue_len != 0) अणु
			/* Drop the lock when notअगरying the core.  */
			spin_unlock_irqrestore(&priv->tx_मुक्त_list[qos].lock,
					       flags);
			netअगर_stop_queue(dev);
			spin_lock_irqsave(&priv->tx_मुक्त_list[qos].lock,
					  flags);
		पूर्ण अन्यथा अणु
			/* If not using normal queueing.  */
			queue_type = QUEUE_DROP;
			जाओ skip_xmit;
		पूर्ण
	पूर्ण

	cvmx_pko_send_packet_prepare(priv->port, priv->queue + qos,
				     CVMX_PKO_LOCK_NONE);

	/* Send the packet to the output queue */
	अगर (unlikely(cvmx_pko_send_packet_finish(priv->port,
						 priv->queue + qos,
						 pko_command, hw_buffer,
						 CVMX_PKO_LOCK_NONE))) अणु
		prपूर्णांकk_ratelimited("%s: Failed to send the packet\n",
				   dev->name);
		queue_type = QUEUE_DROP;
	पूर्ण
skip_xmit:
	to_मुक्त_list = शून्य;

	चयन (queue_type) अणु
	हाल QUEUE_DROP:
		skb->next = to_मुक्त_list;
		to_मुक्त_list = skb;
		dev->stats.tx_dropped++;
		अवरोध;
	हाल QUEUE_HW:
		cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE, -1);
		अवरोध;
	हाल QUEUE_CORE:
		__skb_queue_tail(&priv->tx_मुक्त_list[qos], skb);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	जबतक (skb_to_मुक्त > 0) अणु
		काष्ठा sk_buff *t = __skb_dequeue(&priv->tx_मुक्त_list[qos]);

		t->next = to_मुक्त_list;
		to_मुक्त_list = t;
		skb_to_मुक्त--;
	पूर्ण

	spin_unlock_irqrestore(&priv->tx_मुक्त_list[qos].lock, flags);

	/* Do the actual मुक्तing outside of the lock. */
	जबतक (to_मुक्त_list) अणु
		काष्ठा sk_buff *t = to_मुक्त_list;

		to_मुक्त_list = to_मुक्त_list->next;
		dev_kमुक्त_skb_any(t);
	पूर्ण

	अगर (USE_ASYNC_IOBDMA) अणु
		CVMX_SYNCIOBDMA;
		total_to_clean = cvmx_scratch_पढ़ो64(CVMX_SCR_SCRATCH);
		/* Restore the scratch area */
		cvmx_scratch_ग_लिखो64(CVMX_SCR_SCRATCH, old_scratch);
		cvmx_scratch_ग_लिखो64(CVMX_SCR_SCRATCH + 8, old_scratch2);
	पूर्ण अन्यथा अणु
		total_to_clean =
			cvmx_fau_fetch_and_add32(FAU_TOTAL_TX_TO_CLEAN, 1);
	पूर्ण

	अगर (total_to_clean & 0x3ff) अणु
		/*
		 * Schedule the cleanup tasklet every 1024 packets क्रम
		 * the pathological हाल of high traffic on one port
		 * delaying clean up of packets on a dअगरferent port
		 * that is blocked रुकोing क्रम the cleanup.
		 */
		tasklet_schedule(&cvm_oct_tx_cleanup_tasklet);
	पूर्ण

	cvm_oct_kick_tx_poll_watchकरोg();

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * cvm_oct_xmit_घात - transmit a packet to the POW
 * @skb:    Packet to send
 * @dev:    Device info काष्ठाure

 * Returns Always वापसs zero
 */
पूर्णांक cvm_oct_xmit_घात(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	व्योम *packet_buffer;
	व्योम *copy_location;

	/* Get a work queue entry */
	काष्ठा cvmx_wqe *work = cvmx_fpa_alloc(CVMX_FPA_WQE_POOL);

	अगर (unlikely(!work)) अणु
		prपूर्णांकk_ratelimited("%s: Failed to allocate a work queue entry\n",
				   dev->name);
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	/* Get a packet buffer */
	packet_buffer = cvmx_fpa_alloc(CVMX_FPA_PACKET_POOL);
	अगर (unlikely(!packet_buffer)) अणु
		prपूर्णांकk_ratelimited("%s: Failed to allocate a packet buffer\n",
				   dev->name);
		cvmx_fpa_मुक्त(work, CVMX_FPA_WQE_POOL, 1);
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	/*
	 * Calculate where we need to copy the data to. We need to
	 * leave 8 bytes क्रम a next poपूर्णांकer (unused). We also need to
	 * include any configure skip. Then we need to align the IP
	 * packet src and dest पूर्णांकo the same 64bit word. The below
	 * calculation may add a little extra, but that करोesn't
	 * hurt.
	 */
	copy_location = packet_buffer + माप(u64);
	copy_location += ((CVMX_HELPER_FIRST_MBUFF_SKIP + 7) & 0xfff8) + 6;

	/*
	 * We have to copy the packet since whoever processes this
	 * packet will मुक्त it to a hardware pool. We can't use the
	 * trick of counting outstanding packets like in
	 * cvm_oct_xmit.
	 */
	स_नकल(copy_location, skb->data, skb->len);

	/*
	 * Fill in some of the work queue fields. We may need to add
	 * more अगर the software at the other end needs them.
	 */
	अगर (!OCTEON_IS_MODEL(OCTEON_CN68XX))
		work->word0.pip.cn38xx.hw_chksum = skb->csum;
	work->word1.len = skb->len;
	cvmx_wqe_set_port(work, priv->port);
	cvmx_wqe_set_qos(work, priv->port & 0x7);
	cvmx_wqe_set_grp(work, घात_send_group);
	work->word1.tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	work->word1.tag = घात_send_group;	/* FIXME */
	/* Default to zero. Sets of zero later are commented out */
	work->word2.u64 = 0;
	work->word2.s.bufs = 1;
	work->packet_ptr.u64 = 0;
	work->packet_ptr.s.addr = cvmx_ptr_to_phys(copy_location);
	work->packet_ptr.s.pool = CVMX_FPA_PACKET_POOL;
	work->packet_ptr.s.size = CVMX_FPA_PACKET_POOL_SIZE;
	work->packet_ptr.s.back = (copy_location - packet_buffer) >> 7;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		work->word2.s.ip_offset = 14;
#अगर 0
		work->word2.s.vlan_valid = 0;	/* FIXME */
		work->word2.s.vlan_cfi = 0;	/* FIXME */
		work->word2.s.vlan_id = 0;	/* FIXME */
		work->word2.s.dec_ipcomp = 0;	/* FIXME */
#पूर्ण_अगर
		work->word2.s.tcp_or_udp =
		    (ip_hdr(skb)->protocol == IPPROTO_TCP) ||
		    (ip_hdr(skb)->protocol == IPPROTO_UDP);
#अगर 0
		/* FIXME */
		work->word2.s.dec_ipsec = 0;
		/* We only support IPv4 right now */
		work->word2.s.is_v6 = 0;
		/* Hardware would set to zero */
		work->word2.s.software = 0;
		/* No error, packet is पूर्णांकernal */
		work->word2.s.L4_error = 0;
#पूर्ण_अगर
		work->word2.s.is_frag = !((ip_hdr(skb)->frag_off == 0) ||
					  (ip_hdr(skb)->frag_off ==
					      cpu_to_be16(1 << 14)));
#अगर 0
		/* Assume Linux is sending a good packet */
		work->word2.s.IP_exc = 0;
#पूर्ण_अगर
		work->word2.s.is_bcast = (skb->pkt_type == PACKET_BROADCAST);
		work->word2.s.is_mcast = (skb->pkt_type == PACKET_MULTICAST);
#अगर 0
		/* This is an IP packet */
		work->word2.s.not_IP = 0;
		/* No error, packet is पूर्णांकernal */
		work->word2.s.rcv_error = 0;
		/* No error, packet is पूर्णांकernal */
		work->word2.s.err_code = 0;
#पूर्ण_अगर

		/*
		 * When copying the data, include 4 bytes of the
		 * ethernet header to align the same way hardware
		 * करोes.
		 */
		स_नकल(work->packet_data, skb->data + 10,
		       माप(work->packet_data));
	पूर्ण अन्यथा अणु
#अगर 0
		work->word2.snoip.vlan_valid = 0;	/* FIXME */
		work->word2.snoip.vlan_cfi = 0;	/* FIXME */
		work->word2.snoip.vlan_id = 0;	/* FIXME */
		work->word2.snoip.software = 0;	/* Hardware would set to zero */
#पूर्ण_अगर
		work->word2.snoip.is_rarp = skb->protocol == htons(ETH_P_RARP);
		work->word2.snoip.is_arp = skb->protocol == htons(ETH_P_ARP);
		work->word2.snoip.is_bcast =
		    (skb->pkt_type == PACKET_BROADCAST);
		work->word2.snoip.is_mcast =
		    (skb->pkt_type == PACKET_MULTICAST);
		work->word2.snoip.not_IP = 1;	/* IP was करोne up above */
#अगर 0
		/* No error, packet is पूर्णांकernal */
		work->word2.snoip.rcv_error = 0;
		/* No error, packet is पूर्णांकernal */
		work->word2.snoip.err_code = 0;
#पूर्ण_अगर
		स_नकल(work->packet_data, skb->data, माप(work->packet_data));
	पूर्ण

	/* Submit the packet to the POW */
	cvmx_घात_work_submit(work, work->word1.tag, work->word1.tag_type,
			     cvmx_wqe_get_qos(work), cvmx_wqe_get_grp(work));
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	dev_consume_skb_any(skb);
	वापस 0;
पूर्ण

/**
 * cvm_oct_tx_shutकरोwn_dev - मुक्त all skb that are currently queued क्रम TX.
 * @dev:    Device being shutकरोwn
 *
 */
व्योम cvm_oct_tx_shutकरोwn_dev(काष्ठा net_device *dev)
अणु
	काष्ठा octeon_ethernet *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक qos;

	क्रम (qos = 0; qos < 16; qos++) अणु
		spin_lock_irqsave(&priv->tx_मुक्त_list[qos].lock, flags);
		जबतक (skb_queue_len(&priv->tx_मुक्त_list[qos]))
			dev_kमुक्त_skb_any(__skb_dequeue
					  (&priv->tx_मुक्त_list[qos]));
		spin_unlock_irqrestore(&priv->tx_मुक्त_list[qos].lock, flags);
	पूर्ण
पूर्ण

अटल व्योम cvm_oct_tx_करो_cleanup(अचिन्हित दीर्घ arg)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < TOTAL_NUMBER_OF_PORTS; port++) अणु
		अगर (cvm_oct_device[port]) अणु
			काष्ठा net_device *dev = cvm_oct_device[port];

			cvm_oct_मुक्त_tx_skbs(dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t cvm_oct_tx_cleanup_watchकरोg(पूर्णांक cpl, व्योम *dev_id)
अणु
	/* Disable the पूर्णांकerrupt.  */
	cvmx_ग_लिखो_csr(CVMX_CIU_TIMX(1), 0);
	/* Do the work in the tasklet.  */
	tasklet_schedule(&cvm_oct_tx_cleanup_tasklet);
	वापस IRQ_HANDLED;
पूर्ण

व्योम cvm_oct_tx_initialize(व्योम)
अणु
	पूर्णांक i;

	/* Disable the पूर्णांकerrupt.  */
	cvmx_ग_लिखो_csr(CVMX_CIU_TIMX(1), 0);
	/* Register an IRQ handler to receive CIU_TIMX(1) पूर्णांकerrupts */
	i = request_irq(OCTEON_IRQ_TIMER1,
			cvm_oct_tx_cleanup_watchकरोg, 0,
			"Ethernet", cvm_oct_device);

	अगर (i)
		panic("Could not acquire Ethernet IRQ %d\n", OCTEON_IRQ_TIMER1);
पूर्ण

व्योम cvm_oct_tx_shutकरोwn(व्योम)
अणु
	/* Free the पूर्णांकerrupt handler */
	मुक्त_irq(OCTEON_IRQ_TIMER1, cvm_oct_device);
पूर्ण
