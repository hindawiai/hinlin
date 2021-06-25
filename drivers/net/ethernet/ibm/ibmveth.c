<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM Power Virtual Ethernet Device Driver
 *
 * Copyright (C) IBM Corporation, 2003, 2010
 *
 * Authors: Dave Larson <larson1@us.ibm.com>
 *	    Santiago Leon <santil@linux.vnet.ibm.com>
 *	    Brian King <brking@linux.vnet.ibm.com>
 *	    Robert Jennings <rcj@linux.vnet.ibm.com>
 *	    Anton Blanअक्षरd <anton@au.ibm.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/pm.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/vपन.स>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/firmware.h>
#समावेश <net/tcp.h>
#समावेश <net/ip6_checksum.h>

#समावेश "ibmveth.h"

अटल irqवापस_t ibmveth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance);
अटल व्योम ibmveth_rxq_harvest_buffer(काष्ठा ibmveth_adapter *adapter);
अटल अचिन्हित दीर्घ ibmveth_get_desired_dma(काष्ठा vio_dev *vdev);

अटल काष्ठा kobj_type ktype_veth_pool;


अटल स्थिर अक्षर ibmveth_driver_name[] = "ibmveth";
अटल स्थिर अक्षर ibmveth_driver_string[] = "IBM Power Virtual Ethernet Driver";
#घोषणा ibmveth_driver_version "1.06"

