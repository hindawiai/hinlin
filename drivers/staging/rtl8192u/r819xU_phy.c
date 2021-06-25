<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "r8192U.h"
#समावेश "r8192U_hw.h"
#समावेश "r819xU_phy.h"
#समावेश "r819xU_phyreg.h"
#समावेश "r8190_rtl8256.h"
#समावेश "r8192U_dm.h"
#समावेश "r819xU_firmware_img.h"

#समावेश "ieee80211/dot11d.h"
#समावेश <linux/bitops.h>

अटल u32 RF_CHANNEL_TABLE_ZEBRA[] = अणु
	0,
	0x085c, /* 2412 1  */
	0x08dc, /* 2417 2  */
	0x095c, /* 2422 3  */
	0x09dc, /* 2427 4  */
	0x0a5c, /* 2432 5  */
	0x0adc, /* 2437 6  */
	0x0b5c, /* 2442 7  */
	0x0bdc, /* 2447 8  */
	0x0c5c, /* 2452 9  */
	0x0cdc, /* 2457 10 */
	0x0d5c, /* 2462 11 */
	0x0ddc, /* 2467 12 */
	0x0e5c, /* 2472 13 */
	0x0f72, /* 2484    */
पूर्ण;

#घोषणा rtl819XMACPHY_Array Rtl8192UsbMACPHY_Array

/******************************************************************************
 * function:  This function checks dअगरferent RF type to execute legal judgement.
 *            If RF Path is illegal, we will वापस false.
 * input:     net_device	 *dev
 *            u32		 e_rfpath
 * output:    none
 * वापस:    0(illegal, false), 1(legal, true)
 *****************************************************************************/
u8 rtl8192_phy_CheckIsLegalRFPath(काष्ठा net_device *dev, u32 e_rfpath)
अणु
	u8 ret = 1;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->rf_type == RF_2T4R) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (priv->rf_type == RF_1T2R) अणु
		अगर (e_rfpath == RF90_PATH_A || e_rfpath == RF90_PATH_B)
			ret = 1;
		अन्यथा अगर (e_rfpath == RF90_PATH_C || e_rfpath == RF90_PATH_D)
			ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

/******************************************************************************
 * function:  This function sets specअगरic bits to BB रेजिस्टर
 * input:     net_device *dev
 *            u32        reg_addr   //target addr to be modअगरied
 *            u32        biपंचांगask    //taget bit pos to be modअगरied
 *            u32        data       //value to be ग_लिखो
 * output:    none
 * वापस:    none
 * notice:
 ******************************************************************************/
व्योम rtl8192_setBBreg(काष्ठा net_device *dev, u32 reg_addr, u32 biपंचांगask,
		      u32 data)
अणु
	u32 reg, bitshअगरt;

	अगर (biपंचांगask != bMaskDWord) अणु
		पढ़ो_nic_dword(dev, reg_addr, &reg);
		bitshअगरt = ffs(biपंचांगask) - 1;
		reg &= ~biपंचांगask;
		reg |= data << bitshअगरt;
		ग_लिखो_nic_dword(dev, reg_addr, reg);
	पूर्ण अन्यथा अणु
		ग_लिखो_nic_dword(dev, reg_addr, data);
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function पढ़ोs specअगरic bits from BB रेजिस्टर
 * input:     net_device	*dev
 *            u32		reg_addr   //target addr to be पढ़ोback
 *            u32		biपंचांगask    //taget bit pos to be पढ़ोback
 * output:    none
 * वापस:    u32		data       //the पढ़ोback रेजिस्टर value
 * notice:
 ******************************************************************************/
u32 rtl8192_QueryBBReg(काष्ठा net_device *dev, u32 reg_addr, u32 biपंचांगask)
अणु
	u32 reg, bitshअगरt;

	पढ़ो_nic_dword(dev, reg_addr, &reg);
	bitshअगरt = ffs(biपंचांगask) - 1;

	वापस (reg & biपंचांगask) >> bitshअगरt;
पूर्ण

अटल u32 phy_FwRFSerialRead(काष्ठा net_device *dev,
			      क्रमागत rf90_radio_path_e e_rfpath,
			      u32 offset);

अटल व्योम phy_FwRFSerialWrite(काष्ठा net_device *dev,
				क्रमागत rf90_radio_path_e e_rfpath,
				u32  offset,
				u32  data);

/******************************************************************************
 * function:  This function पढ़ोs रेजिस्टर from RF chip
 * input:     net_device        *dev
 *            rf90_radio_path_e e_rfpath    //radio path of A/B/C/D
 *            u32               offset     //target address to be पढ़ो
 * output:    none
 * वापस:    u32               पढ़ोback value
 * notice:    There are three types of serial operations:
 *            (1) Software serial ग_लिखो.
 *            (2)Hardware LSSI-Low Speed Serial Interface.
 *            (3)Hardware HSSI-High speed serial ग_लिखो.
 *            Driver here need to implement (1) and (2)
 *            ---need more spec क्रम this inक्रमmation.
 ******************************************************************************/
अटल u32 rtl8192_phy_RFSerialRead(काष्ठा net_device *dev,
				    क्रमागत rf90_radio_path_e e_rfpath, u32 offset)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 ret = 0;
	u32 new_offset = 0;
	BB_REGISTER_DEFINITION_T *pPhyReg = &priv->PHYRegDef[e_rfpath];

	rtl8192_setBBreg(dev, pPhyReg->rfLSSIReadBack, bLSSIReadBackData, 0);
	/* Make sure RF रेजिस्टर offset is correct */
	offset &= 0x3f;

	/* Switch page क्रम 8256 RF IC */
	अगर (priv->rf_chip == RF_8256) अणु
		अगर (offset >= 31) अणु
			priv->RfReg0Value[e_rfpath] |= 0x140;
			/* Switch to Reg_Mode2 क्रम Reg 31-45 */
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath]<<16);
			/* Modअगरy offset */
			new_offset = offset - 30;
		पूर्ण अन्यथा अगर (offset >= 16) अणु
			priv->RfReg0Value[e_rfpath] |= 0x100;
			priv->RfReg0Value[e_rfpath] &= (~0x40);
			/* Switch to Reg_Mode1 क्रम Reg16-30 */
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath]<<16);

			new_offset = offset - 15;
		पूर्ण अन्यथा अणु
			new_offset = offset;
		पूर्ण
	पूर्ण अन्यथा अणु
		RT_TRACE((COMP_PHY|COMP_ERR),
			 "check RF type here, need to be 8256\n");
		new_offset = offset;
	पूर्ण
	/* Put desired पढ़ो addr to LSSI control Register */
	rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, bLSSIReadAddress,
			 new_offset);
	/* Issue a posedge trigger */
	rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2,  bLSSIReadEdge, 0x0);
	rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2,  bLSSIReadEdge, 0x1);

	/* TODO: we should not delay such a दीर्घ समय. Ask क्रम help from SD3 */
	usleep_range(1000, 1000);

	ret = rtl8192_QueryBBReg(dev, pPhyReg->rfLSSIReadBack,
				 bLSSIReadBackData);

	/* Switch back to Reg_Mode0 */
	अगर (priv->rf_chip == RF_8256) अणु
		priv->RfReg0Value[e_rfpath] &= 0xebf;

		rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset, bMaskDWord,
				 priv->RfReg0Value[e_rfpath] << 16);
	पूर्ण

	वापस ret;
पूर्ण

/******************************************************************************
 * function:  This function ग_लिखोs data to RF रेजिस्टर
 * input:     net_device        *dev
 *            rf90_radio_path_e e_rfpath  //radio path of A/B/C/D
 *            u32               offset   //target address to be written
 *            u32               data	 //the new रेजिस्टर data to be written
 * output:    none
 * वापस:    none
 * notice:    For RF8256 only.
 * ===========================================================================
 * Reg Mode	RegCTL[1]	RegCTL[0]		Note
 *		(Reg00[12])	(Reg00[10])
 * ===========================================================================
 * Reg_Mode0	0		x			Reg 0 ~ 15(0x0 ~ 0xf)
 * ---------------------------------------------------------------------------
 * Reg_Mode1	1		0			Reg 16 ~ 30(0x1 ~ 0xf)
 * ---------------------------------------------------------------------------
 * Reg_Mode2	1		1			Reg 31 ~ 45(0x1 ~ 0xf)
 * ---------------------------------------------------------------------------
 *****************************************************************************/
