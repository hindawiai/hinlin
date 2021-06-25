<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _HAL_INIT_C_

#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>
#समावेश "hal_com_h2c.h"

अटल व्योम _FWDownloadEnable(काष्ठा adapter *padapter, bool enable)
अणु
	u8 पंचांगp, count = 0;

	अगर (enable) अणु
		/*  8051 enable */
		पंचांगp = rtw_पढ़ो8(padapter, REG_SYS_FUNC_EN+1);
		rtw_ग_लिखो8(padapter, REG_SYS_FUNC_EN+1, पंचांगp|0x04);

		पंचांगp = rtw_पढ़ो8(padapter, REG_MCUFWDL);
		rtw_ग_लिखो8(padapter, REG_MCUFWDL, पंचांगp|0x01);

		करो अणु
			पंचांगp = rtw_पढ़ो8(padapter, REG_MCUFWDL);
			अगर (पंचांगp & 0x01)
				अवरोध;
			rtw_ग_लिखो8(padapter, REG_MCUFWDL, पंचांगp|0x01);
			msleep(1);
		पूर्ण जबतक (count++ < 100);

		/*  8051 reset */
		पंचांगp = rtw_पढ़ो8(padapter, REG_MCUFWDL+2);
		rtw_ग_लिखो8(padapter, REG_MCUFWDL+2, पंचांगp&0xf7);
	पूर्ण अन्यथा अणु
		/*  MCU firmware करोwnload disable. */
		पंचांगp = rtw_पढ़ो8(padapter, REG_MCUFWDL);
		rtw_ग_लिखो8(padapter, REG_MCUFWDL, पंचांगp&0xfe);
	पूर्ण
पूर्ण

अटल पूर्णांक _BlockWrite(काष्ठा adapter *padapter, व्योम *buffer, u32 buffSize)
अणु
	पूर्णांक ret = _SUCCESS;

	u32 blockSize_p1 = 4; /*  (Default) Phase #1 : PCI muse use 4-byte ग_लिखो to करोwnload FW */
	u32 blockSize_p2 = 8; /*  Phase #2 : Use 8-byte, अगर Phase#1 use big size to ग_लिखो FW. */
	u32 blockSize_p3 = 1; /*  Phase #3 : Use 1-byte, the remnant of FW image. */
	u32 blockCount_p1 = 0, blockCount_p2 = 0, blockCount_p3 = 0;
	u32 reमुख्यSize_p1 = 0, reमुख्यSize_p2 = 0;
	u8 *bufferPtr = buffer;
	u32 i = 0, offset = 0;

/* 	prपूर्णांकk("====>%s %d\n", __func__, __LINE__); */

	/* 3 Phase #1 */
	blockCount_p1 = buffSize / blockSize_p1;
	reमुख्यSize_p1 = buffSize % blockSize_p1;

	क्रम (i = 0; i < blockCount_p1; i++) अणु
		ret = rtw_ग_लिखो32(padapter, (FW_8723B_START_ADDRESS + i * blockSize_p1), *((u32 *)(bufferPtr + i * blockSize_p1)));
		अगर (ret == _FAIL) अणु
			prपूर्णांकk("====>%s %d i:%d\n", __func__, __LINE__, i);
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* 3 Phase #2 */
	अगर (reमुख्यSize_p1) अणु
		offset = blockCount_p1 * blockSize_p1;

		blockCount_p2 = reमुख्यSize_p1/blockSize_p2;
		reमुख्यSize_p2 = reमुख्यSize_p1%blockSize_p2;
	पूर्ण

	/* 3 Phase #3 */
	अगर (reमुख्यSize_p2) अणु
		offset = (blockCount_p1 * blockSize_p1) + (blockCount_p2 * blockSize_p2);

		blockCount_p3 = reमुख्यSize_p2 / blockSize_p3;

		क्रम (i = 0; i < blockCount_p3; i++) अणु
			ret = rtw_ग_लिखो8(padapter, (FW_8723B_START_ADDRESS + offset + i), *(bufferPtr + offset + i));

			अगर (ret == _FAIL) अणु
				prपूर्णांकk("====>%s %d i:%d\n", __func__, __LINE__, i);
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक _PageWrite(
	काष्ठा adapter *padapter,
	u32 page,
	व्योम *buffer,
	u32 size
)
अणु
	u8 value8;
	u8 u8Page = (u8) (page & 0x07);

	value8 = (rtw_पढ़ो8(padapter, REG_MCUFWDL+2) & 0xF8) | u8Page;
	rtw_ग_लिखो8(padapter, REG_MCUFWDL+2, value8);

	वापस _BlockWrite(padapter, buffer, size);
पूर्ण

अटल पूर्णांक _WriteFW(काष्ठा adapter *padapter, व्योम *buffer, u32 size)
अणु
	/*  Since we need dynamic decide method of dwonload fw, so we call this function to get chip version. */
	/*  We can हटाओ _ReadChipVersion from ReadpadapterInfo8192C later. */
	पूर्णांक ret = _SUCCESS;
	u32 pageNums, reमुख्यSize;
	u32 page, offset;
	u8 *bufferPtr = buffer;

	pageNums = size / MAX_DLFW_PAGE_SIZE;
	/* RT_ASSERT((pageNums <= 4), ("Page numbers should not greater then 4\n")); */
	reमुख्यSize = size % MAX_DLFW_PAGE_SIZE;

	क्रम (page = 0; page < pageNums; page++) अणु
		offset = page * MAX_DLFW_PAGE_SIZE;
		ret = _PageWrite(padapter, page, bufferPtr+offset, MAX_DLFW_PAGE_SIZE);

		अगर (ret == _FAIL) अणु
			prपूर्णांकk("====>%s %d\n", __func__, __LINE__);
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (reमुख्यSize) अणु
		offset = pageNums * MAX_DLFW_PAGE_SIZE;
		page = pageNums;
		ret = _PageWrite(padapter, page, bufferPtr+offset, reमुख्यSize);

		अगर (ret == _FAIL) अणु
			prपूर्णांकk("====>%s %d\n", __func__, __LINE__);
			जाओ निकास;
		पूर्ण
	पूर्ण

निकास:
	वापस ret;
पूर्ण

व्योम _8051Reset8723(काष्ठा adapter *padapter)
अणु
	u8 cpu_rst;
	u8 io_rst;


	/*  Reset 8051(WLMCU) IO wrapper */
	/*  0x1c[8] = 0 */
	/*  Suggested by Isaac@SD1 and Gimmy@SD1, coding by Lucas@20130624 */
	io_rst = rtw_पढ़ो8(padapter, REG_RSV_CTRL+1);
	io_rst &= ~BIT(0);
	rtw_ग_लिखो8(padapter, REG_RSV_CTRL+1, io_rst);

	cpu_rst = rtw_पढ़ो8(padapter, REG_SYS_FUNC_EN+1);
	cpu_rst &= ~BIT(2);
	rtw_ग_लिखो8(padapter, REG_SYS_FUNC_EN+1, cpu_rst);

	/*  Enable 8051 IO wrapper */
	/*  0x1c[8] = 1 */
	io_rst = rtw_पढ़ो8(padapter, REG_RSV_CTRL+1);
	io_rst |= BIT(0);
	rtw_ग_लिखो8(padapter, REG_RSV_CTRL+1, io_rst);

	cpu_rst = rtw_पढ़ो8(padapter, REG_SYS_FUNC_EN+1);
	cpu_rst |= BIT(2);
	rtw_ग_लिखो8(padapter, REG_SYS_FUNC_EN+1, cpu_rst);
पूर्ण

u8 g_fwdl_chksum_fail;

अटल s32 polling_fwdl_chksum(
	काष्ठा adapter *adapter, u32 min_cnt, u32 समयout_ms
)
अणु
	s32 ret = _FAIL;
	u32 value32;
	अचिन्हित दीर्घ start = jअगरfies;
	u32 cnt = 0;

	/* polling CheckSum report */
	करो अणु
		cnt++;
		value32 = rtw_पढ़ो32(adapter, REG_MCUFWDL);
		अगर (value32 & FWDL_ChkSum_rpt || adapter->bSurpriseRemoved || adapter->bDriverStopped)
			अवरोध;
		yield();
	पूर्ण जबतक (jअगरfies_to_msecs(jअगरfies-start) < समयout_ms || cnt < min_cnt);

	अगर (!(value32 & FWDL_ChkSum_rpt)) अणु
		जाओ निकास;
	पूर्ण

	अगर (g_fwdl_chksum_fail) अणु
		g_fwdl_chksum_fail--;
		जाओ निकास;
	पूर्ण

	ret = _SUCCESS;

निकास:

	वापस ret;
पूर्ण

u8 g_fwdl_wपूर्णांकपूर्णांक_rdy_fail;

अटल s32 _FWFreeToGo(काष्ठा adapter *adapter, u32 min_cnt, u32 समयout_ms)
अणु
	s32 ret = _FAIL;
	u32 value32;
	अचिन्हित दीर्घ start = jअगरfies;
	u32 cnt = 0;

	value32 = rtw_पढ़ो32(adapter, REG_MCUFWDL);
	value32 |= MCUFWDL_RDY;
	value32 &= ~WINTINI_RDY;
	rtw_ग_लिखो32(adapter, REG_MCUFWDL, value32);

	_8051Reset8723(adapter);

	/*  polling क्रम FW पढ़ोy */
	करो अणु
		cnt++;
		value32 = rtw_पढ़ो32(adapter, REG_MCUFWDL);
		अगर (value32 & WINTINI_RDY || adapter->bSurpriseRemoved || adapter->bDriverStopped)
			अवरोध;
		yield();
	पूर्ण जबतक (jअगरfies_to_msecs(jअगरfies - start) < समयout_ms || cnt < min_cnt);

	अगर (!(value32 & WINTINI_RDY)) अणु
		जाओ निकास;
	पूर्ण

	अगर (g_fwdl_wपूर्णांकपूर्णांक_rdy_fail) अणु
		g_fwdl_wपूर्णांकपूर्णांक_rdy_fail--;
		जाओ निकास;
	पूर्ण

	ret = _SUCCESS;

निकास:

	वापस ret;
पूर्ण

#घोषणा IS_FW_81xxC(padapter)	(((GET_HAL_DATA(padapter))->FirmwareSignature & 0xFFF0) == 0x88C0)

व्योम rtl8723b_FirmwareSelfReset(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 u1bTmp;
	u8 Delay = 100;

	अगर (
		!(IS_FW_81xxC(padapter) && ((pHalData->FirmwareVersion < 0x21) || (pHalData->FirmwareVersion == 0x21 && pHalData->FirmwareSubVersion < 0x01)))
	) अणु /*  after 88C Fw v33.1 */
		/* 0x1cf = 0x20. Inक्रमm 8051 to reset. 2009.12.25. tynli_test */
		rtw_ग_लिखो8(padapter, REG_HMETFR+3, 0x20);

		u1bTmp = rtw_पढ़ो8(padapter, REG_SYS_FUNC_EN+1);
		जबतक (u1bTmp & BIT2) अणु
			Delay--;
			अगर (Delay == 0)
				अवरोध;
			udelay(50);
			u1bTmp = rtw_पढ़ो8(padapter, REG_SYS_FUNC_EN+1);
		पूर्ण

		अगर (Delay == 0) अणु
			/* क्रमce firmware reset */
			u1bTmp = rtw_पढ़ो8(padapter, REG_SYS_FUNC_EN+1);
			rtw_ग_लिखो8(padapter, REG_SYS_FUNC_EN+1, u1bTmp&(~BIT2));
		पूर्ण
	पूर्ण
पूर्ण

/*  */
/* 	Description: */
/* 		Download 8192C firmware code. */
/*  */
/*  */
s32 rtl8723b_FirmwareDownload(काष्ठा adapter *padapter, bool  bUsedWoWLANFw)
अणु
	s32 rtStatus = _SUCCESS;
	u8 ग_लिखो_fw = 0;
	अचिन्हित दीर्घ fwdl_start_समय;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा rt_firmware *pFirmware;
	काष्ठा rt_firmware *pBTFirmware;
	काष्ठा rt_firmware_hdr *pFwHdr = शून्य;
	u8 *pFirmwareBuf;
	u32 FirmwareLen;
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *device = dvobj_to_dev(padapter->dvobj);
	u8 *fwfilepath;
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;
	u8 पंचांगp_ps;

	pFirmware = kzalloc(माप(काष्ठा rt_firmware), GFP_KERNEL);
	अगर (!pFirmware)
		वापस _FAIL;
	pBTFirmware = kzalloc(माप(काष्ठा rt_firmware), GFP_KERNEL);
	अगर (!pBTFirmware) अणु
		kमुक्त(pFirmware);
		वापस _FAIL;
	पूर्ण
	पंचांगp_ps = rtw_पढ़ो8(padapter, 0xa3);
	पंचांगp_ps &= 0xf8;
	पंचांगp_ps |= 0x02;
	/* 1. ग_लिखो 0xA3[:2:0] = 3b'010 */
	rtw_ग_लिखो8(padapter, 0xa3, पंचांगp_ps);
	/* 2. पढ़ो घातer_state = 0xA0[1:0] */
	पंचांगp_ps = rtw_पढ़ो8(padapter, 0xa0);
	पंचांगp_ps &= 0x03;
	अगर (पंचांगp_ps != 0x01)
		pdbgpriv->dbg_करोwnloadfw_pwr_state_cnt++;

	fwfilepath = "rtlwifi/rtl8723bs_nic.bin";

	pr_info("rtl8723bs: acquire FW from file:%s\n", fwfilepath);

	rtStatus = request_firmware(&fw, fwfilepath, device);
	अगर (rtStatus) अणु
		pr_err("Request firmware failed with error 0x%x\n", rtStatus);
		rtStatus = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (!fw) अणु
		pr_err("Firmware %s not available\n", fwfilepath);
		rtStatus = _FAIL;
		जाओ निकास;
	पूर्ण

	अगर (fw->size > FW_8723B_SIZE) अणु
		rtStatus = _FAIL;
		जाओ निकास;
	पूर्ण

	pFirmware->fw_buffer_sz = kmemdup(fw->data, fw->size, GFP_KERNEL);
	अगर (!pFirmware->fw_buffer_sz) अणु
		rtStatus = _FAIL;
		जाओ निकास;
	पूर्ण

	pFirmware->fw_length = fw->size;
	release_firmware(fw);
	अगर (pFirmware->fw_length > FW_8723B_SIZE) अणु
		rtStatus = _FAIL;
		netdev_emerg(padapter->pnetdev,
			     "Firmware size:%u exceed %u\n",
			     pFirmware->fw_length, FW_8723B_SIZE);
		जाओ release_fw1;
	पूर्ण

	pFirmwareBuf = pFirmware->fw_buffer_sz;
	FirmwareLen = pFirmware->fw_length;

	/*  To Check Fw header. Added by tynli. 2009.12.04. */
	pFwHdr = (काष्ठा rt_firmware_hdr *)pFirmwareBuf;

	pHalData->FirmwareVersion =  le16_to_cpu(pFwHdr->version);
	pHalData->FirmwareSubVersion = le16_to_cpu(pFwHdr->subversion);
	pHalData->FirmwareSignature = le16_to_cpu(pFwHdr->signature);

	अगर (IS_FW_HEADER_EXIST_8723B(pFwHdr)) अणु
		/*  Shअगरt 32 bytes क्रम FW header */
		pFirmwareBuf = pFirmwareBuf + 32;
		FirmwareLen = FirmwareLen - 32;
	पूर्ण

	/*  Suggested by Filen. If 8051 is running in RAM code, driver should inक्रमm Fw to reset by itself, */
	/*  or it will cause करोwnload Fw fail. 2010.02.01. by tynli. */
	अगर (rtw_पढ़ो8(padapter, REG_MCUFWDL) & RAM_DL_SEL) अणु /* 8051 RAM code */
		rtw_ग_लिखो8(padapter, REG_MCUFWDL, 0x00);
		rtl8723b_FirmwareSelfReset(padapter);
	पूर्ण

	_FWDownloadEnable(padapter, true);
	fwdl_start_समय = jअगरfies;
	जबतक (
		!padapter->bDriverStopped &&
		!padapter->bSurpriseRemoved &&
		(ग_लिखो_fw++ < 3 || jअगरfies_to_msecs(jअगरfies - fwdl_start_समय) < 500)
	) अणु
		/* reset FWDL chksum */
		rtw_ग_लिखो8(padapter, REG_MCUFWDL, rtw_पढ़ो8(padapter, REG_MCUFWDL)|FWDL_ChkSum_rpt);

		rtStatus = _WriteFW(padapter, pFirmwareBuf, FirmwareLen);
		अगर (rtStatus != _SUCCESS)
			जारी;

		rtStatus = polling_fwdl_chksum(padapter, 5, 50);
		अगर (rtStatus == _SUCCESS)
			अवरोध;
	पूर्ण
	_FWDownloadEnable(padapter, false);
	अगर (_SUCCESS != rtStatus)
		जाओ fwdl_stat;

	rtStatus = _FWFreeToGo(padapter, 10, 200);
	अगर (_SUCCESS != rtStatus)
		जाओ fwdl_stat;

fwdl_stat:

निकास:
	kमुक्त(pFirmware->fw_buffer_sz);
	kमुक्त(pFirmware);
release_fw1:
	kमुक्त(pBTFirmware);
	वापस rtStatus;
पूर्ण

व्योम rtl8723b_InitializeFirmwareVars(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	/*  Init Fw LPS related. */
	adapter_to_pwrctl(padapter)->fw_current_in_ps_mode = false;

	/* Init H2C cmd. */
	rtw_ग_लिखो8(padapter, REG_HMETFR, 0x0f);

	/*  Init H2C counter. by tynli. 2009.12.09. */
	pHalData->LastHMEBoxNum = 0;
/* pHalData->H2CQueueHead = 0; */
/* pHalData->H2CQueueTail = 0; */
/* pHalData->H2CStopInsertQueue = false; */
पूर्ण

अटल व्योम rtl8723b_मुक्त_hal_data(काष्ठा adapter *padapter)
अणु
पूर्ण

/*  */
/* 				Efuse related code */
/*  */
अटल u8 hal_EfuseSwitchToBank(
	काष्ठा adapter *padapter, u8 bank, bool bPseuकरोTest
)
अणु
	u8 bRet = false;
	u32 value32 = 0;
#अगर_घोषित HAL_EFUSE_MEMORY
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा efuse_hal *pEfuseHal = &pHalData->EfuseHal;
#पूर्ण_अगर


	अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
		pEfuseHal->fakeEfuseBank = bank;
#अन्यथा
		fakeEfuseBank = bank;
#पूर्ण_अगर
		bRet = true;
	पूर्ण अन्यथा अणु
		value32 = rtw_पढ़ो32(padapter, EFUSE_TEST);
		bRet = true;
		चयन (bank) अणु
		हाल 0:
			value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_WIFI_SEL_0);
			अवरोध;
		हाल 1:
			value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_BT_SEL_0);
			अवरोध;
		हाल 2:
			value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_BT_SEL_1);
			अवरोध;
		हाल 3:
			value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_BT_SEL_2);
			अवरोध;
		शेष:
			value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_WIFI_SEL_0);
			bRet = false;
			अवरोध;
		पूर्ण
		rtw_ग_लिखो32(padapter, EFUSE_TEST, value32);
	पूर्ण

	वापस bRet;
पूर्ण

