<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * NFC Digital Protocol stack
 * Copyright (c) 2013, Intel Corporation.
 */

#अगर_अघोषित __NFC_DIGITAL_H
#घोषणा __NFC_DIGITAL_H

#समावेश <linux/skbuff.h>
#समावेश <net/nfc/nfc.h>

/**
 * Configuration types क्रम in_configure_hw and tg_configure_hw.
 */
क्रमागत अणु
	NFC_DIGITAL_CONFIG_RF_TECH = 0,
	NFC_DIGITAL_CONFIG_FRAMING,
पूर्ण;

/**
 * RF technology values passed as param argument to in_configure_hw and
 * tg_configure_hw क्रम NFC_DIGITAL_CONFIG_RF_TECH configuration type.
 */
क्रमागत अणु
	NFC_DIGITAL_RF_TECH_106A = 0,
	NFC_DIGITAL_RF_TECH_212F,
	NFC_DIGITAL_RF_TECH_424F,
	NFC_DIGITAL_RF_TECH_ISO15693,
	NFC_DIGITAL_RF_TECH_106B,

	NFC_DIGITAL_RF_TECH_LAST,
पूर्ण;

/**
 * Framing configuration passed as param argument to in_configure_hw and
 * tg_configure_hw क्रम NFC_DIGITAL_CONFIG_FRAMING configuration type.
 */
क्रमागत अणु
	NFC_DIGITAL_FRAMING_NFCA_SHORT = 0,
	NFC_DIGITAL_FRAMING_NFCA_STANDARD,
	NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A,
	NFC_DIGITAL_FRAMING_NFCA_ANTICOL_COMPLETE,

	NFC_DIGITAL_FRAMING_NFCA_T1T,
	NFC_DIGITAL_FRAMING_NFCA_T2T,
	NFC_DIGITAL_FRAMING_NFCA_T4T,
	NFC_DIGITAL_FRAMING_NFCA_NFC_DEP,

	NFC_DIGITAL_FRAMING_NFCF,
	NFC_DIGITAL_FRAMING_NFCF_T3T,
	NFC_DIGITAL_FRAMING_NFCF_NFC_DEP,
	NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED,

	NFC_DIGITAL_FRAMING_ISO15693_INVENTORY,
	NFC_DIGITAL_FRAMING_ISO15693_T5T,

	NFC_DIGITAL_FRAMING_NFCB,
	NFC_DIGITAL_FRAMING_NFCB_T4T,

	NFC_DIGITAL_FRAMING_LAST,
पूर्ण;

#घोषणा DIGITAL_MDAA_NFCID1_SIZE 3

काष्ठा digital_tg_mdaa_params अणु
	u16 sens_res;
	u8 nfcid1[DIGITAL_MDAA_NFCID1_SIZE];
	u8 sel_res;

	u8 nfcid2[NFC_NFCID2_MAXSIZE];
	u16 sc;
पूर्ण;

काष्ठा nfc_digital_dev;

/**
 * nfc_digital_cmd_complete_t - Definition of command result callback
 *
 * @ddev: nfc_digital_device ref
 * @arg: user data
 * @resp: response data
 *
 * resp poपूर्णांकer can be an error code and will be checked with IS_ERR() macro.
 * The callback is responsible क्रम मुक्तing resp sk_buff.
 */
प्रकार व्योम (*nfc_digital_cmd_complete_t)(काष्ठा nfc_digital_dev *ddev,
					   व्योम *arg, काष्ठा sk_buff *resp);

