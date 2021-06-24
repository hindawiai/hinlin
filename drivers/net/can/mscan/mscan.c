<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CAN bus driver क्रम the alone generic (as possible as) MSCAN controller.
 *
 * Copyright (C) 2005-2006 Andrey Volkov <avolkov@varma-el.com>,
 *                         Varma Electronics Oy
 * Copyright (C) 2008-2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 * Copyright (C) 2008-2009 Pengutronix <kernel@pengutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/list.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/पन.स>

#समावेश "mscan.h"

अटल स्थिर काष्ठा can_bittiming_स्थिर mscan_bittiming_स्थिर = अणु
	.name = "mscan",
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

काष्ठा mscan_state अणु
	u8 mode;
	u8 canrier;
	u8 cantier;
पूर्ण;

अटल क्रमागत can_state state_map[] = अणु
	CAN_STATE_ERROR_ACTIVE,
	CAN_STATE_ERROR_WARNING,
	CAN_STATE_ERROR_PASSIVE,
	CAN_STATE_BUS_OFF
पूर्ण;

अटल पूर्णांक mscan_set_mode(काष्ठा net_device *dev, u8 mode)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	पूर्णांक ret = 0;
	पूर्णांक i;
	u8 canctl1;

	अगर (mode != MSCAN_NORMAL_MODE) अणु
		अगर (priv->tx_active) अणु
			/* Abort transfers beक्रमe going to sleep */#
			out_8(&regs->cantarq, priv->tx_active);
			/* Suppress TX करोne पूर्णांकerrupts */
			out_8(&regs->cantier, 0);
		पूर्ण

		canctl1 = in_8(&regs->canctl1);
		अगर ((mode & MSCAN_SLPRQ) && !(canctl1 & MSCAN_SLPAK)) अणु
			setbits8(&regs->canctl0, MSCAN_SLPRQ);
			क्रम (i = 0; i < MSCAN_SET_MODE_RETRIES; i++) अणु
				अगर (in_8(&regs->canctl1) & MSCAN_SLPAK)
					अवरोध;
				udelay(100);
			पूर्ण
			/*
			 * The mscan controller will fail to enter sleep mode,
			 * जबतक there are irregular activities on bus, like
			 * somebody keeps retransmitting. This behavior is
			 * unकरोcumented and seems to dअगरfer between mscan built
			 * in mpc5200b and mpc5200. We proceed in that हाल,
			 * since otherwise the slprq will be kept set and the
			 * controller will get stuck. NOTE: INITRQ or CSWAI
			 * will पात all active transmit actions, अगर still
			 * any, at once.
			 */
			अगर (i >= MSCAN_SET_MODE_RETRIES)
				netdev_dbg(dev,
					   "device failed to enter sleep mode. "
					   "We proceed anyhow.\n");
			अन्यथा
				priv->can.state = CAN_STATE_SLEEPING;
		पूर्ण

		अगर ((mode & MSCAN_INITRQ) && !(canctl1 & MSCAN_INITAK)) अणु
			setbits8(&regs->canctl0, MSCAN_INITRQ);
			क्रम (i = 0; i < MSCAN_SET_MODE_RETRIES; i++) अणु
				अगर (in_8(&regs->canctl1) & MSCAN_INITAK)
					अवरोध;
			पूर्ण
			अगर (i >= MSCAN_SET_MODE_RETRIES)
				ret = -ENODEV;
		पूर्ण
		अगर (!ret)
			priv->can.state = CAN_STATE_STOPPED;

		अगर (mode & MSCAN_CSWAI)
			setbits8(&regs->canctl0, MSCAN_CSWAI);

	पूर्ण अन्यथा अणु
		canctl1 = in_8(&regs->canctl1);
		अगर (canctl1 & (MSCAN_SLPAK | MSCAN_INITAK)) अणु
			clrbits8(&regs->canctl0, MSCAN_SLPRQ | MSCAN_INITRQ);
			क्रम (i = 0; i < MSCAN_SET_MODE_RETRIES; i++) अणु
				canctl1 = in_8(&regs->canctl1);
				अगर (!(canctl1 & (MSCAN_INITAK | MSCAN_SLPAK)))
					अवरोध;
			पूर्ण
			अगर (i >= MSCAN_SET_MODE_RETRIES)
				ret = -ENODEV;
			अन्यथा
				priv->can.state = CAN_STATE_ERROR_ACTIVE;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mscan_start(काष्ठा net_device *dev)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	u8 canrflg;
	पूर्णांक err;

	out_8(&regs->canrier, 0);

	INIT_LIST_HEAD(&priv->tx_head);
	priv->prev_buf_id = 0;
	priv->cur_pri = 0;
	priv->tx_active = 0;
	priv->shaकरोw_canrier = 0;
	priv->flags = 0;

	अगर (priv->type == MSCAN_TYPE_MPC5121) अणु
		/* Clear pending bus-off condition */
		अगर (in_8(&regs->canmisc) & MSCAN_BOHOLD)
			out_8(&regs->canmisc, MSCAN_BOHOLD);
	पूर्ण

	err = mscan_set_mode(dev, MSCAN_NORMAL_MODE);
	अगर (err)
		वापस err;

	canrflg = in_8(&regs->canrflg);
	priv->shaकरोw_statflg = canrflg & MSCAN_STAT_MSK;
	priv->can.state = state_map[max(MSCAN_STATE_RX(canrflg),
				    MSCAN_STATE_TX(canrflg))];
	out_8(&regs->cantier, 0);

	/* Enable receive पूर्णांकerrupts. */
	out_8(&regs->canrier, MSCAN_RX_INTS_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक mscan_restart(काष्ठा net_device *dev)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);

	अगर (priv->type == MSCAN_TYPE_MPC5121) अणु
		काष्ठा mscan_regs __iomem *regs = priv->reg_base;

		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		WARN(!(in_8(&regs->canmisc) & MSCAN_BOHOLD),
		     "bus-off state expected\n");
		out_8(&regs->canmisc, MSCAN_BOHOLD);
		/* Re-enable receive पूर्णांकerrupts. */
		out_8(&regs->canrier, MSCAN_RX_INTS_ENABLE);
	पूर्ण अन्यथा अणु
		अगर (priv->can.state <= CAN_STATE_BUS_OFF)
			mscan_set_mode(dev, MSCAN_INIT_MODE);
		वापस mscan_start(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_tx_t mscan_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा can_frame *frame = (काष्ठा can_frame *)skb->data;
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	पूर्णांक i, rtr, buf_id;
	u32 can_id;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	out_8(&regs->cantier, 0);

	i = ~priv->tx_active & MSCAN_TXE;
	buf_id = ffs(i) - 1;
	चयन (hweight8(i)) अणु
	हाल 0:
		netअगर_stop_queue(dev);
		netdev_err(dev, "Tx Ring full when queue awake!\n");
		वापस NETDEV_TX_BUSY;
	हाल 1:
		/*
		 * अगर buf_id < 3, then current frame will be send out of order,
		 * since buffer with lower id have higher priority (hell..)
		 */
		netअगर_stop_queue(dev);
		fallthrough;
	हाल 2:
		अगर (buf_id < priv->prev_buf_id) अणु
			priv->cur_pri++;
			अगर (priv->cur_pri == 0xff) अणु
				set_bit(F_TX_WAIT_ALL, &priv->flags);
				netअगर_stop_queue(dev);
			पूर्ण
		पूर्ण
		set_bit(F_TX_PROGRESS, &priv->flags);
		अवरोध;
	पूर्ण
	priv->prev_buf_id = buf_id;
	out_8(&regs->cantbsel, i);

	rtr = frame->can_id & CAN_RTR_FLAG;

	/* RTR is always the lowest bit of पूर्णांकerest, then IDs follow */
	अगर (frame->can_id & CAN_EFF_FLAG) अणु
		can_id = (frame->can_id & CAN_EFF_MASK)
			 << (MSCAN_EFF_RTR_SHIFT + 1);
		अगर (rtr)
			can_id |= 1 << MSCAN_EFF_RTR_SHIFT;
		out_be16(&regs->tx.idr3_2, can_id);

		can_id >>= 16;
		/* EFF_FLAGS are between the IDs :( */
		can_id = (can_id & 0x7) | ((can_id << 2) & 0xffe0)
			 | MSCAN_EFF_FLAGS;
	पूर्ण अन्यथा अणु
		can_id = (frame->can_id & CAN_SFF_MASK)
			 << (MSCAN_SFF_RTR_SHIFT + 1);
		अगर (rtr)
			can_id |= 1 << MSCAN_SFF_RTR_SHIFT;
	पूर्ण
	out_be16(&regs->tx.idr1_0, can_id);

	अगर (!rtr) अणु
		व्योम __iomem *data = &regs->tx.dsr1_0;
		u16 *payload = (u16 *)frame->data;

		क्रम (i = 0; i < frame->len / 2; i++) अणु
			out_be16(data, *payload++);
			data += 2 + _MSCAN_RESERVED_DSR_SIZE;
		पूर्ण
		/* ग_लिखो reमुख्यing byte अगर necessary */
		अगर (frame->len & 1)
			out_8(data, frame->data[frame->len - 1]);
	पूर्ण

	out_8(&regs->tx.dlr, frame->len);
	out_8(&regs->tx.tbpr, priv->cur_pri);

	/* Start transmission. */
	out_8(&regs->cantflg, 1 << buf_id);

	अगर (!test_bit(F_TX_PROGRESS, &priv->flags))
		netअगर_trans_update(dev);

	list_add_tail(&priv->tx_queue[buf_id].list, &priv->tx_head);

	can_put_echo_skb(skb, dev, buf_id, 0);

	/* Enable पूर्णांकerrupt. */
	priv->tx_active |= 1 << buf_id;
	out_8(&regs->cantier, priv->tx_active);

	वापस NETDEV_TX_OK;
पूर्ण

अटल क्रमागत can_state get_new_state(काष्ठा net_device *dev, u8 canrflg)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);

	अगर (unlikely(canrflg & MSCAN_CSCIF))
		वापस state_map[max(MSCAN_STATE_RX(canrflg),
				 MSCAN_STATE_TX(canrflg))];

	वापस priv->can.state;