अटल व्योम Hal_GetEfuseDefinition(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u8 type,
	व्योम *pOut,
	bool bPseuकरोTest
)
अणु
	चयन (type) अणु
	हाल TYPE_EFUSE_MAX_SECTION:
		अणु
			u8 *pMax_section;
			pMax_section = pOut;

			अगर (efuseType == EFUSE_WIFI)
				*pMax_section = EFUSE_MAX_SECTION_8723B;
			अन्यथा
				*pMax_section = EFUSE_BT_MAX_SECTION;
		पूर्ण
		अवरोध;

	हाल TYPE_EFUSE_REAL_CONTENT_LEN:
		अणु
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			अगर (efuseType == EFUSE_WIFI)
				*pu2Tmp = EFUSE_REAL_CONTENT_LEN_8723B;
			अन्यथा
				*pu2Tmp = EFUSE_BT_REAL_CONTENT_LEN;
		पूर्ण
		अवरोध;

	हाल TYPE_AVAILABLE_EFUSE_BYTES_BANK:
		अणु
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			अगर (efuseType == EFUSE_WIFI)
				*pu2Tmp = (EFUSE_REAL_CONTENT_LEN_8723B-EFUSE_OOB_PROTECT_BYTES);
			अन्यथा
				*pu2Tmp = (EFUSE_BT_REAL_BANK_CONTENT_LEN-EFUSE_PROTECT_BYTES_BANK);
		पूर्ण
		अवरोध;

	हाल TYPE_AVAILABLE_EFUSE_BYTES_TOTAL:
		अणु
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			अगर (efuseType == EFUSE_WIFI)
				*pu2Tmp = (EFUSE_REAL_CONTENT_LEN_8723B-EFUSE_OOB_PROTECT_BYTES);
			अन्यथा
				*pu2Tmp = (EFUSE_BT_REAL_CONTENT_LEN-(EFUSE_PROTECT_BYTES_BANK*3));
		पूर्ण
		अवरोध;

	हाल TYPE_EFUSE_MAP_LEN:
		अणु
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			अगर (efuseType == EFUSE_WIFI)
				*pu2Tmp = EFUSE_MAX_MAP_LEN;
			अन्यथा
				*pu2Tmp = EFUSE_BT_MAP_LEN;
		पूर्ण
		अवरोध;

	हाल TYPE_EFUSE_PROTECT_BYTES_BANK:
		अणु
			u8 *pu1Tmp;
			pu1Tmp = pOut;

			अगर (efuseType == EFUSE_WIFI)
				*pu1Tmp = EFUSE_OOB_PROTECT_BYTES;
			अन्यथा
				*pu1Tmp = EFUSE_PROTECT_BYTES_BANK;
		पूर्ण
		अवरोध;

	हाल TYPE_EFUSE_CONTENT_LEN_BANK:
		अणु
			u16 *pu2Tmp;
			pu2Tmp = pOut;

			अगर (efuseType == EFUSE_WIFI)
				*pu2Tmp = EFUSE_REAL_CONTENT_LEN_8723B;
			अन्यथा
				*pu2Tmp = EFUSE_BT_REAL_BANK_CONTENT_LEN;
		पूर्ण
		अवरोध;

	शेष:
		अणु
			u8 *pu1Tmp;
			pu1Tmp = pOut;
			*pu1Tmp = 0;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा VOLTAGE_V25		0x03
#घोषणा LDOE25_SHIFT	28

/*  */
/* 	The following is क्रम compile ok */
/* 	That should be merged with the original in the future */
/*  */
#घोषणा EFUSE_ACCESS_ON_8723			0x69	/*  For RTL8723 only. */
#घोषणा EFUSE_ACCESS_OFF_8723			0x00	/*  For RTL8723 only. */
#घोषणा REG_EFUSE_ACCESS_8723			0x00CF	/*  Efuse access protection क्रम RTL8723 */

/*  */
अटल व्योम Hal_BT_EfusePowerSwitch(
	काष्ठा adapter *padapter, u8 bWrite, u8 PwrState
)
अणु
	u8 tempval;
	अगर (PwrState) अणु
		/*  enable BT घातer cut */
		/*  0x6A[14] = 1 */
		tempval = rtw_पढ़ो8(padapter, 0x6B);
		tempval |= BIT(6);
		rtw_ग_लिखो8(padapter, 0x6B, tempval);

		/*  Attention!! Between 0x6A[14] and 0x6A[15] setting need 100us delay */
		/*  So करोn't ग_लिखो 0x6A[14]= 1 and 0x6A[15]= 0 together! */
		msleep(1);
		/*  disable BT output isolation */
		/*  0x6A[15] = 0 */
		tempval = rtw_पढ़ो8(padapter, 0x6B);
		tempval &= ~BIT(7);
		rtw_ग_लिखो8(padapter, 0x6B, tempval);
	पूर्ण अन्यथा अणु
		/*  enable BT output isolation */
		/*  0x6A[15] = 1 */
		tempval = rtw_पढ़ो8(padapter, 0x6B);
		tempval |= BIT(7);
		rtw_ग_लिखो8(padapter, 0x6B, tempval);

		/*  Attention!! Between 0x6A[14] and 0x6A[15] setting need 100us delay */
		/*  So करोn't ग_लिखो 0x6A[14]= 1 and 0x6A[15]= 0 together! */

		/*  disable BT घातer cut */
		/*  0x6A[14] = 1 */
		tempval = rtw_पढ़ो8(padapter, 0x6B);
		tempval &= ~BIT(6);
		rtw_ग_लिखो8(padapter, 0x6B, tempval);
	पूर्ण

पूर्ण
अटल व्योम Hal_EfusePowerSwitch(
	काष्ठा adapter *padapter, u8 bWrite, u8 PwrState
)
अणु
	u8 tempval;
	u16 पंचांगpV16;


	अगर (PwrState) अणु
		/*  To aव्योम cannot access efuse regsiters after disable/enable several बार during DTM test. */
		/*  Suggested by SD1 IsaacHsu. 2013.07.08, added by tynli. */
		tempval = rtw_पढ़ो8(padapter, SDIO_LOCAL_BASE|SDIO_REG_HSUS_CTRL);
		अगर (tempval & BIT(0)) अणु /*  SDIO local रेजिस्टर is suspend */
			u8 count = 0;


			tempval &= ~BIT(0);
			rtw_ग_लिखो8(padapter, SDIO_LOCAL_BASE|SDIO_REG_HSUS_CTRL, tempval);

			/*  check 0x86[1:0]= 10'2h, रुको घातer state to leave suspend */
			करो अणु
				tempval = rtw_पढ़ो8(padapter, SDIO_LOCAL_BASE|SDIO_REG_HSUS_CTRL);
				tempval &= 0x3;
				अगर (tempval == 0x02)
					अवरोध;

				count++;
				अगर (count >= 100)
					अवरोध;

				mdelay(10);
			पूर्ण जबतक (1);
		पूर्ण

		rtw_ग_लिखो8(padapter, REG_EFUSE_ACCESS_8723, EFUSE_ACCESS_ON_8723);

		/*  Reset: 0x0000h[28], शेष valid */
		पंचांगpV16 =  rtw_पढ़ो16(padapter, REG_SYS_FUNC_EN);
		अगर (!(पंचांगpV16 & FEN_ELDR)) अणु
			पंचांगpV16 |= FEN_ELDR;
			rtw_ग_लिखो16(padapter, REG_SYS_FUNC_EN, पंचांगpV16);
		पूर्ण

		/*  Clock: Gated(0x0008h[5]) 8M(0x0008h[1]) घड़ी from ANA, शेष valid */
		पंचांगpV16 = rtw_पढ़ो16(padapter, REG_SYS_CLKR);
		अगर ((!(पंचांगpV16 & LOADER_CLK_EN))  || (!(पंचांगpV16 & ANA8M))) अणु
			पंचांगpV16 |= (LOADER_CLK_EN | ANA8M);
			rtw_ग_लिखो16(padapter, REG_SYS_CLKR, पंचांगpV16);
		पूर्ण

		अगर (bWrite) अणु
			/*  Enable LDO 2.5V beक्रमe पढ़ो/ग_लिखो action */
			tempval = rtw_पढ़ो8(padapter, EFUSE_TEST+3);
			tempval &= 0x0F;
			tempval |= (VOLTAGE_V25 << 4);
			rtw_ग_लिखो8(padapter, EFUSE_TEST+3, (tempval | 0x80));

			/* rtw_ग_लिखो8(padapter, REG_EFUSE_ACCESS, EFUSE_ACCESS_ON); */
		पूर्ण
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो8(padapter, REG_EFUSE_ACCESS, EFUSE_ACCESS_OFF);

		अगर (bWrite) अणु
			/*  Disable LDO 2.5V after पढ़ो/ग_लिखो action */
			tempval = rtw_पढ़ो8(padapter, EFUSE_TEST+3);
			rtw_ग_लिखो8(padapter, EFUSE_TEST+3, (tempval & 0x7F));
		पूर्ण

	पूर्ण
पूर्ण

अटल व्योम hal_ReadEFuse_WiFi(
	काष्ठा adapter *padapter,
	u16 _offset,
	u16 _size_byte,
	u8 *pbuf,
	bool bPseuकरोTest
)
अणु
#अगर_घोषित HAL_EFUSE_MEMORY
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा efuse_hal *pEfuseHal = &pHalData->EfuseHal;
#पूर्ण_अगर
	u8 *efuseTbl = शून्य;
	u16 eFuse_Addr = 0;
	u8 offset, wden;
	u8 efuseHeader, efuseExtHdr, efuseData;
	u16 i, total, used;
	u8 efuse_usage = 0;

	/*  */
	/*  Do NOT excess total size of EFuse table. Added by Roger, 2008.11.10. */
	/*  */
	अगर ((_offset + _size_byte) > EFUSE_MAX_MAP_LEN)
		वापस;

	efuseTbl = rtw_दो_स्मृति(EFUSE_MAX_MAP_LEN);
	अगर (!efuseTbl)
		वापस;

	/*  0xff will be efuse शेष value instead of 0x00. */
	स_रखो(efuseTbl, 0xFF, EFUSE_MAX_MAP_LEN);

	/*  चयन bank back to bank 0 क्रम later BT and wअगरi use. */
	hal_EfuseSwitchToBank(padapter, 0, bPseuकरोTest);

	जबतक (AVAILABLE_EFUSE_ADDR(eFuse_Addr)) अणु
		efuse_OneByteRead(padapter, eFuse_Addr++, &efuseHeader, bPseuकरोTest);
		अगर (efuseHeader == 0xFF)
			अवरोध;

		/*  Check PG header क्रम section num. */
		अगर (EXT_HEADER(efuseHeader)) अणु /* extended header */
			offset = GET_HDR_OFFSET_2_0(efuseHeader);

			efuse_OneByteRead(padapter, eFuse_Addr++, &efuseExtHdr, bPseuकरोTest);
			अगर (ALL_WORDS_DISABLED(efuseExtHdr))
				जारी;

			offset |= ((efuseExtHdr & 0xF0) >> 1);
			wden = (efuseExtHdr & 0x0F);
		पूर्ण अन्यथा अणु
			offset = ((efuseHeader >> 4) & 0x0f);
			wden = (efuseHeader & 0x0f);
		पूर्ण

		अगर (offset < EFUSE_MAX_SECTION_8723B) अणु
			u16 addr;
			/*  Get word enable value from PG header */

			addr = offset * PGPKT_DATA_SIZE;
			क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++) अणु
				/*  Check word enable condition in the section */
				अगर (!(wden & (0x01<<i))) अणु
					efuse_OneByteRead(padapter, eFuse_Addr++, &efuseData, bPseuकरोTest);
					efuseTbl[addr] = efuseData;

					efuse_OneByteRead(padapter, eFuse_Addr++, &efuseData, bPseuकरोTest);
					efuseTbl[addr+1] = efuseData;
				पूर्ण
				addr += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			eFuse_Addr += Efuse_CalculateWordCnts(wden)*2;
		पूर्ण
	पूर्ण

	/*  Copy from Efuse map to output poपूर्णांकer memory!!! */
	क्रम (i = 0; i < _size_byte; i++)
		pbuf[i] = efuseTbl[_offset+i];

	/*  Calculate Efuse utilization */
	EFUSE_GetEfuseDefinition(padapter, EFUSE_WIFI, TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, &total, bPseuकरोTest);
	used = eFuse_Addr - 1;
	efuse_usage = (u8)((used*100)/total);
	अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
		pEfuseHal->fakeEfuseUsedBytes = used;
#अन्यथा
		fakeEfuseUsedBytes = used;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		rtw_hal_set_hwreg(padapter, HW_VAR_EFUSE_BYTES, (u8 *)&used);
		rtw_hal_set_hwreg(padapter, HW_VAR_EFUSE_USAGE, (u8 *)&efuse_usage);
	पूर्ण

	kमुक्त(efuseTbl);
पूर्ण

अटल व्योम hal_ReadEFuse_BT(
	काष्ठा adapter *padapter,
	u16 _offset,
	u16 _size_byte,
	u8 *pbuf,
	bool bPseuकरोTest
)
अणु
#अगर_घोषित HAL_EFUSE_MEMORY
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा efuse_hal *pEfuseHal = &pHalData->EfuseHal;
#पूर्ण_अगर
	u8 *efuseTbl;
	u8 bank;
	u16 eFuse_Addr;
	u8 efuseHeader, efuseExtHdr, efuseData;
	u8 offset, wden;
	u16 i, total, used;
	u8 efuse_usage;


	/*  */
	/*  Do NOT excess total size of EFuse table. Added by Roger, 2008.11.10. */
	/*  */
	अगर ((_offset + _size_byte) > EFUSE_BT_MAP_LEN)
		वापस;

	efuseTbl = rtw_दो_स्मृति(EFUSE_BT_MAP_LEN);
	अगर (!efuseTbl)
		वापस;

	/*  0xff will be efuse शेष value instead of 0x00. */
	स_रखो(efuseTbl, 0xFF, EFUSE_BT_MAP_LEN);

	EFUSE_GetEfuseDefinition(padapter, EFUSE_BT, TYPE_AVAILABLE_EFUSE_BYTES_BANK, &total, bPseuकरोTest);

	क्रम (bank = 1; bank < 3; bank++) अणु /*  8723b Max bake 0~2 */
		अगर (hal_EfuseSwitchToBank(padapter, bank, bPseuकरोTest) == false)
			जाओ निकास;

		eFuse_Addr = 0;

		जबतक (AVAILABLE_EFUSE_ADDR(eFuse_Addr)) अणु
			efuse_OneByteRead(padapter, eFuse_Addr++, &efuseHeader, bPseuकरोTest);
			अगर (efuseHeader == 0xFF)
				अवरोध;

			/*  Check PG header क्रम section num. */
			अगर (EXT_HEADER(efuseHeader)) अणु /* extended header */
				offset = GET_HDR_OFFSET_2_0(efuseHeader);

				efuse_OneByteRead(padapter, eFuse_Addr++, &efuseExtHdr, bPseuकरोTest);
				अगर (ALL_WORDS_DISABLED(efuseExtHdr))
					जारी;


				offset |= ((efuseExtHdr & 0xF0) >> 1);
				wden = (efuseExtHdr & 0x0F);
			पूर्ण अन्यथा अणु
				offset = ((efuseHeader >> 4) & 0x0f);
				wden = (efuseHeader & 0x0f);
			पूर्ण

			अगर (offset < EFUSE_BT_MAX_SECTION) अणु
				u16 addr;

				addr = offset * PGPKT_DATA_SIZE;
				क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++) अणु
					/*  Check word enable condition in the section */
					अगर (!(wden & (0x01<<i))) अणु
						efuse_OneByteRead(padapter, eFuse_Addr++, &efuseData, bPseuकरोTest);
						efuseTbl[addr] = efuseData;

						efuse_OneByteRead(padapter, eFuse_Addr++, &efuseData, bPseuकरोTest);
						efuseTbl[addr+1] = efuseData;
					पूर्ण
					addr += 2;
				पूर्ण
			पूर्ण अन्यथा अणु
				eFuse_Addr += Efuse_CalculateWordCnts(wden)*2;
			पूर्ण
		पूर्ण

		अगर ((eFuse_Addr - 1) < total)
			अवरोध;

	पूर्ण

	/*  चयन bank back to bank 0 क्रम later BT and wअगरi use. */
	hal_EfuseSwitchToBank(padapter, 0, bPseuकरोTest);

	/*  Copy from Efuse map to output poपूर्णांकer memory!!! */
	क्रम (i = 0; i < _size_byte; i++)
		pbuf[i] = efuseTbl[_offset+i];

	/*  */
	/*  Calculate Efuse utilization. */
	/*  */
	EFUSE_GetEfuseDefinition(padapter, EFUSE_BT, TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, &total, bPseuकरोTest);
	used = (EFUSE_BT_REAL_BANK_CONTENT_LEN*(bank-1)) + eFuse_Addr - 1;
	efuse_usage = (u8)((used*100)/total);
	अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
		pEfuseHal->fakeBTEfuseUsedBytes = used;
#अन्यथा
		fakeBTEfuseUsedBytes = used;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		rtw_hal_set_hwreg(padapter, HW_VAR_EFUSE_BT_BYTES, (u8 *)&used);
		rtw_hal_set_hwreg(padapter, HW_VAR_EFUSE_BT_USAGE, (u8 *)&efuse_usage);
	पूर्ण

निकास:
	kमुक्त(efuseTbl);
पूर्ण

अटल व्योम Hal_ReadEFuse(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u16 _offset,
	u16 _size_byte,
	u8 *pbuf,
	bool bPseuकरोTest
)
अणु
	अगर (efuseType == EFUSE_WIFI)
		hal_ReadEFuse_WiFi(padapter, _offset, _size_byte, pbuf, bPseuकरोTest);
	अन्यथा
		hal_ReadEFuse_BT(padapter, _offset, _size_byte, pbuf, bPseuकरोTest);
पूर्ण

अटल u16 hal_EfuseGetCurrentSize_WiFi(
	काष्ठा adapter *padapter, bool bPseuकरोTest
)
अणु
#अगर_घोषित HAL_EFUSE_MEMORY
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा efuse_hal *pEfuseHal = &pHalData->EfuseHal;
#पूर्ण_अगर
	u16 efuse_addr = 0;
	u16 start_addr = 0; /*  क्रम debug */
	u8 hoffset = 0, hworden = 0;
	u8 efuse_data, word_cnts = 0;
	u32 count = 0; /*  क्रम debug */


	अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
		efuse_addr = (u16)pEfuseHal->fakeEfuseUsedBytes;
#अन्यथा
		efuse_addr = (u16)fakeEfuseUsedBytes;
#पूर्ण_अगर
	पूर्ण अन्यथा
		rtw_hal_get_hwreg(padapter, HW_VAR_EFUSE_BYTES, (u8 *)&efuse_addr);

	start_addr = efuse_addr;

	/*  चयन bank back to bank 0 क्रम later BT and wअगरi use. */
	hal_EfuseSwitchToBank(padapter, 0, bPseuकरोTest);

	count = 0;
	जबतक (AVAILABLE_EFUSE_ADDR(efuse_addr)) अणु
		अगर (efuse_OneByteRead(padapter, efuse_addr, &efuse_data, bPseuकरोTest) == false)
			जाओ error;

		अगर (efuse_data == 0xFF)
			अवरोध;

		अगर ((start_addr != 0) && (efuse_addr == start_addr)) अणु
			count++;

			efuse_data = 0xFF;
			अगर (count < 4) अणु
				/*  try again! */

				अगर (count > 2) अणु
					/*  try again क्रमm address 0 */
					efuse_addr = 0;
					start_addr = 0;
				पूर्ण

				जारी;
			पूर्ण

			जाओ error;
		पूर्ण

		अगर (EXT_HEADER(efuse_data)) अणु
			hoffset = GET_HDR_OFFSET_2_0(efuse_data);
			efuse_addr++;
			efuse_OneByteRead(padapter, efuse_addr, &efuse_data, bPseuकरोTest);
			अगर (ALL_WORDS_DISABLED(efuse_data))
				जारी;

			hoffset |= ((efuse_data & 0xF0) >> 1);
			hworden = efuse_data & 0x0F;
		पूर्ण अन्यथा अणु
			hoffset = (efuse_data>>4) & 0x0F;
			hworden = efuse_data & 0x0F;
		पूर्ण

		word_cnts = Efuse_CalculateWordCnts(hworden);
		efuse_addr += (word_cnts*2)+1;
	पूर्ण

	अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
		pEfuseHal->fakeEfuseUsedBytes = efuse_addr;
#अन्यथा
		fakeEfuseUsedBytes = efuse_addr;
#पूर्ण_अगर
	पूर्ण अन्यथा
		rtw_hal_set_hwreg(padapter, HW_VAR_EFUSE_BYTES, (u8 *)&efuse_addr);

	जाओ निकास;

error:
	/*  report max size to prevent ग_लिखो efuse */
	EFUSE_GetEfuseDefinition(padapter, EFUSE_WIFI, TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, &efuse_addr, bPseuकरोTest);

निकास:

	वापस efuse_addr;
पूर्ण