अटल व्योम rtl8192_phy_RFSerialWrite(काष्ठा net_device *dev,
				      क्रमागत rf90_radio_path_e e_rfpath,
				      u32 offset,
				      u32 data)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 DataAndAddr = 0, new_offset = 0;
	BB_REGISTER_DEFINITION_T	*pPhyReg = &priv->PHYRegDef[e_rfpath];

	offset &= 0x3f;
	अगर (priv->rf_chip == RF_8256) अणु
		अगर (offset >= 31) अणु
			priv->RfReg0Value[e_rfpath] |= 0x140;
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath] << 16);
			new_offset = offset - 30;
		पूर्ण अन्यथा अगर (offset >= 16) अणु
			priv->RfReg0Value[e_rfpath] |= 0x100;
			priv->RfReg0Value[e_rfpath] &= (~0x40);
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath]<<16);
			new_offset = offset - 15;
		पूर्ण अन्यथा अणु
			new_offset = offset;
		पूर्ण
	पूर्ण अन्यथा अणु
		RT_TRACE((COMP_PHY|COMP_ERR),
			 "check RF type here, need to be 8256\n");
		new_offset = offset;
	पूर्ण

	/* Put ग_लिखो addr in [5:0] and ग_लिखो data in [31:16] */
	DataAndAddr = (data<<16) | (new_offset&0x3f);

	/* Write operation */
	rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset, bMaskDWord, DataAndAddr);

	अगर (offset == 0x0)
		priv->RfReg0Value[e_rfpath] = data;

	/* Switch back to Reg_Mode0 */
	अगर (priv->rf_chip == RF_8256) अणु
		अगर (offset != 0) अणु
			priv->RfReg0Value[e_rfpath] &= 0xebf;
			rtl8192_setBBreg(dev, pPhyReg->rf3wireOffset,
					 bMaskDWord,
					 priv->RfReg0Value[e_rfpath] << 16);
		पूर्ण
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function set specअगरic bits to RF रेजिस्टर
 * input:     net_device        dev
 *            rf90_radio_path_e e_rfpath  //radio path of A/B/C/D
 *            u32               reg_addr //target addr to be modअगरied
 *            u32               biपंचांगask  //taget bit pos to be modअगरied
 *            u32               data     //value to be written
 * output:    none
 * वापस:    none
 * notice:
 *****************************************************************************/
व्योम rtl8192_phy_SetRFReg(काष्ठा net_device *dev,
			  क्रमागत rf90_radio_path_e e_rfpath,
			  u32 reg_addr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32 reg, bitshअगरt;

	अगर (!rtl8192_phy_CheckIsLegalRFPath(dev, e_rfpath))
		वापस;

	अगर (priv->Rf_Mode == RF_OP_By_FW) अणु
		अगर (biपंचांगask != bMask12Bits) अणु
			/* RF data is 12 bits only */
			reg = phy_FwRFSerialRead(dev, e_rfpath, reg_addr);
			bitshअगरt =  ffs(biपंचांगask) - 1;
			reg &= ~biपंचांगask;
			reg |= data << bitshअगरt;

			phy_FwRFSerialWrite(dev, e_rfpath, reg_addr, reg);
		पूर्ण अन्यथा अणु
			phy_FwRFSerialWrite(dev, e_rfpath, reg_addr, data);
		पूर्ण

		udelay(200);

	पूर्ण अन्यथा अणु
		अगर (biपंचांगask != bMask12Bits) अणु
			/* RF data is 12 bits only */
			reg = rtl8192_phy_RFSerialRead(dev, e_rfpath, reg_addr);
			bitshअगरt =  ffs(biपंचांगask) - 1;
			reg &= ~biपंचांगask;
			reg |= data << bitshअगरt;

			rtl8192_phy_RFSerialWrite(dev, e_rfpath, reg_addr, reg);
		पूर्ण अन्यथा अणु
			rtl8192_phy_RFSerialWrite(dev, e_rfpath, reg_addr, data);
		पूर्ण
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function पढ़ोs specअगरic bits from RF रेजिस्टर
 * input:     net_device        *dev
 *            u32               reg_addr //target addr to be पढ़ोback
 *            u32               biपंचांगask  //taget bit pos to be पढ़ोback
 * output:    none
 * वापस:    u32               data     //the पढ़ोback रेजिस्टर value
 * notice:
 *****************************************************************************/
u32 rtl8192_phy_QueryRFReg(काष्ठा net_device *dev,
			   क्रमागत rf90_radio_path_e e_rfpath,
			   u32 reg_addr, u32 biपंचांगask)
अणु
	u32 reg, bitshअगरt;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (!rtl8192_phy_CheckIsLegalRFPath(dev, e_rfpath))
		वापस 0;
	अगर (priv->Rf_Mode == RF_OP_By_FW) अणु
		reg = phy_FwRFSerialRead(dev, e_rfpath, reg_addr);
		udelay(200);
	पूर्ण अन्यथा अणु
		reg = rtl8192_phy_RFSerialRead(dev, e_rfpath, reg_addr);
	पूर्ण
	bitshअगरt =  ffs(biपंचांगask) - 1;
	reg = (reg & biपंचांगask) >> bitshअगरt;
	वापस reg;
पूर्ण

/******************************************************************************
 * function:  We support firmware to execute RF-R/W.
 * input:     net_device        *dev
 *            rf90_radio_path_e e_rfpath
 *            u32               offset
 * output:    none
 * वापस:    u32
 * notice:
 ****************************************************************************/
अटल u32 phy_FwRFSerialRead(काष्ठा net_device *dev,
			      क्रमागत rf90_radio_path_e e_rfpath,
			      u32 offset)
अणु
	u32		reg = 0;
	u32		data = 0;
	u8		समय = 0;
	u32		पंचांगp;

	/* Firmware RF Write control.
	 * We can not execute the scheme in the initial step.
	 * Otherwise, RF-R/W will waste much समय.
	 * This is only क्रम site survey.
	 */
	/* 1. Read operation need not insert data. bit 0-11 */
	/* 2. Write RF रेजिस्टर address. bit 12-19 */
	data |= ((offset&0xFF)<<12);
	/* 3. Write RF path.  bit 20-21 */
	data |= ((e_rfpath&0x3)<<20);
	/* 4. Set RF पढ़ो indicator. bit 22=0 */
	/* 5. Trigger Fw to operate the command. bit 31 */
	data |= 0x80000000;
	/* 6. We can not execute पढ़ो operation अगर bit 31 is 1. */
	पढ़ो_nic_dword(dev, QPNR, &पंचांगp);
	जबतक (पंचांगp & 0x80000000) अणु
		/* If FW can not finish RF-R/W क्रम more than ?? बार.
		 * We must reset FW.
		 */
		अगर (समय++ < 100) अणु
			udelay(10);
			पढ़ो_nic_dword(dev, QPNR, &पंचांगp);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	/* 7. Execute पढ़ो operation. */
	ग_लिखो_nic_dword(dev, QPNR, data);
	/* 8. Check अगर firmware send back RF content. */
	पढ़ो_nic_dword(dev, QPNR, &पंचांगp);
	जबतक (पंचांगp & 0x80000000) अणु
		/* If FW can not finish RF-R/W क्रम more than ?? बार.
		 * We must reset FW.
		 */
		अगर (समय++ < 100) अणु
			udelay(10);
			पढ़ो_nic_dword(dev, QPNR, &पंचांगp);
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण
	पढ़ो_nic_dword(dev, RF_DATA, &reg);

	वापस reg;
पूर्ण

/******************************************************************************
 * function:  We support firmware to execute RF-R/W.
 * input:     net_device        *dev
 *            rf90_radio_path_e e_rfpath
 *            u32               offset
 *            u32               data
 * output:    none
 * वापस:    none
 * notice:
 ****************************************************************************/
अटल व्योम phy_FwRFSerialWrite(काष्ठा net_device *dev,
				क्रमागत rf90_radio_path_e e_rfpath,
				u32 offset, u32 data)
अणु
	u8	समय = 0;
	u32	पंचांगp;

	/* Firmware RF Write control.
	 * We can not execute the scheme in the initial step.
	 * Otherwise, RF-R/W will waste much समय.
	 * This is only क्रम site survey.
	 */

	/* 1. Set driver ग_लिखो bit and 12 bit data. bit 0-11 */
	/* 2. Write RF रेजिस्टर address. bit 12-19 */
	data |= ((offset&0xFF)<<12);
	/* 3. Write RF path.  bit 20-21 */
	data |= ((e_rfpath&0x3)<<20);
	/* 4. Set RF ग_लिखो indicator. bit 22=1 */
	data |= 0x400000;
	/* 5. Trigger Fw to operate the command. bit 31=1 */
	data |= 0x80000000;

	/* 6. Write operation. We can not ग_लिखो अगर bit 31 is 1. */
	पढ़ो_nic_dword(dev, QPNR, &पंचांगp);
	जबतक (पंचांगp & 0x80000000) अणु
		/* If FW can not finish RF-R/W क्रम more than ?? बार.
		 * We must reset FW.
		 */
		अगर (समय++ < 100) अणु
			udelay(10);
			पढ़ो_nic_dword(dev, QPNR, &पंचांगp);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	/* 7. No matter check bit. We always क्रमce the ग_लिखो.
	 * Because FW will not accept the command.
	 */
	ग_लिखो_nic_dword(dev, QPNR, data);
	/* According to test, we must delay 20us to रुको firmware
	 * to finish RF ग_लिखो operation.
	 */
	/* We support delay in firmware side now. */
पूर्ण

/******************************************************************************
 * function:  This function पढ़ोs BB parameters from header file we generate,
 *            and करो रेजिस्टर पढ़ो/ग_लिखो
 * input:     net_device	*dev
 * output:    none
 * वापस:    none
 * notice:    BB parameters may change all the समय, so please make
 *            sure it has been synced with the newest.
 *****************************************************************************/
व्योम rtl8192_phy_configmac(काष्ठा net_device *dev)
अणु
	u32 dwArrayLen = 0, i;
	u32 *pdwArray = शून्य;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->btxघातerdata_पढ़ोfromEEPORM) अणु
		RT_TRACE(COMP_PHY, "Rtl819XMACPHY_Array_PG\n");
		dwArrayLen = MACPHY_Array_PGLength;
		pdwArray = Rtl8192UsbMACPHY_Array_PG;

	पूर्ण अन्यथा अणु
		RT_TRACE(COMP_PHY, "Rtl819XMACPHY_Array\n");
		dwArrayLen = MACPHY_ArrayLength;
		pdwArray = rtl819XMACPHY_Array;
	पूर्ण
	क्रम (i = 0; i < dwArrayLen; i = i+3) अणु
		अगर (pdwArray[i] == 0x318)
			pdwArray[i+2] = 0x00000800;

		RT_TRACE(COMP_DBG,
			 "Rtl8190MACPHY_Array[0]=%x Rtl8190MACPHY_Array[1]=%x Rtl8190MACPHY_Array[2]=%x\n",
			 pdwArray[i], pdwArray[i+1], pdwArray[i+2]);
		rtl8192_setBBreg(dev, pdwArray[i], pdwArray[i+1],
				 pdwArray[i+2]);
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function करोes dirty work
 * input:     net_device	*dev
 *            u8                ConfigType
 * output:    none
 * वापस:    none
 * notice:    BB parameters may change all the समय, so please make
 *            sure it has been synced with the newest.
 *****************************************************************************/
