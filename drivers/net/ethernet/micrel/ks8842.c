<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ks8842.c timberdale KS8842 ethernet driver
 * Copyright (c) 2009 Intel Corporation
 */

/* Supports:
 * The Micrel KS8842 behind the timberdale FPGA
 * The genuine Micrel KS8841/42 device with ISA 16/32bit bus पूर्णांकerface
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ks8842.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>

#घोषणा DRV_NAME "ks8842"

/* Timberdale specअगरic Registers */
#घोषणा REG_TIMB_RST		0x1c
#घोषणा REG_TIMB_FIFO		0x20
#घोषणा REG_TIMB_ISR		0x24
#घोषणा REG_TIMB_IER		0x28
#घोषणा REG_TIMB_IAR		0x2C
#घोषणा REQ_TIMB_DMA_RESUME	0x30

/* KS8842 रेजिस्टरs */

#घोषणा REG_SELECT_BANK 0x0e

/* bank 0 रेजिस्टरs */
#घोषणा REG_QRFCR	0x04

/* bank 2 रेजिस्टरs */
#घोषणा REG_MARL	0x00
#घोषणा REG_MARM	0x02
#घोषणा REG_MARH	0x04

/* bank 3 रेजिस्टरs */
#घोषणा REG_GRR		0x06

/* bank 16 रेजिस्टरs */
#घोषणा REG_TXCR	0x00
#घोषणा REG_TXSR	0x02
#घोषणा REG_RXCR	0x04
#घोषणा REG_TXMIR	0x08
#घोषणा REG_RXMIR	0x0A

/* bank 17 रेजिस्टरs */
#घोषणा REG_TXQCR	0x00
#घोषणा REG_RXQCR	0x02
#घोषणा REG_TXFDPR	0x04
#घोषणा REG_RXFDPR	0x06
#घोषणा REG_QMU_DATA_LO 0x08
#घोषणा REG_QMU_DATA_HI 0x0A

/* bank 18 रेजिस्टरs */
#घोषणा REG_IER		0x00
#घोषणा IRQ_LINK_CHANGE	0x8000
#घोषणा IRQ_TX		0x4000
#घोषणा IRQ_RX		0x2000
#घोषणा IRQ_RX_OVERRUN	0x0800
#घोषणा IRQ_TX_STOPPED	0x0200
#घोषणा IRQ_RX_STOPPED	0x0100
#घोषणा IRQ_RX_ERROR	0x0080
#घोषणा ENABLED_IRQS	(IRQ_LINK_CHANGE | IRQ_TX | IRQ_RX | IRQ_RX_STOPPED | \
		IRQ_TX_STOPPED | IRQ_RX_OVERRUN | IRQ_RX_ERROR)
/* When running via timberdale in DMA mode, the RX पूर्णांकerrupt should be
   enabled in the KS8842, but not in the FPGA IP, since the IP handles
   RX DMA पूर्णांकernally.
   TX पूर्णांकerrupts are not needed it is handled by the FPGA the driver is
   notअगरied via DMA callbacks.
*/
#घोषणा ENABLED_IRQS_DMA_IP	(IRQ_LINK_CHANGE | IRQ_RX_STOPPED | \
	IRQ_TX_STOPPED | IRQ_RX_OVERRUN | IRQ_RX_ERROR)
#घोषणा ENABLED_IRQS_DMA	(ENABLED_IRQS_DMA_IP | IRQ_RX)
#घोषणा REG_ISR		0x02
#घोषणा REG_RXSR	0x04
#घोषणा RXSR_VALID	0x8000
#घोषणा RXSR_BROADCAST	0x80
#घोषणा RXSR_MULTICAST	0x40
#घोषणा RXSR_UNICAST	0x20
#घोषणा RXSR_FRAMETYPE	0x08
#घोषणा RXSR_TOO_LONG	0x04
#घोषणा RXSR_RUNT	0x02
#घोषणा RXSR_CRC_ERROR	0x01
#घोषणा RXSR_ERROR	(RXSR_TOO_LONG | RXSR_RUNT | RXSR_CRC_ERROR)

/* bank 32 रेजिस्टरs */
#घोषणा REG_SW_ID_AND_ENABLE	0x00
#घोषणा REG_SGCR1		0x02
#घोषणा REG_SGCR2		0x04
#घोषणा REG_SGCR3		0x06

/* bank 39 रेजिस्टरs */
#घोषणा REG_MACAR1		0x00
#घोषणा REG_MACAR2		0x02
#घोषणा REG_MACAR3		0x04

/* bank 45 रेजिस्टरs */
#घोषणा REG_P1MBCR		0x00
#घोषणा REG_P1MBSR		0x02

/* bank 46 रेजिस्टरs */
#घोषणा REG_P2MBCR		0x00
#घोषणा REG_P2MBSR		0x02

/* bank 48 रेजिस्टरs */
#घोषणा REG_P1CR2		0x02

/* bank 49 रेजिस्टरs */
#घोषणा REG_P1CR4		0x02
#घोषणा REG_P1SR		0x04

/* flags passed by platक्रमm_device क्रम configuration */
#घोषणा	MICREL_KS884X		0x01	/* 0=Timeberdale(FPGA), 1=Micrel */
#घोषणा	KS884X_16BIT		0x02	/*  1=16bit, 0=32bit */

#घोषणा DMA_BUFFER_SIZE		2048

काष्ठा ks8842_tx_dma_ctl अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_async_tx_descriptor *adesc;
	व्योम *buf;
	काष्ठा scatterlist sg;
	पूर्णांक channel;
पूर्ण;

काष्ठा ks8842_rx_dma_ctl अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_async_tx_descriptor *adesc;
	काष्ठा sk_buff  *skb;
	काष्ठा scatterlist sg;
	काष्ठा tasklet_काष्ठा tasklet;
	पूर्णांक channel;
पूर्ण;

#घोषणा KS8842_USE_DMA(adapter) (((adapter)->dma_tx.channel != -1) && \
	 ((adapter)->dma_rx.channel != -1))

काष्ठा ks8842_adapter अणु
	व्योम __iomem	*hw_addr;
	पूर्णांक		irq;
	अचिन्हित दीर्घ	conf_flags;	/* copy of platक्रमm_device config */
	काष्ठा tasklet_काष्ठा	tasklet;
	spinlock_t	lock; /* spinlock to be पूर्णांकerrupt safe */
	काष्ठा work_काष्ठा समयout_work;
	काष्ठा net_device *netdev;
	काष्ठा device *dev;
	काष्ठा ks8842_tx_dma_ctl	dma_tx;
	काष्ठा ks8842_rx_dma_ctl	dma_rx;
पूर्ण;

अटल व्योम ks8842_dma_rx_cb(व्योम *data);
अटल व्योम ks8842_dma_tx_cb(व्योम *data);

अटल अंतरभूत व्योम ks8842_resume_dma(काष्ठा ks8842_adapter *adapter)
अणु
	ioग_लिखो32(1, adapter->hw_addr + REQ_TIMB_DMA_RESUME);
पूर्ण

अटल अंतरभूत व्योम ks8842_select_bank(काष्ठा ks8842_adapter *adapter, u16 bank)
अणु
	ioग_लिखो16(bank, adapter->hw_addr + REG_SELECT_BANK);
पूर्ण

अटल अंतरभूत व्योम ks8842_ग_लिखो8(काष्ठा ks8842_adapter *adapter, u16 bank,
	u8 value, पूर्णांक offset)
अणु
	ks8842_select_bank(adapter, bank);
	ioग_लिखो8(value, adapter->hw_addr + offset);
पूर्ण

अटल अंतरभूत व्योम ks8842_ग_लिखो16(काष्ठा ks8842_adapter *adapter, u16 bank,
	u16 value, पूर्णांक offset)
अणु
	ks8842_select_bank(adapter, bank);
	ioग_लिखो16(value, adapter->hw_addr + offset);
पूर्ण

अटल अंतरभूत व्योम ks8842_enable_bits(काष्ठा ks8842_adapter *adapter, u16 bank,
	u16 bits, पूर्णांक offset)
अणु
	u16 reg;
	ks8842_select_bank(adapter, bank);
	reg = ioपढ़ो16(adapter->hw_addr + offset);
	reg |= bits;
	ioग_लिखो16(reg, adapter->hw_addr + offset);
पूर्ण

अटल अंतरभूत व्योम ks8842_clear_bits(काष्ठा ks8842_adapter *adapter, u16 bank,
	u16 bits, पूर्णांक offset)
अणु
	u16 reg;
	ks8842_select_bank(adapter, bank);
	reg = ioपढ़ो16(adapter->hw_addr + offset);
	reg &= ~bits;
	ioग_लिखो16(reg, adapter->hw_addr + offset);
पूर्ण

अटल अंतरभूत व्योम ks8842_ग_लिखो32(काष्ठा ks8842_adapter *adapter, u16 bank,
	u32 value, पूर्णांक offset)
अणु
	ks8842_select_bank(adapter, bank);
	ioग_लिखो32(value, adapter->hw_addr + offset);
पूर्ण

अटल अंतरभूत u8 ks8842_पढ़ो8(काष्ठा ks8842_adapter *adapter, u16 bank,
	पूर्णांक offset)
अणु
	ks8842_select_bank(adapter, bank);
	वापस ioपढ़ो8(adapter->hw_addr + offset);
पूर्ण

अटल अंतरभूत u16 ks8842_पढ़ो16(काष्ठा ks8842_adapter *adapter, u16 bank,
	पूर्णांक offset)
अणु
	ks8842_select_bank(adapter, bank);
	वापस ioपढ़ो16(adapter->hw_addr + offset);
पूर्ण

अटल अंतरभूत u32 ks8842_पढ़ो32(काष्ठा ks8842_adapter *adapter, u16 bank,
	पूर्णांक offset)
अणु
	ks8842_select_bank(adapter, bank);
	वापस ioपढ़ो32(adapter->hw_addr + offset);
पूर्ण

अटल व्योम ks8842_reset(काष्ठा ks8842_adapter *adapter)
अणु
	अगर (adapter->conf_flags & MICREL_KS884X) अणु
		ks8842_ग_लिखो16(adapter, 3, 1, REG_GRR);
		msleep(10);
		ioग_लिखो16(0, adapter->hw_addr + REG_GRR);
	पूर्ण अन्यथा अणु
		/* The KS8842 goes haywire when करोing softare reset
		* a work around in the timberdale IP is implemented to
		* करो a hardware reset instead
		ks8842_ग_लिखो16(adapter, 3, 1, REG_GRR);
		msleep(10);
		ioग_लिखो16(0, adapter->hw_addr + REG_GRR);
		*/
		ioग_लिखो32(0x1, adapter->hw_addr + REG_TIMB_RST);
		msleep(20);
	पूर्ण
पूर्ण

अटल व्योम ks8842_update_link_status(काष्ठा net_device *netdev,
	काष्ठा ks8842_adapter *adapter)
अणु
	/* check the status of the link */
	अगर (ks8842_पढ़ो16(adapter, 45, REG_P1MBSR) & 0x4) अणु
		netअगर_carrier_on(netdev);
		netअगर_wake_queue(netdev);
	पूर्ण अन्यथा अणु
		netअगर_stop_queue(netdev);
		netअगर_carrier_off(netdev);
	पूर्ण
पूर्ण

अटल व्योम ks8842_enable_tx(काष्ठा ks8842_adapter *adapter)
अणु
	ks8842_enable_bits(adapter, 16, 0x01, REG_TXCR);
पूर्ण

अटल व्योम ks8842_disable_tx(काष्ठा ks8842_adapter *adapter)
अणु
	ks8842_clear_bits(adapter, 16, 0x01, REG_TXCR);
पूर्ण

अटल व्योम ks8842_enable_rx(काष्ठा ks8842_adapter *adapter)
अणु
	ks8842_enable_bits(adapter, 16, 0x01, REG_RXCR);
पूर्ण

अटल व्योम ks8842_disable_rx(काष्ठा ks8842_adapter *adapter)
अणु
	ks8842_clear_bits(adapter, 16, 0x01, REG_RXCR);
पूर्ण

अटल व्योम ks8842_reset_hw(काष्ठा ks8842_adapter *adapter)
अणु
	/* reset the HW */
	ks8842_reset(adapter);

	/* Enable QMU Transmit flow control / transmit padding / Transmit CRC */
	ks8842_ग_लिखो16(adapter, 16, 0x000E, REG_TXCR);

	/* enable the receiver, uni + multi + broadcast + flow ctrl
		+ crc strip */
	ks8842_ग_लिखो16(adapter, 16, 0x8 | 0x20 | 0x40 | 0x80 | 0x400,
		REG_RXCR);

	/* TX frame poपूर्णांकer स्वतःincrement */
	ks8842_ग_लिखो16(adapter, 17, 0x4000, REG_TXFDPR);

	/* RX frame poपूर्णांकer स्वतःincrement */
	ks8842_ग_लिखो16(adapter, 17, 0x4000, REG_RXFDPR);

	/* RX 2 kb high watermark */
	ks8842_ग_लिखो16(adapter, 0, 0x1000, REG_QRFCR);

	/* aggressive back off in half duplex */
	ks8842_enable_bits(adapter, 32, 1 << 8, REG_SGCR1);

	/* enable no excessive collison drop */
	ks8842_enable_bits(adapter, 32, 1 << 3, REG_SGCR2);

	/* Enable port 1 क्रमce flow control / back pressure / transmit / recv */
	ks8842_ग_लिखो16(adapter, 48, 0x1E07, REG_P1CR2);

	/* restart port स्वतः-negotiation */
	ks8842_enable_bits(adapter, 49, 1 << 13, REG_P1CR4);

	/* Enable the transmitter */
	ks8842_enable_tx(adapter);

	/* Enable the receiver */
	ks8842_enable_rx(adapter);

	/* clear all पूर्णांकerrupts */
	ks8842_ग_लिखो16(adapter, 18, 0xffff, REG_ISR);

	/* enable पूर्णांकerrupts */
	अगर (KS8842_USE_DMA(adapter)) अणु
		/* When running in DMA Mode the RX पूर्णांकerrupt is not enabled in
		   timberdale because RX data is received by DMA callbacks
		   it must still be enabled in the KS8842 because it indicates
		   to timberdale when there is RX data क्रम it's DMA FIFOs */
		ioग_लिखो16(ENABLED_IRQS_DMA_IP, adapter->hw_addr + REG_TIMB_IER);
		ks8842_ग_लिखो16(adapter, 18, ENABLED_IRQS_DMA, REG_IER);
	पूर्ण अन्यथा अणु
		अगर (!(adapter->conf_flags & MICREL_KS884X))
			ioग_लिखो16(ENABLED_IRQS,
				adapter->hw_addr + REG_TIMB_IER);
		ks8842_ग_लिखो16(adapter, 18, ENABLED_IRQS, REG_IER);
	पूर्ण
	/* enable the चयन */
	ks8842_ग_लिखो16(adapter, 32, 0x1, REG_SW_ID_AND_ENABLE);
पूर्ण

अटल व्योम ks8842_पढ़ो_mac_addr(काष्ठा ks8842_adapter *adapter, u8 *dest)
अणु
	पूर्णांक i;
	u16 mac;

	क्रम (i = 0; i < ETH_ALEN; i++)
		dest[ETH_ALEN - i - 1] = ks8842_पढ़ो8(adapter, 2, REG_MARL + i);

	अगर (adapter->conf_flags & MICREL_KS884X) अणु
		/*
		the sequence of saving mac addr between MAC and Switch is
		dअगरferent.
		*/

		mac = ks8842_पढ़ो16(adapter, 2, REG_MARL);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR3);
		mac = ks8842_पढ़ो16(adapter, 2, REG_MARM);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR2);
		mac = ks8842_पढ़ो16(adapter, 2, REG_MARH);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR1);
	पूर्ण अन्यथा अणु

		/* make sure the चयन port uses the same MAC as the QMU */
		mac = ks8842_पढ़ो16(adapter, 2, REG_MARL);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR1);
		mac = ks8842_पढ़ो16(adapter, 2, REG_MARM);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR2);
		mac = ks8842_पढ़ो16(adapter, 2, REG_MARH);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR3);
	पूर्ण
पूर्ण

अटल व्योम ks8842_ग_लिखो_mac_addr(काष्ठा ks8842_adapter *adapter, u8 *mac)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित i;

	spin_lock_irqsave(&adapter->lock, flags);
	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		ks8842_ग_लिखो8(adapter, 2, mac[ETH_ALEN - i - 1], REG_MARL + i);
		अगर (!(adapter->conf_flags & MICREL_KS884X))
			ks8842_ग_लिखो8(adapter, 39, mac[ETH_ALEN - i - 1],
				REG_MACAR1 + i);
	पूर्ण

	अगर (adapter->conf_flags & MICREL_KS884X) अणु
		/*
		the sequence of saving mac addr between MAC and Switch is
		dअगरferent.
		*/

		u16 mac;

		mac = ks8842_पढ़ो16(adapter, 2, REG_MARL);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR3);
		mac = ks8842_पढ़ो16(adapter, 2, REG_MARM);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR2);
		mac = ks8842_पढ़ो16(adapter, 2, REG_MARH);
		ks8842_ग_लिखो16(adapter, 39, mac, REG_MACAR1);
	पूर्ण
	spin_unlock_irqrestore(&adapter->lock, flags);
पूर्ण

अटल अंतरभूत u16 ks8842_tx_fअगरo_space(काष्ठा ks8842_adapter *adapter)
अणु
	वापस ks8842_पढ़ो16(adapter, 16, REG_TXMIR) & 0x1fff;
पूर्ण

अटल पूर्णांक ks8842_tx_frame_dma(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	काष्ठा ks8842_tx_dma_ctl *ctl = &adapter->dma_tx;
	u8 *buf = ctl->buf;

	अगर (ctl->adesc) अणु
		netdev_dbg(netdev, "%s: TX ongoing\n", __func__);
		/* transfer ongoing */
		वापस NETDEV_TX_BUSY;
	पूर्ण

	sg_dma_len(&ctl->sg) = skb->len + माप(u32);

	/* copy data to the TX buffer */
	/* the control word, enable IRQ, port 1 and the length */
	*buf++ = 0x00;
	*buf++ = 0x01; /* Port 1 */
	*buf++ = skb->len & 0xff;
	*buf++ = (skb->len >> 8) & 0xff;
	skb_copy_from_linear_data(skb, buf, skb->len);

	dma_sync_single_range_क्रम_device(adapter->dev,
		sg_dma_address(&ctl->sg), 0, sg_dma_len(&ctl->sg),
		DMA_TO_DEVICE);

	/* make sure the length is a multiple of 4 */
	अगर (sg_dma_len(&ctl->sg) % 4)
		sg_dma_len(&ctl->sg) += 4 - sg_dma_len(&ctl->sg) % 4;

	ctl->adesc = dmaengine_prep_slave_sg(ctl->chan,
		&ctl->sg, 1, DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
	अगर (!ctl->adesc)
		वापस NETDEV_TX_BUSY;

	ctl->adesc->callback_param = netdev;
	ctl->adesc->callback = ks8842_dma_tx_cb;
	ctl->adesc->tx_submit(ctl->adesc);

	netdev->stats.tx_bytes += skb->len;

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ks8842_tx_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	पूर्णांक len = skb->len;

	netdev_dbg(netdev, "%s: len %u head %p data %p tail %p end %p\n",
		__func__, skb->len, skb->head, skb->data,
		skb_tail_poपूर्णांकer(skb), skb_end_poपूर्णांकer(skb));

	/* check FIFO buffer space, we need space क्रम CRC and command bits */
	अगर (ks8842_tx_fअगरo_space(adapter) < len + 8)
		वापस NETDEV_TX_BUSY;

	अगर (adapter->conf_flags & KS884X_16BIT) अणु
		u16 *ptr16 = (u16 *)skb->data;
		ks8842_ग_लिखो16(adapter, 17, 0x8000 | 0x100, REG_QMU_DATA_LO);
		ks8842_ग_लिखो16(adapter, 17, (u16)len, REG_QMU_DATA_HI);
		netdev->stats.tx_bytes += len;

		/* copy buffer */
		जबतक (len > 0) अणु
			ioग_लिखो16(*ptr16++, adapter->hw_addr + REG_QMU_DATA_LO);
			ioग_लिखो16(*ptr16++, adapter->hw_addr + REG_QMU_DATA_HI);
			len -= माप(u32);
		पूर्ण
	पूर्ण अन्यथा अणु

		u32 *ptr = (u32 *)skb->data;
		u32 ctrl;
		/* the control word, enable IRQ, port 1 and the length */
		ctrl = 0x8000 | 0x100 | (len << 16);
		ks8842_ग_लिखो32(adapter, 17, ctrl, REG_QMU_DATA_LO);

		netdev->stats.tx_bytes += len;

		/* copy buffer */
		जबतक (len > 0) अणु
			ioग_लिखो32(*ptr, adapter->hw_addr + REG_QMU_DATA_LO);
			len -= माप(u32);
			ptr++;
		पूर्ण
	पूर्ण

	/* enqueue packet */
	ks8842_ग_लिखो16(adapter, 17, 1, REG_TXQCR);

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ks8842_update_rx_err_counters(काष्ठा net_device *netdev, u32 status)
अणु
	netdev_dbg(netdev, "RX error, status: %x\n", status);

	netdev->stats.rx_errors++;
	अगर (status & RXSR_TOO_LONG)
		netdev->stats.rx_length_errors++;
	अगर (status & RXSR_CRC_ERROR)
		netdev->stats.rx_crc_errors++;
	अगर (status & RXSR_RUNT)
		netdev->stats.rx_frame_errors++;
पूर्ण

अटल व्योम ks8842_update_rx_counters(काष्ठा net_device *netdev, u32 status,
	पूर्णांक len)
अणु
	netdev_dbg(netdev, "RX packet, len: %d\n", len);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += len;
	अगर (status & RXSR_MULTICAST)
		netdev->stats.multicast++;
पूर्ण

अटल पूर्णांक __ks8842_start_new_rx_dma(काष्ठा net_device *netdev)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	काष्ठा ks8842_rx_dma_ctl *ctl = &adapter->dma_rx;
	काष्ठा scatterlist *sg = &ctl->sg;
	पूर्णांक err;

	ctl->skb = netdev_alloc_skb(netdev, DMA_BUFFER_SIZE);
	अगर (ctl->skb) अणु
		sg_init_table(sg, 1);
		sg_dma_address(sg) = dma_map_single(adapter->dev,
			ctl->skb->data, DMA_BUFFER_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(adapter->dev, sg_dma_address(sg))) अणु
			err = -ENOMEM;
			sg_dma_address(sg) = 0;
			जाओ out;
		पूर्ण

		sg_dma_len(sg) = DMA_BUFFER_SIZE;

		ctl->adesc = dmaengine_prep_slave_sg(ctl->chan,
			sg, 1, DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT);

		अगर (!ctl->adesc) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		ctl->adesc->callback_param = netdev;
		ctl->adesc->callback = ks8842_dma_rx_cb;
		ctl->adesc->tx_submit(ctl->adesc);
	पूर्ण अन्यथा अणु
		err = -ENOMEM;
		sg_dma_address(sg) = 0;
		जाओ out;
	पूर्ण

	वापस 0;
out:
	अगर (sg_dma_address(sg))
		dma_unmap_single(adapter->dev, sg_dma_address(sg),
			DMA_BUFFER_SIZE, DMA_FROM_DEVICE);
	sg_dma_address(sg) = 0;
	dev_kमुक्त_skb(ctl->skb);
	ctl->skb = शून्य;

	prपूर्णांकk(KERN_ERR DRV_NAME": Failed to start RX DMA: %d\n", err);
	वापस err;
पूर्ण

अटल व्योम ks8842_rx_frame_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ks8842_adapter *adapter = from_tasklet(adapter, t, dma_rx.tasklet);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ks8842_rx_dma_ctl *ctl = &adapter->dma_rx;
	काष्ठा sk_buff *skb = ctl->skb;
	dma_addr_t addr = sg_dma_address(&ctl->sg);
	u32 status;

	ctl->adesc = शून्य;

	/* kick next transfer going */
	__ks8842_start_new_rx_dma(netdev);

	/* now handle the data we got */
	dma_unmap_single(adapter->dev, addr, DMA_BUFFER_SIZE, DMA_FROM_DEVICE);

	status = *((u32 *)skb->data);

	netdev_dbg(netdev, "%s - rx_data: status: %x\n",
		__func__, status & 0xffff);

	/* check the status */
	अगर ((status & RXSR_VALID) && !(status & RXSR_ERROR)) अणु
		पूर्णांक len = (status >> 16) & 0x7ff;

		ks8842_update_rx_counters(netdev, status, len);

		/* reserve 4 bytes which is the status word */
		skb_reserve(skb, 4);
		skb_put(skb, len);

		skb->protocol = eth_type_trans(skb, netdev);
		netअगर_rx(skb);
	पूर्ण अन्यथा अणु
		ks8842_update_rx_err_counters(netdev, status);
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम ks8842_rx_frame(काष्ठा net_device *netdev,
	काष्ठा ks8842_adapter *adapter)
अणु
	u32 status;
	पूर्णांक len;

	अगर (adapter->conf_flags & KS884X_16BIT) अणु
		status = ks8842_पढ़ो16(adapter, 17, REG_QMU_DATA_LO);
		len = ks8842_पढ़ो16(adapter, 17, REG_QMU_DATA_HI);
		netdev_dbg(netdev, "%s - rx_data: status: %x\n",
			   __func__, status);
	पूर्ण अन्यथा अणु
		status = ks8842_पढ़ो32(adapter, 17, REG_QMU_DATA_LO);
		len = (status >> 16) & 0x7ff;
		status &= 0xffff;
		netdev_dbg(netdev, "%s - rx_data: status: %x\n",
			   __func__, status);
	पूर्ण

	/* check the status */
	अगर ((status & RXSR_VALID) && !(status & RXSR_ERROR)) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb_ip_align(netdev, len + 3);

		अगर (skb) अणु

			ks8842_update_rx_counters(netdev, status, len);

			अगर (adapter->conf_flags & KS884X_16BIT) अणु
				u16 *data16 = skb_put(skb, len);
				ks8842_select_bank(adapter, 17);
				जबतक (len > 0) अणु
					*data16++ = ioपढ़ो16(adapter->hw_addr +
						REG_QMU_DATA_LO);
					*data16++ = ioपढ़ो16(adapter->hw_addr +
						REG_QMU_DATA_HI);
					len -= माप(u32);
				पूर्ण
			पूर्ण अन्यथा अणु
				u32 *data = skb_put(skb, len);

				ks8842_select_bank(adapter, 17);
				जबतक (len > 0) अणु
					*data++ = ioपढ़ो32(adapter->hw_addr +
						REG_QMU_DATA_LO);
					len -= माप(u32);
				पूर्ण
			पूर्ण
			skb->protocol = eth_type_trans(skb, netdev);
			netअगर_rx(skb);
		पूर्ण अन्यथा
			netdev->stats.rx_dropped++;
	पूर्ण अन्यथा
		ks8842_update_rx_err_counters(netdev, status);

	/* set high watermark to 3K */
	ks8842_clear_bits(adapter, 0, 1 << 12, REG_QRFCR);

	/* release the frame */
	ks8842_ग_लिखो16(adapter, 17, 0x01, REG_RXQCR);

	/* set high watermark to 2K */
	ks8842_enable_bits(adapter, 0, 1 << 12, REG_QRFCR);
पूर्ण

अटल व्योम ks8842_handle_rx(काष्ठा net_device *netdev,
	काष्ठा ks8842_adapter *adapter)
अणु
	u16 rx_data = ks8842_पढ़ो16(adapter, 16, REG_RXMIR) & 0x1fff;
	netdev_dbg(netdev, "%s Entry - rx_data: %d\n", __func__, rx_data);
	जबतक (rx_data) अणु
		ks8842_rx_frame(netdev, adapter);
		rx_data = ks8842_पढ़ो16(adapter, 16, REG_RXMIR) & 0x1fff;
	पूर्ण
पूर्ण

अटल व्योम ks8842_handle_tx(काष्ठा net_device *netdev,
	काष्ठा ks8842_adapter *adapter)
अणु
	u16 sr = ks8842_पढ़ो16(adapter, 16, REG_TXSR);
	netdev_dbg(netdev, "%s - entry, sr: %x\n", __func__, sr);
	netdev->stats.tx_packets++;
	अगर (netअगर_queue_stopped(netdev))
		netअगर_wake_queue(netdev);
पूर्ण

अटल व्योम ks8842_handle_rx_overrun(काष्ठा net_device *netdev,
	काष्ठा ks8842_adapter *adapter)
अणु
	netdev_dbg(netdev, "%s: entry\n", __func__);
	netdev->stats.rx_errors++;
	netdev->stats.rx_fअगरo_errors++;
पूर्ण

अटल व्योम ks8842_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ks8842_adapter *adapter = from_tasklet(adapter, t, tasklet);
	काष्ठा net_device *netdev = adapter->netdev;
	u16 isr;
	अचिन्हित दीर्घ flags;
	u16 entry_bank;

	/* पढ़ो current bank to be able to set it back */
	spin_lock_irqsave(&adapter->lock, flags);
	entry_bank = ioपढ़ो16(adapter->hw_addr + REG_SELECT_BANK);
	spin_unlock_irqrestore(&adapter->lock, flags);

	isr = ks8842_पढ़ो16(adapter, 18, REG_ISR);
	netdev_dbg(netdev, "%s - ISR: 0x%x\n", __func__, isr);

	/* when running in DMA mode, करो not ack RX पूर्णांकerrupts, it is handled
	   पूर्णांकernally by timberdale, otherwise it's DMA FIFO:s would stop
	*/
	अगर (KS8842_USE_DMA(adapter))
		isr &= ~IRQ_RX;

	/* Ack */
	ks8842_ग_लिखो16(adapter, 18, isr, REG_ISR);

	अगर (!(adapter->conf_flags & MICREL_KS884X))
		/* Ack in the timberdale IP as well */
		ioग_लिखो32(0x1, adapter->hw_addr + REG_TIMB_IAR);

	अगर (!netअगर_running(netdev))
		वापस;

	अगर (isr & IRQ_LINK_CHANGE)
		ks8842_update_link_status(netdev, adapter);

	/* should not get IRQ_RX when running DMA mode */
	अगर (isr & (IRQ_RX | IRQ_RX_ERROR) && !KS8842_USE_DMA(adapter))
		ks8842_handle_rx(netdev, adapter);

	/* should only happen when in PIO mode */
	अगर (isr & IRQ_TX)
		ks8842_handle_tx(netdev, adapter);

	अगर (isr & IRQ_RX_OVERRUN)
		ks8842_handle_rx_overrun(netdev, adapter);

	अगर (isr & IRQ_TX_STOPPED) अणु
		ks8842_disable_tx(adapter);
		ks8842_enable_tx(adapter);
	पूर्ण

	अगर (isr & IRQ_RX_STOPPED) अणु
		ks8842_disable_rx(adapter);
		ks8842_enable_rx(adapter);
	पूर्ण

	/* re-enable पूर्णांकerrupts, put back the bank selection रेजिस्टर */
	spin_lock_irqsave(&adapter->lock, flags);
	अगर (KS8842_USE_DMA(adapter))
		ks8842_ग_लिखो16(adapter, 18, ENABLED_IRQS_DMA, REG_IER);
	अन्यथा
		ks8842_ग_लिखो16(adapter, 18, ENABLED_IRQS, REG_IER);
	ioग_लिखो16(entry_bank, adapter->hw_addr + REG_SELECT_BANK);

	/* Make sure timberdale जारीs DMA operations, they are stopped जबतक
	   we are handling the ks8842 because we might change bank */
	अगर (KS8842_USE_DMA(adapter))
		ks8842_resume_dma(adapter);

	spin_unlock_irqrestore(&adapter->lock, flags);
पूर्ण

अटल irqवापस_t ks8842_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा net_device *netdev = devid;
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	u16 isr;
	u16 entry_bank = ioपढ़ो16(adapter->hw_addr + REG_SELECT_BANK);
	irqवापस_t ret = IRQ_NONE;

	isr = ks8842_पढ़ो16(adapter, 18, REG_ISR);
	netdev_dbg(netdev, "%s - ISR: 0x%x\n", __func__, isr);

	अगर (isr) अणु
		अगर (KS8842_USE_DMA(adapter))
			/* disable all but RX IRQ, since the FPGA relies on it*/
			ks8842_ग_लिखो16(adapter, 18, IRQ_RX, REG_IER);
		अन्यथा
			/* disable IRQ */
			ks8842_ग_लिखो16(adapter, 18, 0x00, REG_IER);

		/* schedule tasklet */
		tasklet_schedule(&adapter->tasklet);

		ret = IRQ_HANDLED;
	पूर्ण

	ioग_लिखो16(entry_bank, adapter->hw_addr + REG_SELECT_BANK);

	/* After an पूर्णांकerrupt, tell timberdale to जारी DMA operations.
	   DMA is disabled जबतक we are handling the ks8842 because we might
	   change bank */
	ks8842_resume_dma(adapter);

	वापस ret;
पूर्ण

अटल व्योम ks8842_dma_rx_cb(व्योम *data)
अणु
	काष्ठा net_device	*netdev = data;
	काष्ठा ks8842_adapter	*adapter = netdev_priv(netdev);

	netdev_dbg(netdev, "RX DMA finished\n");
	/* schedule tasklet */
	अगर (adapter->dma_rx.adesc)
		tasklet_schedule(&adapter->dma_rx.tasklet);
पूर्ण

अटल व्योम ks8842_dma_tx_cb(व्योम *data)
अणु
	काष्ठा net_device		*netdev = data;
	काष्ठा ks8842_adapter		*adapter = netdev_priv(netdev);
	काष्ठा ks8842_tx_dma_ctl	*ctl = &adapter->dma_tx;

	netdev_dbg(netdev, "TX DMA finished\n");

	अगर (!ctl->adesc)
		वापस;

	netdev->stats.tx_packets++;
	ctl->adesc = शून्य;

	अगर (netअगर_queue_stopped(netdev))
		netअगर_wake_queue(netdev);
पूर्ण

अटल व्योम ks8842_stop_dma(काष्ठा ks8842_adapter *adapter)
अणु
	काष्ठा ks8842_tx_dma_ctl *tx_ctl = &adapter->dma_tx;
	काष्ठा ks8842_rx_dma_ctl *rx_ctl = &adapter->dma_rx;

	tx_ctl->adesc = शून्य;
	अगर (tx_ctl->chan)
		dmaengine_terminate_all(tx_ctl->chan);

	rx_ctl->adesc = शून्य;
	अगर (rx_ctl->chan)
		dmaengine_terminate_all(rx_ctl->chan);

	अगर (sg_dma_address(&rx_ctl->sg))
		dma_unmap_single(adapter->dev, sg_dma_address(&rx_ctl->sg),
			DMA_BUFFER_SIZE, DMA_FROM_DEVICE);
	sg_dma_address(&rx_ctl->sg) = 0;

	dev_kमुक्त_skb(rx_ctl->skb);
	rx_ctl->skb = शून्य;
पूर्ण

अटल व्योम ks8842_dealloc_dma_bufs(काष्ठा ks8842_adapter *adapter)
अणु
	काष्ठा ks8842_tx_dma_ctl *tx_ctl = &adapter->dma_tx;
	काष्ठा ks8842_rx_dma_ctl *rx_ctl = &adapter->dma_rx;

	ks8842_stop_dma(adapter);

	अगर (tx_ctl->chan)
		dma_release_channel(tx_ctl->chan);
	tx_ctl->chan = शून्य;

	अगर (rx_ctl->chan)
		dma_release_channel(rx_ctl->chan);
	rx_ctl->chan = शून्य;

	tasklet_समाप्त(&rx_ctl->tasklet);

	अगर (sg_dma_address(&tx_ctl->sg))
		dma_unmap_single(adapter->dev, sg_dma_address(&tx_ctl->sg),
			DMA_BUFFER_SIZE, DMA_TO_DEVICE);
	sg_dma_address(&tx_ctl->sg) = 0;

	kमुक्त(tx_ctl->buf);
	tx_ctl->buf = शून्य;
पूर्ण

अटल bool ks8842_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *filter_param)
अणु
	वापस chan->chan_id == (दीर्घ)filter_param;
पूर्ण

अटल पूर्णांक ks8842_alloc_dma_bufs(काष्ठा net_device *netdev)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	काष्ठा ks8842_tx_dma_ctl *tx_ctl = &adapter->dma_tx;
	काष्ठा ks8842_rx_dma_ctl *rx_ctl = &adapter->dma_rx;
	पूर्णांक err;

	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	dma_cap_set(DMA_PRIVATE, mask);

	sg_init_table(&tx_ctl->sg, 1);

	tx_ctl->chan = dma_request_channel(mask, ks8842_dma_filter_fn,
					   (व्योम *)(दीर्घ)tx_ctl->channel);
	अगर (!tx_ctl->chan) अणु
		err = -ENODEV;
		जाओ err;
	पूर्ण

	/* allocate DMA buffer */
	tx_ctl->buf = kदो_स्मृति(DMA_BUFFER_SIZE, GFP_KERNEL);
	अगर (!tx_ctl->buf) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	sg_dma_address(&tx_ctl->sg) = dma_map_single(adapter->dev,
		tx_ctl->buf, DMA_BUFFER_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(adapter->dev, sg_dma_address(&tx_ctl->sg))) अणु
		err = -ENOMEM;
		sg_dma_address(&tx_ctl->sg) = 0;
		जाओ err;
	पूर्ण

	rx_ctl->chan = dma_request_channel(mask, ks8842_dma_filter_fn,
					   (व्योम *)(दीर्घ)rx_ctl->channel);
	अगर (!rx_ctl->chan) अणु
		err = -ENODEV;
		जाओ err;
	पूर्ण

	tasklet_setup(&rx_ctl->tasklet, ks8842_rx_frame_dma_tasklet);

	वापस 0;
err:
	ks8842_dealloc_dma_bufs(adapter);
	वापस err;
पूर्ण

/* Netdevice operations */

अटल पूर्णांक ks8842_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	netdev_dbg(netdev, "%s - entry\n", __func__);

	अगर (KS8842_USE_DMA(adapter)) अणु
		err = ks8842_alloc_dma_bufs(netdev);

		अगर (!err) अणु
			/* start RX dma */
			err = __ks8842_start_new_rx_dma(netdev);
			अगर (err)
				ks8842_dealloc_dma_bufs(adapter);
		पूर्ण

		अगर (err) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME
				": Failed to initiate DMA, running PIO\n");
			ks8842_dealloc_dma_bufs(adapter);
			adapter->dma_rx.channel = -1;
			adapter->dma_tx.channel = -1;
		पूर्ण
	पूर्ण

	/* reset the HW */
	ks8842_reset_hw(adapter);

	ks8842_ग_लिखो_mac_addr(adapter, netdev->dev_addr);

	ks8842_update_link_status(netdev, adapter);

	err = request_irq(adapter->irq, ks8842_irq, IRQF_SHARED, DRV_NAME,
		netdev);
	अगर (err) अणु
		pr_err("Failed to request IRQ: %d: %d\n", adapter->irq, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ks8842_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);

	netdev_dbg(netdev, "%s - entry\n", __func__);

	cancel_work_sync(&adapter->समयout_work);

	अगर (KS8842_USE_DMA(adapter))
		ks8842_dealloc_dma_bufs(adapter);

	/* मुक्त the irq */
	मुक्त_irq(adapter->irq, netdev);

	/* disable the चयन */
	ks8842_ग_लिखो16(adapter, 32, 0x0, REG_SW_ID_AND_ENABLE);

	वापस 0;