अटल u16 hal_EfuseGetCurrentSize_BT(काष्ठा adapter *padapter, u8 bPseuकरोTest)
अणु
#अगर_घोषित HAL_EFUSE_MEMORY
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा efuse_hal *pEfuseHal = &pHalData->EfuseHal;
#पूर्ण_अगर
	u16 btusedbytes;
	u16 efuse_addr;
	u8 bank, startBank;
	u8 hoffset = 0, hworden = 0;
	u8 efuse_data, word_cnts = 0;
	u16 retU2 = 0;

	अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
		btusedbytes = pEfuseHal->fakeBTEfuseUsedBytes;
#अन्यथा
		btusedbytes = fakeBTEfuseUsedBytes;
#पूर्ण_अगर
	पूर्ण अन्यथा
		rtw_hal_get_hwreg(padapter, HW_VAR_EFUSE_BT_BYTES, (u8 *)&btusedbytes);

	efuse_addr = (u16)((btusedbytes%EFUSE_BT_REAL_BANK_CONTENT_LEN));
	startBank = (u8)(1+(btusedbytes/EFUSE_BT_REAL_BANK_CONTENT_LEN));

	EFUSE_GetEfuseDefinition(padapter, EFUSE_BT, TYPE_AVAILABLE_EFUSE_BYTES_BANK, &retU2, bPseuकरोTest);

	क्रम (bank = startBank; bank < 3; bank++) अणु
		अगर (hal_EfuseSwitchToBank(padapter, bank, bPseuकरोTest) == false)
			/* bank = EFUSE_MAX_BANK; */
			अवरोध;

		/*  only when bank is चयनed we have to reset the efuse_addr. */
		अगर (bank != startBank)
			efuse_addr = 0;
#अगर 1

		जबतक (AVAILABLE_EFUSE_ADDR(efuse_addr)) अणु
			अगर (efuse_OneByteRead(padapter, efuse_addr,
					      &efuse_data, bPseuकरोTest) == false)
				/* bank = EFUSE_MAX_BANK; */
				अवरोध;

			अगर (efuse_data == 0xFF)
				अवरोध;

			अगर (EXT_HEADER(efuse_data)) अणु
				hoffset = GET_HDR_OFFSET_2_0(efuse_data);
				efuse_addr++;
				efuse_OneByteRead(padapter, efuse_addr, &efuse_data, bPseuकरोTest);

				अगर (ALL_WORDS_DISABLED(efuse_data)) अणु
					efuse_addr++;
					जारी;
				पूर्ण

/* 				hoffset = ((hoffset & 0xE0) >> 5) | ((efuse_data & 0xF0) >> 1); */
				hoffset |= ((efuse_data & 0xF0) >> 1);
				hworden = efuse_data & 0x0F;
			पूर्ण अन्यथा अणु
				hoffset = (efuse_data>>4) & 0x0F;
				hworden =  efuse_data & 0x0F;
			पूर्ण

			word_cnts = Efuse_CalculateWordCnts(hworden);
			/* पढ़ो next header */
			efuse_addr += (word_cnts*2)+1;
		पूर्ण
#अन्यथा
	जबतक (
		bContinual &&
		efuse_OneByteRead(padapter, efuse_addr, &efuse_data, bPseuकरोTest) &&
		AVAILABLE_EFUSE_ADDR(efuse_addr)
	) अणु
			अगर (efuse_data != 0xFF) अणु
				अगर ((efuse_data&0x1F) == 0x0F) अणु /* extended header */
					hoffset = efuse_data;
					efuse_addr++;
					efuse_OneByteRead(padapter, efuse_addr, &efuse_data, bPseuकरोTest);
					अगर ((efuse_data & 0x0F) == 0x0F) अणु
						efuse_addr++;
						जारी;
					पूर्ण अन्यथा अणु
						hoffset = ((hoffset & 0xE0) >> 5) | ((efuse_data & 0xF0) >> 1);
						hworden = efuse_data & 0x0F;
					पूर्ण
				पूर्ण अन्यथा अणु
					hoffset = (efuse_data>>4) & 0x0F;
					hworden =  efuse_data & 0x0F;
				पूर्ण
				word_cnts = Efuse_CalculateWordCnts(hworden);
				/* पढ़ो next header */
				efuse_addr = efuse_addr + (word_cnts*2)+1;
			पूर्ण अन्यथा
				bContinual = false;
		पूर्ण
#पूर्ण_अगर


		/*  Check अगर we need to check next bank efuse */
		अगर (efuse_addr < retU2)
			अवरोध; /*  करोn't need to check next bank. */
	पूर्ण

	retU2 = ((bank-1)*EFUSE_BT_REAL_BANK_CONTENT_LEN)+efuse_addr;
	अगर (bPseuकरोTest) अणु
		pEfuseHal->fakeBTEfuseUsedBytes = retU2;
		/* RT_DISP(FEEPROM, EFUSE_PG, ("Hal_EfuseGetCurrentSize_BT92C(), already use %u bytes\n", pEfuseHal->fakeBTEfuseUsedBytes)); */
	पूर्ण अन्यथा अणु
		pEfuseHal->BTEfuseUsedBytes = retU2;
		/* RT_DISP(FEEPROM, EFUSE_PG, ("Hal_EfuseGetCurrentSize_BT92C(), already use %u bytes\n", pEfuseHal->BTEfuseUsedBytes)); */
	पूर्ण

	वापस retU2;
पूर्ण

अटल u16 Hal_EfuseGetCurrentSize(
	काष्ठा adapter *padapter, u8 efuseType, bool bPseuकरोTest
)
अणु
	u16 ret = 0;

	अगर (efuseType == EFUSE_WIFI)
		ret = hal_EfuseGetCurrentSize_WiFi(padapter, bPseuकरोTest);
	अन्यथा
		ret = hal_EfuseGetCurrentSize_BT(padapter, bPseuकरोTest);

	वापस ret;
पूर्ण

