<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Applied Micro X-Gene SoC Ethernet Driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Authors: Iyappan Subramanian <isubramanian@apm.com>
 *	    Ravi Patel <rapatel@apm.com>
 *	    Keyur Chudgar <kchudgar@apm.com>
 */

#समावेश <linux/gpपन.स>
#समावेश "xgene_enet_main.h"
#समावेश "xgene_enet_hw.h"
#समावेश "xgene_enet_sgmac.h"
#समावेश "xgene_enet_xgmac.h"

#घोषणा RES_ENET_CSR	0
#घोषणा RES_RING_CSR	1
#घोषणा RES_RING_CMD	2

अटल व्योम xgene_enet_init_bufpool(काष्ठा xgene_enet_desc_ring *buf_pool)
अणु
	काष्ठा xgene_enet_raw_desc16 *raw_desc;
	पूर्णांक i;

	अगर (!buf_pool)
		वापस;

	क्रम (i = 0; i < buf_pool->slots; i++) अणु
		raw_desc = &buf_pool->raw_desc16[i];

		/* Hardware expects descriptor in little endian क्रमmat */
		raw_desc->m0 = cpu_to_le64(i |
				SET_VAL(FPQNUM, buf_pool->dst_ring_num) |
				SET_VAL(STASH, 3));
	पूर्ण
पूर्ण

अटल u16 xgene_enet_get_data_len(u64 bufdatalen)
अणु
	u16 hw_len, mask;

	hw_len = GET_VAL(BUFDATALEN, bufdatalen);

	अगर (unlikely(hw_len == 0x7800)) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (!(hw_len & BIT(14))) अणु
		mask = GENMASK(13, 0);
		वापस (hw_len & mask) ? (hw_len & mask) : SIZE_16K;
	पूर्ण अन्यथा अगर (!(hw_len & GENMASK(13, 12))) अणु
		mask = GENMASK(11, 0);
		वापस (hw_len & mask) ? (hw_len & mask) : SIZE_4K;
	पूर्ण अन्यथा अणु
		mask = GENMASK(11, 0);
		वापस (hw_len & mask) ? (hw_len & mask) : SIZE_2K;
	पूर्ण
पूर्ण

अटल u16 xgene_enet_set_data_len(u32 size)
अणु
	u16 hw_len;

	hw_len =  (size == SIZE_4K) ? BIT(14) : 0;

	वापस hw_len;
पूर्ण

अटल पूर्णांक xgene_enet_refill_pagepool(काष्ठा xgene_enet_desc_ring *buf_pool,
				      u32 nbuf)
