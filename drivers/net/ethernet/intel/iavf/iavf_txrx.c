<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश <linux/prefetch.h>

#समावेश "iavf.h"
#समावेश "iavf_trace.h"
#समावेश "iavf_prototype.h"

अटल अंतरभूत __le64 build_ctob(u32 td_cmd, u32 td_offset, अचिन्हित पूर्णांक size,
				u32 td_tag)
अणु
	वापस cpu_to_le64(IAVF_TX_DESC_DTYPE_DATA |
			   ((u64)td_cmd  << IAVF_TXD_QW1_CMD_SHIFT) |
			   ((u64)td_offset << IAVF_TXD_QW1_OFFSET_SHIFT) |
			   ((u64)size  << IAVF_TXD_QW1_TX_BUF_SZ_SHIFT) |
			   ((u64)td_tag  << IAVF_TXD_QW1_L2TAG1_SHIFT));
पूर्ण

#घोषणा IAVF_TXD_CMD (IAVF_TX_DESC_CMD_EOP | IAVF_TX_DESC_CMD_RS)

/**
 * iavf_unmap_and_मुक्त_tx_resource - Release a Tx buffer
 * @ring:      the ring that owns the buffer
 * @tx_buffer: the buffer to मुक्त
 **/
अटल व्योम iavf_unmap_and_मुक्त_tx_resource(काष्ठा iavf_ring *ring,
					    काष्ठा iavf_tx_buffer *tx_buffer)
अणु
	अगर (tx_buffer->skb) अणु
		अगर (tx_buffer->tx_flags & IAVF_TX_FLAGS_FD_SB)
			kमुक्त(tx_buffer->raw_buf);
		अन्यथा
			dev_kमुक्त_skb_any(tx_buffer->skb);
		अगर (dma_unmap_len(tx_buffer, len))
			dma_unmap_single(ring->dev,
					 dma_unmap_addr(tx_buffer, dma),
					 dma_unmap_len(tx_buffer, len),
					 DMA_TO_DEVICE);
	पूर्ण अन्यथा अगर (dma_unmap_len(tx_buffer, len)) अणु
		dma_unmap_page(ring->dev,
			       dma_unmap_addr(tx_buffer, dma),
			       dma_unmap_len(tx_buffer, len),
			       DMA_TO_DEVICE);
	पूर्ण

	tx_buffer->next_to_watch = शून्य;
	tx_buffer->skb = शून्य;
	dma_unmap_len_set(tx_buffer, len, 0);
	/* tx_buffer must be completely set up in the transmit path */
पूर्ण

/**
 * iavf_clean_tx_ring - Free any empty Tx buffers
 * @tx_ring: ring to be cleaned
 **/
व्योम iavf_clean_tx_ring(काष्ठा iavf_ring *tx_ring)
अणु
	अचिन्हित दीर्घ bi_size;
	u16 i;

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!tx_ring->tx_bi)
		वापस;

	/* Free all the Tx ring sk_buffs */
	क्रम (i = 0; i < tx_ring->count; i++)
		iavf_unmap_and_मुक्त_tx_resource(tx_ring, &tx_ring->tx_bi[i]);

	bi_size = माप(काष्ठा iavf_tx_buffer) * tx_ring->count;
	स_रखो(tx_ring->tx_bi, 0, bi_size);

	/* Zero out the descriptor ring */
	स_रखो(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	अगर (!tx_ring->netdev)
		वापस;

	/* cleanup Tx queue statistics */
	netdev_tx_reset_queue(txring_txq(tx_ring));
पूर्ण

/**
 * iavf_मुक्त_tx_resources - Free Tx resources per queue
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 **/
व्योम iavf_मुक्त_tx_resources(काष्ठा iavf_ring *tx_ring)
अणु
	iavf_clean_tx_ring(tx_ring);
	kमुक्त(tx_ring->tx_bi);
	tx_ring->tx_bi = शून्य;

	अगर (tx_ring->desc) अणु
		dma_मुक्त_coherent(tx_ring->dev, tx_ring->size,
				  tx_ring->desc, tx_ring->dma);
		tx_ring->desc = शून्य;
	पूर्ण
पूर्ण

/**
 * iavf_get_tx_pending - how many Tx descriptors not processed
 * @ring: the ring of descriptors
 * @in_sw: is tx_pending being checked in SW or HW
 *
 * Since there is no access to the ring head रेजिस्टर
 * in XL710, we need to use our local copies
 **/
u32 iavf_get_tx_pending(काष्ठा iavf_ring *ring, bool in_sw)
अणु
	u32 head, tail;

	head = ring->next_to_clean;
	tail = पढ़ोl(ring->tail);

	अगर (head != tail)
		वापस (head < tail) ?
			tail - head : (tail + ring->count - head);

	वापस 0;
पूर्ण

/**
 * iavf_detect_recover_hung - Function to detect and recover hung_queues
 * @vsi:  poपूर्णांकer to vsi काष्ठा with tx queues
 *
 * VSI has netdev and netdev has TX queues. This function is to check each of
 * those TX queues अगर they are hung, trigger recovery by issuing SW पूर्णांकerrupt.
 **/
व्योम iavf_detect_recover_hung(काष्ठा iavf_vsi *vsi)
अणु
	काष्ठा iavf_ring *tx_ring = शून्य;
	काष्ठा net_device *netdev;
	अचिन्हित पूर्णांक i;
	पूर्णांक packets;

	अगर (!vsi)
		वापस;

	अगर (test_bit(__IAVF_VSI_DOWN, vsi->state))
		वापस;

	netdev = vsi->netdev;
	अगर (!netdev)
		वापस;

	अगर (!netअगर_carrier_ok(netdev))
		वापस;

	क्रम (i = 0; i < vsi->back->num_active_queues; i++) अणु
		tx_ring = &vsi->back->tx_rings[i];
		अगर (tx_ring && tx_ring->desc) अणु
			/* If packet counter has not changed the queue is
			 * likely stalled, so क्रमce an पूर्णांकerrupt क्रम this
			 * queue.
			 *
			 * prev_pkt_ctr would be negative अगर there was no
			 * pending work.
			 */
			packets = tx_ring->stats.packets & पूर्णांक_उच्च;
			अगर (tx_ring->tx_stats.prev_pkt_ctr == packets) अणु
				iavf_क्रमce_wb(vsi, tx_ring->q_vector);
				जारी;
			पूर्ण

			/* Memory barrier between पढ़ो of packet count and call
			 * to iavf_get_tx_pending()
			 */
			smp_rmb();
			tx_ring->tx_stats.prev_pkt_ctr =
			  iavf_get_tx_pending(tx_ring, true) ? packets : -1;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा WB_STRIDE 4

/**
 * iavf_clean_tx_irq - Reclaim resources after transmit completes
 * @vsi: the VSI we care about
 * @tx_ring: Tx ring to clean
 * @napi_budget: Used to determine अगर we are in netpoll
 *
 * Returns true अगर there's any budget left (e.g. the clean is finished)
 **/
अटल bool iavf_clean_tx_irq(काष्ठा iavf_vsi *vsi,
			      काष्ठा iavf_ring *tx_ring, पूर्णांक napi_budget)
अणु
	पूर्णांक i = tx_ring->next_to_clean;
	काष्ठा iavf_tx_buffer *tx_buf;
	काष्ठा iavf_tx_desc *tx_desc;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित पूर्णांक budget = vsi->work_limit;

	tx_buf = &tx_ring->tx_bi[i];
	tx_desc = IAVF_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		काष्ठा iavf_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		iavf_trace(clean_tx_irq, tx_ring, tx_desc, tx_buf);
		/* अगर the descriptor isn't करोne, no work yet to करो */
		अगर (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_le64(IAVF_TX_DESC_DTYPE_DESC_DONE)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buf->bytecount;
		total_packets += tx_buf->gso_segs;

		/* मुक्त the skb */
		napi_consume_skb(tx_buf->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buf, dma),
				 dma_unmap_len(tx_buf, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		tx_buf->skb = शून्य;
		dma_unmap_len_set(tx_buf, len, 0);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			iavf_trace(clean_tx_irq_unmap,
				   tx_ring, tx_desc, tx_buf);

			tx_buf++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buf = tx_ring->tx_bi;
				tx_desc = IAVF_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buf, len)) अणु
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buf, dma),
					       dma_unmap_len(tx_buf, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buf, len, 0);
			पूर्ण
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buf++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_bi;
			tx_desc = IAVF_TX_DESC(tx_ring, 0);
		पूर्ण

		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->syncp);
	tx_ring->q_vector->tx.total_bytes += total_bytes;
	tx_ring->q_vector->tx.total_packets += total_packets;

	अगर (tx_ring->flags & IAVF_TXR_FLAGS_WB_ON_ITR) अणु
		/* check to see अगर there are < 4 descriptors
		 * रुकोing to be written back, then kick the hardware to क्रमce
		 * them to be written back in हाल we stay in NAPI.
		 * In this mode on X722 we करो not enable Interrupt.
		 */
		अचिन्हित पूर्णांक j = iavf_get_tx_pending(tx_ring, false);

		अगर (budget &&
		    ((j / WB_STRIDE) == 0) && (j > 0) &&
		    !test_bit(__IAVF_VSI_DOWN, vsi->state) &&
		    (IAVF_DESC_UNUSED(tx_ring) != tx_ring->count))
			tx_ring->arm_wb = true;
	पूर्ण

	/* notअगरy netdev of completed buffers */
	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);

#घोषणा TX_WAKE_THRESHOLD ((s16)(DESC_NEEDED * 2))
	अगर (unlikely(total_packets && netअगर_carrier_ok(tx_ring->netdev) &&
		     (IAVF_DESC_UNUSED(tx_ring) >= TX_WAKE_THRESHOLD))) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		   !test_bit(__IAVF_VSI_DOWN, vsi->state)) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

/**
 * iavf_enable_wb_on_itr - Arm hardware to करो a wb, पूर्णांकerrupts are not enabled
 * @vsi: the VSI we care about
 * @q_vector: the vector on which to enable ग_लिखोback
 *
 **/
अटल व्योम iavf_enable_wb_on_itr(काष्ठा iavf_vsi *vsi,
				  काष्ठा iavf_q_vector *q_vector)
अणु
	u16 flags = q_vector->tx.ring[0].flags;
	u32 val;

	अगर (!(flags & IAVF_TXR_FLAGS_WB_ON_ITR))
		वापस;

	अगर (q_vector->arm_wb_state)
		वापस;

	val = IAVF_VFINT_DYN_CTLN1_WB_ON_ITR_MASK |
	      IAVF_VFINT_DYN_CTLN1_ITR_INDX_MASK; /* set noitr */

	wr32(&vsi->back->hw,
	     IAVF_VFINT_DYN_CTLN1(q_vector->reg_idx), val);
	q_vector->arm_wb_state = true;
पूर्ण

/**
 * iavf_क्रमce_wb - Issue SW Interrupt so HW करोes a wb
 * @vsi: the VSI we care about
 * @q_vector: the vector  on which to क्रमce ग_लिखोback
 *
 **/
