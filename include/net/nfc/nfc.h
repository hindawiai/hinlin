<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 * Copyright (C) 2014 Marvell International Ltd.
 *
 * Authors:
 *    Lauro Ramos Venancio <lauro.venancio@खोलोbossa.org>
 *    Aloisio Almeida Jr <aloisio.almeida@खोलोbossa.org>
 */

#अगर_अघोषित __NET_NFC_H
#घोषणा __NET_NFC_H

#समावेश <linux/nfc.h>
#समावेश <linux/device.h>
#समावेश <linux/skbuff.h>

#घोषणा nfc_dbg(dev, fmt, ...) dev_dbg((dev), "NFC: " fmt, ##__VA_ARGS__)
#घोषणा nfc_info(dev, fmt, ...) dev_info((dev), "NFC: " fmt, ##__VA_ARGS__)
#घोषणा nfc_err(dev, fmt, ...) dev_err((dev), "NFC: " fmt, ##__VA_ARGS__)

काष्ठा nfc_phy_ops अणु
	पूर्णांक (*ग_लिखो)(व्योम *dev_id, काष्ठा sk_buff *skb);
	पूर्णांक (*enable)(व्योम *dev_id);
	व्योम (*disable)(व्योम *dev_id);
पूर्ण;

काष्ठा nfc_dev;

/**
 * data_exchange_cb_t - Definition of nfc_data_exchange callback
 *
 * @context: nfc_data_exchange cb_context parameter
 * @skb: response data
 * @err: If an error has occurred during data exchange, it is the
 *	error number. Zero means no error.
 *
 * When a rx or tx package is lost or corrupted or the target माला_लो out
 * of the operating field, err is -EIO.
 */
प्रकार व्योम (*data_exchange_cb_t)(व्योम *context, काष्ठा sk_buff *skb,
								पूर्णांक err);

प्रकार व्योम (*se_io_cb_t)(व्योम *context, u8 *apdu, माप_प्रकार apdu_len, पूर्णांक err);

काष्ठा nfc_target;

काष्ठा nfc_ops अणु
	पूर्णांक (*dev_up)(काष्ठा nfc_dev *dev);
	पूर्णांक (*dev_करोwn)(काष्ठा nfc_dev *dev);
	पूर्णांक (*start_poll)(काष्ठा nfc_dev *dev,
			  u32 im_protocols, u32 पंचांग_protocols);
	व्योम (*stop_poll)(काष्ठा nfc_dev *dev);
	पूर्णांक (*dep_link_up)(काष्ठा nfc_dev *dev, काष्ठा nfc_target *target,
			   u8 comm_mode, u8 *gb, माप_प्रकार gb_len);
	पूर्णांक (*dep_link_करोwn)(काष्ठा nfc_dev *dev);
	पूर्णांक (*activate_target)(काष्ठा nfc_dev *dev, काष्ठा nfc_target *target,
			       u32 protocol);
	व्योम (*deactivate_target)(काष्ठा nfc_dev *dev,
				  काष्ठा nfc_target *target, u8 mode);
	पूर्णांक (*im_transceive)(काष्ठा nfc_dev *dev, काष्ठा nfc_target *target,
			     काष्ठा sk_buff *skb, data_exchange_cb_t cb,
			     व्योम *cb_context);
	पूर्णांक (*पंचांग_send)(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb);
	पूर्णांक (*check_presence)(काष्ठा nfc_dev *dev, काष्ठा nfc_target *target);
	पूर्णांक (*fw_करोwnload)(काष्ठा nfc_dev *dev, स्थिर अक्षर *firmware_name);

	/* Secure Element API */
	पूर्णांक (*discover_se)(काष्ठा nfc_dev *dev);
	पूर्णांक (*enable_se)(काष्ठा nfc_dev *dev, u32 se_idx);
	पूर्णांक (*disable_se)(काष्ठा nfc_dev *dev, u32 se_idx);
	पूर्णांक (*se_io) (काष्ठा nfc_dev *dev, u32 se_idx,
		      u8 *apdu, माप_प्रकार apdu_length,
		      se_io_cb_t cb, व्योम *cb_context);
