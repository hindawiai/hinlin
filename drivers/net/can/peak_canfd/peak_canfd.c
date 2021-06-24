<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2007, 2011 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 * Copyright (C) 2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 *
 * Copyright (C) 2016  PEAK System-Technik GmbH
 */

#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>

#समावेश "peak_canfd_user.h"

/* पूर्णांकernal IP core cache size (used as शेष echo skbs max number) */
#घोषणा PCANFD_ECHO_SKB_MAX		24

/* bittiming ranges of the PEAK-System PC CAN-FD पूर्णांकerfaces */
अटल स्थिर काष्ठा can_bittiming_स्थिर peak_canfd_nominal_स्थिर = अणु
	.name = "peak_canfd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TSLOW_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TSLOW_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TSLOW_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TSLOW_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर peak_canfd_data_स्थिर = अणु
	.name = "peak_canfd",
	.tseg1_min = 1,
	.tseg1_max = (1 << PUCAN_TFAST_TSGEG1_BITS),
	.tseg2_min = 1,
	.tseg2_max = (1 << PUCAN_TFAST_TSGEG2_BITS),
	.sjw_max = (1 << PUCAN_TFAST_SJW_BITS),
	.brp_min = 1,
	.brp_max = (1 << PUCAN_TFAST_BRP_BITS),
	.brp_inc = 1,
पूर्ण;

अटल काष्ठा peak_canfd_priv *pucan_init_cmd(काष्ठा peak_canfd_priv *priv)
अणु
	priv->cmd_len = 0;
	वापस priv;
पूर्ण

अटल व्योम *pucan_add_cmd(काष्ठा peak_canfd_priv *priv, पूर्णांक cmd_op)
अणु
	काष्ठा pucan_command *cmd;

	अगर (priv->cmd_len + माप(*cmd) > priv->cmd_maxlen)
		वापस शून्य;

	cmd = priv->cmd_buffer + priv->cmd_len;

	/* reset all unused bit to शेष */
	स_रखो(cmd, 0, माप(*cmd));

	cmd->opcode_channel = pucan_cmd_opcode_channel(priv->index, cmd_op);
	priv->cmd_len += माप(*cmd);

	वापस cmd;
पूर्ण

अटल पूर्णांक pucan_ग_लिखो_cmd(काष्ठा peak_canfd_priv *priv)
अणु
	पूर्णांक err;

	अगर (priv->pre_cmd) अणु
		err = priv->pre_cmd(priv);
		अगर (err)
			वापस err;
	पूर्ण

	err = priv->ग_लिखो_cmd(priv);
	अगर (err)
		वापस err;

	अगर (priv->post_cmd)
		err = priv->post_cmd(priv);

	वापस err;
पूर्ण

/* uCAN commands पूर्णांकerface functions */
अटल पूर्णांक pucan_set_reset_mode(काष्ठा peak_canfd_priv *priv)
अणु
	pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_RESET_MODE);
	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_set_normal_mode(काष्ठा peak_canfd_priv *priv)
अणु
	पूर्णांक err;

	pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_NORMAL_MODE);
	err = pucan_ग_लिखो_cmd(priv);
	अगर (!err)
		priv->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस err;
पूर्ण

अटल पूर्णांक pucan_set_listen_only_mode(काष्ठा peak_canfd_priv *priv)
अणु
	पूर्णांक err;

	pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_LISTEN_ONLY_MODE);
	err = pucan_ग_लिखो_cmd(priv);
	अगर (!err)
		priv->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस err;
पूर्ण

अटल पूर्णांक pucan_set_timing_slow(काष्ठा peak_canfd_priv *priv,
				 स्थिर काष्ठा can_bittiming *pbt)
अणु
	काष्ठा pucan_timing_slow *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_TIMING_SLOW);

	cmd->sjw_t = PUCAN_TSLOW_SJW_T(pbt->sjw - 1,
				       priv->can.ctrlmode &
				       CAN_CTRLMODE_3_SAMPLES);
	cmd->tseg1 = PUCAN_TSLOW_TSEG1(pbt->prop_seg + pbt->phase_seg1 - 1);
	cmd->tseg2 = PUCAN_TSLOW_TSEG2(pbt->phase_seg2 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TSLOW_BRP(pbt->brp - 1));

	cmd->ewl = 96;	/* शेष */

	netdev_dbg(priv->ndev,
		   "nominal: brp=%u tseg1=%u tseg2=%u sjw=%u\n",
		   le16_to_cpu(cmd->brp), cmd->tseg1, cmd->tseg2, cmd->sjw_t);

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_set_timing_fast(काष्ठा peak_canfd_priv *priv,
				 स्थिर काष्ठा can_bittiming *pbt)
