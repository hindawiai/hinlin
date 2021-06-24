<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/aer.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/ip.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <net/pkt_sched.h>
#समावेश <linux/bpf_trace.h>

#समावेश <net/ipv6.h>

#समावेश "igc.h"
#समावेश "igc_hw.h"
#समावेश "igc_tsn.h"
#समावेश "igc_xdp.h"

#घोषणा DRV_SUMMARY	"Intel(R) 2.5G Ethernet Linux Driver"

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)

#घोषणा IGC_XDP_PASS		0
#घोषणा IGC_XDP_CONSUMED	BIT(0)
#घोषणा IGC_XDP_TX		BIT(1)
#घोषणा IGC_XDP_REसूचीECT	BIT(2)

अटल पूर्णांक debug = -1;

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION(DRV_SUMMARY);
MODULE_LICENSE("GPL v2");
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अक्षर igc_driver_name[] = "igc";
अटल स्थिर अक्षर igc_driver_string[] = DRV_SUMMARY;
अटल स्थिर अक्षर igc_copyright[] =
	"Copyright(c) 2018 Intel Corporation.";

अटल स्थिर काष्ठा igc_info *igc_info_tbl[] = अणु
	[board_base] = &igc_base_info,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id igc_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_LM), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_V), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_I), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I220_V), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_K), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_K2), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I226_K), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_LMVP), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_IT), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I226_LM), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I226_V), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I226_IT), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I221_V), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I226_BLANK_NVM), board_base पूर्ण,
	अणु PCI_VDEVICE(INTEL, IGC_DEV_ID_I225_BLANK_NVM), board_base पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, igc_pci_tbl);

क्रमागत latency_range अणु
	lowest_latency = 0,
	low_latency = 1,
	bulk_latency = 2,
	latency_invalid = 255
पूर्ण;

व्योम igc_reset(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा igc_fc_info *fc = &hw->fc;
	u32 pba, hwm;

	/* Repartition PBA क्रम greater than 9k MTU अगर required */
	pba = IGC_PBA_34K;

	/* flow control settings
	 * The high water mark must be low enough to fit one full frame
	 * after transmitting the छोड़ो frame.  As such we must have enough
	 * space to allow क्रम us to complete our current transmit and then
	 * receive the frame that is in progress from the link partner.
	 * Set it to:
	 * - the full Rx FIFO size minus one full Tx plus one full Rx frame
	 */
	hwm = (pba << 10) - (adapter->max_frame_size + MAX_JUMBO_FRAME_SIZE);

	fc->high_water = hwm & 0xFFFFFFF0;	/* 16-byte granularity */
	fc->low_water = fc->high_water - 16;
	fc->छोड़ो_समय = 0xFFFF;
	fc->send_xon = 1;
	fc->current_mode = fc->requested_mode;

	hw->mac.ops.reset_hw(hw);

	अगर (hw->mac.ops.init_hw(hw))
		netdev_err(dev, "Error on hardware initialization\n");

	/* Re-establish EEE setting */
	igc_set_eee_i225(hw, true, true, true);

	अगर (!netअगर_running(adapter->netdev))
		igc_घातer_करोwn_phy_copper_base(&adapter->hw);

	/* Re-enable PTP, where applicable. */
	igc_ptp_reset(adapter);

	/* Re-enable TSN offloading, where applicable. */
	igc_tsn_offload_apply(adapter);

	igc_get_phy_info(hw);
पूर्ण

/**
 * igc_घातer_up_link - Power up the phy link
 * @adapter: address of board निजी काष्ठाure
 */
अटल व्योम igc_घातer_up_link(काष्ठा igc_adapter *adapter)
अणु
	igc_reset_phy(&adapter->hw);

	igc_घातer_up_phy_copper(&adapter->hw);

	igc_setup_link(&adapter->hw);
पूर्ण

/**
 * igc_release_hw_control - release control of the h/w to f/w
 * @adapter: address of board निजी काष्ठाure
 *
 * igc_release_hw_control resets CTRL_EXT:DRV_LOAD bit.
 * For ASF and Pass Through versions of f/w this means that the
 * driver is no दीर्घer loaded.
 */
अटल व्योम igc_release_hw_control(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 ctrl_ext;

	/* Let firmware take over control of h/w */
	ctrl_ext = rd32(IGC_CTRL_EXT);
	wr32(IGC_CTRL_EXT,
	     ctrl_ext & ~IGC_CTRL_EXT_DRV_LOAD);
पूर्ण

/**
 * igc_get_hw_control - get control of the h/w from f/w
 * @adapter: address of board निजी काष्ठाure
 *
 * igc_get_hw_control sets CTRL_EXT:DRV_LOAD bit.
 * For ASF and Pass Through versions of f/w this means that
 * the driver is loaded.
 */
अटल व्योम igc_get_hw_control(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 ctrl_ext;

	/* Let firmware know the driver has taken over */
	ctrl_ext = rd32(IGC_CTRL_EXT);
	wr32(IGC_CTRL_EXT,
	     ctrl_ext | IGC_CTRL_EXT_DRV_LOAD);
पूर्ण

/**
 * igc_clean_tx_ring - Free Tx Buffers
 * @tx_ring: ring to be cleaned
 */
अटल व्योम igc_clean_tx_ring(काष्ठा igc_ring *tx_ring)
अणु
	u16 i = tx_ring->next_to_clean;
	काष्ठा igc_tx_buffer *tx_buffer = &tx_ring->tx_buffer_info[i];

	जबतक (i != tx_ring->next_to_use) अणु
		जोड़ igc_adv_tx_desc *eop_desc, *tx_desc;

		अगर (tx_buffer->tx_flags & IGC_TX_FLAGS_XDP)
			xdp_वापस_frame(tx_buffer->xdpf);
		अन्यथा
			dev_kमुक्त_skb_any(tx_buffer->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* check क्रम eop_desc to determine the end of the packet */
		eop_desc = tx_buffer->next_to_watch;
		tx_desc = IGC_TX_DESC(tx_ring, i);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(i == tx_ring->count)) अणु
				i = 0;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IGC_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len))
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		i++;
		अगर (unlikely(i == tx_ring->count)) अणु
			i = 0;
			tx_buffer = tx_ring->tx_buffer_info;
		पूर्ण
	पूर्ण

	/* reset BQL क्रम queue */
	netdev_tx_reset_queue(txring_txq(tx_ring));

	/* reset next_to_use and next_to_clean */
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
पूर्ण

/**
 * igc_मुक्त_tx_resources - Free Tx Resources per Queue
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 */
व्योम igc_मुक्त_tx_resources(काष्ठा igc_ring *tx_ring)
अणु
	igc_clean_tx_ring(tx_ring);

	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!tx_ring->desc)
		वापस;

	dma_मुक्त_coherent(tx_ring->dev, tx_ring->size,
			  tx_ring->desc, tx_ring->dma);

	tx_ring->desc = शून्य;
पूर्ण

/**
 * igc_मुक्त_all_tx_resources - Free Tx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 */