MODULE_AUTHOR("Santiago Leon <santil@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("IBM Power Virtual Ethernet Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(ibmveth_driver_version);

अटल अचिन्हित पूर्णांक tx_copyअवरोध __पढ़ो_mostly = 128;
module_param(tx_copyअवरोध, uपूर्णांक, 0644);
MODULE_PARM_DESC(tx_copyअवरोध,
	"Maximum size of packet that is copied to a new buffer on transmit");

अटल अचिन्हित पूर्णांक rx_copyअवरोध __पढ़ो_mostly = 128;
module_param(rx_copyअवरोध, uपूर्णांक, 0644);
MODULE_PARM_DESC(rx_copyअवरोध,
	"Maximum size of packet that is copied to a new buffer on receive");

अटल अचिन्हित पूर्णांक rx_flush __पढ़ो_mostly = 0;
module_param(rx_flush, uपूर्णांक, 0644);
MODULE_PARM_DESC(rx_flush, "Flush receive buffers before use");

अटल bool old_large_send __पढ़ो_mostly;
module_param(old_large_send, bool, 0444);
MODULE_PARM_DESC(old_large_send,
	"Use old large send method on firmware that supports the new method");

काष्ठा ibmveth_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	पूर्णांक offset;
पूर्ण;

#घोषणा IBMVETH_STAT_OFF(stat) दुरत्व(काष्ठा ibmveth_adapter, stat)
#घोषणा IBMVETH_GET_STAT(a, off) *((u64 *)(((अचिन्हित दीर्घ)(a)) + off))

अटल काष्ठा ibmveth_stat ibmveth_stats[] = अणु
	अणु "replenish_task_cycles", IBMVETH_STAT_OFF(replenish_task_cycles) पूर्ण,
	अणु "replenish_no_mem", IBMVETH_STAT_OFF(replenish_no_mem) पूर्ण,
	अणु "replenish_add_buff_failure",
			IBMVETH_STAT_OFF(replenish_add_buff_failure) पूर्ण,
	अणु "replenish_add_buff_success",
			IBMVETH_STAT_OFF(replenish_add_buff_success) पूर्ण,
	अणु "rx_invalid_buffer", IBMVETH_STAT_OFF(rx_invalid_buffer) पूर्ण,
	अणु "rx_no_buffer", IBMVETH_STAT_OFF(rx_no_buffer) पूर्ण,
	अणु "tx_map_failed", IBMVETH_STAT_OFF(tx_map_failed) पूर्ण,
	अणु "tx_send_failed", IBMVETH_STAT_OFF(tx_send_failed) पूर्ण,
	अणु "fw_enabled_ipv4_csum", IBMVETH_STAT_OFF(fw_ipv4_csum_support) पूर्ण,
	अणु "fw_enabled_ipv6_csum", IBMVETH_STAT_OFF(fw_ipv6_csum_support) पूर्ण,
	अणु "tx_large_packets", IBMVETH_STAT_OFF(tx_large_packets) पूर्ण,
	अणु "rx_large_packets", IBMVETH_STAT_OFF(rx_large_packets) पूर्ण,
	अणु "fw_enabled_large_send", IBMVETH_STAT_OFF(fw_large_send_support) पूर्ण
पूर्ण;

/* simple methods of getting data from the current rxq entry */
अटल अंतरभूत u32 ibmveth_rxq_flags(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस be32_to_cpu(adapter->rx_queue.queue_addr[adapter->rx_queue.index].flags_off);
पूर्ण

अटल अंतरभूत पूर्णांक ibmveth_rxq_toggle(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस (ibmveth_rxq_flags(adapter) & IBMVETH_RXQ_TOGGLE) >>
			IBMVETH_RXQ_TOGGLE_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक ibmveth_rxq_pending_buffer(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस ibmveth_rxq_toggle(adapter) == adapter->rx_queue.toggle;
पूर्ण

अटल अंतरभूत पूर्णांक ibmveth_rxq_buffer_valid(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस ibmveth_rxq_flags(adapter) & IBMVETH_RXQ_VALID;
पूर्ण

अटल अंतरभूत पूर्णांक ibmveth_rxq_frame_offset(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस ibmveth_rxq_flags(adapter) & IBMVETH_RXQ_OFF_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ibmveth_rxq_large_packet(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस ibmveth_rxq_flags(adapter) & IBMVETH_RXQ_LRG_PKT;
पूर्ण

अटल अंतरभूत पूर्णांक ibmveth_rxq_frame_length(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस be32_to_cpu(adapter->rx_queue.queue_addr[adapter->rx_queue.index].length);
पूर्ण

अटल अंतरभूत पूर्णांक ibmveth_rxq_csum_good(काष्ठा ibmveth_adapter *adapter)
अणु
	वापस ibmveth_rxq_flags(adapter) & IBMVETH_RXQ_CSUM_GOOD;
पूर्ण

/* setup the initial settings क्रम a buffer pool */
अटल व्योम ibmveth_init_buffer_pool(काष्ठा ibmveth_buff_pool *pool,
				     u32 pool_index, u32 pool_size,
				     u32 buff_size, u32 pool_active)
अणु
	pool->size = pool_size;
	pool->index = pool_index;
	pool->buff_size = buff_size;
	pool->threshold = pool_size * 7 / 8;
	pool->active = pool_active;
पूर्ण

/* allocate and setup an buffer pool - called during खोलो */
अटल पूर्णांक ibmveth_alloc_buffer_pool(काष्ठा ibmveth_buff_pool *pool)
अणु
	पूर्णांक i;

	pool->मुक्त_map = kदो_स्मृति_array(pool->size, माप(u16), GFP_KERNEL);

	अगर (!pool->मुक्त_map)
		वापस -1;

	pool->dma_addr = kसुस्मृति(pool->size, माप(dma_addr_t), GFP_KERNEL);
	अगर (!pool->dma_addr) अणु
		kमुक्त(pool->मुक्त_map);
		pool->मुक्त_map = शून्य;
		वापस -1;
	पूर्ण

	pool->skbuff = kसुस्मृति(pool->size, माप(व्योम *), GFP_KERNEL);

	अगर (!pool->skbuff) अणु
		kमुक्त(pool->dma_addr);
		pool->dma_addr = शून्य;

		kमुक्त(pool->मुक्त_map);
		pool->मुक्त_map = शून्य;
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < pool->size; ++i)
		pool->मुक्त_map[i] = i;

	atomic_set(&pool->available, 0);
	pool->producer_index = 0;
	pool->consumer_index = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ibmveth_flush_buffer(व्योम *addr, अचिन्हित दीर्घ length)
अणु
	अचिन्हित दीर्घ offset;

	क्रम (offset = 0; offset < length; offset += SMP_CACHE_BYTES)
		यंत्र("dcbfl %0,%1" :: "b" (addr), "r" (offset));
पूर्ण

/* replenish the buffers क्रम a pool.  note that we करोn't need to
 * skb_reserve these since they are used क्रम incoming...
 */
अटल व्योम ibmveth_replenish_buffer_pool(काष्ठा ibmveth_adapter *adapter,
					  काष्ठा ibmveth_buff_pool *pool)
अणु
	u32 i;
	u32 count = pool->size - atomic_पढ़ो(&pool->available);
	u32 buffers_added = 0;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक मुक्त_index, index;
	u64 correlator;
	अचिन्हित दीर्घ lpar_rc;
	dma_addr_t dma_addr;

	mb();

	क्रम (i = 0; i < count; ++i) अणु
		जोड़ ibmveth_buf_desc desc;

		skb = netdev_alloc_skb(adapter->netdev, pool->buff_size);

		अगर (!skb) अणु
			netdev_dbg(adapter->netdev,
				   "replenish: unable to allocate skb\n");
			adapter->replenish_no_mem++;
			अवरोध;
		पूर्ण

		मुक्त_index = pool->consumer_index;
		pool->consumer_index++;
		अगर (pool->consumer_index >= pool->size)
			pool->consumer_index = 0;
		index = pool->मुक्त_map[मुक्त_index];

		BUG_ON(index == IBM_VETH_INVALID_MAP);
		BUG_ON(pool->skbuff[index] != शून्य);

		dma_addr = dma_map_single(&adapter->vdev->dev, skb->data,
				pool->buff_size, DMA_FROM_DEVICE);

		अगर (dma_mapping_error(&adapter->vdev->dev, dma_addr))
			जाओ failure;

		pool->मुक्त_map[मुक्त_index] = IBM_VETH_INVALID_MAP;
		pool->dma_addr[index] = dma_addr;
		pool->skbuff[index] = skb;

		correlator = ((u64)pool->index << 32) | index;
		*(u64 *)skb->data = correlator;

		desc.fields.flags_len = IBMVETH_BUF_VALID | pool->buff_size;
		desc.fields.address = dma_addr;

		अगर (rx_flush) अणु
			अचिन्हित पूर्णांक len = min(pool->buff_size,
						adapter->netdev->mtu +
						IBMVETH_BUFF_OH);
			ibmveth_flush_buffer(skb->data, len);
		पूर्ण
		lpar_rc = h_add_logical_lan_buffer(adapter->vdev->unit_address,
						   desc.desc);

		अगर (lpar_rc != H_SUCCESS) अणु
			जाओ failure;
		पूर्ण अन्यथा अणु
			buffers_added++;
			adapter->replenish_add_buff_success++;
		पूर्ण
	पूर्ण

	mb();
	atomic_add(buffers_added, &(pool->available));
	वापस;

failure:
	pool->मुक्त_map[मुक्त_index] = index;
	pool->skbuff[index] = शून्य;
	अगर (pool->consumer_index == 0)
		pool->consumer_index = pool->size - 1;
	अन्यथा
		pool->consumer_index--;
	अगर (!dma_mapping_error(&adapter->vdev->dev, dma_addr))
		dma_unmap_single(&adapter->vdev->dev,
		                 pool->dma_addr[index], pool->buff_size,
		                 DMA_FROM_DEVICE);
	dev_kमुक्त_skb_any(skb);
	adapter->replenish_add_buff_failure++;

	mb();
	atomic_add(buffers_added, &(pool->available));
पूर्ण

/*
 * The final 8 bytes of the buffer list is a counter of frames dropped
 * because there was not a buffer in the buffer list capable of holding
 * the frame.
 */
अटल व्योम ibmveth_update_rx_no_buffer(काष्ठा ibmveth_adapter *adapter)
अणु
	__be64 *p = adapter->buffer_list_addr + 4096 - 8;

	adapter->rx_no_buffer = be64_to_cpup(p);
पूर्ण

/* replenish routine */
अटल व्योम ibmveth_replenish_task(काष्ठा ibmveth_adapter *adapter)
अणु
	पूर्णांक i;

	adapter->replenish_task_cycles++;

	क्रम (i = (IBMVETH_NUM_BUFF_POOLS - 1); i >= 0; i--) अणु
		काष्ठा ibmveth_buff_pool *pool = &adapter->rx_buff_pool[i];

		अगर (pool->active &&
		    (atomic_पढ़ो(&pool->available) < pool->threshold))
			ibmveth_replenish_buffer_pool(adapter, pool);
	पूर्ण

	ibmveth_update_rx_no_buffer(adapter);
पूर्ण

/* empty and मुक्त ana buffer pool - also used to करो cleanup in error paths */
अटल व्योम ibmveth_मुक्त_buffer_pool(काष्ठा ibmveth_adapter *adapter,
				     काष्ठा ibmveth_buff_pool *pool)
अणु
	पूर्णांक i;

	kमुक्त(pool->मुक्त_map);
	pool->मुक्त_map = शून्य;

	अगर (pool->skbuff && pool->dma_addr) अणु
		क्रम (i = 0; i < pool->size; ++i) अणु
			काष्ठा sk_buff *skb = pool->skbuff[i];
			अगर (skb) अणु
				dma_unmap_single(&adapter->vdev->dev,
						 pool->dma_addr[i],
						 pool->buff_size,
						 DMA_FROM_DEVICE);
				dev_kमुक्त_skb_any(skb);
				pool->skbuff[i] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (pool->dma_addr) अणु
		kमुक्त(pool->dma_addr);
		pool->dma_addr = शून्य;
	पूर्ण

	अगर (pool->skbuff) अणु
		kमुक्त(pool->skbuff);
		pool->skbuff = शून्य;
	पूर्ण
पूर्ण

/* हटाओ a buffer from a pool */
अटल व्योम ibmveth_हटाओ_buffer_from_pool(काष्ठा ibmveth_adapter *adapter,
					    u64 correlator)
अणु
	अचिन्हित पूर्णांक pool  = correlator >> 32;
	अचिन्हित पूर्णांक index = correlator & 0xffffffffUL;
	अचिन्हित पूर्णांक मुक्त_index;
	काष्ठा sk_buff *skb;

	BUG_ON(pool >= IBMVETH_NUM_BUFF_POOLS);
	BUG_ON(index >= adapter->rx_buff_pool[pool].size);

	skb = adapter->rx_buff_pool[pool].skbuff[index];

	BUG_ON(skb == शून्य);

	adapter->rx_buff_pool[pool].skbuff[index] = शून्य;

	dma_unmap_single(&adapter->vdev->dev,
			 adapter->rx_buff_pool[pool].dma_addr[index],
			 adapter->rx_buff_pool[pool].buff_size,
			 DMA_FROM_DEVICE);

	मुक्त_index = adapter->rx_buff_pool[pool].producer_index;
	adapter->rx_buff_pool[pool].producer_index++;
	अगर (adapter->rx_buff_pool[pool].producer_index >=
	    adapter->rx_buff_pool[pool].size)
		adapter->rx_buff_pool[pool].producer_index = 0;
	adapter->rx_buff_pool[pool].मुक्त_map[मुक्त_index] = index;

	mb();

	atomic_dec(&(adapter->rx_buff_pool[pool].available));
पूर्ण

/* get the current buffer on the rx queue */
अटल अंतरभूत काष्ठा sk_buff *ibmveth_rxq_get_buffer(काष्ठा ibmveth_adapter *adapter)
अणु
	u64 correlator = adapter->rx_queue.queue_addr[adapter->rx_queue.index].correlator;
	अचिन्हित पूर्णांक pool = correlator >> 32;
	अचिन्हित पूर्णांक index = correlator & 0xffffffffUL;

	BUG_ON(pool >= IBMVETH_NUM_BUFF_POOLS);
	BUG_ON(index >= adapter->rx_buff_pool[pool].size);

	वापस adapter->rx_buff_pool[pool].skbuff[index];
पूर्ण

/* recycle the current buffer on the rx queue */
अटल पूर्णांक ibmveth_rxq_recycle_buffer(काष्ठा ibmveth_adapter *adapter)
अणु
	u32 q_index = adapter->rx_queue.index;
	u64 correlator = adapter->rx_queue.queue_addr[q_index].correlator;
	अचिन्हित पूर्णांक pool = correlator >> 32;
	अचिन्हित पूर्णांक index = correlator & 0xffffffffUL;
	जोड़ ibmveth_buf_desc desc;
	अचिन्हित दीर्घ lpar_rc;
	पूर्णांक ret = 1;

	BUG_ON(pool >= IBMVETH_NUM_BUFF_POOLS);
	BUG_ON(index >= adapter->rx_buff_pool[pool].size);

	अगर (!adapter->rx_buff_pool[pool].active) अणु
		ibmveth_rxq_harvest_buffer(adapter);
		ibmveth_मुक्त_buffer_pool(adapter, &adapter->rx_buff_pool[pool]);
		जाओ out;
	पूर्ण

	desc.fields.flags_len = IBMVETH_BUF_VALID |
		adapter->rx_buff_pool[pool].buff_size;
	desc.fields.address = adapter->rx_buff_pool[pool].dma_addr[index];

	lpar_rc = h_add_logical_lan_buffer(adapter->vdev->unit_address, desc.desc);

	अगर (lpar_rc != H_SUCCESS) अणु
		netdev_dbg(adapter->netdev, "h_add_logical_lan_buffer failed "
			   "during recycle rc=%ld", lpar_rc);
		ibmveth_हटाओ_buffer_from_pool(adapter, adapter->rx_queue.queue_addr[adapter->rx_queue.index].correlator);
		ret = 0;
	पूर्ण

	अगर (++adapter->rx_queue.index == adapter->rx_queue.num_slots) अणु
		adapter->rx_queue.index = 0;
		adapter->rx_queue.toggle = !adapter->rx_queue.toggle;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम ibmveth_rxq_harvest_buffer(काष्ठा ibmveth_adapter *adapter)
अणु
	ibmveth_हटाओ_buffer_from_pool(adapter, adapter->rx_queue.queue_addr[adapter->rx_queue.index].correlator);

	अगर (++adapter->rx_queue.index == adapter->rx_queue.num_slots) अणु
		adapter->rx_queue.index = 0;
		adapter->rx_queue.toggle = !adapter->rx_queue.toggle;
	पूर्ण
पूर्ण

अटल पूर्णांक ibmveth_रेजिस्टर_logical_lan(काष्ठा ibmveth_adapter *adapter,
        जोड़ ibmveth_buf_desc rxq_desc, u64 mac_address)
अणु
	पूर्णांक rc, try_again = 1;

	/*
	 * After a kexec the adapter will still be खोलो, so our attempt to
	 * खोलो it will fail. So अगर we get a failure we मुक्त the adapter and
	 * try again, but only once.
	 */
retry:
	rc = h_रेजिस्टर_logical_lan(adapter->vdev->unit_address,
				    adapter->buffer_list_dma, rxq_desc.desc,
				    adapter->filter_list_dma, mac_address);

	अगर (rc != H_SUCCESS && try_again) अणु
		करो अणु
			rc = h_मुक्त_logical_lan(adapter->vdev->unit_address);
		पूर्ण जबतक (H_IS_LONG_BUSY(rc) || (rc == H_BUSY));

		try_again = 0;
		जाओ retry;
	पूर्ण

	वापस rc;
पूर्ण

अटल u64 ibmveth_encode_mac_addr(u8 *mac)
अणु
	पूर्णांक i;
	u64 encoded = 0;

	क्रम (i = 0; i < ETH_ALEN; i++)
		encoded = (encoded << 8) | mac[i];

	वापस encoded;
पूर्ण

अटल पूर्णांक ibmveth_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(netdev);
	u64 mac_address;
	पूर्णांक rxq_entries = 1;
	अचिन्हित दीर्घ lpar_rc;
	पूर्णांक rc;
	जोड़ ibmveth_buf_desc rxq_desc;
	पूर्णांक i;
	काष्ठा device *dev;

	netdev_dbg(netdev, "open starting\n");

	napi_enable(&adapter->napi);

	क्रम(i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++)
		rxq_entries += adapter->rx_buff_pool[i].size;

	rc = -ENOMEM;
	adapter->buffer_list_addr = (व्योम*) get_zeroed_page(GFP_KERNEL);
	अगर (!adapter->buffer_list_addr) अणु
		netdev_err(netdev, "unable to allocate list pages\n");
		जाओ out;
	पूर्ण

	adapter->filter_list_addr = (व्योम*) get_zeroed_page(GFP_KERNEL);
	अगर (!adapter->filter_list_addr) अणु
		netdev_err(netdev, "unable to allocate filter pages\n");
		जाओ out_मुक्त_buffer_list;
	पूर्ण

	dev = &adapter->vdev->dev;

	adapter->rx_queue.queue_len = माप(काष्ठा ibmveth_rx_q_entry) *
						rxq_entries;
	adapter->rx_queue.queue_addr =
		dma_alloc_coherent(dev, adapter->rx_queue.queue_len,
				   &adapter->rx_queue.queue_dma, GFP_KERNEL);
	अगर (!adapter->rx_queue.queue_addr)
		जाओ out_मुक्त_filter_list;

	adapter->buffer_list_dma = dma_map_single(dev,
			adapter->buffer_list_addr, 4096, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, adapter->buffer_list_dma)) अणु
		netdev_err(netdev, "unable to map buffer list pages\n");
		जाओ out_मुक्त_queue_mem;
	पूर्ण

	adapter->filter_list_dma = dma_map_single(dev,
			adapter->filter_list_addr, 4096, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, adapter->filter_list_dma)) अणु
		netdev_err(netdev, "unable to map filter list pages\n");
		जाओ out_unmap_buffer_list;
	पूर्ण

	adapter->rx_queue.index = 0;
	adapter->rx_queue.num_slots = rxq_entries;
	adapter->rx_queue.toggle = 1;

	mac_address = ibmveth_encode_mac_addr(netdev->dev_addr);

	rxq_desc.fields.flags_len = IBMVETH_BUF_VALID |
					adapter->rx_queue.queue_len;
	rxq_desc.fields.address = adapter->rx_queue.queue_dma;

	netdev_dbg(netdev, "buffer list @ 0x%p\n", adapter->buffer_list_addr);
	netdev_dbg(netdev, "filter list @ 0x%p\n", adapter->filter_list_addr);
	netdev_dbg(netdev, "receive q   @ 0x%p\n", adapter->rx_queue.queue_addr);

	h_vio_संकेत(adapter->vdev->unit_address, VIO_IRQ_DISABLE);

	lpar_rc = ibmveth_रेजिस्टर_logical_lan(adapter, rxq_desc, mac_address);

	अगर (lpar_rc != H_SUCCESS) अणु
		netdev_err(netdev, "h_register_logical_lan failed with %ld\n",
			   lpar_rc);
		netdev_err(netdev, "buffer TCE:0x%llx filter TCE:0x%llx rxq "
			   "desc:0x%llx MAC:0x%llx\n",
				     adapter->buffer_list_dma,
				     adapter->filter_list_dma,
				     rxq_desc.desc,
				     mac_address);
		rc = -ENONET;
		जाओ out_unmap_filter_list;
	पूर्ण

	क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++) अणु
		अगर (!adapter->rx_buff_pool[i].active)
			जारी;
		अगर (ibmveth_alloc_buffer_pool(&adapter->rx_buff_pool[i])) अणु
			netdev_err(netdev, "unable to alloc pool\n");
			adapter->rx_buff_pool[i].active = 0;
			rc = -ENOMEM;
			जाओ out_मुक्त_buffer_pools;
		पूर्ण
	पूर्ण

	netdev_dbg(netdev, "registering irq 0x%x\n", netdev->irq);
	rc = request_irq(netdev->irq, ibmveth_पूर्णांकerrupt, 0, netdev->name,
			 netdev);
	अगर (rc != 0) अणु
		netdev_err(netdev, "unable to request irq 0x%x, rc %d\n",
			   netdev->irq, rc);
		करो अणु
			lpar_rc = h_मुक्त_logical_lan(adapter->vdev->unit_address);
		पूर्ण जबतक (H_IS_LONG_BUSY(lpar_rc) || (lpar_rc == H_BUSY));

		जाओ out_मुक्त_buffer_pools;
	पूर्ण

	rc = -ENOMEM;
	adapter->bounce_buffer =
	    kदो_स्मृति(netdev->mtu + IBMVETH_BUFF_OH, GFP_KERNEL);
	अगर (!adapter->bounce_buffer)
		जाओ out_मुक्त_irq;

	adapter->bounce_buffer_dma =
	    dma_map_single(&adapter->vdev->dev, adapter->bounce_buffer,
			   netdev->mtu + IBMVETH_BUFF_OH, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dev, adapter->bounce_buffer_dma)) अणु
		netdev_err(netdev, "unable to map bounce buffer\n");
		जाओ out_मुक्त_bounce_buffer;
	पूर्ण

	netdev_dbg(netdev, "initial replenish cycle\n");
	ibmveth_पूर्णांकerrupt(netdev->irq, netdev);

	netअगर_start_queue(netdev);

	netdev_dbg(netdev, "open complete\n");

	वापस 0;

out_मुक्त_bounce_buffer:
	kमुक्त(adapter->bounce_buffer);
out_मुक्त_irq:
	मुक्त_irq(netdev->irq, netdev);
out_मुक्त_buffer_pools:
	जबतक (--i >= 0) अणु
		अगर (adapter->rx_buff_pool[i].active)
			ibmveth_मुक्त_buffer_pool(adapter,
						 &adapter->rx_buff_pool[i]);
	पूर्ण
out_unmap_filter_list:
	dma_unmap_single(dev, adapter->filter_list_dma, 4096,
			 DMA_BIसूचीECTIONAL);
out_unmap_buffer_list:
	dma_unmap_single(dev, adapter->buffer_list_dma, 4096,
			 DMA_BIसूचीECTIONAL);
out_मुक्त_queue_mem:
	dma_मुक्त_coherent(dev, adapter->rx_queue.queue_len,
			  adapter->rx_queue.queue_addr,
			  adapter->rx_queue.queue_dma);
out_मुक्त_filter_list:
	मुक्त_page((अचिन्हित दीर्घ)adapter->filter_list_addr);
out_मुक्त_buffer_list:
	मुक्त_page((अचिन्हित दीर्घ)adapter->buffer_list_addr);
out:
	napi_disable(&adapter->napi);
	वापस rc;
पूर्ण

अटल पूर्णांक ibmveth_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(netdev);
	काष्ठा device *dev = &adapter->vdev->dev;
	दीर्घ lpar_rc;
	पूर्णांक i;

	netdev_dbg(netdev, "close starting\n");

	napi_disable(&adapter->napi);

	अगर (!adapter->pool_config)
		netअगर_stop_queue(netdev);

	h_vio_संकेत(adapter->vdev->unit_address, VIO_IRQ_DISABLE);

	करो अणु
		lpar_rc = h_मुक्त_logical_lan(adapter->vdev->unit_address);
	पूर्ण जबतक (H_IS_LONG_BUSY(lpar_rc) || (lpar_rc == H_BUSY));

	अगर (lpar_rc != H_SUCCESS) अणु
		netdev_err(netdev, "h_free_logical_lan failed with %lx, "
			   "continuing with close\n", lpar_rc);
	पूर्ण

	मुक्त_irq(netdev->irq, netdev);

	ibmveth_update_rx_no_buffer(adapter);

	dma_unmap_single(dev, adapter->buffer_list_dma, 4096,
			 DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)adapter->buffer_list_addr);

	dma_unmap_single(dev, adapter->filter_list_dma, 4096,
			 DMA_BIसूचीECTIONAL);
	मुक्त_page((अचिन्हित दीर्घ)adapter->filter_list_addr);

	dma_मुक्त_coherent(dev, adapter->rx_queue.queue_len,
			  adapter->rx_queue.queue_addr,
			  adapter->rx_queue.queue_dma);

	क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++)
		अगर (adapter->rx_buff_pool[i].active)
			ibmveth_मुक्त_buffer_pool(adapter,
						 &adapter->rx_buff_pool[i]);

	dma_unmap_single(&adapter->vdev->dev, adapter->bounce_buffer_dma,
			 adapter->netdev->mtu + IBMVETH_BUFF_OH,
			 DMA_BIसूचीECTIONAL);
	kमुक्त(adapter->bounce_buffer);

	netdev_dbg(netdev, "close complete\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ibmveth_set_link_ksettings(काष्ठा net_device *dev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);

	वापस ethtool_virtdev_set_link_ksettings(dev, cmd,
						  &adapter->speed,
						  &adapter->duplex);
पूर्ण

अटल पूर्णांक ibmveth_get_link_ksettings(काष्ठा net_device *dev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);

	cmd->base.speed = adapter->speed;
	cmd->base.duplex = adapter->duplex;
	cmd->base.port = PORT_OTHER;

	वापस 0;
पूर्ण

अटल व्योम ibmveth_init_link_settings(काष्ठा net_device *dev)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);

	adapter->speed = SPEED_1000;
	adapter->duplex = DUPLEX_FULL;
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, ibmveth_driver_name, माप(info->driver));
	strlcpy(info->version, ibmveth_driver_version, माप(info->version));
