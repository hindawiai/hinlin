<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sunqe.c: Sparc QuadEthernet 10baseT SBUS card driver.
 *          Once again I am out to prove that every ethernet
 *          controller out there can be most efficiently programmed
 *          अगर you make it look like a LANCE.
 *
 * Copyright (C) 1996, 1999, 2003, 2006, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/irq.h>

#समावेश "sunqe.h"

#घोषणा DRV_NAME	"sunqe"
#घोषणा DRV_VERSION	"4.1"
#घोषणा DRV_RELDATE	"August 27, 2008"
#घोषणा DRV_AUTHOR	"David S. Miller (davem@davemloft.net)"

अटल अक्षर version[] =
	DRV_NAME ".c:v" DRV_VERSION " " DRV_RELDATE " " DRV_AUTHOR "\n";

MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION("Sun QuadEthernet 10baseT SBUS card driver");
MODULE_LICENSE("GPL");

अटल काष्ठा sunqec *root_qec_dev;

अटल व्योम qe_set_multicast(काष्ठा net_device *dev);

#घोषणा QEC_RESET_TRIES 200

अटल अंतरभूत पूर्णांक qec_global_reset(व्योम __iomem *gregs)
अणु
	पूर्णांक tries = QEC_RESET_TRIES;

	sbus_ग_लिखोl(GLOB_CTRL_RESET, gregs + GLOB_CTRL);
	जबतक (--tries) अणु
		u32 पंचांगp = sbus_पढ़ोl(gregs + GLOB_CTRL);
		अगर (पंचांगp & GLOB_CTRL_RESET) अणु
			udelay(20);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (tries)
		वापस 0;
	prपूर्णांकk(KERN_ERR "QuadEther: AIEEE cannot reset the QEC!\n");
	वापस -1;
पूर्ण

#घोषणा MACE_RESET_RETRIES 200
#घोषणा QE_RESET_RETRIES   200

