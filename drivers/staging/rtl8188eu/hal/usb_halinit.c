<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _HCI_HAL_INIT_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <rtw_efuse.h>
#समावेश <fw.h>
#समावेश <rtl8188e_hal.h>
#समावेश <phy.h>

#घोषणा		HAL_BB_ENABLE		1

अटल व्योम _ConfigNormalChipOutEP_8188E(काष्ठा adapter *adapt, u8 NumOutPipe)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;

	चयन (NumOutPipe) अणु
	हाल	3:
		haldata->OutEpQueueSel = TX_SELE_HQ | TX_SELE_LQ | TX_SELE_NQ;
		haldata->OutEpNumber = 3;
		अवरोध;
	हाल	2:
		haldata->OutEpQueueSel = TX_SELE_HQ | TX_SELE_NQ;
		haldata->OutEpNumber = 2;
		अवरोध;
	हाल	1:
		haldata->OutEpQueueSel = TX_SELE_HQ;
		haldata->OutEpNumber = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	DBG_88E("%s OutEpQueueSel(0x%02x), OutEpNumber(%d)\n", __func__, haldata->OutEpQueueSel, haldata->OutEpNumber);
पूर्ण

अटल bool HalUsbSetQueuePipeMapping8188EUsb(काष्ठा adapter *adapt, u8 NumInPipe, u8 NumOutPipe)
अणु
	bool			result		= false;

	_ConfigNormalChipOutEP_8188E(adapt, NumOutPipe);

	/*  Normal chip with one IN and one OUT करोesn't have पूर्णांकerrupt IN EP. */
	अगर (adapt->HalData->OutEpNumber == 1) अणु
		अगर (NumInPipe != 1)
			वापस result;
	पूर्ण

	/*  All config other than above support one Bulk IN and one Interrupt IN. */

	result = hal_mapping_out_pipe(adapt, NumOutPipe);

	वापस result;
पूर्ण

व्योम rtw_hal_chip_configure(काष्ठा adapter *adapt)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;
	काष्ठा dvobj_priv	*pdvobjpriv = adapter_to_dvobj(adapt);

	अगर (pdvobjpriv->ishighspeed)
		haldata->UsbBulkOutSize = USB_HIGH_SPEED_BULK_SIZE;/* 512 bytes */
	अन्यथा
		haldata->UsbBulkOutSize = USB_FULL_SPEED_BULK_SIZE;/* 64 bytes */

	haldata->पूर्णांकerfaceIndex = pdvobjpriv->InterfaceNumber;

	haldata->UsbTxAggMode		= 1;
	haldata->UsbTxAggDescNum	= 0x6;	/*  only 4 bits */

	haldata->UsbRxAggMode		= USB_RX_AGG_DMA;/*  USB_RX_AGG_DMA; */
	haldata->UsbRxAggBlockCount	= 8; /* unit : 512b */
	haldata->UsbRxAggBlockTimeout	= 0x6;
	haldata->UsbRxAggPageCount	= 48; /* uपूर्णांक :128 b 0x0A;	10 = MAX_RX_DMA_BUFFER_SIZE/2/haldata->UsbBulkOutSize */
	haldata->UsbRxAggPageTimeout	= 0x4; /* 6, असलolute समय = 34ms/(2^6) */

	HalUsbSetQueuePipeMapping8188EUsb(adapt, pdvobjpriv->RtNumInPipes,
					  pdvobjpriv->RtNumOutPipes);
पूर्ण

u32 rtw_hal_घातer_on(काष्ठा adapter *adapt)
अणु
	u16 value16;
	/*  HW Power on sequence */
	अगर (adapt->HalData->bMacPwrCtrlOn)
		वापस _SUCCESS;

	अगर (!rtl88eu_pwrseqcmdparsing(adapt, PWR_CUT_ALL_MSK,
				      Rtl8188E_NIC_PWR_ON_FLOW)) अणु
		DBG_88E(KERN_ERR "%s: run power on flow fail\n", __func__);
		वापस _FAIL;
	पूर्ण

	/*  Enable MAC DMA/WMAC/SCHEDULE/SEC block */
	/*  Set CR bit10 to enable 32k calibration. Suggested by SD1 Gimmy. Added by tynli. 2011.08.31. */
	usb_ग_लिखो16(adapt, REG_CR, 0x00);  /* suggseted by zhouzhou, by page, 20111230 */

		/*  Enable MAC DMA/WMAC/SCHEDULE/SEC block */
	value16 = usb_पढ़ो16(adapt, REG_CR);
	value16 |= (HCI_TXDMA_EN | HCI_RXDMA_EN | TXDMA_EN | RXDMA_EN
				| PROTOCOL_EN | SCHEDULE_EN | ENSEC | CALTMR_EN);
	/*  क्रम SDIO - Set CR bit10 to enable 32k calibration. Suggested by SD1 Gimmy. Added by tynli. 2011.08.31. */

	usb_ग_लिखो16(adapt, REG_CR, value16);
	adapt->HalData->bMacPwrCtrlOn = true;

	वापस _SUCCESS;
पूर्ण

/*  Shall USB पूर्णांकerface init this? */
अटल व्योम _InitInterrupt(काष्ठा adapter *Adapter)
अणु
	u32 imr, imr_ex;
	u8  usb_opt;

	/* HISR ग_लिखो one to clear */
	usb_ग_लिखो32(Adapter, REG_HISR_88E, 0xFFFFFFFF);
	/*  HIMR - */
	imr = IMR_PSTIMEOUT_88E | IMR_TBDER_88E | IMR_CPWM_88E | IMR_CPWM2_88E;
	usb_ग_लिखो32(Adapter, REG_HIMR_88E, imr);
	Adapter->HalData->IntrMask[0] = imr;

	imr_ex = IMR_TXERR_88E | IMR_RXERR_88E | IMR_TXFOVW_88E | IMR_RXFOVW_88E;
	usb_ग_लिखो32(Adapter, REG_HIMRE_88E, imr_ex);
	Adapter->HalData->IntrMask[1] = imr_ex;

	/*  REG_USB_SPECIAL_OPTION - BIT(4) */
	/*  0; Use पूर्णांकerrupt endpoपूर्णांक to upload पूर्णांकerrupt pkt */
	/*  1; Use bulk endpoपूर्णांक to upload पूर्णांकerrupt pkt, */
	usb_opt = usb_पढ़ो8(Adapter, REG_USB_SPECIAL_OPTION);

	अगर (!adapter_to_dvobj(Adapter)->ishighspeed)
		usb_opt = usb_opt & (~INT_BULK_SEL);
	अन्यथा
		usb_opt = usb_opt | (INT_BULK_SEL);

	usb_ग_लिखो8(Adapter, REG_USB_SPECIAL_OPTION, usb_opt);
पूर्ण

अटल व्योम _InitQueueReservedPage(काष्ठा adapter *Adapter)
अणु
	काष्ठा registry_priv	*pregistrypriv = &Adapter->registrypriv;
	u32 numHQ	= 0;
	u32 numLQ	= 0;
	u32 numNQ	= 0;
	u32 numPubQ;
	u32 value32;
	u8 value8;
	bool bWiFiConfig = pregistrypriv->wअगरi_spec;

	अगर (bWiFiConfig) अणु
		अगर (Adapter->HalData->OutEpQueueSel & TX_SELE_HQ)
			numHQ =  0x29;

		अगर (Adapter->HalData->OutEpQueueSel & TX_SELE_LQ)
			numLQ = 0x1C;

		/*  NOTE: This step shall be proceed beक्रमe writing REG_RQPN. */
		अगर (Adapter->HalData->OutEpQueueSel & TX_SELE_NQ)
			numNQ = 0x1C;
		value8 = (u8)_NPQ(numNQ);
		usb_ग_लिखो8(Adapter, REG_RQPN_NPQ, value8);

		numPubQ = 0xA8 - numHQ - numLQ - numNQ;

		/*  TX DMA */
		value32 = _HPQ(numHQ) | _LPQ(numLQ) | _PUBQ(numPubQ) | LD_RQPN;
		usb_ग_लिखो32(Adapter, REG_RQPN, value32);
	पूर्ण अन्यथा अणु
		usb_ग_लिखो16(Adapter, REG_RQPN_NPQ, 0x0000);/* Just follow MP Team,??? Georgia 03/28 */
		usb_ग_लिखो16(Adapter, REG_RQPN_NPQ, 0x0d);
		usb_ग_लिखो32(Adapter, REG_RQPN, 0x808E000d);/* reserve 7 page क्रम LPS */
	पूर्ण
पूर्ण