पूर्ण

अटल व्योम mscan_get_rx_frame(काष्ठा net_device *dev, काष्ठा can_frame *frame)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	u32 can_id;
	पूर्णांक i;

	can_id = in_be16(&regs->rx.idr1_0);
	अगर (can_id & (1 << 3)) अणु
		frame->can_id = CAN_EFF_FLAG;
		can_id = ((can_id << 16) | in_be16(&regs->rx.idr3_2));
		can_id = ((can_id & 0xffe00000) |
			  ((can_id & 0x7ffff) << 2)) >> 2;
	पूर्ण अन्यथा अणु
		can_id >>= 4;
		frame->can_id = 0;
	पूर्ण

	frame->can_id |= can_id >> 1;
	अगर (can_id & 1)
		frame->can_id |= CAN_RTR_FLAG;

	frame->len = can_cc_dlc2len(in_8(&regs->rx.dlr) & 0xf);

	अगर (!(frame->can_id & CAN_RTR_FLAG)) अणु
		व्योम __iomem *data = &regs->rx.dsr1_0;
		u16 *payload = (u16 *)frame->data;

		क्रम (i = 0; i < frame->len / 2; i++) अणु
			*payload++ = in_be16(data);
			data += 2 + _MSCAN_RESERVED_DSR_SIZE;
		पूर्ण
		/* पढ़ो reमुख्यing byte अगर necessary */
		अगर (frame->len & 1)
			frame->data[frame->len - 1] = in_8(data);
	पूर्ण

	out_8(&regs->canrflg, MSCAN_RXF);
