<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2018 Quantenna Communications */

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/crc32.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/circ_buf.h>

#समावेश "pcie_priv.h"
#समावेश "topaz_pcie_regs.h"
#समावेश "topaz_pcie_ipc.h"
#समावेश "qtn_hw_ids.h"
#समावेश "core.h"
#समावेश "bus.h"
#समावेश "shm_ipc.h"
#समावेश "debug.h"

#घोषणा TOPAZ_TX_BD_SIZE_DEFAULT	128
#घोषणा TOPAZ_RX_BD_SIZE_DEFAULT	256

काष्ठा qtnf_topaz_tx_bd अणु
	__le32 addr;
	__le32 info;
पूर्ण __packed;

काष्ठा qtnf_topaz_rx_bd अणु
	__le32 addr;
	__le32 info;
पूर्ण __packed;

काष्ठा qtnf_extra_bd_params अणु
	__le32 param1;
	__le32 param2;
	__le32 param3;
	__le32 param4;
पूर्ण __packed;

#घोषणा QTNF_BD_PARAM_OFFSET(n)	दुरत्व(काष्ठा qtnf_extra_bd_params, param##n)

काष्ठा vmac_pkt_info अणु
	__le32 addr;
	__le32 info;
पूर्ण;

काष्ठा qtnf_topaz_bda अणु
	__le16	bda_len;
	__le16	bda_version;
	__le32	bda_bootstate;
	__le32	bda_dma_mask;
	__le32	bda_dma_offset;
	__le32	bda_flags;
	__le32	bda_img;
	__le32	bda_img_size;
	__le32	bda_ep2h_irqstatus;
	__le32	bda_h2ep_irqstatus;
	__le32	bda_msi_addr;
	u8	reserved1[56];
	__le32	bda_flashsz;
	u8	bda_boardname[PCIE_BDA_NAMELEN];
	__le32	bda_pci_pre_status;
	__le32	bda_pci_endian;
	__le32	bda_pci_post_status;
	__le32	bda_h2ep_txd_budget;
	__le32	bda_ep2h_txd_budget;
	__le32	bda_rc_rx_bd_base;
	__le32	bda_rc_rx_bd_num;
	__le32	bda_rc_tx_bd_base;
	__le32	bda_rc_tx_bd_num;
	u8	bda_ep_link_state;
	u8	bda_rc_link_state;
	u8	bda_rc_msi_enabled;
	u8	reserved2;
	__le32	bda_ep_next_pkt;
	काष्ठा vmac_pkt_info request[QTN_PCIE_RC_TX_QUEUE_LEN];
	काष्ठा qtnf_shm_ipc_region bda_shm_reg1 __aligned(4096);
	काष्ठा qtnf_shm_ipc_region bda_shm_reg2 __aligned(4096);
पूर्ण __packed;

काष्ठा qtnf_pcie_topaz_state अणु
	काष्ठा qtnf_pcie_bus_priv base;
	काष्ठा qtnf_topaz_bda __iomem *bda;

	dma_addr_t dma_msi_dummy;
	u32 dma_msi_imwr;

	काष्ठा qtnf_topaz_tx_bd *tx_bd_vbase;
	काष्ठा qtnf_topaz_rx_bd *rx_bd_vbase;

	__le32 __iomem *ep_next_rx_pkt;
	__le32 __iomem *txqueue_wake;
	__le32 __iomem *ep_pmstate;

	अचिन्हित दीर्घ rx_pkt_count;
पूर्ण;

अटल व्योम qtnf_deनिश्चित_पूर्णांकx(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	व्योम __iomem *reg = ts->base.sysctl_bar + TOPAZ_PCIE_CFG0_OFFSET;
	u32 cfg;

	cfg = पढ़ोl(reg);
	cfg &= ~TOPAZ_ASSERT_INTX;
	qtnf_non_posted_ग_लिखो(cfg, reg);
पूर्ण

अटल अंतरभूत पूर्णांक qtnf_topaz_पूर्णांकx_निश्चितed(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	व्योम __iomem *reg = ts->base.sysctl_bar + TOPAZ_PCIE_CFG0_OFFSET;
	u32 cfg = पढ़ोl(reg);

	वापस !!(cfg & TOPAZ_ASSERT_INTX);
पूर्ण

अटल व्योम qtnf_topaz_reset_ep(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_RST_EP_IRQ),
	       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));
	msleep(QTN_EP_RESET_WAIT_MS);
	pci_restore_state(ts->base.pdev);
पूर्ण

