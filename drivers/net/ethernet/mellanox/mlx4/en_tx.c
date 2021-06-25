<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <यंत्र/page.h>
#समावेश <linux/mlx4/cq.h>
#समावेश <linux/slab.h>
#समावेश <linux/mlx4/qp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश "mlx4_en.h"

पूर्णांक mlx4_en_create_tx_ring(काष्ठा mlx4_en_priv *priv,
			   काष्ठा mlx4_en_tx_ring **pring, u32 size,
			   u16 stride, पूर्णांक node, पूर्णांक queue_index)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_tx_ring *ring;
	पूर्णांक पंचांगp;
	पूर्णांक err;

	ring = kzalloc_node(माप(*ring), GFP_KERNEL, node);
	अगर (!ring) अणु
		en_err(priv, "Failed allocating TX ring\n");
		वापस -ENOMEM;
	पूर्ण

	ring->size = size;
	ring->size_mask = size - 1;
	ring->sp_stride = stride;
	ring->full_size = ring->size - HEADROOM - MAX_DESC_TXBBS;

	पंचांगp = size * माप(काष्ठा mlx4_en_tx_info);
	ring->tx_info = kvदो_स्मृति_node(पंचांगp, GFP_KERNEL, node);
	अगर (!ring->tx_info) अणु
		err = -ENOMEM;
		जाओ err_ring;
	पूर्ण

	en_dbg(DRV, priv, "Allocated tx_info ring at addr:%p size:%d\n",
		 ring->tx_info, पंचांगp);

	ring->bounce_buf = kदो_स्मृति_node(MAX_DESC_SIZE, GFP_KERNEL, node);
	अगर (!ring->bounce_buf) अणु
		ring->bounce_buf = kदो_स्मृति(MAX_DESC_SIZE, GFP_KERNEL);
		अगर (!ring->bounce_buf) अणु
			err = -ENOMEM;
			जाओ err_info;
		पूर्ण
	पूर्ण
	ring->buf_size = ALIGN(size * ring->sp_stride, MLX4_EN_PAGE_SIZE);

	/* Allocate HW buffers on provided NUMA node */
	set_dev_node(&mdev->dev->persist->pdev->dev, node);
	err = mlx4_alloc_hwq_res(mdev->dev, &ring->sp_wqres, ring->buf_size);
	set_dev_node(&mdev->dev->persist->pdev->dev, mdev->dev->numa_node);
	अगर (err) अणु
		en_err(priv, "Failed allocating hwq resources\n");
		जाओ err_bounce;
	पूर्ण

	ring->buf = ring->sp_wqres.buf.direct.buf;

	en_dbg(DRV, priv, "Allocated TX ring (addr:%p) - buf:%p size:%d buf_size:%d dma:%llx\n",
	       ring, ring->buf, ring->size, ring->buf_size,
	       (अचिन्हित दीर्घ दीर्घ) ring->sp_wqres.buf.direct.map);

	err = mlx4_qp_reserve_range(mdev->dev, 1, 1, &ring->qpn,
				    MLX4_RESERVE_ETH_BF_QP,
				    MLX4_RES_USAGE_DRIVER);
	अगर (err) अणु
		en_err(priv, "failed reserving qp for TX ring\n");
		जाओ err_hwq_res;
	पूर्ण

	err = mlx4_qp_alloc(mdev->dev, ring->qpn, &ring->sp_qp);
	अगर (err) अणु
		en_err(priv, "Failed allocating qp %d\n", ring->qpn);
		जाओ err_reserve;
	पूर्ण
	ring->sp_qp.event = mlx4_en_sqp_event;

	err = mlx4_bf_alloc(mdev->dev, &ring->bf, node);
	अगर (err) अणु
		en_dbg(DRV, priv, "working without blueflame (%d)\n", err);
		ring->bf.uar = &mdev->priv_uar;
		ring->bf.uar->map = mdev->uar_map;
		ring->bf_enabled = false;
		ring->bf_alloced = false;
		priv->pflags &= ~MLX4_EN_PRIV_FLAGS_BLUEFLAME;
	पूर्ण अन्यथा अणु
		ring->bf_alloced = true;
		ring->bf_enabled = !!(priv->pflags &
				      MLX4_EN_PRIV_FLAGS_BLUEFLAME);
	पूर्ण

	ring->hwtstamp_tx_type = priv->hwtstamp_config.tx_type;
	ring->queue_index = queue_index;

	अगर (queue_index < priv->num_tx_rings_p_up)
		cpumask_set_cpu(cpumask_local_spपढ़ो(queue_index,
						     priv->mdev->dev->numa_node),
				&ring->sp_affinity_mask);

	*pring = ring;
	वापस 0;

err_reserve:
	mlx4_qp_release_range(mdev->dev, ring->qpn, 1);
err_hwq_res:
	mlx4_मुक्त_hwq_res(mdev->dev, &ring->sp_wqres, ring->buf_size);
err_bounce:
	kमुक्त(ring->bounce_buf);
	ring->bounce_buf = शून्य;
err_info:
	kvमुक्त(ring->tx_info);
	ring->tx_info = शून्य;
err_ring:
	kमुक्त(ring);
	*pring = शून्य;
	वापस err;
पूर्ण

व्योम mlx4_en_destroy_tx_ring(काष्ठा mlx4_en_priv *priv,
			     काष्ठा mlx4_en_tx_ring **pring)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_tx_ring *ring = *pring;
	en_dbg(DRV, priv, "Destroying tx ring, qpn: %d\n", ring->qpn);

	अगर (ring->bf_alloced)
		mlx4_bf_मुक्त(mdev->dev, &ring->bf);
	mlx4_qp_हटाओ(mdev->dev, &ring->sp_qp);
	mlx4_qp_मुक्त(mdev->dev, &ring->sp_qp);
	mlx4_qp_release_range(priv->mdev->dev, ring->qpn, 1);
	mlx4_मुक्त_hwq_res(mdev->dev, &ring->sp_wqres, ring->buf_size);
	kमुक्त(ring->bounce_buf);
	ring->bounce_buf = शून्य;
	kvमुक्त(ring->tx_info);
	ring->tx_info = शून्य;
	kमुक्त(ring);
	*pring = शून्य;
