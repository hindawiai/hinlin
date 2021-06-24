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
#समावेश <linux/cache.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_net.h>

#समावेश "ks8851.h"

अटल पूर्णांक msg_enable;

/**
 * काष्ठा ks8851_net_spi - KS8851 SPI driver निजी data
 * @lock: Lock to ensure that the device is not accessed when busy.
 * @tx_work: Work queue क्रम tx packets
 * @ks8851: KS8851 driver common निजी data
 * @spidev: The spi device we're bound to.
 * @spi_msg1: pre-setup SPI transfer with one message, @spi_xfer1.
 * @spi_msg2: pre-setup SPI transfer with two messages, @spi_xfer2.
 * @spi_xfer1: @spi_msg1 SPI transfer काष्ठाure
 * @spi_xfer2: @spi_msg2 SPI transfer काष्ठाure
 *
 * The @lock ensures that the chip is रक्षित when certain operations are
 * in progress. When the पढ़ो or ग_लिखो packet transfer is in progress, most
 * of the chip रेजिस्टरs are not ccessible until the transfer is finished and
 * the DMA has been de-निश्चितed.
 */
काष्ठा ks8851_net_spi अणु
	काष्ठा ks8851_net	ks8851;
	काष्ठा mutex		lock;
	काष्ठा work_काष्ठा	tx_work;
	काष्ठा spi_device	*spidev;
	काष्ठा spi_message	spi_msg1;
	काष्ठा spi_message	spi_msg2;
	काष्ठा spi_transfer	spi_xfer1;
	काष्ठा spi_transfer	spi_xfer2[2];
पूर्ण;

#घोषणा to_ks8851_spi(ks) container_of((ks), काष्ठा ks8851_net_spi, ks8851)

/* SPI frame opcodes */
#घोषणा KS_SPIOP_RD	0x00
#घोषणा KS_SPIOP_WR	0x40
#घोषणा KS_SPIOP_RXFIFO	0x80
#घोषणा KS_SPIOP_TXFIFO	0xC0

/* shअगरt क्रम byte-enable data */
#घोषणा BYTE_EN(_x)	((_x) << 2)

/* turn रेजिस्टर number and byte-enable mask पूर्णांकo data क्रम start of packet */
#घोषणा MK_OP(_byteen, _reg)	\
	(BYTE_EN(_byteen) | (_reg) << (8 + 2) | (_reg) >> 6)

/**
 * ks8851_lock_spi - रेजिस्टर access lock
 * @ks: The chip state
 * @flags: Spinlock flags
 *
 * Claim chip रेजिस्टर access lock
 */
