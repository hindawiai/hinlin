<शैली गुरु>
/*
 * TI HECC (CAN) device driver
 *
 * This driver supports TI's HECC (High End CAN Controller module) and the
 * specs क्रम the same is available at <http://www.ti.com>
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 * Copyright (C) 2019 Jeroen Hofstee <jhofstee@victronenergy.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed as is WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>
#समावेश <linux/can/rx-offload.h>

#घोषणा DRV_NAME "ti_hecc"
#घोषणा HECC_MODULE_VERSION     "0.7"
MODULE_VERSION(HECC_MODULE_VERSION);
#घोषणा DRV_DESC "TI High End CAN Controller Driver " HECC_MODULE_VERSION

/* TX / RX Mailbox Configuration */
#घोषणा HECC_MAX_MAILBOXES	32	/* hardware mailboxes - करो not change */
#घोषणा MAX_TX_PRIO		0x3F	/* hardware value - करो not change */

/* Important Note: TX mailbox configuration
 * TX mailboxes should be restricted to the number of SKB buffers to aव्योम
 * मुख्यtaining SKB buffers separately. TX mailboxes should be a घातer of 2
 * क्रम the mailbox logic to work.  Top mailbox numbers are reserved क्रम RX
 * and lower mailboxes क्रम TX.
 *
 * HECC_MAX_TX_MBOX	HECC_MB_TX_SHIFT
 * 4 (शेष)		2
 * 8			3
 * 16			4
 */
#घोषणा HECC_MB_TX_SHIFT	2 /* as per table above */
#घोषणा HECC_MAX_TX_MBOX	BIT(HECC_MB_TX_SHIFT)

#घोषणा HECC_TX_PRIO_SHIFT	(HECC_MB_TX_SHIFT)
#घोषणा HECC_TX_PRIO_MASK	(MAX_TX_PRIO << HECC_MB_TX_SHIFT)
#घोषणा HECC_TX_MB_MASK		(HECC_MAX_TX_MBOX - 1)
#घोषणा HECC_TX_MASK		((HECC_MAX_TX_MBOX - 1) | HECC_TX_PRIO_MASK)

/* RX mailbox configuration
 *
 * The reमुख्यing mailboxes are used क्रम reception and are delivered
 * based on their बारtamp, to aव्योम a hardware race when CANME is
 * changed जबतक CAN-bus traffic is being received.
 */
#घोषणा HECC_MAX_RX_MBOX	(HECC_MAX_MAILBOXES - HECC_MAX_TX_MBOX)
#घोषणा HECC_RX_FIRST_MBOX	(HECC_MAX_MAILBOXES - 1)
#घोषणा HECC_RX_LAST_MBOX	(HECC_MAX_TX_MBOX)

/* TI HECC module रेजिस्टरs */
#घोषणा HECC_CANME		0x0	/* Mailbox enable */
#घोषणा HECC_CANMD		0x4	/* Mailbox direction */
#घोषणा HECC_CANTRS		0x8	/* Transmit request set */
#घोषणा HECC_CANTRR		0xC	/* Transmit request */
#घोषणा HECC_CANTA		0x10	/* Transmission acknowledge */
#घोषणा HECC_CANAA		0x14	/* Abort acknowledge */
#घोषणा HECC_CANRMP		0x18	/* Receive message pending */
#घोषणा HECC_CANRML		0x1C	/* Receive message lost */
#घोषणा HECC_CANRFP		0x20	/* Remote frame pending */
#घोषणा HECC_CANGAM		0x24	/* SECC only:Global acceptance mask */
#घोषणा HECC_CANMC		0x28	/* Master control */
#घोषणा HECC_CANBTC		0x2C	/* Bit timing configuration */
#घोषणा HECC_CANES		0x30	/* Error and status */
#घोषणा HECC_CANTEC		0x34	/* Transmit error counter */
#घोषणा HECC_CANREC		0x38	/* Receive error counter */
#घोषणा HECC_CANGIF0		0x3C	/* Global पूर्णांकerrupt flag 0 */
#घोषणा HECC_CANGIM		0x40	/* Global पूर्णांकerrupt mask */
#घोषणा HECC_CANGIF1		0x44	/* Global पूर्णांकerrupt flag 1 */
#घोषणा HECC_CANMIM		0x48	/* Mailbox पूर्णांकerrupt mask */
#घोषणा HECC_CANMIL		0x4C	/* Mailbox पूर्णांकerrupt level */
#घोषणा HECC_CANOPC		0x50	/* Overग_लिखो protection control */
#घोषणा HECC_CANTIOC		0x54	/* Transmit I/O control */
#घोषणा HECC_CANRIOC		0x58	/* Receive I/O control */
#घोषणा HECC_CANLNT		0x5C	/* HECC only: Local network समय */
#घोषणा HECC_CANTOC		0x60	/* HECC only: Time-out control */
#घोषणा HECC_CANTOS		0x64	/* HECC only: Time-out status */
#घोषणा HECC_CANTIOCE		0x68	/* SCC only:Enhanced TX I/O control */
#घोषणा HECC_CANRIOCE		0x6C	/* SCC only:Enhanced RX I/O control */

/* TI HECC RAM रेजिस्टरs */
#घोषणा HECC_CANMOTS		0x80	/* Message object समय stamp */

/* Mailbox रेजिस्टरs */
#घोषणा HECC_CANMID		0x0
#घोषणा HECC_CANMCF		0x4
#घोषणा HECC_CANMDL		0x8
#घोषणा HECC_CANMDH		0xC