पूर्ण

पूर्णांक mlx4_en_activate_tx_ring(काष्ठा mlx4_en_priv *priv,
			     काष्ठा mlx4_en_tx_ring *ring,
			     पूर्णांक cq, पूर्णांक user_prio)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err;

	ring->sp_cqn = cq;
	ring->prod = 0;
	ring->cons = 0xffffffff;
	ring->last_nr_txbb = 1;
	स_रखो(ring->tx_info, 0, ring->size * माप(काष्ठा mlx4_en_tx_info));
	स_रखो(ring->buf, 0, ring->buf_size);
	ring->मुक्त_tx_desc = mlx4_en_मुक्त_tx_desc;

	ring->sp_qp_state = MLX4_QP_STATE_RST;
	ring->करोorbell_qpn = cpu_to_be32(ring->sp_qp.qpn << 8);
	ring->mr_key = cpu_to_be32(mdev->mr.key);

	mlx4_en_fill_qp_context(priv, ring->size, ring->sp_stride, 1, 0, ring->qpn,
				ring->sp_cqn, user_prio, &ring->sp_context);
	अगर (ring->bf_alloced)
		ring->sp_context.usr_page =
			cpu_to_be32(mlx4_to_hw_uar_index(mdev->dev,
							 ring->bf.uar->index));

	err = mlx4_qp_to_पढ़ोy(mdev->dev, &ring->sp_wqres.mtt, &ring->sp_context,
			       &ring->sp_qp, &ring->sp_qp_state);
	अगर (!cpumask_empty(&ring->sp_affinity_mask))
		netअगर_set_xps_queue(priv->dev, &ring->sp_affinity_mask,
				    ring->queue_index);

	वापस err;
पूर्ण

व्योम mlx4_en_deactivate_tx_ring(काष्ठा mlx4_en_priv *priv,
				काष्ठा mlx4_en_tx_ring *ring)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;

	mlx4_qp_modअगरy(mdev->dev, शून्य, ring->sp_qp_state,
		       MLX4_QP_STATE_RST, शून्य, 0, 0, &ring->sp_qp);
पूर्ण

अटल अंतरभूत bool mlx4_en_is_tx_ring_full(काष्ठा mlx4_en_tx_ring *ring)
अणु
	वापस ring->prod - ring->cons > ring->full_size;
पूर्ण

अटल व्योम mlx4_en_stamp_wqe(काष्ठा mlx4_en_priv *priv,
			      काष्ठा mlx4_en_tx_ring *ring, पूर्णांक index,
			      u8 owner)
अणु
	__be32 stamp = cpu_to_be32(STAMP_VAL | (!!owner << STAMP_SHIFT));
	काष्ठा mlx4_en_tx_desc *tx_desc = ring->buf + (index << LOG_TXBB_SIZE);
	काष्ठा mlx4_en_tx_info *tx_info = &ring->tx_info[index];
	व्योम *end = ring->buf + ring->buf_size;
	__be32 *ptr = (__be32 *)tx_desc;
	पूर्णांक i;

	/* Optimize the common हाल when there are no wraparounds */
	अगर (likely((व्योम *)tx_desc +
		   (tx_info->nr_txbb << LOG_TXBB_SIZE) <= end)) अणु
		/* Stamp the मुक्तd descriptor */
		क्रम (i = 0; i < tx_info->nr_txbb << LOG_TXBB_SIZE;
		     i += STAMP_STRIDE) अणु
			*ptr = stamp;
			ptr += STAMP_DWORDS;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Stamp the मुक्तd descriptor */
		क्रम (i = 0; i < tx_info->nr_txbb << LOG_TXBB_SIZE;
		     i += STAMP_STRIDE) अणु
			*ptr = stamp;
			ptr += STAMP_DWORDS;
			अगर ((व्योम *)ptr >= end) अणु
				ptr = ring->buf;
				stamp ^= cpu_to_be32(0x80000000);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

INसूचीECT_CALLABLE_DECLARE(u32 mlx4_en_मुक्त_tx_desc(काष्ठा mlx4_en_priv *priv,
						   काष्ठा mlx4_en_tx_ring *ring,
						   पूर्णांक index, u64 बारtamp,
						   पूर्णांक napi_mode));

u32 mlx4_en_मुक्त_tx_desc(काष्ठा mlx4_en_priv *priv,
			 काष्ठा mlx4_en_tx_ring *ring,
			 पूर्णांक index, u64 बारtamp,
			 पूर्णांक napi_mode)
अणु
	काष्ठा mlx4_en_tx_info *tx_info = &ring->tx_info[index];
	काष्ठा mlx4_en_tx_desc *tx_desc = ring->buf + (index << LOG_TXBB_SIZE);
	काष्ठा mlx4_wqe_data_seg *data = (व्योम *) tx_desc + tx_info->data_offset;
	व्योम *end = ring->buf + ring->buf_size;
	काष्ठा sk_buff *skb = tx_info->skb;
	पूर्णांक nr_maps = tx_info->nr_maps;
	पूर्णांक i;

	/* We करो not touch skb here, so prefetch skb->users location
	 * to speedup consume_skb()
	 */
	prefetchw(&skb->users);

	अगर (unlikely(बारtamp)) अणु
		काष्ठा skb_shared_hwtstamps hwts;

		mlx4_en_fill_hwtstamps(priv->mdev, &hwts, बारtamp);
		skb_tstamp_tx(skb, &hwts);
	पूर्ण

	अगर (!tx_info->inl) अणु
		अगर (tx_info->linear)
			dma_unmap_single(priv->ddev,
					 tx_info->map0_dma,
					 tx_info->map0_byte_count,
					 PCI_DMA_TODEVICE);
		अन्यथा
			dma_unmap_page(priv->ddev,
				       tx_info->map0_dma,
				       tx_info->map0_byte_count,
				       PCI_DMA_TODEVICE);
		/* Optimize the common हाल when there are no wraparounds */
		अगर (likely((व्योम *)tx_desc +
			   (tx_info->nr_txbb << LOG_TXBB_SIZE) <= end)) अणु
			क्रम (i = 1; i < nr_maps; i++) अणु
				data++;
				dma_unmap_page(priv->ddev,
					(dma_addr_t)be64_to_cpu(data->addr),
					be32_to_cpu(data->byte_count),
					PCI_DMA_TODEVICE);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((व्योम *)data >= end)
				data = ring->buf + ((व्योम *)data - end);

			क्रम (i = 1; i < nr_maps; i++) अणु
				data++;
				/* Check क्रम wraparound beक्रमe unmapping */
				अगर ((व्योम *) data >= end)
					data = ring->buf;
				dma_unmap_page(priv->ddev,
					(dma_addr_t)be64_to_cpu(data->addr),
					be32_to_cpu(data->byte_count),
					PCI_DMA_TODEVICE);
			पूर्ण
		पूर्ण
	पूर्ण
	napi_consume_skb(skb, napi_mode);

	वापस tx_info->nr_txbb;