पूर्ण

अटल netdev_features_t ibmveth_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	/*
	 * Since the ibmveth firmware पूर्णांकerface करोes not have the
	 * concept of separate tx/rx checksum offload enable, अगर rx
	 * checksum is disabled we also have to disable tx checksum
	 * offload. Once we disable rx checksum offload, we are no
	 * दीर्घer allowed to send tx buffers that are not properly
	 * checksummed.
	 */

	अगर (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_CSUM_MASK;

	वापस features;
पूर्ण

अटल पूर्णांक ibmveth_set_csum_offload(काष्ठा net_device *dev, u32 data)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);
	अचिन्हित दीर्घ set_attr, clr_attr, ret_attr;
	अचिन्हित दीर्घ set_attr6, clr_attr6;
	दीर्घ ret, ret4, ret6;
	पूर्णांक rc1 = 0, rc2 = 0;
	पूर्णांक restart = 0;

	अगर (netअगर_running(dev)) अणु
		restart = 1;
		adapter->pool_config = 1;
		ibmveth_बंद(dev);
		adapter->pool_config = 0;
	पूर्ण

	set_attr = 0;
	clr_attr = 0;
	set_attr6 = 0;
	clr_attr6 = 0;

	अगर (data) अणु
		set_attr = IBMVETH_ILLAN_IPV4_TCP_CSUM;
		set_attr6 = IBMVETH_ILLAN_IPV6_TCP_CSUM;
	पूर्ण अन्यथा अणु
		clr_attr = IBMVETH_ILLAN_IPV4_TCP_CSUM;
		clr_attr6 = IBMVETH_ILLAN_IPV6_TCP_CSUM;
	पूर्ण

	ret = h_illan_attributes(adapter->vdev->unit_address, 0, 0, &ret_attr);

	अगर (ret == H_SUCCESS &&
	    (ret_attr & IBMVETH_ILLAN_PADDED_PKT_CSUM)) अणु
		ret4 = h_illan_attributes(adapter->vdev->unit_address, clr_attr,
					 set_attr, &ret_attr);

		अगर (ret4 != H_SUCCESS) अणु
			netdev_err(dev, "unable to change IPv4 checksum "
					"offload settings. %d rc=%ld\n",
					data, ret4);

			h_illan_attributes(adapter->vdev->unit_address,
					   set_attr, clr_attr, &ret_attr);

			अगर (data == 1)
				dev->features &= ~NETIF_F_IP_CSUM;

		पूर्ण अन्यथा अणु
			adapter->fw_ipv4_csum_support = data;
		पूर्ण

		ret6 = h_illan_attributes(adapter->vdev->unit_address,
					 clr_attr6, set_attr6, &ret_attr);

		अगर (ret6 != H_SUCCESS) अणु
			netdev_err(dev, "unable to change IPv6 checksum "
					"offload settings. %d rc=%ld\n",
					data, ret6);

			h_illan_attributes(adapter->vdev->unit_address,
					   set_attr6, clr_attr6, &ret_attr);

			अगर (data == 1)
				dev->features &= ~NETIF_F_IPV6_CSUM;

		पूर्ण अन्यथा
			adapter->fw_ipv6_csum_support = data;

		अगर (ret4 == H_SUCCESS || ret6 == H_SUCCESS)
			adapter->rx_csum = data;
		अन्यथा
			rc1 = -EIO;
	पूर्ण अन्यथा अणु
		rc1 = -EIO;
		netdev_err(dev, "unable to change checksum offload settings."
				     " %d rc=%ld ret_attr=%lx\n", data, ret,
				     ret_attr);
	पूर्ण

	अगर (restart)
		rc2 = ibmveth_खोलो(dev);

	वापस rc1 ? rc1 : rc2;
पूर्ण

अटल पूर्णांक ibmveth_set_tso(काष्ठा net_device *dev, u32 data)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);
	अचिन्हित दीर्घ set_attr, clr_attr, ret_attr;
	दीर्घ ret1, ret2;
	पूर्णांक rc1 = 0, rc2 = 0;
	पूर्णांक restart = 0;

	अगर (netअगर_running(dev)) अणु
		restart = 1;
		adapter->pool_config = 1;
		ibmveth_बंद(dev);
		adapter->pool_config = 0;
	पूर्ण

	set_attr = 0;
	clr_attr = 0;

	अगर (data)
		set_attr = IBMVETH_ILLAN_LRG_SR_ENABLED;
	अन्यथा
		clr_attr = IBMVETH_ILLAN_LRG_SR_ENABLED;

	ret1 = h_illan_attributes(adapter->vdev->unit_address, 0, 0, &ret_attr);

	अगर (ret1 == H_SUCCESS && (ret_attr & IBMVETH_ILLAN_LRG_SND_SUPPORT) &&
	    !old_large_send) अणु
		ret2 = h_illan_attributes(adapter->vdev->unit_address, clr_attr,
					  set_attr, &ret_attr);

		अगर (ret2 != H_SUCCESS) अणु
			netdev_err(dev, "unable to change tso settings. %d rc=%ld\n",
				   data, ret2);

			h_illan_attributes(adapter->vdev->unit_address,
					   set_attr, clr_attr, &ret_attr);

			अगर (data == 1)
				dev->features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
			rc1 = -EIO;

		पूर्ण अन्यथा अणु
			adapter->fw_large_send_support = data;
			adapter->large_send = data;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Older firmware version of large send offload करोes not
		 * support tcp6/ipv6
		 */
		अगर (data == 1) अणु
			dev->features &= ~NETIF_F_TSO6;
			netdev_info(dev, "TSO feature requires all partitions to have updated driver");
		पूर्ण
		adapter->large_send = data;
	पूर्ण

	अगर (restart)
		rc2 = ibmveth_खोलो(dev);

	वापस rc1 ? rc1 : rc2;
पूर्ण

अटल पूर्णांक ibmveth_set_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);
	पूर्णांक rx_csum = !!(features & NETIF_F_RXCSUM);
	पूर्णांक large_send = !!(features & (NETIF_F_TSO | NETIF_F_TSO6));
	पूर्णांक rc1 = 0, rc2 = 0;

	अगर (rx_csum != adapter->rx_csum) अणु
		rc1 = ibmveth_set_csum_offload(dev, rx_csum);
		अगर (rc1 && !adapter->rx_csum)
			dev->features =
				features & ~(NETIF_F_CSUM_MASK |
					     NETIF_F_RXCSUM);
	पूर्ण

	अगर (large_send != adapter->large_send) अणु
		rc2 = ibmveth_set_tso(dev, large_send);
		अगर (rc2 && !adapter->large_send)
			dev->features =
				features & ~(NETIF_F_TSO | NETIF_F_TSO6);
	पूर्ण

	वापस rc1 ? rc1 : rc2;