पूर्ण;

#घोषणा NFC_TARGET_IDX_ANY -1
#घोषणा NFC_MAX_GT_LEN 48
#घोषणा NFC_ATR_RES_GT_OFFSET 15
#घोषणा NFC_ATR_REQ_GT_OFFSET 14

/**
 * काष्ठा nfc_target - NFC target descriptiom
 *
 * @sens_res: 2 bytes describing the target SENS_RES response, अगर the target
 *	is a type A one. The %sens_res most signअगरicant byte must be byte 2
 *	as described by the NFC Forum digital specअगरication (i.e. the platक्रमm
 *	configuration one) जबतक %sens_res least signअगरicant byte is byte 1.
 */
काष्ठा nfc_target अणु
	u32 idx;
	u32 supported_protocols;
	u16 sens_res;
	u8 sel_res;
	u8 nfcid1_len;
	u8 nfcid1[NFC_NFCID1_MAXSIZE];
	u8 nfcid2_len;
	u8 nfcid2[NFC_NFCID2_MAXSIZE];
	u8 sensb_res_len;
	u8 sensb_res[NFC_SENSB_RES_MAXSIZE];
	u8 sensf_res_len;
	u8 sensf_res[NFC_SENSF_RES_MAXSIZE];
	u8 hci_पढ़ोer_gate;
	u8 logical_idx;
	u8 is_iso15693;
	u8 iso15693_dsfid;
	u8 iso15693_uid[NFC_ISO15693_UID_MAXSIZE];
पूर्ण;

/**
 * nfc_se - A काष्ठाure क्रम NFC accessible secure elements.
 *
 * @idx: The secure element index. User space will enable or
 *       disable a secure element by its index.
 * @type: The secure element type. It can be SE_UICC or
 *        SE_EMBEDDED.
 * @state: The secure element state, either enabled or disabled.
 *
 */
काष्ठा nfc_se अणु
	काष्ठा list_head list;
	u32 idx;
	u16 type;
	u16 state;
पूर्ण;

/**
 * nfc_evt_transaction - A काष्ठा क्रम NFC secure element event transaction.
 *
 * @aid: The application identअगरier triggering the event
 *
 * @aid_len: The application identअगरier length [5:16]
 *
 * @params: The application parameters transmitted during the transaction
 *
 * @params_len: The applications parameters length [0:255]
 *
 */
#घोषणा NFC_MIN_AID_LENGTH	5
#घोषणा	NFC_MAX_AID_LENGTH	16
#घोषणा NFC_MAX_PARAMS_LENGTH	255

#घोषणा NFC_EVT_TRANSACTION_AID_TAG	0x81
#घोषणा NFC_EVT_TRANSACTION_PARAMS_TAG	0x82
काष्ठा nfc_evt_transaction अणु
	u32 aid_len;
	u8 aid[NFC_MAX_AID_LENGTH];
	u8 params_len;
	u8 params[];
पूर्ण __packed;

काष्ठा nfc_genl_data अणु
	u32 poll_req_portid;
	काष्ठा mutex genl_data_mutex;
पूर्ण;

काष्ठा nfc_venकरोr_cmd अणु
	__u32 venकरोr_id;
	__u32 subcmd;
	पूर्णांक (*करोit)(काष्ठा nfc_dev *dev, व्योम *data, माप_प्रकार data_len);
पूर्ण;

