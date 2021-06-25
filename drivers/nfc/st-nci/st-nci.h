<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * NCI based Driver क्रम STMicroelectronics NFC Chip
 *
 * Copyright (C) 2014  STMicroelectronics SAS. All rights reserved.
 */

#अगर_अघोषित __LOCAL_ST_NCI_H_
#घोषणा __LOCAL_ST_NCI_H_

#समावेश "ndlc.h"

/* Define निजी flags: */
#घोषणा ST_NCI_RUNNING			1

#घोषणा ST_NCI_CORE_PROP                0x01
#घोषणा ST_NCI_SET_NFC_MODE             0x02

/*
 * ref ISO7816-3 chap 8.1. the initial अक्षरacter TS is followed by a
 * sequence of at most 32 अक्षरacters.
 */
#घोषणा ST_NCI_ESE_MAX_LENGTH  33

#घोषणा ST_NCI_DEVICE_MGNT_GATE		0x01

#घोषणा ST_NCI_VENDOR_OUI 0x0080E1 /* STMicroelectronics */
#घोषणा ST_NCI_FACTORY_MODE 2

काष्ठा nci_mode_set_cmd अणु
	u8 cmd_type;
	u8 mode;
पूर्ण __packed;

काष्ठा nci_mode_set_rsp अणु
	u8 status;
पूर्ण __packed;

काष्ठा st_nci_se_status अणु
	bool is_ese_present;
	bool is_uicc_present;
पूर्ण;

काष्ठा st_nci_se_info अणु
	काष्ठा st_nci_se_status *se_status;
	u8 atr[ST_NCI_ESE_MAX_LENGTH];
	काष्ठा completion req_completion;

	काष्ठा समयr_list bwi_समयr;
	पूर्णांक wt_समयout; /* in msecs */
	bool bwi_active;

	काष्ठा समयr_list se_active_समयr;
	bool se_active;

	bool xch_error;

	se_io_cb_t cb;
	व्योम *cb_context;
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
 * @HCI_DM_सूचीECT_LOAD: Allow to load a firmware पूर्णांकo the CLF. A complete
 *	packet can be more than 8KB.
 * @HCI_DM_RESET: Allow to run a CLF reset in order to "commit" CLF
 *	configuration changes without CLF घातer off.
 * @HCI_GET_PARAM: Allow to retrieve an HCI CLF parameter (क्रम example the
 *	white list).
 * @HCI_DM_FIELD_GENERATOR: Allow to generate dअगरferent kind of RF
 *	technology. When using this command to anti-collision is करोne.
 * @LOOPBACK: Allow to echo a command and test the Dh to CLF connectivity.
 * @HCI_DM_VDC_MEASUREMENT_VALUE: Allow to measure the field applied on the
 *	CLF antenna. A value between 0 and 0x0f is वापसed. 0 is maximum.
 * @HCI_DM_FWUPD_START: Allow to put CLF पूर्णांकo firmware update mode. It is a
 *	specअगरic CLF command as there is no GPIO क्रम this.
 * @HCI_DM_FWUPD_END:  Allow to complete firmware update.
 * @HCI_DM_VDC_VALUE_COMPARISON: Allow to compare the field applied on the
 *	CLF antenna to a reference value.
 * @MANUFACTURER_SPECIFIC: Allow to retrieve manufacturer specअगरic data
 *	received during a NCI_CORE_INIT_CMD.
 */
क्रमागत nfc_venकरोr_cmds अणु
	FACTORY_MODE,
	HCI_CLEAR_ALL_PIPES,
	HCI_DM_PUT_DATA,
	HCI_DM_UPDATE_AID,
	HCI_DM_GET_INFO,
	HCI_DM_GET_DATA,
	HCI_DM_सूचीECT_LOAD,
	HCI_DM_RESET,
	HCI_GET_PARAM,
	HCI_DM_FIELD_GENERATOR,
	LOOPBACK,
	HCI_DM_FWUPD_START,
	HCI_DM_FWUPD_END,
	HCI_DM_VDC_MEASUREMENT_VALUE,
	HCI_DM_VDC_VALUE_COMPARISON,
	MANUFACTURER_SPECIFIC,
पूर्ण;

काष्ठा st_nci_info अणु
	काष्ठा llt_ndlc *ndlc;
	अचिन्हित दीर्घ flags;

	काष्ठा st_nci_se_info se_info;
पूर्ण;

व्योम st_nci_हटाओ(काष्ठा nci_dev *ndev);
पूर्णांक st_nci_probe(काष्ठा llt_ndlc *ndlc, पूर्णांक phy_headroom,
		 पूर्णांक phy_tailroom, काष्ठा st_nci_se_status *se_status);

पूर्णांक st_nci_se_init(काष्ठा nci_dev *ndev, काष्ठा st_nci_se_status *se_status);
व्योम st_nci_se_deinit(काष्ठा nci_dev *ndev);

पूर्णांक st_nci_discover_se(काष्ठा nci_dev *ndev);
पूर्णांक st_nci_enable_se(काष्ठा nci_dev *ndev, u32 se_idx);
पूर्णांक st_nci_disable_se(काष्ठा nci_dev *ndev, u32 se_idx);
पूर्णांक st_nci_se_io(काष्ठा nci_dev *ndev, u32 se_idx,
				u8 *apdu, माप_प्रकार apdu_length,
				se_io_cb_t cb, व्योम *cb_context);
पूर्णांक st_nci_hci_load_session(काष्ठा nci_dev *ndev);
व्योम st_nci_hci_event_received(काष्ठा nci_dev *ndev, u8 pipe,
					u8 event, काष्ठा sk_buff *skb);
व्योम st_nci_hci_cmd_received(काष्ठा nci_dev *ndev, u8 pipe, u8 cmd,
						काष्ठा sk_buff *skb);

पूर्णांक st_nci_venकरोr_cmds_init(काष्ठा nci_dev *ndev);

#पूर्ण_अगर /* __LOCAL_ST_NCI_H_ */
