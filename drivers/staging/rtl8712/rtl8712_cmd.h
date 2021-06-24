<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_CMD_H_
#घोषणा __RTL8712_CMD_H_

#घोषणा CMD_HDR_SZ      8

u8 r8712_fw_cmd(काष्ठा _adapter *pAdapter, u32 cmd);
व्योम r8712_fw_cmd_data(काष्ठा _adapter *pAdapter, u32 *value, u8 flag);

काष्ठा cmd_hdr अणु
	u32 cmd_dw0;
	u32 cmd_dw1;
पूर्ण;

क्रमागत rtl8712_h2c_cmd अणु
	GEN_CMD_CODE(_Read_MACREG),	/*0*/
	GEN_CMD_CODE(_Write_MACREG),
	GEN_CMD_CODE(_Read_BBREG),
	GEN_CMD_CODE(_Write_BBREG),
	GEN_CMD_CODE(_Read_RFREG),
	GEN_CMD_CODE(_Write_RFREG), /*5*/
	GEN_CMD_CODE(_Read_EEPROM),
	GEN_CMD_CODE(_Write_EEPROM),
	GEN_CMD_CODE(_Read_EFUSE),
	GEN_CMD_CODE(_Write_EFUSE),

	GEN_CMD_CODE(_Read_CAM),	/*10*/
	GEN_CMD_CODE(_Write_CAM),
	GEN_CMD_CODE(_setBCNITV),
	GEN_CMD_CODE(_setMBIDCFG),
	GEN_CMD_CODE(_JoinBss),   /*14*/
	GEN_CMD_CODE(_DisConnect), /*15*/
	GEN_CMD_CODE(_CreateBss),
	GEN_CMD_CODE(_SetOpMode),
	GEN_CMD_CODE(_SiteSurvey),  /*18*/
	GEN_CMD_CODE(_SetAuth),

	GEN_CMD_CODE(_SetKey),	/*20*/
	GEN_CMD_CODE(_SetStaKey),
	GEN_CMD_CODE(_SetAssocSta),
	GEN_CMD_CODE(_DelAssocSta),
	GEN_CMD_CODE(_SetStaPwrState),
	GEN_CMD_CODE(_SetBasicRate), /*25*/
	GEN_CMD_CODE(_GetBasicRate),
	GEN_CMD_CODE(_SetDataRate),
	GEN_CMD_CODE(_GetDataRate),
	GEN_CMD_CODE(_SetPhyInfo),

	GEN_CMD_CODE(_GetPhyInfo),	/*30*/
	GEN_CMD_CODE(_SetPhy),
	GEN_CMD_CODE(_GetPhy),
	GEN_CMD_CODE(_पढ़ोRssi),
	GEN_CMD_CODE(_पढ़ोGain),
	GEN_CMD_CODE(_SetAtim), /*35*/
	GEN_CMD_CODE(_SetPwrMode),
	GEN_CMD_CODE(_JoinbssRpt),
	GEN_CMD_CODE(_SetRaTable),
	GEN_CMD_CODE(_GetRaTable),

	GEN_CMD_CODE(_GetCCXReport), /*40*/
	GEN_CMD_CODE(_GetDTMReport),
	GEN_CMD_CODE(_GetTXRateStatistics),
	GEN_CMD_CODE(_SetUsbSuspend),
	GEN_CMD_CODE(_SetH2cLbk),
	GEN_CMD_CODE(_AddBAReq), /*45*/

	GEN_CMD_CODE(_SetChannel), /*46*/
/* MP_OFFLOAD Start (47~54)*/
	GEN_CMD_CODE(_SetTxPower),
	GEN_CMD_CODE(_SwitchAntenna),
	GEN_CMD_CODE(_SetCrystalCap),
	GEN_CMD_CODE(_SetSingleCarrierTx), /*50*/
	GEN_CMD_CODE(_SetSingleToneTx),
	GEN_CMD_CODE(_SetCarrierSuppressionTx),
	GEN_CMD_CODE(_SetContinuousTx),
	GEN_CMD_CODE(_SwitchBandwidth), /*54*/