पूर्ण

अटल व्योम mscan_get_err_frame(काष्ठा net_device *dev, काष्ठा can_frame *frame,
				u8 canrflg)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	काष्ठा net_device_stats *stats = &dev->stats;
	क्रमागत can_state new_state;

	netdev_dbg(dev, "error interrupt (canrflg=%#x)\n", canrflg);
	frame->can_id = CAN_ERR_FLAG;

	अगर (canrflg & MSCAN_OVRIF) अणु
		frame->can_id |= CAN_ERR_CRTL;
		frame->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		stats->rx_errors++;
	पूर्ण अन्यथा अणु
		frame->data[1] = 0;
	पूर्ण

	new_state = get_new_state(dev, canrflg);
	अगर (new_state != priv->can.state) अणु
		can_change_state(dev, frame,
				 state_map[MSCAN_STATE_TX(canrflg)],
				 state_map[MSCAN_STATE_RX(canrflg)]);

		अगर (priv->can.state == CAN_STATE_BUS_OFF) अणु
			/*
			 * The MSCAN on the MPC5200 करोes recover from bus-off
			 * स्वतःmatically. To aव्योम that we stop the chip करोing
			 * a light-weight stop (we are in irq-context).
			 */
			अगर (priv->type != MSCAN_TYPE_MPC5121) अणु
				out_8(&regs->cantier, 0);
				out_8(&regs->canrier, 0);
				setbits8(&regs->canctl0,
					 MSCAN_SLPRQ | MSCAN_INITRQ);
			पूर्ण
			can_bus_off(dev);
		पूर्ण
	पूर्ण
	priv->shaकरोw_statflg = canrflg & MSCAN_STAT_MSK;
	frame->len = CAN_ERR_DLC;
	out_8(&regs->canrflg, MSCAN_ERR_IF);
