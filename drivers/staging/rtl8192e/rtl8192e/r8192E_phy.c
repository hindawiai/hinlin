<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश <linux/bitops.h>
#समावेश "rtl_core.h"
#समावेश "r8192E_hw.h"
#समावेश "r8192E_phyreg.h"
#समावेश "r8190P_rtl8256.h"
#समावेश "r8192E_phy.h"
#समावेश "rtl_dm.h"

#समावेश "r8192E_hwimg.h"

अटल u32 RF_CHANNEL_TABLE_ZEBRA[] = अणु
	0,
	0x085c,
	0x08dc,
	0x095c,
	0x09dc,
	0x0a5c,
	0x0adc,
	0x0b5c,
	0x0bdc,
	0x0c5c,
	0x0cdc,
	0x0d5c,
	0x0ddc,
	0x0e5c,
	0x0f72,
पूर्ण;

/*************************Define local function prototype**********************/

अटल u32 _rtl92e_phy_rf_fw_पढ़ो(काष्ठा net_device *dev,
				  क्रमागत rf90_radio_path eRFPath, u32 Offset);
अटल व्योम _rtl92e_phy_rf_fw_ग_लिखो(काष्ठा net_device *dev,
				    क्रमागत rf90_radio_path eRFPath, u32 Offset,
				    u32 Data);

अटल u32 _rtl92e_calculate_bit_shअगरt(u32 dwBitMask)
अणु
	अगर (!dwBitMask)
		वापस 32;
	वापस ffs(dwBitMask) - 1;
पूर्ण

u8 rtl92e_is_legal_rf_path(काष्ठा net_device *dev, u32 eRFPath)
अणु
	u8 ret = 1;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->rf_type == RF_2T4R)
		ret = 0;
	अन्यथा अगर (priv->rf_type == RF_1T2R) अणु
		अगर (eRFPath == RF90_PATH_A || eRFPath == RF90_PATH_B)
			ret = 1;
		अन्यथा अगर (eRFPath == RF90_PATH_C || eRFPath == RF90_PATH_D)
			ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

व्योम rtl92e_set_bb_reg(काष्ठा net_device *dev, u32 dwRegAddr, u32 dwBitMask,
		       u32 dwData)
अणु

	u32 OriginalValue, BitShअगरt, NewValue;

	अगर (dwBitMask != bMaskDWord) अणु
		OriginalValue = rtl92e_पढ़ोl(dev, dwRegAddr);
		BitShअगरt = _rtl92e_calculate_bit_shअगरt(dwBitMask);
		NewValue = (OriginalValue & ~dwBitMask) | (dwData << BitShअगरt);
		rtl92e_ग_लिखोl(dev, dwRegAddr, NewValue);
	पूर्ण अन्यथा
		rtl92e_ग_लिखोl(dev, dwRegAddr, dwData);
पूर्ण

u32 rtl92e_get_bb_reg(काष्ठा net_device *dev, u32 dwRegAddr, u32 dwBitMask)
अणु
	u32 OriginalValue, BitShअगरt;

	OriginalValue = rtl92e_पढ़ोl(dev, dwRegAddr);
	BitShअगरt = _rtl92e_calculate_bit_shअगरt(dwBitMask);

	वापस (OriginalValue & dwBitMask) >> BitShअगरt;
पूर्ण

अटल u32 _rtl92e_phy_rf_पढ़ो(काष्ठा net_device *dev,
			       क्रमागत rf90_radio_path eRFPath, u32 Offset)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 ret = 0;
	u32 NewOffset = 0;
	काष्ठा bb_reg_definition *pPhyReg = &priv->PHYRegDef[eRFPath];

	Offset &= 0x3f;

	अगर (priv->rf_chip == RF_8256) अणु
		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter4, 0xf00, 0x0);
		अगर (Offset >= 31) अणु
			priv->RfReg0Value[eRFPath] |= 0x140;
			rtl92e_set_bb_reg(dev, pPhyReg->rf3wireOffset,
					  bMaskDWord,
					  (priv->RfReg0Value[eRFPath]<<16));
			NewOffset = Offset - 30;
		पूर्ण अन्यथा अगर (Offset >= 16) अणु
			priv->RfReg0Value[eRFPath] |= 0x100;
			priv->RfReg0Value[eRFPath] &= (~0x40);
			rtl92e_set_bb_reg(dev, pPhyReg->rf3wireOffset,
					  bMaskDWord,
					  (priv->RfReg0Value[eRFPath]<<16));

			NewOffset = Offset - 15;
		पूर्ण अन्यथा
			NewOffset = Offset;
	पूर्ण अन्यथा अणु
		RT_TRACE((COMP_PHY|COMP_ERR),
			 "check RF type here, need to be 8256\n");
		NewOffset = Offset;
	पूर्ण
	rtl92e_set_bb_reg(dev, pPhyReg->rfHSSIPara2, bLSSIReadAddress,
			  NewOffset);
	rtl92e_set_bb_reg(dev, pPhyReg->rfHSSIPara2,  bLSSIReadEdge, 0x0);
	rtl92e_set_bb_reg(dev, pPhyReg->rfHSSIPara2,  bLSSIReadEdge, 0x1);

	mdelay(1);

	ret = rtl92e_get_bb_reg(dev, pPhyReg->rfLSSIReadBack,
				bLSSIReadBackData);

	अगर (priv->rf_chip == RF_8256) अणु
		priv->RfReg0Value[eRFPath] &= 0xebf;

		rtl92e_set_bb_reg(dev, pPhyReg->rf3wireOffset, bMaskDWord,
				  (priv->RfReg0Value[eRFPath] << 16));

		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter4, 0x300, 0x3);
	पूर्ण


	वापस ret;

पूर्ण

अटल व्योम _rtl92e_phy_rf_ग_लिखो(काष्ठा net_device *dev,
				 क्रमागत rf90_radio_path eRFPath, u32 Offset,
				 u32 Data)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 DataAndAddr = 0, NewOffset = 0;
	काष्ठा bb_reg_definition *pPhyReg = &priv->PHYRegDef[eRFPath];

	Offset &= 0x3f;
	अगर (priv->rf_chip == RF_8256) अणु
		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter4, 0xf00, 0x0);

		अगर (Offset >= 31) अणु
			priv->RfReg0Value[eRFPath] |= 0x140;
			rtl92e_set_bb_reg(dev, pPhyReg->rf3wireOffset,
					  bMaskDWord,
					  (priv->RfReg0Value[eRFPath] << 16));
			NewOffset = Offset - 30;
		पूर्ण अन्यथा अगर (Offset >= 16) अणु
			priv->RfReg0Value[eRFPath] |= 0x100;
			priv->RfReg0Value[eRFPath] &= (~0x40);
			rtl92e_set_bb_reg(dev, pPhyReg->rf3wireOffset,
					  bMaskDWord,
					  (priv->RfReg0Value[eRFPath] << 16));
			NewOffset = Offset - 15;
		पूर्ण अन्यथा
			NewOffset = Offset;
	पूर्ण अन्यथा अणु
		RT_TRACE((COMP_PHY|COMP_ERR),
			 "check RF type here, need to be 8256\n");
		NewOffset = Offset;
	पूर्ण

	DataAndAddr = (NewOffset & 0x3f) | (Data << 16);

	rtl92e_set_bb_reg(dev, pPhyReg->rf3wireOffset, bMaskDWord, DataAndAddr);

	अगर (Offset == 0x0)
		priv->RfReg0Value[eRFPath] = Data;

	अगर (priv->rf_chip == RF_8256) अणु
		अगर (Offset != 0) अणु
			priv->RfReg0Value[eRFPath] &= 0xebf;
			rtl92e_set_bb_reg(dev, pPhyReg->rf3wireOffset,
					  bMaskDWord,
					  (priv->RfReg0Value[eRFPath] << 16));
		पूर्ण
		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter4, 0x300, 0x3);
	पूर्ण
पूर्ण

