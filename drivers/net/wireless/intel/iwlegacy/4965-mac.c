<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portions of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/units.h>

#समावेश <net/mac80211.h>

#समावेश <यंत्र/भाग64.h>

#घोषणा DRV_NAME        "iwl4965"

#समावेश "common.h"
#समावेश "4965.h"

/******************************************************************************
 *
 * module boiler plate
 *
 ******************************************************************************/

/*
 * module name, copyright, version, etc.
 */
#घोषणा DRV_DESCRIPTION	"Intel(R) Wireless WiFi 4965 driver for Linux"

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
#घोषणा VD "d"
#अन्यथा
#घोषणा VD
#पूर्ण_अगर

#घोषणा DRV_VERSION     IWLWIFI_VERSION VD

MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR(DRV_COPYRIGHT " " DRV_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_ALIAS("iwl4965");

व्योम
il4965_check_पात_status(काष्ठा il_priv *il, u8 frame_count, u32 status)
अणु
	अगर (frame_count == 1 && status == TX_STATUS_FAIL_RFKILL_FLUSH) अणु
		IL_ERR("Tx flush command to flush out all frames\n");
		अगर (!test_bit(S_EXIT_PENDING, &il->status))
			queue_work(il->workqueue, &il->tx_flush);
	पूर्ण
पूर्ण

/*
 * EEPROM
 */
काष्ठा il_mod_params il4965_mod_params = अणु
	.restart_fw = 1,
	/* the rest are 0 by शेष */
पूर्ण;

व्योम
il4965_rx_queue_reset(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	spin_lock_irqsave(&rxq->lock, flags);
	INIT_LIST_HEAD(&rxq->rx_मुक्त);
	INIT_LIST_HEAD(&rxq->rx_used);
	/* Fill the rx_used queue with _all_ of the Rx buffers */
	क्रम (i = 0; i < RX_FREE_BUFFERS + RX_QUEUE_SIZE; i++) अणु
		/* In the reset function, these buffers may have been allocated
		 * to an SKB, so we need to unmap and मुक्त potential storage */
		अगर (rxq->pool[i].page != शून्य) अणु
			pci_unmap_page(il->pci_dev, rxq->pool[i].page_dma,
				       PAGE_SIZE << il->hw_params.rx_page_order,
				       PCI_DMA_FROMDEVICE);
			__il_मुक्त_pages(il, rxq->pool[i].page);
			rxq->pool[i].page = शून्य;
		पूर्ण
		list_add_tail(&rxq->pool[i].list, &rxq->rx_used);
	पूर्ण

	क्रम (i = 0; i < RX_QUEUE_SIZE; i++)
		rxq->queue[i] = शून्य;

	/* Set us so that we have processed and used all buffers, but have
	 * not restocked the Rx queue with fresh buffers */
	rxq->पढ़ो = rxq->ग_लिखो = 0;
	rxq->ग_लिखो_actual = 0;
	rxq->मुक्त_count = 0;
	spin_unlock_irqrestore(&rxq->lock, flags);
पूर्ण

पूर्णांक
il4965_rx_init(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq)
अणु
	u32 rb_size;
	स्थिर u32 rfdnlog = RX_QUEUE_SIZE_LOG;	/* 256 RBDs */
	u32 rb_समयout = 0;

	अगर (il->cfg->mod_params->amsdu_size_8K)
		rb_size = FH49_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_8K;
	अन्यथा
		rb_size = FH49_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_4K;

	/* Stop Rx DMA */
	il_wr(il, FH49_MEM_RCSR_CHNL0_CONFIG_REG, 0);

	/* Reset driver's Rx queue ग_लिखो idx */
	il_wr(il, FH49_RSCSR_CHNL0_RBDCB_WPTR_REG, 0);

	/* Tell device where to find RBD circular buffer in DRAM */
	il_wr(il, FH49_RSCSR_CHNL0_RBDCB_BASE_REG, (u32) (rxq->bd_dma >> 8));

	/* Tell device where in DRAM to update its Rx status */
	il_wr(il, FH49_RSCSR_CHNL0_STTS_WPTR_REG, rxq->rb_stts_dma >> 4);

	/* Enable Rx DMA
	 * Direct rx पूर्णांकerrupts to hosts
	 * Rx buffer size 4 or 8k
	 * RB समयout 0x10
	 * 256 RBDs
	 */
	il_wr(il, FH49_MEM_RCSR_CHNL0_CONFIG_REG,
	      FH49_RCSR_RX_CONFIG_CHNL_EN_ENABLE_VAL |
	      FH49_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_INT_HOST_VAL |
	      FH49_RCSR_CHNL0_RX_CONFIG_SINGLE_FRAME_MSK |
	      rb_size |
	      (rb_समयout << FH49_RCSR_RX_CONFIG_REG_IRQ_RBTH_POS) |
	      (rfdnlog << FH49_RCSR_RX_CONFIG_RBDCB_SIZE_POS));

	/* Set पूर्णांकerrupt coalescing समयr to शेष (2048 usecs) */
	il_ग_लिखो8(il, CSR_INT_COALESCING, IL_HOST_INT_TIMEOUT_DEF);

	वापस 0;
पूर्ण

अटल व्योम
il4965_set_pwr_vमुख्य(काष्ठा il_priv *il)
अणु
/*
 * (क्रम करोcumentation purposes)
 * to set घातer to V_AUX, करो:

		अगर (pci_pme_capable(il->pci_dev, PCI_D3cold))
			il_set_bits_mask_prph(il, APMG_PS_CTRL_REG,
					       APMG_PS_CTRL_VAL_PWR_SRC_VAUX,
					       ~APMG_PS_CTRL_MSK_PWR_SRC);
 */

	il_set_bits_mask_prph(il, APMG_PS_CTRL_REG,
			      APMG_PS_CTRL_VAL_PWR_SRC_VMAIN,
			      ~APMG_PS_CTRL_MSK_PWR_SRC);
पूर्ण

पूर्णांक
il4965_hw_nic_init(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा il_rx_queue *rxq = &il->rxq;
	पूर्णांक ret;

	spin_lock_irqsave(&il->lock, flags);
	il_apm_init(il);
	/* Set पूर्णांकerrupt coalescing calibration समयr to शेष (512 usecs) */
	il_ग_लिखो8(il, CSR_INT_COALESCING, IL_HOST_INT_CALIB_TIMEOUT_DEF);
	spin_unlock_irqrestore(&il->lock, flags);

	il4965_set_pwr_vमुख्य(il);
	il4965_nic_config(il);

	/* Allocate the RX queue, or reset अगर it is alपढ़ोy allocated */
	अगर (!rxq->bd) अणु
		ret = il_rx_queue_alloc(il);
		अगर (ret) अणु
			IL_ERR("Unable to initialize Rx queue\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा
		il4965_rx_queue_reset(il, rxq);

	il4965_rx_replenish(il);

	il4965_rx_init(il, rxq);

	spin_lock_irqsave(&il->lock, flags);

	rxq->need_update = 1;
	il_rx_queue_update_ग_लिखो_ptr(il, rxq);

	spin_unlock_irqrestore(&il->lock, flags);

	/* Allocate or reset and init all Tx and Command queues */
	अगर (!il->txq) अणु
		ret = il4965_txq_ctx_alloc(il);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		il4965_txq_ctx_reset(il);

	set_bit(S_INIT, &il->status);

	वापस 0;
पूर्ण

/*
 * il4965_dma_addr2rbd_ptr - convert a DMA address to a uCode पढ़ो buffer ptr
 */
अटल अंतरभूत __le32
il4965_dma_addr2rbd_ptr(काष्ठा il_priv *il, dma_addr_t dma_addr)
अणु
	वापस cpu_to_le32((u32) (dma_addr >> 8));
पूर्ण

/*
 * il4965_rx_queue_restock - refill RX queue from pre-allocated pool
 *
 * If there are slots in the RX queue that need to be restocked,
 * and we have मुक्त pre-allocated buffers, fill the ranks as much
 * as we can, pulling from rx_मुक्त.
 *
 * This moves the 'write' idx forward to catch up with 'processed', and
 * also updates the memory address in the firmware to reference the new
 * target buffer.
 */
व्योम
il4965_rx_queue_restock(काष्ठा il_priv *il)
अणु
	काष्ठा il_rx_queue *rxq = &il->rxq;
	काष्ठा list_head *element;
	काष्ठा il_rx_buf *rxb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rxq->lock, flags);
	जबतक (il_rx_queue_space(rxq) > 0 && rxq->मुक्त_count) अणु
		/* The overwritten rxb must be a used one */
		rxb = rxq->queue[rxq->ग_लिखो];
		BUG_ON(rxb && rxb->page);

		/* Get next मुक्त Rx buffer, हटाओ from मुक्त list */
		element = rxq->rx_मुक्त.next;
		rxb = list_entry(element, काष्ठा il_rx_buf, list);
		list_del(element);

		/* Poपूर्णांक to Rx buffer via next RBD in circular buffer */
		rxq->bd[rxq->ग_लिखो] =
		    il4965_dma_addr2rbd_ptr(il, rxb->page_dma);
		rxq->queue[rxq->ग_लिखो] = rxb;
		rxq->ग_लिखो = (rxq->ग_लिखो + 1) & RX_QUEUE_MASK;
		rxq->मुक्त_count--;
	पूर्ण
	spin_unlock_irqrestore(&rxq->lock, flags);
	/* If the pre-allocated buffer pool is dropping low, schedule to
	 * refill it */
	अगर (rxq->मुक्त_count <= RX_LOW_WATERMARK)
		queue_work(il->workqueue, &il->rx_replenish);

	/* If we've added more space क्रम the firmware to place data, tell it.
	 * Increment device's ग_लिखो poपूर्णांकer in multiples of 8. */
	अगर (rxq->ग_लिखो_actual != (rxq->ग_लिखो & ~0x7)) अणु
		spin_lock_irqsave(&rxq->lock, flags);
		rxq->need_update = 1;
		spin_unlock_irqrestore(&rxq->lock, flags);
		il_rx_queue_update_ग_लिखो_ptr(il, rxq);
	पूर्ण
पूर्ण

/*
 * il4965_rx_replenish - Move all used packet from rx_used to rx_मुक्त
 *
 * When moving to rx_मुक्त an SKB is allocated क्रम the slot.
 *
 * Also restock the Rx queue via il_rx_queue_restock.
 * This is called as a scheduled work item (except क्रम during initialization)
 */
अटल व्योम
il4965_rx_allocate(काष्ठा il_priv *il, gfp_t priority)
अणु
	काष्ठा il_rx_queue *rxq = &il->rxq;
	काष्ठा list_head *element;
	काष्ठा il_rx_buf *rxb;
	काष्ठा page *page;
	dma_addr_t page_dma;
	अचिन्हित दीर्घ flags;
	gfp_t gfp_mask = priority;

	जबतक (1) अणु
		spin_lock_irqsave(&rxq->lock, flags);
		अगर (list_empty(&rxq->rx_used)) अणु
			spin_unlock_irqrestore(&rxq->lock, flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&rxq->lock, flags);

		अगर (rxq->मुक्त_count > RX_LOW_WATERMARK)
			gfp_mask |= __GFP_NOWARN;

		अगर (il->hw_params.rx_page_order > 0)
			gfp_mask |= __GFP_COMP;

		/* Alloc a new receive buffer */
		page = alloc_pages(gfp_mask, il->hw_params.rx_page_order);
		अगर (!page) अणु
			अगर (net_ratelimit())
				D_INFO("alloc_pages failed, " "order: %d\n",
				       il->hw_params.rx_page_order);

			अगर (rxq->मुक्त_count <= RX_LOW_WATERMARK &&
			    net_ratelimit())
				IL_ERR("Failed to alloc_pages with %s. "
				       "Only %u free buffers remaining.\n",
				       priority ==
				       GFP_ATOMIC ? "GFP_ATOMIC" : "GFP_KERNEL",
				       rxq->मुक्त_count);
			/* We करोn't reschedule replenish work here -- we will
			 * call the restock method and अगर it still needs
			 * more buffers it will schedule replenish */
			वापस;
		पूर्ण

		/* Get physical address of the RB */
		page_dma =
		    pci_map_page(il->pci_dev, page, 0,
				 PAGE_SIZE << il->hw_params.rx_page_order,
				 PCI_DMA_FROMDEVICE);
		अगर (unlikely(pci_dma_mapping_error(il->pci_dev, page_dma))) अणु
			__मुक्त_pages(page, il->hw_params.rx_page_order);
			अवरोध;
		पूर्ण

		spin_lock_irqsave(&rxq->lock, flags);

		अगर (list_empty(&rxq->rx_used)) अणु
			spin_unlock_irqrestore(&rxq->lock, flags);
			pci_unmap_page(il->pci_dev, page_dma,
				       PAGE_SIZE << il->hw_params.rx_page_order,
				       PCI_DMA_FROMDEVICE);
			__मुक्त_pages(page, il->hw_params.rx_page_order);
			वापस;
		पूर्ण

		element = rxq->rx_used.next;
		rxb = list_entry(element, काष्ठा il_rx_buf, list);
		list_del(element);

		BUG_ON(rxb->page);

		rxb->page = page;
		rxb->page_dma = page_dma;
		list_add_tail(&rxb->list, &rxq->rx_मुक्त);
		rxq->मुक्त_count++;
		il->alloc_rxb_page++;

		spin_unlock_irqrestore(&rxq->lock, flags);
	पूर्ण
पूर्ण

व्योम
il4965_rx_replenish(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;

	il4965_rx_allocate(il, GFP_KERNEL);

	spin_lock_irqsave(&il->lock, flags);
	il4965_rx_queue_restock(il);
	spin_unlock_irqrestore(&il->lock, flags);
पूर्ण

व्योम
il4965_rx_replenish_now(काष्ठा il_priv *il)
अणु
	il4965_rx_allocate(il, GFP_ATOMIC);

	il4965_rx_queue_restock(il);
पूर्ण

/* Assumes that the skb field of the buffers in 'pool' is kept accurate.
 * If an SKB has been detached, the POOL needs to have its SKB set to शून्य
 * This मुक्त routine walks the list of POOL entries and अगर SKB is set to
 * non शून्य it is unmapped and मुक्तd
 */
व्योम
il4965_rx_queue_मुक्त(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < RX_QUEUE_SIZE + RX_FREE_BUFFERS; i++) अणु
		अगर (rxq->pool[i].page != शून्य) अणु
			pci_unmap_page(il->pci_dev, rxq->pool[i].page_dma,
				       PAGE_SIZE << il->hw_params.rx_page_order,
				       PCI_DMA_FROMDEVICE);
			__il_मुक्त_pages(il, rxq->pool[i].page);
			rxq->pool[i].page = शून्य;
		पूर्ण
	पूर्ण

	dma_मुक्त_coherent(&il->pci_dev->dev, 4 * RX_QUEUE_SIZE, rxq->bd,
			  rxq->bd_dma);
	dma_मुक्त_coherent(&il->pci_dev->dev, माप(काष्ठा il_rb_status),
			  rxq->rb_stts, rxq->rb_stts_dma);
	rxq->bd = शून्य;
	rxq->rb_stts = शून्य;
पूर्ण

पूर्णांक
il4965_rxq_stop(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;

	_il_wr(il, FH49_MEM_RCSR_CHNL0_CONFIG_REG, 0);
	ret = _il_poll_bit(il, FH49_MEM_RSSR_RX_STATUS_REG,
			   FH49_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			   FH49_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			   1000);
	अगर (ret < 0)
		IL_ERR("Can't stop Rx DMA.\n");

	वापस 0;
पूर्ण

पूर्णांक
il4965_hwrate_to_mac80211_idx(u32 rate_n_flags, क्रमागत nl80211_band band)
अणु
	पूर्णांक idx = 0;
	पूर्णांक band_offset = 0;

	/* HT rate क्रमmat: mac80211 wants an MCS number, which is just LSB */
	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		idx = (rate_n_flags & 0xff);
		वापस idx;
		/* Legacy rate क्रमmat, search क्रम match in table */
	पूर्ण अन्यथा अणु
		अगर (band == NL80211_BAND_5GHZ)
			band_offset = IL_FIRST_OFDM_RATE;
		क्रम (idx = band_offset; idx < RATE_COUNT_LEGACY; idx++)
			अगर (il_rates[idx].plcp == (rate_n_flags & 0xFF))
				वापस idx - band_offset;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक
il4965_calc_rssi(काष्ठा il_priv *il, काष्ठा il_rx_phy_res *rx_resp)
अणु
	/* data from PHY/DSP regarding संकेत strength, etc.,
	 *   contents are always there, not configurable by host.  */
	काष्ठा il4965_rx_non_cfg_phy *ncphy =
	    (काष्ठा il4965_rx_non_cfg_phy *)rx_resp->non_cfg_phy_buf;
	u32 agc =
	    (le16_to_cpu(ncphy->agc_info) & IL49_AGC_DB_MASK) >>
	    IL49_AGC_DB_POS;

	u32 valid_antennae =
	    (le16_to_cpu(rx_resp->phy_flags) & IL49_RX_PHY_FLAGS_ANTENNAE_MASK)
	    >> IL49_RX_PHY_FLAGS_ANTENNAE_OFFSET;
	u8 max_rssi = 0;
	u32 i;

	/* Find max rssi among 3 possible receivers.
	 * These values are measured by the digital संकेत processor (DSP).
	 * They should stay fairly स्थिरant even as the संकेत strength varies,
	 *   अगर the radio's स्वतःmatic gain control (AGC) is working right.
	 * AGC value (see below) will provide the "interesting" info. */
	क्रम (i = 0; i < 3; i++)
		अगर (valid_antennae & (1 << i))
			max_rssi = max(ncphy->rssi_info[i << 1], max_rssi);

	D_STATS("Rssi In A %d B %d C %d Max %d AGC dB %d\n",
		ncphy->rssi_info[0], ncphy->rssi_info[2], ncphy->rssi_info[4],
		max_rssi, agc);

	/* dBm = max_rssi dB - agc dB - स्थिरant.
	 * Higher AGC (higher radio gain) means lower संकेत. */
	वापस max_rssi - agc - IL4965_RSSI_OFFSET;
पूर्ण

अटल u32
il4965_translate_rx_status(काष्ठा il_priv *il, u32 decrypt_in)
अणु
	u32 decrypt_out = 0;

	अगर ((decrypt_in & RX_RES_STATUS_STATION_FOUND) ==
	    RX_RES_STATUS_STATION_FOUND)
		decrypt_out |=
		    (RX_RES_STATUS_STATION_FOUND |
		     RX_RES_STATUS_NO_STATION_INFO_MISMATCH);

	decrypt_out |= (decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK);

	/* packet was not encrypted */
	अगर ((decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) ==
	    RX_RES_STATUS_SEC_TYPE_NONE)
		वापस decrypt_out;

	/* packet was encrypted with unknown alg */
	अगर ((decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) ==
	    RX_RES_STATUS_SEC_TYPE_ERR)
		वापस decrypt_out;

	/* decryption was not करोne in HW */
	अगर ((decrypt_in & RX_MPDU_RES_STATUS_DEC_DONE_MSK) !=
	    RX_MPDU_RES_STATUS_DEC_DONE_MSK)
		वापस decrypt_out;

	चयन (decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) अणु

	हाल RX_RES_STATUS_SEC_TYPE_CCMP:
		/* alg is CCM: check MIC only */
		अगर (!(decrypt_in & RX_MPDU_RES_STATUS_MIC_OK))
			/* Bad MIC */
			decrypt_out |= RX_RES_STATUS_BAD_ICV_MIC;
		अन्यथा
			decrypt_out |= RX_RES_STATUS_DECRYPT_OK;

		अवरोध;

	हाल RX_RES_STATUS_SEC_TYPE_TKIP:
		अगर (!(decrypt_in & RX_MPDU_RES_STATUS_TTAK_OK)) अणु
			/* Bad TTAK */
			decrypt_out |= RX_RES_STATUS_BAD_KEY_TTAK;
			अवरोध;
		पूर्ण
		fallthrough;	/* अगर TTAK OK */
	शेष:
		अगर (!(decrypt_in & RX_MPDU_RES_STATUS_ICV_OK))
			decrypt_out |= RX_RES_STATUS_BAD_ICV_MIC;
		अन्यथा
			decrypt_out |= RX_RES_STATUS_DECRYPT_OK;
		अवरोध;
	पूर्ण

	D_RX("decrypt_in:0x%x  decrypt_out = 0x%x\n", decrypt_in, decrypt_out);

	वापस decrypt_out;
पूर्ण

#घोषणा SMALL_PACKET_SIZE 256

अटल व्योम
il4965_pass_packet_to_mac80211(काष्ठा il_priv *il, काष्ठा ieee80211_hdr *hdr,
			       u32 len, u32 ampdu_status, काष्ठा il_rx_buf *rxb,
			       काष्ठा ieee80211_rx_status *stats)
अणु
	काष्ठा sk_buff *skb;
	__le16 fc = hdr->frame_control;

	/* We only process data packets अगर the पूर्णांकerface is खोलो */
	अगर (unlikely(!il->is_खोलो)) अणु
		D_DROP("Dropping packet while interface is not open.\n");
		वापस;
	पूर्ण

	अगर (unlikely(test_bit(IL_STOP_REASON_PASSIVE, &il->stop_reason))) अणु
		il_wake_queues_by_reason(il, IL_STOP_REASON_PASSIVE);
		D_INFO("Woke queues - frame received on passive channel\n");
	पूर्ण

	/* In हाल of HW accelerated crypto and bad decryption, drop */
	अगर (!il->cfg->mod_params->sw_crypto &&
	    il_set_decrypted_flag(il, hdr, ampdu_status, stats))
		वापस;

	skb = dev_alloc_skb(SMALL_PACKET_SIZE);
	अगर (!skb) अणु
		IL_ERR("dev_alloc_skb failed\n");
		वापस;
	पूर्ण

	अगर (len <= SMALL_PACKET_SIZE) अणु
		skb_put_data(skb, hdr, len);
	पूर्ण अन्यथा अणु
		skb_add_rx_frag(skb, 0, rxb->page, (व्योम *)hdr - rxb_addr(rxb),
				len, PAGE_SIZE << il->hw_params.rx_page_order);
		il->alloc_rxb_page--;
		rxb->page = शून्य;
	पूर्ण

	il_update_stats(il, false, fc, len);
	स_नकल(IEEE80211_SKB_RXCB(skb), stats, माप(*stats));

	ieee80211_rx(il->hw, skb);
पूर्ण

/* Called क्रम N_RX (legacy ABG frames), or
 * N_RX_MPDU (HT high-throughput N frames). */
अटल व्योम
il4965_hdl_rx(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा ieee80211_hdr *header;
	काष्ठा ieee80211_rx_status rx_status = अणुपूर्ण;
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_rx_phy_res *phy_res;
	__le32 rx_pkt_status;
	काष्ठा il_rx_mpdu_res_start *amsdu;
	u32 len;
	u32 ampdu_status;
	u32 rate_n_flags;

	/**
	 * N_RX and N_RX_MPDU are handled dअगरferently.
	 *	N_RX: physical layer info is in this buffer
	 *	N_RX_MPDU: physical layer info was sent in separate
	 *		command and cached in il->last_phy_res
	 *
	 * Here we set up local variables depending on which command is
	 * received.
	 */
	अगर (pkt->hdr.cmd == N_RX) अणु
		phy_res = (काष्ठा il_rx_phy_res *)pkt->u.raw;
		header =
		    (काष्ठा ieee80211_hdr *)(pkt->u.raw + माप(*phy_res) +
					     phy_res->cfg_phy_cnt);

		len = le16_to_cpu(phy_res->byte_count);
		rx_pkt_status =
		    *(__le32 *) (pkt->u.raw + माप(*phy_res) +
				 phy_res->cfg_phy_cnt + len);
		ampdu_status = le32_to_cpu(rx_pkt_status);
	पूर्ण अन्यथा अणु
		अगर (!il->_4965.last_phy_res_valid) अणु
			IL_ERR("MPDU frame without cached PHY data\n");
			वापस;
		पूर्ण
		phy_res = &il->_4965.last_phy_res;
		amsdu = (काष्ठा il_rx_mpdu_res_start *)pkt->u.raw;
		header = (काष्ठा ieee80211_hdr *)(pkt->u.raw + माप(*amsdu));
		len = le16_to_cpu(amsdu->byte_count);
		rx_pkt_status = *(__le32 *) (pkt->u.raw + माप(*amsdu) + len);
		ampdu_status =
		    il4965_translate_rx_status(il, le32_to_cpu(rx_pkt_status));
	पूर्ण

	अगर ((unlikely(phy_res->cfg_phy_cnt > 20))) अणु
		D_DROP("dsp size out of range [0,20]: %d\n",
		       phy_res->cfg_phy_cnt);
		वापस;
	पूर्ण

	अगर (!(rx_pkt_status & RX_RES_STATUS_NO_CRC32_ERROR) ||
	    !(rx_pkt_status & RX_RES_STATUS_NO_RXE_OVERFLOW)) अणु
		D_RX("Bad CRC or FIFO: 0x%08X.\n", le32_to_cpu(rx_pkt_status));
		वापस;
	पूर्ण

	/* This will be used in several places later */
	rate_n_flags = le32_to_cpu(phy_res->rate_n_flags);

	/* rx_status carries inक्रमmation about the packet to mac80211 */
	rx_status.maस_समय = le64_to_cpu(phy_res->बारtamp);
	rx_status.band =
	    (phy_res->
	     phy_flags & RX_RES_PHY_FLAGS_BAND_24_MSK) ? NL80211_BAND_2GHZ :
	    NL80211_BAND_5GHZ;
	rx_status.freq =
	    ieee80211_channel_to_frequency(le16_to_cpu(phy_res->channel),
					   rx_status.band);
	rx_status.rate_idx =
	    il4965_hwrate_to_mac80211_idx(rate_n_flags, rx_status.band);
	rx_status.flag = 0;

	/* TSF isn't reliable. In order to allow smooth user experience,
	 * this W/A करोesn't propagate it to the mac80211 */
	/*rx_status.flag |= RX_FLAG_MACTIME_START; */

	il->ucode_beacon_समय = le32_to_cpu(phy_res->beacon_समय_stamp);

	/* Find max संकेत strength (dBm) among 3 antenna/receiver chains */
	rx_status.संकेत = il4965_calc_rssi(il, phy_res);

	D_STATS("Rssi %d, TSF %llu\n", rx_status.संकेत,
		(अचिन्हित दीर्घ दीर्घ)rx_status.maस_समय);

	/*
	 * "antenna number"
	 *
	 * It seems that the antenna field in the phy flags value
	 * is actually a bit field. This is undefined by radiotap,
	 * it wants an actual antenna number but I always get "7"
	 * क्रम most legacy frames I receive indicating that the
	 * same frame was received on all three RX chains.
	 *
	 * I think this field should be हटाओd in favor of a
	 * new 802.11n radiotap field "RX chains" that is defined
	 * as a biपंचांगask.
	 */
	rx_status.antenna =
	    (le16_to_cpu(phy_res->phy_flags) & RX_RES_PHY_FLAGS_ANTENNA_MSK) >>
	    RX_RES_PHY_FLAGS_ANTENNA_POS;

	/* set the preamble flag अगर appropriate */
	अगर (phy_res->phy_flags & RX_RES_PHY_FLAGS_SHORT_PREAMBLE_MSK)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORTPRE;

	/* Set up the HT phy flags */
	अगर (rate_n_flags & RATE_MCS_HT_MSK)
		rx_status.encoding = RX_ENC_HT;
	अगर (rate_n_flags & RATE_MCS_HT40_MSK)
		rx_status.bw = RATE_INFO_BW_40;
	अन्यथा
		rx_status.bw = RATE_INFO_BW_20;
	अगर (rate_n_flags & RATE_MCS_SGI_MSK)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORT_GI;

	अगर (phy_res->phy_flags & RX_RES_PHY_FLAGS_AGG_MSK) अणु
		/* We know which subframes of an A-MPDU beदीर्घ
		 * together since we get a single PHY response
		 * from the firmware क्रम all of them.
		 */

		rx_status.flag |= RX_FLAG_AMPDU_DETAILS;
		rx_status.ampdu_reference = il->_4965.ampdu_ref;
	पूर्ण

	il4965_pass_packet_to_mac80211(il, header, len, ampdu_status, rxb,
				       &rx_status);
पूर्ण

/* Cache phy data (Rx संकेत strength, etc) क्रम HT frame (N_RX_PHY).
 * This will be used later in il_hdl_rx() क्रम N_RX_MPDU. */
अटल व्योम
il4965_hdl_rx_phy(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	il->_4965.last_phy_res_valid = true;
	il->_4965.ampdu_ref++;
	स_नकल(&il->_4965.last_phy_res, pkt->u.raw,
	       माप(काष्ठा il_rx_phy_res));
पूर्ण

अटल पूर्णांक
il4965_get_channels_क्रम_scan(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
			     क्रमागत nl80211_band band, u8 is_active,
			     u8 n_probes, काष्ठा il_scan_channel *scan_ch)
अणु
	काष्ठा ieee80211_channel *chan;
	स्थिर काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा il_channel_info *ch_info;
	u16 passive_dwell = 0;
	u16 active_dwell = 0;
	पूर्णांक added, i;
	u16 channel;

	sband = il_get_hw_mode(il, band);
	अगर (!sband)
		वापस 0;

	active_dwell = il_get_active_dwell_समय(il, band, n_probes);
	passive_dwell = il_get_passive_dwell_समय(il, band, vअगर);

	अगर (passive_dwell <= active_dwell)
		passive_dwell = active_dwell + 1;

	क्रम (i = 0, added = 0; i < il->scan_request->n_channels; i++) अणु
		chan = il->scan_request->channels[i];

		अगर (chan->band != band)
			जारी;

		channel = chan->hw_value;
		scan_ch->channel = cpu_to_le16(channel);

		ch_info = il_get_channel_info(il, band, channel);
		अगर (!il_is_channel_valid(ch_info)) अणु
			D_SCAN("Channel %d is INVALID for this band.\n",
			       channel);
			जारी;
		पूर्ण

		अगर (!is_active || il_is_channel_passive(ch_info) ||
		    (chan->flags & IEEE80211_CHAN_NO_IR))
			scan_ch->type = SCAN_CHANNEL_TYPE_PASSIVE;
		अन्यथा
			scan_ch->type = SCAN_CHANNEL_TYPE_ACTIVE;

		अगर (n_probes)
			scan_ch->type |= IL_SCAN_PROBE_MASK(n_probes);

		scan_ch->active_dwell = cpu_to_le16(active_dwell);
		scan_ch->passive_dwell = cpu_to_le16(passive_dwell);

		/* Set txघातer levels to शेषs */
		scan_ch->dsp_atten = 110;

		/* NOTE: अगर we were करोing 6Mb OFDM क्रम scans we'd use
		 * घातer level:
		 * scan_ch->tx_gain = ((1 << 5) | (2 << 3)) | 3;
		 */
		अगर (band == NL80211_BAND_5GHZ)
			scan_ch->tx_gain = ((1 << 5) | (3 << 3)) | 3;
		अन्यथा
			scan_ch->tx_gain = ((1 << 5) | (5 << 3));

		D_SCAN("Scanning ch=%d prob=0x%X [%s %d]\n", channel,
		       le32_to_cpu(scan_ch->type),
		       (scan_ch->
			type & SCAN_CHANNEL_TYPE_ACTIVE) ? "ACTIVE" : "PASSIVE",
		       (scan_ch->
			type & SCAN_CHANNEL_TYPE_ACTIVE) ? active_dwell :
		       passive_dwell);

		scan_ch++;
		added++;
	पूर्ण

	D_SCAN("total channels to scan %d\n", added);
	वापस added;
पूर्ण

अटल व्योम
il4965_toggle_tx_ant(काष्ठा il_priv *il, u8 *ant, u8 valid)
अणु
	पूर्णांक i;
	u8 ind = *ant;

	क्रम (i = 0; i < RATE_ANT_NUM - 1; i++) अणु
		ind = (ind + 1) < RATE_ANT_NUM ? ind + 1 : 0;
		अगर (valid & BIT(ind)) अणु
			*ant = ind;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
il4965_request_scan(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा il_host_cmd cmd = अणु
		.id = C_SCAN,
		.len = माप(काष्ठा il_scan_cmd),
		.flags = CMD_SIZE_HUGE,
	पूर्ण;
	काष्ठा il_scan_cmd *scan;
	u32 rate_flags = 0;
	u16 cmd_len;
	u16 rx_chain = 0;
	क्रमागत nl80211_band band;
	u8 n_probes = 0;
	u8 rx_ant = il->hw_params.valid_rx_ant;
	u8 rate;
	bool is_active = false;
	पूर्णांक chan_mod;
	u8 active_chains;
	u8 scan_tx_antennas = il->hw_params.valid_tx_ant;
	पूर्णांक ret;

	lockdep_निश्चित_held(&il->mutex);

	अगर (!il->scan_cmd) अणु
		il->scan_cmd =
		    kदो_स्मृति(माप(काष्ठा il_scan_cmd) + IL_MAX_SCAN_SIZE,
			    GFP_KERNEL);
		अगर (!il->scan_cmd) अणु
			D_SCAN("fail to allocate memory for scan\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	scan = il->scan_cmd;
	स_रखो(scan, 0, माप(काष्ठा il_scan_cmd) + IL_MAX_SCAN_SIZE);

	scan->quiet_plcp_th = IL_PLCP_QUIET_THRESH;
	scan->quiet_समय = IL_ACTIVE_QUIET_TIME;

	अगर (il_is_any_associated(il)) अणु
		u16 पूर्णांकerval;
		u32 extra;
		u32 suspend_समय = 100;
		u32 scan_suspend_समय = 100;

		D_INFO("Scanning while associated...\n");
		पूर्णांकerval = vअगर->bss_conf.beacon_पूर्णांक;

		scan->suspend_समय = 0;
		scan->max_out_समय = cpu_to_le32(200 * 1024);
		अगर (!पूर्णांकerval)
			पूर्णांकerval = suspend_समय;

		extra = (suspend_समय / पूर्णांकerval) << 22;
		scan_suspend_समय =
		    (extra | ((suspend_समय % पूर्णांकerval) * 1024));
		scan->suspend_समय = cpu_to_le32(scan_suspend_समय);
		D_SCAN("suspend_time 0x%X beacon interval %d\n",
		       scan_suspend_समय, पूर्णांकerval);
	पूर्ण

	अगर (il->scan_request->n_ssids) अणु
		पूर्णांक i, p = 0;
		D_SCAN("Kicking off active scan\n");
		क्रम (i = 0; i < il->scan_request->n_ssids; i++) अणु
			/* always करोes wildcard anyway */
			अगर (!il->scan_request->ssids[i].ssid_len)
				जारी;
			scan->direct_scan[p].id = WLAN_EID_SSID;
			scan->direct_scan[p].len =
			    il->scan_request->ssids[i].ssid_len;
			स_नकल(scan->direct_scan[p].ssid,
			       il->scan_request->ssids[i].ssid,
			       il->scan_request->ssids[i].ssid_len);
			n_probes++;
			p++;
		पूर्ण
		is_active = true;
	पूर्ण अन्यथा
		D_SCAN("Start passive scan.\n");

	scan->tx_cmd.tx_flags = TX_CMD_FLG_SEQ_CTL_MSK;
	scan->tx_cmd.sta_id = il->hw_params.bcast_id;
	scan->tx_cmd.stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;

	चयन (il->scan_band) अणु
	हाल NL80211_BAND_2GHZ:
		scan->flags = RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK;
		chan_mod =
		    le32_to_cpu(il->active.flags & RXON_FLG_CHANNEL_MODE_MSK) >>
		    RXON_FLG_CHANNEL_MODE_POS;
		अगर (chan_mod == CHANNEL_MODE_PURE_40) अणु
			rate = RATE_6M_PLCP;
		पूर्ण अन्यथा अणु
			rate = RATE_1M_PLCP;
			rate_flags = RATE_MCS_CCK_MSK;
		पूर्ण
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		rate = RATE_6M_PLCP;
		अवरोध;
	शेष:
		IL_WARN("Invalid scan band\n");
		वापस -EIO;
	पूर्ण

	/*
	 * If active scanning is requested but a certain channel is
	 * marked passive, we can करो active scanning अगर we detect
	 * transmissions.
	 *
	 * There is an issue with some firmware versions that triggers
	 * a sysनिश्चित on a "good CRC threshold" of zero (== disabled),
	 * on a radar channel even though this means that we should NOT
	 * send probes.
	 *
	 * The "good CRC threshold" is the number of frames that we
	 * need to receive during our dwell समय on a channel beक्रमe
	 * sending out probes -- setting this to a huge value will
	 * mean we never reach it, but at the same समय work around
	 * the aक्रमementioned issue. Thus use IL_GOOD_CRC_TH_NEVER
	 * here instead of IL_GOOD_CRC_TH_DISABLED.
	 */
	scan->good_CRC_th =
	    is_active ? IL_GOOD_CRC_TH_DEFAULT : IL_GOOD_CRC_TH_NEVER;

	band = il->scan_band;

	अगर (il->cfg->scan_rx_antennas[band])
		rx_ant = il->cfg->scan_rx_antennas[band];

	il4965_toggle_tx_ant(il, &il->scan_tx_ant[band], scan_tx_antennas);
	rate_flags |= BIT(il->scan_tx_ant[band]) << RATE_MCS_ANT_POS;
	scan->tx_cmd.rate_n_flags = cpu_to_le32(rate | rate_flags);

	/* In घातer save mode use one chain, otherwise use all chains */
	अगर (test_bit(S_POWER_PMI, &il->status)) अणु
		/* rx_ant has been set to all valid chains previously */
		active_chains =
		    rx_ant & ((u8) (il->chain_noise_data.active_chains));
		अगर (!active_chains)
			active_chains = rx_ant;

		D_SCAN("chain_noise_data.active_chains: %u\n",
		       il->chain_noise_data.active_chains);

		rx_ant = il4965_first_antenna(active_chains);
	पूर्ण

	/* MIMO is not used here, but value is required */
	rx_chain |= il->hw_params.valid_rx_ant << RXON_RX_CHAIN_VALID_POS;
	rx_chain |= rx_ant << RXON_RX_CHAIN_FORCE_MIMO_SEL_POS;
	rx_chain |= rx_ant << RXON_RX_CHAIN_FORCE_SEL_POS;
	rx_chain |= 0x1 << RXON_RX_CHAIN_DRIVER_FORCE_POS;
	scan->rx_chain = cpu_to_le16(rx_chain);

	cmd_len =
	    il_fill_probe_req(il, (काष्ठा ieee80211_mgmt *)scan->data,
			      vअगर->addr, il->scan_request->ie,
			      il->scan_request->ie_len,
			      IL_MAX_SCAN_SIZE - माप(*scan));
	scan->tx_cmd.len = cpu_to_le16(cmd_len);

	scan->filter_flags |=
	    (RXON_FILTER_ACCEPT_GRP_MSK | RXON_FILTER_BCON_AWARE_MSK);

	scan->channel_count =
	    il4965_get_channels_क्रम_scan(il, vअगर, band, is_active, n_probes,
					 (व्योम *)&scan->data[cmd_len]);
	अगर (scan->channel_count == 0) अणु
		D_SCAN("channel count %d\n", scan->channel_count);
		वापस -EIO;
	पूर्ण

	cmd.len +=
	    le16_to_cpu(scan->tx_cmd.len) +
	    scan->channel_count * माप(काष्ठा il_scan_channel);
	cmd.data = scan;
	scan->len = cpu_to_le16(cmd.len);

	set_bit(S_SCAN_HW, &il->status);

	ret = il_send_cmd_sync(il, &cmd);
	अगर (ret)
		clear_bit(S_SCAN_HW, &il->status);

	वापस ret;
पूर्ण

पूर्णांक
il4965_manage_ibss_station(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
			   bool add)
अणु
	काष्ठा il_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;

	अगर (add)
		वापस il4965_add_bssid_station(il, vअगर->bss_conf.bssid,
						&vअगर_priv->ibss_bssid_sta_id);
	वापस il_हटाओ_station(il, vअगर_priv->ibss_bssid_sta_id,
				 vअगर->bss_conf.bssid);
पूर्ण

व्योम
il4965_मुक्त_tfds_in_queue(काष्ठा il_priv *il, पूर्णांक sta_id, पूर्णांक tid, पूर्णांक मुक्तd)
अणु
	lockdep_निश्चित_held(&il->sta_lock);

	अगर (il->stations[sta_id].tid[tid].tfds_in_queue >= मुक्तd)
		il->stations[sta_id].tid[tid].tfds_in_queue -= मुक्तd;
	अन्यथा अणु
		D_TX("free more than tfds_in_queue (%u:%d)\n",
		     il->stations[sta_id].tid[tid].tfds_in_queue, मुक्तd);
		il->stations[sta_id].tid[tid].tfds_in_queue = 0;
	पूर्ण
पूर्ण

#घोषणा IL_TX_QUEUE_MSK	0xfffff

अटल bool
il4965_is_single_rx_stream(काष्ठा il_priv *il)
अणु
	वापस il->current_ht_config.smps == IEEE80211_SMPS_STATIC ||
	    il->current_ht_config.single_chain_sufficient;
पूर्ण

#घोषणा IL_NUM_RX_CHAINS_MULTIPLE	3
#घोषणा IL_NUM_RX_CHAINS_SINGLE	2
#घोषणा IL_NUM_IDLE_CHAINS_DUAL	2
#घोषणा IL_NUM_IDLE_CHAINS_SINGLE	1

/*
 * Determine how many receiver/antenna chains to use.
 *
 * More provides better reception via भागersity.  Fewer saves घातer
 * at the expense of throughput, but only when not in घातersave to
 * start with.
 *
 * MIMO (dual stream) requires at least 2, but works better with 3.
 * This करोes not determine *which* chains to use, just how many.
 */
अटल पूर्णांक
il4965_get_active_rx_chain_count(काष्ठा il_priv *il)
अणु
	/* # of Rx chains to use when expecting MIMO. */
	अगर (il4965_is_single_rx_stream(il))
		वापस IL_NUM_RX_CHAINS_SINGLE;
	अन्यथा
		वापस IL_NUM_RX_CHAINS_MULTIPLE;
पूर्ण

/*
 * When we are in घातer saving mode, unless device support spatial
 * multiplexing घातer save, use the active count क्रम rx chain count.
 */
अटल पूर्णांक
il4965_get_idle_rx_chain_count(काष्ठा il_priv *il, पूर्णांक active_cnt)
अणु
	/* # Rx chains when idling, depending on SMPS mode */
	चयन (il->current_ht_config.smps) अणु
	हाल IEEE80211_SMPS_STATIC:
	हाल IEEE80211_SMPS_DYNAMIC:
		वापस IL_NUM_IDLE_CHAINS_SINGLE;
	हाल IEEE80211_SMPS_OFF:
		वापस active_cnt;
	शेष:
		WARN(1, "invalid SMPS mode %d", il->current_ht_config.smps);
		वापस active_cnt;
	पूर्ण
पूर्ण

/* up to 4 chains */
अटल u8
il4965_count_chain_biपंचांगap(u32 chain_biपंचांगap)
अणु
	u8 res;
	res = (chain_biपंचांगap & BIT(0)) >> 0;
	res += (chain_biपंचांगap & BIT(1)) >> 1;
	res += (chain_biपंचांगap & BIT(2)) >> 2;
	res += (chain_biपंचांगap & BIT(3)) >> 3;
	वापस res;
पूर्ण

/*
 * il4965_set_rxon_chain - Set up Rx chain usage in "staging" RXON image
 *
 * Selects how many and which Rx receivers/antennas/chains to use.
 * This should not be used क्रम scan command ... it माला_दो data in wrong place.
 */
व्योम
il4965_set_rxon_chain(काष्ठा il_priv *il)
अणु
	bool is_single = il4965_is_single_rx_stream(il);
	bool is_cam = !test_bit(S_POWER_PMI, &il->status);
	u8 idle_rx_cnt, active_rx_cnt, valid_rx_cnt;
	u32 active_chains;
	u16 rx_chain;

	/* Tell uCode which antennas are actually connected.
	 * Beक्रमe first association, we assume all antennas are connected.
	 * Just after first association, il4965_chain_noise_calibration()
	 *    checks which antennas actually *are* connected. */
	अगर (il->chain_noise_data.active_chains)
		active_chains = il->chain_noise_data.active_chains;
	अन्यथा
		active_chains = il->hw_params.valid_rx_ant;

	rx_chain = active_chains << RXON_RX_CHAIN_VALID_POS;

	/* How many receivers should we use? */
	active_rx_cnt = il4965_get_active_rx_chain_count(il);
	idle_rx_cnt = il4965_get_idle_rx_chain_count(il, active_rx_cnt);

	/* correct rx chain count according hw settings
	 * and chain noise calibration
	 */
	valid_rx_cnt = il4965_count_chain_biपंचांगap(active_chains);
	अगर (valid_rx_cnt < active_rx_cnt)
		active_rx_cnt = valid_rx_cnt;

	अगर (valid_rx_cnt < idle_rx_cnt)
		idle_rx_cnt = valid_rx_cnt;

	rx_chain |= active_rx_cnt << RXON_RX_CHAIN_MIMO_CNT_POS;
	rx_chain |= idle_rx_cnt << RXON_RX_CHAIN_CNT_POS;

	il->staging.rx_chain = cpu_to_le16(rx_chain);

	अगर (!is_single && active_rx_cnt >= IL_NUM_RX_CHAINS_SINGLE && is_cam)
		il->staging.rx_chain |= RXON_RX_CHAIN_MIMO_FORCE_MSK;
	अन्यथा
		il->staging.rx_chain &= ~RXON_RX_CHAIN_MIMO_FORCE_MSK;

	D_ASSOC("rx_chain=0x%X active=%d idle=%d\n", il->staging.rx_chain,
		active_rx_cnt, idle_rx_cnt);

	WARN_ON(active_rx_cnt == 0 || idle_rx_cnt == 0 ||
		active_rx_cnt < idle_rx_cnt);
पूर्ण

अटल स्थिर अक्षर *
il4965_get_fh_string(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
		IL_CMD(FH49_RSCSR_CHNL0_STTS_WPTR_REG);
		IL_CMD(FH49_RSCSR_CHNL0_RBDCB_BASE_REG);
		IL_CMD(FH49_RSCSR_CHNL0_WPTR);
		IL_CMD(FH49_MEM_RCSR_CHNL0_CONFIG_REG);
		IL_CMD(FH49_MEM_RSSR_SHARED_CTRL_REG);
		IL_CMD(FH49_MEM_RSSR_RX_STATUS_REG);
		IL_CMD(FH49_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV);
		IL_CMD(FH49_TSSR_TX_STATUS_REG);
		IL_CMD(FH49_TSSR_TX_ERROR_REG);
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

पूर्णांक
il4965_dump_fh(काष्ठा il_priv *il, अक्षर **buf, bool display)
अणु
	पूर्णांक i;
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	पूर्णांक pos = 0;
	माप_प्रकार bufsz = 0;
#पूर्ण_अगर
	अटल स्थिर u32 fh_tbl[] = अणु
		FH49_RSCSR_CHNL0_STTS_WPTR_REG,
		FH49_RSCSR_CHNL0_RBDCB_BASE_REG,
		FH49_RSCSR_CHNL0_WPTR,
		FH49_MEM_RCSR_CHNL0_CONFIG_REG,
		FH49_MEM_RSSR_SHARED_CTRL_REG,
		FH49_MEM_RSSR_RX_STATUS_REG,
		FH49_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV,
		FH49_TSSR_TX_STATUS_REG,
		FH49_TSSR_TX_ERROR_REG
	पूर्ण;
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (display) अणु
		bufsz = ARRAY_SIZE(fh_tbl) * 48 + 40;
		*buf = kदो_स्मृति(bufsz, GFP_KERNEL);
		अगर (!*buf)
			वापस -ENOMEM;
		pos +=
		    scnम_लिखो(*buf + pos, bufsz - pos, "FH register values:\n");
		क्रम (i = 0; i < ARRAY_SIZE(fh_tbl); i++) अणु
			pos +=
			    scnम_लिखो(*buf + pos, bufsz - pos,
				      "  %34s: 0X%08x\n",
				      il4965_get_fh_string(fh_tbl[i]),
				      il_rd(il, fh_tbl[i]));
		पूर्ण
		वापस pos;
	पूर्ण
#पूर्ण_अगर
	IL_ERR("FH register values:\n");
	क्रम (i = 0; i < ARRAY_SIZE(fh_tbl); i++) अणु
		IL_ERR("  %34s: 0X%08x\n", il4965_get_fh_string(fh_tbl[i]),
		       il_rd(il, fh_tbl[i]));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
il4965_hdl_missed_beacon(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_missed_beacon_notअगर *missed_beacon;

	missed_beacon = &pkt->u.missed_beacon;
	अगर (le32_to_cpu(missed_beacon->consecutive_missed_beacons) >
	    il->missed_beacon_threshold) अणु
		D_CALIB("missed bcn cnsq %d totl %d rcd %d expctd %d\n",
			le32_to_cpu(missed_beacon->consecutive_missed_beacons),
			le32_to_cpu(missed_beacon->total_missed_becons),
			le32_to_cpu(missed_beacon->num_recvd_beacons),
			le32_to_cpu(missed_beacon->num_expected_beacons));
		अगर (!test_bit(S_SCANNING, &il->status))
			il4965_init_sensitivity(il);
	पूर्ण
पूर्ण

/* Calculate noise level, based on measurements during network silence just
 *   beक्रमe arriving beacon.  This measurement can be करोne only अगर we know
 *   exactly when to expect beacons, thereक्रमe only when we're associated. */
अटल व्योम
il4965_rx_calc_noise(काष्ठा il_priv *il)
अणु
	काष्ठा stats_rx_non_phy *rx_info;
	पूर्णांक num_active_rx = 0;
	पूर्णांक total_silence = 0;
	पूर्णांक bcn_silence_a, bcn_silence_b, bcn_silence_c;
	पूर्णांक last_rx_noise;

	rx_info = &(il->_4965.stats.rx.general);
	bcn_silence_a =
	    le32_to_cpu(rx_info->beacon_silence_rssi_a) & IN_BAND_FILTER;
	bcn_silence_b =
	    le32_to_cpu(rx_info->beacon_silence_rssi_b) & IN_BAND_FILTER;
	bcn_silence_c =
	    le32_to_cpu(rx_info->beacon_silence_rssi_c) & IN_BAND_FILTER;

	अगर (bcn_silence_a) अणु
		total_silence += bcn_silence_a;
		num_active_rx++;
	पूर्ण
	अगर (bcn_silence_b) अणु
		total_silence += bcn_silence_b;
		num_active_rx++;
	पूर्ण
	अगर (bcn_silence_c) अणु
		total_silence += bcn_silence_c;
		num_active_rx++;
	पूर्ण

	/* Average among active antennas */
	अगर (num_active_rx)
		last_rx_noise = (total_silence / num_active_rx) - 107;
	अन्यथा
		last_rx_noise = IL_NOISE_MEAS_NOT_AVAILABLE;

	D_CALIB("inband silence a %u, b %u, c %u, dBm %d\n", bcn_silence_a,
		bcn_silence_b, bcn_silence_c, last_rx_noise);
पूर्ण

#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
/*
 *  based on the assumption of all stats counter are in DWORD
 *  FIXME: This function is क्रम debugging, करो not deal with
 *  the हाल of counters roll-over.
 */
अटल व्योम
il4965_accumulative_stats(काष्ठा il_priv *il, __le32 * stats)
अणु
	पूर्णांक i, size;
	__le32 *prev_stats;
	u32 *accum_stats;
	u32 *delta, *max_delta;
	काष्ठा stats_general_common *general, *accum_general;

	prev_stats = (__le32 *) &il->_4965.stats;
	accum_stats = (u32 *) &il->_4965.accum_stats;
	size = माप(काष्ठा il_notअगर_stats);
	general = &il->_4965.stats.general.common;
	accum_general = &il->_4965.accum_stats.general.common;
	delta = (u32 *) &il->_4965.delta_stats;
	max_delta = (u32 *) &il->_4965.max_delta;

	क्रम (i = माप(__le32); i < size;
	     i +=
	     माप(__le32), stats++, prev_stats++, delta++, max_delta++,
	     accum_stats++) अणु
		अगर (le32_to_cpu(*stats) > le32_to_cpu(*prev_stats)) अणु
			*delta =
			    (le32_to_cpu(*stats) - le32_to_cpu(*prev_stats));
			*accum_stats += *delta;
			अगर (*delta > *max_delta)
				*max_delta = *delta;
		पूर्ण
	पूर्ण

	/* reset accumulative stats क्रम "no-counter" type stats */
	accum_general->temperature = general->temperature;
	accum_general->ttl_बारtamp = general->ttl_बारtamp;
पूर्ण
#पूर्ण_अगर

अटल व्योम
il4965_hdl_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	स्थिर पूर्णांक recalib_seconds = 60;
	bool change;
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);

	D_RX("Statistics notification received (%d vs %d).\n",
	     (पूर्णांक)माप(काष्ठा il_notअगर_stats),
	     le32_to_cpu(pkt->len_n_flags) & IL_RX_FRAME_SIZE_MSK);

	change =
	    ((il->_4965.stats.general.common.temperature !=
	      pkt->u.stats.general.common.temperature) ||
	     ((il->_4965.stats.flag & STATS_REPLY_FLG_HT40_MODE_MSK) !=
	      (pkt->u.stats.flag & STATS_REPLY_FLG_HT40_MODE_MSK)));
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	il4965_accumulative_stats(il, (__le32 *) &pkt->u.stats);
#पूर्ण_अगर

	/* TODO: पढ़ोing some of stats is unneeded */
	स_नकल(&il->_4965.stats, &pkt->u.stats, माप(il->_4965.stats));

	set_bit(S_STATS, &il->status);

	/*
	 * Reschedule the stats समयr to occur in recalib_seconds to ensure
	 * we get a thermal update even अगर the uCode करोesn't give us one
	 */
	mod_समयr(&il->stats_periodic,
		  jअगरfies + msecs_to_jअगरfies(recalib_seconds * 1000));

	अगर (unlikely(!test_bit(S_SCANNING, &il->status)) &&
	    (pkt->hdr.cmd == N_STATS)) अणु
		il4965_rx_calc_noise(il);
		queue_work(il->workqueue, &il->run_समय_calib_work);
	पूर्ण

	अगर (change)
		il4965_temperature_calib(il);
पूर्ण

अटल व्योम
il4965_hdl_c_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);

	अगर (le32_to_cpu(pkt->u.stats.flag) & UCODE_STATS_CLEAR_MSK) अणु
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
		स_रखो(&il->_4965.accum_stats, 0,
		       माप(काष्ठा il_notअगर_stats));
		स_रखो(&il->_4965.delta_stats, 0,
		       माप(काष्ठा il_notअगर_stats));
		स_रखो(&il->_4965.max_delta, 0, माप(काष्ठा il_notअगर_stats));
#पूर्ण_अगर
		D_RX("Statistics have been cleared\n");
	पूर्ण
	il4965_hdl_stats(il, rxb);
पूर्ण


/*
 * mac80211 queues, ACs, hardware queues, FIFOs.
 *
 * Cf. https://wireless.wiki.kernel.org/en/developers/Documentation/mac80211/queues
 *
 * Mac80211 uses the following numbers, which we get as from it
 * by way of skb_get_queue_mapping(skb):
 *
 *     VO      0
 *     VI      1
 *     BE      2
 *     BK      3
 *
 *
 * Regular (not A-MPDU) frames are put पूर्णांकo hardware queues corresponding
 * to the FIFOs, see comments in iwl-prph.h. Aggregated frames get their
 * own queue per aggregation session (RA/TID combination), such queues are
 * set up to map पूर्णांकo FIFOs too, क्रम which we need an AC->FIFO mapping. In
 * order to map frames to the right queue, we also need an AC->hw queue
 * mapping. This is implemented here.
 *
 * Due to the way hw queues are set up (by the hw specअगरic modules like
 * 4965.c), the AC->hw queue mapping is the identity
 * mapping.
 */

अटल स्थिर u8 tid_to_ac[] = अणु
	IEEE80211_AC_BE,
	IEEE80211_AC_BK,
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_VO
पूर्ण;

अटल अंतरभूत पूर्णांक
il4965_get_ac_from_tid(u16 tid)
अणु
	अगर (likely(tid < ARRAY_SIZE(tid_to_ac)))
		वापस tid_to_ac[tid];

	/* no support क्रम TIDs 8-15 yet */
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक
il4965_get_fअगरo_from_tid(u16 tid)
अणु
	अटल स्थिर u8 ac_to_fअगरo[] = अणु
		IL_TX_FIFO_VO,
		IL_TX_FIFO_VI,
		IL_TX_FIFO_BE,
		IL_TX_FIFO_BK,
	पूर्ण;

	अगर (likely(tid < ARRAY_SIZE(tid_to_ac)))
		वापस ac_to_fअगरo[tid_to_ac[tid]];

	/* no support क्रम TIDs 8-15 yet */
	वापस -EINVAL;
पूर्ण

/*
 * handle build C_TX command notअगरication.
 */
अटल व्योम
il4965_tx_cmd_build_basic(काष्ठा il_priv *il, काष्ठा sk_buff *skb,
			  काष्ठा il_tx_cmd *tx_cmd,
			  काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_hdr *hdr, u8 std_id)
अणु
	__le16 fc = hdr->frame_control;
	__le32 tx_flags = tx_cmd->tx_flags;

	tx_cmd->stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;
	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK)) अणु
		tx_flags |= TX_CMD_FLG_ACK_MSK;
		अगर (ieee80211_is_mgmt(fc))
			tx_flags |= TX_CMD_FLG_SEQ_CTL_MSK;
		अगर (ieee80211_is_probe_resp(fc) &&
		    !(le16_to_cpu(hdr->seq_ctrl) & 0xf))
			tx_flags |= TX_CMD_FLG_TSF_MSK;
	पूर्ण अन्यथा अणु
		tx_flags &= (~TX_CMD_FLG_ACK_MSK);
		tx_flags |= TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण

	अगर (ieee80211_is_back_req(fc))
		tx_flags |= TX_CMD_FLG_ACK_MSK | TX_CMD_FLG_IMM_BA_RSP_MASK;

	tx_cmd->sta_id = std_id;
	अगर (ieee80211_has_morefrags(fc))
		tx_flags |= TX_CMD_FLG_MORE_FRAG_MSK;

	अगर (ieee80211_is_data_qos(fc)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tx_cmd->tid_tspec = qc[0] & 0xf;
		tx_flags &= ~TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण अन्यथा अणु
		tx_flags |= TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण

	il_tx_cmd_protection(il, info, fc, &tx_flags);

	tx_flags &= ~(TX_CMD_FLG_ANT_SEL_MSK);
	अगर (ieee80211_is_mgmt(fc)) अणु
		अगर (ieee80211_is_assoc_req(fc) || ieee80211_is_reassoc_req(fc))
			tx_cmd->समयout.pm_frame_समयout = cpu_to_le16(3);
		अन्यथा
			tx_cmd->समयout.pm_frame_समयout = cpu_to_le16(2);
	पूर्ण अन्यथा अणु
		tx_cmd->समयout.pm_frame_समयout = 0;
	पूर्ण

	tx_cmd->driver_txop = 0;
	tx_cmd->tx_flags = tx_flags;
	tx_cmd->next_frame_len = 0;
पूर्ण

अटल व्योम
il4965_tx_cmd_build_rate(काष्ठा il_priv *il,
			 काष्ठा il_tx_cmd *tx_cmd,
			 काष्ठा ieee80211_tx_info *info,
			 काष्ठा ieee80211_sta *sta,
			 __le16 fc)
अणु
	स्थिर u8 rts_retry_limit = 60;
	u32 rate_flags;
	पूर्णांक rate_idx;
	u8 data_retry_limit;
	u8 rate_plcp;

	/* Set retry limit on DATA packets and Probe Responses */
	अगर (ieee80211_is_probe_resp(fc))
		data_retry_limit = 3;
	अन्यथा
		data_retry_limit = IL4965_DEFAULT_TX_RETRY;
	tx_cmd->data_retry_limit = data_retry_limit;
	/* Set retry limit on RTS packets */
	tx_cmd->rts_retry_limit = min(data_retry_limit, rts_retry_limit);

	/* DATA packets will use the uCode station table क्रम rate/antenna
	 * selection */
	अगर (ieee80211_is_data(fc)) अणु
		tx_cmd->initial_rate_idx = 0;
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;
		वापस;
	पूर्ण

	/**
	 * If the current TX rate stored in mac80211 has the MCS bit set, it's
	 * not really a TX rate.  Thus, we use the lowest supported rate क्रम
	 * this band.  Also use the lowest supported rate अगर the stored rate
	 * idx is invalid.
	 */
	rate_idx = info->control.rates[0].idx;
	अगर ((info->control.rates[0].flags & IEEE80211_TX_RC_MCS) || rate_idx < 0
	    || rate_idx > RATE_COUNT_LEGACY)
		rate_idx = rate_lowest_index(&il->bands[info->band], sta);
	/* For 5 GHZ band, remap mac80211 rate indices पूर्णांकo driver indices */
	अगर (info->band == NL80211_BAND_5GHZ)
		rate_idx += IL_FIRST_OFDM_RATE;
	/* Get PLCP rate क्रम tx_cmd->rate_n_flags */
	rate_plcp = il_rates[rate_idx].plcp;
	/* Zero out flags क्रम this packet */
	rate_flags = 0;

	/* Set CCK flag as needed */
	अगर (rate_idx >= IL_FIRST_CCK_RATE && rate_idx <= IL_LAST_CCK_RATE)
		rate_flags |= RATE_MCS_CCK_MSK;

	/* Set up antennas */
	il4965_toggle_tx_ant(il, &il->mgmt_tx_ant, il->hw_params.valid_tx_ant);
	rate_flags |= BIT(il->mgmt_tx_ant) << RATE_MCS_ANT_POS;

	/* Set the rate in the TX cmd */
	tx_cmd->rate_n_flags = cpu_to_le32(rate_plcp | rate_flags);
पूर्ण

अटल व्योम
il4965_tx_cmd_build_hwcrypto(काष्ठा il_priv *il, काष्ठा ieee80211_tx_info *info,
			     काष्ठा il_tx_cmd *tx_cmd, काष्ठा sk_buff *skb_frag,
			     पूर्णांक sta_id)
अणु
	काष्ठा ieee80211_key_conf *keyconf = info->control.hw_key;

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		tx_cmd->sec_ctl = TX_CMD_SEC_CCM;
		स_नकल(tx_cmd->key, keyconf->key, keyconf->keylen);
		अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
			tx_cmd->tx_flags |= TX_CMD_FLG_AGG_CCMP_MSK;
		D_TX("tx_cmd with AES hwcrypto\n");
		अवरोध;

	हाल WLAN_CIPHER_SUITE_TKIP:
		tx_cmd->sec_ctl = TX_CMD_SEC_TKIP;
		ieee80211_get_tkip_p2k(keyconf, skb_frag, tx_cmd->key);
		D_TX("tx_cmd with tkip hwcrypto\n");
		अवरोध;

	हाल WLAN_CIPHER_SUITE_WEP104:
		tx_cmd->sec_ctl |= TX_CMD_SEC_KEY128;
		fallthrough;
	हाल WLAN_CIPHER_SUITE_WEP40:
		tx_cmd->sec_ctl |=
		    (TX_CMD_SEC_WEP | (keyconf->keyidx & TX_CMD_SEC_MSK) <<
		     TX_CMD_SEC_SHIFT);

		स_नकल(&tx_cmd->key[3], keyconf->key, keyconf->keylen);

		D_TX("Configuring packet for WEP encryption " "with key %d\n",
		     keyconf->keyidx);
		अवरोध;

	शेष:
		IL_ERR("Unknown encode cipher %x\n", keyconf->cipher);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * start C_TX command process
 */
पूर्णांक
il4965_tx_skb(काष्ठा il_priv *il,
	      काष्ठा ieee80211_sta *sta,
	      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा il_station_priv *sta_priv = शून्य;
	काष्ठा il_tx_queue *txq;
	काष्ठा il_queue *q;
	काष्ठा il_device_cmd *out_cmd;
	काष्ठा il_cmd_meta *out_meta;
	काष्ठा il_tx_cmd *tx_cmd;
	पूर्णांक txq_id;
	dma_addr_t phys_addr;
	dma_addr_t txcmd_phys;
	dma_addr_t scratch_phys;
	u16 len, firstlen, secondlen;
	u16 seq_number = 0;
	__le16 fc;
	u8 hdr_len;
	u8 sta_id;
	u8 रुको_ग_लिखो_ptr = 0;
	u8 tid = 0;
	u8 *qc = शून्य;
	अचिन्हित दीर्घ flags;
	bool is_agg = false;

	spin_lock_irqsave(&il->lock, flags);
	अगर (il_is_rfसमाप्त(il)) अणु
		D_DROP("Dropping - RF KILL\n");
		जाओ drop_unlock;
	पूर्ण

	fc = hdr->frame_control;

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (ieee80211_is_auth(fc))
		D_TX("Sending AUTH frame\n");
	अन्यथा अगर (ieee80211_is_assoc_req(fc))
		D_TX("Sending ASSOC frame\n");
	अन्यथा अगर (ieee80211_is_reassoc_req(fc))
		D_TX("Sending REASSOC frame\n");
#पूर्ण_अगर

	hdr_len = ieee80211_hdrlen(fc);

	/* For management frames use broadcast id to करो not अवरोध aggregation */
	अगर (!ieee80211_is_data(fc))
		sta_id = il->hw_params.bcast_id;
	अन्यथा अणु
		/* Find idx पूर्णांकo station table क्रम destination station */
		sta_id = il_sta_id_or_broadcast(il, sta);

		अगर (sta_id == IL_INVALID_STATION) अणु
			D_DROP("Dropping - INVALID STATION: %pM\n", hdr->addr1);
			जाओ drop_unlock;
		पूर्ण
	पूर्ण

	D_TX("station Id %d\n", sta_id);

	अगर (sta)
		sta_priv = (व्योम *)sta->drv_priv;

	अगर (sta_priv && sta_priv->asleep &&
	    (info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER)) अणु
		/*
		 * This sends an asynchronous command to the device,
		 * but we can rely on it being processed beक्रमe the
		 * next frame is processed -- and the next frame to
		 * this station is the one that will consume this
		 * counter.
		 * For now set the counter to just 1 since we करो not
		 * support uAPSD yet.
		 */
		il4965_sta_modअगरy_sleep_tx_count(il, sta_id, 1);
	पूर्ण

	/* FIXME: हटाओ me ? */
	WARN_ON_ONCE(info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM);

	/* Access category (AC) is also the queue number */
	txq_id = skb_get_queue_mapping(skb);

	/* irqs alपढ़ोy disabled/saved above when locking il->lock */
	spin_lock(&il->sta_lock);

	अगर (ieee80211_is_data_qos(fc)) अणु
		qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
		अगर (WARN_ON_ONCE(tid >= MAX_TID_COUNT)) अणु
			spin_unlock(&il->sta_lock);
			जाओ drop_unlock;
		पूर्ण
		seq_number = il->stations[sta_id].tid[tid].seq_number;
		seq_number &= IEEE80211_SCTL_SEQ;
		hdr->seq_ctrl =
		    hdr->seq_ctrl & cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(seq_number);
		seq_number += 0x10;
		/* aggregation is on क्रम this <sta,tid> */
		अगर (info->flags & IEEE80211_TX_CTL_AMPDU &&
		    il->stations[sta_id].tid[tid].agg.state == IL_AGG_ON) अणु
			txq_id = il->stations[sta_id].tid[tid].agg.txq_id;
			is_agg = true;
		पूर्ण
	पूर्ण

	txq = &il->txq[txq_id];
	q = &txq->q;

	अगर (unlikely(il_queue_space(q) < q->high_mark)) अणु
		spin_unlock(&il->sta_lock);
		जाओ drop_unlock;
	पूर्ण

	अगर (ieee80211_is_data_qos(fc)) अणु
		il->stations[sta_id].tid[tid].tfds_in_queue++;
		अगर (!ieee80211_has_morefrags(fc))
			il->stations[sta_id].tid[tid].seq_number = seq_number;
	पूर्ण

	spin_unlock(&il->sta_lock);

	txq->skbs[q->ग_लिखो_ptr] = skb;

	/* Set up first empty entry in queue's array of Tx/cmd buffers */
	out_cmd = txq->cmd[q->ग_लिखो_ptr];
	out_meta = &txq->meta[q->ग_लिखो_ptr];
	tx_cmd = &out_cmd->cmd.tx;
	स_रखो(&out_cmd->hdr, 0, माप(out_cmd->hdr));
	स_रखो(tx_cmd, 0, माप(काष्ठा il_tx_cmd));

	/*
	 * Set up the Tx-command (not MAC!) header.
	 * Store the chosen Tx queue and TFD idx within the sequence field;
	 * after Tx, uCode's Tx response will वापस this value so driver can
	 * locate the frame within the tx queue and करो post-tx processing.
	 */
	out_cmd->hdr.cmd = C_TX;
	out_cmd->hdr.sequence =
	    cpu_to_le16((u16)
			(QUEUE_TO_SEQ(txq_id) | IDX_TO_SEQ(q->ग_लिखो_ptr)));

	/* Copy MAC header from skb पूर्णांकo command buffer */
	स_नकल(tx_cmd->hdr, hdr, hdr_len);

	/* Total # bytes to be transmitted */
	tx_cmd->len = cpu_to_le16((u16) skb->len);

	अगर (info->control.hw_key)
		il4965_tx_cmd_build_hwcrypto(il, info, tx_cmd, skb, sta_id);

	/* TODO need this क्रम burst mode later on */
	il4965_tx_cmd_build_basic(il, skb, tx_cmd, info, hdr, sta_id);

	il4965_tx_cmd_build_rate(il, tx_cmd, info, sta, fc);

	/*
	 * Use the first empty entry in this queue's command buffer array
	 * to contain the Tx command and MAC header concatenated together
	 * (payload data will be in another buffer).
	 * Size of this varies, due to varying MAC header length.
	 * If end is not dword aligned, we'll have 2 extra bytes at the end
	 * of the MAC header (device पढ़ोs on dword boundaries).
	 * We'll tell device about this padding later.
	 */
	len = माप(काष्ठा il_tx_cmd) + माप(काष्ठा il_cmd_header) + hdr_len;
	firstlen = (len + 3) & ~3;

	/* Tell NIC about any 2-byte padding after MAC header */
	अगर (firstlen != len)
		tx_cmd->tx_flags |= TX_CMD_FLG_MH_PAD_MSK;

	/* Physical address of this Tx command's header (not MAC header!),
	 * within command buffer array. */
	txcmd_phys =
	    pci_map_single(il->pci_dev, &out_cmd->hdr, firstlen,
			   PCI_DMA_BIसूचीECTIONAL);
	अगर (unlikely(pci_dma_mapping_error(il->pci_dev, txcmd_phys)))
		जाओ drop_unlock;

	/* Set up TFD's 2nd entry to poपूर्णांक directly to reमुख्यder of skb,
	 * अगर any (802.11 null frames have no payload). */
	secondlen = skb->len - hdr_len;
	अगर (secondlen > 0) अणु
		phys_addr =
		    pci_map_single(il->pci_dev, skb->data + hdr_len, secondlen,
				   PCI_DMA_TODEVICE);
		अगर (unlikely(pci_dma_mapping_error(il->pci_dev, phys_addr)))
			जाओ drop_unlock;
	पूर्ण

	/* Add buffer containing Tx command and MAC(!) header to TFD's
	 * first entry */
	il->ops->txq_attach_buf_to_tfd(il, txq, txcmd_phys, firstlen, 1, 0);
	dma_unmap_addr_set(out_meta, mapping, txcmd_phys);
	dma_unmap_len_set(out_meta, len, firstlen);
	अगर (secondlen)
		il->ops->txq_attach_buf_to_tfd(il, txq, phys_addr, secondlen,
					       0, 0);

	अगर (!ieee80211_has_morefrags(hdr->frame_control)) अणु
		txq->need_update = 1;
	पूर्ण अन्यथा अणु
		रुको_ग_लिखो_ptr = 1;
		txq->need_update = 0;
	पूर्ण

	scratch_phys =
	    txcmd_phys + माप(काष्ठा il_cmd_header) +
	    दुरत्व(काष्ठा il_tx_cmd, scratch);

	/* take back ownership of DMA buffer to enable update */
	pci_dma_sync_single_क्रम_cpu(il->pci_dev, txcmd_phys, firstlen,
				    PCI_DMA_BIसूचीECTIONAL);
	tx_cmd->dram_lsb_ptr = cpu_to_le32(scratch_phys);
	tx_cmd->dram_msb_ptr = il_get_dma_hi_addr(scratch_phys);

	il_update_stats(il, true, fc, skb->len);

	D_TX("sequence nr = 0X%x\n", le16_to_cpu(out_cmd->hdr.sequence));
	D_TX("tx_flags = 0X%x\n", le32_to_cpu(tx_cmd->tx_flags));
	il_prपूर्णांक_hex_dump(il, IL_DL_TX, (u8 *) tx_cmd, माप(*tx_cmd));
	il_prपूर्णांक_hex_dump(il, IL_DL_TX, (u8 *) tx_cmd->hdr, hdr_len);

	/* Set up entry क्रम this TFD in Tx byte-count array */
	अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
		il->ops->txq_update_byte_cnt_tbl(il, txq, le16_to_cpu(tx_cmd->len));

	pci_dma_sync_single_क्रम_device(il->pci_dev, txcmd_phys, firstlen,
				       PCI_DMA_BIसूचीECTIONAL);

	/* Tell device the ग_लिखो idx *just past* this latest filled TFD */
	q->ग_लिखो_ptr = il_queue_inc_wrap(q->ग_लिखो_ptr, q->n_bd);
	il_txq_update_ग_लिखो_ptr(il, txq);
	spin_unlock_irqrestore(&il->lock, flags);

	/*
	 * At this poपूर्णांक the frame is "transmitted" successfully
	 * and we will get a TX status notअगरication eventually,
	 * regardless of the value of ret. "ret" only indicates
	 * whether or not we should update the ग_लिखो poपूर्णांकer.
	 */

	/*
	 * Aव्योम atomic ops अगर it isn't an associated client.
	 * Also, अगर this is a packet क्रम aggregation, करोn't
	 * increase the counter because the ucode will stop
	 * aggregation queues when their respective station
	 * goes to sleep.
	 */
	अगर (sta_priv && sta_priv->client && !is_agg)
		atomic_inc(&sta_priv->pending_frames);

	अगर (il_queue_space(q) < q->high_mark && il->mac80211_रेजिस्टरed) अणु
		अगर (रुको_ग_लिखो_ptr) अणु
			spin_lock_irqsave(&il->lock, flags);
			txq->need_update = 1;
			il_txq_update_ग_लिखो_ptr(il, txq);
			spin_unlock_irqrestore(&il->lock, flags);
		पूर्ण अन्यथा अणु
			il_stop_queue(il, txq);
		पूर्ण
	पूर्ण

	वापस 0;

drop_unlock:
	spin_unlock_irqrestore(&il->lock, flags);
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक
il4965_alloc_dma_ptr(काष्ठा il_priv *il, काष्ठा il_dma_ptr *ptr, माप_प्रकार size)
अणु
	ptr->addr = dma_alloc_coherent(&il->pci_dev->dev, size, &ptr->dma,
				       GFP_KERNEL);
	अगर (!ptr->addr)
		वापस -ENOMEM;
	ptr->size = size;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
il4965_मुक्त_dma_ptr(काष्ठा il_priv *il, काष्ठा il_dma_ptr *ptr)
अणु
	अगर (unlikely(!ptr->addr))
		वापस;

	dma_मुक्त_coherent(&il->pci_dev->dev, ptr->size, ptr->addr, ptr->dma);
	स_रखो(ptr, 0, माप(*ptr));
पूर्ण

/*
 * il4965_hw_txq_ctx_मुक्त - Free TXQ Context
 *
 * Destroy all TX DMA queues and काष्ठाures
 */
व्योम
il4965_hw_txq_ctx_मुक्त(काष्ठा il_priv *il)
अणु
	पूर्णांक txq_id;

	/* Tx queues */
	अगर (il->txq) अणु
		क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
			अगर (txq_id == il->cmd_queue)
				il_cmd_queue_मुक्त(il);
			अन्यथा
				il_tx_queue_मुक्त(il, txq_id);
	पूर्ण
	il4965_मुक्त_dma_ptr(il, &il->kw);

	il4965_मुक्त_dma_ptr(il, &il->scd_bc_tbls);

	/* मुक्त tx queue काष्ठाure */
	il_मुक्त_txq_mem(il);
पूर्ण

/*
 * il4965_txq_ctx_alloc - allocate TX queue context
 * Allocate all Tx DMA काष्ठाures and initialize them
 */
पूर्णांक
il4965_txq_ctx_alloc(काष्ठा il_priv *il)
अणु
	पूर्णांक ret, txq_id;
	अचिन्हित दीर्घ flags;

	/* Free all tx/cmd queues and keep-warm buffer */
	il4965_hw_txq_ctx_मुक्त(il);

	ret =
	    il4965_alloc_dma_ptr(il, &il->scd_bc_tbls,
				 il->hw_params.scd_bc_tbls_size);
	अगर (ret) अणु
		IL_ERR("Scheduler BC Table allocation failed\n");
		जाओ error_bc_tbls;
	पूर्ण
	/* Alloc keep-warm buffer */
	ret = il4965_alloc_dma_ptr(il, &il->kw, IL_KW_SIZE);
	अगर (ret) अणु
		IL_ERR("Keep Warm allocation failed\n");
		जाओ error_kw;
	पूर्ण

	/* allocate tx queue काष्ठाure */
	ret = il_alloc_txq_mem(il);
	अगर (ret)
		जाओ error;

	spin_lock_irqsave(&il->lock, flags);

	/* Turn off all Tx DMA fअगरos */
	il4965_txq_set_sched(il, 0);

	/* Tell NIC where to find the "keep warm" buffer */
	il_wr(il, FH49_KW_MEM_ADDR_REG, il->kw.dma >> 4);

	spin_unlock_irqrestore(&il->lock, flags);

	/* Alloc and init all Tx queues, including the command queue (#4/#9) */
	क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++) अणु
		ret = il_tx_queue_init(il, txq_id);
		अगर (ret) अणु
			IL_ERR("Tx %d queue init failed\n", txq_id);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस ret;

error:
	il4965_hw_txq_ctx_मुक्त(il);
	il4965_मुक्त_dma_ptr(il, &il->kw);
error_kw:
	il4965_मुक्त_dma_ptr(il, &il->scd_bc_tbls);
error_bc_tbls:
	वापस ret;
पूर्ण

व्योम
il4965_txq_ctx_reset(काष्ठा il_priv *il)
अणु
	पूर्णांक txq_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&il->lock, flags);

	/* Turn off all Tx DMA fअगरos */
	il4965_txq_set_sched(il, 0);
	/* Tell NIC where to find the "keep warm" buffer */
	il_wr(il, FH49_KW_MEM_ADDR_REG, il->kw.dma >> 4);

	spin_unlock_irqrestore(&il->lock, flags);

	/* Alloc and init all Tx queues, including the command queue (#4) */
	क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
		il_tx_queue_reset(il, txq_id);
पूर्ण

अटल व्योम
il4965_txq_ctx_unmap(काष्ठा il_priv *il)
अणु
	पूर्णांक txq_id;

	अगर (!il->txq)
		वापस;

	/* Unmap DMA from host प्रणाली and मुक्त skb's */
	क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
		अगर (txq_id == il->cmd_queue)
			il_cmd_queue_unmap(il);
		अन्यथा
			il_tx_queue_unmap(il, txq_id);
पूर्ण

/*
 * il4965_txq_ctx_stop - Stop all Tx DMA channels
 */
व्योम
il4965_txq_ctx_stop(काष्ठा il_priv *il)
अणु
	पूर्णांक ch, ret;

	_il_wr_prph(il, IL49_SCD_TXFACT, 0);

	/* Stop each Tx DMA channel, and रुको क्रम it to be idle */
	क्रम (ch = 0; ch < il->hw_params.dma_chnl_num; ch++) अणु
		_il_wr(il, FH49_TCSR_CHNL_TX_CONFIG_REG(ch), 0x0);
		ret =
		    _il_poll_bit(il, FH49_TSSR_TX_STATUS_REG,
				 FH49_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(ch),
				 FH49_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(ch),
				 1000);
		अगर (ret < 0)
			IL_ERR("Timeout stopping DMA channel %d [0x%08x]",
			       ch, _il_rd(il, FH49_TSSR_TX_STATUS_REG));
	पूर्ण
पूर्ण

/*
 * Find first available (lowest unused) Tx Queue, mark it "active".
 * Called only when finding queue क्रम aggregation.
 * Should never वापस anything < 7, because they should alपढ़ोy
 * be in use as EDCA AC (0-3), Command (4), reserved (5, 6)
 */
अटल पूर्णांक
il4965_txq_ctx_activate_मुक्त(काष्ठा il_priv *il)
अणु
	पूर्णांक txq_id;

	क्रम (txq_id = 0; txq_id < il->hw_params.max_txq_num; txq_id++)
		अगर (!test_and_set_bit(txq_id, &il->txq_ctx_active_msk))
			वापस txq_id;
	वापस -1;
पूर्ण

/*
 * il4965_tx_queue_stop_scheduler - Stop queue, but keep configuration
 */
अटल व्योम
il4965_tx_queue_stop_scheduler(काष्ठा il_priv *il, u16 txq_id)
अणु
	/* Simply stop the queue, but करोn't change any configuration;
	 * the SCD_ACT_EN bit is the ग_लिखो-enable mask क्रम the ACTIVE bit. */
	il_wr_prph(il, IL49_SCD_QUEUE_STATUS_BITS(txq_id),
		   (0 << IL49_SCD_QUEUE_STTS_REG_POS_ACTIVE) |
		   (1 << IL49_SCD_QUEUE_STTS_REG_POS_SCD_ACT_EN));
पूर्ण

/*
 * il4965_tx_queue_set_q2ratid - Map unique receiver/tid combination to a queue
 */
अटल पूर्णांक
il4965_tx_queue_set_q2ratid(काष्ठा il_priv *il, u16 ra_tid, u16 txq_id)
अणु
	u32 tbl_dw_addr;
	u32 tbl_dw;
	u16 scd_q2ratid;

	scd_q2ratid = ra_tid & IL_SCD_QUEUE_RA_TID_MAP_RATID_MSK;

	tbl_dw_addr =
	    il->scd_base_addr + IL49_SCD_TRANSLATE_TBL_OFFSET_QUEUE(txq_id);

	tbl_dw = il_पढ़ो_targ_mem(il, tbl_dw_addr);

	अगर (txq_id & 0x1)
		tbl_dw = (scd_q2ratid << 16) | (tbl_dw & 0x0000FFFF);
	अन्यथा
		tbl_dw = scd_q2ratid | (tbl_dw & 0xFFFF0000);

	il_ग_लिखो_targ_mem(il, tbl_dw_addr, tbl_dw);

	वापस 0;
पूर्ण

/*
 * il4965_tx_queue_agg_enable - Set up & enable aggregation क्रम selected queue
 *
 * NOTE:  txq_id must be greater than IL49_FIRST_AMPDU_QUEUE,
 *        i.e. it must be one of the higher queues used क्रम aggregation
 */
अटल पूर्णांक
il4965_txq_agg_enable(काष्ठा il_priv *il, पूर्णांक txq_id, पूर्णांक tx_fअगरo, पूर्णांक sta_id,
		      पूर्णांक tid, u16 ssn_idx)
अणु
	अचिन्हित दीर्घ flags;
	u16 ra_tid;
	पूर्णांक ret;

	अगर ((IL49_FIRST_AMPDU_QUEUE > txq_id) ||
	    (IL49_FIRST_AMPDU_QUEUE +
	     il->cfg->num_of_ampdu_queues <= txq_id)) अणु
		IL_WARN("queue number out of range: %d, must be %d to %d\n",
			txq_id, IL49_FIRST_AMPDU_QUEUE,
			IL49_FIRST_AMPDU_QUEUE +
			il->cfg->num_of_ampdu_queues - 1);
		वापस -EINVAL;
	पूर्ण

	ra_tid = BUILD_RAxTID(sta_id, tid);

	/* Modअगरy device's station table to Tx this TID */
	ret = il4965_sta_tx_modअगरy_enable_tid(il, sta_id, tid);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&il->lock, flags);

	/* Stop this Tx queue beक्रमe configuring it */
	il4965_tx_queue_stop_scheduler(il, txq_id);

	/* Map receiver-address / traffic-ID to this queue */
	il4965_tx_queue_set_q2ratid(il, ra_tid, txq_id);

	/* Set this queue as a chain-building queue */
	il_set_bits_prph(il, IL49_SCD_QUEUECHAIN_SEL, (1 << txq_id));

	/* Place first TFD at idx corresponding to start sequence number.
	 * Assumes that ssn_idx is valid (!= 0xFFF) */
	il->txq[txq_id].q.पढ़ो_ptr = (ssn_idx & 0xff);
	il->txq[txq_id].q.ग_लिखो_ptr = (ssn_idx & 0xff);
	il4965_set_wr_ptrs(il, txq_id, ssn_idx);

	/* Set up Tx win size and frame limit क्रम this queue */
	il_ग_लिखो_targ_mem(il,
			  il->scd_base_addr +
			  IL49_SCD_CONTEXT_QUEUE_OFFSET(txq_id),
			  (SCD_WIN_SIZE << IL49_SCD_QUEUE_CTX_REG1_WIN_SIZE_POS)
			  & IL49_SCD_QUEUE_CTX_REG1_WIN_SIZE_MSK);

	il_ग_लिखो_targ_mem(il,
			  il->scd_base_addr +
			  IL49_SCD_CONTEXT_QUEUE_OFFSET(txq_id) + माप(u32),
			  (SCD_FRAME_LIMIT <<
			   IL49_SCD_QUEUE_CTX_REG2_FRAME_LIMIT_POS) &
			  IL49_SCD_QUEUE_CTX_REG2_FRAME_LIMIT_MSK);

	il_set_bits_prph(il, IL49_SCD_INTERRUPT_MASK, (1 << txq_id));

	/* Set up Status area in SRAM, map to Tx DMA/FIFO, activate the queue */
	il4965_tx_queue_set_status(il, &il->txq[txq_id], tx_fअगरo, 1);

	spin_unlock_irqrestore(&il->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक
il4965_tx_agg_start(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta, u16 tid, u16 * ssn)
अणु
	पूर्णांक sta_id;
	पूर्णांक tx_fअगरo;
	पूर्णांक txq_id;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा il_tid_data *tid_data;

	/* FIXME: warning अगर tx fअगरo not found ? */
	tx_fअगरo = il4965_get_fअगरo_from_tid(tid);
	अगर (unlikely(tx_fअगरo < 0))
		वापस tx_fअगरo;

	D_HT("%s on ra = %pM tid = %d\n", __func__, sta->addr, tid);

	sta_id = il_sta_id(sta);
	अगर (sta_id == IL_INVALID_STATION) अणु
		IL_ERR("Start AGG on invalid station\n");
		वापस -ENXIO;
	पूर्ण
	अगर (unlikely(tid >= MAX_TID_COUNT))
		वापस -EINVAL;

	अगर (il->stations[sta_id].tid[tid].agg.state != IL_AGG_OFF) अणु
		IL_ERR("Start AGG when state is not IL_AGG_OFF !\n");
		वापस -ENXIO;
	पूर्ण

	txq_id = il4965_txq_ctx_activate_मुक्त(il);
	अगर (txq_id == -1) अणु
		IL_ERR("No free aggregation queue available\n");
		वापस -ENXIO;
	पूर्ण

	spin_lock_irqsave(&il->sta_lock, flags);
	tid_data = &il->stations[sta_id].tid[tid];
	*ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
	tid_data->agg.txq_id = txq_id;
	il_set_swq_id(&il->txq[txq_id], il4965_get_ac_from_tid(tid), txq_id);
	spin_unlock_irqrestore(&il->sta_lock, flags);

	ret = il4965_txq_agg_enable(il, txq_id, tx_fअगरo, sta_id, tid, *ssn);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&il->sta_lock, flags);
	tid_data = &il->stations[sta_id].tid[tid];
	अगर (tid_data->tfds_in_queue == 0) अणु
		D_HT("HW queue is empty\n");
		tid_data->agg.state = IL_AGG_ON;
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
	पूर्ण अन्यथा अणु
		D_HT("HW queue is NOT empty: %d packets in HW queue\n",
		     tid_data->tfds_in_queue);
		tid_data->agg.state = IL_EMPTYING_HW_QUEUE_ADDBA;
	पूर्ण
	spin_unlock_irqrestore(&il->sta_lock, flags);
	वापस ret;
पूर्ण

/*
 * txq_id must be greater than IL49_FIRST_AMPDU_QUEUE
 * il->lock must be held by the caller
 */
अटल पूर्णांक
il4965_txq_agg_disable(काष्ठा il_priv *il, u16 txq_id, u16 ssn_idx, u8 tx_fअगरo)
अणु
	अगर ((IL49_FIRST_AMPDU_QUEUE > txq_id) ||
	    (IL49_FIRST_AMPDU_QUEUE +
	     il->cfg->num_of_ampdu_queues <= txq_id)) अणु
		IL_WARN("queue number out of range: %d, must be %d to %d\n",
			txq_id, IL49_FIRST_AMPDU_QUEUE,
			IL49_FIRST_AMPDU_QUEUE +
			il->cfg->num_of_ampdu_queues - 1);
		वापस -EINVAL;
	पूर्ण

	il4965_tx_queue_stop_scheduler(il, txq_id);

	il_clear_bits_prph(il, IL49_SCD_QUEUECHAIN_SEL, (1 << txq_id));

	il->txq[txq_id].q.पढ़ो_ptr = (ssn_idx & 0xff);
	il->txq[txq_id].q.ग_लिखो_ptr = (ssn_idx & 0xff);
	/* supposes that ssn_idx is valid (!= 0xFFF) */
	il4965_set_wr_ptrs(il, txq_id, ssn_idx);

	il_clear_bits_prph(il, IL49_SCD_INTERRUPT_MASK, (1 << txq_id));
	il_txq_ctx_deactivate(il, txq_id);
	il4965_tx_queue_set_status(il, &il->txq[txq_id], tx_fअगरo, 0);

	वापस 0;
पूर्ण

पूर्णांक
il4965_tx_agg_stop(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	पूर्णांक tx_fअगरo_id, txq_id, sta_id, ssn;
	काष्ठा il_tid_data *tid_data;
	पूर्णांक ग_लिखो_ptr, पढ़ो_ptr;
	अचिन्हित दीर्घ flags;

	/* FIXME: warning अगर tx_fअगरo_id not found ? */
	tx_fअगरo_id = il4965_get_fअगरo_from_tid(tid);
	अगर (unlikely(tx_fअगरo_id < 0))
		वापस tx_fअगरo_id;

	sta_id = il_sta_id(sta);

	अगर (sta_id == IL_INVALID_STATION) अणु
		IL_ERR("Invalid station for AGG tid %d\n", tid);
		वापस -ENXIO;
	पूर्ण

	spin_lock_irqsave(&il->sta_lock, flags);

	tid_data = &il->stations[sta_id].tid[tid];
	ssn = (tid_data->seq_number & IEEE80211_SCTL_SEQ) >> 4;
	txq_id = tid_data->agg.txq_id;

	चयन (il->stations[sta_id].tid[tid].agg.state) अणु
	हाल IL_EMPTYING_HW_QUEUE_ADDBA:
		/*
		 * This can happen अगर the peer stops aggregation
		 * again beक्रमe we've had a chance to drain the
		 * queue we selected previously, i.e. beक्रमe the
		 * session was really started completely.
		 */
		D_HT("AGG stop before setup done\n");
		जाओ turn_off;
	हाल IL_AGG_ON:
		अवरोध;
	शेष:
		IL_WARN("Stopping AGG while state not ON or starting\n");
	पूर्ण

	ग_लिखो_ptr = il->txq[txq_id].q.ग_लिखो_ptr;
	पढ़ो_ptr = il->txq[txq_id].q.पढ़ो_ptr;

	/* The queue is not empty */
	अगर (ग_लिखो_ptr != पढ़ो_ptr) अणु
		D_HT("Stopping a non empty AGG HW QUEUE\n");
		il->stations[sta_id].tid[tid].agg.state =
		    IL_EMPTYING_HW_QUEUE_DELBA;
		spin_unlock_irqrestore(&il->sta_lock, flags);
		वापस 0;
	पूर्ण

	D_HT("HW queue is empty\n");
turn_off:
	il->stations[sta_id].tid[tid].agg.state = IL_AGG_OFF;

	/* करो not restore/save irqs */
	spin_unlock(&il->sta_lock);
	spin_lock(&il->lock);

	/*
	 * the only reason this call can fail is queue number out of range,
	 * which can happen अगर uCode is reloaded and all the station
	 * inक्रमmation are lost. अगर it is outside the range, there is no need
	 * to deactivate the uCode queue, just वापस "success" to allow
	 *  mac80211 to clean up it own data.
	 */
	il4965_txq_agg_disable(il, txq_id, ssn, tx_fअगरo_id);
	spin_unlock_irqrestore(&il->lock, flags);

	ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);

	वापस 0;
पूर्ण

पूर्णांक
il4965_txq_check_empty(काष्ठा il_priv *il, पूर्णांक sta_id, u8 tid, पूर्णांक txq_id)
अणु
	काष्ठा il_queue *q = &il->txq[txq_id].q;
	u8 *addr = il->stations[sta_id].sta.sta.addr;
	काष्ठा il_tid_data *tid_data = &il->stations[sta_id].tid[tid];

	lockdep_निश्चित_held(&il->sta_lock);

	चयन (il->stations[sta_id].tid[tid].agg.state) अणु
	हाल IL_EMPTYING_HW_QUEUE_DELBA:
		/* We are reclaiming the last packet of the */
		/* aggregated HW queue */
		अगर (txq_id == tid_data->agg.txq_id &&
		    q->पढ़ो_ptr == q->ग_लिखो_ptr) अणु
			u16 ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
			पूर्णांक tx_fअगरo = il4965_get_fअगरo_from_tid(tid);
			D_HT("HW queue empty: continue DELBA flow\n");
			il4965_txq_agg_disable(il, txq_id, ssn, tx_fअगरo);
			tid_data->agg.state = IL_AGG_OFF;
			ieee80211_stop_tx_ba_cb_irqsafe(il->vअगर, addr, tid);
		पूर्ण
		अवरोध;
	हाल IL_EMPTYING_HW_QUEUE_ADDBA:
		/* We are reclaiming the last packet of the queue */
		अगर (tid_data->tfds_in_queue == 0) अणु
			D_HT("HW queue empty: continue ADDBA flow\n");
			tid_data->agg.state = IL_AGG_ON;
			ieee80211_start_tx_ba_cb_irqsafe(il->vअगर, addr, tid);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
il4965_non_agg_tx_status(काष्ठा il_priv *il, स्थिर u8 *addr1)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा il_station_priv *sta_priv;

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(il->vअगर, addr1);
	अगर (sta) अणु
		sta_priv = (व्योम *)sta->drv_priv;
		/* aव्योम atomic ops अगर this isn't a client */
		अगर (sta_priv->client &&
		    atomic_dec_वापस(&sta_priv->pending_frames) == 0)
			ieee80211_sta_block_awake(il->hw, sta, false);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
il4965_tx_status(काष्ठा il_priv *il, काष्ठा sk_buff *skb, bool is_agg)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (!is_agg)
		il4965_non_agg_tx_status(il, hdr->addr1);

	ieee80211_tx_status_irqsafe(il->hw, skb);
पूर्ण

पूर्णांक
il4965_tx_queue_reclaim(काष्ठा il_priv *il, पूर्णांक txq_id, पूर्णांक idx)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];
	काष्ठा il_queue *q = &txq->q;
	पूर्णांक nमुक्तd = 0;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sk_buff *skb;

	अगर (idx >= q->n_bd || il_queue_used(q, idx) == 0) अणु
		IL_ERR("Read idx for DMA queue txq id (%d), idx %d, "
		       "is out of range [0-%d] %d %d.\n", txq_id, idx, q->n_bd,
		       q->ग_लिखो_ptr, q->पढ़ो_ptr);
		वापस 0;
	पूर्ण

	क्रम (idx = il_queue_inc_wrap(idx, q->n_bd); q->पढ़ो_ptr != idx;
	     q->पढ़ो_ptr = il_queue_inc_wrap(q->पढ़ो_ptr, q->n_bd)) अणु

		skb = txq->skbs[txq->q.पढ़ो_ptr];

		अगर (WARN_ON_ONCE(skb == शून्य))
			जारी;

		hdr = (काष्ठा ieee80211_hdr *) skb->data;
		अगर (ieee80211_is_data_qos(hdr->frame_control))
			nमुक्तd++;

		il4965_tx_status(il, skb, txq_id >= IL4965_FIRST_AMPDU_QUEUE);

		txq->skbs[txq->q.पढ़ो_ptr] = शून्य;
		il->ops->txq_मुक्त_tfd(il, txq);
	पूर्ण
	वापस nमुक्तd;
पूर्ण

/*
 * il4965_tx_status_reply_compressed_ba - Update tx status from block-ack
 *
 * Go through block-ack's bitmap of ACK'd frames, update driver's record of
 * ACK vs. not.  This माला_लो sent to mac80211, then to rate scaling algo.
 */
अटल पूर्णांक
il4965_tx_status_reply_compressed_ba(काष्ठा il_priv *il, काष्ठा il_ht_agg *agg,
				     काष्ठा il_compressed_ba_resp *ba_resp)
अणु
	पूर्णांक i, sh, ack;
	u16 seq_ctl = le16_to_cpu(ba_resp->seq_ctl);
	u16 scd_flow = le16_to_cpu(ba_resp->scd_flow);
	पूर्णांक successes = 0;
	काष्ठा ieee80211_tx_info *info;
	u64 biपंचांगap, sent_biपंचांगap;

	अगर (unlikely(!agg->रुको_क्रम_ba)) अणु
		अगर (unlikely(ba_resp->biपंचांगap))
			IL_ERR("Received BA when not expected\n");
		वापस -EINVAL;
	पूर्ण

	/* Mark that the expected block-ack response arrived */
	agg->रुको_क्रम_ba = 0;
	D_TX_REPLY("BA %d %d\n", agg->start_idx, ba_resp->seq_ctl);

	/* Calculate shअगरt to align block-ack bits with our Tx win bits */
	sh = agg->start_idx - SEQ_TO_IDX(seq_ctl >> 4);
	अगर (sh < 0)		/* tbw something is wrong with indices */
		sh += 0x100;

	अगर (agg->frame_count > (64 - sh)) अणु
		D_TX_REPLY("more frames than bitmap size");
		वापस -1;
	पूर्ण

	/* करोn't use 64-bit values क्रम now */
	biपंचांगap = le64_to_cpu(ba_resp->biपंचांगap) >> sh;

	/* check क्रम success or failure according to the
	 * transmitted biपंचांगap and block-ack biपंचांगap */
	sent_biपंचांगap = biपंचांगap & agg->biपंचांगap;

	/* For each frame attempted in aggregation,
	 * update driver's record of tx frame's status. */
	i = 0;
	जबतक (sent_biपंचांगap) अणु
		ack = sent_biपंचांगap & 1ULL;
		successes += ack;
		D_TX_REPLY("%s ON i=%d idx=%d raw=%d\n", ack ? "ACK" : "NACK",
			   i, (agg->start_idx + i) & 0xff, agg->start_idx + i);
		sent_biपंचांगap >>= 1;
		++i;
	पूर्ण

	D_TX_REPLY("Bitmap %llx\n", (अचिन्हित दीर्घ दीर्घ)biपंचांगap);

	info = IEEE80211_SKB_CB(il->txq[scd_flow].skbs[agg->start_idx]);
	स_रखो(&info->status, 0, माप(info->status));
	info->flags |= IEEE80211_TX_STAT_ACK;
	info->flags |= IEEE80211_TX_STAT_AMPDU;
	info->status.ampdu_ack_len = successes;
	info->status.ampdu_len = agg->frame_count;
	il4965_hwrate_to_tx_control(il, agg->rate_n_flags, info);

	वापस 0;
पूर्ण

अटल अंतरभूत bool
il4965_is_tx_success(u32 status)
अणु
	status &= TX_STATUS_MSK;
	वापस (status == TX_STATUS_SUCCESS || status == TX_STATUS_सूचीECT_DONE);
पूर्ण

अटल u8
il4965_find_station(काष्ठा il_priv *il, स्थिर u8 *addr)
अणु
	पूर्णांक i;
	पूर्णांक start = 0;
	पूर्णांक ret = IL_INVALID_STATION;
	अचिन्हित दीर्घ flags;

	अगर (il->iw_mode == NL80211_IFTYPE_ADHOC)
		start = IL_STA_ID;

	अगर (is_broadcast_ether_addr(addr))
		वापस il->hw_params.bcast_id;

	spin_lock_irqsave(&il->sta_lock, flags);
	क्रम (i = start; i < il->hw_params.max_stations; i++)
		अगर (il->stations[i].used &&
		    ether_addr_equal(il->stations[i].sta.sta.addr, addr)) अणु
			ret = i;
			जाओ out;
		पूर्ण

	D_ASSOC("can not find STA %pM total %d\n", addr, il->num_stations);

out:
	/*
	 * It may be possible that more commands पूर्णांकeracting with stations
	 * arrive beक्रमe we completed processing the adding of
	 * station
	 */
	अगर (ret != IL_INVALID_STATION &&
	    (!(il->stations[ret].used & IL_STA_UCODE_ACTIVE) ||
	      (il->stations[ret].used & IL_STA_UCODE_INPROGRESS))) अणु
		IL_ERR("Requested station info for sta %d before ready.\n",
		       ret);
		ret = IL_INVALID_STATION;
	पूर्ण
	spin_unlock_irqrestore(&il->sta_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक
il4965_get_ra_sta_id(काष्ठा il_priv *il, काष्ठा ieee80211_hdr *hdr)
अणु
	अगर (il->iw_mode == NL80211_IFTYPE_STATION)
		वापस IL_AP_ID;
	अन्यथा अणु
		u8 *da = ieee80211_get_DA(hdr);

		वापस il4965_find_station(il, da);
	पूर्ण
पूर्ण

अटल अंतरभूत u32
il4965_get_scd_ssn(काष्ठा il4965_tx_resp *tx_resp)
अणु
	वापस le32_to_cpup(&tx_resp->u.status +
			    tx_resp->frame_count) & IEEE80211_MAX_SN;
पूर्ण

अटल अंतरभूत u32
il4965_tx_status_to_mac80211(u32 status)
अणु
	status &= TX_STATUS_MSK;

	चयन (status) अणु
	हाल TX_STATUS_SUCCESS:
	हाल TX_STATUS_सूचीECT_DONE:
		वापस IEEE80211_TX_STAT_ACK;
	हाल TX_STATUS_FAIL_DEST_PS:
		वापस IEEE80211_TX_STAT_TX_FILTERED;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * il4965_tx_status_reply_tx - Handle Tx response क्रम frames in aggregation queue
 */
अटल पूर्णांक
il4965_tx_status_reply_tx(काष्ठा il_priv *il, काष्ठा il_ht_agg *agg,
			  काष्ठा il4965_tx_resp *tx_resp, पूर्णांक txq_id,
			  u16 start_idx)
अणु
	u16 status;
	काष्ठा agg_tx_status *frame_status = tx_resp->u.agg_status;
	काष्ठा ieee80211_tx_info *info = शून्य;
	काष्ठा ieee80211_hdr *hdr = शून्य;
	u32 rate_n_flags = le32_to_cpu(tx_resp->rate_n_flags);
	पूर्णांक i, sh, idx;
	u16 seq;
	अगर (agg->रुको_क्रम_ba)
		D_TX_REPLY("got tx response w/o block-ack\n");

	agg->frame_count = tx_resp->frame_count;
	agg->start_idx = start_idx;
	agg->rate_n_flags = rate_n_flags;
	agg->biपंचांगap = 0;

	/* num frames attempted by Tx command */
	अगर (agg->frame_count == 1) अणु
		/* Only one frame was attempted; no block-ack will arrive */
		status = le16_to_cpu(frame_status[0].status);
		idx = start_idx;

		D_TX_REPLY("FrameCnt = %d, StartIdx=%d idx=%d\n",
			   agg->frame_count, agg->start_idx, idx);

		info = IEEE80211_SKB_CB(il->txq[txq_id].skbs[idx]);
		info->status.rates[0].count = tx_resp->failure_frame + 1;
		info->flags &= ~IEEE80211_TX_CTL_AMPDU;
		info->flags |= il4965_tx_status_to_mac80211(status);
		il4965_hwrate_to_tx_control(il, rate_n_flags, info);

		D_TX_REPLY("1 Frame 0x%x failure :%d\n", status & 0xff,
			   tx_resp->failure_frame);
		D_TX_REPLY("Rate Info rate_n_flags=%x\n", rate_n_flags);

		agg->रुको_क्रम_ba = 0;
	पूर्ण अन्यथा अणु
		/* Two or more frames were attempted; expect block-ack */
		u64 biपंचांगap = 0;
		पूर्णांक start = agg->start_idx;
		काष्ठा sk_buff *skb;

		/* Conकाष्ठा bit-map of pending frames within Tx win */
		क्रम (i = 0; i < agg->frame_count; i++) अणु
			u16 sc;
			status = le16_to_cpu(frame_status[i].status);
			seq = le16_to_cpu(frame_status[i].sequence);
			idx = SEQ_TO_IDX(seq);
			txq_id = SEQ_TO_QUEUE(seq);

			अगर (status &
			    (AGG_TX_STATE_FEW_BYTES_MSK |
			     AGG_TX_STATE_ABORT_MSK))
				जारी;

			D_TX_REPLY("FrameCnt = %d, txq_id=%d idx=%d\n",
				   agg->frame_count, txq_id, idx);

			skb = il->txq[txq_id].skbs[idx];
			अगर (WARN_ON_ONCE(skb == शून्य))
				वापस -1;
			hdr = (काष्ठा ieee80211_hdr *) skb->data;

			sc = le16_to_cpu(hdr->seq_ctrl);
			अगर (idx != (IEEE80211_SEQ_TO_SN(sc) & 0xff)) अणु
				IL_ERR("BUG_ON idx doesn't match seq control"
				       " idx=%d, seq_idx=%d, seq=%d\n", idx,
				       IEEE80211_SEQ_TO_SN(sc), hdr->seq_ctrl);
				वापस -1;
			पूर्ण

			D_TX_REPLY("AGG Frame i=%d idx %d seq=%d\n", i, idx,
				   IEEE80211_SEQ_TO_SN(sc));

			sh = idx - start;
			अगर (sh > 64) अणु
				sh = (start - idx) + 0xff;
				biपंचांगap = biपंचांगap << sh;
				sh = 0;
				start = idx;
			पूर्ण अन्यथा अगर (sh < -64)
				sh = 0xff - (start - idx);
			अन्यथा अगर (sh < 0) अणु
				sh = start - idx;
				start = idx;
				biपंचांगap = biपंचांगap << sh;
				sh = 0;
			पूर्ण
			biपंचांगap |= 1ULL << sh;
			D_TX_REPLY("start=%d bitmap=0x%llx\n", start,
				   (अचिन्हित दीर्घ दीर्घ)biपंचांगap);
		पूर्ण

		agg->biपंचांगap = biपंचांगap;
		agg->start_idx = start;
		D_TX_REPLY("Frames %d start_idx=%d bitmap=0x%llx\n",
			   agg->frame_count, agg->start_idx,
			   (अचिन्हित दीर्घ दीर्घ)agg->biपंचांगap);

		अगर (biपंचांगap)
			agg->रुको_क्रम_ba = 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * il4965_hdl_tx - Handle standard (non-aggregation) Tx response
 */
अटल व्योम
il4965_hdl_tx(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	पूर्णांक txq_id = SEQ_TO_QUEUE(sequence);
	पूर्णांक idx = SEQ_TO_IDX(sequence);
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा il4965_tx_resp *tx_resp = (व्योम *)&pkt->u.raw[0];
	u32 status = le32_to_cpu(tx_resp->u.status);
	पूर्णांक tid;
	पूर्णांक sta_id;
	पूर्णांक मुक्तd;
	u8 *qc = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (idx >= txq->q.n_bd || il_queue_used(&txq->q, idx) == 0) अणु
		IL_ERR("Read idx for DMA queue txq_id (%d) idx %d "
		       "is out of range [0-%d] %d %d\n", txq_id, idx,
		       txq->q.n_bd, txq->q.ग_लिखो_ptr, txq->q.पढ़ो_ptr);
		वापस;
	पूर्ण

	txq->समय_stamp = jअगरfies;

	skb = txq->skbs[txq->q.पढ़ो_ptr];
	info = IEEE80211_SKB_CB(skb);
	स_रखो(&info->status, 0, माप(info->status));

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & 0xf;
	पूर्ण

	sta_id = il4965_get_ra_sta_id(il, hdr);
	अगर (txq->sched_retry && unlikely(sta_id == IL_INVALID_STATION)) अणु
		IL_ERR("Station not known\n");
		वापस;
	पूर्ण

	/*
	 * Firmware will not transmit frame on passive channel, अगर it not yet
	 * received some valid frame on that channel. When this error happen
	 * we have to रुको until firmware will unblock itself i.e. when we
	 * note received beacon or other frame. We unblock queues in
	 * il4965_pass_packet_to_mac80211 or in il_mac_bss_info_changed.
	 */
	अगर (unlikely((status & TX_STATUS_MSK) == TX_STATUS_FAIL_PASSIVE_NO_RX) &&
	    il->iw_mode == NL80211_IFTYPE_STATION) अणु
		il_stop_queues_by_reason(il, IL_STOP_REASON_PASSIVE);
		D_INFO("Stopped queues - RX waiting on passive channel\n");
	पूर्ण

	spin_lock_irqsave(&il->sta_lock, flags);
	अगर (txq->sched_retry) अणु
		स्थिर u32 scd_ssn = il4965_get_scd_ssn(tx_resp);
		काष्ठा il_ht_agg *agg;

		अगर (WARN_ON(!qc))
			जाओ out;

		agg = &il->stations[sta_id].tid[tid].agg;

		il4965_tx_status_reply_tx(il, agg, tx_resp, txq_id, idx);

		/* check अगर BAR is needed */
		अगर (tx_resp->frame_count == 1 &&
		    !il4965_is_tx_success(status))
			info->flags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;

		अगर (txq->q.पढ़ो_ptr != (scd_ssn & 0xff)) अणु
			idx = il_queue_dec_wrap(scd_ssn & 0xff, txq->q.n_bd);
			D_TX_REPLY("Retry scheduler reclaim scd_ssn "
				   "%d idx %d\n", scd_ssn, idx);
			मुक्तd = il4965_tx_queue_reclaim(il, txq_id, idx);
			il4965_मुक्त_tfds_in_queue(il, sta_id, tid, मुक्तd);

			अगर (il->mac80211_रेजिस्टरed &&
			    il_queue_space(&txq->q) > txq->q.low_mark &&
			    agg->state != IL_EMPTYING_HW_QUEUE_DELBA)
				il_wake_queue(il, txq);
		पूर्ण
	पूर्ण अन्यथा अणु
		info->status.rates[0].count = tx_resp->failure_frame + 1;
		info->flags |= il4965_tx_status_to_mac80211(status);
		il4965_hwrate_to_tx_control(il,
					    le32_to_cpu(tx_resp->rate_n_flags),
					    info);

		D_TX_REPLY("TXQ %d status %s (0x%08x) "
			   "rate_n_flags 0x%x retries %d\n", txq_id,
			   il4965_get_tx_fail_reason(status), status,
			   le32_to_cpu(tx_resp->rate_n_flags),
			   tx_resp->failure_frame);

		मुक्तd = il4965_tx_queue_reclaim(il, txq_id, idx);
		अगर (qc && likely(sta_id != IL_INVALID_STATION))
			il4965_मुक्त_tfds_in_queue(il, sta_id, tid, मुक्तd);
		अन्यथा अगर (sta_id == IL_INVALID_STATION)
			D_TX_REPLY("Station not known\n");

		अगर (il->mac80211_रेजिस्टरed &&
		    il_queue_space(&txq->q) > txq->q.low_mark)
			il_wake_queue(il, txq);
	पूर्ण
out:
	अगर (qc && likely(sta_id != IL_INVALID_STATION))
		il4965_txq_check_empty(il, sta_id, tid, txq_id);

	il4965_check_पात_status(il, tx_resp->frame_count, status);

	spin_unlock_irqrestore(&il->sta_lock, flags);
पूर्ण

/*
 * translate ucode response to mac80211 tx status control values
 */
व्योम
il4965_hwrate_to_tx_control(काष्ठा il_priv *il, u32 rate_n_flags,
			    काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा ieee80211_tx_rate *r = &info->status.rates[0];

	info->status.antenna =
	    ((rate_n_flags & RATE_MCS_ANT_ABC_MSK) >> RATE_MCS_ANT_POS);
	अगर (rate_n_flags & RATE_MCS_HT_MSK)
		r->flags |= IEEE80211_TX_RC_MCS;
	अगर (rate_n_flags & RATE_MCS_GF_MSK)
		r->flags |= IEEE80211_TX_RC_GREEN_FIELD;
	अगर (rate_n_flags & RATE_MCS_HT40_MSK)
		r->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
	अगर (rate_n_flags & RATE_MCS_DUP_MSK)
		r->flags |= IEEE80211_TX_RC_DUP_DATA;
	अगर (rate_n_flags & RATE_MCS_SGI_MSK)
		r->flags |= IEEE80211_TX_RC_SHORT_GI;
	r->idx = il4965_hwrate_to_mac80211_idx(rate_n_flags, info->band);
पूर्ण

/*
 * il4965_hdl_compressed_ba - Handler क्रम N_COMPRESSED_BA
 *
 * Handles block-acknowledge notअगरication from device, which reports success
 * of frames sent via aggregation.
 */
अटल व्योम
il4965_hdl_compressed_ba(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_compressed_ba_resp *ba_resp = &pkt->u.compressed_ba;
	काष्ठा il_tx_queue *txq = शून्य;
	काष्ठा il_ht_agg *agg;
	पूर्णांक idx;
	पूर्णांक sta_id;
	पूर्णांक tid;
	अचिन्हित दीर्घ flags;

	/* "flow" corresponds to Tx queue */
	u16 scd_flow = le16_to_cpu(ba_resp->scd_flow);

	/* "ssn" is start of block-ack Tx win, corresponds to idx
	 * (in Tx queue's circular buffer) of first TFD/frame in win */
	u16 ba_resp_scd_ssn = le16_to_cpu(ba_resp->scd_ssn);

	अगर (scd_flow >= il->hw_params.max_txq_num) अणु
		IL_ERR("BUG_ON scd_flow is bigger than number of queues\n");
		वापस;
	पूर्ण

	txq = &il->txq[scd_flow];
	sta_id = ba_resp->sta_id;
	tid = ba_resp->tid;
	agg = &il->stations[sta_id].tid[tid].agg;
	अगर (unlikely(agg->txq_id != scd_flow)) अणु
		/*
		 * FIXME: this is a uCode bug which need to be addressed,
		 * log the inक्रमmation and वापस क्रम now!
		 * since it is possible happen very often and in order
		 * not to fill the syslog, करोn't enable the logging by शेष
		 */
		D_TX_REPLY("BA scd_flow %d does not match txq_id %d\n",
			   scd_flow, agg->txq_id);
		वापस;
	पूर्ण

	/* Find idx just beक्रमe block-ack win */
	idx = il_queue_dec_wrap(ba_resp_scd_ssn & 0xff, txq->q.n_bd);

	spin_lock_irqsave(&il->sta_lock, flags);

	D_TX_REPLY("N_COMPRESSED_BA [%d] Received from %pM, " "sta_id = %d\n",
		   agg->रुको_क्रम_ba, (u8 *) &ba_resp->sta_addr_lo32,
		   ba_resp->sta_id);
	D_TX_REPLY("TID = %d, SeqCtl = %d, bitmap = 0x%llx," "scd_flow = "
		   "%d, scd_ssn = %d\n", ba_resp->tid, ba_resp->seq_ctl,
		   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(ba_resp->biपंचांगap),
		   ba_resp->scd_flow, ba_resp->scd_ssn);
	D_TX_REPLY("DAT start_idx = %d, bitmap = 0x%llx\n", agg->start_idx,
		   (अचिन्हित दीर्घ दीर्घ)agg->biपंचांगap);

	/* Update driver's record of ACK vs. not क्रम each frame in win */
	il4965_tx_status_reply_compressed_ba(il, agg, ba_resp);

	/* Release all TFDs beक्रमe the SSN, i.e. all TFDs in front of
	 * block-ack win (we assume that they've been successfully
	 * transmitted ... अगर not, it's too late anyway). */
	अगर (txq->q.पढ़ो_ptr != (ba_resp_scd_ssn & 0xff)) अणु
		/* calculate mac80211 ampdu sw queue to wake */
		पूर्णांक मुक्तd = il4965_tx_queue_reclaim(il, scd_flow, idx);
		il4965_मुक्त_tfds_in_queue(il, sta_id, tid, मुक्तd);

		अगर (il_queue_space(&txq->q) > txq->q.low_mark &&
		    il->mac80211_रेजिस्टरed &&
		    agg->state != IL_EMPTYING_HW_QUEUE_DELBA)
			il_wake_queue(il, txq);

		il4965_txq_check_empty(il, sta_id, tid, scd_flow);
	पूर्ण

	spin_unlock_irqrestore(&il->sta_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
स्थिर अक्षर *
il4965_get_tx_fail_reason(u32 status)
अणु
#घोषणा TX_STATUS_FAIL(x) हाल TX_STATUS_FAIL_ ## x: वापस #x
#घोषणा TX_STATUS_POSTPONE(x) हाल TX_STATUS_POSTPONE_ ## x: वापस #x

	चयन (status & TX_STATUS_MSK) अणु
	हाल TX_STATUS_SUCCESS:
		वापस "SUCCESS";
		TX_STATUS_POSTPONE(DELAY);
		TX_STATUS_POSTPONE(FEW_BYTES);
		TX_STATUS_POSTPONE(QUIET_PERIOD);
		TX_STATUS_POSTPONE(CALC_TTAK);
		TX_STATUS_FAIL(INTERNAL_CROSSED_RETRY);
		TX_STATUS_FAIL(SHORT_LIMIT);
		TX_STATUS_FAIL(LONG_LIMIT);
		TX_STATUS_FAIL(FIFO_UNDERRUN);
		TX_STATUS_FAIL(DRAIN_FLOW);
		TX_STATUS_FAIL(RFKILL_FLUSH);
		TX_STATUS_FAIL(LIFE_EXPIRE);
		TX_STATUS_FAIL(DEST_PS);
		TX_STATUS_FAIL(HOST_ABORTED);
		TX_STATUS_FAIL(BT_RETRY);
		TX_STATUS_FAIL(STA_INVALID);
		TX_STATUS_FAIL(FRAG_DROPPED);
		TX_STATUS_FAIL(TID_DISABLE);
		TX_STATUS_FAIL(FIFO_FLUSHED);
		TX_STATUS_FAIL(INSUFFICIENT_CF_POLL);
		TX_STATUS_FAIL(PASSIVE_NO_RX);
		TX_STATUS_FAIL(NO_BEACON_ON_RADAR);
	पूर्ण

	वापस "UNKNOWN";

#अघोषित TX_STATUS_FAIL
#अघोषित TX_STATUS_POSTPONE
पूर्ण
#पूर्ण_अगर /* CONFIG_IWLEGACY_DEBUG */

अटल काष्ठा il_link_quality_cmd *
il4965_sta_alloc_lq(काष्ठा il_priv *il, u8 sta_id)
अणु
	पूर्णांक i, r;
	काष्ठा il_link_quality_cmd *link_cmd;
	u32 rate_flags = 0;
	__le32 rate_n_flags;

	link_cmd = kzalloc(माप(काष्ठा il_link_quality_cmd), GFP_KERNEL);
	अगर (!link_cmd) अणु
		IL_ERR("Unable to allocate memory for LQ cmd.\n");
		वापस शून्य;
	पूर्ण
	/* Set up the rate scaling to start at selected rate, fall back
	 * all the way करोwn to 1M in IEEE order, and then spin on 1M */
	अगर (il->band == NL80211_BAND_5GHZ)
		r = RATE_6M_IDX;
	अन्यथा
		r = RATE_1M_IDX;

	अगर (r >= IL_FIRST_CCK_RATE && r <= IL_LAST_CCK_RATE)
		rate_flags |= RATE_MCS_CCK_MSK;

	rate_flags |=
	    il4965_first_antenna(il->hw_params.
				 valid_tx_ant) << RATE_MCS_ANT_POS;
	rate_n_flags = cpu_to_le32(il_rates[r].plcp | rate_flags);
	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++)
		link_cmd->rs_table[i].rate_n_flags = rate_n_flags;

	link_cmd->general_params.single_stream_ant_msk =
	    il4965_first_antenna(il->hw_params.valid_tx_ant);

	link_cmd->general_params.dual_stream_ant_msk =
	    il->hw_params.valid_tx_ant & ~il4965_first_antenna(il->hw_params.
							       valid_tx_ant);
	अगर (!link_cmd->general_params.dual_stream_ant_msk) अणु
		link_cmd->general_params.dual_stream_ant_msk = ANT_AB;
	पूर्ण अन्यथा अगर (il4965_num_of_ant(il->hw_params.valid_tx_ant) == 2) अणु
		link_cmd->general_params.dual_stream_ant_msk =
		    il->hw_params.valid_tx_ant;
	पूर्ण

	link_cmd->agg_params.agg_dis_start_th = LINK_QUAL_AGG_DISABLE_START_DEF;
	link_cmd->agg_params.agg_समय_limit =
	    cpu_to_le16(LINK_QUAL_AGG_TIME_LIMIT_DEF);

	link_cmd->sta_id = sta_id;

	वापस link_cmd;
पूर्ण

/*
 * il4965_add_bssid_station - Add the special IBSS BSSID station
 *
 * Function sleeps.
 */
पूर्णांक
il4965_add_bssid_station(काष्ठा il_priv *il, स्थिर u8 *addr, u8 *sta_id_r)
अणु
	पूर्णांक ret;
	u8 sta_id;
	काष्ठा il_link_quality_cmd *link_cmd;
	अचिन्हित दीर्घ flags;

	अगर (sta_id_r)
		*sta_id_r = IL_INVALID_STATION;

	ret = il_add_station_common(il, addr, 0, शून्य, &sta_id);
	अगर (ret) अणु
		IL_ERR("Unable to add station %pM\n", addr);
		वापस ret;
	पूर्ण

	अगर (sta_id_r)
		*sta_id_r = sta_id;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].used |= IL_STA_LOCAL;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	/* Set up शेष rate scaling table in device's station table */
	link_cmd = il4965_sta_alloc_lq(il, sta_id);
	अगर (!link_cmd) अणु
		IL_ERR("Unable to initialize rate scaling for station %pM.\n",
		       addr);
		वापस -ENOMEM;
	पूर्ण

	ret = il_send_lq_cmd(il, link_cmd, CMD_SYNC, true);
	अगर (ret)
		IL_ERR("Link quality command failed (%d)\n", ret);

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].lq = link_cmd;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
il4965_अटल_wepkey_cmd(काष्ठा il_priv *il, bool send_अगर_empty)
अणु
	पूर्णांक i;
	u8 buff[माप(काष्ठा il_wep_cmd) +
		माप(काष्ठा il_wep_key) * WEP_KEYS_MAX];
	काष्ठा il_wep_cmd *wep_cmd = (काष्ठा il_wep_cmd *)buff;
	माप_प्रकार cmd_size = माप(काष्ठा il_wep_cmd);
	काष्ठा il_host_cmd cmd = अणु
		.id = C_WEPKEY,
		.data = wep_cmd,
		.flags = CMD_SYNC,
	पूर्ण;
	bool not_empty = false;

	might_sleep();

	स_रखो(wep_cmd, 0,
	       cmd_size + (माप(काष्ठा il_wep_key) * WEP_KEYS_MAX));

	क्रम (i = 0; i < WEP_KEYS_MAX; i++) अणु
		u8 key_size = il->_4965.wep_keys[i].key_size;

		wep_cmd->key[i].key_idx = i;
		अगर (key_size) अणु
			wep_cmd->key[i].key_offset = i;
			not_empty = true;
		पूर्ण अन्यथा
			wep_cmd->key[i].key_offset = WEP_INVALID_OFFSET;

		wep_cmd->key[i].key_size = key_size;
		स_नकल(&wep_cmd->key[i].key[3], il->_4965.wep_keys[i].key, key_size);
	पूर्ण

	wep_cmd->global_key_type = WEP_KEY_WEP_TYPE;
	wep_cmd->num_keys = WEP_KEYS_MAX;

	cmd_size += माप(काष्ठा il_wep_key) * WEP_KEYS_MAX;
	cmd.len = cmd_size;

	अगर (not_empty || send_अगर_empty)
		वापस il_send_cmd(il, &cmd);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक
il4965_restore_शेष_wep_keys(काष्ठा il_priv *il)
अणु
	lockdep_निश्चित_held(&il->mutex);

	वापस il4965_अटल_wepkey_cmd(il, false);
पूर्ण

पूर्णांक
il4965_हटाओ_शेष_wep_key(काष्ठा il_priv *il,
			      काष्ठा ieee80211_key_conf *keyconf)
अणु
	पूर्णांक ret;
	पूर्णांक idx = keyconf->keyidx;

	lockdep_निश्चित_held(&il->mutex);

	D_WEP("Removing default WEP key: idx=%d\n", idx);

	स_रखो(&il->_4965.wep_keys[idx], 0, माप(काष्ठा il_wep_key));
	अगर (il_is_rfसमाप्त(il)) अणु
		D_WEP("Not sending C_WEPKEY command due to RFKILL.\n");
		/* but keys in device are clear anyway so वापस success */
		वापस 0;
	पूर्ण
	ret = il4965_अटल_wepkey_cmd(il, 1);
	D_WEP("Remove default WEP key: idx=%d ret=%d\n", idx, ret);

	वापस ret;
पूर्ण

पूर्णांक
il4965_set_शेष_wep_key(काष्ठा il_priv *il,
			   काष्ठा ieee80211_key_conf *keyconf)
अणु
	पूर्णांक ret;
	पूर्णांक len = keyconf->keylen;
	पूर्णांक idx = keyconf->keyidx;

	lockdep_निश्चित_held(&il->mutex);

	अगर (len != WEP_KEY_LEN_128 && len != WEP_KEY_LEN_64) अणु
		D_WEP("Bad WEP key length %d\n", keyconf->keylen);
		वापस -EINVAL;
	पूर्ण

	keyconf->flags &= ~IEEE80211_KEY_FLAG_GENERATE_IV;
	keyconf->hw_key_idx = HW_KEY_DEFAULT;
	il->stations[IL_AP_ID].keyinfo.cipher = keyconf->cipher;

	il->_4965.wep_keys[idx].key_size = len;
	स_नकल(&il->_4965.wep_keys[idx].key, &keyconf->key, len);

	ret = il4965_अटल_wepkey_cmd(il, false);

	D_WEP("Set default WEP key: len=%d idx=%d ret=%d\n", len, idx, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
il4965_set_wep_dynamic_key_info(काष्ठा il_priv *il,
				काष्ठा ieee80211_key_conf *keyconf, u8 sta_id)
अणु
	अचिन्हित दीर्घ flags;
	__le16 key_flags = 0;
	काष्ठा il_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&il->mutex);

	keyconf->flags &= ~IEEE80211_KEY_FLAG_GENERATE_IV;

	key_flags |= (STA_KEY_FLG_WEP | STA_KEY_FLG_MAP_KEY_MSK);
	key_flags |= cpu_to_le16(keyconf->keyidx << STA_KEY_FLG_KEYID_POS);
	key_flags &= ~STA_KEY_FLG_INVALID;

	अगर (keyconf->keylen == WEP_KEY_LEN_128)
		key_flags |= STA_KEY_FLG_KEY_SIZE_MSK;

	अगर (sta_id == il->hw_params.bcast_id)
		key_flags |= STA_KEY_MULTICAST_MSK;

	spin_lock_irqsave(&il->sta_lock, flags);

	il->stations[sta_id].keyinfo.cipher = keyconf->cipher;
	il->stations[sta_id].keyinfo.keylen = keyconf->keylen;
	il->stations[sta_id].keyinfo.keyidx = keyconf->keyidx;

	स_नकल(il->stations[sta_id].keyinfo.key, keyconf->key, keyconf->keylen);

	स_नकल(&il->stations[sta_id].sta.key.key[3], keyconf->key,
	       keyconf->keylen);

	अगर ((il->stations[sta_id].sta.key.
	     key_flags & STA_KEY_FLG_ENCRYPT_MSK) == STA_KEY_FLG_NO_ENC)
		il->stations[sta_id].sta.key.key_offset =
		    il_get_मुक्त_ucode_key_idx(il);
	/* अन्यथा, we are overriding an existing key => no need to allocated room
	 * in uCode. */

	WARN(il->stations[sta_id].sta.key.key_offset == WEP_INVALID_OFFSET,
	     "no space for a new key");

	il->stations[sta_id].sta.key.key_flags = key_flags;
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;

	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस il_send_add_sta(il, &sta_cmd, CMD_SYNC);
पूर्ण

अटल पूर्णांक
il4965_set_ccmp_dynamic_key_info(काष्ठा il_priv *il,
				 काष्ठा ieee80211_key_conf *keyconf, u8 sta_id)
अणु
	अचिन्हित दीर्घ flags;
	__le16 key_flags = 0;
	काष्ठा il_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&il->mutex);

	key_flags |= (STA_KEY_FLG_CCMP | STA_KEY_FLG_MAP_KEY_MSK);
	key_flags |= cpu_to_le16(keyconf->keyidx << STA_KEY_FLG_KEYID_POS);
	key_flags &= ~STA_KEY_FLG_INVALID;

	अगर (sta_id == il->hw_params.bcast_id)
		key_flags |= STA_KEY_MULTICAST_MSK;

	keyconf->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].keyinfo.cipher = keyconf->cipher;
	il->stations[sta_id].keyinfo.keylen = keyconf->keylen;

	स_नकल(il->stations[sta_id].keyinfo.key, keyconf->key, keyconf->keylen);

	स_नकल(il->stations[sta_id].sta.key.key, keyconf->key, keyconf->keylen);

	अगर ((il->stations[sta_id].sta.key.
	     key_flags & STA_KEY_FLG_ENCRYPT_MSK) == STA_KEY_FLG_NO_ENC)
		il->stations[sta_id].sta.key.key_offset =
		    il_get_मुक्त_ucode_key_idx(il);
	/* अन्यथा, we are overriding an existing key => no need to allocated room
	 * in uCode. */

	WARN(il->stations[sta_id].sta.key.key_offset == WEP_INVALID_OFFSET,
	     "no space for a new key");

	il->stations[sta_id].sta.key.key_flags = key_flags;
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;

	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस il_send_add_sta(il, &sta_cmd, CMD_SYNC);
पूर्ण

अटल पूर्णांक
il4965_set_tkip_dynamic_key_info(काष्ठा il_priv *il,
				 काष्ठा ieee80211_key_conf *keyconf, u8 sta_id)
अणु
	अचिन्हित दीर्घ flags;
	__le16 key_flags = 0;

	key_flags |= (STA_KEY_FLG_TKIP | STA_KEY_FLG_MAP_KEY_MSK);
	key_flags |= cpu_to_le16(keyconf->keyidx << STA_KEY_FLG_KEYID_POS);
	key_flags &= ~STA_KEY_FLG_INVALID;

	अगर (sta_id == il->hw_params.bcast_id)
		key_flags |= STA_KEY_MULTICAST_MSK;

	keyconf->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
	keyconf->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;

	spin_lock_irqsave(&il->sta_lock, flags);

	il->stations[sta_id].keyinfo.cipher = keyconf->cipher;
	il->stations[sta_id].keyinfo.keylen = 16;

	अगर ((il->stations[sta_id].sta.key.
	     key_flags & STA_KEY_FLG_ENCRYPT_MSK) == STA_KEY_FLG_NO_ENC)
		il->stations[sta_id].sta.key.key_offset =
		    il_get_मुक्त_ucode_key_idx(il);
	/* अन्यथा, we are overriding an existing key => no need to allocated room
	 * in uCode. */

	WARN(il->stations[sta_id].sta.key.key_offset == WEP_INVALID_OFFSET,
	     "no space for a new key");

	il->stations[sta_id].sta.key.key_flags = key_flags;

	/* This copy is acutally not needed: we get the key with each TX */
	स_नकल(il->stations[sta_id].keyinfo.key, keyconf->key, 16);

	स_नकल(il->stations[sta_id].sta.key.key, keyconf->key, 16);

	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस 0;
पूर्ण

व्योम
il4965_update_tkip_key(काष्ठा il_priv *il, काष्ठा ieee80211_key_conf *keyconf,
		       काष्ठा ieee80211_sta *sta, u32 iv32, u16 *phase1key)
अणु
	u8 sta_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (il_scan_cancel(il)) अणु
		/* cancel scan failed, just live w/ bad key and rely
		   briefly on SW decryption */
		वापस;
	पूर्ण

	sta_id = il_sta_id_or_broadcast(il, sta);
	अगर (sta_id == IL_INVALID_STATION)
		वापस;

	spin_lock_irqsave(&il->sta_lock, flags);

	il->stations[sta_id].sta.key.tkip_rx_tsc_byte2 = (u8) iv32;

	क्रम (i = 0; i < 5; i++)
		il->stations[sta_id].sta.key.tkip_rx_ttak[i] =
		    cpu_to_le16(phase1key[i]);

	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;

	il_send_add_sta(il, &il->stations[sta_id].sta, CMD_ASYNC);

	spin_unlock_irqrestore(&il->sta_lock, flags);
पूर्ण

पूर्णांक
il4965_हटाओ_dynamic_key(काष्ठा il_priv *il,
			  काष्ठा ieee80211_key_conf *keyconf, u8 sta_id)
अणु
	अचिन्हित दीर्घ flags;
	u16 key_flags;
	u8 keyidx;
	काष्ठा il_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&il->mutex);

	il->_4965.key_mapping_keys--;

	spin_lock_irqsave(&il->sta_lock, flags);
	key_flags = le16_to_cpu(il->stations[sta_id].sta.key.key_flags);
	keyidx = (key_flags >> STA_KEY_FLG_KEYID_POS) & 0x3;

	D_WEP("Remove dynamic key: idx=%d sta=%d\n", keyconf->keyidx, sta_id);

	अगर (keyconf->keyidx != keyidx) अणु
		/* We need to हटाओ a key with idx dअगरferent that the one
		 * in the uCode. This means that the key we need to हटाओ has
		 * been replaced by another one with dअगरferent idx.
		 * Don't करो anything and वापस ok
		 */
		spin_unlock_irqrestore(&il->sta_lock, flags);
		वापस 0;
	पूर्ण

	अगर (il->stations[sta_id].sta.key.key_flags & STA_KEY_FLG_INVALID) अणु
		IL_WARN("Removing wrong key %d 0x%x\n", keyconf->keyidx,
			key_flags);
		spin_unlock_irqrestore(&il->sta_lock, flags);
		वापस 0;
	पूर्ण

	अगर (!test_and_clear_bit
	    (il->stations[sta_id].sta.key.key_offset, &il->ucode_key_table))
		IL_ERR("idx %d not used in uCode key table.\n",
		       il->stations[sta_id].sta.key.key_offset);
	स_रखो(&il->stations[sta_id].keyinfo, 0, माप(काष्ठा il_hw_key));
	स_रखो(&il->stations[sta_id].sta.key, 0, माप(काष्ठा il4965_keyinfo));
	il->stations[sta_id].sta.key.key_flags =
	    STA_KEY_FLG_NO_ENC | STA_KEY_FLG_INVALID;
	il->stations[sta_id].sta.key.key_offset = keyconf->hw_key_idx;
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;

	अगर (il_is_rfसमाप्त(il)) अणु
		D_WEP
		    ("Not sending C_ADD_STA command because RFKILL enabled.\n");
		spin_unlock_irqrestore(&il->sta_lock, flags);
		वापस 0;
	पूर्ण
	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस il_send_add_sta(il, &sta_cmd, CMD_SYNC);
पूर्ण

पूर्णांक
il4965_set_dynamic_key(काष्ठा il_priv *il, काष्ठा ieee80211_key_conf *keyconf,
		       u8 sta_id)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&il->mutex);

	il->_4965.key_mapping_keys++;
	keyconf->hw_key_idx = HW_KEY_DYNAMIC;

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		ret =
		    il4965_set_ccmp_dynamic_key_info(il, keyconf, sta_id);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		ret =
		    il4965_set_tkip_dynamic_key_info(il, keyconf, sta_id);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		ret = il4965_set_wep_dynamic_key_info(il, keyconf, sta_id);
		अवरोध;
	शेष:
		IL_ERR("Unknown alg: %s cipher = %x\n", __func__,
		       keyconf->cipher);
		ret = -EINVAL;
	पूर्ण

	D_WEP("Set dynamic key: cipher=%x len=%d idx=%d sta=%d ret=%d\n",
	      keyconf->cipher, keyconf->keylen, keyconf->keyidx, sta_id, ret);

	वापस ret;
पूर्ण

/*
 * il4965_alloc_bcast_station - add broadcast station पूर्णांकo driver's station table.
 *
 * This adds the broadcast station पूर्णांकo the driver's station table
 * and marks it driver active, so that it will be restored to the
 * device at the next best समय.
 */
पूर्णांक
il4965_alloc_bcast_station(काष्ठा il_priv *il)
अणु
	काष्ठा il_link_quality_cmd *link_cmd;
	अचिन्हित दीर्घ flags;
	u8 sta_id;

	spin_lock_irqsave(&il->sta_lock, flags);
	sta_id = il_prep_station(il, il_bcast_addr, false, शून्य);
	अगर (sta_id == IL_INVALID_STATION) अणु
		IL_ERR("Unable to prepare broadcast station\n");
		spin_unlock_irqrestore(&il->sta_lock, flags);

		वापस -EINVAL;
	पूर्ण

	il->stations[sta_id].used |= IL_STA_DRIVER_ACTIVE;
	il->stations[sta_id].used |= IL_STA_BCAST;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	link_cmd = il4965_sta_alloc_lq(il, sta_id);
	अगर (!link_cmd) अणु
		IL_ERR
		    ("Unable to initialize rate scaling for bcast station.\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].lq = link_cmd;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस 0;
पूर्ण

/*
 * il4965_update_bcast_station - update broadcast station's LQ command
 *
 * Only used by iwl4965. Placed here to have all bcast station management
 * code together.
 */
अटल पूर्णांक
il4965_update_bcast_station(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा il_link_quality_cmd *link_cmd;
	u8 sta_id = il->hw_params.bcast_id;

	link_cmd = il4965_sta_alloc_lq(il, sta_id);
	अगर (!link_cmd) अणु
		IL_ERR("Unable to initialize rate scaling for bcast sta.\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&il->sta_lock, flags);
	अगर (il->stations[sta_id].lq)
		kमुक्त(il->stations[sta_id].lq);
	अन्यथा
		D_INFO("Bcast sta rate scaling has not been initialized.\n");
	il->stations[sta_id].lq = link_cmd;
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक
il4965_update_bcast_stations(काष्ठा il_priv *il)
अणु
	वापस il4965_update_bcast_station(il);
पूर्ण

/*
 * il4965_sta_tx_modअगरy_enable_tid - Enable Tx क्रम this TID in station table
 */
पूर्णांक
il4965_sta_tx_modअगरy_enable_tid(काष्ठा il_priv *il, पूर्णांक sta_id, पूर्णांक tid)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा il_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&il->mutex);

	/* Remove "disable" flag, to enable Tx क्रम this TID */
	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_TID_DISABLE_TX;
	il->stations[sta_id].sta.tid_disable_tx &= cpu_to_le16(~(1 << tid));
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस il_send_add_sta(il, &sta_cmd, CMD_SYNC);
पूर्ण

पूर्णांक
il4965_sta_rx_agg_start(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta, पूर्णांक tid,
			u16 ssn)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक sta_id;
	काष्ठा il_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&il->mutex);

	sta_id = il_sta_id(sta);
	अगर (sta_id == IL_INVALID_STATION)
		वापस -ENXIO;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].sta.station_flags_msk = 0;
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_ADDBA_TID_MSK;
	il->stations[sta_id].sta.add_immediate_ba_tid = (u8) tid;
	il->stations[sta_id].sta.add_immediate_ba_ssn = cpu_to_le16(ssn);
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस il_send_add_sta(il, &sta_cmd, CMD_SYNC);
पूर्ण

पूर्णांक
il4965_sta_rx_agg_stop(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta, पूर्णांक tid)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक sta_id;
	काष्ठा il_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&il->mutex);

	sta_id = il_sta_id(sta);
	अगर (sta_id == IL_INVALID_STATION) अणु
		IL_ERR("Invalid station for AGG tid %d\n", tid);
		वापस -ENXIO;
	पूर्ण

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].sta.station_flags_msk = 0;
	il->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_DELBA_TID_MSK;
	il->stations[sta_id].sta.हटाओ_immediate_ba_tid = (u8) tid;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस il_send_add_sta(il, &sta_cmd, CMD_SYNC);
पूर्ण

व्योम
il4965_sta_modअगरy_sleep_tx_count(काष्ठा il_priv *il, पूर्णांक sta_id, पूर्णांक cnt)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&il->sta_lock, flags);
	il->stations[sta_id].sta.station_flags |= STA_FLG_PWR_SAVE_MSK;
	il->stations[sta_id].sta.station_flags_msk = STA_FLG_PWR_SAVE_MSK;
	il->stations[sta_id].sta.sta.modअगरy_mask =
	    STA_MODIFY_SLEEP_TX_COUNT_MSK;
	il->stations[sta_id].sta.sleep_tx_count = cpu_to_le16(cnt);
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	il_send_add_sta(il, &il->stations[sta_id].sta, CMD_ASYNC);
	spin_unlock_irqrestore(&il->sta_lock, flags);

