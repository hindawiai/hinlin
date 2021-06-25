<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#अगर_घोषित CONFIG_RFS_ACCEL
#समावेश <linux/cpu_rmap.h>
#पूर्ण_अगर /* CONFIG_RFS_ACCEL */
#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/numa.h>
#समावेश <linux/pci.h>
#समावेश <linux/utsname.h>
#समावेश <linux/version.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/ip.h>

#समावेश "ena_netdev.h"
#समावेश <linux/bpf_trace.h>
#समावेश "ena_pci_id_tbl.h"

MODULE_AUTHOR("Amazon.com, Inc. or its affiliates");
MODULE_DESCRIPTION(DEVICE_NAME);
MODULE_LICENSE("GPL");

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (5 * HZ)

#घोषणा ENA_MAX_RINGS min_t(अचिन्हित पूर्णांक, ENA_MAX_NUM_IO_QUEUES, num_possible_cpus())

#घोषणा ENA_NAPI_BUDGET 64

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_IFUP | \
		NETIF_MSG_TX_DONE | NETIF_MSG_TX_ERR | NETIF_MSG_RX_ERR)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल काष्ठा ena_aenq_handlers aenq_handlers;

अटल काष्ठा workqueue_काष्ठा *ena_wq;

MODULE_DEVICE_TABLE(pci, ena_pci_tbl);

अटल पूर्णांक ena_rss_init_शेष(काष्ठा ena_adapter *adapter);
अटल व्योम check_क्रम_admin_com_state(काष्ठा ena_adapter *adapter);
अटल व्योम ena_destroy_device(काष्ठा ena_adapter *adapter, bool graceful);
अटल पूर्णांक ena_restore_device(काष्ठा ena_adapter *adapter);

अटल व्योम ena_init_io_rings(काष्ठा ena_adapter *adapter,
			      पूर्णांक first_index, पूर्णांक count);
अटल व्योम ena_init_napi_in_range(काष्ठा ena_adapter *adapter, पूर्णांक first_index,
				   पूर्णांक count);
अटल व्योम ena_del_napi_in_range(काष्ठा ena_adapter *adapter, पूर्णांक first_index,
				  पूर्णांक count);
अटल पूर्णांक ena_setup_tx_resources(काष्ठा ena_adapter *adapter, पूर्णांक qid);
अटल पूर्णांक ena_setup_tx_resources_in_range(काष्ठा ena_adapter *adapter,
					   पूर्णांक first_index,
					   पूर्णांक count);
अटल पूर्णांक ena_create_io_tx_queue(काष्ठा ena_adapter *adapter, पूर्णांक qid);
अटल व्योम ena_मुक्त_tx_resources(काष्ठा ena_adapter *adapter, पूर्णांक qid);
अटल पूर्णांक ena_clean_xdp_irq(काष्ठा ena_ring *xdp_ring, u32 budget);
अटल व्योम ena_destroy_all_tx_queues(काष्ठा ena_adapter *adapter);
अटल व्योम ena_मुक्त_all_io_tx_resources(काष्ठा ena_adapter *adapter);
अटल व्योम ena_napi_disable_in_range(काष्ठा ena_adapter *adapter,
				      पूर्णांक first_index, पूर्णांक count);
अटल व्योम ena_napi_enable_in_range(काष्ठा ena_adapter *adapter,
				     पूर्णांक first_index, पूर्णांक count);
अटल पूर्णांक ena_up(काष्ठा ena_adapter *adapter);
अटल व्योम ena_करोwn(काष्ठा ena_adapter *adapter);
अटल व्योम ena_unmask_पूर्णांकerrupt(काष्ठा ena_ring *tx_ring,
				 काष्ठा ena_ring *rx_ring);
अटल व्योम ena_update_ring_numa_node(काष्ठा ena_ring *tx_ring,
				      काष्ठा ena_ring *rx_ring);
अटल व्योम ena_unmap_tx_buff(काष्ठा ena_ring *tx_ring,
			      काष्ठा ena_tx_buffer *tx_info);
अटल पूर्णांक ena_create_io_tx_queues_in_range(काष्ठा ena_adapter *adapter,
					    पूर्णांक first_index, पूर्णांक count);

/* Increase a stat by cnt जबतक holding syncp seqlock on 32bit machines */
अटल व्योम ena_increase_stat(u64 *statp, u64 cnt,
			      काष्ठा u64_stats_sync *syncp)
अणु
	u64_stats_update_begin(syncp);
	(*statp) += cnt;
	u64_stats_update_end(syncp);
पूर्ण

अटल व्योम ena_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(dev);

	/* Change the state of the device to trigger reset
	 * Check that we are not in the middle or a trigger alपढ़ोy
	 */

	अगर (test_and_set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))
		वापस;

	adapter->reset_reason = ENA_REGS_RESET_OS_NETDEV_WD;
	ena_increase_stat(&adapter->dev_stats.tx_समयout, 1, &adapter->syncp);

	netअगर_err(adapter, tx_err, dev, "Transmit time out\n");
पूर्ण

अटल व्योम update_rx_ring_mtu(काष्ठा ena_adapter *adapter, पूर्णांक mtu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_io_queues; i++)
		adapter->rx_ring[i].mtu = mtu;
पूर्ण

अटल पूर्णांक ena_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(dev);
	पूर्णांक ret;

	ret = ena_com_set_dev_mtu(adapter->ena_dev, new_mtu);
	अगर (!ret) अणु
		netअगर_dbg(adapter, drv, dev, "Set MTU to %d\n", new_mtu);
		update_rx_ring_mtu(adapter, new_mtu);
		dev->mtu = new_mtu;
	पूर्ण अन्यथा अणु
		netअगर_err(adapter, drv, dev, "Failed to set MTU to %d\n",
			  new_mtu);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ena_xmit_common(काष्ठा net_device *dev,
			   काष्ठा ena_ring *ring,
			   काष्ठा ena_tx_buffer *tx_info,
			   काष्ठा ena_com_tx_ctx *ena_tx_ctx,
			   u16 next_to_use,
			   u32 bytes)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(dev);
	पूर्णांक rc, nb_hw_desc;

	अगर (unlikely(ena_com_is_करोorbell_needed(ring->ena_com_io_sq,
						ena_tx_ctx))) अणु
		netअगर_dbg(adapter, tx_queued, dev,
			  "llq tx max burst size of queue %d achieved, writing doorbell to send burst\n",
			  ring->qid);
		ena_com_ग_लिखो_sq_करोorbell(ring->ena_com_io_sq);
	पूर्ण

	/* prepare the packet's descriptors to dma engine */
	rc = ena_com_prepare_tx(ring->ena_com_io_sq, ena_tx_ctx,
				&nb_hw_desc);

	/* In हाल there isn't enough space in the queue क्रम the packet,
	 * we simply drop it. All other failure reasons of
	 * ena_com_prepare_tx() are fatal and thereक्रमe require a device reset.
	 */
	अगर (unlikely(rc)) अणु
		netअगर_err(adapter, tx_queued, dev,
			  "Failed to prepare tx bufs\n");
		ena_increase_stat(&ring->tx_stats.prepare_ctx_err, 1,
				  &ring->syncp);
		अगर (rc != -ENOMEM) अणु
			adapter->reset_reason =
				ENA_REGS_RESET_DRIVER_INVALID_STATE;
			set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
		पूर्ण
		वापस rc;
	पूर्ण

	u64_stats_update_begin(&ring->syncp);
	ring->tx_stats.cnt++;
	ring->tx_stats.bytes += bytes;
	u64_stats_update_end(&ring->syncp);

	tx_info->tx_descs = nb_hw_desc;
	tx_info->last_jअगरfies = jअगरfies;
	tx_info->prपूर्णांक_once = 0;

	ring->next_to_use = ENA_TX_RING_IDX_NEXT(next_to_use,
						 ring->ring_size);
	वापस 0;
पूर्ण

/* This is the XDP napi callback. XDP queues use a separate napi callback
 * than Rx/Tx queues.
 */
अटल पूर्णांक ena_xdp_io_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ena_napi *ena_napi = container_of(napi, काष्ठा ena_napi, napi);
	u32 xdp_work_करोne, xdp_budget;
	काष्ठा ena_ring *xdp_ring;
	पूर्णांक napi_comp_call = 0;
	पूर्णांक ret;

	xdp_ring = ena_napi->xdp_ring;
	xdp_ring->first_पूर्णांकerrupt = ena_napi->first_पूर्णांकerrupt;

	xdp_budget = budget;

	अगर (!test_bit(ENA_FLAG_DEV_UP, &xdp_ring->adapter->flags) ||
	    test_bit(ENA_FLAG_TRIGGER_RESET, &xdp_ring->adapter->flags)) अणु
		napi_complete_करोne(napi, 0);
		वापस 0;
	पूर्ण

	xdp_work_करोne = ena_clean_xdp_irq(xdp_ring, xdp_budget);

	/* If the device is about to reset or करोwn, aव्योम unmask
	 * the पूर्णांकerrupt and वापस 0 so NAPI won't reschedule
	 */
	अगर (unlikely(!test_bit(ENA_FLAG_DEV_UP, &xdp_ring->adapter->flags))) अणु
		napi_complete_करोne(napi, 0);
		ret = 0;
	पूर्ण अन्यथा अगर (xdp_budget > xdp_work_करोne) अणु
		napi_comp_call = 1;
		अगर (napi_complete_करोne(napi, xdp_work_करोne))
			ena_unmask_पूर्णांकerrupt(xdp_ring, शून्य);
		ena_update_ring_numa_node(xdp_ring, शून्य);
		ret = xdp_work_करोne;
	पूर्ण अन्यथा अणु
		ret = xdp_budget;
	पूर्ण

	u64_stats_update_begin(&xdp_ring->syncp);
	xdp_ring->tx_stats.napi_comp += napi_comp_call;
	xdp_ring->tx_stats.tx_poll++;
	u64_stats_update_end(&xdp_ring->syncp);

	वापस ret;
पूर्ण

अटल पूर्णांक ena_xdp_tx_map_frame(काष्ठा ena_ring *xdp_ring,
				काष्ठा ena_tx_buffer *tx_info,
				काष्ठा xdp_frame *xdpf,
				काष्ठा ena_com_tx_ctx *ena_tx_ctx)
अणु
	काष्ठा ena_adapter *adapter = xdp_ring->adapter;
	काष्ठा ena_com_buf *ena_buf;
	पूर्णांक push_len = 0;
	dma_addr_t dma;
	व्योम *data;
	u32 size;

	tx_info->xdpf = xdpf;
	data = tx_info->xdpf->data;
	size = tx_info->xdpf->len;

	अगर (xdp_ring->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) अणु
		/* Designate part of the packet क्रम LLQ */
		push_len = min_t(u32, size, xdp_ring->tx_max_header_size);

		ena_tx_ctx->push_header = data;

		size -= push_len;
		data += push_len;
	पूर्ण

	ena_tx_ctx->header_len = push_len;

	अगर (size > 0) अणु
		dma = dma_map_single(xdp_ring->dev,
				     data,
				     size,
				     DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(xdp_ring->dev, dma)))
			जाओ error_report_dma_error;

		tx_info->map_linear_data = 0;

		ena_buf = tx_info->bufs;
		ena_buf->paddr = dma;
		ena_buf->len = size;

		ena_tx_ctx->ena_bufs = ena_buf;
		ena_tx_ctx->num_bufs = tx_info->num_of_bufs = 1;
	पूर्ण

	वापस 0;

error_report_dma_error:
	ena_increase_stat(&xdp_ring->tx_stats.dma_mapping_err, 1,
			  &xdp_ring->syncp);
	netअगर_warn(adapter, tx_queued, adapter->netdev, "Failed to map xdp buff\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ena_xdp_xmit_frame(काष्ठा ena_ring *xdp_ring,
			      काष्ठा net_device *dev,
			      काष्ठा xdp_frame *xdpf,
			      पूर्णांक flags)
अणु
	काष्ठा ena_com_tx_ctx ena_tx_ctx = अणुपूर्ण;
	काष्ठा ena_tx_buffer *tx_info;
	u16 next_to_use, req_id;
	पूर्णांक rc;

	next_to_use = xdp_ring->next_to_use;
	req_id = xdp_ring->मुक्त_ids[next_to_use];
	tx_info = &xdp_ring->tx_buffer_info[req_id];
	tx_info->num_of_bufs = 0;

	rc = ena_xdp_tx_map_frame(xdp_ring, tx_info, xdpf, &ena_tx_ctx);
	अगर (unlikely(rc))
		वापस rc;

	ena_tx_ctx.req_id = req_id;

	rc = ena_xmit_common(dev,
			     xdp_ring,
			     tx_info,
			     &ena_tx_ctx,
			     next_to_use,
			     xdpf->len);
	अगर (rc)
		जाओ error_unmap_dma;
	/* trigger the dma engine. ena_com_ग_लिखो_sq_करोorbell()
	 * has a mb
	 */
	अगर (flags & XDP_XMIT_FLUSH) अणु
		ena_com_ग_लिखो_sq_करोorbell(xdp_ring->ena_com_io_sq);
		ena_increase_stat(&xdp_ring->tx_stats.करोorbells, 1,
				  &xdp_ring->syncp);
	पूर्ण

	वापस rc;

error_unmap_dma:
	ena_unmap_tx_buff(xdp_ring, tx_info);
	tx_info->xdpf = शून्य;
	वापस rc;
पूर्ण

