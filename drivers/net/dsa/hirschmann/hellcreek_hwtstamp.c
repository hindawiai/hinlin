<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * DSA driver क्रम:
 * Hirschmann Hellcreek TSN चयन.
 *
 * Copyright (C) 2019,2020 Hochschule Offenburg
 * Copyright (C) 2019,2020 Linutronix GmbH
 * Authors: Kamil Alkhouri <kamil.alkhouri@hs-offenburg.de>
 *	    Kurt Kanzenbach <kurt@linutronix.de>
 */

#समावेश <linux/ptp_classअगरy.h>

#समावेश "hellcreek.h"
#समावेश "hellcreek_hwtstamp.h"
#समावेश "hellcreek_ptp.h"

पूर्णांक hellcreek_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;

	info->phc_index = hellcreek->ptp_घड़ी ?
		ptp_घड़ी_index(hellcreek->ptp_घड़ी) : -1;
	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;

	/* enabled tx बारtamping */
	info->tx_types = BIT(HWTSTAMP_TX_ON);

	/* L2 & L4 PTPv2 event rx messages are बारtamped */
	info->rx_filters = BIT(HWTSTAMP_FILTER_PTP_V2_EVENT);

	वापस 0;
पूर्ण

/* Enabling/disabling TX and RX HW बारtamping क्रम dअगरferent PTP messages is
 * not available in the चयन. Thus, this function only serves as a check अगर
 * the user requested what is actually available or not
 */
अटल पूर्णांक hellcreek_set_hwtstamp_config(काष्ठा hellcreek *hellcreek, पूर्णांक port,
					 काष्ठा hwtstamp_config *config)
अणु
	काष्ठा hellcreek_port_hwtstamp *ps =
		&hellcreek->ports[port].port_hwtstamp;
	bool tx_tstamp_enable = false;
	bool rx_tstamp_enable = false;

	/* Interaction with the बारtamp hardware is prevented here.  It is
	 * enabled when this config function ends successfully
	 */
	clear_bit_unlock(HELLCREEK_HWTSTAMP_ENABLED, &ps->state);

	/* Reserved क्रम future extensions */
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_ON:
		tx_tstamp_enable = true;
		अवरोध;

	/* TX HW बारtamping can't be disabled on the चयन */
	हाल HWTSTAMP_TX_OFF:
		config->tx_type = HWTSTAMP_TX_ON;
		अवरोध;

	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	/* RX HW बारtamping can't be disabled on the चयन */
	हाल HWTSTAMP_FILTER_NONE:
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
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
		rx_tstamp_enable = true;
		अवरोध;

	/* RX HW बारtamping can't be enabled क्रम all messages on the चयन */
	हाल HWTSTAMP_FILTER_ALL:
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;

	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (!tx_tstamp_enable)
		वापस -दुस्फल;

	अगर (!rx_tstamp_enable)
		वापस -दुस्फल;

	/* If this poपूर्णांक is reached, then the requested hwtstamp config is
	 * compatible with the hwtstamp offered by the चयन.  Thereक्रमe,
	 * enable the पूर्णांकeraction with the HW बारtamping
	 */
	set_bit(HELLCREEK_HWTSTAMP_ENABLED, &ps->state);

	वापस 0;
पूर्ण

पूर्णांक hellcreek_port_hwtstamp_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port_hwtstamp *ps;
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	ps = &hellcreek->ports[port].port_hwtstamp;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = hellcreek_set_hwtstamp_config(hellcreek, port, &config);
	अगर (err)
		वापस err;

	/* Save the chosen configuration to be वापसed later */
	स_नकल(&ps->tstamp_config, &config, माप(config));

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

पूर्णांक hellcreek_port_hwtstamp_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port_hwtstamp *ps;
	काष्ठा hwtstamp_config *config;

	ps = &hellcreek->ports[port].port_hwtstamp;
	config = &ps->tstamp_config;

	वापस copy_to_user(अगरr->अगरr_data, config, माप(*config)) ?
		-EFAULT : 0;
पूर्ण

/* Returns a poपूर्णांकer to the PTP header अगर the caller should समय stamp, or शून्य
 * अगर the caller should not.
 */