पूर्ण

व्योम
il4965_update_chain_flags(काष्ठा il_priv *il)
अणु
	अगर (il->ops->set_rxon_chain) अणु
		il->ops->set_rxon_chain(il);
		अगर (il->active.rx_chain != il->staging.rx_chain)
			il_commit_rxon(il);
	पूर्ण
पूर्ण

अटल व्योम
il4965_clear_मुक्त_frames(काष्ठा il_priv *il)
अणु
	काष्ठा list_head *element;

	D_INFO("%d frames on pre-allocated heap on clear.\n", il->frames_count);

	जबतक (!list_empty(&il->मुक्त_frames)) अणु
		element = il->मुक्त_frames.next;
		list_del(element);
		kमुक्त(list_entry(element, काष्ठा il_frame, list));
		il->frames_count--;
	पूर्ण

	अगर (il->frames_count) अणु
		IL_WARN("%d frames still in use.  Did we lose one?\n",
			il->frames_count);
		il->frames_count = 0;
	पूर्ण
पूर्ण

अटल काष्ठा il_frame *
il4965_get_मुक्त_frame(काष्ठा il_priv *il)
अणु
	काष्ठा il_frame *frame;
	काष्ठा list_head *element;
	अगर (list_empty(&il->मुक्त_frames)) अणु
		frame = kzalloc(माप(*frame), GFP_KERNEL);
		अगर (!frame) अणु
			IL_ERR("Could not allocate frame!\n");
			वापस शून्य;
		पूर्ण

		il->frames_count++;
		वापस frame;
	पूर्ण

	element = il->मुक्त_frames.next;
	list_del(element);
	वापस list_entry(element, काष्ठा il_frame, list);