पूर्ण

अटल पूर्णांक mscan_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा mscan_priv *priv = container_of(napi, काष्ठा mscan_priv, napi);
	काष्ठा net_device *dev = napi->dev;
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	काष्ठा net_device_stats *stats = &dev->stats;
	पूर्णांक work_करोne = 0;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *frame;
	u8 canrflg;

	जबतक (work_करोne < quota) अणु
		canrflg = in_8(&regs->canrflg);
		अगर (!(canrflg & (MSCAN_RXF | MSCAN_ERR_IF)))
			अवरोध;

		skb = alloc_can_skb(dev, &frame);
		अगर (!skb) अणु
			अगर (prपूर्णांकk_ratelimit())
				netdev_notice(dev, "packet dropped\n");
			stats->rx_dropped++;
			out_8(&regs->canrflg, canrflg);
			जारी;
		पूर्ण

		अगर (canrflg & MSCAN_RXF)
			mscan_get_rx_frame(dev, frame);
		अन्यथा अगर (canrflg & MSCAN_ERR_IF)
			mscan_get_err_frame(dev, frame, canrflg);

		stats->rx_packets++;
		stats->rx_bytes += frame->len;
		work_करोne++;
		netअगर_receive_skb(skb);
	पूर्ण

	अगर (work_करोne < quota) अणु
		अगर (likely(napi_complete_करोne(&priv->napi, work_करोne))) अणु
			clear_bit(F_RX_PROGRESS, &priv->flags);
			अगर (priv->can.state < CAN_STATE_BUS_OFF)
				out_8(&regs->canrier, priv->shaकरोw_canrier);
		पूर्ण
	पूर्ण
	वापस work_करोne;
पूर्ण

