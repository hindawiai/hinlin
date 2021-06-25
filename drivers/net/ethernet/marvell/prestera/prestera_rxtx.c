<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved */

#समावेश <linux/bitfield.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "prestera_dsa.h"
#समावेश "prestera.h"
#समावेश "prestera_hw.h"
#समावेश "prestera_rxtx.h"

#घोषणा PRESTERA_SDMA_WAIT_MUL		10

काष्ठा prestera_sdma_desc अणु
	__le32 word1;
	__le32 word2;
	__le32 buff;
	__le32 next;
पूर्ण __packed __aligned(16);

#घोषणा PRESTERA_SDMA_BUFF_SIZE_MAX	1544

#घोषणा PRESTERA_SDMA_RX_DESC_PKT_LEN(desc) \
	((le32_to_cpu((desc)->word2) >> 16) & GENMASK(13, 0))

#घोषणा PRESTERA_SDMA_RX_DESC_OWNER(desc) \
	((le32_to_cpu((desc)->word1) & BIT(31)) >> 31)

#घोषणा PRESTERA_SDMA_RX_DESC_IS_RCVD(desc) \
	(PRESTERA_SDMA_RX_DESC_OWNER(desc) == PRESTERA_SDMA_RX_DESC_CPU_OWN)

#घोषणा PRESTERA_SDMA_RX_DESC_CPU_OWN	0
#घोषणा PRESTERA_SDMA_RX_DESC_DMA_OWN	1

#घोषणा PRESTERA_SDMA_RX_QUEUE_NUM	8

#घोषणा PRESTERA_SDMA_RX_DESC_PER_Q	1000

#घोषणा PRESTERA_SDMA_TX_DESC_PER_Q	1000
#घोषणा PRESTERA_SDMA_TX_MAX_BURST	64

#घोषणा PRESTERA_SDMA_TX_DESC_OWNER(desc) \
	((le32_to_cpu((desc)->word1) & BIT(31)) >> 31)

#घोषणा PRESTERA_SDMA_TX_DESC_CPU_OWN	0
#घोषणा PRESTERA_SDMA_TX_DESC_DMA_OWN	1U

#घोषणा PRESTERA_SDMA_TX_DESC_IS_SENT(desc) \
	(PRESTERA_SDMA_TX_DESC_OWNER(desc) == PRESTERA_SDMA_TX_DESC_CPU_OWN)

#घोषणा PRESTERA_SDMA_TX_DESC_LAST	BIT(20)
#घोषणा PRESTERA_SDMA_TX_DESC_FIRST	BIT(21)
#घोषणा PRESTERA_SDMA_TX_DESC_CALC_CRC	BIT(12)

#घोषणा PRESTERA_SDMA_TX_DESC_SINGLE	\
	(PRESTERA_SDMA_TX_DESC_FIRST | PRESTERA_SDMA_TX_DESC_LAST)

#घोषणा PRESTERA_SDMA_TX_DESC_INIT	\
	(PRESTERA_SDMA_TX_DESC_SINGLE | PRESTERA_SDMA_TX_DESC_CALC_CRC)

#घोषणा PRESTERA_SDMA_RX_INTR_MASK_REG		0x2814
#घोषणा PRESTERA_SDMA_RX_QUEUE_STATUS_REG	0x2680
#घोषणा PRESTERA_SDMA_RX_QUEUE_DESC_REG(n)	(0x260C + (n) * 16)

#घोषणा PRESTERA_SDMA_TX_QUEUE_DESC_REG		0x26C0
#घोषणा PRESTERA_SDMA_TX_QUEUE_START_REG	0x2868

काष्ठा prestera_sdma_buf अणु
	काष्ठा prestera_sdma_desc *desc;
	dma_addr_t desc_dma;
	काष्ठा sk_buff *skb;
	dma_addr_t buf_dma;
	bool is_used;
पूर्ण;

काष्ठा prestera_rx_ring अणु
	काष्ठा prestera_sdma_buf *bufs;
	पूर्णांक next_rx;
पूर्ण;

काष्ठा prestera_tx_ring अणु
	काष्ठा prestera_sdma_buf *bufs;
	पूर्णांक next_tx;
	पूर्णांक max_burst;
	पूर्णांक burst;
पूर्ण;

