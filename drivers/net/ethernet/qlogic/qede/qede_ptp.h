<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qede NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QEDE_PTP_H_
#घोषणा _QEDE_PTP_H_

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/समयcounter.h>
#समावेश "qede.h"

व्योम qede_ptp_rx_ts(काष्ठा qede_dev *edev, काष्ठा sk_buff *skb);
व्योम qede_ptp_tx_ts(काष्ठा qede_dev *edev, काष्ठा sk_buff *skb);
पूर्णांक qede_ptp_hw_ts(काष्ठा qede_dev *edev, काष्ठा अगरreq *req);
व्योम qede_ptp_disable(काष्ठा qede_dev *edev);
पूर्णांक qede_ptp_enable(काष्ठा qede_dev *edev);
पूर्णांक qede_ptp_get_ts_info(काष्ठा qede_dev *edev, काष्ठा ethtool_ts_info *ts);

अटल अंतरभूत व्योम qede_ptp_record_rx_ts(काष्ठा qede_dev *edev,
					 जोड़ eth_rx_cqe *cqe,
					 काष्ठा sk_buff *skb)
अणु
	/* Check अगर this packet was बारtamped */
	अगर (unlikely(le16_to_cpu(cqe->fast_path_regular.pars_flags.flags) &
		     (1 << PARSING_AND_ERR_FLAGS_TIMESTAMPRECORDED_SHIFT))) अणु
		अगर (likely(le16_to_cpu(cqe->fast_path_regular.pars_flags.flags)
		    & (1 << PARSING_AND_ERR_FLAGS_TIMESYNCPKT_SHIFT))) अणु
			qede_ptp_rx_ts(edev, skb);
		पूर्ण अन्यथा अणु
			DP_INFO(edev,
				"Timestamp recorded for non PTP packets\n");
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* _QEDE_PTP_H_ */
