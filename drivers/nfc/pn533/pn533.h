<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम NXP PN533 NFC Chip
 *
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 * Copyright (C) 2012-2013 Tieto Poland
 */

#घोषणा PN533_DEVICE_STD		0x1
#घोषणा PN533_DEVICE_PASORI		0x2
#घोषणा PN533_DEVICE_ACR122U		0x3
#घोषणा PN533_DEVICE_PN532		0x4
#घोषणा PN533_DEVICE_PN532_AUTOPOLL	0x5

#घोषणा PN533_ALL_PROTOCOLS (NFC_PROTO_JEWEL_MASK | NFC_PROTO_MIFARE_MASK |\
			     NFC_PROTO_FELICA_MASK | NFC_PROTO_ISO14443_MASK |\
			     NFC_PROTO_NFC_DEP_MASK |\
			     NFC_PROTO_ISO14443_B_MASK)

#घोषणा PN533_NO_TYPE_B_PROTOCOLS (NFC_PROTO_JEWEL_MASK | \
				   NFC_PROTO_MIFARE_MASK | \
				   NFC_PROTO_FELICA_MASK | \
				   NFC_PROTO_ISO14443_MASK | \
				   NFC_PROTO_NFC_DEP_MASK)

/* Standard pn533 frame definitions (standard and extended)*/
#घोषणा PN533_STD_FRAME_HEADER_LEN (माप(काष्ठा pn533_std_frame) \
					+ 2) /* data[0] TFI, data[1] CC */
#घोषणा PN533_STD_FRAME_TAIL_LEN 2 /* data[len] DCS, data[len + 1] postamble*/

#घोषणा PN533_EXT_FRAME_HEADER_LEN (माप(काष्ठा pn533_ext_frame) \
					+ 2) /* data[0] TFI, data[1] CC */

#घोषणा PN533_CMD_DATAEXCH_HEAD_LEN 1
#घोषणा PN533_CMD_DATAEXCH_DATA_MAXLEN	262
#घोषणा PN533_CMD_DATAFRAME_MAXLEN	240	/* max data length (send) */

/*
 * Max extended frame payload len, excluding TFI and CC
 * which are alपढ़ोy in PN533_FRAME_HEADER_LEN.
 */
#घोषणा PN533_STD_FRAME_MAX_PAYLOAD_LEN 263


/* Preamble (1), SoPC (2), ACK Code (2), Postamble (1) */
#घोषणा PN533_STD_FRAME_ACK_SIZE 6
/*
 * Preamble (1), SoPC (2), Packet Length (1), Packet Length Checksum (1),
 * Specअगरic Application Level Error Code (1) , Postamble (1)
 */
#घोषणा PN533_STD_ERROR_FRAME_SIZE 8
#घोषणा PN533_STD_FRAME_CHECKSUM(f) (f->data[f->datalen])
#घोषणा PN533_STD_FRAME_POSTAMBLE(f) (f->data[f->datalen + 1])
/* Half start code (3), LEN (4) should be 0xffff क्रम extended frame */
#घोषणा PN533_STD_IS_EXTENDED(hdr) ((hdr)->datalen == 0xFF \
					&& (hdr)->datalen_checksum == 0xFF)
#घोषणा PN533_EXT_FRAME_CHECKSUM(f) (f->data[be16_to_cpu(f->datalen)])

/* start of frame */
#घोषणा PN533_STD_FRAME_SOF 0x00FF

/* standard frame identअगरier: in/out/error */
#घोषणा PN533_STD_FRAME_IDENTIFIER(f) (f->data[0]) /* TFI */
#घोषणा PN533_STD_FRAME_सूची_OUT 0xD4
#घोषणा PN533_STD_FRAME_सूची_IN 0xD5

/* PN533 Commands */
#घोषणा PN533_FRAME_CMD(f) (f->data[1])