अटल व्योम _InitTxBufferBoundary(काष्ठा adapter *Adapter, u8 txpktbuf_bndy)
अणु
	usb_ग_लिखो8(Adapter, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	usb_ग_लिखो8(Adapter, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);
	usb_ग_लिखो8(Adapter, REG_TXPKTBUF_WMAC_LBK_BF_HD, txpktbuf_bndy);
	usb_ग_लिखो8(Adapter, REG_TRXFF_BNDY, txpktbuf_bndy);
	usb_ग_लिखो8(Adapter, REG_TDECTRL + 1, txpktbuf_bndy);
पूर्ण

अटल व्योम _InitPageBoundary(काष्ठा adapter *Adapter)
अणु
	/*  RX Page Boundary */
	/*  */
	u16 rxff_bndy = MAX_RX_DMA_BUFFER_SIZE_88E - 1;

	usb_ग_लिखो16(Adapter, (REG_TRXFF_BNDY + 2), rxff_bndy);
पूर्ण

अटल व्योम _InitNormalChipRegPriority(काष्ठा adapter *Adapter, u16 beQ,
				       u16 bkQ, u16 viQ, u16 voQ, u16 mgtQ,
				       u16 hiQ)
अणु
	u16 value16	= (usb_पढ़ो16(Adapter, REG_TRXDMA_CTRL) & 0x7);

	value16 |= _TXDMA_BEQ_MAP(beQ)	| _TXDMA_BKQ_MAP(bkQ) |
		   _TXDMA_VIQ_MAP(viQ)	| _TXDMA_VOQ_MAP(voQ) |
		   _TXDMA_MGQ_MAP(mgtQ) | _TXDMA_HIQ_MAP(hiQ);

	usb_ग_लिखो16(Adapter, REG_TRXDMA_CTRL, value16);
पूर्ण

अटल व्योम _InitNormalChipOneOutEpPriority(काष्ठा adapter *Adapter)
अणु
	u16 value = 0;

	चयन (Adapter->HalData->OutEpQueueSel) अणु
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
		अवरोध;
	पूर्ण
	_InitNormalChipRegPriority(Adapter, value, value, value, value,
				   value, value);
पूर्ण

अटल व्योम _InitNormalChipTwoOutEpPriority(काष्ठा adapter *Adapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &Adapter->registrypriv;
	u16 beQ, bkQ, viQ, voQ, mgtQ, hiQ;
	u16 valueHi = 0;
	u16 valueLow = 0;

	चयन (Adapter->HalData->OutEpQueueSel) अणु
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
		अवरोध;
	पूर्ण

	अगर (!pregistrypriv->wअगरi_spec) अणु
		beQ	= valueLow;
		bkQ	= valueLow;
		viQ	= valueHi;
		voQ	= valueHi;
		mgtQ	= valueHi;
		hiQ	= valueHi;
	पूर्ण अन्यथा अणु/* क्रम WMM ,CONFIG_OUT_EP_WIFI_MODE */
		beQ	= valueLow;
		bkQ	= valueHi;
		viQ	= valueHi;
		voQ	= valueLow;
		mgtQ	= valueHi;
		hiQ	= valueHi;
	पूर्ण
	_InitNormalChipRegPriority(Adapter, beQ, bkQ, viQ, voQ, mgtQ, hiQ);
पूर्ण

अटल व्योम _InitNormalChipThreeOutEpPriority(काष्ठा adapter *Adapter)
अणु
	काष्ठा registry_priv *pregistrypriv = &Adapter->registrypriv;
	u16 beQ, bkQ, viQ, voQ, mgtQ, hiQ;

	अगर (!pregistrypriv->wअगरi_spec) अणु/*  typical setting */
		beQ	= QUEUE_LOW;
		bkQ	= QUEUE_LOW;
		viQ	= QUEUE_NORMAL;
		voQ	= QUEUE_HIGH;
		mgtQ	= QUEUE_HIGH;
		hiQ	= QUEUE_HIGH;
	पूर्ण अन्यथा अणु/*  क्रम WMM */
		beQ	= QUEUE_LOW;
		bkQ	= QUEUE_NORMAL;
		viQ	= QUEUE_NORMAL;
		voQ	= QUEUE_HIGH;
		mgtQ	= QUEUE_HIGH;
		hiQ	= QUEUE_HIGH;
	पूर्ण
	_InitNormalChipRegPriority(Adapter, beQ, bkQ, viQ, voQ, mgtQ, hiQ);
पूर्ण

अटल व्योम _InitQueuePriority(काष्ठा adapter *Adapter)
अणु
	चयन (Adapter->HalData->OutEpNumber) अणु
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
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _InitNetworkType(काष्ठा adapter *Adapter)
अणु
	u32 value32;

	value32 = usb_पढ़ो32(Adapter, REG_CR);
	/*  TODO: use the other function to set network type */
	value32 = (value32 & ~MASK_NETTYPE) | _NETTYPE(NT_LINK_AP);

	usb_ग_लिखो32(Adapter, REG_CR, value32);
पूर्ण

अटल व्योम _InitTransferPageSize(काष्ठा adapter *Adapter)
अणु
	/*  Tx page size is always 128. */

	u8 value8;

	value8 = _PSRX(PBP_128) | _PSTX(PBP_128);
	usb_ग_लिखो8(Adapter, REG_PBP, value8);
पूर्ण

अटल व्योम _InitDriverInfoSize(काष्ठा adapter *Adapter, u8 drvInfoSize)
अणु
	usb_ग_लिखो8(Adapter, REG_RX_DRVINFO_SZ, drvInfoSize);
पूर्ण

अटल व्योम _InitWMACSetting(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;

	haldata->ReceiveConfig = RCR_AAP | RCR_APM | RCR_AM | RCR_AB |
				  RCR_CBSSID_DATA | RCR_CBSSID_BCN |
				  RCR_APP_ICV | RCR_AMF | RCR_HTC_LOC_CTRL |
				  RCR_APP_MIC | RCR_APP_PHYSTS;

	/*  some REG_RCR will be modअगरied later by phy_ConfigMACWithHeaderFile() */
	usb_ग_लिखो32(Adapter, REG_RCR, haldata->ReceiveConfig);

	/*  Accept all multicast address */
	usb_ग_लिखो32(Adapter, REG_MAR, 0xFFFFFFFF);
	usb_ग_लिखो32(Adapter, REG_MAR + 4, 0xFFFFFFFF);
पूर्ण

अटल व्योम _InitAdaptiveCtrl(काष्ठा adapter *Adapter)
अणु
	u16 value16;
	u32 value32;

	/*  Response Rate Set */
	value32 = usb_पढ़ो32(Adapter, REG_RRSR);
	value32 &= ~RATE_BITMAP_ALL;
	value32 |= RATE_RRSR_CCK_ONLY_1M;
	usb_ग_लिखो32(Adapter, REG_RRSR, value32);

	/*  CF-END Threshold */

	/*  SIFS (used in NAV) */
	value16 = _SPEC_SIFS_CCK(0x10) | _SPEC_SIFS_OFDM(0x10);
	usb_ग_लिखो16(Adapter, REG_SPEC_SIFS, value16);

	/*  Retry Limit */
	value16 = _LRL(0x30) | _SRL(0x30);
	usb_ग_लिखो16(Adapter, REG_RL, value16);
पूर्ण

अटल व्योम _InitEDCA(काष्ठा adapter *Adapter)
अणु
	/*  Set Spec SIFS (used in NAV) */
	usb_ग_लिखो16(Adapter, REG_SPEC_SIFS, 0x100a);
	usb_ग_लिखो16(Adapter, REG_MAC_SPEC_SIFS, 0x100a);

	/*  Set SIFS क्रम CCK */
	usb_ग_लिखो16(Adapter, REG_SIFS_CTX, 0x100a);

	/*  Set SIFS क्रम OFDM */
	usb_ग_लिखो16(Adapter, REG_SIFS_TRX, 0x100a);

	/*  TXOP */
	usb_ग_लिखो32(Adapter, REG_EDCA_BE_PARAM, 0x005EA42B);
	usb_ग_लिखो32(Adapter, REG_EDCA_BK_PARAM, 0x0000A44F);
	usb_ग_लिखो32(Adapter, REG_EDCA_VI_PARAM, 0x005EA324);
	usb_ग_लिखो32(Adapter, REG_EDCA_VO_PARAM, 0x002FA226);
पूर्ण

अटल व्योम _InitRDGSetting(काष्ठा adapter *Adapter)
अणु
	usb_ग_लिखो8(Adapter, REG_RD_CTRL, 0xFF);
	usb_ग_लिखो16(Adapter, REG_RD_NAV_NXT, 0x200);
	usb_ग_लिखो8(Adapter, REG_RD_RESP_PKT_TH, 0x05);
पूर्ण

अटल व्योम _InitRxSetting(काष्ठा adapter *Adapter)
अणु
	usb_ग_लिखो32(Adapter, REG_MACID, 0x87654321);
	usb_ग_लिखो32(Adapter, 0x0700, 0x87654321);
पूर्ण

अटल व्योम _InitRetryFunction(काष्ठा adapter *Adapter)
अणु
	u8 value8;

	value8 = usb_पढ़ो8(Adapter, REG_FWHW_TXQ_CTRL);
	value8 |= EN_AMPDU_RTY_NEW;
	usb_ग_लिखो8(Adapter, REG_FWHW_TXQ_CTRL, value8);

	/*  Set ACK समयout */
	usb_ग_लिखो8(Adapter, REG_ACKTO, 0x40);
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	usb_AggSettingTxUpdate()
 *
 * Overview:	Separate TX/RX parameters update independent क्रम TP detection and
 *			dynamic TX/RX aggreagtion parameters update.
 *
 * Input:			काष्ठा adapter *
 *
 * Output/Return:	NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	12/10/2010	MHC		Separate to smaller function.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम usb_AggSettingTxUpdate(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;
	u32 value32;

	अगर (Adapter->registrypriv.wअगरi_spec)
		haldata->UsbTxAggMode = false;

	अगर (haldata->UsbTxAggMode) अणु
		value32 = usb_पढ़ो32(Adapter, REG_TDECTRL);
		value32 = value32 & ~(BLK_DESC_NUM_MASK << BLK_DESC_NUM_SHIFT);
		value32 |= ((haldata->UsbTxAggDescNum & BLK_DESC_NUM_MASK) << BLK_DESC_NUM_SHIFT);

		usb_ग_लिखो32(Adapter, REG_TDECTRL, value32);
	पूर्ण
पूर्ण	/*  usb_AggSettingTxUpdate */

/*-----------------------------------------------------------------------------
 * Function:	usb_AggSettingRxUpdate()
 *
 * Overview:	Separate TX/RX parameters update independent क्रम TP detection and
 *			dynamic TX/RX aggreagtion parameters update.
 *
 * Input:			काष्ठा adapter *
 *
 * Output/Return:	NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	12/10/2010	MHC		Separate to smaller function.
 *
 *---------------------------------------------------------------------------
 */
अटल व्योम usb_AggSettingRxUpdate(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;
	u8 valueDMA;
	u8 valueUSB;

	valueDMA = usb_पढ़ो8(Adapter, REG_TRXDMA_CTRL);
	valueUSB = usb_पढ़ो8(Adapter, REG_USB_SPECIAL_OPTION);

	चयन (haldata->UsbRxAggMode) अणु
	हाल USB_RX_AGG_DMA:
		valueDMA |= RXDMA_AGG_EN;
		valueUSB &= ~USB_AGG_EN;
		अवरोध;
	हाल USB_RX_AGG_USB:
		valueDMA &= ~RXDMA_AGG_EN;
		valueUSB |= USB_AGG_EN;
		अवरोध;
	हाल USB_RX_AGG_MIX:
		valueDMA |= RXDMA_AGG_EN;
		valueUSB |= USB_AGG_EN;
		अवरोध;
	हाल USB_RX_AGG_DISABLE:
	शेष:
		valueDMA &= ~RXDMA_AGG_EN;
		valueUSB &= ~USB_AGG_EN;
		अवरोध;
	पूर्ण

	usb_ग_लिखो8(Adapter, REG_TRXDMA_CTRL, valueDMA);
	usb_ग_लिखो8(Adapter, REG_USB_SPECIAL_OPTION, valueUSB);

	चयन (haldata->UsbRxAggMode) अणु
	हाल USB_RX_AGG_DMA:
		usb_ग_लिखो8(Adapter, REG_RXDMA_AGG_PG_TH, haldata->UsbRxAggPageCount);
		usb_ग_लिखो8(Adapter, REG_RXDMA_AGG_PG_TH + 1, haldata->UsbRxAggPageTimeout);
		अवरोध;
	हाल USB_RX_AGG_USB:
		usb_ग_लिखो8(Adapter, REG_USB_AGG_TH, haldata->UsbRxAggBlockCount);
		usb_ग_लिखो8(Adapter, REG_USB_AGG_TO, haldata->UsbRxAggBlockTimeout);
		अवरोध;
	हाल USB_RX_AGG_MIX:
		usb_ग_लिखो8(Adapter, REG_RXDMA_AGG_PG_TH, haldata->UsbRxAggPageCount);
		usb_ग_लिखो8(Adapter, REG_RXDMA_AGG_PG_TH + 1, (haldata->UsbRxAggPageTimeout & 0x1F));/* 0x280[12:8] */
		usb_ग_लिखो8(Adapter, REG_USB_AGG_TH, haldata->UsbRxAggBlockCount);
		usb_ग_लिखो8(Adapter, REG_USB_AGG_TO, haldata->UsbRxAggBlockTimeout);
		अवरोध;
	हाल USB_RX_AGG_DISABLE:
	शेष:
		/*  TODO: */
		अवरोध;
	पूर्ण

	चयन (PBP_128) अणु
	हाल PBP_128:
		haldata->HwRxPageSize = 128;
		अवरोध;
	हाल PBP_64:
		haldata->HwRxPageSize = 64;
		अवरोध;
	हाल PBP_256:
		haldata->HwRxPageSize = 256;
		अवरोध;
	हाल PBP_512:
		haldata->HwRxPageSize = 512;
		अवरोध;
	हाल PBP_1024:
		haldata->HwRxPageSize = 1024;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण	/*  usb_AggSettingRxUpdate */

अटल व्योम InitUsbAggregationSetting(काष्ठा adapter *Adapter)
अणु
	/*  Tx aggregation setting */
	usb_AggSettingTxUpdate(Adapter);

	/*  Rx aggregation setting */
	usb_AggSettingRxUpdate(Adapter);
पूर्ण

अटल व्योम _InitBeaconParameters(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;

	usb_ग_लिखो16(Adapter, REG_BCN_CTRL, 0x1010);

	/*  TODO: Remove these magic number */
	usb_ग_लिखो16(Adapter, REG_TBTT_PROHIBIT, 0x6404);/*  ms */
	usb_ग_लिखो8(Adapter, REG_DRVERLYINT, DRIVER_EARLY_INT_TIME);/*  5ms */
	usb_ग_लिखो8(Adapter, REG_BCNDMATIM, BCN_DMA_ATIME_INT_TIME); /*  2ms */

	/*  Suggested by designer timchen. Change beacon AIFS to the largest number */
	/*  beacause test chip करोes not contension beक्रमe sending beacon. by tynli. 2009.11.03 */
	usb_ग_लिखो16(Adapter, REG_BCNTCFG, 0x660F);

	haldata->RegBcnCtrlVal = usb_पढ़ो8(Adapter, REG_BCN_CTRL);
	haldata->RegTxPause = usb_पढ़ो8(Adapter, REG_TXPAUSE);
	haldata->RegFwHwTxQCtrl = usb_पढ़ो8(Adapter, REG_FWHW_TXQ_CTRL + 2);
	haldata->RegReg542 = usb_पढ़ो8(Adapter, REG_TBTT_PROHIBIT + 2);
	haldata->RegCR_1 = usb_पढ़ो8(Adapter, REG_CR + 1);
पूर्ण

अटल व्योम _BeaconFunctionEnable(काष्ठा adapter *Adapter)
अणु
	usb_ग_लिखो8(Adapter, REG_BCN_CTRL, (BIT(4) | BIT(3) | BIT(1)));

	usb_ग_लिखो8(Adapter, REG_RD_CTRL + 1, 0x6F);
पूर्ण

/*  Set CCK and OFDM Block "ON" */
अटल व्योम _BBTurnOnBlock(काष्ठा adapter *Adapter)
अणु
	phy_set_bb_reg(Adapter, rFPGA0_RFMOD, bCCKEn, 0x1);
	phy_set_bb_reg(Adapter, rFPGA0_RFMOD, bOFDMEn, 0x1);
पूर्ण

अटल व्योम _InitAntenna_Selection(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;

	अगर (haldata->AntDivCfg == 0)
		वापस;
	DBG_88E("==>  %s ....\n", __func__);

	usb_ग_लिखो32(Adapter, REG_LEDCFG0, usb_पढ़ो32(Adapter, REG_LEDCFG0) | BIT(23));
	phy_set_bb_reg(Adapter, rFPGA0_XAB_RFParameter, BIT(13), 0x01);

	अगर (phy_query_bb_reg(Adapter, rFPGA0_XA_RFInterfaceOE, 0x300) == Antenna_A)
		haldata->CurAntenna = Antenna_A;
	अन्यथा
		haldata->CurAntenna = Antenna_B;
	DBG_88E("%s,Cur_ant:(%x)%s\n", __func__, haldata->CurAntenna, (haldata->CurAntenna == Antenna_A) ? "Antenna_A" : "Antenna_B");
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	HwSuspendModeEnable92Cu()
 *
 * Overview:	HW suspend mode चयन.
 *
 * Input:		NONE
 *
 * Output:	NONE
 *
 * Return:	NONE
 *
 * Revised History:
 *	When		Who		Remark
 *	08/23/2010	MHC		HW suspend mode चयन test..
 *---------------------------------------------------------------------------
 */
क्रमागत rt_rf_घातer_state RfOnOffDetect(काष्ठा adapter *adapt)
अणु
	u8 val8;
	क्रमागत rt_rf_घातer_state rfघातerstate = rf_off;

	अगर (adapt->pwrctrlpriv.bHWPowerकरोwn) अणु
		val8 = usb_पढ़ो8(adapt, REG_HSISR);
		DBG_88E("pwrdown, 0x5c(BIT(7))=%02x\n", val8);
		rfघातerstate = (val8 & BIT(7)) ? rf_off : rf_on;
	पूर्ण अन्यथा अणु /*  rf on/off */
		usb_ग_लिखो8(adapt, REG_MAC_PINMUX_CFG, usb_पढ़ो8(adapt, REG_MAC_PINMUX_CFG) & ~(BIT(3)));
		val8 = usb_पढ़ो8(adapt, REG_GPIO_IO_SEL);
		DBG_88E("GPIO_IN=%02x\n", val8);
		rfघातerstate = (val8 & BIT(3)) ? rf_on : rf_off;
	पूर्ण
	वापस rfघातerstate;
पूर्ण	/*  HalDetectPwrDownMode */

u32 rtl8188eu_hal_init(काष्ठा adapter *Adapter)
अणु
	u8 value8 = 0;
	u16  value16;
	u8 txpktbuf_bndy;
	u32 status = _SUCCESS;
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;
	काष्ठा pwrctrl_priv		*pwrctrlpriv = &Adapter->pwrctrlpriv;
	काष्ठा registry_priv	*pregistrypriv = &Adapter->registrypriv;
	अचिन्हित दीर्घ init_start_समय = jअगरfies;

	#घोषणा HAL_INIT_PROखाता_TAG(stage) करो अणुपूर्ण जबतक (0)

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_BEGIN);

	अगर (Adapter->pwrctrlpriv.bkeepfwalive) अणु
		अगर (haldata->odmpriv.RFCalibrateInfo.bIQKInitialized) अणु
			rtl88eu_phy_iq_calibrate(Adapter, true);
		पूर्ण अन्यथा अणु
			rtl88eu_phy_iq_calibrate(Adapter, false);
			haldata->odmpriv.RFCalibrateInfo.bIQKInitialized = true;
		पूर्ण

		ODM_TXPowerTrackingCheck(&haldata->odmpriv);
		rtl88eu_phy_lc_calibrate(Adapter);

		जाओ निकास;
	पूर्ण

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_INIT_PW_ON);
	status = rtw_hal_घातer_on(Adapter);
	अगर (status == _FAIL) अणु
		RT_TRACE(_module_hci_hal_init_c_, _drv_err_, ("Failed to init power on!\n"));
		जाओ निकास;
	पूर्ण

	/*  Save target channel */
	haldata->CurrentChannel = 6;/* शेष set to 6 */

	अगर (pwrctrlpriv->reg_rfoff)
		pwrctrlpriv->rf_pwrstate = rf_off;

	/*  2010/08/09 MH We need to check अगर we need to turnon or off RF after detecting */
	/*  HW GPIO pin. Beक्रमe PHY_RFConfig8192C. */
	/*  2010/08/26 MH If Efuse करोes not support sective suspend then disable the function. */

	अगर (!pregistrypriv->wअगरi_spec) अणु
		txpktbuf_bndy = TX_PAGE_BOUNDARY_88E;
	पूर्ण अन्यथा अणु
		/*  क्रम WMM */
		txpktbuf_bndy = WMM_NORMAL_TX_PAGE_BOUNDARY_88E;
	पूर्ण

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_MISC01);
	_InitQueueReservedPage(Adapter);
	_InitQueuePriority(Adapter);
	_InitPageBoundary(Adapter);
	_InitTransferPageSize(Adapter);

	_InitTxBufferBoundary(Adapter, 0);

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_DOWNLOAD_FW);
	अगर (Adapter->registrypriv.mp_mode == 1) अणु
		_InitRxSetting(Adapter);
		Adapter->bFWReady = false;
	पूर्ण अन्यथा अणु
		status = rtl88eu_करोwnload_fw(Adapter);

		अगर (status) अणु
			DBG_88E("%s: Download Firmware failed!!\n", __func__);
			Adapter->bFWReady = false;
			वापस status;
		पूर्ण
		RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("Initializeadapt8192CSdio(): Download Firmware Success!!\n"));
		Adapter->bFWReady = true;
	पूर्ण
	rtl8188e_InitializeFirmwareVars(Adapter);

	rtl88eu_phy_mac_config(Adapter);

	rtl88eu_phy_bb_config(Adapter);

	rtl88eu_phy_rf_config(Adapter);

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_EFUSE_PATCH);
	status = rtl8188e_iol_efuse_patch(Adapter);
	अगर (status == _FAIL) अणु
		DBG_88E("%s  rtl8188e_iol_efuse_patch failed\n", __func__);
		जाओ निकास;
	पूर्ण

	_InitTxBufferBoundary(Adapter, txpktbuf_bndy);

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_INIT_LLTT);
	status =  InitLLTTable(Adapter, txpktbuf_bndy);
	अगर (status == _FAIL) अणु
		RT_TRACE(_module_hci_hal_init_c_, _drv_err_, ("Failed to init LLT table\n"));
		जाओ निकास;
	पूर्ण

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_MISC02);
	/*  Get Rx PHY status in order to report RSSI and others. */
	_InitDriverInfoSize(Adapter, DRVINFO_SZ);

	_InitInterrupt(Adapter);
	rtw_hal_set_hwreg(Adapter, HW_VAR_MAC_ADDR,
			  Adapter->eeprompriv.mac_addr);
	_InitNetworkType(Adapter);/* set msr */
	_InitWMACSetting(Adapter);
	_InitAdaptiveCtrl(Adapter);
	_InitEDCA(Adapter);
	_InitRetryFunction(Adapter);
	InitUsbAggregationSetting(Adapter);
	_InitBeaconParameters(Adapter);
	/*  Init CR MACTXEN, MACRXEN after setting RxFF boundary REG_TRXFF_BNDY to patch */
	/*  Hw bug which Hw initials RxFF boundary size to a value which is larger than the real Rx buffer size in 88E. */
	/*  Enable MACTXEN/MACRXEN block */
	value16 = usb_पढ़ो16(Adapter, REG_CR);
	value16 |= (MACTXEN | MACRXEN);
	usb_ग_लिखो8(Adapter, REG_CR, value16);

	अगर (haldata->bRDGEnable)
		_InitRDGSetting(Adapter);

	/* Enable TX Report */
	/* Enable Tx Report Timer */
	value8 = usb_पढ़ो8(Adapter, REG_TX_RPT_CTRL);
	usb_ग_लिखो8(Adapter,  REG_TX_RPT_CTRL, (value8 | BIT(1) | BIT(0)));
	/* Set MAX RPT MACID */
	usb_ग_लिखो8(Adapter,  REG_TX_RPT_CTRL + 1, 2);/* FOR sta mode ,0: bc/mc ,1:AP */
	/* Tx RPT Timer. Unit: 32us */
	usb_ग_लिखो16(Adapter, REG_TX_RPT_TIME, 0xCdf0);

	usb_ग_लिखो8(Adapter, REG_EARLY_MODE_CONTROL, 0);

	usb_ग_लिखो16(Adapter, REG_PKT_VO_VI_LIFE_TIME, 0x0400);	/*  unit: 256us. 256ms */
	usb_ग_लिखो16(Adapter, REG_PKT_BE_BK_LIFE_TIME, 0x0400);	/*  unit: 256us. 256ms */

	/* Keep RfRegChnlVal क्रम later use. */
	haldata->RfRegChnlVal[0] = rtw_hal_पढ़ो_rfreg(Adapter, (क्रमागत rf_radio_path)0, RF_CHNLBW, bRFRegOffsetMask);
	haldata->RfRegChnlVal[1] = rtw_hal_पढ़ो_rfreg(Adapter, (क्रमागत rf_radio_path)1, RF_CHNLBW, bRFRegOffsetMask);

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_TURN_ON_BLOCK);
	_BBTurnOnBlock(Adapter);

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_INIT_SECURITY);
	invalidate_cam_all(Adapter);

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_MISC11);
	/*  2010/12/17 MH We need to set TX घातer according to EFUSE content at first. */
	phy_set_tx_घातer_level(Adapter, haldata->CurrentChannel);

