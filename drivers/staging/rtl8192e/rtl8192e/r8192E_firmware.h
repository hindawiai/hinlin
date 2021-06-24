<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित __INC_FIRMWARE_H
#घोषणा __INC_FIRMWARE_H

#घोषणा RTL8192E_BOOT_IMG_FW	"RTL8192E/boot.img"
#घोषणा RTL8192E_MAIN_IMG_FW	"RTL8192E/main.img"
#घोषणा RTL8192E_DATA_IMG_FW	"RTL8192E/data.img"

क्रमागत firmware_init_step अणु
	FW_INIT_STEP0_BOOT = 0,
	FW_INIT_STEP1_MAIN = 1,
	FW_INIT_STEP2_DATA = 2,
पूर्ण;

क्रमागत opt_rst_type अणु
	OPT_SYSTEM_RESET = 0,
	OPT_FIRMWARE_RESET = 1,
पूर्ण;

क्रमागत desc_packet_type अणु
	DESC_PACKET_TYPE_INIT = 0,
	DESC_PACKET_TYPE_NORMAL = 1,
पूर्ण;

क्रमागत firmware_status अणु
	FW_STATUS_0_INIT = 0,
	FW_STATUS_1_MOVE_BOOT_CODE = 1,
	FW_STATUS_2_MOVE_MAIN_CODE = 2,
	FW_STATUS_3_TURNON_CPU = 3,
	FW_STATUS_4_MOVE_DATA_CODE = 4,
	FW_STATUS_5_READY = 5,
पूर्ण;

#घोषणा MAX_FW_SIZE 64000
काष्ठा rt_fw_blob अणु
	u16 size;
	u8 data[MAX_FW_SIZE];
पूर्ण;

#घोषणा FW_BLOBS 3
काष्ठा rt_firmware अणु
	क्रमागत firmware_status status;
	काष्ठा rt_fw_blob blobs[FW_BLOBS];
पूर्ण;

bool rtl92e_init_fw(काष्ठा net_device *dev);
#पूर्ण_अगर