अणु
	काष्ठा pucan_timing_fast *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_TIMING_FAST);

	cmd->sjw = PUCAN_TFAST_SJW(pbt->sjw - 1);
	cmd->tseg1 = PUCAN_TFAST_TSEG1(pbt->prop_seg + pbt->phase_seg1 - 1);
	cmd->tseg2 = PUCAN_TFAST_TSEG2(pbt->phase_seg2 - 1);
	cmd->brp = cpu_to_le16(PUCAN_TFAST_BRP(pbt->brp - 1));

	netdev_dbg(priv->ndev,
		   "data: brp=%u tseg1=%u tseg2=%u sjw=%u\n",
		   le16_to_cpu(cmd->brp), cmd->tseg1, cmd->tseg2, cmd->sjw);

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_set_std_filter(काष्ठा peak_canfd_priv *priv, u8 row, u32 mask)
अणु
	काष्ठा pucan_std_filter *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_SET_STD_FILTER);

	/* all the 11-bits CAN ID values are represented by one bit in a
	 * 64 rows array of 32 bits: the upper 6 bits of the CAN ID select the
	 * row जबतक the lowest 5 bits select the bit in that row.
	 *
	 * bit	filter
	 * 1	passed
	 * 0	discarded
	 */

	/* select the row */
	cmd->idx = row;

	/* set/unset bits in the row */
	cmd->mask = cpu_to_le32(mask);

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_tx_पात(काष्ठा peak_canfd_priv *priv, u16 flags)
अणु
	काष्ठा pucan_tx_पात *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_TX_ABORT);

	cmd->flags = cpu_to_le16(flags);

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_clr_err_counters(काष्ठा peak_canfd_priv *priv)
अणु
	काष्ठा pucan_wr_err_cnt *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_WR_ERR_CNT);

	cmd->sel_mask = cpu_to_le16(PUCAN_WRERRCNT_TE | PUCAN_WRERRCNT_RE);
	cmd->tx_counter = 0;
	cmd->rx_counter = 0;

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_set_options(काष्ठा peak_canfd_priv *priv, u16 opt_mask)
अणु
	काष्ठा pucan_options *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_SET_EN_OPTION);

	cmd->options = cpu_to_le16(opt_mask);

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_clr_options(काष्ठा peak_canfd_priv *priv, u16 opt_mask)
अणु
	काष्ठा pucan_options *cmd;

	cmd = pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_CLR_DIS_OPTION);

	cmd->options = cpu_to_le16(opt_mask);

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_setup_rx_barrier(काष्ठा peak_canfd_priv *priv)
अणु
	pucan_add_cmd(pucan_init_cmd(priv), PUCAN_CMD_RX_BARRIER);

	वापस pucan_ग_लिखो_cmd(priv);
पूर्ण

अटल पूर्णांक pucan_netअगर_rx(काष्ठा sk_buff *skb, __le32 ts_low, __le32 ts_high)
अणु
	काष्ठा skb_shared_hwtstamps *hwts = skb_hwtstamps(skb);
	u64 ts_us;

	ts_us = (u64)le32_to_cpu(ts_high) << 32;
	ts_us |= le32_to_cpu(ts_low);

	/* IP core बारtamps are तगs. */
	hwts->hwtstamp = ns_to_kसमय(ts_us * NSEC_PER_USEC);

	वापस netअगर_rx(skb);
पूर्ण