काष्ठा prestera_sdma अणु
	काष्ठा prestera_rx_ring rx_ring[PRESTERA_SDMA_RX_QUEUE_NUM];
	काष्ठा prestera_tx_ring tx_ring;
	काष्ठा prestera_चयन *sw;
	काष्ठा dma_pool *desc_pool;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा napi_काष्ठा rx_napi;
	काष्ठा net_device napi_dev;
	u32 map_addr;
	u64 dma_mask;
	/* protect SDMA with concurrrent access from multiple CPUs */
	spinlock_t tx_lock;
पूर्ण;

काष्ठा prestera_rxtx अणु
	काष्ठा prestera_sdma sdma;
पूर्ण;

अटल पूर्णांक prestera_sdma_buf_init(काष्ठा prestera_sdma *sdma,
				  काष्ठा prestera_sdma_buf *buf)
अणु
	काष्ठा prestera_sdma_desc *desc;
	dma_addr_t dma;

	desc = dma_pool_alloc(sdma->desc_pool, GFP_DMA | GFP_KERNEL, &dma);
	अगर (!desc)
		वापस -ENOMEM;

	buf->buf_dma = DMA_MAPPING_ERROR;
	buf->desc_dma = dma;
	buf->desc = desc;
	buf->skb = शून्य;

	वापस 0;
पूर्ण

अटल u32 prestera_sdma_map(काष्ठा prestera_sdma *sdma, dma_addr_t pa)
अणु
	वापस sdma->map_addr + pa;
पूर्ण

अटल व्योम prestera_sdma_rx_desc_init(काष्ठा prestera_sdma *sdma,
				       काष्ठा prestera_sdma_desc *desc,
				       dma_addr_t buf)
अणु
	u32 word = le32_to_cpu(desc->word2);

	u32p_replace_bits(&word, PRESTERA_SDMA_BUFF_SIZE_MAX, GENMASK(15, 0));
	desc->word2 = cpu_to_le32(word);

	desc->buff = cpu_to_le32(prestera_sdma_map(sdma, buf));

	/* make sure buffer is set beक्रमe reset the descriptor */
	wmb();

	desc->word1 = cpu_to_le32(0xA0000000);
पूर्ण

अटल व्योम prestera_sdma_rx_desc_set_next(काष्ठा prestera_sdma *sdma,
					   काष्ठा prestera_sdma_desc *desc,
					   dma_addr_t next)
अणु
	desc->next = cpu_to_le32(prestera_sdma_map(sdma, next));
पूर्ण

अटल पूर्णांक prestera_sdma_rx_skb_alloc(काष्ठा prestera_sdma *sdma,
				      काष्ठा prestera_sdma_buf *buf)
अणु
	काष्ठा device *dev = sdma->sw->dev->dev;
	काष्ठा sk_buff *skb;
	dma_addr_t dma;

	skb = alloc_skb(PRESTERA_SDMA_BUFF_SIZE_MAX, GFP_DMA | GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	dma = dma_map_single(dev, skb->data, skb->len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, dma))
		जाओ err_dma_map;

	अगर (buf->skb)
		dma_unmap_single(dev, buf->buf_dma, buf->skb->len,
				 DMA_FROM_DEVICE);

	buf->buf_dma = dma;
	buf->skb = skb;

	वापस 0;

err_dma_map:
	kमुक्त_skb(skb);

	वापस -ENOMEM;
पूर्ण

अटल काष्ठा sk_buff *prestera_sdma_rx_skb_get(काष्ठा prestera_sdma *sdma,
						काष्ठा prestera_sdma_buf *buf)
अणु
	dma_addr_t buf_dma = buf->buf_dma;
	काष्ठा sk_buff *skb = buf->skb;
	u32 len = skb->len;
	पूर्णांक err;

	err = prestera_sdma_rx_skb_alloc(sdma, buf);
	अगर (err) अणु
		buf->buf_dma = buf_dma;
		buf->skb = skb;

		skb = alloc_skb(skb->len, GFP_ATOMIC);
		अगर (skb) अणु
			skb_put(skb, len);
			skb_copy_from_linear_data(buf->skb, skb->data, len);
		पूर्ण
	पूर्ण

	prestera_sdma_rx_desc_init(sdma, buf->desc, buf->buf_dma);

	वापस skb;
पूर्ण

