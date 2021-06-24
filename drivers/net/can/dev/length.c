<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2012, 2020 Oliver Hartkopp <socketcan@hartkopp.net>
 */

#समावेश <linux/can/dev.h>

/* CAN DLC to real data length conversion helpers */

अटल स्थिर u8 dlc2len[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 12, 16, 20, 24, 32, 48, 64
पूर्ण;

/* get data length from raw data length code (DLC) */
u8 can_fd_dlc2len(u8 dlc)
अणु
	वापस dlc2len[dlc & 0x0F];
पूर्ण
EXPORT_SYMBOL_GPL(can_fd_dlc2len);

अटल स्थिर u8 len2dlc[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7, 8,	/* 0 - 8 */
	9, 9, 9, 9,			/* 9 - 12 */
	10, 10, 10, 10,			/* 13 - 16 */
	11, 11, 11, 11,			/* 17 - 20 */
	12, 12, 12, 12,			/* 21 - 24 */
	13, 13, 13, 13, 13, 13, 13, 13,	/* 25 - 32 */
	14, 14, 14, 14, 14, 14, 14, 14,	/* 33 - 40 */
	14, 14, 14, 14, 14, 14, 14, 14,	/* 41 - 48 */
	15, 15, 15, 15, 15, 15, 15, 15,	/* 49 - 56 */
	15, 15, 15, 15, 15, 15, 15, 15	/* 57 - 64 */
पूर्ण;

/* map the sanitized data length to an appropriate data length code */
u8 can_fd_len2dlc(u8 len)
अणु
	/* check क्रम length mapping table size at build समय */
	BUILD_BUG_ON(ARRAY_SIZE(len2dlc) != CANFD_MAX_DLEN + 1);

	अगर (unlikely(len > CANFD_MAX_DLEN))
		वापस CANFD_MAX_DLC;

	वापस len2dlc[len];
पूर्ण
EXPORT_SYMBOL_GPL(can_fd_len2dlc);

/**
 * can_skb_get_frame_len() - Calculate the CAN Frame length in bytes
 * 	of a given skb.
 * @skb: socket buffer of a CAN message.
 *
 * Do a rough calculation: bit stuffing is ignored and length in bits
 * is rounded up to a length in bytes.
 *
 * Rationale: this function is to be used क्रम the BQL functions
 * (netdev_sent_queue() and netdev_completed_queue()) which expect a
 * value in bytes. Just using skb->len is insufficient because it will
 * वापस the स्थिरant value of CAN(FD)_MTU. Doing the bit stuffing
 * calculation would be too expensive in term of computing resources
 * क्रम no noticeable gain.
 *
 * Remarks: The payload of CAN FD frames with BRS flag are sent at a
 * dअगरferent bitrate. Currently, the can-utils canbusload tool करोes
 * not support CAN-FD yet and so we could not run any benchmark to
 * measure the impact. There might be possible improvement here.
 *
 * Return: length in bytes.
 */
अचिन्हित पूर्णांक can_skb_get_frame_len(स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा canfd_frame *cf = (स्थिर काष्ठा canfd_frame *)skb->data;
	u8 len;

	अगर (can_is_canfd_skb(skb))
		len = canfd_sanitize_len(cf->len);
	अन्यथा अगर (cf->can_id & CAN_RTR_FLAG)
		len = 0;
	अन्यथा
		len = cf->len;

	अगर (can_is_canfd_skb(skb)) अणु
		अगर (cf->can_id & CAN_EFF_FLAG)
			len += CANFD_FRAME_OVERHEAD_EFF;
		अन्यथा
			len += CANFD_FRAME_OVERHEAD_SFF;
	पूर्ण अन्यथा अणु
		अगर (cf->can_id & CAN_EFF_FLAG)
			len += CAN_FRAME_OVERHEAD_EFF;
		अन्यथा
			len += CAN_FRAME_OVERHEAD_SFF;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(can_skb_get_frame_len);