#घोषणा HECC_SET_REG		0xFFFFFFFF
#घोषणा HECC_CANID_MASK		0x3FF	/* 18 bits mask क्रम extended id's */
#घोषणा HECC_CCE_WAIT_COUNT     100	/* Wait क्रम ~1 sec क्रम CCE bit */

#घोषणा HECC_CANMC_SCM		BIT(13)	/* SCC compat mode */
#घोषणा HECC_CANMC_CCR		BIT(12)	/* Change config request */
#घोषणा HECC_CANMC_PDR		BIT(11)	/* Local Power करोwn - क्रम sleep mode */
#घोषणा HECC_CANMC_ABO		BIT(7)	/* Auto Bus On */
#घोषणा HECC_CANMC_STM		BIT(6)	/* Self test mode - loopback */
#घोषणा HECC_CANMC_SRES		BIT(5)	/* Software reset */

#घोषणा HECC_CANTIOC_EN		BIT(3)	/* Enable CAN TX I/O pin */
#घोषणा HECC_CANRIOC_EN		BIT(3)	/* Enable CAN RX I/O pin */

#घोषणा HECC_CANMID_IDE		BIT(31)	/* Extended frame क्रमmat */
#घोषणा HECC_CANMID_AME		BIT(30)	/* Acceptance mask enable */
#घोषणा HECC_CANMID_AAM		BIT(29)	/* Auto answer mode */

#घोषणा HECC_CANES_FE		BIT(24)	/* क्रमm error */
#घोषणा HECC_CANES_BE		BIT(23)	/* bit error */
#घोषणा HECC_CANES_SA1		BIT(22)	/* stuck at करोminant error */
#घोषणा HECC_CANES_CRCE		BIT(21)	/* CRC error */
#घोषणा HECC_CANES_SE		BIT(20)	/* stuff bit error */
#घोषणा HECC_CANES_ACKE		BIT(19)	/* ack error */
#घोषणा HECC_CANES_BO		BIT(18)	/* Bus off status */
#घोषणा HECC_CANES_EP		BIT(17)	/* Error passive status */
#घोषणा HECC_CANES_EW		BIT(16)	/* Error warning status */
#घोषणा HECC_CANES_SMA		BIT(5)	/* suspend mode ack */
#घोषणा HECC_CANES_CCE		BIT(4)	/* Change config enabled */
#घोषणा HECC_CANES_PDA		BIT(3)	/* Power करोwn mode ack */

#घोषणा HECC_CANBTC_SAM		BIT(7)	/* sample poपूर्णांकs */

#घोषणा HECC_BUS_ERROR		(HECC_CANES_FE | HECC_CANES_BE |\
				HECC_CANES_CRCE | HECC_CANES_SE |\
				HECC_CANES_ACKE)
#घोषणा HECC_CANES_FLAGS	(HECC_BUS_ERROR | HECC_CANES_BO |\
				HECC_CANES_EP | HECC_CANES_EW)

#घोषणा HECC_CANMCF_RTR		BIT(4)	/* Remote transmit request */

#घोषणा HECC_CANGIF_MAIF	BIT(17)	/* Message alarm पूर्णांकerrupt */
#घोषणा HECC_CANGIF_TCOIF	BIT(16) /* Timer counter overflow पूर्णांक */
#घोषणा HECC_CANGIF_GMIF	BIT(15)	/* Global mailbox पूर्णांकerrupt */
#घोषणा HECC_CANGIF_AAIF	BIT(14)	/* Abort ack पूर्णांकerrupt */
#घोषणा HECC_CANGIF_WDIF	BIT(13)	/* Write denied पूर्णांकerrupt */
#घोषणा HECC_CANGIF_WUIF	BIT(12)	/* Wake up पूर्णांकerrupt */
#घोषणा HECC_CANGIF_RMLIF	BIT(11)	/* Receive message lost पूर्णांकerrupt */
#घोषणा HECC_CANGIF_BOIF	BIT(10)	/* Bus off पूर्णांकerrupt */
#घोषणा HECC_CANGIF_EPIF	BIT(9)	/* Error passive पूर्णांकerrupt */
#घोषणा HECC_CANGIF_WLIF	BIT(8)	/* Warning level पूर्णांकerrupt */
#घोषणा HECC_CANGIF_MBOX_MASK	0x1F	/* Mailbox number mask */
#घोषणा HECC_CANGIM_I1EN	BIT(1)	/* Int line 1 enable */
#घोषणा HECC_CANGIM_I0EN	BIT(0)	/* Int line 0 enable */
#घोषणा HECC_CANGIM_DEF_MASK	0x700	/* only busoff/warning/passive */
#घोषणा HECC_CANGIM_SIL		BIT(2)	/* प्रणाली पूर्णांकerrupts to पूर्णांक line 1 */

/* CAN Bittiming स्थिरants as per HECC specs */
अटल स्थिर काष्ठा can_bittiming_स्थिर ti_hecc_bittiming_स्थिर = अणु
	.name = DRV_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

काष्ठा ti_hecc_priv अणु
	काष्ठा can_priv can;	/* MUST be first member/field */
	काष्ठा can_rx_offload offload;
	काष्ठा net_device *ndev;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	व्योम __iomem *hecc_ram;
	व्योम __iomem *mbx;
	bool use_hecc1पूर्णांक;
	spinlock_t mbx_lock; /* CANME रेजिस्टर needs protection */
	u32 tx_head;
	u32 tx_tail;
	काष्ठा regulator *reg_xceiver;
पूर्ण;

