<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch hardware बारtamping support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 National Instruments
 *      Erik Hons <erik.hons@ni.com>
 *      Bअक्रमon Streअगरf <bअक्रमon.streअगरf@ni.com>
 *      Dane Wagner <dane.wagner@ni.com>
 */

#समावेश "chip.h"
#समावेश "global2.h"
#समावेश "hwtstamp.h"
#समावेश "ptp.h"
#समावेश <linux/ptp_classअगरy.h>

#घोषणा SKB_PTP_TYPE(__skb) (*(अचिन्हित पूर्णांक *)((__skb)->cb))

अटल पूर्णांक mv88e6xxx_port_ptp_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   पूर्णांक addr, u16 *data, पूर्णांक len)
अणु
	अगर (!chip->info->ops->avb_ops->port_ptp_पढ़ो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->avb_ops->port_ptp_पढ़ो(chip, port, addr,
						       data, len);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_ptp_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक addr, u16 data)
अणु
	अगर (!chip->info->ops->avb_ops->port_ptp_ग_लिखो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->avb_ops->port_ptp_ग_लिखो(chip, port, addr,
							data);
पूर्ण

अटल पूर्णांक mv88e6xxx_ptp_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
			       u16 data)
अणु
	अगर (!chip->info->ops->avb_ops->ptp_ग_लिखो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->avb_ops->ptp_ग_लिखो(chip, addr, data);
पूर्ण

अटल पूर्णांक mv88e6xxx_ptp_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
			      u16 *data)
अणु
	अगर (!chip->info->ops->avb_ops->ptp_पढ़ो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->avb_ops->ptp_पढ़ो(chip, addr, data, 1);
पूर्ण

/* TX_TSTAMP_TIMEOUT: This limits the समय spent polling क्रम a TX
 * बारtamp. When working properly, hardware will produce a बारtamp
 * within 1ms. Software may enounter delays due to MDIO contention, so
 * the समयout is set accordingly.
 */
#घोषणा TX_TSTAMP_TIMEOUT	msecs_to_jअगरfies(40)

पूर्णांक mv88e6xxx_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  काष्ठा ethtool_ts_info *info)
अणु
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops;
	काष्ठा mv88e6xxx_chip *chip;

	chip = ds->priv;
	ptp_ops = chip->info->ops->ptp_ops;

	अगर (!chip->info->ptp_support)
		वापस -EOPNOTSUPP;

	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->phc_index = ptp_घड़ी_index(chip->ptp_घड़ी);
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->rx_filters = ptp_ops->rx_filters;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_set_hwtstamp_config(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					 काष्ठा hwtstamp_config *config)
अणु
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	काष्ठा mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	bool tstamp_enable = false;

	/* Prevent the TX/RX paths from trying to पूर्णांकeract with the
	 * बारtamp hardware जबतक we reconfigure it.
	 */
	clear_bit_unlock(MV88E6XXX_HWTSTAMP_ENABLED, &ps->state);

	/* reserved क्रम future extensions */
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		tstamp_enable = false;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		tstamp_enable = true;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	/* The चयन supports बारtamping both L2 and L4; one cannot be
	 * disabled independently of the other.
	 */

	अगर (!(BIT(config->rx_filter) & ptp_ops->rx_filters)) अणु
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		dev_dbg(chip->dev, "Unsupported rx_filter %d\n",
			config->rx_filter);
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		tstamp_enable = false;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	शेष:
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		वापस -दुस्फल;
	पूर्ण

	mv88e6xxx_reg_lock(chip);
	अगर (tstamp_enable) अणु
		chip->enable_count += 1;
		अगर (chip->enable_count == 1 && ptp_ops->global_enable)
			ptp_ops->global_enable(chip);
		अगर (ptp_ops->port_enable)
			ptp_ops->port_enable(chip, port);
	पूर्ण अन्यथा अणु
		अगर (ptp_ops->port_disable)
			ptp_ops->port_disable(chip, port);
		chip->enable_count -= 1;
		अगर (chip->enable_count == 0 && ptp_ops->global_disable)
			ptp_ops->global_disable(chip);
	पूर्ण
	mv88e6xxx_reg_unlock(chip);

	/* Once hardware has been configured, enable बारtamp checks
	 * in the RX/TX paths.
	 */
	अगर (tstamp_enable)
		set_bit(MV88E6XXX_HWTSTAMP_ENABLED, &ps->state);

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_port_hwtstamp_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	अगर (!chip->info->ptp_support)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = mv88e6xxx_set_hwtstamp_config(chip, port, &config);
	अगर (err)
		वापस err;

	/* Save the chosen configuration to be वापसed later. */
	स_नकल(&ps->tstamp_config, &config, माप(config));

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

पूर्णांक mv88e6xxx_port_hwtstamp_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	काष्ठा hwtstamp_config *config = &ps->tstamp_config;

	अगर (!chip->info->ptp_support)
		वापस -EOPNOTSUPP;

	वापस copy_to_user(अगरr->अगरr_data, config, माप(*config)) ?
		-EFAULT : 0;
पूर्ण

/* Returns a poपूर्णांकer to the PTP header अगर the caller should समय stamp,
 * or शून्य अगर the caller should not.
 */
अटल काष्ठा ptp_header *mv88e6xxx_should_tstamp(काष्ठा mv88e6xxx_chip *chip,
						  पूर्णांक port, काष्ठा sk_buff *skb,
						  अचिन्हित पूर्णांक type)
अणु
	काष्ठा mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	काष्ठा ptp_header *hdr;

	अगर (!chip->info->ptp_support)
		वापस शून्य;

	hdr = ptp_parse_header(skb, type);
	अगर (!hdr)
		वापस शून्य;

	अगर (!test_bit(MV88E6XXX_HWTSTAMP_ENABLED, &ps->state))
		वापस शून्य;

	वापस hdr;
पूर्ण

अटल पूर्णांक mv88e6xxx_ts_valid(u16 status)
अणु
	अगर (!(status & MV88E6XXX_PTP_TS_VALID))
		वापस 0;
	अगर (status & MV88E6XXX_PTP_TS_STATUS_MASK)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक seq_match(काष्ठा sk_buff *skb, u16 ts_seqid)
अणु
	अचिन्हित पूर्णांक type = SKB_PTP_TYPE(skb);
	काष्ठा ptp_header *hdr;

	hdr = ptp_parse_header(skb, type);

	वापस ts_seqid == ntohs(hdr->sequence_id);
पूर्ण

अटल व्योम mv88e6xxx_get_rxts(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mv88e6xxx_port_hwtstamp *ps,
			       काष्ठा sk_buff *skb, u16 reg,
			       काष्ठा sk_buff_head *rxq)
अणु
	u16 buf[4] = अणु 0 पूर्ण, status, seq_id;
	काष्ठा skb_shared_hwtstamps *shwt;
	काष्ठा sk_buff_head received;
	u64 ns, समयlo, समयhi;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	/* The latched बारtamp beदीर्घs to one of the received frames. */
	__skb_queue_head_init(&received);
	spin_lock_irqsave(&rxq->lock, flags);
	skb_queue_splice_tail_init(rxq, &received);
	spin_unlock_irqrestore(&rxq->lock, flags);

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_ptp_पढ़ो(chip, ps->port_id,
				      reg, buf, ARRAY_SIZE(buf));
	mv88e6xxx_reg_unlock(chip);
	अगर (err)
		pr_err("failed to get the receive time stamp\n");

	status = buf[0];
	समयlo = buf[1];
	समयhi = buf[2];
	seq_id = buf[3];

	अगर (status & MV88E6XXX_PTP_TS_VALID) अणु
		mv88e6xxx_reg_lock(chip);
		err = mv88e6xxx_port_ptp_ग_लिखो(chip, ps->port_id, reg, 0);
		mv88e6xxx_reg_unlock(chip);
		अगर (err)
			pr_err("failed to clear the receive status\n");
	पूर्ण
	/* Since the device can only handle one समय stamp at a समय,
	 * we purge any extra frames from the queue.
	 */
	क्रम ( ; skb; skb = __skb_dequeue(&received)) अणु
		अगर (mv88e6xxx_ts_valid(status) && seq_match(skb, seq_id)) अणु
			ns = समयhi << 16 | समयlo;

			mv88e6xxx_reg_lock(chip);
			ns = समयcounter_cyc2समय(&chip->tstamp_tc, ns);
			mv88e6xxx_reg_unlock(chip);
			shwt = skb_hwtstamps(skb);
			स_रखो(shwt, 0, माप(*shwt));
			shwt->hwtstamp = ns_to_kसमय(ns);
			status &= ~MV88E6XXX_PTP_TS_VALID;
		पूर्ण
		netअगर_rx_ni(skb);
	पूर्ण
