<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2012 Texas Instruments. All rights reserved.
 */

#अगर_अघोषित __WL12XX_EVENT_H__
#घोषणा __WL12XX_EVENT_H__

#समावेश "../wlcore/wlcore.h"

क्रमागत अणु
	MEASUREMENT_START_EVENT_ID		 = BIT(8),
	MEASUREMENT_COMPLETE_EVENT_ID		 = BIT(9),
	SCAN_COMPLETE_EVENT_ID			 = BIT(10),
	WFD_DISCOVERY_COMPLETE_EVENT_ID		 = BIT(11),
	AP_DISCOVERY_COMPLETE_EVENT_ID		 = BIT(12),
	RESERVED1			         = BIT(13),
	PSPOLL_DELIVERY_FAILURE_EVENT_ID	 = BIT(14),
	ROLE_STOP_COMPLETE_EVENT_ID		 = BIT(15),
	RADAR_DETECTED_EVENT_ID                  = BIT(16),
	CHANNEL_SWITCH_COMPLETE_EVENT_ID	 = BIT(17),
	BSS_LOSE_EVENT_ID			 = BIT(18),
	REGAINED_BSS_EVENT_ID			 = BIT(19),
	MAX_TX_RETRY_EVENT_ID			 = BIT(20),
	DUMMY_PACKET_EVENT_ID			 = BIT(21),
	SOFT_GEMINI_SENSE_EVENT_ID		 = BIT(22),
	CHANGE_AUTO_MODE_TIMEOUT_EVENT_ID	 = BIT(23),
	SOFT_GEMINI_AVALANCHE_EVENT_ID		 = BIT(24),
	PLT_RX_CALIBRATION_COMPLETE_EVENT_ID	 = BIT(25),
	INACTIVE_STA_EVENT_ID			 = BIT(26),
	PEER_REMOVE_COMPLETE_EVENT_ID		 = BIT(27),
	PERIODIC_SCAN_COMPLETE_EVENT_ID		 = BIT(28),
	PERIODIC_SCAN_REPORT_EVENT_ID		 = BIT(29),
	BA_SESSION_RX_CONSTRAINT_EVENT_ID	 = BIT(30),
	REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID	 = BIT(31),
पूर्ण;

काष्ठा wl12xx_event_mailbox अणु
	__le32 events_vector;
	__le32 events_mask;
	__le32 reserved_1;
	__le32 reserved_2;

	u8 number_of_scan_results;
	u8 scan_tag;
	u8 completed_scan_status;
	u8 reserved_3;

	u8 soft_gemini_sense_info;
	u8 soft_gemini_protective_info;
	s8 rssi_snr_trigger_metric[NUM_OF_RSSI_SNR_TRIGGERS];
	u8 change_स्वतः_mode_समयout;
	u8 scheduled_scan_status;
	u8 reserved4;
	/* tuned channel (roc) */
	u8 roc_channel;

	__le16 hlid_हटाओd_biपंचांगap;

	/* biपंचांगap of aged stations (by HLID) */
	__le16 sta_aging_status;

	/* biपंचांगap of stations (by HLID) which exceeded max tx retries */
	__le16 sta_tx_retry_exceeded;

	/* discovery completed results */
	u8 discovery_tag;
	u8 number_of_preq_results;
	u8 number_of_prsp_results;
	u8 reserved_5;

	/* rx ba स्थिरraपूर्णांक */
	u8 role_id; /* 0xFF means any role. */
	u8 rx_ba_allowed;
	u8 reserved_6[2];

	/* Channel चयन results */

	u8 channel_चयन_role_id;
	u8 channel_चयन_status;
	u8 reserved_7[2];

	u8 ps_poll_delivery_failure_role_ids;
	u8 stopped_role_ids;
	u8 started_role_ids;

	u8 reserved_8[9];
पूर्ण __packed;

पूर्णांक wl12xx_रुको_क्रम_event(काष्ठा wl1271 *wl, क्रमागत wlcore_रुको_event event,
			  bool *समयout);
पूर्णांक wl12xx_process_mailbox_events(काष्ठा wl1271 *wl);

#पूर्ण_अगर