/* handle the reception of one CAN frame */
अटल पूर्णांक pucan_handle_can_rx(काष्ठा peak_canfd_priv *priv,
			       काष्ठा pucan_rx_msg *msg)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा canfd_frame *cf;
	काष्ठा sk_buff *skb;
	स्थिर u16 rx_msg_flags = le16_to_cpu(msg->flags);
	u8 cf_len;

	अगर (rx_msg_flags & PUCAN_MSG_EXT_DATA_LEN)
		cf_len = can_fd_dlc2len(pucan_msg_get_dlc(msg));
	अन्यथा
		cf_len = can_cc_dlc2len(pucan_msg_get_dlc(msg));

	/* अगर this frame is an echo, */
	अगर (rx_msg_flags & PUCAN_MSG_LOOPED_BACK) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->echo_lock, flags);
		can_get_echo_skb(priv->ndev, msg->client, शून्य);

		/* count bytes of the echo instead of skb */
		stats->tx_bytes += cf_len;
		stats->tx_packets++;

		/* restart tx queue (a slot is मुक्त) */
		netअगर_wake_queue(priv->ndev);

		spin_unlock_irqrestore(&priv->echo_lock, flags);

		/* अगर this frame is only an echo, stop here. Otherwise,
		 * जारी to push this application self-received frame पूर्णांकo
		 * its own rx queue.
		 */
		अगर (!(rx_msg_flags & PUCAN_MSG_SELF_RECEIVE))
			वापस 0;
	पूर्ण

	/* otherwise, it should be pushed पूर्णांकo rx fअगरo */
	अगर (rx_msg_flags & PUCAN_MSG_EXT_DATA_LEN) अणु
		/* CANFD frame हाल */
		skb = alloc_canfd_skb(priv->ndev, &cf);
		अगर (!skb)
			वापस -ENOMEM;

		अगर (rx_msg_flags & PUCAN_MSG_BITRATE_SWITCH)
			cf->flags |= CANFD_BRS;

		अगर (rx_msg_flags & PUCAN_MSG_ERROR_STATE_IND)
			cf->flags |= CANFD_ESI;
	पूर्ण अन्यथा अणु
		/* CAN 2.0 frame हाल */
		skb = alloc_can_skb(priv->ndev, (काष्ठा can_frame **)&cf);
		अगर (!skb)
			वापस -ENOMEM;
	पूर्ण

	cf->can_id = le32_to_cpu(msg->can_id);
	cf->len = cf_len;

	अगर (rx_msg_flags & PUCAN_MSG_EXT_ID)
		cf->can_id |= CAN_EFF_FLAG;

	अगर (rx_msg_flags & PUCAN_MSG_RTR)
		cf->can_id |= CAN_RTR_FLAG;
	अन्यथा
		स_नकल(cf->data, msg->d, cf->len);

	stats->rx_bytes += cf->len;
	stats->rx_packets++;

	pucan_netअगर_rx(skb, msg->ts_low, msg->ts_high);

	वापस 0;
पूर्ण

/* handle rx/tx error counters notअगरication */
अटल पूर्णांक pucan_handle_error(काष्ठा peak_canfd_priv *priv,
			      काष्ठा pucan_error_msg *msg)
अणु
	priv->bec.txerr = msg->tx_err_cnt;
	priv->bec.rxerr = msg->rx_err_cnt;

	वापस 0;
पूर्ण

/* handle status notअगरication */
अटल पूर्णांक pucan_handle_status(काष्ठा peak_canfd_priv *priv,
			       काष्ठा pucan_status_msg *msg)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	/* this STATUS is the CNF of the RX_BARRIER: Tx path can be setup */
	अगर (pucan_status_is_rx_barrier(msg)) अणु
		अगर (priv->enable_tx_path) अणु
			पूर्णांक err = priv->enable_tx_path(priv);

			अगर (err)
				वापस err;
		पूर्ण

		/* start network queue (echo_skb array is empty) */
		netअगर_start_queue(ndev);

		वापस 0;
	पूर्ण

	skb = alloc_can_err_skb(ndev, &cf);

	/* test state error bits according to their priority */
	अगर (pucan_status_is_busoff(msg)) अणु
		netdev_dbg(ndev, "Bus-off entry status\n");
		priv->can.state = CAN_STATE_BUS_OFF;
		priv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		अगर (skb)
			cf->can_id |= CAN_ERR_BUSOFF;

	पूर्ण अन्यथा अगर (pucan_status_is_passive(msg)) अणु
		netdev_dbg(ndev, "Error passive status\n");
		priv->can.state = CAN_STATE_ERROR_PASSIVE;
		priv->can.can_stats.error_passive++;
		अगर (skb) अणु
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (priv->bec.txerr > priv->bec.rxerr) ?
					CAN_ERR_CRTL_TX_PASSIVE :
					CAN_ERR_CRTL_RX_PASSIVE;
			cf->data[6] = priv->bec.txerr;
			cf->data[7] = priv->bec.rxerr;
		पूर्ण

	पूर्ण अन्यथा अगर (pucan_status_is_warning(msg)) अणु
		netdev_dbg(ndev, "Error warning status\n");
		priv->can.state = CAN_STATE_ERROR_WARNING;
		priv->can.can_stats.error_warning++;
		अगर (skb) अणु
			cf->can_id |= CAN_ERR_CRTL;
			cf->data[1] = (priv->bec.txerr > priv->bec.rxerr) ?
					CAN_ERR_CRTL_TX_WARNING :
					CAN_ERR_CRTL_RX_WARNING;
			cf->data[6] = priv->bec.txerr;
			cf->data[7] = priv->bec.rxerr;
		पूर्ण

	पूर्ण अन्यथा अगर (priv->can.state != CAN_STATE_ERROR_ACTIVE) अणु
		/* back to ERROR_ACTIVE */
		netdev_dbg(ndev, "Error active status\n");
		can_change_state(ndev, cf, CAN_STATE_ERROR_ACTIVE,
				 CAN_STATE_ERROR_ACTIVE);
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस -ENOMEM;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
	pucan_netअगर_rx(skb, msg->ts_low, msg->ts_high);

	वापस 0;