अटल पूर्णांक ena_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n,
			काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(dev);
	काष्ठा ena_ring *xdp_ring;
	पूर्णांक qid, i, nxmit = 0;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	अगर (!test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		वापस -ENETDOWN;

	/* We assume that all rings have the same XDP program */
	अगर (!READ_ONCE(adapter->rx_ring->xdp_bpf_prog))
		वापस -ENXIO;

	qid = smp_processor_id() % adapter->xdp_num_queues;
	qid += adapter->xdp_first_ring;
	xdp_ring = &adapter->tx_ring[qid];

	/* Other CPU ids might try to send thorugh this queue */
	spin_lock(&xdp_ring->xdp_tx_lock);

	क्रम (i = 0; i < n; i++) अणु
		अगर (ena_xdp_xmit_frame(xdp_ring, dev, frames[i], 0))
			अवरोध;
		nxmit++;
	पूर्ण

	/* Ring करोorbell to make device aware of the packets */
	अगर (flags & XDP_XMIT_FLUSH) अणु
		ena_com_ग_लिखो_sq_करोorbell(xdp_ring->ena_com_io_sq);
		ena_increase_stat(&xdp_ring->tx_stats.करोorbells, 1,
				  &xdp_ring->syncp);
	पूर्ण

	spin_unlock(&xdp_ring->xdp_tx_lock);

	/* Return number of packets sent */
	वापस nxmit;
पूर्ण

अटल पूर्णांक ena_xdp_execute(काष्ठा ena_ring *rx_ring, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा ena_ring *xdp_ring;
	u32 verdict = XDP_PASS;
	काष्ठा xdp_frame *xdpf;
	u64 *xdp_stat;
	पूर्णांक qid;

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(rx_ring->xdp_bpf_prog);

	अगर (!xdp_prog)
		जाओ out;

	verdict = bpf_prog_run_xdp(xdp_prog, xdp);

	चयन (verdict) अणु
	हाल XDP_TX:
		xdpf = xdp_convert_buff_to_frame(xdp);
		अगर (unlikely(!xdpf)) अणु
			trace_xdp_exception(rx_ring->netdev, xdp_prog, verdict);
			xdp_stat = &rx_ring->rx_stats.xdp_पातed;
			verdict = XDP_ABORTED;
			अवरोध;
		पूर्ण

		/* Find xmit queue */
		qid = rx_ring->qid + rx_ring->adapter->num_io_queues;
		xdp_ring = &rx_ring->adapter->tx_ring[qid];

		/* The XDP queues are shared between XDP_TX and XDP_REसूचीECT */
		spin_lock(&xdp_ring->xdp_tx_lock);

		अगर (ena_xdp_xmit_frame(xdp_ring, rx_ring->netdev, xdpf,
				       XDP_XMIT_FLUSH))
			xdp_वापस_frame(xdpf);

		spin_unlock(&xdp_ring->xdp_tx_lock);
		xdp_stat = &rx_ring->rx_stats.xdp_tx;
		अवरोध;
	हाल XDP_REसूचीECT:
		अगर (likely(!xdp_करो_redirect(rx_ring->netdev, xdp, xdp_prog))) अणु
			xdp_stat = &rx_ring->rx_stats.xdp_redirect;
			अवरोध;
		पूर्ण
		trace_xdp_exception(rx_ring->netdev, xdp_prog, verdict);
		xdp_stat = &rx_ring->rx_stats.xdp_पातed;
		verdict = XDP_ABORTED;
		अवरोध;
	हाल XDP_ABORTED:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, verdict);
		xdp_stat = &rx_ring->rx_stats.xdp_पातed;
		अवरोध;
	हाल XDP_DROP:
		xdp_stat = &rx_ring->rx_stats.xdp_drop;
		अवरोध;
	हाल XDP_PASS:
		xdp_stat = &rx_ring->rx_stats.xdp_pass;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(verdict);
		xdp_stat = &rx_ring->rx_stats.xdp_invalid;
	पूर्ण

	ena_increase_stat(xdp_stat, 1, &rx_ring->syncp);
out:
	rcu_पढ़ो_unlock();

	वापस verdict;
पूर्ण

अटल व्योम ena_init_all_xdp_queues(काष्ठा ena_adapter *adapter)
अणु
	adapter->xdp_first_ring = adapter->num_io_queues;
	adapter->xdp_num_queues = adapter->num_io_queues;

	ena_init_io_rings(adapter,
			  adapter->xdp_first_ring,
			  adapter->xdp_num_queues);
पूर्ण

अटल पूर्णांक ena_setup_and_create_all_xdp_queues(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक rc = 0;

	rc = ena_setup_tx_resources_in_range(adapter, adapter->xdp_first_ring,
					     adapter->xdp_num_queues);
	अगर (rc)
		जाओ setup_err;

	rc = ena_create_io_tx_queues_in_range(adapter,
					      adapter->xdp_first_ring,
					      adapter->xdp_num_queues);
	अगर (rc)
		जाओ create_err;

	वापस 0;

create_err:
	ena_मुक्त_all_io_tx_resources(adapter);
setup_err:
	वापस rc;
पूर्ण

/* Provides a way क्रम both kernel and bpf-prog to know
 * more about the RX-queue a given XDP frame arrived on.
 */
अटल पूर्णांक ena_xdp_रेजिस्टर_rxq_info(काष्ठा ena_ring *rx_ring)
अणु
	पूर्णांक rc;

	rc = xdp_rxq_info_reg(&rx_ring->xdp_rxq, rx_ring->netdev, rx_ring->qid, 0);

	अगर (rc) अणु
		netअगर_err(rx_ring->adapter, अगरup, rx_ring->netdev,
			  "Failed to register xdp rx queue info. RX queue num %d rc: %d\n",
			  rx_ring->qid, rc);
		जाओ err;
	पूर्ण

	rc = xdp_rxq_info_reg_mem_model(&rx_ring->xdp_rxq, MEM_TYPE_PAGE_SHARED,
					शून्य);

	अगर (rc) अणु
		netअगर_err(rx_ring->adapter, अगरup, rx_ring->netdev,
			  "Failed to register xdp rx queue info memory model. RX queue num %d rc: %d\n",
			  rx_ring->qid, rc);
		xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	पूर्ण

err:
	वापस rc;
पूर्ण

अटल व्योम ena_xdp_unरेजिस्टर_rxq_info(काष्ठा ena_ring *rx_ring)
अणु
	xdp_rxq_info_unreg_mem_model(&rx_ring->xdp_rxq);
	xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
पूर्ण

अटल व्योम ena_xdp_exchange_program_rx_in_range(काष्ठा ena_adapter *adapter,
						 काष्ठा bpf_prog *prog,
						 पूर्णांक first, पूर्णांक count)
अणु
	काष्ठा ena_ring *rx_ring;
	पूर्णांक i = 0;

	क्रम (i = first; i < count; i++) अणु
		rx_ring = &adapter->rx_ring[i];
		xchg(&rx_ring->xdp_bpf_prog, prog);
		अगर (prog) अणु
			ena_xdp_रेजिस्टर_rxq_info(rx_ring);
			rx_ring->rx_headroom = XDP_PACKET_HEADROOM;
		पूर्ण अन्यथा अणु
			ena_xdp_unरेजिस्टर_rxq_info(rx_ring);
			rx_ring->rx_headroom = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ena_xdp_exchange_program(काष्ठा ena_adapter *adapter,
				     काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *old_bpf_prog = xchg(&adapter->xdp_bpf_prog, prog);

	ena_xdp_exchange_program_rx_in_range(adapter,
					     prog,
					     0,
					     adapter->num_io_queues);

	अगर (old_bpf_prog)
		bpf_prog_put(old_bpf_prog);
पूर्ण

अटल पूर्णांक ena_destroy_and_मुक्त_all_xdp_queues(काष्ठा ena_adapter *adapter)
अणु
	bool was_up;
	पूर्णांक rc;

	was_up = test_bit(ENA_FLAG_DEV_UP, &adapter->flags);

	अगर (was_up)
		ena_करोwn(adapter);

	adapter->xdp_first_ring = 0;
	adapter->xdp_num_queues = 0;
	ena_xdp_exchange_program(adapter, शून्य);
	अगर (was_up) अणु
		rc = ena_up(adapter);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ena_xdp_set(काष्ठा net_device *netdev, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	काष्ठा bpf_prog *prog = bpf->prog;
	काष्ठा bpf_prog *old_bpf_prog;
	पूर्णांक rc, prev_mtu;
	bool is_up;

	is_up = test_bit(ENA_FLAG_DEV_UP, &adapter->flags);
	rc = ena_xdp_allowed(adapter);
	अगर (rc == ENA_XDP_ALLOWED) अणु
		old_bpf_prog = adapter->xdp_bpf_prog;
		अगर (prog) अणु
			अगर (!is_up) अणु
				ena_init_all_xdp_queues(adapter);
			पूर्ण अन्यथा अगर (!old_bpf_prog) अणु
				ena_करोwn(adapter);
				ena_init_all_xdp_queues(adapter);
			पूर्ण
			ena_xdp_exchange_program(adapter, prog);

			अगर (is_up && !old_bpf_prog) अणु
				rc = ena_up(adapter);
				अगर (rc)
					वापस rc;
			पूर्ण
		पूर्ण अन्यथा अगर (old_bpf_prog) अणु
			rc = ena_destroy_and_मुक्त_all_xdp_queues(adapter);
			अगर (rc)
				वापस rc;
		पूर्ण

		prev_mtu = netdev->max_mtu;
		netdev->max_mtu = prog ? ENA_XDP_MAX_MTU : adapter->max_mtu;

		अगर (!old_bpf_prog)
			netअगर_info(adapter, drv, adapter->netdev,
				   "XDP program is set, changing the max_mtu from %d to %d",
				   prev_mtu, netdev->max_mtu);

	पूर्ण अन्यथा अगर (rc == ENA_XDP_CURRENT_MTU_TOO_LARGE) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Failed to set xdp program, the current MTU (%d) is larger than the maximum allowed MTU (%lu) while xdp is on",
			  netdev->mtu, ENA_XDP_MAX_MTU);
		NL_SET_ERR_MSG_MOD(bpf->extack,
				   "Failed to set xdp program, the current MTU is larger than the maximum allowed MTU. Check the dmesg for more info");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (rc == ENA_XDP_NO_ENOUGH_QUEUES) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Failed to set xdp program, the Rx/Tx channel count should be at most half of the maximum allowed channel count. The current queue count (%d), the maximal queue count (%d)\n",
			  adapter->num_io_queues, adapter->max_num_io_queues);
		NL_SET_ERR_MSG_MOD(bpf->extack,
				   "Failed to set xdp program, there is no enough space for allocating XDP queues, Check the dmesg for more info");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* This is the मुख्य xdp callback, it's used by the kernel to set/unset the xdp
 * program as well as to query the current xdp program id.
 */
अटल पूर्णांक ena_xdp(काष्ठा net_device *netdev, काष्ठा netdev_bpf *bpf)
अणु
	चयन (bpf->command) अणु
	हाल XDP_SETUP_PROG:
		वापस ena_xdp_set(netdev, bpf);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ena_init_rx_cpu_rmap(काष्ठा ena_adapter *adapter)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	u32 i;
	पूर्णांक rc;

	adapter->netdev->rx_cpu_rmap = alloc_irq_cpu_rmap(adapter->num_io_queues);
	अगर (!adapter->netdev->rx_cpu_rmap)
		वापस -ENOMEM;
	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		पूर्णांक irq_idx = ENA_IO_IRQ_IDX(i);

		rc = irq_cpu_rmap_add(adapter->netdev->rx_cpu_rmap,
				      pci_irq_vector(adapter->pdev, irq_idx));
		अगर (rc) अणु
			मुक्त_irq_cpu_rmap(adapter->netdev->rx_cpu_rmap);
			adapter->netdev->rx_cpu_rmap = शून्य;
			वापस rc;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_RFS_ACCEL */
	वापस 0;
पूर्ण

अटल व्योम ena_init_io_rings_common(काष्ठा ena_adapter *adapter,
				     काष्ठा ena_ring *ring, u16 qid)
अणु
	ring->qid = qid;
	ring->pdev = adapter->pdev;
	ring->dev = &adapter->pdev->dev;
	ring->netdev = adapter->netdev;
	ring->napi = &adapter->ena_napi[qid].napi;
	ring->adapter = adapter;
	ring->ena_dev = adapter->ena_dev;
	ring->per_napi_packets = 0;
	ring->cpu = 0;
	ring->first_पूर्णांकerrupt = false;
	ring->no_पूर्णांकerrupt_event_cnt = 0;
	u64_stats_init(&ring->syncp);
पूर्ण

अटल व्योम ena_init_io_rings(काष्ठा ena_adapter *adapter,
			      पूर्णांक first_index, पूर्णांक count)
अणु
	काष्ठा ena_com_dev *ena_dev;
	काष्ठा ena_ring *txr, *rxr;
	पूर्णांक i;

	ena_dev = adapter->ena_dev;

	क्रम (i = first_index; i < first_index + count; i++) अणु
		txr = &adapter->tx_ring[i];
		rxr = &adapter->rx_ring[i];

		/* TX common ring state */
		ena_init_io_rings_common(adapter, txr, i);

		/* TX specअगरic ring state */
		txr->ring_size = adapter->requested_tx_ring_size;
		txr->tx_max_header_size = ena_dev->tx_max_header_size;
		txr->tx_mem_queue_type = ena_dev->tx_mem_queue_type;
		txr->sgl_size = adapter->max_tx_sgl_size;
		txr->smoothed_पूर्णांकerval =
			ena_com_get_nonadaptive_moderation_पूर्णांकerval_tx(ena_dev);
		txr->disable_meta_caching = adapter->disable_meta_caching;
		spin_lock_init(&txr->xdp_tx_lock);

		/* Don't init RX queues क्रम xdp queues */
		अगर (!ENA_IS_XDP_INDEX(adapter, i)) अणु
			/* RX common ring state */
			ena_init_io_rings_common(adapter, rxr, i);

			/* RX specअगरic ring state */
			rxr->ring_size = adapter->requested_rx_ring_size;
			rxr->rx_copyअवरोध = adapter->rx_copyअवरोध;
			rxr->sgl_size = adapter->max_rx_sgl_size;
			rxr->smoothed_पूर्णांकerval =
				ena_com_get_nonadaptive_moderation_पूर्णांकerval_rx(ena_dev);
			rxr->empty_rx_queue = 0;
			adapter->ena_napi[i].dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
		पूर्ण
	पूर्ण
पूर्ण

/* ena_setup_tx_resources - allocate I/O Tx resources (Descriptors)
 * @adapter: network पूर्णांकerface device काष्ठाure
 * @qid: queue index
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक ena_setup_tx_resources(काष्ठा ena_adapter *adapter, पूर्णांक qid)
अणु
	काष्ठा ena_ring *tx_ring = &adapter->tx_ring[qid];
	काष्ठा ena_irq *ena_irq = &adapter->irq_tbl[ENA_IO_IRQ_IDX(qid)];
	पूर्णांक size, i, node;

	अगर (tx_ring->tx_buffer_info) अणु
		netअगर_err(adapter, अगरup,
			  adapter->netdev, "tx_buffer_info info is not NULL");
		वापस -EEXIST;
	पूर्ण

	size = माप(काष्ठा ena_tx_buffer) * tx_ring->ring_size;
	node = cpu_to_node(ena_irq->cpu);

	tx_ring->tx_buffer_info = vzalloc_node(size, node);
	अगर (!tx_ring->tx_buffer_info) अणु
		tx_ring->tx_buffer_info = vzalloc(size);
		अगर (!tx_ring->tx_buffer_info)
			जाओ err_tx_buffer_info;
	पूर्ण

	size = माप(u16) * tx_ring->ring_size;
	tx_ring->मुक्त_ids = vzalloc_node(size, node);
	अगर (!tx_ring->मुक्त_ids) अणु
		tx_ring->मुक्त_ids = vzalloc(size);
		अगर (!tx_ring->मुक्त_ids)
			जाओ err_tx_मुक्त_ids;
	पूर्ण

	size = tx_ring->tx_max_header_size;
	tx_ring->push_buf_पूर्णांकermediate_buf = vzalloc_node(size, node);
	अगर (!tx_ring->push_buf_पूर्णांकermediate_buf) अणु
		tx_ring->push_buf_पूर्णांकermediate_buf = vzalloc(size);
		अगर (!tx_ring->push_buf_पूर्णांकermediate_buf)
			जाओ err_push_buf_पूर्णांकermediate_buf;
	पूर्ण

	/* Req id ring क्रम TX out of order completions */
	क्रम (i = 0; i < tx_ring->ring_size; i++)
		tx_ring->मुक्त_ids[i] = i;

	/* Reset tx statistics */
	स_रखो(&tx_ring->tx_stats, 0x0, माप(tx_ring->tx_stats));

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	tx_ring->cpu = ena_irq->cpu;
	वापस 0;

err_push_buf_पूर्णांकermediate_buf:
	vमुक्त(tx_ring->मुक्त_ids);
	tx_ring->मुक्त_ids = शून्य;
err_tx_मुक्त_ids:
	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;
err_tx_buffer_info:
	वापस -ENOMEM;
पूर्ण

/* ena_मुक्त_tx_resources - Free I/O Tx Resources per Queue
 * @adapter: network पूर्णांकerface device काष्ठाure
 * @qid: queue index
 *
 * Free all transmit software resources
 */
अटल व्योम ena_मुक्त_tx_resources(काष्ठा ena_adapter *adapter, पूर्णांक qid)
अणु
	काष्ठा ena_ring *tx_ring = &adapter->tx_ring[qid];

	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;

	vमुक्त(tx_ring->मुक्त_ids);
	tx_ring->मुक्त_ids = शून्य;

	vमुक्त(tx_ring->push_buf_पूर्णांकermediate_buf);
	tx_ring->push_buf_पूर्णांकermediate_buf = शून्य;
पूर्ण

अटल पूर्णांक ena_setup_tx_resources_in_range(काष्ठा ena_adapter *adapter,
					   पूर्णांक first_index,
					   पूर्णांक count)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = first_index; i < first_index + count; i++) अणु
		rc = ena_setup_tx_resources(adapter, i);
		अगर (rc)
			जाओ err_setup_tx;
	पूर्ण

	वापस 0;

err_setup_tx:

	netअगर_err(adapter, अगरup, adapter->netdev,
		  "Tx queue %d: allocation failed\n", i);

	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (first_index < i--)
		ena_मुक्त_tx_resources(adapter, i);
	वापस rc;
पूर्ण

अटल व्योम ena_मुक्त_all_io_tx_resources_in_range(काष्ठा ena_adapter *adapter,
						  पूर्णांक first_index, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = first_index; i < first_index + count; i++)
		ena_मुक्त_tx_resources(adapter, i);
पूर्ण

/* ena_मुक्त_all_io_tx_resources - Free I/O Tx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 */
अटल व्योम ena_मुक्त_all_io_tx_resources(काष्ठा ena_adapter *adapter)
अणु
	ena_मुक्त_all_io_tx_resources_in_range(adapter,
					      0,
					      adapter->xdp_num_queues +
					      adapter->num_io_queues);
पूर्ण

/* ena_setup_rx_resources - allocate I/O Rx resources (Descriptors)
 * @adapter: network पूर्णांकerface device काष्ठाure
 * @qid: queue index
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक ena_setup_rx_resources(काष्ठा ena_adapter *adapter,
				  u32 qid)
अणु
	काष्ठा ena_ring *rx_ring = &adapter->rx_ring[qid];
	काष्ठा ena_irq *ena_irq = &adapter->irq_tbl[ENA_IO_IRQ_IDX(qid)];
	पूर्णांक size, node, i;

	अगर (rx_ring->rx_buffer_info) अणु
		netअगर_err(adapter, अगरup, adapter->netdev,
			  "rx_buffer_info is not NULL");
		वापस -EEXIST;
	पूर्ण

	/* alloc extra element so in rx path
	 * we can always prefetch rx_info + 1
	 */
	size = माप(काष्ठा ena_rx_buffer) * (rx_ring->ring_size + 1);
	node = cpu_to_node(ena_irq->cpu);

	rx_ring->rx_buffer_info = vzalloc_node(size, node);
	अगर (!rx_ring->rx_buffer_info) अणु
		rx_ring->rx_buffer_info = vzalloc(size);
		अगर (!rx_ring->rx_buffer_info)
			वापस -ENOMEM;
	पूर्ण

	size = माप(u16) * rx_ring->ring_size;
	rx_ring->मुक्त_ids = vzalloc_node(size, node);
	अगर (!rx_ring->मुक्त_ids) अणु
		rx_ring->मुक्त_ids = vzalloc(size);
		अगर (!rx_ring->मुक्त_ids) अणु
			vमुक्त(rx_ring->rx_buffer_info);
			rx_ring->rx_buffer_info = शून्य;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Req id ring क्रम receiving RX pkts out of order */
	क्रम (i = 0; i < rx_ring->ring_size; i++)
		rx_ring->मुक्त_ids[i] = i;

	/* Reset rx statistics */
	स_रखो(&rx_ring->rx_stats, 0x0, माप(rx_ring->rx_stats));

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	rx_ring->cpu = ena_irq->cpu;

	वापस 0;
पूर्ण

/* ena_मुक्त_rx_resources - Free I/O Rx Resources
 * @adapter: network पूर्णांकerface device काष्ठाure
 * @qid: queue index
 *
 * Free all receive software resources
 */
अटल व्योम ena_मुक्त_rx_resources(काष्ठा ena_adapter *adapter,
				  u32 qid)
अणु
	काष्ठा ena_ring *rx_ring = &adapter->rx_ring[qid];

	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;

	vमुक्त(rx_ring->मुक्त_ids);
	rx_ring->मुक्त_ids = शून्य;
पूर्ण

/* ena_setup_all_rx_resources - allocate I/O Rx queues resources क्रम all queues
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक ena_setup_all_rx_resources(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		rc = ena_setup_rx_resources(adapter, i);
		अगर (rc)
			जाओ err_setup_rx;
	पूर्ण

	वापस 0;

err_setup_rx:

	netअगर_err(adapter, अगरup, adapter->netdev,
		  "Rx queue %d: allocation failed\n", i);

	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (i--)
		ena_मुक्त_rx_resources(adapter, i);
	वापस rc;
पूर्ण

/* ena_मुक्त_all_io_rx_resources - Free I/O Rx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all receive software resources
 */
अटल व्योम ena_मुक्त_all_io_rx_resources(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_io_queues; i++)
		ena_मुक्त_rx_resources(adapter, i);
पूर्ण

अटल पूर्णांक ena_alloc_rx_page(काष्ठा ena_ring *rx_ring,
				    काष्ठा ena_rx_buffer *rx_info, gfp_t gfp)
अणु
	पूर्णांक headroom = rx_ring->rx_headroom;
	काष्ठा ena_com_buf *ena_buf;
	काष्ठा page *page;
	dma_addr_t dma;

	/* restore page offset value in हाल it has been changed by device */
	rx_info->page_offset = headroom;

	/* अगर previous allocated page is not used */
	अगर (unlikely(rx_info->page))
		वापस 0;

	page = alloc_page(gfp);
	अगर (unlikely(!page)) अणु
		ena_increase_stat(&rx_ring->rx_stats.page_alloc_fail, 1,
				  &rx_ring->syncp);
		वापस -ENOMEM;
	पूर्ण

	/* To enable NIC-side port-mirroring, AKA SPAN port,
	 * we make the buffer पढ़ोable from the nic as well
	 */
	dma = dma_map_page(rx_ring->dev, page, 0, ENA_PAGE_SIZE,
			   DMA_BIसूचीECTIONAL);
	अगर (unlikely(dma_mapping_error(rx_ring->dev, dma))) अणु
		ena_increase_stat(&rx_ring->rx_stats.dma_mapping_err, 1,
				  &rx_ring->syncp);

		__मुक्त_page(page);
		वापस -EIO;
	पूर्ण
	netअगर_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
		  "Allocate page %p, rx_info %p\n", page, rx_info);

	rx_info->page = page;
	ena_buf = &rx_info->ena_buf;
	ena_buf->paddr = dma + headroom;
	ena_buf->len = ENA_PAGE_SIZE - headroom;

	वापस 0;
पूर्ण

अटल व्योम ena_unmap_rx_buff(काष्ठा ena_ring *rx_ring,
			      काष्ठा ena_rx_buffer *rx_info)
अणु
	काष्ठा ena_com_buf *ena_buf = &rx_info->ena_buf;

	dma_unmap_page(rx_ring->dev, ena_buf->paddr - rx_ring->rx_headroom,
		       ENA_PAGE_SIZE,
		       DMA_BIसूचीECTIONAL);
पूर्ण

अटल व्योम ena_मुक्त_rx_page(काष्ठा ena_ring *rx_ring,
			     काष्ठा ena_rx_buffer *rx_info)
अणु
	काष्ठा page *page = rx_info->page;

	अगर (unlikely(!page)) अणु
		netअगर_warn(rx_ring->adapter, rx_err, rx_ring->netdev,
			   "Trying to free unallocated buffer\n");
		वापस;
	पूर्ण

	ena_unmap_rx_buff(rx_ring, rx_info);

	__मुक्त_page(page);
	rx_info->page = शून्य;
पूर्ण

अटल पूर्णांक ena_refill_rx_bufs(काष्ठा ena_ring *rx_ring, u32 num)
अणु
	u16 next_to_use, req_id;
	u32 i;
	पूर्णांक rc;

	next_to_use = rx_ring->next_to_use;

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा ena_rx_buffer *rx_info;

		req_id = rx_ring->मुक्त_ids[next_to_use];

		rx_info = &rx_ring->rx_buffer_info[req_id];

		rc = ena_alloc_rx_page(rx_ring, rx_info,
				       GFP_ATOMIC | __GFP_COMP);
		अगर (unlikely(rc < 0)) अणु
			netअगर_warn(rx_ring->adapter, rx_err, rx_ring->netdev,
				   "Failed to allocate buffer for rx queue %d\n",
				   rx_ring->qid);
			अवरोध;
		पूर्ण
		rc = ena_com_add_single_rx_desc(rx_ring->ena_com_io_sq,
						&rx_info->ena_buf,
						req_id);
		अगर (unlikely(rc)) अणु
			netअगर_warn(rx_ring->adapter, rx_status, rx_ring->netdev,
				   "Failed to add buffer for rx queue %d\n",
				   rx_ring->qid);
			अवरोध;
		पूर्ण
		next_to_use = ENA_RX_RING_IDX_NEXT(next_to_use,
						   rx_ring->ring_size);
	पूर्ण

	अगर (unlikely(i < num)) अणु
		ena_increase_stat(&rx_ring->rx_stats.refil_partial, 1,
				  &rx_ring->syncp);
		netअगर_warn(rx_ring->adapter, rx_err, rx_ring->netdev,
			   "Refilled rx qid %d with only %d buffers (from %d)\n",
			   rx_ring->qid, i, num);
	पूर्ण

	/* ena_com_ग_लिखो_sq_करोorbell issues a wmb() */
	अगर (likely(i))
		ena_com_ग_लिखो_sq_करोorbell(rx_ring->ena_com_io_sq);

	rx_ring->next_to_use = next_to_use;

	वापस i;
पूर्ण

अटल व्योम ena_मुक्त_rx_bufs(काष्ठा ena_adapter *adapter,
			     u32 qid)
अणु
	काष्ठा ena_ring *rx_ring = &adapter->rx_ring[qid];
	u32 i;

	क्रम (i = 0; i < rx_ring->ring_size; i++) अणु
		काष्ठा ena_rx_buffer *rx_info = &rx_ring->rx_buffer_info[i];

		अगर (rx_info->page)
			ena_मुक्त_rx_page(rx_ring, rx_info);
	पूर्ण
पूर्ण

/* ena_refill_all_rx_bufs - allocate all queues Rx buffers
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम ena_refill_all_rx_bufs(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_ring *rx_ring;
	पूर्णांक i, rc, bufs_num;

	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		rx_ring = &adapter->rx_ring[i];
		bufs_num = rx_ring->ring_size - 1;
		rc = ena_refill_rx_bufs(rx_ring, bufs_num);

		अगर (unlikely(rc != bufs_num))
			netअगर_warn(rx_ring->adapter, rx_status, rx_ring->netdev,
				   "Refilling Queue %d failed. allocated %d buffers from: %d\n",
				   i, rc, bufs_num);
	पूर्ण
पूर्ण

अटल व्योम ena_मुक्त_all_rx_bufs(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_io_queues; i++)
		ena_मुक्त_rx_bufs(adapter, i);
पूर्ण

अटल व्योम ena_unmap_tx_buff(काष्ठा ena_ring *tx_ring,
			      काष्ठा ena_tx_buffer *tx_info)
अणु
	काष्ठा ena_com_buf *ena_buf;
	u32 cnt;
	पूर्णांक i;

	ena_buf = tx_info->bufs;
	cnt = tx_info->num_of_bufs;

	अगर (unlikely(!cnt))
		वापस;

	अगर (tx_info->map_linear_data) अणु
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(ena_buf, paddr),
				 dma_unmap_len(ena_buf, len),
				 DMA_TO_DEVICE);
		ena_buf++;
		cnt--;
	पूर्ण

	/* unmap reमुख्यing mapped pages */
	क्रम (i = 0; i < cnt; i++) अणु
		dma_unmap_page(tx_ring->dev, dma_unmap_addr(ena_buf, paddr),
			       dma_unmap_len(ena_buf, len), DMA_TO_DEVICE);
		ena_buf++;
	पूर्ण
पूर्ण

/* ena_मुक्त_tx_bufs - Free Tx Buffers per Queue
 * @tx_ring: TX ring क्रम which buffers be मुक्तd
 */
