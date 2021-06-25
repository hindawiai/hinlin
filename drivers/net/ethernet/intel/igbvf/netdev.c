<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009 - 2018 Intel Corporation. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/sctp.h>

#समावेश "igbvf.h"

अक्षर igbvf_driver_name[] = "igbvf";
अटल स्थिर अक्षर igbvf_driver_string[] =
		  "Intel(R) Gigabit Virtual Function Network Driver";
अटल स्थिर अक्षर igbvf_copyright[] =
		  "Copyright (c) 2009 - 2012 Intel Corporation.";

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV|NETIF_MSG_PROBE|NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल पूर्णांक igbvf_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
अटल व्योम igbvf_reset(काष्ठा igbvf_adapter *);
अटल व्योम igbvf_set_पूर्णांकerrupt_capability(काष्ठा igbvf_adapter *);
अटल व्योम igbvf_reset_पूर्णांकerrupt_capability(काष्ठा igbvf_adapter *);

अटल काष्ठा igbvf_info igbvf_vf_info = अणु
	.mac		= e1000_vfadapt,
	.flags		= 0,
	.pba		= 10,
	.init_ops	= e1000_init_function_poपूर्णांकers_vf,
पूर्ण;

अटल काष्ठा igbvf_info igbvf_i350_vf_info = अणु
	.mac		= e1000_vfadapt_i350,
	.flags		= 0,
	.pba		= 10,
	.init_ops	= e1000_init_function_poपूर्णांकers_vf,
पूर्ण;

अटल स्थिर काष्ठा igbvf_info *igbvf_info_tbl[] = अणु
	[board_vf]	= &igbvf_vf_info,
	[board_i350_vf]	= &igbvf_i350_vf_info,
पूर्ण;

/**
 * igbvf_desc_unused - calculate अगर we have unused descriptors
 * @ring: address of receive ring काष्ठाure
 **/
अटल पूर्णांक igbvf_desc_unused(काष्ठा igbvf_ring *ring)
अणु
	अगर (ring->next_to_clean > ring->next_to_use)
		वापस ring->next_to_clean - ring->next_to_use - 1;

	वापस ring->count + ring->next_to_clean - ring->next_to_use - 1;
पूर्ण

/**
 * igbvf_receive_skb - helper function to handle Rx indications
 * @adapter: board निजी काष्ठाure
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @skb: skb to indicate to stack
 * @status: descriptor status field as written by hardware
 * @vlan: descriptor vlan field as written by hardware (no le/be conversion)
 * @skb: poपूर्णांकer to sk_buff to be indicated to stack
 **/
अटल व्योम igbvf_receive_skb(काष्ठा igbvf_adapter *adapter,
			      काष्ठा net_device *netdev,
			      काष्ठा sk_buff *skb,
			      u32 status, u16 vlan)
अणु
	u16 vid;

	अगर (status & E1000_RXD_STAT_VP) अणु
		अगर ((adapter->flags & IGBVF_FLAG_RX_LB_VLAN_BSWAP) &&
		    (status & E1000_RXDEXT_STATERR_LB))
			vid = be16_to_cpu(vlan) & E1000_RXD_SPC_VLAN_MASK;
		अन्यथा
			vid = le16_to_cpu(vlan) & E1000_RXD_SPC_VLAN_MASK;
		अगर (test_bit(vid, adapter->active_vlans))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	पूर्ण

	napi_gro_receive(&adapter->rx_ring->napi, skb);
पूर्ण

अटल अंतरभूत व्योम igbvf_rx_checksum_adv(काष्ठा igbvf_adapter *adapter,
					 u32 status_err, काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	/* Ignore Checksum bit is set or checksum is disabled through ethtool */
	अगर ((status_err & E1000_RXD_STAT_IXSM) ||
	    (adapter->flags & IGBVF_FLAG_RX_CSUM_DISABLED))
		वापस;

	/* TCP/UDP checksum error bit is set */
	अगर (status_err &
	    (E1000_RXDEXT_STATERR_TCPE | E1000_RXDEXT_STATERR_IPE)) अणु
		/* let the stack verअगरy checksum errors */
		adapter->hw_csum_err++;
		वापस;
	पूर्ण

	/* It must be a TCP or UDP packet with a valid checksum */
	अगर (status_err & (E1000_RXD_STAT_TCPCS | E1000_RXD_STAT_UDPCS))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	adapter->hw_csum_good++;
पूर्ण

/**
 * igbvf_alloc_rx_buffers - Replace used receive buffers; packet split
 * @rx_ring: address of ring काष्ठाure to repopulate
 * @cleaned_count: number of buffers to repopulate
 **/
अटल व्योम igbvf_alloc_rx_buffers(काष्ठा igbvf_ring *rx_ring,
				   पूर्णांक cleaned_count)
अणु
	काष्ठा igbvf_adapter *adapter = rx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	जोड़ e1000_adv_rx_desc *rx_desc;
	काष्ठा igbvf_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	पूर्णांक bufsz;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	अगर (adapter->rx_ps_hdr_size)
		bufsz = adapter->rx_ps_hdr_size;
	अन्यथा
		bufsz = adapter->rx_buffer_len;

	जबतक (cleaned_count--) अणु
		rx_desc = IGBVF_RX_DESC_ADV(*rx_ring, i);

		अगर (adapter->rx_ps_hdr_size && !buffer_info->page_dma) अणु
			अगर (!buffer_info->page) अणु
				buffer_info->page = alloc_page(GFP_ATOMIC);
				अगर (!buffer_info->page) अणु
					adapter->alloc_rx_buff_failed++;
					जाओ no_buffers;
				पूर्ण
				buffer_info->page_offset = 0;
			पूर्ण अन्यथा अणु
				buffer_info->page_offset ^= PAGE_SIZE / 2;
			पूर्ण
			buffer_info->page_dma =
				dma_map_page(&pdev->dev, buffer_info->page,
					     buffer_info->page_offset,
					     PAGE_SIZE / 2,
					     DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&pdev->dev,
					      buffer_info->page_dma)) अणु
				__मुक्त_page(buffer_info->page);
				buffer_info->page = शून्य;
				dev_err(&pdev->dev, "RX DMA map failed\n");
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!buffer_info->skb) अणु
			skb = netdev_alloc_skb_ip_align(netdev, bufsz);
			अगर (!skb) अणु
				adapter->alloc_rx_buff_failed++;
				जाओ no_buffers;
			पूर्ण

			buffer_info->skb = skb;
			buffer_info->dma = dma_map_single(&pdev->dev, skb->data,
							  bufsz,
							  DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&pdev->dev, buffer_info->dma)) अणु
				dev_kमुक्त_skb(buffer_info->skb);
				buffer_info->skb = शून्य;
				dev_err(&pdev->dev, "RX DMA map failed\n");
				जाओ no_buffers;
			पूर्ण
		पूर्ण
		/* Refresh the desc even अगर buffer_addrs didn't change because
		 * each ग_लिखो-back erases this info.
		 */
		अगर (adapter->rx_ps_hdr_size) अणु
			rx_desc->पढ़ो.pkt_addr =
			     cpu_to_le64(buffer_info->page_dma);
			rx_desc->पढ़ो.hdr_addr = cpu_to_le64(buffer_info->dma);
		पूर्ण अन्यथा अणु
			rx_desc->पढ़ो.pkt_addr = cpu_to_le64(buffer_info->dma);
			rx_desc->पढ़ो.hdr_addr = 0;
		पूर्ण

		i++;
		अगर (i == rx_ring->count)
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	पूर्ण

no_buffers:
	अगर (rx_ring->next_to_use != i) अणु
		rx_ring->next_to_use = i;
		अगर (i == 0)
			i = (rx_ring->count - 1);
		अन्यथा
			i--;

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		*/
		wmb();
		ग_लिखोl(i, adapter->hw.hw_addr + rx_ring->tail);
	पूर्ण
पूर्ण

/**
 * igbvf_clean_rx_irq - Send received data up the network stack; legacy
 * @adapter: board निजी काष्ठाure
 * @work_करोne: output parameter used to indicate completed work
 * @work_to_करो: input parameter setting limit of work
 *
 * the वापस value indicates whether actual cleaning was करोne, there
 * is no guarantee that everything was cleaned
 **/
अटल bool igbvf_clean_rx_irq(काष्ठा igbvf_adapter *adapter,
			       पूर्णांक *work_करोne, पूर्णांक work_to_करो)
अणु
	काष्ठा igbvf_ring *rx_ring = adapter->rx_ring;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	जोड़ e1000_adv_rx_desc *rx_desc, *next_rxd;
	काष्ठा igbvf_buffer *buffer_info, *next_buffer;
	काष्ठा sk_buff *skb;
	bool cleaned = false;
	पूर्णांक cleaned_count = 0;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित पूर्णांक i;
	u32 length, hlen, staterr;

	i = rx_ring->next_to_clean;
	rx_desc = IGBVF_RX_DESC_ADV(*rx_ring, i);
	staterr = le32_to_cpu(rx_desc->wb.upper.status_error);

	जबतक (staterr & E1000_RXD_STAT_DD) अणु
		अगर (*work_करोne >= work_to_करो)
			अवरोध;
		(*work_करोne)++;
		rmb(); /* पढ़ो descriptor and rx_buffer_info after status DD */

		buffer_info = &rx_ring->buffer_info[i];

		/* HW will not DMA in data larger than the given buffer, even
		 * अगर it parses the (NFS, of course) header to be larger.  In
		 * that हाल, it fills the header buffer and spills the rest
		 * पूर्णांकo the page.
		 */
		hlen = (le16_to_cpu(rx_desc->wb.lower.lo_dword.hs_rss.hdr_info)
		       & E1000_RXDADV_HDRBUFLEN_MASK) >>
		       E1000_RXDADV_HDRBUFLEN_SHIFT;
		अगर (hlen > adapter->rx_ps_hdr_size)
			hlen = adapter->rx_ps_hdr_size;

		length = le16_to_cpu(rx_desc->wb.upper.length);
		cleaned = true;
		cleaned_count++;

		skb = buffer_info->skb;
		prefetch(skb->data - NET_IP_ALIGN);
		buffer_info->skb = शून्य;
		अगर (!adapter->rx_ps_hdr_size) अणु
			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 adapter->rx_buffer_len,
					 DMA_FROM_DEVICE);
			buffer_info->dma = 0;
			skb_put(skb, length);
			जाओ send_up;
		पूर्ण

		अगर (!skb_shinfo(skb)->nr_frags) अणु
			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 adapter->rx_ps_hdr_size,
					 DMA_FROM_DEVICE);
			buffer_info->dma = 0;
			skb_put(skb, hlen);
		पूर्ण

		अगर (length) अणु
			dma_unmap_page(&pdev->dev, buffer_info->page_dma,
				       PAGE_SIZE / 2,
				       DMA_FROM_DEVICE);
			buffer_info->page_dma = 0;

			skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
					   buffer_info->page,
					   buffer_info->page_offset,
					   length);

			अगर ((adapter->rx_buffer_len > (PAGE_SIZE / 2)) ||
			    (page_count(buffer_info->page) != 1))
				buffer_info->page = शून्य;
			अन्यथा
				get_page(buffer_info->page);

			skb->len += length;
			skb->data_len += length;
			skb->truesize += PAGE_SIZE / 2;
		पूर्ण
