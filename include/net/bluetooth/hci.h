<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#अगर_अघोषित __HCI_H
#घोषणा __HCI_H

#घोषणा HCI_MAX_ACL_SIZE	1024
#घोषणा HCI_MAX_SCO_SIZE	255
#घोषणा HCI_MAX_ISO_SIZE	251
#घोषणा HCI_MAX_EVENT_SIZE	260
#घोषणा HCI_MAX_FRAME_SIZE	(HCI_MAX_ACL_SIZE + 4)

#घोषणा HCI_LINK_KEY_SIZE	16
#घोषणा HCI_AMP_LINK_KEY_SIZE	(2 * HCI_LINK_KEY_SIZE)

#घोषणा HCI_MAX_AMP_ASSOC_SIZE	672

#घोषणा HCI_MAX_CSB_DATA_SIZE	252

/* HCI dev events */
#घोषणा HCI_DEV_REG			1
#घोषणा HCI_DEV_UNREG			2
#घोषणा HCI_DEV_UP			3
#घोषणा HCI_DEV_DOWN			4
#घोषणा HCI_DEV_SUSPEND			5
#घोषणा HCI_DEV_RESUME			6
#घोषणा HCI_DEV_OPEN			7
#घोषणा HCI_DEV_CLOSE			8
#घोषणा HCI_DEV_SETUP			9

/* HCI notअगरy events */
#घोषणा HCI_NOTIFY_CONN_ADD		1
#घोषणा HCI_NOTIFY_CONN_DEL		2
#घोषणा HCI_NOTIFY_VOICE_SETTING	3
#घोषणा HCI_NOTIFY_ENABLE_SCO_CVSD	4
#घोषणा HCI_NOTIFY_ENABLE_SCO_TRANSP	5
#घोषणा HCI_NOTIFY_DISABLE_SCO		6

/* HCI bus types */
#घोषणा HCI_VIRTUAL	0
#घोषणा HCI_USB		1
#घोषणा HCI_PCCARD	2
#घोषणा HCI_UART	3
#घोषणा HCI_RS232	4
#घोषणा HCI_PCI		5
#घोषणा HCI_SDIO	6
#घोषणा HCI_SPI		7
#घोषणा HCI_I2C		8
#घोषणा HCI_SMD		9
#घोषणा HCI_VIRTIO	10

/* HCI controller types */
#घोषणा HCI_PRIMARY	0x00
#घोषणा HCI_AMP		0x01

/* First BR/EDR Controller shall have ID = 0 */
#घोषणा AMP_ID_BREDR	0x00

/* AMP controller types */
#घोषणा AMP_TYPE_BREDR	0x00
#घोषणा AMP_TYPE_80211	0x01

/* AMP controller status */
#घोषणा AMP_STATUS_POWERED_DOWN			0x00
#घोषणा AMP_STATUS_BLUETOOTH_ONLY		0x01
#घोषणा AMP_STATUS_NO_CAPACITY			0x02
#घोषणा AMP_STATUS_LOW_CAPACITY			0x03
#घोषणा AMP_STATUS_MEDIUM_CAPACITY		0x04
#घोषणा AMP_STATUS_HIGH_CAPACITY		0x05
#घोषणा AMP_STATUS_FULL_CAPACITY		0x06

/* HCI device quirks */
क्रमागत अणु
	/* When this quirk is set, the HCI Reset command is send when
	 * closing the transport instead of when खोलोing it.
	 *
	 * This quirk must be set beक्रमe hci_रेजिस्टर_dev is called.
	 */
	HCI_QUIRK_RESET_ON_CLOSE,

	/* When this quirk is set, the device is turned पूर्णांकo a raw-only
	 * device and it will stay in unconfigured state.
	 *
	 * This quirk must be set beक्रमe hci_रेजिस्टर_dev is called.
	 */
	HCI_QUIRK_RAW_DEVICE,

	/* When this quirk is set, the buffer sizes reported by
	 * HCI Read Buffer Size command are corrected अगर invalid.
	 *
	 * This quirk must be set beक्रमe hci_रेजिस्टर_dev is called.
	 */
	HCI_QUIRK_FIXUP_BUFFER_SIZE,

	/* When this quirk is set, then a controller that करोes not
	 * indicate support क्रम Inquiry Result with RSSI is assumed to
	 * support it anyway. Some early Bluetooth 1.2 controllers had
	 * wrongly configured local features that will require क्रमcing
	 * them to enable this mode. Getting RSSI inक्रमmation with the
	 * inquiry responses is preferred since it allows क्रम a better
	 * user experience.
	 *
	 * This quirk must be set beक्रमe hci_रेजिस्टर_dev is called.
	 */
	HCI_QUIRK_FIXUP_INQUIRY_MODE,

	/* When this quirk is set, then the HCI Read Local Supported
	 * Commands command is not supported. In general Bluetooth 1.2
	 * and later controllers should support this command. However
	 * some controllers indicate Bluetooth 1.2 support, but करो
	 * not support this command.
	 *
	 * This quirk must be set beक्रमe hci_रेजिस्टर_dev is called.
	 */
	HCI_QUIRK_BROKEN_LOCAL_COMMANDS,

	/* When this quirk is set, then no stored link key handling
	 * is perक्रमmed. This is मुख्यly due to the fact that the
	 * HCI Delete Stored Link Key command is advertised, but
	 * not supported.
	 *
	 * This quirk must be set beक्रमe hci_रेजिस्टर_dev is called.
	 */
	HCI_QUIRK_BROKEN_STORED_LINK_KEY,

	/* When this quirk is set, an बाह्यal configuration step
	 * is required and will be indicated with the controller
	 * configuration.
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 */
	HCI_QUIRK_EXTERNAL_CONFIG,

	/* When this quirk is set, the खुला Bluetooth address
	 * initially reported by HCI Read BD Address command
	 * is considered invalid. Controller configuration is
	 * required beक्रमe this device can be used.
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 */
	HCI_QUIRK_INVALID_BDADDR,

	/* When this quirk is set, the खुला Bluetooth address
	 * initially reported by HCI Read BD Address command
	 * is considered invalid. The खुला BD Address can be
	 * specअगरied in the fwnode property 'local-bd-address'.
	 * If this property करोes not exist or is invalid controller
	 * configuration is required beक्रमe this device can be used.
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 */
	HCI_QUIRK_USE_BDADDR_PROPERTY,

	/* When this quirk is set, the duplicate filtering during
	 * scanning is based on Bluetooth devices addresses. To allow
	 * RSSI based updates, restart scanning अगर needed.
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 */
	HCI_QUIRK_STRICT_DUPLICATE_FILTER,

	/* When this quirk is set, LE scan and BR/EDR inquiry is करोne
	 * simultaneously, otherwise it's पूर्णांकerleaved.
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 */
	HCI_QUIRK_SIMULTANEOUS_DISCOVERY,

	/* When this quirk is set, the enabling of diagnostic mode is
	 * not persistent over HCI Reset. Every समय the controller
	 * is brought up it needs to be reprogrammed.
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 */
	HCI_QUIRK_NON_PERSISTENT_DIAG,

	/* When this quirk is set, setup() would be run after every
	 * खोलो() and not just after the first खोलो().
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 *
	 */
	HCI_QUIRK_NON_PERSISTENT_SETUP,

	/* When this quirk is set, wide band speech is supported by
	 * the driver since no reliable mechanism exist to report
	 * this from the hardware, a driver flag is use to convey
	 * this support
	 *
	 * This quirk must be set beक्रमe hci_रेजिस्टर_dev is called.
	 */
	HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED,

	/* When this quirk is set, the controller has validated that
	 * LE states reported through the HCI_LE_READ_SUPPORTED_STATES are
	 * valid.  This mechanism is necessary as many controllers have
	 * been seen has having trouble initiating a connectable
	 * advertisement despite the state combination being reported as
	 * supported.
	 */
	HCI_QUIRK_VALID_LE_STATES,

	/* When this quirk is set, then erroneous data reporting
	 * is ignored. This is मुख्यly due to the fact that the HCI
	 * Read Default Erroneous Data Reporting command is advertised,
	 * but not supported; these controllers often reply with unknown
	 * command and tend to lock up अक्रमomly. Needing a hard reset.
	 *
	 * This quirk can be set beक्रमe hci_रेजिस्टर_dev is called or
	 * during the hdev->setup venकरोr callback.
	 */
	HCI_QUIRK_BROKEN_ERR_DATA_REPORTING,

	/*
	 * When this quirk is set, then the hci_suspend_notअगरier is not
	 * रेजिस्टरed. This is पूर्णांकended क्रम devices which drop completely
	 * from the bus on प्रणाली-suspend and which will show up as a new
	 * HCI after resume.
	 */
	HCI_QUIRK_NO_SUSPEND_NOTIFIER,
पूर्ण;

/* HCI device flags */
क्रमागत अणु
	HCI_UP,
	HCI_INIT,
	HCI_RUNNING,

	HCI_PSCAN,
	HCI_ISCAN,
	HCI_AUTH,
	HCI_ENCRYPT,
	HCI_INQUIRY,

	HCI_RAW,

	HCI_RESET,
पूर्ण;

/* HCI socket flags */
क्रमागत अणु
	HCI_SOCK_TRUSTED,
	HCI_MGMT_INDEX_EVENTS,
	HCI_MGMT_UNCONF_INDEX_EVENTS,
	HCI_MGMT_EXT_INDEX_EVENTS,
	HCI_MGMT_EXT_INFO_EVENTS,
	HCI_MGMT_OPTION_EVENTS,
	HCI_MGMT_SETTING_EVENTS,
	HCI_MGMT_DEV_CLASS_EVENTS,
	HCI_MGMT_LOCAL_NAME_EVENTS,
	HCI_MGMT_OOB_DATA_EVENTS,
	HCI_MGMT_EXP_FEATURE_EVENTS,
पूर्ण;

/*
 * BR/EDR and/or LE controller flags: the flags defined here should represent
 * states from the controller.
 */
क्रमागत अणु
	HCI_SETUP,
	HCI_CONFIG,
	HCI_AUTO_OFF,
	HCI_RFKILLED,
	HCI_MGMT,
	HCI_BONDABLE,
	HCI_SERVICE_CACHE,
	HCI_KEEP_DEBUG_KEYS,
	HCI_USE_DEBUG_KEYS,
	HCI_UNREGISTER,
	HCI_UNCONFIGURED,
	HCI_USER_CHANNEL,
	HCI_EXT_CONFIGURED,
	HCI_LE_ADV,
	HCI_LE_SCAN,
	HCI_SSP_ENABLED,
	HCI_SC_ENABLED,
	HCI_SC_ONLY,
	HCI_PRIVACY,
	HCI_LIMITED_PRIVACY,
	HCI_RPA_EXPIRED,
	HCI_RPA_RESOLVING,
	HCI_HS_ENABLED,
	HCI_LE_ENABLED,
	HCI_ADVERTISING,
	HCI_ADVERTISING_CONNECTABLE,
	HCI_CONNECTABLE,
	HCI_DISCOVERABLE,
	HCI_LIMITED_DISCOVERABLE,
	HCI_LINK_SECURITY,
	HCI_PERIODIC_INQ,
	HCI_FAST_CONNECTABLE,
	HCI_BREDR_ENABLED,
	HCI_LE_SCAN_INTERRUPTED,
	HCI_WIDEBAND_SPEECH_ENABLED,
	HCI_EVENT_FILTER_CONFIGURED,

	HCI_DUT_MODE,
	HCI_VENDOR_DIAG,
	HCI_FORCE_BREDR_SMP,
	HCI_FORCE_STATIC_ADDR,
	HCI_LL_RPA_RESOLUTION,
	HCI_ENABLE_LL_PRIVACY,
	HCI_CMD_PENDING,
	HCI_FORCE_NO_MITM,

	__HCI_NUM_FLAGS,
पूर्ण;

