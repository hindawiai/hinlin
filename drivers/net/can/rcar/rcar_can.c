<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Renesas R-Car CAN device driver
 *
 * Copyright (C) 2013 Cogent Embedded, Inc. <source@cogentembedded.com>
 * Copyright (C) 2013 Renesas Solutions Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/can/led.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>

#घोषणा RCAR_CAN_DRV_NAME	"rcar_can"

/* Clock Select Register settings */
क्रमागत CLKR अणु
	CLKR_CLKP1 = 0, /* Peripheral घड़ी (clkp1) */
	CLKR_CLKP2 = 1, /* Peripheral घड़ी (clkp2) */
	CLKR_CLKEXT = 3, /* Externally input घड़ी */
पूर्ण;

#घोषणा RCAR_SUPPORTED_CLOCKS	(BIT(CLKR_CLKP1) | BIT(CLKR_CLKP2) | \
				 BIT(CLKR_CLKEXT))

/* Mailbox configuration:
 * mailbox 60 - 63 - Rx FIFO mailboxes
 * mailbox 56 - 59 - Tx FIFO mailboxes
 * non-FIFO mailboxes are not used
 */
#घोषणा RCAR_CAN_N_MBX		64 /* Number of mailboxes in non-FIFO mode */
#घोषणा RCAR_CAN_RX_FIFO_MBX	60 /* Mailbox - winकरोw to Rx FIFO */
#घोषणा RCAR_CAN_TX_FIFO_MBX	56 /* Mailbox - winकरोw to Tx FIFO */
#घोषणा RCAR_CAN_FIFO_DEPTH	4

/* Mailbox रेजिस्टरs काष्ठाure */
काष्ठा rcar_can_mbox_regs अणु
	u32 id;		/* IDE and RTR bits, SID and EID */
	u8 stub;	/* Not used */
	u8 dlc;		/* Data Length Code - bits [0..3] */
	u8 data[8];	/* Data Bytes */
	u8 tsh;		/* Time Stamp Higher Byte */
	u8 tsl;		/* Time Stamp Lower Byte */
पूर्ण;

काष्ठा rcar_can_regs अणु
	काष्ठा rcar_can_mbox_regs mb[RCAR_CAN_N_MBX]; /* Mailbox रेजिस्टरs */
	u32 mkr_2_9[8];	/* Mask Registers 2-9 */
	u32 fidcr[2];	/* FIFO Received ID Compare Register */
	u32 mkivlr1;	/* Mask Invalid Register 1 */
	u32 mier1;	/* Mailbox Interrupt Enable Register 1 */
	u32 mkr_0_1[2];	/* Mask Registers 0-1 */
	u32 mkivlr0;    /* Mask Invalid Register 0*/
	u32 mier0;      /* Mailbox Interrupt Enable Register 0 */
	u8 pad_440[0x3c0];
	u8 mctl[64];	/* Message Control Registers */
	u16 ctlr;	/* Control Register */
	u16 str;	/* Status रेजिस्टर */
	u8 bcr[3];	/* Bit Configuration Register */
	u8 clkr;	/* Clock Select Register */
	u8 rfcr;	/* Receive FIFO Control Register */
	u8 rfpcr;	/* Receive FIFO Poपूर्णांकer Control Register */
	u8 tfcr;	/* Transmit FIFO Control Register */
	u8 tfpcr;       /* Transmit FIFO Poपूर्णांकer Control Register */
	u8 eier;	/* Error Interrupt Enable Register */
	u8 eअगरr;	/* Error Interrupt Factor Judge Register */
	u8 recr;	/* Receive Error Count Register */
	u8 tecr;        /* Transmit Error Count Register */
	u8 ecsr;	/* Error Code Store Register */
	u8 cssr;	/* Channel Search Support Register */
	u8 mssr;	/* Mailbox Search Status Register */
	u8 msmr;	/* Mailbox Search Mode Register */
	u16 tsr;	/* Time Stamp Register */
	u8 afsr;	/* Acceptance Filter Support Register */
	u8 pad_857;
	u8 tcr;		/* Test Control Register */
	u8 pad_859[7];
	u8 ier;		/* Interrupt Enable Register */
	u8 isr;		/* Interrupt Status Register */
	u8 pad_862;
	u8 mbsmr;	/* Mailbox Search Mask Register */
पूर्ण;

काष्ठा rcar_can_priv अणु
	काष्ठा can_priv can;	/* Must be the first member! */
	काष्ठा net_device *ndev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा rcar_can_regs __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा clk *can_clk;
	u8 tx_dlc[RCAR_CAN_FIFO_DEPTH];
	u32 tx_head;
	u32 tx_tail;
	u8 घड़ी_select;
	u8 ier;
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर rcar_can_bittiming_स्थिर = अणु
	.name = RCAR_CAN_DRV_NAME,
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

/* Control Register bits */
#घोषणा RCAR_CAN_CTLR_BOM	(3 << 11) /* Bus-Off Recovery Mode Bits */
#घोषणा RCAR_CAN_CTLR_BOM_ENT	(1 << 11) /* Entry to halt mode */
					/* at bus-off entry */
