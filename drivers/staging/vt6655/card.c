<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: card.c
 * Purpose: Provide functions to setup NIC operation mode
 * Functions:
 *      s_vSafeResetTx - Rest Tx
 *      CARDvSetRSPINF - Set RSPINF
 *      CARDvUpdateBasicTopRate - Update BasicTopRate
 *      CARDbAddBasicRate - Add to BasicRateSet
 *      CARDbIsOFDMinBasicRate - Check अगर any OFDM rate is in BasicRateSet
 *      CARDqGetTSFOffset - Calculate TSFOffset
 *      CARDbGetCurrentTSF - Read Current NIC TSF counter
 *      CARDqGetNextTBTT - Calculate Next Beacon TSF counter
 *      CARDvSetFirstNextTBTT - Set NIC Beacon समय
 *      CARDvUpdateNextTBTT - Sync. NIC Beacon समय
 *      CARDbRadioPowerOff - Turn Off NIC Radio Power
 *
 * Revision History:
 *      06-10-2003 Bryan YC Fan:  Re-ग_लिखो codes to support VT3253 spec.
 *      08-26-2003 Kyle Hsu:      Modअगरy the definition type of iobase.
 *      09-01-2003 Bryan YC Fan:  Add vUpdateIFS().
 *
 */

#समावेश "tmacro.h"
#समावेश "card.h"
#समावेश "baseband.h"
#समावेश "mac.h"
#समावेश "desc.h"
#समावेश "rf.h"
#समावेश "power.h"

/*---------------------  Static Definitions -------------------------*/

#घोषणा C_SIFS_A        16      /* micro sec. */
#घोषणा C_SIFS_BG       10

#घोषणा C_EIFS          80      /* micro sec. */

#घोषणा C_SLOT_SHORT    9       /* micro sec. */
#घोषणा C_SLOT_LONG     20

#घोषणा C_CWMIN_A       15      /* slot समय */
#घोषणा C_CWMIN_B       31

#घोषणा C_CWMAX         1023    /* slot समय */

#घोषणा WAIT_BEACON_TX_DOWN_TMO         3    /* Times */

/*---------------------  Static Variables  --------------------------*/

अटल स्थिर अचिन्हित लघु cwRXBCNTSFOff[MAX_RATE] = अणु
	17, 17, 17, 17, 34, 23, 17, 11, 8, 5, 4, 3पूर्ण;

/*---------------------  Static Functions  --------------------------*/

अटल व्योम s_vCalculateOFDMRParameter(अचिन्हित अक्षर byRate, u8 bb_type,
				       अचिन्हित अक्षर *pbyTxRate,
				       अचिन्हित अक्षर *pbyRsvTime);

/*---------------------  Export Functions  --------------------------*/

/*
 * Description: Calculate TxRate and RsvTime fields क्रम RSPINF in OFDM mode.
 *
 * Parameters:
 *  In:
 *      wRate           - Tx Rate
 *      byPktType       - Tx Packet type
 *  Out:
 *      pbyTxRate       - poपूर्णांकer to RSPINF TxRate field
 *      pbyRsvTime      - poपूर्णांकer to RSPINF RsvTime field
 *
 * Return Value: none
 */
अटल व्योम s_vCalculateOFDMRParameter(अचिन्हित अक्षर byRate,
				       u8 bb_type,
				       अचिन्हित अक्षर *pbyTxRate,
				       अचिन्हित अक्षर *pbyRsvTime)
