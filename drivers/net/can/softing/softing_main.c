<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2010
 *
 * - Kurt Van Dijck, EIA Electronics
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>

#समावेश "softing.h"

#घोषणा TX_ECHO_SKB_MAX (((TXMAX+1)/2)-1)

/*
 * test is a specअगरic CAN netdev
 * is online (ie. up 'n running, not sleeping, not busoff
 */
अटल अंतरभूत पूर्णांक canअगर_is_active(काष्ठा net_device *netdev)
अणु
	काष्ठा can_priv *can = netdev_priv(netdev);

	अगर (!netअगर_running(netdev))
		वापस 0;
	वापस (can->state <= CAN_STATE_ERROR_PASSIVE);
पूर्ण

/* reset DPRAM */
अटल अंतरभूत व्योम softing_set_reset_dpram(काष्ठा softing *card)
अणु
	अगर (card->pdat->generation >= 2) अणु
		spin_lock_bh(&card->spin);
		ioग_लिखो8(ioपढ़ो8(&card->dpram[DPRAM_V2_RESET]) & ~1,
				&card->dpram[DPRAM_V2_RESET]);
		spin_unlock_bh(&card->spin);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम softing_clr_reset_dpram(काष्ठा softing *card)
अणु
	अगर (card->pdat->generation >= 2) अणु
		spin_lock_bh(&card->spin);
		ioग_लिखो8(ioपढ़ो8(&card->dpram[DPRAM_V2_RESET]) | 1,
				&card->dpram[DPRAM_V2_RESET]);
		spin_unlock_bh(&card->spin);
	पूर्ण
पूर्ण

/* trigger the tx queue-ing */
अटल netdev_tx_t softing_netdev_start_xmit(काष्ठा sk_buff *skb,
		काष्ठा net_device *dev)
अणु
	काष्ठा softing_priv *priv = netdev_priv(dev);
	काष्ठा softing *card = priv->card;
	पूर्णांक ret;
	uपूर्णांक8_t *ptr;
	uपूर्णांक8_t fअगरo_wr, fअगरo_rd;
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	uपूर्णांक8_t buf[DPRAM_TX_SIZE];

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	spin_lock(&card->spin);

	ret = NETDEV_TX_BUSY;
	अगर (!card->fw.up ||
			(card->tx.pending >= TXMAX) ||
			(priv->tx.pending >= TX_ECHO_SKB_MAX))
		जाओ xmit_करोne;
	fअगरo_wr = ioपढ़ो8(&card->dpram[DPRAM_TX_WR]);
	fअगरo_rd = ioपढ़ो8(&card->dpram[DPRAM_TX_RD]);
	अगर (fअगरo_wr == fअगरo_rd)
		/* fअगरo full */
		जाओ xmit_करोne;
	स_रखो(buf, 0, माप(buf));
	ptr = buf;
	*ptr = CMD_TX;
	अगर (cf->can_id & CAN_RTR_FLAG)
		*ptr |= CMD_RTR;
	अगर (cf->can_id & CAN_EFF_FLAG)
		*ptr |= CMD_XTD;
	अगर (priv->index)
		*ptr |= CMD_BUS2;
	++ptr;
	*ptr++ = cf->len;
	*ptr++ = (cf->can_id >> 0);
	*ptr++ = (cf->can_id >> 8);
	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		*ptr++ = (cf->can_id >> 16);
		*ptr++ = (cf->can_id >> 24);
	पूर्ण अन्यथा अणु
		/* increment 1, not 2 as you might think */
		ptr += 1;
	पूर्ण
	अगर (!(cf->can_id & CAN_RTR_FLAG))
		स_नकल(ptr, &cf->data[0], cf->len);
	स_नकल_toio(&card->dpram[DPRAM_TX + DPRAM_TX_SIZE * fअगरo_wr],
			buf, DPRAM_TX_SIZE);
	अगर (++fअगरo_wr >= DPRAM_TX_CNT)
		fअगरo_wr = 0;
	ioग_लिखो8(fअगरo_wr, &card->dpram[DPRAM_TX_WR]);
	card->tx.last_bus = priv->index;
	++card->tx.pending;
	++priv->tx.pending;
	can_put_echo_skb(skb, dev, priv->tx.echo_put, 0);
	++priv->tx.echo_put;
	अगर (priv->tx.echo_put >= TX_ECHO_SKB_MAX)
		priv->tx.echo_put = 0;
	/* can_put_echo_skb() saves the skb, safe to वापस TX_OK */
	ret = NETDEV_TX_OK;