अटल काष्ठा ptp_header *hellcreek_should_tstamp(काष्ठा hellcreek *hellcreek,
						  पूर्णांक port, काष्ठा sk_buff *skb,
						  अचिन्हित पूर्णांक type)
अणु
	काष्ठा hellcreek_port_hwtstamp *ps =
		&hellcreek->ports[port].port_hwtstamp;
	काष्ठा ptp_header *hdr;

	hdr = ptp_parse_header(skb, type);
	अगर (!hdr)
		वापस शून्य;

	अगर (!test_bit(HELLCREEK_HWTSTAMP_ENABLED, &ps->state))
		वापस शून्य;

	वापस hdr;
पूर्ण

अटल u64 hellcreek_get_reserved_field(स्थिर काष्ठा ptp_header *hdr)
अणु
	वापस be32_to_cpu(hdr->reserved2);
पूर्ण

अटल व्योम hellcreek_clear_reserved_field(काष्ठा ptp_header *hdr)
अणु
	hdr->reserved2 = 0;
पूर्ण

अटल पूर्णांक hellcreek_ptp_hwtstamp_available(काष्ठा hellcreek *hellcreek,
					    अचिन्हित पूर्णांक ts_reg)
अणु
	u16 status;

	status = hellcreek_ptp_पढ़ो(hellcreek, ts_reg);

	अगर (status & PR_TS_STATUS_TS_LOST)
		dev_err(hellcreek->dev,
			"Tx time stamp lost! This should never happen!\n");

	/* If hwtstamp is not available, this means the previous hwtstamp was
	 * successfully पढ़ो, and the one we need is not yet available
	 */
	वापस (status & PR_TS_STATUS_TS_AVAIL) ? 1 : 0;
पूर्ण

/* Get nanoseconds बारtamp from बारtamping unit */
अटल u64 hellcreek_ptp_hwtstamp_पढ़ो(काष्ठा hellcreek *hellcreek,
				       अचिन्हित पूर्णांक ts_reg)
अणु
	u16 nsl, nsh;

	nsh = hellcreek_ptp_पढ़ो(hellcreek, ts_reg);
	nsh = hellcreek_ptp_पढ़ो(hellcreek, ts_reg);
	nsh = hellcreek_ptp_पढ़ो(hellcreek, ts_reg);
	nsh = hellcreek_ptp_पढ़ो(hellcreek, ts_reg);
	nsl = hellcreek_ptp_पढ़ो(hellcreek, ts_reg);

	वापस (u64)nsl | ((u64)nsh << 16);
पूर्ण

अटल पूर्णांक hellcreek_txtstamp_work(काष्ठा hellcreek *hellcreek,
				   काष्ठा hellcreek_port_hwtstamp *ps, पूर्णांक port)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	अचिन्हित पूर्णांक status_reg, data_reg;
	काष्ठा sk_buff *पंचांगp_skb;
	पूर्णांक ts_status;
	u64 ns = 0;

	अगर (!ps->tx_skb)
		वापस 0;

	चयन (port) अणु
	हाल 2:
		status_reg = PR_TS_TX_P1_STATUS_C;
		data_reg   = PR_TS_TX_P1_DATA_C;
		अवरोध;
	हाल 3:
		status_reg = PR_TS_TX_P2_STATUS_C;
		data_reg   = PR_TS_TX_P2_DATA_C;
		अवरोध;
	शेष:
		dev_err(hellcreek->dev, "Wrong port for timestamping!\n");
		वापस 0;
	पूर्ण

	ts_status = hellcreek_ptp_hwtstamp_available(hellcreek, status_reg);

	/* Not available yet? */
	अगर (ts_status == 0) अणु
		/* Check whether the operation of पढ़ोing the tx बारtamp has
		 * exceeded its allowed period
		 */
		अगर (समय_is_beक्रमe_jअगरfies(ps->tx_tstamp_start +
					   TX_TSTAMP_TIMEOUT)) अणु
			dev_err(hellcreek->dev,
				"Timeout while waiting for Tx timestamp!\n");
			जाओ मुक्त_and_clear_skb;
		पूर्ण

		/* The बारtamp should be available quickly, जबतक getting it
		 * in high priority. Restart the work
		 */
		वापस 1;
	पूर्ण

	mutex_lock(&hellcreek->ptp_lock);
	ns  = hellcreek_ptp_hwtstamp_पढ़ो(hellcreek, data_reg);
	ns += hellcreek_ptp_समय_लो_seconds(hellcreek, ns);
	mutex_unlock(&hellcreek->ptp_lock);

	/* Now we have the बारtamp in nanoseconds, store it in the correct
	 * काष्ठाure in order to send it to the user
	 */
	स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_kसमय(ns);

	पंचांगp_skb = ps->tx_skb;
	ps->tx_skb = शून्य;

	/* skb_complete_tx_बारtamp() मुक्तs up the client to make another
	 * बारtampable transmit.  We have to be पढ़ोy क्रम it by clearing the
	 * ps->tx_skb "flag" beक्रमehand
	 */
	clear_bit_unlock(HELLCREEK_HWTSTAMP_TX_IN_PROGRESS, &ps->state);

	/* Deliver a clone of the original outgoing tx_skb with tx hwtstamp */
	skb_complete_tx_बारtamp(पंचांगp_skb, &shhwtstamps);

	वापस 0;