व्योम iavf_क्रमce_wb(काष्ठा iavf_vsi *vsi, काष्ठा iavf_q_vector *q_vector)
अणु
	u32 val = IAVF_VFINT_DYN_CTLN1_INTENA_MASK |
		  IAVF_VFINT_DYN_CTLN1_ITR_INDX_MASK | /* set noitr */
		  IAVF_VFINT_DYN_CTLN1_SWINT_TRIG_MASK |
		  IAVF_VFINT_DYN_CTLN1_SW_ITR_INDX_ENA_MASK
		  /* allow 00 to be written to the index */;

	wr32(&vsi->back->hw,
	     IAVF_VFINT_DYN_CTLN1(q_vector->reg_idx),
	     val);
पूर्ण

अटल अंतरभूत bool iavf_container_is_rx(काष्ठा iavf_q_vector *q_vector,
					काष्ठा iavf_ring_container *rc)
अणु
	वापस &q_vector->rx == rc;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक iavf_itr_भागisor(काष्ठा iavf_q_vector *q_vector)
अणु
	अचिन्हित पूर्णांक भागisor;

	चयन (q_vector->adapter->link_speed) अणु
	हाल VIRTCHNL_LINK_SPEED_40GB:
		भागisor = IAVF_ITR_ADAPTIVE_MIN_INC * 1024;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_25GB:
	हाल VIRTCHNL_LINK_SPEED_20GB:
		भागisor = IAVF_ITR_ADAPTIVE_MIN_INC * 512;
		अवरोध;
	शेष:
	हाल VIRTCHNL_LINK_SPEED_10GB:
		भागisor = IAVF_ITR_ADAPTIVE_MIN_INC * 256;
		अवरोध;
	हाल VIRTCHNL_LINK_SPEED_1GB:
	हाल VIRTCHNL_LINK_SPEED_100MB:
		भागisor = IAVF_ITR_ADAPTIVE_MIN_INC * 32;
		अवरोध;
	पूर्ण

	वापस भागisor;
पूर्ण

/**
 * iavf_update_itr - update the dynamic ITR value based on statistics
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @rc: काष्ठाure containing ring perक्रमmance data
 *
 * Stores a new ITR value based on packets and byte
 * counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 * computation is faster updates and more accurate ITR क्रम the current
 * traffic pattern.  Constants in this function were computed
 * based on theoretical maximum wire speed and thresholds were set based
 * on testing data as well as attempting to minimize response समय
 * जबतक increasing bulk throughput.
 **/
अटल व्योम iavf_update_itr(काष्ठा iavf_q_vector *q_vector,
			    काष्ठा iavf_ring_container *rc)
अणु
	अचिन्हित पूर्णांक avg_wire_size, packets, bytes, itr;
	अचिन्हित दीर्घ next_update = jअगरfies;

	/* If we करोn't have any rings just leave ourselves set क्रम maximum
	 * possible latency so we take ourselves out of the equation.
	 */
	अगर (!rc->ring || !ITR_IS_DYNAMIC(rc->ring->itr_setting))
		वापस;

	/* For Rx we want to push the delay up and शेष to low latency.
	 * क्रम Tx we want to pull the delay करोwn and शेष to high latency.
	 */
	itr = iavf_container_is_rx(q_vector, rc) ?
	      IAVF_ITR_ADAPTIVE_MIN_USECS | IAVF_ITR_ADAPTIVE_LATENCY :
	      IAVF_ITR_ADAPTIVE_MAX_USECS | IAVF_ITR_ADAPTIVE_LATENCY;

	/* If we didn't update within up to 1 - 2 jअगरfies we can assume
	 * that either packets are coming in so slow there hasn't been
	 * any work, or that there is so much work that NAPI is dealing
	 * with पूर्णांकerrupt moderation and we करोn't need to करो anything.
	 */
	अगर (समय_after(next_update, rc->next_update))
		जाओ clear_counts;

	/* If itr_countकरोwn is set it means we programmed an ITR within
	 * the last 4 पूर्णांकerrupt cycles. This has a side effect of us
	 * potentially firing an early पूर्णांकerrupt. In order to work around
	 * this we need to throw out any data received क्रम a few
	 * पूर्णांकerrupts following the update.
	 */
	अगर (q_vector->itr_countकरोwn) अणु
		itr = rc->target_itr;
		जाओ clear_counts;
	पूर्ण

	packets = rc->total_packets;
	bytes = rc->total_bytes;

	अगर (iavf_container_is_rx(q_vector, rc)) अणु
		/* If Rx there are 1 to 4 packets and bytes are less than
		 * 9000 assume insufficient data to use bulk rate limiting
		 * approach unless Tx is alपढ़ोy in bulk rate limiting. We
		 * are likely latency driven.
		 */
		अगर (packets && packets < 4 && bytes < 9000 &&
		    (q_vector->tx.target_itr & IAVF_ITR_ADAPTIVE_LATENCY)) अणु
			itr = IAVF_ITR_ADAPTIVE_LATENCY;
			जाओ adjust_by_size;
		पूर्ण
	पूर्ण अन्यथा अगर (packets < 4) अणु
		/* If we have Tx and Rx ITR maxed and Tx ITR is running in
		 * bulk mode and we are receiving 4 or fewer packets just
		 * reset the ITR_ADAPTIVE_LATENCY bit क्रम latency mode so
		 * that the Rx can relax.
		 */
		अगर (rc->target_itr == IAVF_ITR_ADAPTIVE_MAX_USECS &&
		    (q_vector->rx.target_itr & IAVF_ITR_MASK) ==
		     IAVF_ITR_ADAPTIVE_MAX_USECS)
			जाओ clear_counts;
	पूर्ण अन्यथा अगर (packets > 32) अणु
		/* If we have processed over 32 packets in a single पूर्णांकerrupt
		 * क्रम Tx assume we need to चयन over to "bulk" mode.
		 */
		rc->target_itr &= ~IAVF_ITR_ADAPTIVE_LATENCY;
	पूर्ण

	/* We have no packets to actually measure against. This means
	 * either one of the other queues on this vector is active or
	 * we are a Tx queue करोing TSO with too high of an पूर्णांकerrupt rate.
	 *
	 * Between 4 and 56 we can assume that our current पूर्णांकerrupt delay
	 * is only slightly too low. As such we should increase it by a small
	 * fixed amount.
	 */
	अगर (packets < 56) अणु
		itr = rc->target_itr + IAVF_ITR_ADAPTIVE_MIN_INC;
		अगर ((itr & IAVF_ITR_MASK) > IAVF_ITR_ADAPTIVE_MAX_USECS) अणु
			itr &= IAVF_ITR_ADAPTIVE_LATENCY;
			itr += IAVF_ITR_ADAPTIVE_MAX_USECS;
		पूर्ण
		जाओ clear_counts;
	पूर्ण

	अगर (packets <= 256) अणु
		itr = min(q_vector->tx.current_itr, q_vector->rx.current_itr);
		itr &= IAVF_ITR_MASK;

		/* Between 56 and 112 is our "goldilocks" zone where we are
		 * working out "just right". Just report that our current
		 * ITR is good क्रम us.
		 */
		अगर (packets <= 112)
			जाओ clear_counts;

		/* If packet count is 128 or greater we are likely looking
		 * at a slight overrun of the delay we want. Try halving
		 * our delay to see अगर that will cut the number of packets
		 * in half per पूर्णांकerrupt.
		 */
		itr /= 2;
		itr &= IAVF_ITR_MASK;
		अगर (itr < IAVF_ITR_ADAPTIVE_MIN_USECS)
			itr = IAVF_ITR_ADAPTIVE_MIN_USECS;

		जाओ clear_counts;
	पूर्ण

	/* The paths below assume we are dealing with a bulk ITR since
	 * number of packets is greater than 256. We are just going to have
	 * to compute a value and try to bring the count under control,
	 * though क्रम smaller packet sizes there isn't much we can करो as
	 * NAPI polling will likely be kicking in sooner rather than later.
	 */
	itr = IAVF_ITR_ADAPTIVE_BULK;

adjust_by_size:
	/* If packet counts are 256 or greater we can assume we have a gross
	 * overestimation of what the rate should be. Instead of trying to fine
	 * tune it just use the क्रमmula below to try and dial in an exact value
	 * give the current packet size of the frame.
	 */
	avg_wire_size = bytes / packets;

	/* The following is a crude approximation of:
	 *  wmem_शेष / (size + overhead) = desired_pkts_per_पूर्णांक
	 *  rate / bits_per_byte / (size + ethernet overhead) = pkt_rate
	 *  (desired_pkt_rate / pkt_rate) * usecs_per_sec = ITR value
	 *
	 * Assuming wmem_शेष is 212992 and overhead is 640 bytes per
	 * packet, (256 skb, 64 headroom, 320 shared info), we can reduce the
	 * क्रमmula करोwn to
	 *
	 *  (170 * (size + 24)) / (size + 640) = ITR
	 *
	 * We first करो some math on the packet size and then finally bitshअगरt
	 * by 8 after rounding up. We also have to account क्रम PCIe link speed
	 * dअगरference as ITR scales based on this.
	 */
	अगर (avg_wire_size <= 60) अणु
		/* Start at 250k पूर्णांकs/sec */
		avg_wire_size = 4096;
	पूर्ण अन्यथा अगर (avg_wire_size <= 380) अणु
		/* 250K पूर्णांकs/sec to 60K पूर्णांकs/sec */
		avg_wire_size *= 40;
		avg_wire_size += 1696;
	पूर्ण अन्यथा अगर (avg_wire_size <= 1084) अणु
		/* 60K पूर्णांकs/sec to 36K पूर्णांकs/sec */
		avg_wire_size *= 15;
		avg_wire_size += 11452;
	पूर्ण अन्यथा अगर (avg_wire_size <= 1980) अणु
		/* 36K पूर्णांकs/sec to 30K पूर्णांकs/sec */
		avg_wire_size *= 5;
		avg_wire_size += 22420;
	पूर्ण अन्यथा अणु
		/* plateau at a limit of 30K पूर्णांकs/sec */
		avg_wire_size = 32256;
	पूर्ण

	/* If we are in low latency mode halve our delay which द्विगुनs the
	 * rate to somewhere between 100K to 16K पूर्णांकs/sec
	 */
	अगर (itr & IAVF_ITR_ADAPTIVE_LATENCY)
		avg_wire_size /= 2;

	/* Resultant value is 256 बार larger than it needs to be. This
	 * gives us room to adjust the value as needed to either increase
	 * or decrease the value based on link speeds of 10G, 2.5G, 1G, etc.
	 *
	 * Use addition as we have alपढ़ोy recorded the new latency flag
	 * क्रम the ITR value.
	 */
	itr += DIV_ROUND_UP(avg_wire_size, iavf_itr_भागisor(q_vector)) *
	       IAVF_ITR_ADAPTIVE_MIN_INC;

	अगर ((itr & IAVF_ITR_MASK) > IAVF_ITR_ADAPTIVE_MAX_USECS) अणु
		itr &= IAVF_ITR_ADAPTIVE_LATENCY;
		itr += IAVF_ITR_ADAPTIVE_MAX_USECS;
	पूर्ण