पूर्ण

अटल व्योम
il4965_मुक्त_frame(काष्ठा il_priv *il, काष्ठा il_frame *frame)
अणु
	स_रखो(frame, 0, माप(*frame));
	list_add(&frame->list, &il->मुक्त_frames);
पूर्ण

अटल u32
il4965_fill_beacon_frame(काष्ठा il_priv *il, काष्ठा ieee80211_hdr *hdr,
			 पूर्णांक left)
अणु
	lockdep_निश्चित_held(&il->mutex);

	अगर (!il->beacon_skb)
		वापस 0;

	अगर (il->beacon_skb->len > left)
		वापस 0;

	स_नकल(hdr, il->beacon_skb->data, il->beacon_skb->len);

	वापस il->beacon_skb->len;
पूर्ण

/* Parse the beacon frame to find the TIM element and set tim_idx & tim_size */
अटल व्योम
il4965_set_beacon_tim(काष्ठा il_priv *il,
		      काष्ठा il_tx_beacon_cmd *tx_beacon_cmd, u8 * beacon,
		      u32 frame_size)
अणु
	u16 tim_idx;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)beacon;

	/*
	 * The idx is relative to frame start but we start looking at the
	 * variable-length part of the beacon.
	 */
	tim_idx = mgmt->u.beacon.variable - beacon;

	/* Parse variable-length elements of beacon to find WLAN_EID_TIM */
	जबतक ((tim_idx < (frame_size - 2)) &&
	       (beacon[tim_idx] != WLAN_EID_TIM))
		tim_idx += beacon[tim_idx + 1] + 2;

	/* If TIM field was found, set variables */
	अगर ((tim_idx < (frame_size - 1)) && (beacon[tim_idx] == WLAN_EID_TIM)) अणु
		tx_beacon_cmd->tim_idx = cpu_to_le16(tim_idx);
		tx_beacon_cmd->tim_size = beacon[tim_idx + 1];
	पूर्ण अन्यथा
		IL_WARN("Unable to find TIM Element in beacon\n");
