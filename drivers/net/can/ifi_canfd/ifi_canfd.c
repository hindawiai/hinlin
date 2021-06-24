<शैली गुरु>
/*
 * CAN bus driver क्रम IFI CANFD controller
 *
 * Copyright (C) 2016 Marek Vasut <marex@denx.de>
 *
 * Details about this controller can be found at
 * http://www.अगरi-pld.de/IP/CANFD/canfd.hपंचांगl
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/can/dev.h>

#घोषणा IFI_CANFD_STCMD				0x0
#घोषणा IFI_CANFD_STCMD_HARDRESET		0xDEADCAFD
#घोषणा IFI_CANFD_STCMD_ENABLE			BIT(0)
#घोषणा IFI_CANFD_STCMD_ERROR_ACTIVE		BIT(2)
#घोषणा IFI_CANFD_STCMD_ERROR_PASSIVE		BIT(3)
#घोषणा IFI_CANFD_STCMD_BUSOFF			BIT(4)
#घोषणा IFI_CANFD_STCMD_ERROR_WARNING		BIT(5)
#घोषणा IFI_CANFD_STCMD_BUSMONITOR		BIT(16)
#घोषणा IFI_CANFD_STCMD_LOOPBACK		BIT(18)
#घोषणा IFI_CANFD_STCMD_DISABLE_CANFD		BIT(24)
#घोषणा IFI_CANFD_STCMD_ENABLE_ISO		BIT(25)
#घोषणा IFI_CANFD_STCMD_ENABLE_7_9_8_8_TIMING	BIT(26)
#घोषणा IFI_CANFD_STCMD_NORMAL_MODE		((u32)BIT(31))

#घोषणा IFI_CANFD_RXSTCMD			0x4
#घोषणा IFI_CANFD_RXSTCMD_REMOVE_MSG		BIT(0)
#घोषणा IFI_CANFD_RXSTCMD_RESET			BIT(7)
#घोषणा IFI_CANFD_RXSTCMD_EMPTY			BIT(8)
#घोषणा IFI_CANFD_RXSTCMD_OVERFLOW		BIT(13)

#घोषणा IFI_CANFD_TXSTCMD			0x8
#घोषणा IFI_CANFD_TXSTCMD_ADD_MSG		BIT(0)
#घोषणा IFI_CANFD_TXSTCMD_HIGH_PRIO		BIT(1)
#घोषणा IFI_CANFD_TXSTCMD_RESET			BIT(7)
#घोषणा IFI_CANFD_TXSTCMD_EMPTY			BIT(8)
#घोषणा IFI_CANFD_TXSTCMD_FULL			BIT(12)
#घोषणा IFI_CANFD_TXSTCMD_OVERFLOW		BIT(13)

#घोषणा IFI_CANFD_INTERRUPT			0xc
#घोषणा IFI_CANFD_INTERRUPT_ERROR_BUSOFF	BIT(0)
#घोषणा IFI_CANFD_INTERRUPT_ERROR_WARNING	BIT(1)
#घोषणा IFI_CANFD_INTERRUPT_ERROR_STATE_CHG	BIT(2)
#घोषणा IFI_CANFD_INTERRUPT_ERROR_REC_TEC_INC	BIT(3)
#घोषणा IFI_CANFD_INTERRUPT_ERROR_COUNTER	BIT(10)
#घोषणा IFI_CANFD_INTERRUPT_TXFIFO_EMPTY	BIT(16)
#घोषणा IFI_CANFD_INTERRUPT_TXFIFO_REMOVE	BIT(22)
#घोषणा IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY	BIT(24)
#घोषणा IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY_PER	BIT(25)
#घोषणा IFI_CANFD_INTERRUPT_SET_IRQ		((u32)BIT(31))

#घोषणा IFI_CANFD_IRQMASK			0x10
#घोषणा IFI_CANFD_IRQMASK_ERROR_BUSOFF		BIT(0)
#घोषणा IFI_CANFD_IRQMASK_ERROR_WARNING		BIT(1)
#घोषणा IFI_CANFD_IRQMASK_ERROR_STATE_CHG	BIT(2)
#घोषणा IFI_CANFD_IRQMASK_ERROR_REC_TEC_INC	BIT(3)
#घोषणा IFI_CANFD_IRQMASK_SET_ERR		BIT(7)
#घोषणा IFI_CANFD_IRQMASK_SET_TS		BIT(15)
#घोषणा IFI_CANFD_IRQMASK_TXFIFO_EMPTY		BIT(16)
#घोषणा IFI_CANFD_IRQMASK_SET_TX		BIT(23)
#घोषणा IFI_CANFD_IRQMASK_RXFIFO_NEMPTY		BIT(24)
#घोषणा IFI_CANFD_IRQMASK_SET_RX		((u32)BIT(31))

#घोषणा IFI_CANFD_TIME				0x14
#घोषणा IFI_CANFD_FTIME				0x18
#घोषणा IFI_CANFD_TIME_TIMEB_OFF		0
#घोषणा IFI_CANFD_TIME_TIMEA_OFF		8
#घोषणा IFI_CANFD_TIME_PRESCALE_OFF		16
#घोषणा IFI_CANFD_TIME_SJW_OFF_7_9_8_8		25
#घोषणा IFI_CANFD_TIME_SJW_OFF_4_12_6_6		28
#घोषणा IFI_CANFD_TIME_SET_SJW_4_12_6_6		BIT(6)
#घोषणा IFI_CANFD_TIME_SET_TIMEB_4_12_6_6	BIT(7)
#घोषणा IFI_CANFD_TIME_SET_PRESC_4_12_6_6	BIT(14)
#घोषणा IFI_CANFD_TIME_SET_TIMEA_4_12_6_6	BIT(15)

#घोषणा IFI_CANFD_TDELAY			0x1c
#घोषणा IFI_CANFD_TDELAY_DEFAULT		0xb
#घोषणा IFI_CANFD_TDELAY_MASK			0x3fff
#घोषणा IFI_CANFD_TDELAY_ABS			BIT(14)
#घोषणा IFI_CANFD_TDELAY_EN			BIT(15)

#घोषणा IFI_CANFD_ERROR				0x20
#घोषणा IFI_CANFD_ERROR_TX_OFFSET		0
#घोषणा IFI_CANFD_ERROR_TX_MASK			0xff
#घोषणा IFI_CANFD_ERROR_RX_OFFSET		16
#घोषणा IFI_CANFD_ERROR_RX_MASK			0xff

#घोषणा IFI_CANFD_ERRCNT			0x24

#घोषणा IFI_CANFD_SUSPEND			0x28

#घोषणा IFI_CANFD_REPEAT			0x2c

#घोषणा IFI_CANFD_TRAFFIC			0x30

#घोषणा IFI_CANFD_TSCONTROL			0x34

#घोषणा IFI_CANFD_TSC				0x38

#घोषणा IFI_CANFD_TST				0x3c

#घोषणा IFI_CANFD_RES1				0x40

#घोषणा IFI_CANFD_ERROR_CTR			0x44
#घोषणा IFI_CANFD_ERROR_CTR_UNLOCK_MAGIC	0x21302899
#घोषणा IFI_CANFD_ERROR_CTR_OVERLOAD_FIRST	BIT(0)
#घोषणा IFI_CANFD_ERROR_CTR_ACK_ERROR_FIRST	BIT(1)
#घोषणा IFI_CANFD_ERROR_CTR_BIT0_ERROR_FIRST	BIT(2)
#घोषणा IFI_CANFD_ERROR_CTR_BIT1_ERROR_FIRST	BIT(3)
#घोषणा IFI_CANFD_ERROR_CTR_STUFF_ERROR_FIRST	BIT(4)
#घोषणा IFI_CANFD_ERROR_CTR_CRC_ERROR_FIRST	BIT(5)
#घोषणा IFI_CANFD_ERROR_CTR_FORM_ERROR_FIRST	BIT(6)
#घोषणा IFI_CANFD_ERROR_CTR_OVERLOAD_ALL	BIT(8)
#घोषणा IFI_CANFD_ERROR_CTR_ACK_ERROR_ALL	BIT(9)
#घोषणा IFI_CANFD_ERROR_CTR_BIT0_ERROR_ALL	BIT(10)
#घोषणा IFI_CANFD_ERROR_CTR_BIT1_ERROR_ALL	BIT(11)
#घोषणा IFI_CANFD_ERROR_CTR_STUFF_ERROR_ALL	BIT(12)
#घोषणा IFI_CANFD_ERROR_CTR_CRC_ERROR_ALL	BIT(13)
#घोषणा IFI_CANFD_ERROR_CTR_FORM_ERROR_ALL	BIT(14)
#घोषणा IFI_CANFD_ERROR_CTR_BITPOSITION_OFFSET	16
#घोषणा IFI_CANFD_ERROR_CTR_BITPOSITION_MASK	0xff
#घोषणा IFI_CANFD_ERROR_CTR_ER_RESET		BIT(30)
#घोषणा IFI_CANFD_ERROR_CTR_ER_ENABLE		((u32)BIT(31))

#घोषणा IFI_CANFD_PAR				0x48

#घोषणा IFI_CANFD_CANCLOCK			0x4c

#घोषणा IFI_CANFD_SYSCLOCK			0x50

#घोषणा IFI_CANFD_VER				0x54
#घोषणा IFI_CANFD_VER_REV_MASK			0xff
#घोषणा IFI_CANFD_VER_REV_MIN_SUPPORTED		0x15

#घोषणा IFI_CANFD_IP_ID				0x58
#घोषणा IFI_CANFD_IP_ID_VALUE			0xD073CAFD

#घोषणा IFI_CANFD_TEST				0x5c

#घोषणा IFI_CANFD_RXFIFO_TS_63_32		0x60

#घोषणा IFI_CANFD_RXFIFO_TS_31_0		0x64

#घोषणा IFI_CANFD_RXFIFO_DLC			0x68
#घोषणा IFI_CANFD_RXFIFO_DLC_DLC_OFFSET		0
#घोषणा IFI_CANFD_RXFIFO_DLC_DLC_MASK		0xf
#घोषणा IFI_CANFD_RXFIFO_DLC_RTR		BIT(4)
#घोषणा IFI_CANFD_RXFIFO_DLC_EDL		BIT(5)
#घोषणा IFI_CANFD_RXFIFO_DLC_BRS		BIT(6)
#घोषणा IFI_CANFD_RXFIFO_DLC_ESI		BIT(7)
#घोषणा IFI_CANFD_RXFIFO_DLC_OBJ_OFFSET		8
#घोषणा IFI_CANFD_RXFIFO_DLC_OBJ_MASK		0x1ff
#घोषणा IFI_CANFD_RXFIFO_DLC_FNR_OFFSET		24
#घोषणा IFI_CANFD_RXFIFO_DLC_FNR_MASK		0xff

#घोषणा IFI_CANFD_RXFIFO_ID			0x6c
#घोषणा IFI_CANFD_RXFIFO_ID_ID_OFFSET		0
#घोषणा IFI_CANFD_RXFIFO_ID_ID_STD_MASK		CAN_SFF_MASK
#घोषणा IFI_CANFD_RXFIFO_ID_ID_STD_OFFSET	0
#घोषणा IFI_CANFD_RXFIFO_ID_ID_STD_WIDTH	10
#घोषणा IFI_CANFD_RXFIFO_ID_ID_XTD_MASK		CAN_EFF_MASK
#घोषणा IFI_CANFD_RXFIFO_ID_ID_XTD_OFFSET	11
#घोषणा IFI_CANFD_RXFIFO_ID_ID_XTD_WIDTH	18
#घोषणा IFI_CANFD_RXFIFO_ID_IDE			BIT(29)

#घोषणा IFI_CANFD_RXFIFO_DATA			0x70	/* 0x70..0xac */

