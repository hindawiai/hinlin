<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

#घोषणा READ_AND_CONFIG_MP(ic, txt) (ODM_ReadAndConfig_MP_##ic##txt(pDM_Odm))
#घोषणा READ_AND_CONFIG     READ_AND_CONFIG_MP
#घोषणा GET_VERSION_MP(ic, txt) (ODM_GetVersion_MP_##ic##txt())
#घोषणा GET_VERSION(ic, txt) (pDM_Odm->bIsMPChip?GET_VERSION_MP(ic, txt):GET_VERSION_TC(ic, txt))

अटल u8 odm_QueryRxPwrPercentage(s8 AntPower)
अणु
	अगर ((AntPower <= -100) || (AntPower >= 20))
		वापस	0;
	अन्यथा अगर (AntPower >= 0)
		वापस	100;
	अन्यथा
		वापस 100 + AntPower;

पूर्ण

s32 odm_SignalScaleMapping(काष्ठा dm_odm_t *pDM_Odm, s32 CurrSig)
अणु
	s32 RetSig = 0;

	अगर (pDM_Odm->SupportInterface  == ODM_ITRF_SDIO) अणु
		अगर (CurrSig >= 51 && CurrSig <= 100)
			RetSig = 100;
		अन्यथा अगर (CurrSig >= 41 && CurrSig <= 50)
			RetSig = 80 + ((CurrSig - 40)*2);
		अन्यथा अगर (CurrSig >= 31 && CurrSig <= 40)
			RetSig = 66 + (CurrSig - 30);
		अन्यथा अगर (CurrSig >= 21 && CurrSig <= 30)
			RetSig = 54 + (CurrSig - 20);
		अन्यथा अगर (CurrSig >= 10 && CurrSig <= 20)
			RetSig = 42 + (((CurrSig - 10) * 2) / 3);
		अन्यथा अगर (CurrSig >= 5 && CurrSig <= 9)
			RetSig = 22 + (((CurrSig - 5) * 3) / 2);
		अन्यथा अगर (CurrSig >= 1 && CurrSig <= 4)
			RetSig = 6 + (((CurrSig - 1) * 3) / 2);
		अन्यथा
			RetSig = CurrSig;
	पूर्ण

	वापस RetSig;
पूर्ण

अटल u8 odm_EVMdbToPercentage(s8 Value)
अणु
	/*  */
	/*  -33dB~0dB to 0%~99% */
	/*  */
	s8 ret_val;

	ret_val = Value;
	ret_val /= 2;

	/* DbgPrपूर्णांक("Value =%d\n", Value); */
	/* ODM_RT_DISP(FRX, RX_PHY_SQ, ("EVMdbToPercentage92C Value =%d / %x\n", ret_val, ret_val)); */

	अगर (ret_val >= 0)
		ret_val = 0;
	अगर (ret_val <= -33)
		ret_val = -33;

	ret_val = 0 - ret_val;
	ret_val *= 3;

	अगर (ret_val == 99)
		ret_val = 100;

	वापस ret_val;
पूर्ण

