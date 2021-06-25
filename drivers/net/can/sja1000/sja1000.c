<शैली गुरु>
/*
 * sja1000.c -  Philips SJA1000 network device driver
 *
 * Copyright (c) 2003 Matthias Brukner, Trajet Gmbh, Rebenring 33,
 * 38106 Braunschweig, GERMANY
 *
 * Copyright (c) 2002-2007 Volkswagen Group Electronic Research
 * All rights reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>

#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>

#समावेश "sja1000.h"

#घोषणा DRV_NAME "sja1000"

MODULE_AUTHOR("Oliver Hartkopp <oliver.hartkopp@volkswagen.de>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION(DRV_NAME "CAN netdevice driver");

अटल स्थिर काष्ठा can_bittiming_स्थिर sja1000_bittiming_स्थिर = अणु
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

अटल व्योम sja1000_ग_लिखो_cmdreg(काष्ठा sja1000_priv *priv, u8 val)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * The command रेजिस्टर needs some locking and समय to settle
	 * the ग_लिखो_reg() operation - especially on SMP प्रणालीs.
	 */
	spin_lock_irqsave(&priv->cmdreg_lock, flags);
	priv->ग_लिखो_reg(priv, SJA1000_CMR, val);
	priv->पढ़ो_reg(priv, SJA1000_SR);
	spin_unlock_irqrestore(&priv->cmdreg_lock, flags);
पूर्ण

अटल पूर्णांक sja1000_is_असलent(काष्ठा sja1000_priv *priv)
अणु
	वापस (priv->पढ़ो_reg(priv, SJA1000_MOD) == 0xFF);
पूर्ण

