<शैली गुरु>
/*
 * sun4i_can.c - CAN bus controller driver क्रम Allwinner SUN4I&SUN7I based SoCs
 *
 * Copyright (C) 2013 Peter Chen
 * Copyright (C) 2015 Gerhard Bertelsmann
 * All rights reserved.
 *
 * Parts of this software are based on (derived from) the SJA1000 code by:
 *   Copyright (C) 2014 Oliver Hartkopp <oliver.hartkopp@volkswagen.de>
 *   Copyright (C) 2007 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 *   Copyright (C) 2002-2007 Volkswagen Group Electronic Research
 *   Copyright (C) 2003 Matthias Brukner, Trajet Gmbh, Rebenring 33,
 *   38106 Braunschweig, GERMANY
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME "sun4i_can"

/* Registers address (physical base address 0x01C2BC00) */
#घोषणा SUN4I_REG_MSEL_ADDR	0x0000	/* CAN Mode Select */
#घोषणा SUN4I_REG_CMD_ADDR	0x0004	/* CAN Command */
#घोषणा SUN4I_REG_STA_ADDR	0x0008	/* CAN Status */
#घोषणा SUN4I_REG_INT_ADDR	0x000c	/* CAN Interrupt Flag */
#घोषणा SUN4I_REG_INTEN_ADDR	0x0010	/* CAN Interrupt Enable */
#घोषणा SUN4I_REG_BTIME_ADDR	0x0014	/* CAN Bus Timing 0 */
#घोषणा SUN4I_REG_TEWL_ADDR	0x0018	/* CAN Tx Error Warning Limit */
#घोषणा SUN4I_REG_ERRC_ADDR	0x001c	/* CAN Error Counter */
#घोषणा SUN4I_REG_RMCNT_ADDR	0x0020	/* CAN Receive Message Counter */
#घोषणा SUN4I_REG_RBUFSA_ADDR	0x0024	/* CAN Receive Buffer Start Address */
#घोषणा SUN4I_REG_BUF0_ADDR	0x0040	/* CAN Tx/Rx Buffer 0 */
#घोषणा SUN4I_REG_BUF1_ADDR	0x0044	/* CAN Tx/Rx Buffer 1 */
#घोषणा SUN4I_REG_BUF2_ADDR	0x0048	/* CAN Tx/Rx Buffer 2 */
#घोषणा SUN4I_REG_BUF3_ADDR	0x004c	/* CAN Tx/Rx Buffer 3 */
#घोषणा SUN4I_REG_BUF4_ADDR	0x0050	/* CAN Tx/Rx Buffer 4 */
#घोषणा SUN4I_REG_BUF5_ADDR	0x0054	/* CAN Tx/Rx Buffer 5 */
#घोषणा SUN4I_REG_BUF6_ADDR	0x0058	/* CAN Tx/Rx Buffer 6 */
#घोषणा SUN4I_REG_BUF7_ADDR	0x005c	/* CAN Tx/Rx Buffer 7 */
#घोषणा SUN4I_REG_BUF8_ADDR	0x0060	/* CAN Tx/Rx Buffer 8 */
#घोषणा SUN4I_REG_BUF9_ADDR	0x0064	/* CAN Tx/Rx Buffer 9 */
#घोषणा SUN4I_REG_BUF10_ADDR	0x0068	/* CAN Tx/Rx Buffer 10 */
#घोषणा SUN4I_REG_BUF11_ADDR	0x006c	/* CAN Tx/Rx Buffer 11 */
#घोषणा SUN4I_REG_BUF12_ADDR	0x0070	/* CAN Tx/Rx Buffer 12 */
#घोषणा SUN4I_REG_ACPC_ADDR	0x0040	/* CAN Acceptance Code 0 */
#घोषणा SUN4I_REG_ACPM_ADDR	0x0044	/* CAN Acceptance Mask 0 */
#घोषणा SUN4I_REG_RBUF_RBACK_START_ADDR	0x0180	/* CAN transmit buffer start */
#घोषणा SUN4I_REG_RBUF_RBACK_END_ADDR	0x01b0	/* CAN transmit buffer end */