अटल व्योम rtl8192_phyConfigBB(काष्ठा net_device *dev,
				क्रमागत baseband_config_type ConfigType)
अणु
	u32 i;

	अगर (ConfigType == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < PHY_REG_1T2RArrayLength; i += 2) अणु
			rtl8192_setBBreg(dev, Rtl8192UsbPHY_REG_1T2RArray[i],
					 bMaskDWord,
					 Rtl8192UsbPHY_REG_1T2RArray[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, Rtl819xUsbPHY_REGArray[0]=%x Rtl819xUsbPHY_REGArray[1]=%x\n",
				 i, Rtl8192UsbPHY_REG_1T2RArray[i],
				 Rtl8192UsbPHY_REG_1T2RArray[i+1]);
		पूर्ण
	पूर्ण अन्यथा अगर (ConfigType == BASEBAND_CONFIG_AGC_TAB) अणु
		क्रम (i = 0; i < AGCTAB_ArrayLength; i += 2) अणु
			rtl8192_setBBreg(dev, Rtl8192UsbAGCTAB_Array[i],
					 bMaskDWord, Rtl8192UsbAGCTAB_Array[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, Rtl8192UsbAGCTAB_Array[0]=%x Rtl8192UsbAGCTAB_Array[1]=%x\n",
				 i, Rtl8192UsbAGCTAB_Array[i],
				 Rtl8192UsbAGCTAB_Array[i+1]);
		पूर्ण
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function initializes Register definition offset क्रम
 *            Radio Path A/B/C/D
 * input:     net_device	*dev
 * output:    none
 * वापस:    none
 * notice:    Initialization value here is स्थिरant and it should never
 *            be changed
 *****************************************************************************/
अटल व्योम rtl8192_InitBBRFRegDef(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* RF Interface Software Control */
	/* 16 LSBs अगर पढ़ो 32-bit from 0x870 */
	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfs = rFPGA0_XAB_RFInterfaceSW;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x870 (16-bit क्रम 0x872) */
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfs = rFPGA0_XAB_RFInterfaceSW;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x874 */
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfs = rFPGA0_XCD_RFInterfaceSW;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x874 (16-bit क्रम 0x876) */
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfs = rFPGA0_XCD_RFInterfaceSW;

	/* RF Interface Readback Value */
	/* 16 LSBs अगर पढ़ो 32-bit from 0x8E0 */
	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfi = rFPGA0_XAB_RFInterfaceRB;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x8E0 (16-bit क्रम 0x8E2) */
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfi = rFPGA0_XAB_RFInterfaceRB;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x8E4 */
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfi = rFPGA0_XCD_RFInterfaceRB;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x8E4 (16-bit क्रम 0x8E6) */
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfi = rFPGA0_XCD_RFInterfaceRB;

	/* RF Interface Output (and Enable) */
	/* 16 LSBs अगर पढ़ो 32-bit from 0x860 */
	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfo = rFPGA0_XA_RFInterfaceOE;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x864 */
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfo = rFPGA0_XB_RFInterfaceOE;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x868 */
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfo = rFPGA0_XC_RFInterfaceOE;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x86C */
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfo = rFPGA0_XD_RFInterfaceOE;

	/* RF Interface (Output and) Enable */
	/* 16 MSBs अगर पढ़ो 32-bit from 0x860 (16-bit क्रम 0x862) */
	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfe = rFPGA0_XA_RFInterfaceOE;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x864 (16-bit क्रम 0x866) */
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfe = rFPGA0_XB_RFInterfaceOE;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x86A (16-bit क्रम 0x86A) */
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfe = rFPGA0_XC_RFInterfaceOE;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x86C (16-bit क्रम 0x86E) */
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfe = rFPGA0_XD_RFInterfaceOE;

	/* Addr of LSSI. Write RF रेजिस्टर by driver */
	priv->PHYRegDef[RF90_PATH_A].rf3wireOffset = rFPGA0_XA_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_B].rf3wireOffset = rFPGA0_XB_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_C].rf3wireOffset = rFPGA0_XC_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_D].rf3wireOffset = rFPGA0_XD_LSSIParameter;

	/* RF parameter */
	/* BB Band Select */
	priv->PHYRegDef[RF90_PATH_A].rfLSSI_Select = rFPGA0_XAB_RFParameter;
	priv->PHYRegDef[RF90_PATH_B].rfLSSI_Select = rFPGA0_XAB_RFParameter;
	priv->PHYRegDef[RF90_PATH_C].rfLSSI_Select = rFPGA0_XCD_RFParameter;
	priv->PHYRegDef[RF90_PATH_D].rfLSSI_Select = rFPGA0_XCD_RFParameter;

	/* Tx AGC Gain Stage (same क्रम all path. Should we हटाओ this?) */
	priv->PHYRegDef[RF90_PATH_A].rfTxGainStage = rFPGA0_TxGainStage;
	priv->PHYRegDef[RF90_PATH_B].rfTxGainStage = rFPGA0_TxGainStage;
	priv->PHYRegDef[RF90_PATH_C].rfTxGainStage = rFPGA0_TxGainStage;
	priv->PHYRegDef[RF90_PATH_D].rfTxGainStage = rFPGA0_TxGainStage;

	/* Tranceiver A~D HSSI Parameter-1 */
	/* wire control parameter1 */
	priv->PHYRegDef[RF90_PATH_A].rfHSSIPara1 = rFPGA0_XA_HSSIParameter1;
	priv->PHYRegDef[RF90_PATH_B].rfHSSIPara1 = rFPGA0_XB_HSSIParameter1;
	priv->PHYRegDef[RF90_PATH_C].rfHSSIPara1 = rFPGA0_XC_HSSIParameter1;
	priv->PHYRegDef[RF90_PATH_D].rfHSSIPara1 = rFPGA0_XD_HSSIParameter1;

	/* Tranceiver A~D HSSI Parameter-2 */
	/* wire control parameter2 */
	priv->PHYRegDef[RF90_PATH_A].rfHSSIPara2 = rFPGA0_XA_HSSIParameter2;
	priv->PHYRegDef[RF90_PATH_B].rfHSSIPara2 = rFPGA0_XB_HSSIParameter2;
	priv->PHYRegDef[RF90_PATH_C].rfHSSIPara2 = rFPGA0_XC_HSSIParameter2;
	priv->PHYRegDef[RF90_PATH_D].rfHSSIPara2 = rFPGA0_XD_HSSIParameter2;

	/* RF Switch Control */
	/* TR/Ant चयन control */
	priv->PHYRegDef[RF90_PATH_A].rfSwitchControl = rFPGA0_XAB_SwitchControl;
	priv->PHYRegDef[RF90_PATH_B].rfSwitchControl = rFPGA0_XAB_SwitchControl;
	priv->PHYRegDef[RF90_PATH_C].rfSwitchControl = rFPGA0_XCD_SwitchControl;
	priv->PHYRegDef[RF90_PATH_D].rfSwitchControl = rFPGA0_XCD_SwitchControl;

	/* AGC control 1 */
	priv->PHYRegDef[RF90_PATH_A].rfAGCControl1 = rOFDM0_XAAGCCore1;
	priv->PHYRegDef[RF90_PATH_B].rfAGCControl1 = rOFDM0_XBAGCCore1;
	priv->PHYRegDef[RF90_PATH_C].rfAGCControl1 = rOFDM0_XCAGCCore1;
	priv->PHYRegDef[RF90_PATH_D].rfAGCControl1 = rOFDM0_XDAGCCore1;

	/* AGC control 2 */
	priv->PHYRegDef[RF90_PATH_A].rfAGCControl2 = rOFDM0_XAAGCCore2;
	priv->PHYRegDef[RF90_PATH_B].rfAGCControl2 = rOFDM0_XBAGCCore2;
	priv->PHYRegDef[RF90_PATH_C].rfAGCControl2 = rOFDM0_XCAGCCore2;
	priv->PHYRegDef[RF90_PATH_D].rfAGCControl2 = rOFDM0_XDAGCCore2;

	/* RX AFE control 1 */
	priv->PHYRegDef[RF90_PATH_A].rfRxIQImbalance = rOFDM0_XARxIQImbalance;
	priv->PHYRegDef[RF90_PATH_B].rfRxIQImbalance = rOFDM0_XBRxIQImbalance;
	priv->PHYRegDef[RF90_PATH_C].rfRxIQImbalance = rOFDM0_XCRxIQImbalance;
	priv->PHYRegDef[RF90_PATH_D].rfRxIQImbalance = rOFDM0_XDRxIQImbalance;

	/* RX AFE control 1 */
	priv->PHYRegDef[RF90_PATH_A].rfRxAFE = rOFDM0_XARxAFE;
	priv->PHYRegDef[RF90_PATH_B].rfRxAFE = rOFDM0_XBRxAFE;
	priv->PHYRegDef[RF90_PATH_C].rfRxAFE = rOFDM0_XCRxAFE;
	priv->PHYRegDef[RF90_PATH_D].rfRxAFE = rOFDM0_XDRxAFE;

	/* Tx AFE control 1 */
	priv->PHYRegDef[RF90_PATH_A].rfTxIQImbalance = rOFDM0_XATxIQImbalance;
	priv->PHYRegDef[RF90_PATH_B].rfTxIQImbalance = rOFDM0_XBTxIQImbalance;
	priv->PHYRegDef[RF90_PATH_C].rfTxIQImbalance = rOFDM0_XCTxIQImbalance;
	priv->PHYRegDef[RF90_PATH_D].rfTxIQImbalance = rOFDM0_XDTxIQImbalance;

	/* Tx AFE control 2 */
	priv->PHYRegDef[RF90_PATH_A].rfTxAFE = rOFDM0_XATxAFE;
	priv->PHYRegDef[RF90_PATH_B].rfTxAFE = rOFDM0_XBTxAFE;
	priv->PHYRegDef[RF90_PATH_C].rfTxAFE = rOFDM0_XCTxAFE;
	priv->PHYRegDef[RF90_PATH_D].rfTxAFE = rOFDM0_XDTxAFE;

	/* Tranceiver LSSI Readback */
	priv->PHYRegDef[RF90_PATH_A].rfLSSIReadBack = rFPGA0_XA_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_B].rfLSSIReadBack = rFPGA0_XB_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_C].rfLSSIReadBack = rFPGA0_XC_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_D].rfLSSIReadBack = rFPGA0_XD_LSSIReadBack;
