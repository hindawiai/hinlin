<शैली गुरु>
/*
 * CAN bus driver क्रम Bosch C_CAN controller
 *
 * Copyright (C) 2010 ST Microelectronics
 * Bhupesh Sharma <bhupesh.sharma@st.com>
 *
 * Borrowed heavily from the C_CAN driver originally written by:
 * Copyright (C) 2007
 * - Sascha Hauer, Marc Kleine-Budde, Pengutronix <s.hauer@pengutronix.de>
 * - Simon Kallweit, पूर्णांकefo AG <simon.kallweit@पूर्णांकefo.ch>
 *
 * TX and RX NAPI implementation has been borrowed from at91 CAN driver
 * written by:
 * Copyright
 * (C) 2007 by Hans J. Koch <hjk@hansjkoch.de>
 * (C) 2008, 2009 by Marc Kleine-Budde <kernel@pengutronix.de>
 *
 * Bosch C_CAN controller is compliant to CAN protocol version 2.0 part A and B.
 * Bosch C_CAN user manual can be obtained from:
 * http://www.semiconductors.bosch.de/media/en/pdf/ipmodules_1/c_can/
 * users_manual_c_can.pdf
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/list.h>
#समावेश <linux/पन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pinctrl/consumer.h>

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>

#समावेश "c_can.h"

/* Number of पूर्णांकerface रेजिस्टरs */
#घोषणा IF_ENUM_REG_LEN		11
#घोषणा C_CAN_IFACE(reg, अगरace)	(C_CAN_IF1_##reg + (अगरace) * IF_ENUM_REG_LEN)

/* control extension रेजिस्टर D_CAN specअगरic */
#घोषणा CONTROL_EX_PDR		BIT(8)

/* control रेजिस्टर */
#घोषणा CONTROL_SWR		BIT(15)
#घोषणा CONTROL_TEST		BIT(7)
#घोषणा CONTROL_CCE		BIT(6)
#घोषणा CONTROL_DISABLE_AR	BIT(5)
#घोषणा CONTROL_ENABLE_AR	(0 << 5)
#घोषणा CONTROL_EIE		BIT(3)
#घोषणा CONTROL_SIE		BIT(2)
#घोषणा CONTROL_IE		BIT(1)
#घोषणा CONTROL_INIT		BIT(0)

#घोषणा CONTROL_IRQMSK		(CONTROL_EIE | CONTROL_IE | CONTROL_SIE)

/* test रेजिस्टर */
#घोषणा TEST_RX			BIT(7)
#घोषणा TEST_TX1		BIT(6)
#घोषणा TEST_TX2		BIT(5)
#घोषणा TEST_LBACK		BIT(4)
#घोषणा TEST_SILENT		BIT(3)
#घोषणा TEST_BASIC		BIT(2)

/* status रेजिस्टर */
#घोषणा STATUS_PDA		BIT(10)
#घोषणा STATUS_BOFF		BIT(7)
#घोषणा STATUS_EWARN		BIT(6)
#घोषणा STATUS_EPASS		BIT(5)
#घोषणा STATUS_RXOK		BIT(4)
#घोषणा STATUS_TXOK		BIT(3)

/* error counter रेजिस्टर */
#घोषणा ERR_CNT_TEC_MASK	0xff
#घोषणा ERR_CNT_TEC_SHIFT	0
#घोषणा ERR_CNT_REC_SHIFT	8
#घोषणा ERR_CNT_REC_MASK	(0x7f << ERR_CNT_REC_SHIFT)
#घोषणा ERR_CNT_RP_SHIFT	15
#घोषणा ERR_CNT_RP_MASK		(0x1 << ERR_CNT_RP_SHIFT)

/* bit-timing रेजिस्टर */
#घोषणा BTR_BRP_MASK		0x3f
#घोषणा BTR_BRP_SHIFT		0
#घोषणा BTR_SJW_SHIFT		6
#घोषणा BTR_SJW_MASK		(0x3 << BTR_SJW_SHIFT)
#घोषणा BTR_TSEG1_SHIFT		8
#घोषणा BTR_TSEG1_MASK		(0xf << BTR_TSEG1_SHIFT)
#घोषणा BTR_TSEG2_SHIFT		12
#घोषणा BTR_TSEG2_MASK		(0x7 << BTR_TSEG2_SHIFT)

/* पूर्णांकerrupt रेजिस्टर */
#घोषणा INT_STS_PENDING		0x8000

/* brp extension रेजिस्टर */
#घोषणा BRP_EXT_BRPE_MASK	0x0f
#घोषणा BRP_EXT_BRPE_SHIFT	0

/* IFx command request */
#घोषणा IF_COMR_BUSY		BIT(15)

/* IFx command mask */
#घोषणा IF_COMM_WR		BIT(7)
#घोषणा IF_COMM_MASK		BIT(6)
#घोषणा IF_COMM_ARB		BIT(5)
#घोषणा IF_COMM_CONTROL		BIT(4)
#घोषणा IF_COMM_CLR_INT_PND	BIT(3)
#घोषणा IF_COMM_TXRQST		BIT(2)
#घोषणा IF_COMM_CLR_NEWDAT	IF_COMM_TXRQST
#घोषणा IF_COMM_DATAA		BIT(1)
#घोषणा IF_COMM_DATAB		BIT(0)

/* TX buffer setup */
#घोषणा IF_COMM_TX		(IF_COMM_ARB | IF_COMM_CONTROL | \
				 IF_COMM_TXRQST |		 \
				 IF_COMM_DATAA | IF_COMM_DATAB)

/* For the low buffers we clear the पूर्णांकerrupt bit, but keep newdat */
#घोषणा IF_COMM_RCV_LOW		(IF_COMM_MASK | IF_COMM_ARB | \
				 IF_COMM_CONTROL | IF_COMM_CLR_INT_PND | \
				 IF_COMM_DATAA | IF_COMM_DATAB)

