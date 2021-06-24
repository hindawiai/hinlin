<शैली गुरु>
/*
 * Copyright (c) 2013 Johannes Berg <johannes@sipsolutions.net>
 *
 *  This file is मुक्त software: you may copy, redistribute and/or modअगरy it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This file is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/aer.h>
#समावेश <linux/bitops.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/crc32.h>
#समावेश "alx.h"
#समावेश "hw.h"
#समावेश "reg.h"

अटल स्थिर अक्षर alx_drv_name[] = "alx";

अटल व्योम alx_मुक्त_txbuf(काष्ठा alx_tx_queue *txq, पूर्णांक entry)
अणु
	काष्ठा alx_buffer *txb = &txq->bufs[entry];

	अगर (dma_unmap_len(txb, size)) अणु
		dma_unmap_single(txq->dev,
				 dma_unmap_addr(txb, dma),
				 dma_unmap_len(txb, size),
				 DMA_TO_DEVICE);
		dma_unmap_len_set(txb, size, 0);
	पूर्ण

	अगर (txb->skb) अणु
		dev_kमुक्त_skb_any(txb->skb);
		txb->skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alx_refill_rx_ring(काष्ठा alx_priv *alx, gfp_t gfp)
अणु
	काष्ठा alx_rx_queue *rxq = alx->qnapi[0]->rxq;
	काष्ठा sk_buff *skb;
	काष्ठा alx_buffer *cur_buf;
	dma_addr_t dma;
	u16 cur, next, count = 0;

	next = cur = rxq->ग_लिखो_idx;
	अगर (++next == alx->rx_ringsz)
		next = 0;
	cur_buf = &rxq->bufs[cur];

	जबतक (!cur_buf->skb && next != rxq->पढ़ो_idx) अणु
		काष्ठा alx_rfd *rfd = &rxq->rfd[cur];

		/*
		 * When DMA RX address is set to something like
		 * 0x....fc0, it will be very likely to cause DMA
		 * RFD overflow issue.
		 *
		 * To work around it, we apply rx skb with 64 bytes
		 * दीर्घer space, and offset the address whenever
		 * 0x....fc0 is detected.
		 */
		skb = __netdev_alloc_skb(alx->dev, alx->rxbuf_size + 64, gfp);
		अगर (!skb)
			अवरोध;

		अगर (((अचिन्हित दीर्घ)skb->data & 0xfff) == 0xfc0)
			skb_reserve(skb, 64);

		dma = dma_map_single(&alx->hw.pdev->dev,
				     skb->data, alx->rxbuf_size,
				     DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&alx->hw.pdev->dev, dma)) अणु
			dev_kमुक्त_skb(skb);
			अवरोध;
		पूर्ण

		/* Unक्रमtunately, RX descriptor buffers must be 4-byte
		 * aligned, so we can't use IP alignment.
		 */
		अगर (WARN_ON(dma & 3)) अणु
			dev_kमुक्त_skb(skb);
			अवरोध;
		पूर्ण

		cur_buf->skb = skb;
		dma_unmap_len_set(cur_buf, size, alx->rxbuf_size);
		dma_unmap_addr_set(cur_buf, dma, dma);
		rfd->addr = cpu_to_le64(dma);

		cur = next;
		अगर (++next == alx->rx_ringsz)
			next = 0;
		cur_buf = &rxq->bufs[cur];
		count++;
	पूर्ण

	अगर (count) अणु
		/* flush all updates beक्रमe updating hardware */
		wmb();
		rxq->ग_लिखो_idx = cur;
		alx_ग_लिखो_mem16(&alx->hw, ALX_RFD_PIDX, cur);
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा alx_tx_queue *alx_tx_queue_mapping(काष्ठा alx_priv *alx,
						 काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक r_idx = skb->queue_mapping;

	अगर (r_idx >= alx->num_txq)
		r_idx = r_idx % alx->num_txq;

	वापस alx->qnapi[r_idx]->txq;
पूर्ण

अटल काष्ठा netdev_queue *alx_get_tx_queue(स्थिर काष्ठा alx_tx_queue *txq)
अणु
	वापस netdev_get_tx_queue(txq->netdev, txq->queue_idx);
पूर्ण

अटल अंतरभूत पूर्णांक alx_tpd_avail(काष्ठा alx_tx_queue *txq)
अणु
	अगर (txq->ग_लिखो_idx >= txq->पढ़ो_idx)
		वापस txq->count + txq->पढ़ो_idx - txq->ग_लिखो_idx - 1;
	वापस txq->पढ़ो_idx - txq->ग_लिखो_idx - 1;
पूर्ण

अटल bool alx_clean_tx_irq(काष्ठा alx_tx_queue *txq)
अणु
	काष्ठा alx_priv *alx;
	काष्ठा netdev_queue *tx_queue;
	u16 hw_पढ़ो_idx, sw_पढ़ो_idx;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	पूर्णांक budget = ALX_DEFAULT_TX_WORK;

	alx = netdev_priv(txq->netdev);
	tx_queue = alx_get_tx_queue(txq);

	sw_पढ़ो_idx = txq->पढ़ो_idx;
	hw_पढ़ो_idx = alx_पढ़ो_mem16(&alx->hw, txq->c_reg);

	अगर (sw_पढ़ो_idx != hw_पढ़ो_idx) अणु
		जबतक (sw_पढ़ो_idx != hw_पढ़ो_idx && budget > 0) अणु
			काष्ठा sk_buff *skb;

			skb = txq->bufs[sw_पढ़ो_idx].skb;
			अगर (skb) अणु
				total_bytes += skb->len;
				total_packets++;
				budget--;
			पूर्ण

			alx_मुक्त_txbuf(txq, sw_पढ़ो_idx);

			अगर (++sw_पढ़ो_idx == txq->count)
				sw_पढ़ो_idx = 0;
		पूर्ण
		txq->पढ़ो_idx = sw_पढ़ो_idx;

		netdev_tx_completed_queue(tx_queue, total_packets, total_bytes);
	पूर्ण

	अगर (netअगर_tx_queue_stopped(tx_queue) && netअगर_carrier_ok(alx->dev) &&
	    alx_tpd_avail(txq) > txq->count / 4)
		netअगर_tx_wake_queue(tx_queue);

	वापस sw_पढ़ो_idx == hw_पढ़ो_idx;
पूर्ण

अटल व्योम alx_schedule_link_check(काष्ठा alx_priv *alx)
अणु
	schedule_work(&alx->link_check_wk);
पूर्ण

अटल व्योम alx_schedule_reset(काष्ठा alx_priv *alx)
अणु
	schedule_work(&alx->reset_wk);
पूर्ण

अटल पूर्णांक alx_clean_rx_irq(काष्ठा alx_rx_queue *rxq, पूर्णांक budget)
अणु
	काष्ठा alx_priv *alx;
	काष्ठा alx_rrd *rrd;
	काष्ठा alx_buffer *rxb;
	काष्ठा sk_buff *skb;
	u16 length, rfd_cleaned = 0;
	पूर्णांक work = 0;

	alx = netdev_priv(rxq->netdev);

	जबतक (work < budget) अणु
		rrd = &rxq->rrd[rxq->rrd_पढ़ो_idx];
		अगर (!(rrd->word3 & cpu_to_le32(1 << RRD_UPDATED_SHIFT)))
			अवरोध;
		rrd->word3 &= ~cpu_to_le32(1 << RRD_UPDATED_SHIFT);

		अगर (ALX_GET_FIELD(le32_to_cpu(rrd->word0),
				  RRD_SI) != rxq->पढ़ो_idx ||
		    ALX_GET_FIELD(le32_to_cpu(rrd->word0),
				  RRD_NOR) != 1) अणु
			alx_schedule_reset(alx);
			वापस work;
		पूर्ण

		rxb = &rxq->bufs[rxq->पढ़ो_idx];
		dma_unmap_single(rxq->dev,
				 dma_unmap_addr(rxb, dma),
				 dma_unmap_len(rxb, size),
				 DMA_FROM_DEVICE);
		dma_unmap_len_set(rxb, size, 0);
		skb = rxb->skb;
		rxb->skb = शून्य;

		अगर (rrd->word3 & cpu_to_le32(1 << RRD_ERR_RES_SHIFT) ||
		    rrd->word3 & cpu_to_le32(1 << RRD_ERR_LEN_SHIFT)) अणु
			rrd->word3 = 0;
			dev_kमुक्त_skb_any(skb);
			जाओ next_pkt;
		पूर्ण

		length = ALX_GET_FIELD(le32_to_cpu(rrd->word3),
				       RRD_PKTLEN) - ETH_FCS_LEN;
		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, rxq->netdev);

		skb_checksum_none_निश्चित(skb);
		अगर (alx->dev->features & NETIF_F_RXCSUM &&
		    !(rrd->word3 & (cpu_to_le32(1 << RRD_ERR_L4_SHIFT) |
				    cpu_to_le32(1 << RRD_ERR_IPV4_SHIFT)))) अणु
			चयन (ALX_GET_FIELD(le32_to_cpu(rrd->word2),
					      RRD_PID)) अणु
			हाल RRD_PID_IPV6UDP:
			हाल RRD_PID_IPV4UDP:
			हाल RRD_PID_IPV4TCP:
			हाल RRD_PID_IPV6TCP:
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				अवरोध;
			पूर्ण
		पूर्ण

		napi_gro_receive(&rxq->np->napi, skb);
		work++;

next_pkt:
		अगर (++rxq->पढ़ो_idx == rxq->count)
			rxq->पढ़ो_idx = 0;
		अगर (++rxq->rrd_पढ़ो_idx == rxq->count)
			rxq->rrd_पढ़ो_idx = 0;

		अगर (++rfd_cleaned > ALX_RX_ALLOC_THRESH)
			rfd_cleaned -= alx_refill_rx_ring(alx, GFP_ATOMIC);
	पूर्ण

	अगर (rfd_cleaned)
		alx_refill_rx_ring(alx, GFP_ATOMIC);

	वापस work;
पूर्ण

अटल पूर्णांक alx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा alx_napi *np = container_of(napi, काष्ठा alx_napi, napi);
	काष्ठा alx_priv *alx = np->alx;
	काष्ठा alx_hw *hw = &alx->hw;
	अचिन्हित दीर्घ flags;
	bool tx_complete = true;
	पूर्णांक work = 0;

	अगर (np->txq)
		tx_complete = alx_clean_tx_irq(np->txq);
	अगर (np->rxq)
		work = alx_clean_rx_irq(np->rxq, budget);

	अगर (!tx_complete || work == budget)
		वापस budget;

	napi_complete_करोne(&np->napi, work);

	/* enable पूर्णांकerrupt */
	अगर (alx->hw.pdev->msix_enabled) अणु
		alx_mask_msix(hw, np->vec_idx, false);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&alx->irq_lock, flags);
		alx->पूर्णांक_mask |= ALX_ISR_TX_Q0 | ALX_ISR_RX_Q0;
		alx_ग_लिखो_mem32(hw, ALX_IMR, alx->पूर्णांक_mask);
		spin_unlock_irqrestore(&alx->irq_lock, flags);
	पूर्ण

	alx_post_ग_लिखो(hw);

	वापस work;
पूर्ण

अटल bool alx_पूर्णांकr_handle_misc(काष्ठा alx_priv *alx, u32 पूर्णांकr)
अणु
	काष्ठा alx_hw *hw = &alx->hw;

	अगर (पूर्णांकr & ALX_ISR_FATAL) अणु
		netअगर_warn(alx, hw, alx->dev,
			   "fatal interrupt 0x%x, resetting\n", पूर्णांकr);
		alx_schedule_reset(alx);
		वापस true;
	पूर्ण

	अगर (पूर्णांकr & ALX_ISR_ALERT)
		netdev_warn(alx->dev, "alert interrupt: 0x%x\n", पूर्णांकr);

	अगर (पूर्णांकr & ALX_ISR_PHY) अणु
		/* suppress PHY पूर्णांकerrupt, because the source
		 * is from PHY पूर्णांकernal. only the पूर्णांकernal status
		 * is cleared, the पूर्णांकerrupt status could be cleared.
		 */
		alx->पूर्णांक_mask &= ~ALX_ISR_PHY;
		alx_ग_लिखो_mem32(hw, ALX_IMR, alx->पूर्णांक_mask);
		alx_schedule_link_check(alx);
	पूर्ण

	वापस false;
पूर्ण

