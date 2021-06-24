<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित __HINIC_DEVLINK_H__
#घोषणा __HINIC_DEVLINK_H__

#समावेश <net/devlink.h>
#समावेश "hinic_dev.h"

#घोषणा MAX_FW_TYPE_NUM 30
#घोषणा HINIC_MAGIC_NUM 0x18221100
#घोषणा UPDATEFW_IMAGE_HEAD_SIZE 1024
#घोषणा FW_UPDATE_COLD 0
#घोषणा FW_UPDATE_HOT  1

#घोषणा UP_TYPE_A 0x0
#घोषणा UP_TYPE_B 0x1

#घोषणा MAX_FW_FRAGMENT_LEN 1536
#घोषणा HINIC_FW_DISMATCH_ERROR 10

क्रमागत hinic_fw_type अणु
	UP_FW_UPDATE_UP_TEXT_A = 0x0,
	UP_FW_UPDATE_UP_DATA_A,
	UP_FW_UPDATE_UP_TEXT_B,
	UP_FW_UPDATE_UP_DATA_B,
	UP_FW_UPDATE_UP_DICT,

	UP_FW_UPDATE_HLINK_ONE = 0x5,
	UP_FW_UPDATE_HLINK_TWO,
	UP_FW_UPDATE_HLINK_THR,
	UP_FW_UPDATE_PHY,
	UP_FW_UPDATE_TILE_TEXT,

	UP_FW_UPDATE_TILE_DATA = 0xa,
	UP_FW_UPDATE_TILE_DICT,
	UP_FW_UPDATE_PPE_STATE,
	UP_FW_UPDATE_PPE_BRANCH,
	UP_FW_UPDATE_PPE_EXTACT,

	UP_FW_UPDATE_CLP_LEGACY = 0xf,
	UP_FW_UPDATE_PXE_LEGACY,
	UP_FW_UPDATE_ISCSI_LEGACY,
	UP_FW_UPDATE_CLP_EFI,
	UP_FW_UPDATE_PXE_EFI,

	UP_FW_UPDATE_ISCSI_EFI = 0x14,
	UP_FW_UPDATE_CFG,
	UP_FW_UPDATE_BOOT,
	UP_FW_UPDATE_VPD,
	खाता_TYPE_TOTAL_NUM
पूर्ण;

#घोषणा _IMAGE_UP_ALL_IN ((1 << UP_FW_UPDATE_UP_TEXT_A) | \
			  (1 << UP_FW_UPDATE_UP_DATA_A) | \
			  (1 << UP_FW_UPDATE_UP_TEXT_B) | \
			  (1 << UP_FW_UPDATE_UP_DATA_B) | \
			  (1 << UP_FW_UPDATE_UP_DICT) | \
			  (1 << UP_FW_UPDATE_BOOT) | \
			  (1 << UP_FW_UPDATE_HLINK_ONE) | \
			  (1 << UP_FW_UPDATE_HLINK_TWO) | \
			  (1 << UP_FW_UPDATE_HLINK_THR))

#घोषणा _IMAGE_UCODE_ALL_IN ((1 << UP_FW_UPDATE_TILE_TEXT) | \
			     (1 << UP_FW_UPDATE_TILE_DICT) | \
			     (1 << UP_FW_UPDATE_PPE_STATE) | \
			     (1 << UP_FW_UPDATE_PPE_BRANCH) | \
			     (1 << UP_FW_UPDATE_PPE_EXTACT))

#घोषणा _IMAGE_COLD_SUB_MODULES_MUST_IN (_IMAGE_UP_ALL_IN | _IMAGE_UCODE_ALL_IN)
#घोषणा _IMAGE_HOT_SUB_MODULES_MUST_IN (_IMAGE_UP_ALL_IN | _IMAGE_UCODE_ALL_IN)
#घोषणा _IMAGE_CFG_SUB_MODULES_MUST_IN BIT(UP_FW_UPDATE_CFG)
#घोषणा UP_FW_UPDATE_UP_TEXT  0x0
#घोषणा UP_FW_UPDATE_UP_DATA  0x1
#घोषणा UP_FW_UPDATE_VPD_B    0x15

काष्ठा fw_section_info_st अणु
	u32 fw_section_len;
	u32 fw_section_offset;
	u32 fw_section_version;
	u32 fw_section_type;
	u32 fw_section_crc;
पूर्ण;

काष्ठा fw_image_st अणु
	u32 fw_version;
	u32 fw_len;
	u32 fw_magic;
	काष्ठा अणु
		u32 fw_section_cnt:16;
		u32 resd:16;
	पूर्ण fw_info;
	काष्ठा fw_section_info_st fw_section_info[MAX_FW_TYPE_NUM];
	u32 device_id;
	u32 res[101];
	व्योम *bin_data;
पूर्ण;

काष्ठा host_image_st अणु
	काष्ठा fw_section_info_st image_section_info[MAX_FW_TYPE_NUM];
	काष्ठा अणु
		u32 up_total_len;
		u32 fw_version;
	पूर्ण image_info;
	u32 section_type_num;
	u32 device_id;
पूर्ण;

काष्ठा devlink *hinic_devlink_alloc(व्योम);
व्योम hinic_devlink_मुक्त(काष्ठा devlink *devlink);
पूर्णांक hinic_devlink_रेजिस्टर(काष्ठा hinic_devlink_priv *priv, काष्ठा device *dev);
व्योम hinic_devlink_unरेजिस्टर(काष्ठा hinic_devlink_priv *priv);

पूर्णांक hinic_health_reporters_create(काष्ठा hinic_devlink_priv *priv);
व्योम hinic_health_reporters_destroy(काष्ठा hinic_devlink_priv *priv);

#पूर्ण_अगर /* __HINIC_DEVLINK_H__ */