अटल व्योम ena_मुक्त_tx_bufs(काष्ठा ena_ring *tx_ring)
अणु
	bool prपूर्णांक_once = true;
	u32 i;

	क्रम (i = 0; i < tx_ring->ring_size; i++) अणु
		काष्ठा ena_tx_buffer *tx_info = &tx_ring->tx_buffer_info[i];

		अगर (!tx_info->skb)
			जारी;

		अगर (prपूर्णांक_once) अणु
			netअगर_notice(tx_ring->adapter, अगरकरोwn, tx_ring->netdev,
				     "Free uncompleted tx skb qid %d idx 0x%x\n",
				     tx_ring->qid, i);
			prपूर्णांक_once = false;
		पूर्ण अन्यथा अणु
			netअगर_dbg(tx_ring->adapter, अगरकरोwn, tx_ring->netdev,
				  "Free uncompleted tx skb qid %d idx 0x%x\n",
				  tx_ring->qid, i);
		पूर्ण

		ena_unmap_tx_buff(tx_ring, tx_info);

		dev_kमुक्त_skb_any(tx_info->skb);
	पूर्ण
	netdev_tx_reset_queue(netdev_get_tx_queue(tx_ring->netdev,
						  tx_ring->qid));
पूर्ण

अटल व्योम ena_मुक्त_all_tx_bufs(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_ring *tx_ring;
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_io_queues + adapter->xdp_num_queues; i++) अणु
		tx_ring = &adapter->tx_ring[i];
		ena_मुक्त_tx_bufs(tx_ring);
	पूर्ण
पूर्ण

अटल व्योम ena_destroy_all_tx_queues(काष्ठा ena_adapter *adapter)
अणु
	u16 ena_qid;
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_io_queues + adapter->xdp_num_queues; i++) अणु
		ena_qid = ENA_IO_TXQ_IDX(i);
		ena_com_destroy_io_queue(adapter->ena_dev, ena_qid);
	पूर्ण
पूर्ण

अटल व्योम ena_destroy_all_rx_queues(काष्ठा ena_adapter *adapter)
अणु
	u16 ena_qid;
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		ena_qid = ENA_IO_RXQ_IDX(i);
		cancel_work_sync(&adapter->ena_napi[i].dim.work);
		ena_com_destroy_io_queue(adapter->ena_dev, ena_qid);
	पूर्ण
पूर्ण

अटल व्योम ena_destroy_all_io_queues(काष्ठा ena_adapter *adapter)
अणु
	ena_destroy_all_tx_queues(adapter);
	ena_destroy_all_rx_queues(adapter);
पूर्ण

अटल पूर्णांक handle_invalid_req_id(काष्ठा ena_ring *ring, u16 req_id,
				 काष्ठा ena_tx_buffer *tx_info, bool is_xdp)
अणु
	अगर (tx_info)
		netअगर_err(ring->adapter,
			  tx_करोne,
			  ring->netdev,
			  "tx_info doesn't have valid %s",
			   is_xdp ? "xdp frame" : "skb");
	अन्यथा
		netअगर_err(ring->adapter,
			  tx_करोne,
			  ring->netdev,
			  "Invalid req_id: %hu\n",
			  req_id);

	ena_increase_stat(&ring->tx_stats.bad_req_id, 1, &ring->syncp);

	/* Trigger device reset */
	ring->adapter->reset_reason = ENA_REGS_RESET_INV_TX_REQ_ID;
	set_bit(ENA_FLAG_TRIGGER_RESET, &ring->adapter->flags);
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक validate_tx_req_id(काष्ठा ena_ring *tx_ring, u16 req_id)
अणु
	काष्ठा ena_tx_buffer *tx_info = शून्य;

	अगर (likely(req_id < tx_ring->ring_size)) अणु
		tx_info = &tx_ring->tx_buffer_info[req_id];
		अगर (likely(tx_info->skb))
			वापस 0;
	पूर्ण

	वापस handle_invalid_req_id(tx_ring, req_id, tx_info, false);
पूर्ण

अटल पूर्णांक validate_xdp_req_id(काष्ठा ena_ring *xdp_ring, u16 req_id)
अणु
	काष्ठा ena_tx_buffer *tx_info = शून्य;

	अगर (likely(req_id < xdp_ring->ring_size)) अणु
		tx_info = &xdp_ring->tx_buffer_info[req_id];
		अगर (likely(tx_info->xdpf))
			वापस 0;
	पूर्ण

	वापस handle_invalid_req_id(xdp_ring, req_id, tx_info, true);
पूर्ण

अटल पूर्णांक ena_clean_tx_irq(काष्ठा ena_ring *tx_ring, u32 budget)
अणु
	काष्ठा netdev_queue *txq;
	bool above_thresh;
	u32 tx_bytes = 0;
	u32 total_करोne = 0;
	u16 next_to_clean;
	u16 req_id;
	पूर्णांक tx_pkts = 0;
	पूर्णांक rc;

	next_to_clean = tx_ring->next_to_clean;
	txq = netdev_get_tx_queue(tx_ring->netdev, tx_ring->qid);

	जबतक (tx_pkts < budget) अणु
		काष्ठा ena_tx_buffer *tx_info;
		काष्ठा sk_buff *skb;

		rc = ena_com_tx_comp_req_id_get(tx_ring->ena_com_io_cq,
						&req_id);
		अगर (rc)
			अवरोध;

		rc = validate_tx_req_id(tx_ring, req_id);
		अगर (rc)
			अवरोध;

		tx_info = &tx_ring->tx_buffer_info[req_id];
		skb = tx_info->skb;

		/* prefetch skb_end_poपूर्णांकer() to speedup skb_shinfo(skb) */
		prefetch(&skb->end);

		tx_info->skb = शून्य;
		tx_info->last_jअगरfies = 0;

		ena_unmap_tx_buff(tx_ring, tx_info);

		netअगर_dbg(tx_ring->adapter, tx_करोne, tx_ring->netdev,
			  "tx_poll: q %d skb %p completed\n", tx_ring->qid,
			  skb);

		tx_bytes += skb->len;
		dev_kमुक्त_skb(skb);
		tx_pkts++;
		total_करोne += tx_info->tx_descs;

		tx_ring->मुक्त_ids[next_to_clean] = req_id;
		next_to_clean = ENA_TX_RING_IDX_NEXT(next_to_clean,
						     tx_ring->ring_size);
	पूर्ण

	tx_ring->next_to_clean = next_to_clean;
	ena_com_comp_ack(tx_ring->ena_com_io_sq, total_करोne);
	ena_com_update_dev_comp_head(tx_ring->ena_com_io_cq);

	netdev_tx_completed_queue(txq, tx_pkts, tx_bytes);

	netअगर_dbg(tx_ring->adapter, tx_करोne, tx_ring->netdev,
		  "tx_poll: q %d done. total pkts: %d\n",
		  tx_ring->qid, tx_pkts);

	/* need to make the rings circular update visible to
	 * ena_start_xmit() beक्रमe checking क्रम netअगर_queue_stopped().
	 */
	smp_mb();

	above_thresh = ena_com_sq_have_enough_space(tx_ring->ena_com_io_sq,
						    ENA_TX_WAKEUP_THRESH);
	अगर (unlikely(netअगर_tx_queue_stopped(txq) && above_thresh)) अणु
		__netअगर_tx_lock(txq, smp_processor_id());
		above_thresh =
			ena_com_sq_have_enough_space(tx_ring->ena_com_io_sq,
						     ENA_TX_WAKEUP_THRESH);
		अगर (netअगर_tx_queue_stopped(txq) && above_thresh &&
		    test_bit(ENA_FLAG_DEV_UP, &tx_ring->adapter->flags)) अणु
			netअगर_tx_wake_queue(txq);
			ena_increase_stat(&tx_ring->tx_stats.queue_wakeup, 1,
					  &tx_ring->syncp);
		पूर्ण
		__netअगर_tx_unlock(txq);
	पूर्ण

	वापस tx_pkts;
पूर्ण

अटल काष्ठा sk_buff *ena_alloc_skb(काष्ठा ena_ring *rx_ring, bool frags)
अणु
	काष्ठा sk_buff *skb;

	अगर (frags)
		skb = napi_get_frags(rx_ring->napi);
	अन्यथा
		skb = netdev_alloc_skb_ip_align(rx_ring->netdev,
						rx_ring->rx_copyअवरोध);

	अगर (unlikely(!skb)) अणु
		ena_increase_stat(&rx_ring->rx_stats.skb_alloc_fail, 1,
				  &rx_ring->syncp);
		netअगर_dbg(rx_ring->adapter, rx_err, rx_ring->netdev,
			  "Failed to allocate skb. frags: %d\n", frags);
		वापस शून्य;
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ena_rx_skb(काष्ठा ena_ring *rx_ring,
				  काष्ठा ena_com_rx_buf_info *ena_bufs,
				  u32 descs,
				  u16 *next_to_clean)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ena_rx_buffer *rx_info;
	u16 len, req_id, buf = 0;
	व्योम *va;

	len = ena_bufs[buf].len;
	req_id = ena_bufs[buf].req_id;

	rx_info = &rx_ring->rx_buffer_info[req_id];

	अगर (unlikely(!rx_info->page)) अणु
		netअगर_err(rx_ring->adapter, rx_err, rx_ring->netdev,
			  "Page is NULL\n");
		वापस शून्य;
	पूर्ण

	netअगर_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
		  "rx_info %p page %p\n",
		  rx_info, rx_info->page);

	/* save virt address of first buffer */
	va = page_address(rx_info->page) + rx_info->page_offset;

	prefetch(va);

	अगर (len <= rx_ring->rx_copyअवरोध) अणु
		skb = ena_alloc_skb(rx_ring, false);
		अगर (unlikely(!skb))
			वापस शून्य;

		netअगर_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
			  "RX allocated small packet. len %d. data_len %d\n",
			  skb->len, skb->data_len);

		/* sync this buffer क्रम CPU use */
		dma_sync_single_क्रम_cpu(rx_ring->dev,
					dma_unmap_addr(&rx_info->ena_buf, paddr),
					len,
					DMA_FROM_DEVICE);
		skb_copy_to_linear_data(skb, va, len);
		dma_sync_single_क्रम_device(rx_ring->dev,
					   dma_unmap_addr(&rx_info->ena_buf, paddr),
					   len,
					   DMA_FROM_DEVICE);

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, rx_ring->netdev);
		rx_ring->मुक्त_ids[*next_to_clean] = req_id;
		*next_to_clean = ENA_RX_RING_IDX_ADD(*next_to_clean, descs,
						     rx_ring->ring_size);
		वापस skb;
	पूर्ण

	skb = ena_alloc_skb(rx_ring, true);
	अगर (unlikely(!skb))
		वापस शून्य;

	करो अणु
		ena_unmap_rx_buff(rx_ring, rx_info);

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_info->page,
				rx_info->page_offset, len, ENA_PAGE_SIZE);

		netअगर_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
			  "RX skb updated. len %d. data_len %d\n",
			  skb->len, skb->data_len);

		rx_info->page = शून्य;

		rx_ring->मुक्त_ids[*next_to_clean] = req_id;
		*next_to_clean =
			ENA_RX_RING_IDX_NEXT(*next_to_clean,
					     rx_ring->ring_size);
		अगर (likely(--descs == 0))
			अवरोध;

		buf++;
		len = ena_bufs[buf].len;
		req_id = ena_bufs[buf].req_id;

		rx_info = &rx_ring->rx_buffer_info[req_id];
	पूर्ण जबतक (1);

	वापस skb;
पूर्ण

/* ena_rx_checksum - indicate in skb अगर hw indicated a good cksum
 * @adapter: काष्ठाure containing adapter specअगरic data
 * @ena_rx_ctx: received packet context/metadata
 * @skb: skb currently being received and modअगरied
 */
अटल व्योम ena_rx_checksum(काष्ठा ena_ring *rx_ring,
				   काष्ठा ena_com_rx_ctx *ena_rx_ctx,
				   काष्ठा sk_buff *skb)
अणु
	/* Rx csum disabled */
	अगर (unlikely(!(rx_ring->netdev->features & NETIF_F_RXCSUM))) अणु
		skb->ip_summed = CHECKSUM_NONE;
		वापस;
	पूर्ण

	/* For fragmented packets the checksum isn't valid */
	अगर (ena_rx_ctx->frag) अणु
		skb->ip_summed = CHECKSUM_NONE;
		वापस;
	पूर्ण

	/* अगर IP and error */
	अगर (unlikely((ena_rx_ctx->l3_proto == ENA_ETH_IO_L3_PROTO_IPV4) &&
		     (ena_rx_ctx->l3_csum_err))) अणु
		/* ipv4 checksum error */
		skb->ip_summed = CHECKSUM_NONE;
		ena_increase_stat(&rx_ring->rx_stats.bad_csum, 1,
				  &rx_ring->syncp);
		netअगर_dbg(rx_ring->adapter, rx_err, rx_ring->netdev,
			  "RX IPv4 header checksum error\n");
		वापस;
	पूर्ण

	/* अगर TCP/UDP */
	अगर (likely((ena_rx_ctx->l4_proto == ENA_ETH_IO_L4_PROTO_TCP) ||
		   (ena_rx_ctx->l4_proto == ENA_ETH_IO_L4_PROTO_UDP))) अणु
		अगर (unlikely(ena_rx_ctx->l4_csum_err)) अणु
			/* TCP/UDP checksum error */
			ena_increase_stat(&rx_ring->rx_stats.bad_csum, 1,
					  &rx_ring->syncp);
			netअगर_dbg(rx_ring->adapter, rx_err, rx_ring->netdev,
				  "RX L4 checksum error\n");
			skb->ip_summed = CHECKSUM_NONE;
			वापस;
		पूर्ण

		अगर (likely(ena_rx_ctx->l4_csum_checked)) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			ena_increase_stat(&rx_ring->rx_stats.csum_good, 1,
					  &rx_ring->syncp);
		पूर्ण अन्यथा अणु
			ena_increase_stat(&rx_ring->rx_stats.csum_unchecked, 1,
					  &rx_ring->syncp);
			skb->ip_summed = CHECKSUM_NONE;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_NONE;
		वापस;
	पूर्ण

पूर्ण

अटल व्योम ena_set_rx_hash(काष्ठा ena_ring *rx_ring,
			    काष्ठा ena_com_rx_ctx *ena_rx_ctx,
			    काष्ठा sk_buff *skb)
अणु
	क्रमागत pkt_hash_types hash_type;

	अगर (likely(rx_ring->netdev->features & NETIF_F_RXHASH)) अणु
		अगर (likely((ena_rx_ctx->l4_proto == ENA_ETH_IO_L4_PROTO_TCP) ||
			   (ena_rx_ctx->l4_proto == ENA_ETH_IO_L4_PROTO_UDP)))

			hash_type = PKT_HASH_TYPE_L4;
		अन्यथा
			hash_type = PKT_HASH_TYPE_NONE;

		/* Override hash type अगर the packet is fragmented */
		अगर (ena_rx_ctx->frag)
			hash_type = PKT_HASH_TYPE_NONE;

		skb_set_hash(skb, ena_rx_ctx->hash, hash_type);
	पूर्ण
पूर्ण

अटल पूर्णांक ena_xdp_handle_buff(काष्ठा ena_ring *rx_ring, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा ena_rx_buffer *rx_info;
	पूर्णांक ret;

	rx_info = &rx_ring->rx_buffer_info[rx_ring->ena_bufs[0].req_id];
	xdp_prepare_buff(xdp, page_address(rx_info->page),
			 rx_info->page_offset,
			 rx_ring->ena_bufs[0].len, false);
	/* If क्रम some reason we received a bigger packet than
	 * we expect, then we simply drop it
	 */
	अगर (unlikely(rx_ring->ena_bufs[0].len > ENA_XDP_MAX_MTU))
		वापस XDP_DROP;

	ret = ena_xdp_execute(rx_ring, xdp);

	/* The xdp program might expand the headers */
	अगर (ret == XDP_PASS) अणु
		rx_info->page_offset = xdp->data - xdp->data_hard_start;
		rx_ring->ena_bufs[0].len = xdp->data_end - xdp->data;
	पूर्ण

	वापस ret;
पूर्ण
/* ena_clean_rx_irq - Cleanup RX irq
 * @rx_ring: RX ring to clean
 * @napi: napi handler
 * @budget: how many packets driver is allowed to clean
 *
 * Returns the number of cleaned buffers.
 */
अटल पूर्णांक ena_clean_rx_irq(काष्ठा ena_ring *rx_ring, काष्ठा napi_काष्ठा *napi,
			    u32 budget)
अणु
	u16 next_to_clean = rx_ring->next_to_clean;
	काष्ठा ena_com_rx_ctx ena_rx_ctx;
	काष्ठा ena_rx_buffer *rx_info;
	काष्ठा ena_adapter *adapter;
	u32 res_budget, work_करोne;
	पूर्णांक rx_copyअवरोध_pkt = 0;
	पूर्णांक refill_threshold;
	काष्ठा sk_buff *skb;
	पूर्णांक refill_required;
	काष्ठा xdp_buff xdp;
	पूर्णांक xdp_flags = 0;
	पूर्णांक total_len = 0;
	पूर्णांक xdp_verdict;
	पूर्णांक rc = 0;
	पूर्णांक i;

	netअगर_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
		  "%s qid %d\n", __func__, rx_ring->qid);
	res_budget = budget;
	xdp_init_buff(&xdp, ENA_PAGE_SIZE, &rx_ring->xdp_rxq);

	करो अणु
		xdp_verdict = XDP_PASS;
		skb = शून्य;
		ena_rx_ctx.ena_bufs = rx_ring->ena_bufs;
		ena_rx_ctx.max_bufs = rx_ring->sgl_size;
		ena_rx_ctx.descs = 0;
		ena_rx_ctx.pkt_offset = 0;
		rc = ena_com_rx_pkt(rx_ring->ena_com_io_cq,
				    rx_ring->ena_com_io_sq,
				    &ena_rx_ctx);
		अगर (unlikely(rc))
			जाओ error;

		अगर (unlikely(ena_rx_ctx.descs == 0))
			अवरोध;

		/* First descriptor might have an offset set by the device */
		rx_info = &rx_ring->rx_buffer_info[rx_ring->ena_bufs[0].req_id];
		rx_info->page_offset += ena_rx_ctx.pkt_offset;

		netअगर_dbg(rx_ring->adapter, rx_status, rx_ring->netdev,
			  "rx_poll: q %d got packet from ena. descs #: %d l3 proto %d l4 proto %d hash: %x\n",
			  rx_ring->qid, ena_rx_ctx.descs, ena_rx_ctx.l3_proto,
			  ena_rx_ctx.l4_proto, ena_rx_ctx.hash);

		अगर (ena_xdp_present_ring(rx_ring))
			xdp_verdict = ena_xdp_handle_buff(rx_ring, &xdp);

		/* allocate skb and fill it */
		अगर (xdp_verdict == XDP_PASS)
			skb = ena_rx_skb(rx_ring,
					 rx_ring->ena_bufs,
					 ena_rx_ctx.descs,
					 &next_to_clean);

		अगर (unlikely(!skb)) अणु
			क्रम (i = 0; i < ena_rx_ctx.descs; i++) अणु
				पूर्णांक req_id = rx_ring->ena_bufs[i].req_id;

				rx_ring->मुक्त_ids[next_to_clean] = req_id;
				next_to_clean =
					ENA_RX_RING_IDX_NEXT(next_to_clean,
							     rx_ring->ring_size);

				/* Packets was passed क्रम transmission, unmap it
				 * from RX side.
				 */
				अगर (xdp_verdict == XDP_TX || xdp_verdict == XDP_REसूचीECT) अणु
					ena_unmap_rx_buff(rx_ring,
							  &rx_ring->rx_buffer_info[req_id]);
					rx_ring->rx_buffer_info[req_id].page = शून्य;
				पूर्ण
			पूर्ण
			अगर (xdp_verdict != XDP_PASS) अणु
				xdp_flags |= xdp_verdict;
				res_budget--;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		ena_rx_checksum(rx_ring, &ena_rx_ctx, skb);

		ena_set_rx_hash(rx_ring, &ena_rx_ctx, skb);

		skb_record_rx_queue(skb, rx_ring->qid);

		अगर (rx_ring->ena_bufs[0].len <= rx_ring->rx_copyअवरोध) अणु
			total_len += rx_ring->ena_bufs[0].len;
			rx_copyअवरोध_pkt++;
			napi_gro_receive(napi, skb);
		पूर्ण अन्यथा अणु
			total_len += skb->len;
			napi_gro_frags(napi);
		पूर्ण

		res_budget--;
	पूर्ण जबतक (likely(res_budget));

	work_करोne = budget - res_budget;
	rx_ring->per_napi_packets += work_करोne;
	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->rx_stats.bytes += total_len;
	rx_ring->rx_stats.cnt += work_करोne;
	rx_ring->rx_stats.rx_copyअवरोध_pkt += rx_copyअवरोध_pkt;
	u64_stats_update_end(&rx_ring->syncp);

	rx_ring->next_to_clean = next_to_clean;

	refill_required = ena_com_मुक्त_q_entries(rx_ring->ena_com_io_sq);
	refill_threshold =
		min_t(पूर्णांक, rx_ring->ring_size / ENA_RX_REFILL_THRESH_DIVIDER,
		      ENA_RX_REFILL_THRESH_PACKET);

	/* Optimization, try to batch new rx buffers */
	अगर (refill_required > refill_threshold) अणु
		ena_com_update_dev_comp_head(rx_ring->ena_com_io_cq);
		ena_refill_rx_bufs(rx_ring, refill_required);
	पूर्ण

	अगर (xdp_flags & XDP_REसूचीECT)
		xdp_करो_flush_map();

	वापस work_करोne;