अटल व्योम odm_RxPhyStatus92CSeries_Parsing(
	काष्ठा dm_odm_t *pDM_Odm,
	काष्ठा odm_phy_info *pPhyInfo,
	u8 *pPhyStatus,
	काष्ठा odm_packet_info *pPktinfo
)
अणु
	u8 i, Max_spatial_stream;
	s8 rx_pwr[4], rx_pwr_all = 0;
	u8 EVM, PWDB_ALL = 0, PWDB_ALL_BT;
	u8 RSSI, total_rssi = 0;
	bool isCCKrate = false;
	u8 rf_rx_num = 0;
	u8 LNA_idx, VGA_idx;
	काष्ठा phy_status_rpt_8192cd_t *pPhyStaRpt = (काष्ठा phy_status_rpt_8192cd_t *)pPhyStatus;

	isCCKrate = pPktinfo->data_rate <= DESC_RATE11M;
	pPhyInfo->rx_mimo_संकेत_quality[ODM_RF_PATH_A] = -1;
	pPhyInfo->rx_mimo_संकेत_quality[ODM_RF_PATH_B] = -1;


	अगर (isCCKrate) अणु
		u8 cck_agc_rpt;

		pDM_Odm->PhyDbgInfo.NumQryPhyStatusCCK++;
		/*  */
		/*  (1)Hardware करोes not provide RSSI क्रम CCK */
		/*  (2)PWDB, Average PWDB calculated by hardware (क्रम rate adaptive) */
		/*  */

		cck_agc_rpt = pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a;

		/* 2011.11.28 LukeLee: 88E use dअगरferent LNA & VGA gain table */
		/* The RSSI क्रमmula should be modअगरied according to the gain table */
		LNA_idx = ((cck_agc_rpt & 0xE0)>>5);
		VGA_idx = (cck_agc_rpt & 0x1F);
		rx_pwr_all = odm_CCKRSSI_8723B(LNA_idx, VGA_idx);
		PWDB_ALL = odm_QueryRxPwrPercentage(rx_pwr_all);
		अगर (PWDB_ALL > 100)
			PWDB_ALL = 100;

		pPhyInfo->rx_pwd_ba11 = PWDB_ALL;
		pPhyInfo->bt_rx_rssi_percentage = PWDB_ALL;
		pPhyInfo->recv_संकेत_घातer = rx_pwr_all;
		/*  */
		/*  (3) Get Signal Quality (EVM) */
		/*  */
		/* अगर (pPktinfo->bPacketMatchBSSID) */
		अणु
			u8 SQ, SQ_rpt;

			अगर (pPhyInfo->rx_pwd_ba11 > 40 && !pDM_Odm->bInHctTest)
				SQ = 100;
			अन्यथा अणु
				SQ_rpt = pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all;

				अगर (SQ_rpt > 64)
					SQ = 0;
				अन्यथा अगर (SQ_rpt < 20)
					SQ = 100;
				अन्यथा
					SQ = ((64-SQ_rpt) * 100) / 44;

			पूर्ण

			/* DbgPrपूर्णांक("cck SQ = %d\n", SQ); */
			pPhyInfo->संकेत_quality = SQ;
			pPhyInfo->rx_mimo_संकेत_quality[ODM_RF_PATH_A] = SQ;
			pPhyInfo->rx_mimo_संकेत_quality[ODM_RF_PATH_B] = -1;
		पूर्ण
	पूर्ण अन्यथा अणु /* is OFDM rate */
		pDM_Odm->PhyDbgInfo.NumQryPhyStatusOFDM++;

		/*  */
		/*  (1)Get RSSI क्रम HT rate */
		/*  */

		क्रम (i = ODM_RF_PATH_A; i < ODM_RF_PATH_MAX; i++) अणु
			/*  2008/01/30 MH we will judge RF RX path now. */
			अगर (pDM_Odm->RFPathRxEnable & BIT(i))
				rf_rx_num++;
			/* अन्यथा */
				/* जारी; */

			rx_pwr[i] = ((pPhyStaRpt->path_agc[i].gain&0x3F)*2) - 110;


			pPhyInfo->rx_pwr[i] = rx_pwr[i];

			/* Translate DBM to percentage. */
			RSSI = odm_QueryRxPwrPercentage(rx_pwr[i]);
			total_rssi += RSSI;
			/* RT_DISP(FRX, RX_PHY_SS, ("RF-%d RXPWR =%x RSSI =%d\n", i, rx_pwr[i], RSSI)); */

			pPhyInfo->rx_mimo_संकेत_strength[i] = (u8) RSSI;

			/* Get Rx snr value in DB */
			pPhyInfo->rx_snr[i] = pDM_Odm->PhyDbgInfo.RxSNRdB[i] = (s32)(pPhyStaRpt->path_rxsnr[i]/2);
		पूर्ण


		/*  */
		/*  (2)PWDB, Average PWDB calculated by hardware (क्रम rate adaptive) */
		/*  */
		rx_pwr_all = (((pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all) >> 1)&0x7f)-110;

		PWDB_ALL_BT = PWDB_ALL = odm_QueryRxPwrPercentage(rx_pwr_all);
		/* RT_DISP(FRX, RX_PHY_SS, ("PWDB_ALL =%d\n", PWDB_ALL)); */

		pPhyInfo->rx_pwd_ba11 = PWDB_ALL;
		/* ODM_RT_TRACE(pDM_Odm, ODM_COMP_RSSI_MONITOR, ODM_DBG_LOUD, ("ODM OFDM RSSI =%d\n", pPhyInfo->rx_pwd_ba11)); */
		pPhyInfo->bt_rx_rssi_percentage = PWDB_ALL_BT;
		pPhyInfo->rx_घातer = rx_pwr_all;
		pPhyInfo->recv_संकेत_घातer = rx_pwr_all;

		अणु/* pMgntInfo->CustomerID != RT_CID_819x_Lenovo */
			/*  */
			/*  (3)EVM of HT rate */
			/*  */
			अगर (pPktinfo->data_rate >= DESC_RATEMCS8 && pPktinfo->data_rate <= DESC_RATEMCS15)
				Max_spatial_stream = 2; /* both spatial stream make sense */
			अन्यथा
				Max_spatial_stream = 1; /* only spatial stream 1 makes sense */

			क्रम (i = 0; i < Max_spatial_stream; i++) अणु
				/*  Do not use shअगरt operation like "rx_evmX >>= 1" because the compilor of मुक्त build environment */
				/*  fill most signअगरicant bit to "zero" when करोing shअगरting operation which may change a negative */
				/*  value to positive one, then the dbm value (which is supposed to be negative)  is not correct anymore. */
				EVM = odm_EVMdbToPercentage((pPhyStaRpt->stream_rxevm[i]));	/* dbm */

				/* RT_DISP(FRX, RX_PHY_SQ, ("RXRATE =%x RXEVM =%x EVM =%s%d\n", */
				/* GET_RX_STATUS_DESC_RX_MCS(pDesc), pDrvInfo->rxevm[i], "%", EVM)); */

				/* अगर (pPktinfo->bPacketMatchBSSID) */
				अणु
					अगर (i == ODM_RF_PATH_A) /*  Fill value in RFD, Get the first spatial stream only */
						pPhyInfo->संकेत_quality = (u8)(EVM & 0xff);

					pPhyInfo->rx_mimo_संकेत_quality[i] = (u8)(EVM & 0xff);
				पूर्ण
			पूर्ण
		पूर्ण

		ODM_ParsingCFO(pDM_Odm, pPktinfo, pPhyStaRpt->path_cfotail);

	पूर्ण

	/* UI BSS List संकेत strength(in percentage), make it good looking, from 0~100. */
	/* It is asचिन्हित to the BSS List in GetValueFromBeaconOrProbeRsp(). */
	अगर (isCCKrate) अणु
		pPhyInfo->संकेत_strength = (u8)(odm_SignalScaleMapping(pDM_Odm, PWDB_ALL));/* PWDB_ALL; */
	पूर्ण अन्यथा अणु
		अगर (rf_rx_num != 0) अणु
			pPhyInfo->संकेत_strength = (u8)(odm_SignalScaleMapping(pDM_Odm, total_rssi /= rf_rx_num));
		पूर्ण
	पूर्ण

	/* DbgPrपूर्णांक("isCCKrate = %d, pPhyInfo->rx_pwd_ba11 = %d, pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a = 0x%x\n", */
		/* isCCKrate, pPhyInfo->rx_pwd_ba11, pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a); */