पूर्ण

/******************************************************************************
 * function:  This function is to ग_लिखो रेजिस्टर and then पढ़ोback to make
 *            sure whether BB and RF is OK
 * input:     net_device        *dev
 *            hw90_block_e      CheckBlock
 *            rf90_radio_path_e e_rfpath  //only used when checkblock is
 *                                       //HW90_BLOCK_RF
 * output:    none
 * वापस:    वापस whether BB and RF is ok (0:OK, 1:Fail)
 * notice:    This function may be हटाओd in the ASIC
 ******************************************************************************/
u8 rtl8192_phy_checkBBAndRF(काष्ठा net_device *dev, क्रमागत hw90_block_e CheckBlock,
			    क्रमागत rf90_radio_path_e e_rfpath)
अणु
	u8 ret = 0;
	u32 i, CheckTimes = 4, reg = 0;
	u32 WriteAddr[4];
	u32 WriteData[] = अणु0xfffff027, 0xaa55a02f, 0x00000027, 0x55aa502fपूर्ण;

	/* Initialize रेजिस्टर address offset to be checked */
	WriteAddr[HW90_BLOCK_MAC] = 0x100;
	WriteAddr[HW90_BLOCK_PHY0] = 0x900;
	WriteAddr[HW90_BLOCK_PHY1] = 0x800;
	WriteAddr[HW90_BLOCK_RF] = 0x3;
	RT_TRACE(COMP_PHY, "%s(), CheckBlock: %d\n", __func__, CheckBlock);
	क्रम (i = 0; i < CheckTimes; i++) अणु
		/* Write data to रेजिस्टर and पढ़ोback */
		चयन (CheckBlock) अणु
		हाल HW90_BLOCK_MAC:
			RT_TRACE(COMP_ERR,
				 "PHY_CheckBBRFOK(): Never Write 0x100 here!\n");
			अवरोध;

		हाल HW90_BLOCK_PHY0:
		हाल HW90_BLOCK_PHY1:
			ग_लिखो_nic_dword(dev, WriteAddr[CheckBlock],
					WriteData[i]);
			पढ़ो_nic_dword(dev, WriteAddr[CheckBlock], &reg);
			अवरोध;

		हाल HW90_BLOCK_RF:
			WriteData[i] &= 0xfff;
			rtl8192_phy_SetRFReg(dev, e_rfpath,
					     WriteAddr[HW90_BLOCK_RF],
					     bMask12Bits, WriteData[i]);
			/* TODO: we should not delay क्रम such a दीर्घ समय.
			 * Ask SD3
			 */
			usleep_range(1000, 1000);
			reg = rtl8192_phy_QueryRFReg(dev, e_rfpath,
						     WriteAddr[HW90_BLOCK_RF],
						     bMask12Bits);
			usleep_range(1000, 1000);
			अवरोध;

		शेष:
			ret = 1;
			अवरोध;
		पूर्ण

		/* Check whether पढ़ोback data is correct */
		अगर (reg != WriteData[i]) अणु
			RT_TRACE((COMP_PHY|COMP_ERR),
				 "error reg: %x, WriteData: %x\n",
				 reg, WriteData[i]);
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/******************************************************************************
 * function:  This function initializes BB&RF
 * input:     net_device	*dev
 * output:    none
 * वापस:    none
 * notice:    Initialization value may change all the समय, so please make
 *            sure it has been synced with the newest.
 ******************************************************************************/
अटल व्योम rtl8192_BB_Config_ParaFile(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 reg_u8 = 0, eCheckItem = 0, status = 0;
	u32 reg_u32 = 0;

	/**************************************
	 * <1> Initialize BaseBand
	 *************************************/

	/* --set BB Global Reset-- */
	पढ़ो_nic_byte(dev, BB_GLOBAL_RESET, &reg_u8);
	ग_लिखो_nic_byte(dev, BB_GLOBAL_RESET, (reg_u8|BB_GLOBAL_RESET_BIT));
	mdelay(50);
	/* ---set BB reset Active--- */
	पढ़ो_nic_dword(dev, CPU_GEN, &reg_u32);
	ग_लिखो_nic_dword(dev, CPU_GEN, (reg_u32&(~CPU_GEN_BB_RST)));

	/* ----Ckeck FPGAPHY0 and PHY1 board is OK---- */
	/* TODO: this function should be हटाओd on ASIC */
	क्रम (eCheckItem = (क्रमागत hw90_block_e)HW90_BLOCK_PHY0;
	     eCheckItem <= HW90_BLOCK_PHY1; eCheckItem++) अणु
		/* करोn't care RF path */
		status = rtl8192_phy_checkBBAndRF(dev, (क्रमागत hw90_block_e)eCheckItem,
						  (क्रमागत rf90_radio_path_e)0);
		अगर (status != 0) अणु
			RT_TRACE((COMP_ERR | COMP_PHY),
				 "phy_rf8256_config(): Check PHY%d Fail!!\n",
				 eCheckItem-1);
			वापस;
		पूर्ण
	पूर्ण
	/* ---- Set CCK and OFDM Block "OFF"---- */
	rtl8192_setBBreg(dev, rFPGA0_RFMOD, bCCKEn|bOFDMEn, 0x0);
	/* ----BB Register Initilazation---- */
	/* ==m==>Set PHY REG From Header<==m== */
	rtl8192_phyConfigBB(dev, BASEBAND_CONFIG_PHY_REG);

	/* ----Set BB reset de-Active---- */
	पढ़ो_nic_dword(dev, CPU_GEN, &reg_u32);
	ग_लिखो_nic_dword(dev, CPU_GEN, (reg_u32|CPU_GEN_BB_RST));

	/* ----BB AGC table Initialization---- */
	/* ==m==>Set PHY REG From Header<==m== */
	rtl8192_phyConfigBB(dev, BASEBAND_CONFIG_AGC_TAB);

	/* ----Enable XSTAL ---- */
	ग_लिखो_nic_byte_E(dev, 0x5e, 0x00);
	अगर (priv->card_8192_version == VERSION_819XU_A) अणु
		/* Antenna gain offset from B/C/D to A */
		reg_u32 = priv->AntennaTxPwDअगरf[1]<<4 |
			   priv->AntennaTxPwDअगरf[0];
		rtl8192_setBBreg(dev, rFPGA0_TxGainStage, (bXBTxAGC|bXCTxAGC),
				 reg_u32);

		/* XSTALLCap */
		reg_u32 = priv->CrystalCap & 0xf;
		rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, bXtalCap,
				 reg_u32);
	पूर्ण

	/* Check अगर the CCK HighPower is turned ON.
	 * This is used to calculate PWDB.
	 */
	priv->bCckHighPower = (u8)rtl8192_QueryBBReg(dev,
						     rFPGA0_XA_HSSIParameter2,
						     0x200);