व्योम rtl92e_set_rf_reg(काष्ठा net_device *dev, क्रमागत rf90_radio_path eRFPath,
		       u32 RegAddr, u32 BitMask, u32 Data)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 Original_Value, BitShअगरt, New_Value;

	अगर (!rtl92e_is_legal_rf_path(dev, eRFPath))
		वापस;
	अगर (priv->rtllib->eRFPowerState != eRfOn && !priv->being_init_adapter)
		वापस;

	RT_TRACE(COMP_PHY, "FW RF CTRL is not ready now\n");
	अगर (priv->Rf_Mode == RF_OP_By_FW) अणु
		अगर (BitMask != bMask12Bits) अणु
			Original_Value = _rtl92e_phy_rf_fw_पढ़ो(dev, eRFPath,
								RegAddr);
			BitShअगरt =  _rtl92e_calculate_bit_shअगरt(BitMask);
			New_Value = (Original_Value & ~BitMask) | (Data << BitShअगरt);

			_rtl92e_phy_rf_fw_ग_लिखो(dev, eRFPath, RegAddr,
						New_Value);
		पूर्ण अन्यथा
			_rtl92e_phy_rf_fw_ग_लिखो(dev, eRFPath, RegAddr, Data);
		udelay(200);

	पूर्ण अन्यथा अणु
		अगर (BitMask != bMask12Bits) अणु
			Original_Value = _rtl92e_phy_rf_पढ़ो(dev, eRFPath,
							     RegAddr);
			BitShअगरt =  _rtl92e_calculate_bit_shअगरt(BitMask);
			New_Value = (Original_Value & ~BitMask) | (Data << BitShअगरt);

			_rtl92e_phy_rf_ग_लिखो(dev, eRFPath, RegAddr, New_Value);
		पूर्ण अन्यथा
			_rtl92e_phy_rf_ग_लिखो(dev, eRFPath, RegAddr, Data);
	पूर्ण
पूर्ण

u32 rtl92e_get_rf_reg(काष्ठा net_device *dev, क्रमागत rf90_radio_path eRFPath,
		      u32 RegAddr, u32 BitMask)
अणु
	u32 Original_Value, Readback_Value, BitShअगरt;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (!rtl92e_is_legal_rf_path(dev, eRFPath))
		वापस 0;
	अगर (priv->rtllib->eRFPowerState != eRfOn && !priv->being_init_adapter)
		वापस	0;
	mutex_lock(&priv->rf_mutex);
	अगर (priv->Rf_Mode == RF_OP_By_FW) अणु
		Original_Value = _rtl92e_phy_rf_fw_पढ़ो(dev, eRFPath, RegAddr);
		udelay(200);
	पूर्ण अन्यथा अणु
		Original_Value = _rtl92e_phy_rf_पढ़ो(dev, eRFPath, RegAddr);
	पूर्ण
	BitShअगरt =  _rtl92e_calculate_bit_shअगरt(BitMask);
	Readback_Value = (Original_Value & BitMask) >> BitShअगरt;
	mutex_unlock(&priv->rf_mutex);
	वापस Readback_Value;
पूर्ण

अटल u32 _rtl92e_phy_rf_fw_पढ़ो(काष्ठा net_device *dev,
				  क्रमागत rf90_radio_path eRFPath, u32 Offset)
अणु
	u32		Data = 0;
	u8		समय = 0;

	Data |= ((Offset & 0xFF) << 12);
	Data |= ((eRFPath & 0x3) << 20);
	Data |= 0x80000000;
	जबतक (rtl92e_पढ़ोl(dev, QPNR) & 0x80000000) अणु
		अगर (समय++ < 100)
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण
	rtl92e_ग_लिखोl(dev, QPNR, Data);
	जबतक (rtl92e_पढ़ोl(dev, QPNR) & 0x80000000) अणु
		अगर (समय++ < 100)
			udelay(10);
		अन्यथा
			वापस 0;
	पूर्ण
	वापस rtl92e_पढ़ोl(dev, RF_DATA);

पूर्ण

अटल व्योम _rtl92e_phy_rf_fw_ग_लिखो(काष्ठा net_device *dev,
				    क्रमागत rf90_radio_path eRFPath, u32 Offset,
				    u32 Data)
अणु
	u8	समय = 0;

	Data |= ((Offset & 0xFF) << 12);
	Data |= ((eRFPath & 0x3) << 20);
	Data |= 0x400000;
	Data |= 0x80000000;

	जबतक (rtl92e_पढ़ोl(dev, QPNR) & 0x80000000) अणु
		अगर (समय++ < 100)
			udelay(10);
		अन्यथा
			अवरोध;
	पूर्ण
	rtl92e_ग_लिखोl(dev, QPNR, Data);

पूर्ण


व्योम rtl92e_config_mac(काष्ठा net_device *dev)
अणु
	u32 dwArrayLen = 0, i = 0;
	u32 *pdwArray = शून्य;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->bTXPowerDataReadFromEEPORM) अणु
		RT_TRACE(COMP_PHY, "Rtl819XMACPHY_Array_PG\n");
		dwArrayLen = MACPHY_Array_PGLength;
		pdwArray = Rtl819XMACPHY_Array_PG;

	पूर्ण अन्यथा अणु
		RT_TRACE(COMP_PHY, "Read rtl819XMACPHY_Array\n");
		dwArrayLen = MACPHY_ArrayLength;
		pdwArray = Rtl819XMACPHY_Array;
	पूर्ण
	क्रम (i = 0; i < dwArrayLen; i += 3) अणु
		RT_TRACE(COMP_DBG,
			 "The Rtl8190MACPHY_Array[0] is %x Rtl8190MACPHY_Array[1] is %x Rtl8190MACPHY_Array[2] is %x\n",
			 pdwArray[i], pdwArray[i+1], pdwArray[i+2]);
		अगर (pdwArray[i] == 0x318)
			pdwArray[i+2] = 0x00000800;
		rtl92e_set_bb_reg(dev, pdwArray[i], pdwArray[i+1],
				  pdwArray[i+2]);
	पूर्ण
	वापस;

पूर्ण

अटल व्योम _rtl92e_phy_config_bb(काष्ठा net_device *dev, u8 ConfigType)
अणु
	पूर्णांक i;
	u32 *Rtl819XPHY_REGArray_Table = शून्य;
	u32 *Rtl819XAGCTAB_Array_Table = शून्य;
	u16 AGCTAB_ArrayLen, PHY_REGArrayLen = 0;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	AGCTAB_ArrayLen = AGCTAB_ArrayLength;
	Rtl819XAGCTAB_Array_Table = Rtl819XAGCTAB_Array;
	अगर (priv->rf_type == RF_2T4R) अणु
		PHY_REGArrayLen = PHY_REGArrayLength;
		Rtl819XPHY_REGArray_Table = Rtl819XPHY_REGArray;
	पूर्ण अन्यथा अगर (priv->rf_type == RF_1T2R) अणु
		PHY_REGArrayLen = PHY_REG_1T2RArrayLength;
		Rtl819XPHY_REGArray_Table = Rtl819XPHY_REG_1T2RArray;
	पूर्ण

	अगर (ConfigType == BaseBand_Config_PHY_REG) अणु
		क्रम (i = 0; i < PHY_REGArrayLen; i += 2) अणु
			rtl92e_set_bb_reg(dev, Rtl819XPHY_REGArray_Table[i],
					  bMaskDWord,
					  Rtl819XPHY_REGArray_Table[i+1]);
			RT_TRACE(COMP_DBG,
				 "i: %x, The Rtl819xUsbPHY_REGArray[0] is %x Rtl819xUsbPHY_REGArray[1] is %x\n",
				 i, Rtl819XPHY_REGArray_Table[i],
				 Rtl819XPHY_REGArray_Table[i+1]);
		पूर्ण
	पूर्ण अन्यथा अगर (ConfigType == BaseBand_Config_AGC_TAB) अणु
		क्रम (i = 0; i < AGCTAB_ArrayLen; i += 2) अणु
			rtl92e_set_bb_reg(dev, Rtl819XAGCTAB_Array_Table[i],
					  bMaskDWord,
					  Rtl819XAGCTAB_Array_Table[i+1]);
			RT_TRACE(COMP_DBG,
				 "i:%x, The rtl819XAGCTAB_Array[0] is %x rtl819XAGCTAB_Array[1] is %x\n",
				 i, Rtl819XAGCTAB_Array_Table[i],
				 Rtl819XAGCTAB_Array_Table[i+1]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_init_bb_rf_reg_def(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfs = rFPGA0_XAB_RFInterfaceSW;
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfs = rFPGA0_XAB_RFInterfaceSW;
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfs = rFPGA0_XCD_RFInterfaceSW;
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfs = rFPGA0_XCD_RFInterfaceSW;

	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfi = rFPGA0_XAB_RFInterfaceRB;
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfi = rFPGA0_XAB_RFInterfaceRB;
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfi = rFPGA0_XCD_RFInterfaceRB;
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfi = rFPGA0_XCD_RFInterfaceRB;

	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfo = rFPGA0_XA_RFInterfaceOE;
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfo = rFPGA0_XB_RFInterfaceOE;
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfo = rFPGA0_XC_RFInterfaceOE;
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfo = rFPGA0_XD_RFInterfaceOE;

	priv->PHYRegDef[RF90_PATH_A].rfपूर्णांकfe = rFPGA0_XA_RFInterfaceOE;
	priv->PHYRegDef[RF90_PATH_B].rfपूर्णांकfe = rFPGA0_XB_RFInterfaceOE;
	priv->PHYRegDef[RF90_PATH_C].rfपूर्णांकfe = rFPGA0_XC_RFInterfaceOE;
	priv->PHYRegDef[RF90_PATH_D].rfपूर्णांकfe = rFPGA0_XD_RFInterfaceOE;

	priv->PHYRegDef[RF90_PATH_A].rf3wireOffset = rFPGA0_XA_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_B].rf3wireOffset = rFPGA0_XB_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_C].rf3wireOffset = rFPGA0_XC_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_D].rf3wireOffset = rFPGA0_XD_LSSIParameter;

	priv->PHYRegDef[RF90_PATH_A].rfLSSI_Select = rFPGA0_XAB_RFParameter;
	priv->PHYRegDef[RF90_PATH_B].rfLSSI_Select = rFPGA0_XAB_RFParameter;
	priv->PHYRegDef[RF90_PATH_C].rfLSSI_Select = rFPGA0_XCD_RFParameter;
	priv->PHYRegDef[RF90_PATH_D].rfLSSI_Select = rFPGA0_XCD_RFParameter;

	priv->PHYRegDef[RF90_PATH_A].rfTxGainStage = rFPGA0_TxGainStage;
	priv->PHYRegDef[RF90_PATH_B].rfTxGainStage = rFPGA0_TxGainStage;
	priv->PHYRegDef[RF90_PATH_C].rfTxGainStage = rFPGA0_TxGainStage;
	priv->PHYRegDef[RF90_PATH_D].rfTxGainStage = rFPGA0_TxGainStage;

	priv->PHYRegDef[RF90_PATH_A].rfHSSIPara1 = rFPGA0_XA_HSSIParameter1;
	priv->PHYRegDef[RF90_PATH_B].rfHSSIPara1 = rFPGA0_XB_HSSIParameter1;
	priv->PHYRegDef[RF90_PATH_C].rfHSSIPara1 = rFPGA0_XC_HSSIParameter1;
	priv->PHYRegDef[RF90_PATH_D].rfHSSIPara1 = rFPGA0_XD_HSSIParameter1;

	priv->PHYRegDef[RF90_PATH_A].rfHSSIPara2 = rFPGA0_XA_HSSIParameter2;
	priv->PHYRegDef[RF90_PATH_B].rfHSSIPara2 = rFPGA0_XB_HSSIParameter2;
	priv->PHYRegDef[RF90_PATH_C].rfHSSIPara2 = rFPGA0_XC_HSSIParameter2;
	priv->PHYRegDef[RF90_PATH_D].rfHSSIPara2 = rFPGA0_XD_HSSIParameter2;

	priv->PHYRegDef[RF90_PATH_A].rfSwitchControl = rFPGA0_XAB_SwitchControl;
	priv->PHYRegDef[RF90_PATH_B].rfSwitchControl = rFPGA0_XAB_SwitchControl;
	priv->PHYRegDef[RF90_PATH_C].rfSwitchControl = rFPGA0_XCD_SwitchControl;
	priv->PHYRegDef[RF90_PATH_D].rfSwitchControl = rFPGA0_XCD_SwitchControl;

	priv->PHYRegDef[RF90_PATH_A].rfAGCControl1 = rOFDM0_XAAGCCore1;
	priv->PHYRegDef[RF90_PATH_B].rfAGCControl1 = rOFDM0_XBAGCCore1;
	priv->PHYRegDef[RF90_PATH_C].rfAGCControl1 = rOFDM0_XCAGCCore1;
	priv->PHYRegDef[RF90_PATH_D].rfAGCControl1 = rOFDM0_XDAGCCore1;

	priv->PHYRegDef[RF90_PATH_A].rfAGCControl2 = rOFDM0_XAAGCCore2;
	priv->PHYRegDef[RF90_PATH_B].rfAGCControl2 = rOFDM0_XBAGCCore2;
	priv->PHYRegDef[RF90_PATH_C].rfAGCControl2 = rOFDM0_XCAGCCore2;
	priv->PHYRegDef[RF90_PATH_D].rfAGCControl2 = rOFDM0_XDAGCCore2;

	priv->PHYRegDef[RF90_PATH_A].rfRxIQImbalance = rOFDM0_XARxIQImbalance;
	priv->PHYRegDef[RF90_PATH_B].rfRxIQImbalance = rOFDM0_XBRxIQImbalance;
	priv->PHYRegDef[RF90_PATH_C].rfRxIQImbalance = rOFDM0_XCRxIQImbalance;
	priv->PHYRegDef[RF90_PATH_D].rfRxIQImbalance = rOFDM0_XDRxIQImbalance;

	priv->PHYRegDef[RF90_PATH_A].rfRxAFE = rOFDM0_XARxAFE;
	priv->PHYRegDef[RF90_PATH_B].rfRxAFE = rOFDM0_XBRxAFE;
	priv->PHYRegDef[RF90_PATH_C].rfRxAFE = rOFDM0_XCRxAFE;
	priv->PHYRegDef[RF90_PATH_D].rfRxAFE = rOFDM0_XDRxAFE;

	priv->PHYRegDef[RF90_PATH_A].rfTxIQImbalance = rOFDM0_XATxIQImbalance;
	priv->PHYRegDef[RF90_PATH_B].rfTxIQImbalance = rOFDM0_XBTxIQImbalance;
	priv->PHYRegDef[RF90_PATH_C].rfTxIQImbalance = rOFDM0_XCTxIQImbalance;
	priv->PHYRegDef[RF90_PATH_D].rfTxIQImbalance = rOFDM0_XDTxIQImbalance;

	priv->PHYRegDef[RF90_PATH_A].rfTxAFE = rOFDM0_XATxAFE;
	priv->PHYRegDef[RF90_PATH_B].rfTxAFE = rOFDM0_XBTxAFE;
	priv->PHYRegDef[RF90_PATH_C].rfTxAFE = rOFDM0_XCTxAFE;
	priv->PHYRegDef[RF90_PATH_D].rfTxAFE = rOFDM0_XDTxAFE;

	priv->PHYRegDef[RF90_PATH_A].rfLSSIReadBack = rFPGA0_XA_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_B].rfLSSIReadBack = rFPGA0_XB_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_C].rfLSSIReadBack = rFPGA0_XC_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_D].rfLSSIReadBack = rFPGA0_XD_LSSIReadBack;

पूर्ण

bool rtl92e_check_bb_and_rf(काष्ठा net_device *dev, क्रमागत hw90_block CheckBlock,
			    क्रमागत rf90_radio_path eRFPath)
