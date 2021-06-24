<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_EFUSE_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_data.h>
#समावेश <linux/jअगरfies.h>


/* Define global variables */
u8 fakeEfuseBank;
u32 fakeEfuseUsedBytes;
u8 fakeEfuseContent[EFUSE_MAX_HW_SIZE] = अणु0पूर्ण;
u8 fakeEfuseInitMap[EFUSE_MAX_MAP_LEN] = अणु0पूर्ण;
u8 fakeEfuseModअगरiedMap[EFUSE_MAX_MAP_LEN] = अणु0पूर्ण;

u32 BTEfuseUsedBytes;
u8 BTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
u8 BTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN] = अणु0पूर्ण;
u8 BTEfuseModअगरiedMap[EFUSE_BT_MAX_MAP_LEN] = अणु0पूर्ण;

u32 fakeBTEfuseUsedBytes;
u8 fakeBTEfuseContent[EFUSE_MAX_BT_BANK][EFUSE_MAX_HW_SIZE];
u8 fakeBTEfuseInitMap[EFUSE_BT_MAX_MAP_LEN] = अणु0पूर्ण;
u8 fakeBTEfuseModअगरiedMap[EFUSE_BT_MAX_MAP_LEN] = अणु0पूर्ण;

#घोषणा REG_EFUSE_CTRL		0x0030
#घोषणा EFUSE_CTRL			REG_EFUSE_CTRL		/*  E-Fuse Control. */

अटल bool
Efuse_Read1ByteFromFakeContent(
	काष्ठा adapter *padapter,
	u16 	Offset,
	u8 *Value)
अणु
	अगर (Offset >= EFUSE_MAX_HW_SIZE)
		वापस false;
	/* DbgPrपूर्णांक("Read fake content, offset = %d\n", Offset); */
	अगर (fakeEfuseBank == 0)
		*Value = fakeEfuseContent[Offset];
	अन्यथा
		*Value = fakeBTEfuseContent[fakeEfuseBank-1][Offset];
	वापस true;
पूर्ण

अटल bool
Efuse_Write1ByteToFakeContent(
	काष्ठा adapter *padapter,
	u16 	Offset,
	u8 Value)
अणु
	अगर (Offset >= EFUSE_MAX_HW_SIZE)
		वापस false;
	अगर (fakeEfuseBank == 0)
		fakeEfuseContent[Offset] = Value;
	अन्यथा
		fakeBTEfuseContent[fakeEfuseBank-1][Offset] = Value;
	वापस true;
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	Efuse_PowerSwitch
 *
 * Overview:	When we want to enable ग_लिखो operation, we should change to
 *			pwr on state. When we stop ग_लिखो, we should चयन to 500k mode
 *			and disable LDO 2.5V.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 11/17/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------*/
व्योम
Efuse_PowerSwitch(
काष्ठा adapter *padapter,
u8 bWrite,
u8 PwrState)
अणु
	padapter->HalFunc.EfusePowerSwitch(padapter, bWrite, PwrState);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	Efuse_GetCurrentSize
 *
 * Overview:	Get current efuse size!!!
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 11/16/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------*/
u16
Efuse_GetCurrentSize(
	काष्ठा adapter *padapter,
	u8 	efuseType,
	bool		bPseuकरोTest)
अणु
	वापस padapter->HalFunc.EfuseGetCurrentSize(padapter, efuseType,
						     bPseuकरोTest);
पूर्ण

/*  11/16/2008 MH Add description. Get current efuse area enabled word!!. */
u8
Efuse_CalculateWordCnts(u8 word_en)
अणु
	u8 word_cnts = 0;
	अगर (!(word_en & BIT(0)))
		word_cnts++; /*  0 : ग_लिखो enable */
	अगर (!(word_en & BIT(1)))
		word_cnts++;
	अगर (!(word_en & BIT(2)))
		word_cnts++;
	अगर (!(word_en & BIT(3)))
		word_cnts++;
	वापस word_cnts;
पूर्ण

/*  */
/* 	Description: */
/* 		1. Execute E-Fuse पढ़ो byte operation according as map offset and */
/* 		    save to E-Fuse table. */
/* 		2. Referred from SD1 Riअक्षरd. */
/*  */
/* 	Assumption: */
/* 		1. Boot from E-Fuse and successfully स्वतः-load. */
/* 		2. PASSIVE_LEVEL (USB पूर्णांकerface) */
/*  */
/* 	Created by Roger, 2008.10.21. */
/*  */
/* 	2008/12/12 MH	1. Reorganize code flow and reserve bytes. and add description. */
/* 					2. Add efuse utilization collect. */
/* 	2008/12/22 MH	Read Efuse must check अगर we ग_लिखो section 1 data again!!! Sec1 */
/* 					ग_लिखो addr must be after sec5. */
/*  */