पूर्ण

/******************************************************************************
 * function:  This function initializes BB&RF
 * input:     net_device	*dev
 * output:    none
 * वापस:    none
 * notice:    Initialization value may change all the समय, so please make
 *            sure it has been synced with the newest.
 *****************************************************************************/
व्योम rtl8192_BBConfig(काष्ठा net_device *dev)
अणु
	rtl8192_InitBBRFRegDef(dev);
	/* config BB&RF. As hardCode based initialization has not been well
	 * implemented, so use file first.
	 * FIXME: should implement it क्रम hardcode?
	 */
	rtl8192_BB_Config_ParaFile(dev);
पूर्ण

/******************************************************************************
 * function:  This function obtains the initialization value of Tx घातer Level
 *            offset
 * input:     net_device	*dev
 * output:    none
 * वापस:    none
 *****************************************************************************/
व्योम rtl8192_phy_getTxPower(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 पंचांगp;

	पढ़ो_nic_dword(dev, rTxAGC_Rate18_06,
		       &priv->MCSTxPowerLevelOriginalOffset[0]);
	पढ़ो_nic_dword(dev, rTxAGC_Rate54_24,
		       &priv->MCSTxPowerLevelOriginalOffset[1]);
	पढ़ो_nic_dword(dev, rTxAGC_Mcs03_Mcs00,
		       &priv->MCSTxPowerLevelOriginalOffset[2]);
	पढ़ो_nic_dword(dev, rTxAGC_Mcs07_Mcs04,
		       &priv->MCSTxPowerLevelOriginalOffset[3]);
	पढ़ो_nic_dword(dev, rTxAGC_Mcs11_Mcs08,
		       &priv->MCSTxPowerLevelOriginalOffset[4]);
	पढ़ो_nic_dword(dev, rTxAGC_Mcs15_Mcs12,
		       &priv->MCSTxPowerLevelOriginalOffset[5]);

	/* Read rx initial gain */
	पढ़ो_nic_byte(dev, rOFDM0_XAAGCCore1, &priv->DefaultInitialGain[0]);
	पढ़ो_nic_byte(dev, rOFDM0_XBAGCCore1, &priv->DefaultInitialGain[1]);
	पढ़ो_nic_byte(dev, rOFDM0_XCAGCCore1, &priv->DefaultInitialGain[2]);
	पढ़ो_nic_byte(dev, rOFDM0_XDAGCCore1, &priv->DefaultInitialGain[3]);
	RT_TRACE(COMP_INIT,
		 "Default initial gain (c50=0x%x, c58=0x%x, c60=0x%x, c68=0x%x)\n",
		 priv->DefaultInitialGain[0], priv->DefaultInitialGain[1],
		 priv->DefaultInitialGain[2], priv->DefaultInitialGain[3]);

	/* Read framesync */
	पढ़ो_nic_byte(dev, rOFDM0_RxDetector3, &priv->framesync);
	पढ़ो_nic_byte(dev, rOFDM0_RxDetector2, &पंचांगp);
	priv->framesyncC34 = पंचांगp;
	RT_TRACE(COMP_INIT, "Default framesync (0x%x) = 0x%x\n",
		rOFDM0_RxDetector3, priv->framesync);

	/* Read SIFS (save the value पढ़ो fome MACPHY_REG.txt) */
	पढ़ो_nic_word(dev, SIFS, &priv->SअगरsTime);
पूर्ण

/******************************************************************************
 * function:  This function sets the initialization value of Tx घातer Level
 *            offset
 * input:     net_device        *dev
 *            u8                channel
 * output:    none
 * वापस:    none
 ******************************************************************************/
व्योम rtl8192_phy_setTxPower(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8	घातerlevel = priv->TxPowerLevelCCK[channel-1];
	u8	घातerlevelOFDM24G = priv->TxPowerLevelOFDM24G[channel-1];

	चयन (priv->rf_chip) अणु
	हाल RF_8256:
		/* need further implement */
		phy_set_rf8256_cck_tx_घातer(dev, घातerlevel);
		phy_set_rf8256_ofdm_tx_घातer(dev, घातerlevelOFDM24G);
		अवरोध;
	शेष:
		RT_TRACE((COMP_PHY|COMP_ERR),
			 "error RF chipID(8225 or 8258) in function %s()\n",
			 __func__);
		अवरोध;
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function checks Rf chip to करो RF config
 * input:     net_device	*dev
 * output:    none
 * वापस:    only 8256 is supported
 ******************************************************************************/
व्योम rtl8192_phy_RFConfig(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	चयन (priv->rf_chip) अणु
	हाल RF_8256:
		phy_rf8256_config(dev);
		अवरोध;
	शेष:
		RT_TRACE(COMP_ERR, "error chip id\n");
		अवरोध;
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function updates Initial gain
 * input:     net_device	*dev
 * output:    none
 * वापस:    As Winकरोws has not implemented this, रुको क्रम complement
 ******************************************************************************/
व्योम rtl8192_phy_updateInitGain(काष्ठा net_device *dev)
अणु
पूर्ण

/******************************************************************************
 * function:  This function पढ़ो RF parameters from general head file,
 *            and करो RF 3-wire
 * input:     net_device	*dev
 *            rf90_radio_path_e e_rfpath
 * output:    none
 * वापस:    वापस code show अगर RF configuration is successful(0:pass, 1:fail)
 * notice:    Delay may be required क्रम RF configuration
 *****************************************************************************/
u8 rtl8192_phy_ConfigRFWithHeaderFile(काष्ठा net_device *dev,
				      क्रमागत rf90_radio_path_e	e_rfpath)
अणु
	पूर्णांक i;

	चयन (e_rfpath) अणु
	हाल RF90_PATH_A:
		क्रम (i = 0; i < RadioA_ArrayLength; i = i+2) अणु
			अगर (Rtl8192UsbRadioA_Array[i] == 0xfe) अणु
				mdelay(100);
				जारी;
			पूर्ण
			rtl8192_phy_SetRFReg(dev, e_rfpath,
					     Rtl8192UsbRadioA_Array[i],
					     bMask12Bits,
					     Rtl8192UsbRadioA_Array[i+1]);
			mdelay(1);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_B:
		क्रम (i = 0; i < RadioB_ArrayLength; i = i+2) अणु
			अगर (Rtl8192UsbRadioB_Array[i] == 0xfe) अणु
				mdelay(100);
				जारी;
			पूर्ण
			rtl8192_phy_SetRFReg(dev, e_rfpath,
					     Rtl8192UsbRadioB_Array[i],
					     bMask12Bits,
					     Rtl8192UsbRadioB_Array[i+1]);
			mdelay(1);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_C:
		क्रम (i = 0; i < RadioC_ArrayLength; i = i+2) अणु
			अगर (Rtl8192UsbRadioC_Array[i] == 0xfe) अणु
				mdelay(100);
				जारी;
			पूर्ण
			rtl8192_phy_SetRFReg(dev, e_rfpath,
					     Rtl8192UsbRadioC_Array[i],
					     bMask12Bits,
					     Rtl8192UsbRadioC_Array[i+1]);
			mdelay(1);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_D:
		क्रम (i = 0; i < RadioD_ArrayLength; i = i+2) अणु
			अगर (Rtl8192UsbRadioD_Array[i] == 0xfe) अणु
				mdelay(100);
				जारी;
			पूर्ण
			rtl8192_phy_SetRFReg(dev, e_rfpath,
					     Rtl8192UsbRadioD_Array[i],
					     bMask12Bits,
					     Rtl8192UsbRadioD_Array[i+1]);
			mdelay(1);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 * function:  This function sets Tx Power of the channel
 * input:     net_device        *dev
 *            u8                channel
 * output:    none
 * वापस:    none
 * notice:
 ******************************************************************************/
अटल व्योम rtl8192_SetTxPowerLevel(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8	घातerlevel = priv->TxPowerLevelCCK[channel-1];
	u8	घातerlevelOFDM24G = priv->TxPowerLevelOFDM24G[channel-1];

	चयन (priv->rf_chip) अणु
	हाल RF_8225:
		अवरोध;

	हाल RF_8256:
		phy_set_rf8256_cck_tx_घातer(dev, घातerlevel);
		phy_set_rf8256_ofdm_tx_घातer(dev, घातerlevelOFDM24G);
		अवरोध;

	हाल RF_8258:
		अवरोध;
	शेष:
		RT_TRACE(COMP_ERR, "unknown rf chip ID in %s()\n", __func__);
		अवरोध;
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  This function sets RF state on or off
 * input:     net_device         *dev
 *            RT_RF_POWER_STATE  eRFPowerState  //Power State to set
 * output:    none
 * वापस:    none
 * notice:
 *****************************************************************************/
bool rtl8192_SetRFPowerState(काष्ठा net_device *dev,
			     RT_RF_POWER_STATE eRFPowerState)
अणु
	bool				bResult = true;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (eRFPowerState == priv->ieee80211->eRFPowerState)
		वापस false;

	अगर (priv->SetRFPowerStateInProgress)
		वापस false;

	priv->SetRFPowerStateInProgress = true;

	चयन (priv->rf_chip) अणु
	हाल RF_8256:
		चयन (eRFPowerState) अणु
		हाल eRfOn:
			/* RF-A, RF-B */
			/* enable RF-Chip A/B - 0x860[4] */
			rtl8192_setBBreg(dev, rFPGA0_XA_RFInterfaceOE, BIT(4),
					 0x1);
			/* analog to digital on - 0x88c[9:8] */
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0x300,
					 0x3);
			/* digital to analog on - 0x880[4:3] */
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x18,
					 0x3);
			/* rx antenna on - 0xc04[1:0] */
			rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0x3, 0x3);
			/* rx antenna on - 0xd04[1:0] */
			rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0x3, 0x3);
			/* analog to digital part2 on - 0x880[6:5] */
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x60,
					 0x3);

			अवरोध;

		हाल eRfSleep:

			अवरोध;

		हाल eRfOff:
			/* RF-A, RF-B */
			/* disable RF-Chip A/B - 0x860[4] */
			rtl8192_setBBreg(dev, rFPGA0_XA_RFInterfaceOE, BIT(4),
					 0x0);
			/* analog to digital off, क्रम घातer save */
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf00,
					 0x0); /* 0x88c[11:8] */
			/* digital to analog off, क्रम घातer save - 0x880[4:3] */
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x18,
					 0x0);
			/* rx antenna off - 0xc04[3:0] */
			rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0xf, 0x0);
			/* rx antenna off - 0xd04[3:0] */
			rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0xf, 0x0);
			/* analog to digital part2 off, क्रम घातer save */
			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x60,
					 0x0); /* 0x880[6:5] */

			अवरोध;

		शेष:
			bResult = false;
			RT_TRACE(COMP_ERR, "%s(): unknown state to set: 0x%X\n",
				 __func__, eRFPowerState);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		RT_TRACE(COMP_ERR, "Not support rf_chip(%x)\n", priv->rf_chip);
		अवरोध;
	पूर्ण
	priv->SetRFPowerStateInProgress = false;

	वापस bResult;