मुक्त_and_clear_skb:
	dev_kमुक्त_skb_any(ps->tx_skb);
	ps->tx_skb = शून्य;
	clear_bit_unlock(HELLCREEK_HWTSTAMP_TX_IN_PROGRESS, &ps->state);

	वापस 0;
पूर्ण

अटल व्योम hellcreek_get_rxts(काष्ठा hellcreek *hellcreek,
			       काष्ठा hellcreek_port_hwtstamp *ps,
			       काष्ठा sk_buff *skb, काष्ठा sk_buff_head *rxq,
			       पूर्णांक port)
अणु
	काष्ठा skb_shared_hwtstamps *shwt;
	काष्ठा sk_buff_head received;
	अचिन्हित दीर्घ flags;

	/* The latched बारtamp beदीर्घs to one of the received frames. */
	__skb_queue_head_init(&received);

	/* Lock & disable पूर्णांकerrupts */
	spin_lock_irqsave(&rxq->lock, flags);

	/* Add the reception queue "rxq" to the "received" queue an reपूर्णांकialize
	 * "rxq".  From now on, we deal with "received" not with "rxq"
	 */
	skb_queue_splice_tail_init(rxq, &received);

	spin_unlock_irqrestore(&rxq->lock, flags);

	क्रम (; skb; skb = __skb_dequeue(&received)) अणु
		काष्ठा ptp_header *hdr;
		अचिन्हित पूर्णांक type;
		u64 ns;

		/* Get nanoseconds from ptp packet */
		type = SKB_PTP_TYPE(skb);
		hdr  = ptp_parse_header(skb, type);
		ns   = hellcreek_get_reserved_field(hdr);
		hellcreek_clear_reserved_field(hdr);

		/* Add seconds part */
		mutex_lock(&hellcreek->ptp_lock);
		ns += hellcreek_ptp_समय_लो_seconds(hellcreek, ns);
		mutex_unlock(&hellcreek->ptp_lock);

		/* Save समय stamp */
		shwt = skb_hwtstamps(skb);
		स_रखो(shwt, 0, माप(*shwt));
		shwt->hwtstamp = ns_to_kसमय(ns);
		netअगर_rx_ni(skb);
	पूर्ण
पूर्ण

अटल व्योम hellcreek_rxtstamp_work(काष्ठा hellcreek *hellcreek,
				    काष्ठा hellcreek_port_hwtstamp *ps,
				    पूर्णांक port)
अणु
	काष्ठा sk_buff *skb;

	skb = skb_dequeue(&ps->rx_queue);
	अगर (skb)
		hellcreek_get_rxts(hellcreek, ps, skb, &ps->rx_queue, port);
पूर्ण

दीर्घ hellcreek_hwtstamp_work(काष्ठा ptp_घड़ी_info *ptp)
अणु
	काष्ठा hellcreek *hellcreek = ptp_to_hellcreek(ptp);
	काष्ठा dsa_चयन *ds = hellcreek->ds;
	पूर्णांक i, restart = 0;

	क्रम (i = 0; i < ds->num_ports; i++) अणु
		काष्ठा hellcreek_port_hwtstamp *ps;

		अगर (!dsa_is_user_port(ds, i))
			जारी;

		ps = &hellcreek->ports[i].port_hwtstamp;

		अगर (test_bit(HELLCREEK_HWTSTAMP_TX_IN_PROGRESS, &ps->state))
			restart |= hellcreek_txtstamp_work(hellcreek, ps, i);

		hellcreek_rxtstamp_work(hellcreek, ps, i);
	पूर्ण

	वापस restart ? 1 : -1;
पूर्ण

व्योम hellcreek_port_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port_hwtstamp *ps;
	काष्ठा ptp_header *hdr;
	काष्ठा sk_buff *clone;
	अचिन्हित पूर्णांक type;

	ps = &hellcreek->ports[port].port_hwtstamp;

	type = ptp_classअगरy_raw(skb);
	अगर (type == PTP_CLASS_NONE)
		वापस;

	/* Make sure the message is a PTP message that needs to be बारtamped
	 * and the पूर्णांकeraction with the HW बारtamping is enabled. If not, stop
	 * here
	 */
	hdr = hellcreek_should_tstamp(hellcreek, port, skb, type);
	अगर (!hdr)
		वापस;

	clone = skb_clone_sk(skb);
	अगर (!clone)
		वापस;

	अगर (test_and_set_bit_lock(HELLCREEK_HWTSTAMP_TX_IN_PROGRESS,
				  &ps->state)) अणु
		kमुक्त_skb(clone);
		वापस;
	पूर्ण

	ps->tx_skb = clone;

	/* store the number of ticks occurred since प्रणाली start-up till this
	 * moment
	 */
	ps->tx_tstamp_start = jअगरfies;

	ptp_schedule_worker(hellcreek->ptp_घड़ी, 0);
पूर्ण

bool hellcreek_port_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port_hwtstamp *ps;
	काष्ठा ptp_header *hdr;

	ps = &hellcreek->ports[port].port_hwtstamp;

	/* This check only fails अगर the user did not initialize hardware
	 * बारtamping beक्रमehand.
	 */
	अगर (ps->tstamp_config.rx_filter != HWTSTAMP_FILTER_PTP_V2_EVENT)
		वापस false;

	/* Make sure the message is a PTP message that needs to be बारtamped
	 * and the पूर्णांकeraction with the HW बारtamping is enabled. If not, stop
	 * here
	 */
	hdr = hellcreek_should_tstamp(hellcreek, port, skb, type);
	अगर (!hdr)
		वापस false;

	SKB_PTP_TYPE(skb) = type;

	skb_queue_tail(&ps->rx_queue, skb);

	ptp_schedule_worker(hellcreek->ptp_घड़ी, 0);

	वापस true;
पूर्ण

अटल व्योम hellcreek_hwtstamp_port_setup(काष्ठा hellcreek *hellcreek, पूर्णांक port)
अणु
	काष्ठा hellcreek_port_hwtstamp *ps =
		&hellcreek->ports[port].port_hwtstamp;

	skb_queue_head_init(&ps->rx_queue);
पूर्ण

पूर्णांक hellcreek_hwtstamp_setup(काष्ठा hellcreek *hellcreek)
अणु
	काष्ठा dsa_चयन *ds = hellcreek->ds;
	पूर्णांक i;

	/* Initialize बारtamping ports. */
	क्रम (i = 0; i < ds->num_ports; ++i) अणु
		अगर (!dsa_is_user_port(ds, i))
			जारी;

		hellcreek_hwtstamp_port_setup(hellcreek, i);
	पूर्ण

	/* Select the synchronized घड़ी as the source समयkeeper क्रम the
	 * बारtamps and enable अंतरभूत बारtamping.
	 */
	hellcreek_ptp_ग_लिखो(hellcreek, PR_SETTINGS_C_TS_SRC_TK_MASK |
			    PR_SETTINGS_C_RES3TS,
			    PR_SETTINGS_C);

	वापस 0;
पूर्ण

व्योम hellcreek_hwtstamp_मुक्त(काष्ठा hellcreek *hellcreek)
अणु
	/* Nothing toकरो */
पूर्ण
