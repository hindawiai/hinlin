<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * NFC Digital Protocol stack
 * Copyright (c) 2013, Intel Corporation.
 */

#अगर_अघोषित __DIGITAL_H
#घोषणा __DIGITAL_H

#समावेश <net/nfc/nfc.h>
#समावेश <net/nfc/digital.h>

#समावेश <linux/crc-ccitt.h>
#समावेश <linux/crc-itu-t.h>

#घोषणा PROTOCOL_ERR(req) pr_err("%d: NFC Digital Protocol error: %s\n", \
				 __LINE__, req)

#घोषणा DIGITAL_CMD_IN_SEND        0
#घोषणा DIGITAL_CMD_TG_SEND        1
#घोषणा DIGITAL_CMD_TG_LISTEN      2
#घोषणा DIGITAL_CMD_TG_LISTEN_MDAA 3
#घोषणा DIGITAL_CMD_TG_LISTEN_MD   4

#घोषणा DIGITAL_MAX_HEADER_LEN 7
#घोषणा DIGITAL_CRC_LEN        2

#घोषणा DIGITAL_SENSF_NFCID2_NFC_DEP_B1 0x01
#घोषणा DIGITAL_SENSF_NFCID2_NFC_DEP_B2 0xFE

#घोषणा DIGITAL_SENS_RES_NFC_DEP 0x0100
#घोषणा DIGITAL_SEL_RES_NFC_DEP  0x40
#घोषणा DIGITAL_SENSF_FELICA_SC  0xFFFF

#घोषणा DIGITAL_DRV_CAPS_IN_CRC(ddev) \
	((ddev)->driver_capabilities & NFC_DIGITAL_DRV_CAPS_IN_CRC)
#घोषणा DIGITAL_DRV_CAPS_TG_CRC(ddev) \
	((ddev)->driver_capabilities & NFC_DIGITAL_DRV_CAPS_TG_CRC)

काष्ठा digital_data_exch अणु
	data_exchange_cb_t cb;
	व्योम *cb_context;
पूर्ण;

काष्ठा sk_buff *digital_skb_alloc(काष्ठा nfc_digital_dev *ddev,
				  अचिन्हित पूर्णांक len);

पूर्णांक digital_send_cmd(काष्ठा nfc_digital_dev *ddev, u8 cmd_type,
		     काष्ठा sk_buff *skb, काष्ठा digital_tg_mdaa_params *params,
		     u16 समयout, nfc_digital_cmd_complete_t cmd_cb,
		     व्योम *cb_context);

पूर्णांक digital_in_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type, पूर्णांक param);
अटल अंतरभूत पूर्णांक digital_in_send_cmd(काष्ठा nfc_digital_dev *ddev,
				      काष्ठा sk_buff *skb, u16 समयout,
				      nfc_digital_cmd_complete_t cmd_cb,
				      व्योम *cb_context)
अणु
	वापस digital_send_cmd(ddev, DIGITAL_CMD_IN_SEND, skb, शून्य, समयout,
				cmd_cb, cb_context);
पूर्ण

व्योम digital_poll_next_tech(काष्ठा nfc_digital_dev *ddev);

पूर्णांक digital_in_send_sens_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech);
पूर्णांक digital_in_send_sensb_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech);
पूर्णांक digital_in_send_sensf_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech);
पूर्णांक digital_in_send_iso15693_inv_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech);

पूर्णांक digital_in_iso_dep_pull_sod(काष्ठा nfc_digital_dev *ddev,
				काष्ठा sk_buff *skb);
पूर्णांक digital_in_iso_dep_push_sod(काष्ठा nfc_digital_dev *ddev,
				काष्ठा sk_buff *skb);

पूर्णांक digital_target_found(काष्ठा nfc_digital_dev *ddev,
			 काष्ठा nfc_target *target, u8 protocol);

पूर्णांक digital_in_recv_mअगरare_res(काष्ठा sk_buff *resp);

पूर्णांक digital_in_send_atr_req(काष्ठा nfc_digital_dev *ddev,
			    काष्ठा nfc_target *target, __u8 comm_mode, __u8 *gb,
			    माप_प्रकार gb_len);