पूर्ण

अटल व्योम ibmveth_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(ibmveth_stats); i++, data += ETH_GSTRING_LEN)
		स_नकल(data, ibmveth_stats[i].name, ETH_GSTRING_LEN);
पूर्ण

अटल पूर्णांक ibmveth_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ibmveth_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम ibmveth_get_ethtool_stats(काष्ठा net_device *dev,
				      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक i;
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);

	क्रम (i = 0; i < ARRAY_SIZE(ibmveth_stats); i++)
		data[i] = IBMVETH_GET_STAT(adapter, ibmveth_stats[i].offset);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		         = netdev_get_drvinfo,
	.get_link		         = ethtool_op_get_link,
	.get_strings		         = ibmveth_get_strings,
	.get_sset_count		         = ibmveth_get_sset_count,
	.get_ethtool_stats	         = ibmveth_get_ethtool_stats,
	.get_link_ksettings	         = ibmveth_get_link_ksettings,
	.set_link_ksettings              = ibmveth_set_link_ksettings,
पूर्ण;

अटल पूर्णांक ibmveth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ibmveth_send(काष्ठा ibmveth_adapter *adapter,
			जोड़ ibmveth_buf_desc *descs, अचिन्हित दीर्घ mss)
अणु
	अचिन्हित दीर्घ correlator;
	अचिन्हित पूर्णांक retry_count;
	अचिन्हित दीर्घ ret;

	/*
	 * The retry count sets a maximum क्रम the number of broadcast and
	 * multicast destinations within the प्रणाली.
	 */
	retry_count = 1024;
	correlator = 0;
	करो अणु
		ret = h_send_logical_lan(adapter->vdev->unit_address,
					     descs[0].desc, descs[1].desc,
					     descs[2].desc, descs[3].desc,
					     descs[4].desc, descs[5].desc,
					     correlator, &correlator, mss,
					     adapter->fw_large_send_support);
	पूर्ण जबतक ((ret == H_BUSY) && (retry_count--));

	अगर (ret != H_SUCCESS && ret != H_DROPPED) अणु
		netdev_err(adapter->netdev, "tx: h_send_logical_lan failed "
			   "with rc=%ld\n", ret);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ibmveth_is_packet_unsupported(काष्ठा sk_buff *skb,
					 काष्ठा net_device *netdev)
अणु
	काष्ठा ethhdr *ether_header;
	पूर्णांक ret = 0;

	ether_header = eth_hdr(skb);

	अगर (ether_addr_equal(ether_header->h_dest, netdev->dev_addr)) अणु
		netdev_dbg(netdev, "veth doesn't support loopback packets, dropping packet.\n");
		netdev->stats.tx_dropped++;
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल netdev_tx_t ibmveth_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *netdev)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक desc_flags;
	जोड़ ibmveth_buf_desc descs[6];
	पूर्णांक last, i;
	पूर्णांक क्रमce_bounce = 0;
	dma_addr_t dma_addr;
	अचिन्हित दीर्घ mss = 0;

	अगर (ibmveth_is_packet_unsupported(skb, netdev))
		जाओ out;

	/* veth करोesn't handle frag_list, so linearize the skb.
	 * When GRO is enabled SKB's can have frag_list.
	 */
	अगर (adapter->is_active_trunk &&
	    skb_has_frag_list(skb) && __skb_linearize(skb)) अणु
		netdev->stats.tx_dropped++;
		जाओ out;
	पूर्ण

	/*
	 * veth handles a maximum of 6 segments including the header, so
	 * we have to linearize the skb अगर there are more than this.
	 */
	अगर (skb_shinfo(skb)->nr_frags > 5 && __skb_linearize(skb)) अणु
		netdev->stats.tx_dropped++;
		जाओ out;
	पूर्ण

	/* veth can't checksum offload UDP */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    ((skb->protocol == htons(ETH_P_IP) &&
	      ip_hdr(skb)->protocol != IPPROTO_TCP) ||
	     (skb->protocol == htons(ETH_P_IPV6) &&
	      ipv6_hdr(skb)->nexthdr != IPPROTO_TCP)) &&
	    skb_checksum_help(skb)) अणु

		netdev_err(netdev, "tx: failed to checksum packet\n");
		netdev->stats.tx_dropped++;
		जाओ out;
	पूर्ण

	desc_flags = IBMVETH_BUF_VALID;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अचिन्हित अक्षर *buf = skb_transport_header(skb) +
						skb->csum_offset;

		desc_flags |= (IBMVETH_BUF_NO_CSUM | IBMVETH_BUF_CSUM_GOOD);

		/* Need to zero out the checksum */
		buf[0] = 0;
		buf[1] = 0;

		अगर (skb_is_gso(skb) && adapter->fw_large_send_support)
			desc_flags |= IBMVETH_BUF_LRG_SND;
	पूर्ण

retry_bounce:
	स_रखो(descs, 0, माप(descs));

	/*
	 * If a linear packet is below the rx threshold then
	 * copy it पूर्णांकo the अटल bounce buffer. This aव्योमs the
	 * cost of a TCE insert and हटाओ.
	 */
	अगर (क्रमce_bounce || (!skb_is_nonlinear(skb) &&
				(skb->len < tx_copyअवरोध))) अणु
		skb_copy_from_linear_data(skb, adapter->bounce_buffer,
					  skb->len);

		descs[0].fields.flags_len = desc_flags | skb->len;
		descs[0].fields.address = adapter->bounce_buffer_dma;

		अगर (ibmveth_send(adapter, descs, 0)) अणु
			adapter->tx_send_failed++;
			netdev->stats.tx_dropped++;
		पूर्ण अन्यथा अणु
			netdev->stats.tx_packets++;
			netdev->stats.tx_bytes += skb->len;
		पूर्ण

		जाओ out;
	पूर्ण

	/* Map the header */
	dma_addr = dma_map_single(&adapter->vdev->dev, skb->data,
				  skb_headlen(skb), DMA_TO_DEVICE);
	अगर (dma_mapping_error(&adapter->vdev->dev, dma_addr))
		जाओ map_failed;

	descs[0].fields.flags_len = desc_flags | skb_headlen(skb);
	descs[0].fields.address = dma_addr;

	/* Map the frags */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		dma_addr = skb_frag_dma_map(&adapter->vdev->dev, frag, 0,
					    skb_frag_size(frag), DMA_TO_DEVICE);

		अगर (dma_mapping_error(&adapter->vdev->dev, dma_addr))
			जाओ map_failed_frags;

		descs[i+1].fields.flags_len = desc_flags | skb_frag_size(frag);
		descs[i+1].fields.address = dma_addr;
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL && skb_is_gso(skb)) अणु
		अगर (adapter->fw_large_send_support) अणु
			mss = (अचिन्हित दीर्घ)skb_shinfo(skb)->gso_size;
			adapter->tx_large_packets++;
		पूर्ण अन्यथा अगर (!skb_is_gso_v6(skb)) अणु
			/* Put -1 in the IP checksum to tell phyp it
			 * is a largesend packet. Put the mss in
			 * the TCP checksum.
			 */
			ip_hdr(skb)->check = 0xffff;
			tcp_hdr(skb)->check =
				cpu_to_be16(skb_shinfo(skb)->gso_size);
			adapter->tx_large_packets++;
		पूर्ण
	पूर्ण

	अगर (ibmveth_send(adapter, descs, mss)) अणु
		adapter->tx_send_failed++;
		netdev->stats.tx_dropped++;
	पूर्ण अन्यथा अणु
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += skb->len;
	पूर्ण

	dma_unmap_single(&adapter->vdev->dev,
			 descs[0].fields.address,
			 descs[0].fields.flags_len & IBMVETH_BUF_LEN_MASK,
			 DMA_TO_DEVICE);

	क्रम (i = 1; i < skb_shinfo(skb)->nr_frags + 1; i++)
		dma_unmap_page(&adapter->vdev->dev, descs[i].fields.address,
			       descs[i].fields.flags_len & IBMVETH_BUF_LEN_MASK,
			       DMA_TO_DEVICE);

out:
	dev_consume_skb_any(skb);
	वापस NETDEV_TX_OK;

map_failed_frags:
	last = i+1;
	क्रम (i = 1; i < last; i++)
		dma_unmap_page(&adapter->vdev->dev, descs[i].fields.address,
			       descs[i].fields.flags_len & IBMVETH_BUF_LEN_MASK,
			       DMA_TO_DEVICE);

	dma_unmap_single(&adapter->vdev->dev,
			 descs[0].fields.address,
			 descs[0].fields.flags_len & IBMVETH_BUF_LEN_MASK,
			 DMA_TO_DEVICE);
map_failed:
	अगर (!firmware_has_feature(FW_FEATURE_CMO))
		netdev_err(netdev, "tx: unable to map xmit buffer\n");
	adapter->tx_map_failed++;
	अगर (skb_linearize(skb)) अणु
		netdev->stats.tx_dropped++;
		जाओ out;
	पूर्ण
	क्रमce_bounce = 1;
	जाओ retry_bounce;
