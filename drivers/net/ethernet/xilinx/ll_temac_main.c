<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Xilinx TEMAC Ethernet device
 *
 * Copyright (c) 2008 Nissin Systems Co., Ltd.,  Yoshio Kashiwagi
 * Copyright (c) 2005-2008 DLA Systems,  David H. Lynch Jr. <dhlii@dlasys.net>
 * Copyright (c) 2008-2009 Secret Lab Technologies Ltd.
 *
 * This is a driver क्रम the Xilinx ll_temac ipcore which is often used
 * in the Virtex and Spartan series of chips.
 *
 * Notes:
 * - The ll_temac hardware uses indirect access क्रम many of the TEMAC
 *   रेजिस्टरs, include the MDIO bus.  However, indirect access to MDIO
 *   रेजिस्टरs take considerably more घड़ी cycles than to TEMAC रेजिस्टरs.
 *   MDIO accesses are दीर्घ, so thपढ़ोs करोing them should probably sleep
 *   rather than busyरुको.  However, since only one indirect access can be
 *   in progress at any given समय, that means that *all* indirect accesses
 *   could end up sleeping (to रुको क्रम an MDIO access to complete).
 *   Fortunately none of the indirect accesses are on the 'hot' path क्रम tx
 *   or rx, so this should be okay.
 *
 * TODO:
 * - Factor out locallink DMA code पूर्णांकo separate driver
 * - Fix support क्रम hardware checksumming.
 * - Testing.  Lots and lots of testing.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/tcp.h>      /* needed क्रम माप(tcphdr) */
#समावेश <linux/udp.h>      /* needed क्रम माप(udphdr) */
#समावेश <linux/phy.h>
#समावेश <linux/in.h>
#समावेश <linux/पन.स>
#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/processor.h>
#समावेश <linux/platक्रमm_data/xilinx-ll-temac.h>

#समावेश "ll_temac.h"

/* Descriptors defines क्रम Tx and Rx DMA */
#घोषणा TX_BD_NUM_DEFAULT		64
#घोषणा RX_BD_NUM_DEFAULT		1024
#घोषणा TX_BD_NUM_MAX			4096
#घोषणा RX_BD_NUM_MAX			4096

/* ---------------------------------------------------------------------
 * Low level रेजिस्टर access functions
 */

अटल u32 _temac_ior_be(काष्ठा temac_local *lp, पूर्णांक offset)
अणु
	वापस ioपढ़ो32be(lp->regs + offset);
पूर्ण

अटल व्योम _temac_iow_be(काष्ठा temac_local *lp, पूर्णांक offset, u32 value)
अणु
	वापस ioग_लिखो32be(value, lp->regs + offset);
पूर्ण

अटल u32 _temac_ior_le(काष्ठा temac_local *lp, पूर्णांक offset)
अणु
	वापस ioपढ़ो32(lp->regs + offset);
पूर्ण

अटल व्योम _temac_iow_le(काष्ठा temac_local *lp, पूर्णांक offset, u32 value)
अणु
	वापस ioग_लिखो32(value, lp->regs + offset);
पूर्ण

अटल bool hard_acs_rdy(काष्ठा temac_local *lp)
अणु
	वापस temac_ior(lp, XTE_RDY0_OFFSET) & XTE_RDY0_HARD_ACS_RDY_MASK;
पूर्ण

अटल bool hard_acs_rdy_or_समयout(काष्ठा temac_local *lp, kसमय_प्रकार समयout)
अणु
	kसमय_प्रकार cur = kसमय_get();

	वापस hard_acs_rdy(lp) || kसमय_after(cur, समयout);
पूर्ण

/* Poll क्रम maximum 20 ms.  This is similar to the 2 jअगरfies @ 100 Hz
 * that was used beक्रमe, and should cover MDIO bus speed करोwn to 3200
 * Hz.
 */
#घोषणा HARD_ACS_RDY_POLL_NS (20 * NSEC_PER_MSEC)

/*
 * temac_indirect_busyरुको - Wait क्रम current indirect रेजिस्टर access
 * to complete.
 */
पूर्णांक temac_indirect_busyरुको(काष्ठा temac_local *lp)
अणु
	kसमय_प्रकार समयout = kसमय_add_ns(kसमय_get(), HARD_ACS_RDY_POLL_NS);

	spin_until_cond(hard_acs_rdy_or_समयout(lp, समयout));
	अगर (WARN_ON(!hard_acs_rdy(lp)))
		वापस -ETIMEDOUT;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * temac_indirect_in32 - Indirect रेजिस्टर पढ़ो access.  This function
 * must be called without lp->indirect_lock being held.
 */
u32 temac_indirect_in32(काष्ठा temac_local *lp, पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक val;

	spin_lock_irqsave(lp->indirect_lock, flags);
	val = temac_indirect_in32_locked(lp, reg);
	spin_unlock_irqrestore(lp->indirect_lock, flags);
	वापस val;
पूर्ण

/*
 * temac_indirect_in32_locked - Indirect रेजिस्टर पढ़ो access.  This
 * function must be called with lp->indirect_lock being held.  Use
 * this together with spin_lock_irqsave/spin_lock_irqrestore to aव्योम
 * repeated lock/unlock and to ensure unपूर्णांकerrupted access to indirect
 * रेजिस्टरs.
 */
u32 temac_indirect_in32_locked(काष्ठा temac_local *lp, पूर्णांक reg)
अणु
	/* This initial रुको should normally not spin, as we always
	 * try to रुको क्रम indirect access to complete beक्रमe
	 * releasing the indirect_lock.
	 */
	अगर (WARN_ON(temac_indirect_busyरुको(lp)))
		वापस -ETIMEDOUT;
	/* Initiate पढ़ो from indirect रेजिस्टर */
	temac_iow(lp, XTE_CTL0_OFFSET, reg);
	/* Wait क्रम indirect रेजिस्टर access to complete.  We really
	 * should not see समयouts, and could even end up causing
	 * problem क्रम following indirect access, so let's make a bit
	 * of WARN noise.
	 */
	अगर (WARN_ON(temac_indirect_busyरुको(lp)))
		वापस -ETIMEDOUT;
	/* Value is पढ़ोy now */
	वापस temac_ior(lp, XTE_LSW0_OFFSET);
पूर्ण

/*
 * temac_indirect_out32 - Indirect रेजिस्टर ग_लिखो access.  This function
 * must be called without lp->indirect_lock being held.
 */
व्योम temac_indirect_out32(काष्ठा temac_local *lp, पूर्णांक reg, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lp->indirect_lock, flags);
	temac_indirect_out32_locked(lp, reg, value);
	spin_unlock_irqrestore(lp->indirect_lock, flags);
पूर्ण

/*
 * temac_indirect_out32_locked - Indirect रेजिस्टर ग_लिखो access.  This
 * function must be called with lp->indirect_lock being held.  Use
 * this together with spin_lock_irqsave/spin_lock_irqrestore to aव्योम
 * repeated lock/unlock and to ensure unपूर्णांकerrupted access to indirect
 * रेजिस्टरs.
 */
व्योम temac_indirect_out32_locked(काष्ठा temac_local *lp, पूर्णांक reg, u32 value)
अणु
	/* As in temac_indirect_in32_locked(), we should normally not
	 * spin here.  And अगर it happens, we actually end up silently
	 * ignoring the ग_लिखो request.  Ouch.
	 */
	अगर (WARN_ON(temac_indirect_busyरुको(lp)))
		वापस;
	/* Initiate ग_लिखो to indirect रेजिस्टर */
	temac_iow(lp, XTE_LSW0_OFFSET, value);
	temac_iow(lp, XTE_CTL0_OFFSET, CNTLREG_WRITE_ENABLE_MASK | reg);
	/* As in temac_indirect_in32_locked(), we should not see समयouts
	 * here.  And अगर it happens, we जारी beक्रमe the ग_लिखो has
	 * completed.  Not good.
	 */
	WARN_ON(temac_indirect_busyरुको(lp));
पूर्ण

/*
 * temac_dma_in32_* - Memory mapped DMA पढ़ो, these function expects a
 * रेजिस्टर input that is based on DCR word addresses which are then
 * converted to memory mapped byte addresses.  To be asचिन्हित to
 * lp->dma_in32.
 */
अटल u32 temac_dma_in32_be(काष्ठा temac_local *lp, पूर्णांक reg)
अणु
	वापस ioपढ़ो32be(lp->sdma_regs + (reg << 2));
पूर्ण

अटल u32 temac_dma_in32_le(काष्ठा temac_local *lp, पूर्णांक reg)
अणु
	वापस ioपढ़ो32(lp->sdma_regs + (reg << 2));
पूर्ण

/*
 * temac_dma_out32_* - Memory mapped DMA पढ़ो, these function expects
 * a रेजिस्टर input that is based on DCR word addresses which are then
 * converted to memory mapped byte addresses.  To be asचिन्हित to
 * lp->dma_out32.
 */
अटल व्योम temac_dma_out32_be(काष्ठा temac_local *lp, पूर्णांक reg, u32 value)
अणु
	ioग_लिखो32be(value, lp->sdma_regs + (reg << 2));
पूर्ण

अटल व्योम temac_dma_out32_le(काष्ठा temac_local *lp, पूर्णांक reg, u32 value)
अणु
	ioग_लिखो32(value, lp->sdma_regs + (reg << 2));
पूर्ण

/* DMA रेजिस्टर access functions can be DCR based or memory mapped.
 * The PowerPC 440 is DCR based, the PowerPC 405 and MicroBlaze are both
 * memory mapped.
 */
#अगर_घोषित CONFIG_PPC_DCR

/*
 * temac_dma_dcr_in32 - DCR based DMA पढ़ो
 */
अटल u32 temac_dma_dcr_in(काष्ठा temac_local *lp, पूर्णांक reg)
अणु
	वापस dcr_पढ़ो(lp->sdma_dcrs, reg);
पूर्ण

/*
 * temac_dma_dcr_out32 - DCR based DMA ग_लिखो
 */
अटल व्योम temac_dma_dcr_out(काष्ठा temac_local *lp, पूर्णांक reg, u32 value)
अणु
	dcr_ग_लिखो(lp->sdma_dcrs, reg, value);
पूर्ण

/*
 * temac_dcr_setup - If the DMA is DCR based, then setup the address and
 * I/O  functions
 */
अटल पूर्णांक temac_dcr_setup(काष्ठा temac_local *lp, काष्ठा platक्रमm_device *op,
				काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक dcrs;

	/* setup the dcr address mapping अगर it's in the device tree */

	dcrs = dcr_resource_start(np, 0);
	अगर (dcrs != 0) अणु
		lp->sdma_dcrs = dcr_map(np, dcrs, dcr_resource_len(np, 0));
		lp->dma_in = temac_dma_dcr_in;
		lp->dma_out = temac_dma_dcr_out;
		dev_dbg(&op->dev, "DCR base: %x\n", dcrs);
		वापस 0;
	पूर्ण
	/* no DCR in the device tree, indicate a failure */
	वापस -1;
पूर्ण

#अन्यथा

/*
 * temac_dcr_setup - This is a stub क्रम when DCR is not supported,
 * such as with MicroBlaze and x86
 */
अटल पूर्णांक temac_dcr_setup(काष्ठा temac_local *lp, काष्ठा platक्रमm_device *op,
				काष्ठा device_node *np)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर

/*
 * temac_dma_bd_release - Release buffer descriptor rings
 */
अटल व्योम temac_dma_bd_release(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	पूर्णांक i;

	/* Reset Local Link (DMA) */
	lp->dma_out(lp, DMA_CONTROL_REG, DMA_CONTROL_RST);

	क्रम (i = 0; i < lp->rx_bd_num; i++) अणु
		अगर (!lp->rx_skb[i])
			अवरोध;
		अन्यथा अणु
			dma_unmap_single(ndev->dev.parent, lp->rx_bd_v[i].phys,
					XTE_MAX_JUMBO_FRAME_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(lp->rx_skb[i]);
		पूर्ण
	पूर्ण
	अगर (lp->rx_bd_v)
		dma_मुक्त_coherent(ndev->dev.parent,
				  माप(*lp->rx_bd_v) * lp->rx_bd_num,
				  lp->rx_bd_v, lp->rx_bd_p);
	अगर (lp->tx_bd_v)
		dma_मुक्त_coherent(ndev->dev.parent,
				  माप(*lp->tx_bd_v) * lp->tx_bd_num,
				  lp->tx_bd_v, lp->tx_bd_p);
पूर्ण

/*
 * temac_dma_bd_init - Setup buffer descriptor rings
 */
अटल पूर्णांक temac_dma_bd_init(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	dma_addr_t skb_dma_addr;
	पूर्णांक i;

	lp->rx_skb = devm_kसुस्मृति(&ndev->dev, lp->rx_bd_num,
				  माप(*lp->rx_skb), GFP_KERNEL);
	अगर (!lp->rx_skb)
		जाओ out;

	/* allocate the tx and rx ring buffer descriptors. */
	/* वापसs a भव address and a physical address. */
	lp->tx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 माप(*lp->tx_bd_v) * lp->tx_bd_num,
					 &lp->tx_bd_p, GFP_KERNEL);
	अगर (!lp->tx_bd_v)
		जाओ out;

	lp->rx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 माप(*lp->rx_bd_v) * lp->rx_bd_num,
					 &lp->rx_bd_p, GFP_KERNEL);
	अगर (!lp->rx_bd_v)
		जाओ out;

	क्रम (i = 0; i < lp->tx_bd_num; i++) अणु
		lp->tx_bd_v[i].next = cpu_to_be32(lp->tx_bd_p
			+ माप(*lp->tx_bd_v) * ((i + 1) % lp->tx_bd_num));
	पूर्ण

	क्रम (i = 0; i < lp->rx_bd_num; i++) अणु
		lp->rx_bd_v[i].next = cpu_to_be32(lp->rx_bd_p
			+ माप(*lp->rx_bd_v) * ((i + 1) % lp->rx_bd_num));

		skb = netdev_alloc_skb_ip_align(ndev,
						XTE_MAX_JUMBO_FRAME_SIZE);
		अगर (!skb)
			जाओ out;

		lp->rx_skb[i] = skb;
		/* वापसs physical address of skb->data */
		skb_dma_addr = dma_map_single(ndev->dev.parent, skb->data,
					      XTE_MAX_JUMBO_FRAME_SIZE,
					      DMA_FROM_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, skb_dma_addr))
			जाओ out;
		lp->rx_bd_v[i].phys = cpu_to_be32(skb_dma_addr);
		lp->rx_bd_v[i].len = cpu_to_be32(XTE_MAX_JUMBO_FRAME_SIZE);
		lp->rx_bd_v[i].app0 = cpu_to_be32(STS_CTRL_APP0_IRQONEND);
	पूर्ण

	/* Configure DMA channel (irq setup) */
	lp->dma_out(lp, TX_CHNL_CTRL,
		    lp->coalesce_delay_tx << 24 | lp->coalesce_count_tx << 16 |
		    0x00000400 | // Use 1 Bit Wide Counters. Currently Not Used!
		    CHNL_CTRL_IRQ_EN | CHNL_CTRL_IRQ_ERR_EN |
		    CHNL_CTRL_IRQ_DLY_EN | CHNL_CTRL_IRQ_COAL_EN);
	lp->dma_out(lp, RX_CHNL_CTRL,
		    lp->coalesce_delay_rx << 24 | lp->coalesce_count_rx << 16 |
		    CHNL_CTRL_IRQ_IOE |
		    CHNL_CTRL_IRQ_EN | CHNL_CTRL_IRQ_ERR_EN |
		    CHNL_CTRL_IRQ_DLY_EN | CHNL_CTRL_IRQ_COAL_EN);

	/* Init descriptor indexes */
	lp->tx_bd_ci = 0;
	lp->tx_bd_tail = 0;
	lp->rx_bd_ci = 0;
	lp->rx_bd_tail = lp->rx_bd_num - 1;

	/* Enable RX DMA transfers */
	wmb();
	lp->dma_out(lp, RX_CURDESC_PTR,  lp->rx_bd_p);
	lp->dma_out(lp, RX_TAILDESC_PTR,
		       lp->rx_bd_p + (माप(*lp->rx_bd_v) * lp->rx_bd_tail));

	/* Prepare क्रम TX DMA transfer */
	lp->dma_out(lp, TX_CURDESC_PTR, lp->tx_bd_p);

	वापस 0;

out:
	temac_dma_bd_release(ndev);
	वापस -ENOMEM;
पूर्ण

/* ---------------------------------------------------------------------
 * net_device_ops
 */

अटल व्योम temac_करो_set_mac_address(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	/* set up unicast MAC address filter set its mac address */
	spin_lock_irqsave(lp->indirect_lock, flags);
	temac_indirect_out32_locked(lp, XTE_UAW0_OFFSET,
				    (ndev->dev_addr[0]) |
				    (ndev->dev_addr[1] << 8) |
				    (ndev->dev_addr[2] << 16) |
				    (ndev->dev_addr[3] << 24));
	/* There are reserved bits in EUAW1
	 * so करोn't affect them Set MAC bits [47:32] in EUAW1 */
	temac_indirect_out32_locked(lp, XTE_UAW1_OFFSET,
				    (ndev->dev_addr[4] & 0x000000ff) |
				    (ndev->dev_addr[5] << 8));
	spin_unlock_irqrestore(lp->indirect_lock, flags);
पूर्ण

अटल पूर्णांक temac_init_mac_address(काष्ठा net_device *ndev, स्थिर व्योम *address)
अणु
	स_नकल(ndev->dev_addr, address, ETH_ALEN);
	अगर (!is_valid_ether_addr(ndev->dev_addr))
		eth_hw_addr_अक्रमom(ndev);
	temac_करो_set_mac_address(ndev);
	वापस 0;
पूर्ण

अटल पूर्णांक temac_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;
	स_नकल(ndev->dev_addr, addr->sa_data, ETH_ALEN);
	temac_करो_set_mac_address(ndev);
	वापस 0;
पूर्ण

अटल व्योम temac_set_multicast_list(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	u32 multi_addr_msw, multi_addr_lsw;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ flags;
	bool promisc_mode_disabled = false;

	अगर (ndev->flags & (IFF_PROMISC | IFF_ALLMULTI) ||
	    (netdev_mc_count(ndev) > MULTICAST_CAM_TABLE_NUM)) अणु
		temac_indirect_out32(lp, XTE_AFM_OFFSET, XTE_AFM_EPPRM_MASK);
		dev_info(&ndev->dev, "Promiscuous mode enabled.\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(lp->indirect_lock, flags);

	अगर (!netdev_mc_empty(ndev)) अणु
		काष्ठा netdev_hw_addr *ha;

		netdev_क्रम_each_mc_addr(ha, ndev) अणु
			अगर (WARN_ON(i >= MULTICAST_CAM_TABLE_NUM))
				अवरोध;
			multi_addr_msw = ((ha->addr[3] << 24) |
					  (ha->addr[2] << 16) |
					  (ha->addr[1] << 8) |
					  (ha->addr[0]));
			temac_indirect_out32_locked(lp, XTE_MAW0_OFFSET,
						    multi_addr_msw);
			multi_addr_lsw = ((ha->addr[5] << 8) |
					  (ha->addr[4]) | (i << 16));
			temac_indirect_out32_locked(lp, XTE_MAW1_OFFSET,
						    multi_addr_lsw);
			i++;
		पूर्ण
	पूर्ण

	/* Clear all or reमुख्यing/unused address table entries */
	जबतक (i < MULTICAST_CAM_TABLE_NUM) अणु
		temac_indirect_out32_locked(lp, XTE_MAW0_OFFSET, 0);
		temac_indirect_out32_locked(lp, XTE_MAW1_OFFSET, i << 16);
		i++;
	पूर्ण

	/* Enable address filter block अगर currently disabled */
	अगर (temac_indirect_in32_locked(lp, XTE_AFM_OFFSET)
	    & XTE_AFM_EPPRM_MASK) अणु
		temac_indirect_out32_locked(lp, XTE_AFM_OFFSET, 0);
		promisc_mode_disabled = true;
	पूर्ण

	spin_unlock_irqrestore(lp->indirect_lock, flags);

	अगर (promisc_mode_disabled)
		dev_info(&ndev->dev, "Promiscuous mode disabled.\n");
पूर्ण

अटल काष्ठा temac_option अणु
	पूर्णांक flg;
	u32 opt;
	u32 reg;
	u32 m_or;
	u32 m_and;
पूर्ण temac_options[] = अणु
	/* Turn on jumbo packet support क्रम both Rx and Tx */
	अणु
		.opt = XTE_OPTION_JUMBO,
		.reg = XTE_TXC_OFFSET,
		.m_or = XTE_TXC_TXJMBO_MASK,
	पूर्ण,
	अणु
		.opt = XTE_OPTION_JUMBO,
		.reg = XTE_RXC1_OFFSET,
		.m_or =XTE_RXC1_RXJMBO_MASK,
	पूर्ण,
	/* Turn on VLAN packet support क्रम both Rx and Tx */
	अणु
		.opt = XTE_OPTION_VLAN,
		.reg = XTE_TXC_OFFSET,
		.m_or =XTE_TXC_TXVLAN_MASK,
	पूर्ण,
	अणु
		.opt = XTE_OPTION_VLAN,
		.reg = XTE_RXC1_OFFSET,
		.m_or =XTE_RXC1_RXVLAN_MASK,
	पूर्ण,
	/* Turn on FCS stripping on receive packets */
	अणु
		.opt = XTE_OPTION_FCS_STRIP,
		.reg = XTE_RXC1_OFFSET,
		.m_or =XTE_RXC1_RXFCS_MASK,
	पूर्ण,
	/* Turn on FCS insertion on transmit packets */
	अणु
		.opt = XTE_OPTION_FCS_INSERT,
		.reg = XTE_TXC_OFFSET,
		.m_or =XTE_TXC_TXFCS_MASK,
	पूर्ण,
	/* Turn on length/type field checking on receive packets */
	अणु
		.opt = XTE_OPTION_LENTYPE_ERR,
		.reg = XTE_RXC1_OFFSET,
		.m_or =XTE_RXC1_RXLT_MASK,
	पूर्ण,
	/* Turn on flow control */
	अणु
		.opt = XTE_OPTION_FLOW_CONTROL,
		.reg = XTE_FCC_OFFSET,
		.m_or =XTE_FCC_RXFLO_MASK,
	पूर्ण,
	/* Turn on flow control */
	अणु
		.opt = XTE_OPTION_FLOW_CONTROL,
		.reg = XTE_FCC_OFFSET,
		.m_or =XTE_FCC_TXFLO_MASK,
	पूर्ण,
	/* Turn on promiscuous frame filtering (all frames are received ) */
	अणु
		.opt = XTE_OPTION_PROMISC,
		.reg = XTE_AFM_OFFSET,
		.m_or =XTE_AFM_EPPRM_MASK,
	पूर्ण,
	/* Enable transmitter अगर not alपढ़ोy enabled */
	अणु
		.opt = XTE_OPTION_TXEN,
		.reg = XTE_TXC_OFFSET,
		.m_or =XTE_TXC_TXEN_MASK,
	पूर्ण,
	/* Enable receiver? */
	अणु
		.opt = XTE_OPTION_RXEN,
		.reg = XTE_RXC1_OFFSET,
		.m_or =XTE_RXC1_RXEN_MASK,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * temac_setoptions
 */
अटल u32 temac_setoptions(काष्ठा net_device *ndev, u32 options)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	काष्ठा temac_option *tp = &temac_options[0];
	पूर्णांक reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(lp->indirect_lock, flags);
	जबतक (tp->opt) अणु
		reg = temac_indirect_in32_locked(lp, tp->reg) & ~tp->m_or;
		अगर (options & tp->opt) अणु
			reg |= tp->m_or;
			temac_indirect_out32_locked(lp, tp->reg, reg);
		पूर्ण
		tp++;
	पूर्ण
	spin_unlock_irqrestore(lp->indirect_lock, flags);
	lp->options |= options;

	वापस 0;
पूर्ण

/* Initialize temac */
अटल व्योम temac_device_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	u32 समयout;
	u32 val;
	अचिन्हित दीर्घ flags;

	/* Perक्रमm a software reset */

	/* 0x300 host enable bit ? */
	/* reset PHY through control रेजिस्टर ?:1 */

	dev_dbg(&ndev->dev, "%s()\n", __func__);

	/* Reset the receiver and रुको क्रम it to finish reset */
	temac_indirect_out32(lp, XTE_RXC1_OFFSET, XTE_RXC1_RXRST_MASK);
	समयout = 1000;
	जबतक (temac_indirect_in32(lp, XTE_RXC1_OFFSET) & XTE_RXC1_RXRST_MASK) अणु
		udelay(1);
		अगर (--समयout == 0) अणु
			dev_err(&ndev->dev,
				"temac_device_reset RX reset timeout!!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* Reset the transmitter and रुको क्रम it to finish reset */
	temac_indirect_out32(lp, XTE_TXC_OFFSET, XTE_TXC_TXRST_MASK);
	समयout = 1000;
	जबतक (temac_indirect_in32(lp, XTE_TXC_OFFSET) & XTE_TXC_TXRST_MASK) अणु
		udelay(1);
		अगर (--समयout == 0) अणु
			dev_err(&ndev->dev,
				"temac_device_reset TX reset timeout!!\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/* Disable the receiver */
	spin_lock_irqsave(lp->indirect_lock, flags);
	val = temac_indirect_in32_locked(lp, XTE_RXC1_OFFSET);
	temac_indirect_out32_locked(lp, XTE_RXC1_OFFSET,
				    val & ~XTE_RXC1_RXEN_MASK);
	spin_unlock_irqrestore(lp->indirect_lock, flags);

	/* Reset Local Link (DMA) */
	lp->dma_out(lp, DMA_CONTROL_REG, DMA_CONTROL_RST);
	समयout = 1000;
	जबतक (lp->dma_in(lp, DMA_CONTROL_REG) & DMA_CONTROL_RST) अणु
		udelay(1);
		अगर (--समयout == 0) अणु
			dev_err(&ndev->dev,
				"temac_device_reset DMA reset timeout!!\n");
			अवरोध;
		पूर्ण
	पूर्ण
	lp->dma_out(lp, DMA_CONTROL_REG, DMA_TAIL_ENABLE);

	अगर (temac_dma_bd_init(ndev)) अणु
		dev_err(&ndev->dev,
				"temac_device_reset descriptor allocation failed\n");
	पूर्ण

	spin_lock_irqsave(lp->indirect_lock, flags);
	temac_indirect_out32_locked(lp, XTE_RXC0_OFFSET, 0);
	temac_indirect_out32_locked(lp, XTE_RXC1_OFFSET, 0);
	temac_indirect_out32_locked(lp, XTE_TXC_OFFSET, 0);
	temac_indirect_out32_locked(lp, XTE_FCC_OFFSET, XTE_FCC_RXFLO_MASK);
	spin_unlock_irqrestore(lp->indirect_lock, flags);

	/* Sync शेष options with HW
	 * but leave receiver and transmitter disabled.  */
	temac_setoptions(ndev,
			 lp->options & ~(XTE_OPTION_TXEN | XTE_OPTION_RXEN));

	temac_करो_set_mac_address(ndev);

	/* Set address filter table */
	temac_set_multicast_list(ndev);
	अगर (temac_setoptions(ndev, lp->options))
		dev_err(&ndev->dev, "Error setting TEMAC options\n");

	/* Init Driver variable */
	netअगर_trans_update(ndev); /* prevent tx समयout */
पूर्ण

अटल व्योम temac_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	काष्ठा phy_device *phy = ndev->phydev;
	u32 mii_speed;
	पूर्णांक link_state;
	अचिन्हित दीर्घ flags;

	/* hash together the state values to decide अगर something has changed */
	link_state = phy->speed | (phy->duplex << 1) | phy->link;

	अगर (lp->last_link != link_state) अणु
		spin_lock_irqsave(lp->indirect_lock, flags);
		mii_speed = temac_indirect_in32_locked(lp, XTE_EMCFG_OFFSET);
		mii_speed &= ~XTE_EMCFG_LINKSPD_MASK;

		चयन (phy->speed) अणु
		हाल SPEED_1000: mii_speed |= XTE_EMCFG_LINKSPD_1000; अवरोध;
		हाल SPEED_100: mii_speed |= XTE_EMCFG_LINKSPD_100; अवरोध;
		हाल SPEED_10: mii_speed |= XTE_EMCFG_LINKSPD_10; अवरोध;
		पूर्ण

		/* Write new speed setting out to TEMAC */
		temac_indirect_out32_locked(lp, XTE_EMCFG_OFFSET, mii_speed);
		spin_unlock_irqrestore(lp->indirect_lock, flags);

		lp->last_link = link_state;
		phy_prपूर्णांक_status(phy);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_64BIT

अटल व्योम ptr_to_txbd(व्योम *p, काष्ठा cdmac_bd *bd)
अणु
	bd->app3 = (u32)(((u64)p) >> 32);
	bd->app4 = (u32)((u64)p & 0xFFFFFFFF);
पूर्ण

अटल व्योम *ptr_from_txbd(काष्ठा cdmac_bd *bd)
अणु
	वापस (व्योम *)(((u64)(bd->app3) << 32) | bd->app4);
पूर्ण

#अन्यथा

अटल व्योम ptr_to_txbd(व्योम *p, काष्ठा cdmac_bd *bd)
अणु
	bd->app4 = (u32)p;
पूर्ण

अटल व्योम *ptr_from_txbd(काष्ठा cdmac_bd *bd)
अणु
	वापस (व्योम *)(bd->app4);
पूर्ण

#पूर्ण_अगर

अटल व्योम temac_start_xmit_करोne(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	काष्ठा cdmac_bd *cur_p;
	अचिन्हित पूर्णांक stat = 0;
	काष्ठा sk_buff *skb;

	cur_p = &lp->tx_bd_v[lp->tx_bd_ci];
	stat = be32_to_cpu(cur_p->app0);

	जबतक (stat & STS_CTRL_APP0_CMPLT) अणु
		/* Make sure that the other fields are पढ़ो after bd is
		 * released by dma
		 */
		rmb();
		dma_unmap_single(ndev->dev.parent, be32_to_cpu(cur_p->phys),
				 be32_to_cpu(cur_p->len), DMA_TO_DEVICE);
		skb = (काष्ठा sk_buff *)ptr_from_txbd(cur_p);
		अगर (skb)
			dev_consume_skb_irq(skb);
		cur_p->app1 = 0;
		cur_p->app2 = 0;
		cur_p->app3 = 0;
		cur_p->app4 = 0;

		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += be32_to_cpu(cur_p->len);

		/* app0 must be visible last, as it is used to flag
		 * availability of the bd
		 */
		smp_mb();
		cur_p->app0 = 0;

		lp->tx_bd_ci++;
		अगर (lp->tx_bd_ci >= lp->tx_bd_num)
			lp->tx_bd_ci = 0;

		cur_p = &lp->tx_bd_v[lp->tx_bd_ci];
		stat = be32_to_cpu(cur_p->app0);
	पूर्ण

	/* Matches barrier in temac_start_xmit */
	smp_mb();

	netअगर_wake_queue(ndev);
पूर्ण

अटल अंतरभूत पूर्णांक temac_check_tx_bd_space(काष्ठा temac_local *lp, पूर्णांक num_frag)
अणु
	काष्ठा cdmac_bd *cur_p;
	पूर्णांक tail;

	tail = lp->tx_bd_tail;
	cur_p = &lp->tx_bd_v[tail];

	करो अणु
		अगर (cur_p->app0)
			वापस NETDEV_TX_BUSY;

		/* Make sure to पढ़ो next bd app0 after this one */
		rmb();

		tail++;
		अगर (tail >= lp->tx_bd_num)
			tail = 0;

		cur_p = &lp->tx_bd_v[tail];
		num_frag--;
	पूर्ण जबतक (num_frag >= 0);

	वापस 0;
पूर्ण

अटल netdev_tx_t
temac_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	काष्ठा cdmac_bd *cur_p;
	dma_addr_t tail_p, skb_dma_addr;
	पूर्णांक ii;
	अचिन्हित दीर्घ num_frag;
	skb_frag_t *frag;

	num_frag = skb_shinfo(skb)->nr_frags;
	frag = &skb_shinfo(skb)->frags[0];
	cur_p = &lp->tx_bd_v[lp->tx_bd_tail];

	अगर (temac_check_tx_bd_space(lp, num_frag + 1)) अणु
		अगर (netअगर_queue_stopped(ndev))
			वापस NETDEV_TX_BUSY;

		netअगर_stop_queue(ndev);

		/* Matches barrier in temac_start_xmit_करोne */
		smp_mb();

		/* Space might have just been मुक्तd - check again */
		अगर (temac_check_tx_bd_space(lp, num_frag + 1))
			वापस NETDEV_TX_BUSY;

		netअगर_wake_queue(ndev);
	पूर्ण

	cur_p->app0 = 0;
	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अचिन्हित पूर्णांक csum_start_off = skb_checksum_start_offset(skb);
		अचिन्हित पूर्णांक csum_index_off = csum_start_off + skb->csum_offset;

		cur_p->app0 |= cpu_to_be32(0x000001); /* TX Checksum Enabled */
		cur_p->app1 = cpu_to_be32((csum_start_off << 16)
					  | csum_index_off);
		cur_p->app2 = 0;  /* initial checksum seed */
	पूर्ण

	cur_p->app0 |= cpu_to_be32(STS_CTRL_APP0_SOP);
	skb_dma_addr = dma_map_single(ndev->dev.parent, skb->data,
				      skb_headlen(skb), DMA_TO_DEVICE);
	cur_p->len = cpu_to_be32(skb_headlen(skb));
	अगर (WARN_ON_ONCE(dma_mapping_error(ndev->dev.parent, skb_dma_addr))) अणु
		dev_kमुक्त_skb_any(skb);
		ndev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	cur_p->phys = cpu_to_be32(skb_dma_addr);

	क्रम (ii = 0; ii < num_frag; ii++) अणु
		अगर (++lp->tx_bd_tail >= lp->tx_bd_num)
			lp->tx_bd_tail = 0;

		cur_p = &lp->tx_bd_v[lp->tx_bd_tail];
		skb_dma_addr = dma_map_single(ndev->dev.parent,
					      skb_frag_address(frag),
					      skb_frag_size(frag),
					      DMA_TO_DEVICE);
		अगर (dma_mapping_error(ndev->dev.parent, skb_dma_addr)) अणु
			अगर (--lp->tx_bd_tail < 0)
				lp->tx_bd_tail = lp->tx_bd_num - 1;
			cur_p = &lp->tx_bd_v[lp->tx_bd_tail];
			जबतक (--ii >= 0) अणु
				--frag;
				dma_unmap_single(ndev->dev.parent,
						 be32_to_cpu(cur_p->phys),
						 skb_frag_size(frag),
						 DMA_TO_DEVICE);
				अगर (--lp->tx_bd_tail < 0)
					lp->tx_bd_tail = lp->tx_bd_num - 1;
				cur_p = &lp->tx_bd_v[lp->tx_bd_tail];
			पूर्ण
			dma_unmap_single(ndev->dev.parent,
					 be32_to_cpu(cur_p->phys),
					 skb_headlen(skb), DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(skb);
			ndev->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
		cur_p->phys = cpu_to_be32(skb_dma_addr);
		cur_p->len = cpu_to_be32(skb_frag_size(frag));
		cur_p->app0 = 0;
		frag++;
	पूर्ण
	cur_p->app0 |= cpu_to_be32(STS_CTRL_APP0_EOP);

	/* Mark last fragment with skb address, so it can be consumed
	 * in temac_start_xmit_करोne()
	 */
	ptr_to_txbd((व्योम *)skb, cur_p);

	tail_p = lp->tx_bd_p + माप(*lp->tx_bd_v) * lp->tx_bd_tail;
	lp->tx_bd_tail++;
	अगर (lp->tx_bd_tail >= lp->tx_bd_num)
		lp->tx_bd_tail = 0;

	skb_tx_बारtamp(skb);

	/* Kick off the transfer */
	wmb();
	lp->dma_out(lp, TX_TAILDESC_PTR, tail_p); /* DMA start */

	अगर (temac_check_tx_bd_space(lp, MAX_SKB_FRAGS + 1)) अणु
		netdev_info(ndev, "%s -> netif_stop_queue\n", __func__);
		netअगर_stop_queue(ndev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ll_temac_recv_buffers_available(काष्ठा temac_local *lp)
अणु
	पूर्णांक available;

	अगर (!lp->rx_skb[lp->rx_bd_ci])
		वापस 0;
	available = 1 + lp->rx_bd_tail - lp->rx_bd_ci;
	अगर (available <= 0)
		available += lp->rx_bd_num;
	वापस available;
पूर्ण

अटल व्योम ll_temac_recv(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;
	पूर्णांक rx_bd;
	bool update_tail = false;

	spin_lock_irqsave(&lp->rx_lock, flags);

	/* Process all received buffers, passing them on network
	 * stack.  After this, the buffer descriptors will be in an
	 * un-allocated stage, where no skb is allocated क्रम it, and
	 * they are thereक्रमe not available क्रम TEMAC/DMA.
	 */
	करो अणु
		काष्ठा cdmac_bd *bd = &lp->rx_bd_v[lp->rx_bd_ci];
		काष्ठा sk_buff *skb = lp->rx_skb[lp->rx_bd_ci];
		अचिन्हित पूर्णांक bdstat = be32_to_cpu(bd->app0);
		पूर्णांक length;

		/* While this should not normally happen, we can end
		 * here when GFP_ATOMIC allocations fail, and we
		 * thereक्रमe have un-allocated buffers.
		 */
		अगर (!skb)
			अवरोध;

		/* Loop over all completed buffer descriptors */
		अगर (!(bdstat & STS_CTRL_APP0_CMPLT))
			अवरोध;

		dma_unmap_single(ndev->dev.parent, be32_to_cpu(bd->phys),
				 XTE_MAX_JUMBO_FRAME_SIZE, DMA_FROM_DEVICE);
		/* The buffer is not valid क्रम DMA anymore */
		bd->phys = 0;
		bd->len = 0;

		length = be32_to_cpu(bd->app4) & 0x3FFF;
		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, ndev);
		skb_checksum_none_निश्चित(skb);

		/* अगर we're करोing rx csum offload, set it up */
		अगर (((lp->temac_features & TEMAC_FEATURE_RX_CSUM) != 0) &&
		    (skb->protocol == htons(ETH_P_IP)) &&
		    (skb->len > 64)) अणु

			/* Convert from device endianness (be32) to cpu
			 * endiannes, and अगर necessary swap the bytes
			 * (back) क्रम proper IP checksum byte order
			 * (be16).
			 */
			skb->csum = htons(be32_to_cpu(bd->app3) & 0xFFFF);
			skb->ip_summed = CHECKSUM_COMPLETE;
		पूर्ण

		अगर (!skb_defer_rx_बारtamp(skb))
			netअगर_rx(skb);
		/* The skb buffer is now owned by network stack above */
		lp->rx_skb[lp->rx_bd_ci] = शून्य;

		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += length;

		rx_bd = lp->rx_bd_ci;
		अगर (++lp->rx_bd_ci >= lp->rx_bd_num)
			lp->rx_bd_ci = 0;
	पूर्ण जबतक (rx_bd != lp->rx_bd_tail);

	/* DMA operations will halt when the last buffer descriptor is
	 * processed (ie. the one poपूर्णांकed to by RX_TAILDESC_PTR).
	 * When that happens, no more पूर्णांकerrupt events will be
	 * generated.  No IRQ_COAL or IRQ_DLY, and not even an
	 * IRQ_ERR.  To aव्योम stalling, we schedule a delayed work
	 * when there is a potential risk of that happening.  The work
	 * will call this function, and thus re-schedule itself until
	 * enough buffers are available again.
	 */
	अगर (ll_temac_recv_buffers_available(lp) < lp->coalesce_count_rx)
		schedule_delayed_work(&lp->restart_work, HZ / 1000);

	/* Allocate new buffers क्रम those buffer descriptors that were
	 * passed to network stack.  Note that GFP_ATOMIC allocations
	 * can fail (e.g. when a larger burst of GFP_ATOMIC
	 * allocations occurs), so जबतक we try to allocate all
	 * buffers in the same पूर्णांकerrupt where they were processed, we
	 * जारी with what we could get in हाल of allocation
	 * failure.  Allocation of reमुख्यing buffers will be retried
	 * in following calls.
	 */
	जबतक (1) अणु
		काष्ठा sk_buff *skb;
		काष्ठा cdmac_bd *bd;
		dma_addr_t skb_dma_addr;

		rx_bd = lp->rx_bd_tail + 1;
		अगर (rx_bd >= lp->rx_bd_num)
			rx_bd = 0;
		bd = &lp->rx_bd_v[rx_bd];

		अगर (bd->phys)
			अवरोध;	/* All skb's allocated */

		skb = netdev_alloc_skb_ip_align(ndev, XTE_MAX_JUMBO_FRAME_SIZE);
		अगर (!skb) अणु
			dev_warn(&ndev->dev, "skb alloc failed\n");
			अवरोध;
		पूर्ण

		skb_dma_addr = dma_map_single(ndev->dev.parent, skb->data,
					      XTE_MAX_JUMBO_FRAME_SIZE,
					      DMA_FROM_DEVICE);
		अगर (WARN_ON_ONCE(dma_mapping_error(ndev->dev.parent,
						   skb_dma_addr))) अणु
			dev_kमुक्त_skb_any(skb);
			अवरोध;
		पूर्ण

		bd->phys = cpu_to_be32(skb_dma_addr);
		bd->len = cpu_to_be32(XTE_MAX_JUMBO_FRAME_SIZE);
		bd->app0 = cpu_to_be32(STS_CTRL_APP0_IRQONEND);
		lp->rx_skb[rx_bd] = skb;

		lp->rx_bd_tail = rx_bd;
		update_tail = true;
	पूर्ण

	/* Move tail poपूर्णांकer when buffers have been allocated */
	अगर (update_tail) अणु
		lp->dma_out(lp, RX_TAILDESC_PTR,
			lp->rx_bd_p + माप(*lp->rx_bd_v) * lp->rx_bd_tail);
	पूर्ण

	spin_unlock_irqrestore(&lp->rx_lock, flags);
पूर्ण

/* Function scheduled to ensure a restart in हाल of DMA halt
 * condition caused by running out of buffer descriptors.
 */
अटल व्योम ll_temac_restart_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा temac_local *lp = container_of(work, काष्ठा temac_local,
					      restart_work.work);
	काष्ठा net_device *ndev = lp->ndev;

	ll_temac_recv(ndev);
पूर्ण

अटल irqवापस_t ll_temac_tx_irq(पूर्णांक irq, व्योम *_ndev)
अणु
	काष्ठा net_device *ndev = _ndev;
	काष्ठा temac_local *lp = netdev_priv(ndev);
	अचिन्हित पूर्णांक status;

	status = lp->dma_in(lp, TX_IRQ_REG);
	lp->dma_out(lp, TX_IRQ_REG, status);

	अगर (status & (IRQ_COAL | IRQ_DLY))
		temac_start_xmit_करोne(lp->ndev);
	अगर (status & (IRQ_ERR | IRQ_DMAERR))
		dev_err_ratelimited(&ndev->dev,
				    "TX error 0x%x TX_CHNL_STS=0x%08x\n",
				    status, lp->dma_in(lp, TX_CHNL_STS));

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ll_temac_rx_irq(पूर्णांक irq, व्योम *_ndev)
अणु
	काष्ठा net_device *ndev = _ndev;
	काष्ठा temac_local *lp = netdev_priv(ndev);
	अचिन्हित पूर्णांक status;

	/* Read and clear the status रेजिस्टरs */
	status = lp->dma_in(lp, RX_IRQ_REG);
	lp->dma_out(lp, RX_IRQ_REG, status);

	अगर (status & (IRQ_COAL | IRQ_DLY))
		ll_temac_recv(lp->ndev);
	अगर (status & (IRQ_ERR | IRQ_DMAERR))
		dev_err_ratelimited(&ndev->dev,
				    "RX error 0x%x RX_CHNL_STS=0x%08x\n",
				    status, lp->dma_in(lp, RX_CHNL_STS));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक temac_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	काष्ठा phy_device *phydev = शून्य;
	पूर्णांक rc;

	dev_dbg(&ndev->dev, "temac_open()\n");

	अगर (lp->phy_node) अणु
		phydev = of_phy_connect(lp->ndev, lp->phy_node,
					temac_adjust_link, 0, 0);
		अगर (!phydev) अणु
			dev_err(lp->dev, "of_phy_connect() failed\n");
			वापस -ENODEV;
		पूर्ण
		phy_start(phydev);
	पूर्ण अन्यथा अगर (म_माप(lp->phy_name) > 0) अणु
		phydev = phy_connect(lp->ndev, lp->phy_name, temac_adjust_link,
				     lp->phy_पूर्णांकerface);
		अगर (IS_ERR(phydev)) अणु
			dev_err(lp->dev, "phy_connect() failed\n");
			वापस PTR_ERR(phydev);
		पूर्ण
		phy_start(phydev);
	पूर्ण

	temac_device_reset(ndev);

	rc = request_irq(lp->tx_irq, ll_temac_tx_irq, 0, ndev->name, ndev);
	अगर (rc)
		जाओ err_tx_irq;
	rc = request_irq(lp->rx_irq, ll_temac_rx_irq, 0, ndev->name, ndev);
	अगर (rc)
		जाओ err_rx_irq;

	वापस 0;

 err_rx_irq:
	मुक्त_irq(lp->tx_irq, ndev);
 err_tx_irq:
	अगर (phydev)
		phy_disconnect(phydev);
	dev_err(lp->dev, "request_irq() failed\n");
	वापस rc;
पूर्ण

अटल पूर्णांक temac_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);
	काष्ठा phy_device *phydev = ndev->phydev;

	dev_dbg(&ndev->dev, "temac_close()\n");

	cancel_delayed_work_sync(&lp->restart_work);

	मुक्त_irq(lp->tx_irq, ndev);
	मुक्त_irq(lp->rx_irq, ndev);

	अगर (phydev)
		phy_disconnect(phydev);

	temac_dma_bd_release(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम
temac_poll_controller(काष्ठा net_device *ndev)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);

	disable_irq(lp->tx_irq);
	disable_irq(lp->rx_irq);

	ll_temac_rx_irq(lp->tx_irq, ndev);
	ll_temac_tx_irq(lp->rx_irq, ndev);

	enable_irq(lp->tx_irq);
	enable_irq(lp->rx_irq);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops temac_netdev_ops = अणु
	.nकरो_खोलो = temac_खोलो,
	.nकरो_stop = temac_stop,
	.nकरो_start_xmit = temac_start_xmit,
	.nकरो_set_rx_mode = temac_set_multicast_list,
	.nकरो_set_mac_address = temac_set_mac_address,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_करो_ioctl = phy_करो_ioctl_running,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = temac_poll_controller,
#पूर्ण_अगर
पूर्ण;

/* ---------------------------------------------------------------------
 * SYSFS device attributes
 */
अटल sमाप_प्रकार temac_show_llink_regs(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा temac_local *lp = netdev_priv(ndev);
	पूर्णांक i, len = 0;

	क्रम (i = 0; i < 0x11; i++)
		len += प्र_लिखो(buf + len, "%.8x%s", lp->dma_in(lp, i),
			       (i % 8) == 7 ? "\n" : " ");
	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

अटल DEVICE_ATTR(llink_regs, 0440, temac_show_llink_regs, शून्य);

अटल काष्ठा attribute *temac_device_attrs[] = अणु
	&dev_attr_llink_regs.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group temac_attr_group = अणु
	.attrs = temac_device_attrs,
पूर्ण;

/* ---------------------------------------------------------------------
 * ethtool support
 */

अटल व्योम ll_temac_ethtools_get_ringparam(काष्ठा net_device *ndev,
					    काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);

	ering->rx_max_pending = RX_BD_NUM_MAX;
	ering->rx_mini_max_pending = 0;
	ering->rx_jumbo_max_pending = 0;
	ering->tx_max_pending = TX_BD_NUM_MAX;
	ering->rx_pending = lp->rx_bd_num;
	ering->rx_mini_pending = 0;
	ering->rx_jumbo_pending = 0;
	ering->tx_pending = lp->tx_bd_num;
पूर्ण

अटल पूर्णांक ll_temac_ethtools_set_ringparam(काष्ठा net_device *ndev,
					   काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);

	अगर (ering->rx_pending > RX_BD_NUM_MAX ||
	    ering->rx_mini_pending ||
	    ering->rx_jumbo_pending ||
	    ering->rx_pending > TX_BD_NUM_MAX)
		वापस -EINVAL;

	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	lp->rx_bd_num = ering->rx_pending;
	lp->tx_bd_num = ering->tx_pending;
	वापस 0;
पूर्ण

अटल पूर्णांक ll_temac_ethtools_get_coalesce(काष्ठा net_device *ndev,
					  काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);

	ec->rx_max_coalesced_frames = lp->coalesce_count_rx;
	ec->tx_max_coalesced_frames = lp->coalesce_count_tx;
	ec->rx_coalesce_usecs = (lp->coalesce_delay_rx * 512) / 100;
	ec->tx_coalesce_usecs = (lp->coalesce_delay_tx * 512) / 100;
	वापस 0;
पूर्ण

अटल पूर्णांक ll_temac_ethtools_set_coalesce(काष्ठा net_device *ndev,
					  काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा temac_local *lp = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		netdev_err(ndev,
			   "Please stop netif before applying configuration\n");
		वापस -EFAULT;
	पूर्ण

	अगर (ec->rx_max_coalesced_frames)
		lp->coalesce_count_rx = ec->rx_max_coalesced_frames;
	अगर (ec->tx_max_coalesced_frames)
		lp->coalesce_count_tx = ec->tx_max_coalesced_frames;
	/* With typical LocalLink घड़ी speed of 200 MHz and
	 * C_PRESCALAR=1023, each delay count corresponds to 5.12 us.
	 */
	अगर (ec->rx_coalesce_usecs)
		lp->coalesce_delay_rx =
			min(255U, (ec->rx_coalesce_usecs * 100) / 512);
	अगर (ec->tx_coalesce_usecs)
		lp->coalesce_delay_tx =
			min(255U, (ec->tx_coalesce_usecs * 100) / 512);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops temac_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.nway_reset = phy_ethtool_nway_reset,
	.get_link = ethtool_op_get_link,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
	.get_ringparam	= ll_temac_ethtools_get_ringparam,
	.set_ringparam	= ll_temac_ethtools_set_ringparam,
	.get_coalesce	= ll_temac_ethtools_get_coalesce,
	.set_coalesce	= ll_temac_ethtools_set_coalesce,
पूर्ण;

अटल पूर्णांक temac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ll_temac_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *temac_np = dev_of_node(&pdev->dev), *dma_np;
	काष्ठा temac_local *lp;
	काष्ठा net_device *ndev;
	u8 addr[ETH_ALEN];
	__be32 *p;
	bool little_endian;
	पूर्णांक rc = 0;

	/* Init network device काष्ठाure */
	ndev = devm_alloc_etherdev(&pdev->dev, माप(*lp));
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->features = NETIF_F_SG;
	ndev->netdev_ops = &temac_netdev_ops;
	ndev->ethtool_ops = &temac_ethtool_ops;
#अगर 0
	ndev->features |= NETIF_F_IP_CSUM; /* Can checksum TCP/UDP over IPv4. */
	ndev->features |= NETIF_F_HW_CSUM; /* Can checksum all the packets. */
	ndev->features |= NETIF_F_IPV6_CSUM; /* Can checksum IPV6 TCP/UDP */
	ndev->features |= NETIF_F_HIGHDMA; /* Can DMA to high memory. */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_TX; /* Transmit VLAN hw accel */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_RX; /* Receive VLAN hw acceleration */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER; /* Receive VLAN filtering */
	ndev->features |= NETIF_F_VLAN_CHALLENGED; /* cannot handle VLAN pkts */
	ndev->features |= NETIF_F_GSO; /* Enable software GSO. */
	ndev->features |= NETIF_F_MULTI_QUEUE; /* Has multiple TX/RX queues */
	ndev->features |= NETIF_F_LRO; /* large receive offload */
#पूर्ण_अगर

	/* setup temac निजी info काष्ठाure */
	lp = netdev_priv(ndev);
	lp->ndev = ndev;
	lp->dev = &pdev->dev;
	lp->options = XTE_OPTION_DEFAULTS;
	lp->rx_bd_num = RX_BD_NUM_DEFAULT;
	lp->tx_bd_num = TX_BD_NUM_DEFAULT;
	spin_lock_init(&lp->rx_lock);
	INIT_DELAYED_WORK(&lp->restart_work, ll_temac_restart_work_func);

	/* Setup mutex क्रम synchronization of indirect रेजिस्टर access */
	अगर (pdata) अणु
		अगर (!pdata->indirect_lock) अणु
			dev_err(&pdev->dev,
				"indirect_lock missing in platform_data\n");
			वापस -EINVAL;
		पूर्ण
		lp->indirect_lock = pdata->indirect_lock;
	पूर्ण अन्यथा अणु
		lp->indirect_lock = devm_kदो_स्मृति(&pdev->dev,
						 माप(*lp->indirect_lock),
						 GFP_KERNEL);
		spin_lock_init(lp->indirect_lock);
	पूर्ण

	/* map device रेजिस्टरs */
	lp->regs = devm_platक्रमm_ioremap_resource_byname(pdev, 0);
	अगर (IS_ERR(lp->regs)) अणु
		dev_err(&pdev->dev, "could not map TEMAC registers\n");
		वापस -ENOMEM;
	पूर्ण

	/* Select रेजिस्टर access functions with the specअगरied
	 * endianness mode.  Default क्रम OF devices is big-endian.
	 */
	little_endian = false;
	अगर (temac_np) अणु
		अगर (of_get_property(temac_np, "little-endian", शून्य))
			little_endian = true;
	पूर्ण अन्यथा अगर (pdata) अणु
		little_endian = pdata->reg_little_endian;
	पूर्ण
	अगर (little_endian) अणु
		lp->temac_ior = _temac_ior_le;
		lp->temac_iow = _temac_iow_le;
	पूर्ण अन्यथा अणु
		lp->temac_ior = _temac_ior_be;
		lp->temac_iow = _temac_iow_be;
	पूर्ण

	/* Setup checksum offload, but शेष to off अगर not specअगरied */
	lp->temac_features = 0;
	अगर (temac_np) अणु
		p = (__be32 *)of_get_property(temac_np, "xlnx,txcsum", शून्य);
		अगर (p && be32_to_cpu(*p))
			lp->temac_features |= TEMAC_FEATURE_TX_CSUM;
		p = (__be32 *)of_get_property(temac_np, "xlnx,rxcsum", शून्य);
		अगर (p && be32_to_cpu(*p))
			lp->temac_features |= TEMAC_FEATURE_RX_CSUM;
	पूर्ण अन्यथा अगर (pdata) अणु
		अगर (pdata->txcsum)
			lp->temac_features |= TEMAC_FEATURE_TX_CSUM;
		अगर (pdata->rxcsum)
			lp->temac_features |= TEMAC_FEATURE_RX_CSUM;
	पूर्ण
	अगर (lp->temac_features & TEMAC_FEATURE_TX_CSUM)
		/* Can checksum TCP/UDP over IPv4. */
		ndev->features |= NETIF_F_IP_CSUM;

	/* Defaults क्रम IRQ delay/coalescing setup.  These are
	 * configuration values, so करोes not beदीर्घ in device-tree.
	 */
	lp->coalesce_delay_tx = 0x10;
	lp->coalesce_count_tx = 0x22;
	lp->coalesce_delay_rx = 0xff;
	lp->coalesce_count_rx = 0x07;

	/* Setup LocalLink DMA */
	अगर (temac_np) अणु
		/* Find the DMA node, map the DMA रेजिस्टरs, and
		 * decode the DMA IRQs.
		 */
		dma_np = of_parse_phandle(temac_np, "llink-connected", 0);
		अगर (!dma_np) अणु
			dev_err(&pdev->dev, "could not find DMA node\n");
			वापस -ENODEV;
		पूर्ण

		/* Setup the DMA रेजिस्टर accesses, could be DCR or
		 * memory mapped.
		 */
		अगर (temac_dcr_setup(lp, pdev, dma_np)) अणु
			/* no DCR in the device tree, try non-DCR */
			lp->sdma_regs = devm_of_iomap(&pdev->dev, dma_np, 0,
						      शून्य);
			अगर (IS_ERR(lp->sdma_regs)) अणु
				dev_err(&pdev->dev,
					"unable to map DMA registers\n");
				of_node_put(dma_np);
				वापस PTR_ERR(lp->sdma_regs);
			पूर्ण
			अगर (of_get_property(dma_np, "little-endian", शून्य)) अणु
				lp->dma_in = temac_dma_in32_le;
				lp->dma_out = temac_dma_out32_le;
			पूर्ण अन्यथा अणु
				lp->dma_in = temac_dma_in32_be;
				lp->dma_out = temac_dma_out32_be;
			पूर्ण
			dev_dbg(&pdev->dev, "MEM base: %p\n", lp->sdma_regs);
		पूर्ण

		/* Get DMA RX and TX पूर्णांकerrupts */
		lp->rx_irq = irq_of_parse_and_map(dma_np, 0);
		lp->tx_irq = irq_of_parse_and_map(dma_np, 1);

		/* Finished with the DMA node; drop the reference */
		of_node_put(dma_np);
	पूर्ण अन्यथा अगर (pdata) अणु
		/* 2nd memory resource specअगरies DMA रेजिस्टरs */
		lp->sdma_regs = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(lp->sdma_regs)) अणु
			dev_err(&pdev->dev,
				"could not map DMA registers\n");
			वापस PTR_ERR(lp->sdma_regs);
		पूर्ण
		अगर (pdata->dma_little_endian) अणु
			lp->dma_in = temac_dma_in32_le;
			lp->dma_out = temac_dma_out32_le;
		पूर्ण अन्यथा अणु
			lp->dma_in = temac_dma_in32_be;
			lp->dma_out = temac_dma_out32_be;
		पूर्ण

		/* Get DMA RX and TX पूर्णांकerrupts */
		lp->rx_irq = platक्रमm_get_irq(pdev, 0);
		lp->tx_irq = platक्रमm_get_irq(pdev, 1);

		/* IRQ delay/coalescing setup */
		अगर (pdata->tx_irq_समयout || pdata->tx_irq_count) अणु
			lp->coalesce_delay_tx = pdata->tx_irq_समयout;
			lp->coalesce_count_tx = pdata->tx_irq_count;
		पूर्ण
		अगर (pdata->rx_irq_समयout || pdata->rx_irq_count) अणु
			lp->coalesce_delay_rx = pdata->rx_irq_समयout;
			lp->coalesce_count_rx = pdata->rx_irq_count;
		पूर्ण
	पूर्ण

	/* Error handle वापसed DMA RX and TX पूर्णांकerrupts */
	अगर (lp->rx_irq < 0) अणु
		अगर (lp->rx_irq != -EPROBE_DEFER)
			dev_err(&pdev->dev, "could not get DMA RX irq\n");
		वापस lp->rx_irq;
	पूर्ण
	अगर (lp->tx_irq < 0) अणु
		अगर (lp->tx_irq != -EPROBE_DEFER)
			dev_err(&pdev->dev, "could not get DMA TX irq\n");
		वापस lp->tx_irq;
	पूर्ण

	अगर (temac_np) अणु
		/* Retrieve the MAC address */
		rc = of_get_mac_address(temac_np, addr);
		अगर (rc) अणु
			dev_err(&pdev->dev, "could not find MAC address\n");
			वापस -ENODEV;
		पूर्ण
		temac_init_mac_address(ndev, addr);
	पूर्ण अन्यथा अगर (pdata) अणु
		temac_init_mac_address(ndev, pdata->mac_addr);
	पूर्ण

	rc = temac_mdio_setup(lp, pdev);
	अगर (rc)
		dev_warn(&pdev->dev, "error registering MDIO bus\n");

	अगर (temac_np) अणु
		lp->phy_node = of_parse_phandle(temac_np, "phy-handle", 0);
		अगर (lp->phy_node)
			dev_dbg(lp->dev, "using PHY node %pOF\n", temac_np);
	पूर्ण अन्यथा अगर (pdata) अणु
		snम_लिखो(lp->phy_name, माप(lp->phy_name),
			 PHY_ID_FMT, lp->mii_bus->id, pdata->phy_addr);
		lp->phy_पूर्णांकerface = pdata->phy_पूर्णांकerface;
	पूर्ण

	/* Add the device attributes */
	rc = sysfs_create_group(&lp->dev->kobj, &temac_attr_group);
	अगर (rc) अणु
		dev_err(lp->dev, "Error creating sysfs files\n");
		जाओ err_sysfs_create;
	पूर्ण

	rc = रेजिस्टर_netdev(lp->ndev);
	अगर (rc) अणु
		dev_err(lp->dev, "register_netdev() error (%i)\n", rc);
		जाओ err_रेजिस्टर_ndev;
	पूर्ण

	वापस 0;

err_रेजिस्टर_ndev:
	sysfs_हटाओ_group(&lp->dev->kobj, &temac_attr_group);
err_sysfs_create:
	अगर (lp->phy_node)
		of_node_put(lp->phy_node);
	temac_mdio_tearकरोwn(lp);
	वापस rc;
पूर्ण

अटल पूर्णांक temac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा temac_local *lp = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	sysfs_हटाओ_group(&lp->dev->kobj, &temac_attr_group);
	अगर (lp->phy_node)
		of_node_put(lp->phy_node);
	temac_mdio_tearकरोwn(lp);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id temac_of_match[] = अणु
	अणु .compatible = "xlnx,xps-ll-temac-1.01.b", पूर्ण,
	अणु .compatible = "xlnx,xps-ll-temac-2.00.a", पूर्ण,
	अणु .compatible = "xlnx,xps-ll-temac-2.02.a", पूर्ण,
	अणु .compatible = "xlnx,xps-ll-temac-2.03.a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, temac_of_match);

अटल काष्ठा platक्रमm_driver temac_driver = अणु
	.probe = temac_probe,
	.हटाओ = temac_हटाओ,
	.driver = अणु
		.name = "xilinx_temac",
		.of_match_table = temac_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(temac_driver);

MODULE_DESCRIPTION("Xilinx LL_TEMAC Ethernet driver");
MODULE_AUTHOR("Yoshio Kashiwagi");
MODULE_LICENSE("GPL");