पूर्ण

अटल व्योम odm_Process_RSSIForDM(
	काष्ठा dm_odm_t *pDM_Odm, काष्ठा odm_phy_info *pPhyInfo, काष्ठा odm_packet_info *pPktinfo
)
अणु

	s32 UndecoratedSmoothedPWDB, UndecoratedSmoothedCCK, UndecoratedSmoothedOFDM, RSSI_Ave;
	u8 isCCKrate = 0;
	u8 RSSI_max, RSSI_min, i;
	u32 OFDM_pkt = 0;
	u32 Weighting = 0;
	PSTA_INFO_T pEntry;


	अगर (pPktinfo->station_id == 0xFF)
		वापस;

	pEntry = pDM_Odm->pODM_StaInfo[pPktinfo->station_id];

	अगर (!IS_STA_VALID(pEntry))
		वापस;

	अगर ((!pPktinfo->bssid_match))
		वापस;

	अगर (pPktinfo->is_beacon)
		pDM_Odm->PhyDbgInfo.NumQryBeaconPkt++;

	isCCKrate = ((pPktinfo->data_rate <= DESC_RATE11M)) ? true : false;
	pDM_Odm->RxRate = pPktinfo->data_rate;

	/* Statistic क्रम antenna/path भागersity------------------ */
	अगर (pDM_Odm->SupportAbility & ODM_BB_ANT_DIV) अणु

	पूर्ण

	/* Smart Antenna Debug Message------------------ */

	UndecoratedSmoothedCCK = pEntry->rssi_stat.UndecoratedSmoothedCCK;
	UndecoratedSmoothedOFDM = pEntry->rssi_stat.UndecoratedSmoothedOFDM;
	UndecoratedSmoothedPWDB = pEntry->rssi_stat.UndecoratedSmoothedPWDB;

	अगर (pPktinfo->to_self || pPktinfo->is_beacon) अणु

		अगर (!isCCKrate) अणु /* ofdm rate */
			अगर (pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_B] == 0) अणु
				RSSI_Ave = pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_A];
				pDM_Odm->RSSI_A = pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_A];
				pDM_Odm->RSSI_B = 0;
			पूर्ण अन्यथा अणु
				/* DbgPrपूर्णांक("pRfd->Status.rx_mimo_signal_strength[0] = %d, pRfd->Status.rx_mimo_signal_strength[1] = %d\n", */
					/* pRfd->Status.rx_mimo_संकेत_strength[0], pRfd->Status.rx_mimo_संकेत_strength[1]); */
				pDM_Odm->RSSI_A =  pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_A];
				pDM_Odm->RSSI_B = pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_B];

				अगर (
					pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_A] >
					pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_B]
				) अणु
					RSSI_max = pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_A];
					RSSI_min = pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_B];
				पूर्ण अन्यथा अणु
					RSSI_max = pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_B];
					RSSI_min = pPhyInfo->rx_mimo_संकेत_strength[ODM_RF_PATH_A];
				पूर्ण

				अगर ((RSSI_max-RSSI_min) < 3)
					RSSI_Ave = RSSI_max;
				अन्यथा अगर ((RSSI_max-RSSI_min) < 6)
					RSSI_Ave = RSSI_max - 1;
				अन्यथा अगर ((RSSI_max-RSSI_min) < 10)
					RSSI_Ave = RSSI_max - 2;
				अन्यथा
					RSSI_Ave = RSSI_max - 3;
			पूर्ण

			/* 1 Process OFDM RSSI */
			अगर (UndecoratedSmoothedOFDM <= 0)	/*  initialize */
				UndecoratedSmoothedOFDM = pPhyInfo->rx_pwd_ba11;
			अन्यथा अणु
				अगर (pPhyInfo->rx_pwd_ba11 > (u32)UndecoratedSmoothedOFDM) अणु
					UndecoratedSmoothedOFDM =
							((UndecoratedSmoothedOFDM*(Rx_Smooth_Factor-1)) +
							RSSI_Ave)/Rx_Smooth_Factor;
					UndecoratedSmoothedOFDM = UndecoratedSmoothedOFDM + 1;
				पूर्ण अन्यथा अणु
					UndecoratedSmoothedOFDM =
							((UndecoratedSmoothedOFDM*(Rx_Smooth_Factor-1)) +
							RSSI_Ave)/Rx_Smooth_Factor;
				पूर्ण
			पूर्ण

			pEntry->rssi_stat.PacketMap = (pEntry->rssi_stat.PacketMap<<1) | BIT0;

		पूर्ण अन्यथा अणु
			RSSI_Ave = pPhyInfo->rx_pwd_ba11;
			pDM_Odm->RSSI_A = (u8) pPhyInfo->rx_pwd_ba11;
			pDM_Odm->RSSI_B = 0;

			/* 1 Process CCK RSSI */
			अगर (UndecoratedSmoothedCCK <= 0)	/*  initialize */
				UndecoratedSmoothedCCK = pPhyInfo->rx_pwd_ba11;
			अन्यथा अणु
				अगर (pPhyInfo->rx_pwd_ba11 > (u32)UndecoratedSmoothedCCK) अणु
					UndecoratedSmoothedCCK =
							((UndecoratedSmoothedCCK*(Rx_Smooth_Factor-1)) +
							pPhyInfo->rx_pwd_ba11)/Rx_Smooth_Factor;
					UndecoratedSmoothedCCK = UndecoratedSmoothedCCK + 1;
				पूर्ण अन्यथा अणु
					UndecoratedSmoothedCCK =
							((UndecoratedSmoothedCCK*(Rx_Smooth_Factor-1)) +
							pPhyInfo->rx_pwd_ba11)/Rx_Smooth_Factor;
				पूर्ण
			पूर्ण
			pEntry->rssi_stat.PacketMap = pEntry->rssi_stat.PacketMap<<1;
		पूर्ण

		/* अगर (pEntry) */
		अणु
			/* 2011.07.28 LukeLee: modअगरied to prevent unstable CCK RSSI */
			अगर (pEntry->rssi_stat.ValidBit >= 64)
				pEntry->rssi_stat.ValidBit = 64;
			अन्यथा
				pEntry->rssi_stat.ValidBit++;

			क्रम (i = 0; i < pEntry->rssi_stat.ValidBit; i++)
				OFDM_pkt += (u8)(pEntry->rssi_stat.PacketMap>>i)&BIT0;

			अगर (pEntry->rssi_stat.ValidBit == 64) अणु
				Weighting = ((OFDM_pkt<<4) > 64)?64:(OFDM_pkt<<4);
				UndecoratedSmoothedPWDB = (Weighting*UndecoratedSmoothedOFDM+(64-Weighting)*UndecoratedSmoothedCCK)>>6;
			पूर्ण अन्यथा अणु
				अगर (pEntry->rssi_stat.ValidBit != 0)
					UndecoratedSmoothedPWDB = (OFDM_pkt*UndecoratedSmoothedOFDM+(pEntry->rssi_stat.ValidBit-OFDM_pkt)*UndecoratedSmoothedCCK)/pEntry->rssi_stat.ValidBit;
				अन्यथा
					UndecoratedSmoothedPWDB = 0;
			पूर्ण

			pEntry->rssi_stat.UndecoratedSmoothedCCK = UndecoratedSmoothedCCK;
			pEntry->rssi_stat.UndecoratedSmoothedOFDM = UndecoratedSmoothedOFDM;
			pEntry->rssi_stat.UndecoratedSmoothedPWDB = UndecoratedSmoothedPWDB;

			/* DbgPrपूर्णांक("OFDM_pkt =%d, Weighting =%d\n", OFDM_pkt, Weighting); */
			/* DbgPrपूर्णांक("UndecoratedSmoothedOFDM =%d, UndecoratedSmoothedPWDB =%d, UndecoratedSmoothedCCK =%d\n", */
			/* UndecoratedSmoothedOFDM, UndecoratedSmoothedPWDB, UndecoratedSmoothedCCK); */

		पूर्ण

	पूर्ण