/* MP_OFFLOAD End*/
	GEN_CMD_CODE(_TX_Beacon), /*55*/
	GEN_CMD_CODE(_SetPowerTracking),
	GEN_CMD_CODE(_AMSDU_TO_AMPDU), /*57*/
	GEN_CMD_CODE(_SetMacAddress), /*58*/

	GEN_CMD_CODE(_DisconnectCtrl), /*59*/
	GEN_CMD_CODE(_SetChannelPlan), /*60*/
	GEN_CMD_CODE(_DisconnectCtrlEx), /*61*/

	/* To करो, modअगरy these h2c cmd, add or delete */
	GEN_CMD_CODE(_GetH2cLbk),

	/* WPS extra IE */
	GEN_CMD_CODE(_SetProbeReqExtraIE),
	GEN_CMD_CODE(_SetAssocReqExtraIE),
	GEN_CMD_CODE(_SetProbeRspExtraIE),
	GEN_CMD_CODE(_SetAssocRspExtraIE),

	/* the following is driver will करो */
	GEN_CMD_CODE(_GetCurDataRate),

	GEN_CMD_CODE(_GetTxRetrycnt),  /* to record बार that Tx retry to
					* transmit packet after association
					*/
	GEN_CMD_CODE(_GetRxRetrycnt),  /* to record total number of the
					* received frame with ReTry bit set in
					* the WLAN header
					*/

	GEN_CMD_CODE(_GetBCNOKcnt),
	GEN_CMD_CODE(_GetBCNERRcnt),
	GEN_CMD_CODE(_GetCurTxPwrLevel),

	GEN_CMD_CODE(_SetDIG),
	GEN_CMD_CODE(_SetRA),
	GEN_CMD_CODE(_SetPT),
	GEN_CMD_CODE(_ReadTSSI),

	MAX_H2CCMD
पूर्ण;

#घोषणा _GetBBReg_CMD_		_Read_BBREG_CMD_
#घोषणा _SetBBReg_CMD_		_Write_BBREG_CMD_
#घोषणा _GetRFReg_CMD_		_Read_RFREG_CMD_
#घोषणा _SetRFReg_CMD_		_Write_RFREG_CMD_
#घोषणा _DRV_INT_CMD_		(MAX_H2CCMD + 1)
#घोषणा _SetRFIntFs_CMD_	(MAX_H2CCMD + 2)

#अगर_घोषित _RTL8712_CMD_C_
अटल काष्ठा _cmd_callback	cmd_callback[] = अणु
	अणुGEN_CMD_CODE(_Read_MACREG), शून्यपूर्ण, /*0*/
	अणुGEN_CMD_CODE(_Write_MACREG), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Read_BBREG), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Write_BBREG), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Read_RFREG), &r8712_getbbrfreg_cmdrsp_callbackपूर्ण,
	अणुGEN_CMD_CODE(_Write_RFREG), शून्यपूर्ण, /*5*/
	अणुGEN_CMD_CODE(_Read_EEPROM), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Write_EEPROM), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Read_EFUSE), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_Write_EFUSE), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_Read_CAM),	शून्यपूर्ण,	/*10*/
	अणुGEN_CMD_CODE(_Write_CAM),	 शून्यपूर्ण,
	अणुGEN_CMD_CODE(_setBCNITV), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_setMBIDCFG), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_JoinBss), &r8712_joinbss_cmd_callbackपूर्ण,  /*14*/
	अणुGEN_CMD_CODE(_DisConnect), &r8712_disassoc_cmd_callbackपूर्ण, /*15*/
	अणुGEN_CMD_CODE(_CreateBss), &r8712_createbss_cmd_callbackपूर्ण,
	अणुGEN_CMD_CODE(_SetOpMode), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SiteSurvey), &r8712_survey_cmd_callbackपूर्ण, /*18*/
	अणुGEN_CMD_CODE(_SetAuth), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_SetKey), शून्यपूर्ण,	/*20*/
	अणुGEN_CMD_CODE(_SetStaKey), &r8712_setstaKey_cmdrsp_callbackपूर्ण,
	अणुGEN_CMD_CODE(_SetAssocSta), &r8712_setassocsta_cmdrsp_callbackपूर्ण,
	अणुGEN_CMD_CODE(_DelAssocSta), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetStaPwrState), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetBasicRate), शून्यपूर्ण, /*25*/
	अणुGEN_CMD_CODE(_GetBasicRate), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetDataRate), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetDataRate), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetPhyInfo), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_GetPhyInfo), शून्यपूर्ण, /*30*/
	अणुGEN_CMD_CODE(_SetPhy), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetPhy), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_पढ़ोRssi), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_पढ़ोGain), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetAtim), शून्यपूर्ण, /*35*/
	अणुGEN_CMD_CODE(_SetPwrMode), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_JoinbssRpt), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetRaTable), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetRaTable), शून्यपूर्ण,

	अणुGEN_CMD_CODE(_GetCCXReport), शून्यपूर्ण, /*40*/
	अणुGEN_CMD_CODE(_GetDTMReport),	शून्यपूर्ण,
	अणुGEN_CMD_CODE(_GetTXRateStatistics), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetUsbSuspend), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetH2cLbk), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_AddBAReq), शून्यपूर्ण, /*45*/

	अणुGEN_CMD_CODE(_SetChannel), शून्यपूर्ण,		/*46*/