अटल पूर्णांक sja1000_probe_chip(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);

	अगर (priv->reg_base && sja1000_is_असलent(priv)) अणु
		netdev_err(dev, "probing failed\n");
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम set_reset_mode(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	अचिन्हित अक्षर status = priv->पढ़ो_reg(priv, SJA1000_MOD);
	पूर्णांक i;

	/* disable पूर्णांकerrupts */
	priv->ग_लिखो_reg(priv, SJA1000_IER, IRQ_OFF);

	क्रम (i = 0; i < 100; i++) अणु
		/* check reset bit */
		अगर (status & MOD_RM) अणु
			priv->can.state = CAN_STATE_STOPPED;
			वापस;
		पूर्ण

		/* reset chip */
		priv->ग_लिखो_reg(priv, SJA1000_MOD, MOD_RM);
		udelay(10);
		status = priv->पढ़ो_reg(priv, SJA1000_MOD);
	पूर्ण

	netdev_err(dev, "setting SJA1000 into reset mode failed!\n");
पूर्ण

अटल व्योम set_normal_mode(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	अचिन्हित अक्षर status = priv->पढ़ो_reg(priv, SJA1000_MOD);
	u8 mod_reg_val = 0x00;
	पूर्णांक i;

	क्रम (i = 0; i < 100; i++) अणु
		/* check reset bit */
		अगर ((status & MOD_RM) == 0) अणु
			priv->can.state = CAN_STATE_ERROR_ACTIVE;
			/* enable पूर्णांकerrupts */
			अगर (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
				priv->ग_लिखो_reg(priv, SJA1000_IER, IRQ_ALL);
			अन्यथा
				priv->ग_लिखो_reg(priv, SJA1000_IER,
						IRQ_ALL & ~IRQ_BEI);
			वापस;
		पूर्ण

		/* set chip to normal mode */
		अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
			mod_reg_val |= MOD_LOM;
		अगर (priv->can.ctrlmode & CAN_CTRLMODE_PRESUME_ACK)
			mod_reg_val |= MOD_STM;
		priv->ग_लिखो_reg(priv, SJA1000_MOD, mod_reg_val);

		udelay(10);

		status = priv->पढ़ो_reg(priv, SJA1000_MOD);
	पूर्ण

	netdev_err(dev, "setting SJA1000 into normal mode failed!\n");
पूर्ण

/*
 * initialize SJA1000 chip:
 *   - reset chip
 *   - set output mode
 *   - set baudrate
 *   - enable पूर्णांकerrupts
 *   - start operating mode
 */
अटल व्योम chipset_init(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);

	/* set घड़ी भागider and output control रेजिस्टर */
	priv->ग_लिखो_reg(priv, SJA1000_CDR, priv->cdr | CDR_PELICAN);

	/* set acceptance filter (accept all) */
	priv->ग_लिखो_reg(priv, SJA1000_ACCC0, 0x00);
	priv->ग_लिखो_reg(priv, SJA1000_ACCC1, 0x00);
	priv->ग_लिखो_reg(priv, SJA1000_ACCC2, 0x00);
	priv->ग_लिखो_reg(priv, SJA1000_ACCC3, 0x00);

	priv->ग_लिखो_reg(priv, SJA1000_ACCM0, 0xFF);
	priv->ग_लिखो_reg(priv, SJA1000_ACCM1, 0xFF);
	priv->ग_लिखो_reg(priv, SJA1000_ACCM2, 0xFF);
	priv->ग_लिखो_reg(priv, SJA1000_ACCM3, 0xFF);

	priv->ग_लिखो_reg(priv, SJA1000_OCR, priv->ocr | OCR_MODE_NORMAL);
पूर्ण

अटल व्योम sja1000_start(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);

	/* leave reset mode */
	अगर (priv->can.state != CAN_STATE_STOPPED)
		set_reset_mode(dev);

	/* Initialize chip अगर uninitialized at this stage */
	अगर (!(priv->पढ़ो_reg(priv, SJA1000_CDR) & CDR_PELICAN))
		chipset_init(dev);

	/* Clear error counters and error code capture */
	priv->ग_लिखो_reg(priv, SJA1000_TXERR, 0x0);
	priv->ग_लिखो_reg(priv, SJA1000_RXERR, 0x0);
	priv->पढ़ो_reg(priv, SJA1000_ECC);

	/* clear पूर्णांकerrupt flags */
	priv->पढ़ो_reg(priv, SJA1000_IR);

	/* leave reset mode */
	set_normal_mode(dev);
पूर्ण

अटल पूर्णांक sja1000_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	चयन (mode) अणु
	हाल CAN_MODE_START:
		sja1000_start(dev);
		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sja1000_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u8 btr0, btr1;

	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	netdev_info(dev, "setting BTR0=0x%02x BTR1=0x%02x\n", btr0, btr1);

	priv->ग_लिखो_reg(priv, SJA1000_BTR0, btr0);
	priv->ग_लिखो_reg(priv, SJA1000_BTR1, btr1);

	वापस 0;
पूर्ण

अटल पूर्णांक sja1000_get_berr_counter(स्थिर काष्ठा net_device *dev,
				    काष्ठा can_berr_counter *bec)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);

	bec->txerr = priv->पढ़ो_reg(priv, SJA1000_TXERR);
	bec->rxerr = priv->पढ़ो_reg(priv, SJA1000_RXERR);

	वापस 0;
पूर्ण

/*
 * transmit a CAN message
 * message layout in the sk_buff should be like this:
 * xx xx xx xx	 ff	 ll   00 11 22 33 44 55 66 77
 * [  can-id ] [flags] [len] [can data (up to 8 bytes]
 */
अटल netdev_tx_t sja1000_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	uपूर्णांक8_t fi;
	canid_t id;
	uपूर्णांक8_t dreg;
	u8 cmd_reg_val = 0x00;
	पूर्णांक i;

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	netअगर_stop_queue(dev);

	fi = can_get_cc_dlc(cf, priv->can.ctrlmode);
	id = cf->can_id;

	अगर (id & CAN_RTR_FLAG)
		fi |= SJA1000_FI_RTR;

	अगर (id & CAN_EFF_FLAG) अणु
		fi |= SJA1000_FI_FF;
		dreg = SJA1000_EFF_BUF;
		priv->ग_लिखो_reg(priv, SJA1000_FI, fi);
		priv->ग_लिखो_reg(priv, SJA1000_ID1, (id & 0x1fe00000) >> 21);
		priv->ग_लिखो_reg(priv, SJA1000_ID2, (id & 0x001fe000) >> 13);
		priv->ग_लिखो_reg(priv, SJA1000_ID3, (id & 0x00001fe0) >> 5);
		priv->ग_लिखो_reg(priv, SJA1000_ID4, (id & 0x0000001f) << 3);
	पूर्ण अन्यथा अणु
		dreg = SJA1000_SFF_BUF;
		priv->ग_लिखो_reg(priv, SJA1000_FI, fi);
		priv->ग_लिखो_reg(priv, SJA1000_ID1, (id & 0x000007f8) >> 3);
		priv->ग_लिखो_reg(priv, SJA1000_ID2, (id & 0x00000007) << 5);
	पूर्ण

	क्रम (i = 0; i < cf->len; i++)
		priv->ग_लिखो_reg(priv, dreg++, cf->data[i]);

	can_put_echo_skb(skb, dev, 0, 0);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		cmd_reg_val |= CMD_AT;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		cmd_reg_val |= CMD_SRR;
	अन्यथा
		cmd_reg_val |= CMD_TR;

	sja1000_ग_लिखो_cmdreg(priv, cmd_reg_val);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम sja1000_rx(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	uपूर्णांक8_t fi;
	uपूर्णांक8_t dreg;
	canid_t id;
	पूर्णांक i;

	/* create zero'ed CAN frame buffer */
	skb = alloc_can_skb(dev, &cf);
	अगर (skb == शून्य)
		वापस;

	fi = priv->पढ़ो_reg(priv, SJA1000_FI);

	अगर (fi & SJA1000_FI_FF) अणु
		/* extended frame क्रमmat (EFF) */
		dreg = SJA1000_EFF_BUF;
		id = (priv->पढ़ो_reg(priv, SJA1000_ID1) << 21)
		    | (priv->पढ़ो_reg(priv, SJA1000_ID2) << 13)
		    | (priv->पढ़ो_reg(priv, SJA1000_ID3) << 5)
		    | (priv->पढ़ो_reg(priv, SJA1000_ID4) >> 3);
		id |= CAN_EFF_FLAG;
	पूर्ण अन्यथा अणु
		/* standard frame क्रमmat (SFF) */
		dreg = SJA1000_SFF_BUF;
		id = (priv->पढ़ो_reg(priv, SJA1000_ID1) << 3)
		    | (priv->पढ़ो_reg(priv, SJA1000_ID2) >> 5);
	पूर्ण

	can_frame_set_cc_len(cf, fi & 0x0F, priv->can.ctrlmode);
	अगर (fi & SJA1000_FI_RTR) अणु
		id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < cf->len; i++)
			cf->data[i] = priv->पढ़ो_reg(priv, dreg++);
	पूर्ण

	cf->can_id = id;

	/* release receive buffer */
	sja1000_ग_लिखो_cmdreg(priv, CMD_RRB);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);

	can_led_event(dev, CAN_LED_EVENT_RX);
पूर्ण

अटल पूर्णांक sja1000_err(काष्ठा net_device *dev, uपूर्णांक8_t isrc, uपूर्णांक8_t status)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	क्रमागत can_state state = priv->can.state;
	क्रमागत can_state rx_state, tx_state;
	अचिन्हित पूर्णांक rxerr, txerr;
	uपूर्णांक8_t ecc, alc;

	skb = alloc_can_err_skb(dev, &cf);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	txerr = priv->पढ़ो_reg(priv, SJA1000_TXERR);
	rxerr = priv->पढ़ो_reg(priv, SJA1000_RXERR);

	cf->data[6] = txerr;
	cf->data[7] = rxerr;

	अगर (isrc & IRQ_DOI) अणु
		/* data overrun पूर्णांकerrupt */
		netdev_dbg(dev, "data overrun interrupt\n");
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		stats->rx_over_errors++;
		stats->rx_errors++;
		sja1000_ग_लिखो_cmdreg(priv, CMD_CDO);	/* clear bit */
	पूर्ण

	अगर (isrc & IRQ_EI) अणु
		/* error warning पूर्णांकerrupt */
		netdev_dbg(dev, "error warning interrupt\n");

		अगर (status & SR_BS)
			state = CAN_STATE_BUS_OFF;
		अन्यथा अगर (status & SR_ES)
			state = CAN_STATE_ERROR_WARNING;
		अन्यथा
			state = CAN_STATE_ERROR_ACTIVE;
	पूर्ण
	अगर (isrc & IRQ_BEI) अणु
		/* bus error पूर्णांकerrupt */
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;

		ecc = priv->पढ़ो_reg(priv, SJA1000_ECC);

		cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

		/* set error type */
		चयन (ecc & ECC_MASK) अणु
		हाल ECC_BIT:
			cf->data[2] |= CAN_ERR_PROT_BIT;
			अवरोध;
		हाल ECC_FORM:
			cf->data[2] |= CAN_ERR_PROT_FORM;
			अवरोध;
		हाल ECC_STUFF:
			cf->data[2] |= CAN_ERR_PROT_STUFF;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* set error location */
		cf->data[3] = ecc & ECC_SEG;

		/* Error occurred during transmission? */
		अगर ((ecc & ECC_सूची) == 0)
			cf->data[2] |= CAN_ERR_PROT_TX;
	पूर्ण
	अगर (isrc & IRQ_EPI) अणु
		/* error passive पूर्णांकerrupt */
		netdev_dbg(dev, "error passive interrupt\n");

		अगर (state == CAN_STATE_ERROR_PASSIVE)
			state = CAN_STATE_ERROR_WARNING;
		अन्यथा
			state = CAN_STATE_ERROR_PASSIVE;
	पूर्ण
	अगर (isrc & IRQ_ALI) अणु
		/* arbitration lost पूर्णांकerrupt */
		netdev_dbg(dev, "arbitration lost interrupt\n");
		alc = priv->पढ़ो_reg(priv, SJA1000_ALC);
		priv->can.can_stats.arbitration_lost++;
		cf->can_id |= CAN_ERR_LOSTARB;
		cf->data[0] = alc & 0x1f;
	पूर्ण

	अगर (state != priv->can.state) अणु
		tx_state = txerr >= rxerr ? state : 0;
		rx_state = txerr <= rxerr ? state : 0;

		can_change_state(dev, cf, tx_state, rx_state);

		अगर(state == CAN_STATE_BUS_OFF)
			can_bus_off(dev);
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	netअगर_rx(skb);

	वापस 0;
पूर्ण

irqवापस_t sja1000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	uपूर्णांक8_t isrc, status;
	पूर्णांक n = 0;

	अगर (priv->pre_irq)
		priv->pre_irq(priv);

	/* Shared पूर्णांकerrupts and IRQ off? */
	अगर (priv->पढ़ो_reg(priv, SJA1000_IER) == IRQ_OFF)
		जाओ out;

	जबतक ((isrc = priv->पढ़ो_reg(priv, SJA1000_IR)) &&
	       (n < SJA1000_MAX_IRQ)) अणु

		status = priv->पढ़ो_reg(priv, SJA1000_SR);
		/* check क्रम असलent controller due to hw unplug */
		अगर (status == 0xFF && sja1000_is_असलent(priv))
			जाओ out;

		अगर (isrc & IRQ_WUI)
			netdev_warn(dev, "wakeup interrupt\n");

		अगर (isrc & IRQ_TI) अणु
			/* transmission buffer released */
			अगर (priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT &&
			    !(status & SR_TCS)) अणु
				stats->tx_errors++;
				can_मुक्त_echo_skb(dev, 0, शून्य);
			पूर्ण अन्यथा अणु
				/* transmission complete */
				stats->tx_bytes +=
					priv->पढ़ो_reg(priv, SJA1000_FI) & 0xf;
				stats->tx_packets++;
				can_get_echo_skb(dev, 0, शून्य);
			पूर्ण
			netअगर_wake_queue(dev);
			can_led_event(dev, CAN_LED_EVENT_TX);
		पूर्ण
		अगर (isrc & IRQ_RI) अणु
			/* receive पूर्णांकerrupt */
			जबतक (status & SR_RBS) अणु
				sja1000_rx(dev);
				status = priv->पढ़ो_reg(priv, SJA1000_SR);
				/* check क्रम असलent controller */
				अगर (status == 0xFF && sja1000_is_असलent(priv))
					जाओ out;
			पूर्ण
		पूर्ण
		अगर (isrc & (IRQ_DOI | IRQ_EI | IRQ_BEI | IRQ_EPI | IRQ_ALI)) अणु
			/* error पूर्णांकerrupt */
			अगर (sja1000_err(dev, isrc, status))
				अवरोध;
		पूर्ण
		n++;
	पूर्ण
out:
	अगर (priv->post_irq)
		priv->post_irq(priv);

	अगर (n >= SJA1000_MAX_IRQ)
		netdev_dbg(dev, "%d messages handled in ISR", n);

	वापस (n) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(sja1000_पूर्णांकerrupt);

अटल पूर्णांक sja1000_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	/* set chip पूर्णांकo reset mode */
	set_reset_mode(dev);

	/* common खोलो */
	err = खोलो_candev(dev);
	अगर (err)
		वापस err;

	/* रेजिस्टर पूर्णांकerrupt handler, अगर not करोne by the device driver */
	अगर (!(priv->flags & SJA1000_CUSTOM_IRQ_HANDLER)) अणु
		err = request_irq(dev->irq, sja1000_पूर्णांकerrupt, priv->irq_flags,
				  dev->name, (व्योम *)dev);
		अगर (err) अणु
			बंद_candev(dev);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	/* init and start chi */
	sja1000_start(dev);

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sja1000_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);

	netअगर_stop_queue(dev);
	set_reset_mode(dev);

	अगर (!(priv->flags & SJA1000_CUSTOM_IRQ_HANDLER))
		मुक्त_irq(dev->irq, (व्योम *)dev);

	बंद_candev(dev);

	can_led_event(dev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

काष्ठा net_device *alloc_sja1000dev(पूर्णांक माप_priv)
अणु
	काष्ठा net_device *dev;
	काष्ठा sja1000_priv *priv;

	dev = alloc_candev(माप(काष्ठा sja1000_priv) + माप_priv,
		SJA1000_ECHO_SKB_MAX);
	अगर (!dev)
		वापस शून्य;

	priv = netdev_priv(dev);

	priv->dev = dev;
	priv->can.bittiming_स्थिर = &sja1000_bittiming_स्थिर;
	priv->can.करो_set_bittiming = sja1000_set_bittiming;
	priv->can.करो_set_mode = sja1000_set_mode;
	priv->can.करो_get_berr_counter = sja1000_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
				       CAN_CTRLMODE_LISTENONLY |
				       CAN_CTRLMODE_3_SAMPLES |
				       CAN_CTRLMODE_ONE_SHOT |
				       CAN_CTRLMODE_BERR_REPORTING |
				       CAN_CTRLMODE_PRESUME_ACK |
				       CAN_CTRLMODE_CC_LEN8_DLC;

	spin_lock_init(&priv->cmdreg_lock);

	अगर (माप_priv)
		priv->priv = (व्योम *)priv + माप(काष्ठा sja1000_priv);

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_sja1000dev);