अटल व्योम setup_rx_irqs(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	व्योम __iomem *reg = PCIE_DMA_WR_DONE_IMWR_ADDR_LOW(ts->base.dmareg_bar);

	ts->dma_msi_imwr = पढ़ोl(reg);
पूर्ण

अटल व्योम enable_rx_irqs(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	व्योम __iomem *reg = PCIE_DMA_WR_DONE_IMWR_ADDR_LOW(ts->base.dmareg_bar);

	qtnf_non_posted_ग_लिखो(ts->dma_msi_imwr, reg);
पूर्ण

अटल व्योम disable_rx_irqs(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	व्योम __iomem *reg = PCIE_DMA_WR_DONE_IMWR_ADDR_LOW(ts->base.dmareg_bar);

	qtnf_non_posted_ग_लिखो(QTN_HOST_LO32(ts->dma_msi_dummy), reg);
पूर्ण

अटल व्योम qtnf_topaz_ipc_gen_ep_पूर्णांक(व्योम *arg)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = arg;

	ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_CTRL_IRQ),
	       TOPAZ_CTL_M2L_INT(ts->base.sysctl_bar));
पूर्ण

अटल पूर्णांक qtnf_is_state(__le32 __iomem *reg, u32 state)
अणु
	u32 s = पढ़ोl(reg);

	वापस (s == state);
पूर्ण

अटल व्योम qtnf_set_state(__le32 __iomem *reg, u32 state)
अणु
	qtnf_non_posted_ग_लिखो(state, reg);
पूर्ण

अटल पूर्णांक qtnf_poll_state(__le32 __iomem *reg, u32 state, u32 delay_in_ms)
अणु
	u32 समयout = 0;

	जबतक ((qtnf_is_state(reg, state) == 0)) अणु
		usleep_range(1000, 1200);
		अगर (++समयout > delay_in_ms)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक topaz_alloc_bd_table(काष्ठा qtnf_pcie_topaz_state *ts,
				काष्ठा qtnf_topaz_bda __iomem *bda)
अणु
	काष्ठा qtnf_extra_bd_params __iomem *extra_params;
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;
	dma_addr_t paddr;
	व्योम *vaddr;
	पूर्णांक len;
	पूर्णांक i;

	/* bd table */

	len = priv->tx_bd_num * माप(काष्ठा qtnf_topaz_tx_bd) +
		priv->rx_bd_num * माप(काष्ठा qtnf_topaz_rx_bd) +
			माप(काष्ठा qtnf_extra_bd_params);

	vaddr = dmam_alloc_coherent(&priv->pdev->dev, len, &paddr, GFP_KERNEL);
	अगर (!vaddr)
		वापस -ENOMEM;

	/* tx bd */

	ts->tx_bd_vbase = vaddr;
	qtnf_non_posted_ग_लिखो(paddr, &bda->bda_rc_tx_bd_base);

	क्रम (i = 0; i < priv->tx_bd_num; i++)
		ts->tx_bd_vbase[i].info |= cpu_to_le32(QTN_BD_EMPTY);

	pr_debug("TX descriptor table: vaddr=0x%p paddr=%pad\n", vaddr, &paddr);

	priv->tx_bd_r_index = 0;
	priv->tx_bd_w_index = 0;

	/* rx bd */

	vaddr = ((काष्ठा qtnf_topaz_tx_bd *)vaddr) + priv->tx_bd_num;
	paddr += priv->tx_bd_num * माप(काष्ठा qtnf_topaz_tx_bd);

	ts->rx_bd_vbase = vaddr;
	qtnf_non_posted_ग_लिखो(paddr, &bda->bda_rc_rx_bd_base);

	pr_debug("RX descriptor table: vaddr=0x%p paddr=%pad\n", vaddr, &paddr);

	/* extra shared params */

	vaddr = ((काष्ठा qtnf_topaz_rx_bd *)vaddr) + priv->rx_bd_num;
	paddr += priv->rx_bd_num * माप(काष्ठा qtnf_topaz_rx_bd);

	extra_params = (काष्ठा qtnf_extra_bd_params __iomem *)vaddr;

	ts->ep_next_rx_pkt = &extra_params->param1;
	qtnf_non_posted_ग_लिखो(paddr + QTNF_BD_PARAM_OFFSET(1),
			      &bda->bda_ep_next_pkt);
	ts->txqueue_wake = &extra_params->param2;
	ts->ep_pmstate = &extra_params->param3;
	ts->dma_msi_dummy = paddr + QTNF_BD_PARAM_OFFSET(4);

	वापस 0;
पूर्ण

अटल पूर्णांक
topaz_skb2rbd_attach(काष्ठा qtnf_pcie_topaz_state *ts, u16 index, u32 wrap)
अणु
	काष्ठा qtnf_topaz_rx_bd *rxbd = &ts->rx_bd_vbase[index];
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;

	skb = netdev_alloc_skb_ip_align(शून्य, SKB_BUF_SIZE);
	अगर (!skb) अणु
		ts->base.rx_skb[index] = शून्य;
		वापस -ENOMEM;
	पूर्ण

	ts->base.rx_skb[index] = skb;

	paddr = pci_map_single(ts->base.pdev, skb->data,
			       SKB_BUF_SIZE, PCI_DMA_FROMDEVICE);
	अगर (pci_dma_mapping_error(ts->base.pdev, paddr)) अणु
		pr_err("skb mapping error: %pad\n", &paddr);
		वापस -ENOMEM;
	पूर्ण

	rxbd->addr = cpu_to_le32(QTN_HOST_LO32(paddr));
	rxbd->info = cpu_to_le32(QTN_BD_EMPTY | wrap);

	ts->base.rx_bd_w_index = index;

	वापस 0;
पूर्ण

अटल पूर्णांक topaz_alloc_rx_buffers(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	u16 i;
	पूर्णांक ret = 0;

	स_रखो(ts->rx_bd_vbase, 0x0,
	       ts->base.rx_bd_num * माप(काष्ठा qtnf_topaz_rx_bd));

	क्रम (i = 0; i < ts->base.rx_bd_num; i++) अणु
		ret = topaz_skb2rbd_attach(ts, i, 0);
		अगर (ret)
			अवरोध;
	पूर्ण

	ts->rx_bd_vbase[ts->base.rx_bd_num - 1].info |=
						cpu_to_le32(QTN_BD_WRAP);

	वापस ret;
पूर्ण

/* all rx/tx activity should have ceased beक्रमe calling this function */
अटल व्योम qtnf_topaz_मुक्त_xfer_buffers(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;
	काष्ठा qtnf_topaz_rx_bd *rxbd;
	काष्ठा qtnf_topaz_tx_bd *txbd;
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक i;

	/* मुक्त rx buffers */
	क्रम (i = 0; i < priv->rx_bd_num; i++) अणु
		अगर (priv->rx_skb && priv->rx_skb[i]) अणु
			rxbd = &ts->rx_bd_vbase[i];
			skb = priv->rx_skb[i];
			paddr = QTN_HOST_ADDR(0x0, le32_to_cpu(rxbd->addr));
			pci_unmap_single(priv->pdev, paddr, SKB_BUF_SIZE,
					 PCI_DMA_FROMDEVICE);
			dev_kमुक्त_skb_any(skb);
			priv->rx_skb[i] = शून्य;
			rxbd->addr = 0;
			rxbd->info = 0;
		पूर्ण
	पूर्ण

	/* मुक्त tx buffers */
	क्रम (i = 0; i < priv->tx_bd_num; i++) अणु
		अगर (priv->tx_skb && priv->tx_skb[i]) अणु
			txbd = &ts->tx_bd_vbase[i];
			skb = priv->tx_skb[i];
			paddr = QTN_HOST_ADDR(0x0, le32_to_cpu(txbd->addr));
			pci_unmap_single(priv->pdev, paddr, SKB_BUF_SIZE,
					 PCI_DMA_TODEVICE);
			dev_kमुक्त_skb_any(skb);
			priv->tx_skb[i] = शून्य;
			txbd->addr = 0;
			txbd->info = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qtnf_pcie_topaz_init_xfer(काष्ठा qtnf_pcie_topaz_state *ts,
				     अचिन्हित पूर्णांक tx_bd_size,
				     अचिन्हित पूर्णांक rx_bd_size)
अणु
	काष्ठा qtnf_topaz_bda __iomem *bda = ts->bda;
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;
	पूर्णांक ret;

	अगर (tx_bd_size == 0)
		tx_bd_size = TOPAZ_TX_BD_SIZE_DEFAULT;

	/* check TX BD queue max length according to काष्ठा qtnf_topaz_bda */
	अगर (tx_bd_size > QTN_PCIE_RC_TX_QUEUE_LEN) अणु
		pr_warn("TX BD queue cannot exceed %d\n",
			QTN_PCIE_RC_TX_QUEUE_LEN);
		tx_bd_size = QTN_PCIE_RC_TX_QUEUE_LEN;
	पूर्ण

	priv->tx_bd_num = tx_bd_size;
	qtnf_non_posted_ग_लिखो(priv->tx_bd_num, &bda->bda_rc_tx_bd_num);

	अगर (rx_bd_size == 0)
		rx_bd_size = TOPAZ_RX_BD_SIZE_DEFAULT;

	अगर (rx_bd_size > TOPAZ_RX_BD_SIZE_DEFAULT) अणु
		pr_warn("RX BD queue cannot exceed %d\n",
			TOPAZ_RX_BD_SIZE_DEFAULT);
		rx_bd_size = TOPAZ_RX_BD_SIZE_DEFAULT;
	पूर्ण

	priv->rx_bd_num = rx_bd_size;
	qtnf_non_posted_ग_लिखो(priv->rx_bd_num, &bda->bda_rc_rx_bd_num);

	priv->rx_bd_w_index = 0;
	priv->rx_bd_r_index = 0;

	ret = qtnf_pcie_alloc_skb_array(priv);
	अगर (ret) अणु
		pr_err("failed to allocate skb array\n");
		वापस ret;
	पूर्ण

	ret = topaz_alloc_bd_table(ts, bda);
	अगर (ret) अणु
		pr_err("failed to allocate bd table\n");
		वापस ret;
	पूर्ण

	ret = topaz_alloc_rx_buffers(ts);
	अगर (ret) अणु
		pr_err("failed to allocate rx buffers\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qtnf_topaz_data_tx_reclaim(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;
	काष्ठा qtnf_topaz_tx_bd *txbd;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	dma_addr_t paddr;
	u32 tx_करोne_index;
	पूर्णांक count = 0;
	पूर्णांक i;

	spin_lock_irqsave(&priv->tx_reclaim_lock, flags);

	tx_करोne_index = पढ़ोl(ts->ep_next_rx_pkt);
	i = priv->tx_bd_r_index;

	अगर (CIRC_CNT(priv->tx_bd_w_index, tx_करोne_index, priv->tx_bd_num))
		ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_TX_DONE_IRQ),
		       TOPAZ_LH_IPC4_INT(priv->sysctl_bar));

	जबतक (CIRC_CNT(tx_करोne_index, i, priv->tx_bd_num)) अणु
		skb = priv->tx_skb[i];

		अगर (likely(skb)) अणु
			txbd = &ts->tx_bd_vbase[i];
			paddr = QTN_HOST_ADDR(0x0, le32_to_cpu(txbd->addr));
			pci_unmap_single(priv->pdev, paddr, skb->len,
					 PCI_DMA_TODEVICE);

			अगर (skb->dev) अणु
				dev_sw_netstats_tx_add(skb->dev, 1, skb->len);
				अगर (unlikely(priv->tx_stopped)) अणु
					qtnf_wake_all_queues(skb->dev);
					priv->tx_stopped = 0;
				पूर्ण
			पूर्ण

			dev_kमुक्त_skb_any(skb);
		पूर्ण

		priv->tx_skb[i] = शून्य;
		count++;

		अगर (++i >= priv->tx_bd_num)
			i = 0;
	पूर्ण

	priv->tx_reclaim_करोne += count;
	priv->tx_reclaim_req++;
	priv->tx_bd_r_index = i;

	spin_unlock_irqrestore(&priv->tx_reclaim_lock, flags);
पूर्ण

अटल व्योम qtnf_try_stop_xmit(काष्ठा qtnf_bus *bus, काष्ठा net_device *ndev)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = (व्योम *)get_bus_priv(bus);

	अगर (ndev) अणु
		netअगर_tx_stop_all_queues(ndev);
		ts->base.tx_stopped = 1;
	पूर्ण

	ग_लिखोl(0x0, ts->txqueue_wake);

	/* sync up tx queue status beक्रमe generating पूर्णांकerrupt */
	dma_wmb();

	/* send irq to card: tx stopped */
	ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_TX_STOP_IRQ),
	       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));

	/* schedule reclaim attempt */
	tasklet_hi_schedule(&ts->base.reclaim_tq);
