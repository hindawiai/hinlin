<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _SDIO_HALINIT_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>

#समावेश "hal_com_h2c.h"
/*
 * Description:
 *Call घातer on sequence to enable card
 *
 * Return:
 *_SUCCESS	enable success
 *_FAIL		enable fail
 */
अटल u8 CardEnable(काष्ठा adapter *padapter)
अणु
	u8 bMacPwrCtrlOn;
	u8 ret = _FAIL;


	rtw_hal_get_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
	अगर (!bMacPwrCtrlOn) अणु
		/*  RSV_CTRL 0x1C[7:0] = 0x00 */
		/*  unlock ISO/CLK/Power control रेजिस्टर */
		rtw_ग_लिखो8(padapter, REG_RSV_CTRL, 0x0);

		ret = HalPwrSeqCmdParsing(padapter, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, rtl8723B_card_enable_flow);
		अगर (ret == _SUCCESS) अणु
			u8 bMacPwrCtrlOn = true;
			rtw_hal_set_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
		पूर्ण
	पूर्ण अन्यथा
		ret = _SUCCESS;

	वापस ret;
पूर्ण

अटल
u8 _InitPowerOn_8723BS(काष्ठा adapter *padapter)
अणु
	u8 value8;
	u16 value16;
	u32 value32;
	u8 ret;
/* 	u8 bMacPwrCtrlOn; */


	/*  all of these MUST be configured beक्रमe घातer on */

	/*  only cmd52 can be used beक्रमe घातer on(card enable) */
	ret = CardEnable(padapter);
	अगर (!ret)
		वापस _FAIL;

	/*  Radio-Off Pin Trigger */
	value8 = rtw_पढ़ो8(padapter, REG_GPIO_INTM + 1);
	value8 |= BIT(1); /*  Enable falling edge triggering पूर्णांकerrupt */
	rtw_ग_लिखो8(padapter, REG_GPIO_INTM + 1, value8);
	value8 = rtw_पढ़ो8(padapter, REG_GPIO_IO_SEL_2 + 1);
	value8 |= BIT(1);
	rtw_ग_लिखो8(padapter, REG_GPIO_IO_SEL_2 + 1, value8);

	/*  Enable घातer करोwn and GPIO पूर्णांकerrupt */
	value16 = rtw_पढ़ो16(padapter, REG_APS_FSMCO);
	value16 |= EnPDN; /*  Enable HW घातer करोwn and RF on */
	rtw_ग_लिखो16(padapter, REG_APS_FSMCO, value16);

	/*  Enable CMD53 R/W Operation */
/* 	bMacPwrCtrlOn = true; */
/* 	rtw_hal_set_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn); */

	rtw_ग_लिखो8(padapter, REG_CR, 0x00);
	/*  Enable MAC DMA/WMAC/SCHEDULE/SEC block */
	value16 = rtw_पढ़ो16(padapter, REG_CR);
	value16 |= (
		HCI_TXDMA_EN |
		HCI_RXDMA_EN |
		TXDMA_EN |
		RXDMA_EN |
		PROTOCOL_EN |
		SCHEDULE_EN |
		ENSEC |
		CALTMR_EN
	);
	rtw_ग_लिखो16(padapter, REG_CR, value16);

	hal_btcoex_PowerOnSetting(padapter);

	/*  बाह्यal चयन to S1 */
	/*  0x38[11] = 0x1 */
	/*  0x4c[23] = 0x1 */
	/*  0x64[0] = 0 */
	value16 = rtw_पढ़ो16(padapter, REG_PWR_DATA);
	/*  Switch the control of EESK, EECS to RFC क्रम DPDT or Antenna चयन */
	value16 |= BIT(11); /*  BIT_EEPRPAD_RFE_CTRL_EN */
	rtw_ग_लिखो16(padapter, REG_PWR_DATA, value16);

	value32 = rtw_पढ़ो32(padapter, REG_LEDCFG0);
	value32 |= BIT(23); /*  DPDT_SEL_EN, 1 क्रम SW control */
	rtw_ग_लिखो32(padapter, REG_LEDCFG0, value32);

	value8 = rtw_पढ़ो8(padapter, REG_PAD_CTRL1_8723B);
	value8 &= ~BIT(0); /*  BIT_SW_DPDT_SEL_DATA, DPDT_SEL शेष configuration */
	rtw_ग_लिखो8(padapter, REG_PAD_CTRL1_8723B, value8);

	वापस _SUCCESS;
पूर्ण

/* Tx Page FIFO threshold */
अटल व्योम _init_available_page_threshold(काष्ठा adapter *padapter, u8 numHQ, u8 numNQ, u8 numLQ, u8 numPubQ)
अणु
	u16 HQ_threshold, NQ_threshold, LQ_threshold;

	HQ_threshold = (numPubQ + numHQ + 1) >> 1;
	HQ_threshold |= (HQ_threshold << 8);

	NQ_threshold = (numPubQ + numNQ + 1) >> 1;
	NQ_threshold |= (NQ_threshold << 8);

	LQ_threshold = (numPubQ + numLQ + 1) >> 1;
	LQ_threshold |= (LQ_threshold << 8);

	rtw_ग_लिखो16(padapter, 0x218, HQ_threshold);
	rtw_ग_लिखो16(padapter, 0x21A, NQ_threshold);
	rtw_ग_लिखो16(padapter, 0x21C, LQ_threshold);
पूर्ण