व्योम मुक्त_sja1000dev(काष्ठा net_device *dev)
अणु
	मुक्त_candev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_sja1000dev);

अटल स्थिर काष्ठा net_device_ops sja1000_netdev_ops = अणु
	.nकरो_खोलो	= sja1000_खोलो,
	.nकरो_stop	= sja1000_बंद,
	.nकरो_start_xmit	= sja1000_start_xmit,
	.nकरो_change_mtu	= can_change_mtu,
पूर्ण;

पूर्णांक रेजिस्टर_sja1000dev(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;

	अगर (!sja1000_probe_chip(dev))
		वापस -ENODEV;

	dev->flags |= IFF_ECHO;	/* we support local echo */
	dev->netdev_ops = &sja1000_netdev_ops;

	set_reset_mode(dev);
	chipset_init(dev);

	ret =  रेजिस्टर_candev(dev);

	अगर (!ret)
		devm_can_led_init(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_sja1000dev);

व्योम unरेजिस्टर_sja1000dev(काष्ठा net_device *dev)
अणु
	set_reset_mode(dev);
	unरेजिस्टर_candev(dev);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_sja1000dev);

अटल __init पूर्णांक sja1000_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s CAN netdevice driver\n", DRV_NAME);

	वापस 0;
पूर्ण

module_init(sja1000_init);

अटल __निकास व्योम sja1000_निकास(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s: driver removed\n", DRV_NAME);
पूर्ण

module_निकास(sja1000_निकास);