अटल अंतरभूत पूर्णांक get_tx_head_mb(काष्ठा ti_hecc_priv *priv)
अणु
	वापस priv->tx_head & HECC_TX_MB_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक get_tx_tail_mb(काष्ठा ti_hecc_priv *priv)
अणु
	वापस priv->tx_tail & HECC_TX_MB_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक get_tx_head_prio(काष्ठा ti_hecc_priv *priv)
अणु
	वापस (priv->tx_head >> HECC_TX_PRIO_SHIFT) & MAX_TX_PRIO;
पूर्ण

अटल अंतरभूत व्योम hecc_ग_लिखो_lam(काष्ठा ti_hecc_priv *priv, u32 mbxno, u32 val)
अणु
	__raw_ग_लिखोl(val, priv->hecc_ram + mbxno * 4);
पूर्ण

अटल अंतरभूत u32 hecc_पढ़ो_stamp(काष्ठा ti_hecc_priv *priv, u32 mbxno)
अणु
	वापस __raw_पढ़ोl(priv->hecc_ram + HECC_CANMOTS + mbxno * 4);
पूर्ण

अटल अंतरभूत व्योम hecc_ग_लिखो_mbx(काष्ठा ti_hecc_priv *priv, u32 mbxno,
				  u32 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, priv->mbx + mbxno * 0x10 + reg);
पूर्ण

अटल अंतरभूत u32 hecc_पढ़ो_mbx(काष्ठा ti_hecc_priv *priv, u32 mbxno, u32 reg)
अणु
	वापस __raw_पढ़ोl(priv->mbx + mbxno * 0x10 + reg);
पूर्ण

अटल अंतरभूत व्योम hecc_ग_लिखो(काष्ठा ti_hecc_priv *priv, u32 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, priv->base + reg);
पूर्ण

अटल अंतरभूत u32 hecc_पढ़ो(काष्ठा ti_hecc_priv *priv, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(priv->base + reg);
पूर्ण

अटल अंतरभूत व्योम hecc_set_bit(काष्ठा ti_hecc_priv *priv, पूर्णांक reg,
				u32 bit_mask)
अणु
	hecc_ग_लिखो(priv, reg, hecc_पढ़ो(priv, reg) | bit_mask);
पूर्ण

अटल अंतरभूत व्योम hecc_clear_bit(काष्ठा ti_hecc_priv *priv, पूर्णांक reg,
				  u32 bit_mask)
अणु
	hecc_ग_लिखो(priv, reg, hecc_पढ़ो(priv, reg) & ~bit_mask);
पूर्ण

अटल अंतरभूत u32 hecc_get_bit(काष्ठा ti_hecc_priv *priv, पूर्णांक reg, u32 bit_mask)
अणु
	वापस (hecc_पढ़ो(priv, reg) & bit_mask) ? 1 : 0;
पूर्ण

अटल पूर्णांक ti_hecc_set_btc(काष्ठा ti_hecc_priv *priv)
अणु
	काष्ठा can_bittiming *bit_timing = &priv->can.bittiming;
	u32 can_btc;

	can_btc = (bit_timing->phase_seg2 - 1) & 0x7;
	can_btc |= ((bit_timing->phase_seg1 + bit_timing->prop_seg - 1)
			& 0xF) << 3;
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) अणु
		अगर (bit_timing->brp > 4)
			can_btc |= HECC_CANBTC_SAM;
		अन्यथा
			netdev_warn(priv->ndev,
				    "WARN: Triple sampling not set due to h/w limitations");
	पूर्ण
	can_btc |= ((bit_timing->sjw - 1) & 0x3) << 8;
	can_btc |= ((bit_timing->brp - 1) & 0xFF) << 16;

	/* ERM being set to 0 by शेष meaning resync at falling edge */

	hecc_ग_लिखो(priv, HECC_CANBTC, can_btc);
	netdev_info(priv->ndev, "setting CANBTC=%#x\n", can_btc);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_hecc_transceiver_चयन(स्थिर काष्ठा ti_hecc_priv *priv,
				      पूर्णांक on)
अणु
	अगर (!priv->reg_xceiver)
		वापस 0;

	अगर (on)
		वापस regulator_enable(priv->reg_xceiver);
	अन्यथा
		वापस regulator_disable(priv->reg_xceiver);
पूर्ण

अटल व्योम ti_hecc_reset(काष्ठा net_device *ndev)
अणु
	u32 cnt;
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);

	netdev_dbg(ndev, "resetting hecc ...\n");
	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_SRES);

	/* Set change control request and रुको till enabled */
	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_CCR);

	/* INFO: It has been observed that at बार CCE bit may not be
	 * set and hw seems to be ok even अगर this bit is not set so
	 * timing out with a timing of 1ms to respect the specs
	 */
	cnt = HECC_CCE_WAIT_COUNT;
	जबतक (!hecc_get_bit(priv, HECC_CANES, HECC_CANES_CCE) && cnt != 0) अणु
		--cnt;
		udelay(10);
	पूर्ण

	/* Note: On HECC, BTC can be programmed only in initialization mode, so
	 * it is expected that the can bittiming parameters are set via ip
	 * utility beक्रमe the device is खोलोed
	 */
	ti_hecc_set_btc(priv);

	/* Clear CCR (and CANMC रेजिस्टर) and रुको क्रम CCE = 0 enable */
	hecc_ग_लिखो(priv, HECC_CANMC, 0);

	/* INFO: CAN net stack handles bus off and hence disabling स्वतः-bus-on
	 * hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_ABO);
	 */

	/* INFO: It has been observed that at बार CCE bit may not be
	 * set and hw seems to be ok even अगर this bit is not set so
	 */
	cnt = HECC_CCE_WAIT_COUNT;
	जबतक (hecc_get_bit(priv, HECC_CANES, HECC_CANES_CCE) && cnt != 0) अणु
		--cnt;
		udelay(10);
	पूर्ण

	/* Enable TX and RX I/O Control pins */
	hecc_ग_लिखो(priv, HECC_CANTIOC, HECC_CANTIOC_EN);
	hecc_ग_लिखो(priv, HECC_CANRIOC, HECC_CANRIOC_EN);

	/* Clear रेजिस्टरs क्रम clean operation */
	hecc_ग_लिखो(priv, HECC_CANTA, HECC_SET_REG);
	hecc_ग_लिखो(priv, HECC_CANRMP, HECC_SET_REG);
	hecc_ग_लिखो(priv, HECC_CANGIF0, HECC_SET_REG);
	hecc_ग_लिखो(priv, HECC_CANGIF1, HECC_SET_REG);
	hecc_ग_लिखो(priv, HECC_CANME, 0);
	hecc_ग_लिखो(priv, HECC_CANMD, 0);

	/* SCC compat mode NOT supported (and not needed too) */
	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_SCM);
