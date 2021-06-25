<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#अगर_अघोषित _HCI_H_
#घोषणा _HCI_H_

#घोषणा LTE_GET_INFORMATION		0x3002
#घोषणा LTE_GET_INFORMATION_RESULT	0xB003
	#घोषणा MAC_ADDRESS		0xA2

#घोषणा LTE_LINK_ON_OFF_INDICATION	0xB133
#घोषणा LTE_PDN_TABLE_IND		0xB143

#घोषणा LTE_TX_SDU			0x3200
#घोषणा LTE_RX_SDU			0xB201
#घोषणा LTE_TX_MULTI_SDU		0x3202
#घोषणा LTE_RX_MULTI_SDU		0xB203

#घोषणा LTE_DL_SDU_FLOW_CONTROL		0x3305
#घोषणा LTE_UL_SDU_FLOW_CONTROL		0xB306

#घोषणा LTE_AT_CMD_TO_DEVICE		0x3307
#घोषणा LTE_AT_CMD_FROM_DEVICE		0xB308

#घोषणा LTE_SDIO_DM_SEND_PKT		0x3312
#घोषणा LTE_SDIO_DM_RECV_PKT		0xB313

#घोषणा LTE_NV_RESTORE_REQUEST		0xB30C
#घोषणा LTE_NV_RESTORE_RESPONSE		0x330D
#घोषणा LTE_NV_SAVE_REQUEST		0xB30E
	#घोषणा NV_TYPE_LTE_INFO	0x00
	#घोषणा NV_TYPE_BOARD_CONFIG	0x01
	#घोषणा NV_TYPE_RF_CAL		0x02
	#घोषणा NV_TYPE_TEMP		0x03
	#घोषणा NV_TYPE_NET_INFO	0x04
	#घोषणा NV_TYPE_SAFETY_INFO	0x05
	#घोषणा NV_TYPE_CDMA_CAL	0x06
	#घोषणा NV_TYPE_VENDOR		0x07
	#घोषणा NV_TYPE_ALL		0xff
#घोषणा LTE_NV_SAVE_RESPONSE		0x330F

#घोषणा LTE_AT_CMD_TO_DEVICE_EXT	0x3323
#घोषणा LTE_AT_CMD_FROM_DEVICE_EXT	0xB324

#पूर्ण_अगर /* _HCI_H_ */