पूर्ण

अटल व्योम mv88e6xxx_rxtstamp_work(काष्ठा mv88e6xxx_chip *chip,
				    काष्ठा mv88e6xxx_port_hwtstamp *ps)
अणु
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	काष्ठा sk_buff *skb;

	skb = skb_dequeue(&ps->rx_queue);

	अगर (skb)
		mv88e6xxx_get_rxts(chip, ps, skb, ptp_ops->arr0_sts_reg,
				   &ps->rx_queue);

	skb = skb_dequeue(&ps->rx_queue2);
	अगर (skb)
		mv88e6xxx_get_rxts(chip, ps, skb, ptp_ops->arr1_sts_reg,
				   &ps->rx_queue2);
पूर्ण

अटल पूर्णांक is_pdelay_resp(स्थिर काष्ठा ptp_header *hdr)
अणु
	वापस (hdr->tsmt & 0xf) == 3;
पूर्ण

bool mv88e6xxx_port_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type)
अणु
	काष्ठा mv88e6xxx_port_hwtstamp *ps;
	काष्ठा mv88e6xxx_chip *chip;
	काष्ठा ptp_header *hdr;

	chip = ds->priv;
	ps = &chip->port_hwtstamp[port];

	अगर (ps->tstamp_config.rx_filter != HWTSTAMP_FILTER_PTP_V2_EVENT)
		वापस false;

	hdr = mv88e6xxx_should_tstamp(chip, port, skb, type);
	अगर (!hdr)
		वापस false;

	SKB_PTP_TYPE(skb) = type;

	अगर (is_pdelay_resp(hdr))
		skb_queue_tail(&ps->rx_queue2, skb);
	अन्यथा
		skb_queue_tail(&ps->rx_queue, skb);

	ptp_schedule_worker(chip->ptp_घड़ी, 0);

	वापस true;
पूर्ण

अटल पूर्णांक mv88e6xxx_txtstamp_work(काष्ठा mv88e6xxx_chip *chip,
				   काष्ठा mv88e6xxx_port_hwtstamp *ps)