पूर्ण

अटल व्योम ibmveth_rx_mss_helper(काष्ठा sk_buff *skb, u16 mss, पूर्णांक lrg_pkt)
अणु
	काष्ठा tcphdr *tcph;
	पूर्णांक offset = 0;
	पूर्णांक hdr_len;

	/* only TCP packets will be aggregated */
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;

		अगर (iph->protocol == IPPROTO_TCP) अणु
			offset = iph->ihl * 4;
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *iph6 = (काष्ठा ipv6hdr *)skb->data;

		अगर (iph6->nexthdr == IPPROTO_TCP) अणु
			offset = माप(काष्ठा ipv6hdr);
			skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
	/* अगर mss is not set through Large Packet bit/mss in rx buffer,
	 * expect that the mss will be written to the tcp header checksum.
	 */
	tcph = (काष्ठा tcphdr *)(skb->data + offset);
	अगर (lrg_pkt) अणु
		skb_shinfo(skb)->gso_size = mss;
	पूर्ण अन्यथा अगर (offset) अणु
		skb_shinfo(skb)->gso_size = ntohs(tcph->check);
		tcph->check = 0;
	पूर्ण

	अगर (skb_shinfo(skb)->gso_size) अणु
		hdr_len = offset + tcph->करोff * 4;
		skb_shinfo(skb)->gso_segs =
				DIV_ROUND_UP(skb->len - hdr_len,
					     skb_shinfo(skb)->gso_size);
	पूर्ण
पूर्ण

अटल व्योम ibmveth_rx_csum_helper(काष्ठा sk_buff *skb,
				   काष्ठा ibmveth_adapter *adapter)
अणु
	काष्ठा iphdr *iph = शून्य;
	काष्ठा ipv6hdr *iph6 = शून्य;
	__be16 skb_proto = 0;
	u16 iphlen = 0;
	u16 iph_proto = 0;
	u16 tcphdrlen = 0;

	skb_proto = be16_to_cpu(skb->protocol);

	अगर (skb_proto == ETH_P_IP) अणु
		iph = (काष्ठा iphdr *)skb->data;

		/* If the IP checksum is not offloaded and अगर the packet
		 *  is large send, the checksum must be rebuilt.
		 */
		अगर (iph->check == 0xffff) अणु
			iph->check = 0;
			iph->check = ip_fast_csum((अचिन्हित अक्षर *)iph,
						  iph->ihl);
		पूर्ण

		iphlen = iph->ihl * 4;
		iph_proto = iph->protocol;
	पूर्ण अन्यथा अगर (skb_proto == ETH_P_IPV6) अणु
		iph6 = (काष्ठा ipv6hdr *)skb->data;
		iphlen = माप(काष्ठा ipv6hdr);
		iph_proto = iph6->nexthdr;
	पूर्ण

	/* In OVS environment, when a flow is not cached, specअगरically क्रम a
	 * new TCP connection, the first packet inक्रमmation is passed up
	 * the user space क्रम finding a flow. During this process, OVS computes
	 * checksum on the first packet when CHECKSUM_PARTIAL flag is set.
	 *
	 * Given that we zeroed out TCP checksum field in transmit path
	 * (refer ibmveth_start_xmit routine) as we set "no checksum bit",
	 * OVS computed checksum will be incorrect w/o TCP pseuकरो checksum
	 * in the packet. This leads to OVS dropping the packet and hence
	 * TCP retransmissions are seen.
	 *
	 * So, re-compute TCP pseuकरो header checksum.
	 */
	अगर (iph_proto == IPPROTO_TCP && adapter->is_active_trunk) अणु
		काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)(skb->data + iphlen);

		tcphdrlen = skb->len - iphlen;

		/* Recompute TCP pseuकरो header checksum */
		अगर (skb_proto == ETH_P_IP)
			tcph->check = ~csum_tcpudp_magic(iph->saddr,
					iph->daddr, tcphdrlen, iph_proto, 0);
		अन्यथा अगर (skb_proto == ETH_P_IPV6)
			tcph->check = ~csum_ipv6_magic(&iph6->saddr,
					&iph6->daddr, tcphdrlen, iph_proto, 0);

		/* Setup SKB fields क्रम checksum offload */
		skb_partial_csum_set(skb, iphlen,
				     दुरत्व(काष्ठा tcphdr, check));
		skb_reset_network_header(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक ibmveth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ibmveth_adapter *adapter =
			container_of(napi, काष्ठा ibmveth_adapter, napi);
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक frames_processed = 0;
	अचिन्हित दीर्घ lpar_rc;
	u16 mss = 0;

	जबतक (frames_processed < budget) अणु
		अगर (!ibmveth_rxq_pending_buffer(adapter))
			अवरोध;

		smp_rmb();
		अगर (!ibmveth_rxq_buffer_valid(adapter)) अणु
			wmb(); /* suggested by larson1 */
			adapter->rx_invalid_buffer++;
			netdev_dbg(netdev, "recycling invalid buffer\n");
			ibmveth_rxq_recycle_buffer(adapter);
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb, *new_skb;
			पूर्णांक length = ibmveth_rxq_frame_length(adapter);
			पूर्णांक offset = ibmveth_rxq_frame_offset(adapter);
			पूर्णांक csum_good = ibmveth_rxq_csum_good(adapter);
			पूर्णांक lrg_pkt = ibmveth_rxq_large_packet(adapter);
			__sum16 iph_check = 0;

			skb = ibmveth_rxq_get_buffer(adapter);

			/* अगर the large packet bit is set in the rx queue
			 * descriptor, the mss will be written by PHYP eight
			 * bytes from the start of the rx buffer, which is
			 * skb->data at this stage
			 */
			अगर (lrg_pkt) अणु
				__be64 *rxmss = (__be64 *)(skb->data + 8);

				mss = (u16)be64_to_cpu(*rxmss);
			पूर्ण

			new_skb = शून्य;
			अगर (length < rx_copyअवरोध)
				new_skb = netdev_alloc_skb(netdev, length);

			अगर (new_skb) अणु
				skb_copy_to_linear_data(new_skb,
							skb->data + offset,
							length);
				अगर (rx_flush)
					ibmveth_flush_buffer(skb->data,
						length + offset);
				अगर (!ibmveth_rxq_recycle_buffer(adapter))
					kमुक्त_skb(skb);
				skb = new_skb;
			पूर्ण अन्यथा अणु
				ibmveth_rxq_harvest_buffer(adapter);
				skb_reserve(skb, offset);
			पूर्ण

			skb_put(skb, length);
			skb->protocol = eth_type_trans(skb, netdev);

			/* PHYP without PLSO support places a -1 in the ip
			 * checksum क्रम large send frames.
			 */
			अगर (skb->protocol == cpu_to_be16(ETH_P_IP)) अणु
				काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;

				iph_check = iph->check;
			पूर्ण

			अगर ((length > netdev->mtu + ETH_HLEN) ||
			    lrg_pkt || iph_check == 0xffff) अणु
				ibmveth_rx_mss_helper(skb, mss, lrg_pkt);
				adapter->rx_large_packets++;
			पूर्ण

			अगर (csum_good) अणु
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				ibmveth_rx_csum_helper(skb, adapter);
			पूर्ण

			napi_gro_receive(napi, skb);	/* send it up */

			netdev->stats.rx_packets++;
			netdev->stats.rx_bytes += length;
			frames_processed++;
		पूर्ण
	पूर्ण

	ibmveth_replenish_task(adapter);

	अगर (frames_processed < budget) अणु
		napi_complete_करोne(napi, frames_processed);

		/* We think we are करोne - reenable पूर्णांकerrupts,
		 * then check once more to make sure we are करोne.
		 */
		lpar_rc = h_vio_संकेत(adapter->vdev->unit_address,
				       VIO_IRQ_ENABLE);

		BUG_ON(lpar_rc != H_SUCCESS);

		अगर (ibmveth_rxq_pending_buffer(adapter) &&
		    napi_reschedule(napi)) अणु
			lpar_rc = h_vio_संकेत(adapter->vdev->unit_address,
					       VIO_IRQ_DISABLE);
		पूर्ण
	पूर्ण

	वापस frames_processed;
पूर्ण

अटल irqवापस_t ibmveth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *netdev = dev_instance;
	काष्ठा ibmveth_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ lpar_rc;

	अगर (napi_schedule_prep(&adapter->napi)) अणु
		lpar_rc = h_vio_संकेत(adapter->vdev->unit_address,
				       VIO_IRQ_DISABLE);
		BUG_ON(lpar_rc != H_SUCCESS);
		__napi_schedule(&adapter->napi);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ibmveth_set_multicast_list(काष्ठा net_device *netdev)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ lpar_rc;

	अगर ((netdev->flags & IFF_PROMISC) ||
	    (netdev_mc_count(netdev) > adapter->mcastFilterSize)) अणु
		lpar_rc = h_multicast_ctrl(adapter->vdev->unit_address,
					   IbmVethMcastEnableRecv |
					   IbmVethMcastDisableFiltering,
					   0);
		अगर (lpar_rc != H_SUCCESS) अणु
			netdev_err(netdev, "h_multicast_ctrl rc=%ld when "
				   "entering promisc mode\n", lpar_rc);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा netdev_hw_addr *ha;
		/* clear the filter table & disable filtering */
		lpar_rc = h_multicast_ctrl(adapter->vdev->unit_address,
					   IbmVethMcastEnableRecv |
					   IbmVethMcastDisableFiltering |
					   IbmVethMcastClearFilterTable,
					   0);
		अगर (lpar_rc != H_SUCCESS) अणु
			netdev_err(netdev, "h_multicast_ctrl rc=%ld when "
				   "attempting to clear filter table\n",
				   lpar_rc);
		पूर्ण
		/* add the addresses to the filter table */
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			/* add the multicast address to the filter table */
			u64 mcast_addr;
			mcast_addr = ibmveth_encode_mac_addr(ha->addr);
			lpar_rc = h_multicast_ctrl(adapter->vdev->unit_address,
						   IbmVethMcastAddFilter,
						   mcast_addr);
			अगर (lpar_rc != H_SUCCESS) अणु
				netdev_err(netdev, "h_multicast_ctrl rc=%ld "
					   "when adding an entry to the filter "
					   "table\n", lpar_rc);
			पूर्ण
		पूर्ण

		/* re-enable filtering */
		lpar_rc = h_multicast_ctrl(adapter->vdev->unit_address,
					   IbmVethMcastEnableFiltering,
					   0);
		अगर (lpar_rc != H_SUCCESS) अणु
			netdev_err(netdev, "h_multicast_ctrl rc=%ld when "
				   "enabling filtering\n", lpar_rc);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ibmveth_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);
	काष्ठा vio_dev *viodev = adapter->vdev;
	पूर्णांक new_mtu_oh = new_mtu + IBMVETH_BUFF_OH;
	पूर्णांक i, rc;
	पूर्णांक need_restart = 0;

	क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++)
		अगर (new_mtu_oh <= adapter->rx_buff_pool[i].buff_size)
			अवरोध;

	अगर (i == IBMVETH_NUM_BUFF_POOLS)
		वापस -EINVAL;

	/* Deactivate all the buffer pools so that the next loop can activate
	   only the buffer pools necessary to hold the new MTU */
	अगर (netअगर_running(adapter->netdev)) अणु
		need_restart = 1;
		adapter->pool_config = 1;
		ibmveth_बंद(adapter->netdev);
		adapter->pool_config = 0;
	पूर्ण

	/* Look क्रम an active buffer pool that can hold the new MTU */
	क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++) अणु
		adapter->rx_buff_pool[i].active = 1;

		अगर (new_mtu_oh <= adapter->rx_buff_pool[i].buff_size) अणु
			dev->mtu = new_mtu;
			vio_cmo_set_dev_desired(viodev,
						ibmveth_get_desired_dma
						(viodev));
			अगर (need_restart) अणु
				वापस ibmveth_खोलो(adapter->netdev);
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (need_restart && (rc = ibmveth_खोलो(adapter->netdev)))
		वापस rc;

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम ibmveth_poll_controller(काष्ठा net_device *dev)
अणु
	ibmveth_replenish_task(netdev_priv(dev));
	ibmveth_पूर्णांकerrupt(dev->irq, dev);
