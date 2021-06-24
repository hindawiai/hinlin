<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 1998-2009 Texas Instruments. All rights reserved.
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __TX_H__
#घोषणा __TX_H__

#घोषणा TX_HW_MGMT_PKT_LIFETIME_TU       2000
#घोषणा TX_HW_AP_MODE_PKT_LIFETIME_TU    8000

#घोषणा TX_HW_ATTR_SAVE_RETRIES          BIT(0)
#घोषणा TX_HW_ATTR_HEADER_PAD            BIT(1)
#घोषणा TX_HW_ATTR_SESSION_COUNTER       (BIT(2) | BIT(3) | BIT(4))
#घोषणा TX_HW_ATTR_RATE_POLICY           (BIT(5) | BIT(6) | BIT(7) | \
					  BIT(8) | BIT(9))
#घोषणा TX_HW_ATTR_LAST_WORD_PAD         (BIT(10) | BIT(11))
#घोषणा TX_HW_ATTR_TX_CMPLT_REQ          BIT(12)
#घोषणा TX_HW_ATTR_TX_DUMMY_REQ          BIT(13)
#घोषणा TX_HW_ATTR_HOST_ENCRYPT          BIT(14)
#घोषणा TX_HW_ATTR_EAPOL_FRAME           BIT(15)

#घोषणा TX_HW_ATTR_OFST_SAVE_RETRIES     0
#घोषणा TX_HW_ATTR_OFST_HEADER_PAD       1
#घोषणा TX_HW_ATTR_OFST_SESSION_COUNTER  2
#घोषणा TX_HW_ATTR_OFST_RATE_POLICY      5
#घोषणा TX_HW_ATTR_OFST_LAST_WORD_PAD    10
#घोषणा TX_HW_ATTR_OFST_TX_CMPLT_REQ     12

#घोषणा TX_HW_RESULT_QUEUE_LEN           16
#घोषणा TX_HW_RESULT_QUEUE_LEN_MASK      0xf

#घोषणा WL1271_TX_ALIGN_TO 4
#घोषणा WL1271_EXTRA_SPACE_TKIP 4
#घोषणा WL1271_EXTRA_SPACE_AES  8
#घोषणा WL1271_EXTRA_SPACE_MAX  8

/* Used क्रम management frames and dummy packets */
#घोषणा WL1271_TID_MGMT 7

/* stop a ROC क्रम pending authentication reply after this समय (ms) */
#घोषणा WLCORE_PEND_AUTH_ROC_TIMEOUT     1000

काष्ठा wl127x_tx_mem अणु
	/*
	 * Number of extra memory blocks to allocate क्रम this packet
	 * in addition to the number of blocks derived from the packet
	 * length.
	 */
	u8 extra_blocks;
	/*
	 * Total number of memory blocks allocated by the host क्रम
	 * this packet. Must be equal or greater than the actual
	 * blocks number allocated by HW.
	 */
	u8 total_mem_blocks;
पूर्ण __packed;

काष्ठा wl128x_tx_mem अणु
	/*
	 * Total number of memory blocks allocated by the host क्रम
	 * this packet.
	 */
	u8 total_mem_blocks;
	/*
	 * Number of extra bytes, at the end of the frame. the host
	 * uses this padding to complete each frame to पूर्णांकeger number
	 * of SDIO blocks.
	 */
	u8 extra_bytes;
पूर्ण __packed;

काष्ठा wl18xx_tx_mem अणु
	/*
	 * Total number of memory blocks allocated by the host क्रम
	 * this packet.
	 */
	u8 total_mem_blocks;

	/*
	 * control bits
	 */
	u8 ctrl;
पूर्ण __packed;

/*
 * On wl128x based devices, when TX packets are aggregated, each packet
 * size must be aligned to the SDIO block size. The maximum block size
 * is bounded by the type of the padded bytes field that is sent to the
 * FW. Currently the type is u8, so the maximum block size is 256 bytes.
 */
#घोषणा WL12XX_BUS_BLOCK_SIZE min(512u,	\
	    (1u << (8 * माप(((काष्ठा wl128x_tx_mem *) 0)->extra_bytes))))

काष्ठा wl1271_tx_hw_descr अणु
	/* Length of packet in words, including descriptor+header+data */
	__le16 length;
	जोड़ अणु
		काष्ठा wl127x_tx_mem wl127x_mem;
		काष्ठा wl128x_tx_mem wl128x_mem;
		काष्ठा wl18xx_tx_mem wl18xx_mem;
	पूर्ण __packed;
	/* Device समय (in us) when the packet arrived to the driver */
	__le32 start_समय;
	/*
	 * Max delay in TUs until transmission. The last device समय the
	 * packet can be transmitted is: start_समय + (1024 * lअगरe_समय)
	 */
	__le16 lअगरe_समय;
	/* Bitwise fields - see TX_ATTR... definitions above. */
	__le16 tx_attr;
	/* Packet identअगरier used also in the Tx-Result. */
	u8 id;
	/* The packet TID value (as User-Priority) */
	u8 tid;
	/* host link ID (HLID) */
	u8 hlid;

	जोड़ अणु
		u8 wl12xx_reserved;

		/*
		 * bit 0   -> 0 = udp, 1 = tcp
		 * bit 1:7 -> IP header offset
		 */
		u8 wl18xx_checksum_data;
	पूर्ण __packed;
पूर्ण __packed;

क्रमागत wl1271_tx_hw_res_status अणु
	TX_SUCCESS          = 0,
	TX_HW_ERROR         = 1,
	TX_DISABLED         = 2,
	TX_RETRY_EXCEEDED   = 3,
	TX_TIMEOUT          = 4,
	TX_KEY_NOT_FOUND    = 5,
	TX_PEER_NOT_FOUND   = 6,
	TX_SESSION_MISMATCH = 7,
	TX_LINK_NOT_VALID   = 8,
पूर्ण;

काष्ठा wl1271_tx_hw_res_descr अणु
	/* Packet Identअगरier - same value used in the Tx descriptor.*/
	u8 id;
	/* The status of the transmission, indicating success or one of
	   several possible reasons क्रम failure. */
	u8 status;
	/* Total air access duration including all retrys and overheads.*/
	__le16 medium_usage;
	/* The समय passed from host xfer to Tx-complete.*/
	__le32 fw_handling_समय;
	/* Total media delay
	   (from 1st EDCA AIFS counter until TX Complete). */
	__le32 medium_delay;
	/* LS-byte of last TKIP seq-num (saved per AC क्रम recovery). */
	u8 tx_security_sequence_number_lsb;
	/* Retry count - number of transmissions without successful ACK.*/
	u8 ack_failures;
	/* The rate that succeeded getting ACK
	   (Valid only अगर status=SUCCESS). */
	u8 rate_class_index;
	/* क्रम 4-byte alignment. */
	u8 spare;
पूर्ण __packed;

काष्ठा wl1271_tx_hw_res_अगर अणु
	__le32 tx_result_fw_counter;
	__le32 tx_result_host_counter;
	काष्ठा wl1271_tx_hw_res_descr tx_results_queue[TX_HW_RESULT_QUEUE_LEN];
पूर्ण __packed;

क्रमागत wlcore_queue_stop_reason अणु
	WLCORE_QUEUE_STOP_REASON_WATERMARK,
	WLCORE_QUEUE_STOP_REASON_FW_RESTART,
	WLCORE_QUEUE_STOP_REASON_FLUSH,
	WLCORE_QUEUE_STOP_REASON_SPARE_BLK, /* 18xx specअगरic */
पूर्ण;

अटल अंतरभूत पूर्णांक wl1271_tx_get_queue(पूर्णांक queue)
अणु
	चयन (queue) अणु
	हाल 0:
		वापस CONF_TX_AC_VO;
	हाल 1:
		वापस CONF_TX_AC_VI;
	हाल 2:
		वापस CONF_TX_AC_BE;
	हाल 3:
		वापस CONF_TX_AC_BK;
	शेष:
		वापस CONF_TX_AC_BE;
	पूर्ण
पूर्ण

अटल अंतरभूत
पूर्णांक wlcore_tx_get_mac80211_queue(काष्ठा wl12xx_vअगर *wlvअगर, पूर्णांक queue)
अणु
	पूर्णांक mac_queue = wlvअगर->hw_queue_base;

	चयन (queue) अणु
	हाल CONF_TX_AC_VO:
		वापस mac_queue + 0;
	हाल CONF_TX_AC_VI:
		वापस mac_queue + 1;
	हाल CONF_TX_AC_BE:
		वापस mac_queue + 2;
	हाल CONF_TX_AC_BK:
		वापस mac_queue + 3;
	शेष:
		वापस mac_queue + 2;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक wl1271_tx_total_queue_count(काष्ठा wl1271 *wl)
अणु
	पूर्णांक i, count = 0;

	क्रम (i = 0; i < NUM_TX_QUEUES; i++)
		count += wl->tx_queue_count[i];

	वापस count;
पूर्ण

व्योम wl1271_tx_work(काष्ठा work_काष्ठा *work);
पूर्णांक wlcore_tx_work_locked(काष्ठा wl1271 *wl);
पूर्णांक wlcore_tx_complete(काष्ठा wl1271 *wl);
व्योम wl12xx_tx_reset_wlvअगर(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर);
व्योम wl12xx_tx_reset(काष्ठा wl1271 *wl);
व्योम wl1271_tx_flush(काष्ठा wl1271 *wl);
u8 wlcore_rate_to_idx(काष्ठा wl1271 *wl, u8 rate, क्रमागत nl80211_band band);
u32 wl1271_tx_enabled_rates_get(काष्ठा wl1271 *wl, u32 rate_set,
				क्रमागत nl80211_band rate_band);
u32 wl1271_tx_min_rate_get(काष्ठा wl1271 *wl, u32 rate_set);
u8 wl12xx_tx_get_hlid(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		      काष्ठा sk_buff *skb, काष्ठा ieee80211_sta *sta);
व्योम wl1271_tx_reset_link_queues(काष्ठा wl1271 *wl, u8 hlid);
व्योम wl1271_handle_tx_low_watermark(काष्ठा wl1271 *wl);
bool wl12xx_is_dummy_packet(काष्ठा wl1271 *wl, काष्ठा sk_buff *skb);
व्योम wl12xx_rearm_rx_streaming(काष्ठा wl1271 *wl, अचिन्हित दीर्घ *active_hlids);
अचिन्हित पूर्णांक wlcore_calc_packet_alignment(काष्ठा wl1271 *wl,
					  अचिन्हित पूर्णांक packet_length);
व्योम wl1271_मुक्त_tx_id(काष्ठा wl1271 *wl, पूर्णांक id);
व्योम wlcore_stop_queue_locked(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			      u8 queue, क्रमागत wlcore_queue_stop_reason reason);
व्योम wlcore_stop_queue(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 queue,
		       क्रमागत wlcore_queue_stop_reason reason);
व्योम wlcore_wake_queue(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 queue,
		       क्रमागत wlcore_queue_stop_reason reason);
व्योम wlcore_stop_queues(काष्ठा wl1271 *wl,
			क्रमागत wlcore_queue_stop_reason reason);
व्योम wlcore_wake_queues(काष्ठा wl1271 *wl,
			क्रमागत wlcore_queue_stop_reason reason);
bool wlcore_is_queue_stopped_by_reason(काष्ठा wl1271 *wl,
				       काष्ठा wl12xx_vअगर *wlvअगर, u8 queue,
				       क्रमागत wlcore_queue_stop_reason reason);
bool
wlcore_is_queue_stopped_by_reason_locked(काष्ठा wl1271 *wl,
					 काष्ठा wl12xx_vअगर *wlvअगर,
					 u8 queue,
					 क्रमागत wlcore_queue_stop_reason reason);
bool wlcore_is_queue_stopped_locked(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				    u8 queue);

/* from मुख्य.c */
व्योम wl1271_मुक्त_sta(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u8 hlid);
व्योम wl12xx_rearm_tx_watchकरोg_locked(काष्ठा wl1271 *wl);

#पूर्ण_अगर
