<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014  STMicroelectronics SAS. All rights reserved.
 */

#अगर_अघोषित __LOCAL_ST21NFCA_H_
#घोषणा __LOCAL_ST21NFCA_H_

#समावेश <net/nfc/hci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>

#घोषणा HCI_MODE 0

/* framing in HCI mode */
#घोषणा ST21NFCA_SOF_खातापूर्ण_LEN    2

/* Almost every समय value is 0 */
#घोषणा ST21NFCA_HCI_LLC_LEN    1

/* Size in worst हाल :
 * In normal हाल CRC len = 2 but byte stuffing
 * may appear in हाल one CRC byte = ST21NFCA_SOF_खातापूर्ण
 */
#घोषणा ST21NFCA_HCI_LLC_CRC    4

#घोषणा ST21NFCA_HCI_LLC_LEN_CRC        (ST21NFCA_SOF_खातापूर्ण_LEN + \
						ST21NFCA_HCI_LLC_LEN + \
						ST21NFCA_HCI_LLC_CRC)
#घोषणा ST21NFCA_HCI_LLC_MIN_SIZE       (1 + ST21NFCA_HCI_LLC_LEN_CRC)

/* Worst हाल when adding byte stuffing between each byte */
#घोषणा ST21NFCA_HCI_LLC_MAX_PAYLOAD    29
#घोषणा ST21NFCA_HCI_LLC_MAX_SIZE       (ST21NFCA_HCI_LLC_LEN_CRC + 1 + \
					ST21NFCA_HCI_LLC_MAX_PAYLOAD)

/* Reader RF commands */
#घोषणा ST21NFCA_WR_XCHG_DATA           0x10

#घोषणा ST21NFCA_DEVICE_MGNT_GATE       0x01
#घोषणा ST21NFCA_RF_READER_F_GATE       0x14
#घोषणा ST21NFCA_RF_CARD_F_GATE		0x24
#घोषणा ST21NFCA_APDU_READER_GATE	0xf0
#घोषणा ST21NFCA_CONNECTIVITY_GATE	0x41

/*
 * ref ISO7816-3 chap 8.1. the initial अक्षरacter TS is followed by a
 * sequence of at most 32 अक्षरacters.
 */
#घोषणा ST21NFCA_ESE_MAX_LENGTH		33
#घोषणा ST21NFCA_ESE_HOST_ID		0xc0

#घोषणा DRIVER_DESC "HCI NFC driver for ST21NFCA"

#घोषणा ST21NFCA_HCI_MODE		0
#घोषणा ST21NFCA_NUM_DEVICES		256

#घोषणा ST21NFCA_VENDOR_OUI		0x0080E1 /* STMicroelectronics */
#घोषणा ST21NFCA_FACTORY_MODE		2

काष्ठा st21nfca_se_status अणु
	bool is_ese_present;
	bool is_uicc_present;
पूर्ण;

क्रमागत st21nfca_state अणु
	ST21NFCA_ST_COLD,
	ST21NFCA_ST_READY,
पूर्ण;

/**
 * क्रमागत nfc_venकरोr_cmds - supported nfc venकरोr commands
 *
 * @FACTORY_MODE: Allow to set the driver पूर्णांकo a mode where no secure element
 *	are activated. It करोes not consider any NFC_ATTR_VENDOR_DATA.
 * @HCI_CLEAR_ALL_PIPES: Allow to execute a HCI clear all pipes command.
 *	It करोes not consider any NFC_ATTR_VENDOR_DATA.
 * @HCI_DM_PUT_DATA: Allow to configure specअगरic CLF registry as क्रम example
 *	RF trimmings or low level drivers configurations (I2C, SPI, SWP).
 * @HCI_DM_UPDATE_AID: Allow to configure an AID routing पूर्णांकo the CLF routing
 *	table following RF technology, CLF mode or protocol.
 * @HCI_DM_GET_INFO: Allow to retrieve CLF inक्रमmation.
 * @HCI_DM_GET_DATA: Allow to retrieve CLF configurable data such as low
 *	level drivers configurations or RF trimmings.
 * @HCI_DM_LOAD: Allow to load a firmware पूर्णांकo the CLF. A complete
 *	packet can be more than 8KB.
 * @HCI_DM_RESET: Allow to run a CLF reset in order to "commit" CLF
 *	configuration changes without CLF घातer off.
 * @HCI_GET_PARAM: Allow to retrieve an HCI CLF parameter (क्रम example the
 *	white list).
 * @HCI_DM_FIELD_GENERATOR: Allow to generate dअगरferent kind of RF
 *	technology. When using this command to anti-collision is करोne.
 * @HCI_LOOPBACK: Allow to echo a command and test the Dh to CLF
 *	connectivity.
 */