अटल पूर्णांक prestera_rxtx_process_skb(काष्ठा prestera_sdma *sdma,
				     काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा prestera_port *port;
	काष्ठा prestera_dsa dsa;
	u32 hw_port, dev_id;
	पूर्णांक err;

	skb_pull(skb, ETH_HLEN);

	/* ethertype field is part of the dsa header */
	err = prestera_dsa_parse(&dsa, skb->data - ETH_TLEN);
	अगर (err)
		वापस err;

	dev_id = dsa.hw_dev_num;
	hw_port = dsa.port_num;

	port = prestera_port_find_by_hwid(sdma->sw, dev_id, hw_port);
	अगर (unlikely(!port)) अणु
		dev_warn_ratelimited(prestera_dev(sdma->sw), "received pkt for non-existent port(%u, %u)\n",
				     dev_id, hw_port);
		वापस -ENOENT;
	पूर्ण

	अगर (unlikely(!pskb_may_pull(skb, PRESTERA_DSA_HLEN)))
		वापस -EINVAL;

	/* हटाओ DSA tag and update checksum */
	skb_pull_rcsum(skb, PRESTERA_DSA_HLEN);

	स_हटाओ(skb->data - ETH_HLEN, skb->data - ETH_HLEN - PRESTERA_DSA_HLEN,
		ETH_ALEN * 2);

	skb_push(skb, ETH_HLEN);

	skb->protocol = eth_type_trans(skb, port->dev);

	अगर (dsa.vlan.is_tagged) अणु
		u16 tci = dsa.vlan.vid & VLAN_VID_MASK;

		tci |= dsa.vlan.vpt << VLAN_PRIO_SHIFT;
		अगर (dsa.vlan.cfi_bit)
			tci |= VLAN_CFI_MASK;

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tci);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_sdma_next_rx_buf_idx(पूर्णांक buf_idx)
अणु
	वापस (buf_idx + 1) % PRESTERA_SDMA_RX_DESC_PER_Q;
पूर्ण

अटल पूर्णांक prestera_sdma_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	पूर्णांक qnum = PRESTERA_SDMA_RX_QUEUE_NUM;
	अचिन्हित पूर्णांक rxq_करोne_map = 0;
	काष्ठा prestera_sdma *sdma;
	काष्ठा list_head rx_list;
	अचिन्हित पूर्णांक qmask;
	पूर्णांक pkts_करोne = 0;
	पूर्णांक q;

	qnum = PRESTERA_SDMA_RX_QUEUE_NUM;
	qmask = GENMASK(qnum - 1, 0);

	INIT_LIST_HEAD(&rx_list);

	sdma = container_of(napi, काष्ठा prestera_sdma, rx_napi);

	जबतक (pkts_करोne < budget && rxq_करोne_map != qmask) अणु
		क्रम (q = 0; q < qnum && pkts_करोne < budget; q++) अणु
			काष्ठा prestera_rx_ring *ring = &sdma->rx_ring[q];
			काष्ठा prestera_sdma_desc *desc;
			काष्ठा prestera_sdma_buf *buf;
			पूर्णांक buf_idx = ring->next_rx;
			काष्ठा sk_buff *skb;

			buf = &ring->bufs[buf_idx];
			desc = buf->desc;

			अगर (PRESTERA_SDMA_RX_DESC_IS_RCVD(desc)) अणु
				rxq_करोne_map &= ~BIT(q);
			पूर्ण अन्यथा अणु
				rxq_करोne_map |= BIT(q);
				जारी;
			पूर्ण

			pkts_करोne++;

			__skb_trim(buf->skb, PRESTERA_SDMA_RX_DESC_PKT_LEN(desc));

			skb = prestera_sdma_rx_skb_get(sdma, buf);
			अगर (!skb)
				जाओ rx_next_buf;

			अगर (unlikely(prestera_rxtx_process_skb(sdma, skb)))
				जाओ rx_next_buf;

			list_add_tail(&skb->list, &rx_list);
rx_next_buf:
			ring->next_rx = prestera_sdma_next_rx_buf_idx(buf_idx);
		पूर्ण
	पूर्ण

	अगर (pkts_करोne < budget && napi_complete_करोne(napi, pkts_करोne))
		prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_RX_INTR_MASK_REG,
			       GENMASK(9, 2));

	netअगर_receive_skb_list(&rx_list);

	वापस pkts_करोne;
पूर्ण