पूर्ण

अटल व्योम qtnf_try_wake_xmit(काष्ठा qtnf_bus *bus, काष्ठा net_device *ndev)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	पूर्णांक पढ़ोy;

	पढ़ोy = पढ़ोl(ts->txqueue_wake);
	अगर (पढ़ोy) अणु
		netअगर_wake_queue(ndev);
	पूर्ण अन्यथा अणु
		/* re-send irq to card: tx stopped */
		ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_TX_STOP_IRQ),
		       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));
	पूर्ण
पूर्ण

अटल पूर्णांक qtnf_tx_queue_पढ़ोy(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;

	अगर (!CIRC_SPACE(priv->tx_bd_w_index, priv->tx_bd_r_index,
			priv->tx_bd_num)) अणु
		qtnf_topaz_data_tx_reclaim(ts);

		अगर (!CIRC_SPACE(priv->tx_bd_w_index, priv->tx_bd_r_index,
				priv->tx_bd_num)) अणु
			priv->tx_full_count++;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक qtnf_pcie_data_tx(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक macid, अचिन्हित पूर्णांक vअगरid)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = (व्योम *)get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;
	काष्ठा qtnf_topaz_bda __iomem *bda = ts->bda;
	काष्ठा qtnf_topaz_tx_bd *txbd;
	dma_addr_t skb_paddr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	पूर्णांक len;
	पूर्णांक i;

	spin_lock_irqsave(&priv->tx_lock, flags);

	अगर (!qtnf_tx_queue_पढ़ोy(ts)) अणु
		qtnf_try_stop_xmit(bus, skb->dev);
		spin_unlock_irqrestore(&priv->tx_lock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	i = priv->tx_bd_w_index;
	priv->tx_skb[i] = skb;
	len = skb->len;

	skb_paddr = pci_map_single(priv->pdev, skb->data,
				   skb->len, PCI_DMA_TODEVICE);
	अगर (pci_dma_mapping_error(priv->pdev, skb_paddr)) अणु
		ret = -ENOMEM;
		जाओ tx_करोne;
	पूर्ण

	txbd = &ts->tx_bd_vbase[i];
	txbd->addr = cpu_to_le32(QTN_HOST_LO32(skb_paddr));

	ग_लिखोl(QTN_HOST_LO32(skb_paddr), &bda->request[i].addr);
	ग_लिखोl(len | QTN_PCIE_TX_VALID_PKT, &bda->request[i].info);

	/* sync up descriptor updates beक्रमe generating पूर्णांकerrupt */
	dma_wmb();

	/* generate irq to card: tx करोne */
	ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_TX_DONE_IRQ),
	       TOPAZ_LH_IPC4_INT(priv->sysctl_bar));

	अगर (++i >= priv->tx_bd_num)
		i = 0;

	priv->tx_bd_w_index = i;