अणु
	bool ret = true;
	u32 i, CheckTimes = 4, dwRegRead = 0;
	u32 WriteAddr[4];
	u32 WriteData[] = अणु0xfffff027, 0xaa55a02f, 0x00000027, 0x55aa502fपूर्ण;

	WriteAddr[HW90_BLOCK_MAC] = 0x100;
	WriteAddr[HW90_BLOCK_PHY0] = 0x900;
	WriteAddr[HW90_BLOCK_PHY1] = 0x800;
	WriteAddr[HW90_BLOCK_RF] = 0x3;
	RT_TRACE(COMP_PHY, "=======>%s(), CheckBlock:%d\n", __func__,
		 CheckBlock);

	अगर (CheckBlock == HW90_BLOCK_MAC) अणु
		netdev_warn(dev, "%s(): No checks available for MAC block.\n",
			    __func__);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < CheckTimes; i++) अणु
		चयन (CheckBlock) अणु
		हाल HW90_BLOCK_PHY0:
		हाल HW90_BLOCK_PHY1:
			rtl92e_ग_लिखोl(dev, WriteAddr[CheckBlock],
				      WriteData[i]);
			dwRegRead = rtl92e_पढ़ोl(dev, WriteAddr[CheckBlock]);
			अवरोध;

		हाल HW90_BLOCK_RF:
			WriteData[i] &= 0xfff;
			rtl92e_set_rf_reg(dev, eRFPath,
					  WriteAddr[HW90_BLOCK_RF],
					  bMask12Bits, WriteData[i]);
			mdelay(10);
			dwRegRead = rtl92e_get_rf_reg(dev, eRFPath,
						      WriteAddr[HW90_BLOCK_RF],
						      bMaskDWord);
			mdelay(10);
			अवरोध;

		शेष:
			ret = false;
			अवरोध;
		पूर्ण


		अगर (dwRegRead != WriteData[i]) अणु
			netdev_warn(dev, "%s(): Check failed.\n", __func__);
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल bool _rtl92e_bb_config_para_file(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	bool rtStatus = true;
	u8 bRegValue = 0, eCheckItem = 0;
	u32 dwRegValue = 0;

	bRegValue = rtl92e_पढ़ोb(dev, BB_GLOBAL_RESET);
	rtl92e_ग_लिखोb(dev, BB_GLOBAL_RESET, (bRegValue|BB_GLOBAL_RESET_BIT));

	dwRegValue = rtl92e_पढ़ोl(dev, CPU_GEN);
	rtl92e_ग_लिखोl(dev, CPU_GEN, (dwRegValue&(~CPU_GEN_BB_RST)));

	क्रम (eCheckItem = (क्रमागत hw90_block)HW90_BLOCK_PHY0;
	     eCheckItem <= HW90_BLOCK_PHY1; eCheckItem++) अणु
		rtStatus  = rtl92e_check_bb_and_rf(dev,
						   (क्रमागत hw90_block)eCheckItem,
						   (क्रमागत rf90_radio_path)0);
		अगर (!rtStatus) अणु
			RT_TRACE((COMP_ERR | COMP_PHY),
				 "rtl92e_config_rf():Check PHY%d Fail!!\n",
				 eCheckItem-1);
			वापस rtStatus;
		पूर्ण
	पूर्ण
	rtl92e_set_bb_reg(dev, rFPGA0_RFMOD, bCCKEn|bOFDMEn, 0x0);
	_rtl92e_phy_config_bb(dev, BaseBand_Config_PHY_REG);

	dwRegValue = rtl92e_पढ़ोl(dev, CPU_GEN);
	rtl92e_ग_लिखोl(dev, CPU_GEN, (dwRegValue|CPU_GEN_BB_RST));

	_rtl92e_phy_config_bb(dev, BaseBand_Config_AGC_TAB);

	अगर (priv->IC_Cut  > VERSION_8190_BD) अणु
		अगर (priv->rf_type == RF_2T4R)
			dwRegValue = priv->AntennaTxPwDअगरf[2]<<8 |
				      priv->AntennaTxPwDअगरf[1]<<4 |
				      priv->AntennaTxPwDअगरf[0];
		अन्यथा
			dwRegValue = 0x0;
		rtl92e_set_bb_reg(dev, rFPGA0_TxGainStage,
				  (bXBTxAGC|bXCTxAGC|bXDTxAGC), dwRegValue);


		dwRegValue = priv->CrystalCap;
		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, bXtalCap92x,
				  dwRegValue);
	पूर्ण

	वापस rtStatus;
पूर्ण
bool rtl92e_config_bb(काष्ठा net_device *dev)
अणु
	_rtl92e_init_bb_rf_reg_def(dev);
	वापस _rtl92e_bb_config_para_file(dev);
पूर्ण