पूर्ण

अटल अचिन्हित पूर्णांक
il4965_hw_get_beacon_cmd(काष्ठा il_priv *il, काष्ठा il_frame *frame)
अणु
	काष्ठा il_tx_beacon_cmd *tx_beacon_cmd;
	u32 frame_size;
	u32 rate_flags;
	u32 rate;
	/*
	 * We have to set up the TX command, the TX Beacon command, and the
	 * beacon contents.
	 */

	lockdep_निश्चित_held(&il->mutex);

	अगर (!il->beacon_enabled) अणु
		IL_ERR("Trying to build beacon without beaconing enabled\n");
		वापस 0;
	पूर्ण

	/* Initialize memory */
	tx_beacon_cmd = &frame->u.beacon;
	स_रखो(tx_beacon_cmd, 0, माप(*tx_beacon_cmd));

	/* Set up TX beacon contents */
	frame_size =
	    il4965_fill_beacon_frame(il, tx_beacon_cmd->frame,
				     माप(frame->u) - माप(*tx_beacon_cmd));
	अगर (WARN_ON_ONCE(frame_size > MAX_MPDU_SIZE))
		वापस 0;
	अगर (!frame_size)
		वापस 0;

	/* Set up TX command fields */
	tx_beacon_cmd->tx.len = cpu_to_le16((u16) frame_size);
	tx_beacon_cmd->tx.sta_id = il->hw_params.bcast_id;
	tx_beacon_cmd->tx.stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;
	tx_beacon_cmd->tx.tx_flags =
	    TX_CMD_FLG_SEQ_CTL_MSK | TX_CMD_FLG_TSF_MSK |
	    TX_CMD_FLG_STA_RATE_MSK;

	/* Set up TX beacon command fields */
	il4965_set_beacon_tim(il, tx_beacon_cmd, (u8 *) tx_beacon_cmd->frame,
			      frame_size);

	/* Set up packet rate and flags */
	rate = il_get_lowest_plcp(il);
	il4965_toggle_tx_ant(il, &il->mgmt_tx_ant, il->hw_params.valid_tx_ant);
	rate_flags = BIT(il->mgmt_tx_ant) << RATE_MCS_ANT_POS;
	अगर ((rate >= IL_FIRST_CCK_RATE) && (rate <= IL_LAST_CCK_RATE))
		rate_flags |= RATE_MCS_CCK_MSK;
	tx_beacon_cmd->tx.rate_n_flags = cpu_to_le32(rate | rate_flags);

	वापस माप(*tx_beacon_cmd) + frame_size;
