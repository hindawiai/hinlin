<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* CAN bus driver क्रम Holt HI3110 CAN Controller with SPI Interface
 *
 * Copyright(C) Timesys Corporation 2016
 *
 * Based on Microchip 251x CAN Controller (mcp251x) Linux kernel driver
 * Copyright 2009 Christian Pellegrin EVOL S.r.l.
 * Copyright 2007 Raymarine UK, Ltd. All Rights Reserved.
 * Copyright 2006 Arcom Control Systems Ltd.
 *
 * Based on CAN bus driver क्रम the CCAN controller written by
 * - Sascha Hauer, Marc Kleine-Budde, Pengutronix
 * - Simon Kallweit, पूर्णांकefo AG
 * Copyright 2007
 */

#समावेश <linux/can/core.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/led.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/uaccess.h>

#घोषणा HI3110_MASTER_RESET 0x56
#घोषणा HI3110_READ_CTRL0 0xD2
#घोषणा HI3110_READ_CTRL1 0xD4
#घोषणा HI3110_READ_STATF 0xE2
#घोषणा HI3110_WRITE_CTRL0 0x14
#घोषणा HI3110_WRITE_CTRL1 0x16
#घोषणा HI3110_WRITE_INTE 0x1C
#घोषणा HI3110_WRITE_BTR0 0x18
#घोषणा HI3110_WRITE_BTR1 0x1A
#घोषणा HI3110_READ_BTR0 0xD6
#घोषणा HI3110_READ_BTR1 0xD8
#घोषणा HI3110_READ_INTF 0xDE
#घोषणा HI3110_READ_ERR 0xDC
#घोषणा HI3110_READ_FIFO_WOTIME 0x48
#घोषणा HI3110_WRITE_FIFO 0x12
#घोषणा HI3110_READ_MESSTAT 0xDA
#घोषणा HI3110_READ_REC 0xEA
#घोषणा HI3110_READ_TEC 0xEC

#घोषणा HI3110_CTRL0_MODE_MASK (7 << 5)
#घोषणा HI3110_CTRL0_NORMAL_MODE (0 << 5)
#घोषणा HI3110_CTRL0_LOOPBACK_MODE (1 << 5)
#घोषणा HI3110_CTRL0_MONITOR_MODE (2 << 5)
#घोषणा HI3110_CTRL0_SLEEP_MODE (3 << 5)
#घोषणा HI3110_CTRL0_INIT_MODE (4 << 5)

#घोषणा HI3110_CTRL1_TXEN BIT(7)

#घोषणा HI3110_INT_RXTMP BIT(7)
#घोषणा HI3110_INT_RXFIFO BIT(6)
#घोषणा HI3110_INT_TXCPLT BIT(5)
#घोषणा HI3110_INT_BUSERR BIT(4)
#घोषणा HI3110_INT_MCHG BIT(3)
#घोषणा HI3110_INT_WAKEUP BIT(2)
#घोषणा HI3110_INT_F1MESS BIT(1)
#घोषणा HI3110_INT_F0MESS BIT(0)

#घोषणा HI3110_ERR_BUSOFF BIT(7)
#घोषणा HI3110_ERR_TXERRP BIT(6)
#घोषणा HI3110_ERR_RXERRP BIT(5)
#घोषणा HI3110_ERR_BITERR BIT(4)
#घोषणा HI3110_ERR_FRMERR BIT(3)
#घोषणा HI3110_ERR_CRCERR BIT(2)
#घोषणा HI3110_ERR_ACKERR BIT(1)
#घोषणा HI3110_ERR_STUFERR BIT(0)
#घोषणा HI3110_ERR_PROTOCOL_MASK (0x1F)
#घोषणा HI3110_ERR_PASSIVE_MASK (0x60)

#घोषणा HI3110_STAT_RXFMTY BIT(1)
#घोषणा HI3110_STAT_BUSOFF BIT(2)
#घोषणा HI3110_STAT_ERRP BIT(3)
#घोषणा HI3110_STAT_ERRW BIT(4)
#घोषणा HI3110_STAT_TXMTY BIT(7)

#घोषणा HI3110_BTR0_SJW_SHIFT 6
#घोषणा HI3110_BTR0_BRP_SHIFT 0

#घोषणा HI3110_BTR1_SAMP_3PERBIT (1 << 7)
#घोषणा HI3110_BTR1_SAMP_1PERBIT (0 << 7)
#घोषणा HI3110_BTR1_TSEG2_SHIFT 4
#घोषणा HI3110_BTR1_TSEG1_SHIFT 0

#घोषणा HI3110_FIFO_WOTIME_TAG_OFF 0
#घोषणा HI3110_FIFO_WOTIME_ID_OFF 1
#घोषणा HI3110_FIFO_WOTIME_DLC_OFF 5
#घोषणा HI3110_FIFO_WOTIME_DAT_OFF 6