अटल irqवापस_t mscan_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	काष्ठा net_device_stats *stats = &dev->stats;
	u8 cantier, cantflg, canrflg;
	irqवापस_t ret = IRQ_NONE;

	cantier = in_8(&regs->cantier) & MSCAN_TXE;
	cantflg = in_8(&regs->cantflg) & cantier;

	अगर (cantier && cantflg) अणु
		काष्ठा list_head *पंचांगp, *pos;

		list_क्रम_each_safe(pos, पंचांगp, &priv->tx_head) अणु
			काष्ठा tx_queue_entry *entry =
			    list_entry(pos, काष्ठा tx_queue_entry, list);
			u8 mask = entry->mask;

			अगर (!(cantflg & mask))
				जारी;

			out_8(&regs->cantbsel, mask);
			stats->tx_bytes += in_8(&regs->tx.dlr);
			stats->tx_packets++;
			can_get_echo_skb(dev, entry->id, शून्य);
			priv->tx_active &= ~mask;
			list_del(pos);
		पूर्ण

		अगर (list_empty(&priv->tx_head)) अणु
			clear_bit(F_TX_WAIT_ALL, &priv->flags);
			clear_bit(F_TX_PROGRESS, &priv->flags);
			priv->cur_pri = 0;
		पूर्ण अन्यथा अणु
			netअगर_trans_update(dev);
		पूर्ण

		अगर (!test_bit(F_TX_WAIT_ALL, &priv->flags))
			netअगर_wake_queue(dev);

		out_8(&regs->cantier, priv->tx_active);
		ret = IRQ_HANDLED;
	पूर्ण

	canrflg = in_8(&regs->canrflg);
	अगर ((canrflg & ~MSCAN_STAT_MSK) &&
	    !test_and_set_bit(F_RX_PROGRESS, &priv->flags)) अणु
		अगर (canrflg & ~MSCAN_STAT_MSK) अणु
			priv->shaकरोw_canrier = in_8(&regs->canrier);
			out_8(&regs->canrier, 0);
			napi_schedule(&priv->napi);
			ret = IRQ_HANDLED;
		पूर्ण अन्यथा अणु
			clear_bit(F_RX_PROGRESS, &priv->flags);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mscan_करो_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	पूर्णांक ret = 0;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		ret = mscan_restart(dev);
		अगर (ret)
			अवरोध;
		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mscan_करो_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u8 btr0, btr1;

	btr0 = BTR0_SET_BRP(bt->brp) | BTR0_SET_SJW(bt->sjw);
	btr1 = (BTR1_SET_TSEG1(bt->prop_seg + bt->phase_seg1) |
		BTR1_SET_TSEG2(bt->phase_seg2) |
		BTR1_SET_SAM(priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES));

	netdev_info(dev, "setting BTR0=0x%02x BTR1=0x%02x\n", btr0, btr1);

	out_8(&regs->canbtr0, btr0);
	out_8(&regs->canbtr1, btr1);

	वापस 0;
पूर्ण

अटल पूर्णांक mscan_get_berr_counter(स्थिर काष्ठा net_device *dev,
				  काष्ठा can_berr_counter *bec)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;

	bec->txerr = in_8(&regs->cantxerr);
	bec->rxerr = in_8(&regs->canrxerr);

	वापस 0;
पूर्ण

अटल पूर्णांक mscan_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;

	ret = clk_prepare_enable(priv->clk_ipg);
	अगर (ret)
		जाओ निकास_retcode;
	ret = clk_prepare_enable(priv->clk_can);
	अगर (ret)
		जाओ निकास_dis_ipg_घड़ी;

	/* common खोलो */
	ret = खोलो_candev(dev);
	अगर (ret)
		जाओ निकास_dis_can_घड़ी;

	napi_enable(&priv->napi);

	ret = request_irq(dev->irq, mscan_isr, 0, dev->name, dev);
	अगर (ret < 0) अणु
		netdev_err(dev, "failed to attach interrupt\n");
		जाओ निकास_napi_disable;
	पूर्ण

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		setbits8(&regs->canctl1, MSCAN_LISTEN);
	अन्यथा
		clrbits8(&regs->canctl1, MSCAN_LISTEN);

	ret = mscan_start(dev);
	अगर (ret)
		जाओ निकास_मुक्त_irq;

	netअगर_start_queue(dev);

	वापस 0;

निकास_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
निकास_napi_disable:
	napi_disable(&priv->napi);
	बंद_candev(dev);
निकास_dis_can_घड़ी:
	clk_disable_unprepare(priv->clk_can);
निकास_dis_ipg_घड़ी:
	clk_disable_unprepare(priv->clk_ipg);