पूर्ण

/******************************************************************************
 * function:  This function sets command table variable (काष्ठा sw_chnl_cmd).
 * input:     sw_chnl_cmd      *CmdTable    //table to be set
 *            u32            CmdTableIdx  //variable index in table to be set
 *            u32            CmdTableSz   //table size
 *            चयन_chan_cmd_id    CmdID        //command ID to set
 *            u32            Para1
 *            u32            Para2
 *            u32            msDelay
 * output:
 * वापस:    true अगर finished, false otherwise
 * notice:
 ******************************************************************************/
अटल u8 rtl8192_phy_SetSwChnlCmdArray(काष्ठा sw_chnl_cmd *CmdTable, u32 CmdTableIdx,
					u32 CmdTableSz, क्रमागत चयन_chan_cmd_id CmdID,
					u32 Para1, u32 Para2, u32 msDelay)
अणु
	काष्ठा sw_chnl_cmd *pCmd;

	अगर (!CmdTable) अणु
		RT_TRACE(COMP_ERR, "%s(): CmdTable cannot be NULL\n", __func__);
		वापस false;
	पूर्ण
	अगर (CmdTableIdx >= CmdTableSz) अणु
		RT_TRACE(COMP_ERR, "%s(): Access invalid index, please check size of the table, CmdTableIdx:%d, CmdTableSz:%d\n",
			 __func__, CmdTableIdx, CmdTableSz);
		वापस false;
	पूर्ण

	pCmd = CmdTable + CmdTableIdx;
	pCmd->cmd_id = CmdID;
	pCmd->para_1 = Para1;
	pCmd->para_2 = Para2;
	pCmd->ms_delay = msDelay;

	वापस true;
पूर्ण

/******************************************************************************
 * function:  This function sets channel step by step
 * input:     net_device        *dev
 *            u8                channel
 *            u8                *stage   //3 stages
 *            u8                *step
 *            u32               *delay   //whether need to delay
 * output:    store new stage, step and delay क्रम next step
 *            (combine with function above)
 * वापस:    true अगर finished, false otherwise
 * notice:    Wait क्रम simpler function to replace it
 *****************************************************************************/
अटल u8 rtl8192_phy_SwChnlStepByStep(काष्ठा net_device *dev, u8 channel,
				       u8 *stage, u8 *step, u32 *delay)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	काष्ठा sw_chnl_cmd   PreCommonCmd[MAX_PRECMD_CNT];
	u32		   PreCommonCmdCnt;
	काष्ठा sw_chnl_cmd   PostCommonCmd[MAX_POSTCMD_CNT];
	u32		   PostCommonCmdCnt;
	काष्ठा sw_chnl_cmd   RfDependCmd[MAX_RFDEPENDCMD_CNT];
	u32		   RfDependCmdCnt;
	काष्ठा sw_chnl_cmd  *CurrentCmd = शून्य;
	u8		   e_rfpath;

	RT_TRACE(COMP_CH, "%s() stage: %d, step: %d, channel: %d\n",
		 __func__, *stage, *step, channel);
	अगर (!is_legal_channel(priv->ieee80211, channel)) अणु
		RT_TRACE(COMP_ERR, "set to illegal channel: %d\n", channel);
		/* वापस true to tell upper caller function this channel
		 * setting is finished! Or it will in जबतक loop.
		 */
		वापस true;
	पूर्ण
	/* FIXME: need to check whether channel is legal or not here */

	/* <1> Fill up pre common command. */
	PreCommonCmdCnt = 0;
	rtl8192_phy_SetSwChnlCmdArray(PreCommonCmd, PreCommonCmdCnt++,
				      MAX_PRECMD_CNT, CMD_ID_SET_TX_PWR_LEVEL,
				      0, 0, 0);
	rtl8192_phy_SetSwChnlCmdArray(PreCommonCmd, PreCommonCmdCnt++,
				      MAX_PRECMD_CNT, CMD_ID_END, 0, 0, 0);

	/* <2> Fill up post common command. */
	PostCommonCmdCnt = 0;

	rtl8192_phy_SetSwChnlCmdArray(PostCommonCmd, PostCommonCmdCnt++,
				      MAX_POSTCMD_CNT, CMD_ID_END, 0, 0, 0);

	/* <3> Fill up RF dependent command. */
	RfDependCmdCnt = 0;
	चयन (priv->rf_chip) अणु
	हाल RF_8225:
		अगर (!(channel >= 1 && channel <= 14)) अणु
			RT_TRACE(COMP_ERR,
				 "illegal channel for Zebra 8225: %d\n",
				 channel);
			वापस true;
		पूर्ण
		rtl8192_phy_SetSwChnlCmdArray(RfDependCmd, RfDependCmdCnt++,
					      MAX_RFDEPENDCMD_CNT,
					      CMD_ID_RF_WRITE_REG,
					      rZebra1_Channel,
					      RF_CHANNEL_TABLE_ZEBRA[channel],
					      10);
		rtl8192_phy_SetSwChnlCmdArray(RfDependCmd, RfDependCmdCnt++,
					      MAX_RFDEPENDCMD_CNT,
					      CMD_ID_END, 0, 0, 0);
		अवरोध;

	हाल RF_8256:
		/* TEST!! This is not the table क्रम 8256!! */
		अगर (!(channel >= 1 && channel <= 14)) अणु
			RT_TRACE(COMP_ERR,
				 "illegal channel for Zebra 8256: %d\n",
				 channel);
			वापस true;
		पूर्ण
		rtl8192_phy_SetSwChnlCmdArray(RfDependCmd, RfDependCmdCnt++,
					      MAX_RFDEPENDCMD_CNT,
					      CMD_ID_RF_WRITE_REG,
					      rZebra1_Channel, channel, 10);
		rtl8192_phy_SetSwChnlCmdArray(RfDependCmd, RfDependCmdCnt++,
					      MAX_RFDEPENDCMD_CNT,
					      CMD_ID_END, 0, 0, 0);
		अवरोध;

	हाल RF_8258:
		अवरोध;

	शेष:
		RT_TRACE(COMP_ERR, "Unknown RFChipID: %d\n", priv->rf_chip);
		वापस true;
	पूर्ण

	करो अणु
		चयन (*stage) अणु
		हाल 0:
			CurrentCmd = &PreCommonCmd[*step];
			अवरोध;
		हाल 1:
			CurrentCmd = &RfDependCmd[*step];
			अवरोध;
		हाल 2:
			CurrentCmd = &PostCommonCmd[*step];
			अवरोध;
		पूर्ण

		अगर (CurrentCmd->cmd_id == CMD_ID_END) अणु
			अगर ((*stage) == 2) अणु
				(*delay) = CurrentCmd->ms_delay;
				वापस true;
			पूर्ण
			(*stage)++;
			(*step) = 0;
			जारी;
		पूर्ण

		चयन (CurrentCmd->cmd_id) अणु
		हाल CMD_ID_SET_TX_PWR_LEVEL:
			अगर (priv->card_8192_version == VERSION_819XU_A)
				/* consider it later! */
				rtl8192_SetTxPowerLevel(dev, channel);
			अवरोध;
		हाल CMD_ID_WRITE_PORT_ULONG:
			ग_लिखो_nic_dword(dev, CurrentCmd->para_1,
					CurrentCmd->para_2);
			अवरोध;
		हाल CMD_ID_WRITE_PORT_USHORT:
			ग_लिखो_nic_word(dev, CurrentCmd->para_1,
				       (u16)CurrentCmd->para_2);
			अवरोध;
		हाल CMD_ID_WRITE_PORT_UCHAR:
			ग_लिखो_nic_byte(dev, CurrentCmd->para_1,
				       (u8)CurrentCmd->para_2);
			अवरोध;
		हाल CMD_ID_RF_WRITE_REG:
			क्रम (e_rfpath = 0; e_rfpath < RF90_PATH_MAX; e_rfpath++) अणु
				rtl8192_phy_SetRFReg(dev,
						     (क्रमागत rf90_radio_path_e)e_rfpath,
						     CurrentCmd->para_1,
						     bZebra1_ChannelNum,
						     CurrentCmd->para_2);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण जबतक (true);

	(*delay) = CurrentCmd->ms_delay;
	(*step)++;
	वापस false;