#घोषणा HI3110_FIFO_WOTIME_TAG_IDE BIT(7)
#घोषणा HI3110_FIFO_WOTIME_ID_RTR BIT(0)

#घोषणा HI3110_FIFO_TAG_OFF 0
#घोषणा HI3110_FIFO_ID_OFF 1
#घोषणा HI3110_FIFO_STD_DLC_OFF 3
#घोषणा HI3110_FIFO_STD_DATA_OFF 4
#घोषणा HI3110_FIFO_EXT_DLC_OFF 5
#घोषणा HI3110_FIFO_EXT_DATA_OFF 6

#घोषणा HI3110_CAN_MAX_DATA_LEN 8
#घोषणा HI3110_RX_BUF_LEN 15
#घोषणा HI3110_TX_STD_BUF_LEN 12
#घोषणा HI3110_TX_EXT_BUF_LEN 14
#घोषणा HI3110_CAN_FRAME_MAX_BITS 128
#घोषणा HI3110_EFF_FLAGS 0x18 /* IDE + SRR */

#घोषणा HI3110_TX_ECHO_SKB_MAX 1

#घोषणा HI3110_OST_DELAY_MS (10)

#घोषणा DEVICE_NAME "hi3110"

अटल स्थिर काष्ठा can_bittiming_स्थिर hi3110_bittiming_स्थिर = अणु
	.name = DEVICE_NAME,
	.tseg1_min = 2,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

क्रमागत hi3110_model अणु
	CAN_HI3110_HI3110 = 0x3110,
पूर्ण;

काष्ठा hi3110_priv अणु
	काष्ठा can_priv can;
	काष्ठा net_device *net;
	काष्ठा spi_device *spi;
	क्रमागत hi3110_model model;

	काष्ठा mutex hi3110_lock; /* SPI device lock */

	u8 *spi_tx_buf;
	u8 *spi_rx_buf;

	काष्ठा sk_buff *tx_skb;
	पूर्णांक tx_len;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा work_काष्ठा restart_work;

	पूर्णांक क्रमce_quit;
	पूर्णांक after_suspend;
#घोषणा HI3110_AFTER_SUSPEND_UP 1
#घोषणा HI3110_AFTER_SUSPEND_DOWN 2
#घोषणा HI3110_AFTER_SUSPEND_POWER 4
#घोषणा HI3110_AFTER_SUSPEND_RESTART 8
	पूर्णांक restart_tx;
	काष्ठा regulator *घातer;
	काष्ठा regulator *transceiver;
	काष्ठा clk *clk;
पूर्ण;

अटल व्योम hi3110_clean(काष्ठा net_device *net)
अणु
	काष्ठा hi3110_priv *priv = netdev_priv(net);

	अगर (priv->tx_skb || priv->tx_len)
		net->stats.tx_errors++;
	dev_kमुक्त_skb(priv->tx_skb);
	अगर (priv->tx_len)
		can_मुक्त_echo_skb(priv->net, 0, शून्य);
	priv->tx_skb = शून्य;
	priv->tx_len = 0;
पूर्ण

/* Note about handling of error वापस of hi3110_spi_trans: accessing
 * रेजिस्टरs via SPI is not really dअगरferent conceptually than using
 * normal I/O assembler inकाष्ठाions, although it's much more
 * complicated from a practical POV. So it's not advisable to always
 * check the वापस value of this function. Imagine that every
 * पढ़ोअणुb,lपूर्ण, ग_लिखोअणुb,lपूर्ण and मित्रs would be bracketed in "अगर ( < 0)
 * error();", it would be a great mess (well there are some situation
 * when exception handling C++ like could be useful after all). So we
 * just check that transfers are OK at the beginning of our
 * conversation with the chip and to aव्योम करोing really nasty things
 * (like injecting bogus packets in the network stack).
 */
अटल पूर्णांक hi3110_spi_trans(काष्ठा spi_device *spi, पूर्णांक len)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);
	काष्ठा spi_transfer t = अणु
		.tx_buf = priv->spi_tx_buf,
		.rx_buf = priv->spi_rx_buf,
		.len = len,
		.cs_change = 0,
	पूर्ण;
	काष्ठा spi_message m;
	पूर्णांक ret;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);

	ret = spi_sync(spi, &m);

	अगर (ret)
		dev_err(&spi->dev, "spi transfer failed: ret = %d\n", ret);
	वापस ret;
पूर्ण

अटल u8 hi3110_cmd(काष्ठा spi_device *spi, u8 command)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = command;
	dev_dbg(&spi->dev, "hi3110_cmd: %02X\n", command);

	वापस hi3110_spi_trans(spi, 1);
पूर्ण

अटल u8 hi3110_पढ़ो(काष्ठा spi_device *spi, u8 command)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);
	u8 val = 0;

	priv->spi_tx_buf[0] = command;
	hi3110_spi_trans(spi, 2);
	val = priv->spi_rx_buf[1];

	वापस val;
