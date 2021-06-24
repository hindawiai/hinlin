<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर_अघोषित __MT76x02_MCU_H
#घोषणा __MT76x02_MCU_H

#समावेश "mt76x02.h"

#घोषणा MT_MCU_RESET_CTL		0x070C
#घोषणा MT_MCU_INT_LEVEL		0x0718
#घोषणा MT_MCU_COM_REG0			0x0730
#घोषणा MT_MCU_COM_REG1			0x0734
#घोषणा MT_MCU_COM_REG2			0x0738
#घोषणा MT_MCU_COM_REG3			0x073C

#घोषणा MT_INBAND_PACKET_MAX_LEN	192
#घोषणा MT_MCU_MEMMAP_WLAN		0x410000

#घोषणा MT_MCU_PCIE_REMAP_BASE4		0x074C

#घोषणा MT_MCU_SEMAPHORE_00		0x07B0
#घोषणा MT_MCU_SEMAPHORE_01		0x07B4
#घोषणा MT_MCU_SEMAPHORE_02		0x07B8
#घोषणा MT_MCU_SEMAPHORE_03		0x07BC

#घोषणा MT_MCU_ILM_ADDR			0x80000

क्रमागत mcu_cmd अणु
	CMD_FUN_SET_OP = 1,
	CMD_LOAD_CR = 2,
	CMD_INIT_GAIN_OP = 3,
	CMD_DYNC_VGA_OP = 6,
	CMD_TDLS_CH_SW = 7,
	CMD_BURST_WRITE = 8,
	CMD_READ_MODIFY_WRITE = 9,
	CMD_RANDOM_READ = 10,
	CMD_BURST_READ = 11,
	CMD_RANDOM_WRITE = 12,
	CMD_LED_MODE_OP = 16,
	CMD_POWER_SAVING_OP = 20,
	CMD_WOW_CONFIG = 21,
	CMD_WOW_QUERY = 22,
	CMD_WOW_FEATURE = 24,
	CMD_CARRIER_DETECT_OP = 28,
	CMD_RADOR_DETECT_OP = 29,
	CMD_SWITCH_CHANNEL_OP = 30,
	CMD_CALIBRATION_OP = 31,
	CMD_BEACON_OP = 32,
	CMD_ANTENNA_OP = 33,
पूर्ण;

क्रमागत mcu_घातer_mode अणु
	RADIO_OFF = 0x30,
	RADIO_ON = 0x31,
	RADIO_OFF_AUTO_WAKEUP = 0x32,
	RADIO_OFF_ADVANCE = 0x33,
	RADIO_ON_ADVANCE = 0x34,
पूर्ण;

क्रमागत mcu_function अणु
	Q_SELECT = 1,
	BW_SETTING = 2,
	USB2_SW_DISCONNECT = 2,
	USB3_SW_DISCONNECT = 3,
	LOG_FW_DEBUG_MSG = 4,
	GET_FW_VERSION = 5,
पूर्ण;

काष्ठा mt76x02_fw_header अणु
	__le32 ilm_len;
	__le32 dlm_len;
	__le16 build_ver;
	__le16 fw_ver;
	u8 pad[4];
	अक्षर build_समय[16];
पूर्ण;

काष्ठा mt76x02_patch_header अणु
	अक्षर build_समय[16];
	अक्षर platक्रमm[4];
	अक्षर hw_version[4];
	अक्षर patch_version[4];
	u8 pad[2];
पूर्ण;

पूर्णांक mt76x02_mcu_cleanup(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x02_mcu_calibrate(काष्ठा mt76x02_dev *dev, पूर्णांक type, u32 param);
पूर्णांक mt76x02_mcu_msg_send(काष्ठा mt76_dev *mdev, पूर्णांक cmd, स्थिर व्योम *data,
			 पूर्णांक len, bool रुको_resp);
पूर्णांक mt76x02_mcu_parse_response(काष्ठा mt76_dev *mdev, पूर्णांक cmd,
			       काष्ठा sk_buff *skb, पूर्णांक seq);
पूर्णांक mt76x02_mcu_function_select(काष्ठा mt76x02_dev *dev, क्रमागत mcu_function func,
				u32 val);
पूर्णांक mt76x02_mcu_set_radio_state(काष्ठा mt76x02_dev *dev, bool on);
व्योम mt76x02_set_ethtool_fwver(काष्ठा mt76x02_dev *dev,
			       स्थिर काष्ठा mt76x02_fw_header *h);

#पूर्ण_अगर /* __MT76x02_MCU_H */
