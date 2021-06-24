<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/


#अगर_अघोषित __HALHWOUTSRC_H__
#घोषणा __HALHWOUTSRC_H__


/*--------------------------Define -------------------------------------------*/
/* define READ_NEXT_PAIR(v1, v2, i) करो अणु i += 2; v1 = Array[i]; v2 = Array[i+1]; पूर्ण जबतक (0) */
#घोषणा AGC_DIFF_CONFIG_MP(ic, band) (ODM_ReadAndConfig_MP_##ic##_AGC_TAB_DIFF(pDM_Odm, Array_MP_##ic##_AGC_TAB_DIFF_##band, \
	माप(Array_MP_##ic##_AGC_TAB_DIFF_##band)/माप(u32)))
#घोषणा AGC_DIFF_CONFIG_TC(ic, band) (ODM_ReadAndConfig_TC_##ic##_AGC_TAB_DIFF(pDM_Odm, Array_TC_##ic##_AGC_TAB_DIFF_##band, \
	माप(Array_TC_##ic##_AGC_TAB_DIFF_##band)/माप(u32)))

#घोषणा AGC_DIFF_CONFIG(ic, band)\
	करो अणु\
		अगर (pDM_Odm->bIsMPChip)\
			AGC_DIFF_CONFIG_MP(ic, band);\
		अन्यथा\
			AGC_DIFF_CONFIG_TC(ic, band);\
	पूर्ण जबतक (0)


/*  */
/*  काष्ठाure and define */
/*  */

काष्ठा phy_rx_agc_info_t अणु
	#अगर (ODM_ENDIAN_TYPE == ODM_ENDIAN_LITTLE)
		u8 gain:7, trsw:1;
	#अन्यथा
		u8 trsw:1, gain:7;
	#पूर्ण_अगर
पूर्ण;

काष्ठा phy_status_rpt_8192cd_t अणु
	काष्ठा phy_rx_agc_info_t path_agc[2];
	u8 ch_corr[2];
	u8 cck_sig_qual_ofdm_pwdb_all;
	u8 cck_agc_rpt_ofdm_cfosho_a;
	u8 cck_rpt_b_ofdm_cfosho_b;
	u8 rsvd_1;/* ch_corr_msb; */
	u8 noise_घातer_db_msb;
	s8 path_cfotail[2];
	u8 pcts_mask[2];
	s8 stream_rxevm[2];
	u8 path_rxsnr[2];
	u8 noise_घातer_db_lsb;
	u8 rsvd_2[3];
	u8 stream_csi[2];
	u8 stream_target_csi[2];
	s8	sig_evm;
	u8 rsvd_3;

#अगर (ODM_ENDIAN_TYPE == ODM_ENDIAN_LITTLE)
	u8 antsel_rx_keep_2:1;	/* ex_पूर्णांकf_flg:1; */
	u8 sgi_en:1;
	u8 rxsc:2;
	u8 idle_दीर्घ:1;
	u8 r_ant_train_en:1;
	u8 ant_sel_b:1;
	u8 ant_sel:1;
#अन्यथा	/*  _BIG_ENDIAN_ */
	u8 ant_sel:1;
	u8 ant_sel_b:1;
	u8 r_ant_train_en:1;
	u8 idle_दीर्घ:1;
	u8 rxsc:2;
	u8 sgi_en:1;
	u8 antsel_rx_keep_2:1;	/* ex_पूर्णांकf_flg:1; */
#पूर्ण_अगर
पूर्ण;

व्योम ODM_PhyStatusQuery(
	काष्ठा dm_odm_t *pDM_Odm,
	काष्ठा odm_phy_info *pPhyInfo,
	u8 *pPhyStatus,
	काष्ठा odm_packet_info *pPktinfo
);

क्रमागत hal_status ODM_ConfigRFWithTxPwrTrackHeaderFile(काष्ठा dm_odm_t *pDM_Odm);

क्रमागत hal_status ODM_ConfigRFWithHeaderFile(
	काष्ठा dm_odm_t *pDM_Odm,
	क्रमागत ODM_RF_Config_Type ConfigType,
	क्रमागत odm_rf_radio_path_e eRFPath
);

क्रमागत hal_status ODM_ConfigBBWithHeaderFile(
	काष्ठा dm_odm_t *pDM_Odm, क्रमागत ODM_BB_Config_Type ConfigType
);

क्रमागत hal_status ODM_ConfigFWWithHeaderFile(
	काष्ठा dm_odm_t *pDM_Odm,
	क्रमागत ODM_FW_Config_Type ConfigType,
	u8 *pFirmware,
	u32 *pSize
);

s32 odm_SignalScaleMapping(काष्ठा dm_odm_t *pDM_Odm, s32 CurrSig);

#पूर्ण_अगर