पूर्ण

INसूचीECT_CALLABLE_DECLARE(u32 mlx4_en_recycle_tx_desc(काष्ठा mlx4_en_priv *priv,
						      काष्ठा mlx4_en_tx_ring *ring,
						      पूर्णांक index, u64 बारtamp,
						      पूर्णांक napi_mode));

u32 mlx4_en_recycle_tx_desc(काष्ठा mlx4_en_priv *priv,
			    काष्ठा mlx4_en_tx_ring *ring,
			    पूर्णांक index, u64 बारtamp,
			    पूर्णांक napi_mode)
अणु
	काष्ठा mlx4_en_tx_info *tx_info = &ring->tx_info[index];
	काष्ठा mlx4_en_rx_alloc frame = अणु
		.page = tx_info->page,
		.dma = tx_info->map0_dma,
	पूर्ण;

	अगर (!napi_mode || !mlx4_en_rx_recycle(ring->recycle_ring, &frame)) अणु
		dma_unmap_page(priv->ddev, tx_info->map0_dma,
			       PAGE_SIZE, priv->dma_dir);
		put_page(tx_info->page);
	पूर्ण

	वापस tx_info->nr_txbb;
पूर्ण

पूर्णांक mlx4_en_मुक्त_tx_buf(काष्ठा net_device *dev, काष्ठा mlx4_en_tx_ring *ring)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक cnt = 0;

	/* Skip last polled descriptor */
	ring->cons += ring->last_nr_txbb;
	en_dbg(DRV, priv, "Freeing Tx buf - cons:0x%x prod:0x%x\n",
		 ring->cons, ring->prod);

	अगर ((u32) (ring->prod - ring->cons) > ring->size) अणु
		अगर (netअगर_msg_tx_err(priv))
			en_warn(priv, "Tx consumer passed producer!\n");
		वापस 0;
	पूर्ण

	जबतक (ring->cons != ring->prod) अणु
		ring->last_nr_txbb = ring->मुक्त_tx_desc(priv, ring,
						ring->cons & ring->size_mask,
						0, 0 /* Non-NAPI caller */);
		ring->cons += ring->last_nr_txbb;
		cnt++;
	पूर्ण

	अगर (ring->tx_queue)
		netdev_tx_reset_queue(ring->tx_queue);

	अगर (cnt)
		en_dbg(DRV, priv, "Freed %d uncompleted tx descriptors\n", cnt);

	वापस cnt;
पूर्ण

अटल व्योम mlx4_en_handle_err_cqe(काष्ठा mlx4_en_priv *priv, काष्ठा mlx4_err_cqe *err_cqe,
				   u16 cqe_index, काष्ठा mlx4_en_tx_ring *ring)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_tx_info *tx_info;
	काष्ठा mlx4_en_tx_desc *tx_desc;
	u16 wqe_index;
	पूर्णांक desc_size;

	en_err(priv, "CQE error - cqn 0x%x, ci 0x%x, vendor syndrome: 0x%x syndrome: 0x%x\n",
	       ring->sp_cqn, cqe_index, err_cqe->venकरोr_err_syndrome, err_cqe->syndrome);
	prपूर्णांक_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1, err_cqe, माप(*err_cqe),
		       false);

	wqe_index = be16_to_cpu(err_cqe->wqe_index) & ring->size_mask;
	tx_info = &ring->tx_info[wqe_index];
	desc_size = tx_info->nr_txbb << LOG_TXBB_SIZE;
	en_err(priv, "Related WQE - qpn 0x%x, wqe index 0x%x, wqe size 0x%x\n", ring->qpn,
	       wqe_index, desc_size);
	tx_desc = ring->buf + (wqe_index << LOG_TXBB_SIZE);
	prपूर्णांक_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1, tx_desc, desc_size, false);

	अगर (test_and_set_bit(MLX4_EN_STATE_FLAG_RESTARTING, &priv->state))
		वापस;

	en_err(priv, "Scheduling port restart\n");
	queue_work(mdev->workqueue, &priv->restart_task);
पूर्ण