पूर्ण
#पूर्ण_अगर

/**
 * ibmveth_get_desired_dma - Calculate IO memory desired by the driver
 *
 * @vdev: काष्ठा vio_dev क्रम the device whose desired IO mem is to be वापसed
 *
 * Return value:
 *	Number of bytes of IO data the driver will need to perक्रमm well.
 */
अटल अचिन्हित दीर्घ ibmveth_get_desired_dma(काष्ठा vio_dev *vdev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(&vdev->dev);
	काष्ठा ibmveth_adapter *adapter;
	काष्ठा iommu_table *tbl;
	अचिन्हित दीर्घ ret;
	पूर्णांक i;
	पूर्णांक rxqentries = 1;

	tbl = get_iommu_table_base(&vdev->dev);

	/* netdev inits at probe समय aदीर्घ with the काष्ठाures we need below*/
	अगर (netdev == शून्य)
		वापस IOMMU_PAGE_ALIGN(IBMVETH_IO_ENTITLEMENT_DEFAULT, tbl);

	adapter = netdev_priv(netdev);

	ret = IBMVETH_BUFF_LIST_SIZE + IBMVETH_FILT_LIST_SIZE;
	ret += IOMMU_PAGE_ALIGN(netdev->mtu, tbl);

	क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++) अणु
		/* add the size of the active receive buffers */
		अगर (adapter->rx_buff_pool[i].active)
			ret +=
			    adapter->rx_buff_pool[i].size *
			    IOMMU_PAGE_ALIGN(adapter->rx_buff_pool[i].
					     buff_size, tbl);
		rxqentries += adapter->rx_buff_pool[i].size;
	पूर्ण
	/* add the size of the receive queue entries */
	ret += IOMMU_PAGE_ALIGN(
		rxqentries * माप(काष्ठा ibmveth_rx_q_entry), tbl);

	वापस ret;
पूर्ण

अटल पूर्णांक ibmveth_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा ibmveth_adapter *adapter = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;
	u64 mac_address;
	पूर्णांक rc;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	mac_address = ibmveth_encode_mac_addr(addr->sa_data);
	rc = h_change_logical_lan_mac(adapter->vdev->unit_address, mac_address);
	अगर (rc) अणु
		netdev_err(adapter->netdev, "h_change_logical_lan_mac failed with rc=%d\n", rc);
		वापस rc;
	पूर्ण

	ether_addr_copy(dev->dev_addr, addr->sa_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ibmveth_netdev_ops = अणु
	.nकरो_खोलो		= ibmveth_खोलो,
	.nकरो_stop		= ibmveth_बंद,
	.nकरो_start_xmit		= ibmveth_start_xmit,
	.nकरो_set_rx_mode	= ibmveth_set_multicast_list,
	.nकरो_करो_ioctl		= ibmveth_ioctl,
	.nकरो_change_mtu		= ibmveth_change_mtu,
	.nकरो_fix_features	= ibmveth_fix_features,
	.nकरो_set_features	= ibmveth_set_features,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address    = ibmveth_set_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= ibmveth_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ibmveth_probe(काष्ठा vio_dev *dev, स्थिर काष्ठा vio_device_id *id)
अणु
	पूर्णांक rc, i, mac_len;
	काष्ठा net_device *netdev;
	काष्ठा ibmveth_adapter *adapter;
	अचिन्हित अक्षर *mac_addr_p;
	__be32 *mcastFilterSize_p;
	दीर्घ ret;
	अचिन्हित दीर्घ ret_attr;

	dev_dbg(&dev->dev, "entering ibmveth_probe for UA 0x%x\n",
		dev->unit_address);

	mac_addr_p = (अचिन्हित अक्षर *)vio_get_attribute(dev, VETH_MAC_ADDR,
							&mac_len);
	अगर (!mac_addr_p) अणु
		dev_err(&dev->dev, "Can't find VETH_MAC_ADDR attribute\n");
		वापस -EINVAL;
	पूर्ण
	/* Workaround क्रम old/broken pHyp */
	अगर (mac_len == 8)
		mac_addr_p += 2;
	अन्यथा अगर (mac_len != 6) अणु
		dev_err(&dev->dev, "VETH_MAC_ADDR attribute wrong len %d\n",
			mac_len);
		वापस -EINVAL;
	पूर्ण

	mcastFilterSize_p = (__be32 *)vio_get_attribute(dev,
							VETH_MCAST_FILTER_SIZE,
							शून्य);
	अगर (!mcastFilterSize_p) अणु
		dev_err(&dev->dev, "Can't find VETH_MCAST_FILTER_SIZE "
			"attribute\n");
		वापस -EINVAL;
	पूर्ण

	netdev = alloc_etherdev(माप(काष्ठा ibmveth_adapter));

	अगर (!netdev)
		वापस -ENOMEM;

	adapter = netdev_priv(netdev);
	dev_set_drvdata(&dev->dev, netdev);

	adapter->vdev = dev;
	adapter->netdev = netdev;
	adapter->mcastFilterSize = be32_to_cpu(*mcastFilterSize_p);
	adapter->pool_config = 0;
	ibmveth_init_link_settings(netdev);

	netअगर_napi_add(netdev, &adapter->napi, ibmveth_poll, 16);

	netdev->irq = dev->irq;
	netdev->netdev_ops = &ibmveth_netdev_ops;
	netdev->ethtool_ops = &netdev_ethtool_ops;
	SET_NETDEV_DEV(netdev, &dev->dev);
	netdev->hw_features = NETIF_F_SG;
	अगर (vio_get_attribute(dev, "ibm,illan-options", शून्य) != शून्य) अणु
		netdev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				       NETIF_F_RXCSUM;
	पूर्ण

	netdev->features |= netdev->hw_features;

	ret = h_illan_attributes(adapter->vdev->unit_address, 0, 0, &ret_attr);

	/* If running older firmware, TSO should not be enabled by शेष */
	अगर (ret == H_SUCCESS && (ret_attr & IBMVETH_ILLAN_LRG_SND_SUPPORT) &&
	    !old_large_send) अणु
		netdev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;
		netdev->features |= netdev->hw_features;
	पूर्ण अन्यथा अणु
		netdev->hw_features |= NETIF_F_TSO;
	पूर्ण

	adapter->is_active_trunk = false;
	अगर (ret == H_SUCCESS && (ret_attr & IBMVETH_ILLAN_ACTIVE_TRUNK)) अणु
		adapter->is_active_trunk = true;
		netdev->hw_features |= NETIF_F_FRAGLIST;
		netdev->features |= NETIF_F_FRAGLIST;
	पूर्ण

	netdev->min_mtu = IBMVETH_MIN_MTU;
	netdev->max_mtu = ETH_MAX_MTU - IBMVETH_BUFF_OH;

	स_नकल(netdev->dev_addr, mac_addr_p, ETH_ALEN);

	अगर (firmware_has_feature(FW_FEATURE_CMO))
		स_नकल(pool_count, pool_count_cmo, माप(pool_count));

	क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++) अणु
		काष्ठा kobject *kobj = &adapter->rx_buff_pool[i].kobj;
		पूर्णांक error;

		ibmveth_init_buffer_pool(&adapter->rx_buff_pool[i], i,
					 pool_count[i], pool_size[i],
					 pool_active[i]);
		error = kobject_init_and_add(kobj, &ktype_veth_pool,
					     &dev->dev.kobj, "pool%d", i);
		अगर (!error)
			kobject_uevent(kobj, KOBJ_ADD);
	पूर्ण

	netdev_dbg(netdev, "adapter @ 0x%p\n", adapter);
	netdev_dbg(netdev, "registering netdev...\n");

	ibmveth_set_features(netdev, netdev->features);

	rc = रेजिस्टर_netdev(netdev);

	अगर (rc) अणु
		netdev_dbg(netdev, "failed to register netdev rc=%d\n", rc);
		मुक्त_netdev(netdev);
		वापस rc;
	पूर्ण

	netdev_dbg(netdev, "registered\n");

	वापस 0;
