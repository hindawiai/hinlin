<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

/*
 * phy_hal.h:  functionality exported from the phy to higher layers
 */

#अगर_अघोषित _BRCM_PHY_HAL_H_
#घोषणा _BRCM_PHY_HAL_H_

#समावेश <brcmu_utils.h>
#समावेश <brcmu_wअगरi.h>
#समावेश <phy_shim.h>

#घोषणा	IDCODE_VER_MASK		0x0000000f
#घोषणा	IDCODE_VER_SHIFT	0
#घोषणा	IDCODE_MFG_MASK		0x00000fff
#घोषणा	IDCODE_MFG_SHIFT	0
#घोषणा	IDCODE_ID_MASK		0x0ffff000
#घोषणा	IDCODE_ID_SHIFT		12
#घोषणा	IDCODE_REV_MASK		0xf0000000
#घोषणा	IDCODE_REV_SHIFT	28

#घोषणा	NORADIO_ID		0xe4f5
#घोषणा	NORADIO_IDCODE		0x4e4f5246

#घोषणा BCM2055_ID		0x2055
#घोषणा BCM2055_IDCODE		0x02055000
#घोषणा BCM2055A0_IDCODE	0x1205517f

#घोषणा BCM2056_ID		0x2056
#घोषणा BCM2056_IDCODE		0x02056000
#घोषणा BCM2056A0_IDCODE	0x1205617f

#घोषणा BCM2057_ID		0x2057
#घोषणा BCM2057_IDCODE		0x02057000
#घोषणा BCM2057A0_IDCODE	0x1205717f

#घोषणा BCM2064_ID		0x2064
#घोषणा BCM2064_IDCODE		0x02064000
#घोषणा BCM2064A0_IDCODE	0x0206417f

#घोषणा PHY_TPC_HW_OFF		false
#घोषणा PHY_TPC_HW_ON		true

#घोषणा PHY_PERICAL_DRIVERUP	1
#घोषणा PHY_PERICAL_WATCHDOG	2
#घोषणा PHY_PERICAL_PHYINIT	3
#घोषणा PHY_PERICAL_JOIN_BSS	4
#घोषणा PHY_PERICAL_START_IBSS	5
#घोषणा PHY_PERICAL_UP_BSS	6
#घोषणा PHY_PERICAL_CHAN	7
#घोषणा PHY_FULLCAL	8

#घोषणा PHY_PERICAL_DISABLE	0
#घोषणा PHY_PERICAL_SPHASE	1
#घोषणा PHY_PERICAL_MPHASE	2
#घोषणा PHY_PERICAL_MANUAL	3

#घोषणा PHY_HOLD_FOR_ASSOC	1
#घोषणा PHY_HOLD_FOR_SCAN	2
#घोषणा PHY_HOLD_FOR_RM		4
#घोषणा PHY_HOLD_FOR_PLT	8
#घोषणा PHY_HOLD_FOR_MUTE	16
#घोषणा PHY_HOLD_FOR_NOT_ASSOC 0x20

#घोषणा PHY_MUTE_FOR_PREISM	1
#घोषणा PHY_MUTE_ALL		0xffffffff

#घोषणा PHY_NOISE_FIXED_VAL		(-95)
#घोषणा PHY_NOISE_FIXED_VAL_NPHY	(-92)
#घोषणा PHY_NOISE_FIXED_VAL_LCNPHY	(-92)

#घोषणा PHY_MODE_CAL		0x0002
#घोषणा PHY_MODE_NOISEM		0x0004

#घोषणा BRCMS_TXPWR_DB_FACTOR	4

/* a large TX Power as an init value to factor out of min() calculations,
 * keep low enough to fit in an s8, units are .25 dBm
 */
#घोषणा BRCMS_TXPWR_MAX		(127)	/* ~32 dBm = 1,500 mW */

#घोषणा BRCMS_NUM_RATES_CCK           4
#घोषणा BRCMS_NUM_RATES_OFDM          8
#घोषणा BRCMS_NUM_RATES_MCS_1_STREAM  8
#घोषणा BRCMS_NUM_RATES_MCS_2_STREAM  8
#घोषणा BRCMS_NUM_RATES_MCS_3_STREAM  8
#घोषणा BRCMS_NUM_RATES_MCS_4_STREAM  8