xmit_करोne:
	spin_unlock(&card->spin);
	अगर (card->tx.pending >= TXMAX) अणु
		पूर्णांक j;
		क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
			अगर (card->net[j])
				netअगर_stop_queue(card->net[j]);
		पूर्ण
	पूर्ण
	अगर (ret != NETDEV_TX_OK)
		netअगर_stop_queue(dev);

	वापस ret;
पूर्ण

/*
 * लघुcut क्रम skb delivery
 */
पूर्णांक softing_netdev_rx(काष्ठा net_device *netdev, स्थिर काष्ठा can_frame *msg,
		kसमय_प्रकार kसमय)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;

	skb = alloc_can_skb(netdev, &cf);
	अगर (!skb)
		वापस -ENOMEM;
	स_नकल(cf, msg, माप(*msg));
	skb->tstamp = kसमय;
	वापस netअगर_rx(skb);
पूर्ण

/*
 * softing_handle_1
 * pop 1 entry from the DPRAM queue, and process
 */
अटल पूर्णांक softing_handle_1(काष्ठा softing *card)
अणु
	काष्ठा net_device *netdev;
	काष्ठा softing_priv *priv;
	kसमय_प्रकार kसमय;
	काष्ठा can_frame msg;
	पूर्णांक cnt = 0, lost_msg;
	uपूर्णांक8_t fअगरo_rd, fअगरo_wr, cmd;
	uपूर्णांक8_t *ptr;
	uपूर्णांक32_t पंचांगp_u32;
	uपूर्णांक8_t buf[DPRAM_RX_SIZE];

	स_रखो(&msg, 0, माप(msg));
	/* test क्रम lost msgs */
	lost_msg = ioपढ़ो8(&card->dpram[DPRAM_RX_LOST]);
	अगर (lost_msg) अणु
		पूर्णांक j;
		/* reset condition */
		ioग_लिखो8(0, &card->dpram[DPRAM_RX_LOST]);
		/* prepare msg */
		msg.can_id = CAN_ERR_FLAG | CAN_ERR_CRTL;
		msg.len = CAN_ERR_DLC;
		msg.data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
		/*
		 * service to all buses, we करोn't know which it was applicable
		 * but only service buses that are online
		 */
		क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
			netdev = card->net[j];
			अगर (!netdev)
				जारी;
			अगर (!canअगर_is_active(netdev))
				/* a dead bus has no overflows */
				जारी;
			++netdev->stats.rx_over_errors;
			softing_netdev_rx(netdev, &msg, 0);
		पूर्ण
		/* prepare क्रम other use */
		स_रखो(&msg, 0, माप(msg));
		++cnt;
	पूर्ण

	fअगरo_rd = ioपढ़ो8(&card->dpram[DPRAM_RX_RD]);
	fअगरo_wr = ioपढ़ो8(&card->dpram[DPRAM_RX_WR]);

	अगर (++fअगरo_rd >= DPRAM_RX_CNT)
		fअगरo_rd = 0;
	अगर (fअगरo_wr == fअगरo_rd)
		वापस cnt;

	स_नकल_fromio(buf, &card->dpram[DPRAM_RX + DPRAM_RX_SIZE*fअगरo_rd],
			DPRAM_RX_SIZE);
	mb();
	/* trigger dual port RAM */
	ioग_लिखो8(fअगरo_rd, &card->dpram[DPRAM_RX_RD]);

	ptr = buf;
	cmd = *ptr++;
	अगर (cmd == 0xff)
		/* not quite useful, probably the card has got out */
		वापस 0;
	netdev = card->net[0];
	अगर (cmd & CMD_BUS2)
		netdev = card->net[1];
	priv = netdev_priv(netdev);

	अगर (cmd & CMD_ERR) अणु
		uपूर्णांक8_t can_state, state;

		state = *ptr++;

		msg.can_id = CAN_ERR_FLAG;
		msg.len = CAN_ERR_DLC;

		अगर (state & SF_MASK_BUSOFF) अणु
			can_state = CAN_STATE_BUS_OFF;
			msg.can_id |= CAN_ERR_BUSOFF;
			state = STATE_BUSOFF;
		पूर्ण अन्यथा अगर (state & SF_MASK_EPASSIVE) अणु
			can_state = CAN_STATE_ERROR_PASSIVE;
			msg.can_id |= CAN_ERR_CRTL;
			msg.data[1] = CAN_ERR_CRTL_TX_PASSIVE;
			state = STATE_EPASSIVE;
		पूर्ण अन्यथा अणु
			can_state = CAN_STATE_ERROR_ACTIVE;
			msg.can_id |= CAN_ERR_CRTL;
			state = STATE_EACTIVE;
		पूर्ण
		/* update DPRAM */
		ioग_लिखो8(state, &card->dpram[priv->index ?
				DPRAM_INFO_BUSSTATE2 : DPRAM_INFO_BUSSTATE]);
		/* बारtamp */
		पंचांगp_u32 = le32_to_cpup((व्योम *)ptr);
		ptr += 4;
		kसमय = softing_raw2kसमय(card, पंचांगp_u32);

		++netdev->stats.rx_errors;
		/* update पूर्णांकernal status */
		अगर (can_state != priv->can.state) अणु
			priv->can.state = can_state;
			अगर (can_state == CAN_STATE_ERROR_PASSIVE)
				++priv->can.can_stats.error_passive;
			अन्यथा अगर (can_state == CAN_STATE_BUS_OFF) अणु
				/* this calls can_बंद_cleanup() */
				++priv->can.can_stats.bus_off;
				can_bus_off(netdev);
				netअगर_stop_queue(netdev);
			पूर्ण
			/* trigger socketcan */
			softing_netdev_rx(netdev, &msg, kसमय);
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (cmd & CMD_RTR)
			msg.can_id |= CAN_RTR_FLAG;
		msg.len = can_cc_dlc2len(*ptr++);
		अगर (cmd & CMD_XTD) अणु
			msg.can_id |= CAN_EFF_FLAG;
			msg.can_id |= le32_to_cpup((व्योम *)ptr);
			ptr += 4;
		पूर्ण अन्यथा अणु
			msg.can_id |= le16_to_cpup((व्योम *)ptr);
			ptr += 2;
		पूर्ण
		/* बारtamp */
		पंचांगp_u32 = le32_to_cpup((व्योम *)ptr);
		ptr += 4;
		kसमय = softing_raw2kसमय(card, पंचांगp_u32);
		अगर (!(msg.can_id & CAN_RTR_FLAG))
			स_नकल(&msg.data[0], ptr, 8);
		ptr += 8;
		/* update socket */
		अगर (cmd & CMD_ACK) अणु
			/* acknowledge, was tx msg */
			काष्ठा sk_buff *skb;
			skb = priv->can.echo_skb[priv->tx.echo_get];
			अगर (skb)
				skb->tstamp = kसमय;
			can_get_echo_skb(netdev, priv->tx.echo_get, शून्य);
			++priv->tx.echo_get;
			अगर (priv->tx.echo_get >= TX_ECHO_SKB_MAX)
				priv->tx.echo_get = 0;
			अगर (priv->tx.pending)
				--priv->tx.pending;
			अगर (card->tx.pending)
				--card->tx.pending;
			++netdev->stats.tx_packets;
			अगर (!(msg.can_id & CAN_RTR_FLAG))
				netdev->stats.tx_bytes += msg.len;
		पूर्ण अन्यथा अणु
			पूर्णांक ret;

			ret = softing_netdev_rx(netdev, &msg, kसमय);
			अगर (ret == NET_RX_SUCCESS) अणु
				++netdev->stats.rx_packets;
				अगर (!(msg.can_id & CAN_RTR_FLAG))
					netdev->stats.rx_bytes += msg.len;
			पूर्ण अन्यथा अणु
				++netdev->stats.rx_dropped;
			पूर्ण
		पूर्ण
	पूर्ण
	++cnt;
	वापस cnt;