अटल व्योम igc_मुक्त_all_tx_resources(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		igc_मुक्त_tx_resources(adapter->tx_ring[i]);
पूर्ण

/**
 * igc_clean_all_tx_rings - Free Tx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम igc_clean_all_tx_rings(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		अगर (adapter->tx_ring[i])
			igc_clean_tx_ring(adapter->tx_ring[i]);
पूर्ण

/**
 * igc_setup_tx_resources - allocate Tx resources (Descriptors)
 * @tx_ring: tx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Return 0 on success, negative on failure
 */
पूर्णांक igc_setup_tx_resources(काष्ठा igc_ring *tx_ring)
अणु
	काष्ठा net_device *ndev = tx_ring->netdev;
	काष्ठा device *dev = tx_ring->dev;
	पूर्णांक size = 0;

	size = माप(काष्ठा igc_tx_buffer) * tx_ring->count;
	tx_ring->tx_buffer_info = vzalloc(size);
	अगर (!tx_ring->tx_buffer_info)
		जाओ err;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(जोड़ igc_adv_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	tx_ring->desc = dma_alloc_coherent(dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);

	अगर (!tx_ring->desc)
		जाओ err;

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	वापस 0;

err:
	vमुक्त(tx_ring->tx_buffer_info);
	netdev_err(ndev, "Unable to allocate memory for Tx descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * igc_setup_all_tx_resources - wrapper to allocate Tx resources क्रम all queues
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक igc_setup_all_tx_resources(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		err = igc_setup_tx_resources(adapter->tx_ring[i]);
		अगर (err) अणु
			netdev_err(dev, "Error on Tx queue %u setup\n", i);
			क्रम (i--; i >= 0; i--)
				igc_मुक्त_tx_resources(adapter->tx_ring[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * igc_clean_rx_ring - Free Rx Buffers per Queue
 * @rx_ring: ring to मुक्त buffers from
 */
अटल व्योम igc_clean_rx_ring(काष्ठा igc_ring *rx_ring)
अणु
	u16 i = rx_ring->next_to_clean;

	dev_kमुक्त_skb(rx_ring->skb);
	rx_ring->skb = शून्य;

	/* Free all the Rx ring sk_buffs */
	जबतक (i != rx_ring->next_to_alloc) अणु
		काष्ठा igc_rx_buffer *buffer_info = &rx_ring->rx_buffer_info[i];

		/* Invalidate cache lines that may have been written to by
		 * device so that we aव्योम corrupting memory.
		 */
		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      buffer_info->dma,
					      buffer_info->page_offset,
					      igc_rx_bufsz(rx_ring),
					      DMA_FROM_DEVICE);

		/* मुक्त resources associated with mapping */
		dma_unmap_page_attrs(rx_ring->dev,
				     buffer_info->dma,
				     igc_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     IGC_RX_DMA_ATTR);
		__page_frag_cache_drain(buffer_info->page,
					buffer_info->pagecnt_bias);

		i++;
		अगर (i == rx_ring->count)
			i = 0;
	पूर्ण

	clear_ring_uses_large_buffer(rx_ring);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

/**
 * igc_clean_all_rx_rings - Free Rx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम igc_clean_all_rx_rings(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		अगर (adapter->rx_ring[i])
			igc_clean_rx_ring(adapter->rx_ring[i]);
पूर्ण

/**
 * igc_मुक्त_rx_resources - Free Rx Resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 */
व्योम igc_मुक्त_rx_resources(काष्ठा igc_ring *rx_ring)
अणु
	igc_clean_rx_ring(rx_ring);

	igc_xdp_unरेजिस्टर_rxq_info(rx_ring);

	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!rx_ring->desc)
		वापस;

	dma_मुक्त_coherent(rx_ring->dev, rx_ring->size,
			  rx_ring->desc, rx_ring->dma);

	rx_ring->desc = शून्य;
पूर्ण

/**
 * igc_मुक्त_all_rx_resources - Free Rx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all receive software resources
 */
अटल व्योम igc_मुक्त_all_rx_resources(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		igc_मुक्त_rx_resources(adapter->rx_ring[i]);
पूर्ण

/**
 * igc_setup_rx_resources - allocate Rx resources (Descriptors)
 * @rx_ring:    rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक igc_setup_rx_resources(काष्ठा igc_ring *rx_ring)
अणु
	काष्ठा net_device *ndev = rx_ring->netdev;
	काष्ठा device *dev = rx_ring->dev;
	पूर्णांक size, desc_len, res;

	res = igc_xdp_रेजिस्टर_rxq_info(rx_ring);
	अगर (res < 0)
		वापस res;

	size = माप(काष्ठा igc_rx_buffer) * rx_ring->count;
	rx_ring->rx_buffer_info = vzalloc(size);
	अगर (!rx_ring->rx_buffer_info)
		जाओ err;

	desc_len = माप(जोड़ igc_adv_rx_desc);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * desc_len;
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);

	अगर (!rx_ring->desc)
		जाओ err;

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	वापस 0;

err:
	igc_xdp_unरेजिस्टर_rxq_info(rx_ring);
	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;
	netdev_err(ndev, "Unable to allocate memory for Rx descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * igc_setup_all_rx_resources - wrapper to allocate Rx resources
 *                                (Descriptors) क्रम all queues
 * @adapter: board निजी काष्ठाure
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक igc_setup_all_rx_resources(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		err = igc_setup_rx_resources(adapter->rx_ring[i]);
		अगर (err) अणु
			netdev_err(dev, "Error on Rx queue %u setup\n", i);
			क्रम (i--; i >= 0; i--)
				igc_मुक्त_rx_resources(adapter->rx_ring[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल bool igc_xdp_is_enabled(काष्ठा igc_adapter *adapter)
अणु
	वापस !!adapter->xdp_prog;
पूर्ण

/**
 * igc_configure_rx_ring - Configure a receive ring after Reset
 * @adapter: board निजी काष्ठाure
 * @ring: receive ring to be configured
 *
 * Configure the Rx unit of the MAC after a reset.
 */
अटल व्योम igc_configure_rx_ring(काष्ठा igc_adapter *adapter,
				  काष्ठा igc_ring *ring)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	जोड़ igc_adv_rx_desc *rx_desc;
	पूर्णांक reg_idx = ring->reg_idx;
	u32 srrctl = 0, rxdctl = 0;
	u64 rdba = ring->dma;

	अगर (igc_xdp_is_enabled(adapter))
		set_ring_uses_large_buffer(ring);

	/* disable the queue */
	wr32(IGC_RXDCTL(reg_idx), 0);

	/* Set DMA base address रेजिस्टरs */
	wr32(IGC_RDBAL(reg_idx),
	     rdba & 0x00000000ffffffffULL);
	wr32(IGC_RDBAH(reg_idx), rdba >> 32);
	wr32(IGC_RDLEN(reg_idx),
	     ring->count * माप(जोड़ igc_adv_rx_desc));

	/* initialize head and tail */
	ring->tail = adapter->io_addr + IGC_RDT(reg_idx);
	wr32(IGC_RDH(reg_idx), 0);
	ग_लिखोl(0, ring->tail);

	/* reset next-to- use/clean to place SW in sync with hardware */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;

	/* set descriptor configuration */
	srrctl = IGC_RX_HDR_LEN << IGC_SRRCTL_BSIZEHDRSIZE_SHIFT;
	अगर (ring_uses_large_buffer(ring))
		srrctl |= IGC_RXBUFFER_3072 >> IGC_SRRCTL_BSIZEPKT_SHIFT;
	अन्यथा
		srrctl |= IGC_RXBUFFER_2048 >> IGC_SRRCTL_BSIZEPKT_SHIFT;
	srrctl |= IGC_SRRCTL_DESCTYPE_ADV_ONEBUF;

	wr32(IGC_SRRCTL(reg_idx), srrctl);

	rxdctl |= IGC_RX_PTHRESH;
	rxdctl |= IGC_RX_HTHRESH << 8;
	rxdctl |= IGC_RX_WTHRESH << 16;

	/* initialize rx_buffer_info */
	स_रखो(ring->rx_buffer_info, 0,
	       माप(काष्ठा igc_rx_buffer) * ring->count);

	/* initialize Rx descriptor 0 */
	rx_desc = IGC_RX_DESC(ring, 0);
	rx_desc->wb.upper.length = 0;

	/* enable receive descriptor fetching */
	rxdctl |= IGC_RXDCTL_QUEUE_ENABLE;

	wr32(IGC_RXDCTL(reg_idx), rxdctl);
पूर्ण

/**
 * igc_configure_rx - Configure receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 */
अटल व्योम igc_configure_rx(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i;

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		igc_configure_rx_ring(adapter, adapter->rx_ring[i]);
पूर्ण

/**
 * igc_configure_tx_ring - Configure transmit ring after Reset
 * @adapter: board निजी काष्ठाure
 * @ring: tx ring to configure
 *
 * Configure a transmit ring after a reset.
 */
अटल व्योम igc_configure_tx_ring(काष्ठा igc_adapter *adapter,
				  काष्ठा igc_ring *ring)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक reg_idx = ring->reg_idx;
	u64 tdba = ring->dma;
	u32 txdctl = 0;

	/* disable the queue */
	wr32(IGC_TXDCTL(reg_idx), 0);
	wrfl();
	mdelay(10);

	wr32(IGC_TDLEN(reg_idx),
	     ring->count * माप(जोड़ igc_adv_tx_desc));
	wr32(IGC_TDBAL(reg_idx),
	     tdba & 0x00000000ffffffffULL);
	wr32(IGC_TDBAH(reg_idx), tdba >> 32);

	ring->tail = adapter->io_addr + IGC_TDT(reg_idx);
	wr32(IGC_TDH(reg_idx), 0);
	ग_लिखोl(0, ring->tail);

	txdctl |= IGC_TX_PTHRESH;
	txdctl |= IGC_TX_HTHRESH << 8;
	txdctl |= IGC_TX_WTHRESH << 16;

	txdctl |= IGC_TXDCTL_QUEUE_ENABLE;
	wr32(IGC_TXDCTL(reg_idx), txdctl);
पूर्ण

/**
 * igc_configure_tx - Configure transmit Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 */
अटल व्योम igc_configure_tx(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		igc_configure_tx_ring(adapter, adapter->tx_ring[i]);
पूर्ण

/**
 * igc_setup_mrqc - configure the multiple receive queue control रेजिस्टरs
 * @adapter: Board निजी काष्ठाure
 */
अटल व्योम igc_setup_mrqc(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 j, num_rx_queues;
	u32 mrqc, rxcsum;
	u32 rss_key[10];

	netdev_rss_key_fill(rss_key, माप(rss_key));
	क्रम (j = 0; j < 10; j++)
		wr32(IGC_RSSRK(j), rss_key[j]);

	num_rx_queues = adapter->rss_queues;

	अगर (adapter->rss_indir_tbl_init != num_rx_queues) अणु
		क्रम (j = 0; j < IGC_RETA_SIZE; j++)
			adapter->rss_indir_tbl[j] =
			(j * num_rx_queues) / IGC_RETA_SIZE;
		adapter->rss_indir_tbl_init = num_rx_queues;
	पूर्ण
	igc_ग_लिखो_rss_indir_tbl(adapter);

	/* Disable raw packet checksumming so that RSS hash is placed in
	 * descriptor on ग_लिखोback.  No need to enable TCP/UDP/IP checksum
	 * offloads as they are enabled by शेष
	 */
	rxcsum = rd32(IGC_RXCSUM);
	rxcsum |= IGC_RXCSUM_PCSD;

	/* Enable Receive Checksum Offload क्रम SCTP */
	rxcsum |= IGC_RXCSUM_CRCOFL;

	/* Don't need to set TUOFL or IPOFL, they शेष to 1 */
	wr32(IGC_RXCSUM, rxcsum);

	/* Generate RSS hash based on packet types, TCP/UDP
	 * port numbers and/or IPv4/v6 src and dst addresses
	 */
	mrqc = IGC_MRQC_RSS_FIELD_IPV4 |
	       IGC_MRQC_RSS_FIELD_IPV4_TCP |
	       IGC_MRQC_RSS_FIELD_IPV6 |
	       IGC_MRQC_RSS_FIELD_IPV6_TCP |
	       IGC_MRQC_RSS_FIELD_IPV6_TCP_EX;

	अगर (adapter->flags & IGC_FLAG_RSS_FIELD_IPV4_UDP)
		mrqc |= IGC_MRQC_RSS_FIELD_IPV4_UDP;
	अगर (adapter->flags & IGC_FLAG_RSS_FIELD_IPV6_UDP)
		mrqc |= IGC_MRQC_RSS_FIELD_IPV6_UDP;

	mrqc |= IGC_MRQC_ENABLE_RSS_MQ;

	wr32(IGC_MRQC, mrqc);
पूर्ण

/**
 * igc_setup_rctl - configure the receive control रेजिस्टरs
 * @adapter: Board निजी काष्ठाure
 */
अटल व्योम igc_setup_rctl(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 rctl;

	rctl = rd32(IGC_RCTL);

	rctl &= ~(3 << IGC_RCTL_MO_SHIFT);
	rctl &= ~(IGC_RCTL_LBM_TCVR | IGC_RCTL_LBM_MAC);

	rctl |= IGC_RCTL_EN | IGC_RCTL_BAM | IGC_RCTL_RDMTS_HALF |
		(hw->mac.mc_filter_type << IGC_RCTL_MO_SHIFT);

	/* enable stripping of CRC. Newer features require
	 * that the HW strips the CRC.
	 */
	rctl |= IGC_RCTL_SECRC;

	/* disable store bad packets and clear size bits. */
	rctl &= ~(IGC_RCTL_SBP | IGC_RCTL_SZ_256);

	/* enable LPE to allow क्रम reception of jumbo frames */
	rctl |= IGC_RCTL_LPE;

	/* disable queue 0 to prevent tail ग_लिखो w/o re-config */
	wr32(IGC_RXDCTL(0), 0);

	/* This is useful क्रम snअगरfing bad packets. */
	अगर (adapter->netdev->features & NETIF_F_RXALL) अणु
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in set_rx_mode
		 */
		rctl |= (IGC_RCTL_SBP | /* Receive bad packets */
			 IGC_RCTL_BAM | /* RX All Bcast Pkts */
			 IGC_RCTL_PMCF); /* RX All MAC Ctrl Pkts */

		rctl &= ~(IGC_RCTL_DPF | /* Allow filtered छोड़ो */
			  IGC_RCTL_CFIEN); /* Disable VLAN CFIEN Filter */
	पूर्ण

	wr32(IGC_RCTL, rctl);
पूर्ण

/**
 * igc_setup_tctl - configure the transmit control रेजिस्टरs
 * @adapter: Board निजी काष्ठाure
 */
अटल व्योम igc_setup_tctl(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 tctl;

	/* disable queue 0 which icould be enabled by शेष */
	wr32(IGC_TXDCTL(0), 0);

	/* Program the Transmit Control Register */
	tctl = rd32(IGC_TCTL);
	tctl &= ~IGC_TCTL_CT;
	tctl |= IGC_TCTL_PSP | IGC_TCTL_RTLC |
		(IGC_COLLISION_THRESHOLD << IGC_CT_SHIFT);

	/* Enable transmits */
	tctl |= IGC_TCTL_EN;

	wr32(IGC_TCTL, tctl);
पूर्ण

/**
 * igc_set_mac_filter_hw() - Set MAC address filter in hardware
 * @adapter: Poपूर्णांकer to adapter where the filter should be set
 * @index: Filter index
 * @type: MAC address filter type (source or destination)
 * @addr: MAC address
 * @queue: If non-negative, queue assignment feature is enabled and frames
 *         matching the filter are enqueued onto 'queue'. Otherwise, queue
 *         assignment is disabled.
 */
अटल व्योम igc_set_mac_filter_hw(काष्ठा igc_adapter *adapter, पूर्णांक index,
				  क्रमागत igc_mac_filter_type type,
				  स्थिर u8 *addr, पूर्णांक queue)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 ral, rah;

	अगर (WARN_ON(index >= hw->mac.rar_entry_count))
		वापस;

	ral = le32_to_cpup((__le32 *)(addr));
	rah = le16_to_cpup((__le16 *)(addr + 4));

	अगर (type == IGC_MAC_FILTER_TYPE_SRC) अणु
		rah &= ~IGC_RAH_ASEL_MASK;
		rah |= IGC_RAH_ASEL_SRC_ADDR;
	पूर्ण

	अगर (queue >= 0) अणु
		rah &= ~IGC_RAH_QSEL_MASK;
		rah |= (queue << IGC_RAH_QSEL_SHIFT);
		rah |= IGC_RAH_QSEL_ENABLE;
	पूर्ण

	rah |= IGC_RAH_AV;

	wr32(IGC_RAL(index), ral);
	wr32(IGC_RAH(index), rah);

	netdev_dbg(dev, "MAC address filter set in HW: index %d", index);
पूर्ण

/**
 * igc_clear_mac_filter_hw() - Clear MAC address filter in hardware
 * @adapter: Poपूर्णांकer to adapter where the filter should be cleared
 * @index: Filter index
 */
अटल व्योम igc_clear_mac_filter_hw(काष्ठा igc_adapter *adapter, पूर्णांक index)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;

	अगर (WARN_ON(index >= hw->mac.rar_entry_count))
		वापस;

	wr32(IGC_RAL(index), 0);
	wr32(IGC_RAH(index), 0);

	netdev_dbg(dev, "MAC address filter cleared in HW: index %d", index);
पूर्ण

/* Set शेष MAC address क्रम the PF in the first RAR entry */
अटल व्योम igc_set_शेष_mac_filter(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	u8 *addr = adapter->hw.mac.addr;

	netdev_dbg(dev, "Set default MAC address filter: address %pM", addr);

	igc_set_mac_filter_hw(adapter, 0, IGC_MAC_FILTER_TYPE_DST, addr, -1);
पूर्ण

/**
 * igc_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक igc_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(hw->mac.addr, addr->sa_data, netdev->addr_len);

	/* set the correct pool क्रम the new PF MAC address in entry 0 */
	igc_set_शेष_mac_filter(adapter);

	वापस 0;
पूर्ण

/**
 *  igc_ग_लिखो_mc_addr_list - ग_लिखो multicast addresses to MTA
 *  @netdev: network पूर्णांकerface device काष्ठाure
 *
 *  Writes multicast address list to the MTA hash table.
 *  Returns: -ENOMEM on failure
 *           0 on no addresses written
 *           X on writing X addresses to MTA
 **/
अटल पूर्णांक igc_ग_लिखो_mc_addr_list(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u8  *mta_list;
	पूर्णांक i;

	अगर (netdev_mc_empty(netdev)) अणु
		/* nothing to program, so clear mc list */
		igc_update_mc_addr_list(hw, शून्य, 0);
		वापस 0;
	पूर्ण

	mta_list = kसुस्मृति(netdev_mc_count(netdev), 6, GFP_ATOMIC);
	अगर (!mta_list)
		वापस -ENOMEM;

	/* The shared function expects a packed array of only addresses. */
	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev)
		स_नकल(mta_list + (i++ * ETH_ALEN), ha->addr, ETH_ALEN);

	igc_update_mc_addr_list(hw, mta_list, i);
	kमुक्त(mta_list);

	वापस netdev_mc_count(netdev);
पूर्ण

अटल __le32 igc_tx_launchसमय(काष्ठा igc_adapter *adapter, kसमय_प्रकार txसमय)
अणु
	kसमय_प्रकार cycle_समय = adapter->cycle_समय;
	kसमय_प्रकार base_समय = adapter->base_समय;
	u32 launchसमय;

	/* FIXME: when using ETF together with taprio, we may have a
	 * हाल where 'delta' is larger than the cycle_समय, this may
	 * cause problems अगर we करोn't पढ़ो the current value of
	 * IGC_BASET, as the value ग_लिखोn पूर्णांकo the launchसमय
	 * descriptor field may be misपूर्णांकerpreted.
	 */
	भाग_s64_rem(kसमय_sub_ns(txसमय, base_समय), cycle_समय, &launchसमय);

	वापस cpu_to_le32(launchसमय);
पूर्ण

अटल व्योम igc_tx_ctxtdesc(काष्ठा igc_ring *tx_ring,
			    काष्ठा igc_tx_buffer *first,
			    u32 vlan_macip_lens, u32 type_tucmd,
			    u32 mss_l4len_idx)
अणु
	काष्ठा igc_adv_tx_context_desc *context_desc;
	u16 i = tx_ring->next_to_use;

	context_desc = IGC_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identअगरy this as an advanced context descriptor */
	type_tucmd |= IGC_TXD_CMD_DEXT | IGC_ADVTXD_DTYP_CTXT;

	/* For i225, context index must be unique per ring. */
	अगर (test_bit(IGC_RING_FLAG_TX_CTX_IDX, &tx_ring->flags))
		mss_l4len_idx |= tx_ring->reg_idx << 4;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);

	/* We assume there is always a valid Tx समय available. Invalid बार
	 * should have been handled by the upper layers.
	 */
	अगर (tx_ring->launchसमय_enable) अणु
		काष्ठा igc_adapter *adapter = netdev_priv(tx_ring->netdev);
		kसमय_प्रकार txसमय = first->skb->tstamp;

		skb_txसमय_consumed(first->skb);
		context_desc->launch_समय = igc_tx_launchसमय(adapter,
							      txसमय);
	पूर्ण अन्यथा अणु
		context_desc->launch_समय = 0;
	पूर्ण
पूर्ण

अटल व्योम igc_tx_csum(काष्ठा igc_ring *tx_ring, काष्ठा igc_tx_buffer *first)
अणु
	काष्ठा sk_buff *skb = first->skb;
	u32 vlan_macip_lens = 0;
	u32 type_tucmd = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
csum_failed:
		अगर (!(first->tx_flags & IGC_TX_FLAGS_VLAN) &&
		    !tx_ring->launchसमय_enable)
			वापस;
		जाओ no_csum;
	पूर्ण

	चयन (skb->csum_offset) अणु
	हाल दुरत्व(काष्ठा tcphdr, check):
		type_tucmd = IGC_ADVTXD_TUCMD_L4T_TCP;
		fallthrough;
	हाल दुरत्व(काष्ठा udphdr, check):
		अवरोध;
	हाल दुरत्व(काष्ठा sctphdr, checksum):
		/* validate that this is actually an SCTP request */
		अगर (skb_csum_is_sctp(skb)) अणु
			type_tucmd = IGC_ADVTXD_TUCMD_L4T_SCTP;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		skb_checksum_help(skb);
		जाओ csum_failed;
	पूर्ण

	/* update TX checksum flag */
	first->tx_flags |= IGC_TX_FLAGS_CSUM;
	vlan_macip_lens = skb_checksum_start_offset(skb) -
			  skb_network_offset(skb);
no_csum:
	vlan_macip_lens |= skb_network_offset(skb) << IGC_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IGC_TX_FLAGS_VLAN_MASK;

	igc_tx_ctxtdesc(tx_ring, first, vlan_macip_lens, type_tucmd, 0);
पूर्ण

अटल पूर्णांक __igc_maybe_stop_tx(काष्ठा igc_ring *tx_ring, स्थिर u16 size)
अणु
	काष्ठा net_device *netdev = tx_ring->netdev;

	netअगर_stop_subqueue(netdev, tx_ring->queue_index);

	/* memory barriier comment */
	smp_mb();

	/* We need to check again in a हाल another CPU has just
	 * made room available.
	 */
	अगर (igc_desc_unused(tx_ring) < size)
		वापस -EBUSY;

	/* A reprieve! */
	netअगर_wake_subqueue(netdev, tx_ring->queue_index);

	u64_stats_update_begin(&tx_ring->tx_syncp2);
	tx_ring->tx_stats.restart_queue2++;
	u64_stats_update_end(&tx_ring->tx_syncp2);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक igc_maybe_stop_tx(काष्ठा igc_ring *tx_ring, स्थिर u16 size)
अणु
	अगर (igc_desc_unused(tx_ring) >= size)
		वापस 0;
	वापस __igc_maybe_stop_tx(tx_ring, size);
पूर्ण

#घोषणा IGC_SET_FLAG(_input, _flag, _result) \
	(((_flag) <= (_result)) ?				\
	 ((u32)((_input) & (_flag)) * ((_result) / (_flag))) :	\
	 ((u32)((_input) & (_flag)) / ((_flag) / (_result))))

अटल u32 igc_tx_cmd_type(u32 tx_flags)
अणु
	/* set type क्रम advanced descriptor with frame checksum insertion */
	u32 cmd_type = IGC_ADVTXD_DTYP_DATA |
		       IGC_ADVTXD_DCMD_DEXT |
		       IGC_ADVTXD_DCMD_IFCS;

	/* set segmentation bits क्रम TSO */
	cmd_type |= IGC_SET_FLAG(tx_flags, IGC_TX_FLAGS_TSO,
				 (IGC_ADVTXD_DCMD_TSE));

	/* set बारtamp bit अगर present */
	cmd_type |= IGC_SET_FLAG(tx_flags, IGC_TX_FLAGS_TSTAMP,
				 (IGC_ADVTXD_MAC_TSTAMP));

	वापस cmd_type;
पूर्ण

अटल व्योम igc_tx_olinfo_status(काष्ठा igc_ring *tx_ring,
				 जोड़ igc_adv_tx_desc *tx_desc,
				 u32 tx_flags, अचिन्हित पूर्णांक paylen)
अणु
	u32 olinfo_status = paylen << IGC_ADVTXD_PAYLEN_SHIFT;

	/* insert L4 checksum */
	olinfo_status |= (tx_flags & IGC_TX_FLAGS_CSUM) *
			  ((IGC_TXD_POPTS_TXSM << 8) /
			  IGC_TX_FLAGS_CSUM);

	/* insert IPv4 checksum */
	olinfo_status |= (tx_flags & IGC_TX_FLAGS_IPV4) *
			  (((IGC_TXD_POPTS_IXSM << 8)) /
			  IGC_TX_FLAGS_IPV4);

	tx_desc->पढ़ो.olinfo_status = cpu_to_le32(olinfo_status);
पूर्ण

अटल पूर्णांक igc_tx_map(काष्ठा igc_ring *tx_ring,
		      काष्ठा igc_tx_buffer *first,
		      स्थिर u8 hdr_len)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा igc_tx_buffer *tx_buffer;
	जोड़ igc_adv_tx_desc *tx_desc;
	u32 tx_flags = first->tx_flags;
	skb_frag_t *frag;
	u16 i = tx_ring->next_to_use;
	अचिन्हित पूर्णांक data_len, size;
	dma_addr_t dma;
	u32 cmd_type = igc_tx_cmd_type(tx_flags);

	tx_desc = IGC_TX_DESC(tx_ring, i);

	igc_tx_olinfo_status(tx_ring, tx_desc, tx_flags, skb->len - hdr_len);

	size = skb_headlen(skb);
	data_len = skb->data_len;

	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buffer = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buffer, len, size);
		dma_unmap_addr_set(tx_buffer, dma, dma);

		tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

		जबतक (unlikely(size > IGC_MAX_DATA_PER_TXD)) अणु
			tx_desc->पढ़ो.cmd_type_len =
				cpu_to_le32(cmd_type ^ IGC_MAX_DATA_PER_TXD);

			i++;
			tx_desc++;
			अगर (i == tx_ring->count) अणु
				tx_desc = IGC_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण
			tx_desc->पढ़ो.olinfo_status = 0;

			dma += IGC_MAX_DATA_PER_TXD;
			size -= IGC_MAX_DATA_PER_TXD;

			tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type ^ size);

		i++;
		tx_desc++;
		अगर (i == tx_ring->count) अणु
			tx_desc = IGC_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण
		tx_desc->पढ़ो.olinfo_status = 0;

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0,
				       size, DMA_TO_DEVICE);

		tx_buffer = &tx_ring->tx_buffer_info[i];
	पूर्ण

	/* ग_लिखो last descriptor with RS and EOP bits */
	cmd_type |= size | IGC_TXD_DCMD;
	tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);

	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	/* set the बारtamp */
	first->समय_stamp = jअगरfies;

	skb_tx_बारtamp(skb);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.  (Only applicable क्रम weak-ordered
	 * memory model archs, such as IA-64).
	 *
	 * We also need this memory barrier to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	i++;
	अगर (i == tx_ring->count)
		i = 0;

	tx_ring->next_to_use = i;

	/* Make sure there is space in the ring क्रम the next send. */
	igc_maybe_stop_tx(tx_ring, DESC_NEEDED);

	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more()) अणु
		ग_लिखोl(i, tx_ring->tail);
	पूर्ण

	वापस 0;
dma_error:
	netdev_err(tx_ring->netdev, "TX DMA map failed\n");
	tx_buffer = &tx_ring->tx_buffer_info[i];

	/* clear dma mappings क्रम failed tx_buffer_info map */
	जबतक (tx_buffer != first) अणु
		अगर (dma_unmap_len(tx_buffer, len))
			dma_unmap_page(tx_ring->dev,
				       dma_unmap_addr(tx_buffer, dma),
				       dma_unmap_len(tx_buffer, len),
				       DMA_TO_DEVICE);
		dma_unmap_len_set(tx_buffer, len, 0);

		अगर (i-- == 0)
			i += tx_ring->count;
		tx_buffer = &tx_ring->tx_buffer_info[i];
	पूर्ण

	अगर (dma_unmap_len(tx_buffer, len))
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);
	dma_unmap_len_set(tx_buffer, len, 0);

	dev_kमुक्त_skb_any(tx_buffer->skb);
	tx_buffer->skb = शून्य;

	tx_ring->next_to_use = i;

	वापस -1;
पूर्ण

अटल पूर्णांक igc_tso(काष्ठा igc_ring *tx_ring,
		   काष्ठा igc_tx_buffer *first,
		   u8 *hdr_len)
अणु
	u32 vlan_macip_lens, type_tucmd, mss_l4len_idx;
	काष्ठा sk_buff *skb = first->skb;
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
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_checksum_start(skb);

	/* ADV DTYP TUCMD MKRLOC/ISCSIHEDLEN */
	type_tucmd = IGC_ADVTXD_TUCMD_L4T_TCP;

	/* initialize outer IP header fields */
	अगर (ip.v4->version == 4) अणु
		अचिन्हित अक्षर *csum_start = skb_checksum_start(skb);
		अचिन्हित अक्षर *trans_start = ip.hdr + (ip.v4->ihl * 4);

		/* IP header will have to cancel out any data that
		 * is not a part of the outer IP header
		 */
		ip.v4->check = csum_fold(csum_partial(trans_start,
						      csum_start - trans_start,
						      0));
		type_tucmd |= IGC_ADVTXD_TUCMD_IPV4;

		ip.v4->tot_len = 0;
		first->tx_flags |= IGC_TX_FLAGS_TSO |
				   IGC_TX_FLAGS_CSUM |
				   IGC_TX_FLAGS_IPV4;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
		first->tx_flags |= IGC_TX_FLAGS_TSO |
				   IGC_TX_FLAGS_CSUM;
	पूर्ण

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;

	/* हटाओ payload length from inner checksum */
	paylen = skb->len - l4_offset;
	अगर (type_tucmd & IGC_ADVTXD_TUCMD_L4T_TCP) अणु
		/* compute length of segmentation header */
		*hdr_len = (l4.tcp->करोff * 4) + l4_offset;
		csum_replace_by_dअगरf(&l4.tcp->check,
				     (__क्रमce __wsum)htonl(paylen));
	पूर्ण अन्यथा अणु
		/* compute length of segmentation header */
		*hdr_len = माप(*l4.udp) + l4_offset;
		csum_replace_by_dअगरf(&l4.udp->check,
				     (__क्रमce __wsum)htonl(paylen));
	पूर्ण

	/* update gso size and bytecount with header size */
	first->gso_segs = skb_shinfo(skb)->gso_segs;
	first->bytecount += (first->gso_segs - 1) * *hdr_len;

	/* MSS L4LEN IDX */
	mss_l4len_idx = (*hdr_len - l4_offset) << IGC_ADVTXD_L4LEN_SHIFT;
	mss_l4len_idx |= skb_shinfo(skb)->gso_size << IGC_ADVTXD_MSS_SHIFT;

	/* VLAN MACLEN IPLEN */
	vlan_macip_lens = l4.hdr - ip.hdr;
	vlan_macip_lens |= (ip.hdr - skb->data) << IGC_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IGC_TX_FLAGS_VLAN_MASK;

	igc_tx_ctxtdesc(tx_ring, first, vlan_macip_lens,
			type_tucmd, mss_l4len_idx);

	वापस 1;
पूर्ण

अटल netdev_tx_t igc_xmit_frame_ring(काष्ठा sk_buff *skb,
				       काष्ठा igc_ring *tx_ring)
अणु
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
	__be16 protocol = vlan_get_protocol(skb);
	काष्ठा igc_tx_buffer *first;
	u32 tx_flags = 0;
	अचिन्हित लघु f;
	u8 hdr_len = 0;
	पूर्णांक tso = 0;

	/* need: 1 descriptor per page * PAGE_SIZE/IGC_MAX_DATA_PER_TXD,
	 *	+ 1 desc क्रम skb_headlen/IGC_MAX_DATA_PER_TXD,
	 *	+ 2 desc gap to keep tail from touching head,
	 *	+ 1 desc क्रम context descriptor,
	 * otherwise try next समय
	 */
	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++)
		count += TXD_USE_COUNT(skb_frag_size(
						&skb_shinfo(skb)->frags[f]));

	अगर (igc_maybe_stop_tx(tx_ring, count + 3)) अणु
		/* this is a hard error */
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) अणु
		काष्ठा igc_adapter *adapter = netdev_priv(tx_ring->netdev);

		/* FIXME: add support क्रम retrieving बारtamps from
		 * the other समयr रेजिस्टरs beक्रमe skipping the
		 * बारtamping request.
		 */
		अगर (adapter->tstamp_config.tx_type == HWTSTAMP_TX_ON &&
		    !test_and_set_bit_lock(__IGC_PTP_TX_IN_PROGRESS,
					   &adapter->state)) अणु
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
			tx_flags |= IGC_TX_FLAGS_TSTAMP;

			adapter->ptp_tx_skb = skb_get(skb);
			adapter->ptp_tx_start = jअगरfies;
		पूर्ण अन्यथा अणु
			adapter->tx_hwtstamp_skipped++;
		पूर्ण
	पूर्ण

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;
	first->protocol = protocol;

	tso = igc_tso(tx_ring, first, &hdr_len);
	अगर (tso < 0)
		जाओ out_drop;
	अन्यथा अगर (!tso)
		igc_tx_csum(tx_ring, first);

	igc_tx_map(tx_ring, first, hdr_len);

	वापस NETDEV_TX_OK;

out_drop:
	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;

	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत काष्ठा igc_ring *igc_tx_queue_mapping(काष्ठा igc_adapter *adapter,
						    काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक r_idx = skb->queue_mapping;

	अगर (r_idx >= adapter->num_tx_queues)
		r_idx = r_idx % adapter->num_tx_queues;

	वापस adapter->tx_ring[r_idx];
पूर्ण

अटल netdev_tx_t igc_xmit_frame(काष्ठा sk_buff *skb,
				  काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	/* The minimum packet size with TCTL.PSP set is 17 so pad the skb
	 * in order to meet this minimum size requirement.
	 */
	अगर (skb->len < 17) अणु
		अगर (skb_padto(skb, 17))
			वापस NETDEV_TX_OK;
		skb->len = 17;
	पूर्ण

	वापस igc_xmit_frame_ring(skb, igc_tx_queue_mapping(adapter, skb));
पूर्ण

अटल व्योम igc_rx_checksum(काष्ठा igc_ring *ring,
			    जोड़ igc_adv_rx_desc *rx_desc,
			    काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	/* Ignore Checksum bit is set */
	अगर (igc_test_staterr(rx_desc, IGC_RXD_STAT_IXSM))
		वापस;

	/* Rx checksum disabled via ethtool */
	अगर (!(ring->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* TCP/UDP checksum error bit is set */
	अगर (igc_test_staterr(rx_desc,
			     IGC_RXDEXT_STATERR_L4E |
			     IGC_RXDEXT_STATERR_IPE)) अणु
		/* work around errata with sctp packets where the TCPE aka
		 * L4E bit is set incorrectly on 64 byte (60 byte w/o crc)
		 * packets (aka let the stack check the crc32c)
		 */
		अगर (!(skb->len == 60 &&
		      test_bit(IGC_RING_FLAG_RX_SCTP_CSUM, &ring->flags))) अणु
			u64_stats_update_begin(&ring->rx_syncp);
			ring->rx_stats.csum_err++;
			u64_stats_update_end(&ring->rx_syncp);
		पूर्ण
		/* let the stack verअगरy checksum errors */
		वापस;
	पूर्ण
	/* It must be a TCP or UDP packet with a valid checksum */
	अगर (igc_test_staterr(rx_desc, IGC_RXD_STAT_TCPCS |
				      IGC_RXD_STAT_UDPCS))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	netdev_dbg(ring->netdev, "cksum success: bits %08X\n",
		   le32_to_cpu(rx_desc->wb.upper.status_error));
पूर्ण

अटल अंतरभूत व्योम igc_rx_hash(काष्ठा igc_ring *ring,
			       जोड़ igc_adv_rx_desc *rx_desc,
			       काष्ठा sk_buff *skb)
अणु
	अगर (ring->netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb,
			     le32_to_cpu(rx_desc->wb.lower.hi_dword.rss),
			     PKT_HASH_TYPE_L3);
पूर्ण

/**
 * igc_process_skb_fields - Populate skb header fields from Rx descriptor
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being populated
 *
 * This function checks the ring, descriptor, and packet inक्रमmation in order
 * to populate the hash, checksum, VLAN, protocol, and other fields within the
 * skb.
 */
अटल व्योम igc_process_skb_fields(काष्ठा igc_ring *rx_ring,
				   जोड़ igc_adv_rx_desc *rx_desc,
				   काष्ठा sk_buff *skb)
अणु
	igc_rx_hash(rx_ring, rx_desc, skb);

	igc_rx_checksum(rx_ring, rx_desc, skb);

	skb_record_rx_queue(skb, rx_ring->queue_index);

	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
पूर्ण

अटल काष्ठा igc_rx_buffer *igc_get_rx_buffer(काष्ठा igc_ring *rx_ring,
					       स्थिर अचिन्हित पूर्णांक size,
					       पूर्णांक *rx_buffer_pgcnt)
अणु
	काष्ठा igc_rx_buffer *rx_buffer;

	rx_buffer = &rx_ring->rx_buffer_info[rx_ring->next_to_clean];
	*rx_buffer_pgcnt =
#अगर (PAGE_SIZE < 8192)
		page_count(rx_buffer->page);
#अन्यथा
		0;
#पूर्ण_अगर
	prefetchw(rx_buffer->page);

	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);

	rx_buffer->pagecnt_bias--;

	वापस rx_buffer;
पूर्ण

अटल व्योम igc_rx_buffer_flip(काष्ठा igc_rx_buffer *buffer,
			       अचिन्हित पूर्णांक truesize)
अणु
#अगर (PAGE_SIZE < 8192)
	buffer->page_offset ^= truesize;
#अन्यथा
	buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित पूर्णांक igc_get_rx_frame_truesize(काष्ठा igc_ring *ring,
					      अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize;

#अगर (PAGE_SIZE < 8192)
	truesize = igc_rx_pg_size(ring) / 2;
#अन्यथा
	truesize = ring_uses_build_skb(ring) ?
		   SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
		   SKB_DATA_ALIGN(IGC_SKB_PAD + size) :
		   SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	वापस truesize;
पूर्ण

/**
 * igc_add_rx_frag - Add contents of Rx buffer to sk_buff
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: buffer containing page to add
 * @skb: sk_buff to place the data पूर्णांकo
 * @size: size of buffer to be added
 *
 * This function will add the data contained in rx_buffer->page to the skb.
 */
अटल व्योम igc_add_rx_frag(काष्ठा igc_ring *rx_ring,
			    काष्ठा igc_rx_buffer *rx_buffer,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize;

#अगर (PAGE_SIZE < 8192)
	truesize = igc_rx_pg_size(rx_ring) / 2;
#अन्यथा
	truesize = ring_uses_build_skb(rx_ring) ?
		   SKB_DATA_ALIGN(IGC_SKB_PAD + size) :
		   SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buffer->page,
			rx_buffer->page_offset, size, truesize);

	igc_rx_buffer_flip(rx_buffer, truesize);
पूर्ण

अटल काष्ठा sk_buff *igc_build_skb(काष्ठा igc_ring *rx_ring,
				     काष्ठा igc_rx_buffer *rx_buffer,
				     जोड़ igc_adv_rx_desc *rx_desc,
				     अचिन्हित पूर्णांक size)
अणु
	व्योम *va = page_address(rx_buffer->page) + rx_buffer->page_offset;
	अचिन्हित पूर्णांक truesize = igc_get_rx_frame_truesize(rx_ring, size);
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(va);

	/* build an skb around the page buffer */
	skb = build_skb(va - IGC_SKB_PAD, truesize);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* update poपूर्णांकers within the skb to store the data */
	skb_reserve(skb, IGC_SKB_PAD);
	__skb_put(skb, size);

	igc_rx_buffer_flip(rx_buffer, truesize);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *igc_स्थिरruct_skb(काष्ठा igc_ring *rx_ring,
					 काष्ठा igc_rx_buffer *rx_buffer,
					 काष्ठा xdp_buff *xdp,
					 kसमय_प्रकार बारtamp)
अणु
	अचिन्हित पूर्णांक size = xdp->data_end - xdp->data;
	अचिन्हित पूर्णांक truesize = igc_get_rx_frame_truesize(rx_ring, size);
	व्योम *va = xdp->data;
	अचिन्हित पूर्णांक headlen;
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(va);

	/* allocate a skb to store the frags */
	skb = napi_alloc_skb(&rx_ring->q_vector->napi, IGC_RX_HDR_LEN);
	अगर (unlikely(!skb))
		वापस शून्य;

	अगर (बारtamp)
		skb_hwtstamps(skb)->hwtstamp = बारtamp;

	/* Determine available headroom क्रम copy */
	headlen = size;
	अगर (headlen > IGC_RX_HDR_LEN)
		headlen = eth_get_headlen(skb->dev, va, IGC_RX_HDR_LEN);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	स_नकल(__skb_put(skb, headlen), va, ALIGN(headlen, माप(दीर्घ)));

	/* update all of the poपूर्णांकers */
	size -= headlen;
	अगर (size) अणु
		skb_add_rx_frag(skb, 0, rx_buffer->page,
				(va + headlen) - page_address(rx_buffer->page),
				size, truesize);
		igc_rx_buffer_flip(rx_buffer, truesize);
	पूर्ण अन्यथा अणु
		rx_buffer->pagecnt_bias++;
	पूर्ण

	वापस skb;
पूर्ण

/**
 * igc_reuse_rx_page - page flip buffer and store it back on the ring
 * @rx_ring: rx descriptor ring to store buffers on
 * @old_buff: करोnor buffer to have page reused
 *
 * Synchronizes page क्रम reuse by the adapter
 */
अटल व्योम igc_reuse_rx_page(काष्ठा igc_ring *rx_ring,
			      काष्ठा igc_rx_buffer *old_buff)
अणु
	u16 nta = rx_ring->next_to_alloc;
	काष्ठा igc_rx_buffer *new_buff;

	new_buff = &rx_ring->rx_buffer_info[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* Transfer page from old buffer to new buffer.
	 * Move each member inभागidually to aव्योम possible store
	 * क्रमwarding stalls.
	 */
	new_buff->dma		= old_buff->dma;
	new_buff->page		= old_buff->page;
	new_buff->page_offset	= old_buff->page_offset;
	new_buff->pagecnt_bias	= old_buff->pagecnt_bias;
पूर्ण

अटल bool igc_can_reuse_rx_page(काष्ठा igc_rx_buffer *rx_buffer,
				  पूर्णांक rx_buffer_pgcnt)
अणु
	अचिन्हित पूर्णांक pagecnt_bias = rx_buffer->pagecnt_bias;
	काष्ठा page *page = rx_buffer->page;

	/* aव्योम re-using remote and pfmeदो_स्मृति pages */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely((rx_buffer_pgcnt - pagecnt_bias) > 1))
		वापस false;
#अन्यथा
#घोषणा IGC_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - IGC_RXBUFFER_2048)

	अगर (rx_buffer->page_offset > IGC_LAST_OFFSET)
		वापस false;
#पूर्ण_अगर

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	अगर (unlikely(pagecnt_bias == 1)) अणु
		page_ref_add(page, अच_लघु_उच्च - 1);
		rx_buffer->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण

	वापस true;
पूर्ण

/**
 * igc_is_non_eop - process handling of non-EOP buffers
 * @rx_ring: Rx ring being processed
 * @rx_desc: Rx descriptor क्रम current buffer
 *
 * This function updates next to clean.  If the buffer is an EOP buffer
 * this function निकासs वापसing false, otherwise it will place the
 * sk_buff in the next buffer to be chained and वापस true indicating
 * that this is in fact a non-EOP buffer.
 */
अटल bool igc_is_non_eop(काष्ठा igc_ring *rx_ring,
			   जोड़ igc_adv_rx_desc *rx_desc)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(IGC_RX_DESC(rx_ring, ntc));

	अगर (likely(igc_test_staterr(rx_desc, IGC_RXD_STAT_EOP)))
		वापस false;

	वापस true;
पूर्ण

/**
 * igc_cleanup_headers - Correct corrupted or empty headers
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being fixed
 *
 * Address the हाल where we are pulling data in on pages only
 * and as such no data is present in the skb header.
 *
 * In addition अगर skb is not at least 60 bytes we need to pad it so that
 * it is large enough to qualअगरy as a valid Ethernet frame.
 *
 * Returns true अगर an error was encountered and skb was मुक्तd.
 */
अटल bool igc_cleanup_headers(काष्ठा igc_ring *rx_ring,
				जोड़ igc_adv_rx_desc *rx_desc,
				काष्ठा sk_buff *skb)
अणु
	/* XDP packets use error poपूर्णांकer so पात at this poपूर्णांक */
	अगर (IS_ERR(skb))
		वापस true;

	अगर (unlikely(igc_test_staterr(rx_desc, IGC_RXDEXT_STATERR_RXE))) अणु
		काष्ठा net_device *netdev = rx_ring->netdev;

		अगर (!(netdev->features & NETIF_F_RXALL)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस true;
		पूर्ण
	पूर्ण

	/* अगर eth_skb_pad वापसs an error the skb was मुक्तd */
	अगर (eth_skb_pad(skb))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम igc_put_rx_buffer(काष्ठा igc_ring *rx_ring,
			      काष्ठा igc_rx_buffer *rx_buffer,
			      पूर्णांक rx_buffer_pgcnt)
अणु
	अगर (igc_can_reuse_rx_page(rx_buffer, rx_buffer_pgcnt)) अणु
		/* hand second half of page back to the ring */
		igc_reuse_rx_page(rx_ring, rx_buffer);
	पूर्ण अन्यथा अणु
		/* We are not reusing the buffer so unmap it and मुक्त
		 * any references we are holding to it
		 */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     igc_rx_pg_size(rx_ring), DMA_FROM_DEVICE,
				     IGC_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	पूर्ण

	/* clear contents of rx_buffer */
	rx_buffer->page = शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक igc_rx_offset(काष्ठा igc_ring *rx_ring)
अणु
	काष्ठा igc_adapter *adapter = rx_ring->q_vector->adapter;

	अगर (ring_uses_build_skb(rx_ring))
		वापस IGC_SKB_PAD;
	अगर (igc_xdp_is_enabled(adapter))
		वापस XDP_PACKET_HEADROOM;

	वापस 0;
पूर्ण

अटल bool igc_alloc_mapped_page(काष्ठा igc_ring *rx_ring,
				  काष्ठा igc_rx_buffer *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should selकरोm need to alloc */
	अगर (likely(page))
		वापस true;

	/* alloc new page क्रम storage */
	page = dev_alloc_pages(igc_rx_pg_order(rx_ring));
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 igc_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE,
				 IGC_RX_DMA_ATTR);

	/* अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_page(page);

		rx_ring->rx_stats.alloc_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = igc_rx_offset(rx_ring);
	page_ref_add(page, अच_लघु_उच्च - 1);
	bi->pagecnt_bias = अच_लघु_उच्च;

	वापस true;
पूर्ण

/**
 * igc_alloc_rx_buffers - Replace used receive buffers; packet split
 * @rx_ring: rx descriptor ring
 * @cleaned_count: number of buffers to clean
 */
अटल व्योम igc_alloc_rx_buffers(काष्ठा igc_ring *rx_ring, u16 cleaned_count)
अणु
	जोड़ igc_adv_rx_desc *rx_desc;
	u16 i = rx_ring->next_to_use;
	काष्ठा igc_rx_buffer *bi;
	u16 bufsz;

	/* nothing to करो */
	अगर (!cleaned_count)
		वापस;

	rx_desc = IGC_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer_info[i];
	i -= rx_ring->count;

	bufsz = igc_rx_bufsz(rx_ring);

	करो अणु
		अगर (!igc_alloc_mapped_page(rx_ring, bi))
			अवरोध;

		/* sync the buffer क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, bi->dma,
						 bi->page_offset, bufsz,
						 DMA_FROM_DEVICE);

		/* Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		i++;
		अगर (unlikely(!i)) अणु
			rx_desc = IGC_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer_info;
			i -= rx_ring->count;
		पूर्ण

		/* clear the length क्रम the next_to_use descriptor */
		rx_desc->wb.upper.length = 0;

		cleaned_count--;
	पूर्ण जबतक (cleaned_count);

	i += rx_ring->count;

	अगर (rx_ring->next_to_use != i) अणु
		/* record the next descriptor to use */
		rx_ring->next_to_use = i;

		/* update next to alloc since we have filled the ring */
		rx_ring->next_to_alloc = i;

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		ग_लिखोl(i, rx_ring->tail);
	पूर्ण
पूर्ण

अटल पूर्णांक igc_xdp_init_tx_buffer(काष्ठा igc_tx_buffer *buffer,
				  काष्ठा xdp_frame *xdpf,
				  काष्ठा igc_ring *ring)
अणु
	dma_addr_t dma;

	dma = dma_map_single(ring->dev, xdpf->data, xdpf->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ring->dev, dma)) अणु
		netdev_err_once(ring->netdev, "Failed to map DMA for TX\n");
		वापस -ENOMEM;
	पूर्ण

	buffer->xdpf = xdpf;
	buffer->tx_flags = IGC_TX_FLAGS_XDP;
	buffer->protocol = 0;
	buffer->bytecount = xdpf->len;
	buffer->gso_segs = 1;
	buffer->समय_stamp = jअगरfies;
	dma_unmap_len_set(buffer, len, xdpf->len);
	dma_unmap_addr_set(buffer, dma, dma);
	वापस 0;
पूर्ण

/* This function requires __netअगर_tx_lock is held by the caller. */
अटल पूर्णांक igc_xdp_init_tx_descriptor(काष्ठा igc_ring *ring,
				      काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा igc_tx_buffer *buffer;
	जोड़ igc_adv_tx_desc *desc;
	u32 cmd_type, olinfo_status;
	पूर्णांक err;

	अगर (!igc_desc_unused(ring))
		वापस -EBUSY;

	buffer = &ring->tx_buffer_info[ring->next_to_use];
	err = igc_xdp_init_tx_buffer(buffer, xdpf, ring);
	अगर (err)
		वापस err;

	cmd_type = IGC_ADVTXD_DTYP_DATA | IGC_ADVTXD_DCMD_DEXT |
		   IGC_ADVTXD_DCMD_IFCS | IGC_TXD_DCMD |
		   buffer->bytecount;
	olinfo_status = buffer->bytecount << IGC_ADVTXD_PAYLEN_SHIFT;

	desc = IGC_TX_DESC(ring, ring->next_to_use);
	desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);
	desc->पढ़ो.olinfo_status = cpu_to_le32(olinfo_status);
	desc->पढ़ो.buffer_addr = cpu_to_le64(dma_unmap_addr(buffer, dma));

	netdev_tx_sent_queue(txring_txq(ring), buffer->bytecount);

	buffer->next_to_watch = desc;

	ring->next_to_use++;
	अगर (ring->next_to_use == ring->count)
		ring->next_to_use = 0;

	वापस 0;
पूर्ण

अटल काष्ठा igc_ring *igc_xdp_get_tx_ring(काष्ठा igc_adapter *adapter,
					    पूर्णांक cpu)
अणु
	पूर्णांक index = cpu;

	अगर (unlikely(index < 0))
		index = 0;

	जबतक (index >= adapter->num_tx_queues)
		index -= adapter->num_tx_queues;

	वापस adapter->tx_ring[index];
पूर्ण

अटल पूर्णांक igc_xdp_xmit_back(काष्ठा igc_adapter *adapter, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_frame *xdpf = xdp_convert_buff_to_frame(xdp);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा netdev_queue *nq;
	काष्ठा igc_ring *ring;
	पूर्णांक res;

	अगर (unlikely(!xdpf))
		वापस -EFAULT;

	ring = igc_xdp_get_tx_ring(adapter, cpu);
	nq = txring_txq(ring);

	__netअगर_tx_lock(nq, cpu);
	res = igc_xdp_init_tx_descriptor(ring, xdpf);
	__netअगर_tx_unlock(nq);
	वापस res;
पूर्ण

अटल काष्ठा sk_buff *igc_xdp_run_prog(काष्ठा igc_adapter *adapter,
					काष्ठा xdp_buff *xdp)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक res;
	u32 act;

	rcu_पढ़ो_lock();

	prog = READ_ONCE(adapter->xdp_prog);
	अगर (!prog) अणु
		res = IGC_XDP_PASS;
		जाओ unlock;
	पूर्ण

	act = bpf_prog_run_xdp(prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		res = IGC_XDP_PASS;
		अवरोध;
	हाल XDP_TX:
		अगर (igc_xdp_xmit_back(adapter, xdp) < 0)
			जाओ out_failure;
		res = IGC_XDP_TX;
		अवरोध;
	हाल XDP_REसूचीECT:
		अगर (xdp_करो_redirect(adapter->netdev, xdp, prog) < 0)
			जाओ out_failure;
		res = IGC_XDP_REसूचीECT;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(adapter->netdev, prog, act);
		fallthrough;
	हाल XDP_DROP:
		res = IGC_XDP_CONSUMED;
		अवरोध;
	पूर्ण

unlock:
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-res);
पूर्ण

/* This function assumes __netअगर_tx_lock is held by the caller. */
अटल व्योम igc_flush_tx_descriptors(काष्ठा igc_ring *ring)
अणु
	/* Once tail poपूर्णांकer is updated, hardware can fetch the descriptors
	 * any समय so we issue a ग_लिखो membar here to ensure all memory
	 * ग_लिखोs are complete beक्रमe the tail poपूर्णांकer is updated.
	 */
	wmb();
	ग_लिखोl(ring->next_to_use, ring->tail);
पूर्ण

अटल व्योम igc_finalize_xdp(काष्ठा igc_adapter *adapter, पूर्णांक status)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा netdev_queue *nq;
	काष्ठा igc_ring *ring;

	अगर (status & IGC_XDP_TX) अणु
		ring = igc_xdp_get_tx_ring(adapter, cpu);
		nq = txring_txq(ring);

		__netअगर_tx_lock(nq, cpu);
		igc_flush_tx_descriptors(ring);
		__netअगर_tx_unlock(nq);
	पूर्ण

	अगर (status & IGC_XDP_REसूचीECT)
		xdp_करो_flush();
पूर्ण

अटल पूर्णांक igc_clean_rx_irq(काष्ठा igc_q_vector *q_vector, स्थिर पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	काष्ठा igc_adapter *adapter = q_vector->adapter;
	काष्ठा igc_ring *rx_ring = q_vector->rx.ring;
	काष्ठा sk_buff *skb = rx_ring->skb;
	u16 cleaned_count = igc_desc_unused(rx_ring);
	पूर्णांक xdp_status = 0, rx_buffer_pgcnt;

	जबतक (likely(total_packets < budget)) अणु
		जोड़ igc_adv_rx_desc *rx_desc;
		काष्ठा igc_rx_buffer *rx_buffer;
		अचिन्हित पूर्णांक size, truesize;
		kसमय_प्रकार बारtamp = 0;
		काष्ठा xdp_buff xdp;
		पूर्णांक pkt_offset = 0;
		व्योम *pktbuf;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= IGC_RX_BUFFER_WRITE) अणु
			igc_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = IGC_RX_DESC(rx_ring, rx_ring->next_to_clean);
		size = le16_to_cpu(rx_desc->wb.upper.length);
		अगर (!size)
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we know the
		 * descriptor has been written back
		 */
		dma_rmb();

		rx_buffer = igc_get_rx_buffer(rx_ring, size, &rx_buffer_pgcnt);
		truesize = igc_get_rx_frame_truesize(rx_ring, size);

		pktbuf = page_address(rx_buffer->page) + rx_buffer->page_offset;

		अगर (igc_test_staterr(rx_desc, IGC_RXDADV_STAT_TSIP)) अणु
			बारtamp = igc_ptp_rx_pktstamp(q_vector->adapter,
							pktbuf);
			pkt_offset = IGC_TS_HDR_LEN;
			size -= IGC_TS_HDR_LEN;
		पूर्ण

		अगर (!skb) अणु
			xdp.data = pktbuf + pkt_offset;
			xdp.data_end = xdp.data + size;
			xdp.data_hard_start = pktbuf - igc_rx_offset(rx_ring);
			xdp_set_data_meta_invalid(&xdp);
			xdp.frame_sz = truesize;
			xdp.rxq = &rx_ring->xdp_rxq;

			skb = igc_xdp_run_prog(adapter, &xdp);
		पूर्ण

		अगर (IS_ERR(skb)) अणु
			अचिन्हित पूर्णांक xdp_res = -PTR_ERR(skb);

			चयन (xdp_res) अणु
			हाल IGC_XDP_CONSUMED:
				rx_buffer->pagecnt_bias++;
				अवरोध;
			हाल IGC_XDP_TX:
			हाल IGC_XDP_REसूचीECT:
				igc_rx_buffer_flip(rx_buffer, truesize);
				xdp_status |= xdp_res;
				अवरोध;
			पूर्ण

			total_packets++;
			total_bytes += size;
		पूर्ण अन्यथा अगर (skb)
			igc_add_rx_frag(rx_ring, rx_buffer, skb, size);
		अन्यथा अगर (ring_uses_build_skb(rx_ring))
			skb = igc_build_skb(rx_ring, rx_buffer, rx_desc, size);
		अन्यथा
			skb = igc_स्थिरruct_skb(rx_ring, rx_buffer, &xdp,
						बारtamp);

		/* निकास अगर we failed to retrieve a buffer */
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_failed++;
			rx_buffer->pagecnt_bias++;
			अवरोध;
		पूर्ण

		igc_put_rx_buffer(rx_ring, rx_buffer, rx_buffer_pgcnt);
		cleaned_count++;

		/* fetch next buffer in frame अगर non-eop */
		अगर (igc_is_non_eop(rx_ring, rx_desc))
			जारी;

		/* verअगरy the packet layout is correct */
		अगर (igc_cleanup_headers(rx_ring, rx_desc, skb)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* probably a little skewed due to removing CRC */
		total_bytes += skb->len;

		/* populate checksum, VLAN, and protocol */
		igc_process_skb_fields(rx_ring, rx_desc, skb);

		napi_gro_receive(&q_vector->napi, skb);

		/* reset skb poपूर्णांकer */
		skb = शून्य;

		/* update budget accounting */
		total_packets++;
	पूर्ण

	अगर (xdp_status)
		igc_finalize_xdp(adapter, xdp_status);

	/* place incomplete frames back on ring क्रम completion */
	rx_ring->skb = skb;

	u64_stats_update_begin(&rx_ring->rx_syncp);
	rx_ring->rx_stats.packets += total_packets;
	rx_ring->rx_stats.bytes += total_bytes;
	u64_stats_update_end(&rx_ring->rx_syncp);
	q_vector->rx.total_packets += total_packets;
	q_vector->rx.total_bytes += total_bytes;

	अगर (cleaned_count)
		igc_alloc_rx_buffers(rx_ring, cleaned_count);

	वापस total_packets;
पूर्ण

/**
 * igc_clean_tx_irq - Reclaim resources after transmit completes
 * @q_vector: poपूर्णांकer to q_vector containing needed info
 * @napi_budget: Used to determine अगर we are in netpoll
 *
 * वापसs true अगर ring is completely cleaned
 */
अटल bool igc_clean_tx_irq(काष्ठा igc_q_vector *q_vector, पूर्णांक napi_budget)
अणु
	काष्ठा igc_adapter *adapter = q_vector->adapter;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित पूर्णांक budget = q_vector->tx.work_limit;
	काष्ठा igc_ring *tx_ring = q_vector->tx.ring;
	अचिन्हित पूर्णांक i = tx_ring->next_to_clean;
	काष्ठा igc_tx_buffer *tx_buffer;
	जोड़ igc_adv_tx_desc *tx_desc;

	अगर (test_bit(__IGC_DOWN, &adapter->state))
		वापस true;

	tx_buffer = &tx_ring->tx_buffer_info[i];
	tx_desc = IGC_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		जोड़ igc_adv_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर DD is not set pending work has not been completed */
		अगर (!(eop_desc->wb.status & cpu_to_le32(IGC_TXD_STAT_DD)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buffer->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buffer->bytecount;
		total_packets += tx_buffer->gso_segs;

		अगर (tx_buffer->tx_flags & IGC_TX_FLAGS_XDP)
			xdp_वापस_frame(tx_buffer->xdpf);
		अन्यथा
			napi_consume_skb(tx_buffer->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		dma_unmap_len_set(tx_buffer, len, 0);

		/* clear last DMA location and unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IGC_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len)) अणु
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buffer, len, 0);
			पूर्ण
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buffer = tx_ring->tx_buffer_info;
			tx_desc = IGC_TX_DESC(tx_ring, 0);
		पूर्ण

		/* issue prefetch क्रम next Tx descriptor */
		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);

	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->tx_syncp);
	tx_ring->tx_stats.bytes += total_bytes;
	tx_ring->tx_stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->tx_syncp);
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;

	अगर (test_bit(IGC_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags)) अणु
		काष्ठा igc_hw *hw = &adapter->hw;

		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of समय_stamp and movement of i
		 */
		clear_bit(IGC_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags);
		अगर (tx_buffer->next_to_watch &&
		    समय_after(jअगरfies, tx_buffer->समय_stamp +
		    (adapter->tx_समयout_factor * HZ)) &&
		    !(rd32(IGC_STATUS) & IGC_STATUS_TXOFF)) अणु
			/* detected Tx unit hang */
			netdev_err(tx_ring->netdev,
				   "Detected Tx Unit Hang\n"
				   "  Tx Queue             <%d>\n"
				   "  TDH                  <%x>\n"
				   "  TDT                  <%x>\n"
				   "  next_to_use          <%x>\n"
				   "  next_to_clean        <%x>\n"
				   "buffer_info[next_to_clean]\n"
				   "  time_stamp           <%lx>\n"
				   "  next_to_watch        <%p>\n"
				   "  jiffies              <%lx>\n"
				   "  desc.status          <%x>\n",
				   tx_ring->queue_index,
				   rd32(IGC_TDH(tx_ring->reg_idx)),
				   पढ़ोl(tx_ring->tail),
				   tx_ring->next_to_use,
				   tx_ring->next_to_clean,
				   tx_buffer->समय_stamp,
				   tx_buffer->next_to_watch,
				   jअगरfies,
				   tx_buffer->next_to_watch->wb.status);
			netअगर_stop_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

			/* we are about to reset, no poपूर्णांक in enabling stuff */
			वापस true;
		पूर्ण
	पूर्ण

#घोषणा TX_WAKE_THRESHOLD (DESC_NEEDED * 2)
	अगर (unlikely(total_packets &&
		     netअगर_carrier_ok(tx_ring->netdev) &&
		     igc_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD)) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		    !(test_bit(__IGC_DOWN, &adapter->state))) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

			u64_stats_update_begin(&tx_ring->tx_syncp);
			tx_ring->tx_stats.restart_queue++;
			u64_stats_update_end(&tx_ring->tx_syncp);
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

अटल पूर्णांक igc_find_mac_filter(काष्ठा igc_adapter *adapter,
			       क्रमागत igc_mac_filter_type type, स्थिर u8 *addr)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक max_entries = hw->mac.rar_entry_count;
	u32 ral, rah;
	पूर्णांक i;

	क्रम (i = 0; i < max_entries; i++) अणु
		ral = rd32(IGC_RAL(i));
		rah = rd32(IGC_RAH(i));

		अगर (!(rah & IGC_RAH_AV))
			जारी;
		अगर (!!(rah & IGC_RAH_ASEL_SRC_ADDR) != type)
			जारी;
		अगर ((rah & IGC_RAH_RAH_MASK) !=
		    le16_to_cpup((__le16 *)(addr + 4)))
			जारी;
		अगर (ral != le32_to_cpup((__le32 *)(addr)))
			जारी;

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक igc_get_avail_mac_filter_slot(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक max_entries = hw->mac.rar_entry_count;
	u32 rah;
	पूर्णांक i;

	क्रम (i = 0; i < max_entries; i++) अणु
		rah = rd32(IGC_RAH(i));

		अगर (!(rah & IGC_RAH_AV))
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/**
 * igc_add_mac_filter() - Add MAC address filter
 * @adapter: Poपूर्णांकer to adapter where the filter should be added
 * @type: MAC address filter type (source or destination)
 * @addr: MAC address
 * @queue: If non-negative, queue assignment feature is enabled and frames
 *         matching the filter are enqueued onto 'queue'. Otherwise, queue
 *         assignment is disabled.
 *
 * Return: 0 in हाल of success, negative त्रुटि_सं code otherwise.
 */
अटल पूर्णांक igc_add_mac_filter(काष्ठा igc_adapter *adapter,
			      क्रमागत igc_mac_filter_type type, स्थिर u8 *addr,
			      पूर्णांक queue)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक index;

	index = igc_find_mac_filter(adapter, type, addr);
	अगर (index >= 0)
		जाओ update_filter;

	index = igc_get_avail_mac_filter_slot(adapter);
	अगर (index < 0)
		वापस -ENOSPC;

	netdev_dbg(dev, "Add MAC address filter: index %d type %s address %pM queue %d\n",
		   index, type == IGC_MAC_FILTER_TYPE_DST ? "dst" : "src",
		   addr, queue);

update_filter:
	igc_set_mac_filter_hw(adapter, index, type, addr, queue);
	वापस 0;
पूर्ण

/**
 * igc_del_mac_filter() - Delete MAC address filter
 * @adapter: Poपूर्णांकer to adapter where the filter should be deleted from
 * @type: MAC address filter type (source or destination)
 * @addr: MAC address
 */
अटल व्योम igc_del_mac_filter(काष्ठा igc_adapter *adapter,
			       क्रमागत igc_mac_filter_type type, स्थिर u8 *addr)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक index;

	index = igc_find_mac_filter(adapter, type, addr);
	अगर (index < 0)
		वापस;

	अगर (index == 0) अणु
		/* If this is the शेष filter, we करोn't actually delete it.
		 * We just reset to its शेष value i.e. disable queue
		 * assignment.
		 */
		netdev_dbg(dev, "Disable default MAC filter queue assignment");

		igc_set_mac_filter_hw(adapter, 0, type, addr, -1);
	पूर्ण अन्यथा अणु
		netdev_dbg(dev, "Delete MAC address filter: index %d type %s address %pM\n",
			   index,
			   type == IGC_MAC_FILTER_TYPE_DST ? "dst" : "src",
			   addr);

		igc_clear_mac_filter_hw(adapter, index);
	पूर्ण
पूर्ण

/**
 * igc_add_vlan_prio_filter() - Add VLAN priority filter
 * @adapter: Poपूर्णांकer to adapter where the filter should be added
 * @prio: VLAN priority value
 * @queue: Queue number which matching frames are asचिन्हित to
 *
 * Return: 0 in हाल of success, negative त्रुटि_सं code otherwise.
 */
अटल पूर्णांक igc_add_vlan_prio_filter(काष्ठा igc_adapter *adapter, पूर्णांक prio,
				    पूर्णांक queue)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 vlanpqf;

	vlanpqf = rd32(IGC_VLANPQF);

	अगर (vlanpqf & IGC_VLANPQF_VALID(prio)) अणु
		netdev_dbg(dev, "VLAN priority filter already in use\n");
		वापस -EEXIST;
	पूर्ण

	vlanpqf |= IGC_VLANPQF_QSEL(prio, queue);
	vlanpqf |= IGC_VLANPQF_VALID(prio);

	wr32(IGC_VLANPQF, vlanpqf);

	netdev_dbg(dev, "Add VLAN priority filter: prio %d queue %d\n",
		   prio, queue);
	वापस 0;
पूर्ण

/**
 * igc_del_vlan_prio_filter() - Delete VLAN priority filter
 * @adapter: Poपूर्णांकer to adapter where the filter should be deleted from
 * @prio: VLAN priority value
 */
अटल व्योम igc_del_vlan_prio_filter(काष्ठा igc_adapter *adapter, पूर्णांक prio)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 vlanpqf;

	vlanpqf = rd32(IGC_VLANPQF);

	vlanpqf &= ~IGC_VLANPQF_VALID(prio);
	vlanpqf &= ~IGC_VLANPQF_QSEL(prio, IGC_VLANPQF_QUEUE_MASK);

	wr32(IGC_VLANPQF, vlanpqf);

	netdev_dbg(adapter->netdev, "Delete VLAN priority filter: prio %d\n",
		   prio);
पूर्ण

अटल पूर्णांक igc_get_avail_etype_filter_slot(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_ETYPE_FILTER; i++) अणु
		u32 etqf = rd32(IGC_ETQF(i));

		अगर (!(etqf & IGC_ETQF_FILTER_ENABLE))
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/**
 * igc_add_etype_filter() - Add ethertype filter
 * @adapter: Poपूर्णांकer to adapter where the filter should be added
 * @etype: Ethertype value
 * @queue: If non-negative, queue assignment feature is enabled and frames
 *         matching the filter are enqueued onto 'queue'. Otherwise, queue
 *         assignment is disabled.
 *
 * Return: 0 in हाल of success, negative त्रुटि_सं code otherwise.
 */
अटल पूर्णांक igc_add_etype_filter(काष्ठा igc_adapter *adapter, u16 etype,
				पूर्णांक queue)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक index;
	u32 etqf;

	index = igc_get_avail_etype_filter_slot(adapter);
	अगर (index < 0)
		वापस -ENOSPC;

	etqf = rd32(IGC_ETQF(index));

	etqf &= ~IGC_ETQF_ETYPE_MASK;
	etqf |= etype;

	अगर (queue >= 0) अणु
		etqf &= ~IGC_ETQF_QUEUE_MASK;
		etqf |= (queue << IGC_ETQF_QUEUE_SHIFT);
		etqf |= IGC_ETQF_QUEUE_ENABLE;
	पूर्ण

	etqf |= IGC_ETQF_FILTER_ENABLE;

	wr32(IGC_ETQF(index), etqf);

	netdev_dbg(adapter->netdev, "Add ethertype filter: etype %04x queue %d\n",
		   etype, queue);
	वापस 0;
पूर्ण

अटल पूर्णांक igc_find_etype_filter(काष्ठा igc_adapter *adapter, u16 etype)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_ETYPE_FILTER; i++) अणु
		u32 etqf = rd32(IGC_ETQF(i));

		अगर ((etqf & IGC_ETQF_ETYPE_MASK) == etype)
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/**
 * igc_del_etype_filter() - Delete ethertype filter
 * @adapter: Poपूर्णांकer to adapter where the filter should be deleted from
 * @etype: Ethertype value
 */
अटल व्योम igc_del_etype_filter(काष्ठा igc_adapter *adapter, u16 etype)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक index;

	index = igc_find_etype_filter(adapter, etype);
	अगर (index < 0)
		वापस;

	wr32(IGC_ETQF(index), 0);

	netdev_dbg(adapter->netdev, "Delete ethertype filter: etype %04x\n",
		   etype);
पूर्ण

अटल पूर्णांक igc_enable_nfc_rule(काष्ठा igc_adapter *adapter,
			       स्थिर काष्ठा igc_nfc_rule *rule)
अणु
	पूर्णांक err;

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_ETHER_TYPE) अणु
		err = igc_add_etype_filter(adapter, rule->filter.etype,
					   rule->action);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_SRC_MAC_ADDR) अणु
		err = igc_add_mac_filter(adapter, IGC_MAC_FILTER_TYPE_SRC,
					 rule->filter.src_addr, rule->action);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_DST_MAC_ADDR) अणु
		err = igc_add_mac_filter(adapter, IGC_MAC_FILTER_TYPE_DST,
					 rule->filter.dst_addr, rule->action);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_VLAN_TCI) अणु
		पूर्णांक prio = (rule->filter.vlan_tci & VLAN_PRIO_MASK) >>
			   VLAN_PRIO_SHIFT;

		err = igc_add_vlan_prio_filter(adapter, prio, rule->action);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम igc_disable_nfc_rule(काष्ठा igc_adapter *adapter,
				 स्थिर काष्ठा igc_nfc_rule *rule)
अणु
	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_ETHER_TYPE)
		igc_del_etype_filter(adapter, rule->filter.etype);

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_VLAN_TCI) अणु
		पूर्णांक prio = (rule->filter.vlan_tci & VLAN_PRIO_MASK) >>
			   VLAN_PRIO_SHIFT;

		igc_del_vlan_prio_filter(adapter, prio);
	पूर्ण

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_SRC_MAC_ADDR)
		igc_del_mac_filter(adapter, IGC_MAC_FILTER_TYPE_SRC,
				   rule->filter.src_addr);

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_DST_MAC_ADDR)
		igc_del_mac_filter(adapter, IGC_MAC_FILTER_TYPE_DST,
				   rule->filter.dst_addr);