/* For the high buffers we clear the पूर्णांकerrupt bit and newdat */
#घोषणा IF_COMM_RCV_HIGH	(IF_COMM_RCV_LOW | IF_COMM_CLR_NEWDAT)

/* Receive setup of message objects */
#घोषणा IF_COMM_RCV_SETUP	(IF_COMM_MASK | IF_COMM_ARB | IF_COMM_CONTROL)

/* Invalidation of message objects */
#घोषणा IF_COMM_INVAL		(IF_COMM_ARB | IF_COMM_CONTROL)

/* IFx arbitration */
#घोषणा IF_ARB_MSGVAL		BIT(31)
#घोषणा IF_ARB_MSGXTD		BIT(30)
#घोषणा IF_ARB_TRANSMIT		BIT(29)

/* IFx message control */
#घोषणा IF_MCONT_NEWDAT		BIT(15)
#घोषणा IF_MCONT_MSGLST		BIT(14)
#घोषणा IF_MCONT_INTPND		BIT(13)
#घोषणा IF_MCONT_UMASK		BIT(12)
#घोषणा IF_MCONT_TXIE		BIT(11)
#घोषणा IF_MCONT_RXIE		BIT(10)
#घोषणा IF_MCONT_RMTEN		BIT(9)
#घोषणा IF_MCONT_TXRQST		BIT(8)
#घोषणा IF_MCONT_EOB		BIT(7)
#घोषणा IF_MCONT_DLC_MASK	0xf

#घोषणा IF_MCONT_RCV		(IF_MCONT_RXIE | IF_MCONT_UMASK)
#घोषणा IF_MCONT_RCV_EOB	(IF_MCONT_RCV | IF_MCONT_EOB)

#घोषणा IF_MCONT_TX		(IF_MCONT_TXIE | IF_MCONT_EOB)

/* Use IF1 क्रम RX and IF2 क्रम TX */
#घोषणा IF_RX			0
#घोषणा IF_TX			1

/* minimum समयout क्रम checking BUSY status */
#घोषणा MIN_TIMEOUT_VALUE	6

/* Wait क्रम ~1 sec क्रम INIT bit */
#घोषणा INIT_WAIT_MS		1000

/* c_can lec values */
क्रमागत c_can_lec_type अणु
	LEC_NO_ERROR = 0,
	LEC_STUFF_ERROR,
	LEC_FORM_ERROR,
	LEC_ACK_ERROR,
	LEC_BIT1_ERROR,
	LEC_BIT0_ERROR,
	LEC_CRC_ERROR,
	LEC_UNUSED,
	LEC_MASK = LEC_UNUSED,
पूर्ण;

/* c_can error types:
 * Bus errors (BUS_OFF, ERROR_WARNING, ERROR_PASSIVE) are supported
 */
क्रमागत c_can_bus_error_types अणु
	C_CAN_NO_ERROR = 0,
	C_CAN_BUS_OFF,
	C_CAN_ERROR_WARNING,
	C_CAN_ERROR_PASSIVE,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर c_can_bittiming_स्थिर = अणु
	.name = KBUILD_MODNAME,
	.tseg1_min = 2,		/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max = 16,
	.tseg2_min = 1,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 1024,	/* 6-bit BRP field + 4-bit BRPE field*/
	.brp_inc = 1,
पूर्ण;

अटल अंतरभूत व्योम c_can_pm_runसमय_get_sync(स्थिर काष्ठा c_can_priv *priv)
अणु
	अगर (priv->device)
		pm_runसमय_get_sync(priv->device);
पूर्ण

अटल अंतरभूत व्योम c_can_pm_runसमय_put_sync(स्थिर काष्ठा c_can_priv *priv)
अणु
	अगर (priv->device)
		pm_runसमय_put_sync(priv->device);
पूर्ण

अटल अंतरभूत व्योम c_can_reset_ram(स्थिर काष्ठा c_can_priv *priv, bool enable)
अणु
	अगर (priv->raminit)
		priv->raminit(priv, enable);
पूर्ण

अटल व्योम c_can_irq_control(काष्ठा c_can_priv *priv, bool enable)
अणु
	u32 ctrl = priv->पढ़ो_reg(priv,	C_CAN_CTRL_REG) & ~CONTROL_IRQMSK;

	अगर (enable)
		ctrl |= CONTROL_IRQMSK;

	priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, ctrl);
पूर्ण

अटल व्योम c_can_obj_update(काष्ठा net_device *dev, पूर्णांक अगरace, u32 cmd, u32 obj)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक cnt, reg = C_CAN_IFACE(COMREQ_REG, अगरace);

	priv->ग_लिखो_reg32(priv, reg, (cmd << 16) | obj);

	क्रम (cnt = MIN_TIMEOUT_VALUE; cnt; cnt--) अणु
		अगर (!(priv->पढ़ो_reg(priv, reg) & IF_COMR_BUSY))
			वापस;
		udelay(1);
	पूर्ण
	netdev_err(dev, "Updating object timed out\n");
पूर्ण

अटल अंतरभूत व्योम c_can_object_get(काष्ठा net_device *dev, पूर्णांक अगरace,
				    u32 obj, u32 cmd)
अणु
	c_can_obj_update(dev, अगरace, cmd, obj);
पूर्ण

अटल अंतरभूत व्योम c_can_object_put(काष्ठा net_device *dev, पूर्णांक अगरace,
				    u32 obj, u32 cmd)
अणु
	c_can_obj_update(dev, अगरace, cmd | IF_COMM_WR, obj);
पूर्ण

/* Note: According to करोcumentation clearing TXIE जबतक MSGVAL is set
 * is not allowed, but works nicely on C/DCAN. And that lowers the I/O
 * load signअगरicantly.
 */
अटल व्योम c_can_inval_tx_object(काष्ठा net_device *dev, पूर्णांक अगरace, पूर्णांक obj)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	priv->ग_लिखो_reg(priv, C_CAN_IFACE(MSGCTRL_REG, अगरace), 0);
	c_can_object_put(dev, अगरace, obj, IF_COMM_INVAL);