पूर्ण

अटल व्योम hi3110_ग_लिखो(काष्ठा spi_device *spi, u8 reg, u8 val)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = reg;
	priv->spi_tx_buf[1] = val;
	hi3110_spi_trans(spi, 2);
पूर्ण

अटल व्योम hi3110_hw_tx_frame(काष्ठा spi_device *spi, u8 *buf, पूर्णांक len)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = HI3110_WRITE_FIFO;
	स_नकल(priv->spi_tx_buf + 1, buf, len);
	hi3110_spi_trans(spi, len + 1);
पूर्ण

अटल व्योम hi3110_hw_tx(काष्ठा spi_device *spi, काष्ठा can_frame *frame)
अणु
	u8 buf[HI3110_TX_EXT_BUF_LEN];

	buf[HI3110_FIFO_TAG_OFF] = 0;

	अगर (frame->can_id & CAN_EFF_FLAG) अणु
		/* Extended frame */
		buf[HI3110_FIFO_ID_OFF] = (frame->can_id & CAN_EFF_MASK) >> 21;
		buf[HI3110_FIFO_ID_OFF + 1] =
			(((frame->can_id & CAN_EFF_MASK) >> 13) & 0xe0) |
			HI3110_EFF_FLAGS |
			(((frame->can_id & CAN_EFF_MASK) >> 15) & 0x07);
		buf[HI3110_FIFO_ID_OFF + 2] =
			(frame->can_id & CAN_EFF_MASK) >> 7;
		buf[HI3110_FIFO_ID_OFF + 3] =
			((frame->can_id & CAN_EFF_MASK) << 1) |
			((frame->can_id & CAN_RTR_FLAG) ? 1 : 0);

		buf[HI3110_FIFO_EXT_DLC_OFF] = frame->len;

		स_नकल(buf + HI3110_FIFO_EXT_DATA_OFF,
		       frame->data, frame->len);

		hi3110_hw_tx_frame(spi, buf, HI3110_TX_EXT_BUF_LEN -
				   (HI3110_CAN_MAX_DATA_LEN - frame->len));
	पूर्ण अन्यथा अणु
		/* Standard frame */
		buf[HI3110_FIFO_ID_OFF] =   (frame->can_id & CAN_SFF_MASK) >> 3;
		buf[HI3110_FIFO_ID_OFF + 1] =
			((frame->can_id & CAN_SFF_MASK) << 5) |
			((frame->can_id & CAN_RTR_FLAG) ? (1 << 4) : 0);

		buf[HI3110_FIFO_STD_DLC_OFF] = frame->len;

		स_नकल(buf + HI3110_FIFO_STD_DATA_OFF,
		       frame->data, frame->len);

		hi3110_hw_tx_frame(spi, buf, HI3110_TX_STD_BUF_LEN -
				   (HI3110_CAN_MAX_DATA_LEN - frame->len));
	पूर्ण
पूर्ण

अटल व्योम hi3110_hw_rx_frame(काष्ठा spi_device *spi, u8 *buf)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = HI3110_READ_FIFO_WOTIME;
	hi3110_spi_trans(spi, HI3110_RX_BUF_LEN);
	स_नकल(buf, priv->spi_rx_buf + 1, HI3110_RX_BUF_LEN - 1);
पूर्ण

अटल व्योम hi3110_hw_rx(काष्ठा spi_device *spi)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *frame;
	u8 buf[HI3110_RX_BUF_LEN - 1];

	skb = alloc_can_skb(priv->net, &frame);
	अगर (!skb) अणु
		priv->net->stats.rx_dropped++;
		वापस;
	पूर्ण

	hi3110_hw_rx_frame(spi, buf);
	अगर (buf[HI3110_FIFO_WOTIME_TAG_OFF] & HI3110_FIFO_WOTIME_TAG_IDE) अणु
		/* IDE is recessive (1), indicating extended 29-bit frame */
		frame->can_id = CAN_EFF_FLAG;
		frame->can_id |=
			(buf[HI3110_FIFO_WOTIME_ID_OFF] << 21) |
			(((buf[HI3110_FIFO_WOTIME_ID_OFF + 1] & 0xE0) >> 5) << 18) |
			((buf[HI3110_FIFO_WOTIME_ID_OFF + 1] & 0x07) << 15) |
			(buf[HI3110_FIFO_WOTIME_ID_OFF + 2] << 7) |
			(buf[HI3110_FIFO_WOTIME_ID_OFF + 3] >> 1);
	पूर्ण अन्यथा अणु
		/* IDE is करोminant (0), frame indicating standard 11-bit */
		frame->can_id =
			(buf[HI3110_FIFO_WOTIME_ID_OFF] << 3) |
			((buf[HI3110_FIFO_WOTIME_ID_OFF + 1] & 0xE0) >> 5);
	पूर्ण

	/* Data length */
	frame->len = can_cc_dlc2len(buf[HI3110_FIFO_WOTIME_DLC_OFF] & 0x0F);

	अगर (buf[HI3110_FIFO_WOTIME_ID_OFF + 3] & HI3110_FIFO_WOTIME_ID_RTR)
		frame->can_id |= CAN_RTR_FLAG;
	अन्यथा
		स_नकल(frame->data, buf + HI3110_FIFO_WOTIME_DAT_OFF,
		       frame->len);

	priv->net->stats.rx_packets++;
	priv->net->stats.rx_bytes += frame->len;

	can_led_event(priv->net, CAN_LED_EVENT_RX);

	netअगर_rx_ni(skb);