पूर्ण

अटल व्योम ti_hecc_start(काष्ठा net_device *ndev)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);
	u32 cnt, mbxno, mbx_mask;

	/* put HECC in initialization mode and set btc */
	ti_hecc_reset(ndev);

	priv->tx_head = HECC_TX_MASK;
	priv->tx_tail = HECC_TX_MASK;

	/* Enable local and global acceptance mask रेजिस्टरs */
	hecc_ग_लिखो(priv, HECC_CANGAM, HECC_SET_REG);

	/* Prepare configured mailboxes to receive messages */
	क्रम (cnt = 0; cnt < HECC_MAX_RX_MBOX; cnt++) अणु
		mbxno = HECC_MAX_MAILBOXES - 1 - cnt;
		mbx_mask = BIT(mbxno);
		hecc_clear_bit(priv, HECC_CANME, mbx_mask);
		hecc_ग_लिखो_mbx(priv, mbxno, HECC_CANMID, HECC_CANMID_AME);
		hecc_ग_लिखो_lam(priv, mbxno, HECC_SET_REG);
		hecc_set_bit(priv, HECC_CANMD, mbx_mask);
		hecc_set_bit(priv, HECC_CANME, mbx_mask);
		hecc_set_bit(priv, HECC_CANMIM, mbx_mask);
	पूर्ण

	/* Enable tx पूर्णांकerrupts */
	hecc_set_bit(priv, HECC_CANMIM, BIT(HECC_MAX_TX_MBOX) - 1);

	/* Prevent message over-ग_लिखो to create a rx fअगरo, but not क्रम
	 * the lowest priority mailbox, since that allows detecting
	 * overflows instead of the hardware silently dropping the
	 * messages.
	 */
	mbx_mask = ~BIT(HECC_RX_LAST_MBOX);
	hecc_ग_लिखो(priv, HECC_CANOPC, mbx_mask);

	/* Enable पूर्णांकerrupts */
	अगर (priv->use_hecc1पूर्णांक) अणु
		hecc_ग_लिखो(priv, HECC_CANMIL, HECC_SET_REG);
		hecc_ग_लिखो(priv, HECC_CANGIM, HECC_CANGIM_DEF_MASK |
			HECC_CANGIM_I1EN | HECC_CANGIM_SIL);
	पूर्ण अन्यथा अणु
		hecc_ग_लिखो(priv, HECC_CANMIL, 0);
		hecc_ग_लिखो(priv, HECC_CANGIM,
			   HECC_CANGIM_DEF_MASK | HECC_CANGIM_I0EN);
	पूर्ण
	priv->can.state = CAN_STATE_ERROR_ACTIVE;
पूर्ण

अटल व्योम ti_hecc_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);

	/* Disable the CPK; stop sending, erroring and acking */
	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_CCR);

	/* Disable पूर्णांकerrupts and disable mailboxes */
	hecc_ग_लिखो(priv, HECC_CANGIM, 0);
	hecc_ग_लिखो(priv, HECC_CANMIM, 0);
	hecc_ग_लिखो(priv, HECC_CANME, 0);
	priv->can.state = CAN_STATE_STOPPED;
पूर्ण

अटल पूर्णांक ti_hecc_करो_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	पूर्णांक ret = 0;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		ti_hecc_start(ndev);
		netअगर_wake_queue(ndev);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ti_hecc_get_berr_counter(स्थिर काष्ठा net_device *ndev,
				    काष्ठा can_berr_counter *bec)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);

	bec->txerr = hecc_पढ़ो(priv, HECC_CANTEC);
	bec->rxerr = hecc_पढ़ो(priv, HECC_CANREC);

	वापस 0;
पूर्ण

/* ti_hecc_xmit: HECC Transmit
 *
 * The transmit mailboxes start from 0 to HECC_MAX_TX_MBOX. In HECC the
 * priority of the mailbox क्रम transmission is dependent upon priority setting
 * field in mailbox रेजिस्टरs. The mailbox with highest value in priority field
 * is transmitted first. Only when two mailboxes have the same value in
 * priority field the highest numbered mailbox is transmitted first.
 *
 * To utilize the HECC priority feature as described above we start with the
 * highest numbered mailbox with highest priority level and move on to the next
 * mailbox with the same priority level and so on. Once we loop through all the
 * transmit mailboxes we choose the next priority level (lower) and so on
 * until we reach the lowest priority level on the lowest numbered mailbox
 * when we stop transmission until all mailboxes are transmitted and then
 * restart at highest numbered mailbox with highest priority.
 *
 * Two counters (head and tail) are used to track the next mailbox to transmit
 * and to track the echo buffer क्रम alपढ़ोy transmitted mailbox. The queue
 * is stopped when all the mailboxes are busy or when there is a priority
 * value roll-over happens.
 */