पूर्ण

अटल व्योम c_can_inval_msg_object(काष्ठा net_device *dev, पूर्णांक अगरace, पूर्णांक obj)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	priv->ग_लिखो_reg32(priv, C_CAN_IFACE(ARB1_REG, अगरace), 0);
	c_can_inval_tx_object(dev, अगरace, obj);
पूर्ण

अटल व्योम c_can_setup_tx_object(काष्ठा net_device *dev, पूर्णांक अगरace,
				  काष्ठा can_frame *frame, पूर्णांक idx)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	u16 ctrl = IF_MCONT_TX | frame->len;
	bool rtr = frame->can_id & CAN_RTR_FLAG;
	u32 arb = IF_ARB_MSGVAL;
	पूर्णांक i;

	अगर (frame->can_id & CAN_EFF_FLAG) अणु
		arb |= frame->can_id & CAN_EFF_MASK;
		arb |= IF_ARB_MSGXTD;
	पूर्ण अन्यथा अणु
		arb |= (frame->can_id & CAN_SFF_MASK) << 18;
	पूर्ण

	अगर (!rtr)
		arb |= IF_ARB_TRANSMIT;

	/* If we change the सूची bit, we need to invalidate the buffer
	 * first, i.e. clear the MSGVAL flag in the arbiter.
	 */
	अगर (rtr != (bool)test_bit(idx, &priv->tx_dir)) अणु
		u32 obj = idx + priv->msg_obj_tx_first;

		c_can_inval_msg_object(dev, अगरace, obj);
		change_bit(idx, &priv->tx_dir);
	पूर्ण

	priv->ग_लिखो_reg32(priv, C_CAN_IFACE(ARB1_REG, अगरace), arb);

	priv->ग_लिखो_reg(priv, C_CAN_IFACE(MSGCTRL_REG, अगरace), ctrl);

	अगर (priv->type == BOSCH_D_CAN) अणु
		u32 data = 0, dreg = C_CAN_IFACE(DATA1_REG, अगरace);

		क्रम (i = 0; i < frame->len; i += 4, dreg += 2) अणु
			data = (u32)frame->data[i];
			data |= (u32)frame->data[i + 1] << 8;
			data |= (u32)frame->data[i + 2] << 16;
			data |= (u32)frame->data[i + 3] << 24;
			priv->ग_लिखो_reg32(priv, dreg, data);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < frame->len; i += 2) अणु
			priv->ग_लिखो_reg(priv,
					C_CAN_IFACE(DATA1_REG, अगरace) + i / 2,
					frame->data[i] |
					(frame->data[i + 1] << 8));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक c_can_handle_lost_msg_obj(काष्ठा net_device *dev,
				     पूर्णांक अगरace, पूर्णांक objno, u32 ctrl)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	काष्ठा can_frame *frame;
	काष्ठा sk_buff *skb;

	ctrl &= ~(IF_MCONT_MSGLST | IF_MCONT_INTPND | IF_MCONT_NEWDAT);
	priv->ग_लिखो_reg(priv, C_CAN_IFACE(MSGCTRL_REG, अगरace), ctrl);
	c_can_object_put(dev, अगरace, objno, IF_COMM_CONTROL);

	stats->rx_errors++;
	stats->rx_over_errors++;

	/* create an error msg */
	skb = alloc_can_err_skb(dev, &frame);
	अगर (unlikely(!skb))
		वापस 0;

	frame->can_id |= CAN_ERR_CRTL;
	frame->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	netअगर_receive_skb(skb);
	वापस 1;
पूर्ण

अटल पूर्णांक c_can_पढ़ो_msg_object(काष्ठा net_device *dev, पूर्णांक अगरace, u32 ctrl)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	काष्ठा can_frame *frame;
	काष्ठा sk_buff *skb;
	u32 arb, data;

	skb = alloc_can_skb(dev, &frame);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस -ENOMEM;
	पूर्ण

	frame->len = can_cc_dlc2len(ctrl & 0x0F);

	arb = priv->पढ़ो_reg32(priv, C_CAN_IFACE(ARB1_REG, अगरace));

	अगर (arb & IF_ARB_MSGXTD)
		frame->can_id = (arb & CAN_EFF_MASK) | CAN_EFF_FLAG;
	अन्यथा
		frame->can_id = (arb >> 18) & CAN_SFF_MASK;

	अगर (arb & IF_ARB_TRANSMIT) अणु
		frame->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		पूर्णांक i, dreg = C_CAN_IFACE(DATA1_REG, अगरace);

		अगर (priv->type == BOSCH_D_CAN) अणु
			क्रम (i = 0; i < frame->len; i += 4, dreg += 2) अणु
				data = priv->पढ़ो_reg32(priv, dreg);
				frame->data[i] = data;
				frame->data[i + 1] = data >> 8;
				frame->data[i + 2] = data >> 16;
				frame->data[i + 3] = data >> 24;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < frame->len; i += 2, dreg++) अणु
				data = priv->पढ़ो_reg(priv, dreg);
				frame->data[i] = data;
				frame->data[i + 1] = data >> 8;
			पूर्ण
		पूर्ण
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += frame->len;

	netअगर_receive_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम c_can_setup_receive_object(काष्ठा net_device *dev, पूर्णांक अगरace,
				       u32 obj, u32 mask, u32 id, u32 mcont)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	mask |= BIT(29);
	priv->ग_लिखो_reg32(priv, C_CAN_IFACE(MASK1_REG, अगरace), mask);

	id |= IF_ARB_MSGVAL;
	priv->ग_लिखो_reg32(priv, C_CAN_IFACE(ARB1_REG, अगरace), id);

	priv->ग_लिखो_reg(priv, C_CAN_IFACE(MSGCTRL_REG, अगरace), mcont);
	c_can_object_put(dev, अगरace, obj, IF_COMM_RCV_SETUP);
पूर्ण

