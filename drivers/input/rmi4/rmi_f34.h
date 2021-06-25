<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2007-2016, Synaptics Incorporated
 * Copyright (C) 2016 Zodiac Inflight Innovations
 */

#अगर_अघोषित _RMI_F34_H
#घोषणा _RMI_F34_H

/* F34 image file offsets. */
#घोषणा F34_FW_IMAGE_OFFSET	0x100

/* F34 रेजिस्टर offsets. */
#घोषणा F34_BLOCK_DATA_OFFSET	2

/* F34 commands */
#घोषणा F34_WRITE_FW_BLOCK	0x2
#घोषणा F34_ERASE_ALL		0x3
#घोषणा F34_READ_CONFIG_BLOCK	0x5
#घोषणा F34_WRITE_CONFIG_BLOCK	0x6
#घोषणा F34_ERASE_CONFIG	0x7
#घोषणा F34_ENABLE_FLASH_PROG	0xf

#घोषणा F34_STATUS_IN_PROGRESS	0xff
#घोषणा F34_STATUS_IDLE		0x80

#घोषणा F34_IDLE_WAIT_MS	500
#घोषणा F34_ENABLE_WAIT_MS	300
#घोषणा F34_ERASE_WAIT_MS	5000
#घोषणा F34_WRITE_WAIT_MS	3000

#घोषणा F34_BOOTLOADER_ID_LEN	2

/* F34 V7 defines */
#घोषणा V7_FLASH_STATUS_OFFSET		0
#घोषणा V7_PARTITION_ID_OFFSET		1
#घोषणा V7_BLOCK_NUMBER_OFFSET		2
#घोषणा V7_TRANSFER_LENGTH_OFFSET	3
#घोषणा V7_COMMAND_OFFSET		4
#घोषणा V7_PAYLOAD_OFFSET		5
#घोषणा V7_BOOTLOADER_ID_OFFSET		1

#घोषणा IMAGE_HEADER_VERSION_10		0x10

#घोषणा CONFIG_ID_SIZE			32
#घोषणा PRODUCT_ID_SIZE			10


#घोषणा HAS_BSR				BIT(5)
#घोषणा HAS_CONFIG_ID			BIT(3)
#घोषणा HAS_GUEST_CODE			BIT(6)
#घोषणा HAS_DISP_CFG			BIT(5)

/* F34 V7 commands */
#घोषणा CMD_V7_IDLE			0
#घोषणा CMD_V7_ENTER_BL			1
#घोषणा CMD_V7_READ			2
#घोषणा CMD_V7_WRITE			3
#घोषणा CMD_V7_ERASE			4
#घोषणा CMD_V7_ERASE_AP			5
#घोषणा CMD_V7_SENSOR_ID		6

#घोषणा v7_CMD_IDLE			0
#घोषणा v7_CMD_WRITE_FW			1
#घोषणा v7_CMD_WRITE_CONFIG		2
#घोषणा v7_CMD_WRITE_LOCKDOWN		3
#घोषणा v7_CMD_WRITE_GUEST_CODE		4
#घोषणा v7_CMD_READ_CONFIG		5
#घोषणा v7_CMD_ERASE_ALL		6
#घोषणा v7_CMD_ERASE_UI_FIRMWARE	7
#घोषणा v7_CMD_ERASE_UI_CONFIG		8
#घोषणा v7_CMD_ERASE_BL_CONFIG		9
#घोषणा v7_CMD_ERASE_DISP_CONFIG	10
#घोषणा v7_CMD_ERASE_FLASH_CONFIG	11
#घोषणा v7_CMD_ERASE_GUEST_CODE		12
#घोषणा v7_CMD_ENABLE_FLASH_PROG	13

#घोषणा v7_UI_CONFIG_AREA		0
#घोषणा v7_PM_CONFIG_AREA		1
#घोषणा v7_BL_CONFIG_AREA		2
#घोषणा v7_DP_CONFIG_AREA		3
#घोषणा v7_FLASH_CONFIG_AREA		4

