<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 */

#अगर_अघोषित EFX_PTP_H
#घोषणा EFX_PTP_H

#समावेश <linux/net_tstamp.h>
#समावेश "net_driver.h"

काष्ठा ethtool_ts_info;
पूर्णांक efx_ptp_probe(काष्ठा efx_nic *efx, काष्ठा efx_channel *channel);
व्योम efx_ptp_defer_probe_with_channel(काष्ठा efx_nic *efx);
काष्ठा efx_channel *efx_ptp_channel(काष्ठा efx_nic *efx);
व्योम efx_ptp_हटाओ(काष्ठा efx_nic *efx);
पूर्णांक efx_ptp_set_ts_config(काष्ठा efx_nic *efx, काष्ठा अगरreq *अगरr);
पूर्णांक efx_ptp_get_ts_config(काष्ठा efx_nic *efx, काष्ठा अगरreq *अगरr);
व्योम efx_ptp_get_ts_info(काष्ठा efx_nic *efx, काष्ठा ethtool_ts_info *ts_info);
bool efx_ptp_is_ptp_tx(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb);
पूर्णांक efx_ptp_get_mode(काष्ठा efx_nic *efx);
पूर्णांक efx_ptp_change_mode(काष्ठा efx_nic *efx, bool enable_wanted,
			अचिन्हित पूर्णांक new_mode);
पूर्णांक efx_ptp_tx(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb);
व्योम efx_ptp_event(काष्ठा efx_nic *efx, efx_qword_t *ev);
माप_प्रकार efx_ptp_describe_stats(काष्ठा efx_nic *efx, u8 *strings);
माप_प्रकार efx_ptp_update_stats(काष्ठा efx_nic *efx, u64 *stats);
व्योम efx_समय_sync_event(काष्ठा efx_channel *channel, efx_qword_t *ev);
व्योम __efx_rx_skb_attach_बारtamp(काष्ठा efx_channel *channel,
				   काष्ठा sk_buff *skb);
अटल अंतरभूत व्योम efx_rx_skb_attach_बारtamp(काष्ठा efx_channel *channel,
					       काष्ठा sk_buff *skb)
अणु
	अगर (channel->sync_events_state == SYNC_EVENTS_VALID)
		__efx_rx_skb_attach_बारtamp(channel, skb);
पूर्ण
व्योम efx_ptp_start_datapath(काष्ठा efx_nic *efx);
व्योम efx_ptp_stop_datapath(काष्ठा efx_nic *efx);
bool efx_ptp_use_mac_tx_बारtamps(काष्ठा efx_nic *efx);
kसमय_प्रकार efx_ptp_nic_to_kernel_समय(काष्ठा efx_tx_queue *tx_queue);

#पूर्ण_अगर /* EFX_PTP_H */
