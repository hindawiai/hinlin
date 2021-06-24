<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2010 Cavium Networks
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cache.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/माला.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/dst.h>
#अगर_घोषित CONFIG_XFRM
#समावेश <linux/xfrm.h>
#समावेश <net/xfrm.h>
#पूर्ण_अगर /* CONFIG_XFRM */

#समावेश "octeon-ethernet.h"
#समावेश "ethernet-defines.h"
#समावेश "ethernet-mem.h"
#समावेश "ethernet-rx.h"
#समावेश "ethernet-util.h"

अटल atomic_t oct_rx_पढ़ोy = ATOMIC_INIT(0);

अटल काष्ठा oct_rx_group अणु
	पूर्णांक irq;
	पूर्णांक group;
	काष्ठा napi_काष्ठा napi;
पूर्ण oct_rx_group[16];

/**
 * cvm_oct_करो_पूर्णांकerrupt - पूर्णांकerrupt handler.
 * @irq: Interrupt number.
 * @napi_id: Cookie to identअगरy the NAPI instance.
 *
 * The पूर्णांकerrupt occurs whenever the POW has packets in our group.
 *
 */
अटल irqवापस_t cvm_oct_करो_पूर्णांकerrupt(पूर्णांक irq, व्योम *napi_id)
अणु
	/* Disable the IRQ and start napi_poll. */
	disable_irq_nosync(irq);
	napi_schedule(napi_id);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * cvm_oct_check_rcv_error - process receive errors
 * @work: Work queue entry poपूर्णांकing to the packet.
 *
 * Returns Non-zero अगर the packet can be dropped, zero otherwise.
 */
अटल अंतरभूत पूर्णांक cvm_oct_check_rcv_error(काष्ठा cvmx_wqe *work)
अणु
	पूर्णांक port;

	अगर (octeon_has_feature(OCTEON_FEATURE_PKND))
		port = work->word0.pip.cn68xx.pknd;
	अन्यथा
		port = work->word1.cn38xx.ipprt;

	अगर ((work->word2.snoip.err_code == 10) && (work->word1.len <= 64))
		/*
		 * Ignore length errors on min size packets. Some
		 * equipment incorrectly pads packets to 64+4FCS
		 * instead of 60+4FCS.  Note these packets still get
		 * counted as frame errors.
		 */
		वापस 0;

	अगर (work->word2.snoip.err_code == 5 ||
	    work->word2.snoip.err_code == 7) अणु
		/*
		 * We received a packet with either an alignment error
		 * or a FCS error. This may be संकेतling that we are
		 * running 10Mbps with GMXX_RXX_FRM_CTL[PRE_CHK]
		 * off. If this is the हाल we need to parse the
		 * packet to determine अगर we can हटाओ a non spec
		 * preamble and generate a correct packet.
		 */
		पूर्णांक पूर्णांकerface = cvmx_helper_get_पूर्णांकerface_num(port);
		पूर्णांक index = cvmx_helper_get_पूर्णांकerface_index_num(port);
		जोड़ cvmx_gmxx_rxx_frm_ctl gmxx_rxx_frm_ctl;

		gmxx_rxx_frm_ctl.u64 =
		    cvmx_पढ़ो_csr(CVMX_GMXX_RXX_FRM_CTL(index, पूर्णांकerface));
		अगर (gmxx_rxx_frm_ctl.s.pre_chk == 0) अणु
			u8 *ptr =
			    cvmx_phys_to_ptr(work->packet_ptr.s.addr);
			पूर्णांक i = 0;

			जबतक (i < work->word1.len - 1) अणु
				अगर (*ptr != 0x55)
					अवरोध;
				ptr++;
				i++;
			पूर्ण

			अगर (*ptr == 0xd5) अणु
				/* Port received 0xd5 preamble */
				work->packet_ptr.s.addr += i + 1;
				work->word1.len -= i + 5;
				वापस 0;
			पूर्ण

			अगर ((*ptr & 0xf) == 0xd) अणु
				/* Port received 0xd preamble */
				work->packet_ptr.s.addr += i;
				work->word1.len -= i + 4;
				क्रम (i = 0; i < work->word1.len; i++) अणु
					*ptr =
					    ((*ptr & 0xf0) >> 4) |
					    ((*(ptr + 1) & 0xf) << 4);
					ptr++;
				पूर्ण
				वापस 0;
			पूर्ण

			prपूर्णांकk_ratelimited("Port %d unknown preamble, packet dropped\n",
					   port);
			cvm_oct_मुक्त_work(work);
			वापस 1;
		पूर्ण
	पूर्ण

	prपूर्णांकk_ratelimited("Port %d receive error code %d, packet dropped\n",
			   port, work->word2.snoip.err_code);
	cvm_oct_मुक्त_work(work);
	वापस 1;
