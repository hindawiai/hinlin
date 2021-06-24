<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: rxtx.c
 *
 * Purpose: handle WMAC/802.3/802.11 rx & tx functions
 *
 * Author: Lynकरोn Chen
 *
 * Date: May 20, 2003
 *
 * Functions:
 *      s_vGenerateTxParameter - Generate tx dma required parameter.
 *      vGenerateMACHeader - Translate 802.3 to 802.11 header
 *      cbGetFragCount - Calculate fragment number count
 *      csBeacon_xmit - beacon tx function
 *      csMgmt_xmit - management tx function
 *      s_cbFillTxBufHead - fulfill tx dma buffer header
 *      s_uGetDataDuration - get tx data required duration
 *      s_uFillDataHead- fulfill tx data duration header
 *      s_uGetRTSCTSDuration- get rtx/cts required duration
 *      get_rtscts_समय- get rts/cts reserved समय
 *      s_uGetTxRsvTime- get frame reserved समय
 *      s_vFillCTSHead- fulfill CTS ctl header
 *      s_vFillFragParameter- Set fragment ctl parameter.
 *      s_vFillRTSHead- fulfill RTS ctl header
 *      s_vFillTxKey- fulfill tx encrypt key
 *      s_vSWencryption- Software encrypt header
 *      vDMA0_tx_80211- tx 802.11 frame via dma0
 *      vGenerateFIFOHeader- Generate tx FIFO ctl header
 *
 * Revision History:
 *
 */

#समावेश "device.h"
#समावेश "rxtx.h"
#समावेश "card.h"
#समावेश "mac.h"
#समावेश "baseband.h"
#समावेश "rf.h"

/*---------------------  Static Definitions -------------------------*/

/*---------------------  Static Classes  ----------------------------*/

/*---------------------  Static Variables  --------------------------*/

/*---------------------  Static Functions  --------------------------*/

/*---------------------  Static Definitions -------------------------*/
/* अगर packet size < 256 -> in-direct send
 * vpacket size >= 256 -> direct send
 */
#घोषणा CRITICAL_PACKET_LEN      256

अटल स्थिर अचिन्हित लघु wTimeStampOff[2][MAX_RATE] = अणु
	अणु384, 288, 226, 209, 54, 43, 37, 31, 28, 25, 24, 23पूर्ण, /* Long Preamble */
	अणु384, 192, 130, 113, 54, 43, 37, 31, 28, 25, 24, 23पूर्ण, /* Short Preamble */
पूर्ण;

अटल स्थिर अचिन्हित लघु wFB_Opt0[2][5] = अणु
	अणुRATE_12M, RATE_18M, RATE_24M, RATE_36M, RATE_48Mपूर्ण, /* fallback_rate0 */
	अणुRATE_12M, RATE_12M, RATE_18M, RATE_24M, RATE_36Mपूर्ण, /* fallback_rate1 */
पूर्ण;

अटल स्थिर अचिन्हित लघु wFB_Opt1[2][5] = अणु
	अणुRATE_12M, RATE_18M, RATE_24M, RATE_24M, RATE_36Mपूर्ण, /* fallback_rate0 */
	अणुRATE_6M,  RATE_6M,  RATE_12M, RATE_12M, RATE_18Mपूर्ण, /* fallback_rate1 */
पूर्ण;

#घोषणा RTSDUR_BB       0
#घोषणा RTSDUR_BA       1
#घोषणा RTSDUR_AA       2
#घोषणा CTSDUR_BA       3
#घोषणा RTSDUR_BA_F0    4
#घोषणा RTSDUR_AA_F0    5
#घोषणा RTSDUR_BA_F1    6
#घोषणा RTSDUR_AA_F1    7
#घोषणा CTSDUR_BA_F0    8
#घोषणा CTSDUR_BA_F1    9
#घोषणा DATADUR_B       10
#घोषणा DATADUR_A       11
#घोषणा DATADUR_A_F0    12
#घोषणा DATADUR_A_F1    13

/*---------------------  Static Functions  --------------------------*/
अटल
व्योम
s_vFillRTSHead(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byPktType,
	व्योम *pvRTS,
	अचिन्हित पूर्णांक	cbFrameLength,
	bool bNeedAck,
	bool bDisCRC,
	काष्ठा ieee80211_hdr *hdr,
	अचिन्हित लघु wCurrentRate,
	अचिन्हित अक्षर byFBOption
);

अटल
व्योम
s_vGenerateTxParameter(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byPktType,
	काष्ठा vnt_tx_fअगरo_head *,
	व्योम *pvRrvTime,
	व्योम *pvRTS,
	व्योम *pvCTS,
	अचिन्हित पूर्णांक	cbFrameSize,
	bool bNeedACK,
	अचिन्हित पूर्णांक	uDMAIdx,
	व्योम *psEthHeader,
	अचिन्हित लघु wCurrentRate
);

अटल अचिन्हित पूर्णांक
s_cbFillTxBufHead(काष्ठा vnt_निजी *pDevice, अचिन्हित अक्षर byPktType,
		  अचिन्हित अक्षर *pbyTxBufferAddr,
		  अचिन्हित पूर्णांक uDMAIdx, काष्ठा vnt_tx_desc *pHeadTD,
		  अचिन्हित पूर्णांक uNodeIndex);

अटल
__le16
s_uFillDataHead(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byPktType,
	व्योम *pTxDataHead,
	अचिन्हित पूर्णांक cbFrameLength,
	अचिन्हित पूर्णांक uDMAIdx,
	bool bNeedAck,
	अचिन्हित पूर्णांक uFragIdx,
	अचिन्हित पूर्णांक cbLastFragmentSize,
	अचिन्हित पूर्णांक uMACfragNum,
	अचिन्हित अक्षर byFBOption,
	अचिन्हित लघु wCurrentRate,
	bool is_pspoll
);

/*---------------------  Export Variables  --------------------------*/

अटल __le16 vnt_समय_stamp_off(काष्ठा vnt_निजी *priv, u16 rate)
अणु
	वापस cpu_to_le16(wTimeStampOff[priv->byPreambleType % 2]
							[rate % MAX_RATE]);
पूर्ण

/* byPktType : PK_TYPE_11A     0
 * PK_TYPE_11B     1
 * PK_TYPE_11GB    2
 * PK_TYPE_11GA    3
 */
अटल
अचिन्हित पूर्णांक
s_uGetTxRsvTime(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byPktType,
	अचिन्हित पूर्णांक cbFrameLength,
	अचिन्हित लघु wRate,
	bool bNeedAck
)
अणु
	अचिन्हित पूर्णांक uDataTime, uAckTime;

	uDataTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, cbFrameLength, wRate);

	अगर (!bNeedAck)
		वापस uDataTime;

	/*
	 * CCK mode  - 11b
	 * OFDM mode - 11g 2.4G & 11a 5G
	 */
	uAckTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14,
				     byPktType == PK_TYPE_11B ?
				     pDevice->byTopCCKBasicRate :
				     pDevice->byTopOFDMBasicRate);

	वापस uDataTime + pDevice->uSIFS + uAckTime;
पूर्ण

अटल __le16 vnt_rxtx_rsvसमय_le16(काष्ठा vnt_निजी *priv, u8 pkt_type,
				    u32 frame_length, u16 rate, bool need_ack)
अणु
	वापस cpu_to_le16((u16)s_uGetTxRsvTime(priv, pkt_type,
						frame_length, rate, need_ack));
