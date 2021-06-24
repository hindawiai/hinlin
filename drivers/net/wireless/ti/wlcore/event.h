<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __EVENT_H__
#घोषणा __EVENT_H__

/*
 * Mbox events
 *
 * The event mechanism is based on a pair of event buffers (buffers A and
 * B) at fixed locations in the target's memory. The host processes one
 * buffer जबतक the other buffer जारीs to collect events. If the host
 * is not processing events, an पूर्णांकerrupt is issued to संकेत that a buffer
 * is पढ़ोy. Once the host is करोne with processing events from one buffer,
 * it संकेतs the target (with an ACK पूर्णांकerrupt) that the event buffer is
 * मुक्त.
 */

क्रमागत अणु
	RSSI_SNR_TRIGGER_0_EVENT_ID              = BIT(0),
	RSSI_SNR_TRIGGER_1_EVENT_ID              = BIT(1),
	RSSI_SNR_TRIGGER_2_EVENT_ID              = BIT(2),
	RSSI_SNR_TRIGGER_3_EVENT_ID              = BIT(3),
	RSSI_SNR_TRIGGER_4_EVENT_ID              = BIT(4),
	RSSI_SNR_TRIGGER_5_EVENT_ID              = BIT(5),
	RSSI_SNR_TRIGGER_6_EVENT_ID              = BIT(6),
	RSSI_SNR_TRIGGER_7_EVENT_ID              = BIT(7),

	EVENT_MBOX_ALL_EVENT_ID			 = 0x7fffffff,
पूर्ण;

/* events the driver might want to रुको क्रम */
क्रमागत wlcore_रुको_event अणु
	WLCORE_EVENT_ROLE_STOP_COMPLETE,
	WLCORE_EVENT_PEER_REMOVE_COMPLETE,
	WLCORE_EVENT_DFS_CONFIG_COMPLETE
पूर्ण;

क्रमागत अणु
	EVENT_ENTER_POWER_SAVE_FAIL = 0,
	EVENT_ENTER_POWER_SAVE_SUCCESS,
पूर्ण;

#घोषणा NUM_OF_RSSI_SNR_TRIGGERS 8

काष्ठा fw_logger_inक्रमmation अणु
	__le32 max_buff_size;
	__le32 actual_buff_size;
	__le32 num_trace_drop;
	__le32 buff_पढ़ो_ptr;
	__le32 buff_ग_लिखो_ptr;
पूर्ण __packed;

काष्ठा wl1271;

पूर्णांक wl1271_event_unmask(काष्ठा wl1271 *wl);
पूर्णांक wl1271_event_handle(काष्ठा wl1271 *wl, u8 mbox);

व्योम wlcore_event_soft_gemini_sense(काष्ठा wl1271 *wl, u8 enable);
व्योम wlcore_event_sched_scan_completed(काष्ठा wl1271 *wl,
				       u8 status);
व्योम wlcore_event_ba_rx_स्थिरraपूर्णांक(काष्ठा wl1271 *wl,
				   अचिन्हित दीर्घ roles_biपंचांगap,
				   अचिन्हित दीर्घ allowed_biपंचांगap);
व्योम wlcore_event_channel_चयन(काष्ठा wl1271 *wl,
				 अचिन्हित दीर्घ roles_biपंचांगap,
				 bool success);
व्योम wlcore_event_beacon_loss(काष्ठा wl1271 *wl, अचिन्हित दीर्घ roles_biपंचांगap);
व्योम wlcore_event_dummy_packet(काष्ठा wl1271 *wl);
व्योम wlcore_event_max_tx_failure(काष्ठा wl1271 *wl, अचिन्हित दीर्घ sta_biपंचांगap);
व्योम wlcore_event_inactive_sta(काष्ठा wl1271 *wl, अचिन्हित दीर्घ sta_biपंचांगap);
व्योम wlcore_event_roc_complete(काष्ठा wl1271 *wl);
व्योम wlcore_event_rssi_trigger(काष्ठा wl1271 *wl, s8 *metric_arr);
पूर्णांक  wlcore_event_fw_logger(काष्ठा wl1271 *wl);
#पूर्ण_अगर
