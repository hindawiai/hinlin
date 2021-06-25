<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

#घोषणा READ_AND_CONFIG     READ_AND_CONFIG_MP

#घोषणा READ_AND_CONFIG_MP(ic, txt) (ODM_ReadAndConfig##txt##ic(dm_odm))
#घोषणा READ_AND_CONFIG_TC(ic, txt) (ODM_ReadAndConfig_TC##txt##ic(dm_odm))

अटल u8 odm_query_rxpwrpercentage(s8 antघातer)
अणु
	अगर ((antघातer <= -100) || (antघातer >= 20))
		वापस 0;
	अन्यथा अगर (antघातer >= 0)
		वापस 100;
	अन्यथा
		वापस 100 + antघातer;
पूर्ण

/*  2012/01/12 MH MOve some संकेत strength smooth method to MP HAL layer. */
/*  IF other SW team करो not support the feature, हटाओ this section.?? */
अटल s32 odm_संकेत_scale_mapping(काष्ठा odm_dm_काष्ठा *dm_odm, s32 currsig)
अणु
	s32 retsig = 0;

	अगर (currsig >= 51 && currsig <= 100)
		retsig = 100;
	अन्यथा अगर (currsig >= 41 && currsig <= 50)
		retsig = 80 + ((currsig - 40) * 2);
	अन्यथा अगर (currsig >= 31 && currsig <= 40)
		retsig = 66 + (currsig - 30);
	अन्यथा अगर (currsig >= 21 && currsig <= 30)
		retsig = 54 + (currsig - 20);
	अन्यथा अगर (currsig >= 10 && currsig <= 20)
		retsig = 42 + (((currsig - 10) * 2) / 3);
	अन्यथा अगर (currsig >= 5 && currsig <= 9)
		retsig = 22 + (((currsig - 5) * 3) / 2);
	अन्यथा अगर (currsig >= 1 && currsig <= 4)
		retsig = 6 + (((currsig - 1) * 3) / 2);
	अन्यथा
		retsig = currsig;

	वापस retsig;
पूर्ण

अटल u8 odm_evm_db_to_percentage(s8 value)
अणु
	/*  -33dB~0dB to 0%~99% */
	s8 ret_val = clamp(-value, 0, 33) * 3;

	अगर (ret_val == 99)
		ret_val = 100;

	वापस ret_val;
पूर्ण

अटल व्योम odm_RxPhyStatus92CSeries_Parsing(काष्ठा odm_dm_काष्ठा *dm_odm,
			काष्ठा odm_phy_status_info *pPhyInfo,
			u8 *pPhyStatus,
			काष्ठा odm_per_pkt_info *pPktinfo)