पूर्ण


/*  */
/*  Endianness beक्रमe calling this API */
/*  */
अटल व्योम ODM_PhyStatusQuery_92CSeries(
	काष्ठा dm_odm_t *pDM_Odm,
	काष्ठा odm_phy_info *pPhyInfo,
	u8 *pPhyStatus,
	काष्ठा odm_packet_info *pPktinfo
)
अणु

	odm_RxPhyStatus92CSeries_Parsing(pDM_Odm, pPhyInfo, pPhyStatus, pPktinfo);

	अगर (!pDM_Odm->RSSI_test)
		odm_Process_RSSIForDM(pDM_Odm, pPhyInfo, pPktinfo);
पूर्ण

व्योम ODM_PhyStatusQuery(
	काष्ठा dm_odm_t *pDM_Odm,
	काष्ठा odm_phy_info *pPhyInfo,
	u8 *pPhyStatus,
	काष्ठा odm_packet_info *pPktinfo
)
अणु

	ODM_PhyStatusQuery_92CSeries(pDM_Odm, pPhyInfo, pPhyStatus, pPktinfo);
पूर्ण

/*  */
/*  If you want to add a new IC, Please follow below ढाँचा and generate a new one. */
/*  */
/*  */

क्रमागत hal_status ODM_ConfigRFWithHeaderFile(
	काष्ठा dm_odm_t *pDM_Odm,
	क्रमागत ODM_RF_Config_Type ConfigType,
	क्रमागत odm_rf_radio_path_e eRFPath
)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD,
				("===>ODM_ConfigRFWithHeaderFile (%s)\n", (pDM_Odm->bIsMPChip) ? "MPChip" : "TestChip"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD,
				("pDM_Odm->SupportPlatform: 0x%X, pDM_Odm->SupportInterface: 0x%X, pDM_Odm->BoardType: 0x%X\n",
				pDM_Odm->SupportPlatक्रमm, pDM_Odm->SupportInterface, pDM_Odm->BoardType));

	अगर (ConfigType == CONFIG_RF_RADIO)
		READ_AND_CONFIG(8723B, _RadioA);
	अन्यथा अगर (ConfigType == CONFIG_RF_TXPWR_LMT)
		READ_AND_CONFIG(8723B, _TXPWR_LMT);

	वापस HAL_STATUS_SUCCESS;