अटल व्योम _InitQueueReservedPage(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	u32 numHQ = 0;
	u32 numLQ = 0;
	u32 numNQ = 0;
	u32 numPubQ;
	u32 value32;
	u8 value8;
	bool bWiFiConfig	= pregistrypriv->wअगरi_spec;

	अगर (pHalData->OutEpQueueSel & TX_SELE_HQ)
		numHQ = bWiFiConfig ? WMM_NORMAL_PAGE_NUM_HPQ_8723B : NORMAL_PAGE_NUM_HPQ_8723B;

	अगर (pHalData->OutEpQueueSel & TX_SELE_LQ)
		numLQ = bWiFiConfig ? WMM_NORMAL_PAGE_NUM_LPQ_8723B : NORMAL_PAGE_NUM_LPQ_8723B;

	/*  NOTE: This step shall be proceed beक्रमe writing REG_RQPN. */
	अगर (pHalData->OutEpQueueSel & TX_SELE_NQ)
		numNQ = bWiFiConfig ? WMM_NORMAL_PAGE_NUM_NPQ_8723B : NORMAL_PAGE_NUM_NPQ_8723B;

	numPubQ = TX_TOTAL_PAGE_NUMBER_8723B - numHQ - numLQ - numNQ;

	value8 = (u8)_NPQ(numNQ);
	rtw_ग_लिखो8(padapter, REG_RQPN_NPQ, value8);

	/*  TX DMA */
	value32 = _HPQ(numHQ) | _LPQ(numLQ) | _PUBQ(numPubQ) | LD_RQPN;
	rtw_ग_लिखो32(padapter, REG_RQPN, value32);

	rtw_hal_set_sdio_tx_max_length(padapter, numHQ, numNQ, numLQ, numPubQ);

	_init_available_page_threshold(padapter, numHQ, numNQ, numLQ, numPubQ);
पूर्ण

अटल व्योम _InitTxBufferBoundary(काष्ठा adapter *padapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;

	/* u16 txdmactrl; */
	u8 txpktbuf_bndy;

	अगर (!pregistrypriv->wअगरi_spec) अणु
		txpktbuf_bndy = TX_PAGE_BOUNDARY_8723B;
	पूर्ण अन्यथा अणु
		/* क्रम WMM */
		txpktbuf_bndy = WMM_NORMAL_TX_PAGE_BOUNDARY_8723B;
	पूर्ण

	rtw_ग_लिखो8(padapter, REG_TXPKTBUF_BCNQ_BDNY_8723B, txpktbuf_bndy);
	rtw_ग_लिखो8(padapter, REG_TXPKTBUF_MGQ_BDNY_8723B, txpktbuf_bndy);
	rtw_ग_लिखो8(padapter, REG_TXPKTBUF_WMAC_LBK_BF_HD_8723B, txpktbuf_bndy);
	rtw_ग_लिखो8(padapter, REG_TRXFF_BNDY, txpktbuf_bndy);
	rtw_ग_लिखो8(padapter, REG_TDECTRL + 1, txpktbuf_bndy);
पूर्ण

अटल व्योम _InitNormalChipRegPriority(
	काष्ठा adapter *Adapter,
	u16 beQ,
	u16 bkQ,
	u16 viQ,
	u16 voQ,
	u16 mgtQ,
	u16 hiQ
)
अणु
	u16 value16 = (rtw_पढ़ो16(Adapter, REG_TRXDMA_CTRL) & 0x7);

	value16 |=
		_TXDMA_BEQ_MAP(beQ)  |
		_TXDMA_BKQ_MAP(bkQ)  |
		_TXDMA_VIQ_MAP(viQ)  |
		_TXDMA_VOQ_MAP(voQ)  |
		_TXDMA_MGQ_MAP(mgtQ) |
		_TXDMA_HIQ_MAP(hiQ);

	rtw_ग_लिखो16(Adapter, REG_TRXDMA_CTRL, value16);
पूर्ण

अटल व्योम _InitNormalChipOneOutEpPriority(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	u16 value = 0;
	चयन (pHalData->OutEpQueueSel) अणु
	हाल TX_SELE_HQ:
		value = QUEUE_HIGH;
		अवरोध;
	हाल TX_SELE_LQ:
		value = QUEUE_LOW;
		अवरोध;
	हाल TX_SELE_NQ:
		value = QUEUE_NORMAL;
		अवरोध;
	शेष:
		/* RT_ASSERT(false, ("Shall not reach here!\n")); */
		अवरोध;
	पूर्ण

	_InitNormalChipRegPriority(
		Adapter, value, value, value, value, value, value
	);

पूर्ण

अटल व्योम _InitNormalChipTwoOutEpPriority(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा registry_priv *pregistrypriv = &Adapter->registrypriv;
	u16 beQ, bkQ, viQ, voQ, mgtQ, hiQ;


	u16 valueHi = 0;
	u16 valueLow = 0;

	चयन (pHalData->OutEpQueueSel) अणु
	हाल (TX_SELE_HQ | TX_SELE_LQ):
		valueHi = QUEUE_HIGH;
		valueLow = QUEUE_LOW;
		अवरोध;
	हाल (TX_SELE_NQ | TX_SELE_LQ):
		valueHi = QUEUE_NORMAL;
		valueLow = QUEUE_LOW;
		अवरोध;
	हाल (TX_SELE_HQ | TX_SELE_NQ):
		valueHi = QUEUE_HIGH;
		valueLow = QUEUE_NORMAL;
		अवरोध;
	शेष:
		/* RT_ASSERT(false, ("Shall not reach here!\n")); */
		अवरोध;
	पूर्ण

	अगर (!pregistrypriv->wअगरi_spec) अणु
		beQ = valueLow;
		bkQ = valueLow;
		viQ = valueHi;
		voQ = valueHi;
		mgtQ = valueHi;
		hiQ = valueHi;
	पूर्ण अन्यथा अणु
		/* क्रम WMM , CONFIG_OUT_EP_WIFI_MODE */
		beQ = valueLow;
		bkQ = valueHi;
		viQ = valueHi;
		voQ = valueLow;
		mgtQ = valueHi;
		hiQ = valueHi;
	पूर्ण

	_InitNormalChipRegPriority(Adapter, beQ, bkQ, viQ, voQ, mgtQ, hiQ);

पूर्ण

अटल व्योम _InitNormalChipThreeOutEpPriority(काष्ठा adapter *padapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	u16 beQ, bkQ, viQ, voQ, mgtQ, hiQ;

	अगर (!pregistrypriv->wअगरi_spec) अणु
		/*  typical setting */
		beQ = QUEUE_LOW;
		bkQ = QUEUE_LOW;
		viQ = QUEUE_NORMAL;
		voQ = QUEUE_HIGH;
		mgtQ = QUEUE_HIGH;
		hiQ = QUEUE_HIGH;
	पूर्ण अन्यथा अणु
		/*  क्रम WMM */
		beQ = QUEUE_LOW;
		bkQ = QUEUE_NORMAL;
		viQ = QUEUE_NORMAL;
		voQ = QUEUE_HIGH;
		mgtQ = QUEUE_HIGH;
		hiQ = QUEUE_HIGH;
	पूर्ण
	_InitNormalChipRegPriority(padapter, beQ, bkQ, viQ, voQ, mgtQ, hiQ);
पूर्ण

अटल व्योम _InitQueuePriority(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	चयन (pHalData->OutEpNumber) अणु
	हाल 1:
		_InitNormalChipOneOutEpPriority(Adapter);
		अवरोध;
	हाल 2:
		_InitNormalChipTwoOutEpPriority(Adapter);
		अवरोध;
	हाल 3:
		_InitNormalChipThreeOutEpPriority(Adapter);
		अवरोध;
	शेष:
		/* RT_ASSERT(false, ("Shall not reach here!\n")); */
		अवरोध;
	पूर्ण


पूर्ण

अटल व्योम _InitPageBoundary(काष्ठा adapter *padapter)
अणु
	/*  RX Page Boundary */
	u16 rxff_bndy = RX_DMA_BOUNDARY_8723B;

	rtw_ग_लिखो16(padapter, (REG_TRXFF_BNDY + 2), rxff_bndy);
पूर्ण

अटल व्योम _InitTransferPageSize(काष्ठा adapter *padapter)
अणु
	/*  Tx page size is always 128. */

	u8 value8;
	value8 = _PSRX(PBP_128) | _PSTX(PBP_128);
	rtw_ग_लिखो8(padapter, REG_PBP, value8);
पूर्ण

अटल व्योम _InitDriverInfoSize(काष्ठा adapter *padapter, u8 drvInfoSize)
अणु
	rtw_ग_लिखो8(padapter, REG_RX_DRVINFO_SZ, drvInfoSize);
पूर्ण

अटल व्योम _InitNetworkType(काष्ठा adapter *padapter)
अणु
	u32 value32;

	value32 = rtw_पढ़ो32(padapter, REG_CR);

	/*  TODO: use the other function to set network type */
/* 	value32 = (value32 & ~MASK_NETTYPE) | _NETTYPE(NT_LINK_AD_HOC); */
	value32 = (value32 & ~MASK_NETTYPE) | _NETTYPE(NT_LINK_AP);

	rtw_ग_लिखो32(padapter, REG_CR, value32);
पूर्ण

अटल व्योम _InitWMACSetting(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData;
	u16 value16;


	pHalData = GET_HAL_DATA(padapter);

	pHalData->ReceiveConfig = 0;
	pHalData->ReceiveConfig |= RCR_APM | RCR_AM | RCR_AB;
	pHalData->ReceiveConfig |= RCR_CBSSID_DATA | RCR_CBSSID_BCN | RCR_AMF;
	pHalData->ReceiveConfig |= RCR_HTC_LOC_CTRL;
	pHalData->ReceiveConfig |= RCR_APP_PHYST_RXFF | RCR_APP_ICV | RCR_APP_MIC;
	rtw_ग_लिखो32(padapter, REG_RCR, pHalData->ReceiveConfig);

	/*  Accept all multicast address */
	rtw_ग_लिखो32(padapter, REG_MAR, 0xFFFFFFFF);
	rtw_ग_लिखो32(padapter, REG_MAR + 4, 0xFFFFFFFF);

	/*  Accept all data frames */
	value16 = 0xFFFF;
	rtw_ग_लिखो16(padapter, REG_RXFLTMAP2, value16);

	/*  2010.09.08 hpfan */
	/*  Since ADF is हटाओd from RCR, ps-poll will not be indicate to driver, */
	/*  RxFilterMap should mask ps-poll to gurantee AP mode can rx ps-poll. */
	value16 = 0x400;
	rtw_ग_लिखो16(padapter, REG_RXFLTMAP1, value16);

	/*  Accept all management frames */
	value16 = 0xFFFF;
	rtw_ग_लिखो16(padapter, REG_RXFLTMAP0, value16);
पूर्ण

अटल व्योम _InitAdaptiveCtrl(काष्ठा adapter *padapter)
अणु
	u16 value16;
	u32 value32;

	/*  Response Rate Set */
	value32 = rtw_पढ़ो32(padapter, REG_RRSR);
	value32 &= ~RATE_BITMAP_ALL;
	value32 |= RATE_RRSR_CCK_ONLY_1M;
	rtw_ग_लिखो32(padapter, REG_RRSR, value32);

	/*  CF-END Threshold */
	/* m_spIoBase->rtw_ग_लिखो8(REG_CFEND_TH, 0x1); */

	/*  SIFS (used in NAV) */
	value16 = _SPEC_SIFS_CCK(0x10) | _SPEC_SIFS_OFDM(0x10);
	rtw_ग_लिखो16(padapter, REG_SPEC_SIFS, value16);

	/*  Retry Limit */
	value16 = _LRL(0x30) | _SRL(0x30);
	rtw_ग_लिखो16(padapter, REG_RL, value16);
पूर्ण

अटल व्योम _InitEDCA(काष्ठा adapter *padapter)
अणु
	/*  Set Spec SIFS (used in NAV) */
	rtw_ग_लिखो16(padapter, REG_SPEC_SIFS, 0x100a);
	rtw_ग_लिखो16(padapter, REG_MAC_SPEC_SIFS, 0x100a);

	/*  Set SIFS क्रम CCK */
	rtw_ग_लिखो16(padapter, REG_SIFS_CTX, 0x100a);

	/*  Set SIFS क्रम OFDM */
	rtw_ग_लिखो16(padapter, REG_SIFS_TRX, 0x100a);

	/*  TXOP */
	rtw_ग_लिखो32(padapter, REG_EDCA_BE_PARAM, 0x005EA42B);
	rtw_ग_लिखो32(padapter, REG_EDCA_BK_PARAM, 0x0000A44F);
	rtw_ग_लिखो32(padapter, REG_EDCA_VI_PARAM, 0x005EA324);
	rtw_ग_लिखो32(padapter, REG_EDCA_VO_PARAM, 0x002FA226);
पूर्ण

अटल व्योम _InitRetryFunction(काष्ठा adapter *padapter)
अणु
	u8 value8;

	value8 = rtw_पढ़ो8(padapter, REG_FWHW_TXQ_CTRL);
	value8 |= EN_AMPDU_RTY_NEW;
	rtw_ग_लिखो8(padapter, REG_FWHW_TXQ_CTRL, value8);

	/*  Set ACK समयout */
	rtw_ग_लिखो8(padapter, REG_ACKTO, 0x40);
पूर्ण

अटल व्योम HalRxAggr8723BSdio(काष्ठा adapter *padapter)
अणु
	u8 valueDMATimeout;
	u8 valueDMAPageCount;

	valueDMATimeout = 0x06;
	valueDMAPageCount = 0x06;

	rtw_ग_लिखो8(padapter, REG_RXDMA_AGG_PG_TH + 1, valueDMATimeout);
	rtw_ग_लिखो8(padapter, REG_RXDMA_AGG_PG_TH, valueDMAPageCount);
पूर्ण

अटल व्योम sdio_AggSettingRxUpdate(काष्ठा adapter *padapter)
अणु
	u8 valueDMA;
	u8 valueRxAggCtrl = 0;
	u8 aggBurstNum = 3;  /* 0:1, 1:2, 2:3, 3:4 */
	u8 aggBurstSize = 0;  /* 0:1K, 1:512Byte, 2:256Byte... */

	valueDMA = rtw_पढ़ो8(padapter, REG_TRXDMA_CTRL);
	valueDMA |= RXDMA_AGG_EN;
	rtw_ग_लिखो8(padapter, REG_TRXDMA_CTRL, valueDMA);

	valueRxAggCtrl |= RXDMA_AGG_MODE_EN;
	valueRxAggCtrl |= ((aggBurstNum << 2) & 0x0C);
	valueRxAggCtrl |= ((aggBurstSize << 4) & 0x30);
	rtw_ग_लिखो8(padapter, REG_RXDMA_MODE_CTRL_8723B, valueRxAggCtrl);/* RxAggLowThresh = 4*1K */
पूर्ण

अटल व्योम _initSdioAggregationSetting(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	/*  Tx aggregation setting */
/* 	sdio_AggSettingTxUpdate(padapter); */

	/*  Rx aggregation setting */
	HalRxAggr8723BSdio(padapter);

	sdio_AggSettingRxUpdate(padapter);

	/*  201/12/10 MH Add क्रम USB agg mode dynamic चयन. */
	pHalData->UsbRxHighSpeedMode = false;
पूर्ण

अटल व्योम _InitOperationMode(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext;
	u8 regBwOpMode = 0;

	pmlmeext = &padapter->mlmeextpriv;

	/* 1 This part need to modअगरied according to the rate set we filtered!! */
	/*  */
	/*  Set RRSR, RATR, and REG_BWOPMODE रेजिस्टरs */
	/*  */
	चयन (pmlmeext->cur_wireless_mode) अणु
	हाल WIRELESS_MODE_B:
		regBwOpMode = BW_OPMODE_20MHZ;
		अवरोध;
	हाल WIRELESS_MODE_A:
/* 			RT_ASSERT(false, ("Error wireless a mode\n")); */
		अवरोध;
	हाल WIRELESS_MODE_G:
		regBwOpMode = BW_OPMODE_20MHZ;
		अवरोध;
	हाल WIRELESS_MODE_AUTO:
		regBwOpMode = BW_OPMODE_20MHZ;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
		/*  It support CCK rate by शेष. */
		/*  CCK rate will be filtered out only when associated AP करोes not support it. */
		regBwOpMode = BW_OPMODE_20MHZ;
		अवरोध;
	हाल WIRELESS_MODE_N_5G:
/* 			RT_ASSERT(false, ("Error wireless mode")); */
		regBwOpMode = BW_OPMODE_5G;
		अवरोध;

	शेष: /* क्रम MacOSX compiler warning. */
		अवरोध;
	पूर्ण

	rtw_ग_लिखो8(padapter, REG_BWOPMODE, regBwOpMode);

पूर्ण

अटल व्योम _InitInterrupt(काष्ठा adapter *padapter)
अणु
	/*  HISR - turn all off */
	rtw_ग_लिखो32(padapter, REG_HISR, 0);

	/*  HIMR - turn all off */
	rtw_ग_लिखो32(padapter, REG_HIMR, 0);

	/*  */
	/*  Initialize and enable SDIO Host Interrupt. */
	/*  */
	InitInterrupt8723BSdio(padapter);

	/*  */
	/*  Initialize प्रणाली Host Interrupt. */
	/*  */
	InitSysInterrupt8723BSdio(padapter);
पूर्ण

अटल व्योम _InitRFType(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

#अगर	DISABLE_BB_RF
	pHalData->rf_chip	= RF_PSEUDO_11N;
	वापस;
#पूर्ण_अगर

	pHalData->rf_chip	= RF_6052;

	pHalData->rf_type = RF_1T1R;
पूर्ण

अटल व्योम _RfPowerSave(काष्ठा adapter *padapter)
अणु
/* YJ, TODO */
पूर्ण

/*  */
/*  2010/08/09 MH Add क्रम घातer करोwn check. */
/*  */
अटल bool HalDetectPwrDownMode(काष्ठा adapter *Adapter)
अणु
	u8 पंचांगpvalue;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा pwrctrl_priv *pwrctrlpriv = adapter_to_pwrctl(Adapter);


	EFUSE_ShaकरोwRead(Adapter, 1, 0x7B/*EEPROM_RF_OPT3_92C*/, (u32 *)&पंचांगpvalue);

	/*  2010/08/25 MH INF priority > PDN Efuse value. */
	अगर (पंचांगpvalue & BIT4 && pwrctrlpriv->reg_pdnmode)
		pHalData->pwrकरोwn = true;
	अन्यथा
		pHalData->pwrकरोwn = false;

	वापस pHalData->pwrकरोwn;
पूर्ण	/*  HalDetectPwrDownMode */

अटल u32 rtl8723bs_hal_init(काष्ठा adapter *padapter)
अणु
	s32 ret;
	काष्ठा hal_com_data *pHalData;
	काष्ठा pwrctrl_priv *pwrctrlpriv;
	u32 NavUpper = WiFiNavUpperUs;
	u8 u1bTmp;

	pHalData = GET_HAL_DATA(padapter);
	pwrctrlpriv = adapter_to_pwrctl(padapter);

	अगर (
		adapter_to_pwrctl(padapter)->bips_processing == true &&
		adapter_to_pwrctl(padapter)->pre_ips_type == 0
	) अणु
		अचिन्हित दीर्घ start_समय;
		u8 cpwm_orig, cpwm_now;
		u8 val8, bMacPwrCtrlOn = true;

		/* क्रम polling cpwm */
		cpwm_orig = 0;
		rtw_hal_get_hwreg(padapter, HW_VAR_CPWM, &cpwm_orig);

		/* ser rpwm */
		val8 = rtw_पढ़ो8(padapter, SDIO_LOCAL_BASE | SDIO_REG_HRPWM1);
		val8 &= 0x80;
		val8 += 0x80;
		val8 |= BIT(6);
		rtw_ग_लिखो8(padapter, SDIO_LOCAL_BASE | SDIO_REG_HRPWM1, val8);
		adapter_to_pwrctl(padapter)->tog = (val8 + 0x80) & 0x80;

		/* करो polling cpwm */
		start_समय = jअगरfies;
		करो अणु

			mdelay(1);

			rtw_hal_get_hwreg(padapter, HW_VAR_CPWM, &cpwm_now);
			अगर ((cpwm_orig ^ cpwm_now) & 0x80)
				अवरोध;

			अगर (jअगरfies_to_msecs(jअगरfies - start_समय) > 100)
				अवरोध;

		पूर्ण जबतक (1);

		rtl8723b_set_FwPwrModeInIPS_cmd(padapter, 0);

		rtw_hal_set_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);

		hal_btcoex_InitHwConfig(padapter, false);

		वापस _SUCCESS;
	पूर्ण

	/*  Disable Interrupt first. */
/* 	rtw_hal_disable_पूर्णांकerrupt(padapter); */

	ret = _InitPowerOn_8723BS(padapter);
	अगर (ret == _FAIL)
		वापस _FAIL;

	rtw_ग_लिखो8(padapter, REG_EARLY_MODE_CONTROL, 0);

	ret = rtl8723b_FirmwareDownload(padapter, false);
	अगर (ret != _SUCCESS) अणु
		padapter->bFWReady = false;
		pHalData->fw_ractrl = false;
		वापस ret;
	पूर्ण अन्यथा अणु
		padapter->bFWReady = true;
		pHalData->fw_ractrl = true;
	पूर्ण

	rtl8723b_InitializeFirmwareVars(padapter);

/* 	SIC_Init(padapter); */

	अगर (pwrctrlpriv->reg_rfoff)
		pwrctrlpriv->rf_pwrstate = rf_off;

	/*  2010/08/09 MH We need to check अगर we need to turnon or off RF after detecting */
	/*  HW GPIO pin. Beक्रमe PHY_RFConfig8192C. */
	HalDetectPwrDownMode(padapter);

	/*  Set RF type क्रम BB/RF configuration */
	_InitRFType(padapter);

	/*  Save target channel */
	/*  <Roger_Notes> Current Channel will be updated again later. */
	pHalData->CurrentChannel = 6;

#अगर (HAL_MAC_ENABLE == 1)
	ret = PHY_MACConfig8723B(padapter);
	अगर (ret != _SUCCESS)
		वापस ret;
#पूर्ण_अगर
	/*  */
	/* d. Initialize BB related configurations. */
	/*  */
#अगर (HAL_BB_ENABLE == 1)
	ret = PHY_BBConfig8723B(padapter);
	अगर (ret != _SUCCESS)
		वापस ret;
#पूर्ण_अगर

	/*  If RF is on, we need to init RF. Otherwise, skip the procedure. */
	/*  We need to follow SU method to change the RF cfg.txt. Default disable RF TX/RX mode. */
	/* अगर (pHalData->eRFPowerState == eRfOn) */
	अणु
#अगर (HAL_RF_ENABLE == 1)
		ret = PHY_RFConfig8723B(padapter);
		अगर (ret != _SUCCESS)
			वापस ret;
#पूर्ण_अगर
	पूर्ण

	/*  */
	/*  Joseph Note: Keep RfRegChnlVal क्रम later use. */
	/*  */
	pHalData->RfRegChnlVal[0] =
		PHY_QueryRFReg(padapter, (क्रमागत rf_path)0, RF_CHNLBW, bRFRegOffsetMask);
	pHalData->RfRegChnlVal[1] =
		PHY_QueryRFReg(padapter, (क्रमागत rf_path)1, RF_CHNLBW, bRFRegOffsetMask);


	/* अगर (!pHalData->bMACFuncEnable) अणु */
	_InitQueueReservedPage(padapter);
	_InitTxBufferBoundary(padapter);

	/*  init LLT after tx buffer boundary is defined */
	ret = rtl8723b_InitLLTTable(padapter);
	अगर (ret != _SUCCESS)
		वापस _FAIL;

	/*  */
	_InitQueuePriority(padapter);
	_InitPageBoundary(padapter);
	_InitTransferPageSize(padapter);

	/*  Get Rx PHY status in order to report RSSI and others. */
	_InitDriverInfoSize(padapter, DRVINFO_SZ);
	hal_init_macaddr(padapter);
	_InitNetworkType(padapter);
	_InitWMACSetting(padapter);
	_InitAdaptiveCtrl(padapter);
	_InitEDCA(padapter);
	_InitRetryFunction(padapter);
	_initSdioAggregationSetting(padapter);
	_InitOperationMode(padapter);
	rtl8723b_InitBeaconParameters(padapter);
	_InitInterrupt(padapter);
	_InitBurstPktLen_8723BS(padapter);

	/* YJ, TODO */
	rtw_ग_लिखो8(padapter, REG_SECONDARY_CCA_CTRL_8723B, 0x3);	/*  CCA */
	rtw_ग_लिखो8(padapter, 0x976, 0);	/*  hpfan_toकरो: 2nd CCA related */

	rtw_ग_लिखो16(padapter, REG_PKT_VO_VI_LIFE_TIME, 0x0400);	/*  unit: 256us. 256ms */
	rtw_ग_लिखो16(padapter, REG_PKT_BE_BK_LIFE_TIME, 0x0400);	/*  unit: 256us. 256ms */

	invalidate_cam_all(padapter);

	rtw_hal_set_chnl_bw(padapter, padapter->registrypriv.channel,
		CHANNEL_WIDTH_20, HAL_PRIME_CHNL_OFFSET_DONT_CARE, HAL_PRIME_CHNL_OFFSET_DONT_CARE);

	/*  Record original value क्रम ढाँचा. This is arough data, we can only use the data */
	/*  क्रम घातer adjust. The value can not be adjustde according to dअगरferent घातer!!! */
/* 	pHalData->OriginalCckTxPwrIdx = pHalData->CurrentCckTxPwrIdx; */
/* 	pHalData->OriginalOfdm24GTxPwrIdx = pHalData->CurrentOfdm24GTxPwrIdx; */

	rtl8723b_InitAntenna_Selection(padapter);

	/*  */
	/*  Disable BAR, suggested by Scott */
	/*  2010.04.09 add by hpfan */
	/*  */
	rtw_ग_लिखो32(padapter, REG_BAR_MODE_CTRL, 0x0201ffff);

	/*  HW SEQ CTRL */
	/*  set 0x0 to 0xFF by tynli. Default enable HW SEQ NUM. */
	rtw_ग_लिखो8(padapter, REG_HWSEQ_CTRL, 0xFF);


	/*  */
	/*  Configure SDIO TxRx Control to enable Rx DMA समयr masking. */
	/*  2010.02.24. */
	/*  */
	rtw_ग_लिखो32(padapter, SDIO_LOCAL_BASE | SDIO_REG_TX_CTRL, 0);

	_RfPowerSave(padapter);


	rtl8723b_InitHalDm(padapter);

	/* DbgPrपूर्णांक("pHalData->DefaultTxPwrDbm = %d\n", pHalData->DefaultTxPwrDbm); */

	/*  */
	/*  Update current Tx FIFO page status. */
	/*  */
	HalQueryTxBufferStatus8723BSdio(padapter);
	HalQueryTxOQTBufferStatus8723BSdio(padapter);
	pHalData->SdioTxOQTMaxFreeSpace = pHalData->SdioTxOQTFreeSpace;

	/*  Enable MACTXEN/MACRXEN block */
	u1bTmp = rtw_पढ़ो8(padapter, REG_CR);
	u1bTmp |= (MACTXEN | MACRXEN);
	rtw_ग_लिखो8(padapter, REG_CR, u1bTmp);

	rtw_hal_set_hwreg(padapter, HW_VAR_NAV_UPPER, (u8 *)&NavUpper);

	/* ack क्रम xmit mgmt frames. */
	rtw_ग_लिखो32(padapter, REG_FWHW_TXQ_CTRL, rtw_पढ़ो32(padapter, REG_FWHW_TXQ_CTRL) | BIT(12));

/* 	pHalData->PreRpwmVal = SdioLocalCmd52Read1Byte(padapter, SDIO_REG_HRPWM1) & 0x80; */

	अणु
		pwrctrlpriv->rf_pwrstate = rf_on;

		अगर (pwrctrlpriv->rf_pwrstate == rf_on) अणु
			काष्ठा pwrctrl_priv *pwrpriv;
			अचिन्हित दीर्घ start_समय;
			u8 restore_iqk_rst;
			u8 b2Ant;
			u8 h2cCmdBuf;

			pwrpriv = adapter_to_pwrctl(padapter);

			PHY_LCCalibrate_8723B(&pHalData->odmpriv);

			/* Inक्रमm WiFi FW that it is the beginning of IQK */
			h2cCmdBuf = 1;
			FillH2CCmd8723B(padapter, H2C_8723B_BT_WLAN_CALIBRATION, 1, &h2cCmdBuf);

			start_समय = jअगरfies;
			करो अणु
				अगर (rtw_पढ़ो8(padapter, 0x1e7) & 0x01)
					अवरोध;

				msleep(50);
			पूर्ण जबतक (jअगरfies_to_msecs(jअगरfies - start_समय) <= 400);

			hal_btcoex_IQKNotअगरy(padapter, true);

			restore_iqk_rst = pwrpriv->bips_processing;
			b2Ant = pHalData->EEPROMBluetoothAntNum == Ant_x2;
			PHY_IQCalibrate_8723B(padapter, false, restore_iqk_rst, b2Ant, pHalData->ant_path);
			pHalData->odmpriv.RFCalibrateInfo.bIQKInitialized = true;

			hal_btcoex_IQKNotअगरy(padapter, false);

			/* Inक्रमm WiFi FW that it is the finish of IQK */
			h2cCmdBuf = 0;
			FillH2CCmd8723B(padapter, H2C_8723B_BT_WLAN_CALIBRATION, 1, &h2cCmdBuf);

			ODM_TXPowerTrackingCheck(&pHalData->odmpriv);
		पूर्ण
	पूर्ण

	/*  Init BT hw config. */
	hal_btcoex_InitHwConfig(padapter, false);

	वापस _SUCCESS;
पूर्ण

/*  */
/*  Description: */
/* 	RTL8723e card disable घातer sequence v003 which suggested by Scott. */
/*  */
/*  First created by tynli. 2011.01.28. */
/*  */
अटल व्योम CardDisableRTL8723BSdio(काष्ठा adapter *padapter)
अणु
	u8 u1bTmp;
	u8 bMacPwrCtrlOn;
	u8 ret = _FAIL;

	/*  Run LPS WL RFOFF flow */
	ret = HalPwrSeqCmdParsing(padapter, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, rtl8723B_enter_lps_flow);

	/* 	==== Reset digital sequence   ====== */

	u1bTmp = rtw_पढ़ो8(padapter, REG_MCUFWDL);
	अगर ((u1bTmp & RAM_DL_SEL) && padapter->bFWReady) /* 8051 RAM code */
		rtl8723b_FirmwareSelfReset(padapter);

	/*  Reset MCU 0x2[10]= 0. Suggested by Filen. 2011.01.26. by tynli. */
	u1bTmp = rtw_पढ़ो8(padapter, REG_SYS_FUNC_EN + 1);
	u1bTmp &= ~BIT(2);	/*  0x2[10], FEN_CPUEN */
	rtw_ग_लिखो8(padapter, REG_SYS_FUNC_EN + 1, u1bTmp);

	/*  MCUFWDL 0x80[1:0]= 0 */
	/*  reset MCU पढ़ोy status */
	rtw_ग_लिखो8(padapter, REG_MCUFWDL, 0);

	/*  Reset MCU IO Wrapper, added by Roger, 2011.08.30 */
	u1bTmp = rtw_पढ़ो8(padapter, REG_RSV_CTRL + 1);
	u1bTmp &= ~BIT(0);
	rtw_ग_लिखो8(padapter, REG_RSV_CTRL + 1, u1bTmp);
	u1bTmp = rtw_पढ़ो8(padapter, REG_RSV_CTRL + 1);
	u1bTmp |= BIT(0);
	rtw_ग_लिखो8(padapter, REG_RSV_CTRL+1, u1bTmp);

	/* 	==== Reset digital sequence end ====== */

	bMacPwrCtrlOn = false;	/*  Disable CMD53 R/W */
	ret = false;
	rtw_hal_set_hwreg(padapter, HW_VAR_APFM_ON_MAC, &bMacPwrCtrlOn);
	ret = HalPwrSeqCmdParsing(padapter, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK, rtl8723B_card_disable_flow);
पूर्ण

अटल u32 rtl8723bs_hal_deinit(काष्ठा adapter *padapter)
अणु
	काष्ठा dvobj_priv *psdpriv = padapter->dvobj;
	काष्ठा debug_priv *pdbgpriv = &psdpriv->drv_dbg;

	अगर (padapter->hw_init_completed) अणु
		अगर (adapter_to_pwrctl(padapter)->bips_processing) अणु
			अगर (padapter->netअगर_up) अणु
				पूर्णांक cnt = 0;
				u8 val8 = 0;

				rtl8723b_set_FwPwrModeInIPS_cmd(padapter, 0x3);
				/* poll 0x1cc to make sure H2C command alपढ़ोy finished by FW; MAC_0x1cc = 0 means H2C करोne by FW. */
				करो अणु
					val8 = rtw_पढ़ो8(padapter, REG_HMETFR);
					cnt++;
					mdelay(10);
				पूर्ण जबतक (cnt < 100 && (val8 != 0));
				/* H2C करोne, enter 32k */
				अगर (val8 == 0) अणु
					/* ser rpwm to enter 32k */
					val8 = rtw_पढ़ो8(padapter, SDIO_LOCAL_BASE | SDIO_REG_HRPWM1);
					val8 += 0x80;
					val8 |= BIT(0);
					rtw_ग_लिखो8(padapter, SDIO_LOCAL_BASE | SDIO_REG_HRPWM1, val8);
					adapter_to_pwrctl(padapter)->tog = (val8 + 0x80) & 0x80;
					cnt = val8 = 0;
					करो अणु
						val8 = rtw_पढ़ो8(padapter, REG_CR);
						cnt++;
						mdelay(10);
					पूर्ण जबतक (cnt < 100 && (val8 != 0xEA));
				पूर्ण

				adapter_to_pwrctl(padapter)->pre_ips_type = 0;

			पूर्ण अन्यथा अणु
				pdbgpriv->dbg_carddisable_cnt++;
				CardDisableRTL8723BSdio(padapter);

				adapter_to_pwrctl(padapter)->pre_ips_type = 1;
			पूर्ण

		पूर्ण अन्यथा अणु
			pdbgpriv->dbg_carddisable_cnt++;
			CardDisableRTL8723BSdio(padapter);
		पूर्ण
	पूर्ण अन्यथा
		pdbgpriv->dbg_deinit_fail_cnt++;

	वापस _SUCCESS;
पूर्ण

अटल u32 rtl8723bs_inirp_init(काष्ठा adapter *padapter)
अणु
	वापस _SUCCESS;
पूर्ण

अटल u32 rtl8723bs_inirp_deinit(काष्ठा adapter *padapter)
अणु
	वापस _SUCCESS;
पूर्ण

अटल व्योम rtl8723bs_init_शेष_value(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData;


	pHalData = GET_HAL_DATA(padapter);

	rtl8723b_init_शेष_value(padapter);

	/*  पूर्णांकerface related variable */
	pHalData->SdioRxFIFOCnt = 0;
पूर्ण

अटल व्योम rtl8723bs_पूर्णांकerface_configure(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);
	काष्ठा registry_priv *pregistrypriv = &padapter->registrypriv;
	bool bWiFiConfig = pregistrypriv->wअगरi_spec;


	pdvobjpriv->RtOutPipe[0] = WLAN_TX_HIQ_DEVICE_ID;
	pdvobjpriv->RtOutPipe[1] = WLAN_TX_MIQ_DEVICE_ID;
	pdvobjpriv->RtOutPipe[2] = WLAN_TX_LOQ_DEVICE_ID;

	अगर (bWiFiConfig)
		pHalData->OutEpNumber = 2;
	अन्यथा
		pHalData->OutEpNumber = SDIO_MAX_TX_QUEUE;

	चयन (pHalData->OutEpNumber) अणु
	हाल 3:
		pHalData->OutEpQueueSel = TX_SELE_HQ | TX_SELE_LQ | TX_SELE_NQ;
		अवरोध;
	हाल 2:
		pHalData->OutEpQueueSel = TX_SELE_HQ | TX_SELE_NQ;
		अवरोध;
	हाल 1:
		pHalData->OutEpQueueSel = TX_SELE_HQ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	Hal_MappingOutPipe(padapter, pHalData->OutEpNumber);
पूर्ण

/*  */
/* 	Description: */
/* 		We should set Efuse cell selection to WiFi cell in शेष. */
/*  */
/* 	Assumption: */
/* 		PASSIVE_LEVEL */
/*  */
/* 	Added by Roger, 2010.11.23. */
/*  */
अटल व्योम _EfuseCellSel(काष्ठा adapter *padapter)
अणु
	u32 value32;

	value32 = rtw_पढ़ो32(padapter, EFUSE_TEST);
	value32 = (value32 & ~EFUSE_SEL_MASK) | EFUSE_SEL(EFUSE_WIFI_SEL_0);
	rtw_ग_लिखो32(padapter, EFUSE_TEST, value32);
पूर्ण

अटल व्योम _ReadRFType(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

#अगर DISABLE_BB_RF
	pHalData->rf_chip = RF_PSEUDO_11N;
#अन्यथा
	pHalData->rf_chip = RF_6052;
#पूर्ण_अगर
पूर्ण


अटल व्योम Hal_EfuseParseMACAddr_8723BS(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	u16 i;
	u8 sMacAddr[6] = अणु0x00, 0xE0, 0x4C, 0xb7, 0x23, 0x00पूर्ण;
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);

	अगर (AutoLoadFail) अणु
/* 		sMacAddr[5] = (u8)GetRanकरोmNumber(1, 254); */
		क्रम (i = 0; i < 6; i++)
			pEEPROM->mac_addr[i] = sMacAddr[i];
	पूर्ण अन्यथा अणु
		/* Read Permanent MAC address */
		स_नकल(pEEPROM->mac_addr, &hwinfo[EEPROM_MAC_ADDR_8723BS], ETH_ALEN);
	पूर्ण
पूर्ण

अटल व्योम Hal_EfuseParseBoardType_8723BS(
	काष्ठा adapter *padapter, u8 *hwinfo, bool AutoLoadFail
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	अगर (!AutoLoadFail) अणु
		pHalData->BoardType = (hwinfo[EEPROM_RF_BOARD_OPTION_8723B] & 0xE0) >> 5;
		अगर (pHalData->BoardType == 0xFF)
			pHalData->BoardType = (EEPROM_DEFAULT_BOARD_OPTION & 0xE0) >> 5;
	पूर्ण अन्यथा
		pHalData->BoardType = 0;
पूर्ण

अटल व्योम _ReadEfuseInfo8723BS(काष्ठा adapter *padapter)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);
	u8 *hwinfo = शून्य;

	/*  */
	/*  This part पढ़ो and parse the eeprom/efuse content */
	/*  */

	hwinfo = pEEPROM->efuse_eeprom_data;

	Hal_InitPGData(padapter, hwinfo);

	Hal_EfuseParseIDCode(padapter, hwinfo);
	Hal_EfuseParseEEPROMVer_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);

	Hal_EfuseParseMACAddr_8723BS(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);

	Hal_EfuseParseTxPowerInfo_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
	Hal_EfuseParseBoardType_8723BS(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);

	/*  */
	/*  Read Bluetooth co-exist and initialize */
	/*  */
	Hal_EfuseParsePackageType_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
	Hal_EfuseParseBTCoexistInfo_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
	Hal_EfuseParseChnlPlan_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
	Hal_EfuseParseXtal_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
	Hal_EfuseParseThermalMeter_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
	Hal_EfuseParseAntennaDiversity_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
	Hal_EfuseParseCustomerID_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);

	Hal_EfuseParseVoltage_8723B(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);

	Hal_ReadRFGainOffset(padapter, hwinfo, pEEPROM->bस्वतःload_fail_flag);
पूर्ण

अटल व्योम _ReadPROMContent(काष्ठा adapter *padapter)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(padapter);
	u8 	eeValue;

	eeValue = rtw_पढ़ो8(padapter, REG_9346CR);
	/*  To check प्रणाली boot selection. */
	pEEPROM->EepromOrEfuse = (eeValue & BOOT_FROM_EEPROM) ? true : false;
	pEEPROM->bस्वतःload_fail_flag = (eeValue & EEPROM_EN) ? false : true;

/* 	pHalData->EEType = IS_BOOT_FROM_EEPROM(Adapter) ? EEPROM_93C46 : EEPROM_BOOT_EFUSE; */

	_ReadEfuseInfo8723BS(padapter);
पूर्ण

अटल व्योम _InitOtherVariable(काष्ठा adapter *Adapter)
अणु
पूर्ण

/*  */
/* 	Description: */
/* 		Read HW adapter inक्रमmation by E-Fuse or EEPROM according CR9346 reported. */
/*  */
/* 	Assumption: */
/* 		PASSIVE_LEVEL (SDIO पूर्णांकerface) */
/*  */
/*  */
अटल s32 _ReadAdapterInfo8723BS(काष्ठा adapter *padapter)
अणु
	u8 val8;

	/*  beक्रमe access eFuse, make sure card enable has been called */
	अगर (!padapter->hw_init_completed)
		_InitPowerOn_8723BS(padapter);


	val8 = rtw_पढ़ो8(padapter, 0x4e);
	val8 |= BIT(6);
	rtw_ग_लिखो8(padapter, 0x4e, val8);

	_EfuseCellSel(padapter);
	_ReadRFType(padapter);
	_ReadPROMContent(padapter);
	_InitOtherVariable(padapter);

	अगर (!padapter->hw_init_completed) अणु
		rtw_ग_लिखो8(padapter, 0x67, 0x00); /*  क्रम BT, Switch Ant control to BT */
		CardDisableRTL8723BSdio(padapter);/* क्रम the घातer consumption issue,  wअगरi ko module is loaded during booting, but wअगरi GUI is off */
	पूर्ण

	वापस _SUCCESS;
पूर्ण

अटल व्योम ReadAdapterInfo8723BS(काष्ठा adapter *padapter)
अणु
	/*  Read EEPROM size beक्रमe call any EEPROM function */
	padapter->EepromAddressSize = GetEEPROMSize8723B(padapter);

	_ReadAdapterInfo8723BS(padapter);
पूर्ण

/*
 * If variable not handled here,
 * some variables will be processed in SetHwReg8723B()
 */
अटल व्योम SetHwReg8723BS(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	u8 val8;

	चयन (variable) अणु
	हाल HW_VAR_SET_RPWM:
		/*  rpwm value only use BIT0(घड़ी bit) , BIT6(Ack bit), and BIT7(Toggle bit) */
		/*  BIT0 value - 1: 32k, 0:40MHz. */
		/*  BIT6 value - 1: report cpwm value after success set, 0:करो not report. */
		/*  BIT7 value - Toggle bit change. */
		अणु
			val8 = *val;
			val8 &= 0xC1;
			rtw_ग_लिखो8(padapter, SDIO_LOCAL_BASE | SDIO_REG_HRPWM1, val8);
		पूर्ण
		अवरोध;
	हाल HW_VAR_SET_REQ_FW_PS:
		अणु
			u8 req_fw_ps = 0;
			req_fw_ps = rtw_पढ़ो8(padapter, 0x8f);
			req_fw_ps |= 0x10;
			rtw_ग_लिखो8(padapter, 0x8f, req_fw_ps);
		पूर्ण
		अवरोध;
	हाल HW_VAR_RXDMA_AGG_PG_TH:
		val8 = *val;
		अवरोध;

	हाल HW_VAR_DM_IN_LPS:
		rtl8723b_hal_dm_in_lps(padapter);
		अवरोध;
	शेष:
		SetHwReg8723B(padapter, variable, val);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * If variable not handled here,
 * some variables will be processed in GetHwReg8723B()
 */
अटल व्योम GetHwReg8723BS(काष्ठा adapter *padapter, u8 variable, u8 *val)
अणु
	चयन (variable) अणु
	हाल HW_VAR_CPWM:
		*val = rtw_पढ़ो8(padapter, SDIO_LOCAL_BASE | SDIO_REG_HCPWM1_8723B);
		अवरोध;

	हाल HW_VAR_FW_PS_STATE:
		अणु
			/* 3. पढ़ो dword 0x88               driver पढ़ो fw ps state */
			*((u16 *)val) = rtw_पढ़ो16(padapter, 0x88);
		पूर्ण
		अवरोध;
	शेष:
		GetHwReg8723B(padapter, variable, val);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम SetHwRegWithBuf8723B(काष्ठा adapter *padapter, u8 variable, u8 *pbuf, पूर्णांक len)
अणु
	चयन (variable) अणु
	हाल HW_VAR_C2H_HANDLE:
		C2HPacketHandler_8723B(padapter, pbuf, len);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*  */
/* 	Description: */
/* 		Query setting of specअगरied variable. */
/*  */
अटल u8 GetHalDefVar8723BSDIO(
	काष्ठा adapter *Adapter, क्रमागत hal_def_variable eVariable, व्योम *pValue
)
अणु
	u8 	bResult = _SUCCESS;

	चयन (eVariable) अणु
	हाल HAL_DEF_IS_SUPPORT_ANT_DIV:
		अवरोध;
	हाल HAL_DEF_CURRENT_ANTENNA:
		अवरोध;
	हाल HW_VAR_MAX_RX_AMPDU_FACTOR:
		/*  Stanley@BB.SD3 suggests 16K can get stable perक्रमmance */
		/*  coding by Lucas@20130730 */
		*(u32 *)pValue = IEEE80211_HT_MAX_AMPDU_16K;
		अवरोध;
	शेष:
		bResult = GetHalDefVar8723B(Adapter, eVariable, pValue);
		अवरोध;
	पूर्ण

	वापस bResult;
पूर्ण

/*  */
/* 	Description: */
/* 		Change शेष setting of specअगरied variable. */
/*  */
अटल u8 SetHalDefVar8723BSDIO(काष्ठा adapter *Adapter,
				क्रमागत hal_def_variable eVariable, व्योम *pValue)
अणु
	वापस SetHalDefVar8723B(Adapter, eVariable, pValue);
पूर्ण

व्योम rtl8723bs_set_hal_ops(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_ops *pHalFunc = &padapter->HalFunc;

	rtl8723b_set_hal_ops(pHalFunc);

	pHalFunc->hal_init = &rtl8723bs_hal_init;
	pHalFunc->hal_deinit = &rtl8723bs_hal_deinit;

	pHalFunc->inirp_init = &rtl8723bs_inirp_init;
	pHalFunc->inirp_deinit = &rtl8723bs_inirp_deinit;

	pHalFunc->init_xmit_priv = &rtl8723bs_init_xmit_priv;
	pHalFunc->मुक्त_xmit_priv = &rtl8723bs_मुक्त_xmit_priv;

	pHalFunc->init_recv_priv = &rtl8723bs_init_recv_priv;
	pHalFunc->मुक्त_recv_priv = &rtl8723bs_मुक्त_recv_priv;

	pHalFunc->init_शेष_value = &rtl8723bs_init_शेष_value;
	pHalFunc->पूर्णांकf_chip_configure = &rtl8723bs_पूर्णांकerface_configure;
	pHalFunc->पढ़ो_adapter_info = &ReadAdapterInfo8723BS;

	pHalFunc->enable_पूर्णांकerrupt = &EnableInterrupt8723BSdio;
	pHalFunc->disable_पूर्णांकerrupt = &DisableInterrupt8723BSdio;
	pHalFunc->check_ips_status = &CheckIPSStatus;
	pHalFunc->SetHwRegHandler = &SetHwReg8723BS;
	pHalFunc->GetHwRegHandler = &GetHwReg8723BS;
	pHalFunc->SetHwRegHandlerWithBuf = &SetHwRegWithBuf8723B;
	pHalFunc->GetHalDefVarHandler = &GetHalDefVar8723BSDIO;
	pHalFunc->SetHalDefVarHandler = &SetHalDefVar8723BSDIO;

	pHalFunc->hal_xmit = &rtl8723bs_hal_xmit;
	pHalFunc->mgnt_xmit = &rtl8723bs_mgnt_xmit;
	pHalFunc->hal_xmitframe_enqueue = &rtl8723bs_hal_xmitframe_enqueue;
पूर्ण
