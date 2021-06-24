<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL871X_EEPROM_H__
#घोषणा __RTL871X_EEPROM_H__

#समावेश "osdep_service.h"

#घोषणा	RTL8712_EEPROM_ID		0x8712
#घोषणा	EEPROM_MAX_SIZE			256
#घोषणा	CLOCK_RATE			50	/*100us*/

/*- EEPROM opcodes*/
#घोषणा EEPROM_READ_OPCODE		06
#घोषणा EEPROM_WRITE_OPCODE		05
#घोषणा EEPROM_ERASE_OPCODE		07
#घोषणा EEPROM_EWEN_OPCODE		19      /* Erase/ग_लिखो enable*/
#घोषणा EEPROM_EWDS_OPCODE		16      /* Erase/ग_लिखो disable*/

#घोषणा	EEPROM_CID_DEFAULT		0x0
#घोषणा	EEPROM_CID_ALPHA		0x1
#घोषणा	EEPROM_CID_Senao		0x3
#घोषणा	EEPROM_CID_NetCore		0x5
#घोषणा	EEPROM_CID_CAMEO		0X8
#घोषणा	EEPROM_CID_SITECOM		0x9
#घोषणा	EEPROM_CID_COREGA		0xB
#घोषणा	EEPROM_CID_EDIMAX_BELKIN	0xC
#घोषणा	EEPROM_CID_SERCOMM_BELKIN	0xE
#घोषणा	EEPROM_CID_CAMEO1		0xF
#घोषणा	EEPROM_CID_WNC_COREGA		0x12
#घोषणा	EEPROM_CID_CLEVO		0x13
#घोषणा	EEPROM_CID_WHQL			0xFE

क्रमागत RT_CUSTOMER_ID अणु
	RT_CID_DEFAULT = 0,
	RT_CID_8187_ALPHA0 = 1,
	RT_CID_8187_SERCOMM_PS = 2,
	RT_CID_8187_HW_LED = 3,
	RT_CID_8187_NETGEAR = 4,
	RT_CID_WHQL = 5,
	RT_CID_819x_CAMEO  = 6,
	RT_CID_819x_RUNTOP = 7,
	RT_CID_819x_Senao = 8,
	RT_CID_TOSHIBA = 9,
	RT_CID_819x_Netcore = 10,
	RT_CID_Nettronix = 11,
	RT_CID_DLINK = 12,
	RT_CID_PRONET = 13,
	RT_CID_COREGA = 14,
	RT_CID_819x_ALPHA = 15,
	RT_CID_819x_Sitecom = 16,
	RT_CID_CCX = 17,
	RT_CID_819x_Lenovo = 18,
	RT_CID_819x_QMI = 19,
	RT_CID_819x_Edimax_Belkin = 20,
	RT_CID_819x_Sercomm_Belkin = 21,
	RT_CID_819x_CAMEO1 = 22,
	RT_CID_819x_MSI = 23,
	RT_CID_819x_Acer = 24,
	RT_CID_819x_AzWave_ASUS = 25,
	RT_CID_819x_AzWave = 26,
	RT_CID_819x_WNC_COREGA = 27,
	RT_CID_819x_CLEVO = 28,
पूर्ण;

काष्ठा eeprom_priv अणु
	u8 bस्वतःload_fail_flag;
	u8 bempty;
	u8 sys_config;
	u8 mac_addr[6];
	u8 config0;
	u16 channel_plan;
	u8 country_string[3];
	u8 tx_घातer_b[15];
	u8 tx_घातer_g[15];
	u8 tx_घातer_a[201];
	u8 efuse_eeprom_data[EEPROM_MAX_SIZE];
	क्रमागत RT_CUSTOMER_ID CustomerID;
पूर्ण;

व्योम r8712_eeprom_ग_लिखो16(काष्ठा _adapter *padapter, u16 reg, u16 data);
u16 r8712_eeprom_पढ़ो16(काष्ठा _adapter *padapter, u16 reg);

#पूर्ण_अगर  /*__RTL871X_EEPROM_H__*/