अटल netdev_tx_t c_can_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा can_frame *frame = (काष्ठा can_frame *)skb->data;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	u32 idx, obj;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;
	/* This is not a FIFO. C/D_CAN sends out the buffers
	 * prioritized. The lowest buffer number wins.
	 */
	idx = fls(atomic_पढ़ो(&priv->tx_active));
	obj = idx + priv->msg_obj_tx_first;

	/* If this is the last buffer, stop the xmit queue */
	अगर (idx == priv->msg_obj_tx_num - 1)
		netअगर_stop_queue(dev);
	/* Store the message in the पूर्णांकerface so we can call
	 * can_put_echo_skb(). We must करो this beक्रमe we enable
	 * transmit as we might race against करो_tx().
	 */
	c_can_setup_tx_object(dev, IF_TX, frame, idx);
	priv->dlc[idx] = frame->len;
	can_put_echo_skb(skb, dev, idx, 0);

	/* Update the active bits */
	atomic_add(BIT(idx), &priv->tx_active);
	/* Start transmission */
	c_can_object_put(dev, IF_TX, obj, IF_COMM_TX);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक c_can_रुको_क्रम_ctrl_init(काष्ठा net_device *dev,
				    काष्ठा c_can_priv *priv, u32 init)
अणु
	पूर्णांक retry = 0;

	जबतक (init != (priv->पढ़ो_reg(priv, C_CAN_CTRL_REG) & CONTROL_INIT)) अणु
		udelay(10);
		अगर (retry++ > 1000) अणु
			netdev_err(dev, "CCTRL: set CONTROL_INIT failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक c_can_set_bittiming(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक reg_btr, reg_brpe, ctrl_save;
	u8 brp, brpe, sjw, tseg1, tseg2;
	u32 ten_bit_brp;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	स्थिर काष्ठा can_bittiming *bt = &priv->can.bittiming;
	पूर्णांक res;

	/* c_can provides a 6-bit brp and 4-bit brpe fields */
	ten_bit_brp = bt->brp - 1;
	brp = ten_bit_brp & BTR_BRP_MASK;
	brpe = ten_bit_brp >> 6;

	sjw = bt->sjw - 1;
	tseg1 = bt->prop_seg + bt->phase_seg1 - 1;
	tseg2 = bt->phase_seg2 - 1;
	reg_btr = brp | (sjw << BTR_SJW_SHIFT) | (tseg1 << BTR_TSEG1_SHIFT) |
			(tseg2 << BTR_TSEG2_SHIFT);
	reg_brpe = brpe & BRP_EXT_BRPE_MASK;

	netdev_info(dev,
		    "setting BTR=%04x BRPE=%04x\n", reg_btr, reg_brpe);

	ctrl_save = priv->पढ़ो_reg(priv, C_CAN_CTRL_REG);
	ctrl_save &= ~CONTROL_INIT;
	priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, CONTROL_CCE | CONTROL_INIT);
	res = c_can_रुको_क्रम_ctrl_init(dev, priv, CONTROL_INIT);
	अगर (res)
		वापस res;

	priv->ग_लिखो_reg(priv, C_CAN_BTR_REG, reg_btr);
	priv->ग_लिखो_reg(priv, C_CAN_BRPEXT_REG, reg_brpe);
	priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, ctrl_save);

	वापस c_can_रुको_क्रम_ctrl_init(dev, priv, 0);
पूर्ण

/* Configure C_CAN message objects क्रम Tx and Rx purposes:
 * C_CAN provides a total of 32 message objects that can be configured
 * either क्रम Tx or Rx purposes. Here the first 16 message objects are used as
 * a reception FIFO. The end of reception FIFO is signअगरied by the EoB bit
 * being SET. The reमुख्यing 16 message objects are kept aside क्रम Tx purposes.
 * See user guide करोcument क्रम further details on configuring message
 * objects.
 */
अटल व्योम c_can_configure_msg_objects(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	/* first invalidate all message objects */
	क्रम (i = priv->msg_obj_rx_first; i <= priv->msg_obj_num; i++)
		c_can_inval_msg_object(dev, IF_RX, i);

	/* setup receive message objects */
	क्रम (i = priv->msg_obj_rx_first; i < priv->msg_obj_rx_last; i++)
		c_can_setup_receive_object(dev, IF_RX, i, 0, 0, IF_MCONT_RCV);

	c_can_setup_receive_object(dev, IF_RX, priv->msg_obj_rx_last, 0, 0,
				   IF_MCONT_RCV_EOB);
पूर्ण

अटल पूर्णांक c_can_software_reset(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक retry = 0;

	अगर (priv->type != BOSCH_D_CAN)
		वापस 0;

	priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, CONTROL_SWR | CONTROL_INIT);
	जबतक (priv->पढ़ो_reg(priv, C_CAN_CTRL_REG) & CONTROL_SWR) अणु
		msleep(20);
		अगर (retry++ > 100) अणु
			netdev_err(dev, "CCTRL: software reset failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Configure C_CAN chip:
 * - enable/disable स्वतः-retransmission
 * - set operating mode
 * - configure message objects
 */
अटल पूर्णांक c_can_chip_config(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	err = c_can_software_reset(dev);
	अगर (err)
		वापस err;

	/* enable स्वतःmatic retransmission */
	priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, CONTROL_ENABLE_AR);

	अगर ((priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) &&
	    (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)) अणु
		/* loopback + silent mode : useful क्रम hot self-test */
		priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, CONTROL_TEST);
		priv->ग_लिखो_reg(priv, C_CAN_TEST_REG, TEST_LBACK | TEST_SILENT);
	पूर्ण अन्यथा अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK) अणु
		/* loopback mode : useful क्रम self-test function */
		priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, CONTROL_TEST);
		priv->ग_लिखो_reg(priv, C_CAN_TEST_REG, TEST_LBACK);
	पूर्ण अन्यथा अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) अणु
		/* silent mode : bus-monitoring mode */
		priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, CONTROL_TEST);
		priv->ग_लिखो_reg(priv, C_CAN_TEST_REG, TEST_SILENT);
	पूर्ण

	/* configure message objects */
	c_can_configure_msg_objects(dev);

	/* set a `lec` value so that we can check क्रम updates later */
	priv->ग_लिखो_reg(priv, C_CAN_STS_REG, LEC_UNUSED);

	/* Clear all पूर्णांकernal status */
	atomic_set(&priv->tx_active, 0);
	priv->rxmasked = 0;
	priv->tx_dir = 0;

	/* set bittiming params */
	वापस c_can_set_bittiming(dev);