/* Controller Register Description */

/* mode select रेजिस्टर (r/w)
 * offset:0x0000 शेष:0x0000_0001
 */
#घोषणा SUN4I_MSEL_SLEEP_MODE		(0x01 << 4) /* ग_लिखो in reset mode */
#घोषणा SUN4I_MSEL_WAKE_UP		(0x00 << 4)
#घोषणा SUN4I_MSEL_SINGLE_FILTER	(0x01 << 3) /* ग_लिखो in reset mode */
#घोषणा SUN4I_MSEL_DUAL_FILTERS		(0x00 << 3)
#घोषणा SUN4I_MSEL_LOOPBACK_MODE	BIT(2)
#घोषणा SUN4I_MSEL_LISTEN_ONLY_MODE	BIT(1)
#घोषणा SUN4I_MSEL_RESET_MODE		BIT(0)

/* command रेजिस्टर (w)
 * offset:0x0004 शेष:0x0000_0000
 */
#घोषणा SUN4I_CMD_BUS_OFF_REQ	BIT(5)
#घोषणा SUN4I_CMD_SELF_RCV_REQ	BIT(4)
#घोषणा SUN4I_CMD_CLEAR_OR_FLAG	BIT(3)
#घोषणा SUN4I_CMD_RELEASE_RBUF	BIT(2)
#घोषणा SUN4I_CMD_ABORT_REQ	BIT(1)
#घोषणा SUN4I_CMD_TRANS_REQ	BIT(0)

/* status रेजिस्टर (r)
 * offset:0x0008 शेष:0x0000_003c
 */
#घोषणा SUN4I_STA_BIT_ERR	(0x00 << 22)
#घोषणा SUN4I_STA_FORM_ERR	(0x01 << 22)
#घोषणा SUN4I_STA_STUFF_ERR	(0x02 << 22)
#घोषणा SUN4I_STA_OTHER_ERR	(0x03 << 22)
#घोषणा SUN4I_STA_MASK_ERR	(0x03 << 22)
#घोषणा SUN4I_STA_ERR_सूची	BIT(21)
#घोषणा SUN4I_STA_ERR_SEG_CODE	(0x1f << 16)
#घोषणा SUN4I_STA_START		(0x03 << 16)
#घोषणा SUN4I_STA_ID28_21	(0x02 << 16)
#घोषणा SUN4I_STA_ID20_18	(0x06 << 16)
#घोषणा SUN4I_STA_SRTR		(0x04 << 16)
#घोषणा SUN4I_STA_IDE		(0x05 << 16)
#घोषणा SUN4I_STA_ID17_13	(0x07 << 16)
#घोषणा SUN4I_STA_ID12_5	(0x0f << 16)
#घोषणा SUN4I_STA_ID4_0		(0x0e << 16)
#घोषणा SUN4I_STA_RTR		(0x0c << 16)
#घोषणा SUN4I_STA_RB1		(0x0d << 16)
#घोषणा SUN4I_STA_RB0		(0x09 << 16)
#घोषणा SUN4I_STA_DLEN		(0x0b << 16)
#घोषणा SUN4I_STA_DATA_FIELD	(0x0a << 16)
#घोषणा SUN4I_STA_CRC_SEQUENCE	(0x08 << 16)
#घोषणा SUN4I_STA_CRC_DELIMITER	(0x18 << 16)
#घोषणा SUN4I_STA_ACK		(0x19 << 16)
#घोषणा SUN4I_STA_ACK_DELIMITER	(0x1b << 16)
#घोषणा SUN4I_STA_END		(0x1a << 16)
#घोषणा SUN4I_STA_INTERMISSION	(0x12 << 16)
#घोषणा SUN4I_STA_ACTIVE_ERROR	(0x11 << 16)
#घोषणा SUN4I_STA_PASSIVE_ERROR	(0x16 << 16)
#घोषणा SUN4I_STA_TOLERATE_DOMIन_अंकT_BITS	(0x13 << 16)
#घोषणा SUN4I_STA_ERROR_DELIMITER	(0x17 << 16)
#घोषणा SUN4I_STA_OVERLOAD	(0x1c << 16)
#घोषणा SUN4I_STA_BUS_OFF	BIT(7)
#घोषणा SUN4I_STA_ERR_STA	BIT(6)
#घोषणा SUN4I_STA_TRANS_BUSY	BIT(5)
#घोषणा SUN4I_STA_RCV_BUSY	BIT(4)
#घोषणा SUN4I_STA_TRANS_OVER	BIT(3)
#घोषणा SUN4I_STA_TBUF_RDY	BIT(2)
#घोषणा SUN4I_STA_DATA_ORUN	BIT(1)
#घोषणा SUN4I_STA_RBUF_RDY	BIT(0)