अटल netdev_tx_t ti_hecc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	u32 mbxno, mbx_mask, data;
	अचिन्हित दीर्घ flags;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	mbxno = get_tx_head_mb(priv);
	mbx_mask = BIT(mbxno);
	spin_lock_irqsave(&priv->mbx_lock, flags);
	अगर (unlikely(hecc_पढ़ो(priv, HECC_CANME) & mbx_mask)) अणु
		spin_unlock_irqrestore(&priv->mbx_lock, flags);
		netअगर_stop_queue(ndev);
		netdev_err(priv->ndev,
			   "BUG: TX mbx not ready tx_head=%08X, tx_tail=%08X\n",
			   priv->tx_head, priv->tx_tail);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	spin_unlock_irqrestore(&priv->mbx_lock, flags);

	/* Prepare mailbox क्रम transmission */
	data = cf->len | (get_tx_head_prio(priv) << 8);
	अगर (cf->can_id & CAN_RTR_FLAG) /* Remote transmission request */
		data |= HECC_CANMCF_RTR;
	hecc_ग_लिखो_mbx(priv, mbxno, HECC_CANMCF, data);

	अगर (cf->can_id & CAN_EFF_FLAG) /* Extended frame क्रमmat */
		data = (cf->can_id & CAN_EFF_MASK) | HECC_CANMID_IDE;
	अन्यथा /* Standard frame क्रमmat */
		data = (cf->can_id & CAN_SFF_MASK) << 18;
	hecc_ग_लिखो_mbx(priv, mbxno, HECC_CANMID, data);
	hecc_ग_लिखो_mbx(priv, mbxno, HECC_CANMDL,
		       be32_to_cpu(*(__be32 *)(cf->data)));
	अगर (cf->len > 4)
		hecc_ग_लिखो_mbx(priv, mbxno, HECC_CANMDH,
			       be32_to_cpu(*(__be32 *)(cf->data + 4)));
	अन्यथा
		*(u32 *)(cf->data + 4) = 0;
	can_put_echo_skb(skb, ndev, mbxno, 0);

	spin_lock_irqsave(&priv->mbx_lock, flags);
	--priv->tx_head;
	अगर ((hecc_पढ़ो(priv, HECC_CANME) & BIT(get_tx_head_mb(priv))) ||
	    (priv->tx_head & HECC_TX_MASK) == HECC_TX_MASK) अणु
		netअगर_stop_queue(ndev);
	पूर्ण
	hecc_set_bit(priv, HECC_CANME, mbx_mask);
	spin_unlock_irqrestore(&priv->mbx_lock, flags);

	hecc_ग_लिखो(priv, HECC_CANTRS, mbx_mask);

	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत
काष्ठा ti_hecc_priv *rx_offload_to_priv(काष्ठा can_rx_offload *offload)
अणु
	वापस container_of(offload, काष्ठा ti_hecc_priv, offload);
पूर्ण

अटल काष्ठा sk_buff *ti_hecc_mailbox_पढ़ो(काष्ठा can_rx_offload *offload,
					    अचिन्हित पूर्णांक mbxno, u32 *बारtamp,
					    bool drop)
अणु
	काष्ठा ti_hecc_priv *priv = rx_offload_to_priv(offload);
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	u32 data, mbx_mask;

	mbx_mask = BIT(mbxno);

	अगर (unlikely(drop)) अणु
		skb = ERR_PTR(-ENOBUFS);
		जाओ mark_as_पढ़ो;
	पूर्ण

	skb = alloc_can_skb(offload->dev, &cf);
	अगर (unlikely(!skb)) अणु
		skb = ERR_PTR(-ENOMEM);
		जाओ mark_as_पढ़ो;
	पूर्ण

	data = hecc_पढ़ो_mbx(priv, mbxno, HECC_CANMID);
	अगर (data & HECC_CANMID_IDE)
		cf->can_id = (data & CAN_EFF_MASK) | CAN_EFF_FLAG;
	अन्यथा
		cf->can_id = (data >> 18) & CAN_SFF_MASK;

	data = hecc_पढ़ो_mbx(priv, mbxno, HECC_CANMCF);
	अगर (data & HECC_CANMCF_RTR)
		cf->can_id |= CAN_RTR_FLAG;
	cf->len = can_cc_dlc2len(data & 0xF);

	data = hecc_पढ़ो_mbx(priv, mbxno, HECC_CANMDL);
	*(__be32 *)(cf->data) = cpu_to_be32(data);
	अगर (cf->len > 4) अणु
		data = hecc_पढ़ो_mbx(priv, mbxno, HECC_CANMDH);
		*(__be32 *)(cf->data + 4) = cpu_to_be32(data);
	पूर्ण

	*बारtamp = hecc_पढ़ो_stamp(priv, mbxno);

	/* Check क्रम FIFO overrun.
	 *
	 * All but the last RX mailbox have activated overग_लिखो
	 * protection. So skip check क्रम overrun, अगर we're not
	 * handling the last RX mailbox.
	 *
	 * As the overग_लिखो protection क्रम the last RX mailbox is
	 * disabled, the CAN core might update जबतक we're पढ़ोing
	 * it. This means the skb might be inconsistent.
	 *
	 * Return an error to let rx-offload discard this CAN frame.
	 */
	अगर (unlikely(mbxno == HECC_RX_LAST_MBOX &&
		     hecc_पढ़ो(priv, HECC_CANRML) & mbx_mask))
		skb = ERR_PTR(-ENOBUFS);

 mark_as_पढ़ो:
	hecc_ग_लिखो(priv, HECC_CANRMP, mbx_mask);

	वापस skb;