पूर्ण

पूर्णांक
il4965_send_beacon_cmd(काष्ठा il_priv *il)
अणु
	काष्ठा il_frame *frame;
	अचिन्हित पूर्णांक frame_size;
	पूर्णांक rc;

	frame = il4965_get_मुक्त_frame(il);
	अगर (!frame) अणु
		IL_ERR("Could not obtain free frame buffer for beacon "
		       "command.\n");
		वापस -ENOMEM;
	पूर्ण

	frame_size = il4965_hw_get_beacon_cmd(il, frame);
	अगर (!frame_size) अणु
		IL_ERR("Error configuring the beacon command\n");
		il4965_मुक्त_frame(il, frame);
		वापस -EINVAL;
	पूर्ण

	rc = il_send_cmd_pdu(il, C_TX_BEACON, frame_size, &frame->u.cmd[0]);

	il4965_मुक्त_frame(il, frame);

	वापस rc;
पूर्ण

अटल अंतरभूत dma_addr_t
il4965_tfd_tb_get_addr(काष्ठा il_tfd *tfd, u8 idx)
अणु
	काष्ठा il_tfd_tb *tb = &tfd->tbs[idx];

	dma_addr_t addr = get_unaligned_le32(&tb->lo);
	अगर (माप(dma_addr_t) > माप(u32))
		addr |=
		    ((dma_addr_t) (le16_to_cpu(tb->hi_n_len) & 0xF) << 16) <<
		    16;

	वापस addr;
पूर्ण

अटल अंतरभूत u16
il4965_tfd_tb_get_len(काष्ठा il_tfd *tfd, u8 idx)
अणु
	काष्ठा il_tfd_tb *tb = &tfd->tbs[idx];

	वापस le16_to_cpu(tb->hi_n_len) >> 4;
पूर्ण

अटल अंतरभूत व्योम
il4965_tfd_set_tb(काष्ठा il_tfd *tfd, u8 idx, dma_addr_t addr, u16 len)
अणु
	काष्ठा il_tfd_tb *tb = &tfd->tbs[idx];
	u16 hi_n_len = len << 4;

	put_unaligned_le32(addr, &tb->lo);
	अगर (माप(dma_addr_t) > माप(u32))
		hi_n_len |= ((addr >> 16) >> 16) & 0xF;

	tb->hi_n_len = cpu_to_le16(hi_n_len);

	tfd->num_tbs = idx + 1;
पूर्ण

अटल अंतरभूत u8
il4965_tfd_get_num_tbs(काष्ठा il_tfd *tfd)
अणु
	वापस tfd->num_tbs & 0x1f;
पूर्ण

/*
 * il4965_hw_txq_मुक्त_tfd - Free all chunks referenced by TFD [txq->q.पढ़ो_ptr]
 *
 * Does NOT advance any TFD circular buffer पढ़ो/ग_लिखो idxes
 * Does NOT मुक्त the TFD itself (which is within circular buffer)
 */
व्योम
il4965_hw_txq_मुक्त_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq)
अणु
	काष्ठा il_tfd *tfd_पंचांगp = (काष्ठा il_tfd *)txq->tfds;
	काष्ठा il_tfd *tfd;
	काष्ठा pci_dev *dev = il->pci_dev;
	पूर्णांक idx = txq->q.पढ़ो_ptr;
	पूर्णांक i;
	पूर्णांक num_tbs;

	tfd = &tfd_पंचांगp[idx];

	/* Sanity check on number of chunks */
	num_tbs = il4965_tfd_get_num_tbs(tfd);

	अगर (num_tbs >= IL_NUM_OF_TBS) अणु
		IL_ERR("Too many chunks: %i\n", num_tbs);
		/* @toकरो issue fatal error, it is quite serious situation */
		वापस;
	पूर्ण

	/* Unmap tx_cmd */
	अगर (num_tbs)
		pci_unmap_single(dev, dma_unmap_addr(&txq->meta[idx], mapping),
				 dma_unmap_len(&txq->meta[idx], len),
				 PCI_DMA_BIसूचीECTIONAL);

	/* Unmap chunks, अगर any. */
	क्रम (i = 1; i < num_tbs; i++)
		pci_unmap_single(dev, il4965_tfd_tb_get_addr(tfd, i),
				 il4965_tfd_tb_get_len(tfd, i),
				 PCI_DMA_TODEVICE);

	/* मुक्त SKB */
	अगर (txq->skbs) अणु
		काष्ठा sk_buff *skb = txq->skbs[txq->q.पढ़ो_ptr];

		/* can be called from irqs-disabled context */
		अगर (skb) अणु
			dev_kमुक्त_skb_any(skb);
			txq->skbs[txq->q.पढ़ो_ptr] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
il4965_hw_txq_attach_buf_to_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq,
				dma_addr_t addr, u16 len, u8 reset, u8 pad)
अणु
	काष्ठा il_queue *q;
	काष्ठा il_tfd *tfd, *tfd_पंचांगp;
	u32 num_tbs;

	q = &txq->q;
	tfd_पंचांगp = (काष्ठा il_tfd *)txq->tfds;
	tfd = &tfd_पंचांगp[q->ग_लिखो_ptr];

	अगर (reset)
		स_रखो(tfd, 0, माप(*tfd));

	num_tbs = il4965_tfd_get_num_tbs(tfd);

	/* Each TFD can poपूर्णांक to a maximum 20 Tx buffers */
	अगर (num_tbs >= IL_NUM_OF_TBS) अणु
		IL_ERR("Error can not send more than %d chunks\n",
		       IL_NUM_OF_TBS);
		वापस -EINVAL;
	पूर्ण

	BUG_ON(addr & ~DMA_BIT_MASK(36));
	अगर (unlikely(addr & ~IL_TX_DMA_MASK))
		IL_ERR("Unaligned address = %llx\n", (अचिन्हित दीर्घ दीर्घ)addr);

	il4965_tfd_set_tb(tfd, num_tbs, addr, len);

	वापस 0;
पूर्ण

/*
 * Tell nic where to find circular buffer of Tx Frame Descriptors क्रम
 * given Tx queue, and enable the DMA channel used क्रम that queue.
 *
 * 4965 supports up to 16 Tx queues in DRAM, mapped to up to 8 Tx DMA
 * channels supported in hardware.
 */
पूर्णांक
il4965_hw_tx_queue_init(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq)
अणु
	पूर्णांक txq_id = txq->q.id;

	/* Circular buffer (TFD queue in DRAM) physical base address */
	il_wr(il, FH49_MEM_CBBC_QUEUE(txq_id), txq->q.dma_addr >> 8);

	वापस 0;
पूर्ण

/******************************************************************************
 *
 * Generic RX handler implementations
 *
 ******************************************************************************/