/* HCI समयouts */
#घोषणा HCI_DISCONN_TIMEOUT	msecs_to_jअगरfies(2000)	/* 2 seconds */
#घोषणा HCI_PAIRING_TIMEOUT	msecs_to_jअगरfies(60000)	/* 60 seconds */
#घोषणा HCI_INIT_TIMEOUT	msecs_to_jअगरfies(10000)	/* 10 seconds */
#घोषणा HCI_CMD_TIMEOUT		msecs_to_jअगरfies(2000)	/* 2 seconds */
#घोषणा HCI_ACL_TX_TIMEOUT	msecs_to_jअगरfies(45000)	/* 45 seconds */
#घोषणा HCI_AUTO_OFF_TIMEOUT	msecs_to_jअगरfies(2000)	/* 2 seconds */
#घोषणा HCI_POWER_OFF_TIMEOUT	msecs_to_jअगरfies(5000)	/* 5 seconds */
#घोषणा HCI_LE_CONN_TIMEOUT	msecs_to_jअगरfies(20000)	/* 20 seconds */
#घोषणा HCI_LE_AUTOCONN_TIMEOUT	msecs_to_jअगरfies(4000)	/* 4 seconds */

/* HCI data types */
#घोषणा HCI_COMMAND_PKT		0x01
#घोषणा HCI_ACLDATA_PKT		0x02
#घोषणा HCI_SCODATA_PKT		0x03
#घोषणा HCI_EVENT_PKT		0x04
#घोषणा HCI_ISODATA_PKT		0x05
#घोषणा HCI_DIAG_PKT		0xf0
#घोषणा HCI_VENDOR_PKT		0xff

/* HCI packet types */
#घोषणा HCI_DM1		0x0008
#घोषणा HCI_DM3		0x0400
#घोषणा HCI_DM5		0x4000
#घोषणा HCI_DH1		0x0010
#घोषणा HCI_DH3		0x0800
#घोषणा HCI_DH5		0x8000

/* HCI packet types inverted masks */
#घोषणा HCI_2DH1	0x0002
#घोषणा HCI_3DH1	0x0004
#घोषणा HCI_2DH3	0x0100
#घोषणा HCI_3DH3	0x0200
#घोषणा HCI_2DH5	0x1000
#घोषणा HCI_3DH5	0x2000

#घोषणा HCI_HV1		0x0020
#घोषणा HCI_HV2		0x0040
#घोषणा HCI_HV3		0x0080

#घोषणा SCO_PTYPE_MASK	(HCI_HV1 | HCI_HV2 | HCI_HV3)
#घोषणा ACL_PTYPE_MASK	(~SCO_PTYPE_MASK)

/* eSCO packet types */
#घोषणा ESCO_HV1	0x0001
#घोषणा ESCO_HV2	0x0002
#घोषणा ESCO_HV3	0x0004
#घोषणा ESCO_EV3	0x0008
#घोषणा ESCO_EV4	0x0010
#घोषणा ESCO_EV5	0x0020
#घोषणा ESCO_2EV3	0x0040
#घोषणा ESCO_3EV3	0x0080
#घोषणा ESCO_2EV5	0x0100
#घोषणा ESCO_3EV5	0x0200

#घोषणा SCO_ESCO_MASK  (ESCO_HV1 | ESCO_HV2 | ESCO_HV3)
#घोषणा EDR_ESCO_MASK  (ESCO_2EV3 | ESCO_3EV3 | ESCO_2EV5 | ESCO_3EV5)

/* ACL flags */
#घोषणा ACL_START_NO_FLUSH	0x00
#घोषणा ACL_CONT		0x01
#घोषणा ACL_START		0x02
#घोषणा ACL_COMPLETE		0x03
#घोषणा ACL_ACTIVE_BCAST	0x04
#घोषणा ACL_PICO_BCAST		0x08

/* ISO PB flags */
#घोषणा ISO_START		0x00
#घोषणा ISO_CONT		0x01
#घोषणा ISO_SINGLE		0x02
#घोषणा ISO_END			0x03

/* ISO TS flags */
#घोषणा ISO_TS			0x01

/* Baseband links */
#घोषणा SCO_LINK	0x00
#घोषणा ACL_LINK	0x01
#घोषणा ESCO_LINK	0x02
/* Low Energy links करो not have defined link type. Use invented one */
#घोषणा LE_LINK		0x80
#घोषणा AMP_LINK	0x81
#घोषणा ISO_LINK	0x82
#घोषणा INVALID_LINK	0xff

/* LMP features */
#घोषणा LMP_3SLOT	0x01
#घोषणा LMP_5SLOT	0x02
#घोषणा LMP_ENCRYPT	0x04
#घोषणा LMP_SOFFSET	0x08
#घोषणा LMP_TACCURACY	0x10
#घोषणा LMP_RSWITCH	0x20
#घोषणा LMP_HOLD	0x40
#घोषणा LMP_SNIFF	0x80

#घोषणा LMP_PARK	0x01
#घोषणा LMP_RSSI	0x02
#घोषणा LMP_QUALITY	0x04
#घोषणा LMP_SCO		0x08
#घोषणा LMP_HV2		0x10
#घोषणा LMP_HV3		0x20
#घोषणा LMP_ULAW	0x40
#घोषणा LMP_ALAW	0x80

#घोषणा LMP_CVSD	0x01
#घोषणा LMP_PSCHEME	0x02
#घोषणा LMP_PCONTROL	0x04
#घोषणा LMP_TRANSPARENT	0x08

#घोषणा LMP_EDR_2M		0x02
#घोषणा LMP_EDR_3M		0x04
#घोषणा LMP_RSSI_INQ	0x40
#घोषणा LMP_ESCO	0x80

#घोषणा LMP_EV4		0x01
#घोषणा LMP_EV5		0x02
#घोषणा LMP_NO_BREDR	0x20
#घोषणा LMP_LE		0x40
#घोषणा LMP_EDR_3SLOT	0x80

#घोषणा LMP_EDR_5SLOT	0x01
#घोषणा LMP_SNIFF_SUBR	0x02
#घोषणा LMP_PAUSE_ENC	0x04
#घोषणा LMP_EDR_ESCO_2M	0x20
#घोषणा LMP_EDR_ESCO_3M	0x40
#घोषणा LMP_EDR_3S_ESCO	0x80

#घोषणा LMP_EXT_INQ	0x01
#घोषणा LMP_SIMUL_LE_BR	0x02
#घोषणा LMP_SIMPLE_PAIR	0x08
#घोषणा LMP_NO_FLUSH	0x40

#घोषणा LMP_LSTO	0x01
#घोषणा LMP_INQ_TX_PWR	0x02
#घोषणा LMP_EXTFEATURES	0x80

/* Extended LMP features */
#घोषणा LMP_CSB_MASTER	0x01
#घोषणा LMP_CSB_SLAVE	0x02
#घोषणा LMP_SYNC_TRAIN	0x04
#घोषणा LMP_SYNC_SCAN	0x08

#घोषणा LMP_SC		0x01
#घोषणा LMP_PING	0x02

/* Host features */
#घोषणा LMP_HOST_SSP		0x01
#घोषणा LMP_HOST_LE		0x02
#घोषणा LMP_HOST_LE_BREDR	0x04
#घोषणा LMP_HOST_SC		0x08

/* LE features */
#घोषणा HCI_LE_ENCRYPTION		0x01
#घोषणा HCI_LE_CONN_PARAM_REQ_PROC	0x02
#घोषणा HCI_LE_SLAVE_FEATURES		0x08
#घोषणा HCI_LE_PING			0x10
#घोषणा HCI_LE_DATA_LEN_EXT		0x20
#घोषणा HCI_LE_LL_PRIVACY		0x40
#घोषणा HCI_LE_EXT_SCAN_POLICY		0x80
#घोषणा HCI_LE_PHY_2M			0x01
#घोषणा HCI_LE_PHY_CODED		0x08
#घोषणा HCI_LE_EXT_ADV			0x10
#घोषणा HCI_LE_CHAN_SEL_ALG2		0x40
#घोषणा HCI_LE_CIS_MASTER		0x10
#घोषणा HCI_LE_CIS_SLAVE		0x20

/* Connection modes */
#घोषणा HCI_CM_ACTIVE	0x0000
#घोषणा HCI_CM_HOLD	0x0001
#घोषणा HCI_CM_SNIFF	0x0002
#घोषणा HCI_CM_PARK	0x0003

/* Link policies */
#घोषणा HCI_LP_RSWITCH	0x0001
#घोषणा HCI_LP_HOLD	0x0002
#घोषणा HCI_LP_SNIFF	0x0004
#घोषणा HCI_LP_PARK	0x0008

/* Link modes */
#घोषणा HCI_LM_ACCEPT	0x8000
#घोषणा HCI_LM_MASTER	0x0001
#घोषणा HCI_LM_AUTH	0x0002
#घोषणा HCI_LM_ENCRYPT	0x0004
#घोषणा HCI_LM_TRUSTED	0x0008
#घोषणा HCI_LM_RELIABLE	0x0010
#घोषणा HCI_LM_SECURE	0x0020
#घोषणा HCI_LM_FIPS	0x0040

/* Authentication types */
#घोषणा HCI_AT_NO_BONDING		0x00
#घोषणा HCI_AT_NO_BONDING_MITM		0x01
#घोषणा HCI_AT_DEDICATED_BONDING	0x02
#घोषणा HCI_AT_DEDICATED_BONDING_MITM	0x03
#घोषणा HCI_AT_GENERAL_BONDING		0x04
#घोषणा HCI_AT_GENERAL_BONDING_MITM	0x05

/* I/O capabilities */
#घोषणा HCI_IO_DISPLAY_ONLY	0x00
#घोषणा HCI_IO_DISPLAY_YESNO	0x01
#घोषणा HCI_IO_KEYBOARD_ONLY	0x02
#घोषणा HCI_IO_NO_INPUT_OUTPUT	0x03

/* Link Key types */
#घोषणा HCI_LK_COMBINATION		0x00
#घोषणा HCI_LK_LOCAL_UNIT		0x01
#घोषणा HCI_LK_REMOTE_UNIT		0x02
#घोषणा HCI_LK_DEBUG_COMBINATION	0x03
#घोषणा HCI_LK_UNAUTH_COMBINATION_P192	0x04
#घोषणा HCI_LK_AUTH_COMBINATION_P192	0x05
#घोषणा HCI_LK_CHANGED_COMBINATION	0x06
#घोषणा HCI_LK_UNAUTH_COMBINATION_P256	0x07
#घोषणा HCI_LK_AUTH_COMBINATION_P256	0x08

/* ---- HCI Error Codes ---- */
#घोषणा HCI_ERROR_UNKNOWN_CONN_ID	0x02
#घोषणा HCI_ERROR_AUTH_FAILURE		0x05
#घोषणा HCI_ERROR_PIN_OR_KEY_MISSING	0x06
#घोषणा HCI_ERROR_MEMORY_EXCEEDED	0x07
#घोषणा HCI_ERROR_CONNECTION_TIMEOUT	0x08
#घोषणा HCI_ERROR_REJ_LIMITED_RESOURCES	0x0d
#घोषणा HCI_ERROR_REJ_BAD_ADDR		0x0f
#घोषणा HCI_ERROR_REMOTE_USER_TERM	0x13
#घोषणा HCI_ERROR_REMOTE_LOW_RESOURCES	0x14
#घोषणा HCI_ERROR_REMOTE_POWER_OFF	0x15
#घोषणा HCI_ERROR_LOCAL_HOST_TERM	0x16
#घोषणा HCI_ERROR_PAIRING_NOT_ALLOWED	0x18
#घोषणा HCI_ERROR_INVALID_LL_PARAMS	0x1e
#घोषणा HCI_ERROR_UNSPECIFIED		0x1f
#घोषणा HCI_ERROR_ADVERTISING_TIMEOUT	0x3c

/* Flow control modes */
#घोषणा HCI_FLOW_CTL_MODE_PACKET_BASED	0x00
#घोषणा HCI_FLOW_CTL_MODE_BLOCK_BASED	0x01

/* The core spec defines 127 as the "not available" value */
#घोषणा HCI_TX_POWER_INVALID	127
#घोषणा HCI_RSSI_INVALID	127

#घोषणा HCI_ROLE_MASTER		0x00
#घोषणा HCI_ROLE_SLAVE		0x01

/* Extended Inquiry Response field types */
#घोषणा EIR_FLAGS		0x01 /* flags */
#घोषणा EIR_UUID16_SOME		0x02 /* 16-bit UUID, more available */
#घोषणा EIR_UUID16_ALL		0x03 /* 16-bit UUID, all listed */
#घोषणा EIR_UUID32_SOME		0x04 /* 32-bit UUID, more available */
#घोषणा EIR_UUID32_ALL		0x05 /* 32-bit UUID, all listed */
#घोषणा EIR_UUID128_SOME	0x06 /* 128-bit UUID, more available */
#घोषणा EIR_UUID128_ALL		0x07 /* 128-bit UUID, all listed */
#घोषणा EIR_NAME_SHORT		0x08 /* लघुened local name */
#घोषणा EIR_NAME_COMPLETE	0x09 /* complete local name */
#घोषणा EIR_TX_POWER		0x0A /* transmit घातer level */
#घोषणा EIR_CLASS_OF_DEV	0x0D /* Class of Device */
#घोषणा EIR_SSP_HASH_C192	0x0E /* Simple Pairing Hash C-192 */
#घोषणा EIR_SSP_RAND_R192	0x0F /* Simple Pairing Ranकरोmizer R-192 */
#घोषणा EIR_DEVICE_ID		0x10 /* device ID */
#घोषणा EIR_APPEARANCE		0x19 /* Device appearance */
#घोषणा EIR_LE_BDADDR		0x1B /* LE Bluetooth device address */
#घोषणा EIR_LE_ROLE		0x1C /* LE role */
#घोषणा EIR_SSP_HASH_C256	0x1D /* Simple Pairing Hash C-256 */
#घोषणा EIR_SSP_RAND_R256	0x1E /* Simple Pairing Rand R-256 */
#घोषणा EIR_LE_SC_CONFIRM	0x22 /* LE SC Confirmation Value */
#घोषणा EIR_LE_SC_RANDOM	0x23 /* LE SC Ranकरोm Value */

/* Low Energy Advertising Flags */
#घोषणा LE_AD_LIMITED		0x01 /* Limited Discoverable */
#घोषणा LE_AD_GENERAL		0x02 /* General Discoverable */
#घोषणा LE_AD_NO_BREDR		0x04 /* BR/EDR not supported */
#घोषणा LE_AD_SIM_LE_BREDR_CTRL	0x08 /* Simultaneous LE & BR/EDR Controller */
#घोषणा LE_AD_SIM_LE_BREDR_HOST	0x10 /* Simultaneous LE & BR/EDR Host */

/* -----  HCI Commands ---- */
#घोषणा HCI_OP_NOP			0x0000

#घोषणा HCI_OP_INQUIRY			0x0401
काष्ठा hci_cp_inquiry अणु
	__u8     lap[3];
	__u8     length;
	__u8     num_rsp;
पूर्ण __packed;

#घोषणा HCI_OP_INQUIRY_CANCEL		0x0402

#घोषणा HCI_OP_PERIODIC_INQ		0x0403

#घोषणा HCI_OP_EXIT_PERIODIC_INQ	0x0404

#घोषणा HCI_OP_CREATE_CONN		0x0405
काष्ठा hci_cp_create_conn अणु
	bdaddr_t bdaddr;
	__le16   pkt_type;
	__u8     pscan_rep_mode;
	__u8     pscan_mode;
	__le16   घड़ी_offset;
	__u8     role_चयन;
पूर्ण __packed;

#घोषणा HCI_OP_DISCONNECT		0x0406
काष्ठा hci_cp_disconnect अणु
	__le16   handle;
	__u8     reason;
पूर्ण __packed;

#घोषणा HCI_OP_ADD_SCO			0x0407
काष्ठा hci_cp_add_sco अणु
	__le16   handle;
	__le16   pkt_type;
पूर्ण __packed;

#घोषणा HCI_OP_CREATE_CONN_CANCEL	0x0408
काष्ठा hci_cp_create_conn_cancel अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_ACCEPT_CONN_REQ		0x0409
काष्ठा hci_cp_accept_conn_req अणु
	bdaddr_t bdaddr;
	__u8     role;
पूर्ण __packed;

#घोषणा HCI_OP_REJECT_CONN_REQ		0x040a
काष्ठा hci_cp_reject_conn_req अणु
	bdaddr_t bdaddr;
	__u8     reason;
पूर्ण __packed;

#घोषणा HCI_OP_LINK_KEY_REPLY		0x040b
काष्ठा hci_cp_link_key_reply अणु
	bdaddr_t bdaddr;
	__u8     link_key[HCI_LINK_KEY_SIZE];
पूर्ण __packed;

#घोषणा HCI_OP_LINK_KEY_NEG_REPLY	0x040c
काष्ठा hci_cp_link_key_neg_reply अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_PIN_CODE_REPLY		0x040d
काष्ठा hci_cp_pin_code_reply अणु
	bdaddr_t bdaddr;
	__u8     pin_len;
	__u8     pin_code[16];
पूर्ण __packed;
काष्ठा hci_rp_pin_code_reply अणु
	__u8     status;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_PIN_CODE_NEG_REPLY	0x040e
काष्ठा hci_cp_pin_code_neg_reply अणु
	bdaddr_t bdaddr;
पूर्ण __packed;
काष्ठा hci_rp_pin_code_neg_reply अणु
	__u8     status;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_CHANGE_CONN_PTYPE	0x040f
काष्ठा hci_cp_change_conn_ptype अणु
	__le16   handle;
	__le16   pkt_type;
पूर्ण __packed;

#घोषणा HCI_OP_AUTH_REQUESTED		0x0411
काष्ठा hci_cp_auth_requested अणु
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_OP_SET_CONN_ENCRYPT		0x0413
काष्ठा hci_cp_set_conn_encrypt अणु
	__le16   handle;
	__u8     encrypt;
पूर्ण __packed;

#घोषणा HCI_OP_CHANGE_CONN_LINK_KEY	0x0415
काष्ठा hci_cp_change_conn_link_key अणु
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_OP_REMOTE_NAME_REQ		0x0419
काष्ठा hci_cp_remote_name_req अणु
	bdaddr_t bdaddr;
	__u8     pscan_rep_mode;
	__u8     pscan_mode;
	__le16   घड़ी_offset;
पूर्ण __packed;

#घोषणा HCI_OP_REMOTE_NAME_REQ_CANCEL	0x041a
काष्ठा hci_cp_remote_name_req_cancel अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_READ_REMOTE_FEATURES	0x041b
काष्ठा hci_cp_पढ़ो_remote_features अणु
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_OP_READ_REMOTE_EXT_FEATURES	0x041c
काष्ठा hci_cp_पढ़ो_remote_ext_features अणु
	__le16   handle;
	__u8     page;
पूर्ण __packed;

#घोषणा HCI_OP_READ_REMOTE_VERSION	0x041d
काष्ठा hci_cp_पढ़ो_remote_version अणु
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_OP_READ_CLOCK_OFFSET	0x041f
काष्ठा hci_cp_पढ़ो_घड़ी_offset अणु
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_OP_SETUP_SYNC_CONN		0x0428
काष्ठा hci_cp_setup_sync_conn अणु
	__le16   handle;
	__le32   tx_bandwidth;
	__le32   rx_bandwidth;
	__le16   max_latency;
	__le16   voice_setting;
	__u8     retrans_efक्रमt;
	__le16   pkt_type;
पूर्ण __packed;

#घोषणा HCI_OP_ACCEPT_SYNC_CONN_REQ	0x0429
काष्ठा hci_cp_accept_sync_conn_req अणु
	bdaddr_t bdaddr;
	__le32   tx_bandwidth;
	__le32   rx_bandwidth;
	__le16   max_latency;
	__le16   content_क्रमmat;
	__u8     retrans_efक्रमt;
	__le16   pkt_type;
पूर्ण __packed;

#घोषणा HCI_OP_REJECT_SYNC_CONN_REQ	0x042a
काष्ठा hci_cp_reject_sync_conn_req अणु
	bdaddr_t bdaddr;
	__u8     reason;
पूर्ण __packed;

#घोषणा HCI_OP_IO_CAPABILITY_REPLY	0x042b
काष्ठा hci_cp_io_capability_reply अणु
	bdaddr_t bdaddr;
	__u8     capability;
	__u8     oob_data;
	__u8     authentication;
पूर्ण __packed;

#घोषणा HCI_OP_USER_CONFIRM_REPLY		0x042c
काष्ठा hci_cp_user_confirm_reply अणु
	bdaddr_t bdaddr;
पूर्ण __packed;
काष्ठा hci_rp_user_confirm_reply अणु
	__u8     status;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_USER_CONFIRM_NEG_REPLY	0x042d

#घोषणा HCI_OP_USER_PASSKEY_REPLY		0x042e
काष्ठा hci_cp_user_passkey_reply अणु
	bdaddr_t bdaddr;
	__le32	passkey;
पूर्ण __packed;

#घोषणा HCI_OP_USER_PASSKEY_NEG_REPLY	0x042f

#घोषणा HCI_OP_REMOTE_OOB_DATA_REPLY	0x0430
काष्ठा hci_cp_remote_oob_data_reply अणु
	bdaddr_t bdaddr;
	__u8     hash[16];
	__u8     अक्रम[16];
पूर्ण __packed;

#घोषणा HCI_OP_REMOTE_OOB_DATA_NEG_REPLY	0x0433
काष्ठा hci_cp_remote_oob_data_neg_reply अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_IO_CAPABILITY_NEG_REPLY	0x0434
काष्ठा hci_cp_io_capability_neg_reply अणु
	bdaddr_t bdaddr;
	__u8     reason;
पूर्ण __packed;

#घोषणा HCI_OP_CREATE_PHY_LINK		0x0435
काष्ठा hci_cp_create_phy_link अणु
	__u8     phy_handle;
	__u8     key_len;
	__u8     key_type;
	__u8     key[HCI_AMP_LINK_KEY_SIZE];
पूर्ण __packed;

#घोषणा HCI_OP_ACCEPT_PHY_LINK		0x0436
काष्ठा hci_cp_accept_phy_link अणु
	__u8     phy_handle;
	__u8     key_len;
	__u8     key_type;
	__u8     key[HCI_AMP_LINK_KEY_SIZE];
पूर्ण __packed;

#घोषणा HCI_OP_DISCONN_PHY_LINK		0x0437
काष्ठा hci_cp_disconn_phy_link अणु
	__u8     phy_handle;
	__u8     reason;
पूर्ण __packed;

काष्ठा ext_flow_spec अणु
	__u8       id;
	__u8       stype;
	__le16     msdu;
	__le32     sdu_iसमय;
	__le32     acc_lat;
	__le32     flush_to;
पूर्ण __packed;

#घोषणा HCI_OP_CREATE_LOGICAL_LINK	0x0438
#घोषणा HCI_OP_ACCEPT_LOGICAL_LINK	0x0439
काष्ठा hci_cp_create_accept_logical_link अणु
	__u8                  phy_handle;
	काष्ठा ext_flow_spec  tx_flow_spec;
	काष्ठा ext_flow_spec  rx_flow_spec;
पूर्ण __packed;

#घोषणा HCI_OP_DISCONN_LOGICAL_LINK	0x043a
काष्ठा hci_cp_disconn_logical_link अणु
	__le16   log_handle;
पूर्ण __packed;

#घोषणा HCI_OP_LOGICAL_LINK_CANCEL	0x043b
काष्ठा hci_cp_logical_link_cancel अणु
	__u8     phy_handle;
	__u8     flow_spec_id;