क्रमागत nfc_venकरोr_cmds अणु
	FACTORY_MODE,
	HCI_CLEAR_ALL_PIPES,
	HCI_DM_PUT_DATA,
	HCI_DM_UPDATE_AID,
	HCI_DM_GET_INFO,
	HCI_DM_GET_DATA,
	HCI_DM_LOAD,
	HCI_DM_RESET,
	HCI_GET_PARAM,
	HCI_DM_FIELD_GENERATOR,
	HCI_LOOPBACK,
पूर्ण;

काष्ठा st21nfca_venकरोr_info अणु
	काष्ठा completion req_completion;
	काष्ठा sk_buff *rx_skb;
पूर्ण;

काष्ठा st21nfca_dep_info अणु
	काष्ठा sk_buff *tx_pending;
	काष्ठा work_काष्ठा tx_work;
	u8 curr_nfc_dep_pni;
	u32 idx;
	u8 to;
	u8 did;
	u8 bsi;
	u8 bri;
	u8 lri;
पूर्ण __packed;

काष्ठा st21nfca_se_info अणु
	u8 atr[ST21NFCA_ESE_MAX_LENGTH];
	काष्ठा completion req_completion;

	काष्ठा समयr_list bwi_समयr;
	पूर्णांक wt_समयout; /* in msecs */
	bool bwi_active;

	काष्ठा समयr_list se_active_समयr;
	bool se_active;
	पूर्णांक expected_pipes;
	पूर्णांक count_pipes;

	bool xch_error;

	se_io_cb_t cb;
	व्योम *cb_context;
पूर्ण;

काष्ठा st21nfca_hci_info अणु
	काष्ठा nfc_phy_ops *phy_ops;
	व्योम *phy_id;

	काष्ठा nfc_hci_dev *hdev;
	काष्ठा st21nfca_se_status *se_status;

	क्रमागत st21nfca_state state;

	काष्ठा mutex info_lock;

	पूर्णांक async_cb_type;
	data_exchange_cb_t async_cb;
	व्योम *async_cb_context;

	काष्ठा st21nfca_dep_info dep_info;
	काष्ठा st21nfca_se_info se_info;
	काष्ठा st21nfca_venकरोr_info venकरोr_info;
पूर्ण;

पूर्णांक st21nfca_hci_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops,
		       अक्षर *llc_name, पूर्णांक phy_headroom, पूर्णांक phy_tailroom,
		       पूर्णांक phy_payload, काष्ठा nfc_hci_dev **hdev,
		       काष्ठा st21nfca_se_status *se_status);
व्योम st21nfca_hci_हटाओ(काष्ठा nfc_hci_dev *hdev);

पूर्णांक st21nfca_dep_event_received(काष्ठा nfc_hci_dev *hdev,
				u8 event, काष्ठा sk_buff *skb);
पूर्णांक st21nfca_पंचांग_send_dep_res(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb);

पूर्णांक st21nfca_im_send_atr_req(काष्ठा nfc_hci_dev *hdev, u8 *gb, माप_प्रकार gb_len);
पूर्णांक st21nfca_im_send_dep_req(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb);
व्योम st21nfca_dep_init(काष्ठा nfc_hci_dev *hdev);
व्योम st21nfca_dep_deinit(काष्ठा nfc_hci_dev *hdev);

पूर्णांक st21nfca_connectivity_event_received(काष्ठा nfc_hci_dev *hdev, u8 host,
					u8 event, काष्ठा sk_buff *skb);
पूर्णांक st21nfca_apdu_पढ़ोer_event_received(काष्ठा nfc_hci_dev *hdev,
					u8 event, काष्ठा sk_buff *skb);

पूर्णांक st21nfca_hci_discover_se(काष्ठा nfc_hci_dev *hdev);
पूर्णांक st21nfca_hci_enable_se(काष्ठा nfc_hci_dev *hdev, u32 se_idx);
पूर्णांक st21nfca_hci_disable_se(काष्ठा nfc_hci_dev *hdev, u32 se_idx);
पूर्णांक st21nfca_hci_se_io(काष्ठा nfc_hci_dev *hdev, u32 se_idx,
		u8 *apdu, माप_प्रकार apdu_length,
		se_io_cb_t cb, व्योम *cb_context);

व्योम st21nfca_se_init(काष्ठा nfc_hci_dev *hdev);
व्योम st21nfca_se_deinit(काष्ठा nfc_hci_dev *hdev);

पूर्णांक st21nfca_hci_loopback_event_received(काष्ठा nfc_hci_dev *ndev, u8 event,
					 काष्ठा sk_buff *skb);
पूर्णांक st21nfca_venकरोr_cmds_init(काष्ठा nfc_hci_dev *ndev);

#पूर्ण_अगर /* __LOCAL_ST21NFCA_H_ */