पूर्ण

अटल व्योम ibmveth_हटाओ(काष्ठा vio_dev *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(&dev->dev);
	काष्ठा ibmveth_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++)
		kobject_put(&adapter->rx_buff_pool[i].kobj);

	unरेजिस्टर_netdev(netdev);

	मुक्त_netdev(netdev);
	dev_set_drvdata(&dev->dev, शून्य);
पूर्ण

अटल काष्ठा attribute veth_active_attr;
अटल काष्ठा attribute veth_num_attr;
अटल काष्ठा attribute veth_size_attr;

अटल sमाप_प्रकार veth_pool_show(काष्ठा kobject *kobj,
			      काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा ibmveth_buff_pool *pool = container_of(kobj,
						      काष्ठा ibmveth_buff_pool,
						      kobj);

	अगर (attr == &veth_active_attr)
		वापस प्र_लिखो(buf, "%d\n", pool->active);
	अन्यथा अगर (attr == &veth_num_attr)
		वापस प्र_लिखो(buf, "%d\n", pool->size);
	अन्यथा अगर (attr == &veth_size_attr)
		वापस प्र_लिखो(buf, "%d\n", pool->buff_size);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार veth_pool_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ibmveth_buff_pool *pool = container_of(kobj,
						      काष्ठा ibmveth_buff_pool,
						      kobj);
	काष्ठा net_device *netdev = dev_get_drvdata(
	    container_of(kobj->parent, काष्ठा device, kobj));
	काष्ठा ibmveth_adapter *adapter = netdev_priv(netdev);
	दीर्घ value = simple_म_से_दीर्घ(buf, शून्य, 10);
	दीर्घ rc;

	अगर (attr == &veth_active_attr) अणु
		अगर (value && !pool->active) अणु
			अगर (netअगर_running(netdev)) अणु
				अगर (ibmveth_alloc_buffer_pool(pool)) अणु
					netdev_err(netdev,
						   "unable to alloc pool\n");
					वापस -ENOMEM;
				पूर्ण
				pool->active = 1;
				adapter->pool_config = 1;
				ibmveth_बंद(netdev);
				adapter->pool_config = 0;
				अगर ((rc = ibmveth_खोलो(netdev)))
					वापस rc;
			पूर्ण अन्यथा अणु
				pool->active = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (!value && pool->active) अणु
			पूर्णांक mtu = netdev->mtu + IBMVETH_BUFF_OH;
			पूर्णांक i;
			/* Make sure there is a buffer pool with buffers that
			   can hold a packet of the size of the MTU */
			क्रम (i = 0; i < IBMVETH_NUM_BUFF_POOLS; i++) अणु
				अगर (pool == &adapter->rx_buff_pool[i])
					जारी;
				अगर (!adapter->rx_buff_pool[i].active)
					जारी;
				अगर (mtu <= adapter->rx_buff_pool[i].buff_size)
					अवरोध;
			पूर्ण

			अगर (i == IBMVETH_NUM_BUFF_POOLS) अणु
				netdev_err(netdev, "no active pool >= MTU\n");
				वापस -EPERM;
			पूर्ण

			अगर (netअगर_running(netdev)) अणु
				adapter->pool_config = 1;
				ibmveth_बंद(netdev);
				pool->active = 0;
				adapter->pool_config = 0;
				अगर ((rc = ibmveth_खोलो(netdev)))
					वापस rc;
			पूर्ण
			pool->active = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (attr == &veth_num_attr) अणु
		अगर (value <= 0 || value > IBMVETH_MAX_POOL_COUNT) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (netअगर_running(netdev)) अणु
				adapter->pool_config = 1;
				ibmveth_बंद(netdev);
				adapter->pool_config = 0;
				pool->size = value;
				अगर ((rc = ibmveth_खोलो(netdev)))
					वापस rc;
			पूर्ण अन्यथा अणु
				pool->size = value;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (attr == &veth_size_attr) अणु
		अगर (value <= IBMVETH_BUFF_OH || value > IBMVETH_MAX_BUF_SIZE) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (netअगर_running(netdev)) अणु
				adapter->pool_config = 1;
				ibmveth_बंद(netdev);
				adapter->pool_config = 0;
				pool->buff_size = value;
				अगर ((rc = ibmveth_खोलो(netdev)))
					वापस rc;
			पूर्ण अन्यथा अणु
				pool->buff_size = value;
			पूर्ण
		पूर्ण
	पूर्ण

	/* kick the पूर्णांकerrupt handler to allocate/deallocate pools */
	ibmveth_पूर्णांकerrupt(netdev->irq, netdev);
	वापस count;
पूर्ण


#घोषणा ATTR(_name, _mode)				\
	काष्ठा attribute veth_##_name##_attr = अणु	\
	.name = __stringअगरy(_name), .mode = _mode,	\
	पूर्ण;

अटल ATTR(active, 0644);
अटल ATTR(num, 0644);
अटल ATTR(size, 0644);

अटल काष्ठा attribute *veth_pool_attrs[] = अणु
	&veth_active_attr,
	&veth_num_attr,
	&veth_size_attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops veth_pool_ops = अणु
	.show   = veth_pool_show,
	.store  = veth_pool_store,
पूर्ण;

अटल काष्ठा kobj_type ktype_veth_pool = अणु
	.release        = शून्य,
	.sysfs_ops      = &veth_pool_ops,
	.शेष_attrs  = veth_pool_attrs,
पूर्ण;

अटल पूर्णांक ibmveth_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	ibmveth_पूर्णांकerrupt(netdev->irq, netdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vio_device_id ibmveth_device_table[] = अणु
	अणु "network", "IBM,l-lan"पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, ibmveth_device_table);

अटल स्थिर काष्ठा dev_pm_ops ibmveth_pm_ops = अणु
	.resume = ibmveth_resume
पूर्ण;

अटल काष्ठा vio_driver ibmveth_driver = अणु
	.id_table	= ibmveth_device_table,
	.probe		= ibmveth_probe,
	.हटाओ		= ibmveth_हटाओ,
	.get_desired_dma = ibmveth_get_desired_dma,
	.name		= ibmveth_driver_name,
	.pm		= &ibmveth_pm_ops,
पूर्ण;

अटल पूर्णांक __init ibmveth_module_init(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "%s: %s %s\n", ibmveth_driver_name,
	       ibmveth_driver_string, ibmveth_driver_version);

	वापस vio_रेजिस्टर_driver(&ibmveth_driver);
पूर्ण

अटल व्योम __निकास ibmveth_module_निकास(व्योम)
अणु
	vio_unरेजिस्टर_driver(&ibmveth_driver);
पूर्ण

module_init(ibmveth_module_init);
module_निकास(ibmveth_module_निकास);