पूर्ण __packed;

काष्ठा hci_rp_logical_link_cancel अणु
	__u8     status;
	__u8     phy_handle;
	__u8     flow_spec_id;
पूर्ण __packed;

#घोषणा HCI_OP_SET_CSB			0x0441
काष्ठा hci_cp_set_csb अणु
	__u8	enable;
	__u8	lt_addr;
	__u8	lpo_allowed;
	__le16	packet_type;
	__le16	पूर्णांकerval_min;
	__le16	पूर्णांकerval_max;
	__le16	csb_sv_tout;
पूर्ण __packed;
काष्ठा hci_rp_set_csb अणु
	__u8	status;
	__u8	lt_addr;
	__le16	पूर्णांकerval;
पूर्ण __packed;

#घोषणा HCI_OP_START_SYNC_TRAIN		0x0443

#घोषणा HCI_OP_REMOTE_OOB_EXT_DATA_REPLY	0x0445
काष्ठा hci_cp_remote_oob_ext_data_reply अणु
	bdaddr_t bdaddr;
	__u8     hash192[16];
	__u8     अक्रम192[16];
	__u8     hash256[16];
	__u8     अक्रम256[16];
पूर्ण __packed;

#घोषणा HCI_OP_SNIFF_MODE		0x0803
काष्ठा hci_cp_snअगरf_mode अणु
	__le16   handle;
	__le16   max_पूर्णांकerval;
	__le16   min_पूर्णांकerval;
	__le16   attempt;
	__le16   समयout;
पूर्ण __packed;

#घोषणा HCI_OP_EXIT_SNIFF_MODE		0x0804
काष्ठा hci_cp_निकास_snअगरf_mode अणु
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_OP_ROLE_DISCOVERY		0x0809
काष्ठा hci_cp_role_discovery अणु
	__le16   handle;
पूर्ण __packed;
काष्ठा hci_rp_role_discovery अणु
	__u8     status;
	__le16   handle;
	__u8     role;
पूर्ण __packed;

#घोषणा HCI_OP_SWITCH_ROLE		0x080b
काष्ठा hci_cp_चयन_role अणु
	bdaddr_t bdaddr;
	__u8     role;
पूर्ण __packed;

#घोषणा HCI_OP_READ_LINK_POLICY		0x080c
काष्ठा hci_cp_पढ़ो_link_policy अणु
	__le16   handle;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_link_policy अणु
	__u8     status;
	__le16   handle;
	__le16   policy;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_LINK_POLICY	0x080d
काष्ठा hci_cp_ग_लिखो_link_policy अणु
	__le16   handle;
	__le16   policy;
पूर्ण __packed;
काष्ठा hci_rp_ग_लिखो_link_policy अणु
	__u8     status;
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_OP_READ_DEF_LINK_POLICY	0x080e
काष्ठा hci_rp_पढ़ो_def_link_policy अणु
	__u8     status;
	__le16   policy;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_DEF_LINK_POLICY	0x080f
काष्ठा hci_cp_ग_लिखो_def_link_policy अणु
	__le16   policy;
पूर्ण __packed;

#घोषणा HCI_OP_SNIFF_SUBRATE		0x0811
काष्ठा hci_cp_snअगरf_subrate अणु
	__le16   handle;
	__le16   max_latency;
	__le16   min_remote_समयout;
	__le16   min_local_समयout;
पूर्ण __packed;

#घोषणा HCI_OP_SET_EVENT_MASK		0x0c01

#घोषणा HCI_OP_RESET			0x0c03

#घोषणा HCI_OP_SET_EVENT_FLT		0x0c05
#घोषणा HCI_SET_EVENT_FLT_SIZE		9
काष्ठा hci_cp_set_event_filter अणु
	__u8		flt_type;
	__u8		cond_type;
	काष्ठा अणु
		bdaddr_t bdaddr;
		__u8 स्वतः_accept;
	पूर्ण __packed	addr_conn_flt;
पूर्ण __packed;

/* Filter types */
#घोषणा HCI_FLT_CLEAR_ALL	0x00
#घोषणा HCI_FLT_INQ_RESULT	0x01
#घोषणा HCI_FLT_CONN_SETUP	0x02

/* CONN_SETUP Condition types */
#घोषणा HCI_CONN_SETUP_ALLOW_ALL	0x00
#घोषणा HCI_CONN_SETUP_ALLOW_CLASS	0x01
#घोषणा HCI_CONN_SETUP_ALLOW_BDADDR	0x02

/* CONN_SETUP Conditions */
#घोषणा HCI_CONN_SETUP_AUTO_OFF		0x01
#घोषणा HCI_CONN_SETUP_AUTO_ON		0x02
#घोषणा HCI_CONN_SETUP_AUTO_ON_WITH_RS	0x03

#घोषणा HCI_OP_READ_STORED_LINK_KEY	0x0c0d
काष्ठा hci_cp_पढ़ो_stored_link_key अणु
	bdaddr_t bdaddr;
	__u8     पढ़ो_all;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_stored_link_key अणु
	__u8     status;
	__u8     max_keys;
	__u8     num_keys;
पूर्ण __packed;

#घोषणा HCI_OP_DELETE_STORED_LINK_KEY	0x0c12
काष्ठा hci_cp_delete_stored_link_key अणु
	bdaddr_t bdaddr;
	__u8     delete_all;
पूर्ण __packed;
काष्ठा hci_rp_delete_stored_link_key अणु
	__u8     status;
	__u8     num_keys;
पूर्ण __packed;

#घोषणा HCI_MAX_NAME_LENGTH		248

#घोषणा HCI_OP_WRITE_LOCAL_NAME		0x0c13
काष्ठा hci_cp_ग_लिखो_local_name अणु
	__u8     name[HCI_MAX_NAME_LENGTH];
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_NAME		0x0c14
काष्ठा hci_rp_पढ़ो_local_name अणु
	__u8     status;
	__u8     name[HCI_MAX_NAME_LENGTH];
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_CA_TIMEOUT		0x0c16

#घोषणा HCI_OP_WRITE_PG_TIMEOUT		0x0c18

#घोषणा HCI_OP_WRITE_SCAN_ENABLE	0x0c1a
	#घोषणा SCAN_DISABLED		0x00
	#घोषणा SCAN_INQUIRY		0x01
	#घोषणा SCAN_PAGE		0x02

#घोषणा HCI_OP_READ_AUTH_ENABLE		0x0c1f

#घोषणा HCI_OP_WRITE_AUTH_ENABLE	0x0c20
	#घोषणा AUTH_DISABLED		0x00
	#घोषणा AUTH_ENABLED		0x01

#घोषणा HCI_OP_READ_ENCRYPT_MODE	0x0c21

#घोषणा HCI_OP_WRITE_ENCRYPT_MODE	0x0c22
	#घोषणा ENCRYPT_DISABLED	0x00
	#घोषणा ENCRYPT_P2P		0x01
	#घोषणा ENCRYPT_BOTH		0x02

#घोषणा HCI_OP_READ_CLASS_OF_DEV	0x0c23
काष्ठा hci_rp_पढ़ो_class_of_dev अणु
	__u8     status;
	__u8     dev_class[3];
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_CLASS_OF_DEV	0x0c24
काष्ठा hci_cp_ग_लिखो_class_of_dev अणु
	__u8     dev_class[3];
पूर्ण __packed;

#घोषणा HCI_OP_READ_VOICE_SETTING	0x0c25
काष्ठा hci_rp_पढ़ो_voice_setting अणु
	__u8     status;
	__le16   voice_setting;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_VOICE_SETTING	0x0c26
काष्ठा hci_cp_ग_लिखो_voice_setting अणु
	__le16   voice_setting;
पूर्ण __packed;

#घोषणा HCI_OP_HOST_BUFFER_SIZE		0x0c33
काष्ठा hci_cp_host_buffer_size अणु
	__le16   acl_mtu;
	__u8     sco_mtu;
	__le16   acl_max_pkt;
	__le16   sco_max_pkt;
पूर्ण __packed;

#घोषणा HCI_OP_READ_NUM_SUPPORTED_IAC	0x0c38
काष्ठा hci_rp_पढ़ो_num_supported_iac अणु
	__u8	status;
	__u8	num_iac;
पूर्ण __packed;

#घोषणा HCI_OP_READ_CURRENT_IAC_LAP	0x0c39

#घोषणा HCI_OP_WRITE_CURRENT_IAC_LAP	0x0c3a
काष्ठा hci_cp_ग_लिखो_current_iac_lap अणु
	__u8	num_iac;
	__u8	iac_lap[6];
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_INQUIRY_MODE	0x0c45

#घोषणा HCI_MAX_EIR_LENGTH		240

#घोषणा HCI_OP_WRITE_EIR		0x0c52
काष्ठा hci_cp_ग_लिखो_eir अणु
	__u8	fec;
	__u8	data[HCI_MAX_EIR_LENGTH];
पूर्ण __packed;

#घोषणा HCI_OP_READ_SSP_MODE		0x0c55
काष्ठा hci_rp_पढ़ो_ssp_mode अणु
	__u8     status;
	__u8     mode;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_SSP_MODE		0x0c56
काष्ठा hci_cp_ग_लिखो_ssp_mode अणु
	__u8     mode;
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_OOB_DATA		0x0c57
काष्ठा hci_rp_पढ़ो_local_oob_data अणु
	__u8     status;
	__u8     hash[16];
	__u8     अक्रम[16];
पूर्ण __packed;

#घोषणा HCI_OP_READ_INQ_RSP_TX_POWER	0x0c58
काष्ठा hci_rp_पढ़ो_inq_rsp_tx_घातer अणु
	__u8     status;
	__s8     tx_घातer;
पूर्ण __packed;

#घोषणा HCI_OP_READ_DEF_ERR_DATA_REPORTING	0x0c5a
	#घोषणा ERR_DATA_REPORTING_DISABLED	0x00
	#घोषणा ERR_DATA_REPORTING_ENABLED	0x01
काष्ठा hci_rp_पढ़ो_def_err_data_reporting अणु
	__u8     status;
	__u8     err_data_reporting;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_DEF_ERR_DATA_REPORTING	0x0c5b
काष्ठा hci_cp_ग_लिखो_def_err_data_reporting अणु
	__u8     err_data_reporting;
पूर्ण __packed;

#घोषणा HCI_OP_SET_EVENT_MASK_PAGE_2	0x0c63

#घोषणा HCI_OP_READ_LOCATION_DATA	0x0c64

#घोषणा HCI_OP_READ_FLOW_CONTROL_MODE	0x0c66
काष्ठा hci_rp_पढ़ो_flow_control_mode अणु
	__u8     status;
	__u8     mode;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_LE_HOST_SUPPORTED	0x0c6d
काष्ठा hci_cp_ग_लिखो_le_host_supported अणु
	__u8	le;
	__u8	simul;
पूर्ण __packed;

#घोषणा HCI_OP_SET_RESERVED_LT_ADDR	0x0c74
काष्ठा hci_cp_set_reserved_lt_addr अणु
	__u8	lt_addr;
पूर्ण __packed;
काष्ठा hci_rp_set_reserved_lt_addr अणु
	__u8	status;
	__u8	lt_addr;
पूर्ण __packed;

#घोषणा HCI_OP_DELETE_RESERVED_LT_ADDR	0x0c75
काष्ठा hci_cp_delete_reserved_lt_addr अणु
	__u8	lt_addr;
पूर्ण __packed;
काष्ठा hci_rp_delete_reserved_lt_addr अणु
	__u8	status;
	__u8	lt_addr;
पूर्ण __packed;

#घोषणा HCI_OP_SET_CSB_DATA		0x0c76
काष्ठा hci_cp_set_csb_data अणु
	__u8	lt_addr;
	__u8	fragment;
	__u8	data_length;
	__u8	data[HCI_MAX_CSB_DATA_SIZE];
