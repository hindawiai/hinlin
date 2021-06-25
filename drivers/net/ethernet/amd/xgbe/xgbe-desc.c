<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2014 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल व्योम xgbe_unmap_rdata(काष्ठा xgbe_prv_data *, काष्ठा xgbe_ring_data *);

अटल व्योम xgbe_मुक्त_ring(काष्ठा xgbe_prv_data *pdata,
			   काष्ठा xgbe_ring *ring)
अणु
	काष्ठा xgbe_ring_data *rdata;
	अचिन्हित पूर्णांक i;

	अगर (!ring)
		वापस;

	अगर (ring->rdata) अणु
		क्रम (i = 0; i < ring->rdesc_count; i++) अणु
			rdata = XGBE_GET_DESC_DATA(ring, i);
			xgbe_unmap_rdata(pdata, rdata);
		पूर्ण

		kमुक्त(ring->rdata);
		ring->rdata = शून्य;
	पूर्ण

	अगर (ring->rx_hdr_pa.pages) अणु
		dma_unmap_page(pdata->dev, ring->rx_hdr_pa.pages_dma,
			       ring->rx_hdr_pa.pages_len, DMA_FROM_DEVICE);
		put_page(ring->rx_hdr_pa.pages);

		ring->rx_hdr_pa.pages = शून्य;
		ring->rx_hdr_pa.pages_len = 0;
		ring->rx_hdr_pa.pages_offset = 0;
		ring->rx_hdr_pa.pages_dma = 0;
	पूर्ण

	अगर (ring->rx_buf_pa.pages) अणु
		dma_unmap_page(pdata->dev, ring->rx_buf_pa.pages_dma,
			       ring->rx_buf_pa.pages_len, DMA_FROM_DEVICE);
		put_page(ring->rx_buf_pa.pages);

		ring->rx_buf_pa.pages = शून्य;
		ring->rx_buf_pa.pages_len = 0;
		ring->rx_buf_pa.pages_offset = 0;
		ring->rx_buf_pa.pages_dma = 0;
	पूर्ण

	अगर (ring->rdesc) अणु
		dma_मुक्त_coherent(pdata->dev,
				  (माप(काष्ठा xgbe_ring_desc) *
				   ring->rdesc_count),
				  ring->rdesc, ring->rdesc_dma);
		ring->rdesc = शून्य;
	पूर्ण
पूर्ण