पूर्ण

अटल पूर्णांक ti_hecc_error(काष्ठा net_device *ndev, पूर्णांक पूर्णांक_status,
			 पूर्णांक err_status)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 बारtamp;
	पूर्णांक err;

	अगर (err_status & HECC_BUS_ERROR) अणु
		/* propagate the error condition to the can stack */
		skb = alloc_can_err_skb(ndev, &cf);
		अगर (!skb) अणु
			अगर (net_ratelimit())
				netdev_err(priv->ndev,
					   "%s: alloc_can_err_skb() failed\n",
					   __func__);
			वापस -ENOMEM;
		पूर्ण

		++priv->can.can_stats.bus_error;
		cf->can_id |= CAN_ERR_BUSERROR | CAN_ERR_PROT;
		अगर (err_status & HECC_CANES_FE)
			cf->data[2] |= CAN_ERR_PROT_FORM;
		अगर (err_status & HECC_CANES_BE)
			cf->data[2] |= CAN_ERR_PROT_BIT;
		अगर (err_status & HECC_CANES_SE)
			cf->data[2] |= CAN_ERR_PROT_STUFF;
		अगर (err_status & HECC_CANES_CRCE)
			cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		अगर (err_status & HECC_CANES_ACKE)
			cf->data[3] = CAN_ERR_PROT_LOC_ACK;

		बारtamp = hecc_पढ़ो(priv, HECC_CANLNT);
		err = can_rx_offload_queue_sorted(&priv->offload, skb,
						  बारtamp);
		अगर (err)
			ndev->stats.rx_fअगरo_errors++;
	पूर्ण

	hecc_ग_लिखो(priv, HECC_CANES, HECC_CANES_FLAGS);

	वापस 0;
पूर्ण

अटल व्योम ti_hecc_change_state(काष्ठा net_device *ndev,
				 क्रमागत can_state rx_state,
				 क्रमागत can_state tx_state)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 बारtamp;
	पूर्णांक err;

	skb = alloc_can_err_skb(priv->ndev, &cf);
	अगर (unlikely(!skb)) अणु
		priv->can.state = max(tx_state, rx_state);
		वापस;
	पूर्ण

	can_change_state(priv->ndev, cf, tx_state, rx_state);

	अगर (max(tx_state, rx_state) != CAN_STATE_BUS_OFF) अणु
		cf->data[6] = hecc_पढ़ो(priv, HECC_CANTEC);
		cf->data[7] = hecc_पढ़ो(priv, HECC_CANREC);
	पूर्ण

	बारtamp = hecc_पढ़ो(priv, HECC_CANLNT);
	err = can_rx_offload_queue_sorted(&priv->offload, skb, बारtamp);
	अगर (err)
		ndev->stats.rx_fअगरo_errors++;
पूर्ण