अणु
	चयन (byRate) अणु
	हाल RATE_6M:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x9B;
			*pbyRsvTime = 44;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x8B;
			*pbyRsvTime = 50;
		पूर्ण
		अवरोध;

	हाल RATE_9M:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x9F;
			*pbyRsvTime = 36;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x8F;
			*pbyRsvTime = 42;
		पूर्ण
		अवरोध;

	हाल RATE_12M:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x9A;
			*pbyRsvTime = 32;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x8A;
			*pbyRsvTime = 38;
		पूर्ण
		अवरोध;

	हाल RATE_18M:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x9E;
			*pbyRsvTime = 28;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x8E;
			*pbyRsvTime = 34;
		पूर्ण
		अवरोध;

	हाल RATE_36M:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x9D;
			*pbyRsvTime = 24;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x8D;
			*pbyRsvTime = 30;
		पूर्ण
		अवरोध;

	हाल RATE_48M:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x98;
			*pbyRsvTime = 24;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x88;
			*pbyRsvTime = 30;
		पूर्ण
		अवरोध;

	हाल RATE_54M:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x9C;
			*pbyRsvTime = 24;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x8C;
			*pbyRsvTime = 30;
		पूर्ण
		अवरोध;

	हाल RATE_24M:
	शेष:
		अगर (bb_type == BB_TYPE_11A) अणु /* 5GHZ */
			*pbyTxRate = 0x99;
			*pbyRsvTime = 28;
		पूर्ण अन्यथा अणु
			*pbyTxRate = 0x89;
			*pbyRsvTime = 34;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/*---------------------  Export Functions  --------------------------*/

/*
 * Description: Update IFS
 *
 * Parameters:
 *  In:
 *      priv             - The adapter to be set
 *  Out:
 *      none
 *
 * Return Value: None.
 */