पूर्ण

/* handle uCAN Rx overflow notअगरication */
अटल पूर्णांक pucan_handle_cache_critical(काष्ठा peak_canfd_priv *priv)
अणु
	काष्ठा net_device_stats *stats = &priv->ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;

	stats->rx_over_errors++;
	stats->rx_errors++;

	skb = alloc_can_err_skb(priv->ndev, &cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस -ENOMEM;
	पूर्ण

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	cf->data[6] = priv->bec.txerr;
	cf->data[7] = priv->bec.rxerr;

	stats->rx_bytes += cf->len;
	stats->rx_packets++;
	netअगर_rx(skb);

	वापस 0;
पूर्ण

/* handle a single uCAN message */
पूर्णांक peak_canfd_handle_msg(काष्ठा peak_canfd_priv *priv,
			  काष्ठा pucan_rx_msg *msg)
अणु
	u16 msg_type = le16_to_cpu(msg->type);
	पूर्णांक msg_size = le16_to_cpu(msg->size);
	पूर्णांक err;

	अगर (!msg_size || !msg_type) अणु
		/* null packet found: end of list */
		जाओ निकास;
	पूर्ण

	चयन (msg_type) अणु
	हाल PUCAN_MSG_CAN_RX:
		err = pucan_handle_can_rx(priv, (काष्ठा pucan_rx_msg *)msg);
		अवरोध;
	हाल PUCAN_MSG_ERROR:
		err = pucan_handle_error(priv, (काष्ठा pucan_error_msg *)msg);
		अवरोध;
	हाल PUCAN_MSG_STATUS:
		err = pucan_handle_status(priv, (काष्ठा pucan_status_msg *)msg);
		अवरोध;
	हाल PUCAN_MSG_CACHE_CRITICAL:
		err = pucan_handle_cache_critical(priv);
		अवरोध;
	शेष:
		err = 0;
	पूर्ण

	अगर (err < 0)
		वापस err;

निकास:
	वापस msg_size;
पूर्ण

/* handle a list of rx_count messages from rx_msg memory address */
पूर्णांक peak_canfd_handle_msgs_list(काष्ठा peak_canfd_priv *priv,
				काष्ठा pucan_rx_msg *msg_list, पूर्णांक msg_count)
अणु
	व्योम *msg_ptr = msg_list;
	पूर्णांक i, msg_size = 0;

	क्रम (i = 0; i < msg_count; i++) अणु
		msg_size = peak_canfd_handle_msg(priv, msg_ptr);

		/* a null packet can be found at the end of a list */
		अगर (msg_size <= 0)
			अवरोध;

		msg_ptr += ALIGN(msg_size, 4);
	पूर्ण

	अगर (msg_size < 0)
		वापस msg_size;

	वापस i;
पूर्ण

अटल पूर्णांक peak_canfd_start(काष्ठा peak_canfd_priv *priv)
अणु
	पूर्णांक err;

	err = pucan_clr_err_counters(priv);
	अगर (err)
		जाओ err_निकास;

	priv->echo_idx = 0;

	priv->bec.txerr = 0;
	priv->bec.rxerr = 0;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		err = pucan_set_listen_only_mode(priv);
	अन्यथा
		err = pucan_set_normal_mode(priv);

err_निकास:
	वापस err;
पूर्ण

अटल व्योम peak_canfd_stop(काष्ठा peak_canfd_priv *priv)
अणु
	पूर्णांक err;

	/* go back to RESET mode */
	err = pucan_set_reset_mode(priv);
	अगर (err) अणु
		netdev_err(priv->ndev, "channel %u reset failed\n",
			   priv->index);
	पूर्ण अन्यथा अणु
		/* पात last Tx (MUST be करोne in RESET mode only!) */
		pucan_tx_पात(priv, PUCAN_TX_ABORT_FLUSH);
	पूर्ण
पूर्ण

अटल पूर्णांक peak_canfd_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	काष्ठा peak_canfd_priv *priv = netdev_priv(ndev);

	चयन (mode) अणु
	हाल CAN_MODE_START:
		peak_canfd_start(priv);
		netअगर_wake_queue(ndev);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक peak_canfd_get_berr_counter(स्थिर काष्ठा net_device *ndev,
				       काष्ठा can_berr_counter *bec)
अणु
	काष्ठा peak_canfd_priv *priv = netdev_priv(ndev);

	*bec = priv->bec;
	वापस 0;
पूर्ण

अटल पूर्णांक peak_canfd_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा peak_canfd_priv *priv = netdev_priv(ndev);
	पूर्णांक i, err = 0;

	err = खोलो_candev(ndev);
	अगर (err) अणु
		netdev_err(ndev, "open_candev() failed, error %d\n", err);
		जाओ err_निकास;
	पूर्ण

	err = pucan_set_reset_mode(priv);
	अगर (err)
		जाओ err_बंद;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO)
			err = pucan_clr_options(priv, PUCAN_OPTION_CANDFDISO);
		अन्यथा
			err = pucan_set_options(priv, PUCAN_OPTION_CANDFDISO);

		अगर (err)
			जाओ err_बंद;
	पूर्ण

	/* set option: get rx/tx error counters */
	err = pucan_set_options(priv, PUCAN_OPTION_ERROR);
	अगर (err)
		जाओ err_बंद;

	/* accept all standard CAN ID */
	क्रम (i = 0; i <= PUCAN_FLTSTD_ROW_IDX_MAX; i++)
		pucan_set_std_filter(priv, i, 0xffffffff);

	err = peak_canfd_start(priv);
	अगर (err)
		जाओ err_बंद;

	/* receiving the RB status says when Tx path is पढ़ोy */
	err = pucan_setup_rx_barrier(priv);
	अगर (!err)
		जाओ err_निकास;