clear_counts:
	/* ग_लिखो back value */
	rc->target_itr = itr;

	/* next update should occur within next jअगरfy */
	rc->next_update = next_update + 1;

	rc->total_bytes = 0;
	rc->total_packets = 0;
पूर्ण

/**
 * iavf_setup_tx_descriptors - Allocate the Tx descriptors
 * @tx_ring: the tx ring to set up
 *
 * Return 0 on success, negative on error
 **/
पूर्णांक iavf_setup_tx_descriptors(काष्ठा iavf_ring *tx_ring)
अणु
	काष्ठा device *dev = tx_ring->dev;
	पूर्णांक bi_size;

	अगर (!dev)
		वापस -ENOMEM;

	/* warn अगर we are about to overग_लिखो the poपूर्णांकer */
	WARN_ON(tx_ring->tx_bi);
	bi_size = माप(काष्ठा iavf_tx_buffer) * tx_ring->count;
	tx_ring->tx_bi = kzalloc(bi_size, GFP_KERNEL);
	अगर (!tx_ring->tx_bi)
		जाओ err;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(काष्ठा iavf_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);
	tx_ring->desc = dma_alloc_coherent(dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc) अणु
		dev_info(dev, "Unable to allocate memory for the Tx descriptor ring, size=%d\n",
			 tx_ring->size);
		जाओ err;
	पूर्ण

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	tx_ring->tx_stats.prev_pkt_ctr = -1;
	वापस 0;

err:
	kमुक्त(tx_ring->tx_bi);
	tx_ring->tx_bi = शून्य;
	वापस -ENOMEM;
पूर्ण

/**
 * iavf_clean_rx_ring - Free Rx buffers
 * @rx_ring: ring to be cleaned
 **/
व्योम iavf_clean_rx_ring(काष्ठा iavf_ring *rx_ring)
अणु
	अचिन्हित दीर्घ bi_size;
	u16 i;

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!rx_ring->rx_bi)
		वापस;

	अगर (rx_ring->skb) अणु
		dev_kमुक्त_skb(rx_ring->skb);
		rx_ring->skb = शून्य;
	पूर्ण

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		काष्ठा iavf_rx_buffer *rx_bi = &rx_ring->rx_bi[i];

		अगर (!rx_bi->page)
			जारी;

		/* Invalidate cache lines that may have been written to by
		 * device so that we aव्योम corrupting memory.
		 */
		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      rx_bi->dma,
					      rx_bi->page_offset,
					      rx_ring->rx_buf_len,
					      DMA_FROM_DEVICE);

		/* मुक्त resources associated with mapping */
		dma_unmap_page_attrs(rx_ring->dev, rx_bi->dma,
				     iavf_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     IAVF_RX_DMA_ATTR);

		__page_frag_cache_drain(rx_bi->page, rx_bi->pagecnt_bias);

		rx_bi->page = शून्य;
		rx_bi->page_offset = 0;
	पूर्ण

	bi_size = माप(काष्ठा iavf_rx_buffer) * rx_ring->count;
	स_रखो(rx_ring->rx_bi, 0, bi_size);

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

/**
 * iavf_मुक्त_rx_resources - Free Rx resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 **/
व्योम iavf_मुक्त_rx_resources(काष्ठा iavf_ring *rx_ring)
अणु
	iavf_clean_rx_ring(rx_ring);
	kमुक्त(rx_ring->rx_bi);
	rx_ring->rx_bi = शून्य;

	अगर (rx_ring->desc) अणु
		dma_मुक्त_coherent(rx_ring->dev, rx_ring->size,
				  rx_ring->desc, rx_ring->dma);
		rx_ring->desc = शून्य;
	पूर्ण
पूर्ण

/**
 * iavf_setup_rx_descriptors - Allocate Rx descriptors
 * @rx_ring: Rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक iavf_setup_rx_descriptors(काष्ठा iavf_ring *rx_ring)
अणु
	काष्ठा device *dev = rx_ring->dev;
	पूर्णांक bi_size;

	/* warn अगर we are about to overग_लिखो the poपूर्णांकer */
	WARN_ON(rx_ring->rx_bi);
	bi_size = माप(काष्ठा iavf_rx_buffer) * rx_ring->count;
	rx_ring->rx_bi = kzalloc(bi_size, GFP_KERNEL);
	अगर (!rx_ring->rx_bi)
		जाओ err;

	u64_stats_init(&rx_ring->syncp);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * माप(जोड़ iavf_32byte_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);
	rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);

	अगर (!rx_ring->desc) अणु
		dev_info(dev, "Unable to allocate memory for the Rx descriptor ring, size=%d\n",
			 rx_ring->size);
		जाओ err;
	पूर्ण

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	वापस 0;
err:
	kमुक्त(rx_ring->rx_bi);
	rx_ring->rx_bi = शून्य;
	वापस -ENOMEM;
पूर्ण

/**
 * iavf_release_rx_desc - Store the new tail and head values
 * @rx_ring: ring to bump
 * @val: new head index
 **/
अटल अंतरभूत व्योम iavf_release_rx_desc(काष्ठा iavf_ring *rx_ring, u32 val)
अणु
	rx_ring->next_to_use = val;

	/* update next to alloc since we have filled the ring */
	rx_ring->next_to_alloc = val;

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64).
	 */
	wmb();
	ग_लिखोl(val, rx_ring->tail);
पूर्ण

/**
 * iavf_rx_offset - Return expected offset पूर्णांकo page to access data
 * @rx_ring: Ring we are requesting offset of
 *
 * Returns the offset value क्रम ring पूर्णांकo the data buffer.
 */
अटल अंतरभूत अचिन्हित पूर्णांक iavf_rx_offset(काष्ठा iavf_ring *rx_ring)
अणु
	वापस ring_uses_build_skb(rx_ring) ? IAVF_SKB_PAD : 0;
पूर्ण

/**
 * iavf_alloc_mapped_page - recycle or make a new page
 * @rx_ring: ring to use
 * @bi: rx_buffer काष्ठा to modअगरy
 *
 * Returns true अगर the page was successfully allocated or
 * reused.
 **/
अटल bool iavf_alloc_mapped_page(काष्ठा iavf_ring *rx_ring,
				   काष्ठा iavf_rx_buffer *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should selकरोm need to alloc */
	अगर (likely(page)) अणु
		rx_ring->rx_stats.page_reuse_count++;
		वापस true;
	पूर्ण

	/* alloc new page क्रम storage */
	page = dev_alloc_pages(iavf_rx_pg_order(rx_ring));
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_page_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 iavf_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE,
				 IAVF_RX_DMA_ATTR);

	/* अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_pages(page, iavf_rx_pg_order(rx_ring));
		rx_ring->rx_stats.alloc_page_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = iavf_rx_offset(rx_ring);

	/* initialize pagecnt_bias to 1 representing we fully own page */
	bi->pagecnt_bias = 1;

	वापस true;
पूर्ण

/**
 * iavf_receive_skb - Send a completed packet up the stack
 * @rx_ring:  rx ring in play
 * @skb: packet to send up
 * @vlan_tag: vlan tag क्रम packet
 **/
अटल व्योम iavf_receive_skb(काष्ठा iavf_ring *rx_ring,
			     काष्ठा sk_buff *skb, u16 vlan_tag)
अणु
	काष्ठा iavf_q_vector *q_vector = rx_ring->q_vector;

	अगर ((rx_ring->netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    (vlan_tag & VLAN_VID_MASK))
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);

	napi_gro_receive(&q_vector->napi, skb);
पूर्ण

/**
 * iavf_alloc_rx_buffers - Replace used receive buffers
 * @rx_ring: ring to place buffers on
 * @cleaned_count: number of buffers to replace
 *
 * Returns false अगर all allocations were successful, true अगर any fail
 **/
bool iavf_alloc_rx_buffers(काष्ठा iavf_ring *rx_ring, u16 cleaned_count)
अणु
	u16 ntu = rx_ring->next_to_use;
	जोड़ iavf_rx_desc *rx_desc;
	काष्ठा iavf_rx_buffer *bi;

	/* करो nothing अगर no valid netdev defined */
	अगर (!rx_ring->netdev || !cleaned_count)
		वापस false;

	rx_desc = IAVF_RX_DESC(rx_ring, ntu);
	bi = &rx_ring->rx_bi[ntu];

	करो अणु
		अगर (!iavf_alloc_mapped_page(rx_ring, bi))
			जाओ no_buffers;

		/* sync the buffer क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, bi->dma,
						 bi->page_offset,
						 rx_ring->rx_buf_len,
						 DMA_FROM_DEVICE);

		/* Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		ntu++;
		अगर (unlikely(ntu == rx_ring->count)) अणु
			rx_desc = IAVF_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_bi;
			ntu = 0;
		पूर्ण

		/* clear the status bits क्रम the next_to_use descriptor */
		rx_desc->wb.qword1.status_error_len = 0;

		cleaned_count--;
	पूर्ण जबतक (cleaned_count);

	अगर (rx_ring->next_to_use != ntu)
		iavf_release_rx_desc(rx_ring, ntu);

	वापस false;

no_buffers:
	अगर (rx_ring->next_to_use != ntu)
		iavf_release_rx_desc(rx_ring, ntu);

	/* make sure to come back via polling to try again after
	 * allocation failure
	 */
	वापस true;
पूर्ण

/**
 * iavf_rx_checksum - Indicate in skb अगर hw indicated a good cksum
 * @vsi: the VSI we care about
 * @skb: skb currently being received and modअगरied
 * @rx_desc: the receive descriptor
 **/
अटल अंतरभूत व्योम iavf_rx_checksum(काष्ठा iavf_vsi *vsi,
				    काष्ठा sk_buff *skb,
				    जोड़ iavf_rx_desc *rx_desc)