bool CARDbSetPhyParameter(काष्ठा vnt_निजी *priv, u8 bb_type)
अणु
	अचिन्हित अक्षर byCWMaxMin = 0;
	अचिन्हित अक्षर bySlot = 0;
	अचिन्हित अक्षर bySIFS = 0;
	अचिन्हित अक्षर byDIFS = 0;
	अचिन्हित अक्षर byData;
	पूर्णांक i;

	/* Set SIFS, DIFS, EIFS, SlotTime, CwMin */
	अगर (bb_type == BB_TYPE_11A) अणु
		अगर (priv->byRFType == RF_AIROHA7230) अणु
			/* AL7230 use single PAPE and connect to PAPE_2.4G */
			MACvSetBBType(priv->PortOffset, BB_TYPE_11G);
			priv->abyBBVGA[0] = 0x20;
			priv->abyBBVGA[2] = 0x10;
			priv->abyBBVGA[3] = 0x10;
			bb_पढ़ो_embedded(priv, 0xE7, &byData);
			अगर (byData == 0x1C)
				bb_ग_लिखो_embedded(priv, 0xE7, priv->abyBBVGA[0]);

		पूर्ण अन्यथा अगर (priv->byRFType == RF_UW2452) अणु
			MACvSetBBType(priv->PortOffset, BB_TYPE_11A);
			priv->abyBBVGA[0] = 0x18;
			bb_पढ़ो_embedded(priv, 0xE7, &byData);
			अगर (byData == 0x14) अणु
				bb_ग_लिखो_embedded(priv, 0xE7, priv->abyBBVGA[0]);
				bb_ग_लिखो_embedded(priv, 0xE1, 0x57);
			पूर्ण
		पूर्ण अन्यथा अणु
			MACvSetBBType(priv->PortOffset, BB_TYPE_11A);
		पूर्ण
		bb_ग_लिखो_embedded(priv, 0x88, 0x03);
		bySlot = C_SLOT_SHORT;
		bySIFS = C_SIFS_A;
		byDIFS = C_SIFS_A + 2 * C_SLOT_SHORT;
		byCWMaxMin = 0xA4;
	पूर्ण अन्यथा अगर (bb_type == BB_TYPE_11B) अणु
		MACvSetBBType(priv->PortOffset, BB_TYPE_11B);
		अगर (priv->byRFType == RF_AIROHA7230) अणु
			priv->abyBBVGA[0] = 0x1C;
			priv->abyBBVGA[2] = 0x00;
			priv->abyBBVGA[3] = 0x00;
			bb_पढ़ो_embedded(priv, 0xE7, &byData);
			अगर (byData == 0x20)
				bb_ग_लिखो_embedded(priv, 0xE7, priv->abyBBVGA[0]);

		पूर्ण अन्यथा अगर (priv->byRFType == RF_UW2452) अणु
			priv->abyBBVGA[0] = 0x14;
			bb_पढ़ो_embedded(priv, 0xE7, &byData);
			अगर (byData == 0x18) अणु
				bb_ग_लिखो_embedded(priv, 0xE7, priv->abyBBVGA[0]);
				bb_ग_लिखो_embedded(priv, 0xE1, 0xD3);
			पूर्ण
		पूर्ण
		bb_ग_लिखो_embedded(priv, 0x88, 0x02);
		bySlot = C_SLOT_LONG;
		bySIFS = C_SIFS_BG;
		byDIFS = C_SIFS_BG + 2 * C_SLOT_LONG;
		byCWMaxMin = 0xA5;
	पूर्ण अन्यथा अणु /* PK_TYPE_11GA & PK_TYPE_11GB */
		MACvSetBBType(priv->PortOffset, BB_TYPE_11G);
		अगर (priv->byRFType == RF_AIROHA7230) अणु
			priv->abyBBVGA[0] = 0x1C;
			priv->abyBBVGA[2] = 0x00;
			priv->abyBBVGA[3] = 0x00;
			bb_पढ़ो_embedded(priv, 0xE7, &byData);
			अगर (byData == 0x20)
				bb_ग_लिखो_embedded(priv, 0xE7, priv->abyBBVGA[0]);

		पूर्ण अन्यथा अगर (priv->byRFType == RF_UW2452) अणु
			priv->abyBBVGA[0] = 0x14;
			bb_पढ़ो_embedded(priv, 0xE7, &byData);
			अगर (byData == 0x18) अणु
				bb_ग_लिखो_embedded(priv, 0xE7, priv->abyBBVGA[0]);
				bb_ग_लिखो_embedded(priv, 0xE1, 0xD3);
			पूर्ण
		पूर्ण
		bb_ग_लिखो_embedded(priv, 0x88, 0x08);
		bySIFS = C_SIFS_BG;

		अगर (priv->bShortSlotTime) अणु
			bySlot = C_SLOT_SHORT;
			byDIFS = C_SIFS_BG + 2 * C_SLOT_SHORT;
		पूर्ण अन्यथा अणु
			bySlot = C_SLOT_LONG;
			byDIFS = C_SIFS_BG + 2 * C_SLOT_LONG;
		पूर्ण

		byCWMaxMin = 0xa4;

		क्रम (i = RATE_54M; i >= RATE_6M; i--) अणु
			अगर (priv->basic_rates & ((u32)(0x1 << i))) अणु
				byCWMaxMin |= 0x1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (priv->byRFType == RF_RFMD2959) अणु
		/*
		 * bcs TX_PE will reserve 3 us hardware's processing
		 * समय here is 2 us.
		 */
		bySIFS -= 3;
		byDIFS -= 3;
		/*
		 * TX_PE will reserve 3 us क्रम MAX2829 A mode only, it is क्रम
		 * better TX throughput; MAC will need 2 us to process, so the
		 * SIFS, DIFS can be लघुer by 2 us.
		 */
	पूर्ण

	अगर (priv->bySIFS != bySIFS) अणु
		priv->bySIFS = bySIFS;
		VNSvOutPortB(priv->PortOffset + MAC_REG_SIFS, priv->bySIFS);
	पूर्ण
	अगर (priv->byDIFS != byDIFS) अणु
		priv->byDIFS = byDIFS;
		VNSvOutPortB(priv->PortOffset + MAC_REG_DIFS, priv->byDIFS);
	पूर्ण
	अगर (priv->byEIFS != C_EIFS) अणु
		priv->byEIFS = C_EIFS;
		VNSvOutPortB(priv->PortOffset + MAC_REG_EIFS, priv->byEIFS);
	पूर्ण
	अगर (priv->bySlot != bySlot) अणु
		priv->bySlot = bySlot;
		VNSvOutPortB(priv->PortOffset + MAC_REG_SLOT, priv->bySlot);

		bb_set_लघु_slot_समय(priv);
	पूर्ण
	अगर (priv->byCWMaxMin != byCWMaxMin) अणु
		priv->byCWMaxMin = byCWMaxMin;
		VNSvOutPortB(priv->PortOffset + MAC_REG_CWMAXMIN0,
			     priv->byCWMaxMin);
	पूर्ण

	priv->byPacketType = CARDbyGetPktType(priv);

	CARDvSetRSPINF(priv, bb_type);

	वापस true;