अटल व्योम
il4965_hdl_alive(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_alive_resp *palive;
	काष्ठा delayed_work *pwork;

	palive = &pkt->u.alive_frame;

	D_INFO("Alive ucode status 0x%08X revision " "0x%01X 0x%01X\n",
	       palive->is_valid, palive->ver_type, palive->ver_subtype);

	अगर (palive->ver_subtype == INITIALIZE_SUBTYPE) अणु
		D_INFO("Initialization Alive received.\n");
		स_नकल(&il->card_alive_init, &pkt->u.alive_frame,
		       माप(काष्ठा il_init_alive_resp));
		pwork = &il->init_alive_start;
	पूर्ण अन्यथा अणु
		D_INFO("Runtime Alive received.\n");
		स_नकल(&il->card_alive, &pkt->u.alive_frame,
		       माप(काष्ठा il_alive_resp));
		pwork = &il->alive_start;
	पूर्ण

	/* We delay the ALIVE response by 5ms to
	 * give the HW RF Kill समय to activate... */
	अगर (palive->is_valid == UCODE_VALID_OK)
		queue_delayed_work(il->workqueue, pwork, msecs_to_jअगरfies(5));
	अन्यथा
		IL_WARN("uCode did not respond OK.\n");
पूर्ण

/*
 * il4965_bg_stats_periodic - Timer callback to queue stats
 *
 * This callback is provided in order to send a stats request.
 *
 * This समयr function is continually reset to execute within
 * 60 seconds since the last N_STATS was received.  We need to
 * ensure we receive the stats in order to update the temperature
 * used क्रम calibrating the TXPOWER.
 */
अटल व्योम
il4965_bg_stats_periodic(काष्ठा समयr_list *t)
अणु
	काष्ठा il_priv *il = from_समयr(il, t, stats_periodic);

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	/* करोnt send host command अगर rf-समाप्त is on */
	अगर (!il_is_पढ़ोy_rf(il))
		वापस;

	il_send_stats_request(il, CMD_ASYNC, false);
पूर्ण

अटल व्योम
il4965_hdl_beacon(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il4965_beacon_notअगर *beacon =
	    (काष्ठा il4965_beacon_notअगर *)pkt->u.raw;
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	u8 rate = il4965_hw_get_rate(beacon->beacon_notअगरy_hdr.rate_n_flags);

	D_RX("beacon status %x retries %d iss %d tsf:0x%.8x%.8x rate %d\n",
	     le32_to_cpu(beacon->beacon_notअगरy_hdr.u.status) & TX_STATUS_MSK,
	     beacon->beacon_notअगरy_hdr.failure_frame,
	     le32_to_cpu(beacon->ibss_mgr_status),
	     le32_to_cpu(beacon->high_tsf), le32_to_cpu(beacon->low_tsf), rate);
#पूर्ण_अगर
	il->ibss_manager = le32_to_cpu(beacon->ibss_mgr_status);
पूर्ण

अटल व्योम
il4965_perक्रमm_ct_समाप्त_task(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;

	D_POWER("Stop all queues\n");

	अगर (il->mac80211_रेजिस्टरed)
		ieee80211_stop_queues(il->hw);

	_il_wr(il, CSR_UCODE_DRV_GP1_SET,
	       CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
	_il_rd(il, CSR_UCODE_DRV_GP1);

	spin_lock_irqsave(&il->reg_lock, flags);
	अगर (likely(_il_grab_nic_access(il)))
		_il_release_nic_access(il);
	spin_unlock_irqrestore(&il->reg_lock, flags);
पूर्ण

/* Handle notअगरication from uCode that card's घातer state is changing
 * due to software, hardware, or critical temperature RFKILL */
अटल व्योम
il4965_hdl_card_state(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	u32 flags = le32_to_cpu(pkt->u.card_state_notअगर.flags);
	अचिन्हित दीर्घ status = il->status;

	D_RF_KILL("Card state received: HW:%s SW:%s CT:%s\n",
		  (flags & HW_CARD_DISABLED) ? "Kill" : "On",
		  (flags & SW_CARD_DISABLED) ? "Kill" : "On",
		  (flags & CT_CARD_DISABLED) ? "Reached" : "Not reached");

	अगर (flags & (SW_CARD_DISABLED | HW_CARD_DISABLED | CT_CARD_DISABLED)) अणु

		_il_wr(il, CSR_UCODE_DRV_GP1_SET,
		       CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

		il_wr(il, HBUS_TARG_MBX_C, HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED);

		अगर (!(flags & RXON_CARD_DISABLED)) अणु
			_il_wr(il, CSR_UCODE_DRV_GP1_CLR,
			       CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);
			il_wr(il, HBUS_TARG_MBX_C,
			      HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED);
		पूर्ण
	पूर्ण

	अगर (flags & CT_CARD_DISABLED)
		il4965_perक्रमm_ct_समाप्त_task(il);

	अगर (flags & HW_CARD_DISABLED)
		set_bit(S_RFKILL, &il->status);
	अन्यथा
		clear_bit(S_RFKILL, &il->status);

	अगर (!(flags & RXON_CARD_DISABLED))
		il_scan_cancel(il);

	अगर ((test_bit(S_RFKILL, &status) !=
	     test_bit(S_RFKILL, &il->status)))
		wiphy_rfसमाप्त_set_hw_state(il->hw->wiphy,
					  test_bit(S_RFKILL, &il->status));
	अन्यथा
		wake_up(&il->रुको_command_queue);
पूर्ण

/*
 * il4965_setup_handlers - Initialize Rx handler callbacks
 *
 * Setup the RX handlers क्रम each of the reply types sent from the uCode
 * to the host.
 *
 * This function chains पूर्णांकo the hardware specअगरic files क्रम them to setup
 * any hardware specअगरic handlers as well.
 */
अटल व्योम
il4965_setup_handlers(काष्ठा il_priv *il)
अणु
	il->handlers[N_ALIVE] = il4965_hdl_alive;
	il->handlers[N_ERROR] = il_hdl_error;
	il->handlers[N_CHANNEL_SWITCH] = il_hdl_csa;
	il->handlers[N_SPECTRUM_MEASUREMENT] = il_hdl_spectrum_measurement;
	il->handlers[N_PM_SLEEP] = il_hdl_pm_sleep;
	il->handlers[N_PM_DEBUG_STATS] = il_hdl_pm_debug_stats;
	il->handlers[N_BEACON] = il4965_hdl_beacon;

	/*
	 * The same handler is used क्रम both the REPLY to a discrete
	 * stats request from the host as well as क्रम the periodic
	 * stats notअगरications (after received beacons) from the uCode.
	 */
	il->handlers[C_STATS] = il4965_hdl_c_stats;
	il->handlers[N_STATS] = il4965_hdl_stats;

	il_setup_rx_scan_handlers(il);

	/* status change handler */
	il->handlers[N_CARD_STATE] = il4965_hdl_card_state;

	il->handlers[N_MISSED_BEACONS] = il4965_hdl_missed_beacon;
	/* Rx handlers */
	il->handlers[N_RX_PHY] = il4965_hdl_rx_phy;
	il->handlers[N_RX_MPDU] = il4965_hdl_rx;
	il->handlers[N_RX] = il4965_hdl_rx;
	/* block ack */
	il->handlers[N_COMPRESSED_BA] = il4965_hdl_compressed_ba;
	/* Tx response */
	il->handlers[C_TX] = il4965_hdl_tx;
पूर्ण

/*
 * il4965_rx_handle - Main entry function क्रम receiving responses from uCode
 *
 * Uses the il->handlers callback function array to invoke
 * the appropriate handlers, including command responses,
 * frame-received notअगरications, and other notअगरications.
 */
व्योम
il4965_rx_handle(काष्ठा il_priv *il)
अणु
	काष्ठा il_rx_buf *rxb;
	काष्ठा il_rx_pkt *pkt;
	काष्ठा il_rx_queue *rxq = &il->rxq;
	u32 r, i;
	पूर्णांक reclaim;
	अचिन्हित दीर्घ flags;
	u8 fill_rx = 0;
	u32 count = 8;
	पूर्णांक total_empty;

	/* uCode's पढ़ो idx (stored in shared DRAM) indicates the last Rx
	 * buffer that the driver may process (last buffer filled by ucode). */
	r = le16_to_cpu(rxq->rb_stts->बंदd_rb_num) & 0x0FFF;
	i = rxq->पढ़ो;

	/* Rx पूर्णांकerrupt, but nothing sent from uCode */
	अगर (i == r)
		D_RX("r = %d, i = %d\n", r, i);

	/* calculate total frames need to be restock after handling RX */
	total_empty = r - rxq->ग_लिखो_actual;
	अगर (total_empty < 0)
		total_empty += RX_QUEUE_SIZE;

	अगर (total_empty > (RX_QUEUE_SIZE / 2))
		fill_rx = 1;

	जबतक (i != r) अणु
		पूर्णांक len;

		rxb = rxq->queue[i];

		/* If an RXB करोesn't have a Rx queue slot associated with it,
		 * then a bug has been पूर्णांकroduced in the queue refilling
		 * routines -- catch it here */
		BUG_ON(rxb == शून्य);

		rxq->queue[i] = शून्य;

		pci_unmap_page(il->pci_dev, rxb->page_dma,
			       PAGE_SIZE << il->hw_params.rx_page_order,
			       PCI_DMA_FROMDEVICE);
		pkt = rxb_addr(rxb);

		len = le32_to_cpu(pkt->len_n_flags) & IL_RX_FRAME_SIZE_MSK;
		len += माप(u32);	/* account क्रम status word */

		reclaim = il_need_reclaim(il, pkt);

		/* Based on type of command response or notअगरication,
		 *   handle those that need handling via function in
		 *   handlers table.  See il4965_setup_handlers() */
		अगर (il->handlers[pkt->hdr.cmd]) अणु
			D_RX("r = %d, i = %d, %s, 0x%02x\n", r, i,
			     il_get_cmd_string(pkt->hdr.cmd), pkt->hdr.cmd);
			il->isr_stats.handlers[pkt->hdr.cmd]++;
			il->handlers[pkt->hdr.cmd] (il, rxb);
		पूर्ण अन्यथा अणु
			/* No handling needed */
			D_RX("r %d i %d No handler needed for %s, 0x%02x\n", r,
			     i, il_get_cmd_string(pkt->hdr.cmd), pkt->hdr.cmd);
		पूर्ण

		/*
		 * XXX: After here, we should always check rxb->page
		 * against शून्य beक्रमe touching it or its भव
		 * memory (pkt). Because some handler might have
		 * alपढ़ोy taken or मुक्तd the pages.
		 */

		अगर (reclaim) अणु
			/* Invoke any callbacks, transfer the buffer to caller,
			 * and fire off the (possibly) blocking il_send_cmd()
			 * as we reclaim the driver command queue */
			अगर (rxb->page)
				il_tx_cmd_complete(il, rxb);
			अन्यथा
				IL_WARN("Claim null rxb?\n");
		पूर्ण

		/* Reuse the page अगर possible. For notअगरication packets and
		 * SKBs that fail to Rx correctly, add them back पूर्णांकo the
		 * rx_मुक्त list क्रम reuse later. */
		spin_lock_irqsave(&rxq->lock, flags);
		अगर (rxb->page != शून्य) अणु
			rxb->page_dma =
			    pci_map_page(il->pci_dev, rxb->page, 0,
					 PAGE_SIZE << il->hw_params.
					 rx_page_order, PCI_DMA_FROMDEVICE);

			अगर (unlikely(pci_dma_mapping_error(il->pci_dev,
							   rxb->page_dma))) अणु
				__il_मुक्त_pages(il, rxb->page);
				rxb->page = शून्य;
				list_add_tail(&rxb->list, &rxq->rx_used);
			पूर्ण अन्यथा अणु
				list_add_tail(&rxb->list, &rxq->rx_मुक्त);
				rxq->मुक्त_count++;
			पूर्ण
		पूर्ण अन्यथा
			list_add_tail(&rxb->list, &rxq->rx_used);

		spin_unlock_irqrestore(&rxq->lock, flags);

		i = (i + 1) & RX_QUEUE_MASK;
		/* If there are a lot of unused frames,
		 * restock the Rx queue so ucode wont निश्चित. */
		अगर (fill_rx) अणु
			count++;
			अगर (count >= 8) अणु
				rxq->पढ़ो = i;
				il4965_rx_replenish_now(il);
				count = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Backtrack one entry */
	rxq->पढ़ो = i;
	अगर (fill_rx)
		il4965_rx_replenish_now(il);
	अन्यथा
		il4965_rx_queue_restock(il);
पूर्ण

/* call this function to flush any scheduled tasklet */
अटल अंतरभूत व्योम
il4965_synchronize_irq(काष्ठा il_priv *il)
अणु
	/* रुको to make sure we flush pending tasklet */
	synchronize_irq(il->pci_dev->irq);
	tasklet_समाप्त(&il->irq_tasklet);
पूर्ण

अटल व्योम
il4965_irq_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा il_priv *il = from_tasklet(il, t, irq_tasklet);
	u32 पूर्णांकa, handled = 0;
	u32 पूर्णांकa_fh;
	अचिन्हित दीर्घ flags;
	u32 i;
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	u32 पूर्णांकa_mask;
#पूर्ण_अगर

	spin_lock_irqsave(&il->lock, flags);

	/* Ack/clear/reset pending uCode पूर्णांकerrupts.
	 * Note:  Some bits in CSR_INT are "OR" of bits in CSR_FH_INT_STATUS,
	 *  and will clear only when CSR_FH_INT_STATUS माला_लो cleared. */
	पूर्णांकa = _il_rd(il, CSR_INT);
	_il_wr(il, CSR_INT, पूर्णांकa);

	/* Ack/clear/reset pending flow-handler (DMA) पूर्णांकerrupts.
	 * Any new पूर्णांकerrupts that happen after this, either जबतक we're
	 * in this tasklet, or later, will show up in next ISR/tasklet. */
	पूर्णांकa_fh = _il_rd(il, CSR_FH_INT_STATUS);
	_il_wr(il, CSR_FH_INT_STATUS, पूर्णांकa_fh);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (il_get_debug_level(il) & IL_DL_ISR) अणु
		/* just क्रम debug */
		पूर्णांकa_mask = _il_rd(il, CSR_INT_MASK);
		D_ISR("inta 0x%08x, enabled 0x%08x, fh 0x%08x\n", पूर्णांकa,
		      पूर्णांकa_mask, पूर्णांकa_fh);
	पूर्ण
#पूर्ण_अगर

	spin_unlock_irqrestore(&il->lock, flags);

	/* Since CSR_INT and CSR_FH_INT_STATUS पढ़ोs and clears are not
	 * atomic, make sure that पूर्णांकa covers all the पूर्णांकerrupts that
	 * we've discovered, even अगर FH पूर्णांकerrupt came in just after
	 * पढ़ोing CSR_INT. */
	अगर (पूर्णांकa_fh & CSR49_FH_INT_RX_MASK)
		पूर्णांकa |= CSR_INT_BIT_FH_RX;
	अगर (पूर्णांकa_fh & CSR49_FH_INT_TX_MASK)
		पूर्णांकa |= CSR_INT_BIT_FH_TX;

	/* Now service all पूर्णांकerrupt bits discovered above. */
	अगर (पूर्णांकa & CSR_INT_BIT_HW_ERR) अणु
		IL_ERR("Hardware error detected.  Restarting.\n");

		/* Tell the device to stop sending पूर्णांकerrupts */
		il_disable_पूर्णांकerrupts(il);

		il->isr_stats.hw++;
		il_irq_handle_error(il);

		handled |= CSR_INT_BIT_HW_ERR;

		वापस;
	पूर्ण
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (il_get_debug_level(il) & (IL_DL_ISR)) अणु
		/* NIC fires this, but we करोn't use it, redundant with WAKEUP */
		अगर (पूर्णांकa & CSR_INT_BIT_SCD) अणु
			D_ISR("Scheduler finished to transmit "
			      "the frame/frames.\n");
			il->isr_stats.sch++;
		पूर्ण

		/* Alive notअगरication via Rx पूर्णांकerrupt will करो the real work */
		अगर (पूर्णांकa & CSR_INT_BIT_ALIVE) अणु
			D_ISR("Alive interrupt\n");
			il->isr_stats.alive++;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* Safely ignore these bits क्रम debug checks below */
	पूर्णांकa &= ~(CSR_INT_BIT_SCD | CSR_INT_BIT_ALIVE);

	/* HW RF KILL चयन toggled */
	अगर (पूर्णांकa & CSR_INT_BIT_RF_KILL) अणु
		पूर्णांक hw_rf_समाप्त = 0;

		अगर (!(_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW))
			hw_rf_समाप्त = 1;

		IL_WARN("RF_KILL bit toggled to %s.\n",
			hw_rf_समाप्त ? "disable radio" : "enable radio");

		il->isr_stats.rfसमाप्त++;

		/* driver only loads ucode once setting the पूर्णांकerface up.
		 * the driver allows loading the ucode even अगर the radio
		 * is समाप्तed. Hence update the समाप्तचयन state here. The
		 * rfसमाप्त handler will care about restarting अगर needed.
		 */
		अगर (hw_rf_समाप्त) अणु
			set_bit(S_RFKILL, &il->status);
		पूर्ण अन्यथा अणु
			clear_bit(S_RFKILL, &il->status);
			il_क्रमce_reset(il, true);
		पूर्ण
		wiphy_rfसमाप्त_set_hw_state(il->hw->wiphy, hw_rf_समाप्त);

		handled |= CSR_INT_BIT_RF_KILL;
	पूर्ण

	/* Chip got too hot and stopped itself */
	अगर (पूर्णांकa & CSR_INT_BIT_CT_KILL) अणु
		IL_ERR("Microcode CT kill error detected.\n");
		il->isr_stats.ctसमाप्त++;
		handled |= CSR_INT_BIT_CT_KILL;
	पूर्ण

	/* Error detected by uCode */
	अगर (पूर्णांकa & CSR_INT_BIT_SW_ERR) अणु
		IL_ERR("Microcode SW error detected. " " Restarting 0x%X.\n",
		       पूर्णांकa);
		il->isr_stats.sw++;
		il_irq_handle_error(il);
		handled |= CSR_INT_BIT_SW_ERR;
	पूर्ण

	/*
	 * uCode wakes up after घातer-करोwn sleep.
	 * Tell device about any new tx or host commands enqueued,
	 * and about any Rx buffers made available जबतक asleep.
	 */
	अगर (पूर्णांकa & CSR_INT_BIT_WAKEUP) अणु
		D_ISR("Wakeup interrupt\n");
		il_rx_queue_update_ग_लिखो_ptr(il, &il->rxq);
		क्रम (i = 0; i < il->hw_params.max_txq_num; i++)
			il_txq_update_ग_लिखो_ptr(il, &il->txq[i]);
		il->isr_stats.wakeup++;
		handled |= CSR_INT_BIT_WAKEUP;
	पूर्ण

	/* All uCode command responses, including Tx command responses,
	 * Rx "responses" (frame-received notअगरication), and other
	 * notअगरications from uCode come through here*/
	अगर (पूर्णांकa & (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX)) अणु
		il4965_rx_handle(il);
		il->isr_stats.rx++;
		handled |= (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX);
	पूर्ण

	/* This "Tx" DMA channel is used only क्रम loading uCode */
	अगर (पूर्णांकa & CSR_INT_BIT_FH_TX) अणु
		D_ISR("uCode load interrupt\n");
		il->isr_stats.tx++;
		handled |= CSR_INT_BIT_FH_TX;
		/* Wake up uCode load routine, now that load is complete */
		il->ucode_ग_लिखो_complete = 1;
		wake_up(&il->रुको_command_queue);
	पूर्ण

	अगर (पूर्णांकa & ~handled) अणु
		IL_ERR("Unhandled INTA bits 0x%08x\n", पूर्णांकa & ~handled);
		il->isr_stats.unhandled++;
	पूर्ण

	अगर (पूर्णांकa & ~(il->पूर्णांकa_mask)) अणु
		IL_WARN("Disabled INTA bits 0x%08x were pending\n",
			पूर्णांकa & ~il->पूर्णांकa_mask);
		IL_WARN("   with FH49_INT = 0x%08x\n", पूर्णांकa_fh);
	पूर्ण

	/* Re-enable all पूर्णांकerrupts */
	/* only Re-enable अगर disabled by irq */
	अगर (test_bit(S_INT_ENABLED, &il->status))
		il_enable_पूर्णांकerrupts(il);
	/* Re-enable RF_KILL अगर it occurred */
	अन्यथा अगर (handled & CSR_INT_BIT_RF_KILL)
		il_enable_rfसमाप्त_पूर्णांक(il);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (il_get_debug_level(il) & (IL_DL_ISR)) अणु
		पूर्णांकa = _il_rd(il, CSR_INT);
		पूर्णांकa_mask = _il_rd(il, CSR_INT_MASK);
		पूर्णांकa_fh = _il_rd(il, CSR_FH_INT_STATUS);
		D_ISR("End inta 0x%08x, enabled 0x%08x, fh 0x%08x, "
		      "flags 0x%08lx\n", पूर्णांकa, पूर्णांकa_mask, पूर्णांकa_fh, flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*****************************************************************************
 *
 * sysfs attributes
 *
 *****************************************************************************/

#अगर_घोषित CONFIG_IWLEGACY_DEBUG

/*
 * The following adds a new attribute to the sysfs representation
 * of this device driver (i.e. a new file in /sys/class/net/wlan0/device/)
 * used क्रम controlling the debug level.
 *
 * See the level definitions in iwl क्रम details.
 *
 * The debug_level being managed using sysfs below is a per device debug
 * level that is used instead of the global debug level अगर it (the per
 * device debug level) is set.
 */
अटल sमाप_प्रकार
il4965_show_debug_level(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	वापस प्र_लिखो(buf, "0x%08X\n", il_get_debug_level(il));
पूर्ण

अटल sमाप_प्रकार
il4965_store_debug_level(काष्ठा device *d, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		IL_ERR("%s is not in hex or decimal form.\n", buf);
	अन्यथा
		il->debug_level = val;

	वापस strnlen(buf, count);
पूर्ण

अटल DEVICE_ATTR(debug_level, 0644, il4965_show_debug_level,
		   il4965_store_debug_level);

#पूर्ण_अगर /* CONFIG_IWLEGACY_DEBUG */

अटल sमाप_प्रकार
il4965_show_temperature(काष्ठा device *d, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);

	अगर (!il_is_alive(il))
		वापस -EAGAIN;

	वापस प्र_लिखो(buf, "%d\n", il->temperature);
पूर्ण

अटल DEVICE_ATTR(temperature, 0444, il4965_show_temperature, शून्य);

अटल sमाप_प्रकार
il4965_show_tx_घातer(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);

	अगर (!il_is_पढ़ोy_rf(il))
		वापस प्र_लिखो(buf, "off\n");
	अन्यथा
		वापस प्र_लिखो(buf, "%d\n", il->tx_घातer_user_lmt);
पूर्ण

अटल sमाप_प्रकार
il4965_store_tx_घातer(काष्ठा device *d, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(d);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		IL_INFO("%s is not in decimal form.\n", buf);
	अन्यथा अणु
		ret = il_set_tx_घातer(il, val, false);
		अगर (ret)
			IL_ERR("failed setting tx power (0x%08x).\n", ret);
		अन्यथा
			ret = count;
	पूर्ण
	वापस ret;
पूर्ण

अटल DEVICE_ATTR(tx_घातer, 0644, il4965_show_tx_घातer,
		   il4965_store_tx_घातer);

अटल काष्ठा attribute *il_sysfs_entries[] = अणु
	&dev_attr_temperature.attr,
	&dev_attr_tx_घातer.attr,
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	&dev_attr_debug_level.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group il_attribute_group = अणु
	.name = शून्य,		/* put in device directory */
	.attrs = il_sysfs_entries,
पूर्ण;

/******************************************************************************
 *
 * uCode करोwnload functions
 *
 ******************************************************************************/

अटल व्योम
il4965_dealloc_ucode_pci(काष्ठा il_priv *il)
अणु
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_code);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_data);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_data_backup);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_init);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_init_data);
	il_मुक्त_fw_desc(il->pci_dev, &il->ucode_boot);
पूर्ण

अटल व्योम
il4965_nic_start(काष्ठा il_priv *il)
अणु
	/* Remove all resets to allow NIC to operate */
	_il_wr(il, CSR_RESET, 0);
पूर्ण

अटल व्योम il4965_ucode_callback(स्थिर काष्ठा firmware *ucode_raw,
				  व्योम *context);
अटल पूर्णांक il4965_mac_setup_रेजिस्टर(काष्ठा il_priv *il, u32 max_probe_length);

अटल पूर्णांक __must_check
il4965_request_firmware(काष्ठा il_priv *il, bool first)
अणु
	स्थिर अक्षर *name_pre = il->cfg->fw_name_pre;
	अक्षर tag[8];

	अगर (first) अणु
		il->fw_idx = il->cfg->ucode_api_max;
		प्र_लिखो(tag, "%d", il->fw_idx);
	पूर्ण अन्यथा अणु
		il->fw_idx--;
		प्र_लिखो(tag, "%d", il->fw_idx);
	पूर्ण

	अगर (il->fw_idx < il->cfg->ucode_api_min) अणु
		IL_ERR("no suitable firmware found!\n");
		वापस -ENOENT;
	पूर्ण

	प्र_लिखो(il->firmware_name, "%s%s%s", name_pre, tag, ".ucode");

	D_INFO("attempting to load firmware '%s'\n", il->firmware_name);

	वापस request_firmware_noरुको(THIS_MODULE, 1, il->firmware_name,
				       &il->pci_dev->dev, GFP_KERNEL, il,
				       il4965_ucode_callback);
पूर्ण

काष्ठा il4965_firmware_pieces अणु
	स्थिर व्योम *inst, *data, *init, *init_data, *boot;
	माप_प्रकार inst_size, data_size, init_size, init_data_size, boot_size;
पूर्ण;

अटल पूर्णांक
il4965_load_firmware(काष्ठा il_priv *il, स्थिर काष्ठा firmware *ucode_raw,
		     काष्ठा il4965_firmware_pieces *pieces)
अणु
	काष्ठा il_ucode_header *ucode = (व्योम *)ucode_raw->data;
	u32 api_ver, hdr_size;
	स्थिर u8 *src;

	il->ucode_ver = le32_to_cpu(ucode->ver);
	api_ver = IL_UCODE_API(il->ucode_ver);

	चयन (api_ver) अणु
	शेष:
	हाल 0:
	हाल 1:
	हाल 2:
		hdr_size = 24;
		अगर (ucode_raw->size < hdr_size) अणु
			IL_ERR("File size too small!\n");
			वापस -EINVAL;
		पूर्ण
		pieces->inst_size = le32_to_cpu(ucode->v1.inst_size);
		pieces->data_size = le32_to_cpu(ucode->v1.data_size);
		pieces->init_size = le32_to_cpu(ucode->v1.init_size);
		pieces->init_data_size = le32_to_cpu(ucode->v1.init_data_size);
		pieces->boot_size = le32_to_cpu(ucode->v1.boot_size);
		src = ucode->v1.data;
		अवरोध;
	पूर्ण

	/* Verअगरy size of file vs. image size info in file's header */
	अगर (ucode_raw->size !=
	    hdr_size + pieces->inst_size + pieces->data_size +
	    pieces->init_size + pieces->init_data_size + pieces->boot_size) अणु

		IL_ERR("uCode file size %d does not match expected size\n",
		       (पूर्णांक)ucode_raw->size);
		वापस -EINVAL;
	पूर्ण

	pieces->inst = src;
	src += pieces->inst_size;
	pieces->data = src;
	src += pieces->data_size;
	pieces->init = src;
	src += pieces->init_size;
	pieces->init_data = src;
	src += pieces->init_data_size;
	pieces->boot = src;
	src += pieces->boot_size;

	वापस 0;
पूर्ण

/*
 * il4965_ucode_callback - callback when firmware was loaded
 *
 * If loaded successfully, copies the firmware पूर्णांकo buffers
 * क्रम the card to fetch (via DMA).
 */
अटल व्योम
il4965_ucode_callback(स्थिर काष्ठा firmware *ucode_raw, व्योम *context)
अणु
	काष्ठा il_priv *il = context;
	पूर्णांक err;
	काष्ठा il4965_firmware_pieces pieces;
	स्थिर अचिन्हित पूर्णांक api_max = il->cfg->ucode_api_max;
	स्थिर अचिन्हित पूर्णांक api_min = il->cfg->ucode_api_min;
	u32 api_ver;

	u32 max_probe_length = 200;
	u32 standard_phy_calibration_size =
	    IL_DEFAULT_STANDARD_PHY_CALIBRATE_TBL_SIZE;

	स_रखो(&pieces, 0, माप(pieces));

	अगर (!ucode_raw) अणु
		अगर (il->fw_idx <= il->cfg->ucode_api_max)
			IL_ERR("request for firmware file '%s' failed.\n",
			       il->firmware_name);
		जाओ try_again;
	पूर्ण

	D_INFO("Loaded firmware file '%s' (%zd bytes).\n", il->firmware_name,
	       ucode_raw->size);

	/* Make sure that we got at least the API version number */
	अगर (ucode_raw->size < 4) अणु
		IL_ERR("File size way too small!\n");
		जाओ try_again;
	पूर्ण

	/* Data from ucode file:  header followed by uCode images */
	err = il4965_load_firmware(il, ucode_raw, &pieces);

	अगर (err)
		जाओ try_again;

	api_ver = IL_UCODE_API(il->ucode_ver);

	/*
	 * api_ver should match the api version क्रमming part of the
	 * firmware filename ... but we करोn't check क्रम that and only rely
	 * on the API version पढ़ो from firmware header from here on क्रमward
	 */
	अगर (api_ver < api_min || api_ver > api_max) अणु
		IL_ERR("Driver unable to support your firmware API. "
		       "Driver supports v%u, firmware is v%u.\n", api_max,
		       api_ver);
		जाओ try_again;
	पूर्ण

	अगर (api_ver != api_max)
		IL_ERR("Firmware has old API version. Expected v%u, "
		       "got v%u. New firmware can be obtained "
		       "from http://www.intellinuxwireless.org.\n", api_max,
		       api_ver);

	IL_INFO("loaded firmware version %u.%u.%u.%u\n",
		IL_UCODE_MAJOR(il->ucode_ver), IL_UCODE_MINOR(il->ucode_ver),
		IL_UCODE_API(il->ucode_ver), IL_UCODE_SERIAL(il->ucode_ver));

	snम_लिखो(il->hw->wiphy->fw_version, माप(il->hw->wiphy->fw_version),
		 "%u.%u.%u.%u", IL_UCODE_MAJOR(il->ucode_ver),
		 IL_UCODE_MINOR(il->ucode_ver), IL_UCODE_API(il->ucode_ver),
		 IL_UCODE_SERIAL(il->ucode_ver));

	/*
	 * For any of the failures below (beक्रमe allocating pci memory)
	 * we will try to load a version with a smaller API -- maybe the
	 * user just got a corrupted version of the latest API.
	 */

	D_INFO("f/w package hdr ucode version raw = 0x%x\n", il->ucode_ver);
	D_INFO("f/w package hdr runtime inst size = %zd\n", pieces.inst_size);
	D_INFO("f/w package hdr runtime data size = %zd\n", pieces.data_size);
	D_INFO("f/w package hdr init inst size = %zd\n", pieces.init_size);
	D_INFO("f/w package hdr init data size = %zd\n", pieces.init_data_size);
	D_INFO("f/w package hdr boot inst size = %zd\n", pieces.boot_size);

	/* Verअगरy that uCode images will fit in card's SRAM */
	अगर (pieces.inst_size > il->hw_params.max_inst_size) अणु
		IL_ERR("uCode instr len %zd too large to fit in\n",
		       pieces.inst_size);
		जाओ try_again;
	पूर्ण

	अगर (pieces.data_size > il->hw_params.max_data_size) अणु
		IL_ERR("uCode data len %zd too large to fit in\n",
		       pieces.data_size);
		जाओ try_again;
	पूर्ण

	अगर (pieces.init_size > il->hw_params.max_inst_size) अणु
		IL_ERR("uCode init instr len %zd too large to fit in\n",
		       pieces.init_size);
		जाओ try_again;
	पूर्ण

	अगर (pieces.init_data_size > il->hw_params.max_data_size) अणु
		IL_ERR("uCode init data len %zd too large to fit in\n",
		       pieces.init_data_size);
		जाओ try_again;
	पूर्ण

	अगर (pieces.boot_size > il->hw_params.max_bsm_size) अणु
		IL_ERR("uCode boot instr len %zd too large to fit in\n",
		       pieces.boot_size);
		जाओ try_again;
	पूर्ण

	/* Allocate ucode buffers क्रम card's bus-master loading ... */

	/* Runसमय inकाष्ठाions and 2 copies of data:
	 * 1) unmodअगरied from disk
	 * 2) backup cache क्रम save/restore during घातer-करोwns */
	il->ucode_code.len = pieces.inst_size;
	il_alloc_fw_desc(il->pci_dev, &il->ucode_code);

	il->ucode_data.len = pieces.data_size;
	il_alloc_fw_desc(il->pci_dev, &il->ucode_data);

	il->ucode_data_backup.len = pieces.data_size;
	il_alloc_fw_desc(il->pci_dev, &il->ucode_data_backup);

	अगर (!il->ucode_code.v_addr || !il->ucode_data.v_addr ||
	    !il->ucode_data_backup.v_addr)
		जाओ err_pci_alloc;

	/* Initialization inकाष्ठाions and data */
	अगर (pieces.init_size && pieces.init_data_size) अणु
		il->ucode_init.len = pieces.init_size;
		il_alloc_fw_desc(il->pci_dev, &il->ucode_init);

		il->ucode_init_data.len = pieces.init_data_size;
		il_alloc_fw_desc(il->pci_dev, &il->ucode_init_data);

		अगर (!il->ucode_init.v_addr || !il->ucode_init_data.v_addr)
			जाओ err_pci_alloc;
	पूर्ण

	/* Bootstrap (inकाष्ठाions only, no data) */
	अगर (pieces.boot_size) अणु
		il->ucode_boot.len = pieces.boot_size;
		il_alloc_fw_desc(il->pci_dev, &il->ucode_boot);

		अगर (!il->ucode_boot.v_addr)
			जाओ err_pci_alloc;
	पूर्ण

	/* Now that we can no दीर्घer fail, copy inक्रमmation */

	il->sta_key_max_num = STA_KEY_MAX_NUM;

	/* Copy images पूर्णांकo buffers क्रम card's bus-master पढ़ोs ... */

	/* Runसमय inकाष्ठाions (first block of data in file) */
	D_INFO("Copying (but not loading) uCode instr len %zd\n",
	       pieces.inst_size);
	स_नकल(il->ucode_code.v_addr, pieces.inst, pieces.inst_size);

	D_INFO("uCode instr buf vaddr = 0x%p, paddr = 0x%08x\n",
	       il->ucode_code.v_addr, (u32) il->ucode_code.p_addr);

	/*
	 * Runसमय data
	 * NOTE:  Copy पूर्णांकo backup buffer will be करोne in il_up()
	 */
	D_INFO("Copying (but not loading) uCode data len %zd\n",
	       pieces.data_size);
	स_नकल(il->ucode_data.v_addr, pieces.data, pieces.data_size);
	स_नकल(il->ucode_data_backup.v_addr, pieces.data, pieces.data_size);

	/* Initialization inकाष्ठाions */
	अगर (pieces.init_size) अणु
		D_INFO("Copying (but not loading) init instr len %zd\n",
		       pieces.init_size);
		स_नकल(il->ucode_init.v_addr, pieces.init, pieces.init_size);
	पूर्ण

	/* Initialization data */
	अगर (pieces.init_data_size) अणु
		D_INFO("Copying (but not loading) init data len %zd\n",
		       pieces.init_data_size);
		स_नकल(il->ucode_init_data.v_addr, pieces.init_data,
		       pieces.init_data_size);
	पूर्ण

	/* Bootstrap inकाष्ठाions */
	D_INFO("Copying (but not loading) boot instr len %zd\n",
	       pieces.boot_size);
	स_नकल(il->ucode_boot.v_addr, pieces.boot, pieces.boot_size);

	/*
	 * figure out the offset of chain noise reset and gain commands
	 * base on the size of standard phy calibration commands table size
	 */
	il->_4965.phy_calib_chain_noise_reset_cmd =
	    standard_phy_calibration_size;
	il->_4965.phy_calib_chain_noise_gain_cmd =
	    standard_phy_calibration_size + 1;

	/**************************************************
	 * This is still part of probe() in a sense...
	 *
	 * 9. Setup and रेजिस्टर with mac80211 and debugfs
	 **************************************************/
	err = il4965_mac_setup_रेजिस्टर(il, max_probe_length);
	अगर (err)
		जाओ out_unbind;

	il_dbgfs_रेजिस्टर(il, DRV_NAME);

	err = sysfs_create_group(&il->pci_dev->dev.kobj, &il_attribute_group);
	अगर (err) अणु
		IL_ERR("failed to create sysfs device attributes\n");
		जाओ out_unbind;
	पूर्ण

	/* We have our copies now, allow OS release its copies */
	release_firmware(ucode_raw);
	complete(&il->_4965.firmware_loading_complete);
	वापस;

try_again:
	/* try next, अगर any */
	अगर (il4965_request_firmware(il, false))
		जाओ out_unbind;
	release_firmware(ucode_raw);
	वापस;

err_pci_alloc:
	IL_ERR("failed to allocate pci memory\n");
	il4965_dealloc_ucode_pci(il);
out_unbind:
	complete(&il->_4965.firmware_loading_complete);
	device_release_driver(&il->pci_dev->dev);
	release_firmware(ucode_raw);
पूर्ण

अटल स्थिर अक्षर *स्थिर desc_lookup_text[] = अणु
	"OK",
	"FAIL",
	"BAD_PARAM",
	"BAD_CHECKSUM",
	"NMI_INTERRUPT_WDG",
	"SYSASSERT",
	"FATAL_ERROR",
	"BAD_COMMAND",
	"HW_ERROR_TUNE_LOCK",
	"HW_ERROR_TEMPERATURE",
	"ILLEGAL_CHAN_FREQ",
	"VCC_NOT_STBL",
	"FH49_ERROR",
	"NMI_INTERRUPT_HOST",
	"NMI_INTERRUPT_ACTION_PT",
	"NMI_INTERRUPT_UNKNOWN",
	"UCODE_VERSION_MISMATCH",
	"HW_ERROR_ABS_LOCK",
	"HW_ERROR_CAL_LOCK_FAIL",
	"NMI_INTERRUPT_INST_ACTION_PT",
	"NMI_INTERRUPT_DATA_ACTION_PT",
	"NMI_TRM_HW_ER",
	"NMI_INTERRUPT_TRM",
	"NMI_INTERRUPT_BREAK_POINT",
	"DEBUG_0",
	"DEBUG_1",
	"DEBUG_2",
	"DEBUG_3",
पूर्ण;

अटल काष्ठा अणु
	अक्षर *name;
	u8 num;
पूर्ण advanced_lookup[] = अणु
	अणु
	"NMI_INTERRUPT_WDG", 0x34पूर्ण, अणु
	"SYSASSERT", 0x35पूर्ण, अणु
	"UCODE_VERSION_MISMATCH", 0x37पूर्ण, अणु
	"BAD_COMMAND", 0x38पूर्ण, अणु
	"NMI_INTERRUPT_DATA_ACTION_PT", 0x3Cपूर्ण, अणु
	"FATAL_ERROR", 0x3Dपूर्ण, अणु
	"NMI_TRM_HW_ERR", 0x46पूर्ण, अणु
	"NMI_INTERRUPT_TRM", 0x4Cपूर्ण, अणु
	"NMI_INTERRUPT_BREAK_POINT", 0x54पूर्ण, अणु
	"NMI_INTERRUPT_WDG_RXF_FULL", 0x5Cपूर्ण, अणु
	"NMI_INTERRUPT_WDG_NO_RBD_RXF_FULL", 0x64पूर्ण, अणु
	"NMI_INTERRUPT_HOST", 0x66पूर्ण, अणु
	"NMI_INTERRUPT_ACTION_PT", 0x7Cपूर्ण, अणु
	"NMI_INTERRUPT_UNKNOWN", 0x84पूर्ण, अणु
	"NMI_INTERRUPT_INST_ACTION_PT", 0x86पूर्ण, अणु
"ADVANCED_SYSASSERT", 0पूर्ण,पूर्ण;

अटल स्थिर अक्षर *
il4965_desc_lookup(u32 num)
अणु
	पूर्णांक i;
	पूर्णांक max = ARRAY_SIZE(desc_lookup_text);

	अगर (num < max)
		वापस desc_lookup_text[num];

	max = ARRAY_SIZE(advanced_lookup) - 1;
	क्रम (i = 0; i < max; i++) अणु
		अगर (advanced_lookup[i].num == num)
			अवरोध;
	पूर्ण
	वापस advanced_lookup[i].name;
पूर्ण

#घोषणा ERROR_START_OFFSET  (1 * माप(u32))
#घोषणा ERROR_ELEM_SIZE     (7 * माप(u32))

व्योम
il4965_dump_nic_error_log(काष्ठा il_priv *il)
अणु
	u32 data2, line;
	u32 desc, समय, count, base, data1;
	u32 blink1, blink2, ilink1, ilink2;
	u32 pc, hcmd;

	अगर (il->ucode_type == UCODE_INIT)
		base = le32_to_cpu(il->card_alive_init.error_event_table_ptr);
	अन्यथा
		base = le32_to_cpu(il->card_alive.error_event_table_ptr);

	अगर (!il->ops->is_valid_rtc_data_addr(base)) अणु
		IL_ERR("Not valid error log pointer 0x%08X for %s uCode\n",
		       base, (il->ucode_type == UCODE_INIT) ? "Init" : "RT");
		वापस;
	पूर्ण

	count = il_पढ़ो_targ_mem(il, base);

	अगर (ERROR_START_OFFSET <= count * ERROR_ELEM_SIZE) अणु
		IL_ERR("Start IWL Error Log Dump:\n");
		IL_ERR("Status: 0x%08lX, count: %d\n", il->status, count);
	पूर्ण

	desc = il_पढ़ो_targ_mem(il, base + 1 * माप(u32));
	il->isr_stats.err_code = desc;
	pc = il_पढ़ो_targ_mem(il, base + 2 * माप(u32));
	blink1 = il_पढ़ो_targ_mem(il, base + 3 * माप(u32));
	blink2 = il_पढ़ो_targ_mem(il, base + 4 * माप(u32));
	ilink1 = il_पढ़ो_targ_mem(il, base + 5 * माप(u32));
	ilink2 = il_पढ़ो_targ_mem(il, base + 6 * माप(u32));
	data1 = il_पढ़ो_targ_mem(il, base + 7 * माप(u32));
	data2 = il_पढ़ो_targ_mem(il, base + 8 * माप(u32));
	line = il_पढ़ो_targ_mem(il, base + 9 * माप(u32));
	समय = il_पढ़ो_targ_mem(il, base + 11 * माप(u32));
	hcmd = il_पढ़ो_targ_mem(il, base + 22 * माप(u32));

	IL_ERR("Desc                                  Time       "
	       "data1      data2      line\n");
	IL_ERR("%-28s (0x%04X) %010u 0x%08X 0x%08X %u\n",
	       il4965_desc_lookup(desc), desc, समय, data1, data2, line);
	IL_ERR("pc      blink1  blink2  ilink1  ilink2  hcmd\n");
	IL_ERR("0x%05X 0x%05X 0x%05X 0x%05X 0x%05X 0x%05X\n", pc, blink1,
	       blink2, ilink1, ilink2, hcmd);
पूर्ण

अटल व्योम
il4965_rf_समाप्त_ct_config(काष्ठा il_priv *il)
अणु
	काष्ठा il_ct_समाप्त_config cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&il->lock, flags);
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR,
	       CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
	spin_unlock_irqrestore(&il->lock, flags);

	cmd.critical_temperature_R =
	    cpu_to_le32(il->hw_params.ct_समाप्त_threshold);

	ret = il_send_cmd_pdu(il, C_CT_KILL_CONFIG, माप(cmd), &cmd);
	अगर (ret)
		IL_ERR("C_CT_KILL_CONFIG failed\n");
	अन्यथा
		D_INFO("C_CT_KILL_CONFIG " "succeeded, "
		       "critical temperature is %d\n",
		       il->hw_params.ct_समाप्त_threshold);
पूर्ण

अटल स्थिर s8 शेष_queue_to_tx_fअगरo[] = अणु
	IL_TX_FIFO_VO,
	IL_TX_FIFO_VI,
	IL_TX_FIFO_BE,
	IL_TX_FIFO_BK,
	IL49_CMD_FIFO_NUM,
	IL_TX_FIFO_UNUSED,
	IL_TX_FIFO_UNUSED,
पूर्ण;

#घोषणा IL_MASK(lo, hi) ((1 << (hi)) | ((1 << (hi)) - (1 << (lo))))

अटल पूर्णांक
il4965_alive_notअगरy(काष्ठा il_priv *il)
अणु
	u32 a;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, chan;
	u32 reg_val;

	spin_lock_irqsave(&il->lock, flags);

	/* Clear 4965's पूर्णांकernal Tx Scheduler data base */
	il->scd_base_addr = il_rd_prph(il, IL49_SCD_SRAM_BASE_ADDR);
	a = il->scd_base_addr + IL49_SCD_CONTEXT_DATA_OFFSET;
	क्रम (; a < il->scd_base_addr + IL49_SCD_TX_STTS_BITMAP_OFFSET; a += 4)
		il_ग_लिखो_targ_mem(il, a, 0);
	क्रम (; a < il->scd_base_addr + IL49_SCD_TRANSLATE_TBL_OFFSET; a += 4)
		il_ग_लिखो_targ_mem(il, a, 0);
	क्रम (;
	     a <
	     il->scd_base_addr +
	     IL49_SCD_TRANSLATE_TBL_OFFSET_QUEUE(il->hw_params.max_txq_num);
	     a += 4)
		il_ग_लिखो_targ_mem(il, a, 0);

	/* Tel 4965 where to find Tx byte count tables */
	il_wr_prph(il, IL49_SCD_DRAM_BASE_ADDR, il->scd_bc_tbls.dma >> 10);

	/* Enable DMA channel */
	क्रम (chan = 0; chan < FH49_TCSR_CHNL_NUM; chan++)
		il_wr(il, FH49_TCSR_CHNL_TX_CONFIG_REG(chan),
		      FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE |
		      FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE);

	/* Update FH chicken bits */
	reg_val = il_rd(il, FH49_TX_CHICKEN_BITS_REG);
	il_wr(il, FH49_TX_CHICKEN_BITS_REG,
	      reg_val | FH49_TX_CHICKEN_BITS_SCD_AUTO_RETRY_EN);

	/* Disable chain mode क्रम all queues */
	il_wr_prph(il, IL49_SCD_QUEUECHAIN_SEL, 0);

	/* Initialize each Tx queue (including the command queue) */
	क्रम (i = 0; i < il->hw_params.max_txq_num; i++) अणु

		/* TFD circular buffer पढ़ो/ग_लिखो idxes */
		il_wr_prph(il, IL49_SCD_QUEUE_RDPTR(i), 0);
		il_wr(il, HBUS_TARG_WRPTR, 0 | (i << 8));

		/* Max Tx Winकरोw size क्रम Scheduler-ACK mode */
		il_ग_लिखो_targ_mem(il,
				  il->scd_base_addr +
				  IL49_SCD_CONTEXT_QUEUE_OFFSET(i),
				  (SCD_WIN_SIZE <<
				   IL49_SCD_QUEUE_CTX_REG1_WIN_SIZE_POS) &
				  IL49_SCD_QUEUE_CTX_REG1_WIN_SIZE_MSK);

		/* Frame limit */
		il_ग_लिखो_targ_mem(il,
				  il->scd_base_addr +
				  IL49_SCD_CONTEXT_QUEUE_OFFSET(i) +
				  माप(u32),
				  (SCD_FRAME_LIMIT <<
				   IL49_SCD_QUEUE_CTX_REG2_FRAME_LIMIT_POS) &
				  IL49_SCD_QUEUE_CTX_REG2_FRAME_LIMIT_MSK);

	पूर्ण
	il_wr_prph(il, IL49_SCD_INTERRUPT_MASK,
		   (1 << il->hw_params.max_txq_num) - 1);

	/* Activate all Tx DMA/FIFO channels */
	il4965_txq_set_sched(il, IL_MASK(0, 6));

	il4965_set_wr_ptrs(il, IL_DEFAULT_CMD_QUEUE_NUM, 0);

	/* make sure all queue are not stopped */
	स_रखो(&il->queue_stopped[0], 0, माप(il->queue_stopped));
	क्रम (i = 0; i < 4; i++)
		atomic_set(&il->queue_stop_count[i], 0);

	/* reset to 0 to enable all the queue first */
	il->txq_ctx_active_msk = 0;
	/* Map each Tx/cmd queue to its corresponding fअगरo */
	BUILD_BUG_ON(ARRAY_SIZE(शेष_queue_to_tx_fअगरo) != 7);

	क्रम (i = 0; i < ARRAY_SIZE(शेष_queue_to_tx_fअगरo); i++) अणु
		पूर्णांक ac = शेष_queue_to_tx_fअगरo[i];

		il_txq_ctx_activate(il, i);

		अगर (ac == IL_TX_FIFO_UNUSED)
			जारी;

		il4965_tx_queue_set_status(il, &il->txq[i], ac, 0);
	पूर्ण

	spin_unlock_irqrestore(&il->lock, flags);

	वापस 0;
पूर्ण

/*
 * il4965_alive_start - called after N_ALIVE notअगरication received
 *                   from protocol/runसमय uCode (initialization uCode's
 *                   Alive माला_लो handled by il_init_alive_start()).
 */
अटल व्योम
il4965_alive_start(काष्ठा il_priv *il)
अणु
	पूर्णांक ret = 0;

	D_INFO("Runtime Alive received.\n");

	अगर (il->card_alive.is_valid != UCODE_VALID_OK) अणु
		/* We had an error bringing up the hardware, so take it
		 * all the way back करोwn so we can try again */
		D_INFO("Alive failed.\n");
		जाओ restart;
	पूर्ण

	/* Initialize uCode has loaded Runसमय uCode ... verअगरy inst image.
	 * This is a paranoid check, because we would not have gotten the
	 * "runtime" alive अगर code weren't properly loaded.  */
	अगर (il4965_verअगरy_ucode(il)) अणु
		/* Runसमय inकाष्ठाion load was bad;
		 * take it all the way back करोwn so we can try again */
		D_INFO("Bad runtime uCode load.\n");
		जाओ restart;
	पूर्ण

	ret = il4965_alive_notअगरy(il);
	अगर (ret) अणु
		IL_WARN("Could not complete ALIVE transition [ntf]: %d\n", ret);
		जाओ restart;
	पूर्ण

	/* After the ALIVE response, we can send host commands to the uCode */
	set_bit(S_ALIVE, &il->status);

	/* Enable watchकरोg to monitor the driver tx queues */
	il_setup_watchकरोg(il);

	अगर (il_is_rfसमाप्त(il))
		वापस;

	ieee80211_wake_queues(il->hw);

	il->active_rate = RATES_MASK;

	il_घातer_update_mode(il, true);
	D_INFO("Updated power mode\n");

	अगर (il_is_associated(il)) अणु
		काष्ठा il_rxon_cmd *active_rxon =
		    (काष्ठा il_rxon_cmd *)&il->active;
		/* apply any changes in staging */
		il->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	पूर्ण अन्यथा अणु
		/* Initialize our rx_config data */
		il_connection_init_rx_config(il);

		अगर (il->ops->set_rxon_chain)
			il->ops->set_rxon_chain(il);
	पूर्ण

	/* Configure bluetooth coexistence अगर enabled */
	il_send_bt_config(il);

	il4965_reset_run_समय_calib(il);

	set_bit(S_READY, &il->status);

	/* Configure the adapter क्रम unassociated operation */
	il_commit_rxon(il);

	/* At this poपूर्णांक, the NIC is initialized and operational */
	il4965_rf_समाप्त_ct_config(il);

	D_INFO("ALIVE processing complete.\n");
	wake_up(&il->रुको_command_queue);

	वापस;

restart:
	queue_work(il->workqueue, &il->restart);
पूर्ण

अटल व्योम il4965_cancel_deferred_work(काष्ठा il_priv *il);

अटल व्योम
__il4965_करोwn(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक निकास_pending;

	D_INFO(DRV_NAME " is going down\n");

	il_scan_cancel_समयout(il, 200);

	निकास_pending = test_and_set_bit(S_EXIT_PENDING, &il->status);

	/* Stop TX queues watchकरोg. We need to have S_EXIT_PENDING bit set
	 * to prevent rearm समयr */
	del_समयr_sync(&il->watchकरोg);

	il_clear_ucode_stations(il);

	/* FIXME: race conditions ? */
	spin_lock_irq(&il->sta_lock);
	/*
	 * Remove all key inक्रमmation that is not stored as part
	 * of station inक्रमmation since mac80211 may not have had
	 * a chance to हटाओ all the keys. When device is
	 * reconfigured by mac80211 after an error all keys will
	 * be reconfigured.
	 */
	स_रखो(il->_4965.wep_keys, 0, माप(il->_4965.wep_keys));
	il->_4965.key_mapping_keys = 0;
	spin_unlock_irq(&il->sta_lock);

	il_dealloc_bcast_stations(il);
	il_clear_driver_stations(il);

	/* Unblock any रुकोing calls */
	wake_up_all(&il->रुको_command_queue);

	/* Wipe out the EXIT_PENDING status bit अगर we are not actually
	 * निकासing the module */
	अगर (!निकास_pending)
		clear_bit(S_EXIT_PENDING, &il->status);

	/* stop and reset the on-board processor */
	_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_NEVO_RESET);

	/* tell the device to stop sending पूर्णांकerrupts */
	spin_lock_irqsave(&il->lock, flags);
	il_disable_पूर्णांकerrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);
	il4965_synchronize_irq(il);

	अगर (il->mac80211_रेजिस्टरed)
		ieee80211_stop_queues(il->hw);

	/* If we have not previously called il_init() then
	 * clear all bits but the RF Kill bit and वापस */
	अगर (!il_is_init(il)) अणु
		il->status =
		    test_bit(S_RFKILL, &il->status) << S_RFKILL |
		    test_bit(S_GEO_CONFIGURED, &il->status) << S_GEO_CONFIGURED |
		    test_bit(S_EXIT_PENDING, &il->status) << S_EXIT_PENDING;
		जाओ निकास;
	पूर्ण

	/* ...otherwise clear out all the status bits but the RF Kill
	 * bit and जारी taking the NIC करोwn. */
	il->status &=
	    test_bit(S_RFKILL, &il->status) << S_RFKILL |
	    test_bit(S_GEO_CONFIGURED, &il->status) << S_GEO_CONFIGURED |
	    test_bit(S_FW_ERROR, &il->status) << S_FW_ERROR |
	    test_bit(S_EXIT_PENDING, &il->status) << S_EXIT_PENDING;

	/*
	 * We disabled and synchronized पूर्णांकerrupt, and priv->mutex is taken, so
	 * here is the only thपढ़ो which will program device रेजिस्टरs, but
	 * still have lockdep निश्चितions, so we are taking reg_lock.
	 */
	spin_lock_irq(&il->reg_lock);
	/* FIXME: il_grab_nic_access अगर rfसमाप्त is off ? */

	il4965_txq_ctx_stop(il);
	il4965_rxq_stop(il);
	/* Power-करोwn device's busmaster DMA घड़ीs */
	_il_wr_prph(il, APMG_CLK_DIS_REG, APMG_CLK_VAL_DMA_CLK_RQT);
	udelay(5);
	/* Make sure (redundant) we've released our request to stay awake */
	_il_clear_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	/* Stop the device, and put it in low घातer state */
	_il_apm_stop(il);

	spin_unlock_irq(&il->reg_lock);

	il4965_txq_ctx_unmap(il);
निकास:
	स_रखो(&il->card_alive, 0, माप(काष्ठा il_alive_resp));

	dev_kमुक्त_skb(il->beacon_skb);
	il->beacon_skb = शून्य;

	/* clear out any मुक्त frames */
	il4965_clear_मुक्त_frames(il);
पूर्ण

अटल व्योम
il4965_करोwn(काष्ठा il_priv *il)
अणु
	mutex_lock(&il->mutex);
	__il4965_करोwn(il);
	mutex_unlock(&il->mutex);

	il4965_cancel_deferred_work(il);
पूर्ण


अटल व्योम
il4965_set_hw_पढ़ोy(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;

	il_set_bit(il, CSR_HW_IF_CONFIG_REG,
		   CSR_HW_IF_CONFIG_REG_BIT_NIC_READY);

	/* See अगर we got it */
	ret = _il_poll_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR_HW_IF_CONFIG_REG_BIT_NIC_READY,
			   CSR_HW_IF_CONFIG_REG_BIT_NIC_READY,
			   100);
	अगर (ret >= 0)
		il->hw_पढ़ोy = true;

	D_INFO("hardware %s ready\n", (il->hw_पढ़ोy) ? "" : "not");
पूर्ण

अटल व्योम
il4965_prepare_card_hw(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;

	il->hw_पढ़ोy = false;

	il4965_set_hw_पढ़ोy(il);
	अगर (il->hw_पढ़ोy)
		वापस;

	/* If HW is not पढ़ोy, prepare the conditions to check again */
	il_set_bit(il, CSR_HW_IF_CONFIG_REG, CSR_HW_IF_CONFIG_REG_PREPARE);

	ret =
	    _il_poll_bit(il, CSR_HW_IF_CONFIG_REG,
			 ~CSR_HW_IF_CONFIG_REG_BIT_NIC_PREPARE_DONE,
			 CSR_HW_IF_CONFIG_REG_BIT_NIC_PREPARE_DONE, 150000);

	/* HW should be पढ़ोy by now, check again. */
	अगर (ret != -ETIMEDOUT)
		il4965_set_hw_पढ़ोy(il);
पूर्ण

#घोषणा MAX_HW_RESTARTS 5

अटल पूर्णांक
__il4965_up(काष्ठा il_priv *il)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	अगर (test_bit(S_EXIT_PENDING, &il->status)) अणु
		IL_WARN("Exit pending; will not bring the NIC up\n");
		वापस -EIO;
	पूर्ण

	अगर (!il->ucode_data_backup.v_addr || !il->ucode_data.v_addr) अणु
		IL_ERR("ucode not available for device bringup\n");
		वापस -EIO;
	पूर्ण

	ret = il4965_alloc_bcast_station(il);
	अगर (ret) अणु
		il_dealloc_bcast_stations(il);
		वापस ret;
	पूर्ण

	il4965_prepare_card_hw(il);
	अगर (!il->hw_पढ़ोy) अणु
		il_dealloc_bcast_stations(il);
		IL_ERR("HW not ready\n");
		वापस -EIO;
	पूर्ण

	/* If platक्रमm's RF_KILL चयन is NOT set to KILL */
	अगर (_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW)
		clear_bit(S_RFKILL, &il->status);
	अन्यथा अणु
		set_bit(S_RFKILL, &il->status);
		wiphy_rfसमाप्त_set_hw_state(il->hw->wiphy, true);

		il_dealloc_bcast_stations(il);
		il_enable_rfसमाप्त_पूर्णांक(il);
		IL_WARN("Radio disabled by HW RF Kill switch\n");
		वापस 0;
	पूर्ण

	_il_wr(il, CSR_INT, 0xFFFFFFFF);

	/* must be initialised beक्रमe il_hw_nic_init */
	il->cmd_queue = IL_DEFAULT_CMD_QUEUE_NUM;

	ret = il4965_hw_nic_init(il);
	अगर (ret) अणु
		IL_ERR("Unable to init nic\n");
		il_dealloc_bcast_stations(il);
		वापस ret;
	पूर्ण

	/* make sure rfसमाप्त handshake bits are cleared */
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

	/* clear (again), then enable host पूर्णांकerrupts */
	_il_wr(il, CSR_INT, 0xFFFFFFFF);
	il_enable_पूर्णांकerrupts(il);

	/* really make sure rfसमाप्त handshake bits are cleared */
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);
	_il_wr(il, CSR_UCODE_DRV_GP1_CLR, CSR_UCODE_SW_BIT_RFKILL);

	/* Copy original ucode data image from disk पूर्णांकo backup cache.
	 * This will be used to initialize the on-board processor's
	 * data SRAM क्रम a clean start when the runसमय program first loads. */
	स_नकल(il->ucode_data_backup.v_addr, il->ucode_data.v_addr,
	       il->ucode_data.len);

	क्रम (i = 0; i < MAX_HW_RESTARTS; i++) अणु

		/* load bootstrap state machine,
		 * load bootstrap program पूर्णांकo processor's memory,
		 * prepare to load the "initialize" uCode */
		ret = il->ops->load_ucode(il);

		अगर (ret) अणु
			IL_ERR("Unable to set up bootstrap uCode: %d\n", ret);
			जारी;
		पूर्ण

		/* start card; "initialize" will load runसमय ucode */
		il4965_nic_start(il);

		D_INFO(DRV_NAME " is coming up\n");

		वापस 0;
	पूर्ण

	set_bit(S_EXIT_PENDING, &il->status);
	__il4965_करोwn(il);
	clear_bit(S_EXIT_PENDING, &il->status);

	/* tried to restart and config the device क्रम as दीर्घ as our
	 * patience could withstand */
	IL_ERR("Unable to initialize device after %d attempts.\n", i);
	वापस -EIO;
पूर्ण

/*****************************************************************************
 *
 * Workqueue callbacks
 *
 *****************************************************************************/

अटल व्योम
il4965_bg_init_alive_start(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il =
	    container_of(data, काष्ठा il_priv, init_alive_start.work);

	mutex_lock(&il->mutex);
	अगर (test_bit(S_EXIT_PENDING, &il->status))
		जाओ out;

	il->ops->init_alive_start(il);
out:
	mutex_unlock(&il->mutex);
पूर्ण

अटल व्योम
il4965_bg_alive_start(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il =
	    container_of(data, काष्ठा il_priv, alive_start.work);

	mutex_lock(&il->mutex);
	अगर (test_bit(S_EXIT_PENDING, &il->status))
		जाओ out;

	il4965_alive_start(il);
out:
	mutex_unlock(&il->mutex);
पूर्ण

अटल व्योम
il4965_bg_run_समय_calib_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा il_priv *il = container_of(work, काष्ठा il_priv,
					  run_समय_calib_work);

	mutex_lock(&il->mutex);

	अगर (test_bit(S_EXIT_PENDING, &il->status) ||
	    test_bit(S_SCANNING, &il->status)) अणु
		mutex_unlock(&il->mutex);
		वापस;
	पूर्ण

	अगर (il->start_calib) अणु
		il4965_chain_noise_calibration(il, (व्योम *)&il->_4965.stats);
		il4965_sensitivity_calibration(il, (व्योम *)&il->_4965.stats);
	पूर्ण

	mutex_unlock(&il->mutex);
पूर्ण

अटल व्योम
il4965_bg_restart(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il = container_of(data, काष्ठा il_priv, restart);

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	अगर (test_and_clear_bit(S_FW_ERROR, &il->status)) अणु
		mutex_lock(&il->mutex);
		il->is_खोलो = 0;

		__il4965_करोwn(il);

		mutex_unlock(&il->mutex);
		il4965_cancel_deferred_work(il);
		ieee80211_restart_hw(il->hw);
	पूर्ण अन्यथा अणु
		il4965_करोwn(il);

		mutex_lock(&il->mutex);
		अगर (test_bit(S_EXIT_PENDING, &il->status)) अणु
			mutex_unlock(&il->mutex);
			वापस;
		पूर्ण

		__il4965_up(il);
		mutex_unlock(&il->mutex);
	पूर्ण
पूर्ण

अटल व्योम
il4965_bg_rx_replenish(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il = container_of(data, काष्ठा il_priv, rx_replenish);

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	mutex_lock(&il->mutex);
	il4965_rx_replenish(il);
	mutex_unlock(&il->mutex);
पूर्ण

/*****************************************************************************
 *
 * mac80211 entry poपूर्णांक functions
 *
 *****************************************************************************/

#घोषणा UCODE_READY_TIMEOUT	(4 * HZ)

/*
 * Not a mac80211 entry poपूर्णांक function, but it fits in with all the
 * other mac80211 functions grouped here.
 */
अटल पूर्णांक
il4965_mac_setup_रेजिस्टर(काष्ठा il_priv *il, u32 max_probe_length)
अणु
	पूर्णांक ret;
	काष्ठा ieee80211_hw *hw = il->hw;

	hw->rate_control_algorithm = "iwl-4965-rs";

	/* Tell mac80211 our अक्षरacteristics */
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SPECTRUM_MGMT);
	ieee80211_hw_set(hw, NEED_DTIM_BEFORE_ASSOC);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	अगर (il->cfg->sku & IL_SKU_N)
		hw->wiphy->features |= NL80211_FEATURE_DYNAMIC_SMPS |
				       NL80211_FEATURE_STATIC_SMPS;

	hw->sta_data_size = माप(काष्ठा il_station_priv);
	hw->vअगर_data_size = माप(काष्ठा il_vअगर_priv);

	hw->wiphy->पूर्णांकerface_modes =
	    BIT(NL80211_IFTYPE_STATION) | BIT(NL80211_IFTYPE_ADHOC);

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	hw->wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
				       REGULATORY_DISABLE_BEACON_HINTS;

	/*
	 * For now, disable PS by शेष because it affects
	 * RX perक्रमmance signअगरicantly.
	 */
	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->max_scan_ssids = PROBE_OPTION_MAX;
	/* we create the 802.11 header and a zero-length SSID element */
	hw->wiphy->max_scan_ie_len = max_probe_length - 24 - 2;

	/* Default value; 4 EDCA QOS priorities */
	hw->queues = 4;

	hw->max_listen_पूर्णांकerval = IL_CONN_MAX_LISTEN_INTERVAL;

	अगर (il->bands[NL80211_BAND_2GHZ].n_channels)
		il->hw->wiphy->bands[NL80211_BAND_2GHZ] =
		    &il->bands[NL80211_BAND_2GHZ];
	अगर (il->bands[NL80211_BAND_5GHZ].n_channels)
		il->hw->wiphy->bands[NL80211_BAND_5GHZ] =
		    &il->bands[NL80211_BAND_5GHZ];

	il_leds_init(il);

	wiphy_ext_feature_set(il->hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	ret = ieee80211_रेजिस्टर_hw(il->hw);
	अगर (ret) अणु
		IL_ERR("Failed to register hw (error %d)\n", ret);
		वापस ret;
	पूर्ण
	il->mac80211_रेजिस्टरed = 1;

	वापस 0;
पूर्ण

पूर्णांक
il4965_mac_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret;

	D_MAC80211("enter\n");

	/* we should be verअगरying the device is पढ़ोy to be खोलोed */
	mutex_lock(&il->mutex);
	ret = __il4965_up(il);
	mutex_unlock(&il->mutex);

	अगर (ret)
		वापस ret;

	अगर (il_is_rfसमाप्त(il))
		जाओ out;

	D_INFO("Start UP work done.\n");

	/* Wait क्रम START_ALIVE from Run Time ucode. Otherwise callbacks from
	 * mac80211 will not be run successfully. */
	ret = रुको_event_समयout(il->रुको_command_queue,
				 test_bit(S_READY, &il->status),
				 UCODE_READY_TIMEOUT);
	अगर (!ret) अणु
		अगर (!test_bit(S_READY, &il->status)) अणु
			IL_ERR("START_ALIVE timeout after %dms.\n",
				jअगरfies_to_msecs(UCODE_READY_TIMEOUT));
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	il4965_led_enable(il);

out:
	il->is_खोलो = 1;
	D_MAC80211("leave\n");
	वापस 0;
पूर्ण

व्योम
il4965_mac_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा il_priv *il = hw->priv;

	D_MAC80211("enter\n");

	अगर (!il->is_खोलो)
		वापस;

	il->is_खोलो = 0;

	il4965_करोwn(il);

	flush_workqueue(il->workqueue);

	/* User space software may expect getting rfसमाप्त changes
	 * even अगर पूर्णांकerface is करोwn */
	_il_wr(il, CSR_INT, 0xFFFFFFFF);
	il_enable_rfसमाप्त_पूर्णांक(il);

	D_MAC80211("leave\n");
पूर्ण

व्योम
il4965_mac_tx(काष्ठा ieee80211_hw *hw,
	      काष्ठा ieee80211_tx_control *control,
	      काष्ठा sk_buff *skb)
अणु
	काष्ठा il_priv *il = hw->priv;

	D_MACDUMP("enter\n");

	D_TX("dev->xmit(%d bytes) at rate 0x%02x\n", skb->len,
	     ieee80211_get_tx_rate(hw, IEEE80211_SKB_CB(skb))->bitrate);

	अगर (il4965_tx_skb(il, control->sta, skb))
		dev_kमुक्त_skb_any(skb);

	D_MACDUMP("leave\n");
पूर्ण

व्योम
il4965_mac_update_tkip_key(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_key_conf *keyconf,
			   काष्ठा ieee80211_sta *sta, u32 iv32, u16 * phase1key)
अणु
	काष्ठा il_priv *il = hw->priv;

	D_MAC80211("enter\n");

	il4965_update_tkip_key(il, keyconf, sta, iv32, phase1key);

	D_MAC80211("leave\n");
पूर्ण

पूर्णांक
il4965_mac_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		   काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		   काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret;
	u8 sta_id;
	bool is_शेष_wep_key = false;

	D_MAC80211("enter\n");

	अगर (il->cfg->mod_params->sw_crypto) अणु
		D_MAC80211("leave - hwcrypto disabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * To support IBSS RSN, करोn't program group keys in IBSS, the
	 * hardware will then not attempt to decrypt the frames.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		D_MAC80211("leave - ad-hoc group key\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	sta_id = il_sta_id_or_broadcast(il, sta);
	अगर (sta_id == IL_INVALID_STATION)
		वापस -EINVAL;

	mutex_lock(&il->mutex);
	il_scan_cancel_समयout(il, 100);

	/*
	 * If we are getting WEP group key and we didn't receive any key mapping
	 * so far, we are in legacy wep mode (group key only), otherwise we are
	 * in 1X mode.
	 * In legacy wep mode, we use another host command to the uCode.
	 */
	अगर ((key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	     key->cipher == WLAN_CIPHER_SUITE_WEP104) && !sta) अणु
		अगर (cmd == SET_KEY)
			is_शेष_wep_key = !il->_4965.key_mapping_keys;
		अन्यथा
			is_शेष_wep_key =
			    (key->hw_key_idx == HW_KEY_DEFAULT);
	पूर्ण

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (is_शेष_wep_key)
			ret = il4965_set_शेष_wep_key(il, key);
		अन्यथा
			ret = il4965_set_dynamic_key(il, key, sta_id);

		D_MAC80211("enable hwcrypto key\n");
		अवरोध;
	हाल DISABLE_KEY:
		अगर (is_शेष_wep_key)
			ret = il4965_हटाओ_शेष_wep_key(il, key);
		अन्यथा
			ret = il4965_हटाओ_dynamic_key(il, key, sta_id);

		D_MAC80211("disable hwcrypto key\n");
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&il->mutex);
	D_MAC80211("leave\n");

	वापस ret;
पूर्ण

पूर्णांक
il4965_mac_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret = -EINVAL;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;

	D_HT("A-MPDU action on addr %pM tid %d\n", sta->addr, tid);

	अगर (!(il->cfg->sku & IL_SKU_N))
		वापस -EACCES;

	mutex_lock(&il->mutex);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		D_HT("start Rx\n");
		ret = il4965_sta_rx_agg_start(il, sta, tid, *ssn);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		D_HT("stop Rx\n");
		ret = il4965_sta_rx_agg_stop(il, sta, tid);
		अगर (test_bit(S_EXIT_PENDING, &il->status))
			ret = 0;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		D_HT("start Tx\n");
		ret = il4965_tx_agg_start(il, vअगर, sta, tid, ssn);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		D_HT("stop Tx\n");
		ret = il4965_tx_agg_stop(il, vअगर, sta, tid);
		अगर (test_bit(S_EXIT_PENDING, &il->status))
			ret = 0;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = 0;
		अवरोध;
	पूर्ण
	mutex_unlock(&il->mutex);

	वापस ret;
पूर्ण

पूर्णांक
il4965_mac_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा il_priv *il = hw->priv;
	काष्ठा il_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	bool is_ap = vअगर->type == NL80211_IFTYPE_STATION;
	पूर्णांक ret;
	u8 sta_id;

	D_INFO("received request to add station %pM\n", sta->addr);
	mutex_lock(&il->mutex);
	D_INFO("proceeding to add station %pM\n", sta->addr);
	sta_priv->common.sta_id = IL_INVALID_STATION;

	atomic_set(&sta_priv->pending_frames, 0);

	ret =
	    il_add_station_common(il, sta->addr, is_ap, sta, &sta_id);
	अगर (ret) अणु
		IL_ERR("Unable to add station %pM (%d)\n", sta->addr, ret);
		/* Should we वापस success अगर वापस code is EEXIST ? */
		mutex_unlock(&il->mutex);
		वापस ret;
	पूर्ण

	sta_priv->common.sta_id = sta_id;

	/* Initialize rate scaling */
	D_INFO("Initializing rate scaling for station %pM\n", sta->addr);
	il4965_rs_rate_init(il, sta, sta_id);
	mutex_unlock(&il->mutex);

	वापस 0;
पूर्ण

व्योम
il4965_mac_channel_चयन(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	काष्ठा il_priv *il = hw->priv;
	स्थिर काष्ठा il_channel_info *ch_info;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ieee80211_channel *channel = ch_चयन->chandef.chan;
	काष्ठा il_ht_config *ht_conf = &il->current_ht_config;
	u16 ch;

	D_MAC80211("enter\n");

	mutex_lock(&il->mutex);

	अगर (il_is_rfसमाप्त(il))
		जाओ out;

	अगर (test_bit(S_EXIT_PENDING, &il->status) ||
	    test_bit(S_SCANNING, &il->status) ||
	    test_bit(S_CHANNEL_SWITCH_PENDING, &il->status))
		जाओ out;

	अगर (!il_is_associated(il))
		जाओ out;

	अगर (!il->ops->set_channel_चयन)
		जाओ out;

	ch = channel->hw_value;
	अगर (le16_to_cpu(il->active.channel) == ch)
		जाओ out;

	ch_info = il_get_channel_info(il, channel->band, ch);
	अगर (!il_is_channel_valid(ch_info)) अणु
		D_MAC80211("invalid channel\n");
		जाओ out;
	पूर्ण

	spin_lock_irq(&il->lock);

	il->current_ht_config.smps = conf->smps_mode;

	/* Configure HT40 channels */
	चयन (cfg80211_get_chandef_type(&ch_चयन->chandef)) अणु
	हाल NL80211_CHAN_NO_HT:
	हाल NL80211_CHAN_HT20:
		il->ht.is_40mhz = false;
		il->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_NONE;
		अवरोध;
	हाल NL80211_CHAN_HT40MINUS:
		il->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		il->ht.is_40mhz = true;
		अवरोध;
	हाल NL80211_CHAN_HT40PLUS:
		il->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		il->ht.is_40mhz = true;
		अवरोध;
	पूर्ण

	अगर ((le16_to_cpu(il->staging.channel) != ch))
		il->staging.flags = 0;

	il_set_rxon_channel(il, channel);
	il_set_rxon_ht(il, ht_conf);
	il_set_flags_क्रम_band(il, channel->band, il->vअगर);

	spin_unlock_irq(&il->lock);

	il_set_rate(il);
	/*
	 * at this poपूर्णांक, staging_rxon has the
	 * configuration क्रम channel चयन
	 */
	set_bit(S_CHANNEL_SWITCH_PENDING, &il->status);
	il->चयन_channel = cpu_to_le16(ch);
	अगर (il->ops->set_channel_चयन(il, ch_चयन)) अणु
		clear_bit(S_CHANNEL_SWITCH_PENDING, &il->status);
		il->चयन_channel = 0;
		ieee80211_chचयन_करोne(il->vअगर, false);
	पूर्ण

out:
	mutex_unlock(&il->mutex);
	D_MAC80211("leave\n");
पूर्ण

व्योम
il4965_configure_filter(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक changed_flags,
			अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा il_priv *il = hw->priv;
	__le32 filter_or = 0, filter_nand = 0;

#घोषणा CHK(test, flag)	करो अणु \
	अगर (*total_flags & (test))		\
		filter_or |= (flag);		\
	अन्यथा					\
		filter_nand |= (flag);		\
	पूर्ण जबतक (0)

	D_MAC80211("Enter: changed: 0x%x, total: 0x%x\n", changed_flags,
		   *total_flags);

	CHK(FIF_OTHER_BSS, RXON_FILTER_PROMISC_MSK);
	/* Setting _just_ RXON_FILTER_CTL2HOST_MSK causes FH errors */
	CHK(FIF_CONTROL, RXON_FILTER_CTL2HOST_MSK | RXON_FILTER_PROMISC_MSK);
	CHK(FIF_BCN_PRBRESP_PROMISC, RXON_FILTER_BCON_AWARE_MSK);

#अघोषित CHK

	mutex_lock(&il->mutex);

	il->staging.filter_flags &= ~filter_nand;
	il->staging.filter_flags |= filter_or;

	/*
	 * Not committing directly because hardware can perक्रमm a scan,
	 * but we'll eventually commit the filter flags change anyway.
	 */

	mutex_unlock(&il->mutex);

	/*
	 * Receiving all multicast frames is always enabled by the
	 * शेष flags setup in il_connection_init_rx_config()
	 * since we currently करो not support programming multicast
	 * filters पूर्णांकo the device.
	 */
	*total_flags &=
	    FIF_OTHER_BSS | FIF_ALLMULTI |
	    FIF_BCN_PRBRESP_PROMISC | FIF_CONTROL;
पूर्ण

/*****************************************************************************
 *
 * driver setup and tearकरोwn
 *
 *****************************************************************************/

अटल व्योम
il4965_bg_txघातer_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा il_priv *il = container_of(work, काष्ठा il_priv,
					  txघातer_work);

	mutex_lock(&il->mutex);

	/* If a scan happened to start beक्रमe we got here
	 * then just वापस; the stats notअगरication will
	 * kick off another scheduled work to compensate क्रम
	 * any temperature delta we missed here. */
	अगर (test_bit(S_EXIT_PENDING, &il->status) ||
	    test_bit(S_SCANNING, &il->status))
		जाओ out;

	/* Regardless of अगर we are associated, we must reconfigure the
	 * TX घातer since frames can be sent on non-radar channels जबतक
	 * not associated */
	il->ops->send_tx_घातer(il);

	/* Update last_temperature to keep is_calib_needed from running
	 * when it isn't needed... */
	il->last_temperature = il->temperature;
out:
	mutex_unlock(&il->mutex);
पूर्ण

अटल व्योम
il4965_setup_deferred_work(काष्ठा il_priv *il)
अणु
	il->workqueue = create_singlethपढ़ो_workqueue(DRV_NAME);

	init_रुकोqueue_head(&il->रुको_command_queue);

	INIT_WORK(&il->restart, il4965_bg_restart);
	INIT_WORK(&il->rx_replenish, il4965_bg_rx_replenish);
	INIT_WORK(&il->run_समय_calib_work, il4965_bg_run_समय_calib_work);
	INIT_DELAYED_WORK(&il->init_alive_start, il4965_bg_init_alive_start);
	INIT_DELAYED_WORK(&il->alive_start, il4965_bg_alive_start);

	il_setup_scan_deferred_work(il);

	INIT_WORK(&il->txघातer_work, il4965_bg_txघातer_work);

	समयr_setup(&il->stats_periodic, il4965_bg_stats_periodic, 0);

	समयr_setup(&il->watchकरोg, il_bg_watchकरोg, 0);

	tasklet_setup(&il->irq_tasklet, il4965_irq_tasklet);
पूर्ण

अटल व्योम
il4965_cancel_deferred_work(काष्ठा il_priv *il)
अणु
	cancel_work_sync(&il->txघातer_work);
	cancel_delayed_work_sync(&il->init_alive_start);
	cancel_delayed_work(&il->alive_start);
	cancel_work_sync(&il->run_समय_calib_work);

	il_cancel_scan_deferred_work(il);

	del_समयr_sync(&il->stats_periodic);
पूर्ण

अटल व्योम
il4965_init_hw_rates(काष्ठा il_priv *il, काष्ठा ieee80211_rate *rates)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RATE_COUNT_LEGACY; i++) अणु
		rates[i].bitrate = il_rates[i].ieee * 5;
		rates[i].hw_value = i;	/* Rate scaling will work on idxes */
		rates[i].hw_value_लघु = i;
		rates[i].flags = 0;
		अगर ((i >= IL_FIRST_CCK_RATE) && (i <= IL_LAST_CCK_RATE)) अणु
			/*
			 * If CCK != 1M then set लघु preamble rate flag.
			 */
			rates[i].flags |=
			    (il_rates[i].plcp ==
			     RATE_1M_PLCP) ? 0 : IEEE80211_RATE_SHORT_PREAMBLE;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Acquire il->lock beक्रमe calling this function !
 */
व्योम
il4965_set_wr_ptrs(काष्ठा il_priv *il, पूर्णांक txq_id, u32 idx)
अणु
	il_wr(il, HBUS_TARG_WRPTR, (idx & 0xff) | (txq_id << 8));
	il_wr_prph(il, IL49_SCD_QUEUE_RDPTR(txq_id), idx);
पूर्ण

व्योम
il4965_tx_queue_set_status(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq,
			   पूर्णांक tx_fअगरo_id, पूर्णांक scd_retry)
अणु
	पूर्णांक txq_id = txq->q.id;

	/* Find out whether to activate Tx queue */
	पूर्णांक active = test_bit(txq_id, &il->txq_ctx_active_msk) ? 1 : 0;

	/* Set up and activate */
	il_wr_prph(il, IL49_SCD_QUEUE_STATUS_BITS(txq_id),
		   (active << IL49_SCD_QUEUE_STTS_REG_POS_ACTIVE) |
		   (tx_fअगरo_id << IL49_SCD_QUEUE_STTS_REG_POS_TXF) |
		   (scd_retry << IL49_SCD_QUEUE_STTS_REG_POS_WSL) |
		   (scd_retry << IL49_SCD_QUEUE_STTS_REG_POS_SCD_ACK) |
		   IL49_SCD_QUEUE_STTS_REG_MSK);

	txq->sched_retry = scd_retry;

	D_INFO("%s %s Queue %d on AC %d\n", active ? "Activate" : "Deactivate",
	       scd_retry ? "BA" : "AC", txq_id, tx_fअगरo_id);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops il4965_mac_ops = अणु
	.tx = il4965_mac_tx,
	.start = il4965_mac_start,
	.stop = il4965_mac_stop,
	.add_पूर्णांकerface = il_mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = il_mac_हटाओ_पूर्णांकerface,
	.change_पूर्णांकerface = il_mac_change_पूर्णांकerface,
	.config = il_mac_config,
	.configure_filter = il4965_configure_filter,
	.set_key = il4965_mac_set_key,
	.update_tkip_key = il4965_mac_update_tkip_key,
	.conf_tx = il_mac_conf_tx,
	.reset_tsf = il_mac_reset_tsf,
	.bss_info_changed = il_mac_bss_info_changed,
	.ampdu_action = il4965_mac_ampdu_action,
	.hw_scan = il_mac_hw_scan,
	.sta_add = il4965_mac_sta_add,
	.sta_हटाओ = il_mac_sta_हटाओ,
	.channel_चयन = il4965_mac_channel_चयन,
	.tx_last_beacon = il_mac_tx_last_beacon,
	.flush = il_mac_flush,
पूर्ण;

अटल पूर्णांक
il4965_init_drv(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;

	spin_lock_init(&il->sta_lock);
	spin_lock_init(&il->hcmd_lock);

	INIT_LIST_HEAD(&il->मुक्त_frames);

	mutex_init(&il->mutex);

	il->ieee_channels = शून्य;
	il->ieee_rates = शून्य;
	il->band = NL80211_BAND_2GHZ;

	il->iw_mode = NL80211_IFTYPE_STATION;
	il->current_ht_config.smps = IEEE80211_SMPS_STATIC;
	il->missed_beacon_threshold = IL_MISSED_BEACON_THRESHOLD_DEF;

	/* initialize क्रमce reset */
	il->क्रमce_reset.reset_duration = IL_DELAY_NEXT_FORCE_FW_RELOAD;

	/* Choose which receivers/antennas to use */
	अगर (il->ops->set_rxon_chain)
		il->ops->set_rxon_chain(il);

	il_init_scan_params(il);

	ret = il_init_channel_map(il);
	अगर (ret) अणु
		IL_ERR("initializing regulatory failed: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = il_init_geos(il);
	अगर (ret) अणु
		IL_ERR("initializing geos failed: %d\n", ret);
		जाओ err_मुक्त_channel_map;
	पूर्ण
	il4965_init_hw_rates(il, il->ieee_rates);

	वापस 0;

err_मुक्त_channel_map:
	il_मुक्त_channel_map(il);
err:
	वापस ret;
पूर्ण

अटल व्योम
il4965_uninit_drv(काष्ठा il_priv *il)
अणु
	il_मुक्त_geos(il);
	il_मुक्त_channel_map(il);
	kमुक्त(il->scan_cmd);
पूर्ण

अटल व्योम
il4965_hw_detect(काष्ठा il_priv *il)
अणु
	il->hw_rev = _il_rd(il, CSR_HW_REV);
	il->hw_wa_rev = _il_rd(il, CSR_HW_REV_WA_REG);
	il->rev_id = il->pci_dev->revision;
	D_INFO("HW Revision ID = 0x%X\n", il->rev_id);
पूर्ण

अटल स्थिर काष्ठा il_sensitivity_ranges il4965_sensitivity = अणु
	.min_nrg_cck = 97,
	.max_nrg_cck = 0,	/* not used, set to 0 */

	.स्वतः_corr_min_ofdm = 85,
	.स्वतः_corr_min_ofdm_mrc = 170,
	.स्वतः_corr_min_ofdm_x1 = 105,
	.स्वतः_corr_min_ofdm_mrc_x1 = 220,

	.स्वतः_corr_max_ofdm = 120,
	.स्वतः_corr_max_ofdm_mrc = 210,
	.स्वतः_corr_max_ofdm_x1 = 140,
	.स्वतः_corr_max_ofdm_mrc_x1 = 270,

	.स्वतः_corr_min_cck = 125,
	.स्वतः_corr_max_cck = 200,
	.स्वतः_corr_min_cck_mrc = 200,
	.स्वतः_corr_max_cck_mrc = 400,

	.nrg_th_cck = 100,
	.nrg_th_ofdm = 100,

	.barker_corr_th_min = 190,
	.barker_corr_th_min_mrc = 390,
	.nrg_th_cca = 62,
पूर्ण;

अटल व्योम
il4965_set_hw_params(काष्ठा il_priv *il)
अणु
	il->hw_params.bcast_id = IL4965_BROADCAST_ID;
	il->hw_params.max_rxq_size = RX_QUEUE_SIZE;
	il->hw_params.max_rxq_log = RX_QUEUE_SIZE_LOG;
	अगर (il->cfg->mod_params->amsdu_size_8K)
		il->hw_params.rx_page_order = get_order(IL_RX_BUF_SIZE_8K);
	अन्यथा
		il->hw_params.rx_page_order = get_order(IL_RX_BUF_SIZE_4K);

	il->hw_params.max_beacon_itrvl = IL_MAX_UCODE_BEACON_INTERVAL;

	अगर (il->cfg->mod_params->disable_11n)
		il->cfg->sku &= ~IL_SKU_N;

	अगर (il->cfg->mod_params->num_of_queues >= IL_MIN_NUM_QUEUES &&
	    il->cfg->mod_params->num_of_queues <= IL49_NUM_QUEUES)
		il->cfg->num_of_queues =
		    il->cfg->mod_params->num_of_queues;

	il->hw_params.max_txq_num = il->cfg->num_of_queues;
	il->hw_params.dma_chnl_num = FH49_TCSR_CHNL_NUM;
	il->hw_params.scd_bc_tbls_size =
	    il->cfg->num_of_queues *
	    माप(काष्ठा il4965_scd_bc_tbl);

	il->hw_params.tfd_size = माप(काष्ठा il_tfd);
	il->hw_params.max_stations = IL4965_STATION_COUNT;
	il->hw_params.max_data_size = IL49_RTC_DATA_SIZE;
	il->hw_params.max_inst_size = IL49_RTC_INST_SIZE;
	il->hw_params.max_bsm_size = BSM_SRAM_SIZE;
	il->hw_params.ht40_channel = BIT(NL80211_BAND_5GHZ);

	il->hw_params.rx_wrt_ptr_reg = FH49_RSCSR_CHNL0_WPTR;

	il->hw_params.tx_chains_num = il4965_num_of_ant(il->cfg->valid_tx_ant);
	il->hw_params.rx_chains_num = il4965_num_of_ant(il->cfg->valid_rx_ant);
	il->hw_params.valid_tx_ant = il->cfg->valid_tx_ant;
	il->hw_params.valid_rx_ant = il->cfg->valid_rx_ant;

	il->hw_params.ct_समाप्त_threshold =
	   celsius_to_kelvin(CT_KILL_THRESHOLD_LEGACY);

	il->hw_params.sens = &il4965_sensitivity;
	il->hw_params.beacon_समय_प्रकारsf_bits = IL4965_EXT_BEACON_TIME_POS;
पूर्ण

अटल पूर्णांक
il4965_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक err = 0;
	काष्ठा il_priv *il;
	काष्ठा ieee80211_hw *hw;
	काष्ठा il_cfg *cfg = (काष्ठा il_cfg *)(ent->driver_data);
	अचिन्हित दीर्घ flags;
	u16 pci_cmd;

	/************************
	 * 1. Allocating HW data
	 ************************/

	hw = ieee80211_alloc_hw(माप(काष्ठा il_priv), &il4965_mac_ops);
	अगर (!hw) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	il = hw->priv;
	il->hw = hw;
	SET_IEEE80211_DEV(hw, &pdev->dev);

	D_INFO("*** LOAD DRIVER ***\n");
	il->cfg = cfg;
	il->ops = &il4965_ops;
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	il->debugfs_ops = &il4965_debugfs_ops;
#पूर्ण_अगर
	il->pci_dev = pdev;
	il->पूर्णांकa_mask = CSR_INI_SET_MASK;

	/**************************
	 * 2. Initializing PCI bus
	 **************************/
	pci_disable_link_state(pdev,
			       PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1 |
			       PCIE_LINK_STATE_CLKPM);

	अगर (pci_enable_device(pdev)) अणु
		err = -ENODEV;
		जाओ out_ieee80211_मुक्त_hw;
	पूर्ण

	pci_set_master(pdev);

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(36));
	अगर (!err)
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(36));
	अगर (err) अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (!err)
			err =
			    pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
		/* both attempts failed: */
		अगर (err) अणु
			IL_WARN("No suitable DMA available.\n");
			जाओ out_pci_disable_device;
		पूर्ण
	पूर्ण

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err)
		जाओ out_pci_disable_device;

	pci_set_drvdata(pdev, il);

	/***********************
	 * 3. Read REV रेजिस्टर
	 ***********************/
	il->hw_base = pci_ioremap_bar(pdev, 0);
	अगर (!il->hw_base) अणु
		err = -ENODEV;
		जाओ out_pci_release_regions;
	पूर्ण

	D_INFO("pci_resource_len = 0x%08llx\n",
	       (अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, 0));
	D_INFO("pci_resource_base = %p\n", il->hw_base);

	/* these spin locks will be used in apm_ops.init and EEPROM access
	 * we should init now
	 */
	spin_lock_init(&il->reg_lock);
	spin_lock_init(&il->lock);

	/*
	 * stop and reset the on-board processor just in हाल it is in a
	 * strange state ... like being left stअक्रमed by a primary kernel
	 * and this is now the kdump kernel trying to start up
	 */
	_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_NEVO_RESET);

	il4965_hw_detect(il);
	IL_INFO("Detected %s, REV=0x%X\n", il->cfg->name, il->hw_rev);

	/* We disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state */
	pci_ग_लिखो_config_byte(pdev, PCI_CFG_RETRY_TIMEOUT, 0x00);

	il4965_prepare_card_hw(il);
	अगर (!il->hw_पढ़ोy) अणु
		IL_WARN("Failed, HW not ready\n");
		err = -EIO;
		जाओ out_iounmap;
	पूर्ण

	/*****************
	 * 4. Read EEPROM
	 *****************/
	/* Read the EEPROM */
	err = il_eeprom_init(il);
	अगर (err) अणु
		IL_ERR("Unable to init EEPROM\n");
		जाओ out_iounmap;
	पूर्ण
	err = il4965_eeprom_check_version(il);
	अगर (err)
		जाओ out_मुक्त_eeprom;

	/* extract MAC Address */
	il4965_eeprom_get_mac(il, il->addresses[0].addr);
	D_INFO("MAC address: %pM\n", il->addresses[0].addr);
	il->hw->wiphy->addresses = il->addresses;
	il->hw->wiphy->n_addresses = 1;

	/************************
	 * 5. Setup HW स्थिरants
	 ************************/
	il4965_set_hw_params(il);

	/*******************
	 * 6. Setup il
	 *******************/

	err = il4965_init_drv(il);
	अगर (err)
		जाओ out_मुक्त_eeprom;
	/* At this poपूर्णांक both hw and il are initialized. */

	/********************
	 * 7. Setup services
	 ********************/
	spin_lock_irqsave(&il->lock, flags);
	il_disable_पूर्णांकerrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	pci_enable_msi(il->pci_dev);

	err = request_irq(il->pci_dev->irq, il_isr, IRQF_SHARED, DRV_NAME, il);
	अगर (err) अणु
		IL_ERR("Error allocating IRQ %d\n", il->pci_dev->irq);
		जाओ out_disable_msi;
	पूर्ण

	il4965_setup_deferred_work(il);
	il4965_setup_handlers(il);

	/*********************************************
	 * 8. Enable पूर्णांकerrupts and पढ़ो RFKILL state
	 *********************************************/

	/* enable rfसमाप्त पूर्णांकerrupt: hw bug w/a */
	pci_पढ़ो_config_word(il->pci_dev, PCI_COMMAND, &pci_cmd);
	अगर (pci_cmd & PCI_COMMAND_INTX_DISABLE) अणु
		pci_cmd &= ~PCI_COMMAND_INTX_DISABLE;
		pci_ग_लिखो_config_word(il->pci_dev, PCI_COMMAND, pci_cmd);
	पूर्ण

	il_enable_rfसमाप्त_पूर्णांक(il);

	/* If platक्रमm's RF_KILL चयन is NOT set to KILL */
	अगर (_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW)
		clear_bit(S_RFKILL, &il->status);
	अन्यथा
		set_bit(S_RFKILL, &il->status);

	wiphy_rfसमाप्त_set_hw_state(il->hw->wiphy,
				  test_bit(S_RFKILL, &il->status));

	il_घातer_initialize(il);

	init_completion(&il->_4965.firmware_loading_complete);

	err = il4965_request_firmware(il, true);
	अगर (err)
		जाओ out_destroy_workqueue;

	वापस 0;

out_destroy_workqueue:
	destroy_workqueue(il->workqueue);
	il->workqueue = शून्य;
	मुक्त_irq(il->pci_dev->irq, il);
out_disable_msi:
	pci_disable_msi(il->pci_dev);
	il4965_uninit_drv(il);
out_मुक्त_eeprom:
	il_eeprom_मुक्त(il);
out_iounmap:
	iounmap(il->hw_base);
out_pci_release_regions:
	pci_release_regions(pdev);
out_pci_disable_device:
	pci_disable_device(pdev);
out_ieee80211_मुक्त_hw:
	ieee80211_मुक्त_hw(il->hw);
out:
	वापस err;
पूर्ण

अटल व्योम
il4965_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा il_priv *il = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;

	अगर (!il)
		वापस;

	रुको_क्रम_completion(&il->_4965.firmware_loading_complete);

	D_INFO("*** UNLOAD DRIVER ***\n");

	il_dbgfs_unरेजिस्टर(il);
	sysfs_हटाओ_group(&pdev->dev.kobj, &il_attribute_group);

	/* ieee80211_unरेजिस्टर_hw call wil cause il_mac_stop to
	 * to be called and il4965_करोwn since we are removing the device
	 * we need to set S_EXIT_PENDING bit.
	 */
	set_bit(S_EXIT_PENDING, &il->status);

	il_leds_निकास(il);

	अगर (il->mac80211_रेजिस्टरed) अणु
		ieee80211_unरेजिस्टर_hw(il->hw);
		il->mac80211_रेजिस्टरed = 0;
	पूर्ण अन्यथा अणु
		il4965_करोwn(il);
	पूर्ण

	/*
	 * Make sure device is reset to low घातer beक्रमe unloading driver.
	 * This may be redundant with il4965_करोwn(), but there are paths to
	 * run il4965_करोwn() without calling apm_ops.stop(), and there are
	 * paths to aव्योम running il4965_करोwn() at all beक्रमe leaving driver.
	 * This (inexpensive) call *makes sure* device is reset.
	 */
	il_apm_stop(il);

	/* make sure we flush any pending irq or
	 * tasklet क्रम the driver
	 */
	spin_lock_irqsave(&il->lock, flags);
	il_disable_पूर्णांकerrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);

	il4965_synchronize_irq(il);

	il4965_dealloc_ucode_pci(il);

	अगर (il->rxq.bd)
		il4965_rx_queue_मुक्त(il, &il->rxq);
	il4965_hw_txq_ctx_मुक्त(il);

	il_eeprom_मुक्त(il);

	/*netअगर_stop_queue(dev); */
	flush_workqueue(il->workqueue);

	/* ieee80211_unरेजिस्टर_hw calls il_mac_stop, which flushes
	 * il->workqueue... so we can't take करोwn the workqueue
	 * until now... */
	destroy_workqueue(il->workqueue);
	il->workqueue = शून्य;

	मुक्त_irq(il->pci_dev->irq, il);
	pci_disable_msi(il->pci_dev);
	iounmap(il->hw_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	il4965_uninit_drv(il);

	dev_kमुक्त_skb(il->beacon_skb);

	ieee80211_मुक्त_hw(il->hw);
पूर्ण

/*
 * Activate/Deactivate Tx DMA/FIFO channels according tx fअगरos mask
 * must be called under il->lock and mac access
 */
व्योम
il4965_txq_set_sched(काष्ठा il_priv *il, u32 mask)
अणु
	il_wr_prph(il, IL49_SCD_TXFACT, mask);
पूर्ण

/*****************************************************************************
 *
 * driver and module entry poपूर्णांक
 *
 *****************************************************************************/

/* Hardware specअगरic file defines the PCI IDs table क्रम that hardware module */
अटल स्थिर काष्ठा pci_device_id il4965_hw_card_ids[] = अणु
	अणुIL_PCI_DEVICE(0x4229, PCI_ANY_ID, il4965_cfg)पूर्ण,
	अणुIL_PCI_DEVICE(0x4230, PCI_ANY_ID, il4965_cfg)पूर्ण,
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, il4965_hw_card_ids);

अटल काष्ठा pci_driver il4965_driver = अणु
	.name = DRV_NAME,
	.id_table = il4965_hw_card_ids,
	.probe = il4965_pci_probe,
	.हटाओ = il4965_pci_हटाओ,
	.driver.pm = IL_LEGACY_PM_OPS,
पूर्ण;

अटल पूर्णांक __init
il4965_init(व्योम)
अणु

	पूर्णांक ret;
	pr_info(DRV_DESCRIPTION ", " DRV_VERSION "\n");
	pr_info(DRV_COPYRIGHT "\n");

	ret = il4965_rate_control_रेजिस्टर();
	अगर (ret) अणु
		pr_err("Unable to register rate control algorithm: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pci_रेजिस्टर_driver(&il4965_driver);
	अगर (ret) अणु
		pr_err("Unable to initialize PCI module\n");
		जाओ error_रेजिस्टर;
	पूर्ण

	वापस ret;

error_रेजिस्टर:
	il4965_rate_control_unरेजिस्टर();
	वापस ret;
पूर्ण

अटल व्योम __निकास
il4965_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&il4965_driver);
	il4965_rate_control_unरेजिस्टर();
पूर्ण

module_निकास(il4965_निकास);
module_init(il4965_init);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
module_param_named(debug, il_debug_level, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug output mask");
#पूर्ण_अगर

module_param_named(swcrypto, il4965_mod_params.sw_crypto, पूर्णांक, 0444);
MODULE_PARM_DESC(swcrypto, "using crypto in software (default 0 [hardware])");
module_param_named(queues_num, il4965_mod_params.num_of_queues, पूर्णांक, 0444);
MODULE_PARM_DESC(queues_num, "number of hw queues.");
module_param_named(11n_disable, il4965_mod_params.disable_11n, पूर्णांक, 0444);
MODULE_PARM_DESC(11n_disable, "disable 11n functionality");
module_param_named(amsdu_size_8K, il4965_mod_params.amsdu_size_8K, पूर्णांक, 0444);
MODULE_PARM_DESC(amsdu_size_8K, "enable 8K amsdu size (default 0 [disabled])");
module_param_named(fw_restart, il4965_mod_params.restart_fw, पूर्णांक, 0444);
MODULE_PARM_DESC(fw_restart, "restart firmware in case of error");