tx_करोne:
	अगर (ret) अणु
		अगर (skb->dev)
			skb->dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	priv->tx_करोne_count++;
	spin_unlock_irqrestore(&priv->tx_lock, flags);

	qtnf_topaz_data_tx_reclaim(ts);

	वापस NETDEV_TX_OK;
पूर्ण

अटल irqवापस_t qtnf_pcie_topaz_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = (काष्ठा qtnf_bus *)data;
	काष्ठा qtnf_pcie_topaz_state *ts = (व्योम *)get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;

	अगर (!priv->msi_enabled && !qtnf_topaz_पूर्णांकx_निश्चितed(ts))
		वापस IRQ_NONE;

	अगर (!priv->msi_enabled)
		qtnf_deनिश्चित_पूर्णांकx(ts);

	priv->pcie_irq_count++;

	qtnf_shm_ipc_irq_handler(&priv->shm_ipc_ep_in);
	qtnf_shm_ipc_irq_handler(&priv->shm_ipc_ep_out);

	अगर (napi_schedule_prep(&bus->mux_napi)) अणु
		disable_rx_irqs(ts);
		__napi_schedule(&bus->mux_napi);
	पूर्ण

	tasklet_hi_schedule(&priv->reclaim_tq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qtnf_rx_data_पढ़ोy(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	u16 index = ts->base.rx_bd_r_index;
	काष्ठा qtnf_topaz_rx_bd *rxbd;
	u32 descw;

	rxbd = &ts->rx_bd_vbase[index];
	descw = le32_to_cpu(rxbd->info);

	अगर (descw & QTN_BD_EMPTY)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक qtnf_topaz_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा qtnf_bus *bus = container_of(napi, काष्ठा qtnf_bus, mux_napi);
	काष्ठा qtnf_pcie_topaz_state *ts = (व्योम *)get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक processed = 0;
	काष्ठा qtnf_topaz_rx_bd *rxbd;
	dma_addr_t skb_paddr;
	पूर्णांक consume;
	u32 descw;
	u32 poffset;
	u32 psize;
	u16 r_idx;
	u16 w_idx;
	पूर्णांक ret;

	जबतक (processed < budget) अणु
		अगर (!qtnf_rx_data_पढ़ोy(ts))
			जाओ rx_out;

		r_idx = priv->rx_bd_r_index;
		rxbd = &ts->rx_bd_vbase[r_idx];
		descw = le32_to_cpu(rxbd->info);

		skb = priv->rx_skb[r_idx];
		poffset = QTN_GET_OFFSET(descw);
		psize = QTN_GET_LEN(descw);
		consume = 1;

		अगर (descw & QTN_BD_EMPTY) अणु
			pr_warn("skip invalid rxbd[%d]\n", r_idx);
			consume = 0;
		पूर्ण

		अगर (!skb) अणु
			pr_warn("skip missing rx_skb[%d]\n", r_idx);
			consume = 0;
		पूर्ण

		अगर (skb && (skb_tailroom(skb) <  psize)) अणु
			pr_err("skip packet with invalid length: %u > %u\n",
			       psize, skb_tailroom(skb));
			consume = 0;
		पूर्ण

		अगर (skb) अणु
			skb_paddr = QTN_HOST_ADDR(0x0, le32_to_cpu(rxbd->addr));
			pci_unmap_single(priv->pdev, skb_paddr, SKB_BUF_SIZE,
					 PCI_DMA_FROMDEVICE);
		पूर्ण

		अगर (consume) अणु
			skb_reserve(skb, poffset);
			skb_put(skb, psize);
			ndev = qtnf_classअगरy_skb(bus, skb);
			अगर (likely(ndev)) अणु
				dev_sw_netstats_rx_add(ndev, skb->len);
				skb->protocol = eth_type_trans(skb, ndev);
				netअगर_receive_skb(skb);
			पूर्ण अन्यथा अणु
				pr_debug("drop untagged skb\n");
				bus->mux_dev.stats.rx_dropped++;
				dev_kमुक्त_skb_any(skb);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (skb) अणु
				bus->mux_dev.stats.rx_dropped++;
				dev_kमुक्त_skb_any(skb);
			पूर्ण
		पूर्ण

		/* notअगरy card about recv packets once per several packets */
		अगर (((++ts->rx_pkt_count) & RX_DONE_INTR_MSK) == 0)
			ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_RX_DONE_IRQ),
			       TOPAZ_LH_IPC4_INT(priv->sysctl_bar));

		priv->rx_skb[r_idx] = शून्य;
		अगर (++r_idx >= priv->rx_bd_num)
			r_idx = 0;

		priv->rx_bd_r_index = r_idx;

		/* repalce processed buffer by a new one */
		w_idx = priv->rx_bd_w_index;
		जबतक (CIRC_SPACE(priv->rx_bd_w_index, priv->rx_bd_r_index,
				  priv->rx_bd_num) > 0) अणु
			अगर (++w_idx >= priv->rx_bd_num)
				w_idx = 0;

			ret = topaz_skb2rbd_attach(ts, w_idx,
						   descw & QTN_BD_WRAP);
			अगर (ret) अणु
				pr_err("failed to allocate new rx_skb[%d]\n",
				       w_idx);
				अवरोध;
			पूर्ण
		पूर्ण

		processed++;
	पूर्ण

