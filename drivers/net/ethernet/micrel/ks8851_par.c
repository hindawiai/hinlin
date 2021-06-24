<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/net/ethernet/micrel/ks8851.c
 *
 * Copyright 2009 Simtec Electronics
 *	http://www.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mii.h>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_net.h>

#समावेश "ks8851.h"

अटल पूर्णांक msg_enable;

#घोषणा BE3             0x8000      /* Byte Enable 3 */
#घोषणा BE2             0x4000      /* Byte Enable 2 */
#घोषणा BE1             0x2000      /* Byte Enable 1 */
#घोषणा BE0             0x1000      /* Byte Enable 0 */

/**
 * काष्ठा ks8851_net_par - KS8851 Parallel driver निजी data
 * @ks8851: KS8851 driver common निजी data
 * @lock: Lock to ensure that the device is not accessed when busy.
 * @hw_addr	: start address of data रेजिस्टर.
 * @hw_addr_cmd	: start address of command रेजिस्टर.
 * @cmd_reg_cache	: command रेजिस्टर cached.
 *
 * The @lock ensures that the chip is रक्षित when certain operations are
 * in progress. When the पढ़ो or ग_लिखो packet transfer is in progress, most
 * of the chip रेजिस्टरs are not accessible until the transfer is finished
 * and the DMA has been de-निश्चितed.
 */
काष्ठा ks8851_net_par अणु
	काष्ठा ks8851_net	ks8851;
	spinlock_t		lock;
	व्योम __iomem		*hw_addr;
	व्योम __iomem		*hw_addr_cmd;
	u16			cmd_reg_cache;
पूर्ण;

#घोषणा to_ks8851_par(ks) container_of((ks), काष्ठा ks8851_net_par, ks8851)

/**
 * ks8851_lock_par - रेजिस्टर access lock
 * @ks: The chip state
 * @flags: Spinlock flags
 *
 * Claim chip रेजिस्टर access lock
 */