अटल व्योम prestera_sdma_rx_fini(काष्ठा prestera_sdma *sdma)
अणु
	पूर्णांक qnum = PRESTERA_SDMA_RX_QUEUE_NUM;
	पूर्णांक q, b;

	/* disable all rx queues */
	prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_RX_QUEUE_STATUS_REG,
		       GENMASK(15, 8));

	क्रम (q = 0; q < qnum; q++) अणु
		काष्ठा prestera_rx_ring *ring = &sdma->rx_ring[q];

		अगर (!ring->bufs)
			अवरोध;

		क्रम (b = 0; b < PRESTERA_SDMA_RX_DESC_PER_Q; b++) अणु
			काष्ठा prestera_sdma_buf *buf = &ring->bufs[b];

			अगर (buf->desc_dma)
				dma_pool_मुक्त(sdma->desc_pool, buf->desc,
					      buf->desc_dma);

			अगर (!buf->skb)
				जारी;

			अगर (buf->buf_dma != DMA_MAPPING_ERROR)
				dma_unmap_single(sdma->sw->dev->dev,
						 buf->buf_dma, buf->skb->len,
						 DMA_FROM_DEVICE);
			kमुक्त_skb(buf->skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक prestera_sdma_rx_init(काष्ठा prestera_sdma *sdma)
अणु
	पूर्णांक bnum = PRESTERA_SDMA_RX_DESC_PER_Q;
	पूर्णांक qnum = PRESTERA_SDMA_RX_QUEUE_NUM;
	पूर्णांक err;
	पूर्णांक q;

	/* disable all rx queues */
	prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_RX_QUEUE_STATUS_REG,
		       GENMASK(15, 8));

	क्रम (q = 0; q < qnum; q++) अणु
		काष्ठा prestera_sdma_buf *head, *tail, *next, *prev;
		काष्ठा prestera_rx_ring *ring = &sdma->rx_ring[q];

		ring->bufs = kदो_स्मृति_array(bnum, माप(*head), GFP_KERNEL);
		अगर (!ring->bufs)
			वापस -ENOMEM;

		ring->next_rx = 0;

		tail = &ring->bufs[bnum - 1];
		head = &ring->bufs[0];
		next = head;
		prev = next;

		करो अणु
			err = prestera_sdma_buf_init(sdma, next);
			अगर (err)
				वापस err;

			err = prestera_sdma_rx_skb_alloc(sdma, next);
			अगर (err)
				वापस err;

			prestera_sdma_rx_desc_init(sdma, next->desc,
						   next->buf_dma);

			prestera_sdma_rx_desc_set_next(sdma, prev->desc,
						       next->desc_dma);

			prev = next;
			next++;
		पूर्ण जबतक (prev != tail);

		/* join tail with head to make a circular list */
		prestera_sdma_rx_desc_set_next(sdma, tail->desc, head->desc_dma);

		prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_RX_QUEUE_DESC_REG(q),
			       prestera_sdma_map(sdma, head->desc_dma));
	पूर्ण

	/* make sure all rx descs are filled beक्रमe enabling all rx queues */
	wmb();

	prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_RX_QUEUE_STATUS_REG,
		       GENMASK(7, 0));

	वापस 0;
पूर्ण

अटल व्योम prestera_sdma_tx_desc_init(काष्ठा prestera_sdma *sdma,
				       काष्ठा prestera_sdma_desc *desc)
अणु
	desc->word1 = cpu_to_le32(PRESTERA_SDMA_TX_DESC_INIT);
	desc->word2 = 0;
पूर्ण

अटल व्योम prestera_sdma_tx_desc_set_next(काष्ठा prestera_sdma *sdma,
					   काष्ठा prestera_sdma_desc *desc,
					   dma_addr_t next)
अणु
	desc->next = cpu_to_le32(prestera_sdma_map(sdma, next));
पूर्ण

अटल व्योम prestera_sdma_tx_desc_set_buf(काष्ठा prestera_sdma *sdma,
					  काष्ठा prestera_sdma_desc *desc,
					  dma_addr_t buf, माप_प्रकार len)
अणु
	u32 word = le32_to_cpu(desc->word2);

	u32p_replace_bits(&word, len + ETH_FCS_LEN, GENMASK(30, 16));

	desc->buff = cpu_to_le32(prestera_sdma_map(sdma, buf));
	desc->word2 = cpu_to_le32(word);