पूर्ण __packed;
काष्ठा hci_rp_set_csb_data अणु
	__u8	status;
	__u8	lt_addr;
पूर्ण __packed;

#घोषणा HCI_OP_READ_SYNC_TRAIN_PARAMS	0x0c77

#घोषणा HCI_OP_WRITE_SYNC_TRAIN_PARAMS	0x0c78
काष्ठा hci_cp_ग_लिखो_sync_train_params अणु
	__le16	पूर्णांकerval_min;
	__le16	पूर्णांकerval_max;
	__le32	sync_train_tout;
	__u8	service_data;
पूर्ण __packed;
काष्ठा hci_rp_ग_लिखो_sync_train_params अणु
	__u8	status;
	__le16	sync_train_पूर्णांक;
पूर्ण __packed;

#घोषणा HCI_OP_READ_SC_SUPPORT		0x0c79
काष्ठा hci_rp_पढ़ो_sc_support अणु
	__u8	status;
	__u8	support;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_SC_SUPPORT		0x0c7a
काष्ठा hci_cp_ग_लिखो_sc_support अणु
	__u8	support;
पूर्ण __packed;

#घोषणा HCI_OP_READ_AUTH_PAYLOAD_TO    0x0c7b
काष्ठा hci_cp_पढ़ो_auth_payload_to अणु
	__le16  handle;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_auth_payload_to अणु
	__u8    status;
	__le16  handle;
	__le16  समयout;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_AUTH_PAYLOAD_TO    0x0c7c
काष्ठा hci_cp_ग_लिखो_auth_payload_to अणु
	__le16  handle;
	__le16  समयout;
पूर्ण __packed;
काष्ठा hci_rp_ग_लिखो_auth_payload_to अणु
	__u8    status;
	__le16  handle;
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_OOB_EXT_DATA	0x0c7d
काष्ठा hci_rp_पढ़ो_local_oob_ext_data अणु
	__u8     status;
	__u8     hash192[16];
	__u8     अक्रम192[16];
	__u8     hash256[16];
	__u8     अक्रम256[16];
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_VERSION	0x1001
काष्ठा hci_rp_पढ़ो_local_version अणु
	__u8     status;
	__u8     hci_ver;
	__le16   hci_rev;
	__u8     lmp_ver;
	__le16   manufacturer;
	__le16   lmp_subver;
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_COMMANDS	0x1002
काष्ठा hci_rp_पढ़ो_local_commands अणु
	__u8     status;
	__u8     commands[64];
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_FEATURES	0x1003
काष्ठा hci_rp_पढ़ो_local_features अणु
	__u8     status;
	__u8     features[8];
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_EXT_FEATURES	0x1004
काष्ठा hci_cp_पढ़ो_local_ext_features अणु
	__u8     page;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_local_ext_features अणु
	__u8     status;
	__u8     page;
	__u8     max_page;
	__u8     features[8];
पूर्ण __packed;

#घोषणा HCI_OP_READ_BUFFER_SIZE		0x1005
काष्ठा hci_rp_पढ़ो_buffer_size अणु
	__u8     status;
	__le16   acl_mtu;
	__u8     sco_mtu;
	__le16   acl_max_pkt;
	__le16   sco_max_pkt;
पूर्ण __packed;

#घोषणा HCI_OP_READ_BD_ADDR		0x1009
काष्ठा hci_rp_पढ़ो_bd_addr अणु
	__u8     status;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_READ_DATA_BLOCK_SIZE	0x100a
काष्ठा hci_rp_पढ़ो_data_block_size अणु
	__u8     status;
	__le16   max_acl_len;
	__le16   block_len;
	__le16   num_blocks;
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_CODECS	0x100b

#घोषणा HCI_OP_READ_LOCAL_PAIRING_OPTS	0x100c
काष्ठा hci_rp_पढ़ो_local_pairing_opts अणु
	__u8     status;
	__u8     pairing_opts;
	__u8     max_key_size;
पूर्ण __packed;

#घोषणा HCI_OP_READ_PAGE_SCAN_ACTIVITY	0x0c1b
काष्ठा hci_rp_पढ़ो_page_scan_activity अणु
	__u8     status;
	__le16   पूर्णांकerval;
	__le16   winकरोw;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_PAGE_SCAN_ACTIVITY	0x0c1c
काष्ठा hci_cp_ग_लिखो_page_scan_activity अणु
	__le16   पूर्णांकerval;
	__le16   winकरोw;
पूर्ण __packed;

#घोषणा HCI_OP_READ_TX_POWER		0x0c2d
काष्ठा hci_cp_पढ़ो_tx_घातer अणु
	__le16   handle;
	__u8     type;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_tx_घातer अणु
	__u8     status;
	__le16   handle;
	__s8     tx_घातer;
पूर्ण __packed;

#घोषणा HCI_OP_READ_PAGE_SCAN_TYPE	0x0c46
काष्ठा hci_rp_पढ़ो_page_scan_type अणु
	__u8     status;
	__u8     type;
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_PAGE_SCAN_TYPE	0x0c47
	#घोषणा PAGE_SCAN_TYPE_STANDARD		0x00
	#घोषणा PAGE_SCAN_TYPE_INTERLACED	0x01

#घोषणा HCI_OP_READ_RSSI		0x1405
काष्ठा hci_cp_पढ़ो_rssi अणु
	__le16   handle;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_rssi अणु
	__u8     status;
	__le16   handle;
	__s8     rssi;
पूर्ण __packed;

#घोषणा HCI_OP_READ_CLOCK		0x1407
काष्ठा hci_cp_पढ़ो_घड़ी अणु
	__le16   handle;
	__u8     which;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_घड़ी अणु
	__u8     status;
	__le16   handle;
	__le32   घड़ी;
	__le16   accuracy;
पूर्ण __packed;

#घोषणा HCI_OP_READ_ENC_KEY_SIZE	0x1408
काष्ठा hci_cp_पढ़ो_enc_key_size अणु
	__le16   handle;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_enc_key_size अणु
	__u8     status;
	__le16   handle;
	__u8     key_size;
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_AMP_INFO	0x1409
काष्ठा hci_rp_पढ़ो_local_amp_info अणु
	__u8     status;
	__u8     amp_status;
	__le32   total_bw;
	__le32   max_bw;
	__le32   min_latency;
	__le32   max_pdu;
	__u8     amp_type;
	__le16   pal_cap;
	__le16   max_assoc_size;
	__le32   max_flush_to;
	__le32   be_flush_to;
पूर्ण __packed;

#घोषणा HCI_OP_READ_LOCAL_AMP_ASSOC	0x140a
काष्ठा hci_cp_पढ़ो_local_amp_assoc अणु
	__u8     phy_handle;
	__le16   len_so_far;
	__le16   max_len;
पूर्ण __packed;
काष्ठा hci_rp_पढ़ो_local_amp_assoc अणु
	__u8     status;
	__u8     phy_handle;
	__le16   rem_len;
	__u8     frag[];
पूर्ण __packed;

#घोषणा HCI_OP_WRITE_REMOTE_AMP_ASSOC	0x140b
काष्ठा hci_cp_ग_लिखो_remote_amp_assoc अणु
	__u8     phy_handle;
	__le16   len_so_far;
	__le16   rem_len;
	__u8     frag[];
पूर्ण __packed;
काष्ठा hci_rp_ग_लिखो_remote_amp_assoc अणु
	__u8     status;
	__u8     phy_handle;
पूर्ण __packed;

#घोषणा HCI_OP_GET_MWS_TRANSPORT_CONFIG	0x140c

#घोषणा HCI_OP_ENABLE_DUT_MODE		0x1803

#घोषणा HCI_OP_WRITE_SSP_DEBUG_MODE	0x1804

#घोषणा HCI_OP_LE_SET_EVENT_MASK	0x2001
काष्ठा hci_cp_le_set_event_mask अणु
	__u8     mask[8];
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_BUFFER_SIZE	0x2002
काष्ठा hci_rp_le_पढ़ो_buffer_size अणु
	__u8     status;
	__le16   le_mtu;
	__u8     le_max_pkt;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_LOCAL_FEATURES	0x2003
काष्ठा hci_rp_le_पढ़ो_local_features अणु
	__u8     status;
	__u8     features[8];
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_RANDOM_ADDR	0x2005

#घोषणा HCI_OP_LE_SET_ADV_PARAM		0x2006
काष्ठा hci_cp_le_set_adv_param अणु
	__le16   min_पूर्णांकerval;
	__le16   max_पूर्णांकerval;
	__u8     type;
	__u8     own_address_type;
	__u8     direct_addr_type;
	bdaddr_t direct_addr;
	__u8     channel_map;
	__u8     filter_policy;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_ADV_TX_POWER	0x2007
काष्ठा hci_rp_le_पढ़ो_adv_tx_घातer अणु
	__u8	status;
	__s8	tx_घातer;
पूर्ण __packed;

#घोषणा HCI_MAX_AD_LENGTH		31

#घोषणा HCI_OP_LE_SET_ADV_DATA		0x2008
काष्ठा hci_cp_le_set_adv_data अणु
	__u8	length;
	__u8	data[HCI_MAX_AD_LENGTH];
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_SCAN_RSP_DATA	0x2009
काष्ठा hci_cp_le_set_scan_rsp_data अणु
	__u8	length;
	__u8	data[HCI_MAX_AD_LENGTH];
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_ADV_ENABLE	0x200a

#घोषणा LE_SCAN_PASSIVE			0x00
#घोषणा LE_SCAN_ACTIVE			0x01

#घोषणा HCI_OP_LE_SET_SCAN_PARAM	0x200b
काष्ठा hci_cp_le_set_scan_param अणु
	__u8    type;
	__le16  पूर्णांकerval;
	__le16  winकरोw;
	__u8    own_address_type;
	__u8    filter_policy;
पूर्ण __packed;

#घोषणा LE_SCAN_DISABLE			0x00
#घोषणा LE_SCAN_ENABLE			0x01
#घोषणा LE_SCAN_FILTER_DUP_DISABLE	0x00
#घोषणा LE_SCAN_FILTER_DUP_ENABLE	0x01

#घोषणा HCI_OP_LE_SET_SCAN_ENABLE	0x200c
काष्ठा hci_cp_le_set_scan_enable अणु
	__u8     enable;
	__u8     filter_dup;
पूर्ण __packed;

#घोषणा HCI_LE_USE_PEER_ADDR		0x00
#घोषणा HCI_LE_USE_WHITELIST		0x01

#घोषणा HCI_OP_LE_CREATE_CONN		0x200d
काष्ठा hci_cp_le_create_conn अणु
	__le16   scan_पूर्णांकerval;
	__le16   scan_winकरोw;
	__u8     filter_policy;
	__u8     peer_addr_type;
	bdaddr_t peer_addr;
	__u8     own_address_type;
	__le16   conn_पूर्णांकerval_min;
	__le16   conn_पूर्णांकerval_max;
	__le16   conn_latency;
	__le16   supervision_समयout;
	__le16   min_ce_len;
	__le16   max_ce_len;
पूर्ण __packed;

#घोषणा HCI_OP_LE_CREATE_CONN_CANCEL	0x200e

#घोषणा HCI_OP_LE_READ_WHITE_LIST_SIZE	0x200f
काष्ठा hci_rp_le_पढ़ो_white_list_size अणु
	__u8	status;
	__u8	size;
पूर्ण __packed;

#घोषणा HCI_OP_LE_CLEAR_WHITE_LIST	0x2010

#घोषणा HCI_OP_LE_ADD_TO_WHITE_LIST	0x2011
काष्ठा hci_cp_le_add_to_white_list अणु
	__u8     bdaddr_type;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_LE_DEL_FROM_WHITE_LIST	0x2012
काष्ठा hci_cp_le_del_from_white_list अणु
	__u8     bdaddr_type;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_LE_CONN_UPDATE		0x2013