rx_out:
	अगर (processed < budget) अणु
		napi_complete(napi);
		enable_rx_irqs(ts);
	पूर्ण

	वापस processed;
पूर्ण

अटल व्योम
qtnf_pcie_data_tx_समयout(काष्ठा qtnf_bus *bus, काष्ठा net_device *ndev)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);

	qtnf_try_wake_xmit(bus, ndev);
	tasklet_hi_schedule(&ts->base.reclaim_tq);
पूर्ण

अटल व्योम qtnf_pcie_data_rx_start(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);

	napi_enable(&bus->mux_napi);
	enable_rx_irqs(ts);
पूर्ण

अटल व्योम qtnf_pcie_data_rx_stop(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);

	disable_rx_irqs(ts);
	napi_disable(&bus->mux_napi);
पूर्ण

अटल काष्ठा qtnf_bus_ops qtnf_pcie_topaz_bus_ops = अणु
	/* control path methods */
	.control_tx	= qtnf_pcie_control_tx,

	/* data path methods */
	.data_tx		= qtnf_pcie_data_tx,
	.data_tx_समयout	= qtnf_pcie_data_tx_समयout,
	.data_rx_start		= qtnf_pcie_data_rx_start,
	.data_rx_stop		= qtnf_pcie_data_rx_stop,
पूर्ण;

अटल पूर्णांक qtnf_dbg_irq_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = dev_get_drvdata(s->निजी);
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);

	seq_म_लिखो(s, "pcie_irq_count(%u)\n", ts->base.pcie_irq_count);

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_dbg_pkt_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = dev_get_drvdata(s->निजी);
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ts->base;
	u32 tx_करोne_index = पढ़ोl(ts->ep_next_rx_pkt);

	seq_म_लिखो(s, "tx_full_count(%u)\n", priv->tx_full_count);
	seq_म_लिखो(s, "tx_done_count(%u)\n", priv->tx_करोne_count);
	seq_म_लिखो(s, "tx_reclaim_done(%u)\n", priv->tx_reclaim_करोne);
	seq_म_लिखो(s, "tx_reclaim_req(%u)\n", priv->tx_reclaim_req);

	seq_म_लिखो(s, "tx_bd_r_index(%u)\n", priv->tx_bd_r_index);
	seq_म_लिखो(s, "tx_done_index(%u)\n", tx_करोne_index);
	seq_म_लिखो(s, "tx_bd_w_index(%u)\n", priv->tx_bd_w_index);

	seq_म_लिखो(s, "tx host queue len(%u)\n",
		   CIRC_CNT(priv->tx_bd_w_index, priv->tx_bd_r_index,
			    priv->tx_bd_num));
	seq_म_लिखो(s, "tx reclaim queue len(%u)\n",
		   CIRC_CNT(tx_करोne_index, priv->tx_bd_r_index,
			    priv->tx_bd_num));
	seq_म_लिखो(s, "tx card queue len(%u)\n",
		   CIRC_CNT(priv->tx_bd_w_index, tx_करोne_index,
			    priv->tx_bd_num));

	seq_म_लिखो(s, "rx_bd_r_index(%u)\n", priv->rx_bd_r_index);
	seq_म_लिखो(s, "rx_bd_w_index(%u)\n", priv->rx_bd_w_index);
	seq_म_लिखो(s, "rx alloc queue len(%u)\n",
		   CIRC_SPACE(priv->rx_bd_w_index, priv->rx_bd_r_index,
			      priv->rx_bd_num));

	वापस 0;