पूर्ण

/*
 * Description: Sync. TSF counter to BSS
 *              Get TSF offset and ग_लिखो to HW
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be sync.
 *      byRxRate        - data rate of receive beacon
 *      qwBSSTimestamp  - Rx BCN's TSF
 *      qwLocalTSF      - Local TSF
 *  Out:
 *      none
 *
 * Return Value: none
 */
bool CARDbUpdateTSF(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRxRate,
		    u64 qwBSSTimestamp)
अणु
	u64 local_tsf;
	u64 qwTSFOffset = 0;

	CARDbGetCurrentTSF(priv, &local_tsf);

	अगर (qwBSSTimestamp != local_tsf) अणु
		qwTSFOffset = CARDqGetTSFOffset(byRxRate, qwBSSTimestamp,
						local_tsf);
		/* adjust TSF, HW's TSF add TSF Offset reg */
		VNSvOutPortD(priv->PortOffset + MAC_REG_TSFOFST,
			     (u32)qwTSFOffset);
		VNSvOutPortD(priv->PortOffset + MAC_REG_TSFOFST + 4,
			     (u32)(qwTSFOffset >> 32));
		MACvRegBitsOn(priv->PortOffset, MAC_REG_TFTCTL,
			      TFTCTL_TSFSYNCEN);
	पूर्ण
	वापस true;
पूर्ण

/*
 * Description: Set NIC TSF counter क्रम first Beacon समय
 *              Get NEXTTBTT from adjusted TSF and Beacon Interval
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be set.
 *      wBeaconInterval - Beacon Interval
 *  Out:
 *      none
 *
 * Return Value: true अगर succeed; otherwise false
 */
bool CARDbSetBeaconPeriod(काष्ठा vnt_निजी *priv,
			  अचिन्हित लघु wBeaconInterval)
अणु
	u64 qwNextTBTT = 0;

	CARDbGetCurrentTSF(priv, &qwNextTBTT); /* Get Local TSF counter */

	qwNextTBTT = CARDqGetNextTBTT(qwNextTBTT, wBeaconInterval);

	/* set HW beacon पूर्णांकerval */
	VNSvOutPortW(priv->PortOffset + MAC_REG_BI, wBeaconInterval);
	priv->wBeaconInterval = wBeaconInterval;
	/* Set NextTBTT */
	VNSvOutPortD(priv->PortOffset + MAC_REG_NEXTTBTT, (u32)qwNextTBTT);
	VNSvOutPortD(priv->PortOffset + MAC_REG_NEXTTBTT + 4,
		     (u32)(qwNextTBTT >> 32));
	MACvRegBitsOn(priv->PortOffset, MAC_REG_TFTCTL, TFTCTL_TBTTSYNCEN);

	वापस true;
पूर्ण

/*
 * Description: Turn off Radio घातer
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be turned off
 *  Out:
 *      none
 *
 */
व्योम CARDbRadioPowerOff(काष्ठा vnt_निजी *priv)
अणु
	अगर (priv->bRadioOff)
		वापस;

	चयन (priv->byRFType) अणु
	हाल RF_RFMD2959:
		MACvWordRegBitsOff(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				   SOFTPWRCTL_TXPEINV);
		MACvWordRegBitsOn(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				  SOFTPWRCTL_SWPE1);
		अवरोध;

	हाल RF_AIROHA:
	हाल RF_AL2230S:
	हाल RF_AIROHA7230:
		MACvWordRegBitsOff(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				   SOFTPWRCTL_SWPE2);
		MACvWordRegBitsOff(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				   SOFTPWRCTL_SWPE3);
		अवरोध;
	पूर्ण

	MACvRegBitsOff(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_RXON);

	bb_set_deep_sleep(priv, priv->byLocalID);

	priv->bRadioOff = true;
	pr_debug("chester power off\n");
	MACvRegBitsOn(priv->PortOffset, MAC_REG_GPIOCTL0,
		      LED_ACTSET);  /* LED issue */