#घोषणा IFI_CANFD_TXFIFO_SUSPEND_US		0xb0

#घोषणा IFI_CANFD_TXFIFO_REPEATCOUNT		0xb4

#घोषणा IFI_CANFD_TXFIFO_DLC			0xb8
#घोषणा IFI_CANFD_TXFIFO_DLC_DLC_OFFSET		0
#घोषणा IFI_CANFD_TXFIFO_DLC_DLC_MASK		0xf
#घोषणा IFI_CANFD_TXFIFO_DLC_RTR		BIT(4)
#घोषणा IFI_CANFD_TXFIFO_DLC_EDL		BIT(5)
#घोषणा IFI_CANFD_TXFIFO_DLC_BRS		BIT(6)
#घोषणा IFI_CANFD_TXFIFO_DLC_FNR_OFFSET		24
#घोषणा IFI_CANFD_TXFIFO_DLC_FNR_MASK		0xff

#घोषणा IFI_CANFD_TXFIFO_ID			0xbc
#घोषणा IFI_CANFD_TXFIFO_ID_ID_OFFSET		0
#घोषणा IFI_CANFD_TXFIFO_ID_ID_STD_MASK		CAN_SFF_MASK
#घोषणा IFI_CANFD_TXFIFO_ID_ID_STD_OFFSET	0
#घोषणा IFI_CANFD_TXFIFO_ID_ID_STD_WIDTH	10
#घोषणा IFI_CANFD_TXFIFO_ID_ID_XTD_MASK		CAN_EFF_MASK
#घोषणा IFI_CANFD_TXFIFO_ID_ID_XTD_OFFSET	11
#घोषणा IFI_CANFD_TXFIFO_ID_ID_XTD_WIDTH	18
#घोषणा IFI_CANFD_TXFIFO_ID_IDE			BIT(29)