अणु
	काष्ठा sw_ant_चयन *pDM_SWAT_Table = &dm_odm->DM_SWAT_Table;
	u8 i, max_spatial_stream;
	s8 rx_pwr[4], rx_pwr_all = 0;
	u8 EVM, PWDB_ALL = 0, PWDB_ALL_BT;
	u8 RSSI, total_rssi = 0;
	bool is_cck_rate;
	u8 rf_rx_num = 0;
	u8 cck_highpwr = 0;
	u8 LNA_idx, VGA_idx;

	काष्ठा phy_status_rpt *pPhyStaRpt = (काष्ठा phy_status_rpt *)pPhyStatus;

	is_cck_rate = pPktinfo->Rate >= DESC92C_RATE1M &&
		      pPktinfo->Rate <= DESC92C_RATE11M;

	pPhyInfo->RxMIMOSignalQuality[RF_PATH_A] = -1;
	pPhyInfo->RxMIMOSignalQuality[RF_PATH_B] = -1;

	अगर (is_cck_rate) अणु
		u8 cck_agc_rpt;

		dm_odm->PhyDbgInfo.NumQryPhyStatusCCK++;
		/*  (1)Hardware करोes not provide RSSI क्रम CCK */
		/*  (2)PWDB, Average PWDB calculated by hardware (क्रम rate adaptive) */

		cck_highpwr = dm_odm->bCckHighPower;

		cck_agc_rpt =  pPhyStaRpt->cck_agc_rpt_ofdm_cfosho_a;

		/* 2011.11.28 LukeLee: 88E use dअगरferent LNA & VGA gain table */
		/* The RSSI क्रमmula should be modअगरied according to the gain table */
		/* In 88E, cck_highpwr is always set to 1 */
		LNA_idx = (cck_agc_rpt & 0xE0) >> 5;
		VGA_idx = cck_agc_rpt & 0x1F;
		चयन (LNA_idx) अणु
		हाल 7:
			अगर (VGA_idx <= 27)
				rx_pwr_all = -100 + 2 * (27 - VGA_idx); /* VGA_idx = 27~2 */
			अन्यथा
				rx_pwr_all = -100;
			अवरोध;
		हाल 6:
			rx_pwr_all = -48 + 2 * (2 - VGA_idx); /* VGA_idx = 2~0 */
			अवरोध;
		हाल 5:
			rx_pwr_all = -42 + 2 * (7 - VGA_idx); /* VGA_idx = 7~5 */
			अवरोध;
		हाल 4:
			rx_pwr_all = -36 + 2 * (7 - VGA_idx); /* VGA_idx = 7~4 */
			अवरोध;
		हाल 3:
			rx_pwr_all = -24 + 2 * (7 - VGA_idx); /* VGA_idx = 7~0 */
			अवरोध;
		हाल 2:
			अगर (cck_highpwr)
				rx_pwr_all = -12 + 2 * (5 - VGA_idx); /* VGA_idx = 5~0 */
			अन्यथा
				rx_pwr_all = -6 + 2 * (5 - VGA_idx);
			अवरोध;
		हाल 1:
			rx_pwr_all = 8 - 2 * VGA_idx;
			अवरोध;
		हाल 0:
			rx_pwr_all = 14 - 2 * VGA_idx;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		rx_pwr_all += 6;
		PWDB_ALL = odm_query_rxpwrpercentage(rx_pwr_all);
		अगर (!cck_highpwr) अणु
			अगर (PWDB_ALL >= 80)
				PWDB_ALL = ((PWDB_ALL - 80) << 1) + ((PWDB_ALL - 80) >> 1) + 80;
			अन्यथा अगर ((PWDB_ALL <= 78) && (PWDB_ALL >= 20))
				PWDB_ALL += 3;
			अगर (PWDB_ALL > 100)
				PWDB_ALL = 100;
		पूर्ण

		pPhyInfo->RxPWDBAll = PWDB_ALL;
		pPhyInfo->BTRxRSSIPercentage = PWDB_ALL;
		pPhyInfo->RecvSignalPower = rx_pwr_all;
		/*  (3) Get Signal Quality (EVM) */
		अगर (pPktinfo->bPacketMatchBSSID) अणु
			u8 SQ, SQ_rpt;

			अगर (pPhyInfo->RxPWDBAll > 40 && !dm_odm->bInHctTest) अणु
				SQ = 100;
			पूर्ण अन्यथा अणु
				SQ_rpt = pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all;

				अगर (SQ_rpt > 64)
					SQ = 0;
				अन्यथा अगर (SQ_rpt < 20)
					SQ = 100;
				अन्यथा
					SQ = ((64 - SQ_rpt) * 100) / 44;
			पूर्ण
			pPhyInfo->SignalQuality = SQ;
			pPhyInfo->RxMIMOSignalQuality[RF_PATH_A] = SQ;
			pPhyInfo->RxMIMOSignalQuality[RF_PATH_B] = -1;
		पूर्ण
	पूर्ण अन्यथा अणु /* is OFDM rate */
		dm_odm->PhyDbgInfo.NumQryPhyStatusOFDM++;

		/*  (1)Get RSSI क्रम HT rate */

		क्रम (i = RF_PATH_A; i < RF_PATH_MAX; i++) अणु
			/*  2008/01/30 MH we will judge RF RX path now. */
			अगर (dm_odm->RFPathRxEnable & BIT(i))
				rf_rx_num++;

			rx_pwr[i] = ((pPhyStaRpt->path_agc[i].gain & 0x3F) * 2) - 110;

			pPhyInfo->RxPwr[i] = rx_pwr[i];

			/* Translate DBM to percentage. */
			RSSI = odm_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += RSSI;

			/* Modअगरication क्रम ext-LNA board */
			अगर (dm_odm->BoardType == ODM_BOARD_HIGHPWR) अणु
				अगर ((pPhyStaRpt->path_agc[i].trsw) == 1)
					RSSI = (RSSI > 94) ? 100 : (RSSI + 6);
				अन्यथा
					RSSI = (RSSI <= 16) ? (RSSI >> 3) : (RSSI - 16);

				अगर ((RSSI <= 34) && (RSSI >= 4))
					RSSI -= 4;
			पूर्ण

			pPhyInfo->RxMIMOSignalStrength[i] = (u8)RSSI;

			/* Get Rx snr value in DB */
			pPhyInfo->RxSNR[i] = (s32)(pPhyStaRpt->path_rxsnr[i] / 2);
			dm_odm->PhyDbgInfo.RxSNRdB[i] = (s32)(pPhyStaRpt->path_rxsnr[i] / 2);
		पूर्ण
		/*  (2)PWDB, Average PWDB calculated by hardware (क्रम rate adaptive) */
		rx_pwr_all = (((pPhyStaRpt->cck_sig_qual_ofdm_pwdb_all) >> 1) & 0x7f) - 110;

		PWDB_ALL = odm_query_rxpwrpercentage(rx_pwr_all);
		PWDB_ALL_BT = PWDB_ALL;

		pPhyInfo->RxPWDBAll = PWDB_ALL;
		pPhyInfo->BTRxRSSIPercentage = PWDB_ALL_BT;
		pPhyInfo->RxPower = rx_pwr_all;
		pPhyInfo->RecvSignalPower = rx_pwr_all;

		/*  (3)EVM of HT rate */
		अगर (pPktinfo->Rate >= DESC92C_RATEMCS8 && pPktinfo->Rate <= DESC92C_RATEMCS15)
			max_spatial_stream = 2; /* both spatial stream make sense */
		अन्यथा
			max_spatial_stream = 1; /* only spatial stream 1 makes sense */

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			/*  Do not use shअगरt operation like "rx_evmX >>= 1" because the compilor of मुक्त build environment */
			/*  fill most signअगरicant bit to "zero" when करोing shअगरting operation which may change a negative */
			/*  value to positive one, then the dbm value (which is supposed to be negative)  is not correct anymore. */
			EVM = odm_evm_db_to_percentage((pPhyStaRpt->stream_rxevm[i]));	/* dbm */

			अगर (pPktinfo->bPacketMatchBSSID) अणु
				अगर (i == RF_PATH_A) /*  Fill value in RFD, Get the first spatial stream only */
					pPhyInfo->SignalQuality = (u8)(EVM & 0xff);
				pPhyInfo->RxMIMOSignalQuality[i] = (u8)(EVM & 0xff);
			पूर्ण
		पूर्ण
	पूर्ण
	/* UI BSS List संकेत strength(in percentage), make it good looking, from 0~100. */
	/* It is asचिन्हित to the BSS List in GetValueFromBeaconOrProbeRsp(). */
	अगर (is_cck_rate) अणु
		pPhyInfo->SignalStrength = (u8)(odm_संकेत_scale_mapping(dm_odm, PWDB_ALL));/* PWDB_ALL; */
	पूर्ण अन्यथा अणु
		अगर (rf_rx_num != 0)
			pPhyInfo->SignalStrength = (u8)(odm_संकेत_scale_mapping(dm_odm, total_rssi /= rf_rx_num));
	पूर्ण

	/* For 92C/92D HW (Hybrid) Antenna Diversity */
	pDM_SWAT_Table->antsel = pPhyStaRpt->ant_sel;
	/* For 88E HW Antenna Diversity */
	dm_odm->DM_FatTable.antsel_rx_keep_0 = pPhyStaRpt->ant_sel;
	dm_odm->DM_FatTable.antsel_rx_keep_1 = pPhyStaRpt->ant_sel_b;
	dm_odm->DM_FatTable.antsel_rx_keep_2 = pPhyStaRpt->antsel_rx_keep_2;