अणु
	काष्ठा iavf_rx_ptype_decoded decoded;
	u32 rx_error, rx_status;
	bool ipv4, ipv6;
	u8 ptype;
	u64 qword;

	qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
	ptype = (qword & IAVF_RXD_QW1_PTYPE_MASK) >> IAVF_RXD_QW1_PTYPE_SHIFT;
	rx_error = (qword & IAVF_RXD_QW1_ERROR_MASK) >>
		   IAVF_RXD_QW1_ERROR_SHIFT;
	rx_status = (qword & IAVF_RXD_QW1_STATUS_MASK) >>
		    IAVF_RXD_QW1_STATUS_SHIFT;
	decoded = decode_rx_desc_ptype(ptype);

	skb->ip_summed = CHECKSUM_NONE;

	skb_checksum_none_निश्चित(skb);

	/* Rx csum enabled and ip headers found? */
	अगर (!(vsi->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* did the hardware decode the packet and checksum? */
	अगर (!(rx_status & BIT(IAVF_RX_DESC_STATUS_L3L4P_SHIFT)))
		वापस;

	/* both known and outer_ip must be set क्रम the below code to work */
	अगर (!(decoded.known && decoded.outer_ip))
		वापस;

	ipv4 = (decoded.outer_ip == IAVF_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == IAVF_RX_PTYPE_OUTER_IPV4);
	ipv6 = (decoded.outer_ip == IAVF_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == IAVF_RX_PTYPE_OUTER_IPV6);

	अगर (ipv4 &&
	    (rx_error & (BIT(IAVF_RX_DESC_ERROR_IPE_SHIFT) |
			 BIT(IAVF_RX_DESC_ERROR_EIPE_SHIFT))))
		जाओ checksum_fail;

	/* likely incorrect csum अगर alternate IP extension headers found */
	अगर (ipv6 &&
	    rx_status & BIT(IAVF_RX_DESC_STATUS_IPV6EXADD_SHIFT))
		/* करोn't increment checksum err here, non-fatal err */
		वापस;

	/* there was some L4 error, count error and punt packet to the stack */
	अगर (rx_error & BIT(IAVF_RX_DESC_ERROR_L4E_SHIFT))
		जाओ checksum_fail;

	/* handle packets that were not able to be checksummed due
	 * to arrival speed, in this हाल the stack can compute
	 * the csum.
	 */
	अगर (rx_error & BIT(IAVF_RX_DESC_ERROR_PPRS_SHIFT))
		वापस;

	/* Only report checksum unnecessary क्रम TCP, UDP, or SCTP */
	चयन (decoded.inner_prot) अणु
	हाल IAVF_RX_PTYPE_INNER_PROT_TCP:
	हाल IAVF_RX_PTYPE_INNER_PROT_UDP:
	हाल IAVF_RX_PTYPE_INNER_PROT_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

	वापस;

checksum_fail:
	vsi->back->hw_csum_rx_error++;
पूर्ण

/**
 * iavf_ptype_to_htype - get a hash type
 * @ptype: the ptype value from the descriptor
 *
 * Returns a hash type to be used by skb_set_hash
 **/
अटल अंतरभूत पूर्णांक iavf_ptype_to_htype(u8 ptype)
अणु
	काष्ठा iavf_rx_ptype_decoded decoded = decode_rx_desc_ptype(ptype);

	अगर (!decoded.known)
		वापस PKT_HASH_TYPE_NONE;

	अगर (decoded.outer_ip == IAVF_RX_PTYPE_OUTER_IP &&
	    decoded.payload_layer == IAVF_RX_PTYPE_PAYLOAD_LAYER_PAY4)
		वापस PKT_HASH_TYPE_L4;
	अन्यथा अगर (decoded.outer_ip == IAVF_RX_PTYPE_OUTER_IP &&
		 decoded.payload_layer == IAVF_RX_PTYPE_PAYLOAD_LAYER_PAY3)
		वापस PKT_HASH_TYPE_L3;
	अन्यथा
		वापस PKT_HASH_TYPE_L2;
पूर्ण

/**
 * iavf_rx_hash - set the hash value in the skb
 * @ring: descriptor ring
 * @rx_desc: specअगरic descriptor
 * @skb: skb currently being received and modअगरied
 * @rx_ptype: Rx packet type
 **/
अटल अंतरभूत व्योम iavf_rx_hash(काष्ठा iavf_ring *ring,
				जोड़ iavf_rx_desc *rx_desc,
				काष्ठा sk_buff *skb,
				u8 rx_ptype)
अणु
	u32 hash;
	स्थिर __le64 rss_mask =
		cpu_to_le64((u64)IAVF_RX_DESC_FLTSTAT_RSS_HASH <<
			    IAVF_RX_DESC_STATUS_FLTSTAT_SHIFT);

	अगर (ring->netdev->features & NETIF_F_RXHASH)
		वापस;

	अगर ((rx_desc->wb.qword1.status_error_len & rss_mask) == rss_mask) अणु
		hash = le32_to_cpu(rx_desc->wb.qword0.hi_dword.rss);
		skb_set_hash(skb, hash, iavf_ptype_to_htype(rx_ptype));
	पूर्ण
पूर्ण

/**
 * iavf_process_skb_fields - Populate skb header fields from Rx descriptor
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being populated
 * @rx_ptype: the packet type decoded by hardware
 *
 * This function checks the ring, descriptor, and packet inक्रमmation in
 * order to populate the hash, checksum, VLAN, protocol, and
 * other fields within the skb.
 **/
अटल अंतरभूत
व्योम iavf_process_skb_fields(काष्ठा iavf_ring *rx_ring,
			     जोड़ iavf_rx_desc *rx_desc, काष्ठा sk_buff *skb,
			     u8 rx_ptype)
अणु
	iavf_rx_hash(rx_ring, rx_desc, skb, rx_ptype);

	iavf_rx_checksum(rx_ring->vsi, skb, rx_desc);

	skb_record_rx_queue(skb, rx_ring->queue_index);

	/* modअगरies the skb - consumes the enet header */
	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
पूर्ण

/**
 * iavf_cleanup_headers - Correct empty headers
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @skb: poपूर्णांकer to current skb being fixed
 *
 * Also address the हाल where we are pulling data in on pages only
 * and as such no data is present in the skb header.
 *
 * In addition अगर skb is not at least 60 bytes we need to pad it so that
 * it is large enough to qualअगरy as a valid Ethernet frame.
 *
 * Returns true अगर an error was encountered and skb was मुक्तd.
 **/
अटल bool iavf_cleanup_headers(काष्ठा iavf_ring *rx_ring, काष्ठा sk_buff *skb)
अणु
	/* अगर eth_skb_pad वापसs an error the skb was मुक्तd */
	अगर (eth_skb_pad(skb))
		वापस true;

	वापस false;
पूर्ण

/**
 * iavf_reuse_rx_page - page flip buffer and store it back on the ring
 * @rx_ring: rx descriptor ring to store buffers on
 * @old_buff: करोnor buffer to have page reused
 *
 * Synchronizes page क्रम reuse by the adapter
 **/
अटल व्योम iavf_reuse_rx_page(काष्ठा iavf_ring *rx_ring,
			       काष्ठा iavf_rx_buffer *old_buff)
अणु
	काष्ठा iavf_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_bi[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	new_buff->dma		= old_buff->dma;
	new_buff->page		= old_buff->page;
	new_buff->page_offset	= old_buff->page_offset;
	new_buff->pagecnt_bias	= old_buff->pagecnt_bias;
पूर्ण

/**
 * iavf_can_reuse_rx_page - Determine अगर this page can be reused by
 * the adapter क्रम another receive
 *
 * @rx_buffer: buffer containing the page
 *
 * If page is reusable, rx_buffer->page_offset is adjusted to poपूर्णांक to
 * an unused region in the page.
 *
 * For small pages, @truesize will be a स्थिरant value, half the size
 * of the memory at page.  We'll attempt to alternate between high and
 * low halves of the page, with one half पढ़ोy क्रम use by the hardware
 * and the other half being consumed by the stack.  We use the page
 * ref count to determine whether the stack has finished consuming the
 * portion of this page that was passed up with a previous packet.  If
 * the page ref count is >1, we'll assume the "other" half page is
 * still busy, and this page cannot be reused.
 *
 * For larger pages, @truesize will be the actual space used by the
 * received packet (adjusted upward to an even multiple of the cache
 * line size).  This will advance through the page by the amount
 * actually consumed by the received packets जबतक there is still
 * space क्रम a buffer.  Each region of larger pages will be used at
 * most once, after which the page will not be reused.
 *
 * In either हाल, अगर the page is reusable its refcount is increased.
 **/
अटल bool iavf_can_reuse_rx_page(काष्ठा iavf_rx_buffer *rx_buffer)
अणु
	अचिन्हित पूर्णांक pagecnt_bias = rx_buffer->pagecnt_bias;
	काष्ठा page *page = rx_buffer->page;

	/* Is any reuse possible? */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely((page_count(page) - pagecnt_bias) > 1))
		वापस false;
#अन्यथा
#घोषणा IAVF_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - IAVF_RXBUFFER_2048)
	अगर (rx_buffer->page_offset > IAVF_LAST_OFFSET)
		वापस false;
#पूर्ण_अगर

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	अगर (unlikely(!pagecnt_bias)) अणु
		page_ref_add(page, अच_लघु_उच्च);
		rx_buffer->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण

	वापस true;
पूर्ण

/**
 * iavf_add_rx_frag - Add contents of Rx buffer to sk_buff
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: buffer containing page to add
 * @skb: sk_buff to place the data पूर्णांकo
 * @size: packet length from rx_desc
 *
 * This function will add the data contained in rx_buffer->page to the skb.
 * It will just attach the page as a frag to the skb.
 *
 * The function will then update the page offset.
 **/
अटल व्योम iavf_add_rx_frag(काष्ठा iavf_ring *rx_ring,
			     काष्ठा iavf_rx_buffer *rx_buffer,
			     काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक size)
अणु
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = iavf_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(size + iavf_rx_offset(rx_ring));
#पूर्ण_अगर

	अगर (!size)
		वापस;

	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buffer->page,
			rx_buffer->page_offset, size, truesize);

	/* page is being used so we must update the page offset */
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

/**
 * iavf_get_rx_buffer - Fetch Rx buffer and synchronize data क्रम use
 * @rx_ring: rx descriptor ring to transact packets on
 * @size: size of buffer to add to skb
 *
 * This function will pull an Rx buffer from the ring and synchronize it
 * क्रम use by the CPU.
 */
अटल काष्ठा iavf_rx_buffer *iavf_get_rx_buffer(काष्ठा iavf_ring *rx_ring,
						 स्थिर अचिन्हित पूर्णांक size)
अणु
	काष्ठा iavf_rx_buffer *rx_buffer;

	अगर (!size)
		वापस शून्य;

	rx_buffer = &rx_ring->rx_bi[rx_ring->next_to_clean];
	prefetchw(rx_buffer->page);

	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);

	/* We have pulled a buffer क्रम use, so decrement pagecnt_bias */
	rx_buffer->pagecnt_bias--;

	वापस rx_buffer;
पूर्ण

/**
 * iavf_स्थिरruct_skb - Allocate skb and populate it
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: rx buffer to pull data from
 * @size: size of buffer to add to skb
 *
 * This function allocates an skb.  It then populates it with the page
 * data from the current receive descriptor, taking care to set up the
 * skb correctly.
 */
अटल काष्ठा sk_buff *iavf_स्थिरruct_skb(काष्ठा iavf_ring *rx_ring,
					  काष्ठा iavf_rx_buffer *rx_buffer,
					  अचिन्हित पूर्णांक size)