पूर्ण

अटल व्योम copy_segments_to_skb(काष्ठा cvmx_wqe *work, काष्ठा sk_buff *skb)
अणु
	पूर्णांक segments = work->word2.s.bufs;
	जोड़ cvmx_buf_ptr segment_ptr = work->packet_ptr;
	पूर्णांक len = work->word1.len;
	पूर्णांक segment_size;

	जबतक (segments--) अणु
		जोड़ cvmx_buf_ptr next_ptr;

		next_ptr = *(जोड़ cvmx_buf_ptr *)
			cvmx_phys_to_ptr(segment_ptr.s.addr - 8);

		/*
		 * Octeon Errata PKI-100: The segment size is wrong.
		 *
		 * Until it is fixed, calculate the segment size based on
		 * the packet pool buffer size.
		 * When it is fixed, the following line should be replaced
		 * with this one:
		 * पूर्णांक segment_size = segment_ptr.s.size;
		 */
		segment_size =
			CVMX_FPA_PACKET_POOL_SIZE -
			(segment_ptr.s.addr -
			 (((segment_ptr.s.addr >> 7) -
			   segment_ptr.s.back) << 7));

		/* Don't copy more than what is left in the packet */
		अगर (segment_size > len)
			segment_size = len;

		/* Copy the data पूर्णांकo the packet */
		skb_put_data(skb, cvmx_phys_to_ptr(segment_ptr.s.addr),
			     segment_size);
		len -= segment_size;
		segment_ptr = next_ptr;
	पूर्ण
पूर्ण