#घोषणा PN533_CMD_GET_FIRMWARE_VERSION 0x02
#घोषणा PN533_CMD_SAM_CONFIGURATION 0x14
#घोषणा PN533_CMD_RF_CONFIGURATION 0x32
#घोषणा PN533_CMD_IN_DATA_EXCHANGE 0x40
#घोषणा PN533_CMD_IN_COMM_THRU     0x42
#घोषणा PN533_CMD_IN_LIST_PASSIVE_TARGET 0x4A
#घोषणा PN533_CMD_IN_ATR 0x50
#घोषणा PN533_CMD_IN_RELEASE 0x52
#घोषणा PN533_CMD_IN_JUMP_FOR_DEP 0x56
#घोषणा PN533_CMD_IN_AUTOPOLL 0x60

#घोषणा PN533_CMD_TG_INIT_AS_TARGET 0x8c
#घोषणा PN533_CMD_TG_GET_DATA 0x86
#घोषणा PN533_CMD_TG_SET_DATA 0x8e
#घोषणा PN533_CMD_TG_SET_META_DATA 0x94
#घोषणा PN533_CMD_UNDEF 0xff

#घोषणा PN533_CMD_RESPONSE(cmd) (cmd + 1)

/* PN533 Return codes */
#घोषणा PN533_CMD_RET_MASK 0x3F
#घोषणा PN533_CMD_MI_MASK 0x40
#घोषणा PN533_CMD_RET_SUCCESS 0x00

#घोषणा PN533_FRAME_DATALEN_ACK 0x00
#घोषणा PN533_FRAME_DATALEN_ERROR 0x01
#घोषणा PN533_FRAME_DATALEN_EXTENDED 0xFF

क्रमागत  pn533_protocol_type अणु
	PN533_PROTO_REQ_ACK_RESP = 0,
	PN533_PROTO_REQ_RESP
पूर्ण;

/* Poll modulations */
क्रमागत अणु
	PN533_POLL_MOD_106KBPS_A,
	PN533_POLL_MOD_212KBPS_FELICA,
	PN533_POLL_MOD_424KBPS_FELICA,
	PN533_POLL_MOD_106KBPS_JEWEL,
	PN533_POLL_MOD_847KBPS_B,
	PN533_LISTEN_MOD,

	__PN533_POLL_MOD_AFTER_LAST,
पूर्ण;
#घोषणा PN533_POLL_MOD_MAX (__PN533_POLL_MOD_AFTER_LAST - 1)

काष्ठा pn533_std_frame अणु
	u8 preamble;
	__be16 start_frame;
	u8 datalen;
	u8 datalen_checksum;
	u8 data[];
पूर्ण __packed;

काष्ठा pn533_ext_frame अणु	/* Extended Inक्रमmation frame */
	u8 preamble;
	__be16 start_frame;
	__be16 eअगर_flag;	/* fixed to 0xFFFF */
	__be16 datalen;
	u8 datalen_checksum;
	u8 data[];
पूर्ण __packed;

काष्ठा pn533 अणु
	काष्ठा nfc_dev *nfc_dev;
	u32 device_type;
	क्रमागत pn533_protocol_type protocol_type;

	काष्ठा sk_buff_head resp_q;
	काष्ठा sk_buff_head fragment_skb;

	काष्ठा workqueue_काष्ठा	*wq;
	काष्ठा work_काष्ठा cmd_work;
	काष्ठा work_काष्ठा cmd_complete_work;
	काष्ठा delayed_work poll_work;
	काष्ठा work_काष्ठा mi_rx_work;
	काष्ठा work_काष्ठा mi_tx_work;
	काष्ठा work_काष्ठा mi_पंचांग_rx_work;
	काष्ठा work_काष्ठा mi_पंचांग_tx_work;
	काष्ठा work_काष्ठा tg_work;
	काष्ठा work_काष्ठा rf_work;

	काष्ठा list_head cmd_queue;
	काष्ठा pn533_cmd *cmd;
	u8 cmd_pending;
	काष्ठा mutex cmd_lock;  /* protects cmd queue */

	व्योम *cmd_complete_mi_arg;
	व्योम *cmd_complete_dep_arg;

	काष्ठा pn533_poll_modulations *poll_mod_active[PN533_POLL_MOD_MAX + 1];
	u8 poll_mod_count;
	u8 poll_mod_curr;
	u8 poll_dep;
	u32 poll_protocols;
	u32 listen_protocols;
	काष्ठा समयr_list listen_समयr;
	पूर्णांक cancel_listen;

	u8 *gb;
	माप_प्रकार gb_len;

	u8 tgt_available_prots;
	u8 tgt_active_prot;
	u8 tgt_mode;

	काष्ठा pn533_frame_ops *ops;

	काष्ठा device *dev;
	व्योम *phy;
	काष्ठा pn533_phy_ops *phy_ops;