पूर्ण

/* byFreqType: 0=>5GHZ 1=>2.4GHZ */
अटल __le16 get_rtscts_समय(काष्ठा vnt_निजी *priv,
			      अचिन्हित अक्षर rts_rsvtype,
			      अचिन्हित अक्षर pkt_type,
			      अचिन्हित पूर्णांक frame_length,
			      अचिन्हित लघु current_rate)
अणु
	अचिन्हित पूर्णांक rrv_समय = 0;
	अचिन्हित पूर्णांक rts_समय = 0;
	अचिन्हित पूर्णांक cts_समय = 0;
	अचिन्हित पूर्णांक ack_समय = 0;
	अचिन्हित पूर्णांक data_समय = 0;

	data_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, frame_length, current_rate);
	अगर (rts_rsvtype == 0) अणु /* RTSTxRrvTime_bb */
		rts_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 20, priv->byTopCCKBasicRate);
		ack_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 14, priv->byTopCCKBasicRate);
		cts_समय = ack_समय;
	पूर्ण अन्यथा अगर (rts_rsvtype == 1) अणु /* RTSTxRrvTime_ba, only in 2.4GHZ */
		rts_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 20, priv->byTopCCKBasicRate);
		cts_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 14, priv->byTopCCKBasicRate);
		ack_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 14, priv->byTopOFDMBasicRate);
	पूर्ण अन्यथा अगर (rts_rsvtype == 2) अणु /* RTSTxRrvTime_aa */
		rts_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 20, priv->byTopOFDMBasicRate);
		ack_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 14, priv->byTopOFDMBasicRate);
		cts_समय = ack_समय;
	पूर्ण अन्यथा अगर (rts_rsvtype == 3) अणु /* CTSTxRrvTime_ba, only in 2.4GHZ */
		cts_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 14, priv->byTopCCKBasicRate);
		ack_समय = bb_get_frame_समय(priv->byPreambleType, pkt_type, 14, priv->byTopOFDMBasicRate);
		rrv_समय = cts_समय + ack_समय + data_समय + 2 * priv->uSIFS;
		वापस cpu_to_le16((u16)rrv_समय);
	पूर्ण

	/* RTSRrvTime */
	rrv_समय = rts_समय + cts_समय + ack_समय + data_समय + 3 * priv->uSIFS;
	वापस cpu_to_le16((u16)rrv_समय);
पूर्ण

/* byFreqType 0: 5GHz, 1:2.4Ghz */
अटल
अचिन्हित पूर्णांक
s_uGetDataDuration(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byDurType,
	अचिन्हित पूर्णांक cbFrameLength,
	अचिन्हित अक्षर byPktType,
	अचिन्हित लघु wRate,
	bool bNeedAck,
	अचिन्हित पूर्णांक uFragIdx,
	अचिन्हित पूर्णांक cbLastFragmentSize,
	अचिन्हित पूर्णांक uMACfragNum,
	अचिन्हित अक्षर byFBOption
)
अणु
	bool bLastFrag = false;
	अचिन्हित पूर्णांक uAckTime = 0, uNextPktTime = 0, len;

	अगर (uFragIdx == (uMACfragNum - 1))
		bLastFrag = true;

	अगर (uFragIdx == (uMACfragNum - 2))
		len = cbLastFragmentSize;
	अन्यथा
		len = cbFrameLength;

	चयन (byDurType) अणु
	हाल DATADUR_B:    /* DATADUR_B */
		अगर (bNeedAck) अणु
			uAckTime = bb_get_frame_समय(pDevice->byPreambleType,
						     byPktType, 14,
						     pDevice->byTopCCKBasicRate);
		पूर्ण
		/* Non Frag or Last Frag */
		अगर ((uMACfragNum == 1) || bLastFrag) अणु
			अगर (!bNeedAck)
				वापस 0;
		पूर्ण अन्यथा अणु
			/* First Frag or Mid Frag */
			uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType,
						       len, wRate, bNeedAck);
		पूर्ण

		वापस pDevice->uSIFS + uAckTime + uNextPktTime;

	हाल DATADUR_A:    /* DATADUR_A */
		अगर (bNeedAck) अणु
			uAckTime = bb_get_frame_समय(pDevice->byPreambleType,
						     byPktType, 14,
						     pDevice->byTopOFDMBasicRate);
		पूर्ण
		/* Non Frag or Last Frag */
		अगर ((uMACfragNum == 1) || bLastFrag) अणु
			अगर (!bNeedAck)
				वापस 0;
		पूर्ण अन्यथा अणु
			/* First Frag or Mid Frag */
			uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType,
						       len, wRate, bNeedAck);
		पूर्ण

		वापस pDevice->uSIFS + uAckTime + uNextPktTime;

	हाल DATADUR_A_F0:    /* DATADUR_A_F0 */
	हाल DATADUR_A_F1:    /* DATADUR_A_F1 */
		अगर (bNeedAck) अणु
			uAckTime = bb_get_frame_समय(pDevice->byPreambleType,
						     byPktType, 14,
						     pDevice->byTopOFDMBasicRate);
		पूर्ण
		/* Non Frag or Last Frag */
		अगर ((uMACfragNum == 1) || bLastFrag) अणु
			अगर (!bNeedAck)
				वापस 0;
		पूर्ण अन्यथा अणु
			/* First Frag or Mid Frag */
			अगर (wRate < RATE_18M)
				wRate = RATE_18M;
			अन्यथा अगर (wRate > RATE_54M)
				wRate = RATE_54M;

			wRate -= RATE_18M;

			अगर (byFBOption == AUTO_FB_0)
				wRate = wFB_Opt0[FB_RATE0][wRate];
			अन्यथा
				wRate = wFB_Opt1[FB_RATE0][wRate];

			uNextPktTime = s_uGetTxRsvTime(pDevice, byPktType,
						       len, wRate, bNeedAck);
		पूर्ण

		वापस pDevice->uSIFS + uAckTime + uNextPktTime;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* byFreqType: 0=>5GHZ 1=>2.4GHZ */
