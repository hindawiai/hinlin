<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_ENDPOINT_H_
#घोषणा _IPA_ENDPOINT_H_

#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_ether.h>

#समावेश "gsi.h"
#समावेश "ipa_reg.h"

काष्ठा net_device;
काष्ठा sk_buff;

काष्ठा ipa;
काष्ठा ipa_gsi_endpoपूर्णांक_data;

/* Non-zero granularity of counter used to implement aggregation समयout */
#घोषणा IPA_AGGR_GRANULARITY		500	/* microseconds */

#घोषणा IPA_MTU			ETH_DATA_LEN

क्रमागत ipa_endpoपूर्णांक_name अणु
	IPA_ENDPOINT_AP_COMMAND_TX,
	IPA_ENDPOINT_AP_LAN_RX,
	IPA_ENDPOINT_AP_MODEM_TX,
	IPA_ENDPOINT_AP_MODEM_RX,
	IPA_ENDPOINT_MODEM_COMMAND_TX,
	IPA_ENDPOINT_MODEM_LAN_TX,
	IPA_ENDPOINT_MODEM_LAN_RX,
	IPA_ENDPOINT_MODEM_AP_TX,
	IPA_ENDPOINT_MODEM_AP_RX,
	IPA_ENDPOINT_MODEM_DL_NLO_TX,
	IPA_ENDPOINT_COUNT,	/* Number of names (not an index) */
पूर्ण;

#घोषणा IPA_ENDPOपूर्णांक_उच्च		32	/* Max supported by driver */

/**
 * काष्ठा ipa_endpoपूर्णांक - IPA endpoपूर्णांक inक्रमmation
 * @ipa:		IPA poपूर्णांकer
 * @ee_id:		Execution environmnent endpoपूर्णांक is associated with
 * @channel_id:		GSI channel used by the endpoपूर्णांक
 * @endpoपूर्णांक_id:	IPA endpoपूर्णांक number
 * @toward_ipa:		Endpoपूर्णांक direction (true = TX, false = RX)
 * @data:		Endpoपूर्णांक configuration data
 * @trans_tre_max:	Maximum number of TRE descriptors per transaction
 * @evt_ring_id:	GSI event ring used by the endpoपूर्णांक
 * @netdev:		Network device poपूर्णांकer, अगर endpoपूर्णांक uses one
 * @replenish_enabled:	Whether receive buffer replenishing is enabled
 * @replenish_पढ़ोy:	Number of replenish transactions without करोorbell
 * @replenish_saved:	Replenish requests held जबतक disabled
 * @replenish_backlog:	Number of buffers needed to fill hardware queue
 * @replenish_work:	Work item used क्रम repeated replenish failures
 */
काष्ठा ipa_endpoपूर्णांक अणु
	काष्ठा ipa *ipa;
	क्रमागत gsi_ee_id ee_id;
	u32 channel_id;
	u32 endpoपूर्णांक_id;
	bool toward_ipa;
	स्थिर काष्ठा ipa_endpoपूर्णांक_config_data *data;

	u32 trans_tre_max;
	u32 evt_ring_id;

	/* Net device this endpoपूर्णांक is associated with, अगर any */
	काष्ठा net_device *netdev;

	/* Receive buffer replenishing क्रम RX endpoपूर्णांकs */
	bool replenish_enabled;
	u32 replenish_पढ़ोy;
	atomic_t replenish_saved;
	atomic_t replenish_backlog;
	काष्ठा delayed_work replenish_work;		/* global wq */
पूर्ण;

व्योम ipa_endpoपूर्णांक_modem_hol_block_clear_all(काष्ठा ipa *ipa);

व्योम ipa_endpoपूर्णांक_modem_छोड़ो_all(काष्ठा ipa *ipa, bool enable);

पूर्णांक ipa_endpoपूर्णांक_modem_exception_reset_all(काष्ठा ipa *ipa);

पूर्णांक ipa_endpoपूर्णांक_skb_tx(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक, काष्ठा sk_buff *skb);

पूर्णांक ipa_endpoपूर्णांक_enable_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक);
व्योम ipa_endpoपूर्णांक_disable_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक);

व्योम ipa_endpoपूर्णांक_suspend_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक);
व्योम ipa_endpoपूर्णांक_resume_one(काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक);

व्योम ipa_endpoपूर्णांक_suspend(काष्ठा ipa *ipa);
व्योम ipa_endpoपूर्णांक_resume(काष्ठा ipa *ipa);

व्योम ipa_endpoपूर्णांक_setup(काष्ठा ipa *ipa);
व्योम ipa_endpoपूर्णांक_tearकरोwn(काष्ठा ipa *ipa);

पूर्णांक ipa_endpoपूर्णांक_config(काष्ठा ipa *ipa);
व्योम ipa_endpoपूर्णांक_deconfig(काष्ठा ipa *ipa);

व्योम ipa_endpoपूर्णांक_शेष_route_set(काष्ठा ipa *ipa, u32 endpoपूर्णांक_id);
व्योम ipa_endpoपूर्णांक_शेष_route_clear(काष्ठा ipa *ipa);

u32 ipa_endpoपूर्णांक_init(काष्ठा ipa *ipa, u32 count,
		      स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data);
व्योम ipa_endpoपूर्णांक_निकास(काष्ठा ipa *ipa);

व्योम ipa_endpoपूर्णांक_trans_complete(काष्ठा ipa_endpoपूर्णांक *ipa,
				 काष्ठा gsi_trans *trans);
व्योम ipa_endpoपूर्णांक_trans_release(काष्ठा ipa_endpoपूर्णांक *ipa,
				काष्ठा gsi_trans *trans);

#पूर्ण_अगर /* _IPA_ENDPOINT_H_ */