/* पूर्णांकerrupt रेजिस्टर (r)
 * offset:0x000c शेष:0x0000_0000
 */
#घोषणा SUN4I_INT_BUS_ERR	BIT(7)
#घोषणा SUN4I_INT_ARB_LOST	BIT(6)
#घोषणा SUN4I_INT_ERR_PASSIVE	BIT(5)
#घोषणा SUN4I_INT_WAKEUP	BIT(4)
#घोषणा SUN4I_INT_DATA_OR	BIT(3)
#घोषणा SUN4I_INT_ERR_WRN	BIT(2)
#घोषणा SUN4I_INT_TBUF_VLD	BIT(1)
#घोषणा SUN4I_INT_RBUF_VLD	BIT(0)

/* पूर्णांकerrupt enable रेजिस्टर (r/w)
 * offset:0x0010 शेष:0x0000_0000
 */
#घोषणा SUN4I_INTEN_BERR	BIT(7)
#घोषणा SUN4I_INTEN_ARB_LOST	BIT(6)
#घोषणा SUN4I_INTEN_ERR_PASSIVE	BIT(5)
#घोषणा SUN4I_INTEN_WAKEUP	BIT(4)
#घोषणा SUN4I_INTEN_OR		BIT(3)
#घोषणा SUN4I_INTEN_ERR_WRN	BIT(2)
#घोषणा SUN4I_INTEN_TX		BIT(1)
#घोषणा SUN4I_INTEN_RX		BIT(0)

/* error code */
#घोषणा SUN4I_ERR_INRCV		(0x1 << 5)
#घोषणा SUN4I_ERR_INTRANS	(0x0 << 5)

/* filter mode */
#घोषणा SUN4I_FILTER_CLOSE	0
#घोषणा SUN4I_SINGLE_FLTER_MODE	1
#घोषणा SUN4I_DUAL_FILTER_MODE	2

/* message buffer flags */
#घोषणा SUN4I_MSG_EFF_FLAG	BIT(7)
#घोषणा SUN4I_MSG_RTR_FLAG	BIT(6)

/* max. number of पूर्णांकerrupts handled in ISR */
#घोषणा SUN4I_CAN_MAX_IRQ	20
#घोषणा SUN4I_MODE_MAX_RETRIES	100

काष्ठा sun4ican_priv अणु
	काष्ठा can_priv can;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	spinlock_t cmdreg_lock;	/* lock क्रम concurrent cmd रेजिस्टर ग_लिखोs */
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर sun4ican_bittiming_स्थिर = अणु
	.name = DRV_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

अटल व्योम sun4i_can_ग_लिखो_cmdreg(काष्ठा sun4ican_priv *priv, u8 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->cmdreg_lock, flags);
	ग_लिखोl(val, priv->base + SUN4I_REG_CMD_ADDR);
	spin_unlock_irqrestore(&priv->cmdreg_lock, flags);
पूर्ण