अटल
__le16
s_uGetRTSCTSDuration(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byDurType,
	अचिन्हित पूर्णांक cbFrameLength,
	अचिन्हित अक्षर byPktType,
	अचिन्हित लघु wRate,
	bool bNeedAck,
	अचिन्हित अक्षर byFBOption
)
अणु
	अचिन्हित पूर्णांक uCTSTime = 0, uDurTime = 0;

	चयन (byDurType) अणु
	हाल RTSDUR_BB:    /* RTSDuration_bb */
		uCTSTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
		uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wRate, bNeedAck);
		अवरोध;

	हाल RTSDUR_BA:    /* RTSDuration_ba */
		uCTSTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
		uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wRate, bNeedAck);
		अवरोध;

	हाल RTSDUR_AA:    /* RTSDuration_aa */
		uCTSTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
		uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wRate, bNeedAck);
		अवरोध;

	हाल CTSDUR_BA:    /* CTSDuration_ba */
		uDurTime = pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wRate, bNeedAck);
		अवरोध;

	हाल RTSDUR_BA_F0: /* RTSDuration_ba_f0 */
		uCTSTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
		अगर ((byFBOption == AUTO_FB_0) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE0][wRate - RATE_18M], bNeedAck);
		अन्यथा अगर ((byFBOption == AUTO_FB_1) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE0][wRate - RATE_18M], bNeedAck);

		अवरोध;

	हाल RTSDUR_AA_F0: /* RTSDuration_aa_f0 */
		uCTSTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
		अगर ((byFBOption == AUTO_FB_0) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE0][wRate - RATE_18M], bNeedAck);
		अन्यथा अगर ((byFBOption == AUTO_FB_1) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE0][wRate - RATE_18M], bNeedAck);

		अवरोध;

	हाल RTSDUR_BA_F1: /* RTSDuration_ba_f1 */
		uCTSTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14, pDevice->byTopCCKBasicRate);
		अगर ((byFBOption == AUTO_FB_0) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE1][wRate - RATE_18M], bNeedAck);
		अन्यथा अगर ((byFBOption == AUTO_FB_1) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE1][wRate - RATE_18M], bNeedAck);

		अवरोध;

	हाल RTSDUR_AA_F1: /* RTSDuration_aa_f1 */
		uCTSTime = bb_get_frame_समय(pDevice->byPreambleType, byPktType, 14, pDevice->byTopOFDMBasicRate);
		अगर ((byFBOption == AUTO_FB_0) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE1][wRate - RATE_18M], bNeedAck);
		अन्यथा अगर ((byFBOption == AUTO_FB_1) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = uCTSTime + 2 * pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE1][wRate - RATE_18M], bNeedAck);

		अवरोध;

	हाल CTSDUR_BA_F0: /* CTSDuration_ba_f0 */
		अगर ((byFBOption == AUTO_FB_0) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE0][wRate - RATE_18M], bNeedAck);
		अन्यथा अगर ((byFBOption == AUTO_FB_1) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE0][wRate - RATE_18M], bNeedAck);

		अवरोध;

	हाल CTSDUR_BA_F1: /* CTSDuration_ba_f1 */
		अगर ((byFBOption == AUTO_FB_0) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt0[FB_RATE1][wRate - RATE_18M], bNeedAck);
		अन्यथा अगर ((byFBOption == AUTO_FB_1) && (wRate >= RATE_18M) && (wRate <= RATE_54M))
			uDurTime = pDevice->uSIFS + s_uGetTxRsvTime(pDevice, byPktType, cbFrameLength, wFB_Opt1[FB_RATE1][wRate - RATE_18M], bNeedAck);

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस cpu_to_le16((u16)uDurTime);
पूर्ण

अटल
__le16
s_uFillDataHead(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byPktType,
	व्योम *pTxDataHead,
	अचिन्हित पूर्णांक cbFrameLength,
	अचिन्हित पूर्णांक uDMAIdx,
	bool bNeedAck,
	अचिन्हित पूर्णांक uFragIdx,
	अचिन्हित पूर्णांक cbLastFragmentSize,
	अचिन्हित पूर्णांक uMACfragNum,
	अचिन्हित अक्षर byFBOption,
	अचिन्हित लघु wCurrentRate,
	bool is_pspoll
)
अणु
	काष्ठा vnt_tx_datahead_ab *buf = pTxDataHead;

	अगर (!pTxDataHead)
		वापस 0;

	अगर (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) अणु
		/* Auto Fallback */
		काष्ठा vnt_tx_datahead_g_fb *buf = pTxDataHead;

		अगर (byFBOption == AUTO_FB_NONE) अणु
			काष्ठा vnt_tx_datahead_g *buf = pTxDataHead;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
					  byPktType, &buf->a);

			vnt_get_phy_field(pDevice, cbFrameLength,
					  pDevice->byTopCCKBasicRate,
					  PK_TYPE_11B, &buf->b);

			अगर (is_pspoll) अणु
				__le16 dur = cpu_to_le16(pDevice->current_aid | BIT(14) | BIT(15));

				buf->duration_a = dur;
				buf->duration_b = dur;
			पूर्ण अन्यथा अणु
				/* Get Duration and TimeStamp */
				buf->duration_a =
					cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength,
									    byPktType, wCurrentRate, bNeedAck, uFragIdx,
									    cbLastFragmentSize, uMACfragNum,
									    byFBOption));
				buf->duration_b =
					cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_B, cbFrameLength,
									    PK_TYPE_11B, pDevice->byTopCCKBasicRate,
									    bNeedAck, uFragIdx, cbLastFragmentSize,
									    uMACfragNum, byFBOption));
			पूर्ण

			buf->समय_stamp_off_a = vnt_समय_stamp_off(pDevice, wCurrentRate);
			buf->समय_stamp_off_b = vnt_समय_stamp_off(pDevice, pDevice->byTopCCKBasicRate);

			वापस buf->duration_a;
		पूर्ण

		/* Get SignalField, ServiceField & Length */
		vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
				  byPktType, &buf->a);

		vnt_get_phy_field(pDevice, cbFrameLength,
				  pDevice->byTopCCKBasicRate,
				  PK_TYPE_11B, &buf->b);
		/* Get Duration and TimeStamp */
		buf->duration_a = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength, byPktType,
								      wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
		buf->duration_b = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_B, cbFrameLength, PK_TYPE_11B,
								       pDevice->byTopCCKBasicRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
		buf->duration_a_f0 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F0, cbFrameLength, byPktType,
									  wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
		buf->duration_a_f1 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F1, cbFrameLength, byPktType,
									 wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));

		buf->समय_stamp_off_a = vnt_समय_stamp_off(pDevice, wCurrentRate);
		buf->समय_stamp_off_b = vnt_समय_stamp_off(pDevice, pDevice->byTopCCKBasicRate);

		वापस buf->duration_a;
		  /* अगर (byFBOption == AUTO_FB_NONE) */
	पूर्ण अन्यथा अगर (byPktType == PK_TYPE_11A) अणु
		काष्ठा vnt_tx_datahead_ab *buf = pTxDataHead;

		अगर (byFBOption != AUTO_FB_NONE) अणु
			/* Auto Fallback */
			काष्ठा vnt_tx_datahead_a_fb *buf = pTxDataHead;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
					  byPktType, &buf->a);

			/* Get Duration and TimeStampOff */
			buf->duration = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength, byPktType,
									    wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->duration_f0 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F0, cbFrameLength, byPktType,
									       wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->duration_f1 = cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A_F1, cbFrameLength, byPktType,
										wCurrentRate, bNeedAck, uFragIdx, cbLastFragmentSize, uMACfragNum, byFBOption));
			buf->समय_stamp_off = vnt_समय_stamp_off(pDevice, wCurrentRate);
			वापस buf->duration;
		पूर्ण

		/* Get SignalField, ServiceField & Length */
		vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
				  byPktType, &buf->ab);

		अगर (is_pspoll) अणु
			__le16 dur = cpu_to_le16(pDevice->current_aid | BIT(14) | BIT(15));

			buf->duration = dur;
		पूर्ण अन्यथा अणु
			/* Get Duration and TimeStampOff */
			buf->duration =
				cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameLength, byPktType,
								    wCurrentRate, bNeedAck, uFragIdx,
								    cbLastFragmentSize, uMACfragNum,
								    byFBOption));
		पूर्ण

		buf->समय_stamp_off = vnt_समय_stamp_off(pDevice, wCurrentRate);
		वापस buf->duration;
	पूर्ण

	/* Get SignalField, ServiceField & Length */
	vnt_get_phy_field(pDevice, cbFrameLength, wCurrentRate,
			  byPktType, &buf->ab);

	अगर (is_pspoll) अणु
		__le16 dur = cpu_to_le16(pDevice->current_aid | BIT(14) | BIT(15));

		buf->duration = dur;
	पूर्ण अन्यथा अणु
		/* Get Duration and TimeStampOff */
		buf->duration =
			cpu_to_le16((u16)s_uGetDataDuration(pDevice, DATADUR_B, cbFrameLength, byPktType,
							    wCurrentRate, bNeedAck, uFragIdx,
							    cbLastFragmentSize, uMACfragNum,
							    byFBOption));
	पूर्ण

	buf->समय_stamp_off = vnt_समय_stamp_off(pDevice, wCurrentRate);
	वापस buf->duration;