/*  Move by Neo क्रम USB SS to below setp */
/* _RfPowerSave(Adapter); */

	_InitAntenna_Selection(Adapter);

	/*  */
	/*  Disable BAR, suggested by Scott */
	/*  2010.04.09 add by hpfan */
	/*  */
	usb_ग_लिखो32(Adapter, REG_BAR_MODE_CTRL, 0x0201ffff);

	/*  HW SEQ CTRL */
	/* set 0x0 to 0xFF by tynli. Default enable HW SEQ NUM. */
	usb_ग_लिखो8(Adapter, REG_HWSEQ_CTRL, 0xFF);

	अगर (pregistrypriv->wअगरi_spec)
		usb_ग_लिखो16(Adapter, REG_FAST_EDCA_CTRL, 0);

	/* Nav limit , suggest by scott */
	usb_ग_लिखो8(Adapter, 0x652, 0x0);

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_INIT_HAL_DM);
	rtl8188e_InitHalDm(Adapter);

	/*  2010/08/11 MH Merge from 8192SE क्रम Minicard init. We need to confirm current radio status */
	/*  and then decide to enable RF or not.!!!??? For Selective suspend mode. We may not */
	/*  call initकाष्ठा adapter. May cause some problem?? */
	/*  Fix the bug that Hw/Sw radio off beक्रमe S3/S4, the RF off action will not be executed */
	/*  in MgntActSet_RF_State() after wake up, because the value of haldata->eRFPowerState */
	/*  is the same as eRfOff, we should change it to eRfOn after we config RF parameters. */
	/*  Added by tynli. 2010.03.30. */
	pwrctrlpriv->rf_pwrstate = rf_on;

	/*  enable Tx report. */
	usb_ग_लिखो8(Adapter,  REG_FWHW_TXQ_CTRL + 1, 0x0F);

	/*  Suggested by SD1 pisa. Added by tynli. 2011.10.21. */
	usb_ग_लिखो8(Adapter, REG_EARLY_MODE_CONTROL + 3, 0x01);/* Pretx_en, क्रम WEP/TKIP SEC */

	/* tynli_test_tx_report. */
	usb_ग_लिखो16(Adapter, REG_TX_RPT_TIME, 0x3DF0);

	/* enable tx DMA to drop the redundate data of packet */
	usb_ग_लिखो16(Adapter, REG_TXDMA_OFFSET_CHK, (usb_पढ़ो16(Adapter, REG_TXDMA_OFFSET_CHK) | DROP_DATA_EN));

	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_IQK);
	/*  2010/08/26 MH Merge from 8192CE. */
	अगर (pwrctrlpriv->rf_pwrstate == rf_on) अणु
		अगर (haldata->odmpriv.RFCalibrateInfo.bIQKInitialized) अणु
			rtl88eu_phy_iq_calibrate(Adapter, true);
		पूर्ण अन्यथा अणु
			rtl88eu_phy_iq_calibrate(Adapter, false);
			haldata->odmpriv.RFCalibrateInfo.bIQKInitialized = true;
		पूर्ण

		HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_PW_TRACK);

		ODM_TXPowerTrackingCheck(&haldata->odmpriv);

		HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_LCK);
		rtl88eu_phy_lc_calibrate(Adapter);
	पूर्ण

/* HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_INIT_PABIAS); */
/*	_InitPABias(Adapter); */
	usb_ग_लिखो8(Adapter, REG_USB_HRPWM, 0);

	/* ack क्रम xmit mgmt frames. */
	usb_ग_लिखो32(Adapter, REG_FWHW_TXQ_CTRL, usb_पढ़ो32(Adapter, REG_FWHW_TXQ_CTRL) | BIT(12));

निकास:
	HAL_INIT_PROखाता_TAG(HAL_INIT_STAGES_END);

	DBG_88E("%s in %dms\n", __func__,
		jअगरfies_to_msecs(jअगरfies - init_start_समय));

	वापस status;
पूर्ण

अटल व्योम CardDisableRTL8188EU(काष्ठा adapter *Adapter)
अणु
	u8 val8;

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("%s\n", __func__));

	/* Stop Tx Report Timer. 0x4EC[Bit1]=b'0 */
	val8 = usb_पढ़ो8(Adapter, REG_TX_RPT_CTRL);
	usb_ग_लिखो8(Adapter, REG_TX_RPT_CTRL, val8 & (~BIT(1)));

	/*  stop rx */
	usb_ग_लिखो8(Adapter, REG_CR, 0x0);

	/*  Run LPS WL RFOFF flow */
	rtl88eu_pwrseqcmdparsing(Adapter, PWR_CUT_ALL_MSK,
				 Rtl8188E_NIC_LPS_ENTER_FLOW);

	/*  2. 0x1F[7:0] = 0		turn off RF */

	val8 = usb_पढ़ो8(Adapter, REG_MCUFWDL);
	अगर ((val8 & RAM_DL_SEL) && Adapter->bFWReady) अणु /* 8051 RAM code */
		/*  Reset MCU 0x2[10]=0. */
		val8 = usb_पढ़ो8(Adapter, REG_SYS_FUNC_EN + 1);
		val8 &= ~BIT(2);	/*  0x2[10], FEN_CPUEN */
		usb_ग_लिखो8(Adapter, REG_SYS_FUNC_EN + 1, val8);
	पूर्ण

	/*  reset MCU पढ़ोy status */
	usb_ग_लिखो8(Adapter, REG_MCUFWDL, 0);

	/* YJ,add,111212 */
	/* Disable 32k */
	val8 = usb_पढ़ो8(Adapter, REG_32K_CTRL);
	usb_ग_लिखो8(Adapter, REG_32K_CTRL, val8 & (~BIT(0)));

	/*  Card disable घातer action flow */
	rtl88eu_pwrseqcmdparsing(Adapter, PWR_CUT_ALL_MSK,
				 Rtl8188E_NIC_DISABLE_FLOW);

	/*  Reset MCU IO Wrapper */
	val8 = usb_पढ़ो8(Adapter, REG_RSV_CTRL + 1);
	usb_ग_लिखो8(Adapter, REG_RSV_CTRL + 1, (val8 & (~BIT(3))));
	val8 = usb_पढ़ो8(Adapter, REG_RSV_CTRL + 1);
	usb_ग_लिखो8(Adapter, REG_RSV_CTRL + 1, val8 | BIT(3));

	/* YJ,test add, 111207. For Power Consumption. */
	val8 = usb_पढ़ो8(Adapter, GPIO_IN);
	usb_ग_लिखो8(Adapter, GPIO_OUT, val8);
	usb_ग_लिखो8(Adapter, GPIO_IO_SEL, 0xFF);/* Reg0x46 */

	val8 = usb_पढ़ो8(Adapter, REG_GPIO_IO_SEL);
	usb_ग_लिखो8(Adapter, REG_GPIO_IO_SEL, (val8 << 4));
	val8 = usb_पढ़ो8(Adapter, REG_GPIO_IO_SEL + 1);
	usb_ग_लिखो8(Adapter, REG_GPIO_IO_SEL + 1, val8 | 0x0F);/* Reg0x43 */
	usb_ग_लिखो32(Adapter, REG_BB_PAD_CTRL, 0x00080808);/* set LNA ,TRSW,EX_PA Pin to output mode */
	Adapter->HalData->bMacPwrCtrlOn = false;
	Adapter->bFWReady = false;
पूर्ण

अटल व्योम rtl8192cu_hw_घातer_करोwn(काष्ठा adapter *adapt)
अणु
	/*  2010/-8/09 MH For घातer करोwn module, we need to enable रेजिस्टर block contrl reg at 0x1c. */
	/*  Then enable घातer करोwn control bit of रेजिस्टर 0x04 BIT4 and BIT15 as 1. */

	/*  Enable रेजिस्टर area 0x0-0xc. */
	usb_ग_लिखो8(adapt, REG_RSV_CTRL, 0x0);
	usb_ग_लिखो16(adapt, REG_APS_FSMCO, 0x8812);
पूर्ण

u32 rtl8188eu_hal_deinit(काष्ठा adapter *Adapter)
अणु
	DBG_88E("==> %s\n", __func__);

	usb_ग_लिखो32(Adapter, REG_HIMR_88E, IMR_DISABLED_88E);
	usb_ग_लिखो32(Adapter, REG_HIMRE_88E, IMR_DISABLED_88E);

	DBG_88E("bkeepfwalive(%x)\n", Adapter->pwrctrlpriv.bkeepfwalive);
	अगर (Adapter->pwrctrlpriv.bkeepfwalive) अणु
		अगर ((Adapter->pwrctrlpriv.bHWPwrPindetect) && (Adapter->pwrctrlpriv.bHWPowerकरोwn))
			rtl8192cu_hw_घातer_करोwn(Adapter);
	पूर्ण अन्यथा अणु
		अगर (Adapter->hw_init_completed) अणु
			CardDisableRTL8188EU(Adapter);

			अगर ((Adapter->pwrctrlpriv.bHWPwrPindetect) && (Adapter->pwrctrlpriv.bHWPowerकरोwn))
				rtl8192cu_hw_घातer_करोwn(Adapter);
		पूर्ण
	पूर्ण
	वापस _SUCCESS;
पूर्ण

u32 rtw_hal_inirp_init(काष्ठा adapter *Adapter)
अणु
	u8 i;
	काष्ठा recv_buf *precvbuf;
	uपूर्णांक	status;
	काष्ठा recv_priv *precvpriv = &Adapter->recvpriv;

	status = _SUCCESS;

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_,
		 ("===> usb_inirp_init\n"));

	/* issue Rx irp to receive data */
	precvbuf = precvpriv->precv_buf;
	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		अगर (!usb_पढ़ो_port(Adapter, RECV_BULK_IN_ADDR, precvbuf)) अणु
			RT_TRACE(_module_hci_hal_init_c_, _drv_err_, ("usb_rx_init: usb_read_port error\n"));
			status = _FAIL;
			जाओ निकास;
		पूर्ण

		precvbuf++;
	पूर्ण

निकास:

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("<=== usb_inirp_init\n"));

	वापस status;
पूर्ण

/*  */
/*  */
/*	EEPROM/EFUSE Content Parsing */
/*  */
/*  */
अटल व्योम Hal_EfuseParsePIDVID_8188EU(काष्ठा adapter *adapt, u8 *hwinfo, bool AutoLoadFail)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;

	अगर (!AutoLoadFail) अणु
		/*  VID, PID */
		haldata->EEPROMVID = EF2BYTE(*(__le16 *)&hwinfo[EEPROM_VID_88EU]);
		haldata->EEPROMPID = EF2BYTE(*(__le16 *)&hwinfo[EEPROM_PID_88EU]);

		/*  Customer ID, 0x00 and 0xff are reserved क्रम Realtek. */
		haldata->EEPROMCustomerID = *(u8 *)&hwinfo[EEPROM_CUSTOMERID_88E];
		haldata->EEPROMSubCustomerID = EEPROM_Default_SubCustomerID;
	पूर्ण अन्यथा अणु
		haldata->EEPROMVID			= EEPROM_Default_VID;
		haldata->EEPROMPID			= EEPROM_Default_PID;

		/*  Customer ID, 0x00 and 0xff are reserved क्रम Realtek. */
		haldata->EEPROMCustomerID		= EEPROM_Default_CustomerID;
		haldata->EEPROMSubCustomerID	= EEPROM_Default_SubCustomerID;
	पूर्ण

	DBG_88E("VID = 0x%04X, PID = 0x%04X\n", haldata->EEPROMVID, haldata->EEPROMPID);
	DBG_88E("Customer ID: 0x%02X, SubCustomer ID: 0x%02X\n", haldata->EEPROMCustomerID, haldata->EEPROMSubCustomerID);
पूर्ण

अटल व्योम Hal_EfuseParseMACAddr_8188EU(काष्ठा adapter *adapt, u8 *hwinfo, bool AutoLoadFail)
अणु
	u16 i;
	u8 sMacAddr[6] = अणु0x00, 0xE0, 0x4C, 0x81, 0x88, 0x02पूर्ण;
	काष्ठा eeprom_priv *eeprom = GET_EEPROM_EFUSE_PRIV(adapt);

	अगर (AutoLoadFail) अणु
		क्रम (i = 0; i < 6; i++)
			eeprom->mac_addr[i] = sMacAddr[i];
	पूर्ण अन्यथा अणु
		/* Read Permanent MAC address */
		स_नकल(eeprom->mac_addr, &hwinfo[EEPROM_MAC_ADDR_88EU], ETH_ALEN);
	पूर्ण
	RT_TRACE(_module_hci_hal_init_c_, _drv_notice_,
		 ("%s: Permanent Address = %pM\n", __func__, eeprom->mac_addr));
पूर्ण

अटल व्योम पढ़ोAdapterInfo_8188EU(काष्ठा adapter *adapt)
अणु
	काष्ठा eeprom_priv *eeprom = GET_EEPROM_EFUSE_PRIV(adapt);

	/* parse the eeprom/efuse content */
	Hal_EfuseParseIDCode88E(adapt, eeprom->efuse_eeprom_data);
	Hal_EfuseParsePIDVID_8188EU(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_EfuseParseMACAddr_8188EU(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);

	Hal_ReadPowerSavingMode88E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_ReadTxPowerInfo88E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_EfuseParseEEPROMVer88E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	rtl8188e_EfuseParseChnlPlan(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_EfuseParseXtal_8188E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_EfuseParseCustomerID88E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_ReadAntennaDiversity88E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_EfuseParseBoardType88E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
	Hal_ReadThermalMeter_88E(adapt, eeprom->efuse_eeprom_data, eeprom->bस्वतःload_fail_flag);
पूर्ण

अटल व्योम _ReadPROMContent(काष्ठा adapter *Adapter)
अणु
	काष्ठा eeprom_priv *eeprom = GET_EEPROM_EFUSE_PRIV(Adapter);
	u8 eeValue;

	/* check प्रणाली boot selection */
	eeValue = usb_पढ़ो8(Adapter, REG_9346CR);
	eeprom->EepromOrEfuse		= (eeValue & BOOT_FROM_EEPROM) ? true : false;
	eeprom->bस्वतःload_fail_flag	= (eeValue & EEPROM_EN) ? false : true;

	DBG_88E("Boot from %s, Autoload %s !\n", (eeprom->EepromOrEfuse ? "EEPROM" : "EFUSE"),
		(eeprom->bस्वतःload_fail_flag ? "Fail" : "OK"));

	Hal_InitPGData88E(Adapter);
	पढ़ोAdapterInfo_8188EU(Adapter);
पूर्ण

व्योम rtw_hal_पढ़ो_chip_info(काष्ठा adapter *Adapter)
अणु
	अचिन्हित दीर्घ start = jअगरfies;

	MSG_88E("====> %s\n", __func__);

	_ReadPROMContent(Adapter);

	MSG_88E("<==== %s in %d ms\n", __func__,
		jअगरfies_to_msecs(jअगरfies - start));
पूर्ण

#घोषणा GPIO_DEBUG_PORT_NUM 0
अटल व्योम rtl8192cu_trigger_gpio_0(काष्ठा adapter *adapt)
अणु
पूर्ण

अटल व्योम ResumeTxBeacon(काष्ठा adapter *adapt)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;

	/*  2010.03.01. Marked by tynli. No need to call workitem beacause we record the value */
	/*  which should be पढ़ो from रेजिस्टर to a global variable. */

	usb_ग_लिखो8(adapt, REG_FWHW_TXQ_CTRL + 2, (haldata->RegFwHwTxQCtrl) | BIT(6));
	haldata->RegFwHwTxQCtrl |= BIT(6);
	usb_ग_लिखो8(adapt, REG_TBTT_PROHIBIT + 1, 0xff);
	haldata->RegReg542 |= BIT(0);
	usb_ग_लिखो8(adapt, REG_TBTT_PROHIBIT + 2, haldata->RegReg542);
पूर्ण

अटल व्योम StopTxBeacon(काष्ठा adapter *adapt)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;

	/*  2010.03.01. Marked by tynli. No need to call workitem beacause we record the value */
	/*  which should be पढ़ो from रेजिस्टर to a global variable. */

	usb_ग_लिखो8(adapt, REG_FWHW_TXQ_CTRL + 2, (haldata->RegFwHwTxQCtrl) & (~BIT(6)));
	haldata->RegFwHwTxQCtrl &= (~BIT(6));
	usb_ग_लिखो8(adapt, REG_TBTT_PROHIBIT + 1, 0x64);
	haldata->RegReg542 &= ~(BIT(0));
	usb_ग_लिखो8(adapt, REG_TBTT_PROHIBIT + 2, haldata->RegReg542);

	 /* toकरो: CheckFwRsvdPageContent(Adapter);  2010.06.23. Added by tynli. */
पूर्ण

अटल व्योम hw_var_set_opmode(काष्ठा adapter *Adapter, u8 variable, u8 *val)
अणु
	u8 val8;
	u8 mode = *((u8 *)val);

	/*  disable Port0 TSF update */
	usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) | BIT(4));

	/*  set net_type */
	val8 = usb_पढ़ो8(Adapter, MSR) & 0x0c;
	val8 |= mode;
	usb_ग_लिखो8(Adapter, MSR, val8);

	DBG_88E("%s()-%d mode = %d\n", __func__, __LINE__, mode);

	अगर ((mode == _HW_STATE_STATION_) || (mode == _HW_STATE_NOLINK_)) अणु
		StopTxBeacon(Adapter);

		usb_ग_लिखो8(Adapter, REG_BCN_CTRL, 0x19);/* disable atim wnd */
	पूर्ण अन्यथा अगर (mode == _HW_STATE_ADHOC_) अणु
		ResumeTxBeacon(Adapter);
		usb_ग_लिखो8(Adapter, REG_BCN_CTRL, 0x1a);
	पूर्ण अन्यथा अगर (mode == _HW_STATE_AP_) अणु
		ResumeTxBeacon(Adapter);

		usb_ग_लिखो8(Adapter, REG_BCN_CTRL, 0x12);

		/* Set RCR */
		usb_ग_लिखो32(Adapter, REG_RCR, 0x7000208e);/* CBSSID_DATA must set to 0,reject ICV_ERR packet */
		/* enable to rx data frame */
		usb_ग_लिखो16(Adapter, REG_RXFLTMAP2, 0xFFFF);
		/* enable to rx ps-poll */
		usb_ग_लिखो16(Adapter, REG_RXFLTMAP1, 0x0400);

		/* Beacon Control related रेजिस्टर क्रम first समय */
		usb_ग_लिखो8(Adapter, REG_BCNDMATIM, 0x02); /*  2ms */

		usb_ग_लिखो8(Adapter, REG_ATIMWND, 0x0a); /*  10ms */
		usb_ग_लिखो16(Adapter, REG_BCNTCFG, 0x00);
		usb_ग_लिखो16(Adapter, REG_TBTT_PROHIBIT, 0xff04);
		usb_ग_लिखो16(Adapter, REG_TSFTR_SYN_OFFSET, 0x7fff);/*  +32767 (~32ms) */

		/* reset TSF */
		usb_ग_लिखो8(Adapter, REG_DUAL_TSF_RST, BIT(0));

		/* BIT3 - If set 0, hw will clr bcnq when tx becon ok/fail or port 0 */
		usb_ग_लिखो8(Adapter, REG_MBID_NUM, usb_पढ़ो8(Adapter, REG_MBID_NUM) | BIT(3) | BIT(4));

		/* enable BCN0 Function क्रम अगर1 */
		/* करोn't enable update TSF0 क्रम अगर1 (due to TSF update when beacon/probe rsp are received) */
		usb_ग_लिखो8(Adapter, REG_BCN_CTRL, (DIS_TSF_UDT0_NORMAL_CHIP | EN_BCN_FUNCTION | BIT(1)));

		/* dis BCN1 ATIM  WND अगर अगर2 is station */
		usb_ग_लिखो8(Adapter, REG_BCN_CTRL_1, usb_पढ़ो8(Adapter, REG_BCN_CTRL_1) | BIT(0));
	पूर्ण
पूर्ण

अटल व्योम hw_var_set_macaddr(काष्ठा adapter *Adapter, u8 variable, u8 *val)
अणु
	u8 idx = 0;
	u32 reg_macid;

	reg_macid = REG_MACID;

	क्रम (idx = 0; idx < 6; idx++)
		usb_ग_लिखो8(Adapter, (reg_macid + idx), val[idx]);
पूर्ण

अटल व्योम hw_var_set_bssid(काष्ठा adapter *Adapter, u8 variable, u8 *val)
अणु
	u8 idx = 0;
	u32 reg_bssid;

	reg_bssid = REG_BSSID;

	क्रम (idx = 0; idx < 6; idx++)
		usb_ग_लिखो8(Adapter, (reg_bssid + idx), val[idx]);
पूर्ण

अटल व्योम hw_var_set_bcn_func(काष्ठा adapter *Adapter, u8 variable, u8 *val)
अणु
	u32 bcn_ctrl_reg;

	bcn_ctrl_reg = REG_BCN_CTRL;

	अगर (*((u8 *)val))
		usb_ग_लिखो8(Adapter, bcn_ctrl_reg, (EN_BCN_FUNCTION | EN_TXBCN_RPT));
	अन्यथा
		usb_ग_लिखो8(Adapter, bcn_ctrl_reg, usb_पढ़ो8(Adapter, bcn_ctrl_reg) & (~(EN_BCN_FUNCTION | EN_TXBCN_RPT)));
पूर्ण

व्योम rtw_hal_set_hwreg(काष्ठा adapter *Adapter, u8 variable, u8 *val)
अणु
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;
	काष्ठा dm_priv	*pdmpriv = &haldata->dmpriv;
	काष्ठा odm_dm_काष्ठा *podmpriv = &haldata->odmpriv;

	चयन (variable) अणु
	हाल HW_VAR_MEDIA_STATUS:
		अणु
			u8 val8;

			val8 = usb_पढ़ो8(Adapter, MSR) & 0x0c;
			val8 |= *((u8 *)val);
			usb_ग_लिखो8(Adapter, MSR, val8);
		पूर्ण
		अवरोध;
	हाल HW_VAR_MEDIA_STATUS1:
		अणु
			u8 val8;

			val8 = usb_पढ़ो8(Adapter, MSR) & 0x03;
			val8 |= *((u8 *)val) << 2;
			usb_ग_लिखो8(Adapter, MSR, val8);
		पूर्ण
		अवरोध;
	हाल HW_VAR_SET_OPMODE:
		hw_var_set_opmode(Adapter, variable, val);
		अवरोध;
	हाल HW_VAR_MAC_ADDR:
		hw_var_set_macaddr(Adapter, variable, val);
		अवरोध;
	हाल HW_VAR_BSSID:
		hw_var_set_bssid(Adapter, variable, val);
		अवरोध;
	हाल HW_VAR_BASIC_RATE:
		अणु
			u16 BrateCfg = 0;
			u8 RateIndex = 0;

			/*  2007.01.16, by Emily */
			/*  Select RRSR (in Legacy-OFDM and CCK) */
			/*  For 8190, we select only 24M, 12M, 6M, 11M, 5.5M, 2M, and 1M from the Basic rate. */
			/*  We करो not use other rates. */
			hal_set_brate_cfg(val, &BrateCfg);
			DBG_88E("HW_VAR_BASIC_RATE: BrateCfg(%#x)\n", BrateCfg);

			/* 2011.03.30 add by Luke Lee */
			/* CCK 2M ACK should be disabled क्रम some BCM and Atheros AP IOT */
			/* because CCK 2M has poor TXEVM */
			/* CCK 5.5M & 11M ACK should be enabled क्रम better perक्रमmance */

			BrateCfg = (BrateCfg | 0xd) & 0x15d;
			haldata->BasicRateSet = BrateCfg;

			BrateCfg |= 0x01; /*  शेष enable 1M ACK rate */
			/*  Set RRSR rate table. */
			usb_ग_लिखो8(Adapter, REG_RRSR, BrateCfg & 0xff);
			usb_ग_लिखो8(Adapter, REG_RRSR + 1, (BrateCfg >> 8) & 0xff);
			usb_ग_लिखो8(Adapter, REG_RRSR + 2, usb_पढ़ो8(Adapter, REG_RRSR + 2) & 0xf0);

			/*  Set RTS initial rate */
			जबतक (BrateCfg > 0x1) अणु
				BrateCfg >>= 1;
				RateIndex++;
			पूर्ण
			/*  Ziv - Check */
			usb_ग_लिखो8(Adapter, REG_INIRTS_RATE_SEL, RateIndex);
		पूर्ण
		अवरोध;
	हाल HW_VAR_TXPAUSE:
		usb_ग_लिखो8(Adapter, REG_TXPAUSE, *((u8 *)val));
		अवरोध;
	हाल HW_VAR_BCN_FUNC:
		hw_var_set_bcn_func(Adapter, variable, val);
		अवरोध;
	हाल HW_VAR_CORRECT_TSF:
		अणु
			u64	tsf;
			काष्ठा mlme_ext_priv	*pmlmeext = &Adapter->mlmeextpriv;
			काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

			tsf = pmlmeext->TSFValue - करो_भाग(pmlmeext->TSFValue, (pmlmeinfo->bcn_पूर्णांकerval * 1024)) - 1024; /* us */

			अगर (((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE))
				StopTxBeacon(Adapter);

			/* disable related TSF function */
			usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) & (~BIT(3)));

			usb_ग_लिखो32(Adapter, REG_TSFTR, tsf);
			usb_ग_लिखो32(Adapter, REG_TSFTR + 4, tsf >> 32);

			/* enable related TSF function */
			usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) | BIT(3));

			अगर (((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE))
				ResumeTxBeacon(Adapter);
		पूर्ण
		अवरोध;
	हाल HW_VAR_CHECK_BSSID:
		अगर (*((u8 *)val)) अणु
			usb_ग_लिखो32(Adapter, REG_RCR, usb_पढ़ो32(Adapter, REG_RCR) | RCR_CBSSID_DATA | RCR_CBSSID_BCN);
		पूर्ण अन्यथा अणु
			u32 val32;

			val32 = usb_पढ़ो32(Adapter, REG_RCR);

			val32 &= ~(RCR_CBSSID_DATA | RCR_CBSSID_BCN);

			usb_ग_लिखो32(Adapter, REG_RCR, val32);
		पूर्ण
		अवरोध;
	हाल HW_VAR_MLME_DISCONNECT:
		/* Set RCR to not to receive data frame when NO LINK state */
		/* reject all data frames */
		usb_ग_लिखो16(Adapter, REG_RXFLTMAP2, 0x00);

		/* reset TSF */
		usb_ग_लिखो8(Adapter, REG_DUAL_TSF_RST, (BIT(0) | BIT(1)));

		/* disable update TSF */
		usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) | BIT(4));
		अवरोध;
	हाल HW_VAR_MLME_SITESURVEY:
		अगर (*((u8 *)val)) अणु /* under sitesurvey */
			/* config RCR to receive dअगरferent BSSID & not to receive data frame */
			u32 v = usb_पढ़ो32(Adapter, REG_RCR);

			v &= ~(RCR_CBSSID_BCN);
			usb_ग_लिखो32(Adapter, REG_RCR, v);
			/* reject all data frame */
			usb_ग_लिखो16(Adapter, REG_RXFLTMAP2, 0x00);

			/* disable update TSF */
			usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) | BIT(4));
		पूर्ण अन्यथा अणु /* sitesurvey करोne */
			काष्ठा mlme_ext_priv	*pmlmeext = &Adapter->mlmeextpriv;
			काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

			अगर ((is_client_associated_to_ap(Adapter)) ||
			    ((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE)) अणु
				/* enable to rx data frame */
				usb_ग_लिखो16(Adapter, REG_RXFLTMAP2, 0xFFFF);

				/* enable update TSF */
				usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) & (~BIT(4)));
			पूर्ण अन्यथा अगर ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE) अणु
				usb_ग_लिखो16(Adapter, REG_RXFLTMAP2, 0xFFFF);
				/* enable update TSF */
				usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) & (~BIT(4)));
			पूर्ण

			usb_ग_लिखो32(Adapter, REG_RCR, usb_पढ़ो32(Adapter, REG_RCR) | RCR_CBSSID_BCN);
		पूर्ण
		अवरोध;
	हाल HW_VAR_MLME_JOIN:
		अणु
			u8 RetryLimit = 0x30;
			u8 type = *((u8 *)val);
			काष्ठा mlme_priv	*pmlmepriv = &Adapter->mlmepriv;

			अगर (type == 0) अणु /*  prepare to join */
				/* enable to rx data frame.Accept all data frame */
				usb_ग_लिखो16(Adapter, REG_RXFLTMAP2, 0xFFFF);

				usb_ग_लिखो32(Adapter, REG_RCR, usb_पढ़ो32(Adapter, REG_RCR) | RCR_CBSSID_DATA | RCR_CBSSID_BCN);

				अगर (check_fwstate(pmlmepriv, WIFI_STATION_STATE))
					RetryLimit = (haldata->CustomerID == RT_CID_CCX) ? 7 : 48;
				अन्यथा /*  Ad-hoc Mode */
					RetryLimit = 0x7;
			पूर्ण अन्यथा अगर (type == 1) अणु
				/* joinbss_event call back when join res < 0 */
				usb_ग_लिखो16(Adapter, REG_RXFLTMAP2, 0x00);
			पूर्ण अन्यथा अगर (type == 2) अणु
				/* sta add event call back */
				/* enable update TSF */
				usb_ग_लिखो8(Adapter, REG_BCN_CTRL, usb_पढ़ो8(Adapter, REG_BCN_CTRL) & (~BIT(4)));

				अगर (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE | WIFI_ADHOC_MASTER_STATE))
					RetryLimit = 0x7;
			पूर्ण
			usb_ग_लिखो16(Adapter, REG_RL, RetryLimit << RETRY_LIMIT_SHORT_SHIFT | RetryLimit << RETRY_LIMIT_LONG_SHIFT);
		पूर्ण
		अवरोध;
	हाल HW_VAR_BEACON_INTERVAL:
		usb_ग_लिखो16(Adapter, REG_BCN_INTERVAL, *((u16 *)val));
		अवरोध;
	हाल HW_VAR_SLOT_TIME:
		अणु
			u8 u1bAIFS, aSअगरsTime;
			काष्ठा mlme_ext_priv	*pmlmeext = &Adapter->mlmeextpriv;
			काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;

			usb_ग_लिखो8(Adapter, REG_SLOT, val[0]);

			अगर (pmlmeinfo->WMM_enable == 0) अणु
				अगर (pmlmeext->cur_wireless_mode == WIRELESS_11B)
					aSअगरsTime = 10;
				अन्यथा
					aSअगरsTime = 16;

				u1bAIFS = aSअगरsTime + (2 * pmlmeinfo->slotTime);

				/*  <Roger_EXP> Temporary हटाओd, 2008.06.20. */
				usb_ग_लिखो8(Adapter, REG_EDCA_VO_PARAM, u1bAIFS);
				usb_ग_लिखो8(Adapter, REG_EDCA_VI_PARAM, u1bAIFS);
				usb_ग_लिखो8(Adapter, REG_EDCA_BE_PARAM, u1bAIFS);
				usb_ग_लिखो8(Adapter, REG_EDCA_BK_PARAM, u1bAIFS);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_RESP_SIFS:
		/* RESP_SIFS क्रम CCK */
		usb_ग_लिखो8(Adapter, REG_R2T_SIFS, val[0]); /*  SIFS_T2T_CCK (0x08) */
		usb_ग_लिखो8(Adapter, REG_R2T_SIFS + 1, val[1]); /* SIFS_R2T_CCK(0x08) */
		/* RESP_SIFS क्रम OFDM */
		usb_ग_लिखो8(Adapter, REG_T2T_SIFS, val[2]); /* SIFS_T2T_OFDM (0x0a) */
		usb_ग_लिखो8(Adapter, REG_T2T_SIFS + 1, val[3]); /* SIFS_R2T_OFDM(0x0a) */
		अवरोध;
	हाल HW_VAR_ACK_PREAMBLE:
		अणु
			u8 regTmp;
			u8 bShortPreamble = *((bool *)val);
			/*  Joseph marked out क्रम Netgear 3500 TKIP channel 7 issue.(Temporarily) */
			regTmp = (haldata->nCur40MhzPrimeSC) << 5;
			अगर (bShortPreamble)
				regTmp |= 0x80;

			usb_ग_लिखो8(Adapter, REG_RRSR + 2, regTmp);
		पूर्ण
		अवरोध;
	हाल HW_VAR_SEC_CFG:
		usb_ग_लिखो8(Adapter, REG_SECCFG, *((u8 *)val));
		अवरोध;
	हाल HW_VAR_DM_FUNC_OP:
		अगर (val[0])
			podmpriv->BK_SupportAbility = podmpriv->SupportAbility;
		अन्यथा
			podmpriv->SupportAbility = podmpriv->BK_SupportAbility;
		अवरोध;
	हाल HW_VAR_DM_FUNC_SET:
		अगर (*((u32 *)val) == DYNAMIC_ALL_FUNC_ENABLE) अणु
			pdmpriv->DMFlag = pdmpriv->InitDMFlag;
			podmpriv->SupportAbility =	pdmpriv->InitODMFlag;
		पूर्ण अन्यथा अणु
			podmpriv->SupportAbility |= *((u32 *)val);
		पूर्ण
		अवरोध;
	हाल HW_VAR_DM_FUNC_CLR:
		podmpriv->SupportAbility &= *((u32 *)val);
		अवरोध;
	हाल HW_VAR_CAM_EMPTY_ENTRY:
		अणु
			u8 ucIndex = *((u8 *)val);
			u8 i;
			u32 ulCommand = 0;
			u32 ulContent = 0;
			u32 ulEncAlgo = CAM_AES;

			क्रम (i = 0; i < CAM_CONTENT_COUNT; i++) अणु
				/*  filled id in CAM config 2 byte */
				अगर (i == 0)
					ulContent |= (ucIndex & 0x03) | ((u16)(ulEncAlgo) << 2);
				अन्यथा
					ulContent = 0;
				/*  polling bit, and No Write enable, and address */
				ulCommand = CAM_CONTENT_COUNT * ucIndex + i;
				ulCommand = ulCommand | CAM_POLLINIG |
					    CAM_WRITE;
				/*  ग_लिखो content 0 is equall to mark invalid */
				usb_ग_लिखो32(Adapter, WCAMI, ulContent);  /* delay_ms(40); */
				usb_ग_लिखो32(Adapter, RWCAM, ulCommand);  /* delay_ms(40); */
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_CAM_INVALID_ALL:
		usb_ग_लिखो32(Adapter, RWCAM, BIT(31) | BIT(30));
		अवरोध;
	हाल HW_VAR_CAM_WRITE:
		अणु
			u32 cmd;
			u32 *cam_val = (u32 *)val;

			usb_ग_लिखो32(Adapter, WCAMI, cam_val[0]);

			cmd = CAM_POLLINIG | CAM_WRITE | cam_val[1];
			usb_ग_लिखो32(Adapter, RWCAM, cmd);
		पूर्ण
		अवरोध;
	हाल HW_VAR_AC_PARAM_VO:
		usb_ग_लिखो32(Adapter, REG_EDCA_VO_PARAM, ((u32 *)(val))[0]);
		अवरोध;
	हाल HW_VAR_AC_PARAM_VI:
		usb_ग_लिखो32(Adapter, REG_EDCA_VI_PARAM, ((u32 *)(val))[0]);
		अवरोध;
	हाल HW_VAR_AC_PARAM_BE:
		haldata->AcParam_BE = ((u32 *)(val))[0];
		usb_ग_लिखो32(Adapter, REG_EDCA_BE_PARAM, ((u32 *)(val))[0]);
		अवरोध;
	हाल HW_VAR_AC_PARAM_BK:
		usb_ग_लिखो32(Adapter, REG_EDCA_BK_PARAM, ((u32 *)(val))[0]);
		अवरोध;
	हाल HW_VAR_ACM_CTRL:
		अणु
			u8 acm_ctrl = *((u8 *)val);
			u8 AcmCtrl = usb_पढ़ो8(Adapter, REG_ACMHWCTRL);

			अगर (acm_ctrl > 1)
				AcmCtrl = AcmCtrl | 0x1;

			अगर (acm_ctrl & BIT(3))
				AcmCtrl |= AcmHw_VoqEn;
			अन्यथा
				AcmCtrl &= (~AcmHw_VoqEn);

			अगर (acm_ctrl & BIT(2))
				AcmCtrl |= AcmHw_ViqEn;
			अन्यथा
				AcmCtrl &= (~AcmHw_ViqEn);

			अगर (acm_ctrl & BIT(1))
				AcmCtrl |= AcmHw_BeqEn;
			अन्यथा
				AcmCtrl &= (~AcmHw_BeqEn);

			DBG_88E("[HW_VAR_ACM_CTRL] Write 0x%X\n", AcmCtrl);
			usb_ग_लिखो8(Adapter, REG_ACMHWCTRL, AcmCtrl);
		पूर्ण
		अवरोध;
	हाल HW_VAR_AMPDU_MIN_SPACE:
		अणु
			u8 MinSpacingToSet;
			u8 SecMinSpace;

			MinSpacingToSet = *((u8 *)val);
			अगर (MinSpacingToSet <= 7) अणु
				चयन (Adapter->securitypriv.करोt11PrivacyAlgrthm) अणु
				हाल _NO_PRIVACY_:
				हाल _AES_:
					SecMinSpace = 0;
					अवरोध;
				हाल _WEP40_:
				हाल _WEP104_:
				हाल _TKIP_:
				हाल _TKIP_WTMIC_:
					SecMinSpace = 6;
					अवरोध;
				शेष:
					SecMinSpace = 7;
					अवरोध;
				पूर्ण
				अगर (MinSpacingToSet < SecMinSpace)
					MinSpacingToSet = SecMinSpace;
				usb_ग_लिखो8(Adapter, REG_AMPDU_MIN_SPACE, (usb_पढ़ो8(Adapter, REG_AMPDU_MIN_SPACE) & 0xf8) | MinSpacingToSet);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_AMPDU_FACTOR:
		अणु
			u8 RegToSet_Normal[4] = अणु0x41, 0xa8, 0x72, 0xb9पूर्ण;
			u8 FactorToSet;
			u8 *pRegToSet;
			u8 index = 0;

			pRegToSet = RegToSet_Normal; /*  0xb972a841; */
			FactorToSet = *((u8 *)val);
			अगर (FactorToSet <= 3) अणु
				FactorToSet = 1 << (FactorToSet + 2);
				अगर (FactorToSet > 0xf)
					FactorToSet = 0xf;

				क्रम (index = 0; index < 4; index++) अणु
					अगर ((pRegToSet[index] & 0xf0) > (FactorToSet << 4))
						pRegToSet[index] = (pRegToSet[index] & 0x0f) | (FactorToSet << 4);

					अगर ((pRegToSet[index] & 0x0f) > FactorToSet)
						pRegToSet[index] = (pRegToSet[index] & 0xf0) | (FactorToSet);

					usb_ग_लिखो8(Adapter, (REG_AGGLEN_LMT + index), pRegToSet[index]);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_RXDMA_AGG_PG_TH:
		अणु
			u8 threshold = *((u8 *)val);

			अगर (threshold == 0)
				threshold = haldata->UsbRxAggPageCount;
			usb_ग_लिखो8(Adapter, REG_RXDMA_AGG_PG_TH, threshold);
		पूर्ण
		अवरोध;
	हाल HW_VAR_SET_RPWM:
		अवरोध;
	हाल HW_VAR_H2C_FW_PWRMODE:
		अणु
			u8 psmode = (*(u8 *)val);

			/*  Forece leave RF low घातer mode क्रम 1T1R to prevent conficting setting in Fw घातer */
			/*  saving sequence. 2010.06.07. Added by tynli. Suggested by SD3 yschang. */
			अगर (psmode != PS_MODE_ACTIVE)
				ODM_RF_Saving(podmpriv, true);
			rtl8188e_set_FwPwrMode_cmd(Adapter, psmode);
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_FW_JOINBSSRPT:
		अणु
			u8 mstatus = (*(u8 *)val);

			rtl8188e_set_FwJoinBssReport_cmd(Adapter, mstatus);
		पूर्ण
		अवरोध;
	हाल HW_VAR_INITIAL_GAIN:
		अणु
			काष्ठा rtw_dig *pDigTable = &podmpriv->DM_DigTable;
			u32 rx_gain = ((u32 *)(val))[0];

			अगर (rx_gain == 0xff) अणु/* restore rx gain */
				ODM_Write_DIG(podmpriv, pDigTable->BackupIGValue);
			पूर्ण अन्यथा अणु
				pDigTable->BackupIGValue = pDigTable->CurIGValue;
				ODM_Write_DIG(podmpriv, rx_gain);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_TRIGGER_GPIO_0:
		rtl8192cu_trigger_gpio_0(Adapter);
		अवरोध;
	हाल HW_VAR_RPT_TIMER_SETTING:
		अणु
			u16 min_rpt_समय = (*(u16 *)val);

			ODM_RA_Set_TxRPT_Time(podmpriv, min_rpt_समय);
		पूर्ण
		अवरोध;
	हाल HW_VAR_ANTENNA_DIVERSITY_SELECT:
		अणु
			u8 Optimum_antenna = (*(u8 *)val);
			u8 Ant;
			/* चयन antenna to Optimum_antenna */
			अगर (haldata->CurAntenna !=  Optimum_antenna) अणु
				Ant = (Optimum_antenna == 2) ? MAIN_ANT : AUX_ANT;
				rtl88eu_dm_update_rx_idle_ant(&haldata->odmpriv, Ant);

				haldata->CurAntenna = Optimum_antenna;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_EFUSE_BYTES: /*  To set EFUE total used bytes, added by Roger, 2008.12.22. */
		haldata->EfuseUsedBytes = *((u16 *)val);
		अवरोध;
	हाल HW_VAR_FIFO_CLEARN_UP:
		अणु
			काष्ठा pwrctrl_priv *pwrpriv = &Adapter->pwrctrlpriv;
			u8 trycnt = 100;

			/* छोड़ो tx */
			usb_ग_लिखो8(Adapter, REG_TXPAUSE, 0xff);

			/* keep sn */
			Adapter->xmitpriv.nqos_ssn = usb_पढ़ो16(Adapter, REG_NQOS_SEQ);

			अगर (!pwrpriv->bkeepfwalive) अणु
				/* RX DMA stop */
				usb_ग_लिखो32(Adapter, REG_RXPKT_NUM, (usb_पढ़ो32(Adapter, REG_RXPKT_NUM) | RW_RELEASE_EN));
				करो अणु
					अगर (!(usb_पढ़ो32(Adapter, REG_RXPKT_NUM) & RXDMA_IDLE))
						अवरोध;
				पूर्ण जबतक (trycnt--);
				अगर (trycnt == 0)
					DBG_88E("Stop RX DMA failed......\n");

				/* RQPN Load 0 */
				usb_ग_लिखो16(Adapter, REG_RQPN_NPQ, 0x0);
				usb_ग_लिखो32(Adapter, REG_RQPN, 0x80000000);
				mdelay(10);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_CHECK_TXBUF:
		अवरोध;
	हाल HW_VAR_APFM_ON_MAC:
		haldata->bMacPwrCtrlOn = *val;
		DBG_88E("%s: bMacPwrCtrlOn=%d\n", __func__, haldata->bMacPwrCtrlOn);
		अवरोध;
	हाल HW_VAR_TX_RPT_MAX_MACID:
		अणु
			u8 maxMacid = *val;

			DBG_88E("### MacID(%d),Set Max Tx RPT MID(%d)\n", maxMacid, maxMacid + 1);
			usb_ग_लिखो8(Adapter, REG_TX_RPT_CTRL + 1, maxMacid + 1);
		पूर्ण
		अवरोध;
	हाल HW_VAR_H2C_MEDIA_STATUS_RPT:
		rtl8188e_set_FwMediaStatus_cmd(Adapter, (*(__le16 *)val));
		अवरोध;
	हाल HW_VAR_BCN_VALID:
		/* BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2, ग_लिखो 1 to clear, Clear by sw */
		usb_ग_लिखो8(Adapter, REG_TDECTRL + 2, usb_पढ़ो8(Adapter, REG_TDECTRL + 2) | BIT(0));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtw_hal_get_hwreg(काष्ठा adapter *Adapter, u8 variable, u8 *val)
अणु
	चयन (variable) अणु
	हाल HW_VAR_BASIC_RATE:
		*((u16 *)(val)) = Adapter->HalData->BasicRateSet;
		fallthrough;
	हाल HW_VAR_TXPAUSE:
		val[0] = usb_पढ़ो8(Adapter, REG_TXPAUSE);
		अवरोध;
	हाल HW_VAR_BCN_VALID:
		/* BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2 */
		val[0] = (BIT(0) & usb_पढ़ो8(Adapter, REG_TDECTRL + 2)) ? true : false;
		अवरोध;
	हाल HW_VAR_FWLPS_RF_ON:
		अणु
			/* When we halt NIC, we should check अगर FW LPS is leave. */
			अगर (Adapter->pwrctrlpriv.rf_pwrstate == rf_off) अणु
				/*  If it is in HW/SW Radio OFF or IPS state, we करो not check Fw LPS Leave, */
				/*  because Fw is unload. */
				val[0] = true;
			पूर्ण अन्यथा अणु
				u32 valRCR;

				valRCR = usb_पढ़ो32(Adapter, REG_RCR);
				valRCR &= 0x00070000;
				अगर (valRCR)
					val[0] = false;
				अन्यथा
					val[0] = true;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_VAR_CURRENT_ANTENNA:
		val[0] = Adapter->HalData->CurAntenna;
		अवरोध;
	हाल HW_VAR_EFUSE_BYTES: /*  To get EFUE total used bytes, added by Roger, 2008.12.22. */
		*((u16 *)(val)) = Adapter->HalData->EfuseUsedBytes;
		अवरोध;
	हाल HW_VAR_APFM_ON_MAC:
		*val = Adapter->HalData->bMacPwrCtrlOn;
		अवरोध;
	हाल HW_VAR_CHK_HI_QUEUE_EMPTY:
		*val = ((usb_पढ़ो32(Adapter, REG_HGQ_INFORMATION) & 0x0000ff00) == 0) ? true : false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*  */