अणु
	व्योम *va;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = iavf_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	अचिन्हित पूर्णांक headlen;
	काष्ठा sk_buff *skb;

	अगर (!rx_buffer)
		वापस शून्य;
	/* prefetch first cache line of first page */
	va = page_address(rx_buffer->page) + rx_buffer->page_offset;
	net_prefetch(va);

	/* allocate a skb to store the frags */
	skb = __napi_alloc_skb(&rx_ring->q_vector->napi,
			       IAVF_RX_HDR_SIZE,
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* Determine available headroom क्रम copy */
	headlen = size;
	अगर (headlen > IAVF_RX_HDR_SIZE)
		headlen = eth_get_headlen(skb->dev, va, IAVF_RX_HDR_SIZE);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	स_नकल(__skb_put(skb, headlen), va, ALIGN(headlen, माप(दीर्घ)));

	/* update all of the poपूर्णांकers */
	size -= headlen;
	अगर (size) अणु
		skb_add_rx_frag(skb, 0, rx_buffer->page,
				rx_buffer->page_offset + headlen,
				size, truesize);

		/* buffer is used by skb, update page_offset */
#अगर (PAGE_SIZE < 8192)
		rx_buffer->page_offset ^= truesize;
#अन्यथा
		rx_buffer->page_offset += truesize;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* buffer is unused, reset bias back to rx_buffer */
		rx_buffer->pagecnt_bias++;
	पूर्ण

	वापस skb;
पूर्ण

/**
 * iavf_build_skb - Build skb around an existing buffer
 * @rx_ring: Rx descriptor ring to transact packets on
 * @rx_buffer: Rx buffer to pull data from
 * @size: size of buffer to add to skb
 *
 * This function builds an skb around an existing Rx buffer, taking care
 * to set up the skb correctly and aव्योम any स_नकल overhead.
 */
अटल काष्ठा sk_buff *iavf_build_skb(काष्ठा iavf_ring *rx_ring,
				      काष्ठा iavf_rx_buffer *rx_buffer,
				      अचिन्हित पूर्णांक size)
अणु
	व्योम *va;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = iavf_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
				SKB_DATA_ALIGN(IAVF_SKB_PAD + size);
#पूर्ण_अगर
	काष्ठा sk_buff *skb;

	अगर (!rx_buffer)
		वापस शून्य;
	/* prefetch first cache line of first page */
	va = page_address(rx_buffer->page) + rx_buffer->page_offset;
	net_prefetch(va);

	/* build an skb around the page buffer */
	skb = build_skb(va - IAVF_SKB_PAD, truesize);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* update poपूर्णांकers within the skb to store the data */
	skb_reserve(skb, IAVF_SKB_PAD);
	__skb_put(skb, size);

	/* buffer is used by skb, update page_offset */
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर

	वापस skb;
पूर्ण

/**
 * iavf_put_rx_buffer - Clean up used buffer and either recycle or मुक्त
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: rx buffer to pull data from
 *
 * This function will clean up the contents of the rx_buffer.  It will
 * either recycle the buffer or unmap it and मुक्त the associated resources.
 */
अटल व्योम iavf_put_rx_buffer(काष्ठा iavf_ring *rx_ring,
			       काष्ठा iavf_rx_buffer *rx_buffer)
अणु
	अगर (!rx_buffer)
		वापस;

	अगर (iavf_can_reuse_rx_page(rx_buffer)) अणु
		/* hand second half of page back to the ring */
		iavf_reuse_rx_page(rx_ring, rx_buffer);
		rx_ring->rx_stats.page_reuse_count++;
	पूर्ण अन्यथा अणु
		/* we are not reusing the buffer so unmap it */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     iavf_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE, IAVF_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	पूर्ण

	/* clear contents of buffer_info */
	rx_buffer->page = शून्य;
पूर्ण

/**
 * iavf_is_non_eop - process handling of non-EOP buffers
 * @rx_ring: Rx ring being processed
 * @rx_desc: Rx descriptor क्रम current buffer
 * @skb: Current socket buffer containing buffer in progress
 *
 * This function updates next to clean.  If the buffer is an EOP buffer
 * this function निकासs वापसing false, otherwise it will place the
 * sk_buff in the next buffer to be chained and वापस true indicating
 * that this is in fact a non-EOP buffer.
 **/
अटल bool iavf_is_non_eop(काष्ठा iavf_ring *rx_ring,
			    जोड़ iavf_rx_desc *rx_desc,
			    काष्ठा sk_buff *skb)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(IAVF_RX_DESC(rx_ring, ntc));

	/* अगर we are the last buffer then there is nothing अन्यथा to करो */
#घोषणा IAVF_RXD_खातापूर्ण BIT(IAVF_RX_DESC_STATUS_खातापूर्ण_SHIFT)
	अगर (likely(iavf_test_staterr(rx_desc, IAVF_RXD_खातापूर्ण)))
		वापस false;

	rx_ring->rx_stats.non_eop_descs++;

	वापस true;
पूर्ण

/**
 * iavf_clean_rx_irq - Clean completed descriptors from Rx ring - bounce buf
 * @rx_ring: rx descriptor ring to transact packets on
 * @budget: Total limit on number of packets to process
 *
 * This function provides a "bounce buffer" approach to Rx पूर्णांकerrupt
 * processing.  The advantage to this is that on प्रणालीs that have
 * expensive overhead क्रम IOMMU access this provides a means of aव्योमing
 * it by मुख्यtaining the mapping of the page to the प्रणाली.
 *
 * Returns amount of work completed
 **/
अटल पूर्णांक iavf_clean_rx_irq(काष्ठा iavf_ring *rx_ring, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;
	काष्ठा sk_buff *skb = rx_ring->skb;
	u16 cleaned_count = IAVF_DESC_UNUSED(rx_ring);
	bool failure = false;

	जबतक (likely(total_rx_packets < (अचिन्हित पूर्णांक)budget)) अणु
		काष्ठा iavf_rx_buffer *rx_buffer;
		जोड़ iavf_rx_desc *rx_desc;
		अचिन्हित पूर्णांक size;
		u16 vlan_tag;
		u8 rx_ptype;
		u64 qword;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= IAVF_RX_BUFFER_WRITE) अणु
			failure = failure ||
				  iavf_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = IAVF_RX_DESC(rx_ring, rx_ring->next_to_clean);

		/* status_error_len will always be zero क्रम unused descriptors
		 * because it's cleared in cleanup, and overlaps with hdr_addr
		 * which is always zero because packet split isn't used, अगर the
		 * hardware wrote DD then the length will be non-zero
		 */
		qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we have
		 * verअगरied the descriptor has been written back.
		 */
		dma_rmb();
#घोषणा IAVF_RXD_DD BIT(IAVF_RX_DESC_STATUS_DD_SHIFT)
		अगर (!iavf_test_staterr(rx_desc, IAVF_RXD_DD))
			अवरोध;

		size = (qword & IAVF_RXD_QW1_LENGTH_PBUF_MASK) >>
		       IAVF_RXD_QW1_LENGTH_PBUF_SHIFT;

		iavf_trace(clean_rx_irq, rx_ring, rx_desc, skb);
		rx_buffer = iavf_get_rx_buffer(rx_ring, size);

		/* retrieve a buffer from the ring */
		अगर (skb)
			iavf_add_rx_frag(rx_ring, rx_buffer, skb, size);
		अन्यथा अगर (ring_uses_build_skb(rx_ring))
			skb = iavf_build_skb(rx_ring, rx_buffer, size);
		अन्यथा
			skb = iavf_स्थिरruct_skb(rx_ring, rx_buffer, size);

		/* निकास अगर we failed to retrieve a buffer */
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_buff_failed++;
			अगर (rx_buffer)
				rx_buffer->pagecnt_bias++;
			अवरोध;
		पूर्ण

		iavf_put_rx_buffer(rx_ring, rx_buffer);
		cleaned_count++;

		अगर (iavf_is_non_eop(rx_ring, rx_desc, skb))
			जारी;

		/* ERR_MASK will only have valid bits अगर EOP set, and
		 * what we are करोing here is actually checking
		 * IAVF_RX_DESC_ERROR_RXE_SHIFT, since it is the zeroth bit in
		 * the error field
		 */
		अगर (unlikely(iavf_test_staterr(rx_desc, BIT(IAVF_RXD_QW1_ERROR_SHIFT)))) अणु
			dev_kमुक्त_skb_any(skb);
			skb = शून्य;
			जारी;
		पूर्ण

		अगर (iavf_cleanup_headers(rx_ring, skb)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;

		qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);
		rx_ptype = (qword & IAVF_RXD_QW1_PTYPE_MASK) >>
			   IAVF_RXD_QW1_PTYPE_SHIFT;

		/* populate checksum, VLAN, and protocol */
		iavf_process_skb_fields(rx_ring, rx_desc, skb, rx_ptype);


		vlan_tag = (qword & BIT(IAVF_RX_DESC_STATUS_L2TAG1P_SHIFT)) ?
			   le16_to_cpu(rx_desc->wb.qword0.lo_dword.l2tag1) : 0;

		iavf_trace(clean_rx_irq_rx, rx_ring, rx_desc, skb);
		iavf_receive_skb(rx_ring, skb, vlan_tag);
		skb = शून्य;

		/* update budget accounting */
		total_rx_packets++;
	पूर्ण

	rx_ring->skb = skb;

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_rx_packets;
	rx_ring->stats.bytes += total_rx_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	rx_ring->q_vector->rx.total_packets += total_rx_packets;
	rx_ring->q_vector->rx.total_bytes += total_rx_bytes;

	/* guarantee a trip back through this routine अगर there was a failure */
	वापस failure ? budget : (पूर्णांक)total_rx_packets;
पूर्ण

अटल अंतरभूत u32 iavf_buildreg_itr(स्थिर पूर्णांक type, u16 itr)
अणु
	u32 val;

	/* We करोn't bother with setting the CLEARPBA bit as the data sheet
	 * poपूर्णांकs out करोing so is "meaningless since it was alपढ़ोy
	 * स्वतः-cleared". The स्वतः-clearing happens when the पूर्णांकerrupt is
	 * निश्चितed.
	 *
	 * Hardware errata 28 क्रम also indicates that writing to a
	 * xxINT_DYN_CTLx CSR with INTENA_MSK (bit 31) set to 0 will clear
	 * an event in the PBA anyway so we need to rely on the स्वतःmask
	 * to hold pending events क्रम us until the पूर्णांकerrupt is re-enabled
	 *
	 * The itr value is reported in microseconds, and the रेजिस्टर
	 * value is recorded in 2 microsecond units. For this reason we
	 * only need to shअगरt by the पूर्णांकerval shअगरt - 1 instead of the
	 * full value.
	 */
	itr &= IAVF_ITR_MASK;

	val = IAVF_VFINT_DYN_CTLN1_INTENA_MASK |
	      (type << IAVF_VFINT_DYN_CTLN1_ITR_INDX_SHIFT) |
	      (itr << (IAVF_VFINT_DYN_CTLN1_INTERVAL_SHIFT - 1));

	वापस val;
पूर्ण

/* a small macro to लघुen up some दीर्घ lines */
#घोषणा INTREG IAVF_VFINT_DYN_CTLN1

/* The act of updating the ITR will cause it to immediately trigger. In order
 * to prevent this from throwing off adaptive update statistics we defer the
 * update so that it can only happen so often. So after either Tx or Rx are
 * updated we make the adaptive scheme रुको until either the ITR completely
 * expires via the next_update expiration or we have been through at least
 * 3 पूर्णांकerrupts.
 */
#घोषणा ITR_COUNTDOWN_START 3

/**
 * iavf_update_enable_itr - Update itr and re-enable MSIX पूर्णांकerrupt
 * @vsi: the VSI we care about
 * @q_vector: q_vector क्रम which itr is being updated and पूर्णांकerrupt enabled
 *
 **/
अटल अंतरभूत व्योम iavf_update_enable_itr(काष्ठा iavf_vsi *vsi,
					  काष्ठा iavf_q_vector *q_vector)
अणु
	काष्ठा iavf_hw *hw = &vsi->back->hw;
	u32 पूर्णांकval;

	/* These will करो nothing अगर dynamic updates are not enabled */
	iavf_update_itr(q_vector, &q_vector->tx);
	iavf_update_itr(q_vector, &q_vector->rx);

	/* This block of logic allows us to get away with only updating
	 * one ITR value with each पूर्णांकerrupt. The idea is to perक्रमm a
	 * pseuकरो-lazy update with the following criteria.
	 *
	 * 1. Rx is given higher priority than Tx अगर both are in same state
	 * 2. If we must reduce an ITR that is given highest priority.
	 * 3. We then give priority to increasing ITR based on amount.
	 */
	अगर (q_vector->rx.target_itr < q_vector->rx.current_itr) अणु
		/* Rx ITR needs to be reduced, this is highest priority */
		पूर्णांकval = iavf_buildreg_itr(IAVF_RX_ITR,
					   q_vector->rx.target_itr);
		q_vector->rx.current_itr = q_vector->rx.target_itr;
		q_vector->itr_countकरोwn = ITR_COUNTDOWN_START;
	पूर्ण अन्यथा अगर ((q_vector->tx.target_itr < q_vector->tx.current_itr) ||
		   ((q_vector->rx.target_itr - q_vector->rx.current_itr) <
		    (q_vector->tx.target_itr - q_vector->tx.current_itr))) अणु
		/* Tx ITR needs to be reduced, this is second priority
		 * Tx ITR needs to be increased more than Rx, fourth priority
		 */
		पूर्णांकval = iavf_buildreg_itr(IAVF_TX_ITR,
					   q_vector->tx.target_itr);
		q_vector->tx.current_itr = q_vector->tx.target_itr;
		q_vector->itr_countकरोwn = ITR_COUNTDOWN_START;
	पूर्ण अन्यथा अगर (q_vector->rx.current_itr != q_vector->rx.target_itr) अणु
		/* Rx ITR needs to be increased, third priority */
		पूर्णांकval = iavf_buildreg_itr(IAVF_RX_ITR,
					   q_vector->rx.target_itr);
		q_vector->rx.current_itr = q_vector->rx.target_itr;
		q_vector->itr_countकरोwn = ITR_COUNTDOWN_START;
	पूर्ण अन्यथा अणु
		/* No ITR update, lowest priority */
		पूर्णांकval = iavf_buildreg_itr(IAVF_ITR_NONE, 0);
		अगर (q_vector->itr_countकरोwn)
			q_vector->itr_countकरोwn--;
	पूर्ण

	अगर (!test_bit(__IAVF_VSI_DOWN, vsi->state))
		wr32(hw, INTREG(q_vector->reg_idx), पूर्णांकval);
पूर्ण

/**
 * iavf_napi_poll - NAPI polling Rx/Tx cleanup routine
 * @napi: napi काष्ठा with our devices info in it
 * @budget: amount of work driver is allowed to करो this pass, in packets
 *
 * This function will clean all queues associated with a q_vector.
 *
 * Returns the amount of work करोne
 **/
पूर्णांक iavf_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा iavf_q_vector *q_vector =
			       container_of(napi, काष्ठा iavf_q_vector, napi);
	काष्ठा iavf_vsi *vsi = q_vector->vsi;
	काष्ठा iavf_ring *ring;
	bool clean_complete = true;
	bool arm_wb = false;
	पूर्णांक budget_per_ring;
	पूर्णांक work_करोne = 0;

	अगर (test_bit(__IAVF_VSI_DOWN, vsi->state)) अणु
		napi_complete(napi);
		वापस 0;
	पूर्ण

	/* Since the actual Tx work is minimal, we can give the Tx a larger
	 * budget and be more aggressive about cleaning up the Tx descriptors.
	 */
	iavf_क्रम_each_ring(ring, q_vector->tx) अणु
		अगर (!iavf_clean_tx_irq(vsi, ring, budget)) अणु
			clean_complete = false;
			जारी;
		पूर्ण
		arm_wb |= ring->arm_wb;
		ring->arm_wb = false;
	पूर्ण

	/* Handle हाल where we are called by netpoll with a budget of 0 */
	अगर (budget <= 0)
		जाओ tx_only;

	/* We attempt to distribute budget to each Rx queue fairly, but करोn't
	 * allow the budget to go below 1 because that would निकास polling early.
	 */
	budget_per_ring = max(budget/q_vector->num_ringpairs, 1);

	iavf_क्रम_each_ring(ring, q_vector->rx) अणु
		पूर्णांक cleaned = iavf_clean_rx_irq(ring, budget_per_ring);

		work_करोne += cleaned;
		/* अगर we clean as many as budgeted, we must not be करोne */
		अगर (cleaned >= budget_per_ring)
			clean_complete = false;
	पूर्ण

	/* If work not completed, वापस budget and polling will वापस */
	अगर (!clean_complete) अणु
		पूर्णांक cpu_id = smp_processor_id();

		/* It is possible that the पूर्णांकerrupt affinity has changed but,
		 * अगर the cpu is pegged at 100%, polling will never निकास जबतक
		 * traffic जारीs and the पूर्णांकerrupt will be stuck on this
		 * cpu.  We check to make sure affinity is correct beक्रमe we
		 * जारी to poll, otherwise we must stop polling so the
		 * पूर्णांकerrupt can move to the correct cpu.
		 */
		अगर (!cpumask_test_cpu(cpu_id, &q_vector->affinity_mask)) अणु
			/* Tell napi that we are करोne polling */
			napi_complete_करोne(napi, work_करोne);

			/* Force an पूर्णांकerrupt */
			iavf_क्रमce_wb(vsi, q_vector);

			/* Return budget-1 so that polling stops */
			वापस budget - 1;
		पूर्ण
tx_only:
		अगर (arm_wb) अणु
			q_vector->tx.ring[0].tx_stats.tx_क्रमce_wb++;
			iavf_enable_wb_on_itr(vsi, q_vector);
		पूर्ण
		वापस budget;
	पूर्ण

	अगर (vsi->back->flags & IAVF_TXR_FLAGS_WB_ON_ITR)
		q_vector->arm_wb_state = false;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne)))
		iavf_update_enable_itr(vsi, q_vector);

	वापस min(work_करोne, budget - 1);
