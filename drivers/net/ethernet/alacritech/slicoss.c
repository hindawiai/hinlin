<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Gigabit Ethernet adapters based on the Session Layer
 * Interface (SLIC) technology by Alacritech. The driver करोes not
 * support the hardware acceleration features provided by these cards.
 *
 * Copyright (C) 2016 Lino Sanfilippo <LinoSanfilippo@gmx.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/crc32.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/list.h>
#समावेश <linux/u64_stats_sync.h>

#समावेश "slic.h"

#घोषणा DRV_NAME			"slicoss"

अटल स्थिर काष्ठा pci_device_id slic_id_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_ALACRITECH,
		     PCI_DEVICE_ID_ALACRITECH_MOJAVE) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ALACRITECH,
		     PCI_DEVICE_ID_ALACRITECH_OASIS) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल स्थिर अक्षर slic_stats_strings[][ETH_GSTRING_LEN] = अणु
	"rx_packets",
	"rx_bytes",
	"rx_multicasts",
	"rx_errors",
	"rx_buff_miss",
	"rx_tp_csum",
	"rx_tp_oflow",
	"rx_tp_hlen",
	"rx_ip_csum",
	"rx_ip_len",
	"rx_ip_hdr_len",
	"rx_early",
	"rx_buff_oflow",
	"rx_lcode",
	"rx_drbl",
	"rx_crc",
	"rx_oflow_802",
	"rx_uflow_802",
	"tx_packets",
	"tx_bytes",
	"tx_carrier",
	"tx_dropped",
	"irq_errs",
पूर्ण;

अटल अंतरभूत पूर्णांक slic_next_queue_idx(अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक qlen)
अणु
	वापस (idx + 1) & (qlen - 1);
पूर्ण

अटल अंतरभूत पूर्णांक slic_get_मुक्त_queue_descs(अचिन्हित पूर्णांक put_idx,
					    अचिन्हित पूर्णांक करोne_idx,
					    अचिन्हित पूर्णांक qlen)
अणु
	अगर (put_idx >= करोne_idx)
		वापस (qlen - (put_idx - करोne_idx) - 1);
	वापस (करोne_idx - put_idx - 1);
पूर्ण

