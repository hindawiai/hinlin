<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित	__HALHWOUTSRC_H__
#घोषणा __HALHWOUTSRC_H__

/*  Definition */
/*  CCK Rates, TxHT = 0 */
#घोषणा DESC92C_RATE1M				0x00
#घोषणा DESC92C_RATE2M				0x01
#घोषणा DESC92C_RATE5_5M			0x02
#घोषणा DESC92C_RATE11M				0x03

/*  OFDM Rates, TxHT = 0 */
#घोषणा DESC92C_RATE6M				0x04
#घोषणा DESC92C_RATE9M				0x05
#घोषणा DESC92C_RATE12M				0x06
#घोषणा DESC92C_RATE18M				0x07
#घोषणा DESC92C_RATE24M				0x08
#घोषणा DESC92C_RATE36M				0x09
#घोषणा DESC92C_RATE48M				0x0a
#घोषणा DESC92C_RATE54M				0x0b

/*  MCS Rates, TxHT = 1 */
#घोषणा DESC92C_RATEMCS0			0x0c
#घोषणा DESC92C_RATEMCS1			0x0d
#घोषणा DESC92C_RATEMCS2			0x0e
#घोषणा DESC92C_RATEMCS3			0x0f
#घोषणा DESC92C_RATEMCS4			0x10
#घोषणा DESC92C_RATEMCS5			0x11
#घोषणा DESC92C_RATEMCS6			0x12
#घोषणा DESC92C_RATEMCS7			0x13
#घोषणा DESC92C_RATEMCS8			0x14
#घोषणा DESC92C_RATEMCS9			0x15
#घोषणा DESC92C_RATEMCS10			0x16
#घोषणा DESC92C_RATEMCS11			0x17
#घोषणा DESC92C_RATEMCS12			0x18
#घोषणा DESC92C_RATEMCS13			0x19
#घोषणा DESC92C_RATEMCS14			0x1a
#घोषणा DESC92C_RATEMCS15			0x1b
#घोषणा DESC92C_RATEMCS15_SG			0x1c
#घोषणा DESC92C_RATEMCS32			0x20

/*  काष्ठाure and define */

काष्ठा phy_rx_agc_info अणु
	#अगर_घोषित __LITTLE_ENDIAN
		u8	gain:7, trsw:1;
	#अन्यथा
		u8	trsw:1, gain:7;
	#पूर्ण_अगर
पूर्ण;

काष्ठा phy_status_rpt अणु
	काष्ठा phy_rx_agc_info path_agc[RF_PATH_MAX];
	u8	ch_corr[2];
	u8	cck_sig_qual_ofdm_pwdb_all;
	u8	cck_agc_rpt_ofdm_cfosho_a;
	u8	cck_rpt_b_ofdm_cfosho_b;
	u8	rsvd_1;/* ch_corr_msb; */
	u8	noise_घातer_db_msb;
	u8	path_cfotail[2];
	u8	pcts_mask[2];
	s8	stream_rxevm[2];
	u8	path_rxsnr[3];
	u8	noise_घातer_db_lsb;
	u8	rsvd_2[3];
	u8	stream_csi[2];
	u8	stream_target_csi[2];
	s8	sig_evm;
	u8	rsvd_3;

#अगर_घोषित __LITTLE_ENDIAN
	u8	antsel_rx_keep_2:1;	/* ex_पूर्णांकf_flg:1; */
	u8	sgi_en:1;
	u8	rxsc:2;
	u8	idle_दीर्घ:1;
	u8	r_ant_train_en:1;
	u8	ant_sel_b:1;
	u8	ant_sel:1;
#अन्यथा	/*  _BIG_ENDIAN_ */
	u8	ant_sel:1;
	u8	ant_sel_b:1;
	u8	r_ant_train_en:1;
	u8	idle_दीर्घ:1;
	u8	rxsc:2;
	u8	sgi_en:1;
	u8	antsel_rx_keep_2:1;	/* ex_पूर्णांकf_flg:1; */
#पूर्ण_अगर
पूर्ण;

व्योम odm_phy_status_query(काष्ठा odm_dm_काष्ठा *dm_odm,
			  काष्ठा odm_phy_status_info *phy_info,
			  u8 *phy_status,
			  काष्ठा odm_per_pkt_info *pkt_info);

#पूर्ण_अगर
