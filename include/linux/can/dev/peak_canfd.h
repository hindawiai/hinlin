<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * CAN driver क्रम PEAK System micro-CAN based adapters
 *
 * Copyright (C) 2003-2011 PEAK System-Technik GmbH
 * Copyright (C) 2011-2013 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 */
#अगर_अघोषित PUCAN_H
#घोषणा PUCAN_H

/* uCAN commands opcodes list (low-order 10 bits) */
#घोषणा PUCAN_CMD_NOP			0x000
#घोषणा PUCAN_CMD_RESET_MODE		0x001
#घोषणा PUCAN_CMD_NORMAL_MODE		0x002
#घोषणा PUCAN_CMD_LISTEN_ONLY_MODE	0x003
#घोषणा PUCAN_CMD_TIMING_SLOW		0x004
#घोषणा PUCAN_CMD_TIMING_FAST		0x005
#घोषणा PUCAN_CMD_SET_STD_FILTER	0x006
#घोषणा PUCAN_CMD_RESERVED2		0x007
#घोषणा PUCAN_CMD_FILTER_STD		0x008
#घोषणा PUCAN_CMD_TX_ABORT		0x009
#घोषणा PUCAN_CMD_WR_ERR_CNT		0x00a
#घोषणा PUCAN_CMD_SET_EN_OPTION		0x00b
#घोषणा PUCAN_CMD_CLR_DIS_OPTION	0x00c
#घोषणा PUCAN_CMD_RX_BARRIER		0x010
#घोषणा PUCAN_CMD_END_OF_COLLECTION	0x3ff

/* uCAN received messages list */
#घोषणा PUCAN_MSG_CAN_RX		0x0001
#घोषणा PUCAN_MSG_ERROR			0x0002
#घोषणा PUCAN_MSG_STATUS		0x0003
#घोषणा PUCAN_MSG_BUSLOAD		0x0004

#घोषणा PUCAN_MSG_CACHE_CRITICAL	0x0102

/* uCAN transmitted messages */
#घोषणा PUCAN_MSG_CAN_TX		0x1000

/* uCAN command common header */
काष्ठा __packed pucan_command अणु
	__le16	opcode_channel;
	u16	args[3];
पूर्ण;

/* वापस the opcode from the opcode_channel field of a command */
अटल अंतरभूत u16 pucan_cmd_get_opcode(काष्ठा pucan_command *c)
अणु
	वापस le16_to_cpu(c->opcode_channel) & 0x3ff;
पूर्ण

#घोषणा PUCAN_TSLOW_BRP_BITS		10
#घोषणा PUCAN_TSLOW_TSGEG1_BITS		8
#घोषणा PUCAN_TSLOW_TSGEG2_BITS		7
#घोषणा PUCAN_TSLOW_SJW_BITS		7

#घोषणा PUCAN_TSLOW_BRP_MASK		((1 << PUCAN_TSLOW_BRP_BITS) - 1)
#घोषणा PUCAN_TSLOW_TSEG1_MASK		((1 << PUCAN_TSLOW_TSGEG1_BITS) - 1)
#घोषणा PUCAN_TSLOW_TSEG2_MASK		((1 << PUCAN_TSLOW_TSGEG2_BITS) - 1)
#घोषणा PUCAN_TSLOW_SJW_MASK		((1 << PUCAN_TSLOW_SJW_BITS) - 1)

/* uCAN TIMING_SLOW command fields */
#घोषणा PUCAN_TSLOW_SJW_T(s, t)		(((s) & PUCAN_TSLOW_SJW_MASK) | \
								((!!(t)) << 7))
#घोषणा PUCAN_TSLOW_TSEG2(t)		((t) & PUCAN_TSLOW_TSEG2_MASK)
#घोषणा PUCAN_TSLOW_TSEG1(t)		((t) & PUCAN_TSLOW_TSEG1_MASK)
#घोषणा PUCAN_TSLOW_BRP(b)		((b) & PUCAN_TSLOW_BRP_MASK)

काष्ठा __packed pucan_timing_slow अणु
	__le16	opcode_channel;

	u8	ewl;		/* Error Warning limit */
	u8	sjw_t;		/* Sync Jump Width + Triple sampling */
	u8	tseg2;		/* Timing SEGment 2 */
	u8	tseg1;		/* Timing SEGment 1 */

	__le16	brp;		/* BaudRate Prescaler */
पूर्ण;

