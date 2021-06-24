<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_SEC_H_
#घोषणा __RTW_SEC_H_

#घोषणा RTW_SEC_CMD_REG			0x670
#घोषणा RTW_SEC_WRITE_REG		0x674
#घोषणा RTW_SEC_READ_REG		0x678
#घोषणा RTW_SEC_CONFIG			0x680

#घोषणा RTW_SEC_CAM_ENTRY_SHIFT		3
#घोषणा RTW_SEC_DEFAULT_KEY_NUM		4
#घोषणा RTW_SEC_CMD_WRITE_ENABLE	BIT(16)
#घोषणा RTW_SEC_CMD_CLEAR		BIT(30)
#घोषणा RTW_SEC_CMD_POLLING		BIT(31)

#घोषणा RTW_SEC_TX_UNI_USE_DK		BIT(0)
#घोषणा RTW_SEC_RX_UNI_USE_DK		BIT(1)
#घोषणा RTW_SEC_TX_DEC_EN		BIT(2)
#घोषणा RTW_SEC_RX_DEC_EN		BIT(3)
#घोषणा RTW_SEC_TX_BC_USE_DK		BIT(6)
#घोषणा RTW_SEC_RX_BC_USE_DK		BIT(7)

#घोषणा RTW_SEC_ENGINE_EN		BIT(9)

पूर्णांक rtw_sec_get_मुक्त_cam(काष्ठा rtw_sec_desc *sec);
व्योम rtw_sec_ग_लिखो_cam(काष्ठा rtw_dev *rtwdev,
		       काष्ठा rtw_sec_desc *sec,
		       काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key,
		       u8 hw_key_type, u8 hw_key_idx);
व्योम rtw_sec_clear_cam(काष्ठा rtw_dev *rtwdev,
		       काष्ठा rtw_sec_desc *sec,
		       u8 hw_key_idx);
u8 rtw_sec_cam_pg_backup(काष्ठा rtw_dev *rtwdev, u8 *used_cam);
व्योम rtw_sec_enable_sec_engine(काष्ठा rtw_dev *rtwdev);

#पूर्ण_अगर
