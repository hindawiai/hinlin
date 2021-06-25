<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_MAC_H__
#घोषणा __RTW_MAC_H__

#घोषणा RTW_HW_PORT_NUM		5
#घोषणा cut_version_to_mask(cut) (0x1 << ((cut) + 1))
#घोषणा SDIO_LOCAL_OFFSET	0x10250000
#घोषणा DDMA_POLLING_COUNT	1000
#घोषणा C2H_PKT_BUF		256
#घोषणा REPORT_BUF		128
#घोषणा PHY_STATUS_SIZE		4
#घोषणा ILLEGAL_KEY_GROUP	0xFAAAAA00

/* HW memory address */
#घोषणा OCPBASE_RXBUF_FW_88XX		0x18680000
#घोषणा OCPBASE_TXBUF_88XX		0x18780000
#घोषणा OCPBASE_ROM_88XX		0x00000000
#घोषणा OCPBASE_IMEM_88XX		0x00030000
#घोषणा OCPBASE_DMEM_88XX		0x00200000
#घोषणा OCPBASE_EMEM_88XX		0x00100000

#घोषणा RSVD_PG_DRV_NUM			16
#घोषणा RSVD_PG_H2C_EXTRAINFO_NUM	24
#घोषणा RSVD_PG_H2C_STATICINFO_NUM	8
#घोषणा RSVD_PG_H2CQ_NUM		8
#घोषणा RSVD_PG_CPU_INSTRUCTION_NUM	0
#घोषणा RSVD_PG_FW_TXBUF_NUM		4

व्योम rtw_set_channel_mac(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
			 u8 primary_ch_idx);
पूर्णांक rtw_mac_घातer_on(काष्ठा rtw_dev *rtwdev);
व्योम rtw_mac_घातer_off(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_करोwnload_firmware(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_fw_state *fw);
पूर्णांक rtw_mac_init(काष्ठा rtw_dev *rtwdev);
व्योम rtw_mac_flush_queues(काष्ठा rtw_dev *rtwdev, u32 queues, bool drop);
पूर्णांक rtw_ddma_to_fw_fअगरo(काष्ठा rtw_dev *rtwdev, u32 ocp_src, u32 size);

अटल अंतरभूत व्योम rtw_mac_flush_all_queues(काष्ठा rtw_dev *rtwdev, bool drop)
अणु
	rtw_mac_flush_queues(rtwdev, BIT(rtwdev->hw->queues) - 1, drop);
पूर्ण

#पूर्ण_अगर