पूर्ण

/*
 * real पूर्णांकerrupt handler
 */
अटल irqवापस_t softing_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा softing *card = (काष्ठा softing *)dev_id;
	काष्ठा net_device *netdev;
	काष्ठा softing_priv *priv;
	पूर्णांक j, offset, work_करोne;

	work_करोne = 0;
	spin_lock_bh(&card->spin);
	जबतक (softing_handle_1(card) > 0) अणु
		++card->irq.svc_count;
		++work_करोne;
	पूर्ण
	spin_unlock_bh(&card->spin);
	/* resume tx queue's */
	offset = card->tx.last_bus;
	क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
		अगर (card->tx.pending >= TXMAX)
			अवरोध;
		netdev = card->net[(j + offset + 1) % card->pdat->nbus];
		अगर (!netdev)
			जारी;
		priv = netdev_priv(netdev);
		अगर (!canअगर_is_active(netdev))
			/* it makes no sense to wake dead buses */
			जारी;
		अगर (priv->tx.pending >= TX_ECHO_SKB_MAX)
			जारी;
		++work_करोne;
		netअगर_wake_queue(netdev);
	पूर्ण
	वापस work_करोne ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/*
 * पूर्णांकerrupt routines:
 * schedule the 'real interrupt handler'
 */
अटल irqवापस_t softing_irq_v2(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा softing *card = (काष्ठा softing *)dev_id;
	uपूर्णांक8_t ir;

	ir = ioपढ़ो8(&card->dpram[DPRAM_V2_IRQ_TOHOST]);
	ioग_लिखो8(0, &card->dpram[DPRAM_V2_IRQ_TOHOST]);
	वापस (1 == ir) ? IRQ_WAKE_THREAD : IRQ_NONE;
पूर्ण

अटल irqवापस_t softing_irq_v1(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा softing *card = (काष्ठा softing *)dev_id;
	uपूर्णांक8_t ir;

	ir = ioपढ़ो8(&card->dpram[DPRAM_IRQ_TOHOST]);
	ioग_लिखो8(0, &card->dpram[DPRAM_IRQ_TOHOST]);
	वापस ir ? IRQ_WAKE_THREAD : IRQ_NONE;
पूर्ण

/*
 * netdev/candev पूर्णांकeroperability
 */
अटल पूर्णांक softing_netdev_खोलो(काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;

	/* check or determine and set bitसमय */
	ret = खोलो_candev(ndev);
	अगर (ret)
		वापस ret;

	ret = softing_startstop(ndev, 1);
	अगर (ret < 0)
		बंद_candev(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक softing_netdev_stop(काष्ठा net_device *ndev)
अणु
	पूर्णांक ret;

	netअगर_stop_queue(ndev);

	/* softing cycle करोes बंद_candev() */
	ret = softing_startstop(ndev, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक softing_candev_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	पूर्णांक ret;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		/* softing_startstop करोes बंद_candev() */
		ret = softing_startstop(ndev, 1);
		वापस ret;
	हाल CAN_MODE_STOP:
	हाल CAN_MODE_SLEEP:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Softing device management helpers
 */
पूर्णांक softing_enable_irq(काष्ठा softing *card, पूर्णांक enable)
अणु
	पूर्णांक ret;

	अगर (!card->irq.nr) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (card->irq.requested && !enable) अणु
		मुक्त_irq(card->irq.nr, card);
		card->irq.requested = 0;
	पूर्ण अन्यथा अगर (!card->irq.requested && enable) अणु
		ret = request_thपढ़ोed_irq(card->irq.nr,
				(card->pdat->generation >= 2) ?
					softing_irq_v2 : softing_irq_v1,
				softing_irq_thपढ़ो, IRQF_SHARED,
				dev_name(&card->pdev->dev), card);
		अगर (ret) अणु
			dev_alert(&card->pdev->dev,
					"request_threaded_irq(%u) failed\n",
					card->irq.nr);
			वापस ret;
		पूर्ण
		card->irq.requested = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम softing_card_shutकरोwn(काष्ठा softing *card)
अणु
	पूर्णांक fw_up = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&card->fw.lock)) अणु
		/* वापस -ERESTARTSYS */;
	पूर्ण
	fw_up = card->fw.up;
	card->fw.up = 0;

	अगर (card->irq.requested && card->irq.nr) अणु
		मुक्त_irq(card->irq.nr, card);
		card->irq.requested = 0;
	पूर्ण
	अगर (fw_up) अणु
		अगर (card->pdat->enable_irq)
			card->pdat->enable_irq(card->pdev, 0);
		softing_set_reset_dpram(card);
		अगर (card->pdat->reset)
			card->pdat->reset(card->pdev, 1);
	पूर्ण
	mutex_unlock(&card->fw.lock);
पूर्ण

अटल पूर्णांक softing_card_boot(काष्ठा softing *card)
अणु
	पूर्णांक ret, j;
	अटल स्थिर uपूर्णांक8_t stream[] = अणु
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, पूर्ण;
	अचिन्हित अक्षर back[माप(stream)];

	अगर (mutex_lock_पूर्णांकerruptible(&card->fw.lock))
		वापस -ERESTARTSYS;
	अगर (card->fw.up) अणु
		mutex_unlock(&card->fw.lock);
		वापस 0;
	पूर्ण
	/* reset board */
	अगर (card->pdat->enable_irq)
		card->pdat->enable_irq(card->pdev, 1);
	/* boot card */
	softing_set_reset_dpram(card);
	अगर (card->pdat->reset)
		card->pdat->reset(card->pdev, 1);
	क्रम (j = 0; (j + माप(stream)) < card->dpram_size;
			j += माप(stream)) अणु

		स_नकल_toio(&card->dpram[j], stream, माप(stream));
		/* flush IO cache */
		mb();
		स_नकल_fromio(back, &card->dpram[j], माप(stream));

		अगर (!स_भेद(back, stream, माप(stream)))
			जारी;
		/* memory is not equal */
		dev_alert(&card->pdev->dev, "dpram failed at 0x%04x\n", j);
		ret = -EIO;
		जाओ failed;
	पूर्ण
	wmb();
	/* load boot firmware */
	ret = softing_load_fw(card->pdat->boot.fw, card, card->dpram,
				card->dpram_size,
				card->pdat->boot.offs - card->pdat->boot.addr);
	अगर (ret < 0)
		जाओ failed;
	/* load loader firmware */
	ret = softing_load_fw(card->pdat->load.fw, card, card->dpram,
				card->dpram_size,
				card->pdat->load.offs - card->pdat->load.addr);
	अगर (ret < 0)
		जाओ failed;

	अगर (card->pdat->reset)
		card->pdat->reset(card->pdev, 0);
	softing_clr_reset_dpram(card);
	ret = softing_bootloader_command(card, 0, "card boot");
	अगर (ret < 0)
		जाओ failed;
	ret = softing_load_app_fw(card->pdat->app.fw, card);
	अगर (ret < 0)
		जाओ failed;

	ret = softing_chip_घातeron(card);
	अगर (ret < 0)
		जाओ failed;

	card->fw.up = 1;
	mutex_unlock(&card->fw.lock);
	वापस 0;
failed:
	card->fw.up = 0;
	अगर (card->pdat->enable_irq)
		card->pdat->enable_irq(card->pdev, 0);
	softing_set_reset_dpram(card);
	अगर (card->pdat->reset)
		card->pdat->reset(card->pdev, 1);
	mutex_unlock(&card->fw.lock);
	वापस ret;
पूर्ण

/*
 * netdev sysfs
 */
अटल sमाप_प्रकार show_chip(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	काष्ठा softing_priv *priv = netdev2softing(ndev);

	वापस प्र_लिखो(buf, "%i\n", priv->chip);
पूर्ण

अटल sमाप_प्रकार show_output(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	काष्ठा softing_priv *priv = netdev2softing(ndev);

	वापस प्र_लिखो(buf, "0x%02x\n", priv->output);
पूर्ण

अटल sमाप_प्रकार store_output(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा net_device *ndev = to_net_dev(dev);
	काष्ठा softing_priv *priv = netdev2softing(ndev);
	काष्ठा softing *card = priv->card;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;
	val &= 0xFF;

	ret = mutex_lock_पूर्णांकerruptible(&card->fw.lock);
	अगर (ret)
		वापस -ERESTARTSYS;
	अगर (netअगर_running(ndev)) अणु
		mutex_unlock(&card->fw.lock);
		वापस -EBUSY;
	पूर्ण
	priv->output = val;
	mutex_unlock(&card->fw.lock);
	वापस count;
पूर्ण

अटल स्थिर DEVICE_ATTR(chip, 0444, show_chip, शून्य);
अटल स्थिर DEVICE_ATTR(output, 0644, show_output, store_output);

अटल स्थिर काष्ठा attribute *स्थिर netdev_sysfs_attrs[] = अणु
	&dev_attr_chip.attr,
	&dev_attr_output.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group netdev_sysfs_group = अणु
	.name = शून्य,
	.attrs = (काष्ठा attribute **)netdev_sysfs_attrs,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops softing_netdev_ops = अणु
	.nकरो_खोलो = softing_netdev_खोलो,
	.nकरो_stop = softing_netdev_stop,
	.nकरो_start_xmit	= softing_netdev_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर softing_btr_स्थिर = अणु
	.name = "softing",
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4, /* overruled */
	.brp_min = 1,
	.brp_max = 32, /* overruled */
	.brp_inc = 1,
पूर्ण;


अटल काष्ठा net_device *softing_netdev_create(काष्ठा softing *card,
						uपूर्णांक16_t chip_id)
अणु
	काष्ठा net_device *netdev;
	काष्ठा softing_priv *priv;

	netdev = alloc_candev(माप(*priv), TX_ECHO_SKB_MAX);
	अगर (!netdev) अणु
		dev_alert(&card->pdev->dev, "alloc_candev failed\n");
		वापस शून्य;
	पूर्ण
	priv = netdev_priv(netdev);
	priv->netdev = netdev;
	priv->card = card;
	स_नकल(&priv->btr_स्थिर, &softing_btr_स्थिर, माप(priv->btr_स्थिर));
	priv->btr_स्थिर.brp_max = card->pdat->max_brp;
	priv->btr_स्थिर.sjw_max = card->pdat->max_sjw;
	priv->can.bittiming_स्थिर = &priv->btr_स्थिर;
	priv->can.घड़ी.freq = 8000000;
	priv->chip = chip_id;
	priv->output = softing_शेष_output(netdev);
	SET_NETDEV_DEV(netdev, &card->pdev->dev);

	netdev->flags |= IFF_ECHO;
	netdev->netdev_ops = &softing_netdev_ops;
	priv->can.करो_set_mode = softing_candev_set_mode;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES;

	वापस netdev;
पूर्ण

अटल पूर्णांक softing_netdev_रेजिस्टर(काष्ठा net_device *netdev)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_candev(netdev);
	अगर (ret) अणु
		dev_alert(&netdev->dev, "register failed\n");
		वापस ret;
	पूर्ण
	अगर (sysfs_create_group(&netdev->dev.kobj, &netdev_sysfs_group) < 0)
		netdev_alert(netdev, "sysfs group failed\n");

	वापस 0;
पूर्ण

अटल व्योम softing_netdev_cleanup(काष्ठा net_device *netdev)
अणु
	sysfs_हटाओ_group(&netdev->dev.kobj, &netdev_sysfs_group);
	unरेजिस्टर_candev(netdev);
	मुक्त_candev(netdev);
पूर्ण

/*
 * sysfs क्रम Platक्रमm device
 */
#घोषणा DEV_ATTR_RO(name, member) \
अटल sमाप_प्रकार show_##name(काष्ठा device *dev, \
		काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा softing *card = dev_get_drvdata(dev); \
	वापस प्र_लिखो(buf, "%u\n", card->member); \
पूर्ण \
अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

#घोषणा DEV_ATTR_RO_STR(name, member) \
अटल sमाप_प्रकार show_##name(काष्ठा device *dev, \
		काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा softing *card = dev_get_drvdata(dev); \
	वापस प्र_लिखो(buf, "%s\n", card->member); \
पूर्ण \
अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

DEV_ATTR_RO(serial, id.serial);
DEV_ATTR_RO_STR(firmware, pdat->app.fw);
DEV_ATTR_RO(firmware_version, id.fw_version);
DEV_ATTR_RO_STR(hardware, pdat->name);
DEV_ATTR_RO(hardware_version, id.hw_version);
DEV_ATTR_RO(license, id.license);

अटल काष्ठा attribute *softing_pdev_attrs[] = अणु
	&dev_attr_serial.attr,
	&dev_attr_firmware.attr,
	&dev_attr_firmware_version.attr,
	&dev_attr_hardware.attr,
	&dev_attr_hardware_version.attr,
	&dev_attr_license.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group softing_pdev_group = अणु
	.name = शून्य,
	.attrs = softing_pdev_attrs,
पूर्ण;

/*
 * platक्रमm driver
 */
अटल पूर्णांक softing_pdev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा softing *card = platक्रमm_get_drvdata(pdev);
	पूर्णांक j;

	/* first, disable card*/
	softing_card_shutकरोwn(card);

	क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
		अगर (!card->net[j])
			जारी;
		softing_netdev_cleanup(card->net[j]);
		card->net[j] = शून्य;
	पूर्ण
	sysfs_हटाओ_group(&pdev->dev.kobj, &softing_pdev_group);

	iounmap(card->dpram);
	kमुक्त(card);
	वापस 0;
पूर्ण

अटल पूर्णांक softing_pdev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा softing_platक्रमm_data *pdat = dev_get_platdata(&pdev->dev);
	काष्ठा softing *card;
	काष्ठा net_device *netdev;
	काष्ठा softing_priv *priv;
	काष्ठा resource *pres;
	पूर्णांक ret;
	पूर्णांक j;

	अगर (!pdat) अणु
		dev_warn(&pdev->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण
	अगर (pdat->nbus > ARRAY_SIZE(card->net)) अणु
		dev_warn(&pdev->dev, "%u nets??\n", pdat->nbus);
		वापस -EINVAL;
	पूर्ण

	card = kzalloc(माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;
	card->pdat = pdat;
	card->pdev = pdev;
	platक्रमm_set_drvdata(pdev, card);
	mutex_init(&card->fw.lock);
	spin_lock_init(&card->spin);

	ret = -EINVAL;
	pres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!pres)
		जाओ platक्रमm_resource_failed;
	card->dpram_phys = pres->start;
	card->dpram_size = resource_size(pres);
	card->dpram = ioremap(card->dpram_phys, card->dpram_size);
	अगर (!card->dpram) अणु
		dev_alert(&card->pdev->dev, "dpram ioremap failed\n");
		जाओ ioremap_failed;
	पूर्ण

	pres = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (pres)
		card->irq.nr = pres->start;

	/* reset card */
	ret = softing_card_boot(card);
	अगर (ret < 0) अणु
		dev_alert(&pdev->dev, "failed to boot\n");
		जाओ boot_failed;
	पूर्ण

	/* only now, the chip's are known */
	card->id.freq = card->pdat->freq;

	ret = sysfs_create_group(&pdev->dev.kobj, &softing_pdev_group);
	अगर (ret < 0) अणु
		dev_alert(&card->pdev->dev, "sysfs failed\n");
		जाओ sysfs_failed;
	पूर्ण

	क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
		card->net[j] = netdev =
			softing_netdev_create(card, card->id.chip[j]);
		अगर (!netdev) अणु
			dev_alert(&pdev->dev, "failed to make can[%i]", j);
			ret = -ENOMEM;
			जाओ netdev_failed;
		पूर्ण
		netdev->dev_id = j;
		priv = netdev_priv(card->net[j]);
		priv->index = j;
		ret = softing_netdev_रेजिस्टर(netdev);
		अगर (ret) अणु
			मुक्त_candev(netdev);
			card->net[j] = शून्य;
			dev_alert(&card->pdev->dev,
					"failed to register can[%i]\n", j);
			जाओ netdev_failed;
		पूर्ण
	पूर्ण
	dev_info(&card->pdev->dev, "%s ready.\n", card->pdat->name);
	वापस 0;

netdev_failed:
	क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
		अगर (!card->net[j])
			जारी;
		softing_netdev_cleanup(card->net[j]);
	पूर्ण
	sysfs_हटाओ_group(&pdev->dev.kobj, &softing_pdev_group);
sysfs_failed:
	softing_card_shutकरोwn(card);
boot_failed:
	iounmap(card->dpram);
ioremap_failed:
platक्रमm_resource_failed:
	kमुक्त(card);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver softing_driver = अणु
	.driver = अणु
		.name = "softing",
	पूर्ण,
	.probe = softing_pdev_probe,
	.हटाओ = softing_pdev_हटाओ,
पूर्ण;

module_platक्रमm_driver(softing_driver);

MODULE_ALIAS("platform:softing");
MODULE_DESCRIPTION("Softing DPRAM CAN driver");
MODULE_AUTHOR("Kurt Van Dijck <kurt.van.dijck@eia.be>");
MODULE_LICENSE("GPL v2");