अटल अंतरभूत पूर्णांक qe_stop(काष्ठा sunqe *qep)
अणु
	व्योम __iomem *cregs = qep->qcregs;
	व्योम __iomem *mregs = qep->mregs;
	पूर्णांक tries;

	/* Reset the MACE, then the QEC channel. */
	sbus_ग_लिखोb(MREGS_BCONFIG_RESET, mregs + MREGS_BCONFIG);
	tries = MACE_RESET_RETRIES;
	जबतक (--tries) अणु
		u8 पंचांगp = sbus_पढ़ोb(mregs + MREGS_BCONFIG);
		अगर (पंचांगp & MREGS_BCONFIG_RESET) अणु
			udelay(20);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (!tries) अणु
		prपूर्णांकk(KERN_ERR "QuadEther: AIEEE cannot reset the MACE!\n");
		वापस -1;
	पूर्ण

	sbus_ग_लिखोl(CREG_CTRL_RESET, cregs + CREG_CTRL);
	tries = QE_RESET_RETRIES;
	जबतक (--tries) अणु
		u32 पंचांगp = sbus_पढ़ोl(cregs + CREG_CTRL);
		अगर (पंचांगp & CREG_CTRL_RESET) अणु
			udelay(20);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (!tries) अणु
		prपूर्णांकk(KERN_ERR "QuadEther: Cannot reset QE channel!\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qe_init_rings(काष्ठा sunqe *qep)
अणु
	काष्ठा qe_init_block *qb = qep->qe_block;
	काष्ठा sunqe_buffers *qbufs = qep->buffers;
	__u32 qbufs_dvma = (__u32)qep->buffers_dvma;
	पूर्णांक i;

	qep->rx_new = qep->rx_old = qep->tx_new = qep->tx_old = 0;
	स_रखो(qb, 0, माप(काष्ठा qe_init_block));
	स_रखो(qbufs, 0, माप(काष्ठा sunqe_buffers));
	क्रम (i = 0; i < RX_RING_SIZE; i++) अणु
		qb->qe_rxd[i].rx_addr = qbufs_dvma + qebuf_offset(rx_buf, i);
		qb->qe_rxd[i].rx_flags =
			(RXD_OWN | ((RXD_PKT_SZ) & RXD_LENGTH));
	पूर्ण
पूर्ण

अटल पूर्णांक qe_init(काष्ठा sunqe *qep, पूर्णांक from_irq)
अणु
	काष्ठा sunqec *qecp = qep->parent;
	व्योम __iomem *cregs = qep->qcregs;
	व्योम __iomem *mregs = qep->mregs;
	व्योम __iomem *gregs = qecp->gregs;
	अचिन्हित अक्षर *e = &qep->dev->dev_addr[0];
	__u32 qblk_dvma = (__u32)qep->qblock_dvma;
	u32 पंचांगp;
	पूर्णांक i;

	/* Shut it up. */
	अगर (qe_stop(qep))
		वापस -EAGAIN;

	/* Setup initial rx/tx init block poपूर्णांकers. */
	sbus_ग_लिखोl(qblk_dvma + qib_offset(qe_rxd, 0), cregs + CREG_RXDS);
	sbus_ग_लिखोl(qblk_dvma + qib_offset(qe_txd, 0), cregs + CREG_TXDS);

	/* Enable/mask the various irq's. */
	sbus_ग_लिखोl(0, cregs + CREG_RIMASK);
	sbus_ग_लिखोl(1, cregs + CREG_TIMASK);

	sbus_ग_लिखोl(0, cregs + CREG_QMASK);
	sbus_ग_लिखोl(CREG_MMASK_RXCOLL, cregs + CREG_MMASK);

	/* Setup the FIFO poपूर्णांकers पूर्णांकo QEC local memory. */
	पंचांगp = qep->channel * sbus_पढ़ोl(gregs + GLOB_MSIZE);
	sbus_ग_लिखोl(पंचांगp, cregs + CREG_RXRBUFPTR);
	sbus_ग_लिखोl(पंचांगp, cregs + CREG_RXWBUFPTR);

	पंचांगp = sbus_पढ़ोl(cregs + CREG_RXRBUFPTR) +
		sbus_पढ़ोl(gregs + GLOB_RSIZE);
	sbus_ग_लिखोl(पंचांगp, cregs + CREG_TXRBUFPTR);
	sbus_ग_लिखोl(पंचांगp, cregs + CREG_TXWBUFPTR);

	/* Clear the channel collision counter. */
	sbus_ग_लिखोl(0, cregs + CREG_CCNT);

	/* For 10baseT, पूर्णांकer frame space nor throttle seems to be necessary. */
	sbus_ग_लिखोl(0, cregs + CREG_PIPG);

	/* Now करोrk with the AMD MACE. */
	sbus_ग_लिखोb(MREGS_PHYCONFIG_AUTO, mregs + MREGS_PHYCONFIG);
	sbus_ग_लिखोb(MREGS_TXFCNTL_AUTOPAD, mregs + MREGS_TXFCNTL);
	sbus_ग_लिखोb(0, mregs + MREGS_RXFCNTL);

	/* The QEC dma's the rx'd packets from local memory out to मुख्य memory,
	 * and thereक्रमe it पूर्णांकerrupts when the packet reception is "complete".
	 * So करोn't listen क्रम the MACE talking about it.
	 */
	sbus_ग_लिखोb(MREGS_IMASK_COLL | MREGS_IMASK_RXIRQ, mregs + MREGS_IMASK);
	sbus_ग_लिखोb(MREGS_BCONFIG_BSWAP | MREGS_BCONFIG_64TS, mregs + MREGS_BCONFIG);
	sbus_ग_लिखोb((MREGS_FCONFIG_TXF16 | MREGS_FCONFIG_RXF32 |
		     MREGS_FCONFIG_RFWU | MREGS_FCONFIG_TFWU),
		    mregs + MREGS_FCONFIG);

	/* Only usable पूर्णांकerface on QuadEther is twisted pair. */
	sbus_ग_लिखोb(MREGS_PLSCONFIG_TP, mregs + MREGS_PLSCONFIG);

	/* Tell MACE we are changing the ether address. */
	sbus_ग_लिखोb(MREGS_IACONFIG_ACHNGE | MREGS_IACONFIG_PARESET,
		    mregs + MREGS_IACONFIG);
	जबतक ((sbus_पढ़ोb(mregs + MREGS_IACONFIG) & MREGS_IACONFIG_ACHNGE) != 0)
		barrier();
	sbus_ग_लिखोb(e[0], mregs + MREGS_ETHADDR);
	sbus_ग_लिखोb(e[1], mregs + MREGS_ETHADDR);
	sbus_ग_लिखोb(e[2], mregs + MREGS_ETHADDR);
	sbus_ग_लिखोb(e[3], mregs + MREGS_ETHADDR);
	sbus_ग_लिखोb(e[4], mregs + MREGS_ETHADDR);
	sbus_ग_लिखोb(e[5], mregs + MREGS_ETHADDR);

	/* Clear out the address filter. */
	sbus_ग_लिखोb(MREGS_IACONFIG_ACHNGE | MREGS_IACONFIG_LARESET,
		    mregs + MREGS_IACONFIG);
	जबतक ((sbus_पढ़ोb(mregs + MREGS_IACONFIG) & MREGS_IACONFIG_ACHNGE) != 0)
		barrier();
	क्रम (i = 0; i < 8; i++)
		sbus_ग_लिखोb(0, mregs + MREGS_FILTER);

	/* Address changes are now complete. */
	sbus_ग_लिखोb(0, mregs + MREGS_IACONFIG);

	qe_init_rings(qep);

	/* Wait a little bit क्रम the link to come up... */
	mdelay(5);
	अगर (!(sbus_पढ़ोb(mregs + MREGS_PHYCONFIG) & MREGS_PHYCONFIG_LTESTDIS)) अणु
		पूर्णांक tries = 50;

		जबतक (--tries) अणु
			u8 पंचांगp;

			mdelay(5);
			barrier();
			पंचांगp = sbus_पढ़ोb(mregs + MREGS_PHYCONFIG);
			अगर ((पंचांगp & MREGS_PHYCONFIG_LSTAT) != 0)
				अवरोध;
		पूर्ण
		अगर (tries == 0)
			prपूर्णांकk(KERN_NOTICE "%s: Warning, link state is down.\n", qep->dev->name);
	पूर्ण

	/* Missed packet counter is cleared on a पढ़ो. */
	sbus_पढ़ोb(mregs + MREGS_MPCNT);

	/* Reload multicast inक्रमmation, this will enable the receiver
	 * and transmitter.
	 */
	qe_set_multicast(qep->dev);

	/* QEC should now start to show पूर्णांकerrupts. */
	वापस 0;
पूर्ण

/* Grrr, certain error conditions completely lock up the AMD MACE,
 * so when we get these we _must_ reset the chip.
 */
अटल पूर्णांक qe_is_bolixed(काष्ठा sunqe *qep, u32 qe_status)
अणु
	काष्ठा net_device *dev = qep->dev;
	पूर्णांक mace_hwbug_workaround = 0;

	अगर (qe_status & CREG_STAT_EDEFER) अणु
		prपूर्णांकk(KERN_ERR "%s: Excessive transmit defers.\n", dev->name);
		dev->stats.tx_errors++;
	पूर्ण

	अगर (qe_status & CREG_STAT_CLOSS) अणु
		prपूर्णांकk(KERN_ERR "%s: Carrier lost, link down?\n", dev->name);
		dev->stats.tx_errors++;
		dev->stats.tx_carrier_errors++;
	पूर्ण

	अगर (qe_status & CREG_STAT_ERETRIES) अणु
		prपूर्णांकk(KERN_ERR "%s: Excessive transmit retries (more than 16).\n", dev->name);
		dev->stats.tx_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_LCOLL) अणु
		prपूर्णांकk(KERN_ERR "%s: Late transmit collision.\n", dev->name);
		dev->stats.tx_errors++;
		dev->stats.collisions++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_FUFLOW) अणु
		prपूर्णांकk(KERN_ERR "%s: Transmit fifo underflow, driver bug.\n", dev->name);
		dev->stats.tx_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_JERROR) अणु
		prपूर्णांकk(KERN_ERR "%s: Jabber error.\n", dev->name);
	पूर्ण

	अगर (qe_status & CREG_STAT_BERROR) अणु
		prपूर्णांकk(KERN_ERR "%s: Babble error.\n", dev->name);
	पूर्ण

	अगर (qe_status & CREG_STAT_CCOFLOW) अणु
		dev->stats.tx_errors += 256;
		dev->stats.collisions += 256;
	पूर्ण

	अगर (qe_status & CREG_STAT_TXDERROR) अणु
		prपूर्णांकk(KERN_ERR "%s: Transmit descriptor is bogus, driver bug.\n", dev->name);
		dev->stats.tx_errors++;
		dev->stats.tx_पातed_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_TXLERR) अणु
		prपूर्णांकk(KERN_ERR "%s: Transmit late error.\n", dev->name);
		dev->stats.tx_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_TXPERR) अणु
		prपूर्णांकk(KERN_ERR "%s: Transmit DMA parity error.\n", dev->name);
		dev->stats.tx_errors++;
		dev->stats.tx_पातed_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_TXSERR) अणु
		prपूर्णांकk(KERN_ERR "%s: Transmit DMA sbus error ack.\n", dev->name);
		dev->stats.tx_errors++;
		dev->stats.tx_पातed_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_RCCOFLOW) अणु
		dev->stats.rx_errors += 256;
		dev->stats.collisions += 256;
	पूर्ण

	अगर (qe_status & CREG_STAT_RUOFLOW) अणु
		dev->stats.rx_errors += 256;
		dev->stats.rx_over_errors += 256;
	पूर्ण

	अगर (qe_status & CREG_STAT_MCOFLOW) अणु
		dev->stats.rx_errors += 256;
		dev->stats.rx_missed_errors += 256;
	पूर्ण

	अगर (qe_status & CREG_STAT_RXFOFLOW) अणु
		prपूर्णांकk(KERN_ERR "%s: Receive fifo overflow.\n", dev->name);
		dev->stats.rx_errors++;
		dev->stats.rx_over_errors++;
	पूर्ण

	अगर (qe_status & CREG_STAT_RLCOLL) अणु
		prपूर्णांकk(KERN_ERR "%s: Late receive collision.\n", dev->name);
		dev->stats.rx_errors++;
		dev->stats.collisions++;
	पूर्ण

	अगर (qe_status & CREG_STAT_FCOFLOW) अणु
		dev->stats.rx_errors += 256;
		dev->stats.rx_frame_errors += 256;
	पूर्ण

	अगर (qe_status & CREG_STAT_CECOFLOW) अणु
		dev->stats.rx_errors += 256;
		dev->stats.rx_crc_errors += 256;
	पूर्ण

	अगर (qe_status & CREG_STAT_RXDROP) अणु
		prपूर्णांकk(KERN_ERR "%s: Receive packet dropped.\n", dev->name);
		dev->stats.rx_errors++;
		dev->stats.rx_dropped++;
		dev->stats.rx_missed_errors++;
	पूर्ण

	अगर (qe_status & CREG_STAT_RXSMALL) अणु
		prपूर्णांकk(KERN_ERR "%s: Receive buffer too small, driver bug.\n", dev->name);
		dev->stats.rx_errors++;
		dev->stats.rx_length_errors++;
	पूर्ण

	अगर (qe_status & CREG_STAT_RXLERR) अणु
		prपूर्णांकk(KERN_ERR "%s: Receive late error.\n", dev->name);
		dev->stats.rx_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_RXPERR) अणु
		prपूर्णांकk(KERN_ERR "%s: Receive DMA parity error.\n", dev->name);
		dev->stats.rx_errors++;
		dev->stats.rx_missed_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (qe_status & CREG_STAT_RXSERR) अणु
		prपूर्णांकk(KERN_ERR "%s: Receive DMA sbus error ack.\n", dev->name);
		dev->stats.rx_errors++;
		dev->stats.rx_missed_errors++;
		mace_hwbug_workaround = 1;
	पूर्ण

	अगर (mace_hwbug_workaround)
		qe_init(qep, 1);
	वापस mace_hwbug_workaround;