अणु
	काष्ठा xgene_enet_raw_desc16 *raw_desc;
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा net_device *ndev;
	dma_addr_t dma_addr;
	काष्ठा device *dev;
	काष्ठा page *page;
	u32 slots, tail;
	u16 hw_len;
	पूर्णांक i;

	अगर (unlikely(!buf_pool))
		वापस 0;

	ndev = buf_pool->ndev;
	pdata = netdev_priv(ndev);
	dev = ndev_to_dev(ndev);
	slots = buf_pool->slots - 1;
	tail = buf_pool->tail;

	क्रम (i = 0; i < nbuf; i++) अणु
		raw_desc = &buf_pool->raw_desc16[tail];

		page = dev_alloc_page();
		अगर (unlikely(!page))
			वापस -ENOMEM;

		dma_addr = dma_map_page(dev, page, 0,
					PAGE_SIZE, DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(dev, dma_addr))) अणु
			put_page(page);
			वापस -ENOMEM;
		पूर्ण

		hw_len = xgene_enet_set_data_len(PAGE_SIZE);
		raw_desc->m1 = cpu_to_le64(SET_VAL(DATAADDR, dma_addr) |
					   SET_VAL(BUFDATALEN, hw_len) |
					   SET_BIT(COHERENT));

		buf_pool->frag_page[tail] = page;
		tail = (tail + 1) & slots;
	पूर्ण

	pdata->ring_ops->wr_cmd(buf_pool, nbuf);
	buf_pool->tail = tail;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_enet_refill_bufpool(काष्ठा xgene_enet_desc_ring *buf_pool,
				     u32 nbuf)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा xgene_enet_raw_desc16 *raw_desc;
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा net_device *ndev;
	काष्ठा device *dev;
	dma_addr_t dma_addr;
	u32 tail = buf_pool->tail;
	u32 slots = buf_pool->slots - 1;
	u16 bufdatalen, len;
	पूर्णांक i;

	ndev = buf_pool->ndev;
	dev = ndev_to_dev(buf_pool->ndev);
	pdata = netdev_priv(ndev);

	bufdatalen = BUF_LEN_CODE_2K | (SKB_BUFFER_SIZE & GENMASK(11, 0));
	len = XGENE_ENET_STD_MTU;

	क्रम (i = 0; i < nbuf; i++) अणु
		raw_desc = &buf_pool->raw_desc16[tail];

		skb = netdev_alloc_skb_ip_align(ndev, len);
		अगर (unlikely(!skb))
			वापस -ENOMEM;

		dma_addr = dma_map_single(dev, skb->data, len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			netdev_err(ndev, "DMA mapping error\n");
			dev_kमुक्त_skb_any(skb);
			वापस -EINVAL;
		पूर्ण

		buf_pool->rx_skb[tail] = skb;

		raw_desc->m1 = cpu_to_le64(SET_VAL(DATAADDR, dma_addr) |
					   SET_VAL(BUFDATALEN, bufdatalen) |
					   SET_BIT(COHERENT));
		tail = (tail + 1) & slots;
	पूर्ण

	pdata->ring_ops->wr_cmd(buf_pool, nbuf);
	buf_pool->tail = tail;

	वापस 0;
पूर्ण

अटल u8 xgene_enet_hdr_len(स्थिर व्योम *data)
अणु
	स्थिर काष्ठा ethhdr *eth = data;

	वापस (eth->h_proto == htons(ETH_P_8021Q)) ? VLAN_ETH_HLEN : ETH_HLEN;
पूर्ण

अटल व्योम xgene_enet_delete_bufpool(काष्ठा xgene_enet_desc_ring *buf_pool)
अणु
	काष्ठा device *dev = ndev_to_dev(buf_pool->ndev);
	काष्ठा xgene_enet_raw_desc16 *raw_desc;
	dma_addr_t dma_addr;
	पूर्णांक i;

	/* Free up the buffers held by hardware */
	क्रम (i = 0; i < buf_pool->slots; i++) अणु
		अगर (buf_pool->rx_skb[i]) अणु
			dev_kमुक्त_skb_any(buf_pool->rx_skb[i]);

			raw_desc = &buf_pool->raw_desc16[i];
			dma_addr = GET_VAL(DATAADDR, le64_to_cpu(raw_desc->m1));
			dma_unmap_single(dev, dma_addr, XGENE_ENET_MAX_MTU,
					 DMA_FROM_DEVICE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_delete_pagepool(काष्ठा xgene_enet_desc_ring *buf_pool)
अणु
	काष्ठा device *dev = ndev_to_dev(buf_pool->ndev);
	dma_addr_t dma_addr;
	काष्ठा page *page;
	पूर्णांक i;

	/* Free up the buffers held by hardware */
	क्रम (i = 0; i < buf_pool->slots; i++) अणु
		page = buf_pool->frag_page[i];
		अगर (page) अणु
			dma_addr = buf_pool->frag_dma_addr[i];
			dma_unmap_page(dev, dma_addr, PAGE_SIZE,
				       DMA_FROM_DEVICE);
			put_page(page);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t xgene_enet_rx_irq(स्थिर पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xgene_enet_desc_ring *rx_ring = data;

	अगर (napi_schedule_prep(&rx_ring->napi)) अणु
		disable_irq_nosync(irq);
		__napi_schedule(&rx_ring->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xgene_enet_tx_completion(काष्ठा xgene_enet_desc_ring *cp_ring,
				    काष्ठा xgene_enet_raw_desc *raw_desc)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(cp_ring->ndev);
	काष्ठा sk_buff *skb;
	काष्ठा device *dev;
	skb_frag_t *frag;
	dma_addr_t *frag_dma_addr;
	u16 skb_index;
	u8 mss_index;
	u8 status;
	पूर्णांक i;

	skb_index = GET_VAL(USERINFO, le64_to_cpu(raw_desc->m0));
	skb = cp_ring->cp_skb[skb_index];
	frag_dma_addr = &cp_ring->frag_dma_addr[skb_index * MAX_SKB_FRAGS];

	dev = ndev_to_dev(cp_ring->ndev);
	dma_unmap_single(dev, GET_VAL(DATAADDR, le64_to_cpu(raw_desc->m1)),
			 skb_headlen(skb),
			 DMA_TO_DEVICE);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		dma_unmap_page(dev, frag_dma_addr[i], skb_frag_size(frag),
			       DMA_TO_DEVICE);
	पूर्ण

	अगर (GET_BIT(ET, le64_to_cpu(raw_desc->m3))) अणु
		mss_index = GET_VAL(MSS, le64_to_cpu(raw_desc->m3));
		spin_lock(&pdata->mss_lock);
		pdata->mss_refcnt[mss_index]--;
		spin_unlock(&pdata->mss_lock);
	पूर्ण

	/* Checking क्रम error */
	status = GET_VAL(LERR, le64_to_cpu(raw_desc->m0));
	अगर (unlikely(status > 2)) अणु
		cp_ring->tx_dropped++;
		cp_ring->tx_errors++;
	पूर्ण

	अगर (likely(skb)) अणु
		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
		netdev_err(cp_ring->ndev, "completion skb is NULL\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_enet_setup_mss(काष्ठा net_device *ndev, u32 mss)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	पूर्णांक mss_index = -EBUSY;
	पूर्णांक i;

	spin_lock(&pdata->mss_lock);

	/* Reuse the slot अगर MSS matches */
	क्रम (i = 0; mss_index < 0 && i < NUM_MSS_REG; i++) अणु
		अगर (pdata->mss[i] == mss) अणु
			pdata->mss_refcnt[i]++;
			mss_index = i;
		पूर्ण
	पूर्ण

	/* Overग_लिखो the slot with ref_count = 0 */
	क्रम (i = 0; mss_index < 0 && i < NUM_MSS_REG; i++) अणु
		अगर (!pdata->mss_refcnt[i]) अणु
			pdata->mss_refcnt[i]++;
			pdata->mac_ops->set_mss(pdata, mss, i);
			pdata->mss[i] = mss;
			mss_index = i;
		पूर्ण
	पूर्ण

	spin_unlock(&pdata->mss_lock);

	वापस mss_index;
पूर्ण

अटल पूर्णांक xgene_enet_work_msg(काष्ठा sk_buff *skb, u64 *hopinfo)
अणु
	काष्ठा net_device *ndev = skb->dev;
	काष्ठा iphdr *iph;
	u8 l3hlen = 0, l4hlen = 0;
	u8 ethhdr, proto = 0, csum_enable = 0;
	u32 hdr_len, mss = 0;
	u32 i, len, nr_frags;
	पूर्णांक mss_index;

	ethhdr = xgene_enet_hdr_len(skb->data);

	अगर (unlikely(skb->protocol != htons(ETH_P_IP)) &&
	    unlikely(skb->protocol != htons(ETH_P_8021Q)))
		जाओ out;

	अगर (unlikely(!(skb->dev->features & NETIF_F_IP_CSUM)))
		जाओ out;

	iph = ip_hdr(skb);
	अगर (unlikely(ip_is_fragment(iph)))
		जाओ out;

	अगर (likely(iph->protocol == IPPROTO_TCP)) अणु
		l4hlen = tcp_hdrlen(skb) >> 2;
		csum_enable = 1;
		proto = TSO_IPPROTO_TCP;
		अगर (ndev->features & NETIF_F_TSO) अणु
			hdr_len = ethhdr + ip_hdrlen(skb) + tcp_hdrlen(skb);
			mss = skb_shinfo(skb)->gso_size;

			अगर (skb_is_nonlinear(skb)) अणु
				len = skb_headlen(skb);
				nr_frags = skb_shinfo(skb)->nr_frags;

				क्रम (i = 0; i < 2 && i < nr_frags; i++)
					len += skb_frag_size(
						&skb_shinfo(skb)->frags[i]);

				/* HW requires header must reside in 3 buffer */
				अगर (unlikely(hdr_len > len)) अणु
					अगर (skb_linearize(skb))
						वापस 0;
				पूर्ण
			पूर्ण

			अगर (!mss || ((skb->len - hdr_len) <= mss))
				जाओ out;

			mss_index = xgene_enet_setup_mss(ndev, mss);
			अगर (unlikely(mss_index < 0))
				वापस -EBUSY;

			*hopinfo |= SET_BIT(ET) | SET_VAL(MSS, mss_index);
		पूर्ण
	पूर्ण अन्यथा अगर (iph->protocol == IPPROTO_UDP) अणु
		l4hlen = UDP_HDR_SIZE;
		csum_enable = 1;
	पूर्ण
out:
	l3hlen = ip_hdrlen(skb) >> 2;
	*hopinfo |= SET_VAL(TCPHDR, l4hlen) |
		    SET_VAL(IPHDR, l3hlen) |
		    SET_VAL(ETHHDR, ethhdr) |
		    SET_VAL(EC, csum_enable) |
		    SET_VAL(IS, proto) |
		    SET_BIT(IC) |
		    SET_BIT(TYPE_ETH_WORK_MESSAGE);

	वापस 0;
पूर्ण

अटल u16 xgene_enet_encode_len(u16 len)
अणु
	वापस (len == BUFLEN_16K) ? 0 : len;
पूर्ण

अटल व्योम xgene_set_addr_len(__le64 *desc, u32 idx, dma_addr_t addr, u32 len)
अणु
	desc[idx ^ 1] = cpu_to_le64(SET_VAL(DATAADDR, addr) |
				    SET_VAL(BUFDATALEN, len));
पूर्ण

अटल __le64 *xgene_enet_get_exp_bufs(काष्ठा xgene_enet_desc_ring *ring)
अणु
	__le64 *exp_bufs;

	exp_bufs = &ring->exp_bufs[ring->exp_buf_tail * MAX_EXP_BUFFS];
	स_रखो(exp_bufs, 0, माप(__le64) * MAX_EXP_BUFFS);
	ring->exp_buf_tail = (ring->exp_buf_tail + 1) & ((ring->slots / 2) - 1);

	वापस exp_bufs;
पूर्ण

अटल dma_addr_t *xgene_get_frag_dma_array(काष्ठा xgene_enet_desc_ring *ring)
अणु
	वापस &ring->cp_ring->frag_dma_addr[ring->tail * MAX_SKB_FRAGS];
पूर्ण

अटल पूर्णांक xgene_enet_setup_tx_desc(काष्ठा xgene_enet_desc_ring *tx_ring,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dev = ndev_to_dev(tx_ring->ndev);
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(tx_ring->ndev);
	काष्ठा xgene_enet_raw_desc *raw_desc;
	__le64 *exp_desc = शून्य, *exp_bufs = शून्य;
	dma_addr_t dma_addr, pbuf_addr, *frag_dma_addr;
	skb_frag_t *frag;
	u16 tail = tx_ring->tail;
	u64 hopinfo = 0;
	u32 len, hw_len;
	u8 ll = 0, nv = 0, idx = 0;
	bool split = false;
	u32 size, offset, ell_bytes = 0;
	u32 i, fidx, nr_frags, count = 1;
	पूर्णांक ret;

	raw_desc = &tx_ring->raw_desc[tail];
	tail = (tail + 1) & (tx_ring->slots - 1);
	स_रखो(raw_desc, 0, माप(काष्ठा xgene_enet_raw_desc));

	ret = xgene_enet_work_msg(skb, &hopinfo);
	अगर (ret)
		वापस ret;

	raw_desc->m3 = cpu_to_le64(SET_VAL(HENQNUM, tx_ring->dst_ring_num) |
				   hopinfo);

	len = skb_headlen(skb);
	hw_len = xgene_enet_encode_len(len);

	dma_addr = dma_map_single(dev, skb->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		netdev_err(tx_ring->ndev, "DMA mapping error\n");
		वापस -EINVAL;
	पूर्ण

	/* Hardware expects descriptor in little endian क्रमmat */
	raw_desc->m1 = cpu_to_le64(SET_VAL(DATAADDR, dma_addr) |
				   SET_VAL(BUFDATALEN, hw_len) |
				   SET_BIT(COHERENT));

	अगर (!skb_is_nonlinear(skb))
		जाओ out;

	/* scatter gather */
	nv = 1;
	exp_desc = (व्योम *)&tx_ring->raw_desc[tail];
	tail = (tail + 1) & (tx_ring->slots - 1);
	स_रखो(exp_desc, 0, माप(काष्ठा xgene_enet_raw_desc));

	nr_frags = skb_shinfo(skb)->nr_frags;
	क्रम (i = nr_frags; i < 4 ; i++)
		exp_desc[i ^ 1] = cpu_to_le64(LAST_BUFFER);

	frag_dma_addr = xgene_get_frag_dma_array(tx_ring);

	क्रम (i = 0, fidx = 0; split || (fidx < nr_frags); i++) अणु
		अगर (!split) अणु
			frag = &skb_shinfo(skb)->frags[fidx];
			size = skb_frag_size(frag);
			offset = 0;

			pbuf_addr = skb_frag_dma_map(dev, frag, 0, size,
						     DMA_TO_DEVICE);
			अगर (dma_mapping_error(dev, pbuf_addr))
				वापस -EINVAL;

			frag_dma_addr[fidx] = pbuf_addr;
			fidx++;

			अगर (size > BUFLEN_16K)
				split = true;
		पूर्ण

		अगर (size > BUFLEN_16K) अणु
			len = BUFLEN_16K;
			size -= BUFLEN_16K;
		पूर्ण अन्यथा अणु
			len = size;
			split = false;
		पूर्ण

		dma_addr = pbuf_addr + offset;
		hw_len = xgene_enet_encode_len(len);

		चयन (i) अणु
		हाल 0:
		हाल 1:
		हाल 2:
			xgene_set_addr_len(exp_desc, i, dma_addr, hw_len);
			अवरोध;
		हाल 3:
			अगर (split || (fidx != nr_frags)) अणु
				exp_bufs = xgene_enet_get_exp_bufs(tx_ring);
				xgene_set_addr_len(exp_bufs, idx, dma_addr,
						   hw_len);
				idx++;
				ell_bytes += len;
			पूर्ण अन्यथा अणु
				xgene_set_addr_len(exp_desc, i, dma_addr,
						   hw_len);
			पूर्ण
			अवरोध;
		शेष:
			xgene_set_addr_len(exp_bufs, idx, dma_addr, hw_len);
			idx++;
			ell_bytes += len;
			अवरोध;
		पूर्ण

		अगर (split)
			offset += BUFLEN_16K;
	पूर्ण
	count++;

	अगर (idx) अणु
		ll = 1;
		dma_addr = dma_map_single(dev, exp_bufs,
					  माप(u64) * MAX_EXP_BUFFS,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस -EINVAL;
		पूर्ण
		i = ell_bytes >> LL_BYTES_LSB_LEN;
		exp_desc[2] = cpu_to_le64(SET_VAL(DATAADDR, dma_addr) |
					  SET_VAL(LL_BYTES_MSB, i) |
					  SET_VAL(LL_LEN, idx));
		raw_desc->m2 = cpu_to_le64(SET_VAL(LL_BYTES_LSB, ell_bytes));
	पूर्ण

out:
	raw_desc->m0 = cpu_to_le64(SET_VAL(LL, ll) | SET_VAL(NV, nv) |
				   SET_VAL(USERINFO, tx_ring->tail));
	tx_ring->cp_ring->cp_skb[tx_ring->tail] = skb;
	pdata->tx_level[tx_ring->cp_ring->index] += count;
	tx_ring->tail = tail;

	वापस count;
पूर्ण

अटल netdev_tx_t xgene_enet_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा xgene_enet_desc_ring *tx_ring;
	पूर्णांक index = skb->queue_mapping;
	u32 tx_level = pdata->tx_level[index];
	पूर्णांक count;

	tx_ring = pdata->tx_ring[index];
	अगर (tx_level < pdata->txc_level[index])
		tx_level += ((typeof(pdata->tx_level[index]))~0U);

	अगर ((tx_level - pdata->txc_level[index]) > pdata->tx_qcnt_hi) अणु
		netअगर_stop_subqueue(ndev, index);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (skb_padto(skb, XGENE_MIN_ENET_FRAME_SIZE))
		वापस NETDEV_TX_OK;

	count = xgene_enet_setup_tx_desc(tx_ring, skb);
	अगर (count == -EBUSY)
		वापस NETDEV_TX_BUSY;

	अगर (count <= 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	skb_tx_बारtamp(skb);

	tx_ring->tx_packets++;
	tx_ring->tx_bytes += skb->len;

	pdata->ring_ops->wr_cmd(tx_ring, count);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम xgene_enet_rx_csum(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *ndev = skb->dev;
	काष्ठा iphdr *iph = ip_hdr(skb);

	अगर (!(ndev->features & NETIF_F_RXCSUM))
		वापस;

	अगर (skb->protocol != htons(ETH_P_IP))
		वापस;

	अगर (ip_is_fragment(iph))
		वापस;

	अगर (iph->protocol != IPPROTO_TCP && iph->protocol != IPPROTO_UDP)
		वापस;

	skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल व्योम xgene_enet_मुक्त_pagepool(काष्ठा xgene_enet_desc_ring *buf_pool,
				     काष्ठा xgene_enet_raw_desc *raw_desc,
				     काष्ठा xgene_enet_raw_desc *exp_desc)
अणु
	__le64 *desc = (व्योम *)exp_desc;
	dma_addr_t dma_addr;
	काष्ठा device *dev;
	काष्ठा page *page;
	u16 slots, head;
	u32 frag_size;
	पूर्णांक i;

	अगर (!buf_pool || !raw_desc || !exp_desc ||
	    (!GET_VAL(NV, le64_to_cpu(raw_desc->m0))))
		वापस;

	dev = ndev_to_dev(buf_pool->ndev);
	slots = buf_pool->slots - 1;
	head = buf_pool->head;

	क्रम (i = 0; i < 4; i++) अणु
		frag_size = xgene_enet_get_data_len(le64_to_cpu(desc[i ^ 1]));
		अगर (!frag_size)
			अवरोध;

		dma_addr = GET_VAL(DATAADDR, le64_to_cpu(desc[i ^ 1]));
		dma_unmap_page(dev, dma_addr, PAGE_SIZE, DMA_FROM_DEVICE);

		page = buf_pool->frag_page[head];
		put_page(page);

		buf_pool->frag_page[head] = शून्य;
		head = (head + 1) & slots;
	पूर्ण
	buf_pool->head = head;
पूर्ण

/* Errata 10GE_10 and ENET_15 - Fix duplicated HW statistic counters */
अटल bool xgene_enet_errata_10GE_10(काष्ठा sk_buff *skb, u32 len, u8 status)
अणु
	अगर (status == INGRESS_CRC &&
	    len >= (ETHER_STD_PACKET + 1) &&
	    len <= (ETHER_STD_PACKET + 4) &&
	    skb->protocol == htons(ETH_P_8021Q))
		वापस true;

	वापस false;
पूर्ण

/* Errata 10GE_8 and ENET_11 - allow packet with length <=64B */
अटल bool xgene_enet_errata_10GE_8(काष्ठा sk_buff *skb, u32 len, u8 status)
अणु
	अगर (status == INGRESS_PKT_LEN && len == ETHER_MIN_PACKET) अणु
		अगर (ntohs(eth_hdr(skb)->h_proto) < 46)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक xgene_enet_rx_frame(काष्ठा xgene_enet_desc_ring *rx_ring,
			       काष्ठा xgene_enet_raw_desc *raw_desc,
			       काष्ठा xgene_enet_raw_desc *exp_desc)
अणु
	काष्ठा xgene_enet_desc_ring *buf_pool, *page_pool;
	u32 datalen, frag_size, skb_index;
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा net_device *ndev;
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
	काष्ठा device *dev;
	काष्ठा page *page;
	u16 slots, head;
	पूर्णांक i, ret = 0;
	__le64 *desc;
	u8 status;
	bool nv;

	ndev = rx_ring->ndev;
	pdata = netdev_priv(ndev);
	dev = ndev_to_dev(rx_ring->ndev);
	buf_pool = rx_ring->buf_pool;
	page_pool = rx_ring->page_pool;

	dma_unmap_single(dev, GET_VAL(DATAADDR, le64_to_cpu(raw_desc->m1)),
			 XGENE_ENET_STD_MTU, DMA_FROM_DEVICE);
	skb_index = GET_VAL(USERINFO, le64_to_cpu(raw_desc->m0));
	skb = buf_pool->rx_skb[skb_index];
	buf_pool->rx_skb[skb_index] = शून्य;

	datalen = xgene_enet_get_data_len(le64_to_cpu(raw_desc->m1));
	skb_put(skb, datalen);
	prefetch(skb->data - NET_IP_ALIGN);
	skb->protocol = eth_type_trans(skb, ndev);

	/* checking क्रम error */
	status = (GET_VAL(ELERR, le64_to_cpu(raw_desc->m0)) << LERR_LEN) |
		  GET_VAL(LERR, le64_to_cpu(raw_desc->m0));
	अगर (unlikely(status)) अणु
		अगर (xgene_enet_errata_10GE_8(skb, datalen, status)) अणु
			pdata->false_rflr++;
		पूर्ण अन्यथा अगर (xgene_enet_errata_10GE_10(skb, datalen, status)) अणु
			pdata->vlan_rjbr++;
		पूर्ण अन्यथा अणु
			dev_kमुक्त_skb_any(skb);
			xgene_enet_मुक्त_pagepool(page_pool, raw_desc, exp_desc);
			xgene_enet_parse_error(rx_ring, status);
			rx_ring->rx_dropped++;
			जाओ out;
		पूर्ण
	पूर्ण

	nv = GET_VAL(NV, le64_to_cpu(raw_desc->m0));
	अगर (!nv) अणु
		/* strip off CRC as HW isn't करोing this */
		datalen -= 4;
		जाओ skip_jumbo;
	पूर्ण

	slots = page_pool->slots - 1;
	head = page_pool->head;
	desc = (व्योम *)exp_desc;

	क्रम (i = 0; i < 4; i++) अणु
		frag_size = xgene_enet_get_data_len(le64_to_cpu(desc[i ^ 1]));
		अगर (!frag_size)
			अवरोध;

		dma_addr = GET_VAL(DATAADDR, le64_to_cpu(desc[i ^ 1]));
		dma_unmap_page(dev, dma_addr, PAGE_SIZE, DMA_FROM_DEVICE);

		page = page_pool->frag_page[head];
		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page, 0,
				frag_size, PAGE_SIZE);

		datalen += frag_size;

		page_pool->frag_page[head] = शून्य;
		head = (head + 1) & slots;
	पूर्ण

	page_pool->head = head;
	rx_ring->npagepool -= skb_shinfo(skb)->nr_frags;

skip_jumbo:
	skb_checksum_none_निश्चित(skb);
	xgene_enet_rx_csum(skb);

	rx_ring->rx_packets++;
	rx_ring->rx_bytes += datalen;
	napi_gro_receive(&rx_ring->napi, skb);

out:
	अगर (rx_ring->npagepool <= 0) अणु
		ret = xgene_enet_refill_pagepool(page_pool, NUM_NXTBUFPOOL);
		rx_ring->npagepool = NUM_NXTBUFPOOL;
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (--rx_ring->nbufpool == 0) अणु
		ret = xgene_enet_refill_bufpool(buf_pool, NUM_BUFPOOL);
		rx_ring->nbufpool = NUM_BUFPOOL;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool is_rx_desc(काष्ठा xgene_enet_raw_desc *raw_desc)
अणु
	वापस GET_VAL(FPQNUM, le64_to_cpu(raw_desc->m0)) ? true : false;
पूर्ण

अटल पूर्णांक xgene_enet_process_ring(काष्ठा xgene_enet_desc_ring *ring,
				   पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = ring->ndev;
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा xgene_enet_raw_desc *raw_desc, *exp_desc;
	u16 head = ring->head;
	u16 slots = ring->slots - 1;
	पूर्णांक ret, desc_count, count = 0, processed = 0;
	bool is_completion;

	करो अणु
		raw_desc = &ring->raw_desc[head];
		desc_count = 0;
		is_completion = false;
		exp_desc = शून्य;
		अगर (unlikely(xgene_enet_is_desc_slot_empty(raw_desc)))
			अवरोध;

		/* पढ़ो fpqnum field after dataaddr field */
		dma_rmb();
		अगर (GET_BIT(NV, le64_to_cpu(raw_desc->m0))) अणु
			head = (head + 1) & slots;
			exp_desc = &ring->raw_desc[head];

			अगर (unlikely(xgene_enet_is_desc_slot_empty(exp_desc))) अणु
				head = (head - 1) & slots;
				अवरोध;
			पूर्ण
			dma_rmb();
			count++;
			desc_count++;
		पूर्ण
		अगर (is_rx_desc(raw_desc)) अणु
			ret = xgene_enet_rx_frame(ring, raw_desc, exp_desc);
		पूर्ण अन्यथा अणु
			ret = xgene_enet_tx_completion(ring, raw_desc);
			is_completion = true;
		पूर्ण
		xgene_enet_mark_desc_slot_empty(raw_desc);
		अगर (exp_desc)
			xgene_enet_mark_desc_slot_empty(exp_desc);

		head = (head + 1) & slots;
		count++;
		desc_count++;
		processed++;
		अगर (is_completion)
			pdata->txc_level[ring->index] += desc_count;

		अगर (ret)
			अवरोध;
	पूर्ण जबतक (--budget);

	अगर (likely(count)) अणु
		pdata->ring_ops->wr_cmd(ring, -count);
		ring->head = head;

		अगर (__netअगर_subqueue_stopped(ndev, ring->index))
			netअगर_start_subqueue(ndev, ring->index);
	पूर्ण

	वापस processed;
पूर्ण

अटल पूर्णांक xgene_enet_napi(काष्ठा napi_काष्ठा *napi, स्थिर पूर्णांक budget)
अणु
	काष्ठा xgene_enet_desc_ring *ring;
	पूर्णांक processed;

	ring = container_of(napi, काष्ठा xgene_enet_desc_ring, napi);
	processed = xgene_enet_process_ring(ring, budget);

	अगर (processed != budget) अणु
		napi_complete_करोne(napi, processed);
		enable_irq(ring->irq);
	पूर्ण

	वापस processed;
पूर्ण

अटल व्योम xgene_enet_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा netdev_queue *txq;
	पूर्णांक i;

	pdata->mac_ops->reset(pdata);

	क्रम (i = 0; i < pdata->txq_cnt; i++) अणु
		txq = netdev_get_tx_queue(ndev, i);
		txq->trans_start = jअगरfies;
		netअगर_tx_start_queue(txq);
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_set_irq_name(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा xgene_enet_desc_ring *ring;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		ring = pdata->rx_ring[i];
		अगर (!pdata->cq_cnt) अणु
			snम_लिखो(ring->irq_name, IRQ_ID_SIZE, "%s-rx-txc",
				 ndev->name);
		पूर्ण अन्यथा अणु
			snम_लिखो(ring->irq_name, IRQ_ID_SIZE, "%s-rx-%d",
				 ndev->name, i);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pdata->cq_cnt; i++) अणु
		ring = pdata->tx_ring[i]->cp_ring;
		snम_लिखो(ring->irq_name, IRQ_ID_SIZE, "%s-txc-%d",
			 ndev->name, i);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_enet_रेजिस्टर_irq(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = ndev_to_dev(ndev);
	काष्ठा xgene_enet_desc_ring *ring;
	पूर्णांक ret = 0, i;

	xgene_enet_set_irq_name(ndev);
	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		ring = pdata->rx_ring[i];
		irq_set_status_flags(ring->irq, IRQ_DISABLE_UNLAZY);
		ret = devm_request_irq(dev, ring->irq, xgene_enet_rx_irq,
				       0, ring->irq_name, ring);
		अगर (ret) अणु
			netdev_err(ndev, "Failed to request irq %s\n",
				   ring->irq_name);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pdata->cq_cnt; i++) अणु
		ring = pdata->tx_ring[i]->cp_ring;
		irq_set_status_flags(ring->irq, IRQ_DISABLE_UNLAZY);
		ret = devm_request_irq(dev, ring->irq, xgene_enet_rx_irq,
				       0, ring->irq_name, ring);
		अगर (ret) अणु
			netdev_err(ndev, "Failed to request irq %s\n",
				   ring->irq_name);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xgene_enet_मुक्त_irq(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा xgene_enet_desc_ring *ring;
	काष्ठा device *dev;
	पूर्णांक i;

	pdata = netdev_priv(ndev);
	dev = ndev_to_dev(ndev);

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		ring = pdata->rx_ring[i];
		irq_clear_status_flags(ring->irq, IRQ_DISABLE_UNLAZY);
		devm_मुक्त_irq(dev, ring->irq, ring);
	पूर्ण

	क्रम (i = 0; i < pdata->cq_cnt; i++) अणु
		ring = pdata->tx_ring[i]->cp_ring;
		irq_clear_status_flags(ring->irq, IRQ_DISABLE_UNLAZY);
		devm_मुक्त_irq(dev, ring->irq, ring);
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_napi_enable(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा napi_काष्ठा *napi;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		napi = &pdata->rx_ring[i]->napi;
		napi_enable(napi);
	पूर्ण

	क्रम (i = 0; i < pdata->cq_cnt; i++) अणु
		napi = &pdata->tx_ring[i]->cp_ring->napi;
		napi_enable(napi);
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_napi_disable(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा napi_काष्ठा *napi;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		napi = &pdata->rx_ring[i]->napi;
		napi_disable(napi);
	पूर्ण

	क्रम (i = 0; i < pdata->cq_cnt; i++) अणु
		napi = &pdata->tx_ring[i]->cp_ring->napi;
		napi_disable(napi);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_enet_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	स्थिर काष्ठा xgene_mac_ops *mac_ops = pdata->mac_ops;
	पूर्णांक ret;

	ret = netअगर_set_real_num_tx_queues(ndev, pdata->txq_cnt);
	अगर (ret)
		वापस ret;

	ret = netअगर_set_real_num_rx_queues(ndev, pdata->rxq_cnt);
	अगर (ret)
		वापस ret;

	xgene_enet_napi_enable(pdata);
	ret = xgene_enet_रेजिस्टर_irq(ndev);
	अगर (ret)
		वापस ret;

	अगर (ndev->phydev) अणु
		phy_start(ndev->phydev);
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&pdata->link_work, PHY_POLL_LINK_OFF);
		netअगर_carrier_off(ndev);
	पूर्ण

	mac_ops->tx_enable(pdata);
	mac_ops->rx_enable(pdata);
	netअगर_tx_start_all_queues(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_enet_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	स्थिर काष्ठा xgene_mac_ops *mac_ops = pdata->mac_ops;
	पूर्णांक i;

	netअगर_tx_stop_all_queues(ndev);
	mac_ops->tx_disable(pdata);
	mac_ops->rx_disable(pdata);

	अगर (ndev->phydev)
		phy_stop(ndev->phydev);
	अन्यथा
		cancel_delayed_work_sync(&pdata->link_work);

	xgene_enet_मुक्त_irq(ndev);
	xgene_enet_napi_disable(pdata);
	क्रम (i = 0; i < pdata->rxq_cnt; i++)
		xgene_enet_process_ring(pdata->rx_ring[i], -1);

	वापस 0;
पूर्ण
अटल व्योम xgene_enet_delete_ring(काष्ठा xgene_enet_desc_ring *ring)
अणु
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा device *dev;

	pdata = netdev_priv(ring->ndev);
	dev = ndev_to_dev(ring->ndev);

	pdata->ring_ops->clear(ring);
	dmam_मुक्त_coherent(dev, ring->size, ring->desc_addr, ring->dma);
पूर्ण

अटल व्योम xgene_enet_delete_desc_rings(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा xgene_enet_desc_ring *buf_pool, *page_pool;
	काष्ठा xgene_enet_desc_ring *ring;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->txq_cnt; i++) अणु
		ring = pdata->tx_ring[i];
		अगर (ring) अणु
			xgene_enet_delete_ring(ring);
			pdata->port_ops->clear(pdata, ring);
			अगर (pdata->cq_cnt)
				xgene_enet_delete_ring(ring->cp_ring);
			pdata->tx_ring[i] = शून्य;
		पूर्ण

	पूर्ण

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		ring = pdata->rx_ring[i];
		अगर (ring) अणु
			page_pool = ring->page_pool;
			अगर (page_pool) अणु
				xgene_enet_delete_pagepool(page_pool);
				xgene_enet_delete_ring(page_pool);
				pdata->port_ops->clear(pdata, page_pool);
			पूर्ण

			buf_pool = ring->buf_pool;
			xgene_enet_delete_bufpool(buf_pool);
			xgene_enet_delete_ring(buf_pool);
			pdata->port_ops->clear(pdata, buf_pool);

			xgene_enet_delete_ring(ring);
			pdata->rx_ring[i] = शून्य;
		पूर्ण

	पूर्ण
पूर्ण

अटल पूर्णांक xgene_enet_get_ring_size(काष्ठा device *dev,
				    क्रमागत xgene_enet_ring_cfgsize cfgsize)
अणु
	पूर्णांक size = -EINVAL;

	चयन (cfgsize) अणु
	हाल RING_CFGSIZE_512B:
		size = 0x200;
		अवरोध;
	हाल RING_CFGSIZE_2KB:
		size = 0x800;
		अवरोध;
	हाल RING_CFGSIZE_16KB:
		size = 0x4000;
		अवरोध;
	हाल RING_CFGSIZE_64KB:
		size = 0x10000;
		अवरोध;
	हाल RING_CFGSIZE_512KB:
		size = 0x80000;
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported cfg ring size %d\n", cfgsize);
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम xgene_enet_मुक्त_desc_ring(काष्ठा xgene_enet_desc_ring *ring)
अणु
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा device *dev;

	अगर (!ring)
		वापस;

	dev = ndev_to_dev(ring->ndev);
	pdata = netdev_priv(ring->ndev);

	अगर (ring->desc_addr) अणु
		pdata->ring_ops->clear(ring);
		dmam_मुक्त_coherent(dev, ring->size, ring->desc_addr, ring->dma);
	पूर्ण
	devm_kमुक्त(dev, ring);
पूर्ण

अटल व्योम xgene_enet_मुक्त_desc_rings(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा xgene_enet_desc_ring *page_pool;
	काष्ठा device *dev = &pdata->pdev->dev;
	काष्ठा xgene_enet_desc_ring *ring;
	व्योम *p;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->txq_cnt; i++) अणु
		ring = pdata->tx_ring[i];
		अगर (ring) अणु
			अगर (ring->cp_ring && ring->cp_ring->cp_skb)
				devm_kमुक्त(dev, ring->cp_ring->cp_skb);

			अगर (ring->cp_ring && pdata->cq_cnt)
				xgene_enet_मुक्त_desc_ring(ring->cp_ring);

			xgene_enet_मुक्त_desc_ring(ring);
		पूर्ण

	पूर्ण

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		ring = pdata->rx_ring[i];
		अगर (ring) अणु
			अगर (ring->buf_pool) अणु
				अगर (ring->buf_pool->rx_skb)
					devm_kमुक्त(dev, ring->buf_pool->rx_skb);

				xgene_enet_मुक्त_desc_ring(ring->buf_pool);
			पूर्ण

			page_pool = ring->page_pool;
			अगर (page_pool) अणु
				p = page_pool->frag_page;
				अगर (p)
					devm_kमुक्त(dev, p);

				p = page_pool->frag_dma_addr;
				अगर (p)
					devm_kमुक्त(dev, p);
			पूर्ण

			xgene_enet_मुक्त_desc_ring(ring);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool is_irq_mbox_required(काष्ठा xgene_enet_pdata *pdata,
				 काष्ठा xgene_enet_desc_ring *ring)
अणु
	अगर ((pdata->enet_id == XGENE_ENET2) &&
	    (xgene_enet_ring_owner(ring->id) == RING_OWNER_CPU)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम __iomem *xgene_enet_ring_cmd_base(काष्ठा xgene_enet_pdata *pdata,
					      काष्ठा xgene_enet_desc_ring *ring)
अणु
	u8 num_ring_id_shअगरt = pdata->ring_ops->num_ring_id_shअगरt;

	वापस pdata->ring_cmd_addr + (ring->num << num_ring_id_shअगरt);
पूर्ण

अटल काष्ठा xgene_enet_desc_ring *xgene_enet_create_desc_ring(
			काष्ठा net_device *ndev, u32 ring_num,
			क्रमागत xgene_enet_ring_cfgsize cfgsize, u32 ring_id)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा device *dev = ndev_to_dev(ndev);
	काष्ठा xgene_enet_desc_ring *ring;
	व्योम *irq_mbox_addr;
	पूर्णांक size;

	size = xgene_enet_get_ring_size(dev, cfgsize);
	अगर (size < 0)
		वापस शून्य;

	ring = devm_kzalloc(dev, माप(काष्ठा xgene_enet_desc_ring),
			    GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	ring->ndev = ndev;
	ring->num = ring_num;
	ring->cfgsize = cfgsize;
	ring->id = ring_id;

	ring->desc_addr = dmam_alloc_coherent(dev, size, &ring->dma,
					      GFP_KERNEL | __GFP_ZERO);
	अगर (!ring->desc_addr) अणु
		devm_kमुक्त(dev, ring);
		वापस शून्य;
	पूर्ण
	ring->size = size;

	अगर (is_irq_mbox_required(pdata, ring)) अणु
		irq_mbox_addr = dmam_alloc_coherent(dev, INTR_MBOX_SIZE,
						    &ring->irq_mbox_dma,
						    GFP_KERNEL | __GFP_ZERO);
		अगर (!irq_mbox_addr) अणु
			dmam_मुक्त_coherent(dev, size, ring->desc_addr,
					   ring->dma);
			devm_kमुक्त(dev, ring);
			वापस शून्य;
		पूर्ण
		ring->irq_mbox_addr = irq_mbox_addr;
	पूर्ण

	ring->cmd_base = xgene_enet_ring_cmd_base(pdata, ring);
	ring->cmd = ring->cmd_base + INC_DEC_CMD_ADDR;
	ring = pdata->ring_ops->setup(ring);
	netdev_dbg(ndev, "ring info: num=%d  size=%d  id=%d  slots=%d\n",
		   ring->num, ring->size, ring->id, ring->slots);

	वापस ring;
पूर्ण

अटल u16 xgene_enet_get_ring_id(क्रमागत xgene_ring_owner owner, u8 bufnum)
अणु
	वापस (owner << 6) | (bufnum & GENMASK(5, 0));
पूर्ण

अटल क्रमागत xgene_ring_owner xgene_derive_ring_owner(काष्ठा xgene_enet_pdata *p)
अणु
	क्रमागत xgene_ring_owner owner;

	अगर (p->enet_id == XGENE_ENET1) अणु
		चयन (p->phy_mode) अणु
		हाल PHY_INTERFACE_MODE_SGMII:
			owner = RING_OWNER_ETH0;
			अवरोध;
		शेष:
			owner = (!p->port_id) ? RING_OWNER_ETH0 :
						RING_OWNER_ETH1;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		owner = (!p->port_id) ? RING_OWNER_ETH0 : RING_OWNER_ETH1;
	पूर्ण

	वापस owner;
पूर्ण

अटल u8 xgene_start_cpu_bufnum(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;
	u32 cpu_bufnum;
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, "channel", &cpu_bufnum);

	वापस (!ret) ? cpu_bufnum : pdata->cpu_bufnum;
पूर्ण

अटल पूर्णांक xgene_enet_create_desc_rings(काष्ठा net_device *ndev)
अणु
	काष्ठा xgene_enet_desc_ring *rx_ring, *tx_ring, *cp_ring;
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा xgene_enet_desc_ring *page_pool = शून्य;
	काष्ठा xgene_enet_desc_ring *buf_pool = शून्य;
	काष्ठा device *dev = ndev_to_dev(ndev);
	u8 eth_bufnum = pdata->eth_bufnum;
	u8 bp_bufnum = pdata->bp_bufnum;
	u16 ring_num = pdata->ring_num;
	क्रमागत xgene_ring_owner owner;
	dma_addr_t dma_exp_bufs;
	u16 ring_id, slots;
	__le64 *exp_bufs;
	पूर्णांक i, ret, size;
	u8 cpu_bufnum;

	cpu_bufnum = xgene_start_cpu_bufnum(pdata);

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		/* allocate rx descriptor ring */
		owner = xgene_derive_ring_owner(pdata);
		ring_id = xgene_enet_get_ring_id(RING_OWNER_CPU, cpu_bufnum++);
		rx_ring = xgene_enet_create_desc_ring(ndev, ring_num++,
						      RING_CFGSIZE_16KB,
						      ring_id);
		अगर (!rx_ring) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		/* allocate buffer pool क्रम receiving packets */
		owner = xgene_derive_ring_owner(pdata);
		ring_id = xgene_enet_get_ring_id(owner, bp_bufnum++);
		buf_pool = xgene_enet_create_desc_ring(ndev, ring_num++,
						       RING_CFGSIZE_16KB,
						       ring_id);
		अगर (!buf_pool) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		rx_ring->nbufpool = NUM_BUFPOOL;
		rx_ring->npagepool = NUM_NXTBUFPOOL;
		rx_ring->irq = pdata->irqs[i];
		buf_pool->rx_skb = devm_kसुस्मृति(dev, buf_pool->slots,
						माप(काष्ठा sk_buff *),
						GFP_KERNEL);
		अगर (!buf_pool->rx_skb) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		buf_pool->dst_ring_num = xgene_enet_dst_ring_num(buf_pool);
		rx_ring->buf_pool = buf_pool;
		pdata->rx_ring[i] = rx_ring;

		अगर ((pdata->enet_id == XGENE_ENET1 &&  pdata->rxq_cnt > 4) ||
		    (pdata->enet_id == XGENE_ENET2 &&  pdata->rxq_cnt > 16)) अणु
			अवरोध;
		पूर्ण

		/* allocate next buffer pool क्रम jumbo packets */
		owner = xgene_derive_ring_owner(pdata);
		ring_id = xgene_enet_get_ring_id(owner, bp_bufnum++);
		page_pool = xgene_enet_create_desc_ring(ndev, ring_num++,
							RING_CFGSIZE_16KB,
							ring_id);
		अगर (!page_pool) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		slots = page_pool->slots;
		page_pool->frag_page = devm_kसुस्मृति(dev, slots,
						    माप(काष्ठा page *),
						    GFP_KERNEL);
		अगर (!page_pool->frag_page) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		page_pool->frag_dma_addr = devm_kसुस्मृति(dev, slots,
							माप(dma_addr_t),
							GFP_KERNEL);
		अगर (!page_pool->frag_dma_addr) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		page_pool->dst_ring_num = xgene_enet_dst_ring_num(page_pool);
		rx_ring->page_pool = page_pool;
	पूर्ण

	क्रम (i = 0; i < pdata->txq_cnt; i++) अणु
		/* allocate tx descriptor ring */
		owner = xgene_derive_ring_owner(pdata);
		ring_id = xgene_enet_get_ring_id(owner, eth_bufnum++);
		tx_ring = xgene_enet_create_desc_ring(ndev, ring_num++,
						      RING_CFGSIZE_16KB,
						      ring_id);
		अगर (!tx_ring) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		size = (tx_ring->slots / 2) * माप(__le64) * MAX_EXP_BUFFS;
		exp_bufs = dmam_alloc_coherent(dev, size, &dma_exp_bufs,
					       GFP_KERNEL | __GFP_ZERO);
		अगर (!exp_bufs) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		tx_ring->exp_bufs = exp_bufs;

		pdata->tx_ring[i] = tx_ring;

		अगर (!pdata->cq_cnt) अणु
			cp_ring = pdata->rx_ring[i];
		पूर्ण अन्यथा अणु
			/* allocate tx completion descriptor ring */
			ring_id = xgene_enet_get_ring_id(RING_OWNER_CPU,
							 cpu_bufnum++);
			cp_ring = xgene_enet_create_desc_ring(ndev, ring_num++,
							      RING_CFGSIZE_16KB,
							      ring_id);
			अगर (!cp_ring) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण

			cp_ring->irq = pdata->irqs[pdata->rxq_cnt + i];
			cp_ring->index = i;
		पूर्ण

		cp_ring->cp_skb = devm_kसुस्मृति(dev, tx_ring->slots,
					       माप(काष्ठा sk_buff *),
					       GFP_KERNEL);
		अगर (!cp_ring->cp_skb) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		size = माप(dma_addr_t) * MAX_SKB_FRAGS;
		cp_ring->frag_dma_addr = devm_kसुस्मृति(dev, tx_ring->slots,
						      size, GFP_KERNEL);
		अगर (!cp_ring->frag_dma_addr) अणु
			devm_kमुक्त(dev, cp_ring->cp_skb);
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		tx_ring->cp_ring = cp_ring;
		tx_ring->dst_ring_num = xgene_enet_dst_ring_num(cp_ring);
	पूर्ण

	अगर (pdata->ring_ops->coalesce)
		pdata->ring_ops->coalesce(pdata->tx_ring[0]);
	pdata->tx_qcnt_hi = pdata->tx_ring[0]->slots - 128;

	वापस 0;

err:
	xgene_enet_मुक्त_desc_rings(pdata);
	वापस ret;
पूर्ण

अटल व्योम xgene_enet_get_stats64(
			काष्ठा net_device *ndev,
			काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	काष्ठा xgene_enet_desc_ring *ring;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->txq_cnt; i++) अणु
		ring = pdata->tx_ring[i];
		अगर (ring) अणु
			stats->tx_packets += ring->tx_packets;
			stats->tx_bytes += ring->tx_bytes;
			stats->tx_dropped += ring->tx_dropped;
			stats->tx_errors += ring->tx_errors;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		ring = pdata->rx_ring[i];
		अगर (ring) अणु
			stats->rx_packets += ring->rx_packets;
			stats->rx_bytes += ring->rx_bytes;
			stats->rx_dropped += ring->rx_dropped;
			stats->rx_errors += ring->rx_errors +
				ring->rx_length_errors +
				ring->rx_crc_errors +
				ring->rx_frame_errors +
				ring->rx_fअगरo_errors;
			stats->rx_length_errors += ring->rx_length_errors;
			stats->rx_crc_errors += ring->rx_crc_errors;
			stats->rx_frame_errors += ring->rx_frame_errors;
			stats->rx_fअगरo_errors += ring->rx_fअगरo_errors;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_enet_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	पूर्णांक ret;

	ret = eth_mac_addr(ndev, addr);
	अगर (ret)
		वापस ret;
	pdata->mac_ops->set_mac_addr(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा xgene_enet_pdata *pdata = netdev_priv(ndev);
	पूर्णांक frame_size;

	अगर (!netअगर_running(ndev))
		वापस 0;

	frame_size = (new_mtu > ETH_DATA_LEN) ? (new_mtu + 18) : 0x600;

	xgene_enet_बंद(ndev);
	ndev->mtu = new_mtu;
	pdata->mac_ops->set_framesize(pdata, frame_size);
	xgene_enet_खोलो(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xgene_ndev_ops = अणु
	.nकरो_खोलो = xgene_enet_खोलो,
	.nकरो_stop = xgene_enet_बंद,
	.nकरो_start_xmit = xgene_enet_start_xmit,
	.nकरो_tx_समयout = xgene_enet_समयout,
	.nकरो_get_stats64 = xgene_enet_get_stats64,
	.nकरो_change_mtu = xgene_change_mtu,
	.nकरो_set_mac_address = xgene_enet_set_mac_address,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल व्योम xgene_get_port_id_acpi(काष्ठा device *dev,
				  काष्ठा xgene_enet_pdata *pdata)
अणु
	acpi_status status;
	u64 temp;

	status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(dev), "_SUN", शून्य, &temp);
	अगर (ACPI_FAILURE(status)) अणु
		pdata->port_id = 0;
	पूर्ण अन्यथा अणु
		pdata->port_id = temp;
	पूर्ण

	वापस;
पूर्ण
#पूर्ण_अगर

अटल व्योम xgene_get_port_id_dt(काष्ठा device *dev, काष्ठा xgene_enet_pdata *pdata)
अणु
	u32 id = 0;

	of_property_पढ़ो_u32(dev->of_node, "port-id", &id);

	pdata->port_id = id & BIT(0);

	वापस;
पूर्ण

अटल पूर्णांक xgene_get_tx_delay(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;
	पूर्णांक delay, ret;

	ret = device_property_पढ़ो_u32(dev, "tx-delay", &delay);
	अगर (ret) अणु
		pdata->tx_delay = 4;
		वापस 0;
	पूर्ण

	अगर (delay < 0 || delay > 7) अणु
		dev_err(dev, "Invalid tx-delay specified\n");
		वापस -EINVAL;
	पूर्ण

	pdata->tx_delay = delay;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_get_rx_delay(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;
	पूर्णांक delay, ret;

	ret = device_property_पढ़ो_u32(dev, "rx-delay", &delay);
	अगर (ret) अणु
		pdata->rx_delay = 2;
		वापस 0;
	पूर्ण

	अगर (delay < 0 || delay > 7) अणु
		dev_err(dev, "Invalid rx-delay specified\n");
		वापस -EINVAL;
	पूर्ण

	pdata->rx_delay = delay;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_enet_get_irqs(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा platक्रमm_device *pdev = pdata->pdev;
	पूर्णांक i, ret, max_irqs;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode))
		max_irqs = 1;
	अन्यथा अगर (pdata->phy_mode == PHY_INTERFACE_MODE_SGMII)
		max_irqs = 2;
	अन्यथा
		max_irqs = XGENE_MAX_ENET_IRQ;

	क्रम (i = 0; i < max_irqs; i++) अणु
		ret = platक्रमm_get_irq(pdev, i);
		अगर (ret <= 0) अणु
			अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) अणु
				max_irqs = i;
				pdata->rxq_cnt = max_irqs / 2;
				pdata->txq_cnt = max_irqs / 2;
				pdata->cq_cnt = max_irqs / 2;
				अवरोध;
			पूर्ण
			वापस ret ? : -ENXIO;
		पूर्ण
		pdata->irqs[i] = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_enet_check_phy_handle(काष्ठा xgene_enet_pdata *pdata)
अणु
	पूर्णांक ret;

	अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII)
		वापस;

	अगर (!IS_ENABLED(CONFIG_MDIO_XGENE))
		वापस;

	ret = xgene_enet_phy_connect(pdata->ndev);
	अगर (!ret)
		pdata->mdio_driver = true;
पूर्ण

अटल व्योम xgene_enet_gpiod_get(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा device *dev = &pdata->pdev->dev;

	pdata->sfp_gpio_en = false;
	अगर (pdata->phy_mode != PHY_INTERFACE_MODE_XGMII ||
	    (!device_property_present(dev, "sfp-gpios") &&
	     !device_property_present(dev, "rxlos-gpios")))
		वापस;

	pdata->sfp_gpio_en = true;
	pdata->sfp_rdy = gpiod_get(dev, "rxlos", GPIOD_IN);
	अगर (IS_ERR(pdata->sfp_rdy))
		pdata->sfp_rdy = gpiod_get(dev, "sfp", GPIOD_IN);
पूर्ण

अटल पूर्णांक xgene_enet_get_resources(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा net_device *ndev;
	काष्ठा device *dev;
	काष्ठा resource *res;
	व्योम __iomem *base_addr;
	u32 offset;
	पूर्णांक ret = 0;

	pdev = pdata->pdev;
	dev = &pdev->dev;
	ndev = pdata->ndev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, RES_ENET_CSR);
	अगर (!res) अणु
		dev_err(dev, "Resource enet_csr not defined\n");
		वापस -ENODEV;
	पूर्ण
	pdata->base_addr = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!pdata->base_addr) अणु
		dev_err(dev, "Unable to retrieve ENET Port CSR region\n");
		वापस -ENOMEM;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, RES_RING_CSR);
	अगर (!res) अणु
		dev_err(dev, "Resource ring_csr not defined\n");
		वापस -ENODEV;
	पूर्ण
	pdata->ring_csr_addr = devm_ioremap(dev, res->start,
							resource_size(res));
	अगर (!pdata->ring_csr_addr) अणु
		dev_err(dev, "Unable to retrieve ENET Ring CSR region\n");
		वापस -ENOMEM;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, RES_RING_CMD);
	अगर (!res) अणु
		dev_err(dev, "Resource ring_cmd not defined\n");
		वापस -ENODEV;
	पूर्ण
	pdata->ring_cmd_addr = devm_ioremap(dev, res->start,
							resource_size(res));
	अगर (!pdata->ring_cmd_addr) अणु
		dev_err(dev, "Unable to retrieve ENET Ring command region\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (dev->of_node)
		xgene_get_port_id_dt(dev, pdata);
#अगर_घोषित CONFIG_ACPI
	अन्यथा
		xgene_get_port_id_acpi(dev, pdata);
#पूर्ण_अगर

	अगर (!device_get_mac_address(dev, ndev->dev_addr, ETH_ALEN))
		eth_hw_addr_अक्रमom(ndev);

	स_नकल(ndev->perm_addr, ndev->dev_addr, ndev->addr_len);

	pdata->phy_mode = device_get_phy_mode(dev);
	अगर (pdata->phy_mode < 0) अणु
		dev_err(dev, "Unable to get phy-connection-type\n");
		वापस pdata->phy_mode;
	पूर्ण
	अगर (!phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode) &&
	    pdata->phy_mode != PHY_INTERFACE_MODE_SGMII &&
	    pdata->phy_mode != PHY_INTERFACE_MODE_XGMII) अणु
		dev_err(dev, "Incorrect phy-connection-type specified\n");
		वापस -ENODEV;
	पूर्ण

	ret = xgene_get_tx_delay(pdata);
	अगर (ret)
		वापस ret;

	ret = xgene_get_rx_delay(pdata);
	अगर (ret)
		वापस ret;

	ret = xgene_enet_get_irqs(pdata);
	अगर (ret)
		वापस ret;

	xgene_enet_gpiod_get(pdata);

	pdata->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pdata->clk)) अणु
		अगर (pdata->phy_mode != PHY_INTERFACE_MODE_SGMII) अणु
			/* Abort अगर the घड़ी is defined but couldn't be
			 * retrived. Always पात अगर the घड़ी is missing on
			 * DT प्रणाली as the driver can't cope with this हाल.
			 */
			अगर (PTR_ERR(pdata->clk) != -ENOENT || dev->of_node)
				वापस PTR_ERR(pdata->clk);
			/* Firmware may have set up the घड़ी alपढ़ोy. */
			dev_info(dev, "clocks have been setup already\n");
		पूर्ण
	पूर्ण

	अगर (pdata->phy_mode != PHY_INTERFACE_MODE_XGMII)
		base_addr = pdata->base_addr - (pdata->port_id * MAC_OFFSET);
	अन्यथा
		base_addr = pdata->base_addr;
	pdata->eth_csr_addr = base_addr + BLOCK_ETH_CSR_OFFSET;
	pdata->cle.base = base_addr + BLOCK_ETH_CLE_CSR_OFFSET;
	pdata->eth_ring_अगर_addr = base_addr + BLOCK_ETH_RING_IF_OFFSET;
	pdata->eth_diag_csr_addr = base_addr + BLOCK_ETH_DIAG_CSR_OFFSET;
	अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode) ||
	    pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) अणु
		pdata->mcx_mac_addr = pdata->base_addr + BLOCK_ETH_MAC_OFFSET;
		pdata->mcx_stats_addr =
			pdata->base_addr + BLOCK_ETH_STATS_OFFSET;
		offset = (pdata->enet_id == XGENE_ENET1) ?
			  BLOCK_ETH_MAC_CSR_OFFSET :
			  X2_BLOCK_ETH_MAC_CSR_OFFSET;
		pdata->mcx_mac_csr_addr = base_addr + offset;
	पूर्ण अन्यथा अणु
		pdata->mcx_mac_addr = base_addr + BLOCK_AXG_MAC_OFFSET;
		pdata->mcx_stats_addr = base_addr + BLOCK_AXG_STATS_OFFSET;
		pdata->mcx_mac_csr_addr = base_addr + BLOCK_AXG_MAC_CSR_OFFSET;
		pdata->pcs_addr = base_addr + BLOCK_PCS_OFFSET;
	पूर्ण
	pdata->rx_buff_cnt = NUM_PKT_BUF;

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_enet_init_hw(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा xgene_enet_cle *enet_cle = &pdata->cle;
	काष्ठा xgene_enet_desc_ring *page_pool;
	काष्ठा net_device *ndev = pdata->ndev;
	काष्ठा xgene_enet_desc_ring *buf_pool;
	u16 dst_ring_num, ring_id;
	पूर्णांक i, ret;
	u32 count;

	ret = pdata->port_ops->reset(pdata);
	अगर (ret)
		वापस ret;

	ret = xgene_enet_create_desc_rings(ndev);
	अगर (ret) अणु
		netdev_err(ndev, "Error in ring configuration\n");
		वापस ret;
	पूर्ण

	/* setup buffer pool */
	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		buf_pool = pdata->rx_ring[i]->buf_pool;
		xgene_enet_init_bufpool(buf_pool);
		page_pool = pdata->rx_ring[i]->page_pool;
		xgene_enet_init_bufpool(page_pool);

		count = pdata->rx_buff_cnt;
		ret = xgene_enet_refill_bufpool(buf_pool, count);
		अगर (ret)
			जाओ err;

		ret = xgene_enet_refill_pagepool(page_pool, count);
		अगर (ret)
			जाओ err;

	पूर्ण

	dst_ring_num = xgene_enet_dst_ring_num(pdata->rx_ring[0]);
	buf_pool = pdata->rx_ring[0]->buf_pool;
	अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) अणु
		/* Initialize and Enable  PreClassअगरier Tree */
		enet_cle->max_nodes = 512;
		enet_cle->max_dbptrs = 1024;
		enet_cle->parsers = 3;
		enet_cle->active_parser = PARSER_ALL;
		enet_cle->ptree.start_node = 0;
		enet_cle->ptree.start_dbptr = 0;
		enet_cle->jump_bytes = 8;
		ret = pdata->cle_ops->cle_init(pdata);
		अगर (ret) अणु
			netdev_err(ndev, "Preclass Tree init error\n");
			जाओ err;
		पूर्ण

	पूर्ण अन्यथा अणु
		dst_ring_num = xgene_enet_dst_ring_num(pdata->rx_ring[0]);
		buf_pool = pdata->rx_ring[0]->buf_pool;
		page_pool = pdata->rx_ring[0]->page_pool;
		ring_id = (page_pool) ? page_pool->id : 0;
		pdata->port_ops->cle_bypass(pdata, dst_ring_num,
					    buf_pool->id, ring_id);
	पूर्ण

	ndev->max_mtu = XGENE_ENET_MAX_MTU;
	pdata->phy_speed = SPEED_UNKNOWN;
	pdata->mac_ops->init(pdata);

	वापस ret;

err:
	xgene_enet_delete_desc_rings(pdata);
	वापस ret;
पूर्ण

अटल व्योम xgene_enet_setup_ops(काष्ठा xgene_enet_pdata *pdata)
अणु
	चयन (pdata->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		pdata->mac_ops = &xgene_gmac_ops;
		pdata->port_ops = &xgene_gport_ops;
		pdata->rm = RM3;
		pdata->rxq_cnt = 1;
		pdata->txq_cnt = 1;
		pdata->cq_cnt = 0;
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
		pdata->mac_ops = &xgene_sgmac_ops;
		pdata->port_ops = &xgene_sgport_ops;
		pdata->rm = RM1;
		pdata->rxq_cnt = 1;
		pdata->txq_cnt = 1;
		pdata->cq_cnt = 1;
		अवरोध;
	शेष:
		pdata->mac_ops = &xgene_xgmac_ops;
		pdata->port_ops = &xgene_xgport_ops;
		pdata->cle_ops = &xgene_cle3in_ops;
		pdata->rm = RM0;
		अगर (!pdata->rxq_cnt) अणु
			pdata->rxq_cnt = XGENE_NUM_RX_RING;
			pdata->txq_cnt = XGENE_NUM_TX_RING;
			pdata->cq_cnt = XGENE_NUM_TXC_RING;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (pdata->enet_id == XGENE_ENET1) अणु
		चयन (pdata->port_id) अणु
		हाल 0:
			अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) अणु
				pdata->cpu_bufnum = X2_START_CPU_BUFNUM_0;
				pdata->eth_bufnum = X2_START_ETH_BUFNUM_0;
				pdata->bp_bufnum = X2_START_BP_BUFNUM_0;
				pdata->ring_num = START_RING_NUM_0;
			पूर्ण अन्यथा अणु
				pdata->cpu_bufnum = START_CPU_BUFNUM_0;
				pdata->eth_bufnum = START_ETH_BUFNUM_0;
				pdata->bp_bufnum = START_BP_BUFNUM_0;
				pdata->ring_num = START_RING_NUM_0;
			पूर्ण
			अवरोध;
		हाल 1:
			अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) अणु
				pdata->cpu_bufnum = XG_START_CPU_BUFNUM_1;
				pdata->eth_bufnum = XG_START_ETH_BUFNUM_1;
				pdata->bp_bufnum = XG_START_BP_BUFNUM_1;
				pdata->ring_num = XG_START_RING_NUM_1;
			पूर्ण अन्यथा अणु
				pdata->cpu_bufnum = START_CPU_BUFNUM_1;
				pdata->eth_bufnum = START_ETH_BUFNUM_1;
				pdata->bp_bufnum = START_BP_BUFNUM_1;
				pdata->ring_num = START_RING_NUM_1;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		pdata->ring_ops = &xgene_ring1_ops;
	पूर्ण अन्यथा अणु
		चयन (pdata->port_id) अणु
		हाल 0:
			pdata->cpu_bufnum = X2_START_CPU_BUFNUM_0;
			pdata->eth_bufnum = X2_START_ETH_BUFNUM_0;
			pdata->bp_bufnum = X2_START_BP_BUFNUM_0;
			pdata->ring_num = X2_START_RING_NUM_0;
			अवरोध;
		हाल 1:
			pdata->cpu_bufnum = X2_START_CPU_BUFNUM_1;
			pdata->eth_bufnum = X2_START_ETH_BUFNUM_1;
			pdata->bp_bufnum = X2_START_BP_BUFNUM_1;
			pdata->ring_num = X2_START_RING_NUM_1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		pdata->rm = RM0;
		pdata->ring_ops = &xgene_ring2_ops;
	पूर्ण
पूर्ण

अटल व्योम xgene_enet_napi_add(काष्ठा xgene_enet_pdata *pdata)
अणु
	काष्ठा napi_काष्ठा *napi;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->rxq_cnt; i++) अणु
		napi = &pdata->rx_ring[i]->napi;
		netअगर_napi_add(pdata->ndev, napi, xgene_enet_napi,
			       NAPI_POLL_WEIGHT);
	पूर्ण

	क्रम (i = 0; i < pdata->cq_cnt; i++) अणु
		napi = &pdata->tx_ring[i]->cp_ring->napi;
		netअगर_napi_add(pdata->ndev, napi, xgene_enet_napi,
			       NAPI_POLL_WEIGHT);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_enet_acpi_match[] = अणु
	अणु "APMC0D05", XGENE_ENET1पूर्ण,
	अणु "APMC0D30", XGENE_ENET1पूर्ण,
	अणु "APMC0D31", XGENE_ENET1पूर्ण,
	अणु "APMC0D3F", XGENE_ENET1पूर्ण,
	अणु "APMC0D26", XGENE_ENET2पूर्ण,
	अणु "APMC0D25", XGENE_ENET2पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_enet_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id xgene_enet_of_match[] = अणु
	अणु.compatible = "apm,xgene-enet",    .data = (व्योम *)XGENE_ENET1पूर्ण,
	अणु.compatible = "apm,xgene1-sgenet", .data = (व्योम *)XGENE_ENET1पूर्ण,
	अणु.compatible = "apm,xgene1-xgenet", .data = (व्योम *)XGENE_ENET1पूर्ण,
	अणु.compatible = "apm,xgene2-sgenet", .data = (व्योम *)XGENE_ENET2पूर्ण,
	अणु.compatible = "apm,xgene2-xgenet", .data = (व्योम *)XGENE_ENET2पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, xgene_enet_of_match);

अटल पूर्णांक xgene_enet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev;
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा device *dev = &pdev->dev;
	व्योम (*link_state)(काष्ठा work_काष्ठा *);
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक ret;

	ndev = alloc_etherdev_mqs(माप(काष्ठा xgene_enet_pdata),
				  XGENE_NUM_TX_RING, XGENE_NUM_RX_RING);
	अगर (!ndev)
		वापस -ENOMEM;

	pdata = netdev_priv(ndev);

	pdata->pdev = pdev;
	pdata->ndev = ndev;
	SET_NETDEV_DEV(ndev, dev);
	platक्रमm_set_drvdata(pdev, pdata);
	ndev->netdev_ops = &xgene_ndev_ops;
	xgene_enet_set_ethtool_ops(ndev);
	ndev->features |= NETIF_F_IP_CSUM |
			  NETIF_F_GSO |
			  NETIF_F_GRO |
			  NETIF_F_SG;

	of_id = of_match_device(xgene_enet_of_match, &pdev->dev);
	अगर (of_id) अणु
		pdata->enet_id = (क्रमागत xgene_enet_id)of_id->data;
	पूर्ण
#अगर_घोषित CONFIG_ACPI
	अन्यथा अणु
		स्थिर काष्ठा acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(xgene_enet_acpi_match, &pdev->dev);
		अगर (acpi_id)
			pdata->enet_id = (क्रमागत xgene_enet_id) acpi_id->driver_data;
	पूर्ण
#पूर्ण_अगर
	अगर (!pdata->enet_id) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = xgene_enet_get_resources(pdata);
	अगर (ret)
		जाओ err;

	xgene_enet_setup_ops(pdata);
	spin_lock_init(&pdata->mac_lock);

	अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) अणु
		ndev->features |= NETIF_F_TSO | NETIF_F_RXCSUM;
		spin_lock_init(&pdata->mss_lock);
	पूर्ण
	ndev->hw_features = ndev->features;

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		netdev_err(ndev, "No usable DMA configuration\n");
		जाओ err;
	पूर्ण

	xgene_enet_check_phy_handle(pdata);

	ret = xgene_enet_init_hw(pdata);
	अगर (ret)
		जाओ err2;

	link_state = pdata->mac_ops->link_state;
	अगर (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) अणु
		INIT_DELAYED_WORK(&pdata->link_work, link_state);
	पूर्ण अन्यथा अगर (!pdata->mdio_driver) अणु
		अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode))
			ret = xgene_enet_mdio_config(pdata);
		अन्यथा
			INIT_DELAYED_WORK(&pdata->link_work, link_state);

		अगर (ret)
			जाओ err1;
	पूर्ण

	spin_lock_init(&pdata->stats_lock);
	ret = xgene_extd_stats_init(pdata);
	अगर (ret)
		जाओ err1;

	xgene_enet_napi_add(pdata);
	ret = रेजिस्टर_netdev(ndev);
	अगर (ret) अणु
		netdev_err(ndev, "Failed to register netdev\n");
		जाओ err1;
	पूर्ण

	वापस 0;

err1:
	/*
	 * If necessary, मुक्त_netdev() will call netअगर_napi_del() and unकरो
	 * the effects of xgene_enet_napi_add()'s calls to netअगर_napi_add().
	 */

	xgene_enet_delete_desc_rings(pdata);

err2:
	अगर (pdata->mdio_driver)
		xgene_enet_phy_disconnect(pdata);
	अन्यथा अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode))
		xgene_enet_mdio_हटाओ(pdata);
err:
	मुक्त_netdev(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक xgene_enet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_enet_pdata *pdata;
	काष्ठा net_device *ndev;

	pdata = platक्रमm_get_drvdata(pdev);
	ndev = pdata->ndev;

	rtnl_lock();
	अगर (netअगर_running(ndev))
		dev_बंद(ndev);
	rtnl_unlock();

	अगर (pdata->mdio_driver)
		xgene_enet_phy_disconnect(pdata);
	अन्यथा अगर (phy_पूर्णांकerface_mode_is_rgmii(pdata->phy_mode))
		xgene_enet_mdio_हटाओ(pdata);

	unरेजिस्टर_netdev(ndev);
	xgene_enet_delete_desc_rings(pdata);
	pdata->port_ops->shutकरोwn(pdata);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल व्योम xgene_enet_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_enet_pdata *pdata;

	pdata = platक्रमm_get_drvdata(pdev);
	अगर (!pdata)
		वापस;

	अगर (!pdata->ndev)
		वापस;

	xgene_enet_हटाओ(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver xgene_enet_driver = अणु
	.driver = अणु
		   .name = "xgene-enet",
		   .of_match_table = of_match_ptr(xgene_enet_of_match),
		   .acpi_match_table = ACPI_PTR(xgene_enet_acpi_match),
	पूर्ण,
	.probe = xgene_enet_probe,
	.हटाओ = xgene_enet_हटाओ,
	.shutकरोwn = xgene_enet_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(xgene_enet_driver);

MODULE_DESCRIPTION("APM X-Gene SoC Ethernet driver");
MODULE_AUTHOR("Iyappan Subramanian <isubramanian@apm.com>");
MODULE_AUTHOR("Keyur Chudgar <kchudgar@apm.com>");
MODULE_LICENSE("GPL");