अटल पूर्णांक set_normal_mode(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	पूर्णांक retry = SUN4I_MODE_MAX_RETRIES;
	u32 mod_reg_val = 0;

	करो अणु
		mod_reg_val = पढ़ोl(priv->base + SUN4I_REG_MSEL_ADDR);
		mod_reg_val &= ~SUN4I_MSEL_RESET_MODE;
		ग_लिखोl(mod_reg_val, priv->base + SUN4I_REG_MSEL_ADDR);
	पूर्ण जबतक (retry-- && (mod_reg_val & SUN4I_MSEL_RESET_MODE));

	अगर (पढ़ोl(priv->base + SUN4I_REG_MSEL_ADDR) & SUN4I_MSEL_RESET_MODE) अणु
		netdev_err(dev,
			   "setting controller into normal mode failed!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_reset_mode(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	पूर्णांक retry = SUN4I_MODE_MAX_RETRIES;
	u32 mod_reg_val = 0;

	करो अणु
		mod_reg_val = पढ़ोl(priv->base + SUN4I_REG_MSEL_ADDR);
		mod_reg_val |= SUN4I_MSEL_RESET_MODE;
		ग_लिखोl(mod_reg_val, priv->base + SUN4I_REG_MSEL_ADDR);
	पूर्ण जबतक (retry-- && !(mod_reg_val & SUN4I_MSEL_RESET_MODE));

	अगर (!(पढ़ोl(priv->base + SUN4I_REG_MSEL_ADDR) &
	      SUN4I_MSEL_RESET_MODE)) अणु
		netdev_err(dev, "setting controller into reset mode failed!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/* bittiming is called in reset_mode only */
अटल पूर्णांक sun4ican_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u32 cfg;

	cfg = ((bt->brp - 1) & 0x3FF) |
	     (((bt->sjw - 1) & 0x3) << 14) |
	     (((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) << 16) |
	     (((bt->phase_seg2 - 1) & 0x7) << 20);
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		cfg |= 0x800000;

	netdev_dbg(dev, "setting BITTIMING=0x%08x\n", cfg);
	ग_लिखोl(cfg, priv->base + SUN4I_REG_BTIME_ADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4ican_get_berr_counter(स्थिर काष्ठा net_device *dev,
				     काष्ठा can_berr_counter *bec)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	u32 errors;
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		netdev_err(dev, "could not enable clock\n");
		वापस err;
	पूर्ण

	errors = पढ़ोl(priv->base + SUN4I_REG_ERRC_ADDR);

	bec->txerr = errors & 0xFF;
	bec->rxerr = (errors >> 16) & 0xFF;

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_can_start(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	पूर्णांक err;
	u32 mod_reg_val;

	/* we need to enter the reset mode */
	err = set_reset_mode(dev);
	अगर (err) अणु
		netdev_err(dev, "could not enter reset mode\n");
		वापस err;
	पूर्ण

	/* set filters - we accept all */
	ग_लिखोl(0x00000000, priv->base + SUN4I_REG_ACPC_ADDR);
	ग_लिखोl(0xFFFFFFFF, priv->base + SUN4I_REG_ACPM_ADDR);

	/* clear error counters and error code capture */
	ग_लिखोl(0, priv->base + SUN4I_REG_ERRC_ADDR);

	/* enable पूर्णांकerrupts */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
		ग_लिखोl(0xFF, priv->base + SUN4I_REG_INTEN_ADDR);
	अन्यथा
		ग_लिखोl(0xFF & ~SUN4I_INTEN_BERR,
		       priv->base + SUN4I_REG_INTEN_ADDR);

	/* enter the selected mode */
	mod_reg_val = पढ़ोl(priv->base + SUN4I_REG_MSEL_ADDR);
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		mod_reg_val |= SUN4I_MSEL_LOOPBACK_MODE;
	अन्यथा अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		mod_reg_val |= SUN4I_MSEL_LISTEN_ONLY_MODE;
	ग_लिखोl(mod_reg_val, priv->base + SUN4I_REG_MSEL_ADDR);

	err = sun4ican_set_bittiming(dev);
	अगर (err)
		वापस err;

	/* we are पढ़ोy to enter the normal mode */
	err = set_normal_mode(dev);
	अगर (err) अणु
		netdev_err(dev, "could not enter normal mode\n");
		वापस err;
	पूर्ण

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_can_stop(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	priv->can.state = CAN_STATE_STOPPED;
	/* we need to enter reset mode */
	err = set_reset_mode(dev);
	अगर (err) अणु
		netdev_err(dev, "could not enter reset mode\n");
		वापस err;
	पूर्ण

	/* disable all पूर्णांकerrupts */
	ग_लिखोl(0, priv->base + SUN4I_REG_INTEN_ADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4ican_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	पूर्णांक err;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		err = sun4i_can_start(dev);
		अगर (err) अणु
			netdev_err(dev, "starting CAN controller failed!\n");
			वापस err;
		पूर्ण
		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/* transmit a CAN message
 * message layout in the sk_buff should be like this:
 * xx xx xx xx         ff         ll 00 11 22 33 44 55 66 77
 * [ can_id ] [flags] [len] [can data (up to 8 bytes]
 */
अटल netdev_tx_t sun4ican_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	u8 dlc;
	u32 dreg, msg_flag_n;
	canid_t id;
	पूर्णांक i;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	netअगर_stop_queue(dev);

	id = cf->can_id;
	dlc = cf->len;
	msg_flag_n = dlc;

	अगर (id & CAN_RTR_FLAG)
		msg_flag_n |= SUN4I_MSG_RTR_FLAG;

	अगर (id & CAN_EFF_FLAG) अणु
		msg_flag_n |= SUN4I_MSG_EFF_FLAG;
		dreg = SUN4I_REG_BUF5_ADDR;
		ग_लिखोl((id >> 21) & 0xFF, priv->base + SUN4I_REG_BUF1_ADDR);
		ग_लिखोl((id >> 13) & 0xFF, priv->base + SUN4I_REG_BUF2_ADDR);
		ग_लिखोl((id >> 5)  & 0xFF, priv->base + SUN4I_REG_BUF3_ADDR);
		ग_लिखोl((id << 3)  & 0xF8, priv->base + SUN4I_REG_BUF4_ADDR);
	पूर्ण अन्यथा अणु
		dreg = SUN4I_REG_BUF3_ADDR;
		ग_लिखोl((id >> 3) & 0xFF, priv->base + SUN4I_REG_BUF1_ADDR);
		ग_लिखोl((id << 5) & 0xE0, priv->base + SUN4I_REG_BUF2_ADDR);
	पूर्ण

	क्रम (i = 0; i < dlc; i++)
		ग_लिखोl(cf->data[i], priv->base + (dreg + i * 4));

	ग_लिखोl(msg_flag_n, priv->base + SUN4I_REG_BUF0_ADDR);

	can_put_echo_skb(skb, dev, 0, 0);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		sun4i_can_ग_लिखो_cmdreg(priv, SUN4I_CMD_SELF_RCV_REQ);
	अन्यथा
		sun4i_can_ग_लिखो_cmdreg(priv, SUN4I_CMD_TRANS_REQ);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम sun4i_can_rx(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u8 fi;
	u32 dreg;
	canid_t id;
	पूर्णांक i;

	/* create zero'ed CAN frame buffer */
	skb = alloc_can_skb(dev, &cf);
	अगर (!skb)
		वापस;

	fi = पढ़ोl(priv->base + SUN4I_REG_BUF0_ADDR);
	cf->len = can_cc_dlc2len(fi & 0x0F);
	अगर (fi & SUN4I_MSG_EFF_FLAG) अणु
		dreg = SUN4I_REG_BUF5_ADDR;
		id = (पढ़ोl(priv->base + SUN4I_REG_BUF1_ADDR) << 21) |
		     (पढ़ोl(priv->base + SUN4I_REG_BUF2_ADDR) << 13) |
		     (पढ़ोl(priv->base + SUN4I_REG_BUF3_ADDR) << 5)  |
		    ((पढ़ोl(priv->base + SUN4I_REG_BUF4_ADDR) >> 3)  & 0x1f);
		id |= CAN_EFF_FLAG;
	पूर्ण अन्यथा अणु
		dreg = SUN4I_REG_BUF3_ADDR;
		id = (पढ़ोl(priv->base + SUN4I_REG_BUF1_ADDR) << 3) |
		    ((पढ़ोl(priv->base + SUN4I_REG_BUF2_ADDR) >> 5) & 0x7);
	पूर्ण

	/* remote frame ? */
	अगर (fi & SUN4I_MSG_RTR_FLAG)
		id |= CAN_RTR_FLAG;
	अन्यथा
		क्रम (i = 0; i < cf->len; i++)
			cf->data[i] = पढ़ोl(priv->base + dreg + i * 4);

	cf->can_id = id;

	sun4i_can_ग_लिखो_cmdreg(priv, SUN4I_CMD_RELEASE_RBUF);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);

	can_led_event(dev, CAN_LED_EVENT_RX);
पूर्ण

अटल पूर्णांक sun4i_can_err(काष्ठा net_device *dev, u8 isrc, u8 status)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	क्रमागत can_state state = priv->can.state;
	क्रमागत can_state rx_state, tx_state;
	अचिन्हित पूर्णांक rxerr, txerr, errc;
	u32 ecc, alc;

	/* we करोn't skip अगर alloc fails because we want the stats anyhow */
	skb = alloc_can_err_skb(dev, &cf);

	errc = पढ़ोl(priv->base + SUN4I_REG_ERRC_ADDR);
	rxerr = (errc >> 16) & 0xFF;
	txerr = errc & 0xFF;

	अगर (skb) अणु
		cf->data[6] = txerr;
		cf->data[7] = rxerr;
	पूर्ण

	अगर (isrc & SUN4I_INT_DATA_OR) अणु
		/* data overrun पूर्णांकerrupt */
		netdev_dbg(dev, "data overrun interrupt\n");
		अगर (likely(skb)) अणु
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		पूर्ण
		stats->rx_over_errors++;
		stats->rx_errors++;

		/* reset the CAN IP by entering reset mode
		 * ignoring समयout error
		 */
		set_reset_mode(dev);
		set_normal_mode(dev);

		/* clear bit */
		sun4i_can_ग_लिखो_cmdreg(priv, SUN4I_CMD_CLEAR_OR_FLAG);
	पूर्ण
	अगर (isrc & SUN4I_INT_ERR_WRN) अणु
		/* error warning पूर्णांकerrupt */
		netdev_dbg(dev, "error warning interrupt\n");

		अगर (status & SUN4I_STA_BUS_OFF)
			state = CAN_STATE_BUS_OFF;
		अन्यथा अगर (status & SUN4I_STA_ERR_STA)
			state = CAN_STATE_ERROR_WARNING;
		अन्यथा
			state = CAN_STATE_ERROR_ACTIVE;
	पूर्ण
	अगर (isrc & SUN4I_INT_BUS_ERR) अणु
		/* bus error पूर्णांकerrupt */
		netdev_dbg(dev, "bus error interrupt\n");
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;

		अगर (likely(skb)) अणु
			ecc = पढ़ोl(priv->base + SUN4I_REG_STA_ADDR);

			cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

			चयन (ecc & SUN4I_STA_MASK_ERR) अणु
			हाल SUN4I_STA_BIT_ERR:
				cf->data[2] |= CAN_ERR_PROT_BIT;
				अवरोध;
			हाल SUN4I_STA_FORM_ERR:
				cf->data[2] |= CAN_ERR_PROT_FORM;
				अवरोध;
			हाल SUN4I_STA_STUFF_ERR:
				cf->data[2] |= CAN_ERR_PROT_STUFF;
				अवरोध;
			शेष:
				cf->data[3] = (ecc & SUN4I_STA_ERR_SEG_CODE)
					       >> 16;
				अवरोध;
			पूर्ण
			/* error occurred during transmission? */
			अगर ((ecc & SUN4I_STA_ERR_सूची) == 0)
				cf->data[2] |= CAN_ERR_PROT_TX;
		पूर्ण
	पूर्ण
	अगर (isrc & SUN4I_INT_ERR_PASSIVE) अणु
		/* error passive पूर्णांकerrupt */
		netdev_dbg(dev, "error passive interrupt\n");
		अगर (state == CAN_STATE_ERROR_PASSIVE)
			state = CAN_STATE_ERROR_WARNING;
		अन्यथा
			state = CAN_STATE_ERROR_PASSIVE;
	पूर्ण
	अगर (isrc & SUN4I_INT_ARB_LOST) अणु
		/* arbitration lost पूर्णांकerrupt */
		netdev_dbg(dev, "arbitration lost interrupt\n");
		alc = पढ़ोl(priv->base + SUN4I_REG_STA_ADDR);
		priv->can.can_stats.arbitration_lost++;
		अगर (likely(skb)) अणु
			cf->can_id |= CAN_ERR_LOSTARB;
			cf->data[0] = (alc >> 8) & 0x1f;
		पूर्ण
	पूर्ण

	अगर (state != priv->can.state) अणु
		tx_state = txerr >= rxerr ? state : 0;
		rx_state = txerr <= rxerr ? state : 0;

		अगर (likely(skb))
			can_change_state(dev, cf, tx_state, rx_state);
		अन्यथा
			priv->can.state = state;
		अगर (state == CAN_STATE_BUS_OFF)
			can_bus_off(dev);
	पूर्ण

	अगर (likely(skb)) अणु
		stats->rx_packets++;
		stats->rx_bytes += cf->len;
		netअगर_rx(skb);
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t sun4i_can_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	u8 isrc, status;
	पूर्णांक n = 0;

	जबतक ((isrc = पढ़ोl(priv->base + SUN4I_REG_INT_ADDR)) &&
	       (n < SUN4I_CAN_MAX_IRQ)) अणु
		n++;
		status = पढ़ोl(priv->base + SUN4I_REG_STA_ADDR);

		अगर (isrc & SUN4I_INT_WAKEUP)
			netdev_warn(dev, "wakeup interrupt\n");

		अगर (isrc & SUN4I_INT_TBUF_VLD) अणु
			/* transmission complete पूर्णांकerrupt */
			stats->tx_bytes +=
			    पढ़ोl(priv->base +
				  SUN4I_REG_RBUF_RBACK_START_ADDR) & 0xf;
			stats->tx_packets++;
			can_get_echo_skb(dev, 0, शून्य);
			netअगर_wake_queue(dev);
			can_led_event(dev, CAN_LED_EVENT_TX);
		पूर्ण
		अगर ((isrc & SUN4I_INT_RBUF_VLD) &&
		    !(isrc & SUN4I_INT_DATA_OR)) अणु
			/* receive पूर्णांकerrupt - करोn't पढ़ो अगर overrun occurred */
			जबतक (status & SUN4I_STA_RBUF_RDY) अणु
				/* RX buffer is not empty */
				sun4i_can_rx(dev);
				status = पढ़ोl(priv->base + SUN4I_REG_STA_ADDR);
			पूर्ण
		पूर्ण
		अगर (isrc &
		    (SUN4I_INT_DATA_OR | SUN4I_INT_ERR_WRN | SUN4I_INT_BUS_ERR |
		     SUN4I_INT_ERR_PASSIVE | SUN4I_INT_ARB_LOST)) अणु
			/* error पूर्णांकerrupt */
			अगर (sun4i_can_err(dev, isrc, status))
				netdev_err(dev, "can't allocate buffer - clearing pending interrupts\n");
		पूर्ण
		/* clear पूर्णांकerrupts */
		ग_लिखोl(isrc, priv->base + SUN4I_REG_INT_ADDR);
		पढ़ोl(priv->base + SUN4I_REG_INT_ADDR);
	पूर्ण
	अगर (n >= SUN4I_CAN_MAX_IRQ)
		netdev_dbg(dev, "%d messages handled in ISR", n);

	वापस (n) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक sun4ican_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	/* common खोलो */
	err = खोलो_candev(dev);
	अगर (err)
		वापस err;

	/* रेजिस्टर पूर्णांकerrupt handler */
	err = request_irq(dev->irq, sun4i_can_पूर्णांकerrupt, 0, dev->name, dev);
	अगर (err) अणु
		netdev_err(dev, "request_irq err: %d\n", err);
		जाओ निकास_irq;
	पूर्ण

	/* turn on घड़ीing क्रम CAN peripheral block */
	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		netdev_err(dev, "could not enable CAN peripheral clock\n");
		जाओ निकास_घड़ी;
	पूर्ण

	err = sun4i_can_start(dev);
	अगर (err) अणु
		netdev_err(dev, "could not start CAN peripheral\n");
		जाओ निकास_can_start;
	पूर्ण

	can_led_event(dev, CAN_LED_EVENT_OPEN);
	netअगर_start_queue(dev);

	वापस 0;

निकास_can_start:
	clk_disable_unprepare(priv->clk);
निकास_घड़ी:
	मुक्त_irq(dev->irq, dev);
निकास_irq:
	बंद_candev(dev);
	वापस err;
पूर्ण

अटल पूर्णांक sun4ican_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sun4ican_priv *priv = netdev_priv(dev);

	netअगर_stop_queue(dev);
	sun4i_can_stop(dev);
	clk_disable_unprepare(priv->clk);

	मुक्त_irq(dev->irq, dev);
	बंद_candev(dev);
	can_led_event(dev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sun4ican_netdev_ops = अणु
	.nकरो_खोलो = sun4ican_खोलो,
	.nकरो_stop = sun4ican_बंद,
	.nकरो_start_xmit = sun4ican_start_xmit,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4ican_of_match[] = अणु
	अणु.compatible = "allwinner,sun4i-a10-can"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, sun4ican_of_match);

अटल पूर्णांक sun4ican_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(dev);
	मुक्त_candev(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4ican_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा clk *clk;
	व्योम __iomem *addr;
	पूर्णांक err, irq;
	काष्ठा net_device *dev;
	काष्ठा sun4ican_priv *priv;

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to request clock\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(addr)) अणु
		err = PTR_ERR(addr);
		जाओ निकास;
	पूर्ण

	dev = alloc_candev(माप(काष्ठा sun4ican_priv), 1);
	अगर (!dev) अणु
		dev_err(&pdev->dev,
			"could not allocate memory for CAN device\n");
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	dev->netdev_ops = &sun4ican_netdev_ops;
	dev->irq = irq;
	dev->flags |= IFF_ECHO;

	priv = netdev_priv(dev);
	priv->can.घड़ी.freq = clk_get_rate(clk);
	priv->can.bittiming_स्थिर = &sun4ican_bittiming_स्थिर;
	priv->can.करो_set_mode = sun4ican_set_mode;
	priv->can.करो_get_berr_counter = sun4ican_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_BERR_REPORTING |
				       CAN_CTRLMODE_LISTENONLY |
				       CAN_CTRLMODE_LOOPBACK |
				       CAN_CTRLMODE_3_SAMPLES;
	priv->base = addr;
	priv->clk = clk;
	spin_lock_init(&priv->cmdreg_lock);

	platक्रमm_set_drvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = रेजिस्टर_candev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "registering %s failed (err=%d)\n",
			DRV_NAME, err);
		जाओ निकास_मुक्त;
	पूर्ण
	devm_can_led_init(dev);

	dev_info(&pdev->dev, "device registered (base=%p, irq=%d)\n",
		 priv->base, dev->irq);

	वापस 0;

निकास_मुक्त:
	मुक्त_candev(dev);
निकास:
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver sun4i_can_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = sun4ican_of_match,
	पूर्ण,
	.probe = sun4ican_probe,
	.हटाओ = sun4ican_हटाओ,
पूर्ण;

module_platक्रमm_driver(sun4i_can_driver);

MODULE_AUTHOR("Peter Chen <xingkongcp@gmail.com>");
MODULE_AUTHOR("Gerhard Bertelsmann <info@gerhard-bertelsmann.de>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("CAN driver for Allwinner SoCs (A10/A20)");