अटल पूर्णांक cvm_oct_poll(काष्ठा oct_rx_group *rx_group, पूर्णांक budget)
अणु
	स्थिर पूर्णांक	coreid = cvmx_get_core_num();
	u64	old_group_mask;
	u64	old_scratch;
	पूर्णांक		rx_count = 0;
	पूर्णांक		did_work_request = 0;
	पूर्णांक		packet_not_copied;

	/* Prefetch cvm_oct_device since we know we need it soon */
	prefetch(cvm_oct_device);

	अगर (USE_ASYNC_IOBDMA) अणु
		/* Save scratch in हाल userspace is using it */
		CVMX_SYNCIOBDMA;
		old_scratch = cvmx_scratch_पढ़ो64(CVMX_SCR_SCRATCH);
	पूर्ण

	/* Only allow work क्रम our group (and preserve priorities) */
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
		old_group_mask = cvmx_पढ़ो_csr(CVMX_SSO_PPX_GRP_MSK(coreid));
		cvmx_ग_लिखो_csr(CVMX_SSO_PPX_GRP_MSK(coreid),
			       BIT(rx_group->group));
		cvmx_पढ़ो_csr(CVMX_SSO_PPX_GRP_MSK(coreid)); /* Flush */
	पूर्ण अन्यथा अणु
		old_group_mask = cvmx_पढ़ो_csr(CVMX_POW_PP_GRP_MSKX(coreid));
		cvmx_ग_लिखो_csr(CVMX_POW_PP_GRP_MSKX(coreid),
			       (old_group_mask & ~0xFFFFull) |
			       BIT(rx_group->group));
	पूर्ण

	अगर (USE_ASYNC_IOBDMA) अणु
		cvmx_घात_work_request_async(CVMX_SCR_SCRATCH, CVMX_POW_NO_WAIT);
		did_work_request = 1;
	पूर्ण

	जबतक (rx_count < budget) अणु
		काष्ठा sk_buff *skb = शून्य;
		काष्ठा sk_buff **pskb = शून्य;
		पूर्णांक skb_in_hw;
		काष्ठा cvmx_wqe *work;
		पूर्णांक port;

		अगर (USE_ASYNC_IOBDMA && did_work_request)
			work = cvmx_घात_work_response_async(CVMX_SCR_SCRATCH);
		अन्यथा
			work = cvmx_घात_work_request_sync(CVMX_POW_NO_WAIT);

		prefetch(work);
		did_work_request = 0;
		अगर (!work) अणु
			अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
				cvmx_ग_लिखो_csr(CVMX_SSO_WQ_IQ_DIS,
					       BIT(rx_group->group));
				cvmx_ग_लिखो_csr(CVMX_SSO_WQ_INT,
					       BIT(rx_group->group));
			पूर्ण अन्यथा अणु
				जोड़ cvmx_घात_wq_पूर्णांक wq_पूर्णांक;

				wq_पूर्णांक.u64 = 0;
				wq_पूर्णांक.s.iq_dis = BIT(rx_group->group);
				wq_पूर्णांक.s.wq_पूर्णांक = BIT(rx_group->group);
				cvmx_ग_लिखो_csr(CVMX_POW_WQ_INT, wq_पूर्णांक.u64);
			पूर्ण
			अवरोध;
		पूर्ण
		pskb = (काष्ठा sk_buff **)
			(cvm_oct_get_buffer_ptr(work->packet_ptr) -
			माप(व्योम *));
		prefetch(pskb);

		अगर (USE_ASYNC_IOBDMA && rx_count < (budget - 1)) अणु
			cvmx_घात_work_request_async_nocheck(CVMX_SCR_SCRATCH,
							    CVMX_POW_NO_WAIT);
			did_work_request = 1;
		पूर्ण
		rx_count++;

		skb_in_hw = work->word2.s.bufs == 1;
		अगर (likely(skb_in_hw)) अणु
			skb = *pskb;
			prefetch(&skb->head);
			prefetch(&skb->len);
		पूर्ण

		अगर (octeon_has_feature(OCTEON_FEATURE_PKND))
			port = work->word0.pip.cn68xx.pknd;
		अन्यथा
			port = work->word1.cn38xx.ipprt;

		prefetch(cvm_oct_device[port]);

		/* Immediately throw away all packets with receive errors */
		अगर (unlikely(work->word2.snoip.rcv_error)) अणु
			अगर (cvm_oct_check_rcv_error(work))
				जारी;
		पूर्ण

		/*
		 * We can only use the zero copy path अगर skbuffs are
		 * in the FPA pool and the packet fits in a single
		 * buffer.
		 */
		अगर (likely(skb_in_hw)) अणु
			skb->data = skb->head + work->packet_ptr.s.addr -
				cvmx_ptr_to_phys(skb->head);
			prefetch(skb->data);
			skb->len = work->word1.len;
			skb_set_tail_poपूर्णांकer(skb, skb->len);
			packet_not_copied = 1;
		पूर्ण अन्यथा अणु
			/*
			 * We have to copy the packet. First allocate
			 * an skbuff क्रम it.
			 */
			skb = dev_alloc_skb(work->word1.len);
			अगर (!skb) अणु
				cvm_oct_मुक्त_work(work);
				जारी;
			पूर्ण

			/*
			 * Check अगर we've received a packet that was
			 * entirely stored in the work entry.
			 */
			अगर (unlikely(work->word2.s.bufs == 0)) अणु
				u8 *ptr = work->packet_data;

				अगर (likely(!work->word2.s.not_IP)) अणु
					/*
					 * The beginning of the packet
					 * moves क्रम IP packets.
					 */
					अगर (work->word2.s.is_v6)
						ptr += 2;
					अन्यथा
						ptr += 6;
				पूर्ण
				skb_put_data(skb, ptr, work->word1.len);
				/* No packet buffers to मुक्त */
			पूर्ण अन्यथा अणु
				copy_segments_to_skb(work, skb);
			पूर्ण
			packet_not_copied = 0;
		पूर्ण
		अगर (likely((port < TOTAL_NUMBER_OF_PORTS) &&
			   cvm_oct_device[port])) अणु
			काष्ठा net_device *dev = cvm_oct_device[port];

			/*
			 * Only accept packets क्रम devices that are
			 * currently up.
			 */
			अगर (likely(dev->flags & IFF_UP)) अणु
				skb->protocol = eth_type_trans(skb, dev);
				skb->dev = dev;

				अगर (unlikely(work->word2.s.not_IP ||
					     work->word2.s.IP_exc ||
					     work->word2.s.L4_error ||
					     !work->word2.s.tcp_or_udp))
					skb->ip_summed = CHECKSUM_NONE;
				अन्यथा
					skb->ip_summed = CHECKSUM_UNNECESSARY;

				/* Increment RX stats क्रम भव ports */
				अगर (port >= CVMX_PIP_NUM_INPUT_PORTS) अणु
					dev->stats.rx_packets++;
					dev->stats.rx_bytes += skb->len;
				पूर्ण
				netअगर_receive_skb(skb);
			पूर्ण अन्यथा अणु
				/*
				 * Drop any packet received क्रम a device that
				 * isn't up.
				 */
				dev->stats.rx_dropped++;
				dev_kमुक्त_skb_irq(skb);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Drop any packet received क्रम a device that
			 * करोesn't exist.
			 */
			prपूर्णांकk_ratelimited("Port %d not controlled by Linux, packet dropped\n",
					   port);
			dev_kमुक्त_skb_irq(skb);
		पूर्ण
		/*
		 * Check to see अगर the skbuff and work share the same
		 * packet buffer.
		 */
		अगर (likely(packet_not_copied)) अणु
			/*
			 * This buffer needs to be replaced, increment
			 * the number of buffers we need to मुक्त by
			 * one.
			 */
			cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFERS_TO_FREE,
					      1);

			cvmx_fpa_मुक्त(work, CVMX_FPA_WQE_POOL, 1);
		पूर्ण अन्यथा अणु
			cvm_oct_मुक्त_work(work);
		पूर्ण
	पूर्ण
	/* Restore the original POW group mask */
	अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
		cvmx_ग_लिखो_csr(CVMX_SSO_PPX_GRP_MSK(coreid), old_group_mask);
		cvmx_पढ़ो_csr(CVMX_SSO_PPX_GRP_MSK(coreid)); /* Flush */
	पूर्ण अन्यथा अणु
		cvmx_ग_लिखो_csr(CVMX_POW_PP_GRP_MSKX(coreid), old_group_mask);
	पूर्ण

	अगर (USE_ASYNC_IOBDMA) अणु
		/* Restore the scratch area */
		cvmx_scratch_ग_लिखो64(CVMX_SCR_SCRATCH, old_scratch);
	पूर्ण
	cvm_oct_rx_refill_pool(0);

	वापस rx_count;