काष्ठा nfc_dev अणु
	पूर्णांक idx;
	u32 target_next_idx;
	काष्ठा nfc_target *tarमाला_लो;
	पूर्णांक n_tarमाला_लो;
	पूर्णांक tarमाला_लो_generation;
	काष्ठा device dev;
	bool dev_up;
	bool fw_करोwnload_in_progress;
	u8 rf_mode;
	bool polling;
	काष्ठा nfc_target *active_target;
	bool dep_link_up;
	काष्ठा nfc_genl_data genl_data;
	u32 supported_protocols;

	काष्ठा list_head secure_elements;

	पूर्णांक tx_headroom;
	पूर्णांक tx_tailroom;

	काष्ठा समयr_list check_pres_समयr;
	काष्ठा work_काष्ठा check_pres_work;

	bool shutting_करोwn;

	काष्ठा rfसमाप्त *rfसमाप्त;

	काष्ठा nfc_venकरोr_cmd *venकरोr_cmds;
	पूर्णांक n_venकरोr_cmds;

	काष्ठा nfc_ops *ops;
	काष्ठा genl_info *cur_cmd_info;
पूर्ण;
#घोषणा to_nfc_dev(_dev) container_of(_dev, काष्ठा nfc_dev, dev)

बाह्य काष्ठा class nfc_class;

काष्ठा nfc_dev *nfc_allocate_device(काष्ठा nfc_ops *ops,
				    u32 supported_protocols,
				    पूर्णांक tx_headroom,
				    पूर्णांक tx_tailroom);

/**
 * nfc_मुक्त_device - मुक्त nfc device
 *
 * @dev: The nfc device to मुक्त
 */
अटल अंतरभूत व्योम nfc_मुक्त_device(काष्ठा nfc_dev *dev)
अणु
	put_device(&dev->dev);
पूर्ण

पूर्णांक nfc_रेजिस्टर_device(काष्ठा nfc_dev *dev);

व्योम nfc_unरेजिस्टर_device(काष्ठा nfc_dev *dev);

/**
 * nfc_set_parent_dev - set the parent device
 *
 * @nfc_dev: The nfc device whose parent is being set
 * @dev: The parent device
 */
अटल अंतरभूत व्योम nfc_set_parent_dev(काष्ठा nfc_dev *nfc_dev,
				      काष्ठा device *dev)
अणु
	nfc_dev->dev.parent = dev;
पूर्ण

/**
 * nfc_set_drvdata - set driver specअगरc data
 *
 * @dev: The nfc device
 * @data: Poपूर्णांकer to driver specअगरc data
 */
अटल अंतरभूत व्योम nfc_set_drvdata(काष्ठा nfc_dev *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->dev, data);
पूर्ण

/**
 * nfc_get_drvdata - get driver specअगरc data
 *
 * @dev: The nfc device
 */
अटल अंतरभूत व्योम *nfc_get_drvdata(काष्ठा nfc_dev *dev)
अणु
	वापस dev_get_drvdata(&dev->dev);
पूर्ण

/**
 * nfc_device_name - get the nfc device name
 *
 * @dev: The nfc device whose name to वापस
 */
अटल अंतरभूत स्थिर अक्षर *nfc_device_name(काष्ठा nfc_dev *dev)
अणु
	वापस dev_name(&dev->dev);
पूर्ण

काष्ठा sk_buff *nfc_alloc_send_skb(काष्ठा nfc_dev *dev, काष्ठा sock *sk,
				   अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक size,
				   अचिन्हित पूर्णांक *err);
काष्ठा sk_buff *nfc_alloc_recv_skb(अचिन्हित पूर्णांक size, gfp_t gfp);

पूर्णांक nfc_set_remote_general_bytes(काष्ठा nfc_dev *dev,
				 u8 *gt, u8 gt_len);
u8 *nfc_get_local_general_bytes(काष्ठा nfc_dev *dev, माप_प्रकार *gb_len);

पूर्णांक nfc_fw_करोwnload_करोne(काष्ठा nfc_dev *dev, स्थिर अक्षर *firmware_name,
			 u32 result);

पूर्णांक nfc_tarमाला_लो_found(काष्ठा nfc_dev *dev,
		      काष्ठा nfc_target *tarमाला_लो, पूर्णांक ntarमाला_लो);