/* F34 V7 partition IDs */
#घोषणा BOOTLOADER_PARTITION		1
#घोषणा DEVICE_CONFIG_PARTITION		2
#घोषणा FLASH_CONFIG_PARTITION		3
#घोषणा MANUFACTURING_BLOCK_PARTITION	4
#घोषणा GUEST_SERIALIZATION_PARTITION	5
#घोषणा GLOBAL_PARAMETERS_PARTITION	6
#घोषणा CORE_CODE_PARTITION		7
#घोषणा CORE_CONFIG_PARTITION		8
#घोषणा GUEST_CODE_PARTITION		9
#घोषणा DISPLAY_CONFIG_PARTITION	10

/* F34 V7 container IDs */
#घोषणा TOP_LEVEL_CONTAINER			0
#घोषणा UI_CONTAINER				1
#घोषणा UI_CONFIG_CONTAINER			2
#घोषणा BL_CONTAINER				3
#घोषणा BL_IMAGE_CONTAINER			4
#घोषणा BL_CONFIG_CONTAINER			5
#घोषणा BL_LOCKDOWN_INFO_CONTAINER		6
#घोषणा PERMANENT_CONFIG_CONTAINER		7
#घोषणा GUEST_CODE_CONTAINER			8
#घोषणा BL_PROTOCOL_DESCRIPTOR_CONTAINER	9
#घोषणा UI_PROTOCOL_DESCRIPTOR_CONTAINER	10
#घोषणा RMI_SELF_DISCOVERY_CONTAINER		11
#घोषणा RMI_PAGE_CONTENT_CONTAINER		12
#घोषणा GENERAL_INFORMATION_CONTAINER		13
#घोषणा DEVICE_CONFIG_CONTAINER			14
#घोषणा FLASH_CONFIG_CONTAINER			15
#घोषणा GUEST_SERIALIZATION_CONTAINER		16
#घोषणा GLOBAL_PARAMETERS_CONTAINER		17
#घोषणा CORE_CODE_CONTAINER			18
#घोषणा CORE_CONFIG_CONTAINER			19
#घोषणा DISPLAY_CONFIG_CONTAINER		20

काष्ठा f34v7_query_1_7 अणु
	u8 bl_minor_revision;			/* query 1 */
	u8 bl_major_revision;
	__le32 bl_fw_id;			/* query 2 */
	u8 minimum_ग_लिखो_size;			/* query 3 */
	__le16 block_size;
	__le16 flash_page_size;
	__le16 adjustable_partition_area_size;	/* query 4 */
	__le16 flash_config_length;		/* query 5 */
	__le16 payload_length;			/* query 6 */
	u8 partition_support[4];		/* query 7 */
पूर्ण __packed;

काष्ठा f34v7_data_1_5 अणु
	u8 partition_id;
	__le16 block_offset;
	__le16 transfer_length;
	u8 command;
	u8 payload[2];
पूर्ण __packed;

काष्ठा block_data अणु
	स्थिर व्योम *data;
	पूर्णांक size;
पूर्ण;

काष्ठा partition_table अणु
	u8 partition_id;
	u8 byte_1_reserved;
	__le16 partition_length;
	__le16 start_physical_address;
	__le16 partition_properties;
पूर्ण __packed;

काष्ठा physical_address अणु
	u16 ui_firmware;
	u16 ui_config;
	u16 dp_config;
	u16 guest_code;
पूर्ण;

काष्ठा container_descriptor अणु
	__le32 content_checksum;
	__le16 container_id;
	u8 minor_version;
	u8 major_version;
	u8 reserved_08;
	u8 reserved_09;
	u8 reserved_0a;
	u8 reserved_0b;
	u8 container_option_flags[4];
	__le32 content_options_length;
	__le32 content_options_address;
	__le32 content_length;
	__le32 content_address;
पूर्ण __packed;

काष्ठा block_count अणु
	u16 ui_firmware;
	u16 ui_config;
	u16 dp_config;
	u16 fl_config;
	u16 pm_config;
	u16 bl_config;
	u16 lockकरोwn;
	u16 guest_code;
पूर्ण;