पूर्णांक mlx4_en_process_tx_cq(काष्ठा net_device *dev,
			  काष्ठा mlx4_en_cq *cq, पूर्णांक napi_budget)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_cq *mcq = &cq->mcq;
	काष्ठा mlx4_en_tx_ring *ring = priv->tx_ring[cq->type][cq->ring];
	काष्ठा mlx4_cqe *cqe;
	u16 index, ring_index, stamp_index;
	u32 txbbs_skipped = 0;
	u32 txbbs_stamp = 0;
	u32 cons_index = mcq->cons_index;
	पूर्णांक size = cq->size;
	u32 size_mask = ring->size_mask;
	काष्ठा mlx4_cqe *buf = cq->buf;
	u32 packets = 0;
	u32 bytes = 0;
	पूर्णांक factor = priv->cqe_factor;
	पूर्णांक करोne = 0;
	पूर्णांक budget = priv->tx_work_limit;
	u32 last_nr_txbb;
	u32 ring_cons;

	अगर (unlikely(!priv->port_up))
		वापस 0;

	netdev_txq_bql_complete_prefetchw(ring->tx_queue);

	index = cons_index & size_mask;
	cqe = mlx4_en_get_cqe(buf, index, priv->cqe_size) + factor;
	last_nr_txbb = READ_ONCE(ring->last_nr_txbb);
	ring_cons = READ_ONCE(ring->cons);
	ring_index = ring_cons & size_mask;
	stamp_index = ring_index;

	/* Process all completed CQEs */
	जबतक (XNOR(cqe->owner_sr_opcode & MLX4_CQE_OWNER_MASK,
			cons_index & size) && (करोne < budget)) अणु
		u16 new_index;

		/*
		 * make sure we पढ़ो the CQE after we पढ़ो the
		 * ownership bit
		 */
		dma_rmb();

		अगर (unlikely((cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) ==
			     MLX4_CQE_OPCODE_ERROR))
			अगर (!test_and_set_bit(MLX4_EN_TX_RING_STATE_RECOVERING, &ring->state))
				mlx4_en_handle_err_cqe(priv, (काष्ठा mlx4_err_cqe *)cqe, index,
						       ring);

		/* Skip over last polled CQE */
		new_index = be16_to_cpu(cqe->wqe_index) & size_mask;

		करो अणु
			u64 बारtamp = 0;

			txbbs_skipped += last_nr_txbb;
			ring_index = (ring_index + last_nr_txbb) & size_mask;

			अगर (unlikely(ring->tx_info[ring_index].ts_requested))
				बारtamp = mlx4_en_get_cqe_ts(cqe);

			/* मुक्त next descriptor */
			last_nr_txbb = INसूचीECT_CALL_2(ring->मुक्त_tx_desc,
						       mlx4_en_मुक्त_tx_desc,
						       mlx4_en_recycle_tx_desc,
					priv, ring, ring_index,
					बारtamp, napi_budget);

			mlx4_en_stamp_wqe(priv, ring, stamp_index,
					  !!((ring_cons + txbbs_stamp) &
						ring->size));
			stamp_index = ring_index;
			txbbs_stamp = txbbs_skipped;
			packets++;
			bytes += ring->tx_info[ring_index].nr_bytes;
		पूर्ण जबतक ((++करोne < budget) && (ring_index != new_index));

		++cons_index;
		index = cons_index & size_mask;
		cqe = mlx4_en_get_cqe(buf, index, priv->cqe_size) + factor;
	पूर्ण

	/*
	 * To prevent CQ overflow we first update CQ consumer and only then
	 * the ring consumer.
	 */
	mcq->cons_index = cons_index;
	mlx4_cq_set_ci(mcq);
	wmb();

	/* we want to dirty this cache line once */
	WRITE_ONCE(ring->last_nr_txbb, last_nr_txbb);
	WRITE_ONCE(ring->cons, ring_cons + txbbs_skipped);

	अगर (cq->type == TX_XDP)
		वापस करोne;

	netdev_tx_completed_queue(ring->tx_queue, packets, bytes);

	/* Wakeup Tx queue अगर this stopped, and ring is not full.
	 */
	अगर (netअगर_tx_queue_stopped(ring->tx_queue) &&
	    !mlx4_en_is_tx_ring_full(ring)) अणु
		netअगर_tx_wake_queue(ring->tx_queue);
		ring->wake_queue++;
	पूर्ण

	वापस करोne;
पूर्ण

व्योम mlx4_en_tx_irq(काष्ठा mlx4_cq *mcq)
अणु
	काष्ठा mlx4_en_cq *cq = container_of(mcq, काष्ठा mlx4_en_cq, mcq);
	काष्ठा mlx4_en_priv *priv = netdev_priv(cq->dev);

	अगर (likely(priv->port_up))
		napi_schedule_irqoff(&cq->napi);
	अन्यथा
		mlx4_en_arm_cq(priv, cq);
पूर्ण