पूर्ण

अटल netdev_tx_t ks8842_xmit_frame(काष्ठा sk_buff *skb,
				     काष्ठा net_device *netdev)
अणु
	पूर्णांक ret;
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);

	netdev_dbg(netdev, "%s: entry\n", __func__);

	अगर (KS8842_USE_DMA(adapter)) अणु
		अचिन्हित दीर्घ flags;
		ret = ks8842_tx_frame_dma(skb, netdev);
		/* क्रम now only allow one transfer at the समय */
		spin_lock_irqsave(&adapter->lock, flags);
		अगर (adapter->dma_tx.adesc)
			netअगर_stop_queue(netdev);
		spin_unlock_irqrestore(&adapter->lock, flags);
		वापस ret;
	पूर्ण

	ret = ks8842_tx_frame(skb, netdev);

	अगर (ks8842_tx_fअगरo_space(adapter) <  netdev->mtu + 8)
		netअगर_stop_queue(netdev);

	वापस ret;
पूर्ण

अटल पूर्णांक ks8842_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;
	अक्षर *mac = (u8 *)addr->sa_data;

	netdev_dbg(netdev, "%s: entry\n", __func__);

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, mac, netdev->addr_len);

	ks8842_ग_लिखो_mac_addr(adapter, mac);
	वापस 0;