काष्ठा hci_cp_le_conn_update अणु
	__le16   handle;
	__le16   conn_पूर्णांकerval_min;
	__le16   conn_पूर्णांकerval_max;
	__le16   conn_latency;
	__le16   supervision_समयout;
	__le16   min_ce_len;
	__le16   max_ce_len;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_REMOTE_FEATURES	0x2016
काष्ठा hci_cp_le_पढ़ो_remote_features अणु
	__le16	 handle;
पूर्ण __packed;

#घोषणा HCI_OP_LE_START_ENC		0x2019
काष्ठा hci_cp_le_start_enc अणु
	__le16	handle;
	__le64	अक्रम;
	__le16	eभाग;
	__u8	ltk[16];
पूर्ण __packed;

#घोषणा HCI_OP_LE_LTK_REPLY		0x201a
काष्ठा hci_cp_le_ltk_reply अणु
	__le16	handle;
	__u8	ltk[16];
पूर्ण __packed;
काष्ठा hci_rp_le_ltk_reply अणु
	__u8	status;
	__le16	handle;
पूर्ण __packed;

#घोषणा HCI_OP_LE_LTK_NEG_REPLY		0x201b
काष्ठा hci_cp_le_ltk_neg_reply अणु
	__le16	handle;
पूर्ण __packed;
काष्ठा hci_rp_le_ltk_neg_reply अणु
	__u8	status;
	__le16	handle;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_SUPPORTED_STATES	0x201c
काष्ठा hci_rp_le_पढ़ो_supported_states अणु
	__u8	status;
	__u8	le_states[8];
पूर्ण __packed;

#घोषणा HCI_OP_LE_CONN_PARAM_REQ_REPLY	0x2020
काष्ठा hci_cp_le_conn_param_req_reply अणु
	__le16	handle;
	__le16	पूर्णांकerval_min;
	__le16	पूर्णांकerval_max;
	__le16	latency;
	__le16	समयout;
	__le16	min_ce_len;
	__le16	max_ce_len;
पूर्ण __packed;

#घोषणा HCI_OP_LE_CONN_PARAM_REQ_NEG_REPLY	0x2021
काष्ठा hci_cp_le_conn_param_req_neg_reply अणु
	__le16	handle;
	__u8	reason;
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_DATA_LEN		0x2022
काष्ठा hci_cp_le_set_data_len अणु
	__le16	handle;
	__le16	tx_len;
	__le16	tx_समय;
पूर्ण __packed;
काष्ठा hci_rp_le_set_data_len अणु
	__u8	status;
	__le16	handle;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_DEF_DATA_LEN	0x2023
काष्ठा hci_rp_le_पढ़ो_def_data_len अणु
	__u8	status;
	__le16	tx_len;
	__le16	tx_समय;
पूर्ण __packed;

#घोषणा HCI_OP_LE_WRITE_DEF_DATA_LEN	0x2024
काष्ठा hci_cp_le_ग_लिखो_def_data_len अणु
	__le16	tx_len;
	__le16	tx_समय;
पूर्ण __packed;

#घोषणा HCI_OP_LE_ADD_TO_RESOLV_LIST	0x2027
काष्ठा hci_cp_le_add_to_resolv_list अणु
	__u8	 bdaddr_type;
	bdaddr_t bdaddr;
	__u8	 peer_irk[16];
	__u8	 local_irk[16];
पूर्ण __packed;

#घोषणा HCI_OP_LE_DEL_FROM_RESOLV_LIST	0x2028
काष्ठा hci_cp_le_del_from_resolv_list अणु
	__u8	 bdaddr_type;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_LE_CLEAR_RESOLV_LIST	0x2029

#घोषणा HCI_OP_LE_READ_RESOLV_LIST_SIZE	0x202a
काष्ठा hci_rp_le_पढ़ो_resolv_list_size अणु
	__u8	status;
	__u8	size;
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_ADDR_RESOLV_ENABLE 0x202d

#घोषणा HCI_OP_LE_SET_RPA_TIMEOUT	0x202e

#घोषणा HCI_OP_LE_READ_MAX_DATA_LEN	0x202f
काष्ठा hci_rp_le_पढ़ो_max_data_len अणु
	__u8	status;
	__le16	tx_len;
	__le16	tx_समय;
	__le16	rx_len;
	__le16	rx_समय;
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_DEFAULT_PHY	0x2031
काष्ठा hci_cp_le_set_शेष_phy अणु
	__u8    all_phys;
	__u8    tx_phys;
	__u8    rx_phys;
पूर्ण __packed;

#घोषणा HCI_LE_SET_PHY_1M		0x01
#घोषणा HCI_LE_SET_PHY_2M		0x02
#घोषणा HCI_LE_SET_PHY_CODED		0x04

#घोषणा HCI_OP_LE_SET_EXT_SCAN_PARAMS   0x2041
काष्ठा hci_cp_le_set_ext_scan_params अणु
	__u8    own_addr_type;
	__u8    filter_policy;
	__u8    scanning_phys;
	__u8    data[];
पूर्ण __packed;

#घोषणा LE_SCAN_PHY_1M		0x01
#घोषणा LE_SCAN_PHY_2M		0x02
#घोषणा LE_SCAN_PHY_CODED	0x04

काष्ठा hci_cp_le_scan_phy_params अणु
	__u8    type;
	__le16  पूर्णांकerval;
	__le16  winकरोw;
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_EXT_SCAN_ENABLE   0x2042
काष्ठा hci_cp_le_set_ext_scan_enable अणु
	__u8    enable;
	__u8    filter_dup;
	__le16  duration;
	__le16  period;
पूर्ण __packed;

#घोषणा HCI_OP_LE_EXT_CREATE_CONN    0x2043
काष्ठा hci_cp_le_ext_create_conn अणु
	__u8      filter_policy;
	__u8      own_addr_type;
	__u8      peer_addr_type;
	bdaddr_t  peer_addr;
	__u8      phys;
	__u8      data[];
पूर्ण __packed;

काष्ठा hci_cp_le_ext_conn_param अणु
	__le16 scan_पूर्णांकerval;
	__le16 scan_winकरोw;
	__le16 conn_पूर्णांकerval_min;
	__le16 conn_पूर्णांकerval_max;
	__le16 conn_latency;
	__le16 supervision_समयout;
	__le16 min_ce_len;
	__le16 max_ce_len;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_NUM_SUPPORTED_ADV_SETS	0x203b
काष्ठा hci_rp_le_पढ़ो_num_supported_adv_sets अणु
	__u8  status;
	__u8  num_of_sets;
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_EXT_ADV_PARAMS		0x2036
काष्ठा hci_cp_le_set_ext_adv_params अणु
	__u8      handle;
	__le16    evt_properties;
	__u8      min_पूर्णांकerval[3];
	__u8      max_पूर्णांकerval[3];
	__u8      channel_map;
	__u8      own_addr_type;
	__u8      peer_addr_type;
	bdaddr_t  peer_addr;
	__u8      filter_policy;
	__u8      tx_घातer;
	__u8      primary_phy;
	__u8      secondary_max_skip;
	__u8      secondary_phy;
	__u8      sid;
	__u8      notअगर_enable;
पूर्ण __packed;

#घोषणा HCI_ADV_PHY_1M		0X01
#घोषणा HCI_ADV_PHY_2M		0x02
#घोषणा HCI_ADV_PHY_CODED	0x03

काष्ठा hci_rp_le_set_ext_adv_params अणु
	__u8  status;
	__u8  tx_घातer;
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_EXT_ADV_ENABLE		0x2039
काष्ठा hci_cp_le_set_ext_adv_enable अणु
	__u8  enable;
	__u8  num_of_sets;
	__u8  data[];
पूर्ण __packed;

काष्ठा hci_cp_ext_adv_set अणु
	__u8  handle;
	__le16 duration;
	__u8  max_events;
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_EXT_ADV_DATA		0x2037
काष्ठा hci_cp_le_set_ext_adv_data अणु
	__u8  handle;
	__u8  operation;
	__u8  frag_pref;
	__u8  length;
	__u8  data[HCI_MAX_AD_LENGTH];
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_EXT_SCAN_RSP_DATA		0x2038
काष्ठा hci_cp_le_set_ext_scan_rsp_data अणु
	__u8  handle;
	__u8  operation;
	__u8  frag_pref;
	__u8  length;
	__u8  data[HCI_MAX_AD_LENGTH];
पूर्ण __packed;

#घोषणा LE_SET_ADV_DATA_OP_COMPLETE	0x03

#घोषणा LE_SET_ADV_DATA_NO_FRAG		0x01

#घोषणा HCI_OP_LE_REMOVE_ADV_SET	0x203c

#घोषणा HCI_OP_LE_CLEAR_ADV_SETS	0x203d

#घोषणा HCI_OP_LE_SET_ADV_SET_RAND_ADDR	0x2035
काष्ठा hci_cp_le_set_adv_set_अक्रम_addr अणु
	__u8  handle;
	bdaddr_t  bdaddr;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_TRANSMIT_POWER	0x204b
काष्ठा hci_rp_le_पढ़ो_transmit_घातer अणु
	__u8  status;
	__s8  min_le_tx_घातer;
	__s8  max_le_tx_घातer;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_BUFFER_SIZE_V2	0x2060
काष्ठा hci_rp_le_पढ़ो_buffer_size_v2 अणु
	__u8    status;
	__le16  acl_mtu;
	__u8    acl_max_pkt;
	__le16  iso_mtu;
	__u8    iso_max_pkt;
पूर्ण __packed;

#घोषणा HCI_OP_LE_READ_ISO_TX_SYNC		0x2061
काष्ठा hci_cp_le_पढ़ो_iso_tx_sync अणु
	__le16  handle;
पूर्ण __packed;

काष्ठा hci_rp_le_पढ़ो_iso_tx_sync अणु
	__u8    status;
	__le16  handle;
	__le16  seq;
	__le32  imestamp;
	__u8    offset[3];
पूर्ण __packed;

#घोषणा HCI_OP_LE_SET_CIG_PARAMS		0x2062
काष्ठा hci_cis_params अणु
	__u8    cis_id;
	__le16  m_sdu;
	__le16  s_sdu;
	__u8    m_phy;
	__u8    s_phy;
	__u8    m_rtn;
	__u8    s_rtn;
पूर्ण __packed;

काष्ठा hci_cp_le_set_cig_params अणु
	__u8    cig_id;
	__u8    m_पूर्णांकerval[3];
	__u8    s_पूर्णांकerval[3];
	__u8    sca;
	__u8    packing;
	__u8    framing;
	__le16  m_latency;
	__le16  s_latency;
	__u8    num_cis;
	काष्ठा hci_cis_params cis[];
पूर्ण __packed;

काष्ठा hci_rp_le_set_cig_params अणु
	__u8    status;
	__u8    cig_id;
	__u8    num_handles;
	__le16  handle[];
पूर्ण __packed;

#घोषणा HCI_OP_LE_CREATE_CIS			0x2064
काष्ठा hci_cis अणु
	__le16  cis_handle;
	__le16  acl_handle;
पूर्ण __packed;

काष्ठा hci_cp_le_create_cis अणु
	__u8    num_cis;
	काष्ठा hci_cis cis[];
पूर्ण __packed;

#घोषणा HCI_OP_LE_REMOVE_CIG			0x2065
काष्ठा hci_cp_le_हटाओ_cig अणु
	__u8    cig_id;
पूर्ण __packed;

#घोषणा HCI_OP_LE_ACCEPT_CIS			0x2066
काष्ठा hci_cp_le_accept_cis अणु
	__le16  handle;
पूर्ण __packed;

#घोषणा HCI_OP_LE_REJECT_CIS			0x2067
काष्ठा hci_cp_le_reject_cis अणु
	__le16  handle;
	__u8    reason;
पूर्ण __packed;

/* ---- HCI Events ---- */
#घोषणा HCI_EV_INQUIRY_COMPLETE		0x01