send_up:
		i++;
		अगर (i == rx_ring->count)
			i = 0;
		next_rxd = IGBVF_RX_DESC_ADV(*rx_ring, i);
		prefetch(next_rxd);
		next_buffer = &rx_ring->buffer_info[i];

		अगर (!(staterr & E1000_RXD_STAT_EOP)) अणु
			buffer_info->skb = next_buffer->skb;
			buffer_info->dma = next_buffer->dma;
			next_buffer->skb = skb;
			next_buffer->dma = 0;
			जाओ next_desc;
		पूर्ण

		अगर (staterr & E1000_RXDEXT_ERR_FRAME_ERR_MASK) अणु
			dev_kमुक्त_skb_irq(skb);
			जाओ next_desc;
		पूर्ण

		total_bytes += skb->len;
		total_packets++;

		igbvf_rx_checksum_adv(adapter, staterr, skb);

		skb->protocol = eth_type_trans(skb, netdev);

		igbvf_receive_skb(adapter, netdev, skb, staterr,
				  rx_desc->wb.upper.vlan);

next_desc:
		rx_desc->wb.upper.status_error = 0;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= IGBVF_RX_BUFFER_WRITE) अणु
			igbvf_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;

		staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	पूर्ण

	rx_ring->next_to_clean = i;
	cleaned_count = igbvf_desc_unused(rx_ring);

	अगर (cleaned_count)
		igbvf_alloc_rx_buffers(rx_ring, cleaned_count);

	adapter->total_rx_packets += total_packets;
	adapter->total_rx_bytes += total_bytes;
	netdev->stats.rx_bytes += total_bytes;
	netdev->stats.rx_packets += total_packets;
	वापस cleaned;
पूर्ण

अटल व्योम igbvf_put_txbuf(काष्ठा igbvf_adapter *adapter,
			    काष्ठा igbvf_buffer *buffer_info)
अणु
	अगर (buffer_info->dma) अणु
		अगर (buffer_info->mapped_as_page)
			dma_unmap_page(&adapter->pdev->dev,
				       buffer_info->dma,
				       buffer_info->length,
				       DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(&adapter->pdev->dev,
					 buffer_info->dma,
					 buffer_info->length,
					 DMA_TO_DEVICE);
		buffer_info->dma = 0;
	पूर्ण
	अगर (buffer_info->skb) अणु
		dev_kमुक्त_skb_any(buffer_info->skb);
		buffer_info->skb = शून्य;
	पूर्ण
	buffer_info->समय_stamp = 0;
पूर्ण

/**
 * igbvf_setup_tx_resources - allocate Tx resources (Descriptors)
 * @adapter: board निजी काष्ठाure
 * @tx_ring: ring being initialized
 *
 * Return 0 on success, negative on failure
 **/
पूर्णांक igbvf_setup_tx_resources(काष्ठा igbvf_adapter *adapter,
			     काष्ठा igbvf_ring *tx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size;

	size = माप(काष्ठा igbvf_buffer) * tx_ring->count;
	tx_ring->buffer_info = vzalloc(size);
	अगर (!tx_ring->buffer_info)
		जाओ err;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(जोड़ e1000_adv_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	tx_ring->desc = dma_alloc_coherent(&pdev->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc)
		जाओ err;

	tx_ring->adapter = adapter;
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	वापस 0;
err:
	vमुक्त(tx_ring->buffer_info);
	dev_err(&adapter->pdev->dev,
		"Unable to allocate memory for the transmit descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * igbvf_setup_rx_resources - allocate Rx resources (Descriptors)
 * @adapter: board निजी काष्ठाure
 * @rx_ring: ring being initialized
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक igbvf_setup_rx_resources(काष्ठा igbvf_adapter *adapter,
			     काष्ठा igbvf_ring *rx_ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक size, desc_len;

	size = माप(काष्ठा igbvf_buffer) * rx_ring->count;
	rx_ring->buffer_info = vzalloc(size);
	अगर (!rx_ring->buffer_info)
		जाओ err;

	desc_len = माप(जोड़ e1000_adv_rx_desc);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * desc_len;
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(&pdev->dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);
	अगर (!rx_ring->desc)
		जाओ err;

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	rx_ring->adapter = adapter;

	वापस 0;

err:
	vमुक्त(rx_ring->buffer_info);
	rx_ring->buffer_info = शून्य;
	dev_err(&adapter->pdev->dev,
		"Unable to allocate memory for the receive descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * igbvf_clean_tx_ring - Free Tx Buffers
 * @tx_ring: ring to be cleaned
 **/
अटल व्योम igbvf_clean_tx_ring(काष्ठा igbvf_ring *tx_ring)
अणु
	काष्ठा igbvf_adapter *adapter = tx_ring->adapter;
	काष्ठा igbvf_buffer *buffer_info;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	अगर (!tx_ring->buffer_info)
		वापस;

	/* Free all the Tx ring sk_buffs */
	क्रम (i = 0; i < tx_ring->count; i++) अणु
		buffer_info = &tx_ring->buffer_info[i];
		igbvf_put_txbuf(adapter, buffer_info);
	पूर्ण

	size = माप(काष्ठा igbvf_buffer) * tx_ring->count;
	स_रखो(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	ग_लिखोl(0, adapter->hw.hw_addr + tx_ring->head);
	ग_लिखोl(0, adapter->hw.hw_addr + tx_ring->tail);
पूर्ण

/**
 * igbvf_मुक्त_tx_resources - Free Tx Resources per Queue
 * @tx_ring: ring to मुक्त resources from
 *
 * Free all transmit software resources
 **/
व्योम igbvf_मुक्त_tx_resources(काष्ठा igbvf_ring *tx_ring)
अणु
	काष्ठा pci_dev *pdev = tx_ring->adapter->pdev;

	igbvf_clean_tx_ring(tx_ring);

	vमुक्त(tx_ring->buffer_info);
	tx_ring->buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, tx_ring->size, tx_ring->desc,
			  tx_ring->dma);

	tx_ring->desc = शून्य;
पूर्ण

/**
 * igbvf_clean_rx_ring - Free Rx Buffers per Queue
 * @rx_ring: ring काष्ठाure poपूर्णांकer to मुक्त buffers from
 **/
अटल व्योम igbvf_clean_rx_ring(काष्ठा igbvf_ring *rx_ring)
अणु
	काष्ठा igbvf_adapter *adapter = rx_ring->adapter;
	काष्ठा igbvf_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	अगर (!rx_ring->buffer_info)
		वापस;

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		अगर (buffer_info->dma) अणु
			अगर (adapter->rx_ps_hdr_size) अणु
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_ps_hdr_size,
						 DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_buffer_len,
						 DMA_FROM_DEVICE);
			पूर्ण
			buffer_info->dma = 0;
		पूर्ण

		अगर (buffer_info->skb) अणु
			dev_kमुक्त_skb(buffer_info->skb);
			buffer_info->skb = शून्य;
		पूर्ण

		अगर (buffer_info->page) अणु
			अगर (buffer_info->page_dma)
				dma_unmap_page(&pdev->dev,
					       buffer_info->page_dma,
					       PAGE_SIZE / 2,
					       DMA_FROM_DEVICE);
			put_page(buffer_info->page);
			buffer_info->page = शून्य;
			buffer_info->page_dma = 0;
			buffer_info->page_offset = 0;
		पूर्ण
	पूर्ण

	size = माप(काष्ठा igbvf_buffer) * rx_ring->count;
	स_रखो(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	ग_लिखोl(0, adapter->hw.hw_addr + rx_ring->head);
	ग_लिखोl(0, adapter->hw.hw_addr + rx_ring->tail);
पूर्ण

/**
 * igbvf_मुक्त_rx_resources - Free Rx Resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 **/

व्योम igbvf_मुक्त_rx_resources(काष्ठा igbvf_ring *rx_ring)
अणु
	काष्ठा pci_dev *pdev = rx_ring->adapter->pdev;

	igbvf_clean_rx_ring(rx_ring);

	vमुक्त(rx_ring->buffer_info);
	rx_ring->buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);
	rx_ring->desc = शून्य;
पूर्ण

/**
 * igbvf_update_itr - update the dynamic ITR value based on statistics
 * @adapter: poपूर्णांकer to adapter
 * @itr_setting: current adapter->itr
 * @packets: the number of packets during this measurement पूर्णांकerval
 * @bytes: the number of bytes during this measurement पूर्णांकerval
 *
 * Stores a new ITR value based on packets and byte counts during the last
 * पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt computation is faster updates
 * and more accurate ITR क्रम the current traffic pattern.  Constants in this
 * function were computed based on theoretical maximum wire speed and thresholds
 * were set based on testing data as well as attempting to minimize response
 * समय जबतक increasing bulk throughput.
 **/
अटल क्रमागत latency_range igbvf_update_itr(काष्ठा igbvf_adapter *adapter,
					   क्रमागत latency_range itr_setting,
					   पूर्णांक packets, पूर्णांक bytes)
अणु
	क्रमागत latency_range retval = itr_setting;

	अगर (packets == 0)
		जाओ update_itr_करोne;

	चयन (itr_setting) अणु
	हाल lowest_latency:
		/* handle TSO and jumbo frames */
		अगर (bytes/packets > 8000)
			retval = bulk_latency;
		अन्यथा अगर ((packets < 5) && (bytes > 512))
			retval = low_latency;
		अवरोध;
	हाल low_latency:  /* 50 usec aka 20000 पूर्णांकs/s */
		अगर (bytes > 10000) अणु
			/* this अगर handles the TSO accounting */
			अगर (bytes/packets > 8000)
				retval = bulk_latency;
			अन्यथा अगर ((packets < 10) || ((bytes/packets) > 1200))
				retval = bulk_latency;
			अन्यथा अगर ((packets > 35))
				retval = lowest_latency;
		पूर्ण अन्यथा अगर (bytes/packets > 2000) अणु
			retval = bulk_latency;
		पूर्ण अन्यथा अगर (packets <= 2 && bytes < 512) अणु
			retval = lowest_latency;
		पूर्ण
		अवरोध;
	हाल bulk_latency: /* 250 usec aka 4000 पूर्णांकs/s */
		अगर (bytes > 25000) अणु
			अगर (packets > 35)
				retval = low_latency;
		पूर्ण अन्यथा अगर (bytes < 6000) अणु
			retval = low_latency;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

update_itr_करोne:
	वापस retval;
पूर्ण

अटल पूर्णांक igbvf_range_to_itr(क्रमागत latency_range current_range)
अणु
	पूर्णांक new_itr;

	चयन (current_range) अणु
	/* counts and packets in update_itr are dependent on these numbers */
	हाल lowest_latency:
		new_itr = IGBVF_70K_ITR;
		अवरोध;
	हाल low_latency:
		new_itr = IGBVF_20K_ITR;
		अवरोध;
	हाल bulk_latency:
		new_itr = IGBVF_4K_ITR;
		अवरोध;
	शेष:
		new_itr = IGBVF_START_ITR;
		अवरोध;
	पूर्ण
	वापस new_itr;
पूर्ण

अटल व्योम igbvf_set_itr(काष्ठा igbvf_adapter *adapter)
अणु
	u32 new_itr;

	adapter->tx_ring->itr_range =
			igbvf_update_itr(adapter,
					 adapter->tx_ring->itr_val,
					 adapter->total_tx_packets,
					 adapter->total_tx_bytes);

	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (adapter->requested_itr == 3 &&
	    adapter->tx_ring->itr_range == lowest_latency)
		adapter->tx_ring->itr_range = low_latency;

	new_itr = igbvf_range_to_itr(adapter->tx_ring->itr_range);

	अगर (new_itr != adapter->tx_ring->itr_val) अणु
		u32 current_itr = adapter->tx_ring->itr_val;
		/* this attempts to bias the पूर्णांकerrupt rate towards Bulk
		 * by adding पूर्णांकermediate steps when पूर्णांकerrupt rate is
		 * increasing
		 */
		new_itr = new_itr > current_itr ?
			  min(current_itr + (new_itr >> 2), new_itr) :
			  new_itr;
		adapter->tx_ring->itr_val = new_itr;

		adapter->tx_ring->set_itr = 1;
	पूर्ण

	adapter->rx_ring->itr_range =
			igbvf_update_itr(adapter, adapter->rx_ring->itr_val,
					 adapter->total_rx_packets,
					 adapter->total_rx_bytes);
	अगर (adapter->requested_itr == 3 &&
	    adapter->rx_ring->itr_range == lowest_latency)
		adapter->rx_ring->itr_range = low_latency;

	new_itr = igbvf_range_to_itr(adapter->rx_ring->itr_range);

	अगर (new_itr != adapter->rx_ring->itr_val) अणु
		u32 current_itr = adapter->rx_ring->itr_val;

		new_itr = new_itr > current_itr ?
			  min(current_itr + (new_itr >> 2), new_itr) :
			  new_itr;
		adapter->rx_ring->itr_val = new_itr;

		adapter->rx_ring->set_itr = 1;
	पूर्ण
पूर्ण

/**
 * igbvf_clean_tx_irq - Reclaim resources after transmit completes
 * @tx_ring: ring काष्ठाure to clean descriptors from
 *
 * वापसs true अगर ring is completely cleaned
 **/
अटल bool igbvf_clean_tx_irq(काष्ठा igbvf_ring *tx_ring)
अणु
	काष्ठा igbvf_adapter *adapter = tx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा igbvf_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	जोड़ e1000_adv_tx_desc *tx_desc, *eop_desc;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित पूर्णांक i, count = 0;
	bool cleaned = false;

	i = tx_ring->next_to_clean;
	buffer_info = &tx_ring->buffer_info[i];
	eop_desc = buffer_info->next_to_watch;

	करो अणु
		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर DD is not set pending work has not been completed */
		अगर (!(eop_desc->wb.status & cpu_to_le32(E1000_TXD_STAT_DD)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		buffer_info->next_to_watch = शून्य;

		क्रम (cleaned = false; !cleaned; count++) अणु
			tx_desc = IGBVF_TX_DESC_ADV(*tx_ring, i);
			cleaned = (tx_desc == eop_desc);
			skb = buffer_info->skb;

			अगर (skb) अणु
				अचिन्हित पूर्णांक segs, bytecount;

				/* gso_segs is currently only valid क्रम tcp */
				segs = skb_shinfo(skb)->gso_segs ?: 1;
				/* multiply data chunks by size of headers */
				bytecount = ((segs - 1) * skb_headlen(skb)) +
					    skb->len;
				total_packets += segs;
				total_bytes += bytecount;
			पूर्ण

			igbvf_put_txbuf(adapter, buffer_info);
			tx_desc->wb.status = 0;

			i++;
			अगर (i == tx_ring->count)
				i = 0;

			buffer_info = &tx_ring->buffer_info[i];
		पूर्ण

		eop_desc = buffer_info->next_to_watch;
	पूर्ण जबतक (count < tx_ring->count);

	tx_ring->next_to_clean = i;

	अगर (unlikely(count && netअगर_carrier_ok(netdev) &&
	    igbvf_desc_unused(tx_ring) >= IGBVF_TX_QUEUE_WAKE)) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (netअगर_queue_stopped(netdev) &&
		    !(test_bit(__IGBVF_DOWN, &adapter->state))) अणु
			netअगर_wake_queue(netdev);
			++adapter->restart_queue;
		पूर्ण
	पूर्ण

	netdev->stats.tx_bytes += total_bytes;
	netdev->stats.tx_packets += total_packets;
	वापस count < tx_ring->count;
पूर्ण

अटल irqवापस_t igbvf_msix_other(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	adapter->पूर्णांक_counter1++;

	hw->mac.get_link_status = 1;
	अगर (!test_bit(__IGBVF_DOWN, &adapter->state))
		mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);

	ew32(EIMS, adapter->eims_other);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t igbvf_पूर्णांकr_msix_tx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा igbvf_ring *tx_ring = adapter->tx_ring;

	अगर (tx_ring->set_itr) अणु
		ग_लिखोl(tx_ring->itr_val,
		       adapter->hw.hw_addr + tx_ring->itr_रेजिस्टर);
		adapter->tx_ring->set_itr = 0;
	पूर्ण

	adapter->total_tx_bytes = 0;
	adapter->total_tx_packets = 0;

	/* स्वतः mask will स्वतःmatically re-enable the पूर्णांकerrupt when we ग_लिखो
	 * EICS
	 */
	अगर (!igbvf_clean_tx_irq(tx_ring))
		/* Ring was not completely cleaned, so fire another पूर्णांकerrupt */
		ew32(EICS, tx_ring->eims_value);
	अन्यथा
		ew32(EIMS, tx_ring->eims_value);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t igbvf_पूर्णांकr_msix_rx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	adapter->पूर्णांक_counter0++;

	/* Write the ITR value calculated at the end of the
	 * previous पूर्णांकerrupt.
	 */
	अगर (adapter->rx_ring->set_itr) अणु
		ग_लिखोl(adapter->rx_ring->itr_val,
		       adapter->hw.hw_addr + adapter->rx_ring->itr_रेजिस्टर);
		adapter->rx_ring->set_itr = 0;
	पूर्ण

	अगर (napi_schedule_prep(&adapter->rx_ring->napi)) अणु
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->rx_ring->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा IGBVF_NO_QUEUE -1

अटल व्योम igbvf_assign_vector(काष्ठा igbvf_adapter *adapter, पूर्णांक rx_queue,
				पूर्णांक tx_queue, पूर्णांक msix_vector)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ivar, index;

	/* 82576 uses a table-based method क्रम assigning vectors.
	 * Each queue has a single entry in the table to which we ग_लिखो
	 * a vector number aदीर्घ with a "valid" bit.  Sadly, the layout
	 * of the table is somewhat counterपूर्णांकuitive.
	 */
	अगर (rx_queue > IGBVF_NO_QUEUE) अणु
		index = (rx_queue >> 1);
		ivar = array_er32(IVAR0, index);
		अगर (rx_queue & 0x1) अणु
			/* vector goes पूर्णांकo third byte of रेजिस्टर */
			ivar = ivar & 0xFF00FFFF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 16;
		पूर्ण अन्यथा अणु
			/* vector goes पूर्णांकo low byte of रेजिस्टर */
			ivar = ivar & 0xFFFFFF00;
			ivar |= msix_vector | E1000_IVAR_VALID;
		पूर्ण
		adapter->rx_ring[rx_queue].eims_value = BIT(msix_vector);
		array_ew32(IVAR0, index, ivar);
	पूर्ण
	अगर (tx_queue > IGBVF_NO_QUEUE) अणु
		index = (tx_queue >> 1);
		ivar = array_er32(IVAR0, index);
		अगर (tx_queue & 0x1) अणु
			/* vector goes पूर्णांकo high byte of रेजिस्टर */
			ivar = ivar & 0x00FFFFFF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 24;
		पूर्ण अन्यथा अणु
			/* vector goes पूर्णांकo second byte of रेजिस्टर */
			ivar = ivar & 0xFFFF00FF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 8;
		पूर्ण
		adapter->tx_ring[tx_queue].eims_value = BIT(msix_vector);
		array_ew32(IVAR0, index, ivar);
	पूर्ण
पूर्ण

/**
 * igbvf_configure_msix - Configure MSI-X hardware
 * @adapter: board निजी काष्ठाure
 *
 * igbvf_configure_msix sets up the hardware to properly
 * generate MSI-X पूर्णांकerrupts.
 **/
अटल व्योम igbvf_configure_msix(काष्ठा igbvf_adapter *adapter)
अणु
	u32 पंचांगp;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा igbvf_ring *tx_ring = adapter->tx_ring;
	काष्ठा igbvf_ring *rx_ring = adapter->rx_ring;
	पूर्णांक vector = 0;

	adapter->eims_enable_mask = 0;

	igbvf_assign_vector(adapter, IGBVF_NO_QUEUE, 0, vector++);
	adapter->eims_enable_mask |= tx_ring->eims_value;
	ग_लिखोl(tx_ring->itr_val, hw->hw_addr + tx_ring->itr_रेजिस्टर);
	igbvf_assign_vector(adapter, 0, IGBVF_NO_QUEUE, vector++);
	adapter->eims_enable_mask |= rx_ring->eims_value;
	ग_लिखोl(rx_ring->itr_val, hw->hw_addr + rx_ring->itr_रेजिस्टर);

	/* set vector क्रम other causes, i.e. link changes */

	पंचांगp = (vector++ | E1000_IVAR_VALID);

	ew32(IVAR_MISC, पंचांगp);

	adapter->eims_enable_mask = GENMASK(vector - 1, 0);
	adapter->eims_other = BIT(vector - 1);
	e1e_flush();
पूर्ण

अटल व्योम igbvf_reset_पूर्णांकerrupt_capability(काष्ठा igbvf_adapter *adapter)
अणु
	अगर (adapter->msix_entries) अणु
		pci_disable_msix(adapter->pdev);
		kमुक्त(adapter->msix_entries);
		adapter->msix_entries = शून्य;
	पूर्ण
पूर्ण

/**
 * igbvf_set_पूर्णांकerrupt_capability - set MSI or MSI-X अगर supported
 * @adapter: board निजी काष्ठाure
 *
 * Attempt to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 **/
अटल व्योम igbvf_set_पूर्णांकerrupt_capability(काष्ठा igbvf_adapter *adapter)
अणु
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;

	/* we allocate 3 vectors, 1 क्रम Tx, 1 क्रम Rx, one क्रम PF messages */
	adapter->msix_entries = kसुस्मृति(3, माप(काष्ठा msix_entry),
					GFP_KERNEL);
	अगर (adapter->msix_entries) अणु
		क्रम (i = 0; i < 3; i++)
			adapter->msix_entries[i].entry = i;

		err = pci_enable_msix_range(adapter->pdev,
					    adapter->msix_entries, 3, 3);
	पूर्ण

	अगर (err < 0) अणु
		/* MSI-X failed */
		dev_err(&adapter->pdev->dev,
			"Failed to initialize MSI-X interrupts.\n");
		igbvf_reset_पूर्णांकerrupt_capability(adapter);
	पूर्ण
पूर्ण

/**
 * igbvf_request_msix - Initialize MSI-X पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * igbvf_request_msix allocates MSI-X vectors and requests पूर्णांकerrupts from the
 * kernel.
 **/
अटल पूर्णांक igbvf_request_msix(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0, vector = 0;

	अगर (म_माप(netdev->name) < (IFNAMSIZ - 5)) अणु
		प्र_लिखो(adapter->tx_ring->name, "%s-tx-0", netdev->name);
		प्र_लिखो(adapter->rx_ring->name, "%s-rx-0", netdev->name);
	पूर्ण अन्यथा अणु
		स_नकल(adapter->tx_ring->name, netdev->name, IFNAMSIZ);
		स_नकल(adapter->rx_ring->name, netdev->name, IFNAMSIZ);
	पूर्ण

	err = request_irq(adapter->msix_entries[vector].vector,
			  igbvf_पूर्णांकr_msix_tx, 0, adapter->tx_ring->name,
			  netdev);
	अगर (err)
		जाओ out;

	adapter->tx_ring->itr_रेजिस्टर = E1000_EITR(vector);
	adapter->tx_ring->itr_val = adapter->current_itr;
	vector++;

	err = request_irq(adapter->msix_entries[vector].vector,
			  igbvf_पूर्णांकr_msix_rx, 0, adapter->rx_ring->name,
			  netdev);
	अगर (err)
		जाओ out;

	adapter->rx_ring->itr_रेजिस्टर = E1000_EITR(vector);
	adapter->rx_ring->itr_val = adapter->current_itr;
	vector++;

	err = request_irq(adapter->msix_entries[vector].vector,
			  igbvf_msix_other, 0, netdev->name, netdev);
	अगर (err)
		जाओ out;

	igbvf_configure_msix(adapter);
	वापस 0;
out:
	वापस err;
पूर्ण

/**
 * igbvf_alloc_queues - Allocate memory क्रम all rings
 * @adapter: board निजी काष्ठाure to initialize
 **/
अटल पूर्णांक igbvf_alloc_queues(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	adapter->tx_ring = kzalloc(माप(काष्ठा igbvf_ring), GFP_KERNEL);
	अगर (!adapter->tx_ring)
		वापस -ENOMEM;

	adapter->rx_ring = kzalloc(माप(काष्ठा igbvf_ring), GFP_KERNEL);
	अगर (!adapter->rx_ring) अणु
		kमुक्त(adapter->tx_ring);
		वापस -ENOMEM;
	पूर्ण

	netअगर_napi_add(netdev, &adapter->rx_ring->napi, igbvf_poll, 64);

	वापस 0;
पूर्ण

/**
 * igbvf_request_irq - initialize पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * Attempts to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 **/
अटल पूर्णांक igbvf_request_irq(काष्ठा igbvf_adapter *adapter)
अणु
	पूर्णांक err = -1;

	/* igbvf supports msi-x only */
	अगर (adapter->msix_entries)
		err = igbvf_request_msix(adapter);

	अगर (!err)
		वापस err;

	dev_err(&adapter->pdev->dev,
		"Unable to allocate interrupt, Error: %d\n", err);

	वापस err;
पूर्ण

अटल व्योम igbvf_मुक्त_irq(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक vector;

	अगर (adapter->msix_entries) अणु
		क्रम (vector = 0; vector < 3; vector++)
			मुक्त_irq(adapter->msix_entries[vector].vector, netdev);
	पूर्ण
पूर्ण

/**
 * igbvf_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम igbvf_irq_disable(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	ew32(EIMC, ~0);

	अगर (adapter->msix_entries)
		ew32(EIAC, 0);
पूर्ण

/**
 * igbvf_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम igbvf_irq_enable(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	ew32(EIAC, adapter->eims_enable_mask);
	ew32(EIAM, adapter->eims_enable_mask);
	ew32(EIMS, adapter->eims_enable_mask);
पूर्ण

/**
 * igbvf_poll - NAPI Rx polling callback
 * @napi: काष्ठा associated with this polling callback
 * @budget: amount of packets driver is allowed to process this poll
 **/
अटल पूर्णांक igbvf_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा igbvf_ring *rx_ring = container_of(napi, काष्ठा igbvf_ring, napi);
	काष्ठा igbvf_adapter *adapter = rx_ring->adapter;
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक work_करोne = 0;

	igbvf_clean_rx_irq(adapter, &work_करोne, budget);

	अगर (work_करोne == budget)
		वापस budget;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne))) अणु
		अगर (adapter->requested_itr & 3)
			igbvf_set_itr(adapter);

		अगर (!test_bit(__IGBVF_DOWN, &adapter->state))
			ew32(EIMS, adapter->rx_ring->eims_value);
	पूर्ण

	वापस work_करोne;
पूर्ण

/**
 * igbvf_set_rlpml - set receive large packet maximum length
 * @adapter: board निजी काष्ठाure
 *
 * Configure the maximum size of packets that will be received
 */
अटल व्योम igbvf_set_rlpml(काष्ठा igbvf_adapter *adapter)
अणु
	पूर्णांक max_frame_size;
	काष्ठा e1000_hw *hw = &adapter->hw;

	max_frame_size = adapter->max_frame_size + VLAN_TAG_SIZE;

	spin_lock_bh(&hw->mbx_lock);

	e1000_rlpml_set_vf(hw, max_frame_size);

	spin_unlock_bh(&hw->mbx_lock);
पूर्ण

अटल पूर्णांक igbvf_vlan_rx_add_vid(काष्ठा net_device *netdev,
				 __be16 proto, u16 vid)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	spin_lock_bh(&hw->mbx_lock);

	अगर (hw->mac.ops.set_vfta(hw, vid, true)) अणु
		dev_warn(&adapter->pdev->dev, "Vlan id %d\n is not added", vid);
		spin_unlock_bh(&hw->mbx_lock);
		वापस -EINVAL;
	पूर्ण

	spin_unlock_bh(&hw->mbx_lock);

	set_bit(vid, adapter->active_vlans);
	वापस 0;
पूर्ण

अटल पूर्णांक igbvf_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				  __be16 proto, u16 vid)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	spin_lock_bh(&hw->mbx_lock);

	अगर (hw->mac.ops.set_vfta(hw, vid, false)) अणु
		dev_err(&adapter->pdev->dev,
			"Failed to remove vlan id %d\n", vid);
		spin_unlock_bh(&hw->mbx_lock);
		वापस -EINVAL;
	पूर्ण

	spin_unlock_bh(&hw->mbx_lock);

	clear_bit(vid, adapter->active_vlans);
	वापस 0;
पूर्ण

अटल व्योम igbvf_restore_vlan(काष्ठा igbvf_adapter *adapter)
अणु
	u16 vid;

	क्रम_each_set_bit(vid, adapter->active_vlans, VLAN_N_VID)
		igbvf_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), vid);
पूर्ण

/**
 * igbvf_configure_tx - Configure Transmit Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम igbvf_configure_tx(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा igbvf_ring *tx_ring = adapter->tx_ring;
	u64 tdba;
	u32 txdctl, dca_txctrl;

	/* disable transmits */
	txdctl = er32(TXDCTL(0));
	ew32(TXDCTL(0), txdctl & ~E1000_TXDCTL_QUEUE_ENABLE);
	e1e_flush();
	msleep(10);

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */
	ew32(TDLEN(0), tx_ring->count * माप(जोड़ e1000_adv_tx_desc));
	tdba = tx_ring->dma;
	ew32(TDBAL(0), (tdba & DMA_BIT_MASK(32)));
	ew32(TDBAH(0), (tdba >> 32));
	ew32(TDH(0), 0);
	ew32(TDT(0), 0);
	tx_ring->head = E1000_TDH(0);
	tx_ring->tail = E1000_TDT(0);

	/* Turn off Relaxed Ordering on head ग_लिखो-backs.  The ग_लिखोbacks
	 * MUST be delivered in order or it will completely screw up
	 * our bookkeeping.
	 */
	dca_txctrl = er32(DCA_TXCTRL(0));
	dca_txctrl &= ~E1000_DCA_TXCTRL_TX_WB_RO_EN;
	ew32(DCA_TXCTRL(0), dca_txctrl);

	/* enable transmits */
	txdctl |= E1000_TXDCTL_QUEUE_ENABLE;
	ew32(TXDCTL(0), txdctl);

	/* Setup Transmit Descriptor Settings क्रम eop descriptor */
	adapter->txd_cmd = E1000_ADVTXD_DCMD_EOP | E1000_ADVTXD_DCMD_IFCS;

	/* enable Report Status bit */
	adapter->txd_cmd |= E1000_ADVTXD_DCMD_RS;
पूर्ण

/**
 * igbvf_setup_srrctl - configure the receive control रेजिस्टरs
 * @adapter: Board निजी काष्ठाure
 **/
अटल व्योम igbvf_setup_srrctl(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 srrctl = 0;

	srrctl &= ~(E1000_SRRCTL_DESCTYPE_MASK |
		    E1000_SRRCTL_BSIZEHDR_MASK |
		    E1000_SRRCTL_BSIZEPKT_MASK);

	/* Enable queue drop to aव्योम head of line blocking */
	srrctl |= E1000_SRRCTL_DROP_EN;

	/* Setup buffer sizes */
	srrctl |= ALIGN(adapter->rx_buffer_len, 1024) >>
		  E1000_SRRCTL_BSIZEPKT_SHIFT;

	अगर (adapter->rx_buffer_len < 2048) अणु
		adapter->rx_ps_hdr_size = 0;
		srrctl |= E1000_SRRCTL_DESCTYPE_ADV_ONEBUF;
	पूर्ण अन्यथा अणु
		adapter->rx_ps_hdr_size = 128;
		srrctl |= adapter->rx_ps_hdr_size <<
			  E1000_SRRCTL_BSIZEHDRSIZE_SHIFT;
		srrctl |= E1000_SRRCTL_DESCTYPE_HDR_SPLIT_ALWAYS;
	पूर्ण

	ew32(SRRCTL(0), srrctl);
पूर्ण

/**
 * igbvf_configure_rx - Configure Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम igbvf_configure_rx(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा igbvf_ring *rx_ring = adapter->rx_ring;
	u64 rdba;
	u32 rxdctl;

	/* disable receives */
	rxdctl = er32(RXDCTL(0));
	ew32(RXDCTL(0), rxdctl & ~E1000_RXDCTL_QUEUE_ENABLE);
	e1e_flush();
	msleep(10);

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	rdba = rx_ring->dma;
	ew32(RDBAL(0), (rdba & DMA_BIT_MASK(32)));
	ew32(RDBAH(0), (rdba >> 32));
	ew32(RDLEN(0), rx_ring->count * माप(जोड़ e1000_adv_rx_desc));
	rx_ring->head = E1000_RDH(0);
	rx_ring->tail = E1000_RDT(0);
	ew32(RDH(0), 0);
	ew32(RDT(0), 0);

	rxdctl |= E1000_RXDCTL_QUEUE_ENABLE;
	rxdctl &= 0xFFF00000;
	rxdctl |= IGBVF_RX_PTHRESH;
	rxdctl |= IGBVF_RX_HTHRESH << 8;
	rxdctl |= IGBVF_RX_WTHRESH << 16;

	igbvf_set_rlpml(adapter);

	/* enable receives */
	ew32(RXDCTL(0), rxdctl);
पूर्ण

/**
 * igbvf_set_multi - Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_multi entry poपूर्णांक is called whenever the multicast address
 * list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper multicast,
 * promiscuous mode, and all-multi behavior.
 **/
अटल व्योम igbvf_set_multi(काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u8  *mta_list = शून्य;
	पूर्णांक i;

	अगर (!netdev_mc_empty(netdev)) अणु
		mta_list = kदो_स्मृति_array(netdev_mc_count(netdev), ETH_ALEN,
					 GFP_ATOMIC);
		अगर (!mta_list)
			वापस;
	पूर्ण

	/* prepare a packed array of only addresses. */
	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev)
		स_नकल(mta_list + (i++ * ETH_ALEN), ha->addr, ETH_ALEN);

	spin_lock_bh(&hw->mbx_lock);

	hw->mac.ops.update_mc_addr_list(hw, mta_list, i, 0, 0);

	spin_unlock_bh(&hw->mbx_lock);
	kमुक्त(mta_list);
पूर्ण

/**
 * igbvf_set_uni - Configure unicast MAC filters
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * This routine is responsible क्रम configuring the hardware क्रम proper
 * unicast filters.
 **/
अटल पूर्णांक igbvf_set_uni(काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (netdev_uc_count(netdev) > IGBVF_MAX_MAC_FILTERS) अणु
		pr_err("Too many unicast filters - No Space\n");
		वापस -ENOSPC;
	पूर्ण

	spin_lock_bh(&hw->mbx_lock);

	/* Clear all unicast MAC filters */
	hw->mac.ops.set_uc_addr(hw, E1000_VF_MAC_FILTER_CLR, शून्य);

	spin_unlock_bh(&hw->mbx_lock);

	अगर (!netdev_uc_empty(netdev)) अणु
		काष्ठा netdev_hw_addr *ha;

		/* Add MAC filters one by one */
		netdev_क्रम_each_uc_addr(ha, netdev) अणु
			spin_lock_bh(&hw->mbx_lock);

			hw->mac.ops.set_uc_addr(hw, E1000_VF_MAC_FILTER_ADD,
						ha->addr);

			spin_unlock_bh(&hw->mbx_lock);
			udelay(200);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम igbvf_set_rx_mode(काष्ठा net_device *netdev)
अणु
	igbvf_set_multi(netdev);
	igbvf_set_uni(netdev);
पूर्ण

/**
 * igbvf_configure - configure the hardware क्रम Rx and Tx
 * @adapter: निजी board काष्ठाure
 **/
अटल व्योम igbvf_configure(काष्ठा igbvf_adapter *adapter)
अणु
	igbvf_set_rx_mode(adapter->netdev);

	igbvf_restore_vlan(adapter);

	igbvf_configure_tx(adapter);
	igbvf_setup_srrctl(adapter);
	igbvf_configure_rx(adapter);
	igbvf_alloc_rx_buffers(adapter->rx_ring,
			       igbvf_desc_unused(adapter->rx_ring));
पूर्ण

/* igbvf_reset - bring the hardware पूर्णांकo a known good state
 * @adapter: निजी board काष्ठाure
 *
 * This function boots the hardware and enables some settings that
 * require a configuration cycle of the hardware - those cannot be
 * set/changed during runसमय. After reset the device needs to be
 * properly configured क्रम Rx, Tx etc.
 */
अटल व्योम igbvf_reset(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;

	spin_lock_bh(&hw->mbx_lock);

	/* Allow समय क्रम pending master requests to run */
	अगर (mac->ops.reset_hw(hw))
		dev_warn(&adapter->pdev->dev, "PF still resetting\n");

	mac->ops.init_hw(hw);

	spin_unlock_bh(&hw->mbx_lock);

	अगर (is_valid_ether_addr(adapter->hw.mac.addr)) अणु
		स_नकल(netdev->dev_addr, adapter->hw.mac.addr,
		       netdev->addr_len);
		स_नकल(netdev->perm_addr, adapter->hw.mac.addr,
		       netdev->addr_len);
	पूर्ण

	adapter->last_reset = jअगरfies;
पूर्ण

पूर्णांक igbvf_up(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* hardware has been reset, we need to reload some things */
	igbvf_configure(adapter);

	clear_bit(__IGBVF_DOWN, &adapter->state);

	napi_enable(&adapter->rx_ring->napi);
	अगर (adapter->msix_entries)
		igbvf_configure_msix(adapter);

	/* Clear any pending पूर्णांकerrupts. */
	er32(EICR);
	igbvf_irq_enable(adapter);

	/* start the watchकरोg */
	hw->mac.get_link_status = 1;
	mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);

	वापस 0;
पूर्ण

व्योम igbvf_करोwn(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rxdctl, txdctl;

	/* संकेत that we're करोwn so the पूर्णांकerrupt handler करोes not
	 * reschedule our watchकरोg समयr
	 */
	set_bit(__IGBVF_DOWN, &adapter->state);

	/* disable receives in the hardware */
	rxdctl = er32(RXDCTL(0));
	ew32(RXDCTL(0), rxdctl & ~E1000_RXDCTL_QUEUE_ENABLE);

	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);

	/* disable transmits in the hardware */
	txdctl = er32(TXDCTL(0));
	ew32(TXDCTL(0), txdctl & ~E1000_TXDCTL_QUEUE_ENABLE);

	/* flush both disables and रुको क्रम them to finish */
	e1e_flush();
	msleep(10);

	napi_disable(&adapter->rx_ring->napi);

	igbvf_irq_disable(adapter);

	del_समयr_sync(&adapter->watchकरोg_समयr);

	/* record the stats beक्रमe reset*/
	igbvf_update_stats(adapter);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	igbvf_reset(adapter);
	igbvf_clean_tx_ring(adapter->tx_ring);
	igbvf_clean_rx_ring(adapter->rx_ring);
पूर्ण

व्योम igbvf_reinit_locked(काष्ठा igbvf_adapter *adapter)
अणु
	might_sleep();
	जबतक (test_and_set_bit(__IGBVF_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	igbvf_करोwn(adapter);
	igbvf_up(adapter);
	clear_bit(__IGBVF_RESETTING, &adapter->state);
पूर्ण

/**
 * igbvf_sw_init - Initialize general software काष्ठाures (काष्ठा igbvf_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * igbvf_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 **/
अटल पूर्णांक igbvf_sw_init(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	s32 rc;

	adapter->rx_buffer_len = ETH_FRAME_LEN + VLAN_HLEN + ETH_FCS_LEN;
	adapter->rx_ps_hdr_size = 0;
	adapter->max_frame_size = netdev->mtu + ETH_HLEN + ETH_FCS_LEN;
	adapter->min_frame_size = ETH_ZLEN + ETH_FCS_LEN;

	adapter->tx_पूर्णांक_delay = 8;
	adapter->tx_असल_पूर्णांक_delay = 32;
	adapter->rx_पूर्णांक_delay = 0;
	adapter->rx_असल_पूर्णांक_delay = 8;
	adapter->requested_itr = 3;
	adapter->current_itr = IGBVF_START_ITR;

	/* Set various function poपूर्णांकers */
	adapter->ei->init_ops(&adapter->hw);

	rc = adapter->hw.mac.ops.init_params(&adapter->hw);
	अगर (rc)
		वापस rc;

	rc = adapter->hw.mbx.ops.init_params(&adapter->hw);
	अगर (rc)
		वापस rc;

	igbvf_set_पूर्णांकerrupt_capability(adapter);

	अगर (igbvf_alloc_queues(adapter))
		वापस -ENOMEM;

	spin_lock_init(&adapter->tx_queue_lock);

	/* Explicitly disable IRQ since the NIC can be in any state. */
	igbvf_irq_disable(adapter);

	spin_lock_init(&adapter->stats_lock);
	spin_lock_init(&adapter->hw.mbx_lock);

	set_bit(__IGBVF_DOWN, &adapter->state);
	वापस 0;
पूर्ण

अटल व्योम igbvf_initialize_last_counter_stats(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	adapter->stats.last_gprc = er32(VFGPRC);
	adapter->stats.last_gorc = er32(VFGORC);
	adapter->stats.last_gptc = er32(VFGPTC);
	adapter->stats.last_gotc = er32(VFGOTC);
	adapter->stats.last_mprc = er32(VFMPRC);
	adapter->stats.last_gotlbc = er32(VFGOTLBC);
	adapter->stats.last_gptlbc = er32(VFGPTLBC);
	adapter->stats.last_gorlbc = er32(VFGORLBC);
	adapter->stats.last_gprlbc = er32(VFGPRLBC);

	adapter->stats.base_gprc = er32(VFGPRC);
	adapter->stats.base_gorc = er32(VFGORC);
	adapter->stats.base_gptc = er32(VFGPTC);
	adapter->stats.base_gotc = er32(VFGOTC);
	adapter->stats.base_mprc = er32(VFMPRC);
	adapter->stats.base_gotlbc = er32(VFGOTLBC);
	adapter->stats.base_gptlbc = er32(VFGPTLBC);
	adapter->stats.base_gorlbc = er32(VFGORLBC);
	adapter->stats.base_gprlbc = er32(VFGPRLBC);
पूर्ण

/**
 * igbvf_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
अटल पूर्णांक igbvf_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* disallow खोलो during test */
	अगर (test_bit(__IGBVF_TESTING, &adapter->state))
		वापस -EBUSY;

	/* allocate transmit descriptors */
	err = igbvf_setup_tx_resources(adapter, adapter->tx_ring);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = igbvf_setup_rx_resources(adapter, adapter->rx_ring);
	अगर (err)
		जाओ err_setup_rx;

	/* beक्रमe we allocate an पूर्णांकerrupt, we must be पढ़ोy to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an पूर्णांकerrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler beक्रमe we करो so.
	 */
	igbvf_configure(adapter);

	err = igbvf_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	/* From here on the code is the same as igbvf_up() */
	clear_bit(__IGBVF_DOWN, &adapter->state);

	napi_enable(&adapter->rx_ring->napi);

	/* clear any pending पूर्णांकerrupts */
	er32(EICR);

	igbvf_irq_enable(adapter);

	/* start the watchकरोg */
	hw->mac.get_link_status = 1;
	mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);

	वापस 0;

err_req_irq:
	igbvf_मुक्त_rx_resources(adapter->rx_ring);
err_setup_rx:
	igbvf_मुक्त_tx_resources(adapter->tx_ring);
err_setup_tx:
	igbvf_reset(adapter);

	वापस err;
पूर्ण

/**
 * igbvf_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/
अटल पूर्णांक igbvf_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	WARN_ON(test_bit(__IGBVF_RESETTING, &adapter->state));
	igbvf_करोwn(adapter);

	igbvf_मुक्त_irq(adapter);

	igbvf_मुक्त_tx_resources(adapter->tx_ring);
	igbvf_मुक्त_rx_resources(adapter->rx_ring);

	वापस 0;
पूर्ण

/**
 * igbvf_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक igbvf_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(hw->mac.addr, addr->sa_data, netdev->addr_len);

	spin_lock_bh(&hw->mbx_lock);

	hw->mac.ops.rar_set(hw, hw->mac.addr, 0);

	spin_unlock_bh(&hw->mbx_lock);

	अगर (!ether_addr_equal(addr->sa_data, hw->mac.addr))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	वापस 0;
पूर्ण

#घोषणा UPDATE_VF_COUNTER(reg, name) \
अणु \
	u32 current_counter = er32(reg); \
	अगर (current_counter < adapter->stats.last_##name) \
		adapter->stats.name += 0x100000000LL; \
	adapter->stats.last_##name = current_counter; \
	adapter->stats.name &= 0xFFFFFFFF00000000LL; \
	adapter->stats.name |= current_counter; \
पूर्ण

/**
 * igbvf_update_stats - Update the board statistics counters
 * @adapter: board निजी काष्ठाure
**/
व्योम igbvf_update_stats(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;

	/* Prevent stats update जबतक adapter is being reset, link is करोwn
	 * or अगर the pci connection is करोwn.
	 */
	अगर (adapter->link_speed == 0)
		वापस;

	अगर (test_bit(__IGBVF_RESETTING, &adapter->state))
		वापस;

	अगर (pci_channel_offline(pdev))
		वापस;

	UPDATE_VF_COUNTER(VFGPRC, gprc);
	UPDATE_VF_COUNTER(VFGORC, gorc);
	UPDATE_VF_COUNTER(VFGPTC, gptc);
	UPDATE_VF_COUNTER(VFGOTC, gotc);
	UPDATE_VF_COUNTER(VFMPRC, mprc);
	UPDATE_VF_COUNTER(VFGOTLBC, gotlbc);
	UPDATE_VF_COUNTER(VFGPTLBC, gptlbc);
	UPDATE_VF_COUNTER(VFGORLBC, gorlbc);
	UPDATE_VF_COUNTER(VFGPRLBC, gprlbc);

	/* Fill out the OS statistics काष्ठाure */
	adapter->netdev->stats.multicast = adapter->stats.mprc;
पूर्ण

अटल व्योम igbvf_prपूर्णांक_link_info(काष्ठा igbvf_adapter *adapter)
अणु
	dev_info(&adapter->pdev->dev, "Link is Up %d Mbps %s Duplex\n",
		 adapter->link_speed,
		 adapter->link_duplex == FULL_DUPLEX ? "Full" : "Half");
पूर्ण

अटल bool igbvf_has_link(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 ret_val = E1000_SUCCESS;
	bool link_active;

	/* If पूर्णांकerface is करोwn, stay link करोwn */
	अगर (test_bit(__IGBVF_DOWN, &adapter->state))
		वापस false;

	spin_lock_bh(&hw->mbx_lock);

	ret_val = hw->mac.ops.check_क्रम_link(hw);

	spin_unlock_bh(&hw->mbx_lock);

	link_active = !hw->mac.get_link_status;

	/* अगर check क्रम link वापसs error we will need to reset */
	अगर (ret_val && समय_after(jअगरfies, adapter->last_reset + (10 * HZ)))
		schedule_work(&adapter->reset_task);

	वापस link_active;
पूर्ण

/**
 * igbvf_watchकरोg - Timer Call-back
 * @t: समयr list poपूर्णांकer containing निजी काष्ठा
 **/
अटल व्योम igbvf_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा igbvf_adapter *adapter = from_समयr(adapter, t, watchकरोg_समयr);

	/* Do the rest outside of पूर्णांकerrupt context */
	schedule_work(&adapter->watchकरोg_task);
पूर्ण

अटल व्योम igbvf_watchकरोg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igbvf_adapter *adapter = container_of(work,
						     काष्ठा igbvf_adapter,
						     watchकरोg_task);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;
	काष्ठा igbvf_ring *tx_ring = adapter->tx_ring;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 link;
	पूर्णांक tx_pending = 0;

	link = igbvf_has_link(adapter);

	अगर (link) अणु
		अगर (!netअगर_carrier_ok(netdev)) अणु
			mac->ops.get_link_up_info(&adapter->hw,
						  &adapter->link_speed,
						  &adapter->link_duplex);
			igbvf_prपूर्णांक_link_info(adapter);

			netअगर_carrier_on(netdev);
			netअगर_wake_queue(netdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			adapter->link_speed = 0;
			adapter->link_duplex = 0;
			dev_info(&adapter->pdev->dev, "Link is Down\n");
			netअगर_carrier_off(netdev);
			netअगर_stop_queue(netdev);
		पूर्ण
	पूर्ण

	अगर (netअगर_carrier_ok(netdev)) अणु
		igbvf_update_stats(adapter);
	पूर्ण अन्यथा अणु
		tx_pending = (igbvf_desc_unused(tx_ring) + 1 <
			      tx_ring->count);
		अगर (tx_pending) अणु
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get करोne, so reset controller to flush Tx.
			 * (Do the reset outside of पूर्णांकerrupt context).
			 */
			adapter->tx_समयout_count++;
			schedule_work(&adapter->reset_task);
		पूर्ण
	पूर्ण

	/* Cause software पूर्णांकerrupt to ensure Rx ring is cleaned */
	ew32(EICS, adapter->rx_ring->eims_value);

	/* Reset the समयr */
	अगर (!test_bit(__IGBVF_DOWN, &adapter->state))
		mod_समयr(&adapter->watchकरोg_समयr,
			  round_jअगरfies(jअगरfies + (2 * HZ)));
पूर्ण

#घोषणा IGBVF_TX_FLAGS_CSUM		0x00000001
#घोषणा IGBVF_TX_FLAGS_VLAN		0x00000002
#घोषणा IGBVF_TX_FLAGS_TSO		0x00000004
#घोषणा IGBVF_TX_FLAGS_IPV4		0x00000008
#घोषणा IGBVF_TX_FLAGS_VLAN_MASK	0xffff0000
#घोषणा IGBVF_TX_FLAGS_VLAN_SHIFT	16

अटल व्योम igbvf_tx_ctxtdesc(काष्ठा igbvf_ring *tx_ring, u32 vlan_macip_lens,
			      u32 type_tucmd, u32 mss_l4len_idx)
अणु
	काष्ठा e1000_adv_tx_context_desc *context_desc;
	काष्ठा igbvf_buffer *buffer_info;
	u16 i = tx_ring->next_to_use;

	context_desc = IGBVF_TX_CTXTDESC_ADV(*tx_ring, i);
	buffer_info = &tx_ring->buffer_info[i];

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identअगरy this as an advanced context descriptor */
	type_tucmd |= E1000_TXD_CMD_DEXT | E1000_ADVTXD_DTYP_CTXT;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->seqnum_seed	= 0;
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);

	buffer_info->समय_stamp = jअगरfies;
	buffer_info->dma = 0;
पूर्ण

अटल पूर्णांक igbvf_tso(काष्ठा igbvf_ring *tx_ring,
		     काष्ठा sk_buff *skb, u32 tx_flags, u8 *hdr_len)
अणु
	u32 vlan_macip_lens, type_tucmd, mss_l4len_idx;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
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
	type_tucmd = E1000_ADVTXD_TUCMD_L4T_TCP;

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
		type_tucmd |= E1000_ADVTXD_TUCMD_IPV4;

		ip.v4->tot_len = 0;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
	पूर्ण

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;

	/* compute length of segmentation header */
	*hdr_len = (l4.tcp->करोff * 4) + l4_offset;

	/* हटाओ payload length from inner checksum */
	paylen = skb->len - l4_offset;
	csum_replace_by_dअगरf(&l4.tcp->check, htonl(paylen));

	/* MSS L4LEN IDX */
	mss_l4len_idx = (*hdr_len - l4_offset) << E1000_ADVTXD_L4LEN_SHIFT;
	mss_l4len_idx |= skb_shinfo(skb)->gso_size << E1000_ADVTXD_MSS_SHIFT;

	/* VLAN MACLEN IPLEN */
	vlan_macip_lens = l4.hdr - ip.hdr;
	vlan_macip_lens |= (ip.hdr - skb->data) << E1000_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= tx_flags & IGBVF_TX_FLAGS_VLAN_MASK;

	igbvf_tx_ctxtdesc(tx_ring, vlan_macip_lens, type_tucmd, mss_l4len_idx);

	वापस 1;
पूर्ण

अटल bool igbvf_tx_csum(काष्ठा igbvf_ring *tx_ring, काष्ठा sk_buff *skb,
			  u32 tx_flags, __be16 protocol)
अणु
	u32 vlan_macip_lens = 0;
	u32 type_tucmd = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
csum_failed:
		अगर (!(tx_flags & IGBVF_TX_FLAGS_VLAN))
			वापस false;
		जाओ no_csum;
	पूर्ण

	चयन (skb->csum_offset) अणु
	हाल दुरत्व(काष्ठा tcphdr, check):
		type_tucmd = E1000_ADVTXD_TUCMD_L4T_TCP;
		fallthrough;
	हाल दुरत्व(काष्ठा udphdr, check):
		अवरोध;
	हाल दुरत्व(काष्ठा sctphdr, checksum):
		/* validate that this is actually an SCTP request */
		अगर (skb_csum_is_sctp(skb)) अणु
			type_tucmd = E1000_ADVTXD_TUCMD_L4T_SCTP;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		skb_checksum_help(skb);
		जाओ csum_failed;
	पूर्ण

	vlan_macip_lens = skb_checksum_start_offset(skb) -
			  skb_network_offset(skb);
no_csum:
	vlan_macip_lens |= skb_network_offset(skb) << E1000_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= tx_flags & IGBVF_TX_FLAGS_VLAN_MASK;

	igbvf_tx_ctxtdesc(tx_ring, vlan_macip_lens, type_tucmd, 0);
	वापस true;
पूर्ण

अटल पूर्णांक igbvf_maybe_stop_tx(काष्ठा net_device *netdev, पूर्णांक size)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	/* there is enough descriptors then we करोn't need to worry  */
	अगर (igbvf_desc_unused(adapter->tx_ring) >= size)
		वापस 0;

	netअगर_stop_queue(netdev);

	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it.
	 */
	smp_mb();

	/* We need to check again just in हाल room has been made available */
	अगर (igbvf_desc_unused(adapter->tx_ring) < size)
		वापस -EBUSY;

	netअगर_wake_queue(netdev);

	++adapter->restart_queue;
	वापस 0;
पूर्ण

#घोषणा IGBVF_MAX_TXD_PWR	16
#घोषणा IGBVF_MAX_DATA_PER_TXD	(1u << IGBVF_MAX_TXD_PWR)

अटल अंतरभूत पूर्णांक igbvf_tx_map_adv(काष्ठा igbvf_adapter *adapter,
				   काष्ठा igbvf_ring *tx_ring,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा igbvf_buffer *buffer_info;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	अचिन्हित पूर्णांक count = 0, i;
	अचिन्हित पूर्णांक f;

	i = tx_ring->next_to_use;

	buffer_info = &tx_ring->buffer_info[i];
	BUG_ON(len >= IGBVF_MAX_DATA_PER_TXD);
	buffer_info->length = len;
	/* set समय_stamp *beक्रमe* dma to help aव्योम a possible race */
	buffer_info->समय_stamp = jअगरfies;
	buffer_info->mapped_as_page = false;
	buffer_info->dma = dma_map_single(&pdev->dev, skb->data, len,
					  DMA_TO_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
		जाओ dma_error;

	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++) अणु
		स्थिर skb_frag_t *frag;

		count++;
		i++;
		अगर (i == tx_ring->count)
			i = 0;

		frag = &skb_shinfo(skb)->frags[f];
		len = skb_frag_size(frag);

		buffer_info = &tx_ring->buffer_info[i];
		BUG_ON(len >= IGBVF_MAX_DATA_PER_TXD);
		buffer_info->length = len;
		buffer_info->समय_stamp = jअगरfies;
		buffer_info->mapped_as_page = true;
		buffer_info->dma = skb_frag_dma_map(&pdev->dev, frag, 0, len,
						    DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
			जाओ dma_error;
	पूर्ण

	tx_ring->buffer_info[i].skb = skb;

	वापस ++count;

dma_error:
	dev_err(&pdev->dev, "TX DMA map failed\n");

	/* clear बारtamp and dma mappings क्रम failed buffer_info mapping */
	buffer_info->dma = 0;
	buffer_info->समय_stamp = 0;
	buffer_info->length = 0;
	buffer_info->mapped_as_page = false;
	अगर (count)
		count--;

	/* clear बारtamp and dma mappings क्रम reमुख्यing portion of packet */
	जबतक (count--) अणु
		अगर (i == 0)
			i += tx_ring->count;
		i--;
		buffer_info = &tx_ring->buffer_info[i];
		igbvf_put_txbuf(adapter, buffer_info);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम igbvf_tx_queue_adv(काष्ठा igbvf_adapter *adapter,
				      काष्ठा igbvf_ring *tx_ring,
				      पूर्णांक tx_flags, पूर्णांक count,
				      अचिन्हित पूर्णांक first, u32 paylen,
				      u8 hdr_len)
अणु
	जोड़ e1000_adv_tx_desc *tx_desc = शून्य;
	काष्ठा igbvf_buffer *buffer_info;
	u32 olinfo_status = 0, cmd_type_len;
	अचिन्हित पूर्णांक i;

	cmd_type_len = (E1000_ADVTXD_DTYP_DATA | E1000_ADVTXD_DCMD_IFCS |
			E1000_ADVTXD_DCMD_DEXT);

	अगर (tx_flags & IGBVF_TX_FLAGS_VLAN)
		cmd_type_len |= E1000_ADVTXD_DCMD_VLE;

	अगर (tx_flags & IGBVF_TX_FLAGS_TSO) अणु
		cmd_type_len |= E1000_ADVTXD_DCMD_TSE;

		/* insert tcp checksum */
		olinfo_status |= E1000_TXD_POPTS_TXSM << 8;

		/* insert ip checksum */
		अगर (tx_flags & IGBVF_TX_FLAGS_IPV4)
			olinfo_status |= E1000_TXD_POPTS_IXSM << 8;

	पूर्ण अन्यथा अगर (tx_flags & IGBVF_TX_FLAGS_CSUM) अणु
		olinfo_status |= E1000_TXD_POPTS_TXSM << 8;
	पूर्ण

	olinfo_status |= ((paylen - hdr_len) << E1000_ADVTXD_PAYLEN_SHIFT);

	i = tx_ring->next_to_use;
	जबतक (count--) अणु
		buffer_info = &tx_ring->buffer_info[i];
		tx_desc = IGBVF_TX_DESC_ADV(*tx_ring, i);
		tx_desc->पढ़ो.buffer_addr = cpu_to_le64(buffer_info->dma);
		tx_desc->पढ़ो.cmd_type_len =
			 cpu_to_le32(cmd_type_len | buffer_info->length);
		tx_desc->पढ़ो.olinfo_status = cpu_to_le32(olinfo_status);
		i++;
		अगर (i == tx_ring->count)
			i = 0;
	पूर्ण

	tx_desc->पढ़ो.cmd_type_len |= cpu_to_le32(adapter->txd_cmd);
	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64).
	 */
	wmb();

	tx_ring->buffer_info[first].next_to_watch = tx_desc;
	tx_ring->next_to_use = i;
	ग_लिखोl(i, adapter->hw.hw_addr + tx_ring->tail);
पूर्ण

अटल netdev_tx_t igbvf_xmit_frame_ring_adv(काष्ठा sk_buff *skb,
					     काष्ठा net_device *netdev,
					     काष्ठा igbvf_ring *tx_ring)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक first, tx_flags = 0;
	u8 hdr_len = 0;
	पूर्णांक count = 0;
	पूर्णांक tso = 0;
	__be16 protocol = vlan_get_protocol(skb);

	अगर (test_bit(__IGBVF_DOWN, &adapter->state)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb->len <= 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* need: count + 4 desc gap to keep tail from touching
	 *       + 2 desc gap to keep tail from touching head,
	 *       + 1 desc क्रम skb->data,
	 *       + 1 desc क्रम context descriptor,
	 * head, otherwise try next समय
	 */
	अगर (igbvf_maybe_stop_tx(netdev, skb_shinfo(skb)->nr_frags + 4)) अणु
		/* this is a hard error */
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= IGBVF_TX_FLAGS_VLAN;
		tx_flags |= (skb_vlan_tag_get(skb) <<
			     IGBVF_TX_FLAGS_VLAN_SHIFT);
	पूर्ण

	अगर (protocol == htons(ETH_P_IP))
		tx_flags |= IGBVF_TX_FLAGS_IPV4;

	first = tx_ring->next_to_use;

	tso = igbvf_tso(tx_ring, skb, tx_flags, &hdr_len);
	अगर (unlikely(tso < 0)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (tso)
		tx_flags |= IGBVF_TX_FLAGS_TSO;
	अन्यथा अगर (igbvf_tx_csum(tx_ring, skb, tx_flags, protocol) &&
		 (skb->ip_summed == CHECKSUM_PARTIAL))
		tx_flags |= IGBVF_TX_FLAGS_CSUM;

	/* count reflects descriptors mapped, अगर 0 then mapping error
	 * has occurred and we need to शुरुआत the descriptor queue
	 */
	count = igbvf_tx_map_adv(adapter, tx_ring, skb);

	अगर (count) अणु
		igbvf_tx_queue_adv(adapter, tx_ring, tx_flags, count,
				   first, skb->len, hdr_len);
		/* Make sure there is space in the ring क्रम the next send. */
		igbvf_maybe_stop_tx(netdev, MAX_SKB_FRAGS + 4);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
		tx_ring->buffer_info[first].समय_stamp = 0;
		tx_ring->next_to_use = first;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t igbvf_xmit_frame(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा igbvf_ring *tx_ring;

	अगर (test_bit(__IGBVF_DOWN, &adapter->state)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	tx_ring = &adapter->tx_ring[0];

	वापस igbvf_xmit_frame_ring_adv(skb, netdev, tx_ring);
पूर्ण

/**
 * igbvf_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: queue timing out (unused)
 **/
अटल व्योम igbvf_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	adapter->tx_समयout_count++;
	schedule_work(&adapter->reset_task);
पूर्ण

अटल व्योम igbvf_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igbvf_adapter *adapter;

	adapter = container_of(work, काष्ठा igbvf_adapter, reset_task);

	igbvf_reinit_locked(adapter);
पूर्ण

/**
 * igbvf_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक igbvf_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	पूर्णांक max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;

	जबतक (test_and_set_bit(__IGBVF_RESETTING, &adapter->state))
		usleep_range(1000, 2000);
	/* igbvf_करोwn has a dependency on max_frame_size */
	adapter->max_frame_size = max_frame;
	अगर (netअगर_running(netdev))
		igbvf_करोwn(adapter);

	/* NOTE: netdev_alloc_skb reserves 16 bytes, and typically NET_IP_ALIGN
	 * means we reserve 2 more, this pushes us to allocate from the next
	 * larger slab size.
	 * i.e. RXBUFFER_2048 --> size-4096 slab
	 * However with the new *_jumbo_rx* routines, jumbo receives will use
	 * fragmented skbs
	 */

	अगर (max_frame <= 1024)
		adapter->rx_buffer_len = 1024;
	अन्यथा अगर (max_frame <= 2048)
		adapter->rx_buffer_len = 2048;
	अन्यथा
#अगर (PAGE_SIZE / 2) > 16384
		adapter->rx_buffer_len = 16384;
#अन्यथा
		adapter->rx_buffer_len = PAGE_SIZE / 2;
#पूर्ण_अगर

	/* adjust allocation अगर LPE protects us, and we aren't using SBP */
	अगर ((max_frame == ETH_FRAME_LEN + ETH_FCS_LEN) ||
	    (max_frame == ETH_FRAME_LEN + VLAN_HLEN + ETH_FCS_LEN))
		adapter->rx_buffer_len = ETH_FRAME_LEN + VLAN_HLEN +
					 ETH_FCS_LEN;

	netdev_dbg(netdev, "changing MTU from %d to %d\n",
		   netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		igbvf_up(adapter);
	अन्यथा
		igbvf_reset(adapter);

	clear_bit(__IGBVF_RESETTING, &adapter->state);

	वापस 0;
पूर्ण

अटल पूर्णांक igbvf_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक igbvf_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev_d);
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev)) अणु
		WARN_ON(test_bit(__IGBVF_RESETTING, &adapter->state));
		igbvf_करोwn(adapter);
		igbvf_मुक्त_irq(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused igbvf_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	u32 err;

	pci_set_master(pdev);

	अगर (netअगर_running(netdev)) अणु
		err = igbvf_request_irq(adapter);
		अगर (err)
			वापस err;
	पूर्ण

	igbvf_reset(adapter);

	अगर (netअगर_running(netdev))
		igbvf_up(adapter);

	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण

अटल व्योम igbvf_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	igbvf_suspend(&pdev->dev);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/* Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम igbvf_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	disable_irq(adapter->pdev->irq);

	igbvf_clean_tx_irq(adapter->tx_ring);

	enable_irq(adapter->pdev->irq);
पूर्ण
#पूर्ण_अगर

/**
 * igbvf_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t igbvf_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	netअगर_device_detach(netdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	अगर (netअगर_running(netdev))
		igbvf_करोwn(adapter);
	pci_disable_device(pdev);

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * igbvf_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot. Implementation
 * resembles the first-half of the igbvf_resume routine.
 */
अटल pci_ers_result_t igbvf_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	अगर (pci_enable_device_mem(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	pci_set_master(pdev);

	igbvf_reset(adapter);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * igbvf_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation. Implementation resembles the
 * second-half of the igbvf_resume routine.
 */
अटल व्योम igbvf_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev)) अणु
		अगर (igbvf_up(adapter)) अणु
			dev_err(&pdev->dev,
				"can't bring device back up after reset\n");
			वापस;
		पूर्ण
	पूर्ण

	netअगर_device_attach(netdev);
पूर्ण

अटल व्योम igbvf_prपूर्णांक_device_info(काष्ठा igbvf_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;

	अगर (hw->mac.type == e1000_vfadapt_i350)
		dev_info(&pdev->dev, "Intel(R) I350 Virtual Function\n");
	अन्यथा
		dev_info(&pdev->dev, "Intel(R) 82576 Virtual Function\n");
	dev_info(&pdev->dev, "Address: %pM\n", netdev->dev_addr);
पूर्ण

अटल पूर्णांक igbvf_set_features(काष्ठा net_device *netdev,
			      netdev_features_t features)
अणु
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);

	अगर (features & NETIF_F_RXCSUM)
		adapter->flags &= ~IGBVF_FLAG_RX_CSUM_DISABLED;
	अन्यथा
		adapter->flags |= IGBVF_FLAG_RX_CSUM_DISABLED;

	वापस 0;
पूर्ण

#घोषणा IGBVF_MAX_MAC_HDR_LEN		127
#घोषणा IGBVF_MAX_NETWORK_HDR_LEN	511

अटल netdev_features_t
igbvf_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     netdev_features_t features)
अणु
	अचिन्हित पूर्णांक network_hdr_len, mac_hdr_len;

	/* Make certain the headers can be described by a context descriptor */
	mac_hdr_len = skb_network_header(skb) - skb->data;
	अगर (unlikely(mac_hdr_len > IGBVF_MAX_MAC_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	network_hdr_len = skb_checksum_start(skb) - skb_network_header(skb);
	अगर (unlikely(network_hdr_len >  IGBVF_MAX_NETWORK_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	/* We can only support IPV4 TSO in tunnels अगर we can mangle the
	 * inner IP ID field, so strip TSO अगर MANGLEID is not supported.
	 */
	अगर (skb->encapsulation && !(features & NETIF_F_TSO_MANGLEID))
		features &= ~NETIF_F_TSO;

	वापस features;
पूर्ण

अटल स्थिर काष्ठा net_device_ops igbvf_netdev_ops = अणु
	.nकरो_खोलो		= igbvf_खोलो,
	.nकरो_stop		= igbvf_बंद,
	.nकरो_start_xmit		= igbvf_xmit_frame,
	.nकरो_set_rx_mode	= igbvf_set_rx_mode,
	.nकरो_set_mac_address	= igbvf_set_mac,
	.nकरो_change_mtu		= igbvf_change_mtu,
	.nकरो_करो_ioctl		= igbvf_ioctl,
	.nकरो_tx_समयout		= igbvf_tx_समयout,
	.nकरो_vlan_rx_add_vid	= igbvf_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= igbvf_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= igbvf_netpoll,
#पूर्ण_अगर
	.nकरो_set_features	= igbvf_set_features,
	.nकरो_features_check	= igbvf_features_check,
पूर्ण;

/**
 * igbvf_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in igbvf_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * igbvf_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक igbvf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा igbvf_adapter *adapter;
	काष्ठा e1000_hw *hw;
	स्थिर काष्ठा igbvf_info *ei = igbvf_info_tbl[ent->driver_data];

	अटल पूर्णांक cards_found;
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

	err = pci_request_regions(pdev, igbvf_driver_name);
	अगर (err)
		जाओ err_pci_reg;

	pci_set_master(pdev);

	err = -ENOMEM;
	netdev = alloc_etherdev(माप(काष्ठा igbvf_adapter));
	अगर (!netdev)
		जाओ err_alloc_etherdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	hw = &adapter->hw;
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->ei = ei;
	adapter->pba = ei->pba;
	adapter->flags = ei->flags;
	adapter->hw.back = adapter;
	adapter->hw.mac.type = ei->mac;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	/* PCI config space info */

	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;
	hw->revision_id = pdev->revision;

	err = -EIO;
	adapter->hw.hw_addr = ioremap(pci_resource_start(pdev, 0),
				      pci_resource_len(pdev, 0));

	अगर (!adapter->hw.hw_addr)
		जाओ err_ioremap;

	अगर (ei->get_variants) अणु
		err = ei->get_variants(adapter);
		अगर (err)
			जाओ err_get_variants;
	पूर्ण

	/* setup adapter काष्ठा */
	err = igbvf_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	/* स्थिरruct the net_device काष्ठा */
	netdev->netdev_ops = &igbvf_netdev_ops;

	igbvf_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;
	म_नकलन(netdev->name, pci_name(pdev), माप(netdev->name) - 1);

	adapter->bd_number = cards_found++;

	netdev->hw_features = NETIF_F_SG |
			      NETIF_F_TSO |
			      NETIF_F_TSO6 |
			      NETIF_F_RXCSUM |
			      NETIF_F_HW_CSUM |
			      NETIF_F_SCTP_CRC;

#घोषणा IGBVF_GSO_PARTIAL_FEATURES (NETIF_F_GSO_GRE | \
				    NETIF_F_GSO_GRE_CSUM | \
				    NETIF_F_GSO_IPXIP4 | \
				    NETIF_F_GSO_IPXIP6 | \
				    NETIF_F_GSO_UDP_TUNNEL | \
				    NETIF_F_GSO_UDP_TUNNEL_CSUM)

	netdev->gso_partial_features = IGBVF_GSO_PARTIAL_FEATURES;
	netdev->hw_features |= NETIF_F_GSO_PARTIAL |
			       IGBVF_GSO_PARTIAL_FEATURES;

	netdev->features = netdev->hw_features;

	अगर (pci_using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->vlan_features |= netdev->features | NETIF_F_TSO_MANGLEID;
	netdev->mpls_features |= NETIF_F_HW_CSUM;
	netdev->hw_enc_features |= netdev->vlan_features;

	/* set this bit last since it cannot be part of vlan_features */
	netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER |
			    NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_TX;

	/* MTU range: 68 - 9216 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = MAX_STD_JUMBO_FRAME_SIZE;

	spin_lock_bh(&hw->mbx_lock);

	/*reset the controller to put the device in a known good state */
	err = hw->mac.ops.reset_hw(hw);
	अगर (err) अणु
		dev_info(&pdev->dev,
			 "PF still in reset state. Is the PF interface up?\n");
	पूर्ण अन्यथा अणु
		err = hw->mac.ops.पढ़ो_mac_addr(hw);
		अगर (err)
			dev_info(&pdev->dev, "Error reading MAC address.\n");
		अन्यथा अगर (is_zero_ether_addr(adapter->hw.mac.addr))
			dev_info(&pdev->dev,
				 "MAC address not assigned by administrator.\n");
		स_नकल(netdev->dev_addr, adapter->hw.mac.addr,
		       netdev->addr_len);
	पूर्ण

	spin_unlock_bh(&hw->mbx_lock);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		dev_info(&pdev->dev, "Assigning random MAC address.\n");
		eth_hw_addr_अक्रमom(netdev);
		स_नकल(adapter->hw.mac.addr, netdev->dev_addr,
		       netdev->addr_len);
	पूर्ण

	समयr_setup(&adapter->watchकरोg_समयr, igbvf_watchकरोg, 0);

	INIT_WORK(&adapter->reset_task, igbvf_reset_task);
	INIT_WORK(&adapter->watchकरोg_task, igbvf_watchकरोg_task);

	/* ring size शेषs */
	adapter->rx_ring->count = 1024;
	adapter->tx_ring->count = 1024;

	/* reset the hardware with the new settings */
	igbvf_reset(adapter);

	/* set hardware-specअगरic flags */
	अगर (adapter->hw.mac.type == e1000_vfadapt_i350)
		adapter->flags |= IGBVF_FLAG_RX_LB_VLAN_BSWAP;

	म_नकल(netdev->name, "eth%d");
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_hw_init;

	/* tell the stack to leave us alone until igbvf_खोलो() is called */
	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);

	igbvf_prपूर्णांक_device_info(adapter);

	igbvf_initialize_last_counter_stats(adapter);

	वापस 0;

err_hw_init:
	kमुक्त(adapter->tx_ring);
	kमुक्त(adapter->rx_ring);
err_sw_init:
	igbvf_reset_पूर्णांकerrupt_capability(adapter);
err_get_variants:
	iounmap(adapter->hw.hw_addr);
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * igbvf_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * igbvf_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम igbvf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा igbvf_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* The watchकरोg समयr may be rescheduled, so explicitly
	 * disable it from being rescheduled.
	 */
	set_bit(__IGBVF_DOWN, &adapter->state);
	del_समयr_sync(&adapter->watchकरोg_समयr);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchकरोg_task);

	unरेजिस्टर_netdev(netdev);

	igbvf_reset_पूर्णांकerrupt_capability(adapter);

	/* it is important to delete the NAPI काष्ठा prior to मुक्तing the
	 * Rx ring so that you करो not end up with null poपूर्णांकer refs
	 */
	netअगर_napi_del(&adapter->rx_ring->napi);
	kमुक्त(adapter->tx_ring);
	kमुक्त(adapter->rx_ring);

	iounmap(hw->hw_addr);
	अगर (hw->flash_address)
		iounmap(hw->flash_address);
	pci_release_regions(pdev);

	मुक्त_netdev(netdev);

	pci_disable_device(pdev);
पूर्ण

/* PCI Error Recovery (ERS) */
अटल स्थिर काष्ठा pci_error_handlers igbvf_err_handler = अणु
	.error_detected = igbvf_io_error_detected,
	.slot_reset = igbvf_io_slot_reset,
	.resume = igbvf_io_resume,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id igbvf_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82576_VF), board_vf पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_I350_VF), board_i350_vf पूर्ण,
	अणु पूर्ण /* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, igbvf_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(igbvf_pm_ops, igbvf_suspend, igbvf_resume);

/* PCI Device API Driver */
अटल काष्ठा pci_driver igbvf_driver = अणु
	.name		= igbvf_driver_name,
	.id_table	= igbvf_pci_tbl,
	.probe		= igbvf_probe,
	.हटाओ		= igbvf_हटाओ,
	.driver.pm	= &igbvf_pm_ops,
	.shutकरोwn	= igbvf_shutकरोwn,
	.err_handler	= &igbvf_err_handler
पूर्ण;

/**
 * igbvf_init_module - Driver Registration Routine
 *
 * igbvf_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init igbvf_init_module(व्योम)
अणु
	पूर्णांक ret;

	pr_info("%s\n", igbvf_driver_string);
	pr_info("%s\n", igbvf_copyright);

	ret = pci_रेजिस्टर_driver(&igbvf_driver);

	वापस ret;
पूर्ण
module_init(igbvf_init_module);

/**
 * igbvf_निकास_module - Driver Exit Cleanup Routine
 *
 * igbvf_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास igbvf_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&igbvf_driver);
पूर्ण
module_निकास(igbvf_निकास_module);

MODULE_AUTHOR("Intel Corporation, <e1000-devel@lists.sourceforge.net>");
MODULE_DESCRIPTION("Intel(R) Gigabit Virtual Function Network Driver");
MODULE_LICENSE("GPL v2");

/* netdev.c */