पूर्ण

/**
 * igc_get_nfc_rule() - Get NFC rule
 * @adapter: Poपूर्णांकer to adapter
 * @location: Rule location
 *
 * Context: Expects adapter->nfc_rule_lock to be held by caller.
 *
 * Return: Poपूर्णांकer to NFC rule at @location. If not found, शून्य.
 */
काष्ठा igc_nfc_rule *igc_get_nfc_rule(काष्ठा igc_adapter *adapter,
				      u32 location)
अणु
	काष्ठा igc_nfc_rule *rule;

	list_क्रम_each_entry(rule, &adapter->nfc_rule_list, list) अणु
		अगर (rule->location == location)
			वापस rule;
		अगर (rule->location > location)
			अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * igc_del_nfc_rule() - Delete NFC rule
 * @adapter: Poपूर्णांकer to adapter
 * @rule: Poपूर्णांकer to rule to be deleted
 *
 * Disable NFC rule in hardware and delete it from adapter.
 *
 * Context: Expects adapter->nfc_rule_lock to be held by caller.
 */
व्योम igc_del_nfc_rule(काष्ठा igc_adapter *adapter, काष्ठा igc_nfc_rule *rule)
अणु
	igc_disable_nfc_rule(adapter, rule);

	list_del(&rule->list);
	adapter->nfc_rule_count--;

	kमुक्त(rule);