पूर्ण

/**
 * iavf_tx_prepare_vlan_flags - prepare generic TX VLAN tagging flags क्रम HW
 * @skb:     send buffer
 * @tx_ring: ring to send buffer on
 * @flags:   the tx flags to be set
 *
 * Checks the skb and set up correspondingly several generic transmit flags
 * related to VLAN tagging क्रम the HW, such as VLAN, DCB, etc.
 *
 * Returns error code indicate the frame should be dropped upon error and the
 * otherwise  वापसs 0 to indicate the flags has been set properly.
 **/
अटल अंतरभूत पूर्णांक iavf_tx_prepare_vlan_flags(काष्ठा sk_buff *skb,
					     काष्ठा iavf_ring *tx_ring,
					     u32 *flags)
अणु
	__be16 protocol = skb->protocol;
	u32  tx_flags = 0;

	अगर (protocol == htons(ETH_P_8021Q) &&
	    !(tx_ring->netdev->features & NETIF_F_HW_VLAN_CTAG_TX)) अणु
		/* When HW VLAN acceleration is turned off by the user the
		 * stack sets the protocol to 8021q so that the driver
		 * can take any steps required to support the SW only
		 * VLAN handling.  In our हाल the driver करोesn't need
		 * to take any further steps so just set the protocol
		 * to the encapsulated ethertype.
		 */
		skb->protocol = vlan_get_protocol(skb);
		जाओ out;
	पूर्ण

	/* अगर we have a HW VLAN tag being added, शेष to the HW one */
	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= skb_vlan_tag_get(skb) << IAVF_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= IAVF_TX_FLAGS_HW_VLAN;
	/* अन्यथा अगर it is a SW VLAN, check the next protocol and store the tag */
	पूर्ण अन्यथा अगर (protocol == htons(ETH_P_8021Q)) अणु
		काष्ठा vlan_hdr *vhdr, _vhdr;

		vhdr = skb_header_poपूर्णांकer(skb, ETH_HLEN, माप(_vhdr), &_vhdr);
		अगर (!vhdr)
			वापस -EINVAL;

		protocol = vhdr->h_vlan_encapsulated_proto;
		tx_flags |= ntohs(vhdr->h_vlan_TCI) << IAVF_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= IAVF_TX_FLAGS_SW_VLAN;
	पूर्ण

out:
	*flags = tx_flags;
	वापस 0;
पूर्ण

/**
 * iavf_tso - set up the tso context descriptor
 * @first:    poपूर्णांकer to first Tx buffer क्रम xmit
 * @hdr_len:  ptr to the size of the packet header
 * @cd_type_cmd_tso_mss: Quad Word 1
 *
 * Returns 0 अगर no TSO can happen, 1 अगर tso is going, or error
 **/
अटल पूर्णांक iavf_tso(काष्ठा iavf_tx_buffer *first, u8 *hdr_len,
		    u64 *cd_type_cmd_tso_mss)