पूर्ण

अटल
व्योम
s_vFillRTSHead(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byPktType,
	व्योम *pvRTS,
	अचिन्हित पूर्णांक cbFrameLength,
	bool bNeedAck,
	bool bDisCRC,
	काष्ठा ieee80211_hdr *hdr,
	अचिन्हित लघु wCurrentRate,
	अचिन्हित अक्षर byFBOption
)
अणु
	अचिन्हित पूर्णांक uRTSFrameLen = 20;

	अगर (!pvRTS)
		वापस;

	अगर (bDisCRC) अणु
		/* When CRCDIS bit is on, H/W क्रमgot to generate FCS क्रम
		 * RTS frame, in this हाल we need to decrease its length by 4.
		 */
		uRTSFrameLen -= 4;
	पूर्ण

	/* Note: So far RTSHead करोesn't appear in ATIM & Beacom DMA,
	 * so we करोn't need to take them पूर्णांकo account.
	 * Otherwise, we need to modअगरy codes क्रम them.
	 */
	अगर (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) अणु
		अगर (byFBOption == AUTO_FB_NONE) अणु
			काष्ठा vnt_rts_g *buf = pvRTS;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, uRTSFrameLen,
					  pDevice->byTopCCKBasicRate,
					  PK_TYPE_11B, &buf->b);

			vnt_get_phy_field(pDevice, uRTSFrameLen,
					  pDevice->byTopOFDMBasicRate,
					  byPktType, &buf->a);
			/* Get Duration */
			buf->duration_bb =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_BB,
						     cbFrameLength, PK_TYPE_11B,
						     pDevice->byTopCCKBasicRate,
						     bNeedAck, byFBOption);
			buf->duration_aa =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->duration_ba =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_BA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);

			buf->data.duration = buf->duration_aa;
			/* Get RTS Frame body */
			buf->data.frame_control =
					cpu_to_le16(IEEE80211_FTYPE_CTL |
						    IEEE80211_STYPE_RTS);

			ether_addr_copy(buf->data.ra, hdr->addr1);
			ether_addr_copy(buf->data.ta, hdr->addr2);
		पूर्ण अन्यथा अणु
			काष्ठा vnt_rts_g_fb *buf = pvRTS;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, uRTSFrameLen,
					  pDevice->byTopCCKBasicRate,
					  PK_TYPE_11B, &buf->b);

			vnt_get_phy_field(pDevice, uRTSFrameLen,
					  pDevice->byTopOFDMBasicRate,
					  byPktType, &buf->a);
			/* Get Duration */
			buf->duration_bb =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_BB,
						     cbFrameLength, PK_TYPE_11B,
						     pDevice->byTopCCKBasicRate,
						     bNeedAck, byFBOption);
			buf->duration_aa =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->duration_ba =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_BA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->rts_duration_ba_f0 =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_BA_F0,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->rts_duration_aa_f0 =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA_F0,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->rts_duration_ba_f1 =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_BA_F1,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->rts_duration_aa_f1 =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA_F1,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->data.duration = buf->duration_aa;
			/* Get RTS Frame body */
			buf->data.frame_control =
					cpu_to_le16(IEEE80211_FTYPE_CTL |
						    IEEE80211_STYPE_RTS);

			ether_addr_copy(buf->data.ra, hdr->addr1);
			ether_addr_copy(buf->data.ta, hdr->addr2);
		पूर्ण /* अगर (byFBOption == AUTO_FB_NONE) */
	पूर्ण अन्यथा अगर (byPktType == PK_TYPE_11A) अणु
		अगर (byFBOption == AUTO_FB_NONE) अणु
			काष्ठा vnt_rts_ab *buf = pvRTS;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, uRTSFrameLen,
					  pDevice->byTopOFDMBasicRate,
					  byPktType, &buf->ab);
			/* Get Duration */
			buf->duration =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->data.duration = buf->duration;
			/* Get RTS Frame body */
			buf->data.frame_control =
					cpu_to_le16(IEEE80211_FTYPE_CTL |
						    IEEE80211_STYPE_RTS);

			ether_addr_copy(buf->data.ra, hdr->addr1);
			ether_addr_copy(buf->data.ta, hdr->addr2);
		पूर्ण अन्यथा अणु
			काष्ठा vnt_rts_a_fb *buf = pvRTS;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, uRTSFrameLen,
					  pDevice->byTopOFDMBasicRate,
					  byPktType, &buf->a);
			/* Get Duration */
			buf->duration =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->rts_duration_f0 =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA_F0,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->rts_duration_f1 =
				s_uGetRTSCTSDuration(pDevice, RTSDUR_AA_F1,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);
			buf->data.duration = buf->duration;
			/* Get RTS Frame body */
			buf->data.frame_control =
					cpu_to_le16(IEEE80211_FTYPE_CTL |
						    IEEE80211_STYPE_RTS);

			ether_addr_copy(buf->data.ra, hdr->addr1);
			ether_addr_copy(buf->data.ta, hdr->addr2);
		पूर्ण
	पूर्ण अन्यथा अगर (byPktType == PK_TYPE_11B) अणु
		काष्ठा vnt_rts_ab *buf = pvRTS;
		/* Get SignalField, ServiceField & Length */
		vnt_get_phy_field(pDevice, uRTSFrameLen,
				  pDevice->byTopCCKBasicRate,
				  PK_TYPE_11B, &buf->ab);
		/* Get Duration */
		buf->duration =
			s_uGetRTSCTSDuration(pDevice, RTSDUR_BB, cbFrameLength,
					     byPktType, wCurrentRate, bNeedAck,
					     byFBOption);

		buf->data.duration = buf->duration;
		/* Get RTS Frame body */
		buf->data.frame_control =
			cpu_to_le16(IEEE80211_FTYPE_CTL | IEEE80211_STYPE_RTS);

		ether_addr_copy(buf->data.ra, hdr->addr1);
		ether_addr_copy(buf->data.ta, hdr->addr2);
	पूर्ण
पूर्ण

अटल
व्योम
s_vFillCTSHead(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित पूर्णांक uDMAIdx,
	अचिन्हित अक्षर byPktType,
	व्योम *pvCTS,
	अचिन्हित पूर्णांक cbFrameLength,
	bool bNeedAck,
	bool bDisCRC,
	अचिन्हित लघु wCurrentRate,
	अचिन्हित अक्षर byFBOption
)
अणु
	अचिन्हित पूर्णांक uCTSFrameLen = 14;

	अगर (!pvCTS)
		वापस;

	अगर (bDisCRC) अणु
		/* When CRCDIS bit is on, H/W क्रमgot to generate FCS क्रम
		 * CTS frame, in this हाल we need to decrease its length by 4.
		 */
		uCTSFrameLen -= 4;
	पूर्ण

	अगर (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) अणु
		अगर (byFBOption != AUTO_FB_NONE && uDMAIdx != TYPE_ATIMDMA && uDMAIdx != TYPE_BEACONDMA) अणु
			/* Auto Fall back */
			काष्ठा vnt_cts_fb *buf = pvCTS;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, uCTSFrameLen,
					  pDevice->byTopCCKBasicRate,
					  PK_TYPE_11B, &buf->b);

			buf->duration_ba =
				s_uGetRTSCTSDuration(pDevice, CTSDUR_BA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);

			/* Get CTSDuration_ba_f0 */
			buf->cts_duration_ba_f0 =
				s_uGetRTSCTSDuration(pDevice, CTSDUR_BA_F0,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);

			/* Get CTSDuration_ba_f1 */
			buf->cts_duration_ba_f1 =
				s_uGetRTSCTSDuration(pDevice, CTSDUR_BA_F1,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);

			/* Get CTS Frame body */
			buf->data.duration = buf->duration_ba;

			buf->data.frame_control =
				cpu_to_le16(IEEE80211_FTYPE_CTL |
					    IEEE80211_STYPE_CTS);

			buf->reserved2 = 0x0;

			ether_addr_copy(buf->data.ra,
					pDevice->abyCurrentNetAddr);
		पूर्ण अन्यथा अणु /* अगर (byFBOption != AUTO_FB_NONE && uDMAIdx != TYPE_ATIMDMA && uDMAIdx != TYPE_BEACONDMA) */
			काष्ठा vnt_cts *buf = pvCTS;
			/* Get SignalField, ServiceField & Length */
			vnt_get_phy_field(pDevice, uCTSFrameLen,
					  pDevice->byTopCCKBasicRate,
					  PK_TYPE_11B, &buf->b);

			/* Get CTSDuration_ba */
			buf->duration_ba =
				s_uGetRTSCTSDuration(pDevice, CTSDUR_BA,
						     cbFrameLength, byPktType,
						     wCurrentRate, bNeedAck,
						     byFBOption);

			/* Get CTS Frame body */
			buf->data.duration = buf->duration_ba;

			buf->data.frame_control =
				cpu_to_le16(IEEE80211_FTYPE_CTL |
					    IEEE80211_STYPE_CTS);

			buf->reserved2 = 0x0;
			ether_addr_copy(buf->data.ra,
					pDevice->abyCurrentNetAddr);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *
 * Description:
 *      Generate FIFO control क्रम MAC & Baseband controller
 *
 * Parameters:
 *  In:
 *      pDevice         - Poपूर्णांकer to adapter
 *      pTxDataHead     - Transmit Data Buffer
 *      pTxBufHead      - pTxBufHead
 *      pvRrvTime        - pvRrvTime
 *      pvRTS            - RTS Buffer
 *      pCTS            - CTS Buffer
 *      cbFrameSize     - Transmit Data Length (Hdr+Payload+FCS)
 *      bNeedACK        - If need ACK
 *      uDescIdx        - Desc Index
 *  Out:
 *      none
 *
 * Return Value: none
 *
 -
 * अचिन्हित पूर्णांक cbFrameSize, Hdr+Payload+FCS
 */
अटल
व्योम
s_vGenerateTxParameter(
	काष्ठा vnt_निजी *pDevice,
	अचिन्हित अक्षर byPktType,
	काष्ठा vnt_tx_fअगरo_head *tx_buffer_head,
	व्योम *pvRrvTime,
	व्योम *pvRTS,
	व्योम *pvCTS,
	अचिन्हित पूर्णांक cbFrameSize,
	bool bNeedACK,
	अचिन्हित पूर्णांक uDMAIdx,
	व्योम *psEthHeader,
	अचिन्हित लघु wCurrentRate
)
अणु
	u16 fअगरo_ctl = le16_to_cpu(tx_buffer_head->fअगरo_ctl);
	bool bDisCRC = false;
	अचिन्हित अक्षर byFBOption = AUTO_FB_NONE;

	tx_buffer_head->current_rate = cpu_to_le16(wCurrentRate);

	अगर (fअगरo_ctl & FIFOCTL_CRCDIS)
		bDisCRC = true;

	अगर (fअगरo_ctl & FIFOCTL_AUTO_FB_0)
		byFBOption = AUTO_FB_0;
	अन्यथा अगर (fअगरo_ctl & FIFOCTL_AUTO_FB_1)
		byFBOption = AUTO_FB_1;

	अगर (!pvRrvTime)
		वापस;

	अगर (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) अणु
		अगर (pvRTS) अणु /* RTS_need */
			/* Fill RsvTime */
			काष्ठा vnt_rrv_समय_rts *buf = pvRrvTime;

			buf->rts_rrv_समय_aa = get_rtscts_समय(pDevice, 2, byPktType, cbFrameSize, wCurrentRate);
			buf->rts_rrv_समय_ba = get_rtscts_समय(pDevice, 1, byPktType, cbFrameSize, wCurrentRate);
			buf->rts_rrv_समय_bb = get_rtscts_समय(pDevice, 0, byPktType, cbFrameSize, wCurrentRate);
			buf->rrv_समय_a = vnt_rxtx_rsvसमय_le16(pDevice, byPktType, cbFrameSize, wCurrentRate, bNeedACK);
			buf->rrv_समय_b = vnt_rxtx_rsvसमय_le16(pDevice, PK_TYPE_11B, cbFrameSize, pDevice->byTopCCKBasicRate, bNeedACK);

			s_vFillRTSHead(pDevice, byPktType, pvRTS, cbFrameSize, bNeedACK, bDisCRC, psEthHeader, wCurrentRate, byFBOption);
		पूर्ण अन्यथा अणु/* RTS_needless, PCF mode */
			काष्ठा vnt_rrv_समय_cts *buf = pvRrvTime;

			buf->rrv_समय_a = vnt_rxtx_rsvसमय_le16(pDevice, byPktType, cbFrameSize, wCurrentRate, bNeedACK);
			buf->rrv_समय_b = vnt_rxtx_rsvसमय_le16(pDevice, PK_TYPE_11B, cbFrameSize, pDevice->byTopCCKBasicRate, bNeedACK);
			buf->cts_rrv_समय_ba = get_rtscts_समय(pDevice, 3, byPktType, cbFrameSize, wCurrentRate);

			/* Fill CTS */
			s_vFillCTSHead(pDevice, uDMAIdx, byPktType, pvCTS, cbFrameSize, bNeedACK, bDisCRC, wCurrentRate, byFBOption);
		पूर्ण
	पूर्ण अन्यथा अगर (byPktType == PK_TYPE_11A) अणु
		अगर (pvRTS) अणु/* RTS_need, non PCF mode */
			काष्ठा vnt_rrv_समय_ab *buf = pvRrvTime;

			buf->rts_rrv_समय = get_rtscts_समय(pDevice, 2, byPktType, cbFrameSize, wCurrentRate);
			buf->rrv_समय = vnt_rxtx_rsvसमय_le16(pDevice, byPktType, cbFrameSize, wCurrentRate, bNeedACK);

			/* Fill RTS */
			s_vFillRTSHead(pDevice, byPktType, pvRTS, cbFrameSize, bNeedACK, bDisCRC, psEthHeader, wCurrentRate, byFBOption);
		पूर्ण अन्यथा अगर (!pvRTS) अणु/* RTS_needless, non PCF mode */
			काष्ठा vnt_rrv_समय_ab *buf = pvRrvTime;

			buf->rrv_समय = vnt_rxtx_rsvसमय_le16(pDevice, PK_TYPE_11A, cbFrameSize, wCurrentRate, bNeedACK);
		पूर्ण
	पूर्ण अन्यथा अगर (byPktType == PK_TYPE_11B) अणु
		अगर (pvRTS) अणु/* RTS_need, non PCF mode */
			काष्ठा vnt_rrv_समय_ab *buf = pvRrvTime;

			buf->rts_rrv_समय = get_rtscts_समय(pDevice, 0, byPktType, cbFrameSize, wCurrentRate);
			buf->rrv_समय = vnt_rxtx_rsvसमय_le16(pDevice, PK_TYPE_11B, cbFrameSize, wCurrentRate, bNeedACK);

			/* Fill RTS */
			s_vFillRTSHead(pDevice, byPktType, pvRTS, cbFrameSize, bNeedACK, bDisCRC, psEthHeader, wCurrentRate, byFBOption);
		पूर्ण अन्यथा अणु /* RTS_needless, non PCF mode */
			काष्ठा vnt_rrv_समय_ab *buf = pvRrvTime;

			buf->rrv_समय = vnt_rxtx_rsvसमय_le16(pDevice, PK_TYPE_11B, cbFrameSize, wCurrentRate, bNeedACK);
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
s_cbFillTxBufHead(काष्ठा vnt_निजी *pDevice, अचिन्हित अक्षर byPktType,
		  अचिन्हित अक्षर *pbyTxBufferAddr,
		  अचिन्हित पूर्णांक uDMAIdx, काष्ठा vnt_tx_desc *pHeadTD,
		  अचिन्हित पूर्णांक is_pspoll)
अणु
	काष्ठा vnt_td_info *td_info = pHeadTD->td_info;
	काष्ठा sk_buff *skb = td_info->skb;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा vnt_tx_fअगरo_head *tx_buffer_head =
			(काष्ठा vnt_tx_fअगरo_head *)td_info->buf;
	u16 fअगरo_ctl = le16_to_cpu(tx_buffer_head->fअगरo_ctl);
	अचिन्हित पूर्णांक cbFrameSize;
	__le16 uDuration;
	अचिन्हित अक्षर *pbyBuffer;
	अचिन्हित पूर्णांक uLength = 0;
	अचिन्हित पूर्णांक cbMICHDR = 0;
	अचिन्हित पूर्णांक uMACfragNum = 1;
	अचिन्हित पूर्णांक uPadding = 0;
	अचिन्हित पूर्णांक cbReqCount = 0;
	bool bNeedACK = (bool)(fअगरo_ctl & FIFOCTL_NEEDACK);
	bool bRTS = (bool)(fअगरo_ctl & FIFOCTL_RTS);
	काष्ठा vnt_tx_desc *ptdCurr;
	अचिन्हित पूर्णांक cbHeaderLength = 0;
	व्योम *pvRrvTime = शून्य;
	काष्ठा vnt_mic_hdr *pMICHDR = शून्य;
	व्योम *pvRTS = शून्य;
	व्योम *pvCTS = शून्य;
	व्योम *pvTxDataHd = शून्य;
	अचिन्हित लघु wTxBufSize;   /* FFinfo size */
	अचिन्हित अक्षर byFBOption = AUTO_FB_NONE;

	cbFrameSize = skb->len + 4;

	अगर (info->control.hw_key) अणु
		चयन (info->control.hw_key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_CCMP:
			cbMICHDR = माप(काष्ठा vnt_mic_hdr);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		cbFrameSize += info->control.hw_key->icv_len;

		अगर (pDevice->byLocalID > REV_ID_VT3253_A1) अणु
			/* MAC Header should be padding 0 to DW alignment. */
			uPadding = 4 - (ieee80211_get_hdrlen_from_skb(skb) % 4);
			uPadding %= 4;
		पूर्ण
	पूर्ण

	/*
	 * Use क्रम AUTO FALL BACK
	 */
	अगर (fअगरo_ctl & FIFOCTL_AUTO_FB_0)
		byFBOption = AUTO_FB_0;
	अन्यथा अगर (fअगरo_ctl & FIFOCTL_AUTO_FB_1)
		byFBOption = AUTO_FB_1;

	/* Set RrvTime/RTS/CTS Buffer */
	wTxBufSize = माप(काष्ठा vnt_tx_fअगरo_head);
	अगर (byPktType == PK_TYPE_11GB || byPktType == PK_TYPE_11GA) अणु/* 802.11g packet */

		अगर (byFBOption == AUTO_FB_NONE) अणु
			अगर (bRTS) अणु/* RTS_need */
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts));
				pvRTS = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts) + cbMICHDR);
				pvCTS = शून्य;
				pvTxDataHd = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts) +
							cbMICHDR + माप(काष्ठा vnt_rts_g));
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts) +
							cbMICHDR + माप(काष्ठा vnt_rts_g) +
							माप(काष्ठा vnt_tx_datahead_g);
			पूर्ण अन्यथा अणु /* RTS_needless */
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_cts));
				pvRTS = शून्य;
				pvCTS = (व्योम *) (pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_cts) + cbMICHDR);
				pvTxDataHd = (व्योम *)(pbyTxBufferAddr + wTxBufSize +
						माप(काष्ठा vnt_rrv_समय_cts) + cbMICHDR + माप(काष्ठा vnt_cts));
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_cts) +
							cbMICHDR + माप(काष्ठा vnt_cts) + माप(काष्ठा vnt_tx_datahead_g);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Auto Fall Back */
			अगर (bRTS) अणु/* RTS_need */
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts));
				pvRTS = (व्योम *) (pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts) + cbMICHDR);
				pvCTS = शून्य;
				pvTxDataHd = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts) +
					cbMICHDR + माप(काष्ठा vnt_rts_g_fb));
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_rts) +
					cbMICHDR + माप(काष्ठा vnt_rts_g_fb) + माप(काष्ठा vnt_tx_datahead_g_fb);
			पूर्ण अन्यथा अणु /* RTS_needless */
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_cts));
				pvRTS = शून्य;
				pvCTS = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_cts) + cbMICHDR);
				pvTxDataHd = (व्योम  *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_cts) +
					cbMICHDR + माप(काष्ठा vnt_cts_fb));
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_cts) +
					cbMICHDR + माप(काष्ठा vnt_cts_fb) + माप(काष्ठा vnt_tx_datahead_g_fb);
			पूर्ण
		पूर्ण /* Auto Fall Back */
	पूर्ण अन्यथा अणु/* 802.11a/b packet */

		अगर (byFBOption == AUTO_FB_NONE) अणु
			अगर (bRTS) अणु
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab));
				pvRTS = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) + cbMICHDR);
				pvCTS = शून्य;
				pvTxDataHd = (व्योम *)(pbyTxBufferAddr + wTxBufSize +
					माप(काष्ठा vnt_rrv_समय_ab) + cbMICHDR + माप(काष्ठा vnt_rts_ab));
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) +
					cbMICHDR + माप(काष्ठा vnt_rts_ab) + माप(काष्ठा vnt_tx_datahead_ab);
			पूर्ण अन्यथा अणु /* RTS_needless, need MICHDR */
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab));
				pvRTS = शून्य;
				pvCTS = शून्य;
				pvTxDataHd = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) + cbMICHDR);
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) +
					cbMICHDR + माप(काष्ठा vnt_tx_datahead_ab);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Auto Fall Back */
			अगर (bRTS) अणु /* RTS_need */
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab));
				pvRTS = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) + cbMICHDR);
				pvCTS = शून्य;
				pvTxDataHd = (व्योम *)(pbyTxBufferAddr + wTxBufSize +
					माप(काष्ठा vnt_rrv_समय_ab) + cbMICHDR + माप(काष्ठा vnt_rts_a_fb));
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) +
					cbMICHDR + माप(काष्ठा vnt_rts_a_fb) + माप(काष्ठा vnt_tx_datahead_a_fb);
			पूर्ण अन्यथा अणु /* RTS_needless */
				pvRrvTime = (व्योम *)(pbyTxBufferAddr + wTxBufSize);
				pMICHDR = (काष्ठा vnt_mic_hdr *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab));
				pvRTS = शून्य;
				pvCTS = शून्य;
				pvTxDataHd = (व्योम *)(pbyTxBufferAddr + wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) + cbMICHDR);
				cbHeaderLength = wTxBufSize + माप(काष्ठा vnt_rrv_समय_ab) +
					cbMICHDR + माप(काष्ठा vnt_tx_datahead_a_fb);
			पूर्ण
		पूर्ण /* Auto Fall Back */
	पूर्ण

	td_info->mic_hdr = pMICHDR;

	स_रखो((व्योम *)(pbyTxBufferAddr + wTxBufSize), 0, (cbHeaderLength - wTxBufSize));

	/* Fill FIFO,RrvTime,RTS,and CTS */
	s_vGenerateTxParameter(pDevice, byPktType, tx_buffer_head, pvRrvTime, pvRTS, pvCTS,
			       cbFrameSize, bNeedACK, uDMAIdx, hdr, pDevice->wCurrentRate);
	/* Fill DataHead */
	uDuration = s_uFillDataHead(pDevice, byPktType, pvTxDataHd, cbFrameSize, uDMAIdx, bNeedACK,
				    0, 0, uMACfragNum, byFBOption, pDevice->wCurrentRate, is_pspoll);

	hdr->duration_id = uDuration;

	cbReqCount = cbHeaderLength + uPadding + skb->len;
	pbyBuffer = (अचिन्हित अक्षर *)pHeadTD->td_info->buf;
	uLength = cbHeaderLength + uPadding;

	/* Copy the Packet पूर्णांकo a tx Buffer */
	स_नकल((pbyBuffer + uLength), skb->data, skb->len);

	ptdCurr = pHeadTD;

	ptdCurr->td_info->req_count = (u16)cbReqCount;

	वापस cbHeaderLength;
