<शैली गुरु>
/*
 * Copyright(c) 2017 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains HFI1 support क्रम VNIC SDMA functionality
 */

#समावेश "sdma.h"
#समावेश "vnic.h"

#घोषणा HFI1_VNIC_SDMA_Q_ACTIVE   BIT(0)
#घोषणा HFI1_VNIC_SDMA_Q_DEFERRED BIT(1)

#घोषणा HFI1_VNIC_TXREQ_NAME_LEN   32
#घोषणा HFI1_VNIC_SDMA_DESC_WTRMRK 64

/*
 * काष्ठा vnic_txreq - VNIC transmit descriptor
 * @txreq: sdma transmit request
 * @sdma: vnic sdma poपूर्णांकer
 * @skb: skb to send
 * @pad: pad buffer
 * @plen: pad length
 * @pbc_val: pbc value
 */
काष्ठा vnic_txreq अणु
	काष्ठा sdma_txreq       txreq;
	काष्ठा hfi1_vnic_sdma   *sdma;

	काष्ठा sk_buff         *skb;
	अचिन्हित अक्षर           pad[HFI1_VNIC_MAX_PAD];
	u16                     plen;
	__le64                  pbc_val;
पूर्ण;

अटल व्योम vnic_sdma_complete(काष्ठा sdma_txreq *txreq,
			       पूर्णांक status)
अणु
	काष्ठा vnic_txreq *tx = container_of(txreq, काष्ठा vnic_txreq, txreq);
	काष्ठा hfi1_vnic_sdma *vnic_sdma = tx->sdma;

	sdma_txclean(vnic_sdma->dd, txreq);
	dev_kमुक्त_skb_any(tx->skb);
	kmem_cache_मुक्त(vnic_sdma->dd->vnic.txreq_cache, tx);
पूर्ण

अटल noअंतरभूत पूर्णांक build_vnic_ulp_payload(काष्ठा sdma_engine *sde,
					   काष्ठा vnic_txreq *tx)
अणु
	पूर्णांक i, ret = 0;

	ret = sdma_txadd_kvaddr(
		sde->dd,
		&tx->txreq,
		tx->skb->data,
		skb_headlen(tx->skb));
	अगर (unlikely(ret))
		जाओ bail_txadd;

	क्रम (i = 0; i < skb_shinfo(tx->skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(tx->skb)->frags[i];

		/* combine physically continuous fragments later? */
		ret = sdma_txadd_page(sde->dd,
				      &tx->txreq,
				      skb_frag_page(frag),
				      skb_frag_off(frag),
				      skb_frag_size(frag));
		अगर (unlikely(ret))
			जाओ bail_txadd;
	पूर्ण

	अगर (tx->plen)
		ret = sdma_txadd_kvaddr(sde->dd, &tx->txreq,
					tx->pad + HFI1_VNIC_MAX_PAD - tx->plen,
					tx->plen);

bail_txadd:
	वापस ret;
पूर्ण

अटल पूर्णांक build_vnic_tx_desc(काष्ठा sdma_engine *sde,
			      काष्ठा vnic_txreq *tx,
			      u64 pbc)
अणु
	पूर्णांक ret = 0;
	u16 hdrbytes = 2 << 2;  /* PBC */

	ret = sdma_txinit_ahg(
		&tx->txreq,
		0,
		hdrbytes + tx->skb->len + tx->plen,
		0,
		0,
		शून्य,
		0,
		vnic_sdma_complete);
	अगर (unlikely(ret))
		जाओ bail_txadd;

	/* add pbc */
	tx->pbc_val = cpu_to_le64(pbc);
	ret = sdma_txadd_kvaddr(
		sde->dd,
		&tx->txreq,
		&tx->pbc_val,
		hdrbytes);
	अगर (unlikely(ret))
		जाओ bail_txadd;

	/* add the ulp payload */
	ret = build_vnic_ulp_payload(sde, tx);
bail_txadd:
	वापस ret;
पूर्ण

/* setup the last plen bypes of pad */
अटल अंतरभूत व्योम hfi1_vnic_update_pad(अचिन्हित अक्षर *pad, u8 plen)
अणु
	pad[HFI1_VNIC_MAX_PAD - 1] = plen - OPA_VNIC_ICRC_TAIL_LEN;
पूर्ण

पूर्णांक hfi1_vnic_send_dma(काष्ठा hfi1_devdata *dd, u8 q_idx,
		       काष्ठा hfi1_vnic_vport_info *vinfo,
		       काष्ठा sk_buff *skb, u64 pbc, u8 plen)
अणु
	काष्ठा hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[q_idx];
	काष्ठा sdma_engine *sde = vnic_sdma->sde;
	काष्ठा vnic_txreq *tx;
	पूर्णांक ret = -ECOMM;

	अगर (unlikely(READ_ONCE(vnic_sdma->state) != HFI1_VNIC_SDMA_Q_ACTIVE))
		जाओ tx_err;

	अगर (unlikely(!sde || !sdma_running(sde)))
		जाओ tx_err;

	tx = kmem_cache_alloc(dd->vnic.txreq_cache, GFP_ATOMIC);
	अगर (unlikely(!tx)) अणु
		ret = -ENOMEM;
		जाओ tx_err;
	पूर्ण

	tx->sdma = vnic_sdma;
	tx->skb = skb;
	hfi1_vnic_update_pad(tx->pad, plen);
	tx->plen = plen;
	ret = build_vnic_tx_desc(sde, tx, pbc);
	अगर (unlikely(ret))
		जाओ मुक्त_desc;

	ret = sdma_send_txreq(sde, ioरुको_get_ib_work(&vnic_sdma->रुको),
			      &tx->txreq, vnic_sdma->pkts_sent);
	/* When -ECOMM, sdma callback will be called with ABORT status */
	अगर (unlikely(ret && unlikely(ret != -ECOMM)))
		जाओ मुक्त_desc;

	अगर (!ret) अणु
		vnic_sdma->pkts_sent = true;
		ioरुको_starve_clear(vnic_sdma->pkts_sent, &vnic_sdma->रुको);
	पूर्ण
	वापस ret;

मुक्त_desc:
	sdma_txclean(dd, &tx->txreq);
	kmem_cache_मुक्त(dd->vnic.txreq_cache, tx);
tx_err:
	अगर (ret != -EBUSY)
		dev_kमुक्त_skb_any(skb);
	अन्यथा
		vnic_sdma->pkts_sent = false;
	वापस ret;
पूर्ण

/*
 * hfi1_vnic_sdma_sleep - vnic sdma sleep function
 *
 * This function माला_लो called from sdma_send_txreq() when there are not enough
 * sdma descriptors available to send the packet. It adds Tx queue's रुको
 * काष्ठाure to sdma engine's dmaरुको list to be woken up when descriptors
 * become available.
 */
अटल पूर्णांक hfi1_vnic_sdma_sleep(काष्ठा sdma_engine *sde,
				काष्ठा ioरुको_work *रुको,
				काष्ठा sdma_txreq *txreq,
				uपूर्णांक seq,
				bool pkts_sent)
अणु
	काष्ठा hfi1_vnic_sdma *vnic_sdma =
		container_of(रुको->iow, काष्ठा hfi1_vnic_sdma, रुको);

	ग_लिखो_seqlock(&sde->रुकोlock);
	अगर (sdma_progress(sde, seq, txreq)) अणु
		ग_लिखो_sequnlock(&sde->रुकोlock);
		वापस -EAGAIN;
	पूर्ण

	vnic_sdma->state = HFI1_VNIC_SDMA_Q_DEFERRED;
	अगर (list_empty(&vnic_sdma->रुको.list)) अणु
		ioरुको_get_priority(रुको->iow);
		ioरुको_queue(pkts_sent, रुको->iow, &sde->dmaरुको);
	पूर्ण
	ग_लिखो_sequnlock(&sde->रुकोlock);
	वापस -EBUSY;
पूर्ण

/*
 * hfi1_vnic_sdma_wakeup - vnic sdma wakeup function
 *
 * This function माला_लो called when SDMA descriptors becomes available and Tx
 * queue's wait structure was previously added to sdma engine's dmaरुको list.
 * It notअगरies the upper driver about Tx queue wakeup.
 */
अटल व्योम hfi1_vnic_sdma_wakeup(काष्ठा ioरुको *रुको, पूर्णांक reason)
अणु
	काष्ठा hfi1_vnic_sdma *vnic_sdma =
		container_of(रुको, काष्ठा hfi1_vnic_sdma, रुको);
	काष्ठा hfi1_vnic_vport_info *vinfo = vnic_sdma->vinfo;

	vnic_sdma->state = HFI1_VNIC_SDMA_Q_ACTIVE;
	अगर (__netअगर_subqueue_stopped(vinfo->netdev, vnic_sdma->q_idx))
		netअगर_wake_subqueue(vinfo->netdev, vnic_sdma->q_idx);
पूर्ण;

अंतरभूत bool hfi1_vnic_sdma_ग_लिखो_avail(काष्ठा hfi1_vnic_vport_info *vinfo,
				       u8 q_idx)
अणु
	काष्ठा hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[q_idx];

	वापस (READ_ONCE(vnic_sdma->state) == HFI1_VNIC_SDMA_Q_ACTIVE);
पूर्ण

व्योम hfi1_vnic_sdma_init(काष्ठा hfi1_vnic_vport_info *vinfo)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vinfo->num_tx_q; i++) अणु
		काष्ठा hfi1_vnic_sdma *vnic_sdma = &vinfo->sdma[i];

		ioरुको_init(&vnic_sdma->रुको, 0, शून्य, शून्य,
			    hfi1_vnic_sdma_sleep,
			    hfi1_vnic_sdma_wakeup, शून्य, शून्य);
		vnic_sdma->sde = &vinfo->dd->per_sdma[i];
		vnic_sdma->dd = vinfo->dd;
		vnic_sdma->vinfo = vinfo;
		vnic_sdma->q_idx = i;
		vnic_sdma->state = HFI1_VNIC_SDMA_Q_ACTIVE;

		/* Add a मुक्त descriptor watermark क्रम wakeups */
		अगर (vnic_sdma->sde->descq_cnt > HFI1_VNIC_SDMA_DESC_WTRMRK) अणु
			काष्ठा ioरुको_work *work;

			INIT_LIST_HEAD(&vnic_sdma->stx.list);
			vnic_sdma->stx.num_desc = HFI1_VNIC_SDMA_DESC_WTRMRK;
			work = ioरुको_get_ib_work(&vnic_sdma->रुको);
			list_add_tail(&vnic_sdma->stx.list, &work->tx_head);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक hfi1_vnic_txreq_init(काष्ठा hfi1_devdata *dd)
अणु
	अक्षर buf[HFI1_VNIC_TXREQ_NAME_LEN];

	snम_लिखो(buf, माप(buf), "hfi1_%u_vnic_txreq_cache", dd->unit);
	dd->vnic.txreq_cache = kmem_cache_create(buf,
						 माप(काष्ठा vnic_txreq),
						 0, SLAB_HWCACHE_ALIGN,
						 शून्य);
	अगर (!dd->vnic.txreq_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम hfi1_vnic_txreq_deinit(काष्ठा hfi1_devdata *dd)
अणु
	kmem_cache_destroy(dd->vnic.txreq_cache);
	dd->vnic.txreq_cache = शून्य;
पूर्ण