अटल व्योम ks8851_lock_par(काष्ठा ks8851_net *ks, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ks8851_net_par *ksp = to_ks8851_par(ks);

	spin_lock_irqsave(&ksp->lock, *flags);
पूर्ण

/**
 * ks8851_unlock_par - रेजिस्टर access unlock
 * @ks: The chip state
 * @flags: Spinlock flags
 *
 * Release chip रेजिस्टर access lock
 */
अटल व्योम ks8851_unlock_par(काष्ठा ks8851_net *ks, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ks8851_net_par *ksp = to_ks8851_par(ks);

	spin_unlock_irqrestore(&ksp->lock, *flags);
पूर्ण

/**
 * ks_check_endian - Check whether endianness of the bus is correct
 * @ks	  : The chip inक्रमmation
 *
 * The KS8851-16MLL EESK pin allows selecting the endianness of the 16bit
 * bus. To मुख्यtain optimum perक्रमmance, the bus endianness should be set
 * such that it matches the endianness of the CPU.
 */
अटल पूर्णांक ks_check_endian(काष्ठा ks8851_net *ks)
अणु
	काष्ठा ks8851_net_par *ksp = to_ks8851_par(ks);
	u16 cider;

	/*
	 * Read CIDER रेजिस्टर first, however पढ़ो it the "wrong" way around.
	 * If the endian strap on the KS8851-16MLL in incorrect and the chip
	 * is operating in dअगरferent endianness than the CPU, then the meaning
	 * of BE[3:0] byte-enable bits is also swapped such that:
	 *    BE[3,2,1,0] becomes BE[1,0,3,2]
	 *
	 * Luckily क्रम us, the byte-enable bits are the top four MSbits of
	 * the address रेजिस्टर and the CIDER रेजिस्टर is at offset 0xc0.
	 * Hence, by पढ़ोing address 0xc0c0, which is not impacted by endian
	 * swapping, we निश्चित either BE[3:2] or BE[1:0] जबतक पढ़ोing the
	 * CIDER रेजिस्टर.
	 *
	 * If the bus configuration is correct, पढ़ोing 0xc0c0 निश्चितs
	 * BE[3:2] and this पढ़ो वापसs 0x0000, because to पढ़ो रेजिस्टर
	 * with bottom two LSbits of address set to 0, BE[1:0] must be
	 * निश्चितed.
	 *
	 * If the bus configuration is NOT correct, पढ़ोing 0xc0c0 निश्चितs
	 * BE[1:0] and this पढ़ो वापसs non-zero 0x8872 value.
	 */
	ioग_लिखो16(BE3 | BE2 | KS_CIDER, ksp->hw_addr_cmd);
	cider = ioपढ़ो16(ksp->hw_addr);
	अगर (!cider)
		वापस 0;

	netdev_err(ks->netdev, "incorrect EESK endian strap setting\n");

	वापस -EINVAL;
पूर्ण

/**
 * ks8851_wrreg16_par - ग_लिखो 16bit रेजिस्टर value to chip
 * @ks: The chip state
 * @reg: The रेजिस्टर address
 * @val: The value to ग_लिखो
 *
 * Issue a ग_लिखो to put the value @val पूर्णांकo the रेजिस्टर specअगरied in @reg.
 */
अटल व्योम ks8851_wrreg16_par(काष्ठा ks8851_net *ks, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक val)
अणु
	काष्ठा ks8851_net_par *ksp = to_ks8851_par(ks);

	ksp->cmd_reg_cache = (u16)reg | ((BE1 | BE0) << (reg & 0x02));
	ioग_लिखो16(ksp->cmd_reg_cache, ksp->hw_addr_cmd);
	ioग_लिखो16(val, ksp->hw_addr);
पूर्ण

/**
 * ks8851_rdreg16_par - पढ़ो 16 bit रेजिस्टर from chip
 * @ks: The chip inक्रमmation
 * @reg: The रेजिस्टर address
 *
 * Read a 16bit रेजिस्टर from the chip, वापसing the result
 */
अटल अचिन्हित पूर्णांक ks8851_rdreg16_par(काष्ठा ks8851_net *ks, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा ks8851_net_par *ksp = to_ks8851_par(ks);

	ksp->cmd_reg_cache = (u16)reg | ((BE1 | BE0) << (reg & 0x02));
	ioग_लिखो16(ksp->cmd_reg_cache, ksp->hw_addr_cmd);
	वापस ioपढ़ो16(ksp->hw_addr);
पूर्ण

/**
 * ks8851_rdfअगरo_par - पढ़ो data from the receive fअगरo
 * @ks: The device state.
 * @buff: The buffer address
 * @len: The length of the data to पढ़ो
 *
 * Issue an RXQ FIFO पढ़ो command and पढ़ो the @len amount of data from
 * the FIFO पूर्णांकo the buffer specअगरied by @buff.
 */
अटल व्योम ks8851_rdfअगरo_par(काष्ठा ks8851_net *ks, u8 *buff, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ks8851_net_par *ksp = to_ks8851_par(ks);

	netअगर_dbg(ks, rx_status, ks->netdev,
		  "%s: %d@%p\n", __func__, len, buff);

	ioपढ़ो16_rep(ksp->hw_addr, (u16 *)buff + 1, len / 2);
पूर्ण

/**
 * ks8851_wrfअगरo_par - ग_लिखो packet to TX FIFO
 * @ks: The device state.
 * @txp: The sk_buff to transmit.
 * @irq: IRQ on completion of the packet.
 *
 * Send the @txp to the chip. This means creating the relevant packet header
 * specअगरying the length of the packet and the other inक्रमmation the chip
 * needs, such as IRQ on completion. Send the header and the packet data to
 * the device.
 */
अटल व्योम ks8851_wrfअगरo_par(काष्ठा ks8851_net *ks, काष्ठा sk_buff *txp,
			      bool irq)
अणु
	काष्ठा ks8851_net_par *ksp = to_ks8851_par(ks);
	अचिन्हित पूर्णांक len = ALIGN(txp->len, 4);
	अचिन्हित पूर्णांक fid = 0;

	netअगर_dbg(ks, tx_queued, ks->netdev, "%s: skb %p, %d@%p, irq %d\n",
		  __func__, txp, txp->len, txp->data, irq);

	fid = ks->fid++;
	fid &= TXFR_TXFID_MASK;

	अगर (irq)
		fid |= TXFR_TXIC;	/* irq on completion */

	ioग_लिखो16(fid, ksp->hw_addr);
	ioग_लिखो16(txp->len, ksp->hw_addr);

	ioग_लिखो16_rep(ksp->hw_addr, txp->data, len / 2);
पूर्ण

/**
 * ks8851_rx_skb_par - receive skbuff
 * @ks: The device state.
 * @skb: The skbuff
 */
अटल व्योम ks8851_rx_skb_par(काष्ठा ks8851_net *ks, काष्ठा sk_buff *skb)
अणु
	netअगर_rx(skb);
पूर्ण

अटल अचिन्हित पूर्णांक ks8851_rdreg16_par_txqcr(काष्ठा ks8851_net *ks)
अणु
	वापस ks8851_rdreg16_par(ks, KS_TXQCR);
पूर्ण

/**
 * ks8851_start_xmit_par - transmit packet
 * @skb: The buffer to transmit
 * @dev: The device used to transmit the packet.
 *
 * Called by the network layer to transmit the @skb. Queue the packet क्रम
 * the device and schedule the necessary work to transmit the packet when
 * it is मुक्त.
 *
 * We करो this to firstly aव्योम sleeping with the network device locked,
 * and secondly so we can round up more than one packet to transmit which
 * means we can try and aव्योम generating too many transmit करोne पूर्णांकerrupts.
 */
अटल netdev_tx_t ks8851_start_xmit_par(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	netdev_tx_t ret = NETDEV_TX_OK;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक txqcr;
	u16 txmir;
	पूर्णांक err;

	netअगर_dbg(ks, tx_queued, ks->netdev,
		  "%s: skb %p, %d@%p\n", __func__, skb, skb->len, skb->data);

	ks8851_lock_par(ks, &flags);

	txmir = ks8851_rdreg16_par(ks, KS_TXMIR) & 0x1fff;

	अगर (likely(txmir >= skb->len + 12)) अणु
		ks8851_wrreg16_par(ks, KS_RXQCR, ks->rc_rxqcr | RXQCR_SDA);
		ks8851_wrfअगरo_par(ks, skb, false);
		ks8851_wrreg16_par(ks, KS_RXQCR, ks->rc_rxqcr);
		ks8851_wrreg16_par(ks, KS_TXQCR, TXQCR_METFE);

		err = पढ़ोx_poll_समयout_atomic(ks8851_rdreg16_par_txqcr, ks,
						txqcr, !(txqcr & TXQCR_METFE),
						5, 1000000);
		अगर (err)
			ret = NETDEV_TX_BUSY;

		ks8851_करोne_tx(ks, skb);
	पूर्ण अन्यथा अणु
		ret = NETDEV_TX_BUSY;
	पूर्ण

	ks8851_unlock_par(ks, &flags);

	वापस ret;
पूर्ण

अटल पूर्णांक ks8851_probe_par(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ks8851_net_par *ksp;
	काष्ठा net_device *netdev;
	काष्ठा ks8851_net *ks;
	पूर्णांक ret;

	netdev = devm_alloc_etherdev(dev, माप(काष्ठा ks8851_net_par));
	अगर (!netdev)
		वापस -ENOMEM;

	ks = netdev_priv(netdev);

	ks->lock = ks8851_lock_par;
	ks->unlock = ks8851_unlock_par;
	ks->rdreg16 = ks8851_rdreg16_par;
	ks->wrreg16 = ks8851_wrreg16_par;
	ks->rdfअगरo = ks8851_rdfअगरo_par;
	ks->wrfअगरo = ks8851_wrfअगरo_par;
	ks->start_xmit = ks8851_start_xmit_par;
	ks->rx_skb = ks8851_rx_skb_par;

#घोषणा STD_IRQ (IRQ_LCI |	/* Link Change */	\
		 IRQ_RXI |	/* RX करोne */		\
		 IRQ_RXPSI)	/* RX process stop */
	ks->rc_ier = STD_IRQ;

	ksp = to_ks8851_par(ks);
	spin_lock_init(&ksp->lock);

	ksp->hw_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ksp->hw_addr))
		वापस PTR_ERR(ksp->hw_addr);

	ksp->hw_addr_cmd = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(ksp->hw_addr_cmd))
		वापस PTR_ERR(ksp->hw_addr_cmd);

	ret = ks_check_endian(ks);
	अगर (ret)
		वापस ret;

	netdev->irq = platक्रमm_get_irq(pdev, 0);

	वापस ks8851_probe_common(netdev, dev, msg_enable);
पूर्ण

अटल पूर्णांक ks8851_हटाओ_par(काष्ठा platक्रमm_device *pdev)
अणु
	वापस ks8851_हटाओ_common(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ks8851_match_table[] = अणु
	अणु .compatible = "micrel,ks8851-mll" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ks8851_match_table);

अटल काष्ठा platक्रमm_driver ks8851_driver = अणु
	.driver = अणु
		.name = "ks8851",
		.of_match_table = ks8851_match_table,
		.pm = &ks8851_pm_ops,
	पूर्ण,
	.probe = ks8851_probe_par,
	.हटाओ = ks8851_हटाओ_par,
पूर्ण;
module_platक्रमm_driver(ks8851_driver);

MODULE_DESCRIPTION("KS8851 Network driver");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_LICENSE("GPL");

module_param_named(message, msg_enable, पूर्णांक, 0);
MODULE_PARM_DESC(message, "Message verbosity level (0=none, 31=all)");