error:
	adapter = netdev_priv(rx_ring->netdev);

	अगर (rc == -ENOSPC) अणु
		ena_increase_stat(&rx_ring->rx_stats.bad_desc_num, 1,
				  &rx_ring->syncp);
		adapter->reset_reason = ENA_REGS_RESET_TOO_MANY_RX_DESCS;
	पूर्ण अन्यथा अणु
		ena_increase_stat(&rx_ring->rx_stats.bad_req_id, 1,
				  &rx_ring->syncp);
		adapter->reset_reason = ENA_REGS_RESET_INV_RX_REQ_ID;
	पूर्ण

	set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);

	वापस 0;
पूर्ण

अटल व्योम ena_dim_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dim *dim = container_of(w, काष्ठा dim, work);
	काष्ठा dim_cq_moder cur_moder =
		net_dim_get_rx_moderation(dim->mode, dim->profile_ix);
	काष्ठा ena_napi *ena_napi = container_of(dim, काष्ठा ena_napi, dim);

	ena_napi->rx_ring->smoothed_पूर्णांकerval = cur_moder.usec;
	dim->state = DIM_START_MEASURE;
पूर्ण

अटल व्योम ena_adjust_adaptive_rx_पूर्णांकr_moderation(काष्ठा ena_napi *ena_napi)
अणु
	काष्ठा dim_sample dim_sample;
	काष्ठा ena_ring *rx_ring = ena_napi->rx_ring;

	अगर (!rx_ring->per_napi_packets)
		वापस;

	rx_ring->non_empty_napi_events++;

	dim_update_sample(rx_ring->non_empty_napi_events,
			  rx_ring->rx_stats.cnt,
			  rx_ring->rx_stats.bytes,
			  &dim_sample);

	net_dim(&ena_napi->dim, dim_sample);

	rx_ring->per_napi_packets = 0;
पूर्ण

अटल व्योम ena_unmask_पूर्णांकerrupt(काष्ठा ena_ring *tx_ring,
					काष्ठा ena_ring *rx_ring)
अणु
	काष्ठा ena_eth_io_पूर्णांकr_reg पूर्णांकr_reg;
	u32 rx_पूर्णांकerval = 0;
	/* Rx ring can be शून्य when क्रम XDP tx queues which करोn't have an
	 * accompanying rx_ring pair.
	 */
	अगर (rx_ring)
		rx_पूर्णांकerval = ena_com_get_adaptive_moderation_enabled(rx_ring->ena_dev) ?
			rx_ring->smoothed_पूर्णांकerval :
			ena_com_get_nonadaptive_moderation_पूर्णांकerval_rx(rx_ring->ena_dev);

	/* Update पूर्णांकr रेजिस्टर: rx पूर्णांकr delay,
	 * tx पूर्णांकr delay and पूर्णांकerrupt unmask
	 */
	ena_com_update_पूर्णांकr_reg(&पूर्णांकr_reg,
				rx_पूर्णांकerval,
				tx_ring->smoothed_पूर्णांकerval,
				true);

	ena_increase_stat(&tx_ring->tx_stats.unmask_पूर्णांकerrupt, 1,
			  &tx_ring->syncp);

	/* It is a shared MSI-X.
	 * Tx and Rx CQ have poपूर्णांकer to it.
	 * So we use one of them to reach the पूर्णांकr reg
	 * The Tx ring is used because the rx_ring is शून्य क्रम XDP queues
	 */
	ena_com_unmask_पूर्णांकr(tx_ring->ena_com_io_cq, &पूर्णांकr_reg);
पूर्ण

अटल व्योम ena_update_ring_numa_node(काष्ठा ena_ring *tx_ring,
					     काष्ठा ena_ring *rx_ring)
अणु
	पूर्णांक cpu = get_cpu();
	पूर्णांक numa_node;

	/* Check only one ring since the 2 rings are running on the same cpu */
	अगर (likely(tx_ring->cpu == cpu))
		जाओ out;

	numa_node = cpu_to_node(cpu);
	put_cpu();

	अगर (numa_node != NUMA_NO_NODE) अणु
		ena_com_update_numa_node(tx_ring->ena_com_io_cq, numa_node);
		अगर (rx_ring)
			ena_com_update_numa_node(rx_ring->ena_com_io_cq,
						 numa_node);
	पूर्ण

	tx_ring->cpu = cpu;
	अगर (rx_ring)
		rx_ring->cpu = cpu;

	वापस;
out:
	put_cpu();
पूर्ण

अटल पूर्णांक ena_clean_xdp_irq(काष्ठा ena_ring *xdp_ring, u32 budget)
अणु
	u32 total_करोne = 0;
	u16 next_to_clean;
	u32 tx_bytes = 0;
	पूर्णांक tx_pkts = 0;
	u16 req_id;
	पूर्णांक rc;

	अगर (unlikely(!xdp_ring))
		वापस 0;
	next_to_clean = xdp_ring->next_to_clean;

	जबतक (tx_pkts < budget) अणु
		काष्ठा ena_tx_buffer *tx_info;
		काष्ठा xdp_frame *xdpf;

		rc = ena_com_tx_comp_req_id_get(xdp_ring->ena_com_io_cq,
						&req_id);
		अगर (rc)
			अवरोध;

		rc = validate_xdp_req_id(xdp_ring, req_id);
		अगर (rc)
			अवरोध;

		tx_info = &xdp_ring->tx_buffer_info[req_id];
		xdpf = tx_info->xdpf;

		tx_info->xdpf = शून्य;
		tx_info->last_jअगरfies = 0;
		ena_unmap_tx_buff(xdp_ring, tx_info);

		netअगर_dbg(xdp_ring->adapter, tx_करोne, xdp_ring->netdev,
			  "tx_poll: q %d skb %p completed\n", xdp_ring->qid,
			  xdpf);

		tx_bytes += xdpf->len;
		tx_pkts++;
		total_करोne += tx_info->tx_descs;

		xdp_वापस_frame(xdpf);
		xdp_ring->मुक्त_ids[next_to_clean] = req_id;
		next_to_clean = ENA_TX_RING_IDX_NEXT(next_to_clean,
						     xdp_ring->ring_size);
	पूर्ण

	xdp_ring->next_to_clean = next_to_clean;
	ena_com_comp_ack(xdp_ring->ena_com_io_sq, total_करोne);
	ena_com_update_dev_comp_head(xdp_ring->ena_com_io_cq);

	netअगर_dbg(xdp_ring->adapter, tx_करोne, xdp_ring->netdev,
		  "tx_poll: q %d done. total pkts: %d\n",
		  xdp_ring->qid, tx_pkts);

	वापस tx_pkts;
पूर्ण

अटल पूर्णांक ena_io_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ena_napi *ena_napi = container_of(napi, काष्ठा ena_napi, napi);
	काष्ठा ena_ring *tx_ring, *rx_ring;
	पूर्णांक tx_work_करोne;
	पूर्णांक rx_work_करोne = 0;
	पूर्णांक tx_budget;
	पूर्णांक napi_comp_call = 0;
	पूर्णांक ret;

	tx_ring = ena_napi->tx_ring;
	rx_ring = ena_napi->rx_ring;

	tx_ring->first_पूर्णांकerrupt = ena_napi->first_पूर्णांकerrupt;
	rx_ring->first_पूर्णांकerrupt = ena_napi->first_पूर्णांकerrupt;

	tx_budget = tx_ring->ring_size / ENA_TX_POLL_BUDGET_DIVIDER;

	अगर (!test_bit(ENA_FLAG_DEV_UP, &tx_ring->adapter->flags) ||
	    test_bit(ENA_FLAG_TRIGGER_RESET, &tx_ring->adapter->flags)) अणु
		napi_complete_करोne(napi, 0);
		वापस 0;
	पूर्ण

	tx_work_करोne = ena_clean_tx_irq(tx_ring, tx_budget);
	/* On netpoll the budget is zero and the handler should only clean the
	 * tx completions.
	 */
	अगर (likely(budget))
		rx_work_करोne = ena_clean_rx_irq(rx_ring, napi, budget);

	/* If the device is about to reset or करोwn, aव्योम unmask
	 * the पूर्णांकerrupt and वापस 0 so NAPI won't reschedule
	 */
	अगर (unlikely(!test_bit(ENA_FLAG_DEV_UP, &tx_ring->adapter->flags) ||
		     test_bit(ENA_FLAG_TRIGGER_RESET, &tx_ring->adapter->flags))) अणु
		napi_complete_करोne(napi, 0);
		ret = 0;

	पूर्ण अन्यथा अगर ((budget > rx_work_करोne) && (tx_budget > tx_work_करोne)) अणु
		napi_comp_call = 1;

		/* Update numa and unmask the पूर्णांकerrupt only when schedule
		 * from the पूर्णांकerrupt context (vs from sk_busy_loop)
		 */
		अगर (napi_complete_करोne(napi, rx_work_करोne) &&
		    READ_ONCE(ena_napi->पूर्णांकerrupts_masked)) अणु
			smp_rmb(); /* make sure पूर्णांकerrupts_masked is पढ़ो */
			WRITE_ONCE(ena_napi->पूर्णांकerrupts_masked, false);
			/* We apply adaptive moderation on Rx path only.
			 * Tx uses अटल पूर्णांकerrupt moderation.
			 */
			अगर (ena_com_get_adaptive_moderation_enabled(rx_ring->ena_dev))
				ena_adjust_adaptive_rx_पूर्णांकr_moderation(ena_napi);

			ena_unmask_पूर्णांकerrupt(tx_ring, rx_ring);
		पूर्ण

		ena_update_ring_numa_node(tx_ring, rx_ring);

		ret = rx_work_करोne;
	पूर्ण अन्यथा अणु
		ret = budget;
	पूर्ण

	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->tx_stats.napi_comp += napi_comp_call;
	tx_ring->tx_stats.tx_poll++;
	u64_stats_update_end(&tx_ring->syncp);

	वापस ret;
पूर्ण

अटल irqवापस_t ena_पूर्णांकr_msix_mgmnt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ena_adapter *adapter = (काष्ठा ena_adapter *)data;

	ena_com_admin_q_comp_पूर्णांकr_handler(adapter->ena_dev);

	/* Don't call the aenq handler beक्रमe probe is करोne */
	अगर (likely(test_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags)))
		ena_com_aenq_पूर्णांकr_handler(adapter->ena_dev, data);

	वापस IRQ_HANDLED;
पूर्ण

/* ena_पूर्णांकr_msix_io - MSI-X Interrupt Handler क्रम Tx/Rx
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface निजी napi device काष्ठाure
 */
अटल irqवापस_t ena_पूर्णांकr_msix_io(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ena_napi *ena_napi = data;

	ena_napi->first_पूर्णांकerrupt = true;

	WRITE_ONCE(ena_napi->पूर्णांकerrupts_masked, true);
	smp_wmb(); /* ग_लिखो पूर्णांकerrupts_masked beक्रमe calling napi */

	napi_schedule_irqoff(&ena_napi->napi);

	वापस IRQ_HANDLED;
पूर्ण

/* Reserve a single MSI-X vector क्रम management (admin + aenq).
 * plus reserve one vector क्रम each potential io queue.
 * the number of potential io queues is the minimum of what the device
 * supports and the number of vCPUs.
 */
अटल पूर्णांक ena_enable_msix(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक msix_vecs, irq_cnt;

	अगर (test_bit(ENA_FLAG_MSIX_ENABLED, &adapter->flags)) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "Error, MSI-X is already enabled\n");
		वापस -EPERM;
	पूर्ण

	/* Reserved the max msix vectors we might need */
	msix_vecs = ENA_MAX_MSIX_VEC(adapter->max_num_io_queues);
	netअगर_dbg(adapter, probe, adapter->netdev,
		  "Trying to enable MSI-X, vectors %d\n", msix_vecs);

	irq_cnt = pci_alloc_irq_vectors(adapter->pdev, ENA_MIN_MSIX_VEC,
					msix_vecs, PCI_IRQ_MSIX);

	अगर (irq_cnt < 0) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "Failed to enable MSI-X. irq_cnt %d\n", irq_cnt);
		वापस -ENOSPC;
	पूर्ण

	अगर (irq_cnt != msix_vecs) अणु
		netअगर_notice(adapter, probe, adapter->netdev,
			     "Enable only %d MSI-X (out of %d), reduce the number of queues\n",
			     irq_cnt, msix_vecs);
		adapter->num_io_queues = irq_cnt - ENA_ADMIN_MSIX_VEC;
	पूर्ण

	अगर (ena_init_rx_cpu_rmap(adapter))
		netअगर_warn(adapter, probe, adapter->netdev,
			   "Failed to map IRQs to CPUs\n");

	adapter->msix_vecs = irq_cnt;
	set_bit(ENA_FLAG_MSIX_ENABLED, &adapter->flags);

	वापस 0;
पूर्ण

अटल व्योम ena_setup_mgmnt_पूर्णांकr(काष्ठा ena_adapter *adapter)
अणु
	u32 cpu;

	snम_लिखो(adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].name,
		 ENA_IRQNAME_SIZE, "ena-mgmnt@pci:%s",
		 pci_name(adapter->pdev));
	adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].handler =
		ena_पूर्णांकr_msix_mgmnt;
	adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].data = adapter;
	adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].vector =
		pci_irq_vector(adapter->pdev, ENA_MGMNT_IRQ_IDX);
	cpu = cpumask_first(cpu_online_mask);
	adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].cpu = cpu;
	cpumask_set_cpu(cpu,
			&adapter->irq_tbl[ENA_MGMNT_IRQ_IDX].affinity_hपूर्णांक_mask);
पूर्ण