निकास_retcode:
	वापस ret;
पूर्ण

अटल पूर्णांक mscan_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;

	netअगर_stop_queue(dev);
	napi_disable(&priv->napi);

	out_8(&regs->cantier, 0);
	out_8(&regs->canrier, 0);
	mscan_set_mode(dev, MSCAN_INIT_MODE);
	बंद_candev(dev);
	मुक्त_irq(dev->irq, dev);

	clk_disable_unprepare(priv->clk_can);
	clk_disable_unprepare(priv->clk_ipg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mscan_netdev_ops = अणु
	.nकरो_खोलो	= mscan_खोलो,
	.nकरो_stop	= mscan_बंद,
	.nकरो_start_xmit	= mscan_start_xmit,
	.nकरो_change_mtu	= can_change_mtu,
पूर्ण;

पूर्णांक रेजिस्टर_mscandev(काष्ठा net_device *dev, पूर्णांक mscan_clksrc)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	u8 ctl1;

	ctl1 = in_8(&regs->canctl1);
	अगर (mscan_clksrc)
		ctl1 |= MSCAN_CLKSRC;
	अन्यथा
		ctl1 &= ~MSCAN_CLKSRC;

	अगर (priv->type == MSCAN_TYPE_MPC5121) अणु
		priv->can.करो_get_berr_counter = mscan_get_berr_counter;
		ctl1 |= MSCAN_BORM; /* bus-off recovery upon request */
	पूर्ण

	ctl1 |= MSCAN_CANE;
	out_8(&regs->canctl1, ctl1);
	udelay(100);

	/* acceptance mask/acceptance code (accept everything) */
	out_be16(&regs->canidar1_0, 0);
	out_be16(&regs->canidar3_2, 0);
	out_be16(&regs->canidar5_4, 0);
	out_be16(&regs->canidar7_6, 0);

	out_be16(&regs->canidmr1_0, 0xffff);
	out_be16(&regs->canidmr3_2, 0xffff);
	out_be16(&regs->canidmr5_4, 0xffff);
	out_be16(&regs->canidmr7_6, 0xffff);
	/* Two 32 bit Acceptance Filters */
	out_8(&regs->canidac, MSCAN_AF_32BIT);

	mscan_set_mode(dev, MSCAN_INIT_MODE);

	वापस रेजिस्टर_candev(dev);
पूर्ण

व्योम unरेजिस्टर_mscandev(काष्ठा net_device *dev)
अणु
	काष्ठा mscan_priv *priv = netdev_priv(dev);
	काष्ठा mscan_regs __iomem *regs = priv->reg_base;
	mscan_set_mode(dev, MSCAN_INIT_MODE);
	clrbits8(&regs->canctl1, MSCAN_CANE);
	unरेजिस्टर_candev(dev);
पूर्ण

काष्ठा net_device *alloc_mscandev(व्योम)
अणु
	काष्ठा net_device *dev;
	काष्ठा mscan_priv *priv;
	पूर्णांक i;

	dev = alloc_candev(माप(काष्ठा mscan_priv), MSCAN_ECHO_SKB_MAX);
	अगर (!dev)
		वापस शून्य;
	priv = netdev_priv(dev);

	dev->netdev_ops = &mscan_netdev_ops;

	dev->flags |= IFF_ECHO;	/* we support local echo */

	netअगर_napi_add(dev, &priv->napi, mscan_rx_poll, 8);

	priv->can.bittiming_स्थिर = &mscan_bittiming_स्थिर;
	priv->can.करो_set_bittiming = mscan_करो_set_bittiming;
	priv->can.करो_set_mode = mscan_करो_set_mode;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_LISTENONLY;

	क्रम (i = 0; i < TX_QUEUE_SIZE; i++) अणु
		priv->tx_queue[i].id = i;
		priv->tx_queue[i].mask = 1 << i;
	पूर्ण

	वापस dev;
पूर्ण

MODULE_AUTHOR("Andrey Volkov <avolkov@varma-el.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CAN port driver for a MSCAN based chips");
