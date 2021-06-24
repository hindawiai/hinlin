<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __HAL_PHY_H__
#घोषणा __HAL_PHY_H__


#अगर DISABLE_BB_RF
#घोषणा	HAL_FW_ENABLE				0
#घोषणा	HAL_MAC_ENABLE			0
#घोषणा	HAL_BB_ENABLE				0
#घोषणा	HAL_RF_ENABLE				0
#अन्यथा /*  FPGA_PHY and ASIC */
#घोषणा		HAL_FW_ENABLE				1
#घोषणा	HAL_MAC_ENABLE			1
#घोषणा	HAL_BB_ENABLE				1
#घोषणा	HAL_RF_ENABLE				1
#पूर्ण_अगर

/*  */
/*  Antenna detection method, i.e., using single tone detection or RSSI reported from each antenna detected. */
/*  Added by Roger, 2013.05.22. */
/*  */
#घोषणा ANT_DETECT_BY_SINGLE_TONE	BIT0
#घोषणा ANT_DETECT_BY_RSSI				BIT1
#घोषणा IS_ANT_DETECT_SUPPORT_SINGLE_TONE(__Adapter)		((GET_HAL_DATA(__Adapter)->AntDetection) & ANT_DETECT_BY_SINGLE_TONE)
#घोषणा IS_ANT_DETECT_SUPPORT_RSSI(__Adapter)		((GET_HAL_DATA(__Adapter)->AntDetection) & ANT_DETECT_BY_RSSI)


/*--------------------------Define Parameters-------------------------------*/
क्रमागत band_type अणु
	BAND_ON_2_4G = 0,
	BAND_ON_5G,
	BAND_ON_BOTH,
	BANDMAX
पूर्ण;

क्रमागत अणु
	RF_TYPE_MIN = 0,	/*  0 */
	RF_8225 = 1,		/*  1 11b/g RF क्रम verअगरication only */
	RF_8256 = 2,		/*  2 11b/g/n */
	RF_8258 = 3,		/*  3 11a/b/g/n RF */
	RF_6052 = 4,		/*  4 11b/g/n RF */
	RF_PSEUDO_11N = 5,	/*  5, It is a temporality RF. */
	RF_TYPE_MAX
पूर्ण;

क्रमागत rf_path अणु
	RF_PATH_A = 0,
	RF_PATH_B,
	RF_PATH_C,
	RF_PATH_D
पूर्ण;

#घोषणा	TX_1S			0
#घोषणा	TX_2S			1
#घोषणा	TX_3S			2
#घोषणा	TX_4S			3

#घोषणा	RF_PATH_MAX_92C_88E		2
#घोषणा	RF_PATH_MAX_90_8812		4	/* Max RF number 90 support */

क्रमागत wireless_mode अणु
	WIRELESS_MODE_UNKNOWN = 0x00,
	WIRELESS_MODE_A = 0x01,
	WIRELESS_MODE_B = 0x02,
	WIRELESS_MODE_G = 0x04,
	WIRELESS_MODE_AUTO = 0x08,
	WIRELESS_MODE_N_24G = 0x10,
	WIRELESS_MODE_N_5G = 0x20,
	WIRELESS_MODE_AC_5G = 0x40,
	WIRELESS_MODE_AC_24G  = 0x80,
	WIRELESS_MODE_AC_ONLY  = 0x100,
पूर्ण;

क्रमागत SwChnlCmdID अणु
	CmdID_End,
	CmdID_SetTxPowerLevel,
	CmdID_BBRegWrite10,
	CmdID_WritePortUदीर्घ,
	CmdID_WritePortUलघु,
	CmdID_WritePortUअक्षर,
	CmdID_RF_WriteReg,
पूर्ण;

काष्ठा SwChnlCmd अणु
	क्रमागत SwChnlCmdID	CmdID;
	u32 			Para1;
	u32 			Para2;
	u32 			msDelay;
पूर्ण;

/*--------------------------Exported Function prototype---------------------*/

#पूर्ण_अगर /* __HAL_COMMON_H__ */