/*	Description: */
/*		Query setting of specअगरied variable. */
/*  */
u8 rtw_hal_get_def_var(काष्ठा adapter *Adapter, क्रमागत hal_def_variable eVariable,
		       व्योम *pValue)
अणु
	काष्ठा hal_data_8188e *haldata = Adapter->HalData;
	u8 bResult = _SUCCESS;

	चयन (eVariable) अणु
	हाल HAL_DEF_UNDERCORATEDSMOOTHEDPWDB:
		अणु
			काष्ठा mlme_priv *pmlmepriv = &Adapter->mlmepriv;
			काष्ठा sta_priv *pstapriv = &Adapter->stapriv;
			काष्ठा sta_info *psta;

			psta = rtw_get_stainfo(pstapriv, pmlmepriv->cur_network.network.MacAddress);
			अगर (psta)
				*((पूर्णांक *)pValue) = psta->rssi_stat.UndecoratedSmoothedPWDB;
		पूर्ण
		अवरोध;
	हाल HAL_DEF_IS_SUPPORT_ANT_DIV:
		*((u8 *)pValue) = (haldata->AntDivCfg == 0) ? false : true;
		अवरोध;
	हाल HAL_DEF_CURRENT_ANTENNA:
		*((u8 *)pValue) = haldata->CurAntenna;
		अवरोध;
	हाल HAL_DEF_DRVINFO_SZ:
		*((u32 *)pValue) = DRVINFO_SZ;
		अवरोध;
	हाल HAL_DEF_MAX_RECVBUF_SZ:
		*((u32 *)pValue) = MAX_RECVBUF_SZ;
		अवरोध;
	हाल HAL_DEF_RX_PACKET_OFFSET:
		*((u32 *)pValue) = RXDESC_SIZE + DRVINFO_SZ;
		अवरोध;
	हाल HAL_DEF_DBG_DM_FUNC:
		*((u32 *)pValue) = haldata->odmpriv.SupportAbility;
		अवरोध;
	हाल HAL_DEF_RA_DECISION_RATE:
		अणु
			u8 MacID = *((u8 *)pValue);

			*((u8 *)pValue) = ODM_RA_GetDecisionRate_8188E(&haldata->odmpriv, MacID);
		पूर्ण
		अवरोध;
	हाल HAL_DEF_RA_SGI:
		अणु
			u8 MacID = *((u8 *)pValue);

			*((u8 *)pValue) = ODM_RA_GetShortGI_8188E(&haldata->odmpriv, MacID);
		पूर्ण
		अवरोध;
	हाल HAL_DEF_PT_PWR_STATUS:
		अणु
			u8 MacID = *((u8 *)pValue);

			*((u8 *)pValue) = ODM_RA_GetHwPwrStatus_8188E(&haldata->odmpriv, MacID);
		पूर्ण
		अवरोध;
	हाल HW_VAR_MAX_RX_AMPDU_FACTOR:
		*((u32 *)pValue) = MAX_AMPDU_FACTOR_64K;
		अवरोध;
	हाल HW_DEF_RA_INFO_DUMP:
		अणु
			u8 entry_id = *((u8 *)pValue);

			अगर (check_fwstate(&Adapter->mlmepriv, _FW_LINKED)) अणु
				DBG_88E("============ RA status check ===================\n");
				DBG_88E("Mac_id:%d , RateID = %d, RAUseRate = 0x%08x, RateSGI = %d, DecisionRate = 0x%02x ,PTStage = %d\n",
					entry_id,
					haldata->odmpriv.RAInfo[entry_id].RateID,
					haldata->odmpriv.RAInfo[entry_id].RAUseRate,
					haldata->odmpriv.RAInfo[entry_id].RateSGI,
					haldata->odmpriv.RAInfo[entry_id].DecisionRate,
					haldata->odmpriv.RAInfo[entry_id].PTStage);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल HW_DEF_ODM_DBG_FLAG:
		अणु
			काष्ठा odm_dm_काष्ठा *dm_ocm = &haldata->odmpriv;

			pr_info("dm_ocm->DebugComponents = 0x%llx\n", dm_ocm->DebugComponents);
		पूर्ण
		अवरोध;
	हाल HAL_DEF_DBG_DUMP_RXPKT:
		*((u8 *)pValue) = haldata->bDumpRxPkt;
		अवरोध;
	हाल HAL_DEF_DBG_DUMP_TXPKT:
		*((u8 *)pValue) = haldata->bDumpTxPkt;
		अवरोध;
	शेष:
		bResult = _FAIL;
		अवरोध;
	पूर्ण

	वापस bResult;
पूर्ण

व्योम UpdateHalRAMask8188EUsb(काष्ठा adapter *adapt, u32 mac_id, u8 rssi_level)
अणु
	u8 init_rate = 0;
	u8 networkType, raid;
	u32 mask, rate_biपंचांगap;
	u8 लघुGIrate = false;
	पूर्णांक	supportRateNum = 0;
	काष्ठा sta_info	*psta;
	काष्ठा odm_dm_काष्ठा *odmpriv = &adapt->HalData->odmpriv;
	काष्ठा mlme_ext_priv	*pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;
	काष्ठा wlan_bssid_ex	*cur_network = &pmlmeinfo->network;

	अगर (mac_id >= NUM_STA) /* CAM_SIZE */
		वापस;
	psta = pmlmeinfo->FW_sta_info[mac_id].psta;
	अगर (!psta)
		वापस;
	चयन (mac_id) अणु
	हाल 0:/*  क्रम infra mode */
		supportRateNum = rtw_get_rateset_len(cur_network->SupportedRates);
		networkType = judge_network_type(adapt, cur_network->SupportedRates) & 0xf;
		raid = networktype_to_raid(networkType);
		mask = update_supported_rate(cur_network->SupportedRates, supportRateNum);
		mask |= (pmlmeinfo->HT_enable) ? update_MSC_rate(&pmlmeinfo->HT_caps) : 0;
		अगर (support_लघु_GI(adapt, &pmlmeinfo->HT_caps))
			लघुGIrate = true;
		अवरोध;
	हाल 1:/* क्रम broadcast/multicast */
		supportRateNum = rtw_get_rateset_len(pmlmeinfo->FW_sta_info[mac_id].SupportedRates);
		अगर (pmlmeext->cur_wireless_mode & WIRELESS_11B)
			networkType = WIRELESS_11B;
		अन्यथा
			networkType = WIRELESS_11G;
		raid = networktype_to_raid(networkType);
		mask = update_basic_rate(cur_network->SupportedRates, supportRateNum);
		अवरोध;
	शेष: /* क्रम each sta in IBSS */
		supportRateNum = rtw_get_rateset_len(pmlmeinfo->FW_sta_info[mac_id].SupportedRates);
		networkType = judge_network_type(adapt, pmlmeinfo->FW_sta_info[mac_id].SupportedRates) & 0xf;
		raid = networktype_to_raid(networkType);
		mask = update_supported_rate(cur_network->SupportedRates, supportRateNum);

		/* toकरो: support HT in IBSS */
		अवरोध;
	पूर्ण

	rate_biपंचांगap = ODM_Get_Rate_Biपंचांगap(odmpriv, mac_id, mask, rssi_level);
	DBG_88E("%s => mac_id:%d, networkType:0x%02x, mask:0x%08x\n\t ==> rssi_level:%d, rate_bitmap:0x%08x\n",
		__func__, mac_id, networkType, mask, rssi_level, rate_biपंचांगap);

	mask &= rate_biपंचांगap;

	init_rate = get_highest_rate_idx(mask) & 0x3f;

	ODM_RA_UpdateRateInfo_8188E(odmpriv, mac_id, raid, mask, लघुGIrate);

	/* set ra_id */
	psta->raid = raid;
	psta->init_rate = init_rate;
पूर्ण

व्योम beacon_timing_control(काष्ठा adapter *adapt)
अणु
	u32 value32;
	काष्ठा mlme_ext_priv	*pmlmeext = &adapt->mlmeextpriv;
	काष्ठा mlme_ext_info	*pmlmeinfo = &pmlmeext->mlmext_info;
	u32 bcn_ctrl_reg			= REG_BCN_CTRL;
	/* reset TSF, enable update TSF, correcting TSF On Beacon */

	/* BCN पूर्णांकerval */
	usb_ग_लिखो16(adapt, REG_BCN_INTERVAL, pmlmeinfo->bcn_पूर्णांकerval);
	usb_ग_लिखो8(adapt, REG_ATIMWND, 0x02);/*  2ms */

	_InitBeaconParameters(adapt);

	usb_ग_लिखो8(adapt, REG_SLOT, 0x09);

	value32 = usb_पढ़ो32(adapt, REG_TCR);
	value32 &= ~TSFRST;
	usb_ग_लिखो32(adapt,  REG_TCR, value32);

	value32 |= TSFRST;
	usb_ग_लिखो32(adapt, REG_TCR, value32);

	/*  NOTE: Fix test chip's bug (about contention windows's अक्रमomness) */
	usb_ग_लिखो8(adapt,  REG_RXTSF_OFFSET_CCK, 0x50);
	usb_ग_लिखो8(adapt, REG_RXTSF_OFFSET_OFDM, 0x50);

	_BeaconFunctionEnable(adapt);

	ResumeTxBeacon(adapt);

	usb_ग_लिखो8(adapt, bcn_ctrl_reg, usb_पढ़ो8(adapt, bcn_ctrl_reg) | BIT(1));
पूर्ण

व्योम rtw_hal_def_value_init(काष्ठा adapter *adapt)
अणु
	काष्ठा hal_data_8188e *haldata = adapt->HalData;
	काष्ठा pwrctrl_priv *pwrctrlpriv;
	u8 i;

	pwrctrlpriv = &adapt->pwrctrlpriv;

	/* init शेष value */
	अगर (!pwrctrlpriv->bkeepfwalive)
		haldata->LastHMEBoxNum = 0;

	/* init dm शेष value */
	haldata->odmpriv.RFCalibrateInfo.bIQKInitialized = false;
	haldata->odmpriv.RFCalibrateInfo.TM_Trigger = 0;/* क्रम IQK */
	haldata->pwrGroupCnt = 0;
	haldata->PGMaxGroup = 13;
	haldata->odmpriv.RFCalibrateInfo.ThermalValue_HP_index = 0;
	क्रम (i = 0; i < HP_THERMAL_NUM; i++)
		haldata->odmpriv.RFCalibrateInfo.ThermalValue_HP[i] = 0;
पूर्ण