पूर्ण

व्योम CARDvSafeResetTx(काष्ठा vnt_निजी *priv)
अणु
	अचिन्हित पूर्णांक uu;
	काष्ठा vnt_tx_desc *pCurrTD;

	/* initialize TD index */
	priv->apTailTD[0] = &priv->apTD0Rings[0];
	priv->apCurrTD[0] = &priv->apTD0Rings[0];

	priv->apTailTD[1] = &priv->apTD1Rings[0];
	priv->apCurrTD[1] = &priv->apTD1Rings[0];

	क्रम (uu = 0; uu < TYPE_MAXTD; uu++)
		priv->iTDUsed[uu] = 0;

	क्रम (uu = 0; uu < priv->opts.tx_descs[0]; uu++) अणु
		pCurrTD = &priv->apTD0Rings[uu];
		pCurrTD->td0.owner = OWNED_BY_HOST;
		/* init all Tx Packet poपूर्णांकer to शून्य */
	पूर्ण
	क्रम (uu = 0; uu < priv->opts.tx_descs[1]; uu++) अणु
		pCurrTD = &priv->apTD1Rings[uu];
		pCurrTD->td0.owner = OWNED_BY_HOST;
		/* init all Tx Packet poपूर्णांकer to शून्य */
	पूर्ण

	/* set MAC TD poपूर्णांकer */
	MACvSetCurrTXDescAddr(TYPE_TXDMA0, priv, priv->td0_pool_dma);

	MACvSetCurrTXDescAddr(TYPE_AC0DMA, priv, priv->td1_pool_dma);

	/* set MAC Beacon TX poपूर्णांकer */
	MACvSetCurrBCNTxDescAddr(priv->PortOffset,
				 (priv->tx_beacon_dma));
पूर्ण

/*
 * Description:
 *      Reset Rx
 *
 * Parameters:
 *  In:
 *      priv     - Poपूर्णांकer to the adapter
 *  Out:
 *      none
 *
 * Return Value: none
 */
व्योम CARDvSafeResetRx(काष्ठा vnt_निजी *priv)
अणु
	अचिन्हित पूर्णांक uu;
	काष्ठा vnt_rx_desc *pDesc;

	/* initialize RD index */
	priv->pCurrRD[0] = &priv->aRD0Ring[0];
	priv->pCurrRD[1] = &priv->aRD1Ring[0];

	/* init state, all RD is chip's */
	क्रम (uu = 0; uu < priv->opts.rx_descs0; uu++) अणु
		pDesc = &priv->aRD0Ring[uu];
		pDesc->rd0.res_count = cpu_to_le16(priv->rx_buf_sz);
		pDesc->rd0.owner = OWNED_BY_NIC;
		pDesc->rd1.req_count = cpu_to_le16(priv->rx_buf_sz);
	पूर्ण

	/* init state, all RD is chip's */
	क्रम (uu = 0; uu < priv->opts.rx_descs1; uu++) अणु
		pDesc = &priv->aRD1Ring[uu];
		pDesc->rd0.res_count = cpu_to_le16(priv->rx_buf_sz);
		pDesc->rd0.owner = OWNED_BY_NIC;
		pDesc->rd1.req_count = cpu_to_le16(priv->rx_buf_sz);
	पूर्ण

	/* set perPkt mode */
	MACvRx0PerPktMode(priv->PortOffset);
	MACvRx1PerPktMode(priv->PortOffset);
	/* set MAC RD poपूर्णांकer */
	MACvSetCurrRx0DescAddr(priv, priv->rd0_pool_dma);

	MACvSetCurrRx1DescAddr(priv, priv->rd1_pool_dma);