काष्ठा image_header_10 अणु
	__le32 checksum;
	u8 reserved_04;
	u8 reserved_05;
	u8 minor_header_version;
	u8 major_header_version;
	u8 reserved_08;
	u8 reserved_09;
	u8 reserved_0a;
	u8 reserved_0b;
	__le32 top_level_container_start_addr;
पूर्ण;

काष्ठा image_metadata अणु
	bool contains_firmware_id;
	bool contains_bootloader;
	bool contains_display_cfg;
	bool contains_guest_code;
	bool contains_flash_config;
	अचिन्हित पूर्णांक firmware_id;
	अचिन्हित पूर्णांक checksum;
	अचिन्हित पूर्णांक bootloader_size;
	अचिन्हित पूर्णांक display_cfg_offset;
	अचिन्हित अक्षर bl_version;
	अचिन्हित अक्षर product_id[PRODUCT_ID_SIZE + 1];
	अचिन्हित अक्षर csपंचांगr_product_id[PRODUCT_ID_SIZE + 1];
	काष्ठा block_data bootloader;
	काष्ठा block_data ui_firmware;
	काष्ठा block_data ui_config;
	काष्ठा block_data dp_config;
	काष्ठा block_data fl_config;
	काष्ठा block_data bl_config;
	काष्ठा block_data guest_code;
	काष्ठा block_data lockकरोwn;
	काष्ठा block_count blkcount;
	काष्ठा physical_address phyaddr;
पूर्ण;

काष्ठा रेजिस्टर_offset अणु
	u8 properties;
	u8 properties_2;
	u8 block_size;
	u8 block_count;
	u8 gc_block_count;
	u8 flash_status;
	u8 partition_id;
	u8 block_number;
	u8 transfer_length;
	u8 flash_cmd;
	u8 payload;
पूर्ण;

काष्ठा rmi_f34_firmware अणु
	__le32 checksum;
	u8 pad1[3];
	u8 bootloader_version;
	__le32 image_size;
	__le32 config_size;
	u8 product_id[10];
	u8 product_info[2];
	u8 pad2[228];
	u8 data[];
पूर्ण;

काष्ठा f34v5_data अणु
	u16 block_size;
	u16 fw_blocks;
	u16 config_blocks;
	u16 ctrl_address;
	u8 status;

	काष्ठा completion cmd_करोne;
	काष्ठा mutex flash_mutex;
पूर्ण;

काष्ठा f34v7_data अणु
	bool has_display_cfg;
	bool has_guest_code;
	bool क्रमce_update;
	bool in_bl_mode;
	u8 *पढ़ो_config_buf;
	माप_प्रकार पढ़ो_config_buf_size;
	u8 command;
	u8 flash_status;
	u16 block_size;
	u16 config_block_count;
	u16 config_size;
	u16 config_area;
	u16 flash_config_length;
	u16 payload_length;
	u8 partitions;
	u16 partition_table_bytes;
	bool new_partition_table;

	काष्ठा रेजिस्टर_offset off;
	काष्ठा block_count blkcount;
	काष्ठा physical_address phyaddr;
	काष्ठा image_metadata img;

	स्थिर व्योम *config_data;
	स्थिर व्योम *image;
	काष्ठा completion cmd_करोne;
पूर्ण;

काष्ठा f34_data अणु
	काष्ठा rmi_function *fn;

	u8 bl_version;
	अचिन्हित अक्षर bootloader_id[5];
	अचिन्हित अक्षर configuration_id[CONFIG_ID_SIZE*2 + 1];

	पूर्णांक update_status;
	पूर्णांक update_progress;
	पूर्णांक update_size;

	जोड़ अणु
		काष्ठा f34v5_data v5;
		काष्ठा f34v7_data v7;
	पूर्ण;
पूर्ण;

पूर्णांक rmi_f34v7_start_reflash(काष्ठा f34_data *f34, स्थिर काष्ठा firmware *fw);
पूर्णांक rmi_f34v7_करो_reflash(काष्ठा f34_data *f34, स्थिर काष्ठा firmware *fw);
पूर्णांक rmi_f34v7_probe(काष्ठा f34_data *f34);

#पूर्ण_अगर /* _RMI_F34_H */