अणु
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	u16 departure_block[4], status;
	काष्ठा sk_buff *पंचांगp_skb;
	u32 समय_raw;
	पूर्णांक err;
	u64 ns;

	अगर (!ps->tx_skb)
		वापस 0;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_ptp_पढ़ो(chip, ps->port_id,
				      ptp_ops->dep_sts_reg,
				      departure_block,
				      ARRAY_SIZE(departure_block));
	mv88e6xxx_reg_unlock(chip);

	अगर (err)
		जाओ मुक्त_and_clear_skb;

	अगर (!(departure_block[0] & MV88E6XXX_PTP_TS_VALID)) अणु
		अगर (समय_is_beक्रमe_jअगरfies(ps->tx_tstamp_start +
					   TX_TSTAMP_TIMEOUT)) अणु
			dev_warn(chip->dev, "p%d: clearing tx timestamp hang\n",
				 ps->port_id);
			जाओ मुक्त_and_clear_skb;
		पूर्ण
		/* The बारtamp should be available quickly, जबतक getting it
		 * is high priority and समय bounded to only 10ms. A poll is
		 * warranted so restart the work.
		 */
		वापस 1;
	पूर्ण

	/* We have the बारtamp; go ahead and clear valid now */
	mv88e6xxx_reg_lock(chip);
	mv88e6xxx_port_ptp_ग_लिखो(chip, ps->port_id, ptp_ops->dep_sts_reg, 0);
	mv88e6xxx_reg_unlock(chip);

	status = departure_block[0] & MV88E6XXX_PTP_TS_STATUS_MASK;
	अगर (status != MV88E6XXX_PTP_TS_STATUS_NORMAL) अणु
		dev_warn(chip->dev, "p%d: tx timestamp overrun\n", ps->port_id);
		जाओ मुक्त_and_clear_skb;
	पूर्ण

	अगर (departure_block[3] != ps->tx_seq_id) अणु
		dev_warn(chip->dev, "p%d: unexpected seq. id\n", ps->port_id);
		जाओ मुक्त_and_clear_skb;
	पूर्ण

	स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
	समय_raw = ((u32)departure_block[2] << 16) | departure_block[1];
	mv88e6xxx_reg_lock(chip);
	ns = समयcounter_cyc2समय(&chip->tstamp_tc, समय_raw);
	mv88e6xxx_reg_unlock(chip);
	shhwtstamps.hwtstamp = ns_to_kसमय(ns);

	dev_dbg(chip->dev,
		"p%d: txtstamp %llx status 0x%04x skb ID 0x%04x hw ID 0x%04x\n",
		ps->port_id, kसमय_प्रकारo_ns(shhwtstamps.hwtstamp),
		departure_block[0], ps->tx_seq_id, departure_block[3]);

	/* skb_complete_tx_बारtamp() will मुक्त up the client to make
	 * another बारtamp-able transmit. We have to be पढ़ोy क्रम it
	 * -- by clearing the ps->tx_skb "flag" -- beक्रमehand.
	 */

	पंचांगp_skb = ps->tx_skb;
	ps->tx_skb = शून्य;
	clear_bit_unlock(MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS, &ps->state);
	skb_complete_tx_बारtamp(पंचांगp_skb, &shhwtstamps);

	वापस 0;

मुक्त_and_clear_skb:
	dev_kमुक्त_skb_any(ps->tx_skb);
	ps->tx_skb = शून्य;
	clear_bit_unlock(MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS, &ps->state);

	वापस 0;
पूर्ण

दीर्घ mv88e6xxx_hwtstamp_work(काष्ठा ptp_घड़ी_info *ptp)
अणु
	काष्ठा mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	काष्ठा dsa_चयन *ds = chip->ds;
	काष्ठा mv88e6xxx_port_hwtstamp *ps;
	पूर्णांक i, restart = 0;

	क्रम (i = 0; i < ds->num_ports; i++) अणु
		अगर (!dsa_is_user_port(ds, i))
			जारी;

		ps = &chip->port_hwtstamp[i];
		अगर (test_bit(MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS, &ps->state))
			restart |= mv88e6xxx_txtstamp_work(chip, ps);

		mv88e6xxx_rxtstamp_work(chip, ps);
	पूर्ण

	वापस restart ? 1 : -1;
पूर्ण

व्योम mv88e6xxx_port_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा mv88e6xxx_chip *chip = ds->priv;
	काष्ठा mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	काष्ठा ptp_header *hdr;
	काष्ठा sk_buff *clone;
	अचिन्हित पूर्णांक type;

	type = ptp_classअगरy_raw(skb);
	अगर (type == PTP_CLASS_NONE)
		वापस;

	hdr = mv88e6xxx_should_tstamp(chip, port, skb, type);
	अगर (!hdr)
		वापस;

	clone = skb_clone_sk(skb);
	अगर (!clone)
		वापस;

	अगर (test_and_set_bit_lock(MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS,
				  &ps->state)) अणु
		kमुक्त_skb(clone);
		वापस;
	पूर्ण

	ps->tx_skb = clone;
	ps->tx_tstamp_start = jअगरfies;
	ps->tx_seq_id = be16_to_cpu(hdr->sequence_id);

	ptp_schedule_worker(chip->ptp_घड़ी, 0);
पूर्ण

पूर्णांक mv88e6165_global_disable(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_ptp_पढ़ो(chip, MV88E6165_PTP_CFG, &val);
	अगर (err)
		वापस err;
	val |= MV88E6165_PTP_CFG_DISABLE_PTP;

	वापस mv88e6xxx_ptp_ग_लिखो(chip, MV88E6165_PTP_CFG, val);
पूर्ण

पूर्णांक mv88e6165_global_enable(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_ptp_पढ़ो(chip, MV88E6165_PTP_CFG, &val);
	अगर (err)
		वापस err;

	val &= ~(MV88E6165_PTP_CFG_DISABLE_PTP | MV88E6165_PTP_CFG_TSPEC_MASK);

	वापस mv88e6xxx_ptp_ग_लिखो(chip, MV88E6165_PTP_CFG, val);
पूर्ण

पूर्णांक mv88e6352_hwtstamp_port_disable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_port_ptp_ग_लिखो(chip, port, MV88E6XXX_PORT_PTP_CFG0,
					MV88E6XXX_PORT_PTP_CFG0_DISABLE_PTP);
पूर्ण

पूर्णांक mv88e6352_hwtstamp_port_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_port_ptp_ग_लिखो(chip, port, MV88E6XXX_PORT_PTP_CFG0,
					MV88E6XXX_PORT_PTP_CFG0_DISABLE_TSPEC_MATCH);
पूर्ण

अटल पूर्णांक mv88e6xxx_hwtstamp_port_setup(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	काष्ठा mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];

	ps->port_id = port;

	skb_queue_head_init(&ps->rx_queue);
	skb_queue_head_init(&ps->rx_queue2);

	अगर (ptp_ops->port_disable)
		वापस ptp_ops->port_disable(chip, port);

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_hwtstamp_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	पूर्णांक err;
	पूर्णांक i;

	/* Disable बारtamping on all ports. */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		err = mv88e6xxx_hwtstamp_port_setup(chip, i);
		अगर (err)
			वापस err;
	पूर्ण

	/* Disable PTP globally */
	अगर (ptp_ops->global_disable) अणु
		err = ptp_ops->global_disable(chip);
		अगर (err)
			वापस err;
	पूर्ण

	/* Set the ethertype of L2 PTP messages */
	err = mv88e6xxx_ptp_ग_लिखो(chip, MV88E6XXX_PTP_GC_ETYPE, ETH_P_1588);
	अगर (err)
		वापस err;

	/* MV88E6XXX_PTP_MSG_TYPE is a mask of PTP message types to
	 * बारtamp. This affects all ports that have बारtamping enabled,
	 * but the बारtamp config is per-port; thus we configure all events
	 * here and only support the HWTSTAMP_FILTER_*_EVENT filter types.
	 */
	err = mv88e6xxx_ptp_ग_लिखो(chip, MV88E6XXX_PTP_MSGTYPE,
				  MV88E6XXX_PTP_MSGTYPE_ALL_EVENT);
	अगर (err)
		वापस err;

	/* Use ARRIVAL1 क्रम peer delay response messages. */
	err = mv88e6xxx_ptp_ग_लिखो(chip, MV88E6XXX_PTP_TS_ARRIVAL_PTR,
				  MV88E6XXX_PTP_MSGTYPE_PDLAY_RES);
	अगर (err)
		वापस err;

	/* 88E6341 devices शेष to बारtamping at the PHY, but this has
	 * a hardware issue that results in unreliable बारtamps. Force
	 * these devices to बारtamp at the MAC.
	 */
	अगर (chip->info->family == MV88E6XXX_FAMILY_6341) अणु
		u16 val = MV88E6341_PTP_CFG_UPDATE |
			  MV88E6341_PTP_CFG_MODE_IDX |
			  MV88E6341_PTP_CFG_MODE_TS_AT_MAC;
		err = mv88e6xxx_ptp_ग_लिखो(chip, MV88E6341_PTP_CFG, val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mv88e6xxx_hwtstamp_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
पूर्ण