पूर्ण

अटल व्योम prestera_sdma_tx_desc_xmit(काष्ठा prestera_sdma_desc *desc)
अणु
	u32 word = le32_to_cpu(desc->word1);

	word |= PRESTERA_SDMA_TX_DESC_DMA_OWN << 31;

	/* make sure everything is written beक्रमe enable xmit */
	wmb();

	desc->word1 = cpu_to_le32(word);
पूर्ण

अटल पूर्णांक prestera_sdma_tx_buf_map(काष्ठा prestera_sdma *sdma,
				    काष्ठा prestera_sdma_buf *buf,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dma_dev = sdma->sw->dev->dev;
	dma_addr_t dma;

	dma = dma_map_single(dma_dev, skb->data, skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dma_dev, dma))
		वापस -ENOMEM;

	buf->buf_dma = dma;
	buf->skb = skb;

	वापस 0;
पूर्ण

अटल व्योम prestera_sdma_tx_buf_unmap(काष्ठा prestera_sdma *sdma,
				       काष्ठा prestera_sdma_buf *buf)
अणु
	काष्ठा device *dma_dev = sdma->sw->dev->dev;

	dma_unmap_single(dma_dev, buf->buf_dma, buf->skb->len, DMA_TO_DEVICE);
पूर्ण

अटल व्योम prestera_sdma_tx_recycle_work_fn(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक bnum = PRESTERA_SDMA_TX_DESC_PER_Q;
	काष्ठा prestera_tx_ring *tx_ring;
	काष्ठा prestera_sdma *sdma;
	पूर्णांक b;

	sdma = container_of(work, काष्ठा prestera_sdma, tx_work);

	tx_ring = &sdma->tx_ring;

	क्रम (b = 0; b < bnum; b++) अणु
		काष्ठा prestera_sdma_buf *buf = &tx_ring->bufs[b];

		अगर (!buf->is_used)
			जारी;

		अगर (!PRESTERA_SDMA_TX_DESC_IS_SENT(buf->desc))
			जारी;

		prestera_sdma_tx_buf_unmap(sdma, buf);
		dev_consume_skb_any(buf->skb);
		buf->skb = शून्य;

		/* make sure everything is cleaned up */
		wmb();

		buf->is_used = false;
	पूर्ण
पूर्ण

अटल पूर्णांक prestera_sdma_tx_init(काष्ठा prestera_sdma *sdma)
अणु
	काष्ठा prestera_sdma_buf *head, *tail, *next, *prev;
	काष्ठा prestera_tx_ring *tx_ring = &sdma->tx_ring;
	पूर्णांक bnum = PRESTERA_SDMA_TX_DESC_PER_Q;
	पूर्णांक err;

	INIT_WORK(&sdma->tx_work, prestera_sdma_tx_recycle_work_fn);
	spin_lock_init(&sdma->tx_lock);

	tx_ring->bufs = kदो_स्मृति_array(bnum, माप(*head), GFP_KERNEL);
	अगर (!tx_ring->bufs)
		वापस -ENOMEM;

	tail = &tx_ring->bufs[bnum - 1];
	head = &tx_ring->bufs[0];
	next = head;
	prev = next;

	tx_ring->max_burst = PRESTERA_SDMA_TX_MAX_BURST;
	tx_ring->burst = tx_ring->max_burst;
	tx_ring->next_tx = 0;

	करो अणु
		err = prestera_sdma_buf_init(sdma, next);
		अगर (err)
			वापस err;

		next->is_used = false;

		prestera_sdma_tx_desc_init(sdma, next->desc);

		prestera_sdma_tx_desc_set_next(sdma, prev->desc,
					       next->desc_dma);

		prev = next;
		next++;
	पूर्ण जबतक (prev != tail);

	/* join tail with head to make a circular list */
	prestera_sdma_tx_desc_set_next(sdma, tail->desc, head->desc_dma);

	/* make sure descriptors are written */
	wmb();

	prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_TX_QUEUE_DESC_REG,
		       prestera_sdma_map(sdma, head->desc_dma));

	वापस 0;
पूर्ण

