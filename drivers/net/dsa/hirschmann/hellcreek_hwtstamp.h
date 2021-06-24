<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * DSA driver क्रम:
 * Hirschmann Hellcreek TSN चयन.
 *
 * Copyright (C) 2019,2020 Hochschule Offenburg
 * Copyright (C) 2019,2020 Linutronix GmbH
 * Authors: Kurt Kanzenbach <kurt@linutronix.de>
 *	    Kamil Alkhouri <kamil.alkhouri@hs-offenburg.de>
 */

#अगर_अघोषित _HELLCREEK_HWTSTAMP_H_
#घोषणा _HELLCREEK_HWTSTAMP_H_

#समावेश <net/dsa.h>
#समावेश "hellcreek.h"

/* Timestamp Register */
#घोषणा PR_TS_RX_P1_STATUS_C	(0x1d * 2)
#घोषणा PR_TS_RX_P1_DATA_C	(0x1e * 2)
#घोषणा PR_TS_TX_P1_STATUS_C	(0x1f * 2)
#घोषणा PR_TS_TX_P1_DATA_C	(0x20 * 2)
#घोषणा PR_TS_RX_P2_STATUS_C	(0x25 * 2)
#घोषणा PR_TS_RX_P2_DATA_C	(0x26 * 2)
#घोषणा PR_TS_TX_P2_STATUS_C	(0x27 * 2)
#घोषणा PR_TS_TX_P2_DATA_C	(0x28 * 2)

#घोषणा PR_TS_STATUS_TS_AVAIL	BIT(2)
#घोषणा PR_TS_STATUS_TS_LOST	BIT(3)

#घोषणा SKB_PTP_TYPE(__skb) (*(अचिन्हित पूर्णांक *)((__skb)->cb))

/* TX_TSTAMP_TIMEOUT: This limits the समय spent polling क्रम a TX
 * बारtamp. When working properly, hardware will produce a बारtamp
 * within 1ms. Software may enounter delays, so the समयout is set
 * accordingly.
 */
#घोषणा TX_TSTAMP_TIMEOUT	msecs_to_jअगरfies(40)

पूर्णांक hellcreek_port_hwtstamp_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr);
पूर्णांक hellcreek_port_hwtstamp_get(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा अगरreq *अगरr);

bool hellcreek_port_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *clone, अचिन्हित पूर्णांक type);
व्योम hellcreek_port_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा sk_buff *skb);

पूर्णांक hellcreek_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  काष्ठा ethtool_ts_info *info);

दीर्घ hellcreek_hwtstamp_work(काष्ठा ptp_घड़ी_info *ptp);

पूर्णांक hellcreek_hwtstamp_setup(काष्ठा hellcreek *chip);
व्योम hellcreek_hwtstamp_मुक्त(काष्ठा hellcreek *chip);

#पूर्ण_अगर /* _HELLCREEK_HWTSTAMP_H_ */