#घोषणा HCI_EV_INQUIRY_RESULT		0x02
काष्ठा inquiry_info अणु
	bdaddr_t bdaddr;
	__u8     pscan_rep_mode;
	__u8     pscan_period_mode;
	__u8     pscan_mode;
	__u8     dev_class[3];
	__le16   घड़ी_offset;
पूर्ण __packed;

#घोषणा HCI_EV_CONN_COMPLETE		0x03
काष्ठा hci_ev_conn_complete अणु
	__u8     status;
	__le16   handle;
	bdaddr_t bdaddr;
	__u8     link_type;
	__u8     encr_mode;
पूर्ण __packed;

#घोषणा HCI_EV_CONN_REQUEST		0x04
काष्ठा hci_ev_conn_request अणु
	bdaddr_t bdaddr;
	__u8     dev_class[3];
	__u8     link_type;
पूर्ण __packed;

#घोषणा HCI_EV_DISCONN_COMPLETE		0x05
काष्ठा hci_ev_disconn_complete अणु
	__u8     status;
	__le16   handle;
	__u8     reason;
पूर्ण __packed;

#घोषणा HCI_EV_AUTH_COMPLETE		0x06
काष्ठा hci_ev_auth_complete अणु
	__u8     status;
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_EV_REMOTE_NAME		0x07
काष्ठा hci_ev_remote_name अणु
	__u8     status;
	bdaddr_t bdaddr;
	__u8     name[HCI_MAX_NAME_LENGTH];
पूर्ण __packed;

#घोषणा HCI_EV_ENCRYPT_CHANGE		0x08
काष्ठा hci_ev_encrypt_change अणु
	__u8     status;
	__le16   handle;
	__u8     encrypt;
पूर्ण __packed;

#घोषणा HCI_EV_CHANGE_LINK_KEY_COMPLETE	0x09
काष्ठा hci_ev_change_link_key_complete अणु
	__u8     status;
	__le16   handle;
पूर्ण __packed;

#घोषणा HCI_EV_REMOTE_FEATURES		0x0b
काष्ठा hci_ev_remote_features अणु
	__u8     status;
	__le16   handle;
	__u8     features[8];
पूर्ण __packed;

#घोषणा HCI_EV_REMOTE_VERSION		0x0c
काष्ठा hci_ev_remote_version अणु
	__u8     status;
	__le16   handle;
	__u8     lmp_ver;
	__le16   manufacturer;
	__le16   lmp_subver;
पूर्ण __packed;

#घोषणा HCI_EV_QOS_SETUP_COMPLETE	0x0d
काष्ठा hci_qos अणु
	__u8     service_type;
	__u32    token_rate;
	__u32    peak_bandwidth;
	__u32    latency;
	__u32    delay_variation;
पूर्ण __packed;
काष्ठा hci_ev_qos_setup_complete अणु
	__u8     status;
	__le16   handle;
	काष्ठा   hci_qos qos;
पूर्ण __packed;

#घोषणा HCI_EV_CMD_COMPLETE		0x0e
काष्ठा hci_ev_cmd_complete अणु
	__u8     ncmd;
	__le16   opcode;
पूर्ण __packed;

#घोषणा HCI_EV_CMD_STATUS		0x0f
काष्ठा hci_ev_cmd_status अणु
	__u8     status;
	__u8     ncmd;
	__le16   opcode;
पूर्ण __packed;

#घोषणा HCI_EV_HARDWARE_ERROR		0x10
काष्ठा hci_ev_hardware_error अणु
	__u8     code;
पूर्ण __packed;

#घोषणा HCI_EV_ROLE_CHANGE		0x12
काष्ठा hci_ev_role_change अणु
	__u8     status;
	bdaddr_t bdaddr;
	__u8     role;
पूर्ण __packed;

#घोषणा HCI_EV_NUM_COMP_PKTS		0x13
काष्ठा hci_comp_pkts_info अणु
	__le16   handle;
	__le16   count;
पूर्ण __packed;

काष्ठा hci_ev_num_comp_pkts अणु
	__u8     num_hndl;
	काष्ठा hci_comp_pkts_info handles[];
पूर्ण __packed;

#घोषणा HCI_EV_MODE_CHANGE		0x14
काष्ठा hci_ev_mode_change अणु
	__u8     status;
	__le16   handle;
	__u8     mode;
	__le16   पूर्णांकerval;
पूर्ण __packed;

#घोषणा HCI_EV_PIN_CODE_REQ		0x16
काष्ठा hci_ev_pin_code_req अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_EV_LINK_KEY_REQ		0x17
काष्ठा hci_ev_link_key_req अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_EV_LINK_KEY_NOTIFY		0x18
काष्ठा hci_ev_link_key_notअगरy अणु
	bdaddr_t bdaddr;
	__u8     link_key[HCI_LINK_KEY_SIZE];
	__u8     key_type;
पूर्ण __packed;

#घोषणा HCI_EV_CLOCK_OFFSET		0x1c
काष्ठा hci_ev_घड़ी_offset अणु
	__u8     status;
	__le16   handle;
	__le16   घड़ी_offset;
पूर्ण __packed;

#घोषणा HCI_EV_PKT_TYPE_CHANGE		0x1d
काष्ठा hci_ev_pkt_type_change अणु
	__u8     status;
	__le16   handle;
	__le16   pkt_type;
पूर्ण __packed;

#घोषणा HCI_EV_PSCAN_REP_MODE		0x20
काष्ठा hci_ev_pscan_rep_mode अणु
	bdaddr_t bdaddr;
	__u8     pscan_rep_mode;
पूर्ण __packed;

#घोषणा HCI_EV_INQUIRY_RESULT_WITH_RSSI	0x22
काष्ठा inquiry_info_with_rssi अणु
	bdaddr_t bdaddr;
	__u8     pscan_rep_mode;
	__u8     pscan_period_mode;
	__u8     dev_class[3];
	__le16   घड़ी_offset;
	__s8     rssi;
पूर्ण __packed;
काष्ठा inquiry_info_with_rssi_and_pscan_mode अणु
	bdaddr_t bdaddr;
	__u8     pscan_rep_mode;
	__u8     pscan_period_mode;
	__u8     pscan_mode;
	__u8     dev_class[3];
	__le16   घड़ी_offset;
	__s8     rssi;
पूर्ण __packed;

#घोषणा HCI_EV_REMOTE_EXT_FEATURES	0x23
काष्ठा hci_ev_remote_ext_features अणु
	__u8     status;
	__le16   handle;
	__u8     page;
	__u8     max_page;
	__u8     features[8];
पूर्ण __packed;

#घोषणा HCI_EV_SYNC_CONN_COMPLETE	0x2c
काष्ठा hci_ev_sync_conn_complete अणु
	__u8     status;
	__le16   handle;
	bdaddr_t bdaddr;
	__u8     link_type;
	__u8     tx_पूर्णांकerval;
	__u8     retrans_winकरोw;
	__le16   rx_pkt_len;
	__le16   tx_pkt_len;
	__u8     air_mode;
पूर्ण __packed;

#घोषणा HCI_EV_SYNC_CONN_CHANGED	0x2d
काष्ठा hci_ev_sync_conn_changed अणु
	__u8     status;
	__le16   handle;
	__u8     tx_पूर्णांकerval;
	__u8     retrans_winकरोw;
	__le16   rx_pkt_len;
	__le16   tx_pkt_len;
पूर्ण __packed;

#घोषणा HCI_EV_SNIFF_SUBRATE		0x2e
काष्ठा hci_ev_snअगरf_subrate अणु
	__u8     status;
	__le16   handle;
	__le16   max_tx_latency;
	__le16   max_rx_latency;
	__le16   max_remote_समयout;
	__le16   max_local_समयout;
पूर्ण __packed;

#घोषणा HCI_EV_EXTENDED_INQUIRY_RESULT	0x2f
काष्ठा extended_inquiry_info अणु
	bdaddr_t bdaddr;
	__u8     pscan_rep_mode;
	__u8     pscan_period_mode;
	__u8     dev_class[3];
	__le16   घड़ी_offset;
	__s8     rssi;
	__u8     data[240];
पूर्ण __packed;

#घोषणा HCI_EV_KEY_REFRESH_COMPLETE	0x30
काष्ठा hci_ev_key_refresh_complete अणु
	__u8	status;
	__le16	handle;
पूर्ण __packed;

#घोषणा HCI_EV_IO_CAPA_REQUEST		0x31
काष्ठा hci_ev_io_capa_request अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_EV_IO_CAPA_REPLY		0x32
काष्ठा hci_ev_io_capa_reply अणु
	bdaddr_t bdaddr;
	__u8     capability;
	__u8     oob_data;
	__u8     authentication;
पूर्ण __packed;

#घोषणा HCI_EV_USER_CONFIRM_REQUEST	0x33
काष्ठा hci_ev_user_confirm_req अणु
	bdaddr_t	bdaddr;
	__le32		passkey;
पूर्ण __packed;

#घोषणा HCI_EV_USER_PASSKEY_REQUEST	0x34
काष्ठा hci_ev_user_passkey_req अणु
	bdaddr_t	bdaddr;
पूर्ण __packed;

#घोषणा HCI_EV_REMOTE_OOB_DATA_REQUEST	0x35
काष्ठा hci_ev_remote_oob_data_request अणु
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_EV_SIMPLE_PAIR_COMPLETE	0x36
काष्ठा hci_ev_simple_pair_complete अणु
	__u8     status;
	bdaddr_t bdaddr;
पूर्ण __packed;

#घोषणा HCI_EV_USER_PASSKEY_NOTIFY	0x3b
काष्ठा hci_ev_user_passkey_notअगरy अणु
	bdaddr_t	bdaddr;
	__le32		passkey;
पूर्ण __packed;

#घोषणा HCI_KEYPRESS_STARTED		0
#घोषणा HCI_KEYPRESS_ENTERED		1
#घोषणा HCI_KEYPRESS_ERASED		2
#घोषणा HCI_KEYPRESS_CLEARED		3
#घोषणा HCI_KEYPRESS_COMPLETED		4

#घोषणा HCI_EV_KEYPRESS_NOTIFY		0x3c
काष्ठा hci_ev_keypress_notअगरy अणु
	bdaddr_t	bdaddr;
	__u8		type;
पूर्ण __packed;

#घोषणा HCI_EV_REMOTE_HOST_FEATURES	0x3d
काष्ठा hci_ev_remote_host_features अणु
	bdaddr_t bdaddr;
	__u8     features[8];
पूर्ण __packed;

#घोषणा HCI_EV_LE_META			0x3e
काष्ठा hci_ev_le_meta अणु
	__u8     subevent;
पूर्ण __packed;

#घोषणा HCI_EV_PHY_LINK_COMPLETE	0x40
काष्ठा hci_ev_phy_link_complete अणु
	__u8     status;
	__u8     phy_handle;
पूर्ण __packed;

#घोषणा HCI_EV_CHANNEL_SELECTED		0x41
काष्ठा hci_ev_channel_selected अणु
	__u8     phy_handle;
पूर्ण __packed;

#घोषणा HCI_EV_DISCONN_PHY_LINK_COMPLETE	0x42
काष्ठा hci_ev_disconn_phy_link_complete अणु
	__u8     status;
	__u8     phy_handle;
	__u8     reason;
पूर्ण __packed;

#घोषणा HCI_EV_LOGICAL_LINK_COMPLETE		0x45
काष्ठा hci_ev_logical_link_complete अणु
	__u8     status;
	__le16   handle;
	__u8     phy_handle;
	__u8     flow_spec_id;
पूर्ण __packed;

#घोषणा HCI_EV_DISCONN_LOGICAL_LINK_COMPLETE	0x46
काष्ठा hci_ev_disconn_logical_link_complete अणु
	__u8     status;
	__le16   handle;
	__u8     reason;
पूर्ण __packed;

#घोषणा HCI_EV_NUM_COMP_BLOCKS		0x48
काष्ठा hci_comp_blocks_info अणु
	__le16   handle;
	__le16   pkts;
	__le16   blocks;