पूर्ण

अटल व्योम hi3110_hw_sleep(काष्ठा spi_device *spi)
अणु
	hi3110_ग_लिखो(spi, HI3110_WRITE_CTRL0, HI3110_CTRL0_SLEEP_MODE);
पूर्ण

अटल netdev_tx_t hi3110_hard_start_xmit(काष्ठा sk_buff *skb,
					  काष्ठा net_device *net)
अणु
	काष्ठा hi3110_priv *priv = netdev_priv(net);
	काष्ठा spi_device *spi = priv->spi;

	अगर (priv->tx_skb || priv->tx_len) अणु
		dev_err(&spi->dev, "hard_xmit called while tx busy\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (can_dropped_invalid_skb(net, skb))
		वापस NETDEV_TX_OK;

	netअगर_stop_queue(net);
	priv->tx_skb = skb;
	queue_work(priv->wq, &priv->tx_work);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक hi3110_करो_set_mode(काष्ठा net_device *net, क्रमागत can_mode mode)
अणु
	काष्ठा hi3110_priv *priv = netdev_priv(net);

	चयन (mode) अणु
	हाल CAN_MODE_START:
		hi3110_clean(net);
		/* We have to delay work since SPI I/O may sleep */
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		priv->restart_tx = 1;
		अगर (priv->can.restart_ms == 0)
			priv->after_suspend = HI3110_AFTER_SUSPEND_RESTART;
		queue_work(priv->wq, &priv->restart_work);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hi3110_get_berr_counter(स्थिर काष्ठा net_device *net,
				   काष्ठा can_berr_counter *bec)
अणु
	काष्ठा hi3110_priv *priv = netdev_priv(net);
	काष्ठा spi_device *spi = priv->spi;

	mutex_lock(&priv->hi3110_lock);
	bec->txerr = hi3110_पढ़ो(spi, HI3110_READ_TEC);
	bec->rxerr = hi3110_पढ़ो(spi, HI3110_READ_REC);
	mutex_unlock(&priv->hi3110_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hi3110_set_normal_mode(काष्ठा spi_device *spi)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);
	u8 reg = 0;

	hi3110_ग_लिखो(spi, HI3110_WRITE_INTE, HI3110_INT_BUSERR |
		     HI3110_INT_RXFIFO | HI3110_INT_TXCPLT);

	/* Enable TX */
	hi3110_ग_लिखो(spi, HI3110_WRITE_CTRL1, HI3110_CTRL1_TXEN);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		reg = HI3110_CTRL0_LOOPBACK_MODE;
	अन्यथा अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		reg = HI3110_CTRL0_MONITOR_MODE;
	अन्यथा
		reg = HI3110_CTRL0_NORMAL_MODE;

	hi3110_ग_लिखो(spi, HI3110_WRITE_CTRL0, reg);

	/* Wait क्रम the device to enter the mode */
	mdelay(HI3110_OST_DELAY_MS);
	reg = hi3110_पढ़ो(spi, HI3110_READ_CTRL0);
	अगर ((reg & HI3110_CTRL0_MODE_MASK) != reg)
		वापस -EBUSY;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	वापस 0;
पूर्ण

अटल पूर्णांक hi3110_करो_set_bittiming(काष्ठा net_device *net)
अणु
	काष्ठा hi3110_priv *priv = netdev_priv(net);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा spi_device *spi = priv->spi;

	hi3110_ग_लिखो(spi, HI3110_WRITE_BTR0,
		     ((bt->sjw - 1) << HI3110_BTR0_SJW_SHIFT) |
		     ((bt->brp - 1) << HI3110_BTR0_BRP_SHIFT));

	hi3110_ग_लिखो(spi, HI3110_WRITE_BTR1,
		     (priv->can.ctrlmode &
		      CAN_CTRLMODE_3_SAMPLES ?
		      HI3110_BTR1_SAMP_3PERBIT : HI3110_BTR1_SAMP_1PERBIT) |
		     ((bt->phase_seg1 + bt->prop_seg - 1)
		      << HI3110_BTR1_TSEG1_SHIFT) |
		     ((bt->phase_seg2 - 1) << HI3110_BTR1_TSEG2_SHIFT));

	dev_dbg(&spi->dev, "BT: 0x%02x 0x%02x\n",
		hi3110_पढ़ो(spi, HI3110_READ_BTR0),
		hi3110_पढ़ो(spi, HI3110_READ_BTR1));

	वापस 0;
पूर्ण

अटल पूर्णांक hi3110_setup(काष्ठा net_device *net)
अणु
	hi3110_करो_set_bittiming(net);
	वापस 0;
पूर्ण

अटल पूर्णांक hi3110_hw_reset(काष्ठा spi_device *spi)
अणु
	u8 reg;
	पूर्णांक ret;

	/* Wait क्रम oscillator startup समयr after घातer up */
	mdelay(HI3110_OST_DELAY_MS);

	ret = hi3110_cmd(spi, HI3110_MASTER_RESET);
	अगर (ret)
		वापस ret;

	/* Wait क्रम oscillator startup समयr after reset */
	mdelay(HI3110_OST_DELAY_MS);

	reg = hi3110_पढ़ो(spi, HI3110_READ_CTRL0);
	अगर ((reg & HI3110_CTRL0_MODE_MASK) != HI3110_CTRL0_INIT_MODE)
		वापस -ENODEV;

	/* As per the datasheet it appears the error flags are
	 * not cleared on reset. Explicitly clear them by perक्रमming a पढ़ो
	 */
	hi3110_पढ़ो(spi, HI3110_READ_ERR);

	वापस 0;
पूर्ण

अटल पूर्णांक hi3110_hw_probe(काष्ठा spi_device *spi)
अणु
	u8 statf;

	hi3110_hw_reset(spi);

	/* Confirm correct operation by checking against reset values
	 * in datasheet
	 */
	statf = hi3110_पढ़ो(spi, HI3110_READ_STATF);

	dev_dbg(&spi->dev, "statf: %02X\n", statf);

	अगर (statf != 0x82)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक hi3110_घातer_enable(काष्ठा regulator *reg, पूर्णांक enable)
अणु
	अगर (IS_ERR_OR_शून्य(reg))
		वापस 0;

	अगर (enable)
		वापस regulator_enable(reg);
	अन्यथा
		वापस regulator_disable(reg);
पूर्ण

अटल पूर्णांक hi3110_stop(काष्ठा net_device *net)
अणु
	काष्ठा hi3110_priv *priv = netdev_priv(net);
	काष्ठा spi_device *spi = priv->spi;

	बंद_candev(net);

	priv->क्रमce_quit = 1;
	मुक्त_irq(spi->irq, priv);
	destroy_workqueue(priv->wq);
	priv->wq = शून्य;

	mutex_lock(&priv->hi3110_lock);

	/* Disable transmit, पूर्णांकerrupts and clear flags */
	hi3110_ग_लिखो(spi, HI3110_WRITE_CTRL1, 0x0);
	hi3110_ग_लिखो(spi, HI3110_WRITE_INTE, 0x0);
	hi3110_पढ़ो(spi, HI3110_READ_INTF);

	hi3110_clean(net);

	hi3110_hw_sleep(spi);

	hi3110_घातer_enable(priv->transceiver, 0);

	priv->can.state = CAN_STATE_STOPPED;

	mutex_unlock(&priv->hi3110_lock);

	can_led_event(net, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल व्योम hi3110_tx_work_handler(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा hi3110_priv *priv = container_of(ws, काष्ठा hi3110_priv,
						tx_work);
	काष्ठा spi_device *spi = priv->spi;
	काष्ठा net_device *net = priv->net;
	काष्ठा can_frame *frame;

	mutex_lock(&priv->hi3110_lock);
	अगर (priv->tx_skb) अणु
		अगर (priv->can.state == CAN_STATE_BUS_OFF) अणु
			hi3110_clean(net);
		पूर्ण अन्यथा अणु
			frame = (काष्ठा can_frame *)priv->tx_skb->data;
			hi3110_hw_tx(spi, frame);
			priv->tx_len = 1 + frame->len;
			can_put_echo_skb(priv->tx_skb, net, 0, 0);
			priv->tx_skb = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->hi3110_lock);
पूर्ण

अटल व्योम hi3110_restart_work_handler(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा hi3110_priv *priv = container_of(ws, काष्ठा hi3110_priv,
						restart_work);
	काष्ठा spi_device *spi = priv->spi;
	काष्ठा net_device *net = priv->net;

	mutex_lock(&priv->hi3110_lock);
	अगर (priv->after_suspend) अणु
		hi3110_hw_reset(spi);
		hi3110_setup(net);
		अगर (priv->after_suspend & HI3110_AFTER_SUSPEND_RESTART) अणु
			hi3110_set_normal_mode(spi);
		पूर्ण अन्यथा अगर (priv->after_suspend & HI3110_AFTER_SUSPEND_UP) अणु
			netअगर_device_attach(net);
			hi3110_clean(net);
			hi3110_set_normal_mode(spi);
			netअगर_wake_queue(net);
		पूर्ण अन्यथा अणु
			hi3110_hw_sleep(spi);
		पूर्ण
		priv->after_suspend = 0;
		priv->क्रमce_quit = 0;
	पूर्ण

	अगर (priv->restart_tx) अणु
		priv->restart_tx = 0;
		hi3110_hw_reset(spi);
		hi3110_setup(net);
		hi3110_clean(net);
		hi3110_set_normal_mode(spi);
		netअगर_wake_queue(net);
	पूर्ण
	mutex_unlock(&priv->hi3110_lock);
पूर्ण

अटल irqवापस_t hi3110_can_ist(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hi3110_priv *priv = dev_id;
	काष्ठा spi_device *spi = priv->spi;
	काष्ठा net_device *net = priv->net;

	mutex_lock(&priv->hi3110_lock);

	जबतक (!priv->क्रमce_quit) अणु
		क्रमागत can_state new_state;
		u8 पूर्णांकf, eflag, statf;

		जबतक (!(HI3110_STAT_RXFMTY &
			 (statf = hi3110_पढ़ो(spi, HI3110_READ_STATF)))) अणु
			hi3110_hw_rx(spi);
		पूर्ण

		पूर्णांकf = hi3110_पढ़ो(spi, HI3110_READ_INTF);
		eflag = hi3110_पढ़ो(spi, HI3110_READ_ERR);
		/* Update can state */
		अगर (eflag & HI3110_ERR_BUSOFF)
			new_state = CAN_STATE_BUS_OFF;
		अन्यथा अगर (eflag & HI3110_ERR_PASSIVE_MASK)
			new_state = CAN_STATE_ERROR_PASSIVE;
		अन्यथा अगर (statf & HI3110_STAT_ERRW)
			new_state = CAN_STATE_ERROR_WARNING;
		अन्यथा
			new_state = CAN_STATE_ERROR_ACTIVE;

		अगर (new_state != priv->can.state) अणु
			काष्ठा can_frame *cf;
			काष्ठा sk_buff *skb;
			क्रमागत can_state rx_state, tx_state;
			u8 rxerr, txerr;

			skb = alloc_can_err_skb(net, &cf);
			अगर (!skb)
				अवरोध;

			txerr = hi3110_पढ़ो(spi, HI3110_READ_TEC);
			rxerr = hi3110_पढ़ो(spi, HI3110_READ_REC);
			cf->data[6] = txerr;
			cf->data[7] = rxerr;
			tx_state = txerr >= rxerr ? new_state : 0;
			rx_state = txerr <= rxerr ? new_state : 0;
			can_change_state(net, cf, tx_state, rx_state);
			netअगर_rx_ni(skb);

			अगर (new_state == CAN_STATE_BUS_OFF) अणु
				can_bus_off(net);
				अगर (priv->can.restart_ms == 0) अणु
					priv->क्रमce_quit = 1;
					hi3110_hw_sleep(spi);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Update bus errors */
		अगर ((पूर्णांकf & HI3110_INT_BUSERR) &&
		    (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)) अणु
			काष्ठा can_frame *cf;
			काष्ठा sk_buff *skb;

			/* Check क्रम protocol errors */
			अगर (eflag & HI3110_ERR_PROTOCOL_MASK) अणु
				skb = alloc_can_err_skb(net, &cf);
				अगर (!skb)
					अवरोध;

				cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
				priv->can.can_stats.bus_error++;
				priv->net->stats.rx_errors++;
				अगर (eflag & HI3110_ERR_BITERR)
					cf->data[2] |= CAN_ERR_PROT_BIT;
				अन्यथा अगर (eflag & HI3110_ERR_FRMERR)
					cf->data[2] |= CAN_ERR_PROT_FORM;
				अन्यथा अगर (eflag & HI3110_ERR_STUFERR)
					cf->data[2] |= CAN_ERR_PROT_STUFF;
				अन्यथा अगर (eflag & HI3110_ERR_CRCERR)
					cf->data[3] |= CAN_ERR_PROT_LOC_CRC_SEQ;
				अन्यथा अगर (eflag & HI3110_ERR_ACKERR)
					cf->data[3] |= CAN_ERR_PROT_LOC_ACK;

				cf->data[6] = hi3110_पढ़ो(spi, HI3110_READ_TEC);
				cf->data[7] = hi3110_पढ़ो(spi, HI3110_READ_REC);
				netdev_dbg(priv->net, "Bus Error\n");
				netअगर_rx_ni(skb);
			पूर्ण
		पूर्ण

		अगर (priv->tx_len && statf & HI3110_STAT_TXMTY) अणु
			net->stats.tx_packets++;
			net->stats.tx_bytes += priv->tx_len - 1;
			can_led_event(net, CAN_LED_EVENT_TX);
			अगर (priv->tx_len) अणु
				can_get_echo_skb(net, 0, शून्य);
				priv->tx_len = 0;
			पूर्ण
			netअगर_wake_queue(net);
		पूर्ण

		अगर (पूर्णांकf == 0)
			अवरोध;
	पूर्ण
	mutex_unlock(&priv->hi3110_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hi3110_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा hi3110_priv *priv = netdev_priv(net);
	काष्ठा spi_device *spi = priv->spi;
	अचिन्हित दीर्घ flags = IRQF_ONESHOT | IRQF_TRIGGER_HIGH;
	पूर्णांक ret;

	ret = खोलो_candev(net);
	अगर (ret)
		वापस ret;

	mutex_lock(&priv->hi3110_lock);
	hi3110_घातer_enable(priv->transceiver, 1);

	priv->क्रमce_quit = 0;
	priv->tx_skb = शून्य;
	priv->tx_len = 0;

	ret = request_thपढ़ोed_irq(spi->irq, शून्य, hi3110_can_ist,
				   flags, DEVICE_NAME, priv);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to acquire irq %d\n", spi->irq);
		जाओ out_बंद;
	पूर्ण

	priv->wq = alloc_workqueue("hi3110_wq", WQ_FREEZABLE | WQ_MEM_RECLAIM,
				   0);
	अगर (!priv->wq) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_irq;
	पूर्ण
	INIT_WORK(&priv->tx_work, hi3110_tx_work_handler);
	INIT_WORK(&priv->restart_work, hi3110_restart_work_handler);

	ret = hi3110_hw_reset(spi);
	अगर (ret)
		जाओ out_मुक्त_wq;

	ret = hi3110_setup(net);
	अगर (ret)
		जाओ out_मुक्त_wq;

	ret = hi3110_set_normal_mode(spi);
	अगर (ret)
		जाओ out_मुक्त_wq;

	can_led_event(net, CAN_LED_EVENT_OPEN);
	netअगर_wake_queue(net);
	mutex_unlock(&priv->hi3110_lock);

	वापस 0;

 out_मुक्त_wq:
	destroy_workqueue(priv->wq);
 out_मुक्त_irq:
	मुक्त_irq(spi->irq, priv);
	hi3110_hw_sleep(spi);
 out_बंद:
	hi3110_घातer_enable(priv->transceiver, 0);
	बंद_candev(net);
	mutex_unlock(&priv->hi3110_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops hi3110_netdev_ops = अणु
	.nकरो_खोलो = hi3110_खोलो,
	.nकरो_stop = hi3110_stop,
	.nकरो_start_xmit = hi3110_hard_start_xmit,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hi3110_of_match[] = अणु
	अणु
		.compatible	= "holt,hi3110",
		.data		= (व्योम *)CAN_HI3110_HI3110,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hi3110_of_match);

अटल स्थिर काष्ठा spi_device_id hi3110_id_table[] = अणु
	अणु
		.name		= "hi3110",
		.driver_data	= (kernel_uदीर्घ_t)CAN_HI3110_HI3110,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, hi3110_id_table);

अटल पूर्णांक hi3110_can_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा of_device_id *of_id = of_match_device(hi3110_of_match,
							   &spi->dev);
	काष्ठा net_device *net;
	काष्ठा hi3110_priv *priv;
	काष्ठा clk *clk;
	पूर्णांक freq, ret;

	clk = devm_clk_get(&spi->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&spi->dev, "no CAN clock source defined\n");
		वापस PTR_ERR(clk);
	पूर्ण
	freq = clk_get_rate(clk);

	/* Sanity check */
	अगर (freq > 40000000)
		वापस -दुस्फल;

	/* Allocate can/net device */
	net = alloc_candev(माप(काष्ठा hi3110_priv), HI3110_TX_ECHO_SKB_MAX);
	अगर (!net)
		वापस -ENOMEM;

	अगर (!IS_ERR(clk)) अणु
		ret = clk_prepare_enable(clk);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	net->netdev_ops = &hi3110_netdev_ops;
	net->flags |= IFF_ECHO;

	priv = netdev_priv(net);
	priv->can.bittiming_स्थिर = &hi3110_bittiming_स्थिर;
	priv->can.करो_set_mode = hi3110_करो_set_mode;
	priv->can.करो_get_berr_counter = hi3110_get_berr_counter;
	priv->can.घड़ी.freq = freq / 2;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_LOOPBACK |
		CAN_CTRLMODE_LISTENONLY |
		CAN_CTRLMODE_BERR_REPORTING;

	अगर (of_id)
		priv->model = (क्रमागत hi3110_model)of_id->data;
	अन्यथा
		priv->model = spi_get_device_id(spi)->driver_data;
	priv->net = net;
	priv->clk = clk;

	spi_set_drvdata(spi, priv);

	/* Configure the SPI bus */
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret)
		जाओ out_clk;

	priv->घातer = devm_regulator_get_optional(&spi->dev, "vdd");
	priv->transceiver = devm_regulator_get_optional(&spi->dev, "xceiver");
	अगर ((PTR_ERR(priv->घातer) == -EPROBE_DEFER) ||
	    (PTR_ERR(priv->transceiver) == -EPROBE_DEFER)) अणु
		ret = -EPROBE_DEFER;
		जाओ out_clk;
	पूर्ण

	ret = hi3110_घातer_enable(priv->घातer, 1);
	अगर (ret)
		जाओ out_clk;

	priv->spi = spi;
	mutex_init(&priv->hi3110_lock);

	priv->spi_tx_buf = devm_kzalloc(&spi->dev, HI3110_RX_BUF_LEN,
					GFP_KERNEL);
	अगर (!priv->spi_tx_buf) अणु
		ret = -ENOMEM;
		जाओ error_probe;
	पूर्ण
	priv->spi_rx_buf = devm_kzalloc(&spi->dev, HI3110_RX_BUF_LEN,
					GFP_KERNEL);

	अगर (!priv->spi_rx_buf) अणु
		ret = -ENOMEM;
		जाओ error_probe;
	पूर्ण

	SET_NETDEV_DEV(net, &spi->dev);

	ret = hi3110_hw_probe(spi);
	अगर (ret) अणु
		अगर (ret == -ENODEV)
			dev_err(&spi->dev, "Cannot initialize %x. Wrong wiring?\n",
				priv->model);
		जाओ error_probe;
	पूर्ण
	hi3110_hw_sleep(spi);

	ret = रेजिस्टर_candev(net);
	अगर (ret)
		जाओ error_probe;

	devm_can_led_init(net);
	netdev_info(net, "%x successfully initialized.\n", priv->model);

	वापस 0;

 error_probe:
	hi3110_घातer_enable(priv->घातer, 0);

 out_clk:
	अगर (!IS_ERR(clk))
		clk_disable_unprepare(clk);

 out_मुक्त:
	मुक्त_candev(net);

	dev_err(&spi->dev, "Probe failed, err=%d\n", -ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hi3110_can_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);
	काष्ठा net_device *net = priv->net;

	unरेजिस्टर_candev(net);

	hi3110_घातer_enable(priv->घातer, 0);

	अगर (!IS_ERR(priv->clk))
		clk_disable_unprepare(priv->clk);

	मुक्त_candev(net);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hi3110_can_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);
	काष्ठा net_device *net = priv->net;

	priv->क्रमce_quit = 1;
	disable_irq(spi->irq);

	/* Note: at this poपूर्णांक neither IST nor workqueues are running.
	 * खोलो/stop cannot be called anyway so locking is not needed
	 */
	अगर (netअगर_running(net)) अणु
		netअगर_device_detach(net);

		hi3110_hw_sleep(spi);
		hi3110_घातer_enable(priv->transceiver, 0);
		priv->after_suspend = HI3110_AFTER_SUSPEND_UP;
	पूर्ण अन्यथा अणु
		priv->after_suspend = HI3110_AFTER_SUSPEND_DOWN;
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(priv->घातer)) अणु
		regulator_disable(priv->घातer);
		priv->after_suspend |= HI3110_AFTER_SUSPEND_POWER;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hi3110_can_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा hi3110_priv *priv = spi_get_drvdata(spi);

	अगर (priv->after_suspend & HI3110_AFTER_SUSPEND_POWER)
		hi3110_घातer_enable(priv->घातer, 1);

	अगर (priv->after_suspend & HI3110_AFTER_SUSPEND_UP) अणु
		hi3110_घातer_enable(priv->transceiver, 1);
		queue_work(priv->wq, &priv->restart_work);
	पूर्ण अन्यथा अणु
		priv->after_suspend = 0;
	पूर्ण

	priv->क्रमce_quit = 0;
	enable_irq(spi->irq);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(hi3110_can_pm_ops, hi3110_can_suspend, hi3110_can_resume);

अटल काष्ठा spi_driver hi3110_can_driver = अणु
	.driver = अणु
		.name = DEVICE_NAME,
		.of_match_table = hi3110_of_match,
		.pm = &hi3110_can_pm_ops,
	पूर्ण,
	.id_table = hi3110_id_table,
	.probe = hi3110_can_probe,
	.हटाओ = hi3110_can_हटाओ,
पूर्ण;

module_spi_driver(hi3110_can_driver);

MODULE_AUTHOR("Akshay Bhat <akshay.bhat@timesys.com>");
MODULE_AUTHOR("Casey Fitzpatrick <casey.fitzpatrick@timesys.com>");
MODULE_DESCRIPTION("Holt HI-3110 CAN driver");
MODULE_LICENSE("GPL v2");