अटल व्योम ks8851_lock_spi(काष्ठा ks8851_net *ks, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ks8851_net_spi *kss = to_ks8851_spi(ks);

	mutex_lock(&kss->lock);
पूर्ण

/**
 * ks8851_unlock_spi - रेजिस्टर access unlock
 * @ks: The chip state
 * @flags: Spinlock flags
 *
 * Release chip रेजिस्टर access lock
 */
अटल व्योम ks8851_unlock_spi(काष्ठा ks8851_net *ks, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ks8851_net_spi *kss = to_ks8851_spi(ks);

	mutex_unlock(&kss->lock);
पूर्ण

/* SPI रेजिस्टर पढ़ो/ग_लिखो calls.
 *
 * All these calls issue SPI transactions to access the chip's रेजिस्टरs. They
 * all require that the necessary lock is held to prevent accesses when the
 * chip is busy transferring packet data (RX/TX FIFO accesses).
 */

/**
 * ks8851_wrreg16_spi - ग_लिखो 16bit रेजिस्टर value to chip via SPI
 * @ks: The chip state
 * @reg: The रेजिस्टर address
 * @val: The value to ग_लिखो
 *
 * Issue a ग_लिखो to put the value @val पूर्णांकo the रेजिस्टर specअगरied in @reg.
 */
अटल व्योम ks8851_wrreg16_spi(काष्ठा ks8851_net *ks, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक val)
अणु
	काष्ठा ks8851_net_spi *kss = to_ks8851_spi(ks);
	काष्ठा spi_transfer *xfer = &kss->spi_xfer1;
	काष्ठा spi_message *msg = &kss->spi_msg1;
	__le16 txb[2];
	पूर्णांक ret;

	txb[0] = cpu_to_le16(MK_OP(reg & 2 ? 0xC : 0x03, reg) | KS_SPIOP_WR);
	txb[1] = cpu_to_le16(val);

	xfer->tx_buf = txb;
	xfer->rx_buf = शून्य;
	xfer->len = 4;

	ret = spi_sync(kss->spidev, msg);
	अगर (ret < 0)
		netdev_err(ks->netdev, "spi_sync() failed\n");
पूर्ण

/**
 * ks8851_rdreg - issue पढ़ो रेजिस्टर command and वापस the data
 * @ks: The device state
 * @op: The रेजिस्टर address and byte enables in message क्रमmat.
 * @rxb: The RX buffer to वापस the result पूर्णांकo
 * @rxl: The length of data expected.
 *
 * This is the low level पढ़ो call that issues the necessary spi message(s)
 * to पढ़ो data from the रेजिस्टर specअगरied in @op.
 */
अटल व्योम ks8851_rdreg(काष्ठा ks8851_net *ks, अचिन्हित पूर्णांक op,
			 u8 *rxb, अचिन्हित पूर्णांक rxl)
अणु
	काष्ठा ks8851_net_spi *kss = to_ks8851_spi(ks);
	काष्ठा spi_transfer *xfer;
	काष्ठा spi_message *msg;
	__le16 *txb = (__le16 *)ks->txd;
	u8 *trx = ks->rxd;
	पूर्णांक ret;

	txb[0] = cpu_to_le16(op | KS_SPIOP_RD);

	अगर (kss->spidev->master->flags & SPI_MASTER_HALF_DUPLEX) अणु
		msg = &kss->spi_msg2;
		xfer = kss->spi_xfer2;

		xfer->tx_buf = txb;
		xfer->rx_buf = शून्य;
		xfer->len = 2;

		xfer++;
		xfer->tx_buf = शून्य;
		xfer->rx_buf = trx;
		xfer->len = rxl;
	पूर्ण अन्यथा अणु
		msg = &kss->spi_msg1;
		xfer = &kss->spi_xfer1;

		xfer->tx_buf = txb;
		xfer->rx_buf = trx;
		xfer->len = rxl + 2;
	पूर्ण

	ret = spi_sync(kss->spidev, msg);
	अगर (ret < 0)
		netdev_err(ks->netdev, "read: spi_sync() failed\n");
	अन्यथा अगर (kss->spidev->master->flags & SPI_MASTER_HALF_DUPLEX)
		स_नकल(rxb, trx, rxl);
	अन्यथा
		स_नकल(rxb, trx + 2, rxl);
पूर्ण

/**
 * ks8851_rdreg16_spi - पढ़ो 16 bit रेजिस्टर from device via SPI
 * @ks: The chip inक्रमmation
 * @reg: The रेजिस्टर address
 *
 * Read a 16bit रेजिस्टर from the chip, वापसing the result
 */
अटल अचिन्हित पूर्णांक ks8851_rdreg16_spi(काष्ठा ks8851_net *ks, अचिन्हित पूर्णांक reg)
अणु
	__le16 rx = 0;

	ks8851_rdreg(ks, MK_OP(reg & 2 ? 0xC : 0x3, reg), (u8 *)&rx, 2);
	वापस le16_to_cpu(rx);
पूर्ण

/**
 * ks8851_rdfअगरo_spi - पढ़ो data from the receive fअगरo via SPI
 * @ks: The device state.
 * @buff: The buffer address
 * @len: The length of the data to पढ़ो
 *
 * Issue an RXQ FIFO पढ़ो command and पढ़ो the @len amount of data from
 * the FIFO पूर्णांकo the buffer specअगरied by @buff.
 */
अटल व्योम ks8851_rdfअगरo_spi(काष्ठा ks8851_net *ks, u8 *buff, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ks8851_net_spi *kss = to_ks8851_spi(ks);
	काष्ठा spi_transfer *xfer = kss->spi_xfer2;
	काष्ठा spi_message *msg = &kss->spi_msg2;
	u8 txb[1];
	पूर्णांक ret;

	netअगर_dbg(ks, rx_status, ks->netdev,
		  "%s: %d@%p\n", __func__, len, buff);

	/* set the operation we're issuing */
	txb[0] = KS_SPIOP_RXFIFO;

	xfer->tx_buf = txb;
	xfer->rx_buf = शून्य;
	xfer->len = 1;

	xfer++;
	xfer->rx_buf = buff;
	xfer->tx_buf = शून्य;
	xfer->len = len;

	ret = spi_sync(kss->spidev, msg);
	अगर (ret < 0)
		netdev_err(ks->netdev, "%s: spi_sync() failed\n", __func__);
पूर्ण

/**
 * ks8851_wrfअगरo_spi - ग_लिखो packet to TX FIFO via SPI
 * @ks: The device state.
 * @txp: The sk_buff to transmit.
 * @irq: IRQ on completion of the packet.
 *
 * Send the @txp to the chip. This means creating the relevant packet header
 * specअगरying the length of the packet and the other inक्रमmation the chip
 * needs, such as IRQ on completion. Send the header and the packet data to
 * the device.
 */
अटल व्योम ks8851_wrfअगरo_spi(काष्ठा ks8851_net *ks, काष्ठा sk_buff *txp,
			      bool irq)
अणु
	काष्ठा ks8851_net_spi *kss = to_ks8851_spi(ks);
	काष्ठा spi_transfer *xfer = kss->spi_xfer2;
	काष्ठा spi_message *msg = &kss->spi_msg2;
	अचिन्हित पूर्णांक fid = 0;
	पूर्णांक ret;

	netअगर_dbg(ks, tx_queued, ks->netdev, "%s: skb %p, %d@%p, irq %d\n",
		  __func__, txp, txp->len, txp->data, irq);

	fid = ks->fid++;
	fid &= TXFR_TXFID_MASK;

	अगर (irq)
		fid |= TXFR_TXIC;	/* irq on completion */

	/* start header at txb[1] to align txw entries */
	ks->txh.txb[1] = KS_SPIOP_TXFIFO;
	ks->txh.txw[1] = cpu_to_le16(fid);
	ks->txh.txw[2] = cpu_to_le16(txp->len);

	xfer->tx_buf = &ks->txh.txb[1];
	xfer->rx_buf = शून्य;
	xfer->len = 5;

	xfer++;
	xfer->tx_buf = txp->data;
	xfer->rx_buf = शून्य;
	xfer->len = ALIGN(txp->len, 4);

	ret = spi_sync(kss->spidev, msg);
	अगर (ret < 0)
		netdev_err(ks->netdev, "%s: spi_sync() failed\n", __func__);
पूर्ण

/**
 * ks8851_rx_skb_spi - receive skbuff
 * @ks: The device state
 * @skb: The skbuff
 */
अटल व्योम ks8851_rx_skb_spi(काष्ठा ks8851_net *ks, काष्ठा sk_buff *skb)
अणु
	netअगर_rx_ni(skb);
पूर्ण

/**
 * ks8851_tx_work - process tx packet(s)
 * @work: The work strucutre what was scheduled.
 *
 * This is called when a number of packets have been scheduled क्रम
 * transmission and need to be sent to the device.
 */
अटल व्योम ks8851_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ks8851_net_spi *kss;
	काष्ठा ks8851_net *ks;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *txb;
	bool last;

	kss = container_of(work, काष्ठा ks8851_net_spi, tx_work);
	ks = &kss->ks8851;
	last = skb_queue_empty(&ks->txq);

	ks8851_lock_spi(ks, &flags);

	जबतक (!last) अणु
		txb = skb_dequeue(&ks->txq);
		last = skb_queue_empty(&ks->txq);

		अगर (txb) अणु
			ks8851_wrreg16_spi(ks, KS_RXQCR,
					   ks->rc_rxqcr | RXQCR_SDA);
			ks8851_wrfअगरo_spi(ks, txb, last);
			ks8851_wrreg16_spi(ks, KS_RXQCR, ks->rc_rxqcr);
			ks8851_wrreg16_spi(ks, KS_TXQCR, TXQCR_METFE);

			ks8851_करोne_tx(ks, txb);
		पूर्ण
	पूर्ण

	ks8851_unlock_spi(ks, &flags);
पूर्ण

/**
 * ks8851_flush_tx_work_spi - flush outstanding TX work
 * @ks: The device state
 */
अटल व्योम ks8851_flush_tx_work_spi(काष्ठा ks8851_net *ks)
अणु
	काष्ठा ks8851_net_spi *kss = to_ks8851_spi(ks);

	flush_work(&kss->tx_work);
पूर्ण

/**
 * calc_txlen - calculate size of message to send packet
 * @len: Length of data
 *
 * Returns the size of the TXFIFO message needed to send
 * this packet.
 */
अटल अचिन्हित पूर्णांक calc_txlen(अचिन्हित पूर्णांक len)
अणु
	वापस ALIGN(len + 4, 4);
पूर्ण

/**
 * ks8851_start_xmit_spi - transmit packet using SPI
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
अटल netdev_tx_t ks8851_start_xmit_spi(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक needed = calc_txlen(skb->len);
	काष्ठा ks8851_net *ks = netdev_priv(dev);
	netdev_tx_t ret = NETDEV_TX_OK;
	काष्ठा ks8851_net_spi *kss;

	kss = to_ks8851_spi(ks);

	netअगर_dbg(ks, tx_queued, ks->netdev,
		  "%s: skb %p, %d@%p\n", __func__, skb, skb->len, skb->data);

	spin_lock(&ks->statelock);

	अगर (needed > ks->tx_space) अणु
		netअगर_stop_queue(dev);
		ret = NETDEV_TX_BUSY;
	पूर्ण अन्यथा अणु
		ks->tx_space -= needed;
		skb_queue_tail(&ks->txq, skb);
	पूर्ण

	spin_unlock(&ks->statelock);
	schedule_work(&kss->tx_work);

	वापस ret;
पूर्ण

अटल पूर्णांक ks8851_probe_spi(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा ks8851_net_spi *kss;
	काष्ठा net_device *netdev;
	काष्ठा ks8851_net *ks;

	netdev = devm_alloc_etherdev(dev, माप(काष्ठा ks8851_net_spi));
	अगर (!netdev)
		वापस -ENOMEM;

	spi->bits_per_word = 8;

	ks = netdev_priv(netdev);

	ks->lock = ks8851_lock_spi;
	ks->unlock = ks8851_unlock_spi;
	ks->rdreg16 = ks8851_rdreg16_spi;
	ks->wrreg16 = ks8851_wrreg16_spi;
	ks->rdfअगरo = ks8851_rdfअगरo_spi;
	ks->wrfअगरo = ks8851_wrfअगरo_spi;
	ks->start_xmit = ks8851_start_xmit_spi;
	ks->rx_skb = ks8851_rx_skb_spi;
	ks->flush_tx_work = ks8851_flush_tx_work_spi;

#घोषणा STD_IRQ (IRQ_LCI |	/* Link Change */	\
		 IRQ_TXI |	/* TX करोne */		\
		 IRQ_RXI |	/* RX करोne */		\
		 IRQ_SPIBEI |	/* SPI bus error */	\
		 IRQ_TXPSI |	/* TX process stop */	\
		 IRQ_RXPSI)	/* RX process stop */
	ks->rc_ier = STD_IRQ;

	kss = to_ks8851_spi(ks);

	kss->spidev = spi;
	mutex_init(&kss->lock);
	INIT_WORK(&kss->tx_work, ks8851_tx_work);

	/* initialise pre-made spi transfer messages */
	spi_message_init(&kss->spi_msg1);
	spi_message_add_tail(&kss->spi_xfer1, &kss->spi_msg1);

	spi_message_init(&kss->spi_msg2);
	spi_message_add_tail(&kss->spi_xfer2[0], &kss->spi_msg2);
	spi_message_add_tail(&kss->spi_xfer2[1], &kss->spi_msg2);

	netdev->irq = spi->irq;

	वापस ks8851_probe_common(netdev, dev, msg_enable);
पूर्ण

अटल पूर्णांक ks8851_हटाओ_spi(काष्ठा spi_device *spi)
अणु
	वापस ks8851_हटाओ_common(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ks8851_match_table[] = अणु
	अणु .compatible = "micrel,ks8851" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ks8851_match_table);

अटल काष्ठा spi_driver ks8851_driver = अणु
	.driver = अणु
		.name = "ks8851",
		.of_match_table = ks8851_match_table,
		.pm = &ks8851_pm_ops,
	पूर्ण,
	.probe = ks8851_probe_spi,
	.हटाओ = ks8851_हटाओ_spi,
पूर्ण;
module_spi_driver(ks8851_driver);

MODULE_DESCRIPTION("KS8851 Network driver");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_LICENSE("GPL");

module_param_named(message, msg_enable, पूर्णांक, 0);
MODULE_PARM_DESC(message, "Message verbosity level (0=none, 31=all)");
MODULE_ALIAS("spi:ks8851");