अटल u8 Hal_EfuseWordEnableDataWrite(
	काष्ठा adapter *padapter,
	u16 efuse_addr,
	u8 word_en,
	u8 *data,
	bool bPseuकरोTest
)
अणु
	u16 पंचांगpaddr = 0;
	u16 start_addr = efuse_addr;
	u8 badworden = 0x0F;
	u8 पंचांगpdata[PGPKT_DATA_SIZE];

	स_रखो(पंचांगpdata, 0xFF, PGPKT_DATA_SIZE);

	अगर (!(word_en & BIT(0))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(padapter, start_addr++, data[0], bPseuकरोTest);
		efuse_OneByteWrite(padapter, start_addr++, data[1], bPseuकरोTest);

		efuse_OneByteRead(padapter, पंचांगpaddr, &पंचांगpdata[0], bPseuकरोTest);
		efuse_OneByteRead(padapter, पंचांगpaddr+1, &पंचांगpdata[1], bPseuकरोTest);
		अगर ((data[0] != पंचांगpdata[0]) || (data[1] != पंचांगpdata[1])) अणु
			badworden &= (~BIT(0));
		पूर्ण
	पूर्ण
	अगर (!(word_en & BIT(1))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(padapter, start_addr++, data[2], bPseuकरोTest);
		efuse_OneByteWrite(padapter, start_addr++, data[3], bPseuकरोTest);

		efuse_OneByteRead(padapter, पंचांगpaddr, &पंचांगpdata[2], bPseuकरोTest);
		efuse_OneByteRead(padapter, पंचांगpaddr+1, &पंचांगpdata[3], bPseuकरोTest);
		अगर ((data[2] != पंचांगpdata[2]) || (data[3] != पंचांगpdata[3])) अणु
			badworden &= (~BIT(1));
		पूर्ण
	पूर्ण

	अगर (!(word_en & BIT(2))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(padapter, start_addr++, data[4], bPseuकरोTest);
		efuse_OneByteWrite(padapter, start_addr++, data[5], bPseuकरोTest);

		efuse_OneByteRead(padapter, पंचांगpaddr, &पंचांगpdata[4], bPseuकरोTest);
		efuse_OneByteRead(padapter, पंचांगpaddr+1, &पंचांगpdata[5], bPseuकरोTest);
		अगर ((data[4] != पंचांगpdata[4]) || (data[5] != पंचांगpdata[5])) अणु
			badworden &= (~BIT(2));
		पूर्ण
	पूर्ण

	अगर (!(word_en & BIT(3))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(padapter, start_addr++, data[6], bPseuकरोTest);
		efuse_OneByteWrite(padapter, start_addr++, data[7], bPseuकरोTest);

		efuse_OneByteRead(padapter, पंचांगpaddr, &पंचांगpdata[6], bPseuकरोTest);
		efuse_OneByteRead(padapter, पंचांगpaddr+1, &पंचांगpdata[7], bPseuकरोTest);
		अगर ((data[6] != पंचांगpdata[6]) || (data[7] != पंचांगpdata[7])) अणु
			badworden &= (~BIT(3));
		पूर्ण
	पूर्ण

	वापस badworden;
पूर्ण

अटल s32 Hal_EfusePgPacketRead(
	काष्ठा adapter *padapter,
	u8 offset,
	u8 *data,
	bool bPseuकरोTest
)
अणु
	u8 efuse_data, word_cnts = 0;
	u16 efuse_addr = 0;
	u8 hoffset = 0, hworden = 0;
	u8 i;
	u8 max_section = 0;
	s32	ret;


	अगर (!data)
		वापस false;

	EFUSE_GetEfuseDefinition(padapter, EFUSE_WIFI, TYPE_EFUSE_MAX_SECTION, &max_section, bPseuकरोTest);
	अगर (offset > max_section)
		वापस false;

	स_रखो(data, 0xFF, PGPKT_DATA_SIZE);
	ret = true;

	/*  */
	/*  <Roger_TODO> Efuse has been pre-programmed dummy 5Bytes at the end of Efuse by CP. */
	/*  Skip dummy parts to prevent unexpected data पढ़ो from Efuse. */
	/*  By pass right now. 2009.02.19. */
	/*  */
	जबतक (AVAILABLE_EFUSE_ADDR(efuse_addr)) अणु
		अगर (efuse_OneByteRead(padapter, efuse_addr++, &efuse_data, bPseuकरोTest) == false) अणु
			ret = false;
			अवरोध;
		पूर्ण

		अगर (efuse_data == 0xFF)
			अवरोध;

		अगर (EXT_HEADER(efuse_data)) अणु
			hoffset = GET_HDR_OFFSET_2_0(efuse_data);
			efuse_OneByteRead(padapter, efuse_addr++, &efuse_data, bPseuकरोTest);
			अगर (ALL_WORDS_DISABLED(efuse_data))
				जारी;

			hoffset |= ((efuse_data & 0xF0) >> 1);
			hworden = efuse_data & 0x0F;
		पूर्ण अन्यथा अणु
			hoffset = (efuse_data>>4) & 0x0F;
			hworden =  efuse_data & 0x0F;
		पूर्ण

		अगर (hoffset == offset) अणु
			क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++) अणु
				/*  Check word enable condition in the section */
				अगर (!(hworden & (0x01<<i))) अणु
					efuse_OneByteRead(padapter, efuse_addr++, &efuse_data, bPseuकरोTest);
					data[i*2] = efuse_data;

					efuse_OneByteRead(padapter, efuse_addr++, &efuse_data, bPseuकरोTest);
					data[(i*2)+1] = efuse_data;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			word_cnts = Efuse_CalculateWordCnts(hworden);
			efuse_addr += word_cnts*2;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल u8 hal_EfusePgCheckAvailableAddr(
	काष्ठा adapter *padapter, u8 efuseType, u8 bPseuकरोTest
)
अणु
	u16 max_available = 0;
	u16 current_size;


	EFUSE_GetEfuseDefinition(padapter, efuseType, TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, &max_available, bPseuकरोTest);

	current_size = Efuse_GetCurrentSize(padapter, efuseType, bPseuकरोTest);
	अगर (current_size >= max_available)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम hal_EfuseConकाष्ठाPGPkt(
	u8 offset,
	u8 word_en,
	u8 *pData,
	काष्ठा pgpkt_काष्ठा *pTargetPkt
)
अणु
	स_रखो(pTargetPkt->data, 0xFF, PGPKT_DATA_SIZE);
	pTargetPkt->offset = offset;
	pTargetPkt->word_en = word_en;
	efuse_WordEnableDataRead(word_en, pData, pTargetPkt->data);
	pTargetPkt->word_cnts = Efuse_CalculateWordCnts(pTargetPkt->word_en);
पूर्ण

अटल u8 hal_EfusePartialWriteCheck(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u16 *pAddr,
	काष्ठा pgpkt_काष्ठा *pTargetPkt,
	u8 bPseuकरोTest
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा efuse_hal *pEfuseHal = &pHalData->EfuseHal;
	u8 bRet = false;
	u16 startAddr = 0, efuse_max_available_len = 0, efuse_max = 0;
	u8 efuse_data = 0;

	EFUSE_GetEfuseDefinition(padapter, efuseType, TYPE_AVAILABLE_EFUSE_BYTES_TOTAL, &efuse_max_available_len, bPseuकरोTest);
	EFUSE_GetEfuseDefinition(padapter, efuseType, TYPE_EFUSE_CONTENT_LEN_BANK, &efuse_max, bPseuकरोTest);

	अगर (efuseType == EFUSE_WIFI) अणु
		अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
			startAddr = (u16)pEfuseHal->fakeEfuseUsedBytes;
#अन्यथा
			startAddr = (u16)fakeEfuseUsedBytes;
#पूर्ण_अगर
		पूर्ण अन्यथा
			rtw_hal_get_hwreg(padapter, HW_VAR_EFUSE_BYTES, (u8 *)&startAddr);
	पूर्ण अन्यथा अणु
		अगर (bPseuकरोTest) अणु
#अगर_घोषित HAL_EFUSE_MEMORY
			startAddr = (u16)pEfuseHal->fakeBTEfuseUsedBytes;
#अन्यथा
			startAddr = (u16)fakeBTEfuseUsedBytes;
#पूर्ण_अगर
		पूर्ण अन्यथा
			rtw_hal_get_hwreg(padapter, HW_VAR_EFUSE_BT_BYTES, (u8 *)&startAddr);
	पूर्ण
	startAddr %= efuse_max;

	जबतक (1) अणु
		अगर (startAddr >= efuse_max_available_len) अणु
			bRet = false;
			अवरोध;
		पूर्ण

		अगर (efuse_OneByteRead(padapter, startAddr, &efuse_data, bPseuकरोTest) && (efuse_data != 0xFF)) अणु
#अगर 1
			bRet = false;
			अवरोध;
#अन्यथा
			अगर (EXT_HEADER(efuse_data)) अणु
				cur_header = efuse_data;
				startAddr++;
				efuse_OneByteRead(padapter, startAddr, &efuse_data, bPseuकरोTest);
				अगर (ALL_WORDS_DISABLED(efuse_data)) अणु
					bRet = false;
					अवरोध;
				पूर्ण अन्यथा अणु
					curPkt.offset = ((cur_header & 0xE0) >> 5) | ((efuse_data & 0xF0) >> 1);
					curPkt.word_en = efuse_data & 0x0F;
				पूर्ण
			पूर्ण अन्यथा अणु
				cur_header  =  efuse_data;
				curPkt.offset = (cur_header>>4) & 0x0F;
				curPkt.word_en = cur_header & 0x0F;
			पूर्ण

			curPkt.word_cnts = Efuse_CalculateWordCnts(curPkt.word_en);
			/*  अगर same header is found but no data followed */
			/*  ग_लिखो some part of data followed by the header. */
			अगर (
				(curPkt.offset == pTargetPkt->offset) &&
				(hal_EfuseCheckIfDatafollowed(padapter, curPkt.word_cnts, startAddr+1, bPseuकरोTest) == false) &&
				wordEnMatched(pTargetPkt, &curPkt, &matched_wden) == true
			) अणु
				/*  Here to ग_लिखो partial data */
				badworden = Efuse_WordEnableDataWrite(padapter, startAddr+1, matched_wden, pTargetPkt->data, bPseuकरोTest);
				अगर (badworden != 0x0F) अणु
					u32 PgWriteSuccess = 0;
					/*  अगर ग_लिखो fail on some words, ग_लिखो these bad words again */
					अगर (efuseType == EFUSE_WIFI)
						PgWriteSuccess = Efuse_PgPacketWrite(padapter, pTargetPkt->offset, badworden, pTargetPkt->data, bPseuकरोTest);
					अन्यथा
						PgWriteSuccess = Efuse_PgPacketWrite_BT(padapter, pTargetPkt->offset, badworden, pTargetPkt->data, bPseuकरोTest);

					अगर (!PgWriteSuccess) अणु
						bRet = false;	/*  ग_लिखो fail, वापस */
						अवरोध;
					पूर्ण
				पूर्ण
				/*  partial ग_लिखो ok, update the target packet क्रम later use */
				क्रम (i = 0; i < 4; i++) अणु
					अगर ((matched_wden & (0x1<<i)) == 0) अणु /*  this word has been written */
						pTargetPkt->word_en |= (0x1<<i);	/*  disable the word */
					पूर्ण
				पूर्ण
				pTargetPkt->word_cnts = Efuse_CalculateWordCnts(pTargetPkt->word_en);
			पूर्ण
			/*  पढ़ो from next header */
			startAddr = startAddr + (curPkt.word_cnts*2) + 1;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			/*  not used header, 0xff */
			*pAddr = startAddr;
			bRet = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस bRet;
पूर्ण

अटल u8 hal_EfusePgPacketWrite1ByteHeader(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u16 *pAddr,
	काष्ठा pgpkt_काष्ठा *pTargetPkt,
	u8 bPseuकरोTest
)
अणु
	u8 pg_header = 0, पंचांगp_header = 0;
	u16 efuse_addr = *pAddr;
	u8 repeatcnt = 0;

	pg_header = ((pTargetPkt->offset << 4) & 0xf0) | pTargetPkt->word_en;

	करो अणु
		efuse_OneByteWrite(padapter, efuse_addr, pg_header, bPseuकरोTest);
		efuse_OneByteRead(padapter, efuse_addr, &पंचांगp_header, bPseuकरोTest);
		अगर (पंचांगp_header != 0xFF)
			अवरोध;
		अगर (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
			वापस false;

	पूर्ण जबतक (1);

	अगर (पंचांगp_header != pg_header)
		वापस false;

	*pAddr = efuse_addr;

	वापस true;
पूर्ण

अटल u8 hal_EfusePgPacketWrite2ByteHeader(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u16 *pAddr,
	काष्ठा pgpkt_काष्ठा *pTargetPkt,
	u8 bPseuकरोTest
)
अणु
	u16 efuse_addr, efuse_max_available_len = 0;
	u8 pg_header = 0, पंचांगp_header = 0;
	u8 repeatcnt = 0;

	EFUSE_GetEfuseDefinition(padapter, efuseType, TYPE_AVAILABLE_EFUSE_BYTES_BANK, &efuse_max_available_len, bPseuकरोTest);

	efuse_addr = *pAddr;
	अगर (efuse_addr >= efuse_max_available_len)
		वापस false;

	pg_header = ((pTargetPkt->offset & 0x07) << 5) | 0x0F;

	करो अणु
		efuse_OneByteWrite(padapter, efuse_addr, pg_header, bPseuकरोTest);
		efuse_OneByteRead(padapter, efuse_addr, &पंचांगp_header, bPseuकरोTest);
		अगर (पंचांगp_header != 0xFF)
			अवरोध;
		अगर (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
			वापस false;

	पूर्ण जबतक (1);

	अगर (पंचांगp_header != pg_header)
		वापस false;

	/*  to ग_लिखो ext_header */
	efuse_addr++;
	pg_header = ((pTargetPkt->offset & 0x78) << 1) | pTargetPkt->word_en;

	करो अणु
		efuse_OneByteWrite(padapter, efuse_addr, pg_header, bPseuकरोTest);
		efuse_OneByteRead(padapter, efuse_addr, &पंचांगp_header, bPseuकरोTest);
		अगर (पंचांगp_header != 0xFF)
			अवरोध;
		अगर (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
			वापस false;

	पूर्ण जबतक (1);

	अगर (पंचांगp_header != pg_header) /* offset PG fail */
		वापस false;

	*pAddr = efuse_addr;

	वापस true;
पूर्ण

अटल u8 hal_EfusePgPacketWriteHeader(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u16 *pAddr,
	काष्ठा pgpkt_काष्ठा *pTargetPkt,
	u8 bPseuकरोTest
)
अणु
	u8 bRet = false;

	अगर (pTargetPkt->offset >= EFUSE_MAX_SECTION_BASE)
		bRet = hal_EfusePgPacketWrite2ByteHeader(padapter, efuseType, pAddr, pTargetPkt, bPseuकरोTest);
	अन्यथा
		bRet = hal_EfusePgPacketWrite1ByteHeader(padapter, efuseType, pAddr, pTargetPkt, bPseuकरोTest);

	वापस bRet;
पूर्ण

अटल u8 hal_EfusePgPacketWriteData(
	काष्ठा adapter *padapter,
	u8 efuseType,
	u16 *pAddr,
	काष्ठा pgpkt_काष्ठा *pTargetPkt,
	u8 bPseuकरोTest
)
अणु
	u16 efuse_addr;
	u8 badworden;


	efuse_addr = *pAddr;
	badworden = Efuse_WordEnableDataWrite(padapter, efuse_addr+1, pTargetPkt->word_en, pTargetPkt->data, bPseuकरोTest);
	अगर (badworden != 0x0F)
		वापस false;

	वापस true;
पूर्ण

अटल s32 Hal_EfusePgPacketWrite(
	काष्ठा adapter *padapter,
	u8 offset,
	u8 word_en,
	u8 *pData,
	bool bPseuकरोTest
)
अणु
	काष्ठा pgpkt_काष्ठा targetPkt;
	u16 startAddr = 0;
	u8 efuseType = EFUSE_WIFI;

	अगर (!hal_EfusePgCheckAvailableAddr(padapter, efuseType, bPseuकरोTest))
		वापस false;

	hal_EfuseConकाष्ठाPGPkt(offset, word_en, pData, &targetPkt);

	अगर (!hal_EfusePartialWriteCheck(padapter, efuseType, &startAddr, &targetPkt, bPseuकरोTest))
		वापस false;

	अगर (!hal_EfusePgPacketWriteHeader(padapter, efuseType, &startAddr, &targetPkt, bPseuकरोTest))
		वापस false;

	अगर (!hal_EfusePgPacketWriteData(padapter, efuseType, &startAddr, &targetPkt, bPseuकरोTest))
		वापस false;

	वापस true;
पूर्ण

अटल bool Hal_EfusePgPacketWrite_BT(
	काष्ठा adapter *padapter,
	u8 offset,
	u8 word_en,
	u8 *pData,
	bool bPseuकरोTest
)
अणु
	काष्ठा pgpkt_काष्ठा targetPkt;
	u16 startAddr = 0;
	u8 efuseType = EFUSE_BT;

	अगर (!hal_EfusePgCheckAvailableAddr(padapter, efuseType, bPseuकरोTest))
		वापस false;

	hal_EfuseConकाष्ठाPGPkt(offset, word_en, pData, &targetPkt);

	अगर (!hal_EfusePartialWriteCheck(padapter, efuseType, &startAddr, &targetPkt, bPseuकरोTest))
		वापस false;

	अगर (!hal_EfusePgPacketWriteHeader(padapter, efuseType, &startAddr, &targetPkt, bPseuकरोTest))
		वापस false;

	अगर (!hal_EfusePgPacketWriteData(padapter, efuseType, &startAddr, &targetPkt, bPseuकरोTest))
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा hal_version ReadChipVersion8723B(काष्ठा adapter *padapter)
अणु
	u32 value32;
	काष्ठा hal_version ChipVersion;
	काष्ठा hal_com_data *pHalData;

/* YJ, TODO, move पढ़ो chip type here */
	pHalData = GET_HAL_DATA(padapter);

	value32 = rtw_पढ़ो32(padapter, REG_SYS_CFG);
	ChipVersion.ICType = CHIP_8723B;
	ChipVersion.ChipType = ((value32 & RTL_ID) ? TEST_CHIP : NORMAL_CHIP);
	ChipVersion.RFType = RF_TYPE_1T1R;
	ChipVersion.VenकरोrType = ((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : CHIP_VENDOR_TSMC);
	ChipVersion.CUTVersion = (value32 & CHIP_VER_RTL_MASK)>>CHIP_VER_RTL_SHIFT; /*  IC version (CUT) */

	/*  For regulator mode. by tynli. 2011.01.14 */
	pHalData->RegulatorMode = ((value32 & SPS_SEL) ? RT_LDO_REGULATOR : RT_SWITCHING_REGULATOR);

	value32 = rtw_पढ़ो32(padapter, REG_GPIO_OUTSTS);
	ChipVersion.ROMVer = ((value32 & RF_RL_ID) >> 20);	/*  ROM code version. */

	/*  For multi-function consideration. Added by Roger, 2010.10.06. */
	pHalData->MultiFunc = RT_MULTI_FUNC_NONE;
	value32 = rtw_पढ़ो32(padapter, REG_MULTI_FUNC_CTRL);
	pHalData->MultiFunc |= ((value32 & WL_FUNC_EN) ? RT_MULTI_FUNC_WIFI : 0);
	pHalData->MultiFunc |= ((value32 & BT_FUNC_EN) ? RT_MULTI_FUNC_BT : 0);
	pHalData->MultiFunc |= ((value32 & GPS_FUNC_EN) ? RT_MULTI_FUNC_GPS : 0);
	pHalData->PolarityCtl = ((value32 & WL_HWPDN_SL) ? RT_POLARITY_HIGH_ACT : RT_POLARITY_LOW_ACT);
#अगर 1
	dump_chip_info(ChipVersion);
#पूर्ण_अगर
	pHalData->VersionID = ChipVersion;
	अगर (IS_1T2R(ChipVersion))
		pHalData->rf_type = RF_1T2R;
	अन्यथा अगर (IS_2T2R(ChipVersion))
		pHalData->rf_type = RF_2T2R;
	अन्यथा
		pHalData->rf_type = RF_1T1R;

	वापस ChipVersion;
पूर्ण

अटल व्योम rtl8723b_पढ़ो_chip_version(काष्ठा adapter *padapter)
अणु
	ReadChipVersion8723B(padapter);
पूर्ण

व्योम rtl8723b_InitBeaconParameters(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u16 val16;
	u8 val8;


	val8 = DIS_TSF_UDT;
	val16 = val8 | (val8 << 8); /*  port0 and port1 */

	/*  Enable prot0 beacon function क्रम PSTDMA */
	val16 |= EN_BCN_FUNCTION;

	rtw_ग_लिखो16(padapter, REG_BCN_CTRL, val16);

	/*  TODO: Remove these magic number */
	rtw_ग_लिखो16(padapter, REG_TBTT_PROHIBIT, 0x6404);/*  ms */
	/*  Firmware will control REG_DRVERLYINT when घातer saving is enable, */
	/*  so करोn't set this रेजिस्टर on STA mode. */
	अगर (check_fwstate(&padapter->mlmepriv, WIFI_STATION_STATE) == false)
		rtw_ग_लिखो8(padapter, REG_DRVERLYINT, DRIVER_EARLY_INT_TIME_8723B); /*  5ms */
	rtw_ग_लिखो8(padapter, REG_BCNDMATIM, BCN_DMA_ATIME_INT_TIME_8723B); /*  2ms */

	/*  Suggested by designer timchen. Change beacon AIFS to the largest number */
	/*  beacause test chip करोes not contension beक्रमe sending beacon. by tynli. 2009.11.03 */
	rtw_ग_लिखो16(padapter, REG_BCNTCFG, 0x660F);

	pHalData->RegBcnCtrlVal = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
	pHalData->RegTxPause = rtw_पढ़ो8(padapter, REG_TXPAUSE);
	pHalData->RegFwHwTxQCtrl = rtw_पढ़ो8(padapter, REG_FWHW_TXQ_CTRL+2);
	pHalData->RegReg542 = rtw_पढ़ो8(padapter, REG_TBTT_PROHIBIT+2);
	pHalData->RegCR_1 = rtw_पढ़ो8(padapter, REG_CR+1);
पूर्ण

व्योम _InitBurstPktLen_8723BS(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	rtw_ग_लिखो8(Adapter, 0x4c7, rtw_पढ़ो8(Adapter, 0x4c7)|BIT(7)); /* enable single pkt ampdu */
	rtw_ग_लिखो8(Adapter, REG_RX_PKT_LIMIT_8723B, 0x18);		/* क्रम VHT packet length 11K */
	rtw_ग_लिखो8(Adapter, REG_MAX_AGGR_NUM_8723B, 0x1F);
	rtw_ग_लिखो8(Adapter, REG_PIFS_8723B, 0x00);
	rtw_ग_लिखो8(Adapter, REG_FWHW_TXQ_CTRL_8723B, rtw_पढ़ो8(Adapter, REG_FWHW_TXQ_CTRL)&(~BIT(7)));
	अगर (pHalData->AMPDUBurstMode)
		rtw_ग_लिखो8(Adapter, REG_AMPDU_BURST_MODE_8723B,  0x5F);
	rtw_ग_लिखो8(Adapter, REG_AMPDU_MAX_TIME_8723B, 0x70);

	/*  ARFB table 9 क्रम 11ac 5G 2SS */
	rtw_ग_लिखो32(Adapter, REG_ARFR0_8723B, 0x00000010);
	अगर (IS_NORMAL_CHIP(pHalData->VersionID))
		rtw_ग_लिखो32(Adapter, REG_ARFR0_8723B+4, 0xfffff000);
	अन्यथा
		rtw_ग_लिखो32(Adapter, REG_ARFR0_8723B+4, 0x3e0ff000);

	/*  ARFB table 10 क्रम 11ac 5G 1SS */
	rtw_ग_लिखो32(Adapter, REG_ARFR1_8723B, 0x00000010);
	rtw_ग_लिखो32(Adapter, REG_ARFR1_8723B+4, 0x003ff000);
पूर्ण

अटल व्योम ResumeTxBeacon(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	pHalData->RegFwHwTxQCtrl |= BIT(6);
	rtw_ग_लिखो8(padapter, REG_FWHW_TXQ_CTRL+2, pHalData->RegFwHwTxQCtrl);
	rtw_ग_लिखो8(padapter, REG_TBTT_PROHIBIT+1, 0xff);
	pHalData->RegReg542 |= BIT(0);
	rtw_ग_लिखो8(padapter, REG_TBTT_PROHIBIT+2, pHalData->RegReg542);
पूर्ण

अटल व्योम StopTxBeacon(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	pHalData->RegFwHwTxQCtrl &= ~BIT(6);
	rtw_ग_लिखो8(padapter, REG_FWHW_TXQ_CTRL+2, pHalData->RegFwHwTxQCtrl);
	rtw_ग_लिखो8(padapter, REG_TBTT_PROHIBIT+1, 0x64);
	pHalData->RegReg542 &= ~BIT(0);
	rtw_ग_लिखो8(padapter, REG_TBTT_PROHIBIT+2, pHalData->RegReg542);

	CheckFwRsvdPageContent(padapter);  /*  2010.06.23. Added by tynli. */
पूर्ण

अटल व्योम _BeaconFunctionEnable(काष्ठा adapter *padapter, u8 Enable, u8 Linked)
अणु
	rtw_ग_लिखो8(padapter, REG_BCN_CTRL, DIS_TSF_UDT | EN_BCN_FUNCTION | DIS_BCNQ_SUB);
	rtw_ग_लिखो8(padapter, REG_RD_CTRL+1, 0x6F);
पूर्ण

अटल व्योम rtl8723b_SetBeaconRelatedRegisters(काष्ठा adapter *padapter)
अणु
	u8 val8;
	u32 value32;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u32 bcn_ctrl_reg;

	/* reset TSF, enable update TSF, correcting TSF On Beacon */

	/* REG_BCN_INTERVAL */
	/* REG_BCNDMATIM */
	/* REG_ATIMWND */
	/* REG_TBTT_PROHIBIT */
	/* REG_DRVERLYINT */
	/* REG_BCN_MAX_ERR */
	/* REG_BCNTCFG (0x510) */
	/* REG_DUAL_TSF_RST */
	/* REG_BCN_CTRL (0x550) */


	bcn_ctrl_reg = REG_BCN_CTRL;

	/*  */
	/*  ATIM winकरोw */
	/*  */
	rtw_ग_लिखो16(padapter, REG_ATIMWND, 2);

	/*  */
	/*  Beacon पूर्णांकerval (in unit of TU). */
	/*  */
	rtw_ग_लिखो16(padapter, REG_BCN_INTERVAL, pmlmeinfo->bcn_पूर्णांकerval);

	rtl8723b_InitBeaconParameters(padapter);

	rtw_ग_लिखो8(padapter, REG_SLOT, 0x09);

	/*  */
	/*  Reset TSF Timer to zero, added by Roger. 2008.06.24 */
	/*  */
	value32 = rtw_पढ़ो32(padapter, REG_TCR);
	value32 &= ~TSFRST;
	rtw_ग_लिखो32(padapter, REG_TCR, value32);

	value32 |= TSFRST;
	rtw_ग_लिखो32(padapter, REG_TCR, value32);

	/*  NOTE: Fix test chip's bug (about contention windows's अक्रमomness) */
	अगर (check_fwstate(&padapter->mlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE|WIFI_AP_STATE) == true) अणु
		rtw_ग_लिखो8(padapter, REG_RXTSF_OFFSET_CCK, 0x50);
		rtw_ग_लिखो8(padapter, REG_RXTSF_OFFSET_OFDM, 0x50);
	पूर्ण

	_BeaconFunctionEnable(padapter, true, true);

	ResumeTxBeacon(padapter);
	val8 = rtw_पढ़ो8(padapter, bcn_ctrl_reg);
	val8 |= DIS_BCNQ_SUB;
	rtw_ग_लिखो8(padapter, bcn_ctrl_reg, val8);
पूर्ण

अटल व्योम rtl8723b_GetHalODMVar(
	काष्ठा adapter *Adapter,
	क्रमागत hal_odm_variable eVariable,
	व्योम *pValue1,
	व्योम *pValue2
)
अणु
	GetHalODMVar(Adapter, eVariable, pValue1, pValue2);
पूर्ण

अटल व्योम rtl8723b_SetHalODMVar(
	काष्ठा adapter *Adapter,
	क्रमागत hal_odm_variable eVariable,
	व्योम *pValue1,
	bool bSet
)
अणु
	SetHalODMVar(Adapter, eVariable, pValue1, bSet);
पूर्ण

अटल व्योम hal_notch_filter_8723b(काष्ठा adapter *adapter, bool enable)
अणु
	अगर (enable)
		rtw_ग_लिखो8(adapter, rOFDM0_RxDSP+1, rtw_पढ़ो8(adapter, rOFDM0_RxDSP+1) | BIT1);
	अन्यथा
		rtw_ग_लिखो8(adapter, rOFDM0_RxDSP+1, rtw_पढ़ो8(adapter, rOFDM0_RxDSP+1) & ~BIT1);
पूर्ण

अटल व्योम UpdateHalRAMask8723B(काष्ठा adapter *padapter, u32 mac_id, u8 rssi_level)
अणु
	u32 mask, rate_biपंचांगap;
	u8 लघुGIrate = false;
	काष्ठा sta_info *psta;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_priv *pdmpriv = &pHalData->dmpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	अगर (mac_id >= NUM_STA) /* CAM_SIZE */
		वापस;

	psta = pmlmeinfo->FW_sta_info[mac_id].psta;
	अगर (!psta)
		वापस;

	लघुGIrate = query_ra_लघु_GI(psta);

	mask = psta->ra_mask;

	rate_biपंचांगap = 0xffffffff;
	rate_biपंचांगap = ODM_Get_Rate_Biपंचांगap(&pHalData->odmpriv, mac_id, mask, rssi_level);

	mask &= rate_biपंचांगap;

	rate_biपंचांगap = hal_btcoex_GetRaMask(padapter);
	mask &= ~rate_biपंचांगap;

	अगर (pHalData->fw_ractrl) अणु
		rtl8723b_set_FwMacIdConfig_cmd(padapter, mac_id, psta->raid, psta->bw_mode, लघुGIrate, mask);
	पूर्ण

	/* set correct initial date rate क्रम each mac_id */
	pdmpriv->INIDATA_RATE[mac_id] = psta->init_rate;
पूर्ण


व्योम rtl8723b_set_hal_ops(काष्ठा hal_ops *pHalFunc)
अणु
	pHalFunc->मुक्त_hal_data = &rtl8723b_मुक्त_hal_data;

	pHalFunc->dm_init = &rtl8723b_init_dm_priv;

	pHalFunc->पढ़ो_chip_version = &rtl8723b_पढ़ो_chip_version;

	pHalFunc->UpdateRAMaskHandler = &UpdateHalRAMask8723B;

	pHalFunc->set_bwmode_handler = &PHY_SetBWMode8723B;
	pHalFunc->set_channel_handler = &PHY_SwChnl8723B;
	pHalFunc->set_chnl_bw_handler = &PHY_SetSwChnlBWMode8723B;

	pHalFunc->set_tx_घातer_level_handler = &PHY_SetTxPowerLevel8723B;
	pHalFunc->get_tx_घातer_level_handler = &PHY_GetTxPowerLevel8723B;

	pHalFunc->hal_dm_watchकरोg = &rtl8723b_HalDmWatchDog;
	pHalFunc->hal_dm_watchकरोg_in_lps = &rtl8723b_HalDmWatchDog_in_LPS;


	pHalFunc->SetBeaconRelatedRegistersHandler = &rtl8723b_SetBeaconRelatedRegisters;

	pHalFunc->Add_RateATid = &rtl8723b_Add_RateATid;

	pHalFunc->run_thपढ़ो = &rtl8723b_start_thपढ़ो;
	pHalFunc->cancel_thपढ़ो = &rtl8723b_stop_thपढ़ो;

	pHalFunc->पढ़ो_bbreg = &PHY_QueryBBReg_8723B;
	pHalFunc->ग_लिखो_bbreg = &PHY_SetBBReg_8723B;
	pHalFunc->पढ़ो_rfreg = &PHY_QueryRFReg_8723B;
	pHalFunc->ग_लिखो_rfreg = &PHY_SetRFReg_8723B;

	/*  Efuse related function */
	pHalFunc->BTEfusePowerSwitch = &Hal_BT_EfusePowerSwitch;
	pHalFunc->EfusePowerSwitch = &Hal_EfusePowerSwitch;
	pHalFunc->ReadEFuse = &Hal_ReadEFuse;
	pHalFunc->EFUSEGetEfuseDefinition = &Hal_GetEfuseDefinition;
	pHalFunc->EfuseGetCurrentSize = &Hal_EfuseGetCurrentSize;
	pHalFunc->Efuse_PgPacketRead = &Hal_EfusePgPacketRead;
	pHalFunc->Efuse_PgPacketWrite = &Hal_EfusePgPacketWrite;
	pHalFunc->Efuse_WordEnableDataWrite = &Hal_EfuseWordEnableDataWrite;
	pHalFunc->Efuse_PgPacketWrite_BT = &Hal_EfusePgPacketWrite_BT;

	pHalFunc->GetHalODMVarHandler = &rtl8723b_GetHalODMVar;
	pHalFunc->SetHalODMVarHandler = &rtl8723b_SetHalODMVar;

	pHalFunc->xmit_thपढ़ो_handler = &hal_xmit_handler;
	pHalFunc->hal_notch_filter = &hal_notch_filter_8723b;

	pHalFunc->c2h_handler = c2h_handler_8723b;
	pHalFunc->c2h_id_filter_ccx = c2h_id_filter_ccx_8723b;

	pHalFunc->fill_h2c_cmd = &FillH2CCmd8723B;
पूर्ण

व्योम rtl8723b_InitAntenna_Selection(काष्ठा adapter *padapter)
अणु
	u8 val;

	val = rtw_पढ़ो8(padapter, REG_LEDCFG2);
	/*  Let 8051 take control antenna setting */
	val |= BIT(7); /*  DPDT_SEL_EN, 0x4C[23] */
	rtw_ग_लिखो8(padapter, REG_LEDCFG2, val);
पूर्ण

व्योम rtl8723b_init_शेष_value(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData;
	काष्ठा dm_priv *pdmpriv;
	u8 i;


	pHalData = GET_HAL_DATA(padapter);
	pdmpriv = &pHalData->dmpriv;

	padapter->registrypriv.wireless_mode = WIRELESS_11BG_24N;

	/*  init शेष value */
	pHalData->fw_ractrl = false;
	pHalData->bIQKInitialized = false;
	अगर (!adapter_to_pwrctl(padapter)->bkeepfwalive)
		pHalData->LastHMEBoxNum = 0;

	pHalData->bIQKInitialized = false;

	/*  init dm शेष value */
	pdmpriv->TM_Trigger = 0;/* क्रम IQK */
/* 	pdmpriv->binitialized = false; */
/* 	pdmpriv->prv_traffic_idx = 3; */
/* 	pdmpriv->initialize = 0; */

	pdmpriv->ThermalValue_HP_index = 0;
	क्रम (i = 0; i < HP_THERMAL_NUM; i++)
		pdmpriv->ThermalValue_HP[i] = 0;

	/*  init Efuse variables */
	pHalData->EfuseUsedBytes = 0;
	pHalData->EfuseUsedPercentage = 0;
#अगर_घोषित HAL_EFUSE_MEMORY
	pHalData->EfuseHal.fakeEfuseBank = 0;
	pHalData->EfuseHal.fakeEfuseUsedBytes = 0;
	स_रखो(pHalData->EfuseHal.fakeEfuseContent, 0xFF, EFUSE_MAX_HW_SIZE);
	स_रखो(pHalData->EfuseHal.fakeEfuseInitMap, 0xFF, EFUSE_MAX_MAP_LEN);
	स_रखो(pHalData->EfuseHal.fakeEfuseModअगरiedMap, 0xFF, EFUSE_MAX_MAP_LEN);
	pHalData->EfuseHal.BTEfuseUsedBytes = 0;
	pHalData->EfuseHal.BTEfuseUsedPercentage = 0;
	स_रखो(pHalData->EfuseHal.BTEfuseContent, 0xFF, EFUSE_MAX_BT_BANK*EFUSE_MAX_HW_SIZE);
	स_रखो(pHalData->EfuseHal.BTEfuseInitMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
	स_रखो(pHalData->EfuseHal.BTEfuseModअगरiedMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
	pHalData->EfuseHal.fakeBTEfuseUsedBytes = 0;
	स_रखो(pHalData->EfuseHal.fakeBTEfuseContent, 0xFF, EFUSE_MAX_BT_BANK*EFUSE_MAX_HW_SIZE);
	स_रखो(pHalData->EfuseHal.fakeBTEfuseInitMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
	स_रखो(pHalData->EfuseHal.fakeBTEfuseModअगरiedMap, 0xFF, EFUSE_BT_MAX_MAP_LEN);
#पूर्ण_अगर
पूर्ण

u8 GetEEPROMSize8723B(काष्ठा adapter *padapter)
अणु
	u8 size = 0;
	u32 cr;

	cr = rtw_पढ़ो16(padapter, REG_9346CR);
	/*  6: EEPROM used is 93C46, 4: boot from E-Fuse. */
	size = (cr & BOOT_FROM_EEPROM) ? 6 : 4;

	वापस size;
पूर्ण

/*  */
/*  */
/*  LLT R/W/Init function */
/*  */
/*  */
s32 rtl8723b_InitLLTTable(काष्ठा adapter *padapter)
अणु
	अचिन्हित दीर्घ start, passing_समय;
	u32 val32;
	s32 ret;


	ret = _FAIL;

	val32 = rtw_पढ़ो32(padapter, REG_AUTO_LLT);
	val32 |= BIT_AUTO_INIT_LLT;
	rtw_ग_लिखो32(padapter, REG_AUTO_LLT, val32);

	start = jअगरfies;

	करो अणु
		val32 = rtw_पढ़ो32(padapter, REG_AUTO_LLT);
		अगर (!(val32 & BIT_AUTO_INIT_LLT)) अणु
			ret = _SUCCESS;
			अवरोध;
		पूर्ण

		passing_समय = jअगरfies_to_msecs(jअगरfies - start);
		अगर (passing_समय > 1000)
			अवरोध;

		msleep(1);
	पूर्ण जबतक (1);

	वापस ret;
पूर्ण

अटल bool Hal_GetChnlGroup8723B(u8 Channel, u8 *pGroup)
अणु
	bool bIn24G = true;

	अगर (Channel <= 14) अणु
		bIn24G = true;

		अगर (1  <= Channel && Channel <= 2)
			*pGroup = 0;
		अन्यथा अगर (3  <= Channel && Channel <= 5)
			*pGroup = 1;
		अन्यथा अगर (6  <= Channel && Channel <= 8)
			*pGroup = 2;
		अन्यथा अगर (9  <= Channel && Channel <= 11)
			*pGroup = 3;
		अन्यथा अगर (12 <= Channel && Channel <= 14)
			*pGroup = 4;
	पूर्ण अन्यथा अणु
		bIn24G = false;

		अगर (36   <= Channel && Channel <=  42)
			*pGroup = 0;
		अन्यथा अगर (44   <= Channel && Channel <=  48)
			*pGroup = 1;
		अन्यथा अगर (50   <= Channel && Channel <=  58)
			*pGroup = 2;
		अन्यथा अगर (60   <= Channel && Channel <=  64)
			*pGroup = 3;
		अन्यथा अगर (100  <= Channel && Channel <= 106)
			*pGroup = 4;
		अन्यथा अगर (108  <= Channel && Channel <= 114)
			*pGroup = 5;
		अन्यथा अगर (116  <= Channel && Channel <= 122)
			*pGroup = 6;
		अन्यथा अगर (124  <= Channel && Channel <= 130)
			*pGroup = 7;
		अन्यथा अगर (132  <= Channel && Channel <= 138)
			*pGroup = 8;
		अन्यथा अगर (140  <= Channel && Channel <= 144)
			*pGroup = 9;
		अन्यथा अगर (149  <= Channel && Channel <= 155)
			*pGroup = 10;
		अन्यथा अगर (157  <= Channel && Channel <= 161)
			*pGroup = 11;
		अन्यथा अगर (165  <= Channel && Channel <= 171)
			*pGroup = 12;
		अन्यथा अगर (173  <= Channel && Channel <= 177)
			*pGroup = 13;
	पूर्ण
	वापस bIn24G;
पूर्ण

व्योम Hal_InitPGData(काष्ठा adapter *padapter, u8 *PROMContent)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	अगर (!pEEPROM->bस्वतःload_fail_flag) अणु /*  स्वतःload OK. */
		अगर (!pEEPROM->EepromOrEfuse) अणु
			/*  Read EFUSE real map to shaकरोw. */
			EFUSE_ShaकरोwMapUpdate(padapter, EFUSE_WIFI, false);
			स_नकल((व्योम *)PROMContent, (व्योम *)pEEPROM->efuse_eeprom_data, HWSET_MAX_SIZE_8723B);
		पूर्ण
	पूर्ण अन्यथा अणु/* स्वतःload fail */
		अगर (!pEEPROM->EepromOrEfuse)
			EFUSE_ShaकरोwMapUpdate(padapter, EFUSE_WIFI, false);
		स_नकल((व्योम *)PROMContent, (व्योम *)pEEPROM->efuse_eeprom_data, HWSET_MAX_SIZE_8723B);
	पूर्ण
पूर्ण

व्योम Hal_EfuseParseIDCode(काष्ठा adapter *padapter, u8 *hwinfo)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);
/* 	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter); */
	u16 EEPROMId;


	/*  Checl 0x8129 again क्रम making sure स्वतःload status!! */
	EEPROMId = le16_to_cpu(*((__le16 *)hwinfo));
	अगर (EEPROMId != RTL_EEPROM_ID) अणु
		pEEPROM->bस्वतःload_fail_flag = true;
	पूर्ण अन्यथा
		pEEPROM->bस्वतःload_fail_flag = false;
पूर्ण

अटल व्योम Hal_ReadPowerValueFromPROM_8723B(
	काष्ठा adapter *Adapter,
	काष्ठा TxPowerInfo24G *pwrInfo24G,
	u8 *PROMContent,
	bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	u32 rfPath, eeAddr = EEPROM_TX_PWR_INX_8723B, group, TxCount = 0;

	स_रखो(pwrInfo24G, 0, माप(काष्ठा TxPowerInfo24G));

	अगर (0xFF == PROMContent[eeAddr+1])
		AutoLoadFail = true;

	अगर (AutoLoadFail) अणु
		क्रम (rfPath = 0; rfPath < MAX_RF_PATH; rfPath++) अणु
			/* 2.4G शेष value */
			क्रम (group = 0; group < MAX_CHNL_GROUP_24G; group++) अणु
				pwrInfo24G->IndexCCK_Base[rfPath][group] = EEPROM_DEFAULT_24G_INDEX;
				pwrInfo24G->IndexBW40_Base[rfPath][group] = EEPROM_DEFAULT_24G_INDEX;
			पूर्ण

			क्रम (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) अणु
				अगर (TxCount == 0) अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][0] = EEPROM_DEFAULT_24G_HT20_DIFF;
					pwrInfo24G->OFDM_Dअगरf[rfPath][0] = EEPROM_DEFAULT_24G_OFDM_DIFF;
				पूर्ण अन्यथा अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
					pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
					pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				पूर्ण
			पूर्ण
		पूर्ण

		वापस;
	पूर्ण

	pHalData->bTXPowerDataReadFromEEPORM = true;		/* YJ, move, 120316 */

	क्रम (rfPath = 0; rfPath < MAX_RF_PATH; rfPath++) अणु
		/* 2 2.4G शेष value */
		क्रम (group = 0; group < MAX_CHNL_GROUP_24G; group++) अणु
			pwrInfo24G->IndexCCK_Base[rfPath][group] =	PROMContent[eeAddr++];
			अगर (pwrInfo24G->IndexCCK_Base[rfPath][group] == 0xFF)
				pwrInfo24G->IndexCCK_Base[rfPath][group] = EEPROM_DEFAULT_24G_INDEX;
		पूर्ण

		क्रम (group = 0; group < MAX_CHNL_GROUP_24G-1; group++) अणु
			pwrInfo24G->IndexBW40_Base[rfPath][group] =	PROMContent[eeAddr++];
			अगर (pwrInfo24G->IndexBW40_Base[rfPath][group] == 0xFF)
				pwrInfo24G->IndexBW40_Base[rfPath][group] =	EEPROM_DEFAULT_24G_INDEX;
		पूर्ण

		क्रम (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) अणु
			अगर (TxCount == 0) अणु
				pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] = 0;
				अगर (PROMContent[eeAddr] == 0xFF)
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] =	EEPROM_DEFAULT_24G_HT20_DIFF;
				अन्यथा अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] =	(PROMContent[eeAddr]&0xf0)>>4;
					अगर (pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] & BIT3)		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण

				अगर (PROMContent[eeAddr] == 0xFF)
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_24G_OFDM_DIFF;
				अन्यथा अणु
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] = (PROMContent[eeAddr]&0x0f);
					अगर (pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] & BIT3)		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण
				pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] = 0;
				eeAddr++;
			पूर्ण अन्यथा अणु
				अगर (PROMContent[eeAddr] == 0xFF)
					pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				अन्यथा अणु
					pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] = (PROMContent[eeAddr]&0xf0)>>4;
					अगर (pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] & BIT3)		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW40_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण

				अगर (PROMContent[eeAddr] == 0xFF)
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				अन्यथा अणु
					pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] = (PROMContent[eeAddr]&0x0f);
					अगर (pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] & BIT3)		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->BW20_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण
				eeAddr++;

				अगर (PROMContent[eeAddr] == 0xFF)
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				अन्यथा अणु
					pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] = (PROMContent[eeAddr]&0xf0)>>4;
					अगर (pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] & BIT3)		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->OFDM_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण

				अगर (PROMContent[eeAddr] == 0xFF)
					pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] = EEPROM_DEFAULT_DIFF;
				अन्यथा अणु
					pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] = (PROMContent[eeAddr]&0x0f);
					अगर (pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] & BIT3)		/* 4bit sign number to 8 bit sign number */
						pwrInfo24G->CCK_Dअगरf[rfPath][TxCount] |= 0xF0;
				पूर्ण
				eeAddr++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


