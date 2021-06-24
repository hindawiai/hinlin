<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित _R819XU_PHY_H
#घोषणा _R819XU_PHY_H

#घोषणा MAX_DOZE_WAITING_TIMES_9x 64

#घोषणा AGCTAB_ArrayLength			AGCTAB_ArrayLengthPciE
#घोषणा MACPHY_ArrayLength			MACPHY_ArrayLengthPciE
#घोषणा RadioA_ArrayLength			RadioA_ArrayLengthPciE
#घोषणा RadioB_ArrayLength			RadioB_ArrayLengthPciE
#घोषणा MACPHY_Array_PGLength			MACPHY_Array_PGLengthPciE
#घोषणा RadioC_ArrayLength			RadioC_ArrayLengthPciE
#घोषणा RadioD_ArrayLength			RadioD_ArrayLengthPciE
#घोषणा PHY_REGArrayLength			PHY_REGArrayLengthPciE
#घोषणा PHY_REG_1T2RArrayLength			PHY_REG_1T2RArrayLengthPciE

#घोषणा Rtl819XMACPHY_Array_PG			Rtl8192PciEMACPHY_Array_PG
#घोषणा Rtl819XMACPHY_Array			Rtl8192PciEMACPHY_Array
#घोषणा Rtl819XRadioA_Array			Rtl8192PciERadioA_Array
#घोषणा Rtl819XRadioB_Array			Rtl8192PciERadioB_Array
#घोषणा Rtl819XRadioC_Array			Rtl8192PciERadioC_Array
#घोषणा Rtl819XRadioD_Array			Rtl8192PciERadioD_Array
#घोषणा Rtl819XAGCTAB_Array			Rtl8192PciEAGCTAB_Array
#घोषणा Rtl819XPHY_REGArray			Rtl8192PciEPHY_REGArray
#घोषणा Rtl819XPHY_REG_1T2RArray		Rtl8192PciEPHY_REG_1T2RArray

बाह्य u32 rtl819XAGCTAB_Array[];

क्रमागत hw90_block अणु
	HW90_BLOCK_MAC = 0,
	HW90_BLOCK_PHY0 = 1,
	HW90_BLOCK_PHY1 = 2,
	HW90_BLOCK_RF = 3,
	HW90_BLOCK_MAXIMUM = 4,
पूर्ण;

क्रमागत rf90_radio_path अणु
	RF90_PATH_A = 0,
	RF90_PATH_B = 1,
	RF90_PATH_C = 2,
	RF90_PATH_D = 3,
	RF90_PATH_MAX
पूर्ण;

#घोषणा bMaskByte0                0xff
#घोषणा bMaskByte1                0xff00
#घोषणा bMaskByte2                0xff0000
#घोषणा bMaskByte3                0xff000000
#घोषणा bMaskHWord                0xffff0000
#घोषणा bMaskLWord                0x0000ffff
#घोषणा bMaskDWord                0xffffffff

u8 rtl92e_is_legal_rf_path(काष्ठा net_device *dev, u32 eRFPath);
व्योम rtl92e_set_bb_reg(काष्ठा net_device *dev, u32 dwRegAddr,
		       u32 dwBitMask, u32 dwData);
u32 rtl92e_get_bb_reg(काष्ठा net_device *dev, u32 dwRegAddr, u32 dwBitMask);
व्योम rtl92e_set_rf_reg(काष्ठा net_device *dev, क्रमागत rf90_radio_path eRFPath,
		       u32 RegAddr, u32 BitMask, u32 Data);
u32 rtl92e_get_rf_reg(काष्ठा net_device *dev, क्रमागत rf90_radio_path eRFPath,
		      u32 RegAddr, u32 BitMask);
व्योम rtl92e_config_mac(काष्ठा net_device *dev);
bool rtl92e_check_bb_and_rf(काष्ठा net_device *dev,
			    क्रमागत hw90_block CheckBlock,
			    क्रमागत rf90_radio_path eRFPath);
bool rtl92e_config_bb(काष्ठा net_device *dev);
व्योम rtl92e_get_tx_घातer(काष्ठा net_device *dev);
व्योम rtl92e_set_tx_घातer(काष्ठा net_device *dev, u8 channel);
bool rtl92e_config_phy(काष्ठा net_device *dev);
u8 rtl92e_config_rf_path(काष्ठा net_device *dev, क्रमागत rf90_radio_path eRFPath);

u8 rtl92e_set_channel(काष्ठा net_device *dev, u8 channel);
व्योम rtl92e_set_bw_mode(काष्ठा net_device *dev,
			क्रमागत ht_channel_width Bandwidth,
			क्रमागत ht_extchnl_offset Offset);
व्योम rtl92e_init_gain(काष्ठा net_device *dev, u8 Operation);

व्योम rtl92e_set_rf_off(काष्ठा net_device *dev);

bool rtl92e_set_rf_घातer_state(काष्ठा net_device *dev,
			       क्रमागत rt_rf_घातer_state eRFPowerState);
#घोषणा PHY_SetRFPowerState rtl92e_set_rf_घातer_state

व्योम rtl92e_scan_op_backup(काष्ठा net_device *dev, u8 Operation);

#पूर्ण_अगर