पूर्ण;

प्रकार पूर्णांक (*pn533_send_async_complete_t) (काष्ठा pn533 *dev, व्योम *arg,
					काष्ठा sk_buff *resp);

काष्ठा pn533_cmd अणु
	काष्ठा list_head queue;
	u8 code;
	पूर्णांक status;
	काष्ठा sk_buff *req;
	काष्ठा sk_buff *resp;
	pn533_send_async_complete_t  complete_cb;
	व्योम *complete_cb_context;
पूर्ण;


काष्ठा pn533_frame_ops अणु
	व्योम (*tx_frame_init)(व्योम *frame, u8 cmd_code);
	व्योम (*tx_frame_finish)(व्योम *frame);
	व्योम (*tx_update_payload_len)(व्योम *frame, पूर्णांक len);
	पूर्णांक tx_header_len;
	पूर्णांक tx_tail_len;

	bool (*rx_is_frame_valid)(व्योम *frame, काष्ठा pn533 *dev);
	bool (*rx_frame_is_ack)(व्योम *frame);
	पूर्णांक (*rx_frame_size)(व्योम *frame);
	पूर्णांक rx_header_len;
	पूर्णांक rx_tail_len;

	पूर्णांक max_payload_len;
	u8 (*get_cmd_code)(व्योम *frame);
पूर्ण;


काष्ठा pn533_phy_ops अणु
	पूर्णांक (*send_frame)(काष्ठा pn533 *priv,
			  काष्ठा sk_buff *out);
	पूर्णांक (*send_ack)(काष्ठा pn533 *dev, gfp_t flags);
	व्योम (*पात_cmd)(काष्ठा pn533 *priv, gfp_t flags);
	/*
	 * dev_up and dev_करोwn are optional.
	 * They are used to inक्रमm the phy layer that the nfc chip
	 * is going to be really used very soon. The phy layer can then
	 * bring up it's पूर्णांकerface to the chip and have it suspended क्रम घातer
	 * saving reasons otherwise.
	 */
	पूर्णांक (*dev_up)(काष्ठा pn533 *priv);
	पूर्णांक (*dev_करोwn)(काष्ठा pn533 *priv);
पूर्ण;


काष्ठा pn533 *pn53x_common_init(u32 device_type,
				क्रमागत pn533_protocol_type protocol_type,
				व्योम *phy,
				काष्ठा pn533_phy_ops *phy_ops,
				काष्ठा pn533_frame_ops *fops,
				काष्ठा device *dev);

पूर्णांक pn533_finalize_setup(काष्ठा pn533 *dev);
व्योम pn53x_common_clean(काष्ठा pn533 *priv);
व्योम pn533_recv_frame(काष्ठा pn533 *dev, काष्ठा sk_buff *skb, पूर्णांक status);
पूर्णांक pn532_i2c_nfc_alloc(काष्ठा pn533 *priv, u32 protocols,
			काष्ठा device *parent);
पूर्णांक pn53x_रेजिस्टर_nfc(काष्ठा pn533 *priv, u32 protocols,
			काष्ठा device *parent);
व्योम pn53x_unरेजिस्टर_nfc(काष्ठा pn533 *priv);

bool pn533_rx_frame_is_cmd_response(काष्ठा pn533 *dev, व्योम *frame);
bool pn533_rx_frame_is_ack(व्योम *_frame);