/**
 * Device side NFC Digital operations
 *
 * Initiator mode:
 * @in_configure_hw: Hardware configuration क्रम RF technology and communication
 *	framing in initiator mode. This is a synchronous function.
 * @in_send_cmd: Initiator mode data exchange using RF technology and framing
 *	previously set with in_configure_hw. The peer response is वापसed
 *	through callback cb. If an io error occurs or the peer didn't reply
 *	within the specअगरied समयout (ms), the error code is passed back through
 *	the resp poपूर्णांकer. This is an asynchronous function.
 *
 * Target mode: Only NFC-DEP protocol is supported in target mode.
 * @tg_configure_hw: Hardware configuration क्रम RF technology and communication
 *	framing in target mode. This is a synchronous function.
 * @tg_send_cmd: Target mode data exchange using RF technology and framing
 *	previously set with tg_configure_hw. The peer next command is वापसed
 *	through callback cb. If an io error occurs or the peer didn't reply
 *	within the specअगरied समयout (ms), the error code is passed back through
 *	the resp poपूर्णांकer. This is an asynchronous function.
 * @tg_listen: Put the device in listen mode रुकोing क्रम data from the peer
 *	device. This is an asynchronous function.
 * @tg_listen_mdaa: If supported, put the device in स्वतःmatic listen mode with
 *	mode detection and स्वतःmatic anti-collision. In this mode, the device
 *	स्वतःmatically detects the RF technology and executes the anti-collision
 *	detection using the command responses specअगरied in mdaa_params. The
 *	mdaa_params काष्ठाure contains SENS_RES, NFCID1, and SEL_RES क्रम 106A RF
 *	tech. NFCID2 and प्रणाली code (sc) क्रम 212F and 424F. The driver वापसs
 *	the NFC-DEP ATR_REQ command through cb. The digital stack deducts the RF
 *	tech by analyzing the SoD of the frame containing the ATR_REQ command.
 *	This is an asynchronous function.
 * @tg_listen_md: If supported, put the device in स्वतःmatic listen mode with
 *	mode detection but without स्वतःmatic anti-collision. In this mode, the
 *	device स्वतःmatically detects the RF technology.  What the actual
 *	RF technology is can be retrieved by calling @tg_get_rf_tech.
 *	The digital stack will then perक्रमm the appropriate anti-collision
 *	sequence.  This is an asynchronous function.
 * @tg_get_rf_tech: Required when @tg_listen_md is supported, unused otherwise.
 *	Return the RF Technology that was detected by the @tg_listen_md call.
 *	This is a synchronous function.
 *
 * @चयन_rf: Turns device radio on or off. The stack करोes not call explicitly
 *	चयन_rf to turn the radio on. A call to in|tg_configure_hw must turn
 *	the device radio on.
 * @पात_cmd: Discard the last sent command.
 *
 * Notes: Asynchronous functions have a समयout parameter. It is the driver
 *	responsibility to call the digital stack back through the
 *	nfc_digital_cmd_complete_t callback when no RF respsonse has been
 *	received within the specअगरied समय (in milliseconds). In that हाल the
 *	driver must set the resp sk_buff to ERR_PTR(-ETIMEDOUT).
 *	Since the digital stack serializes commands to be sent, it's mandatory
 *	क्रम the driver to handle the समयout correctly. Otherwise the stack
 *	would not be able to send new commands, रुकोing क्रम the reply of the
 *	current one.
 */
काष्ठा nfc_digital_ops अणु
	पूर्णांक (*in_configure_hw)(काष्ठा nfc_digital_dev *ddev, पूर्णांक type,
			       पूर्णांक param);
	पूर्णांक (*in_send_cmd)(काष्ठा nfc_digital_dev *ddev, काष्ठा sk_buff *skb,
			   u16 समयout, nfc_digital_cmd_complete_t cb,
			   व्योम *arg);

	पूर्णांक (*tg_configure_hw)(काष्ठा nfc_digital_dev *ddev, पूर्णांक type,
			       पूर्णांक param);
	पूर्णांक (*tg_send_cmd)(काष्ठा nfc_digital_dev *ddev, काष्ठा sk_buff *skb,
			   u16 समयout, nfc_digital_cmd_complete_t cb,
			   व्योम *arg);
	पूर्णांक (*tg_listen)(काष्ठा nfc_digital_dev *ddev, u16 समयout,
			 nfc_digital_cmd_complete_t cb, व्योम *arg);
	पूर्णांक (*tg_listen_mdaa)(काष्ठा nfc_digital_dev *ddev,
			      काष्ठा digital_tg_mdaa_params *mdaa_params,
			      u16 समयout, nfc_digital_cmd_complete_t cb,
			      व्योम *arg);
	पूर्णांक (*tg_listen_md)(काष्ठा nfc_digital_dev *ddev, u16 समयout,
			    nfc_digital_cmd_complete_t cb, व्योम *arg);
	पूर्णांक (*tg_get_rf_tech)(काष्ठा nfc_digital_dev *ddev, u8 *rf_tech);

	पूर्णांक (*चयन_rf)(काष्ठा nfc_digital_dev *ddev, bool on);
	व्योम (*पात_cmd)(काष्ठा nfc_digital_dev *ddev);