#घोषणा RCAR_CAN_CTLR_SLPM	(1 << 10)
#घोषणा RCAR_CAN_CTLR_CANM	(3 << 8) /* Operating Mode Select Bit */
#घोषणा RCAR_CAN_CTLR_CANM_HALT	(1 << 9)
#घोषणा RCAR_CAN_CTLR_CANM_RESET (1 << 8)
#घोषणा RCAR_CAN_CTLR_CANM_FORCE_RESET (3 << 8)
#घोषणा RCAR_CAN_CTLR_MLM	(1 << 3) /* Message Lost Mode Select */
#घोषणा RCAR_CAN_CTLR_IDFM	(3 << 1) /* ID Format Mode Select Bits */
#घोषणा RCAR_CAN_CTLR_IDFM_MIXED (1 << 2) /* Mixed ID mode */
#घोषणा RCAR_CAN_CTLR_MBM	(1 << 0) /* Mailbox Mode select */

/* Status Register bits */
#घोषणा RCAR_CAN_STR_RSTST	(1 << 8) /* Reset Status Bit */

/* FIFO Received ID Compare Registers 0 and 1 bits */
#घोषणा RCAR_CAN_FIDCR_IDE	(1 << 31) /* ID Extension Bit */
#घोषणा RCAR_CAN_FIDCR_RTR	(1 << 30) /* Remote Transmission Request Bit */

/* Receive FIFO Control Register bits */
#घोषणा RCAR_CAN_RFCR_RFEST	(1 << 7) /* Receive FIFO Empty Status Flag */
#घोषणा RCAR_CAN_RFCR_RFE	(1 << 0) /* Receive FIFO Enable */

/* Transmit FIFO Control Register bits */
#घोषणा RCAR_CAN_TFCR_TFUST	(7 << 1) /* Transmit FIFO Unsent Message */
					/* Number Status Bits */
#घोषणा RCAR_CAN_TFCR_TFUST_SHIFT 1	/* Offset of Transmit FIFO Unsent */
					/* Message Number Status Bits */
#घोषणा RCAR_CAN_TFCR_TFE	(1 << 0) /* Transmit FIFO Enable */

#घोषणा RCAR_CAN_N_RX_MKREGS1	2	/* Number of mask रेजिस्टरs */
					/* क्रम Rx mailboxes 0-31 */
#घोषणा RCAR_CAN_N_RX_MKREGS2	8

/* Bit Configuration Register settings */
#घोषणा RCAR_CAN_BCR_TSEG1(x)	(((x) & 0x0f) << 20)
#घोषणा RCAR_CAN_BCR_BPR(x)	(((x) & 0x3ff) << 8)
#घोषणा RCAR_CAN_BCR_SJW(x)	(((x) & 0x3) << 4)
#घोषणा RCAR_CAN_BCR_TSEG2(x)	((x) & 0x07)

/* Mailbox and Mask Registers bits */
#घोषणा RCAR_CAN_IDE		(1 << 31)
#घोषणा RCAR_CAN_RTR		(1 << 30)
#घोषणा RCAR_CAN_SID_SHIFT	18

/* Mailbox Interrupt Enable Register 1 bits */
#घोषणा RCAR_CAN_MIER1_RXFIE	(1 << 28) /* Receive  FIFO Interrupt Enable */
#घोषणा RCAR_CAN_MIER1_TXFIE	(1 << 24) /* Transmit FIFO Interrupt Enable */

/* Interrupt Enable Register bits */
#घोषणा RCAR_CAN_IER_ERSIE	(1 << 5) /* Error (ERS) Interrupt Enable Bit */
#घोषणा RCAR_CAN_IER_RXFIE	(1 << 4) /* Reception FIFO Interrupt */
					/* Enable Bit */
#घोषणा RCAR_CAN_IER_TXFIE	(1 << 3) /* Transmission FIFO Interrupt */
					/* Enable Bit */
/* Interrupt Status Register bits */
#घोषणा RCAR_CAN_ISR_ERSF	(1 << 5) /* Error (ERS) Interrupt Status Bit */
#घोषणा RCAR_CAN_ISR_RXFF	(1 << 4) /* Reception FIFO Interrupt */
					/* Status Bit */
#घोषणा RCAR_CAN_ISR_TXFF	(1 << 3) /* Transmission FIFO Interrupt */
					/* Status Bit */

/* Error Interrupt Enable Register bits */
#घोषणा RCAR_CAN_EIER_BLIE	(1 << 7) /* Bus Lock Interrupt Enable */
#घोषणा RCAR_CAN_EIER_OLIE	(1 << 6) /* Overload Frame Transmit */
					/* Interrupt Enable */