अणु
	काष्ठा sk_buff *skb = first->skb;
	u64 cd_cmd, cd_tso_len, cd_mss;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		काष्ठा udphdr *udp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	u32 paylen, l4_offset;
	u16 gso_segs, gso_size;
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* initialize outer IP header fields */
	अगर (ip.v4->version == 4) अणु
		ip.v4->tot_len = 0;
		ip.v4->check = 0;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
	पूर्ण

	अगर (skb_shinfo(skb)->gso_type & (SKB_GSO_GRE |
					 SKB_GSO_GRE_CSUM |
					 SKB_GSO_IPXIP4 |
					 SKB_GSO_IPXIP6 |
					 SKB_GSO_UDP_TUNNEL |
					 SKB_GSO_UDP_TUNNEL_CSUM)) अणु
		अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM)) अणु
			l4.udp->len = 0;

			/* determine offset of outer transport header */
			l4_offset = l4.hdr - skb->data;

			/* हटाओ payload length from outer checksum */
			paylen = skb->len - l4_offset;
			csum_replace_by_dअगरf(&l4.udp->check,
					     (__क्रमce __wsum)htonl(paylen));
		पूर्ण

		/* reset poपूर्णांकers to inner headers */
		ip.hdr = skb_inner_network_header(skb);
		l4.hdr = skb_inner_transport_header(skb);

		/* initialize inner IP header fields */
		अगर (ip.v4->version == 4) अणु
			ip.v4->tot_len = 0;
			ip.v4->check = 0;
		पूर्ण अन्यथा अणु
			ip.v6->payload_len = 0;
		पूर्ण
	पूर्ण

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;
	/* हटाओ payload length from inner checksum */
	paylen = skb->len - l4_offset;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
		csum_replace_by_dअगरf(&l4.udp->check,
				     (__क्रमce __wsum)htonl(paylen));
		/* compute length of UDP segmentation header */
		*hdr_len = (u8)माप(l4.udp) + l4_offset;
	पूर्ण अन्यथा अणु
		csum_replace_by_dअगरf(&l4.tcp->check,
				     (__क्रमce __wsum)htonl(paylen));
		/* compute length of TCP segmentation header */
		*hdr_len = (u8)((l4.tcp->करोff * 4) + l4_offset);
	पूर्ण

	/* pull values out of skb_shinfo */
	gso_size = skb_shinfo(skb)->gso_size;
	gso_segs = skb_shinfo(skb)->gso_segs;

	/* update GSO size and bytecount with header size */
	first->gso_segs = gso_segs;
	first->bytecount += (first->gso_segs - 1) * *hdr_len;

	/* find the field values */
	cd_cmd = IAVF_TX_CTX_DESC_TSO;
	cd_tso_len = skb->len - *hdr_len;
	cd_mss = gso_size;
	*cd_type_cmd_tso_mss |= (cd_cmd << IAVF_TXD_CTX_QW1_CMD_SHIFT) |
				(cd_tso_len << IAVF_TXD_CTX_QW1_TSO_LEN_SHIFT) |
				(cd_mss << IAVF_TXD_CTX_QW1_MSS_SHIFT);
	वापस 1;
पूर्ण

/**
 * iavf_tx_enable_csum - Enable Tx checksum offloads
 * @skb: send buffer
 * @tx_flags: poपूर्णांकer to Tx flags currently set
 * @td_cmd: Tx descriptor command bits to set
 * @td_offset: Tx descriptor header offsets to set
 * @tx_ring: Tx descriptor ring
 * @cd_tunneling: ptr to context desc bits
 **/
अटल पूर्णांक iavf_tx_enable_csum(काष्ठा sk_buff *skb, u32 *tx_flags,
			       u32 *td_cmd, u32 *td_offset,
			       काष्ठा iavf_ring *tx_ring,
			       u32 *cd_tunneling)
अणु
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		काष्ठा udphdr *udp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	अचिन्हित अक्षर *exthdr;
	u32 offset, cmd = 0;
	__be16 frag_off;
	u8 l4_proto = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* compute outer L2 header size */
	offset = ((ip.hdr - skb->data) / 2) << IAVF_TX_DESC_LENGTH_MACLEN_SHIFT;

	अगर (skb->encapsulation) अणु
		u32 tunnel = 0;
		/* define outer network header type */
		अगर (*tx_flags & IAVF_TX_FLAGS_IPV4) अणु
			tunnel |= (*tx_flags & IAVF_TX_FLAGS_TSO) ?
				  IAVF_TX_CTX_EXT_IP_IPV4 :
				  IAVF_TX_CTX_EXT_IP_IPV4_NO_CSUM;

			l4_proto = ip.v4->protocol;
		पूर्ण अन्यथा अगर (*tx_flags & IAVF_TX_FLAGS_IPV6) अणु
			tunnel |= IAVF_TX_CTX_EXT_IP_IPV6;

			exthdr = ip.hdr + माप(*ip.v6);
			l4_proto = ip.v6->nexthdr;
			अगर (l4.hdr != exthdr)
				ipv6_skip_exthdr(skb, exthdr - skb->data,
						 &l4_proto, &frag_off);
		पूर्ण

		/* define outer transport */
		चयन (l4_proto) अणु
		हाल IPPROTO_UDP:
			tunnel |= IAVF_TXD_CTX_UDP_TUNNELING;
			*tx_flags |= IAVF_TX_FLAGS_VXLAN_TUNNEL;
			अवरोध;
		हाल IPPROTO_GRE:
			tunnel |= IAVF_TXD_CTX_GRE_TUNNELING;
			*tx_flags |= IAVF_TX_FLAGS_VXLAN_TUNNEL;
			अवरोध;
		हाल IPPROTO_IPIP:
		हाल IPPROTO_IPV6:
			*tx_flags |= IAVF_TX_FLAGS_VXLAN_TUNNEL;
			l4.hdr = skb_inner_network_header(skb);
			अवरोध;
		शेष:
			अगर (*tx_flags & IAVF_TX_FLAGS_TSO)
				वापस -1;

			skb_checksum_help(skb);
			वापस 0;
		पूर्ण

		/* compute outer L3 header size */
		tunnel |= ((l4.hdr - ip.hdr) / 4) <<
			  IAVF_TXD_CTX_QW0_EXT_IPLEN_SHIFT;

		/* चयन IP header poपूर्णांकer from outer to inner header */
		ip.hdr = skb_inner_network_header(skb);

		/* compute tunnel header size */
		tunnel |= ((ip.hdr - l4.hdr) / 2) <<
			  IAVF_TXD_CTX_QW0_NATLEN_SHIFT;

		/* indicate अगर we need to offload outer UDP header */
		अगर ((*tx_flags & IAVF_TX_FLAGS_TSO) &&
		    !(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM))
			tunnel |= IAVF_TXD_CTX_QW0_L4T_CS_MASK;

		/* record tunnel offload values */
		*cd_tunneling |= tunnel;

		/* चयन L4 header poपूर्णांकer from outer to inner */
		l4.hdr = skb_inner_transport_header(skb);
		l4_proto = 0;

		/* reset type as we transition from outer to inner headers */
		*tx_flags &= ~(IAVF_TX_FLAGS_IPV4 | IAVF_TX_FLAGS_IPV6);
		अगर (ip.v4->version == 4)
			*tx_flags |= IAVF_TX_FLAGS_IPV4;
		अगर (ip.v6->version == 6)
			*tx_flags |= IAVF_TX_FLAGS_IPV6;
	पूर्ण

	/* Enable IP checksum offloads */
	अगर (*tx_flags & IAVF_TX_FLAGS_IPV4) अणु
		l4_proto = ip.v4->protocol;
		/* the stack computes the IP header alपढ़ोy, the only समय we
		 * need the hardware to recompute it is in the हाल of TSO.
		 */
		cmd |= (*tx_flags & IAVF_TX_FLAGS_TSO) ?
		       IAVF_TX_DESC_CMD_IIPT_IPV4_CSUM :
		       IAVF_TX_DESC_CMD_IIPT_IPV4;
	पूर्ण अन्यथा अगर (*tx_flags & IAVF_TX_FLAGS_IPV6) अणु
		cmd |= IAVF_TX_DESC_CMD_IIPT_IPV6;

		exthdr = ip.hdr + माप(*ip.v6);
		l4_proto = ip.v6->nexthdr;
		अगर (l4.hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data,
					 &l4_proto, &frag_off);
	पूर्ण

	/* compute inner L3 header size */
	offset |= ((l4.hdr - ip.hdr) / 4) << IAVF_TX_DESC_LENGTH_IPLEN_SHIFT;

	/* Enable L4 checksum offloads */
	चयन (l4_proto) अणु
	हाल IPPROTO_TCP:
		/* enable checksum offloads */
		cmd |= IAVF_TX_DESC_CMD_L4T_खातापूर्णT_TCP;
		offset |= l4.tcp->करोff << IAVF_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		अवरोध;
	हाल IPPROTO_SCTP:
		/* enable SCTP checksum offload */
		cmd |= IAVF_TX_DESC_CMD_L4T_खातापूर्णT_SCTP;
		offset |= (माप(काष्ठा sctphdr) >> 2) <<
			  IAVF_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		अवरोध;
	हाल IPPROTO_UDP:
		/* enable UDP checksum offload */
		cmd |= IAVF_TX_DESC_CMD_L4T_खातापूर्णT_UDP;
		offset |= (माप(काष्ठा udphdr) >> 2) <<
			  IAVF_TX_DESC_LENGTH_L4_FC_LEN_SHIFT;
		अवरोध;
	शेष:
		अगर (*tx_flags & IAVF_TX_FLAGS_TSO)
			वापस -1;
		skb_checksum_help(skb);
		वापस 0;
	पूर्ण

	*td_cmd |= cmd;
	*td_offset |= offset;

	वापस 1;
पूर्ण

/**
 * iavf_create_tx_ctx - Build the Tx context descriptor
 * @tx_ring:  ring to create the descriptor on
 * @cd_type_cmd_tso_mss: Quad Word 1
 * @cd_tunneling: Quad Word 0 - bits 0-31
 * @cd_l2tag2: Quad Word 0 - bits 32-63
 **/
अटल व्योम iavf_create_tx_ctx(काष्ठा iavf_ring *tx_ring,
			       स्थिर u64 cd_type_cmd_tso_mss,
			       स्थिर u32 cd_tunneling, स्थिर u32 cd_l2tag2)
अणु
	काष्ठा iavf_tx_context_desc *context_desc;
	पूर्णांक i = tx_ring->next_to_use;

	अगर ((cd_type_cmd_tso_mss == IAVF_TX_DESC_DTYPE_CONTEXT) &&
	    !cd_tunneling && !cd_l2tag2)
		वापस;

	/* grab the next descriptor */
	context_desc = IAVF_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* cpu_to_le32 and assign to काष्ठा fields */
	context_desc->tunneling_params = cpu_to_le32(cd_tunneling);
	context_desc->l2tag2 = cpu_to_le16(cd_l2tag2);
	context_desc->rsvd = cpu_to_le16(0);
	context_desc->type_cmd_tso_mss = cpu_to_le64(cd_type_cmd_tso_mss);
पूर्ण

/**
 * __iavf_chk_linearize - Check अगर there are more than 8 buffers per packet
 * @skb:      send buffer
 *
 * Note: Our HW can't DMA more than 8 buffers to build a packet on the wire
 * and so we need to figure out the हालs where we need to linearize the skb.
 *
 * For TSO we need to count the TSO header and segment payload separately.
 * As such we need to check हालs where we have 7 fragments or more as we
 * can potentially require 9 DMA transactions, 1 क्रम the TSO header, 1 क्रम
 * the segment payload in the first descriptor, and another 7 क्रम the
 * fragments.
 **/