#घोषणा	BRCMS_RSSI_INVALID	 0	/* invalid RSSI value */

काष्ठा d11regs;
काष्ठा phy_shim_info;

काष्ठा txpwr_limits अणु
	u8 cck[BRCMS_NUM_RATES_CCK];
	u8 ofdm[BRCMS_NUM_RATES_OFDM];

	u8 ofdm_cdd[BRCMS_NUM_RATES_OFDM];

	u8 ofdm_40_siso[BRCMS_NUM_RATES_OFDM];
	u8 ofdm_40_cdd[BRCMS_NUM_RATES_OFDM];

	u8 mcs_20_siso[BRCMS_NUM_RATES_MCS_1_STREAM];
	u8 mcs_20_cdd[BRCMS_NUM_RATES_MCS_1_STREAM];
	u8 mcs_20_stbc[BRCMS_NUM_RATES_MCS_1_STREAM];
	u8 mcs_20_mimo[BRCMS_NUM_RATES_MCS_2_STREAM];

	u8 mcs_40_siso[BRCMS_NUM_RATES_MCS_1_STREAM];
	u8 mcs_40_cdd[BRCMS_NUM_RATES_MCS_1_STREAM];
	u8 mcs_40_stbc[BRCMS_NUM_RATES_MCS_1_STREAM];
	u8 mcs_40_mimo[BRCMS_NUM_RATES_MCS_2_STREAM];
	u8 mcs32;
पूर्ण;

काष्ठा tx_घातer अणु
	u32 flags;
	u16 chanspec;   /* txpwr report क्रम this channel */
	u16 local_chanspec;     /* channel on which we are associated */
	u8 local_max;   /* local max according to the AP */
	u8 local_स्थिरraपूर्णांक;    /* local स्थिरraपूर्णांक according to the AP */
	s8 antgain[2];  /* Ant gain क्रम each band - from SROM */
	u8 rf_cores;            /* count of RF Cores being reported */
	u8 est_Pout[4]; /* Latest tx घातer out estimate per RF chain */
	u8 est_Pout_act[4];     /* Latest tx घातer out estimate per RF chain
				 * without adjusपंचांगent */
	u8 est_Pout_cck;        /* Latest CCK tx घातer out estimate */
	u8 tx_घातer_max[4];     /* Maximum target घातer among all rates */
	/* Index of the rate with the max target घातer */
	u8 tx_घातer_max_rate_ind[4];
	/* User limit */
	u8 user_limit[WL_TX_POWER_RATES];
	/* Regulatory घातer limit */
	u8 reg_limit[WL_TX_POWER_RATES];
	/* Max घातer board can support (SROM) */
	u8 board_limit[WL_TX_POWER_RATES];
	/* Latest target घातer */
	u8 target[WL_TX_POWER_RATES];
पूर्ण;

काष्ठा tx_inst_घातer अणु
	u8 txpwr_est_Pout[2];   /* Latest estimate क्रम 2.4 and 5 Ghz */
	u8 txpwr_est_Pout_gofdm;        /* Pwr estimate क्रम 2.4 OFDM */
पूर्ण;

काष्ठा brcms_chanvec अणु
	u8 vec[MAXCHANNEL / NBBY];
पूर्ण;

काष्ठा shared_phy_params अणु
	काष्ठा si_pub *sih;
	काष्ठा phy_shim_info *physhim;
	uपूर्णांक unit;
	uपूर्णांक corerev;
	u16 vid;
	u16 did;
	uपूर्णांक chip;
	uपूर्णांक chiprev;
	uपूर्णांक chippkg;
	uपूर्णांक sromrev;
	uपूर्णांक boardtype;
	uपूर्णांक boardrev;
	u32 boardflags;
	u32 boardflags2;
पूर्ण;