/* TX CQ polling - called by NAPI */
पूर्णांक mlx4_en_poll_tx_cq(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mlx4_en_cq *cq = container_of(napi, काष्ठा mlx4_en_cq, napi);
	काष्ठा net_device *dev = cq->dev;
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक work_करोne;

	work_करोne = mlx4_en_process_tx_cq(dev, cq, budget);
	अगर (work_करोne >= budget)
		वापस budget;

	अगर (napi_complete_करोne(napi, work_करोne))
		mlx4_en_arm_cq(priv, cq);

	वापस 0;
पूर्ण

अटल काष्ठा mlx4_en_tx_desc *mlx4_en_bounce_to_desc(काष्ठा mlx4_en_priv *priv,
						      काष्ठा mlx4_en_tx_ring *ring,
						      u32 index,
						      अचिन्हित पूर्णांक desc_size)
अणु
	u32 copy = (ring->size - index) << LOG_TXBB_SIZE;
	पूर्णांक i;

	क्रम (i = desc_size - copy - 4; i >= 0; i -= 4) अणु
		अगर ((i & (TXBB_SIZE - 1)) == 0)
			wmb();

		*((u32 *) (ring->buf + i)) =
			*((u32 *) (ring->bounce_buf + copy + i));
	पूर्ण

	क्रम (i = copy - 4; i >= 4 ; i -= 4) अणु
		अगर ((i & (TXBB_SIZE - 1)) == 0)
			wmb();

		*((u32 *)(ring->buf + (index << LOG_TXBB_SIZE) + i)) =
			*((u32 *) (ring->bounce_buf + i));
	पूर्ण

	/* Return real descriptor location */
	वापस ring->buf + (index << LOG_TXBB_SIZE);
पूर्ण

/* Decide अगर skb can be अंतरभूतd in tx descriptor to aव्योम dma mapping
 *
 * It seems strange we करो not simply use skb_copy_bits().
 * This would allow to अंतरभूत all skbs अगरf skb->len <= अंतरभूत_thold
 *
 * Note that caller alपढ़ोy checked skb was not a gso packet
 */
अटल bool is_अंतरभूत(पूर्णांक अंतरभूत_thold, स्थिर काष्ठा sk_buff *skb,
		      स्थिर काष्ठा skb_shared_info *shinfo,
		      व्योम **pfrag)
अणु
	व्योम *ptr;

	अगर (skb->len > अंतरभूत_thold || !अंतरभूत_thold)
		वापस false;

	अगर (shinfo->nr_frags == 1) अणु
		ptr = skb_frag_address_safe(&shinfo->frags[0]);
		अगर (unlikely(!ptr))
			वापस false;
		*pfrag = ptr;
		वापस true;
	पूर्ण
	अगर (shinfo->nr_frags)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक अंतरभूत_size(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb->len + CTRL_SIZE + माप(काष्ठा mlx4_wqe_अंतरभूत_seg)
	    <= MLX4_INLINE_ALIGN)
		वापस ALIGN(skb->len + CTRL_SIZE +
			     माप(काष्ठा mlx4_wqe_अंतरभूत_seg), 16);
	अन्यथा
		वापस ALIGN(skb->len + CTRL_SIZE + 2 *
			     माप(काष्ठा mlx4_wqe_अंतरभूत_seg), 16);
पूर्ण

अटल पूर्णांक get_real_size(स्थिर काष्ठा sk_buff *skb,
			 स्थिर काष्ठा skb_shared_info *shinfo,
			 काष्ठा net_device *dev,
			 पूर्णांक *lso_header_size,
			 bool *अंतरभूत_ok,
			 व्योम **pfrag)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक real_size;

	अगर (shinfo->gso_size) अणु
		*अंतरभूत_ok = false;
		अगर (skb->encapsulation)
			*lso_header_size = (skb_inner_transport_header(skb) - skb->data) + inner_tcp_hdrlen(skb);
		अन्यथा
			*lso_header_size = skb_transport_offset(skb) + tcp_hdrlen(skb);
		real_size = CTRL_SIZE + shinfo->nr_frags * DS_SIZE +
			ALIGN(*lso_header_size + 4, DS_SIZE);
		अगर (unlikely(*lso_header_size != skb_headlen(skb))) अणु
			/* We add a segment क्रम the skb linear buffer only अगर
			 * it contains data */
			अगर (*lso_header_size < skb_headlen(skb))
				real_size += DS_SIZE;
			अन्यथा अणु
				अगर (netअगर_msg_tx_err(priv))
					en_warn(priv, "Non-linear headers\n");
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		*lso_header_size = 0;
		*अंतरभूत_ok = is_अंतरभूत(priv->prof->अंतरभूत_thold, skb,
				       shinfo, pfrag);

		अगर (*अंतरभूत_ok)
			real_size = अंतरभूत_size(skb);
		अन्यथा
			real_size = CTRL_SIZE +
				    (shinfo->nr_frags + 1) * DS_SIZE;
	पूर्ण

	वापस real_size;
पूर्ण

अटल व्योम build_अंतरभूत_wqe(काष्ठा mlx4_en_tx_desc *tx_desc,
			     स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा skb_shared_info *shinfo,
			     व्योम *fragptr)
अणु
	काष्ठा mlx4_wqe_अंतरभूत_seg *inl = &tx_desc->inl;
	पूर्णांक spc = MLX4_INLINE_ALIGN - CTRL_SIZE - माप(*inl);
	अचिन्हित पूर्णांक hlen = skb_headlen(skb);

	अगर (skb->len <= spc) अणु
		अगर (likely(skb->len >= MIN_PKT_LEN)) अणु
			inl->byte_count = cpu_to_be32(1 << 31 | skb->len);
		पूर्ण अन्यथा अणु
			inl->byte_count = cpu_to_be32(1 << 31 | MIN_PKT_LEN);
			स_रखो(((व्योम *)(inl + 1)) + skb->len, 0,
			       MIN_PKT_LEN - skb->len);
		पूर्ण
		skb_copy_from_linear_data(skb, inl + 1, hlen);
		अगर (shinfo->nr_frags)
			स_नकल(((व्योम *)(inl + 1)) + hlen, fragptr,
			       skb_frag_size(&shinfo->frags[0]));

	पूर्ण अन्यथा अणु
		inl->byte_count = cpu_to_be32(1 << 31 | spc);
		अगर (hlen <= spc) अणु
			skb_copy_from_linear_data(skb, inl + 1, hlen);
			अगर (hlen < spc) अणु
				स_नकल(((व्योम *)(inl + 1)) + hlen,
				       fragptr, spc - hlen);
				fragptr +=  spc - hlen;
			पूर्ण
			inl = (व्योम *) (inl + 1) + spc;
			स_नकल(((व्योम *)(inl + 1)), fragptr, skb->len - spc);
		पूर्ण अन्यथा अणु
			skb_copy_from_linear_data(skb, inl + 1, spc);
			inl = (व्योम *) (inl + 1) + spc;
			skb_copy_from_linear_data_offset(skb, spc, inl + 1,
							 hlen - spc);
			अगर (shinfo->nr_frags)
				स_नकल(((व्योम *)(inl + 1)) + hlen - spc,
				       fragptr,
				       skb_frag_size(&shinfo->frags[0]));
		पूर्ण

		dma_wmb();
		inl->byte_count = cpu_to_be32(1 << 31 | (skb->len - spc));
	पूर्ण
पूर्ण

u16 mlx4_en_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			 काष्ठा net_device *sb_dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	u16 rings_p_up = priv->num_tx_rings_p_up;

	अगर (netdev_get_num_tc(dev))
		वापस netdev_pick_tx(dev, skb, शून्य);

	वापस netdev_pick_tx(dev, skb, शून्य) % rings_p_up;
पूर्ण

अटल व्योम mlx4_bf_copy(व्योम __iomem *dst, स्थिर व्योम *src,
			 अचिन्हित पूर्णांक bytecnt)
अणु
	__ioग_लिखो64_copy(dst, src, bytecnt / 8);
पूर्ण

व्योम mlx4_en_xmit_करोorbell(काष्ठा mlx4_en_tx_ring *ring)
अणु
	wmb();
	/* Since there is no ioग_लिखो*_native() that ग_लिखोs the
	 * value as is, without byteswapping - using the one
	 * the करोesn't करो byteswapping in the relevant arch
	 * endianness.
	 */
#अगर defined(__LITTLE_ENDIAN)
	ioग_लिखो32(
#अन्यथा
	ioग_लिखो32be(
#पूर्ण_अगर
		  (__क्रमce u32)ring->करोorbell_qpn,
		  ring->bf.uar->map + MLX4_SEND_DOORBELL);
पूर्ण

अटल व्योम mlx4_en_tx_ग_लिखो_desc(काष्ठा mlx4_en_tx_ring *ring,
				  काष्ठा mlx4_en_tx_desc *tx_desc,
				  जोड़ mlx4_wqe_qpn_vlan qpn_vlan,
				  पूर्णांक desc_size, पूर्णांक bf_index,
				  __be32 op_own, bool bf_ok,
				  bool send_करोorbell)
अणु
	tx_desc->ctrl.qpn_vlan = qpn_vlan;

	अगर (bf_ok) अणु
		op_own |= htonl((bf_index & 0xffff) << 8);
		/* Ensure new descriptor hits memory
		 * beक्रमe setting ownership of this descriptor to HW
		 */
		dma_wmb();
		tx_desc->ctrl.owner_opcode = op_own;

		wmb();

		mlx4_bf_copy(ring->bf.reg + ring->bf.offset, &tx_desc->ctrl,
			     desc_size);

		wmb();

		ring->bf.offset ^= ring->bf.buf_size;
	पूर्ण अन्यथा अणु
		/* Ensure new descriptor hits memory
		 * beक्रमe setting ownership of this descriptor to HW
		 */
		dma_wmb();
		tx_desc->ctrl.owner_opcode = op_own;
		अगर (send_करोorbell)
			mlx4_en_xmit_करोorbell(ring);
		अन्यथा
			ring->xmit_more++;
	पूर्ण
पूर्ण

अटल bool mlx4_en_build_dma_wqe(काष्ठा mlx4_en_priv *priv,
				  काष्ठा skb_shared_info *shinfo,
				  काष्ठा mlx4_wqe_data_seg *data,
				  काष्ठा sk_buff *skb,
				  पूर्णांक lso_header_size,
				  __be32 mr_key,
				  काष्ठा mlx4_en_tx_info *tx_info)
अणु
	काष्ठा device *ddev = priv->ddev;
	dma_addr_t dma = 0;
	u32 byte_count = 0;
	पूर्णांक i_frag;

	/* Map fragments अगर any */
	क्रम (i_frag = shinfo->nr_frags - 1; i_frag >= 0; i_frag--) अणु
		स्थिर skb_frag_t *frag = &shinfo->frags[i_frag];
		byte_count = skb_frag_size(frag);
		dma = skb_frag_dma_map(ddev, frag,
				       0, byte_count,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(ddev, dma))
			जाओ tx_drop_unmap;

		data->addr = cpu_to_be64(dma);
		data->lkey = mr_key;
		dma_wmb();
		data->byte_count = cpu_to_be32(byte_count);
		--data;
	पूर्ण

	/* Map linear part अगर needed */
	अगर (tx_info->linear) अणु
		byte_count = skb_headlen(skb) - lso_header_size;

		dma = dma_map_single(ddev, skb->data +
				     lso_header_size, byte_count,
				     PCI_DMA_TODEVICE);
		अगर (dma_mapping_error(ddev, dma))
			जाओ tx_drop_unmap;

		data->addr = cpu_to_be64(dma);
		data->lkey = mr_key;
		dma_wmb();
		data->byte_count = cpu_to_be32(byte_count);
	पूर्ण
	/* tx completion can aव्योम cache line miss क्रम common हालs */
	tx_info->map0_dma = dma;
	tx_info->map0_byte_count = byte_count;

	वापस true;

tx_drop_unmap:
	en_err(priv, "DMA mapping error\n");

	जबतक (++i_frag < shinfo->nr_frags) अणु
		++data;
		dma_unmap_page(ddev, (dma_addr_t)be64_to_cpu(data->addr),
			       be32_to_cpu(data->byte_count),
			       PCI_DMA_TODEVICE);
	पूर्ण

	वापस false;
पूर्ण

netdev_tx_t mlx4_en_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	जोड़ mlx4_wqe_qpn_vlan	qpn_vlan = अणुपूर्ण;
	काष्ठा mlx4_en_tx_ring *ring;
	काष्ठा mlx4_en_tx_desc *tx_desc;
	काष्ठा mlx4_wqe_data_seg *data;
	काष्ठा mlx4_en_tx_info *tx_info;
	u32 __maybe_unused ring_cons;
	पूर्णांक tx_ind;
	पूर्णांक nr_txbb;
	पूर्णांक desc_size;
	पूर्णांक real_size;
	u32 index, bf_index;
	__be32 op_own;
	पूर्णांक lso_header_size;
	व्योम *fragptr = शून्य;
	bool bounce = false;
	bool send_करोorbell;
	bool stop_queue;
	bool अंतरभूत_ok;
	u8 data_offset;
	bool bf_ok;

	tx_ind = skb_get_queue_mapping(skb);
	ring = priv->tx_ring[TX][tx_ind];

	अगर (unlikely(!priv->port_up))
		जाओ tx_drop;

	real_size = get_real_size(skb, shinfo, dev, &lso_header_size,
				  &अंतरभूत_ok, &fragptr);
	अगर (unlikely(!real_size))
		जाओ tx_drop_count;

	/* Align descriptor to TXBB size */
	desc_size = ALIGN(real_size, TXBB_SIZE);
	nr_txbb = desc_size >> LOG_TXBB_SIZE;
	अगर (unlikely(nr_txbb > MAX_DESC_TXBBS)) अणु
		अगर (netअगर_msg_tx_err(priv))
			en_warn(priv, "Oversized header or SG list\n");
		जाओ tx_drop_count;
	पूर्ण

	bf_ok = ring->bf_enabled;
	अगर (skb_vlan_tag_present(skb)) अणु
		u16 vlan_proto;

		qpn_vlan.vlan_tag = cpu_to_be16(skb_vlan_tag_get(skb));
		vlan_proto = be16_to_cpu(skb->vlan_proto);
		अगर (vlan_proto == ETH_P_8021AD)
			qpn_vlan.ins_vlan = MLX4_WQE_CTRL_INS_SVLAN;
		अन्यथा अगर (vlan_proto == ETH_P_8021Q)
			qpn_vlan.ins_vlan = MLX4_WQE_CTRL_INS_CVLAN;
		अन्यथा
			qpn_vlan.ins_vlan = 0;
		bf_ok = false;
	पूर्ण

	netdev_txq_bql_enqueue_prefetchw(ring->tx_queue);

	/* Packet is good - grab an index and transmit it */
	index = ring->prod & ring->size_mask;
	bf_index = ring->prod;

	/* See अगर we have enough space क्रम whole descriptor TXBB क्रम setting
	 * SW ownership on next descriptor; अगर not, use a bounce buffer. */
	अगर (likely(index + nr_txbb <= ring->size))
		tx_desc = ring->buf + (index << LOG_TXBB_SIZE);
	अन्यथा अणु
		tx_desc = (काष्ठा mlx4_en_tx_desc *) ring->bounce_buf;
		bounce = true;
		bf_ok = false;
	पूर्ण

	/* Save skb in tx_info ring */
	tx_info = &ring->tx_info[index];
	tx_info->skb = skb;
	tx_info->nr_txbb = nr_txbb;

	अगर (!lso_header_size) अणु
		data = &tx_desc->data;
		data_offset = दुरत्व(काष्ठा mlx4_en_tx_desc, data);
	पूर्ण अन्यथा अणु
		पूर्णांक lso_align = ALIGN(lso_header_size + 4, DS_SIZE);

		data = (व्योम *)&tx_desc->lso + lso_align;
		data_offset = दुरत्व(काष्ठा mlx4_en_tx_desc, lso) + lso_align;
	पूर्ण

	/* valid only क्रम none अंतरभूत segments */
	tx_info->data_offset = data_offset;

	tx_info->inl = अंतरभूत_ok;

	tx_info->linear = lso_header_size < skb_headlen(skb) && !अंतरभूत_ok;

	tx_info->nr_maps = shinfo->nr_frags + tx_info->linear;
	data += tx_info->nr_maps - 1;

	अगर (!tx_info->inl)
		अगर (!mlx4_en_build_dma_wqe(priv, shinfo, data, skb,
					   lso_header_size, ring->mr_key,
					   tx_info))
			जाओ tx_drop_count;

	/*
	 * For बारtamping add flag to skb_shinfo and
	 * set flag क्रम further reference
	 */
	tx_info->ts_requested = 0;
	अगर (unlikely(ring->hwtstamp_tx_type == HWTSTAMP_TX_ON &&
		     shinfo->tx_flags & SKBTX_HW_TSTAMP)) अणु
		shinfo->tx_flags |= SKBTX_IN_PROGRESS;
		tx_info->ts_requested = 1;
	पूर्ण

	/* Prepare ctrl segement apart opcode+ownership, which depends on
	 * whether LSO is used */
	tx_desc->ctrl.srcrb_flags = priv->ctrl_flags;
	अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		अगर (!skb->encapsulation)
			tx_desc->ctrl.srcrb_flags |= cpu_to_be32(MLX4_WQE_CTRL_IP_CSUM |
								 MLX4_WQE_CTRL_TCP_UDP_CSUM);
		अन्यथा
			tx_desc->ctrl.srcrb_flags |= cpu_to_be32(MLX4_WQE_CTRL_IP_CSUM);
		ring->tx_csum++;
	पूर्ण

	अगर (priv->flags & MLX4_EN_FLAG_ENABLE_HW_LOOPBACK) अणु
		काष्ठा ethhdr *ethh;

		/* Copy dst mac address to wqe. This allows loopback in eSwitch,
		 * so that VFs and PF can communicate with each other
		 */
		ethh = (काष्ठा ethhdr *)skb->data;
		tx_desc->ctrl.srcrb_flags16[0] = get_unaligned((__be16 *)ethh->h_dest);
		tx_desc->ctrl.imm = get_unaligned((__be32 *)(ethh->h_dest + 2));
	पूर्ण

	/* Handle LSO (TSO) packets */
	अगर (lso_header_size) अणु
		पूर्णांक i;

		/* Mark opcode as LSO */
		op_own = cpu_to_be32(MLX4_OPCODE_LSO | (1 << 6)) |
			((ring->prod & ring->size) ?
				cpu_to_be32(MLX4_EN_BIT_DESC_OWN) : 0);

		/* Fill in the LSO prefix */
		tx_desc->lso.mss_hdr_size = cpu_to_be32(
			shinfo->gso_size << 16 | lso_header_size);

		/* Copy headers;
		 * note that we alपढ़ोy verअगरied that it is linear */
		स_नकल(tx_desc->lso.header, skb->data, lso_header_size);

		ring->tso_packets++;

		i = shinfo->gso_segs;
		tx_info->nr_bytes = skb->len + (i - 1) * lso_header_size;
		ring->packets += i;
	पूर्ण अन्यथा अणु
		/* Normal (Non LSO) packet */
		op_own = cpu_to_be32(MLX4_OPCODE_SEND) |
			((ring->prod & ring->size) ?
			 cpu_to_be32(MLX4_EN_BIT_DESC_OWN) : 0);
		tx_info->nr_bytes = max_t(अचिन्हित पूर्णांक, skb->len, ETH_ZLEN);
		ring->packets++;
	पूर्ण
	ring->bytes += tx_info->nr_bytes;

	अगर (tx_info->inl)
		build_अंतरभूत_wqe(tx_desc, skb, shinfo, fragptr);

	अगर (skb->encapsulation) अणु
		जोड़ अणु
			काष्ठा iphdr *v4;
			काष्ठा ipv6hdr *v6;
			अचिन्हित अक्षर *hdr;
		पूर्ण ip;
		u8 proto;

		ip.hdr = skb_inner_network_header(skb);
		proto = (ip.v4->version == 4) ? ip.v4->protocol :
						ip.v6->nexthdr;

		अगर (proto == IPPROTO_TCP || proto == IPPROTO_UDP)
			op_own |= cpu_to_be32(MLX4_WQE_CTRL_IIP | MLX4_WQE_CTRL_ILP);
		अन्यथा
			op_own |= cpu_to_be32(MLX4_WQE_CTRL_IIP);
	पूर्ण

	ring->prod += nr_txbb;

	/* If we used a bounce buffer then copy descriptor back पूर्णांकo place */
	अगर (unlikely(bounce))
		tx_desc = mlx4_en_bounce_to_desc(priv, ring, index, desc_size);

	skb_tx_बारtamp(skb);

	/* Check available TXBBs And 2K spare क्रम prefetch */
	stop_queue = mlx4_en_is_tx_ring_full(ring);
	अगर (unlikely(stop_queue)) अणु
		netअगर_tx_stop_queue(ring->tx_queue);
		ring->queue_stopped++;
	पूर्ण

	send_करोorbell = __netdev_tx_sent_queue(ring->tx_queue,
					       tx_info->nr_bytes,
					       netdev_xmit_more());

	real_size = (real_size / 16) & 0x3f;

	bf_ok &= desc_size <= MAX_BF && send_करोorbell;

	अगर (bf_ok)
		qpn_vlan.bf_qpn = ring->करोorbell_qpn | cpu_to_be32(real_size);
	अन्यथा
		qpn_vlan.fence_size = real_size;

	mlx4_en_tx_ग_लिखो_desc(ring, tx_desc, qpn_vlan, desc_size, bf_index,
			      op_own, bf_ok, send_करोorbell);

	अगर (unlikely(stop_queue)) अणु
		/* If queue was emptied after the अगर (stop_queue) , and beक्रमe
		 * the netअगर_tx_stop_queue() - need to wake the queue,
		 * or अन्यथा it will reमुख्य stopped क्रमever.
		 * Need a memory barrier to make sure ring->cons was not
		 * updated beक्रमe queue was stopped.
		 */
		smp_rmb();

		अगर (unlikely(!mlx4_en_is_tx_ring_full(ring))) अणु
			netअगर_tx_wake_queue(ring->tx_queue);
			ring->wake_queue++;
		पूर्ण
	पूर्ण
	वापस NETDEV_TX_OK;

tx_drop_count:
	ring->tx_dropped++;
tx_drop:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

#घोषणा MLX4_EN_XDP_TX_NRTXBB  1
#घोषणा MLX4_EN_XDP_TX_REAL_SZ (((CTRL_SIZE + MLX4_EN_XDP_TX_NRTXBB * DS_SIZE) \
				 / 16) & 0x3f)