पूर्ण

/* Per-QE receive पूर्णांकerrupt service routine.  Just like on the happy meal
 * we receive directly पूर्णांकo skb's with a small packet copy water mark.
 */
अटल व्योम qe_rx(काष्ठा sunqe *qep)
अणु
	काष्ठा qe_rxd *rxbase = &qep->qe_block->qe_rxd[0];
	काष्ठा net_device *dev = qep->dev;
	काष्ठा qe_rxd *this;
	काष्ठा sunqe_buffers *qbufs = qep->buffers;
	__u32 qbufs_dvma = (__u32)qep->buffers_dvma;
	पूर्णांक elem = qep->rx_new;
	u32 flags;

	this = &rxbase[elem];
	जबतक (!((flags = this->rx_flags) & RXD_OWN)) अणु
		काष्ठा sk_buff *skb;
		अचिन्हित अक्षर *this_qbuf =
			&qbufs->rx_buf[elem & (RX_RING_SIZE - 1)][0];
		__u32 this_qbuf_dvma = qbufs_dvma +
			qebuf_offset(rx_buf, (elem & (RX_RING_SIZE - 1)));
		काष्ठा qe_rxd *end_rxd =
			&rxbase[(elem+RX_RING_SIZE)&(RX_RING_MAXSIZE-1)];
		पूर्णांक len = (flags & RXD_LENGTH) - 4;  /* QE adds ether FCS size to len */

		/* Check क्रम errors. */
		अगर (len < ETH_ZLEN) अणु
			dev->stats.rx_errors++;
			dev->stats.rx_length_errors++;
			dev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			skb = netdev_alloc_skb(dev, len + 2);
			अगर (skb == शून्य) अणु
				dev->stats.rx_dropped++;
			पूर्ण अन्यथा अणु
				skb_reserve(skb, 2);
				skb_put(skb, len);
				skb_copy_to_linear_data(skb, this_qbuf,
						 len);
				skb->protocol = eth_type_trans(skb, qep->dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += len;
			पूर्ण
		पूर्ण
		end_rxd->rx_addr = this_qbuf_dvma;
		end_rxd->rx_flags = (RXD_OWN | ((RXD_PKT_SZ) & RXD_LENGTH));

		elem = NEXT_RX(elem);
		this = &rxbase[elem];
	पूर्ण
	qep->rx_new = elem;
पूर्ण

अटल व्योम qe_tx_reclaim(काष्ठा sunqe *qep);

/* Interrupts क्रम all QE's get filtered out via the QEC master controller,
 * so we just run through each qe and check to see who is संकेतing
 * and thus needs to be serviced.
 */
अटल irqवापस_t qec_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sunqec *qecp = dev_id;
	u32 qec_status;
	पूर्णांक channel = 0;

	/* Latch the status now. */
	qec_status = sbus_पढ़ोl(qecp->gregs + GLOB_STAT);
	जबतक (channel < 4) अणु
		अगर (qec_status & 0xf) अणु
			काष्ठा sunqe *qep = qecp->qes[channel];
			u32 qe_status;

			qe_status = sbus_पढ़ोl(qep->qcregs + CREG_STAT);
			अगर (qe_status & CREG_STAT_ERRORS) अणु
				अगर (qe_is_bolixed(qep, qe_status))
					जाओ next;
			पूर्ण
			अगर (qe_status & CREG_STAT_RXIRQ)
				qe_rx(qep);
			अगर (netअगर_queue_stopped(qep->dev) &&
			    (qe_status & CREG_STAT_TXIRQ)) अणु
				spin_lock(&qep->lock);
				qe_tx_reclaim(qep);
				अगर (TX_BUFFS_AVAIL(qep) > 0) अणु
					/* Wake net queue and वापस to
					 * lazy tx reclaim.
					 */
					netअगर_wake_queue(qep->dev);
					sbus_ग_लिखोl(1, qep->qcregs + CREG_TIMASK);
				पूर्ण
				spin_unlock(&qep->lock);
			पूर्ण
	next:
			;
		पूर्ण
		qec_status >>= 4;
		channel++;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qe_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sunqe *qep = netdev_priv(dev);

	qep->mconfig = (MREGS_MCONFIG_TXENAB |
			MREGS_MCONFIG_RXENAB |
			MREGS_MCONFIG_MBAENAB);
	वापस qe_init(qep, 0);
पूर्ण

अटल पूर्णांक qe_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sunqe *qep = netdev_priv(dev);

	qe_stop(qep);
	वापस 0;
पूर्ण

/* Reclaim TX'd frames from the ring.  This must always run under
 * the IRQ रक्षित qep->lock.
 */
अटल व्योम qe_tx_reclaim(काष्ठा sunqe *qep)
अणु
	काष्ठा qe_txd *txbase = &qep->qe_block->qe_txd[0];
	पूर्णांक elem = qep->tx_old;

	जबतक (elem != qep->tx_new) अणु
		u32 flags = txbase[elem].tx_flags;

		अगर (flags & TXD_OWN)
			अवरोध;
		elem = NEXT_TX(elem);
	पूर्ण
	qep->tx_old = elem;
पूर्ण

अटल व्योम qe_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा sunqe *qep = netdev_priv(dev);
	पूर्णांक tx_full;

	spin_lock_irq(&qep->lock);

	/* Try to reclaim, अगर that मुक्तs up some tx
	 * entries, we're fine.
	 */
	qe_tx_reclaim(qep);
	tx_full = TX_BUFFS_AVAIL(qep) <= 0;

	spin_unlock_irq(&qep->lock);

	अगर (! tx_full)
		जाओ out;

	prपूर्णांकk(KERN_ERR "%s: transmit timed out, resetting\n", dev->name);
	qe_init(qep, 1);

out:
	netअगर_wake_queue(dev);
पूर्ण

/* Get a packet queued to go onto the wire. */
अटल netdev_tx_t qe_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sunqe *qep = netdev_priv(dev);
	काष्ठा sunqe_buffers *qbufs = qep->buffers;
	__u32 txbuf_dvma, qbufs_dvma = (__u32)qep->buffers_dvma;
	अचिन्हित अक्षर *txbuf;
	पूर्णांक len, entry;

	spin_lock_irq(&qep->lock);

	qe_tx_reclaim(qep);

	len = skb->len;
	entry = qep->tx_new;

	txbuf = &qbufs->tx_buf[entry & (TX_RING_SIZE - 1)][0];
	txbuf_dvma = qbufs_dvma +
		qebuf_offset(tx_buf, (entry & (TX_RING_SIZE - 1)));

	/* Aव्योम a race... */
	qep->qe_block->qe_txd[entry].tx_flags = TXD_UPDATE;

	skb_copy_from_linear_data(skb, txbuf, len);

	qep->qe_block->qe_txd[entry].tx_addr = txbuf_dvma;
	qep->qe_block->qe_txd[entry].tx_flags =
		(TXD_OWN | TXD_SOP | TXD_EOP | (len & TXD_LENGTH));
	qep->tx_new = NEXT_TX(entry);

	/* Get it going. */
	sbus_ग_लिखोl(CREG_CTRL_TWAKEUP, qep->qcregs + CREG_CTRL);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;

	अगर (TX_BUFFS_AVAIL(qep) <= 0) अणु
		/* Halt the net queue and enable tx पूर्णांकerrupts.
		 * When the tx queue empties the tx irq handler
		 * will wake up the queue and वापस us back to
		 * the lazy tx reclaim scheme.
		 */
		netअगर_stop_queue(dev);
		sbus_ग_लिखोl(0, qep->qcregs + CREG_TIMASK);
	पूर्ण
	spin_unlock_irq(&qep->lock);

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम qe_set_multicast(काष्ठा net_device *dev)
अणु
	काष्ठा sunqe *qep = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	u8 new_mconfig = qep->mconfig;
	पूर्णांक i;
	u32 crc;

	/* Lock out others. */
	netअगर_stop_queue(dev);

	अगर ((dev->flags & IFF_ALLMULTI) || (netdev_mc_count(dev) > 64)) अणु
		sbus_ग_लिखोb(MREGS_IACONFIG_ACHNGE | MREGS_IACONFIG_LARESET,
			    qep->mregs + MREGS_IACONFIG);
		जबतक ((sbus_पढ़ोb(qep->mregs + MREGS_IACONFIG) & MREGS_IACONFIG_ACHNGE) != 0)
			barrier();
		क्रम (i = 0; i < 8; i++)
			sbus_ग_लिखोb(0xff, qep->mregs + MREGS_FILTER);
		sbus_ग_लिखोb(0, qep->mregs + MREGS_IACONFIG);
	पूर्ण अन्यथा अगर (dev->flags & IFF_PROMISC) अणु
		new_mconfig |= MREGS_MCONFIG_PROMISC;
	पूर्ण अन्यथा अणु
		u16 hash_table[4];
		u8 *hbytes = (अचिन्हित अक्षर *) &hash_table[0];

		स_रखो(hash_table, 0, माप(hash_table));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = ether_crc_le(6, ha->addr);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (crc & 0xf);
		पूर्ण
		/* Program the qe with the new filter value. */
		sbus_ग_लिखोb(MREGS_IACONFIG_ACHNGE | MREGS_IACONFIG_LARESET,
			    qep->mregs + MREGS_IACONFIG);
		जबतक ((sbus_पढ़ोb(qep->mregs + MREGS_IACONFIG) & MREGS_IACONFIG_ACHNGE) != 0)
			barrier();
		क्रम (i = 0; i < 8; i++) अणु
			u8 पंचांगp = *hbytes++;
			sbus_ग_लिखोb(पंचांगp, qep->mregs + MREGS_FILTER);
		पूर्ण
		sbus_ग_लिखोb(0, qep->mregs + MREGS_IACONFIG);
	पूर्ण

	/* Any change of the logical address filter, the physical address,
	 * or enabling/disabling promiscuous mode causes the MACE to disable
	 * the receiver.  So we must re-enable them here or अन्यथा the MACE
	 * refuses to listen to anything on the network.  Sheesh, took
	 * me a day or two to find this bug.
	 */
	qep->mconfig = new_mconfig;
	sbus_ग_लिखोb(qep->mconfig, qep->mregs + MREGS_MCONFIG);

	/* Let us get going again. */
	netअगर_wake_queue(dev);
पूर्ण

/* Ethtool support... */
अटल व्योम qe_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	स्थिर काष्ठा linux_prom_रेजिस्टरs *regs;
	काष्ठा sunqe *qep = netdev_priv(dev);
	काष्ठा platक्रमm_device *op;

	strlcpy(info->driver, "sunqe", माप(info->driver));
	strlcpy(info->version, "3.0", माप(info->version));

	op = qep->op;
	regs = of_get_property(op->dev.of_node, "reg", शून्य);
	अगर (regs)
		snम_लिखो(info->bus_info, माप(info->bus_info), "SBUS:%d",
			 regs->which_io);

पूर्ण

अटल u32 qe_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा sunqe *qep = netdev_priv(dev);
	व्योम __iomem *mregs = qep->mregs;
	u8 phyconfig;

	spin_lock_irq(&qep->lock);
	phyconfig = sbus_पढ़ोb(mregs + MREGS_PHYCONFIG);
	spin_unlock_irq(&qep->lock);

	वापस phyconfig & MREGS_PHYCONFIG_LSTAT;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops qe_ethtool_ops = अणु
	.get_drvinfo		= qe_get_drvinfo,
	.get_link		= qe_get_link,
पूर्ण;

/* This is only called once at boot समय क्रम each card probed. */
अटल व्योम qec_init_once(काष्ठा sunqec *qecp, काष्ठा platक्रमm_device *op)
अणु
	u8 bsizes = qecp->qec_bursts;

	अगर (sbus_can_burst64() && (bsizes & DMA_BURST64)) अणु
		sbus_ग_लिखोl(GLOB_CTRL_B64, qecp->gregs + GLOB_CTRL);
	पूर्ण अन्यथा अगर (bsizes & DMA_BURST32) अणु
		sbus_ग_लिखोl(GLOB_CTRL_B32, qecp->gregs + GLOB_CTRL);
	पूर्ण अन्यथा अणु
		sbus_ग_लिखोl(GLOB_CTRL_B16, qecp->gregs + GLOB_CTRL);
	पूर्ण

	/* Packetsize only used in 100baseT BigMAC configurations,
	 * set it to zero just to be on the safe side.
	 */
	sbus_ग_लिखोl(GLOB_PSIZE_2048, qecp->gregs + GLOB_PSIZE);

	/* Set the local memsize रेजिस्टर, भागided up to one piece per QE channel. */
	sbus_ग_लिखोl((resource_size(&op->resource[1]) >> 2),
		    qecp->gregs + GLOB_MSIZE);

	/* Divide up the local QEC memory amongst the 4 QE receiver and
	 * transmitter FIFOs.  Basically it is (total / 2 / num_channels).
	 */
	sbus_ग_लिखोl((resource_size(&op->resource[1]) >> 2) >> 1,
		    qecp->gregs + GLOB_TSIZE);
	sbus_ग_लिखोl((resource_size(&op->resource[1]) >> 2) >> 1,
		    qecp->gregs + GLOB_RSIZE);
पूर्ण

अटल u8 qec_get_burst(काष्ठा device_node *dp)
अणु
	u8 bsizes, bsizes_more;

	/* Find and set the burst sizes क्रम the QEC, since it
	 * करोes the actual dma क्रम all 4 channels.
	 */
	bsizes = of_getपूर्णांकprop_शेष(dp, "burst-sizes", 0xff);
	bsizes &= 0xff;
	bsizes_more = of_getपूर्णांकprop_शेष(dp->parent, "burst-sizes", 0xff);

	अगर (bsizes_more != 0xff)
		bsizes &= bsizes_more;
	अगर (bsizes == 0xff || (bsizes & DMA_BURST16) == 0 ||
	    (bsizes & DMA_BURST32)==0)
		bsizes = (DMA_BURST32 - 1);

	वापस bsizes;
पूर्ण

अटल काष्ठा sunqec *get_qec(काष्ठा platक्रमm_device *child)
अणु
	काष्ठा platक्रमm_device *op = to_platक्रमm_device(child->dev.parent);
	काष्ठा sunqec *qecp;

	qecp = platक्रमm_get_drvdata(op);
	अगर (!qecp) अणु
		qecp = kzalloc(माप(काष्ठा sunqec), GFP_KERNEL);
		अगर (qecp) अणु
			u32 ctrl;

			qecp->op = op;
			qecp->gregs = of_ioremap(&op->resource[0], 0,
						 GLOB_REG_SIZE,
						 "QEC Global Registers");
			अगर (!qecp->gregs)
				जाओ fail;

			/* Make sure the QEC is in MACE mode. */
			ctrl = sbus_पढ़ोl(qecp->gregs + GLOB_CTRL);
			ctrl &= 0xf0000000;
			अगर (ctrl != GLOB_CTRL_MMODE) अणु
				prपूर्णांकk(KERN_ERR "qec: Not in MACE mode!\n");
				जाओ fail;
			पूर्ण

			अगर (qec_global_reset(qecp->gregs))
				जाओ fail;

			qecp->qec_bursts = qec_get_burst(op->dev.of_node);

			qec_init_once(qecp, op);

			अगर (request_irq(op->archdata.irqs[0], qec_पूर्णांकerrupt,
					IRQF_SHARED, "qec", (व्योम *) qecp)) अणु
				prपूर्णांकk(KERN_ERR "qec: Can't register irq.\n");
				जाओ fail;
			पूर्ण

			platक्रमm_set_drvdata(op, qecp);

			qecp->next_module = root_qec_dev;
			root_qec_dev = qecp;
		पूर्ण
	पूर्ण

	वापस qecp;

fail:
	अगर (qecp->gregs)
		of_iounmap(&op->resource[0], qecp->gregs, GLOB_REG_SIZE);
	kमुक्त(qecp);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा net_device_ops qec_ops = अणु
	.nकरो_खोलो		= qe_खोलो,
	.nकरो_stop		= qe_बंद,
	.nकरो_start_xmit		= qe_start_xmit,
	.nकरो_set_rx_mode	= qe_set_multicast,
	.nकरो_tx_समयout		= qe_tx_समयout,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक qec_ether_init(काष्ठा platक्रमm_device *op)
अणु
	अटल अचिन्हित version_prपूर्णांकed;
	काष्ठा net_device *dev;
	काष्ठा sunqec *qecp;
	काष्ठा sunqe *qe;
	पूर्णांक i, res;

	अगर (version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);

	dev = alloc_etherdev(माप(काष्ठा sunqe));
	अगर (!dev)
		वापस -ENOMEM;

	स_नकल(dev->dev_addr, idprom->id_ethaddr, ETH_ALEN);

	qe = netdev_priv(dev);

	res = -ENODEV;

	i = of_getपूर्णांकprop_शेष(op->dev.of_node, "channel#", -1);
	अगर (i == -1)
		जाओ fail;
	qe->channel = i;
	spin_lock_init(&qe->lock);

	qecp = get_qec(op);
	अगर (!qecp)
		जाओ fail;

	qecp->qes[qe->channel] = qe;
	qe->dev = dev;
	qe->parent = qecp;
	qe->op = op;

	res = -ENOMEM;
	qe->qcregs = of_ioremap(&op->resource[0], 0,
				CREG_REG_SIZE, "QEC Channel Registers");
	अगर (!qe->qcregs) अणु
		prपूर्णांकk(KERN_ERR "qe: Cannot map channel registers.\n");
		जाओ fail;
	पूर्ण

	qe->mregs = of_ioremap(&op->resource[1], 0,
			       MREGS_REG_SIZE, "QE MACE Registers");
	अगर (!qe->mregs) अणु
		prपूर्णांकk(KERN_ERR "qe: Cannot map MACE registers.\n");
		जाओ fail;
	पूर्ण

	qe->qe_block = dma_alloc_coherent(&op->dev, PAGE_SIZE,
					  &qe->qblock_dvma, GFP_ATOMIC);
	qe->buffers = dma_alloc_coherent(&op->dev, माप(काष्ठा sunqe_buffers),
					 &qe->buffers_dvma, GFP_ATOMIC);
	अगर (qe->qe_block == शून्य || qe->qblock_dvma == 0 ||
	    qe->buffers == शून्य || qe->buffers_dvma == 0)
		जाओ fail;

	/* Stop this QE. */
	qe_stop(qe);

	SET_NETDEV_DEV(dev, &op->dev);

	dev->watchकरोg_समयo = 5*HZ;
	dev->irq = op->archdata.irqs[0];
	dev->dma = 0;
	dev->ethtool_ops = &qe_ethtool_ops;
	dev->netdev_ops = &qec_ops;

	res = रेजिस्टर_netdev(dev);
	अगर (res)
		जाओ fail;

	platक्रमm_set_drvdata(op, qe);

	prपूर्णांकk(KERN_INFO "%s: qe channel[%d] %pM\n", dev->name, qe->channel,
	       dev->dev_addr);
	वापस 0;

fail:
	अगर (qe->qcregs)
		of_iounmap(&op->resource[0], qe->qcregs, CREG_REG_SIZE);
	अगर (qe->mregs)
		of_iounmap(&op->resource[1], qe->mregs, MREGS_REG_SIZE);
	अगर (qe->qe_block)
		dma_मुक्त_coherent(&op->dev, PAGE_SIZE,
				  qe->qe_block, qe->qblock_dvma);
	अगर (qe->buffers)
		dma_मुक्त_coherent(&op->dev,
				  माप(काष्ठा sunqe_buffers),
				  qe->buffers,
				  qe->buffers_dvma);

	मुक्त_netdev(dev);

	वापस res;
पूर्ण

अटल पूर्णांक qec_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	वापस qec_ether_init(op);
पूर्ण

अटल पूर्णांक qec_sbus_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा sunqe *qp = platक्रमm_get_drvdata(op);
	काष्ठा net_device *net_dev = qp->dev;

	unरेजिस्टर_netdev(net_dev);

	of_iounmap(&op->resource[0], qp->qcregs, CREG_REG_SIZE);
	of_iounmap(&op->resource[1], qp->mregs, MREGS_REG_SIZE);
	dma_मुक्त_coherent(&op->dev, PAGE_SIZE,
			  qp->qe_block, qp->qblock_dvma);
	dma_मुक्त_coherent(&op->dev, माप(काष्ठा sunqe_buffers),
			  qp->buffers, qp->buffers_dvma);

	मुक्त_netdev(net_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qec_sbus_match[] = अणु
	अणु
		.name = "qe",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, qec_sbus_match);

अटल काष्ठा platक्रमm_driver qec_sbus_driver = अणु
	.driver = अणु
		.name = "qec",
		.of_match_table = qec_sbus_match,
	पूर्ण,
	.probe		= qec_sbus_probe,
	.हटाओ		= qec_sbus_हटाओ,
पूर्ण;

अटल पूर्णांक __init qec_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qec_sbus_driver);
पूर्ण

अटल व्योम __निकास qec_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qec_sbus_driver);

	जबतक (root_qec_dev) अणु
		काष्ठा sunqec *next = root_qec_dev->next_module;
		काष्ठा platक्रमm_device *op = root_qec_dev->op;

		मुक्त_irq(op->archdata.irqs[0], (व्योम *) root_qec_dev);
		of_iounmap(&op->resource[0], root_qec_dev->gregs,
			   GLOB_REG_SIZE);
		kमुक्त(root_qec_dev);

		root_qec_dev = next;
	पूर्ण
पूर्ण

module_init(qec_init);
module_निकास(qec_निकास);