पूर्ण

/******************************************************************************
 * function:  This function करोes actually set channel work
 * input:     net_device        *dev
 *            u8                channel
 * output:    none
 * वापस:    none
 * notice:    We should not call this function directly
 *****************************************************************************/
अटल व्योम rtl8192_phy_FinishSwChnlNow(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32	delay = 0;

	जबतक (!rtl8192_phy_SwChnlStepByStep(dev, channel, &priv->SwChnlStage,
					     &priv->SwChnlStep, &delay)) अणु
		अगर (!priv->up)
			अवरोध;
	पूर्ण
पूर्ण

/******************************************************************************
 * function:  Callback routine of the work item क्रम चयन channel.
 * input:     net_device	*dev
 *
 * output:    none
 * वापस:    none
 *****************************************************************************/
व्योम rtl8192_SwChnl_WorkItem(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	RT_TRACE(COMP_CH, "==> SwChnlCallback819xUsbWorkItem(), chan:%d\n",
		 priv->chan);

	rtl8192_phy_FinishSwChnlNow(dev, priv->chan);

	RT_TRACE(COMP_CH, "<== SwChnlCallback819xUsbWorkItem()\n");
पूर्ण

/******************************************************************************
 * function:  This function scheduled actual work item to set channel
 * input:     net_device        *dev
 *            u8                channel   //channel to set
 * output:    none
 * वापस:    वापस code show अगर workitem is scheduled (1:pass, 0:fail)
 * notice:    Delay may be required क्रम RF configuration
 ******************************************************************************/
u8 rtl8192_phy_SwChnl(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	RT_TRACE(COMP_CH, "%s(), SwChnlInProgress: %d\n", __func__,
		 priv->SwChnlInProgress);
	अगर (!priv->up)
		वापस false;
	अगर (priv->SwChnlInProgress)
		वापस false;

	/* -------------------------------------------- */
	चयन (priv->ieee80211->mode) अणु
	हाल WIRELESS_MODE_A:
	हाल WIRELESS_MODE_N_5G:
		अगर (channel <= 14) अणु
			RT_TRACE(COMP_ERR, "WIRELESS_MODE_A but channel<=14\n");
			वापस false;
		पूर्ण
		अवरोध;
	हाल WIRELESS_MODE_B:
		अगर (channel > 14) अणु
			RT_TRACE(COMP_ERR, "WIRELESS_MODE_B but channel>14\n");
			वापस false;
		पूर्ण
		अवरोध;
	हाल WIRELESS_MODE_G:
	हाल WIRELESS_MODE_N_24G:
		अगर (channel > 14) अणु
			RT_TRACE(COMP_ERR, "WIRELESS_MODE_G but channel>14\n");
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण
	/* -------------------------------------------- */

	priv->SwChnlInProgress = true;
	अगर (channel == 0)
		channel = 1;

	priv->chan = channel;

	priv->SwChnlStage = 0;
	priv->SwChnlStep = 0;
	अगर (priv->up)
		rtl8192_SwChnl_WorkItem(dev);

	priv->SwChnlInProgress = false;
	वापस true;
पूर्ण

/******************************************************************************
 * function:  Callback routine of the work item क्रम set bandwidth mode.
 * input:     net_device	 *dev
 * output:    none
 * वापस:    none
 * notice:    I करोubt whether SetBWModeInProgress flag is necessary as we can
 *            test whether current work in the queue or not.//करो I?
 *****************************************************************************/
व्योम rtl8192_SetBWModeWorkItem(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u8 regBwOpMode;

	RT_TRACE(COMP_SWBW, "%s()  Switch to %s bandwidth\n", __func__,
		 priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20?"20MHz":"40MHz");

	अगर (priv->rf_chip == RF_PSEUDO_11N) अणु
		priv->SetBWModeInProgress = false;
		वापस;
	पूर्ण

	/* <1> Set MAC रेजिस्टर */
	पढ़ो_nic_byte(dev, BW_OPMODE, &regBwOpMode);

	चयन (priv->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		regBwOpMode |= BW_OPMODE_20MHZ;
		/* We have not verअगरy whether this रेजिस्टर works */
		ग_लिखो_nic_byte(dev, BW_OPMODE, regBwOpMode);
		अवरोध;

	हाल HT_CHANNEL_WIDTH_20_40:
		regBwOpMode &= ~BW_OPMODE_20MHZ;
		/* We have not verअगरy whether this रेजिस्टर works */
		ग_लिखो_nic_byte(dev, BW_OPMODE, regBwOpMode);
		अवरोध;

	शेष:
		RT_TRACE(COMP_ERR,
			 "SetChannelBandwidth819xUsb(): unknown Bandwidth: %#X\n",
			 priv->CurrentChannelBW);
		अवरोध;
	पूर्ण

	/* <2> Set PHY related रेजिस्टर */
	चयन (priv->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl8192_setBBreg(dev, rFPGA0_RFMOD, bRFMOD, 0x0);
		rtl8192_setBBreg(dev, rFPGA1_RFMOD, bRFMOD, 0x0);
		rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1,
				 0x00100000, 1);

		/* Correct the tx घातer क्रम CCK rate in 20M. */
		priv->cck_present_attenuation =
			priv->cck_present_attenuation_20Mशेष +
			priv->cck_present_attenuation_dअगरference;

		अगर (priv->cck_present_attenuation > 22)
			priv->cck_present_attenuation = 22;
		अगर (priv->cck_present_attenuation < 0)
			priv->cck_present_attenuation = 0;
		RT_TRACE(COMP_INIT,
			 "20M, pHalData->CCKPresentAttentuation = %d\n",
			 priv->cck_present_attenuation);

		अगर (priv->chan == 14 && !priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = true;
			dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अगर (priv->chan != 14 && priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = false;
			dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अणु
			dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण

		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl8192_setBBreg(dev, rFPGA0_RFMOD, bRFMOD, 0x1);
		rtl8192_setBBreg(dev, rFPGA1_RFMOD, bRFMOD, 0x1);
		rtl8192_setBBreg(dev, rCCK0_System, bCCKSideBand,
				 priv->nCur40MhzPrimeSC >> 1);
		rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x00100000, 0);
		rtl8192_setBBreg(dev, rOFDM1_LSTF, 0xC00,
				 priv->nCur40MhzPrimeSC);
		priv->cck_present_attenuation =
			priv->cck_present_attenuation_40Mशेष +
			priv->cck_present_attenuation_dअगरference;

		अगर (priv->cck_present_attenuation > 22)
			priv->cck_present_attenuation = 22;
		अगर (priv->cck_present_attenuation < 0)
			priv->cck_present_attenuation = 0;

		RT_TRACE(COMP_INIT,
			 "40M, pHalData->CCKPresentAttentuation = %d\n",
			 priv->cck_present_attenuation);
		अगर (priv->chan == 14 && !priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = true;
			dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अगर (priv->chan != 14 && priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = false;
			dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अणु
			dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण

		अवरोध;
	शेष:
		RT_TRACE(COMP_ERR,
			 "SetChannelBandwidth819xUsb(): unknown Bandwidth: %#X\n",
			 priv->CurrentChannelBW);
		अवरोध;
	पूर्ण
	/* Skip over setting of J-mode in BB रेजिस्टर here.
	 * Default value is "None J mode".
	 */

	/* <3> Set RF related रेजिस्टर */
	चयन (priv->rf_chip) अणु
	हाल RF_8225:
		अवरोध;

	हाल RF_8256:
		phy_set_rf8256_bandwidth(dev, priv->CurrentChannelBW);
		अवरोध;

	हाल RF_8258:
		अवरोध;

	हाल RF_PSEUDO_11N:
		अवरोध;

	शेष:
		RT_TRACE(COMP_ERR, "Unknown RFChipID: %d\n", priv->rf_chip);
		अवरोध;
	पूर्ण
	priv->SetBWModeInProgress = false;

	RT_TRACE(COMP_SWBW, "<==SetBWMode819xUsb(), %d\n",
		 atomic_पढ़ो(&priv->ieee80211->aपंचांग_swbw));
पूर्ण

/******************************************************************************
 * function:  This function schedules bandwidth चयन work.
 * input:     काष्ठा net_deviceq   *dev
 *            HT_CHANNEL_WIDTH     bandwidth  //20M or 40M
 *            HT_EXTCHNL_OFFSET    offset     //Upper, Lower, or Don't care
 * output:    none
 * वापस:    none
 * notice:    I करोubt whether SetBWModeInProgress flag is necessary as we can
 *	      test whether current work in the queue or not.//करो I?
 *****************************************************************************/
व्योम rtl8192_SetBWMode(काष्ठा net_device *dev,
		       क्रमागत ht_channel_width bandwidth,
		       क्रमागत ht_extension_chan_offset offset)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	अगर (priv->SetBWModeInProgress)
		वापस;
	priv->SetBWModeInProgress = true;

	priv->CurrentChannelBW = bandwidth;

	अगर (offset == HT_EXTCHNL_OFFSET_LOWER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_UPPER;
	अन्यथा अगर (offset == HT_EXTCHNL_OFFSET_UPPER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_LOWER;
	अन्यथा
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	rtl8192_SetBWModeWorkItem(dev);
पूर्ण

व्योम InitialGain819xUsb(काष्ठा net_device *dev,	u8 Operation)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	priv->InitialGainOperateType = Operation;

	अगर (priv->up)
		queue_delayed_work(priv->priv_wq, &priv->initialgain_operate_wq, 0);
पूर्ण

व्योम InitialGainOperateWorkItemCallBack(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा r8192_priv *priv = container_of(dwork, काष्ठा r8192_priv,
					       initialgain_operate_wq);
	काष्ठा net_device *dev = priv->ieee80211->dev;
#घोषणा SCAN_RX_INITIAL_GAIN	0x17
#घोषणा POWER_DETECTION_TH	0x08
	u32	biपंचांगask;
	u8	initial_gain;
	u8	Operation;

	Operation = priv->InitialGainOperateType;

	चयन (Operation) अणु
	हाल IG_Backup:
		RT_TRACE(COMP_SCAN, "IG_Backup, backup the initial gain.\n");
		initial_gain = SCAN_RX_INITIAL_GAIN;
		biपंचांगask = bMaskByte0;
		अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_FALSE_ALARM)
			/* FW DIG OFF */
			rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);
		priv->initgain_backup.xaagccore1 =
			(u8)rtl8192_QueryBBReg(dev, rOFDM0_XAAGCCore1, biपंचांगask);
		priv->initgain_backup.xbagccore1 =
			(u8)rtl8192_QueryBBReg(dev, rOFDM0_XBAGCCore1, biपंचांगask);
		priv->initgain_backup.xcagccore1 =
			(u8)rtl8192_QueryBBReg(dev, rOFDM0_XCAGCCore1, biपंचांगask);
		priv->initgain_backup.xdagccore1 =
			(u8)rtl8192_QueryBBReg(dev, rOFDM0_XDAGCCore1, biपंचांगask);
		biपंचांगask = bMaskByte2;
		priv->initgain_backup.cca =
			(u8)rtl8192_QueryBBReg(dev, rCCK0_CCA, biपंचांगask);

		RT_TRACE(COMP_SCAN, "Scan InitialGainBackup 0xc50 is %x\n",
			 priv->initgain_backup.xaagccore1);
		RT_TRACE(COMP_SCAN, "Scan InitialGainBackup 0xc58 is %x\n",
			 priv->initgain_backup.xbagccore1);
		RT_TRACE(COMP_SCAN, "Scan InitialGainBackup 0xc60 is %x\n",
			 priv->initgain_backup.xcagccore1);
		RT_TRACE(COMP_SCAN, "Scan InitialGainBackup 0xc68 is %x\n",
			 priv->initgain_backup.xdagccore1);
		RT_TRACE(COMP_SCAN, "Scan InitialGainBackup 0xa0a is %x\n",
			 priv->initgain_backup.cca);

		RT_TRACE(COMP_SCAN, "Write scan initial gain = 0x%x\n",
			 initial_gain);
		ग_लिखो_nic_byte(dev, rOFDM0_XAAGCCore1, initial_gain);
		ग_लिखो_nic_byte(dev, rOFDM0_XBAGCCore1, initial_gain);
		ग_लिखो_nic_byte(dev, rOFDM0_XCAGCCore1, initial_gain);
		ग_लिखो_nic_byte(dev, rOFDM0_XDAGCCore1, initial_gain);
		RT_TRACE(COMP_SCAN, "Write scan 0xa0a = 0x%x\n",
			 POWER_DETECTION_TH);
		ग_लिखो_nic_byte(dev, 0xa0a, POWER_DETECTION_TH);
		अवरोध;
	हाल IG_Restore:
		RT_TRACE(COMP_SCAN, "IG_Restore, restore the initial gain.\n");
		biपंचांगask = 0x7f; /* Bit0 ~ Bit6 */
		अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_FALSE_ALARM)
			/* FW DIG OFF */
			rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);

		rtl8192_setBBreg(dev, rOFDM0_XAAGCCore1, biपंचांगask,
				 (u32)priv->initgain_backup.xaagccore1);
		rtl8192_setBBreg(dev, rOFDM0_XBAGCCore1, biपंचांगask,
				 (u32)priv->initgain_backup.xbagccore1);
		rtl8192_setBBreg(dev, rOFDM0_XCAGCCore1, biपंचांगask,
				 (u32)priv->initgain_backup.xcagccore1);
		rtl8192_setBBreg(dev, rOFDM0_XDAGCCore1, biपंचांगask,
				 (u32)priv->initgain_backup.xdagccore1);
		biपंचांगask  = bMaskByte2;
		rtl8192_setBBreg(dev, rCCK0_CCA, biपंचांगask,
				 (u32)priv->initgain_backup.cca);

		RT_TRACE(COMP_SCAN, "Scan BBInitialGainRestore 0xc50 is %x\n",
			 priv->initgain_backup.xaagccore1);
		RT_TRACE(COMP_SCAN, "Scan BBInitialGainRestore 0xc58 is %x\n",
			 priv->initgain_backup.xbagccore1);
		RT_TRACE(COMP_SCAN, "Scan BBInitialGainRestore 0xc60 is %x\n",
			 priv->initgain_backup.xcagccore1);
		RT_TRACE(COMP_SCAN, "Scan BBInitialGainRestore 0xc68 is %x\n",
			 priv->initgain_backup.xdagccore1);
		RT_TRACE(COMP_SCAN, "Scan BBInitialGainRestore 0xa0a is %x\n",
			 priv->initgain_backup.cca);

		rtl8192_phy_setTxPower(dev, priv->ieee80211->current_network.channel);

		अगर (dm_digtable.dig_algorithm == DIG_ALGO_BY_FALSE_ALARM)
			/* FW DIG ON */
			rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x1);
		अवरोध;
	शेष:
		RT_TRACE(COMP_SCAN, "Unknown IG Operation.\n");
		अवरोध;
	पूर्ण
पूर्ण