पूर्ण

क्रमागत hal_status ODM_ConfigRFWithTxPwrTrackHeaderFile(काष्ठा dm_odm_t *pDM_Odm)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD,
				 ("===>ODM_ConfigRFWithTxPwrTrackHeaderFile (%s)\n", (pDM_Odm->bIsMPChip) ? "MPChip" : "TestChip"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD,
				 ("pDM_Odm->SupportPlatform: 0x%X, pDM_Odm->SupportInterface: 0x%X, pDM_Odm->BoardType: 0x%X\n",
				 pDM_Odm->SupportPlatक्रमm, pDM_Odm->SupportInterface, pDM_Odm->BoardType));

	अगर (pDM_Odm->SupportInterface == ODM_ITRF_SDIO)
		READ_AND_CONFIG(8723B, _TxPowerTrack_SDIO);

	वापस HAL_STATUS_SUCCESS;
पूर्ण

क्रमागत hal_status ODM_ConfigBBWithHeaderFile(
	काष्ठा dm_odm_t *pDM_Odm, क्रमागत ODM_BB_Config_Type ConfigType
)
अणु
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD,
				("===>ODM_ConfigBBWithHeaderFile (%s)\n", (pDM_Odm->bIsMPChip) ? "MPChip" : "TestChip"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD,
				("pDM_Odm->SupportPlatform: 0x%X, pDM_Odm->SupportInterface: 0x%X, pDM_Odm->BoardType: 0x%X\n",
				pDM_Odm->SupportPlatक्रमm, pDM_Odm->SupportInterface, pDM_Odm->BoardType));

	अगर (ConfigType == CONFIG_BB_PHY_REG)
		READ_AND_CONFIG(8723B, _PHY_REG);
	अन्यथा अगर (ConfigType == CONFIG_BB_AGC_TAB)
		READ_AND_CONFIG(8723B, _AGC_TAB);
	अन्यथा अगर (ConfigType == CONFIG_BB_PHY_REG_PG)
		READ_AND_CONFIG(8723B, _PHY_REG_PG);

	वापस HAL_STATUS_SUCCESS;
पूर्ण

