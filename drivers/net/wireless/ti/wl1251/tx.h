<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1251
 *
 * Copyright (c) 1998-2007 Texas Instruments Incorporated
 * Copyright (C) 2008 Nokia Corporation
 */

#अगर_अघोषित __WL1251_TX_H__
#घोषणा __WL1251_TX_H__

#समावेश <linux/bitops.h>
#समावेश "acx.h"

/*
 *
 * TX PATH
 *
 * The Tx path uses a द्विगुन buffer and a tx_control काष्ठाure, each located
 * at a fixed address in the device's memory. On startup, the host retrieves
 * the poपूर्णांकers to these addresses. A द्विगुन buffer allows क्रम continuous data
 * flow towards the device. The host keeps track of which buffer is available
 * and alternates between these two buffers on a per packet basis.
 *
 * The size of each of the two buffers is large enough to hold the दीर्घest
 * 802.3 packet - maximum size Ethernet packet + header + descriptor.
 * TX complete indication will be received a-synchronously in a TX करोne cyclic
 * buffer which is composed of 16 tx_result descriptors काष्ठाures and is used
 * in a cyclic manner.
 *
 * The TX (HOST) procedure is as follows:
 * 1. Read the Tx path status, that will give the data_out_count.
 * 2. जाओ 1, अगर not possible.
 *    i.e. अगर data_in_count - data_out_count >= HwBuffer size (2 क्रम द्विगुन
 *    buffer).
 * 3. Copy the packet (preceded by द्विगुन_buffer_desc), अगर possible.
 *    i.e. अगर data_in_count - data_out_count < HwBuffer size (2 क्रम द्विगुन
 *    buffer).
 * 4. increment data_in_count.
 * 5. Inक्रमm the firmware by generating a firmware पूर्णांकernal पूर्णांकerrupt.
 * 6. FW will increment data_out_count after it पढ़ोs the buffer.
 *
 * The TX Complete procedure:
 * 1. To get a TX complete indication the host enables the tx_complete flag in
 *    the TX descriptor Structure.
 * 2. For each packet with a Tx Complete field set, the firmware adds the
 *    transmit results to the cyclic buffer (txDoneRing) and sets both करोne_1
 *    and करोne_2 to 1 to indicate driver ownership.
 * 3. The firmware sends a Tx Complete पूर्णांकerrupt to the host to trigger the
 *    host to process the new data. Note: पूर्णांकerrupt will be send per packet अगर
 *    TX complete indication was requested in tx_control or per crossing
 *    aggregation threshold.
 * 4. After receiving the Tx Complete पूर्णांकerrupt, the host पढ़ोs the
 *    TxDescriptorDone inक्रमmation in a cyclic manner and clears both करोne_1
 *    and करोne_2 fields.
 *
 */

#घोषणा TX_COMPLETE_REQUIRED_BIT	0x80
#घोषणा TX_STATUS_DATA_OUT_COUNT_MASK   0xf

#घोषणा WL1251_TX_ALIGN_TO 4
#घोषणा WL1251_TX_ALIGN(len) (((len) + WL1251_TX_ALIGN_TO - 1) & \
			     ~(WL1251_TX_ALIGN_TO - 1))
#घोषणा WL1251_TKIP_IV_SPACE 4

काष्ठा tx_control अणु
	/* Rate Policy (class) index */
	अचिन्हित rate_policy:3;

	/* When set, no ack policy is expected */
	अचिन्हित ack_policy:1;

	/*
	 * Packet type:
	 * 0 -> 802.11
	 * 1 -> 802.3
	 * 2 -> IP
	 * 3 -> raw codec
	 */
	अचिन्हित packet_type:2;

	/* If set, this is a QoS-Null or QoS-Data frame */
	अचिन्हित qos:1;

	/*
	 * If set, the target triggers the tx complete INT
	 * upon frame sending completion.
	 */
	अचिन्हित tx_complete:1;

	/* 2 bytes padding beक्रमe packet header */
	अचिन्हित xfer_pad:1;

	अचिन्हित reserved:7;
पूर्ण __packed;


काष्ठा tx_द्विगुन_buffer_desc अणु
	/* Length of payload, including headers. */
	__le16 length;

	/*
	 * A bit mask that specअगरies the initial rate to be used
	 * Possible values are:
	 * 0x0001 - 1Mbits
	 * 0x0002 - 2Mbits
	 * 0x0004 - 5.5Mbits
	 * 0x0008 - 6Mbits
	 * 0x0010 - 9Mbits
	 * 0x0020 - 11Mbits
	 * 0x0040 - 12Mbits
	 * 0x0080 - 18Mbits
	 * 0x0100 - 22Mbits
	 * 0x0200 - 24Mbits
	 * 0x0400 - 36Mbits
	 * 0x0800 - 48Mbits
	 * 0x1000 - 54Mbits
	 */
	__le16 rate;

	/* Time in us that a packet can spend in the target */
	__le32 expiry_समय;

	/* index of the TX queue used क्रम this packet */
	u8 xmit_queue;

	/* Used to identअगरy a packet */
	u8 id;

	काष्ठा tx_control control;

	/*
	 * The FW should cut the packet पूर्णांकo fragments
	 * of this size.
	 */
	__le16 frag_threshold;

	/* Numbers of HW queue blocks to be allocated */
	u8 num_mem_blocks;

	u8 reserved;
पूर्ण __packed;

क्रमागत अणु
	TX_SUCCESS              = 0,
	TX_DMA_ERROR            = BIT(7),
	TX_DISABLED             = BIT(6),
	TX_RETRY_EXCEEDED       = BIT(5),
	TX_TIMEOUT              = BIT(4),
	TX_KEY_NOT_FOUND        = BIT(3),
	TX_ENCRYPT_FAIL         = BIT(2),
	TX_UNAVAILABLE_PRIORITY = BIT(1),
पूर्ण;

काष्ठा tx_result अणु
	/*
	 * Ownership synchronization between the host and
	 * the firmware. If करोne_1 and करोne_2 are cleared,
	 * owned by the FW (no info पढ़ोy).
	 */
	u8 करोne_1;

	/* same as द्विगुन_buffer_desc->id */
	u8 id;

	/*
	 * Total air access duration consumed by this
	 * packet, including all retries and overheads.
	 */
	u16 medium_usage;

	/* Total media delay (from 1st EDCA AIFS counter until TX Complete). */
	u32 medium_delay;

	/* Time between host xfer and tx complete */
	u32 fw_hnadling_समय;

	/* The LS-byte of the last TKIP sequence number. */
	u8 lsb_seq_num;

	/* Retry count */
	u8 ack_failures;

	/* At which rate we got a ACK */
	u16 rate;

	u16 reserved;

	/* TX_* */
	u8 status;

	/* See करोne_1 */
	u8 करोne_2;
पूर्ण __packed;

अटल अंतरभूत पूर्णांक wl1251_tx_get_queue(पूर्णांक queue)
अणु
	चयन (queue) अणु
	हाल 0:
		वापस QOS_AC_VO;
	हाल 1:
		वापस QOS_AC_VI;
	हाल 2:
		वापस QOS_AC_BE;
	हाल 3:
		वापस QOS_AC_BK;
	शेष:
		वापस QOS_AC_BE;
	पूर्ण
पूर्ण

व्योम wl1251_tx_work(काष्ठा work_काष्ठा *work);
व्योम wl1251_tx_complete(काष्ठा wl1251 *wl);
व्योम wl1251_tx_flush(काष्ठा wl1251 *wl);

#पूर्ण_अगर