#घोषणा IFI_CANFD_TXFIFO_DATA			0xc0	/* 0xb0..0xfc */

#घोषणा IFI_CANFD_FILTER_MASK(n)		(0x800 + ((n) * 8) + 0)
#घोषणा IFI_CANFD_FILTER_MASK_EXT		BIT(29)
#घोषणा IFI_CANFD_FILTER_MASK_EDL		BIT(30)
#घोषणा IFI_CANFD_FILTER_MASK_VALID		((u32)BIT(31))

#घोषणा IFI_CANFD_FILTER_IDENT(n)		(0x800 + ((n) * 8) + 4)
#घोषणा IFI_CANFD_FILTER_IDENT_IDE		BIT(29)
#घोषणा IFI_CANFD_FILTER_IDENT_CANFD		BIT(30)
#घोषणा IFI_CANFD_FILTER_IDENT_VALID		((u32)BIT(31))

/* IFI CANFD निजी data काष्ठाure */
काष्ठा अगरi_canfd_priv अणु
	काष्ठा can_priv		can;	/* must be the first member */
	काष्ठा napi_काष्ठा	napi;
	काष्ठा net_device	*ndev;
	व्योम __iomem		*base;
पूर्ण;

अटल व्योम अगरi_canfd_irq_enable(काष्ठा net_device *ndev, bool enable)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	u32 enirq = 0;

	अगर (enable) अणु
		enirq = IFI_CANFD_IRQMASK_TXFIFO_EMPTY |
			IFI_CANFD_IRQMASK_RXFIFO_NEMPTY |
			IFI_CANFD_IRQMASK_ERROR_STATE_CHG |
			IFI_CANFD_IRQMASK_ERROR_WARNING |
			IFI_CANFD_IRQMASK_ERROR_BUSOFF;
		अगर (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
			enirq |= IFI_CANFD_INTERRUPT_ERROR_COUNTER;
	पूर्ण

	ग_लिखोl(IFI_CANFD_IRQMASK_SET_ERR |
	       IFI_CANFD_IRQMASK_SET_TS |
	       IFI_CANFD_IRQMASK_SET_TX |
	       IFI_CANFD_IRQMASK_SET_RX | enirq,
	       priv->base + IFI_CANFD_IRQMASK);
पूर्ण

अटल व्योम अगरi_canfd_पढ़ो_fअगरo(काष्ठा net_device *ndev)
अणु
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	काष्ठा canfd_frame *cf;
	काष्ठा sk_buff *skb;
	स्थिर u32 rx_irq_mask = IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY |
				IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY_PER;
	u32 rxdlc, rxid;
	u32 dlc, id;
	पूर्णांक i;

	rxdlc = पढ़ोl(priv->base + IFI_CANFD_RXFIFO_DLC);
	अगर (rxdlc & IFI_CANFD_RXFIFO_DLC_EDL)
		skb = alloc_canfd_skb(ndev, &cf);
	अन्यथा
		skb = alloc_can_skb(ndev, (काष्ठा can_frame **)&cf);

	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	dlc = (rxdlc >> IFI_CANFD_RXFIFO_DLC_DLC_OFFSET) &
	      IFI_CANFD_RXFIFO_DLC_DLC_MASK;
	अगर (rxdlc & IFI_CANFD_RXFIFO_DLC_EDL)
		cf->len = can_fd_dlc2len(dlc);
	अन्यथा
		cf->len = can_cc_dlc2len(dlc);

	rxid = पढ़ोl(priv->base + IFI_CANFD_RXFIFO_ID);
	id = (rxid >> IFI_CANFD_RXFIFO_ID_ID_OFFSET);
	अगर (id & IFI_CANFD_RXFIFO_ID_IDE) अणु
		id &= IFI_CANFD_RXFIFO_ID_ID_XTD_MASK;
		/*
		 * In हाल the Extended ID frame is received, the standard
		 * and extended part of the ID are swapped in the रेजिस्टर,
		 * so swap them back to obtain the correct ID.
		 */
		id = (id >> IFI_CANFD_RXFIFO_ID_ID_XTD_OFFSET) |
		     ((id & IFI_CANFD_RXFIFO_ID_ID_STD_MASK) <<
		       IFI_CANFD_RXFIFO_ID_ID_XTD_WIDTH);
		id |= CAN_EFF_FLAG;
	पूर्ण अन्यथा अणु
		id &= IFI_CANFD_RXFIFO_ID_ID_STD_MASK;
	पूर्ण
	cf->can_id = id;

	अगर (rxdlc & IFI_CANFD_RXFIFO_DLC_ESI) अणु
		cf->flags |= CANFD_ESI;
		netdev_dbg(ndev, "ESI Error\n");
	पूर्ण

	अगर (!(rxdlc & IFI_CANFD_RXFIFO_DLC_EDL) &&
	    (rxdlc & IFI_CANFD_RXFIFO_DLC_RTR)) अणु
		cf->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		अगर (rxdlc & IFI_CANFD_RXFIFO_DLC_BRS)
			cf->flags |= CANFD_BRS;

		क्रम (i = 0; i < cf->len; i += 4) अणु
			*(u32 *)(cf->data + i) =
				पढ़ोl(priv->base + IFI_CANFD_RXFIFO_DATA + i);
		पूर्ण
	पूर्ण

	/* Remove the packet from FIFO */
	ग_लिखोl(IFI_CANFD_RXSTCMD_REMOVE_MSG, priv->base + IFI_CANFD_RXSTCMD);
	ग_लिखोl(rx_irq_mask, priv->base + IFI_CANFD_INTERRUPT);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक अगरi_canfd_करो_rx_poll(काष्ठा net_device *ndev, पूर्णांक quota)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	u32 pkts = 0;
	u32 rxst;

	rxst = पढ़ोl(priv->base + IFI_CANFD_RXSTCMD);
	अगर (rxst & IFI_CANFD_RXSTCMD_EMPTY) अणु
		netdev_dbg(ndev, "No messages in RX FIFO\n");
		वापस 0;
	पूर्ण

	क्रम (;;) अणु
		अगर (rxst & IFI_CANFD_RXSTCMD_EMPTY)
			अवरोध;
		अगर (quota <= 0)
			अवरोध;

		अगरi_canfd_पढ़ो_fअगरo(ndev);
		quota--;
		pkts++;
		rxst = पढ़ोl(priv->base + IFI_CANFD_RXSTCMD);
	पूर्ण

	अगर (pkts)
		can_led_event(ndev, CAN_LED_EVENT_RX);

	वापस pkts;
पूर्ण

अटल पूर्णांक अगरi_canfd_handle_lost_msg(काष्ठा net_device *ndev)
अणु
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *frame;

	netdev_err(ndev, "RX FIFO overflow, message(s) lost.\n");

	stats->rx_errors++;
	stats->rx_over_errors++;

	skb = alloc_can_err_skb(ndev, &frame);
	अगर (unlikely(!skb))
		वापस 0;

	frame->can_id |= CAN_ERR_CRTL;
	frame->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	netअगर_receive_skb(skb);

	वापस 1;
पूर्ण

अटल पूर्णांक अगरi_canfd_handle_lec_err(काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 errctr = पढ़ोl(priv->base + IFI_CANFD_ERROR_CTR);
	स्थिर u32 errmask = IFI_CANFD_ERROR_CTR_OVERLOAD_FIRST |
			    IFI_CANFD_ERROR_CTR_ACK_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_BIT0_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_BIT1_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_STUFF_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_CRC_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_FORM_ERROR_FIRST;

	अगर (!(errctr & errmask))	/* No error happened. */
		वापस 0;

	priv->can.can_stats.bus_error++;
	stats->rx_errors++;

	/* Propagate the error condition to the CAN stack. */
	skb = alloc_can_err_skb(ndev, &cf);
	अगर (unlikely(!skb))
		वापस 0;

	/* Read the error counter रेजिस्टर and check क्रम new errors. */
	cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

	अगर (errctr & IFI_CANFD_ERROR_CTR_OVERLOAD_FIRST)
		cf->data[2] |= CAN_ERR_PROT_OVERLOAD;

	अगर (errctr & IFI_CANFD_ERROR_CTR_ACK_ERROR_FIRST)
		cf->data[3] = CAN_ERR_PROT_LOC_ACK;

	अगर (errctr & IFI_CANFD_ERROR_CTR_BIT0_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_BIT0;

	अगर (errctr & IFI_CANFD_ERROR_CTR_BIT1_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_BIT1;

	अगर (errctr & IFI_CANFD_ERROR_CTR_STUFF_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_STUFF;

	अगर (errctr & IFI_CANFD_ERROR_CTR_CRC_ERROR_FIRST)
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;

	अगर (errctr & IFI_CANFD_ERROR_CTR_FORM_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_FORM;

	/* Reset the error counter, ack the IRQ and re-enable the counter. */
	ग_लिखोl(IFI_CANFD_ERROR_CTR_ER_RESET, priv->base + IFI_CANFD_ERROR_CTR);
	ग_लिखोl(IFI_CANFD_INTERRUPT_ERROR_COUNTER,
	       priv->base + IFI_CANFD_INTERRUPT);
	ग_लिखोl(IFI_CANFD_ERROR_CTR_ER_ENABLE, priv->base + IFI_CANFD_ERROR_CTR);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_receive_skb(skb);

	वापस 1;
पूर्ण

अटल पूर्णांक अगरi_canfd_get_berr_counter(स्थिर काष्ठा net_device *ndev,
				      काष्ठा can_berr_counter *bec)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	u32 err;

	err = पढ़ोl(priv->base + IFI_CANFD_ERROR);
	bec->rxerr = (err >> IFI_CANFD_ERROR_RX_OFFSET) &
		     IFI_CANFD_ERROR_RX_MASK;
	bec->txerr = (err >> IFI_CANFD_ERROR_TX_OFFSET) &
		     IFI_CANFD_ERROR_TX_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक अगरi_canfd_handle_state_change(काष्ठा net_device *ndev,
					 क्रमागत can_state new_state)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा can_berr_counter bec;

	चयन (new_state) अणु
	हाल CAN_STATE_ERROR_ACTIVE:
		/* error active state */
		priv->can.can_stats.error_warning++;
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		अवरोध;
	हाल CAN_STATE_ERROR_WARNING:
		/* error warning state */
		priv->can.can_stats.error_warning++;
		priv->can.state = CAN_STATE_ERROR_WARNING;
		अवरोध;
	हाल CAN_STATE_ERROR_PASSIVE:
		/* error passive state */
		priv->can.can_stats.error_passive++;
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		अवरोध;
	हाल CAN_STATE_BUS_OFF:
		/* bus-off state */
		priv->can.state = CAN_STATE_BUS_OFF;
		अगरi_canfd_irq_enable(ndev, 0);
		priv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(ndev, &cf);
	अगर (unlikely(!skb))
		वापस 0;

	अगरi_canfd_get_berr_counter(ndev, &bec);

	चयन (new_state) अणु
	हाल CAN_STATE_ERROR_WARNING:
		/* error warning state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = (bec.txerr > bec.rxerr) ?
			CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		अवरोध;
	हाल CAN_STATE_ERROR_PASSIVE:
		/* error passive state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		अगर (bec.txerr > 127)
			cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		अवरोध;
	हाल CAN_STATE_BUS_OFF:
		/* bus-off state */
		cf->can_id |= CAN_ERR_BUSOFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_receive_skb(skb);

	वापस 1;
पूर्ण

अटल पूर्णांक अगरi_canfd_handle_state_errors(काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	u32 stcmd = पढ़ोl(priv->base + IFI_CANFD_STCMD);
	पूर्णांक work_करोne = 0;

	अगर ((stcmd & IFI_CANFD_STCMD_ERROR_ACTIVE) &&
	    (priv->can.state != CAN_STATE_ERROR_ACTIVE)) अणु
		netdev_dbg(ndev, "Error, entered active state\n");
		work_करोne += अगरi_canfd_handle_state_change(ndev,
						CAN_STATE_ERROR_ACTIVE);
	पूर्ण

	अगर ((stcmd & IFI_CANFD_STCMD_ERROR_WARNING) &&
	    (priv->can.state != CAN_STATE_ERROR_WARNING)) अणु
		netdev_dbg(ndev, "Error, entered warning state\n");
		work_करोne += अगरi_canfd_handle_state_change(ndev,
						CAN_STATE_ERROR_WARNING);
	पूर्ण

	अगर ((stcmd & IFI_CANFD_STCMD_ERROR_PASSIVE) &&
	    (priv->can.state != CAN_STATE_ERROR_PASSIVE)) अणु
		netdev_dbg(ndev, "Error, entered passive state\n");
		work_करोne += अगरi_canfd_handle_state_change(ndev,
						CAN_STATE_ERROR_PASSIVE);
	पूर्ण

	अगर ((stcmd & IFI_CANFD_STCMD_BUSOFF) &&
	    (priv->can.state != CAN_STATE_BUS_OFF)) अणु
		netdev_dbg(ndev, "Error, entered bus-off state\n");
		work_करोne += अगरi_canfd_handle_state_change(ndev,
						CAN_STATE_BUS_OFF);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक अगरi_canfd_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	u32 rxstcmd = पढ़ोl(priv->base + IFI_CANFD_RXSTCMD);
	पूर्णांक work_करोne = 0;

	/* Handle bus state changes */
	work_करोne += अगरi_canfd_handle_state_errors(ndev);

	/* Handle lost messages on RX */
	अगर (rxstcmd & IFI_CANFD_RXSTCMD_OVERFLOW)
		work_करोne += अगरi_canfd_handle_lost_msg(ndev);

	/* Handle lec errors on the bus */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
		work_करोne += अगरi_canfd_handle_lec_err(ndev);

	/* Handle normal messages on RX */
	अगर (!(rxstcmd & IFI_CANFD_RXSTCMD_EMPTY))
		work_करोne += अगरi_canfd_करो_rx_poll(ndev, quota - work_करोne);

	अगर (work_करोne < quota) अणु
		napi_complete_करोne(napi, work_करोne);
		अगरi_canfd_irq_enable(ndev, 1);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल irqवापस_t अगरi_canfd_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)dev_id;
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	स्थिर u32 rx_irq_mask = IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY |
				IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY_PER |
				IFI_CANFD_INTERRUPT_ERROR_COUNTER |
				IFI_CANFD_INTERRUPT_ERROR_STATE_CHG |
				IFI_CANFD_INTERRUPT_ERROR_WARNING |
				IFI_CANFD_INTERRUPT_ERROR_BUSOFF;
	स्थिर u32 tx_irq_mask = IFI_CANFD_INTERRUPT_TXFIFO_EMPTY |
				IFI_CANFD_INTERRUPT_TXFIFO_REMOVE;
	स्थिर u32 clr_irq_mask = ~((u32)IFI_CANFD_INTERRUPT_SET_IRQ);
	u32 isr;

	isr = पढ़ोl(priv->base + IFI_CANFD_INTERRUPT);

	/* No पूर्णांकerrupt */
	अगर (isr == 0)
		वापस IRQ_NONE;

	/* Clear all pending पूर्णांकerrupts but ErrWarn */
	ग_लिखोl(clr_irq_mask, priv->base + IFI_CANFD_INTERRUPT);

	/* RX IRQ or bus warning, start NAPI */
	अगर (isr & rx_irq_mask) अणु
		अगरi_canfd_irq_enable(ndev, 0);
		napi_schedule(&priv->napi);
	पूर्ण

	/* TX IRQ */
	अगर (isr & IFI_CANFD_INTERRUPT_TXFIFO_REMOVE) अणु
		stats->tx_bytes += can_get_echo_skb(ndev, 0, शून्य);
		stats->tx_packets++;
		can_led_event(ndev, CAN_LED_EVENT_TX);
	पूर्ण

	अगर (isr & tx_irq_mask)
		netअगर_wake_queue(ndev);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा can_bittiming_स्थिर अगरi_canfd_bittiming_स्थिर = अणु
	.name		= KBUILD_MODNAME,
	.tseg1_min	= 1,	/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max	= 256,
	.tseg2_min	= 2,	/* Time segment 2 = phase_seg2 */
	.tseg2_max	= 256,
	.sjw_max	= 128,
	.brp_min	= 2,
	.brp_max	= 512,
	.brp_inc	= 1,
पूर्ण;

अटल व्योम अगरi_canfd_set_bittiming(काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	स्थिर काष्ठा can_bittiming *bt = &priv->can.bittiming;
	स्थिर काष्ठा can_bittiming *dbt = &priv->can.data_bittiming;
	u16 brp, sjw, tseg1, tseg2, tdc;

	/* Configure bit timing */
	brp = bt->brp - 2;
	sjw = bt->sjw - 1;
	tseg1 = bt->prop_seg + bt->phase_seg1 - 1;
	tseg2 = bt->phase_seg2 - 2;
	ग_लिखोl((tseg2 << IFI_CANFD_TIME_TIMEB_OFF) |
	       (tseg1 << IFI_CANFD_TIME_TIMEA_OFF) |
	       (brp << IFI_CANFD_TIME_PRESCALE_OFF) |
	       (sjw << IFI_CANFD_TIME_SJW_OFF_7_9_8_8),
	       priv->base + IFI_CANFD_TIME);

	/* Configure data bit timing */
	brp = dbt->brp - 2;
	sjw = dbt->sjw - 1;
	tseg1 = dbt->prop_seg + dbt->phase_seg1 - 1;
	tseg2 = dbt->phase_seg2 - 2;
	ग_लिखोl((tseg2 << IFI_CANFD_TIME_TIMEB_OFF) |
	       (tseg1 << IFI_CANFD_TIME_TIMEA_OFF) |
	       (brp << IFI_CANFD_TIME_PRESCALE_OFF) |
	       (sjw << IFI_CANFD_TIME_SJW_OFF_7_9_8_8),
	       priv->base + IFI_CANFD_FTIME);

	/* Configure transmitter delay */
	tdc = dbt->brp * (dbt->prop_seg + dbt->phase_seg1);
	tdc &= IFI_CANFD_TDELAY_MASK;
	ग_लिखोl(IFI_CANFD_TDELAY_EN | tdc, priv->base + IFI_CANFD_TDELAY);
पूर्ण

अटल व्योम अगरi_canfd_set_filter(काष्ठा net_device *ndev, स्थिर u32 id,
				 स्थिर u32 mask, स्थिर u32 ident)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);

	ग_लिखोl(mask, priv->base + IFI_CANFD_FILTER_MASK(id));
	ग_लिखोl(ident, priv->base + IFI_CANFD_FILTER_IDENT(id));
पूर्ण

अटल व्योम अगरi_canfd_set_filters(काष्ठा net_device *ndev)
अणु
	/* Receive all CAN frames (standard ID) */
	अगरi_canfd_set_filter(ndev, 0,
			     IFI_CANFD_FILTER_MASK_VALID |
			     IFI_CANFD_FILTER_MASK_EXT,
			     IFI_CANFD_FILTER_IDENT_VALID);

	/* Receive all CAN frames (extended ID) */
	अगरi_canfd_set_filter(ndev, 1,
			     IFI_CANFD_FILTER_MASK_VALID |
			     IFI_CANFD_FILTER_MASK_EXT,
			     IFI_CANFD_FILTER_IDENT_VALID |
			     IFI_CANFD_FILTER_IDENT_IDE);

	/* Receive all CANFD frames */
	अगरi_canfd_set_filter(ndev, 2,
			     IFI_CANFD_FILTER_MASK_VALID |
			     IFI_CANFD_FILTER_MASK_EDL |
			     IFI_CANFD_FILTER_MASK_EXT,
			     IFI_CANFD_FILTER_IDENT_VALID |
			     IFI_CANFD_FILTER_IDENT_CANFD |
			     IFI_CANFD_FILTER_IDENT_IDE);
पूर्ण

अटल व्योम अगरi_canfd_start(काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	u32 stcmd;

	/* Reset the IP */
	ग_लिखोl(IFI_CANFD_STCMD_HARDRESET, priv->base + IFI_CANFD_STCMD);
	ग_लिखोl(IFI_CANFD_STCMD_ENABLE_7_9_8_8_TIMING,
	       priv->base + IFI_CANFD_STCMD);

	अगरi_canfd_set_bittiming(ndev);
	अगरi_canfd_set_filters(ndev);

	/* Reset FIFOs */
	ग_लिखोl(IFI_CANFD_RXSTCMD_RESET, priv->base + IFI_CANFD_RXSTCMD);
	ग_लिखोl(0, priv->base + IFI_CANFD_RXSTCMD);
	ग_लिखोl(IFI_CANFD_TXSTCMD_RESET, priv->base + IFI_CANFD_TXSTCMD);
	ग_लिखोl(0, priv->base + IFI_CANFD_TXSTCMD);

	/* Repeat transmission until successful */
	ग_लिखोl(0, priv->base + IFI_CANFD_REPEAT);
	ग_लिखोl(0, priv->base + IFI_CANFD_SUSPEND);

	/* Clear all pending पूर्णांकerrupts */
	ग_लिखोl((u32)(~IFI_CANFD_INTERRUPT_SET_IRQ),
	       priv->base + IFI_CANFD_INTERRUPT);

	stcmd = IFI_CANFD_STCMD_ENABLE | IFI_CANFD_STCMD_NORMAL_MODE |
		IFI_CANFD_STCMD_ENABLE_7_9_8_8_TIMING;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		stcmd |= IFI_CANFD_STCMD_BUSMONITOR;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		stcmd |= IFI_CANFD_STCMD_LOOPBACK;

	अगर ((priv->can.ctrlmode & CAN_CTRLMODE_FD) &&
	    !(priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO))
		stcmd |= IFI_CANFD_STCMD_ENABLE_ISO;

	अगर (!(priv->can.ctrlmode & CAN_CTRLMODE_FD))
		stcmd |= IFI_CANFD_STCMD_DISABLE_CANFD;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	अगरi_canfd_irq_enable(ndev, 1);

	/* Unlock, reset and enable the error counter. */
	ग_लिखोl(IFI_CANFD_ERROR_CTR_UNLOCK_MAGIC,
	       priv->base + IFI_CANFD_ERROR_CTR);
	ग_लिखोl(IFI_CANFD_ERROR_CTR_ER_RESET, priv->base + IFI_CANFD_ERROR_CTR);
	ग_लिखोl(IFI_CANFD_ERROR_CTR_ER_ENABLE, priv->base + IFI_CANFD_ERROR_CTR);

	/* Enable controller */
	ग_लिखोl(stcmd, priv->base + IFI_CANFD_STCMD);
पूर्ण

अटल व्योम अगरi_canfd_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);

	/* Reset and disable the error counter. */
	ग_लिखोl(IFI_CANFD_ERROR_CTR_ER_RESET, priv->base + IFI_CANFD_ERROR_CTR);
	ग_लिखोl(0, priv->base + IFI_CANFD_ERROR_CTR);

	/* Reset the IP */
	ग_लिखोl(IFI_CANFD_STCMD_HARDRESET, priv->base + IFI_CANFD_STCMD);

	/* Mask all पूर्णांकerrupts */
	ग_लिखोl(~0, priv->base + IFI_CANFD_IRQMASK);

	/* Clear all pending पूर्णांकerrupts */
	ग_लिखोl((u32)(~IFI_CANFD_INTERRUPT_SET_IRQ),
	       priv->base + IFI_CANFD_INTERRUPT);

	/* Set the state as STOPPED */
	priv->can.state = CAN_STATE_STOPPED;
पूर्ण

अटल पूर्णांक अगरi_canfd_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	चयन (mode) अणु
	हाल CAN_MODE_START:
		अगरi_canfd_start(ndev);
		netअगर_wake_queue(ndev);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक अगरi_canfd_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	ret = खोलो_candev(ndev);
	अगर (ret) अणु
		netdev_err(ndev, "Failed to open CAN device\n");
		वापस ret;
	पूर्ण

	/* Register पूर्णांकerrupt handler */
	ret = request_irq(ndev->irq, अगरi_canfd_isr, IRQF_SHARED,
			  ndev->name, ndev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "Failed to request interrupt\n");
		जाओ err_irq;
	पूर्ण

	अगरi_canfd_start(ndev);

	can_led_event(ndev, CAN_LED_EVENT_OPEN);
	napi_enable(&priv->napi);
	netअगर_start_queue(ndev);

	वापस 0;
err_irq:
	बंद_candev(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक अगरi_canfd_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);

	अगरi_canfd_stop(ndev);

	मुक्त_irq(ndev->irq, ndev);

	बंद_candev(ndev);

	can_led_event(ndev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल netdev_tx_t अगरi_canfd_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *ndev)
अणु
	काष्ठा अगरi_canfd_priv *priv = netdev_priv(ndev);
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;
	u32 txst, txid, txdlc;
	पूर्णांक i;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	/* Check अगर the TX buffer is full */
	txst = पढ़ोl(priv->base + IFI_CANFD_TXSTCMD);
	अगर (txst & IFI_CANFD_TXSTCMD_FULL) अणु
		netअगर_stop_queue(ndev);
		netdev_err(ndev, "BUG! TX FIFO full when queue awake!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	netअगर_stop_queue(ndev);

	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		txid = cf->can_id & CAN_EFF_MASK;
		/*
		 * In हाल the Extended ID frame is transmitted, the
		 * standard and extended part of the ID are swapped
		 * in the रेजिस्टर, so swap them back to send the
		 * correct ID.
		 */
		txid = (txid >> IFI_CANFD_TXFIFO_ID_ID_XTD_WIDTH) |
		       ((txid & IFI_CANFD_TXFIFO_ID_ID_XTD_MASK) <<
		         IFI_CANFD_TXFIFO_ID_ID_XTD_OFFSET);
		txid |= IFI_CANFD_TXFIFO_ID_IDE;
	पूर्ण अन्यथा अणु
		txid = cf->can_id & CAN_SFF_MASK;
	पूर्ण

	txdlc = can_fd_len2dlc(cf->len);
	अगर ((priv->can.ctrlmode & CAN_CTRLMODE_FD) && can_is_canfd_skb(skb)) अणु
		txdlc |= IFI_CANFD_TXFIFO_DLC_EDL;
		अगर (cf->flags & CANFD_BRS)
			txdlc |= IFI_CANFD_TXFIFO_DLC_BRS;
	पूर्ण

	अगर (cf->can_id & CAN_RTR_FLAG)
		txdlc |= IFI_CANFD_TXFIFO_DLC_RTR;

	/* message ram configuration */
	ग_लिखोl(txid, priv->base + IFI_CANFD_TXFIFO_ID);
	ग_लिखोl(txdlc, priv->base + IFI_CANFD_TXFIFO_DLC);

	क्रम (i = 0; i < cf->len; i += 4) अणु
		ग_लिखोl(*(u32 *)(cf->data + i),
		       priv->base + IFI_CANFD_TXFIFO_DATA + i);
	पूर्ण

	ग_लिखोl(0, priv->base + IFI_CANFD_TXFIFO_REPEATCOUNT);
	ग_लिखोl(0, priv->base + IFI_CANFD_TXFIFO_SUSPEND_US);

	can_put_echo_skb(skb, ndev, 0, 0);

	/* Start the transmission */
	ग_लिखोl(IFI_CANFD_TXSTCMD_ADD_MSG, priv->base + IFI_CANFD_TXSTCMD);

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops अगरi_canfd_netdev_ops = अणु
	.nकरो_खोलो	= अगरi_canfd_खोलो,
	.nकरो_stop	= अगरi_canfd_बंद,
	.nकरो_start_xmit	= अगरi_canfd_start_xmit,
	.nकरो_change_mtu	= can_change_mtu,
पूर्ण;

अटल पूर्णांक अगरi_canfd_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *ndev;
	काष्ठा अगरi_canfd_priv *priv;
	व्योम __iomem *addr;
	पूर्णांक irq, ret;
	u32 id, rev;

	addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	id = पढ़ोl(addr + IFI_CANFD_IP_ID);
	अगर (id != IFI_CANFD_IP_ID_VALUE) अणु
		dev_err(dev, "This block is not IFI CANFD, id=%08x\n", id);
		वापस -EINVAL;
	पूर्ण

	rev = पढ़ोl(addr + IFI_CANFD_VER) & IFI_CANFD_VER_REV_MASK;
	अगर (rev < IFI_CANFD_VER_REV_MIN_SUPPORTED) अणु
		dev_err(dev, "This block is too old (rev %i), minimum supported is rev %i\n",
			rev, IFI_CANFD_VER_REV_MIN_SUPPORTED);
		वापस -EINVAL;
	पूर्ण

	ndev = alloc_candev(माप(*priv), 1);
	अगर (!ndev)
		वापस -ENOMEM;

	ndev->irq = irq;
	ndev->flags |= IFF_ECHO;	/* we support local echo */
	ndev->netdev_ops = &अगरi_canfd_netdev_ops;

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->base = addr;

	netअगर_napi_add(ndev, &priv->napi, अगरi_canfd_poll, 64);

	priv->can.state = CAN_STATE_STOPPED;

	priv->can.घड़ी.freq = पढ़ोl(addr + IFI_CANFD_CANCLOCK);

	priv->can.bittiming_स्थिर	= &अगरi_canfd_bittiming_स्थिर;
	priv->can.data_bittiming_स्थिर	= &अगरi_canfd_bittiming_स्थिर;
	priv->can.करो_set_mode		= अगरi_canfd_set_mode;
	priv->can.करो_get_berr_counter	= अगरi_canfd_get_berr_counter;

	/* IFI CANFD can करो both Bosch FD and ISO FD */
	priv->can.ctrlmode = CAN_CTRLMODE_FD;

	/* IFI CANFD can करो both Bosch FD and ISO FD */
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
				       CAN_CTRLMODE_LISTENONLY |
				       CAN_CTRLMODE_FD |
				       CAN_CTRLMODE_FD_NON_ISO |
				       CAN_CTRLMODE_BERR_REPORTING;

	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);

	ret = रेजिस्टर_candev(ndev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register (ret=%d)\n", ret);
		जाओ err_reg;
	पूर्ण

	devm_can_led_init(ndev);

	dev_info(dev, "Driver registered: regs=%p, irq=%d, clock=%d\n",
		 priv->base, ndev->irq, priv->can.घड़ी.freq);

	वापस 0;

err_reg:
	मुक्त_candev(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक अगरi_canfd_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_candev(ndev);
	platक्रमm_set_drvdata(pdev, शून्य);
	मुक्त_candev(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id अगरi_canfd_of_table[] = अणु
	अणु .compatible = "ifi,canfd-1.0", .data = शून्य पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, अगरi_canfd_of_table);

अटल काष्ठा platक्रमm_driver अगरi_canfd_plat_driver = अणु
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= अगरi_canfd_of_table,
	पूर्ण,
	.probe	= अगरi_canfd_plat_probe,
	.हटाओ	= अगरi_canfd_plat_हटाओ,
पूर्ण;

module_platक्रमm_driver(अगरi_canfd_plat_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CAN bus driver for IFI CANFD controller");