अटल irqवापस_t ti_hecc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)dev_id;
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	u32 mbxno, mbx_mask, पूर्णांक_status, err_status, stamp;
	अचिन्हित दीर्घ flags, rx_pending;
	u32 handled = 0;

	पूर्णांक_status = hecc_पढ़ो(priv,
			       priv->use_hecc1पूर्णांक ?
			       HECC_CANGIF1 : HECC_CANGIF0);

	अगर (!पूर्णांक_status)
		वापस IRQ_NONE;

	err_status = hecc_पढ़ो(priv, HECC_CANES);
	अगर (unlikely(err_status & HECC_CANES_FLAGS))
		ti_hecc_error(ndev, पूर्णांक_status, err_status);

	अगर (unlikely(पूर्णांक_status & HECC_CANGIM_DEF_MASK)) अणु
		क्रमागत can_state rx_state, tx_state;
		u32 rec = hecc_पढ़ो(priv, HECC_CANREC);
		u32 tec = hecc_पढ़ो(priv, HECC_CANTEC);

		अगर (पूर्णांक_status & HECC_CANGIF_WLIF) अणु
			handled |= HECC_CANGIF_WLIF;
			rx_state = rec >= tec ? CAN_STATE_ERROR_WARNING : 0;
			tx_state = rec <= tec ? CAN_STATE_ERROR_WARNING : 0;
			netdev_dbg(priv->ndev, "Error Warning interrupt\n");
			ti_hecc_change_state(ndev, rx_state, tx_state);
		पूर्ण

		अगर (पूर्णांक_status & HECC_CANGIF_EPIF) अणु
			handled |= HECC_CANGIF_EPIF;
			rx_state = rec >= tec ? CAN_STATE_ERROR_PASSIVE : 0;
			tx_state = rec <= tec ? CAN_STATE_ERROR_PASSIVE : 0;
			netdev_dbg(priv->ndev, "Error passive interrupt\n");
			ti_hecc_change_state(ndev, rx_state, tx_state);
		पूर्ण

		अगर (पूर्णांक_status & HECC_CANGIF_BOIF) अणु
			handled |= HECC_CANGIF_BOIF;
			rx_state = CAN_STATE_BUS_OFF;
			tx_state = CAN_STATE_BUS_OFF;
			netdev_dbg(priv->ndev, "Bus off interrupt\n");

			/* Disable all पूर्णांकerrupts */
			hecc_ग_लिखो(priv, HECC_CANGIM, 0);
			can_bus_off(ndev);
			ti_hecc_change_state(ndev, rx_state, tx_state);
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(priv->can.state != CAN_STATE_ERROR_ACTIVE)) अणु
		क्रमागत can_state new_state, tx_state, rx_state;
		u32 rec = hecc_पढ़ो(priv, HECC_CANREC);
		u32 tec = hecc_पढ़ो(priv, HECC_CANTEC);

		अगर (rec >= 128 || tec >= 128)
			new_state = CAN_STATE_ERROR_PASSIVE;
		अन्यथा अगर (rec >= 96 || tec >= 96)
			new_state = CAN_STATE_ERROR_WARNING;
		अन्यथा
			new_state = CAN_STATE_ERROR_ACTIVE;

		अगर (new_state < priv->can.state) अणु
			rx_state = rec >= tec ? new_state : 0;
			tx_state = rec <= tec ? new_state : 0;
			ti_hecc_change_state(ndev, rx_state, tx_state);
		पूर्ण
	पूर्ण

	अगर (पूर्णांक_status & HECC_CANGIF_GMIF) अणु
		जबतक (priv->tx_tail - priv->tx_head > 0) अणु
			mbxno = get_tx_tail_mb(priv);
			mbx_mask = BIT(mbxno);
			अगर (!(mbx_mask & hecc_पढ़ो(priv, HECC_CANTA)))
				अवरोध;
			hecc_ग_लिखो(priv, HECC_CANTA, mbx_mask);
			spin_lock_irqsave(&priv->mbx_lock, flags);
			hecc_clear_bit(priv, HECC_CANME, mbx_mask);
			spin_unlock_irqrestore(&priv->mbx_lock, flags);
			stamp = hecc_पढ़ो_stamp(priv, mbxno);
			stats->tx_bytes +=
				can_rx_offload_get_echo_skb(&priv->offload,
							    mbxno, stamp, शून्य);
			stats->tx_packets++;
			can_led_event(ndev, CAN_LED_EVENT_TX);
			--priv->tx_tail;
		पूर्ण

		/* restart queue अगर wrap-up or अगर queue stalled on last pkt */
		अगर ((priv->tx_head == priv->tx_tail &&
		     ((priv->tx_head & HECC_TX_MASK) != HECC_TX_MASK)) ||
		    (((priv->tx_tail & HECC_TX_MASK) == HECC_TX_MASK) &&
		     ((priv->tx_head & HECC_TX_MASK) == HECC_TX_MASK)))
			netअगर_wake_queue(ndev);

		/* offload RX mailboxes and let NAPI deliver them */
		जबतक ((rx_pending = hecc_पढ़ो(priv, HECC_CANRMP))) अणु
			can_rx_offload_irq_offload_बारtamp(&priv->offload,
							     rx_pending);
		पूर्ण
	पूर्ण

	/* clear all पूर्णांकerrupt conditions - पढ़ो back to aव्योम spurious पूर्णांकs */
	अगर (priv->use_hecc1पूर्णांक) अणु
		hecc_ग_लिखो(priv, HECC_CANGIF1, handled);
		पूर्णांक_status = hecc_पढ़ो(priv, HECC_CANGIF1);
	पूर्ण अन्यथा अणु
		hecc_ग_लिखो(priv, HECC_CANGIF0, handled);
		पूर्णांक_status = hecc_पढ़ो(priv, HECC_CANGIF0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ti_hecc_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	err = request_irq(ndev->irq, ti_hecc_पूर्णांकerrupt, IRQF_SHARED,
			  ndev->name, ndev);
	अगर (err) अणु
		netdev_err(ndev, "error requesting interrupt\n");
		वापस err;
	पूर्ण

	ti_hecc_transceiver_चयन(priv, 1);

	/* Open common can device */
	err = खोलो_candev(ndev);
	अगर (err) अणु
		netdev_err(ndev, "open_candev() failed %d\n", err);
		ti_hecc_transceiver_चयन(priv, 0);
		मुक्त_irq(ndev->irq, ndev);
		वापस err;
	पूर्ण

	can_led_event(ndev, CAN_LED_EVENT_OPEN);

	ti_hecc_start(ndev);
	can_rx_offload_enable(&priv->offload);
	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_hecc_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	can_rx_offload_disable(&priv->offload);
	ti_hecc_stop(ndev);
	मुक्त_irq(ndev->irq, ndev);
	बंद_candev(ndev);
	ti_hecc_transceiver_चयन(priv, 0);

	can_led_event(ndev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ti_hecc_netdev_ops = अणु
	.nकरो_खोलो		= ti_hecc_खोलो,
	.nकरो_stop		= ti_hecc_बंद,
	.nकरो_start_xmit		= ti_hecc_xmit,
	.nकरो_change_mtu		= can_change_mtu,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_hecc_dt_ids[] = अणु
	अणु
		.compatible = "ti,am3517-hecc",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_hecc_dt_ids);

अटल पूर्णांक ti_hecc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)0;
	काष्ठा ti_hecc_priv *priv;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *irq;
	काष्ठा regulator *reg_xceiver;
	पूर्णांक err = -ENODEV;

	अगर (!IS_ENABLED(CONFIG_OF) || !np)
		वापस -EINVAL;

	reg_xceiver = devm_regulator_get(&pdev->dev, "xceiver");
	अगर (PTR_ERR(reg_xceiver) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अन्यथा अगर (IS_ERR(reg_xceiver))
		reg_xceiver = शून्य;

	ndev = alloc_candev(माप(काष्ठा ti_hecc_priv), HECC_MAX_TX_MBOX);
	अगर (!ndev) अणु
		dev_err(&pdev->dev, "alloc_candev failed\n");
		वापस -ENOMEM;
	पूर्ण
	priv = netdev_priv(ndev);

	/* handle hecc memory */
	priv->base = devm_platक्रमm_ioremap_resource_byname(pdev, "hecc");
	अगर (IS_ERR(priv->base)) अणु
		dev_err(&pdev->dev, "hecc ioremap failed\n");
		err = PTR_ERR(priv->base);
		जाओ probe_निकास_candev;
	पूर्ण

	/* handle hecc-ram memory */
	priv->hecc_ram = devm_platक्रमm_ioremap_resource_byname(pdev,
							       "hecc-ram");
	अगर (IS_ERR(priv->hecc_ram)) अणु
		dev_err(&pdev->dev, "hecc-ram ioremap failed\n");
		err = PTR_ERR(priv->hecc_ram);
		जाओ probe_निकास_candev;
	पूर्ण

	/* handle mbx memory */
	priv->mbx = devm_platक्रमm_ioremap_resource_byname(pdev, "mbx");
	अगर (IS_ERR(priv->mbx)) अणु
		dev_err(&pdev->dev, "mbx ioremap failed\n");
		err = PTR_ERR(priv->mbx);
		जाओ probe_निकास_candev;
	पूर्ण

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "No irq resource\n");
		जाओ probe_निकास_candev;
	पूर्ण

	priv->ndev = ndev;
	priv->reg_xceiver = reg_xceiver;
	priv->use_hecc1पूर्णांक = of_property_पढ़ो_bool(np, "ti,use-hecc1int");

	priv->can.bittiming_स्थिर = &ti_hecc_bittiming_स्थिर;
	priv->can.करो_set_mode = ti_hecc_करो_set_mode;
	priv->can.करो_get_berr_counter = ti_hecc_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES;

	spin_lock_init(&priv->mbx_lock);
	ndev->irq = irq->start;
	ndev->flags |= IFF_ECHO;
	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->netdev_ops = &ti_hecc_netdev_ops;

	priv->clk = clk_get(&pdev->dev, "hecc_ck");
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "No clock available\n");
		err = PTR_ERR(priv->clk);
		priv->clk = शून्य;
		जाओ probe_निकास_candev;
	पूर्ण
	priv->can.घड़ी.freq = clk_get_rate(priv->clk);

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "clk_prepare_enable() failed\n");
		जाओ probe_निकास_release_clk;
	पूर्ण

	priv->offload.mailbox_पढ़ो = ti_hecc_mailbox_पढ़ो;
	priv->offload.mb_first = HECC_RX_FIRST_MBOX;
	priv->offload.mb_last = HECC_RX_LAST_MBOX;
	err = can_rx_offload_add_बारtamp(ndev, &priv->offload);
	अगर (err) अणु
		dev_err(&pdev->dev, "can_rx_offload_add_timestamp() failed\n");
		जाओ probe_निकास_disable_clk;
	पूर्ण

	err = रेजिस्टर_candev(ndev);
	अगर (err) अणु
		dev_err(&pdev->dev, "register_candev() failed\n");
		जाओ probe_निकास_offload;
	पूर्ण

	devm_can_led_init(ndev);

	dev_info(&pdev->dev, "device registered (reg_base=%p, irq=%u)\n",
		 priv->base, (u32)ndev->irq);

	वापस 0;