व्योम
efuse_ReadEFuse(
	काष्ठा adapter *Adapter,
	u8 efuseType,
	u16 	_offset,
	u16 	_size_byte,
	u8 *pbuf,
bool	bPseuकरोTest
	);
व्योम
efuse_ReadEFuse(
	काष्ठा adapter *Adapter,
	u8 efuseType,
	u16 	_offset,
	u16 	_size_byte,
	u8 *pbuf,
bool	bPseuकरोTest
	)
अणु
	Adapter->HalFunc.ReadEFuse(Adapter, efuseType, _offset, _size_byte, pbuf, bPseuकरोTest);
पूर्ण

व्योम
EFUSE_GetEfuseDefinition(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u8 type,
	व्योम 	*pOut,
	bool		bPseuकरोTest
	)
अणु
	padapter->HalFunc.EFUSEGetEfuseDefinition(padapter, efuseType, type, pOut, bPseuकरोTest);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	EFUSE_Read1Byte
 *
 * Overview:	Copy from WMAC fot EFUSE पढ़ो 1 byte.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 09/23/2008	MHC		Copy from WMAC.
 *
 *---------------------------------------------------------------------------*/
u8
EFUSE_Read1Byte(
काष्ठा adapter *Adapter,
u16 	Address)
अणु
	u8 Bytetemp = अणु0x00पूर्ण;
	u8 temp = अणु0x00पूर्ण;
	u32 k = 0;
	u16 contentLen = 0;

	EFUSE_GetEfuseDefinition(Adapter, EFUSE_WIFI, TYPE_EFUSE_REAL_CONTENT_LEN, (व्योम *)&contentLen, false);

	अगर (Address < contentLen) अणु/* E-fuse 512Byte */
		/* Write E-fuse Register address bit0~7 */
		temp = Address & 0xFF;
		rtw_ग_लिखो8(Adapter, EFUSE_CTRL+1, temp);
		Bytetemp = rtw_पढ़ो8(Adapter, EFUSE_CTRL+2);
		/* Write E-fuse Register address bit8~9 */
		temp = ((Address >> 8) & 0x03) | (Bytetemp & 0xFC);
		rtw_ग_लिखो8(Adapter, EFUSE_CTRL+2, temp);

		/* Write 0x30[31]= 0 */
		Bytetemp = rtw_पढ़ो8(Adapter, EFUSE_CTRL+3);
		temp = Bytetemp & 0x7F;
		rtw_ग_लिखो8(Adapter, EFUSE_CTRL+3, temp);

		/* Wait Write-पढ़ोy (0x30[31]= 1) */
		Bytetemp = rtw_पढ़ो8(Adapter, EFUSE_CTRL+3);
		जबतक (!(Bytetemp & 0x80)) अणु
			Bytetemp = rtw_पढ़ो8(Adapter, EFUSE_CTRL+3);
			k++;
			अगर (k == 1000)
				अवरोध;
		पूर्ण
		वापस rtw_पढ़ो8(Adapter, EFUSE_CTRL);
	पूर्ण अन्यथा
		वापस 0xFF;

पूर्ण /* EFUSE_Read1Byte */

/*  11/16/2008 MH Read one byte from real Efuse. */
u8
efuse_OneByteRead(
काष्ठा adapter *padapter,
u16 		addr,
u8 	*data,
bool		bPseuकरोTest)
अणु
	u32 पंचांगpidx = 0;
	u8 bResult;
	u8 पढ़ोbyte;

	अगर (bPseuकरोTest) अणु
		वापस Efuse_Read1ByteFromFakeContent(padapter, addr, data);
	पूर्ण

	/*  <20130121, Kordan> For SMIC EFUSE specअगरicम_से_पn. */
	/* 0x34[11]: SW क्रमce PGMEN input of efuse to high. (क्रम the bank selected by 0x34[9:8]) */
	/* PHY_SetMacReg(padapter, 0x34, BIT11, 0); */
	rtw_ग_लिखो16(padapter, 0x34, rtw_पढ़ो16(padapter, 0x34) & (~BIT11));

	/*  -----------------e-fuse reg ctrl --------------------------------- */
	/* address */
	rtw_ग_लिखो8(padapter, EFUSE_CTRL+1, (u8)(addr&0xff));
	rtw_ग_लिखो8(padapter, EFUSE_CTRL+2, ((u8)((addr>>8) & 0x03)) |
	(rtw_पढ़ो8(padapter, EFUSE_CTRL+2)&0xFC));

	/* rtw_ग_लिखो8(padapter, EFUSE_CTRL+3,  0x72); पढ़ो cmd */
	/* Write bit 32 0 */
	पढ़ोbyte = rtw_पढ़ो8(padapter, EFUSE_CTRL+3);
	rtw_ग_लिखो8(padapter, EFUSE_CTRL+3, (पढ़ोbyte & 0x7f));

	जबतक (!(0x80 & rtw_पढ़ो8(padapter, EFUSE_CTRL+3)) && (पंचांगpidx < 1000)) अणु
		mdelay(1);
		पंचांगpidx++;
	पूर्ण
	अगर (पंचांगpidx < 100) अणु
		*data = rtw_पढ़ो8(padapter, EFUSE_CTRL);
		bResult = true;
	पूर्ण अन्यथा अणु
		*data = 0xff;
		bResult = false;
	पूर्ण

	वापस bResult;
