<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**************************************************************************/
/*                                                                        */
/*  IBM System i and System p Virtual NIC Device Driver                   */
/*  Copyright (C) 2014 IBM Corp.                                          */
/*  Santiago Leon (santi_leon@yahoo.com)                                  */
/*  Thomas Falcon (tlfalcon@linux.vnet.ibm.com)                           */
/*  John Allen (jallen@linux.vnet.ibm.com)                                */
/*                                                                        */
/*                                                                        */
/* This module contains the implementation of a भव ethernet device   */
/* क्रम use with IBM i/p Series LPAR Linux. It utilizes the logical LAN    */
/* option of the RS/6000 Platक्रमm Architecture to पूर्णांकerface with भव  */
/* ethernet NICs that are presented to the partition by the hypervisor.   */
/*									   */
/* Messages are passed between the VNIC driver and the VNIC server using  */
/* Command/Response Queues (CRQs) and sub CRQs (sCRQs). CRQs are used to  */
/* issue and receive commands that initiate communication with the server */
/* on driver initialization. Sub CRQs (sCRQs) are similar to CRQs, but    */
/* are used by the driver to notअगरy the server that a packet is           */
/* पढ़ोy क्रम transmission or that a buffer has been added to receive a    */
/* packet. Subsequently, sCRQs are used by the server to notअगरy the       */
/* driver that a packet transmission has been completed or that a packet  */
/* has been received and placed in a रुकोing buffer.                      */
/*                                                                        */
/* In lieu of a more conventional "on-the-fly" DMA mapping strategy in    */
/* which skbs are DMA mapped and immediately unmapped when the transmit   */
/* or receive has been completed, the VNIC driver is required to use      */
/* "long term mapping". This entails that large, continuous DMA mapped    */
/* buffers are allocated on driver initialization and these buffers are   */
/* then continuously reused to pass skbs to and from the VNIC server.     */
/*                                                                        */
/**************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/completion.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/irq.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <net/net_namespace.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/iommu.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/firmware.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/utsname.h>

#समावेश "ibmvnic.h"

अटल स्थिर अक्षर ibmvnic_driver_name[] = "ibmvnic";
अटल स्थिर अक्षर ibmvnic_driver_string[] = "IBM System i/p Virtual NIC Driver";

MODULE_AUTHOR("Santiago Leon");
MODULE_DESCRIPTION("IBM System i/p Virtual NIC Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(IBMVNIC_DRIVER_VERSION);

अटल पूर्णांक ibmvnic_version = IBMVNIC_INITIAL_VERSION;
अटल व्योम release_sub_crqs(काष्ठा ibmvnic_adapter *, bool);
अटल पूर्णांक ibmvnic_reset_crq(काष्ठा ibmvnic_adapter *);
अटल पूर्णांक ibmvnic_send_crq_init(काष्ठा ibmvnic_adapter *);
अटल पूर्णांक ibmvnic_reenable_crq_queue(काष्ठा ibmvnic_adapter *);
अटल पूर्णांक ibmvnic_send_crq(काष्ठा ibmvnic_adapter *, जोड़ ibmvnic_crq *);
अटल पूर्णांक send_subcrq_indirect(काष्ठा ibmvnic_adapter *, u64, u64, u64);
अटल irqवापस_t ibmvnic_पूर्णांकerrupt_rx(पूर्णांक irq, व्योम *instance);
अटल पूर्णांक enable_scrq_irq(काष्ठा ibmvnic_adapter *,
			   काष्ठा ibmvnic_sub_crq_queue *);
अटल पूर्णांक disable_scrq_irq(काष्ठा ibmvnic_adapter *,
			    काष्ठा ibmvnic_sub_crq_queue *);
अटल पूर्णांक pending_scrq(काष्ठा ibmvnic_adapter *,
			काष्ठा ibmvnic_sub_crq_queue *);
अटल जोड़ sub_crq *ibmvnic_next_scrq(काष्ठा ibmvnic_adapter *,
					काष्ठा ibmvnic_sub_crq_queue *);
अटल पूर्णांक ibmvnic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक data);
अटल व्योम send_query_map(काष्ठा ibmvnic_adapter *adapter);
अटल पूर्णांक send_request_map(काष्ठा ibmvnic_adapter *, dma_addr_t, __be32, u8);
अटल पूर्णांक send_request_unmap(काष्ठा ibmvnic_adapter *, u8);
अटल पूर्णांक send_login(काष्ठा ibmvnic_adapter *adapter);
अटल व्योम send_query_cap(काष्ठा ibmvnic_adapter *adapter);
अटल पूर्णांक init_sub_crqs(काष्ठा ibmvnic_adapter *);
अटल पूर्णांक init_sub_crq_irqs(काष्ठा ibmvnic_adapter *adapter);
अटल पूर्णांक ibmvnic_reset_init(काष्ठा ibmvnic_adapter *, bool reset);
अटल व्योम release_crq_queue(काष्ठा ibmvnic_adapter *);
अटल पूर्णांक __ibmvnic_set_mac(काष्ठा net_device *, u8 *);
अटल पूर्णांक init_crq_queue(काष्ठा ibmvnic_adapter *adapter);
अटल पूर्णांक send_query_phys_parms(काष्ठा ibmvnic_adapter *adapter);

काष्ठा ibmvnic_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक offset;
पूर्ण;

#घोषणा IBMVNIC_STAT_OFF(stat) (दुरत्व(काष्ठा ibmvnic_adapter, stats) + \
			     दुरत्व(काष्ठा ibmvnic_statistics, stat))
#घोषणा IBMVNIC_GET_STAT(a, off) (*((u64 *)(((अचिन्हित दीर्घ)(a)) + (off))))

अटल स्थिर काष्ठा ibmvnic_stat ibmvnic_stats[] = अणु
	अणु"rx_packets", IBMVNIC_STAT_OFF(rx_packets)पूर्ण,
	अणु"rx_bytes", IBMVNIC_STAT_OFF(rx_bytes)पूर्ण,
	अणु"tx_packets", IBMVNIC_STAT_OFF(tx_packets)पूर्ण,
	अणु"tx_bytes", IBMVNIC_STAT_OFF(tx_bytes)पूर्ण,
	अणु"ucast_tx_packets", IBMVNIC_STAT_OFF(ucast_tx_packets)पूर्ण,
	अणु"ucast_rx_packets", IBMVNIC_STAT_OFF(ucast_rx_packets)पूर्ण,
	अणु"mcast_tx_packets", IBMVNIC_STAT_OFF(mcast_tx_packets)पूर्ण,
	अणु"mcast_rx_packets", IBMVNIC_STAT_OFF(mcast_rx_packets)पूर्ण,
	अणु"bcast_tx_packets", IBMVNIC_STAT_OFF(bcast_tx_packets)पूर्ण,
	अणु"bcast_rx_packets", IBMVNIC_STAT_OFF(bcast_rx_packets)पूर्ण,
	अणु"align_errors", IBMVNIC_STAT_OFF(align_errors)पूर्ण,
	अणु"fcs_errors", IBMVNIC_STAT_OFF(fcs_errors)पूर्ण,
	अणु"single_collision_frames", IBMVNIC_STAT_OFF(single_collision_frames)पूर्ण,
	अणु"multi_collision_frames", IBMVNIC_STAT_OFF(multi_collision_frames)पूर्ण,
	अणु"sqe_test_errors", IBMVNIC_STAT_OFF(sqe_test_errors)पूर्ण,
	अणु"deferred_tx", IBMVNIC_STAT_OFF(deferred_tx)पूर्ण,
	अणु"late_collisions", IBMVNIC_STAT_OFF(late_collisions)पूर्ण,
	अणु"excess_collisions", IBMVNIC_STAT_OFF(excess_collisions)पूर्ण,
	अणु"internal_mac_tx_errors", IBMVNIC_STAT_OFF(पूर्णांकernal_mac_tx_errors)पूर्ण,
	अणु"carrier_sense", IBMVNIC_STAT_OFF(carrier_sense)पूर्ण,
	अणु"too_long_frames", IBMVNIC_STAT_OFF(too_दीर्घ_frames)पूर्ण,
	अणु"internal_mac_rx_errors", IBMVNIC_STAT_OFF(पूर्णांकernal_mac_rx_errors)पूर्ण,
पूर्ण;

अटल दीर्घ h_reg_sub_crq(अचिन्हित दीर्घ unit_address, अचिन्हित दीर्घ token,
			  अचिन्हित दीर्घ length, अचिन्हित दीर्घ *number,
			  अचिन्हित दीर्घ *irq)
अणु
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	दीर्घ rc;

	rc = plpar_hcall(H_REG_SUB_CRQ, retbuf, unit_address, token, length);
	*number = retbuf[0];
	*irq = retbuf[1];

	वापस rc;
पूर्ण

/**
 * ibmvnic_रुको_क्रम_completion - Check device state and रुको क्रम completion
 * @adapter: निजी device data
 * @comp_करोne: completion काष्ठाure to रुको क्रम
 * @समयout: समय to रुको in milliseconds
 *
 * Wait क्रम a completion संकेत or until the समयout limit is reached
 * जबतक checking that the device is still active.
 */
अटल पूर्णांक ibmvnic_रुको_क्रम_completion(काष्ठा ibmvnic_adapter *adapter,
				       काष्ठा completion *comp_करोne,
				       अचिन्हित दीर्घ समयout)
अणु
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ भाग_प्रकारimeout;
	u8 retry;

	netdev = adapter->netdev;
	retry = 5;
	भाग_प्रकारimeout = msecs_to_jअगरfies(समयout / retry);
	जबतक (true) अणु
		अगर (!adapter->crq.active) अणु
			netdev_err(netdev, "Device down!\n");
			वापस -ENODEV;
		पूर्ण
		अगर (!retry--)
			अवरोध;
		अगर (रुको_क्रम_completion_समयout(comp_करोne, भाग_प्रकारimeout))
			वापस 0;
	पूर्ण
	netdev_err(netdev, "Operation timed out.\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक alloc_दीर्घ_term_buff(काष्ठा ibmvnic_adapter *adapter,
				काष्ठा ibmvnic_दीर्घ_term_buff *ltb, पूर्णांक size)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	पूर्णांक rc;

	ltb->size = size;
	ltb->buff = dma_alloc_coherent(dev, ltb->size, &ltb->addr,
				       GFP_KERNEL);

	अगर (!ltb->buff) अणु
		dev_err(dev, "Couldn't alloc long term buffer\n");
		वापस -ENOMEM;
	पूर्ण
	ltb->map_id = adapter->map_id;
	adapter->map_id++;

	mutex_lock(&adapter->fw_lock);
	adapter->fw_करोne_rc = 0;
	reinit_completion(&adapter->fw_करोne);
	rc = send_request_map(adapter, ltb->addr,
			      ltb->size, ltb->map_id);
	अगर (rc) अणु
		dma_मुक्त_coherent(dev, ltb->size, ltb->buff, ltb->addr);
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण

	rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->fw_करोne, 10000);
	अगर (rc) अणु
		dev_err(dev,
			"Long term map request aborted or timed out,rc = %d\n",
			rc);
		dma_मुक्त_coherent(dev, ltb->size, ltb->buff, ltb->addr);
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण

	अगर (adapter->fw_करोne_rc) अणु
		dev_err(dev, "Couldn't map long term buffer,rc = %d\n",
			adapter->fw_करोne_rc);
		dma_मुक्त_coherent(dev, ltb->size, ltb->buff, ltb->addr);
		mutex_unlock(&adapter->fw_lock);
		वापस -1;
	पूर्ण
	mutex_unlock(&adapter->fw_lock);
	वापस 0;
पूर्ण

अटल व्योम मुक्त_दीर्घ_term_buff(काष्ठा ibmvnic_adapter *adapter,
				काष्ठा ibmvnic_दीर्घ_term_buff *ltb)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;

	अगर (!ltb->buff)
		वापस;

	/* VIOS स्वतःmatically unmaps the दीर्घ term buffer at remote
	 * end क्रम the following resets:
	 * FAILOVER, MOBILITY, TIMEOUT.
	 */
	अगर (adapter->reset_reason != VNIC_RESET_FAILOVER &&
	    adapter->reset_reason != VNIC_RESET_MOBILITY &&
	    adapter->reset_reason != VNIC_RESET_TIMEOUT)
		send_request_unmap(adapter, ltb->map_id);
	dma_मुक्त_coherent(dev, ltb->size, ltb->buff, ltb->addr);
पूर्ण

अटल पूर्णांक reset_दीर्घ_term_buff(काष्ठा ibmvnic_दीर्घ_term_buff *ltb)
अणु
	अगर (!ltb->buff)
		वापस -EINVAL;

	स_रखो(ltb->buff, 0, ltb->size);
	वापस 0;
पूर्ण

अटल व्योम deactivate_rx_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_active_rx_pools; i++)
		adapter->rx_pool[i].active = 0;
पूर्ण

अटल व्योम replenish_rx_pool(काष्ठा ibmvnic_adapter *adapter,
			      काष्ठा ibmvnic_rx_pool *pool)
अणु
	पूर्णांक count = pool->size - atomic_पढ़ो(&pool->available);
	u64 handle = adapter->rx_scrq[pool->index]->handle;
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_ind_xmit_queue *ind_bufp;
	काष्ठा ibmvnic_sub_crq_queue *rx_scrq;
	जोड़ sub_crq *sub_crq;
	पूर्णांक buffers_added = 0;
	अचिन्हित दीर्घ lpar_rc;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक offset;
	dma_addr_t dma_addr;
	अचिन्हित अक्षर *dst;
	पूर्णांक shअगरt = 0;
	पूर्णांक index;
	पूर्णांक i;

	अगर (!pool->active)
		वापस;

	rx_scrq = adapter->rx_scrq[pool->index];
	ind_bufp = &rx_scrq->ind_buf;
	क्रम (i = 0; i < count; ++i) अणु
		skb = netdev_alloc_skb(adapter->netdev, pool->buff_size);
		अगर (!skb) अणु
			dev_err(dev, "Couldn't replenish rx buff\n");
			adapter->replenish_no_mem++;
			अवरोध;
		पूर्ण

		index = pool->मुक्त_map[pool->next_मुक्त];

		अगर (pool->rx_buff[index].skb)
			dev_err(dev, "Inconsistent free_map!\n");

		/* Copy the skb to the दीर्घ term mapped DMA buffer */
		offset = index * pool->buff_size;
		dst = pool->दीर्घ_term_buff.buff + offset;
		स_रखो(dst, 0, pool->buff_size);
		dma_addr = pool->दीर्घ_term_buff.addr + offset;
		pool->rx_buff[index].data = dst;

		pool->मुक्त_map[pool->next_मुक्त] = IBMVNIC_INVALID_MAP;
		pool->rx_buff[index].dma = dma_addr;
		pool->rx_buff[index].skb = skb;
		pool->rx_buff[index].pool_index = pool->index;
		pool->rx_buff[index].size = pool->buff_size;

		sub_crq = &ind_bufp->indir_arr[ind_bufp->index++];
		स_रखो(sub_crq, 0, माप(*sub_crq));
		sub_crq->rx_add.first = IBMVNIC_CRQ_CMD;
		sub_crq->rx_add.correlator =
		    cpu_to_be64((u64)&pool->rx_buff[index]);
		sub_crq->rx_add.ioba = cpu_to_be32(dma_addr);
		sub_crq->rx_add.map_id = pool->दीर्घ_term_buff.map_id;

		/* The length field of the sCRQ is defined to be 24 bits so the
		 * buffer size needs to be left shअगरted by a byte beक्रमe it is
		 * converted to big endian to prevent the last byte from being
		 * truncated.
		 */
#अगर_घोषित __LITTLE_ENDIAN__
		shअगरt = 8;
#पूर्ण_अगर
		sub_crq->rx_add.len = cpu_to_be32(pool->buff_size << shअगरt);
		pool->next_मुक्त = (pool->next_मुक्त + 1) % pool->size;
		अगर (ind_bufp->index == IBMVNIC_MAX_IND_DESCS ||
		    i == count - 1) अणु
			lpar_rc =
				send_subcrq_indirect(adapter, handle,
						     (u64)ind_bufp->indir_dma,
						     (u64)ind_bufp->index);
			अगर (lpar_rc != H_SUCCESS)
				जाओ failure;
			buffers_added += ind_bufp->index;
			adapter->replenish_add_buff_success += ind_bufp->index;
			ind_bufp->index = 0;
		पूर्ण
	पूर्ण
	atomic_add(buffers_added, &pool->available);
	वापस;

failure:
	अगर (lpar_rc != H_PARAMETER && lpar_rc != H_CLOSED)
		dev_err_ratelimited(dev, "rx: replenish packet buffer failed\n");
	क्रम (i = ind_bufp->index - 1; i >= 0; --i) अणु
		काष्ठा ibmvnic_rx_buff *rx_buff;

		pool->next_मुक्त = pool->next_मुक्त == 0 ?
				  pool->size - 1 : pool->next_मुक्त - 1;
		sub_crq = &ind_bufp->indir_arr[i];
		rx_buff = (काष्ठा ibmvnic_rx_buff *)
				be64_to_cpu(sub_crq->rx_add.correlator);
		index = (पूर्णांक)(rx_buff - pool->rx_buff);
		pool->मुक्त_map[pool->next_मुक्त] = index;
		dev_kमुक्त_skb_any(pool->rx_buff[index].skb);
		pool->rx_buff[index].skb = शून्य;
	पूर्ण
	adapter->replenish_add_buff_failure += ind_bufp->index;
	atomic_add(buffers_added, &pool->available);
	ind_bufp->index = 0;
	अगर (lpar_rc == H_CLOSED || adapter->failover_pending) अणु
		/* Disable buffer pool replenishment and report carrier off अगर
		 * queue is बंदd or pending failover.
		 * Firmware guarantees that a संकेत will be sent to the
		 * driver, triggering a reset.
		 */
		deactivate_rx_pools(adapter);
		netअगर_carrier_off(adapter->netdev);
	पूर्ण
पूर्ण

अटल व्योम replenish_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i;

	adapter->replenish_task_cycles++;
	क्रम (i = 0; i < adapter->num_active_rx_pools; i++) अणु
		अगर (adapter->rx_pool[i].active)
			replenish_rx_pool(adapter, &adapter->rx_pool[i]);
	पूर्ण

	netdev_dbg(adapter->netdev, "Replenished %d pools\n", i);
पूर्ण

अटल व्योम release_stats_buffers(काष्ठा ibmvnic_adapter *adapter)
अणु
	kमुक्त(adapter->tx_stats_buffers);
	kमुक्त(adapter->rx_stats_buffers);
	adapter->tx_stats_buffers = शून्य;
	adapter->rx_stats_buffers = शून्य;
पूर्ण

अटल पूर्णांक init_stats_buffers(काष्ठा ibmvnic_adapter *adapter)
अणु
	adapter->tx_stats_buffers =
				kसुस्मृति(IBMVNIC_MAX_QUEUES,
					माप(काष्ठा ibmvnic_tx_queue_stats),
					GFP_KERNEL);
	अगर (!adapter->tx_stats_buffers)
		वापस -ENOMEM;

	adapter->rx_stats_buffers =
				kसुस्मृति(IBMVNIC_MAX_QUEUES,
					माप(काष्ठा ibmvnic_rx_queue_stats),
					GFP_KERNEL);
	अगर (!adapter->rx_stats_buffers)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम release_stats_token(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;

	अगर (!adapter->stats_token)
		वापस;

	dma_unmap_single(dev, adapter->stats_token,
			 माप(काष्ठा ibmvnic_statistics),
			 DMA_FROM_DEVICE);
	adapter->stats_token = 0;
पूर्ण

अटल पूर्णांक init_stats_token(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	dma_addr_t stok;

	stok = dma_map_single(dev, &adapter->stats,
			      माप(काष्ठा ibmvnic_statistics),
			      DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, stok)) अणु
		dev_err(dev, "Couldn't map stats buffer\n");
		वापस -1;
	पूर्ण

	adapter->stats_token = stok;
	netdev_dbg(adapter->netdev, "Stats token initialized (%llx)\n", stok);
	वापस 0;
पूर्ण

अटल पूर्णांक reset_rx_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_rx_pool *rx_pool;
	u64 buff_size;
	पूर्णांक rx_scrqs;
	पूर्णांक i, j, rc;

	अगर (!adapter->rx_pool)
		वापस -1;

	buff_size = adapter->cur_rx_buf_sz;
	rx_scrqs = adapter->num_active_rx_pools;
	क्रम (i = 0; i < rx_scrqs; i++) अणु
		rx_pool = &adapter->rx_pool[i];

		netdev_dbg(adapter->netdev, "Re-setting rx_pool[%d]\n", i);

		अगर (rx_pool->buff_size != buff_size) अणु
			मुक्त_दीर्घ_term_buff(adapter, &rx_pool->दीर्घ_term_buff);
			rx_pool->buff_size = ALIGN(buff_size, L1_CACHE_BYTES);
			rc = alloc_दीर्घ_term_buff(adapter,
						  &rx_pool->दीर्घ_term_buff,
						  rx_pool->size *
						  rx_pool->buff_size);
		पूर्ण अन्यथा अणु
			rc = reset_दीर्घ_term_buff(&rx_pool->दीर्घ_term_buff);
		पूर्ण

		अगर (rc)
			वापस rc;

		क्रम (j = 0; j < rx_pool->size; j++)
			rx_pool->मुक्त_map[j] = j;

		स_रखो(rx_pool->rx_buff, 0,
		       rx_pool->size * माप(काष्ठा ibmvnic_rx_buff));

		atomic_set(&rx_pool->available, 0);
		rx_pool->next_alloc = 0;
		rx_pool->next_मुक्त = 0;
		rx_pool->active = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम release_rx_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_rx_pool *rx_pool;
	पूर्णांक i, j;

	अगर (!adapter->rx_pool)
		वापस;

	क्रम (i = 0; i < adapter->num_active_rx_pools; i++) अणु
		rx_pool = &adapter->rx_pool[i];

		netdev_dbg(adapter->netdev, "Releasing rx_pool[%d]\n", i);

		kमुक्त(rx_pool->मुक्त_map);
		मुक्त_दीर्घ_term_buff(adapter, &rx_pool->दीर्घ_term_buff);

		अगर (!rx_pool->rx_buff)
			जारी;

		क्रम (j = 0; j < rx_pool->size; j++) अणु
			अगर (rx_pool->rx_buff[j].skb) अणु
				dev_kमुक्त_skb_any(rx_pool->rx_buff[j].skb);
				rx_pool->rx_buff[j].skb = शून्य;
			पूर्ण
		पूर्ण

		kमुक्त(rx_pool->rx_buff);
	पूर्ण

	kमुक्त(adapter->rx_pool);
	adapter->rx_pool = शून्य;
	adapter->num_active_rx_pools = 0;
पूर्ण

अटल पूर्णांक init_rx_pools(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_rx_pool *rx_pool;
	पूर्णांक rxadd_subcrqs;
	u64 buff_size;
	पूर्णांक i, j;

	rxadd_subcrqs = adapter->num_active_rx_scrqs;
	buff_size = adapter->cur_rx_buf_sz;

	adapter->rx_pool = kसुस्मृति(rxadd_subcrqs,
				   माप(काष्ठा ibmvnic_rx_pool),
				   GFP_KERNEL);
	अगर (!adapter->rx_pool) अणु
		dev_err(dev, "Failed to allocate rx pools\n");
		वापस -1;
	पूर्ण

	adapter->num_active_rx_pools = rxadd_subcrqs;

	क्रम (i = 0; i < rxadd_subcrqs; i++) अणु
		rx_pool = &adapter->rx_pool[i];

		netdev_dbg(adapter->netdev,
			   "Initializing rx_pool[%d], %lld buffs, %lld bytes each\n",
			   i, adapter->req_rx_add_entries_per_subcrq,
			   buff_size);

		rx_pool->size = adapter->req_rx_add_entries_per_subcrq;
		rx_pool->index = i;
		rx_pool->buff_size = ALIGN(buff_size, L1_CACHE_BYTES);
		rx_pool->active = 1;

		rx_pool->मुक्त_map = kसुस्मृति(rx_pool->size, माप(पूर्णांक),
					    GFP_KERNEL);
		अगर (!rx_pool->मुक्त_map) अणु
			release_rx_pools(adapter);
			वापस -1;
		पूर्ण

		rx_pool->rx_buff = kसुस्मृति(rx_pool->size,
					   माप(काष्ठा ibmvnic_rx_buff),
					   GFP_KERNEL);
		अगर (!rx_pool->rx_buff) अणु
			dev_err(dev, "Couldn't alloc rx buffers\n");
			release_rx_pools(adapter);
			वापस -1;
		पूर्ण

		अगर (alloc_दीर्घ_term_buff(adapter, &rx_pool->दीर्घ_term_buff,
					 rx_pool->size * rx_pool->buff_size)) अणु
			release_rx_pools(adapter);
			वापस -1;
		पूर्ण

		क्रम (j = 0; j < rx_pool->size; ++j)
			rx_pool->मुक्त_map[j] = j;

		atomic_set(&rx_pool->available, 0);
		rx_pool->next_alloc = 0;
		rx_pool->next_मुक्त = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक reset_one_tx_pool(काष्ठा ibmvnic_tx_pool *tx_pool)
अणु
	पूर्णांक rc, i;

	rc = reset_दीर्घ_term_buff(&tx_pool->दीर्घ_term_buff);
	अगर (rc)
		वापस rc;

	स_रखो(tx_pool->tx_buff, 0,
	       tx_pool->num_buffers *
	       माप(काष्ठा ibmvnic_tx_buff));

	क्रम (i = 0; i < tx_pool->num_buffers; i++)
		tx_pool->मुक्त_map[i] = i;

	tx_pool->consumer_index = 0;
	tx_pool->producer_index = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक reset_tx_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक tx_scrqs;
	पूर्णांक i, rc;

	अगर (!adapter->tx_pool)
		वापस -1;

	tx_scrqs = adapter->num_active_tx_pools;
	क्रम (i = 0; i < tx_scrqs; i++) अणु
		rc = reset_one_tx_pool(&adapter->tso_pool[i]);
		अगर (rc)
			वापस rc;
		rc = reset_one_tx_pool(&adapter->tx_pool[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम release_vpd_data(काष्ठा ibmvnic_adapter *adapter)
अणु
	अगर (!adapter->vpd)
		वापस;

	kमुक्त(adapter->vpd->buff);
	kमुक्त(adapter->vpd);

	adapter->vpd = शून्य;
पूर्ण

अटल व्योम release_one_tx_pool(काष्ठा ibmvnic_adapter *adapter,
				काष्ठा ibmvnic_tx_pool *tx_pool)
अणु
	kमुक्त(tx_pool->tx_buff);
	kमुक्त(tx_pool->मुक्त_map);
	मुक्त_दीर्घ_term_buff(adapter, &tx_pool->दीर्घ_term_buff);
पूर्ण

अटल व्योम release_tx_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i;

	अगर (!adapter->tx_pool)
		वापस;

	क्रम (i = 0; i < adapter->num_active_tx_pools; i++) अणु
		release_one_tx_pool(adapter, &adapter->tx_pool[i]);
		release_one_tx_pool(adapter, &adapter->tso_pool[i]);
	पूर्ण

	kमुक्त(adapter->tx_pool);
	adapter->tx_pool = शून्य;
	kमुक्त(adapter->tso_pool);
	adapter->tso_pool = शून्य;
	adapter->num_active_tx_pools = 0;
पूर्ण

अटल पूर्णांक init_one_tx_pool(काष्ठा net_device *netdev,
			    काष्ठा ibmvnic_tx_pool *tx_pool,
			    पूर्णांक num_entries, पूर्णांक buf_size)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	tx_pool->tx_buff = kसुस्मृति(num_entries,
				   माप(काष्ठा ibmvnic_tx_buff),
				   GFP_KERNEL);
	अगर (!tx_pool->tx_buff)
		वापस -1;

	अगर (alloc_दीर्घ_term_buff(adapter, &tx_pool->दीर्घ_term_buff,
				 num_entries * buf_size))
		वापस -1;

	tx_pool->मुक्त_map = kसुस्मृति(num_entries, माप(पूर्णांक), GFP_KERNEL);
	अगर (!tx_pool->मुक्त_map)
		वापस -1;

	क्रम (i = 0; i < num_entries; i++)
		tx_pool->मुक्त_map[i] = i;

	tx_pool->consumer_index = 0;
	tx_pool->producer_index = 0;
	tx_pool->num_buffers = num_entries;
	tx_pool->buf_size = buf_size;

	वापस 0;
पूर्ण

अटल पूर्णांक init_tx_pools(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक tx_subcrqs;
	u64 buff_size;
	पूर्णांक i, rc;

	tx_subcrqs = adapter->num_active_tx_scrqs;
	adapter->tx_pool = kसुस्मृति(tx_subcrqs,
				   माप(काष्ठा ibmvnic_tx_pool), GFP_KERNEL);
	अगर (!adapter->tx_pool)
		वापस -1;

	adapter->tso_pool = kसुस्मृति(tx_subcrqs,
				    माप(काष्ठा ibmvnic_tx_pool), GFP_KERNEL);
	अगर (!adapter->tso_pool)
		वापस -1;

	adapter->num_active_tx_pools = tx_subcrqs;

	क्रम (i = 0; i < tx_subcrqs; i++) अणु
		buff_size = adapter->req_mtu + VLAN_HLEN;
		buff_size = ALIGN(buff_size, L1_CACHE_BYTES);
		rc = init_one_tx_pool(netdev, &adapter->tx_pool[i],
				      adapter->req_tx_entries_per_subcrq,
				      buff_size);
		अगर (rc) अणु
			release_tx_pools(adapter);
			वापस rc;
		पूर्ण

		rc = init_one_tx_pool(netdev, &adapter->tso_pool[i],
				      IBMVNIC_TSO_BUFS,
				      IBMVNIC_TSO_BUF_SZ);
		अगर (rc) अणु
			release_tx_pools(adapter);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ibmvnic_napi_enable(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i;

	अगर (adapter->napi_enabled)
		वापस;

	क्रम (i = 0; i < adapter->req_rx_queues; i++)
		napi_enable(&adapter->napi[i]);

	adapter->napi_enabled = true;
पूर्ण

अटल व्योम ibmvnic_napi_disable(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i;

	अगर (!adapter->napi_enabled)
		वापस;

	क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
		netdev_dbg(adapter->netdev, "Disabling napi[%d]\n", i);
		napi_disable(&adapter->napi[i]);
	पूर्ण

	adapter->napi_enabled = false;
पूर्ण

अटल पूर्णांक init_napi(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i;

	adapter->napi = kसुस्मृति(adapter->req_rx_queues,
				माप(काष्ठा napi_काष्ठा), GFP_KERNEL);
	अगर (!adapter->napi)
		वापस -ENOMEM;

	क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
		netdev_dbg(adapter->netdev, "Adding napi[%d]\n", i);
		netअगर_napi_add(adapter->netdev, &adapter->napi[i],
			       ibmvnic_poll, NAPI_POLL_WEIGHT);
	पूर्ण

	adapter->num_active_rx_napi = adapter->req_rx_queues;
	वापस 0;
पूर्ण

अटल व्योम release_napi(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i;

	अगर (!adapter->napi)
		वापस;

	क्रम (i = 0; i < adapter->num_active_rx_napi; i++) अणु
		netdev_dbg(adapter->netdev, "Releasing napi[%d]\n", i);
		netअगर_napi_del(&adapter->napi[i]);
	पूर्ण

	kमुक्त(adapter->napi);
	adapter->napi = शून्य;
	adapter->num_active_rx_napi = 0;
	adapter->napi_enabled = false;
पूर्ण

अटल स्थिर अक्षर *adapter_state_to_string(क्रमागत vnic_state state)
अणु
	चयन (state) अणु
	हाल VNIC_PROBING:
		वापस "PROBING";
	हाल VNIC_PROBED:
		वापस "PROBED";
	हाल VNIC_OPENING:
		वापस "OPENING";
	हाल VNIC_OPEN:
		वापस "OPEN";
	हाल VNIC_CLOSING:
		वापस "CLOSING";
	हाल VNIC_CLOSED:
		वापस "CLOSED";
	हाल VNIC_REMOVING:
		वापस "REMOVING";
	हाल VNIC_REMOVED:
		वापस "REMOVED";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल पूर्णांक ibmvnic_login(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(20000);
	पूर्णांक retry_count = 0;
	पूर्णांक retries = 10;
	bool retry;
	पूर्णांक rc;

	करो अणु
		retry = false;
		अगर (retry_count > retries) अणु
			netdev_warn(netdev, "Login attempts exceeded\n");
			वापस -1;
		पूर्ण

		adapter->init_करोne_rc = 0;
		reinit_completion(&adapter->init_करोne);
		rc = send_login(adapter);
		अगर (rc)
			वापस rc;

		अगर (!रुको_क्रम_completion_समयout(&adapter->init_करोne,
						 समयout)) अणु
			netdev_warn(netdev, "Login timed out, retrying...\n");
			retry = true;
			adapter->init_करोne_rc = 0;
			retry_count++;
			जारी;
		पूर्ण

		अगर (adapter->init_करोne_rc == ABORTED) अणु
			netdev_warn(netdev, "Login aborted, retrying...\n");
			retry = true;
			adapter->init_करोne_rc = 0;
			retry_count++;
			/* FW or device may be busy, so
			 * रुको a bit beक्रमe retrying login
			 */
			msleep(500);
		पूर्ण अन्यथा अगर (adapter->init_करोne_rc == PARTIALSUCCESS) अणु
			retry_count++;
			release_sub_crqs(adapter, 1);

			retry = true;
			netdev_dbg(netdev,
				   "Received partial success, retrying...\n");
			adapter->init_करोne_rc = 0;
			reinit_completion(&adapter->init_करोne);
			send_query_cap(adapter);
			अगर (!रुको_क्रम_completion_समयout(&adapter->init_करोne,
							 समयout)) अणु
				netdev_warn(netdev,
					    "Capabilities query timed out\n");
				वापस -1;
			पूर्ण

			rc = init_sub_crqs(adapter);
			अगर (rc) अणु
				netdev_warn(netdev,
					    "SCRQ initialization failed\n");
				वापस -1;
			पूर्ण

			rc = init_sub_crq_irqs(adapter);
			अगर (rc) अणु
				netdev_warn(netdev,
					    "SCRQ irq initialization failed\n");
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अगर (adapter->init_करोne_rc) अणु
			netdev_warn(netdev, "Adapter login failed\n");
			वापस -1;
		पूर्ण
	पूर्ण जबतक (retry);

	__ibmvnic_set_mac(netdev, adapter->mac_addr);

	netdev_dbg(netdev, "[S:%s] Login succeeded\n", adapter_state_to_string(adapter->state));
	वापस 0;
पूर्ण

अटल व्योम release_login_buffer(काष्ठा ibmvnic_adapter *adapter)
अणु
	kमुक्त(adapter->login_buf);
	adapter->login_buf = शून्य;
पूर्ण

अटल व्योम release_login_rsp_buffer(काष्ठा ibmvnic_adapter *adapter)
अणु
	kमुक्त(adapter->login_rsp_buf);
	adapter->login_rsp_buf = शून्य;
पूर्ण

अटल व्योम release_resources(काष्ठा ibmvnic_adapter *adapter)
अणु
	release_vpd_data(adapter);

	release_tx_pools(adapter);
	release_rx_pools(adapter);

	release_napi(adapter);
	release_login_buffer(adapter);
	release_login_rsp_buffer(adapter);
पूर्ण

अटल पूर्णांक set_link_state(काष्ठा ibmvnic_adapter *adapter, u8 link_state)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(20000);
	जोड़ ibmvnic_crq crq;
	bool resend;
	पूर्णांक rc;

	netdev_dbg(netdev, "setting link state %d\n", link_state);

	स_रखो(&crq, 0, माप(crq));
	crq.logical_link_state.first = IBMVNIC_CRQ_CMD;
	crq.logical_link_state.cmd = LOGICAL_LINK_STATE;
	crq.logical_link_state.link_state = link_state;

	करो अणु
		resend = false;

		reinit_completion(&adapter->init_करोne);
		rc = ibmvnic_send_crq(adapter, &crq);
		अगर (rc) अणु
			netdev_err(netdev, "Failed to set link state\n");
			वापस rc;
		पूर्ण

		अगर (!रुको_क्रम_completion_समयout(&adapter->init_करोne,
						 समयout)) अणु
			netdev_err(netdev, "timeout setting link state\n");
			वापस -1;
		पूर्ण

		अगर (adapter->init_करोne_rc == PARTIALSUCCESS) अणु
			/* Partuial success, delay and re-send */
			mdelay(1000);
			resend = true;
		पूर्ण अन्यथा अगर (adapter->init_करोne_rc) अणु
			netdev_warn(netdev, "Unable to set link state, rc=%d\n",
				    adapter->init_करोne_rc);
			वापस adapter->init_करोne_rc;
		पूर्ण
	पूर्ण जबतक (resend);

	वापस 0;
पूर्ण

अटल पूर्णांक set_real_num_queues(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc;

	netdev_dbg(netdev, "Setting real tx/rx queues (%llx/%llx)\n",
		   adapter->req_tx_queues, adapter->req_rx_queues);

	rc = netअगर_set_real_num_tx_queues(netdev, adapter->req_tx_queues);
	अगर (rc) अणु
		netdev_err(netdev, "failed to set the number of tx queues\n");
		वापस rc;
	पूर्ण

	rc = netअगर_set_real_num_rx_queues(netdev, adapter->req_rx_queues);
	अगर (rc)
		netdev_err(netdev, "failed to set the number of rx queues\n");

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_get_vpd(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	जोड़ ibmvnic_crq crq;
	पूर्णांक len = 0;
	पूर्णांक rc;

	अगर (adapter->vpd->buff)
		len = adapter->vpd->len;

	mutex_lock(&adapter->fw_lock);
	adapter->fw_करोne_rc = 0;
	reinit_completion(&adapter->fw_करोne);

	crq.get_vpd_size.first = IBMVNIC_CRQ_CMD;
	crq.get_vpd_size.cmd = GET_VPD_SIZE;
	rc = ibmvnic_send_crq(adapter, &crq);
	अगर (rc) अणु
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण

	rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->fw_करोne, 10000);
	अगर (rc) अणु
		dev_err(dev, "Could not retrieve VPD size, rc = %d\n", rc);
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण
	mutex_unlock(&adapter->fw_lock);

	अगर (!adapter->vpd->len)
		वापस -ENODATA;

	अगर (!adapter->vpd->buff)
		adapter->vpd->buff = kzalloc(adapter->vpd->len, GFP_KERNEL);
	अन्यथा अगर (adapter->vpd->len != len)
		adapter->vpd->buff =
			kपुनः_स्मृति(adapter->vpd->buff,
				 adapter->vpd->len, GFP_KERNEL);

	अगर (!adapter->vpd->buff) अणु
		dev_err(dev, "Could allocate VPD buffer\n");
		वापस -ENOMEM;
	पूर्ण

	adapter->vpd->dma_addr =
		dma_map_single(dev, adapter->vpd->buff, adapter->vpd->len,
			       DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, adapter->vpd->dma_addr)) अणु
		dev_err(dev, "Could not map VPD buffer\n");
		kमुक्त(adapter->vpd->buff);
		adapter->vpd->buff = शून्य;
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&adapter->fw_lock);
	adapter->fw_करोne_rc = 0;
	reinit_completion(&adapter->fw_करोne);

	crq.get_vpd.first = IBMVNIC_CRQ_CMD;
	crq.get_vpd.cmd = GET_VPD;
	crq.get_vpd.ioba = cpu_to_be32(adapter->vpd->dma_addr);
	crq.get_vpd.len = cpu_to_be32((u32)adapter->vpd->len);
	rc = ibmvnic_send_crq(adapter, &crq);
	अगर (rc) अणु
		kमुक्त(adapter->vpd->buff);
		adapter->vpd->buff = शून्य;
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण

	rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->fw_करोne, 10000);
	अगर (rc) अणु
		dev_err(dev, "Unable to retrieve VPD, rc = %d\n", rc);
		kमुक्त(adapter->vpd->buff);
		adapter->vpd->buff = शून्य;
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण

	mutex_unlock(&adapter->fw_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक init_resources(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक rc;

	rc = set_real_num_queues(netdev);
	अगर (rc)
		वापस rc;

	adapter->vpd = kzalloc(माप(*adapter->vpd), GFP_KERNEL);
	अगर (!adapter->vpd)
		वापस -ENOMEM;

	/* Vital Product Data (VPD) */
	rc = ibmvnic_get_vpd(adapter);
	अगर (rc) अणु
		netdev_err(netdev, "failed to initialize Vital Product Data (VPD)\n");
		वापस rc;
	पूर्ण

	adapter->map_id = 1;

	rc = init_napi(adapter);
	अगर (rc)
		वापस rc;

	send_query_map(adapter);

	rc = init_rx_pools(netdev);
	अगर (rc)
		वापस rc;

	rc = init_tx_pools(netdev);
	वापस rc;
पूर्ण

अटल पूर्णांक __ibmvnic_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	क्रमागत vnic_state prev_state = adapter->state;
	पूर्णांक i, rc;

	adapter->state = VNIC_OPENING;
	replenish_pools(adapter);
	ibmvnic_napi_enable(adapter);

	/* We're पढ़ोy to receive frames, enable the sub-crq पूर्णांकerrupts and
	 * set the logical link state to up
	 */
	क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
		netdev_dbg(netdev, "Enabling rx_scrq[%d] irq\n", i);
		अगर (prev_state == VNIC_CLOSED)
			enable_irq(adapter->rx_scrq[i]->irq);
		enable_scrq_irq(adapter, adapter->rx_scrq[i]);
	पूर्ण

	क्रम (i = 0; i < adapter->req_tx_queues; i++) अणु
		netdev_dbg(netdev, "Enabling tx_scrq[%d] irq\n", i);
		अगर (prev_state == VNIC_CLOSED)
			enable_irq(adapter->tx_scrq[i]->irq);
		enable_scrq_irq(adapter, adapter->tx_scrq[i]);
		netdev_tx_reset_queue(netdev_get_tx_queue(netdev, i));
	पूर्ण

	rc = set_link_state(adapter, IBMVNIC_LOGICAL_LNK_UP);
	अगर (rc) अणु
		ibmvnic_napi_disable(adapter);
		release_resources(adapter);
		वापस rc;
	पूर्ण

	netअगर_tx_start_all_queues(netdev);

	adapter->state = VNIC_OPEN;
	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc;

	ASSERT_RTNL();

	/* If device failover is pending or we are about to reset, just set
	 * device state and वापस. Device operation will be handled by reset
	 * routine.
	 *
	 * It should be safe to overग_लिखो the adapter->state here. Since
	 * we hold the rtnl, either the reset has not actually started or
	 * the rtnl got dropped during the set_link_state() in करो_reset().
	 * In the क्रमmer हाल, no one अन्यथा is changing the state (again we
	 * have the rtnl) and in the latter हाल, करो_reset() will detect and
	 * honor our setting below.
	 */
	अगर (adapter->failover_pending || (test_bit(0, &adapter->resetting))) अणु
		netdev_dbg(netdev, "[S:%s FOP:%d] Resetting, deferring open\n",
			   adapter_state_to_string(adapter->state),
			   adapter->failover_pending);
		adapter->state = VNIC_OPEN;
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (adapter->state != VNIC_CLOSED) अणु
		rc = ibmvnic_login(netdev);
		अगर (rc)
			जाओ out;

		rc = init_resources(adapter);
		अगर (rc) अणु
			netdev_err(netdev, "failed to initialize resources\n");
			release_resources(adapter);
			जाओ out;
		पूर्ण
	पूर्ण

	rc = __ibmvnic_खोलो(netdev);

out:
	/* If खोलो failed and there is a pending failover or in-progress reset,
	 * set device state and वापस. Device operation will be handled by
	 * reset routine. See also comments above regarding rtnl.
	 */
	अगर (rc &&
	    (adapter->failover_pending || (test_bit(0, &adapter->resetting)))) अणु
		adapter->state = VNIC_OPEN;
		rc = 0;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम clean_rx_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_rx_pool *rx_pool;
	काष्ठा ibmvnic_rx_buff *rx_buff;
	u64 rx_entries;
	पूर्णांक rx_scrqs;
	पूर्णांक i, j;

	अगर (!adapter->rx_pool)
		वापस;

	rx_scrqs = adapter->num_active_rx_pools;
	rx_entries = adapter->req_rx_add_entries_per_subcrq;

	/* Free any reमुख्यing skbs in the rx buffer pools */
	क्रम (i = 0; i < rx_scrqs; i++) अणु
		rx_pool = &adapter->rx_pool[i];
		अगर (!rx_pool || !rx_pool->rx_buff)
			जारी;

		netdev_dbg(adapter->netdev, "Cleaning rx_pool[%d]\n", i);
		क्रम (j = 0; j < rx_entries; j++) अणु
			rx_buff = &rx_pool->rx_buff[j];
			अगर (rx_buff && rx_buff->skb) अणु
				dev_kमुक्त_skb_any(rx_buff->skb);
				rx_buff->skb = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम clean_one_tx_pool(काष्ठा ibmvnic_adapter *adapter,
			      काष्ठा ibmvnic_tx_pool *tx_pool)
अणु
	काष्ठा ibmvnic_tx_buff *tx_buff;
	u64 tx_entries;
	पूर्णांक i;

	अगर (!tx_pool || !tx_pool->tx_buff)
		वापस;

	tx_entries = tx_pool->num_buffers;

	क्रम (i = 0; i < tx_entries; i++) अणु
		tx_buff = &tx_pool->tx_buff[i];
		अगर (tx_buff && tx_buff->skb) अणु
			dev_kमुक्त_skb_any(tx_buff->skb);
			tx_buff->skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम clean_tx_pools(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक tx_scrqs;
	पूर्णांक i;

	अगर (!adapter->tx_pool || !adapter->tso_pool)
		वापस;

	tx_scrqs = adapter->num_active_tx_pools;

	/* Free any reमुख्यing skbs in the tx buffer pools */
	क्रम (i = 0; i < tx_scrqs; i++) अणु
		netdev_dbg(adapter->netdev, "Cleaning tx_pool[%d]\n", i);
		clean_one_tx_pool(adapter, &adapter->tx_pool[i]);
		clean_one_tx_pool(adapter, &adapter->tso_pool[i]);
	पूर्ण
पूर्ण

अटल व्योम ibmvnic_disable_irqs(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i;

	अगर (adapter->tx_scrq) अणु
		क्रम (i = 0; i < adapter->req_tx_queues; i++)
			अगर (adapter->tx_scrq[i]->irq) अणु
				netdev_dbg(netdev,
					   "Disabling tx_scrq[%d] irq\n", i);
				disable_scrq_irq(adapter, adapter->tx_scrq[i]);
				disable_irq(adapter->tx_scrq[i]->irq);
			पूर्ण
	पूर्ण

	अगर (adapter->rx_scrq) अणु
		क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
			अगर (adapter->rx_scrq[i]->irq) अणु
				netdev_dbg(netdev,
					   "Disabling rx_scrq[%d] irq\n", i);
				disable_scrq_irq(adapter, adapter->rx_scrq[i]);
				disable_irq(adapter->rx_scrq[i]->irq);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ibmvnic_cleanup(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	/* ensure that transmissions are stopped अगर called by करो_reset */
	अगर (test_bit(0, &adapter->resetting))
		netअगर_tx_disable(netdev);
	अन्यथा
		netअगर_tx_stop_all_queues(netdev);

	ibmvnic_napi_disable(adapter);
	ibmvnic_disable_irqs(adapter);

	clean_rx_pools(adapter);
	clean_tx_pools(adapter);
पूर्ण

अटल पूर्णांक __ibmvnic_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc = 0;

	adapter->state = VNIC_CLOSING;
	rc = set_link_state(adapter, IBMVNIC_LOGICAL_LNK_DN);
	adapter->state = VNIC_CLOSED;
	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc;

	netdev_dbg(netdev, "[S:%s FOP:%d FRR:%d] Closing\n",
		   adapter_state_to_string(adapter->state),
		   adapter->failover_pending,
		   adapter->क्रमce_reset_recovery);

	/* If device failover is pending, just set device state and वापस.
	 * Device operation will be handled by reset routine.
	 */
	अगर (adapter->failover_pending) अणु
		adapter->state = VNIC_CLOSED;
		वापस 0;
	पूर्ण

	rc = __ibmvnic_बंद(netdev);
	ibmvnic_cleanup(netdev);

	वापस rc;
पूर्ण

/**
 * build_hdr_data - creates L2/L3/L4 header data buffer
 * @hdr_field: bitfield determining needed headers
 * @skb: socket buffer
 * @hdr_len: array of header lengths
 * @hdr_data: buffer to ग_लिखो the header to
 *
 * Reads hdr_field to determine which headers are needed by firmware.
 * Builds a buffer containing these headers.  Saves inभागidual header
 * lengths and total buffer length to be used to build descriptors.
 */
अटल पूर्णांक build_hdr_data(u8 hdr_field, काष्ठा sk_buff *skb,
			  पूर्णांक *hdr_len, u8 *hdr_data)
अणु
	पूर्णांक len = 0;
	u8 *hdr;

	अगर (skb_vlan_tagged(skb) && !skb_vlan_tag_present(skb))
		hdr_len[0] = माप(काष्ठा vlan_ethhdr);
	अन्यथा
		hdr_len[0] = माप(काष्ठा ethhdr);

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		hdr_len[1] = ip_hdr(skb)->ihl * 4;
		अगर (ip_hdr(skb)->protocol == IPPROTO_TCP)
			hdr_len[2] = tcp_hdrlen(skb);
		अन्यथा अगर (ip_hdr(skb)->protocol == IPPROTO_UDP)
			hdr_len[2] = माप(काष्ठा udphdr);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		hdr_len[1] = माप(काष्ठा ipv6hdr);
		अगर (ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
			hdr_len[2] = tcp_hdrlen(skb);
		अन्यथा अगर (ipv6_hdr(skb)->nexthdr == IPPROTO_UDP)
			hdr_len[2] = माप(काष्ठा udphdr);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_ARP)) अणु
		hdr_len[1] = arp_hdr_len(skb->dev);
		hdr_len[2] = 0;
	पूर्ण

	स_रखो(hdr_data, 0, 120);
	अगर ((hdr_field >> 6) & 1) अणु
		hdr = skb_mac_header(skb);
		स_नकल(hdr_data, hdr, hdr_len[0]);
		len += hdr_len[0];
	पूर्ण

	अगर ((hdr_field >> 5) & 1) अणु
		hdr = skb_network_header(skb);
		स_नकल(hdr_data + len, hdr, hdr_len[1]);
		len += hdr_len[1];
	पूर्ण

	अगर ((hdr_field >> 4) & 1) अणु
		hdr = skb_transport_header(skb);
		स_नकल(hdr_data + len, hdr, hdr_len[2]);
		len += hdr_len[2];
	पूर्ण
	वापस len;
पूर्ण

/**
 * create_hdr_descs - create header and header extension descriptors
 * @hdr_field: bitfield determining needed headers
 * @hdr_data: buffer containing header data
 * @len: length of data buffer
 * @hdr_len: array of inभागidual header lengths
 * @scrq_arr: descriptor array
 *
 * Creates header and, अगर needed, header extension descriptors and
 * places them in a descriptor array, scrq_arr
 */

अटल पूर्णांक create_hdr_descs(u8 hdr_field, u8 *hdr_data, पूर्णांक len, पूर्णांक *hdr_len,
			    जोड़ sub_crq *scrq_arr)
अणु
	जोड़ sub_crq hdr_desc;
	पूर्णांक पंचांगp_len = len;
	पूर्णांक num_descs = 0;
	u8 *data, *cur;
	पूर्णांक पंचांगp;

	जबतक (पंचांगp_len > 0) अणु
		cur = hdr_data + len - पंचांगp_len;

		स_रखो(&hdr_desc, 0, माप(hdr_desc));
		अगर (cur != hdr_data) अणु
			data = hdr_desc.hdr_ext.data;
			पंचांगp = पंचांगp_len > 29 ? 29 : पंचांगp_len;
			hdr_desc.hdr_ext.first = IBMVNIC_CRQ_CMD;
			hdr_desc.hdr_ext.type = IBMVNIC_HDR_EXT_DESC;
			hdr_desc.hdr_ext.len = पंचांगp;
		पूर्ण अन्यथा अणु
			data = hdr_desc.hdr.data;
			पंचांगp = पंचांगp_len > 24 ? 24 : पंचांगp_len;
			hdr_desc.hdr.first = IBMVNIC_CRQ_CMD;
			hdr_desc.hdr.type = IBMVNIC_HDR_DESC;
			hdr_desc.hdr.len = पंचांगp;
			hdr_desc.hdr.l2_len = (u8)hdr_len[0];
			hdr_desc.hdr.l3_len = cpu_to_be16((u16)hdr_len[1]);
			hdr_desc.hdr.l4_len = (u8)hdr_len[2];
			hdr_desc.hdr.flag = hdr_field << 1;
		पूर्ण
		स_नकल(data, cur, पंचांगp);
		पंचांगp_len -= पंचांगp;
		*scrq_arr = hdr_desc;
		scrq_arr++;
		num_descs++;
	पूर्ण

	वापस num_descs;
पूर्ण

/**
 * build_hdr_descs_arr - build a header descriptor array
 * @txbuff: tx buffer
 * @num_entries: number of descriptors to be sent
 * @hdr_field: bit field determining which headers will be sent
 *
 * This function will build a TX descriptor array with applicable
 * L2/L3/L4 packet header descriptors to be sent by send_subcrq_indirect.
 */

अटल व्योम build_hdr_descs_arr(काष्ठा sk_buff *skb,
				जोड़ sub_crq *indir_arr,
				पूर्णांक *num_entries, u8 hdr_field)
अणु
	पूर्णांक hdr_len[3] = अणु0, 0, 0पूर्ण;
	u8 hdr_data[140] = अणु0पूर्ण;
	पूर्णांक tot_len;

	tot_len = build_hdr_data(hdr_field, skb, hdr_len,
				 hdr_data);
	*num_entries += create_hdr_descs(hdr_field, hdr_data, tot_len, hdr_len,
					 indir_arr + 1);
पूर्ण

अटल पूर्णांक ibmvnic_xmit_workarounds(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev)
अणु
	/* For some backing devices, mishandling of small packets
	 * can result in a loss of connection or TX stall. Device
	 * architects recommend that no packet should be smaller
	 * than the minimum MTU value provided to the driver, so
	 * pad any packets to that length
	 */
	अगर (skb->len < netdev->min_mtu)
		वापस skb_put_padto(skb, netdev->min_mtu);

	वापस 0;
पूर्ण

अटल व्योम ibmvnic_tx_scrq_clean_buffer(काष्ठा ibmvnic_adapter *adapter,
					 काष्ठा ibmvnic_sub_crq_queue *tx_scrq)
अणु
	काष्ठा ibmvnic_ind_xmit_queue *ind_bufp;
	काष्ठा ibmvnic_tx_buff *tx_buff;
	काष्ठा ibmvnic_tx_pool *tx_pool;
	जोड़ sub_crq tx_scrq_entry;
	पूर्णांक queue_num;
	पूर्णांक entries;
	पूर्णांक index;
	पूर्णांक i;

	ind_bufp = &tx_scrq->ind_buf;
	entries = (u64)ind_bufp->index;
	queue_num = tx_scrq->pool_index;

	क्रम (i = entries - 1; i >= 0; --i) अणु
		tx_scrq_entry = ind_bufp->indir_arr[i];
		अगर (tx_scrq_entry.v1.type != IBMVNIC_TX_DESC)
			जारी;
		index = be32_to_cpu(tx_scrq_entry.v1.correlator);
		अगर (index & IBMVNIC_TSO_POOL_MASK) अणु
			tx_pool = &adapter->tso_pool[queue_num];
			index &= ~IBMVNIC_TSO_POOL_MASK;
		पूर्ण अन्यथा अणु
			tx_pool = &adapter->tx_pool[queue_num];
		पूर्ण
		tx_pool->मुक्त_map[tx_pool->consumer_index] = index;
		tx_pool->consumer_index = tx_pool->consumer_index == 0 ?
					  tx_pool->num_buffers - 1 :
					  tx_pool->consumer_index - 1;
		tx_buff = &tx_pool->tx_buff[index];
		adapter->netdev->stats.tx_packets--;
		adapter->netdev->stats.tx_bytes -= tx_buff->skb->len;
		adapter->tx_stats_buffers[queue_num].packets--;
		adapter->tx_stats_buffers[queue_num].bytes -=
						tx_buff->skb->len;
		dev_kमुक्त_skb_any(tx_buff->skb);
		tx_buff->skb = शून्य;
		adapter->netdev->stats.tx_dropped++;
	पूर्ण
	ind_bufp->index = 0;
	अगर (atomic_sub_वापस(entries, &tx_scrq->used) <=
	    (adapter->req_tx_entries_per_subcrq / 2) &&
	    __netअगर_subqueue_stopped(adapter->netdev, queue_num)) अणु
		netअगर_wake_subqueue(adapter->netdev, queue_num);
		netdev_dbg(adapter->netdev, "Started queue %d\n",
			   queue_num);
	पूर्ण
पूर्ण

अटल पूर्णांक ibmvnic_tx_scrq_flush(काष्ठा ibmvnic_adapter *adapter,
				 काष्ठा ibmvnic_sub_crq_queue *tx_scrq)
अणु
	काष्ठा ibmvnic_ind_xmit_queue *ind_bufp;
	u64 dma_addr;
	u64 entries;
	u64 handle;
	पूर्णांक rc;

	ind_bufp = &tx_scrq->ind_buf;
	dma_addr = (u64)ind_bufp->indir_dma;
	entries = (u64)ind_bufp->index;
	handle = tx_scrq->handle;

	अगर (!entries)
		वापस 0;
	rc = send_subcrq_indirect(adapter, handle, dma_addr, entries);
	अगर (rc)
		ibmvnic_tx_scrq_clean_buffer(adapter, tx_scrq);
	अन्यथा
		ind_bufp->index = 0;
	वापस 0;
पूर्ण

अटल netdev_tx_t ibmvnic_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक queue_num = skb_get_queue_mapping(skb);
	u8 *hdrs = (u8 *)&adapter->tx_rx_desc_req;
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_ind_xmit_queue *ind_bufp;
	काष्ठा ibmvnic_tx_buff *tx_buff = शून्य;
	काष्ठा ibmvnic_sub_crq_queue *tx_scrq;
	काष्ठा ibmvnic_tx_pool *tx_pool;
	अचिन्हित पूर्णांक tx_send_failed = 0;
	netdev_tx_t ret = NETDEV_TX_OK;
	अचिन्हित पूर्णांक tx_map_failed = 0;
	जोड़ sub_crq indir_arr[16];
	अचिन्हित पूर्णांक tx_dropped = 0;
	अचिन्हित पूर्णांक tx_packets = 0;
	अचिन्हित पूर्णांक tx_bytes = 0;
	dma_addr_t data_dma_addr;
	काष्ठा netdev_queue *txq;
	अचिन्हित दीर्घ lpar_rc;
	जोड़ sub_crq tx_crq;
	अचिन्हित पूर्णांक offset;
	पूर्णांक num_entries = 1;
	अचिन्हित अक्षर *dst;
	पूर्णांक index = 0;
	u8 proto = 0;

	tx_scrq = adapter->tx_scrq[queue_num];
	txq = netdev_get_tx_queue(netdev, queue_num);
	ind_bufp = &tx_scrq->ind_buf;

	अगर (test_bit(0, &adapter->resetting)) अणु
		अगर (!netअगर_subqueue_stopped(netdev, skb))
			netअगर_stop_subqueue(netdev, queue_num);
		dev_kमुक्त_skb_any(skb);

		tx_send_failed++;
		tx_dropped++;
		ret = NETDEV_TX_OK;
		ibmvnic_tx_scrq_flush(adapter, tx_scrq);
		जाओ out;
	पूर्ण

	अगर (ibmvnic_xmit_workarounds(skb, netdev)) अणु
		tx_dropped++;
		tx_send_failed++;
		ret = NETDEV_TX_OK;
		ibmvnic_tx_scrq_flush(adapter, tx_scrq);
		जाओ out;
	पूर्ण
	अगर (skb_is_gso(skb))
		tx_pool = &adapter->tso_pool[queue_num];
	अन्यथा
		tx_pool = &adapter->tx_pool[queue_num];

	index = tx_pool->मुक्त_map[tx_pool->consumer_index];

	अगर (index == IBMVNIC_INVALID_MAP) अणु
		dev_kमुक्त_skb_any(skb);
		tx_send_failed++;
		tx_dropped++;
		ret = NETDEV_TX_OK;
		ibmvnic_tx_scrq_flush(adapter, tx_scrq);
		जाओ out;
	पूर्ण

	tx_pool->मुक्त_map[tx_pool->consumer_index] = IBMVNIC_INVALID_MAP;

	offset = index * tx_pool->buf_size;
	dst = tx_pool->दीर्घ_term_buff.buff + offset;
	स_रखो(dst, 0, tx_pool->buf_size);
	data_dma_addr = tx_pool->दीर्घ_term_buff.addr + offset;

	अगर (skb_shinfo(skb)->nr_frags) अणु
		पूर्णांक cur, i;

		/* Copy the head */
		skb_copy_from_linear_data(skb, dst, skb_headlen(skb));
		cur = skb_headlen(skb);

		/* Copy the frags */
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			स_नकल(dst + cur, skb_frag_address(frag),
			       skb_frag_size(frag));
			cur += skb_frag_size(frag);
		पूर्ण
	पूर्ण अन्यथा अणु
		skb_copy_from_linear_data(skb, dst, skb->len);
	पूर्ण

	/* post changes to दीर्घ_term_buff *dst beक्रमe VIOS accessing it */
	dma_wmb();

	tx_pool->consumer_index =
	    (tx_pool->consumer_index + 1) % tx_pool->num_buffers;

	tx_buff = &tx_pool->tx_buff[index];
	tx_buff->skb = skb;
	tx_buff->index = index;
	tx_buff->pool_index = queue_num;

	स_रखो(&tx_crq, 0, माप(tx_crq));
	tx_crq.v1.first = IBMVNIC_CRQ_CMD;
	tx_crq.v1.type = IBMVNIC_TX_DESC;
	tx_crq.v1.n_crq_elem = 1;
	tx_crq.v1.n_sge = 1;
	tx_crq.v1.flags1 = IBMVNIC_TX_COMP_NEEDED;

	अगर (skb_is_gso(skb))
		tx_crq.v1.correlator =
			cpu_to_be32(index | IBMVNIC_TSO_POOL_MASK);
	अन्यथा
		tx_crq.v1.correlator = cpu_to_be32(index);
	tx_crq.v1.dma_reg = cpu_to_be16(tx_pool->दीर्घ_term_buff.map_id);
	tx_crq.v1.sge_len = cpu_to_be32(skb->len);
	tx_crq.v1.ioba = cpu_to_be64(data_dma_addr);

	अगर (adapter->vlan_header_insertion && skb_vlan_tag_present(skb)) अणु
		tx_crq.v1.flags2 |= IBMVNIC_TX_VLAN_INSERT;
		tx_crq.v1.vlan_id = cpu_to_be16(skb->vlan_tci);
	पूर्ण

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		tx_crq.v1.flags1 |= IBMVNIC_TX_PROT_IPV4;
		proto = ip_hdr(skb)->protocol;
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		tx_crq.v1.flags1 |= IBMVNIC_TX_PROT_IPV6;
		proto = ipv6_hdr(skb)->nexthdr;
	पूर्ण

	अगर (proto == IPPROTO_TCP)
		tx_crq.v1.flags1 |= IBMVNIC_TX_PROT_TCP;
	अन्यथा अगर (proto == IPPROTO_UDP)
		tx_crq.v1.flags1 |= IBMVNIC_TX_PROT_UDP;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		tx_crq.v1.flags1 |= IBMVNIC_TX_CHKSUM_OFFLOAD;
		hdrs += 2;
	पूर्ण
	अगर (skb_is_gso(skb)) अणु
		tx_crq.v1.flags1 |= IBMVNIC_TX_LSO;
		tx_crq.v1.mss = cpu_to_be16(skb_shinfo(skb)->gso_size);
		hdrs += 2;
	पूर्ण

	अगर ((*hdrs >> 7) & 1)
		build_hdr_descs_arr(skb, indir_arr, &num_entries, *hdrs);

	tx_crq.v1.n_crq_elem = num_entries;
	tx_buff->num_entries = num_entries;
	/* flush buffer अगर current entry can not fit */
	अगर (num_entries + ind_bufp->index > IBMVNIC_MAX_IND_DESCS) अणु
		lpar_rc = ibmvnic_tx_scrq_flush(adapter, tx_scrq);
		अगर (lpar_rc != H_SUCCESS)
			जाओ tx_flush_err;
	पूर्ण

	indir_arr[0] = tx_crq;
	स_नकल(&ind_bufp->indir_arr[ind_bufp->index], &indir_arr[0],
	       num_entries * माप(काष्ठा ibmvnic_generic_scrq));
	ind_bufp->index += num_entries;
	अगर (__netdev_tx_sent_queue(txq, skb->len,
				   netdev_xmit_more() &&
				   ind_bufp->index < IBMVNIC_MAX_IND_DESCS)) अणु
		lpar_rc = ibmvnic_tx_scrq_flush(adapter, tx_scrq);
		अगर (lpar_rc != H_SUCCESS)
			जाओ tx_err;
	पूर्ण

	अगर (atomic_add_वापस(num_entries, &tx_scrq->used)
					>= adapter->req_tx_entries_per_subcrq) अणु
		netdev_dbg(netdev, "Stopping queue %d\n", queue_num);
		netअगर_stop_subqueue(netdev, queue_num);
	पूर्ण

	tx_packets++;
	tx_bytes += skb->len;
	txq->trans_start = jअगरfies;
	ret = NETDEV_TX_OK;
	जाओ out;

tx_flush_err:
	dev_kमुक्त_skb_any(skb);
	tx_buff->skb = शून्य;
	tx_pool->consumer_index = tx_pool->consumer_index == 0 ?
				  tx_pool->num_buffers - 1 :
				  tx_pool->consumer_index - 1;
	tx_dropped++;
tx_err:
	अगर (lpar_rc != H_CLOSED && lpar_rc != H_PARAMETER)
		dev_err_ratelimited(dev, "tx: send failed\n");

	अगर (lpar_rc == H_CLOSED || adapter->failover_pending) अणु
		/* Disable TX and report carrier off अगर queue is बंदd
		 * or pending failover.
		 * Firmware guarantees that a संकेत will be sent to the
		 * driver, triggering a reset or some other action.
		 */
		netअगर_tx_stop_all_queues(netdev);
		netअगर_carrier_off(netdev);
	पूर्ण
out:
	netdev->stats.tx_dropped += tx_dropped;
	netdev->stats.tx_bytes += tx_bytes;
	netdev->stats.tx_packets += tx_packets;
	adapter->tx_send_failed += tx_send_failed;
	adapter->tx_map_failed += tx_map_failed;
	adapter->tx_stats_buffers[queue_num].packets += tx_packets;
	adapter->tx_stats_buffers[queue_num].bytes += tx_bytes;
	adapter->tx_stats_buffers[queue_num].dropped_packets += tx_dropped;

	वापस ret;
पूर्ण

अटल व्योम ibmvnic_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा netdev_hw_addr *ha;
	जोड़ ibmvnic_crq crq;

	स_रखो(&crq, 0, माप(crq));
	crq.request_capability.first = IBMVNIC_CRQ_CMD;
	crq.request_capability.cmd = REQUEST_CAPABILITY;

	अगर (netdev->flags & IFF_PROMISC) अणु
		अगर (!adapter->promisc_supported)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_ALLMULTI) अणु
			/* Accept all multicast */
			स_रखो(&crq, 0, माप(crq));
			crq.multicast_ctrl.first = IBMVNIC_CRQ_CMD;
			crq.multicast_ctrl.cmd = MULTICAST_CTRL;
			crq.multicast_ctrl.flags = IBMVNIC_ENABLE_ALL;
			ibmvnic_send_crq(adapter, &crq);
		पूर्ण अन्यथा अगर (netdev_mc_empty(netdev)) अणु
			/* Reject all multicast */
			स_रखो(&crq, 0, माप(crq));
			crq.multicast_ctrl.first = IBMVNIC_CRQ_CMD;
			crq.multicast_ctrl.cmd = MULTICAST_CTRL;
			crq.multicast_ctrl.flags = IBMVNIC_DISABLE_ALL;
			ibmvnic_send_crq(adapter, &crq);
		पूर्ण अन्यथा अणु
			/* Accept one or more multicast(s) */
			netdev_क्रम_each_mc_addr(ha, netdev) अणु
				स_रखो(&crq, 0, माप(crq));
				crq.multicast_ctrl.first = IBMVNIC_CRQ_CMD;
				crq.multicast_ctrl.cmd = MULTICAST_CTRL;
				crq.multicast_ctrl.flags = IBMVNIC_ENABLE_MC;
				ether_addr_copy(&crq.multicast_ctrl.mac_addr[0],
						ha->addr);
				ibmvnic_send_crq(adapter, &crq);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __ibmvnic_set_mac(काष्ठा net_device *netdev, u8 *dev_addr)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	जोड़ ibmvnic_crq crq;
	पूर्णांक rc;

	अगर (!is_valid_ether_addr(dev_addr)) अणु
		rc = -EADDRNOTAVAIL;
		जाओ err;
	पूर्ण

	स_रखो(&crq, 0, माप(crq));
	crq.change_mac_addr.first = IBMVNIC_CRQ_CMD;
	crq.change_mac_addr.cmd = CHANGE_MAC_ADDR;
	ether_addr_copy(&crq.change_mac_addr.mac_addr[0], dev_addr);

	mutex_lock(&adapter->fw_lock);
	adapter->fw_करोne_rc = 0;
	reinit_completion(&adapter->fw_करोne);

	rc = ibmvnic_send_crq(adapter, &crq);
	अगर (rc) अणु
		rc = -EIO;
		mutex_unlock(&adapter->fw_lock);
		जाओ err;
	पूर्ण

	rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->fw_करोne, 10000);
	/* netdev->dev_addr is changed in handle_change_mac_rsp function */
	अगर (rc || adapter->fw_करोne_rc) अणु
		rc = -EIO;
		mutex_unlock(&adapter->fw_lock);
		जाओ err;
	पूर्ण
	mutex_unlock(&adapter->fw_lock);
	वापस 0;
err:
	ether_addr_copy(adapter->mac_addr, netdev->dev_addr);
	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक rc;

	rc = 0;
	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ether_addr_copy(adapter->mac_addr, addr->sa_data);
	अगर (adapter->state != VNIC_PROBED)
		rc = __ibmvnic_set_mac(netdev, addr->sa_data);

	वापस rc;
पूर्ण

अटल स्थिर अक्षर *reset_reason_to_string(क्रमागत ibmvnic_reset_reason reason)
अणु
	चयन (reason) अणु
	हाल VNIC_RESET_FAILOVER:
		वापस "FAILOVER";
	हाल VNIC_RESET_MOBILITY:
		वापस "MOBILITY";
	हाल VNIC_RESET_FATAL:
		वापस "FATAL";
	हाल VNIC_RESET_NON_FATAL:
		वापस "NON_FATAL";
	हाल VNIC_RESET_TIMEOUT:
		वापस "TIMEOUT";
	हाल VNIC_RESET_CHANGE_PARAM:
		वापस "CHANGE_PARAM";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

/*
 * करो_reset वापसs zero अगर we are able to keep processing reset events, or
 * non-zero अगर we hit a fatal error and must halt.
 */
अटल पूर्णांक करो_reset(काष्ठा ibmvnic_adapter *adapter,
		    काष्ठा ibmvnic_rwi *rwi, u32 reset_state)
अणु
	u64 old_num_rx_queues, old_num_tx_queues;
	u64 old_num_rx_slots, old_num_tx_slots;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक rc;

	netdev_dbg(adapter->netdev,
		   "[S:%s FOP:%d] Reset reason: %s, reset_state: %s\n",
		   adapter_state_to_string(adapter->state),
		   adapter->failover_pending,
		   reset_reason_to_string(rwi->reset_reason),
		   adapter_state_to_string(reset_state));

	adapter->reset_reason = rwi->reset_reason;
	/* requestor of VNIC_RESET_CHANGE_PARAM alपढ़ोy has the rtnl lock */
	अगर (!(adapter->reset_reason == VNIC_RESET_CHANGE_PARAM))
		rtnl_lock();

	/* Now that we have the rtnl lock, clear any pending failover.
	 * This will ensure ibmvnic_खोलो() has either completed or will
	 * block until failover is complete.
	 */
	अगर (rwi->reset_reason == VNIC_RESET_FAILOVER)
		adapter->failover_pending = false;

	/* पढ़ो the state and check (again) after getting rtnl */
	reset_state = adapter->state;

	अगर (reset_state == VNIC_REMOVING || reset_state == VNIC_REMOVED) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	netअगर_carrier_off(netdev);

	old_num_rx_queues = adapter->req_rx_queues;
	old_num_tx_queues = adapter->req_tx_queues;
	old_num_rx_slots = adapter->req_rx_add_entries_per_subcrq;
	old_num_tx_slots = adapter->req_tx_entries_per_subcrq;

	ibmvnic_cleanup(netdev);

	अगर (reset_state == VNIC_OPEN &&
	    adapter->reset_reason != VNIC_RESET_MOBILITY &&
	    adapter->reset_reason != VNIC_RESET_FAILOVER) अणु
		अगर (adapter->reset_reason == VNIC_RESET_CHANGE_PARAM) अणु
			rc = __ibmvnic_बंद(netdev);
			अगर (rc)
				जाओ out;
		पूर्ण अन्यथा अणु
			adapter->state = VNIC_CLOSING;

			/* Release the RTNL lock beक्रमe link state change and
			 * re-acquire after the link state change to allow
			 * linkwatch_event to grab the RTNL lock and run during
			 * a reset.
			 */
			rtnl_unlock();
			rc = set_link_state(adapter, IBMVNIC_LOGICAL_LNK_DN);
			rtnl_lock();
			अगर (rc)
				जाओ out;

			अगर (adapter->state == VNIC_OPEN) अणु
				/* When we dropped rtnl, ibmvnic_खोलो() got
				 * it and noticed that we are resetting and
				 * set the adapter state to OPEN. Update our
				 * new "target" state, and resume the reset
				 * from VNIC_CLOSING state.
				 */
				netdev_dbg(netdev,
					   "Open changed state from %s, updating.\n",
					   adapter_state_to_string(reset_state));
				reset_state = VNIC_OPEN;
				adapter->state = VNIC_CLOSING;
			पूर्ण

			अगर (adapter->state != VNIC_CLOSING) अणु
				/* If someone अन्यथा changed the adapter state
				 * when we dropped the rtnl, fail the reset
				 */
				rc = -1;
				जाओ out;
			पूर्ण
			adapter->state = VNIC_CLOSED;
		पूर्ण
	पूर्ण

	अगर (adapter->reset_reason == VNIC_RESET_CHANGE_PARAM) अणु
		release_resources(adapter);
		release_sub_crqs(adapter, 1);
		release_crq_queue(adapter);
	पूर्ण

	अगर (adapter->reset_reason != VNIC_RESET_NON_FATAL) अणु
		/* हटाओ the बंदd state so when we call खोलो it appears
		 * we are coming from the probed state.
		 */
		adapter->state = VNIC_PROBED;

		अगर (adapter->reset_reason == VNIC_RESET_CHANGE_PARAM) अणु
			rc = init_crq_queue(adapter);
		पूर्ण अन्यथा अगर (adapter->reset_reason == VNIC_RESET_MOBILITY) अणु
			rc = ibmvnic_reenable_crq_queue(adapter);
			release_sub_crqs(adapter, 1);
		पूर्ण अन्यथा अणु
			rc = ibmvnic_reset_crq(adapter);
			अगर (rc == H_CLOSED || rc == H_SUCCESS) अणु
				rc = vio_enable_पूर्णांकerrupts(adapter->vdev);
				अगर (rc)
					netdev_err(adapter->netdev,
						   "Reset failed to enable interrupts. rc=%d\n",
						   rc);
			पूर्ण
		पूर्ण

		अगर (rc) अणु
			netdev_err(adapter->netdev,
				   "Reset couldn't initialize crq. rc=%d\n", rc);
			जाओ out;
		पूर्ण

		rc = ibmvnic_reset_init(adapter, true);
		अगर (rc) अणु
			rc = IBMVNIC_INIT_FAILED;
			जाओ out;
		पूर्ण

		/* If the adapter was in PROBE state prior to the reset,
		 * निकास here.
		 */
		अगर (reset_state == VNIC_PROBED) अणु
			rc = 0;
			जाओ out;
		पूर्ण

		rc = ibmvnic_login(netdev);
		अगर (rc)
			जाओ out;

		अगर (adapter->reset_reason == VNIC_RESET_CHANGE_PARAM) अणु
			rc = init_resources(adapter);
			अगर (rc)
				जाओ out;
		पूर्ण अन्यथा अगर (adapter->req_rx_queues != old_num_rx_queues ||
		    adapter->req_tx_queues != old_num_tx_queues ||
		    adapter->req_rx_add_entries_per_subcrq !=
		    old_num_rx_slots ||
		    adapter->req_tx_entries_per_subcrq !=
		    old_num_tx_slots ||
		    !adapter->rx_pool ||
		    !adapter->tso_pool ||
		    !adapter->tx_pool) अणु
			release_rx_pools(adapter);
			release_tx_pools(adapter);
			release_napi(adapter);
			release_vpd_data(adapter);

			rc = init_resources(adapter);
			अगर (rc)
				जाओ out;

		पूर्ण अन्यथा अणु
			rc = reset_tx_pools(adapter);
			अगर (rc) अणु
				netdev_dbg(adapter->netdev, "reset tx pools failed (%d)\n",
					   rc);
				जाओ out;
			पूर्ण

			rc = reset_rx_pools(adapter);
			अगर (rc) अणु
				netdev_dbg(adapter->netdev, "reset rx pools failed (%d)\n",
					   rc);
				जाओ out;
			पूर्ण
		पूर्ण
		ibmvnic_disable_irqs(adapter);
	पूर्ण
	adapter->state = VNIC_CLOSED;

	अगर (reset_state == VNIC_CLOSED) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	rc = __ibmvnic_खोलो(netdev);
	अगर (rc) अणु
		rc = IBMVNIC_OPEN_FAILED;
		जाओ out;
	पूर्ण

	/* refresh device's multicast list */
	ibmvnic_set_multi(netdev);

	अगर (adapter->reset_reason == VNIC_RESET_FAILOVER ||
	    adapter->reset_reason == VNIC_RESET_MOBILITY)
		__netdev_notअगरy_peers(netdev);

	rc = 0;

out:
	/* restore the adapter state अगर reset failed */
	अगर (rc)
		adapter->state = reset_state;
	/* requestor of VNIC_RESET_CHANGE_PARAM should still hold the rtnl lock */
	अगर (!(adapter->reset_reason == VNIC_RESET_CHANGE_PARAM))
		rtnl_unlock();

	netdev_dbg(adapter->netdev, "[S:%s FOP:%d] Reset done, rc %d\n",
		   adapter_state_to_string(adapter->state),
		   adapter->failover_pending, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक करो_hard_reset(काष्ठा ibmvnic_adapter *adapter,
			 काष्ठा ibmvnic_rwi *rwi, u32 reset_state)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक rc;

	netdev_dbg(adapter->netdev, "Hard resetting driver (%s)\n",
		   reset_reason_to_string(rwi->reset_reason));

	/* पढ़ो the state and check (again) after getting rtnl */
	reset_state = adapter->state;

	अगर (reset_state == VNIC_REMOVING || reset_state == VNIC_REMOVED) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	netअगर_carrier_off(netdev);
	adapter->reset_reason = rwi->reset_reason;

	ibmvnic_cleanup(netdev);
	release_resources(adapter);
	release_sub_crqs(adapter, 0);
	release_crq_queue(adapter);

	/* हटाओ the बंदd state so when we call खोलो it appears
	 * we are coming from the probed state.
	 */
	adapter->state = VNIC_PROBED;

	reinit_completion(&adapter->init_करोne);
	rc = init_crq_queue(adapter);
	अगर (rc) अणु
		netdev_err(adapter->netdev,
			   "Couldn't initialize crq. rc=%d\n", rc);
		जाओ out;
	पूर्ण

	rc = ibmvnic_reset_init(adapter, false);
	अगर (rc)
		जाओ out;

	/* If the adapter was in PROBE state prior to the reset,
	 * निकास here.
	 */
	अगर (reset_state == VNIC_PROBED)
		जाओ out;

	rc = ibmvnic_login(netdev);
	अगर (rc)
		जाओ out;

	rc = init_resources(adapter);
	अगर (rc)
		जाओ out;

	ibmvnic_disable_irqs(adapter);
	adapter->state = VNIC_CLOSED;

	अगर (reset_state == VNIC_CLOSED)
		जाओ out;

	rc = __ibmvnic_खोलो(netdev);
	अगर (rc) अणु
		rc = IBMVNIC_OPEN_FAILED;
		जाओ out;
	पूर्ण

	__netdev_notअगरy_peers(netdev);
out:
	/* restore adapter state अगर reset failed */
	अगर (rc)
		adapter->state = reset_state;
	netdev_dbg(adapter->netdev, "[S:%s FOP:%d] Hard reset done, rc %d\n",
		   adapter_state_to_string(adapter->state),
		   adapter->failover_pending, rc);
	वापस rc;
पूर्ण

अटल काष्ठा ibmvnic_rwi *get_next_rwi(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_rwi *rwi;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->rwi_lock, flags);

	अगर (!list_empty(&adapter->rwi_list)) अणु
		rwi = list_first_entry(&adapter->rwi_list, काष्ठा ibmvnic_rwi,
				       list);
		list_del(&rwi->list);
	पूर्ण अन्यथा अणु
		rwi = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&adapter->rwi_lock, flags);
	वापस rwi;
पूर्ण

अटल व्योम __ibmvnic_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ibmvnic_rwi *rwi;
	काष्ठा ibmvnic_adapter *adapter;
	bool saved_state = false;
	अचिन्हित दीर्घ flags;
	u32 reset_state;
	पूर्णांक rc = 0;

	adapter = container_of(work, काष्ठा ibmvnic_adapter, ibmvnic_reset);

	अगर (test_and_set_bit_lock(0, &adapter->resetting)) अणु
		queue_delayed_work(प्रणाली_दीर्घ_wq,
				   &adapter->ibmvnic_delayed_reset,
				   IBMVNIC_RESET_DELAY);
		वापस;
	पूर्ण

	rwi = get_next_rwi(adapter);
	जबतक (rwi) अणु
		spin_lock_irqsave(&adapter->state_lock, flags);

		अगर (adapter->state == VNIC_REMOVING ||
		    adapter->state == VNIC_REMOVED) अणु
			spin_unlock_irqrestore(&adapter->state_lock, flags);
			kमुक्त(rwi);
			rc = EBUSY;
			अवरोध;
		पूर्ण

		अगर (!saved_state) अणु
			reset_state = adapter->state;
			saved_state = true;
		पूर्ण
		spin_unlock_irqrestore(&adapter->state_lock, flags);

		अगर (adapter->क्रमce_reset_recovery) अणु
			/* Since we are करोing a hard reset now, clear the
			 * failover_pending flag so we करोn't ignore any
			 * future MOBILITY or other resets.
			 */
			adapter->failover_pending = false;

			/* Transport event occurred during previous reset */
			अगर (adapter->रुको_क्रम_reset) अणु
				/* Previous was CHANGE_PARAM; caller locked */
				adapter->क्रमce_reset_recovery = false;
				rc = करो_hard_reset(adapter, rwi, reset_state);
			पूर्ण अन्यथा अणु
				rtnl_lock();
				adapter->क्रमce_reset_recovery = false;
				rc = करो_hard_reset(adapter, rwi, reset_state);
				rtnl_unlock();
			पूर्ण
			अगर (rc) अणु
				/* give backing device समय to settle करोwn */
				netdev_dbg(adapter->netdev,
					   "[S:%s] Hard reset failed, waiting 60 secs\n",
					   adapter_state_to_string(adapter->state));
				set_current_state(TASK_UNINTERRUPTIBLE);
				schedule_समयout(60 * HZ);
			पूर्ण
		पूर्ण अन्यथा अणु
			rc = करो_reset(adapter, rwi, reset_state);
		पूर्ण
		kमुक्त(rwi);
		adapter->last_reset_समय = jअगरfies;

		अगर (rc)
			netdev_dbg(adapter->netdev, "Reset failed, rc=%d\n", rc);

		rwi = get_next_rwi(adapter);

		अगर (rwi && (rwi->reset_reason == VNIC_RESET_FAILOVER ||
			    rwi->reset_reason == VNIC_RESET_MOBILITY))
			adapter->क्रमce_reset_recovery = true;
	पूर्ण

	अगर (adapter->रुको_क्रम_reset) अणु
		adapter->reset_करोne_rc = rc;
		complete(&adapter->reset_करोne);
	पूर्ण

	clear_bit_unlock(0, &adapter->resetting);

	netdev_dbg(adapter->netdev,
		   "[S:%s FRR:%d WFR:%d] Done processing resets\n",
		   adapter_state_to_string(adapter->state),
		   adapter->क्रमce_reset_recovery,
		   adapter->रुको_क्रम_reset);
पूर्ण

अटल व्योम __ibmvnic_delayed_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ibmvnic_adapter *adapter;

	adapter = container_of(work, काष्ठा ibmvnic_adapter,
			       ibmvnic_delayed_reset.work);
	__ibmvnic_reset(&adapter->ibmvnic_reset);
पूर्ण

अटल पूर्णांक ibmvnic_reset(काष्ठा ibmvnic_adapter *adapter,
			 क्रमागत ibmvnic_reset_reason reason)
अणु
	काष्ठा list_head *entry, *पंचांगp_entry;
	काष्ठा ibmvnic_rwi *rwi, *पंचांगp;
	काष्ठा net_device *netdev = adapter->netdev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&adapter->rwi_lock, flags);

	/* If failover is pending करोn't schedule any other reset.
	 * Instead let the failover complete. If there is alपढ़ोy a
	 * a failover reset scheduled, we will detect and drop the
	 * duplicate reset when walking the ->rwi_list below.
	 */
	अगर (adapter->state == VNIC_REMOVING ||
	    adapter->state == VNIC_REMOVED ||
	    (adapter->failover_pending && reason != VNIC_RESET_FAILOVER)) अणु
		ret = EBUSY;
		netdev_dbg(netdev, "Adapter removing or pending failover, skipping reset\n");
		जाओ err;
	पूर्ण

	अगर (adapter->state == VNIC_PROBING) अणु
		netdev_warn(netdev, "Adapter reset during probe\n");
		adapter->init_करोne_rc = EAGAIN;
		ret = EAGAIN;
		जाओ err;
	पूर्ण

	list_क्रम_each(entry, &adapter->rwi_list) अणु
		पंचांगp = list_entry(entry, काष्ठा ibmvnic_rwi, list);
		अगर (पंचांगp->reset_reason == reason) अणु
			netdev_dbg(netdev, "Skipping matching reset, reason=%s\n",
				   reset_reason_to_string(reason));
			ret = EBUSY;
			जाओ err;
		पूर्ण
	पूर्ण

	rwi = kzalloc(माप(*rwi), GFP_ATOMIC);
	अगर (!rwi) अणु
		ret = ENOMEM;
		जाओ err;
	पूर्ण
	/* अगर we just received a transport event,
	 * flush reset queue and process this reset
	 */
	अगर (adapter->क्रमce_reset_recovery && !list_empty(&adapter->rwi_list)) अणु
		list_क्रम_each_safe(entry, पंचांगp_entry, &adapter->rwi_list)
			list_del(entry);
	पूर्ण
	rwi->reset_reason = reason;
	list_add_tail(&rwi->list, &adapter->rwi_list);
	netdev_dbg(adapter->netdev, "Scheduling reset (reason %s)\n",
		   reset_reason_to_string(reason));
	queue_work(प्रणाली_दीर्घ_wq, &adapter->ibmvnic_reset);

	ret = 0;
err:
	/* ibmvnic_बंद() below can block, so drop the lock first */
	spin_unlock_irqrestore(&adapter->rwi_lock, flags);

	अगर (ret == ENOMEM)
		ibmvnic_बंद(netdev);

	वापस -ret;
पूर्ण

अटल व्योम ibmvnic_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(dev);

	अगर (test_bit(0, &adapter->resetting)) अणु
		netdev_err(adapter->netdev,
			   "Adapter is resetting, skip timeout reset\n");
		वापस;
	पूर्ण
	/* No queuing up reset until at least 5 seconds (शेष watchकरोg val)
	 * after last reset
	 */
	अगर (समय_beक्रमe(jअगरfies, (adapter->last_reset_समय + dev->watchकरोg_समयo))) अणु
		netdev_dbg(dev, "Not yet time to tx timeout.\n");
		वापस;
	पूर्ण
	ibmvnic_reset(adapter, VNIC_RESET_TIMEOUT);
पूर्ण

अटल व्योम हटाओ_buff_from_pool(काष्ठा ibmvnic_adapter *adapter,
				  काष्ठा ibmvnic_rx_buff *rx_buff)
अणु
	काष्ठा ibmvnic_rx_pool *pool = &adapter->rx_pool[rx_buff->pool_index];

	rx_buff->skb = शून्य;

	pool->मुक्त_map[pool->next_alloc] = (पूर्णांक)(rx_buff - pool->rx_buff);
	pool->next_alloc = (pool->next_alloc + 1) % pool->size;

	atomic_dec(&pool->available);
पूर्ण

अटल पूर्णांक ibmvnic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ibmvnic_sub_crq_queue *rx_scrq;
	काष्ठा ibmvnic_adapter *adapter;
	काष्ठा net_device *netdev;
	पूर्णांक frames_processed;
	पूर्णांक scrq_num;

	netdev = napi->dev;
	adapter = netdev_priv(netdev);
	scrq_num = (पूर्णांक)(napi - adapter->napi);
	frames_processed = 0;
	rx_scrq = adapter->rx_scrq[scrq_num];

restart_poll:
	जबतक (frames_processed < budget) अणु
		काष्ठा sk_buff *skb;
		काष्ठा ibmvnic_rx_buff *rx_buff;
		जोड़ sub_crq *next;
		u32 length;
		u16 offset;
		u8 flags = 0;

		अगर (unlikely(test_bit(0, &adapter->resetting) &&
			     adapter->reset_reason != VNIC_RESET_NON_FATAL)) अणु
			enable_scrq_irq(adapter, rx_scrq);
			napi_complete_करोne(napi, frames_processed);
			वापस frames_processed;
		पूर्ण

		अगर (!pending_scrq(adapter, rx_scrq))
			अवरोध;
		next = ibmvnic_next_scrq(adapter, rx_scrq);
		rx_buff = (काष्ठा ibmvnic_rx_buff *)
			  be64_to_cpu(next->rx_comp.correlator);
		/* करो error checking */
		अगर (next->rx_comp.rc) अणु
			netdev_dbg(netdev, "rx buffer returned with rc %x\n",
				   be16_to_cpu(next->rx_comp.rc));
			/* मुक्त the entry */
			next->rx_comp.first = 0;
			dev_kमुक्त_skb_any(rx_buff->skb);
			हटाओ_buff_from_pool(adapter, rx_buff);
			जारी;
		पूर्ण अन्यथा अगर (!rx_buff->skb) अणु
			/* मुक्त the entry */
			next->rx_comp.first = 0;
			हटाओ_buff_from_pool(adapter, rx_buff);
			जारी;
		पूर्ण

		length = be32_to_cpu(next->rx_comp.len);
		offset = be16_to_cpu(next->rx_comp.off_frame_data);
		flags = next->rx_comp.flags;
		skb = rx_buff->skb;
		/* load दीर्घ_term_buff beक्रमe copying to skb */
		dma_rmb();
		skb_copy_to_linear_data(skb, rx_buff->data + offset,
					length);

		/* VLAN Header has been stripped by the प्रणाली firmware and
		 * needs to be inserted by the driver
		 */
		अगर (adapter->rx_vlan_header_insertion &&
		    (flags & IBMVNIC_VLAN_STRIPPED))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       ntohs(next->rx_comp.vlan_tci));

		/* मुक्त the entry */
		next->rx_comp.first = 0;
		हटाओ_buff_from_pool(adapter, rx_buff);

		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, scrq_num);

		अगर (flags & IBMVNIC_IP_CHKSUM_GOOD &&
		    flags & IBMVNIC_TCP_UDP_CHKSUM_GOOD) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण

		length = skb->len;
		napi_gro_receive(napi, skb); /* send it up */
		netdev->stats.rx_packets++;
		netdev->stats.rx_bytes += length;
		adapter->rx_stats_buffers[scrq_num].packets++;
		adapter->rx_stats_buffers[scrq_num].bytes += length;
		frames_processed++;
	पूर्ण

	अगर (adapter->state != VNIC_CLOSING &&
	    ((atomic_पढ़ो(&adapter->rx_pool[scrq_num].available) <
	      adapter->req_rx_add_entries_per_subcrq / 2) ||
	      frames_processed < budget))
		replenish_rx_pool(adapter, &adapter->rx_pool[scrq_num]);
	अगर (frames_processed < budget) अणु
		अगर (napi_complete_करोne(napi, frames_processed)) अणु
			enable_scrq_irq(adapter, rx_scrq);
			अगर (pending_scrq(adapter, rx_scrq)) अणु
				अगर (napi_reschedule(napi)) अणु
					disable_scrq_irq(adapter, rx_scrq);
					जाओ restart_poll;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस frames_processed;
पूर्ण

अटल पूर्णांक रुको_क्रम_reset(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक rc, ret;

	adapter->fallback.mtu = adapter->req_mtu;
	adapter->fallback.rx_queues = adapter->req_rx_queues;
	adapter->fallback.tx_queues = adapter->req_tx_queues;
	adapter->fallback.rx_entries = adapter->req_rx_add_entries_per_subcrq;
	adapter->fallback.tx_entries = adapter->req_tx_entries_per_subcrq;

	reinit_completion(&adapter->reset_करोne);
	adapter->रुको_क्रम_reset = true;
	rc = ibmvnic_reset(adapter, VNIC_RESET_CHANGE_PARAM);

	अगर (rc) अणु
		ret = rc;
		जाओ out;
	पूर्ण
	rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->reset_करोne, 60000);
	अगर (rc) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = 0;
	अगर (adapter->reset_करोne_rc) अणु
		ret = -EIO;
		adapter->desired.mtu = adapter->fallback.mtu;
		adapter->desired.rx_queues = adapter->fallback.rx_queues;
		adapter->desired.tx_queues = adapter->fallback.tx_queues;
		adapter->desired.rx_entries = adapter->fallback.rx_entries;
		adapter->desired.tx_entries = adapter->fallback.tx_entries;

		reinit_completion(&adapter->reset_करोne);
		adapter->रुको_क्रम_reset = true;
		rc = ibmvnic_reset(adapter, VNIC_RESET_CHANGE_PARAM);
		अगर (rc) अणु
			ret = rc;
			जाओ out;
		पूर्ण
		rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->reset_करोne,
						 60000);
		अगर (rc) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	adapter->रुको_क्रम_reset = false;

	वापस ret;
पूर्ण

अटल पूर्णांक ibmvnic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	adapter->desired.mtu = new_mtu + ETH_HLEN;

	वापस रुको_क्रम_reset(adapter);
पूर्ण

अटल netdev_features_t ibmvnic_features_check(काष्ठा sk_buff *skb,
						काष्ठा net_device *dev,
						netdev_features_t features)
अणु
	/* Some backing hardware adapters can not
	 * handle packets with a MSS less than 224
	 * or with only one segment.
	 */
	अगर (skb_is_gso(skb)) अणु
		अगर (skb_shinfo(skb)->gso_size < 224 ||
		    skb_shinfo(skb)->gso_segs == 1)
			features &= ~NETIF_F_GSO_MASK;
	पूर्ण

	वापस features;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ibmvnic_netdev_ops = अणु
	.nकरो_खोलो		= ibmvnic_खोलो,
	.nकरो_stop		= ibmvnic_बंद,
	.nकरो_start_xmit		= ibmvnic_xmit,
	.nकरो_set_rx_mode	= ibmvnic_set_multi,
	.nकरो_set_mac_address	= ibmvnic_set_mac,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_tx_समयout		= ibmvnic_tx_समयout,
	.nकरो_change_mtu		= ibmvnic_change_mtu,
	.nकरो_features_check     = ibmvnic_features_check,
पूर्ण;

/* ethtool functions */

अटल पूर्णांक ibmvnic_get_link_ksettings(काष्ठा net_device *netdev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc;

	rc = send_query_phys_parms(adapter);
	अगर (rc) अणु
		adapter->speed = SPEED_UNKNOWN;
		adapter->duplex = DUPLEX_UNKNOWN;
	पूर्ण
	cmd->base.speed = adapter->speed;
	cmd->base.duplex = adapter->duplex;
	cmd->base.port = PORT_FIBRE;
	cmd->base.phy_address = 0;
	cmd->base.स्वतःneg = AUTONEG_ENABLE;

	वापस 0;
पूर्ण

अटल व्योम ibmvnic_get_drvinfo(काष्ठा net_device *netdev,
				काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	strscpy(info->driver, ibmvnic_driver_name, माप(info->driver));
	strscpy(info->version, IBMVNIC_DRIVER_VERSION, माप(info->version));
	strscpy(info->fw_version, adapter->fw_version,
		माप(info->fw_version));
पूर्ण

अटल u32 ibmvnic_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम ibmvnic_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	adapter->msg_enable = data;
पूर्ण

अटल u32 ibmvnic_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	/* Don't need to send a query because we request a logical link up at
	 * init and then we रुको क्रम link state indications
	 */
	वापस adapter->logical_link_state;
पूर्ण

अटल व्योम ibmvnic_get_ringparam(काष्ठा net_device *netdev,
				  काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->priv_flags & IBMVNIC_USE_SERVER_MAXES) अणु
		ring->rx_max_pending = adapter->max_rx_add_entries_per_subcrq;
		ring->tx_max_pending = adapter->max_tx_entries_per_subcrq;
	पूर्ण अन्यथा अणु
		ring->rx_max_pending = IBMVNIC_MAX_QUEUE_SZ;
		ring->tx_max_pending = IBMVNIC_MAX_QUEUE_SZ;
	पूर्ण
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_pending = adapter->req_rx_add_entries_per_subcrq;
	ring->tx_pending = adapter->req_tx_entries_per_subcrq;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
पूर्ण

अटल पूर्णांक ibmvnic_set_ringparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret;

	ret = 0;
	adapter->desired.rx_entries = ring->rx_pending;
	adapter->desired.tx_entries = ring->tx_pending;

	ret = रुको_क्रम_reset(adapter);

	अगर (!ret &&
	    (adapter->req_rx_add_entries_per_subcrq != ring->rx_pending ||
	     adapter->req_tx_entries_per_subcrq != ring->tx_pending))
		netdev_info(netdev,
			    "Could not match full ringsize request. Requested: RX %d, TX %d; Allowed: RX %llu, TX %llu\n",
			    ring->rx_pending, ring->tx_pending,
			    adapter->req_rx_add_entries_per_subcrq,
			    adapter->req_tx_entries_per_subcrq);
	वापस ret;
पूर्ण

अटल व्योम ibmvnic_get_channels(काष्ठा net_device *netdev,
				 काष्ठा ethtool_channels *channels)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->priv_flags & IBMVNIC_USE_SERVER_MAXES) अणु
		channels->max_rx = adapter->max_rx_queues;
		channels->max_tx = adapter->max_tx_queues;
	पूर्ण अन्यथा अणु
		channels->max_rx = IBMVNIC_MAX_QUEUES;
		channels->max_tx = IBMVNIC_MAX_QUEUES;
	पूर्ण

	channels->max_other = 0;
	channels->max_combined = 0;
	channels->rx_count = adapter->req_rx_queues;
	channels->tx_count = adapter->req_tx_queues;
	channels->other_count = 0;
	channels->combined_count = 0;
पूर्ण

अटल पूर्णांक ibmvnic_set_channels(काष्ठा net_device *netdev,
				काष्ठा ethtool_channels *channels)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक ret;

	ret = 0;
	adapter->desired.rx_queues = channels->rx_count;
	adapter->desired.tx_queues = channels->tx_count;

	ret = रुको_क्रम_reset(adapter);

	अगर (!ret &&
	    (adapter->req_rx_queues != channels->rx_count ||
	     adapter->req_tx_queues != channels->tx_count))
		netdev_info(netdev,
			    "Could not match full channels request. Requested: RX %d, TX %d; Allowed: RX %llu, TX %llu\n",
			    channels->rx_count, channels->tx_count,
			    adapter->req_rx_queues, adapter->req_tx_queues);
	वापस ret;
पूर्ण

अटल व्योम ibmvnic_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(dev);
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(ibmvnic_stats);
				i++, data += ETH_GSTRING_LEN)
			स_नकल(data, ibmvnic_stats[i].name, ETH_GSTRING_LEN);

		क्रम (i = 0; i < adapter->req_tx_queues; i++) अणु
			snम_लिखो(data, ETH_GSTRING_LEN, "tx%d_packets", i);
			data += ETH_GSTRING_LEN;

			snम_लिखो(data, ETH_GSTRING_LEN, "tx%d_bytes", i);
			data += ETH_GSTRING_LEN;

			snम_लिखो(data, ETH_GSTRING_LEN,
				 "tx%d_dropped_packets", i);
			data += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
			snम_लिखो(data, ETH_GSTRING_LEN, "rx%d_packets", i);
			data += ETH_GSTRING_LEN;

			snम_लिखो(data, ETH_GSTRING_LEN, "rx%d_bytes", i);
			data += ETH_GSTRING_LEN;

			snम_लिखो(data, ETH_GSTRING_LEN, "rx%d_interrupts", i);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;

	हाल ETH_SS_PRIV_FLAGS:
		क्रम (i = 0; i < ARRAY_SIZE(ibmvnic_priv_flags); i++)
			म_नकल(data + i * ETH_GSTRING_LEN,
			       ibmvnic_priv_flags[i]);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ibmvnic_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ibmvnic_stats) +
		       adapter->req_tx_queues * NUM_TX_STATS +
		       adapter->req_rx_queues * NUM_RX_STATS;
	हाल ETH_SS_PRIV_FLAGS:
		वापस ARRAY_SIZE(ibmvnic_priv_flags);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम ibmvnic_get_ethtool_stats(काष्ठा net_device *dev,
				      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(dev);
	जोड़ ibmvnic_crq crq;
	पूर्णांक i, j;
	पूर्णांक rc;

	स_रखो(&crq, 0, माप(crq));
	crq.request_statistics.first = IBMVNIC_CRQ_CMD;
	crq.request_statistics.cmd = REQUEST_STATISTICS;
	crq.request_statistics.ioba = cpu_to_be32(adapter->stats_token);
	crq.request_statistics.len =
	    cpu_to_be32(माप(काष्ठा ibmvnic_statistics));

	/* Wait क्रम data to be written */
	reinit_completion(&adapter->stats_करोne);
	rc = ibmvnic_send_crq(adapter, &crq);
	अगर (rc)
		वापस;
	rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->stats_करोne, 10000);
	अगर (rc)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(ibmvnic_stats); i++)
		data[i] = be64_to_cpu(IBMVNIC_GET_STAT
				      (adapter, ibmvnic_stats[i].offset));

	क्रम (j = 0; j < adapter->req_tx_queues; j++) अणु
		data[i] = adapter->tx_stats_buffers[j].packets;
		i++;
		data[i] = adapter->tx_stats_buffers[j].bytes;
		i++;
		data[i] = adapter->tx_stats_buffers[j].dropped_packets;
		i++;
	पूर्ण

	क्रम (j = 0; j < adapter->req_rx_queues; j++) अणु
		data[i] = adapter->rx_stats_buffers[j].packets;
		i++;
		data[i] = adapter->rx_stats_buffers[j].bytes;
		i++;
		data[i] = adapter->rx_stats_buffers[j].पूर्णांकerrupts;
		i++;
	पूर्ण
पूर्ण

अटल u32 ibmvnic_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	वापस adapter->priv_flags;
पूर्ण

अटल पूर्णांक ibmvnic_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	bool which_maxes = !!(flags & IBMVNIC_USE_SERVER_MAXES);

	अगर (which_maxes)
		adapter->priv_flags |= IBMVNIC_USE_SERVER_MAXES;
	अन्यथा
		adapter->priv_flags &= ~IBMVNIC_USE_SERVER_MAXES;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ibmvnic_ethtool_ops = अणु
	.get_drvinfo		= ibmvnic_get_drvinfo,
	.get_msglevel		= ibmvnic_get_msglevel,
	.set_msglevel		= ibmvnic_set_msglevel,
	.get_link		= ibmvnic_get_link,
	.get_ringparam		= ibmvnic_get_ringparam,
	.set_ringparam		= ibmvnic_set_ringparam,
	.get_channels		= ibmvnic_get_channels,
	.set_channels		= ibmvnic_set_channels,
	.get_strings            = ibmvnic_get_strings,
	.get_sset_count         = ibmvnic_get_sset_count,
	.get_ethtool_stats	= ibmvnic_get_ethtool_stats,
	.get_link_ksettings	= ibmvnic_get_link_ksettings,
	.get_priv_flags		= ibmvnic_get_priv_flags,
	.set_priv_flags		= ibmvnic_set_priv_flags,
पूर्ण;

/* Routines क्रम managing CRQs/sCRQs  */

अटल पूर्णांक reset_one_sub_crq_queue(काष्ठा ibmvnic_adapter *adapter,
				   काष्ठा ibmvnic_sub_crq_queue *scrq)
अणु
	पूर्णांक rc;

	अगर (!scrq) अणु
		netdev_dbg(adapter->netdev, "Invalid scrq reset.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (scrq->irq) अणु
		मुक्त_irq(scrq->irq, scrq);
		irq_dispose_mapping(scrq->irq);
		scrq->irq = 0;
	पूर्ण

	अगर (scrq->msgs) अणु
		स_रखो(scrq->msgs, 0, 4 * PAGE_SIZE);
		atomic_set(&scrq->used, 0);
		scrq->cur = 0;
		scrq->ind_buf.index = 0;
	पूर्ण अन्यथा अणु
		netdev_dbg(adapter->netdev, "Invalid scrq reset\n");
		वापस -EINVAL;
	पूर्ण

	rc = h_reg_sub_crq(adapter->vdev->unit_address, scrq->msg_token,
			   4 * PAGE_SIZE, &scrq->crq_num, &scrq->hw_irq);
	वापस rc;
पूर्ण

अटल पूर्णांक reset_sub_crq_queues(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक i, rc;

	अगर (!adapter->tx_scrq || !adapter->rx_scrq)
		वापस -EINVAL;

	क्रम (i = 0; i < adapter->req_tx_queues; i++) अणु
		netdev_dbg(adapter->netdev, "Re-setting tx_scrq[%d]\n", i);
		rc = reset_one_sub_crq_queue(adapter, adapter->tx_scrq[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
		netdev_dbg(adapter->netdev, "Re-setting rx_scrq[%d]\n", i);
		rc = reset_one_sub_crq_queue(adapter, adapter->rx_scrq[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम release_sub_crq_queue(काष्ठा ibmvnic_adapter *adapter,
				  काष्ठा ibmvnic_sub_crq_queue *scrq,
				  bool करो_h_मुक्त)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	दीर्घ rc;

	netdev_dbg(adapter->netdev, "Releasing sub-CRQ\n");

	अगर (करो_h_मुक्त) अणु
		/* Close the sub-crqs */
		करो अणु
			rc = plpar_hcall_norets(H_FREE_SUB_CRQ,
						adapter->vdev->unit_address,
						scrq->crq_num);
		पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

		अगर (rc) अणु
			netdev_err(adapter->netdev,
				   "Failed to release sub-CRQ %16lx, rc = %ld\n",
				   scrq->crq_num, rc);
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(dev,
			  IBMVNIC_IND_ARR_SZ,
			  scrq->ind_buf.indir_arr,
			  scrq->ind_buf.indir_dma);

	dma_unmap_single(dev, scrq->msg_token, 4 * PAGE_SIZE,
			 DMA_BIसूचीECTIONAL);
	मुक्त_pages((अचिन्हित दीर्घ)scrq->msgs, 2);
	kमुक्त(scrq);
पूर्ण

अटल काष्ठा ibmvnic_sub_crq_queue *init_sub_crq_queue(काष्ठा ibmvnic_adapter
							*adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_sub_crq_queue *scrq;
	पूर्णांक rc;

	scrq = kzalloc(माप(*scrq), GFP_KERNEL);
	अगर (!scrq)
		वापस शून्य;

	scrq->msgs =
		(जोड़ sub_crq *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, 2);
	अगर (!scrq->msgs) अणु
		dev_warn(dev, "Couldn't allocate crq queue messages page\n");
		जाओ zero_page_failed;
	पूर्ण

	scrq->msg_token = dma_map_single(dev, scrq->msgs, 4 * PAGE_SIZE,
					 DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, scrq->msg_token)) अणु
		dev_warn(dev, "Couldn't map crq queue messages page\n");
		जाओ map_failed;
	पूर्ण

	rc = h_reg_sub_crq(adapter->vdev->unit_address, scrq->msg_token,
			   4 * PAGE_SIZE, &scrq->crq_num, &scrq->hw_irq);

	अगर (rc == H_RESOURCE)
		rc = ibmvnic_reset_crq(adapter);

	अगर (rc == H_CLOSED) अणु
		dev_warn(dev, "Partner adapter not ready, waiting.\n");
	पूर्ण अन्यथा अगर (rc) अणु
		dev_warn(dev, "Error %d registering sub-crq\n", rc);
		जाओ reg_failed;
	पूर्ण

	scrq->adapter = adapter;
	scrq->size = 4 * PAGE_SIZE / माप(*scrq->msgs);
	scrq->ind_buf.index = 0;

	scrq->ind_buf.indir_arr =
		dma_alloc_coherent(dev,
				   IBMVNIC_IND_ARR_SZ,
				   &scrq->ind_buf.indir_dma,
				   GFP_KERNEL);

	अगर (!scrq->ind_buf.indir_arr)
		जाओ indir_failed;

	spin_lock_init(&scrq->lock);

	netdev_dbg(adapter->netdev,
		   "sub-crq initialized, num %lx, hw_irq=%lx, irq=%x\n",
		   scrq->crq_num, scrq->hw_irq, scrq->irq);

	वापस scrq;

indir_failed:
	करो अणु
		rc = plpar_hcall_norets(H_FREE_SUB_CRQ,
					adapter->vdev->unit_address,
					scrq->crq_num);
	पूर्ण जबतक (rc == H_BUSY || rc == H_IS_LONG_BUSY(rc));
reg_failed:
	dma_unmap_single(dev, scrq->msg_token, 4 * PAGE_SIZE,
			 DMA_BIसूचीECTIONAL);
map_failed:
	मुक्त_pages((अचिन्हित दीर्घ)scrq->msgs, 2);
zero_page_failed:
	kमुक्त(scrq);

	वापस शून्य;
पूर्ण

अटल व्योम release_sub_crqs(काष्ठा ibmvnic_adapter *adapter, bool करो_h_मुक्त)
अणु
	पूर्णांक i;

	अगर (adapter->tx_scrq) अणु
		क्रम (i = 0; i < adapter->num_active_tx_scrqs; i++) अणु
			अगर (!adapter->tx_scrq[i])
				जारी;

			netdev_dbg(adapter->netdev, "Releasing tx_scrq[%d]\n",
				   i);
			अगर (adapter->tx_scrq[i]->irq) अणु
				मुक्त_irq(adapter->tx_scrq[i]->irq,
					 adapter->tx_scrq[i]);
				irq_dispose_mapping(adapter->tx_scrq[i]->irq);
				adapter->tx_scrq[i]->irq = 0;
			पूर्ण

			release_sub_crq_queue(adapter, adapter->tx_scrq[i],
					      करो_h_मुक्त);
		पूर्ण

		kमुक्त(adapter->tx_scrq);
		adapter->tx_scrq = शून्य;
		adapter->num_active_tx_scrqs = 0;
	पूर्ण

	अगर (adapter->rx_scrq) अणु
		क्रम (i = 0; i < adapter->num_active_rx_scrqs; i++) अणु
			अगर (!adapter->rx_scrq[i])
				जारी;

			netdev_dbg(adapter->netdev, "Releasing rx_scrq[%d]\n",
				   i);
			अगर (adapter->rx_scrq[i]->irq) अणु
				मुक्त_irq(adapter->rx_scrq[i]->irq,
					 adapter->rx_scrq[i]);
				irq_dispose_mapping(adapter->rx_scrq[i]->irq);
				adapter->rx_scrq[i]->irq = 0;
			पूर्ण

			release_sub_crq_queue(adapter, adapter->rx_scrq[i],
					      करो_h_मुक्त);
		पूर्ण

		kमुक्त(adapter->rx_scrq);
		adapter->rx_scrq = शून्य;
		adapter->num_active_rx_scrqs = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक disable_scrq_irq(काष्ठा ibmvnic_adapter *adapter,
			    काष्ठा ibmvnic_sub_crq_queue *scrq)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	अचिन्हित दीर्घ rc;

	rc = plpar_hcall_norets(H_VIOCTL, adapter->vdev->unit_address,
				H_DISABLE_VIO_INTERRUPT, scrq->hw_irq, 0, 0);
	अगर (rc)
		dev_err(dev, "Couldn't disable scrq irq 0x%lx. rc=%ld\n",
			scrq->hw_irq, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक enable_scrq_irq(काष्ठा ibmvnic_adapter *adapter,
			   काष्ठा ibmvnic_sub_crq_queue *scrq)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	अचिन्हित दीर्घ rc;

	अगर (scrq->hw_irq > 0x100000000ULL) अणु
		dev_err(dev, "bad hw_irq = %lx\n", scrq->hw_irq);
		वापस 1;
	पूर्ण

	अगर (test_bit(0, &adapter->resetting) &&
	    adapter->reset_reason == VNIC_RESET_MOBILITY) अणु
		u64 val = (0xff000000) | scrq->hw_irq;

		rc = plpar_hcall_norets(H_EOI, val);
		/* H_EOI would fail with rc = H_FUNCTION when running
		 * in XIVE mode which is expected, but not an error.
		 */
		अगर (rc && rc != H_FUNCTION)
			dev_err(dev, "H_EOI FAILED irq 0x%llx. rc=%ld\n",
				val, rc);
	पूर्ण

	rc = plpar_hcall_norets(H_VIOCTL, adapter->vdev->unit_address,
				H_ENABLE_VIO_INTERRUPT, scrq->hw_irq, 0, 0);
	अगर (rc)
		dev_err(dev, "Couldn't enable scrq irq 0x%lx. rc=%ld\n",
			scrq->hw_irq, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_complete_tx(काष्ठा ibmvnic_adapter *adapter,
			       काष्ठा ibmvnic_sub_crq_queue *scrq)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_tx_pool *tx_pool;
	काष्ठा ibmvnic_tx_buff *txbuff;
	काष्ठा netdev_queue *txq;
	जोड़ sub_crq *next;
	पूर्णांक index;
	पूर्णांक i;

restart_loop:
	जबतक (pending_scrq(adapter, scrq)) अणु
		अचिन्हित पूर्णांक pool = scrq->pool_index;
		पूर्णांक num_entries = 0;
		पूर्णांक total_bytes = 0;
		पूर्णांक num_packets = 0;

		next = ibmvnic_next_scrq(adapter, scrq);
		क्रम (i = 0; i < next->tx_comp.num_comps; i++) अणु
			index = be32_to_cpu(next->tx_comp.correlators[i]);
			अगर (index & IBMVNIC_TSO_POOL_MASK) अणु
				tx_pool = &adapter->tso_pool[pool];
				index &= ~IBMVNIC_TSO_POOL_MASK;
			पूर्ण अन्यथा अणु
				tx_pool = &adapter->tx_pool[pool];
			पूर्ण

			txbuff = &tx_pool->tx_buff[index];
			num_packets++;
			num_entries += txbuff->num_entries;
			अगर (txbuff->skb) अणु
				total_bytes += txbuff->skb->len;
				अगर (next->tx_comp.rcs[i]) अणु
					dev_err(dev, "tx error %x\n",
						next->tx_comp.rcs[i]);
					dev_kमुक्त_skb_irq(txbuff->skb);
				पूर्ण अन्यथा अणु
					dev_consume_skb_irq(txbuff->skb);
				पूर्ण
				txbuff->skb = शून्य;
			पूर्ण अन्यथा अणु
				netdev_warn(adapter->netdev,
					    "TX completion received with NULL socket buffer\n");
			पूर्ण
			tx_pool->मुक्त_map[tx_pool->producer_index] = index;
			tx_pool->producer_index =
				(tx_pool->producer_index + 1) %
					tx_pool->num_buffers;
		पूर्ण
		/* हटाओ tx_comp scrq*/
		next->tx_comp.first = 0;

		txq = netdev_get_tx_queue(adapter->netdev, scrq->pool_index);
		netdev_tx_completed_queue(txq, num_packets, total_bytes);

		अगर (atomic_sub_वापस(num_entries, &scrq->used) <=
		    (adapter->req_tx_entries_per_subcrq / 2) &&
		    __netअगर_subqueue_stopped(adapter->netdev,
					     scrq->pool_index)) अणु
			netअगर_wake_subqueue(adapter->netdev, scrq->pool_index);
			netdev_dbg(adapter->netdev, "Started queue %d\n",
				   scrq->pool_index);
		पूर्ण
	पूर्ण

	enable_scrq_irq(adapter, scrq);

	अगर (pending_scrq(adapter, scrq)) अणु
		disable_scrq_irq(adapter, scrq);
		जाओ restart_loop;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t ibmvnic_पूर्णांकerrupt_tx(पूर्णांक irq, व्योम *instance)
अणु
	काष्ठा ibmvnic_sub_crq_queue *scrq = instance;
	काष्ठा ibmvnic_adapter *adapter = scrq->adapter;

	disable_scrq_irq(adapter, scrq);
	ibmvnic_complete_tx(adapter, scrq);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ibmvnic_पूर्णांकerrupt_rx(पूर्णांक irq, व्योम *instance)
अणु
	काष्ठा ibmvnic_sub_crq_queue *scrq = instance;
	काष्ठा ibmvnic_adapter *adapter = scrq->adapter;

	/* When booting a kdump kernel we can hit pending पूर्णांकerrupts
	 * prior to completing driver initialization.
	 */
	अगर (unlikely(adapter->state != VNIC_OPEN))
		वापस IRQ_NONE;

	adapter->rx_stats_buffers[scrq->scrq_num].पूर्णांकerrupts++;

	अगर (napi_schedule_prep(&adapter->napi[scrq->scrq_num])) अणु
		disable_scrq_irq(adapter, scrq);
		__napi_schedule(&adapter->napi[scrq->scrq_num]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक init_sub_crq_irqs(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_sub_crq_queue *scrq;
	पूर्णांक i = 0, j = 0;
	पूर्णांक rc = 0;

	क्रम (i = 0; i < adapter->req_tx_queues; i++) अणु
		netdev_dbg(adapter->netdev, "Initializing tx_scrq[%d] irq\n",
			   i);
		scrq = adapter->tx_scrq[i];
		scrq->irq = irq_create_mapping(शून्य, scrq->hw_irq);

		अगर (!scrq->irq) अणु
			rc = -EINVAL;
			dev_err(dev, "Error mapping irq\n");
			जाओ req_tx_irq_failed;
		पूर्ण

		snम_लिखो(scrq->name, माप(scrq->name), "ibmvnic-%x-tx%d",
			 adapter->vdev->unit_address, i);
		rc = request_irq(scrq->irq, ibmvnic_पूर्णांकerrupt_tx,
				 0, scrq->name, scrq);

		अगर (rc) अणु
			dev_err(dev, "Couldn't register tx irq 0x%x. rc=%d\n",
				scrq->irq, rc);
			irq_dispose_mapping(scrq->irq);
			जाओ req_tx_irq_failed;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
		netdev_dbg(adapter->netdev, "Initializing rx_scrq[%d] irq\n",
			   i);
		scrq = adapter->rx_scrq[i];
		scrq->irq = irq_create_mapping(शून्य, scrq->hw_irq);
		अगर (!scrq->irq) अणु
			rc = -EINVAL;
			dev_err(dev, "Error mapping irq\n");
			जाओ req_rx_irq_failed;
		पूर्ण
		snम_लिखो(scrq->name, माप(scrq->name), "ibmvnic-%x-rx%d",
			 adapter->vdev->unit_address, i);
		rc = request_irq(scrq->irq, ibmvnic_पूर्णांकerrupt_rx,
				 0, scrq->name, scrq);
		अगर (rc) अणु
			dev_err(dev, "Couldn't register rx irq 0x%x. rc=%d\n",
				scrq->irq, rc);
			irq_dispose_mapping(scrq->irq);
			जाओ req_rx_irq_failed;
		पूर्ण
	पूर्ण
	वापस rc;

req_rx_irq_failed:
	क्रम (j = 0; j < i; j++) अणु
		मुक्त_irq(adapter->rx_scrq[j]->irq, adapter->rx_scrq[j]);
		irq_dispose_mapping(adapter->rx_scrq[j]->irq);
	पूर्ण
	i = adapter->req_tx_queues;
req_tx_irq_failed:
	क्रम (j = 0; j < i; j++) अणु
		मुक्त_irq(adapter->tx_scrq[j]->irq, adapter->tx_scrq[j]);
		irq_dispose_mapping(adapter->tx_scrq[j]->irq);
	पूर्ण
	release_sub_crqs(adapter, 1);
	वापस rc;
पूर्ण

अटल पूर्णांक init_sub_crqs(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_sub_crq_queue **allqueues;
	पूर्णांक रेजिस्टरed_queues = 0;
	पूर्णांक total_queues;
	पूर्णांक more = 0;
	पूर्णांक i;

	total_queues = adapter->req_tx_queues + adapter->req_rx_queues;

	allqueues = kसुस्मृति(total_queues, माप(*allqueues), GFP_KERNEL);
	अगर (!allqueues)
		वापस -1;

	क्रम (i = 0; i < total_queues; i++) अणु
		allqueues[i] = init_sub_crq_queue(adapter);
		अगर (!allqueues[i]) अणु
			dev_warn(dev, "Couldn't allocate all sub-crqs\n");
			अवरोध;
		पूर्ण
		रेजिस्टरed_queues++;
	पूर्ण

	/* Make sure we were able to रेजिस्टर the minimum number of queues */
	अगर (रेजिस्टरed_queues <
	    adapter->min_tx_queues + adapter->min_rx_queues) अणु
		dev_err(dev, "Fatal: Couldn't init  min number of sub-crqs\n");
		जाओ tx_failed;
	पूर्ण

	/* Distribute the failed allocated queues*/
	क्रम (i = 0; i < total_queues - रेजिस्टरed_queues + more ; i++) अणु
		netdev_dbg(adapter->netdev, "Reducing number of queues\n");
		चयन (i % 3) अणु
		हाल 0:
			अगर (adapter->req_rx_queues > adapter->min_rx_queues)
				adapter->req_rx_queues--;
			अन्यथा
				more++;
			अवरोध;
		हाल 1:
			अगर (adapter->req_tx_queues > adapter->min_tx_queues)
				adapter->req_tx_queues--;
			अन्यथा
				more++;
			अवरोध;
		पूर्ण
	पूर्ण

	adapter->tx_scrq = kसुस्मृति(adapter->req_tx_queues,
				   माप(*adapter->tx_scrq), GFP_KERNEL);
	अगर (!adapter->tx_scrq)
		जाओ tx_failed;

	क्रम (i = 0; i < adapter->req_tx_queues; i++) अणु
		adapter->tx_scrq[i] = allqueues[i];
		adapter->tx_scrq[i]->pool_index = i;
		adapter->num_active_tx_scrqs++;
	पूर्ण

	adapter->rx_scrq = kसुस्मृति(adapter->req_rx_queues,
				   माप(*adapter->rx_scrq), GFP_KERNEL);
	अगर (!adapter->rx_scrq)
		जाओ rx_failed;

	क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
		adapter->rx_scrq[i] = allqueues[i + adapter->req_tx_queues];
		adapter->rx_scrq[i]->scrq_num = i;
		adapter->num_active_rx_scrqs++;
	पूर्ण

	kमुक्त(allqueues);
	वापस 0;

rx_failed:
	kमुक्त(adapter->tx_scrq);
	adapter->tx_scrq = शून्य;
tx_failed:
	क्रम (i = 0; i < रेजिस्टरed_queues; i++)
		release_sub_crq_queue(adapter, allqueues[i], 1);
	kमुक्त(allqueues);
	वापस -1;
पूर्ण

अटल व्योम send_request_cap(काष्ठा ibmvnic_adapter *adapter, पूर्णांक retry)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	जोड़ ibmvnic_crq crq;
	पूर्णांक max_entries;

	अगर (!retry) अणु
		/* Sub-CRQ entries are 32 byte दीर्घ */
		पूर्णांक entries_page = 4 * PAGE_SIZE / (माप(u64) * 4);

		अगर (adapter->min_tx_entries_per_subcrq > entries_page ||
		    adapter->min_rx_add_entries_per_subcrq > entries_page) अणु
			dev_err(dev, "Fatal, invalid entries per sub-crq\n");
			वापस;
		पूर्ण

		अगर (adapter->desired.mtu)
			adapter->req_mtu = adapter->desired.mtu;
		अन्यथा
			adapter->req_mtu = adapter->netdev->mtu + ETH_HLEN;

		अगर (!adapter->desired.tx_entries)
			adapter->desired.tx_entries =
					adapter->max_tx_entries_per_subcrq;
		अगर (!adapter->desired.rx_entries)
			adapter->desired.rx_entries =
					adapter->max_rx_add_entries_per_subcrq;

		max_entries = IBMVNIC_MAX_LTB_SIZE /
			      (adapter->req_mtu + IBMVNIC_BUFFER_HLEN);

		अगर ((adapter->req_mtu + IBMVNIC_BUFFER_HLEN) *
			adapter->desired.tx_entries > IBMVNIC_MAX_LTB_SIZE) अणु
			adapter->desired.tx_entries = max_entries;
		पूर्ण

		अगर ((adapter->req_mtu + IBMVNIC_BUFFER_HLEN) *
			adapter->desired.rx_entries > IBMVNIC_MAX_LTB_SIZE) अणु
			adapter->desired.rx_entries = max_entries;
		पूर्ण

		अगर (adapter->desired.tx_entries)
			adapter->req_tx_entries_per_subcrq =
					adapter->desired.tx_entries;
		अन्यथा
			adapter->req_tx_entries_per_subcrq =
					adapter->max_tx_entries_per_subcrq;

		अगर (adapter->desired.rx_entries)
			adapter->req_rx_add_entries_per_subcrq =
					adapter->desired.rx_entries;
		अन्यथा
			adapter->req_rx_add_entries_per_subcrq =
					adapter->max_rx_add_entries_per_subcrq;

		अगर (adapter->desired.tx_queues)
			adapter->req_tx_queues =
					adapter->desired.tx_queues;
		अन्यथा
			adapter->req_tx_queues =
					adapter->opt_tx_comp_sub_queues;

		अगर (adapter->desired.rx_queues)
			adapter->req_rx_queues =
					adapter->desired.rx_queues;
		अन्यथा
			adapter->req_rx_queues =
					adapter->opt_rx_comp_queues;

		adapter->req_rx_add_queues = adapter->max_rx_add_queues;
	पूर्ण

	स_रखो(&crq, 0, माप(crq));
	crq.request_capability.first = IBMVNIC_CRQ_CMD;
	crq.request_capability.cmd = REQUEST_CAPABILITY;

	crq.request_capability.capability = cpu_to_be16(REQ_TX_QUEUES);
	crq.request_capability.number = cpu_to_be64(adapter->req_tx_queues);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability = cpu_to_be16(REQ_RX_QUEUES);
	crq.request_capability.number = cpu_to_be64(adapter->req_rx_queues);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability = cpu_to_be16(REQ_RX_ADD_QUEUES);
	crq.request_capability.number = cpu_to_be64(adapter->req_rx_add_queues);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability =
	    cpu_to_be16(REQ_TX_ENTRIES_PER_SUBCRQ);
	crq.request_capability.number =
	    cpu_to_be64(adapter->req_tx_entries_per_subcrq);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability =
	    cpu_to_be16(REQ_RX_ADD_ENTRIES_PER_SUBCRQ);
	crq.request_capability.number =
	    cpu_to_be64(adapter->req_rx_add_entries_per_subcrq);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.request_capability.capability = cpu_to_be16(REQ_MTU);
	crq.request_capability.number = cpu_to_be64(adapter->req_mtu);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	अगर (adapter->netdev->flags & IFF_PROMISC) अणु
		अगर (adapter->promisc_supported) अणु
			crq.request_capability.capability =
			    cpu_to_be16(PROMISC_REQUESTED);
			crq.request_capability.number = cpu_to_be64(1);
			atomic_inc(&adapter->running_cap_crqs);
			ibmvnic_send_crq(adapter, &crq);
		पूर्ण
	पूर्ण अन्यथा अणु
		crq.request_capability.capability =
		    cpu_to_be16(PROMISC_REQUESTED);
		crq.request_capability.number = cpu_to_be64(0);
		atomic_inc(&adapter->running_cap_crqs);
		ibmvnic_send_crq(adapter, &crq);
	पूर्ण
पूर्ण

अटल पूर्णांक pending_scrq(काष्ठा ibmvnic_adapter *adapter,
			काष्ठा ibmvnic_sub_crq_queue *scrq)
अणु
	जोड़ sub_crq *entry = &scrq->msgs[scrq->cur];
	पूर्णांक rc;

	rc = !!(entry->generic.first & IBMVNIC_CRQ_CMD_RSP);

	/* Ensure that the SCRQ valid flag is loaded prior to loading the
	 * contents of the SCRQ descriptor
	 */
	dma_rmb();

	वापस rc;
पूर्ण

अटल जोड़ sub_crq *ibmvnic_next_scrq(काष्ठा ibmvnic_adapter *adapter,
					काष्ठा ibmvnic_sub_crq_queue *scrq)
अणु
	जोड़ sub_crq *entry;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&scrq->lock, flags);
	entry = &scrq->msgs[scrq->cur];
	अगर (entry->generic.first & IBMVNIC_CRQ_CMD_RSP) अणु
		अगर (++scrq->cur == scrq->size)
			scrq->cur = 0;
	पूर्ण अन्यथा अणु
		entry = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&scrq->lock, flags);

	/* Ensure that the SCRQ valid flag is loaded prior to loading the
	 * contents of the SCRQ descriptor
	 */
	dma_rmb();

	वापस entry;
पूर्ण

अटल जोड़ ibmvnic_crq *ibmvnic_next_crq(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_crq_queue *queue = &adapter->crq;
	जोड़ ibmvnic_crq *crq;

	crq = &queue->msgs[queue->cur];
	अगर (crq->generic.first & IBMVNIC_CRQ_CMD_RSP) अणु
		अगर (++queue->cur == queue->size)
			queue->cur = 0;
	पूर्ण अन्यथा अणु
		crq = शून्य;
	पूर्ण

	वापस crq;
पूर्ण

अटल व्योम prपूर्णांक_subcrq_error(काष्ठा device *dev, पूर्णांक rc, स्थिर अक्षर *func)
अणु
	चयन (rc) अणु
	हाल H_PARAMETER:
		dev_warn_ratelimited(dev,
				     "%s failed: Send request is malformed or adapter failover pending. (rc=%d)\n",
				     func, rc);
		अवरोध;
	हाल H_CLOSED:
		dev_warn_ratelimited(dev,
				     "%s failed: Backing queue closed. Adapter is down or failover pending. (rc=%d)\n",
				     func, rc);
		अवरोध;
	शेष:
		dev_err_ratelimited(dev, "%s failed: (rc=%d)\n", func, rc);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक send_subcrq_indirect(काष्ठा ibmvnic_adapter *adapter,
				u64 remote_handle, u64 ioba, u64 num_entries)
अणु
	अचिन्हित पूर्णांक ua = adapter->vdev->unit_address;
	काष्ठा device *dev = &adapter->vdev->dev;
	पूर्णांक rc;

	/* Make sure the hypervisor sees the complete request */
	dma_wmb();
	rc = plpar_hcall_norets(H_SEND_SUB_CRQ_INसूचीECT, ua,
				cpu_to_be64(remote_handle),
				ioba, num_entries);

	अगर (rc)
		prपूर्णांक_subcrq_error(dev, rc, __func__);

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_send_crq(काष्ठा ibmvnic_adapter *adapter,
			    जोड़ ibmvnic_crq *crq)
अणु
	अचिन्हित पूर्णांक ua = adapter->vdev->unit_address;
	काष्ठा device *dev = &adapter->vdev->dev;
	u64 *u64_crq = (u64 *)crq;
	पूर्णांक rc;

	netdev_dbg(adapter->netdev, "Sending CRQ: %016lx %016lx\n",
		   (अचिन्हित दीर्घ)cpu_to_be64(u64_crq[0]),
		   (अचिन्हित दीर्घ)cpu_to_be64(u64_crq[1]));

	अगर (!adapter->crq.active &&
	    crq->generic.first != IBMVNIC_CRQ_INIT_CMD) अणु
		dev_warn(dev, "Invalid request detected while CRQ is inactive, possible device state change during reset\n");
		वापस -EINVAL;
	पूर्ण

	/* Make sure the hypervisor sees the complete request */
	dma_wmb();

	rc = plpar_hcall_norets(H_SEND_CRQ, ua,
				cpu_to_be64(u64_crq[0]),
				cpu_to_be64(u64_crq[1]));

	अगर (rc) अणु
		अगर (rc == H_CLOSED) अणु
			dev_warn(dev, "CRQ Queue closed\n");
			/* करो not reset, report the fail, रुको क्रम passive init from server */
		पूर्ण

		dev_warn(dev, "Send error (rc=%d)\n", rc);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_send_crq_init(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	जोड़ ibmvnic_crq crq;
	पूर्णांक retries = 100;
	पूर्णांक rc;

	स_रखो(&crq, 0, माप(crq));
	crq.generic.first = IBMVNIC_CRQ_INIT_CMD;
	crq.generic.cmd = IBMVNIC_CRQ_INIT;
	netdev_dbg(adapter->netdev, "Sending CRQ init\n");

	करो अणु
		rc = ibmvnic_send_crq(adapter, &crq);
		अगर (rc != H_CLOSED)
			अवरोध;
		retries--;
		msleep(50);

	पूर्ण जबतक (retries > 0);

	अगर (rc) अणु
		dev_err(dev, "Failed to send init request, rc = %d\n", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक send_version_xchg(काष्ठा ibmvnic_adapter *adapter)
अणु
	जोड़ ibmvnic_crq crq;

	स_रखो(&crq, 0, माप(crq));
	crq.version_exchange.first = IBMVNIC_CRQ_CMD;
	crq.version_exchange.cmd = VERSION_EXCHANGE;
	crq.version_exchange.version = cpu_to_be16(ibmvnic_version);

	वापस ibmvnic_send_crq(adapter, &crq);
पूर्ण

काष्ठा vnic_login_client_data अणु
	u8	type;
	__be16	len;
	अक्षर	name[];
पूर्ण __packed;

अटल पूर्णांक vnic_client_data_len(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक len;

	/* Calculate the amount of buffer space needed क्रम the
	 * vnic client data in the login buffer. There are four entries,
	 * OS name, LPAR name, device name, and a null last entry.
	 */
	len = 4 * माप(काष्ठा vnic_login_client_data);
	len += 6; /* "Linux" plus शून्य */
	len += म_माप(utsname()->nodename) + 1;
	len += म_माप(adapter->netdev->name) + 1;

	वापस len;
पूर्ण

अटल व्योम vnic_add_client_data(काष्ठा ibmvnic_adapter *adapter,
				 काष्ठा vnic_login_client_data *vlcd)
अणु
	स्थिर अक्षर *os_name = "Linux";
	पूर्णांक len;

	/* Type 1 - LPAR OS */
	vlcd->type = 1;
	len = म_माप(os_name) + 1;
	vlcd->len = cpu_to_be16(len);
	म_नकलन(vlcd->name, os_name, len);
	vlcd = (काष्ठा vnic_login_client_data *)(vlcd->name + len);

	/* Type 2 - LPAR name */
	vlcd->type = 2;
	len = म_माप(utsname()->nodename) + 1;
	vlcd->len = cpu_to_be16(len);
	म_नकलन(vlcd->name, utsname()->nodename, len);
	vlcd = (काष्ठा vnic_login_client_data *)(vlcd->name + len);

	/* Type 3 - device name */
	vlcd->type = 3;
	len = म_माप(adapter->netdev->name) + 1;
	vlcd->len = cpu_to_be16(len);
	म_नकलन(vlcd->name, adapter->netdev->name, len);
पूर्ण

अटल पूर्णांक send_login(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_login_rsp_buffer *login_rsp_buffer;
	काष्ठा ibmvnic_login_buffer *login_buffer;
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा vnic_login_client_data *vlcd;
	dma_addr_t rsp_buffer_token;
	dma_addr_t buffer_token;
	माप_प्रकार rsp_buffer_size;
	जोड़ ibmvnic_crq crq;
	पूर्णांक client_data_len;
	माप_प्रकार buffer_size;
	__be64 *tx_list_p;
	__be64 *rx_list_p;
	पूर्णांक rc;
	पूर्णांक i;

	अगर (!adapter->tx_scrq || !adapter->rx_scrq) अणु
		netdev_err(adapter->netdev,
			   "RX or TX queues are not allocated, device login failed\n");
		वापस -1;
	पूर्ण

	release_login_buffer(adapter);
	release_login_rsp_buffer(adapter);

	client_data_len = vnic_client_data_len(adapter);

	buffer_size =
	    माप(काष्ठा ibmvnic_login_buffer) +
	    माप(u64) * (adapter->req_tx_queues + adapter->req_rx_queues) +
	    client_data_len;

	login_buffer = kzalloc(buffer_size, GFP_ATOMIC);
	अगर (!login_buffer)
		जाओ buf_alloc_failed;

	buffer_token = dma_map_single(dev, login_buffer, buffer_size,
				      DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, buffer_token)) अणु
		dev_err(dev, "Couldn't map login buffer\n");
		जाओ buf_map_failed;
	पूर्ण

	rsp_buffer_size = माप(काष्ठा ibmvnic_login_rsp_buffer) +
			  माप(u64) * adapter->req_tx_queues +
			  माप(u64) * adapter->req_rx_queues +
			  माप(u64) * adapter->req_rx_queues +
			  माप(u8) * IBMVNIC_TX_DESC_VERSIONS;

	login_rsp_buffer = kदो_स्मृति(rsp_buffer_size, GFP_ATOMIC);
	अगर (!login_rsp_buffer)
		जाओ buf_rsp_alloc_failed;

	rsp_buffer_token = dma_map_single(dev, login_rsp_buffer,
					  rsp_buffer_size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, rsp_buffer_token)) अणु
		dev_err(dev, "Couldn't map login rsp buffer\n");
		जाओ buf_rsp_map_failed;
	पूर्ण

	adapter->login_buf = login_buffer;
	adapter->login_buf_token = buffer_token;
	adapter->login_buf_sz = buffer_size;
	adapter->login_rsp_buf = login_rsp_buffer;
	adapter->login_rsp_buf_token = rsp_buffer_token;
	adapter->login_rsp_buf_sz = rsp_buffer_size;

	login_buffer->len = cpu_to_be32(buffer_size);
	login_buffer->version = cpu_to_be32(INITIAL_VERSION_LB);
	login_buffer->num_txcomp_subcrqs = cpu_to_be32(adapter->req_tx_queues);
	login_buffer->off_txcomp_subcrqs =
	    cpu_to_be32(माप(काष्ठा ibmvnic_login_buffer));
	login_buffer->num_rxcomp_subcrqs = cpu_to_be32(adapter->req_rx_queues);
	login_buffer->off_rxcomp_subcrqs =
	    cpu_to_be32(माप(काष्ठा ibmvnic_login_buffer) +
			माप(u64) * adapter->req_tx_queues);
	login_buffer->login_rsp_ioba = cpu_to_be32(rsp_buffer_token);
	login_buffer->login_rsp_len = cpu_to_be32(rsp_buffer_size);

	tx_list_p = (__be64 *)((अक्षर *)login_buffer +
				      माप(काष्ठा ibmvnic_login_buffer));
	rx_list_p = (__be64 *)((अक्षर *)login_buffer +
				      माप(काष्ठा ibmvnic_login_buffer) +
				      माप(u64) * adapter->req_tx_queues);

	क्रम (i = 0; i < adapter->req_tx_queues; i++) अणु
		अगर (adapter->tx_scrq[i]) अणु
			tx_list_p[i] =
				cpu_to_be64(adapter->tx_scrq[i]->crq_num);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < adapter->req_rx_queues; i++) अणु
		अगर (adapter->rx_scrq[i]) अणु
			rx_list_p[i] =
				cpu_to_be64(adapter->rx_scrq[i]->crq_num);
		पूर्ण
	पूर्ण

	/* Insert vNIC login client data */
	vlcd = (काष्ठा vnic_login_client_data *)
		((अक्षर *)rx_list_p + (माप(u64) * adapter->req_rx_queues));
	login_buffer->client_data_offset =
			cpu_to_be32((अक्षर *)vlcd - (अक्षर *)login_buffer);
	login_buffer->client_data_len = cpu_to_be32(client_data_len);

	vnic_add_client_data(adapter, vlcd);

	netdev_dbg(adapter->netdev, "Login Buffer:\n");
	क्रम (i = 0; i < (adapter->login_buf_sz - 1) / 8 + 1; i++) अणु
		netdev_dbg(adapter->netdev, "%016lx\n",
			   ((अचिन्हित दीर्घ *)(adapter->login_buf))[i]);
	पूर्ण

	स_रखो(&crq, 0, माप(crq));
	crq.login.first = IBMVNIC_CRQ_CMD;
	crq.login.cmd = LOGIN;
	crq.login.ioba = cpu_to_be32(buffer_token);
	crq.login.len = cpu_to_be32(buffer_size);

	adapter->login_pending = true;
	rc = ibmvnic_send_crq(adapter, &crq);
	अगर (rc) अणु
		adapter->login_pending = false;
		netdev_err(adapter->netdev, "Failed to send login, rc=%d\n", rc);
		जाओ buf_rsp_map_failed;
	पूर्ण

	वापस 0;

buf_rsp_map_failed:
	kमुक्त(login_rsp_buffer);
	adapter->login_rsp_buf = शून्य;
buf_rsp_alloc_failed:
	dma_unmap_single(dev, buffer_token, buffer_size, DMA_TO_DEVICE);
buf_map_failed:
	kमुक्त(login_buffer);
	adapter->login_buf = शून्य;
buf_alloc_failed:
	वापस -1;
पूर्ण

अटल पूर्णांक send_request_map(काष्ठा ibmvnic_adapter *adapter, dma_addr_t addr,
			    u32 len, u8 map_id)
अणु
	जोड़ ibmvnic_crq crq;

	स_रखो(&crq, 0, माप(crq));
	crq.request_map.first = IBMVNIC_CRQ_CMD;
	crq.request_map.cmd = REQUEST_MAP;
	crq.request_map.map_id = map_id;
	crq.request_map.ioba = cpu_to_be32(addr);
	crq.request_map.len = cpu_to_be32(len);
	वापस ibmvnic_send_crq(adapter, &crq);
पूर्ण

अटल पूर्णांक send_request_unmap(काष्ठा ibmvnic_adapter *adapter, u8 map_id)
अणु
	जोड़ ibmvnic_crq crq;

	स_रखो(&crq, 0, माप(crq));
	crq.request_unmap.first = IBMVNIC_CRQ_CMD;
	crq.request_unmap.cmd = REQUEST_UNMAP;
	crq.request_unmap.map_id = map_id;
	वापस ibmvnic_send_crq(adapter, &crq);
पूर्ण

अटल व्योम send_query_map(काष्ठा ibmvnic_adapter *adapter)
अणु
	जोड़ ibmvnic_crq crq;

	स_रखो(&crq, 0, माप(crq));
	crq.query_map.first = IBMVNIC_CRQ_CMD;
	crq.query_map.cmd = QUERY_MAP;
	ibmvnic_send_crq(adapter, &crq);
पूर्ण

/* Send a series of CRQs requesting various capabilities of the VNIC server */
अटल व्योम send_query_cap(काष्ठा ibmvnic_adapter *adapter)
अणु
	जोड़ ibmvnic_crq crq;

	atomic_set(&adapter->running_cap_crqs, 0);
	स_रखो(&crq, 0, माप(crq));
	crq.query_capability.first = IBMVNIC_CRQ_CMD;
	crq.query_capability.cmd = QUERY_CAPABILITY;

	crq.query_capability.capability = cpu_to_be16(MIN_TX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MIN_RX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MIN_RX_ADD_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_TX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_RX_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_RX_ADD_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MIN_TX_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MIN_RX_ADD_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MAX_TX_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
	    cpu_to_be16(MAX_RX_ADD_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(TCP_IP_OFFLOAD);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(PROMISC_SUPPORTED);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MIN_MTU);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_MTU);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_MULTICAST_FILTERS);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(VLAN_HEADER_INSERTION);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(RX_VLAN_HEADER_INSERTION);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(MAX_TX_SG_ENTRIES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(RX_SG_SUPPORTED);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(OPT_TX_COMP_SUB_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(OPT_RX_COMP_QUEUES);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
			cpu_to_be16(OPT_RX_BUFADD_Q_PER_RX_COMP_Q);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
			cpu_to_be16(OPT_TX_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability =
			cpu_to_be16(OPT_RXBA_ENTRIES_PER_SUBCRQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);

	crq.query_capability.capability = cpu_to_be16(TX_RX_DESC_REQ);
	atomic_inc(&adapter->running_cap_crqs);
	ibmvnic_send_crq(adapter, &crq);
पूर्ण

अटल व्योम send_query_ip_offload(काष्ठा ibmvnic_adapter *adapter)
अणु
	पूर्णांक buf_sz = माप(काष्ठा ibmvnic_query_ip_offload_buffer);
	काष्ठा device *dev = &adapter->vdev->dev;
	जोड़ ibmvnic_crq crq;

	adapter->ip_offload_tok =
		dma_map_single(dev,
			       &adapter->ip_offload_buf,
			       buf_sz,
			       DMA_FROM_DEVICE);

	अगर (dma_mapping_error(dev, adapter->ip_offload_tok)) अणु
		अगर (!firmware_has_feature(FW_FEATURE_CMO))
			dev_err(dev, "Couldn't map offload buffer\n");
		वापस;
	पूर्ण

	स_रखो(&crq, 0, माप(crq));
	crq.query_ip_offload.first = IBMVNIC_CRQ_CMD;
	crq.query_ip_offload.cmd = QUERY_IP_OFFLOAD;
	crq.query_ip_offload.len = cpu_to_be32(buf_sz);
	crq.query_ip_offload.ioba =
	    cpu_to_be32(adapter->ip_offload_tok);

	ibmvnic_send_crq(adapter, &crq);
पूर्ण

अटल व्योम send_control_ip_offload(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_control_ip_offload_buffer *ctrl_buf = &adapter->ip_offload_ctrl;
	काष्ठा ibmvnic_query_ip_offload_buffer *buf = &adapter->ip_offload_buf;
	काष्ठा device *dev = &adapter->vdev->dev;
	netdev_features_t old_hw_features = 0;
	जोड़ ibmvnic_crq crq;

	adapter->ip_offload_ctrl_tok =
		dma_map_single(dev,
			       ctrl_buf,
			       माप(adapter->ip_offload_ctrl),
			       DMA_TO_DEVICE);

	अगर (dma_mapping_error(dev, adapter->ip_offload_ctrl_tok)) अणु
		dev_err(dev, "Couldn't map ip offload control buffer\n");
		वापस;
	पूर्ण

	ctrl_buf->len = cpu_to_be32(माप(adapter->ip_offload_ctrl));
	ctrl_buf->version = cpu_to_be32(INITIAL_VERSION_IOB);
	ctrl_buf->ipv4_chksum = buf->ipv4_chksum;
	ctrl_buf->ipv6_chksum = buf->ipv6_chksum;
	ctrl_buf->tcp_ipv4_chksum = buf->tcp_ipv4_chksum;
	ctrl_buf->udp_ipv4_chksum = buf->udp_ipv4_chksum;
	ctrl_buf->tcp_ipv6_chksum = buf->tcp_ipv6_chksum;
	ctrl_buf->udp_ipv6_chksum = buf->udp_ipv6_chksum;
	ctrl_buf->large_tx_ipv4 = buf->large_tx_ipv4;
	ctrl_buf->large_tx_ipv6 = buf->large_tx_ipv6;

	/* large_rx disabled क्रम now, additional features needed */
	ctrl_buf->large_rx_ipv4 = 0;
	ctrl_buf->large_rx_ipv6 = 0;

	अगर (adapter->state != VNIC_PROBING) अणु
		old_hw_features = adapter->netdev->hw_features;
		adapter->netdev->hw_features = 0;
	पूर्ण

	adapter->netdev->hw_features = NETIF_F_SG | NETIF_F_GSO | NETIF_F_GRO;

	अगर (buf->tcp_ipv4_chksum || buf->udp_ipv4_chksum)
		adapter->netdev->hw_features |= NETIF_F_IP_CSUM;

	अगर (buf->tcp_ipv6_chksum || buf->udp_ipv6_chksum)
		adapter->netdev->hw_features |= NETIF_F_IPV6_CSUM;

	अगर ((adapter->netdev->features &
	    (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)))
		adapter->netdev->hw_features |= NETIF_F_RXCSUM;

	अगर (buf->large_tx_ipv4)
		adapter->netdev->hw_features |= NETIF_F_TSO;
	अगर (buf->large_tx_ipv6)
		adapter->netdev->hw_features |= NETIF_F_TSO6;

	अगर (adapter->state == VNIC_PROBING) अणु
		adapter->netdev->features |= adapter->netdev->hw_features;
	पूर्ण अन्यथा अगर (old_hw_features != adapter->netdev->hw_features) अणु
		netdev_features_t पंचांगp = 0;

		/* disable features no दीर्घer supported */
		adapter->netdev->features &= adapter->netdev->hw_features;
		/* turn on features now supported अगर previously enabled */
		पंचांगp = (old_hw_features ^ adapter->netdev->hw_features) &
			adapter->netdev->hw_features;
		adapter->netdev->features |=
				पंचांगp & adapter->netdev->wanted_features;
	पूर्ण

	स_रखो(&crq, 0, माप(crq));
	crq.control_ip_offload.first = IBMVNIC_CRQ_CMD;
	crq.control_ip_offload.cmd = CONTROL_IP_OFFLOAD;
	crq.control_ip_offload.len =
	    cpu_to_be32(माप(adapter->ip_offload_ctrl));
	crq.control_ip_offload.ioba = cpu_to_be32(adapter->ip_offload_ctrl_tok);
	ibmvnic_send_crq(adapter, &crq);
पूर्ण

अटल व्योम handle_vpd_size_rsp(जोड़ ibmvnic_crq *crq,
				काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;

	अगर (crq->get_vpd_size_rsp.rc.code) अणु
		dev_err(dev, "Error retrieving VPD size, rc=%x\n",
			crq->get_vpd_size_rsp.rc.code);
		complete(&adapter->fw_करोne);
		वापस;
	पूर्ण

	adapter->vpd->len = be64_to_cpu(crq->get_vpd_size_rsp.len);
	complete(&adapter->fw_करोne);
पूर्ण

अटल व्योम handle_vpd_rsp(जोड़ ibmvnic_crq *crq,
			   काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	अचिन्हित अक्षर *substr = शून्य;
	u8 fw_level_len = 0;

	स_रखो(adapter->fw_version, 0, 32);

	dma_unmap_single(dev, adapter->vpd->dma_addr, adapter->vpd->len,
			 DMA_FROM_DEVICE);

	अगर (crq->get_vpd_rsp.rc.code) अणु
		dev_err(dev, "Error retrieving VPD from device, rc=%x\n",
			crq->get_vpd_rsp.rc.code);
		जाओ complete;
	पूर्ण

	/* get the position of the firmware version info
	 * located after the ASCII 'RM' substring in the buffer
	 */
	substr = strnstr(adapter->vpd->buff, "RM", adapter->vpd->len);
	अगर (!substr) अणु
		dev_info(dev, "Warning - No FW level has been provided in the VPD buffer by the VIOS Server\n");
		जाओ complete;
	पूर्ण

	/* get length of firmware level ASCII substring */
	अगर ((substr + 2) < (adapter->vpd->buff + adapter->vpd->len)) अणु
		fw_level_len = *(substr + 2);
	पूर्ण अन्यथा अणु
		dev_info(dev, "Length of FW substr extrapolated VDP buff\n");
		जाओ complete;
	पूर्ण

	/* copy firmware version string from vpd पूर्णांकo adapter */
	अगर ((substr + 3 + fw_level_len) <
	    (adapter->vpd->buff + adapter->vpd->len)) अणु
		म_नकलन((अक्षर *)adapter->fw_version, substr + 3, fw_level_len);
	पूर्ण अन्यथा अणु
		dev_info(dev, "FW substr extrapolated VPD buff\n");
	पूर्ण

complete:
	अगर (adapter->fw_version[0] == '\0')
		म_नकलन((अक्षर *)adapter->fw_version, "N/A", 3 * माप(अक्षर));
	complete(&adapter->fw_करोne);
पूर्ण

अटल व्योम handle_query_ip_offload_rsp(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा ibmvnic_query_ip_offload_buffer *buf = &adapter->ip_offload_buf;
	पूर्णांक i;

	dma_unmap_single(dev, adapter->ip_offload_tok,
			 माप(adapter->ip_offload_buf), DMA_FROM_DEVICE);

	netdev_dbg(adapter->netdev, "Query IP Offload Buffer:\n");
	क्रम (i = 0; i < (माप(adapter->ip_offload_buf) - 1) / 8 + 1; i++)
		netdev_dbg(adapter->netdev, "%016lx\n",
			   ((अचिन्हित दीर्घ *)(buf))[i]);

	netdev_dbg(adapter->netdev, "ipv4_chksum = %d\n", buf->ipv4_chksum);
	netdev_dbg(adapter->netdev, "ipv6_chksum = %d\n", buf->ipv6_chksum);
	netdev_dbg(adapter->netdev, "tcp_ipv4_chksum = %d\n",
		   buf->tcp_ipv4_chksum);
	netdev_dbg(adapter->netdev, "tcp_ipv6_chksum = %d\n",
		   buf->tcp_ipv6_chksum);
	netdev_dbg(adapter->netdev, "udp_ipv4_chksum = %d\n",
		   buf->udp_ipv4_chksum);
	netdev_dbg(adapter->netdev, "udp_ipv6_chksum = %d\n",
		   buf->udp_ipv6_chksum);
	netdev_dbg(adapter->netdev, "large_tx_ipv4 = %d\n",
		   buf->large_tx_ipv4);
	netdev_dbg(adapter->netdev, "large_tx_ipv6 = %d\n",
		   buf->large_tx_ipv6);
	netdev_dbg(adapter->netdev, "large_rx_ipv4 = %d\n",
		   buf->large_rx_ipv4);
	netdev_dbg(adapter->netdev, "large_rx_ipv6 = %d\n",
		   buf->large_rx_ipv6);
	netdev_dbg(adapter->netdev, "max_ipv4_hdr_sz = %d\n",
		   buf->max_ipv4_header_size);
	netdev_dbg(adapter->netdev, "max_ipv6_hdr_sz = %d\n",
		   buf->max_ipv6_header_size);
	netdev_dbg(adapter->netdev, "max_tcp_hdr_size = %d\n",
		   buf->max_tcp_header_size);
	netdev_dbg(adapter->netdev, "max_udp_hdr_size = %d\n",
		   buf->max_udp_header_size);
	netdev_dbg(adapter->netdev, "max_large_tx_size = %d\n",
		   buf->max_large_tx_size);
	netdev_dbg(adapter->netdev, "max_large_rx_size = %d\n",
		   buf->max_large_rx_size);
	netdev_dbg(adapter->netdev, "ipv6_ext_hdr = %d\n",
		   buf->ipv6_extension_header);
	netdev_dbg(adapter->netdev, "tcp_pseudosum_req = %d\n",
		   buf->tcp_pseuकरोsum_req);
	netdev_dbg(adapter->netdev, "num_ipv6_ext_hd = %d\n",
		   buf->num_ipv6_ext_headers);
	netdev_dbg(adapter->netdev, "off_ipv6_ext_hd = %d\n",
		   buf->off_ipv6_ext_headers);

	send_control_ip_offload(adapter);
पूर्ण

अटल स्थिर अक्षर *ibmvnic_fw_err_cause(u16 cause)
अणु
	चयन (cause) अणु
	हाल ADAPTER_PROBLEM:
		वापस "adapter problem";
	हाल BUS_PROBLEM:
		वापस "bus problem";
	हाल FW_PROBLEM:
		वापस "firmware problem";
	हाल DD_PROBLEM:
		वापस "device driver problem";
	हाल EEH_RECOVERY:
		वापस "EEH recovery";
	हाल FW_UPDATED:
		वापस "firmware updated";
	हाल LOW_MEMORY:
		वापस "low Memory";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल व्योम handle_error_indication(जोड़ ibmvnic_crq *crq,
				    काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	u16 cause;

	cause = be16_to_cpu(crq->error_indication.error_cause);

	dev_warn_ratelimited(dev,
			     "Firmware reports %serror, cause: %s. Starting recovery...\n",
			     crq->error_indication.flags
				& IBMVNIC_FATAL_ERROR ? "FATAL " : "",
			     ibmvnic_fw_err_cause(cause));

	अगर (crq->error_indication.flags & IBMVNIC_FATAL_ERROR)
		ibmvnic_reset(adapter, VNIC_RESET_FATAL);
	अन्यथा
		ibmvnic_reset(adapter, VNIC_RESET_NON_FATAL);
पूर्ण

अटल पूर्णांक handle_change_mac_rsp(जोड़ ibmvnic_crq *crq,
				 काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा device *dev = &adapter->vdev->dev;
	दीर्घ rc;

	rc = crq->change_mac_addr_rsp.rc.code;
	अगर (rc) अणु
		dev_err(dev, "Error %ld in CHANGE_MAC_ADDR_RSP\n", rc);
		जाओ out;
	पूर्ण
	/* crq->change_mac_addr.mac_addr is the requested one
	 * crq->change_mac_addr_rsp.mac_addr is the वापसed valid one.
	 */
	ether_addr_copy(netdev->dev_addr,
			&crq->change_mac_addr_rsp.mac_addr[0]);
	ether_addr_copy(adapter->mac_addr,
			&crq->change_mac_addr_rsp.mac_addr[0]);
out:
	complete(&adapter->fw_करोne);
	वापस rc;
पूर्ण

अटल व्योम handle_request_cap_rsp(जोड़ ibmvnic_crq *crq,
				   काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	u64 *req_value;
	अक्षर *name;

	atomic_dec(&adapter->running_cap_crqs);
	चयन (be16_to_cpu(crq->request_capability_rsp.capability)) अणु
	हाल REQ_TX_QUEUES:
		req_value = &adapter->req_tx_queues;
		name = "tx";
		अवरोध;
	हाल REQ_RX_QUEUES:
		req_value = &adapter->req_rx_queues;
		name = "rx";
		अवरोध;
	हाल REQ_RX_ADD_QUEUES:
		req_value = &adapter->req_rx_add_queues;
		name = "rx_add";
		अवरोध;
	हाल REQ_TX_ENTRIES_PER_SUBCRQ:
		req_value = &adapter->req_tx_entries_per_subcrq;
		name = "tx_entries_per_subcrq";
		अवरोध;
	हाल REQ_RX_ADD_ENTRIES_PER_SUBCRQ:
		req_value = &adapter->req_rx_add_entries_per_subcrq;
		name = "rx_add_entries_per_subcrq";
		अवरोध;
	हाल REQ_MTU:
		req_value = &adapter->req_mtu;
		name = "mtu";
		अवरोध;
	हाल PROMISC_REQUESTED:
		req_value = &adapter->promisc;
		name = "promisc";
		अवरोध;
	शेष:
		dev_err(dev, "Got invalid cap request rsp %d\n",
			crq->request_capability.capability);
		वापस;
	पूर्ण

	चयन (crq->request_capability_rsp.rc.code) अणु
	हाल SUCCESS:
		अवरोध;
	हाल PARTIALSUCCESS:
		dev_info(dev, "req=%lld, rsp=%ld in %s queue, retrying.\n",
			 *req_value,
			 (दीर्घ)be64_to_cpu(crq->request_capability_rsp.number),
			 name);

		अगर (be16_to_cpu(crq->request_capability_rsp.capability) ==
		    REQ_MTU) अणु
			pr_err("mtu of %llu is not supported. Reverting.\n",
			       *req_value);
			*req_value = adapter->fallback.mtu;
		पूर्ण अन्यथा अणु
			*req_value =
				be64_to_cpu(crq->request_capability_rsp.number);
		पूर्ण

		send_request_cap(adapter, 1);
		वापस;
	शेष:
		dev_err(dev, "Error %d in request cap rsp\n",
			crq->request_capability_rsp.rc.code);
		वापस;
	पूर्ण

	/* Done receiving requested capabilities, query IP offload support */
	अगर (atomic_पढ़ो(&adapter->running_cap_crqs) == 0) अणु
		adapter->रुको_capability = false;
		send_query_ip_offload(adapter);
	पूर्ण
पूर्ण

अटल पूर्णांक handle_login_rsp(जोड़ ibmvnic_crq *login_rsp_crq,
			    काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ibmvnic_login_rsp_buffer *login_rsp = adapter->login_rsp_buf;
	काष्ठा ibmvnic_login_buffer *login = adapter->login_buf;
	u64 *tx_handle_array;
	u64 *rx_handle_array;
	पूर्णांक num_tx_pools;
	पूर्णांक num_rx_pools;
	u64 *size_array;
	पूर्णांक i;

	/* CHECK: Test/set of login_pending करोes not need to be atomic
	 * because only ibmvnic_tasklet tests/clears this.
	 */
	अगर (!adapter->login_pending) अणु
		netdev_warn(netdev, "Ignoring unexpected login response\n");
		वापस 0;
	पूर्ण
	adapter->login_pending = false;

	dma_unmap_single(dev, adapter->login_buf_token, adapter->login_buf_sz,
			 DMA_TO_DEVICE);
	dma_unmap_single(dev, adapter->login_rsp_buf_token,
			 adapter->login_rsp_buf_sz, DMA_FROM_DEVICE);

	/* If the number of queues requested can't be allocated by the
	 * server, the login response will वापस with code 1. We will need
	 * to resend the login buffer with fewer queues requested.
	 */
	अगर (login_rsp_crq->generic.rc.code) अणु
		adapter->init_करोne_rc = login_rsp_crq->generic.rc.code;
		complete(&adapter->init_करोne);
		वापस 0;
	पूर्ण

	netdev->mtu = adapter->req_mtu - ETH_HLEN;

	netdev_dbg(adapter->netdev, "Login Response Buffer:\n");
	क्रम (i = 0; i < (adapter->login_rsp_buf_sz - 1) / 8 + 1; i++) अणु
		netdev_dbg(adapter->netdev, "%016lx\n",
			   ((अचिन्हित दीर्घ *)(adapter->login_rsp_buf))[i]);
	पूर्ण

	/* Sanity checks */
	अगर (login->num_txcomp_subcrqs != login_rsp->num_txsubm_subcrqs ||
	    (be32_to_cpu(login->num_rxcomp_subcrqs) *
	     adapter->req_rx_add_queues !=
	     be32_to_cpu(login_rsp->num_rxadd_subcrqs))) अणु
		dev_err(dev, "FATAL: Inconsistent login and login rsp\n");
		ibmvnic_reset(adapter, VNIC_RESET_FATAL);
		वापस -EIO;
	पूर्ण
	size_array = (u64 *)((u8 *)(adapter->login_rsp_buf) +
		be32_to_cpu(adapter->login_rsp_buf->off_rxadd_buff_size));
	/* variable buffer sizes are not supported, so just पढ़ो the
	 * first entry.
	 */
	adapter->cur_rx_buf_sz = be64_to_cpu(size_array[0]);

	num_tx_pools = be32_to_cpu(adapter->login_rsp_buf->num_txsubm_subcrqs);
	num_rx_pools = be32_to_cpu(adapter->login_rsp_buf->num_rxadd_subcrqs);

	tx_handle_array = (u64 *)((u8 *)(adapter->login_rsp_buf) +
				  be32_to_cpu(adapter->login_rsp_buf->off_txsubm_subcrqs));
	rx_handle_array = (u64 *)((u8 *)(adapter->login_rsp_buf) +
				  be32_to_cpu(adapter->login_rsp_buf->off_rxadd_subcrqs));

	क्रम (i = 0; i < num_tx_pools; i++)
		adapter->tx_scrq[i]->handle = tx_handle_array[i];

	क्रम (i = 0; i < num_rx_pools; i++)
		adapter->rx_scrq[i]->handle = rx_handle_array[i];

	adapter->num_active_tx_scrqs = num_tx_pools;
	adapter->num_active_rx_scrqs = num_rx_pools;
	release_login_rsp_buffer(adapter);
	release_login_buffer(adapter);
	complete(&adapter->init_करोne);

	वापस 0;
पूर्ण

अटल व्योम handle_request_unmap_rsp(जोड़ ibmvnic_crq *crq,
				     काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	दीर्घ rc;

	rc = crq->request_unmap_rsp.rc.code;
	अगर (rc)
		dev_err(dev, "Error %ld in REQUEST_UNMAP_RSP\n", rc);
पूर्ण

अटल व्योम handle_query_map_rsp(जोड़ ibmvnic_crq *crq,
				 काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा device *dev = &adapter->vdev->dev;
	दीर्घ rc;

	rc = crq->query_map_rsp.rc.code;
	अगर (rc) अणु
		dev_err(dev, "Error %ld in QUERY_MAP_RSP\n", rc);
		वापस;
	पूर्ण
	netdev_dbg(netdev, "page_size = %d\ntot_pages = %d\nfree_pages = %d\n",
		   crq->query_map_rsp.page_size, crq->query_map_rsp.tot_pages,
		   crq->query_map_rsp.मुक्त_pages);
पूर्ण

अटल व्योम handle_query_cap_rsp(जोड़ ibmvnic_crq *crq,
				 काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा device *dev = &adapter->vdev->dev;
	दीर्घ rc;

	atomic_dec(&adapter->running_cap_crqs);
	netdev_dbg(netdev, "Outstanding queries: %d\n",
		   atomic_पढ़ो(&adapter->running_cap_crqs));
	rc = crq->query_capability.rc.code;
	अगर (rc) अणु
		dev_err(dev, "Error %ld in QUERY_CAP_RSP\n", rc);
		जाओ out;
	पूर्ण

	चयन (be16_to_cpu(crq->query_capability.capability)) अणु
	हाल MIN_TX_QUEUES:
		adapter->min_tx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_tx_queues = %lld\n",
			   adapter->min_tx_queues);
		अवरोध;
	हाल MIN_RX_QUEUES:
		adapter->min_rx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_rx_queues = %lld\n",
			   adapter->min_rx_queues);
		अवरोध;
	हाल MIN_RX_ADD_QUEUES:
		adapter->min_rx_add_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_rx_add_queues = %lld\n",
			   adapter->min_rx_add_queues);
		अवरोध;
	हाल MAX_TX_QUEUES:
		adapter->max_tx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_tx_queues = %lld\n",
			   adapter->max_tx_queues);
		अवरोध;
	हाल MAX_RX_QUEUES:
		adapter->max_rx_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_rx_queues = %lld\n",
			   adapter->max_rx_queues);
		अवरोध;
	हाल MAX_RX_ADD_QUEUES:
		adapter->max_rx_add_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_rx_add_queues = %lld\n",
			   adapter->max_rx_add_queues);
		अवरोध;
	हाल MIN_TX_ENTRIES_PER_SUBCRQ:
		adapter->min_tx_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_tx_entries_per_subcrq = %lld\n",
			   adapter->min_tx_entries_per_subcrq);
		अवरोध;
	हाल MIN_RX_ADD_ENTRIES_PER_SUBCRQ:
		adapter->min_rx_add_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "min_rx_add_entrs_per_subcrq = %lld\n",
			   adapter->min_rx_add_entries_per_subcrq);
		अवरोध;
	हाल MAX_TX_ENTRIES_PER_SUBCRQ:
		adapter->max_tx_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_tx_entries_per_subcrq = %lld\n",
			   adapter->max_tx_entries_per_subcrq);
		अवरोध;
	हाल MAX_RX_ADD_ENTRIES_PER_SUBCRQ:
		adapter->max_rx_add_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_rx_add_entrs_per_subcrq = %lld\n",
			   adapter->max_rx_add_entries_per_subcrq);
		अवरोध;
	हाल TCP_IP_OFFLOAD:
		adapter->tcp_ip_offload =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "tcp_ip_offload = %lld\n",
			   adapter->tcp_ip_offload);
		अवरोध;
	हाल PROMISC_SUPPORTED:
		adapter->promisc_supported =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "promisc_supported = %lld\n",
			   adapter->promisc_supported);
		अवरोध;
	हाल MIN_MTU:
		adapter->min_mtu = be64_to_cpu(crq->query_capability.number);
		netdev->min_mtu = adapter->min_mtu - ETH_HLEN;
		netdev_dbg(netdev, "min_mtu = %lld\n", adapter->min_mtu);
		अवरोध;
	हाल MAX_MTU:
		adapter->max_mtu = be64_to_cpu(crq->query_capability.number);
		netdev->max_mtu = adapter->max_mtu - ETH_HLEN;
		netdev_dbg(netdev, "max_mtu = %lld\n", adapter->max_mtu);
		अवरोध;
	हाल MAX_MULTICAST_FILTERS:
		adapter->max_multicast_filters =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_multicast_filters = %lld\n",
			   adapter->max_multicast_filters);
		अवरोध;
	हाल VLAN_HEADER_INSERTION:
		adapter->vlan_header_insertion =
		    be64_to_cpu(crq->query_capability.number);
		अगर (adapter->vlan_header_insertion)
			netdev->features |= NETIF_F_HW_VLAN_STAG_TX;
		netdev_dbg(netdev, "vlan_header_insertion = %lld\n",
			   adapter->vlan_header_insertion);
		अवरोध;
	हाल RX_VLAN_HEADER_INSERTION:
		adapter->rx_vlan_header_insertion =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "rx_vlan_header_insertion = %lld\n",
			   adapter->rx_vlan_header_insertion);
		अवरोध;
	हाल MAX_TX_SG_ENTRIES:
		adapter->max_tx_sg_entries =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "max_tx_sg_entries = %lld\n",
			   adapter->max_tx_sg_entries);
		अवरोध;
	हाल RX_SG_SUPPORTED:
		adapter->rx_sg_supported =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "rx_sg_supported = %lld\n",
			   adapter->rx_sg_supported);
		अवरोध;
	हाल OPT_TX_COMP_SUB_QUEUES:
		adapter->opt_tx_comp_sub_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_tx_comp_sub_queues = %lld\n",
			   adapter->opt_tx_comp_sub_queues);
		अवरोध;
	हाल OPT_RX_COMP_QUEUES:
		adapter->opt_rx_comp_queues =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_rx_comp_queues = %lld\n",
			   adapter->opt_rx_comp_queues);
		अवरोध;
	हाल OPT_RX_BUFADD_Q_PER_RX_COMP_Q:
		adapter->opt_rx_bufadd_q_per_rx_comp_q =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_rx_bufadd_q_per_rx_comp_q = %lld\n",
			   adapter->opt_rx_bufadd_q_per_rx_comp_q);
		अवरोध;
	हाल OPT_TX_ENTRIES_PER_SUBCRQ:
		adapter->opt_tx_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_tx_entries_per_subcrq = %lld\n",
			   adapter->opt_tx_entries_per_subcrq);
		अवरोध;
	हाल OPT_RXBA_ENTRIES_PER_SUBCRQ:
		adapter->opt_rxba_entries_per_subcrq =
		    be64_to_cpu(crq->query_capability.number);
		netdev_dbg(netdev, "opt_rxba_entries_per_subcrq = %lld\n",
			   adapter->opt_rxba_entries_per_subcrq);
		अवरोध;
	हाल TX_RX_DESC_REQ:
		adapter->tx_rx_desc_req = crq->query_capability.number;
		netdev_dbg(netdev, "tx_rx_desc_req = %llx\n",
			   adapter->tx_rx_desc_req);
		अवरोध;

	शेष:
		netdev_err(netdev, "Got invalid cap rsp %d\n",
			   crq->query_capability.capability);
	पूर्ण

out:
	अगर (atomic_पढ़ो(&adapter->running_cap_crqs) == 0) अणु
		adapter->रुको_capability = false;
		send_request_cap(adapter, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक send_query_phys_parms(काष्ठा ibmvnic_adapter *adapter)
अणु
	जोड़ ibmvnic_crq crq;
	पूर्णांक rc;

	स_रखो(&crq, 0, माप(crq));
	crq.query_phys_parms.first = IBMVNIC_CRQ_CMD;
	crq.query_phys_parms.cmd = QUERY_PHYS_PARMS;

	mutex_lock(&adapter->fw_lock);
	adapter->fw_करोne_rc = 0;
	reinit_completion(&adapter->fw_करोne);

	rc = ibmvnic_send_crq(adapter, &crq);
	अगर (rc) अणु
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण

	rc = ibmvnic_रुको_क्रम_completion(adapter, &adapter->fw_करोne, 10000);
	अगर (rc) अणु
		mutex_unlock(&adapter->fw_lock);
		वापस rc;
	पूर्ण

	mutex_unlock(&adapter->fw_lock);
	वापस adapter->fw_करोne_rc ? -EIO : 0;
पूर्ण

अटल पूर्णांक handle_query_phys_parms_rsp(जोड़ ibmvnic_crq *crq,
				       काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक rc;
	__be32 rspeed = cpu_to_be32(crq->query_phys_parms_rsp.speed);

	rc = crq->query_phys_parms_rsp.rc.code;
	अगर (rc) अणु
		netdev_err(netdev, "Error %d in QUERY_PHYS_PARMS\n", rc);
		वापस rc;
	पूर्ण
	चयन (rspeed) अणु
	हाल IBMVNIC_10MBPS:
		adapter->speed = SPEED_10;
		अवरोध;
	हाल IBMVNIC_100MBPS:
		adapter->speed = SPEED_100;
		अवरोध;
	हाल IBMVNIC_1GBPS:
		adapter->speed = SPEED_1000;
		अवरोध;
	हाल IBMVNIC_10GBPS:
		adapter->speed = SPEED_10000;
		अवरोध;
	हाल IBMVNIC_25GBPS:
		adapter->speed = SPEED_25000;
		अवरोध;
	हाल IBMVNIC_40GBPS:
		adapter->speed = SPEED_40000;
		अवरोध;
	हाल IBMVNIC_50GBPS:
		adapter->speed = SPEED_50000;
		अवरोध;
	हाल IBMVNIC_100GBPS:
		adapter->speed = SPEED_100000;
		अवरोध;
	हाल IBMVNIC_200GBPS:
		adapter->speed = SPEED_200000;
		अवरोध;
	शेष:
		अगर (netअगर_carrier_ok(netdev))
			netdev_warn(netdev, "Unknown speed 0x%08x\n", rspeed);
		adapter->speed = SPEED_UNKNOWN;
	पूर्ण
	अगर (crq->query_phys_parms_rsp.flags1 & IBMVNIC_FULL_DUPLEX)
		adapter->duplex = DUPLEX_FULL;
	अन्यथा अगर (crq->query_phys_parms_rsp.flags1 & IBMVNIC_HALF_DUPLEX)
		adapter->duplex = DUPLEX_HALF;
	अन्यथा
		adapter->duplex = DUPLEX_UNKNOWN;

	वापस rc;
पूर्ण

अटल व्योम ibmvnic_handle_crq(जोड़ ibmvnic_crq *crq,
			       काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_generic_crq *gen_crq = &crq->generic;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा device *dev = &adapter->vdev->dev;
	u64 *u64_crq = (u64 *)crq;
	दीर्घ rc;

	netdev_dbg(netdev, "Handling CRQ: %016lx %016lx\n",
		   (अचिन्हित दीर्घ)cpu_to_be64(u64_crq[0]),
		   (अचिन्हित दीर्घ)cpu_to_be64(u64_crq[1]));
	चयन (gen_crq->first) अणु
	हाल IBMVNIC_CRQ_INIT_RSP:
		चयन (gen_crq->cmd) अणु
		हाल IBMVNIC_CRQ_INIT:
			dev_info(dev, "Partner initialized\n");
			adapter->from_passive_init = true;
			/* Discard any stale login responses from prev reset.
			 * CHECK: should we clear even on INIT_COMPLETE?
			 */
			adapter->login_pending = false;

			अगर (!completion_करोne(&adapter->init_करोne)) अणु
				complete(&adapter->init_करोne);
				adapter->init_करोne_rc = -EIO;
			पूर्ण
			rc = ibmvnic_reset(adapter, VNIC_RESET_FAILOVER);
			अगर (rc && rc != -EBUSY) अणु
				/* We were unable to schedule the failover
				 * reset either because the adapter was still
				 * probing (eg: during kexec) or we could not
				 * allocate memory. Clear the failover_pending
				 * flag since no one अन्यथा will. We ignore
				 * EBUSY because it means either FAILOVER reset
				 * is alपढ़ोy scheduled or the adapter is
				 * being हटाओd.
				 */
				netdev_err(netdev,
					   "Error %ld scheduling failover reset\n",
					   rc);
				adapter->failover_pending = false;
			पूर्ण
			अवरोध;
		हाल IBMVNIC_CRQ_INIT_COMPLETE:
			dev_info(dev, "Partner initialization complete\n");
			adapter->crq.active = true;
			send_version_xchg(adapter);
			अवरोध;
		शेष:
			dev_err(dev, "Unknown crq cmd: %d\n", gen_crq->cmd);
		पूर्ण
		वापस;
	हाल IBMVNIC_CRQ_XPORT_EVENT:
		netअगर_carrier_off(netdev);
		adapter->crq.active = false;
		/* terminate any thपढ़ो रुकोing क्रम a response
		 * from the device
		 */
		अगर (!completion_करोne(&adapter->fw_करोne)) अणु
			adapter->fw_करोne_rc = -EIO;
			complete(&adapter->fw_करोne);
		पूर्ण
		अगर (!completion_करोne(&adapter->stats_करोne))
			complete(&adapter->stats_करोne);
		अगर (test_bit(0, &adapter->resetting))
			adapter->क्रमce_reset_recovery = true;
		अगर (gen_crq->cmd == IBMVNIC_PARTITION_MIGRATED) अणु
			dev_info(dev, "Migrated, re-enabling adapter\n");
			ibmvnic_reset(adapter, VNIC_RESET_MOBILITY);
		पूर्ण अन्यथा अगर (gen_crq->cmd == IBMVNIC_DEVICE_FAILOVER) अणु
			dev_info(dev, "Backing device failover detected\n");
			adapter->failover_pending = true;
		पूर्ण अन्यथा अणु
			/* The adapter lost the connection */
			dev_err(dev, "Virtual Adapter failed (rc=%d)\n",
				gen_crq->cmd);
			ibmvnic_reset(adapter, VNIC_RESET_FATAL);
		पूर्ण
		वापस;
	हाल IBMVNIC_CRQ_CMD_RSP:
		अवरोध;
	शेष:
		dev_err(dev, "Got an invalid msg type 0x%02x\n",
			gen_crq->first);
		वापस;
	पूर्ण

	चयन (gen_crq->cmd) अणु
	हाल VERSION_EXCHANGE_RSP:
		rc = crq->version_exchange_rsp.rc.code;
		अगर (rc) अणु
			dev_err(dev, "Error %ld in VERSION_EXCHG_RSP\n", rc);
			अवरोध;
		पूर्ण
		ibmvnic_version =
			    be16_to_cpu(crq->version_exchange_rsp.version);
		dev_info(dev, "Partner protocol version is %d\n",
			 ibmvnic_version);
		send_query_cap(adapter);
		अवरोध;
	हाल QUERY_CAPABILITY_RSP:
		handle_query_cap_rsp(crq, adapter);
		अवरोध;
	हाल QUERY_MAP_RSP:
		handle_query_map_rsp(crq, adapter);
		अवरोध;
	हाल REQUEST_MAP_RSP:
		adapter->fw_करोne_rc = crq->request_map_rsp.rc.code;
		complete(&adapter->fw_करोne);
		अवरोध;
	हाल REQUEST_UNMAP_RSP:
		handle_request_unmap_rsp(crq, adapter);
		अवरोध;
	हाल REQUEST_CAPABILITY_RSP:
		handle_request_cap_rsp(crq, adapter);
		अवरोध;
	हाल LOGIN_RSP:
		netdev_dbg(netdev, "Got Login Response\n");
		handle_login_rsp(crq, adapter);
		अवरोध;
	हाल LOGICAL_LINK_STATE_RSP:
		netdev_dbg(netdev,
			   "Got Logical Link State Response, state: %d rc: %d\n",
			   crq->logical_link_state_rsp.link_state,
			   crq->logical_link_state_rsp.rc.code);
		adapter->logical_link_state =
		    crq->logical_link_state_rsp.link_state;
		adapter->init_करोne_rc = crq->logical_link_state_rsp.rc.code;
		complete(&adapter->init_करोne);
		अवरोध;
	हाल LINK_STATE_INDICATION:
		netdev_dbg(netdev, "Got Logical Link State Indication\n");
		adapter->phys_link_state =
		    crq->link_state_indication.phys_link_state;
		adapter->logical_link_state =
		    crq->link_state_indication.logical_link_state;
		अगर (adapter->phys_link_state && adapter->logical_link_state)
			netअगर_carrier_on(netdev);
		अन्यथा
			netअगर_carrier_off(netdev);
		अवरोध;
	हाल CHANGE_MAC_ADDR_RSP:
		netdev_dbg(netdev, "Got MAC address change Response\n");
		adapter->fw_करोne_rc = handle_change_mac_rsp(crq, adapter);
		अवरोध;
	हाल ERROR_INDICATION:
		netdev_dbg(netdev, "Got Error Indication\n");
		handle_error_indication(crq, adapter);
		अवरोध;
	हाल REQUEST_STATISTICS_RSP:
		netdev_dbg(netdev, "Got Statistics Response\n");
		complete(&adapter->stats_करोne);
		अवरोध;
	हाल QUERY_IP_OFFLOAD_RSP:
		netdev_dbg(netdev, "Got Query IP offload Response\n");
		handle_query_ip_offload_rsp(adapter);
		अवरोध;
	हाल MULTICAST_CTRL_RSP:
		netdev_dbg(netdev, "Got multicast control Response\n");
		अवरोध;
	हाल CONTROL_IP_OFFLOAD_RSP:
		netdev_dbg(netdev, "Got Control IP offload Response\n");
		dma_unmap_single(dev, adapter->ip_offload_ctrl_tok,
				 माप(adapter->ip_offload_ctrl),
				 DMA_TO_DEVICE);
		complete(&adapter->init_करोne);
		अवरोध;
	हाल COLLECT_FW_TRACE_RSP:
		netdev_dbg(netdev, "Got Collect firmware trace Response\n");
		complete(&adapter->fw_करोne);
		अवरोध;
	हाल GET_VPD_SIZE_RSP:
		handle_vpd_size_rsp(crq, adapter);
		अवरोध;
	हाल GET_VPD_RSP:
		handle_vpd_rsp(crq, adapter);
		अवरोध;
	हाल QUERY_PHYS_PARMS_RSP:
		adapter->fw_करोne_rc = handle_query_phys_parms_rsp(crq, adapter);
		complete(&adapter->fw_करोne);
		अवरोध;
	शेष:
		netdev_err(netdev, "Got an invalid cmd type 0x%02x\n",
			   gen_crq->cmd);
	पूर्ण
पूर्ण

अटल irqवापस_t ibmvnic_पूर्णांकerrupt(पूर्णांक irq, व्योम *instance)
अणु
	काष्ठा ibmvnic_adapter *adapter = instance;

	tasklet_schedule(&adapter->tasklet);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ibmvnic_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ibmvnic_adapter *adapter = from_tasklet(adapter, t, tasklet);
	काष्ठा ibmvnic_crq_queue *queue = &adapter->crq;
	जोड़ ibmvnic_crq *crq;
	अचिन्हित दीर्घ flags;
	bool करोne = false;

	spin_lock_irqsave(&queue->lock, flags);
	जबतक (!करोne) अणु
		/* Pull all the valid messages off the CRQ */
		जबतक ((crq = ibmvnic_next_crq(adapter)) != शून्य) अणु
			/* This barrier makes sure ibmvnic_next_crq()'s
			 * crq->generic.first & IBMVNIC_CRQ_CMD_RSP is loaded
			 * beक्रमe ibmvnic_handle_crq()'s
			 * चयन(gen_crq->first) and चयन(gen_crq->cmd).
			 */
			dma_rmb();
			ibmvnic_handle_crq(crq, adapter);
			crq->generic.first = 0;
		पूर्ण

		/* reमुख्य in tasklet until all
		 * capabilities responses are received
		 */
		अगर (!adapter->रुको_capability)
			करोne = true;
	पूर्ण
	/* अगर capabilities CRQ's were sent in this tasklet, the following
	 * tasklet must रुको until all responses are received
	 */
	अगर (atomic_पढ़ो(&adapter->running_cap_crqs) != 0)
		adapter->रुको_capability = true;
	spin_unlock_irqrestore(&queue->lock, flags);
पूर्ण

अटल पूर्णांक ibmvnic_reenable_crq_queue(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा vio_dev *vdev = adapter->vdev;
	पूर्णांक rc;

	करो अणु
		rc = plpar_hcall_norets(H_ENABLE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_IN_PROGRESS || rc == H_BUSY || H_IS_LONG_BUSY(rc));

	अगर (rc)
		dev_err(&vdev->dev, "Error enabling adapter (rc=%d)\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक ibmvnic_reset_crq(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_crq_queue *crq = &adapter->crq;
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा vio_dev *vdev = adapter->vdev;
	पूर्णांक rc;

	/* Close the CRQ */
	करो अणु
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	/* Clean out the queue */
	अगर (!crq->msgs)
		वापस -EINVAL;

	स_रखो(crq->msgs, 0, PAGE_SIZE);
	crq->cur = 0;
	crq->active = false;

	/* And re-खोलो it again */
	rc = plpar_hcall_norets(H_REG_CRQ, vdev->unit_address,
				crq->msg_token, PAGE_SIZE);

	अगर (rc == H_CLOSED)
		/* Adapter is good, but other end is not पढ़ोy */
		dev_warn(dev, "Partner adapter not ready\n");
	अन्यथा अगर (rc != 0)
		dev_warn(dev, "Couldn't register crq (rc=%d)\n", rc);

	वापस rc;
पूर्ण

अटल व्योम release_crq_queue(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_crq_queue *crq = &adapter->crq;
	काष्ठा vio_dev *vdev = adapter->vdev;
	दीर्घ rc;

	अगर (!crq->msgs)
		वापस;

	netdev_dbg(adapter->netdev, "Releasing CRQ\n");
	मुक्त_irq(vdev->irq, adapter);
	tasklet_समाप्त(&adapter->tasklet);
	करो अणु
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));

	dma_unmap_single(&vdev->dev, crq->msg_token, PAGE_SIZE,
			 DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)crq->msgs);
	crq->msgs = शून्य;
	crq->active = false;
पूर्ण

अटल पूर्णांक init_crq_queue(काष्ठा ibmvnic_adapter *adapter)
अणु
	काष्ठा ibmvnic_crq_queue *crq = &adapter->crq;
	काष्ठा device *dev = &adapter->vdev->dev;
	काष्ठा vio_dev *vdev = adapter->vdev;
	पूर्णांक rc, retrc = -ENOMEM;

	अगर (crq->msgs)
		वापस 0;

	crq->msgs = (जोड़ ibmvnic_crq *)get_zeroed_page(GFP_KERNEL);
	/* Should we allocate more than one page? */

	अगर (!crq->msgs)
		वापस -ENOMEM;

	crq->size = PAGE_SIZE / माप(*crq->msgs);
	crq->msg_token = dma_map_single(dev, crq->msgs, PAGE_SIZE,
					DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, crq->msg_token))
		जाओ map_failed;

	rc = plpar_hcall_norets(H_REG_CRQ, vdev->unit_address,
				crq->msg_token, PAGE_SIZE);

	अगर (rc == H_RESOURCE)
		/* maybe kexecing and resource is busy. try a reset */
		rc = ibmvnic_reset_crq(adapter);
	retrc = rc;

	अगर (rc == H_CLOSED) अणु
		dev_warn(dev, "Partner adapter not ready\n");
	पूर्ण अन्यथा अगर (rc) अणु
		dev_warn(dev, "Error %d opening adapter\n", rc);
		जाओ reg_crq_failed;
	पूर्ण

	retrc = 0;

	tasklet_setup(&adapter->tasklet, (व्योम *)ibmvnic_tasklet);

	netdev_dbg(adapter->netdev, "registering irq 0x%x\n", vdev->irq);
	snम_लिखो(crq->name, माप(crq->name), "ibmvnic-%x",
		 adapter->vdev->unit_address);
	rc = request_irq(vdev->irq, ibmvnic_पूर्णांकerrupt, 0, crq->name, adapter);
	अगर (rc) अणु
		dev_err(dev, "Couldn't register irq 0x%x. rc=%d\n",
			vdev->irq, rc);
		जाओ req_irq_failed;
	पूर्ण

	rc = vio_enable_पूर्णांकerrupts(vdev);
	अगर (rc) अणु
		dev_err(dev, "Error %d enabling interrupts\n", rc);
		जाओ req_irq_failed;
	पूर्ण

	crq->cur = 0;
	spin_lock_init(&crq->lock);

	वापस retrc;

req_irq_failed:
	tasklet_समाप्त(&adapter->tasklet);
	करो अणु
		rc = plpar_hcall_norets(H_FREE_CRQ, vdev->unit_address);
	पूर्ण जबतक (rc == H_BUSY || H_IS_LONG_BUSY(rc));
reg_crq_failed:
	dma_unmap_single(dev, crq->msg_token, PAGE_SIZE, DMA_BIसूचीECTIONAL);
map_failed:
	मुक्त_page((अचिन्हित दीर्घ)crq->msgs);
	crq->msgs = शून्य;
	वापस retrc;
पूर्ण

अटल पूर्णांक ibmvnic_reset_init(काष्ठा ibmvnic_adapter *adapter, bool reset)
अणु
	काष्ठा device *dev = &adapter->vdev->dev;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(20000);
	u64 old_num_rx_queues = adapter->req_rx_queues;
	u64 old_num_tx_queues = adapter->req_tx_queues;
	पूर्णांक rc;

	adapter->from_passive_init = false;

	अगर (reset)
		reinit_completion(&adapter->init_करोne);

	adapter->init_करोne_rc = 0;
	rc = ibmvnic_send_crq_init(adapter);
	अगर (rc) अणु
		dev_err(dev, "Send crq init failed with error %d\n", rc);
		वापस rc;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&adapter->init_करोne, समयout)) अणु
		dev_err(dev, "Initialization sequence timed out\n");
		वापस -1;
	पूर्ण

	अगर (adapter->init_करोne_rc) अणु
		release_crq_queue(adapter);
		वापस adapter->init_करोne_rc;
	पूर्ण

	अगर (adapter->from_passive_init) अणु
		adapter->state = VNIC_OPEN;
		adapter->from_passive_init = false;
		वापस -1;
	पूर्ण

	अगर (reset &&
	    test_bit(0, &adapter->resetting) && !adapter->रुको_क्रम_reset &&
	    adapter->reset_reason != VNIC_RESET_MOBILITY) अणु
		अगर (adapter->req_rx_queues != old_num_rx_queues ||
		    adapter->req_tx_queues != old_num_tx_queues) अणु
			release_sub_crqs(adapter, 0);
			rc = init_sub_crqs(adapter);
		पूर्ण अन्यथा अणु
			rc = reset_sub_crq_queues(adapter);
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = init_sub_crqs(adapter);
	पूर्ण

	अगर (rc) अणु
		dev_err(dev, "Initialization of sub crqs failed\n");
		release_crq_queue(adapter);
		वापस rc;
	पूर्ण

	rc = init_sub_crq_irqs(adapter);
	अगर (rc) अणु
		dev_err(dev, "Failed to initialize sub crq irqs\n");
		release_crq_queue(adapter);
	पूर्ण

	वापस rc;
पूर्ण

अटल काष्ठा device_attribute dev_attr_failover;

अटल पूर्णांक ibmvnic_probe(काष्ठा vio_dev *dev, स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा ibmvnic_adapter *adapter;
	काष्ठा net_device *netdev;
	अचिन्हित अक्षर *mac_addr_p;
	पूर्णांक rc;

	dev_dbg(&dev->dev, "entering ibmvnic_probe for UA 0x%x\n",
		dev->unit_address);

	mac_addr_p = (अचिन्हित अक्षर *)vio_get_attribute(dev,
							VETH_MAC_ADDR, शून्य);
	अगर (!mac_addr_p) अणु
		dev_err(&dev->dev,
			"(%s:%3.3d) ERROR: Can't find MAC_ADDR attribute\n",
			__खाता__, __LINE__);
		वापस 0;
	पूर्ण

	netdev = alloc_etherdev_mq(माप(काष्ठा ibmvnic_adapter),
				   IBMVNIC_MAX_QUEUES);
	अगर (!netdev)
		वापस -ENOMEM;

	adapter = netdev_priv(netdev);
	adapter->state = VNIC_PROBING;
	dev_set_drvdata(&dev->dev, netdev);
	adapter->vdev = dev;
	adapter->netdev = netdev;
	adapter->login_pending = false;

	ether_addr_copy(adapter->mac_addr, mac_addr_p);
	ether_addr_copy(netdev->dev_addr, adapter->mac_addr);
	netdev->irq = dev->irq;
	netdev->netdev_ops = &ibmvnic_netdev_ops;
	netdev->ethtool_ops = &ibmvnic_ethtool_ops;
	SET_NETDEV_DEV(netdev, &dev->dev);

	INIT_WORK(&adapter->ibmvnic_reset, __ibmvnic_reset);
	INIT_DELAYED_WORK(&adapter->ibmvnic_delayed_reset,
			  __ibmvnic_delayed_reset);
	INIT_LIST_HEAD(&adapter->rwi_list);
	spin_lock_init(&adapter->rwi_lock);
	spin_lock_init(&adapter->state_lock);
	mutex_init(&adapter->fw_lock);
	init_completion(&adapter->init_करोne);
	init_completion(&adapter->fw_करोne);
	init_completion(&adapter->reset_करोne);
	init_completion(&adapter->stats_करोne);
	clear_bit(0, &adapter->resetting);

	करो अणु
		rc = init_crq_queue(adapter);
		अगर (rc) अणु
			dev_err(&dev->dev, "Couldn't initialize crq. rc=%d\n",
				rc);
			जाओ ibmvnic_init_fail;
		पूर्ण

		rc = ibmvnic_reset_init(adapter, false);
		अगर (rc && rc != EAGAIN)
			जाओ ibmvnic_init_fail;
	पूर्ण जबतक (rc == EAGAIN);

	rc = init_stats_buffers(adapter);
	अगर (rc)
		जाओ ibmvnic_init_fail;

	rc = init_stats_token(adapter);
	अगर (rc)
		जाओ ibmvnic_stats_fail;

	netdev->mtu = adapter->req_mtu - ETH_HLEN;
	netdev->min_mtu = adapter->min_mtu - ETH_HLEN;
	netdev->max_mtu = adapter->max_mtu - ETH_HLEN;

	rc = device_create_file(&dev->dev, &dev_attr_failover);
	अगर (rc)
		जाओ ibmvnic_dev_file_err;

	netअगर_carrier_off(netdev);
	rc = रेजिस्टर_netdev(netdev);
	अगर (rc) अणु
		dev_err(&dev->dev, "failed to register netdev rc=%d\n", rc);
		जाओ ibmvnic_रेजिस्टर_fail;
	पूर्ण
	dev_info(&dev->dev, "ibmvnic registered\n");

	adapter->state = VNIC_PROBED;

	adapter->रुको_क्रम_reset = false;
	adapter->last_reset_समय = jअगरfies;
	वापस 0;

ibmvnic_रेजिस्टर_fail:
	device_हटाओ_file(&dev->dev, &dev_attr_failover);

ibmvnic_dev_file_err:
	release_stats_token(adapter);

ibmvnic_stats_fail:
	release_stats_buffers(adapter);

ibmvnic_init_fail:
	release_sub_crqs(adapter, 1);
	release_crq_queue(adapter);
	mutex_destroy(&adapter->fw_lock);
	मुक्त_netdev(netdev);

	वापस rc;
पूर्ण

अटल व्योम ibmvnic_हटाओ(काष्ठा vio_dev *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(&dev->dev);
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->state_lock, flags);

	/* If ibmvnic_reset() is scheduling a reset, रुको क्रम it to
	 * finish. Then, set the state to REMOVING to prevent it from
	 * scheduling any more work and to have reset functions ignore
	 * any resets that have alपढ़ोy been scheduled. Drop the lock
	 * after setting state, so __ibmvnic_reset() which is called
	 * from the flush_work() below, can make progress.
	 */
	spin_lock(&adapter->rwi_lock);
	adapter->state = VNIC_REMOVING;
	spin_unlock(&adapter->rwi_lock);

	spin_unlock_irqrestore(&adapter->state_lock, flags);

	flush_work(&adapter->ibmvnic_reset);
	flush_delayed_work(&adapter->ibmvnic_delayed_reset);

	rtnl_lock();
	unरेजिस्टर_netdevice(netdev);

	release_resources(adapter);
	release_sub_crqs(adapter, 1);
	release_crq_queue(adapter);

	release_stats_token(adapter);
	release_stats_buffers(adapter);

	adapter->state = VNIC_REMOVED;

	rtnl_unlock();
	mutex_destroy(&adapter->fw_lock);
	device_हटाओ_file(&dev->dev, &dev_attr_failover);
	मुक्त_netdev(netdev);
	dev_set_drvdata(&dev->dev, शून्य);
पूर्ण

अटल sमाप_प्रकार failover_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ retbuf[PLPAR_HCALL_बफ_मानE];
	__be64 session_token;
	दीर्घ rc;

	अगर (!sysfs_streq(buf, "1"))
		वापस -EINVAL;

	rc = plpar_hcall(H_VIOCTL, retbuf, adapter->vdev->unit_address,
			 H_GET_SESSION_TOKEN, 0, 0, 0);
	अगर (rc) अणु
		netdev_err(netdev, "Couldn't retrieve session token, rc %ld\n",
			   rc);
		जाओ last_resort;
	पूर्ण

	session_token = (__be64)retbuf[0];
	netdev_dbg(netdev, "Initiating client failover, session id %llx\n",
		   be64_to_cpu(session_token));
	rc = plpar_hcall_norets(H_VIOCTL, adapter->vdev->unit_address,
				H_SESSION_ERR_DETECTED, session_token, 0, 0);
	अगर (rc)
		netdev_err(netdev,
			   "H_VIOCTL initiated failover failed, rc %ld\n",
			   rc);

last_resort:
	netdev_dbg(netdev, "Trying to send CRQ_CMD, the last resort\n");
	ibmvnic_reset(adapter, VNIC_RESET_FAILOVER);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(failover);

अटल अचिन्हित दीर्घ ibmvnic_get_desired_dma(काष्ठा vio_dev *vdev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(&vdev->dev);
	काष्ठा ibmvnic_adapter *adapter;
	काष्ठा iommu_table *tbl;
	अचिन्हित दीर्घ ret = 0;
	पूर्णांक i;

	tbl = get_iommu_table_base(&vdev->dev);

	/* netdev inits at probe समय aदीर्घ with the काष्ठाures we need below*/
	अगर (!netdev)
		वापस IOMMU_PAGE_ALIGN(IBMVNIC_IO_ENTITLEMENT_DEFAULT, tbl);

	adapter = netdev_priv(netdev);

	ret += PAGE_SIZE; /* the crq message queue */
	ret += IOMMU_PAGE_ALIGN(माप(काष्ठा ibmvnic_statistics), tbl);

	क्रम (i = 0; i < adapter->req_tx_queues + adapter->req_rx_queues; i++)
		ret += 4 * PAGE_SIZE; /* the scrq message queue */

	क्रम (i = 0; i < adapter->num_active_rx_pools; i++)
		ret += adapter->rx_pool[i].size *
		    IOMMU_PAGE_ALIGN(adapter->rx_pool[i].buff_size, tbl);

	वापस ret;
पूर्ण

अटल पूर्णांक ibmvnic_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा ibmvnic_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->state != VNIC_OPEN)
		वापस 0;

	tasklet_schedule(&adapter->tasklet);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vio_device_id ibmvnic_device_table[] = अणु
	अणु"network", "IBM,vnic"पूर्ण,
	अणु"", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, ibmvnic_device_table);

अटल स्थिर काष्ठा dev_pm_ops ibmvnic_pm_ops = अणु
	.resume = ibmvnic_resume
पूर्ण;

अटल काष्ठा vio_driver ibmvnic_driver = अणु
	.id_table       = ibmvnic_device_table,
	.probe          = ibmvnic_probe,
	.हटाओ         = ibmvnic_हटाओ,
	.get_desired_dma = ibmvnic_get_desired_dma,
	.name		= ibmvnic_driver_name,
	.pm		= &ibmvnic_pm_ops,
पूर्ण;

/* module functions */
अटल पूर्णांक __init ibmvnic_module_init(व्योम)
अणु
	pr_info("%s: %s %s\n", ibmvnic_driver_name, ibmvnic_driver_string,
		IBMVNIC_DRIVER_VERSION);

	वापस vio_रेजिस्टर_driver(&ibmvnic_driver);
पूर्ण

अटल व्योम __निकास ibmvnic_module_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&ibmvnic_driver);
पूर्ण

module_init(ibmvnic_module_init);
module_निकास(ibmvnic_module_निकास);