पूर्ण

अटल व्योम ks8842_tx_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ks8842_adapter *adapter =
		container_of(work, काष्ठा ks8842_adapter, समयout_work);
	काष्ठा net_device *netdev = adapter->netdev;
	अचिन्हित दीर्घ flags;

	netdev_dbg(netdev, "%s: entry\n", __func__);

	spin_lock_irqsave(&adapter->lock, flags);

	अगर (KS8842_USE_DMA(adapter))
		ks8842_stop_dma(adapter);

	/* disable पूर्णांकerrupts */
	ks8842_ग_लिखो16(adapter, 18, 0, REG_IER);
	ks8842_ग_लिखो16(adapter, 18, 0xFFFF, REG_ISR);

	netअगर_stop_queue(netdev);

	spin_unlock_irqrestore(&adapter->lock, flags);

	ks8842_reset_hw(adapter);

	ks8842_ग_लिखो_mac_addr(adapter, netdev->dev_addr);

	ks8842_update_link_status(netdev, adapter);

	अगर (KS8842_USE_DMA(adapter))
		__ks8842_start_new_rx_dma(netdev);
पूर्ण

अटल व्योम ks8842_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);

	netdev_dbg(netdev, "%s: entry\n", __func__);

	schedule_work(&adapter->समयout_work);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ks8842_netdev_ops = अणु
	.nकरो_खोलो		= ks8842_खोलो,
	.nकरो_stop		= ks8842_बंद,
	.nकरो_start_xmit		= ks8842_xmit_frame,
	.nकरो_set_mac_address	= ks8842_set_mac,
	.nकरो_tx_समयout 	= ks8842_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops ks8842_ethtool_ops = अणु
	.get_link		= ethtool_op_get_link,