व्योम Hal_EfuseParseTxPowerInfo_8723B(
	काष्ठा adapter *padapter, u8 *PROMContent, bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा TxPowerInfo24G	pwrInfo24G;
	u8 	rfPath, ch, TxCount = 1;

	Hal_ReadPowerValueFromPROM_8723B(padapter, &pwrInfo24G, PROMContent, AutoLoadFail);
	क्रम (rfPath = 0 ; rfPath < MAX_RF_PATH ; rfPath++) अणु
		क्रम (ch = 0 ; ch < CHANNEL_MAX_NUMBER; ch++) अणु
			u8 group = 0;

			Hal_GetChnlGroup8723B(ch+1, &group);

			अगर (ch == 14-1) अणु
				pHalData->Index24G_CCK_Base[rfPath][ch] = pwrInfo24G.IndexCCK_Base[rfPath][5];
				pHalData->Index24G_BW40_Base[rfPath][ch] = pwrInfo24G.IndexBW40_Base[rfPath][group];
			पूर्ण अन्यथा अणु
				pHalData->Index24G_CCK_Base[rfPath][ch] = pwrInfo24G.IndexCCK_Base[rfPath][group];
				pHalData->Index24G_BW40_Base[rfPath][ch] = pwrInfo24G.IndexBW40_Base[rfPath][group];
			पूर्ण
		पूर्ण

		क्रम (TxCount = 0; TxCount < MAX_TX_COUNT; TxCount++) अणु
			pHalData->CCK_24G_Dअगरf[rfPath][TxCount] = pwrInfo24G.CCK_Dअगरf[rfPath][TxCount];
			pHalData->OFDM_24G_Dअगरf[rfPath][TxCount] = pwrInfo24G.OFDM_Dअगरf[rfPath][TxCount];
			pHalData->BW20_24G_Dअगरf[rfPath][TxCount] = pwrInfo24G.BW20_Dअगरf[rfPath][TxCount];
			pHalData->BW40_24G_Dअगरf[rfPath][TxCount] = pwrInfo24G.BW40_Dअगरf[rfPath][TxCount];
		पूर्ण
	पूर्ण

	/*  2010/10/19 MH Add Regulator recognize क्रम CU. */
	अगर (!AutoLoadFail) अणु
		pHalData->EEPROMRegulatory = (PROMContent[EEPROM_RF_BOARD_OPTION_8723B]&0x7);	/* bit0~2 */
		अगर (PROMContent[EEPROM_RF_BOARD_OPTION_8723B] == 0xFF)
			pHalData->EEPROMRegulatory = (EEPROM_DEFAULT_BOARD_OPTION&0x7);	/* bit0~2 */
	पूर्ण अन्यथा
		pHalData->EEPROMRegulatory = 0;
पूर्ण

व्योम Hal_EfuseParseBTCoexistInfo_8723B(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 tempval;
	u32 पंचांगpu4;

	अगर (!AutoLoadFail) अणु
		पंचांगpu4 = rtw_पढ़ो32(padapter, REG_MULTI_FUNC_CTRL);
		अगर (पंचांगpu4 & BT_FUNC_EN)
			pHalData->EEPROMBluetoothCoexist = true;
		अन्यथा
			pHalData->EEPROMBluetoothCoexist = false;

		pHalData->EEPROMBluetoothType = BT_RTL8723B;

		tempval = hwinfo[EEPROM_RF_BT_SETTING_8723B];
		अगर (tempval != 0xFF) अणु
			pHalData->EEPROMBluetoothAntNum = tempval & BIT(0);
			/*  EFUSE_0xC3[6] == 0, S1(Main)-ODM_RF_PATH_A; */
			/*  EFUSE_0xC3[6] == 1, S0(Aux)-ODM_RF_PATH_B */
			pHalData->ant_path = (tempval & BIT(6))?ODM_RF_PATH_B:ODM_RF_PATH_A;
		पूर्ण अन्यथा अणु
			pHalData->EEPROMBluetoothAntNum = Ant_x1;
			अगर (pHalData->PackageType == PACKAGE_QFN68)
				pHalData->ant_path = ODM_RF_PATH_B;
			अन्यथा
				pHalData->ant_path = ODM_RF_PATH_A;
		पूर्ण
	पूर्ण अन्यथा अणु
		pHalData->EEPROMBluetoothCoexist = false;
		pHalData->EEPROMBluetoothType = BT_RTL8723B;
		pHalData->EEPROMBluetoothAntNum = Ant_x1;
		pHalData->ant_path = ODM_RF_PATH_A;
	पूर्ण

	अगर (padapter->registrypriv.ant_num > 0) अणु
		चयन (padapter->registrypriv.ant_num) अणु
		हाल 1:
			pHalData->EEPROMBluetoothAntNum = Ant_x1;
			अवरोध;
		हाल 2:
			pHalData->EEPROMBluetoothAntNum = Ant_x2;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	hal_btcoex_SetBTCoexist(padapter, pHalData->EEPROMBluetoothCoexist);
	hal_btcoex_SetChipType(padapter, pHalData->EEPROMBluetoothType);
	hal_btcoex_SetPgAntNum(padapter, pHalData->EEPROMBluetoothAntNum == Ant_x2 ? 2 : 1);
	अगर (pHalData->EEPROMBluetoothAntNum == Ant_x1)
		hal_btcoex_SetSingleAntPath(padapter, pHalData->ant_path);
पूर्ण

व्योम Hal_EfuseParseEEPROMVer_8723B(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	अगर (!AutoLoadFail)
		pHalData->EEPROMVersion = hwinfo[EEPROM_VERSION_8723B];
	अन्यथा
		pHalData->EEPROMVersion = 1;
पूर्ण



व्योम Hal_EfuseParsePackageType_8723B(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 package;
	u8 efuseContent;

	Efuse_PowerSwitch(padapter, false, true);
	efuse_OneByteRead(padapter, 0x1FB, &efuseContent, false);
	Efuse_PowerSwitch(padapter, false, false);

	package = efuseContent & 0x7;
	चयन (package) अणु
	हाल 0x4:
		pHalData->PackageType = PACKAGE_TFBGA79;
		अवरोध;
	हाल 0x5:
		pHalData->PackageType = PACKAGE_TFBGA90;
		अवरोध;
	हाल 0x6:
		pHalData->PackageType = PACKAGE_QFN68;
		अवरोध;
	हाल 0x7:
		pHalData->PackageType = PACKAGE_TFBGA80;
		अवरोध;

	शेष:
		pHalData->PackageType = PACKAGE_DEFAULT;
		अवरोध;
	पूर्ण
पूर्ण


व्योम Hal_EfuseParseVoltage_8723B(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	/* स_नकल(pEEPROM->adjuseVoltageVal, &hwinfo[EEPROM_Voltage_ADDR_8723B], 1); */
	pEEPROM->adjuseVoltageVal = (hwinfo[EEPROM_Voltage_ADDR_8723B] & 0xf0) >> 4;
पूर्ण

व्योम Hal_EfuseParseChnlPlan_8723B(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	padapter->mlmepriv.ChannelPlan = hal_com_config_channel_plan(
		padapter,
		hwinfo ? hwinfo[EEPROM_ChannelPlan_8723B] : 0xFF,
		padapter->registrypriv.channel_plan,
		RT_CHANNEL_DOMAIN_WORLD_शून्य,
		AutoLoadFail
	);

	Hal_ChannelPlanToRegulation(padapter, padapter->mlmepriv.ChannelPlan);
पूर्ण

व्योम Hal_EfuseParseCustomerID_8723B(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	अगर (!AutoLoadFail)
		pHalData->EEPROMCustomerID = hwinfo[EEPROM_CustomID_8723B];
	अन्यथा
		pHalData->EEPROMCustomerID = 0;
पूर्ण

व्योम Hal_EfuseParseAntennaDiversity_8723B(
	काष्ठा adapter *padapter,
	u8 *hwinfo,
	bool AutoLoadFail
)
अणु
पूर्ण

व्योम Hal_EfuseParseXtal_8723B(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	अगर (!AutoLoadFail) अणु
		pHalData->CrystalCap = hwinfo[EEPROM_XTAL_8723B];
		अगर (pHalData->CrystalCap == 0xFF)
			pHalData->CrystalCap = EEPROM_Default_CrystalCap_8723B;	   /* what value should 8812 set? */
	पूर्ण अन्यथा
		pHalData->CrystalCap = EEPROM_Default_CrystalCap_8723B;
पूर्ण


व्योम Hal_EfuseParseThermalMeter_8723B(
	काष्ठा adapter *padapter, u8 *PROMContent, u8 AutoLoadFail
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	/*  */
	/*  ThermalMeter from EEPROM */
	/*  */
	अगर (!AutoLoadFail)
		pHalData->EEPROMThermalMeter = PROMContent[EEPROM_THERMAL_METER_8723B];
	अन्यथा
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_8723B;

	अगर ((pHalData->EEPROMThermalMeter == 0xff) || AutoLoadFail) अणु
		pHalData->bAPKThermalMeterIgnore = true;
		pHalData->EEPROMThermalMeter = EEPROM_Default_ThermalMeter_8723B;
	पूर्ण
पूर्ण


व्योम Hal_ReadRFGainOffset(
	काष्ठा adapter *Adapter, u8 *PROMContent, bool AutoloadFail
)
अणु
	/*  */
	/*  BB_RF Gain Offset from EEPROM */
	/*  */

	अगर (!AutoloadFail) अणु
		Adapter->eeprompriv.EEPROMRFGainOffset = PROMContent[EEPROM_RF_GAIN_OFFSET];
		Adapter->eeprompriv.EEPROMRFGainVal = EFUSE_Read1Byte(Adapter, EEPROM_RF_GAIN_VAL);
	पूर्ण अन्यथा अणु
		Adapter->eeprompriv.EEPROMRFGainOffset = 0;
		Adapter->eeprompriv.EEPROMRFGainVal = 0xFF;
	पूर्ण
पूर्ण

u8 BWMapping_8723B(काष्ठा adapter *Adapter, काष्ठा pkt_attrib *pattrib)
अणु
	u8 BWSettingOfDesc = 0;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	अगर (pHalData->CurrentChannelBW == CHANNEL_WIDTH_80) अणु
		अगर (pattrib->bwmode == CHANNEL_WIDTH_80)
			BWSettingOfDesc = 2;
		अन्यथा अगर (pattrib->bwmode == CHANNEL_WIDTH_40)
			BWSettingOfDesc = 1;
		अन्यथा
			BWSettingOfDesc = 0;
	पूर्ण अन्यथा अगर (pHalData->CurrentChannelBW == CHANNEL_WIDTH_40) अणु
		अगर ((pattrib->bwmode == CHANNEL_WIDTH_40) || (pattrib->bwmode == CHANNEL_WIDTH_80))
			BWSettingOfDesc = 1;
		अन्यथा
			BWSettingOfDesc = 0;
	पूर्ण अन्यथा
		BWSettingOfDesc = 0;

	/* अगर (pTcb->bBTTxPacket) */
	/* 	BWSettingOfDesc = 0; */

	वापस BWSettingOfDesc;
पूर्ण

u8 SCMapping_8723B(काष्ठा adapter *Adapter, काष्ठा pkt_attrib *pattrib)
अणु
	u8 SCSettingOfDesc = 0;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	अगर (pHalData->CurrentChannelBW == CHANNEL_WIDTH_80) अणु
		अगर (pattrib->bwmode == CHANNEL_WIDTH_80) अणु
			SCSettingOfDesc = VHT_DATA_SC_DONOT_CARE;
		पूर्ण अन्यथा अगर (pattrib->bwmode == CHANNEL_WIDTH_40) अणु
			अगर (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
				SCSettingOfDesc = VHT_DATA_SC_40_LOWER_OF_80MHZ;
			अन्यथा अगर (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
				SCSettingOfDesc = VHT_DATA_SC_40_UPPER_OF_80MHZ;
		पूर्ण अन्यथा अणु
			अगर ((pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) && (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER))
				SCSettingOfDesc = VHT_DATA_SC_20_LOWEST_OF_80MHZ;
			अन्यथा अगर ((pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER) && (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER))
				SCSettingOfDesc = VHT_DATA_SC_20_LOWER_OF_80MHZ;
			अन्यथा अगर ((pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) && (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER))
				SCSettingOfDesc = VHT_DATA_SC_20_UPPER_OF_80MHZ;
			अन्यथा अगर ((pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER) && (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER))
				SCSettingOfDesc = VHT_DATA_SC_20_UPPERST_OF_80MHZ;
		पूर्ण
	पूर्ण अन्यथा अगर (pHalData->CurrentChannelBW == CHANNEL_WIDTH_40) अणु
		अगर (pattrib->bwmode == CHANNEL_WIDTH_40) अणु
			SCSettingOfDesc = VHT_DATA_SC_DONOT_CARE;
		पूर्ण अन्यथा अगर (pattrib->bwmode == CHANNEL_WIDTH_20) अणु
			अगर (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER) अणु
				SCSettingOfDesc = VHT_DATA_SC_20_UPPER_OF_80MHZ;
			पूर्ण अन्यथा अगर (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) अणु
				SCSettingOfDesc = VHT_DATA_SC_20_LOWER_OF_80MHZ;
			पूर्ण अन्यथा अणु
				SCSettingOfDesc = VHT_DATA_SC_DONOT_CARE;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		SCSettingOfDesc = VHT_DATA_SC_DONOT_CARE;
	पूर्ण

	वापस SCSettingOfDesc;
पूर्ण

अटल व्योम rtl8723b_cal_txdesc_chksum(काष्ठा tx_desc *ptxdesc)
अणु
	u16 *usPtr = (u16 *)ptxdesc;
	u32 count;
	u32 index;
	u16 checksum = 0;


	/*  Clear first */
	ptxdesc->txdw7 &= cpu_to_le32(0xffff0000);

	/*  checksume is always calculated by first 32 bytes, */
	/*  and it करोesn't depend on TX DESC length. */
	/*  Thomas, Lucas@SD4, 20130515 */
	count = 16;

	क्रम (index = 0; index < count; index++) अणु
		checksum |= le16_to_cpu(*(__le16 *)(usPtr + index));
	पूर्ण

	ptxdesc->txdw7 |= cpu_to_le32(checksum & 0x0000ffff);
पूर्ण

अटल u8 fill_txdesc_sectype(काष्ठा pkt_attrib *pattrib)
अणु
	u8 sectype = 0;
	अगर ((pattrib->encrypt > 0) && !pattrib->bswenc) अणु
		चयन (pattrib->encrypt) अणु
		/*  SEC_TYPE */
		हाल _WEP40_:
		हाल _WEP104_:
		हाल _TKIP_:
		हाल _TKIP_WTMIC_:
			sectype = 1;
			अवरोध;

		हाल _AES_:
			sectype = 3;
			अवरोध;

		हाल _NO_PRIVACY_:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस sectype;
पूर्ण

अटल व्योम fill_txdesc_vcs_8723b(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib, काष्ठा txdesc_8723b *ptxdesc)
अणु
	अगर (pattrib->vcs_mode) अणु
		चयन (pattrib->vcs_mode) अणु
		हाल RTS_CTS:
			ptxdesc->rtsen = 1;
			/*  ENABLE HW RTS */
			ptxdesc->hw_rts_en = 1;
			अवरोध;

		हाल CTS_TO_SELF:
			ptxdesc->cts2self = 1;
			अवरोध;

		हाल NONE_VCS:
		शेष:
			अवरोध;
		पूर्ण

		ptxdesc->rtsrate = 8; /*  RTS Rate =24M */
		ptxdesc->rts_ratefb_lmt = 0xF;

		अगर (padapter->mlmeextpriv.mlmext_info.preamble_mode == PREAMBLE_SHORT)
			ptxdesc->rts_लघु = 1;

		/*  Set RTS BW */
		अगर (pattrib->ht_en)
			ptxdesc->rts_sc = SCMapping_8723B(padapter, pattrib);
	पूर्ण
पूर्ण

अटल व्योम fill_txdesc_phy_8723b(काष्ठा adapter *padapter, काष्ठा pkt_attrib *pattrib, काष्ठा txdesc_8723b *ptxdesc)
अणु
	अगर (pattrib->ht_en) अणु
		ptxdesc->data_bw = BWMapping_8723B(padapter, pattrib);

		ptxdesc->data_sc = SCMapping_8723B(padapter, pattrib);
	पूर्ण
पूर्ण

अटल व्योम rtl8723b_fill_शेष_txdesc(
	काष्ठा xmit_frame *pxmitframe, u8 *pbuf
)
अणु
	काष्ठा adapter *padapter;
	काष्ठा hal_com_data *pHalData;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;
	काष्ठा pkt_attrib *pattrib;
	काष्ठा txdesc_8723b *ptxdesc;
	s32 bmcst;

	स_रखो(pbuf, 0, TXDESC_SIZE);

	padapter = pxmitframe->padapter;
	pHalData = GET_HAL_DATA(padapter);
	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &(pmlmeext->mlmext_info);

	pattrib = &pxmitframe->attrib;
	bmcst = IS_MCAST(pattrib->ra);

	ptxdesc = (काष्ठा txdesc_8723b *)pbuf;

	अगर (pxmitframe->frame_tag == DATA_FRAMETAG) अणु
		u8 drv_userate = 0;

		ptxdesc->macid = pattrib->mac_id; /*  CAM_ID(MAC_ID) */
		ptxdesc->rate_id = pattrib->raid;
		ptxdesc->qsel = pattrib->qsel;
		ptxdesc->seq = pattrib->seqnum;

		ptxdesc->sectype = fill_txdesc_sectype(pattrib);
		fill_txdesc_vcs_8723b(padapter, pattrib, ptxdesc);

		अगर (pattrib->icmp_pkt == 1 && padapter->registrypriv.wअगरi_spec == 1)
			drv_userate = 1;

		अगर (
			(pattrib->ether_type != 0x888e) &&
			(pattrib->ether_type != 0x0806) &&
			(pattrib->ether_type != 0x88B4) &&
			(pattrib->dhcp_pkt != 1) &&
			(drv_userate != 1)
		) अणु
			/*  Non EAP & ARP & DHCP type data packet */

			अगर (pattrib->ampdu_en) अणु
				ptxdesc->agg_en = 1; /*  AGG EN */
				ptxdesc->max_agg_num = 0x1f;
				ptxdesc->ampdu_density = pattrib->ampdu_spacing;
			पूर्ण अन्यथा
				ptxdesc->bk = 1; /*  AGG BK */

			fill_txdesc_phy_8723b(padapter, pattrib, ptxdesc);

			ptxdesc->data_ratefb_lmt = 0x1F;

			अगर (!pHalData->fw_ractrl) अणु
				ptxdesc->userate = 1;

				अगर (pHalData->dmpriv.INIDATA_RATE[pattrib->mac_id] & BIT(7))
					ptxdesc->data_लघु = 1;

				ptxdesc->datarate = pHalData->dmpriv.INIDATA_RATE[pattrib->mac_id] & 0x7F;
			पूर्ण

			अगर (padapter->fix_rate != 0xFF) अणु /*  modअगरy data rate by iwpriv */
				ptxdesc->userate = 1;
				अगर (padapter->fix_rate & BIT(7))
					ptxdesc->data_लघु = 1;

				ptxdesc->datarate = (padapter->fix_rate & 0x7F);
				ptxdesc->disdatafb = 1;
			पूर्ण

			अगर (pattrib->ldpc)
				ptxdesc->data_ldpc = 1;
			अगर (pattrib->stbc)
				ptxdesc->data_stbc = 1;
		पूर्ण अन्यथा अणु
			/*  EAP data packet and ARP packet. */
			/*  Use the 1M data rate to send the EAP/ARP packet. */
			/*  This will maybe make the handshake smooth. */

			ptxdesc->bk = 1; /*  AGG BK */
			ptxdesc->userate = 1; /*  driver uses rate */
			अगर (pmlmeinfo->preamble_mode == PREAMBLE_SHORT)
				ptxdesc->data_लघु = 1;/*  DATA_SHORT */
			ptxdesc->datarate = MRateToHwRate(pmlmeext->tx_rate);
		पूर्ण

		ptxdesc->usb_txagg_num = pxmitframe->agg_num;
	पूर्ण अन्यथा अगर (pxmitframe->frame_tag == MGNT_FRAMETAG) अणु
		ptxdesc->macid = pattrib->mac_id; /*  CAM_ID(MAC_ID) */
		ptxdesc->qsel = pattrib->qsel;
		ptxdesc->rate_id = pattrib->raid; /*  Rate ID */
		ptxdesc->seq = pattrib->seqnum;
		ptxdesc->userate = 1; /*  driver uses rate, 1M */

		ptxdesc->mbssid = pattrib->mbssid & 0xF;

		ptxdesc->rty_lmt_en = 1; /*  retry limit enable */
		अगर (pattrib->retry_ctrl) अणु
			ptxdesc->data_rt_lmt = 6;
		पूर्ण अन्यथा अणु
			ptxdesc->data_rt_lmt = 12;
		पूर्ण

		ptxdesc->datarate = MRateToHwRate(pmlmeext->tx_rate);

		/*  CCX-TXRPT ack क्रम xmit mgmt frames. */
		अगर (pxmitframe->ack_report) अणु
			ptxdesc->spe_rpt = 1;
			ptxdesc->sw_define = (u8)(GET_PRIMARY_ADAPTER(padapter)->xmitpriv.seq_no);
		पूर्ण
	पूर्ण अन्यथा अणु
		ptxdesc->macid = pattrib->mac_id; /*  CAM_ID(MAC_ID) */
		ptxdesc->rate_id = pattrib->raid; /*  Rate ID */
		ptxdesc->qsel = pattrib->qsel;
		ptxdesc->seq = pattrib->seqnum;
		ptxdesc->userate = 1; /*  driver uses rate */
		ptxdesc->datarate = MRateToHwRate(pmlmeext->tx_rate);
	पूर्ण

	ptxdesc->pktlen = pattrib->last_txcmdsz;
	ptxdesc->offset = TXDESC_SIZE + OFFSET_SZ;

	अगर (bmcst)
		ptxdesc->bmc = 1;

	/* 2009.11.05. tynli_test. Suggested by SD4 Filen क्रम FW LPS.
	 * (1) The sequence number of each non-Qos frame / broadcast /
	 * multicast / mgnt frame should be controlled by Hw because Fw
	 * will also send null data which we cannot control when Fw LPS
	 * enable.
	 * --> शेष enable non-Qos data sequense number. 2010.06.23.
	 * by tynli.
	 * (2) Enable HW SEQ control क्रम beacon packet, because we use
	 * Hw beacon.
	 * (3) Use HW Qos SEQ to control the seq num of Ext port non-Qos
	 * packets.
	 * 2010.06.23. Added by tynli.
	 */
	अगर (!pattrib->qos_en) /*  Hw set sequence number */
		ptxdesc->en_hwseq = 1; /*  HWSEQ_EN */
पूर्ण

/* Description:
 *
 * Parameters:
 *	pxmitframe	xmitframe
 *	pbuf		where to fill tx desc
 */
व्योम rtl8723b_update_txdesc(काष्ठा xmit_frame *pxmitframe, u8 *pbuf)
अणु
	काष्ठा tx_desc *pdesc;

	rtl8723b_fill_शेष_txdesc(pxmitframe, pbuf);

	pdesc = (काष्ठा tx_desc *)pbuf;
	pdesc->txdw0 = pdesc->txdw0;
	pdesc->txdw1 = pdesc->txdw1;
	pdesc->txdw2 = pdesc->txdw2;
	pdesc->txdw3 = pdesc->txdw3;
	pdesc->txdw4 = pdesc->txdw4;
	pdesc->txdw5 = pdesc->txdw5;
	pdesc->txdw6 = pdesc->txdw6;
	pdesc->txdw7 = pdesc->txdw7;
	pdesc->txdw8 = pdesc->txdw8;
	pdesc->txdw9 = pdesc->txdw9;

	rtl8723b_cal_txdesc_chksum(pdesc);
पूर्ण

/*  */
/*  Description: In normal chip, we should send some packet to Hw which will be used by Fw */
/* 			in FW LPS mode. The function is to fill the Tx descriptor of this packets, then */
/* 			Fw can tell Hw to send these packet derectly. */
/*  Added by tynli. 2009.10.15. */
/*  */
/* type1:pspoll, type2:null */
व्योम rtl8723b_fill_fake_txdesc(
	काष्ठा adapter *padapter,
	u8 *pDesc,
	u32 BufferLen,
	u8 IsPsPoll,
	u8 IsBTQosNull,
	u8 bDataFrame
)
अणु
	/*  Clear all status */
	स_रखो(pDesc, 0, TXDESC_SIZE);

	SET_TX_DESC_FIRST_SEG_8723B(pDesc, 1); /* bFirstSeg; */
	SET_TX_DESC_LAST_SEG_8723B(pDesc, 1); /* bLastSeg; */

	SET_TX_DESC_OFFSET_8723B(pDesc, 0x28); /*  Offset = 32 */

	SET_TX_DESC_PKT_SIZE_8723B(pDesc, BufferLen); /*  Buffer size + command header */
	SET_TX_DESC_QUEUE_SEL_8723B(pDesc, QSLT_MGNT); /*  Fixed queue of Mgnt queue */

	/*  Set NAVUSEHDR to prevent Ps-poll AId filed to be changed to error vlaue by Hw. */
	अगर (IsPsPoll) अणु
		SET_TX_DESC_NAV_USE_HDR_8723B(pDesc, 1);
	पूर्ण अन्यथा अणु
		SET_TX_DESC_HWSEQ_EN_8723B(pDesc, 1); /*  Hw set sequence number */
		SET_TX_DESC_HWSEQ_SEL_8723B(pDesc, 0);
	पूर्ण

	अगर (IsBTQosNull) अणु
		SET_TX_DESC_BT_INT_8723B(pDesc, 1);
	पूर्ण

	SET_TX_DESC_USE_RATE_8723B(pDesc, 1); /*  use data rate which is set by Sw */
	SET_TX_DESC_OWN_8723B((u8 *)pDesc, 1);

	SET_TX_DESC_TX_RATE_8723B(pDesc, DESC8723B_RATE1M);

	/*  */
	/*  Encrypt the data frame अगर under security mode excepct null data. Suggested by CCW. */
	/*  */
	अगर (bDataFrame) अणु
		u32 EncAlg;

		EncAlg = padapter->securitypriv.करोt11PrivacyAlgrthm;
		चयन (EncAlg) अणु
		हाल _NO_PRIVACY_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x0);
			अवरोध;
		हाल _WEP40_:
		हाल _WEP104_:
		हाल _TKIP_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x1);
			अवरोध;
		हाल _SMS4_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x2);
			अवरोध;
		हाल _AES_:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x3);
			अवरोध;
		शेष:
			SET_TX_DESC_SEC_TYPE_8723B(pDesc, 0x0);
			अवरोध;
		पूर्ण
	पूर्ण

	/*  USB पूर्णांकerface drop packet अगर the checksum of descriptor isn't correct. */
	/*  Using this checksum can let hardware recovery from packet bulk out error (e.g. Cancel URC, Bulk out error.). */
	rtl8723b_cal_txdesc_chksum((काष्ठा tx_desc *)pDesc);
पूर्ण

अटल व्योम hw_var_set_opmode(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u8 val8;
	u8 mode = *((u8 *)val);

	अणु
		/*  disable Port0 TSF update */
		val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
		val8 |= DIS_TSF_UDT;
		rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);

		/*  set net_type */
		Set_MSR(padapter, mode);

		अगर ((mode == _HW_STATE_STATION_) || (mode == _HW_STATE_NOLINK_)) अणु
			अणु
				StopTxBeacon(padapter);
			पूर्ण

			/*  disable atim wnd */
			rtw_ग_लिखो8(padapter, REG_BCN_CTRL, DIS_TSF_UDT|EN_BCN_FUNCTION|DIS_ATIM);
			/* rtw_ग_लिखो8(padapter, REG_BCN_CTRL, 0x18); */
		पूर्ण अन्यथा अगर (mode == _HW_STATE_ADHOC_) अणु
			ResumeTxBeacon(padapter);
			rtw_ग_लिखो8(padapter, REG_BCN_CTRL, DIS_TSF_UDT|EN_BCN_FUNCTION|DIS_BCNQ_SUB);
		पूर्ण अन्यथा अगर (mode == _HW_STATE_AP_) अणु

			ResumeTxBeacon(padapter);

			rtw_ग_लिखो8(padapter, REG_BCN_CTRL, DIS_TSF_UDT|DIS_BCNQ_SUB);

			/* Set RCR */
			rtw_ग_लिखो32(padapter, REG_RCR, 0x7000208e);/* CBSSID_DATA must set to 0, reject ICV_ERR packet */
			/* enable to rx data frame */
			rtw_ग_लिखो16(padapter, REG_RXFLTMAP2, 0xFFFF);
			/* enable to rx ps-poll */
			rtw_ग_लिखो16(padapter, REG_RXFLTMAP1, 0x0400);

			/* Beacon Control related रेजिस्टर क्रम first समय */
			rtw_ग_लिखो8(padapter, REG_BCNDMATIM, 0x02); /*  2ms */

			/* rtw_ग_लिखो8(padapter, REG_BCN_MAX_ERR, 0xFF); */
			rtw_ग_लिखो8(padapter, REG_ATIMWND, 0x0a); /*  10ms */
			rtw_ग_लिखो16(padapter, REG_BCNTCFG, 0x00);
			rtw_ग_लिखो16(padapter, REG_TBTT_PROHIBIT, 0xff04);
			rtw_ग_लिखो16(padapter, REG_TSFTR_SYN_OFFSET, 0x7fff);/*  +32767 (~32ms) */

			/* reset TSF */
			rtw_ग_लिखो8(padapter, REG_DUAL_TSF_RST, BIT(0));

			/* enable BCN0 Function क्रम अगर1 */
			/* करोn't enable update TSF0 क्रम अगर1 (due to TSF update when beacon/probe rsp are received) */
			rtw_ग_लिखो8(padapter, REG_BCN_CTRL, (DIS_TSF_UDT|EN_BCN_FUNCTION|EN_TXBCN_RPT|DIS_BCNQ_SUB));

			/* SW_BCN_SEL - Port0 */
			/* rtw_ग_लिखो8(Adapter, REG_DWBCN1_CTRL_8192E+2, rtw_पढ़ो8(Adapter, REG_DWBCN1_CTRL_8192E+2) & ~BIT4); */
			rtw_hal_set_hwreg(padapter, HW_VAR_DL_BCN_SEL, शून्य);

			/*  select BCN on port 0 */
			rtw_ग_लिखो8(
				padapter,
				REG_CCK_CHECK_8723B,
				(rtw_पढ़ो8(padapter, REG_CCK_CHECK_8723B)&~BIT_BCN_PORT_SEL)
			);

			/*  dis BCN1 ATIM  WND अगर अगर2 is station */
			val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL_1);
			val8 |= DIS_ATIM;
			rtw_ग_लिखो8(padapter, REG_BCN_CTRL_1, val8);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hw_var_set_macaddr(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u8 idx = 0;
	u32 reg_macid;

	reg_macid = REG_MACID;

	क्रम (idx = 0 ; idx < 6; idx++)
		rtw_ग_लिखो8(GET_PRIMARY_ADAPTER(padapter), (reg_macid+idx), val[idx]);
पूर्ण

अटल व्योम hw_var_set_bssid(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u8 idx = 0;
	u32 reg_bssid;

	reg_bssid = REG_BSSID;

	क्रम (idx = 0 ; idx < 6; idx++)
		rtw_ग_लिखो8(padapter, (reg_bssid+idx), val[idx]);
पूर्ण

अटल व्योम hw_var_set_bcn_func(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u32 bcn_ctrl_reg;

	bcn_ctrl_reg = REG_BCN_CTRL;

	अगर (*(u8 *)val)
		rtw_ग_लिखो8(padapter, bcn_ctrl_reg, (EN_BCN_FUNCTION | EN_TXBCN_RPT));
	अन्यथा अणु
		u8 val8;
		val8 = rtw_पढ़ो8(padapter, bcn_ctrl_reg);
		val8 &= ~(EN_BCN_FUNCTION | EN_TXBCN_RPT);

		/*  Always enable port0 beacon function क्रम PSTDMA */
		अगर (REG_BCN_CTRL == bcn_ctrl_reg)
			val8 |= EN_BCN_FUNCTION;

		rtw_ग_लिखो8(padapter, bcn_ctrl_reg, val8);
	पूर्ण
पूर्ण

अटल व्योम hw_var_set_correct_tsf(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u8 val8;
	u64 tsf;
	काष्ठा mlme_ext_priv *pmlmeext;
	काष्ठा mlme_ext_info *pmlmeinfo;


	pmlmeext = &padapter->mlmeextpriv;
	pmlmeinfo = &pmlmeext->mlmext_info;

	tsf = pmlmeext->TSFValue-करो_भाग(pmlmeext->TSFValue, (pmlmeinfo->bcn_पूर्णांकerval*1024))-1024; /* us */

	अगर (
		((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) ||
		((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)
	)
		StopTxBeacon(padapter);

	अणु
		/*  disable related TSF function */
		val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
		val8 &= ~EN_BCN_FUNCTION;
		rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);

		rtw_ग_लिखो32(padapter, REG_TSFTR, tsf);
		rtw_ग_लिखो32(padapter, REG_TSFTR+4, tsf>>32);

		/*  enable related TSF function */
		val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
		val8 |= EN_BCN_FUNCTION;
		rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);
	पूर्ण

	अगर (
		((pmlmeinfo->state&0x03) == WIFI_FW_ADHOC_STATE) ||
		((pmlmeinfo->state&0x03) == WIFI_FW_AP_STATE)
	)
		ResumeTxBeacon(padapter);
पूर्ण

अटल व्योम hw_var_set_mlme_disconnect(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u8 val8;

	/*  Set RCR to not to receive data frame when NO LINK state */
	/* rtw_ग_लिखो32(padapter, REG_RCR, rtw_पढ़ो32(padapter, REG_RCR) & ~RCR_ADF); */
	/*  reject all data frames */
	rtw_ग_लिखो16(padapter, REG_RXFLTMAP2, 0);

	/*  reset TSF */
	rtw_ग_लिखो8(padapter, REG_DUAL_TSF_RST, BIT(0));

	/*  disable update TSF */
	val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
	val8 |= DIS_TSF_UDT;
	rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);
पूर्ण

अटल व्योम hw_var_set_mlme_sitesurvey(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u32 value_rcr, rcr_clear_bit, reg_bcn_ctl;
	u16 value_rxflपंचांगap2;
	u8 val8;
	काष्ठा hal_com_data *pHalData;
	काष्ठा mlme_priv *pmlmepriv;


	pHalData = GET_HAL_DATA(padapter);
	pmlmepriv = &padapter->mlmepriv;

	reg_bcn_ctl = REG_BCN_CTRL;

	rcr_clear_bit = RCR_CBSSID_BCN;

	/*  config RCR to receive dअगरferent BSSID & not to receive data frame */
	value_rxflपंचांगap2 = 0;

	अगर ((check_fwstate(pmlmepriv, WIFI_AP_STATE) == true))
		rcr_clear_bit = RCR_CBSSID_BCN;

	value_rcr = rtw_पढ़ो32(padapter, REG_RCR);

	अगर (*((u8 *)val)) अणु
		/*  under sitesurvey */
		value_rcr &= ~(rcr_clear_bit);
		rtw_ग_लिखो32(padapter, REG_RCR, value_rcr);

		rtw_ग_लिखो16(padapter, REG_RXFLTMAP2, value_rxflपंचांगap2);

		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE)) अणु
			/*  disable update TSF */
			val8 = rtw_पढ़ो8(padapter, reg_bcn_ctl);
			val8 |= DIS_TSF_UDT;
			rtw_ग_लिखो8(padapter, reg_bcn_ctl, val8);
		पूर्ण

		/*  Save original RRSR setting. */
		pHalData->RegRRSR = rtw_पढ़ो16(padapter, REG_RRSR);
	पूर्ण अन्यथा अणु
		/*  sitesurvey करोne */
		अगर (check_fwstate(pmlmepriv, (_FW_LINKED|WIFI_AP_STATE)))
			/*  enable to rx data frame */
			rtw_ग_लिखो16(padapter, REG_RXFLTMAP2, 0xFFFF);

		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE | WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE)) अणु
			/*  enable update TSF */
			val8 = rtw_पढ़ो8(padapter, reg_bcn_ctl);
			val8 &= ~DIS_TSF_UDT;
			rtw_ग_लिखो8(padapter, reg_bcn_ctl, val8);
		पूर्ण

		value_rcr |= rcr_clear_bit;
		rtw_ग_लिखो32(padapter, REG_RCR, value_rcr);

		/*  Restore original RRSR setting. */
		rtw_ग_लिखो16(padapter, REG_RRSR, pHalData->RegRRSR);
	पूर्ण
पूर्ण

अटल व्योम hw_var_set_mlme_join(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u8 val8;
	u16 val16;
	u32 val32;
	u8 RetryLimit;
	u8 type;
	काष्ठा mlme_priv *pmlmepriv;
	काष्ठा eeprom_priv *pEEPROM;


	RetryLimit = 0x30;
	type = *(u8 *)val;
	pmlmepriv = &padapter->mlmepriv;
	pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	अगर (type == 0) अणु /*  prepare to join */
		/* enable to rx data frame.Accept all data frame */
		/* rtw_ग_लिखो32(padapter, REG_RCR, rtw_पढ़ो32(padapter, REG_RCR)|RCR_ADF); */
		rtw_ग_लिखो16(padapter, REG_RXFLTMAP2, 0xFFFF);

		val32 = rtw_पढ़ो32(padapter, REG_RCR);
		अगर (padapter->in_cta_test)
			val32 &= ~(RCR_CBSSID_DATA | RCR_CBSSID_BCN);/*  RCR_ADF */
		अन्यथा
			val32 |= RCR_CBSSID_DATA|RCR_CBSSID_BCN;
		rtw_ग_लिखो32(padapter, REG_RCR, val32);

		अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE) == true)
			RetryLimit = (pEEPROM->CustomerID == RT_CID_CCX) ? 7 : 48;
		अन्यथा /*  Ad-hoc Mode */
			RetryLimit = 0x7;
	पूर्ण अन्यथा अगर (type == 1) /* joinbss_event call back when join res < 0 */
		rtw_ग_लिखो16(padapter, REG_RXFLTMAP2, 0x00);
	अन्यथा अगर (type == 2) अणु /* sta add event call back */
		/* enable update TSF */
		val8 = rtw_पढ़ो8(padapter, REG_BCN_CTRL);
		val8 &= ~DIS_TSF_UDT;
		rtw_ग_लिखो8(padapter, REG_BCN_CTRL, val8);

		अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTER_STATE))
			RetryLimit = 0x7;
	पूर्ण

	val16 = (RetryLimit << RETRY_LIMIT_SHORT_SHIFT) | (RetryLimit << RETRY_LIMIT_LONG_SHIFT);
	rtw_ग_लिखो16(padapter, REG_RL, val16);
पूर्ण

व्योम CCX_FwC2HTxRpt_8723b(काष्ठा adapter *padapter, u8 *pdata, u8 len)
अणु

#घोषणा	GET_8723B_C2H_TX_RPT_LIFE_TIME_OVER(_Header)	LE_BITS_TO_1BYTE((_Header + 0), 6, 1)
#घोषणा	GET_8723B_C2H_TX_RPT_RETRY_OVER(_Header)	LE_BITS_TO_1BYTE((_Header + 0), 7, 1)

	अगर (GET_8723B_C2H_TX_RPT_RETRY_OVER(pdata) | GET_8723B_C2H_TX_RPT_LIFE_TIME_OVER(pdata)) अणु
		rtw_ack_tx_करोne(&padapter->xmitpriv, RTW_SCTX_DONE_CCX_PKT_FAIL);
	पूर्ण
/*
	अन्यथा अगर (seq_no != padapter->xmitpriv.seq_no) अणु
		rtw_ack_tx_करोne(&padapter->xmitpriv, RTW_SCTX_DONE_CCX_PKT_FAIL);
	पूर्ण
*/
	अन्यथा
		rtw_ack_tx_करोne(&padapter->xmitpriv, RTW_SCTX_DONE_SUCCESS);
पूर्ण

s32 c2h_id_filter_ccx_8723b(u8 *buf)
अणु
	काष्ठा c2h_evt_hdr_88xx *c2h_evt = (काष्ठा c2h_evt_hdr_88xx *)buf;
	s32 ret = false;
	अगर (c2h_evt->id == C2H_CCX_TX_RPT)
		ret = true;

	वापस ret;
पूर्ण


s32 c2h_handler_8723b(काष्ठा adapter *padapter, u8 *buf)
अणु
	काष्ठा c2h_evt_hdr_88xx *pC2hEvent = (काष्ठा c2h_evt_hdr_88xx *)buf;
	s32 ret = _SUCCESS;

	अगर (!pC2hEvent) अणु
		ret = _FAIL;
		जाओ निकास;
	पूर्ण

	चयन (pC2hEvent->id) अणु
	हाल C2H_AP_RPT_RSP:
		अवरोध;
	हाल C2H_DBG:
		अणु
		पूर्ण
		अवरोध;

	हाल C2H_CCX_TX_RPT:
/* 			CCX_FwC2HTxRpt(padapter, QueueID, pC2hEvent->payload); */
		अवरोध;

	हाल C2H_EXT_RA_RPT:
/* 			C2HExtRaRptHandler(padapter, pC2hEvent->payload, C2hEvent.CmdLen); */
		अवरोध;

	हाल C2H_HW_INFO_EXCH:
		अवरोध;

	हाल C2H_8723B_BT_INFO:
		hal_btcoex_BtInfoNotअगरy(padapter, pC2hEvent->plen, pC2hEvent->payload);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/*  Clear event to notअगरy FW we have पढ़ो the command. */
	/*  Note: */
	/* 	If this field isn't clear, the FW won't update the next command message. */
/* 	rtw_ग_लिखो8(padapter, REG_C2HEVT_CLEAR, C2H_EVT_HOST_CLOSE); */
निकास:
	वापस ret;
पूर्ण

अटल व्योम process_c2h_event(काष्ठा adapter *padapter, काष्ठा c2h_evt_hdr_t *pC2hEvent, u8 *c2hBuf)
अणु
	अगर (!c2hBuf)
		वापस;

	चयन (pC2hEvent->CmdID) अणु
	हाल C2H_AP_RPT_RSP:
		अवरोध;
	हाल C2H_DBG:
		अणु
		पूर्ण
		अवरोध;

	हाल C2H_CCX_TX_RPT:
/* 			CCX_FwC2HTxRpt(padapter, QueueID, पंचांगpBuf); */
		अवरोध;

	हाल C2H_EXT_RA_RPT:
/* 			C2HExtRaRptHandler(padapter, पंचांगpBuf, C2hEvent.CmdLen); */
		अवरोध;

	हाल C2H_HW_INFO_EXCH:
		अवरोध;

	हाल C2H_8723B_BT_INFO:
		hal_btcoex_BtInfoNotअगरy(padapter, pC2hEvent->CmdLen, c2hBuf);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम C2HPacketHandler_8723B(काष्ठा adapter *padapter, u8 *pbuffer, u16 length)
अणु
	काष्ठा c2h_evt_hdr_t	C2hEvent;
	u8 *पंचांगpBuf = शून्य;
	C2hEvent.CmdID = pbuffer[0];
	C2hEvent.CmdSeq = pbuffer[1];
	C2hEvent.CmdLen = length-2;
	पंचांगpBuf = pbuffer+2;

	prपूर्णांक_hex_dump_debug(DRIVER_PREFIX ": C2HPacketHandler_8723B(): Command Content:\n",
			     DUMP_PREFIX_NONE, 16, 1, पंचांगpBuf, C2hEvent.CmdLen, false);

	process_c2h_event(padapter, &C2hEvent, पंचांगpBuf);
	/* c2h_handler_8723b(padapter,&C2hEvent); */
पूर्ण

व्योम SetHwReg8723B(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 val8;
	u32 val32;

	चयन (variable) अणु
	हाल HW_VAR_MEDIA_STATUS:
		val8 = rtw_पढ़ो8(padapter, MSR) & 0x0c;
		val8 |= *val;
		rtw_ग_लिखो8(padapter, MSR, val8);
		अवरोध;

	हाल HW_VAR_MEDIA_STATUS1:
		val8 = rtw_पढ़ो8(padapter, MSR) & 0x03;
		val8 |= *val << 2;
		rtw_ग_लिखो8(padapter, MSR, val8);
		अवरोध;

	हाल HW_VAR_SET_OPMODE:
		hw_var_set_opmode(padapter, variable, val);
		अवरोध;

	हाल HW_VAR_MAC_ADDR:
		hw_var_set_macaddr(padapter, variable, val);
		अवरोध;

	हाल HW_VAR_BSSID:
		hw_var_set_bssid(padapter, variable, val);
		अवरोध;

	हाल HW_VAR_BASIC_RATE:
	अणु
		काष्ठा mlme_ext_info *mlmext_info = &padapter->mlmeextpriv.mlmext_info;
		u16 BrateCfg = 0;
		u16 rrsr_2g_क्रमce_mask = (RRSR_11M|RRSR_5_5M|RRSR_1M);
		u16 rrsr_2g_allow_mask = (RRSR_24M|RRSR_12M|RRSR_6M|RRSR_CCK_RATES);

		HalSetBrateCfg(padapter, val, &BrateCfg);

		/* apply क्रमce and allow mask */
		BrateCfg |= rrsr_2g_क्रमce_mask;
		BrateCfg &= rrsr_2g_allow_mask;

		/* IOT consideration */
		अगर (mlmext_info->assoc_AP_venकरोr == HT_IOT_PEER_CISCO) अणु
			/* अगर peer is cisco and didn't use ofdm rate, we enable 6M ack */
			अगर ((BrateCfg & (RRSR_24M|RRSR_12M|RRSR_6M)) == 0)
				BrateCfg |= RRSR_6M;
		पूर्ण

		pHalData->BasicRateSet = BrateCfg;

		/*  Set RRSR rate table. */
		rtw_ग_लिखो16(padapter, REG_RRSR, BrateCfg);
		rtw_ग_लिखो8(padapter, REG_RRSR+2, rtw_पढ़ो8(padapter, REG_RRSR+2)&0xf0);
	पूर्ण
		अवरोध;

	हाल HW_VAR_TXPAUSE:
		rtw_ग_लिखो8(padapter, REG_TXPAUSE, *val);
		अवरोध;

	हाल HW_VAR_BCN_FUNC:
		hw_var_set_bcn_func(padapter, variable, val);
		अवरोध;

	हाल HW_VAR_CORRECT_TSF:
		hw_var_set_correct_tsf(padapter, variable, val);
		अवरोध;

	हाल HW_VAR_CHECK_BSSID:
		अणु
			u32 val32;
			val32 = rtw_पढ़ो32(padapter, REG_RCR);
			अगर (*val)
				val32 |= RCR_CBSSID_DATA|RCR_CBSSID_BCN;
			अन्यथा
				val32 &= ~(RCR_CBSSID_DATA|RCR_CBSSID_BCN);
			rtw_ग_लिखो32(padapter, REG_RCR, val32);
		पूर्ण
		अवरोध;

	हाल HW_VAR_MLME_DISCONNECT:
		hw_var_set_mlme_disconnect(padapter, variable, val);
		अवरोध;

	हाल HW_VAR_MLME_SITESURVEY:
		hw_var_set_mlme_sitesurvey(padapter, variable,  val);

		hal_btcoex_ScanNotअगरy(padapter, *val?true:false);
		अवरोध;

	हाल HW_VAR_MLME_JOIN:
		hw_var_set_mlme_join(padapter, variable, val);

		चयन (*val) अणु
		हाल 0:
			/*  prepare to join */
			hal_btcoex_ConnectNotअगरy(padapter, true);
			अवरोध;
		हाल 1:
			/*  joinbss_event callback when join res < 0 */
			hal_btcoex_ConnectNotअगरy(padapter, false);
			अवरोध;
		हाल 2:
			/*  sta add event callback */
/* 				rtw_btcoex_MediaStatusNotअगरy(padapter, RT_MEDIA_CONNECT); */
			अवरोध;
		पूर्ण
		अवरोध;

	हाल HW_VAR_ON_RCR_AM:
		val32 = rtw_पढ़ो32(padapter, REG_RCR);
		val32 |= RCR_AM;
		rtw_ग_लिखो32(padapter, REG_RCR, val32);
		अवरोध;

	हाल HW_VAR_OFF_RCR_AM:
		val32 = rtw_पढ़ो32(padapter, REG_RCR);
		val32 &= ~RCR_AM;
		rtw_ग_लिखो32(padapter, REG_RCR, val32);
		अवरोध;

	हाल HW_VAR_BEACON_INTERVAL:
		rtw_ग_लिखो16(padapter, REG_BCN_INTERVAL, *((u16 *)val));
		अवरोध;

	हाल HW_VAR_SLOT_TIME:
		rtw_ग_लिखो8(padapter, REG_SLOT, *val);
		अवरोध;

	हाल HW_VAR_RESP_SIFS:
		/* SIFS_Timer = 0x0a0a0808; */
		/* RESP_SIFS क्रम CCK */
		rtw_ग_लिखो8(padapter, REG_RESP_SIFS_CCK, val[0]); /*  SIFS_T2T_CCK (0x08) */
		rtw_ग_लिखो8(padapter, REG_RESP_SIFS_CCK+1, val[1]); /* SIFS_R2T_CCK(0x08) */
		/* RESP_SIFS क्रम OFDM */
		rtw_ग_लिखो8(padapter, REG_RESP_SIFS_OFDM, val[2]); /* SIFS_T2T_OFDM (0x0a) */
		rtw_ग_लिखो8(padapter, REG_RESP_SIFS_OFDM+1, val[3]); /* SIFS_R2T_OFDM(0x0a) */
		अवरोध;

	हाल HW_VAR_ACK_PREAMBLE:
		अणु
			u8 regTmp;
			u8 bShortPreamble = *val;

			/*  Joseph marked out क्रम Netgear 3500 TKIP channel 7 issue.(Temporarily) */
			/* regTmp = (pHalData->nCur40MhzPrimeSC)<<5; */
			regTmp = 0;
			अगर (bShortPreamble)
				regTmp |= 0x80;
			rtw_ग_लिखो8(padapter, REG_RRSR+2, regTmp);
		पूर्ण
		अवरोध;

	हाल HW_VAR_CAM_EMPTY_ENTRY:
		अणु
			u8 ucIndex = *val;
			u8 i;
			u32 ulCommand = 0;
			u32 ulContent = 0;
			u32 ulEncAlgo = CAM_AES;

			क्रम (i = 0; i < CAM_CONTENT_COUNT; i++) अणु
				/*  filled id in CAM config 2 byte */
				अगर (i == 0) अणु
					ulContent |= (ucIndex & 0x03) | ((u16)(ulEncAlgo)<<2);
					/* ulContent |= CAM_VALID; */
				पूर्ण अन्यथा
					ulContent = 0;

				/*  polling bit, and No Write enable, and address */
				ulCommand = CAM_CONTENT_COUNT*ucIndex+i;
				ulCommand = ulCommand | CAM_POLLINIG | CAM_WRITE;
				/*  ग_लिखो content 0 is equall to mark invalid */
				rtw_ग_लिखो32(padapter, WCAMI, ulContent);  /* mdelay(40); */
				rtw_ग_लिखो32(padapter, RWCAM, ulCommand);  /* mdelay(40); */
			पूर्ण
		पूर्ण
		अवरोध;

	हाल HW_VAR_CAM_INVALID_ALL:
		rtw_ग_लिखो32(padapter, RWCAM, BIT(31)|BIT(30));
		अवरोध;

	हाल HW_VAR_CAM_WRITE:
		अणु
			u32 cmd;
			u32 *cam_val = (u32 *)val;

			rtw_ग_लिखो32(padapter, WCAMI, cam_val[0]);

			cmd = CAM_POLLINIG | CAM_WRITE | cam_val[1];
			rtw_ग_लिखो32(padapter, RWCAM, cmd);
		पूर्ण
		अवरोध;

	हाल HW_VAR_AC_PARAM_VO:
		rtw_ग_लिखो32(padapter, REG_EDCA_VO_PARAM, *((u32 *)val));
		अवरोध;

	हाल HW_VAR_AC_PARAM_VI:
		rtw_ग_लिखो32(padapter, REG_EDCA_VI_PARAM, *((u32 *)val));
		अवरोध;

	हाल HW_VAR_AC_PARAM_BE:
		pHalData->AcParam_BE = ((u32 *)(val))[0];
		rtw_ग_लिखो32(padapter, REG_EDCA_BE_PARAM, *((u32 *)val));
		अवरोध;

	हाल HW_VAR_AC_PARAM_BK:
		rtw_ग_लिखो32(padapter, REG_EDCA_BK_PARAM, *((u32 *)val));
		अवरोध;

	हाल HW_VAR_ACM_CTRL:
		अणु
			u8 ctrl = *((u8 *)val);
			u8 hwctrl = 0;

			अगर (ctrl != 0) अणु
				hwctrl |= AcmHw_HwEn;

				अगर (ctrl & BIT(1)) /*  BE */
					hwctrl |= AcmHw_BeqEn;

				अगर (ctrl & BIT(2)) /*  VI */
					hwctrl |= AcmHw_ViqEn;

				अगर (ctrl & BIT(3)) /*  VO */
					hwctrl |= AcmHw_VoqEn;
			पूर्ण

			rtw_ग_लिखो8(padapter, REG_ACMHWCTRL, hwctrl);
		पूर्ण
		अवरोध;

	हाल HW_VAR_AMPDU_FACTOR:
		अणु
			u32 AMPDULen =  (*((u8 *)val));

			अगर (AMPDULen < HT_AGG_SIZE_32K)
				AMPDULen = (0x2000 << (*((u8 *)val)))-1;
			अन्यथा
				AMPDULen = 0x7fff;

			rtw_ग_लिखो32(padapter, REG_AMPDU_MAX_LENGTH_8723B, AMPDULen);
		पूर्ण
		अवरोध;

	हाल HW_VAR_H2C_FW_PWRMODE:
		अणु
			u8 psmode = *val;

			/*  Forece leave RF low घातer mode क्रम 1T1R to prevent conficting setting in Fw घातer */
			/*  saving sequence. 2010.06.07. Added by tynli. Suggested by SD3 yschang. */
			अगर (psmode != PS_MODE_ACTIVE) अणु
				ODM_RF_Saving(&pHalData->odmpriv, true);
			पूर्ण

			/* अगर (psmode != PS_MODE_ACTIVE)	अणु */
			/* 	rtl8723b_set_lowpwr_lps_cmd(padapter, true); */
			/*  अन्यथा अणु */
			/* 	rtl8723b_set_lowpwr_lps_cmd(padapter, false); */
			/*  */
			rtl8723b_set_FwPwrMode_cmd(padapter, psmode);
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_PS_TUNE_PARAM:
		rtl8723b_set_FwPsTuneParam_cmd(padapter);
		अवरोध;

	हाल HW_VAR_H2C_FW_JOINBSSRPT:
		rtl8723b_set_FwJoinBssRpt_cmd(padapter, *val);
		अवरोध;

	हाल HW_VAR_INITIAL_GAIN:
		अणु
			काष्ठा dig_t *pDigTable = &pHalData->odmpriv.DM_DigTable;
			u32 rx_gain = *(u32 *)val;

			अगर (rx_gain == 0xff) अणु/* restore rx gain */
				ODM_Write_DIG(&pHalData->odmpriv, pDigTable->BackupIGValue);
			पूर्ण अन्यथा अणु
				pDigTable->BackupIGValue = pDigTable->CurIGValue;
				ODM_Write_DIG(&pHalData->odmpriv, rx_gain);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल HW_VAR_EFUSE_USAGE:
		pHalData->EfuseUsedPercentage = *val;
		अवरोध;

	हाल HW_VAR_EFUSE_BYTES:
		pHalData->EfuseUsedBytes = *((u16 *)val);
		अवरोध;

	हाल HW_VAR_EFUSE_BT_USAGE:
#अगर_घोषित HAL_EFUSE_MEMORY
		pHalData->EfuseHal.BTEfuseUsedPercentage = *val;
#पूर्ण_अगर
		अवरोध;

	हाल HW_VAR_EFUSE_BT_BYTES:
#अगर_घोषित HAL_EFUSE_MEMORY
		pHalData->EfuseHal.BTEfuseUsedBytes = *((u16 *)val);
#अन्यथा
		BTEfuseUsedBytes = *((u16 *)val);
#पूर्ण_अगर
		अवरोध;

	हाल HW_VAR_FIFO_CLEARN_UP:
		अणु
			#घोषणा RW_RELEASE_EN		BIT(18)
			#घोषणा RXDMA_IDLE			BIT(17)

			काष्ठा pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
			u8 trycnt = 100;

			/*  छोड़ो tx */
			rtw_ग_लिखो8(padapter, REG_TXPAUSE, 0xff);

			/*  keep sn */
			padapter->xmitpriv.nqos_ssn = rtw_पढ़ो16(padapter, REG_NQOS_SEQ);

			अगर (!pwrpriv->bkeepfwalive) अणु
				/* RX DMA stop */
				val32 = rtw_पढ़ो32(padapter, REG_RXPKT_NUM);
				val32 |= RW_RELEASE_EN;
				rtw_ग_लिखो32(padapter, REG_RXPKT_NUM, val32);
				करो अणु
					val32 = rtw_पढ़ो32(padapter, REG_RXPKT_NUM);
					val32 &= RXDMA_IDLE;
					अगर (val32)
						अवरोध;
				पूर्ण जबतक (--trycnt);

				/*  RQPN Load 0 */
				rtw_ग_लिखो16(padapter, REG_RQPN_NPQ, 0);
				rtw_ग_लिखो32(padapter, REG_RQPN, 0x80000000);
				mdelay(2);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल HW_VAR_APFM_ON_MAC:
		pHalData->bMacPwrCtrlOn = *val;
		अवरोध;

	हाल HW_VAR_NAV_UPPER:
		अणु
			u32 usNavUpper = *((u32 *)val);

			अगर (usNavUpper > HAL_NAV_UPPER_UNIT_8723B * 0xFF)
				अवरोध;

			usNavUpper = DIV_ROUND_UP(usNavUpper,
						  HAL_NAV_UPPER_UNIT_8723B);
			rtw_ग_लिखो8(padapter, REG_NAV_UPPER, (u8)usNavUpper);
		पूर्ण
		अवरोध;

	हाल HW_VAR_H2C_MEDIA_STATUS_RPT:
		अणु
			u16 mstatus_rpt = (*(u16 *)val);
			u8 mstatus, macId;

			mstatus = (u8) (mstatus_rpt & 0xFF);
			macId = (u8)(mstatus_rpt >> 8);
			rtl8723b_set_FwMediaStatusRpt_cmd(padapter, mstatus, macId);
		पूर्ण
		अवरोध;
	हाल HW_VAR_BCN_VALID:
		अणु
			/*  BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2, ग_लिखो 1 to clear, Clear by sw */
			val8 = rtw_पढ़ो8(padapter, REG_TDECTRL+2);
			val8 |= BIT(0);
			rtw_ग_लिखो8(padapter, REG_TDECTRL+2, val8);
		पूर्ण
		अवरोध;

	हाल HW_VAR_DL_BCN_SEL:
		अणु
			/*  SW_BCN_SEL - Port0 */
			val8 = rtw_पढ़ो8(padapter, REG_DWBCN1_CTRL_8723B+2);
			val8 &= ~BIT(4);
			rtw_ग_लिखो8(padapter, REG_DWBCN1_CTRL_8723B+2, val8);
		पूर्ण
		अवरोध;

	हाल HW_VAR_DO_IQK:
		pHalData->bNeedIQK = true;
		अवरोध;

	हाल HW_VAR_DL_RSVD_PAGE:
		अगर (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == true)
			rtl8723b_करोwnload_BTCoex_AP_mode_rsvd_page(padapter);
		अन्यथा
			rtl8723b_करोwnload_rsvd_page(padapter, RT_MEDIA_CONNECT);
		अवरोध;

	हाल HW_VAR_MACID_SLEEP:
		/*  Input is MACID */
		val32 = *(u32 *)val;
		अगर (val32 > 31)
			अवरोध;

		val8 = (u8)val32; /*  macid is between 0~31 */

		val32 = rtw_पढ़ो32(padapter, REG_MACID_SLEEP);
		अगर (val32 & BIT(val8))
			अवरोध;
		val32 |= BIT(val8);
		rtw_ग_लिखो32(padapter, REG_MACID_SLEEP, val32);
		अवरोध;

	हाल HW_VAR_MACID_WAKEUP:
		/*  Input is MACID */
		val32 = *(u32 *)val;
		अगर (val32 > 31)
			अवरोध;

		val8 = (u8)val32; /*  macid is between 0~31 */

		val32 = rtw_पढ़ो32(padapter, REG_MACID_SLEEP);
		अगर (!(val32 & BIT(val8)))
			अवरोध;
		val32 &= ~BIT(val8);
		rtw_ग_लिखो32(padapter, REG_MACID_SLEEP, val32);
		अवरोध;

	शेष:
		SetHwReg(padapter, variable, val);
		अवरोध;
	पूर्ण
पूर्ण

व्योम GetHwReg8723B(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 val8;
	u16 val16;

	चयन (variable) अणु
	हाल HW_VAR_TXPAUSE:
		*val = rtw_पढ़ो8(padapter, REG_TXPAUSE);
		अवरोध;

	हाल HW_VAR_BCN_VALID:
		अणु
			/*  BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2 */
			val8 = rtw_पढ़ो8(padapter, REG_TDECTRL+2);
			*val = (BIT(0) & val8) ? true : false;
		पूर्ण
		अवरोध;

	हाल HW_VAR_FWLPS_RF_ON:
		अणु
			/*  When we halt NIC, we should check अगर FW LPS is leave. */
			u32 valRCR;

			अगर (
				padapter->bSurpriseRemoved  ||
				(adapter_to_pwrctl(padapter)->rf_pwrstate == rf_off)
			) अणु
				/*  If it is in HW/SW Radio OFF or IPS state, we करो not check Fw LPS Leave, */
				/*  because Fw is unload. */
				*val = true;
			पूर्ण अन्यथा अणु
				valRCR = rtw_पढ़ो32(padapter, REG_RCR);
				valRCR &= 0x00070000;
				अगर (valRCR)
					*val = false;
				अन्यथा
					*val = true;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल HW_VAR_EFUSE_USAGE:
		*val = pHalData->EfuseUsedPercentage;
		अवरोध;

	हाल HW_VAR_EFUSE_BYTES:
		*((u16 *)val) = pHalData->EfuseUsedBytes;
		अवरोध;

	हाल HW_VAR_EFUSE_BT_USAGE:
#अगर_घोषित HAL_EFUSE_MEMORY
		*val = pHalData->EfuseHal.BTEfuseUsedPercentage;
#पूर्ण_अगर
		अवरोध;

	हाल HW_VAR_EFUSE_BT_BYTES:
#अगर_घोषित HAL_EFUSE_MEMORY
		*((u16 *)val) = pHalData->EfuseHal.BTEfuseUsedBytes;
#अन्यथा
		*((u16 *)val) = BTEfuseUsedBytes;
#पूर्ण_अगर
		अवरोध;

	हाल HW_VAR_APFM_ON_MAC:
		*val = pHalData->bMacPwrCtrlOn;
		अवरोध;
	हाल HW_VAR_CHK_HI_QUEUE_EMPTY:
		val16 = rtw_पढ़ो16(padapter, REG_TXPKT_EMPTY);
		*val = (val16 & BIT(10)) ? true:false;
		अवरोध;
	शेष:
		GetHwReg(padapter, variable, val);
		अवरोध;
	पूर्ण
पूर्ण

/* Description:
 *	Change शेष setting of specअगरied variable.
 */
u8 SetHalDefVar8723B(काष्ठा adapter *padapter, क्रमागत hal_def_variable variable, व्योम *pval)
अणु
	u8 bResult;

	bResult = _SUCCESS;

	चयन (variable) अणु
	शेष:
		bResult = SetHalDefVar(padapter, variable, pval);
		अवरोध;
	पूर्ण

	वापस bResult;
पूर्ण

/* Description:
 *	Query setting of specअगरied variable.
 */
u8 GetHalDefVar8723B(काष्ठा adapter *padapter, क्रमागत hal_def_variable variable, व्योम *pval)
अणु
	u8 bResult;

	bResult = _SUCCESS;

	चयन (variable) अणु
	हाल HAL_DEF_MAX_RECVBUF_SZ:
		*((u32 *)pval) = MAX_RECVBUF_SZ;
		अवरोध;

	हाल HAL_DEF_RX_PACKET_OFFSET:
		*((u32 *)pval) = RXDESC_SIZE + DRVINFO_SZ*8;
		अवरोध;

	हाल HW_VAR_MAX_RX_AMPDU_FACTOR:
		/*  Stanley@BB.SD3 suggests 16K can get stable perक्रमmance */
		/*  The experiment was करोne on SDIO पूर्णांकerface */
		/*  coding by Lucas@20130730 */
		*(u32 *)pval = IEEE80211_HT_MAX_AMPDU_16K;
		अवरोध;
	हाल HAL_DEF_TX_LDPC:
	हाल HAL_DEF_RX_LDPC:
		*((u8 *)pval) = false;
		अवरोध;
	हाल HAL_DEF_TX_STBC:
		*((u8 *)pval) = 0;
		अवरोध;
	हाल HAL_DEF_RX_STBC:
		*((u8 *)pval) = 1;
		अवरोध;
	हाल HAL_DEF_EXPLICIT_BEAMFORMER:
	हाल HAL_DEF_EXPLICIT_BEAMFORMEE:
		*((u8 *)pval) = false;
		अवरोध;

	हाल HW_DEF_RA_INFO_DUMP:
		अणु
			u8 mac_id = *(u8 *)pval;
			u32 cmd;
			u32 ra_info1, ra_info2;
			u32 rate_mask1, rate_mask2;
			u8 curr_tx_rate, curr_tx_sgi, hight_rate, lowest_rate;

			cmd = 0x40000100 | mac_id;
			rtw_ग_लिखो32(padapter, REG_HMEBOX_DBG_2_8723B, cmd);
			msleep(10);
			ra_info1 = rtw_पढ़ो32(padapter, 0x2F0);
			curr_tx_rate = ra_info1&0x7F;
			curr_tx_sgi = (ra_info1>>7)&0x01;

			cmd = 0x40000400 | mac_id;
			rtw_ग_लिखो32(padapter, REG_HMEBOX_DBG_2_8723B, cmd);
			msleep(10);
			ra_info1 = rtw_पढ़ो32(padapter, 0x2F0);
			ra_info2 = rtw_पढ़ो32(padapter, 0x2F4);
			rate_mask1 = rtw_पढ़ो32(padapter, 0x2F8);
			rate_mask2 = rtw_पढ़ो32(padapter, 0x2FC);
			hight_rate = ra_info2&0xFF;
			lowest_rate = (ra_info2>>8)  & 0xFF;

		पूर्ण
		अवरोध;

	हाल HAL_DEF_TX_PAGE_BOUNDARY:
		अगर (!padapter->registrypriv.wअगरi_spec) अणु
			*(u8 *)pval = TX_PAGE_BOUNDARY_8723B;
		पूर्ण अन्यथा अणु
			*(u8 *)pval = WMM_NORMAL_TX_PAGE_BOUNDARY_8723B;
		पूर्ण
		अवरोध;

	हाल HAL_DEF_MACID_SLEEP:
		*(u8 *)pval = true; /*  support macid sleep */
		अवरोध;

	शेष:
		bResult = GetHalDefVar(padapter, variable, pval);
		अवरोध;
	पूर्ण

	वापस bResult;
पूर्ण

व्योम rtl8723b_start_thपढ़ो(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *xmitpriv = &padapter->xmitpriv;

	xmitpriv->SdioXmitThपढ़ो = kthपढ़ो_run(rtl8723bs_xmit_thपढ़ो, padapter, "RTWHALXT");
पूर्ण

व्योम rtl8723b_stop_thपढ़ो(काष्ठा adapter *padapter)
अणु
	काष्ठा xmit_priv *xmitpriv = &padapter->xmitpriv;

	/*  stop xmit_buf_thपढ़ो */
	अगर (xmitpriv->SdioXmitThपढ़ो) अणु
		complete(&xmitpriv->SdioXmitStart);
		रुको_क्रम_completion(&xmitpriv->SdioXmitTerminate);
		xmitpriv->SdioXmitThपढ़ो = शून्य;
	पूर्ण
पूर्ण
