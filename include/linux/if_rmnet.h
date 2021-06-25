<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (c) 2013-2019, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _LINUX_IF_RMNET_H_
#घोषणा _LINUX_IF_RMNET_H_

काष्ठा rmnet_map_header अणु
	u8 flags;			/* MAP_CMD_FLAG, MAP_PAD_LEN_MASK */
	u8 mux_id;
	__be16 pkt_len;			/* Length of packet, including pad */
पूर्ण  __aligned(1);

/* rmnet_map_header flags field:
 *  PAD_LEN:	number of pad bytes following packet data
 *  CMD:	1 = packet contains a MAP command; 0 = packet contains data
 */
#घोषणा MAP_PAD_LEN_MASK		GENMASK(5, 0)
#घोषणा MAP_CMD_FLAG			BIT(7)

काष्ठा rmnet_map_dl_csum_trailer अणु
	u8 reserved1;
	u8 flags;			/* MAP_CSUM_DL_VALID_FLAG */
	__be16 csum_start_offset;
	__be16 csum_length;
	__be16 csum_value;
पूर्ण __aligned(1);

/* rmnet_map_dl_csum_trailer flags field:
 *  VALID:	1 = checksum and length valid; 0 = ignore them
 */
#घोषणा MAP_CSUM_DL_VALID_FLAG		BIT(0)

काष्ठा rmnet_map_ul_csum_header अणु
	__be16 csum_start_offset;
	__be16 csum_info;		/* MAP_CSUM_UL_* */
पूर्ण __aligned(1);

/* csum_info field:
 *  OFFSET:	where (offset in bytes) to insert computed checksum
 *  UDP:	1 = UDP checksum (zero checkum means no checksum)
 *  ENABLED:	1 = checksum computation requested
 */
#घोषणा MAP_CSUM_UL_OFFSET_MASK		GENMASK(13, 0)
#घोषणा MAP_CSUM_UL_UDP_FLAG		BIT(14)
#घोषणा MAP_CSUM_UL_ENABLED_FLAG	BIT(15)

#पूर्ण_अगर /* !(_LINUX_IF_RMNET_H_) */