पूर्ण;

अटल पूर्णांक ks8842_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा resource *iomem;
	काष्ठा net_device *netdev;
	काष्ठा ks8842_adapter *adapter;
	काष्ठा ks8842_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	u16 id;
	अचिन्हित i;

	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!request_mem_region(iomem->start, resource_size(iomem), DRV_NAME))
		जाओ err_mem_region;

	netdev = alloc_etherdev(माप(काष्ठा ks8842_adapter));
	अगर (!netdev)
		जाओ err_alloc_etherdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	INIT_WORK(&adapter->समयout_work, ks8842_tx_समयout_work);
	adapter->hw_addr = ioremap(iomem->start, resource_size(iomem));
	adapter->conf_flags = iomem->flags;

	अगर (!adapter->hw_addr)
		जाओ err_ioremap;

	adapter->irq = platक्रमm_get_irq(pdev, 0);
	अगर (adapter->irq < 0) अणु
		err = adapter->irq;
		जाओ err_get_irq;
	पूर्ण

	adapter->dev = (pdev->dev.parent) ? pdev->dev.parent : &pdev->dev;

	/* DMA is only supported when accessed via timberdale */
	अगर (!(adapter->conf_flags & MICREL_KS884X) && pdata &&
		(pdata->tx_dma_channel != -1) &&
		(pdata->rx_dma_channel != -1)) अणु
		adapter->dma_rx.channel = pdata->rx_dma_channel;
		adapter->dma_tx.channel = pdata->tx_dma_channel;
	पूर्ण अन्यथा अणु
		adapter->dma_rx.channel = -1;
		adapter->dma_tx.channel = -1;
	पूर्ण

	tasklet_setup(&adapter->tasklet, ks8842_tasklet);
	spin_lock_init(&adapter->lock);

	netdev->netdev_ops = &ks8842_netdev_ops;
	netdev->ethtool_ops = &ks8842_ethtool_ops;

	/* Check अगर a mac address was given */
	i = netdev->addr_len;
	अगर (pdata) अणु
		क्रम (i = 0; i < netdev->addr_len; i++)
			अगर (pdata->macaddr[i] != 0)
				अवरोध;

		अगर (i < netdev->addr_len)
			/* an address was passed, use it */
			स_नकल(netdev->dev_addr, pdata->macaddr,
				netdev->addr_len);
	पूर्ण

	अगर (i == netdev->addr_len) अणु
		ks8842_पढ़ो_mac_addr(adapter, netdev->dev_addr);

		अगर (!is_valid_ether_addr(netdev->dev_addr))
			eth_hw_addr_अक्रमom(netdev);
	पूर्ण

	id = ks8842_पढ़ो16(adapter, 32, REG_SW_ID_AND_ENABLE);

	म_नकल(netdev->name, "eth%d");
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	platक्रमm_set_drvdata(pdev, netdev);

	pr_info("Found chip, family: 0x%x, id: 0x%x, rev: 0x%x\n",
		(id >> 8) & 0xff, (id >> 4) & 0xf, (id >> 1) & 0x7);

	वापस 0;

err_रेजिस्टर:
err_get_irq:
	iounmap(adapter->hw_addr);
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	release_mem_region(iomem->start, resource_size(iomem));
err_mem_region:
	वापस err;
पूर्ण

अटल पूर्णांक ks8842_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *netdev = platक्रमm_get_drvdata(pdev);
	काष्ठा ks8842_adapter *adapter = netdev_priv(netdev);
	काष्ठा resource *iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	unरेजिस्टर_netdev(netdev);
	tasklet_समाप्त(&adapter->tasklet);
	iounmap(adapter->hw_addr);
	मुक्त_netdev(netdev);
	release_mem_region(iomem->start, resource_size(iomem));
	वापस 0;
पूर्ण


अटल काष्ठा platक्रमm_driver ks8842_platक्रमm_driver = अणु
	.driver = अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= ks8842_probe,
	.हटाओ		= ks8842_हटाओ,
पूर्ण;

module_platक्रमm_driver(ks8842_platक्रमm_driver);

MODULE_DESCRIPTION("Timberdale KS8842 ethernet driver");
MODULE_AUTHOR("Mocean Laboratories <info@mocean-labs.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ks8842");