पूर्ण

अटल व्योम qtnf_reset_dma_offset(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	काष्ठा qtnf_topaz_bda __iomem *bda = ts->bda;
	u32 offset = पढ़ोl(&bda->bda_dma_offset);

	अगर ((offset & PCIE_DMA_OFFSET_ERROR_MASK) != PCIE_DMA_OFFSET_ERROR)
		वापस;

	ग_लिखोl(0x0, &bda->bda_dma_offset);
पूर्ण

अटल पूर्णांक qtnf_pcie_endian_detect(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	काष्ठा qtnf_topaz_bda __iomem *bda = ts->bda;
	u32 समयout = 0;
	u32 endian;
	पूर्णांक ret = 0;

	ग_लिखोl(QTN_PCI_ENDIAN_DETECT_DATA, &bda->bda_pci_endian);

	/* flush endian modअगरications beक्रमe status update */
	dma_wmb();

	ग_लिखोl(QTN_PCI_ENDIAN_VALID_STATUS, &bda->bda_pci_pre_status);

	जबतक (पढ़ोl(&bda->bda_pci_post_status) !=
	       QTN_PCI_ENDIAN_VALID_STATUS) अणु
		usleep_range(1000, 1200);
		अगर (++समयout > QTN_FW_DL_TIMEOUT_MS) अणु
			pr_err("card endianness detection timed out\n");
			ret = -ETIMEDOUT;
			जाओ endian_out;
		पूर्ण
	पूर्ण

	/* करो not पढ़ो beक्रमe status is updated */
	dma_rmb();

	endian = पढ़ोl(&bda->bda_pci_endian);
	WARN(endian != QTN_PCI_LITTLE_ENDIAN,
	     "%s: unexpected card endianness", __func__);

endian_out:
	ग_लिखोl(0, &bda->bda_pci_pre_status);
	ग_लिखोl(0, &bda->bda_pci_post_status);
	ग_लिखोl(0, &bda->bda_pci_endian);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_pre_init_ep(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = (व्योम *)get_bus_priv(bus);
	काष्ठा qtnf_topaz_bda __iomem *bda = ts->bda;
	u32 flags;
	पूर्णांक ret;

	ret = qtnf_pcie_endian_detect(ts);
	अगर (ret < 0) अणु
		pr_err("failed to detect card endianness\n");
		वापस ret;
	पूर्ण

	ग_लिखोb(ts->base.msi_enabled, &ts->bda->bda_rc_msi_enabled);
	qtnf_reset_dma_offset(ts);

	/* notअगरy card about driver type and boot mode */
	flags = पढ़ोl(&bda->bda_flags) | QTN_BDA_HOST_QLINK_DRV;

	अगर (ts->base.flashboot)
		flags |= QTN_BDA_FLASH_BOOT;
	अन्यथा
		flags &= ~QTN_BDA_FLASH_BOOT;

	ग_लिखोl(flags, &bda->bda_flags);

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_HOST_RDY);
	अगर (qtnf_poll_state(&ts->bda->bda_bootstate, QTN_BDA_FW_TARGET_RDY,
			    QTN_FW_DL_TIMEOUT_MS)) अणु
		pr_err("card is not ready to boot...\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_post_init_ep(काष्ठा qtnf_pcie_topaz_state *ts)
अणु
	काष्ठा pci_dev *pdev = ts->base.pdev;

	setup_rx_irqs(ts);
	disable_rx_irqs(ts);

	अगर (qtnf_poll_state(&ts->bda->bda_bootstate, QTN_BDA_FW_QLINK_DONE,
			    QTN_FW_QLINK_TIMEOUT_MS))
		वापस -ETIMEDOUT;

	enable_irq(pdev->irq);
	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_ep_fw_load(काष्ठा qtnf_pcie_topaz_state *ts, स्थिर u8 *fw, u32 fw_size)
अणु
	काष्ठा qtnf_topaz_bda __iomem *bda = ts->bda;
	काष्ठा pci_dev *pdev = ts->base.pdev;
	u32 reमुख्यing = fw_size;
	u8 *curr = (u8 *)fw;
	u32 blksize;
	u32 nblocks;
	u32 offset;
	u32 count;
	u32 size;
	dma_addr_t paddr;
	व्योम *data;
	पूर्णांक ret = 0;

	pr_debug("FW upload started: fw_addr = 0x%p, size=%d\n", fw, fw_size);

	blksize = ts->base.fw_blksize;

	अगर (blksize < PAGE_SIZE)
		blksize = PAGE_SIZE;

	जबतक (blksize >= PAGE_SIZE) अणु
		pr_debug("allocating %u bytes to upload FW\n", blksize);
		data = dma_alloc_coherent(&pdev->dev, blksize,
					  &paddr, GFP_KERNEL);
		अगर (data)
			अवरोध;
		blksize /= 2;
	पूर्ण

	अगर (!data) अणु
		pr_err("failed to allocate DMA buffer for FW upload\n");
		ret = -ENOMEM;
		जाओ fw_load_out;
	पूर्ण

	nblocks = NBLOCKS(fw_size, blksize);
	offset = पढ़ोl(&bda->bda_dma_offset);

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_HOST_LOAD);
	अगर (qtnf_poll_state(&ts->bda->bda_bootstate, QTN_BDA_FW_EP_RDY,
			    QTN_FW_DL_TIMEOUT_MS)) अणु
		pr_err("card is not ready to download FW\n");
		ret = -ETIMEDOUT;
		जाओ fw_load_map;
	पूर्ण

	क्रम (count = 0 ; count < nblocks; count++) अणु
		size = (reमुख्यing > blksize) ? blksize : reमुख्यing;

		स_नकल(data, curr, size);
		qtnf_non_posted_ग_लिखो(paddr + offset, &bda->bda_img);
		qtnf_non_posted_ग_लिखो(size, &bda->bda_img_size);

		pr_debug("chunk[%u] VA[0x%p] PA[%pad] sz[%u]\n",
			 count, (व्योम *)curr, &paddr, size);

		qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BLOCK_RDY);
		अगर (qtnf_poll_state(&ts->bda->bda_bootstate,
				    QTN_BDA_FW_BLOCK_DONE,
				    QTN_FW_DL_TIMEOUT_MS)) अणु
			pr_err("confirmation for block #%d timed out\n", count);
			ret = -ETIMEDOUT;
			जाओ fw_load_map;
		पूर्ण

		reमुख्यing = (reमुख्यing < size) ? reमुख्यing : (reमुख्यing - size);
		curr += size;
	पूर्ण

	/* upload completion mark: zero-sized block */
	qtnf_non_posted_ग_लिखो(0, &bda->bda_img);
	qtnf_non_posted_ग_लिखो(0, &bda->bda_img_size);

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BLOCK_RDY);
	अगर (qtnf_poll_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BLOCK_DONE,
			    QTN_FW_DL_TIMEOUT_MS)) अणु
		pr_err("confirmation for the last block timed out\n");
		ret = -ETIMEDOUT;
		जाओ fw_load_map;
	पूर्ण

	/* RC is करोne */
	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_BLOCK_END);
	अगर (qtnf_poll_state(&ts->bda->bda_bootstate, QTN_BDA_FW_LOAD_DONE,
			    QTN_FW_DL_TIMEOUT_MS)) अणु
		pr_err("confirmation for FW upload completion timed out\n");
		ret = -ETIMEDOUT;
		जाओ fw_load_map;
	पूर्ण

	pr_debug("FW upload completed: totally sent %d blocks\n", count);