पूर्ण;

#घोषणा NFC_DIGITAL_POLL_MODE_COUNT_MAX	6 /* 106A, 212F, and 424F in & tg */

प्रकार पूर्णांक (*digital_poll_t)(काष्ठा nfc_digital_dev *ddev, u8 rf_tech);

काष्ठा digital_poll_tech अणु
	u8 rf_tech;
	digital_poll_t poll_func;
पूर्ण;

/**
 * Driver capabilities - bit mask made of the following values
 *
 * @NFC_DIGITAL_DRV_CAPS_IN_CRC: The driver handles CRC calculation in initiator
 *	mode.
 * @NFC_DIGITAL_DRV_CAPS_TG_CRC: The driver handles CRC calculation in target
 *	mode.
 */
#घोषणा NFC_DIGITAL_DRV_CAPS_IN_CRC	0x0001
#घोषणा NFC_DIGITAL_DRV_CAPS_TG_CRC	0x0002

काष्ठा nfc_digital_dev अणु
	काष्ठा nfc_dev *nfc_dev;
	काष्ठा nfc_digital_ops *ops;

	u32 protocols;

	पूर्णांक tx_headroom;
	पूर्णांक tx_tailroom;

	u32 driver_capabilities;
	व्योम *driver_data;

	काष्ठा digital_poll_tech poll_techs[NFC_DIGITAL_POLL_MODE_COUNT_MAX];
	u8 poll_tech_count;
	u8 poll_tech_index;
	काष्ठा mutex poll_lock;

	काष्ठा work_काष्ठा cmd_work;
	काष्ठा work_काष्ठा cmd_complete_work;
	काष्ठा list_head cmd_queue;
	काष्ठा mutex cmd_lock;

	काष्ठा delayed_work poll_work;

	u8 curr_protocol;
	u8 curr_rf_tech;
	u8 curr_nfc_dep_pni;
	u8 did;
	u16 dep_rwt;

	u8 local_payload_max;
	u8 remote_payload_max;

	काष्ठा sk_buff *chaining_skb;
	काष्ठा digital_data_exch *data_exch;

	पूर्णांक atn_count;
	पूर्णांक nack_count;

	काष्ठा sk_buff *saved_skb;

	u16 target_fsc;

	पूर्णांक (*skb_check_crc)(काष्ठा sk_buff *skb);
	व्योम (*skb_add_crc)(काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा nfc_digital_dev *nfc_digital_allocate_device(काष्ठा nfc_digital_ops *ops,
						    __u32 supported_protocols,
						    __u32 driver_capabilities,
						    पूर्णांक tx_headroom,
						    पूर्णांक tx_tailroom);
व्योम nfc_digital_मुक्त_device(काष्ठा nfc_digital_dev *ndev);
पूर्णांक nfc_digital_रेजिस्टर_device(काष्ठा nfc_digital_dev *ndev);
व्योम nfc_digital_unरेजिस्टर_device(काष्ठा nfc_digital_dev *ndev);

अटल अंतरभूत व्योम nfc_digital_set_parent_dev(काष्ठा nfc_digital_dev *ndev,
					      काष्ठा device *dev)
अणु
	nfc_set_parent_dev(ndev->nfc_dev, dev);
पूर्ण

अटल अंतरभूत व्योम nfc_digital_set_drvdata(काष्ठा nfc_digital_dev *dev,
					   व्योम *data)
अणु
	dev->driver_data = data;
पूर्ण

अटल अंतरभूत व्योम *nfc_digital_get_drvdata(काष्ठा nfc_digital_dev *dev)
अणु
	वापस dev->driver_data;
पूर्ण

#पूर्ण_अगर /* __NFC_DIGITAL_H */