पूर्ण

/*  11/16/2008 MH Write one byte to reald Efuse. */
u8 efuse_OneByteWrite(काष्ठा adapter *padapter, u16 addr, u8 data, bool bPseuकरोTest)
अणु
	u8 पंचांगpidx = 0;
	u8 bResult = false;
	u32 efuseValue = 0;

	अगर (bPseuकरोTest) अणु
		वापस Efuse_Write1ByteToFakeContent(padapter, addr, data);
	पूर्ण


	/*  -----------------e-fuse reg ctrl --------------------------------- */
	/* address */


	efuseValue = rtw_पढ़ो32(padapter, EFUSE_CTRL);
	efuseValue |= (BIT21|BIT31);
	efuseValue &= ~(0x3FFFF);
	efuseValue |= ((addr<<8 | data) & 0x3FFFF);


	/*  <20130227, Kordan> 8192E MP chip A-cut had better not set 0x34[11] until B-Cut. */

	/*  <20130121, Kordan> For SMIC EFUSE specअगरicम_से_पn. */
	/* 0x34[11]: SW क्रमce PGMEN input of efuse to high. (क्रम the bank selected by 0x34[9:8]) */
	/* PHY_SetMacReg(padapter, 0x34, BIT11, 1); */
	rtw_ग_लिखो16(padapter, 0x34, rtw_पढ़ो16(padapter, 0x34) | (BIT11));
	rtw_ग_लिखो32(padapter, EFUSE_CTRL, 0x90600000|((addr<<8 | data)));

	जबतक ((0x80 &  rtw_पढ़ो8(padapter, EFUSE_CTRL+3)) && (पंचांगpidx < 100)) अणु
		mdelay(1);
		पंचांगpidx++;
	पूर्ण

	अगर (पंचांगpidx < 100) अणु
		bResult = true;
	पूर्ण अन्यथा अणु
		bResult = false;
	पूर्ण

	/*  disable Efuse program enable */
	PHY_SetMacReg(padapter, EFUSE_TEST, BIT(11), 0);

	वापस bResult;
पूर्ण

पूर्णांक
Efuse_PgPacketRead(काष्ठा adapter *padapter,
				u8 	offset,
				u8 	*data,
				bool		bPseuकरोTest)
अणु
	वापस padapter->HalFunc.Efuse_PgPacketRead(padapter, offset, data,
						    bPseuकरोTest);
पूर्ण

पूर्णांक
Efuse_PgPacketWrite(काष्ठा adapter *padapter,
				u8 	offset,
				u8 	word_en,
				u8 	*data,
				bool		bPseuकरोTest)
अणु
	वापस padapter->HalFunc.Efuse_PgPacketWrite(padapter, offset, word_en,
						     data, bPseuकरोTest);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	efuse_WordEnableDataRead
 *
 * Overview:	Read allowed word in current efuse section data.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 11/16/2008	MHC		Create Version 0.
 * 11/21/2008	MHC		Fix Write bug when we only enable late word.
 *
 *---------------------------------------------------------------------------*/
व्योम
efuse_WordEnableDataRead(u8 word_en,
						u8 *sourdata,
						u8 *targetdata)
अणु
	अगर (!(word_en&BIT(0))) अणु
		targetdata[0] = sourdata[0];
		targetdata[1] = sourdata[1];
	पूर्ण
	अगर (!(word_en&BIT(1))) अणु
		targetdata[2] = sourdata[2];
		targetdata[3] = sourdata[3];
	पूर्ण
	अगर (!(word_en&BIT(2))) अणु
		targetdata[4] = sourdata[4];
		targetdata[5] = sourdata[5];
	पूर्ण
	अगर (!(word_en&BIT(3))) अणु
		targetdata[6] = sourdata[6];
		targetdata[7] = sourdata[7];
	पूर्ण
पूर्ण


u8
Efuse_WordEnableDataWrite(काष्ठा adapter *padapter,
						u16 	efuse_addr,
						u8 word_en,
						u8 *data,
						bool		bPseuकरोTest)