पूर्ण

अटल पूर्णांक c_can_start(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक err;
	काष्ठा pinctrl *p;

	/* basic c_can configuration */
	err = c_can_chip_config(dev);
	अगर (err)
		वापस err;

	/* Setup the command क्रम new messages */
	priv->comm_rcv_high = priv->type != BOSCH_D_CAN ?
		IF_COMM_RCV_LOW : IF_COMM_RCV_HIGH;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Attempt to use "active" अगर available अन्यथा use "default" */
	p = pinctrl_get_select(priv->device, "active");
	अगर (!IS_ERR(p))
		pinctrl_put(p);
	अन्यथा
		pinctrl_pm_select_शेष_state(priv->device);

	वापस 0;
पूर्ण

अटल व्योम c_can_stop(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	c_can_irq_control(priv, false);

	/* put ctrl to init on stop to end ongoing transmission */
	priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, CONTROL_INIT);

	/* deactivate pins */
	pinctrl_pm_select_sleep_state(dev->dev.parent);
	priv->can.state = CAN_STATE_STOPPED;
पूर्ण

अटल पूर्णांक c_can_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = c_can_start(dev);
		अगर (err)
			वापस err;
		netअगर_wake_queue(dev);
		c_can_irq_control(priv, true);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __c_can_get_berr_counter(स्थिर काष्ठा net_device *dev,
				    काष्ठा can_berr_counter *bec)
अणु
	अचिन्हित पूर्णांक reg_err_counter;
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	reg_err_counter = priv->पढ़ो_reg(priv, C_CAN_ERR_CNT_REG);
	bec->rxerr = (reg_err_counter & ERR_CNT_REC_MASK) >>
				ERR_CNT_REC_SHIFT;
	bec->txerr = reg_err_counter & ERR_CNT_TEC_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक c_can_get_berr_counter(स्थिर काष्ठा net_device *dev,
				  काष्ठा can_berr_counter *bec)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	c_can_pm_runसमय_get_sync(priv);
	err = __c_can_get_berr_counter(dev, bec);
	c_can_pm_runसमय_put_sync(priv);

	वापस err;
पूर्ण

अटल व्योम c_can_करो_tx(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	u32 idx, obj, pkts = 0, bytes = 0, pend, clr;

	अगर (priv->msg_obj_tx_last > 32)
		pend = priv->पढ़ो_reg32(priv, C_CAN_INTPND3_REG);
	अन्यथा
		pend = priv->पढ़ो_reg(priv, C_CAN_INTPND2_REG);
	clr = pend;

	जबतक ((idx = ffs(pend))) अणु
		idx--;
		pend &= ~BIT(idx);
		obj = idx + priv->msg_obj_tx_first;

		/* We use IF_RX पूर्णांकerface instead of IF_TX because we
		 * are called from c_can_poll(), which runs inside
		 * NAPI. We are not trयंत्रitting.
		 */
		c_can_inval_tx_object(dev, IF_RX, obj);
		can_get_echo_skb(dev, idx, शून्य);
		bytes += priv->dlc[idx];
		pkts++;
	पूर्ण

	/* Clear the bits in the tx_active mask */
	atomic_sub(clr, &priv->tx_active);

	अगर (clr & BIT(priv->msg_obj_tx_num - 1))
		netअगर_wake_queue(dev);

	अगर (pkts) अणु
		stats->tx_bytes += bytes;
		stats->tx_packets += pkts;
		can_led_event(dev, CAN_LED_EVENT_TX);
	पूर्ण
पूर्ण

/* If we have a gap in the pending bits, that means we either
 * raced with the hardware or failed to पढ़ोout all upper
 * objects in the last run due to quota limit.
 */
अटल u32 c_can_adjust_pending(u32 pend, u32 rx_mask)
अणु
	u32 weight, lasts;

	अगर (pend == rx_mask)
		वापस pend;

	/* If the last set bit is larger than the number of pending
	 * bits we have a gap.
	 */
	weight = hweight32(pend);
	lasts = fls(pend);

	/* If the bits are linear, nothing to करो */
	अगर (lasts == weight)
		वापस pend;

	/* Find the first set bit after the gap. We walk backwards
	 * from the last set bit.
	 */
	क्रम (lasts--; pend & BIT(lasts - 1); lasts--)
		;

	वापस pend & ~GENMASK(lasts - 1, 0);
पूर्ण

अटल अंतरभूत व्योम c_can_rx_object_get(काष्ठा net_device *dev,
				       काष्ठा c_can_priv *priv, u32 obj)
अणु
	c_can_object_get(dev, IF_RX, obj, priv->comm_rcv_high);
पूर्ण

अटल अंतरभूत व्योम c_can_rx_finalize(काष्ठा net_device *dev,
				     काष्ठा c_can_priv *priv, u32 obj)
अणु
	अगर (priv->type != BOSCH_D_CAN)
		c_can_object_get(dev, IF_RX, obj, IF_COMM_CLR_NEWDAT);
पूर्ण

अटल पूर्णांक c_can_पढ़ो_objects(काष्ठा net_device *dev, काष्ठा c_can_priv *priv,
			      u32 pend, पूर्णांक quota)
अणु
	u32 pkts = 0, ctrl, obj;

	जबतक ((obj = ffs(pend)) && quota > 0) अणु
		pend &= ~BIT(obj - 1);

		c_can_rx_object_get(dev, priv, obj);
		ctrl = priv->पढ़ो_reg(priv, C_CAN_IFACE(MSGCTRL_REG, IF_RX));

		अगर (ctrl & IF_MCONT_MSGLST) अणु
			पूर्णांक n = c_can_handle_lost_msg_obj(dev, IF_RX, obj, ctrl);

			pkts += n;
			quota -= n;
			जारी;
		पूर्ण

		/* This really should not happen, but this covers some
		 * odd HW behaviour. Do not हटाओ that unless you
		 * want to brick your machine.
		 */
		अगर (!(ctrl & IF_MCONT_NEWDAT))
			जारी;

		/* पढ़ो the data from the message object */
		c_can_पढ़ो_msg_object(dev, IF_RX, ctrl);

		c_can_rx_finalize(dev, priv, obj);

		pkts++;
		quota--;
	पूर्ण

	वापस pkts;
पूर्ण

अटल अंतरभूत u32 c_can_get_pending(काष्ठा c_can_priv *priv)
अणु
	u32 pend;

	अगर (priv->msg_obj_rx_last > 16)
		pend = priv->पढ़ो_reg32(priv, C_CAN_NEWDAT1_REG);
	अन्यथा
		pend = priv->पढ़ो_reg(priv, C_CAN_NEWDAT1_REG);

	वापस pend;
पूर्ण

/* theory of operation:
 *
 * c_can core saves a received CAN message पूर्णांकo the first मुक्त message
 * object it finds मुक्त (starting with the lowest). Bits NEWDAT and
 * INTPND are set क्रम this message object indicating that a new message
 * has arrived.
 *
 * We clear the newdat bit right away.
 *
 * This can result in packet reordering when the पढ़ोout is slow.
 */
अटल पूर्णांक c_can_करो_rx_poll(काष्ठा net_device *dev, पूर्णांक quota)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	u32 pkts = 0, pend = 0, toपढ़ो, n;

	जबतक (quota > 0) अणु
		अगर (!pend) अणु
			pend = c_can_get_pending(priv);
			अगर (!pend)
				अवरोध;
			/* If the pending field has a gap, handle the
			 * bits above the gap first.
			 */
			toपढ़ो = c_can_adjust_pending(pend,
						      priv->msg_obj_rx_mask);
		पूर्ण अन्यथा अणु
			toपढ़ो = pend;
		पूर्ण
		/* Remove the bits from pend */
		pend &= ~toपढ़ो;
		/* Read the objects */
		n = c_can_पढ़ो_objects(dev, priv, toपढ़ो, quota);
		pkts += n;
		quota -= n;
	पूर्ण

	अगर (pkts)
		can_led_event(dev, CAN_LED_EVENT_RX);

	वापस pkts;
पूर्ण

अटल पूर्णांक c_can_handle_state_change(काष्ठा net_device *dev,
				     क्रमागत c_can_bus_error_types error_type)
अणु
	अचिन्हित पूर्णांक reg_err_counter;
	अचिन्हित पूर्णांक rx_err_passive;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा can_berr_counter bec;

	चयन (error_type) अणु
	हाल C_CAN_NO_ERROR:
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		अवरोध;
	हाल C_CAN_ERROR_WARNING:
		/* error warning state */
		priv->can.can_stats.error_warning++;
		priv->can.state = CAN_STATE_ERROR_WARNING;
		अवरोध;
	हाल C_CAN_ERROR_PASSIVE:
		/* error passive state */
		priv->can.can_stats.error_passive++;
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		अवरोध;
	हाल C_CAN_BUS_OFF:
		/* bus-off state */
		priv->can.state = CAN_STATE_BUS_OFF;
		priv->can.can_stats.bus_off++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस 0;

	__c_can_get_berr_counter(dev, &bec);
	reg_err_counter = priv->पढ़ो_reg(priv, C_CAN_ERR_CNT_REG);
	rx_err_passive = (reg_err_counter & ERR_CNT_RP_MASK) >>
				ERR_CNT_RP_SHIFT;

	चयन (error_type) अणु
	हाल C_CAN_NO_ERROR:
		/* error warning state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_ACTIVE;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		अवरोध;
	हाल C_CAN_ERROR_WARNING:
		/* error warning state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = (bec.txerr > bec.rxerr) ?
			CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;

		अवरोध;
	हाल C_CAN_ERROR_PASSIVE:
		/* error passive state */
		cf->can_id |= CAN_ERR_CRTL;
		अगर (rx_err_passive)
			cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		अगर (bec.txerr > 127)
			cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;

		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		अवरोध;
	हाल C_CAN_BUS_OFF:
		/* bus-off state */
		cf->can_id |= CAN_ERR_BUSOFF;
		can_bus_off(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_receive_skb(skb);

	वापस 1;
पूर्ण

अटल पूर्णांक c_can_handle_bus_err(काष्ठा net_device *dev,
				क्रमागत c_can_lec_type lec_type)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	/* early निकास अगर no lec update or no error.
	 * no lec update means that no CAN bus event has been detected
	 * since CPU wrote 0x7 value to status reg.
	 */
	अगर (lec_type == LEC_UNUSED || lec_type == LEC_NO_ERROR)
		वापस 0;

	अगर (!(priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING))
		वापस 0;

	/* common क्रम all type of bus errors */
	priv->can.can_stats.bus_error++;
	stats->rx_errors++;

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस 0;

	/* check क्रम 'last error code' which tells us the
	 * type of the last error to occur on the CAN bus
	 */
	cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

	चयन (lec_type) अणु
	हाल LEC_STUFF_ERROR:
		netdev_dbg(dev, "stuff error\n");
		cf->data[2] |= CAN_ERR_PROT_STUFF;
		अवरोध;
	हाल LEC_FORM_ERROR:
		netdev_dbg(dev, "form error\n");
		cf->data[2] |= CAN_ERR_PROT_FORM;
		अवरोध;
	हाल LEC_ACK_ERROR:
		netdev_dbg(dev, "ack error\n");
		cf->data[3] = CAN_ERR_PROT_LOC_ACK;
		अवरोध;
	हाल LEC_BIT1_ERROR:
		netdev_dbg(dev, "bit1 error\n");
		cf->data[2] |= CAN_ERR_PROT_BIT1;
		अवरोध;
	हाल LEC_BIT0_ERROR:
		netdev_dbg(dev, "bit0 error\n");
		cf->data[2] |= CAN_ERR_PROT_BIT0;
		अवरोध;
	हाल LEC_CRC_ERROR:
		netdev_dbg(dev, "CRC error\n");
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_receive_skb(skb);
	वापस 1;
पूर्ण

अटल पूर्णांक c_can_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा net_device *dev = napi->dev;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	u16 curr, last = priv->last_status;
	पूर्णांक work_करोne = 0;

	/* Only पढ़ो the status रेजिस्टर अगर a status पूर्णांकerrupt was pending */
	अगर (atomic_xchg(&priv->sie_pending, 0)) अणु
		priv->last_status = priv->पढ़ो_reg(priv, C_CAN_STS_REG);
		curr = priv->last_status;
		/* Ack status on C_CAN. D_CAN is self clearing */
		अगर (priv->type != BOSCH_D_CAN)
			priv->ग_लिखो_reg(priv, C_CAN_STS_REG, LEC_UNUSED);
	पूर्ण अन्यथा अणु
		/* no change detected ... */
		curr = last;
	पूर्ण

	/* handle state changes */
	अगर ((curr & STATUS_EWARN) && (!(last & STATUS_EWARN))) अणु
		netdev_dbg(dev, "entered error warning state\n");
		work_करोne += c_can_handle_state_change(dev, C_CAN_ERROR_WARNING);
	पूर्ण

	अगर ((curr & STATUS_EPASS) && (!(last & STATUS_EPASS))) अणु
		netdev_dbg(dev, "entered error passive state\n");
		work_करोne += c_can_handle_state_change(dev, C_CAN_ERROR_PASSIVE);
	पूर्ण

	अगर ((curr & STATUS_BOFF) && (!(last & STATUS_BOFF))) अणु
		netdev_dbg(dev, "entered bus off state\n");
		work_करोne += c_can_handle_state_change(dev, C_CAN_BUS_OFF);
		जाओ end;
	पूर्ण

	/* handle bus recovery events */
	अगर ((!(curr & STATUS_BOFF)) && (last & STATUS_BOFF)) अणु
		netdev_dbg(dev, "left bus off state\n");
		work_करोne += c_can_handle_state_change(dev, C_CAN_ERROR_PASSIVE);
	पूर्ण

	अगर ((!(curr & STATUS_EPASS)) && (last & STATUS_EPASS)) अणु
		netdev_dbg(dev, "left error passive state\n");
		work_करोne += c_can_handle_state_change(dev, C_CAN_ERROR_WARNING);
	पूर्ण

	अगर ((!(curr & STATUS_EWARN)) && (last & STATUS_EWARN)) अणु
		netdev_dbg(dev, "left error warning state\n");
		work_करोne += c_can_handle_state_change(dev, C_CAN_NO_ERROR);
	पूर्ण

	/* handle lec errors on the bus */
	work_करोne += c_can_handle_bus_err(dev, curr & LEC_MASK);

	/* Handle Tx/Rx events. We करो this unconditionally */
	work_करोne += c_can_करो_rx_poll(dev, (quota - work_करोne));
	c_can_करो_tx(dev);

end:
	अगर (work_करोne < quota) अणु
		napi_complete_करोne(napi, work_करोne);
		/* enable all IRQs अगर we are not in bus off state */
		अगर (priv->can.state != CAN_STATE_BUS_OFF)
			c_can_irq_control(priv, true);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल irqवापस_t c_can_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक reg_पूर्णांक;

	reg_पूर्णांक = priv->पढ़ो_reg(priv, C_CAN_INT_REG);
	अगर (!reg_पूर्णांक)
		वापस IRQ_NONE;

	/* save क्रम later use */
	अगर (reg_पूर्णांक & INT_STS_PENDING)
		atomic_set(&priv->sie_pending, 1);

	/* disable all पूर्णांकerrupts and schedule the NAPI */
	c_can_irq_control(priv, false);
	napi_schedule(&priv->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक c_can_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक err;
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	c_can_pm_runसमय_get_sync(priv);
	c_can_reset_ram(priv, true);

	/* खोलो the can device */
	err = खोलो_candev(dev);
	अगर (err) अणु
		netdev_err(dev, "failed to open can device\n");
		जाओ निकास_खोलो_fail;
	पूर्ण

	/* रेजिस्टर पूर्णांकerrupt handler */
	err = request_irq(dev->irq, &c_can_isr, IRQF_SHARED, dev->name,
			  dev);
	अगर (err < 0) अणु
		netdev_err(dev, "failed to request interrupt\n");
		जाओ निकास_irq_fail;
	पूर्ण

	/* start the c_can controller */
	err = c_can_start(dev);
	अगर (err)
		जाओ निकास_start_fail;

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	napi_enable(&priv->napi);
	/* enable status change, error and module पूर्णांकerrupts */
	c_can_irq_control(priv, true);
	netअगर_start_queue(dev);

	वापस 0;

निकास_start_fail:
	मुक्त_irq(dev->irq, dev);
निकास_irq_fail:
	बंद_candev(dev);
निकास_खोलो_fail:
	c_can_reset_ram(priv, false);
	c_can_pm_runसमय_put_sync(priv);
	वापस err;
पूर्ण

अटल पूर्णांक c_can_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	netअगर_stop_queue(dev);
	napi_disable(&priv->napi);
	c_can_stop(dev);
	मुक्त_irq(dev->irq, dev);
	बंद_candev(dev);

	c_can_reset_ram(priv, false);
	c_can_pm_runसमय_put_sync(priv);

	can_led_event(dev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

काष्ठा net_device *alloc_c_can_dev(पूर्णांक msg_obj_num)
अणु
	काष्ठा net_device *dev;
	काष्ठा c_can_priv *priv;
	पूर्णांक msg_obj_tx_num = msg_obj_num / 2;

	dev = alloc_candev(काष्ठा_size(priv, dlc, msg_obj_tx_num),
			   msg_obj_tx_num);
	अगर (!dev)
		वापस शून्य;

	priv = netdev_priv(dev);
	priv->msg_obj_num = msg_obj_num;
	priv->msg_obj_rx_num = msg_obj_num - msg_obj_tx_num;
	priv->msg_obj_rx_first = 1;
	priv->msg_obj_rx_last =
		priv->msg_obj_rx_first + priv->msg_obj_rx_num - 1;
	priv->msg_obj_rx_mask = GENMASK(priv->msg_obj_rx_num - 1, 0);

	priv->msg_obj_tx_num = msg_obj_tx_num;
	priv->msg_obj_tx_first = priv->msg_obj_rx_last + 1;
	priv->msg_obj_tx_last =
		priv->msg_obj_tx_first + priv->msg_obj_tx_num - 1;

	netअगर_napi_add(dev, &priv->napi, c_can_poll, priv->msg_obj_rx_num);

	priv->dev = dev;
	priv->can.bittiming_स्थिर = &c_can_bittiming_स्थिर;
	priv->can.करो_set_mode = c_can_set_mode;
	priv->can.करो_get_berr_counter = c_can_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
					CAN_CTRLMODE_LISTENONLY |
					CAN_CTRLMODE_BERR_REPORTING;

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_c_can_dev);

#अगर_घोषित CONFIG_PM
पूर्णांक c_can_घातer_करोwn(काष्ठा net_device *dev)
अणु
	u32 val;
	अचिन्हित दीर्घ समय_out;
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	अगर (!(dev->flags & IFF_UP))
		वापस 0;

	WARN_ON(priv->type != BOSCH_D_CAN);

	/* set PDR value so the device goes to घातer करोwn mode */
	val = priv->पढ़ो_reg(priv, C_CAN_CTRL_EX_REG);
	val |= CONTROL_EX_PDR;
	priv->ग_लिखो_reg(priv, C_CAN_CTRL_EX_REG, val);

	/* Wait क्रम the PDA bit to get set */
	समय_out = jअगरfies + msecs_to_jअगरfies(INIT_WAIT_MS);
	जबतक (!(priv->पढ़ो_reg(priv, C_CAN_STS_REG) & STATUS_PDA) &&
	       समय_after(समय_out, jअगरfies))
		cpu_relax();

	अगर (समय_after(jअगरfies, समय_out))
		वापस -ETIMEDOUT;

	c_can_stop(dev);

	c_can_reset_ram(priv, false);
	c_can_pm_runसमय_put_sync(priv);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(c_can_घातer_करोwn);

पूर्णांक c_can_घातer_up(काष्ठा net_device *dev)
अणु
	u32 val;
	अचिन्हित दीर्घ समय_out;
	काष्ठा c_can_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	अगर (!(dev->flags & IFF_UP))
		वापस 0;

	WARN_ON(priv->type != BOSCH_D_CAN);

	c_can_pm_runसमय_get_sync(priv);
	c_can_reset_ram(priv, true);

	/* Clear PDR and INIT bits */
	val = priv->पढ़ो_reg(priv, C_CAN_CTRL_EX_REG);
	val &= ~CONTROL_EX_PDR;
	priv->ग_लिखो_reg(priv, C_CAN_CTRL_EX_REG, val);
	val = priv->पढ़ो_reg(priv, C_CAN_CTRL_REG);
	val &= ~CONTROL_INIT;
	priv->ग_लिखो_reg(priv, C_CAN_CTRL_REG, val);

	/* Wait क्रम the PDA bit to get clear */
	समय_out = jअगरfies + msecs_to_jअगरfies(INIT_WAIT_MS);
	जबतक ((priv->पढ़ो_reg(priv, C_CAN_STS_REG) & STATUS_PDA) &&
	       समय_after(समय_out, jअगरfies))
		cpu_relax();

	अगर (समय_after(jअगरfies, समय_out)) अणु
		ret = -ETIMEDOUT;
		जाओ err_out;
	पूर्ण

	ret = c_can_start(dev);
	अगर (ret)
		जाओ err_out;

	c_can_irq_control(priv, true);

	वापस 0;

err_out:
	c_can_reset_ram(priv, false);
	c_can_pm_runसमय_put_sync(priv);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(c_can_घातer_up);
#पूर्ण_अगर

व्योम मुक्त_c_can_dev(काष्ठा net_device *dev)
अणु
	काष्ठा c_can_priv *priv = netdev_priv(dev);

	netअगर_napi_del(&priv->napi);
	मुक्त_candev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_c_can_dev);

अटल स्थिर काष्ठा net_device_ops c_can_netdev_ops = अणु
	.nकरो_खोलो = c_can_खोलो,
	.nकरो_stop = c_can_बंद,
	.nकरो_start_xmit = c_can_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

पूर्णांक रेजिस्टर_c_can_dev(काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	/* Deactivate pins to prevent DRA7 DCAN IP from being
	 * stuck in transition when module is disabled.
	 * Pins are activated in c_can_start() and deactivated
	 * in c_can_stop()
	 */
	pinctrl_pm_select_sleep_state(dev->dev.parent);

	dev->flags |= IFF_ECHO;	/* we support local echo */
	dev->netdev_ops = &c_can_netdev_ops;

	err = रेजिस्टर_candev(dev);
	अगर (!err)
		devm_can_led_init(dev);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_c_can_dev);

व्योम unरेजिस्टर_c_can_dev(काष्ठा net_device *dev)
अणु
	unरेजिस्टर_candev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_c_can_dev);

MODULE_AUTHOR("Bhupesh Sharma <bhupesh.sharma@st.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CAN bus driver for Bosch C_CAN controller");