पूर्ण

/*
 * Description: Get response Control frame rate in CCK mode
 *
 * Parameters:
 *  In:
 *      priv             - The adapter to be set
 *      wRateIdx            - Receiving data rate
 *  Out:
 *      none
 *
 * Return Value: response Control frame rate
 */
अटल अचिन्हित लघु CARDwGetCCKControlRate(काष्ठा vnt_निजी *priv,
					     अचिन्हित लघु wRateIdx)
अणु
	अचिन्हित पूर्णांक ui = (अचिन्हित पूर्णांक)wRateIdx;

	जबतक (ui > RATE_1M) अणु
		अगर (priv->basic_rates & ((u32)0x1 << ui))
			वापस (अचिन्हित लघु)ui;

		ui--;
	पूर्ण
	वापस (अचिन्हित लघु)RATE_1M;
पूर्ण

/*
 * Description: Get response Control frame rate in OFDM mode
 *
 * Parameters:
 *  In:
 *      priv             - The adapter to be set
 *      wRateIdx            - Receiving data rate
 *  Out:
 *      none
 *
 * Return Value: response Control frame rate
 */
अटल अचिन्हित लघु CARDwGetOFDMControlRate(काष्ठा vnt_निजी *priv,
					      अचिन्हित लघु wRateIdx)
अणु
	अचिन्हित पूर्णांक ui = (अचिन्हित पूर्णांक)wRateIdx;

	pr_debug("BASIC RATE: %X\n", priv->basic_rates);

	अगर (!CARDbIsOFDMinBasicRate((व्योम *)priv)) अणु
		pr_debug("%s:(NO OFDM) %d\n", __func__, wRateIdx);
		अगर (wRateIdx > RATE_24M)
			wRateIdx = RATE_24M;
		वापस wRateIdx;
	पूर्ण
	जबतक (ui > RATE_11M) अणु
		अगर (priv->basic_rates & ((u32)0x1 << ui)) अणु
			pr_debug("%s : %d\n", __func__, ui);
			वापस (अचिन्हित लघु)ui;
		पूर्ण
		ui--;
	पूर्ण
	pr_debug("%s: 6M\n", __func__);
	वापस (अचिन्हित लघु)RATE_24M;
पूर्ण

/*
 * Description: Set RSPINF
 *
 * Parameters:
 *  In:
 *      priv             - The adapter to be set
 *  Out:
 *      none
 *
 * Return Value: None.
 */