व्योम mlx4_en_init_tx_xdp_ring_descs(काष्ठा mlx4_en_priv *priv,
				    काष्ठा mlx4_en_tx_ring *ring)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ring->size; i++) अणु
		काष्ठा mlx4_en_tx_info *tx_info = &ring->tx_info[i];
		काष्ठा mlx4_en_tx_desc *tx_desc = ring->buf +
			(i << LOG_TXBB_SIZE);

		tx_info->map0_byte_count = PAGE_SIZE;
		tx_info->nr_txbb = MLX4_EN_XDP_TX_NRTXBB;
		tx_info->data_offset = दुरत्व(काष्ठा mlx4_en_tx_desc, data);
		tx_info->ts_requested = 0;
		tx_info->nr_maps = 1;
		tx_info->linear = 1;
		tx_info->inl = 0;

		tx_desc->data.lkey = ring->mr_key;
		tx_desc->ctrl.qpn_vlan.fence_size = MLX4_EN_XDP_TX_REAL_SZ;
		tx_desc->ctrl.srcrb_flags = priv->ctrl_flags;
	पूर्ण
पूर्ण

netdev_tx_t mlx4_en_xmit_frame(काष्ठा mlx4_en_rx_ring *rx_ring,
			       काष्ठा mlx4_en_rx_alloc *frame,
			       काष्ठा mlx4_en_priv *priv, अचिन्हित पूर्णांक length,
			       पूर्णांक tx_ind, bool *करोorbell_pending)
