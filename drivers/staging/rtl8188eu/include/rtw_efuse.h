<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_EFUSE_H__
#घोषणा __RTW_EFUSE_H__

#समावेश <osdep_service.h>

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

/* E-Fuse */
#घोषणा EFUSE_MAP_SIZE      512
#घोषणा EFUSE_MAX_SIZE      256
/* end of E-Fuse */

#घोषणा		EFUSE_MAX_MAP_LEN		512
#घोषणा		EFUSE_MAX_HW_SIZE		512
#घोषणा		EFUSE_MAX_SECTION_BASE	16

#घोषणा EXT_HEADER(header) ((header & 0x1F) == 0x0F)
#घोषणा ALL_WORDS_DISABLED(wde)	((wde & 0x0F) == 0x0F)
#घोषणा GET_HDR_OFFSET_2_0(header) ((header & 0xE0) >> 5)

#घोषणा		EFUSE_REPEAT_THRESHOLD_			3

/*	The following is क्रम BT Efuse definition */
#घोषणा		EFUSE_BT_MAX_MAP_LEN		1024
#घोषणा		EFUSE_MAX_BANK			4
#घोषणा		EFUSE_MAX_BT_BANK		(EFUSE_MAX_BANK - 1)
/*--------------------------Define Parameters-------------------------------*/
#घोषणा		EFUSE_MAX_WORD_UNIT			4

/*------------------------------Define काष्ठाure----------------------------*/
काष्ठा pgpkt अणु
	u8 offset;
	u8 word_en;
	u8 data[8];
	u8 word_cnts;
पूर्ण;

u8 Efuse_CalculateWordCnts(u8 word_en);
u8 efuse_OneByteRead(काष्ठा adapter *adapter, u16 addr, u8 *data);
u8 efuse_OneByteWrite(काष्ठा adapter *adapter, u16 addr, u8 data);

व्योम efuse_ReadEFuse(काष्ठा adapter *Adapter, u8 efuseType, u16 _offset,
		u16 _size_byte, u8 *pbuf);
पूर्णांक Efuse_PgPacketRead(काष्ठा adapter *adapt, u8 offset, u8 *data);
bool Efuse_PgPacketWrite(काष्ठा adapter *adapter, u8 offset, u8 word, u8 *data);
व्योम efuse_WordEnableDataRead(u8 word_en, u8 *sourdata, u8 *targetdata);
u8 Efuse_WordEnableDataWrite(काष्ठा adapter *adapter, u16 efuse_addr,
			     u8 word_en, u8 *data);

व्योम EFUSE_ShaकरोwMapUpdate(काष्ठा adapter *adapter, u8 efusetype);
#पूर्ण_अगर
