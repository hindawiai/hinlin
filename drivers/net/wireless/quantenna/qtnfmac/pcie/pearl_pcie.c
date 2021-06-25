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
#समावेश <linux/completion.h>
#समावेश <linux/crc32.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/log2.h>

#समावेश "pcie_priv.h"
#समावेश "pearl_pcie_regs.h"
#समावेश "pearl_pcie_ipc.h"
#समावेश "qtn_hw_ids.h"
#समावेश "core.h"
#समावेश "bus.h"
#समावेश "shm_ipc.h"
#समावेश "debug.h"

#घोषणा PEARL_TX_BD_SIZE_DEFAULT	32
#घोषणा PEARL_RX_BD_SIZE_DEFAULT	256

काष्ठा qtnf_pearl_bda अणु
	__le16 bda_len;
	__le16 bda_version;
	__le32 bda_pci_endian;
	__le32 bda_ep_state;
	__le32 bda_rc_state;
	__le32 bda_dma_mask;
	__le32 bda_msi_addr;
	__le32 bda_flashsz;
	u8 bda_boardname[PCIE_BDA_NAMELEN];
	__le32 bda_rc_msi_enabled;
	u8 bda_hhbm_list[PCIE_HHBM_MAX_SIZE];
	__le32 bda_dsbw_start_index;
	__le32 bda_dsbw_end_index;
	__le32 bda_dsbw_total_bytes;
	__le32 bda_rc_tx_bd_base;
	__le32 bda_rc_tx_bd_num;
	u8 bda_pcie_mac[QTN_ENET_ADDR_LENGTH];
	काष्ठा qtnf_shm_ipc_region bda_shm_reg1 __aligned(4096); /* host TX */
	काष्ठा qtnf_shm_ipc_region bda_shm_reg2 __aligned(4096); /* host RX */
पूर्ण __packed;

काष्ठा qtnf_pearl_tx_bd अणु
	__le32 addr;
	__le32 addr_h;
	__le32 info;
	__le32 info_h;
पूर्ण __packed;

काष्ठा qtnf_pearl_rx_bd अणु
	__le32 addr;
	__le32 addr_h;
	__le32 info;
	__le32 info_h;
	__le32 next_ptr;
	__le32 next_ptr_h;
पूर्ण __packed;

काष्ठा qtnf_pearl_fw_hdr अणु
	u8 boardflg[8];
	__le32 fwsize;
	__le32 seqnum;
	__le32 type;
	__le32 pktlen;
	__le32 crc;
पूर्ण __packed;

काष्ठा qtnf_pcie_pearl_state अणु
	काष्ठा qtnf_pcie_bus_priv base;

	/* lock क्रम irq configuration changes */
	spinlock_t irq_lock;

	काष्ठा qtnf_pearl_bda __iomem *bda;
	व्योम __iomem *pcie_reg_base;

	काष्ठा qtnf_pearl_tx_bd *tx_bd_vbase;
	dma_addr_t tx_bd_pbase;

	काष्ठा qtnf_pearl_rx_bd *rx_bd_vbase;
	dma_addr_t rx_bd_pbase;

	dma_addr_t bd_table_paddr;
	व्योम *bd_table_vaddr;
	u32 bd_table_len;
	u32 pcie_irq_mask;
	u32 pcie_irq_rx_count;
	u32 pcie_irq_tx_count;
	u32 pcie_irq_uf_count;
पूर्ण;

अटल अंतरभूत व्योम qtnf_init_hdp_irqs(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ps->pcie_irq_mask = (PCIE_HDP_INT_RX_BITS | PCIE_HDP_INT_TX_BITS);
	spin_unlock_irqrestore(&ps->irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम qtnf_enable_hdp_irqs(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ग_लिखोl(ps->pcie_irq_mask, PCIE_HDP_INT_EN(ps->pcie_reg_base));
	spin_unlock_irqrestore(&ps->irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम qtnf_disable_hdp_irqs(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ग_लिखोl(0x0, PCIE_HDP_INT_EN(ps->pcie_reg_base));
	spin_unlock_irqrestore(&ps->irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम qtnf_en_rxकरोne_irq(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ps->pcie_irq_mask |= PCIE_HDP_INT_RX_BITS;
	ग_लिखोl(ps->pcie_irq_mask, PCIE_HDP_INT_EN(ps->pcie_reg_base));
	spin_unlock_irqrestore(&ps->irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम qtnf_dis_rxकरोne_irq(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ps->pcie_irq_mask &= ~PCIE_HDP_INT_RX_BITS;
	ग_लिखोl(ps->pcie_irq_mask, PCIE_HDP_INT_EN(ps->pcie_reg_base));
	spin_unlock_irqrestore(&ps->irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम qtnf_en_txकरोne_irq(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ps->pcie_irq_mask |= PCIE_HDP_INT_TX_BITS;
	ग_लिखोl(ps->pcie_irq_mask, PCIE_HDP_INT_EN(ps->pcie_reg_base));
	spin_unlock_irqrestore(&ps->irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम qtnf_dis_txकरोne_irq(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ps->irq_lock, flags);
	ps->pcie_irq_mask &= ~PCIE_HDP_INT_TX_BITS;
	ग_लिखोl(ps->pcie_irq_mask, PCIE_HDP_INT_EN(ps->pcie_reg_base));
	spin_unlock_irqrestore(&ps->irq_lock, flags);
पूर्ण

अटल व्योम qtnf_deनिश्चित_पूर्णांकx(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	व्योम __iomem *reg = ps->base.sysctl_bar + PEARL_PCIE_CFG0_OFFSET;
	u32 cfg;

	cfg = पढ़ोl(reg);
	cfg &= ~PEARL_ASSERT_INTX;
	qtnf_non_posted_ग_लिखो(cfg, reg);
पूर्ण

अटल व्योम qtnf_pearl_reset_ep(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	स्थिर u32 data = QTN_PEARL_IPC_IRQ_WORD(QTN_PEARL_LHOST_EP_RESET);
	व्योम __iomem *reg = ps->base.sysctl_bar +
			    QTN_PEARL_SYSCTL_LHOST_IRQ_OFFSET;

	qtnf_non_posted_ग_लिखो(data, reg);
	msleep(QTN_EP_RESET_WAIT_MS);
	pci_restore_state(ps->base.pdev);
पूर्ण

अटल व्योम qtnf_pcie_pearl_ipc_gen_ep_पूर्णांक(व्योम *arg)
अणु
	स्थिर काष्ठा qtnf_pcie_pearl_state *ps = arg;
	स्थिर u32 data = QTN_PEARL_IPC_IRQ_WORD(QTN_PEARL_LHOST_IPC_IRQ);
	व्योम __iomem *reg = ps->base.sysctl_bar +
			    QTN_PEARL_SYSCTL_LHOST_IRQ_OFFSET;

	qtnf_non_posted_ग_लिखो(data, reg);
पूर्ण

अटल पूर्णांक qtnf_is_state(__le32 __iomem *reg, u32 state)
अणु
	u32 s = पढ़ोl(reg);

	वापस s & state;
पूर्ण

अटल व्योम qtnf_set_state(__le32 __iomem *reg, u32 state)
अणु
	u32 s = पढ़ोl(reg);

	qtnf_non_posted_ग_लिखो(state | s, reg);
पूर्ण

अटल व्योम qtnf_clear_state(__le32 __iomem *reg, u32 state)
अणु
	u32 s = पढ़ोl(reg);

	qtnf_non_posted_ग_लिखो(s & ~state, reg);
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

अटल पूर्णांक pearl_alloc_bd_table(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	dma_addr_t paddr;
	व्योम *vaddr;
	पूर्णांक len;

	len = priv->tx_bd_num * माप(काष्ठा qtnf_pearl_tx_bd) +
		priv->rx_bd_num * माप(काष्ठा qtnf_pearl_rx_bd);

	vaddr = dmam_alloc_coherent(&priv->pdev->dev, len, &paddr, GFP_KERNEL);
	अगर (!vaddr)
		वापस -ENOMEM;

	/* tx bd */

	ps->bd_table_vaddr = vaddr;
	ps->bd_table_paddr = paddr;
	ps->bd_table_len = len;

	ps->tx_bd_vbase = vaddr;
	ps->tx_bd_pbase = paddr;

	pr_debug("TX descriptor table: vaddr=0x%p paddr=%pad\n", vaddr, &paddr);

	priv->tx_bd_r_index = 0;
	priv->tx_bd_w_index = 0;

	/* rx bd */

	vaddr = ((काष्ठा qtnf_pearl_tx_bd *)vaddr) + priv->tx_bd_num;
	paddr += priv->tx_bd_num * माप(काष्ठा qtnf_pearl_tx_bd);

	ps->rx_bd_vbase = vaddr;
	ps->rx_bd_pbase = paddr;

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	ग_लिखोl(QTN_HOST_HI32(paddr),
	       PCIE_HDP_TX_HOST_Q_BASE_H(ps->pcie_reg_base));
#पूर्ण_अगर
	ग_लिखोl(QTN_HOST_LO32(paddr),
	       PCIE_HDP_TX_HOST_Q_BASE_L(ps->pcie_reg_base));
	ग_लिखोl(priv->rx_bd_num | (माप(काष्ठा qtnf_pearl_rx_bd)) << 16,
	       PCIE_HDP_TX_HOST_Q_SZ_CTRL(ps->pcie_reg_base));

	pr_debug("RX descriptor table: vaddr=0x%p paddr=%pad\n", vaddr, &paddr);

	वापस 0;
पूर्ण

अटल पूर्णांक pearl_skb2rbd_attach(काष्ठा qtnf_pcie_pearl_state *ps, u16 index)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	काष्ठा qtnf_pearl_rx_bd *rxbd;
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;

	skb = netdev_alloc_skb_ip_align(शून्य, SKB_BUF_SIZE);
	अगर (!skb) अणु
		priv->rx_skb[index] = शून्य;
		वापस -ENOMEM;
	पूर्ण

	priv->rx_skb[index] = skb;
	rxbd = &ps->rx_bd_vbase[index];

	paddr = pci_map_single(priv->pdev, skb->data,
			       SKB_BUF_SIZE, PCI_DMA_FROMDEVICE);
	अगर (pci_dma_mapping_error(priv->pdev, paddr)) अणु
		pr_err("skb DMA mapping error: %pad\n", &paddr);
		वापस -ENOMEM;
	पूर्ण

	/* keep rx skb paddrs in rx buffer descriptors क्रम cleanup purposes */
	rxbd->addr = cpu_to_le32(QTN_HOST_LO32(paddr));
	rxbd->addr_h = cpu_to_le32(QTN_HOST_HI32(paddr));
	rxbd->info = 0x0;

	priv->rx_bd_w_index = index;

	/* sync up all descriptor updates */
	wmb();

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	ग_लिखोl(QTN_HOST_HI32(paddr),
	       PCIE_HDP_HHBM_BUF_PTR_H(ps->pcie_reg_base));
#पूर्ण_अगर
	ग_लिखोl(QTN_HOST_LO32(paddr),
	       PCIE_HDP_HHBM_BUF_PTR(ps->pcie_reg_base));

	ग_लिखोl(index, PCIE_HDP_TX_HOST_Q_WR_PTR(ps->pcie_reg_base));
	वापस 0;
पूर्ण

अटल पूर्णांक pearl_alloc_rx_buffers(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	u16 i;
	पूर्णांक ret = 0;

	स_रखो(ps->rx_bd_vbase, 0x0,
	       ps->base.rx_bd_num * माप(काष्ठा qtnf_pearl_rx_bd));

	क्रम (i = 0; i < ps->base.rx_bd_num; i++) अणु
		ret = pearl_skb2rbd_attach(ps, i);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* all rx/tx activity should have ceased beक्रमe calling this function */
अटल व्योम qtnf_pearl_मुक्त_xfer_buffers(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	काष्ठा qtnf_pearl_tx_bd *txbd;
	काष्ठा qtnf_pearl_rx_bd *rxbd;
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक i;

	/* मुक्त rx buffers */
	क्रम (i = 0; i < priv->rx_bd_num; i++) अणु
		अगर (priv->rx_skb && priv->rx_skb[i]) अणु
			rxbd = &ps->rx_bd_vbase[i];
			skb = priv->rx_skb[i];
			paddr = QTN_HOST_ADDR(le32_to_cpu(rxbd->addr_h),
					      le32_to_cpu(rxbd->addr));
			pci_unmap_single(priv->pdev, paddr, SKB_BUF_SIZE,
					 PCI_DMA_FROMDEVICE);
			dev_kमुक्त_skb_any(skb);
			priv->rx_skb[i] = शून्य;
		पूर्ण
	पूर्ण

	/* मुक्त tx buffers */
	क्रम (i = 0; i < priv->tx_bd_num; i++) अणु
		अगर (priv->tx_skb && priv->tx_skb[i]) अणु
			txbd = &ps->tx_bd_vbase[i];
			skb = priv->tx_skb[i];
			paddr = QTN_HOST_ADDR(le32_to_cpu(txbd->addr_h),
					      le32_to_cpu(txbd->addr));
			pci_unmap_single(priv->pdev, paddr, skb->len,
					 PCI_DMA_TODEVICE);
			dev_kमुक्त_skb_any(skb);
			priv->tx_skb[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pearl_hhbm_init(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	u32 val;

	val = पढ़ोl(PCIE_HHBM_CONFIG(ps->pcie_reg_base));
	val |= HHBM_CONFIG_SOFT_RESET;
	ग_लिखोl(val, PCIE_HHBM_CONFIG(ps->pcie_reg_base));
	usleep_range(50, 100);
	val &= ~HHBM_CONFIG_SOFT_RESET;
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	val |= HHBM_64BIT;
#पूर्ण_अगर
	ग_लिखोl(val, PCIE_HHBM_CONFIG(ps->pcie_reg_base));
	ग_लिखोl(ps->base.rx_bd_num, PCIE_HHBM_Q_LIMIT_REG(ps->pcie_reg_base));

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_pcie_pearl_init_xfer(काष्ठा qtnf_pcie_pearl_state *ps,
				     अचिन्हित पूर्णांक tx_bd_size,
				     अचिन्हित पूर्णांक rx_bd_size)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	पूर्णांक ret;
	u32 val;

	अगर (tx_bd_size == 0)
		tx_bd_size = PEARL_TX_BD_SIZE_DEFAULT;

	val = tx_bd_size * माप(काष्ठा qtnf_pearl_tx_bd);

	अगर (!is_घातer_of_2(tx_bd_size) || val > PCIE_HHBM_MAX_SIZE) अणु
		pr_warn("invalid tx_bd_size value %u, use default %u\n",
			tx_bd_size, PEARL_TX_BD_SIZE_DEFAULT);
		priv->tx_bd_num = PEARL_TX_BD_SIZE_DEFAULT;
	पूर्ण अन्यथा अणु
		priv->tx_bd_num = tx_bd_size;
	पूर्ण

	अगर (rx_bd_size == 0)
		rx_bd_size = PEARL_RX_BD_SIZE_DEFAULT;

	val = rx_bd_size * माप(dma_addr_t);

	अगर (!is_घातer_of_2(rx_bd_size) || val > PCIE_HHBM_MAX_SIZE) अणु
		pr_warn("invalid rx_bd_size value %u, use default %u\n",
			rx_bd_size, PEARL_RX_BD_SIZE_DEFAULT);
		priv->rx_bd_num = PEARL_RX_BD_SIZE_DEFAULT;
	पूर्ण अन्यथा अणु
		priv->rx_bd_num = rx_bd_size;
	पूर्ण

	priv->rx_bd_w_index = 0;
	priv->rx_bd_r_index = 0;

	ret = pearl_hhbm_init(ps);
	अगर (ret) अणु
		pr_err("failed to init h/w queues\n");
		वापस ret;
	पूर्ण

	ret = qtnf_pcie_alloc_skb_array(priv);
	अगर (ret) अणु
		pr_err("failed to allocate skb array\n");
		वापस ret;
	पूर्ण

	ret = pearl_alloc_bd_table(ps);
	अगर (ret) अणु
		pr_err("failed to allocate bd table\n");
		वापस ret;
	पूर्ण

	ret = pearl_alloc_rx_buffers(ps);
	अगर (ret) अणु
		pr_err("failed to allocate rx buffers\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qtnf_pearl_data_tx_reclaim(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	काष्ठा qtnf_pearl_tx_bd *txbd;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	dma_addr_t paddr;
	u32 tx_करोne_index;
	पूर्णांक count = 0;
	पूर्णांक i;

	spin_lock_irqsave(&priv->tx_reclaim_lock, flags);

	tx_करोne_index = पढ़ोl(PCIE_HDP_RX0DMA_CNT(ps->pcie_reg_base))
			& (priv->tx_bd_num - 1);

	i = priv->tx_bd_r_index;

	जबतक (CIRC_CNT(tx_करोne_index, i, priv->tx_bd_num)) अणु
		skb = priv->tx_skb[i];
		अगर (likely(skb)) अणु
			txbd = &ps->tx_bd_vbase[i];
			paddr = QTN_HOST_ADDR(le32_to_cpu(txbd->addr_h),
					      le32_to_cpu(txbd->addr));
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

अटल पूर्णांक qtnf_tx_queue_पढ़ोy(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;

	अगर (!CIRC_SPACE(priv->tx_bd_w_index, priv->tx_bd_r_index,
			priv->tx_bd_num)) अणु
		qtnf_pearl_data_tx_reclaim(ps);

		अगर (!CIRC_SPACE(priv->tx_bd_w_index, priv->tx_bd_r_index,
				priv->tx_bd_num)) अणु
			pr_warn_ratelimited("reclaim full Tx queue\n");
			priv->tx_full_count++;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक qtnf_pcie_skb_send(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb)
अणु
	काष्ठा qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	dma_addr_t txbd_paddr, skb_paddr;
	काष्ठा qtnf_pearl_tx_bd *txbd;
	अचिन्हित दीर्घ flags;
	पूर्णांक len, i;
	u32 info;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&priv->tx_lock, flags);

	अगर (!qtnf_tx_queue_पढ़ोy(ps)) अणु
		अगर (skb->dev) अणु
			netअगर_tx_stop_all_queues(skb->dev);
			priv->tx_stopped = 1;
		पूर्ण

		spin_unlock_irqrestore(&priv->tx_lock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	i = priv->tx_bd_w_index;
	priv->tx_skb[i] = skb;
	len = skb->len;

	skb_paddr = pci_map_single(priv->pdev, skb->data,
				   skb->len, PCI_DMA_TODEVICE);
	अगर (pci_dma_mapping_error(priv->pdev, skb_paddr)) अणु
		pr_err("skb DMA mapping error: %pad\n", &skb_paddr);
		ret = -ENOMEM;
		जाओ tx_करोne;
	पूर्ण

	txbd = &ps->tx_bd_vbase[i];
	txbd->addr = cpu_to_le32(QTN_HOST_LO32(skb_paddr));
	txbd->addr_h = cpu_to_le32(QTN_HOST_HI32(skb_paddr));

	info = (len & QTN_PCIE_TX_DESC_LEN_MASK) << QTN_PCIE_TX_DESC_LEN_SHIFT;
	txbd->info = cpu_to_le32(info);

	/* sync up all descriptor updates beक्रमe passing them to EP */
	dma_wmb();

	/* ग_लिखो new TX descriptor to PCIE_RX_FIFO on EP */
	txbd_paddr = ps->tx_bd_pbase + i * माप(काष्ठा qtnf_pearl_tx_bd);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	ग_लिखोl(QTN_HOST_HI32(txbd_paddr),
	       PCIE_HDP_HOST_WR_DESC0_H(ps->pcie_reg_base));
#पूर्ण_अगर
	ग_लिखोl(QTN_HOST_LO32(txbd_paddr),
	       PCIE_HDP_HOST_WR_DESC0(ps->pcie_reg_base));

	अगर (++i >= priv->tx_bd_num)
		i = 0;

	priv->tx_bd_w_index = i;

tx_करोne:
	अगर (ret) अणु
		pr_err_ratelimited("drop skb\n");
		अगर (skb->dev)
			skb->dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	priv->tx_करोne_count++;
	spin_unlock_irqrestore(&priv->tx_lock, flags);

	qtnf_pearl_data_tx_reclaim(ps);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक qtnf_pcie_data_tx(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक macid, अचिन्हित पूर्णांक vअगरid)
अणु
	वापस qtnf_pcie_skb_send(bus, skb);
पूर्ण

अटल पूर्णांक qtnf_pcie_data_tx_meta(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक macid, अचिन्हित पूर्णांक vअगरid)
अणु
	काष्ठा qtnf_frame_meta_info *meta;
	पूर्णांक tail_need = माप(*meta) - skb_tailroom(skb);
	पूर्णांक ret;

	अगर (tail_need > 0 && pskb_expand_head(skb, 0, tail_need, GFP_ATOMIC)) अणु
		skb->dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	meta = skb_put(skb, माप(*meta));
	meta->magic_s = HBM_FRAME_META_MAGIC_PATTERN_S;
	meta->magic_e = HBM_FRAME_META_MAGIC_PATTERN_E;
	meta->macid = macid;
	meta->अगरidx = vअगरid;

	ret = qtnf_pcie_skb_send(bus, skb);
	अगर (unlikely(ret == NETDEV_TX_BUSY))
		__skb_trim(skb, skb->len - माप(*meta));

	वापस ret;
पूर्ण

अटल irqवापस_t qtnf_pcie_pearl_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = (काष्ठा qtnf_bus *)data;
	काष्ठा qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	u32 status;

	priv->pcie_irq_count++;
	status = पढ़ोl(PCIE_HDP_INT_STATUS(ps->pcie_reg_base));

	qtnf_shm_ipc_irq_handler(&priv->shm_ipc_ep_in);
	qtnf_shm_ipc_irq_handler(&priv->shm_ipc_ep_out);

	अगर (!(status & ps->pcie_irq_mask))
		जाओ irq_करोne;

	अगर (status & PCIE_HDP_INT_RX_BITS)
		ps->pcie_irq_rx_count++;

	अगर (status & PCIE_HDP_INT_TX_BITS)
		ps->pcie_irq_tx_count++;

	अगर (status & PCIE_HDP_INT_HHBM_UF)
		ps->pcie_irq_uf_count++;

	अगर (status & PCIE_HDP_INT_RX_BITS) अणु
		qtnf_dis_rxकरोne_irq(ps);
		napi_schedule(&bus->mux_napi);
	पूर्ण

	अगर (status & PCIE_HDP_INT_TX_BITS) अणु
		qtnf_dis_txकरोne_irq(ps);
		tasklet_hi_schedule(&priv->reclaim_tq);
	पूर्ण

irq_करोne:
	/* H/W workaround: clean all bits, not only enabled */
	qtnf_non_posted_ग_लिखो(~0U, PCIE_HDP_INT_STATUS(ps->pcie_reg_base));

	अगर (!priv->msi_enabled)
		qtnf_deनिश्चित_पूर्णांकx(ps);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qtnf_rx_data_पढ़ोy(काष्ठा qtnf_pcie_pearl_state *ps)
अणु
	u16 index = ps->base.rx_bd_r_index;
	काष्ठा qtnf_pearl_rx_bd *rxbd;
	u32 descw;

	rxbd = &ps->rx_bd_vbase[index];
	descw = le32_to_cpu(rxbd->info);

	अगर (descw & QTN_TXDONE_MASK)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_pcie_pearl_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा qtnf_bus *bus = container_of(napi, काष्ठा qtnf_bus, mux_napi);
	काष्ठा qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक processed = 0;
	काष्ठा qtnf_pearl_rx_bd *rxbd;
	dma_addr_t skb_paddr;
	पूर्णांक consume;
	u32 descw;
	u32 psize;
	u16 r_idx;
	u16 w_idx;
	पूर्णांक ret;

	जबतक (processed < budget) अणु
		अगर (!qtnf_rx_data_पढ़ोy(ps))
			जाओ rx_out;

		r_idx = priv->rx_bd_r_index;
		rxbd = &ps->rx_bd_vbase[r_idx];
		descw = le32_to_cpu(rxbd->info);

		skb = priv->rx_skb[r_idx];
		psize = QTN_GET_LEN(descw);
		consume = 1;

		अगर (!(descw & QTN_TXDONE_MASK)) अणु
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
			skb_paddr = QTN_HOST_ADDR(le32_to_cpu(rxbd->addr_h),
						  le32_to_cpu(rxbd->addr));
			pci_unmap_single(priv->pdev, skb_paddr, SKB_BUF_SIZE,
					 PCI_DMA_FROMDEVICE);
		पूर्ण

		अगर (consume) अणु
			skb_put(skb, psize);
			ndev = qtnf_classअगरy_skb(bus, skb);
			अगर (likely(ndev)) अणु
				dev_sw_netstats_rx_add(ndev, skb->len);
				skb->protocol = eth_type_trans(skb, ndev);
				napi_gro_receive(napi, skb);
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

			ret = pearl_skb2rbd_attach(ps, w_idx);
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
		qtnf_en_rxकरोne_irq(ps);
	पूर्ण

	वापस processed;
पूर्ण

अटल व्योम
qtnf_pcie_data_tx_समयout(काष्ठा qtnf_bus *bus, काष्ठा net_device *ndev)
अणु
	काष्ठा qtnf_pcie_pearl_state *ps = (व्योम *)get_bus_priv(bus);

	tasklet_hi_schedule(&ps->base.reclaim_tq);
पूर्ण

अटल व्योम qtnf_pcie_data_rx_start(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_pearl_state *ps = (व्योम *)get_bus_priv(bus);

	qtnf_enable_hdp_irqs(ps);
	napi_enable(&bus->mux_napi);
पूर्ण

अटल व्योम qtnf_pcie_data_rx_stop(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_pearl_state *ps = (व्योम *)get_bus_priv(bus);

	napi_disable(&bus->mux_napi);
	qtnf_disable_hdp_irqs(ps);
पूर्ण

अटल व्योम qtnf_pearl_tx_use_meta_info_set(काष्ठा qtnf_bus *bus, bool use_meta)
अणु
	अगर (use_meta)
		bus->bus_ops->data_tx = qtnf_pcie_data_tx_meta;
	अन्यथा
		bus->bus_ops->data_tx = qtnf_pcie_data_tx;
पूर्ण

अटल काष्ठा qtnf_bus_ops qtnf_pcie_pearl_bus_ops = अणु
	/* control path methods */
	.control_tx	= qtnf_pcie_control_tx,

	/* data path methods */
	.data_tx		= qtnf_pcie_data_tx,
	.data_tx_समयout	= qtnf_pcie_data_tx_समयout,
	.data_tx_use_meta_set	= qtnf_pearl_tx_use_meta_info_set,
	.data_rx_start		= qtnf_pcie_data_rx_start,
	.data_rx_stop		= qtnf_pcie_data_rx_stop,
पूर्ण;

अटल पूर्णांक qtnf_dbg_irq_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = dev_get_drvdata(s->निजी);
	काष्ठा qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	u32 reg = पढ़ोl(PCIE_HDP_INT_EN(ps->pcie_reg_base));
	u32 status;

	seq_म_लिखो(s, "pcie_irq_count(%u)\n", ps->base.pcie_irq_count);
	seq_म_लिखो(s, "pcie_irq_tx_count(%u)\n", ps->pcie_irq_tx_count);
	status = reg &  PCIE_HDP_INT_TX_BITS;
	seq_म_लिखो(s, "pcie_irq_tx_status(%s)\n",
		   (status == PCIE_HDP_INT_TX_BITS) ? "EN" : "DIS");
	seq_म_लिखो(s, "pcie_irq_rx_count(%u)\n", ps->pcie_irq_rx_count);
	status = reg &  PCIE_HDP_INT_RX_BITS;
	seq_म_लिखो(s, "pcie_irq_rx_status(%s)\n",
		   (status == PCIE_HDP_INT_RX_BITS) ? "EN" : "DIS");
	seq_म_लिखो(s, "pcie_irq_uf_count(%u)\n", ps->pcie_irq_uf_count);
	status = reg &  PCIE_HDP_INT_HHBM_UF;
	seq_म_लिखो(s, "pcie_irq_hhbm_uf_status(%s)\n",
		   (status == PCIE_HDP_INT_HHBM_UF) ? "EN" : "DIS");

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_dbg_hdp_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = dev_get_drvdata(s->निजी);
	काष्ठा qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	काष्ठा qtnf_pcie_bus_priv *priv = &ps->base;

	seq_म_लिखो(s, "tx_full_count(%u)\n", priv->tx_full_count);
	seq_म_लिखो(s, "tx_done_count(%u)\n", priv->tx_करोne_count);
	seq_म_लिखो(s, "tx_reclaim_done(%u)\n", priv->tx_reclaim_करोne);
	seq_म_लिखो(s, "tx_reclaim_req(%u)\n", priv->tx_reclaim_req);

	seq_म_लिखो(s, "tx_bd_r_index(%u)\n", priv->tx_bd_r_index);
	seq_म_लिखो(s, "tx_bd_p_index(%u)\n",
		   पढ़ोl(PCIE_HDP_RX0DMA_CNT(ps->pcie_reg_base))
			& (priv->tx_bd_num - 1));
	seq_म_लिखो(s, "tx_bd_w_index(%u)\n", priv->tx_bd_w_index);
	seq_म_लिखो(s, "tx queue len(%u)\n",
		   CIRC_CNT(priv->tx_bd_w_index, priv->tx_bd_r_index,
			    priv->tx_bd_num));

	seq_म_लिखो(s, "rx_bd_r_index(%u)\n", priv->rx_bd_r_index);
	seq_म_लिखो(s, "rx_bd_p_index(%u)\n",
		   पढ़ोl(PCIE_HDP_TX0DMA_CNT(ps->pcie_reg_base))
			& (priv->rx_bd_num - 1));
	seq_म_लिखो(s, "rx_bd_w_index(%u)\n", priv->rx_bd_w_index);
	seq_म_लिखो(s, "rx alloc queue len(%u)\n",
		   CIRC_SPACE(priv->rx_bd_w_index, priv->rx_bd_r_index,
			      priv->rx_bd_num));

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_ep_fw_send(काष्ठा pci_dev *pdev, uपूर्णांक32_t size,
			   पूर्णांक blk, स्थिर u8 *pblk, स्थिर u8 *fw)
अणु
	काष्ठा qtnf_bus *bus = pci_get_drvdata(pdev);

	काष्ठा qtnf_pearl_fw_hdr *hdr;
	u8 *pdata;

	पूर्णांक hds = माप(*hdr);
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक len = 0;
	पूर्णांक ret;

	skb = __dev_alloc_skb(QTN_PCIE_FW_BUFSZ, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb->len = QTN_PCIE_FW_BUFSZ;
	skb->dev = शून्य;

	hdr = (काष्ठा qtnf_pearl_fw_hdr *)skb->data;
	स_नकल(hdr->boardflg, QTN_PCIE_BOARDFLG, म_माप(QTN_PCIE_BOARDFLG));
	hdr->fwsize = cpu_to_le32(size);
	hdr->seqnum = cpu_to_le32(blk);

	अगर (blk)
		hdr->type = cpu_to_le32(QTN_FW_DSUB);
	अन्यथा
		hdr->type = cpu_to_le32(QTN_FW_DBEGIN);

	pdata = skb->data + hds;

	len = QTN_PCIE_FW_BUFSZ - hds;
	अगर (pblk >= (fw + size - len)) अणु
		len = fw + size - pblk;
		hdr->type = cpu_to_le32(QTN_FW_DEND);
	पूर्ण

	hdr->pktlen = cpu_to_le32(len);
	स_नकल(pdata, pblk, len);
	hdr->crc = cpu_to_le32(~crc32(0, pdata, len));

	ret = qtnf_pcie_skb_send(bus, skb);

	वापस (ret == NETDEV_TX_OK) ? len : 0;
पूर्ण

अटल पूर्णांक
qtnf_ep_fw_load(काष्ठा qtnf_pcie_pearl_state *ps, स्थिर u8 *fw, u32 fw_size)
अणु
	पूर्णांक blk_size = QTN_PCIE_FW_BUFSZ - माप(काष्ठा qtnf_pearl_fw_hdr);
	पूर्णांक blk_count = fw_size / blk_size + ((fw_size % blk_size) ? 1 : 0);
	स्थिर u8 *pblk = fw;
	पूर्णांक threshold = 0;
	पूर्णांक blk = 0;
	पूर्णांक len;

	pr_debug("FW upload started: fw_addr=0x%p size=%d\n", fw, fw_size);

	जबतक (blk < blk_count) अणु
		अगर (++threshold > 10000) अणु
			pr_err("FW upload failed: too many retries\n");
			वापस -ETIMEDOUT;
		पूर्ण

		len = qtnf_ep_fw_send(ps->base.pdev, fw_size, blk, pblk, fw);
		अगर (len <= 0)
			जारी;

		अगर (!((blk + 1) & QTN_PCIE_FW_DLMASK) ||
		    (blk == (blk_count - 1))) अणु
			qtnf_set_state(&ps->bda->bda_rc_state,
				       QTN_RC_FW_SYNC);
			अगर (qtnf_poll_state(&ps->bda->bda_ep_state,
					    QTN_EP_FW_SYNC,
					    QTN_FW_DL_TIMEOUT_MS)) अणु
				pr_err("FW upload failed: SYNC timed out\n");
				वापस -ETIMEDOUT;
			पूर्ण

			qtnf_clear_state(&ps->bda->bda_ep_state,
					 QTN_EP_FW_SYNC);

			अगर (qtnf_is_state(&ps->bda->bda_ep_state,
					  QTN_EP_FW_RETRY)) अणु
				अगर (blk == (blk_count - 1)) अणु
					पूर्णांक last_round =
						blk_count & QTN_PCIE_FW_DLMASK;
					blk -= last_round;
					pblk -= ((last_round - 1) *
						blk_size + len);
				पूर्ण अन्यथा अणु
					blk -= QTN_PCIE_FW_DLMASK;
					pblk -= QTN_PCIE_FW_DLMASK * blk_size;
				पूर्ण

				qtnf_clear_state(&ps->bda->bda_ep_state,
						 QTN_EP_FW_RETRY);

				pr_warn("FW upload retry: block #%d\n", blk);
				जारी;
			पूर्ण

			qtnf_pearl_data_tx_reclaim(ps);
		पूर्ण

		pblk += len;
		blk++;
	पूर्ण

	pr_debug("FW upload completed: totally sent %d blocks\n", blk);
	वापस 0;
पूर्ण

अटल व्योम qtnf_pearl_fw_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qtnf_bus *bus = container_of(work, काष्ठा qtnf_bus, fw_work);
	काष्ठा qtnf_pcie_pearl_state *ps = (व्योम *)get_bus_priv(bus);
	u32 state = QTN_RC_FW_LOADRDY | QTN_RC_FW_QLINK;
	स्थिर अक्षर *fwname = QTN_PCI_PEARL_FW_NAME;
	काष्ठा pci_dev *pdev = ps->base.pdev;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	अगर (ps->base.flashboot) अणु
		state |= QTN_RC_FW_FLASHBOOT;
	पूर्ण अन्यथा अणु
		ret = request_firmware(&fw, fwname, &pdev->dev);
		अगर (ret < 0) अणु
			pr_err("failed to get firmware %s\n", fwname);
			जाओ fw_load_निकास;
		पूर्ण
	पूर्ण

	qtnf_set_state(&ps->bda->bda_rc_state, state);

	अगर (qtnf_poll_state(&ps->bda->bda_ep_state, QTN_EP_FW_LOADRDY,
			    QTN_FW_DL_TIMEOUT_MS)) अणु
		pr_err("card is not ready\n");

		अगर (!ps->base.flashboot)
			release_firmware(fw);

		जाओ fw_load_निकास;
	पूर्ण

	qtnf_clear_state(&ps->bda->bda_ep_state, QTN_EP_FW_LOADRDY);

	अगर (ps->base.flashboot) अणु
		pr_info("booting firmware from flash\n");

	पूर्ण अन्यथा अणु
		pr_info("starting firmware upload: %s\n", fwname);

		ret = qtnf_ep_fw_load(ps, fw->data, fw->size);
		release_firmware(fw);
		अगर (ret) अणु
			pr_err("firmware upload error\n");
			जाओ fw_load_निकास;
		पूर्ण
	पूर्ण

	अगर (qtnf_poll_state(&ps->bda->bda_ep_state, QTN_EP_FW_DONE,
			    QTN_FW_DL_TIMEOUT_MS)) अणु
		pr_err("firmware bringup timed out\n");
		जाओ fw_load_निकास;
	पूर्ण

	अगर (qtnf_poll_state(&ps->bda->bda_ep_state,
			    QTN_EP_FW_QLINK_DONE, QTN_FW_QLINK_TIMEOUT_MS)) अणु
		pr_err("firmware runtime failure\n");
		जाओ fw_load_निकास;
	पूर्ण

	pr_info("firmware is up and running\n");

	ret = qtnf_pcie_fw_boot_करोne(bus);
	अगर (ret)
		जाओ fw_load_निकास;

	qtnf_debugfs_add_entry(bus, "hdp_stats", qtnf_dbg_hdp_stats);
	qtnf_debugfs_add_entry(bus, "irq_stats", qtnf_dbg_irq_stats);

fw_load_निकास:
	put_device(&pdev->dev);
पूर्ण

अटल व्योम qtnf_pearl_reclaim_tasklet_fn(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा qtnf_pcie_pearl_state *ps = from_tasklet(ps, t, base.reclaim_tq);

	qtnf_pearl_data_tx_reclaim(ps);
	qtnf_en_txकरोne_irq(ps);
पूर्ण

अटल u64 qtnf_pearl_dma_mask_get(व्योम)
अणु
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	वापस DMA_BIT_MASK(64);
#अन्यथा
	वापस DMA_BIT_MASK(32);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक qtnf_pcie_pearl_probe(काष्ठा qtnf_bus *bus, अचिन्हित पूर्णांक tx_bd_size,
				 अचिन्हित पूर्णांक rx_bd_size)
अणु
	काष्ठा qtnf_shm_ipc_पूर्णांक ipc_पूर्णांक;
	काष्ठा qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	काष्ठा pci_dev *pdev = ps->base.pdev;
	पूर्णांक ret;

	bus->bus_ops = &qtnf_pcie_pearl_bus_ops;
	spin_lock_init(&ps->irq_lock);
	INIT_WORK(&bus->fw_work, qtnf_pearl_fw_work_handler);

	ps->pcie_reg_base = ps->base.dmareg_bar;
	ps->bda = ps->base.epmem_bar;
	ग_लिखोl(ps->base.msi_enabled, &ps->bda->bda_rc_msi_enabled);

	ret = qtnf_pcie_pearl_init_xfer(ps, tx_bd_size, rx_bd_size);
	अगर (ret) अणु
		pr_err("PCIE xfer init failed\n");
		वापस ret;
	पूर्ण

	/* init शेष irq settings */
	qtnf_init_hdp_irqs(ps);

	/* start with disabled irqs */
	qtnf_disable_hdp_irqs(ps);

	ret = devm_request_irq(&pdev->dev, pdev->irq,
			       &qtnf_pcie_pearl_पूर्णांकerrupt, 0,
			       "qtnf_pearl_irq", (व्योम *)bus);
	अगर (ret) अणु
		pr_err("failed to request pcie irq %d\n", pdev->irq);
		qtnf_pearl_मुक्त_xfer_buffers(ps);
		वापस ret;
	पूर्ण

	tasklet_setup(&ps->base.reclaim_tq, qtnf_pearl_reclaim_tasklet_fn);
	netअगर_napi_add(&bus->mux_dev, &bus->mux_napi,
		       qtnf_pcie_pearl_rx_poll, 10);

	ipc_पूर्णांक.fn = qtnf_pcie_pearl_ipc_gen_ep_पूर्णांक;
	ipc_पूर्णांक.arg = ps;
	qtnf_pcie_init_shm_ipc(&ps->base, &ps->bda->bda_shm_reg1,
			       &ps->bda->bda_shm_reg2, &ipc_पूर्णांक);

	वापस 0;
पूर्ण

अटल व्योम qtnf_pcie_pearl_हटाओ(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_pearl_state *ps = get_bus_priv(bus);

	qtnf_pearl_reset_ep(ps);
	qtnf_pearl_मुक्त_xfer_buffers(ps);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक qtnf_pcie_pearl_suspend(काष्ठा qtnf_bus *bus)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक qtnf_pcie_pearl_resume(काष्ठा qtnf_bus *bus)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा qtnf_bus *qtnf_pcie_pearl_alloc(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qtnf_bus *bus;
	काष्ठा qtnf_pcie_pearl_state *ps;

	bus = devm_kzalloc(&pdev->dev, माप(*bus) + माप(*ps), GFP_KERNEL);
	अगर (!bus)
		वापस शून्य;

	ps = get_bus_priv(bus);
	ps->base.probe_cb = qtnf_pcie_pearl_probe;
	ps->base.हटाओ_cb = qtnf_pcie_pearl_हटाओ;
	ps->base.dma_mask_get_cb = qtnf_pearl_dma_mask_get;
#अगर_घोषित CONFIG_PM_SLEEP
	ps->base.resume_cb = qtnf_pcie_pearl_resume;
	ps->base.suspend_cb = qtnf_pcie_pearl_suspend;
#पूर्ण_अगर

	वापस bus;
पूर्ण