पूर्ण

अटल व्योम vnt_fill_txkey(काष्ठा ieee80211_hdr *hdr, u8 *key_buffer,
			   काष्ठा ieee80211_key_conf *tx_key,
			   काष्ठा sk_buff *skb,	u16 payload_len,
			   काष्ठा vnt_mic_hdr *mic_hdr)
अणु
	u64 pn64;
	u8 *iv = ((u8 *)hdr + ieee80211_get_hdrlen_from_skb(skb));

	/* strip header and icv len from payload */
	payload_len -= ieee80211_get_hdrlen_from_skb(skb);
	payload_len -= tx_key->icv_len;

	चयन (tx_key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		स_नकल(key_buffer, iv, 3);
		स_नकल(key_buffer + 3, tx_key->key, tx_key->keylen);

		अगर (tx_key->keylen == WLAN_KEY_LEN_WEP40) अणु
			स_नकल(key_buffer + 8, iv, 3);
			स_नकल(key_buffer + 11,
			       tx_key->key, WLAN_KEY_LEN_WEP40);
		पूर्ण

		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		ieee80211_get_tkip_p2k(tx_key, skb, key_buffer);

		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:

		अगर (!mic_hdr)
			वापस;

		mic_hdr->id = 0x59;
		mic_hdr->payload_len = cpu_to_be16(payload_len);
		ether_addr_copy(mic_hdr->mic_addr2, hdr->addr2);

		pn64 = atomic64_पढ़ो(&tx_key->tx_pn);
		mic_hdr->ccmp_pn[5] = pn64;
		mic_hdr->ccmp_pn[4] = pn64 >> 8;
		mic_hdr->ccmp_pn[3] = pn64 >> 16;
		mic_hdr->ccmp_pn[2] = pn64 >> 24;
		mic_hdr->ccmp_pn[1] = pn64 >> 32;
		mic_hdr->ccmp_pn[0] = pn64 >> 40;

		अगर (ieee80211_has_a4(hdr->frame_control))
			mic_hdr->hlen = cpu_to_be16(28);
		अन्यथा
			mic_hdr->hlen = cpu_to_be16(22);

		ether_addr_copy(mic_hdr->addr1, hdr->addr1);
		ether_addr_copy(mic_hdr->addr2, hdr->addr2);
		ether_addr_copy(mic_hdr->addr3, hdr->addr3);

		mic_hdr->frame_control = cpu_to_le16(
			le16_to_cpu(hdr->frame_control) & 0xc78f);
		mic_hdr->seq_ctrl = cpu_to_le16(
				le16_to_cpu(hdr->seq_ctrl) & 0xf);

		अगर (ieee80211_has_a4(hdr->frame_control))
			ether_addr_copy(mic_hdr->addr4, hdr->addr4);

		स_नकल(key_buffer, tx_key->key, WLAN_KEY_LEN_CCMP);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक vnt_generate_fअगरo_header(काष्ठा vnt_निजी *priv, u32 dma_idx,
			     काष्ठा vnt_tx_desc *head_td, काष्ठा sk_buff *skb)
अणु
	काष्ठा vnt_td_info *td_info = head_td->td_info;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *tx_rate = &info->control.rates[0];
	काष्ठा ieee80211_rate *rate;
	काष्ठा ieee80211_key_conf *tx_key;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा vnt_tx_fअगरo_head *tx_buffer_head =
			(काष्ठा vnt_tx_fअगरo_head *)td_info->buf;
	u16 tx_body_size = skb->len, current_rate;
	u8 pkt_type;
	bool is_pspoll = false;

	स_रखो(tx_buffer_head, 0, माप(*tx_buffer_head));

	hdr = (काष्ठा ieee80211_hdr *)(skb->data);

	rate = ieee80211_get_tx_rate(priv->hw, info);

	current_rate = rate->hw_value;
	अगर (priv->wCurrentRate != current_rate &&
	    !(priv->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL)) अणु
		priv->wCurrentRate = current_rate;

		RFbSetPower(priv, priv->wCurrentRate,
			    priv->hw->conf.chandef.chan->hw_value);
	पूर्ण

	अगर (current_rate > RATE_11M) अणु
		अगर (info->band == NL80211_BAND_5GHZ) अणु
			pkt_type = PK_TYPE_11A;
		पूर्ण अन्यथा अणु
			अगर (tx_rate->flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
				pkt_type = PK_TYPE_11GB;
			अन्यथा
				pkt_type = PK_TYPE_11GA;
		पूर्ण
	पूर्ण अन्यथा अणु
		pkt_type = PK_TYPE_11B;
	पूर्ण

	/*Set fअगरo controls */
	अगर (pkt_type == PK_TYPE_11A)
		tx_buffer_head->fअगरo_ctl = 0;
	अन्यथा अगर (pkt_type == PK_TYPE_11B)
		tx_buffer_head->fअगरo_ctl = cpu_to_le16(FIFOCTL_11B);
	अन्यथा अगर (pkt_type == PK_TYPE_11GB)
		tx_buffer_head->fअगरo_ctl = cpu_to_le16(FIFOCTL_11GB);
	अन्यथा अगर (pkt_type == PK_TYPE_11GA)
		tx_buffer_head->fअगरo_ctl = cpu_to_le16(FIFOCTL_11GA);

	/* generate पूर्णांकerrupt */
	tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_GENINT);

	अगर (!ieee80211_is_data(hdr->frame_control)) अणु
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_TMOEN);
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_ISDMA0);
		tx_buffer_head->समय_stamp =
			cpu_to_le16(DEFAULT_MGN_LIFETIME_RES_64us);
	पूर्ण अन्यथा अणु
		tx_buffer_head->समय_stamp =
			cpu_to_le16(DEFAULT_MSDU_LIFETIME_RES_64us);
	पूर्ण

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_NEEDACK);

	अगर (ieee80211_has_retry(hdr->frame_control))
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_LRETRY);

	अगर (tx_rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		priv->byPreambleType = PREAMBLE_SHORT;
	अन्यथा
		priv->byPreambleType = PREAMBLE_LONG;

	अगर (tx_rate->flags & IEEE80211_TX_RC_USE_RTS_CTS)
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_RTS);

	अगर (ieee80211_has_a4(hdr->frame_control)) अणु
		tx_buffer_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_LHEAD);
		priv->bLongHeader = true;
	पूर्ण

	अगर (info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER)
		is_pspoll = true;

	tx_buffer_head->frag_ctl =
			cpu_to_le16(ieee80211_get_hdrlen_from_skb(skb) << 10);

	अगर (info->control.hw_key) अणु
		tx_key = info->control.hw_key;

		चयन (info->control.hw_key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			tx_buffer_head->frag_ctl |= cpu_to_le16(FRAGCTL_LEGACY);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			tx_buffer_head->frag_ctl |= cpu_to_le16(FRAGCTL_TKIP);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			tx_buffer_head->frag_ctl |= cpu_to_le16(FRAGCTL_AES);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	tx_buffer_head->current_rate = cpu_to_le16(current_rate);

	/* legacy rates TODO use ieee80211_tx_rate */
	अगर (current_rate >= RATE_18M && ieee80211_is_data(hdr->frame_control)) अणु
		अगर (priv->byAutoFBCtrl == AUTO_FB_0)
			tx_buffer_head->fअगरo_ctl |=
						cpu_to_le16(FIFOCTL_AUTO_FB_0);
		अन्यथा अगर (priv->byAutoFBCtrl == AUTO_FB_1)
			tx_buffer_head->fअगरo_ctl |=
						cpu_to_le16(FIFOCTL_AUTO_FB_1);
	पूर्ण

	tx_buffer_head->frag_ctl |= cpu_to_le16(FRAGCTL_NONFRAG);

	s_cbFillTxBufHead(priv, pkt_type, (u8 *)tx_buffer_head,
			  dma_idx, head_td, is_pspoll);

	अगर (info->control.hw_key) अणु
		tx_key = info->control.hw_key;
		अगर (tx_key->keylen > 0)
			vnt_fill_txkey(hdr, tx_buffer_head->tx_key,
				       tx_key, skb, tx_body_size,
				       td_info->mic_hdr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vnt_beacon_xmit(काष्ठा vnt_निजी *priv,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा vnt_tx_लघु_buf_head *लघु_head =
		(काष्ठा vnt_tx_लघु_buf_head *)priv->tx_beacon_bufs;
	काष्ठा ieee80211_mgmt *mgmt_hdr = (काष्ठा ieee80211_mgmt *)
				(priv->tx_beacon_bufs + माप(*लघु_head));
	काष्ठा ieee80211_tx_info *info;
	u32 frame_size = skb->len + 4;
	u16 current_rate;

	स_रखो(priv->tx_beacon_bufs, 0, माप(*लघु_head));

	अगर (priv->byBBType == BB_TYPE_11A) अणु
		current_rate = RATE_6M;

		/* Get SignalField,ServiceField,Length */
		vnt_get_phy_field(priv, frame_size, current_rate,
				  PK_TYPE_11A, &लघु_head->ab);

		/* Get Duration and TimeStampOff */
		लघु_head->duration =
			cpu_to_le16((u16)s_uGetDataDuration(priv, DATADUR_B,
				    frame_size, PK_TYPE_11A, current_rate,
				    false, 0, 0, 1, AUTO_FB_NONE));

		लघु_head->समय_stamp_off =
				vnt_समय_stamp_off(priv, current_rate);
	पूर्ण अन्यथा अणु
		current_rate = RATE_1M;
		लघु_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_11B);

		/* Get SignalField,ServiceField,Length */
		vnt_get_phy_field(priv, frame_size, current_rate,
				  PK_TYPE_11B, &लघु_head->ab);

		/* Get Duration and TimeStampOff */
		लघु_head->duration =
			cpu_to_le16((u16)s_uGetDataDuration(priv, DATADUR_B,
				    frame_size, PK_TYPE_11B, current_rate,
				    false, 0, 0, 1, AUTO_FB_NONE));

		लघु_head->समय_stamp_off =
			vnt_समय_stamp_off(priv, current_rate);
	पूर्ण

	लघु_head->fअगरo_ctl |= cpu_to_le16(FIFOCTL_GENINT);

	/* Copy Beacon */
	स_नकल(mgmt_hdr, skb->data, skb->len);

	/* समय stamp always 0 */
	mgmt_hdr->u.beacon.बारtamp = 0;

	info = IEEE80211_SKB_CB(skb);
	अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ) अणु
		काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)mgmt_hdr;

		hdr->duration_id = 0;
		hdr->seq_ctrl = cpu_to_le16(priv->wSeqCounter << 4);
	पूर्ण

	priv->wSeqCounter++;
	अगर (priv->wSeqCounter > 0x0fff)
		priv->wSeqCounter = 0;

	priv->wBCNBufLen = माप(*लघु_head) + skb->len;

	MACvSetCurrBCNTxDescAddr(priv->PortOffset, priv->tx_beacon_dma);

	MACvSetCurrBCNLength(priv->PortOffset, priv->wBCNBufLen);
	/* Set स्वतः Transmit on */
	MACvRegBitsOn(priv->PortOffset, MAC_REG_TCR, TCR_AUTOBCNTX);
	/* Poll Transmit the adapter */
	MACvTransmitBCN(priv->PortOffset);

	वापस 0;
पूर्ण

पूर्णांक vnt_beacon_make(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *beacon;

	beacon = ieee80211_beacon_get(priv->hw, vअगर);
	अगर (!beacon)
		वापस -ENOMEM;

	अगर (vnt_beacon_xmit(priv, beacon)) अणु
		ieee80211_मुक्त_txskb(priv->hw, beacon);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vnt_beacon_enable(काष्ठा vnt_निजी *priv, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_bss_conf *conf)
अणु
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);

	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	CARDvSetFirstNextTBTT(priv, conf->beacon_पूर्णांक);

	CARDbSetBeaconPeriod(priv, conf->beacon_पूर्णांक);

	वापस vnt_beacon_make(priv, vअगर);
पूर्ण