bool __iavf_chk_linearize(काष्ठा sk_buff *skb)
अणु
	स्थिर skb_frag_t *frag, *stale;
	पूर्णांक nr_frags, sum;

	/* no need to check अगर number of frags is less than 7 */
	nr_frags = skb_shinfo(skb)->nr_frags;
	अगर (nr_frags < (IAVF_MAX_BUFFER_TXD - 1))
		वापस false;

	/* We need to walk through the list and validate that each group
	 * of 6 fragments totals at least gso_size.
	 */
	nr_frags -= IAVF_MAX_BUFFER_TXD - 2;
	frag = &skb_shinfo(skb)->frags[0];

	/* Initialize size to the negative value of gso_size minus 1.  We
	 * use this as the worst हाल scenerio in which the frag ahead
	 * of us only provides one byte which is why we are limited to 6
	 * descriptors क्रम a single transmit as the header and previous
	 * fragment are alपढ़ोy consuming 2 descriptors.
	 */
	sum = 1 - skb_shinfo(skb)->gso_size;

	/* Add size of frags 0 through 4 to create our initial sum */
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);

	/* Walk through fragments adding latest fragment, testing it, and
	 * then removing stale fragments from the sum.
	 */
	क्रम (stale = &skb_shinfo(skb)->frags[0];; stale++) अणु
		पूर्णांक stale_size = skb_frag_size(stale);

		sum += skb_frag_size(frag++);

		/* The stale fragment may present us with a smaller
		 * descriptor than the actual fragment size. To account
		 * क्रम that we need to हटाओ all the data on the front and
		 * figure out what the reमुख्यder would be in the last
		 * descriptor associated with the fragment.
		 */
		अगर (stale_size > IAVF_MAX_DATA_PER_TXD) अणु
			पूर्णांक align_pad = -(skb_frag_off(stale)) &
					(IAVF_MAX_READ_REQ_SIZE - 1);

			sum -= align_pad;
			stale_size -= align_pad;

			करो अणु
				sum -= IAVF_MAX_DATA_PER_TXD_ALIGNED;
				stale_size -= IAVF_MAX_DATA_PER_TXD_ALIGNED;
			पूर्ण जबतक (stale_size > IAVF_MAX_DATA_PER_TXD);
		पूर्ण

		/* अगर sum is negative we failed to make sufficient progress */
		अगर (sum < 0)
			वापस true;

		अगर (!nr_frags--)
			अवरोध;

		sum -= stale_size;
	पूर्ण

	वापस false;
पूर्ण

/**
 * __iavf_maybe_stop_tx - 2nd level check क्रम tx stop conditions
 * @tx_ring: the ring to be checked
 * @size:    the size buffer we want to assure is available
 *
 * Returns -EBUSY अगर a stop is needed, अन्यथा 0
 **/
पूर्णांक __iavf_maybe_stop_tx(काष्ठा iavf_ring *tx_ring, पूर्णांक size)
अणु
	netअगर_stop_subqueue(tx_ring->netdev, tx_ring->queue_index);
	/* Memory barrier beक्रमe checking head and tail */
	smp_mb();

	/* Check again in a हाल another CPU has just made room available. */
	अगर (likely(IAVF_DESC_UNUSED(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! - use start_queue because it करोesn't call schedule */
	netअगर_start_subqueue(tx_ring->netdev, tx_ring->queue_index);
	++tx_ring->tx_stats.restart_queue;
	वापस 0;
पूर्ण

/**
 * iavf_tx_map - Build the Tx descriptor
 * @tx_ring:  ring to send buffer on
 * @skb:      send buffer
 * @first:    first buffer info buffer to use
 * @tx_flags: collected send inक्रमmation
 * @hdr_len:  size of the packet header
 * @td_cmd:   the command field in the descriptor
 * @td_offset: offset क्रम checksum or crc
 **/
अटल अंतरभूत व्योम iavf_tx_map(काष्ठा iavf_ring *tx_ring, काष्ठा sk_buff *skb,
			       काष्ठा iavf_tx_buffer *first, u32 tx_flags,
			       स्थिर u8 hdr_len, u32 td_cmd, u32 td_offset)
अणु
	अचिन्हित पूर्णांक data_len = skb->data_len;
	अचिन्हित पूर्णांक size = skb_headlen(skb);
	skb_frag_t *frag;
	काष्ठा iavf_tx_buffer *tx_bi;
	काष्ठा iavf_tx_desc *tx_desc;
	u16 i = tx_ring->next_to_use;
	u32 td_tag = 0;
	dma_addr_t dma;

	अगर (tx_flags & IAVF_TX_FLAGS_HW_VLAN) अणु
		td_cmd |= IAVF_TX_DESC_CMD_IL2TAG1;
		td_tag = (tx_flags & IAVF_TX_FLAGS_VLAN_MASK) >>
			 IAVF_TX_FLAGS_VLAN_SHIFT;
	पूर्ण

	first->tx_flags = tx_flags;

	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_desc = IAVF_TX_DESC(tx_ring, i);
	tx_bi = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अचिन्हित पूर्णांक max_data = IAVF_MAX_DATA_PER_TXD_ALIGNED;

		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_bi, len, size);
		dma_unmap_addr_set(tx_bi, dma, dma);

		/* align size to end of page */
		max_data += -dma & (IAVF_MAX_READ_REQ_SIZE - 1);
		tx_desc->buffer_addr = cpu_to_le64(dma);

		जबतक (unlikely(size > IAVF_MAX_DATA_PER_TXD)) अणु
			tx_desc->cmd_type_offset_bsz =
				build_ctob(td_cmd, td_offset,
					   max_data, td_tag);

			tx_desc++;
			i++;

			अगर (i == tx_ring->count) अणु
				tx_desc = IAVF_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण

			dma += max_data;
			size -= max_data;

			max_data = IAVF_MAX_DATA_PER_TXD_ALIGNED;
			tx_desc->buffer_addr = cpu_to_le64(dma);
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		tx_desc->cmd_type_offset_bsz = build_ctob(td_cmd, td_offset,
							  size, td_tag);

		tx_desc++;
		i++;

		अगर (i == tx_ring->count) अणु
			tx_desc = IAVF_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_bi = &tx_ring->tx_bi[i];
	पूर्ण

	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	i++;
	अगर (i == tx_ring->count)
		i = 0;

	tx_ring->next_to_use = i;

	iavf_maybe_stop_tx(tx_ring, DESC_NEEDED);

	/* ग_लिखो last descriptor with RS and EOP bits */
	td_cmd |= IAVF_TXD_CMD;
	tx_desc->cmd_type_offset_bsz =
			build_ctob(td_cmd, td_offset, size, td_tag);

	skb_tx_बारtamp(skb);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.
	 *
	 * We also use this memory barrier to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	/* notअगरy HW of packet */
	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more()) अणु
		ग_लिखोl(i, tx_ring->tail);
	पूर्ण

	वापस;

dma_error:
	dev_info(tx_ring->dev, "TX DMA map failed\n");

	/* clear dma mappings क्रम failed tx_bi map */
	क्रम (;;) अणु
		tx_bi = &tx_ring->tx_bi[i];
		iavf_unmap_and_मुक्त_tx_resource(tx_ring, tx_bi);
		अगर (tx_bi == first)
			अवरोध;
		अगर (i == 0)
			i = tx_ring->count;
		i--;
	पूर्ण

	tx_ring->next_to_use = i;
पूर्ण

/**
 * iavf_xmit_frame_ring - Sends buffer on Tx ring
 * @skb:     send buffer
 * @tx_ring: ring to send buffer on
 *
 * Returns NETDEV_TX_OK अगर sent, अन्यथा an error code
 **/
अटल netdev_tx_t iavf_xmit_frame_ring(काष्ठा sk_buff *skb,
					काष्ठा iavf_ring *tx_ring)
अणु
	u64 cd_type_cmd_tso_mss = IAVF_TX_DESC_DTYPE_CONTEXT;
	u32 cd_tunneling = 0, cd_l2tag2 = 0;
	काष्ठा iavf_tx_buffer *first;
	u32 td_offset = 0;
	u32 tx_flags = 0;
	__be16 protocol;
	u32 td_cmd = 0;
	u8 hdr_len = 0;
	पूर्णांक tso, count;

	/* prefetch the data, we'll need it later */
	prefetch(skb->data);

	iavf_trace(xmit_frame_ring, skb, tx_ring);

	count = iavf_xmit_descriptor_count(skb);
	अगर (iavf_chk_linearize(skb, count)) अणु
		अगर (__skb_linearize(skb)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
		count = iavf_txd_use_count(skb->len);
		tx_ring->tx_stats.tx_linearize++;
	पूर्ण

	/* need: 1 descriptor per page * PAGE_SIZE/IAVF_MAX_DATA_PER_TXD,
	 *       + 1 desc क्रम skb_head_len/IAVF_MAX_DATA_PER_TXD,
	 *       + 4 desc gap to aव्योम the cache line where head is,
	 *       + 1 desc क्रम context descriptor,
	 * otherwise try next समय
	 */
	अगर (iavf_maybe_stop_tx(tx_ring, count + 4 + 1)) अणु
		tx_ring->tx_stats.tx_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_bi[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	/* prepare the xmit flags */
	अगर (iavf_tx_prepare_vlan_flags(skb, tx_ring, &tx_flags))
		जाओ out_drop;

	/* obtain protocol of skb */
	protocol = vlan_get_protocol(skb);

	/* setup IPv4/IPv6 offloads */
	अगर (protocol == htons(ETH_P_IP))
		tx_flags |= IAVF_TX_FLAGS_IPV4;
	अन्यथा अगर (protocol == htons(ETH_P_IPV6))
		tx_flags |= IAVF_TX_FLAGS_IPV6;

	tso = iavf_tso(first, &hdr_len, &cd_type_cmd_tso_mss);

	अगर (tso < 0)
		जाओ out_drop;
	अन्यथा अगर (tso)
		tx_flags |= IAVF_TX_FLAGS_TSO;

	/* Always offload the checksum, since it's in the data descriptor */
	tso = iavf_tx_enable_csum(skb, &tx_flags, &td_cmd, &td_offset,
				  tx_ring, &cd_tunneling);
	अगर (tso < 0)
		जाओ out_drop;

	/* always enable CRC insertion offload */
	td_cmd |= IAVF_TX_DESC_CMD_ICRC;

	iavf_create_tx_ctx(tx_ring, cd_type_cmd_tso_mss,
			   cd_tunneling, cd_l2tag2);

	iavf_tx_map(tx_ring, skb, first, tx_flags, hdr_len,
		    td_cmd, td_offset);

	वापस NETDEV_TX_OK;

out_drop:
	iavf_trace(xmit_frame_ring_drop, first->skb, tx_ring);
	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * iavf_xmit_frame - Selects the correct VSI and Tx queue to send buffer
 * @skb:    send buffer
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns NETDEV_TX_OK अगर sent, अन्यथा an error code
 **/
netdev_tx_t iavf_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा iavf_adapter *adapter = netdev_priv(netdev);
	काष्ठा iavf_ring *tx_ring = &adapter->tx_rings[skb->queue_mapping];

	/* hardware can't handle really लघु frames, hardware padding works
	 * beyond this poपूर्णांक
	 */
	अगर (unlikely(skb->len < IAVF_MIN_TX_LEN)) अणु
		अगर (skb_pad(skb, IAVF_MIN_TX_LEN - skb->len))
			वापस NETDEV_TX_OK;
		skb->len = IAVF_MIN_TX_LEN;
		skb_set_tail_poपूर्णांकer(skb, IAVF_MIN_TX_LEN);
	पूर्ण

	वापस iavf_xmit_frame_ring(skb, tx_ring);
पूर्ण
