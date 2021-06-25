<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_EFUSE_H__
#घोषणा __RTW_EFUSE_H__


#घोषणा	EFUSE_ERROE_HANDLE		1

#घोषणा	PG_STATE_HEADER			0x01
#घोषणा	PG_STATE_WORD_0		0x02
#घोषणा	PG_STATE_WORD_1		0x04
#घोषणा	PG_STATE_WORD_2		0x08
#घोषणा	PG_STATE_WORD_3		0x10
#घोषणा	PG_STATE_DATA			0x20

#घोषणा	PG_SWBYTE_H			0x01
#घोषणा	PG_SWBYTE_L			0x02

#घोषणा	PGPKT_DATA_SIZE		8

#घोषणा	EFUSE_WIFI				0
#घोषणा	EFUSE_BT				1

क्रमागत अणु
	TYPE_EFUSE_MAX_SECTION				= 0,
	TYPE_EFUSE_REAL_CONTENT_LEN			= 1,
	TYPE_AVAILABLE_EFUSE_BYTES_BANK		= 2,
	TYPE_AVAILABLE_EFUSE_BYTES_TOTAL	= 3,
	TYPE_EFUSE_MAP_LEN					= 4,
	TYPE_EFUSE_PROTECT_BYTES_BANK		= 5,
	TYPE_EFUSE_CONTENT_LEN_BANK			= 6,
पूर्ण;

#घोषणा		EFUSE_MAX_MAP_LEN		512

#घोषणा		EFUSE_MAX_HW_SIZE		512
#घोषणा		EFUSE_MAX_SECTION_BASE	16

#घोषणा EXT_HEADER(header) ((header & 0x1F) == 0x0F)
#घोषणा ALL_WORDS_DISABLED(wde)	((wde & 0x0F) == 0x0F)
#घोषणा GET_HDR_OFFSET_2_0(header) ((header & 0xE0) >> 5)

#घोषणा		EFUSE_REPEAT_THRESHOLD_			3

/*  */
/* 	The following is क्रम BT Efuse definition */
/*  */
#घोषणा		EFUSE_BT_MAX_MAP_LEN		1024
#घोषणा		EFUSE_MAX_BANK			4
#घोषणा		EFUSE_MAX_BT_BANK		(EFUSE_MAX_BANK-1)
/*  */
/*--------------------------Define Parameters-------------------------------*/
#घोषणा		EFUSE_MAX_WORD_UNIT			4

/*------------------------------Define काष्ठाure----------------------------*/
काष्ठा pgpkt_काष्ठा अणु
	u8 offset;
	u8 word_en;
	u8 data[8];
	u8 word_cnts;
पूर्ण;

/*------------------------------Define काष्ठाure----------------------------*/
काष्ठा efuse_hal अणु
	u8 fakeEfuseBank;
	u32 fakeEfuseUsedBytes;
	u8 fakeEfuseContent[EFUSE_MAX_HW_SIZE];
	u8 fakeEfuseInitMap[EFUSE_MAX_MAP_LEN];
	u8 fakeEfuseModअगरiedMap[EFUSE_MAX_MAP_LEN];

	u16 BTEfuseUsedBytes;
	u8 BTEfuseUsedPercentage;
	u8 BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	u8 BTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN];
	u8 BTEfuseModअगरiedMap[EFUSE_BT_MAX_MAP_LEN];

	u16 fakeBTEfuseUsedBytes;
	u8 fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
	u8 fakeBTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN];
	u8 fakeBTEfuseModअगरiedMap[EFUSE_BT_MAX_MAP_LEN];
पूर्ण;


/*------------------------Export global variable----------------------------*/
बाह्य u8 fakeEfuseBank;
बाह्य u32 fakeEfuseUsedBytes;
बाह्य u8 fakeEfuseContent[];
बाह्य u8 fakeEfuseInitMap[];
बाह्य u8 fakeEfuseModअगरiedMap[];

बाह्य u32 BTEfuseUsedBytes;
बाह्य u8 BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
बाह्य u8 BTEfuseInitMap[];
बाह्य u8 BTEfuseModअगरiedMap[];

बाह्य u32 fakeBTEfuseUsedBytes;
बाह्य u8 fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
बाह्य u8 fakeBTEfuseInitMap[];
बाह्य u8 fakeBTEfuseModअगरiedMap[];
/*------------------------Export global variable----------------------------*/

u16 Efuse_GetCurrentSize(काष्ठा adapter *padapter, u8 efuseType, bool bPseuकरोTest);
u8 Efuse_CalculateWordCnts(u8 word_en);
व्योम EFUSE_GetEfuseDefinition(काष्ठा adapter *padapter, u8 efuseType, u8 type, व्योम *pOut, bool bPseuकरोTest);
u8 efuse_OneByteRead(काष्ठा adapter *padapter, u16 addr, u8 *data, bool	 bPseuकरोTest);
u8 efuse_OneByteWrite(काष्ठा adapter *padapter, u16 addr, u8 data, bool	 bPseuकरोTest);

व्योम Efuse_PowerSwitch(काष्ठा adapter *padapter, u8 bWrite, u8  PwrState);
पूर्णांक	Efuse_PgPacketRead(काष्ठा adapter *padapter, u8 offset, u8 *data, bool bPseuकरोTest);
पूर्णांक	Efuse_PgPacketWrite(काष्ठा adapter *padapter, u8 offset, u8 word_en, u8 *data, bool bPseuकरोTest);
व्योम efuse_WordEnableDataRead(u8 word_en, u8 *sourdata, u8 *targetdata);
u8 Efuse_WordEnableDataWrite(काष्ठा adapter *padapter, u16 efuse_addr, u8 word_en, u8 *data, bool bPseuकरोTest);

u8 EFUSE_Read1Byte(काष्ठा adapter *padapter, u16 Address);
व्योम EFUSE_ShaकरोwMapUpdate(काष्ठा adapter *padapter, u8 efuseType, bool bPseuकरोTest);
व्योम EFUSE_ShaकरोwRead(काष्ठा adapter *padapter, u8 Type, u16 Offset, u32 *Value);
व्योम Rtw_Hal_ReadMACAddrFromFile(काष्ठा adapter *padapter);
u32 Rtw_Hal_पढ़ोPGDataFromConfigFile(काष्ठा adapter *padapter);

#पूर्ण_अगर