/* MP_OFFLOAD Start (47~54)*/
	अणुGEN_CMD_CODE(_SetTxPower), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SwitchAntenna), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetCrystalCap), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetSingleCarrierTx), शून्यपूर्ण,	/*50*/
	अणुGEN_CMD_CODE(_SetSingleToneTx), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetCarrierSuppressionTx), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SetContinuousTx), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_SwitchBandwidth), शून्यपूर्ण,		/*54*/
/* MP_OFFLOAD End*/
	अणुGEN_CMD_CODE(_TX_Beacon), शून्यपूर्ण, /*55*/
	अणुGEN_CMD_CODE(_SetPowerTracking), शून्यपूर्ण,
	अणुGEN_CMD_CODE(_AMSDU_TO_AMPDU), शून्यपूर्ण, /*57*/
	अणुGEN_CMD_CODE(_SetMacAddress), शून्यपूर्ण, /*58*/

	अणुGEN_CMD_CODE(_DisconnectCtrl), शून्यपूर्ण, /*59*/
	अणुGEN_CMD_CODE(_SetChannelPlan), शून्यपूर्ण, /*60*/
	अणुGEN_CMD_CODE(_DisconnectCtrlEx), शून्यपूर्ण, /*61*/

	/* To करो, modअगरy these h2c cmd, add or delete */
	अणुGEN_CMD_CODE(_GetH2cLbk), शून्यपूर्ण,

	अणु_SetProbeReqExtraIE_CMD_, शून्यपूर्ण,
	अणु_SetAssocReqExtraIE_CMD_, शून्यपूर्ण,
	अणु_SetProbeRspExtraIE_CMD_, शून्यपूर्ण,
	अणु_SetAssocRspExtraIE_CMD_, शून्यपूर्ण,
	अणु_GetCurDataRate_CMD_, शून्यपूर्ण,
	अणु_GetTxRetrycnt_CMD_, शून्यपूर्ण,
	अणु_GetRxRetrycnt_CMD_, शून्यपूर्ण,
	अणु_GetBCNOKcnt_CMD_, शून्यपूर्ण,
	अणु_GetBCNERRcnt_CMD_, शून्यपूर्ण,
	अणु_GetCurTxPwrLevel_CMD_, शून्यपूर्ण,
	अणु_SetDIG_CMD_, शून्यपूर्ण,
	अणु_SetRA_CMD_, शून्यपूर्ण,
	अणु_SetPT_CMD_, शून्यपूर्ण,
	अणुGEN_CMD_CODE(_ReadTSSI), &r8712_पढ़ोtssi_cmdrsp_callbackपूर्ण
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर
