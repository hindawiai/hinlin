<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश "main.h"
#समावेश "pci.h"
#समावेश "reg.h"
#समावेश "tx.h"
#समावेश "rx.h"
#समावेश "fw.h"
#समावेश "ps.h"
#समावेश "debug.h"

अटल bool rtw_disable_msi;
अटल bool rtw_pci_disable_aspm;
module_param_named(disable_msi, rtw_disable_msi, bool, 0644);
module_param_named(disable_aspm, rtw_pci_disable_aspm, bool, 0644);
MODULE_PARM_DESC(disable_msi, "Set Y to disable MSI interrupt support");
MODULE_PARM_DESC(disable_aspm, "Set Y to disable PCI ASPM support");

अटल u32 rtw_pci_tx_queue_idx_addr[] = अणु
	[RTW_TX_QUEUE_BK]	= RTK_PCI_TXBD_IDX_BKQ,
	[RTW_TX_QUEUE_BE]	= RTK_PCI_TXBD_IDX_BEQ,
	[RTW_TX_QUEUE_VI]	= RTK_PCI_TXBD_IDX_VIQ,
	[RTW_TX_QUEUE_VO]	= RTK_PCI_TXBD_IDX_VOQ,
	[RTW_TX_QUEUE_MGMT]	= RTK_PCI_TXBD_IDX_MGMTQ,
	[RTW_TX_QUEUE_HI0]	= RTK_PCI_TXBD_IDX_HI0Q,
	[RTW_TX_QUEUE_H2C]	= RTK_PCI_TXBD_IDX_H2CQ,
पूर्ण;

अटल u8 rtw_pci_get_tx_qsel(काष्ठा sk_buff *skb, u8 queue)
अणु
	चयन (queue) अणु
	हाल RTW_TX_QUEUE_BCN:
		वापस TX_DESC_QSEL_BEACON;
	हाल RTW_TX_QUEUE_H2C:
		वापस TX_DESC_QSEL_H2C;
	हाल RTW_TX_QUEUE_MGMT:
		वापस TX_DESC_QSEL_MGMT;
	हाल RTW_TX_QUEUE_HI0:
		वापस TX_DESC_QSEL_HIGH;
	शेष:
		वापस skb->priority;
	पूर्ण
पूर्ण;

अटल u8 rtw_pci_पढ़ो8(काष्ठा rtw_dev *rtwdev, u32 addr)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	वापस पढ़ोb(rtwpci->mmap + addr);
पूर्ण

अटल u16 rtw_pci_पढ़ो16(काष्ठा rtw_dev *rtwdev, u32 addr)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	वापस पढ़ोw(rtwpci->mmap + addr);
पूर्ण

अटल u32 rtw_pci_पढ़ो32(काष्ठा rtw_dev *rtwdev, u32 addr)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	वापस पढ़ोl(rtwpci->mmap + addr);
पूर्ण

अटल व्योम rtw_pci_ग_लिखो8(काष्ठा rtw_dev *rtwdev, u32 addr, u8 val)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	ग_लिखोb(val, rtwpci->mmap + addr);
पूर्ण

अटल व्योम rtw_pci_ग_लिखो16(काष्ठा rtw_dev *rtwdev, u32 addr, u16 val)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	ग_लिखोw(val, rtwpci->mmap + addr);
पूर्ण

अटल व्योम rtw_pci_ग_लिखो32(काष्ठा rtw_dev *rtwdev, u32 addr, u32 val)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	ग_लिखोl(val, rtwpci->mmap + addr);
पूर्ण

अटल अंतरभूत व्योम *rtw_pci_get_tx_desc(काष्ठा rtw_pci_tx_ring *tx_ring, u8 idx)
अणु
	पूर्णांक offset = tx_ring->r.desc_size * idx;

	वापस tx_ring->r.head + offset;
पूर्ण

अटल व्योम rtw_pci_मुक्त_tx_ring_skbs(काष्ठा rtw_dev *rtwdev,
				      काष्ठा rtw_pci_tx_ring *tx_ring)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(rtwdev->dev);
	काष्ठा rtw_pci_tx_data *tx_data;
	काष्ठा sk_buff *skb, *पंचांगp;
	dma_addr_t dma;

	/* मुक्त every skb reमुख्यed in tx list */
	skb_queue_walk_safe(&tx_ring->queue, skb, पंचांगp) अणु
		__skb_unlink(skb, &tx_ring->queue);
		tx_data = rtw_pci_get_tx_data(skb);
		dma = tx_data->dma;

		dma_unmap_single(&pdev->dev, dma, skb->len, DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम rtw_pci_मुक्त_tx_ring(काष्ठा rtw_dev *rtwdev,
				 काष्ठा rtw_pci_tx_ring *tx_ring)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(rtwdev->dev);
	u8 *head = tx_ring->r.head;
	u32 len = tx_ring->r.len;
	पूर्णांक ring_sz = len * tx_ring->r.desc_size;

	rtw_pci_मुक्त_tx_ring_skbs(rtwdev, tx_ring);

	/* मुक्त the ring itself */
	dma_मुक्त_coherent(&pdev->dev, ring_sz, head, tx_ring->r.dma);
	tx_ring->r.head = शून्य;
पूर्ण

अटल व्योम rtw_pci_मुक्त_rx_ring_skbs(काष्ठा rtw_dev *rtwdev,
				      काष्ठा rtw_pci_rx_ring *rx_ring)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(rtwdev->dev);
	काष्ठा sk_buff *skb;
	पूर्णांक buf_sz = RTK_PCI_RX_BUF_SIZE;
	dma_addr_t dma;
	पूर्णांक i;

	क्रम (i = 0; i < rx_ring->r.len; i++) अणु
		skb = rx_ring->buf[i];
		अगर (!skb)
			जारी;

		dma = *((dma_addr_t *)skb->cb);
		dma_unmap_single(&pdev->dev, dma, buf_sz, DMA_FROM_DEVICE);
		dev_kमुक्त_skb(skb);
		rx_ring->buf[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम rtw_pci_मुक्त_rx_ring(काष्ठा rtw_dev *rtwdev,
				 काष्ठा rtw_pci_rx_ring *rx_ring)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(rtwdev->dev);
	u8 *head = rx_ring->r.head;
	पूर्णांक ring_sz = rx_ring->r.desc_size * rx_ring->r.len;

	rtw_pci_मुक्त_rx_ring_skbs(rtwdev, rx_ring);

	dma_मुक्त_coherent(&pdev->dev, ring_sz, head, rx_ring->r.dma);
पूर्ण

अटल व्योम rtw_pci_मुक्त_trx_ring(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_pci_tx_ring *tx_ring;
	काष्ठा rtw_pci_rx_ring *rx_ring;
	पूर्णांक i;

	क्रम (i = 0; i < RTK_MAX_TX_QUEUE_NUM; i++) अणु
		tx_ring = &rtwpci->tx_rings[i];
		rtw_pci_मुक्त_tx_ring(rtwdev, tx_ring);
	पूर्ण

	क्रम (i = 0; i < RTK_MAX_RX_QUEUE_NUM; i++) अणु
		rx_ring = &rtwpci->rx_rings[i];
		rtw_pci_मुक्त_rx_ring(rtwdev, rx_ring);
	पूर्ण
पूर्ण

अटल पूर्णांक rtw_pci_init_tx_ring(काष्ठा rtw_dev *rtwdev,
				काष्ठा rtw_pci_tx_ring *tx_ring,
				u8 desc_size, u32 len)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(rtwdev->dev);
	पूर्णांक ring_sz = desc_size * len;
	dma_addr_t dma;
	u8 *head;

	अगर (len > TRX_BD_IDX_MASK) अणु
		rtw_err(rtwdev, "len %d exceeds maximum TX entries\n", len);
		वापस -EINVAL;
	पूर्ण

	head = dma_alloc_coherent(&pdev->dev, ring_sz, &dma, GFP_KERNEL);
	अगर (!head) अणु
		rtw_err(rtwdev, "failed to allocate tx ring\n");
		वापस -ENOMEM;
	पूर्ण

	skb_queue_head_init(&tx_ring->queue);
	tx_ring->r.head = head;
	tx_ring->r.dma = dma;
	tx_ring->r.len = len;
	tx_ring->r.desc_size = desc_size;
	tx_ring->r.wp = 0;
	tx_ring->r.rp = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_pci_reset_rx_desc(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb,
				 काष्ठा rtw_pci_rx_ring *rx_ring,
				 u32 idx, u32 desc_sz)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(rtwdev->dev);
	काष्ठा rtw_pci_rx_buffer_desc *buf_desc;
	पूर्णांक buf_sz = RTK_PCI_RX_BUF_SIZE;
	dma_addr_t dma;

	अगर (!skb)
		वापस -EINVAL;

	dma = dma_map_single(&pdev->dev, skb->data, buf_sz, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&pdev->dev, dma))
		वापस -EBUSY;

	*((dma_addr_t *)skb->cb) = dma;
	buf_desc = (काष्ठा rtw_pci_rx_buffer_desc *)(rx_ring->r.head +
						     idx * desc_sz);
	स_रखो(buf_desc, 0, माप(*buf_desc));
	buf_desc->buf_size = cpu_to_le16(RTK_PCI_RX_BUF_SIZE);
	buf_desc->dma = cpu_to_le32(dma);

	वापस 0;
पूर्ण

अटल व्योम rtw_pci_sync_rx_desc_device(काष्ठा rtw_dev *rtwdev, dma_addr_t dma,
					काष्ठा rtw_pci_rx_ring *rx_ring,
					u32 idx, u32 desc_sz)
अणु
	काष्ठा device *dev = rtwdev->dev;
	काष्ठा rtw_pci_rx_buffer_desc *buf_desc;
	पूर्णांक buf_sz = RTK_PCI_RX_BUF_SIZE;

	dma_sync_single_क्रम_device(dev, dma, buf_sz, DMA_FROM_DEVICE);

	buf_desc = (काष्ठा rtw_pci_rx_buffer_desc *)(rx_ring->r.head +
						     idx * desc_sz);
	स_रखो(buf_desc, 0, माप(*buf_desc));
	buf_desc->buf_size = cpu_to_le16(RTK_PCI_RX_BUF_SIZE);
	buf_desc->dma = cpu_to_le32(dma);
पूर्ण

अटल पूर्णांक rtw_pci_init_rx_ring(काष्ठा rtw_dev *rtwdev,
				काष्ठा rtw_pci_rx_ring *rx_ring,
				u8 desc_size, u32 len)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(rtwdev->dev);
	काष्ठा sk_buff *skb = शून्य;
	dma_addr_t dma;
	u8 *head;
	पूर्णांक ring_sz = desc_size * len;
	पूर्णांक buf_sz = RTK_PCI_RX_BUF_SIZE;
	पूर्णांक i, allocated;
	पूर्णांक ret = 0;

	अगर (len > TRX_BD_IDX_MASK) अणु
		rtw_err(rtwdev, "len %d exceeds maximum RX entries\n", len);
		वापस -EINVAL;
	पूर्ण

	head = dma_alloc_coherent(&pdev->dev, ring_sz, &dma, GFP_KERNEL);
	अगर (!head) अणु
		rtw_err(rtwdev, "failed to allocate rx ring\n");
		वापस -ENOMEM;
	पूर्ण
	rx_ring->r.head = head;

	क्रम (i = 0; i < len; i++) अणु
		skb = dev_alloc_skb(buf_sz);
		अगर (!skb) अणु
			allocated = i;
			ret = -ENOMEM;
			जाओ err_out;
		पूर्ण

		स_रखो(skb->data, 0, buf_sz);
		rx_ring->buf[i] = skb;
		ret = rtw_pci_reset_rx_desc(rtwdev, skb, rx_ring, i, desc_size);
		अगर (ret) अणु
			allocated = i;
			dev_kमुक्त_skb_any(skb);
			जाओ err_out;
		पूर्ण
	पूर्ण

	rx_ring->r.dma = dma;
	rx_ring->r.len = len;
	rx_ring->r.desc_size = desc_size;
	rx_ring->r.wp = 0;
	rx_ring->r.rp = 0;

	वापस 0;

err_out:
	क्रम (i = 0; i < allocated; i++) अणु
		skb = rx_ring->buf[i];
		अगर (!skb)
			जारी;
		dma = *((dma_addr_t *)skb->cb);
		dma_unmap_single(&pdev->dev, dma, buf_sz, DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		rx_ring->buf[i] = शून्य;
	पूर्ण
	dma_मुक्त_coherent(&pdev->dev, ring_sz, head, dma);

	rtw_err(rtwdev, "failed to init rx buffer\n");

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_pci_init_trx_ring(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_pci_tx_ring *tx_ring;
	काष्ठा rtw_pci_rx_ring *rx_ring;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	पूर्णांक i = 0, j = 0, tx_alloced = 0, rx_alloced = 0;
	पूर्णांक tx_desc_size, rx_desc_size;
	u32 len;
	पूर्णांक ret;

	tx_desc_size = chip->tx_buf_desc_sz;

	क्रम (i = 0; i < RTK_MAX_TX_QUEUE_NUM; i++) अणु
		tx_ring = &rtwpci->tx_rings[i];
		len = max_num_of_tx_queue(i);
		ret = rtw_pci_init_tx_ring(rtwdev, tx_ring, tx_desc_size, len);
		अगर (ret)
			जाओ out;
	पूर्ण

	rx_desc_size = chip->rx_buf_desc_sz;

	क्रम (j = 0; j < RTK_MAX_RX_QUEUE_NUM; j++) अणु
		rx_ring = &rtwpci->rx_rings[j];
		ret = rtw_pci_init_rx_ring(rtwdev, rx_ring, rx_desc_size,
					   RTK_MAX_RX_DESC_NUM);
		अगर (ret)
			जाओ out;
	पूर्ण

	वापस 0;

out:
	tx_alloced = i;
	क्रम (i = 0; i < tx_alloced; i++) अणु
		tx_ring = &rtwpci->tx_rings[i];
		rtw_pci_मुक्त_tx_ring(rtwdev, tx_ring);
	पूर्ण

	rx_alloced = j;
	क्रम (j = 0; j < rx_alloced; j++) अणु
		rx_ring = &rtwpci->rx_rings[j];
		rtw_pci_मुक्त_rx_ring(rtwdev, rx_ring);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rtw_pci_deinit(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_pci_मुक्त_trx_ring(rtwdev);
पूर्ण

अटल पूर्णांक rtw_pci_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	पूर्णांक ret = 0;

	rtwpci->irq_mask[0] = IMR_HIGHDOK |
			      IMR_MGNTDOK |
			      IMR_BKDOK |
			      IMR_BEDOK |
			      IMR_VIDOK |
			      IMR_VODOK |
			      IMR_ROK |
			      IMR_BCNDMAINT_E |
			      IMR_C2HCMD |
			      0;
	rtwpci->irq_mask[1] = IMR_TXFOVW |
			      0;
	rtwpci->irq_mask[3] = IMR_H2CDOK |
			      0;
	spin_lock_init(&rtwpci->irq_lock);
	spin_lock_init(&rtwpci->hwirq_lock);
	ret = rtw_pci_init_trx_ring(rtwdev);

	वापस ret;
पूर्ण

अटल व्योम rtw_pci_reset_buf_desc(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	u32 len;
	u8 पंचांगp;
	dma_addr_t dma;

	पंचांगp = rtw_पढ़ो8(rtwdev, RTK_PCI_CTRL + 3);
	rtw_ग_लिखो8(rtwdev, RTK_PCI_CTRL + 3, पंचांगp | 0xf7);

	dma = rtwpci->tx_rings[RTW_TX_QUEUE_BCN].r.dma;
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_BCNQ, dma);

	अगर (!rtw_chip_wcpu_11n(rtwdev)) अणु
		len = rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.len;
		dma = rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.dma;
		rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.rp = 0;
		rtwpci->tx_rings[RTW_TX_QUEUE_H2C].r.wp = 0;
		rtw_ग_लिखो16(rtwdev, RTK_PCI_TXBD_NUM_H2CQ, len & TRX_BD_IDX_MASK);
		rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_H2CQ, dma);
	पूर्ण

	len = rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_BK].r.wp = 0;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_TXBD_NUM_BKQ, len & TRX_BD_IDX_MASK);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_BKQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_BE].r.wp = 0;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_TXBD_NUM_BEQ, len & TRX_BD_IDX_MASK);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_BEQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_VO].r.wp = 0;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_TXBD_NUM_VOQ, len & TRX_BD_IDX_MASK);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_VOQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_VI].r.wp = 0;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_TXBD_NUM_VIQ, len & TRX_BD_IDX_MASK);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_VIQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_MGMT].r.wp = 0;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_TXBD_NUM_MGMTQ, len & TRX_BD_IDX_MASK);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_MGMTQ, dma);

	len = rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.len;
	dma = rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.dma;
	rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.rp = 0;
	rtwpci->tx_rings[RTW_TX_QUEUE_HI0].r.wp = 0;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_TXBD_NUM_HI0Q, len & TRX_BD_IDX_MASK);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_DESA_HI0Q, dma);

	len = rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.len;
	dma = rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.dma;
	rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.rp = 0;
	rtwpci->rx_rings[RTW_RX_QUEUE_MPDU].r.wp = 0;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_RXBD_NUM_MPDUQ, len & TRX_BD_IDX_MASK);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_RXBD_DESA_MPDUQ, dma);

	/* reset पढ़ो/ग_लिखो poपूर्णांक */
	rtw_ग_लिखो32(rtwdev, RTK_PCI_TXBD_RWPTR_CLR, 0xffffffff);

	/* reset H2C Queue index in a single ग_लिखो */
	अगर (rtw_chip_wcpu_11ac(rtwdev))
		rtw_ग_लिखो32_set(rtwdev, RTK_PCI_TXBD_H2CQ_CSR,
				BIT_CLR_H2CQ_HOST_IDX | BIT_CLR_H2CQ_HW_IDX);
पूर्ण

अटल व्योम rtw_pci_reset_trx_ring(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_pci_reset_buf_desc(rtwdev);
पूर्ण

अटल व्योम rtw_pci_enable_पूर्णांकerrupt(काष्ठा rtw_dev *rtwdev,
				     काष्ठा rtw_pci *rtwpci, bool exclude_rx)
अणु
	अचिन्हित दीर्घ flags;
	u32 imr0_unmask = exclude_rx ? IMR_ROK : 0;

	spin_lock_irqsave(&rtwpci->hwirq_lock, flags);

	rtw_ग_लिखो32(rtwdev, RTK_PCI_HIMR0, rtwpci->irq_mask[0] & ~imr0_unmask);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_HIMR1, rtwpci->irq_mask[1]);
	अगर (rtw_chip_wcpu_11ac(rtwdev))
		rtw_ग_लिखो32(rtwdev, RTK_PCI_HIMR3, rtwpci->irq_mask[3]);

	rtwpci->irq_enabled = true;

	spin_unlock_irqrestore(&rtwpci->hwirq_lock, flags);
पूर्ण

अटल व्योम rtw_pci_disable_पूर्णांकerrupt(काष्ठा rtw_dev *rtwdev,
				      काष्ठा rtw_pci *rtwpci)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtwpci->hwirq_lock, flags);

	अगर (!rtwpci->irq_enabled)
		जाओ out;

	rtw_ग_लिखो32(rtwdev, RTK_PCI_HIMR0, 0);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_HIMR1, 0);
	अगर (rtw_chip_wcpu_11ac(rtwdev))
		rtw_ग_लिखो32(rtwdev, RTK_PCI_HIMR3, 0);

	rtwpci->irq_enabled = false;

out:
	spin_unlock_irqrestore(&rtwpci->hwirq_lock, flags);
पूर्ण

अटल व्योम rtw_pci_dma_reset(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_pci *rtwpci)
अणु
	/* reset dma and rx tag */
	rtw_ग_लिखो32_set(rtwdev, RTK_PCI_CTRL,
			BIT_RST_TRXDMA_INTF | BIT_RX_TAG_EN);
	rtwpci->rx_tag = 0;
पूर्ण