पूर्ण

अटल व्योम igc_flush_nfc_rules(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_nfc_rule *rule, *पंचांगp;

	mutex_lock(&adapter->nfc_rule_lock);

	list_क्रम_each_entry_safe(rule, पंचांगp, &adapter->nfc_rule_list, list)
		igc_del_nfc_rule(adapter, rule);

	mutex_unlock(&adapter->nfc_rule_lock);
पूर्ण

/**
 * igc_add_nfc_rule() - Add NFC rule
 * @adapter: Poपूर्णांकer to adapter
 * @rule: Poपूर्णांकer to rule to be added
 *
 * Enable NFC rule in hardware and add it to adapter.
 *
 * Context: Expects adapter->nfc_rule_lock to be held by caller.
 *
 * Return: 0 on success, negative त्रुटि_सं on failure.
 */
पूर्णांक igc_add_nfc_rule(काष्ठा igc_adapter *adapter, काष्ठा igc_nfc_rule *rule)
अणु
	काष्ठा igc_nfc_rule *pred, *cur;
	पूर्णांक err;

	err = igc_enable_nfc_rule(adapter, rule);
	अगर (err)
		वापस err;

	pred = शून्य;
	list_क्रम_each_entry(cur, &adapter->nfc_rule_list, list) अणु
		अगर (cur->location >= rule->location)
			अवरोध;
		pred = cur;
	पूर्ण

	list_add(&rule->list, pred ? &pred->list : &adapter->nfc_rule_list);
	adapter->nfc_rule_count++;
	वापस 0;
पूर्ण

अटल व्योम igc_restore_nfc_rules(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_nfc_rule *rule;

	mutex_lock(&adapter->nfc_rule_lock);

	list_क्रम_each_entry_reverse(rule, &adapter->nfc_rule_list, list)
		igc_enable_nfc_rule(adapter, rule);

	mutex_unlock(&adapter->nfc_rule_lock);
पूर्ण

अटल पूर्णांक igc_uc_sync(काष्ठा net_device *netdev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	वापस igc_add_mac_filter(adapter, IGC_MAC_FILTER_TYPE_DST, addr, -1);
पूर्ण

अटल पूर्णांक igc_uc_unsync(काष्ठा net_device *netdev, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	igc_del_mac_filter(adapter, IGC_MAC_FILTER_TYPE_DST, addr);
	वापस 0;
पूर्ण

/**
 * igc_set_rx_mode - Secondary Unicast, Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_rx_mode entry poपूर्णांक is called whenever the unicast or multicast
 * address lists or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper unicast, multicast,
 * promiscuous mode, and all-multi behavior.
 */
अटल व्योम igc_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 rctl = 0, rlpml = MAX_JUMBO_FRAME_SIZE;
	पूर्णांक count;

	/* Check क्रम Promiscuous and All Multicast modes */
	अगर (netdev->flags & IFF_PROMISC) अणु
		rctl |= IGC_RCTL_UPE | IGC_RCTL_MPE;
	पूर्ण अन्यथा अणु
		अगर (netdev->flags & IFF_ALLMULTI) अणु
			rctl |= IGC_RCTL_MPE;
		पूर्ण अन्यथा अणु
			/* Write addresses to the MTA, अगर the attempt fails
			 * then we should just turn on promiscuous mode so
			 * that we can at least receive multicast traffic
			 */
			count = igc_ग_लिखो_mc_addr_list(netdev);
			अगर (count < 0)
				rctl |= IGC_RCTL_MPE;
		पूर्ण
	पूर्ण

	/* Write addresses to available RAR रेजिस्टरs, अगर there is not
	 * sufficient space to store all the addresses then enable
	 * unicast promiscuous mode
	 */
	अगर (__dev_uc_sync(netdev, igc_uc_sync, igc_uc_unsync))
		rctl |= IGC_RCTL_UPE;

	/* update state of unicast and multicast */
	rctl |= rd32(IGC_RCTL) & ~(IGC_RCTL_UPE | IGC_RCTL_MPE);
	wr32(IGC_RCTL, rctl);

#अगर (PAGE_SIZE < 8192)
	अगर (adapter->max_frame_size <= IGC_MAX_FRAME_BUILD_SKB)
		rlpml = IGC_MAX_FRAME_BUILD_SKB;
#पूर्ण_अगर
	wr32(IGC_RLPML, rlpml);
पूर्ण

/**
 * igc_configure - configure the hardware क्रम RX and TX
 * @adapter: निजी board काष्ठाure
 */
अटल व्योम igc_configure(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i = 0;

	igc_get_hw_control(adapter);
	igc_set_rx_mode(netdev);

	igc_setup_tctl(adapter);
	igc_setup_mrqc(adapter);
	igc_setup_rctl(adapter);

	igc_set_शेष_mac_filter(adapter);
	igc_restore_nfc_rules(adapter);

	igc_configure_tx(adapter);
	igc_configure_rx(adapter);

	igc_rx_fअगरo_flush_base(&adapter->hw);

	/* call igc_desc_unused which always leaves
	 * at least 1 descriptor unused to make sure
	 * next_to_use != next_to_clean
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा igc_ring *ring = adapter->rx_ring[i];

		igc_alloc_rx_buffers(ring, igc_desc_unused(ring));
	पूर्ण
पूर्ण

/**
 * igc_ग_लिखो_ivar - configure ivar क्रम given MSI-X vector
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @msix_vector: vector number we are allocating to a given ring
 * @index: row index of IVAR रेजिस्टर to ग_लिखो within IVAR table
 * @offset: column offset of in IVAR, should be multiple of 8
 *
 * The IVAR table consists of 2 columns,
 * each containing an cause allocation क्रम an Rx and Tx ring, and a
 * variable number of rows depending on the number of queues supported.
 */
अटल व्योम igc_ग_लिखो_ivar(काष्ठा igc_hw *hw, पूर्णांक msix_vector,
			   पूर्णांक index, पूर्णांक offset)
अणु
	u32 ivar = array_rd32(IGC_IVAR0, index);

	/* clear any bits that are currently set */
	ivar &= ~((u32)0xFF << offset);

	/* ग_लिखो vector and valid bit */
	ivar |= (msix_vector | IGC_IVAR_VALID) << offset;

	array_wr32(IGC_IVAR0, index, ivar);
पूर्ण

अटल व्योम igc_assign_vector(काष्ठा igc_q_vector *q_vector, पूर्णांक msix_vector)
अणु
	काष्ठा igc_adapter *adapter = q_vector->adapter;
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक rx_queue = IGC_N0_QUEUE;
	पूर्णांक tx_queue = IGC_N0_QUEUE;

	अगर (q_vector->rx.ring)
		rx_queue = q_vector->rx.ring->reg_idx;
	अगर (q_vector->tx.ring)
		tx_queue = q_vector->tx.ring->reg_idx;

	चयन (hw->mac.type) अणु
	हाल igc_i225:
		अगर (rx_queue > IGC_N0_QUEUE)
			igc_ग_लिखो_ivar(hw, msix_vector,
				       rx_queue >> 1,
				       (rx_queue & 0x1) << 4);
		अगर (tx_queue > IGC_N0_QUEUE)
			igc_ग_लिखो_ivar(hw, msix_vector,
				       tx_queue >> 1,
				       ((tx_queue & 0x1) << 4) + 8);
		q_vector->eims_value = BIT(msix_vector);
		अवरोध;
	शेष:
		WARN_ONCE(hw->mac.type != igc_i225, "Wrong MAC type\n");
		अवरोध;
	पूर्ण

	/* add q_vector eims value to global eims_enable_mask */
	adapter->eims_enable_mask |= q_vector->eims_value;

	/* configure q_vector to set itr on first पूर्णांकerrupt */
	q_vector->set_itr = 1;
पूर्ण

/**
 * igc_configure_msix - Configure MSI-X hardware
 * @adapter: Poपूर्णांकer to adapter काष्ठाure
 *
 * igc_configure_msix sets up the hardware to properly
 * generate MSI-X पूर्णांकerrupts.
 */
अटल व्योम igc_configure_msix(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक i, vector = 0;
	u32 पंचांगp;

	adapter->eims_enable_mask = 0;

	/* set vector क्रम other causes, i.e. link changes */
	चयन (hw->mac.type) अणु
	हाल igc_i225:
		/* Turn on MSI-X capability first, or our settings
		 * won't stick.  And it will take days to debug.
		 */
		wr32(IGC_GPIE, IGC_GPIE_MSIX_MODE |
		     IGC_GPIE_PBA | IGC_GPIE_EIAME |
		     IGC_GPIE_NSICR);

		/* enable msix_other पूर्णांकerrupt */
		adapter->eims_other = BIT(vector);
		पंचांगp = (vector++ | IGC_IVAR_VALID) << 8;

		wr32(IGC_IVAR_MISC, पंचांगp);
		अवरोध;
	शेष:
		/* करो nothing, since nothing अन्यथा supports MSI-X */
		अवरोध;
	पूर्ण /* चयन (hw->mac.type) */

	adapter->eims_enable_mask |= adapter->eims_other;

	क्रम (i = 0; i < adapter->num_q_vectors; i++)
		igc_assign_vector(adapter->q_vector[i], vector++);

	wrfl();
पूर्ण

/**
 * igc_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम igc_irq_enable(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;

	अगर (adapter->msix_entries) अणु
		u32 ims = IGC_IMS_LSC | IGC_IMS_DOUTSYNC | IGC_IMS_DRSTA;
		u32 regval = rd32(IGC_EIAC);

		wr32(IGC_EIAC, regval | adapter->eims_enable_mask);
		regval = rd32(IGC_EIAM);
		wr32(IGC_EIAM, regval | adapter->eims_enable_mask);
		wr32(IGC_EIMS, adapter->eims_enable_mask);
		wr32(IGC_IMS, ims);
	पूर्ण अन्यथा अणु
		wr32(IGC_IMS, IMS_ENABLE_MASK | IGC_IMS_DRSTA);
		wr32(IGC_IAM, IMS_ENABLE_MASK | IGC_IMS_DRSTA);
	पूर्ण
पूर्ण

/**
 * igc_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 */
अटल व्योम igc_irq_disable(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;

	अगर (adapter->msix_entries) अणु
		u32 regval = rd32(IGC_EIAM);

		wr32(IGC_EIAM, regval & ~adapter->eims_enable_mask);
		wr32(IGC_EIMC, adapter->eims_enable_mask);
		regval = rd32(IGC_EIAC);
		wr32(IGC_EIAC, regval & ~adapter->eims_enable_mask);
	पूर्ण

	wr32(IGC_IAM, 0);
	wr32(IGC_IMC, ~0);
	wrfl();

	अगर (adapter->msix_entries) अणु
		पूर्णांक vector = 0, i;

		synchronize_irq(adapter->msix_entries[vector++].vector);

		क्रम (i = 0; i < adapter->num_q_vectors; i++)
			synchronize_irq(adapter->msix_entries[vector++].vector);
	पूर्ण अन्यथा अणु
		synchronize_irq(adapter->pdev->irq);
	पूर्ण
पूर्ण

व्योम igc_set_flag_queue_pairs(काष्ठा igc_adapter *adapter,
			      स्थिर u32 max_rss_queues)
अणु
	/* Determine अगर we need to pair queues. */
	/* If rss_queues > half of max_rss_queues, pair the queues in
	 * order to conserve पूर्णांकerrupts due to limited supply.
	 */
	अगर (adapter->rss_queues > (max_rss_queues / 2))
		adapter->flags |= IGC_FLAG_QUEUE_PAIRS;
	अन्यथा
		adapter->flags &= ~IGC_FLAG_QUEUE_PAIRS;
पूर्ण

अचिन्हित पूर्णांक igc_get_max_rss_queues(काष्ठा igc_adapter *adapter)
अणु
	वापस IGC_MAX_RX_QUEUES;
पूर्ण

अटल व्योम igc_init_queue_configuration(काष्ठा igc_adapter *adapter)
अणु
	u32 max_rss_queues;

	max_rss_queues = igc_get_max_rss_queues(adapter);
	adapter->rss_queues = min_t(u32, max_rss_queues, num_online_cpus());

	igc_set_flag_queue_pairs(adapter, max_rss_queues);
पूर्ण

/**
 * igc_reset_q_vector - Reset config क्रम पूर्णांकerrupt vector
 * @adapter: board निजी काष्ठाure to initialize
 * @v_idx: Index of vector to be reset
 *
 * If NAPI is enabled it will delete any references to the
 * NAPI काष्ठा. This is preparation क्रम igc_मुक्त_q_vector.
 */
अटल व्योम igc_reset_q_vector(काष्ठा igc_adapter *adapter, पूर्णांक v_idx)
अणु
	काष्ठा igc_q_vector *q_vector = adapter->q_vector[v_idx];

	/* अगर we're coming from igc_set_पूर्णांकerrupt_capability, the vectors are
	 * not yet allocated
	 */
	अगर (!q_vector)
		वापस;

	अगर (q_vector->tx.ring)
		adapter->tx_ring[q_vector->tx.ring->queue_index] = शून्य;

	अगर (q_vector->rx.ring)
		adapter->rx_ring[q_vector->rx.ring->queue_index] = शून्य;

	netअगर_napi_del(&q_vector->napi);
पूर्ण

/**
 * igc_मुक्त_q_vector - Free memory allocated क्रम specअगरic पूर्णांकerrupt vector
 * @adapter: board निजी काष्ठाure to initialize
 * @v_idx: Index of vector to be मुक्तd
 *
 * This function मुक्तs the memory allocated to the q_vector.
 */
अटल व्योम igc_मुक्त_q_vector(काष्ठा igc_adapter *adapter, पूर्णांक v_idx)
अणु
	काष्ठा igc_q_vector *q_vector = adapter->q_vector[v_idx];

	adapter->q_vector[v_idx] = शून्य;

	/* igc_get_stats64() might access the rings on this vector,
	 * we must रुको a grace period beक्रमe मुक्तing it.
	 */
	अगर (q_vector)
		kमुक्त_rcu(q_vector, rcu);
पूर्ण

/**
 * igc_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This function मुक्तs the memory allocated to the q_vectors.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 */
अटल व्योम igc_मुक्त_q_vectors(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक v_idx = adapter->num_q_vectors;

	adapter->num_tx_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	जबतक (v_idx--) अणु
		igc_reset_q_vector(adapter, v_idx);
		igc_मुक्त_q_vector(adapter, v_idx);
	पूर्ण
पूर्ण

/**
 * igc_update_itr - update the dynamic ITR value based on statistics
 * @q_vector: poपूर्णांकer to q_vector
 * @ring_container: ring info to update the itr क्रम
 *
 * Stores a new ITR value based on packets and byte
 * counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 * computation is faster updates and more accurate ITR क्रम the current
 * traffic pattern.  Constants in this function were computed
 * based on theoretical maximum wire speed and thresholds were set based
 * on testing data as well as attempting to minimize response समय
 * जबतक increasing bulk throughput.
 * NOTE: These calculations are only valid when operating in a single-
 * queue environment.
 */
अटल व्योम igc_update_itr(काष्ठा igc_q_vector *q_vector,
			   काष्ठा igc_ring_container *ring_container)
अणु
	अचिन्हित पूर्णांक packets = ring_container->total_packets;
	अचिन्हित पूर्णांक bytes = ring_container->total_bytes;
	u8 itrval = ring_container->itr;

	/* no packets, निकास with status unchanged */
	अगर (packets == 0)
		वापस;

	चयन (itrval) अणु
	हाल lowest_latency:
		/* handle TSO and jumbo frames */
		अगर (bytes / packets > 8000)
			itrval = bulk_latency;
		अन्यथा अगर ((packets < 5) && (bytes > 512))
			itrval = low_latency;
		अवरोध;
	हाल low_latency:  /* 50 usec aka 20000 पूर्णांकs/s */
		अगर (bytes > 10000) अणु
			/* this अगर handles the TSO accounting */
			अगर (bytes / packets > 8000)
				itrval = bulk_latency;
			अन्यथा अगर ((packets < 10) || ((bytes / packets) > 1200))
				itrval = bulk_latency;
			अन्यथा अगर ((packets > 35))
				itrval = lowest_latency;
		पूर्ण अन्यथा अगर (bytes / packets > 2000) अणु
			itrval = bulk_latency;
		पूर्ण अन्यथा अगर (packets <= 2 && bytes < 512) अणु
			itrval = lowest_latency;
		पूर्ण
		अवरोध;
	हाल bulk_latency: /* 250 usec aka 4000 पूर्णांकs/s */
		अगर (bytes > 25000) अणु
			अगर (packets > 35)
				itrval = low_latency;
		पूर्ण अन्यथा अगर (bytes < 1500) अणु
			itrval = low_latency;
		पूर्ण
		अवरोध;
	पूर्ण

	/* clear work counters since we have the values we need */
	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;

	/* ग_लिखो updated itr to ring container */
	ring_container->itr = itrval;
पूर्ण

अटल व्योम igc_set_itr(काष्ठा igc_q_vector *q_vector)
अणु
	काष्ठा igc_adapter *adapter = q_vector->adapter;
	u32 new_itr = q_vector->itr_val;
	u8 current_itr = 0;

	/* क्रम non-gigabit speeds, just fix the पूर्णांकerrupt rate at 4000 */
	चयन (adapter->link_speed) अणु
	हाल SPEED_10:
	हाल SPEED_100:
		current_itr = 0;
		new_itr = IGC_4K_ITR;
		जाओ set_itr_now;
	शेष:
		अवरोध;
	पूर्ण

	igc_update_itr(q_vector, &q_vector->tx);
	igc_update_itr(q_vector, &q_vector->rx);

	current_itr = max(q_vector->rx.itr, q_vector->tx.itr);

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (current_itr == lowest_latency &&
	    ((q_vector->rx.ring && adapter->rx_itr_setting == 3) ||
	    (!q_vector->rx.ring && adapter->tx_itr_setting == 3)))
		current_itr = low_latency;

	चयन (current_itr) अणु
	/* counts and packets in update_itr are dependent on these numbers */
	हाल lowest_latency:
		new_itr = IGC_70K_ITR; /* 70,000 पूर्णांकs/sec */
		अवरोध;
	हाल low_latency:
		new_itr = IGC_20K_ITR; /* 20,000 पूर्णांकs/sec */
		अवरोध;
	हाल bulk_latency:
		new_itr = IGC_4K_ITR;  /* 4,000 पूर्णांकs/sec */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

set_itr_now:
	अगर (new_itr != q_vector->itr_val) अणु
		/* this attempts to bias the पूर्णांकerrupt rate towards Bulk
		 * by adding पूर्णांकermediate steps when पूर्णांकerrupt rate is
		 * increasing
		 */
		new_itr = new_itr > q_vector->itr_val ?
			  max((new_itr * q_vector->itr_val) /
			  (new_itr + (q_vector->itr_val >> 2)),
			  new_itr) : new_itr;
		/* Don't write the value here; it resets the adapter's
		 * पूर्णांकernal समयr, and causes us to delay far दीर्घer than
		 * we should between पूर्णांकerrupts.  Instead, we ग_लिखो the ITR
		 * value at the beginning of the next पूर्णांकerrupt so the timing
		 * ends up being correct.
		 */
		q_vector->itr_val = new_itr;
		q_vector->set_itr = 1;
	पूर्ण
पूर्ण

अटल व्योम igc_reset_पूर्णांकerrupt_capability(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक v_idx = adapter->num_q_vectors;

	अगर (adapter->msix_entries) अणु
		pci_disable_msix(adapter->pdev);
		kमुक्त(adapter->msix_entries);
		adapter->msix_entries = शून्य;
	पूर्ण अन्यथा अगर (adapter->flags & IGC_FLAG_HAS_MSI) अणु
		pci_disable_msi(adapter->pdev);
	पूर्ण

	जबतक (v_idx--)
		igc_reset_q_vector(adapter, v_idx);
पूर्ण

/**
 * igc_set_पूर्णांकerrupt_capability - set MSI or MSI-X अगर supported
 * @adapter: Poपूर्णांकer to adapter काष्ठाure
 * @msix: boolean value क्रम MSI-X capability
 *
 * Attempt to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 */
अटल व्योम igc_set_पूर्णांकerrupt_capability(काष्ठा igc_adapter *adapter,
					 bool msix)
अणु
	पूर्णांक numvecs, i;
	पूर्णांक err;

	अगर (!msix)
		जाओ msi_only;
	adapter->flags |= IGC_FLAG_HAS_MSIX;

	/* Number of supported queues. */
	adapter->num_rx_queues = adapter->rss_queues;

	adapter->num_tx_queues = adapter->rss_queues;

	/* start with one vector क्रम every Rx queue */
	numvecs = adapter->num_rx_queues;

	/* अगर Tx handler is separate add 1 क्रम every Tx queue */
	अगर (!(adapter->flags & IGC_FLAG_QUEUE_PAIRS))
		numvecs += adapter->num_tx_queues;

	/* store the number of vectors reserved क्रम queues */
	adapter->num_q_vectors = numvecs;

	/* add 1 vector क्रम link status पूर्णांकerrupts */
	numvecs++;

	adapter->msix_entries = kसुस्मृति(numvecs, माप(काष्ठा msix_entry),
					GFP_KERNEL);

	अगर (!adapter->msix_entries)
		वापस;

	/* populate entry values */
	क्रम (i = 0; i < numvecs; i++)
		adapter->msix_entries[i].entry = i;

	err = pci_enable_msix_range(adapter->pdev,
				    adapter->msix_entries,
				    numvecs,
				    numvecs);
	अगर (err > 0)
		वापस;

	kमुक्त(adapter->msix_entries);
	adapter->msix_entries = शून्य;

	igc_reset_पूर्णांकerrupt_capability(adapter);

msi_only:
	adapter->flags &= ~IGC_FLAG_HAS_MSIX;

	adapter->rss_queues = 1;
	adapter->flags |= IGC_FLAG_QUEUE_PAIRS;
	adapter->num_rx_queues = 1;
	adapter->num_tx_queues = 1;
	adapter->num_q_vectors = 1;
	अगर (!pci_enable_msi(adapter->pdev))
		adapter->flags |= IGC_FLAG_HAS_MSI;
पूर्ण

/**
 * igc_update_ring_itr - update the dynamic ITR value based on packet size
 * @q_vector: poपूर्णांकer to q_vector
 *
 * Stores a new ITR value based on strictly on packet size.  This
 * algorithm is less sophisticated than that used in igc_update_itr,
 * due to the dअगरficulty of synchronizing statistics across multiple
 * receive rings.  The भागisors and thresholds used by this function
 * were determined based on theoretical maximum wire speed and testing
 * data, in order to minimize response समय जबतक increasing bulk
 * throughput.
 * NOTE: This function is called only when operating in a multiqueue
 * receive environment.
 */
अटल व्योम igc_update_ring_itr(काष्ठा igc_q_vector *q_vector)
अणु
	काष्ठा igc_adapter *adapter = q_vector->adapter;
	पूर्णांक new_val = q_vector->itr_val;
	पूर्णांक avg_wire_size = 0;
	अचिन्हित पूर्णांक packets;

	/* For non-gigabit speeds, just fix the पूर्णांकerrupt rate at 4000
	 * पूर्णांकs/sec - ITR समयr value of 120 ticks.
	 */
	चयन (adapter->link_speed) अणु
	हाल SPEED_10:
	हाल SPEED_100:
		new_val = IGC_4K_ITR;
		जाओ set_itr_val;
	शेष:
		अवरोध;
	पूर्ण

	packets = q_vector->rx.total_packets;
	अगर (packets)
		avg_wire_size = q_vector->rx.total_bytes / packets;

	packets = q_vector->tx.total_packets;
	अगर (packets)
		avg_wire_size = max_t(u32, avg_wire_size,
				      q_vector->tx.total_bytes / packets);

	/* अगर avg_wire_size isn't set no work was करोne */
	अगर (!avg_wire_size)
		जाओ clear_counts;

	/* Add 24 bytes to size to account क्रम CRC, preamble, and gap */
	avg_wire_size += 24;

	/* Don't starve jumbo frames */
	avg_wire_size = min(avg_wire_size, 3000);

	/* Give a little boost to mid-size frames */
	अगर (avg_wire_size > 300 && avg_wire_size < 1200)
		new_val = avg_wire_size / 3;
	अन्यथा
		new_val = avg_wire_size / 2;

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (new_val < IGC_20K_ITR &&
	    ((q_vector->rx.ring && adapter->rx_itr_setting == 3) ||
	    (!q_vector->rx.ring && adapter->tx_itr_setting == 3)))
		new_val = IGC_20K_ITR;

set_itr_val:
	अगर (new_val != q_vector->itr_val) अणु
		q_vector->itr_val = new_val;
		q_vector->set_itr = 1;
	पूर्ण
clear_counts:
	q_vector->rx.total_bytes = 0;
	q_vector->rx.total_packets = 0;
	q_vector->tx.total_bytes = 0;
	q_vector->tx.total_packets = 0;
पूर्ण

अटल व्योम igc_ring_irq_enable(काष्ठा igc_q_vector *q_vector)
अणु
	काष्ठा igc_adapter *adapter = q_vector->adapter;
	काष्ठा igc_hw *hw = &adapter->hw;

	अगर ((q_vector->rx.ring && (adapter->rx_itr_setting & 3)) ||
	    (!q_vector->rx.ring && (adapter->tx_itr_setting & 3))) अणु
		अगर (adapter->num_q_vectors == 1)
			igc_set_itr(q_vector);
		अन्यथा
			igc_update_ring_itr(q_vector);
	पूर्ण

	अगर (!test_bit(__IGC_DOWN, &adapter->state)) अणु
		अगर (adapter->msix_entries)
			wr32(IGC_EIMS, q_vector->eims_value);
		अन्यथा
			igc_irq_enable(adapter);
	पूर्ण
पूर्ण

अटल व्योम igc_add_ring(काष्ठा igc_ring *ring,
			 काष्ठा igc_ring_container *head)
अणु
	head->ring = ring;
	head->count++;
पूर्ण

/**
 * igc_cache_ring_रेजिस्टर - Descriptor ring to रेजिस्टर mapping
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Once we know the feature-set enabled क्रम the device, we'll cache
 * the रेजिस्टर offset the descriptor ring is asचिन्हित to.
 */
अटल व्योम igc_cache_ring_रेजिस्टर(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i = 0, j = 0;

	चयन (adapter->hw.mac.type) अणु
	हाल igc_i225:
	शेष:
		क्रम (; i < adapter->num_rx_queues; i++)
			adapter->rx_ring[i]->reg_idx = i;
		क्रम (; j < adapter->num_tx_queues; j++)
			adapter->tx_ring[j]->reg_idx = j;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * igc_poll - NAPI Rx polling callback
 * @napi: napi polling काष्ठाure
 * @budget: count of how many packets we should handle
 */
अटल पूर्णांक igc_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा igc_q_vector *q_vector = container_of(napi,
						     काष्ठा igc_q_vector,
						     napi);
	bool clean_complete = true;
	पूर्णांक work_करोne = 0;

	अगर (q_vector->tx.ring)
		clean_complete = igc_clean_tx_irq(q_vector, budget);

	अगर (q_vector->rx.ring) अणु
		पूर्णांक cleaned = igc_clean_rx_irq(q_vector, budget);

		work_करोne += cleaned;
		अगर (cleaned >= budget)
			clean_complete = false;
	पूर्ण

	/* If all work not completed, वापस budget and keep polling */
	अगर (!clean_complete)
		वापस budget;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne)))
		igc_ring_irq_enable(q_vector);

	वापस min(work_करोne, budget - 1);
पूर्ण

/**
 * igc_alloc_q_vector - Allocate memory क्रम a single पूर्णांकerrupt vector
 * @adapter: board निजी काष्ठाure to initialize
 * @v_count: q_vectors allocated on adapter, used क्रम ring पूर्णांकerleaving
 * @v_idx: index of vector in adapter काष्ठा
 * @txr_count: total number of Tx rings to allocate
 * @txr_idx: index of first Tx ring to allocate
 * @rxr_count: total number of Rx rings to allocate
 * @rxr_idx: index of first Rx ring to allocate
 *
 * We allocate one q_vector.  If allocation fails we वापस -ENOMEM.
 */
अटल पूर्णांक igc_alloc_q_vector(काष्ठा igc_adapter *adapter,
			      अचिन्हित पूर्णांक v_count, अचिन्हित पूर्णांक v_idx,
			      अचिन्हित पूर्णांक txr_count, अचिन्हित पूर्णांक txr_idx,
			      अचिन्हित पूर्णांक rxr_count, अचिन्हित पूर्णांक rxr_idx)
अणु
	काष्ठा igc_q_vector *q_vector;
	काष्ठा igc_ring *ring;
	पूर्णांक ring_count;

	/* igc only supports 1 Tx and/or 1 Rx queue per vector */
	अगर (txr_count > 1 || rxr_count > 1)
		वापस -ENOMEM;

	ring_count = txr_count + rxr_count;

	/* allocate q_vector and rings */
	q_vector = adapter->q_vector[v_idx];
	अगर (!q_vector)
		q_vector = kzalloc(काष्ठा_size(q_vector, ring, ring_count),
				   GFP_KERNEL);
	अन्यथा
		स_रखो(q_vector, 0, काष्ठा_size(q_vector, ring, ring_count));
	अगर (!q_vector)
		वापस -ENOMEM;

	/* initialize NAPI */
	netअगर_napi_add(adapter->netdev, &q_vector->napi,
		       igc_poll, 64);

	/* tie q_vector and adapter together */
	adapter->q_vector[v_idx] = q_vector;
	q_vector->adapter = adapter;

	/* initialize work limits */
	q_vector->tx.work_limit = adapter->tx_work_limit;

	/* initialize ITR configuration */
	q_vector->itr_रेजिस्टर = adapter->io_addr + IGC_EITR(0);
	q_vector->itr_val = IGC_START_ITR;

	/* initialize poपूर्णांकer to rings */
	ring = q_vector->ring;

	/* initialize ITR */
	अगर (rxr_count) अणु
		/* rx or rx/tx vector */
		अगर (!adapter->rx_itr_setting || adapter->rx_itr_setting > 3)
			q_vector->itr_val = adapter->rx_itr_setting;
	पूर्ण अन्यथा अणु
		/* tx only vector */
		अगर (!adapter->tx_itr_setting || adapter->tx_itr_setting > 3)
			q_vector->itr_val = adapter->tx_itr_setting;
	पूर्ण

	अगर (txr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		igc_add_ring(ring, &q_vector->tx);

		/* apply Tx specअगरic ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = txr_idx;

		/* assign ring to adapter */
		adapter->tx_ring[txr_idx] = ring;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	अगर (rxr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Rx values */
		igc_add_ring(ring, &q_vector->rx);

		/* apply Rx specअगरic ring traits */
		ring->count = adapter->rx_ring_count;
		ring->queue_index = rxr_idx;

		/* assign ring to adapter */
		adapter->rx_ring[rxr_idx] = ring;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * igc_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * We allocate one q_vector per queue पूर्णांकerrupt.  If allocation fails we
 * वापस -ENOMEM.
 */
अटल पूर्णांक igc_alloc_q_vectors(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक rxr_reमुख्यing = adapter->num_rx_queues;
	पूर्णांक txr_reमुख्यing = adapter->num_tx_queues;
	पूर्णांक rxr_idx = 0, txr_idx = 0, v_idx = 0;
	पूर्णांक q_vectors = adapter->num_q_vectors;
	पूर्णांक err;

	अगर (q_vectors >= (rxr_reमुख्यing + txr_reमुख्यing)) अणु
		क्रम (; rxr_reमुख्यing; v_idx++) अणु
			err = igc_alloc_q_vector(adapter, q_vectors, v_idx,
						 0, 0, 1, rxr_idx);

			अगर (err)
				जाओ err_out;

			/* update counts and index */
			rxr_reमुख्यing--;
			rxr_idx++;
		पूर्ण
	पूर्ण

	क्रम (; v_idx < q_vectors; v_idx++) अणु
		पूर्णांक rqpv = DIV_ROUND_UP(rxr_reमुख्यing, q_vectors - v_idx);
		पूर्णांक tqpv = DIV_ROUND_UP(txr_reमुख्यing, q_vectors - v_idx);

		err = igc_alloc_q_vector(adapter, q_vectors, v_idx,
					 tqpv, txr_idx, rqpv, rxr_idx);

		अगर (err)
			जाओ err_out;

		/* update counts and index */
		rxr_reमुख्यing -= rqpv;
		txr_reमुख्यing -= tqpv;
		rxr_idx++;
		txr_idx++;
	पूर्ण

	वापस 0;

err_out:
	adapter->num_tx_queues = 0;
	adapter->num_rx_queues = 0;
	adapter->num_q_vectors = 0;

	जबतक (v_idx--)
		igc_मुक्त_q_vector(adapter, v_idx);

	वापस -ENOMEM;
पूर्ण

/**
 * igc_init_पूर्णांकerrupt_scheme - initialize पूर्णांकerrupts, allocate queues/vectors
 * @adapter: Poपूर्णांकer to adapter काष्ठाure
 * @msix: boolean क्रम MSI-X capability
 *
 * This function initializes the पूर्णांकerrupts and allocates all of the queues.
 */
अटल पूर्णांक igc_init_पूर्णांकerrupt_scheme(काष्ठा igc_adapter *adapter, bool msix)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक err = 0;

	igc_set_पूर्णांकerrupt_capability(adapter, msix);

	err = igc_alloc_q_vectors(adapter);
	अगर (err) अणु
		netdev_err(dev, "Unable to allocate memory for vectors\n");
		जाओ err_alloc_q_vectors;
	पूर्ण

	igc_cache_ring_रेजिस्टर(adapter);

	वापस 0;

err_alloc_q_vectors:
	igc_reset_पूर्णांकerrupt_capability(adapter);
	वापस err;
पूर्ण

/**
 * igc_sw_init - Initialize general software काष्ठाures (काष्ठा igc_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * igc_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 */
अटल पूर्णांक igc_sw_init(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा igc_hw *hw = &adapter->hw;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &hw->bus.pci_cmd_word);

	/* set शेष ring sizes */
	adapter->tx_ring_count = IGC_DEFAULT_TXD;
	adapter->rx_ring_count = IGC_DEFAULT_RXD;

	/* set शेष ITR values */
	adapter->rx_itr_setting = IGC_DEFAULT_ITR;
	adapter->tx_itr_setting = IGC_DEFAULT_ITR;

	/* set शेष work limits */
	adapter->tx_work_limit = IGC_DEFAULT_TX_WORK;

	/* adjust max frame to be at least the size of a standard frame */
	adapter->max_frame_size = netdev->mtu + ETH_HLEN + ETH_FCS_LEN +
				VLAN_HLEN;
	adapter->min_frame_size = ETH_ZLEN + ETH_FCS_LEN;

	mutex_init(&adapter->nfc_rule_lock);
	INIT_LIST_HEAD(&adapter->nfc_rule_list);
	adapter->nfc_rule_count = 0;

	spin_lock_init(&adapter->stats64_lock);
	/* Assume MSI-X पूर्णांकerrupts, will be checked during IRQ allocation */
	adapter->flags |= IGC_FLAG_HAS_MSIX;

	igc_init_queue_configuration(adapter);

	/* This call may decrease the number of queues */
	अगर (igc_init_पूर्णांकerrupt_scheme(adapter, true)) अणु
		netdev_err(netdev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	/* Explicitly disable IRQ since the NIC can be in any state. */
	igc_irq_disable(adapter);

	set_bit(__IGC_DOWN, &adapter->state);

	वापस 0;
पूर्ण

/**
 * igc_up - Open the पूर्णांकerface and prepare it to handle traffic
 * @adapter: board निजी काष्ठाure
 */
व्योम igc_up(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक i = 0;

	/* hardware has been reset, we need to reload some things */
	igc_configure(adapter);

	clear_bit(__IGC_DOWN, &adapter->state);

	क्रम (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&adapter->q_vector[i]->napi);

	अगर (adapter->msix_entries)
		igc_configure_msix(adapter);
	अन्यथा
		igc_assign_vector(adapter->q_vector[0], 0);

	/* Clear any pending पूर्णांकerrupts. */
	rd32(IGC_ICR);
	igc_irq_enable(adapter);

	netअगर_tx_start_all_queues(adapter->netdev);

	/* start the watchकरोg. */
	hw->mac.get_link_status = true;
	schedule_work(&adapter->watchकरोg_task);
पूर्ण

/**
 * igc_update_stats - Update the board statistics counters
 * @adapter: board निजी काष्ठाure
 */
व्योम igc_update_stats(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा rtnl_link_stats64 *net_stats = &adapter->stats64;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	u64 _bytes, _packets;
	u64 bytes, packets;
	अचिन्हित पूर्णांक start;
	u32 mpc;
	पूर्णांक i;

	/* Prevent stats update जबतक adapter is being reset, or अगर the pci
	 * connection is करोwn.
	 */
	अगर (adapter->link_speed == 0)
		वापस;
	अगर (pci_channel_offline(pdev))
		वापस;

	packets = 0;
	bytes = 0;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा igc_ring *ring = adapter->rx_ring[i];
		u32 rqdpc = rd32(IGC_RQDPC(i));

		अगर (hw->mac.type >= igc_i225)
			wr32(IGC_RQDPC(i), 0);

		अगर (rqdpc) अणु
			ring->rx_stats.drops += rqdpc;
			net_stats->rx_fअगरo_errors += rqdpc;
		पूर्ण

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->rx_syncp);
			_bytes = ring->rx_stats.bytes;
			_packets = ring->rx_stats.packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->rx_syncp, start));
		bytes += _bytes;
		packets += _packets;
	पूर्ण

	net_stats->rx_bytes = bytes;
	net_stats->rx_packets = packets;

	packets = 0;
	bytes = 0;
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा igc_ring *ring = adapter->tx_ring[i];

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp);
			_bytes = ring->tx_stats.bytes;
			_packets = ring->tx_stats.packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->tx_syncp, start));
		bytes += _bytes;
		packets += _packets;
	पूर्ण
	net_stats->tx_bytes = bytes;
	net_stats->tx_packets = packets;
	rcu_पढ़ो_unlock();

	/* पढ़ो stats रेजिस्टरs */
	adapter->stats.crcerrs += rd32(IGC_CRCERRS);
	adapter->stats.gprc += rd32(IGC_GPRC);
	adapter->stats.gorc += rd32(IGC_GORCL);
	rd32(IGC_GORCH); /* clear GORCL */
	adapter->stats.bprc += rd32(IGC_BPRC);
	adapter->stats.mprc += rd32(IGC_MPRC);
	adapter->stats.roc += rd32(IGC_ROC);

	adapter->stats.prc64 += rd32(IGC_PRC64);
	adapter->stats.prc127 += rd32(IGC_PRC127);
	adapter->stats.prc255 += rd32(IGC_PRC255);
	adapter->stats.prc511 += rd32(IGC_PRC511);
	adapter->stats.prc1023 += rd32(IGC_PRC1023);
	adapter->stats.prc1522 += rd32(IGC_PRC1522);
	adapter->stats.tlpic += rd32(IGC_TLPIC);
	adapter->stats.rlpic += rd32(IGC_RLPIC);
	adapter->stats.hgptc += rd32(IGC_HGPTC);

	mpc = rd32(IGC_MPC);
	adapter->stats.mpc += mpc;
	net_stats->rx_fअगरo_errors += mpc;
	adapter->stats.scc += rd32(IGC_SCC);
	adapter->stats.ecol += rd32(IGC_ECOL);
	adapter->stats.mcc += rd32(IGC_MCC);
	adapter->stats.latecol += rd32(IGC_LATECOL);
	adapter->stats.dc += rd32(IGC_DC);
	adapter->stats.rlec += rd32(IGC_RLEC);
	adapter->stats.xonrxc += rd32(IGC_XONRXC);
	adapter->stats.xontxc += rd32(IGC_XONTXC);
	adapter->stats.xoffrxc += rd32(IGC_XOFFRXC);
	adapter->stats.xofftxc += rd32(IGC_XOFFTXC);
	adapter->stats.fcruc += rd32(IGC_FCRUC);
	adapter->stats.gptc += rd32(IGC_GPTC);
	adapter->stats.gotc += rd32(IGC_GOTCL);
	rd32(IGC_GOTCH); /* clear GOTCL */
	adapter->stats.rnbc += rd32(IGC_RNBC);
	adapter->stats.ruc += rd32(IGC_RUC);
	adapter->stats.rfc += rd32(IGC_RFC);
	adapter->stats.rjc += rd32(IGC_RJC);
	adapter->stats.tor += rd32(IGC_TORH);
	adapter->stats.tot += rd32(IGC_TOTH);
	adapter->stats.tpr += rd32(IGC_TPR);

	adapter->stats.ptc64 += rd32(IGC_PTC64);
	adapter->stats.ptc127 += rd32(IGC_PTC127);
	adapter->stats.ptc255 += rd32(IGC_PTC255);
	adapter->stats.ptc511 += rd32(IGC_PTC511);
	adapter->stats.ptc1023 += rd32(IGC_PTC1023);
	adapter->stats.ptc1522 += rd32(IGC_PTC1522);

	adapter->stats.mptc += rd32(IGC_MPTC);
	adapter->stats.bptc += rd32(IGC_BPTC);

	adapter->stats.tpt += rd32(IGC_TPT);
	adapter->stats.colc += rd32(IGC_COLC);
	adapter->stats.colc += rd32(IGC_RERC);

	adapter->stats.algnerrc += rd32(IGC_ALGNERRC);

	adapter->stats.tsctc += rd32(IGC_TSCTC);

	adapter->stats.iac += rd32(IGC_IAC);

	/* Fill out the OS statistics काष्ठाure */
	net_stats->multicast = adapter->stats.mprc;
	net_stats->collisions = adapter->stats.colc;

	/* Rx Errors */

	/* RLEC on some newer hardware can be incorrect so build
	 * our own version based on RUC and ROC
	 */
	net_stats->rx_errors = adapter->stats.rxerrc +
		adapter->stats.crcerrs + adapter->stats.algnerrc +
		adapter->stats.ruc + adapter->stats.roc +
		adapter->stats.cexterr;
	net_stats->rx_length_errors = adapter->stats.ruc +
				      adapter->stats.roc;
	net_stats->rx_crc_errors = adapter->stats.crcerrs;
	net_stats->rx_frame_errors = adapter->stats.algnerrc;
	net_stats->rx_missed_errors = adapter->stats.mpc;

	/* Tx Errors */
	net_stats->tx_errors = adapter->stats.ecol +
			       adapter->stats.latecol;
	net_stats->tx_पातed_errors = adapter->stats.ecol;
	net_stats->tx_winकरोw_errors = adapter->stats.latecol;
	net_stats->tx_carrier_errors = adapter->stats.tncrs;

	/* Tx Dropped needs to be मुख्यtained अन्यथाwhere */

	/* Management Stats */
	adapter->stats.mgptc += rd32(IGC_MGTPTC);
	adapter->stats.mgprc += rd32(IGC_MGTPRC);
	adapter->stats.mgpdc += rd32(IGC_MGTPDC);
पूर्ण

/**
 * igc_करोwn - Close the पूर्णांकerface
 * @adapter: board निजी काष्ठाure
 */
व्योम igc_करोwn(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 tctl, rctl;
	पूर्णांक i = 0;

	set_bit(__IGC_DOWN, &adapter->state);

	igc_ptp_suspend(adapter);

	/* disable receives in the hardware */
	rctl = rd32(IGC_RCTL);
	wr32(IGC_RCTL, rctl & ~IGC_RCTL_EN);
	/* flush and sleep below */

	/* set trans_start so we करोn't get spurious watchकरोgs during reset */
	netअगर_trans_update(netdev);

	netअगर_carrier_off(netdev);
	netअगर_tx_stop_all_queues(netdev);

	/* disable transmits in the hardware */
	tctl = rd32(IGC_TCTL);
	tctl &= ~IGC_TCTL_EN;
	wr32(IGC_TCTL, tctl);
	/* flush both disables and रुको क्रम them to finish */
	wrfl();
	usleep_range(10000, 20000);

	igc_irq_disable(adapter);

	adapter->flags &= ~IGC_FLAG_NEED_LINK_UPDATE;

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		अगर (adapter->q_vector[i]) अणु
			napi_synchronize(&adapter->q_vector[i]->napi);
			napi_disable(&adapter->q_vector[i]->napi);
		पूर्ण
	पूर्ण

	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_info_समयr);

	/* record the stats beक्रमe reset*/
	spin_lock(&adapter->stats64_lock);
	igc_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	अगर (!pci_channel_offline(adapter->pdev))
		igc_reset(adapter);

	/* clear VLAN promisc flag so VFTA will be updated अगर necessary */
	adapter->flags &= ~IGC_FLAG_VLAN_PROMISC;

	igc_clean_all_tx_rings(adapter);
	igc_clean_all_rx_rings(adapter);
पूर्ण

व्योम igc_reinit_locked(काष्ठा igc_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__IGC_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	igc_करोwn(adapter);
	igc_up(adapter);
	clear_bit(__IGC_RESETTING, &adapter->state);
पूर्ण

अटल व्योम igc_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igc_adapter *adapter;

	adapter = container_of(work, काष्ठा igc_adapter, reset_task);

	rtnl_lock();
	/* If we're alपढ़ोy करोwn or resetting, just bail */
	अगर (test_bit(__IGC_DOWN, &adapter->state) ||
	    test_bit(__IGC_RESETTING, &adapter->state)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	igc_rings_dump(adapter);
	igc_regs_dump(adapter);
	netdev_err(adapter->netdev, "Reset adapter\n");
	igc_reinit_locked(adapter);
	rtnl_unlock();
पूर्ण

/**
 * igc_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक igc_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	पूर्णांक max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	अगर (igc_xdp_is_enabled(adapter) && new_mtu > ETH_DATA_LEN) अणु
		netdev_dbg(netdev, "Jumbo frames not supported with XDP");
		वापस -EINVAL;
	पूर्ण

	/* adjust max frame to be at least the size of a standard frame */
	अगर (max_frame < (ETH_FRAME_LEN + ETH_FCS_LEN))
		max_frame = ETH_FRAME_LEN + ETH_FCS_LEN;

	जबतक (test_and_set_bit(__IGC_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	/* igc_करोwn has a dependency on max_frame_size */
	adapter->max_frame_size = max_frame;

	अगर (netअगर_running(netdev))
		igc_करोwn(adapter);

	netdev_dbg(netdev, "changing MTU from %d to %d\n", netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		igc_up(adapter);
	अन्यथा
		igc_reset(adapter);

	clear_bit(__IGC_RESETTING, &adapter->state);

	वापस 0;
पूर्ण

/**
 * igc_get_stats64 - Get System Network Statistics
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @stats: rtnl_link_stats64 poपूर्णांकer
 *
 * Returns the address of the device statistics काष्ठाure.
 * The statistics are updated here and also from the समयr callback.
 */
अटल व्योम igc_get_stats64(काष्ठा net_device *netdev,
			    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	spin_lock(&adapter->stats64_lock);
	अगर (!test_bit(__IGC_RESETTING, &adapter->state))
		igc_update_stats(adapter);
	स_नकल(stats, &adapter->stats64, माप(*stats));
	spin_unlock(&adapter->stats64_lock);
पूर्ण

अटल netdev_features_t igc_fix_features(काष्ठा net_device *netdev,
					  netdev_features_t features)
अणु
	/* Since there is no support क्रम separate Rx/Tx vlan accel
	 * enable/disable make sure Tx flag is always in same state as Rx.
	 */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	अन्यथा
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	वापस features;
पूर्ण

अटल पूर्णांक igc_set_features(काष्ठा net_device *netdev,
			    netdev_features_t features)
अणु
	netdev_features_t changed = netdev->features ^ features;
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	/* Add VLAN support */
	अगर (!(changed & (NETIF_F_RXALL | NETIF_F_NTUPLE)))
		वापस 0;

	अगर (!(features & NETIF_F_NTUPLE))
		igc_flush_nfc_rules(adapter);

	netdev->features = features;

	अगर (netअगर_running(netdev))
		igc_reinit_locked(adapter);
	अन्यथा
		igc_reset(adapter);

	वापस 1;
पूर्ण

अटल netdev_features_t
igc_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		   netdev_features_t features)
अणु
	अचिन्हित पूर्णांक network_hdr_len, mac_hdr_len;

	/* Make certain the headers can be described by a context descriptor */
	mac_hdr_len = skb_network_header(skb) - skb->data;
	अगर (unlikely(mac_hdr_len > IGC_MAX_MAC_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	network_hdr_len = skb_checksum_start(skb) - skb_network_header(skb);
	अगर (unlikely(network_hdr_len >  IGC_MAX_NETWORK_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	/* We can only support IPv4 TSO in tunnels अगर we can mangle the
	 * inner IP ID field, so strip TSO अगर MANGLEID is not supported.
	 */
	अगर (skb->encapsulation && !(features & NETIF_F_TSO_MANGLEID))
		features &= ~NETIF_F_TSO;

	वापस features;
पूर्ण

अटल व्योम igc_tsync_पूर्णांकerrupt(काष्ठा igc_adapter *adapter)
अणु
	u32 ack, tsauxc, sec, nsec, tsicr;
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा ptp_घड़ी_event event;
	काष्ठा बारpec64 ts;

	tsicr = rd32(IGC_TSICR);
	ack = 0;

	अगर (tsicr & IGC_TSICR_SYS_WRAP) अणु
		event.type = PTP_CLOCK_PPS;
		अगर (adapter->ptp_caps.pps)
			ptp_घड़ी_event(adapter->ptp_घड़ी, &event);
		ack |= IGC_TSICR_SYS_WRAP;
	पूर्ण

	अगर (tsicr & IGC_TSICR_TXTS) अणु
		/* retrieve hardware बारtamp */
		schedule_work(&adapter->ptp_tx_work);
		ack |= IGC_TSICR_TXTS;
	पूर्ण

	अगर (tsicr & IGC_TSICR_TT0) अणु
		spin_lock(&adapter->पंचांगreg_lock);
		ts = बारpec64_add(adapter->perout[0].start,
				    adapter->perout[0].period);
		wr32(IGC_TRGTTIML0, ts.tv_nsec | IGC_TT_IO_TIMER_SEL_SYSTIM0);
		wr32(IGC_TRGTTIMH0, (u32)ts.tv_sec);
		tsauxc = rd32(IGC_TSAUXC);
		tsauxc |= IGC_TSAUXC_EN_TT0;
		wr32(IGC_TSAUXC, tsauxc);
		adapter->perout[0].start = ts;
		spin_unlock(&adapter->पंचांगreg_lock);
		ack |= IGC_TSICR_TT0;
	पूर्ण

	अगर (tsicr & IGC_TSICR_TT1) अणु
		spin_lock(&adapter->पंचांगreg_lock);
		ts = बारpec64_add(adapter->perout[1].start,
				    adapter->perout[1].period);
		wr32(IGC_TRGTTIML1, ts.tv_nsec | IGC_TT_IO_TIMER_SEL_SYSTIM0);
		wr32(IGC_TRGTTIMH1, (u32)ts.tv_sec);
		tsauxc = rd32(IGC_TSAUXC);
		tsauxc |= IGC_TSAUXC_EN_TT1;
		wr32(IGC_TSAUXC, tsauxc);
		adapter->perout[1].start = ts;
		spin_unlock(&adapter->पंचांगreg_lock);
		ack |= IGC_TSICR_TT1;
	पूर्ण

	अगर (tsicr & IGC_TSICR_AUTT0) अणु
		nsec = rd32(IGC_AUXSTMPL0);
		sec  = rd32(IGC_AUXSTMPH0);
		event.type = PTP_CLOCK_EXTTS;
		event.index = 0;
		event.बारtamp = sec * NSEC_PER_SEC + nsec;
		ptp_घड़ी_event(adapter->ptp_घड़ी, &event);
		ack |= IGC_TSICR_AUTT0;
	पूर्ण

	अगर (tsicr & IGC_TSICR_AUTT1) अणु
		nsec = rd32(IGC_AUXSTMPL1);
		sec  = rd32(IGC_AUXSTMPH1);
		event.type = PTP_CLOCK_EXTTS;
		event.index = 1;
		event.बारtamp = sec * NSEC_PER_SEC + nsec;
		ptp_घड़ी_event(adapter->ptp_घड़ी, &event);
		ack |= IGC_TSICR_AUTT1;
	पूर्ण

	/* acknowledge the पूर्णांकerrupts */
	wr32(IGC_TSICR, ack);
पूर्ण

/**
 * igc_msix_other - msix other पूर्णांकerrupt handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a q_vector
 */
अटल irqवापस_t igc_msix_other(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igc_adapter *adapter = data;
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 icr = rd32(IGC_ICR);

	/* पढ़ोing ICR causes bit 31 of EICR to be cleared */
	अगर (icr & IGC_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	अगर (icr & IGC_ICR_DOUTSYNC) अणु
		/* HW is reporting DMA is out of sync */
		adapter->stats.करोosync++;
	पूर्ण

	अगर (icr & IGC_ICR_LSC) अणु
		hw->mac.get_link_status = true;
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__IGC_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	अगर (icr & IGC_ICR_TS)
		igc_tsync_पूर्णांकerrupt(adapter);

	wr32(IGC_EIMS, adapter->eims_other);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम igc_ग_लिखो_itr(काष्ठा igc_q_vector *q_vector)
अणु
	u32 itr_val = q_vector->itr_val & IGC_QVECTOR_MASK;

	अगर (!q_vector->set_itr)
		वापस;

	अगर (!itr_val)
		itr_val = IGC_ITR_VAL_MASK;

	itr_val |= IGC_EITR_CNT_IGNR;

	ग_लिखोl(itr_val, q_vector->itr_रेजिस्टर);
	q_vector->set_itr = 0;
पूर्ण

अटल irqवापस_t igc_msix_ring(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igc_q_vector *q_vector = data;

	/* Write the ITR value calculated from the previous पूर्णांकerrupt. */
	igc_ग_लिखो_itr(q_vector);

	napi_schedule(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * igc_request_msix - Initialize MSI-X पूर्णांकerrupts
 * @adapter: Poपूर्णांकer to adapter काष्ठाure
 *
 * igc_request_msix allocates MSI-X vectors and requests पूर्णांकerrupts from the
 * kernel.
 */
अटल पूर्णांक igc_request_msix(काष्ठा igc_adapter *adapter)
अणु
	पूर्णांक i = 0, err = 0, vector = 0, मुक्त_vector = 0;
	काष्ठा net_device *netdev = adapter->netdev;

	err = request_irq(adapter->msix_entries[vector].vector,
			  &igc_msix_other, 0, netdev->name, adapter);
	अगर (err)
		जाओ err_out;

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		काष्ठा igc_q_vector *q_vector = adapter->q_vector[i];

		vector++;

		q_vector->itr_रेजिस्टर = adapter->io_addr + IGC_EITR(vector);

		अगर (q_vector->rx.ring && q_vector->tx.ring)
			प्र_लिखो(q_vector->name, "%s-TxRx-%u", netdev->name,
				q_vector->rx.ring->queue_index);
		अन्यथा अगर (q_vector->tx.ring)
			प्र_लिखो(q_vector->name, "%s-tx-%u", netdev->name,
				q_vector->tx.ring->queue_index);
		अन्यथा अगर (q_vector->rx.ring)
			प्र_लिखो(q_vector->name, "%s-rx-%u", netdev->name,
				q_vector->rx.ring->queue_index);
		अन्यथा
			प्र_लिखो(q_vector->name, "%s-unused", netdev->name);

		err = request_irq(adapter->msix_entries[vector].vector,
				  igc_msix_ring, 0, q_vector->name,
				  q_vector);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण

	igc_configure_msix(adapter);
	वापस 0;

err_मुक्त:
	/* मुक्त alपढ़ोy asचिन्हित IRQs */
	मुक्त_irq(adapter->msix_entries[मुक्त_vector++].vector, adapter);

	vector--;
	क्रम (i = 0; i < vector; i++) अणु
		मुक्त_irq(adapter->msix_entries[मुक्त_vector++].vector,
			 adapter->q_vector[i]);
	पूर्ण
err_out:
	वापस err;
पूर्ण

/**
 * igc_clear_पूर्णांकerrupt_scheme - reset the device to a state of no पूर्णांकerrupts
 * @adapter: Poपूर्णांकer to adapter काष्ठाure
 *
 * This function resets the device so that it has 0 rx queues, tx queues, and
 * MSI-X पूर्णांकerrupts allocated.
 */
अटल व्योम igc_clear_पूर्णांकerrupt_scheme(काष्ठा igc_adapter *adapter)
अणु
	igc_मुक्त_q_vectors(adapter);
	igc_reset_पूर्णांकerrupt_capability(adapter);
पूर्ण

/* Need to रुको a few seconds after link up to get diagnostic inक्रमmation from
 * the phy
 */
अटल व्योम igc_update_phy_info(काष्ठा समयr_list *t)
अणु
	काष्ठा igc_adapter *adapter = from_समयr(adapter, t, phy_info_समयr);

	igc_get_phy_info(&adapter->hw);
पूर्ण

/**
 * igc_has_link - check shared code क्रम link and determine up/करोwn
 * @adapter: poपूर्णांकer to driver निजी info
 */
bool igc_has_link(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	bool link_active = false;

	/* get_link_status is set on LSC (link status) पूर्णांकerrupt or
	 * rx sequence error पूर्णांकerrupt.  get_link_status will stay
	 * false until the igc_check_क्रम_link establishes link
	 * क्रम copper adapters ONLY
	 */
	चयन (hw->phy.media_type) अणु
	हाल igc_media_type_copper:
		अगर (!hw->mac.get_link_status)
			वापस true;
		hw->mac.ops.check_क्रम_link(hw);
		link_active = !hw->mac.get_link_status;
		अवरोध;
	शेष:
	हाल igc_media_type_unknown:
		अवरोध;
	पूर्ण

	अगर (hw->mac.type == igc_i225 &&
	    hw->phy.id == I225_I_PHY_ID) अणु
		अगर (!netअगर_carrier_ok(adapter->netdev)) अणु
			adapter->flags &= ~IGC_FLAG_NEED_LINK_UPDATE;
		पूर्ण अन्यथा अगर (!(adapter->flags & IGC_FLAG_NEED_LINK_UPDATE)) अणु
			adapter->flags |= IGC_FLAG_NEED_LINK_UPDATE;
			adapter->link_check_समयout = jअगरfies;
		पूर्ण
	पूर्ण

	वापस link_active;
पूर्ण

/**
 * igc_watchकरोg - Timer Call-back
 * @t: समयr क्रम the watchकरोg
 */
अटल व्योम igc_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा igc_adapter *adapter = from_समयr(adapter, t, watchकरोg_समयr);
	/* Do the rest outside of पूर्णांकerrupt context */
	schedule_work(&adapter->watchकरोg_task);
पूर्ण

अटल व्योम igc_watchकरोg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igc_adapter *adapter = container_of(work,
						   काष्ठा igc_adapter,
						   watchकरोg_task);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा igc_phy_info *phy = &hw->phy;
	u16 phy_data, retry_count = 20;
	u32 link;
	पूर्णांक i;

	link = igc_has_link(adapter);

	अगर (adapter->flags & IGC_FLAG_NEED_LINK_UPDATE) अणु
		अगर (समय_after(jअगरfies, (adapter->link_check_समयout + HZ)))
			adapter->flags &= ~IGC_FLAG_NEED_LINK_UPDATE;
		अन्यथा
			link = false;
	पूर्ण

	अगर (link) अणु
		/* Cancel scheduled suspend requests. */
		pm_runसमय_resume(netdev->dev.parent);

		अगर (!netअगर_carrier_ok(netdev)) अणु
			u32 ctrl;

			hw->mac.ops.get_speed_and_duplex(hw,
							 &adapter->link_speed,
							 &adapter->link_duplex);

			ctrl = rd32(IGC_CTRL);
			/* Link status message must follow this क्रमmat */
			netdev_info(netdev,
				    "NIC Link is Up %d Mbps %s Duplex, Flow Control: %s\n",
				    adapter->link_speed,
				    adapter->link_duplex == FULL_DUPLEX ?
				    "Full" : "Half",
				    (ctrl & IGC_CTRL_TFCE) &&
				    (ctrl & IGC_CTRL_RFCE) ? "RX/TX" :
				    (ctrl & IGC_CTRL_RFCE) ?  "RX" :
				    (ctrl & IGC_CTRL_TFCE) ?  "TX" : "None");

			/* disable EEE अगर enabled */
			अगर ((adapter->flags & IGC_FLAG_EEE) &&
			    adapter->link_duplex == HALF_DUPLEX) अणु
				netdev_info(netdev,
					    "EEE Disabled: unsupported at half duplex. Re-enable using ethtool when at full duplex\n");
				adapter->hw.dev_spec._base.eee_enable = false;
				adapter->flags &= ~IGC_FLAG_EEE;
			पूर्ण

			/* check अगर SmartSpeed worked */
			igc_check_करोwnshअगरt(hw);
			अगर (phy->speed_करोwngraded)
				netdev_warn(netdev, "Link Speed was downgraded by SmartSpeed\n");

			/* adjust समयout factor according to speed/duplex */
			adapter->tx_समयout_factor = 1;
			चयन (adapter->link_speed) अणु
			हाल SPEED_10:
				adapter->tx_समयout_factor = 14;
				अवरोध;
			हाल SPEED_100:
				/* maybe add some समयout factor ? */
				अवरोध;
			पूर्ण

			अगर (adapter->link_speed != SPEED_1000)
				जाओ no_रुको;

			/* रुको क्रम Remote receiver status OK */
retry_पढ़ो_status:
			अगर (!igc_पढ़ो_phy_reg(hw, PHY_1000T_STATUS,
					      &phy_data)) अणु
				अगर (!(phy_data & SR_1000T_REMOTE_RX_STATUS) &&
				    retry_count) अणु
					msleep(100);
					retry_count--;
					जाओ retry_पढ़ो_status;
				पूर्ण अन्यथा अगर (!retry_count) अणु
					netdev_err(netdev, "exceed max 2 second\n");
				पूर्ण
			पूर्ण अन्यथा अणु
				netdev_err(netdev, "read 1000Base-T Status Reg\n");
			पूर्ण
no_रुको:
			netअगर_carrier_on(netdev);

			/* link state has changed, schedule phy info update */
			अगर (!test_bit(__IGC_DOWN, &adapter->state))
				mod_समयr(&adapter->phy_info_समयr,
					  round_jअगरfies(jअगरfies + 2 * HZ));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			adapter->link_speed = 0;
			adapter->link_duplex = 0;

			/* Links status message must follow this क्रमmat */
			netdev_info(netdev, "NIC Link is Down\n");
			netअगर_carrier_off(netdev);

			/* link state has changed, schedule phy info update */
			अगर (!test_bit(__IGC_DOWN, &adapter->state))
				mod_समयr(&adapter->phy_info_समयr,
					  round_jअगरfies(jअगरfies + 2 * HZ));

			/* link is करोwn, समय to check क्रम alternate media */
			अगर (adapter->flags & IGC_FLAG_MAS_ENABLE) अणु
				अगर (adapter->flags & IGC_FLAG_MEDIA_RESET) अणु
					schedule_work(&adapter->reset_task);
					/* वापस immediately */
					वापस;
				पूर्ण
			पूर्ण
			pm_schedule_suspend(netdev->dev.parent,
					    MSEC_PER_SEC * 5);

		/* also check क्रम alternate media here */
		पूर्ण अन्यथा अगर (!netअगर_carrier_ok(netdev) &&
			   (adapter->flags & IGC_FLAG_MAS_ENABLE)) अणु
			अगर (adapter->flags & IGC_FLAG_MEDIA_RESET) अणु
				schedule_work(&adapter->reset_task);
				/* वापस immediately */
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock(&adapter->stats64_lock);
	igc_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा igc_ring *tx_ring = adapter->tx_ring[i];

		अगर (!netअगर_carrier_ok(netdev)) अणु
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get करोne, so reset controller to flush Tx.
			 * (Do the reset outside of पूर्णांकerrupt context).
			 */
			अगर (igc_desc_unused(tx_ring) + 1 < tx_ring->count) अणु
				adapter->tx_समयout_count++;
				schedule_work(&adapter->reset_task);
				/* वापस immediately since reset is imminent */
				वापस;
			पूर्ण
		पूर्ण

		/* Force detection of hung controller every watchकरोg period */
		set_bit(IGC_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags);
	पूर्ण

	/* Cause software पूर्णांकerrupt to ensure Rx ring is cleaned */
	अगर (adapter->flags & IGC_FLAG_HAS_MSIX) अणु
		u32 eics = 0;

		क्रम (i = 0; i < adapter->num_q_vectors; i++)
			eics |= adapter->q_vector[i]->eims_value;
		wr32(IGC_EICS, eics);
	पूर्ण अन्यथा अणु
		wr32(IGC_ICS, IGC_ICS_RXDMT0);
	पूर्ण

	igc_ptp_tx_hang(adapter);

	/* Reset the समयr */
	अगर (!test_bit(__IGC_DOWN, &adapter->state)) अणु
		अगर (adapter->flags & IGC_FLAG_NEED_LINK_UPDATE)
			mod_समयr(&adapter->watchकरोg_समयr,
				  round_jअगरfies(jअगरfies +  HZ));
		अन्यथा
			mod_समयr(&adapter->watchकरोg_समयr,
				  round_jअगरfies(jअगरfies + 2 * HZ));
	पूर्ण
पूर्ण

/**
 * igc_पूर्णांकr_msi - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 */
अटल irqवापस_t igc_पूर्णांकr_msi(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igc_adapter *adapter = data;
	काष्ठा igc_q_vector *q_vector = adapter->q_vector[0];
	काष्ठा igc_hw *hw = &adapter->hw;
	/* पढ़ो ICR disables पूर्णांकerrupts using IAM */
	u32 icr = rd32(IGC_ICR);

	igc_ग_लिखो_itr(q_vector);

	अगर (icr & IGC_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	अगर (icr & IGC_ICR_DOUTSYNC) अणु
		/* HW is reporting DMA is out of sync */
		adapter->stats.करोosync++;
	पूर्ण

	अगर (icr & (IGC_ICR_RXSEQ | IGC_ICR_LSC)) अणु
		hw->mac.get_link_status = true;
		अगर (!test_bit(__IGC_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	napi_schedule(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * igc_पूर्णांकr - Legacy Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 */
अटल irqवापस_t igc_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igc_adapter *adapter = data;
	काष्ठा igc_q_vector *q_vector = adapter->q_vector[0];
	काष्ठा igc_hw *hw = &adapter->hw;
	/* Interrupt Auto-Mask...upon पढ़ोing ICR, पूर्णांकerrupts are masked.  No
	 * need क्रम the IMC ग_लिखो
	 */
	u32 icr = rd32(IGC_ICR);

	/* IMS will not स्वतः-mask अगर INT_ASSERTED is not set, and अगर it is
	 * not set, then the adapter didn't send an पूर्णांकerrupt
	 */
	अगर (!(icr & IGC_ICR_INT_ASSERTED))
		वापस IRQ_NONE;

	igc_ग_लिखो_itr(q_vector);

	अगर (icr & IGC_ICR_DRSTA)
		schedule_work(&adapter->reset_task);

	अगर (icr & IGC_ICR_DOUTSYNC) अणु
		/* HW is reporting DMA is out of sync */
		adapter->stats.करोosync++;
	पूर्ण

	अगर (icr & (IGC_ICR_RXSEQ | IGC_ICR_LSC)) अणु
		hw->mac.get_link_status = true;
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__IGC_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	napi_schedule(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम igc_मुक्त_irq(काष्ठा igc_adapter *adapter)
अणु
	अगर (adapter->msix_entries) अणु
		पूर्णांक vector = 0, i;

		मुक्त_irq(adapter->msix_entries[vector++].vector, adapter);

		क्रम (i = 0; i < adapter->num_q_vectors; i++)
			मुक्त_irq(adapter->msix_entries[vector++].vector,
				 adapter->q_vector[i]);
	पूर्ण अन्यथा अणु
		मुक्त_irq(adapter->pdev->irq, adapter);
	पूर्ण
पूर्ण

/**
 * igc_request_irq - initialize पूर्णांकerrupts
 * @adapter: Poपूर्णांकer to adapter काष्ठाure
 *
 * Attempts to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 */
अटल पूर्णांक igc_request_irq(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err = 0;

	अगर (adapter->flags & IGC_FLAG_HAS_MSIX) अणु
		err = igc_request_msix(adapter);
		अगर (!err)
			जाओ request_करोne;
		/* fall back to MSI */
		igc_मुक्त_all_tx_resources(adapter);
		igc_मुक्त_all_rx_resources(adapter);

		igc_clear_पूर्णांकerrupt_scheme(adapter);
		err = igc_init_पूर्णांकerrupt_scheme(adapter, false);
		अगर (err)
			जाओ request_करोne;
		igc_setup_all_tx_resources(adapter);
		igc_setup_all_rx_resources(adapter);
		igc_configure(adapter);
	पूर्ण

	igc_assign_vector(adapter->q_vector[0], 0);

	अगर (adapter->flags & IGC_FLAG_HAS_MSI) अणु
		err = request_irq(pdev->irq, &igc_पूर्णांकr_msi, 0,
				  netdev->name, adapter);
		अगर (!err)
			जाओ request_करोne;

		/* fall back to legacy पूर्णांकerrupts */
		igc_reset_पूर्णांकerrupt_capability(adapter);
		adapter->flags &= ~IGC_FLAG_HAS_MSI;
	पूर्ण

	err = request_irq(pdev->irq, &igc_पूर्णांकr, IRQF_SHARED,
			  netdev->name, adapter);

	अगर (err)
		netdev_err(netdev, "Error %d getting interrupt\n", err);

request_करोne:
	वापस err;
पूर्ण

/**
 * __igc_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @resuming: boolean indicating अगर the device is resuming
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 */
अटल पूर्णांक __igc_खोलो(काष्ठा net_device *netdev, bool resuming)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक err = 0;
	पूर्णांक i = 0;

	/* disallow खोलो during test */

	अगर (test_bit(__IGC_TESTING, &adapter->state)) अणु
		WARN_ON(resuming);
		वापस -EBUSY;
	पूर्ण

	अगर (!resuming)
		pm_runसमय_get_sync(&pdev->dev);

	netअगर_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = igc_setup_all_tx_resources(adapter);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = igc_setup_all_rx_resources(adapter);
	अगर (err)
		जाओ err_setup_rx;

	igc_घातer_up_link(adapter);

	igc_configure(adapter);

	err = igc_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	/* Notअगरy the stack of the actual queue counts. */
	err = netअगर_set_real_num_tx_queues(netdev, adapter->num_tx_queues);
	अगर (err)
		जाओ err_set_queues;

	err = netअगर_set_real_num_rx_queues(netdev, adapter->num_rx_queues);
	अगर (err)
		जाओ err_set_queues;

	clear_bit(__IGC_DOWN, &adapter->state);

	क्रम (i = 0; i < adapter->num_q_vectors; i++)
		napi_enable(&adapter->q_vector[i]->napi);

	/* Clear any pending पूर्णांकerrupts. */
	rd32(IGC_ICR);
	igc_irq_enable(adapter);

	अगर (!resuming)
		pm_runसमय_put(&pdev->dev);

	netअगर_tx_start_all_queues(netdev);

	/* start the watchकरोg. */
	hw->mac.get_link_status = true;
	schedule_work(&adapter->watchकरोg_task);

	वापस IGC_SUCCESS;

err_set_queues:
	igc_मुक्त_irq(adapter);
err_req_irq:
	igc_release_hw_control(adapter);
	igc_घातer_करोwn_phy_copper_base(&adapter->hw);
	igc_मुक्त_all_rx_resources(adapter);
err_setup_rx:
	igc_मुक्त_all_tx_resources(adapter);
err_setup_tx:
	igc_reset(adapter);
	अगर (!resuming)
		pm_runसमय_put(&pdev->dev);

	वापस err;
पूर्ण

पूर्णांक igc_खोलो(काष्ठा net_device *netdev)
अणु
	वापस __igc_खोलो(netdev, false);
पूर्ण

/**
 * __igc_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @suspending: boolean indicating the device is suspending
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the driver's control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 */
अटल पूर्णांक __igc_बंद(काष्ठा net_device *netdev, bool suspending)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;

	WARN_ON(test_bit(__IGC_RESETTING, &adapter->state));

	अगर (!suspending)
		pm_runसमय_get_sync(&pdev->dev);

	igc_करोwn(adapter);

	igc_release_hw_control(adapter);

	igc_मुक्त_irq(adapter);

	igc_मुक्त_all_tx_resources(adapter);
	igc_मुक्त_all_rx_resources(adapter);

	अगर (!suspending)
		pm_runसमय_put_sync(&pdev->dev);

	वापस 0;
पूर्ण

पूर्णांक igc_बंद(काष्ठा net_device *netdev)
अणु
	अगर (netअगर_device_present(netdev) || netdev->dismantle)
		वापस __igc_बंद(netdev, false);
	वापस 0;
पूर्ण

/**
 * igc_ioctl - Access the hwtstamp पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @अगरr: पूर्णांकerface request data
 * @cmd: ioctl command
 **/
अटल पूर्णांक igc_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGHWTSTAMP:
		वापस igc_ptp_get_ts_config(netdev, अगरr);
	हाल SIOCSHWTSTAMP:
		वापस igc_ptp_set_ts_config(netdev, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक igc_save_launchसमय_params(काष्ठा igc_adapter *adapter, पूर्णांक queue,
				      bool enable)
अणु
	काष्ठा igc_ring *ring;
	पूर्णांक i;

	अगर (queue < 0 || queue >= adapter->num_tx_queues)
		वापस -EINVAL;

	ring = adapter->tx_ring[queue];
	ring->launchसमय_enable = enable;

	अगर (adapter->base_समय)
		वापस 0;

	adapter->cycle_समय = NSEC_PER_SEC;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		ring = adapter->tx_ring[i];
		ring->start_समय = 0;
		ring->end_समय = NSEC_PER_SEC;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_base_समय_past(kसमय_प्रकार base_समय, स्थिर काष्ठा बारpec64 *now)
अणु
	काष्ठा बारpec64 b;

	b = kसमय_प्रकारo_बारpec64(base_समय);

	वापस बारpec64_compare(now, &b) > 0;
पूर्ण

अटल bool validate_schedule(काष्ठा igc_adapter *adapter,
			      स्थिर काष्ठा tc_taprio_qopt_offload *qopt)
अणु
	पूर्णांक queue_uses[IGC_MAX_TX_QUEUES] = अणु पूर्ण;
	काष्ठा बारpec64 now;
	माप_प्रकार n;

	अगर (qopt->cycle_समय_extension)
		वापस false;

	igc_ptp_पढ़ो(adapter, &now);

	/* If we program the controller's BASET रेजिस्टरs with a समय
	 * in the future, it will hold all the packets until that
	 * समय, causing a lot of TX Hangs, so to aव्योम that, we
	 * reject schedules that would start in the future.
	 */
	अगर (!is_base_समय_past(qopt->base_समय, &now))
		वापस false;

	क्रम (n = 0; n < qopt->num_entries; n++) अणु
		स्थिर काष्ठा tc_taprio_sched_entry *e;
		पूर्णांक i;

		e = &qopt->entries[n];

		/* i225 only supports "global" frame preemption
		 * settings.
		 */
		अगर (e->command != TC_TAPRIO_CMD_SET_GATES)
			वापस false;

		क्रम (i = 0; i < IGC_MAX_TX_QUEUES; i++) अणु
			अगर (e->gate_mask & BIT(i))
				queue_uses[i]++;

			अगर (queue_uses[i] > 1)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक igc_tsn_enable_launchसमय(काष्ठा igc_adapter *adapter,
				     काष्ठा tc_etf_qopt_offload *qopt)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक err;

	अगर (hw->mac.type != igc_i225)
		वापस -EOPNOTSUPP;

	err = igc_save_launchसमय_params(adapter, qopt->queue, qopt->enable);
	अगर (err)
		वापस err;

	वापस igc_tsn_offload_apply(adapter);
पूर्ण

अटल पूर्णांक igc_save_qbv_schedule(काष्ठा igc_adapter *adapter,
				 काष्ठा tc_taprio_qopt_offload *qopt)
अणु
	u32 start_समय = 0, end_समय = 0;
	माप_प्रकार n;

	अगर (!qopt->enable) अणु
		adapter->base_समय = 0;
		वापस 0;
	पूर्ण

	अगर (adapter->base_समय)
		वापस -EALREADY;

	अगर (!validate_schedule(adapter, qopt))
		वापस -EINVAL;

	adapter->cycle_समय = qopt->cycle_समय;
	adapter->base_समय = qopt->base_समय;

	/* FIXME: be a little smarter about हालs when the gate क्रम a
	 * queue stays खोलो क्रम more than one entry.
	 */
	क्रम (n = 0; n < qopt->num_entries; n++) अणु
		काष्ठा tc_taprio_sched_entry *e = &qopt->entries[n];
		पूर्णांक i;

		end_समय += e->पूर्णांकerval;

		क्रम (i = 0; i < IGC_MAX_TX_QUEUES; i++) अणु
			काष्ठा igc_ring *ring = adapter->tx_ring[i];

			अगर (!(e->gate_mask & BIT(i)))
				जारी;

			ring->start_समय = start_समय;
			ring->end_समय = end_समय;
		पूर्ण

		start_समय += e->पूर्णांकerval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igc_tsn_enable_qbv_scheduling(काष्ठा igc_adapter *adapter,
					 काष्ठा tc_taprio_qopt_offload *qopt)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक err;

	अगर (hw->mac.type != igc_i225)
		वापस -EOPNOTSUPP;

	err = igc_save_qbv_schedule(adapter, qopt);
	अगर (err)
		वापस err;

	वापस igc_tsn_offload_apply(adapter);
पूर्ण

अटल पूर्णांक igc_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			व्योम *type_data)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(dev);

	चयन (type) अणु
	हाल TC_SETUP_QDISC_TAPRIO:
		वापस igc_tsn_enable_qbv_scheduling(adapter, type_data);

	हाल TC_SETUP_QDISC_ETF:
		वापस igc_tsn_enable_launchसमय(adapter, type_data);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक igc_bpf(काष्ठा net_device *dev, काष्ठा netdev_bpf *bpf)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(dev);

	चयन (bpf->command) अणु
	हाल XDP_SETUP_PROG:
		वापस igc_xdp_set_prog(adapter, bpf->prog, bpf->extack);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक igc_xdp_xmit(काष्ठा net_device *dev, पूर्णांक num_frames,
			काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(dev);
	पूर्णांक cpu = smp_processor_id();
	काष्ठा netdev_queue *nq;
	काष्ठा igc_ring *ring;
	पूर्णांक i, drops;

	अगर (unlikely(test_bit(__IGC_DOWN, &adapter->state)))
		वापस -ENETDOWN;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	ring = igc_xdp_get_tx_ring(adapter, cpu);
	nq = txring_txq(ring);

	__netअगर_tx_lock(nq, cpu);

	drops = 0;
	क्रम (i = 0; i < num_frames; i++) अणु
		पूर्णांक err;
		काष्ठा xdp_frame *xdpf = frames[i];

		err = igc_xdp_init_tx_descriptor(ring, xdpf);
		अगर (err) अणु
			xdp_वापस_frame_rx_napi(xdpf);
			drops++;
		पूर्ण
	पूर्ण

	अगर (flags & XDP_XMIT_FLUSH)
		igc_flush_tx_descriptors(ring);

	__netअगर_tx_unlock(nq);

	वापस num_frames - drops;
पूर्ण

अटल स्थिर काष्ठा net_device_ops igc_netdev_ops = अणु
	.nकरो_खोलो		= igc_खोलो,
	.nकरो_stop		= igc_बंद,
	.nकरो_start_xmit		= igc_xmit_frame,
	.nकरो_set_rx_mode	= igc_set_rx_mode,
	.nकरो_set_mac_address	= igc_set_mac,
	.nकरो_change_mtu		= igc_change_mtu,
	.nकरो_get_stats64	= igc_get_stats64,
	.nकरो_fix_features	= igc_fix_features,
	.nकरो_set_features	= igc_set_features,
	.nकरो_features_check	= igc_features_check,
	.nकरो_करो_ioctl		= igc_ioctl,
	.nकरो_setup_tc		= igc_setup_tc,
	.nकरो_bpf		= igc_bpf,
	.nकरो_xdp_xmit		= igc_xdp_xmit,
पूर्ण;

/* PCIe configuration access */
व्योम igc_पढ़ो_pci_cfg(काष्ठा igc_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igc_adapter *adapter = hw->back;

	pci_पढ़ो_config_word(adapter->pdev, reg, value);
पूर्ण

व्योम igc_ग_लिखो_pci_cfg(काष्ठा igc_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igc_adapter *adapter = hw->back;

	pci_ग_लिखो_config_word(adapter->pdev, reg, *value);
पूर्ण

s32 igc_पढ़ो_pcie_cap_reg(काष्ठा igc_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igc_adapter *adapter = hw->back;

	अगर (!pci_is_pcie(adapter->pdev))
		वापस -IGC_ERR_CONFIG;

	pcie_capability_पढ़ो_word(adapter->pdev, reg, value);

	वापस IGC_SUCCESS;
पूर्ण

s32 igc_ग_लिखो_pcie_cap_reg(काष्ठा igc_hw *hw, u32 reg, u16 *value)
अणु
	काष्ठा igc_adapter *adapter = hw->back;

	अगर (!pci_is_pcie(adapter->pdev))
		वापस -IGC_ERR_CONFIG;

	pcie_capability_ग_लिखो_word(adapter->pdev, reg, *value);

	वापस IGC_SUCCESS;
पूर्ण

u32 igc_rd32(काष्ठा igc_hw *hw, u32 reg)
अणु
	काष्ठा igc_adapter *igc = container_of(hw, काष्ठा igc_adapter, hw);
	u8 __iomem *hw_addr = READ_ONCE(hw->hw_addr);
	u32 value = 0;

	value = पढ़ोl(&hw_addr[reg]);

	/* पढ़ोs should not वापस all F's */
	अगर (!(~value) && (!reg || !(~पढ़ोl(hw_addr)))) अणु
		काष्ठा net_device *netdev = igc->netdev;

		hw->hw_addr = शून्य;
		netअगर_device_detach(netdev);
		netdev_err(netdev, "PCIe link lost, device now detached\n");
		WARN(pci_device_is_present(igc->pdev),
		     "igc: Failed to read reg 0x%x!\n", reg);
	पूर्ण

	वापस value;
पूर्ण

पूर्णांक igc_set_spd_dplx(काष्ठा igc_adapter *adapter, u32 spd, u8 dplx)
अणु
	काष्ठा igc_mac_info *mac = &adapter->hw.mac;

	mac->स्वतःneg = false;

	/* Make sure dplx is at most 1 bit and lsb of speed is not set
	 * क्रम the चयन() below to work
	 */
	अगर ((spd & 1) || (dplx & ~1))
		जाओ err_inval;

	चयन (spd + dplx) अणु
	हाल SPEED_10 + DUPLEX_HALF:
		mac->क्रमced_speed_duplex = ADVERTISE_10_HALF;
		अवरोध;
	हाल SPEED_10 + DUPLEX_FULL:
		mac->क्रमced_speed_duplex = ADVERTISE_10_FULL;
		अवरोध;
	हाल SPEED_100 + DUPLEX_HALF:
		mac->क्रमced_speed_duplex = ADVERTISE_100_HALF;
		अवरोध;
	हाल SPEED_100 + DUPLEX_FULL:
		mac->क्रमced_speed_duplex = ADVERTISE_100_FULL;
		अवरोध;
	हाल SPEED_1000 + DUPLEX_FULL:
		mac->स्वतःneg = true;
		adapter->hw.phy.स्वतःneg_advertised = ADVERTISE_1000_FULL;
		अवरोध;
	हाल SPEED_1000 + DUPLEX_HALF: /* not supported */
		जाओ err_inval;
	हाल SPEED_2500 + DUPLEX_FULL:
		mac->स्वतःneg = true;
		adapter->hw.phy.स्वतःneg_advertised = ADVERTISE_2500_FULL;
		अवरोध;
	हाल SPEED_2500 + DUPLEX_HALF: /* not supported */
	शेष:
		जाओ err_inval;
	पूर्ण

	/* clear MDI, MDI(-X) override is only allowed when स्वतःneg enabled */
	adapter->hw.phy.mdix = AUTO_ALL_MODES;

	वापस 0;

err_inval:
	netdev_err(adapter->netdev, "Unsupported Speed/Duplex configuration\n");
	वापस -EINVAL;
पूर्ण

/**
 * igc_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in igc_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * igc_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 */
अटल पूर्णांक igc_probe(काष्ठा pci_dev *pdev,
		     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा igc_adapter *adapter;
	काष्ठा net_device *netdev;
	काष्ठा igc_hw *hw;
	स्थिर काष्ठा igc_info *ei = igc_info_tbl[ent->driver_data];
	पूर्णांक err, pci_using_dac;

	err = pci_enable_device_mem(pdev);
	अगर (err)
		वापस err;

	pci_using_dac = 0;
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (!err) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"No usable DMA configuration, aborting\n");
			जाओ err_dma;
		पूर्ण
	पूर्ण

	err = pci_request_mem_regions(pdev, igc_driver_name);
	अगर (err)
		जाओ err_pci_reg;

	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);

	err = -ENOMEM;
	netdev = alloc_etherdev_mq(माप(काष्ठा igc_adapter),
				   IGC_MAX_TX_QUEUES);

	अगर (!netdev)
		जाओ err_alloc_etherdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	hw = &adapter->hw;
	hw->back = adapter;
	adapter->port_num = hw->bus.func;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	err = pci_save_state(pdev);
	अगर (err)
		जाओ err_ioremap;

	err = -EIO;
	adapter->io_addr = ioremap(pci_resource_start(pdev, 0),
				   pci_resource_len(pdev, 0));
	अगर (!adapter->io_addr)
		जाओ err_ioremap;

	/* hw->hw_addr can be zeroed, so use adapter->io_addr क्रम unmap */
	hw->hw_addr = adapter->io_addr;

	netdev->netdev_ops = &igc_netdev_ops;
	igc_ethtool_set_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;

	netdev->mem_start = pci_resource_start(pdev, 0);
	netdev->mem_end = pci_resource_end(pdev, 0);

	/* PCI config space info */
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->revision_id = pdev->revision;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;

	/* Copy the शेष MAC and PHY function poपूर्णांकers */
	स_नकल(&hw->mac.ops, ei->mac_ops, माप(hw->mac.ops));
	स_नकल(&hw->phy.ops, ei->phy_ops, माप(hw->phy.ops));

	/* Initialize skew-specअगरic स्थिरants */
	err = ei->get_invariants(hw);
	अगर (err)
		जाओ err_sw_init;

	/* Add supported features to the features list*/
	netdev->features |= NETIF_F_SG;
	netdev->features |= NETIF_F_TSO;
	netdev->features |= NETIF_F_TSO6;
	netdev->features |= NETIF_F_TSO_ECN;
	netdev->features |= NETIF_F_RXCSUM;
	netdev->features |= NETIF_F_HW_CSUM;
	netdev->features |= NETIF_F_SCTP_CRC;
	netdev->features |= NETIF_F_HW_TC;

#घोषणा IGC_GSO_PARTIAL_FEATURES (NETIF_F_GSO_GRE | \
				  NETIF_F_GSO_GRE_CSUM | \
				  NETIF_F_GSO_IPXIP4 | \
				  NETIF_F_GSO_IPXIP6 | \
				  NETIF_F_GSO_UDP_TUNNEL | \
				  NETIF_F_GSO_UDP_TUNNEL_CSUM)

	netdev->gso_partial_features = IGC_GSO_PARTIAL_FEATURES;
	netdev->features |= NETIF_F_GSO_PARTIAL | IGC_GSO_PARTIAL_FEATURES;

	/* setup the निजी काष्ठाure */
	err = igc_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	/* copy netdev features पूर्णांकo list of user selectable features */
	netdev->hw_features |= NETIF_F_NTUPLE;
	netdev->hw_features |= netdev->features;

	अगर (pci_using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	/* MTU range: 68 - 9216 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = MAX_STD_JUMBO_FRAME_SIZE;

	/* beक्रमe पढ़ोing the NVM, reset the controller to put the device in a
	 * known good starting state
	 */
	hw->mac.ops.reset_hw(hw);

	अगर (igc_get_flash_presence_i225(hw)) अणु
		अगर (hw->nvm.ops.validate(hw) < 0) अणु
			dev_err(&pdev->dev, "The NVM Checksum Is Not Valid\n");
			err = -EIO;
			जाओ err_eeprom;
		पूर्ण
	पूर्ण

	अगर (eth_platक्रमm_get_mac_address(&pdev->dev, hw->mac.addr)) अणु
		/* copy the MAC address out of the NVM */
		अगर (hw->mac.ops.पढ़ो_mac_addr(hw))
			dev_err(&pdev->dev, "NVM Read Error\n");
	पूर्ण

	स_नकल(netdev->dev_addr, hw->mac.addr, netdev->addr_len);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		dev_err(&pdev->dev, "Invalid MAC Address\n");
		err = -EIO;
		जाओ err_eeprom;
	पूर्ण

	/* configure RXPBSIZE and TXPBSIZE */
	wr32(IGC_RXPBS, I225_RXPBSIZE_DEFAULT);
	wr32(IGC_TXPBS, I225_TXPBSIZE_DEFAULT);

	समयr_setup(&adapter->watchकरोg_समयr, igc_watchकरोg, 0);
	समयr_setup(&adapter->phy_info_समयr, igc_update_phy_info, 0);

	INIT_WORK(&adapter->reset_task, igc_reset_task);
	INIT_WORK(&adapter->watchकरोg_task, igc_watchकरोg_task);

	/* Initialize link properties that are user-changeable */
	adapter->fc_स्वतःneg = true;
	hw->mac.स्वतःneg = true;
	hw->phy.स्वतःneg_advertised = 0xaf;

	hw->fc.requested_mode = igc_fc_शेष;
	hw->fc.current_mode = igc_fc_शेष;

	/* By शेष, support wake on port A */
	adapter->flags |= IGC_FLAG_WOL_SUPPORTED;

	/* initialize the wol settings based on the eeprom settings */
	अगर (adapter->flags & IGC_FLAG_WOL_SUPPORTED)
		adapter->wol |= IGC_WUFC_MAG;

	device_set_wakeup_enable(&adapter->pdev->dev,
				 adapter->flags & IGC_FLAG_WOL_SUPPORTED);

	igc_ptp_init(adapter);

	/* reset the hardware with the new settings */
	igc_reset(adapter);

	/* let the f/w know that the h/w is now under the control of the
	 * driver.
	 */
	igc_get_hw_control(adapter);

	म_नकलन(netdev->name, "eth%d", IFNAMSIZ);
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	 /* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	/* Check अगर Media Autosense is enabled */
	adapter->ei = *ei;

	/* prपूर्णांक pcie link status and MAC address */
	pcie_prपूर्णांक_link_status(pdev);
	netdev_info(netdev, "MAC: %pM\n", netdev->dev_addr);

	dev_pm_set_driver_flags(&pdev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE);
	/* Disable EEE क्रम पूर्णांकernal PHY devices */
	hw->dev_spec._base.eee_enable = false;
	adapter->flags &= ~IGC_FLAG_EEE;
	igc_set_eee_i225(hw, false, false, false);

	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;

err_रेजिस्टर:
	igc_release_hw_control(adapter);
err_eeprom:
	अगर (!igc_check_reset_block(hw))
		igc_reset_phy(hw);
err_sw_init:
	igc_clear_पूर्णांकerrupt_scheme(adapter);
	iounmap(adapter->io_addr);
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_mem_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * igc_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * igc_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  This could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 */
अटल व्योम igc_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	pm_runसमय_get_noresume(&pdev->dev);

	igc_flush_nfc_rules(adapter);

	igc_ptp_stop(adapter);

	set_bit(__IGC_DOWN, &adapter->state);

	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_info_समयr);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchकरोg_task);

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have alपढ़ोy happened in बंद and is redundant.
	 */
	igc_release_hw_control(adapter);
	unरेजिस्टर_netdev(netdev);

	igc_clear_पूर्णांकerrupt_scheme(adapter);
	pci_iounmap(pdev, adapter->io_addr);
	pci_release_mem_regions(pdev);

	मुक्त_netdev(netdev);

	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __igc_shutकरोwn(काष्ठा pci_dev *pdev, bool *enable_wake,
			  bool runसमय)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	u32 wufc = runसमय ? IGC_WUFC_LNKC : adapter->wol;
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 ctrl, rctl, status;
	bool wake;

	rtnl_lock();
	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		__igc_बंद(netdev, true);

	igc_ptp_suspend(adapter);

	igc_clear_पूर्णांकerrupt_scheme(adapter);
	rtnl_unlock();

	status = rd32(IGC_STATUS);
	अगर (status & IGC_STATUS_LU)
		wufc &= ~IGC_WUFC_LNKC;

	अगर (wufc) अणु
		igc_setup_rctl(adapter);
		igc_set_rx_mode(netdev);

		/* turn on all-multi mode अगर wake on multicast is enabled */
		अगर (wufc & IGC_WUFC_MC) अणु
			rctl = rd32(IGC_RCTL);
			rctl |= IGC_RCTL_MPE;
			wr32(IGC_RCTL, rctl);
		पूर्ण

		ctrl = rd32(IGC_CTRL);
		ctrl |= IGC_CTRL_ADVD3WUC;
		wr32(IGC_CTRL, ctrl);

		/* Allow समय क्रम pending master requests to run */
		igc_disable_pcie_master(hw);

		wr32(IGC_WUC, IGC_WUC_PME_EN);
		wr32(IGC_WUFC, wufc);
	पूर्ण अन्यथा अणु
		wr32(IGC_WUC, 0);
		wr32(IGC_WUFC, 0);
	पूर्ण

	wake = wufc || adapter->en_mng_pt;
	अगर (!wake)
		igc_घातer_करोwn_phy_copper_base(&adapter->hw);
	अन्यथा
		igc_घातer_up_link(adapter);

	अगर (enable_wake)
		*enable_wake = wake;

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have alपढ़ोy happened in बंद and is redundant.
	 */
	igc_release_hw_control(adapter);

	pci_disable_device(pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक __maybe_unused igc_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस __igc_shutकरोwn(to_pci_dev(dev), शून्य, 1);
पूर्ण

अटल व्योम igc_deliver_wake_packet(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा sk_buff *skb;
	u32 wupl;

	wupl = rd32(IGC_WUPL) & IGC_WUPL_MASK;

	/* WUPM stores only the first 128 bytes of the wake packet.
	 * Read the packet only अगर we have the whole thing.
	 */
	अगर (wupl == 0 || wupl > IGC_WUPM_BYTES)
		वापस;

	skb = netdev_alloc_skb_ip_align(netdev, IGC_WUPM_BYTES);
	अगर (!skb)
		वापस;

	skb_put(skb, wupl);

	/* Ensure पढ़ोs are 32-bit aligned */
	wupl = roundup(wupl, 4);

	स_नकल_fromio(skb->data, hw->hw_addr + IGC_WUPM_REG(0), wupl);

	skb->protocol = eth_type_trans(skb, netdev);
	netअगर_rx(skb);
पूर्ण

अटल पूर्णांक __maybe_unused igc_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 err, val;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	अगर (!pci_device_is_present(pdev))
		वापस -ENODEV;
	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		netdev_err(netdev, "Cannot enable PCI device from suspend\n");
		वापस err;
	पूर्ण
	pci_set_master(pdev);

	pci_enable_wake(pdev, PCI_D3hot, 0);
	pci_enable_wake(pdev, PCI_D3cold, 0);

	अगर (igc_init_पूर्णांकerrupt_scheme(adapter, true)) अणु
		netdev_err(netdev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	igc_reset(adapter);

	/* let the f/w know that the h/w is now under the control of the
	 * driver.
	 */
	igc_get_hw_control(adapter);

	val = rd32(IGC_WUS);
	अगर (val & WAKE_PKT_WUS)
		igc_deliver_wake_packet(netdev);

	wr32(IGC_WUS, ~0);

	rtnl_lock();
	अगर (!err && netअगर_running(netdev))
		err = __igc_खोलो(netdev, true);

	अगर (!err)
		netअगर_device_attach(netdev);
	rtnl_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused igc_runसमय_resume(काष्ठा device *dev)
अणु
	वापस igc_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused igc_suspend(काष्ठा device *dev)
अणु
	वापस __igc_shutकरोwn(to_pci_dev(dev), शून्य, 0);
पूर्ण

अटल पूर्णांक __maybe_unused igc_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	अगर (!igc_has_link(adapter))
		pm_schedule_suspend(dev, MSEC_PER_SEC * 5);

	वापस -EBUSY;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल व्योम igc_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	bool wake;

	__igc_shutकरोwn(pdev, &wake, 0);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF) अणु
		pci_wake_from_d3(pdev, wake);
		pci_set_घातer_state(pdev, PCI_D3hot);
	पूर्ण
पूर्ण

/**
 *  igc_io_error_detected - called when PCI error is detected
 *  @pdev: Poपूर्णांकer to PCI device
 *  @state: The current PCI connection state
 *
 *  This function is called after a PCI bus error affecting
 *  this device has been detected.
 **/
अटल pci_ers_result_t igc_io_error_detected(काष्ठा pci_dev *pdev,
					      pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		igc_करोwn(adapter);
	pci_disable_device(pdev);

	/* Request a slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 *  igc_io_slot_reset - called after the PCI bus has been reset.
 *  @pdev: Poपूर्णांकer to PCI device
 *
 *  Restart the card from scratch, as अगर from a cold-boot. Implementation
 *  resembles the first-half of the igc_resume routine.
 **/
अटल pci_ers_result_t igc_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	pci_ers_result_t result;

	अगर (pci_enable_device_mem(pdev)) अणु
		netdev_err(netdev, "Could not re-enable PCI device after reset\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		pci_restore_state(pdev);
		pci_save_state(pdev);

		pci_enable_wake(pdev, PCI_D3hot, 0);
		pci_enable_wake(pdev, PCI_D3cold, 0);

		/* In हाल of PCI error, adapter loses its HW address
		 * so we should re-assign it here.
		 */
		hw->hw_addr = adapter->io_addr;

		igc_reset(adapter);
		wr32(IGC_WUS, ~0);
		result = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	वापस result;
पूर्ण

/**
 *  igc_io_resume - called when traffic can start to flow again.
 *  @pdev: Poपूर्णांकer to PCI device
 *
 *  This callback is called when the error recovery driver tells us that
 *  its OK to resume normal operation. Implementation resembles the
 *  second-half of the igc_resume routine.
 */
अटल व्योम igc_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	rtnl_lock();
	अगर (netअगर_running(netdev)) अणु
		अगर (igc_खोलो(netdev)) अणु
			netdev_err(netdev, "igc_open failed after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);

	/* let the f/w know that the h/w is now under the control of the
	 * driver.
	 */
	igc_get_hw_control(adapter);
	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers igc_err_handler = अणु
	.error_detected = igc_io_error_detected,
	.slot_reset = igc_io_slot_reset,
	.resume = igc_io_resume,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा dev_pm_ops igc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(igc_suspend, igc_resume)
	SET_RUNTIME_PM_OPS(igc_runसमय_suspend, igc_runसमय_resume,
			   igc_runसमय_idle)
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा pci_driver igc_driver = अणु
	.name     = igc_driver_name,
	.id_table = igc_pci_tbl,
	.probe    = igc_probe,
	.हटाओ   = igc_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver.pm = &igc_pm_ops,
#पूर्ण_अगर
	.shutकरोwn = igc_shutकरोwn,
	.err_handler = &igc_err_handler,
पूर्ण;

/**
 * igc_reinit_queues - वापस error
 * @adapter: poपूर्णांकer to adapter काष्ठाure
 */
पूर्णांक igc_reinit_queues(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0;

	अगर (netअगर_running(netdev))
		igc_बंद(netdev);

	igc_reset_पूर्णांकerrupt_capability(adapter);

	अगर (igc_init_पूर्णांकerrupt_scheme(adapter, true)) अणु
		netdev_err(netdev, "Unable to allocate memory for queues\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (netअगर_running(netdev))
		err = igc_खोलो(netdev);

	वापस err;
पूर्ण

/**
 * igc_get_hw_dev - वापस device
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * used by hardware layer to prपूर्णांक debugging inक्रमmation
 */
काष्ठा net_device *igc_get_hw_dev(काष्ठा igc_hw *hw)
अणु
	काष्ठा igc_adapter *adapter = hw->back;

	वापस adapter->netdev;
पूर्ण

/**
 * igc_init_module - Driver Registration Routine
 *
 * igc_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 */
अटल पूर्णांक __init igc_init_module(व्योम)
अणु
	पूर्णांक ret;

	pr_info("%s\n", igc_driver_string);
	pr_info("%s\n", igc_copyright);

	ret = pci_रेजिस्टर_driver(&igc_driver);
	वापस ret;
पूर्ण

module_init(igc_init_module);

/**
 * igc_निकास_module - Driver Exit Cleanup Routine
 *
 * igc_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 */
अटल व्योम __निकास igc_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&igc_driver);
पूर्ण

module_निकास(igc_निकास_module);
/* igc_मुख्य.c */