fw_load_map:
	dma_मुक्त_coherent(&pdev->dev, blksize, data, paddr);

fw_load_out:
	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_topaz_fw_upload(काष्ठा qtnf_pcie_topaz_state *ts,
				स्थिर अक्षर *fwname)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा pci_dev *pdev = ts->base.pdev;
	पूर्णांक ret;

	अगर (qtnf_poll_state(&ts->bda->bda_bootstate,
			    QTN_BDA_FW_LOAD_RDY,
			    QTN_FW_DL_TIMEOUT_MS)) अणु
		pr_err("%s: card is not ready\n", fwname);
		वापस -1;
	पूर्ण

	pr_info("starting firmware upload: %s\n", fwname);

	ret = request_firmware(&fw, fwname, &pdev->dev);
	अगर (ret < 0) अणु
		pr_err("%s: request_firmware error %d\n", fwname, ret);
		वापस -1;
	पूर्ण

	ret = qtnf_ep_fw_load(ts, fw->data, fw->size);
	release_firmware(fw);

	अगर (ret)
		pr_err("%s: FW upload error\n", fwname);

	वापस ret;
पूर्ण

अटल व्योम qtnf_topaz_fw_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qtnf_bus *bus = container_of(work, काष्ठा qtnf_bus, fw_work);
	काष्ठा qtnf_pcie_topaz_state *ts = (व्योम *)get_bus_priv(bus);
	पूर्णांक bootloader_needed = पढ़ोl(&ts->bda->bda_flags) & QTN_BDA_XMIT_UBOOT;
	काष्ठा pci_dev *pdev = ts->base.pdev;
	पूर्णांक ret;

	qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_TARGET_BOOT);

	अगर (bootloader_needed) अणु
		ret = qtnf_topaz_fw_upload(ts, QTN_PCI_TOPAZ_BOOTLD_NAME);
		अगर (ret)
			जाओ fw_load_निकास;

		ret = qtnf_pre_init_ep(bus);
		अगर (ret)
			जाओ fw_load_निकास;

		qtnf_set_state(&ts->bda->bda_bootstate,
			       QTN_BDA_FW_TARGET_BOOT);
	पूर्ण

	अगर (ts->base.flashboot) अणु
		pr_info("booting firmware from flash\n");

		ret = qtnf_poll_state(&ts->bda->bda_bootstate,
				      QTN_BDA_FW_FLASH_BOOT,
				      QTN_FW_DL_TIMEOUT_MS);
		अगर (ret)
			जाओ fw_load_निकास;
	पूर्ण अन्यथा अणु
		ret = qtnf_topaz_fw_upload(ts, QTN_PCI_TOPAZ_FW_NAME);
		अगर (ret)
			जाओ fw_load_निकास;

		qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_START);
		ret = qtnf_poll_state(&ts->bda->bda_bootstate,
				      QTN_BDA_FW_CONFIG,
				      QTN_FW_QLINK_TIMEOUT_MS);
		अगर (ret) अणु
			pr_err("FW bringup timed out\n");
			जाओ fw_load_निकास;
		पूर्ण

		qtnf_set_state(&ts->bda->bda_bootstate, QTN_BDA_FW_RUN);
		ret = qtnf_poll_state(&ts->bda->bda_bootstate,
				      QTN_BDA_FW_RUNNING,
				      QTN_FW_QLINK_TIMEOUT_MS);
		अगर (ret) अणु
			pr_err("card bringup timed out\n");
			जाओ fw_load_निकास;
		पूर्ण
	पूर्ण

	ret = qtnf_post_init_ep(ts);
	अगर (ret) अणु
		pr_err("FW runtime failure\n");
		जाओ fw_load_निकास;
	पूर्ण

	pr_info("firmware is up and running\n");

	ret = qtnf_pcie_fw_boot_करोne(bus);
	अगर (ret)
		जाओ fw_load_निकास;

	qtnf_debugfs_add_entry(bus, "pkt_stats", qtnf_dbg_pkt_stats);
	qtnf_debugfs_add_entry(bus, "irq_stats", qtnf_dbg_irq_stats);

fw_load_निकास:
	put_device(&pdev->dev);
पूर्ण

अटल व्योम qtnf_reclaim_tasklet_fn(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = from_tasklet(ts, t, base.reclaim_tq);

	qtnf_topaz_data_tx_reclaim(ts);
पूर्ण

अटल u64 qtnf_topaz_dma_mask_get(व्योम)
अणु
	वापस DMA_BIT_MASK(32);
पूर्ण

अटल पूर्णांक qtnf_pcie_topaz_probe(काष्ठा qtnf_bus *bus,
				 अचिन्हित पूर्णांक tx_bd_num, अचिन्हित पूर्णांक rx_bd_num)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	काष्ठा pci_dev *pdev = ts->base.pdev;
	काष्ठा qtnf_shm_ipc_पूर्णांक ipc_पूर्णांक;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret;

	bus->bus_ops = &qtnf_pcie_topaz_bus_ops;
	INIT_WORK(&bus->fw_work, qtnf_topaz_fw_work_handler);
	ts->bda = ts->base.epmem_bar;

	/* assign host msi irq beक्रमe card init */
	अगर (ts->base.msi_enabled)
		irqflags = IRQF_NOBALANCING;
	अन्यथा
		irqflags = IRQF_NOBALANCING | IRQF_SHARED;

	ret = devm_request_irq(&pdev->dev, pdev->irq,
			       &qtnf_pcie_topaz_पूर्णांकerrupt,
			       irqflags, "qtnf_topaz_irq", (व्योम *)bus);
	अगर (ret) अणु
		pr_err("failed to request pcie irq %d\n", pdev->irq);
		वापस ret;
	पूर्ण

	disable_irq(pdev->irq);

	ret = qtnf_pre_init_ep(bus);
	अगर (ret) अणु
		pr_err("failed to init card\n");
		वापस ret;
	पूर्ण

	ret = qtnf_pcie_topaz_init_xfer(ts, tx_bd_num, rx_bd_num);
	अगर (ret) अणु
		pr_err("PCIE xfer init failed\n");
		वापस ret;
	पूर्ण

	tasklet_setup(&ts->base.reclaim_tq, qtnf_reclaim_tasklet_fn);
	netअगर_napi_add(&bus->mux_dev, &bus->mux_napi,
		       qtnf_topaz_rx_poll, 10);

	ipc_पूर्णांक.fn = qtnf_topaz_ipc_gen_ep_पूर्णांक;
	ipc_पूर्णांक.arg = ts;
	qtnf_pcie_init_shm_ipc(&ts->base, &ts->bda->bda_shm_reg1,
			       &ts->bda->bda_shm_reg2, &ipc_पूर्णांक);

	वापस 0;
पूर्ण

अटल व्योम qtnf_pcie_topaz_हटाओ(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);

	qtnf_topaz_reset_ep(ts);
	qtnf_topaz_मुक्त_xfer_buffers(ts);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक qtnf_pcie_topaz_suspend(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	काष्ठा pci_dev *pdev = ts->base.pdev;

	ग_लिखोl((u32 __क्रमce)PCI_D3hot, ts->ep_pmstate);
	dma_wmb();
	ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_PM_EP_IRQ),
	       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));

	pci_save_state(pdev);
	pci_enable_wake(pdev, PCI_D3hot, 1);
	pci_set_घातer_state(pdev, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_pcie_topaz_resume(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	काष्ठा pci_dev *pdev = ts->base.pdev;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	pci_enable_wake(pdev, PCI_D0, 0);

	ग_लिखोl((u32 __क्रमce)PCI_D0, ts->ep_pmstate);
	dma_wmb();
	ग_लिखोl(TOPAZ_IPC_IRQ_WORD(TOPAZ_RC_PM_EP_IRQ),
	       TOPAZ_LH_IPC4_INT(ts->base.sysctl_bar));

	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा qtnf_bus *qtnf_pcie_topaz_alloc(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qtnf_bus *bus;
	काष्ठा qtnf_pcie_topaz_state *ts;

	bus = devm_kzalloc(&pdev->dev, माप(*bus) + माप(*ts), GFP_KERNEL);
	अगर (!bus)
		वापस शून्य;

	ts = get_bus_priv(bus);
	ts->base.probe_cb = qtnf_pcie_topaz_probe;
	ts->base.हटाओ_cb = qtnf_pcie_topaz_हटाओ;
	ts->base.dma_mask_get_cb = qtnf_topaz_dma_mask_get;
#अगर_घोषित CONFIG_PM_SLEEP
	ts->base.resume_cb = qtnf_pcie_topaz_resume;
	ts->base.suspend_cb = qtnf_pcie_topaz_suspend;
#पूर्ण_अगर

	वापस bus;
पूर्ण