अटल irqवापस_t alx_पूर्णांकr_handle(काष्ठा alx_priv *alx, u32 पूर्णांकr)
अणु
	काष्ठा alx_hw *hw = &alx->hw;

	spin_lock(&alx->irq_lock);

	/* ACK पूर्णांकerrupt */
	alx_ग_लिखो_mem32(hw, ALX_ISR, पूर्णांकr | ALX_ISR_DIS);
	पूर्णांकr &= alx->पूर्णांक_mask;

	अगर (alx_पूर्णांकr_handle_misc(alx, पूर्णांकr))
		जाओ out;

	अगर (पूर्णांकr & (ALX_ISR_TX_Q0 | ALX_ISR_RX_Q0)) अणु
		napi_schedule(&alx->qnapi[0]->napi);
		/* mask rx/tx पूर्णांकerrupt, enable them when napi complete */
		alx->पूर्णांक_mask &= ~ALX_ISR_ALL_QUEUES;
		alx_ग_लिखो_mem32(hw, ALX_IMR, alx->पूर्णांक_mask);
	पूर्ण

	alx_ग_लिखो_mem32(hw, ALX_ISR, 0);

 out:
	spin_unlock(&alx->irq_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t alx_पूर्णांकr_msix_ring(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा alx_napi *np = data;
	काष्ठा alx_hw *hw = &np->alx->hw;

	/* mask पूर्णांकerrupt to ACK chip */
	alx_mask_msix(hw, np->vec_idx, true);
	/* clear पूर्णांकerrupt status */
	alx_ग_लिखो_mem32(hw, ALX_ISR, np->vec_mask);

	napi_schedule(&np->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t alx_पूर्णांकr_msix_misc(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा alx_priv *alx = data;
	काष्ठा alx_hw *hw = &alx->hw;
	u32 पूर्णांकr;

	/* mask पूर्णांकerrupt to ACK chip */
	alx_mask_msix(hw, 0, true);

	/* पढ़ो पूर्णांकerrupt status */
	पूर्णांकr = alx_पढ़ो_mem32(hw, ALX_ISR);
	पूर्णांकr &= (alx->पूर्णांक_mask & ~ALX_ISR_ALL_QUEUES);

	अगर (alx_पूर्णांकr_handle_misc(alx, पूर्णांकr))
		वापस IRQ_HANDLED;

	/* clear पूर्णांकerrupt status */
	alx_ग_लिखो_mem32(hw, ALX_ISR, पूर्णांकr);

	/* enable पूर्णांकerrupt again */
	alx_mask_msix(hw, 0, false);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t alx_पूर्णांकr_msi(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा alx_priv *alx = data;

	वापस alx_पूर्णांकr_handle(alx, alx_पढ़ो_mem32(&alx->hw, ALX_ISR));
पूर्ण

अटल irqवापस_t alx_पूर्णांकr_legacy(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा alx_priv *alx = data;
	काष्ठा alx_hw *hw = &alx->hw;
	u32 पूर्णांकr;

	पूर्णांकr = alx_पढ़ो_mem32(hw, ALX_ISR);

	अगर (पूर्णांकr & ALX_ISR_DIS || !(पूर्णांकr & alx->पूर्णांक_mask))
		वापस IRQ_NONE;

	वापस alx_पूर्णांकr_handle(alx, पूर्णांकr);
पूर्ण

अटल स्थिर u16 txring_header_reg[] = अणुALX_TPD_PRI0_ADDR_LO,
					ALX_TPD_PRI1_ADDR_LO,
					ALX_TPD_PRI2_ADDR_LO,
					ALX_TPD_PRI3_ADDR_LOपूर्ण;

अटल व्योम alx_init_ring_ptrs(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;
	u32 addr_hi = ((u64)alx->descmem.dma) >> 32;
	काष्ठा alx_napi *np;
	पूर्णांक i;

	क्रम (i = 0; i < alx->num_napi; i++) अणु
		np = alx->qnapi[i];
		अगर (np->txq) अणु
			np->txq->पढ़ो_idx = 0;
			np->txq->ग_लिखो_idx = 0;
			alx_ग_लिखो_mem32(hw,
					txring_header_reg[np->txq->queue_idx],
					np->txq->tpd_dma);
		पूर्ण

		अगर (np->rxq) अणु
			np->rxq->पढ़ो_idx = 0;
			np->rxq->ग_लिखो_idx = 0;
			np->rxq->rrd_पढ़ो_idx = 0;
			alx_ग_लिखो_mem32(hw, ALX_RRD_ADDR_LO, np->rxq->rrd_dma);
			alx_ग_लिखो_mem32(hw, ALX_RFD_ADDR_LO, np->rxq->rfd_dma);
		पूर्ण
	पूर्ण

	alx_ग_लिखो_mem32(hw, ALX_TX_BASE_ADDR_HI, addr_hi);
	alx_ग_लिखो_mem32(hw, ALX_TPD_RING_SZ, alx->tx_ringsz);

	alx_ग_लिखो_mem32(hw, ALX_RX_BASE_ADDR_HI, addr_hi);
	alx_ग_लिखो_mem32(hw, ALX_RRD_RING_SZ, alx->rx_ringsz);
	alx_ग_लिखो_mem32(hw, ALX_RFD_RING_SZ, alx->rx_ringsz);
	alx_ग_लिखो_mem32(hw, ALX_RFD_BUF_SZ, alx->rxbuf_size);

	/* load these poपूर्णांकers पूर्णांकo the chip */
	alx_ग_लिखो_mem32(hw, ALX_SRAM9, ALX_SRAM_LOAD_PTR);
पूर्ण

अटल व्योम alx_मुक्त_txring_buf(काष्ठा alx_tx_queue *txq)
अणु
	पूर्णांक i;

	अगर (!txq->bufs)
		वापस;

	क्रम (i = 0; i < txq->count; i++)
		alx_मुक्त_txbuf(txq, i);

	स_रखो(txq->bufs, 0, txq->count * माप(काष्ठा alx_buffer));
	स_रखो(txq->tpd, 0, txq->count * माप(काष्ठा alx_txd));
	txq->ग_लिखो_idx = 0;
	txq->पढ़ो_idx = 0;

	netdev_tx_reset_queue(alx_get_tx_queue(txq));
पूर्ण

अटल व्योम alx_मुक्त_rxring_buf(काष्ठा alx_rx_queue *rxq)
अणु
	काष्ठा alx_buffer *cur_buf;
	u16 i;

	अगर (!rxq->bufs)
		वापस;

	क्रम (i = 0; i < rxq->count; i++) अणु
		cur_buf = rxq->bufs + i;
		अगर (cur_buf->skb) अणु
			dma_unmap_single(rxq->dev,
					 dma_unmap_addr(cur_buf, dma),
					 dma_unmap_len(cur_buf, size),
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(cur_buf->skb);
			cur_buf->skb = शून्य;
			dma_unmap_len_set(cur_buf, size, 0);
			dma_unmap_addr_set(cur_buf, dma, 0);
		पूर्ण
	पूर्ण

	rxq->ग_लिखो_idx = 0;
	rxq->पढ़ो_idx = 0;
	rxq->rrd_पढ़ो_idx = 0;
पूर्ण

अटल व्योम alx_मुक्त_buffers(काष्ठा alx_priv *alx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < alx->num_txq; i++)
		अगर (alx->qnapi[i] && alx->qnapi[i]->txq)
			alx_मुक्त_txring_buf(alx->qnapi[i]->txq);

	अगर (alx->qnapi[0] && alx->qnapi[0]->rxq)
		alx_मुक्त_rxring_buf(alx->qnapi[0]->rxq);
पूर्ण

अटल पूर्णांक alx_reinit_rings(काष्ठा alx_priv *alx)
अणु
	alx_मुक्त_buffers(alx);

	alx_init_ring_ptrs(alx);

	अगर (!alx_refill_rx_ring(alx, GFP_KERNEL))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम alx_add_mc_addr(काष्ठा alx_hw *hw, स्थिर u8 *addr, u32 *mc_hash)
अणु
	u32 crc32, bit, reg;

	crc32 = ether_crc(ETH_ALEN, addr);
	reg = (crc32 >> 31) & 0x1;
	bit = (crc32 >> 26) & 0x1F;

	mc_hash[reg] |= BIT(bit);
पूर्ण

अटल व्योम __alx_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;
	काष्ठा netdev_hw_addr *ha;
	u32 mc_hash[2] = अणुपूर्ण;

	अगर (!(netdev->flags & IFF_ALLMULTI)) अणु
		netdev_क्रम_each_mc_addr(ha, netdev)
			alx_add_mc_addr(hw, ha->addr, mc_hash);

		alx_ग_लिखो_mem32(hw, ALX_HASH_TBL0, mc_hash[0]);
		alx_ग_लिखो_mem32(hw, ALX_HASH_TBL1, mc_hash[1]);
	पूर्ण

	hw->rx_ctrl &= ~(ALX_MAC_CTRL_MULTIALL_EN | ALX_MAC_CTRL_PROMISC_EN);
	अगर (netdev->flags & IFF_PROMISC)
		hw->rx_ctrl |= ALX_MAC_CTRL_PROMISC_EN;
	अगर (netdev->flags & IFF_ALLMULTI)
		hw->rx_ctrl |= ALX_MAC_CTRL_MULTIALL_EN;

	alx_ग_लिखो_mem32(hw, ALX_MAC_CTRL, hw->rx_ctrl);
पूर्ण

अटल व्योम alx_set_rx_mode(काष्ठा net_device *netdev)
अणु
	__alx_set_rx_mode(netdev);
पूर्ण

अटल पूर्णांक alx_set_mac_address(काष्ठा net_device *netdev, व्योम *data)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;
	काष्ठा sockaddr *addr = data;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (netdev->addr_assign_type & NET_ADDR_RANDOM)
		netdev->addr_assign_type ^= NET_ADDR_RANDOM;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(hw->mac_addr, addr->sa_data, netdev->addr_len);
	alx_set_macaddr(hw, hw->mac_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक alx_alloc_tx_ring(काष्ठा alx_priv *alx, काष्ठा alx_tx_queue *txq,
			     पूर्णांक offset)
अणु
	txq->bufs = kसुस्मृति(txq->count, माप(काष्ठा alx_buffer), GFP_KERNEL);
	अगर (!txq->bufs)
		वापस -ENOMEM;

	txq->tpd = alx->descmem.virt + offset;
	txq->tpd_dma = alx->descmem.dma + offset;
	offset += माप(काष्ठा alx_txd) * txq->count;

	वापस offset;
पूर्ण

अटल पूर्णांक alx_alloc_rx_ring(काष्ठा alx_priv *alx, काष्ठा alx_rx_queue *rxq,
			     पूर्णांक offset)
अणु
	rxq->bufs = kसुस्मृति(rxq->count, माप(काष्ठा alx_buffer), GFP_KERNEL);
	अगर (!rxq->bufs)
		वापस -ENOMEM;

	rxq->rrd = alx->descmem.virt + offset;
	rxq->rrd_dma = alx->descmem.dma + offset;
	offset += माप(काष्ठा alx_rrd) * rxq->count;

	rxq->rfd = alx->descmem.virt + offset;
	rxq->rfd_dma = alx->descmem.dma + offset;
	offset += माप(काष्ठा alx_rfd) * rxq->count;

	वापस offset;
पूर्ण

अटल पूर्णांक alx_alloc_rings(काष्ठा alx_priv *alx)
अणु
	पूर्णांक i, offset = 0;

	/* physical tx/rx ring descriptors
	 *
	 * Allocate them as a single chunk because they must not cross a
	 * 4G boundary (hardware has a single रेजिस्टर क्रम high 32 bits
	 * of addresses only)
	 */
	alx->descmem.size = माप(काष्ठा alx_txd) * alx->tx_ringsz *
			    alx->num_txq +
			    माप(काष्ठा alx_rrd) * alx->rx_ringsz +
			    माप(काष्ठा alx_rfd) * alx->rx_ringsz;
	alx->descmem.virt = dma_alloc_coherent(&alx->hw.pdev->dev,
					       alx->descmem.size,
					       &alx->descmem.dma, GFP_KERNEL);
	अगर (!alx->descmem.virt)
		वापस -ENOMEM;

	/* alignment requirements */
	BUILD_BUG_ON(माप(काष्ठा alx_txd) % 8);
	BUILD_BUG_ON(माप(काष्ठा alx_rrd) % 8);

	क्रम (i = 0; i < alx->num_txq; i++) अणु
		offset = alx_alloc_tx_ring(alx, alx->qnapi[i]->txq, offset);
		अगर (offset < 0) अणु
			netdev_err(alx->dev, "Allocation of tx buffer failed!\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	offset = alx_alloc_rx_ring(alx, alx->qnapi[0]->rxq, offset);
	अगर (offset < 0) अणु
		netdev_err(alx->dev, "Allocation of rx buffer failed!\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम alx_मुक्त_rings(काष्ठा alx_priv *alx)
अणु
	पूर्णांक i;

	alx_मुक्त_buffers(alx);

	क्रम (i = 0; i < alx->num_txq; i++)
		अगर (alx->qnapi[i] && alx->qnapi[i]->txq)
			kमुक्त(alx->qnapi[i]->txq->bufs);

	अगर (alx->qnapi[0] && alx->qnapi[0]->rxq)
		kमुक्त(alx->qnapi[0]->rxq->bufs);

	अगर (alx->descmem.virt)
		dma_मुक्त_coherent(&alx->hw.pdev->dev,
				  alx->descmem.size,
				  alx->descmem.virt,
				  alx->descmem.dma);
पूर्ण

अटल व्योम alx_मुक्त_napis(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_napi *np;
	पूर्णांक i;

	क्रम (i = 0; i < alx->num_napi; i++) अणु
		np = alx->qnapi[i];
		अगर (!np)
			जारी;

		netअगर_napi_del(&np->napi);
		kमुक्त(np->txq);
		kमुक्त(np->rxq);
		kमुक्त(np);
		alx->qnapi[i] = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर u16 tx_pidx_reg[] = अणुALX_TPD_PRI0_PIDX, ALX_TPD_PRI1_PIDX,
				  ALX_TPD_PRI2_PIDX, ALX_TPD_PRI3_PIDXपूर्ण;
अटल स्थिर u16 tx_cidx_reg[] = अणुALX_TPD_PRI0_CIDX, ALX_TPD_PRI1_CIDX,
				  ALX_TPD_PRI2_CIDX, ALX_TPD_PRI3_CIDXपूर्ण;
अटल स्थिर u32 tx_vect_mask[] = अणुALX_ISR_TX_Q0, ALX_ISR_TX_Q1,
				   ALX_ISR_TX_Q2, ALX_ISR_TX_Q3पूर्ण;
अटल स्थिर u32 rx_vect_mask[] = अणुALX_ISR_RX_Q0, ALX_ISR_RX_Q1,
				   ALX_ISR_RX_Q2, ALX_ISR_RX_Q3,
				   ALX_ISR_RX_Q4, ALX_ISR_RX_Q5,
				   ALX_ISR_RX_Q6, ALX_ISR_RX_Q7पूर्ण;

अटल पूर्णांक alx_alloc_napis(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_napi *np;
	काष्ठा alx_rx_queue *rxq;
	काष्ठा alx_tx_queue *txq;
	पूर्णांक i;

	alx->पूर्णांक_mask &= ~ALX_ISR_ALL_QUEUES;

	/* allocate alx_napi काष्ठाures */
	क्रम (i = 0; i < alx->num_napi; i++) अणु
		np = kzalloc(माप(काष्ठा alx_napi), GFP_KERNEL);
		अगर (!np)
			जाओ err_out;

		np->alx = alx;
		netअगर_napi_add(alx->dev, &np->napi, alx_poll, 64);
		alx->qnapi[i] = np;
	पूर्ण

	/* allocate tx queues */
	क्रम (i = 0; i < alx->num_txq; i++) अणु
		np = alx->qnapi[i];
		txq = kzalloc(माप(*txq), GFP_KERNEL);
		अगर (!txq)
			जाओ err_out;

		np->txq = txq;
		txq->p_reg = tx_pidx_reg[i];
		txq->c_reg = tx_cidx_reg[i];
		txq->queue_idx = i;
		txq->count = alx->tx_ringsz;
		txq->netdev = alx->dev;
		txq->dev = &alx->hw.pdev->dev;
		np->vec_mask |= tx_vect_mask[i];
		alx->पूर्णांक_mask |= tx_vect_mask[i];
	पूर्ण

	/* allocate rx queues */
	np = alx->qnapi[0];
	rxq = kzalloc(माप(*rxq), GFP_KERNEL);
	अगर (!rxq)
		जाओ err_out;

	np->rxq = rxq;
	rxq->np = alx->qnapi[0];
	rxq->queue_idx = 0;
	rxq->count = alx->rx_ringsz;
	rxq->netdev = alx->dev;
	rxq->dev = &alx->hw.pdev->dev;
	np->vec_mask |= rx_vect_mask[0];
	alx->पूर्णांक_mask |= rx_vect_mask[0];

	वापस 0;

err_out:
	netdev_err(alx->dev, "error allocating internal structures\n");
	alx_मुक्त_napis(alx);
	वापस -ENOMEM;
पूर्ण

अटल स्थिर पूर्णांक txq_vec_mapping_shअगरt[] = अणु
	0, ALX_MSI_MAP_TBL1_TXQ0_SHIFT,
	0, ALX_MSI_MAP_TBL1_TXQ1_SHIFT,
	1, ALX_MSI_MAP_TBL2_TXQ2_SHIFT,
	1, ALX_MSI_MAP_TBL2_TXQ3_SHIFT,
पूर्ण;

अटल व्योम alx_config_vector_mapping(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;
	u32 tbl[2] = अणु0, 0पूर्ण;
	पूर्णांक i, vector, idx, shअगरt;

	अगर (alx->hw.pdev->msix_enabled) अणु
		/* tx mappings */
		क्रम (i = 0, vector = 1; i < alx->num_txq; i++, vector++) अणु
			idx = txq_vec_mapping_shअगरt[i * 2];
			shअगरt = txq_vec_mapping_shअगरt[i * 2 + 1];
			tbl[idx] |= vector << shअगरt;
		पूर्ण

		/* rx mapping */
		tbl[0] |= 1 << ALX_MSI_MAP_TBL1_RXQ0_SHIFT;
	पूर्ण

	alx_ग_लिखो_mem32(hw, ALX_MSI_MAP_TBL1, tbl[0]);
	alx_ग_लिखो_mem32(hw, ALX_MSI_MAP_TBL2, tbl[1]);
	alx_ग_लिखो_mem32(hw, ALX_MSI_ID_MAP, 0);
पूर्ण

अटल पूर्णांक alx_enable_msix(काष्ठा alx_priv *alx)
अणु
	पूर्णांक err, num_vec, num_txq, num_rxq;

	num_txq = min_t(पूर्णांक, num_online_cpus(), ALX_MAX_TX_QUEUES);
	num_rxq = 1;
	num_vec = max_t(पूर्णांक, num_txq, num_rxq) + 1;

	err = pci_alloc_irq_vectors(alx->hw.pdev, num_vec, num_vec,
			PCI_IRQ_MSIX);
	अगर (err < 0) अणु
		netdev_warn(alx->dev, "Enabling MSI-X interrupts failed!\n");
		वापस err;
	पूर्ण

	alx->num_vec = num_vec;
	alx->num_napi = num_vec - 1;
	alx->num_txq = num_txq;
	alx->num_rxq = num_rxq;

	वापस err;
पूर्ण

अटल पूर्णांक alx_request_msix(काष्ठा alx_priv *alx)
अणु
	काष्ठा net_device *netdev = alx->dev;
	पूर्णांक i, err, vector = 0, मुक्त_vector = 0;

	err = request_irq(pci_irq_vector(alx->hw.pdev, 0), alx_पूर्णांकr_msix_misc,
			  0, netdev->name, alx);
	अगर (err)
		जाओ out_err;

	क्रम (i = 0; i < alx->num_napi; i++) अणु
		काष्ठा alx_napi *np = alx->qnapi[i];

		vector++;

		अगर (np->txq && np->rxq)
			प्र_लिखो(np->irq_lbl, "%s-TxRx-%u", netdev->name,
				np->txq->queue_idx);
		अन्यथा अगर (np->txq)
			प्र_लिखो(np->irq_lbl, "%s-tx-%u", netdev->name,
				np->txq->queue_idx);
		अन्यथा अगर (np->rxq)
			प्र_लिखो(np->irq_lbl, "%s-rx-%u", netdev->name,
				np->rxq->queue_idx);
		अन्यथा
			प्र_लिखो(np->irq_lbl, "%s-unused", netdev->name);

		np->vec_idx = vector;
		err = request_irq(pci_irq_vector(alx->hw.pdev, vector),
				  alx_पूर्णांकr_msix_ring, 0, np->irq_lbl, np);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण
	वापस 0;

out_मुक्त:
	मुक्त_irq(pci_irq_vector(alx->hw.pdev, मुक्त_vector++), alx);

	vector--;
	क्रम (i = 0; i < vector; i++)
		मुक्त_irq(pci_irq_vector(alx->hw.pdev,मुक्त_vector++),
			 alx->qnapi[i]);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक alx_init_पूर्णांकr(काष्ठा alx_priv *alx)
अणु
	पूर्णांक ret;

	ret = pci_alloc_irq_vectors(alx->hw.pdev, 1, 1,
			PCI_IRQ_MSI | PCI_IRQ_LEGACY);
	अगर (ret < 0)
		वापस ret;

	alx->num_vec = 1;
	alx->num_napi = 1;
	alx->num_txq = 1;
	alx->num_rxq = 1;
	वापस 0;
पूर्ण

अटल व्योम alx_irq_enable(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;
	पूर्णांक i;

	/* level-1 पूर्णांकerrupt चयन */
	alx_ग_लिखो_mem32(hw, ALX_ISR, 0);
	alx_ग_लिखो_mem32(hw, ALX_IMR, alx->पूर्णांक_mask);
	alx_post_ग_लिखो(hw);

	अगर (alx->hw.pdev->msix_enabled) अणु
		/* enable all msix irqs */
		क्रम (i = 0; i < alx->num_vec; i++)
			alx_mask_msix(hw, i, false);
	पूर्ण
पूर्ण

अटल व्योम alx_irq_disable(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;
	पूर्णांक i;

	alx_ग_लिखो_mem32(hw, ALX_ISR, ALX_ISR_DIS);
	alx_ग_लिखो_mem32(hw, ALX_IMR, 0);
	alx_post_ग_लिखो(hw);

	अगर (alx->hw.pdev->msix_enabled) अणु
		क्रम (i = 0; i < alx->num_vec; i++) अणु
			alx_mask_msix(hw, i, true);
			synchronize_irq(pci_irq_vector(alx->hw.pdev, i));
		पूर्ण
	पूर्ण अन्यथा अणु
		synchronize_irq(pci_irq_vector(alx->hw.pdev, 0));
	पूर्ण
पूर्ण

अटल पूर्णांक alx_पुनः_स्मृति_resources(काष्ठा alx_priv *alx)
अणु
	पूर्णांक err;

	alx_मुक्त_rings(alx);
	alx_मुक्त_napis(alx);
	pci_मुक्त_irq_vectors(alx->hw.pdev);

	err = alx_init_पूर्णांकr(alx);
	अगर (err)
		वापस err;

	err = alx_alloc_napis(alx);
	अगर (err)
		वापस err;

	err = alx_alloc_rings(alx);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक alx_request_irq(काष्ठा alx_priv *alx)
अणु
	काष्ठा pci_dev *pdev = alx->hw.pdev;
	काष्ठा alx_hw *hw = &alx->hw;
	पूर्णांक err;
	u32 msi_ctrl;

	msi_ctrl = (hw->imt >> 1) << ALX_MSI_RETRANS_TM_SHIFT;

	अगर (alx->hw.pdev->msix_enabled) अणु
		alx_ग_लिखो_mem32(hw, ALX_MSI_RETRANS_TIMER, msi_ctrl);
		err = alx_request_msix(alx);
		अगर (!err)
			जाओ out;

		/* msix request failed, पुनः_स्मृति resources */
		err = alx_पुनः_स्मृति_resources(alx);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (alx->hw.pdev->msi_enabled) अणु
		alx_ग_लिखो_mem32(hw, ALX_MSI_RETRANS_TIMER,
				msi_ctrl | ALX_MSI_MASK_SEL_LINE);
		err = request_irq(pci_irq_vector(pdev, 0), alx_पूर्णांकr_msi, 0,
				  alx->dev->name, alx);
		अगर (!err)
			जाओ out;

		/* fall back to legacy पूर्णांकerrupt */
		pci_मुक्त_irq_vectors(alx->hw.pdev);
	पूर्ण

	alx_ग_लिखो_mem32(hw, ALX_MSI_RETRANS_TIMER, 0);
	err = request_irq(pci_irq_vector(pdev, 0), alx_पूर्णांकr_legacy, IRQF_SHARED,
			  alx->dev->name, alx);
out:
	अगर (!err)
		alx_config_vector_mapping(alx);
	अन्यथा
		netdev_err(alx->dev, "IRQ registration failed!\n");
	वापस err;
पूर्ण

अटल व्योम alx_मुक्त_irq(काष्ठा alx_priv *alx)
अणु
	काष्ठा pci_dev *pdev = alx->hw.pdev;
	पूर्णांक i;

	मुक्त_irq(pci_irq_vector(pdev, 0), alx);
	अगर (alx->hw.pdev->msix_enabled) अणु
		क्रम (i = 0; i < alx->num_napi; i++)
			मुक्त_irq(pci_irq_vector(pdev, i + 1), alx->qnapi[i]);
	पूर्ण

	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल पूर्णांक alx_identअगरy_hw(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;
	पूर्णांक rev = alx_hw_revision(hw);

	अगर (rev > ALX_REV_C0)
		वापस -EINVAL;

	hw->max_dma_chnl = rev >= ALX_REV_B0 ? 4 : 2;

	वापस 0;
पूर्ण

अटल पूर्णांक alx_init_sw(काष्ठा alx_priv *alx)
अणु
	काष्ठा pci_dev *pdev = alx->hw.pdev;
	काष्ठा alx_hw *hw = &alx->hw;
	पूर्णांक err;

	err = alx_identअगरy_hw(alx);
	अगर (err) अणु
		dev_err(&pdev->dev, "unrecognized chip, aborting\n");
		वापस err;
	पूर्ण

	alx->hw.lnk_patch =
		pdev->device == ALX_DEV_ID_AR8161 &&
		pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_ATTANSIC &&
		pdev->subप्रणाली_device == 0x0091 &&
		pdev->revision == 0;

	hw->smb_समयr = 400;
	hw->mtu = alx->dev->mtu;
	alx->rxbuf_size = ALX_MAX_FRAME_LEN(hw->mtu);
	/* MTU range: 34 - 9256 */
	alx->dev->min_mtu = 34;
	alx->dev->max_mtu = ALX_MAX_FRAME_LEN(ALX_MAX_FRAME_SIZE);
	alx->tx_ringsz = 256;
	alx->rx_ringsz = 512;
	hw->imt = 200;
	alx->पूर्णांक_mask = ALX_ISR_MISC;
	hw->dma_chnl = hw->max_dma_chnl;
	hw->ith_tpd = alx->tx_ringsz / 3;
	hw->link_speed = SPEED_UNKNOWN;
	hw->duplex = DUPLEX_UNKNOWN;
	hw->adv_cfg = ADVERTISED_Autoneg |
		      ADVERTISED_10baseT_Half |
		      ADVERTISED_10baseT_Full |
		      ADVERTISED_100baseT_Full |
		      ADVERTISED_100baseT_Half |
		      ADVERTISED_1000baseT_Full;
	hw->flowctrl = ALX_FC_ANEG | ALX_FC_RX | ALX_FC_TX;

	hw->rx_ctrl = ALX_MAC_CTRL_WOLSPED_SWEN |
		      ALX_MAC_CTRL_MHASH_ALG_HI5B |
		      ALX_MAC_CTRL_BRD_EN |
		      ALX_MAC_CTRL_PCRCE |
		      ALX_MAC_CTRL_CRCE |
		      ALX_MAC_CTRL_RXFC_EN |
		      ALX_MAC_CTRL_TXFC_EN |
		      7 << ALX_MAC_CTRL_PRMBLEN_SHIFT;

	वापस err;
पूर्ण


अटल netdev_features_t alx_fix_features(काष्ठा net_device *netdev,
					  netdev_features_t features)
अणु
	अगर (netdev->mtu > ALX_MAX_TSO_PKT_SIZE)
		features &= ~(NETIF_F_TSO | NETIF_F_TSO6);

	वापस features;
पूर्ण

अटल व्योम alx_netअगर_stop(काष्ठा alx_priv *alx)
अणु
	पूर्णांक i;

	netअगर_trans_update(alx->dev);
	अगर (netअगर_carrier_ok(alx->dev)) अणु
		netअगर_carrier_off(alx->dev);
		netअगर_tx_disable(alx->dev);
		क्रम (i = 0; i < alx->num_napi; i++)
			napi_disable(&alx->qnapi[i]->napi);
	पूर्ण
पूर्ण

अटल व्योम alx_halt(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;

	alx_netअगर_stop(alx);
	hw->link_speed = SPEED_UNKNOWN;
	hw->duplex = DUPLEX_UNKNOWN;

	alx_reset_mac(hw);

	/* disable l0s/l1 */
	alx_enable_aspm(hw, false, false);
	alx_irq_disable(alx);
	alx_मुक्त_buffers(alx);
पूर्ण

अटल व्योम alx_configure(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;

	alx_configure_basic(hw);
	alx_disable_rss(hw);
	__alx_set_rx_mode(alx->dev);

	alx_ग_लिखो_mem32(hw, ALX_MAC_CTRL, hw->rx_ctrl);
पूर्ण

अटल व्योम alx_activate(काष्ठा alx_priv *alx)
अणु
	/* hardware setting lost, restore it */
	alx_reinit_rings(alx);
	alx_configure(alx);

	/* clear old पूर्णांकerrupts */
	alx_ग_लिखो_mem32(&alx->hw, ALX_ISR, ~(u32)ALX_ISR_DIS);

	alx_irq_enable(alx);

	alx_schedule_link_check(alx);
पूर्ण

अटल व्योम alx_reinit(काष्ठा alx_priv *alx)
अणु
	ASSERT_RTNL();

	alx_halt(alx);
	alx_activate(alx);
पूर्ण

अटल पूर्णांक alx_change_mtu(काष्ठा net_device *netdev, पूर्णांक mtu)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	पूर्णांक max_frame = ALX_MAX_FRAME_LEN(mtu);

	netdev->mtu = mtu;
	alx->hw.mtu = mtu;
	alx->rxbuf_size = max(max_frame, ALX_DEF_RXBUF_SIZE);
	netdev_update_features(netdev);
	अगर (netअगर_running(netdev))
		alx_reinit(alx);
	वापस 0;
पूर्ण

अटल व्योम alx_netअगर_start(काष्ठा alx_priv *alx)
अणु
	पूर्णांक i;

	netअगर_tx_wake_all_queues(alx->dev);
	क्रम (i = 0; i < alx->num_napi; i++)
		napi_enable(&alx->qnapi[i]->napi);
	netअगर_carrier_on(alx->dev);
पूर्ण

अटल पूर्णांक __alx_खोलो(काष्ठा alx_priv *alx, bool resume)
अणु
	पूर्णांक err;

	err = alx_enable_msix(alx);
	अगर (err < 0) अणु
		err = alx_init_पूर्णांकr(alx);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!resume)
		netअगर_carrier_off(alx->dev);

	err = alx_alloc_napis(alx);
	अगर (err)
		जाओ out_disable_adv_पूर्णांकr;

	err = alx_alloc_rings(alx);
	अगर (err)
		जाओ out_मुक्त_rings;

	alx_configure(alx);

	err = alx_request_irq(alx);
	अगर (err)
		जाओ out_मुक्त_rings;

	/* must be called after alx_request_irq because the chip stops working
	 * अगर we copy the dma addresses in alx_init_ring_ptrs twice when
	 * requesting msi-x पूर्णांकerrupts failed
	 */
	alx_reinit_rings(alx);

	netअगर_set_real_num_tx_queues(alx->dev, alx->num_txq);
	netअगर_set_real_num_rx_queues(alx->dev, alx->num_rxq);

	/* clear old पूर्णांकerrupts */
	alx_ग_लिखो_mem32(&alx->hw, ALX_ISR, ~(u32)ALX_ISR_DIS);

	alx_irq_enable(alx);

	अगर (!resume)
		netअगर_tx_start_all_queues(alx->dev);

	alx_schedule_link_check(alx);
	वापस 0;

out_मुक्त_rings:
	alx_मुक्त_rings(alx);
	alx_मुक्त_napis(alx);
out_disable_adv_पूर्णांकr:
	pci_मुक्त_irq_vectors(alx->hw.pdev);
	वापस err;
पूर्ण

अटल व्योम __alx_stop(काष्ठा alx_priv *alx)
अणु
	alx_मुक्त_irq(alx);

	cancel_work_sync(&alx->link_check_wk);
	cancel_work_sync(&alx->reset_wk);

	alx_halt(alx);
	alx_मुक्त_rings(alx);
	alx_मुक्त_napis(alx);
पूर्ण

अटल स्थिर अक्षर *alx_speed_desc(काष्ठा alx_hw *hw)
अणु
	चयन (alx_speed_to_ethadv(hw->link_speed, hw->duplex)) अणु
	हाल ADVERTISED_1000baseT_Full:
		वापस "1 Gbps Full";
	हाल ADVERTISED_100baseT_Full:
		वापस "100 Mbps Full";
	हाल ADVERTISED_100baseT_Half:
		वापस "100 Mbps Half";
	हाल ADVERTISED_10baseT_Full:
		वापस "10 Mbps Full";
	हाल ADVERTISED_10baseT_Half:
		वापस "10 Mbps Half";
	शेष:
		वापस "Unknown speed";
	पूर्ण
पूर्ण

अटल व्योम alx_check_link(काष्ठा alx_priv *alx)
अणु
	काष्ठा alx_hw *hw = &alx->hw;
	अचिन्हित दीर्घ flags;
	पूर्णांक old_speed;
	पूर्णांक err;

	/* clear PHY पूर्णांकernal पूर्णांकerrupt status, otherwise the मुख्य
	 * पूर्णांकerrupt status will be निश्चितed क्रमever
	 */
	alx_clear_phy_पूर्णांकr(hw);

	old_speed = hw->link_speed;
	err = alx_पढ़ो_phy_link(hw);
	अगर (err < 0)
		जाओ reset;

	spin_lock_irqsave(&alx->irq_lock, flags);
	alx->पूर्णांक_mask |= ALX_ISR_PHY;
	alx_ग_लिखो_mem32(hw, ALX_IMR, alx->पूर्णांक_mask);
	spin_unlock_irqrestore(&alx->irq_lock, flags);

	अगर (old_speed == hw->link_speed)
		वापस;

	अगर (hw->link_speed != SPEED_UNKNOWN) अणु
		netअगर_info(alx, link, alx->dev,
			   "NIC Up: %s\n", alx_speed_desc(hw));
		alx_post_phy_link(hw);
		alx_enable_aspm(hw, true, true);
		alx_start_mac(hw);

		अगर (old_speed == SPEED_UNKNOWN)
			alx_netअगर_start(alx);
	पूर्ण अन्यथा अणु
		/* link is now करोwn */
		alx_netअगर_stop(alx);
		netअगर_info(alx, link, alx->dev, "Link Down\n");
		err = alx_reset_mac(hw);
		अगर (err)
			जाओ reset;
		alx_irq_disable(alx);

		/* MAC reset causes all HW settings to be lost, restore all */
		err = alx_reinit_rings(alx);
		अगर (err)
			जाओ reset;
		alx_configure(alx);
		alx_enable_aspm(hw, false, true);
		alx_post_phy_link(hw);
		alx_irq_enable(alx);
	पूर्ण

	वापस;

reset:
	alx_schedule_reset(alx);
पूर्ण

अटल पूर्णांक alx_खोलो(काष्ठा net_device *netdev)
अणु
	वापस __alx_खोलो(netdev_priv(netdev), false);
पूर्ण

अटल पूर्णांक alx_stop(काष्ठा net_device *netdev)
अणु
	__alx_stop(netdev_priv(netdev));
	वापस 0;
पूर्ण

अटल व्योम alx_link_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा alx_priv *alx;

	alx = container_of(work, काष्ठा alx_priv, link_check_wk);

	rtnl_lock();
	alx_check_link(alx);
	rtnl_unlock();
पूर्ण

अटल व्योम alx_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा alx_priv *alx = container_of(work, काष्ठा alx_priv, reset_wk);

	rtnl_lock();
	alx_reinit(alx);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक alx_tpd_req(काष्ठा sk_buff *skb)
अणु
	पूर्णांक num;

	num = skb_shinfo(skb)->nr_frags + 1;
	/* we need one extra descriptor क्रम LSOv2 */
	अगर (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6)
		num++;

	वापस num;
पूर्ण

अटल पूर्णांक alx_tx_csum(काष्ठा sk_buff *skb, काष्ठा alx_txd *first)
अणु
	u8 cso, css;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	cso = skb_checksum_start_offset(skb);
	अगर (cso & 1)
		वापस -EINVAL;

	css = cso + skb->csum_offset;
	first->word1 |= cpu_to_le32((cso >> 1) << TPD_CXSUMSTART_SHIFT);
	first->word1 |= cpu_to_le32((css >> 1) << TPD_CXSUMOFFSET_SHIFT);
	first->word1 |= cpu_to_le32(1 << TPD_CXSUM_EN_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक alx_tso(काष्ठा sk_buff *skb, काष्ठा alx_txd *first)
अणु
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = ip_hdr(skb);

		iph->check = 0;
		tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr, iph->daddr,
							 0, IPPROTO_TCP, 0);
		first->word1 |= 1 << TPD_IPV4_SHIFT;
	पूर्ण अन्यथा अगर (skb_is_gso_v6(skb)) अणु
		tcp_v6_gso_csum_prep(skb);
		/* LSOv2: the first TPD only provides the packet length */
		first->adrl.l.pkt_len = skb->len;
		first->word1 |= 1 << TPD_LSO_V2_SHIFT;
	पूर्ण

	first->word1 |= 1 << TPD_LSO_EN_SHIFT;
	first->word1 |= (skb_transport_offset(skb) &
			 TPD_L4HDROFFSET_MASK) << TPD_L4HDROFFSET_SHIFT;
	first->word1 |= (skb_shinfo(skb)->gso_size &
			 TPD_MSS_MASK) << TPD_MSS_SHIFT;
	वापस 1;
पूर्ण

अटल पूर्णांक alx_map_tx_skb(काष्ठा alx_tx_queue *txq, काष्ठा sk_buff *skb)
अणु
	काष्ठा alx_txd *tpd, *first_tpd;
	dma_addr_t dma;
	पूर्णांक maplen, f, first_idx = txq->ग_लिखो_idx;

	first_tpd = &txq->tpd[txq->ग_लिखो_idx];
	tpd = first_tpd;

	अगर (tpd->word1 & (1 << TPD_LSO_V2_SHIFT)) अणु
		अगर (++txq->ग_लिखो_idx == txq->count)
			txq->ग_लिखो_idx = 0;

		tpd = &txq->tpd[txq->ग_लिखो_idx];
		tpd->len = first_tpd->len;
		tpd->vlan_tag = first_tpd->vlan_tag;
		tpd->word1 = first_tpd->word1;
	पूर्ण

	maplen = skb_headlen(skb);
	dma = dma_map_single(txq->dev, skb->data, maplen,
			     DMA_TO_DEVICE);
	अगर (dma_mapping_error(txq->dev, dma))
		जाओ err_dma;

	dma_unmap_len_set(&txq->bufs[txq->ग_लिखो_idx], size, maplen);
	dma_unmap_addr_set(&txq->bufs[txq->ग_लिखो_idx], dma, dma);

	tpd->adrl.addr = cpu_to_le64(dma);
	tpd->len = cpu_to_le16(maplen);

	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		अगर (++txq->ग_लिखो_idx == txq->count)
			txq->ग_लिखो_idx = 0;
		tpd = &txq->tpd[txq->ग_लिखो_idx];

		tpd->word1 = first_tpd->word1;

		maplen = skb_frag_size(frag);
		dma = skb_frag_dma_map(txq->dev, frag, 0,
				       maplen, DMA_TO_DEVICE);
		अगर (dma_mapping_error(txq->dev, dma))
			जाओ err_dma;
		dma_unmap_len_set(&txq->bufs[txq->ग_लिखो_idx], size, maplen);
		dma_unmap_addr_set(&txq->bufs[txq->ग_लिखो_idx], dma, dma);

		tpd->adrl.addr = cpu_to_le64(dma);
		tpd->len = cpu_to_le16(maplen);
	पूर्ण

	/* last TPD, set EOP flag and store skb */
	tpd->word1 |= cpu_to_le32(1 << TPD_EOP_SHIFT);
	txq->bufs[txq->ग_लिखो_idx].skb = skb;

	अगर (++txq->ग_लिखो_idx == txq->count)
		txq->ग_लिखो_idx = 0;

	वापस 0;

err_dma:
	f = first_idx;
	जबतक (f != txq->ग_लिखो_idx) अणु
		alx_मुक्त_txbuf(txq, f);
		अगर (++f == txq->count)
			f = 0;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल netdev_tx_t alx_start_xmit_ring(काष्ठा sk_buff *skb,
				       काष्ठा alx_tx_queue *txq)
अणु
	काष्ठा alx_priv *alx;
	काष्ठा alx_txd *first;
	पूर्णांक tso;

	alx = netdev_priv(txq->netdev);

	अगर (alx_tpd_avail(txq) < alx_tpd_req(skb)) अणु
		netअगर_tx_stop_queue(alx_get_tx_queue(txq));
		जाओ drop;
	पूर्ण

	first = &txq->tpd[txq->ग_लिखो_idx];
	स_रखो(first, 0, माप(*first));

	tso = alx_tso(skb, first);
	अगर (tso < 0)
		जाओ drop;
	अन्यथा अगर (!tso && alx_tx_csum(skb, first))
		जाओ drop;

	अगर (alx_map_tx_skb(txq, skb) < 0)
		जाओ drop;

	netdev_tx_sent_queue(alx_get_tx_queue(txq), skb->len);

	/* flush updates beक्रमe updating hardware */
	wmb();
	alx_ग_लिखो_mem16(&alx->hw, txq->p_reg, txq->ग_लिखो_idx);

	अगर (alx_tpd_avail(txq) < txq->count / 8)
		netअगर_tx_stop_queue(alx_get_tx_queue(txq));

	वापस NETDEV_TX_OK;

drop:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t alx_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *netdev)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	वापस alx_start_xmit_ring(skb, alx_tx_queue_mapping(alx, skb));
पूर्ण

अटल व्योम alx_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा alx_priv *alx = netdev_priv(dev);

	alx_schedule_reset(alx);
पूर्ण

अटल पूर्णांक alx_mdio_पढ़ो(काष्ठा net_device *netdev,
			 पूर्णांक prtad, पूर्णांक devad, u16 addr)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;
	u16 val;
	पूर्णांक err;

	अगर (prtad != hw->mdio.prtad)
		वापस -EINVAL;

	अगर (devad == MDIO_DEVAD_NONE)
		err = alx_पढ़ो_phy_reg(hw, addr, &val);
	अन्यथा
		err = alx_पढ़ो_phy_ext(hw, devad, addr, &val);

	अगर (err)
		वापस err;
	वापस val;
पूर्ण

अटल पूर्णांक alx_mdio_ग_लिखो(काष्ठा net_device *netdev,
			  पूर्णांक prtad, पूर्णांक devad, u16 addr, u16 val)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	काष्ठा alx_hw *hw = &alx->hw;

	अगर (prtad != hw->mdio.prtad)
		वापस -EINVAL;

	अगर (devad == MDIO_DEVAD_NONE)
		वापस alx_ग_लिखो_phy_reg(hw, addr, val);

	वापस alx_ग_लिखो_phy_ext(hw, devad, addr, val);
पूर्ण

अटल पूर्णांक alx_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);

	अगर (!netअगर_running(netdev))
		वापस -EAGAIN;

	वापस mdio_mii_ioctl(&alx->hw.mdio, अगर_mii(अगरr), cmd);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम alx_poll_controller(काष्ठा net_device *netdev)
अणु
	काष्ठा alx_priv *alx = netdev_priv(netdev);
	पूर्णांक i;

	अगर (alx->hw.pdev->msix_enabled) अणु
		alx_पूर्णांकr_msix_misc(0, alx);
		क्रम (i = 0; i < alx->num_txq; i++)
			alx_पूर्णांकr_msix_ring(0, alx->qnapi[i]);
	पूर्ण अन्यथा अगर (alx->hw.pdev->msi_enabled)
		alx_पूर्णांकr_msi(0, alx);
	अन्यथा
		alx_पूर्णांकr_legacy(0, alx);
पूर्ण
#पूर्ण_अगर

अटल व्योम alx_get_stats64(काष्ठा net_device *dev,
			    काष्ठा rtnl_link_stats64 *net_stats)
अणु
	काष्ठा alx_priv *alx = netdev_priv(dev);
	काष्ठा alx_hw_stats *hw_stats = &alx->hw.stats;

	spin_lock(&alx->stats_lock);

	alx_update_hw_stats(&alx->hw);

	net_stats->tx_bytes   = hw_stats->tx_byte_cnt;
	net_stats->rx_bytes   = hw_stats->rx_byte_cnt;
	net_stats->multicast  = hw_stats->rx_mcast;
	net_stats->collisions = hw_stats->tx_single_col +
				hw_stats->tx_multi_col +
				hw_stats->tx_late_col +
				hw_stats->tx_पात_col;

	net_stats->rx_errors  = hw_stats->rx_frag +
				hw_stats->rx_fcs_err +
				hw_stats->rx_len_err +
				hw_stats->rx_ov_sz +
				hw_stats->rx_ov_rrd +
				hw_stats->rx_align_err +
				hw_stats->rx_ov_rxf;

	net_stats->rx_fअगरo_errors   = hw_stats->rx_ov_rxf;
	net_stats->rx_length_errors = hw_stats->rx_len_err;
	net_stats->rx_crc_errors    = hw_stats->rx_fcs_err;
	net_stats->rx_frame_errors  = hw_stats->rx_align_err;
	net_stats->rx_dropped       = hw_stats->rx_ov_rrd;

	net_stats->tx_errors = hw_stats->tx_late_col +
			       hw_stats->tx_पात_col +
			       hw_stats->tx_underrun +
			       hw_stats->tx_trunc;

	net_stats->tx_पातed_errors = hw_stats->tx_पात_col;
	net_stats->tx_fअगरo_errors    = hw_stats->tx_underrun;
	net_stats->tx_winकरोw_errors  = hw_stats->tx_late_col;

	net_stats->tx_packets = hw_stats->tx_ok + net_stats->tx_errors;
	net_stats->rx_packets = hw_stats->rx_ok + net_stats->rx_errors;

	spin_unlock(&alx->stats_lock);
पूर्ण

अटल स्थिर काष्ठा net_device_ops alx_netdev_ops = अणु
	.nकरो_खोलो               = alx_खोलो,
	.nकरो_stop               = alx_stop,
	.nकरो_start_xmit         = alx_start_xmit,
	.nकरो_get_stats64        = alx_get_stats64,
	.nकरो_set_rx_mode        = alx_set_rx_mode,
	.nकरो_validate_addr      = eth_validate_addr,
	.nकरो_set_mac_address    = alx_set_mac_address,
	.nकरो_change_mtu         = alx_change_mtu,
	.nकरो_करो_ioctl           = alx_ioctl,
	.nकरो_tx_समयout         = alx_tx_समयout,
	.nकरो_fix_features	= alx_fix_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller    = alx_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक alx_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा alx_priv *alx;
	काष्ठा alx_hw *hw;
	bool phy_configured;
	पूर्णांक err;

	err = pci_enable_device_mem(pdev);
	अगर (err)
		वापस err;

	/* The alx chip can DMA to 64-bit addresses, but it uses a single
	 * shared रेजिस्टर क्रम the high 32 bits, so only a single, aligned,
	 * 4 GB physical address range can be used क्रम descriptors.
	 */
	अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		dev_dbg(&pdev->dev, "DMA to 64-BIT addresses\n");
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "No usable DMA config, aborting\n");
			जाओ out_pci_disable;
		पूर्ण
	पूर्ण

	err = pci_request_mem_regions(pdev, alx_drv_name);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"pci_request_mem_regions failed\n");
		जाओ out_pci_disable;
	पूर्ण

	pci_enable_pcie_error_reporting(pdev);
	pci_set_master(pdev);

	अगर (!pdev->pm_cap) अणु
		dev_err(&pdev->dev,
			"Can't find power management capability, aborting\n");
		err = -EIO;
		जाओ out_pci_release;
	पूर्ण

	netdev = alloc_etherdev_mqs(माप(*alx),
				    ALX_MAX_TX_QUEUES, 1);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ out_pci_release;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);
	alx = netdev_priv(netdev);
	spin_lock_init(&alx->hw.mdio_lock);
	spin_lock_init(&alx->irq_lock);
	spin_lock_init(&alx->stats_lock);
	alx->dev = netdev;
	alx->hw.pdev = pdev;
	alx->msg_enable = NETIF_MSG_LINK | NETIF_MSG_HW | NETIF_MSG_IFUP |
			  NETIF_MSG_TX_ERR | NETIF_MSG_RX_ERR | NETIF_MSG_WOL;
	hw = &alx->hw;
	pci_set_drvdata(pdev, alx);

	hw->hw_addr = pci_ioremap_bar(pdev, 0);
	अगर (!hw->hw_addr) अणु
		dev_err(&pdev->dev, "cannot map device registers\n");
		err = -EIO;
		जाओ out_मुक्त_netdev;
	पूर्ण

	netdev->netdev_ops = &alx_netdev_ops;
	netdev->ethtool_ops = &alx_ethtool_ops;
	netdev->irq = pci_irq_vector(pdev, 0);
	netdev->watchकरोg_समयo = ALX_WATCHDOG_TIME;

	अगर (ent->driver_data & ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG)
		pdev->dev_flags |= PCI_DEV_FLAGS_MSI_INTX_DISABLE_BUG;

	err = alx_init_sw(alx);
	अगर (err) अणु
		dev_err(&pdev->dev, "net device private data init failed\n");
		जाओ out_unmap;
	पूर्ण

	alx_reset_pcie(hw);

	phy_configured = alx_phy_configured(hw);

	अगर (!phy_configured)
		alx_reset_phy(hw);

	err = alx_reset_mac(hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "MAC Reset failed, error = %d\n", err);
		जाओ out_unmap;
	पूर्ण

	/* setup link to put it in a known good starting state */
	अगर (!phy_configured) अणु
		err = alx_setup_speed_duplex(hw, hw->adv_cfg, hw->flowctrl);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"failed to configure PHY speed/duplex (err=%d)\n",
				err);
			जाओ out_unmap;
		पूर्ण
	पूर्ण

	netdev->hw_features = NETIF_F_SG |
			      NETIF_F_HW_CSUM |
			      NETIF_F_RXCSUM |
			      NETIF_F_TSO |
			      NETIF_F_TSO6;

	अगर (alx_get_perm_macaddr(hw, hw->perm_addr)) अणु
		dev_warn(&pdev->dev,
			 "Invalid permanent address programmed, using random one\n");
		eth_hw_addr_अक्रमom(netdev);
		स_नकल(hw->perm_addr, netdev->dev_addr, netdev->addr_len);
	पूर्ण

	स_नकल(hw->mac_addr, hw->perm_addr, ETH_ALEN);
	स_नकल(netdev->dev_addr, hw->mac_addr, ETH_ALEN);
	स_नकल(netdev->perm_addr, hw->perm_addr, ETH_ALEN);

	hw->mdio.prtad = 0;
	hw->mdio.mmds = 0;
	hw->mdio.dev = netdev;
	hw->mdio.mode_support = MDIO_SUPPORTS_C45 |
				MDIO_SUPPORTS_C22 |
				MDIO_EMULATE_C22;
	hw->mdio.mdio_पढ़ो = alx_mdio_पढ़ो;
	hw->mdio.mdio_ग_लिखो = alx_mdio_ग_लिखो;

	अगर (!alx_get_phy_info(hw)) अणु
		dev_err(&pdev->dev, "failed to identify PHY\n");
		err = -EIO;
		जाओ out_unmap;
	पूर्ण

	INIT_WORK(&alx->link_check_wk, alx_link_check);
	INIT_WORK(&alx->reset_wk, alx_reset);
	netअगर_carrier_off(netdev);

	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "register netdevice failed\n");
		जाओ out_unmap;
	पूर्ण

	netdev_info(netdev,
		    "Qualcomm Atheros AR816x/AR817x Ethernet [%pM]\n",
		    netdev->dev_addr);

	वापस 0;

out_unmap:
	iounmap(hw->hw_addr);
out_मुक्त_netdev:
	मुक्त_netdev(netdev);
out_pci_release:
	pci_release_mem_regions(pdev);
	pci_disable_pcie_error_reporting(pdev);
out_pci_disable:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल व्योम alx_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा alx_priv *alx = pci_get_drvdata(pdev);
	काष्ठा alx_hw *hw = &alx->hw;

	/* restore permanent mac address */
	alx_set_macaddr(hw, hw->perm_addr);

	unरेजिस्टर_netdev(alx->dev);
	iounmap(hw->hw_addr);
	pci_release_mem_regions(pdev);

	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);

	मुक्त_netdev(alx->dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक alx_suspend(काष्ठा device *dev)
अणु
	काष्ठा alx_priv *alx = dev_get_drvdata(dev);

	अगर (!netअगर_running(alx->dev))
		वापस 0;
	netअगर_device_detach(alx->dev);
	__alx_stop(alx);
	वापस 0;
पूर्ण

अटल पूर्णांक alx_resume(काष्ठा device *dev)
अणु
	काष्ठा alx_priv *alx = dev_get_drvdata(dev);
	काष्ठा alx_hw *hw = &alx->hw;
	पूर्णांक err;

	alx_reset_phy(hw);

	अगर (!netअगर_running(alx->dev))
		वापस 0;

	rtnl_lock();
	err = __alx_खोलो(alx, true);
	rtnl_unlock();
	अगर (err)
		वापस err;

	netअगर_device_attach(alx->dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(alx_pm_ops, alx_suspend, alx_resume);
#घोषणा ALX_PM_OPS      (&alx_pm_ops)
#अन्यथा
#घोषणा ALX_PM_OPS      शून्य
#पूर्ण_अगर


अटल pci_ers_result_t alx_pci_error_detected(काष्ठा pci_dev *pdev,
					       pci_channel_state_t state)
अणु
	काष्ठा alx_priv *alx = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = alx->dev;
	pci_ers_result_t rc = PCI_ERS_RESULT_NEED_RESET;

	dev_info(&pdev->dev, "pci error detected\n");

	rtnl_lock();

	अगर (netअगर_running(netdev)) अणु
		netअगर_device_detach(netdev);
		alx_halt(alx);
	पूर्ण

	अगर (state == pci_channel_io_perm_failure)
		rc = PCI_ERS_RESULT_DISCONNECT;
	अन्यथा
		pci_disable_device(pdev);

	rtnl_unlock();

	वापस rc;
पूर्ण

अटल pci_ers_result_t alx_pci_error_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा alx_priv *alx = pci_get_drvdata(pdev);
	काष्ठा alx_hw *hw = &alx->hw;
	pci_ers_result_t rc = PCI_ERS_RESULT_DISCONNECT;

	dev_info(&pdev->dev, "pci error slot reset\n");

	rtnl_lock();

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "Failed to re-enable PCI device after reset\n");
		जाओ out;
	पूर्ण

	pci_set_master(pdev);

	alx_reset_pcie(hw);
	अगर (!alx_reset_mac(hw))
		rc = PCI_ERS_RESULT_RECOVERED;
out:
	rtnl_unlock();

	वापस rc;
पूर्ण

अटल व्योम alx_pci_error_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा alx_priv *alx = pci_get_drvdata(pdev);
	काष्ठा net_device *netdev = alx->dev;

	dev_info(&pdev->dev, "pci error resume\n");

	rtnl_lock();

	अगर (netअगर_running(netdev)) अणु
		alx_activate(alx);
		netअगर_device_attach(netdev);
	पूर्ण

	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers alx_err_handlers = अणु
	.error_detected = alx_pci_error_detected,
	.slot_reset     = alx_pci_error_slot_reset,
	.resume         = alx_pci_error_resume,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id alx_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ATTANSIC, ALX_DEV_ID_AR8161),
	  .driver_data = ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG पूर्ण,
	अणु PCI_VDEVICE(ATTANSIC, ALX_DEV_ID_E2200),
	  .driver_data = ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG पूर्ण,
	अणु PCI_VDEVICE(ATTANSIC, ALX_DEV_ID_E2400),
	  .driver_data = ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG पूर्ण,
	अणु PCI_VDEVICE(ATTANSIC, ALX_DEV_ID_E2500),
	  .driver_data = ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG पूर्ण,
	अणु PCI_VDEVICE(ATTANSIC, ALX_DEV_ID_AR8162),
	  .driver_data = ALX_DEV_QUIRK_MSI_INTX_DISABLE_BUG पूर्ण,
	अणु PCI_VDEVICE(ATTANSIC, ALX_DEV_ID_AR8171) पूर्ण,
	अणु PCI_VDEVICE(ATTANSIC, ALX_DEV_ID_AR8172) पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा pci_driver alx_driver = अणु
	.name        = alx_drv_name,
	.id_table    = alx_pci_tbl,
	.probe       = alx_probe,
	.हटाओ      = alx_हटाओ,
	.err_handler = &alx_err_handlers,
	.driver.pm   = ALX_PM_OPS,
पूर्ण;

module_pci_driver(alx_driver);
MODULE_DEVICE_TABLE(pci, alx_pci_tbl);
MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_AUTHOR("Qualcomm Corporation");
MODULE_DESCRIPTION(
	"Qualcomm Atheros(R) AR816x/AR817x PCI-E Ethernet Network Driver");
MODULE_LICENSE("GPL");