अटल व्योम xgbe_मुक्त_ring_resources(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;

	DBGPR("-->xgbe_free_ring_resources\n");

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		xgbe_मुक्त_ring(pdata, channel->tx_ring);
		xgbe_मुक्त_ring(pdata, channel->rx_ring);
	पूर्ण

	DBGPR("<--xgbe_free_ring_resources\n");
पूर्ण

अटल व्योम *xgbe_alloc_node(माप_प्रकार size, पूर्णांक node)
अणु
	व्योम *mem;

	mem = kzalloc_node(size, GFP_KERNEL, node);
	अगर (!mem)
		mem = kzalloc(size, GFP_KERNEL);

	वापस mem;
पूर्ण

अटल व्योम *xgbe_dma_alloc_node(काष्ठा device *dev, माप_प्रकार size,
				 dma_addr_t *dma, पूर्णांक node)
अणु
	व्योम *mem;
	पूर्णांक cur_node = dev_to_node(dev);

	set_dev_node(dev, node);
	mem = dma_alloc_coherent(dev, size, dma, GFP_KERNEL);
	set_dev_node(dev, cur_node);

	अगर (!mem)
		mem = dma_alloc_coherent(dev, size, dma, GFP_KERNEL);

	वापस mem;
पूर्ण

अटल पूर्णांक xgbe_init_ring(काष्ठा xgbe_prv_data *pdata,
			  काष्ठा xgbe_ring *ring, अचिन्हित पूर्णांक rdesc_count)
अणु
	माप_प्रकार size;

	अगर (!ring)
		वापस 0;

	/* Descriptors */
	size = rdesc_count * माप(काष्ठा xgbe_ring_desc);

	ring->rdesc_count = rdesc_count;
	ring->rdesc = xgbe_dma_alloc_node(pdata->dev, size, &ring->rdesc_dma,
					  ring->node);
	अगर (!ring->rdesc)
		वापस -ENOMEM;

	/* Descriptor inक्रमmation */
	size = rdesc_count * माप(काष्ठा xgbe_ring_data);

	ring->rdata = xgbe_alloc_node(size, ring->node);
	अगर (!ring->rdata)
		वापस -ENOMEM;

	netअगर_dbg(pdata, drv, pdata->netdev,
		  "rdesc=%p, rdesc_dma=%pad, rdata=%p, node=%d\n",
		  ring->rdesc, &ring->rdesc_dma, ring->rdata, ring->node);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_alloc_ring_resources(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		netअगर_dbg(pdata, drv, pdata->netdev, "%s - Tx ring:\n",
			  channel->name);

		ret = xgbe_init_ring(pdata, channel->tx_ring,
				     pdata->tx_desc_count);
		अगर (ret) अणु
			netdev_alert(pdata->netdev,
				     "error initializing Tx ring\n");
			जाओ err_ring;
		पूर्ण

		netअगर_dbg(pdata, drv, pdata->netdev, "%s - Rx ring:\n",
			  channel->name);

		ret = xgbe_init_ring(pdata, channel->rx_ring,
				     pdata->rx_desc_count);
		अगर (ret) अणु
			netdev_alert(pdata->netdev,
				     "error initializing Rx ring\n");
			जाओ err_ring;
		पूर्ण
	पूर्ण

	वापस 0;

err_ring:
	xgbe_मुक्त_ring_resources(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_alloc_pages(काष्ठा xgbe_prv_data *pdata,
			    काष्ठा xgbe_page_alloc *pa, पूर्णांक alloc_order,
			    पूर्णांक node)
अणु
	काष्ठा page *pages = शून्य;
	dma_addr_t pages_dma;
	gfp_t gfp;
	पूर्णांक order;

again:
	order = alloc_order;

	/* Try to obtain pages, decreasing order अगर necessary */
	gfp = GFP_ATOMIC | __GFP_COMP | __GFP_NOWARN;
	जबतक (order >= 0) अणु
		pages = alloc_pages_node(node, gfp, order);
		अगर (pages)
			अवरोध;

		order--;
	पूर्ण

	/* If we couldn't get local pages, try getting from anywhere */
	अगर (!pages && (node != NUMA_NO_NODE)) अणु
		node = NUMA_NO_NODE;
		जाओ again;
	पूर्ण

	अगर (!pages)
		वापस -ENOMEM;

	/* Map the pages */
	pages_dma = dma_map_page(pdata->dev, pages, 0,
				 PAGE_SIZE << order, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(pdata->dev, pages_dma)) अणु
		put_page(pages);
		वापस -ENOMEM;
	पूर्ण

	pa->pages = pages;
	pa->pages_len = PAGE_SIZE << order;
	pa->pages_offset = 0;
	pa->pages_dma = pages_dma;

	वापस 0;
पूर्ण

अटल व्योम xgbe_set_buffer_data(काष्ठा xgbe_buffer_data *bd,
				 काष्ठा xgbe_page_alloc *pa,
				 अचिन्हित पूर्णांक len)
अणु
	get_page(pa->pages);
	bd->pa = *pa;

	bd->dma_base = pa->pages_dma;
	bd->dma_off = pa->pages_offset;
	bd->dma_len = len;

	pa->pages_offset += len;
	अगर ((pa->pages_offset + len) > pa->pages_len) अणु
		/* This data descriptor is responsible क्रम unmapping page(s) */
		bd->pa_unmap = *pa;

		/* Get a new allocation next समय */
		pa->pages = शून्य;
		pa->pages_len = 0;
		pa->pages_offset = 0;
		pa->pages_dma = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_map_rx_buffer(काष्ठा xgbe_prv_data *pdata,
			      काष्ठा xgbe_ring *ring,
			      काष्ठा xgbe_ring_data *rdata)
अणु
	पूर्णांक ret;

	अगर (!ring->rx_hdr_pa.pages) अणु
		ret = xgbe_alloc_pages(pdata, &ring->rx_hdr_pa, 0, ring->node);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!ring->rx_buf_pa.pages) अणु
		ret = xgbe_alloc_pages(pdata, &ring->rx_buf_pa,
				       PAGE_ALLOC_COSTLY_ORDER, ring->node);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set up the header page info */
	xgbe_set_buffer_data(&rdata->rx.hdr, &ring->rx_hdr_pa,
			     XGBE_SKB_ALLOC_SIZE);

	/* Set up the buffer page info */
	xgbe_set_buffer_data(&rdata->rx.buf, &ring->rx_buf_pa,
			     pdata->rx_buf_size);

	वापस 0;
पूर्ण

अटल व्योम xgbe_wrapper_tx_descriptor_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_channel *channel;
	काष्ठा xgbe_ring *ring;
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_ring_desc *rdesc;
	dma_addr_t rdesc_dma;
	अचिन्हित पूर्णांक i, j;

	DBGPR("-->xgbe_wrapper_tx_descriptor_init\n");

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		ring = channel->tx_ring;
		अगर (!ring)
			अवरोध;

		rdesc = ring->rdesc;
		rdesc_dma = ring->rdesc_dma;

		क्रम (j = 0; j < ring->rdesc_count; j++) अणु
			rdata = XGBE_GET_DESC_DATA(ring, j);

			rdata->rdesc = rdesc;
			rdata->rdesc_dma = rdesc_dma;

			rdesc++;
			rdesc_dma += माप(काष्ठा xgbe_ring_desc);
		पूर्ण

		ring->cur = 0;
		ring->dirty = 0;
		स_रखो(&ring->tx, 0, माप(ring->tx));

		hw_अगर->tx_desc_init(channel);
	पूर्ण

	DBGPR("<--xgbe_wrapper_tx_descriptor_init\n");
पूर्ण

अटल व्योम xgbe_wrapper_rx_descriptor_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	काष्ठा xgbe_channel *channel;
	काष्ठा xgbe_ring *ring;
	काष्ठा xgbe_ring_desc *rdesc;
	काष्ठा xgbe_ring_data *rdata;
	dma_addr_t rdesc_dma;
	अचिन्हित पूर्णांक i, j;

	DBGPR("-->xgbe_wrapper_rx_descriptor_init\n");

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];
		ring = channel->rx_ring;
		अगर (!ring)
			अवरोध;

		rdesc = ring->rdesc;
		rdesc_dma = ring->rdesc_dma;

		क्रम (j = 0; j < ring->rdesc_count; j++) अणु
			rdata = XGBE_GET_DESC_DATA(ring, j);

			rdata->rdesc = rdesc;
			rdata->rdesc_dma = rdesc_dma;

			अगर (xgbe_map_rx_buffer(pdata, ring, rdata))
				अवरोध;

			rdesc++;
			rdesc_dma += माप(काष्ठा xgbe_ring_desc);
		पूर्ण

		ring->cur = 0;
		ring->dirty = 0;

		hw_अगर->rx_desc_init(channel);
	पूर्ण

	DBGPR("<--xgbe_wrapper_rx_descriptor_init\n");
पूर्ण

अटल व्योम xgbe_unmap_rdata(काष्ठा xgbe_prv_data *pdata,
			     काष्ठा xgbe_ring_data *rdata)
अणु
	अगर (rdata->skb_dma) अणु
		अगर (rdata->mapped_as_page) अणु
			dma_unmap_page(pdata->dev, rdata->skb_dma,
				       rdata->skb_dma_len, DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			dma_unmap_single(pdata->dev, rdata->skb_dma,
					 rdata->skb_dma_len, DMA_TO_DEVICE);
		पूर्ण
		rdata->skb_dma = 0;
		rdata->skb_dma_len = 0;
	पूर्ण

	अगर (rdata->skb) अणु
		dev_kमुक्त_skb_any(rdata->skb);
		rdata->skb = शून्य;
	पूर्ण

	अगर (rdata->rx.hdr.pa.pages)
		put_page(rdata->rx.hdr.pa.pages);

	अगर (rdata->rx.hdr.pa_unmap.pages) अणु
		dma_unmap_page(pdata->dev, rdata->rx.hdr.pa_unmap.pages_dma,
			       rdata->rx.hdr.pa_unmap.pages_len,
			       DMA_FROM_DEVICE);
		put_page(rdata->rx.hdr.pa_unmap.pages);
	पूर्ण

	अगर (rdata->rx.buf.pa.pages)
		put_page(rdata->rx.buf.pa.pages);

	अगर (rdata->rx.buf.pa_unmap.pages) अणु
		dma_unmap_page(pdata->dev, rdata->rx.buf.pa_unmap.pages_dma,
			       rdata->rx.buf.pa_unmap.pages_len,
			       DMA_FROM_DEVICE);
		put_page(rdata->rx.buf.pa_unmap.pages);
	पूर्ण

	स_रखो(&rdata->tx, 0, माप(rdata->tx));
	स_रखो(&rdata->rx, 0, माप(rdata->rx));

	rdata->mapped_as_page = 0;

	अगर (rdata->state_saved) अणु
		rdata->state_saved = 0;
		rdata->state.skb = शून्य;
		rdata->state.len = 0;
		rdata->state.error = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_map_tx_skb(काष्ठा xgbe_channel *channel, काष्ठा sk_buff *skb)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_ring *ring = channel->tx_ring;
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_packet_data *packet;
	skb_frag_t *frag;
	dma_addr_t skb_dma;
	अचिन्हित पूर्णांक start_index, cur_index;
	अचिन्हित पूर्णांक offset, tso, vlan, datalen, len;
	अचिन्हित पूर्णांक i;

	DBGPR("-->xgbe_map_tx_skb: cur = %d\n", ring->cur);

	offset = 0;
	start_index = ring->cur;
	cur_index = ring->cur;

	packet = &ring->packet_data;
	packet->rdesc_count = 0;
	packet->length = 0;

	tso = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			     TSO_ENABLE);
	vlan = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			      VLAN_CTAG);

	/* Save space क्रम a context descriptor अगर needed */
	अगर ((tso && (packet->mss != ring->tx.cur_mss)) ||
	    (vlan && (packet->vlan_ctag != ring->tx.cur_vlan_ctag)))
		cur_index++;
	rdata = XGBE_GET_DESC_DATA(ring, cur_index);

	अगर (tso) अणु
		/* Map the TSO header */
		skb_dma = dma_map_single(pdata->dev, skb->data,
					 packet->header_len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(pdata->dev, skb_dma)) अणु
			netdev_alert(pdata->netdev, "dma_map_single failed\n");
			जाओ err_out;
		पूर्ण
		rdata->skb_dma = skb_dma;
		rdata->skb_dma_len = packet->header_len;
		netअगर_dbg(pdata, tx_queued, pdata->netdev,
			  "skb header: index=%u, dma=%pad, len=%u\n",
			  cur_index, &skb_dma, packet->header_len);

		offset = packet->header_len;

		packet->length += packet->header_len;

		cur_index++;
		rdata = XGBE_GET_DESC_DATA(ring, cur_index);
	पूर्ण

	/* Map the (reमुख्यder of the) packet */
	क्रम (datalen = skb_headlen(skb) - offset; datalen; ) अणु
		len = min_t(अचिन्हित पूर्णांक, datalen, XGBE_TX_MAX_BUF_SIZE);

		skb_dma = dma_map_single(pdata->dev, skb->data + offset, len,
					 DMA_TO_DEVICE);
		अगर (dma_mapping_error(pdata->dev, skb_dma)) अणु
			netdev_alert(pdata->netdev, "dma_map_single failed\n");
			जाओ err_out;
		पूर्ण
		rdata->skb_dma = skb_dma;
		rdata->skb_dma_len = len;
		netअगर_dbg(pdata, tx_queued, pdata->netdev,
			  "skb data: index=%u, dma=%pad, len=%u\n",
			  cur_index, &skb_dma, len);

		datalen -= len;
		offset += len;

		packet->length += len;

		cur_index++;
		rdata = XGBE_GET_DESC_DATA(ring, cur_index);
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		netअगर_dbg(pdata, tx_queued, pdata->netdev,
			  "mapping frag %u\n", i);

		frag = &skb_shinfo(skb)->frags[i];
		offset = 0;

		क्रम (datalen = skb_frag_size(frag); datalen; ) अणु
			len = min_t(अचिन्हित पूर्णांक, datalen,
				    XGBE_TX_MAX_BUF_SIZE);

			skb_dma = skb_frag_dma_map(pdata->dev, frag, offset,
						   len, DMA_TO_DEVICE);
			अगर (dma_mapping_error(pdata->dev, skb_dma)) अणु
				netdev_alert(pdata->netdev,
					     "skb_frag_dma_map failed\n");
				जाओ err_out;
			पूर्ण
			rdata->skb_dma = skb_dma;
			rdata->skb_dma_len = len;
			rdata->mapped_as_page = 1;
			netअगर_dbg(pdata, tx_queued, pdata->netdev,
				  "skb frag: index=%u, dma=%pad, len=%u\n",
				  cur_index, &skb_dma, len);

			datalen -= len;
			offset += len;

			packet->length += len;

			cur_index++;
			rdata = XGBE_GET_DESC_DATA(ring, cur_index);
		पूर्ण
	पूर्ण

	/* Save the skb address in the last entry. We always have some data
	 * that has been mapped so rdata is always advanced past the last
	 * piece of mapped data - use the entry poपूर्णांकed to by cur_index - 1.
	 */
	rdata = XGBE_GET_DESC_DATA(ring, cur_index - 1);
	rdata->skb = skb;

	/* Save the number of descriptor entries used */
	packet->rdesc_count = cur_index - start_index;

	DBGPR("<--xgbe_map_tx_skb: count=%u\n", packet->rdesc_count);

	वापस packet->rdesc_count;

err_out:
	जबतक (start_index < cur_index) अणु
		rdata = XGBE_GET_DESC_DATA(ring, start_index++);
		xgbe_unmap_rdata(pdata, rdata);
	पूर्ण

	DBGPR("<--xgbe_map_tx_skb: count=0\n");

	वापस 0;
पूर्ण

व्योम xgbe_init_function_ptrs_desc(काष्ठा xgbe_desc_अगर *desc_अगर)
अणु
	DBGPR("-->xgbe_init_function_ptrs_desc\n");

	desc_अगर->alloc_ring_resources = xgbe_alloc_ring_resources;
	desc_अगर->मुक्त_ring_resources = xgbe_मुक्त_ring_resources;
	desc_अगर->map_tx_skb = xgbe_map_tx_skb;
	desc_अगर->map_rx_buffer = xgbe_map_rx_buffer;
	desc_अगर->unmap_rdata = xgbe_unmap_rdata;
	desc_अगर->wrapper_tx_desc_init = xgbe_wrapper_tx_descriptor_init;
	desc_अगर->wrapper_rx_desc_init = xgbe_wrapper_rx_descriptor_init;

	DBGPR("<--xgbe_init_function_ptrs_desc\n");
पूर्ण