पूर्णांक nfc_target_lost(काष्ठा nfc_dev *dev, u32 target_idx);

पूर्णांक nfc_dep_link_is_up(काष्ठा nfc_dev *dev, u32 target_idx,
		       u8 comm_mode, u8 rf_mode);

पूर्णांक nfc_पंचांग_activated(काष्ठा nfc_dev *dev, u32 protocol, u8 comm_mode,
		     u8 *gb, माप_प्रकार gb_len);
पूर्णांक nfc_पंचांग_deactivated(काष्ठा nfc_dev *dev);
पूर्णांक nfc_पंचांग_data_received(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb);

व्योम nfc_driver_failure(काष्ठा nfc_dev *dev, पूर्णांक err);

पूर्णांक nfc_se_transaction(काष्ठा nfc_dev *dev, u8 se_idx,
		       काष्ठा nfc_evt_transaction *evt_transaction);
पूर्णांक nfc_se_connectivity(काष्ठा nfc_dev *dev, u8 se_idx);
पूर्णांक nfc_add_se(काष्ठा nfc_dev *dev, u32 se_idx, u16 type);
पूर्णांक nfc_हटाओ_se(काष्ठा nfc_dev *dev, u32 se_idx);
काष्ठा nfc_se *nfc_find_se(काष्ठा nfc_dev *dev, u32 se_idx);

व्योम nfc_send_to_raw_sock(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb,
			  u8 payload_type, u8 direction);

अटल अंतरभूत पूर्णांक nfc_set_venकरोr_cmds(काष्ठा nfc_dev *dev,
				      काष्ठा nfc_venकरोr_cmd *cmds,
				      पूर्णांक n_cmds)
अणु
	अगर (dev->venकरोr_cmds || dev->n_venकरोr_cmds)
		वापस -EINVAL;

	dev->venकरोr_cmds = cmds;
	dev->n_venकरोr_cmds = n_cmds;

	वापस 0;
पूर्ण

काष्ठा sk_buff *__nfc_alloc_venकरोr_cmd_reply_skb(काष्ठा nfc_dev *dev,
						 क्रमागत nfc_attrs attr,
						 u32 oui, u32 subcmd,
						 पूर्णांक approxlen);
पूर्णांक nfc_venकरोr_cmd_reply(काष्ठा sk_buff *skb);

/**
 * nfc_venकरोr_cmd_alloc_reply_skb - allocate venकरोr command reply
 * @dev: nfc device
 * @oui: venकरोr oui
 * @approxlen: an upper bound of the length of the data that will
 *      be put पूर्णांकo the skb
 *
 * This function allocates and pre-fills an skb क्रम a reply to
 * a venकरोr command. Since it is पूर्णांकended क्रम a reply, calling
 * it outside of a venकरोr command's करोit() operation is invalid.
 *
 * The वापसed skb is pre-filled with some identअगरying data in
 * a way that any data that is put पूर्णांकo the skb (with skb_put(),
 * nla_put() or similar) will end up being within the
 * %NFC_ATTR_VENDOR_DATA attribute, so all that needs to be करोne
 * with the skb is adding data क्रम the corresponding userspace tool
 * which can then पढ़ो that data out of the venकरोr data attribute.
 * You must not modअगरy the skb in any other way.
 *
 * When करोne, call nfc_venकरोr_cmd_reply() with the skb and वापस
 * its error code as the result of the करोit() operation.
 *
 * Return: An allocated and pre-filled skb. %शून्य अगर any errors happen.
 */
अटल अंतरभूत काष्ठा sk_buff *
nfc_venकरोr_cmd_alloc_reply_skb(काष्ठा nfc_dev *dev,
				u32 oui, u32 subcmd, पूर्णांक approxlen)
अणु
	वापस __nfc_alloc_venकरोr_cmd_reply_skb(dev,
						NFC_ATTR_VENDOR_DATA,
						oui,
						subcmd, approxlen);
पूर्ण

#पूर्ण_अगर /* __NET_NFC_H */