अटल पूर्णांक rtw_pci_setup(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	rtw_pci_reset_trx_ring(rtwdev);
	rtw_pci_dma_reset(rtwdev, rtwpci);

	वापस 0;
पूर्ण

अटल व्योम rtw_pci_dma_release(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_pci *rtwpci)
अणु
	काष्ठा rtw_pci_tx_ring *tx_ring;
	u8 queue;

	rtw_pci_reset_trx_ring(rtwdev);
	क्रम (queue = 0; queue < RTK_MAX_TX_QUEUE_NUM; queue++) अणु
		tx_ring = &rtwpci->tx_rings[queue];
		rtw_pci_मुक्त_tx_ring_skbs(rtwdev, tx_ring);
	पूर्ण
पूर्ण

अटल व्योम rtw_pci_napi_start(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	अगर (test_and_set_bit(RTW_PCI_FLAG_NAPI_RUNNING, rtwpci->flags))
		वापस;

	napi_enable(&rtwpci->napi);
पूर्ण

अटल व्योम rtw_pci_napi_stop(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	अगर (!test_and_clear_bit(RTW_PCI_FLAG_NAPI_RUNNING, rtwpci->flags))
		वापस;

	napi_synchronize(&rtwpci->napi);
	napi_disable(&rtwpci->napi);
पूर्ण

अटल पूर्णांक rtw_pci_start(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	rtw_pci_napi_start(rtwdev);

	spin_lock_bh(&rtwpci->irq_lock);
	rtwpci->running = true;
	rtw_pci_enable_पूर्णांकerrupt(rtwdev, rtwpci, false);
	spin_unlock_bh(&rtwpci->irq_lock);

	वापस 0;
पूर्ण

अटल व्योम rtw_pci_stop(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा pci_dev *pdev = rtwpci->pdev;

	spin_lock_bh(&rtwpci->irq_lock);
	rtwpci->running = false;
	rtw_pci_disable_पूर्णांकerrupt(rtwdev, rtwpci);
	spin_unlock_bh(&rtwpci->irq_lock);

	synchronize_irq(pdev->irq);
	rtw_pci_napi_stop(rtwdev);

	spin_lock_bh(&rtwpci->irq_lock);
	rtw_pci_dma_release(rtwdev, rtwpci);
	spin_unlock_bh(&rtwpci->irq_lock);
पूर्ण

अटल व्योम rtw_pci_deep_ps_enter(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_pci_tx_ring *tx_ring;
	bool tx_empty = true;
	u8 queue;

	lockdep_निश्चित_held(&rtwpci->irq_lock);

	/* Deep PS state is not allowed to TX-DMA */
	क्रम (queue = 0; queue < RTK_MAX_TX_QUEUE_NUM; queue++) अणु
		/* BCN queue is rsvd page, करोes not have DMA पूर्णांकerrupt
		 * H2C queue is managed by firmware
		 */
		अगर (queue == RTW_TX_QUEUE_BCN ||
		    queue == RTW_TX_QUEUE_H2C)
			जारी;

		tx_ring = &rtwpci->tx_rings[queue];

		/* check अगर there is any skb DMAing */
		अगर (skb_queue_len(&tx_ring->queue)) अणु
			tx_empty = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tx_empty) अणु
		rtw_dbg(rtwdev, RTW_DBG_PS,
			"TX path not empty, cannot enter deep power save state\n");
		वापस;
	पूर्ण

	set_bit(RTW_FLAG_LEISURE_PS_DEEP, rtwdev->flags);
	rtw_घातer_mode_change(rtwdev, true);
पूर्ण

अटल व्योम rtw_pci_deep_ps_leave(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	lockdep_निश्चित_held(&rtwpci->irq_lock);

	अगर (test_and_clear_bit(RTW_FLAG_LEISURE_PS_DEEP, rtwdev->flags))
		rtw_घातer_mode_change(rtwdev, false);
पूर्ण

अटल व्योम rtw_pci_deep_ps(काष्ठा rtw_dev *rtwdev, bool enter)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	spin_lock_bh(&rtwpci->irq_lock);

	अगर (enter && !test_bit(RTW_FLAG_LEISURE_PS_DEEP, rtwdev->flags))
		rtw_pci_deep_ps_enter(rtwdev);

	अगर (!enter && test_bit(RTW_FLAG_LEISURE_PS_DEEP, rtwdev->flags))
		rtw_pci_deep_ps_leave(rtwdev);

	spin_unlock_bh(&rtwpci->irq_lock);
पूर्ण

अटल u8 ac_to_hwq[] = अणु
	[IEEE80211_AC_VO] = RTW_TX_QUEUE_VO,
	[IEEE80211_AC_VI] = RTW_TX_QUEUE_VI,
	[IEEE80211_AC_BE] = RTW_TX_QUEUE_BE,
	[IEEE80211_AC_BK] = RTW_TX_QUEUE_BK,
पूर्ण;

अटल_निश्चित(ARRAY_SIZE(ac_to_hwq) == IEEE80211_NUM_ACS);

अटल u8 rtw_hw_queue_mapping(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	__le16 fc = hdr->frame_control;
	u8 q_mapping = skb_get_queue_mapping(skb);
	u8 queue;

	अगर (unlikely(ieee80211_is_beacon(fc)))
		queue = RTW_TX_QUEUE_BCN;
	अन्यथा अगर (unlikely(ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc)))
		queue = RTW_TX_QUEUE_MGMT;
	अन्यथा अगर (WARN_ON_ONCE(q_mapping >= ARRAY_SIZE(ac_to_hwq)))
		queue = ac_to_hwq[IEEE80211_AC_BE];
	अन्यथा
		queue = ac_to_hwq[q_mapping];

	वापस queue;
पूर्ण

अटल व्योम rtw_pci_release_rsvd_page(काष्ठा rtw_pci *rtwpci,
				      काष्ठा rtw_pci_tx_ring *ring)
अणु
	काष्ठा sk_buff *prev = skb_dequeue(&ring->queue);
	काष्ठा rtw_pci_tx_data *tx_data;
	dma_addr_t dma;

	अगर (!prev)
		वापस;

	tx_data = rtw_pci_get_tx_data(prev);
	dma = tx_data->dma;
	dma_unmap_single(&rtwpci->pdev->dev, dma, prev->len, DMA_TO_DEVICE);
	dev_kमुक्त_skb_any(prev);
पूर्ण

अटल व्योम rtw_pci_dma_check(काष्ठा rtw_dev *rtwdev,
			      काष्ठा rtw_pci_rx_ring *rx_ring,
			      u32 idx)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_pci_rx_buffer_desc *buf_desc;
	u32 desc_sz = chip->rx_buf_desc_sz;
	u16 total_pkt_size;

	buf_desc = (काष्ठा rtw_pci_rx_buffer_desc *)(rx_ring->r.head +
						     idx * desc_sz);
	total_pkt_size = le16_to_cpu(buf_desc->total_pkt_size);

	/* rx tag mismatch, throw a warning */
	अगर (total_pkt_size != rtwpci->rx_tag)
		rtw_warn(rtwdev, "pci bus timeout, check dma status\n");

	rtwpci->rx_tag = (rtwpci->rx_tag + 1) % RX_TAG_MAX;
पूर्ण

अटल u32 __pci_get_hw_tx_ring_rp(काष्ठा rtw_dev *rtwdev, u8 pci_q)
अणु
	u32 bd_idx_addr = rtw_pci_tx_queue_idx_addr[pci_q];
	u32 bd_idx = rtw_पढ़ो16(rtwdev, bd_idx_addr + 2);

	वापस FIELD_GET(TRX_BD_IDX_MASK, bd_idx);
पूर्ण

अटल व्योम __pci_flush_queue(काष्ठा rtw_dev *rtwdev, u8 pci_q, bool drop)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_pci_tx_ring *ring = &rtwpci->tx_rings[pci_q];
	u32 cur_rp;
	u8 i;

	/* Because the समय taked by the I/O in __pci_get_hw_tx_ring_rp is a
	 * bit dynamic, it's hard to define a reasonable fixed total समयout to
	 * use पढ़ो_poll_समयout* helper. Instead, we can ensure a reasonable
	 * polling बार, so we just use क्रम loop with udelay here.
	 */
	क्रम (i = 0; i < 30; i++) अणु
		cur_rp = __pci_get_hw_tx_ring_rp(rtwdev, pci_q);
		अगर (cur_rp == ring->r.wp)
			वापस;

		udelay(1);
	पूर्ण

	अगर (!drop)
		rtw_warn(rtwdev, "timed out to flush pci tx ring[%d]\n", pci_q);
पूर्ण

अटल व्योम __rtw_pci_flush_queues(काष्ठा rtw_dev *rtwdev, u32 pci_queues,
				   bool drop)
अणु
	u8 q;

	क्रम (q = 0; q < RTK_MAX_TX_QUEUE_NUM; q++) अणु
		/* It may be not necessary to flush BCN and H2C tx queues. */
		अगर (q == RTW_TX_QUEUE_BCN || q == RTW_TX_QUEUE_H2C)
			जारी;

		अगर (pci_queues & BIT(q))
			__pci_flush_queue(rtwdev, q, drop);
	पूर्ण
पूर्ण

अटल व्योम rtw_pci_flush_queues(काष्ठा rtw_dev *rtwdev, u32 queues, bool drop)
अणु
	u32 pci_queues = 0;
	u8 i;

	/* If all of the hardware queues are requested to flush,
	 * flush all of the pci queues.
	 */
	अगर (queues == BIT(rtwdev->hw->queues) - 1) अणु
		pci_queues = BIT(RTK_MAX_TX_QUEUE_NUM) - 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < rtwdev->hw->queues; i++)
			अगर (queues & BIT(i))
				pci_queues |= BIT(ac_to_hwq[i]);
	पूर्ण

	__rtw_pci_flush_queues(rtwdev, pci_queues, drop);
पूर्ण

अटल व्योम rtw_pci_tx_kick_off_queue(काष्ठा rtw_dev *rtwdev, u8 queue)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_pci_tx_ring *ring;
	u32 bd_idx;

	ring = &rtwpci->tx_rings[queue];
	bd_idx = rtw_pci_tx_queue_idx_addr[queue];

	spin_lock_bh(&rtwpci->irq_lock);
	rtw_pci_deep_ps_leave(rtwdev);
	rtw_ग_लिखो16(rtwdev, bd_idx, ring->r.wp & TRX_BD_IDX_MASK);
	spin_unlock_bh(&rtwpci->irq_lock);
पूर्ण

अटल व्योम rtw_pci_tx_kick_off(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	u8 queue;

	क्रम (queue = 0; queue < RTK_MAX_TX_QUEUE_NUM; queue++)
		अगर (test_and_clear_bit(queue, rtwpci->tx_queued))
			rtw_pci_tx_kick_off_queue(rtwdev, queue);
पूर्ण

अटल पूर्णांक rtw_pci_tx_ग_लिखो_data(काष्ठा rtw_dev *rtwdev,
				 काष्ठा rtw_tx_pkt_info *pkt_info,
				 काष्ठा sk_buff *skb, u8 queue)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_pci_tx_ring *ring;
	काष्ठा rtw_pci_tx_data *tx_data;
	dma_addr_t dma;
	u32 tx_pkt_desc_sz = chip->tx_pkt_desc_sz;
	u32 tx_buf_desc_sz = chip->tx_buf_desc_sz;
	u32 size;
	u32 psb_len;
	u8 *pkt_desc;
	काष्ठा rtw_pci_tx_buffer_desc *buf_desc;

	ring = &rtwpci->tx_rings[queue];

	size = skb->len;

	अगर (queue == RTW_TX_QUEUE_BCN)
		rtw_pci_release_rsvd_page(rtwpci, ring);
	अन्यथा अगर (!avail_desc(ring->r.wp, ring->r.rp, ring->r.len))
		वापस -ENOSPC;

	pkt_desc = skb_push(skb, chip->tx_pkt_desc_sz);
	स_रखो(pkt_desc, 0, tx_pkt_desc_sz);
	pkt_info->qsel = rtw_pci_get_tx_qsel(skb, queue);
	rtw_tx_fill_tx_desc(pkt_info, skb);
	dma = dma_map_single(&rtwpci->pdev->dev, skb->data, skb->len,
			     DMA_TO_DEVICE);
	अगर (dma_mapping_error(&rtwpci->pdev->dev, dma))
		वापस -EBUSY;

	/* after this we got dma mapped, there is no way back */
	buf_desc = get_tx_buffer_desc(ring, tx_buf_desc_sz);
	स_रखो(buf_desc, 0, tx_buf_desc_sz);
	psb_len = (skb->len - 1) / 128 + 1;
	अगर (queue == RTW_TX_QUEUE_BCN)
		psb_len |= 1 << RTK_PCI_TXBD_OWN_OFFSET;

	buf_desc[0].psb_len = cpu_to_le16(psb_len);
	buf_desc[0].buf_size = cpu_to_le16(tx_pkt_desc_sz);
	buf_desc[0].dma = cpu_to_le32(dma);
	buf_desc[1].buf_size = cpu_to_le16(size);
	buf_desc[1].dma = cpu_to_le32(dma + tx_pkt_desc_sz);

	tx_data = rtw_pci_get_tx_data(skb);
	tx_data->dma = dma;
	tx_data->sn = pkt_info->sn;

	spin_lock_bh(&rtwpci->irq_lock);

	skb_queue_tail(&ring->queue, skb);

	अगर (queue == RTW_TX_QUEUE_BCN)
		जाओ out_unlock;

	/* update ग_लिखो-index, and kick it off later */
	set_bit(queue, rtwpci->tx_queued);
	अगर (++ring->r.wp >= ring->r.len)
		ring->r.wp = 0;

out_unlock:
	spin_unlock_bh(&rtwpci->irq_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_pci_ग_लिखो_data_rsvd_page(काष्ठा rtw_dev *rtwdev, u8 *buf,
					u32 size)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtw_tx_pkt_info pkt_info = अणु0पूर्ण;
	u8 reg_bcn_work;
	पूर्णांक ret;

	skb = rtw_tx_ग_लिखो_data_rsvd_page_get(rtwdev, &pkt_info, buf, size);
	अगर (!skb)
		वापस -ENOMEM;

	ret = rtw_pci_tx_ग_लिखो_data(rtwdev, &pkt_info, skb, RTW_TX_QUEUE_BCN);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to write rsvd page data\n");
		वापस ret;
	पूर्ण

	/* reserved pages go through beacon queue */
	reg_bcn_work = rtw_पढ़ो8(rtwdev, RTK_PCI_TXBD_BCN_WORK);
	reg_bcn_work |= BIT_PCI_BCNQ_FLAG;
	rtw_ग_लिखो8(rtwdev, RTK_PCI_TXBD_BCN_WORK, reg_bcn_work);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_pci_ग_लिखो_data_h2c(काष्ठा rtw_dev *rtwdev, u8 *buf, u32 size)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rtw_tx_pkt_info pkt_info = अणु0पूर्ण;
	पूर्णांक ret;

	skb = rtw_tx_ग_लिखो_data_h2c_get(rtwdev, &pkt_info, buf, size);
	अगर (!skb)
		वापस -ENOMEM;

	ret = rtw_pci_tx_ग_लिखो_data(rtwdev, &pkt_info, skb, RTW_TX_QUEUE_H2C);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to write h2c data\n");
		वापस ret;
	पूर्ण

	rtw_pci_tx_kick_off_queue(rtwdev, RTW_TX_QUEUE_H2C);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_pci_tx_ग_लिखो(काष्ठा rtw_dev *rtwdev,
			    काष्ठा rtw_tx_pkt_info *pkt_info,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा rtw_pci_tx_ring *ring;
	u8 queue = rtw_hw_queue_mapping(skb);
	पूर्णांक ret;

	ret = rtw_pci_tx_ग_लिखो_data(rtwdev, pkt_info, skb, queue);
	अगर (ret)
		वापस ret;

	ring = &rtwpci->tx_rings[queue];
	spin_lock_bh(&rtwpci->irq_lock);
	अगर (avail_desc(ring->r.wp, ring->r.rp, ring->r.len) < 2) अणु
		ieee80211_stop_queue(rtwdev->hw, skb_get_queue_mapping(skb));
		ring->queue_stopped = true;
	पूर्ण
	spin_unlock_bh(&rtwpci->irq_lock);

	वापस 0;
पूर्ण

अटल व्योम rtw_pci_tx_isr(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_pci *rtwpci,
			   u8 hw_queue)
अणु
	काष्ठा ieee80211_hw *hw = rtwdev->hw;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा rtw_pci_tx_ring *ring;
	काष्ठा rtw_pci_tx_data *tx_data;
	काष्ठा sk_buff *skb;
	u32 count;
	u32 bd_idx_addr;
	u32 bd_idx, cur_rp, rp_idx;
	u16 q_map;

	ring = &rtwpci->tx_rings[hw_queue];

	bd_idx_addr = rtw_pci_tx_queue_idx_addr[hw_queue];
	bd_idx = rtw_पढ़ो32(rtwdev, bd_idx_addr);
	cur_rp = bd_idx >> 16;
	cur_rp &= TRX_BD_IDX_MASK;
	rp_idx = ring->r.rp;
	अगर (cur_rp >= ring->r.rp)
		count = cur_rp - ring->r.rp;
	अन्यथा
		count = ring->r.len - (ring->r.rp - cur_rp);

	जबतक (count--) अणु
		skb = skb_dequeue(&ring->queue);
		अगर (!skb) अणु
			rtw_err(rtwdev, "failed to dequeue %d skb TX queue %d, BD=0x%08x, rp %d -> %d\n",
				count, hw_queue, bd_idx, ring->r.rp, cur_rp);
			अवरोध;
		पूर्ण
		tx_data = rtw_pci_get_tx_data(skb);
		dma_unmap_single(&rtwpci->pdev->dev, tx_data->dma, skb->len,
				 DMA_TO_DEVICE);

		/* just मुक्त command packets from host to card */
		अगर (hw_queue == RTW_TX_QUEUE_H2C) अणु
			dev_kमुक्त_skb_irq(skb);
			जारी;
		पूर्ण

		अगर (ring->queue_stopped &&
		    avail_desc(ring->r.wp, rp_idx, ring->r.len) > 4) अणु
			q_map = skb_get_queue_mapping(skb);
			ieee80211_wake_queue(hw, q_map);
			ring->queue_stopped = false;
		पूर्ण

		अगर (++rp_idx >= ring->r.len)
			rp_idx = 0;

		skb_pull(skb, rtwdev->chip->tx_pkt_desc_sz);

		info = IEEE80211_SKB_CB(skb);

		/* enqueue to रुको क्रम tx report */
		अगर (info->flags & IEEE80211_TX_CTL_REQ_TX_STATUS) अणु
			rtw_tx_report_enqueue(rtwdev, skb, tx_data->sn);
			जारी;
		पूर्ण

		/* always ACK क्रम others, then they won't be marked as drop */
		अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
			info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		अन्यथा
			info->flags |= IEEE80211_TX_STAT_ACK;

		ieee80211_tx_info_clear_status(info);
		ieee80211_tx_status_irqsafe(hw, skb);
	पूर्ण

	ring->r.rp = cur_rp;
पूर्ण

अटल व्योम rtw_pci_rx_isr(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा napi_काष्ठा *napi = &rtwpci->napi;

	napi_schedule(napi);
पूर्ण

अटल पूर्णांक rtw_pci_get_hw_rx_ring_nr(काष्ठा rtw_dev *rtwdev,
				     काष्ठा rtw_pci *rtwpci)
अणु
	काष्ठा rtw_pci_rx_ring *ring;
	पूर्णांक count = 0;
	u32 पंचांगp, cur_wp;

	ring = &rtwpci->rx_rings[RTW_RX_QUEUE_MPDU];
	पंचांगp = rtw_पढ़ो32(rtwdev, RTK_PCI_RXBD_IDX_MPDUQ);
	cur_wp = u32_get_bits(पंचांगp, TRX_BD_HW_IDX_MASK);
	अगर (cur_wp >= ring->r.wp)
		count = cur_wp - ring->r.wp;
	अन्यथा
		count = ring->r.len - (ring->r.wp - cur_wp);

	वापस count;
पूर्ण

अटल u32 rtw_pci_rx_napi(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_pci *rtwpci,
			   u8 hw_queue, u32 limit)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा napi_काष्ठा *napi = &rtwpci->napi;
	काष्ठा rtw_pci_rx_ring *ring = &rtwpci->rx_rings[RTW_RX_QUEUE_MPDU];
	काष्ठा rtw_rx_pkt_stat pkt_stat;
	काष्ठा ieee80211_rx_status rx_status;
	काष्ठा sk_buff *skb, *new;
	u32 cur_rp = ring->r.rp;
	u32 count, rx_करोne = 0;
	u32 pkt_offset;
	u32 pkt_desc_sz = chip->rx_pkt_desc_sz;
	u32 buf_desc_sz = chip->rx_buf_desc_sz;
	u32 new_len;
	u8 *rx_desc;
	dma_addr_t dma;

	count = rtw_pci_get_hw_rx_ring_nr(rtwdev, rtwpci);
	count = min(count, limit);

	जबतक (count--) अणु
		rtw_pci_dma_check(rtwdev, ring, cur_rp);
		skb = ring->buf[cur_rp];
		dma = *((dma_addr_t *)skb->cb);
		dma_sync_single_क्रम_cpu(rtwdev->dev, dma, RTK_PCI_RX_BUF_SIZE,
					DMA_FROM_DEVICE);
		rx_desc = skb->data;
		chip->ops->query_rx_desc(rtwdev, rx_desc, &pkt_stat, &rx_status);

		/* offset from rx_desc to payload */
		pkt_offset = pkt_desc_sz + pkt_stat.drv_info_sz +
			     pkt_stat.shअगरt;

		/* allocate a new skb क्रम this frame,
		 * discard the frame अगर none available
		 */
		new_len = pkt_stat.pkt_len + pkt_offset;
		new = dev_alloc_skb(new_len);
		अगर (WARN_ONCE(!new, "rx routine starvation\n"))
			जाओ next_rp;

		/* put the DMA data including rx_desc from phy to new skb */
		skb_put_data(new, skb->data, new_len);

		अगर (pkt_stat.is_c2h) अणु
			rtw_fw_c2h_cmd_rx_irqsafe(rtwdev, pkt_offset, new);
		पूर्ण अन्यथा अणु
			/* हटाओ rx_desc */
			skb_pull(new, pkt_offset);

			rtw_rx_stats(rtwdev, pkt_stat.vअगर, new);
			स_नकल(new->cb, &rx_status, माप(rx_status));
			ieee80211_rx_napi(rtwdev->hw, शून्य, new, napi);
			rx_करोne++;
		पूर्ण

next_rp:
		/* new skb delivered to mac80211, re-enable original skb DMA */
		rtw_pci_sync_rx_desc_device(rtwdev, dma, ring, cur_rp,
					    buf_desc_sz);

		/* host पढ़ो next element in ring */
		अगर (++cur_rp >= ring->r.len)
			cur_rp = 0;
	पूर्ण

	ring->r.rp = cur_rp;
	/* 'rp', the last position we have पढ़ो, is seen as previous posistion
	 * of 'wp' that is used to calculate 'count' next समय.
	 */
	ring->r.wp = cur_rp;
	rtw_ग_लिखो16(rtwdev, RTK_PCI_RXBD_IDX_MPDUQ, ring->r.rp);

	वापस rx_करोne;
पूर्ण

अटल व्योम rtw_pci_irq_recognized(काष्ठा rtw_dev *rtwdev,
				   काष्ठा rtw_pci *rtwpci, u32 *irq_status)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtwpci->hwirq_lock, flags);

	irq_status[0] = rtw_पढ़ो32(rtwdev, RTK_PCI_HISR0);
	irq_status[1] = rtw_पढ़ो32(rtwdev, RTK_PCI_HISR1);
	अगर (rtw_chip_wcpu_11ac(rtwdev))
		irq_status[3] = rtw_पढ़ो32(rtwdev, RTK_PCI_HISR3);
	अन्यथा
		irq_status[3] = 0;
	irq_status[0] &= rtwpci->irq_mask[0];
	irq_status[1] &= rtwpci->irq_mask[1];
	irq_status[3] &= rtwpci->irq_mask[3];
	rtw_ग_लिखो32(rtwdev, RTK_PCI_HISR0, irq_status[0]);
	rtw_ग_लिखो32(rtwdev, RTK_PCI_HISR1, irq_status[1]);
	अगर (rtw_chip_wcpu_11ac(rtwdev))
		rtw_ग_लिखो32(rtwdev, RTK_PCI_HISR3, irq_status[3]);

	spin_unlock_irqrestore(&rtwpci->hwirq_lock, flags);
पूर्ण

अटल irqवापस_t rtw_pci_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा rtw_dev *rtwdev = dev;
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	/* disable RTW PCI पूर्णांकerrupt to aव्योम more पूर्णांकerrupts beक्रमe the end of
	 * thपढ़ो function
	 *
	 * disable HIMR here to also aव्योम new HISR flag being उठाओd beक्रमe
	 * the HISRs have been Write-1-cleared क्रम MSI. If not all of the HISRs
	 * are cleared, the edge-triggered पूर्णांकerrupt will not be generated when
	 * a new HISR flag is set.
	 */
	rtw_pci_disable_पूर्णांकerrupt(rtwdev, rtwpci);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t rtw_pci_पूर्णांकerrupt_thपढ़ोfn(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा rtw_dev *rtwdev = dev;
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	u32 irq_status[4];
	bool rx = false;

	spin_lock_bh(&rtwpci->irq_lock);
	rtw_pci_irq_recognized(rtwdev, rtwpci, irq_status);

	अगर (irq_status[0] & IMR_MGNTDOK)
		rtw_pci_tx_isr(rtwdev, rtwpci, RTW_TX_QUEUE_MGMT);
	अगर (irq_status[0] & IMR_HIGHDOK)
		rtw_pci_tx_isr(rtwdev, rtwpci, RTW_TX_QUEUE_HI0);
	अगर (irq_status[0] & IMR_BEDOK)
		rtw_pci_tx_isr(rtwdev, rtwpci, RTW_TX_QUEUE_BE);
	अगर (irq_status[0] & IMR_BKDOK)
		rtw_pci_tx_isr(rtwdev, rtwpci, RTW_TX_QUEUE_BK);
	अगर (irq_status[0] & IMR_VODOK)
		rtw_pci_tx_isr(rtwdev, rtwpci, RTW_TX_QUEUE_VO);
	अगर (irq_status[0] & IMR_VIDOK)
		rtw_pci_tx_isr(rtwdev, rtwpci, RTW_TX_QUEUE_VI);
	अगर (irq_status[3] & IMR_H2CDOK)
		rtw_pci_tx_isr(rtwdev, rtwpci, RTW_TX_QUEUE_H2C);
	अगर (irq_status[0] & IMR_ROK) अणु
		rtw_pci_rx_isr(rtwdev);
		rx = true;
	पूर्ण
	अगर (unlikely(irq_status[0] & IMR_C2HCMD))
		rtw_fw_c2h_cmd_isr(rtwdev);

	/* all of the jobs क्रम this पूर्णांकerrupt have been करोne */
	अगर (rtwpci->running)
		rtw_pci_enable_पूर्णांकerrupt(rtwdev, rtwpci, rx);
	spin_unlock_bh(&rtwpci->irq_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rtw_pci_io_mapping(काष्ठा rtw_dev *rtwdev,
			      काष्ठा pci_dev *pdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	अचिन्हित दीर्घ len;
	u8 bar_id = 2;
	पूर्णांक ret;

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to request pci regions\n");
		वापस ret;
	पूर्ण

	len = pci_resource_len(pdev, bar_id);
	rtwpci->mmap = pci_iomap(pdev, bar_id, len);
	अगर (!rtwpci->mmap) अणु
		pci_release_regions(pdev);
		rtw_err(rtwdev, "failed to map pci memory\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtw_pci_io_unmapping(काष्ठा rtw_dev *rtwdev,
				 काष्ठा pci_dev *pdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	अगर (rtwpci->mmap) अणु
		pci_iounmap(pdev, rtwpci->mmap);
		pci_release_regions(pdev);
	पूर्ण
पूर्ण

अटल व्योम rtw_dbi_ग_लिखो8(काष्ठा rtw_dev *rtwdev, u16 addr, u8 data)
अणु
	u16 ग_लिखो_addr;
	u16 reमुख्यder = addr & ~(BITS_DBI_WREN | BITS_DBI_ADDR_MASK);
	u8 flag;
	u8 cnt;

	ग_लिखो_addr = addr & BITS_DBI_ADDR_MASK;
	ग_लिखो_addr |= u16_encode_bits(BIT(reमुख्यder), BITS_DBI_WREN);
	rtw_ग_लिखो8(rtwdev, REG_DBI_WDATA_V1 + reमुख्यder, data);
	rtw_ग_लिखो16(rtwdev, REG_DBI_FLAG_V1, ग_लिखो_addr);
	rtw_ग_लिखो8(rtwdev, REG_DBI_FLAG_V1 + 2, BIT_DBI_WFLAG >> 16);

	क्रम (cnt = 0; cnt < RTW_PCI_WR_RETRY_CNT; cnt++) अणु
		flag = rtw_पढ़ो8(rtwdev, REG_DBI_FLAG_V1 + 2);
		अगर (flag == 0)
			वापस;

		udelay(10);
	पूर्ण

	WARN(flag, "failed to write to DBI register, addr=0x%04x\n", addr);
पूर्ण

अटल पूर्णांक rtw_dbi_पढ़ो8(काष्ठा rtw_dev *rtwdev, u16 addr, u8 *value)
अणु
	u16 पढ़ो_addr = addr & BITS_DBI_ADDR_MASK;
	u8 flag;
	u8 cnt;

	rtw_ग_लिखो16(rtwdev, REG_DBI_FLAG_V1, पढ़ो_addr);
	rtw_ग_लिखो8(rtwdev, REG_DBI_FLAG_V1 + 2, BIT_DBI_RFLAG >> 16);

	क्रम (cnt = 0; cnt < RTW_PCI_WR_RETRY_CNT; cnt++) अणु
		flag = rtw_पढ़ो8(rtwdev, REG_DBI_FLAG_V1 + 2);
		अगर (flag == 0) अणु
			पढ़ो_addr = REG_DBI_RDATA_V1 + (addr & 3);
			*value = rtw_पढ़ो8(rtwdev, पढ़ो_addr);
			वापस 0;
		पूर्ण

		udelay(10);
	पूर्ण

	WARN(1, "failed to read DBI register, addr=0x%04x\n", addr);
	वापस -EIO;
पूर्ण

अटल व्योम rtw_mdio_ग_लिखो(काष्ठा rtw_dev *rtwdev, u8 addr, u16 data, bool g1)
अणु
	u8 page;
	u8 wflag;
	u8 cnt;

	rtw_ग_लिखो16(rtwdev, REG_MDIO_V1, data);

	page = addr < RTW_PCI_MDIO_PG_SZ ? 0 : 1;
	page += g1 ? RTW_PCI_MDIO_PG_OFFS_G1 : RTW_PCI_MDIO_PG_OFFS_G2;
	rtw_ग_लिखो8(rtwdev, REG_PCIE_MIX_CFG, addr & BITS_MDIO_ADDR_MASK);
	rtw_ग_लिखो8(rtwdev, REG_PCIE_MIX_CFG + 3, page);
	rtw_ग_लिखो32_mask(rtwdev, REG_PCIE_MIX_CFG, BIT_MDIO_WFLAG_V1, 1);

	क्रम (cnt = 0; cnt < RTW_PCI_WR_RETRY_CNT; cnt++) अणु
		wflag = rtw_पढ़ो32_mask(rtwdev, REG_PCIE_MIX_CFG,
					BIT_MDIO_WFLAG_V1);
		अगर (wflag == 0)
			वापस;

		udelay(10);
	पूर्ण

	WARN(wflag, "failed to write to MDIO register, addr=0x%02x\n", addr);
पूर्ण

अटल व्योम rtw_pci_clkreq_set(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 value;
	पूर्णांक ret;

	अगर (rtw_pci_disable_aspm)
		वापस;

	ret = rtw_dbi_पढ़ो8(rtwdev, RTK_PCIE_LINK_CFG, &value);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to read CLKREQ_L1, ret=%d", ret);
		वापस;
	पूर्ण

	अगर (enable)
		value |= BIT_CLKREQ_SW_EN;
	अन्यथा
		value &= ~BIT_CLKREQ_SW_EN;

	rtw_dbi_ग_लिखो8(rtwdev, RTK_PCIE_LINK_CFG, value);
पूर्ण

अटल व्योम rtw_pci_aspm_set(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 value;
	पूर्णांक ret;

	अगर (rtw_pci_disable_aspm)
		वापस;

	ret = rtw_dbi_पढ़ो8(rtwdev, RTK_PCIE_LINK_CFG, &value);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to read ASPM, ret=%d", ret);
		वापस;
	पूर्ण

	अगर (enable)
		value |= BIT_L1_SW_EN;
	अन्यथा
		value &= ~BIT_L1_SW_EN;

	rtw_dbi_ग_लिखो8(rtwdev, RTK_PCIE_LINK_CFG, value);
पूर्ण

अटल व्योम rtw_pci_link_ps(काष्ठा rtw_dev *rtwdev, bool enter)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	/* Like CLKREQ, ASPM is also implemented by two HW modules, and can
	 * only be enabled when host supports it.
	 *
	 * And ASPM mechanism should be enabled when driver/firmware enters
	 * घातer save mode, without having heavy traffic. Because we've
	 * experienced some पूर्णांकer-operability issues that the link tends
	 * to enter L1 state on the fly even when driver is having high
	 * throughput. This is probably because the ASPM behavior slightly
	 * varies from dअगरferent SOC.
	 */
	अगर (rtwpci->link_ctrl & PCI_EXP_LNKCTL_ASPM_L1)
		rtw_pci_aspm_set(rtwdev, enter);
पूर्ण

अटल व्योम rtw_pci_link_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	काष्ठा pci_dev *pdev = rtwpci->pdev;
	u16 link_ctrl;
	पूर्णांक ret;

	/* RTL8822CE has enabled REFCLK स्वतः calibration, it करोes not need
	 * to add घड़ी delay to cover the REFCLK timing gap.
	 */
	अगर (chip->id == RTW_CHIP_TYPE_8822C)
		rtw_dbi_ग_लिखो8(rtwdev, RTK_PCIE_CLKDLY_CTRL, 0);

	/* Though there is standard PCIE configuration space to set the
	 * link control रेजिस्टर, but by Realtek's design, driver should
	 * check अगर host supports CLKREQ/ASPM to enable the HW module.
	 *
	 * These functions are implemented by two HW modules associated,
	 * one is responsible to access PCIE configuration space to
	 * follow the host settings, and another is in अक्षरge of करोing
	 * CLKREQ/ASPM mechanisms, it is शेष disabled. Because someबार
	 * the host करोes not support it, and due to some reasons or wrong
	 * settings (ex. CLKREQ# not Bi-Direction), it could lead to device
	 * loss अगर HW misbehaves on the link.
	 *
	 * Hence it's deचिन्हित that driver should first check the PCIE
	 * configuration space is sync'ed and enabled, then driver can turn
	 * on the other module that is actually working on the mechanism.
	 */
	ret = pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL, &link_ctrl);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to read PCI cap, ret=%d\n", ret);
		वापस;
	पूर्ण

	अगर (link_ctrl & PCI_EXP_LNKCTL_CLKREQ_EN)
		rtw_pci_clkreq_set(rtwdev, true);

	rtwpci->link_ctrl = link_ctrl;
पूर्ण

अटल व्योम rtw_pci_पूर्णांकerface_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	चयन (chip->id) अणु
	हाल RTW_CHIP_TYPE_8822C:
		अगर (rtwdev->hal.cut_version >= RTW_CHIP_VER_CUT_D)
			rtw_ग_लिखो32_mask(rtwdev, REG_HCI_MIX_CFG,
					 BIT_PCIE_EMAC_PDN_AUX_TO_FAST_CLK, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw_pci_phy_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_पूर्णांकf_phy_para *para;
	u16 cut;
	u16 value;
	u16 offset;
	पूर्णांक i;

	cut = BIT(0) << rtwdev->hal.cut_version;

	क्रम (i = 0; i < chip->पूर्णांकf_table->n_gen1_para; i++) अणु
		para = &chip->पूर्णांकf_table->gen1_para[i];
		अगर (!(para->cut_mask & cut))
			जारी;
		अगर (para->offset == 0xffff)
			अवरोध;
		offset = para->offset;
		value = para->value;
		अगर (para->ip_sel == RTW_IP_SEL_PHY)
			rtw_mdio_ग_लिखो(rtwdev, offset, value, true);
		अन्यथा
			rtw_dbi_ग_लिखो8(rtwdev, offset, value);
	पूर्ण

	क्रम (i = 0; i < chip->पूर्णांकf_table->n_gen2_para; i++) अणु
		para = &chip->पूर्णांकf_table->gen2_para[i];
		अगर (!(para->cut_mask & cut))
			जारी;
		अगर (para->offset == 0xffff)
			अवरोध;
		offset = para->offset;
		value = para->value;
		अगर (para->ip_sel == RTW_IP_SEL_PHY)
			rtw_mdio_ग_लिखो(rtwdev, offset, value, false);
		अन्यथा
			rtw_dbi_ग_लिखो8(rtwdev, offset, value);
	पूर्ण

	rtw_pci_link_cfg(rtwdev);
पूर्ण

अटल पूर्णांक __maybe_unused rtw_pci_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rtw_pci_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(rtw_pm_ops, rtw_pci_suspend, rtw_pci_resume);
EXPORT_SYMBOL(rtw_pm_ops);

अटल पूर्णांक rtw_pci_claim(काष्ठा rtw_dev *rtwdev, काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to enable pci device\n");
		वापस ret;
	पूर्ण

	pci_set_master(pdev);
	pci_set_drvdata(pdev, rtwdev->hw);
	SET_IEEE80211_DEV(rtwdev->hw, &pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम rtw_pci_declaim(काष्ठा rtw_dev *rtwdev, काष्ठा pci_dev *pdev)
अणु
	pci_clear_master(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक rtw_pci_setup_resource(काष्ठा rtw_dev *rtwdev, काष्ठा pci_dev *pdev)
अणु
	काष्ठा rtw_pci *rtwpci;
	पूर्णांक ret;

	rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;
	rtwpci->pdev = pdev;

	/* after this driver can access to hw रेजिस्टरs */
	ret = rtw_pci_io_mapping(rtwdev, pdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to request pci io region\n");
		जाओ err_out;
	पूर्ण

	ret = rtw_pci_init(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to allocate pci resources\n");
		जाओ err_io_unmap;
	पूर्ण

	वापस 0;

err_io_unmap:
	rtw_pci_io_unmapping(rtwdev, pdev);

err_out:
	वापस ret;
पूर्ण

अटल व्योम rtw_pci_destroy(काष्ठा rtw_dev *rtwdev, काष्ठा pci_dev *pdev)
अणु
	rtw_pci_deinit(rtwdev);
	rtw_pci_io_unmapping(rtwdev, pdev);
पूर्ण

अटल काष्ठा rtw_hci_ops rtw_pci_ops = अणु
	.tx_ग_लिखो = rtw_pci_tx_ग_लिखो,
	.tx_kick_off = rtw_pci_tx_kick_off,
	.flush_queues = rtw_pci_flush_queues,
	.setup = rtw_pci_setup,
	.start = rtw_pci_start,
	.stop = rtw_pci_stop,
	.deep_ps = rtw_pci_deep_ps,
	.link_ps = rtw_pci_link_ps,
	.पूर्णांकerface_cfg = rtw_pci_पूर्णांकerface_cfg,

	.पढ़ो8 = rtw_pci_पढ़ो8,
	.पढ़ो16 = rtw_pci_पढ़ो16,
	.पढ़ो32 = rtw_pci_पढ़ो32,
	.ग_लिखो8 = rtw_pci_ग_लिखो8,
	.ग_लिखो16 = rtw_pci_ग_लिखो16,
	.ग_लिखो32 = rtw_pci_ग_लिखो32,
	.ग_लिखो_data_rsvd_page = rtw_pci_ग_लिखो_data_rsvd_page,
	.ग_लिखो_data_h2c = rtw_pci_ग_लिखो_data_h2c,
पूर्ण;

अटल पूर्णांक rtw_pci_request_irq(काष्ठा rtw_dev *rtwdev, काष्ठा pci_dev *pdev)
अणु
	अचिन्हित पूर्णांक flags = PCI_IRQ_LEGACY;
	पूर्णांक ret;

	अगर (!rtw_disable_msi)
		flags |= PCI_IRQ_MSI;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, flags);
	अगर (ret < 0) अणु
		rtw_err(rtwdev, "failed to alloc PCI irq vectors\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(rtwdev->dev, pdev->irq,
					rtw_pci_पूर्णांकerrupt_handler,
					rtw_pci_पूर्णांकerrupt_thपढ़ोfn,
					IRQF_SHARED, KBUILD_MODNAME, rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to request irq %d\n", ret);
		pci_मुक्त_irq_vectors(pdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rtw_pci_मुक्त_irq(काष्ठा rtw_dev *rtwdev, काष्ठा pci_dev *pdev)
अणु
	devm_मुक्त_irq(rtwdev->dev, pdev->irq, rtwdev);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

अटल पूर्णांक rtw_pci_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा rtw_pci *rtwpci = container_of(napi, काष्ठा rtw_pci, napi);
	काष्ठा rtw_dev *rtwdev = container_of((व्योम *)rtwpci, काष्ठा rtw_dev,
					      priv);
	पूर्णांक work_करोne = 0;

	जबतक (work_करोne < budget) अणु
		u32 work_करोne_once;

		work_करोne_once = rtw_pci_rx_napi(rtwdev, rtwpci, RTW_RX_QUEUE_MPDU,
						 budget - work_करोne);
		अगर (work_करोne_once == 0)
			अवरोध;
		work_करोne += work_करोne_once;
	पूर्ण
	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		spin_lock_bh(&rtwpci->irq_lock);
		अगर (rtwpci->running)
			rtw_pci_enable_पूर्णांकerrupt(rtwdev, rtwpci, false);
		spin_unlock_bh(&rtwpci->irq_lock);
		/* When ISR happens during polling and beक्रमe napi_complete
		 * जबतक no further data is received. Data on the dma_ring will
		 * not be processed immediately. Check whether dma ring is
		 * empty and perक्रमm napi_schedule accordingly.
		 */
		अगर (rtw_pci_get_hw_rx_ring_nr(rtwdev, rtwpci))
			napi_schedule(napi);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम rtw_pci_napi_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	init_dummy_netdev(&rtwpci->netdev);
	netअगर_napi_add(&rtwpci->netdev, &rtwpci->napi, rtw_pci_napi_poll,
		       RTW_NAPI_WEIGHT_NUM);
पूर्ण

अटल व्योम rtw_pci_napi_deinit(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_pci *rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	rtw_pci_napi_stop(rtwdev);
	netअगर_napi_del(&rtwpci->napi);
पूर्ण

पूर्णांक rtw_pci_probe(काष्ठा pci_dev *pdev,
		  स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा rtw_dev *rtwdev;
	पूर्णांक drv_data_size;
	पूर्णांक ret;

	drv_data_size = माप(काष्ठा rtw_dev) + माप(काष्ठा rtw_pci);
	hw = ieee80211_alloc_hw(drv_data_size, &rtw_ops);
	अगर (!hw) अणु
		dev_err(&pdev->dev, "failed to allocate hw\n");
		वापस -ENOMEM;
	पूर्ण

	rtwdev = hw->priv;
	rtwdev->hw = hw;
	rtwdev->dev = &pdev->dev;
	rtwdev->chip = (काष्ठा rtw_chip_info *)id->driver_data;
	rtwdev->hci.ops = &rtw_pci_ops;
	rtwdev->hci.type = RTW_HCI_TYPE_PCIE;

	ret = rtw_core_init(rtwdev);
	अगर (ret)
		जाओ err_release_hw;

	rtw_dbg(rtwdev, RTW_DBG_PCI,
		"rtw88 pci probe: vendor=0x%4.04X device=0x%4.04X rev=%d\n",
		pdev->venकरोr, pdev->device, pdev->revision);

	ret = rtw_pci_claim(rtwdev, pdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to claim pci device\n");
		जाओ err_deinit_core;
	पूर्ण

	ret = rtw_pci_setup_resource(rtwdev, pdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup pci resources\n");
		जाओ err_pci_declaim;
	पूर्ण

	rtw_pci_napi_init(rtwdev);

	ret = rtw_chip_info_setup(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup chip information\n");
		जाओ err_destroy_pci;
	पूर्ण

	rtw_pci_phy_cfg(rtwdev);

	ret = rtw_रेजिस्टर_hw(rtwdev, hw);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to register hw\n");
		जाओ err_destroy_pci;
	पूर्ण

	ret = rtw_pci_request_irq(rtwdev, pdev);
	अगर (ret) अणु
		ieee80211_unरेजिस्टर_hw(hw);
		जाओ err_destroy_pci;
	पूर्ण

	वापस 0;

err_destroy_pci:
	rtw_pci_napi_deinit(rtwdev);
	rtw_pci_destroy(rtwdev, pdev);

err_pci_declaim:
	rtw_pci_declaim(rtwdev, pdev);

err_deinit_core:
	rtw_core_deinit(rtwdev);

err_release_hw:
	ieee80211_मुक्त_hw(hw);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtw_pci_probe);

व्योम rtw_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा rtw_dev *rtwdev;
	काष्ठा rtw_pci *rtwpci;

	अगर (!hw)
		वापस;

	rtwdev = hw->priv;
	rtwpci = (काष्ठा rtw_pci *)rtwdev->priv;

	rtw_unरेजिस्टर_hw(rtwdev, hw);
	rtw_pci_disable_पूर्णांकerrupt(rtwdev, rtwpci);
	rtw_pci_napi_deinit(rtwdev);
	rtw_pci_destroy(rtwdev, pdev);
	rtw_pci_declaim(rtwdev, pdev);
	rtw_pci_मुक्त_irq(rtwdev, pdev);
	rtw_core_deinit(rtwdev);
	ieee80211_मुक्त_hw(hw);
पूर्ण
EXPORT_SYMBOL(rtw_pci_हटाओ);

व्योम rtw_pci_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *hw = pci_get_drvdata(pdev);
	काष्ठा rtw_dev *rtwdev;
	काष्ठा rtw_chip_info *chip;

	अगर (!hw)
		वापस;

	rtwdev = hw->priv;
	chip = rtwdev->chip;

	अगर (chip->ops->shutकरोwn)
		chip->ops->shutकरोwn(rtwdev);

	pci_set_घातer_state(pdev, PCI_D3hot);
पूर्ण
EXPORT_SYMBOL(rtw_pci_shutकरोwn);

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11ac wireless PCI driver");
MODULE_LICENSE("Dual BSD/GPL");