अटल व्योम prestera_sdma_tx_fini(काष्ठा prestera_sdma *sdma)
अणु
	काष्ठा prestera_tx_ring *ring = &sdma->tx_ring;
	पूर्णांक bnum = PRESTERA_SDMA_TX_DESC_PER_Q;
	पूर्णांक b;

	cancel_work_sync(&sdma->tx_work);

	अगर (!ring->bufs)
		वापस;

	क्रम (b = 0; b < bnum; b++) अणु
		काष्ठा prestera_sdma_buf *buf = &ring->bufs[b];

		अगर (buf->desc)
			dma_pool_मुक्त(sdma->desc_pool, buf->desc,
				      buf->desc_dma);

		अगर (!buf->skb)
			जारी;

		dma_unmap_single(sdma->sw->dev->dev, buf->buf_dma,
				 buf->skb->len, DMA_TO_DEVICE);

		dev_consume_skb_any(buf->skb);
	पूर्ण
पूर्ण

अटल व्योम prestera_rxtx_handle_event(काष्ठा prestera_चयन *sw,
				       काष्ठा prestera_event *evt,
				       व्योम *arg)
अणु
	काष्ठा prestera_sdma *sdma = arg;

	अगर (evt->id != PRESTERA_RXTX_EVENT_RCV_PKT)
		वापस;

	prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_RX_INTR_MASK_REG, 0);
	napi_schedule(&sdma->rx_napi);
पूर्ण