err_बंद:
	बंद_candev(ndev);
err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक peak_canfd_set_bittiming(काष्ठा net_device *ndev)
अणु
	काष्ठा peak_canfd_priv *priv = netdev_priv(ndev);

	वापस pucan_set_timing_slow(priv, &priv->can.bittiming);
पूर्ण

अटल पूर्णांक peak_canfd_set_data_bittiming(काष्ठा net_device *ndev)
अणु
	काष्ठा peak_canfd_priv *priv = netdev_priv(ndev);

	वापस pucan_set_timing_fast(priv, &priv->can.data_bittiming);
पूर्ण

अटल पूर्णांक peak_canfd_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा peak_canfd_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	peak_canfd_stop(priv);
	बंद_candev(ndev);

	वापस 0;
पूर्ण

अटल netdev_tx_t peak_canfd_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *ndev)
अणु
	काष्ठा peak_canfd_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;
	काष्ठा pucan_tx_msg *msg;
	u16 msg_size, msg_flags;
	अचिन्हित दीर्घ flags;
	bool should_stop_tx_queue;
	पूर्णांक room_left;
	u8 len;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	msg_size = ALIGN(माप(*msg) + cf->len, 4);
	msg = priv->alloc_tx_msg(priv, msg_size, &room_left);

	/* should never happen except under bus-off condition and (स्वतः-)restart
	 * mechanism
	 */
	अगर (!msg) अणु
		stats->tx_dropped++;
		netअगर_stop_queue(ndev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	msg->size = cpu_to_le16(msg_size);
	msg->type = cpu_to_le16(PUCAN_MSG_CAN_TX);
	msg_flags = 0;

	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		msg_flags |= PUCAN_MSG_EXT_ID;
		msg->can_id = cpu_to_le32(cf->can_id & CAN_EFF_MASK);
	पूर्ण अन्यथा अणु
		msg->can_id = cpu_to_le32(cf->can_id & CAN_SFF_MASK);
	पूर्ण

	अगर (can_is_canfd_skb(skb)) अणु
		/* CAN FD frame क्रमmat */
		len = can_fd_len2dlc(cf->len);

		msg_flags |= PUCAN_MSG_EXT_DATA_LEN;

		अगर (cf->flags & CANFD_BRS)
			msg_flags |= PUCAN_MSG_BITRATE_SWITCH;

		अगर (cf->flags & CANFD_ESI)
			msg_flags |= PUCAN_MSG_ERROR_STATE_IND;
	पूर्ण अन्यथा अणु
		/* CAN 2.0 frame क्रमmat */
		len = cf->len;

		अगर (cf->can_id & CAN_RTR_FLAG)
			msg_flags |= PUCAN_MSG_RTR;
	पूर्ण

	/* always ask loopback क्रम echo management */
	msg_flags |= PUCAN_MSG_LOOPED_BACK;

	/* set driver specअगरic bit to dअगरferentiate with application loopback */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		msg_flags |= PUCAN_MSG_SELF_RECEIVE;

	msg->flags = cpu_to_le16(msg_flags);
	msg->channel_dlc = PUCAN_MSG_CHANNEL_DLC(priv->index, len);
	स_नकल(msg->d, cf->data, cf->len);

	/* काष्ठा msg client field is used as an index in the echo skbs ring */
	msg->client = priv->echo_idx;

	spin_lock_irqsave(&priv->echo_lock, flags);

	/* prepare and save echo skb in पूर्णांकernal slot */
	can_put_echo_skb(skb, ndev, priv->echo_idx, 0);

	/* move echo index to the next slot */
	priv->echo_idx = (priv->echo_idx + 1) % priv->can.echo_skb_max;

	/* अगर next slot is not मुक्त, stop network queue (no slot मुक्त in echo
	 * skb ring means that the controller did not ग_लिखो these frames on
	 * the bus: no need to जारी).
	 */
	should_stop_tx_queue = !!(priv->can.echo_skb[priv->echo_idx]);

	/* stop network tx queue अगर not enough room to save one more msg too */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_FD)
		should_stop_tx_queue |= (room_left <
					(माप(*msg) + CANFD_MAX_DLEN));
	अन्यथा
		should_stop_tx_queue |= (room_left <
					(माप(*msg) + CAN_MAX_DLEN));

	अगर (should_stop_tx_queue)
		netअगर_stop_queue(ndev);

	spin_unlock_irqrestore(&priv->echo_lock, flags);

	/* ग_लिखो the skb on the पूर्णांकerface */
	priv->ग_लिखो_tx_msg(priv, msg);

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops peak_canfd_netdev_ops = अणु
	.nकरो_खोलो = peak_canfd_खोलो,
	.nकरो_stop = peak_canfd_बंद,
	.nकरो_start_xmit = peak_canfd_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