पूर्ण

अटल व्योम odm_Process_RSSIForDM(काष्ठा odm_dm_काष्ठा *dm_odm,
				  काष्ठा odm_phy_status_info *pPhyInfo,
				  काष्ठा odm_per_pkt_info *pPktinfo)
अणु
	s32 UndecoratedSmoothedPWDB, UndecoratedSmoothedCCK;
	s32 UndecoratedSmoothedOFDM, RSSI_Ave;
	bool is_cck_rate;
	u8 RSSI_max, RSSI_min, i;
	u32 OFDM_pkt = 0;
	u32 Weighting = 0;
	काष्ठा sta_info *pEntry;
	u8 antsel_tr_mux;
	काष्ठा fast_ant_train *pDM_FatTable = &dm_odm->DM_FatTable;

	अगर (pPktinfo->StationID == 0xFF)
		वापस;
	pEntry = dm_odm->pODM_StaInfo[pPktinfo->StationID];
	अगर (!IS_STA_VALID(pEntry))
		वापस;
	अगर ((!pPktinfo->bPacketMatchBSSID))
		वापस;

	is_cck_rate = pPktinfo->Rate >= DESC92C_RATE1M &&
		      pPktinfo->Rate <= DESC92C_RATE11M;

	/* Smart Antenna Debug Message------------------  */

	अगर (dm_odm->AntDivType == CG_TRX_SMART_ANTDIV) अणु
		अगर (pDM_FatTable->FAT_State == FAT_TRAINING_STATE) अणु
			अगर (pPktinfo->bPacketToSelf) अणु
				antsel_tr_mux = (pDM_FatTable->antsel_rx_keep_2 << 2) |
						(pDM_FatTable->antsel_rx_keep_1 << 1) |
						pDM_FatTable->antsel_rx_keep_0;
				pDM_FatTable->antSumRSSI[antsel_tr_mux] += pPhyInfo->RxPWDBAll;
				pDM_FatTable->antRSSIcnt[antsel_tr_mux]++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर ((dm_odm->AntDivType == CG_TRX_HW_ANTDIV) || (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV)) अणु
		अगर (pPktinfo->bPacketToSelf || pPktinfo->bPacketBeacon) अणु
			antsel_tr_mux = (pDM_FatTable->antsel_rx_keep_2 << 2) |
					(pDM_FatTable->antsel_rx_keep_1 << 1) | pDM_FatTable->antsel_rx_keep_0;
			rtl88eu_dm_ant_sel_statistics(dm_odm, antsel_tr_mux, pPktinfo->StationID, pPhyInfo->RxPWDBAll);
		पूर्ण
	पूर्ण
	/* Smart Antenna Debug Message------------------ */

	UndecoratedSmoothedCCK =  pEntry->rssi_stat.UndecoratedSmoothedCCK;
	UndecoratedSmoothedOFDM = pEntry->rssi_stat.UndecoratedSmoothedOFDM;
	UndecoratedSmoothedPWDB = pEntry->rssi_stat.UndecoratedSmoothedPWDB;

	अगर (pPktinfo->bPacketToSelf || pPktinfo->bPacketBeacon) अणु
		अगर (!is_cck_rate) अणु /* ofdm rate */
			अगर (pPhyInfo->RxMIMOSignalStrength[RF_PATH_B] == 0) अणु
				RSSI_Ave = pPhyInfo->RxMIMOSignalStrength[RF_PATH_A];
			पूर्ण अन्यथा अणु
				अगर (pPhyInfo->RxMIMOSignalStrength[RF_PATH_A] > pPhyInfo->RxMIMOSignalStrength[RF_PATH_B]) अणु
					RSSI_max = pPhyInfo->RxMIMOSignalStrength[RF_PATH_A];
					RSSI_min = pPhyInfo->RxMIMOSignalStrength[RF_PATH_B];
				पूर्ण अन्यथा अणु
					RSSI_max = pPhyInfo->RxMIMOSignalStrength[RF_PATH_B];
					RSSI_min = pPhyInfo->RxMIMOSignalStrength[RF_PATH_A];
				पूर्ण
				अगर ((RSSI_max - RSSI_min) < 3)
					RSSI_Ave = RSSI_max;
				अन्यथा अगर ((RSSI_max - RSSI_min) < 6)
					RSSI_Ave = RSSI_max - 1;
				अन्यथा अगर ((RSSI_max - RSSI_min) < 10)
					RSSI_Ave = RSSI_max - 2;
				अन्यथा
					RSSI_Ave = RSSI_max - 3;
			पूर्ण

			/* 1 Process OFDM RSSI */
			अगर (UndecoratedSmoothedOFDM <= 0) अणु	/*  initialize */
				UndecoratedSmoothedOFDM = pPhyInfo->RxPWDBAll;
			पूर्ण अन्यथा अणु
				अगर (pPhyInfo->RxPWDBAll > (u32)UndecoratedSmoothedOFDM) अणु
					UndecoratedSmoothedOFDM =
							(((UndecoratedSmoothedOFDM) * (Rx_Smooth_Factor - 1)) +
							(RSSI_Ave)) / (Rx_Smooth_Factor);
					UndecoratedSmoothedOFDM = UndecoratedSmoothedOFDM + 1;
				पूर्ण अन्यथा अणु
					UndecoratedSmoothedOFDM =
							(((UndecoratedSmoothedOFDM) * (Rx_Smooth_Factor - 1)) +
							(RSSI_Ave)) / (Rx_Smooth_Factor);
				पूर्ण
			पूर्ण

			pEntry->rssi_stat.PacketMap = (pEntry->rssi_stat.PacketMap << 1) | BIT(0);

		पूर्ण अन्यथा अणु
			RSSI_Ave = pPhyInfo->RxPWDBAll;

			/* 1 Process CCK RSSI */
			अगर (UndecoratedSmoothedCCK <= 0) अणु	/*  initialize */
				UndecoratedSmoothedCCK = pPhyInfo->RxPWDBAll;
			पूर्ण अन्यथा अणु
				अगर (pPhyInfo->RxPWDBAll > (u32)UndecoratedSmoothedCCK) अणु
					UndecoratedSmoothedCCK =
							((UndecoratedSmoothedCCK * (Rx_Smooth_Factor - 1)) +
							pPhyInfo->RxPWDBAll) / Rx_Smooth_Factor;
					UndecoratedSmoothedCCK = UndecoratedSmoothedCCK + 1;
				पूर्ण अन्यथा अणु
					UndecoratedSmoothedCCK =
							((UndecoratedSmoothedCCK * (Rx_Smooth_Factor - 1)) +
							pPhyInfo->RxPWDBAll) / Rx_Smooth_Factor;
				पूर्ण
			पूर्ण
			pEntry->rssi_stat.PacketMap = pEntry->rssi_stat.PacketMap << 1;
		पूर्ण
		/* 2011.07.28 LukeLee: modअगरied to prevent unstable CCK RSSI */
		अगर (pEntry->rssi_stat.ValidBit >= 64)
			pEntry->rssi_stat.ValidBit = 64;
		अन्यथा
			pEntry->rssi_stat.ValidBit++;

		क्रम (i = 0; i < pEntry->rssi_stat.ValidBit; i++)
			OFDM_pkt += (u8)(pEntry->rssi_stat.PacketMap >> i) & BIT(0);

		अगर (pEntry->rssi_stat.ValidBit == 64) अणु
			Weighting = min_t(u32, OFDM_pkt << 4, 64);
			UndecoratedSmoothedPWDB = (Weighting * UndecoratedSmoothedOFDM + (64 - Weighting) * UndecoratedSmoothedCCK) >> 6;
		पूर्ण अन्यथा अणु
			अगर (pEntry->rssi_stat.ValidBit != 0)
				UndecoratedSmoothedPWDB = (OFDM_pkt * UndecoratedSmoothedOFDM +
							  (pEntry->rssi_stat.ValidBit - OFDM_pkt) *
							  UndecoratedSmoothedCCK) / pEntry->rssi_stat.ValidBit;
			अन्यथा
				UndecoratedSmoothedPWDB = 0;
		पूर्ण
		pEntry->rssi_stat.UndecoratedSmoothedCCK = UndecoratedSmoothedCCK;
		pEntry->rssi_stat.UndecoratedSmoothedOFDM = UndecoratedSmoothedOFDM;
		pEntry->rssi_stat.UndecoratedSmoothedPWDB = UndecoratedSmoothedPWDB;
	पूर्ण
पूर्ण

/*  Endianness beक्रमe calling this API */
व्योम odm_phy_status_query(काष्ठा odm_dm_काष्ठा *dm_odm,
			  काष्ठा odm_phy_status_info *phy_info,
			  u8 *phy_status, काष्ठा odm_per_pkt_info *pkt_info)
अणु
	odm_RxPhyStatus92CSeries_Parsing(dm_odm, phy_info, phy_status, pkt_info);
	अगर (dm_odm->RSSI_test)
		;/*  Select the packets to करो RSSI checking क्रम antenna चयनing. */
	अन्यथा
		odm_Process_RSSIForDM(dm_odm, phy_info, pkt_info);
पूर्ण