काष्ठा shared_phy *wlc_phy_shared_attach(काष्ठा shared_phy_params *shp);
काष्ठा brcms_phy_pub *wlc_phy_attach(काष्ठा shared_phy *sh,
				     काष्ठा bcma_device *d11core, पूर्णांक bandtype,
				     काष्ठा wiphy *wiphy);
व्योम wlc_phy_detach(काष्ठा brcms_phy_pub *ppi);

bool wlc_phy_get_phyversion(काष्ठा brcms_phy_pub *pih, u16 *phytype,
			    u16 *phyrev, u16 *radioid, u16 *radiover);
bool wlc_phy_get_encore(काष्ठा brcms_phy_pub *pih);
u32 wlc_phy_get_coreflags(काष्ठा brcms_phy_pub *pih);

व्योम wlc_phy_hw_clk_state_upd(काष्ठा brcms_phy_pub *ppi, bool newstate);
व्योम wlc_phy_hw_state_upd(काष्ठा brcms_phy_pub *ppi, bool newstate);
व्योम wlc_phy_init(काष्ठा brcms_phy_pub *ppi, u16 chanspec);
व्योम wlc_phy_watchकरोg(काष्ठा brcms_phy_pub *ppi);
पूर्णांक wlc_phy_करोwn(काष्ठा brcms_phy_pub *ppi);
u32 wlc_phy_clk_bwbits(काष्ठा brcms_phy_pub *pih);
व्योम wlc_phy_cal_init(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_antsel_init(काष्ठा brcms_phy_pub *ppi, bool lut_init);

व्योम wlc_phy_chanspec_set(काष्ठा brcms_phy_pub *ppi, u16 chanspec);
u16 wlc_phy_chanspec_get(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_chanspec_radio_set(काष्ठा brcms_phy_pub *ppi, u16 newch);
u16 wlc_phy_bw_state_get(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_bw_state_set(काष्ठा brcms_phy_pub *ppi, u16 bw);

पूर्णांक wlc_phy_rssi_compute(काष्ठा brcms_phy_pub *pih, काष्ठा d11rxhdr *rxh);
व्योम wlc_phy_por_inक्रमm(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_noise_sample_पूर्णांकr(काष्ठा brcms_phy_pub *ppi);
bool wlc_phy_bist_check_phy(काष्ठा brcms_phy_pub *ppi);

व्योम wlc_phy_set_deaf(काष्ठा brcms_phy_pub *ppi, bool user_flag);

व्योम wlc_phy_चयन_radio(काष्ठा brcms_phy_pub *ppi, bool on);
व्योम wlc_phy_anacore(काष्ठा brcms_phy_pub *ppi, bool on);


व्योम wlc_phy_BSSinit(काष्ठा brcms_phy_pub *ppi, bool bonlyap, पूर्णांक rssi);

व्योम wlc_phy_chanspec_ch14_widefilter_set(काष्ठा brcms_phy_pub *ppi,
					  bool wide_filter);
व्योम wlc_phy_chanspec_band_validch(काष्ठा brcms_phy_pub *ppi, uपूर्णांक band,
				   काष्ठा brcms_chanvec *channels);
u16 wlc_phy_chanspec_band_firstch(काष्ठा brcms_phy_pub *ppi, uपूर्णांक band);

व्योम wlc_phy_txघातer_sromlimit(काष्ठा brcms_phy_pub *ppi, uपूर्णांक chan, u8 *_min_,
			       u8 *_max_, पूर्णांक rate);
व्योम wlc_phy_txघातer_sromlimit_max_get(काष्ठा brcms_phy_pub *ppi, uपूर्णांक chan,
				       u8 *_max_, u8 *_min_);
व्योम wlc_phy_txघातer_boardlimit_band(काष्ठा brcms_phy_pub *ppi, uपूर्णांक band,
				     s32 *, s32 *, u32 *);
व्योम wlc_phy_txघातer_limit_set(काष्ठा brcms_phy_pub *ppi, काष्ठा txpwr_limits *,
			       u16 chanspec);
पूर्णांक wlc_phy_txघातer_get(काष्ठा brcms_phy_pub *ppi, uपूर्णांक *qdbm, bool *override);
पूर्णांक wlc_phy_txघातer_set(काष्ठा brcms_phy_pub *ppi, uपूर्णांक qdbm, bool override);
व्योम wlc_phy_txघातer_target_set(काष्ठा brcms_phy_pub *ppi,
				काष्ठा txpwr_limits *);
bool wlc_phy_txघातer_hw_ctrl_get(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_txघातer_hw_ctrl_set(काष्ठा brcms_phy_pub *ppi, bool hwpwrctrl);
u8 wlc_phy_txघातer_get_target_min(काष्ठा brcms_phy_pub *ppi);
u8 wlc_phy_txघातer_get_target_max(काष्ठा brcms_phy_pub *ppi);
bool wlc_phy_txघातer_ipa_ison(काष्ठा brcms_phy_pub *pih);

व्योम wlc_phy_stf_chain_init(काष्ठा brcms_phy_pub *pih, u8 txchain, u8 rxchain);
व्योम wlc_phy_stf_chain_set(काष्ठा brcms_phy_pub *pih, u8 txchain, u8 rxchain);
व्योम wlc_phy_stf_chain_get(काष्ठा brcms_phy_pub *pih, u8 *txchain, u8 *rxchain);
u8 wlc_phy_stf_chain_active_get(काष्ठा brcms_phy_pub *pih);
s8 wlc_phy_stf_ssmode_get(काष्ठा brcms_phy_pub *pih, u16 chanspec);
व्योम wlc_phy_ldpc_override_set(काष्ठा brcms_phy_pub *ppi, bool val);

व्योम wlc_phy_cal_perical(काष्ठा brcms_phy_pub *ppi, u8 reason);
व्योम wlc_phy_noise_sample_request_बाह्यal(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_edcrs_lock(काष्ठा brcms_phy_pub *pih, bool lock);
व्योम wlc_phy_cal_papd_recal(काष्ठा brcms_phy_pub *ppi);

व्योम wlc_phy_ant_rxभाग_set(काष्ठा brcms_phy_pub *ppi, u8 val);
व्योम wlc_phy_clear_tssi(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_hold_upd(काष्ठा brcms_phy_pub *ppi, u32 id, bool val);
व्योम wlc_phy_mute_upd(काष्ठा brcms_phy_pub *ppi, bool val, u32 flags);

व्योम wlc_phy_antsel_type_set(काष्ठा brcms_phy_pub *ppi, u8 antsel_type);

व्योम wlc_phy_txघातer_get_current(काष्ठा brcms_phy_pub *ppi,
				 काष्ठा tx_घातer *घातer, uपूर्णांक channel);

व्योम wlc_phy_initcal_enable(काष्ठा brcms_phy_pub *pih, bool initcal);
bool wlc_phy_test_ison(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_txpwr_percent_set(काष्ठा brcms_phy_pub *ppi, u8 txpwr_percent);
व्योम wlc_phy_ofdm_rateset_war(काष्ठा brcms_phy_pub *pih, bool war);
व्योम wlc_phy_bf_preempt_enable(काष्ठा brcms_phy_pub *pih, bool bf_preempt);
व्योम wlc_phy_machwcap_set(काष्ठा brcms_phy_pub *ppi, u32 machwcap);

व्योम wlc_phy_runbist_config(काष्ठा brcms_phy_pub *ppi, bool start_end);

व्योम wlc_phy_freqtrack_start(काष्ठा brcms_phy_pub *ppi);
व्योम wlc_phy_freqtrack_end(काष्ठा brcms_phy_pub *ppi);

स्थिर u8 *wlc_phy_get_ofdm_rate_lookup(व्योम);

s8 wlc_phy_get_tx_घातer_offset_by_mcs(काष्ठा brcms_phy_pub *ppi,
				      u8 mcs_offset);
s8 wlc_phy_get_tx_घातer_offset(काष्ठा brcms_phy_pub *ppi, u8 tbl_offset);
#पूर्ण_अगर                          /* _BRCM_PHY_HAL_H_ */