व्योम CARDvSetRSPINF(काष्ठा vnt_निजी *priv, u8 bb_type)
अणु
	जोड़ vnt_phy_field_swap phy;
	अचिन्हित अक्षर byTxRate, byRsvTime;      /* For OFDM */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* Set to Page1 */
	MACvSelectPage1(priv->PortOffset);

	/* RSPINF_b_1 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_1M),
			  PK_TYPE_11B, &phy.field_पढ़ो);

	 /* swap over to get correct ग_लिखो order */
	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_1, phy.field_ग_लिखो);

	/* RSPINF_b_2 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_2M),
			  PK_TYPE_11B, &phy.field_पढ़ो);

	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_2, phy.field_ग_लिखो);

	/* RSPINF_b_5 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_5M),
			  PK_TYPE_11B, &phy.field_पढ़ो);

	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_5, phy.field_ग_लिखो);

	/* RSPINF_b_11 */
	vnt_get_phy_field(priv, 14,
			  CARDwGetCCKControlRate(priv, RATE_11M),
			  PK_TYPE_11B, &phy.field_पढ़ो);

	swap(phy.swap[0], phy.swap[1]);

	VNSvOutPortD(priv->PortOffset + MAC_REG_RSPINF_B_11, phy.field_ग_लिखो);

	/* RSPINF_a_6 */
	s_vCalculateOFDMRParameter(RATE_6M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_6,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_9 */
	s_vCalculateOFDMRParameter(RATE_9M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_9,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_12 */
	s_vCalculateOFDMRParameter(RATE_12M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_12,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_18 */
	s_vCalculateOFDMRParameter(RATE_18M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_18,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_24 */
	s_vCalculateOFDMRParameter(RATE_24M,
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_24,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_36 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate((व्योम *)priv,
							   RATE_36M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_36,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_48 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate((व्योम *)priv,
							   RATE_48M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_48,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_54 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate((व्योम *)priv,
							   RATE_54M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_54,
		     MAKEWORD(byTxRate, byRsvTime));
	/* RSPINF_a_72 */
	s_vCalculateOFDMRParameter(CARDwGetOFDMControlRate((व्योम *)priv,
							   RATE_54M),
				   bb_type,
				   &byTxRate,
				   &byRsvTime);
	VNSvOutPortW(priv->PortOffset + MAC_REG_RSPINF_A_72,
		     MAKEWORD(byTxRate, byRsvTime));
	/* Set to Page0 */
	MACvSelectPage0(priv->PortOffset);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

व्योम CARDvUpdateBasicTopRate(काष्ठा vnt_निजी *priv)
अणु
	अचिन्हित अक्षर byTopOFDM = RATE_24M, byTopCCK = RATE_1M;
	अचिन्हित अक्षर ii;

	/* Determines the highest basic rate. */
	क्रम (ii = RATE_54M; ii >= RATE_6M; ii--) अणु
		अगर ((priv->basic_rates) & ((u32)(1 << ii))) अणु
			byTopOFDM = ii;
			अवरोध;
		पूर्ण
	पूर्ण
	priv->byTopOFDMBasicRate = byTopOFDM;

	क्रम (ii = RATE_11M;; ii--) अणु
		अगर ((priv->basic_rates) & ((u32)(1 << ii))) अणु
			byTopCCK = ii;
			अवरोध;
		पूर्ण
		अगर (ii == RATE_1M)
			अवरोध;
	पूर्ण
	priv->byTopCCKBasicRate = byTopCCK;
पूर्ण

bool CARDbIsOFDMinBasicRate(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक ii;

	क्रम (ii = RATE_54M; ii >= RATE_6M; ii--) अणु
		अगर ((priv->basic_rates) & ((u32)BIT(ii)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अचिन्हित अक्षर CARDbyGetPktType(काष्ठा vnt_निजी *priv)
अणु
	अगर (priv->byBBType == BB_TYPE_11A || priv->byBBType == BB_TYPE_11B)
		वापस (अचिन्हित अक्षर)priv->byBBType;
	अन्यथा अगर (CARDbIsOFDMinBasicRate((व्योम *)priv))
		वापस PK_TYPE_11GA;
	अन्यथा
		वापस PK_TYPE_11GB;
पूर्ण

/*
 * Description: Calculate TSF offset of two TSF input
 *              Get TSF Offset from RxBCN's TSF and local TSF
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be sync.
 *      qwTSF1          - Rx BCN's TSF
 *      qwTSF2          - Local TSF
 *  Out:
 *      none
 *
 * Return Value: TSF Offset value
 */
u64 CARDqGetTSFOffset(अचिन्हित अक्षर byRxRate, u64 qwTSF1, u64 qwTSF2)
अणु
	अचिन्हित लघु wRxBcnTSFOffst;

	wRxBcnTSFOffst = cwRXBCNTSFOff[byRxRate % MAX_RATE];

	qwTSF2 += (u64)wRxBcnTSFOffst;

	वापस qwTSF1 - qwTSF2;
पूर्ण

/*
 * Description: Read NIC TSF counter
 *              Get local TSF counter
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be पढ़ो
 *  Out:
 *      qwCurrTSF       - Current TSF counter
 *
 * Return Value: true अगर success; otherwise false
 */
bool CARDbGetCurrentTSF(काष्ठा vnt_निजी *priv, u64 *pqwCurrTSF)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	अचिन्हित लघु ww;
	अचिन्हित अक्षर byData;

	MACvRegBitsOn(iobase, MAC_REG_TFTCTL, TFTCTL_TSFCNTRRD);
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		VNSvInPortB(iobase + MAC_REG_TFTCTL, &byData);
		अगर (!(byData & TFTCTL_TSFCNTRRD))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT)
		वापस false;
	VNSvInPortD(iobase + MAC_REG_TSFCNTR, (u32 *)pqwCurrTSF);
	VNSvInPortD(iobase + MAC_REG_TSFCNTR + 4, (u32 *)pqwCurrTSF + 1);

	वापस true;
पूर्ण

/*
 * Description: Read NIC TSF counter
 *              Get NEXTTBTT from adjusted TSF and Beacon Interval
 *
 * Parameters:
 *  In:
 *      qwTSF           - Current TSF counter
 *      wbeaconInterval - Beacon Interval
 *  Out:
 *      qwCurrTSF       - Current TSF counter
 *
 * Return Value: TSF value of next Beacon
 */
u64 CARDqGetNextTBTT(u64 qwTSF, अचिन्हित लघु wBeaconInterval)
अणु
	u32 beacon_पूर्णांक;

	beacon_पूर्णांक = wBeaconInterval * 1024;
	अगर (beacon_पूर्णांक) अणु
		करो_भाग(qwTSF, beacon_पूर्णांक);
		qwTSF += 1;
		qwTSF *= beacon_पूर्णांक;
	पूर्ण

	वापस qwTSF;
पूर्ण

/*
 * Description: Set NIC TSF counter क्रम first Beacon समय
 *              Get NEXTTBTT from adjusted TSF and Beacon Interval
 *
 * Parameters:
 *  In:
 *      iobase          - IO Base
 *      wBeaconInterval - Beacon Interval
 *  Out:
 *      none
 *
 * Return Value: none
 */
व्योम CARDvSetFirstNextTBTT(काष्ठा vnt_निजी *priv,
			   अचिन्हित लघु wBeaconInterval)
अणु
	व्योम __iomem *iobase = priv->PortOffset;
	u64 qwNextTBTT = 0;

	CARDbGetCurrentTSF(priv, &qwNextTBTT); /* Get Local TSF counter */

	qwNextTBTT = CARDqGetNextTBTT(qwNextTBTT, wBeaconInterval);
	/* Set NextTBTT */
	VNSvOutPortD(iobase + MAC_REG_NEXTTBTT, (u32)qwNextTBTT);
	VNSvOutPortD(iobase + MAC_REG_NEXTTBTT + 4, (u32)(qwNextTBTT >> 32));
	MACvRegBitsOn(iobase, MAC_REG_TFTCTL, TFTCTL_TBTTSYNCEN);
पूर्ण

/*
 * Description: Sync NIC TSF counter क्रम Beacon समय
 *              Get NEXTTBTT and ग_लिखो to HW
 *
 * Parameters:
 *  In:
 *      priv         - The adapter to be set
 *      qwTSF           - Current TSF counter
 *      wBeaconInterval - Beacon Interval
 *  Out:
 *      none
 *
 * Return Value: none
 */
व्योम CARDvUpdateNextTBTT(काष्ठा vnt_निजी *priv, u64 qwTSF,
			 अचिन्हित लघु wBeaconInterval)
अणु
	व्योम __iomem *iobase = priv->PortOffset;

	qwTSF = CARDqGetNextTBTT(qwTSF, wBeaconInterval);
	/* Set NextTBTT */
	VNSvOutPortD(iobase + MAC_REG_NEXTTBTT, (u32)qwTSF);
	VNSvOutPortD(iobase + MAC_REG_NEXTTBTT + 4, (u32)(qwTSF >> 32));
	MACvRegBitsOn(iobase, MAC_REG_TFTCTL, TFTCTL_TBTTSYNCEN);
	pr_debug("Card:Update Next TBTT[%8llx]\n", qwTSF);
पूर्ण