काष्ठा net_device *alloc_peak_canfd_dev(पूर्णांक माप_priv, पूर्णांक index,
					पूर्णांक echo_skb_max)
अणु
	काष्ठा net_device *ndev;
	काष्ठा peak_canfd_priv *priv;

	/* we DO support local echo */
	अगर (echo_skb_max < 0)
		echo_skb_max = PCANFD_ECHO_SKB_MAX;

	/* allocate the candev object */
	ndev = alloc_candev(माप_priv, echo_skb_max);
	अगर (!ndev)
		वापस शून्य;

	priv = netdev_priv(ndev);

	/* complete now socket-can initialization side */
	priv->can.state = CAN_STATE_STOPPED;
	priv->can.bittiming_स्थिर = &peak_canfd_nominal_स्थिर;
	priv->can.data_bittiming_स्थिर = &peak_canfd_data_स्थिर;

	priv->can.करो_set_mode = peak_canfd_set_mode;
	priv->can.करो_get_berr_counter = peak_canfd_get_berr_counter;
	priv->can.करो_set_bittiming = peak_canfd_set_bittiming;
	priv->can.करो_set_data_bittiming = peak_canfd_set_data_bittiming;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
				       CAN_CTRLMODE_LISTENONLY |
				       CAN_CTRLMODE_3_SAMPLES |
				       CAN_CTRLMODE_FD |
				       CAN_CTRLMODE_FD_NON_ISO |
				       CAN_CTRLMODE_BERR_REPORTING;

	priv->ndev = ndev;
	priv->index = index;
	priv->cmd_len = 0;
	spin_lock_init(&priv->echo_lock);

	ndev->flags |= IFF_ECHO;
	ndev->netdev_ops = &peak_canfd_netdev_ops;
	ndev->dev_id = index;

	वापस ndev;
पूर्ण
