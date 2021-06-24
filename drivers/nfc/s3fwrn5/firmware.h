<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NCI based driver क्रम Samsung S3FWRN5 NFC chip
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 */

#अगर_अघोषित __LOCAL_S3FWRN5_FIRMWARE_H_
#घोषणा __LOCAL_S3FWRN5_FIRMWARE_H_

/* FW Message Types */
#घोषणा S3FWRN5_FW_MSG_CMD			0x00
#घोषणा S3FWRN5_FW_MSG_RSP			0x01
#घोषणा S3FWRN5_FW_MSG_DATA			0x02

/* FW Return Codes */
#घोषणा S3FWRN5_FW_RET_SUCCESS			0x00
#घोषणा S3FWRN5_FW_RET_MESSAGE_TYPE_INVALID	0x01
#घोषणा S3FWRN5_FW_RET_COMMAND_INVALID		0x02
#घोषणा S3FWRN5_FW_RET_PAGE_DATA_OVERFLOW	0x03
#घोषणा S3FWRN5_FW_RET_SECT_DATA_OVERFLOW	0x04
#घोषणा S3FWRN5_FW_RET_AUTHENTICATION_FAIL	0x05
#घोषणा S3FWRN5_FW_RET_FLASH_OPERATION_FAIL	0x06
#घोषणा S3FWRN5_FW_RET_ADDRESS_OUT_OF_RANGE	0x07
#घोषणा S3FWRN5_FW_RET_PARAMETER_INVALID	0x08

/* ---- FW Packet काष्ठाures ---- */
#घोषणा S3FWRN5_FW_HDR_SIZE 4

काष्ठा s3fwrn5_fw_header अणु
	__u8 type;
	__u8 code;
	__u16 len;
पूर्ण;

#घोषणा S3FWRN5_FW_CMD_RESET			0x00

#घोषणा S3FWRN5_FW_CMD_GET_BOOTINFO		0x01

काष्ठा s3fwrn5_fw_cmd_get_bootinfo_rsp अणु
	__u8 hw_version[4];
	__u16 sector_size;
	__u16 page_size;
	__u16 frame_max_size;
	__u16 hw_buffer_size;
पूर्ण;

#घोषणा S3FWRN5_FW_CMD_ENTER_UPDATE_MODE	0x02

काष्ठा s3fwrn5_fw_cmd_enter_updatemode अणु
	__u16 hashcode_size;
	__u16 signature_size;
पूर्ण;

#घोषणा S3FWRN5_FW_CMD_UPDATE_SECTOR		0x04

काष्ठा s3fwrn5_fw_cmd_update_sector अणु
	__u32 base_address;
पूर्ण;

#घोषणा S3FWRN5_FW_CMD_COMPLETE_UPDATE_MODE	0x05

काष्ठा s3fwrn5_fw_image अणु
	स्थिर काष्ठा firmware *fw;

	अक्षर date[13];
	u32 version;
	स्थिर व्योम *sig;
	u32 sig_size;
	स्थिर व्योम *image;
	u32 image_sectors;
	स्थिर व्योम *custom_sig;
	u32 custom_sig_size;
पूर्ण;

काष्ठा s3fwrn5_fw_info अणु
	काष्ठा nci_dev *ndev;
	काष्ठा s3fwrn5_fw_image fw;
	अक्षर fw_name[NFC_FIRMWARE_NAME_MAXSIZE + 1];

	स्थिर व्योम *sig;
	u32 sig_size;
	u32 sector_size;
	u32 base_addr;

	काष्ठा completion completion;
	काष्ठा sk_buff *rsp;
	अक्षर parity;
पूर्ण;

पूर्णांक s3fwrn5_fw_request_firmware(काष्ठा s3fwrn5_fw_info *fw_info);
व्योम s3fwrn5_fw_init(काष्ठा s3fwrn5_fw_info *fw_info, स्थिर अक्षर *fw_name);
पूर्णांक s3fwrn5_fw_setup(काष्ठा s3fwrn5_fw_info *fw_info);
bool s3fwrn5_fw_check_version(स्थिर काष्ठा s3fwrn5_fw_info *fw_info, u32 version);
पूर्णांक s3fwrn5_fw_करोwnload(काष्ठा s3fwrn5_fw_info *fw_info);
व्योम s3fwrn5_fw_cleanup(काष्ठा s3fwrn5_fw_info *fw_info);

पूर्णांक s3fwrn5_fw_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);

#पूर्ण_अगर /* __LOCAL_S3FWRN5_FIRMWARE_H_ */