अटल अचिन्हित पूर्णांक slic_next_compl_idx(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_stat_queue *stq = &sdev->stq;
	अचिन्हित पूर्णांक active = stq->active_array;
	काष्ठा slic_stat_desc *descs;
	काष्ठा slic_stat_desc *stat;
	अचिन्हित पूर्णांक idx;

	descs = stq->descs[active];
	stat = &descs[stq->करोne_idx];

	अगर (!stat->status)
		वापस SLIC_INVALID_STAT_DESC_IDX;

	idx = (le32_to_cpu(stat->hnd) & 0xffff) - 1;
	/* reset desc */
	stat->hnd = 0;
	stat->status = 0;

	stq->करोne_idx = slic_next_queue_idx(stq->करोne_idx, stq->len);
	/* check क्रम wraparound */
	अगर (!stq->करोne_idx) अणु
		dma_addr_t paddr = stq->paddr[active];

		slic_ग_लिखो(sdev, SLIC_REG_RBAR, lower_32_bits(paddr) |
						stq->len);
		/* make sure new status descriptors are immediately available */
		slic_flush_ग_लिखो(sdev);
		active++;
		active &= (SLIC_NUM_STAT_DESC_ARRAYS - 1);
		stq->active_array = active;
	पूर्ण
	वापस idx;
पूर्ण

अटल अचिन्हित पूर्णांक slic_get_मुक्त_tx_descs(काष्ठा slic_tx_queue *txq)
अणु
	/* ensure tail idx is updated */
	smp_mb();
	वापस slic_get_मुक्त_queue_descs(txq->put_idx, txq->करोne_idx, txq->len);
पूर्ण

अटल अचिन्हित पूर्णांक slic_get_मुक्त_rx_descs(काष्ठा slic_rx_queue *rxq)
अणु
	वापस slic_get_मुक्त_queue_descs(rxq->put_idx, rxq->करोne_idx, rxq->len);
पूर्ण

अटल व्योम slic_clear_upr_list(काष्ठा slic_upr_list *upr_list)
अणु
	काष्ठा slic_upr *upr;
	काष्ठा slic_upr *पंचांगp;

	spin_lock_bh(&upr_list->lock);
	list_क्रम_each_entry_safe(upr, पंचांगp, &upr_list->list, list) अणु
		list_del(&upr->list);
		kमुक्त(upr);
	पूर्ण
	upr_list->pending = false;
	spin_unlock_bh(&upr_list->lock);
पूर्ण

अटल व्योम slic_start_upr(काष्ठा slic_device *sdev, काष्ठा slic_upr *upr)
अणु
	u32 reg;

	reg = (upr->type == SLIC_UPR_CONFIG) ? SLIC_REG_RCONFIG :
					       SLIC_REG_LSTAT;
	slic_ग_लिखो(sdev, reg, lower_32_bits(upr->paddr));
	slic_flush_ग_लिखो(sdev);
पूर्ण

अटल व्योम slic_queue_upr(काष्ठा slic_device *sdev, काष्ठा slic_upr *upr)
अणु
	काष्ठा slic_upr_list *upr_list = &sdev->upr_list;
	bool pending;

	spin_lock_bh(&upr_list->lock);
	pending = upr_list->pending;
	INIT_LIST_HEAD(&upr->list);
	list_add_tail(&upr->list, &upr_list->list);
	upr_list->pending = true;
	spin_unlock_bh(&upr_list->lock);

	अगर (!pending)
		slic_start_upr(sdev, upr);
पूर्ण

अटल काष्ठा slic_upr *slic_dequeue_upr(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_upr_list *upr_list = &sdev->upr_list;
	काष्ठा slic_upr *next_upr = शून्य;
	काष्ठा slic_upr *upr = शून्य;

	spin_lock_bh(&upr_list->lock);
	अगर (!list_empty(&upr_list->list)) अणु
		upr = list_first_entry(&upr_list->list, काष्ठा slic_upr, list);
		list_del(&upr->list);

		अगर (list_empty(&upr_list->list))
			upr_list->pending = false;
		अन्यथा
			next_upr = list_first_entry(&upr_list->list,
						    काष्ठा slic_upr, list);
	पूर्ण
	spin_unlock_bh(&upr_list->lock);
	/* trigger processing of the next upr in list */
	अगर (next_upr)
		slic_start_upr(sdev, next_upr);

	वापस upr;
पूर्ण

अटल पूर्णांक slic_new_upr(काष्ठा slic_device *sdev, अचिन्हित पूर्णांक type,
			dma_addr_t paddr)
अणु
	काष्ठा slic_upr *upr;

	upr = kदो_स्मृति(माप(*upr), GFP_ATOMIC);
	अगर (!upr)
		वापस -ENOMEM;
	upr->type = type;
	upr->paddr = paddr;

	slic_queue_upr(sdev, upr);

	वापस 0;
पूर्ण

अटल व्योम slic_set_mcast_bit(u64 *mcmask, अचिन्हित अक्षर स्थिर *addr)
अणु
	u64 mask = *mcmask;
	u8 crc;
	/* Get the CRC polynomial क्रम the mac address: we use bits 1-8 (lsb),
	 * bitwise reversed, msb (= lsb bit 0 beक्रमe bitrev) is स्वतःmatically
	 * discarded.
	 */
	crc = ether_crc(ETH_ALEN, addr) >> 23;
	 /* we only have space on the SLIC क्रम 64 entries */
	crc &= 0x3F;
	mask |= (u64)1 << crc;
	*mcmask = mask;
पूर्ण

/* must be called with link_lock held */
अटल व्योम slic_configure_rcv(काष्ठा slic_device *sdev)
अणु
	u32 val;

	val = SLIC_GRCR_RESET | SLIC_GRCR_ADDRAEN | SLIC_GRCR_RCVEN |
	      SLIC_GRCR_HASHSIZE << SLIC_GRCR_HASHSIZE_SHIFT | SLIC_GRCR_RCVBAD;

	अगर (sdev->duplex == DUPLEX_FULL)
		val |= SLIC_GRCR_CTLEN;

	अगर (sdev->promisc)
		val |= SLIC_GRCR_RCVALL;

	slic_ग_लिखो(sdev, SLIC_REG_WRCFG, val);
पूर्ण

/* must be called with link_lock held */
अटल व्योम slic_configure_xmt(काष्ठा slic_device *sdev)
अणु
	u32 val;

	val = SLIC_GXCR_RESET | SLIC_GXCR_XMTEN;

	अगर (sdev->duplex == DUPLEX_FULL)
		val |= SLIC_GXCR_PAUSEEN;

	slic_ग_लिखो(sdev, SLIC_REG_WXCFG, val);
पूर्ण

/* must be called with link_lock held */
अटल व्योम slic_configure_mac(काष्ठा slic_device *sdev)
अणु
	u32 val;

	अगर (sdev->speed == SPEED_1000) अणु
		val = SLIC_GMCR_GAPBB_1000 << SLIC_GMCR_GAPBB_SHIFT |
		      SLIC_GMCR_GAPR1_1000 << SLIC_GMCR_GAPR1_SHIFT |
		      SLIC_GMCR_GAPR2_1000 << SLIC_GMCR_GAPR2_SHIFT |
		      SLIC_GMCR_GBIT; /* enable GMII */
	पूर्ण अन्यथा अणु
		val = SLIC_GMCR_GAPBB_100 << SLIC_GMCR_GAPBB_SHIFT |
		      SLIC_GMCR_GAPR1_100 << SLIC_GMCR_GAPR1_SHIFT |
		      SLIC_GMCR_GAPR2_100 << SLIC_GMCR_GAPR2_SHIFT;
	पूर्ण

	अगर (sdev->duplex == DUPLEX_FULL)
		val |= SLIC_GMCR_FULLD;

	slic_ग_लिखो(sdev, SLIC_REG_WMCFG, val);
पूर्ण

अटल व्योम slic_configure_link_locked(काष्ठा slic_device *sdev, पूर्णांक speed,
				       अचिन्हित पूर्णांक duplex)
अणु
	काष्ठा net_device *dev = sdev->netdev;

	अगर (sdev->speed == speed && sdev->duplex == duplex)
		वापस;

	sdev->speed = speed;
	sdev->duplex = duplex;

	अगर (sdev->speed == SPEED_UNKNOWN) अणु
		अगर (netअगर_carrier_ok(dev))
			netअगर_carrier_off(dev);
	पूर्ण अन्यथा अणु
		/* (re)configure link settings */
		slic_configure_mac(sdev);
		slic_configure_xmt(sdev);
		slic_configure_rcv(sdev);
		slic_flush_ग_लिखो(sdev);

		अगर (!netअगर_carrier_ok(dev))
			netअगर_carrier_on(dev);
	पूर्ण
पूर्ण

अटल व्योम slic_configure_link(काष्ठा slic_device *sdev, पूर्णांक speed,
				अचिन्हित पूर्णांक duplex)
अणु
	spin_lock_bh(&sdev->link_lock);
	slic_configure_link_locked(sdev, speed, duplex);
	spin_unlock_bh(&sdev->link_lock);
पूर्ण

अटल व्योम slic_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा slic_device *sdev = netdev_priv(dev);
	काष्ठा netdev_hw_addr *hwaddr;
	bool set_promisc;
	u64 mcmask;

	अगर (dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) अणु
		/* Turn on all multicast addresses. We have to करो this क्रम
		 * promiscuous mode as well as ALLMCAST mode (it saves the
		 * microcode from having to keep state about the MAC
		 * configuration).
		 */
		mcmask = ~(u64)0;
	पूर्ण अन्यथा  अणु
		mcmask = 0;

		netdev_क्रम_each_mc_addr(hwaddr, dev) अणु
			slic_set_mcast_bit(&mcmask, hwaddr->addr);
		पूर्ण
	पूर्ण

	slic_ग_लिखो(sdev, SLIC_REG_MCASTLOW, lower_32_bits(mcmask));
	slic_ग_लिखो(sdev, SLIC_REG_MCASTHIGH, upper_32_bits(mcmask));

	set_promisc = !!(dev->flags & IFF_PROMISC);

	spin_lock_bh(&sdev->link_lock);
	अगर (sdev->promisc != set_promisc) अणु
		sdev->promisc = set_promisc;
		slic_configure_rcv(sdev);
	पूर्ण
	spin_unlock_bh(&sdev->link_lock);
पूर्ण

अटल व्योम slic_xmit_complete(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_tx_queue *txq = &sdev->txq;
	काष्ठा net_device *dev = sdev->netdev;
	काष्ठा slic_tx_buffer *buff;
	अचिन्हित पूर्णांक frames = 0;
	अचिन्हित पूर्णांक bytes = 0;
	अचिन्हित पूर्णांक idx;

	/* Limit processing to SLIC_MAX_TX_COMPLETIONS frames to aव्योम that new
	 * completions during processing keeps the loop running endlessly.
	 */
	करो अणु
		idx = slic_next_compl_idx(sdev);
		अगर (idx == SLIC_INVALID_STAT_DESC_IDX)
			अवरोध;

		txq->करोne_idx = idx;
		buff = &txq->txbuffs[idx];

		अगर (unlikely(!buff->skb)) अणु
			netdev_warn(dev,
				    "no skb found for desc idx %i\n", idx);
			जारी;
		पूर्ण
		dma_unmap_single(&sdev->pdev->dev,
				 dma_unmap_addr(buff, map_addr),
				 dma_unmap_len(buff, map_len), DMA_TO_DEVICE);

		bytes += buff->skb->len;
		frames++;

		dev_kमुक्त_skb_any(buff->skb);
		buff->skb = शून्य;
	पूर्ण जबतक (frames < SLIC_MAX_TX_COMPLETIONS);
	/* make sure xmit sees the new value क्रम करोne_idx */
	smp_wmb();

	u64_stats_update_begin(&sdev->stats.syncp);
	sdev->stats.tx_bytes += bytes;
	sdev->stats.tx_packets += frames;
	u64_stats_update_end(&sdev->stats.syncp);

	netअगर_tx_lock(dev);
	अगर (netअगर_queue_stopped(dev) &&
	    (slic_get_मुक्त_tx_descs(txq) >= SLIC_MIN_TX_WAKEUP_DESCS))
		netअगर_wake_queue(dev);
	netअगर_tx_unlock(dev);
पूर्ण

अटल व्योम slic_refill_rx_queue(काष्ठा slic_device *sdev, gfp_t gfp)
अणु
	स्थिर अचिन्हित पूर्णांक ALIGN_MASK = SLIC_RX_BUFF_ALIGN - 1;
	अचिन्हित पूर्णांक maplen = SLIC_RX_BUFF_SIZE;
	काष्ठा slic_rx_queue *rxq = &sdev->rxq;
	काष्ठा net_device *dev = sdev->netdev;
	काष्ठा slic_rx_buffer *buff;
	काष्ठा slic_rx_desc *desc;
	अचिन्हित पूर्णांक misalign;
	अचिन्हित पूर्णांक offset;
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;

	जबतक (slic_get_मुक्त_rx_descs(rxq) > SLIC_MAX_REQ_RX_DESCS) अणु
		skb = alloc_skb(maplen + ALIGN_MASK, gfp);
		अगर (!skb)
			अवरोध;

		paddr = dma_map_single(&sdev->pdev->dev, skb->data, maplen,
				       DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&sdev->pdev->dev, paddr)) अणु
			netdev_err(dev, "mapping rx packet failed\n");
			/* drop skb */
			dev_kमुक्त_skb_any(skb);
			अवरोध;
		पूर्ण
		/* ensure head buffer descriptors are 256 byte aligned */
		offset = 0;
		misalign = paddr & ALIGN_MASK;
		अगर (misalign) अणु
			offset = SLIC_RX_BUFF_ALIGN - misalign;
			skb_reserve(skb, offset);
		पूर्ण
		/* the HW expects dma chunks क्रम descriptor + frame data */
		desc = (काष्ठा slic_rx_desc *)skb->data;
		/* temporarily sync descriptor क्रम CPU to clear status */
		dma_sync_single_क्रम_cpu(&sdev->pdev->dev, paddr,
					offset + माप(*desc),
					DMA_FROM_DEVICE);
		desc->status = 0;
		/* वापस it to HW again */
		dma_sync_single_क्रम_device(&sdev->pdev->dev, paddr,
					   offset + माप(*desc),
					   DMA_FROM_DEVICE);

		buff = &rxq->rxbuffs[rxq->put_idx];
		buff->skb = skb;
		dma_unmap_addr_set(buff, map_addr, paddr);
		dma_unmap_len_set(buff, map_len, maplen);
		buff->addr_offset = offset;
		/* complete ग_लिखो to descriptor beक्रमe it is handed to HW */
		wmb();
		/* head buffer descriptors are placed immediately beक्रमe skb */
		slic_ग_लिखो(sdev, SLIC_REG_HBAR, lower_32_bits(paddr) + offset);
		rxq->put_idx = slic_next_queue_idx(rxq->put_idx, rxq->len);
	पूर्ण
पूर्ण

अटल व्योम slic_handle_frame_error(काष्ठा slic_device *sdev,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा slic_stats *stats = &sdev->stats;

	अगर (sdev->model == SLIC_MODEL_OASIS) अणु
		काष्ठा slic_rx_info_oasis *info;
		u32 status_b;
		u32 status;

		info = (काष्ठा slic_rx_info_oasis *)skb->data;
		status = le32_to_cpu(info->frame_status);
		status_b = le32_to_cpu(info->frame_status_b);
		/* transport layer */
		अगर (status_b & SLIC_VRHSTATB_TPCSUM)
			SLIC_INC_STATS_COUNTER(stats, rx_tpcsum);
		अगर (status & SLIC_VRHSTAT_TPOFLO)
			SLIC_INC_STATS_COUNTER(stats, rx_tpoflow);
		अगर (status_b & SLIC_VRHSTATB_TPHLEN)
			SLIC_INC_STATS_COUNTER(stats, rx_tphlen);
		/* ip layer */
		अगर (status_b & SLIC_VRHSTATB_IPCSUM)
			SLIC_INC_STATS_COUNTER(stats, rx_ipcsum);
		अगर (status_b & SLIC_VRHSTATB_IPLERR)
			SLIC_INC_STATS_COUNTER(stats, rx_iplen);
		अगर (status_b & SLIC_VRHSTATB_IPHERR)
			SLIC_INC_STATS_COUNTER(stats, rx_iphlen);
		/* link layer */
		अगर (status_b & SLIC_VRHSTATB_RCVE)
			SLIC_INC_STATS_COUNTER(stats, rx_early);
		अगर (status_b & SLIC_VRHSTATB_BUFF)
			SLIC_INC_STATS_COUNTER(stats, rx_buffoflow);
		अगर (status_b & SLIC_VRHSTATB_CODE)
			SLIC_INC_STATS_COUNTER(stats, rx_lcode);
		अगर (status_b & SLIC_VRHSTATB_DRBL)
			SLIC_INC_STATS_COUNTER(stats, rx_drbl);
		अगर (status_b & SLIC_VRHSTATB_CRC)
			SLIC_INC_STATS_COUNTER(stats, rx_crc);
		अगर (status & SLIC_VRHSTAT_802OE)
			SLIC_INC_STATS_COUNTER(stats, rx_oflow802);
		अगर (status_b & SLIC_VRHSTATB_802UE)
			SLIC_INC_STATS_COUNTER(stats, rx_uflow802);
		अगर (status_b & SLIC_VRHSTATB_CARRE)
			SLIC_INC_STATS_COUNTER(stats, tx_carrier);
	पूर्ण अन्यथा अणु /* mojave */
		काष्ठा slic_rx_info_mojave *info;
		u32 status;

		info = (काष्ठा slic_rx_info_mojave *)skb->data;
		status = le32_to_cpu(info->frame_status);
		/* transport layer */
		अगर (status & SLIC_VGBSTAT_XPERR) अणु
			u32 xerr = status >> SLIC_VGBSTAT_XERRSHFT;

			अगर (xerr == SLIC_VGBSTAT_XCSERR)
				SLIC_INC_STATS_COUNTER(stats, rx_tpcsum);
			अगर (xerr == SLIC_VGBSTAT_XUFLOW)
				SLIC_INC_STATS_COUNTER(stats, rx_tpoflow);
			अगर (xerr == SLIC_VGBSTAT_XHLEN)
				SLIC_INC_STATS_COUNTER(stats, rx_tphlen);
		पूर्ण
		/* ip layer */
		अगर (status & SLIC_VGBSTAT_NETERR) अणु
			u32 nerr = status >> SLIC_VGBSTAT_NERRSHFT &
				   SLIC_VGBSTAT_NERRMSK;

			अगर (nerr == SLIC_VGBSTAT_NCSERR)
				SLIC_INC_STATS_COUNTER(stats, rx_ipcsum);
			अगर (nerr == SLIC_VGBSTAT_NUFLOW)
				SLIC_INC_STATS_COUNTER(stats, rx_iplen);
			अगर (nerr == SLIC_VGBSTAT_NHLEN)
				SLIC_INC_STATS_COUNTER(stats, rx_iphlen);
		पूर्ण
		/* link layer */
		अगर (status & SLIC_VGBSTAT_LNKERR) अणु
			u32 lerr = status & SLIC_VGBSTAT_LERRMSK;

			अगर (lerr == SLIC_VGBSTAT_LDEARLY)
				SLIC_INC_STATS_COUNTER(stats, rx_early);
			अगर (lerr == SLIC_VGBSTAT_LBOFLO)
				SLIC_INC_STATS_COUNTER(stats, rx_buffoflow);
			अगर (lerr == SLIC_VGBSTAT_LCODERR)
				SLIC_INC_STATS_COUNTER(stats, rx_lcode);
			अगर (lerr == SLIC_VGBSTAT_LDBLNBL)
				SLIC_INC_STATS_COUNTER(stats, rx_drbl);
			अगर (lerr == SLIC_VGBSTAT_LCRCERR)
				SLIC_INC_STATS_COUNTER(stats, rx_crc);
			अगर (lerr == SLIC_VGBSTAT_LOFLO)
				SLIC_INC_STATS_COUNTER(stats, rx_oflow802);
			अगर (lerr == SLIC_VGBSTAT_LUFLO)
				SLIC_INC_STATS_COUNTER(stats, rx_uflow802);
		पूर्ण
	पूर्ण
	SLIC_INC_STATS_COUNTER(stats, rx_errors);
पूर्ण

अटल व्योम slic_handle_receive(काष्ठा slic_device *sdev, अचिन्हित पूर्णांक toकरो,
				अचिन्हित पूर्णांक *करोne)
अणु
	काष्ठा slic_rx_queue *rxq = &sdev->rxq;
	काष्ठा net_device *dev = sdev->netdev;
	काष्ठा slic_rx_buffer *buff;
	काष्ठा slic_rx_desc *desc;
	अचिन्हित पूर्णांक frames = 0;
	अचिन्हित पूर्णांक bytes = 0;
	काष्ठा sk_buff *skb;
	u32 status;
	u32 len;

	जबतक (toकरो && (rxq->करोne_idx != rxq->put_idx)) अणु
		buff = &rxq->rxbuffs[rxq->करोne_idx];

		skb = buff->skb;
		अगर (!skb)
			अवरोध;

		desc = (काष्ठा slic_rx_desc *)skb->data;

		dma_sync_single_क्रम_cpu(&sdev->pdev->dev,
					dma_unmap_addr(buff, map_addr),
					buff->addr_offset + माप(*desc),
					DMA_FROM_DEVICE);

		status = le32_to_cpu(desc->status);
		अगर (!(status & SLIC_IRHDDR_SVALID)) अणु
			dma_sync_single_क्रम_device(&sdev->pdev->dev,
						   dma_unmap_addr(buff,
								  map_addr),
						   buff->addr_offset +
						   माप(*desc),
						   DMA_FROM_DEVICE);
			अवरोध;
		पूर्ण

		buff->skb = शून्य;

		dma_unmap_single(&sdev->pdev->dev,
				 dma_unmap_addr(buff, map_addr),
				 dma_unmap_len(buff, map_len),
				 DMA_FROM_DEVICE);

		/* skip rx descriptor that is placed beक्रमe the frame data */
		skb_reserve(skb, SLIC_RX_BUFF_HDR_SIZE);

		अगर (unlikely(status & SLIC_IRHDDR_ERR)) अणु
			slic_handle_frame_error(sdev, skb);
			dev_kमुक्त_skb_any(skb);
		पूर्ण अन्यथा अणु
			काष्ठा ethhdr *eh = (काष्ठा ethhdr *)skb->data;

			अगर (is_multicast_ether_addr(eh->h_dest))
				SLIC_INC_STATS_COUNTER(&sdev->stats, rx_mcasts);

			len = le32_to_cpu(desc->length) & SLIC_IRHDDR_FLEN_MSK;
			skb_put(skb, len);
			skb->protocol = eth_type_trans(skb, dev);
			skb->ip_summed = CHECKSUM_UNNECESSARY;

			napi_gro_receive(&sdev->napi, skb);

			bytes += len;
			frames++;
		पूर्ण
		rxq->करोne_idx = slic_next_queue_idx(rxq->करोne_idx, rxq->len);
		toकरो--;
	पूर्ण

	u64_stats_update_begin(&sdev->stats.syncp);
	sdev->stats.rx_bytes += bytes;
	sdev->stats.rx_packets += frames;
	u64_stats_update_end(&sdev->stats.syncp);

	slic_refill_rx_queue(sdev, GFP_ATOMIC);
पूर्ण

अटल व्योम slic_handle_link_irq(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_shmem *sm = &sdev->shmem;
	काष्ठा slic_shmem_data *sm_data = sm->shmem_data;
	अचिन्हित पूर्णांक duplex;
	पूर्णांक speed;
	u32 link;

	link = le32_to_cpu(sm_data->link);

	अगर (link & SLIC_GIG_LINKUP) अणु
		अगर (link & SLIC_GIG_SPEED_1000)
			speed = SPEED_1000;
		अन्यथा अगर (link & SLIC_GIG_SPEED_100)
			speed = SPEED_100;
		अन्यथा
			speed = SPEED_10;

		duplex = (link & SLIC_GIG_FULLDUPLEX) ? DUPLEX_FULL :
							DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		duplex = DUPLEX_UNKNOWN;
		speed = SPEED_UNKNOWN;
	पूर्ण
	slic_configure_link(sdev, speed, duplex);
पूर्ण

अटल व्योम slic_handle_upr_irq(काष्ठा slic_device *sdev, u32 irqs)
अणु
	काष्ठा slic_upr *upr;

	/* हटाओ upr that caused this irq (always the first entry in list) */
	upr = slic_dequeue_upr(sdev);
	अगर (!upr) अणु
		netdev_warn(sdev->netdev, "no upr found on list\n");
		वापस;
	पूर्ण

	अगर (upr->type == SLIC_UPR_LSTAT) अणु
		अगर (unlikely(irqs & SLIC_ISR_UPCERR_MASK)) अणु
			/* try again */
			slic_queue_upr(sdev, upr);
			वापस;
		पूर्ण
		slic_handle_link_irq(sdev);
	पूर्ण
	kमुक्त(upr);
पूर्ण

अटल पूर्णांक slic_handle_link_change(काष्ठा slic_device *sdev)
अणु
	वापस slic_new_upr(sdev, SLIC_UPR_LSTAT, sdev->shmem.link_paddr);
पूर्ण

अटल व्योम slic_handle_err_irq(काष्ठा slic_device *sdev, u32 isr)
अणु
	काष्ठा slic_stats *stats = &sdev->stats;

	अगर (isr & SLIC_ISR_RMISS)
		SLIC_INC_STATS_COUNTER(stats, rx_buff_miss);
	अगर (isr & SLIC_ISR_XDROP)
		SLIC_INC_STATS_COUNTER(stats, tx_dropped);
	अगर (!(isr & (SLIC_ISR_RMISS | SLIC_ISR_XDROP)))
		SLIC_INC_STATS_COUNTER(stats, irq_errs);
पूर्ण

अटल व्योम slic_handle_irq(काष्ठा slic_device *sdev, u32 isr,
			    अचिन्हित पूर्णांक toकरो, अचिन्हित पूर्णांक *करोne)
अणु
	अगर (isr & SLIC_ISR_ERR)
		slic_handle_err_irq(sdev, isr);

	अगर (isr & SLIC_ISR_LEVENT)
		slic_handle_link_change(sdev);

	अगर (isr & SLIC_ISR_UPC_MASK)
		slic_handle_upr_irq(sdev, isr);

	अगर (isr & SLIC_ISR_RCV)
		slic_handle_receive(sdev, toकरो, करोne);

	अगर (isr & SLIC_ISR_CMD)
		slic_xmit_complete(sdev);
पूर्ण

अटल पूर्णांक slic_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक toकरो)
अणु
	काष्ठा slic_device *sdev = container_of(napi, काष्ठा slic_device, napi);
	काष्ठा slic_shmem *sm = &sdev->shmem;
	काष्ठा slic_shmem_data *sm_data = sm->shmem_data;
	u32 isr = le32_to_cpu(sm_data->isr);
	पूर्णांक करोne = 0;

	slic_handle_irq(sdev, isr, toकरो, &करोne);

	अगर (करोne < toकरो) अणु
		napi_complete_करोne(napi, करोne);
		/* reenable irqs */
		sm_data->isr = 0;
		/* make sure sm_data->isr is cleard beक्रमe irqs are reenabled */
		wmb();
		slic_ग_लिखो(sdev, SLIC_REG_ISR, 0);
		slic_flush_ग_लिखो(sdev);
	पूर्ण

	वापस करोne;
पूर्ण

अटल irqवापस_t slic_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा slic_device *sdev = dev_id;
	काष्ठा slic_shmem *sm = &sdev->shmem;
	काष्ठा slic_shmem_data *sm_data = sm->shmem_data;

	slic_ग_लिखो(sdev, SLIC_REG_ICR, SLIC_ICR_INT_MASK);
	slic_flush_ग_लिखो(sdev);
	/* make sure sm_data->isr is पढ़ो after ICR_INT_MASK is set */
	wmb();

	अगर (!sm_data->isr) अणु
		dma_rmb();
		/* spurious पूर्णांकerrupt */
		slic_ग_लिखो(sdev, SLIC_REG_ISR, 0);
		slic_flush_ग_लिखो(sdev);
		वापस IRQ_NONE;
	पूर्ण

	napi_schedule_irqoff(&sdev->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम slic_card_reset(काष्ठा slic_device *sdev)
अणु
	u16 cmd;

	slic_ग_लिखो(sdev, SLIC_REG_RESET, SLIC_RESET_MAGIC);
	/* flush ग_लिखो by means of config space */
	pci_पढ़ो_config_word(sdev->pdev, PCI_COMMAND, &cmd);
	mdelay(1);
पूर्ण

अटल पूर्णांक slic_init_stat_queue(काष्ठा slic_device *sdev)
अणु
	स्थिर अचिन्हित पूर्णांक DESC_ALIGN_MASK = SLIC_STATS_DESC_ALIGN - 1;
	काष्ठा slic_stat_queue *stq = &sdev->stq;
	काष्ठा slic_stat_desc *descs;
	अचिन्हित पूर्णांक misalign;
	अचिन्हित पूर्णांक offset;
	dma_addr_t paddr;
	माप_प्रकार size;
	पूर्णांक err;
	पूर्णांक i;

	stq->len = SLIC_NUM_STAT_DESCS;
	stq->active_array = 0;
	stq->करोne_idx = 0;

	size = stq->len * माप(*descs) + DESC_ALIGN_MASK;

	क्रम (i = 0; i < SLIC_NUM_STAT_DESC_ARRAYS; i++) अणु
		descs = dma_alloc_coherent(&sdev->pdev->dev, size, &paddr,
					   GFP_KERNEL);
		अगर (!descs) अणु
			netdev_err(sdev->netdev,
				   "failed to allocate status descriptors\n");
			err = -ENOMEM;
			जाओ मुक्त_descs;
		पूर्ण
		/* ensure correct alignment */
		offset = 0;
		misalign = paddr & DESC_ALIGN_MASK;
		अगर (misalign) अणु
			offset = SLIC_STATS_DESC_ALIGN - misalign;
			descs += offset;
			paddr += offset;
		पूर्ण

		slic_ग_लिखो(sdev, SLIC_REG_RBAR, lower_32_bits(paddr) |
						stq->len);
		stq->descs[i] = descs;
		stq->paddr[i] = paddr;
		stq->addr_offset[i] = offset;
	पूर्ण

	stq->mem_size = size;

	वापस 0;

मुक्त_descs:
	जबतक (i--) अणु
		dma_मुक्त_coherent(&sdev->pdev->dev, stq->mem_size,
				  stq->descs[i] - stq->addr_offset[i],
				  stq->paddr[i] - stq->addr_offset[i]);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम slic_मुक्त_stat_queue(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_stat_queue *stq = &sdev->stq;
	पूर्णांक i;

	क्रम (i = 0; i < SLIC_NUM_STAT_DESC_ARRAYS; i++) अणु
		dma_मुक्त_coherent(&sdev->pdev->dev, stq->mem_size,
				  stq->descs[i] - stq->addr_offset[i],
				  stq->paddr[i] - stq->addr_offset[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक slic_init_tx_queue(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_tx_queue *txq = &sdev->txq;
	काष्ठा slic_tx_buffer *buff;
	काष्ठा slic_tx_desc *desc;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	txq->len = SLIC_NUM_TX_DESCS;
	txq->put_idx = 0;
	txq->करोne_idx = 0;

	txq->txbuffs = kसुस्मृति(txq->len, माप(*buff), GFP_KERNEL);
	अगर (!txq->txbuffs)
		वापस -ENOMEM;

	txq->dma_pool = dma_pool_create("slic_pool", &sdev->pdev->dev,
					माप(*desc), SLIC_TX_DESC_ALIGN,
					4096);
	अगर (!txq->dma_pool) अणु
		err = -ENOMEM;
		netdev_err(sdev->netdev, "failed to create dma pool\n");
		जाओ मुक्त_buffs;
	पूर्ण

	क्रम (i = 0; i < txq->len; i++) अणु
		buff = &txq->txbuffs[i];
		desc = dma_pool_zalloc(txq->dma_pool, GFP_KERNEL,
				       &buff->desc_paddr);
		अगर (!desc) अणु
			netdev_err(sdev->netdev,
				   "failed to alloc pool chunk (%i)\n", i);
			err = -ENOMEM;
			जाओ मुक्त_descs;
		पूर्ण

		desc->hnd = cpu_to_le32((u32)(i + 1));
		desc->cmd = SLIC_CMD_XMT_REQ;
		desc->flags = 0;
		desc->type = cpu_to_le32(SLIC_CMD_TYPE_DUMB);
		buff->desc = desc;
	पूर्ण

	वापस 0;

मुक्त_descs:
	जबतक (i--) अणु
		buff = &txq->txbuffs[i];
		dma_pool_मुक्त(txq->dma_pool, buff->desc, buff->desc_paddr);
	पूर्ण
	dma_pool_destroy(txq->dma_pool);

मुक्त_buffs:
	kमुक्त(txq->txbuffs);

	वापस err;
पूर्ण

अटल व्योम slic_मुक्त_tx_queue(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_tx_queue *txq = &sdev->txq;
	काष्ठा slic_tx_buffer *buff;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < txq->len; i++) अणु
		buff = &txq->txbuffs[i];
		dma_pool_मुक्त(txq->dma_pool, buff->desc, buff->desc_paddr);
		अगर (!buff->skb)
			जारी;

		dma_unmap_single(&sdev->pdev->dev,
				 dma_unmap_addr(buff, map_addr),
				 dma_unmap_len(buff, map_len), DMA_TO_DEVICE);
		consume_skb(buff->skb);
	पूर्ण
	dma_pool_destroy(txq->dma_pool);

	kमुक्त(txq->txbuffs);
पूर्ण

अटल पूर्णांक slic_init_rx_queue(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_rx_queue *rxq = &sdev->rxq;
	काष्ठा slic_rx_buffer *buff;

	rxq->len = SLIC_NUM_RX_LES;
	rxq->करोne_idx = 0;
	rxq->put_idx = 0;

	buff = kसुस्मृति(rxq->len, माप(*buff), GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	rxq->rxbuffs = buff;
	slic_refill_rx_queue(sdev, GFP_KERNEL);

	वापस 0;
पूर्ण

अटल व्योम slic_मुक्त_rx_queue(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_rx_queue *rxq = &sdev->rxq;
	काष्ठा slic_rx_buffer *buff;
	अचिन्हित पूर्णांक i;

	/* मुक्त rx buffers */
	क्रम (i = 0; i < rxq->len; i++) अणु
		buff = &rxq->rxbuffs[i];

		अगर (!buff->skb)
			जारी;

		dma_unmap_single(&sdev->pdev->dev,
				 dma_unmap_addr(buff, map_addr),
				 dma_unmap_len(buff, map_len),
				 DMA_FROM_DEVICE);
		consume_skb(buff->skb);
	पूर्ण
	kमुक्त(rxq->rxbuffs);
पूर्ण

अटल व्योम slic_set_link_स्वतःneg(काष्ठा slic_device *sdev)
अणु
	अचिन्हित पूर्णांक subid = sdev->pdev->subप्रणाली_device;
	u32 val;

	अगर (sdev->is_fiber) अणु
		/* We've got a fiber gigabit पूर्णांकerface, and रेजिस्टर 4 is
		 * dअगरferent in fiber mode than in copper mode.
		 */
		/* advertise FD only @1000 Mb */
		val = MII_ADVERTISE << 16 | ADVERTISE_1000XFULL |
		      ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM;
		/* enable PAUSE frames */
		slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);
		/* reset phy, enable स्वतः-neg  */
		val = MII_BMCR << 16 | BMCR_RESET | BMCR_ANENABLE |
		      BMCR_ANRESTART;
		slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);
	पूर्ण अन्यथा अणु	/* copper gigabit */
		/* We've got a copper gigabit पूर्णांकerface, and रेजिस्टर 4 is
		 * dअगरferent in copper mode than in fiber mode.
		 */
		/* advertise 10/100 Mb modes   */
		val = MII_ADVERTISE << 16 | ADVERTISE_100FULL |
		      ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF;
		/* enable PAUSE frames  */
		val |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		/* required by the Cicada PHY  */
		val |= ADVERTISE_CSMA;
		slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);

		/* advertise FD only @1000 Mb  */
		val = MII_CTRL1000 << 16 | ADVERTISE_1000FULL;
		slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);

		अगर (subid != PCI_SUBDEVICE_ID_ALACRITECH_CICADA) अणु
			 /* अगर a Marvell PHY enable स्वतः crossover */
			val = SLIC_MIICR_REG_16 | SLIC_MRV_REG16_XOVERON;
			slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);

			/* reset phy, enable स्वतः-neg  */
			val = MII_BMCR << 16 | BMCR_RESET | BMCR_ANENABLE |
			      BMCR_ANRESTART;
			slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);
		पूर्ण अन्यथा अणु
			/* enable and restart स्वतः-neg (करोn't reset)  */
			val = MII_BMCR << 16 | BMCR_ANENABLE | BMCR_ANRESTART;
			slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम slic_set_mac_address(काष्ठा slic_device *sdev)
अणु
	u8 *addr = sdev->netdev->dev_addr;
	u32 val;

	val = addr[5] | addr[4] << 8 | addr[3] << 16 | addr[2] << 24;

	slic_ग_लिखो(sdev, SLIC_REG_WRADDRAL, val);
	slic_ग_लिखो(sdev, SLIC_REG_WRADDRBL, val);

	val = addr[0] << 8 | addr[1];

	slic_ग_लिखो(sdev, SLIC_REG_WRADDRAH, val);
	slic_ग_लिखो(sdev, SLIC_REG_WRADDRBH, val);
	slic_flush_ग_लिखो(sdev);
पूर्ण

अटल u32 slic_पढ़ो_dword_from_firmware(स्थिर काष्ठा firmware *fw, पूर्णांक *offset)
अणु
	पूर्णांक idx = *offset;
	__le32 val;

	स_नकल(&val, fw->data + *offset, माप(val));
	idx += 4;
	*offset = idx;

	वापस le32_to_cpu(val);
पूर्ण

MODULE_FIRMWARE(SLIC_RCV_FIRMWARE_MOJAVE);
MODULE_FIRMWARE(SLIC_RCV_FIRMWARE_OASIS);

अटल पूर्णांक slic_load_rcvseq_firmware(काष्ठा slic_device *sdev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *file;
	u32 codelen;
	पूर्णांक idx = 0;
	u32 instr;
	u32 addr;
	पूर्णांक err;

	file = (sdev->model == SLIC_MODEL_OASIS) ?  SLIC_RCV_FIRMWARE_OASIS :
						    SLIC_RCV_FIRMWARE_MOJAVE;
	err = request_firmware(&fw, file, &sdev->pdev->dev);
	अगर (err) अणु
		dev_err(&sdev->pdev->dev,
			"failed to load receive sequencer firmware %s\n", file);
		वापस err;
	पूर्ण
	/* Do an initial sanity check concerning firmware size now. A further
	 * check follows below.
	 */
	अगर (fw->size < SLIC_FIRMWARE_MIN_SIZE) अणु
		dev_err(&sdev->pdev->dev,
			"invalid firmware size %zu (min %u expected)\n",
			fw->size, SLIC_FIRMWARE_MIN_SIZE);
		err = -EINVAL;
		जाओ release;
	पूर्ण

	codelen = slic_पढ़ो_dword_from_firmware(fw, &idx);

	/* करो another sanity check against firmware size */
	अगर ((codelen + 4) > fw->size) अणु
		dev_err(&sdev->pdev->dev,
			"invalid rcv-sequencer firmware size %zu\n", fw->size);
		err = -EINVAL;
		जाओ release;
	पूर्ण

	/* करोwnload sequencer code to card */
	slic_ग_लिखो(sdev, SLIC_REG_RCV_WCS, SLIC_RCVWCS_BEGIN);
	क्रम (addr = 0; addr < codelen; addr++) अणु
		__le32 val;
		/* ग_लिखो out inकाष्ठाion address */
		slic_ग_लिखो(sdev, SLIC_REG_RCV_WCS, addr);

		instr = slic_पढ़ो_dword_from_firmware(fw, &idx);
		/* ग_लिखो out the inकाष्ठाion data low addr */
		slic_ग_लिखो(sdev, SLIC_REG_RCV_WCS, instr);

		val = (__le32)fw->data[idx];
		instr = le32_to_cpu(val);
		idx++;
		/* ग_लिखो out the inकाष्ठाion data high addr */
		slic_ग_लिखो(sdev, SLIC_REG_RCV_WCS, instr);
	पूर्ण
	/* finish करोwnload */
	slic_ग_लिखो(sdev, SLIC_REG_RCV_WCS, SLIC_RCVWCS_FINISH);
	slic_flush_ग_लिखो(sdev);
release:
	release_firmware(fw);

	वापस err;
पूर्ण

MODULE_FIRMWARE(SLIC_FIRMWARE_MOJAVE);
MODULE_FIRMWARE(SLIC_FIRMWARE_OASIS);

अटल पूर्णांक slic_load_firmware(काष्ठा slic_device *sdev)
अणु
	u32 sectstart[SLIC_FIRMWARE_MAX_SECTIONS];
	u32 sectsize[SLIC_FIRMWARE_MAX_SECTIONS];
	स्थिर काष्ठा firmware *fw;
	अचिन्हित पूर्णांक datalen;
	स्थिर अक्षर *file;
	पूर्णांक code_start;
	अचिन्हित पूर्णांक i;
	u32 numsects;
	पूर्णांक idx = 0;
	u32 sect;
	u32 instr;
	u32 addr;
	u32 base;
	पूर्णांक err;

	file = (sdev->model == SLIC_MODEL_OASIS) ?  SLIC_FIRMWARE_OASIS :
						    SLIC_FIRMWARE_MOJAVE;
	err = request_firmware(&fw, file, &sdev->pdev->dev);
	अगर (err) अणु
		dev_err(&sdev->pdev->dev, "failed to load firmware %s\n", file);
		वापस err;
	पूर्ण
	/* Do an initial sanity check concerning firmware size now. A further
	 * check follows below.
	 */
	अगर (fw->size < SLIC_FIRMWARE_MIN_SIZE) अणु
		dev_err(&sdev->pdev->dev,
			"invalid firmware size %zu (min is %u)\n", fw->size,
			SLIC_FIRMWARE_MIN_SIZE);
		err = -EINVAL;
		जाओ release;
	पूर्ण

	numsects = slic_पढ़ो_dword_from_firmware(fw, &idx);
	अगर (numsects == 0 || numsects > SLIC_FIRMWARE_MAX_SECTIONS) अणु
		dev_err(&sdev->pdev->dev,
			"invalid number of sections in firmware: %u", numsects);
		err = -EINVAL;
		जाओ release;
	पूर्ण

	datalen = numsects * 8 + 4;
	क्रम (i = 0; i < numsects; i++) अणु
		sectsize[i] = slic_पढ़ो_dword_from_firmware(fw, &idx);
		datalen += sectsize[i];
	पूर्ण

	/* करो another sanity check against firmware size */
	अगर (datalen > fw->size) अणु
		dev_err(&sdev->pdev->dev,
			"invalid firmware size %zu (expected >= %u)\n",
			fw->size, datalen);
		err = -EINVAL;
		जाओ release;
	पूर्ण
	/* get sections */
	क्रम (i = 0; i < numsects; i++)
		sectstart[i] = slic_पढ़ो_dword_from_firmware(fw, &idx);

	code_start = idx;
	instr = slic_पढ़ो_dword_from_firmware(fw, &idx);

	क्रम (sect = 0; sect < numsects; sect++) अणु
		अचिन्हित पूर्णांक ssize = sectsize[sect] >> 3;

		base = sectstart[sect];

		क्रम (addr = 0; addr < ssize; addr++) अणु
			/* ग_लिखो out inकाष्ठाion address */
			slic_ग_लिखो(sdev, SLIC_REG_WCS, base + addr);
			/* ग_लिखो out inकाष्ठाion to low addr */
			slic_ग_लिखो(sdev, SLIC_REG_WCS, instr);
			instr = slic_पढ़ो_dword_from_firmware(fw, &idx);
			/* ग_लिखो out inकाष्ठाion to high addr */
			slic_ग_लिखो(sdev, SLIC_REG_WCS, instr);
			instr = slic_पढ़ो_dword_from_firmware(fw, &idx);
		पूर्ण
	पूर्ण

	idx = code_start;

	क्रम (sect = 0; sect < numsects; sect++) अणु
		अचिन्हित पूर्णांक ssize = sectsize[sect] >> 3;

		instr = slic_पढ़ो_dword_from_firmware(fw, &idx);
		base = sectstart[sect];
		अगर (base < 0x8000)
			जारी;

		क्रम (addr = 0; addr < ssize; addr++) अणु
			/* ग_लिखो out inकाष्ठाion address */
			slic_ग_लिखो(sdev, SLIC_REG_WCS,
				   SLIC_WCS_COMPARE | (base + addr));
			/* ग_लिखो out inकाष्ठाion to low addr */
			slic_ग_लिखो(sdev, SLIC_REG_WCS, instr);
			instr = slic_पढ़ो_dword_from_firmware(fw, &idx);
			/* ग_लिखो out inकाष्ठाion to high addr */
			slic_ग_लिखो(sdev, SLIC_REG_WCS, instr);
			instr = slic_पढ़ो_dword_from_firmware(fw, &idx);
		पूर्ण
	पूर्ण
	slic_flush_ग_लिखो(sdev);
	mdelay(10);
	/* everything OK, kick off the card */
	slic_ग_लिखो(sdev, SLIC_REG_WCS, SLIC_WCS_START);
	slic_flush_ग_लिखो(sdev);
	/* रुको दीर्घ enough क्रम ucode to init card and reach the मुख्यloop */
	mdelay(20);
release:
	release_firmware(fw);

	वापस err;
पूर्ण

अटल पूर्णांक slic_init_shmem(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_shmem *sm = &sdev->shmem;
	काष्ठा slic_shmem_data *sm_data;
	dma_addr_t paddr;

	sm_data = dma_alloc_coherent(&sdev->pdev->dev, माप(*sm_data),
				     &paddr, GFP_KERNEL);
	अगर (!sm_data) अणु
		dev_err(&sdev->pdev->dev, "failed to allocate shared memory\n");
		वापस -ENOMEM;
	पूर्ण

	sm->shmem_data = sm_data;
	sm->isr_paddr = paddr;
	sm->link_paddr = paddr + दुरत्व(काष्ठा slic_shmem_data, link);

	वापस 0;
पूर्ण

अटल व्योम slic_मुक्त_shmem(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_shmem *sm = &sdev->shmem;
	काष्ठा slic_shmem_data *sm_data = sm->shmem_data;

	dma_मुक्त_coherent(&sdev->pdev->dev, माप(*sm_data), sm_data,
			  sm->isr_paddr);
पूर्ण

अटल पूर्णांक slic_init_अगरace(काष्ठा slic_device *sdev)
अणु
	काष्ठा slic_shmem *sm = &sdev->shmem;
	पूर्णांक err;

	sdev->upr_list.pending = false;

	err = slic_init_shmem(sdev);
	अगर (err) अणु
		netdev_err(sdev->netdev, "failed to init shared memory\n");
		वापस err;
	पूर्ण

	err = slic_load_firmware(sdev);
	अगर (err) अणु
		netdev_err(sdev->netdev, "failed to load firmware\n");
		जाओ मुक्त_sm;
	पूर्ण

	err = slic_load_rcvseq_firmware(sdev);
	अगर (err) अणु
		netdev_err(sdev->netdev,
			   "failed to load firmware for receive sequencer\n");
		जाओ मुक्त_sm;
	पूर्ण

	slic_ग_लिखो(sdev, SLIC_REG_ICR, SLIC_ICR_INT_OFF);
	slic_flush_ग_लिखो(sdev);
	mdelay(1);

	err = slic_init_rx_queue(sdev);
	अगर (err) अणु
		netdev_err(sdev->netdev, "failed to init rx queue: %u\n", err);
		जाओ मुक्त_sm;
	पूर्ण

	err = slic_init_tx_queue(sdev);
	अगर (err) अणु
		netdev_err(sdev->netdev, "failed to init tx queue: %u\n", err);
		जाओ मुक्त_rxq;
	पूर्ण

	err = slic_init_stat_queue(sdev);
	अगर (err) अणु
		netdev_err(sdev->netdev, "failed to init status queue: %u\n",
			   err);
		जाओ मुक्त_txq;
	पूर्ण

	slic_ग_लिखो(sdev, SLIC_REG_ISP, lower_32_bits(sm->isr_paddr));
	napi_enable(&sdev->napi);
	/* disable irq mitigation */
	slic_ग_लिखो(sdev, SLIC_REG_INTAGG, 0);
	slic_ग_लिखो(sdev, SLIC_REG_ISR, 0);
	slic_flush_ग_लिखो(sdev);

	slic_set_mac_address(sdev);

	spin_lock_bh(&sdev->link_lock);
	sdev->duplex = DUPLEX_UNKNOWN;
	sdev->speed = SPEED_UNKNOWN;
	spin_unlock_bh(&sdev->link_lock);

	slic_set_link_स्वतःneg(sdev);

	err = request_irq(sdev->pdev->irq, slic_irq, IRQF_SHARED, DRV_NAME,
			  sdev);
	अगर (err) अणु
		netdev_err(sdev->netdev, "failed to request irq: %u\n", err);
		जाओ disable_napi;
	पूर्ण

	slic_ग_लिखो(sdev, SLIC_REG_ICR, SLIC_ICR_INT_ON);
	slic_flush_ग_लिखो(sdev);
	/* request initial link status */
	err = slic_handle_link_change(sdev);
	अगर (err)
		netdev_warn(sdev->netdev,
			    "failed to set initial link state: %u\n", err);
	वापस 0;

disable_napi:
	napi_disable(&sdev->napi);
	slic_मुक्त_stat_queue(sdev);
मुक्त_txq:
	slic_मुक्त_tx_queue(sdev);
मुक्त_rxq:
	slic_मुक्त_rx_queue(sdev);
मुक्त_sm:
	slic_मुक्त_shmem(sdev);
	slic_card_reset(sdev);

	वापस err;
पूर्ण

अटल पूर्णांक slic_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा slic_device *sdev = netdev_priv(dev);
	पूर्णांक err;

	netअगर_carrier_off(dev);

	err = slic_init_अगरace(sdev);
	अगर (err) अणु
		netdev_err(dev, "failed to initialize interface: %i\n", err);
		वापस err;
	पूर्ण

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक slic_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा slic_device *sdev = netdev_priv(dev);
	u32 val;

	netअगर_stop_queue(dev);

	/* stop irq handling */
	napi_disable(&sdev->napi);
	slic_ग_लिखो(sdev, SLIC_REG_ICR, SLIC_ICR_INT_OFF);
	slic_ग_लिखो(sdev, SLIC_REG_ISR, 0);
	slic_flush_ग_लिखो(sdev);

	मुक्त_irq(sdev->pdev->irq, sdev);
	/* turn off RCV and XMT and घातer करोwn PHY */
	val = SLIC_GXCR_RESET | SLIC_GXCR_PAUSEEN;
	slic_ग_लिखो(sdev, SLIC_REG_WXCFG, val);

	val = SLIC_GRCR_RESET | SLIC_GRCR_CTLEN | SLIC_GRCR_ADDRAEN |
	      SLIC_GRCR_HASHSIZE << SLIC_GRCR_HASHSIZE_SHIFT;
	slic_ग_लिखो(sdev, SLIC_REG_WRCFG, val);

	val = MII_BMCR << 16 | BMCR_PDOWN;
	slic_ग_लिखो(sdev, SLIC_REG_WPHY, val);
	slic_flush_ग_लिखो(sdev);

	slic_clear_upr_list(&sdev->upr_list);
	slic_ग_लिखो(sdev, SLIC_REG_QUIESCE, 0);

	slic_मुक्त_stat_queue(sdev);
	slic_मुक्त_tx_queue(sdev);
	slic_मुक्त_rx_queue(sdev);
	slic_मुक्त_shmem(sdev);

	slic_card_reset(sdev);
	netअगर_carrier_off(dev);

	वापस 0;
पूर्ण

अटल netdev_tx_t slic_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा slic_device *sdev = netdev_priv(dev);
	काष्ठा slic_tx_queue *txq = &sdev->txq;
	काष्ठा slic_tx_buffer *buff;
	काष्ठा slic_tx_desc *desc;
	dma_addr_t paddr;
	u32 cbar_val;
	u32 maplen;

	अगर (unlikely(slic_get_मुक्त_tx_descs(txq) < SLIC_MAX_REQ_TX_DESCS)) अणु
		netdev_err(dev, "BUG! not enough tx LEs left: %u\n",
			   slic_get_मुक्त_tx_descs(txq));
		वापस NETDEV_TX_BUSY;
	पूर्ण

	maplen = skb_headlen(skb);
	paddr = dma_map_single(&sdev->pdev->dev, skb->data, maplen,
			       DMA_TO_DEVICE);
	अगर (dma_mapping_error(&sdev->pdev->dev, paddr)) अणु
		netdev_err(dev, "failed to map tx buffer\n");
		जाओ drop_skb;
	पूर्ण

	buff = &txq->txbuffs[txq->put_idx];
	buff->skb = skb;
	dma_unmap_addr_set(buff, map_addr, paddr);
	dma_unmap_len_set(buff, map_len, maplen);

	desc = buff->desc;
	desc->totlen = cpu_to_le32(maplen);
	desc->paddrl = cpu_to_le32(lower_32_bits(paddr));
	desc->paddrh = cpu_to_le32(upper_32_bits(paddr));
	desc->len = cpu_to_le32(maplen);

	txq->put_idx = slic_next_queue_idx(txq->put_idx, txq->len);

	cbar_val = lower_32_bits(buff->desc_paddr) | 1;
	/* complete ग_लिखोs to RAM and DMA beक्रमe hardware is inक्रमmed */
	wmb();

	slic_ग_लिखो(sdev, SLIC_REG_CBAR, cbar_val);

	अगर (slic_get_मुक्त_tx_descs(txq) < SLIC_MAX_REQ_TX_DESCS)
		netअगर_stop_queue(dev);

	वापस NETDEV_TX_OK;
drop_skb:
	dev_kमुक्त_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम slic_get_stats(काष्ठा net_device *dev,
			   काष्ठा rtnl_link_stats64 *lst)
अणु
	काष्ठा slic_device *sdev = netdev_priv(dev);
	काष्ठा slic_stats *stats = &sdev->stats;

	SLIC_GET_STATS_COUNTER(lst->rx_packets, stats, rx_packets);
	SLIC_GET_STATS_COUNTER(lst->tx_packets, stats, tx_packets);
	SLIC_GET_STATS_COUNTER(lst->rx_bytes, stats, rx_bytes);
	SLIC_GET_STATS_COUNTER(lst->tx_bytes, stats, tx_bytes);
	SLIC_GET_STATS_COUNTER(lst->rx_errors, stats, rx_errors);
	SLIC_GET_STATS_COUNTER(lst->rx_dropped, stats, rx_buff_miss);
	SLIC_GET_STATS_COUNTER(lst->tx_dropped, stats, tx_dropped);
	SLIC_GET_STATS_COUNTER(lst->multicast, stats, rx_mcasts);
	SLIC_GET_STATS_COUNTER(lst->rx_over_errors, stats, rx_buffoflow);
	SLIC_GET_STATS_COUNTER(lst->rx_crc_errors, stats, rx_crc);
	SLIC_GET_STATS_COUNTER(lst->rx_fअगरo_errors, stats, rx_oflow802);
	SLIC_GET_STATS_COUNTER(lst->tx_carrier_errors, stats, tx_carrier);
पूर्ण

अटल पूर्णांक slic_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(slic_stats_strings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम slic_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *eth_stats, u64 *data)
अणु
	काष्ठा slic_device *sdev = netdev_priv(dev);
	काष्ठा slic_stats *stats = &sdev->stats;

	SLIC_GET_STATS_COUNTER(data[0], stats, rx_packets);
	SLIC_GET_STATS_COUNTER(data[1], stats, rx_bytes);
	SLIC_GET_STATS_COUNTER(data[2], stats, rx_mcasts);
	SLIC_GET_STATS_COUNTER(data[3], stats, rx_errors);
	SLIC_GET_STATS_COUNTER(data[4], stats, rx_buff_miss);
	SLIC_GET_STATS_COUNTER(data[5], stats, rx_tpcsum);
	SLIC_GET_STATS_COUNTER(data[6], stats, rx_tpoflow);
	SLIC_GET_STATS_COUNTER(data[7], stats, rx_tphlen);
	SLIC_GET_STATS_COUNTER(data[8], stats, rx_ipcsum);
	SLIC_GET_STATS_COUNTER(data[9], stats, rx_iplen);
	SLIC_GET_STATS_COUNTER(data[10], stats, rx_iphlen);
	SLIC_GET_STATS_COUNTER(data[11], stats, rx_early);
	SLIC_GET_STATS_COUNTER(data[12], stats, rx_buffoflow);
	SLIC_GET_STATS_COUNTER(data[13], stats, rx_lcode);
	SLIC_GET_STATS_COUNTER(data[14], stats, rx_drbl);
	SLIC_GET_STATS_COUNTER(data[15], stats, rx_crc);
	SLIC_GET_STATS_COUNTER(data[16], stats, rx_oflow802);
	SLIC_GET_STATS_COUNTER(data[17], stats, rx_uflow802);
	SLIC_GET_STATS_COUNTER(data[18], stats, tx_packets);
	SLIC_GET_STATS_COUNTER(data[19], stats, tx_bytes);
	SLIC_GET_STATS_COUNTER(data[20], stats, tx_carrier);
	SLIC_GET_STATS_COUNTER(data[21], stats, tx_dropped);
	SLIC_GET_STATS_COUNTER(data[22], stats, irq_errs);
पूर्ण

अटल व्योम slic_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS) अणु
		स_नकल(data, slic_stats_strings, माप(slic_stats_strings));
		data += माप(slic_stats_strings);
	पूर्ण
पूर्ण

अटल व्योम slic_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा slic_device *sdev = netdev_priv(dev);

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(sdev->pdev), माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops slic_ethtool_ops = अणु
	.get_drvinfo		= slic_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_strings		= slic_get_strings,
	.get_ethtool_stats	= slic_get_ethtool_stats,
	.get_sset_count		= slic_get_sset_count,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops slic_netdev_ops = अणु
	.nकरो_खोलो		= slic_खोलो,
	.nकरो_stop		= slic_बंद,
	.nकरो_start_xmit		= slic_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_get_stats64	= slic_get_stats,
	.nकरो_set_rx_mode	= slic_set_rx_mode,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल u16 slic_eeprom_csum(अचिन्हित अक्षर *eeprom, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *ptr = eeprom;
	u32 csum = 0;
	__le16 data;

	जबतक (len > 1) अणु
		स_नकल(&data, ptr, माप(data));
		csum += le16_to_cpu(data);
		ptr += 2;
		len -= 2;
	पूर्ण
	अगर (len > 0)
		csum += *(u8 *)ptr;
	जबतक (csum >> 16)
		csum = (csum & 0xFFFF) + ((csum >> 16) & 0xFFFF);
	वापस ~csum;
पूर्ण

/* check eeprom size, magic and checksum */
अटल bool slic_eeprom_valid(अचिन्हित अक्षर *eeprom, अचिन्हित पूर्णांक size)
अणु
	स्थिर अचिन्हित पूर्णांक MAX_SIZE = 128;
	स्थिर अचिन्हित पूर्णांक MIN_SIZE = 98;
	__le16 magic;
	__le16 csum;

	अगर (size < MIN_SIZE || size > MAX_SIZE)
		वापस false;
	स_नकल(&magic, eeprom, माप(magic));
	अगर (le16_to_cpu(magic) != SLIC_EEPROM_MAGIC)
		वापस false;
	/* cut checksum bytes */
	size -= 2;
	स_नकल(&csum, eeprom + size, माप(csum));

	वापस (le16_to_cpu(csum) == slic_eeprom_csum(eeprom, size));
पूर्ण

अटल पूर्णांक slic_पढ़ो_eeprom(काष्ठा slic_device *sdev)
अणु
	अचिन्हित पूर्णांक devfn = PCI_FUNC(sdev->pdev->devfn);
	काष्ठा slic_shmem *sm = &sdev->shmem;
	काष्ठा slic_shmem_data *sm_data = sm->shmem_data;
	स्थिर अचिन्हित पूर्णांक MAX_LOOPS = 5000;
	अचिन्हित पूर्णांक codesize;
	अचिन्हित अक्षर *eeprom;
	काष्ठा slic_upr *upr;
	अचिन्हित पूर्णांक i = 0;
	dma_addr_t paddr;
	पूर्णांक err = 0;
	u8 *mac[2];

	eeprom = dma_alloc_coherent(&sdev->pdev->dev, SLIC_EEPROM_SIZE,
				    &paddr, GFP_KERNEL);
	अगर (!eeprom)
		वापस -ENOMEM;

	slic_ग_लिखो(sdev, SLIC_REG_ICR, SLIC_ICR_INT_OFF);
	/* setup ISP temporarily */
	slic_ग_लिखो(sdev, SLIC_REG_ISP, lower_32_bits(sm->isr_paddr));

	err = slic_new_upr(sdev, SLIC_UPR_CONFIG, paddr);
	अगर (!err) अणु
		क्रम (i = 0; i < MAX_LOOPS; i++) अणु
			अगर (le32_to_cpu(sm_data->isr) & SLIC_ISR_UPC)
				अवरोध;
			mdelay(1);
		पूर्ण
		अगर (i == MAX_LOOPS) अणु
			dev_err(&sdev->pdev->dev,
				"timed out while waiting for eeprom data\n");
			err = -ETIMEDOUT;
		पूर्ण
		upr = slic_dequeue_upr(sdev);
		kमुक्त(upr);
	पूर्ण

	slic_ग_लिखो(sdev, SLIC_REG_ISP, 0);
	slic_ग_लिखो(sdev, SLIC_REG_ISR, 0);
	slic_flush_ग_लिखो(sdev);

	अगर (err)
		जाओ मुक्त_eeprom;

	अगर (sdev->model == SLIC_MODEL_OASIS) अणु
		काष्ठा slic_oasis_eeprom *oee;

		oee = (काष्ठा slic_oasis_eeprom *)eeprom;
		mac[0] = oee->mac;
		mac[1] = oee->mac2;
		codesize = le16_to_cpu(oee->eeprom_code_size);
	पूर्ण अन्यथा अणु
		काष्ठा slic_mojave_eeprom *mee;

		mee = (काष्ठा slic_mojave_eeprom *)eeprom;
		mac[0] = mee->mac;
		mac[1] = mee->mac2;
		codesize = le16_to_cpu(mee->eeprom_code_size);
	पूर्ण

	अगर (!slic_eeprom_valid(eeprom, codesize)) अणु
		dev_err(&sdev->pdev->dev, "invalid checksum in eeprom\n");
		err = -EINVAL;
		जाओ मुक्त_eeprom;
	पूर्ण
	/* set mac address */
	ether_addr_copy(sdev->netdev->dev_addr, mac[devfn]);
मुक्त_eeprom:
	dma_मुक्त_coherent(&sdev->pdev->dev, SLIC_EEPROM_SIZE, eeprom, paddr);

	वापस err;
पूर्ण

अटल पूर्णांक slic_init(काष्ठा slic_device *sdev)
अणु
	पूर्णांक err;

	spin_lock_init(&sdev->upper_lock);
	spin_lock_init(&sdev->link_lock);
	INIT_LIST_HEAD(&sdev->upr_list.list);
	spin_lock_init(&sdev->upr_list.lock);
	u64_stats_init(&sdev->stats.syncp);

	slic_card_reset(sdev);

	err = slic_load_firmware(sdev);
	अगर (err) अणु
		dev_err(&sdev->pdev->dev, "failed to load firmware\n");
		वापस err;
	पूर्ण

	/* we need the shared memory to पढ़ो EEPROM so set it up temporarily */
	err = slic_init_shmem(sdev);
	अगर (err) अणु
		dev_err(&sdev->pdev->dev, "failed to init shared memory\n");
		वापस err;
	पूर्ण

	err = slic_पढ़ो_eeprom(sdev);
	अगर (err) अणु
		dev_err(&sdev->pdev->dev, "failed to read eeprom\n");
		जाओ मुक्त_sm;
	पूर्ण

	slic_card_reset(sdev);
	slic_मुक्त_shmem(sdev);

	वापस 0;
मुक्त_sm:
	slic_मुक्त_shmem(sdev);

	वापस err;
पूर्ण

अटल bool slic_is_fiber(अचिन्हित लघु subdev)
अणु
	चयन (subdev) अणु
	/* Mojave */
	हाल PCI_SUBDEVICE_ID_ALACRITECH_1000X1F:
	हाल PCI_SUBDEVICE_ID_ALACRITECH_SES1001F: fallthrough;
	/* Oasis */
	हाल PCI_SUBDEVICE_ID_ALACRITECH_SEN2002XF:
	हाल PCI_SUBDEVICE_ID_ALACRITECH_SEN2001XF:
	हाल PCI_SUBDEVICE_ID_ALACRITECH_SEN2104EF:
	हाल PCI_SUBDEVICE_ID_ALACRITECH_SEN2102EF:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम slic_configure_pci(काष्ठा pci_dev *pdev)
अणु
	u16 old;
	u16 cmd;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &old);

	cmd = old | PCI_COMMAND_PARITY | PCI_COMMAND_SERR;
	अगर (old != cmd)
		pci_ग_लिखो_config_word(pdev, PCI_COMMAND, cmd);
पूर्ण

अटल पूर्णांक slic_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा slic_device *sdev;
	काष्ठा net_device *dev;
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable PCI device\n");
		वापस err;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	slic_configure_pci(pdev);

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to setup DMA\n");
		जाओ disable;
	पूर्ण

	dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to obtain PCI regions\n");
		जाओ disable;
	पूर्ण

	dev = alloc_etherdev(माप(*sdev));
	अगर (!dev) अणु
		dev_err(&pdev->dev, "failed to alloc ethernet device\n");
		err = -ENOMEM;
		जाओ मुक्त_regions;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);
	pci_set_drvdata(pdev, dev);
	dev->irq = pdev->irq;
	dev->netdev_ops = &slic_netdev_ops;
	dev->hw_features = NETIF_F_RXCSUM;
	dev->features |= dev->hw_features;

	dev->ethtool_ops = &slic_ethtool_ops;

	sdev = netdev_priv(dev);
	sdev->model = (pdev->device == PCI_DEVICE_ID_ALACRITECH_OASIS) ?
		      SLIC_MODEL_OASIS : SLIC_MODEL_MOJAVE;
	sdev->is_fiber = slic_is_fiber(pdev->subप्रणाली_device);
	sdev->pdev = pdev;
	sdev->netdev = dev;
	sdev->regs = ioremap(pci_resource_start(pdev, 0),
				     pci_resource_len(pdev, 0));
	अगर (!sdev->regs) अणु
		dev_err(&pdev->dev, "failed to map registers\n");
		err = -ENOMEM;
		जाओ मुक्त_netdev;
	पूर्ण

	err = slic_init(sdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to initialize driver\n");
		जाओ unmap;
	पूर्ण

	netअगर_napi_add(dev, &sdev->napi, slic_poll, SLIC_NAPI_WEIGHT);
	netअगर_carrier_off(dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register net device: %i\n", err);
		जाओ unmap;
	पूर्ण

	वापस 0;

unmap:
	iounmap(sdev->regs);
मुक्त_netdev:
	मुक्त_netdev(dev);
मुक्त_regions:
	pci_release_regions(pdev);
disable:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम slic_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा slic_device *sdev = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	iounmap(sdev->regs);
	मुक्त_netdev(dev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver slic_driver = अणु
	.name = DRV_NAME,
	.id_table = slic_id_tbl,
	.probe = slic_probe,
	.हटाओ = slic_हटाओ,
पूर्ण;

module_pci_driver(slic_driver);

MODULE_DESCRIPTION("Alacritech non-accelerated SLIC driver");
MODULE_AUTHOR("Lino Sanfilippo <LinoSanfilippo@gmx.de>");
MODULE_LICENSE("GPL");
