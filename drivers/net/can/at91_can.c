<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * at91_can.c - CAN network driver क्रम AT91 SoC CAN controller
 *
 * (C) 2007 by Hans J. Koch <hjk@hansjkoch.de>
 * (C) 2008, 2009, 2010, 2011 by Marc Kleine-Budde <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>

#घोषणा AT91_MB_MASK(i)		((1 << (i)) - 1)

/* Common रेजिस्टरs */
क्रमागत at91_reg अणु
	AT91_MR		= 0x000,
	AT91_IER	= 0x004,
	AT91_IDR	= 0x008,
	AT91_IMR	= 0x00C,
	AT91_SR		= 0x010,
	AT91_BR		= 0x014,
	AT91_TIM	= 0x018,
	AT91_TIMESTP	= 0x01C,
	AT91_ECR	= 0x020,
	AT91_TCR	= 0x024,
	AT91_ACR	= 0x028,
पूर्ण;

/* Mailbox रेजिस्टरs (0 <= i <= 15) */
#घोषणा AT91_MMR(i)		(क्रमागत at91_reg)(0x200 + ((i) * 0x20))
#घोषणा AT91_MAM(i)		(क्रमागत at91_reg)(0x204 + ((i) * 0x20))
#घोषणा AT91_MID(i)		(क्रमागत at91_reg)(0x208 + ((i) * 0x20))
#घोषणा AT91_MFID(i)		(क्रमागत at91_reg)(0x20C + ((i) * 0x20))
#घोषणा AT91_MSR(i)		(क्रमागत at91_reg)(0x210 + ((i) * 0x20))
#घोषणा AT91_MDL(i)		(क्रमागत at91_reg)(0x214 + ((i) * 0x20))
#घोषणा AT91_MDH(i)		(क्रमागत at91_reg)(0x218 + ((i) * 0x20))
#घोषणा AT91_MCR(i)		(क्रमागत at91_reg)(0x21C + ((i) * 0x20))

/* Register bits */
#घोषणा AT91_MR_CANEN		BIT(0)
#घोषणा AT91_MR_LPM		BIT(1)
#घोषणा AT91_MR_ABM		BIT(2)
#घोषणा AT91_MR_OVL		BIT(3)
#घोषणा AT91_MR_Tखातापूर्ण		BIT(4)
#घोषणा AT91_MR_TTM		BIT(5)
#घोषणा AT91_MR_TIMFRZ		BIT(6)
#घोषणा AT91_MR_DRPT		BIT(7)

#घोषणा AT91_SR_RBSY		BIT(29)

#घोषणा AT91_MMR_PRIO_SHIFT	(16)

#घोषणा AT91_MID_MIDE		BIT(29)

#घोषणा AT91_MSR_MRTR		BIT(20)
#घोषणा AT91_MSR_MABT		BIT(22)
#घोषणा AT91_MSR_MRDY		BIT(23)
#घोषणा AT91_MSR_MMI		BIT(24)

#घोषणा AT91_MCR_MRTR		BIT(20)
#घोषणा AT91_MCR_MTCR		BIT(23)

/* Mailbox Modes */
क्रमागत at91_mb_mode अणु
	AT91_MB_MODE_DISABLED	= 0,
	AT91_MB_MODE_RX		= 1,
	AT91_MB_MODE_RX_OVRWR	= 2,
	AT91_MB_MODE_TX		= 3,
	AT91_MB_MODE_CONSUMER	= 4,
	AT91_MB_MODE_PRODUCER	= 5,
पूर्ण;

/* Interrupt mask bits */
#घोषणा AT91_IRQ_ERRA		(1 << 16)
#घोषणा AT91_IRQ_WARN		(1 << 17)
#घोषणा AT91_IRQ_ERRP		(1 << 18)
#घोषणा AT91_IRQ_BOFF		(1 << 19)
#घोषणा AT91_IRQ_SLEEP		(1 << 20)
#घोषणा AT91_IRQ_WAKEUP		(1 << 21)
#घोषणा AT91_IRQ_TOVF		(1 << 22)
#घोषणा AT91_IRQ_TSTP		(1 << 23)
#घोषणा AT91_IRQ_CERR		(1 << 24)
#घोषणा AT91_IRQ_SERR		(1 << 25)
#घोषणा AT91_IRQ_AERR		(1 << 26)
#घोषणा AT91_IRQ_FERR		(1 << 27)
#घोषणा AT91_IRQ_BERR		(1 << 28)

#घोषणा AT91_IRQ_ERR_ALL	(0x1fff0000)
#घोषणा AT91_IRQ_ERR_FRAME	(AT91_IRQ_CERR | AT91_IRQ_SERR | \
				 AT91_IRQ_AERR | AT91_IRQ_FERR | AT91_IRQ_BERR)
#घोषणा AT91_IRQ_ERR_LINE	(AT91_IRQ_ERRA | AT91_IRQ_WARN | \
				 AT91_IRQ_ERRP | AT91_IRQ_BOFF)

#घोषणा AT91_IRQ_ALL		(0x1fffffff)

क्रमागत at91_devtype अणु
	AT91_DEVTYPE_SAM9263,
	AT91_DEVTYPE_SAM9X5,
पूर्ण;

काष्ठा at91_devtype_data अणु
	अचिन्हित पूर्णांक rx_first;
	अचिन्हित पूर्णांक rx_split;
	अचिन्हित पूर्णांक rx_last;
	अचिन्हित पूर्णांक tx_shअगरt;
	क्रमागत at91_devtype type;
पूर्ण;

काष्ठा at91_priv अणु
	काष्ठा can_priv can;		/* must be the first member! */
	काष्ठा napi_काष्ठा napi;

	व्योम __iomem *reg_base;

	u32 reg_sr;
	अचिन्हित पूर्णांक tx_next;
	अचिन्हित पूर्णांक tx_echo;
	अचिन्हित पूर्णांक rx_next;
	काष्ठा at91_devtype_data devtype_data;

	काष्ठा clk *clk;
	काष्ठा at91_can_data *pdata;

	canid_t mb0_id;
पूर्ण;

अटल स्थिर काष्ठा at91_devtype_data at91_at91sam9263_data = अणु
	.rx_first = 1,
	.rx_split = 8,
	.rx_last = 11,
	.tx_shअगरt = 2,
	.type = AT91_DEVTYPE_SAM9263,
पूर्ण;

अटल स्थिर काष्ठा at91_devtype_data at91_at91sam9x5_data = अणु
	.rx_first = 0,
	.rx_split = 4,
	.rx_last = 5,
	.tx_shअगरt = 1,
	.type = AT91_DEVTYPE_SAM9X5,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर at91_bittiming_स्थिर = अणु
	.name		= KBUILD_MODNAME,
	.tseg1_min	= 4,
	.tseg1_max	= 16,
	.tseg2_min	= 2,
	.tseg2_max	= 8,
	.sjw_max	= 4,
	.brp_min 	= 2,
	.brp_max	= 128,
	.brp_inc	= 1,
पूर्ण;

#घोषणा AT91_IS(_model) \
अटल अंतरभूत पूर्णांक at91_is_sam##_model(स्थिर काष्ठा at91_priv *priv) \
अणु \
	वापस priv->devtype_data.type == AT91_DEVTYPE_SAM##_model; \
पूर्ण

AT91_IS(9263);
AT91_IS(9X5);

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_rx_first(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस priv->devtype_data.rx_first;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_rx_last(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस priv->devtype_data.rx_last;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_rx_split(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस priv->devtype_data.rx_split;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_rx_num(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस get_mb_rx_last(priv) - get_mb_rx_first(priv) + 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_rx_low_last(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस get_mb_rx_split(priv) - 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_rx_low_mask(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस AT91_MB_MASK(get_mb_rx_split(priv)) &
		~AT91_MB_MASK(get_mb_rx_first(priv));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_tx_shअगरt(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस priv->devtype_data.tx_shअगरt;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_tx_num(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस 1 << get_mb_tx_shअगरt(priv);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_tx_first(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस get_mb_rx_last(priv) + 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_mb_tx_last(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस get_mb_tx_first(priv) + get_mb_tx_num(priv) - 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_next_prio_shअगरt(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस get_mb_tx_shअगरt(priv);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_next_prio_mask(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस 0xf << get_mb_tx_shअगरt(priv);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_next_mb_mask(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस AT91_MB_MASK(get_mb_tx_shअगरt(priv));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_next_mask(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस get_next_mb_mask(priv) | get_next_prio_mask(priv);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_irq_mb_rx(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस AT91_MB_MASK(get_mb_rx_last(priv) + 1) &
		~AT91_MB_MASK(get_mb_rx_first(priv));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_irq_mb_tx(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस AT91_MB_MASK(get_mb_tx_last(priv) + 1) &
		~AT91_MB_MASK(get_mb_tx_first(priv));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_tx_next_mb(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस (priv->tx_next & get_next_mb_mask(priv)) + get_mb_tx_first(priv);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_tx_next_prio(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस (priv->tx_next >> get_next_prio_shअगरt(priv)) & 0xf;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_tx_echo_mb(स्थिर काष्ठा at91_priv *priv)
अणु
	वापस (priv->tx_echo & get_next_mb_mask(priv)) + get_mb_tx_first(priv);
पूर्ण

अटल अंतरभूत u32 at91_पढ़ो(स्थिर काष्ठा at91_priv *priv, क्रमागत at91_reg reg)
अणु
	वापस पढ़ोl_relaxed(priv->reg_base + reg);
पूर्ण

अटल अंतरभूत व्योम at91_ग_लिखो(स्थिर काष्ठा at91_priv *priv, क्रमागत at91_reg reg,
		u32 value)
अणु
	ग_लिखोl_relaxed(value, priv->reg_base + reg);
पूर्ण

अटल अंतरभूत व्योम set_mb_mode_prio(स्थिर काष्ठा at91_priv *priv,
		अचिन्हित पूर्णांक mb, क्रमागत at91_mb_mode mode, पूर्णांक prio)
अणु
	at91_ग_लिखो(priv, AT91_MMR(mb), (mode << 24) | (prio << 16));
पूर्ण

अटल अंतरभूत व्योम set_mb_mode(स्थिर काष्ठा at91_priv *priv, अचिन्हित पूर्णांक mb,
		क्रमागत at91_mb_mode mode)
अणु
	set_mb_mode_prio(priv, mb, mode, 0);
पूर्ण

अटल अंतरभूत u32 at91_can_id_to_reg_mid(canid_t can_id)
अणु
	u32 reg_mid;

	अगर (can_id & CAN_EFF_FLAG)
		reg_mid = (can_id & CAN_EFF_MASK) | AT91_MID_MIDE;
	अन्यथा
		reg_mid = (can_id & CAN_SFF_MASK) << 18;

	वापस reg_mid;
पूर्ण

अटल व्योम at91_setup_mailboxes(काष्ठा net_device *dev)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक i;
	u32 reg_mid;

	/*
	 * Due to a chip bug (errata 50.2.6.3 & 50.3.5.3) the first
	 * mailbox is disabled. The next 11 mailboxes are used as a
	 * reception FIFO. The last mailbox is configured with
	 * overग_लिखो option. The overग_लिखो flag indicates a FIFO
	 * overflow.
	 */
	reg_mid = at91_can_id_to_reg_mid(priv->mb0_id);
	क्रम (i = 0; i < get_mb_rx_first(priv); i++) अणु
		set_mb_mode(priv, i, AT91_MB_MODE_DISABLED);
		at91_ग_लिखो(priv, AT91_MID(i), reg_mid);
		at91_ग_लिखो(priv, AT91_MCR(i), 0x0);	/* clear dlc */
	पूर्ण

	क्रम (i = get_mb_rx_first(priv); i < get_mb_rx_last(priv); i++)
		set_mb_mode(priv, i, AT91_MB_MODE_RX);
	set_mb_mode(priv, get_mb_rx_last(priv), AT91_MB_MODE_RX_OVRWR);

	/* reset acceptance mask and id रेजिस्टर */
	क्रम (i = get_mb_rx_first(priv); i <= get_mb_rx_last(priv); i++) अणु
		at91_ग_लिखो(priv, AT91_MAM(i), 0x0);
		at91_ग_लिखो(priv, AT91_MID(i), AT91_MID_MIDE);
	पूर्ण

	/* The last 4 mailboxes are used क्रम transmitting. */
	क्रम (i = get_mb_tx_first(priv); i <= get_mb_tx_last(priv); i++)
		set_mb_mode_prio(priv, i, AT91_MB_MODE_TX, 0);

	/* Reset tx and rx helper poपूर्णांकers */
	priv->tx_next = priv->tx_echo = 0;
	priv->rx_next = get_mb_rx_first(priv);
पूर्ण

अटल पूर्णांक at91_set_bittiming(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा at91_priv *priv = netdev_priv(dev);
	स्थिर काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u32 reg_br;

	reg_br = ((priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) ? 1 << 24 : 0) |
		((bt->brp - 1) << 16) | ((bt->sjw - 1) << 12) |
		((bt->prop_seg - 1) << 8) | ((bt->phase_seg1 - 1) << 4) |
		((bt->phase_seg2 - 1) << 0);

	netdev_info(dev, "writing AT91_BR: 0x%08x\n", reg_br);

	at91_ग_लिखो(priv, AT91_BR, reg_br);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_get_berr_counter(स्थिर काष्ठा net_device *dev,
		काष्ठा can_berr_counter *bec)
अणु
	स्थिर काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_ecr = at91_पढ़ो(priv, AT91_ECR);

	bec->rxerr = reg_ecr & 0xff;
	bec->txerr = reg_ecr >> 16;

	वापस 0;
पूर्ण

अटल व्योम at91_chip_start(काष्ठा net_device *dev)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_mr, reg_ier;

	/* disable पूर्णांकerrupts */
	at91_ग_लिखो(priv, AT91_IDR, AT91_IRQ_ALL);

	/* disable chip */
	reg_mr = at91_पढ़ो(priv, AT91_MR);
	at91_ग_लिखो(priv, AT91_MR, reg_mr & ~AT91_MR_CANEN);

	at91_set_bittiming(dev);
	at91_setup_mailboxes(dev);

	/* enable chip */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		reg_mr = AT91_MR_CANEN | AT91_MR_ABM;
	अन्यथा
		reg_mr = AT91_MR_CANEN;
	at91_ग_लिखो(priv, AT91_MR, reg_mr);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Enable पूर्णांकerrupts */
	reg_ier = get_irq_mb_rx(priv) | AT91_IRQ_ERRP | AT91_IRQ_ERR_FRAME;
	at91_ग_लिखो(priv, AT91_IDR, AT91_IRQ_ALL);
	at91_ग_लिखो(priv, AT91_IER, reg_ier);
पूर्ण

अटल व्योम at91_chip_stop(काष्ठा net_device *dev, क्रमागत can_state state)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_mr;

	/* disable पूर्णांकerrupts */
	at91_ग_लिखो(priv, AT91_IDR, AT91_IRQ_ALL);

	reg_mr = at91_पढ़ो(priv, AT91_MR);
	at91_ग_लिखो(priv, AT91_MR, reg_mr & ~AT91_MR_CANEN);

	priv->can.state = state;
पूर्ण

/*
 * theory of operation:
 *
 * According to the datasheet priority 0 is the highest priority, 15
 * is the lowest. If two mailboxes have the same priority level the
 * message of the mailbox with the lowest number is sent first.
 *
 * We use the first TX mailbox (AT91_MB_TX_FIRST) with prio 0, then
 * the next mailbox with prio 0, and so on, until all mailboxes are
 * used. Then we start from the beginning with mailbox
 * AT91_MB_TX_FIRST, but with prio 1, mailbox AT91_MB_TX_FIRST + 1
 * prio 1. When we reach the last mailbox with prio 15, we have to
 * stop sending, रुकोing क्रम all messages to be delivered, then start
 * again with mailbox AT91_MB_TX_FIRST prio 0.
 *
 * We use the priv->tx_next as counter क्रम the next transmission
 * mailbox, but without the offset AT91_MB_TX_FIRST. The lower bits
 * encode the mailbox number, the upper 4 bits the mailbox priority:
 *
 * priv->tx_next = (prio << get_next_prio_shअगरt(priv)) |
 *                 (mb - get_mb_tx_first(priv));
 *
 */
अटल netdev_tx_t at91_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	अचिन्हित पूर्णांक mb, prio;
	u32 reg_mid, reg_mcr;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	mb = get_tx_next_mb(priv);
	prio = get_tx_next_prio(priv);

	अगर (unlikely(!(at91_पढ़ो(priv, AT91_MSR(mb)) & AT91_MSR_MRDY))) अणु
		netअगर_stop_queue(dev);

		netdev_err(dev, "BUG! TX buffer full when queue awake!\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण
	reg_mid = at91_can_id_to_reg_mid(cf->can_id);
	reg_mcr = ((cf->can_id & CAN_RTR_FLAG) ? AT91_MCR_MRTR : 0) |
		(cf->len << 16) | AT91_MCR_MTCR;

	/* disable MB जबतक writing ID (see datasheet) */
	set_mb_mode(priv, mb, AT91_MB_MODE_DISABLED);
	at91_ग_लिखो(priv, AT91_MID(mb), reg_mid);
	set_mb_mode_prio(priv, mb, AT91_MB_MODE_TX, prio);

	at91_ग_लिखो(priv, AT91_MDL(mb), *(u32 *)(cf->data + 0));
	at91_ग_लिखो(priv, AT91_MDH(mb), *(u32 *)(cf->data + 4));

	/* This triggers transmission */
	at91_ग_लिखो(priv, AT91_MCR(mb), reg_mcr);

	stats->tx_bytes += cf->len;

	/* _NOTE_: subtract AT91_MB_TX_FIRST offset from mb! */
	can_put_echo_skb(skb, dev, mb - get_mb_tx_first(priv), 0);

	/*
	 * we have to stop the queue and deliver all messages in हाल
	 * of a prio+mb counter wrap around. This is the हाल अगर
	 * tx_next buffer prio and mailbox equals 0.
	 *
	 * also stop the queue अगर next buffer is still in use
	 * (== not पढ़ोy)
	 */
	priv->tx_next++;
	अगर (!(at91_पढ़ो(priv, AT91_MSR(get_tx_next_mb(priv))) &
	      AT91_MSR_MRDY) ||
	    (priv->tx_next & get_next_mask(priv)) == 0)
		netअगर_stop_queue(dev);

	/* Enable पूर्णांकerrupt क्रम this mailbox */
	at91_ग_लिखो(priv, AT91_IER, 1 << mb);

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * at91_activate_rx_low - activate lower rx mailboxes
 * @priv: a91 context
 *
 * Reenables the lower mailboxes क्रम reception of new CAN messages
 */
अटल अंतरभूत व्योम at91_activate_rx_low(स्थिर काष्ठा at91_priv *priv)
अणु
	u32 mask = get_mb_rx_low_mask(priv);
	at91_ग_लिखो(priv, AT91_TCR, mask);
पूर्ण

/**
 * at91_activate_rx_mb - reactive single rx mailbox
 * @priv: a91 context
 * @mb: mailbox to reactivate
 *
 * Reenables given mailbox क्रम reception of new CAN messages
 */
अटल अंतरभूत व्योम at91_activate_rx_mb(स्थिर काष्ठा at91_priv *priv,
		अचिन्हित पूर्णांक mb)
अणु
	u32 mask = 1 << mb;
	at91_ग_लिखो(priv, AT91_TCR, mask);
पूर्ण

/**
 * at91_rx_overflow_err - send error frame due to rx overflow
 * @dev: net device
 */
अटल व्योम at91_rx_overflow_err(काष्ठा net_device *dev)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;

	netdev_dbg(dev, "RX buffer overflow\n");
	stats->rx_over_errors++;
	stats->rx_errors++;

	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस;

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_receive_skb(skb);
पूर्ण

/**
 * at91_पढ़ो_mb - पढ़ो CAN msg from mailbox (lowlevel impl)
 * @dev: net device
 * @mb: mailbox number to पढ़ो from
 * @cf: can frame where to store message
 *
 * Reads a CAN message from the given mailbox and stores data पूर्णांकo
 * given can frame. "mb" and "cf" must be valid.
 */
अटल व्योम at91_पढ़ो_mb(काष्ठा net_device *dev, अचिन्हित पूर्णांक mb,
		काष्ठा can_frame *cf)
अणु
	स्थिर काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_msr, reg_mid;

	reg_mid = at91_पढ़ो(priv, AT91_MID(mb));
	अगर (reg_mid & AT91_MID_MIDE)
		cf->can_id = ((reg_mid >> 0) & CAN_EFF_MASK) | CAN_EFF_FLAG;
	अन्यथा
		cf->can_id = (reg_mid >> 18) & CAN_SFF_MASK;

	reg_msr = at91_पढ़ो(priv, AT91_MSR(mb));
	cf->len = can_cc_dlc2len((reg_msr >> 16) & 0xf);

	अगर (reg_msr & AT91_MSR_MRTR)
		cf->can_id |= CAN_RTR_FLAG;
	अन्यथा अणु
		*(u32 *)(cf->data + 0) = at91_पढ़ो(priv, AT91_MDL(mb));
		*(u32 *)(cf->data + 4) = at91_पढ़ो(priv, AT91_MDH(mb));
	पूर्ण

	/* allow RX of extended frames */
	at91_ग_लिखो(priv, AT91_MID(mb), AT91_MID_MIDE);

	अगर (unlikely(mb == get_mb_rx_last(priv) && reg_msr & AT91_MSR_MMI))
		at91_rx_overflow_err(dev);
पूर्ण

/**
 * at91_पढ़ो_msg - पढ़ो CAN message from mailbox
 * @dev: net device
 * @mb: mail box to पढ़ो from
 *
 * Reads a CAN message from given mailbox, and put पूर्णांकo linux network
 * RX queue, करोes all housekeeping chores (stats, ...)
 */
अटल व्योम at91_पढ़ो_msg(काष्ठा net_device *dev, अचिन्हित पूर्णांक mb)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	skb = alloc_can_skb(dev, &cf);
	अगर (unlikely(!skb)) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	at91_पढ़ो_mb(dev, mb, cf);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_receive_skb(skb);

	can_led_event(dev, CAN_LED_EVENT_RX);
पूर्ण

/**
 * at91_poll_rx - पढ़ो multiple CAN messages from mailboxes
 * @dev: net device
 * @quota: max number of pkgs we're allowed to receive
 *
 * Theory of Operation:
 *
 * About 3/4 of the mailboxes (get_mb_rx_first()...get_mb_rx_last())
 * on the chip are reserved क्रम RX. We split them पूर्णांकo 2 groups. The
 * lower group ranges from get_mb_rx_first() to get_mb_rx_low_last().
 *
 * Like it or not, but the chip always saves a received CAN message
 * पूर्णांकo the first मुक्त mailbox it finds (starting with the
 * lowest). This makes it very dअगरficult to पढ़ो the messages in the
 * right order from the chip. This is how we work around that problem:
 *
 * The first message goes पूर्णांकo mb nr. 1 and issues an पूर्णांकerrupt. All
 * rx पूर्णांकs are disabled in the पूर्णांकerrupt handler and a napi poll is
 * scheduled. We पढ़ो the mailbox, but करो _not_ re-enable the mb (to
 * receive another message).
 *
 *    lower mbxs      upper
 *     ____^______    __^__
 *    /           \  /     \
 * +-+-+-+-+-+-+-+-++-+-+-+-+
 * | |x|x|x|x|x|x|x|| | | | |
 * +-+-+-+-+-+-+-+-++-+-+-+-+
 *  0 0 0 0 0 0  0 0 0 0 1 1  \ mail
 *  0 1 2 3 4 5  6 7 8 9 0 1  / box
 *  ^
 *  |
 *   \
 *     unused, due to chip bug
 *
 * The variable priv->rx_next poपूर्णांकs to the next mailbox to पढ़ो a
 * message from. As दीर्घ we're in the lower mailboxes we just पढ़ो the
 * mailbox but not re-enable it.
 *
 * With completion of the last of the lower mailboxes, we re-enable the
 * whole first group, but जारी to look क्रम filled mailboxes in the
 * upper mailboxes. Imagine the second group like overflow mailboxes,
 * which takes CAN messages अगर the lower goup is full. While in the
 * upper group we re-enable the mailbox right after पढ़ोing it. Giving
 * the chip more room to store messages.
 *
 * After finishing we look again in the lower group अगर we've still
 * quota.
 *
 */
अटल पूर्णांक at91_poll_rx(काष्ठा net_device *dev, पूर्णांक quota)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_sr = at91_पढ़ो(priv, AT91_SR);
	स्थिर अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)&reg_sr;
	अचिन्हित पूर्णांक mb;
	पूर्णांक received = 0;

	अगर (priv->rx_next > get_mb_rx_low_last(priv) &&
	    reg_sr & get_mb_rx_low_mask(priv))
		netdev_info(dev,
			"order of incoming frames cannot be guaranteed\n");

 again:
	क्रम (mb = find_next_bit(addr, get_mb_tx_first(priv), priv->rx_next);
	     mb < get_mb_tx_first(priv) && quota > 0;
	     reg_sr = at91_पढ़ो(priv, AT91_SR),
	     mb = find_next_bit(addr, get_mb_tx_first(priv), ++priv->rx_next)) अणु
		at91_पढ़ो_msg(dev, mb);

		/* reactivate mailboxes */
		अगर (mb == get_mb_rx_low_last(priv))
			/* all lower mailboxed, अगर just finished it */
			at91_activate_rx_low(priv);
		अन्यथा अगर (mb > get_mb_rx_low_last(priv))
			/* only the mailbox we पढ़ो */
			at91_activate_rx_mb(priv, mb);

		received++;
		quota--;
	पूर्ण

	/* upper group completed, look again in lower */
	अगर (priv->rx_next > get_mb_rx_low_last(priv) &&
	    mb > get_mb_rx_last(priv)) अणु
		priv->rx_next = get_mb_rx_first(priv);
		अगर (quota > 0)
			जाओ again;
	पूर्ण

	वापस received;
पूर्ण

अटल व्योम at91_poll_err_frame(काष्ठा net_device *dev,
		काष्ठा can_frame *cf, u32 reg_sr)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);

	/* CRC error */
	अगर (reg_sr & AT91_IRQ_CERR) अणु
		netdev_dbg(dev, "CERR irq\n");
		dev->stats.rx_errors++;
		priv->can.can_stats.bus_error++;
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
	पूर्ण

	/* Stuffing Error */
	अगर (reg_sr & AT91_IRQ_SERR) अणु
		netdev_dbg(dev, "SERR irq\n");
		dev->stats.rx_errors++;
		priv->can.can_stats.bus_error++;
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
		cf->data[2] |= CAN_ERR_PROT_STUFF;
	पूर्ण

	/* Acknowledgement Error */
	अगर (reg_sr & AT91_IRQ_AERR) अणु
		netdev_dbg(dev, "AERR irq\n");
		dev->stats.tx_errors++;
		cf->can_id |= CAN_ERR_ACK;
	पूर्ण

	/* Form error */
	अगर (reg_sr & AT91_IRQ_FERR) अणु
		netdev_dbg(dev, "FERR irq\n");
		dev->stats.rx_errors++;
		priv->can.can_stats.bus_error++;
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
		cf->data[2] |= CAN_ERR_PROT_FORM;
	पूर्ण

	/* Bit Error */
	अगर (reg_sr & AT91_IRQ_BERR) अणु
		netdev_dbg(dev, "BERR irq\n");
		dev->stats.tx_errors++;
		priv->can.can_stats.bus_error++;
		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
		cf->data[2] |= CAN_ERR_PROT_BIT;
	पूर्ण
पूर्ण

अटल पूर्णांक at91_poll_err(काष्ठा net_device *dev, पूर्णांक quota, u32 reg_sr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;

	अगर (quota == 0)
		वापस 0;

	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस 0;

	at91_poll_err_frame(dev, cf, reg_sr);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += cf->len;
	netअगर_receive_skb(skb);

	वापस 1;
पूर्ण

अटल पूर्णांक at91_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा net_device *dev = napi->dev;
	स्थिर काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_sr = at91_पढ़ो(priv, AT91_SR);
	पूर्णांक work_करोne = 0;

	अगर (reg_sr & get_irq_mb_rx(priv))
		work_करोne += at91_poll_rx(dev, quota - work_करोne);

	/*
	 * The error bits are clear on पढ़ो,
	 * so use saved value from irq handler.
	 */
	reg_sr |= priv->reg_sr;
	अगर (reg_sr & AT91_IRQ_ERR_FRAME)
		work_करोne += at91_poll_err(dev, quota - work_करोne, reg_sr);

	अगर (work_करोne < quota) अणु
		/* enable IRQs क्रम frame errors and all mailboxes >= rx_next */
		u32 reg_ier = AT91_IRQ_ERR_FRAME;
		reg_ier |= get_irq_mb_rx(priv) & ~AT91_MB_MASK(priv->rx_next);

		napi_complete_करोne(napi, work_करोne);
		at91_ग_लिखो(priv, AT91_IER, reg_ier);
	पूर्ण

	वापस work_करोne;
पूर्ण

/*
 * theory of operation:
 *
 * priv->tx_echo holds the number of the oldest can_frame put क्रम
 * transmission पूर्णांकo the hardware, but not yet ACKed by the CAN tx
 * complete IRQ.
 *
 * We iterate from priv->tx_echo to priv->tx_next and check अगर the
 * packet has been transmitted, echo it back to the CAN framework. If
 * we discover a not yet transmitted package, stop looking क्रम more.
 *
 */
अटल व्योम at91_irq_tx(काष्ठा net_device *dev, u32 reg_sr)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_msr;
	अचिन्हित पूर्णांक mb;

	/* masking of reg_sr not needed, alपढ़ोy करोne by at91_irq */

	क्रम (/* nix */; (priv->tx_next - priv->tx_echo) > 0; priv->tx_echo++) अणु
		mb = get_tx_echo_mb(priv);

		/* no event in mailbox? */
		अगर (!(reg_sr & (1 << mb)))
			अवरोध;

		/* Disable irq क्रम this TX mailbox */
		at91_ग_लिखो(priv, AT91_IDR, 1 << mb);

		/*
		 * only echo अगर mailbox संकेतs us a transfer
		 * complete (MSR_MRDY). Otherwise it's a tansfer
		 * पात. "can_bus_off()" takes care about the skbs
		 * parked in the echo queue.
		 */
		reg_msr = at91_पढ़ो(priv, AT91_MSR(mb));
		अगर (likely(reg_msr & AT91_MSR_MRDY &&
			   ~reg_msr & AT91_MSR_MABT)) अणु
			/* _NOTE_: subtract AT91_MB_TX_FIRST offset from mb! */
			can_get_echo_skb(dev, mb - get_mb_tx_first(priv), शून्य);
			dev->stats.tx_packets++;
			can_led_event(dev, CAN_LED_EVENT_TX);
		पूर्ण
	पूर्ण

	/*
	 * restart queue अगर we करोn't have a wrap around but restart अगर
	 * we get a TX पूर्णांक क्रम the last can frame directly beक्रमe a
	 * wrap around.
	 */
	अगर ((priv->tx_next & get_next_mask(priv)) != 0 ||
	    (priv->tx_echo & get_next_mask(priv)) == 0)
		netअगर_wake_queue(dev);
पूर्ण

अटल व्योम at91_irq_err_state(काष्ठा net_device *dev,
		काष्ठा can_frame *cf, क्रमागत can_state new_state)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	u32 reg_idr = 0, reg_ier = 0;
	काष्ठा can_berr_counter bec;

	at91_get_berr_counter(dev, &bec);

	चयन (priv->can.state) अणु
	हाल CAN_STATE_ERROR_ACTIVE:
		/*
		 * from: ERROR_ACTIVE
		 * to  : ERROR_WARNING, ERROR_PASSIVE, BUS_OFF
		 * =>  : there was a warning पूर्णांक
		 */
		अगर (new_state >= CAN_STATE_ERROR_WARNING &&
		    new_state <= CAN_STATE_BUS_OFF) अणु
			netdev_dbg(dev, "Error Warning IRQ\n");
			priv->can.can_stats.error_warning++;

			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (bec.txerr > bec.rxerr) ?
				CAN_ERR_CRTL_TX_WARNING :
				CAN_ERR_CRTL_RX_WARNING;
		पूर्ण
		fallthrough;
	हाल CAN_STATE_ERROR_WARNING:
		/*
		 * from: ERROR_ACTIVE, ERROR_WARNING
		 * to  : ERROR_PASSIVE, BUS_OFF
		 * =>  : error passive पूर्णांक
		 */
		अगर (new_state >= CAN_STATE_ERROR_PASSIVE &&
		    new_state <= CAN_STATE_BUS_OFF) अणु
			netdev_dbg(dev, "Error Passive IRQ\n");
			priv->can.can_stats.error_passive++;

			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (bec.txerr > bec.rxerr) ?
				CAN_ERR_CRTL_TX_PASSIVE :
				CAN_ERR_CRTL_RX_PASSIVE;
		पूर्ण
		अवरोध;
	हाल CAN_STATE_BUS_OFF:
		/*
		 * from: BUS_OFF
		 * to  : ERROR_ACTIVE, ERROR_WARNING, ERROR_PASSIVE
		 */
		अगर (new_state <= CAN_STATE_ERROR_PASSIVE) अणु
			cf->can_id |= CAN_ERR_RESTARTED;

			netdev_dbg(dev, "restarted\n");
			priv->can.can_stats.restarts++;

			netअगर_carrier_on(dev);
			netअगर_wake_queue(dev);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण


	/* process state changes depending on the new state */
	चयन (new_state) अणु
	हाल CAN_STATE_ERROR_ACTIVE:
		/*
		 * actually we want to enable AT91_IRQ_WARN here, but
		 * it screws up the प्रणाली under certain
		 * circumstances. so just enable AT91_IRQ_ERRP, thus
		 * the "fallthrough"
		 */
		netdev_dbg(dev, "Error Active\n");
		cf->can_id |= CAN_ERR_PROT;
		cf->data[2] = CAN_ERR_PROT_ACTIVE;
		fallthrough;
	हाल CAN_STATE_ERROR_WARNING:
		reg_idr = AT91_IRQ_ERRA | AT91_IRQ_WARN | AT91_IRQ_BOFF;
		reg_ier = AT91_IRQ_ERRP;
		अवरोध;
	हाल CAN_STATE_ERROR_PASSIVE:
		reg_idr = AT91_IRQ_ERRA | AT91_IRQ_WARN | AT91_IRQ_ERRP;
		reg_ier = AT91_IRQ_BOFF;
		अवरोध;
	हाल CAN_STATE_BUS_OFF:
		reg_idr = AT91_IRQ_ERRA | AT91_IRQ_ERRP |
			AT91_IRQ_WARN | AT91_IRQ_BOFF;
		reg_ier = 0;

		cf->can_id |= CAN_ERR_BUSOFF;

		netdev_dbg(dev, "bus-off\n");
		netअगर_carrier_off(dev);
		priv->can.can_stats.bus_off++;

		/* turn off chip, अगर restart is disabled */
		अगर (!priv->can.restart_ms) अणु
			at91_chip_stop(dev, CAN_STATE_BUS_OFF);
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	at91_ग_लिखो(priv, AT91_IDR, reg_idr);
	at91_ग_लिखो(priv, AT91_IER, reg_ier);
पूर्ण

अटल पूर्णांक at91_get_state_by_bec(स्थिर काष्ठा net_device *dev,
		क्रमागत can_state *state)
अणु
	काष्ठा can_berr_counter bec;
	पूर्णांक err;

	err = at91_get_berr_counter(dev, &bec);
	अगर (err)
		वापस err;

	अगर (bec.txerr < 96 && bec.rxerr < 96)
		*state = CAN_STATE_ERROR_ACTIVE;
	अन्यथा अगर (bec.txerr < 128 && bec.rxerr < 128)
		*state = CAN_STATE_ERROR_WARNING;
	अन्यथा अगर (bec.txerr < 256 && bec.rxerr < 256)
		*state = CAN_STATE_ERROR_PASSIVE;
	अन्यथा
		*state = CAN_STATE_BUS_OFF;

	वापस 0;
पूर्ण


अटल व्योम at91_irq_err(काष्ठा net_device *dev)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	क्रमागत can_state new_state;
	u32 reg_sr;
	पूर्णांक err;

	अगर (at91_is_sam9263(priv)) अणु
		reg_sr = at91_पढ़ो(priv, AT91_SR);

		/* we need to look at the unmasked reg_sr */
		अगर (unlikely(reg_sr & AT91_IRQ_BOFF))
			new_state = CAN_STATE_BUS_OFF;
		अन्यथा अगर (unlikely(reg_sr & AT91_IRQ_ERRP))
			new_state = CAN_STATE_ERROR_PASSIVE;
		अन्यथा अगर (unlikely(reg_sr & AT91_IRQ_WARN))
			new_state = CAN_STATE_ERROR_WARNING;
		अन्यथा अगर (likely(reg_sr & AT91_IRQ_ERRA))
			new_state = CAN_STATE_ERROR_ACTIVE;
		अन्यथा अणु
			netdev_err(dev, "BUG! hardware in undefined state\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = at91_get_state_by_bec(dev, &new_state);
		अगर (err)
			वापस;
	पूर्ण

	/* state hasn't changed */
	अगर (likely(new_state == priv->can.state))
		वापस;

	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस;

	at91_irq_err_state(dev, cf, new_state);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += cf->len;
	netअगर_rx(skb);

	priv->can.state = new_state;
पूर्ण

/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t at91_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा at91_priv *priv = netdev_priv(dev);
	irqवापस_t handled = IRQ_NONE;
	u32 reg_sr, reg_imr;

	reg_sr = at91_पढ़ो(priv, AT91_SR);
	reg_imr = at91_पढ़ो(priv, AT91_IMR);

	/* Ignore masked पूर्णांकerrupts */
	reg_sr &= reg_imr;
	अगर (!reg_sr)
		जाओ निकास;

	handled = IRQ_HANDLED;

	/* Receive or error पूर्णांकerrupt? -> napi */
	अगर (reg_sr & (get_irq_mb_rx(priv) | AT91_IRQ_ERR_FRAME)) अणु
		/*
		 * The error bits are clear on पढ़ो,
		 * save क्रम later use.
		 */
		priv->reg_sr = reg_sr;
		at91_ग_लिखो(priv, AT91_IDR,
			   get_irq_mb_rx(priv) | AT91_IRQ_ERR_FRAME);
		napi_schedule(&priv->napi);
	पूर्ण

	/* Transmission complete पूर्णांकerrupt */
	अगर (reg_sr & get_irq_mb_tx(priv))
		at91_irq_tx(dev, reg_sr);

	at91_irq_err(dev);

 निकास:
	वापस handled;
पूर्ण

अटल पूर्णांक at91_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		वापस err;

	/* check or determine and set bitसमय */
	err = खोलो_candev(dev);
	अगर (err)
		जाओ out;

	/* रेजिस्टर पूर्णांकerrupt handler */
	अगर (request_irq(dev->irq, at91_irq, IRQF_SHARED,
			dev->name, dev)) अणु
		err = -EAGAIN;
		जाओ out_बंद;
	पूर्ण

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	/* start chip and queuing */
	at91_chip_start(dev);
	napi_enable(&priv->napi);
	netअगर_start_queue(dev);

	वापस 0;

 out_बंद:
	बंद_candev(dev);
 out:
	clk_disable_unprepare(priv->clk);

	वापस err;
पूर्ण

/*
 * stop CAN bus activity
 */
अटल पूर्णांक at91_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा at91_priv *priv = netdev_priv(dev);

	netअगर_stop_queue(dev);
	napi_disable(&priv->napi);
	at91_chip_stop(dev, CAN_STATE_STOPPED);

	मुक्त_irq(dev->irq, dev);
	clk_disable_unprepare(priv->clk);

	बंद_candev(dev);

	can_led_event(dev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	चयन (mode) अणु
	हाल CAN_MODE_START:
		at91_chip_start(dev);
		netअगर_wake_queue(dev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops at91_netdev_ops = अणु
	.nकरो_खोलो	= at91_खोलो,
	.nकरो_stop	= at91_बंद,
	.nकरो_start_xmit	= at91_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल sमाप_प्रकार at91_sysfs_show_mb0_id(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा at91_priv *priv = netdev_priv(to_net_dev(dev));

	अगर (priv->mb0_id & CAN_EFF_FLAG)
		वापस snम_लिखो(buf, PAGE_SIZE, "0x%08x\n", priv->mb0_id);
	अन्यथा
		वापस snम_लिखो(buf, PAGE_SIZE, "0x%03x\n", priv->mb0_id);
पूर्ण

अटल sमाप_प्रकार at91_sysfs_set_mb0_id(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	काष्ठा at91_priv *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ can_id;
	sमाप_प्रकार ret;
	पूर्णांक err;

	rtnl_lock();

	अगर (ndev->flags & IFF_UP) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	err = kम_से_अदीर्घ(buf, 0, &can_id);
	अगर (err) अणु
		ret = err;
		जाओ out;
	पूर्ण

	अगर (can_id & CAN_EFF_FLAG)
		can_id &= CAN_EFF_MASK | CAN_EFF_FLAG;
	अन्यथा
		can_id &= CAN_SFF_MASK;

	priv->mb0_id = can_id;
	ret = count;

 out:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल DEVICE_ATTR(mb0_id, 0644, at91_sysfs_show_mb0_id, at91_sysfs_set_mb0_id);

अटल काष्ठा attribute *at91_sysfs_attrs[] = अणु
	&dev_attr_mb0_id.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group at91_sysfs_attr_group = अणु
	.attrs = at91_sysfs_attrs,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id at91_can_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91sam9x5-can",
		.data = &at91_at91sam9x5_data,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9263-can",
		.data = &at91_at91sam9263_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at91_can_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा at91_devtype_data *at91_can_get_driver_data(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(at91_can_dt_ids, pdev->dev.of_node);
		अगर (!match) अणु
			dev_err(&pdev->dev, "no matching node found in dtb\n");
			वापस शून्य;
		पूर्ण
		वापस (स्थिर काष्ठा at91_devtype_data *)match->data;
	पूर्ण
	वापस (स्थिर काष्ठा at91_devtype_data *)
		platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

अटल पूर्णांक at91_can_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा at91_devtype_data *devtype_data;
	काष्ठा net_device *dev;
	काष्ठा at91_priv *priv;
	काष्ठा resource *res;
	काष्ठा clk *clk;
	व्योम __iomem *addr;
	पूर्णांक err, irq;

	devtype_data = at91_can_get_driver_data(pdev);
	अगर (!devtype_data) अणु
		dev_err(&pdev->dev, "no driver data\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	clk = clk_get(&pdev->dev, "can_clk");
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "no clock defined\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!res || irq <= 0) अणु
		err = -ENODEV;
		जाओ निकास_put;
	पूर्ण

	अगर (!request_mem_region(res->start,
				resource_size(res),
				pdev->name)) अणु
		err = -EBUSY;
		जाओ निकास_put;
	पूर्ण

	addr = ioremap(res->start, resource_size(res));
	अगर (!addr) अणु
		err = -ENOMEM;
		जाओ निकास_release;
	पूर्ण

	dev = alloc_candev(माप(काष्ठा at91_priv),
			   1 << devtype_data->tx_shअगरt);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ निकास_iounmap;
	पूर्ण

	dev->netdev_ops	= &at91_netdev_ops;
	dev->irq = irq;
	dev->flags |= IFF_ECHO;

	priv = netdev_priv(dev);
	priv->can.घड़ी.freq = clk_get_rate(clk);
	priv->can.bittiming_स्थिर = &at91_bittiming_स्थिर;
	priv->can.करो_set_mode = at91_set_mode;
	priv->can.करो_get_berr_counter = at91_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_LISTENONLY;
	priv->reg_base = addr;
	priv->devtype_data = *devtype_data;
	priv->clk = clk;
	priv->pdata = dev_get_platdata(&pdev->dev);
	priv->mb0_id = 0x7ff;

	netअगर_napi_add(dev, &priv->napi, at91_poll, get_mb_rx_num(priv));

	अगर (at91_is_sam9263(priv))
		dev->sysfs_groups[0] = &at91_sysfs_attr_group;

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = रेजिस्टर_candev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "registering netdev failed\n");
		जाओ निकास_मुक्त;
	पूर्ण

	devm_can_led_init(dev);

	dev_info(&pdev->dev, "device registered (reg_base=%p, irq=%d)\n",
		 priv->reg_base, dev->irq);

	वापस 0;

 निकास_मुक्त:
	मुक्त_candev(dev);
 निकास_iounmap:
	iounmap(addr);
 निकास_release:
	release_mem_region(res->start, resource_size(res));
 निकास_put:
	clk_put(clk);
 निकास:
	वापस err;
पूर्ण

अटल पूर्णांक at91_can_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_priv *priv = netdev_priv(dev);
	काष्ठा resource *res;

	unरेजिस्टर_netdev(dev);

	iounmap(priv->reg_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	clk_put(priv->clk);

	मुक्त_candev(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id at91_can_id_table[] = अणु
	अणु
		.name = "at91sam9x5_can",
		.driver_data = (kernel_uदीर्घ_t)&at91_at91sam9x5_data,
	पूर्ण, अणु
		.name = "at91_can",
		.driver_data = (kernel_uदीर्घ_t)&at91_at91sam9263_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, at91_can_id_table);

अटल काष्ठा platक्रमm_driver at91_can_driver = अणु
	.probe = at91_can_probe,
	.हटाओ = at91_can_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = of_match_ptr(at91_can_dt_ids),
	पूर्ण,
	.id_table = at91_can_id_table,
पूर्ण;

module_platक्रमm_driver(at91_can_driver);

MODULE_AUTHOR("Marc Kleine-Budde <mkl@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(KBUILD_MODNAME " CAN netdevice driver");
