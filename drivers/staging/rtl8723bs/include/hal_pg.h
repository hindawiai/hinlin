<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित __HAL_PG_H__
#घोषणा __HAL_PG_H__

#घोषणा	MAX_RF_PATH				4
/* MAX_TX_COUNT must always be set to 4, otherwise the पढ़ो efuse table
 * sequence will be wrong.
 */
#घोषणा MAX_TX_COUNT				4

/*  For VHT series TX घातer by rate table. */
/*  VHT TX घातer by rate off setArray = */
/*  Band:-2G&5G = 0 / 1 */
/*  RF: at most 4*4 = ABCD = 0/1/2/3 */
/*  CCK = 0 OFDM = 1/2 HT-MCS 0-15 =3/4/56 VHT =7/8/9/10/11 */
#घोषणा TX_PWR_BY_RATE_NUM_BAND			2
#घोषणा TX_PWR_BY_RATE_NUM_RF			4
#घोषणा TX_PWR_BY_RATE_NUM_RATE			84
#घोषणा MAX_RF_PATH_NUM				2
#घोषणा	MAX_CHNL_GROUP_24G			6
#घोषणा EEPROM_DEFAULT_BOARD_OPTION		0x00

/* EEPROM/Efuse PG Offset क्रम 8723BE/8723BU/8723BS */
/*  0x10 ~ 0x63 = TX घातer area. */
#घोषणा	EEPROM_TX_PWR_INX_8723B			0x10
/* New EFUSE शेष value */
#घोषणा EEPROM_DEFAULT_24G_INDEX		0x2D
#घोषणा EEPROM_DEFAULT_24G_HT20_DIFF		0X02
#घोषणा EEPROM_DEFAULT_24G_OFDM_DIFF		0X04
#घोषणा	EEPROM_Default_ThermalMeter_8723B	0x18
#घोषणा EEPROM_Default_CrystalCap_8723B		0x20

#घोषणा	EEPROM_ChannelPlan_8723B		0xB8
#घोषणा	EEPROM_XTAL_8723B			0xB9
#घोषणा	EEPROM_THERMAL_METER_8723B		0xBA

#घोषणा	EEPROM_RF_BOARD_OPTION_8723B		0xC1
#घोषणा	EEPROM_RF_BT_SETTING_8723B		0xC3
#घोषणा	EEPROM_VERSION_8723B			0xC4
#घोषणा	EEPROM_CustomID_8723B			0xC5
#घोषणा EEPROM_DEFAULT_DIFF			0XFE

/* RTL8723BS */
#घोषणा	EEPROM_MAC_ADDR_8723BS			0x11A
#घोषणा EEPROM_Voltage_ADDR_8723B		0x8
#घोषणा RTL_EEPROM_ID				0x8129

काष्ठा TxPowerInfo24G अणु
	u8 IndexCCK_Base[MAX_RF_PATH][MAX_CHNL_GROUP_24G];
	u8 IndexBW40_Base[MAX_RF_PATH][MAX_CHNL_GROUP_24G];
	/* If only one tx, only BW20 and OFDM are used. */
	s8 CCK_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 OFDM_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 BW20_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
	s8 BW40_Dअगरf[MAX_RF_PATH][MAX_TX_COUNT];
पूर्ण;

क्रमागत अणु
	Ant_x2	= 0,
	Ant_x1	= 1
पूर्ण;

क्रमागत अणु
	BT_RTL8723B = 8,
पूर्ण;

#पूर्ण_अगर