probe_निकास_offload:
	can_rx_offload_del(&priv->offload);
probe_निकास_disable_clk:
	clk_disable_unprepare(priv->clk);
probe_निकास_release_clk:
	clk_put(priv->clk);
probe_निकास_candev:
	मुक्त_candev(ndev);

	वापस err;
पूर्ण

अटल पूर्णांक ti_hecc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा ti_hecc_priv *priv = netdev_priv(ndev);

	unरेजिस्टर_candev(ndev);
	clk_disable_unprepare(priv->clk);
	clk_put(priv->clk);
	can_rx_offload_del(&priv->offload);
	मुक्त_candev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ti_hecc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा ti_hecc_priv *priv = netdev_priv(dev);

	अगर (netअगर_running(dev)) अणु
		netअगर_stop_queue(dev);
		netअगर_device_detach(dev);
	पूर्ण

	hecc_set_bit(priv, HECC_CANMC, HECC_CANMC_PDR);
	priv->can.state = CAN_STATE_SLEEPING;

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_hecc_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा ti_hecc_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		वापस err;

	hecc_clear_bit(priv, HECC_CANMC, HECC_CANMC_PDR);
	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	अगर (netअगर_running(dev)) अणु
		netअगर_device_attach(dev);
		netअगर_start_queue(dev);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ti_hecc_suspend शून्य
#घोषणा ti_hecc_resume शून्य
#पूर्ण_अगर

/* TI HECC netdevice driver: platक्रमm driver काष्ठाure */
अटल काष्ठा platक्रमm_driver ti_hecc_driver = अणु
	.driver = अणु
		.name    = DRV_NAME,
		.of_match_table = ti_hecc_dt_ids,
	पूर्ण,
	.probe = ti_hecc_probe,
	.हटाओ = ti_hecc_हटाओ,
	.suspend = ti_hecc_suspend,
	.resume = ti_hecc_resume,
पूर्ण;

module_platक्रमm_driver(ti_hecc_driver);

MODULE_AUTHOR("Anant Gole <anantgole@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(DRV_DESC);
MODULE_ALIAS("platform:" DRV_NAME);