पूर्ण

/**
 * cvm_oct_napi_poll - the NAPI poll function.
 * @napi: The NAPI instance.
 * @budget: Maximum number of packets to receive.
 *
 * Returns the number of packets processed.
 */
अटल पूर्णांक cvm_oct_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा oct_rx_group *rx_group = container_of(napi, काष्ठा oct_rx_group,
						     napi);
	पूर्णांक rx_count;

	rx_count = cvm_oct_poll(rx_group, budget);

	अगर (rx_count < budget) अणु
		/* No more work */
		napi_complete_करोne(napi, rx_count);
		enable_irq(rx_group->irq);
	पूर्ण
	वापस rx_count;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/**
 * cvm_oct_poll_controller - poll क्रम receive packets
 * device.
 *
 * @dev:    Device to poll. Unused
 */
व्योम cvm_oct_poll_controller(काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	अगर (!atomic_पढ़ो(&oct_rx_पढ़ोy))
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(oct_rx_group); i++) अणु
		अगर (!(घात_receive_groups & BIT(i)))
			जारी;

		cvm_oct_poll(&oct_rx_group[i], 16);
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम cvm_oct_rx_initialize(व्योम)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev_क्रम_napi = शून्य;

	क्रम (i = 0; i < TOTAL_NUMBER_OF_PORTS; i++) अणु
		अगर (cvm_oct_device[i]) अणु
			dev_क्रम_napi = cvm_oct_device[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!dev_क्रम_napi)
		panic("No net_devices were allocated.");

	क्रम (i = 0; i < ARRAY_SIZE(oct_rx_group); i++) अणु
		पूर्णांक ret;

		अगर (!(घात_receive_groups & BIT(i)))
			जारी;

		netअगर_napi_add(dev_क्रम_napi, &oct_rx_group[i].napi,
			       cvm_oct_napi_poll, rx_napi_weight);
		napi_enable(&oct_rx_group[i].napi);

		oct_rx_group[i].irq = OCTEON_IRQ_WORKQ0 + i;
		oct_rx_group[i].group = i;

		/* Register an IRQ handler to receive POW पूर्णांकerrupts */
		ret = request_irq(oct_rx_group[i].irq, cvm_oct_करो_पूर्णांकerrupt, 0,
				  "Ethernet", &oct_rx_group[i].napi);
		अगर (ret)
			panic("Could not acquire Ethernet IRQ %d\n",
			      oct_rx_group[i].irq);

		disable_irq_nosync(oct_rx_group[i].irq);

		/* Enable POW पूर्णांकerrupt when our port has at least one packet */
		अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
			जोड़ cvmx_sso_wq_पूर्णांक_thrx पूर्णांक_thr;
			जोड़ cvmx_घात_wq_पूर्णांक_pc पूर्णांक_pc;

			पूर्णांक_thr.u64 = 0;
			पूर्णांक_thr.s.tc_en = 1;
			पूर्णांक_thr.s.tc_thr = 1;
			cvmx_ग_लिखो_csr(CVMX_SSO_WQ_INT_THRX(i), पूर्णांक_thr.u64);

			पूर्णांक_pc.u64 = 0;
			पूर्णांक_pc.s.pc_thr = 5;
			cvmx_ग_लिखो_csr(CVMX_SSO_WQ_INT_PC, पूर्णांक_pc.u64);
		पूर्ण अन्यथा अणु
			जोड़ cvmx_घात_wq_पूर्णांक_thrx पूर्णांक_thr;
			जोड़ cvmx_घात_wq_पूर्णांक_pc पूर्णांक_pc;

			पूर्णांक_thr.u64 = 0;
			पूर्णांक_thr.s.tc_en = 1;
			पूर्णांक_thr.s.tc_thr = 1;
			cvmx_ग_लिखो_csr(CVMX_POW_WQ_INT_THRX(i), पूर्णांक_thr.u64);

			पूर्णांक_pc.u64 = 0;
			पूर्णांक_pc.s.pc_thr = 5;
			cvmx_ग_लिखो_csr(CVMX_POW_WQ_INT_PC, पूर्णांक_pc.u64);
		पूर्ण

		/* Schedule NAPI now. This will indirectly enable the
		 * पूर्णांकerrupt.
		 */
		napi_schedule(&oct_rx_group[i].napi);
	पूर्ण
	atomic_inc(&oct_rx_पढ़ोy);
पूर्ण

व्योम cvm_oct_rx_shutकरोwn(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(oct_rx_group); i++) अणु
		अगर (!(घात_receive_groups & BIT(i)))
			जारी;

		/* Disable POW पूर्णांकerrupt */
		अगर (OCTEON_IS_MODEL(OCTEON_CN68XX))
			cvmx_ग_लिखो_csr(CVMX_SSO_WQ_INT_THRX(i), 0);
		अन्यथा
			cvmx_ग_लिखो_csr(CVMX_POW_WQ_INT_THRX(i), 0);

		/* Free the पूर्णांकerrupt handler */
		मुक्त_irq(oct_rx_group[i].irq, cvm_oct_device);

		netअगर_napi_del(&oct_rx_group[i].napi);
	पूर्ण
पूर्ण