अणु
	काष्ठा mlx4_en_tx_desc *tx_desc;
	काष्ठा mlx4_en_tx_info *tx_info;
	काष्ठा mlx4_wqe_data_seg *data;
	काष्ठा mlx4_en_tx_ring *ring;
	dma_addr_t dma;
	__be32 op_own;
	पूर्णांक index;

	अगर (unlikely(!priv->port_up))
		जाओ tx_drop;

	ring = priv->tx_ring[TX_XDP][tx_ind];

	अगर (unlikely(mlx4_en_is_tx_ring_full(ring)))
		जाओ tx_drop_count;

	index = ring->prod & ring->size_mask;
	tx_info = &ring->tx_info[index];

	tx_desc = ring->buf + (index << LOG_TXBB_SIZE);
	data = &tx_desc->data;

	dma = frame->dma;

	tx_info->page = frame->page;
	frame->page = शून्य;
	tx_info->map0_dma = dma;
	tx_info->nr_bytes = max_t(अचिन्हित पूर्णांक, length, ETH_ZLEN);

	dma_sync_single_range_क्रम_device(priv->ddev, dma, frame->page_offset,
					 length, PCI_DMA_TODEVICE);

	data->addr = cpu_to_be64(dma + frame->page_offset);
	dma_wmb();
	data->byte_count = cpu_to_be32(length);

	/* tx completion can aव्योम cache line miss क्रम common हालs */

	op_own = cpu_to_be32(MLX4_OPCODE_SEND) |
		((ring->prod & ring->size) ?
		 cpu_to_be32(MLX4_EN_BIT_DESC_OWN) : 0);

	rx_ring->xdp_tx++;

	ring->prod += MLX4_EN_XDP_TX_NRTXBB;

	/* Ensure new descriptor hits memory
	 * beक्रमe setting ownership of this descriptor to HW
	 */
	dma_wmb();
	tx_desc->ctrl.owner_opcode = op_own;
	ring->xmit_more++;

	*करोorbell_pending = true;

	वापस NETDEV_TX_OK;

tx_drop_count:
	rx_ring->xdp_tx_full++;
	*करोorbell_pending = true;
tx_drop:
	वापस NETDEV_TX_BUSY;
पूर्ण