पूर्णांक digital_in_send_dep_req(काष्ठा nfc_digital_dev *ddev,
			    काष्ठा nfc_target *target, काष्ठा sk_buff *skb,
			    काष्ठा digital_data_exch *data_exch);

पूर्णांक digital_tg_configure_hw(काष्ठा nfc_digital_dev *ddev, पूर्णांक type, पूर्णांक param);
अटल अंतरभूत पूर्णांक digital_tg_send_cmd(काष्ठा nfc_digital_dev *ddev,
			काष्ठा sk_buff *skb, u16 समयout,
			nfc_digital_cmd_complete_t cmd_cb, व्योम *cb_context)
अणु
	वापस digital_send_cmd(ddev, DIGITAL_CMD_TG_SEND, skb, शून्य, समयout,
				cmd_cb, cb_context);
पूर्ण

व्योम digital_tg_recv_sens_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			      काष्ठा sk_buff *resp);

व्योम digital_tg_recv_sensf_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			       काष्ठा sk_buff *resp);

अटल अंतरभूत पूर्णांक digital_tg_listen(काष्ठा nfc_digital_dev *ddev, u16 समयout,
				    nfc_digital_cmd_complete_t cb, व्योम *arg)
अणु
	वापस digital_send_cmd(ddev, DIGITAL_CMD_TG_LISTEN, शून्य, शून्य,
				समयout, cb, arg);
पूर्ण

व्योम digital_tg_recv_atr_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			     काष्ठा sk_buff *resp);

पूर्णांक digital_tg_send_dep_res(काष्ठा nfc_digital_dev *ddev, काष्ठा sk_buff *skb);

पूर्णांक digital_tg_listen_nfca(काष्ठा nfc_digital_dev *ddev, u8 rf_tech);
पूर्णांक digital_tg_listen_nfcf(काष्ठा nfc_digital_dev *ddev, u8 rf_tech);
व्योम digital_tg_recv_md_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			    काष्ठा sk_buff *resp);

प्रकार u16 (*crc_func_t)(u16, स्थिर u8 *, माप_प्रकार);

#घोषणा CRC_A_INIT 0x6363
#घोषणा CRC_B_INIT 0xFFFF
#घोषणा CRC_F_INIT 0x0000

व्योम digital_skb_add_crc(काष्ठा sk_buff *skb, crc_func_t crc_func, u16 init,
			 u8 bitwise_inv, u8 msb_first);

अटल अंतरभूत व्योम digital_skb_add_crc_a(काष्ठा sk_buff *skb)
अणु
	digital_skb_add_crc(skb, crc_ccitt, CRC_A_INIT, 0, 0);
पूर्ण

अटल अंतरभूत व्योम digital_skb_add_crc_b(काष्ठा sk_buff *skb)
अणु
	digital_skb_add_crc(skb, crc_ccitt, CRC_B_INIT, 1, 0);
पूर्ण

अटल अंतरभूत व्योम digital_skb_add_crc_f(काष्ठा sk_buff *skb)
अणु
	digital_skb_add_crc(skb, crc_itu_t, CRC_F_INIT, 0, 1);
पूर्ण

अटल अंतरभूत व्योम digital_skb_add_crc_none(काष्ठा sk_buff *skb)
अणु
	वापस;
पूर्ण

पूर्णांक digital_skb_check_crc(काष्ठा sk_buff *skb, crc_func_t crc_func,
			  u16 crc_init, u8 bitwise_inv, u8 msb_first);

अटल अंतरभूत पूर्णांक digital_skb_check_crc_a(काष्ठा sk_buff *skb)
अणु
	वापस digital_skb_check_crc(skb, crc_ccitt, CRC_A_INIT, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक digital_skb_check_crc_b(काष्ठा sk_buff *skb)
अणु
	वापस digital_skb_check_crc(skb, crc_ccitt, CRC_B_INIT, 1, 0);
पूर्ण

अटल अंतरभूत पूर्णांक digital_skb_check_crc_f(काष्ठा sk_buff *skb)
अणु
	वापस digital_skb_check_crc(skb, crc_itu_t, CRC_F_INIT, 0, 1);
पूर्ण

अटल अंतरभूत पूर्णांक digital_skb_check_crc_none(काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __DIGITAL_H */