अटल पूर्णांक prestera_sdma_चयन_init(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_sdma *sdma = &sw->rxtx->sdma;
	काष्ठा device *dev = sw->dev->dev;
	काष्ठा prestera_rxtx_params p;
	पूर्णांक err;

	p.use_sdma = true;

	err = prestera_hw_rxtx_init(sw, &p);
	अगर (err) अणु
		dev_err(dev, "failed to init rxtx by hw\n");
		वापस err;
	पूर्ण

	sdma->dma_mask = dma_get_mask(dev);
	sdma->map_addr = p.map_addr;
	sdma->sw = sw;

	sdma->desc_pool = dma_pool_create("desc_pool", dev,
					  माप(काष्ठा prestera_sdma_desc),
					  16, 0);
	अगर (!sdma->desc_pool)
		वापस -ENOMEM;

	err = prestera_sdma_rx_init(sdma);
	अगर (err) अणु
		dev_err(dev, "failed to init rx ring\n");
		जाओ err_rx_init;
	पूर्ण

	err = prestera_sdma_tx_init(sdma);
	अगर (err) अणु
		dev_err(dev, "failed to init tx ring\n");
		जाओ err_tx_init;
	पूर्ण

	err = prestera_hw_event_handler_रेजिस्टर(sw, PRESTERA_EVENT_TYPE_RXTX,
						 prestera_rxtx_handle_event,
						 sdma);
	अगर (err)
		जाओ err_evt_रेजिस्टर;

	init_dummy_netdev(&sdma->napi_dev);

	netअगर_napi_add(&sdma->napi_dev, &sdma->rx_napi, prestera_sdma_rx_poll, 64);
	napi_enable(&sdma->rx_napi);

	वापस 0;

err_evt_रेजिस्टर:
err_tx_init:
	prestera_sdma_tx_fini(sdma);
err_rx_init:
	prestera_sdma_rx_fini(sdma);

	dma_pool_destroy(sdma->desc_pool);
	वापस err;
पूर्ण

अटल व्योम prestera_sdma_चयन_fini(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_sdma *sdma = &sw->rxtx->sdma;

	napi_disable(&sdma->rx_napi);
	netअगर_napi_del(&sdma->rx_napi);
	prestera_hw_event_handler_unरेजिस्टर(sw, PRESTERA_EVENT_TYPE_RXTX,
					     prestera_rxtx_handle_event);
	prestera_sdma_tx_fini(sdma);
	prestera_sdma_rx_fini(sdma);
	dma_pool_destroy(sdma->desc_pool);
पूर्ण

अटल bool prestera_sdma_is_पढ़ोy(काष्ठा prestera_sdma *sdma)
अणु
	वापस !(prestera_पढ़ो(sdma->sw, PRESTERA_SDMA_TX_QUEUE_START_REG) & 1);
पूर्ण

अटल पूर्णांक prestera_sdma_tx_रुको(काष्ठा prestera_sdma *sdma,
				 काष्ठा prestera_tx_ring *tx_ring)
अणु
	पूर्णांक tx_रुको_num = PRESTERA_SDMA_WAIT_MUL * tx_ring->max_burst;

	करो अणु
		अगर (prestera_sdma_is_पढ़ोy(sdma))
			वापस 0;

		udelay(1);
	पूर्ण जबतक (--tx_रुको_num);

	वापस -EBUSY;
पूर्ण

अटल व्योम prestera_sdma_tx_start(काष्ठा prestera_sdma *sdma)
अणु
	prestera_ग_लिखो(sdma->sw, PRESTERA_SDMA_TX_QUEUE_START_REG, 1);
	schedule_work(&sdma->tx_work);
पूर्ण

अटल netdev_tx_t prestera_sdma_xmit(काष्ठा prestera_sdma *sdma,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dma_dev = sdma->sw->dev->dev;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा prestera_tx_ring *tx_ring;
	काष्ठा prestera_sdma_buf *buf;
	पूर्णांक err;

	spin_lock(&sdma->tx_lock);

	tx_ring = &sdma->tx_ring;

	buf = &tx_ring->bufs[tx_ring->next_tx];
	अगर (buf->is_used) अणु
		schedule_work(&sdma->tx_work);
		जाओ drop_skb;
	पूर्ण

	अगर (unlikely(eth_skb_pad(skb)))
		जाओ drop_skb_noमुक्त;

	err = prestera_sdma_tx_buf_map(sdma, buf, skb);
	अगर (err)
		जाओ drop_skb;

	prestera_sdma_tx_desc_set_buf(sdma, buf->desc, buf->buf_dma, skb->len);

	dma_sync_single_क्रम_device(dma_dev, buf->buf_dma, skb->len,
				   DMA_TO_DEVICE);

	अगर (tx_ring->burst) अणु
		tx_ring->burst--;
	पूर्ण अन्यथा अणु
		tx_ring->burst = tx_ring->max_burst;

		err = prestera_sdma_tx_रुको(sdma, tx_ring);
		अगर (err)
			जाओ drop_skb_unmap;
	पूर्ण

	tx_ring->next_tx = (tx_ring->next_tx + 1) % PRESTERA_SDMA_TX_DESC_PER_Q;
	prestera_sdma_tx_desc_xmit(buf->desc);
	buf->is_used = true;

	prestera_sdma_tx_start(sdma);

	जाओ tx_करोne;

drop_skb_unmap:
	prestera_sdma_tx_buf_unmap(sdma, buf);
drop_skb:
	dev_consume_skb_any(skb);
drop_skb_noमुक्त:
	dev->stats.tx_dropped++;
tx_करोne:
	spin_unlock(&sdma->tx_lock);
	वापस NETDEV_TX_OK;
पूर्ण

पूर्णांक prestera_rxtx_चयन_init(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_rxtx *rxtx;

	rxtx = kzalloc(माप(*rxtx), GFP_KERNEL);
	अगर (!rxtx)
		वापस -ENOMEM;

	sw->rxtx = rxtx;

	वापस prestera_sdma_चयन_init(sw);
पूर्ण

व्योम prestera_rxtx_चयन_fini(काष्ठा prestera_चयन *sw)
अणु
	prestera_sdma_चयन_fini(sw);
	kमुक्त(sw->rxtx);
पूर्ण

पूर्णांक prestera_rxtx_port_init(काष्ठा prestera_port *port)
अणु
	पूर्णांक err;

	err = prestera_hw_rxtx_port_init(port);
	अगर (err)
		वापस err;

	port->dev->needed_headroom = PRESTERA_DSA_HLEN;

	वापस 0;
पूर्ण

netdev_tx_t prestera_rxtx_xmit(काष्ठा prestera_port *port, काष्ठा sk_buff *skb)
अणु
	काष्ठा prestera_dsa dsa;

	dsa.hw_dev_num = port->dev_id;
	dsa.port_num = port->hw_id;

	अगर (skb_cow_head(skb, PRESTERA_DSA_HLEN) < 0)
		वापस NET_XMIT_DROP;

	skb_push(skb, PRESTERA_DSA_HLEN);
	स_हटाओ(skb->data, skb->data + PRESTERA_DSA_HLEN, 2 * ETH_ALEN);

	अगर (prestera_dsa_build(&dsa, skb->data + 2 * ETH_ALEN) != 0)
		वापस NET_XMIT_DROP;

	वापस prestera_sdma_xmit(&port->sw->rxtx->sdma, skb);
पूर्ण