#घोषणा RCAR_CAN_EIER_ORIE	(1 << 5) /* Receive Overrun  Interrupt Enable */
#घोषणा RCAR_CAN_EIER_BORIE	(1 << 4) /* Bus-Off Recovery Interrupt Enable */
#घोषणा RCAR_CAN_EIER_BOEIE	(1 << 3) /* Bus-Off Entry Interrupt Enable */
#घोषणा RCAR_CAN_EIER_EPIE	(1 << 2) /* Error Passive Interrupt Enable */
#घोषणा RCAR_CAN_EIER_EWIE	(1 << 1) /* Error Warning Interrupt Enable */
#घोषणा RCAR_CAN_EIER_BEIE	(1 << 0) /* Bus Error Interrupt Enable */

/* Error Interrupt Factor Judge Register bits */
#घोषणा RCAR_CAN_EIFR_BLIF	(1 << 7) /* Bus Lock Detect Flag */
#घोषणा RCAR_CAN_EIFR_OLIF	(1 << 6) /* Overload Frame Transmission */
					 /* Detect Flag */
#घोषणा RCAR_CAN_EIFR_ORIF	(1 << 5) /* Receive Overrun Detect Flag */
#घोषणा RCAR_CAN_EIFR_BORIF	(1 << 4) /* Bus-Off Recovery Detect Flag */
#घोषणा RCAR_CAN_EIFR_BOEIF	(1 << 3) /* Bus-Off Entry Detect Flag */
#घोषणा RCAR_CAN_EIFR_EPIF	(1 << 2) /* Error Passive Detect Flag */
#घोषणा RCAR_CAN_EIFR_EWIF	(1 << 1) /* Error Warning Detect Flag */
#घोषणा RCAR_CAN_EIFR_BEIF	(1 << 0) /* Bus Error Detect Flag */

/* Error Code Store Register bits */
#घोषणा RCAR_CAN_ECSR_EDPM	(1 << 7) /* Error Display Mode Select Bit */
#घोषणा RCAR_CAN_ECSR_ADEF	(1 << 6) /* ACK Delimiter Error Flag */
#घोषणा RCAR_CAN_ECSR_BE0F	(1 << 5) /* Bit Error (करोminant) Flag */
#घोषणा RCAR_CAN_ECSR_BE1F	(1 << 4) /* Bit Error (recessive) Flag */
#घोषणा RCAR_CAN_ECSR_CEF	(1 << 3) /* CRC Error Flag */
#घोषणा RCAR_CAN_ECSR_AEF	(1 << 2) /* ACK Error Flag */
#घोषणा RCAR_CAN_ECSR_FEF	(1 << 1) /* Form Error Flag */
#घोषणा RCAR_CAN_ECSR_SEF	(1 << 0) /* Stuff Error Flag */

#घोषणा RCAR_CAN_NAPI_WEIGHT	4
#घोषणा MAX_STR_READS		0x100

अटल व्योम tx_failure_cleanup(काष्ठा net_device *ndev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RCAR_CAN_FIFO_DEPTH; i++)
		can_मुक्त_echo_skb(ndev, i, शून्य);
पूर्ण

अटल व्योम rcar_can_error(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u8 eअगरr, txerr = 0, rxerr = 0;

	/* Propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(ndev, &cf);

	eअगरr = पढ़ोb(&priv->regs->eअगरr);
	अगर (eअगरr & (RCAR_CAN_EIFR_EWIF | RCAR_CAN_EIFR_EPIF)) अणु
		txerr = पढ़ोb(&priv->regs->tecr);
		rxerr = पढ़ोb(&priv->regs->recr);
		अगर (skb) अणु
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[6] = txerr;
			cf->data[7] = rxerr;
		पूर्ण
	पूर्ण
	अगर (eअगरr & RCAR_CAN_EIFR_BEIF) अणु
		पूर्णांक rx_errors = 0, tx_errors = 0;
		u8 ecsr;

		netdev_dbg(priv->ndev, "Bus error interrupt:\n");
		अगर (skb)
			cf->can_id |= CAN_ERR_BUSERROR | CAN_ERR_PROT;

		ecsr = पढ़ोb(&priv->regs->ecsr);
		अगर (ecsr & RCAR_CAN_ECSR_ADEF) अणु
			netdev_dbg(priv->ndev, "ACK Delimiter Error\n");
			tx_errors++;
			ग_लिखोb(~RCAR_CAN_ECSR_ADEF, &priv->regs->ecsr);
			अगर (skb)
				cf->data[3] = CAN_ERR_PROT_LOC_ACK_DEL;
		पूर्ण
		अगर (ecsr & RCAR_CAN_ECSR_BE0F) अणु
			netdev_dbg(priv->ndev, "Bit Error (dominant)\n");
			tx_errors++;
			ग_लिखोb(~RCAR_CAN_ECSR_BE0F, &priv->regs->ecsr);
			अगर (skb)
				cf->data[2] |= CAN_ERR_PROT_BIT0;
		पूर्ण
		अगर (ecsr & RCAR_CAN_ECSR_BE1F) अणु
			netdev_dbg(priv->ndev, "Bit Error (recessive)\n");
			tx_errors++;
			ग_लिखोb(~RCAR_CAN_ECSR_BE1F, &priv->regs->ecsr);
			अगर (skb)
				cf->data[2] |= CAN_ERR_PROT_BIT1;
		पूर्ण
		अगर (ecsr & RCAR_CAN_ECSR_CEF) अणु
			netdev_dbg(priv->ndev, "CRC Error\n");
			rx_errors++;
			ग_लिखोb(~RCAR_CAN_ECSR_CEF, &priv->regs->ecsr);
			अगर (skb)
				cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		पूर्ण
		अगर (ecsr & RCAR_CAN_ECSR_AEF) अणु
			netdev_dbg(priv->ndev, "ACK Error\n");
			tx_errors++;
			ग_लिखोb(~RCAR_CAN_ECSR_AEF, &priv->regs->ecsr);
			अगर (skb) अणु
				cf->can_id |= CAN_ERR_ACK;
				cf->data[3] = CAN_ERR_PROT_LOC_ACK;
			पूर्ण
		पूर्ण
		अगर (ecsr & RCAR_CAN_ECSR_FEF) अणु
			netdev_dbg(priv->ndev, "Form Error\n");
			rx_errors++;
			ग_लिखोb(~RCAR_CAN_ECSR_FEF, &priv->regs->ecsr);
			अगर (skb)
				cf->data[2] |= CAN_ERR_PROT_FORM;
		पूर्ण
		अगर (ecsr & RCAR_CAN_ECSR_SEF) अणु
			netdev_dbg(priv->ndev, "Stuff Error\n");
			rx_errors++;
			ग_लिखोb(~RCAR_CAN_ECSR_SEF, &priv->regs->ecsr);
			अगर (skb)
				cf->data[2] |= CAN_ERR_PROT_STUFF;
		पूर्ण

		priv->can.can_stats.bus_error++;
		ndev->stats.rx_errors += rx_errors;
		ndev->stats.tx_errors += tx_errors;
		ग_लिखोb(~RCAR_CAN_EIFR_BEIF, &priv->regs->eअगरr);
	पूर्ण
	अगर (eअगरr & RCAR_CAN_EIFR_EWIF) अणु
		netdev_dbg(priv->ndev, "Error warning interrupt\n");
		priv->can.state = CAN_STATE_ERROR_WARNING;
		priv->can.can_stats.error_warning++;
		/* Clear पूर्णांकerrupt condition */
		ग_लिखोb(~RCAR_CAN_EIFR_EWIF, &priv->regs->eअगरr);
		अगर (skb)
			cf->data[1] = txerr > rxerr ? CAN_ERR_CRTL_TX_WARNING :
					      CAN_ERR_CRTL_RX_WARNING;
	पूर्ण
	अगर (eअगरr & RCAR_CAN_EIFR_EPIF) अणु
		netdev_dbg(priv->ndev, "Error passive interrupt\n");
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		priv->can.can_stats.error_passive++;
		/* Clear पूर्णांकerrupt condition */
		ग_लिखोb(~RCAR_CAN_EIFR_EPIF, &priv->regs->eअगरr);
		अगर (skb)
			cf->data[1] = txerr > rxerr ? CAN_ERR_CRTL_TX_PASSIVE :
					      CAN_ERR_CRTL_RX_PASSIVE;
	पूर्ण
	अगर (eअगरr & RCAR_CAN_EIFR_BOEIF) अणु
		netdev_dbg(priv->ndev, "Bus-off entry interrupt\n");
		tx_failure_cleanup(ndev);
		priv->ier = RCAR_CAN_IER_ERSIE;
		ग_लिखोb(priv->ier, &priv->regs->ier);
		priv->can.state = CAN_STATE_BUS_OFF;
		/* Clear पूर्णांकerrupt condition */
		ग_लिखोb(~RCAR_CAN_EIFR_BOEIF, &priv->regs->eअगरr);
		priv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		अगर (skb)
			cf->can_id |= CAN_ERR_BUSOFF;
	पूर्ण
	अगर (eअगरr & RCAR_CAN_EIFR_ORIF) अणु
		netdev_dbg(priv->ndev, "Receive overrun error interrupt\n");
		ndev->stats.rx_over_errors++;
		ndev->stats.rx_errors++;
		ग_लिखोb(~RCAR_CAN_EIFR_ORIF, &priv->regs->eअगरr);
		अगर (skb) अणु
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		पूर्ण
	पूर्ण
	अगर (eअगरr & RCAR_CAN_EIFR_OLIF) अणु
		netdev_dbg(priv->ndev,
			   "Overload Frame Transmission error interrupt\n");
		ndev->stats.rx_over_errors++;
		ndev->stats.rx_errors++;
		ग_लिखोb(~RCAR_CAN_EIFR_OLIF, &priv->regs->eअगरr);
		अगर (skb) अणु
			cf->can_id |= CAN_ERR_PROT;
			cf->data[2] |= CAN_ERR_PROT_OVERLOAD;
		पूर्ण
	पूर्ण

	अगर (skb) अणु
		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_rx(skb);
	पूर्ण
पूर्ण

अटल व्योम rcar_can_tx_करोne(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	u8 isr;

	जबतक (1) अणु
		u8 unsent = पढ़ोb(&priv->regs->tfcr);

		unsent = (unsent & RCAR_CAN_TFCR_TFUST) >>
			  RCAR_CAN_TFCR_TFUST_SHIFT;
		अगर (priv->tx_head - priv->tx_tail <= unsent)
			अवरोध;
		stats->tx_packets++;
		stats->tx_bytes += priv->tx_dlc[priv->tx_tail %
						RCAR_CAN_FIFO_DEPTH];
		priv->tx_dlc[priv->tx_tail % RCAR_CAN_FIFO_DEPTH] = 0;
		can_get_echo_skb(ndev, priv->tx_tail % RCAR_CAN_FIFO_DEPTH, शून्य);
		priv->tx_tail++;
		netअगर_wake_queue(ndev);
	पूर्ण
	/* Clear पूर्णांकerrupt */
	isr = पढ़ोb(&priv->regs->isr);
	ग_लिखोb(isr & ~RCAR_CAN_ISR_TXFF, &priv->regs->isr);
	can_led_event(ndev, CAN_LED_EVENT_TX);
पूर्ण

अटल irqवापस_t rcar_can_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	u8 isr;

	isr = पढ़ोb(&priv->regs->isr);
	अगर (!(isr & priv->ier))
		वापस IRQ_NONE;

	अगर (isr & RCAR_CAN_ISR_ERSF)
		rcar_can_error(ndev);

	अगर (isr & RCAR_CAN_ISR_TXFF)
		rcar_can_tx_करोne(ndev);

	अगर (isr & RCAR_CAN_ISR_RXFF) अणु
		अगर (napi_schedule_prep(&priv->napi)) अणु
			/* Disable Rx FIFO पूर्णांकerrupts */
			priv->ier &= ~RCAR_CAN_IER_RXFIE;
			ग_लिखोb(priv->ier, &priv->regs->ier);
			__napi_schedule(&priv->napi);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rcar_can_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(dev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u32 bcr;

	bcr = RCAR_CAN_BCR_TSEG1(bt->phase_seg1 + bt->prop_seg - 1) |
	      RCAR_CAN_BCR_BPR(bt->brp - 1) | RCAR_CAN_BCR_SJW(bt->sjw - 1) |
	      RCAR_CAN_BCR_TSEG2(bt->phase_seg2 - 1);
	/* Don't overग_लिखो CLKR with 32-bit BCR access; CLKR has 8-bit access.
	 * All the रेजिस्टरs are big-endian but they get byte-swapped on 32-bit
	 * पढ़ो/ग_लिखो (but not on 8-bit, contrary to the manuals)...
	 */
	ग_लिखोl((bcr << 8) | priv->घड़ी_select, &priv->regs->bcr);
पूर्ण

अटल व्योम rcar_can_start(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	u16 ctlr;
	पूर्णांक i;

	/* Set controller to known mode:
	 * - FIFO mailbox mode
	 * - accept all messages
	 * - overrun mode
	 * CAN is in sleep mode after MCU hardware or software reset.
	 */
	ctlr = पढ़ोw(&priv->regs->ctlr);
	ctlr &= ~RCAR_CAN_CTLR_SLPM;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	/* Go to reset mode */
	ctlr |= RCAR_CAN_CTLR_CANM_FORCE_RESET;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	क्रम (i = 0; i < MAX_STR_READS; i++) अणु
		अगर (पढ़ोw(&priv->regs->str) & RCAR_CAN_STR_RSTST)
			अवरोध;
	पूर्ण
	rcar_can_set_bittiming(ndev);
	ctlr |= RCAR_CAN_CTLR_IDFM_MIXED; /* Select mixed ID mode */
	ctlr |= RCAR_CAN_CTLR_BOM_ENT;	/* Entry to halt mode स्वतःmatically */
					/* at bus-off */
	ctlr |= RCAR_CAN_CTLR_MBM;	/* Select FIFO mailbox mode */
	ctlr |= RCAR_CAN_CTLR_MLM;	/* Overrun mode */
	ग_लिखोw(ctlr, &priv->regs->ctlr);

	/* Accept all SID and EID */
	ग_लिखोl(0, &priv->regs->mkr_2_9[6]);
	ग_लिखोl(0, &priv->regs->mkr_2_9[7]);
	/* In FIFO mailbox mode, ग_लिखो "0" to bits 24 to 31 */
	ग_लिखोl(0, &priv->regs->mkivlr1);
	/* Accept all frames */
	ग_लिखोl(0, &priv->regs->fidcr[0]);
	ग_लिखोl(RCAR_CAN_FIDCR_IDE | RCAR_CAN_FIDCR_RTR, &priv->regs->fidcr[1]);
	/* Enable and configure FIFO mailbox पूर्णांकerrupts */
	ग_लिखोl(RCAR_CAN_MIER1_RXFIE | RCAR_CAN_MIER1_TXFIE, &priv->regs->mier1);

	priv->ier = RCAR_CAN_IER_ERSIE | RCAR_CAN_IER_RXFIE |
		    RCAR_CAN_IER_TXFIE;
	ग_लिखोb(priv->ier, &priv->regs->ier);

	/* Accumulate error codes */
	ग_लिखोb(RCAR_CAN_ECSR_EDPM, &priv->regs->ecsr);
	/* Enable error पूर्णांकerrupts */
	ग_लिखोb(RCAR_CAN_EIER_EWIE | RCAR_CAN_EIER_EPIE | RCAR_CAN_EIER_BOEIE |
	       (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING ?
	       RCAR_CAN_EIER_BEIE : 0) | RCAR_CAN_EIER_ORIE |
	       RCAR_CAN_EIER_OLIE, &priv->regs->eier);
	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Go to operation mode */
	ग_लिखोw(ctlr & ~RCAR_CAN_CTLR_CANM, &priv->regs->ctlr);
	क्रम (i = 0; i < MAX_STR_READS; i++) अणु
		अगर (!(पढ़ोw(&priv->regs->str) & RCAR_CAN_STR_RSTST))
			अवरोध;
	पूर्ण
	/* Enable Rx and Tx FIFO */
	ग_लिखोb(RCAR_CAN_RFCR_RFE, &priv->regs->rfcr);
	ग_लिखोb(RCAR_CAN_TFCR_TFE, &priv->regs->tfcr);
पूर्ण

अटल पूर्णांक rcar_can_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		netdev_err(ndev,
			   "failed to enable peripheral clock, error %d\n",
			   err);
		जाओ out;
	पूर्ण
	err = clk_prepare_enable(priv->can_clk);
	अगर (err) अणु
		netdev_err(ndev, "failed to enable CAN clock, error %d\n",
			   err);
		जाओ out_घड़ी;
	पूर्ण
	err = खोलो_candev(ndev);
	अगर (err) अणु
		netdev_err(ndev, "open_candev() failed, error %d\n", err);
		जाओ out_can_घड़ी;
	पूर्ण
	napi_enable(&priv->napi);
	err = request_irq(ndev->irq, rcar_can_पूर्णांकerrupt, 0, ndev->name, ndev);
	अगर (err) अणु
		netdev_err(ndev, "request_irq(%d) failed, error %d\n",
			   ndev->irq, err);
		जाओ out_बंद;
	पूर्ण
	can_led_event(ndev, CAN_LED_EVENT_OPEN);
	rcar_can_start(ndev);
	netअगर_start_queue(ndev);
	वापस 0;
out_बंद:
	napi_disable(&priv->napi);
	बंद_candev(ndev);
out_can_घड़ी:
	clk_disable_unprepare(priv->can_clk);
out_घड़ी:
	clk_disable_unprepare(priv->clk);
out:
	वापस err;
पूर्ण

अटल व्योम rcar_can_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	u16 ctlr;
	पूर्णांक i;

	/* Go to (क्रमce) reset mode */
	ctlr = पढ़ोw(&priv->regs->ctlr);
	ctlr |= RCAR_CAN_CTLR_CANM_FORCE_RESET;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	क्रम (i = 0; i < MAX_STR_READS; i++) अणु
		अगर (पढ़ोw(&priv->regs->str) & RCAR_CAN_STR_RSTST)
			अवरोध;
	पूर्ण
	ग_लिखोl(0, &priv->regs->mier0);
	ग_लिखोl(0, &priv->regs->mier1);
	ग_लिखोb(0, &priv->regs->ier);
	ग_लिखोb(0, &priv->regs->eier);
	/* Go to sleep mode */
	ctlr |= RCAR_CAN_CTLR_SLPM;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	priv->can.state = CAN_STATE_STOPPED;
पूर्ण

अटल पूर्णांक rcar_can_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	rcar_can_stop(ndev);
	मुक्त_irq(ndev->irq, ndev);
	napi_disable(&priv->napi);
	clk_disable_unprepare(priv->can_clk);
	clk_disable_unprepare(priv->clk);
	बंद_candev(ndev);
	can_led_event(ndev, CAN_LED_EVENT_STOP);
	वापस 0;
पूर्ण

अटल netdev_tx_t rcar_can_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *ndev)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	u32 data, i;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	अगर (cf->can_id & CAN_EFF_FLAG)	/* Extended frame क्रमmat */
		data = (cf->can_id & CAN_EFF_MASK) | RCAR_CAN_IDE;
	अन्यथा				/* Standard frame क्रमmat */
		data = (cf->can_id & CAN_SFF_MASK) << RCAR_CAN_SID_SHIFT;

	अगर (cf->can_id & CAN_RTR_FLAG) अणु /* Remote transmission request */
		data |= RCAR_CAN_RTR;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < cf->len; i++)
			ग_लिखोb(cf->data[i],
			       &priv->regs->mb[RCAR_CAN_TX_FIFO_MBX].data[i]);
	पूर्ण

	ग_लिखोl(data, &priv->regs->mb[RCAR_CAN_TX_FIFO_MBX].id);

	ग_लिखोb(cf->len, &priv->regs->mb[RCAR_CAN_TX_FIFO_MBX].dlc);

	priv->tx_dlc[priv->tx_head % RCAR_CAN_FIFO_DEPTH] = cf->len;
	can_put_echo_skb(skb, ndev, priv->tx_head % RCAR_CAN_FIFO_DEPTH, 0);
	priv->tx_head++;
	/* Start Tx: ग_लिखो 0xff to the TFPCR रेजिस्टर to increment
	 * the CPU-side poपूर्णांकer क्रम the transmit FIFO to the next
	 * mailbox location
	 */
	ग_लिखोb(0xff, &priv->regs->tfpcr);
	/* Stop the queue अगर we've filled all FIFO entries */
	अगर (priv->tx_head - priv->tx_tail >= RCAR_CAN_FIFO_DEPTH)
		netअगर_stop_queue(ndev);

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops rcar_can_netdev_ops = अणु
	.nकरो_खोलो = rcar_can_खोलो,
	.nकरो_stop = rcar_can_बंद,
	.nकरो_start_xmit = rcar_can_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल व्योम rcar_can_rx_pkt(काष्ठा rcar_can_priv *priv)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 data;
	u8 dlc;

	skb = alloc_can_skb(priv->ndev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	data = पढ़ोl(&priv->regs->mb[RCAR_CAN_RX_FIFO_MBX].id);
	अगर (data & RCAR_CAN_IDE)
		cf->can_id = (data & CAN_EFF_MASK) | CAN_EFF_FLAG;
	अन्यथा
		cf->can_id = (data >> RCAR_CAN_SID_SHIFT) & CAN_SFF_MASK;

	dlc = पढ़ोb(&priv->regs->mb[RCAR_CAN_RX_FIFO_MBX].dlc);
	cf->len = can_cc_dlc2len(dlc);
	अगर (data & RCAR_CAN_RTR) अणु
		cf->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		क्रम (dlc = 0; dlc < cf->len; dlc++)
			cf->data[dlc] =
			पढ़ोb(&priv->regs->mb[RCAR_CAN_RX_FIFO_MBX].data[dlc]);
	पूर्ण

	can_led_event(priv->ndev, CAN_LED_EVENT_RX);

	stats->rx_bytes += cf->len;
	stats->rx_packets++;
	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक rcar_can_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा rcar_can_priv *priv = container_of(napi,
						  काष्ठा rcar_can_priv, napi);
	पूर्णांक num_pkts;

	क्रम (num_pkts = 0; num_pkts < quota; num_pkts++) अणु
		u8 rfcr, isr;

		isr = पढ़ोb(&priv->regs->isr);
		/* Clear पूर्णांकerrupt bit */
		अगर (isr & RCAR_CAN_ISR_RXFF)
			ग_लिखोb(isr & ~RCAR_CAN_ISR_RXFF, &priv->regs->isr);
		rfcr = पढ़ोb(&priv->regs->rfcr);
		अगर (rfcr & RCAR_CAN_RFCR_RFEST)
			अवरोध;
		rcar_can_rx_pkt(priv);
		/* Write 0xff to the RFPCR रेजिस्टर to increment
		 * the CPU-side poपूर्णांकer क्रम the receive FIFO
		 * to the next mailbox location
		 */
		ग_लिखोb(0xff, &priv->regs->rfpcr);
	पूर्ण
	/* All packets processed */
	अगर (num_pkts < quota) अणु
		napi_complete_करोne(napi, num_pkts);
		priv->ier |= RCAR_CAN_IER_RXFIE;
		ग_लिखोb(priv->ier, &priv->regs->ier);
	पूर्ण
	वापस num_pkts;
पूर्ण

अटल पूर्णांक rcar_can_करो_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	चयन (mode) अणु
	हाल CAN_MODE_START:
		rcar_can_start(ndev);
		netअगर_wake_queue(ndev);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_can_get_berr_counter(स्थिर काष्ठा net_device *dev,
				     काष्ठा can_berr_counter *bec)
अणु
	काष्ठा rcar_can_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		वापस err;
	bec->txerr = पढ़ोb(&priv->regs->tecr);
	bec->rxerr = पढ़ोb(&priv->regs->recr);
	clk_disable_unprepare(priv->clk);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर घड़ी_names[] = अणु
	[CLKR_CLKP1]	= "clkp1",
	[CLKR_CLKP2]	= "clkp2",
	[CLKR_CLKEXT]	= "can_clk",
पूर्ण;

अटल पूर्णांक rcar_can_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_can_priv *priv;
	काष्ठा net_device *ndev;
	व्योम __iomem *addr;
	u32 घड़ी_select = CLKR_CLKP1;
	पूर्णांक err = -ENODEV;
	पूर्णांक irq;

	of_property_पढ़ो_u32(pdev->dev.of_node, "renesas,can-clock-select",
			     &घड़ी_select);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ fail;
	पूर्ण

	addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(addr)) अणु
		err = PTR_ERR(addr);
		जाओ fail;
	पूर्ण

	ndev = alloc_candev(माप(काष्ठा rcar_can_priv), RCAR_CAN_FIFO_DEPTH);
	अगर (!ndev) अणु
		dev_err(&pdev->dev, "alloc_candev() failed\n");
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	priv = netdev_priv(ndev);

	priv->clk = devm_clk_get(&pdev->dev, "clkp1");
	अगर (IS_ERR(priv->clk)) अणु
		err = PTR_ERR(priv->clk);
		dev_err(&pdev->dev, "cannot get peripheral clock, error %d\n",
			err);
		जाओ fail_clk;
	पूर्ण

	अगर (!(BIT(घड़ी_select) & RCAR_SUPPORTED_CLOCKS)) अणु
		err = -EINVAL;
		dev_err(&pdev->dev, "invalid CAN clock selected\n");
		जाओ fail_clk;
	पूर्ण
	priv->can_clk = devm_clk_get(&pdev->dev, घड़ी_names[घड़ी_select]);
	अगर (IS_ERR(priv->can_clk)) अणु
		err = PTR_ERR(priv->can_clk);
		dev_err(&pdev->dev, "cannot get CAN clock, error %d\n", err);
		जाओ fail_clk;
	पूर्ण

	ndev->netdev_ops = &rcar_can_netdev_ops;
	ndev->irq = irq;
	ndev->flags |= IFF_ECHO;
	priv->ndev = ndev;
	priv->regs = addr;
	priv->घड़ी_select = घड़ी_select;
	priv->can.घड़ी.freq = clk_get_rate(priv->can_clk);
	priv->can.bittiming_स्थिर = &rcar_can_bittiming_स्थिर;
	priv->can.करो_set_mode = rcar_can_करो_set_mode;
	priv->can.करो_get_berr_counter = rcar_can_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_BERR_REPORTING;
	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	netअगर_napi_add(ndev, &priv->napi, rcar_can_rx_poll,
		       RCAR_CAN_NAPI_WEIGHT);
	err = रेजिस्टर_candev(ndev);
	अगर (err) अणु
		dev_err(&pdev->dev, "register_candev() failed, error %d\n",
			err);
		जाओ fail_candev;
	पूर्ण

	devm_can_led_init(ndev);

	dev_info(&pdev->dev, "device registered (IRQ%d)\n", ndev->irq);

	वापस 0;
fail_candev:
	netअगर_napi_del(&priv->napi);
fail_clk:
	मुक्त_candev(ndev);
fail:
	वापस err;
पूर्ण

अटल पूर्णांक rcar_can_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);

	unरेजिस्टर_candev(ndev);
	netअगर_napi_del(&priv->napi);
	मुक्त_candev(ndev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rcar_can_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	u16 ctlr;

	अगर (netअगर_running(ndev)) अणु
		netअगर_stop_queue(ndev);
		netअगर_device_detach(ndev);
	पूर्ण
	ctlr = पढ़ोw(&priv->regs->ctlr);
	ctlr |= RCAR_CAN_CTLR_CANM_HALT;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	ctlr |= RCAR_CAN_CTLR_SLPM;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	priv->can.state = CAN_STATE_SLEEPING;

	clk_disable(priv->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rcar_can_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा rcar_can_priv *priv = netdev_priv(ndev);
	u16 ctlr;
	पूर्णांक err;

	err = clk_enable(priv->clk);
	अगर (err) अणु
		netdev_err(ndev, "clk_enable() failed, error %d\n", err);
		वापस err;
	पूर्ण

	ctlr = पढ़ोw(&priv->regs->ctlr);
	ctlr &= ~RCAR_CAN_CTLR_SLPM;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	ctlr &= ~RCAR_CAN_CTLR_CANM;
	ग_लिखोw(ctlr, &priv->regs->ctlr);
	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	अगर (netअगर_running(ndev)) अणु
		netअगर_device_attach(ndev);
		netअगर_start_queue(ndev);
	पूर्ण
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rcar_can_pm_ops, rcar_can_suspend, rcar_can_resume);

अटल स्थिर काष्ठा of_device_id rcar_can_of_table[] __maybe_unused = अणु
	अणु .compatible = "renesas,can-r8a7778" पूर्ण,
	अणु .compatible = "renesas,can-r8a7779" पूर्ण,
	अणु .compatible = "renesas,can-r8a7790" पूर्ण,
	अणु .compatible = "renesas,can-r8a7791" पूर्ण,
	अणु .compatible = "renesas,rcar-gen1-can" पूर्ण,
	अणु .compatible = "renesas,rcar-gen2-can" पूर्ण,
	अणु .compatible = "renesas,rcar-gen3-can" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_can_of_table);

अटल काष्ठा platक्रमm_driver rcar_can_driver = अणु
	.driver = अणु
		.name = RCAR_CAN_DRV_NAME,
		.of_match_table = of_match_ptr(rcar_can_of_table),
		.pm = &rcar_can_pm_ops,
	पूर्ण,
	.probe = rcar_can_probe,
	.हटाओ = rcar_can_हटाओ,
पूर्ण;

module_platक्रमm_driver(rcar_can_driver);

MODULE_AUTHOR("Cogent Embedded, Inc.");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CAN driver for Renesas R-Car SoC");
MODULE_ALIAS("platform:" RCAR_CAN_DRV_NAME);