अटल व्योम ena_setup_io_पूर्णांकr(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा net_device *netdev;
	पूर्णांक irq_idx, i, cpu;
	पूर्णांक io_queue_count;

	netdev = adapter->netdev;
	io_queue_count = adapter->num_io_queues + adapter->xdp_num_queues;

	क्रम (i = 0; i < io_queue_count; i++) अणु
		irq_idx = ENA_IO_IRQ_IDX(i);
		cpu = i % num_online_cpus();

		snम_लिखो(adapter->irq_tbl[irq_idx].name, ENA_IRQNAME_SIZE,
			 "%s-Tx-Rx-%d", netdev->name, i);
		adapter->irq_tbl[irq_idx].handler = ena_पूर्णांकr_msix_io;
		adapter->irq_tbl[irq_idx].data = &adapter->ena_napi[i];
		adapter->irq_tbl[irq_idx].vector =
			pci_irq_vector(adapter->pdev, irq_idx);
		adapter->irq_tbl[irq_idx].cpu = cpu;

		cpumask_set_cpu(cpu,
				&adapter->irq_tbl[irq_idx].affinity_hपूर्णांक_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक ena_request_mgmnt_irq(काष्ठा ena_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ena_irq *irq;
	पूर्णांक rc;

	irq = &adapter->irq_tbl[ENA_MGMNT_IRQ_IDX];
	rc = request_irq(irq->vector, irq->handler, flags, irq->name,
			 irq->data);
	अगर (rc) अणु
		netअगर_err(adapter, probe, adapter->netdev,
			  "Failed to request admin irq\n");
		वापस rc;
	पूर्ण

	netअगर_dbg(adapter, probe, adapter->netdev,
		  "Set affinity hint of mgmnt irq.to 0x%lx (irq vector: %d)\n",
		  irq->affinity_hपूर्णांक_mask.bits[0], irq->vector);

	irq_set_affinity_hपूर्णांक(irq->vector, &irq->affinity_hपूर्णांक_mask);

	वापस rc;
पूर्ण

अटल पूर्णांक ena_request_io_irq(काष्ठा ena_adapter *adapter)
अणु
	u32 io_queue_count = adapter->num_io_queues + adapter->xdp_num_queues;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा ena_irq *irq;
	पूर्णांक rc = 0, i, k;

	अगर (!test_bit(ENA_FLAG_MSIX_ENABLED, &adapter->flags)) अणु
		netअगर_err(adapter, अगरup, adapter->netdev,
			  "Failed to request I/O IRQ: MSI-X is not enabled\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = ENA_IO_IRQ_FIRST_IDX; i < ENA_MAX_MSIX_VEC(io_queue_count); i++) अणु
		irq = &adapter->irq_tbl[i];
		rc = request_irq(irq->vector, irq->handler, flags, irq->name,
				 irq->data);
		अगर (rc) अणु
			netअगर_err(adapter, अगरup, adapter->netdev,
				  "Failed to request I/O IRQ. index %d rc %d\n",
				   i, rc);
			जाओ err;
		पूर्ण

		netअगर_dbg(adapter, अगरup, adapter->netdev,
			  "Set affinity hint of irq. index %d to 0x%lx (irq vector: %d)\n",
			  i, irq->affinity_hपूर्णांक_mask.bits[0], irq->vector);

		irq_set_affinity_hपूर्णांक(irq->vector, &irq->affinity_hपूर्णांक_mask);
	पूर्ण

	वापस rc;

err:
	क्रम (k = ENA_IO_IRQ_FIRST_IDX; k < i; k++) अणु
		irq = &adapter->irq_tbl[k];
		मुक्त_irq(irq->vector, irq->data);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ena_मुक्त_mgmnt_irq(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_irq *irq;

	irq = &adapter->irq_tbl[ENA_MGMNT_IRQ_IDX];
	synchronize_irq(irq->vector);
	irq_set_affinity_hपूर्णांक(irq->vector, शून्य);
	मुक्त_irq(irq->vector, irq->data);
पूर्ण

अटल व्योम ena_मुक्त_io_irq(काष्ठा ena_adapter *adapter)
अणु
	u32 io_queue_count = adapter->num_io_queues + adapter->xdp_num_queues;
	काष्ठा ena_irq *irq;
	पूर्णांक i;

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर (adapter->msix_vecs >= 1) अणु
		मुक्त_irq_cpu_rmap(adapter->netdev->rx_cpu_rmap);
		adapter->netdev->rx_cpu_rmap = शून्य;
	पूर्ण
#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

	क्रम (i = ENA_IO_IRQ_FIRST_IDX; i < ENA_MAX_MSIX_VEC(io_queue_count); i++) अणु
		irq = &adapter->irq_tbl[i];
		irq_set_affinity_hपूर्णांक(irq->vector, शून्य);
		मुक्त_irq(irq->vector, irq->data);
	पूर्ण
पूर्ण

अटल व्योम ena_disable_msix(काष्ठा ena_adapter *adapter)
अणु
	अगर (test_and_clear_bit(ENA_FLAG_MSIX_ENABLED, &adapter->flags))
		pci_मुक्त_irq_vectors(adapter->pdev);
पूर्ण

अटल व्योम ena_disable_io_पूर्णांकr_sync(काष्ठा ena_adapter *adapter)
अणु
	u32 io_queue_count = adapter->num_io_queues + adapter->xdp_num_queues;
	पूर्णांक i;

	अगर (!netअगर_running(adapter->netdev))
		वापस;

	क्रम (i = ENA_IO_IRQ_FIRST_IDX; i < ENA_MAX_MSIX_VEC(io_queue_count); i++)
		synchronize_irq(adapter->irq_tbl[i].vector);
पूर्ण

अटल व्योम ena_del_napi_in_range(काष्ठा ena_adapter *adapter,
				  पूर्णांक first_index,
				  पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = first_index; i < first_index + count; i++) अणु
		netअगर_napi_del(&adapter->ena_napi[i].napi);

		WARN_ON(!ENA_IS_XDP_INDEX(adapter, i) &&
			adapter->ena_napi[i].xdp_ring);
	पूर्ण
पूर्ण

अटल व्योम ena_init_napi_in_range(काष्ठा ena_adapter *adapter,
				   पूर्णांक first_index, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = first_index; i < first_index + count; i++) अणु
		काष्ठा ena_napi *napi = &adapter->ena_napi[i];

		netअगर_napi_add(adapter->netdev,
			       &napi->napi,
			       ENA_IS_XDP_INDEX(adapter, i) ? ena_xdp_io_poll : ena_io_poll,
			       ENA_NAPI_BUDGET);

		अगर (!ENA_IS_XDP_INDEX(adapter, i)) अणु
			napi->rx_ring = &adapter->rx_ring[i];
			napi->tx_ring = &adapter->tx_ring[i];
		पूर्ण अन्यथा अणु
			napi->xdp_ring = &adapter->tx_ring[i];
		पूर्ण
		napi->qid = i;
	पूर्ण
पूर्ण

अटल व्योम ena_napi_disable_in_range(काष्ठा ena_adapter *adapter,
				      पूर्णांक first_index,
				      पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = first_index; i < first_index + count; i++)
		napi_disable(&adapter->ena_napi[i].napi);
पूर्ण

अटल व्योम ena_napi_enable_in_range(काष्ठा ena_adapter *adapter,
				     पूर्णांक first_index,
				     पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = first_index; i < first_index + count; i++)
		napi_enable(&adapter->ena_napi[i].napi);
पूर्ण

/* Configure the Rx क्रमwarding */
अटल पूर्णांक ena_rss_configure(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	पूर्णांक rc;

	/* In हाल the RSS table wasn't initialized by probe */
	अगर (!ena_dev->rss.tbl_log_size) अणु
		rc = ena_rss_init_शेष(adapter);
		अगर (rc && (rc != -EOPNOTSUPP)) अणु
			netअगर_err(adapter, अगरup, adapter->netdev,
				  "Failed to init RSS rc: %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	/* Set indirect table */
	rc = ena_com_indirect_table_set(ena_dev);
	अगर (unlikely(rc && rc != -EOPNOTSUPP))
		वापस rc;

	/* Configure hash function (अगर supported) */
	rc = ena_com_set_hash_function(ena_dev);
	अगर (unlikely(rc && (rc != -EOPNOTSUPP)))
		वापस rc;

	/* Configure hash inमाला_दो (अगर supported) */
	rc = ena_com_set_hash_ctrl(ena_dev);
	अगर (unlikely(rc && (rc != -EOPNOTSUPP)))
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_up_complete(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक rc;

	rc = ena_rss_configure(adapter);
	अगर (rc)
		वापस rc;

	ena_change_mtu(adapter->netdev, adapter->netdev->mtu);

	ena_refill_all_rx_bufs(adapter);

	/* enable transmits */
	netअगर_tx_start_all_queues(adapter->netdev);

	ena_napi_enable_in_range(adapter,
				 0,
				 adapter->xdp_num_queues + adapter->num_io_queues);

	वापस 0;
पूर्ण

अटल पूर्णांक ena_create_io_tx_queue(काष्ठा ena_adapter *adapter, पूर्णांक qid)
अणु
	काष्ठा ena_com_create_io_ctx ctx;
	काष्ठा ena_com_dev *ena_dev;
	काष्ठा ena_ring *tx_ring;
	u32 msix_vector;
	u16 ena_qid;
	पूर्णांक rc;

	ena_dev = adapter->ena_dev;

	tx_ring = &adapter->tx_ring[qid];
	msix_vector = ENA_IO_IRQ_IDX(qid);
	ena_qid = ENA_IO_TXQ_IDX(qid);

	स_रखो(&ctx, 0x0, माप(ctx));

	ctx.direction = ENA_COM_IO_QUEUE_सूचीECTION_TX;
	ctx.qid = ena_qid;
	ctx.mem_queue_type = ena_dev->tx_mem_queue_type;
	ctx.msix_vector = msix_vector;
	ctx.queue_size = tx_ring->ring_size;
	ctx.numa_node = cpu_to_node(tx_ring->cpu);

	rc = ena_com_create_io_queue(ena_dev, &ctx);
	अगर (rc) अणु
		netअगर_err(adapter, अगरup, adapter->netdev,
			  "Failed to create I/O TX queue num %d rc: %d\n",
			  qid, rc);
		वापस rc;
	पूर्ण

	rc = ena_com_get_io_handlers(ena_dev, ena_qid,
				     &tx_ring->ena_com_io_sq,
				     &tx_ring->ena_com_io_cq);
	अगर (rc) अणु
		netअगर_err(adapter, अगरup, adapter->netdev,
			  "Failed to get TX queue handlers. TX queue num %d rc: %d\n",
			  qid, rc);
		ena_com_destroy_io_queue(ena_dev, ena_qid);
		वापस rc;
	पूर्ण

	ena_com_update_numa_node(tx_ring->ena_com_io_cq, ctx.numa_node);
	वापस rc;
पूर्ण

अटल पूर्णांक ena_create_io_tx_queues_in_range(काष्ठा ena_adapter *adapter,
					    पूर्णांक first_index, पूर्णांक count)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	पूर्णांक rc, i;

	क्रम (i = first_index; i < first_index + count; i++) अणु
		rc = ena_create_io_tx_queue(adapter, i);
		अगर (rc)
			जाओ create_err;
	पूर्ण

	वापस 0;

create_err:
	जबतक (i-- > first_index)
		ena_com_destroy_io_queue(ena_dev, ENA_IO_TXQ_IDX(i));

	वापस rc;
पूर्ण

अटल पूर्णांक ena_create_io_rx_queue(काष्ठा ena_adapter *adapter, पूर्णांक qid)
अणु
	काष्ठा ena_com_dev *ena_dev;
	काष्ठा ena_com_create_io_ctx ctx;
	काष्ठा ena_ring *rx_ring;
	u32 msix_vector;
	u16 ena_qid;
	पूर्णांक rc;

	ena_dev = adapter->ena_dev;

	rx_ring = &adapter->rx_ring[qid];
	msix_vector = ENA_IO_IRQ_IDX(qid);
	ena_qid = ENA_IO_RXQ_IDX(qid);

	स_रखो(&ctx, 0x0, माप(ctx));

	ctx.qid = ena_qid;
	ctx.direction = ENA_COM_IO_QUEUE_सूचीECTION_RX;
	ctx.mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
	ctx.msix_vector = msix_vector;
	ctx.queue_size = rx_ring->ring_size;
	ctx.numa_node = cpu_to_node(rx_ring->cpu);

	rc = ena_com_create_io_queue(ena_dev, &ctx);
	अगर (rc) अणु
		netअगर_err(adapter, अगरup, adapter->netdev,
			  "Failed to create I/O RX queue num %d rc: %d\n",
			  qid, rc);
		वापस rc;
	पूर्ण

	rc = ena_com_get_io_handlers(ena_dev, ena_qid,
				     &rx_ring->ena_com_io_sq,
				     &rx_ring->ena_com_io_cq);
	अगर (rc) अणु
		netअगर_err(adapter, अगरup, adapter->netdev,
			  "Failed to get RX queue handlers. RX queue num %d rc: %d\n",
			  qid, rc);
		जाओ err;
	पूर्ण

	ena_com_update_numa_node(rx_ring->ena_com_io_cq, ctx.numa_node);

	वापस rc;
err:
	ena_com_destroy_io_queue(ena_dev, ena_qid);
	वापस rc;
पूर्ण

अटल पूर्णांक ena_create_all_io_rx_queues(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	पूर्णांक rc, i;

	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		rc = ena_create_io_rx_queue(adapter, i);
		अगर (rc)
			जाओ create_err;
		INIT_WORK(&adapter->ena_napi[i].dim.work, ena_dim_work);
	पूर्ण

	वापस 0;

create_err:
	जबतक (i--) अणु
		cancel_work_sync(&adapter->ena_napi[i].dim.work);
		ena_com_destroy_io_queue(ena_dev, ENA_IO_RXQ_IDX(i));
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम set_io_rings_size(काष्ठा ena_adapter *adapter,
			      पूर्णांक new_tx_size,
			      पूर्णांक new_rx_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		adapter->tx_ring[i].ring_size = new_tx_size;
		adapter->rx_ring[i].ring_size = new_rx_size;
	पूर्ण
पूर्ण

/* This function allows queue allocation to backoff when the प्रणाली is
 * low on memory. If there is not enough memory to allocate io queues
 * the driver will try to allocate smaller queues.
 *
 * The backoff algorithm is as follows:
 *  1. Try to allocate TX and RX and अगर successful.
 *  1.1. वापस success
 *
 *  2. Divide by 2 the size of the larger of RX and TX queues (or both अगर their size is the same).
 *
 *  3. If TX or RX is smaller than 256
 *  3.1. वापस failure.
 *  4. अन्यथा
 *  4.1. go back to 1.
 */
अटल पूर्णांक create_queues_with_size_backoff(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक rc, cur_rx_ring_size, cur_tx_ring_size;
	पूर्णांक new_rx_ring_size, new_tx_ring_size;

	/* current queue sizes might be set to smaller than the requested
	 * ones due to past queue allocation failures.
	 */
	set_io_rings_size(adapter, adapter->requested_tx_ring_size,
			  adapter->requested_rx_ring_size);

	जबतक (1) अणु
		अगर (ena_xdp_present(adapter)) अणु
			rc = ena_setup_and_create_all_xdp_queues(adapter);

			अगर (rc)
				जाओ err_setup_tx;
		पूर्ण
		rc = ena_setup_tx_resources_in_range(adapter,
						     0,
						     adapter->num_io_queues);
		अगर (rc)
			जाओ err_setup_tx;

		rc = ena_create_io_tx_queues_in_range(adapter,
						      0,
						      adapter->num_io_queues);
		अगर (rc)
			जाओ err_create_tx_queues;

		rc = ena_setup_all_rx_resources(adapter);
		अगर (rc)
			जाओ err_setup_rx;

		rc = ena_create_all_io_rx_queues(adapter);
		अगर (rc)
			जाओ err_create_rx_queues;

		वापस 0;

err_create_rx_queues:
		ena_मुक्त_all_io_rx_resources(adapter);
err_setup_rx:
		ena_destroy_all_tx_queues(adapter);
err_create_tx_queues:
		ena_मुक्त_all_io_tx_resources(adapter);
err_setup_tx:
		अगर (rc != -ENOMEM) अणु
			netअगर_err(adapter, अगरup, adapter->netdev,
				  "Queue creation failed with error code %d\n",
				  rc);
			वापस rc;
		पूर्ण

		cur_tx_ring_size = adapter->tx_ring[0].ring_size;
		cur_rx_ring_size = adapter->rx_ring[0].ring_size;

		netअगर_err(adapter, अगरup, adapter->netdev,
			  "Not enough memory to create queues with sizes TX=%d, RX=%d\n",
			  cur_tx_ring_size, cur_rx_ring_size);

		new_tx_ring_size = cur_tx_ring_size;
		new_rx_ring_size = cur_rx_ring_size;

		/* Decrease the size of the larger queue, or
		 * decrease both अगर they are the same size.
		 */
		अगर (cur_rx_ring_size <= cur_tx_ring_size)
			new_tx_ring_size = cur_tx_ring_size / 2;
		अगर (cur_rx_ring_size >= cur_tx_ring_size)
			new_rx_ring_size = cur_rx_ring_size / 2;

		अगर (new_tx_ring_size < ENA_MIN_RING_SIZE ||
		    new_rx_ring_size < ENA_MIN_RING_SIZE) अणु
			netअगर_err(adapter, अगरup, adapter->netdev,
				  "Queue creation failed with the smallest possible queue size of %d for both queues. Not retrying with smaller queues\n",
				  ENA_MIN_RING_SIZE);
			वापस rc;
		पूर्ण

		netअगर_err(adapter, अगरup, adapter->netdev,
			  "Retrying queue creation with sizes TX=%d, RX=%d\n",
			  new_tx_ring_size,
			  new_rx_ring_size);

		set_io_rings_size(adapter, new_tx_ring_size,
				  new_rx_ring_size);
	पूर्ण
पूर्ण

अटल पूर्णांक ena_up(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक io_queue_count, rc, i;

	netअगर_dbg(adapter, अगरup, adapter->netdev, "%s\n", __func__);

	io_queue_count = adapter->num_io_queues + adapter->xdp_num_queues;
	ena_setup_io_पूर्णांकr(adapter);

	/* napi poll functions should be initialized beक्रमe running
	 * request_irq(), to handle a rare condition where there is a pending
	 * पूर्णांकerrupt, causing the ISR to fire immediately जबतक the poll
	 * function wasn't set yet, causing a null dereference
	 */
	ena_init_napi_in_range(adapter, 0, io_queue_count);

	rc = ena_request_io_irq(adapter);
	अगर (rc)
		जाओ err_req_irq;

	rc = create_queues_with_size_backoff(adapter);
	अगर (rc)
		जाओ err_create_queues_with_backoff;

	rc = ena_up_complete(adapter);
	अगर (rc)
		जाओ err_up;

	अगर (test_bit(ENA_FLAG_LINK_UP, &adapter->flags))
		netअगर_carrier_on(adapter->netdev);

	ena_increase_stat(&adapter->dev_stats.पूर्णांकerface_up, 1,
			  &adapter->syncp);

	set_bit(ENA_FLAG_DEV_UP, &adapter->flags);

	/* Enable completion queues पूर्णांकerrupt */
	क्रम (i = 0; i < adapter->num_io_queues; i++)
		ena_unmask_पूर्णांकerrupt(&adapter->tx_ring[i],
				     &adapter->rx_ring[i]);

	/* schedule napi in हाल we had pending packets
	 * from the last समय we disable napi
	 */
	क्रम (i = 0; i < io_queue_count; i++)
		napi_schedule(&adapter->ena_napi[i].napi);

	वापस rc;

err_up:
	ena_destroy_all_tx_queues(adapter);
	ena_मुक्त_all_io_tx_resources(adapter);
	ena_destroy_all_rx_queues(adapter);
	ena_मुक्त_all_io_rx_resources(adapter);
err_create_queues_with_backoff:
	ena_मुक्त_io_irq(adapter);
err_req_irq:
	ena_del_napi_in_range(adapter, 0, io_queue_count);

	वापस rc;
पूर्ण

अटल व्योम ena_करोwn(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक io_queue_count = adapter->num_io_queues + adapter->xdp_num_queues;

	netअगर_info(adapter, अगरकरोwn, adapter->netdev, "%s\n", __func__);

	clear_bit(ENA_FLAG_DEV_UP, &adapter->flags);

	ena_increase_stat(&adapter->dev_stats.पूर्णांकerface_करोwn, 1,
			  &adapter->syncp);

	netअगर_carrier_off(adapter->netdev);
	netअगर_tx_disable(adapter->netdev);

	/* After this poपूर्णांक the napi handler won't enable the tx queue */
	ena_napi_disable_in_range(adapter, 0, io_queue_count);

	/* After destroy the queue there won't be any new पूर्णांकerrupts */

	अगर (test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags)) अणु
		पूर्णांक rc;

		rc = ena_com_dev_reset(adapter->ena_dev, adapter->reset_reason);
		अगर (rc)
			netअगर_err(adapter, अगरकरोwn, adapter->netdev,
				  "Device reset failed\n");
		/* stop submitting admin commands on a device that was reset */
		ena_com_set_admin_running_state(adapter->ena_dev, false);
	पूर्ण

	ena_destroy_all_io_queues(adapter);

	ena_disable_io_पूर्णांकr_sync(adapter);
	ena_मुक्त_io_irq(adapter);
	ena_del_napi_in_range(adapter, 0, io_queue_count);

	ena_मुक्त_all_tx_bufs(adapter);
	ena_मुक्त_all_rx_bufs(adapter);
	ena_मुक्त_all_io_tx_resources(adapter);
	ena_मुक्त_all_io_rx_resources(adapter);
पूर्ण

/* ena_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 */
अटल पूर्णांक ena_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc;

	/* Notअगरy the stack of the actual queue counts. */
	rc = netअगर_set_real_num_tx_queues(netdev, adapter->num_io_queues);
	अगर (rc) अणु
		netअगर_err(adapter, अगरup, netdev, "Can't set num tx queues\n");
		वापस rc;
	पूर्ण

	rc = netअगर_set_real_num_rx_queues(netdev, adapter->num_io_queues);
	अगर (rc) अणु
		netअगर_err(adapter, अगरup, netdev, "Can't set num rx queues\n");
		वापस rc;
	पूर्ण

	rc = ena_up(adapter);
	अगर (rc)
		वापस rc;

	वापस rc;
पूर्ण

/* ena_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 */
अटल पूर्णांक ena_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);

	netअगर_dbg(adapter, अगरकरोwn, netdev, "%s\n", __func__);

	अगर (!test_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags))
		वापस 0;

	अगर (test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		ena_करोwn(adapter);

	/* Check क्रम device status and issue reset अगर needed*/
	check_क्रम_admin_com_state(adapter);
	अगर (unlikely(test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))) अणु
		netअगर_err(adapter, अगरकरोwn, adapter->netdev,
			  "Destroy failure, restarting device\n");
		ena_dump_stats_to_dmesg(adapter);
		/* rtnl lock alपढ़ोy obtained in dev_ioctl() layer */
		ena_destroy_device(adapter, false);
		ena_restore_device(adapter);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ena_update_queue_sizes(काष्ठा ena_adapter *adapter,
			   u32 new_tx_size,
			   u32 new_rx_size)
अणु
	bool dev_was_up;

	dev_was_up = test_bit(ENA_FLAG_DEV_UP, &adapter->flags);
	ena_बंद(adapter->netdev);
	adapter->requested_tx_ring_size = new_tx_size;
	adapter->requested_rx_ring_size = new_rx_size;
	ena_init_io_rings(adapter,
			  0,
			  adapter->xdp_num_queues +
			  adapter->num_io_queues);
	वापस dev_was_up ? ena_up(adapter) : 0;
पूर्ण

पूर्णांक ena_update_queue_count(काष्ठा ena_adapter *adapter, u32 new_channel_count)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	पूर्णांक prev_channel_count;
	bool dev_was_up;

	dev_was_up = test_bit(ENA_FLAG_DEV_UP, &adapter->flags);
	ena_बंद(adapter->netdev);
	prev_channel_count = adapter->num_io_queues;
	adapter->num_io_queues = new_channel_count;
	अगर (ena_xdp_present(adapter) &&
	    ena_xdp_allowed(adapter) == ENA_XDP_ALLOWED) अणु
		adapter->xdp_first_ring = new_channel_count;
		adapter->xdp_num_queues = new_channel_count;
		अगर (prev_channel_count > new_channel_count)
			ena_xdp_exchange_program_rx_in_range(adapter,
							     शून्य,
							     new_channel_count,
							     prev_channel_count);
		अन्यथा
			ena_xdp_exchange_program_rx_in_range(adapter,
							     adapter->xdp_bpf_prog,
							     prev_channel_count,
							     new_channel_count);
	पूर्ण

	/* We need to destroy the rss table so that the indirection
	 * table will be reinitialized by ena_up()
	 */
	ena_com_rss_destroy(ena_dev);
	ena_init_io_rings(adapter,
			  0,
			  adapter->xdp_num_queues +
			  adapter->num_io_queues);
	वापस dev_was_up ? ena_खोलो(adapter->netdev) : 0;
पूर्ण

अटल व्योम ena_tx_csum(काष्ठा ena_com_tx_ctx *ena_tx_ctx,
			काष्ठा sk_buff *skb,
			bool disable_meta_caching)
अणु
	u32 mss = skb_shinfo(skb)->gso_size;
	काष्ठा ena_com_tx_meta *ena_meta = &ena_tx_ctx->ena_meta;
	u8 l4_protocol = 0;

	अगर ((skb->ip_summed == CHECKSUM_PARTIAL) || mss) अणु
		ena_tx_ctx->l4_csum_enable = 1;
		अगर (mss) अणु
			ena_tx_ctx->tso_enable = 1;
			ena_meta->l4_hdr_len = tcp_hdr(skb)->करोff;
			ena_tx_ctx->l4_csum_partial = 0;
		पूर्ण अन्यथा अणु
			ena_tx_ctx->tso_enable = 0;
			ena_meta->l4_hdr_len = 0;
			ena_tx_ctx->l4_csum_partial = 1;
		पूर्ण

		चयन (ip_hdr(skb)->version) अणु
		हाल IPVERSION:
			ena_tx_ctx->l3_proto = ENA_ETH_IO_L3_PROTO_IPV4;
			अगर (ip_hdr(skb)->frag_off & htons(IP_DF))
				ena_tx_ctx->df = 1;
			अगर (mss)
				ena_tx_ctx->l3_csum_enable = 1;
			l4_protocol = ip_hdr(skb)->protocol;
			अवरोध;
		हाल 6:
			ena_tx_ctx->l3_proto = ENA_ETH_IO_L3_PROTO_IPV6;
			l4_protocol = ipv6_hdr(skb)->nexthdr;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (l4_protocol == IPPROTO_TCP)
			ena_tx_ctx->l4_proto = ENA_ETH_IO_L4_PROTO_TCP;
		अन्यथा
			ena_tx_ctx->l4_proto = ENA_ETH_IO_L4_PROTO_UDP;

		ena_meta->mss = mss;
		ena_meta->l3_hdr_len = skb_network_header_len(skb);
		ena_meta->l3_hdr_offset = skb_network_offset(skb);
		ena_tx_ctx->meta_valid = 1;
	पूर्ण अन्यथा अगर (disable_meta_caching) अणु
		स_रखो(ena_meta, 0, माप(*ena_meta));
		ena_tx_ctx->meta_valid = 1;
	पूर्ण अन्यथा अणु
		ena_tx_ctx->meta_valid = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ena_check_and_linearize_skb(काष्ठा ena_ring *tx_ring,
				       काष्ठा sk_buff *skb)
अणु
	पूर्णांक num_frags, header_len, rc;

	num_frags = skb_shinfo(skb)->nr_frags;
	header_len = skb_headlen(skb);

	अगर (num_frags < tx_ring->sgl_size)
		वापस 0;

	अगर ((num_frags == tx_ring->sgl_size) &&
	    (header_len < tx_ring->tx_max_header_size))
		वापस 0;

	ena_increase_stat(&tx_ring->tx_stats.linearize, 1, &tx_ring->syncp);

	rc = skb_linearize(skb);
	अगर (unlikely(rc)) अणु
		ena_increase_stat(&tx_ring->tx_stats.linearize_failed, 1,
				  &tx_ring->syncp);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ena_tx_map_skb(काष्ठा ena_ring *tx_ring,
			  काष्ठा ena_tx_buffer *tx_info,
			  काष्ठा sk_buff *skb,
			  व्योम **push_hdr,
			  u16 *header_len)
अणु
	काष्ठा ena_adapter *adapter = tx_ring->adapter;
	काष्ठा ena_com_buf *ena_buf;
	dma_addr_t dma;
	u32 skb_head_len, frag_len, last_frag;
	u16 push_len = 0;
	u16 delta = 0;
	पूर्णांक i = 0;

	skb_head_len = skb_headlen(skb);
	tx_info->skb = skb;
	ena_buf = tx_info->bufs;

	अगर (tx_ring->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) अणु
		/* When the device is LLQ mode, the driver will copy
		 * the header पूर्णांकo the device memory space.
		 * the ena_com layer assume the header is in a linear
		 * memory space.
		 * This assumption might be wrong since part of the header
		 * can be in the fragmented buffers.
		 * Use skb_header_poपूर्णांकer to make sure the header is in a
		 * linear memory space.
		 */

		push_len = min_t(u32, skb->len, tx_ring->tx_max_header_size);
		*push_hdr = skb_header_poपूर्णांकer(skb, 0, push_len,
					       tx_ring->push_buf_पूर्णांकermediate_buf);
		*header_len = push_len;
		अगर (unlikely(skb->data != *push_hdr)) अणु
			ena_increase_stat(&tx_ring->tx_stats.llq_buffer_copy, 1,
					  &tx_ring->syncp);

			delta = push_len - skb_head_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		*push_hdr = शून्य;
		*header_len = min_t(u32, skb_head_len,
				    tx_ring->tx_max_header_size);
	पूर्ण

	netअगर_dbg(adapter, tx_queued, adapter->netdev,
		  "skb: %p header_buf->vaddr: %p push_len: %d\n", skb,
		  *push_hdr, push_len);

	अगर (skb_head_len > push_len) अणु
		dma = dma_map_single(tx_ring->dev, skb->data + push_len,
				     skb_head_len - push_len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(tx_ring->dev, dma)))
			जाओ error_report_dma_error;

		ena_buf->paddr = dma;
		ena_buf->len = skb_head_len - push_len;

		ena_buf++;
		tx_info->num_of_bufs++;
		tx_info->map_linear_data = 1;
	पूर्ण अन्यथा अणु
		tx_info->map_linear_data = 0;
	पूर्ण

	last_frag = skb_shinfo(skb)->nr_frags;

	क्रम (i = 0; i < last_frag; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		frag_len = skb_frag_size(frag);

		अगर (unlikely(delta >= frag_len)) अणु
			delta -= frag_len;
			जारी;
		पूर्ण

		dma = skb_frag_dma_map(tx_ring->dev, frag, delta,
				       frag_len - delta, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(tx_ring->dev, dma)))
			जाओ error_report_dma_error;

		ena_buf->paddr = dma;
		ena_buf->len = frag_len - delta;
		ena_buf++;
		tx_info->num_of_bufs++;
		delta = 0;
	पूर्ण

	वापस 0;

error_report_dma_error:
	ena_increase_stat(&tx_ring->tx_stats.dma_mapping_err, 1,
			  &tx_ring->syncp);
	netअगर_warn(adapter, tx_queued, adapter->netdev, "Failed to map skb\n");

	tx_info->skb = शून्य;

	tx_info->num_of_bufs += i;
	ena_unmap_tx_buff(tx_ring, tx_info);

	वापस -EINVAL;
पूर्ण

/* Called with netअगर_tx_lock. */
अटल netdev_tx_t ena_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(dev);
	काष्ठा ena_tx_buffer *tx_info;
	काष्ठा ena_com_tx_ctx ena_tx_ctx;
	काष्ठा ena_ring *tx_ring;
	काष्ठा netdev_queue *txq;
	व्योम *push_hdr;
	u16 next_to_use, req_id, header_len;
	पूर्णांक qid, rc;

	netअगर_dbg(adapter, tx_queued, dev, "%s skb %p\n", __func__, skb);
	/*  Determine which tx ring we will be placed on */
	qid = skb_get_queue_mapping(skb);
	tx_ring = &adapter->tx_ring[qid];
	txq = netdev_get_tx_queue(dev, qid);

	rc = ena_check_and_linearize_skb(tx_ring, skb);
	अगर (unlikely(rc))
		जाओ error_drop_packet;

	skb_tx_बारtamp(skb);

	next_to_use = tx_ring->next_to_use;
	req_id = tx_ring->मुक्त_ids[next_to_use];
	tx_info = &tx_ring->tx_buffer_info[req_id];
	tx_info->num_of_bufs = 0;

	WARN(tx_info->skb, "SKB isn't NULL req_id %d\n", req_id);

	rc = ena_tx_map_skb(tx_ring, tx_info, skb, &push_hdr, &header_len);
	अगर (unlikely(rc))
		जाओ error_drop_packet;

	स_रखो(&ena_tx_ctx, 0x0, माप(काष्ठा ena_com_tx_ctx));
	ena_tx_ctx.ena_bufs = tx_info->bufs;
	ena_tx_ctx.push_header = push_hdr;
	ena_tx_ctx.num_bufs = tx_info->num_of_bufs;
	ena_tx_ctx.req_id = req_id;
	ena_tx_ctx.header_len = header_len;

	/* set flags and meta data */
	ena_tx_csum(&ena_tx_ctx, skb, tx_ring->disable_meta_caching);

	rc = ena_xmit_common(dev,
			     tx_ring,
			     tx_info,
			     &ena_tx_ctx,
			     next_to_use,
			     skb->len);
	अगर (rc)
		जाओ error_unmap_dma;

	netdev_tx_sent_queue(txq, skb->len);

	/* stop the queue when no more space available, the packet can have up
	 * to sgl_size + 2. one क्रम the meta descriptor and one क्रम header
	 * (अगर the header is larger than tx_max_header_size).
	 */
	अगर (unlikely(!ena_com_sq_have_enough_space(tx_ring->ena_com_io_sq,
						   tx_ring->sgl_size + 2))) अणु
		netअगर_dbg(adapter, tx_queued, dev, "%s stop queue %d\n",
			  __func__, qid);

		netअगर_tx_stop_queue(txq);
		ena_increase_stat(&tx_ring->tx_stats.queue_stop, 1,
				  &tx_ring->syncp);

		/* There is a rare condition where this function decide to
		 * stop the queue but meanजबतक clean_tx_irq updates
		 * next_to_completion and terminates.
		 * The queue will reमुख्य stopped क्रमever.
		 * To solve this issue add a mb() to make sure that
		 * netअगर_tx_stop_queue() ग_लिखो is vissible beक्रमe checking अगर
		 * there is additional space in the queue.
		 */
		smp_mb();

		अगर (ena_com_sq_have_enough_space(tx_ring->ena_com_io_sq,
						 ENA_TX_WAKEUP_THRESH)) अणु
			netअगर_tx_wake_queue(txq);
			ena_increase_stat(&tx_ring->tx_stats.queue_wakeup, 1,
					  &tx_ring->syncp);
		पूर्ण
	पूर्ण

	अगर (netअगर_xmit_stopped(txq) || !netdev_xmit_more()) अणु
		/* trigger the dma engine. ena_com_ग_लिखो_sq_करोorbell()
		 * has a mb
		 */
		ena_com_ग_लिखो_sq_करोorbell(tx_ring->ena_com_io_sq);
		ena_increase_stat(&tx_ring->tx_stats.करोorbells, 1,
				  &tx_ring->syncp);
	पूर्ण

	वापस NETDEV_TX_OK;

error_unmap_dma:
	ena_unmap_tx_buff(tx_ring, tx_info);
	tx_info->skb = शून्य;

error_drop_packet:
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल u16 ena_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा net_device *sb_dev)
अणु
	u16 qid;
	/* we suspect that this is good क्रम in--kernel network services that
	 * want to loop incoming skb rx to tx in normal user generated traffic,
	 * most probably we will not get to this
	 */
	अगर (skb_rx_queue_recorded(skb))
		qid = skb_get_rx_queue(skb);
	अन्यथा
		qid = netdev_pick_tx(dev, skb, शून्य);

	वापस qid;
पूर्ण

अटल व्योम ena_config_host_info(काष्ठा ena_com_dev *ena_dev, काष्ठा pci_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ena_admin_host_info *host_info;
	पूर्णांक rc;

	/* Allocate only the host info */
	rc = ena_com_allocate_host_info(ena_dev);
	अगर (rc) अणु
		dev_err(dev, "Cannot allocate host info\n");
		वापस;
	पूर्ण

	host_info = ena_dev->host_attr.host_info;

	host_info->bdf = (pdev->bus->number << 8) | pdev->devfn;
	host_info->os_type = ENA_ADMIN_OS_LINUX;
	host_info->kernel_ver = LINUX_VERSION_CODE;
	strlcpy(host_info->kernel_ver_str, utsname()->version,
		माप(host_info->kernel_ver_str) - 1);
	host_info->os_dist = 0;
	म_नकलन(host_info->os_dist_str, utsname()->release,
		माप(host_info->os_dist_str) - 1);
	host_info->driver_version =
		(DRV_MODULE_GEN_MAJOR) |
		(DRV_MODULE_GEN_MINOR << ENA_ADMIN_HOST_INFO_MINOR_SHIFT) |
		(DRV_MODULE_GEN_SUBMINOR << ENA_ADMIN_HOST_INFO_SUB_MINOR_SHIFT) |
		("K"[0] << ENA_ADMIN_HOST_INFO_MODULE_TYPE_SHIFT);
	host_info->num_cpus = num_online_cpus();

	host_info->driver_supported_features =
		ENA_ADMIN_HOST_INFO_RX_OFFSET_MASK |
		ENA_ADMIN_HOST_INFO_INTERRUPT_MODERATION_MASK |
		ENA_ADMIN_HOST_INFO_RX_BUF_MIRRORING_MASK |
		ENA_ADMIN_HOST_INFO_RSS_CONFIGURABLE_FUNCTION_KEY_MASK;

	rc = ena_com_set_host_attributes(ena_dev);
	अगर (rc) अणु
		अगर (rc == -EOPNOTSUPP)
			dev_warn(dev, "Cannot set host attributes\n");
		अन्यथा
			dev_err(dev, "Cannot set host attributes\n");

		जाओ err;
	पूर्ण

	वापस;

err:
	ena_com_delete_host_info(ena_dev);
पूर्ण

अटल व्योम ena_config_debug_area(काष्ठा ena_adapter *adapter)
अणु
	u32 debug_area_size;
	पूर्णांक rc, ss_count;

	ss_count = ena_get_sset_count(adapter->netdev, ETH_SS_STATS);
	अगर (ss_count <= 0) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "SS count is negative\n");
		वापस;
	पूर्ण

	/* allocate 32 bytes क्रम each string and 64bit क्रम the value */
	debug_area_size = ss_count * ETH_GSTRING_LEN + माप(u64) * ss_count;

	rc = ena_com_allocate_debug_area(adapter->ena_dev, debug_area_size);
	अगर (rc) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Cannot allocate debug area\n");
		वापस;
	पूर्ण

	rc = ena_com_set_host_attributes(adapter->ena_dev);
	अगर (rc) अणु
		अगर (rc == -EOPNOTSUPP)
			netअगर_warn(adapter, drv, adapter->netdev,
				   "Cannot set host attributes\n");
		अन्यथा
			netअगर_err(adapter, drv, adapter->netdev,
				  "Cannot set host attributes\n");
		जाओ err;
	पूर्ण

	वापस;
err:
	ena_com_delete_debug_area(adapter->ena_dev);
पूर्ण

पूर्णांक ena_update_hw_stats(काष्ठा ena_adapter *adapter)
अणु
	पूर्णांक rc = 0;

	rc = ena_com_get_eni_stats(adapter->ena_dev, &adapter->eni_stats);
	अगर (rc) अणु
		dev_info_once(&adapter->pdev->dev, "Failed to get ENI stats\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ena_get_stats64(काष्ठा net_device *netdev,
			    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ena_adapter *adapter = netdev_priv(netdev);
	काष्ठा ena_ring *rx_ring, *tx_ring;
	अचिन्हित पूर्णांक start;
	u64 rx_drops;
	u64 tx_drops;
	पूर्णांक i;

	अगर (!test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		वापस;

	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		u64 bytes, packets;

		tx_ring = &adapter->tx_ring[i];

		करो अणु
			start = u64_stats_fetch_begin_irq(&tx_ring->syncp);
			packets = tx_ring->tx_stats.cnt;
			bytes = tx_ring->tx_stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&tx_ring->syncp, start));

		stats->tx_packets += packets;
		stats->tx_bytes += bytes;

		rx_ring = &adapter->rx_ring[i];

		करो अणु
			start = u64_stats_fetch_begin_irq(&rx_ring->syncp);
			packets = rx_ring->rx_stats.cnt;
			bytes = rx_ring->rx_stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rx_ring->syncp, start));

		stats->rx_packets += packets;
		stats->rx_bytes += bytes;
	पूर्ण

	करो अणु
		start = u64_stats_fetch_begin_irq(&adapter->syncp);
		rx_drops = adapter->dev_stats.rx_drops;
		tx_drops = adapter->dev_stats.tx_drops;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&adapter->syncp, start));

	stats->rx_dropped = rx_drops;
	stats->tx_dropped = tx_drops;

	stats->multicast = 0;
	stats->collisions = 0;

	stats->rx_length_errors = 0;
	stats->rx_crc_errors = 0;
	stats->rx_frame_errors = 0;
	stats->rx_fअगरo_errors = 0;
	stats->rx_missed_errors = 0;
	stats->tx_winकरोw_errors = 0;

	stats->rx_errors = 0;
	stats->tx_errors = 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ena_netdev_ops = अणु
	.nकरो_खोलो		= ena_खोलो,
	.nकरो_stop		= ena_बंद,
	.nकरो_start_xmit		= ena_start_xmit,
	.nकरो_select_queue	= ena_select_queue,
	.nकरो_get_stats64	= ena_get_stats64,
	.nकरो_tx_समयout		= ena_tx_समयout,
	.nकरो_change_mtu		= ena_change_mtu,
	.nकरो_set_mac_address	= शून्य,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_bpf		= ena_xdp,
	.nकरो_xdp_xmit		= ena_xdp_xmit,
पूर्ण;

अटल पूर्णांक ena_device_validate_params(काष्ठा ena_adapter *adapter,
				      काष्ठा ena_com_dev_get_features_ctx *get_feat_ctx)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक rc;

	rc = ether_addr_equal(get_feat_ctx->dev_attr.mac_addr,
			      adapter->mac_addr);
	अगर (!rc) अणु
		netअगर_err(adapter, drv, netdev,
			  "Error, mac address are different\n");
		वापस -EINVAL;
	पूर्ण

	अगर (get_feat_ctx->dev_attr.max_mtu < netdev->mtu) अणु
		netअगर_err(adapter, drv, netdev,
			  "Error, device max mtu is smaller than netdev MTU\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_शेष_llq_configurations(काष्ठा ena_llq_configurations *llq_config)
अणु
	llq_config->llq_header_location = ENA_ADMIN_INLINE_HEADER;
	llq_config->llq_stride_ctrl = ENA_ADMIN_MULTIPLE_DESCS_PER_ENTRY;
	llq_config->llq_num_decs_beक्रमe_header = ENA_ADMIN_LLQ_NUM_DESCS_BEFORE_HEADER_2;
	llq_config->llq_ring_entry_size = ENA_ADMIN_LIST_ENTRY_SIZE_128B;
	llq_config->llq_ring_entry_size_value = 128;
पूर्ण

अटल पूर्णांक ena_set_queues_placement_policy(काष्ठा pci_dev *pdev,
					   काष्ठा ena_com_dev *ena_dev,
					   काष्ठा ena_admin_feature_llq_desc *llq,
					   काष्ठा ena_llq_configurations *llq_शेष_configurations)
अणु
	पूर्णांक rc;
	u32 llq_feature_mask;

	llq_feature_mask = 1 << ENA_ADMIN_LLQ;
	अगर (!(ena_dev->supported_features & llq_feature_mask)) अणु
		dev_err(&pdev->dev,
			"LLQ is not supported Fallback to host mode policy.\n");
		ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
		वापस 0;
	पूर्ण

	rc = ena_com_config_dev_mode(ena_dev, llq, llq_शेष_configurations);
	अगर (unlikely(rc)) अणु
		dev_err(&pdev->dev,
			"Failed to configure the device mode.  Fallback to host mode policy.\n");
		ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ena_map_llq_mem_bar(काष्ठा pci_dev *pdev, काष्ठा ena_com_dev *ena_dev,
			       पूर्णांक bars)
अणु
	bool has_mem_bar = !!(bars & BIT(ENA_MEM_BAR));

	अगर (!has_mem_bar) अणु
		अगर (ena_dev->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV) अणु
			dev_err(&pdev->dev,
				"ENA device does not expose LLQ bar. Fallback to host mode policy.\n");
			ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
		पूर्ण

		वापस 0;
	पूर्ण

	ena_dev->mem_bar = devm_ioremap_wc(&pdev->dev,
					   pci_resource_start(pdev, ENA_MEM_BAR),
					   pci_resource_len(pdev, ENA_MEM_BAR));

	अगर (!ena_dev->mem_bar)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ena_device_init(काष्ठा ena_com_dev *ena_dev, काष्ठा pci_dev *pdev,
			   काष्ठा ena_com_dev_get_features_ctx *get_feat_ctx,
			   bool *wd_state)
अणु
	काष्ठा ena_llq_configurations llq_config;
	काष्ठा device *dev = &pdev->dev;
	bool पढ़ोless_supported;
	u32 aenq_groups;
	पूर्णांक dma_width;
	पूर्णांक rc;

	rc = ena_com_mmio_reg_पढ़ो_request_init(ena_dev);
	अगर (rc) अणु
		dev_err(dev, "Failed to init mmio read less\n");
		वापस rc;
	पूर्ण

	/* The PCIe configuration space revision id indicate अगर mmio reg
	 * पढ़ो is disabled
	 */
	पढ़ोless_supported = !(pdev->revision & ENA_MMIO_DISABLE_REG_READ);
	ena_com_set_mmio_पढ़ो_mode(ena_dev, पढ़ोless_supported);

	rc = ena_com_dev_reset(ena_dev, ENA_REGS_RESET_NORMAL);
	अगर (rc) अणु
		dev_err(dev, "Can not reset device\n");
		जाओ err_mmio_पढ़ो_less;
	पूर्ण

	rc = ena_com_validate_version(ena_dev);
	अगर (rc) अणु
		dev_err(dev, "Device version is too low\n");
		जाओ err_mmio_पढ़ो_less;
	पूर्ण

	dma_width = ena_com_get_dma_width(ena_dev);
	अगर (dma_width < 0) अणु
		dev_err(dev, "Invalid dma width value %d", dma_width);
		rc = dma_width;
		जाओ err_mmio_पढ़ो_less;
	पूर्ण

	rc = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(dma_width));
	अगर (rc) अणु
		dev_err(dev, "dma_set_mask_and_coherent failed %d\n", rc);
		जाओ err_mmio_पढ़ो_less;
	पूर्ण

	/* ENA admin level init */
	rc = ena_com_admin_init(ena_dev, &aenq_handlers);
	अगर (rc) अणु
		dev_err(dev,
			"Can not initialize ena admin queue with device\n");
		जाओ err_mmio_पढ़ो_less;
	पूर्ण

	/* To enable the msix पूर्णांकerrupts the driver needs to know the number
	 * of queues. So the driver uses polling mode to retrieve this
	 * inक्रमmation
	 */
	ena_com_set_admin_polling_mode(ena_dev, true);

	ena_config_host_info(ena_dev, pdev);

	/* Get Device Attributes*/
	rc = ena_com_get_dev_attr_feat(ena_dev, get_feat_ctx);
	अगर (rc) अणु
		dev_err(dev, "Cannot get attribute for ena device rc=%d\n", rc);
		जाओ err_admin_init;
	पूर्ण

	/* Try to turn all the available aenq groups */
	aenq_groups = BIT(ENA_ADMIN_LINK_CHANGE) |
		BIT(ENA_ADMIN_FATAL_ERROR) |
		BIT(ENA_ADMIN_WARNING) |
		BIT(ENA_ADMIN_NOTIFICATION) |
		BIT(ENA_ADMIN_KEEP_ALIVE);

	aenq_groups &= get_feat_ctx->aenq.supported_groups;

	rc = ena_com_set_aenq_config(ena_dev, aenq_groups);
	अगर (rc) अणु
		dev_err(dev, "Cannot configure aenq groups rc= %d\n", rc);
		जाओ err_admin_init;
	पूर्ण

	*wd_state = !!(aenq_groups & BIT(ENA_ADMIN_KEEP_ALIVE));

	set_शेष_llq_configurations(&llq_config);

	rc = ena_set_queues_placement_policy(pdev, ena_dev, &get_feat_ctx->llq,
					     &llq_config);
	अगर (rc) अणु
		dev_err(dev, "ENA device init failed\n");
		जाओ err_admin_init;
	पूर्ण

	वापस 0;

err_admin_init:
	ena_com_delete_host_info(ena_dev);
	ena_com_admin_destroy(ena_dev);
err_mmio_पढ़ो_less:
	ena_com_mmio_reg_पढ़ो_request_destroy(ena_dev);

	वापस rc;
पूर्ण

अटल पूर्णांक ena_enable_msix_and_set_admin_पूर्णांकerrupts(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक rc;

	rc = ena_enable_msix(adapter);
	अगर (rc) अणु
		dev_err(dev, "Can not reserve msix vectors\n");
		वापस rc;
	पूर्ण

	ena_setup_mgmnt_पूर्णांकr(adapter);

	rc = ena_request_mgmnt_irq(adapter);
	अगर (rc) अणु
		dev_err(dev, "Can not setup management interrupts\n");
		जाओ err_disable_msix;
	पूर्ण

	ena_com_set_admin_polling_mode(ena_dev, false);

	ena_com_admin_aenq_enable(ena_dev);

	वापस 0;

err_disable_msix:
	ena_disable_msix(adapter);

	वापस rc;
पूर्ण

अटल व्योम ena_destroy_device(काष्ठा ena_adapter *adapter, bool graceful)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	bool dev_up;

	अगर (!test_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags))
		वापस;

	netअगर_carrier_off(netdev);

	del_समयr_sync(&adapter->समयr_service);

	dev_up = test_bit(ENA_FLAG_DEV_UP, &adapter->flags);
	adapter->dev_up_beक्रमe_reset = dev_up;
	अगर (!graceful)
		ena_com_set_admin_running_state(ena_dev, false);

	अगर (test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		ena_करोwn(adapter);

	/* Stop the device from sending AENQ events (in हाल reset flag is set
	 *  and device is up, ena_करोwn() alपढ़ोy reset the device.
	 */
	अगर (!(test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags) && dev_up))
		ena_com_dev_reset(adapter->ena_dev, adapter->reset_reason);

	ena_मुक्त_mgmnt_irq(adapter);

	ena_disable_msix(adapter);

	ena_com_पात_admin_commands(ena_dev);

	ena_com_रुको_क्रम_पात_completion(ena_dev);

	ena_com_admin_destroy(ena_dev);

	ena_com_mmio_reg_पढ़ो_request_destroy(ena_dev);

	/* वापस reset reason to शेष value */
	adapter->reset_reason = ENA_REGS_RESET_NORMAL;

	clear_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
	clear_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags);
पूर्ण

अटल पूर्णांक ena_restore_device(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_com_dev_get_features_ctx get_feat_ctx;
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	bool wd_state;
	पूर्णांक rc;

	set_bit(ENA_FLAG_ONGOING_RESET, &adapter->flags);
	rc = ena_device_init(ena_dev, adapter->pdev, &get_feat_ctx, &wd_state);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Can not initialize device\n");
		जाओ err;
	पूर्ण
	adapter->wd_state = wd_state;

	rc = ena_device_validate_params(adapter, &get_feat_ctx);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Validation of device parameters failed\n");
		जाओ err_device_destroy;
	पूर्ण

	rc = ena_enable_msix_and_set_admin_पूर्णांकerrupts(adapter);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Enable MSI-X failed\n");
		जाओ err_device_destroy;
	पूर्ण
	/* If the पूर्णांकerface was up beक्रमe the reset bring it up */
	अगर (adapter->dev_up_beक्रमe_reset) अणु
		rc = ena_up(adapter);
		अगर (rc) अणु
			dev_err(&pdev->dev, "Failed to create I/O queues\n");
			जाओ err_disable_msix;
		पूर्ण
	पूर्ण

	set_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags);

	clear_bit(ENA_FLAG_ONGOING_RESET, &adapter->flags);
	अगर (test_bit(ENA_FLAG_LINK_UP, &adapter->flags))
		netअगर_carrier_on(adapter->netdev);

	mod_समयr(&adapter->समयr_service, round_jअगरfies(jअगरfies + HZ));
	adapter->last_keep_alive_jअगरfies = jअगरfies;

	dev_err(&pdev->dev, "Device reset completed successfully\n");

	वापस rc;
err_disable_msix:
	ena_मुक्त_mgmnt_irq(adapter);
	ena_disable_msix(adapter);
err_device_destroy:
	ena_com_पात_admin_commands(ena_dev);
	ena_com_रुको_क्रम_पात_completion(ena_dev);
	ena_com_admin_destroy(ena_dev);
	ena_com_dev_reset(ena_dev, ENA_REGS_RESET_DRIVER_INVALID_STATE);
	ena_com_mmio_reg_पढ़ो_request_destroy(ena_dev);
err:
	clear_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags);
	clear_bit(ENA_FLAG_ONGOING_RESET, &adapter->flags);
	dev_err(&pdev->dev,
		"Reset attempt failed. Can not reset the device\n");

	वापस rc;
पूर्ण

अटल व्योम ena_fw_reset_device(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ena_adapter *adapter =
		container_of(work, काष्ठा ena_adapter, reset_task);

	rtnl_lock();

	अगर (likely(test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))) अणु
		ena_destroy_device(adapter, false);
		ena_restore_device(adapter);
	पूर्ण

	rtnl_unlock();
पूर्ण

अटल पूर्णांक check_क्रम_rx_पूर्णांकerrupt_queue(काष्ठा ena_adapter *adapter,
					काष्ठा ena_ring *rx_ring)
अणु
	अगर (likely(rx_ring->first_पूर्णांकerrupt))
		वापस 0;

	अगर (ena_com_cq_empty(rx_ring->ena_com_io_cq))
		वापस 0;

	rx_ring->no_पूर्णांकerrupt_event_cnt++;

	अगर (rx_ring->no_पूर्णांकerrupt_event_cnt == ENA_MAX_NO_INTERRUPT_ITERATIONS) अणु
		netअगर_err(adapter, rx_err, adapter->netdev,
			  "Potential MSIX issue on Rx side Queue = %d. Reset the device\n",
			  rx_ring->qid);
		adapter->reset_reason = ENA_REGS_RESET_MISS_INTERRUPT;
		smp_mb__beक्रमe_atomic();
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_missing_comp_in_tx_queue(काष्ठा ena_adapter *adapter,
					  काष्ठा ena_ring *tx_ring)
अणु
	काष्ठा ena_tx_buffer *tx_buf;
	अचिन्हित दीर्घ last_jअगरfies;
	u32 missed_tx = 0;
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < tx_ring->ring_size; i++) अणु
		tx_buf = &tx_ring->tx_buffer_info[i];
		last_jअगरfies = tx_buf->last_jअगरfies;

		अगर (last_jअगरfies == 0)
			/* no pending Tx at this location */
			जारी;

		अगर (unlikely(!tx_ring->first_पूर्णांकerrupt && समय_is_beक्रमe_jअगरfies(last_jअगरfies +
			     2 * adapter->missing_tx_completion_to))) अणु
			/* If after graceful period पूर्णांकerrupt is still not
			 * received, we schedule a reset
			 */
			netअगर_err(adapter, tx_err, adapter->netdev,
				  "Potential MSIX issue on Tx side Queue = %d. Reset the device\n",
				  tx_ring->qid);
			adapter->reset_reason = ENA_REGS_RESET_MISS_INTERRUPT;
			smp_mb__beक्रमe_atomic();
			set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
			वापस -EIO;
		पूर्ण

		अगर (unlikely(समय_is_beक्रमe_jअगरfies(last_jअगरfies +
				adapter->missing_tx_completion_to))) अणु
			अगर (!tx_buf->prपूर्णांक_once)
				netअगर_notice(adapter, tx_err, adapter->netdev,
					     "Found a Tx that wasn't completed on time, qid %d, index %d.\n",
					     tx_ring->qid, i);

			tx_buf->prपूर्णांक_once = 1;
			missed_tx++;
		पूर्ण
	पूर्ण

	अगर (unlikely(missed_tx > adapter->missing_tx_completion_threshold)) अणु
		netअगर_err(adapter, tx_err, adapter->netdev,
			  "The number of lost tx completions is above the threshold (%d > %d). Reset the device\n",
			  missed_tx,
			  adapter->missing_tx_completion_threshold);
		adapter->reset_reason =
			ENA_REGS_RESET_MISS_TX_CMPL;
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
		rc = -EIO;
	पूर्ण

	ena_increase_stat(&tx_ring->tx_stats.missed_tx, missed_tx,
			  &tx_ring->syncp);

	वापस rc;
पूर्ण

अटल व्योम check_क्रम_missing_completions(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_ring *tx_ring;
	काष्ठा ena_ring *rx_ring;
	पूर्णांक i, budget, rc;
	पूर्णांक io_queue_count;

	io_queue_count = adapter->xdp_num_queues + adapter->num_io_queues;
	/* Make sure the driver करोesn't turn the device in other process */
	smp_rmb();

	अगर (!test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		वापस;

	अगर (test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))
		वापस;

	अगर (adapter->missing_tx_completion_to == ENA_HW_HINTS_NO_TIMEOUT)
		वापस;

	budget = ENA_MONITORED_TX_QUEUES;

	क्रम (i = adapter->last_monitored_tx_qid; i < io_queue_count; i++) अणु
		tx_ring = &adapter->tx_ring[i];
		rx_ring = &adapter->rx_ring[i];

		rc = check_missing_comp_in_tx_queue(adapter, tx_ring);
		अगर (unlikely(rc))
			वापस;

		rc =  !ENA_IS_XDP_INDEX(adapter, i) ?
			check_क्रम_rx_पूर्णांकerrupt_queue(adapter, rx_ring) : 0;
		अगर (unlikely(rc))
			वापस;

		budget--;
		अगर (!budget)
			अवरोध;
	पूर्ण

	adapter->last_monitored_tx_qid = i % io_queue_count;
पूर्ण

/* trigger napi schedule after 2 consecutive detections */
#घोषणा EMPTY_RX_REFILL 2
/* For the rare हाल where the device runs out of Rx descriptors and the
 * napi handler failed to refill new Rx descriptors (due to a lack of memory
 * क्रम example).
 * This हाल will lead to a deadlock:
 * The device won't send पूर्णांकerrupts since all the new Rx packets will be dropped
 * The napi handler won't allocate new Rx descriptors so the device will be
 * able to send new packets.
 *
 * This scenario can happen when the kernel's vm.min_मुक्त_kbytes is too small.
 * It is recommended to have at least 512MB, with a minimum of 128MB क्रम
 * स्थिरrained environment).
 *
 * When such a situation is detected - Reschedule napi
 */
अटल व्योम check_क्रम_empty_rx_ring(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_ring *rx_ring;
	पूर्णांक i, refill_required;

	अगर (!test_bit(ENA_FLAG_DEV_UP, &adapter->flags))
		वापस;

	अगर (test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))
		वापस;

	क्रम (i = 0; i < adapter->num_io_queues; i++) अणु
		rx_ring = &adapter->rx_ring[i];

		refill_required = ena_com_मुक्त_q_entries(rx_ring->ena_com_io_sq);
		अगर (unlikely(refill_required == (rx_ring->ring_size - 1))) अणु
			rx_ring->empty_rx_queue++;

			अगर (rx_ring->empty_rx_queue >= EMPTY_RX_REFILL) अणु
				ena_increase_stat(&rx_ring->rx_stats.empty_rx_ring, 1,
						  &rx_ring->syncp);

				netअगर_err(adapter, drv, adapter->netdev,
					  "Trigger refill for ring %d\n", i);

				napi_schedule(rx_ring->napi);
				rx_ring->empty_rx_queue = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			rx_ring->empty_rx_queue = 0;
		पूर्ण
	पूर्ण
पूर्ण

/* Check क्रम keep alive expiration */
अटल व्योम check_क्रम_missing_keep_alive(काष्ठा ena_adapter *adapter)
अणु
	अचिन्हित दीर्घ keep_alive_expired;

	अगर (!adapter->wd_state)
		वापस;

	अगर (adapter->keep_alive_समयout == ENA_HW_HINTS_NO_TIMEOUT)
		वापस;

	keep_alive_expired = adapter->last_keep_alive_jअगरfies +
			     adapter->keep_alive_समयout;
	अगर (unlikely(समय_is_beक्रमe_jअगरfies(keep_alive_expired))) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Keep alive watchdog timeout.\n");
		ena_increase_stat(&adapter->dev_stats.wd_expired, 1,
				  &adapter->syncp);
		adapter->reset_reason = ENA_REGS_RESET_KEEP_ALIVE_TO;
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
	पूर्ण
पूर्ण

अटल व्योम check_क्रम_admin_com_state(काष्ठा ena_adapter *adapter)
अणु
	अगर (unlikely(!ena_com_get_admin_running_state(adapter->ena_dev))) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "ENA admin queue is not in running state!\n");
		ena_increase_stat(&adapter->dev_stats.admin_q_छोड़ो, 1,
				  &adapter->syncp);
		adapter->reset_reason = ENA_REGS_RESET_ADMIN_TO;
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
	पूर्ण
पूर्ण

अटल व्योम ena_update_hपूर्णांकs(काष्ठा ena_adapter *adapter,
			     काष्ठा ena_admin_ena_hw_hपूर्णांकs *hपूर्णांकs)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (hपूर्णांकs->admin_completion_tx_समयout)
		adapter->ena_dev->admin_queue.completion_समयout =
			hपूर्णांकs->admin_completion_tx_समयout * 1000;

	अगर (hपूर्णांकs->mmio_पढ़ो_समयout)
		/* convert to usec */
		adapter->ena_dev->mmio_पढ़ो.reg_पढ़ो_to =
			hपूर्णांकs->mmio_पढ़ो_समयout * 1000;

	अगर (hपूर्णांकs->missed_tx_completion_count_threshold_to_reset)
		adapter->missing_tx_completion_threshold =
			hपूर्णांकs->missed_tx_completion_count_threshold_to_reset;

	अगर (hपूर्णांकs->missing_tx_completion_समयout) अणु
		अगर (hपूर्णांकs->missing_tx_completion_समयout == ENA_HW_HINTS_NO_TIMEOUT)
			adapter->missing_tx_completion_to = ENA_HW_HINTS_NO_TIMEOUT;
		अन्यथा
			adapter->missing_tx_completion_to =
				msecs_to_jअगरfies(hपूर्णांकs->missing_tx_completion_समयout);
	पूर्ण

	अगर (hपूर्णांकs->netdev_wd_समयout)
		netdev->watchकरोg_समयo = msecs_to_jअगरfies(hपूर्णांकs->netdev_wd_समयout);

	अगर (hपूर्णांकs->driver_watchकरोg_समयout) अणु
		अगर (hपूर्णांकs->driver_watchकरोg_समयout == ENA_HW_HINTS_NO_TIMEOUT)
			adapter->keep_alive_समयout = ENA_HW_HINTS_NO_TIMEOUT;
		अन्यथा
			adapter->keep_alive_समयout =
				msecs_to_jअगरfies(hपूर्णांकs->driver_watchकरोg_समयout);
	पूर्ण
पूर्ण

अटल व्योम ena_update_host_info(काष्ठा ena_admin_host_info *host_info,
				 काष्ठा net_device *netdev)
अणु
	host_info->supported_network_features[0] =
		netdev->features & GENMASK_ULL(31, 0);
	host_info->supported_network_features[1] =
		(netdev->features & GENMASK_ULL(63, 32)) >> 32;
पूर्ण

अटल व्योम ena_समयr_service(काष्ठा समयr_list *t)
अणु
	काष्ठा ena_adapter *adapter = from_समयr(adapter, t, समयr_service);
	u8 *debug_area = adapter->ena_dev->host_attr.debug_area_virt_addr;
	काष्ठा ena_admin_host_info *host_info =
		adapter->ena_dev->host_attr.host_info;

	check_क्रम_missing_keep_alive(adapter);

	check_क्रम_admin_com_state(adapter);

	check_क्रम_missing_completions(adapter);

	check_क्रम_empty_rx_ring(adapter);

	अगर (debug_area)
		ena_dump_stats_to_buf(adapter, debug_area);

	अगर (host_info)
		ena_update_host_info(host_info, adapter->netdev);

	अगर (unlikely(test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Trigger reset is on\n");
		ena_dump_stats_to_dmesg(adapter);
		queue_work(ena_wq, &adapter->reset_task);
		वापस;
	पूर्ण

	/* Reset the समयr */
	mod_समयr(&adapter->समयr_service, round_jअगरfies(jअगरfies + HZ));
पूर्ण

अटल u32 ena_calc_max_io_queue_num(काष्ठा pci_dev *pdev,
				     काष्ठा ena_com_dev *ena_dev,
				     काष्ठा ena_com_dev_get_features_ctx *get_feat_ctx)
अणु
	u32 io_tx_sq_num, io_tx_cq_num, io_rx_num, max_num_io_queues;

	अगर (ena_dev->supported_features & BIT(ENA_ADMIN_MAX_QUEUES_EXT)) अणु
		काष्ठा ena_admin_queue_ext_feature_fields *max_queue_ext =
			&get_feat_ctx->max_queue_ext.max_queue_ext;
		io_rx_num = min_t(u32, max_queue_ext->max_rx_sq_num,
				  max_queue_ext->max_rx_cq_num);

		io_tx_sq_num = max_queue_ext->max_tx_sq_num;
		io_tx_cq_num = max_queue_ext->max_tx_cq_num;
	पूर्ण अन्यथा अणु
		काष्ठा ena_admin_queue_feature_desc *max_queues =
			&get_feat_ctx->max_queues;
		io_tx_sq_num = max_queues->max_sq_num;
		io_tx_cq_num = max_queues->max_cq_num;
		io_rx_num = min_t(u32, io_tx_sq_num, io_tx_cq_num);
	पूर्ण

	/* In हाल of LLQ use the llq fields क्रम the tx SQ/CQ */
	अगर (ena_dev->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
		io_tx_sq_num = get_feat_ctx->llq.max_llq_num;

	max_num_io_queues = min_t(u32, num_online_cpus(), ENA_MAX_NUM_IO_QUEUES);
	max_num_io_queues = min_t(u32, max_num_io_queues, io_rx_num);
	max_num_io_queues = min_t(u32, max_num_io_queues, io_tx_sq_num);
	max_num_io_queues = min_t(u32, max_num_io_queues, io_tx_cq_num);
	/* 1 IRQ क्रम mgmnt and 1 IRQs क्रम each IO direction */
	max_num_io_queues = min_t(u32, max_num_io_queues, pci_msix_vec_count(pdev) - 1);
	अगर (unlikely(!max_num_io_queues)) अणु
		dev_err(&pdev->dev, "The device doesn't have io queues\n");
		वापस -EFAULT;
	पूर्ण

	वापस max_num_io_queues;
पूर्ण

अटल व्योम ena_set_dev_offloads(काष्ठा ena_com_dev_get_features_ctx *feat,
				 काष्ठा net_device *netdev)
अणु
	netdev_features_t dev_features = 0;

	/* Set offload features */
	अगर (feat->offload.tx &
		ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV4_CSUM_PART_MASK)
		dev_features |= NETIF_F_IP_CSUM;

	अगर (feat->offload.tx &
		ENA_ADMIN_FEATURE_OFFLOAD_DESC_TX_L4_IPV6_CSUM_PART_MASK)
		dev_features |= NETIF_F_IPV6_CSUM;

	अगर (feat->offload.tx & ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV4_MASK)
		dev_features |= NETIF_F_TSO;

	अगर (feat->offload.tx & ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_IPV6_MASK)
		dev_features |= NETIF_F_TSO6;

	अगर (feat->offload.tx & ENA_ADMIN_FEATURE_OFFLOAD_DESC_TSO_ECN_MASK)
		dev_features |= NETIF_F_TSO_ECN;

	अगर (feat->offload.rx_supported &
		ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV4_CSUM_MASK)
		dev_features |= NETIF_F_RXCSUM;

	अगर (feat->offload.rx_supported &
		ENA_ADMIN_FEATURE_OFFLOAD_DESC_RX_L4_IPV6_CSUM_MASK)
		dev_features |= NETIF_F_RXCSUM;

	netdev->features =
		dev_features |
		NETIF_F_SG |
		NETIF_F_RXHASH |
		NETIF_F_HIGHDMA;

	netdev->hw_features |= netdev->features;
	netdev->vlan_features |= netdev->features;
पूर्ण

अटल व्योम ena_set_conf_feat_params(काष्ठा ena_adapter *adapter,
				     काष्ठा ena_com_dev_get_features_ctx *feat)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	/* Copy mac address */
	अगर (!is_valid_ether_addr(feat->dev_attr.mac_addr)) अणु
		eth_hw_addr_अक्रमom(netdev);
		ether_addr_copy(adapter->mac_addr, netdev->dev_addr);
	पूर्ण अन्यथा अणु
		ether_addr_copy(adapter->mac_addr, feat->dev_attr.mac_addr);
		ether_addr_copy(netdev->dev_addr, adapter->mac_addr);
	पूर्ण

	/* Set offload features */
	ena_set_dev_offloads(feat, netdev);

	adapter->max_mtu = feat->dev_attr.max_mtu;
	netdev->max_mtu = adapter->max_mtu;
	netdev->min_mtu = ENA_MIN_MTU;
पूर्ण

अटल पूर्णांक ena_rss_init_शेष(काष्ठा ena_adapter *adapter)
अणु
	काष्ठा ena_com_dev *ena_dev = adapter->ena_dev;
	काष्ठा device *dev = &adapter->pdev->dev;
	पूर्णांक rc, i;
	u32 val;

	rc = ena_com_rss_init(ena_dev, ENA_RX_RSS_TABLE_LOG_SIZE);
	अगर (unlikely(rc)) अणु
		dev_err(dev, "Cannot init indirect table\n");
		जाओ err_rss_init;
	पूर्ण

	क्रम (i = 0; i < ENA_RX_RSS_TABLE_SIZE; i++) अणु
		val = ethtool_rxfh_indir_शेष(i, adapter->num_io_queues);
		rc = ena_com_indirect_table_fill_entry(ena_dev, i,
						       ENA_IO_RXQ_IDX(val));
		अगर (unlikely(rc && (rc != -EOPNOTSUPP))) अणु
			dev_err(dev, "Cannot fill indirect table\n");
			जाओ err_fill_indir;
		पूर्ण
	पूर्ण

	rc = ena_com_fill_hash_function(ena_dev, ENA_ADMIN_TOEPLITZ, शून्य,
					ENA_HASH_KEY_SIZE, 0xFFFFFFFF);
	अगर (unlikely(rc && (rc != -EOPNOTSUPP))) अणु
		dev_err(dev, "Cannot fill hash function\n");
		जाओ err_fill_indir;
	पूर्ण

	rc = ena_com_set_शेष_hash_ctrl(ena_dev);
	अगर (unlikely(rc && (rc != -EOPNOTSUPP))) अणु
		dev_err(dev, "Cannot fill hash control\n");
		जाओ err_fill_indir;
	पूर्ण

	वापस 0;

err_fill_indir:
	ena_com_rss_destroy(ena_dev);
err_rss_init:

	वापस rc;
पूर्ण

अटल व्योम ena_release_bars(काष्ठा ena_com_dev *ena_dev, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक release_bars = pci_select_bars(pdev, IORESOURCE_MEM) & ENA_BAR_MASK;

	pci_release_selected_regions(pdev, release_bars);
पूर्ण


अटल पूर्णांक ena_calc_io_queue_size(काष्ठा ena_calc_queue_size_ctx *ctx)
अणु
	काष्ठा ena_admin_feature_llq_desc *llq = &ctx->get_feat_ctx->llq;
	काष्ठा ena_com_dev *ena_dev = ctx->ena_dev;
	u32 tx_queue_size = ENA_DEFAULT_RING_SIZE;
	u32 rx_queue_size = ENA_DEFAULT_RING_SIZE;
	u32 max_tx_queue_size;
	u32 max_rx_queue_size;

	अगर (ena_dev->supported_features & BIT(ENA_ADMIN_MAX_QUEUES_EXT)) अणु
		काष्ठा ena_admin_queue_ext_feature_fields *max_queue_ext =
			&ctx->get_feat_ctx->max_queue_ext.max_queue_ext;
		max_rx_queue_size = min_t(u32, max_queue_ext->max_rx_cq_depth,
					  max_queue_ext->max_rx_sq_depth);
		max_tx_queue_size = max_queue_ext->max_tx_cq_depth;

		अगर (ena_dev->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
			max_tx_queue_size = min_t(u32, max_tx_queue_size,
						  llq->max_llq_depth);
		अन्यथा
			max_tx_queue_size = min_t(u32, max_tx_queue_size,
						  max_queue_ext->max_tx_sq_depth);

		ctx->max_tx_sgl_size = min_t(u16, ENA_PKT_MAX_BUFS,
					     max_queue_ext->max_per_packet_tx_descs);
		ctx->max_rx_sgl_size = min_t(u16, ENA_PKT_MAX_BUFS,
					     max_queue_ext->max_per_packet_rx_descs);
	पूर्ण अन्यथा अणु
		काष्ठा ena_admin_queue_feature_desc *max_queues =
			&ctx->get_feat_ctx->max_queues;
		max_rx_queue_size = min_t(u32, max_queues->max_cq_depth,
					  max_queues->max_sq_depth);
		max_tx_queue_size = max_queues->max_cq_depth;

		अगर (ena_dev->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
			max_tx_queue_size = min_t(u32, max_tx_queue_size,
						  llq->max_llq_depth);
		अन्यथा
			max_tx_queue_size = min_t(u32, max_tx_queue_size,
						  max_queues->max_sq_depth);

		ctx->max_tx_sgl_size = min_t(u16, ENA_PKT_MAX_BUFS,
					     max_queues->max_packet_tx_descs);
		ctx->max_rx_sgl_size = min_t(u16, ENA_PKT_MAX_BUFS,
					     max_queues->max_packet_rx_descs);
	पूर्ण

	max_tx_queue_size = roundकरोwn_घात_of_two(max_tx_queue_size);
	max_rx_queue_size = roundकरोwn_घात_of_two(max_rx_queue_size);

	tx_queue_size = clamp_val(tx_queue_size, ENA_MIN_RING_SIZE,
				  max_tx_queue_size);
	rx_queue_size = clamp_val(rx_queue_size, ENA_MIN_RING_SIZE,
				  max_rx_queue_size);

	tx_queue_size = roundकरोwn_घात_of_two(tx_queue_size);
	rx_queue_size = roundकरोwn_घात_of_two(rx_queue_size);

	ctx->max_tx_queue_size = max_tx_queue_size;
	ctx->max_rx_queue_size = max_rx_queue_size;
	ctx->tx_queue_size = tx_queue_size;
	ctx->rx_queue_size = rx_queue_size;

	वापस 0;
पूर्ण

/* ena_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in ena_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * ena_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 */
अटल पूर्णांक ena_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा ena_calc_queue_size_ctx calc_queue_ctx = अणुपूर्ण;
	काष्ठा ena_com_dev_get_features_ctx get_feat_ctx;
	काष्ठा ena_com_dev *ena_dev = शून्य;
	काष्ठा ena_adapter *adapter;
	काष्ठा net_device *netdev;
	अटल पूर्णांक adapters_found;
	u32 max_num_io_queues;
	bool wd_state;
	पूर्णांक bars, rc;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	rc = pci_enable_device_mem(pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "pci_enable_device_mem() failed!\n");
		वापस rc;
	पूर्ण

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(ENA_MAX_PHYS_ADDR_SIZE_BITS));
	अगर (rc) अणु
		dev_err(&pdev->dev, "dma_set_mask_and_coherent failed %d\n", rc);
		जाओ err_disable_device;
	पूर्ण

	pci_set_master(pdev);

	ena_dev = vzalloc(माप(*ena_dev));
	अगर (!ena_dev) अणु
		rc = -ENOMEM;
		जाओ err_disable_device;
	पूर्ण

	bars = pci_select_bars(pdev, IORESOURCE_MEM) & ENA_BAR_MASK;
	rc = pci_request_selected_regions(pdev, bars, DRV_MODULE_NAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "pci_request_selected_regions failed %d\n",
			rc);
		जाओ err_मुक्त_ena_dev;
	पूर्ण

	ena_dev->reg_bar = devm_ioremap(&pdev->dev,
					pci_resource_start(pdev, ENA_REG_BAR),
					pci_resource_len(pdev, ENA_REG_BAR));
	अगर (!ena_dev->reg_bar) अणु
		dev_err(&pdev->dev, "Failed to remap regs bar\n");
		rc = -EFAULT;
		जाओ err_मुक्त_region;
	पूर्ण

	ena_dev->ena_min_poll_delay_us = ENA_ADMIN_POLL_DELAY_US;

	ena_dev->dmadev = &pdev->dev;

	netdev = alloc_etherdev_mq(माप(काष्ठा ena_adapter), ENA_MAX_RINGS);
	अगर (!netdev) अणु
		dev_err(&pdev->dev, "alloc_etherdev_mq failed\n");
		rc = -ENOMEM;
		जाओ err_मुक्त_region;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);
	adapter = netdev_priv(netdev);
	adapter->ena_dev = ena_dev;
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	ena_dev->net_device = netdev;

	pci_set_drvdata(pdev, adapter);

	rc = ena_device_init(ena_dev, pdev, &get_feat_ctx, &wd_state);
	अगर (rc) अणु
		dev_err(&pdev->dev, "ENA device init failed\n");
		अगर (rc == -ETIME)
			rc = -EPROBE_DEFER;
		जाओ err_netdev_destroy;
	पूर्ण

	rc = ena_map_llq_mem_bar(pdev, ena_dev, bars);
	अगर (rc) अणु
		dev_err(&pdev->dev, "ENA llq bar mapping failed\n");
		जाओ err_device_destroy;
	पूर्ण

	calc_queue_ctx.ena_dev = ena_dev;
	calc_queue_ctx.get_feat_ctx = &get_feat_ctx;
	calc_queue_ctx.pdev = pdev;

	/* Initial TX and RX पूर्णांकerrupt delay. Assumes 1 usec granularity.
	 * Updated during device initialization with the real granularity
	 */
	ena_dev->पूर्णांकr_moder_tx_पूर्णांकerval = ENA_INTR_INITIAL_TX_INTERVAL_USECS;
	ena_dev->पूर्णांकr_moder_rx_पूर्णांकerval = ENA_INTR_INITIAL_RX_INTERVAL_USECS;
	ena_dev->पूर्णांकr_delay_resolution = ENA_DEFAULT_INTR_DELAY_RESOLUTION;
	max_num_io_queues = ena_calc_max_io_queue_num(pdev, ena_dev, &get_feat_ctx);
	rc = ena_calc_io_queue_size(&calc_queue_ctx);
	अगर (rc || !max_num_io_queues) अणु
		rc = -EFAULT;
		जाओ err_device_destroy;
	पूर्ण

	ena_set_conf_feat_params(adapter, &get_feat_ctx);

	adapter->reset_reason = ENA_REGS_RESET_NORMAL;

	adapter->requested_tx_ring_size = calc_queue_ctx.tx_queue_size;
	adapter->requested_rx_ring_size = calc_queue_ctx.rx_queue_size;
	adapter->max_tx_ring_size = calc_queue_ctx.max_tx_queue_size;
	adapter->max_rx_ring_size = calc_queue_ctx.max_rx_queue_size;
	adapter->max_tx_sgl_size = calc_queue_ctx.max_tx_sgl_size;
	adapter->max_rx_sgl_size = calc_queue_ctx.max_rx_sgl_size;

	adapter->num_io_queues = max_num_io_queues;
	adapter->max_num_io_queues = max_num_io_queues;
	adapter->last_monitored_tx_qid = 0;

	adapter->xdp_first_ring = 0;
	adapter->xdp_num_queues = 0;

	adapter->rx_copyअवरोध = ENA_DEFAULT_RX_COPYBREAK;
	अगर (ena_dev->tx_mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_DEV)
		adapter->disable_meta_caching =
			!!(get_feat_ctx.llq.accel_mode.u.get.supported_flags &
			   BIT(ENA_ADMIN_DISABLE_META_CACHING));

	adapter->wd_state = wd_state;

	snम_लिखो(adapter->name, ENA_NAME_MAX_LEN, "ena_%d", adapters_found);

	rc = ena_com_init_पूर्णांकerrupt_moderation(adapter->ena_dev);
	अगर (rc) अणु
		dev_err(&pdev->dev,
			"Failed to query interrupt moderation feature\n");
		जाओ err_device_destroy;
	पूर्ण
	ena_init_io_rings(adapter,
			  0,
			  adapter->xdp_num_queues +
			  adapter->num_io_queues);

	netdev->netdev_ops = &ena_netdev_ops;
	netdev->watchकरोg_समयo = TX_TIMEOUT;
	ena_set_ethtool_ops(netdev);

	netdev->priv_flags |= IFF_UNICAST_FLT;

	u64_stats_init(&adapter->syncp);

	rc = ena_enable_msix_and_set_admin_पूर्णांकerrupts(adapter);
	अगर (rc) अणु
		dev_err(&pdev->dev,
			"Failed to enable and set the admin interrupts\n");
		जाओ err_worker_destroy;
	पूर्ण
	rc = ena_rss_init_शेष(adapter);
	अगर (rc && (rc != -EOPNOTSUPP)) अणु
		dev_err(&pdev->dev, "Cannot init RSS rc: %d\n", rc);
		जाओ err_मुक्त_msix;
	पूर्ण

	ena_config_debug_area(adapter);

	अगर (!ena_update_hw_stats(adapter))
		adapter->eni_stats_supported = true;
	अन्यथा
		adapter->eni_stats_supported = false;

	स_नकल(adapter->netdev->perm_addr, adapter->mac_addr, netdev->addr_len);

	netअगर_carrier_off(netdev);

	rc = रेजिस्टर_netdev(netdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot register net device\n");
		जाओ err_rss;
	पूर्ण

	INIT_WORK(&adapter->reset_task, ena_fw_reset_device);

	adapter->last_keep_alive_jअगरfies = jअगरfies;
	adapter->keep_alive_समयout = ENA_DEVICE_KALIVE_TIMEOUT;
	adapter->missing_tx_completion_to = TX_TIMEOUT;
	adapter->missing_tx_completion_threshold = MAX_NUM_OF_TIMEOUTED_PACKETS;

	ena_update_hपूर्णांकs(adapter, &get_feat_ctx.hw_hपूर्णांकs);

	समयr_setup(&adapter->समयr_service, ena_समयr_service, 0);
	mod_समयr(&adapter->समयr_service, round_jअगरfies(jअगरfies + HZ));

	dev_info(&pdev->dev,
		 "%s found at mem %lx, mac addr %pM\n",
		 DEVICE_NAME, (दीर्घ)pci_resource_start(pdev, 0),
		 netdev->dev_addr);

	set_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags);

	adapters_found++;

	वापस 0;

err_rss:
	ena_com_delete_debug_area(ena_dev);
	ena_com_rss_destroy(ena_dev);
err_मुक्त_msix:
	ena_com_dev_reset(ena_dev, ENA_REGS_RESET_INIT_ERR);
	/* stop submitting admin commands on a device that was reset */
	ena_com_set_admin_running_state(ena_dev, false);
	ena_मुक्त_mgmnt_irq(adapter);
	ena_disable_msix(adapter);
err_worker_destroy:
	del_समयr(&adapter->समयr_service);
err_device_destroy:
	ena_com_delete_host_info(ena_dev);
	ena_com_admin_destroy(ena_dev);
err_netdev_destroy:
	मुक्त_netdev(netdev);
err_मुक्त_region:
	ena_release_bars(ena_dev, pdev);
err_मुक्त_ena_dev:
	vमुक्त(ena_dev);
err_disable_device:
	pci_disable_device(pdev);
	वापस rc;
पूर्ण

/*****************************************************************************/

/* __ena_shutoff - Helper used in both PCI हटाओ/shutकरोwn routines
 * @pdev: PCI device inक्रमmation काष्ठा
 * @shutकरोwn: Is it a shutकरोwn operation? If false, means it is a removal
 *
 * __ena_shutoff is a helper routine that करोes the real work on shutकरोwn and
 * removal paths; the dअगरference between those paths is with regards to whether
 * dettach or unरेजिस्टर the netdevice.
 */
अटल व्योम __ena_shutoff(काष्ठा pci_dev *pdev, bool shutकरोwn)
अणु
	काष्ठा ena_adapter *adapter = pci_get_drvdata(pdev);
	काष्ठा ena_com_dev *ena_dev;
	काष्ठा net_device *netdev;

	ena_dev = adapter->ena_dev;
	netdev = adapter->netdev;

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर ((adapter->msix_vecs >= 1) && (netdev->rx_cpu_rmap)) अणु
		मुक्त_irq_cpu_rmap(netdev->rx_cpu_rmap);
		netdev->rx_cpu_rmap = शून्य;
	पूर्ण
#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

	/* Make sure समयr and reset routine won't be called after
	 * मुक्तing device resources.
	 */
	del_समयr_sync(&adapter->समयr_service);
	cancel_work_sync(&adapter->reset_task);

	rtnl_lock(); /* lock released inside the below अगर-अन्यथा block */
	adapter->reset_reason = ENA_REGS_RESET_SHUTDOWN;
	ena_destroy_device(adapter, true);
	अगर (shutकरोwn) अणु
		netअगर_device_detach(netdev);
		dev_बंद(netdev);
		rtnl_unlock();
	पूर्ण अन्यथा अणु
		rtnl_unlock();
		unरेजिस्टर_netdev(netdev);
		मुक्त_netdev(netdev);
	पूर्ण

	ena_com_rss_destroy(ena_dev);

	ena_com_delete_debug_area(ena_dev);

	ena_com_delete_host_info(ena_dev);

	ena_release_bars(ena_dev, pdev);

	pci_disable_device(pdev);

	vमुक्त(ena_dev);
पूर्ण

/* ena_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * ena_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.
 */

अटल व्योम ena_हटाओ(काष्ठा pci_dev *pdev)
अणु
	__ena_shutoff(pdev, false);
पूर्ण

/* ena_shutकरोwn - Device Shutकरोwn Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * ena_shutकरोwn is called by the PCI subप्रणाली to alert the driver that
 * a shutकरोwn/reboot (or kexec) is happening and device must be disabled.
 */

अटल व्योम ena_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	__ena_shutoff(pdev, true);
पूर्ण

/* ena_suspend - PM suspend callback
 * @dev_d: Device inक्रमmation काष्ठा
 */
अटल पूर्णांक __maybe_unused ena_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा ena_adapter *adapter = pci_get_drvdata(pdev);

	ena_increase_stat(&adapter->dev_stats.suspend, 1, &adapter->syncp);

	rtnl_lock();
	अगर (unlikely(test_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))) अणु
		dev_err(&pdev->dev,
			"Ignoring device reset request as the device is being suspended\n");
		clear_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
	पूर्ण
	ena_destroy_device(adapter, true);
	rtnl_unlock();
	वापस 0;
पूर्ण

/* ena_resume - PM resume callback
 * @dev_d: Device inक्रमmation काष्ठा
 */
अटल पूर्णांक __maybe_unused ena_resume(काष्ठा device *dev_d)
अणु
	काष्ठा ena_adapter *adapter = dev_get_drvdata(dev_d);
	पूर्णांक rc;

	ena_increase_stat(&adapter->dev_stats.resume, 1, &adapter->syncp);

	rtnl_lock();
	rc = ena_restore_device(adapter);
	rtnl_unlock();
	वापस rc;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ena_pm_ops, ena_suspend, ena_resume);

अटल काष्ठा pci_driver ena_pci_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= ena_pci_tbl,
	.probe		= ena_probe,
	.हटाओ		= ena_हटाओ,
	.shutकरोwn	= ena_shutकरोwn,
	.driver.pm	= &ena_pm_ops,
	.sriov_configure = pci_sriov_configure_simple,
पूर्ण;

अटल पूर्णांक __init ena_init(व्योम)
अणु
	ena_wq = create_singlethपढ़ो_workqueue(DRV_MODULE_NAME);
	अगर (!ena_wq) अणु
		pr_err("Failed to create workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	वापस pci_रेजिस्टर_driver(&ena_pci_driver);
पूर्ण

अटल व्योम __निकास ena_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ena_pci_driver);

	अगर (ena_wq) अणु
		destroy_workqueue(ena_wq);
		ena_wq = शून्य;
	पूर्ण
पूर्ण

/******************************************************************************
 ******************************** AENQ Handlers *******************************
 *****************************************************************************/
/* ena_update_on_link_change:
 * Notअगरy the network पूर्णांकerface about the change in link status
 */
अटल व्योम ena_update_on_link_change(व्योम *adapter_data,
				      काष्ठा ena_admin_aenq_entry *aenq_e)
अणु
	काष्ठा ena_adapter *adapter = (काष्ठा ena_adapter *)adapter_data;
	काष्ठा ena_admin_aenq_link_change_desc *aenq_desc =
		(काष्ठा ena_admin_aenq_link_change_desc *)aenq_e;
	पूर्णांक status = aenq_desc->flags &
		ENA_ADMIN_AENQ_LINK_CHANGE_DESC_LINK_STATUS_MASK;

	अगर (status) अणु
		netअगर_dbg(adapter, अगरup, adapter->netdev, "%s\n", __func__);
		set_bit(ENA_FLAG_LINK_UP, &adapter->flags);
		अगर (!test_bit(ENA_FLAG_ONGOING_RESET, &adapter->flags))
			netअगर_carrier_on(adapter->netdev);
	पूर्ण अन्यथा अणु
		clear_bit(ENA_FLAG_LINK_UP, &adapter->flags);
		netअगर_carrier_off(adapter->netdev);
	पूर्ण
पूर्ण

अटल व्योम ena_keep_alive_wd(व्योम *adapter_data,
			      काष्ठा ena_admin_aenq_entry *aenq_e)
अणु
	काष्ठा ena_adapter *adapter = (काष्ठा ena_adapter *)adapter_data;
	काष्ठा ena_admin_aenq_keep_alive_desc *desc;
	u64 rx_drops;
	u64 tx_drops;

	desc = (काष्ठा ena_admin_aenq_keep_alive_desc *)aenq_e;
	adapter->last_keep_alive_jअगरfies = jअगरfies;

	rx_drops = ((u64)desc->rx_drops_high << 32) | desc->rx_drops_low;
	tx_drops = ((u64)desc->tx_drops_high << 32) | desc->tx_drops_low;

	u64_stats_update_begin(&adapter->syncp);
	/* These stats are accumulated by the device, so the counters indicate
	 * all drops since last reset.
	 */
	adapter->dev_stats.rx_drops = rx_drops;
	adapter->dev_stats.tx_drops = tx_drops;
	u64_stats_update_end(&adapter->syncp);
पूर्ण

अटल व्योम ena_notअगरication(व्योम *adapter_data,
			     काष्ठा ena_admin_aenq_entry *aenq_e)
अणु
	काष्ठा ena_adapter *adapter = (काष्ठा ena_adapter *)adapter_data;
	काष्ठा ena_admin_ena_hw_hपूर्णांकs *hपूर्णांकs;

	WARN(aenq_e->aenq_common_desc.group != ENA_ADMIN_NOTIFICATION,
	     "Invalid group(%x) expected %x\n",
	     aenq_e->aenq_common_desc.group,
	     ENA_ADMIN_NOTIFICATION);

	चयन (aenq_e->aenq_common_desc.syndrome) अणु
	हाल ENA_ADMIN_UPDATE_HINTS:
		hपूर्णांकs = (काष्ठा ena_admin_ena_hw_hपूर्णांकs *)
			(&aenq_e->अंतरभूत_data_w4);
		ena_update_hपूर्णांकs(adapter, hपूर्णांकs);
		अवरोध;
	शेष:
		netअगर_err(adapter, drv, adapter->netdev,
			  "Invalid aenq notification link state %d\n",
			  aenq_e->aenq_common_desc.syndrome);
	पूर्ण
पूर्ण

/* This handler will called क्रम unknown event group or unimplemented handlers*/
अटल व्योम unimplemented_aenq_handler(व्योम *data,
				       काष्ठा ena_admin_aenq_entry *aenq_e)
अणु
	काष्ठा ena_adapter *adapter = (काष्ठा ena_adapter *)data;

	netअगर_err(adapter, drv, adapter->netdev,
		  "Unknown event was received or event with unimplemented handler\n");
पूर्ण

अटल काष्ठा ena_aenq_handlers aenq_handlers = अणु
	.handlers = अणु
		[ENA_ADMIN_LINK_CHANGE] = ena_update_on_link_change,
		[ENA_ADMIN_NOTIFICATION] = ena_notअगरication,
		[ENA_ADMIN_KEEP_ALIVE] = ena_keep_alive_wd,
	पूर्ण,
	.unimplemented_handler = unimplemented_aenq_handler
पूर्ण;

module_init(ena_init);
module_निकास(ena_cleanup);