व्योम rtl92e_get_tx_घातer(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	priv->MCSTxPowerLevelOriginalOffset[0] =
		rtl92e_पढ़ोl(dev, rTxAGC_Rate18_06);
	priv->MCSTxPowerLevelOriginalOffset[1] =
		rtl92e_पढ़ोl(dev, rTxAGC_Rate54_24);
	priv->MCSTxPowerLevelOriginalOffset[2] =
		rtl92e_पढ़ोl(dev, rTxAGC_Mcs03_Mcs00);
	priv->MCSTxPowerLevelOriginalOffset[3] =
		rtl92e_पढ़ोl(dev, rTxAGC_Mcs07_Mcs04);
	priv->MCSTxPowerLevelOriginalOffset[4] =
		rtl92e_पढ़ोl(dev, rTxAGC_Mcs11_Mcs08);
	priv->MCSTxPowerLevelOriginalOffset[5] =
		rtl92e_पढ़ोl(dev, rTxAGC_Mcs15_Mcs12);

	priv->DefaultInitialGain[0] = rtl92e_पढ़ोb(dev, rOFDM0_XAAGCCore1);
	priv->DefaultInitialGain[1] = rtl92e_पढ़ोb(dev, rOFDM0_XBAGCCore1);
	priv->DefaultInitialGain[2] = rtl92e_पढ़ोb(dev, rOFDM0_XCAGCCore1);
	priv->DefaultInitialGain[3] = rtl92e_पढ़ोb(dev, rOFDM0_XDAGCCore1);
	RT_TRACE(COMP_INIT,
		 "Default initial gain (c50=0x%x, c58=0x%x, c60=0x%x, c68=0x%x)\n",
		 priv->DefaultInitialGain[0], priv->DefaultInitialGain[1],
		 priv->DefaultInitialGain[2], priv->DefaultInitialGain[3]);

	priv->framesync = rtl92e_पढ़ोb(dev, rOFDM0_RxDetector3);
	priv->framesyncC34 = rtl92e_पढ़ोl(dev, rOFDM0_RxDetector2);
	RT_TRACE(COMP_INIT, "Default framesync (0x%x) = 0x%x\n",
		rOFDM0_RxDetector3, priv->framesync);
	priv->SअगरsTime = rtl92e_पढ़ोw(dev, SIFS);
पूर्ण

व्योम rtl92e_set_tx_घातer(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8	घातerlevel = 0, घातerlevelOFDM24G = 0;
	s8	ant_pwr_dअगरf;
	u32	u4RegValue;

	अगर (priv->epromtype == EEPROM_93C46) अणु
		घातerlevel = priv->TxPowerLevelCCK[channel-1];
		घातerlevelOFDM24G = priv->TxPowerLevelOFDM24G[channel-1];
	पूर्ण अन्यथा अगर (priv->epromtype == EEPROM_93C56) अणु
		अगर (priv->rf_type == RF_1T2R) अणु
			घातerlevel = priv->TxPowerLevelCCK_C[channel-1];
			घातerlevelOFDM24G = priv->TxPowerLevelOFDM24G_C[channel-1];
		पूर्ण अन्यथा अगर (priv->rf_type == RF_2T4R) अणु
			घातerlevel = priv->TxPowerLevelCCK_A[channel-1];
			घातerlevelOFDM24G = priv->TxPowerLevelOFDM24G_A[channel-1];

			ant_pwr_dअगरf = priv->TxPowerLevelOFDM24G_C[channel-1]
				       - priv->TxPowerLevelOFDM24G_A[channel-1];

			priv->RF_C_TxPwDअगरf = ant_pwr_dअगरf;

			ant_pwr_dअगरf &= 0xf;

			priv->AntennaTxPwDअगरf[2] = 0;
			priv->AntennaTxPwDअगरf[1] = (u8)(ant_pwr_dअगरf);
			priv->AntennaTxPwDअगरf[0] = 0;

			u4RegValue = priv->AntennaTxPwDअगरf[2]<<8 |
				      priv->AntennaTxPwDअगरf[1]<<4 |
				      priv->AntennaTxPwDअगरf[0];

			rtl92e_set_bb_reg(dev, rFPGA0_TxGainStage,
					  (bXBTxAGC|bXCTxAGC|bXDTxAGC),
					  u4RegValue);
		पूर्ण
	पूर्ण
	चयन (priv->rf_chip) अणु
	हाल RF_8225:
		अवरोध;
	हाल RF_8256:
		rtl92e_set_cck_tx_घातer(dev, घातerlevel);
		rtl92e_set_ofdm_tx_घातer(dev, घातerlevelOFDM24G);
		अवरोध;
	हाल RF_8258:
		अवरोध;
	शेष:
		netdev_err(dev, "Invalid RF Chip ID.\n");
		अवरोध;
	पूर्ण
पूर्ण

bool rtl92e_config_phy(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	bool rtStatus = true;

	चयन (priv->rf_chip) अणु
	हाल RF_8225:
		अवरोध;
	हाल RF_8256:
		rtStatus = rtl92e_config_rf(dev);
		अवरोध;

	हाल RF_8258:
		अवरोध;
	हाल RF_PSEUDO_11N:
		अवरोध;

	शेष:
		netdev_err(dev, "Invalid RF Chip ID.\n");
		अवरोध;
	पूर्ण
	वापस rtStatus;
पूर्ण

u8 rtl92e_config_rf_path(काष्ठा net_device *dev, क्रमागत rf90_radio_path eRFPath)
अणु

	पूर्णांक i;

	चयन (eRFPath) अणु
	हाल RF90_PATH_A:
		क्रम (i = 0; i < RadioA_ArrayLength; i += 2) अणु
			अगर (Rtl819XRadioA_Array[i] == 0xfe) अणु
				msleep(100);
				जारी;
			पूर्ण
			rtl92e_set_rf_reg(dev, eRFPath, Rtl819XRadioA_Array[i],
					  bMask12Bits,
					  Rtl819XRadioA_Array[i+1]);

		पूर्ण
		अवरोध;
	हाल RF90_PATH_B:
		क्रम (i = 0; i < RadioB_ArrayLength; i += 2) अणु
			अगर (Rtl819XRadioB_Array[i] == 0xfe) अणु
				msleep(100);
				जारी;
			पूर्ण
			rtl92e_set_rf_reg(dev, eRFPath, Rtl819XRadioB_Array[i],
					  bMask12Bits,
					  Rtl819XRadioB_Array[i+1]);

		पूर्ण
		अवरोध;
	हाल RF90_PATH_C:
		क्रम (i = 0; i < RadioC_ArrayLength; i += 2) अणु
			अगर (Rtl819XRadioC_Array[i] == 0xfe) अणु
				msleep(100);
				जारी;
			पूर्ण
			rtl92e_set_rf_reg(dev, eRFPath, Rtl819XRadioC_Array[i],
					  bMask12Bits,
					  Rtl819XRadioC_Array[i+1]);

		पूर्ण
		अवरोध;
	हाल RF90_PATH_D:
		क्रम (i = 0; i < RadioD_ArrayLength; i += 2) अणु
			अगर (Rtl819XRadioD_Array[i] == 0xfe) अणु
				msleep(100);
				जारी;
			पूर्ण
			rtl92e_set_rf_reg(dev, eRFPath, Rtl819XRadioD_Array[i],
					  bMask12Bits,
					  Rtl819XRadioD_Array[i+1]);

		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;

पूर्ण

अटल व्योम _rtl92e_set_tx_घातer_level(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8	घातerlevel = priv->TxPowerLevelCCK[channel-1];
	u8	घातerlevelOFDM24G = priv->TxPowerLevelOFDM24G[channel-1];

	चयन (priv->rf_chip) अणु
	हाल RF_8225:
		अवरोध;

	हाल RF_8256:
		rtl92e_set_cck_tx_घातer(dev, घातerlevel);
		rtl92e_set_ofdm_tx_घातer(dev, घातerlevelOFDM24G);
		अवरोध;

	हाल RF_8258:
		अवरोध;
	शेष:
		netdev_warn(dev, "%s(): Invalid RF Chip ID\n", __func__);
		अवरोध;
	पूर्ण
पूर्ण

अटल u8 _rtl92e_phy_set_sw_chnl_cmd_array(काष्ठा net_device *dev,
					    काष्ठा sw_chnl_cmd *CmdTable,
					    u32 CmdTableIdx, u32 CmdTableSz,
					    क्रमागत sw_chnl_cmd_id CmdID,
					    u32 Para1, u32 Para2, u32 msDelay)
अणु
	काष्ठा sw_chnl_cmd *pCmd;

	अगर (CmdTable == शून्य) अणु
		netdev_err(dev, "%s(): CmdTable cannot be NULL.\n", __func__);
		वापस false;
	पूर्ण
	अगर (CmdTableIdx >= CmdTableSz) अणु
		netdev_err(dev, "%s(): Invalid index requested.\n", __func__);
		वापस false;
	पूर्ण

	pCmd = CmdTable + CmdTableIdx;
	pCmd->CmdID = CmdID;
	pCmd->Para1 = Para1;
	pCmd->Para2 = Para2;
	pCmd->msDelay = msDelay;

	वापस true;
पूर्ण

अटल u8 _rtl92e_phy_चयन_channel_step(काष्ठा net_device *dev, u8 channel,
					  u8 *stage, u8 *step, u32 *delay)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;
	u32					PreCommonCmdCnt;
	u32					PostCommonCmdCnt;
	u32					RfDependCmdCnt;
	काष्ठा sw_chnl_cmd *CurrentCmd = शून्य;
	u8		eRFPath;

	RT_TRACE(COMP_TRACE, "====>%s()====stage:%d, step:%d, channel:%d\n",
		  __func__, *stage, *step, channel);

	अगर (!rtllib_legal_channel(priv->rtllib, channel)) अणु
		netdev_err(dev, "Invalid channel requested: %d\n", channel);
		वापस true;
	पूर्ण

	अणु
		PreCommonCmdCnt = 0;
		_rtl92e_phy_set_sw_chnl_cmd_array(dev, ieee->PreCommonCmd,
						  PreCommonCmdCnt++,
						  MAX_PRECMD_CNT,
						  CmdID_SetTxPowerLevel,
						  0, 0, 0);
		_rtl92e_phy_set_sw_chnl_cmd_array(dev, ieee->PreCommonCmd,
						  PreCommonCmdCnt++,
						  MAX_PRECMD_CNT, CmdID_End,
						  0, 0, 0);

		PostCommonCmdCnt = 0;

		_rtl92e_phy_set_sw_chnl_cmd_array(dev, ieee->PostCommonCmd,
						  PostCommonCmdCnt++,
						  MAX_POSTCMD_CNT, CmdID_End,
						  0, 0, 0);

		RfDependCmdCnt = 0;
		चयन (priv->rf_chip) अणु
		हाल RF_8225:
			अगर (!(channel >= 1 && channel <= 14)) अणु
				netdev_err(dev,
					   "Invalid channel requested for 8225: %d\n",
					   channel);
				वापस false;
			पूर्ण
			_rtl92e_phy_set_sw_chnl_cmd_array(dev,
							  ieee->RfDependCmd,
							  RfDependCmdCnt++,
							  MAX_RFDEPENDCMD_CNT,
							  CmdID_RF_WriteReg,
							  rZebra1_Channel,
							  RF_CHANNEL_TABLE_ZEBRA[channel],
							  10);
			_rtl92e_phy_set_sw_chnl_cmd_array(dev,
							  ieee->RfDependCmd,
							  RfDependCmdCnt++,
							  MAX_RFDEPENDCMD_CNT,
							  CmdID_End, 0, 0, 0);
			अवरोध;

		हाल RF_8256:
			अगर (!(channel >= 1 && channel <= 14)) अणु
				netdev_err(dev,
					   "Invalid channel requested for 8256: %d\n",
					   channel);
				वापस false;
			पूर्ण
			_rtl92e_phy_set_sw_chnl_cmd_array(dev,
							  ieee->RfDependCmd,
							  RfDependCmdCnt++,
							  MAX_RFDEPENDCMD_CNT,
							  CmdID_RF_WriteReg,
							  rZebra1_Channel,
							  channel, 10);
			_rtl92e_phy_set_sw_chnl_cmd_array(dev,
							  ieee->RfDependCmd,
							  RfDependCmdCnt++,
							  MAX_RFDEPENDCMD_CNT,
							  CmdID_End, 0, 0, 0);
			अवरोध;

		हाल RF_8258:
			अवरोध;

		शेष:
			netdev_warn(dev, "Unknown RF Chip ID\n");
			वापस false;
		पूर्ण


		करो अणु
			चयन (*stage) अणु
			हाल 0:
				CurrentCmd = &ieee->PreCommonCmd[*step];
				अवरोध;
			हाल 1:
				CurrentCmd = &ieee->RfDependCmd[*step];
				अवरोध;
			हाल 2:
				CurrentCmd = &ieee->PostCommonCmd[*step];
				अवरोध;
			पूर्ण

			अगर (CurrentCmd && CurrentCmd->CmdID == CmdID_End) अणु
				अगर ((*stage) == 2)
					वापस true;
				(*stage)++;
				(*step) = 0;
				जारी;
			पूर्ण

			अगर (!CurrentCmd)
				जारी;
			चयन (CurrentCmd->CmdID) अणु
			हाल CmdID_SetTxPowerLevel:
				अगर (priv->IC_Cut > (u8)VERSION_8190_BD)
					_rtl92e_set_tx_घातer_level(dev,
								   channel);
				अवरोध;
			हाल CmdID_WritePortUदीर्घ:
				rtl92e_ग_लिखोl(dev, CurrentCmd->Para1,
					      CurrentCmd->Para2);
				अवरोध;
			हाल CmdID_WritePortUलघु:
				rtl92e_ग_लिखोw(dev, CurrentCmd->Para1,
					      (u16)CurrentCmd->Para2);
				अवरोध;
			हाल CmdID_WritePortUअक्षर:
				rtl92e_ग_लिखोb(dev, CurrentCmd->Para1,
					      (u8)CurrentCmd->Para2);
				अवरोध;
			हाल CmdID_RF_WriteReg:
				क्रम (eRFPath = 0; eRFPath <
				     priv->NumTotalRFPath; eRFPath++)
					rtl92e_set_rf_reg(dev,
						 (क्रमागत rf90_radio_path)eRFPath,
						 CurrentCmd->Para1, bMask12Bits,
						 CurrentCmd->Para2<<7);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			अवरोध;
		पूर्ण जबतक (true);
	पूर्ण /*क्रम (Number of RF paths)*/

	(*delay) = CurrentCmd->msDelay;
	(*step)++;
	वापस false;
पूर्ण

अटल व्योम _rtl92e_phy_चयन_channel(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 delay = 0;

	जबतक (!_rtl92e_phy_चयन_channel_step(dev, channel,
						&priv->SwChnlStage,
						&priv->SwChnlStep, &delay)) अणु
		अगर (delay > 0)
			msleep(delay);
		अगर (!priv->up)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_phy_चयन_channel_work_item(काष्ठा net_device *dev)
अणु

	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_TRACE, "==> SwChnlCallback819xUsbWorkItem()\n");

	RT_TRACE(COMP_TRACE, "=====>--%s(), set chan:%d, priv:%p\n", __func__,
		 priv->chan, priv);

	_rtl92e_phy_चयन_channel(dev, priv->chan);

	RT_TRACE(COMP_TRACE, "<== SwChnlCallback819xUsbWorkItem()\n");
पूर्ण

u8 rtl92e_set_channel(काष्ठा net_device *dev, u8 channel)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_PHY, "=====>%s()\n", __func__);
	अगर (!priv->up) अणु
		netdev_err(dev, "%s(): Driver is not initialized\n", __func__);
		वापस false;
	पूर्ण
	अगर (priv->SwChnlInProgress)
		वापस false;


	चयन (priv->rtllib->mode) अणु
	हाल WIRELESS_MODE_A:
	हाल WIRELESS_MODE_N_5G:
		अगर (channel <= 14) अणु
			netdev_warn(dev,
				    "Channel %d not available in 802.11a.\n",
				    channel);
			वापस false;
		पूर्ण
		अवरोध;
	हाल WIRELESS_MODE_B:
		अगर (channel > 14) अणु
			netdev_warn(dev,
				    "Channel %d not available in 802.11b.\n",
				    channel);
			वापस false;
		पूर्ण
		अवरोध;
	हाल WIRELESS_MODE_G:
	हाल WIRELESS_MODE_N_24G:
		अगर (channel > 14) अणु
			netdev_warn(dev,
				    "Channel %d not available in 802.11g.\n",
				    channel);
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण

	priv->SwChnlInProgress = true;
	अगर (channel == 0)
		channel = 1;

	priv->chan = channel;

	priv->SwChnlStage = 0;
	priv->SwChnlStep = 0;

	अगर (priv->up)
		_rtl92e_phy_चयन_channel_work_item(dev);
	priv->SwChnlInProgress = false;
	वापस true;
पूर्ण

अटल व्योम _rtl92e_cck_tx_घातer_track_bw_चयन_tssi(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	चयन (priv->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		priv->CCKPresentAttentuation =
			priv->CCKPresentAttentuation_20Mशेष +
			    priv->CCKPresentAttentuation_dअगरference;

		अगर (priv->CCKPresentAttentuation >
		    (CCKTxBBGainTableLength-1))
			priv->CCKPresentAttentuation =
					 CCKTxBBGainTableLength-1;
		अगर (priv->CCKPresentAttentuation < 0)
			priv->CCKPresentAttentuation = 0;

		RT_TRACE(COMP_POWER_TRACKING,
			 "20M, priv->CCKPresentAttentuation = %d\n",
			 priv->CCKPresentAttentuation);

		अगर (priv->rtllib->current_network.channel == 14 &&
		    !priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = true;
			rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अगर (priv->rtllib->current_network.channel !=
			   14 && priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = false;
			rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अणु
			rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण
		अवरोध;

	हाल HT_CHANNEL_WIDTH_20_40:
		priv->CCKPresentAttentuation =
			priv->CCKPresentAttentuation_40Mशेष +
			priv->CCKPresentAttentuation_dअगरference;

		RT_TRACE(COMP_POWER_TRACKING,
			 "40M, priv->CCKPresentAttentuation = %d\n",
			 priv->CCKPresentAttentuation);
		अगर (priv->CCKPresentAttentuation >
		    (CCKTxBBGainTableLength - 1))
			priv->CCKPresentAttentuation =
					 CCKTxBBGainTableLength-1;
		अगर (priv->CCKPresentAttentuation < 0)
			priv->CCKPresentAttentuation = 0;

		अगर (priv->rtllib->current_network.channel == 14 &&
		    !priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = true;
			rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अगर (priv->rtllib->current_network.channel != 14
			   && priv->bcck_in_ch14) अणु
			priv->bcck_in_ch14 = false;
			rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण अन्यथा अणु
			rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_cck_tx_घातer_track_bw_चयन_thermal(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->rtllib->current_network.channel == 14 &&
	    !priv->bcck_in_ch14)
		priv->bcck_in_ch14 = true;
	अन्यथा अगर (priv->rtllib->current_network.channel != 14 &&
		 priv->bcck_in_ch14)
		priv->bcck_in_ch14 = false;

	चयन (priv->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		अगर (priv->Record_CCK_20Mindex == 0)
			priv->Record_CCK_20Mindex = 6;
		priv->CCK_index = priv->Record_CCK_20Mindex;
		RT_TRACE(COMP_POWER_TRACKING,
			 "20MHz, %s,CCK_index = %d\n", __func__,
			 priv->CCK_index);
	अवरोध;

	हाल HT_CHANNEL_WIDTH_20_40:
		priv->CCK_index = priv->Record_CCK_40Mindex;
		RT_TRACE(COMP_POWER_TRACKING,
			 "40MHz, %s, CCK_index = %d\n", __func__,
			 priv->CCK_index);
	अवरोध;
	पूर्ण
	rtl92e_dm_cck_txघातer_adjust(dev, priv->bcck_in_ch14);
पूर्ण

अटल व्योम _rtl92e_cck_tx_घातer_track_bw_चयन(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->IC_Cut >= IC_VersionCut_D)
		_rtl92e_cck_tx_घातer_track_bw_चयन_tssi(dev);
	अन्यथा
		_rtl92e_cck_tx_घातer_track_bw_चयन_thermal(dev);
पूर्ण

अटल व्योम _rtl92e_set_bw_mode_work_item(काष्ठा net_device *dev)
अणु

	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 regBwOpMode;

	RT_TRACE(COMP_SWBW,
		 "==>%s Switch to %s bandwidth\n", __func__,
		 priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20 ?
			 "20MHz" : "40MHz");


	अगर (priv->rf_chip == RF_PSEUDO_11N) अणु
		priv->SetBWModeInProgress = false;
		वापस;
	पूर्ण
	अगर (!priv->up) अणु
		netdev_err(dev, "%s(): Driver is not initialized\n", __func__);
		वापस;
	पूर्ण
	regBwOpMode = rtl92e_पढ़ोb(dev, BW_OPMODE);

	चयन (priv->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		regBwOpMode |= BW_OPMODE_20MHZ;
		rtl92e_ग_लिखोb(dev, BW_OPMODE, regBwOpMode);
		अवरोध;

	हाल HT_CHANNEL_WIDTH_20_40:
		regBwOpMode &= ~BW_OPMODE_20MHZ;
		rtl92e_ग_लिखोb(dev, BW_OPMODE, regBwOpMode);
		अवरोध;

	शेष:
		netdev_err(dev, "%s(): unknown Bandwidth: %#X\n", __func__,
			   priv->CurrentChannelBW);
		अवरोध;
	पूर्ण

	चयन (priv->CurrentChannelBW) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl92e_set_bb_reg(dev, rFPGA0_RFMOD, bRFMOD, 0x0);
		rtl92e_set_bb_reg(dev, rFPGA1_RFMOD, bRFMOD, 0x0);

		अगर (!priv->btxघातer_tracking) अणु
			rtl92e_ग_लिखोl(dev, rCCK0_TxFilter1, 0x1a1b0000);
			rtl92e_ग_लिखोl(dev, rCCK0_TxFilter2, 0x090e1317);
			rtl92e_ग_लिखोl(dev, rCCK0_DebugPort, 0x00000204);
		पूर्ण अन्यथा अणु
			_rtl92e_cck_tx_घातer_track_bw_चयन(dev);
		पूर्ण

		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x00100000, 1);

		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl92e_set_bb_reg(dev, rFPGA0_RFMOD, bRFMOD, 0x1);
		rtl92e_set_bb_reg(dev, rFPGA1_RFMOD, bRFMOD, 0x1);

		अगर (!priv->btxघातer_tracking) अणु
			rtl92e_ग_लिखोl(dev, rCCK0_TxFilter1, 0x35360000);
			rtl92e_ग_लिखोl(dev, rCCK0_TxFilter2, 0x121c252e);
			rtl92e_ग_लिखोl(dev, rCCK0_DebugPort, 0x00000409);
		पूर्ण अन्यथा अणु
			_rtl92e_cck_tx_घातer_track_bw_चयन(dev);
		पूर्ण

		rtl92e_set_bb_reg(dev, rCCK0_System, bCCKSideBand,
				  (priv->nCur40MhzPrimeSC>>1));
		rtl92e_set_bb_reg(dev, rOFDM1_LSTF, 0xC00,
				  priv->nCur40MhzPrimeSC);

		rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x00100000, 0);
		अवरोध;
	शेष:
		netdev_err(dev, "%s(): unknown Bandwidth: %#X\n", __func__,
			   priv->CurrentChannelBW);
		अवरोध;

	पूर्ण

	चयन (priv->rf_chip) अणु
	हाल RF_8225:
		अवरोध;

	हाल RF_8256:
		rtl92e_set_bandwidth(dev, priv->CurrentChannelBW);
		अवरोध;

	हाल RF_8258:
		अवरोध;

	हाल RF_PSEUDO_11N:
		अवरोध;

	शेष:
		netdev_info(dev, "%s(): Unknown RFChipID: %d\n", __func__,
			    priv->rf_chip);
		अवरोध;
	पूर्ण

	atomic_dec(&(priv->rtllib->aपंचांग_swbw));
	priv->SetBWModeInProgress = false;

	RT_TRACE(COMP_SWBW, "<==SetBWMode819xUsb()");
पूर्ण

व्योम rtl92e_set_bw_mode(काष्ठा net_device *dev, क्रमागत ht_channel_width Bandwidth,
			क्रमागत ht_extchnl_offset Offset)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);


	अगर (priv->SetBWModeInProgress)
		वापस;

	atomic_inc(&(priv->rtllib->aपंचांग_swbw));
	priv->SetBWModeInProgress = true;

	priv->CurrentChannelBW = Bandwidth;

	अगर (Offset == HT_EXTCHNL_OFFSET_LOWER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_UPPER;
	अन्यथा अगर (Offset == HT_EXTCHNL_OFFSET_UPPER)
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_LOWER;
	अन्यथा
		priv->nCur40MhzPrimeSC = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

	_rtl92e_set_bw_mode_work_item(dev);

पूर्ण

व्योम rtl92e_init_gain(काष्ठा net_device *dev, u8 Operation)
अणु
#घोषणा SCAN_RX_INITIAL_GAIN	0x17
#घोषणा POWER_DETECTION_TH	0x08
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 BitMask;
	u8 initial_gain;

	अगर (priv->up) अणु
		चयन (Operation) अणु
		हाल IG_Backup:
			RT_TRACE(COMP_SCAN,
				 "IG_Backup, backup the initial gain.\n");
			initial_gain = SCAN_RX_INITIAL_GAIN;
			BitMask = bMaskByte0;
			अगर (dm_digtable.dig_algorithm ==
			    DIG_ALGO_BY_FALSE_ALARM)
				rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x8);
			priv->initgain_backup.xaagccore1 =
				 (u8)rtl92e_get_bb_reg(dev, rOFDM0_XAAGCCore1,
						       BitMask);
			priv->initgain_backup.xbagccore1 =
				 (u8)rtl92e_get_bb_reg(dev, rOFDM0_XBAGCCore1,
						       BitMask);
			priv->initgain_backup.xcagccore1 =
				 (u8)rtl92e_get_bb_reg(dev, rOFDM0_XCAGCCore1,
						       BitMask);
			priv->initgain_backup.xdagccore1 =
				 (u8)rtl92e_get_bb_reg(dev, rOFDM0_XDAGCCore1,
						       BitMask);
			BitMask = bMaskByte2;
			priv->initgain_backup.cca = (u8)rtl92e_get_bb_reg(dev,
						    rCCK0_CCA, BitMask);

			RT_TRACE(COMP_SCAN,
				 "Scan InitialGainBackup 0xc50 is %x\n",
				 priv->initgain_backup.xaagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan InitialGainBackup 0xc58 is %x\n",
				 priv->initgain_backup.xbagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan InitialGainBackup 0xc60 is %x\n",
				 priv->initgain_backup.xcagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan InitialGainBackup 0xc68 is %x\n",
				 priv->initgain_backup.xdagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan InitialGainBackup 0xa0a is %x\n",
				 priv->initgain_backup.cca);

			RT_TRACE(COMP_SCAN, "Write scan initial gain = 0x%x\n",
				 initial_gain);
			rtl92e_ग_लिखोb(dev, rOFDM0_XAAGCCore1, initial_gain);
			rtl92e_ग_लिखोb(dev, rOFDM0_XBAGCCore1, initial_gain);
			rtl92e_ग_लिखोb(dev, rOFDM0_XCAGCCore1, initial_gain);
			rtl92e_ग_लिखोb(dev, rOFDM0_XDAGCCore1, initial_gain);
			RT_TRACE(COMP_SCAN, "Write scan 0xa0a = 0x%x\n",
				 POWER_DETECTION_TH);
			rtl92e_ग_लिखोb(dev, 0xa0a, POWER_DETECTION_TH);
			अवरोध;
		हाल IG_Restore:
			RT_TRACE(COMP_SCAN,
				 "IG_Restore, restore the initial gain.\n");
			BitMask = 0x7f;
			अगर (dm_digtable.dig_algorithm ==
			    DIG_ALGO_BY_FALSE_ALARM)
				rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x8);

			rtl92e_set_bb_reg(dev, rOFDM0_XAAGCCore1, BitMask,
					 (u32)priv->initgain_backup.xaagccore1);
			rtl92e_set_bb_reg(dev, rOFDM0_XBAGCCore1, BitMask,
					 (u32)priv->initgain_backup.xbagccore1);
			rtl92e_set_bb_reg(dev, rOFDM0_XCAGCCore1, BitMask,
					 (u32)priv->initgain_backup.xcagccore1);
			rtl92e_set_bb_reg(dev, rOFDM0_XDAGCCore1, BitMask,
					 (u32)priv->initgain_backup.xdagccore1);
			BitMask  = bMaskByte2;
			rtl92e_set_bb_reg(dev, rCCK0_CCA, BitMask,
					 (u32)priv->initgain_backup.cca);

			RT_TRACE(COMP_SCAN,
				 "Scan BBInitialGainRestore 0xc50 is %x\n",
				 priv->initgain_backup.xaagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan BBInitialGainRestore 0xc58 is %x\n",
				 priv->initgain_backup.xbagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan BBInitialGainRestore 0xc60 is %x\n",
				 priv->initgain_backup.xcagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan BBInitialGainRestore 0xc68 is %x\n",
				 priv->initgain_backup.xdagccore1);
			RT_TRACE(COMP_SCAN,
				 "Scan BBInitialGainRestore 0xa0a is %x\n",
				 priv->initgain_backup.cca);

			rtl92e_set_tx_घातer(dev,
					 priv->rtllib->current_network.channel);

			अगर (dm_digtable.dig_algorithm ==
			    DIG_ALGO_BY_FALSE_ALARM)
				rtl92e_set_bb_reg(dev, UFWP, bMaskByte1, 0x1);
			अवरोध;
		शेष:
			RT_TRACE(COMP_SCAN, "Unknown IG Operation.\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92e_set_rf_off(काष्ठा net_device *dev)
अणु

	rtl92e_set_bb_reg(dev, rFPGA0_XA_RFInterfaceOE, BIT4, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter4, 0x300, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x18, 0x0);
	rtl92e_set_bb_reg(dev, rOFDM0_TRxPathEnable, 0xf, 0x0);
	rtl92e_set_bb_reg(dev, rOFDM1_TRxPathEnable, 0xf, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x60, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x4, 0x0);
	rtl92e_ग_लिखोb(dev, ANAPAR_FOR_8192PciE, 0x07);

पूर्ण

अटल bool _rtl92e_set_rf_घातer_state(काष्ठा net_device *dev,
				       क्रमागत rt_rf_घातer_state eRFPowerState)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_pwr_save_ctrl *pPSC = (काष्ठा rt_pwr_save_ctrl *)
					(&(priv->rtllib->PowerSaveControl));
	bool bResult = true;
	u8	i = 0, QueueID = 0;
	काष्ठा rtl8192_tx_ring  *ring = शून्य;

	अगर (priv->SetRFPowerStateInProgress)
		वापस false;
	RT_TRACE(COMP_PS, "===========> %s!\n", __func__);
	priv->SetRFPowerStateInProgress = true;

	चयन (priv->rf_chip) अणु
	हाल RF_8256:
		चयन (eRFPowerState) अणु
		हाल eRfOn:
			RT_TRACE(COMP_PS, "%s eRfOn!\n", __func__);
			अगर ((priv->rtllib->eRFPowerState == eRfOff) &&
			     RT_IN_PS_LEVEL(pPSC, RT_RF_OFF_LEVL_HALT_NIC)) अणु
				bool rtstatus;
				u32 InitilizeCount = 3;

				करो अणु
					InitilizeCount--;
					priv->RegRfOff = false;
					rtstatus = rtl92e_enable_nic(dev);
				पूर्ण जबतक (!rtstatus && (InitilizeCount > 0));

				अगर (!rtstatus) अणु
					netdev_err(dev,
						   "%s(): Failed to initialize Adapter.\n",
						   __func__);
					priv->SetRFPowerStateInProgress = false;
					वापस false;
				पूर्ण

				RT_CLEAR_PS_LEVEL(pPSC,
						  RT_RF_OFF_LEVL_HALT_NIC);
			पूर्ण अन्यथा अणु
				rtl92e_ग_लिखोb(dev, ANAPAR, 0x37);
				mdelay(1);
				rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1,
						 0x4, 0x1);
				priv->bHwRfOffAction = 0;

				rtl92e_set_bb_reg(dev, rFPGA0_XA_RFInterfaceOE,
						  BIT4, 0x1);
				rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter4,
						  0x300, 0x3);
				rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1,
						  0x18, 0x3);
				rtl92e_set_bb_reg(dev, rOFDM0_TRxPathEnable,
						  0x3, 0x3);
				rtl92e_set_bb_reg(dev, rOFDM1_TRxPathEnable,
						  0x3, 0x3);
				rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1,
						  0x60, 0x3);

			पूर्ण

			अवरोध;

		हाल eRfSleep:
			अगर (priv->rtllib->eRFPowerState == eRfOff)
				अवरोध;


			क्रम (QueueID = 0, i = 0; QueueID < MAX_TX_QUEUE; ) अणु
				ring = &priv->tx_ring[QueueID];

				अगर (skb_queue_len(&ring->queue) == 0) अणु
					QueueID++;
					जारी;
				पूर्ण अन्यथा अणु
					RT_TRACE((COMP_POWER|COMP_RF),
						 "eRf Off/Sleep: %d times TcbBusyQueue[%d] !=0 before doze!\n",
						 (i+1), QueueID);
					udelay(10);
					i++;
				पूर्ण

				अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
					RT_TRACE(COMP_POWER, "\n\n\n TimeOut!! %s: eRfOff: %d times TcbBusyQueue[%d] != 0 !!!\n",
						 __func__, MAX_DOZE_WAITING_TIMES_9x, QueueID);
					अवरोध;
				पूर्ण
			पूर्ण
			rtl92e_set_rf_off(dev);
			अवरोध;

		हाल eRfOff:
			RT_TRACE(COMP_PS, "%s eRfOff/Sleep !\n", __func__);

			क्रम (QueueID = 0, i = 0; QueueID < MAX_TX_QUEUE; ) अणु
				ring = &priv->tx_ring[QueueID];

				अगर (skb_queue_len(&ring->queue) == 0) अणु
					QueueID++;
					जारी;
				पूर्ण अन्यथा अणु
					RT_TRACE(COMP_POWER,
						 "eRf Off/Sleep: %d times TcbBusyQueue[%d] !=0 before doze!\n",
						 (i+1), QueueID);
					udelay(10);
					i++;
				पूर्ण

				अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
					RT_TRACE(COMP_POWER,
						 "\n\n\n SetZebra: RFPowerState8185B(): eRfOff: %d times TcbBusyQueue[%d] != 0 !!!\n",
						 MAX_DOZE_WAITING_TIMES_9x,
						 QueueID);
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (pPSC->RegRfPsLevel & RT_RF_OFF_LEVL_HALT_NIC &&
			    !RT_IN_PS_LEVEL(pPSC, RT_RF_OFF_LEVL_HALT_NIC)) अणु
				rtl92e_disable_nic(dev);
				RT_SET_PS_LEVEL(pPSC, RT_RF_OFF_LEVL_HALT_NIC);
			पूर्ण अन्यथा अगर (!(pPSC->RegRfPsLevel &
				   RT_RF_OFF_LEVL_HALT_NIC)) अणु
				rtl92e_set_rf_off(dev);
			पूर्ण

			अवरोध;

		शेष:
			bResult = false;
			netdev_warn(dev,
				    "%s(): Unknown state requested: 0x%X.\n",
				    __func__, eRFPowerState);
			अवरोध;
		पूर्ण

		अवरोध;

	शेष:
		netdev_warn(dev, "%s(): Unknown RF type\n", __func__);
		अवरोध;
	पूर्ण

	अगर (bResult) अणु
		priv->rtllib->eRFPowerState = eRFPowerState;

		चयन (priv->rf_chip) अणु
		हाल RF_8256:
			अवरोध;

		शेष:
			netdev_warn(dev, "%s(): Unknown RF type\n", __func__);
			अवरोध;
		पूर्ण
	पूर्ण

	priv->SetRFPowerStateInProgress = false;
	RT_TRACE(COMP_PS, "<=========== %s bResult = %d!\n", __func__, bResult);
	वापस bResult;
पूर्ण

bool rtl92e_set_rf_घातer_state(काष्ठा net_device *dev,
			       क्रमागत rt_rf_घातer_state eRFPowerState)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	bool bResult = false;

	RT_TRACE(COMP_PS,
		 "---------> %s: eRFPowerState(%d)\n", __func__, eRFPowerState);
	अगर (eRFPowerState == priv->rtllib->eRFPowerState &&
	    priv->bHwRfOffAction == 0) अणु
		RT_TRACE(COMP_PS, "<--------- %s: discard the request for eRFPowerState(%d) is the same.\n",
			 __func__, eRFPowerState);
		वापस bResult;
	पूर्ण

	bResult = _rtl92e_set_rf_घातer_state(dev, eRFPowerState);

	RT_TRACE(COMP_PS, "<--------- %s: bResult(%d)\n", __func__, bResult);

	वापस bResult;
पूर्ण

व्योम rtl92e_scan_op_backup(काष्ठा net_device *dev, u8 Operation)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->up) अणु
		चयन (Operation) अणु
		हाल SCAN_OPT_BACKUP:
			priv->rtllib->InitialGainHandler(dev, IG_Backup);
			अवरोध;

		हाल SCAN_OPT_RESTORE:
			priv->rtllib->InitialGainHandler(dev, IG_Restore);
			अवरोध;

		शेष:
			RT_TRACE(COMP_SCAN, "Unknown Scan Backup Operation.\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