#घोषणा PUCAN_TFAST_BRP_BITS		10
#घोषणा PUCAN_TFAST_TSGEG1_BITS		5
#घोषणा PUCAN_TFAST_TSGEG2_BITS		4
#घोषणा PUCAN_TFAST_SJW_BITS		4

#घोषणा PUCAN_TFAST_BRP_MASK		((1 << PUCAN_TFAST_BRP_BITS) - 1)
#घोषणा PUCAN_TFAST_TSEG1_MASK		((1 << PUCAN_TFAST_TSGEG1_BITS) - 1)
#घोषणा PUCAN_TFAST_TSEG2_MASK		((1 << PUCAN_TFAST_TSGEG2_BITS) - 1)
#घोषणा PUCAN_TFAST_SJW_MASK		((1 << PUCAN_TFAST_SJW_BITS) - 1)

/* uCAN TIMING_FAST command fields */
#घोषणा PUCAN_TFAST_SJW(s)		((s) & PUCAN_TFAST_SJW_MASK)
#घोषणा PUCAN_TFAST_TSEG2(t)		((t) & PUCAN_TFAST_TSEG2_MASK)
#घोषणा PUCAN_TFAST_TSEG1(t)		((t) & PUCAN_TFAST_TSEG1_MASK)
#घोषणा PUCAN_TFAST_BRP(b)		((b) & PUCAN_TFAST_BRP_MASK)

काष्ठा __packed pucan_timing_fast अणु
	__le16	opcode_channel;

	u8	unused;
	u8	sjw;		/* Sync Jump Width */
	u8	tseg2;		/* Timing SEGment 2 */
	u8	tseg1;		/* Timing SEGment 1 */

	__le16	brp;		/* BaudRate Prescaler */
पूर्ण;

/* uCAN FILTER_STD command fields */
#घोषणा PUCAN_FLTSTD_ROW_IDX_BITS	6

काष्ठा __packed pucan_filter_std अणु
	__le16	opcode_channel;

	__le16	idx;
	__le32	mask;		/* CAN-ID biपंचांगask in idx range */
पूर्ण;

#घोषणा PUCAN_FLTSTD_ROW_IDX_MAX	((1 << PUCAN_FLTSTD_ROW_IDX_BITS) - 1)

/* uCAN SET_STD_FILTER command fields */
काष्ठा __packed pucan_std_filter अणु
	__le16	opcode_channel;

	u8	unused;
	u8	idx;
	__le32	mask;		/* CAN-ID biपंचांगask in idx range */
पूर्ण;

/* uCAN TX_ABORT commands fields */
#घोषणा PUCAN_TX_ABORT_FLUSH		0x0001

काष्ठा __packed pucan_tx_पात अणु
	__le16	opcode_channel;

	__le16	flags;
	u32	unused;
पूर्ण;

/* uCAN WR_ERR_CNT command fields */
#घोषणा PUCAN_WRERRCNT_TE		0x4000	/* Tx error cntr ग_लिखो Enable */
#घोषणा PUCAN_WRERRCNT_RE		0x8000	/* Rx error cntr ग_लिखो Enable */

काष्ठा __packed pucan_wr_err_cnt अणु
	__le16	opcode_channel;

	__le16	sel_mask;
	u8	tx_counter;	/* Tx error counter new value */
	u8	rx_counter;	/* Rx error counter new value */

	u16	unused;
पूर्ण;

/* uCAN SET_EN/CLR_DIS _OPTION command fields */
#घोषणा PUCAN_OPTION_ERROR		0x0001
#घोषणा PUCAN_OPTION_BUSLOAD		0x0002
#घोषणा PUCAN_OPTION_CANDFDISO		0x0004

काष्ठा __packed pucan_options अणु
	__le16	opcode_channel;

	__le16	options;
	u32	unused;
पूर्ण;

/* uCAN received messages global क्रमmat */
काष्ठा __packed pucan_msg अणु
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
पूर्ण;

/* uCAN flags क्रम CAN/CANFD messages */
#घोषणा PUCAN_MSG_SELF_RECEIVE		0x80
#घोषणा PUCAN_MSG_ERROR_STATE_IND	0x40	/* error state indicator */
#घोषणा PUCAN_MSG_BITRATE_SWITCH	0x20	/* bitrate चयन */
#घोषणा PUCAN_MSG_EXT_DATA_LEN		0x10	/* extended data length */
#घोषणा PUCAN_MSG_SINGLE_SHOT		0x08
#घोषणा PUCAN_MSG_LOOPED_BACK		0x04
#घोषणा PUCAN_MSG_EXT_ID		0x02
#घोषणा PUCAN_MSG_RTR			0x01

काष्ठा __packed pucan_rx_msg अणु
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	__le32	tag_low;
	__le32	tag_high;
	u8	channel_dlc;
	u8	client;
	__le16	flags;
	__le32	can_id;
	u8	d[];
पूर्ण;

/* uCAN error types */
#घोषणा PUCAN_ERMSG_BIT_ERROR		0
#घोषणा PUCAN_ERMSG_FORM_ERROR		1
#घोषणा PUCAN_ERMSG_STUFF_ERROR		2
#घोषणा PUCAN_ERMSG_OTHER_ERROR		3
#घोषणा PUCAN_ERMSG_ERR_CNT_DEC		4

काष्ठा __packed pucan_error_msg अणु
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	u8	channel_type_d;
	u8	code_g;
	u8	tx_err_cnt;
	u8	rx_err_cnt;
पूर्ण;

अटल अंतरभूत पूर्णांक pucan_error_get_channel(स्थिर काष्ठा pucan_error_msg *msg)
अणु
	वापस msg->channel_type_d & 0x0f;
पूर्ण

#घोषणा PUCAN_RX_BARRIER		0x10
#घोषणा PUCAN_BUS_PASSIVE		0x20
#घोषणा PUCAN_BUS_WARNING		0x40
#घोषणा PUCAN_BUS_BUSOFF		0x80

काष्ठा __packed pucan_status_msg अणु
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	u8	channel_p_w_b;
	u8	unused[3];
पूर्ण;

अटल अंतरभूत पूर्णांक pucan_status_get_channel(स्थिर काष्ठा pucan_status_msg *msg)
अणु
	वापस msg->channel_p_w_b & 0x0f;
पूर्ण

अटल अंतरभूत पूर्णांक pucan_status_is_rx_barrier(स्थिर काष्ठा pucan_status_msg *msg)
अणु
	वापस msg->channel_p_w_b & PUCAN_RX_BARRIER;
पूर्ण

अटल अंतरभूत पूर्णांक pucan_status_is_passive(स्थिर काष्ठा pucan_status_msg *msg)
अणु
	वापस msg->channel_p_w_b & PUCAN_BUS_PASSIVE;
पूर्ण

अटल अंतरभूत पूर्णांक pucan_status_is_warning(स्थिर काष्ठा pucan_status_msg *msg)
अणु
	वापस msg->channel_p_w_b & PUCAN_BUS_WARNING;
पूर्ण

अटल अंतरभूत पूर्णांक pucan_status_is_busoff(स्थिर काष्ठा pucan_status_msg *msg)
अणु
	वापस msg->channel_p_w_b & PUCAN_BUS_BUSOFF;
पूर्ण

/* uCAN transmitted message क्रमmat */
#घोषणा PUCAN_MSG_CHANNEL_DLC(c, d)	(((c) & 0xf) | ((d) << 4))

काष्ठा __packed pucan_tx_msg अणु
	__le16	size;
	__le16	type;
	__le32	tag_low;
	__le32	tag_high;
	u8	channel_dlc;
	u8	client;
	__le16	flags;
	__le32	can_id;
	u8	d[];
पूर्ण;

/* build the cmd opcode_channel field with respect to the correct endianness */
अटल अंतरभूत __le16 pucan_cmd_opcode_channel(पूर्णांक index, पूर्णांक opcode)
अणु
	वापस cpu_to_le16(((index) << 12) | ((opcode) & 0x3ff));
पूर्ण

/* वापस the channel number part from any received message channel_dlc field */
अटल अंतरभूत पूर्णांक pucan_msg_get_channel(स्थिर काष्ठा pucan_rx_msg *msg)
अणु
	वापस msg->channel_dlc & 0xf;
पूर्ण

/* वापस the dlc value from any received message channel_dlc field */
अटल अंतरभूत u8 pucan_msg_get_dlc(स्थिर काष्ठा pucan_rx_msg *msg)
अणु
	वापस msg->channel_dlc >> 4;
पूर्ण

अटल अंतरभूत पूर्णांक pucan_ermsg_get_channel(स्थिर काष्ठा pucan_error_msg *msg)
अणु
	वापस msg->channel_type_d & 0x0f;
पूर्ण

अटल अंतरभूत पूर्णांक pucan_sपंचांगsg_get_channel(स्थिर काष्ठा pucan_status_msg *msg)
अणु
	वापस msg->channel_p_w_b & 0x0f;
पूर्ण

#पूर्ण_अगर