अणु
	वापस padapter->HalFunc.Efuse_WordEnableDataWrite(padapter, efuse_addr,
							   word_en, data,
							   bPseuकरोTest);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	Efuse_ReadAllMap
 *
 * Overview:	Read All Efuse content
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 11/11/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------*/
व्योम
Efuse_ReadAllMap(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u8 *Efuse,
	bool		bPseuकरोTest);
व्योम Efuse_ReadAllMap(काष्ठा adapter *padapter, u8 efuseType, u8 *Efuse, bool bPseuकरोTest)
अणु
	u16 mapLen = 0;

	Efuse_PowerSwitch(padapter, false, true);

	EFUSE_GetEfuseDefinition(padapter, efuseType, TYPE_EFUSE_MAP_LEN, (व्योम *)&mapLen, bPseuकरोTest);

	efuse_ReadEFuse(padapter, efuseType, 0, mapLen, Efuse, bPseuकरोTest);

	Efuse_PowerSwitch(padapter, false, false);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	efuse_ShaकरोwRead1Byte
 *		efuse_ShaकरोwRead2Byte
 *		efuse_ShaकरोwRead4Byte
 *
 * Overview:	Read from efuse init map by one/two/four bytes !!!!!
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 11/12/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------*/
अटल व्योम efuse_ShaकरोwRead1Byte(काष्ठा adapter *padapter, u16 Offset, u8 *Value)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	*Value = pEEPROM->efuse_eeprom_data[Offset];

पूर्ण	/*  EFUSE_ShaकरोwRead1Byte */

/* Read Two Bytes */
अटल व्योम efuse_ShaकरोwRead2Byte(काष्ठा adapter *padapter, u16 Offset, u16 *Value)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	*Value = pEEPROM->efuse_eeprom_data[Offset];
	*Value |= pEEPROM->efuse_eeprom_data[Offset+1]<<8;

पूर्ण	/*  EFUSE_ShaकरोwRead2Byte */

/* Read Four Bytes */
अटल व्योम efuse_ShaकरोwRead4Byte(काष्ठा adapter *padapter, u16 Offset, u32 *Value)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	*Value = pEEPROM->efuse_eeprom_data[Offset];
	*Value |= pEEPROM->efuse_eeprom_data[Offset+1]<<8;
	*Value |= pEEPROM->efuse_eeprom_data[Offset+2]<<16;
	*Value |= pEEPROM->efuse_eeprom_data[Offset+3]<<24;

पूर्ण	/*  efuse_ShaकरोwRead4Byte */

/*-----------------------------------------------------------------------------
 * Function:	EFUSE_ShaकरोwMapUpdate
 *
 * Overview:	Transfer current EFUSE content to shaकरोw init and modअगरy map.
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 11/13/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------*/
व्योम EFUSE_ShaकरोwMapUpdate(काष्ठा adapter *padapter, u8 efuseType, bool bPseuकरोTest)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);
	u16 mapLen = 0;

	EFUSE_GetEfuseDefinition(padapter, efuseType, TYPE_EFUSE_MAP_LEN, (व्योम *)&mapLen, bPseuकरोTest);

	अगर (pEEPROM->bस्वतःload_fail_flag)
		स_रखो(pEEPROM->efuse_eeprom_data, 0xFF, mapLen);
	अन्यथा
		Efuse_ReadAllMap(padapter, efuseType, pEEPROM->efuse_eeprom_data, bPseuकरोTest);

	/* Platक्रमmMoveMemory((व्योम *)&pHalData->EfuseMap[EFUSE_MODIFY_MAP][0], */
	/* व्योम *)&pHalData->EfuseMap[EFUSE_INIT_MAP][0], mapLen); */
पूर्ण /*  EFUSE_ShaकरोwMapUpdate */


/*-----------------------------------------------------------------------------
 * Function:	EFUSE_ShaकरोwRead
 *
 * Overview:	Read from efuse init map !!!!!
 *
 * Input:       NONE
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Revised History:
 * When			Who		Remark
 * 11/12/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------*/
व्योम EFUSE_ShaकरोwRead(काष्ठा adapter *padapter, u8 Type, u16 Offset, u32 *Value)
अणु
	अगर (Type == 1)
		efuse_ShaकरोwRead1Byte(padapter, Offset, (u8 *)Value);
	अन्यथा अगर (Type == 2)
		efuse_ShaकरोwRead2Byte(padapter, Offset, (u16 *)Value);
	अन्यथा अगर (Type == 4)
		efuse_ShaकरोwRead4Byte(padapter, Offset, (u32 *)Value);

पूर्ण	/* EFUSE_ShaकरोwRead*/