पूर्ण __packed;

काष्ठा hci_ev_num_comp_blocks अणु
	__le16   num_blocks;
	__u8     num_hndl;
	काष्ठा hci_comp_blocks_info handles[];
पूर्ण __packed;

#घोषणा HCI_EV_SYNC_TRAIN_COMPLETE	0x4F
काष्ठा hci_ev_sync_train_complete अणु
	__u8	status;
पूर्ण __packed;

#घोषणा HCI_EV_SLAVE_PAGE_RESP_TIMEOUT	0x54

#घोषणा HCI_EV_LE_CONN_COMPLETE		0x01
काष्ठा hci_ev_le_conn_complete अणु
	__u8     status;
	__le16   handle;
	__u8     role;
	__u8     bdaddr_type;
	bdaddr_t bdaddr;
	__le16   पूर्णांकerval;
	__le16   latency;
	__le16   supervision_समयout;
	__u8     clk_accurancy;
पूर्ण __packed;

/* Advertising report event types */
#घोषणा LE_ADV_IND		0x00
#घोषणा LE_ADV_सूचीECT_IND	0x01
#घोषणा LE_ADV_SCAN_IND		0x02
#घोषणा LE_ADV_NONCONN_IND	0x03
#घोषणा LE_ADV_SCAN_RSP		0x04
#घोषणा LE_ADV_INVALID		0x05

/* Legacy event types in extended adv report */
#घोषणा LE_LEGACY_ADV_IND		0x0013
#घोषणा LE_LEGACY_ADV_सूचीECT_IND 	0x0015
#घोषणा LE_LEGACY_ADV_SCAN_IND		0x0012
#घोषणा LE_LEGACY_NONCONN_IND		0x0010
#घोषणा LE_LEGACY_SCAN_RSP_ADV		0x001b
#घोषणा LE_LEGACY_SCAN_RSP_ADV_SCAN	0x001a

/* Extended Advertising event types */
#घोषणा LE_EXT_ADV_NON_CONN_IND		0x0000
#घोषणा LE_EXT_ADV_CONN_IND		0x0001
#घोषणा LE_EXT_ADV_SCAN_IND		0x0002
#घोषणा LE_EXT_ADV_सूचीECT_IND		0x0004
#घोषणा LE_EXT_ADV_SCAN_RSP		0x0008
#घोषणा LE_EXT_ADV_LEGACY_PDU		0x0010

#घोषणा ADDR_LE_DEV_PUBLIC		0x00
#घोषणा ADDR_LE_DEV_RANDOM		0x01
#घोषणा ADDR_LE_DEV_PUBLIC_RESOLVED	0x02
#घोषणा ADDR_LE_DEV_RANDOM_RESOLVED	0x03

#घोषणा HCI_EV_LE_ADVERTISING_REPORT	0x02
काष्ठा hci_ev_le_advertising_info अणु
	__u8	 evt_type;
	__u8	 bdaddr_type;
	bdaddr_t bdaddr;
	__u8	 length;
	__u8	 data[];
पूर्ण __packed;

#घोषणा HCI_EV_LE_CONN_UPDATE_COMPLETE	0x03
काष्ठा hci_ev_le_conn_update_complete अणु
	__u8     status;
	__le16   handle;
	__le16   पूर्णांकerval;
	__le16   latency;
	__le16   supervision_समयout;
पूर्ण __packed;

#घोषणा HCI_EV_LE_REMOTE_FEAT_COMPLETE	0x04
काष्ठा hci_ev_le_remote_feat_complete अणु
	__u8     status;
	__le16   handle;
	__u8     features[8];
पूर्ण __packed;

#घोषणा HCI_EV_LE_LTK_REQ		0x05
काष्ठा hci_ev_le_ltk_req अणु
	__le16	handle;
	__le64	अक्रम;
	__le16	eभाग;
पूर्ण __packed;

#घोषणा HCI_EV_LE_REMOTE_CONN_PARAM_REQ	0x06
काष्ठा hci_ev_le_remote_conn_param_req अणु
	__le16 handle;
	__le16 पूर्णांकerval_min;
	__le16 पूर्णांकerval_max;
	__le16 latency;
	__le16 समयout;
पूर्ण __packed;

#घोषणा HCI_EV_LE_DATA_LEN_CHANGE	0x07
काष्ठा hci_ev_le_data_len_change अणु
	__le16	handle;
	__le16	tx_len;
	__le16	tx_समय;
	__le16	rx_len;
	__le16	rx_समय;
पूर्ण __packed;

#घोषणा HCI_EV_LE_सूचीECT_ADV_REPORT	0x0B
काष्ठा hci_ev_le_direct_adv_info अणु
	__u8	 evt_type;
	__u8	 bdaddr_type;
	bdaddr_t bdaddr;
	__u8	 direct_addr_type;
	bdaddr_t direct_addr;
	__s8	 rssi;
पूर्ण __packed;

#घोषणा HCI_EV_LE_PHY_UPDATE_COMPLETE	0x0c
काष्ठा hci_ev_le_phy_update_complete अणु
	__u8  status;
	__le16 handle;
	__u8  tx_phy;
	__u8  rx_phy;
पूर्ण __packed;

#घोषणा HCI_EV_LE_EXT_ADV_REPORT    0x0d
काष्ठा hci_ev_le_ext_adv_report अणु
	__le16 	 evt_type;
	__u8	 bdaddr_type;
	bdaddr_t bdaddr;
	__u8	 primary_phy;
	__u8	 secondary_phy;
	__u8	 sid;
	__u8	 tx_घातer;
	__s8	 rssi;
	__le16 	 पूर्णांकerval;
	__u8  	 direct_addr_type;
	bdaddr_t direct_addr;
	__u8  	 length;
	__u8	 data[];
पूर्ण __packed;

#घोषणा HCI_EV_LE_ENHANCED_CONN_COMPLETE    0x0a
काष्ठा hci_ev_le_enh_conn_complete अणु
	__u8      status;
	__le16    handle;
	__u8      role;
	__u8      bdaddr_type;
	bdaddr_t  bdaddr;
	bdaddr_t  local_rpa;
	bdaddr_t  peer_rpa;
	__le16    पूर्णांकerval;
	__le16    latency;
	__le16    supervision_समयout;
	__u8      clk_accurancy;
पूर्ण __packed;

#घोषणा HCI_EV_LE_EXT_ADV_SET_TERM	0x12
काष्ठा hci_evt_le_ext_adv_set_term अणु
	__u8	status;
	__u8	handle;
	__le16	conn_handle;
	__u8	num_evts;
पूर्ण __packed;

#घोषणा HCI_EVT_LE_CIS_ESTABLISHED	0x19
काष्ठा hci_evt_le_cis_established अणु
	__u8  status;
	__le16 handle;
	__u8  cig_sync_delay[3];
	__u8  cis_sync_delay[3];
	__u8  m_latency[3];
	__u8  s_latency[3];
	__u8  m_phy;
	__u8  s_phy;
	__u8  nse;
	__u8  m_bn;
	__u8  s_bn;
	__u8  m_ft;
	__u8  s_ft;
	__le16 m_mtu;
	__le16 s_mtu;
	__le16 पूर्णांकerval;
पूर्ण __packed;

#घोषणा HCI_EVT_LE_CIS_REQ		0x1a
काष्ठा hci_evt_le_cis_req अणु
	__le16 acl_handle;
	__le16 cis_handle;
	__u8  cig_id;
	__u8  cis_id;
पूर्ण __packed;

#घोषणा HCI_EV_VENDOR			0xff

/* Internal events generated by Bluetooth stack */
#घोषणा HCI_EV_STACK_INTERNAL	0xfd
काष्ठा hci_ev_stack_पूर्णांकernal अणु
	__u16    type;
	__u8     data[];
पूर्ण __packed;

#घोषणा HCI_EV_SI_DEVICE	0x01
काष्ठा hci_ev_si_device अणु
	__u16    event;
	__u16    dev_id;
पूर्ण __packed;

#घोषणा HCI_EV_SI_SECURITY	0x02
काष्ठा hci_ev_si_security अणु
	__u16    event;
	__u16    proto;
	__u16    subproto;
	__u8     incoming;
पूर्ण __packed;

/* ---- HCI Packet काष्ठाures ---- */
#घोषणा HCI_COMMAND_HDR_SIZE 3
#घोषणा HCI_EVENT_HDR_SIZE   2
#घोषणा HCI_ACL_HDR_SIZE     4
#घोषणा HCI_SCO_HDR_SIZE     3
#घोषणा HCI_ISO_HDR_SIZE     4

काष्ठा hci_command_hdr अणु
	__le16	opcode;		/* OCF & OGF */
	__u8	plen;
पूर्ण __packed;

काष्ठा hci_event_hdr अणु
	__u8	evt;
	__u8	plen;
पूर्ण __packed;

काष्ठा hci_acl_hdr अणु
	__le16	handle;		/* Handle & Flags(PB, BC) */
	__le16	dlen;
पूर्ण __packed;

काष्ठा hci_sco_hdr अणु
	__le16	handle;
	__u8	dlen;
पूर्ण __packed;

काष्ठा hci_iso_hdr अणु
	__le16	handle;
	__le16	dlen;
	__u8	data[];
पूर्ण __packed;

/* ISO data packet status flags */
#घोषणा HCI_ISO_STATUS_VALID	0x00
#घोषणा HCI_ISO_STATUS_INVALID	0x01
#घोषणा HCI_ISO_STATUS_NOP	0x02

#घोषणा HCI_ISO_DATA_HDR_SIZE	4
काष्ठा hci_iso_data_hdr अणु
	__le16	sn;
	__le16	slen;
पूर्ण;

#घोषणा HCI_ISO_TS_DATA_HDR_SIZE 8
काष्ठा hci_iso_ts_data_hdr अणु
	__le32	ts;
	__le16	sn;
	__le16	slen;
पूर्ण;

अटल अंतरभूत काष्ठा hci_event_hdr *hci_event_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा hci_event_hdr *) skb->data;
पूर्ण

अटल अंतरभूत काष्ठा hci_acl_hdr *hci_acl_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा hci_acl_hdr *) skb->data;
पूर्ण

अटल अंतरभूत काष्ठा hci_sco_hdr *hci_sco_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा hci_sco_hdr *) skb->data;
पूर्ण

/* Command opcode pack/unpack */
#घोषणा hci_opcode_pack(ogf, ocf)	((__u16) ((ocf & 0x03ff)|(ogf << 10)))
#घोषणा hci_opcode_ogf(op)		(op >> 10)
#घोषणा hci_opcode_ocf(op)		(op & 0x03ff)

/* ACL handle and flags pack/unpack */
#घोषणा hci_handle_pack(h, f)	((__u16) ((h & 0x0fff)|(f << 12)))
#घोषणा hci_handle(h)		(h & 0x0fff)
#घोषणा hci_flags(h)		(h >> 12)

/* ISO handle and flags pack/unpack */
#घोषणा hci_iso_flags_pb(f)		(f & 0x0003)
#घोषणा hci_iso_flags_ts(f)		((f >> 2) & 0x0001)
#घोषणा hci_iso_flags_pack(pb, ts)	((pb & 0x03) | ((ts & 0x01) << 2))

/* ISO data length and flags pack/unpack */
#घोषणा hci_iso_data_len_pack(h, f)	((__u16) ((h) | ((f) << 14)))
#घोषणा hci_iso_data_len(h)		((h) & 0x3fff)
#घोषणा hci_iso_data_flags(h)		((h) >> 14)

/* le24 support */
अटल अंतरभूत व्योम hci_cpu_to_le24(__u32 val, __u8 dst[3])
अणु
	dst[0] = val & 0xff;
	dst[1] = (val & 0xff00) >> 8;
	dst[2] = (val & 0xff0000) >> 16;
पूर्ण

#पूर्ण_अगर /* __HCI_H */
