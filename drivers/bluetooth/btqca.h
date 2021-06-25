<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Bluetooth supports क्रम Qualcomm Atheros ROME chips
 *
 *  Copyright (c) 2015 The Linux Foundation. All rights reserved.
 */

#घोषणा EDL_PATCH_CMD_OPCODE		(0xFC00)
#घोषणा EDL_NVM_ACCESS_OPCODE		(0xFC0B)
#घोषणा EDL_WRITE_BD_ADDR_OPCODE	(0xFC14)
#घोषणा EDL_PATCH_CMD_LEN		(1)
#घोषणा EDL_PATCH_VER_REQ_CMD		(0x19)
#घोषणा EDL_PATCH_TLV_REQ_CMD		(0x1E)
#घोषणा EDL_GET_BUILD_INFO_CMD		(0x20)
#घोषणा EDL_NVM_ACCESS_SET_REQ_CMD	(0x01)
#घोषणा MAX_SIZE_PER_TLV_SEGMENT	(243)
#घोषणा QCA_PRE_SHUTDOWN_CMD		(0xFC08)
#घोषणा QCA_DISABLE_LOGGING		(0xFC17)

#घोषणा EDL_CMD_REQ_RES_EVT		(0x00)
#घोषणा EDL_PATCH_VER_RES_EVT		(0x19)
#घोषणा EDL_APP_VER_RES_EVT		(0x02)
#घोषणा EDL_TVL_DNLD_RES_EVT		(0x04)
#घोषणा EDL_CMD_EXE_STATUS_EVT		(0x00)
#घोषणा EDL_SET_BAUDRATE_RSP_EVT	(0x92)
#घोषणा EDL_NVM_ACCESS_CODE_EVT		(0x0B)
#घोषणा QCA_DISABLE_LOGGING_SUB_OP	(0x14)

#घोषणा EDL_TAG_ID_HCI			(17)
#घोषणा EDL_TAG_ID_DEEP_SLEEP		(27)

#घोषणा QCA_WCN3990_POWERON_PULSE	0xFC
#घोषणा QCA_WCN3990_POWEROFF_PULSE	0xC0

#घोषणा QCA_HCI_CC_OPCODE		0xFC00
#घोषणा QCA_HCI_CC_SUCCESS		0x00

#घोषणा QCA_WCN3991_SOC_ID		(0x40014320)

/* QCA chipset version can be decided by patch and SoC
 * version, combination with upper 2 bytes from SoC
 * and lower 2 bytes from patch will be used.
 */
#घोषणा get_soc_ver(soc_id, rom_ver)	\
	((le32_to_cpu(soc_id) << 16) | (le16_to_cpu(rom_ver)))

#घोषणा QCA_FW_BUILD_VER_LEN		255


क्रमागत qca_baudrate अणु
	QCA_BAUDRATE_115200 	= 0,
	QCA_BAUDRATE_57600,
	QCA_BAUDRATE_38400,
	QCA_BAUDRATE_19200,
	QCA_BAUDRATE_9600,
	QCA_BAUDRATE_230400,
	QCA_BAUDRATE_250000,
	QCA_BAUDRATE_460800,
	QCA_BAUDRATE_500000,
	QCA_BAUDRATE_720000,
	QCA_BAUDRATE_921600,
	QCA_BAUDRATE_1000000,
	QCA_BAUDRATE_1250000,
	QCA_BAUDRATE_2000000,
	QCA_BAUDRATE_3000000,
	QCA_BAUDRATE_4000000,
	QCA_BAUDRATE_1600000,
	QCA_BAUDRATE_3200000,
	QCA_BAUDRATE_3500000,
	QCA_BAUDRATE_AUTO 	= 0xFE,
	QCA_BAUDRATE_RESERVED
पूर्ण;

क्रमागत qca_tlv_dnld_mode अणु
	QCA_SKIP_EVT_NONE,
	QCA_SKIP_EVT_VSE,
	QCA_SKIP_EVT_CC,
	QCA_SKIP_EVT_VSE_CC
पूर्ण;

क्रमागत qca_tlv_type अणु
	TLV_TYPE_PATCH = 1,
	TLV_TYPE_NVM
पूर्ण;

काष्ठा qca_fw_config अणु
	u8 type;
	अक्षर fwname[64];
	uपूर्णांक8_t user_baud_rate;
	क्रमागत qca_tlv_dnld_mode dnld_mode;
	क्रमागत qca_tlv_dnld_mode dnld_type;
पूर्ण;

काष्ठा edl_event_hdr अणु
	__u8 cresp;
	__u8 rtype;
	__u8 data[];
पूर्ण __packed;

काष्ठा qca_btsoc_version अणु
	__le32 product_id;
	__le16 patch_ver;
	__le16 rom_ver;
	__le32 soc_id;
पूर्ण __packed;

काष्ठा tlv_seg_resp अणु
	__u8 result;
पूर्ण __packed;

काष्ठा tlv_type_patch अणु
	__le32 total_size;
	__le32 data_length;
	__u8   क्रमmat_version;
	__u8   signature;
	__u8   करोwnload_mode;
	__u8   reserved1;
	__le16 product_id;
	__le16 rom_build;
	__le16 patch_version;
	__le16 reserved2;
	__le32 entry;
पूर्ण __packed;

काष्ठा tlv_type_nvm अणु
	__le16 tag_id;
	__le16 tag_len;
	__le32 reserve1;
	__le32 reserve2;
	__u8   data[];
पूर्ण __packed;

काष्ठा tlv_type_hdr अणु
	__le32 type_len;
	__u8   data[];
पूर्ण __packed;

क्रमागत qca_btsoc_type अणु
	QCA_INVALID = -1,
	QCA_AR3002,
	QCA_ROME,
	QCA_WCN3990,
	QCA_WCN3998,
	QCA_WCN3991,
	QCA_QCA6390,
पूर्ण;

#अगर IS_ENABLED(CONFIG_BT_QCA)

पूर्णांक qca_set_bdaddr_rome(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr);
पूर्णांक qca_uart_setup(काष्ठा hci_dev *hdev, uपूर्णांक8_t baudrate,
		   क्रमागत qca_btsoc_type soc_type, काष्ठा qca_btsoc_version ver,
		   स्थिर अक्षर *firmware_name);
पूर्णांक qca_पढ़ो_soc_version(काष्ठा hci_dev *hdev, काष्ठा qca_btsoc_version *ver,
			 क्रमागत qca_btsoc_type);
पूर्णांक qca_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr);
पूर्णांक qca_send_pre_shutकरोwn_cmd(काष्ठा hci_dev *hdev);
अटल अंतरभूत bool qca_is_wcn399x(क्रमागत qca_btsoc_type soc_type)
अणु
	वापस soc_type == QCA_WCN3990 || soc_type == QCA_WCN3991 ||
	       soc_type == QCA_WCN3998;
पूर्ण
#अन्यथा

अटल अंतरभूत पूर्णांक qca_set_bdaddr_rome(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक qca_uart_setup(काष्ठा hci_dev *hdev, uपूर्णांक8_t baudrate,
				 क्रमागत qca_btsoc_type soc_type,
				 काष्ठा qca_btsoc_version ver,
				 स्थिर अक्षर *firmware_name)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक qca_पढ़ो_soc_version(काष्ठा hci_dev *hdev,
				       काष्ठा qca_btsoc_version *ver,
				       क्रमागत qca_btsoc_type)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक qca_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool qca_is_wcn399x(क्रमागत qca_btsoc_type soc_type)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक qca_send_pre_shutकरोwn_cmd(काष्ठा hci_dev *hdev)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर
